//////////////////////////////////////////////////////////////
//  ODBC - Anbindung an das Clinicum
//////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/ddsodbc/rev/opodbc.cpv   1.57   10 Oct 1999 12:55:50   Hannes  $
//  $Log:   P:/marille/clinicum/ddsodbc/rev/opodbc.cpv  $
//
//    Rev 1.58   25 Nov 1999 03:11:14   Hannes
// Auch _Excute mit Ausgabeparameter unterstuetzen...
//
//    Rev 1.57   10 Oct 1999 12:55:50   Hannes
// Bei den Feldgroessen sicherheitshalber ein Byte dazugetan (Wegen ev. Strings)
//
//    Rev 1.56   17 Sep 1999 02:38:44   Hannes
//
//    Rev 1.55   09 Sep 1999 22:18:38   Hannes
// SQL Syntax auch in ODBC
//
//    Rev 1.54   25 Apr 1999 19:06:12   Martin
// alias fuer COUNT (XCOUNT)
//
//    Rev 1.53   13 Jan 1999 10:02:02   Martin
// auch Implementierungen von LockForInsert und ClearLock raus
//
//    Rev 1.52   28 Dec 1998 16:45:48   Hannes
// Naechster Versuch (ODBC_Check)
//
//    Rev 1.51   28 Dec 1998 12:06:40   Hannes
// Sequence - Check in der Zwischenzeit ausgelassen
//
//    Rev 1.48   26 Nov 1998 08:23:30   Hannes
// Fehler Data trancated ignoriert
//
//    Rev 1.47   21 Aug 1998 14:46:18   Martin
// WIN_ASSERTs -> DBWIN_ASSERTs
//
//    Rev 1.46   11 Aug 1998 15:32:18   Hannes
//
//    Rev 1.45   11 Aug 1998 10:45:02   Martin
// Alias auch bei INSERT INTO ...
//
//    Rev 1.44   06 Aug 1998 23:00:52   Martin
// ein Sternchen zuviel
//
//    Rev 1.43   06 Aug 1998 22:42:40   Martin
//
//    Rev 1.42   06 Aug 1998 09:26:26   Hannes
// Statmenthandle richtig freigeben beim Update
//
//    Rev 1.41   04 Aug 1998 17:56:56   Hannes
// Timestamp
//
//    Rev 1.40   27 Jul 1998 13:28:50   Hannes
// DBSpace - Handling
//
//    Rev 1.39   03 Jul 1998 15:11:08   Martin
// foreign keys
//
//    Rev 1.38   17 Jun 1998 17:34:48   Martin
// identity insert off nur bei SQL Server !
//
//    Rev 1.37   05 May 1998 18:50:58   Hannes
// Statt Parameterbindung mit NULL / Datum / Zeit -> Statement auf = NULL
// umgesetzt
//
//    Rev 1.36   24 Mar 1998 12:31:48   Martin
// Sybase Anywhere Authentication
//
//    Rev 1.35   06 Mar 1998 17:26:12   Hannes
// Prototyp Transaktionshandling
//
//    Rev 1.34   27 Jan 1998 13:17:56   Martin
// DataSource, UserName und PassWord in dmw.ini einstellbar
// (Section [ODBC])
//
//    Rev 1.33   12 Jan 1998 17:49:48   Hannes
//
//    Rev 1.32   12 Jan 1998 17:14:32   Hannes
// ausser bei SQL Server neuen AliasName OPTIONS eingefuegt
//
//    Rev 1.31   15 Dec 1997 22:07:40   Martin
// Zeit in SQL Server (TIMESTAMP_STRUCT statt TIME_STRUCT)
//
//    Rev 1.30   31 Oct 1997 12:50:32   Hannes
// Timestampfunktion, Diverse Fehlerkorr.
//
//    Rev 1.29   19 Oct 1997 21:26:04   Martin
// einige ODBCGetTableNames
//
//    Rev 1.28   18 Oct 1997 22:01:34   Martin
// Parameter der WHERE-Klausel HINTER denen der JOINs !!!!
//
//    Rev 1.27   25 Sep 1997 14:09:22   Hannes
// mystrcmp ... Nur auf ganze Worte ueberpruefen
//
//    Rev 1.26   24 Sep 1997 09:30:38   Hannes
// Update auch fuer Microsoft SQL - Server
//
//    Rev 1.25   16 Jul 1997 16:44:18   Hannes
// Aliasnamensueberpruefung -> '.Nummer' wird rauseleminiert
//
//    Rev 1.24   14 Jul 1997 13:36:26   Hannes
//
//    Rev 1.23   07 Jul 1997 15:57:10   Martin
// SQLServer 1. Version
// bei StandardGet: BindColData statt einzelnen SQLGetData-Aufrufen
//
//    Rev 1.22   12 Jun 1997 11:13:22   Martin
// ISOLATION_LEVEL 1
//
//    Rev 1.21   12 Jun 1997 10:52:40   Martin
// Autocommit-Handling richtiggestellt
//
//    Rev 1.20   20 Mar 1997 10:44:38   Hannes
// Einbau des Primaerschluessels, EnlargeInsert -> Nur ein NULL eingebaut,
// CreateTable: NOT NULL angegeben
//
//    Rev 1.19   29 Jan 1997 16:53:00   HANNES
// GetRecCopy ... BLOBS ganz kopieren
//
//    Rev 1.18   23 Jan 1997 16:19:22   HANNES
// ISNULL Handling bei normalen Abfragen, Leerer Insert
//
//    Rev 1.17   14 Jan 1997 16:01:40   HANNES
// GetTableDef / FreeTableDef paarweise gecheckt
// GetDBPointer
//
//    Rev 1.16   18 Dec 1996 17:50:42   HANNES
// Subselect - Handling
//
//    Rev 1.15   17 Dec 1996 11:13:24   HANNES
// EndOfUpdate
//
//    Rev 1.14   26 Nov 1996 08:03:12   HANNES
// Automatischer Update
//
//    Rev 1.13   07 Nov 1996 18:22:02   HANNES
//
//    Rev 1.12   07 Nov 1996 17:22:34   HANNES
// Fehlerkorrekturen / Aliasnamen, TestTableDef
//
//    Rev 1.11   06 Nov 1996 11:46:42   HANNES
//
//    Rev 1.10   06 Nov 1996 10:55:04   HANNES
//
//    Rev 1.9   30 Oct 1996 11:56:08   HANNES
//
//    Rev 1.8   07 Oct 1996 16:52:24   MARTIN
// Insert ohne Autoinc -> altes Record im Recordbuffer nicht loeschen !
//
//    Rev 1.7   19 Jul 1996 10:22:42   HANNES
// Stand DentSo
//
//    Rev 1.6   13 Apr 1996 19:55:38   HANNES
// Erste Version fuer WATCOM
//
//    Rev 1.5   04 Feb 1996 15:40:06   hannes
// #define NOCOMPILE
//
//    Rev 1.4   02 Feb 1996 10:46:10   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.3   26 Apr 1995 15:33:36   HANNES
//
//    Rev 1.2   30 Mar 1995 10:25:34   GERHOLD
// #pragma optimize
//
//    Rev 1.1   24 Feb 1995 11:15:40   HANNES
//
//
//    Rev 1.0   20 Feb 1995 21:55:36   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "dds32.h"

#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 147
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"

#define NOCOMPILE
#include "compile.hpp"

#define OPODC_MAIN
#include "opodbc.hpp"

static DWORD timeForLog;

/******************************************************************************
Erweitertes benutzerdefinierbares Errorhandling
******************************************************************************/

struct errToIgnore {
  errToIgnore FAR *Next;
  int errType;
  };

static struct errToIgnore FAR *eri = NULL ;
static BOOL errToWith_All = FALSE ;
static BOOL errToWith_UserDefined = FALSE ;

static int  lastIgnoredErrorType   = 0 ;
static char lastIgnoredErrMsg[256] = {0};

void FreeErrToIgnore ();
BOOL IsTypeToIgnore (int errType);

typedef struct {
  int ErrType ;
  int ErrCode ;
  }
  _ErrorMap ;

static _ErrorMap errmapSybase [] =
  {
    { ERRTYPE_DUPLICATEKEY , -196 } ,
    { ERRTYPE_DUPLICATEKEY , -193 }
  } ;

int ErorCodeToErrorType (int DatabaseType,int ErrorCode)
  {
  if ((DatabaseType != DT_MSSQLSERVER) && (DatabaseType != DT_ACCESS)) {
    for (int i = 0 ; i < sizeof(errmapSybase) / sizeof(errmapSybase[0]) ; i++) {
      if (ErrorCode == errmapSybase[i].ErrCode) {
        return errmapSybase[i].ErrType ;
        }
      }
    if (errToWith_All) {
      return ERRTYPE_ALLERRORS ;
      }
    }
  return 0 ;
  } //ErorCodeToErrorType

BOOL ErrorCodeToIgnore (int DatabaseType,int ErrorCode,LPSTR errorMessage)
  {
  int errType = ErorCodeToErrorType (DatabaseType,ErrorCode) ;
  if (errType && (IsTypeToIgnore (errType))) {
    lastIgnoredErrorType = errType;
    if (errorMessage) {
      lstrcpy (lastIgnoredErrMsg,errorMessage);
      }
    else {
      lastIgnoredErrMsg[0] = 0 ;
      }
    return TRUE ;
    }
  else {
    return FALSE ;
    }
  } //ErrorCodeToIgnore

/*****************************************************************************/

static BOOL  ovrDoLog    = FALSE;
static LPSTR ovrLogFile  = NULL;

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
    timeForLog     = GetPrivateProfileInt ("DataBase","TimeForLog",0,GetIniName());

    FirstTime = FALSE;
    }
  if (ovrDoLog) {
    return TRUE;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog;
  }

BOOL DoLog(LPSTR what)
  {
  static char lastWhat[32] = "" ;
  BOOL doLog = DoLog();  
  if (doLog) {
    if (lstrcmp(what,lastWhat) == 0) {
      doLog = TRUE;
      }
    else {
      char buf[20];
      GetPrivateProfileString ("DataBaseLog",what,"no",buf,sizeof(buf),GetIniName());
      doLog = (lstrcmp(buf,"yes") == 0);
      lstrcpy(lastWhat,what);
      }
    }
  return doLog;
  }

extern LPSTR WINAPI makeIni(LPSTR txt);
void LogCmd (LPSTR t1,LPSTR t2,LPSTR t3,LPSTR t4)
  {
  OFSTRUCT Of;
  LPSTR fname ;
  if (ovrLogFile == NULL) {
    fname = makeIni ("odbccmds.log");
    }
  else {
    fname = makeIni (ovrLogFile);
    }
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
    if (t1 != NULL)
      _lwrite (f,t1,lstrlen(t1));
    if (t2 != NULL)
      _lwrite (f,t2,lstrlen(t2));
    if (t3 != NULL)
      _lwrite (f,t3,lstrlen(t3));
    if (t4 != NULL)
      _lwrite (f,t4,lstrlen(t4));
    _lwrite (f,"\r\n",2);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

LPSTR GetParNr (LPSTR h,int FAR *Nr)
  {
  *Nr = 0 ;
  for ( ; ((*h >= '0') && (*h <= '9')) ; h ++ ) {
    *Nr = *Nr * 10 + *h - '0' ;
    }
  (*Nr) ++ ;
  return h ;
  }

inline BOOL myIsCharAlpha (char h)
  {
  return ((IsCharAlpha(h)) || (h == '_') || ((h >= '0') && (h <= '9')));
  }

inline BOOL myIsCharAlpha1(char ch,char ch1)
  {
    return ( IsCharAlpha(ch) ||
             ((ch >= '0') && (ch <= '9')) ||
             (ch == '_') ||
             ((ch == '.') && (ch1 >= '0') && (ch1 <= '9'))
           );
  } // myIsCharAlpha1

BOOL mystrcmp (LPSTR h,LPSTR Name,int FAR *len)
  {
  for ( *len = 0 ; ; ) {
    if ((*Name == '\0') && (!myIsCharAlpha (*h))) return TRUE ;
    if (*h++ == *Name++) (*len) ++ ;
    else                 break ;
    }
  return FALSE ;
  }


inline BOOL IsSpace (char ch)
  {
  return ((ch == ' ') || (ch == '\r') || (ch == '\t') || (ch == '\n'));
  }

LPSTR LongString::SkipSpace (LPSTR h,LPSTR FAR &lastStart)
  {
  if (IsSpace (*h)) {
    *this = *this + PartString (lastStart,h-lastStart);
    *this = *this + " " ;
    for ( ; IsSpace (*h) ; h ++ ) ;
    lastStart = h ;
    }
  return h ;
  }

LPSTR GetFullFieldName (LPSTR h,LPSTR AliasName,int tnum,LPTABLEDEF ti,LPDBREQUEST req)
  {
  *AliasName = '\0' ;
  if (IsCharAlpha(*h)) {
    // Es koennte sich um einen Feldnamen handeln
    LPTABLEDEF tx = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
    if (tx->IsInternTable()) {
      LPINTTABLE tix = LPINTTABLE (tx->GetDLLDef());
      LPPTABLE p = tix->GetTableByNum(0);
      LPTABLEDEF td0 = req->TableDef[0] ;
      for (int j = 0 ; j < int(p->AnzVars) ; j++) {
        int len;
        if (mystrcmp (h,tx->GetVarDef(j)->GetName(),&len)) {
          wsprintf (AliasName,"t%d.%s",tnum,dbase->GetAliasName (td0->GetVarDef(p->VarID[j])->GetName()));
          GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
          return h + len;
          }
        }
      }
    GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
    if (ti->IsInternTable()) {
      LPPTABLE p = LPINTTABLE (ti->GetDLLDef())->GetTableByNum(tnum);
      for (int i = 0 ; i < int(p->AnzVars) ; i++) {
        LPSTR Name = req->TableDef[tnum]->GetVarDef(p->VarID[i])->GetName();
        int len ;
        if (mystrcmp (h,Name,&len)) {
          wsprintf (AliasName,"t%d.%s",tnum,dbase->GetAliasName (Name));
          return h + len;
          }
        }
      for ( ; ((IsCharAlpha(*h)) || (*h == '_') || ((*h >= '0') && (*h <= '9'))) ; h++ ) ;
      return h ;
      }
    else {
      for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
        LPSTR Name = ti->GetVarDef(i)->GetName();
        int len ;
        if (mystrcmp (h,Name,&len)) {
          wsprintf (AliasName,"t%d.%s",tnum,dbase->GetAliasName (Name));
          return h + len;
          }
        }
      for ( ; myIsCharAlpha(*h) ; h++ ) ;
      return h ;
      }
    }
  else
    return h + 1 ;
  }

LPSTR AnalyseAlias (LPSTR h,LPSTR AliasName)
  {
  *AliasName = '\0' ;
  BOOL pFound = FALSE;
  LPSTR pPos;
  if (IsCharAlpha(*h)) {
    // Es koennte sich um eine Schluesselwort handeln
    for ( LPSTR x = AliasName ;
            ((IsCharAlpha(*h)) ||
             (*h == '_') ||
             ((*h >= '0') && (*h <= '9')) ||
             ((*h == '.') && ((pFound = ((h[1] >= '0') && (h[1] <= '9'))) && (pPos = x)))
            )
             ; *x++ = *h++ ) ;
    if (pFound)
      *pPos = '\0' ;
    else
      *x = '\0' ;
    LPSTR an = dbase->GetAliasName (AliasName);
    if (an != AliasName)
      lstrcpy (AliasName,an);
    return h ;
    }
  else
    return h + 1 ;
  }

BOOL NextIsSelect (LPSTR h)
  {
  int l;
  for ( ; ; h ++ ) {
    if ((*h != ' ') && (*h != '\r') && (*h != '\n') && (*h != '\t')) {
      return (mystrcmp (h,"SELECT",&l));
      }
    }
  return FALSE ;
  }

