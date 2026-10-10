#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#include "DDS32.H"
#include "GLOBMEM.H"
#include "DLLADMIN.H"
#include "DLLADMIN.HPP"
#include "TBDEF.HPP"

extern DLLExport LPSTR _export WINAPI SetStartDir(LPSTR dirname, LPSTR IniFile);

static void PrintUsage(const char* prog)
{
  printf("Usage: %s [script|resource|dict|all|xproc-write|xproc-read] [--ini <ini-file>]\n", prog);
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

static std::string MakeRealisticPayload(size_t length, DWORD seed)
{
  static const char kAlphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 "
    "_-/.:,;[]{}()<>!=?&|#@\n\r\t";

  std::string out;
  out.reserve(length);
  const size_t alphabetLen = sizeof(kAlphabet) - 1;

  for (size_t i = 0; i < length; ++i) {
    size_t index = (seed + i * 17 + i / 5) % alphabetLen;
    out.push_back(kAlphabet[index]);
  }

  return out;
}

static bool VerifyStringReadback(const std::vector<unsigned char>& got, const std::string& expected)
{
  if (got.size() != expected.size()) return false;
  if (expected.empty()) return true;
  return memcmp(&got[0], expected.c_str(), expected.size()) == 0;
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

static void ShutdownHarnessForRestart()
{
  __try {
    GetTableAdmin()->OnExit();
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    printf("[shutdown] WARNING: exception during restart cleanup, code=0x%08lX\n", (unsigned long) GetExceptionCode());
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

static bool TestScriptDBRealistic()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char name[64];
  wsprintfA(name, "__HARNESS_SCRIPT_REAL_%lu", (unsigned long) (stamp % 100000));

  const DWORD seeds[] = { 7, 13, 29, 41 };
  const size_t lens[] = { 40, 180, 32, 512 };

  printf("[script realistic] start: %s\n", name);
  fflush(stdout);

  for (size_t i = 0; i < sizeof(lens) / sizeof(lens[0]); ++i) {
    std::string payload = MakeRealisticPayload(lens[i], seeds[i]);
    if (!WriteScriptBytes(type, name, payload.c_str())) {
      printf("[script realistic] ERROR: write stage %zu failed.\n", i);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = ReadScriptData(type, name, &size);
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payload)) {
      printf("[script realistic] ERROR: read-back stage %zu failed.\n", i);
      return false;
    }
  }

  printf("[script realistic] PASS\n");
  return true;
}

static bool TestResourceDBRealistic()
{
  DWORD stamp = GetTickCount();
  short type = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_RESOURCE_REAL_%lu", (unsigned long) (stamp % 100000));

  const DWORD seeds[] = { 3, 11, 19, 47 };
  const size_t lens[] = { 64, 220, 16, 420 };

  printf("[resource realistic] start: %s\n", name);
  fflush(stdout);

  for (size_t i = 0; i < sizeof(lens) / sizeof(lens[0]); ++i) {
    std::string payload = MakeRealisticPayload(lens[i], seeds[i]);
    if (!WriteResourceBytes(type, name, payload.c_str())) {
      printf("[resource realistic] ERROR: write stage %zu failed.\n", i);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = ReadResourceData(type, (LPSTR) name, &size);
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payload)) {
      printf("[resource realistic] ERROR: read-back stage %zu failed.\n", i);
      return false;
    }
  }

  printf("[resource realistic] PASS\n");
  return true;
}

static bool TestDataDictRealistic()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  short tableId = (short) (31000 + (stamp % 2000));
  short version = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_TABLE_REAL_%hu", (unsigned short) tableId);

  const DWORD seeds[] = { 5, 17, 23, 53 };
  const size_t lens[] = { 48, 260, 12, 600 };

  printf("[dict realistic] start: %s (id=%hd ver=%hd)\n", name, tableId, version);
  fflush(stdout);

  for (size_t i = 0; i < sizeof(lens) / sizeof(lens[0]); ++i) {
    std::string payload = MakeRealisticPayload(lens[i], seeds[i]);
    if (!WriteDictBytes(type, name, tableId, version, payload.c_str())) {
      printf("[dict realistic] ERROR: write stage %zu failed.\n", i);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = NULL;
    if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
      return false;
    }
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payload)) {
      printf("[dict realistic] ERROR: read-back stage %zu failed.\n", i);
      return false;
    }
  }

  if (!SafeDelDataDict(type, (WORD) tableId, (WORD) version)) {
    return false;
  }

  printf("[dict realistic] PASS\n");
  return true;
}

