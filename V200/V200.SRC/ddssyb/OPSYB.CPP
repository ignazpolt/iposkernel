//////////////////////////////////////////////////////////////
//  Sybase - Anbindung an das Clinicum
//////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/ddssyb/rev/opsyb.cpv   1.13   17 Dec 1996 11:16:48   GERHOLD  $
//  $Log:   P:/marille/clinicum/ddssyb/rev/opsyb.cpv  $
// 
//    Rev 1.13   17 Dec 1996 11:16:48   GERHOLD
// 32 Bit Umstellung
// 
//    Rev 1.12   27 Nov 1996 08:41:30   HANNES
// 
//    Rev 1.11   19 Mar 1996 21:15:36   MARTIN
// -outerjoins fuer hierarichisch tieferliegende Tabellen mitschleifen
// -indikator fuer Null - Werte
// -bei Joins auf die volle Tabellendefinition eingehen
// -Wherebedingung bei Listen auf ein EXEC abpruefen
// 
//    Rev 1.10   08 Mar 1996 12:58:32   MARTIN
// HEX-Codierung in GetVarString->IsFixed->default korrigiert
// 
//    Rev 1.9   08 Mar 1996 00:02:26   HANNES
// Null - Values
// Fehler in GetVarString
// Fehlerhandling 'unkritischer' Fehler
// Syntaxfehler in SyncStatement
// 
//    Rev 1.8   04 Mar 1996 23:45:36   HANNES
// CHAR->VARCHAR, Default NULL, keine Leeren Strings in die Datenbank
// 
//    Rev 1.7   04 Mar 1996 17:23:28   HANNES
// WhereDone dem SyncStatement uebergeben
// Speicherfresser in CreateTable
// VarLen dem GetVarString uebergeben
// 
//    Rev 1.6   04 Feb 1996 15:40:54   hannes
// #define NOCOMPILE
// 
//    Rev 1.5   02 Feb 1996 14:30:24   MARTIN
// dds32.h
// 
//    Rev 1.4   01 Feb 1996 15:55:24   HANNES
// Feineres Handling der Joindefinition: Abhaengig von TypeOfJoin wird ein
// unterschiedliches Verhalten bezueglich inner / outer Join angewendet. Zu
// diesem Zwecke wurde der Compiler der Join - Definition erweitert:
// Neue Syntax: ... join [ inner | outer ] with ... 
// Wird keines dieser neuen Schluesselwoerter im Compiler angegeben, dann blei
// das Standardverhalten erhalten.
// 
//    Rev 1.3   20 Jan 1996 11:17:00   HANNES
// 
//    Rev 1.2   13 Jan 1996 15:44:28   HANNES
// Letze Version vor der Umstellung auf die CS - Library
// 
//    Rev 1.1   02 Jan 1996 22:20:52   HANNES
// 
//    Rev 1.0   04 Dec 1995 10:06:12   HANNES
// Initial revision.
// 
#include <windows.h>
#include "dds32.h"

#ifdef WIN32
  #define __export
  #define _far
  #define _pascal
  #define  NT    1
#else
  #define WIN3  1
#endif

extern "C" {
#include <stdio.h>
#include <ctpublic.h>
  }
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 162
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"

#define NOCOMPILE
#include "compile.hpp"
#include "resadmin.hpp"

#define DOLOG

static char winassstr[2048];
void LogCmd (LPSTR txt)
  {
  OFSTRUCT Of;
  static char *fname = "cmds.log";
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        retry++;
        }
      else {
        f = OpenFile (fname,&Of,OF_CREATE);
        _lclose(f);
        }
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    _lwrite (f,txt,lstrlen(txt) + 1);
    _lwrite (f,"\r\n\r\n",4);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

/*------< Klasse sybase zur Herstellung der Verbindung >--------*/
#define MAXBLOCKEDSIZE  0x2000
struct TableData {
  BOOL IsTested;
  };
struct ColData {
  char TypeName[32];
  };
class FAR sybstmt;
class FAR PartString {
 public :
  int len;
  LPSTR str;
  PartString (LPSTR h,int size)
    {
    str = h ;
    len = size;
    }
  };
class FAR LongString {
 private :
  GLOBALHANDLE hGmem;
  int Size;
  int SizeAlloced;
  LPSTR base;
  int NextSize (int s)
    {
    return ((s / 4096) + 1) * 4096 ;
    }
  void Enlarge (int s)
    {
    if (NextSize (s) != SizeAlloced) {
      SizeAlloced = NextSize(s) ;
      if (hGmem != NULL)
        hGmem = GlobalReAlloc (hGmem,SizeAlloced,GMEM_MOVEABLE);
      else
        hGmem = GlobalAlloc (GMEM_MOVEABLE,SizeAlloced);
      base = (LPSTR)GlobalLock (hGmem);
      }
    }
 public :
  LongString ()
    {
    Size = 0;
    SizeAlloced = 0;
    hGmem = 0;
    base = NULL ;
    }
  void Clear ()
    {
    if (hGmem != NULL) GlobalFree (hGmem);
    Size = 0;
    SizeAlloced = 0;
    hGmem = 0;
    base = NULL ;
    }
  ~LongString ()
    {
    if (hGmem != NULL) GlobalFree (hGmem);
    }
  LongString &operator + (LPSTR str)
    {
    if (str == NULL) return *this ;
    int nsize = lstrlen(str);
    Enlarge (Size + nsize + 1);
    lstrcpy (base + Size,str);
    Size += nsize;
    base[Size] = '\0';
    return *this;
    }
  LongString &operator + (PartString FAR &p)
    {
    if (p.len == 0) return *this ;
    int nsize = p.len;
    Enlarge (Size + nsize + 1);
    lmemcpy (base + Size,p.str,p.len);
    Size += nsize;
    base[Size] = '\0';
    return *this;
    }
  LongString &operator + (int i)
    {
    char istr[32];
    sprintf (istr,"%d",i);
    return *this + istr;
    }

  LongString &operator + (LONG i)
    {
    char istr[32];
    sprintf (istr,"%ld",i);
    return *this + istr;
    }

  LongString &operator + (WORD i)
    {
    char istr[32];
    sprintf (istr,"%u",i);
    return *this + istr;
    }

  LongString &operator + (DWORD i)
    {
    char istr[32];
    sprintf (istr,"%lu",i);
    return *this + istr;
    }

  LPSTR Ptr()
    {
    return base;
    }
  int size()
    {
    return Size ;
    }
  LPSTR AnalyseSeq (LPSTR source,LPTABLEDEF ti = NULL,LPDBREQUEST req = NULL,BOOL useAlias = TRUE,BOOL useOld = FALSE,sybstmt FAR *s = NULL);
  LPSTR AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,LPSTR FAR *JoinSel,BOOL FAR *UseOuter);
  LPSTR InsertDescending (LPSTR h);
  LPSTR InsertSyncCond (LPSTR sync,LPDBREQUEST req,LPSTR connect,BOOL FAR &doAnd);
  };

class FAR sybase {
  void FetchTableNames ();
  BOOL TestTableDef (LPTABLEDEF td);
  void CreateTable (LPTABLEDEF td);

public :     
  /*---- Hash Tabellen fuer Tabellen, die bereits getestet wurden ----*/
  hash *TableHash;

  /*---- Sybase spezifische Daten ------*/
  CS_CONTEXT    *context;
  CS_CONNECTION *connection;

  /* --- Hilfsvariablen -----*/
  LPSTR GetAliasName (LPSTR Name)
    {
    return Name;
    }
  void TestTable (LPTABLEDEF td);
  LPSTR GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0);
  LPSTR BlockVarName ();
  LPSTR BlockTypeName ();

  CS_RETCODE Init ();
  CS_RETCODE Connect (LPSTR username, LPSTR password,LPSTR appname);

  sybase (LPSTR _user,LPSTR _password,LPSTR _appname);
  ~sybase () ;
  void Reset () ;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  DLLExport friend void _export FAR PASCAL DoBeginTransaction ();
  DLLExport friend void _export FAR PASCAL DoEndTransaction ();
  DLLExport friend void _export FAR PASCAL DoAbortTransaction ();
  };
static sybase FAR *dbase;

#define MAXROWSBUFFERED   64
static WORD AnzOpenStatements;

class FAR sybstmt {
 public :
  int  retVal;
  WORD Op;
  int  RecsToGet;
  RecBuffer FAR *res;
  LPDBREQUEST req;
  LPSTR oldStatement ;
  BOOL  prepareDone;
  LPVOID oldParam[CB_PARAM-2];
  WORD oldParamType[CB_PARAM-2];
  int dbCols;
  int dbMaxRows;
  BOOL noResult;
  LPCLKEYDEF k0;
  LPDBRECORD old;

  struct _COLINFO {
    CS_INT FAR     *VarLen;
    CS_SMALLINT FAR     *VarIndikat;
    LPVOID          VarData;
    CS_DATAFMT      VarFormat;
    } FAR *ColInfo ;

  // Virtuelle Funktionen zum Handling der verschiedenen 
  // des Datenbindung und Speicherung
  virtual int nRows (LPTABLEDEF ti);
  virtual int nRowsToGet (LPTABLEDEF ti)
    { return nRows (ti) ; }
  virtual int nCols (LPTABLEDEF ti);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual void StoreData (LPTABLEDEF ti,int Row);

  // Datenbindung
  LPVOID GetSybDataType (CS_DATAFMT FAR *fmt,WORD mType,int maxSize,int nRows);
  BOOL BindColData (CS_COMMAND FAR *cmd,LPTABLEDEF ti);

  // Ausfueheren eines Kommandos
  CS_COMMAND      *cmd;
  CS_RETCODE execute (LPSTR cmdbuf,LPTABLEDEF ti,CS_CONNECTION *conn = NULL);

  LPVOID BlockedData;
  BOOL ThereAreBlockedData ;
  void PushToBlocked (LPVOID Data,WORD VarID);
  LPVOID FindData (LPVOID BlockData,WORD VarID,int FAR *Size);

  void GetOldStatementCopy ()
    {
    oldStatement = LPSTR (GetGlobMem (lstrlen(req->SelectionName)+1));
    lstrcpy (oldStatement,req->SelectionName);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (req->Param[i+2] != NULL) {
        oldParam[i] = GetGlobMem (GetBlockSize (req->Param[i+2]));
        lmemcpy (oldParam[i],req->Param[i+2],GetBlockSize(req->Param[i+2]));
        oldParamType[i] = req->ParamType[i+2];
        }
      else {
        if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
        oldParam[i] = NULL ;
        }
      }
    }

  sybstmt ()
    {
    AnzOpenStatements ++ ;
    dbCols = -1 ;
    }

  virtual ~sybstmt ()
    {
    AnzOpenStatements -- ;
    if (oldStatement != NULL)
      FreeGlobMem (oldStatement);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
      }
    if (ColInfo != NULL) {
      for (int i = 0 ; i < dbCols ; i++) {
        FreeGlobMem (ColInfo[i].VarLen);
        FreeGlobMem (ColInfo[i].VarIndikat);
        FreeGlobMem (ColInfo[i].VarData);
        }
      FreeGlobMem (ColInfo);
      }
    if (BlockedData != NULL)
      FreeGlobMem (BlockedData);
    }

  void StmtExit ()
    {
    if (BlockedData != NULL)
      FreeGlobMem (BlockedData);
    BlockedData = NULL ;
    ThereAreBlockedData = FALSE ;
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }

  int StandardDelete ();
  int StandardGet ();
  void SelectStatement (LPTABLEDEF td,LongString FAR &s,int KeyNmbr = -1);
  void WhereStatement (LongString FAR &s,LPTABLEDEF td,LPTABLEDEF ti,BOOL FAR &wheredone,BOOL useOld = FALSE);
  void OrderStatement (LongString FAR &s,LPTABLEDEF td,BOOL descending);
  void SyncStatement (LongString FAR &s,LPDBREQUEST req,LPTABLEDEF td,LPSTR str,BOOL whereDone);
  LPVOID ConvertToMData (LPVARDEF v,LPVOID data,int Size,int FAR *rSize);
  LPDBRECORD StoreRow (LPTABLEDEF ti,int row);
  int StandardList (BOOL first);
  BOOL EnlargeInsert (LPVARDEF vd,int VarNr,LongString FAR &s,LongString FAR &v,int FAR *AnzPars);
  BOOL EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars);
  BOOL EnlargeUpdate (LPVARDEF vd,int VarNr,LongString FAR &s,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0);
  BOOL EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first);
  LPDBRECORD GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize);
  int StandardUpdate ();
  int StandardExcute ();
  int StandardInsert ();
  };
typedef sybstmt FAR *LPSYBSTMT;

