//---------------------------------------------------------------------------
//
//  Resourcenverwaltung mit sequentiellen Files
//  $Header:   F:/marille/clinicum/ddsseq/rev/opseq.cpv   1.17   17 May 2000 17:26:50   Hannes  $
//  $Log:   F:/marille/clinicum/ddsseq/rev/opseq.cpv  $
// 
//    Rev 1.17   17 May 2000 17:26:50   Hannes
// Protokollierung auch der SEQ - Zugriffe
// 
//    Rev 1.16   22 Jan 1999 10:57:52   Martin
// einfache Liste eingebaut (DBCALLTYPE_GETLIST)
// 
//    Rev 1.15   13 Jun 1998 17:26:34   Martin
// ExePath
// 
//    Rev 1.14   07 Apr 1998 19:52:36   Hannes
// DictDB eingebaut
// 
//    Rev 1.13   15 Dec 1997 17:57:04   Hannes
// Restriktionsscript
// 
//    Rev 1.12   05 Dec 1997 17:47:26   Hannes
// 
//    Rev 1.11   21 Apr 1997 17:04:38   Hannes
// Implementierung des Zugriffes "Type = %1 AND fName = %2" in rsseq.dll
// 
//    Rev 1.10   10 Feb 1997 12:50:48   martin
// zusaetzliche diagnostische Ausgaben beim SEEK - error
// 
//    Rev 1.9   15 Jan 1997 14:39:04   HANNES
// WIN_ASSERT
// 
//    Rev 1.8   10 Jan 1997 17:03:26   MARTIN
// Format des SEEK-errors verbessert
// 
//    Rev 1.7   10 Jan 1997 16:07:50   HANNES
// 
//    Rev 1.6   10 Jan 1997 15:32:02   HANNES
// Besser Formatierung
// 
//    Rev 1.5   20 Dec 1996 21:33:02   MARTIN
// DBCALLTYPE_CREATE und DBCALLTYPE_TEST rudimentaer implementiert
// 
//    Rev 1.4   02 Dec 1996 14:49:50   MARTIN
// path[PATHBUFFERSIZE] statt [128]
// 
//    Rev 1.3   27 Nov 1996 09:00:30   HANNES
// 
//    Rev 1.2   26 Nov 1996 09:53:06   GERHOLD
// Umstellung auf 32 Bit
// 
//    Rev 1.1   08 Sep 1996 12:48:54   HANNES
// 
//    Rev 1.0   08 Sep 1996 12:38:38   HANNES
// Initial revision.
//
//---------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "stdlib.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 167
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#include "compile.hpp"

BOOL DoLog(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL doLog;
  static BOOL ScrollLockOnly;
  static BOOL LogSeqAccess;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("DataBase","DoLog", "no", buf, sizeof(buf),GetIniName());
    doLog = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","ScrollLockOnly", "no", buf, sizeof(buf),GetIniName());
    ScrollLockOnly = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","LogSeqAccess", "no", buf, sizeof(buf),GetIniName());
    LogSeqAccess = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE ;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog || LogSeqAccess;
  }

static BOOL SeqLoggingEnabled(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL enabled = FALSE;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("DataBase","LogSeqAccess", "no", buf, sizeof(buf),GetIniName());
    enabled = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE;
    }
  return enabled;
  }

