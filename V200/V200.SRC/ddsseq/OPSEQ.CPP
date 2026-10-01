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
#include "rsbtrv.hpp"
#include "resadmin.hpp"
#define MODULENUM 167
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#include "compile.hpp"

#define INTERNNAME "-"

static GLOBALHANDLE CopyToHandle (LPVOID Data,DWORD DataSize)
  {
  GLOBALHANDLE hG = GlobalAlloc (GMEM_MOVEABLE,DataSize);
  LPVOID b = GlobalLock (hG);
  hmemcpy (b,Data,DataSize);
  GlobalUnlock (hG);
  return hG;
  }

static GLOBALHANDLE CopyBlobToHandle (LPBLOBDESC d,DWORD FAR *DataSize)
  {
  if ((d == NULL) || (d->hGmem == NULL)) {
    *DataSize = 0L;
    return 0;
    }
  *DataSize = d->Size;
  GLOBALHANDLE hG = GlobalAlloc (GMEM_MOVEABLE,d->Size);
  LPVOID dst = GlobalLock (hG);
  LPVOID src = GlobalLock (d->hGmem);
  hmemcpy (dst,src,d->Size);
  GlobalUnlock (d->hGmem);
  GlobalUnlock (hG);
  return hG;
  }

static BOOL IsSameBlobData (LPBLOBDESC d,LPVOID Data,DWORD DataSize)
  {
  if (d == NULL)
    return FALSE;
  if (d->Size != DataSize)
    return FALSE;
  LPVOID oldData = GlobalLock (d->hGmem);
  BOOL same = lmemcmp (oldData,Data,DataSize);
  GlobalUnlock (d->hGmem);
  return same;
  }

static BOOL GetDataDictNameByID (short type,WORD TableID,WORD Version,LPSTR TableName)
  {
  DBList FAR *lst = GetAllDataDict (type);
  BOOL found = FALSE;
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if ((*(WORD FAR *)r->Get(2) == TableID) && (*(WORD FAR *)r->Get(4) == Version)) {
      lstrcpy (TableName,LPSTR(r->Get(1)));
      found = TRUE;
      break;
      }
    }
  delete lst;
  return found;
  }

static WORD FindRowVersionByName (WORD TableIdent,LPSTR VarName)
  {
  DBList FAR *lst = GetAllDataDict (RST_VRDATADICT);
  WORD res = 0;
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if ((*(WORD FAR *)r->Get(2) == TableIdent) && (lstrcmp (LPSTR(r->Get(1)),VarName) == 0)) {
      res = *(WORD FAR *)r->Get(4);
      break;
      }
    }
  delete lst;
  return res;
  }

static WORD FindNextRowVersion (WORD TableIdent,WORD PrevRow,LPSTR RowName)
  {
  DBList FAR *lst = GetAllDataDict (RST_VRDATADICT);
  WORD foundVersion = 0;
  BOOL found = FALSE;
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if (*(WORD FAR *)r->Get(2) == TableIdent) {
      WORD v = *(WORD FAR *)r->Get(4);
      if ((v > PrevRow) && ((!found) || (v < foundVersion))) {
        foundVersion = v;
        lstrcpy (RowName,LPSTR(r->Get(1)));
        found = TRUE;
        }
      }
    }
  delete lst;
  return (found) ? foundVersion : 0;
  }

static WORD FindMaxRowVersion (WORD TableIdent)
  {
  DBList FAR *lst = GetAllDataDict (RST_VRDATADICT);
  WORD maxV = 0;
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if (*(WORD FAR *)r->Get(2) == TableIdent) {
      WORD v = *(WORD FAR *)r->Get(4);
      if (v > maxV) maxV = v;
      }
    }
  delete lst;
  return maxV;
  }

static void DeleteDataDictByTypeAndTable (short type,WORD TableIdent)
  {
  WORD vers[2048];
  int cnt = 0;
  DBList FAR *lst = GetAllDataDict (type);
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if (*(WORD FAR *)r->Get(2) == TableIdent) {
      if (cnt < int(sizeof(vers) / sizeof(vers[0])))
        vers[cnt++] = *(WORD FAR *)r->Get(4);
      }
    }
  delete lst;

  for (int i = 0 ; i < cnt ; i++)
    DelDataDict (type,TableIdent,vers[i]);
  }