class FAR insstmt : public sybstmt {
 public :
  int va ;
  insstmt () : sybstmt () { } 
  virtual int nRows (LPTABLEDEF ti)
    { return 1 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual void StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~insstmt () { }
  };

class FAR tablecheck : public sybstmt {
 public :
  tablecheck () : sybstmt () { } 
  virtual int nRows (LPTABLEDEF ti)
    { return 300 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual void StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~tablecheck () { }
  };

class FAR colcheck : public sybstmt {
 public :
  hash FAR *colhash;
  colcheck () : sybstmt () 
    { 
    colhash = new hash (111,STRKEY);
    } 
  virtual int nRows (LPTABLEDEF ti)
    { return 300 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 2 ; }
  virtual void StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~colcheck () { delete colhash ; }
  };

class FAR liststmt : public sybstmt {
 public :
  liststmt () : sybstmt () { } 
  BOOL doNext,doIt;
  PrimKey kLast;
  virtual void StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~liststmt () { }
  };

LPSTR GetParNr (LPSTR h,int FAR *Nr)
  {
  *Nr = 0 ;
  for ( ; ((*h >= '0') && (*h <= '9')) ; h ++ ) {
    *Nr = *Nr * 10 + *h - '0' ;
    }
  (*Nr) ++ ;
  return h ;
  }

BOOL mystrmcp (LPSTR h,LPSTR Name,int FAR *len)
  {
  for ( *len = 0 ; ; ) {
    if (*Name == '\0') return TRUE ;
    if (*h++ == *Name++) (*len) ++ ;
    else                 break ;
    }
  return FALSE ;
  }

LPSTR GetFullFieldName (LPSTR h,LPSTR AliasName,int tnum,LPTABLEDEF ti,LPDBREQUEST req,BOOL useAlias)
  {
  *AliasName = '\0' ;
  if (IsCharAlpha(*h)) {
    // Es koennte sich um einen Feldnamen handeln
    if (ti->IsInternTable()) {
      LPPTABLE p = LPINTTABLE (ti->GetDLLDef())->GetTableByNum(tnum);
      for (int i = 0 ; i < int(p->AnzVars) ; i++) {
        LPSTR Name = req->TableDef[tnum]->GetVarDef(p->VarID[i])->GetName();
        int len ;
        if (mystrmcp (h,Name,&len)) {
          if (useAlias)
            sprintf (AliasName,"t%d.%s",tnum,Name);
          else
            sprintf (AliasName,"%s",Name);
          return h + len;
          }
        }
      for ( ; ((IsCharAlpha(*h)) || ((*h >= '0') && (*h <= '9'))) ; h++ ) ;
      return h ;
      }
    else {
      for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
        LPSTR Name = ti->GetVarDef(i)->GetName();
        int len ;
        if (mystrmcp (h,Name,&len)) {
          if (useAlias)
            sprintf (AliasName,"t%d.%s",tnum,Name);
          else
            sprintf (AliasName,"%s",Name);
          return h + len;
          }
        }
      for ( ; ((IsCharAlpha(*h)) || ((*h >= '0') && (*h <= '9'))) ; h++ ) ;
      return h ;
      }
    }
  else
    return h + 1 ;
  }

BOOL NextIsSelect (LPSTR h)
  {
  int l;
  for ( ; ; h ++ ) {
    if ((*h != ' ') && (*h != '\r') && (*h != '\n') && (*h != '\t')) {
      return (mystrmcp (h,"SELECT",&l));
      }
    }
  return FALSE ;
  }

static LPSTR sqlmonth [] = {
  "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OKT","NOV","DEC" 
  };
inline BOOL IsFixed (int varType)
  {
  return ((varType == VAR_STRARR) || (varType == VAR_LONG) ||
          (varType == VAR_FLAG) || (varType == VAR_DEC) ||
          (varType == VAR_DWORD) || (varType == VAR_DATE) ||
          (varType == VAR_TIME) || (varType == VAR_POINT) || 
          (varType == VAR_SCALE)) ;
  }
inline BOOL IsChar (int varType)
  {
  return (varType == VAR_STR) ;
  }
LPSTR GetVarString (LPVOID data,int mType,BOOL FAR *doFree,int Size)
  {
  static char *null = "NULL" ;
  if (data == NULL) {
    *doFree = FALSE ;
    return null ;
    }
  if (IsFixed (mType)) {
    static char resstr[128];
    switch (mType) {
      case VAR_STRARR :
      case VAR_FLAG :
              sprintf (resstr,"%d",*(short FAR *) data) ;
              break ;
      case VAR_DEC :
        sprintf (resstr,"%f",*(float FAR *) data) ;
        break ;
      case VAR_LONG :
      case VAR_DWORD :
        sprintf (resstr,"%ld",* (LONG FAR *) data) ;
        break ;
      case VAR_DATE :
              sprintf (resstr,"'%s %d %d'",sqlmonth[((packdate FAR *) data)->month - 1],
                                          int (((packdate FAR *) data)->day),
                                          int (((packdate FAR *) data)->year));
              break ;
      case VAR_TIME :
              sprintf (resstr,"'%d:%d:%d'",int (((packtime FAR *) data)->hour),
                                          int (((packtime FAR *) data)->minute),
                                          int (((packtime FAR *) data)->second));
              break ;
      default :
              // binaere Codierung
              {
              LPSTR b = LPSTR(data);
              int len = GetBlockSize(b);
              LPSTR res = resstr ;
              *res ++ = '\'' ;
              for (int i = 0 ; i < len ; i++) {
          char h = (*b & 0xF0) >> 4 ;
          *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
          h = *b & 0x0F ;
          *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
          b ++ ;
                }
              *res ++ = '\'' ;
              *res ++ = '\0' ;
              }
              break ;
      }
    *doFree = FALSE ;
    return resstr ;
    }
  else if (IsChar(mType)) {
    int len = lstrlen(LPSTR(data)) ;
    if (len > 0) {
      *doFree = TRUE ;
      if ((Size > 0) && (len > Size - 1)) len = Size - 1;
      LPSTR res = LPSTR(GetGlobMem (len + 3)) ;
      lmemcpy (res+1,data,len) ;
      res[0] = '\'' ;
      res[len+1] = '\'' ;
      return res ;
      }
    else {
      *doFree = FALSE ;
      return null ;
      }
    }
  else {
    // Binary - Datatype
    LPSTR b = LPSTR(data);
    int len = GetBlockSize(b);
    LPSTR base = LPSTR (GetGlobMem (2 * len + 3)) ;
    LPSTR res = base ;
    *res ++ = '0' ;
    *res ++ = 'x' ;
    for (int i = 0 ; i < len ; i++) {
      char h = (*b & 0xF0) >> 4 ;
      *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
      h = *b & 0x0F ;
      *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
      b ++ ;
      }
    *res ++ = '\0' ;
    *doFree = TRUE ;
    return base ;
    }
  return NULL ;
  }
LPSTR GetParamString (LPDBREQUEST req,int parNr,BOOL FAR *doFree,BOOL useOld,sybstmt FAR *s)
  {
  if (useOld)
    return GetVarString (s->oldParam[parNr-2],s->oldParamType[parNr-2],doFree,-1);
  else
    return GetVarString (req->Param[parNr],req->ParamType[parNr],doFree,-1);
  }

LPSTR LongString::AnalyseSeq (LPSTR source,LPTABLEDEF ti,LPDBREQUEST req,BOOL useAlias,BOOL useOld,sybstmt FAR *s)
  {
  if (source == NULL) return NULL;
  BOOL instring = FALSE ;
  BOOL InSubSelect = FALSE ;
  LPSTR lastStart = source ;
  int level ;
  if (*source) {
    for (LPSTR h = source ; *h ; ) {
      if (instring) {
        switch (*h) {
          case '\'' :
            instring = FALSE ;
            h ++ ;
            break ;
          default :
            h++ ;
          }
        }
      else {
        switch (*h) {
          case '\'' :
            instring = TRUE ;
            h ++ ;
            break ;
          case '%' :
            {
            LPSTR beg = h ;
            int parNr;
            h = GetParNr (h+1,&parNr);
            WIN_ASSERT (req != NULL);
            BOOL doFree;
            LPSTR param = GetParamString (req,parNr,&doFree,useOld,s) ;
            *this = *this + PartString (lastStart,beg-lastStart) + param;
            if (doFree)
              FreeGlobMem (param);
            lastStart = h ;
            }
            break ;
          case '(' :
            h++ ;
            if (InSubSelect) level ++ ;
            else if (NextIsSelect (h)) level = 1 , InSubSelect = TRUE ;
            break ;
          case ')' :
            h++ ;
            level -- ;
            if (level == 0) InSubSelect = FALSE ;
            break ;
          default :
            if ((ti != NULL) && (req != NULL) && (!InSubSelect)) {
              char AliasName [256];
              LPSTR behindField = GetFullFieldName(h,AliasName,0,ti,req,useAlias);
              if (*AliasName) {
                      *this = *this + PartString (lastStart,h-lastStart);
                      lastStart = h = behindField ;
                      *this = *this + AliasName;
                }
              else
                h = behindField ;
              }
            else
              h ++ ;
          }
        }
      }
    if (lastStart != h)
       *this = *this + PartString (lastStart,h-lastStart);
    }
  else
    *this = *this + "" ;
  return LPSTR (Ptr());
  }

LPSTR LongString::InsertDescending (LPSTR source)
  {
  LPSTR last = source ;
  for (LPSTR h = source ; ; h ++) {
    if ((*h == ',') || (*h == '\0')) {
      *this = *this + PartString (last,h - last) + " DESC" ;
      last = h ;
      if (*h == '\0') break ;
      }
    }
  return LPSTR (Ptr());
  }

LPSTR LongString::InsertSyncCond (LPSTR sync,LPDBREQUEST req,LPSTR connect,BOOL FAR &doAnd)
  {
  LPSTR last = sync ;
  int pn = 1 ;
  for (LPSTR h = sync ; ; h ++) {
    if ((*h == ',') || (*h == '\0')) {
      BOOL doFree ;
      LPSTR param = GetParamString (req,pn++,&doFree,FALSE,NULL);
      if (doAnd)
        *this = *this + " AND" ;
      *this = *this + " " + PartString (last,h - last) + " " + 
              connect + " " + param ;
      doAnd = TRUE ;
      if (doFree)
        FreeGlobMem (param);
      if (*h == '\0') break ;
      h ++ ;
      last = h ;
      }
    }
  return LPSTR (Ptr());
  }

BOOL NextIsParam (LPSTR h)
  {
  for (h++ ; ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) ; h++ ) ;
  return (*h == '%') ;
  }

BOOL IsNullAllowed (LPDBREQUEST req,LPTABLEDEF ti,LPCLRIDEF r)
  {
  WIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if ((req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->Property & VPROP_NOTNULL) == 0) return TRUE ;
    }
  return FALSE ;
  }

LPSTR LongString::AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,LPSTR FAR *JoinSel,BOOL FAR *UseOuter)
  {
  LPSTR JoinName[32];
  // Ermitteln der Namen der Felder, die in den Join eingehen
  WIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if (UseOuter[e.TableNumber])
      UseOuter[tnum] = TRUE ;
    if (JoinSel[e.TableNumber] == NULL) {
      char JN[66];
      sprintf (JN,"t%d.%s",e.TableNumber,
            req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->GetName());
      JoinName[i] = LPSTR(GetGlobMem (lstrlen(JN)+1));
      lstrcpy (JoinName[i],JN);
      }
    else {
      // Loesung ueber Subselect
      char JN[256];
      sprintf (JN,"(SELECT t%d.%s FROM",e.TableNumber,req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->GetName()) ;
      for (int j = 0 ; j <= e.TableNumber ; j++) {
        char FN[80];
        if (j > 0)
          wsprintf (FN,",%s t%d",req->TableDef[j]->GetName(),j);
        else
          wsprintf (FN," %s t%d",req->TableDef[j]->GetName(),j);
        lstrcat (JN,FN);
        }
      JoinName[i] = LPSTR(GetGlobMem (lstrlen(JN) + GetBlockSize(JoinSel[e.TableNumber])+1));
      lstrcpy (JoinName[i],JN);
      lstrcat (JoinName[i],JoinSel[e.TableNumber]);
      lstrcat (JoinName[i],")");
      }
    }

  // Austauschen der %xx Teile durch den Alias Namen
  BOOL instring = FALSE ;
  LPSTR lastStart = r->name ;
  BOOL InSubSelect = FALSE ;
  int level;
  for (LPSTR h = r->name ; *h ; ) {
    if (instring) {
      switch (*h) {
        case '\'' :
          instring = FALSE ;
          h ++ ;
          break ;
        default :
          h++ ;
        }
      }
    else {
      switch (*h) {
        case '\'' :
          instring = TRUE ;
          h ++ ;
          break ;
        case '(' :
          h++ ;
          if (InSubSelect) level ++ ;
          else if (NextIsSelect (h)) level = 1 , InSubSelect = TRUE ;
          break ;
        case ')' :
          h++ ;
          level -- ;
          if (level == 0) InSubSelect = FALSE ;
          break ;
        case '%' :
          {
          *this = *this + PartString (lastStart,h-lastStart) ;
          int FieldNr;
          lastStart = h = GetParNr (h+1,&FieldNr);
          *this = *this + JoinName[FieldNr-2] ;
          }
          break ;
        case '=' :
          {
          if ((UseOuter[tnum]) && (NextIsParam (h)) && (!InSubSelect)) {
            // = wird durch =* ersetzt
            *this = *this + PartString (lastStart,h-lastStart);
            lastStart = h = h + 1 ;
            *this = *this + "=*";
            }
          else
            h ++ ;  // nur 'normaler' Join
          }
          break ;
        default :
          {
          char AliasName [256];
          LPSTR behindField = GetFullFieldName(h,AliasName,tnum,req->TableDef[tnum],req,TRUE);
          if (*AliasName) {
            *this = *this + PartString (lastStart,h-lastStart);
            lastStart = h = behindField ;
            *this = *this + AliasName;
            }
          else
            h = behindField ;
          }
        }
      }
    }
  if (lastStart != h)
    *this = *this + PartString (lastStart,h-lastStart);

  // Loeschen der Feldname
  for (i = 0 ; i < int(r->AnzSegs) ; i++)
    FreeGlobMem (JoinName[i]);
  return LPSTR(Ptr());
  }

struct MBlockHeader {
  WORD AnzVars;
  WORD BlockSize;
  };
struct MBlockVarHeader {
  WORD VarID;
  WORD VarSize;
  };
