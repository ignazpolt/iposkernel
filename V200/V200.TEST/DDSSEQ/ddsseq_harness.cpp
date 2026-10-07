#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "DDS32.H"
#include "GLOBMEM.H"
#include "DLLADMIN.H"
#include "DLLADMIN.HPP"
#include "TBDEF.HPP"

extern DLLExport LPSTR _export WINAPI SetStartDir(LPSTR dirname, LPSTR IniFile);

static void PrintUsage(const char* prog)
{
  printf("Usage: %s [script|resource|dict|all] [--ini <ini-file>]\n", prog);
  printf("Runs DDSSEQ CRUD smoke tests against copied SEQ files.\n");
  printf("Default mode is 'all', default ini is DMW.INI in the current folder.\n");
}

static GLOBALHANDLE MakeBlobFromBytes(const unsigned char* data, DWORD size)
{
  GLOBALHANDLE h = GlobalAlloc(GMEM_MOVEABLE, size);
  if (h == NULL) return NULL;

  LPVOID p = GlobalLock(h);
  if (p == NULL) {
    GlobalFree(h);
    return NULL;
  }

  if (size > 0 && data != NULL) memcpy(p, data, size);
  GlobalUnlock(h);
  return h;
}

static bool ReadBlobToVector(GLOBALHANDLE h, DWORD size, std::vector<unsigned char>& out)
{
  out.clear();
  if (h == NULL) return false;

  LPVOID p = GlobalLock(h);
  if (p == NULL) {
    GlobalFree(h);
    return false;
  }

  out.resize(size);
  if (size > 0) memcpy(&out[0], p, size);
  GlobalUnlock(h);
  GlobalFree(h);
  return true;
}

static bool WriteScriptBytes(short type, const char* name, const char* payload)
{
  DWORD size = (DWORD) strlen(payload);
  GLOBALHANDLE h = MakeBlobFromBytes((const unsigned char*) payload, size);
  if (h == NULL) return false;
  __try {
    WriteScriptData(type, (LPSTR) name, h, size);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[script] ERROR: exception in WriteScriptData, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    GlobalFree(h);
    return false;
  }
  GlobalFree(h);
  return true;
}

static bool WriteResourceBytes(short type, const char* name, const char* payload)
{
  DWORD size = (DWORD) strlen(payload);
  GLOBALHANDLE h = MakeBlobFromBytes((const unsigned char*) payload, size);
  if (h == NULL) return false;
  __try {
    WriteResourceData(type, (LPSTR) name, h, size);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[resource] ERROR: exception in WriteResourceData, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    GlobalFree(h);
    return false;
  }
  GlobalFree(h);
  return true;
}

static bool WriteDictBytes(short type, const char* name, short tableId, short version, const char* payload)
{
  DWORD size = (DWORD) strlen(payload);
  GLOBALHANDLE h = MakeBlobFromBytes((const unsigned char*) payload, size);
  if (h == NULL) return false;
  __try {
    WriteDataDict(type, (LPSTR) name, tableId, version, 0, 0, h, size);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[dict] ERROR: exception in WriteDataDict, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    GlobalFree(h);
    return false;
  }
  GlobalFree(h);
  return true;
}

static bool SafeReadDataDict(short type, WORD tableId, WORD version, GLOBALHANDLE* outHandle, DWORD* outSize)
{
  *outHandle = NULL;
  *outSize = 0;
  __try {
    *outHandle = ReadDataDict(type, tableId, version, outSize);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[dict] ERROR: exception in ReadDataDict, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    return false;
  }
  return true;
}

static bool SafeDelDataDict(short type, WORD tableId, WORD version)
{
  __try {
    DelDataDict(type, tableId, version);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[dict] ERROR: exception in DelDataDict, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    return false;
  }
  return true;
}

static bool VerifyBytes(const std::vector<unsigned char>& got, const char* expected)
{
  size_t expSize = strlen(expected);
  if (got.size() != expSize) return false;
  if (expSize == 0) return true;
  return memcmp(&got[0], expected, expSize) == 0;
}

static bool InitHarness(const char* iniName)
{
  char cwd[MAX_PATH];
  if (GetCurrentDirectoryA(MAX_PATH, cwd) == 0) {
    printf("[init] ERROR: GetCurrentDirectory failed.\n");
    return false;
  }

  if (SetStartDir(cwd, (LPSTR) iniName) == NULL) {
    printf("[init] ERROR: SetStartDir failed for %s.\n", iniName);
    return false;
  }

  __try {
    GetTableAdmin()->Initialize(FALSE);
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[init] ERROR: exception in TableAdmin::Initialize, code=0x%08lX\n", (unsigned long) GetExceptionCode());
    return false;
  }
  return true;
}

static void ShutdownHarness()
{
  __try {
    GetTableAdmin()->OnExit();
    GetDLLAdmin()->ResetDLLAdmin();
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[shutdown] WARNING: exception during cleanup, code=0x%08lX\n", (unsigned long) GetExceptionCode());
  }
}