BOOL NextIsNullString (LPSTR h)
  {
  for (h++ ; ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) ; h++ ) ;
  int len;
  return (mystrcmp(h, "NULL", &len));
  }

#define STATE_NORMAL        0
#define STATE_INSERTFOUND   1
#define STATE_TABLEFOUND    2

LPSTR ODBCGetTableName (LPTABLEDEF t);
void odbcstmt::PushToDscList (int ParNum,LPDBREQUEST req)
  {
  BndList FAR *n = (BndList FAR *) GetGlobMem (sizeof(*n));
  n->Num = ParNum ;
  n->Next = NULL ;
  n->Type = req->ParamType [ParNum + 1];
  if (LastDsc) LastDsc->Next = n;
  LastDsc = n;
  if (TopDsc == NULL) TopDsc = n ;
  }

LPSTR LongString::AnalyseSeq (LPSTR source,int FAR *ParNums,int FAR *AnzPars,BOOL translateNull,LPTABLEDEF ti,LPDBREQUEST req,BOOL FAR *IdentityInsert,LPSTR IdentityInsertTable,odbcstmt FAR *stmt)
  {
  if (IdentityInsert != NULL)
    *IdentityInsert = FALSE;
  if (source == NULL) return NULL;
  BOOL instring = FALSE ;
  BOOL InSubSelect = FALSE ;
  LPSTR lastStart = source ;
  int level,len ;
  int State = STATE_NORMAL ;
  LPTABLEDEF td = NULL ;
  WORD TableID,VarIDToCheck,Version ;
  BOOL TableFound = FALSE ;
  if (*source) {
    LPSTR h = source ;
    if (*h == '$') {
      //Wenn das erste Zeichen �berhaupt ein $ ist, dann wird das Statement absolut nicht
      //betrachtet und ver�ndert
      h++ ;
      *this = *this + h ;
      }
    else {
      for ( ; *h ; ) {
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
          h = SkipSpace (h,lastStart);
          switch (State) {
            case STATE_NORMAL :
              switch (*h) {
                case '\0' :
                  break ;
                case '\'' :
                  instring = TRUE ;
                  h ++ ;
                  break ;
                case '=' :
                  if ((NextIsNullString (h)) && (translateNull)) {
                    *this = *this + PartString (lastStart,h-lastStart);
                    *this = *this + " IS ";
                    lastStart = h = h + 1;
                    }
                  else {
                    h++;
                    }
                  break ;
                case '<' :
                  if ((h[1] == '>') && NextIsNullString (h + 1) && (translateNull)) {
                    *this = *this + PartString (lastStart,h-lastStart);
                    *this = *this + " IS NOT ";
                    lastStart = h = h + 2;
                    }
                  else {
                    h++;
                    }
                  break ;
                case '%' :
                  {
                  int pnum;
                  LPSTR next = GetParNr (h+1,&pnum);
                  if ((req != NULL) && ((req->ParamType[pnum] == VAR_TIME) || (req->ParamType[pnum] == VAR_DATE) || (req->ParamType[pnum] == VAR_DATETIME)) && (req->Param[pnum] == NULL) &&
                      (!translateNull)) {
                    *this = *this + PartString (lastStart,h-lastStart) + "NULL" ;
                    }
                  else {
                    DBWIN_ASSERT ((ParNums != NULL) && (AnzPars != NULL));
                    *this = *this + PartString (lastStart,h-lastStart) + "?" ;
                      ParNums[(*AnzPars)++] = pnum;
                    }
                  lastStart = h = next ;
                  }
                  break ;
                case '$' :
                  {
                  LPSTR beg = h ;
                  int parNr;
                  h = GetParNr (h+1,&parNr);
                  *this = *this + PartString (lastStart,beg-lastStart) ;
                  if (stmt != NULL)
                    stmt->PushToDscList (parNr - 1,req); // Achtung: GetParNr zaehlt eins dazu
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
                  char AliasName [256];
                  if (mystrcmp (h,"WHERE",&len)) {
                    h += len ;
                    translateNull = TRUE ;
                    }
                  else if ((ti != NULL) && (req != NULL) && (!InSubSelect)) {
                    LPSTR behindField = GetFullFieldName(h,AliasName,0,ti,req);
                    if (*AliasName) {
                      *this = *this + PartString (lastStart,h-lastStart);
                      lastStart = h = behindField ;
                      *this = *this + AliasName;
                      }
                    else
                      h = behindField ;
                    }
                  else if (mystrcmp (h,"INSERT",&len)) {
                    h += len ;
                    State = STATE_INSERTFOUND ;
                    }
                  else {
                    LPSTR behindField = AnalyseAlias (h,AliasName);
                    if (*AliasName) {
                      *this = *this + dbase->GetAliasName (PartString (lastStart,h-lastStart));
                      lastStart = h = behindField ;
                      *this = *this + AliasName ;
                      }
                    else
                      h = behindField ;
                    }
                  break ;
                }
              break ;
            case STATE_INSERTFOUND :
              if (myIsCharAlpha(*h)) {
                char TableName[65];
                LPSTR x = TableName ;
                LPSTR hStart = h ;
                for ( ; myIsCharAlpha1 (*h,h[1]) ; ) {
                  *x++ = *h++ ;
                  }
                *x++ = '\0' ;
                TableID = GetTableAdmin()->GetTableID (NULL,TableName,&TableFound,&Version);
                if (TableFound) {
                  td = GetTableAdmin()->GetTableDef (TableID,Version);
                  *this = *this + PartString (lastStart,hStart-lastStart);
                  *this = *this + td->GetName();
                  lastStart = h ;
                  LPCLKEYDEF k0 = td->GetKeyDef(0);
                  if (k0->Attribute & CLKD_AUTOINC) {
                    VarIDToCheck = k0->VarID;
                    State = STATE_TABLEFOUND ;
                    }
                  else
                    State = STATE_NORMAL ;
                  }
                }
              else
                h ++ ;
              break ;   // STATE_INSERTFOUND
            case STATE_TABLEFOUND :
              switch (*h) {
                case '\'' :
                  *this = *this + PartString (lastStart,h-lastStart) ;
                  lastStart = h ;
                  h ++ ;
                  instring = TRUE ;
                  break ;
                case ')' :
                  *this = *this + PartString (lastStart,h-lastStart);
                  lastStart = h ;
                  h ++ ;
                  level = 0 ;
                  State = STATE_NORMAL ;
                  break ;
                default :
                  // Untersuchen, ob die Variable dem Autoinc - Feld entspricht
                  if (myIsCharAlpha(*h)) {
                    if (mystrcmp (h,td->GetVarDef (VarIDToCheck)->GetName(),&len)) {
                      if (IdentityInsert != NULL) {
                        *IdentityInsert = TRUE;
                        lstrcpy(IdentityInsertTable,ODBCGetTableName(td));
                        }
                      State = STATE_NORMAL ;    // Autoinc feld schon gesetzt
                      h += len ;
                      }
                    else {
                      char AliasName[256];
                      LPSTR behindField = AnalyseAlias (h,AliasName);
                      if (*AliasName) {
                        *this = *this + dbase->GetAliasName (PartString (lastStart,h-lastStart));
                        lastStart = h = behindField ;
                        *this = *this + AliasName ;
                        }
                      else
                        h = behindField ;
                      }
                    }
                  else
                    h ++ ;
                  break ;
                }
              break ;   // STATE_TABLEFOUND
            }
          }
        }
      if (lastStart != h)
         *this = *this + PartString (lastStart,h-lastStart);
      }
    }
  else
    *this = *this + "" ;

  if (TableFound)
    GetTableAdmin()->FreeTable (TableID,Version);

  return LPSTR (Ptr());
  }

BOOL IsNullAllowed (LPDBREQUEST req,LPTABLEDEF ti,LPCLRIDEF r)
  {
  DBWIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if ((req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->Property & VPROP_NOTNULL) == 0) return TRUE ;
    }
  return FALSE ;
  }

LPSTR LongString::AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,BOOL FAR *UseOuter,int FAR *ParNums,int FAR *AnzPars)
  {
  LPSTR JoinName[32];
  BOOL InSubSelect = FALSE ;
  int level = 0;
  // Ermitteln der Namen der Felder, die in den Join eingehen
  DBWIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if (UseOuter[e.TableNumber])
      UseOuter[tnum] = TRUE ;
    char JN[66];
    wsprintf (JN,"t%d.%s",e.TableNumber,
          req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->GetName());
    JoinName[i] = LPSTR(GetGlobMem (lstrlen(JN)+1));
    lstrcpy (JoinName[i],JN);
    }

  // Austauschen der %xx Teile durch den Alias Namen
  BOOL instring = FALSE ;
  LPSTR lastStart = r->name ;
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
        case '=' :
          if (NextIsNullString (h)) {
            *this = *this + PartString (lastStart,h-lastStart);
            *this = *this + " IS ";
            lastStart = h = h + 1;
            }
          else {
            h++;
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
        case '<' :
          if ((h[1] == '>') && NextIsNullString (h + 1)) {
            *this = *this + PartString (lastStart,h-lastStart);
            *this = *this + " IS NOT ";
            lastStart = h = h + 2;
            }
          else {
            h++;
            }
          break ;
        case '%' :
          {
          *this = *this + PartString (lastStart,h-lastStart) ;
          int FieldNr;
          lastStart = h = GetParNr (h+1,&FieldNr);
          if (FieldNr >= int(r->AnzSegs + 2)) {
            FieldNr -= int(r->AnzSegs);
            DBWIN_ASSERT ((ParNums != NULL) && (AnzPars != NULL));
            *this = *this + PartString (lastStart,h-lastStart) + "?" ;
            ParNums[(*AnzPars)++] = FieldNr ;
            }
          else {
            *this = *this + JoinName[FieldNr-2] ;
            }
          }
          break ;
        default :
          {
          char AliasName [256];
          if ((ti != NULL) && (!InSubSelect)) {
            LPSTR behindField = GetFullFieldName(h,AliasName,tnum,ti,req);
            if (*AliasName) {
              *this = *this + PartString (lastStart,h-lastStart);
              lastStart = h = behindField ;
              *this = *this + AliasName;
              }
            else
              h = behindField ;
            }
          else {
            LPSTR behindField = AnalyseAlias (h,AliasName);
            if (*AliasName) {
              *this = *this + dbase->GetAliasName (PartString (lastStart,h-lastStart));
              lastStart = h = behindField ;
              *this = *this + AliasName ;
              }
            else
              h = behindField ;
            }
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

void database::FetchTableNames (HSTMT hstmt)
  {
  char qualifier [128],owner [128],name [128],type [128],remarks [256];
  SDWORD cbqualifier,cbowner,cbname,cbtype,cbremarks;
  SQLBindCol (hstmt,1,SQL_C_CHAR,qualifier,sizeof(qualifier),&cbqualifier);
  SQLBindCol (hstmt,2,SQL_C_CHAR,owner,sizeof(owner),&cbowner);
  SQLBindCol (hstmt,3,SQL_C_CHAR,name,sizeof(name),&cbname);
  SQLBindCol (hstmt,4,SQL_C_CHAR,type,sizeof(type),&cbtype);
  SQLBindCol (hstmt,5,SQL_C_CHAR,remarks,sizeof(remarks),&cbremarks);
  for ( ; ; ) {
    if (TestRetCode (hstmt,SQLFetch (hstmt))) {
      TableData d;
      d.IsTested = FALSE ;
      TableHash->SetData (name,&d,sizeof(d));
      }
    else
      break ;
    }
  }

void database::FetchColNames (HSTMT hstmt,hash *ColHash)
  {
  #define STR_LEN 65
  #define REM_LEN 257

  UCHAR  szQualifier[STR_LEN], szOwner[STR_LEN];
  UCHAR  szTableName[STR_LEN], szColName[STR_LEN];
  UCHAR  szTypeName[STR_LEN], szRemarks[REM_LEN];
  SDWORD Precision, Length;
  SWORD  DataType, Scale, Radix, Nullable;

  SDWORD cbQualifier, cbOwner, cbTableName, cbColName;
  SDWORD cbTypeName, cbRemarks, cbDataType, cbPrecision;

  SDWORD cbLength, cbScale, cbRadix, cbNullable;

  SQLBindCol(hstmt, 1, SQL_C_CHAR, szQualifier, STR_LEN,&cbQualifier);
  SQLBindCol(hstmt, 2, SQL_C_CHAR, szOwner, STR_LEN, &cbOwner);
  SQLBindCol(hstmt, 3, SQL_C_CHAR, szTableName, STR_LEN,&cbTableName);
  SQLBindCol(hstmt, 4, SQL_C_CHAR, szColName, STR_LEN, &cbColName);
  SQLBindCol(hstmt, 5, SQL_C_SHORT, &DataType, sizeof(DataType), &cbDataType);
  SQLBindCol(hstmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, &cbTypeName);
  SQLBindCol(hstmt, 7, SQL_C_LONG, &Precision, sizeof(Precision), &cbPrecision);
  SQLBindCol(hstmt, 8, SQL_C_LONG, &Length, sizeof(Length), &cbLength);
  SQLBindCol(hstmt, 9, SQL_C_SHORT, &Scale, sizeof(Scale), &cbScale);
  SQLBindCol(hstmt, 10, SQL_C_SHORT, &Radix, sizeof(Radix), &cbRadix);
  SQLBindCol(hstmt, 11, SQL_C_SHORT, &Nullable, sizeof(Nullable), &cbNullable);
  SQLBindCol(hstmt, 12, SQL_C_CHAR, szRemarks, REM_LEN, &cbRemarks);

  for ( ; ; ) {
    if (TestRetCode (hstmt,SQLFetch (hstmt))) {
      ColData d;
      AnsiUpper (LPSTR(szColName));
      lstrcpy (d.TypeName,LPSTR(szTypeName));
      AnsiUpper (d.TypeName);
      ColHash->SetData (LPSTR(szColName),&d,sizeof(d));
      }
    else
      break ;
    }
  }

#define MAXVARSIZE 0x8000
void database::StartTableTest ()
  {
  if (!TableFetched) {
    // Befuellen der Hashtabelle mit den Tabellen
    TableHash = new hash (111,STRKEY);
    HSTMT hstmt = GetStatementHandle ();
    if (TestRetCode (hstmt,SQLTables (hstmt,NULL,0,NULL,0,NULL,0,(UCHAR FAR *)"TABLE",SQL_NTS))) {
      FetchTableNames (hstmt);
      }
    FreeStatementHandle (hstmt);
    TableFetched = TRUE ;
    }
  }

extern void InitializeSybaseAnywhereAuthentication(void);
extern void FinishSybaseAnywhereAuthentication(void);
extern HANDLE hLibInst;
char MySection[64];
LPSTR Section()
  {
  if (*MySection == '\0') {
    char szFileName[256];
    GetModuleFileName (HINSTANCE(hLibInst), szFileName, sizeof(szFileName));
    int i = lstrlen(szFileName);
    for ( ; (i > 0) && (szFileName[i] != '\\') && (szFileName[i] != ':'); i--);
    if (i > 0)
      i++;
    i += 3;  // dds
    lstrcpy(MySection,szFileName + i);
    for (i = 0; (MySection[i] != '\0') && (MySection[i] != '.'); i++);
    MySection[i] = '\0';  // .dll abschneiden
    AnsiUpper(MySection);
    }
  return MySection;
  }

database::database (UCHAR FAR * _server,UCHAR FAR * _user,UCHAR FAR * _password)
  {
  char buf[20];
  GetPrivateProfileString (Section(),"Authenticate", "no", buf, sizeof(buf),GetIniName());
  if (lstrcmp(buf,"yes") == 0)
    InitializeSybaseAnywhereAuthentication();

  hdbc = SQL_NULL_HDBC ;
  henv = SQL_NULL_HENV ;
  RETCODE retCode = SQLAllocEnv (&henv) ;
  if (retCode == SQL_SUCCESS) {
    retCode = SQLAllocConnect (henv, &hdbc) ;
    if (retCode == SQL_SUCCESS) {
      SQLSetConnectOption (hdbc, SQL_LOGIN_TIMEOUT, 5) ;
      SQLSetConnectOption (hdbc, SQL_TXN_ISOLATION, SQL_TXN_READ_COMMITTED) ;
      retCode = SQLConnect (
         hdbc, _server, SQL_NTS, _user, SQL_NTS, _password, SQL_NTS ) ;
      if ((retCode == SQL_SUCCESS) ||
          (retCode == SQL_SUCCESS_WITH_INFO)) {
        char drivername[256], driverversion[256], mainVersion[3];
        SWORD namelen = 0;
        retCode = SQLGetInfo (hdbc, SQL_DBMS_NAME, drivername, sizeof(drivername), &namelen);
        retCode = SQLGetInfo (hdbc, SQL_DBMS_VER, driverversion, sizeof(driverversion), &namelen);
        if (!lstrcmp(drivername,"Microsoft SQL Server")) {
          DatabaseType = DT_MSSQLSERVER;
#define  SQL_PRESERVE_CURSORS   1204
#define  SQL_PC_ON              1L
          RETCODE r = SQLSetConnectOption (hdbc,SQL_PRESERVE_CURSORS,SQL_PC_ON);
          if (r != SQL_SUCCESS)
            r = fehler (SQL_NULL_HSTMT,r) ;
          }
        else if (!lstrcmp(drivername,"ACCESS"))
          DatabaseType = DT_ACCESS;
        else
          DatabaseType = DT_SYBASEANYWHERE;
        AliasNames = new hash (111,STRKEY);
        // Namen, die umgesetzt werden
        AliasNames->SetData ("TABLEID","XTABLEID",9);
        AliasNames->SetData ("TEXT","XTEXT",6);
        if (DatabaseType == DT_MSSQLSERVER)
          AliasNames->SetData ("COUNT","XCOUNT",7);
        else
          AliasNames->SetData ("OPTIONS","XOPTIONS",9);
        if (DatabaseType == DT_SYBASEANYWHERE) {
          lstrcpyn (mainVersion,driverversion,3);
          if (lstrcmp(mainVersion,"05") != 0) {
            //Versionen > 5
            AliasNames->SetData ("TOP","XTOP",5);
            AliasNames->SetData ("BOTTOM","XBOTTOM",8);
            }
          AliasNames->SetData ("VARIABLE","XVARIABLE",10);
          }
        // Variablenbuffer anlegen
        hGVarBuffer = GlobalAlloc (GMEM_FIXED,MAXVARSIZE);    // Das wird wohl reichen
        VarBuffer = LPSTR(GlobalLock (hGVarBuffer));
        hGBlockBuffer = GlobalAlloc (GMEM_FIXED,MAXVARSIZE);    // Das wird wohl reichen
        BlockBuffer = LPSTR(GlobalLock (hGBlockBuffer));
        }
      else {
        retCode = fehler (SQL_NULL_HSTMT,retCode) ;
        SQLFreeEnv (henv) ;
        }
      }
    else {
      retCode = fehler (SQL_NULL_HSTMT,retCode) ;
      SQLFreeEnv (henv) ;
      }
    }
  else
    retCode = fehler (SQL_NULL_HSTMT,retCode) ;
  }

database::~database ()
  {
  if (TableHash != NULL)
    delete TableHash;
  if (AliasNames != NULL)
    delete AliasNames;
  if (hdbc != SQL_NULL_HDBC) {
    SQLDisconnect (hdbc) ;
    SQLFreeConnect (hdbc) ;
    }
  if (henv != SQL_NULL_HENV)
    SQLFreeEnv (henv) ;

  char buf[20];
  GetPrivateProfileString (Section(),"Authenticate", "no", buf, sizeof(buf),GetIniName());
  if (lstrcmp(buf,"yes") == 0)
    FinishSybaseAnywhereAuthentication();

  FreeErrToIgnore ();
  }

void DisConnect ()
  {
  if (dbase != NULL)
    delete dbase;
  }

LPSTR database::GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0)
  {
  *doSize = FALSE ;
  switch (v->mType) {
    case VAR_LONG :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC)) {
        if (DatabaseType == DT_MSSQLSERVER)
          return "INTEGER IDENTITY" ;
        else
          return "INTEGER DEFAULT AUTOINCREMENT" ;
        }
      else
        return "INTEGER" ;
      break ;
    case VAR_DEC :
      return "REAL" ;
      break ;
    case VAR_STR :
      if (v->VarSize > 254) {
        if (DatabaseType == DT_MSSQLSERVER)
          return "TEXT" ;
        else
          return "LONG VARCHAR" ;
        }
      else {
        if (DatabaseType == DT_MSSQLSERVER) {
          *doSize = TRUE ;
          return "VARCHAR" ;
          }
        else {
          *doSize = TRUE ;
          return "CHAR" ;
          }
        }
      break ;
    case VAR_POINT :
      *doSize = TRUE ;
      return "BINARY" ;
      break ;
    case VAR_CONT :
      if (DatabaseType == DT_MSSQLSERVER)
        return "IMAGE" ;
      else
        return "LONG BINARY" ;
      break ;
    case VAR_STRARR :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC))
        if (DatabaseType == DT_MSSQLSERVER)
          return "SMALLINT IDENTITY" ;
        else
          return "SMALLINT DEFAULT AUTOINCREMENT" ;
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
      if (DatabaseType == DT_MSSQLSERVER)
        return "DATETIME" ;
      else
        return "DATE" ;
      break ;
    case VAR_OBJ :
      if (v->VarSize > 254) {
        if (DatabaseType == DT_MSSQLSERVER)
          return "IMAGE" ;
        else
          return "LONG BINARY" ;
        }
      else {
        *doSize = TRUE ;
        return "BINARY" ;
        }
      break ;
    case VAR_TIME :
      if (DatabaseType == DT_MSSQLSERVER)
        return "DATETIME" ;
      else
        return "TIME" ;
      break ;
    case VAR_DATETIME :
      if (DatabaseType == DT_MSSQLSERVER)
        return "DATETIME" ;
      else
        return "TIMESTAMP" ;
      break ;
    case VAR_BLOB :
      if (DatabaseType == DT_MSSQLSERVER)
        return "IMAGE" ;
      else
        return "LONG BINARY" ;
      break ;
    default :
      DBWIN_ASSERT(FALSE);
    }
  return NULL;
  }