/*-----------------------------------------*/
/*  MessageHandler fuer Client - Messages  */
/*-----------------------------------------*/
DLLExport CS_RETCODE _export FAR PASCAL ex_clientmsg_cb(CS_CONTEXT *context, CS_CONNECTION *connection, CS_CLIENTMSG *errmsg)
  {
  LongString errStr;
  errStr = errStr + "Open Client Message:\r\nMessage number: LAYER = " + 
                    CS_LAYER(errmsg->msgnumber) +
                    " ORIGIN = " + CS_ORIGIN(errmsg->msgnumber) + 
                    "SEVERITY = " + CS_SEVERITY(errmsg->msgnumber) + 
                    "NUMBER = " + CS_NUMBER(errmsg->msgnumber) + 
                    "\r\nMessage: " + errmsg->msgstring ;
  if (errmsg->osstringlen > 0)
    errStr = errStr + "\r\n (OS: " + errmsg->osstring + ")" ;

  WIN_ASSERT_TEXT (FALSE,errStr.Ptr());

  return CS_SUCCEED;
  }

/*-----------------------------------------*/
/*  MessageHandler fuer Server - Messages  */
/*-----------------------------------------*/
BOOL IsSevere (CS_INT msg)
  {
  return ((msg != 5701) &&  // server changed to 'master', 
          (msg != 233) &&   // null is not allowed for this collumn
          (msg != 2601) &&  // collumn not unique
          (msg != 3621));   // command has been aborted
  }

DLLExport CS_RETCODE _export FAR PASCAL ex_servermsg_cb(CS_CONTEXT *context, CS_CONNECTION *connection, CS_SERVERMSG *srvmsg)
  {
  if (IsSevere (srvmsg->msgnumber)) {
    LongString errStr;
    errStr = errStr + "Server message:\r\nMessage number: " +
                      srvmsg->msgnumber + ", Severity " + srvmsg->severity +
                      ", State " + srvmsg->state + ", Line " + srvmsg->line ;

    if (srvmsg->svrnlen > 0)
      errStr = errStr + "\r\n (Server '" + srvmsg->svrname + "')" ;
    if (srvmsg->proclen > 0)
      errStr = errStr + "\r\n (Procedure '" + srvmsg->proc + "')" ;
    errStr = errStr + "\r\nMessage: " + srvmsg->text ;

    WIN_ASSERT_TEXT (FALSE,errStr.Ptr());
    }

  return CS_SUCCEED;
  }

/*------------------------------------------------------*/
/* Vorbereiten eines Kommandos und dieses an            */
/* den Server senden                                    */
/*------------------------------------------------------*/
LPVOID sybstmt::GetSybDataType (CS_DATAFMT FAR *fmt,WORD mType,int maxSize,int nRows)
  {
  fmt->count = nRows ;
  switch (mType) {
    case VAR_LONG   :
    case VAR_DWORD  :
      fmt->datatype = CS_INT_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_STRARR :
    case VAR_FLAG   :
      fmt->datatype = CS_SMALLINT_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_DEC    :
      fmt->datatype = CS_REAL_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_STR    :
      if (maxSize > 254)
        fmt->datatype = CS_TEXT_TYPE ;
      else
        fmt->datatype = CS_CHAR_TYPE ;
      fmt->maxlength = maxSize ;
      fmt->format = CS_FMT_NULLTERM ;
      break ;
    case VAR_POINT  :
    case VAR_CONT   :
    case VAR_SCALE  :
    case VAR_OBJ    :
      if (maxSize > 254)
        fmt->datatype = CS_BINARY_TYPE ;
      else
        fmt->datatype = CS_IMAGE_TYPE ;
      fmt->maxlength = maxSize ;
      fmt->format = CS_FMT_UNUSED ;
      break ;
    case VAR_DATE   :
    case VAR_TIME   :
      fmt->datatype = CS_DATETIME_TYPE ;
      fmt->maxlength = sizeof(CS_DATETIME) ;
      fmt->format = CS_FMT_UNUSED ;
      break ;
    }
  return GetGlobMem (int (fmt->maxlength) * nRows);
  }

int sybstmt::nRows (LPTABLEDEF ti)
  {
  if (dbMaxRows == 0) {
    if (RecsToGet > 0)
      dbMaxRows = RecsToGet ;
    else
      dbMaxRows = MAXROWSBUFFERED ;
    // Ausrechnen, wieviel Zeilen maximal platz haetten
    /////////////////////////////////////////////////////
    WIN_ASSERT (ti != NULL) ;
    if (req->AnzElems > 0) {
      for (int i = 0 ; i < int (req->AnzElems) ; i++) {
        LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
        int nMax = int (long (0x7FFF) / long(v->VarSize)) ;
        if (nMax < dbMaxRows) dbMaxRows = nMax ;
        }
      }
    else {
      for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
        LPVARDEF v = ti->GetVarDef(i);
        if (v->VarSize != 0xFFFF) {
          int nMax = int (long (0x7FFF) / long(v->VarSize)) ;
          if (nMax < dbMaxRows) dbMaxRows = nMax ;
          }
        else
          dbMaxRows = 1 ;
        }
      }
    }
  return dbMaxRows ;
  }

int sybstmt::nCols (LPTABLEDEF ti)
  {
  if (dbCols < 0) {
    WIN_ASSERT (ti != NULL) ;
    if (req->AnzElems > 0)
      dbCols = int(req->AnzElems) ;   // Views duerfen keine blocked elemente besitzen
    else {
      BOOL blocked_Done = FALSE ;
      dbCols = 0 ;
      for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
        LPVARDEF v = ti->GetVarDef(i);
        if (v->VarSize != 0xFFFF)
          dbCols ++ ;
        else {
          if (!blocked_Done)
            dbCols ++ ;
          blocked_Done = TRUE ;
          }
        }
      }
    }
  return dbCols ;
  }

void sybstmt::GetColInfo(LPTABLEDEF ti)
  {
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
    BOOL BlockedDone = FALSE ;
    for (int i = 0 ; i < nCols(ti) ; i++) {
      LPVARDEF v;
      if (req->AnzElems > 0)
        v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      else
        v = ti->GetVarDef(i);
      ColInfo[i].VarLen    = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[i].VarLen) * nRows(ti)) ;
      ColInfo[i].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[i].VarIndikat) * nRows(ti)) ;
      if (v->VarSize != 0xFFFF) {
              WIN_ASSERT (!BlockedDone);    // Der geblockte Teil muss hinten stehen
              ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,v->mType,v->VarSize,nRows(ti));
              }
      else {
              WIN_ASSERT (nRows(ti) == 1);    // Nur Get zugelassen
              ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,VAR_OBJ,MAXBLOCKEDSIZE,nRows(ti));
              }
      }
    }
  }

BOOL sybstmt::BindColData (CS_COMMAND *cmd,LPTABLEDEF ti)
  {
  GetColInfo (ti);
  BOOL correct = TRUE ;
  if (ColInfo != NULL) {
    for (int i = 0 ; ((i < nCols(ti)) && (correct)) ; i++) {
      correct = (
              ct_bind (cmd,i+1,&ColInfo[i].VarFormat,ColInfo[i].VarData,
              ColInfo[i].VarLen,ColInfo[i].VarIndikat) == CS_SUCCEED
              ) ;
      }
    }
  return correct;
  }

//
// Ausfueheren eines Kommandos
// Das speichern der Daten uebernehmen dann die
// virtuellen Funktion StoreData (bzw. die Vorbereitung
// dazu BindColData und deren virtuelle Funktionen)
//
CS_RETCODE sybstmt::execute (LPSTR cmdbuf,LPTABLEDEF ti,CS_CONNECTION *con)
  {
  CS_RETCODE      retcode;

#ifdef DOLOG
  LogCmd (cmdbuf);
#endif

  if (con == NULL) con = dbase->connection ;

  if ((retcode = ct_cmd_alloc(con, &cmd)) != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"execute_cmd: ct_cmd_alloc() failed");
    return retcode;
    }
  if ((retcode = ct_command(cmd, CS_LANG_CMD, cmdbuf, CS_NULLTERM,
    CS_UNUSED)) != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"execute_cmd: ct_command() failed");
    ct_cmd_drop(cmd);
    return retcode;
    }
  if ((retcode = ct_send(cmd)) != CS_SUCCEED) {
    WIN_ASSERT ("execute_cmd: ct_send() failed");
    ct_cmd_drop(cmd);
    return retcode;
    }

  /*--- Ueberepruefen der Ergebnisse, bei Fehlern return CS_FAIL --*/
  CS_RETCODE query_code = CS_SUCCEED;
  CS_INT          restype;
  BOOL BindDone = FALSE ;
  while ((retcode = ct_results(cmd, &restype)) == CS_SUCCEED) {
    switch (restype) {
      case CS_CMD_SUCCEED:
      case CS_CMD_DONE:
        break;
      case CS_CMD_FAIL:
        query_code = CS_FAIL;
        break;
      case CS_STATUS_RESULT:
        retcode = ct_cancel(NULL, cmd, CS_CANCEL_CURRENT);
        if (retcode != CS_SUCCEED) {
          WIN_ASSERT_TEXT (FALSE,"execute_cmd: ct_cancel() failed");
          query_code = CS_FAIL;
          }
        break;
      case CS_ROW_RESULT :
        {
        if (!BindDone) {
          BindColData (cmd,ti);
          BindDone = TRUE ;
          }
        CS_RETCODE fetchRet ;
        CS_INT rowsRead ;
        query_code = CS_SUCCEED;
        for ( int rowsGot = 0 ; ; ) {
                  fetchRet = ct_fetch (cmd,CS_UNUSED,CS_UNUSED,CS_UNUSED,&rowsRead) ;
                  if ((fetchRet == CS_SUCCEED) || (fetchRet == CS_ROW_FAIL)) {
                    for (int i = 0 ; i < rowsRead ; i++) {
                      StoreData (ti,i);
                      rowsGot ++ ;
                      }
                    if ((nRowsToGet (ti) > 0) && (rowsGot >= nRowsToGet(ti))) {
                      // Ausstieg, wenn genuegend Datensaetze gelesen wurden
                      ct_cancel (NULL,cmd,CS_CANCEL_CURRENT);
                      query_code = CS_SUCCEED ;
                      break ;
                      }
                    }
                  if ((fetchRet != CS_SUCCEED) && (fetchRet != CS_ROW_FAIL) && (fetchRet != CS_END_DATA)) {
                    // Ausstieg im Fehlerfall
                    query_code = CS_FAIL ;
                    break ;
                    }
                  else {
                    if (fetchRet == CS_END_DATA) {
                      // Ausstieg beim Selektionsende
                      if ((nRowsToGet (ti) > 0) && (rowsGot >= nRowsToGet(ti)))
                        // Ausstieg, wenn genuegend Datensaetze gelesen wurden
                        query_code = CS_SUCCEED ;
                      else
                        query_code = CS_END_DATA ;
                      break ;
                      }
                    else
                      // Weiter gehts
                      query_code = CS_SUCCEED ;
                    }
                  }
                }
                break ;
      default:
                query_code = CS_FAIL;
                break;
      }
    if (query_code == CS_FAIL) {
      retcode = ct_cancel(NULL, cmd, CS_CANCEL_ALL);
      if (retcode != CS_SUCCEED) {
                WIN_ASSERT_TEXT (FALSE,"execute_cmd: ct_cancel() failed");
                }
      break;
      }
    }

  /*
  ** handle aufraeumen
  */
  if (retcode == CS_END_RESULTS) {
    retcode = ct_cmd_drop(cmd);
    if (retcode != CS_SUCCEED) {
      query_code = CS_FAIL;
      }
    }
  else {
    ct_cmd_drop(cmd);
    query_code = CS_FAIL;
    }

  return query_code;
  }

void tablecheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(t0)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_STR,64,nRows(t0));
    }
  }

void colcheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (2 * sizeof(*ColInfo));
    ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(t0)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_STR,64,nRows(t0));
    ColInfo[1].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarLen) * nRows(t0)) ;
    ColInfo[1].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarIndikat) * nRows(t0)) ;
    ColInfo[1].VarData    = GetSybDataType (&ColInfo[1].VarFormat,VAR_STRARR,2,nRows(t0));
    }
  }

void tablecheck::StoreData (LPTABLEDEF ti,int row)
  {
  LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int size = int (ColInfo[0].VarLen[row]);
  if (ColInfo[0].VarIndikat[row] != CS_NULLDATA) {
    TableData d;
    d.IsTested = FALSE ;
    dbase->TableHash->SetData (LPSTR(data),&d,sizeof(d));
    }
  }

void colcheck::StoreData (LPTABLEDEF ti,int row)
  {
  LPSTR str = LPSTR (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int size = int (ColInfo[0].VarLen[row]);
  int FAR *lpType = (int FAR *) (LPSTR (ColInfo[1].VarData) + row * ColInfo[1].VarFormat.maxlength) ;
  int size_1 = int (ColInfo[1].VarLen[row]);
  if ((ColInfo[0].VarIndikat[row] != CS_NULLDATA) &&
      (ColInfo[1].VarIndikat[row] != CS_NULLDATA)) {
    char VarName[128];
    lstrcpy (VarName,str);
    AnsiUpper (VarName);
    colhash->SetData (VarName,lpType,size_1);
    }
  }

LPSTR GetUseString (LPSTR str)
  {
  lstrcpy (str,"USE ") ;
  char dbname[32];
  GetPrivateProfileString ("Sybase","DBName","CLINICUM",dbname,sizeof(dbname),GetIniName());
  lstrcat (str,dbname);

  return str;
  }

void sybase::FetchTableNames ()
  {
  tablecheck *h = new tablecheck ();
  char ustr[64];
  h->execute (GetUseString(ustr),NULL);
  h->execute ("SET TEXTSIZE 2097152",NULL);
  h->execute ("EXEC CLTABLES",NULL);
  }

//
// Initialisieren der Clientlib
//
CS_RETCODE sybase::Init ()
#define EX_CTLIB_VERSION        CS_VERSION_100

#define MAXVARSIZE 0x8000
  {
        CS_RETCODE retcode = cs_ctx_alloc(EX_CTLIB_VERSION, &context);
        if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"init: cs_ctx_alloc() failed");
    return retcode ;
    }
        retcode = ct_init(context, EX_CTLIB_VERSION);
        if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"init: ct_init() failed");
    cs_ctx_drop(context);
    context = NULL;
    return retcode;
    }
  retcode = ct_callback(context, NULL, CS_SET, CS_CLIENTMSG_CB,
                          (CS_VOID *)ex_clientmsg_cb);
  if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"init: ct_callback(clientmsg) failed");
    return retcode ;
    }
  retcode = ct_callback(context, NULL, CS_SET, CS_SERVERMSG_CB,
      (CS_VOID *)ex_servermsg_cb);
  if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT (FALSE,"init: ct_callback(servermsg) failed");
    return retcode ;
    }
  return retcode ;
  }