static bool TestScriptDBStressLoop()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char name[64];
  wsprintfA(name, "__HARNESS_SCRIPT_STRESS_%lu", (unsigned long) (stamp % 100000));

  printf("[script stress] start: %s\n", name);
  fflush(stdout);

  for (int round = 0; round < 6; ++round) {
    std::string payloadA = MakeRealisticPayload(32 + round * 13, 100 + round);
    std::string payloadB = MakeRealisticPayload(200 + round * 27, 200 + round * 3);
    std::string payloadC = MakeRealisticPayload(18 + round * 9, 300 + round * 5);

    if (!WriteScriptBytes(type, name, payloadA.c_str())) {
      printf("[script stress] ERROR: create round %d failed.\n", round);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = ReadScriptData(type, name, &size);
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadA)) {
      printf("[script stress] ERROR: read round %d after create failed.\n", round);
      return false;
    }

    if (!WriteScriptBytes(type, name, payloadB.c_str())) {
      printf("[script stress] ERROR: update to longer round %d failed.\n", round);
      return false;
    }

    size = 0;
    h = ReadScriptData(type, name, &size);
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadB)) {
      printf("[script stress] ERROR: read round %d after larger update failed.\n", round);
      return false;
    }

    if (!WriteScriptBytes(type, name, payloadC.c_str())) {
      printf("[script stress] ERROR: update to shorter round %d failed.\n", round);
      return false;
    }

    size = 0;
    h = ReadScriptData(type, name, &size);
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadC)) {
      printf("[script stress] ERROR: read round %d after shorter update failed.\n", round);
      return false;
    }
  }

  printf("[script stress] PASS\n");
  return true;
}

static bool TestResourceDBStressLoop()
{
  DWORD stamp = GetTickCount();
  short type = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_RESOURCE_STRESS_%lu", (unsigned long) (stamp % 100000));

  printf("[resource stress] start: %s\n", name);
  fflush(stdout);

  for (int round = 0; round < 6; ++round) {
    std::string payloadA = MakeRealisticPayload(40 + round * 12, 101 + round);
    std::string payloadB = MakeRealisticPayload(210 + round * 31, 203 + round * 2);
    std::string payloadC = MakeRealisticPayload(24 + round * 7, 307 + round * 5);

    if (!WriteResourceBytes(type, name, payloadA.c_str())) {
      printf("[resource stress] ERROR: create round %d failed.\n", round);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = ReadResourceData(type, (LPSTR) name, &size);
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadA)) {
      printf("[resource stress] ERROR: read round %d after create failed.\n", round);
      return false;
    }

    if (!WriteResourceBytes(type, name, payloadB.c_str())) {
      printf("[resource stress] ERROR: update to longer round %d failed.\n", round);
      return false;
    }

    size = 0;
    h = ReadResourceData(type, (LPSTR) name, &size);
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadB)) {
      printf("[resource stress] ERROR: read round %d after larger update failed.\n", round);
      return false;
    }

    if (!WriteResourceBytes(type, name, payloadC.c_str())) {
      printf("[resource stress] ERROR: update to shorter round %d failed.\n", round);
      return false;
    }

    size = 0;
    h = ReadResourceData(type, (LPSTR) name, &size);
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadC)) {
      printf("[resource stress] ERROR: read round %d after shorter update failed.\n", round);
      return false;
    }
  }

  printf("[resource stress] PASS\n");
  return true;
}