LPSTR database::BlockVarName ()
  {
  return "XXXBlockedXXX" ;
  }
LPSTR database::BlockTypeName ()
  {
  if (DatabaseType == DT_MSSQLSERVER)
    return "IMAGE" ;
  else
    return "LONG BINARY" ;
  }

BOOL database::TestTableDef (LPTABLEDEF td)
  {
  static char TCheck[32];
  if (td->GetTableProperty ("ODBC_Check",TCheck,sizeof(TCheck)) > 0)
    if (lstrcmp(TCheck,"no") == 0) return TRUE;
  hash *ColHash = new hash (111,STRKEY);
  HSTMT hstmt = GetStatementHandle ();
  BOOL res = FALSE ;
  if (TestRetCode (hstmt,SQLColumns (hstmt,NULL,0,NULL,0,(UCHAR FAR *)ODBCGetTableName (td),SQL_NTS,NULL,0))) {
    FetchColNames (hstmt,ColHash);
    res = TRUE ;
    BOOL blockedDone = FALSE ;
    for (int i = 0 ; ((i < td->GetAnzVars ()) && (res)) ; i++) {
      char VarName[128];
      char TypeName[128];
      *VarName = '\0';
      LPVARDEF v = td->GetVarDef(i);
      if (v->VarSize != 0xFFFF) {
        lstrcpy (VarName,GetAliasName (v->GetName()));
        AnsiUpper (VarName);
        BOOL doSize;
        lstrcpy (TypeName,GetTypeName (v,i,&doSize,td->GetKeyDef(0)));
        }
      else {
        if (!blockedDone) {
          lstrcpy (VarName,BlockVarName()) ;
          AnsiUpper (VarName);
          lstrcpy (TypeName,BlockTypeName());
          }
        blockedDone = TRUE ;
        }
      if (*VarName) {
        ColData FAR *d = (ColData FAR *) ColHash->GetData (VarName);
        if (d == NULL) res = FALSE ;    // Datentypvergleich wird keiner gemacht
        }
      }
    }
  FreeStatementHandle (hstmt);
  return res;
  }