CS_RETCODE sybase::Connect (LPSTR username, LPSTR password,LPSTR appname)
  {
  CS_RETCODE    retcode;

  retcode = ct_con_alloc(context, &connection);
  if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT(FALSE,"ct_con_alloc failed");
    }

  if ((retcode == CS_SUCCEED) && (username != NULL)) {
    if ((retcode = ct_con_props(connection, CS_SET, CS_USERNAME, 
         username, CS_NULLTERM, NULL)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"ct_con_props(username) failed");
      }
    }

  if ((retcode == CS_SUCCEED) && (password != NULL)) {
    if ((retcode = ct_con_props(connection, CS_SET, CS_PASSWORD, 
                password, CS_NULLTERM, NULL)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"ct_con_props(password) failed");
      }
    }

  if ((retcode == CS_SUCCEED) && (appname != NULL)) {
    if ((retcode = ct_con_props(connection, CS_SET, CS_APPNAME, 
          appname, CS_NULLTERM, NULL)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"ct_con_props(appname) failed");
      }
    }

  if (retcode == CS_SUCCEED) {
    retcode = ct_connect(connection, NULL, 0);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"ct_connect failed");
      }
    }

  if (retcode != CS_SUCCEED) {
    ct_con_drop(connection);
    connection = NULL;
    }
  return retcode;
  }

sybase::sybase (LPSTR _username,LPSTR _password,LPSTR _appname) 
  {
  CS_RETCODE retcode;
  if ((retcode = Init ()) == CS_SUCCEED)
    retcode = Connect (_username,_password,_appname);
  if (retcode == CS_SUCCEED) {
    TableHash = new hash (111,STRKEY);
    dbase = this ;
    FetchTableNames ();
    }
  }

sybase::~sybase () 
  {
  CS_RETCODE    retcode;

  if (connection != NULL) {
    retcode = ct_close(connection, CS_FORCE_CLOSE);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"cleanup: ct_close() failed");
      return ;
      }
    retcode = ct_con_drop(connection);
    if (retcode != CS_SUCCEED) {
        WIN_ASSERT_TEXT(FALSE,"cleanup: ct_con_drop() failed");
        return ;
      }
    }

  if (context != NULL) {
    retcode = ct_exit(context, CS_FORCE_EXIT);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"cleanup: ct_exit() failed");
      return ;
      }
    retcode = cs_ctx_drop(context);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"cleanup: cs_ctx_drop() failed");
      return ;
      }
    }
  }

//
// Aufrauem - Prozedur:
//   Diese Funktion wird u.U zwei mal aufgerufen:
//   bei einem regulaeren Ausstieg durch DBReset
//   und auf jeden FALL durch den WEP! (fuer den
//      Fall das das Programm durch GP - Fehler abstuerzt)
//   d.h.:
//   die Funktion muss 2 maligen Einsprung zulassen, ohne
//   dadurch Fehler zu erzeugen
//
DLLExport void _export FAR PASCAL DisConnect ()
  {
  if (dbase != NULL)
    delete dbase;
  dbase = NULL ;
  }

// 
// Ermitteln des Typbezeichners eines Feldes, inkl. Angabe,
// ob eine Groesse beim Create - Statement verlangt wird.
// dabei kann durch k0 untersucht werden, ob es sich um ein
// AUTOINC Feld handelt.
//
LPSTR sybase::GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0)
  {
  *doSize = FALSE ;
  switch (v->mType) {
    case VAR_LONG :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC))
        return "NUMERIC(10,0) IDENTITY" ;
      else
        return "INT" ;
      break ;
    case VAR_DEC :
      return "REAL" ;
      break ;
    case VAR_STR :
      if (v->VarSize > 254)
        return "TEXT" ;
      else {
              *doSize = TRUE ;
              return "VARCHAR" ;
              }
      break ;
    case VAR_POINT :
      *doSize = TRUE ;
      return "BINARY" ;
      break ;
    case VAR_CONT :
      return "IMAGE" ;
      break ;
    case VAR_STRARR :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC))
        return "NUMERIC(5,0) IDENTITY" ;
      else
        return "SMALLINT" ;
      break ;
    case VAR_FLAG :
      return "SMALLINT" ;
      break ;
    case VAR_SCALE :
      *doSize = TRUE ;
      return "BINARY" ;
      break ;
    case VAR_DATE :
      return "DATETIME" ;
      break ;
    case VAR_OBJ :
      if (v->VarSize > 254)
        return "IMAGE" ;
      else {
        *doSize = TRUE ;
        return "BINARY" ;
        }
      break ;
    case VAR_TIME :
      return "DATETIME" ;
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  return NULL;
  }
LPSTR sybase::BlockVarName ()
  {
  return "XXXBlockedXXX" ;
  }
LPSTR sybase::BlockTypeName ()
  {
  return "IMAGE" ;
  }

BOOL sybase::TestTableDef (LPTABLEDEF td)
  {
  colcheck FAR *cc = new colcheck ();
  LongString s ;
  s = s + "EXEC CLCOLS '" + td->GetName () + "'" ;
  cc->execute (s.Ptr(),NULL) ;
  BOOL blockedDone = FALSE ;
  BOOL res = TRUE ;
  for (int i = 0 ; ((i < td->GetAnzVars ()) && (res)) ; i++) {
    char VarName[128];
    *VarName = '\0';
    LPVARDEF v = td->GetVarDef(i);
    if (v->VarSize != 0xFFFF) {
      lstrcpy (VarName,GetAliasName (v->GetName()));
      }
    else {
      if (!blockedDone) {
        lstrcpy (VarName,BlockVarName()) ;
        }
      blockedDone = TRUE ;
      }
    if (*VarName) {
      AnsiUpper (VarName);
      int FAR *d = (int FAR *) cc->colhash->GetData (VarName);
      if (d == NULL) res = FALSE ;    // Datentypvergleich wird (vorerst) 
                                      // keiner gemacht !!!!!!!!
      cc->colhash->DelData (VarName);     // Variable aus der Hashtabelle
                                      // entfernen, da fertig gecheckt
      }
    }
  // Nachsehen, ob wohl nicht zuviele Elemente in der Datenbank definiert
  // sind
  if (res) res = cc->colhash->IsHashEmpty ();
  delete cc ;
  return res;
  }

void sybase::CreateTable (LPTABLEDEF td)
  {
  sybstmt *h = new sybstmt ();

  LongString s,c;
  s = s + "CREATE TABLE " + td->GetName() + "(";
  // CreateTableStatement...
  BOOL blockDone = FALSE ;
  BOOL first = TRUE ;
  for (int i = 0 ; i < td->GetAnzVars() ; i++) {
    LPVARDEF v = td->GetVarDef(i);
    if (v->VarSize != 0xFFFF) {
      if (!first)
            s = s + "," ;
      BOOL doSize;
      s = s + GetAliasName(v->GetName()) + " " + GetTypeName (v,i,&doSize,td->GetKeyDef(0));
      if (doSize) {
              int size = v->VarSize;
              s = s + "(" + size + ")" ;
        }
      if ((v->Property & VPROP_NOTNULL) != 0)
              s = s + " NOT NULL" ;
      else if (IsChar (v->mType))
        s = s + " NULL" ;
      }
    else {
      if (!blockDone) {
              if (!first)
                s = s + "," ;
              s = s + BlockVarName() + " " + BlockTypeName();
              blockDone = TRUE ;
              }
      }
    first = FALSE ;
    }
  s = s + ")" ;

  h->execute (s.Ptr(),NULL);

  // CreateIndexStatements...
  WORD oldKeyNr = 0xFFFF;
  first = TRUE ;
  for (i = 0 ; ; i++) {
    LPCLKEYDEF k = (i < td->GetAnzKeySegs()) ? td->GetKeyDef (i) : NULL ;
    if ((k == NULL) || (k->KeyNmbr != oldKeyNr)) {
      if (!first) {
              c = c + ")" ;
              h->execute (c.Ptr(),NULL);
              }
      if (k != NULL) {
              c.Clear ();
              LPVARDEF v = td->GetVarDef (k->VarID);
              c = c + "CREATE " ;
              if ((k->Attribute & CLKD_UNIQUE) != 0)
                c = c + "UNIQUE " ;
              if ((k->Attribute & CLKD_CLUSTERED) != 0)
                c = c + "CLUSTERED " ;
              c = c + "INDEX " + k->name + " ON " + td->GetName() + "(" + GetAliasName(v->GetName()) ;
              oldKeyNr = k->KeyNmbr;
              }
      else
              break ;
      }
    else {
      LPVARDEF v = td->GetVarDef (k->VarID);
      c = c + "," + GetAliasName(v->GetName()) ;
      }
    first = FALSE ;
    }
  delete h ;
  }

void sybase::TestTable (LPTABLEDEF td)
  {
  TableData FAR *d = (TableData FAR *) TableHash->GetData (td->GetName());
  if (d != NULL) {
    if (!d->IsTested) {
      if (!TestTableDef (td)) {
        char outtxt[256];
        sprintf (outtxt,"Tabelle %s stimmt nicht mit der Clientdefinition überein!",td->GetName());
        WIN_ASSERT_TEXT(FALSE,outtxt);
        }
      d->IsTested = TRUE ;
      }
    }
  else {
    // Die Tabelle gibts noch nicht -> Vater informieren
    char outtxt[256];
    sprintf (outtxt,"Tabelle %s nicht definiert! Contiune zum Erstellen der Tabelle",td->GetName());
    WIN_ASSERT_TEXT(FALSE,outtxt);
    CreateTable (td);
    TableData di;
    di.IsTested = TRUE ;
    TableHash->SetData (td->GetName(),&di,sizeof(di));
    }
  }

/*--------< Verwaltung eines Statements >---------*/
static char *UserName   = "sa";
static char *PassWord   = "";
static char *AppName    = "SW - CLINICUM";

void CheckFile (LPSYBSTMT stmt,BOOL first)
  {
  if (dbase == NULL)
    // Login to sybase
    dbase = new sybase (UserName,PassWord,AppName);
  if (first) {
    for (int i = 0 ; i < int(stmt->req->AnzTables) ; i++) {
      if (stmt->req->TableDef[i] != NULL) 
        dbase->TestTable (stmt->req->TableDef[i]);
      }
    }
  }

void CloseAllDataFiles ()
  {
  WIN_ASSERT (AnzOpenStatements == 0);
  if (dbase != NULL)
    delete dbase ;
  }

int sybstmt::StandardDelete ()
  {
  LongString s,w;
  LPTABLEDEF td = req->TableDef[0];

  LPSTR seq = w.AnalyseSeq (req->SelectionName,td,req,FALSE) ;
  s = s + "DELETE FROM " + td->GetName() ;
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;

  CS_RETCODE ret = execute (s.Ptr(),td);

  return (ret == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_ERROR ;
  }

#pragma optimize("", off)
void sybstmt::SelectStatement (LPTABLEDEF ti,LongString FAR &s,int KeyNmbr)
  {
  if (req->AnzElems > 0) {
    // Auf jeden Fall mit alias Namen fuer Tabellen arbeiten
    s = s + "SELECT " ;
    BOOL BlockedDone[CB_TABLEDEF];
    lmemset (BlockedDone,'\0',sizeof(BlockedDone));
    for (int i = 0 ; i < req->AnzElems ; i++) {
      int tnr = req->elem[i].TableNumber ;
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      if (i > 0) s = s + "," ;
      if (v->VarSize != 0xFFFF) {
              s = s + "t" + tnr + "." +
                      dbase->GetAliasName(v->GetName()) ;
        }
      else {
              if (!BlockedDone[tnr]) {
                s = s + "t" + tnr + "." +
                      dbase->BlockVarName ();
                BlockedDone[tnr] = TRUE ;
                }
              }
      }
    s = s + " FROM " ;
    for (i = 0 ; i < int (req->AnzTables) ; i++) {
      if (i > 0) {
              s = s + "," ;
              }
      s = s + req->TableDef[i]->GetName() + " t" + i;
      if (KeyNmbr >= 0)
        s = s + "(" + KeyNmbr + ")" ;
      }
    }
  else {
    s = s + "SELECT * FROM " ;
    for (int i = 0 ; i < int (req->AnzTables) ; i++) {
      if (i > 0) {
              s = s + "," ;
              }
      s = s + req->TableDef[i]->GetName() + " t" + i;
      if (KeyNmbr >= 0)
        s = s + "(" + KeyNmbr + ")" ;
      }
    }
  }

void sybstmt::WhereStatement (LongString FAR &s,LPTABLEDEF td,LPTABLEDEF ti,BOOL FAR &wheredone,BOOL useOld)
  {
  wheredone = FALSE ;
  LongString w;
  LPSTR seq = w.AnalyseSeq (req->SelectionName,td,req,TRUE,useOld,this);
  int offs = s.size();
  LPSTR JoinSel[CB_TABLEDEF];
  for (int i = 0 ; i < CB_TABLEDEF ; i++)
    JoinSel[i] = NULL ;
  if ((seq != NULL) && (*seq)) {
    s = s + " WHERE " + seq ;
    wheredone = TRUE ;
    }
  // Noch die Joins dazu
  BOOL UseOuter[CB_TABLEDEF] ;
  for (i = 0 ; i < CB_TABLEDEF ; i++)
    UseOuter[i] = FALSE ;
  for (i = 1 ; i < int (req->AnzTables) ; i++) {
    LongString js;
    if (wheredone)
      s = s + " AND (" ;
    else
      s = s + " WHERE (" ;
    LPCLRIDEF r = ti->GetRIDef(i-1) ;
    switch (r->TypeOfJoin) {
      case CLJT_USEDEFAULT :
        UseOuter[i] = IsNullAllowed(req,ti,ti->GetRIDef(i-1));
        break ;
      case CLJT_USEINNERJOIN :
        UseOuter[i] = FALSE ;
        break ;
      case CLJT_USEOUTERJOIN :
        UseOuter[i] = TRUE ;
        break ;
      default :
        WIN_ASSERT (FALSE) ;
      }
    s = s + js.AnalyseJoin (req,ti,i,r,JoinSel,UseOuter) + ")";
    if (UseOuter[i]) {
      // Diese Tabelle ist durch einen Outerjoin dazu gekommen ->
      // das Wherestatement merken, um ev. spaeter ein Subselect absetzen zu 
      // koennen
      ///////////////////////////////////////////////////////////////////////
      JoinSel[i] = LPSTR(GetGlobMem (s.size() - offs + 1)) ;
      lmemcpy (JoinSel[i],s.Ptr() + offs,s.size() - offs);
      }
    wheredone = TRUE ;
    }
  for (i = 0 ; i < CB_TABLEDEF ; i++)
    if (JoinSel[i] != NULL) FreeGlobMem (JoinSel[i]) ;
  }

void sybstmt::OrderStatement (LongString FAR &s,LPTABLEDEF td,BOOL descending)
  {
  LongString o;
  LPSTR os ;
  char PrimKeyOrder[256];
  if ((req->OrderStatement == NULL) || (*req->OrderStatement == '\0')) {
    *PrimKeyOrder = '\0' ;
    WORD KeySeg[MAX_PRIMARYSEGS] ;
    WIN_ASSERT(td->GetPrimKeySegs (KeySeg));
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      if (KeySeg[i] == 0xFFFF) break ;
      if (*PrimKeyOrder) lstrcat (PrimKeyOrder,",");
      lstrcat (PrimKeyOrder,td->GetVarDef(KeySeg[i])->GetName());
      }
    os = PrimKeyOrder;
    }
  else
    os = req->OrderStatement ;
  LPSTR order = o.AnalyseSeq (os,td,req);
  LongString r;
  if (descending) {
    order = r.InsertDescending (order);
    }
  if ((order != NULL) && (*order))
    s = s + " ORDER BY " + order ;
  }