static DWORD FindResourceIdByTypeAndName (short type,LPSTR Name)
  {
  DBList FAR *lst = GetAllResourceData (type);
  DWORD id = 0;
  for (LPDBRECORD r = lst->GetFirst(); r != NULL ; r = lst->GetNext(r)) {
    if (lstrcmp (LPSTR(r->Get(2)),Name) == 0) {
      id = *(DWORD FAR *)r->Get(0);
      break;
      }
    }
  delete lst;
  return id;
  }

static DBList FAR *gDocList = NULL;
static LPDBRECORD gDocRec = NULL;
static DBList FAR *gResList = NULL;
static LPDBRECORD gResRec = NULL;
static DBList FAR *gTblList = NULL;
static LPDBRECORD gTblRec = NULL;

static void ResetDocEnum ()
  {
  if (gDocList != NULL) delete gDocList;
  gDocList = NULL;
  gDocRec = NULL;
  }

static void ResetResEnum ()
  {
  if (gResList != NULL) delete gResList;
  gResList = NULL;
  gResRec = NULL;
  }

static void ResetTblEnum ()
  {
  if (gTblList != NULL) delete gTblList;
  gTblList = NULL;
  gTblRec = NULL;
  }

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
class FAR SeqFile {
 public :
  HFILE hfile;
  LPSTR FileName;
  int AnzHashs ;
  KHDef FAR *k;
  HFILE hfileCopy;