BOOL database::CreateAllIndex (LPTABLEDEF td)
  {
  // CreateIndexStatements...
  LongString c;
  HSTMT hstmt = GetStatementHandle ();

  WORD oldKeyNr = 0xFFFF;
  BOOL first = TRUE ;
  BOOL correct = TRUE ;

  for (int i = 0 ; (correct) ; i++) {
    LPCLKEYDEF k = (i < td->GetAnzKeySegs()) ? td->GetKeyDef (i) : NULL ;
    if ((k == NULL) || (k->KeyNmbr != oldKeyNr)) {
      if (!first) {
        c = c + ")" ;
        correct = TestRetCode (hstmt,SQLExecDirect (hstmt,c.Ptr(),SQL_NTS));
        }
      if (k != NULL) {
        c.Clear ();
        LPVARDEF v = td->GetVarDef (k->VarID);
        if (DatabaseType == DT_MSSQLSERVER) {
          LongString i;
          i = i + k->name + ODBCGetTableName (td);
          char iname[31];
          lmemset(iname,'\0',sizeof(iname));
          lstrncpy(iname,(LPSTR)i.Ptr(),30);
          c = c + "CREATE " + (((k->Attribute & CLKD_UNIQUE) != 0) ? "UNIQUE INDEX " : "INDEX ") +
                  iname + " ON " + ODBCGetTableName (td) + "(" + GetAliasName(v->GetName()) ;
          }
        else
          c = c + "CREATE " + (((k->Attribute & CLKD_UNIQUE) != 0) ? "UNIQUE INDEX " : "INDEX ") +
                  k->name + ODBCGetTableName (td) + " ON " + ODBCGetTableName (td) + "(" + GetAliasName(v->GetName()) ;
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

  FreeStatementHandle (hstmt);
  return correct ;
  }

BOOL database::CreateTable (LPTABLEDEF td,BOOL withIndex)
  {
  static char TCheck[32];
  if (td->GetTableProperty ("ODBC_Check",TCheck,sizeof(TCheck)) > 0)
    if (lstrcmp(TCheck,"no") == 0) return TRUE;
  LongString s;
  s = s + "CREATE TABLE " + ODBCGetTableName (td) + "(";
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
      if (v->Property & VPROP_NOTNULL) {
        s = s + " NOT NULL " ;
        }
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
  if (DatabaseType == DT_MSSQLSERVER) {
    s = s + ")" ;
    }
  else {
    BOOL firstPSeg = TRUE ;
    for (i = 0 ; i < td->GetAnzKeySegs () ; i++) {
      LPCLKEYDEF k = td->GetKeyDef(i);
      if (k->KeyNmbr == 0) {
        LPVARDEF v = td->GetVarDef(k->VarID) ;
        if (firstPSeg)
          s = s + ",PRIMARY KEY (" ;
        else
          s = s + "," ;
        s = s + GetAliasName(v->GetName());
        firstPSeg = FALSE ;
        }
      }
    s = s + "))" ;
    }

  if (DatabaseType == DT_SYBASEANYWHERE) {
    char Buffer[256],BufferFile[256];
    if (td->GetTableProperty ("SQLANY_DBSPACE",Buffer,sizeof(Buffer))) {
      if (td->GetTableProperty ("SQLANY_DBFILE",BufferFile,sizeof(BufferFile))) {
        HSTMT hstmt = GetStatementHandle ();
        LongString xsp;
        xsp = xsp + "CREATE DBSPACE " + Buffer + " AS '" + BufferFile + "'";
        SQLExecDirect (hstmt,xsp.Ptr(), SQL_NTS);
        FreeStatementHandle (hstmt);
        }
      s = s + " IN " + Buffer ;
      }
    }
  HSTMT hstmt = GetStatementHandle ();
  BOOL correct = TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(), SQL_NTS));
  FreeStatementHandle (hstmt);

  if ((withIndex) && (correct))
    correct = CreateAllIndex (td);

  return correct ;
  }

BOOL WithForeignKeys(void)
  {
  char buf[20];
  GetPrivateProfileString (Section(),"ForeignKeys", "no", buf, sizeof(buf),GetIniName());
  return (lstrcmp(buf,"yes") == 0);
  }

void database::LogForeign (LPSTR cmd,HSTMT hstmt,RETCODE retCode)
  {
  OFSTRUCT Of;
  LPSTR fname = makeIni ("foreign.log");
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
    if (cmd != NULL)
      _lwrite (f,cmd,lstrlen(cmd));
    _lwrite (f," - ",3);
    UCHAR errorMessage [SQL_MAX_MESSAGE_LENGTH + 100];
    *errorMessage = '\0';
    if ((retCode == SQL_ERROR) || (retCode == SQL_SUCCESS_WITH_INFO))
      retCode = fehlertext (hstmt,retCode,(LPSTR)&errorMessage,FALSE);
    if (*errorMessage)
      _lwrite (f,(LPSTR)&errorMessage,lstrlen((LPSTR)&errorMessage));
    else
      _lwrite (f,"success",7);
    _lwrite (f,"\r\n",2);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

BOOL database::CreateForeignKeys (LPTABLEDEF td)
  {
  if (DatabaseType == DT_MSSQLSERVER) return TRUE;

  LongString c;
  HSTMT hstmt = GetStatementHandle ();

  for (int i = 0 ; i < td->GetAnzRIDefs() ; i++) {
    LPCLRIDEF ri = td->GetRIDef (i);
    DBWIN_ASSERT(ri->Type == CLKR_STANDARD);
    c.Clear ();
    BOOL NotNull = FALSE;
    StandardRI FAR *sri = ri->GetSRI();
    for (WORD j = 0 ; j < ri->AnzSegs ; j++ ) {
      if (j > 0)
        sri = sri->GetNextSRI();
      LPVARDEF v = td->GetVarDef (sri->VarID);
      if (v->Property & VPROP_NOTNULL)
        NotNull = TRUE;
      }
    c = c + "ALTER TABLE " + ODBCGetTableName (td) + " ADD " +
            (NotNull ? "NOT NULL " : "") + "FOREIGN KEY (" ;
    sri = ri->GetSRI();
    for (j = 0 ; j < ri->AnzSegs ; j++ ) {
      if (j > 0) {
        c = c + "," ;
        sri = sri->GetNextSRI();
        }
      LPVARDEF v = td->GetVarDef (sri->VarID);
      c = c + GetAliasName(v->GetName()) ;
      }
    c = c + ") REFERENCES " + ri->name + " (";
    sri = ri->GetSRI();
    for (j = 0 ; j < ri->AnzSegs ; j++ ) {
      if (j > 0) {
        c = c + "," ;
        sri = sri->GetNextSRI();
        }
      c = c + GetAliasName(sri->ForeignField) ;
      }
    c = c + ")" ;
    int status = SQLExecDirect (hstmt,c.Ptr(),SQL_NTS);
    LogForeign ((LPSTR)c.Ptr(),hstmt,status);
    }

  FreeStatementHandle (hstmt);
  return TRUE ;
  }

static BOOL InCreate ;
BOOL database::TestTable (LPTABLEDEF td)
  {
  if (!TableFetched) return TRUE ;

  BOOL res = TRUE ;
  TableData FAR *d = (TableData FAR *) TableHash->GetData (ODBCGetTableName (td));
  if (d != NULL) {
    if (!d->IsTested) {
      if (!TestTableDef (td)) {
        char outtxt[256];
        wsprintf (outtxt,"Tabelle %s stimmt nicht mit der Clientdefinition �berein!",ODBCGetTableName (td));
        WIN_ASSERT_TEXT(FALSE,outtxt);
        res = FALSE ;
        }
      else {
        static BOOL AddForeignKeys = WithForeignKeys();
        if (AddForeignKeys && InCreate) {
          // bei _CREATE auch die foreign constraints erzeugen
          CreateForeignKeys(td);
          }
        }
      d->IsTested = TRUE ;
      }
    }
  else {
    // Die Tabelle gibts noch nicht -> Vater informieren
    BOOL noCheck = FALSE ;
    static char TCheck[32];
    if (td->GetTableProperty ("ODBC_Check",TCheck,sizeof(TCheck)) > 0)
      if (lstrcmp(TCheck,"no") == 0) noCheck = TRUE;
    if ((!InAlter()) && (!InCreate) && (!noCheck)) {
      char outtxt[256];
      wsprintf (outtxt,"Tabelle %s nicht definiert! Contiune zum Erstellen der Tabelle",ODBCGetTableName (td));
      WIN_ASSERT_TEXT(FALSE,outtxt);
      }
    res = CreateTable (td,TRUE);
    if (res) {
      TableData di;
      di.IsTested = TRUE ;
      TableHash->SetData (ODBCGetTableName (td),&di,sizeof(di));
      }
    }

  return res;
  }

struct errtoignore {
  SDWORD  Code ;
  RETCODE RetCode ;
  } ;
int database::fehlertext (HSTMT hstmt,int retCode,LPSTR errorMessage,BOOL doIgnore)
  {
  *errorMessage = '\0';
  SDWORD ptNativeError = -1L;
  UCHAR szSqlState [SQL_MAX_MESSAGE_LENGTH] ;
  UCHAR myerrorMessage [SQL_MAX_MESSAGE_LENGTH] ;
  SWORD lenErrorMessage ;
  SQLError (henv, hdbc, hstmt, szSqlState, &ptNativeError, (UCHAR *) &myerrorMessage, SQL_MAX_MESSAGE_LENGTH - 1, &lenErrorMessage) ;
  if (doIgnore) {
    if (ErrorCodeToIgnore (DatabaseType,ptNativeError,(LPSTR)&myerrorMessage)) {
      myerrorMessage[0] = '0' ; //Kein Assert machen
      return retCode ;
      }
    else {
      if ((DatabaseType != DT_MSSQLSERVER) && (DatabaseType != DT_ACCESS)) {
        // Nicht bei Microsoft SQL Server
        if (lstrcmp (LPSTR (szSqlState),"01004") == 0) return SQL_SUCCESS;
        if (lstrcmp (LPSTR (szSqlState),"01000") == 0) return SQL_SUCCESS;
        static errtoignore ptNativeErrorToIgnor [] = {
            {     2L, SQL_SUCCESS } ,
            { -1605L, SQL_ERROR   } ,
            {  -196L, SQL_ERROR   } ,
            {  5701L, SQL_SUCCESS }
            };
        for (int i = 0 ; i < sizeof(ptNativeErrorToIgnor) / sizeof(ptNativeErrorToIgnor[0]) ; i++) {
          if (ptNativeErrorToIgnor[i].Code == ptNativeError)
            return ptNativeErrorToIgnor[i].RetCode ;
          }
        }
      else {
       if (lstrcmp (LPSTR(szSqlState),"01S02") == 0)
          return SQL_SUCCESS;
        static errtoignore ptNativeErrorToIgnor [] = {
            { 2601L, SQL_ERROR   } ,
            { 8153L, SQL_SUCCESS }
            };
        for (int i = 0 ; i < sizeof(ptNativeErrorToIgnor) / sizeof(ptNativeErrorToIgnor[0]) ; i++) {
          if (ptNativeErrorToIgnor[i].Code == ptNativeError)
            return ptNativeErrorToIgnor[i].RetCode ;
          }
        }
      }
    }
  lstrcpy(errorMessage,(LPSTR)&myerrorMessage);
  char ptnative[32];
  wsprintf (ptnative,"[%ld]",ptNativeError);
  lstrcat (errorMessage,"(");
  lstrcat (errorMessage,LPSTR(szSqlState));
  lstrcat (errorMessage,")");
  lstrcat (errorMessage,ptnative);
  return retCode;
  } //database::fehlertext

int database::fehler (HSTMT hstmt,int retCode)
  {
  UCHAR myErrorMessage [SQL_MAX_MESSAGE_LENGTH + 100];
  retCode = fehlertext (hstmt,retCode,(LPSTR)&myErrorMessage,TRUE);
  if (*myErrorMessage)
    DBWIN_ASSERT_TEXT (FALSE,(LPSTR)&myErrorMessage);
  return retCode;
  } //database::fehler

/*--------< Verwaltung eines Statements >---------*/
WORD AnzOpenStatements;
#ifdef WIN32
static LPSTR DefServerName = "CLINICUM32";
#else
static LPSTR DefServerName = "CLINICUM";
#endif
static LPSTR DefUserName   = "ADMIN";
static LPSTR DefPassWord   = "UGSEWL";

UCHAR *ServerName()
  {
  static char MyServerName[64];
  GetPrivateProfileString (Section(),"DataSource", DefServerName, MyServerName, sizeof(MyServerName),GetIniName());
  return (UCHAR *)MyServerName;
  }

UCHAR *UserName()
  {
  static char MyUserName[64];
  GetPrivateProfileString (Section(),"UserName", DefUserName, MyUserName, sizeof(MyUserName),GetIniName());
  return (UCHAR *)MyUserName;
  }

UCHAR *PassWord()
  {
  static char MyPassWord[64];
  GetPrivateProfileString (Section(),"PassWord", DefPassWord, MyPassWord, sizeof(MyPassWord),GetIniName());
  return (UCHAR *)MyPassWord;
  }

BOOL CheckFile (LPODBCSTMT stmt,BOOL first)
  {
  BOOL res = TRUE ;
  if (dbase == NULL)
    // Login to database
    dbase = new database (ServerName(),UserName(),PassWord());
  if (first) {
    for (int i = 0 ; i < int(stmt->req->AnzTables) ; i++) {
      if (stmt->req->TableDef[i] != NULL)
        res = dbase->TestTable (stmt->req->TableDef[i]);
      }
    }
  return res;
  }

void CloseAllDataFiles ()
  {
  WIN_ASSERT (AnzOpenStatements == 0);
  if (dbase != NULL)
    delete dbase ;
  }

SWORD GetCType(WORD mType)
  {
  if (dbase->DatabaseType == DT_SYBASEANYWHERE) {
    static SWORD MTypeTOCType [] = {
      /* VAR_LONG                0 */  SQL_C_LONG ,
      /* VAR_DEC                 1 */  SQL_C_FLOAT ,
      /* VAR_STR                 2 */  SQL_C_CHAR ,
      /* VAR_POINT               3 */  SQL_C_BINARY ,
      /* VAR_CONT                4 */  SQL_C_BINARY ,
      /* VAR_STRARR              5 */  SQL_C_SHORT ,
      /* VAR_FLAG                6 */  SQL_C_SHORT ,
      /* VAR_SCALE               7 */  SQL_C_BINARY ,
      /* VAR_PICTURE             8 */  SQL_C_BINARY ,
      /* VAR_DATE                9 */  SQL_C_DATE ,
      /* VAR_PROC                10 */ SQL_C_BINARY ,
      /* VAR_IMAGE               11 */ SQL_C_BINARY ,
      /* VAR_DWORD               12 */ SQL_C_LONG ,
      /* VAR_OBJ                 13 */ SQL_C_BINARY ,
      /* VAR_BITMAP              14 */ SQL_C_BINARY ,
      /* VAR_TIME                15 */ SQL_C_TIME ,
      /* VAR_QLONG               16 */ SQL_C_BINARY ,
      /* VAR_BLOB                17 */ SQL_C_BINARY ,
      /* VAR_DATETIME            15 */ SQL_C_TIMESTAMP
      };

    WIN_ASSERT (mType < sizeof(MTypeTOCType)/sizeof(WORD));
    return MTypeTOCType[mType];
    }
  else {
    static SWORD MTypeTOCType [] = {
      /* VAR_LONG                0 */  SQL_C_LONG ,
      /* VAR_DEC                 1 */  SQL_C_FLOAT ,
      /* VAR_STR                 2 */  SQL_C_CHAR ,
      /* VAR_POINT               3 */  SQL_C_BINARY ,
      /* VAR_CONT                4 */  SQL_C_BINARY ,
      /* VAR_STRARR              5 */  SQL_C_SHORT ,
      /* VAR_FLAG                6 */  SQL_C_SHORT ,
      /* VAR_SCALE               7 */  SQL_C_BINARY ,
      /* VAR_PICTURE             8 */  SQL_C_BINARY ,
      /* VAR_DATE                9 */  SQL_C_TIMESTAMP ,
      /* VAR_PROC                10 */ SQL_C_BINARY ,
      /* VAR_IMAGE               11 */ SQL_C_BINARY ,
      /* VAR_DWORD               12 */ SQL_C_LONG ,
      /* VAR_OBJ                 13 */ SQL_C_BINARY ,
      /* VAR_BITMAP              14 */ SQL_C_BINARY ,
      /* VAR_TIME                15 */ SQL_C_TIMESTAMP ,
      /* VAR_QLONG               16 */ SQL_C_BINARY ,
      /* VAR_BLOB                17 */ SQL_C_BINARY ,
      /* VAR_DATETIME            18 */ SQL_C_TIMESTAMP
      };
    WIN_ASSERT (mType < sizeof(MTypeTOCType)/sizeof(WORD));
    return MTypeTOCType[mType];
    }
  }

SWORD GetSQLType(WORD mType,SLONG VarSize)
  {
  SWORD FAR *mtSQL;
  static SWORD MTypeTOSQL [] = {
    /* VAR_LONG                0 */  SQL_INTEGER ,
    /* VAR_DEC                 1 */  SQL_FLOAT ,
    /* VAR_STR                 2 */  SQL_CHAR ,
    /* VAR_POINT               3 */  SQL_BINARY ,
    /* VAR_CONT                4 */  SQL_BINARY ,
    /* VAR_STRARR              5 */  SQL_SMALLINT ,
    /* VAR_FLAG                6 */  SQL_SMALLINT ,
    /* VAR_SCALE               7 */  SQL_BINARY ,
    /* VAR_PICTURE             8 */  SQL_BINARY ,
    /* VAR_DATE                9 */  SQL_DATE ,
    /* VAR_PROC                10 */ SQL_BINARY ,
    /* VAR_IMAGE               11 */ SQL_BINARY ,
    /* VAR_DWORD               12 */ SQL_INTEGER ,
    /* VAR_OBJ                 13 */ SQL_BINARY ,
    /* VAR_BITMAP              14 */ SQL_BINARY ,
    /* VAR_TIME                15 */ SQL_TIME ,
    /* VAR_QLONG               16 */ SQL_BINARY ,
    /* VAR_BLOB                17 */ SQL_LONGVARBINARY ,
    /* VAR_DATETIME            18 */ SQL_TIMESTAMP
    };
  static SWORD MTypeTOSQL_MS [] = {
    /* VAR_LONG                0 */  SQL_INTEGER ,
    /* VAR_DEC                 1 */  SQL_FLOAT ,
    /* VAR_STR                 2 */  SQL_VARCHAR ,
    /* VAR_POINT               3 */  SQL_BINARY ,
    /* VAR_CONT                4 */  SQL_BINARY ,
    /* VAR_STRARR              5 */  SQL_SMALLINT ,
    /* VAR_FLAG                6 */  SQL_SMALLINT ,
    /* VAR_SCALE               7 */  SQL_BINARY ,
    /* VAR_PICTURE             8 */  SQL_BINARY ,
    /* VAR_DATE                9 */  SQL_TIMESTAMP ,
    /* VAR_PROC                10 */ SQL_BINARY ,
    /* VAR_IMAGE               11 */ SQL_BINARY ,
    /* VAR_DWORD               12 */ SQL_INTEGER ,
    /* VAR_OBJ                 13 */ SQL_BINARY ,
    /* VAR_BITMAP              14 */ SQL_BINARY ,
    /* VAR_TIME                15 */ SQL_TIMESTAMP ,
    /* VAR_QLONG               16 */ SQL_BINARY ,
    /* VAR_BLOB                17 */ SQL_LONGVARBINARY ,
    /* VAR_DATETIME            18 */ SQL_TIMESTAMP
    };
  if (dbase->DatabaseType == DT_SYBASEANYWHERE)
    mtSQL = MTypeTOSQL;
  else
    mtSQL = MTypeTOSQL_MS;

  if ((VarSize >= 255) && (mType != VAR_BLOB)) {
    if (mType == VAR_OBJ)      return SQL_LONGVARBINARY ;
    else if (mType == VAR_STR) return SQL_LONGVARCHAR ;
    else WIN_ASSERT (FALSE);
    return SQL_LONGVARCHAR ;
    }
  else {
    WIN_ASSERT (mType < sizeof(MTypeTOSQL)/sizeof(WORD));
    return mtSQL[mType];
    }
  }

SLONG GetTypePrecision (WORD mType,LPVOID parData,WORD VarSize)
  {
  if (mType == VAR_BLOB) {
    return 0 ;  // SQL_DATA_AT_EXECUTION
    }
  else if (VarSize == 0xFFFF) {
    return GetBlockSize(parData);
    }
  else
    return VarSize ;
  }

LPVOID ConvertTo(WORD mType,LPVOID parData,ConvertBuffer FAR *cb,SDWORD FAR *length)
  {
  if (parData == NULL) return NULL ;
  switch (mType) {
    case VAR_BLOB :
      {
      *length = 0;
      return parData;
      }
      break ;
    case VAR_DATE :
      {
      if (dbase->DatabaseType == DT_SYBASEANYWHERE) {
        DATE_STRUCT FAR *r = (DATE_STRUCT FAR *) cb->GetBuffer (sizeof(*r));
        packdate FAR *pd = (packdate FAR *) parData ;
        r->year = pd->year ;
        r->month = pd->month;
        r->day = pd->day ;
        return r;
        }
      else {
        TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) cb->GetBuffer (sizeof(*r));
        packdate FAR *pd = (packdate FAR *) parData ;
        r->year = pd->year ;
        r->month = pd->month;
        r->day = pd->day ;
        r->hour = 0 ;
        r->minute = 0 ;
        r->second = 0 ;
        r->fraction = 0 ;
        *length = sizeof(*r);
        return r;
        char tst[32];
        wsprintf (tst,"%04d-%02d-%02d",pd->year,pd->month,pd->day);
        LPSTR res = LPSTR (cb->GetBuffer (lstrlen(tst) + 1));
        lstrcpy (res,tst);
        *length = lstrlen(tst) + 1;
        return res;
        }
      }
      break ;
    case VAR_TIME :
      {
      if (dbase->DatabaseType == DT_SYBASEANYWHERE) {
        TIME_STRUCT FAR *r = (TIME_STRUCT FAR *) cb->GetBuffer (sizeof(*r));
        packtime FAR *pt = (packtime FAR *) parData ;
        r->hour = pt->hour ;
        r->minute = pt->minute ;
        r->second = pt->second ;
        return r;
        }
      else {
        TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) cb->GetBuffer (sizeof(*r));
        packtime FAR *pt = (packtime FAR *) parData ;
        r->year = 1900 ;
        r->month = 1 ;
        r->day = 1 ;
        r->hour = pt->hour ;
        r->minute = pt->minute ;
        r->second = pt->second ;
        r->fraction = 0 ;
        *length = sizeof(*r);
        return r;
        char tst[32];
        wsprintf (tst,"%02d:%02d:%02d",pt->hour,pt->minute,pt->second);
        LPSTR res = LPSTR (cb->GetBuffer (lstrlen(tst) + 1));
        lstrcpy (res,tst);
        *length = lstrlen(tst) + 1;
        return res;
        }
      }
      break ;
    case VAR_DATETIME :
      {
      TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) cb->GetBuffer (sizeof(*r));
      packdatetime FAR *pdt = (packdatetime FAR *) parData ;
      r->year = pdt->pd.year ;
      r->month = pdt->pd.month ;
      r->day = pdt->pd.day ;
      r->hour = pdt->pt.hour ;
      r->minute = pdt->pt.minute ;
      r->second = pdt->pt.second ;
      r->fraction = 0 ;
      *length = sizeof(*r);
      return r;
      }
      break ;
    case VAR_STR :
      *length = lstrlen(LPSTR(parData));
      if (*length == 0) return NULL ;
      break ;
    default :
      *length = GetBlockSize(parData);
      break ;
    }
  return parData;
  }