void sybstmt::SyncStatement (LongString FAR &w,LPDBREQUEST req,LPTABLEDEF td,LPSTR connect,BOOL whereDone)
  {
  LongString o;
  LPSTR os ;
  char PrimKeyOrder[256];
  if ((req->OrderStatement == NULL) || (*req->OrderStatement == '\0')) {
    *PrimKeyOrder = '\0' ;
    WORD KeySeg[MAX_PRIMARYSEGS] ;
    WIN_ASSERT(td->GetPrimKeySegs (KeySeg));
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      if (KeySeg[i] == 0xFFFF) break ;
      if (*PrimKeyOrder) lstrcat (PrimKeyOrder,",");
      lstrcat (PrimKeyOrder,td->GetVarDef(KeySeg[i])->GetName());
      }
    os = PrimKeyOrder;
    }
  else
    os = req->OrderStatement ;
  LPSTR sync = o.AnalyseSeq (os,td,req);

  LongString r;
  BOOL doAnd = whereDone ;
  if (!whereDone)
    w = w + " WHERE " ;
  sync = r.InsertSyncCond (sync,req,connect,doAnd);

  if ((sync != NULL) && (*sync))
    w = w + sync ;
  }
#pragma optimize("", on)

LPVOID sybstmt::ConvertToMData (LPVARDEF v,LPVOID data,int Size,int FAR *rSize)
  {
  static char AchtNullen[8];
  switch (v->mType) {
    case VAR_STR :
      if ((Size == 1) && (*(LPSTR) data == '\0')) return NULL ;
      else {
        *rSize = int (Size) ;
        return data ;
        }
      break ;
    case VAR_DATE :
      if (!lmemcmp (data,AchtNullen,sizeof(AchtNullen))) {
        CS_DATEREC r;
        cs_dt_crack (dbase->context,CS_DATETIME_TYPE,data,&r);
        static packdate res;
        res.year = WORD(r.dateyear) ;
        res.month = BYTE(r.datemonth + 1) ;
        res.day = BYTE(r.datedmonth) ;
        *rSize = sizeof(res);
        return &res ;
        }
      else
        return NULL ;
      break ;
    case VAR_TIME :
      if (!lmemcmp (data,AchtNullen,sizeof(AchtNullen))) {
        CS_DATEREC r;
        cs_dt_crack (dbase->context,CS_DATETIME_TYPE,data,&r);
        static packtime res;
        res.hour = BYTE(r.datehour) ;
        res.minute = BYTE(r.dateminute) ;
        res.second = BYTE(r.datesecond) ;
        res.hundred_second = 0 ;
        *rSize = sizeof(res);
        return &res ;
        }
      else
        return NULL ;
      break ;
    default :
      *rSize = int(Size) ;
      return data ;
      break ;
    }
  return NULL ;
  }

LPVOID sybstmt::FindData (LPVOID BlockData,WORD VarID,int FAR *Size)
  {
  MBlockHeader FAR *hd = (MBlockHeader FAR *) BlockData ;
  MBlockVarHeader FAR *vhd = (MBlockVarHeader FAR *) (hd + 1) ;
  for (WORD i = 0 ; i < hd->AnzVars ; i++) {
    if (vhd->VarID == VarID) {
      *Size = int (vhd->VarSize) ;
      return (vhd + 1) ;
      }
    vhd = (MBlockVarHeader FAR *) (LPSTR (vhd + 1) + vhd->VarSize);
    }
  return NULL ;
  }

void sybstmt::PushToBlocked (LPVOID Data,WORD VarID)
  {
  WORD nSize,oSize;
  if (BlockedData != NULL) {
    nSize = GetBlockSize (BlockedData) + GetBlockSize (Data) + sizeof (MBlockVarHeader) ;
    oSize = GetBlockSize (BlockedData) ;
    }
  else {
    nSize = sizeof(MBlockHeader) + GetBlockSize (Data) + sizeof (MBlockVarHeader) ;
    oSize = sizeof(MBlockHeader) ;
    }
  WIN_ASSERT (nSize <= MAXBLOCKEDSIZE);
  LPVOID nwBlockedData = GetGlobMem (nSize);
  if (BlockedData != NULL) {
    lmemcpy (nwBlockedData,BlockedData,oSize);
    FreeGlobMem (BlockedData);
    }
  MBlockHeader FAR *hd = (MBlockHeader FAR *) nwBlockedData ;
  MBlockVarHeader FAR *vhd = (MBlockVarHeader FAR *) (LPSTR (nwBlockedData) + oSize) ;
  hd->AnzVars += 1;
  hd->BlockSize = nSize;
  vhd->VarID = VarID;
  vhd->VarSize = GetBlockSize (Data);
  lmemcpy (vhd+1,Data,GetBlockSize (Data));

  BlockedData = nwBlockedData ;
  }

LPDBRECORD sybstmt::StoreRow (LPTABLEDEF ti,int row)
  {
  LPDBRECORD rec = new DBRecord (req);
  if (req->AnzElems > 0) {
    // Stueck fuer Stueck aus den echten Tabellen abholen
    for (int i = 0 ; (i < int(req->AnzElems)) ; i++) {
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      LPVOID data = LPVOID (LPSTR (ColInfo[i].VarData) + row * ColInfo[i].VarFormat.maxlength) ;
      if (ColInfo[i].VarIndikat[row] != CS_NULLDATA) {
        int size = int (ColInfo[i].VarLen[row]);
        int rLen;
        LPVOID cd = ConvertToMData (v,data,size,&rLen);
        if (cd != NULL)
          rec->Initialize (i,cd,rLen);
        }
      }
    }
  else {
    // Stueck fuer Stueck aus ti abholen
    for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
      LPVARDEF v = ti->GetVarDef(i);
      if (v->VarSize != 0xFFFF) {
        LPVOID data = LPVOID (LPSTR (ColInfo[i].VarData) + row * ColInfo[i].VarFormat.maxlength) ;
        if (ColInfo[i].VarIndikat[row] != CS_NULLDATA) {
          int size = int (ColInfo[i].VarLen[row]);
          int rLen;
          LPVOID cd = ConvertToMData (v,data,size,&rLen);
          if (cd != NULL)
            rec->Initialize (i,cd,rLen);
          }
        }
      else {
        // Information aus dem geblockten Teil holen
        ///////////////////////////////////////////////////
        LPVOID data = LPVOID (LPSTR (ColInfo[nCols(ti)-1].VarData) + row * ColInfo[nCols(ti)].VarFormat.maxlength) ;
        int size = int (ColInfo[nCols(ti)-1].VarLen[row]);
        if (size > 0) {
          int rLen;
          LPVOID d_int = FindData (data,v->VarID,&rLen);
          if (d_int != NULL)
            rec->Initialize (i,d_int,rLen);
          }
        }
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  return rec;
  }

void sybstmt::StoreData (LPTABLEDEF ti,int row)
  {
  res->AddLine (1,((Op == DBOP_GETNEXT) || (Op == DBOP_GETFIRST)) ? ADDLINEPOS_END : ADDLINEPOS_START);
  res->SetRes (0,StoreRow (ti,row));
  }

void liststmt::GetColInfo(LPTABLEDEF ti)
  {
  doNext = doIt = FALSE ;
  if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) {
    kLast.SetKeyNull();
    kLast.PushKeySeg (req->Param[0],GetBlockSize(req->Param[0]));
    }
  sybstmt::GetColInfo (ti);
  }

void liststmt::StoreData (LPTABLEDEF ti,int row)
  {
  LPDBRECORD rec = StoreRow (ti,row);
  if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) {
    if (!doNext) {
      doNext = (kLast == *rec->GetPrimKey ());
      }
    }
  else
    doIt = TRUE ;
  if (doIt) {
    res->AddLine (1,((Op == DBOP_GETNEXT) || (Op == DBOP_GETFIRST)) ? ADDLINEPOS_END : ADDLINEPOS_START);
    res->SetRes (0,rec);
    }
  else
    delete rec ;
  doIt = doIt || doNext ;
  }

void insstmt::StoreData (LPTABLEDEF ti,int row)
  {
  LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  if (ColInfo[0].VarIndikat[row] != CS_NULLDATA) {
    int size = int (ColInfo[0].VarLen[row]);
    res->AddLine (1,ADDLINEPOS_END);
    res->SetRes (0,GetRecCopy (old,va,data,int(size)));
    }
  }

void insstmt::GetColInfo(LPTABLEDEF t0)
  {
  LPVARDEF v;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  if (ti == req->TableDef[0]) {
    va = k0->VarID;
    v = ti->GetVarDef (va);
    }
  else {
    for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
      ReqElem e;
      ti->GetReqElem (&e,i);
      if (e.VarID == k0->VarID) {
        va = i ;
        v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
        break ;
        }
      }
    }
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(t0)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,v->mType,v->VarSize,nRows(t0));
    }
  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  }

int sybstmt::StandardGet ()
  {
  LongString s;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());

  SelectStatement (ti,s);
  BOOL wheredone;
  WhereStatement (s,req->TableDef[0],ti,wheredone);

  RecsToGet = 1 ;
  CS_RETCODE retcode = execute (s.Ptr(),ti);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  if (retcode == CS_SUCCEED) 
    return DBCALL_SUCCESS ;
  else if (retcode == CS_END_DATA) 
    return DBCALL_NODATA ;
  else
    return DBCALL_ERROR ;
  }

int sybstmt::StandardInsert ()
  {
  LongString s,v;
  s = s + "INSERT INTO " + req->TableDef[0]->GetName() + " (" ;
  v = v + ") VALUES (" ;
  int correct = TRUE ;
  int AnzPars = 0;
  LPTABLEDEF ti = req->TableDef[0] ;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
              LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
              correct = EnlargeInsert (vd,i,s,v,&AnzPars);
              }
      }
    }
  else {
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeInsert (vd,i,s,v,&AnzPars);
      }
    }
  correct = EnlargeInsert_Blocked (s,v,&AnzPars);
  s = s + LPSTR(v.Ptr()) + ")";

  CS_RETCODE retcode = execute (s.Ptr(),ti);

  old = res->first->rec[0];

  // Den eingefuegten Datensatz entfernen
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;

  if (retcode == CS_SUCCEED) {
    k0 = req->TableDef[0]->GetKeyDef(0);
    if (k0->Attribute & CLKD_AUTOINC) {
      // Der Wert der Autoinc variable muss noch gefuellt werden
      LPVARDEF vd = req->TableDef[0]->GetVarDef (k0->VarID);
      LongString m;
      m = m + "SELECT MAX(" + vd->GetName() + ") FROM " + req->TableDef[0]->GetName();

      retcode = execute (m.Ptr(),ti);
      }
    }
  return (retcode == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

BOOL IsExecute (LPSTR seq)
  {
  int len;
  return mystrmcp (seq,"EXEC",&len);
  }

int sybstmt::StandardList (BOOL first)
  {
  LongString s,w;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  if (IsExecute (req->SelectionName)) {
    // Es ist eine stored - procedure angegeben
    s.AnalyseSeq (req->SelectionName,NULL,req,FALSE);
    }
  else {
    // Den Rowcount setzen
    s = s + "SET ROWCOUNT " + nRows(ti) ;
    execute (s.Ptr(),ti);
    s.Clear ();

    BOOL wheredone;
    WhereStatement (w,req->TableDef[0],ti,wheredone,((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)));
    if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV))
      SyncStatement (w,req,req->TableDef[0],(Op == DBOP_GETPREV) ? "<=" : ">=",wheredone) ;
    SelectStatement (ti,s);
    s = s + LPSTR(w.Ptr());
    OrderStatement (s,req->TableDef[0],((Op == DBOP_GETPREV) || (Op == DBOP_GETLAST)));
    }

  CS_RETCODE retcode = execute (s.Ptr(),ti);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

  if (retcode == CS_SUCCEED)
    return DBCALL_SUCCESS ;
  else if (retcode == CS_END_DATA)
    return DBCALL_ENDOFFILE ;
  else
    return DBCALL_ERROR ;
  }