extern DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name);
extern DLLExport LPSTR _export WINAPI GetExePath (void);
static char OraCmdsName[128];
static DWORD lastT;
void LogCmd (LPSTR txt,LPSTR Table,DWORD startT,DWORD endT,LPSTR ParamString)
  {
  OFSTRUCT Of;
  if (*OraCmdsName == '\0')
    lstrcpy(OraCmdsName,GetStationLogFile ("seqcmds.log"));
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    f = OpenFile (OraCmdsName,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        }
      else {
        f = OpenFile (OraCmdsName,&Of,OF_CREATE);
        _lclose(f);
        }
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    char timestr[32];
    // ltoarechts(time,timestr);
    wsprintf (timestr,"(Pause: %5ld) [%8ld - %8ld (= %5ld)] - ",startT - lastT,startT,endT,endT - startT);
    lastT = endT;
    _lwrite (f,timestr,lstrlen(timestr));
    _lwrite (f,txt,lstrlen(txt));
    _lwrite (f,txt,lstrlen(Table));
    if (ParamString != NULL) {
      _lwrite (f," (",2);
      _lwrite (f,ParamString,lstrlen(ParamString));
      _lwrite (f,")\r\n\r\n",5);
      }
    else
      _lwrite (f,"\r\n\r\n",4);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

static void SeqTrace (LPSTR tag,LPSTR fileName,LONG pos,LONG len,LPSTR detail)
  {
  if (!SeqLoggingEnabled())
    return;

  char fullExePath[MAX_PATH];
  char path[512];
  char baseName[MAX_PATH];
  DWORD n = GetModuleFileName (NULL,fullExePath,sizeof(fullExePath));
  if (n == 0 || n >= sizeof(fullExePath))
    lstrcpy (fullExePath,GetExePath());
  char *slash = strrchr (fullExePath,'\\');
  if (slash == NULL) {
    lstrcpy (path,GetExePath());
    lstrcpy (baseName,"ddsseq_trace.log");
    }
  else {
    int dirLen = int (slash - fullExePath);
    lstrncpy (path,fullExePath,dirLen);
    path[dirLen] = '\0';
    lstrcpy (baseName,slash + 1);
    char *dot = strrchr (baseName,'.');
    if (dot != NULL)
      *dot = '\0';
    }
  int n2 = lstrlen(path);
  if (n2 > 0 && path[n2 - 1] != '\\')
    path[n2++] = '\\';
  char fileNameOnly[256];
  wsprintf (fileNameOnly,"%s_ddsseq_trace.log",baseName);
  lstrcpy (path + n2,fileNameOnly);

  FILE *f = fopen (path,"a");
  if (f != NULL) {
    fprintf (f,"[%s] file=%s pos=%ld len=%ld",tag,fileName,pos,len);
    if (detail != NULL && *detail != '\0')
      fprintf (f," %s",detail);
    fprintf (f,"\n");
    fclose (f);
    }
  }

static void AppendTracePart (LPSTR dest,int destSize,LPSTR part)
  {
  if ((dest == NULL) || (part == NULL) || (destSize <= 1))
    return;
  int len = lstrlen(dest);
  if (len >= (destSize - 1))
    return;
  lstrcpyn (dest + len,part,destSize - len);
  }

LPSTR PushParam (LPSTR old,LPVOID data,short dt)
  {
  char actString[256];
  FormatOutTxt (actString,data,dt);
  int l = lstrlen (actString);
  LPSTR res;
  if (old != NULL) {
    // Den neuen String nach vorne, da die Strings verkehrt herum aufgebaut werden
    res = LPSTR (GetGlobMem (GetBlockSize (old) + l + 1));
    lmemcpy (res,actString,l);
    res[l] = ',' ;
    lmemcpy (res + l + 1,old,GetBlockSize(old));
    FreeGlobMem (old);
    }
  else {
    res = LPSTR (GetGlobMem (l + 1));
    lmemcpy (res,actString,l);
    }
  return res;
  }
static BOOL GetWordVarFromRecordByName (LPDBRECORD rec,LPTABLEDEF td,LPSTR varName,WORD FAR *out)
  {
  if ((rec == NULL) || (td == NULL) || (varName == NULL) || (out == NULL))
    return FALSE;
  BOOL found;
  WORD dt;
  WORD varNum = td->GetVarID (varName,&dt,&found);
  if (!found)
    return FALSE;
  LPVOID d = rec->Get(varNum);
  if ((d == NULL) || (GetBlockSize(d) < sizeof(WORD)))
    return FALSE;
  *out = *((WORD FAR *) d);
  return TRUE;
  }
extern DLLExport LPSTR _export WINAPI GetExePath (void);
extern LPSTR _export WINAPI GetIniName ();
#define PATHBUFFERSIZE  256
struct FAR SeqRDesc {
  LONG dbPos;
  LONG dbLen;
  };
struct FAR KHDef {
  LPSTR TestWhereStatement;
  int AnzKeySegs;
  LPSTR FAR *KeySeg;
  hash FAR *keyHash;
  };
typedef SeqRDesc FAR *LPSEQRDESC ;
DWORD GetNextSeqAutoId ();
class FAR SeqFile {
 public :
  HFILE hfile;
  LPSTR FileName;
  int AnzHashs ;
  KHDef FAR *k;
  HFILE hfileCopy;
  char WriteOrigin[256];
  BOOL KeyStateDirty;

  void GetInsertRecord (LPDBRECORD old,LPTABLEDEF td,RecBuffer FAR *res)
    {
    // Keine Manipulation am RecBuffer:
    // der Aufrufer (z.B. Out in RESSQL) verwendet rb.act nach DBCall noch.
    }
  LPDBRECORD CreateRecord (LPVOID Buffer,LPTABLEDEF td)
    {
    LPDBRECORD rec = new DBRecord (td);
    LPWORD lpav = LPWORD (Buffer);
    LPWORD ptr = lpav + 1;
    for (int i = 0 ; i < int (*lpav) ; i++) {
      WORD varNr = *ptr ;
      ptr ++ ;
      if (varNr >= WORD(td->GetAnzVars())) {
        char t1[256];
        wsprintf (t1,"CreateRecord invalid varNr=%u for table=%s (AnzVars=%d)",UINT(varNr),td->GetName(),td->GetAnzVars());
        WIN_ASSERT_TEXT (FALSE,t1);
        delete rec;
        return NULL;
        }
      LPVARDEF v = td->GetVarDef(varNr);
      if (v->mType == VAR_BLOB) {
        LPDWORD lpblobSize = LPDWORD (ptr);
        BlobDesc d ;
        d.Size = *lpblobSize ;
        d.hGmem = GlobalAlloc (GMEM_MOVEABLE,*lpblobSize);
        LPVOID Buffer = GlobalLock (d.hGmem);
        hmemcpy (Buffer,lpblobSize + 1,*lpblobSize);
        rec->Initialize (varNr,&d,sizeof(d));
        ptr = LPWORD ((char huge *) (lpblobSize + 1) + *lpblobSize) ;
        GlobalUnlock (d.hGmem);
        }
      else {
        rec->Initialize (varNr,ptr + 1,*ptr);
        ptr = LPWORD(LPSTR(ptr + 1) + *ptr) ;
        }
      }
    return rec ;
    }
  GLOBALHANDLE PushToRes (GLOBALHANDLE hG,LPVOID Data,DWORD DataSize,LONG FAR *l)
    {
    LONG nSize = *l + LONG (DataSize) ;
    hG = GlobalReAlloc (hG,nSize,GMEM_MOVEABLE);
    char huge *buffer = (char huge *)GlobalLock (hG);
    hmemcpy (buffer + *l,Data,DataSize);
    *l = nSize ;
    GlobalUnlock (hG);

    return hG ;
    }
  GLOBALHANDLE InitializeRes (LONG FAR *l)
    {
    GLOBALHANDLE hGRes = GlobalAlloc (GMEM_MOVEABLE,sizeof(WORD));
    LPWORD i = LPWORD (GlobalLock (hGRes));
    *i = 0;
    GlobalUnlock (hGRes);
    *l = sizeof(WORD);
    return hGRes;
    }
  void IncAnzVars (GLOBALHANDLE hGRes)
    {
    LPWORD i = LPWORD (GlobalLock (hGRes));
    *i = *i + 1;
    GlobalUnlock (hGRes);
    }
  GLOBALHANDLE CreateBlock (LPDBRECORD rec,LONG FAR *length,RecBuffer FAR *res)
    {
    WORD varInd;
    LPTABLEDEF td = rec->GetTableDef (0,&varInd);
    GLOBALHANDLE hGRes = InitializeRes(length);
    for (int i = 0 ; i < td->GetAnzVars() ; i++) {
      LPVOID Data = rec->Get(i);
      if (Data != NULL) {
        hGRes = PushToRes (hGRes,&i,sizeof(WORD),length);
        LPVARDEF v = td->GetVarDef(i);
        if (v->mType == VAR_BLOB) {
          LPBLOBDESC d = LPBLOBDESC(Data);
          hGRes = PushToRes (hGRes,&d->Size,sizeof(DWORD),length);
          hGRes = PushToRes (hGRes,GlobalLock (d->hGmem),d->Size,length);
          GlobalUnlock (d->hGmem);
          }
        else {
          WORD Size = GetBlockSize(Data);
          hGRes = PushToRes (hGRes,&Size,sizeof(WORD),length);
          hGRes = PushToRes (hGRes,Data,GetBlockSize(Data),length);
          }
        IncAnzVars (hGRes);
        }
      }

    GetInsertRecord (rec,td,res);

    return hGRes ;
    }
  LPSTR GetFullPath(LPSTR buffer)
    {
    GetPrivateProfileString ("DataBase","SeqPath","",buffer,PATHBUFFERSIZE - 13,GetIniName ());
    // default: im EXE-Pfad suchen
    if (!*buffer)
      lstrcpy(buffer,GetExePath());
    lstrcat (buffer,FileName);
    lstrcat (buffer,".seq");
    return buffer;
    }
  LONG dbPos ()
    {
    return _llseek (hfile,0L,SEEK_END);
    }
  void SetWriteOrigin (LPSTR txt)
    {
    if (txt == NULL || *txt == '\0') {
      WriteOrigin[0] = '\0';
      return;
      }
    lstrcpyn (WriteOrigin,txt,sizeof(WriteOrigin));
    }
  void ClearWriteOrigin ()
    {
    WriteOrigin[0] = '\0';
    }
  LONG Write (LPVOID buffer,LONG length)
    {
    BOOL isKeyStateWrite = FALSE;
    if (WriteOrigin[0] != '\0') {
      LPSTR prefix = "origin=key-state";
      int pi = 0;
      while (prefix[pi] != '\0' && WriteOrigin[pi] != '\0' && WriteOrigin[pi] == prefix[pi])
        pi++;
      isKeyStateWrite = (prefix[pi] == '\0');
      }
    LPSTR traceTag = isKeyStateWrite ? LPSTR("KEYSTATE") : LPSTR("WRITE");
    LONG res = dbPos();
    if ((buffer == NULL) || (length <= 0)) {
      SeqTrace (traceTag,FileName,res,length,"invalid-write");
      WIN_ASSERT (FALSE);
      return -1L;
      }
    char beginDetail[320];
    if (WriteOrigin[0] != '\0')
      wsprintf (beginDetail,"begin %s",WriteOrigin);
    else
      lstrcpy (beginDetail,"begin");
    SeqTrace (traceTag,FileName,res,length,beginDetail);

    LONG totalWritten = 0;
    char FAR *p = (char FAR *) buffer;
    while (totalWritten < length) {
      LONG chunk = length - totalWritten;
      if (chunk > 32000L)
        chunk = 32000L;
#ifdef WIN32
      LONG lWritten = _hwrite (hfile,p + totalWritten,UINT(chunk));
#else
      LONG lWritten = _hwrite (hfile,p + totalWritten,UINT(chunk));
#endif
      if (lWritten <= 0) {
        SeqTrace (traceTag,FileName,res,totalWritten,"partial-write-failed");
        WIN_ASSERT (FALSE);
        return -1L;
        }
      totalWritten += lWritten;
      }
    char detail[320];
    if (WriteOrigin[0] != '\0')
      wsprintf (detail,"append %s",WriteOrigin);
    else
      lstrcpy (detail,"append");
    SeqTrace (traceTag,FileName,res,totalWritten,detail);
    if (totalWritten != length) {
      WIN_ASSERT (FALSE);
      return -1L;
      }
    return res;
    }
  LPVOID PushToKeyBuffer (LPVOID oldBuffer,LPVOID Data)
    {
    int s2 = GetBlockSize (Data);
    if (s2 > 0) {
      int s1 = GetBlockSize (oldBuffer);
      LPVOID newBuffer = GetGlobMem (s1 + s2);
      if (s1 > 0) {
        lmemcpy (newBuffer,oldBuffer,s1);
        FreeGlobMem (oldBuffer);
        }
      lmemcpy (LPSTR (newBuffer) + s1,Data,s2);
      return newBuffer ;
      }
    else
      return oldBuffer ;
    }
  LPVOID BuildKeyBuffer (int kn,LPDBRECORD rec)
    {
    WORD varInd;
    LPTABLEDEF td = rec->GetTableDef (0,&varInd);
    LPVOID KeyBuffer = NULL;
    for (int i = 0 ; i < k[kn].AnzKeySegs ; i++)
      for (int j = 0 ; j < td->GetAnzVars () ; j ++)
        if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[i]) == 0)
          KeyBuffer = PushToKeyBuffer (KeyBuffer,rec->Get(j));
    return KeyBuffer;
    }
  void BuildWriteOriginFromRecord (int kn,LPDBRECORD rec,LPSTR opName)
    {
    char detail[512];
    detail[0] = '\0';
    if (opName != NULL && *opName != '\0') {
      lstrcpy (detail,opName);
      lstrcat (detail," ");
      }
    lstrcat (detail,"key=");
    char keyNum[24];
    wsprintf (keyNum,"%d",kn);
    lstrcat (detail,keyNum);
    if (rec != NULL) {
      WORD debugVarId = 0;
      LPTABLEDEF td = rec->GetTableDef (0,&debugVarId);
      if (td != NULL) {
        for (int i = 0 ; i < k[kn].AnzKeySegs ; i++) {
          for (int j = 0 ; j < td->GetAnzVars () ; j++) {
            if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[i]) == 0) {
              LPVOID data = rec->Get(j);
              if (data != NULL) {
                char part[96];
                FormatOutTxt (part,data,td->GetVarDef(j)->mType);
                lstrcat (detail," ");
                lstrcat (detail,td->GetVarDef(j)->GetName());
                lstrcat (detail,"=");
                lstrcat (detail,part);
                }
              break;
              }
            }
          }
        if (lstrcmp (FileName,"DataDict") == 0) {
          for (int j = 0 ; j < td->GetAnzVars () ; j++) {
            if (lstrcmp (td->GetVarDef(j)->GetName(),"Name") == 0) {
              LPVOID data = rec->Get(j);
              if (data != NULL) {
                char part[128];
                FormatOutTxt (part,data,td->GetVarDef(j)->mType);
                if (*part != '\0') {
                  lstrcat (detail," ");
                  lstrcat (detail,"Name=");
                  lstrcat (detail,part);
                  }
                }
              break;
              }
            }
          }
        }
      }
    SetWriteOrigin (detail);
    }
  BOOL RecordMatchesKeyParams (int kn,LPDBRECORD rec,LPVOID FAR *p)
    {
    if (rec == NULL)
      return FALSE;
    WORD varInd;
    LPTABLEDEF td = rec->GetTableDef (0,&varInd);
    if (td == NULL)
      return FALSE;
    for (int seg = 0 ; seg < k[kn].AnzKeySegs ; seg++) {
      LPVOID recData = NULL;
      for (int j = 0 ; j < td->GetAnzVars() ; j++) {
        if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[seg]) == 0) {
          recData = rec->Get(j);
          break;
          }
        }
      LPVOID reqData = p[seg + 2];
      if ((recData == NULL) || (reqData == NULL))
        return FALSE;
      WORD recSize = GetBlockSize (recData);
      WORD reqSize = GetBlockSize (reqData);
      if ((recSize == 0) || (recSize != reqSize) || (!lmemcmp (recData,reqData,recSize)))
        return FALSE;
      }
    return TRUE;
    }
  void TraceKeyDetail (int kn,LPDBRECORD rec,LONG Pos,LONG recSize)
    {
    char detail[256];
    detail[0] = '\0';
    if (rec != NULL) {
      WORD debugVarId = 0;
      LPTABLEDEF td = rec->GetTableDef (0,&debugVarId);
      if (td != NULL) {
        char part[128];
        int first = TRUE;
        for (int i = 0 ; i < k[kn].AnzKeySegs ; i++) {
          for (int j = 0 ; j < td->GetAnzVars () ; j++) {
            if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[i]) == 0) {
              LPVOID data = rec->Get(j);
              if (data != NULL) {
                FormatOutTxt (part,data,td->GetVarDef(j)->mType);
                if (!first)
                  lstrcat (detail,", ");
                first = FALSE;
                lstrcat (detail,td->GetVarDef(j)->GetName());
                lstrcat (detail,"=");
                lstrcat (detail,part);
              }
              break;
            }
          }
        }
      }
    }
    if (*detail == '\0')
      wsprintf (detail,"key=%d pos=%ld len=%ld",kn,Pos,recSize);
    SeqTrace ("KEY",FileName,Pos,recSize,detail);
    }
  BOOL ReadWordField (LPDBRECORD rec,int varNum,WORD FAR *out)
    {
    if ((rec == NULL) || (out == NULL))
      return FALSE;
    LPVOID d = rec->Get(varNum);
    if ((d == NULL) || (GetBlockSize(d) < sizeof(WORD)))
      return FALSE;
    *out = *((WORD FAR *) d);
    return TRUE;
    }
  BOOL ReadWordFieldByName (LPDBRECORD rec,LPTABLEDEF td,LPSTR varName,WORD FAR *out)
    {
    if ((rec == NULL) || (td == NULL) || (varName == NULL) || (out == NULL))
      return FALSE;
    BOOL found;
    WORD dt;
    WORD varNum = td->GetVarID (varName,&dt,&found);
    if (!found)
      return FALSE;
    return ReadWordField (rec,varNum,out);
    }
  LPSTR ReadStrFieldByName (LPDBRECORD rec,LPTABLEDEF td,LPSTR varName)
    {
    if ((rec == NULL) || (td == NULL) || (varName == NULL))
      return NULL;
    BOOL found;
    WORD dt;
    WORD varNum = td->GetVarID (varName,&dt,&found);
    if (!found)
      return NULL;
    return LPSTR(rec->Get(varNum));
    }
  LPDBRECORD LoadRecordBySeqDesc (LPSEQRDESC ss,LPTABLEDEF td)
    {
    if ((ss == NULL) || (td == NULL))
      return NULL;
    LONG nPos = _llseek (hfile,ss->dbPos,SEEK_SET);
    if (nPos != ss->dbPos) {
      char t1[256];
      wsprintf (t1,"Fehler beim SEEK: Offset = <%ld>, Size = <%ld>, errno = <%d>, doserrno = <%d>, nPos = <%ld>, hfile = <%d>, hfileCopy = <%d>",ss->dbPos,ss->dbLen,errno,_doserrno,nPos,hfile,hfileCopy);
      WIN_ASSERT_TEXT (FALSE,t1);
      return NULL;
      }
    GLOBALHANDLE hGBuffer = GlobalAlloc (GMEM_MOVEABLE,ss->dbLen);
    if (hGBuffer == NULL)
      return NULL;
    LPVOID Buffer = LPVOID (GlobalLock (hGBuffer));
    if (Buffer == NULL) {
      GlobalFree (hGBuffer);
      return NULL;
      }
    if (_hread (hfile,Buffer,ss->dbLen) != ss->dbLen) {
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);
      WIN_ASSERT (FALSE);
      return NULL;
      }
    LPDBRECORD rec = CreateRecord (Buffer,td);
    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);
    return rec;
    }
  LPTABLEDEF CreateDataDictScanTable ()
    {
    static LPSTR qn [] = { "Nummer" , "Type" , "Name" , "TableID" , "Version" , "ParentID" , "ParentVersion" , "Data" } ;
    static LPSTR qt [] = { "DataDict" } ;
    return GetTableAdmin()->GetTemporaryTable (sizeof(qn) / sizeof(*qn),qn,1,qt);
    }
  LPDBRECORD ProjectRecordToTable (LPDBRECORD src,LPTABLEDEF srcTd,LPTABLEDEF dstTd)
    {
    if ((src == NULL) || (srcTd == NULL) || (dstTd == NULL))
      return NULL;
    LPDBRECORD dst = new DBRecord (dstTd);
    if (dst == NULL)
      return NULL;
    for (int i = 0 ; i < dstTd->GetAnzVars() ; i++) {
      LPVARDEF v = dstTd->GetVarDef(i);
      if (v == NULL)
        continue;
      BOOL found;
      WORD dt;
      WORD srcVar = srcTd->GetVarID (v->GetName(),&dt,&found);
      if (!found)
        continue;
      LPVOID d = src->Get(srcVar);
      if (d == NULL)
        continue;
      dst->Set (WORD(i),d,WORD(GetBlockSize(d)));
      }
    return dst;
    }
  LPDBRECORD GetDataDictByTypeAndName (short type,LPSTR name,LPTABLEDEF dstTd)
    {
    Open();
    LPTABLEDEF scanTd = CreateDataDictScanTable ();
    if (scanTd == NULL)
      return NULL;
    hash *ht = k[0].keyHash;
    if ((ht == NULL) || (ht->Type != VOIDKEY)) {
      GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
      return NULL;
      }
    LPDBRECORD best = NULL;
    WORD bestTableId = 0;
    WORD bestVersion = 0;
    for (int bi = 0 ; bi < int(ht->hash_dimension) ; bi++) {
      for (LPhash_entry e = ht->Table + bi ; e != NULL ; e = e->Next) {
        if (ht->is_empty (e))
          continue;
        LPSEQRDESC ss = LPSEQRDESC (ht->DataPtr(e));
        LPDBRECORD rec = LoadRecordBySeqDesc (ss,scanTd);
        if (rec == NULL)
          continue;
        WORD recType;
        if (!ReadWordFieldByName (rec,scanTd,"Type",&recType) || (recType != WORD(type))) {
          delete rec;
          continue;
          }
        LPSTR pName = ReadStrFieldByName (rec,scanTd,"Name");
        if ((pName == NULL) || (lstrcmp (pName,name) != 0)) {
          delete rec;
          continue;
          }
        WORD recId = 0;
        WORD recVersion = 0;
        ReadWordFieldByName (rec,scanTd,"TableID",&recId);
        ReadWordFieldByName (rec,scanTd,"Version",&recVersion);
        if ((best == NULL) ||
            (recId > bestTableId) ||
            ((recId == bestTableId) && (recVersion > bestVersion))) {
          if (best != NULL)
            delete best;
          best = rec;
          bestTableId = recId;
          bestVersion = recVersion;
          }
        else
          delete rec;
        }
      }
    LPDBRECORD out = ProjectRecordToTable (best,scanTd,dstTd);
    if (best != NULL)
      delete best;
    GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
    return out;
    }
  LPDBRECORD GetDataDictMaxTableIdBelow (short type,WORD idMax,LPTABLEDEF dstTd)
    {
    Open();
    LPTABLEDEF scanTd = CreateDataDictScanTable ();
    if (scanTd == NULL)
      return NULL;
    hash *ht = k[0].keyHash;
    if ((ht == NULL) || (ht->Type != VOIDKEY)) {
      GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
      return NULL;
      }
    LPDBRECORD best = NULL;
    WORD bestId = 0;
    for (int bi = 0 ; bi < int(ht->hash_dimension) ; bi++) {
      for (LPhash_entry e = ht->Table + bi ; e != NULL ; e = e->Next) {
        if (ht->is_empty (e))
          continue;
        LPSEQRDESC ss = LPSEQRDESC (ht->DataPtr(e));
        LPDBRECORD rec = LoadRecordBySeqDesc (ss,scanTd);
        if (rec == NULL)
          continue;
        WORD recType, recId;
        if ((!ReadWordFieldByName (rec,scanTd,"Type",&recType)) ||
            (!ReadWordFieldByName (rec,scanTd,"TableID",&recId)) ||
            (recType != WORD(type)) ||
            (recId >= idMax)) {
          delete rec;
          continue;
          }
        if ((best == NULL) || (recId > bestId)) {
          if (best != NULL)
            delete best;
          best = rec;
          bestId = recId;
          }
        else
          delete rec;
        }
      }
    LPDBRECORD out = ProjectRecordToTable (best,scanTd,dstTd);
    if (best != NULL)
      delete best;
    GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
    return out;
    }
  LPDBRECORD GetDataDictMaxVersionBelow (short type,WORD tableId,WORD maxVersion,LPTABLEDEF dstTd)
    {
    Open();
    LPTABLEDEF scanTd = CreateDataDictScanTable ();
    if (scanTd == NULL)
      return NULL;
    hash *ht = k[0].keyHash;
    if ((ht == NULL) || (ht->Type != VOIDKEY)) {
      GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
      return NULL;
      }
    LPDBRECORD best = NULL;
    WORD bestVersion = 0;
    for (int bi = 0 ; bi < int(ht->hash_dimension) ; bi++) {
      for (LPhash_entry e = ht->Table + bi ; e != NULL ; e = e->Next) {
        if (ht->is_empty (e))
          continue;
        LPSEQRDESC ss = LPSEQRDESC (ht->DataPtr(e));
        LPDBRECORD rec = LoadRecordBySeqDesc (ss,scanTd);
        if (rec == NULL)
          continue;
        WORD recType, recId, recVersion;
        if ((!ReadWordFieldByName (rec,scanTd,"Type",&recType)) ||
            (!ReadWordFieldByName (rec,scanTd,"TableID",&recId)) ||
            (!ReadWordFieldByName (rec,scanTd,"Version",&recVersion)) ||
            (recType != WORD(type)) ||
            (recId != tableId) ||
            (recVersion >= maxVersion)) {
          delete rec;
          continue;
          }
        if ((best == NULL) || (recVersion > bestVersion)) {
          if (best != NULL)
            delete best;
          best = rec;
          bestVersion = recVersion;
          }
        else
          delete rec;
        }
      }
    LPDBRECORD out = ProjectRecordToTable (best,scanTd,dstTd);
    if (best != NULL)
      delete best;
    GetTableAdmin()->FreeTable (scanTd->GetTableID(),scanTd->GetVersion());
    return out;
    }
  void AddToKey (int kn,LPDBRECORD rec,LONG Pos,LONG recSize)
    {
    LPVOID KeyBuffer = BuildKeyBuffer(kn,rec);
    if (KeyBuffer == NULL)
      return;
    WORD keySize = GetBlockSize (KeyBuffer);
    if (keySize <= 0) {
      FreeGlobMem (KeyBuffer);
      return;
      }
    SeqRDesc r;
    r.dbPos = Pos ;
    r.dbLen = recSize ;
    TraceKeyDetail (kn,rec,Pos,recSize);
    k[kn].keyHash->DelDatav (KeyBuffer,keySize);
    if (!k[kn].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),keySize)) {
      SeqTrace ("KEYSTATE",FileName,Pos,recSize,"setdatav-failed-add");
      WIN_ASSERT (FALSE);
      }
    KeyStateDirty = TRUE;
    FreeGlobMem (KeyBuffer);
    }
  void DeleteKey (int kn,LPDBRECORD rec)
    {
    LPVOID KeyBuffer = BuildKeyBuffer(kn,rec);
    if (KeyBuffer != NULL) {
      k[kn].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
      KeyStateDirty = TRUE;
      }
    FreeGlobMem (KeyBuffer);
    }
  void Create ()
    {
    if (hfile == 0) {
      char path[PATHBUFFERSIZE];
      OFSTRUCT Of;
      hfile = OpenFile (GetFullPath(path),&Of,OF_CREATE);
      hfileCopy = hfile;
      WIN_ASSERT (hfile > 0);
      LONG dummy[2];    // Platz fuer die Position des KeyBlockes und
                        // die Laenge des KeyBlockes
      dummy[0] = 0L;
      dummy[1] = 0L;
      for (int i = 0 ; i < AnzHashs ; i++)
#ifdef WIN32
        WIN_ASSERT (_lwrite (hfile,LPSTR(dummy),sizeof(dummy)) == sizeof(dummy));
#else
        WIN_ASSERT (_lwrite (hfile,dummy,sizeof(dummy)) == sizeof(dummy));
#endif
      }
    }
  void Open ()
    {
    if (hfile == 0) {
      char path[PATHBUFFERSIZE];
      OFSTRUCT Of;
      hfile = OpenFile (GetFullPath(path),&Of,OF_READWRITE | OF_SHARE_COMPAT);
      if (hfile <= 0)
        hfile = OpenFile (GetFullPath(path),&Of,OF_READ | OF_SHARE_COMPAT);
      if (hfile <= 0) {
        Create();
        if (hfile > 0) {
          _lclose (hfile);
          hfile = 0;
          hfileCopy = 0;
        }
        hfile = OpenFile (GetFullPath(path),&Of,OF_READWRITE | OF_SHARE_COMPAT);
        if (hfile <= 0)
          hfile = OpenFile (GetFullPath(path),&Of,OF_READ | OF_SHARE_COMPAT);
      }
      hfileCopy = hfile;
      WIN_ASSERT (hfile > 0);
      LONG keyInfo[32];
      LONG keyInfoSize = sizeof(keyInfo[0]) * AnzHashs * 2;
      WIN_ASSERT (_lread (hfile,keyInfo,keyInfoSize) == keyInfoSize);
      LONG fileEnd = _llseek (hfile,0L,SEEK_END);
      LONG minDataPos = keyInfoSize;
      BOOL keyHeaderChanged = FALSE;
      for (int i = 0 ; i < AnzHashs ; i++) {
        if (k[i].keyHash == NULL)
          k[i].keyHash = new hash (137,VOIDKEY);
        LONG keyPos = keyInfo[2 * i + 0];
        LONG keyLen = keyInfo[2 * i + 1];
        if ((keyPos <= 0L) || (keyLen <= 0L))
          continue;

        BOOL invalidRange = (keyPos < minDataPos) ||
                            (keyLen < LONG (2 * sizeof(WORD))) ||
                            (keyPos > fileEnd) ||
                            (keyLen > fileEnd) ||
                            (keyPos + keyLen < keyPos) ||
                            (keyPos + keyLen > fileEnd);
        if (invalidRange) {
          SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,"invalid-key-range");
          keyInfo[2 * i + 0] = 0L;
          keyInfo[2 * i + 1] = 0L;
          keyHeaderChanged = TRUE;
          continue;
          }

        if (_llseek (hfile,keyPos,SEEK_SET) != keyPos) {
          SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,"seek-failed");
          keyInfo[2 * i + 0] = 0L;
          keyInfo[2 * i + 1] = 0L;
          keyHeaderChanged = TRUE;
          continue;
          }

        GLOBALHANDLE hGKeyInfo = GlobalAlloc (GMEM_MOVEABLE,keyLen);
        if (hGKeyInfo == NULL) {
          SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,"alloc-failed");
          continue;
          }
        LPVOID keyBuf = GlobalLock (hGKeyInfo);
        if (keyBuf == NULL) {
          GlobalFree (hGKeyInfo);
          SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,"lock-failed");
          continue;
          }
        LONG nread = _hread (hfile,keyBuf,keyLen);
        GlobalUnlock (hGKeyInfo);
        if (nread != keyLen) {
          GlobalFree (hGKeyInfo);
          SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,"short-read");
          keyInfo[2 * i + 0] = 0L;
          keyInfo[2 * i + 1] = 0L;
          keyHeaderChanged = TRUE;
          continue;
          }

        k[i].keyHash->GetHugeHash (hGKeyInfo);
        char loadDetail[96];
        wsprintf (loadDetail,"loaded key=%d",i);
        SeqTrace ("KEYSTATE",FileName,keyPos,keyLen,loadDetail);
        GlobalFree (hGKeyInfo);
        }
      if (keyHeaderChanged) {
        if (_llseek (hfile,0L,SEEK_SET) == 0L) {
          _lwrite (hfile,LPSTR(keyInfo),keyInfoSize);
          _llseek (hfile,0L,SEEK_END);
          }
        }
      }
    }
  LPSTR GetName ()
    {
    return FileName ;
    }
  void FlushKeyState ()
    {
    if (hfile <= 0)
      return;
    if (!KeyStateDirty)
      return;
    for (int i = 0 ; i < AnzHashs ; i++) {
      GLOBALHANDLE hGKeyBuffer = k[i].keyHash->StoreHugeHash ();
      if (hGKeyBuffer == NULL) {
        SeqTrace ("KEYSTATE",FileName,0L,0L,"store-hugehash-failed");
        WIN_ASSERT (FALSE);
        return;
        }
      DWORD keysize = GlobalSize (hGKeyBuffer);
      char keyStateDetail[96];
      wsprintf (keyStateDetail,"origin=key-state key=%d",i);
      SetWriteOrigin (keyStateDetail);
      LONG dbKeyPos = Write (GlobalLock (hGKeyBuffer),keysize);
      ClearWriteOrigin ();
      if (dbKeyPos < 0L) {
        GlobalUnlock (hGKeyBuffer);
        GlobalFree (hGKeyBuffer);
        SeqTrace ("KEYSTATE",FileName,0,keysize,"flush-write-failed");
        return;
        }
      LONG headerPos = i * 2 * sizeof(LONG);
      if (_llseek (hfile,headerPos,SEEK_SET) != headerPos) {
        GlobalUnlock (hGKeyBuffer);
        GlobalFree (hGKeyBuffer);
        SeqTrace ("KEYSTATE",FileName,headerPos,keysize,"flush-header-seek-failed");
        WIN_ASSERT (FALSE);
        return;
        }
      LONG keyHeaderPair[2];
      keyHeaderPair[0] = dbKeyPos;
      keyHeaderPair[1] = LONG (keysize);
#ifdef WIN32
      if (_lwrite (hfile,LPSTR(keyHeaderPair),sizeof(keyHeaderPair)) != sizeof(keyHeaderPair)) {
        GlobalUnlock (hGKeyBuffer);
        GlobalFree (hGKeyBuffer);
        SeqTrace ("KEYSTATE",FileName,headerPos,keysize,"flush-header-write-failed");
        WIN_ASSERT (FALSE);
        return;
        }
#else
      if (_lwrite (hfile,keyHeaderPair,sizeof(keyHeaderPair)) != sizeof(keyHeaderPair)) {
        GlobalUnlock (hGKeyBuffer);
        GlobalFree (hGKeyBuffer);
        SeqTrace ("KEYSTATE",FileName,headerPos,keysize,"flush-header-write-failed");
        WIN_ASSERT (FALSE);
        return;
        }
#endif
      _llseek (hfile,0L,SEEK_END);
      GlobalUnlock (hGKeyBuffer);
      GlobalFree (hGKeyBuffer);
      }
    KeyStateDirty = FALSE;
    }
  void CloseFileAfterInsert ()
    {
    FlushKeyState ();
    if (hfile > 0) {
      _lclose (hfile);
      hfile = 0 ;
      }
    }
  void Insert (LPDBRECORD rec,RecBuffer FAR *res)
    {
    Create ();
    if (rec->Get(0) == NULL) {
      DWORD nwNummer = GetNextSeqAutoId();
      rec->Initialize (0,&nwNummer,sizeof(nwNummer));
      }
    LONG length ;
    GLOBALHANDLE hGBuffer = CreateBlock (rec,&length,res);
    BuildWriteOriginFromRecord (0,rec,"origin=record insert");
    LONG pos = Write (GlobalLock (hGBuffer),length);
    ClearWriteOrigin ();
    if (pos < 0L) {
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);
      WIN_ASSERT (FALSE);
      return;
      }
    for (int i = 0 ; i < AnzHashs ; i++)
      AddToKey (i,rec,pos,length);
    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);
    }
  void Update (LPDBRECORD rec,RecBuffer FAR *res)
    {
    Create ();
    LONG length ;
    GLOBALHANDLE hGBuffer = CreateBlock (rec,&length,res);
    BuildWriteOriginFromRecord (0,rec,"origin=record update");
    LONG newPos = Write (GlobalLock (hGBuffer),length);
    ClearWriteOrigin ();
    if (newPos < 0L) {
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);
      WIN_ASSERT (FALSE);
      return;
      }
    GlobalUnlock (hGBuffer);
    for (int i = 0 ; i < AnzHashs ; i++) {
      LPVOID KeyBuffer = BuildKeyBuffer (i,rec);
      if (KeyBuffer != NULL) {
        SeqRDesc r;
        r.dbPos = newPos ;
        r.dbLen = length ;
        k[i].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
        if (!k[i].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer))) {
          SeqTrace ("KEYSTATE",FileName,newPos,length,"setdatav-failed-update");
          WIN_ASSERT (FALSE);
          }
        KeyStateDirty = TRUE;
        FreeGlobMem (KeyBuffer);
        }
      }
    GlobalFree (hGBuffer);
    }
  void Delete (LPDBRECORD rec)
    {
    for (int i = 0 ; i < AnzHashs ; i++)
      DeleteKey (i,rec);
    }
  void DeleteByParams (int j,LPVOID FAR *p)
    {
    LPVOID KeyBuffer = NULL;
    for (int i = 0 ; i < k[j].AnzKeySegs ; i++)
      KeyBuffer = PushToKeyBuffer (KeyBuffer,p[i + 2]);
    if (KeyBuffer != NULL) {
      k[j].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
      KeyStateDirty = TRUE;
      }
    FreeGlobMem (KeyBuffer);
    }
  int CheckSelection (LPSTR WhereStatement)
    {
    for (int i = 0 ; i < AnzHashs ; i++) {
      if (lstrcmp (WhereStatement,k[i].TestWhereStatement) == 0) 
        return i ;
      }
    return -1;
    }
  LPDBRECORD Get (int j,LPVOID FAR *p,LPTABLEDEF td,WORD FAR *pt,LPSTR stmt)
    {
    Open ();
    LPVOID KeyBuffer = NULL ;
    DWORD tStart = GetTickCount ();
    LPSTR ParamString = NULL;
    char namedParamPreview[220];
    namedParamPreview[0] = '\0';
    for (int i = 0 ; i < k[j].AnzKeySegs ; i++) {
      KeyBuffer = PushToKeyBuffer (KeyBuffer,p[i + 2]);
      ParamString = PushParam (ParamString,p[i + 2],pt[i + 2]) ;
      char pValue[96];
      char pEntry[128];
      FormatOutTxt (pValue,p[i + 2],pt[i + 2]);
      wsprintf (pEntry,"%s=%s",k[j].KeySeg[i],pValue);
      if (*namedParamPreview != '\0')
        AppendTracePart (namedParamPreview,sizeof(namedParamPreview),", ");
      AppendTracePart (namedParamPreview,sizeof(namedParamPreview),pEntry);
      }
    char stmtPreview[120];
    if ((stmt != NULL) && (*stmt != '\0'))
      lstrcpyn (stmtPreview,stmt,sizeof(stmtPreview));
    else
      lstrcpy (stmtPreview,"<none>");
    char paramPreview[180];
    if ((ParamString != NULL) && (*ParamString != '\0'))
      lstrcpyn (paramPreview,ParamString,sizeof(paramPreview));
    else
      lstrcpy (paramPreview,"<none>");
    char lookupDetail[360];
    wsprintf (lookupDetail,"lookup key=%d where=%s params=%s keyparams=%s",j,stmtPreview,paramPreview,(*namedParamPreview != '\0') ? namedParamPreview : "<none>");
    SeqTrace ("GET",FileName,-1L,0L,lookupDetail);
    LPSEQRDESC s = LPSEQRDESC (k[j].keyHash->GetDatav (KeyBuffer,GetBlockSize(KeyBuffer)));
    FreeGlobMem (KeyBuffer);
    if (s != NULL) {
    LONG nPos = _llseek (hfile,s->dbPos,SEEK_SET);
    if (nPos != s->dbPos) {
      char testmsg[256],t1[256];
      FormatOutTxt (testmsg,KeyBuffer,VAR_OBJ);
      wsprintf (t1,"Fehler beim SEEK: Key = <%s>,Offset = <%ld>, Size = <%ld>, errno = <%d>, doserrno = <%d>, nPos = <%ld>, hfile = <%d>, hfileCopy = <%d>",LPSTR(testmsg),s->dbPos,s->dbLen,errno,_doserrno,nPos,hfile,hfileCopy);
      WIN_ASSERT_TEXT (FALSE,t1);
      }
    GLOBALHANDLE hGBuffer = GlobalAlloc (GMEM_MOVEABLE,s->dbLen);
    LPVOID Buffer = LPVOID (GlobalLock (hGBuffer));
    WIN_ASSERT (_hread (hfile,Buffer,s->dbLen) == s->dbLen);
    LPDBRECORD rec = CreateRecord (Buffer,td);
    if ((rec != NULL) && (!RecordMatchesKeyParams (j,rec,p))) {
      SeqTrace ("KEYSTATE",FileName,s->dbPos,s->dbLen,"hash-key-mismatch");
      WIN_ASSERT (FALSE);
      }
    char detail[256];
    detail[0] = '\0';
    if (rec != NULL) {
      WORD debugVarId = 0;
      LPTABLEDEF td2 = rec->GetTableDef (0,&debugVarId);
      if (td2 != NULL) {
        char part[128];
        int first = TRUE;
        for (int i = 0 ; i < k[j].AnzKeySegs ; i++) {
          for (int x = 0 ; x < td2->GetAnzVars() ; x++) {
            if (lstrcmp (td2->GetVarDef(x)->GetName(),k[j].KeySeg[i]) == 0) {
              LPVOID data = rec->Get(x);
              if (data != NULL) {
                FormatOutTxt (part,data,td2->GetVarDef(x)->mType);
                if (!first)
                  AppendTracePart (detail,sizeof(detail),", ");
                first = FALSE;
                AppendTracePart (detail,sizeof(detail),td2->GetVarDef(x)->GetName());
                AppendTracePart (detail,sizeof(detail),"=");
                AppendTracePart (detail,sizeof(detail),part);
                }
              break;
              }
            }
          }
        if (lstrcmp (FileName,"DataDict") == 0) {
          for (int nx = 0 ; nx < td2->GetAnzVars() ; nx++) {
            if (lstrcmp (td2->GetVarDef(nx)->GetName(),"Name") == 0) {
              LPVOID nData = rec->Get(nx);
              if (nData != NULL) {
                char namePart[160];
                FormatOutTxt (namePart,nData,td2->GetVarDef(nx)->mType);
                if (*namePart != '\0') {
                  if (*detail != '\0')
                    AppendTracePart (detail,sizeof(detail),", ");
                  AppendTracePart (detail,sizeof(detail),"Name=");
                  AppendTracePart (detail,sizeof(detail),namePart);
                  }
                }
              break;
              }
            }
          }
        }
      }
    if (*detail == '\0')
      wsprintf (detail,"key=%d pos=%ld len=%ld",j,s->dbPos,s->dbLen);
    SeqTrace ("GET",FileName,s->dbPos,s->dbLen,detail);
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);

      if (DoLog())
        LogCmd (stmt,td->GetName(),tStart,GetTickCount(),ParamString);

      if (ParamString) FreeGlobMem (ParamString);
      return rec;
      }
    else
      {
      char missDetail[360];
      wsprintf (missDetail,"miss key=%d where=%s params=%s keyparams=%s",j,stmtPreview,paramPreview,(*namedParamPreview != '\0') ? namedParamPreview : "<none>");
      SeqTrace ("GET",FileName,-1L,0L,missDetail);
      if (DoLog())
        LogCmd (stmt,td->GetName(),tStart,GetTickCount(),ParamString);
      if (ParamString) FreeGlobMem (ParamString);
      return NULL ;
      }
    }

  SeqFile (LPSTR fName,int ah,KHDef FAR *kd)
    {
    hfile = 0;
    hfileCopy = 0;
    KeyStateDirty = FALSE;
    FileName = fName ;
    k = kd;
    AnzHashs = ah;
    for (int i = 0 ; i < ah ; i++) {
      k[i].keyHash = new hash (137,VOIDKEY);
      }
    }

  ~SeqFile ()
    {
    if (hfile > 0) {
      FlushKeyState ();
      _lclose (hfile);
      hfile = 0;
      }
    for (int i = 0 ; i < AnzHashs ; i++) {
      if (k[i].keyHash != NULL)
        delete k[i].keyHash;
      }
    }

  LPVOID operator new (size_t size)
    {
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };


static LPSTR ScriptSegs [] = { "Type","fName" } ;
static LPSTR ResSegs1 [] = { "Nummer" } ;
static LPSTR ResSegs2 [] = { "Type","fName" } ;
static LPSTR DataDictSegs [] = { "Type","TableID","Version" } ;
static LPSTR RSSegs1 [] = { "Nummer" } ;
static LPSTR RSSegs2 [] = { "Art","Leistung" } ;
static LPSTR RSSegs3 [] = { "Art","Makro" } ;
static LPSTR DictDBSegs [] = { "Type" } ;
KHDef ScriptKey [] = {
  { 
  "Type = %1 AND fName = %2", 
  2 , 
  ScriptSegs , 
  NULL }
  } ;
KHDef ResKeys [] = {
  { "Nummer = %1", 1 , ResSegs1 , NULL } ,
  { "Type = %1 AND fName = %2", 2 , ResSegs2 , NULL }
  } ;
KHDef DDictKeys [] = {
  { "Type = %1 AND TableID = %2 AND Version = %3", 3 , DataDictSegs , NULL }
  } ;
KHDef RSKeys [] = {
  { "Nummer = %1", 1 , RSSegs1 , NULL } ,
  { "Art = %1 AND Leistung = %2", 2 , RSSegs2 , NULL } ,
  { "Art = %1 AND Makro = %2", 2 , RSSegs3 , NULL }
  } ;