int odbcstmt::StandardDelete ()
  {
  LongString s,w;
  LPTABLEDEF td = req->TableDef[0];
  int ParNums[64];
  int AnzPars = 0;
  ConvertBuffer cb;

  LPSTR seq = w.AnalyseSeq (req->SelectionName,ParNums,&AnzPars,TRUE) ;
  s = s + "DELETE FROM " + ODBCGetTableName (td);
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;
  BOOL correct = dbase->TestRetCode (hstmt,SQLPrepare (hstmt,s.Ptr(),SQL_NTS));

  SLONG llen[CB_PARAM * 2] ;
  for (int i = 0 ; ((i < AnzPars) && (correct)) ; i++) {
    SLONG precision = GetTypePrecision(req->ParamType[ParNums[i]],req->Param[ParNums[i]]);
    llen[i] = precision;
    LPVOID sdata = ConvertTo(req->ParamType[ParNums[i]],req->Param[ParNums[i]],&cb,llen + i);
    SDWORD len = llen[i];
    if (sdata == NULL) llen[i] = SQL_NULL_DATA ;
    else if (llen[i] == 0) {
      if (dbase->DatabaseType == DT_MSSQLSERVER)
        llen[i] = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
      else
        llen[i] = SQL_LEN_DATA_AT_EXEC(0);
      }
    correct = (dbase->TestRetCode (hstmt,
                  SQLBindParameter (hstmt,i+1,
                  SQL_PARAM_INPUT,
                  GetCType(req->ParamType[ParNums[i]]),
                  GetSQLType(req->ParamType[ParNums[i]],precision),
                  precision,
                  0,
                  sdata,
                  len,
                  llen + i
              )));
    }
  if (correct)
    correct = (dbase->TestRetCode (hstmt,SQLExecute (hstmt)));
  return (correct) ? DBCALL_SUCCESS : DBCALL_ERROR ;
  }

#pragma optimize("", off)
void odbcstmt::SelectStatement (LPTABLEDEF ti,LongString FAR &s,int FAR *ParNums,int FAR *AnzPars,BOOL forList)
  {
  if (req->AnzElems > 0) {
    // Auf jeden Fall mit alias Namen fuer Tabellen arbeiten
    s = s + "SELECT " ;
    BOOL blockedDone = FALSE ;
    for (int i = 0 ; i < req->AnzElems ; i++) {
      if (i > 0) s = s + "," ;
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      if (v->VarSize != 0xFFFF) {
        s = s + "t" + req->elem[i].TableNumber + "." +
                dbase->GetAliasName(v->GetName()) ;
        }
      else {
        if (!blockedDone)
          s = s + "t" + req->elem[i].TableNumber + "." +
                  dbase->BlockVarName() ;
        blockedDone = TRUE ;
        }
      }
    s = s + " FROM " ;
    for (i = 0 ; i < int (req->AnzTables) - 1 ; i++)
      s = s + "(" ;
    BOOL UseOuter[CB_TABLEDEF] ;
    for (i = 0 ; i < CB_TABLEDEF ; i++)
      UseOuter[i] = FALSE ;
    LPSTR aj ;
    LongString js;
    for (i = 0 ; i < int (req->AnzTables) ; i++) {
      js.Clear () ;
      if (i > 0) {
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
        aj = js.AnalyseJoin (req,ti,i,ti->GetRIDef(i-1),UseOuter,ParNums,AnzPars) ;
        if (UseOuter[i])
          s = s + " LEFT OUTER JOIN " ;
        else
          s = s + " INNER JOIN " ;
        }
      s = s + ODBCGetTableName (req->TableDef[i]) + " t" +
                            i;
      if (i > 0) {
        s = s + " ON (" + aj + "))";
        }
      else
        if ((forList) && (dbase->DatabaseType == DT_MSSQLSERVER))
          s = s + " (FASTFIRSTROW) ";
      }
    }
  else {
    s = s + "SELECT " ;
    LPTABLEDEF td = req->TableDef[0];
    BOOL blockedDone = FALSE ;
    for (int i = 0 ; i < td->GetAnzVars () ; i++) {
      LPVARDEF v = td->GetVarDef(i);
      if (v->VarID == 0xFFFF) {
        if (i > 0)
          s = s + "," ;
        s = s + dbase->GetAliasName (td->GetVarDef(i)->GetName()) ;
        }
      else {
        if (!blockedDone) {
          if (i > 0)
            s = s + "," ;
          s = s + dbase->BlockVarName() ;
          }
        blockedDone = TRUE ;
        }
      }
    s = s + " FROM " + ODBCGetTableName (req->TableDef[0]) + " t0" ;
    }
  }

void odbcstmt::WhereStatement (LongString FAR &s,int FAR *ParNums,int FAR *AnzPars,LPTABLEDEF td)
  {
  LongString w;
  LPSTR seq = w.AnalyseSeq (req->SelectionName,ParNums,AnzPars,TRUE,td,req);
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;
  }

void odbcstmt::OrderStatement (LongString FAR &s,LPTABLEDEF td)
  {
  LongString o;
  LPSTR order = o.AnalyseSeq (req->OrderStatement,0,NULL,TRUE,td,req);
  if ((order != NULL) && (*order))
    s = s + " ORDER BY " + order ;
  }
#pragma optimize("", on)

LPVOID odbcstmt::ConvertToMData_T (WORD mType,LPVOID data,SDWORD FAR *Size,BOOL FAR *doFree)
  {
  *doFree = FALSE ;
  static packdate pdres;
  static packtime ptres;
  static packdatetime pdt;
  switch (mType) {
    case VAR_DATE :
      {
      if (dbase->DatabaseType == DT_MSSQLSERVER) {
        TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) data;
        pdres.year = r->year;
        pdres.month = BYTE(r->month);
        pdres.day = BYTE(r->day);
        }
      else {
        DATE_STRUCT FAR *r = (DATE_STRUCT FAR *) data;
        pdres.year = r->year;
        pdres.month = BYTE(r->month);
        pdres.day = BYTE(r->day);
        }

      *Size = sizeof(pdres);
      return &pdres;
      }
      break ;
    case VAR_DATETIME :
      {
      TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) data;
      pdt.pd.year = r->year;
      pdt.pd.month = BYTE(r->month);
      pdt.pd.day = BYTE(r->day);
      pdt.pt.hour = BYTE(r->hour);
      pdt.pt.minute = BYTE(r->minute);
      pdt.pt.second = BYTE(r->second);

      *Size = sizeof(pdt);
      return &pdt;
      }
      break ;
    case VAR_TIME :
      {
      if (dbase->DatabaseType == DT_MSSQLSERVER) {
        TIMESTAMP_STRUCT FAR *r = (TIMESTAMP_STRUCT FAR *) data;
        ptres.hour = BYTE(r->hour);
        ptres.minute = BYTE(r->minute);
        ptres.second = BYTE(r->second);
        }
      else {
        TIME_STRUCT FAR *r = (TIME_STRUCT FAR *) data;
        ptres.hour = BYTE(r->hour);
        ptres.minute = BYTE(r->minute);
        ptres.second = BYTE(r->second);
        }
      *Size = sizeof(ptres);
      return &ptres;
      }
    case VAR_STR :
      {
      LPVOID res = GetGlobMem (int (*Size) + 1) ;
      lmemcpy (res,data,int(*Size));
      *doFree = TRUE ;
      (*Size)++ ;
      return res ;
      }
    default :
      return data ;
    }
  }

LPVOID odbcstmt::ConvertToMData (LPVARDEF v,LPVOID data,SDWORD FAR *Size,BOOL FAR *doFree)
  {
  return ConvertToMData_T (v->mType,data,Size,doFree);
  }

#define MAX_SIZE  0x8000
LPVOID odbcstmt::GetColData (LPVARDEF v,UWORD col,SDWORD FAR *Size,BOOL FAR *doFree,BOOL FAR *blockDone)
  {
  *doFree = FALSE ;
  if (v->mType == VAR_BLOB) {
    if (Size) {
      static BlobDesc bdsc ;
      for ( DWORD sizeDone = 0L ; ; ) {
        SLONG sizeRead ;
        if (sizeDone > 0L)
          bdsc.hGmem = GlobalReAlloc (bdsc.hGmem,sizeDone + MAX_SIZE,GMEM_MOVEABLE) ;
        else
          bdsc.hGmem = GlobalAlloc (GMEM_MOVEABLE,MAX_SIZE) ;
        char huge * Buffer = (char huge *) GlobalLock (bdsc.hGmem) + sizeDone ;
        RETCODE status = SQLGetData (hstmt,col,SQL_C_BINARY,
                                    Buffer,MAX_SIZE,&sizeRead) ;
        if ((status == SQL_SUCCESS) || (status == SQL_SUCCESS_WITH_INFO)) {
          if ((sizeRead == SQL_NO_TOTAL) || (sizeRead > MAX_SIZE)) {
            sizeDone += MAX_SIZE ;
            }
          else if (sizeRead == SQL_NULL_DATA) {
            GlobalUnlock (bdsc.hGmem);
            GlobalFree (bdsc.hGmem);
            return NULL ;
            }
          else {
            bdsc.Size = sizeDone + sizeRead ;
            bdsc.hGmem = GlobalReAlloc (bdsc.hGmem,bdsc.Size,GMEM_MOVEABLE) ;
            *Size = sizeof(bdsc);
            return &bdsc ;
            }
          }
        else {
          GlobalUnlock (bdsc.hGmem);
          GlobalFree (bdsc.hGmem);
          return NULL ;
          }
        }
      }
    else
      return NULL;
    }
  else {
    if (v->VarSize == 0xFFFF) {
      WIN_ASSERT (blockDone != NULL);
      if (!*blockDone) {
        dbase->BlockValid = dbase->TestRetCode (hstmt,SQLGetData (hstmt,col,SQL_C_BINARY,
                                  dbase->BlockBuffer,MAXVARSIZE,&dbase->BlockSize)) ;
        if (dbase->BlockSize == SQL_NULL_DATA) dbase->BlockValid = FALSE;
        *blockDone = TRUE ;
        }
      if (dbase->BlockValid) {
        return dbase->FindData (v->VarID,Size);
        }
      return NULL;
      }
    else {
      if (dbase->TestRetCode (hstmt,SQLGetData (hstmt,col,GetCType(v->mType),
                                dbase->VarBuffer,MAXVARSIZE,Size))) {
        if (*Size == SQL_NULL_DATA) return NULL ;
        else                        return ConvertToMData (v,dbase->VarBuffer,Size,doFree);
        }
      else
        return NULL;
      }
    }
  }

LPDBRECORD odbcstmt::StoreRow (LPTABLEDEF ti)
  {
  LPDBRECORD rec = new DBRecord (req);
  SDWORD Size;
  BOOL blockDone = FALSE ;
  if (req->AnzElems > 0) {
    // Stueck fuer Stueck aus den echten Tabellen abholen
    BOOL doFree ;
    for (int i = 0 ; (i < int(req->AnzElems)) ; i++) {
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      LPVOID data = GetColData (v,i+1,&Size,&doFree,&blockDone);
      if (data != NULL)
        rec->Initialize (i,data,int(Size));
      if (doFree)
        FreeGlobMem (data);
      }
    }
  else {
    // Stueck fuer Stueck aus ti abholen
    for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
      BOOL doFree ;
      LPVARDEF v = ti->GetVarDef(i);
      LPVOID data = GetColData (v,i+1,&Size,&doFree,&blockDone);
      if (data != NULL)
        rec->Initialize (i,data,int(Size));
      if (doFree)
        FreeGlobMem (data);
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  return rec;
  }

int odbcstmt::StandardGet ()
  {
  LongString s;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  int ParNums[64];
  int AnzPars = 0;
  ConvertBuffer cb;

  BOOL correct = TRUE ;
  if (prepareDone)
    SQLFreeStmt (hstmt,SQL_CLOSE);
 
  SelectStatement (ti,s,ParNums,&AnzPars);
  WhereStatement (s,ParNums,&AnzPars,req->TableDef[0]);
  correct = dbase->TestRetCode (hstmt,SQLPrepare (hstmt,s.Ptr(),SQL_NTS));
  prepareDone = TRUE ;

  SLONG llen[CB_PARAM * 2];
  for (int i = 0 ; ((i < AnzPars) && (correct)) ; i++) {
    SLONG precision = GetTypePrecision(req->ParamType[ParNums[i]],req->Param[ParNums[i]]);
    llen[i] = precision;
    LPVOID sdata = ConvertTo(req->ParamType[ParNums[i]],req->Param[ParNums[i]],&cb,llen + i);
    SDWORD len = llen[i];
    if (sdata != NULL) {
      if (llen[i] == 0) {
        if (dbase->DatabaseType == DT_MSSQLSERVER)
          llen[i] = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
          // llen[i] = SQL_LEN_DATA_AT_EXEC(0);
        else
          llen[i] = SQL_LEN_DATA_AT_EXEC(0);
        }
      correct = (dbase->TestRetCode (hstmt,
                    SQLBindParameter (hstmt,i+1,
                    SQL_PARAM_INPUT,
                    GetCType(req->ParamType[ParNums[i]]),
                    GetSQLType(req->ParamType[ParNums[i]],precision),
                    precision,
                    0,
                    sdata,
                    len,
                    llen + i
                                  )));
      }
    else {
      GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
      return DBCALL_NODATA ;
      }
    }

  if (correct)
    correct = (dbase->TestRetCode (hstmt,SQLExecute (hstmt)));

  if (correct)
    correct = BindColData (ti);

  // So jetzt koennen die Daten geholt werden
  //---------------------------------------------------------

  if (correct) {
    RETCODE status = SQLFetch (hstmt);
    if (status == SQL_SUCCESS_WITH_INFO) {
      dbase->TestRetCode (hstmt,status);
      status = SQL_SUCCESS ;
      }
    else if (status == SQL_NO_DATA_FOUND) {
      GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
      return DBCALL_NODATA ;
      }
    else
      dbase->TestRetCode (hstmt,status);
    if (status == SQL_SUCCESS) {
      StoreExtendedRow (ti,ADDLINEPOS_END);
      dbase->TestRetCode (hstmt,SQLCancel (hstmt));
      }
    }

#ifdef UEBERLEGT
  // So jetzt koennen die Daten geholt werden ...
  if (correct) {
    RETCODE status = SQLFetch (hstmt);
    if (status == SQL_NO_DATA_FOUND) {
      GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
      return DBCALL_NODATA ;
      }
    if (dbase->TestRetCode (hstmt,status)) {
      // Na also, ab damit ...
      res->AddLine (1,ADDLINEPOS_END);
      res->SetRes (0,StoreRow (ti));
      dbase->TestRetCode (hstmt,SQLCancel (hstmt));
      }
    }
#endif
  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  return (correct) ? DBCALL_SUCCESS : DBCALL_ERROR ;
  }

WORD odbcstmt::GetColSize (LPVARDEF v)
  {
  WORD Size ;
  switch (v->mType) {
    case VAR_DATE :
      if (dbase->DatabaseType == DT_MSSQLSERVER)
        Size = sizeof(TIMESTAMP_STRUCT) ;
      else
        Size = sizeof(DATE_STRUCT) ;
      break ;
    case VAR_TIME :
      if (dbase->DatabaseType == DT_MSSQLSERVER)
        Size = sizeof(TIMESTAMP_STRUCT) ;
      else
        Size = sizeof(TIME_STRUCT) ;
      break ;
    case VAR_DATETIME :
      Size = sizeof(TIMESTAMP_STRUCT) ;
      break ;
    case VAR_STR :
      Size = v->VarSize + 1;
      break ;
    case VAR_STRARR :
    case VAR_FLAG :
      Size = sizeof(DBINT);
      break ;
    case VAR_LONG :
      Size = sizeof(LONG);
      break ;
    default :
      Size = v->VarSize ;
    }
  return Size ;
  }
BOOL odbcstmt::BindColData (LPTABLEDEF ti)
  {
  WORD ActOffset = 0;
  BOOL correct = TRUE ;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef (req->elem[i].VarID);
      if ((v->VarSize != 0xFFFF) && (v->mType != VAR_BLOB)) {
        // Nur fixe Variablen werden gebunden, der Rest wird mit GetColData
        // Gelesen
        WORD Size = GetColSize (v);
        correct = dbase->TestRetCode (hstmt,SQLBindCol (hstmt,i+1,
                              GetCType(v->mType),
                              dbase->VarBuffer+ActOffset+sizeof(DWORD),
                              Size,(SDWORD FAR *) (dbase->VarBuffer+ActOffset)
                                    ));
        ActOffset += sizeof(SDWORD) + Size ;
        }
      }
    }
  else if (ti != NULL) {
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF v = ti->GetVarDef (i);
      if ((v->VarSize != 0xFFFF) && (v->mType != VAR_BLOB)) {
        WORD Size = GetColSize (v);
        correct = dbase->TestRetCode (hstmt,SQLBindCol (hstmt,i+1,
                              GetCType(v->mType),
                              dbase->VarBuffer+ActOffset+sizeof(DWORD),
                              Size,(SDWORD FAR *) (dbase->VarBuffer+ActOffset)
                                    ));
        ActOffset += sizeof(SDWORD) + Size ;
        }
      }
    }

  // Binden der expliziten '$' Parameter
  BndList FAR *h = TopDsc ;
  unsigned char nmDummy[256];
  short nml,dt,dti,dtn;
  for ( int cn = 1 ; (h != NULL) ; h = h->Next) {
    SQLDescribeCol (hstmt,cn,nmDummy,256,&nml,&dt,&h->VarLen,&dti,&dtn);
    if (h->VarLen) {
      if (h->VarLen > 32768) {
        h->VarLen = 32768;
        }
      h->retBuffer = LPSTR(GetGlobMem (short (h->VarLen + 1)));
      }
    cn = cn + 1;
    }

  int i = 1 ;
  for ( h = TopDsc ; h != NULL ; h = h->Next) {
    correct = dbase->TestRetCode (hstmt,SQLBindCol (hstmt,i,
                          GetCType(h->Type),
                          h->retBuffer,
                          h->VarLen + 1,&h->retStatus
                                 ));
    i = i + 1 ;
    }
  return correct;
  }