#pragma optimize("", off)
BOOL sybstmt::EnlargeInsert (LPVARDEF vd,int VarNr,LongString FAR &s,LongString FAR &v,int FAR *AnzPars)
  {
  LPVOID Data = res->first->rec[0]->Get(VarNr);
  BOOL correct = TRUE ;
  if (Data != NULL) {
    if (vd->VarSize != 0xFFFF) {
      if (*AnzPars > 0) {
              s = s + "," ;
              v = v + "," ;
              }
      s = s + dbase->GetAliasName(vd->GetName()) ;
      BOOL doFree ;
      LPSTR r = GetVarString (Data,vd->mType,&doFree,vd->VarSize) ;
      correct = (r != NULL) ;
      if (correct) {
              v = v + r ;
              if (doFree) FreeGlobMem (r) ;
              (*AnzPars) ++ ;
              }
      }
    else {
      PushToBlocked (Data,vd->VarID);
      }
    }
  return correct ;
  }
BOOL sybstmt::EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars)
  {
  BOOL correct = TRUE ;
  if (BlockedData != NULL) {
    if (*AnzPars > 0) {
      s = s + "," ;
      v = v + "," ;
      }
    s = s + dbase->BlockVarName ();
    BOOL doFree ;
    LPSTR r = GetVarString (BlockedData,VAR_OBJ,&doFree,-1) ;
    correct = (r != NULL) ;
    if (correct) {
      v = v + r ;
      if (doFree) FreeGlobMem (r) ;
      (*AnzPars) ++ ;
      }
    }
  return correct ;
  }
#pragma optimize("", on)

LPDBRECORD sybstmt::GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize)
  {
  LPDBRECORD rec = new DBRecord (req);
  for (int i = 0 ; i < int(old->GetAnzVars()) ; i++) {
    if ((i == PrimkeyID) && (PrimKeyData != NULL))
      rec->Initialize (i,PrimKeyData,PrimKeySize);
    else {
      LPVOID data = old->Get(i);
      if (data != NULL)
        rec->Initialize (i,data,GetBlockSize(data));
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  return rec;
  }

BOOL IsModifiable (LPVARDEF v,int vID,LPCLKEYDEF k0)
  {
  switch (v->mType) {
    case VAR_LONG :
    case VAR_STRARR :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC)) return FALSE ;
    default :
      return TRUE ;
    }
  }
#pragma optimize("", off)
BOOL sybstmt::EnlargeUpdate (LPVARDEF vd,int VarID,LongString FAR &s,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0)
  {
  if (!IsModifiable(vd,VarID,k0)) return TRUE ;
  LPVOID Data = res->first->rec[0]->Get(VarID);
  BOOL correct = TRUE ;
  if (vd->VarSize != 0xFFFF) {
    if (Data != NULL) {
      if (!first)
              s = s + "," ;
      BOOL doFree ;
      LPSTR vstring = GetVarString (Data,vd->mType,&doFree,vd->VarSize);
      if (vstring != NULL) {
              s = s + dbase->GetAliasName(vd->GetName()) + " = " + vstring ;
              if (doFree)
                FreeGlobMem (vstring);
              (*AnzPars) ++ ;
              correct = TRUE ;
              }
      else
        correct = FALSE ;
      }
    else {
      if (!first)
        s = s + "," ;
      s = s + dbase->GetAliasName(vd->GetName()) + " = NULL";
      correct = TRUE ;
      }
    first = FALSE ;
    }
  else {
    if (Data != NULL)
      PushToBlocked (Data,vd->VarID);
    ThereAreBlockedData = TRUE ;
    }
  return correct ;
  }
BOOL sybstmt::EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first)
  {
  BOOL correct = TRUE ;
  if (BlockedData != NULL) {
    if (!first)
      s = s + "," ;
    BOOL doFree ;
    LPSTR vstring = GetVarString (BlockedData,VAR_OBJ,&doFree,-1);
    if (vstring != NULL) {
      s = s + dbase->BlockVarName () + " = " + vstring ;
      if (doFree)
        FreeGlobMem (vstring);
      (*AnzPars) ++ ;
      correct = TRUE ;
      }
    else
      correct = FALSE ;
    }
  else {
    if (ThereAreBlockedData) {
      if (!first)
        s = s + "," ;
      s = s + dbase->BlockVarName () + " = NULL";
      correct = TRUE ;
      }
    }
  first = FALSE ;
  return correct ;
  }
#pragma optimize("", on)

int sybstmt::StandardUpdate ()
  {
  LongString s,w;
  s = s + "UPDATE " + req->TableDef[0]->GetName() + " SET " ;
  BOOL correct = TRUE ;
  int AnzPars = 0;
  BOOL first = TRUE ;
  LPCLKEYDEF k0 = req->TableDef[0]->GetKeyDef(0);
  LPTABLEDEF ti = req->TableDef[0] ;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
        LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
        correct = EnlargeUpdate (vd,i,s,&AnzPars,first,k0);
        }
      }
    }
  else {
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeUpdate (vd,i,s,&AnzPars,first,k0);
      }
    }
  correct = EnlargeUpdate_Blocked (s,&AnzPars,first);
  // Where Buffer
  LPSTR seq = w.AnalyseSeq (req->SelectionName,req->TableDef[0],req,FALSE) ;
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;

  CS_RETCODE retcode = execute (s.Ptr(),ti);

  // Die Zeile auf jeden Fall rausnehmen...
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;

  return (retcode == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

int sybstmt::StandardExcute ()
  {
  LongString s;
  LPSTR seq = s.AnalyseSeq (req->SelectionName,NULL,req,FALSE) ;

  CS_RETCODE retcode = execute (s.Ptr(),NULL);

  return (retcode == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

DLLExport int _export FAR PASCAL DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  switch (Op) {
    case DBOP_RESET :
      // Statement wieder freigeben
      if (*hstmt != NULL) {
              LPSYBSTMT stmt = LPSYBSTMT (*hstmt);
              delete stmt;
              *hstmt = NULL ;
              }
      return DBCALL_SUCCESS;
    default :
      LPSYBSTMT stmt = LPSYBSTMT (*hstmt);
      // Laufende Initialisierungen
      BOOL first ;
      if (stmt == NULL) {
              if (req->Type == DBCALLTYPE_STANDARDINSERT)
                stmt               = new insstmt();
              else if (req->Type == DBCALLTYPE_GETLIST)
                stmt               = new liststmt();
              else
                stmt               = new sybstmt();
              *hstmt             = stmt;
              first              = TRUE ;
              }
      else
        first              = FALSE ;
      stmt->retVal         = DBCALL_ERROR_NOACCESS;
      stmt->req            = req;
      stmt->Op             = Op;
      stmt->RecsToGet      = AnzLines;
      stmt->res            = res;
      CheckFile (stmt,first);
      if (req->Type == DBCALLTYPE_TEST)
        return DBCALL_SUCCESS ;

      if (!req->foreignDone)
        req->BuildForeign ();   // Und noch die Fremdzugriffe ...
      
      switch (req->Type) {
              case DBCALLTYPE_STANDARDDELETE :
                stmt->retVal = stmt->StandardDelete ();
                break ;
              case DBCALLTYPE_STANDARDGET :
                stmt->retVal = stmt->StandardGet ();
                stmt->GetOldStatementCopy ();
                break ;
              case DBCALLTYPE_GETLIST :
                stmt->retVal = stmt->StandardList (first);
                if ((Op != DBOP_GETNEXT) && (Op != DBOP_GETPREV))
                  stmt->GetOldStatementCopy ();
                break ;
              case DBCALLTYPE_STANDARDINSERT :
                stmt->retVal = stmt->StandardInsert ();
                break ;
              case DBCALLTYPE_STANDARDUPDATE :
                stmt->retVal = stmt->StandardUpdate ();
                break ;
              case DBCALLTYPE_EXECUTE :
              case DBCALLTYPE_EXECUTESINGLE :
                if (Op == DBOP_GETFIRST) {
                  stmt->retVal = stmt->StandardExcute ();
                  }
                break ;
              }
      stmt->StmtExit ();
      return stmt->retVal;
      break ;
    }

  return DBCALL_SUCCESS ;
  }

DLLExport void _export FAR PASCAL DoBeginTransaction ()
  {
  if (dbase == NULL)
    // Login to sybase
    dbase = new sybase (UserName,PassWord,AppName);
  sybstmt *h = new sybstmt ;
  h->execute ("begin tran",NULL);
  delete h ;
  }

DLLExport void _export FAR PASCAL DoEndTransaction ()
  {
  sybstmt *h = new sybstmt ;
  h->execute ("commit tran",NULL);
  delete h ;
  }

BOOL hmemcmp (LPVOID c1,LPVOID c2,DWORD cmpSize)
  {
  char huge *h1 = (char huge *) c1;
  char huge *h2 = (char huge *) c2;
  BOOL res = TRUE ;
  for ( DWORD i = 0 ; i < cmpSize ; i++ ) {
    if (*h1++ != *h2++) {
      res = FALSE ;
      break ;
      }
    }
  return res;
  }

DLLExport void _export FAR PASCAL DoAbortTransaction ()
  {
  sybstmt *h = new sybstmt ;
  h->execute ("rollback tran",NULL);
  delete h ;
  }

/*------------------------------------------------------*/
/*  Verwaltung der Resourcen                            */
/*------------------------------------------------------*/
// Statement zum Lesen / Schreiben von IMAGE Daten
#define PARTSIZE  0x10000
class FAR imgstmt : public sybstmt {
 public :
  // Buffer - Handling
  GLOBALHANDLE hGBuffer ;
  DWORD lRead;
  DWORD lAllocated;
  CS_IODESC iodesc;
  CS_CONNECTION *connection ;
  BOOL flushItem;

  void ResetDataPtr()
    {
    lRead = 0 ;
    if (hGBuffer) {
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);
      hGBuffer = 0 ;
      }
    }
  LPVOID GetDataPtr ()
    {
    hGBuffer = GlobalAlloc (GMEM_MOVEABLE,PARTSIZE);
    lAllocated = PARTSIZE ;
    return GlobalLock (hGBuffer);
    }
  CS_INT PartSize ()
    {
    return PARTSIZE ;
    }
  LPVOID NextDataPtr()
    {
    GlobalUnlock (hGBuffer);
    hGBuffer = GlobalReAlloc (hGBuffer,lAllocated + PARTSIZE,GMEM_MOVEABLE);
    LPVOID res = LPVOID ((LPSTR)GlobalLock (hGBuffer) + lAllocated);
    lAllocated += PARTSIZE ;
    return res ;
    }
  void ReSizeData()
    {
    GlobalUnlock (hGBuffer);
    if (lRead) {
      hGBuffer = GlobalReAlloc (hGBuffer,lRead,GMEM_MOVEABLE);
      GlobalLock (hGBuffer);
      }
    else {
      GlobalUnlock (hGBuffer);
      GlobalFree (hGBuffer);
      hGBuffer = 0 ;
      }
    }

  virtual ~imgstmt ()
    {
    ResetDataPtr();
    }
  imgstmt () : sybstmt ()
    {
    }
  virtual int nRows (LPTABLEDEF ti) 
    { 
    return 1 ; 
    }
  virtual int nCols (LPTABLEDEF ti)
    {
    return 1 ;
    }

  virtual void GetColInfo(LPTABLEDEF ti)
    {
    // Kein Binding !!!
    }

  virtual ImageItem()
    {
    return 1 ;
    }

  virtual void StoreData (LPTABLEDEF ti,int Row)
    {
    // Aufruf von ct_get_data und ct_get_data_info
    ResetDataPtr();
    LPVOID data = GetDataPtr ();
    CS_INT len;
    CS_RETCODE retcode ;
    // Lesen der Daten
    //////////////////////
    do {
      CS_INT toRead = flushItem ? 0 : PartSize() ;
      retcode = ct_get_data(cmd, ImageItem(), data, PartSize(), &len);
      lRead += len ;
      if (retcode == CS_SUCCEED) data = NextDataPtr();
      } while (retcode == CS_SUCCEED);
    ReSizeData();
    if (!((retcode == CS_END_ITEM) || (retcode == CS_END_DATA))) {
      WIN_ASSERT_TEXT (FALSE,"imgstmt::StoreData: ct_get_data() failed");
      return ;
      }
    retcode = ct_data_info(cmd, CS_GET,  ImageItem(), &iodesc);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"imgstmt::StoreData: cs_data_info() failed");
      return ;
      }
    }

  CS_RETCODE ProcessTimestamp()
    {
    CS_RETCODE  retcode;
    CS_INT              count;
    CS_DATAFMT  datafmt;

    retcode = ct_describe(cmd, 1, &datafmt);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"ProcessTimestamp: ct_describe() failed");
      return retcode;
      }

    if (!(datafmt.status & CS_TIMESTAMP)) {
      WIN_ASSERT_TEXT (FALSE,"ProcessTimestamp: unexpected parameter data received");
      return CS_FAIL;
      }

    datafmt.maxlength = sizeof(iodesc.timestamp);
    datafmt.format     = CS_FMT_UNUSED;
    if ((retcode = ct_bind(cmd, 1, &datafmt, iodesc.timestamp,
              &iodesc.timestamplen,NULL)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"ProcessTimestamp: ct_bind() failed");
      return retcode;
      }

    retcode = ct_fetch(cmd, CS_UNUSED, CS_UNUSED, CS_UNUSED, &count);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"ProcessTimestamp: ct_fetch() failed");
      return retcode;
      }

    retcode = ct_cancel(NULL, cmd, CS_CANCEL_CURRENT);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"ProcessTimestamp: ct_cancel() failed");
      }
    return retcode;
    }

  void UpdateImage (LPVOID Data,DWORD Size)
    {
    CS_RETCODE  retcode;

    if ((retcode = ct_cmd_alloc(dbase->connection, &cmd)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT(FALSE,"UpdateImage: ct_cmd_alloc() failed");
      return ;
      }

    if ((retcode = ct_command(cmd, CS_SEND_DATA_CMD, NULL, CS_UNUSED,
        CS_COLUMN_DATA)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"UpdateImage: ct_command() failed");
      return ;
      }

    iodesc.total_txtlen = Size;
    iodesc.log_on_update = CS_TRUE;
    retcode = ct_data_info(cmd, CS_SET, CS_UNUSED, &iodesc);
    if (retcode != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"UpdateImage: ct_data_info() failed");
      return ;
      }

    char huge *pToSend = (char huge *) Data ;
    for ( DWORD SizeToSend = Size ; ; ) {
      DWORD rSize = min (SizeToSend,0x4000) ;
      retcode = ct_send_data (cmd, pToSend, rSize);
      SizeToSend -= rSize ;
      if (SizeToSend > 0)
        pToSend += rSize ;
      else
        break ;
      }

    if ((retcode = ct_send(cmd)) != CS_SUCCEED) {
      WIN_ASSERT_TEXT (FALSE,"UpdateImage: ct_send() failed");
      return ;
      }

    ct_cancel(NULL, cmd, CS_CANCEL_ALL);
    ct_cmd_drop(cmd);
    }

  BOOL compare (LPVOID Data,DWORD Size)
    {
    if (Size == lRead) {
      return hmemcmp (Data,GlobalLock (hGBuffer),Size);
      }
    else
      return FALSE ;
    }

  GLOBALHANDLE GetRes (DWORD FAR *Size)
    {
    if (hGBuffer) {
      GLOBALHANDLE res = GlobalAlloc (GMEM_MOVEABLE,*Size = lRead) ;
      hmemcpy (GlobalLock (res),GlobalLock (hGBuffer),lRead);
      GlobalUnlock (res) ; GlobalUnlock (hGBuffer) ;
      return res ;
      }
    else
      return 0 ;
    }
  };