static bool TestDataDictStressLoop()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  short tableId = (short) (33000 + (stamp % 1500));
  short version = 1;
  char name[64];
  wsprintfA(name, "__HARNESS_TABLE_STRESS_%hu", (unsigned short) tableId);

  printf("[dict stress] start: %s (id=%hd ver=%hd)\n", name, tableId, version);
  fflush(stdout);

  for (int round = 0; round < 6; ++round) {
    std::string payloadA = MakeRealisticPayload(44 + round * 14, 110 + round);
    std::string payloadB = MakeRealisticPayload(260 + round * 33, 220 + round * 2);
    std::string payloadC = MakeRealisticPayload(28 + round * 9, 330 + round * 4);

    if (!WriteDictBytes(type, name, tableId, version, payloadA.c_str())) {
      printf("[dict stress] ERROR: create round %d failed.\n", round);
      return false;
    }

    DWORD size = 0;
    GLOBALHANDLE h = NULL;
    if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
      return false;
    }
    std::vector<unsigned char> got;
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadA)) {
      printf("[dict stress] ERROR: read round %d after create failed.\n", round);
      return false;
    }

    if (!WriteDictBytes(type, name, tableId, version, payloadB.c_str())) {
      printf("[dict stress] ERROR: update to longer round %d failed.\n", round);
      return false;
    }

    size = 0;
    if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
      return false;
    }
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadB)) {
      printf("[dict stress] ERROR: read round %d after larger update failed.\n", round);
      return false;
    }

    if (!WriteDictBytes(type, name, tableId, version, payloadC.c_str())) {
      printf("[dict stress] ERROR: update to shorter round %d failed.\n", round);
      return false;
    }

    size = 0;
    if (!SafeReadDataDict(type, (WORD) tableId, (WORD) version, &h, &size)) {
      return false;
    }
    got.clear();
    if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, payloadC)) {
      printf("[dict stress] ERROR: read round %d after shorter update failed.\n", round);
      return false;
    }
  }

  if (!SafeDelDataDict(type, (WORD) tableId, (WORD) version)) {
    return false;
  }

  printf("[dict stress] PASS\n");
  return true;
}

static bool TestMixedWorkload()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char scriptName[64];
  char resourceName[64];
  short tableId = (short) (35000 + (stamp % 1000));
  short version = 1;

  wsprintfA(scriptName, "__HARNESS_MIX_SCRIPT_%lu", (unsigned long)(stamp % 100000));
  wsprintfA(resourceName, "__HARNESS_MIX_RESOURCE_%lu", (unsigned long)(stamp % 100000));

  printf("[mixed] start script=%s resource=%s table=%hd ver=%hd\n", scriptName, resourceName, tableId, version);
  fflush(stdout);

  std::string scriptA = MakeRealisticPayload(96, 1);
  std::string scriptB = MakeRealisticPayload(390, 2);
  std::string resourceA = MakeRealisticPayload(84, 11);
  std::string resourceB = MakeRealisticPayload(430, 12);
  std::string dictA = MakeRealisticPayload(120, 21);
  std::string dictB = MakeRealisticPayload(520, 22);

  if (!WriteScriptBytes(type, scriptName, scriptA.c_str()) ||
      !WriteResourceBytes(1, resourceName, resourceA.c_str()) ||
      !WriteDictBytes(type, scriptName, tableId, version, dictA.c_str())) {
    printf("[mixed] ERROR: initial mixed create failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(type, scriptName, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, scriptA)) {
    printf("[mixed] ERROR: script read-back after mixed create failed.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(1, resourceName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, resourceA)) {
    printf("[mixed] ERROR: resource read-back after mixed create failed.\n");
    return false;
  }

  size = 0;
  GLOBALHANDLE hDict = NULL;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dictA)) {
    printf("[mixed] ERROR: dict read-back after mixed create failed.\n");
    return false;
  }

  if (!WriteScriptBytes(type, scriptName, scriptB.c_str()) ||
      !WriteResourceBytes(1, resourceName, resourceB.c_str()) ||
      !WriteDictBytes(type, scriptName, tableId, version, dictB.c_str())) {
    printf("[mixed] ERROR: mixed update failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, scriptName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, scriptB)) {
    printf("[mixed] ERROR: script read-back after mixed update failed.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(1, resourceName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, resourceB)) {
    printf("[mixed] ERROR: resource read-back after mixed update failed.\n");
    return false;
  }

  size = 0;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dictB)) {
    printf("[mixed] ERROR: dict read-back after mixed update failed.\n");
    return false;
  }

  if (!SafeDelDataDict(type, (WORD)tableId, (WORD)version)) {
    return false;
  }

  printf("[mixed] PASS\n");
  return true;
}