// Uebergabeparameter speichern
void odbcstmt::StoreBndParam (BOOL correct)
  {
  for ( BndList FAR *h = TopDsc ; h != NULL ; h = h->Next) {
    BOOL doFree;
    if (correct && ((h->retStatus != SQL_NULL_DATA) && (h->retStatus > 0))) {
      LPVOID cd = ConvertToMData_T (h->Type,h->retBuffer,&h->retStatus,&doFree);
      if (cd != NULL)
        req->SetOutParam (h->Num,cd,int(h->retStatus));
      else
        req->SetOutParam (h->Num,NULL,0);
      if (doFree) FreeGlobMem (cd);
      }
    else
      req->SetOutParam (h->Num,NULL,0);
    }
  }

void odbcstmt::StoreExtendedRow (LPTABLEDEF ti,WORD pos)
  {
  WORD ActOffset = 0;
  LPDBRECORD rec = new DBRecord (req);
  BOOL blockDone = FALSE ;
  LPVOID Data ;
  BOOL doFree ;
  SDWORD lSize;
  if (req->AnzElems > 0) {
    for (int i = 0 ; (i < int(req->AnzElems)) ; i++) {
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef (req->elem[i].VarID);
      if ((v->mType == VAR_BLOB) || (v->VarSize == 0xFFFF)) {
        Data = GetColData (v,i+1,&lSize,&doFree,&blockDone);
        }
      else {
        SDWORD FAR *pcbValue = (SDWORD FAR *) (dbase->VarBuffer+ActOffset);
        Data = LPVOID (pcbValue+1);
        WORD Size = GetColSize (v);
        if (*pcbValue == SQL_NULL_DATA)
          Data = NULL ;
        else {
          Data = ConvertToMData (v,Data,pcbValue,&doFree);
          lSize = *pcbValue;
          //Debugausgabe tempor�r:
          if (DoLog ("ATTR0LONG")) {
            if ((i == 0) && (v->mType == VAR_LONG)) {
              char lstr[32];
              wsprintf (lstr,"%ld",*((long *) Data));
              LogCmd("StoreExtendedRow-0-LONG:",lstr,NULL,NULL);
              }
            }
          }
        ActOffset += sizeof(SDWORD) + Size ;
        }
      if (Data != NULL) {
        rec->Initialize (i,Data,int(lSize));
        if (doFree) FreeGlobMem (Data);
        }
      }
    }
  else {
    for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
      LPVARDEF v = ti->GetVarDef (i);
      if ((v->mType == VAR_BLOB) || (v->VarSize == 0xFFFF)) {
        Data = GetColData (v,i+1,&lSize,&doFree,&blockDone);
        }
      else {
        SDWORD FAR *pcbValue = (SDWORD FAR *) (dbase->VarBuffer+ActOffset);
        Data = LPVOID (pcbValue+1);
        WORD Size = GetColSize (v);
        if (*pcbValue == SQL_NULL_DATA)
          Data = NULL ;
        else {
          Data = ConvertToMData (v,Data,pcbValue,&doFree);
          lSize = *pcbValue;
          }
        ActOffset += sizeof(SDWORD) + Size ;
        }
      if (Data != NULL) {
        rec->Initialize (i,Data,int(lSize));
        if (doFree) FreeGlobMem (Data);
        }
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);
  res->AddLine (1,pos);
  res->SetRes (0,rec);
  }

int odbcstmt::StandardList (BOOL first,short DatabaseType)
  {
  LongString s,w;
  LPTABLEDEF ti;
  if (req->AnzTables > 0)
    ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  else
    ti = NULL;
  int ParNums[64];
  int AnzPars = 0;
  ConvertBuffer cb;

  BOOL correct = TRUE ;
  if ((Op != DBOP_GETNEXT) && (Op != DBOP_GETPREV)) {
    if (IsToExecute()) {
      if (!first) {
        ClearStmt ();
        GetStatementHandle();
        }
      if (req->AnzTables > 0) {
        int wParNums[64];
        int wAnzPars = 0;
        WhereStatement (w,wParNums,&wAnzPars,req->TableDef[0]);  // Die muessen auf jeden Fall da sein
        SelectStatement (ti,s,ParNums,&AnzPars,TRUE);
        s = s + LPSTR(w.Ptr());
        // die Parameter der WHERE-Klausel bitte HINTER denen der JOINs !!!!
        for (int i = 0; i < wAnzPars; i++)
          ParNums[AnzPars++] = wParNums[i];
        OrderStatement (s,req->TableDef[0]);

        if (correct)
          correct = dbase->TestRetCode (hstmt,SQLSetStmtOption (hstmt,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC));
        }
      else
        s.AnalyseSeq (req->SelectionName,ParNums,&AnzPars,TRUE,NULL,req,NULL,NULL,this) ;
      if (DoLog ()) {
        LogCmd ("","",(LPSTR) s.Ptr(),"");
        }

      correct = dbase->TestRetCode (hstmt,SQLPrepare (hstmt,s.Ptr(),SQL_NTS));
      // Binding vor execute
      if (correct)
        correct = BindColData (ti);

      prepareDone = TRUE ;

      SLONG llen[CB_PARAM * 2];
      for (int i = 0 ; ((i < AnzPars) && (correct)) ; i++) {
        SLONG precision = GetTypePrecision(req->ParamType[ParNums[i]],req->Param[ParNums[i]]);
        llen[i] = precision;
        LPVOID sdata = ConvertTo(req->ParamType[ParNums[i]],req->Param[ParNums[i]],&cb,llen + i);
        SDWORD len = llen[i];
        if (sdata != NULL) {
          if (llen[i] == 0) {
            if (dbase->DatabaseType == DT_MSSQLSERVER)
              llen[i] = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
              // llen[i] = SQL_LEN_DATA_AT_EXEC(0);
            else
              llen[i] = SQL_LEN_DATA_AT_EXEC(0);
            }
          correct = (dbase->TestRetCode (hstmt,
                        SQLBindParameter (hstmt,i+1,
                        SQL_PARAM_INPUT,
                        GetCType(req->ParamType[ParNums[i]]),
                        GetSQLType(req->ParamType[ParNums[i]],precision),
                        precision,
                        0,
                        sdata,
                        len,
                        llen + i
                                      )));
          }
        else {
          if (ti) GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

          return DBCALL_NODATA ;
          }
        }
      if (correct)
        correct = (dbase->TestRetCode (hstmt,SQLExecute (hstmt)));
      }
    }

  // So jetzt koennen die Daten geholt werden ...
  RETCODE status  = SQL_SUCCESS ;
  int rowsRead    = 0 ;
  #ifdef UEBERLEGT
  if (correct)
    correct = BindColData (ti);
  #endif
  if (correct) {
    UDWORD AnzRows;
    UWORD RowStatus ;
    switch (Op) {
      case DBOP_GETFIRST :
        for ( ; ((status == SQL_SUCCESS) && ((rowsRead < RecsToGet) || (RecsToGet < 0))) ; ) {
          status = SQLExtendedFetch (hstmt,
                /* (rowsRead == 0) ? SQL_FETCH_FIRST : */ SQL_FETCH_NEXT,
                0,&AnzRows,&RowStatus);
          if (status == SQL_SUCCESS_WITH_INFO) {
            dbase->TestRetCode (hstmt,status);
            status = SQL_SUCCESS ;
            }
          if (status == SQL_SUCCESS) {
            if (ti)
              StoreExtendedRow (ti,ADDLINEPOS_END);
            else
              StoreBndParam ();
            rowsRead ++ ;
            }
          else if (status != SQL_NO_DATA_FOUND) {
            correct = dbase->TestRetCode (hstmt,status);
            }
          }
        break ;
      case DBOP_GETLAST :
        for ( ; ((status == SQL_SUCCESS) && ((rowsRead < RecsToGet) || (RecsToGet < 0))) ; ) {
          status = SQLExtendedFetch (hstmt,
                (rowsRead == 0) ? SQL_FETCH_LAST : SQL_FETCH_PREV,
                0,&AnzRows,&RowStatus);
          if (status == SQL_SUCCESS_WITH_INFO) {
            dbase->TestRetCode (hstmt,status);
            status = SQL_SUCCESS ;
            }
          if (status == SQL_SUCCESS) {
            if (ti)
              StoreExtendedRow (ti,ADDLINEPOS_START);
            else
              StoreBndParam ();
            rowsRead ++ ;
            }
          else if (status != SQL_NO_DATA_FOUND) {
            correct = dbase->TestRetCode (hstmt,status);
            }
          }
        break ;
      case DBOP_GETNEXT :
        for ( ; ((status == SQL_SUCCESS) && ((rowsRead < RecsToGet) || (RecsToGet < 0))) ; ) {
          status = SQLExtendedFetch (hstmt,
                SQL_FETCH_NEXT,
                0,&AnzRows,&RowStatus);
          if (status == SQL_SUCCESS_WITH_INFO) {
            dbase->TestRetCode (hstmt,status);
            status = SQL_SUCCESS ;
            }
          if (status == SQL_SUCCESS) {
            if (ti != NULL)
              StoreExtendedRow (ti,ADDLINEPOS_END);
            else
              StoreBndParam ();
            rowsRead ++ ;
            }
          else if (status != SQL_NO_DATA_FOUND) {
            correct = dbase->TestRetCode (hstmt,status);
            }
          }
        break ;
      case DBOP_GETPREV :
        for ( ; ((status == SQL_SUCCESS) && ((rowsRead < RecsToGet) || (RecsToGet < 0))) ; ) {
          status = SQLExtendedFetch (hstmt,
                SQL_FETCH_PREV,
                0,&AnzRows,&RowStatus);
          if (status == SQL_SUCCESS_WITH_INFO) {
            dbase->TestRetCode (hstmt,status);
            status = SQL_SUCCESS ;
            }
          if (status == SQL_SUCCESS) {
            if (ti != NULL)
              StoreExtendedRow (ti,ADDLINEPOS_START);
            else
              StoreBndParam ();
            rowsRead ++ ;
            }
          else if (status != SQL_NO_DATA_FOUND) {
            correct = dbase->TestRetCode (hstmt,status);
            }
          }
        break ;
      }
    }

  if (ti) GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

  if (correct) {
    if (status == SQL_NO_DATA_FOUND)
      return (rowsRead > 0) ? DBCALL_ENDOFFILE : DBCALL_NODATA ;
    else
      return DBCALL_SUCCESS ;
    }
  else {
    int j = 0 ;
    int k = 100 / j ;
    return DBCALL_ERROR ;
    }
  }

#define MAXBLOCKEDSIZE  0x8000
#pragma optimize("", off)
void odbcstmt::PushToBlocked (LPVOID Data,WORD VarID)
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
BOOL odbcstmt::EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars,int FAR *AnzVars)
  {
  BOOL correct = TRUE;
  if (BlockedData != NULL) {
    SLONG precision = GetBlockSize (BlockedData);
    SLONG FAR *llen = (SLONG FAR *) (dbase->VarBuffer + *(AnzPars) * sizeof(SLONG)) ;
    *llen = SLONG (precision);
    LPVOID sdata = BlockedData;
    SDWORD len = *llen;
    correct = (dbase->TestRetCode (hstmt,
                  SQLBindParameter (hstmt,*AnzPars + 1,
                  SQL_PARAM_INPUT,
                  SQL_C_BINARY,
                  SQL_LONGVARBINARY,
                  precision,
                  0,
                  sdata,
                  len,
                  llen
                                  )));
    if (*AnzVars > 0) {
      s = s + "," ;
      v = v + "," ;
      }
    s = s + dbase->BlockVarName ();
    if (correct) {
      v = v + "?" ;
      (*AnzPars) ++ ;
      (*AnzVars) ++ ;
      }
    }
  else if (*AnzVars == 0) {
    s = s + dbase->BlockVarName ();
    v = v + "NULL" ;
    (*AnzVars) ++ ;
    }
  return correct ;
  }