class FAR img1stmt : public imgstmt {
 public :
  LPSTR StrRes;
  img1stmt () : imgstmt ()
    {
    }
  virtual int nRows (LPTABLEDEF ti) 
    { 
    return 1 ; 
    }
  virtual int nCols (LPTABLEDEF ti)
    {
    return 1 ;
    }

  virtual void GetColInfo(LPTABLEDEF ti)
    {
    // Binding der ersten Variable (TableName)
    if (ColInfo == NULL) {
      ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
      ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(NULL)) ;
      ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(NULL)) ;
      ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_STR,64,nRows(NULL));
      }
    }

  virtual ImageItem()
    {
    return 2 ;
    }

  virtual void StoreData (LPTABLEDEF ti,int row)
    {
    LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
    int size = int (ColInfo[0].VarLen[row]);
    if (size != NULL)
      StrRes = LPSTR(data);
    else
      StrRes = NULL;
    imgstmt::StoreData (ti,row);
    }
  };

class FAR img2stmt : public imgstmt {
 public :
  DWORD resID;
  LPSTR Name;
  BOOL readDone;
  img2stmt () : imgstmt ()
    {
    readDone = FALSE ;
    }
  virtual int nRows (LPTABLEDEF ti) 
    { 
    return 1 ; 
    }
  virtual int nCols (LPTABLEDEF ti)
    {
    return 2 ;  // Nur 2 Spalte wird gebunden
    }

  virtual void GetColInfo(LPTABLEDEF ti)
    {
    // Binding der ersten Variable (TableName)
    if (ColInfo == NULL) {
      ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
      ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(NULL)) ;
      ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(NULL)) ;
      ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_LONG,sizeof(LONG),nRows(NULL));
      ColInfo[1].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarLen) * nRows(ti)) ;
      ColInfo[1].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarIndikat) * nRows(ti)) ;
      ColInfo[1].VarData    = GetSybDataType (&ColInfo[1].VarFormat,VAR_STR,64,nRows(ti));
      }
    }

  virtual ImageItem()
    {
    return 3 ;
    }

  virtual void StoreData (LPTABLEDEF ti,int row)
    {
    LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
    int size = int (ColInfo[0].VarLen[row]);
    if (size == sizeof(DWORD)) {
      resID = *(LONG *) data ;
      readDone = TRUE ;
      }
    else {
      readDone = FALSE ;
      }
    data = LPVOID (LPSTR (ColInfo[1].VarData) + row * ColInfo[1].VarFormat.maxlength) ;
    size = int (ColInfo[1].VarLen[row]);
    if (size > 0)
      Name = LPSTR(data);
    else
      readDone = FALSE ;
    imgstmt::StoreData (ti,row);
    }
  };
//
// Statement zum Absetzen von Kommandos zum
// Ermitteln des Idens
//
class FAR imgtest : public sybstmt {
 public :
  BOOL readDone;
  DWORD resID;
  imgtest () : sybstmt () 
    { 
    readDone = FALSE ;
    } 
  virtual int nRows (LPTABLEDEF ti)
    { return 1 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual void StoreData (LPTABLEDEF ti,int row)
    {
    LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
    int size = int (ColInfo[0].VarLen[row]);
    if (size == sizeof(resID)) {
      readDone = TRUE ;
      resID = *(DWORD FAR *) data ;
      }
    }
  virtual void GetColInfo(LPTABLEDEF ti)
    {
    readDone = FALSE ;
    if (ColInfo == NULL) {
      ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
      ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(ti)) ;
      ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(ti)) ;
      ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_LONG,sizeof(resID),nRows(ti));
      }
    }
  virtual ~imgtest () { }
  };

struct _DInfo {
  WORD Id;
  LPSTR Name ;
  _DInfo FAR *Next ;
  };

_DInfo FAR *DFirst,FAR *DLast;
void PushDInfo (LPSTR Name,WORD Id)
  {
  _DInfo FAR *n = (_DInfo FAR *) GetGlobMem (sizeof (*n)) ;
  n->Name = LPSTR(GetGlobMem (lstrlen(Name) + 1)) ;
  lstrcpy (n->Name,Name);
  n->Id = Id ;
  if (DLast != NULL) {
    DLast->Next = n ;
    DLast = n ;
    }
  else {
    DLast = DFirst = n ;
    }
  }


BOOL PopDInfo (LPSTR Name,WORD *Id)
  {
  if (DFirst != NULL) {
    lstrcpy (Name,DFirst->Name);
    *Id = DFirst->Id ;
    _DInfo FAR *DNext = DFirst->Next ;
    FreeGlobMem (DFirst->Name);
    FreeGlobMem (DFirst);
    DFirst = DNext ;
    if (DFirst == NULL)
      DLast = NULL ;
    return TRUE ;
    }
  else
    return FALSE ;
  }

class FAR img1test : public sybstmt {
 public :
  BOOL readDone;
  DWORD resID;
  LPSTR Name;
  img1test () : sybstmt () { } 
  virtual int nRows (LPTABLEDEF ti)
    { return 1 ; }
  virtual int nRowsToGet (LPTABLEDEF ti)
    {
    return - 1; 
    }
  virtual int nCols (LPTABLEDEF ti)
    { return 2 ; }
  virtual void StoreData (LPTABLEDEF ti,int row)
    {
    LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
    int size = int (ColInfo[0].VarLen[row]);
    WORD Id ;
    if (size == sizeof(resID)) {
      readDone = TRUE ;
      Id = *(WORD FAR *) data ;
      }
    data = LPVOID (LPSTR (ColInfo[1].VarData) + row * ColInfo[1].VarFormat.maxlength) ;
    size = int (ColInfo[1].VarLen[row]);
    if (size > 0)
      PushDInfo (LPSTR(data),Id);
    else
      readDone = FALSE ;
    }
  virtual void GetColInfo(LPTABLEDEF ti)
    {
    readDone = FALSE ;
    if (ColInfo == NULL) {
      ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
      ColInfo[0].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(ti)) ;
      ColInfo[0].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[0].VarIndikat) * nRows(ti)) ;
      ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_LONG,sizeof(resID),nRows(ti));
      ColInfo[1].VarLen     = (CS_INT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarLen) * nRows(ti)) ;
      ColInfo[1].VarIndikat = (CS_SMALLINT FAR *) GetGlobMem (sizeof(*ColInfo[1].VarIndikat) * nRows(ti)) ;
      ColInfo[1].VarData    = GetSybDataType (&ColInfo[1].VarFormat,VAR_STR,64,nRows(ti));
      }
    }
  virtual ~img1test () { }
  };


/*
**  Die Resourcenfunktionen im Einzelnen
*/
#define DEFDLL  "-"
class ResDB {
 public :
  LPSTR Name;
  LPVOID Data;
  DWORD Size;
  BOOL *changed;
  WORD IdMin,IdMax;
  imgtest *t;
  img1test *t1;
  imgstmt *r;
  img1stmt *r1;
  img2stmt *r2;

  virtual LPSTR ResDBName ()
    {
    return NULL ;
    }

  ResDB (LPSTR _Name,LPVOID _Data,DWORD _Size,BOOL FAR *_changed,WORD _IdMin,WORD _IdMax)
    {
    Name  = _Name;
    Data  = _Data;
    Size  = _Size;
    changed    = _changed;
    IdMin = _IdMin;
    IdMax = _IdMax;
    if (dbase == NULL)
      dbase = new sybase (UserName,PassWord,AppName);
    t = new imgtest ();
    r = new imgstmt ();
    t1 = NULL ;
    r1 = NULL ;
    r2 = NULL ;
    }

  ~ResDB ()
    {
    if (r  != NULL) delete r  ;
    if (r1 != NULL) delete r1 ;
    if (r2 != NULL) delete r2 ;
    if (t  != NULL) delete t  ;
    if (t1 != NULL) delete t1 ;
    }

  void ReadDef_WithID(LPSTR DLLName,BOOL flush = FALSE)
    {
    LongString h ;
    h = h + "SELECT data FROM " + ResDBName () + " WHERE DLL = '" + DLLName + 
            "' AND Id = " + t->resID ;
    r->flushItem = flush ;
    r->execute (h.Ptr(),NULL);
    }
  void ReadDefAndName_WithID(LPSTR DLLName,DWORD resID)
    {
    LongString h ;
    h = h + "SELECT Name,data FROM " + ResDBName () + " WHERE DLL = '" + DLLName + 
            "' AND Id = " + resID ;
    if (r1 == NULL)
      r1 = new img1stmt ();
    r1->execute (h.Ptr(),NULL);
    if (r1->StrRes != NULL)
      lstrcpy (Name,r1->StrRes);
    }
  void UpdateDef(LPSTR DLLName)
    {
    ReadDef_WithID(DLLName,FALSE);
    if (!r->compare (Data,Size)) {
      r->UpdateImage (Data,Size);
      *changed = TRUE ;
      }
    else
      *changed = FALSE ;
    }
  void InsertDef (BOOL doUpdate,LPSTR DLLName)
    {
    LongString i ;
    i = i + "INSERT INTO " + ResDBName () + " (Name,DLL,Id,Data) VALUES ('" +
            Name + "','" + DLLName + "'," + t->resID + "," + "'refData')" ;
    t->execute (i.Ptr(),NULL);
    // Nun noch updaten
    if (doUpdate)
      UpdateDef (DLLName);
    }
  void NewID ()
    {
    LongString h ;
    h = h + "SELECT MAX (Id) FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL +
          "' AND Id >= " + IdMin + " AND Id <= " + IdMax ;
    t->execute (h.Ptr(),NULL);
    if ((t->readDone) && (t->resID >= IdMin)) {
      WIN_ASSERT (t->resID < IdMax) ;
      t->resID ++ ;
      }
    else
      t->resID = IdMin ;
    }
  void NewID (LPSTR DLLName)
    {
    LongString h ;
    h = h + "SELECT MAX (Id) FROM " + ResDBName() + " WHERE DLL = '" + DLLName +
          "' AND Id >= " + IdMin + " AND Id <= " + IdMax ;
    t->execute (h.Ptr(),NULL);
    if ((t->readDone) && (t->resID >= IdMin)) {
      WIN_ASSERT (t->resID < IdMax) ;
      t->resID ++ ;
      }
    else
      t->resID = IdMin ;
    }
  BOOL ReadDef_UseName (LPSTR DLLName)
    {
    LongString h ;
    h = h + "SELECT Id FROM " + ResDBName() + " WHERE DLL = '" + DLLName + 
          "' AND Name = '" + Name + 
          "' AND Id >= " + IdMin + " AND Id <= " + IdMax ;
    t->execute (h.Ptr(),NULL);

    return t->readDone ;
    }