KHDef DictDBKeys [] = {
  { "Type = %1" , 1, DictDBSegs , NULL }
  } ;
static struct {
  LPSTR fName ;
  int AnzHashs ;
  KHDef FAR *k;
  SeqFile FAR *sf;
  } sfDef [] = {
    { "ScriptDB" , 1, ScriptKey , NULL } ,
    { "ResDB" , 2 , ResKeys , NULL } ,
    { "DataDict" , 1 , DDictKeys , NULL } ,
    { "RestriktionsScript" , 3 , RSKeys , NULL } ,
    { "DictDB" , 1 , DictDBKeys , NULL } 
  } ;

static DWORD SeqAutoIdCounter = 0;
DWORD GetNextSeqAutoId ()
  {
  if (SeqAutoIdCounter == 0)
    SeqAutoIdCounter = GetTickCount();
  SeqAutoIdCounter++;
  if (SeqAutoIdCounter == 0)
    SeqAutoIdCounter = 1;
  return SeqAutoIdCounter;
  }

static BOOL Initialized ;
void Initialize ()
  {
  if (!Initialized) {
    for (int i = 0 ; i < sizeof(sfDef) / sizeof(sfDef[0]) ; i++)
      sfDef[i].sf = new SeqFile (sfDef[i].fName,sfDef[i].AnzHashs,sfDef[i].k);
    Initialized = TRUE ;
    }
  }

