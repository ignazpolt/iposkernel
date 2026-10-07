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
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("DataBase","DoLog", "no", buf, sizeof(buf),GetIniName());
    doLog = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","ScrollLockOnly", "no", buf, sizeof(buf),GetIniName());
    ScrollLockOnly = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE ;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog;
  }

extern DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name);
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
  LONG Write (LPVOID buffer,LONG length)
    {
    LONG res = dbPos();
#ifdef WIN32
    LONG lWritten = _hwrite (hfile,(LPSTR)buffer,length);
#else
    LONG lWritten = _hwrite (hfile,buffer,length);
#endif
    WIN_ASSERT (lWritten == length);
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
  void AddToKey (int kn,LPDBRECORD rec,LONG Pos,LONG recSize)
    {
    LPVOID KeyBuffer = BuildKeyBuffer(kn,rec);
    SeqRDesc r;
    r.dbPos = Pos ;
    r.dbLen = recSize ;
    // WIN_ASSERT (k[kn].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer)));
    k[kn].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer));
    FreeGlobMem (KeyBuffer);
    }
  void DeleteKey (int kn,LPDBRECORD rec)
    {
    LPVOID KeyBuffer = BuildKeyBuffer(kn,rec);
    if (KeyBuffer != NULL)
      k[kn].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
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
      WIN_ASSERT (_lread (hfile,keyInfo,sizeof(keyInfo[0]) * AnzHashs * 2) == sizeof(keyInfo[0]) * AnzHashs * 2);
      for (int i = 0 ; i < AnzHashs ; i++) {
        if ((keyInfo[2 * i + 0] <= 0L) || (keyInfo[2 * i + 1] <= 0L))
          continue;
        WIN_ASSERT (_llseek (hfile,keyInfo[2 * i + 0],SEEK_SET) == keyInfo[2 * i + 0]);
        GLOBALHANDLE hGKeyInfo = GlobalAlloc (GMEM_MOVEABLE,keyInfo[2 * i + 1]);
        WIN_ASSERT (_hread (hfile,GlobalLock (hGKeyInfo),keyInfo[2 * i + 1]) == keyInfo[2 * i + 1]);
        GlobalUnlock (hGKeyInfo);
        k[i].keyHash->GetHugeHash (hGKeyInfo);
        GlobalFree (hGKeyInfo);
        }
      }
    }
  LPSTR GetName ()
    {
    return FileName ;
    }
  void FlushKeyState ()
    {
    for (int i = 0 ; i < AnzHashs ; i++) {
      GLOBALHANDLE hGKeyBuffer = k[i].keyHash->StoreHugeHash ();
      DWORD keysize = GlobalSize (hGKeyBuffer);
      LONG dbKeyPos = Write (GlobalLock (hGKeyBuffer),keysize);
      _llseek (hfile,i * 2 * sizeof(LONG),SEEK_SET);
#ifdef WIN32
      WIN_ASSERT (_lwrite (hfile,LPSTR(&dbKeyPos),sizeof(LONG)) == sizeof(LONG));
      WIN_ASSERT (_lwrite (hfile,LPSTR(&keysize),sizeof(LONG)) == sizeof(LONG));
#else
      WIN_ASSERT (_lwrite (hfile,&dbKeyPos,sizeof(LONG)) == sizeof(LONG));
      WIN_ASSERT (_lwrite (hfile,&keysize,sizeof(LONG)) == sizeof(LONG));
#endif
      _llseek (hfile,0L,SEEK_END);
      GlobalUnlock (hGKeyBuffer);
      GlobalFree (hGKeyBuffer);
      }
    }
  void CloseFileAfterInsert ()
    {
    FlushKeyState ();
    for (int i = 0 ; i < AnzHashs ; i++) {
      delete k[i].keyHash ;
      k[i].keyHash = NULL ;
      }
    _lclose (hfile);

    hfile = 0 ;
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
    for (int i = 0 ; i < AnzHashs ; i++)
      AddToKey (i,rec,Write (GlobalLock (hGBuffer),length),length);
    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);
    }
  void Update (LPDBRECORD rec,RecBuffer FAR *res)
    {
    Create ();
    LONG length ;
    GLOBALHANDLE hGBuffer = CreateBlock (rec,&length,res);
    LONG newPos = Write (GlobalLock (hGBuffer),length);
    GlobalUnlock (hGBuffer);
    for (int i = 0 ; i < AnzHashs ; i++) {
      LPVOID KeyBuffer = BuildKeyBuffer (i,rec);
      if (KeyBuffer != NULL) {
        SeqRDesc r;
        r.dbPos = newPos ;
        r.dbLen = length ;
        k[i].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
        k[i].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer));
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
    if (KeyBuffer != NULL)
      k[j].keyHash->DelDatav (KeyBuffer,GetBlockSize(KeyBuffer));
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
    for (int i = 0 ; i < k[j].AnzKeySegs ; i++) {
      KeyBuffer = PushToKeyBuffer (KeyBuffer,p[i + 2]);
      ParamString = PushParam (ParamString,p[i + 2],pt[i + 2]) ;
      }
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
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);

      if (DoLog())
        LogCmd (stmt,td->GetName(),tStart,GetTickCount(),ParamString);

      if (ParamString) FreeGlobMem (ParamString);
      return rec;
      }
    else
      return NULL ;
    }

  SeqFile (LPSTR fName,int ah,KHDef FAR *kd)
    {
    FileName = fName ;
    k = kd;
    AnzHashs = ah;
    for (int i = 0 ; i < ah ; i++) {
      k[i].keyHash = new hash (137,VOIDKEY);
      }
    }

  ~SeqFile ()
    {
    for (int i = 0 ; i < AnzHashs ; i++) {
      if (k[i].keyHash != NULL)
        delete k[i].keyHash;
      }
    if (hfile > 0)
      _lclose (hfile);
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
          WIN_ASSERT (s != NULL);
          s->Open ();
          int hn = s->CheckSelection ("Type = %1 AND TableID = %2 AND Version = %3");
          WIN_ASSERT (hn >= 0);
          s->DeleteByParams (hn,req->Param);
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
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDUPDATE :
          s->Update (res->first->rec[0],res);
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDDELETE :
          s->Delete (res->first->rec[0]);
          if ((res != NULL) && (res->first != NULL))
            res->first->rec[0] = NULL;
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDGET :
          {
          int hn = s->CheckSelection (req->SelectionName);
          WIN_ASSERT (hn >= 0);
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
      delete sfDef[i].sf ;
      sfDef[i].sf = NULL ;
      }
  Initialized = FALSE ;
  }