BOOL odbcstmt::EnlargeInsert (LPVARDEF vd,int VarID,LongString FAR &s,LongString FAR &v,ConvertBuffer FAR *b,int FAR *AnzPars,int FAR *AnzVars,BOOL doSetNull)
  {
  LPVOID Data = res->first->rec[0]->Get(VarID);
  BOOL correct ;
  if (Data != NULL) {
    if (vd->VarSize != 0xFFFF) {
      SLONG precision = GetTypePrecision(vd->mType,Data,vd->VarSize);
      SLONG FAR *llen = (SLONG FAR *) (dbase->VarBuffer + *(AnzPars) * sizeof(SLONG)) ;
      *llen = SLONG (precision);
      LPVOID sdata = ConvertTo(vd->mType,Data,b,llen);
      SDWORD len = *llen;
      if (sdata == NULL) *llen = SQL_NULL_DATA ;
      else if (*llen == 0) {
        if (dbase->DatabaseType == DT_MSSQLSERVER) {
          *llen = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
          // llen[i] = SQL_LEN_DATA_AT_EXEC(0);
          precision = 2000000;
          }
        else
          *llen = SQL_LEN_DATA_AT_EXEC(0);
        }
      correct = (dbase->TestRetCode (hstmt,
                    SQLBindParameter (hstmt,*AnzPars + 1,
                    SQL_PARAM_INPUT,
                    GetCType(vd->mType),
                    GetSQLType(vd->mType,precision),
                    precision,
                    0,
                    sdata,
                    len,
                    llen
                )));
      if (*AnzVars > 0) {
        s = s + "," ;
        v = v + "," ;
        }
      s = s + dbase->GetAliasName(vd->GetName()) ;
      v = v + "?" ;
      (*AnzPars) ++ ;
      (*AnzVars) ++ ;
      }
    else {
      PushToBlocked (Data,vd->VarID);
      correct = TRUE ;
      }
    }
  else if (doSetNull) {
    if (vd->VarSize != 0xFFFF) {
      if (*AnzVars > 0) {
        s = s + "," ;
        v = v + "," ;
        }
      s = s + dbase->GetAliasName(vd->GetName()) ;
      v = v + "NULL" ;
      (*AnzVars) ++ ;
      }
    correct = TRUE ;
    }
  return correct ;
  }
#pragma optimize("", on)

LPDBRECORD odbcstmt::GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize)
  {
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  LPDBRECORD rec = new DBRecord (req);
  for (int i = 0 ; i < int(old->GetAnzVars()) ; i++) {
    if ((i == PrimkeyID) && (PrimKeyData != NULL))
      rec->Initialize (i,PrimKeyData,PrimKeySize);
    else {
      LPVOID data = old->Get(i);
      if (data != NULL) {
        LPVARDEF v = ti->GetVarDef (i);
        if (v->mType == VAR_BLOB) {
          LPBLOBDESC b = LPBLOBDESC(data);
          BlobDesc bn = *b ;
          bn.hGmem = GlobalAlloc (GMEM_MOVEABLE,b->Size);
          hmemcpy (GlobalLock (bn.hGmem),GlobalLock (b->hGmem),b->Size);
          rec->Initialize (i,&bn,sizeof(bn));
          }
        else
          rec->Initialize (i,data,GetBlockSize(data));
        }
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

  return rec;
  }

#ifdef WITHAUTOINCLOCK
DLLExport void _export WINAPI GetNWAddress (LPSTR,int);
BOOL odbcstmt::LockForInsert (LPSTR Name)
  {
  char NWName [64];
  GetNWAddress (NWName,sizeof(NWName));
  NWName[NWName[0]+1] = '\0';
  LongString s;
//  s = s + "INSERT INTO LOCKTABLE (XTableId,PrimKey,NWAddress) VALUES (0,'" + Name + "','" + LPSTR (NWName + 1) + "')" ;
  s = s + "INSERT INTO LOCKTABLE (XTableId,PrimKey,NWAddress) VALUES (0,'IchWillJetztInserten','" + LPSTR (NWName + 1) + "')" ;
  RETCODE status = SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
  dbase->TestRetCode (hstmt,status);
  return (status == 0);
  }

void odbcstmt::ClearLock (LPSTR Name)
  {
  LongString s;
//  s = s + "DELETE FROM LOCKTABLE WHERE XTableId = 0 AND PrimKey = '" + Name + "'" ;
  s = s + "DELETE FROM LOCKTABLE WHERE XTableId = 0 AND PrimKey = 'IchWillJetztInserten'" ;
  RETCODE status = SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
  dbase->TestRetCode (hstmt,status);
  }
#endif

static BOOL inTransaction;
void Delay (DWORD ms)
  {
  DWORD t0 = GetTickCount ();
  for ( ; GetTickCount () < t0 + ms ; ) ;
  }

int odbcstmt::StandardInsert (short DatabaseType)
  {
  LPCLKEYDEF k0 = req->TableDef[0]->GetKeyDef(0);
  LPDBRECORD old = res->first->rec[0];
  #ifdef WITHAUTOINCLOCK
  BOOL oldInTransaction;
  BOOL AutoIncLocked = FALSE;
  if ((k0->Attribute & CLKD_AUTOINC) && (old->Get(k0->VarID) == NULL)) {
    oldInTransaction = inTransaction;
    if (!oldInTransaction)
      BeginTransaction (FALSE);
    for ( short i = 0 ; !LockForInsert (req->TableDef[0]->GetName()) ; i++) {
      Delay (200);
      DBWIN_ASSERT_TEXT (i < 1000,"Kann Satz fuer den Insert nicht locken!!");
      }
    AutoIncLocked = TRUE;
    }
  #endif

  LongString s,v;
  ConvertBuffer b;
  s = s + "INSERT INTO " + ODBCGetTableName(req->TableDef[0]) + " (" ;
  v = v + ") VALUES (" ;
  int correct = TRUE ;
  int AnzPars = 0;
  int AnzVars = 0 ;
  BOOL doSetNull;
  if (DatabaseType == DT_MSSQLSERVER)
    doSetNull = FALSE ;
  else
    doSetNull = TRUE ;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
        LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
        correct = EnlargeInsert (vd,i,s,v,&b,&AnzPars,&AnzVars,doSetNull);
        doSetNull = FALSE ;
        }
      }
    }
  else {
    LPTABLEDEF ti = req->TableDef[0] ;
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeInsert (vd,i,s,v,&b,&AnzPars,&AnzVars,doSetNull);
      doSetNull = FALSE ;
      }
    }
  EnlargeInsert_Blocked (s,v,&AnzPars,&AnzVars);
  s = s + LPSTR(v.Ptr()) + ")";

  LongString ss,se;
  if ((k0->Attribute & CLKD_AUTOINC) && (old->Get(k0->VarID) != NULL) &&
        (dbase->DatabaseType == DT_MSSQLSERVER)) {
    ss = ss + "SET IDENTITY_INSERT " + ODBCGetTableName(req->TableDef[0]) + " ON" ;
    SQLExecDirect (hstmt,ss.Ptr(),SQL_NTS);
    }
  RETCODE status = SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);

  while ((status == SQL_NEED_DATA) && (correct)) {
    LPBLOBDESC bd ;
    status = SQLParamData(hstmt, (LPVOID FAR *)(&bd));
    if (status == SQL_NEED_DATA) {
      char huge *Data = (char huge *) GlobalLock (bd->hGmem);
      DWORD actOffs = 0L ;
      DWORD Size ;
      for ( DWORD SizeRemaining = bd->Size ; SizeRemaining > 0 ; ) {
        Size = min(0x4000,SizeRemaining) ;
        RETCODE rStatus = SQLPutData(hstmt, Data + actOffs, Size) ;
        dbase->TestRetCode (hstmt,rStatus);
        SizeRemaining -= Size ;
        actOffs += Size ;
        }
      }
    }

  correct = dbase->TestRetCode (hstmt,status);

  if ((k0->Attribute & CLKD_AUTOINC) && (old->Get(k0->VarID) != NULL) &&
      (dbase->DatabaseType == DT_MSSQLSERVER)) {
    se = se + "SET IDENTITY_INSERT " + ODBCGetTableName(req->TableDef[0]) + " OFF" ;
    SQLExecDirect (hstmt,se.Ptr(),SQL_NTS);
    }

  BOOL recCopyDone = FALSE ;

  // Den eingefuegten Datensatz entfernen
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;

  if (correct) {
    // LPCLKEYDEF k0 = req->TableDef[0]->GetKeyDef(0);

    if ((k0->Attribute & CLKD_AUTOINC) && (old->Get(k0->VarID) == NULL)) {
      LPVARDEF vd = req->TableDef[0]->GetVarDef (k0->VarID);
      LongString m;
      m = m + "SELECT MAX(" + vd->GetName() + ") FROM " + ODBCGetTableName(req->TableDef[0]);
      odbcstmt FAR *selstmt = new odbcstmt();
      selstmt->GetStatementHandle ();
      correct = dbase->TestRetCode (selstmt->hstmt,SQLExecDirect (selstmt->hstmt,m.Ptr(), SQL_NTS));
      if (correct)
        correct = dbase->TestRetCode (selstmt->hstmt,SQLFetch (selstmt->hstmt));
      if (correct) {
        SDWORD Size;
        BOOL doFree ;
        LPVOID data = selstmt->GetColData (vd,1,&Size,&doFree,NULL);

        int va = -1;
        LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
        if (ti == req->TableDef[0])
          va = k0->VarID;
        else {
          for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
            ReqElem e;
            ti->GetReqElem (&e,i);
            if (e.VarID == k0->VarID) {
              va = i ;
              break ;
              }
            }
          }
        res->AddLine (1,ADDLINEPOS_END);
        res->SetRes (0,GetRecCopy (old,va,data,int(Size)));
        GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
        if (doFree)
          FreeGlobMem (data);
        recCopyDone = TRUE ;
        }
      delete selstmt;
      }
    }
  if (!recCopyDone) {
    res->AddLine (1,ADDLINEPOS_END);
    res->SetRes (0,GetRecCopy (old,-1,NULL,0));
    }

  #ifdef WITHAUTOINCLOCK
  if (AutoIncLocked) {
    ClearLock (req->TableDef[0]->GetName());
    if (!oldInTransaction)
      EndTransaction ();
    }
  #endif

  return (correct) ? DBCALL_SUCCESS : DBCALL_NODATA ;
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
BOOL odbcstmt::EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first)
  {
  BOOL correct = TRUE;
  if (BlockedData != NULL) {
    SLONG precision = GetBlockSize (BlockedData);
    SLONG FAR *llen = (SLONG FAR *) (dbase->VarBuffer + *(AnzPars) * sizeof(SLONG)) ;
    *llen = SLONG (precision);
    LPVOID sdata = BlockedData;
    SDWORD len = *llen;
    correct = (dbase->TestRetCode (hstmt,
                  SQLBindParameter (hstmt,*AnzPars + 1,
                  SQL_PARAM_INPUT,
                  SQL_C_BINARY,
                  SQL_LONGVARBINARY,
                  precision,
                  0,
                  sdata,
                  len,
                  llen
                                  )));
    if (correct) {
      if (!first)
        s = s + "," ;
      s = s + dbase->BlockVarName () + " = ?" ;
      first = FALSE ;
      (*AnzPars) ++ ;
      }
    }
  else {
    if (ThereAreBlockedData) {
      if (!first)
        s = s + "," ;
      s = s + dbase->BlockVarName () + " = NULL";
      first = FALSE ;
      correct = TRUE ;
      }
    }
  return correct ;
  }
BOOL odbcstmt::EnlargeUpdate (LPVARDEF vd,int VarID,LongString FAR &s,ConvertBuffer FAR *b,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0)
  {
  if (!IsModifiable(vd,VarID,k0)) return TRUE ;
  LPVOID Data = res->first->rec[0]->Get(VarID);
  BOOL correct ;
  if (Data != NULL) {
    if (vd->VarSize != 0xFFFF) {
      SLONG precision = GetTypePrecision(vd->mType,Data,vd->VarSize);
      SLONG FAR *llen = (SLONG FAR *) (dbase->VarBuffer + *(AnzPars) * sizeof(SLONG)) ;
      *llen = SLONG (precision);
      LPVOID sdata = ConvertTo(vd->mType,Data,b,llen);
      SDWORD len = *llen;
      if (sdata == NULL) *llen = SQL_NULL_DATA ;
      else if (*llen == 0) {
        if (dbase->DatabaseType == DT_MSSQLSERVER)
          *llen = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
        else
          *llen = SQL_LEN_DATA_AT_EXEC(0);
        }
      correct = (dbase->TestRetCode (hstmt,
                    SQLBindParameter (hstmt,*AnzPars + 1,
                    SQL_PARAM_INPUT,
                    GetCType(vd->mType),
                    GetSQLType(vd->mType,precision),
                    precision,
                    0,
                    sdata,
                    len,
                    llen
                                    )));
      if (!first)
        s = s + "," ;
      s = s + dbase->GetAliasName(vd->GetName()) + " = ?";
      first = FALSE ;
      (*AnzPars) ++ ;
      }
    else {
      PushToBlocked (Data,vd->VarID);
      correct = TRUE ;
      ThereAreBlockedData = TRUE ;
      }
    }
  else {
    if (vd->VarSize != 0xFFFF) {
      if (!first)
        s = s + "," ;
      s = s + dbase->GetAliasName(vd->GetName()) + " = NULL";
      first = FALSE ;
      }
    else
      ThereAreBlockedData = TRUE ;
    correct = TRUE ;
    }
  return correct ;
  }
#pragma optimize("", on)

int odbcstmt::StandardUpdate ()
  {
  LongString s,w;
  ConvertBuffer b;
  s = s + "UPDATE " + ODBCGetTableName(req->TableDef[0]) + " SET " ;
  int correct = TRUE ;
  int AnzPars = 0;
  BOOL first = TRUE ;
  LPCLKEYDEF k0 = req->TableDef[0]->GetKeyDef(0);
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
        LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
        correct = EnlargeUpdate (vd,i,s,&b,&AnzPars,first,k0);
        }
      }
    }
  else {
    LPTABLEDEF ti = req->TableDef[0] ;
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeUpdate (vd,i,s,&b,&AnzPars,first,k0);
      }
    }
  correct = EnlargeUpdate_Blocked (s,&AnzPars,first);
  // Where Buffer
  int ParNums[64];
  int wAnzPars = 0;
  LPSTR seq = w.AnalyseSeq (req->SelectionName,ParNums,&wAnzPars,TRUE) ;
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;
  SLONG llen[CB_PARAM * 2];
  for (int i = 0 ; ((i < wAnzPars) && (correct)) ; i++) {
    SLONG precision = GetTypePrecision(req->ParamType[ParNums[i]],req->Param[ParNums[i]]);
    llen[i] = precision ;
    LPVOID sdata = ConvertTo(req->ParamType[ParNums[i]],req->Param[ParNums[i]],&b,llen + i);
    SDWORD len = llen[i];
    if (sdata == NULL) llen[i] = SQL_NULL_DATA ;
      else if (llen[i] == 0) {
        if (dbase->DatabaseType == DT_MSSQLSERVER)
          llen[i] = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
          // llen[i] = SQL_LEN_DATA_AT_EXEC(0);
        else
          llen[i] = SQL_LEN_DATA_AT_EXEC(0);
        }
    correct = (dbase->TestRetCode (hstmt,
                  SQLBindParameter (hstmt,AnzPars + i + 1,
                  SQL_PARAM_INPUT,
                  GetCType(req->ParamType[ParNums[i]]),
                  GetSQLType(req->ParamType[ParNums[i]],precision),
                  precision,
                  0,
                  sdata,
                  len,
                  llen + i
                                  )));
    }

  RETCODE status = SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
 while (status == SQL_NEED_DATA) {
    LPVOID bd ;
  status = SQLParamData(hstmt, &bd);
  if (status == SQL_NEED_DATA) {
      char huge *Data = (char huge *) GlobalLock (LPBLOBDESC(bd)->hGmem);
      DWORD actOffs = 0L ;
      DWORD Size ;
      for ( DWORD SizeRemaining = LPBLOBDESC(bd)->Size ; SizeRemaining > 0 ; ) {
        Size = min(0x4000,SizeRemaining) ;
        RETCODE rStatus = SQLPutData(hstmt, Data + actOffs, Size) ;
        dbase->TestRetCode (hstmt,rStatus);
        SizeRemaining -= Size ;
        actOffs += Size ;
        }
      }
  }
  correct = dbase->TestRetCode (hstmt,status);

  // Die Zeile auf jeden Fall rausnehmen...
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;
  return (correct) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