static bool TestSameKeyReuse()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char name[64];
  wsprintfA(name, "__HARNESS_REUSE_%lu", (unsigned long)(stamp % 100000));

  const std::string v1 = MakeRealisticPayload(120, 700);
  const std::string v2 = MakeRealisticPayload(290, 701);
  const std::string v3 = MakeRealisticPayload(70, 702);

  printf("[reuse] same key overwritten and re-used: %s\n", name);
  fflush(stdout);

  if (!WriteScriptBytes(type, name, v1.c_str())) {
    printf("[reuse] ERROR: initial create failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(type, name, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, v1)) {
    printf("[reuse] ERROR: initial read-back failed.\n");
    return false;
  }

  if (!WriteScriptBytes(type, name, v2.c_str())) {
    printf("[reuse] ERROR: overwrite to v2 failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, name, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, v2)) {
    printf("[reuse] ERROR: reread of v2 failed.\n");
    return false;
  }

  if (!WriteScriptBytes(type, name, v3.c_str())) {
    printf("[reuse] ERROR: overwrite to v3 failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, name, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, v3)) {
    printf("[reuse] ERROR: reread of v3 failed.\n");
    return false;
  }

  short tableId = (short)(36000 + (stamp % 500));
  short version = 1;
  const std::string dictV1 = MakeRealisticPayload(150, 800);
  const std::string dictV2 = MakeRealisticPayload(300, 801);
  char dictName[64];
  wsprintfA(dictName, "__HARNESS_REUSE_DICT_%hu", (unsigned short)tableId);

  if (!WriteDictBytes(type, dictName, tableId, version, dictV1.c_str())) {
    printf("[reuse] ERROR: dict create failed.\n");
    return false;
  }

  size = 0;
  GLOBALHANDLE hDict = NULL;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dictV1)) {
    printf("[reuse] ERROR: dict read-back failed.\n");
    return false;
  }

  if (!WriteDictBytes(type, dictName, tableId, version, dictV2.c_str())) {
    printf("[reuse] ERROR: dict overwrite failed.\n");
    return false;
  }

  size = 0;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dictV2)) {
    printf("[reuse] ERROR: dict overwritten value wrong.\n");
    return false;
  }

  if (!SafeDelDataDict(type, (WORD)tableId, (WORD)version)) {
    return false;
  }

  printf("[reuse] PASS\n");
  return true;
}