  void GetInsertRecord (LPDBRECORD old,LPTABLEDEF td,RecBuffer FAR *res)
    {
    // Da dieser Zweig nur von DBConvert aufgerufen wird, kann auf
    // die Recordrueckgabe verzichtet werden
    res->first = res->act = NULL ;
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

    RecBufferLine FAR *n = res->first->Next;
    FreeGlobMem (res->first);
    res->first = n;

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
  void AddToKey (int kn,LPDBRECORD rec,LONG Pos,LONG recSize)
    {
    WORD varInd;
    LPTABLEDEF td = rec->GetTableDef (0,&varInd);
    LPVOID KeyBuffer = NULL;
    for (int i = 0 ; i < k[kn].AnzKeySegs ; i++)
      for (int j = 0 ; j < td->GetAnzVars () ; j ++)
        if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[i]) == 0)
          KeyBuffer = PushToKeyBuffer (KeyBuffer,rec->Get(j));
    SeqRDesc r;
    r.dbPos = Pos ;
    r.dbLen = recSize ;
    // WIN_ASSERT (k[kn].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer)));
    k[kn].keyHash->SetDatav (KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer));
    FreeGlobMem (KeyBuffer);
    }
  void RemoveFromKey (int kn,LPDBRECORD rec)
    {
    WORD varInd;
    LPTABLEDEF td = rec->GetTableDef (0,&varInd);
    LPVOID KeyBuffer = NULL;
    for (int i = 0 ; i < k[kn].AnzKeySegs ; i++)
      for (int j = 0 ; j < td->GetAnzVars () ; j ++)
        if (lstrcmp (td->GetVarDef(j)->GetName(),k[kn].KeySeg[i]) == 0)
          KeyBuffer = PushToKeyBuffer (KeyBuffer,rec->Get(j));
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
      hfile = OpenFile (GetFullPath(path),&Of,OF_READ | OF_SHARE_COMPAT);
      hfileCopy = hfile;
      WIN_ASSERT (hfile > 0);
      LONG keyInfo[32];
      WIN_ASSERT (_lread (hfile,keyInfo,sizeof(keyInfo[0]) * AnzHashs * 2) == sizeof(keyInfo[0]) * AnzHashs * 2);
      for (int i = 0 ; i < AnzHashs ; i++) {
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
  void CloseFileAfterInsert ()
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
      delete k[i].keyHash ;
      k[i].keyHash = NULL ;
      }
    _lclose (hfile);

    hfile = 0 ;
    }
  void Insert (LPDBRECORD rec,RecBuffer FAR *res)
    {
    Create ();
    LONG length ;
    GLOBALHANDLE hGBuffer = CreateBlock (rec,&length,res);
    for (int i = 0 ; i < AnzHashs ; i++)
      AddToKey (i,rec,Write (GlobalLock (hGBuffer),length),length);
    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);
    }
  LPDBRECORD Update (int j,LPVOID FAR *p,LPTABLEDEF td,WORD FAR *pt,LPSTR stmt,
                     LPDBRECORD rec,RecBuffer FAR *res)
    {
    LPDBRECORD oldRec = Get (j,p,td,pt,stmt);
    if (oldRec == NULL)
      return NULL;

    for (int i = 0 ; i < AnzHashs ; i++)
      RemoveFromKey (i,oldRec);
    delete oldRec;

    Insert (rec,res);
    return rec;
    }

  BOOL Delete (int j,LPVOID FAR *p,LPTABLEDEF td,WORD FAR *pt,LPSTR stmt)
    {
    LPDBRECORD oldRec = Get (j,p,td,pt,stmt);
    if (oldRec == NULL)
      return FALSE;

    for (int i = 0 ; i < AnzHashs ; i++)
      RemoveFromKey (i,oldRec);
    delete oldRec;
    return TRUE;
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


static LPSTR ScriptSegs0 [] = { "Type" } ;
static LPSTR ScriptSegs [] = { "Type","fName" } ;
static LPSTR ResSegs1 [] = { "Nummer" } ;
static LPSTR ResSegs2 [] = { "Type","fName" } ;
static LPSTR ResSegs3 [] = { "Type" } ;
static LPSTR DataDictSegs [] = { "Type","TableID","Version" } ;
static LPSTR DataDictSegs1 [] = { "Type" } ;
static LPSTR DataDictSegs2 [] = { "Version" } ;
static LPSTR DataDictSegs3 [] = { "Type","Name" } ;
static LPSTR DataDictSegs4 [] = { "Type","TableID" } ;
static LPSTR RSSegs1 [] = { "Nummer" } ;
static LPSTR RSSegs2 [] = { "Art","Leistung" } ;
static LPSTR RSSegs3 [] = { "Art","Makro" } ;
static LPSTR DictDBSegs [] = { "Type" } ;
KHDef ScriptKey [] = {
  { "Type = %1", 1 , ScriptSegs0 , NULL } ,
  { "Type = %1 AND fName = %2", 2 , ScriptSegs , NULL }
  } ;
KHDef ResKeys [] = {
  { "Nummer = %1", 1 , ResSegs1 , NULL } ,
  { "Type = %1 AND fName = %2", 2 , ResSegs2 , NULL } ,
  { "Type = %1", 1 , ResSegs3 , NULL }
  } ;
KHDef DDictKeys [] = {
  { "Type = %1 AND TableID = %2 AND Version = %3", 3 , DataDictSegs , NULL } ,
  { "Type = %1", 1 , DataDictSegs1 , NULL } ,
  { "Version = %1", 1 , DataDictSegs2 , NULL } ,
  { "Type = %1 AND Name = %2", 2 , DataDictSegs3 , NULL } ,
  { "Type = %1 AND TableID = (SELECT MAX(TableID) FROM DataDict WHERE Type = %1 AND TableID < %2)", 2 , DataDictSegs4 , NULL } ,
  { "Type = %1 AND TableID = %2 AND Version = (SELECT MAX(Version) FROM DataDict WHERE Type = %1 AND TableID = %2 AND Version < %3)", 3 , DataDictSegs , NULL }
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
    { "ScriptDB" , 2, ScriptKey , NULL } ,
    { "ResDB" , 3 , ResKeys , NULL } ,
    { "DataDict" , 6 , DDictKeys , NULL } ,
    { "RestriktionsScript" , 3 , RSKeys , NULL } ,
    { "DictDB" , 1 , DictDBKeys , NULL } 
  } ;

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
      s = GetSeqFile (req->TableDef[0]);
      WIN_ASSERT (s != NULL) ;
      switch (req->Type) {
        case DBCALLTYPE_CREATE:
        case DBCALLTYPE_TEST:
          state = DBCALL_SUCCESS ;
          break ;
        case DBCALLTYPE_STANDARDINSERT :
          s->Insert (res->first->rec[0],res);
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
        case DBCALLTYPE_STANDARDUPDATE :
          {
          int hn = s->CheckSelection (req->SelectionName);
          WIN_ASSERT (hn >= 0);
          rec = s->Update (hn,req->Param,req->TableDef[0],req->ParamType,req->SelectionName,
                           res->first->rec[0],res);
          if (rec != NULL)
            state = DBCALL_SUCCESS;
          else
            state = DBCALL_NODATA;
          }
          break ;
        case DBCALLTYPE_STANDARDDELETE :
          {
          int hn = s->CheckSelection (req->SelectionName);
          WIN_ASSERT (hn >= 0);
          if (s->Delete (hn,req->Param,req->TableDef[0],req->ParamType,req->SelectionName))
            state = DBCALL_SUCCESS;
          else
            state = DBCALL_NODATA;
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

DLLExport WORD _export WINAPI DataRes_SetTableDef (LPSTR DLLName,LPSTR TableName,
             WORD TableIdMin,WORD TableIdMax,LPVOID TableData,DWORD TableSize,
             BOOL FAR *changed)
  {
  WORD TableID = ReadTableID (RST_TBDATADICT,TableName,TableIdMin,TableIdMax);
  DWORD oldSize = 0L;
  GLOBALHANDLE hGold = ReadDataDict (RST_TBDATADICT,TableID,0,&oldSize);

  if ((hGold != 0) && (oldSize == TableSize)) {
    LPVOID oldData = GlobalLock (hGold);
    *changed = !lmemcmp (oldData,TableData,TableSize);
    GlobalUnlock (hGold);
    }
  else
    *changed = TRUE;

  if (*changed) {
    GLOBALHANDLE hG = CopyToHandle (TableData,TableSize);
    WriteDataDict (RST_TBDATADICT,TableName,TableID,0,0,0,hG,TableSize);
    GlobalFree (hG);
    }

  if (hGold != 0)
    GlobalFree (hGold);
  return TableID;
  }

DLLExport WORD _export WINAPI DataRes_SetRowDef (LPSTR DLLName,WORD TableIdent,
             LPSTR VarName,LPVOID VarData,DWORD VarSize,BOOL FAR *changed)
  {
  WORD RowIdent = FindRowVersionByName (TableIdent,VarName);
  if (RowIdent == 0)
    RowIdent = WORD(FindMaxRowVersion(TableIdent) + 1);

  DWORD oldSize = 0L;
  GLOBALHANDLE hGold = ReadDataDict (RST_VRDATADICT,TableIdent,RowIdent,&oldSize);
  if ((hGold != 0) && (oldSize == VarSize)) {
    LPVOID oldData = GlobalLock (hGold);
    *changed = !lmemcmp (oldData,VarData,VarSize);
    GlobalUnlock (hGold);
    }
  else
    *changed = TRUE;

  if (*changed) {
    GLOBALHANDLE hG = CopyToHandle (VarData,VarSize);
    WriteDataDict (RST_VRDATADICT,VarName,TableIdent,RowIdent,0,0,hG,VarSize);
    GlobalFree (hG);
    }

  if (hGold != 0)
    GlobalFree (hGold);
  return RowIdent;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetTableDef (LPSTR DLLName,WORD TableId,
                  LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *Size)
  {
  *HeaderSize = 0L;
  if (!GetDataDictNameByID (RST_TBDATADICT,TableId,0,TableName))
    *TableName = '\0';
  return ReadDataDict (RST_TBDATADICT,TableId,0,Size);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstRowDef (LPSTR DLLName,
             WORD TableIdent,LPSTR RowName,WORD FAR *RowIdent,
             DWORD FAR *HeaderSize,DWORD FAR *RowSize)
  {
  *HeaderSize = 0L;
  *RowName = '\0';
  *RowSize = 0L;
  *RowIdent = FindNextRowVersion (TableIdent,0,RowName);
  if (*RowIdent == 0)
    return 0;
  return ReadDataDict (RST_VRDATADICT,TableIdent,*RowIdent,RowSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextRowDef (LPSTR DLLName,
             WORD TableIdent,WORD PrevRow,LPSTR RowName,WORD FAR *RowIdent,
             DWORD FAR *HeaderSize,DWORD FAR *RowSize)
  {
  *HeaderSize = 0L;
  *RowName = '\0';
  *RowSize = 0L;
  *RowIdent = FindNextRowVersion (TableIdent,PrevRow,RowName);
  if (*RowIdent == 0)
    return 0;
  return ReadDataDict (RST_VRDATADICT,TableIdent,*RowIdent,RowSize);
  }

DLLExport void _export WINAPI DataRes_SetFullTableDef (LPSTR DLLName,WORD TableIdent,
                  LPSTR TableName,LPVOID TableData,DWORD TableSize)
  {
  GLOBALHANDLE hG = CopyToHandle (TableData,TableSize);
  WriteDataDict (RST_TBFDATADICT,TableName,TableIdent,0,0,0,hG,TableSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFullTableDef (LPSTR DLLName,WORD TableIdent,
                  LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize)
  {
  *HeaderSize = 0L;
  if (!GetDataDictNameByID (RST_TBFDATADICT,TableIdent,0,TableName))
    *TableName = '\0';
  return ReadDataDict (RST_TBFDATADICT,TableIdent,0,TableSize);
  }

DLLExport BOOL _export WINAPI DataRes_GetFirstTableDef (WORD FAR *TableIdent,LPSTR TableName)
  {
  ResetTblEnum();
  gTblList = GetAllDataDict (RST_TBDATADICT);
  gTblRec = (gTblList != NULL) ? gTblList->GetFirst() : NULL;
  if (gTblRec == NULL) {
    *TableName = '\0';
    *TableIdent = 0;
    ResetTblEnum();
    return FALSE;
    }
  *TableIdent = *(WORD FAR *)gTblRec->Get(2);
  lstrcpy (TableName,LPSTR(gTblRec->Get(1)));
  return TRUE;
  }

DLLExport BOOL _export WINAPI DataRes_GetNextTableDef (WORD PrevIdent,WORD FAR *TableIdent,LPSTR TableName)
  {
  if ((gTblList == NULL) || (gTblRec == NULL)) {
    *TableName = '\0';
    *TableIdent = 0;
    return FALSE;
    }
  gTblRec = gTblList->GetNext (gTblRec);
  if (gTblRec == NULL) {
    *TableName = '\0';
    *TableIdent = 0;
    ResetTblEnum();
    return FALSE;
    }
  *TableIdent = *(WORD FAR *)gTblRec->Get(2);
  lstrcpy (TableName,LPSTR(gTblRec->Get(1)));
  return TRUE;
  }

DLLExport void _export WINAPI DataRes_SetDictCont (LPVOID Data,DWORD DataSize)
  {
  GLOBALHANDLE hG = CopyToHandle (Data,DataSize);
  WriteDataDict (RST_DDCONT,"CONT",0,0,0,0,hG,DataSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDictCont (DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  *HeaderSize = 0L;
  return ReadDataDict (RST_DDCONT,0,0,DataSize);
  }

DLLExport void _export WINAPI DataRes_SetDocDef (LPSTR DocName,LPVOID DocData,DWORD DataSize)
  {
  GLOBALHANDLE hG = CopyToHandle (DocData,DataSize);
  WriteScriptData (RSS_TYPEDOCDEF,DocName,hG,DataSize);
  GlobalFree (hG);
  }

DLLExport void _export WINAPI DataRes_SetFuncDef (LPVOID DocData,DWORD DataSize)
  {
  GLOBALHANDLE hG = CopyToHandle (DocData,DataSize);
  WriteScriptData (RSS_TYPEFNCPROT,INTERNNAME,hG,DataSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDocDef (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *HeaderSize = 0L;
  return ReadScriptData (RSS_TYPEDOCDEF,DocName,DocSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFuncDef (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *HeaderSize = 0L;
  return ReadScriptData (RSS_TYPEFNCPROT,INTERNNAME,DocSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *HeaderSize = 0L;
  *DocName = '\0';
  ResetDocEnum();
  gDocList = GetAllScriptData (RSS_TYPEDOCDEF);
  gDocRec = (gDocList != NULL) ? gDocList->GetFirst() : NULL;
  if (gDocRec == NULL)
    return 0;
  lstrcpy (DocName,LPSTR(gDocRec->Get(2)));
  return CopyBlobToHandle (LPBLOBDESC(gDocRec->Get(3)),DocSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *HeaderSize = 0L;
  *DocName = '\0';
  if ((gDocList == NULL) || (gDocRec == NULL))
    return 0;
  gDocRec = gDocList->GetNext (gDocRec);
  if (gDocRec == NULL) {
    ResetDocEnum();
    return 0;
    }
  lstrcpy (DocName,LPSTR(gDocRec->Get(2)));
  return CopyBlobToHandle (LPBLOBDESC(gDocRec->Get(3)),DocSize);
  }

DLLExport void _export WINAPI DataRes_SetDocCont (LPVOID DocData,DWORD DataSize)
  {
  GLOBALHANDLE hG = CopyToHandle (DocData,DataSize);
  WriteScriptData (RSS_TYPEDOCCONT,INTERNNAME,hG,DataSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDocCont (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *HeaderSize = 0L;
  return ReadScriptData (RSS_TYPEDOCCONT,INTERNNAME,DocSize);
  }

DLLExport DWORD _export WINAPI DataRes_SetResource (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
  {
  DWORD ResID = FindResourceIdByTypeAndName (short(Type),Name);
  BOOL doWrite = TRUE;
  if (ResID != 0) {
    DWORD oldSize = 0L;
    GLOBALHANDLE hOld = ReadResourceData (ResID,&oldSize);
    if ((hOld != 0) && (oldSize == DataSize)) {
      LPVOID oldData = GlobalLock (hOld);
      doWrite = !lmemcmp (oldData,Data,DataSize);
      GlobalUnlock (hOld);
      }
    if (hOld != 0)
      GlobalFree (hOld);
    }

  if (doWrite) {
    GLOBALHANDLE hG = CopyToHandle (Data,DataSize);
    WriteResourceData (short(Type),Name,hG,DataSize);
    GlobalFree (hG);
    }

  if (ResID == 0)
    ResID = FindResourceIdByTypeAndName (short(Type),Name);
  return ResID;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetResource (DWORD ResID,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  *HeaderSize = 0L;
  return ReadResourceData (ResID,DataSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstResource (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  *HeaderSize = 0L;
  *ResName = '\0';
  *Id = 0;
  ResetResEnum();
  gResList = GetAllResourceData (short(Type));
  gResRec = (gResList != NULL) ? gResList->GetFirst() : NULL;
  if (gResRec == NULL)
    return 0;
  *Id = *(DWORD FAR *)gResRec->Get(0);
  lstrcpy (ResName,LPSTR(gResRec->Get(2)));
  return CopyBlobToHandle (LPBLOBDESC(gResRec->Get(3)),DataSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextResource (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  *HeaderSize = 0L;
  *ResName = '\0';
  if ((gResList == NULL) || (gResRec == NULL)) {
    *Id = 0;
    return 0;
    }
  gResRec = gResList->GetNext (gResRec);
  if (gResRec == NULL) {
    *Id = 0;
    ResetResEnum();
    return 0;
    }
  *Id = *(DWORD FAR *)gResRec->Get(0);
  lstrcpy (ResName,LPSTR(gResRec->Get(2)));
  return CopyBlobToHandle (LPBLOBDESC(gResRec->Get(3)),DataSize);
  }

DLLExport void _export WINAPI DataRes_SetResCont (WORD Type,LPVOID Data,DWORD DataSize)
  {
  GLOBALHANDLE hG = CopyToHandle (Data,DataSize);
  WriteResourceData (short(Type + 0x8000),INTERNNAME,hG,DataSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetResCont (WORD Type,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  *HeaderSize = 0L;
  return ReadResourceData (short(Type + 0x8000),INTERNNAME,DataSize);
  }

DLLExport void _export WINAPI DataRes_ClearRowDefs (LPSTR DLLName,WORD TableIdent)
  {
  DeleteDataDictByTypeAndTable (RST_VRDATADICT,TableIdent);
  }

DLLExport void _export WINAPI DataRes_SetServerSource (LPSTR DLLName,WORD TableIdent,
                  LPSTR TableName,LPVOID TableData,DWORD TableSize)
  {
  GLOBALHANDLE hG = CopyToHandle (TableData,TableSize);
  WriteDataDict (RST_DSERVSRC,TableName,TableIdent,0,0,0,hG,TableSize);
  GlobalFree (hG);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetServerSource (LPSTR DLLName,WORD TableIdent,
                  LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize)
  {
  *HeaderSize = 0L;
  if (!GetDataDictNameByID (RST_DSERVSRC,TableIdent,0,TableName))
    *TableName = '\0';
  return ReadDataDict (RST_DSERVSRC,TableIdent,0,TableSize);
  }

DLLExport void _export WINAPI DataRes_DelTableDef (LPSTR DLLName,WORD TableIdent)
  {
  DataRes_ClearRowDefs (DLLName,TableIdent);
  DeleteDataDictByTypeAndTable (RST_TBDATADICT,TableIdent);
  DeleteDataDictByTypeAndTable (RST_TBFDATADICT,TableIdent);
  DeleteDataDictByTypeAndTable (RST_DSERVSRC,TableIdent);
  }

void OnExit ()
  {
  ResetDocEnum();
  ResetResEnum();
  ResetTblEnum();
  for (int i = 0 ; i < sizeof(sfDef) / sizeof(sfDef[0]) ; i++)
    if (sfDef[i].sf != NULL) {
      delete sfDef[i].sf ;
      sfDef[i].sf = NULL ;
      }
  Initialized = FALSE ;
  }