  void Set (LPSTR DLLName)
    {
    if (ReadDef_UseName (DLLName))
      // Normaler Update
      UpdateDef (DLLName);
    else {
      // Versuchen die Referenz zu finden
      if (ReadDef_UseName (DEFDLL))
        // Nur mehr fuer die DLL einfuegen
        InsertDef (TRUE,DLLName);
      else {
        // Die Referenz und die DLL einfuegen
        NewID ();
        if (lstrcmp (DLLName,DEFDLL))
          InsertDef (FALSE,DEFDLL);
        InsertDef (TRUE,DLLName);
        }
      }
    }
  BOOL GetFirst (WORD FAR *Id)
    {
    if (t1 == NULL)
      t1 = new img1test ;
    LongString h ;
    h = h + "SELECT Id,Name FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + "'" ;
    t1->execute (h.Ptr(),NULL) ;
    return PopDInfo (Name,Id);
    }
  GLOBALHANDLE GetFirst_Data (WORD FAR *Id,DWORD FAR *DataSize)
    {
    if (r2 == NULL)
      r2 = new img2stmt ;
    LongString h ;
    h = h + "SELECT Id,Name,data FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + 
            "' AND Id = (SELECT MIN(Id) FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + 
          "' AND Name <> '_CONT_' AND Name <> '_FUNC_' AND Id >= " + IdMin + " AND Id <= " + IdMax + ")" ;
    r2->execute (h.Ptr(),NULL) ;
    if (r2->readDone) {
      *Id = WORD(r2->resID) ;
      lstrcpy (Name,r2->Name);
      }
    return r2->GetRes (DataSize) ;
    }
  BOOL GetNext (WORD PrevId,WORD FAR *Id)
    {
    return PopDInfo (Name,Id);
    }
  GLOBALHANDLE GetNext_Data (WORD PrevId,WORD FAR *Id,DWORD *DataSize)
    {
    if (r2 == NULL)
      r2 = new img2stmt () ;
    LongString h ;
    h = h + "SELECT Id,Name,data FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + 
            "' AND Id = (SELECT MIN(Id) FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + 
          "' AND Name <> '_CONT_' AND Name <> '_FUNC_' AND Id > " + PrevId + " AND Id <= " + IdMax + ")" ;
    r2->execute (h.Ptr(),NULL);
    if (r2->readDone) {
      *Id = WORD(r2->resID) ;
      lstrcpy (Name,r2->Name);
      }
    return r2->GetRes (DataSize) ;
    }
  void DelDef (LPSTR DLLName,WORD TableIdent)
    {
    LongString h ;
    h = h + "DELETE FROM " + ResDBName() + " WHERE DLL = '" + DEFDLL + 
            "' AND Id = " + TableIdent ;
    t->execute (h.Ptr(),NULL);
    h.Clear ();
    h = h + "DELETE FROM " + ResDBName() + " WHERE DLL = '" + DLLName + 
            "' AND Id = " + TableIdent ;
    t->execute (h.Ptr(),NULL);
    }
  };

class TableDB : public ResDB {
 public :
  TableDB (LPSTR _Name,LPVOID _Data,DWORD _Size,BOOL FAR *_changed,WORD _IdMin,WORD _IdMax)
    : ResDB (_Name,_Data,_Size,_changed,_IdMin,_IdMax)
    {
    }
  virtual LPSTR ResDBName ()
    {
    return "_CLTABLES" ;
    }
  };

class TableContDB : public ResDB {
 public :
  TableContDB (LPSTR _Name,LPVOID _Data,DWORD _Size,BOOL FAR *_changed,WORD _IdMin,WORD _IdMax)
    : ResDB (_Name,_Data,_Size,_changed,_IdMin,_IdMax)
    {
    }
  virtual LPSTR ResDBName ()
    {
    return "_CLTABLECONT" ;
    }
  };

class ScriptDB : public ResDB {
 public :
  ScriptDB (LPSTR _Name,LPVOID _Data,DWORD _Size,BOOL FAR *_changed,WORD _IdMin,WORD _IdMax)
    : ResDB (_Name,_Data,_Size,_changed,_IdMin,_IdMax)
    {
    }
  virtual LPSTR ResDBName ()
    {
    return "_SCRIPT" ;
    }
  };

class PictDB : public ResDB {
 public :
  PictDB (LPSTR _Name,LPVOID _Data,DWORD _Size,BOOL FAR *_changed,WORD _IdMin,WORD _IdMax)
    : ResDB (_Name,_Data,_Size,_changed,_IdMin,_IdMax)
    {
    }
  virtual LPSTR ResDBName ()
    {
    return "_PICT" ;
    }
  };

DLLExport WORD _export FAR PASCAL DataRes_SetTableDef 
            (LPSTR DLLName,
             LPSTR TableName,
             WORD TableIdMin,WORD TableIdMax,
             LPVOID TableData,DWORD TableSize,
             BOOL FAR *changed
            )
  {
  TableDB r (TableName,TableData,TableSize,changed,TableIdMin,TableIdMax);
  r.Set (DLLName) ;
  return WORD(r.t->resID) ;
  }

DLLExport void _export FAR PASCAL DataRes_SetFullTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  LPVOID TableData,
                  DWORD TableSize
                                                )
  {
  BOOL changed;
  TableDB r (TableName,TableData,TableSize,&changed,0,0xFFFF);
  r.t->resID = DWORD(TableIdent);
  r.UpdateDef (DLLName) ;
  }

// Lesen der Tabellendefinition
DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  DWORD FAR *HeaderSize,
                  DWORD FAR *TableSize
                                                    )
  {
  *TableName = '\0' ;
  BOOL changed ;
  TableDB r (TableName,0,0L,&changed,0,0xFFFF);
  r.ReadDefAndName_WithID (DLLName,TableIdent);
  GLOBALHANDLE hGres = r.r1->GetRes (TableSize);
  *HeaderSize = 0L ;
  return hGres;
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetFullTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  DWORD FAR *HeaderSize,
                  DWORD FAR *TableSize
                                                       )
  {
  return DataRes_GetTableDef (DLLName,TableIdent,TableName,HeaderSize,TableSize);
  }

DLLExport BOOL _export FAR PASCAL DataRes_GetFirstTableDef (WORD FAR *TableIdent,LPSTR TableName)
  {
  *TableName = '\0' ;
  BOOL changed ;
  TableDB r (TableName,0,0L,&changed,0,0xFFFF);
  return r.GetFirst (TableIdent);
  }

DLLExport BOOL _export FAR PASCAL DataRes_GetNextTableDef 
            (WORD PrevIdent,
             WORD FAR *TableIdent,
             LPSTR TableName
            )
  {
  *TableName = '\0' ;
  BOOL changed ;
  TableDB r (TableName,0,0L,&changed,0,0xFFFF);
  return r.GetNext (PrevIdent,TableIdent);
  }

DLLExport void _export FAR PASCAL DataRes_SetDictCont (LPVOID Data,DWORD DataSize)
  {
  char Name[1];
  *Name = '\0' ;
  char DLLName[1] ;
  *DLLName = '\0' ;
  BOOL changed ;
  TableContDB r (Name,Data,DataSize,&changed,0,0xFFFF);
  r.t->resID = 1 ;

  if (r.ReadDef_UseName (DLLName))
    // Normaler Update
    r.UpdateDef (DLLName);
  else
    // Erweiterung
    r.InsertDef (TRUE,DLLName);
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetDictCont (
        DWORD FAR *HeaderSize,
        DWORD FAR *DataSize
                                                    )
  {
  char Name[1];
  *Name = '\0' ;
  char DLLName[1] ;
  *DLLName = '\0' ;
  BOOL changed ;
  TableContDB r (Name,NULL,0L,&changed,0,0xFFFF);
  r.t->resID = 1 ;

  r.ReadDef_WithID (DLLName) ;
  GLOBALHANDLE hGres = r.r->GetRes (DataSize);
  *HeaderSize = 0 ;
  return hGres ;
  }

DLLExport void _export FAR PASCAL DataRes_DelTableDef (LPSTR DLLName,WORD TableIdent)
  {
  char Name[1];
  *Name = '\0' ;
  BOOL changed ;
  TableDB r (Name,NULL,0L,&changed,0,0xFFFF);

  r.DelDef (DLLName,TableIdent);
  }

DLLExport void _export FAR PASCAL DataRes_SetDocDef (LPSTR DocName,LPVOID DocData,DWORD DataSize)
  {
  BOOL changed ;
  ScriptDB r (DocName,DocData,DataSize,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL))
    // Normaler Update
    r.UpdateDef (DEFDLL);
  else {
    // Erweiterung
    r.NewID(DEFDLL);
    r.InsertDef (TRUE,DEFDLL);
    }
  }

DLLExport void _export FAR PASCAL DataRes_SetFuncDef (LPVOID DocData,DWORD DataSize)
  {
  BOOL changed ;
  ScriptDB r ("_FUNC_",DocData,DataSize,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL))
    // Normaler Update
    r.UpdateDef (DEFDLL);
  else {
    // Erweiterung
    r.NewID(DEFDLL);
    r.InsertDef (TRUE,DEFDLL);
    }
  }


DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetDocDef (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  BOOL changed ;
  ScriptDB r (DocName,NULL,0L,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL)) {
    *HeaderSize = 0L ;
    return r.r->GetRes (DocSize);
    }
  else
    return 0 ;
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetFuncDef (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  BOOL changed ;
  ScriptDB r ("_FUNC_",NULL,0L,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL)) {
    r.ReadDef_WithID (DEFDLL) ;
    *HeaderSize = 0L ;
    return r.r->GetRes (DocSize);
    }
  else
    return 0 ;
  }

static WORD lastID;
DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetFirstDoc (LPSTR DocName,DWORD *HeaderSize,DWORD FAR *DocSize)
  {
  *DocName = '\0' ;
  BOOL changed ;
  ScriptDB r (DocName,0,0L,&changed,0,0xFFFF);
  *HeaderSize = 0L;
  return r.GetFirst_Data (&lastID,DocSize);
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetNextDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  *DocName = '\0' ;
  BOOL changed ;
  ScriptDB r (DocName,0,0L,&changed,0,0xFFFF);
  *HeaderSize = 0L;
  return r.GetNext_Data (lastID,&lastID,DocSize);
  }

DLLExport void _export FAR PASCAL DataRes_SetDocCont (LPVOID DocData,DWORD DataSize)
  {
  BOOL changed ;
  ScriptDB r ("_CONT_",DocData,DataSize,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL))
    // Normaler Update
    r.UpdateDef (DEFDLL);
  else {
    // Erweiterung
    r.NewID(DEFDLL);
    r.InsertDef (TRUE,DEFDLL);
    }
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetDocCont (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  BOOL changed ;
  ScriptDB r ("_CONT_",NULL,0L,&changed,0,0xFFFF);
  if (r.ReadDef_UseName (DEFDLL)) {
    r.ReadDef_WithID (DEFDLL) ;
    *HeaderSize = 0L ;
    return r.r->GetRes (DocSize);
    }
  else
    return 0 ;
  }

inline WORD MinPictID(WORD Type)
  {
  switch (Type) {
    case RESTYPE_CONT  :
      return 1 ;
    case RESTYPE_BITMAP :
      return 10 ;
    case RESTYPE_WMF :
      return 2000 ;
    }
  return 0 ;
  }

inline WORD MaxPictID(WORD Type)
  {
  switch (Type) {
    case RESTYPE_CONT  :
      return 9 ;
    case RESTYPE_BITMAP :
      return 1999 ;
    case RESTYPE_WMF :
      return 3000 ;
    }
  return 0 ;
  }

DLLExport DWORD _export FAR PASCAL DataRes_SetResource (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
  {
  BOOL changed ;
  PictDB r (Name,Data,DataSize,&changed,MinPictID(Type),MaxPictID(Type));
  if (r.ReadDef_UseName (DEFDLL))
    // Normaler Update
    r.UpdateDef (DEFDLL);
  else {
    // Erweiterung
    r.NewID(DEFDLL);
    r.InsertDef (TRUE,DEFDLL);
    }
  return r.t->resID ;
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetResource (DWORD ResID,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  char ResourceName[64];
  BOOL changed ;
  PictDB r (ResourceName,0,0L,&changed,0,0xFFFF);
  r.t->resID = DWORD (ResID);
  r.ReadDef_WithID (DEFDLL);
  GLOBALHANDLE hGres = r.r->GetRes (DataSize);
  *HeaderSize = 0L ;
  return hGres;
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetFirstResource
            (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,
             DWORD FAR *DataSize
            )
  {
  BOOL changed ;
  PictDB r (ResName,0,0L,&changed,MinPictID(Type),MaxPictID(Type));
  *HeaderSize = 0L;
  GLOBALHANDLE hGres = r.GetFirst_Data (&lastID,DataSize);
  *Id = lastID ;
  return hGres ;
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetNextResource
            (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,
             DWORD FAR *DataSize
            )
  {
  BOOL changed ;
  PictDB r (ResName,0,0L,&changed,MinPictID(Type),MaxPictID(Type));
  *HeaderSize = 0L;
  lastID = WORD(*Id) ;
  GLOBALHANDLE hGres = r.GetNext_Data (lastID,&lastID,DataSize);
  *Id = lastID ;
  return hGres ;
  }

DLLExport void _export FAR PASCAL DataRes_SetResCont (WORD Type,LPVOID Data,DWORD DataSize)
  {
  BOOL changed ;
  PictDB r ("_CONT_",Data,DataSize,&changed,MinPictID(Type),MaxPictID(Type));
  if (r.ReadDef_UseName (DEFDLL))
    // Normaler Update
    r.UpdateDef (DEFDLL);
  else {
    // Erweiterung
    r.NewID(DEFDLL);
    r.InsertDef (TRUE,DEFDLL);
    }
  }

DLLExport GLOBALHANDLE _export FAR PASCAL DataRes_GetResCont (WORD Type,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  BOOL changed ;
  PictDB r ("_CONT_",NULL,0L,&changed,MinPictID(Type),MaxPictID(Type));
  if (r.ReadDef_UseName (DEFDLL)) {
    r.ReadDef_WithID (DEFDLL) ;
    *HeaderSize = 0L ;
    return r.r->GetRes (DataSize);
    }
  else
    return 0 ;
  }