static bool TestScriptDB()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char name[64];
  wsprintfA(name, "__HARNESS_SCRIPT_%lu", (unsigned long) (stamp % 100000));

  const char* payloadV1 = "SCRIPT_PAYLOAD_V1";
  const char* payloadV2 = "SCRIPT_PAYLOAD_V2_WITH_LONGER_CONTENT";

  printf("[script] Create and read: %s\n", name);
  fflush(stdout);
  if (!WriteScriptBytes(type, name, payloadV1)) {
    printf("[script] ERROR: write v1 failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(type, name, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV1)) {
    printf("[script] ERROR: read-back of v1 failed.\n");
    return false;
  }

  printf("[script] Update and read: %s\n", name);
  fflush(stdout);
  if (!WriteScriptBytes(type, name, payloadV2)) {
    printf("[script] ERROR: write v2 failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, name, &size);
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV2)) {
    printf("[script] ERROR: read-back of v2 failed.\n");
    return false;
  }

  printf("[script] PASS\n");
  return true;
}

static bool TestResourceDB()
{
  DWORD stamp = GetTickCount();
  short type = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_RESOURCE_%lu", (unsigned long) (stamp % 100000));

  const char* payloadV1 = "RESOURCE_PAYLOAD_V1";
  const char* payloadV2 = "RESOURCE_PAYLOAD_V2_WITH_LONGER_CONTENT";

  printf("[resource] Create and read: %s\n", name);
  fflush(stdout);
  if (!WriteResourceBytes(type, name, payloadV1)) {
    printf("[resource] ERROR: write v1 failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadResourceData(type, (LPSTR) name, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV1)) {
    printf("[resource] ERROR: read-back of v1 failed.\n");
    return false;
  }

  printf("[resource] Update and read: %s\n", name);
  fflush(stdout);
  if (!WriteResourceBytes(type, name, payloadV2)) {
    printf("[resource] ERROR: write v2 failed.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(type, (LPSTR) name, &size);
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV2)) {
    printf("[resource] ERROR: read-back of v2 failed.\n");
    return false;
  }

  printf("[resource] PASS\n");
  return true;
}

static bool TestDataDict()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  short tableId = (short) (30000 + (stamp % 1000));
  short version = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_TABLE_%hu", (unsigned short) tableId);

  const char* payloadV1 = "DICT_PAYLOAD_V1";
  const char* payloadV2 = "DICT_PAYLOAD_V2_WITH_LONGER_CONTENT";

  printf("[dict] Create and read: %s (id=%hd ver=%hd)\n", name, tableId, version);
  fflush(stdout);
  if (!WriteDictBytes(type, name, tableId, version, payloadV1)) {
    printf("[dict] ERROR: write v1 failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = NULL;
  if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
    return false;
  }
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV1)) {
    printf("[dict] ERROR: read-back of v1 failed.\n");
    return false;
  }

  printf("[dict] Update and read: %s\n", name);
  fflush(stdout);
  if (!WriteDictBytes(type, name, tableId, version, payloadV2)) {
    printf("[dict] ERROR: write v2 failed.\n");
    return false;
  }

  size = 0;
  if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
    return false;
  }
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV2)) {
    printf("[dict] ERROR: read-back of v2 failed.\n");
    return false;
  }

  printf("[dict] Delete and verify: %s\n", name);
  if (!SafeDelDataDict(type, (WORD) tableId, (WORD) version)) {
    return false;
  }
  size = 0;
  if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
    return false;
  }
  if (h != NULL) {
    GlobalFree(h);
    printf("[dict] ERROR: record still exists after delete.\n");
    return false;
  }

  printf("[dict] PASS\n");
  return true;
}

int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  const char* mode = "all";
  const char* iniName = "DMW.INI";

  for (int i = 1; i < argc; ++i) {
    if ((_stricmp(argv[i], "--ini") == 0) && (i + 1 < argc)) {
      iniName = argv[++i];
    } else if ((_stricmp(argv[i], "-h") == 0) || (_stricmp(argv[i], "--help") == 0)) {
      PrintUsage(argv[0]);
      return 0;
    } else {
      mode = argv[i];
    }
  }

  if (!InitHarness(iniName)) return 2;

  bool ok = true;
  if (_stricmp(mode, "script") == 0) {
    ok = TestScriptDB();
  } else if (_stricmp(mode, "resource") == 0) {
    ok = TestResourceDB();
  } else if (_stricmp(mode, "dict") == 0) {
    ok = TestDataDict();
  } else if (_stricmp(mode, "all") == 0) {
    ok = TestScriptDB() && TestResourceDB() && TestDataDict();
  } else {
    PrintUsage(argv[0]);
    ShutdownHarness();
    return 1;
  }

  ShutdownHarness();
  return ok ? 0 : 3;
}