int odbcstmt::StandardExcute ()
  {
  LongString s;
  int ParNums[64];
  int AnzPars = 0;
  BOOL IdentityInsert;
  char IdentityInsertTable[72];
  LPSTR seq = s.AnalyseSeq (req->SelectionName,ParNums,&AnzPars,FALSE,NULL,req,&IdentityInsert,IdentityInsertTable,this) ;
  BOOL correct = TRUE ;
  ConvertBuffer b;
  SLONG llen[CB_PARAM * 2];
  char nstr = '\0';
  for (int i = 0 ; ((i < AnzPars) && (correct)) ; i++) {
    SLONG precision = GetTypePrecision(req->ParamType[ParNums[i]],req->Param[ParNums[i]]);
    llen[i] = precision ;
    LPVOID sdata = ConvertTo(req->ParamType[ParNums[i]],req->Param[ParNums[i]],&b,llen + i);
    SDWORD len = llen[i];
    if (sdata == NULL) llen[i] = SQL_NULL_DATA ;
    else if (llen[i] == 0) {
      if (dbase->DatabaseType == DT_MSSQLSERVER)
        llen[i] = SQL_LEN_DATA_AT_EXEC((LONG)(LPBLOBDESC(sdata)->Size));
        // llen[i] = SQL_LEN_DATA_AT_EXEC(0);
      else
        llen[i] = SQL_LEN_DATA_AT_EXEC(0);
      }

    int ctype = GetCType(req->ParamType[ParNums[i]]);
    int sqltype = GetSQLType(req->ParamType[ParNums[i]],precision);

    correct = (dbase->TestRetCode (hstmt,
                  SQLBindParameter (hstmt,i + 1,
                  SQL_PARAM_INPUT,
                  ctype,
                  sqltype,
                  precision,
                  0,
                  sdata,
                  len,
                  llen + i
                                  )));
    }
  
  if ((correct) && (TopDsc != NULL)) {
    correct = dbase->TestRetCode (hstmt,SQLPrepare (hstmt,s.Ptr(),SQL_NTS));
    if (correct)
      correct = BindColData (NULL);
    }
  
  LongString ss,se;
  if (IdentityInsert && (dbase->DatabaseType == DT_MSSQLSERVER)) {
    ss = ss + "SET IDENTITY_INSERT " + IdentityInsertTable + " ON" ;
    SQLExecDirect (hstmt,ss.Ptr(),SQL_NTS);
    }

  RETCODE status;
  if (correct) {
    if ((correct) && (TopDsc != NULL)) {
      UDWORD AnzRows;
      UWORD RowStatus;
      correct = (dbase->TestRetCode (hstmt,SQLExecute (hstmt)));
      status = SQLExtendedFetch (hstmt,SQL_FETCH_NEXT,0,&AnzRows,&RowStatus);
      }
    else
      status = SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);

    correct = dbase->TestRetCode (hstmt,status);
    }

  if (IdentityInsert && (dbase->DatabaseType == DT_MSSQLSERVER)) {
    se = se + "SET IDENTITY_INSERT " + IdentityInsertTable + " OFF" ;
    SQLExecDirect (hstmt,se.Ptr(),SQL_NTS);
    }

  // Ev. Parameter abholen
  StoreBndParam (correct);
  return (correct) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

static char outString [2048];
LPSTR CallTypeName (WORD Type)
  {
  switch (Type) {
    case DBCALLTYPE_EXTENDED         : return "EXTENDED" ;
    case DBCALLTYPE_STANDARDGET      : return "STANDARDGET" ;
    case DBCALLTYPE_GETLIST          : return "GETLIST" ;
    case DBCALLTYPE_STANDARDUPDATE   : return "STANDARDUPDATE" ;
    case DBCALLTYPE_STANDARDDELETE   : return "STANDARDDELETE" ;
    case DBCALLTYPE_STANDARDINSERT   : return "STANDARDINSERT" ;
    case DBCALLTYPE_EXECUTE          : return "EXECUTE" ;
    case DBCALLTYPE_EXECUTESINGLE    : return "EXECUTESINGLE" ;
    case DBCALLTYPE_TEST             : return "TEST" ;
    }
  return "unknown" ;
  }
static char ParStr[256];
LPSTR GetParStr (LPSTR r,LPVOID data,WORD mType)
  {
  if (data == NULL)
    lstrcpy (r,"NULL,");
  else if (mType == VAR_STR)
    wsprintf (r,"%.30s,",data);
  else if (mType == VAR_OBJ)
    lstrcpy (r,"BINARY,");
  else {
    FormatOutTxt (r,data,mType);
    lstrcat (r,",");
    }
  return r + lstrlen(r);
  }
void GetParStrs (LPDBREQUEST req)
  {
  *ParStr = '<' ;
  LPSTR h = GetParStr (ParStr + 1,req->Param[2],req->ParamType[2]);
  h = GetParStr (h,req->Param[3],req->ParamType[3]);
  h = GetParStr (h,req->Param[4],req->ParamType[4]);
  lstrcpy (h,"...>");
  }
DLLExport int _export WINAPI DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  DWORD startT;
  switch (Op) {
    case DBOP_ENDOFCONVERSION :
      return DBCALL_SUCCESS;
    case DBOP_RESET :
      // Statement wieder freigeben
      if (*hstmt != NULL) {
        LPODBCSTMT stmt = LPODBCSTMT (*hstmt);
        delete stmt;
        *hstmt = NULL ;
        }
      return DBCALL_SUCCESS;
    case DBOP_STARTOFUPDATE :
      return DBCALL_SUCCESS;
    case DBOP_ENDOFUPDATE :
      return DBCALL_SUCCESS;
    default :
      LPODBCSTMT stmt = LPODBCSTMT (*hstmt);
      // Laufende Initialisierungen
      BOOL first ;
      if (stmt == NULL) {
        stmt               = new odbcstmt();
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
      BOOL istNoCheckFile = FALSE;
      if ((req->Type == DBCALLTYPE_TEST) || (req->Type == DBCALLTYPE_CREATE)) {
        if (req->Type == DBCALLTYPE_CREATE)
          InCreate = TRUE ;

        if (first) {
          for (int i = 0 ; i < int(stmt->req->AnzTables) ; i++) {
            if (stmt->req->TableDef[i] != NULL) {
              static char TCheck[32];
              if ((stmt->req->TableDef[i])->GetTableProperty ("ODBC_Check",TCheck,sizeof(TCheck)) > 0) {
                if (lstrcmp(TCheck,"no") == 0) {
                  istNoCheckFile = TRUE;
                  }
                }
              }
            }
          }

        if (!istNoCheckFile) {
          CheckFile (NULL,FALSE) ;
          dbase->StartTableTest ();
          }
        }
      BOOL cf ;
      if (istNoCheckFile) {
        cf = TRUE;
        }
      else {
        cf = CheckFile (stmt,first);
        }
      if ((req->Type == DBCALLTYPE_TEST) || (req->Type == DBCALLTYPE_CREATE)) {
        return (cf) ? DBCALL_SUCCESS : DBCALL_NODATA ;
        }

      if (stmt->hstmt == NULL)
        stmt->GetStatementHandle ();
      if (!req->foreignDone)
        req->BuildForeign ();   // Und noch die Fremdzugriffe ...
 
   BOOL startDone = FALSE ;
      if (DoLog ()) {
        if (req->GetTableID()) {
          LPTABLEDEF td = GetTableAdmin()->GetTableDef(req->GetTableID(),req->GetVersion());
          if (req->SelectionName != NULL)
            wsprintf (outString,"<%s ON %s> \"%.2048s\"",CallTypeName (req->Type),td->GetName(),req->SelectionName,startT = GetTickCount());
          else
            wsprintf (outString,"<FURTHER ON %s>",ODBCGetTableName(td),startT = GetTickCount());
          GetTableAdmin()->FreeTable(req->GetTableID(),req->GetVersion());
          startDone = TRUE ;
          }
        else {
          if ((req->SelectionName != NULL) && (Op == DBOP_GETFIRST)) {
            wsprintf (outString,"<%s> \"%.2048s\" (%ld - ",CallTypeName (req->Type),req->SelectionName,startT = GetTickCount());
            startDone = TRUE ;
            }
          }
        }

      switch (req->Type) {
        case DBCALLTYPE_STANDARDDELETE :
          stmt->retVal = stmt->StandardDelete ();
          stmt->ClearStmt ();
          break ;
        case DBCALLTYPE_STANDARDGET :
          stmt->retVal = stmt->StandardGet ();
          stmt->GetOldStatementCopy ();
          break ;
        case DBCALLTYPE_GETLIST :
          stmt->retVal = stmt->StandardList (first,dbase->DatabaseType);
          stmt->GetOldStatementCopy ();
          break ;
        case DBCALLTYPE_STANDARDINSERT :
          stmt->retVal = stmt->StandardInsert (dbase->DatabaseType);
          stmt->ClearStmt ();
          break ;
        case DBCALLTYPE_STANDARDUPDATE :
          stmt->retVal = stmt->StandardUpdate ();
          stmt->ClearStmt ();
          break ;
        case DBCALLTYPE_EXECUTE :
        case DBCALLTYPE_EXECUTESINGLE :
          if (Op == DBOP_GETFIRST) {
            stmt->retVal = stmt->StandardExcute ();
            stmt->ClearStmt ();
            }
          break ;
        }

      if (startDone) {
        DWORD endt = GetTickCount () ;
        if ((timeForLog == 0) || (endt - startT >= timeForLog)) {
          char timestr[32];
          wsprintf (timestr,"[%ld - %ld (= %ld)]",startT,endt,endt - startT);
          GetParStrs (req);
  
          LogCmd ("",timestr,outString,ParStr);
          }
        }
      return stmt->retVal;
      break ;
    }

  return DBCALL_SUCCESS ;
  }

DLLExport void _export WINAPI DoBeginTransaction (BOOL doLarge)
  {
  if (DoLog() && (timeForLog == 0))
    LogCmd ("\rBEGINTRANSACTION\r----------------",NULL,NULL,NULL);
  if (dbase == NULL)
    // Login to database
    dbase = new database (ServerName(),UserName(),PassWord());
#ifdef UEBERLEGT
  static BOOL Initialized;
  if (!Initialized)
    dbase->TestRetCode (SQL_NULL_HSTMT,SQLSetConnectOption(dbase->hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF));
  Initialized = TRUE ;
#endif
  dbase->TestRetCode (SQL_NULL_HSTMT,SQLSetConnectOption(dbase->hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF));
  inTransaction = TRUE ;
  }

DLLExport void _export WINAPI DoEndTransaction ()
  {
  if (DoLog() && (timeForLog == 0))
    LogCmd ("\rENDTRANSACTION\r--------------",NULL,NULL,NULL);
  dbase->TestRetCode (SQL_NULL_HSTMT,SQLTransact(dbase->henv,dbase->hdbc,SQL_COMMIT));
  dbase->TestRetCode (SQL_NULL_HSTMT,SQLSetConnectOption(dbase->hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON));
  inTransaction = FALSE ;
  }

DLLExport void _export WINAPI DoAbortTransaction ()
  {
  if (DoLog() && (timeForLog == 0))
    LogCmd ("\rABORTTRANSACTION\r----------------",NULL,NULL,NULL);
  dbase->TestRetCode (SQL_NULL_HSTMT,SQLTransact(dbase->henv,dbase->hdbc,SQL_ROLLBACK));
  dbase->TestRetCode (SQL_NULL_HSTMT,SQLSetConnectOption(dbase->hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON));
  inTransaction = FALSE ;
  }

struct FAR DBPoiterData {
  HDBC hdbc ;
  HENV henv ;
  };
DLLExport LPVOID _export WINAPI GetDBPointer ()
  {
  DBPoiterData FAR *res = (DBPoiterData FAR *) GetGlobMem (sizeof(*res));
  res->henv = dbase->henv;
  res->hdbc = dbase->hdbc;
  return res ;
  }

static DWORD LastEndT;
DLLExport void _export WINAPI MakeTimeStamp (LPSTR Msg)
  {
  DWORD endt = GetTickCount () ;
  if (DoLog()) {
    if ((timeForLog == 0) || (endt - LastEndT >= timeForLog)) {
      char timestr[32];
      wsprintf (timestr,"[%ld - %ld (= %ld)]",LastEndT,endt,endt - LastEndT);
  
      LogCmd ("",timestr,Msg,"");
      }
    }
  LastEndT = endt;
  }

/******************************************************************************

Erweitertes benutzerdefinierbares Errorhandling

******************************************************************************/

void PushErrToIgnore (int errType)
  {
  errToIgnore FAR *h = (errToIgnore FAR *) GetGlobMem (sizeof(*h));
  h->Next = eri ;
  eri = h ;
  h->errType = errType ;
  if (errType == ERRTYPE_ALLERRORS) {
    errToWith_All = TRUE ;
    }
  else if (errType == ERRTYPE_USERDEFINED) {
    errToWith_UserDefined = TRUE ;
    }
  } //PushErrToIgnore

void PopErrToIgnore (int errType)
  {
  errToIgnore FAR *prev = NULL ;
  for (errToIgnore FAR *h = eri ; h != NULL ; h = h->Next) {
    if (h->errType == errType) {
      if (prev != NULL) prev->Next = h->Next ;
      else              eri = h->Next ;
      FreeGlobMem (h);
      if (errType == ERRTYPE_ALLERRORS) {
        errToWith_All = FALSE ;
        }
      else if (errType == ERRTYPE_USERDEFINED) {
        errToWith_UserDefined = FALSE ;
        }
      break ;
      }
    else
      prev = h;
    }
  } //PopErrToIgnore

void FreeErrToIgnore ()
  {
  for ( ; eri != NULL ; ) {
    errToIgnore FAR *h = eri->Next;
    FreeGlobMem (eri);
    eri = h;
    }
  errToWith_All = FALSE ;
  errToWith_UserDefined = FALSE ;
  } //FreeErrToIgnore

BOOL IsTypeToIgnore (int errType)
  {
  lastIgnoredErrorType = 0;
  for (errToIgnore FAR *h = eri ; h != NULL ; h = h->Next) {
    if (h->errType == errType) {
      return TRUE ;
      }
    }
  return FALSE ;
  } //IsTypeToIgnore

BOOL IgnoreODBCError(int errType,BOOL State)
  //Liefert TRUE, wenn der Fehler schon ignoriert wurde
  {
  BOOL res;
  if (State) {
    if (!(res = IsTypeToIgnore (errType))) {
      PushErrToIgnore (errType);
      }
    }
  else {
    PopErrToIgnore (errType);
    res = FALSE ;
    }
  return res;
  } //IgnoreODBCError

DLLExport BOOL _export WINAPI DBIgnoreError (int ErrType,BOOL State)
  {
  return IgnoreODBCError (ErrType,State);
  } //DBIgnoreError

DLLExport int _export WINAPI GetDBLastError ()
  {
  return lastIgnoredErrorType;
  } //GetDBLastError

DLLExport LPSTR _export WINAPI GetDBLastErrorText ()
  {
  return lastIgnoredErrMsg;
  } //GetDBLastErrorText

DLLExport void _export WINAPI SetDBLogState (BOOL logState, LPSTR logFile)
  {
  ovrDoLog = logState;
  if (ovrLogFile != NULL) {
    FreeGlobMem (ovrLogFile);
    ovrLogFile = NULL;
    }
  if (logFile != NULL) {
    ovrLogFile = LPSTR (GetGlobMem (1 + lstrlen(logFile) + 12)); //12 = lstrlen("odbccmds.log")
    ovrLogFile[0] = 0;
    lstrcat(ovrLogFile,"odbccmds");
    lstrcat(ovrLogFile,logFile);
    lstrcat(ovrLogFile,".log");
    }
  }