SeqFile FAR *GetSeqFile (LPTABLEDEF td)
  {
  for (int i = 0 ; i < sizeof(sfDef) / sizeof(sfDef[0]) ; i++)
    if (lstrcmp (td->GetName(),sfDef[i].sf->GetName ()) == 0)
      return sfDef[i].sf ;
  return NULL ;
  }

DLLExport int _export WINAPI DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  int state = DBCALL_ERROR ;
  SeqFile FAR *s;
  LPDBRECORD rec;
  switch (Op) {
    case DBOP_RESET :
      state = DBCALL_SUCCESS ;
      break ;
    case DBOP_ENDOFCONVERSION :
      s = GetSeqFile (req->TableDef[0]);
      WIN_ASSERT (s != NULL) ;
      s->CloseFileAfterInsert ();
      state = DBCALL_SUCCESS ;
      break ;
    default :
      Initialize ();
      if (req->Type == DBCALLTYPE_EXECUTE) {
        if ((req->SelectionName != NULL) &&
            (lstrcmp (req->SelectionName,"DELETE FROM DataDict WHERE Type = %1 AND TableID = %2 AND Version = %3") == 0)) {
          s = NULL;
          for (int si = 0 ; si < sizeof(sfDef) / sizeof(sfDef[0]) ; si++)
            if (lstrcmp (sfDef[si].fName,"DataDict") == 0)
              s = sfDef[si].sf ;
          if (s == NULL) {
            state = DBCALL_NODATA ;
            break ;
            }
          s->Open ();
          int hn = s->CheckSelection ("Type = %1 AND TableID = %2 AND Version = %3");
          if (hn < 0) {
            state = DBCALL_NODATA ;
            break ;
            }
          s->DeleteByParams (hn,req->Param);
          s->FlushKeyState ();
          state = DBCALL_ENDOFFILE ;
          }
        else
          WIN_ASSERT (FALSE);
        break ;
        }
      s = GetSeqFile (req->TableDef[0]);
      WIN_ASSERT (s != NULL) ;
      switch (req->Type) {
        case DBCALLTYPE_CREATE:
        case DBCALLTYPE_TEST:
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDINSERT :
          s->Insert (res->first->rec[0],res);
          s->FlushKeyState ();
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDUPDATE :
          s->Update (res->first->rec[0],res);
          s->FlushKeyState ();
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDDELETE :
          s->Delete (res->first->rec[0]);
          s->FlushKeyState ();
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDGET :
          {
          if (lstrcmp (s->GetName(),"DataDict") == 0) {
            if ((req->SelectionName != NULL) &&
                (lstrcmp (req->SelectionName,"Type = %1 AND Name = %2") == 0)) {
              if ((req->Param[2] == NULL) || (req->Param[3] == NULL)) {
                state = DBCALL_NODATA ;
                break ;
                }
              short type = *((short FAR *) req->Param[2]);
              LPSTR name = LPSTR(req->Param[3]);
              rec = s->GetDataDictByTypeAndName (type,name,req->TableDef[0]);
              if (rec != NULL) {
                WORD outTableId = 0;
                if (GetWordVarFromRecordByName (rec,req->TableDef[0],"TableID",&outTableId)) {
                  if (req->TableDef[0]->GetAnzVars() > 1)
                    rec->Set (1,&outTableId,sizeof(outTableId));
                  }
                res->AddLine (1,ADDLINEPOS_START);
                res->SetRes (0,rec);
                state = DBCALL_SUCCESS ;
                }
              else
                state = DBCALL_NODATA ;
              break ;
              }
            if ((req->SelectionName != NULL) &&
                (lstrcmp (req->SelectionName,"Type = %1 AND TableID = (SELECT MAX(TableID) FROM DataDict WHERE Type = %1 AND TableID < %2)") == 0)) {
              if ((req->Param[2] == NULL) || (req->Param[3] == NULL)) {
                state = DBCALL_NODATA ;
                break ;
                }
              short type = *((short FAR *) req->Param[2]);
              WORD idMax = *((WORD FAR *) req->Param[3]);
              rec = s->GetDataDictMaxTableIdBelow (type,idMax,req->TableDef[0]);
              if (rec != NULL) {
                WORD outTableId = 0;
                if (GetWordVarFromRecordByName (rec,req->TableDef[0],"TableID",&outTableId)) {
                  if (req->TableDef[0]->GetAnzVars() > 1)
                    rec->Set (1,&outTableId,sizeof(outTableId));
                  }
                res->AddLine (1,ADDLINEPOS_START);
                res->SetRes (0,rec);
                state = DBCALL_SUCCESS ;
                }
              else
                state = DBCALL_NODATA ;
              break ;
              }
            if ((req->SelectionName != NULL) &&
                (lstrcmp (req->SelectionName,"Type = %1 AND TableID = %2 AND Version = (SELECT MAX(Version) FROM DataDict WHERE Type = %1 AND TableID = %2 AND Version < %3)") == 0)) {
              if ((req->Param[2] == NULL) || (req->Param[3] == NULL) || (req->Param[4] == NULL)) {
                state = DBCALL_NODATA ;
                break ;
                }
              short type = *((short FAR *) req->Param[2]);
              WORD tableId = *((WORD FAR *) req->Param[3]);
              WORD maxVersion = *((WORD FAR *) req->Param[4]);
              rec = s->GetDataDictMaxVersionBelow (type,tableId,maxVersion,req->TableDef[0]);
              if (rec != NULL) {
                WORD outVersion = 0;
                if (GetWordVarFromRecordByName (rec,req->TableDef[0],"Version",&outVersion)) {
                  if (req->TableDef[0]->GetAnzVars() > 1)
                    rec->Set (1,&outVersion,sizeof(outVersion));
                  }
                res->AddLine (1,ADDLINEPOS_START);
                res->SetRes (0,rec);
                state = DBCALL_SUCCESS ;
                }
              else
                state = DBCALL_NODATA ;
              break ;
              }
            }
          int hn = s->CheckSelection (req->SelectionName);
          if (hn < 0) {
            char sSel[320];
            char t1[512];
            sSel[0] = '\0';
            if (req->SelectionName != NULL)
              lstrcpyn (sSel,req->SelectionName,sizeof(sSel));
            wsprintf (t1,"DDSSEQ unsupported STANDARDGET selection: file=%s, op=%d, calltype=%d, selection=%s",s->GetName(),Op,req->Type,(sSel[0] != '\0') ? sSel : "<null>");
            WIN_ASSERT_TEXT (FALSE,t1);
            state = DBCALL_NODATA ;
            break ;
            }
          rec = s->Get (hn,req->Param,req->TableDef[0],req->ParamType,req->SelectionName);
          if (rec != NULL) {
            res->AddLine (1,ADDLINEPOS_START);
            res->SetRes (0,rec);
            state = DBCALL_SUCCESS ;
            }
          else
            state = DBCALL_NODATA ;
          }
          break ;
        case DBCALLTYPE_GETLIST :
          {
          WIN_ASSERT ((req->OrderStatement != NULL) && (*req->OrderStatement == '\0'));
          s->Open();
          if ((Op == DBOP_GETFIRST) || (Op == DBOP_GETNEXT)) {
            if (Op == DBOP_GETFIRST)
              WIN_ASSERT(*hstmt == NULL);
            if (Op == DBOP_GETNEXT)
              WIN_ASSERT(*hstmt != NULL);
            LPhash_entry tosearch = (LPhash_entry)*hstmt;
            *hstmt = NULL;
            int keynum = 0;   // vorerst fix
            hash *ht = s->k[keynum].keyHash;
            WIN_ASSERT (ht->Type == VOIDKEY);
            int count = 0;
            for (int i = 0 ; i < int (ht->hash_dimension) ; i++) {
              for (LPhash_entry e = ht->Table + i ; e != NULL ; ) {
                if (!ht->is_empty (e)) {
                  if (tosearch == NULL) {
                    LPSEQRDESC ss = LPSEQRDESC (ht->DataPtr(e));
                    WIN_ASSERT (ss != NULL);
                    LONG nPos = _llseek (s->hfile,ss->dbPos,SEEK_SET);
                    if (nPos != ss->dbPos) {
                      char t1[256];
                      wsprintf (t1,"Fehler beim SEEK: Offset = <%ld>, Size = <%ld>, errno = <%d>, doserrno = <%d>, nPos = <%ld>, hfile = <%d>, hfileCopy = <%d>",ss->dbPos,ss->dbLen,errno,_doserrno,nPos,s->hfile,s->hfileCopy);
                      WIN_ASSERT_TEXT (FALSE,t1);
                      }
                    GLOBALHANDLE hGBuffer = GlobalAlloc (GMEM_MOVEABLE,ss->dbLen);
                    LPVOID Buffer = LPVOID (GlobalLock (hGBuffer));
                    WIN_ASSERT (_hread (s->hfile,Buffer,ss->dbLen) == ss->dbLen);
                    rec = s->CreateRecord (Buffer,req->TableDef[0]);
                    GlobalUnlock (hGBuffer);
                    GlobalFree (hGBuffer);
                    res->AddLine (1,ADDLINEPOS_END);
                    res->SetRes (0,rec);
                    count++;
                    if (count >= AnzLines) {
                      *hstmt = e;
                      i = int (ht->hash_dimension);
                      break;
                      }
                    }
                  else {
                    if (e == tosearch)
                      tosearch = NULL;
                    }
                  }
                e = ht->NextEnt (e);
                }
              }
            }
          else {
            WIN_ASSERT(FALSE);
            }
          if (*hstmt != NULL)
            state = DBCALL_SUCCESS ;
          else
            state = DBCALL_ENDOFFILE ;
          }
          break ;
        default :
          WIN_ASSERT (FALSE);
        }
    }
  return state ;
  }

void OnExit ()
  {
  for (int i = 0 ; i < sizeof(sfDef) / sizeof(sfDef[0]) ; i++)
    if (sfDef[i].sf != NULL) {
      sfDef[i].sf->FlushKeyState ();
      delete sfDef[i].sf ;
      sfDef[i].sf = NULL ;
      }
  Initialized = FALSE ;
  }