static bool TestMultiTableSequentialMix()
{
  DWORD stamp = GetTickCount();
  short type = 0;
  char scriptName[64];
  char resourceName[64];
  char dictName[64];
  short tableId = (short)(37000 + (stamp % 600));
  short version = 1;

  wsprintfA(scriptName, "__HARNESS_MULTI_SCRIPT_%lu", (unsigned long)(stamp % 100000));
  wsprintfA(resourceName, "__HARNESS_MULTI_RESOURCE_%lu", (unsigned long)(stamp % 100000));
  wsprintfA(dictName, "__HARNESS_MULTI_DICT_%hu", (unsigned short)tableId);

  printf("[multi] start script=%s resource=%s table=%hd ver=%hd\n", scriptName, resourceName, tableId, version);
  fflush(stdout);

  std::string script1 = MakeRealisticPayload(80, 91);
  std::string script2 = MakeRealisticPayload(310, 92);
  std::string resource1 = MakeRealisticPayload(64, 201);
  std::string resource2 = MakeRealisticPayload(500, 202);
  std::string dict1 = MakeRealisticPayload(150, 301);
  std::string dict2 = MakeRealisticPayload(610, 302);

  if (!WriteScriptBytes(type, scriptName, script1.c_str())) {
    printf("[multi] ERROR: script create failed.\n");
    return false;
  }
  if (!WriteResourceBytes(1, resourceName, resource1.c_str())) {
    printf("[multi] ERROR: resource create failed.\n");
    return false;
  }
  if (!WriteDictBytes(type, dictName, tableId, version, dict1.c_str())) {
    printf("[multi] ERROR: dict create failed.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(type, scriptName, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, script1)) {
    printf("[multi] ERROR: script create read-back failed.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(1, resourceName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, resource1)) {
    printf("[multi] ERROR: resource create read-back failed.\n");
    return false;
  }

  size = 0;
  GLOBALHANDLE hDict = NULL;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dict1)) {
    printf("[multi] ERROR: dict create read-back failed.\n");
    return false;
  }

  if (!WriteScriptBytes(type, scriptName, script2.c_str()) ||
      !WriteResourceBytes(1, resourceName, resource2.c_str()) ||
      !WriteDictBytes(type, dictName, tableId, version, dict2.c_str())) {
    printf("[multi] ERROR: second-phase mixed update failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, scriptName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, script2)) {
    printf("[multi] ERROR: script update read-back failed.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(1, resourceName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyStringReadback(got, resource2)) {
    printf("[multi] ERROR: resource update read-back failed.\n");
    return false;
  }

  size = 0;
  if (!SafeReadDataDict(type, (WORD)tableId, (WORD)version, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyStringReadback(got, dict2)) {
    printf("[multi] ERROR: dict update read-back failed.\n");
    return false;
  }

  if (!SafeDelDataDict(type, (WORD)tableId, (WORD)version)) {
    return false;
  }

  printf("[multi] PASS\n");
  return true;
}

static bool TestRestartPersistence()
{
  printf("[restart] start persistence regression\n");
  fflush(stdout);

  const char* iniName = "DMW.INI";
  short type = 0;
  DWORD stamp = GetTickCount();
  char name[64];
  wsprintfA(name, "__HARNESS_RESTART_%lu", (unsigned long) (stamp % 100000));

  const char* payloadV1 = "RESTART_PAYLOAD_V1";
  const char* payloadV2 = "RESTART_PAYLOAD_V2_WITH_LONGER_CONTENT";

  if (!WriteScriptBytes(type, name, payloadV1)) {
    printf("[restart] ERROR: create failed.\n");
    return false;
  }

  ShutdownHarnessForRestart();
  if (!InitHarness(iniName)) {
    printf("[restart] ERROR: re-init failed after shutdown.\n");
    return false;
  }

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(type, name, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV1)) {
    printf("[restart] ERROR: read-back after restart did not match the persisted payload.\n");
    return false;
  }

  if (!WriteScriptBytes(type, name, payloadV2)) {
    printf("[restart] ERROR: update before second restart failed.\n");
    return false;
  }

  ShutdownHarnessForRestart();
  if (!InitHarness(iniName)) {
    printf("[restart] ERROR: second re-init failed.\n");
    return false;
  }

  size = 0;
  h = ReadScriptData(type, name, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, payloadV2)) {
    printf("[restart] ERROR: updated payload missing after second restart.\n");
    return false;
  }

  printf("[restart] PASS\n");
  return true;
}

static bool TestCrossProcessWrite()
{
  printf("[xproc-write] start producer phase\n");
  fflush(stdout);

  const short scriptType = 0;
  const short resourceType = 1;
  const short dictType = 0;
  const short dictTableId = 32321;
  const short dictVersion = 1;

  const char* scriptName = "__HARNESS_XPROC_SCRIPT";
  const char* resourceName = "__HARNESS_XPROC_RESOURCE";
  const char* dictName = "__HARNESS_XPROC_DICT";

  const char* scriptPayload = "XPROC_SCRIPT_PAYLOAD_V1";
  const char* resourcePayload = "XPROC_RESOURCE_PAYLOAD_V1";
  const char* dictPayload = "XPROC_DICT_PAYLOAD_V1";

  if (!WriteScriptBytes(scriptType, scriptName, scriptPayload)) {
    printf("[xproc-write] ERROR: script write failed.\n");
    return false;
  }
  if (!WriteResourceBytes(resourceType, resourceName, resourcePayload)) {
    printf("[xproc-write] ERROR: resource write failed.\n");
    return false;
  }
  if (!WriteDictBytes(dictType, dictName, dictTableId, dictVersion, dictPayload)) {
    printf("[xproc-write] ERROR: dict write failed.\n");
    return false;
  }

  printf("[xproc-write] PASS\n");
  return true;
}

static bool TestCrossProcessRead()
{
  printf("[xproc-read] start consumer phase\n");
  fflush(stdout);

  const short scriptType = 0;
  const short resourceType = 1;
  const short dictType = 0;
  const short dictTableId = 32321;
  const short dictVersion = 1;

  const char* scriptName = "__HARNESS_XPROC_SCRIPT";
  const char* resourceName = "__HARNESS_XPROC_RESOURCE";
  const char* dictPayload = "XPROC_DICT_PAYLOAD_V1";
  const char* scriptPayload = "XPROC_SCRIPT_PAYLOAD_V1";
  const char* resourcePayload = "XPROC_RESOURCE_PAYLOAD_V1";

  DWORD size = 0;
  GLOBALHANDLE h = ReadScriptData(scriptType, (LPSTR) scriptName, &size);
  std::vector<unsigned char> got;
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, scriptPayload)) {
    printf("[xproc-read] ERROR: script read-back mismatch.\n");
    return false;
  }

  size = 0;
  h = ReadResourceData(resourceType, (LPSTR) resourceName, &size);
  got.clear();
  if (!ReadBlobToVector(h, size, got) || !VerifyBytes(got, resourcePayload)) {
    printf("[xproc-read] ERROR: resource read-back mismatch.\n");
    return false;
  }

  size = 0;
  GLOBALHANDLE hDict = NULL;
  if (!SafeReadDataDict(dictType, (WORD) dictTableId, (WORD) dictVersion, &hDict, &size)) {
    return false;
  }
  got.clear();
  if (!ReadBlobToVector(hDict, size, got) || !VerifyBytes(got, dictPayload)) {
    printf("[xproc-read] ERROR: dict read-back mismatch.\n");
    return false;
  }

  printf("[xproc-read] PASS\n");
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
    ok = TestScriptDB() && TestResourceDB() && TestDataDict() &&
         TestScriptDBRealistic() && TestResourceDBRealistic() && TestDataDictRealistic() &&
         TestScriptDBStressLoop() && TestResourceDBStressLoop() && TestDataDictStressLoop() &&
         TestMixedWorkload() && TestSameKeyReuse() && TestMultiTableSequentialMix() &&
         TestRestartPersistence();
  } else if (_stricmp(mode, "xproc-write") == 0) {
    ok = TestCrossProcessWrite();
  } else if (_stricmp(mode, "xproc-read") == 0) {
    ok = TestCrossProcessRead();
  } else {
    PrintUsage(argv[0]);
    ShutdownHarness();
    return 1;
  }

  ShutdownHarness();
  return ok ? 0 : 3;
}
