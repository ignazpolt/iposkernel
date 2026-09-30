////////////////////////////////////////////////////////////
//  Verwaltung der Datenbank - DLL's
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/dlladmin.cpv   1.23   03 Dec 1999 02:38:46   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/dlladmin.cpv  $
// 
//    Rev 1.23   03 Dec 1999 02:38:46   Hannes
// ErrorText
// 
//    Rev 1.22   16 Jul 1999 18:36:32   Martin
// (C)ontinue bei "geschachtelte Transaktion" erlaubt
// 
//    Rev 1.21   16 Jul 1999 18:32:52   Martin
// WIN_ASSERTs gegen geschachtelte Transaktionsaufrufe
// 
//    Rev 1.20   05 Oct 1998 11:09:34   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.19   06 Mar 1998 17:27:58   Hannes
// Prototyp Transaktionshandling
// 
//    Rev 1.18   31 Oct 1997 15:19:26   Hannes
// 
//    Rev 1.17   18 Jul 1997 08:07:26   Hannes
// 
//    Rev 1.16   30 Apr 1997 08:43:42   Hannes
// Fehlerkorrektur in FreeLibrary
// 
//    Rev 1.15   26 Nov 1996 07:53:46   HANNES
// Automatischer Update
// 
//    Rev 1.14   05 Apr 1996 15:05:42   MARTIN
// Abgleich Schweiz
//
// 21.03.96 FL FreeLibrary in a normal way
// 
//    Rev 1.13   16 Feb 1996 15:12:20   GERHOLD
// hDLLInst != NULL   ->  hDLLInst == NULL !!!
// 
//    Rev 1.12   02 Feb 1996 10:45:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   31 Jan 1996 18:17:04   HANNES
// 
//    Rev 1.9   02 Jan 1996 22:16:58   HANNES
// Echtes dynamisches Linken
// 
//    Rev 1.8   26 Apr 1995 15:32:54   HANNES
// 
//    Rev 1.7   24 Feb 1995 11:12:40   HANNES
//  
// 
//    Rev 1.6   16 Feb 1995 12:48:46   HANNES
//  
// 
//    Rev 1.5   29 Jan 1995 11:46:04   HANNES
// 
//    Rev 1.4   09 Jan 1995 12:09:30   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   07 Nov 1994 11:43:44   HANNES
// DBBTRV direkt angebunden
// 
//    Rev 1.2   31 Oct 1994 10:39:44   hannes
// Transaktionen weiterleiten
// 
//    Rev 1.1   17 Jul 1994 14:33:48   HANNES
// IsViewAllowed fuer Interne Tabellen
// 
//    Rev 1.0   24 Jun 1994 16:44:48   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   19 Apr 1994 10:47:52   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 76
#include "winass.hpp"

extern HINSTANCE hLibInst;

#define DYNAMIC_BIND

extern void MyDLLName (LPSTR res,LPSTR symbname);
extern LPSTR FAR PASCAL GetIniName();

#ifndef DYNAMIC_BIND
extern "C" {
  int FAR PASCAL DATARES_GETDICTCONT (void);
  int FAR PASCAL DATARES_GETDOCCONT (void);
  int FAR PASCAL DATARES_GETDOCDEF (void);
  int FAR PASCAL DATARES_GETFIRSTDOC (void);
  int FAR PASCAL DATARES_GETFIRSTROWDEF (void);
  int FAR PASCAL DATARES_GETFIRSTTABLEDEF (void);
  int FAR PASCAL DATARES_GETNEXTDOC (void);
  int FAR PASCAL DATARES_GETNEXTROWDEF (void);
  int FAR PASCAL DATARES_GETNEXTTABLEDEF (void);
  int FAR PASCAL DATARES_GETRESOURCE (void);
  int FAR PASCAL DATARES_SETDICTCONT (void);
  int FAR PASCAL DATARES_SETDOCCONT (void);
  int FAR PASCAL DATARES_SETDOCDEF (void);
  int FAR PASCAL DATARES_SETRESOURCE (void);
  int FAR PASCAL DATARES_SETROWDEF (void);
  int FAR PASCAL DATARES_SETTABLEDEF (void);
  int FAR PASCAL DATARES_GETFULLTABLEDEF (void);
  int FAR PASCAL DATARES_SETFULLTABLEDEF (void);
  int FAR PASCAL DBRESET (void);
  int FAR PASCAL DATADICT_TABLEDEF (void);
  int FAR PASCAL DATADICT_FREETABLEDEF (void);
  int FAR PASCAL DATARES_GETTABLEDEF (void);
  int FAR PASCAL DBCALL (void);
  int FAR PASCAL DATADICT_FREEVARDEF (void);
  int FAR PASCAL DATADICT_VARDEF (void);
  int FAR PASCAL DATADICT_GETMTYPE (void);
  int FAR PASCAL DATADICT_GETACCESSLIST (void);
  int FAR PASCAL DATADICT_GETVARDESCEXTRA (void);
  int FAR PASCAL DATADICT_ISFOREIGNKEY (void);
  int FAR PASCAL DATARES_CLEARROWDEFS (void);
  int FAR PASCAL DATADICT_ISPRIMARY (void);
  int FAR PASCAL DATARES_GETFIRSTRESOURCE (void);
  int FAR PASCAL DATARES_GETNEXTRESOURCE (void);
  int FAR PASCAL DATARES_GETRESCONT (void);
  int FAR PASCAL DATARES_SETRESCONT (void);
  int FAR PASCAL DATARES_SETFUNCDEF (void);
  int FAR PASCAL DATARES_GETFUNCDEF (void);
  int FAR PASCAL DATADICT_ISACCESSFORVIEW (void);
  int FAR PASCAL DATADICT_GETSQLPART (void);
  int FAR PASCAL DOBEGINTRANSACTION (void);
  int FAR PASCAL DOENDTRANSACTION (void);
  int FAR PASCAL DOABORTTRANSACTION (void);
  int FAR PASCAL DATADICT_GETVARPROPERTY (void);
  int FAR PASCAL DATARES_GETSERVERSOURCE (void);
  int FAR PASCAL DATADICT_LASTSERVERSOURCE (void);
  int FAR PASCAL DATARES_SETSERVERSOURCE (void);
  int FAR PASCAL DATADICT_NEWTABLEDEF (void);
  int FAR PASCAL DATARES_DELTABLEDEF (void);

  int FAR PASCAL ODBCDBCALL (void);
  int FAR PASCAL ODBCDBRESET (void);
  int FAR PASCAL ODBCDATADICT_NEWTABLEDEF (void);
  int FAR PASCAL ODBCDOBEGINTRANSACTION (void);
  int FAR PASCAL ODBCDOENDTRANSACTION (void);
  int FAR PASCAL ODBCDOABORTTRANSACTION (void);

  int FAR PASCAL GETUNIQUEADDRESS (void);
  int FAR PASCAL NETSETSTATIONSEMAPHOR (void);
  int FAR PASCAL NETCLEARSTATIONSEMAPHOR (void); 
  int FAR PASCAL NETCHECKSTATIONSEMAPHOR (void);
  int FAR PASCAL NETSETSEMA (void);
  int FAR PASCAL NETCLEARSEMA (void);
  int FAR PASCAL NETTESTSEMA (void);
  int FAR PASCAL NETGETCONNECTIONNMBR (void);
  int FAR PASCAL NETSEMAPHOREAVAILABLE (void);
  }

void LoadProcArray (FARPROC FAR *DLLProc,LPSTR DLLName,LPSTR FName)
  {
  OFSTRUCT Of;
  HFILE fi = OpenFile (DLLName,&Of,OF_EXIST);
  if (fi >= 0)
    lstrcpy (FName,DLLName);
  else
    MyDLLName (FName,DLLName);

  AnsiUpper (FName);
  if (lstrcmp (FName,"DBBTRV.DLL") == 0) {
    DLLProc [_DATARES_GETDICTCONT]       = DATARES_GETDICTCONT;
    DLLProc [_DATARES_GETDOCCONT]        = DATARES_GETDOCCONT;
    DLLProc [_DATARES_GETDOCDEF]         = DATARES_GETDOCDEF;
    DLLProc [_DATARES_GETFIRSTDOC]       = DATARES_GETFIRSTDOC;
    DLLProc [_DATARES_GETFIRSTROWDEF]    = DATARES_GETFIRSTROWDEF;
    DLLProc [_DATARES_GETFIRSTTABLEDEF]  = DATARES_GETFIRSTTABLEDEF;
    DLLProc [_DATARES_GETNEXTDOC]        = DATARES_GETNEXTDOC;
    DLLProc [_DATARES_GETNEXTROWDEF]     = DATARES_GETNEXTROWDEF;
    DLLProc [_DATARES_GETNEXTTABLEDEF]   = DATARES_GETNEXTTABLEDEF;
    DLLProc [_DATARES_GETRESOURCE]       = DATARES_GETRESOURCE;
    DLLProc [_DATARES_SETDICTCONT]       = DATARES_SETDICTCONT;
    DLLProc [_DATARES_SETDOCCONT]        = DATARES_SETDOCCONT;
    DLLProc [_DATARES_SETDOCDEF]         = DATARES_SETDOCDEF;
    DLLProc [_DATARES_SETRESOURCE]       = DATARES_SETRESOURCE;
    DLLProc [_DATARES_SETROWDEF]         = DATARES_SETROWDEF;
    DLLProc [_DATARES_SETTABLEDEF]       = DATARES_SETTABLEDEF;
    DLLProc [_DATARES_GETFULLTABLEDEF]   = DATARES_GETFULLTABLEDEF;
    DLLProc [_DATARES_SETFULLTABLEDEF]   = DATARES_SETFULLTABLEDEF;
    DLLProc [_DBRESET]                   = DBRESET;
    DLLProc [_DATADICT_TABLEDEF]         = DATADICT_TABLEDEF;
    DLLProc [_DATADICT_FREETABLEDEF]     = DATADICT_FREETABLEDEF;
    DLLProc [_DATARES_GETTABLEDEF]       = DATARES_GETTABLEDEF;
    DLLProc [_DBCALL]                    = DBCALL;
    DLLProc [_DATADICT_FREEVARDEF]       = DATADICT_FREEVARDEF;
    DLLProc [_DATADICT_VARDEF]           = DATADICT_VARDEF;
    DLLProc [_DATADICT_GETMTYPE]         = DATADICT_GETMTYPE;
    DLLProc [_DATADICT_GETACCESSLIST]    = DATADICT_GETACCESSLIST;
    DLLProc [_DATADICT_GETVARDESCEXTRA]  = DATADICT_GETVARDESCEXTRA;
    DLLProc [_DATADICT_ISFOREIGNKEY]     = DATADICT_ISFOREIGNKEY;
    DLLProc [_DATARES_CLEARROWDEFS]      = DATARES_CLEARROWDEFS;
    DLLProc [_DATADICT_ISPRIMARY]        = DATADICT_ISPRIMARY;
    DLLProc [_DATARES_GETFIRSTRESOURCE]  = DATARES_GETFIRSTRESOURCE;
    DLLProc [_DATARES_GETNEXTRESOURCE]   = DATARES_GETNEXTRESOURCE;
    DLLProc [_DATARES_GETRESCONT]        = DATARES_GETRESCONT;
    DLLProc [_DATARES_SETRESCONT]        = DATARES_SETRESCONT;
    DLLProc [_DATARES_SETFUNCDEF]        = DATARES_SETFUNCDEF;
    DLLProc [_DATARES_GETFUNCDEF]        = DATARES_GETFUNCDEF;
    DLLProc [_DATADICT_ISACCESSFORVIEW]  = DATADICT_ISACCESSFORVIEW;
    DLLProc [_DATADICT_GETSQLPART]       = DATADICT_GETSQLPART;
    DLLProc [_DOBEGINTRANSACTION]        = DOBEGINTRANSACTION;
    DLLProc [_DOENDTRANSACTION]          = DOENDTRANSACTION;
    DLLProc [_DOABORTTRANSACTION]        = DOABORTTRANSACTION;
    DLLProc [_DATADICT_GETVARPROPERTY]   = DATADICT_GETVARPROPERTY;
    DLLProc [_DATARES_GETSERVERSOURCE]   = DATARES_GETSERVERSOURCE ;
    DLLProc [_DATADICT_LASTSERVERSOURCE] = DATADICT_LASTSERVERSOURCE ;
    DLLProc [_DATARES_SETSERVERSOURCE]   = DATARES_SETSERVERSOURCE ;
    DLLProc [_DATADICT_NEWTABLEDEF]      = DATADICT_NEWTABLEDEF ;
    DLLProc [_DATARES_DELTABLEDEF]       = DATARES_DELTABLEDEF ;
    }
  else if ( (strncmp (FName,"DNET", 4) == 0) ) {
    DLLProc [_NET_GETUNIQUEADDRESS]      = GETUNIQUEADDRESS;
    DLLProc [_NET_SETSTATIONSEMAPHOR]    = NETSETSTATIONSEMAPHOR;
    DLLProc [_NET_CLEARSTATIONSEMAPHOR]  = NETCLEARSTATIONSEMAPHOR;
    DLLProc [_NET_CHECKSTATIONSEMAPHOR]  = NETCHECKSTATIONSEMAPHOR;
    DLLProc [_NET_SETSEMA]               = NETSETSEMA;
    DLLProc [_NET_CLEARSEMA]             = NETCLEARSEMA;
    DLLProc [_NET_TESTSEMA]              = NETTESTSEMA;
    DLLProc [_NET_GETCONNECTIONNMBR]     = NETGETCONNECTIONNMBR;
    DLLProc [_NET_SEMAPHOREAVAILABLE]    = NETSEMAPHOREAVAILABLE;

  	} // if
  else {
    DLLProc [_DBRESET]                   = ODBCDBRESET;
    DLLProc [_DBCALL]                    = ODBCDBCALL;
    DLLProc [_DATADICT_NEWTABLEDEF]      = ODBCDATADICT_NEWTABLEDEF ;
    DLLProc [_DOBEGINTRANSACTION]        = ODBCDOBEGINTRANSACTION;
    DLLProc [_DOENDTRANSACTION]          = ODBCDOENDTRANSACTION;
    DLLProc [_DOABORTTRANSACTION]        = ODBCDOABORTTRANSACTION;
    }
  }
#endif

/*--------------------------------------------------------------*/
/*  Implementierung der Klasse Basisklasse DLLEntry             */
/*--------------------------------------------------------------*/
DLLEntry::DLLEntry (LPSTR DLLName,BOOL doTest)
  {
  lstrcpy (_name,DLLName);

  if (lstrcmp (_name,GetInternDLLName()) != 0) {
#ifdef DYNAMIC_BIND
    OFSTRUCT Of;
    HFILE fi = OpenFile (DLLName,&Of,OF_EXIST);
    if (fi >= 0)
      lstrcpy (_Fname,DLLName);
    else
      MyDLLName (_Fname,_name);
    hDLLInst = LoadLibrary (_Fname);

#ifdef WIN32
    if (hDLLInst == NULL) {
#else
    if (hDLLInst <= 32) {
#endif

      char outtxt[128];
      wsprintf (outtxt,"cannot load lib: %s",DLLName);
      WIN_ASSERT_TEXT (FALSE,outtxt);
      }
    for (int i = 0 ; i < MAXDLLPROC ; i++) {
      char procname[64];
      LoadString (hLibInst,1000 + i,procname,sizeof(procname));
      DLLProc [i] = GetProcAddress (hDLLInst,procname);
      if (doTest) {
        char flagstring[16];
        LoadString (hLibInst,2000 + i,flagstring,sizeof(flagstring));
        if ((*flagstring == 'y') && (DLLProc[i] == NULL)) {
          char outtxt[128];
          wsprintf (outtxt,"Funktion %s not found in %s",LPSTR(procname),LPSTR(DLLName));
          WIN_ASSERT_TEXT (FALSE,outtxt);
          }
        }
      }                  
#else
    LoadProcArray (DLLProc,DLLName,_Fname);
#endif
    }
  else {
    hDLLInst = 0;
    lstrcpy (_Fname,DLLName);
    // Nur die Zeiger eintragen, ohne eine DLL zu laden !!!
    /////////////////////////////////////////////////////////
    DLLProc [_DATADICT_TABLEDEF]        = FARPROC (Intern_DATADICT_TABLEDEF);
    DLLProc [_DATADICT_FREETABLEDEF]    = FARPROC (Intern_DATADICT_FREETABLEDEF);
    DLLProc [_DATADICT_VARDEF]          = FARPROC (Intern_DATADICT_VARDEF);
    DLLProc [_DATADICT_FREEVARDEF]      = FARPROC (Intern_DATADICT_FREEVARDEF);
    DLLProc [_DATADICT_GETMTYPE]        = FARPROC (Intern_DATADICT_GETMTYPE);
    DLLProc [_DATADICT_GETACCESSLIST]   = FARPROC (Intern_DATADICT_GETACCESSLIST);
    DLLProc [_DBRESET]                  = FARPROC (Intern_DBRESET);
    DLLProc [_DBCALL]                   = FARPROC (Intern_DBCALL);
    DLLProc [_DATADICT_GETVARDESCEXTRA] = FARPROC (Intern_GETVARDESCEXTRA);
    DLLProc [_DATADICT_ISPRIMARY]       = FARPROC (Intern_ISPRIMARY);
    DLLProc [_DATADICT_ISACCESSFORVIEW] = FARPROC (Intern_DATADICT_ISACCESSFORVIEW);
    DLLProc [_DATADICT_GETVARPROPERTY]  = FARPROC (Intern_DATADICT_GETVARPROPERTY);
    }
  doUpdate = TRUE ;                  
  }

DLLEntry::~DLLEntry ()
  {
  DBReset ();
  // >>> FL 21.3.96 : This frees all Libraries in a normal way
  if (hDLLInst)
    FreeLibrary(hDLLInst);
  }

/*------------------------------------------------------------*/
/*  Klasse DLLAmin                                            */
/*------------------------------------------------------------*/
static DLLAdmin _dllAdmin;

DLLExport LPDLLADMIN _export FAR PASCAL GetDLLAdmin()
  {
  return &_dllAdmin;
  }

DLLHANDLE DLLAdmin::GetFreeEntry()
  {
  for (DLLHANDLE i = 0 ; i < MAXDLLS ; i++)
    if (dll[i] == NULL) return i ;
  WIN_ASSERT_TEXT (FALSE,"Max Count of DLL's reached");
  return 0;
  }

DLLHANDLE DLLAdmin::GetDLLNmbr(LPSTR DLLName)
  {
  for (DLLHANDLE i = 0 ; i < MAXDLLS ; i++) {
    if ((dll[i] != NULL) && (lstrcmp (dll[i]->GetDLLName(),DLLName) == 0))
      return i ;
    }
  return -1 ;
  }

DLLExport DLLHANDLE _export FAR PASCAL DLLAdmin::LoadResDLL ()
  {
  char path[128];
  GetPrivateProfileString ("DataBase","ResourceDLL","MV1",
                            path,sizeof(path),
                            GetIniName()
                          );
  DLLHANDLE res = GetDLLNmbr(path);
  if (res < 0) {
    res = GetFreeEntry();
    dll[res] = new DLLEntry (path,FALSE);
    }
  return res;
  }

DLLExport DLLHANDLE _export FAR PASCAL DLLAdmin::LoadDLL (LPSTR DLLName)
  {
  DLLHANDLE res = GetDLLNmbr(DLLName);
  if (res < 0) {
    res = GetFreeEntry();
    dll[res] = new DLLEntry (DLLName,FALSE);
    }
  return res;
  }

DLLExport void _export FAR PASCAL DLLAdmin::ResetDLLAdmin()
  {
  for (DLLHANDLE i = 0 ; i < MAXDLLS ; i++) {
    if (dll[i] != NULL) {
      delete dll[i] ;
      dll[i] = NULL ;
      }
    }
  }

DLLExport DLLHANDLE _export FAR PASCAL GetTransactionDLL ()
  {
  static DLLHANDLE TransActionDLL;
  static BOOL TransActionDLLDone;
  if (!TransActionDLLDone) {
    char Name[128];
    GetPrivateProfileString ("DataBase","DefaultDLL","MV1",
                            Name,sizeof(Name),
                            GetIniName()
                          );
    TransActionDLL = GetDLLAdmin()->LoadDLL (Name);
    TransActionDLLDone = TRUE ;
    }
  return TransActionDLL;
  }

DLLExport DLLHANDLE _export FAR PASCAL DLLAdmin::LoadDefaultDLL ()
  {
  return GetTransactionDLL();
  }

DLLExport void _export FAR PASCAL SetDBLogState (BOOL logState, LPSTR logFile)
  {
  DLLHANDLE th = GetTransactionDLL();
  (GetDLLAdmin()->GetDLLEntry (th))->DoSetDBLogState(logState,logFile);
  }

static BOOL IAmInTransaction = FALSE;
DLLExport void _export FAR PASCAL BeginTransaction (BOOL doLarge)
  {
  if (IAmInTransaction) {
    IAmInTransaction = FALSE;  // damit man (C)ontinue druecken darf
    WIN_ASSERT_TEXT(FALSE,"geschachtelte Transaktion !");
    IAmInTransaction = TRUE;
    }
  DLLHANDLE th = GetTransactionDLL();
  IAmInTransaction = TRUE;
  (GetDLLAdmin()->GetDLLEntry (th))->DoBeginTransaction(doLarge);
  }
DLLExport void _export FAR PASCAL EndTransaction ()
  {
  WIN_ASSERT_TEXT(IAmInTransaction,"EndTransaction ohne BeginTransaction !");
  DLLHANDLE th = GetTransactionDLL();
  (GetDLLAdmin()->GetDLLEntry (th))->DoEndTransaction();
  IAmInTransaction = FALSE;
  }
DLLExport void _export FAR PASCAL AbortTransaction ()
  {
  WIN_ASSERT_TEXT(IAmInTransaction,"AbortTransaction ohne BeginTransaction !");
  DLLHANDLE th = GetTransactionDLL();
  (GetDLLAdmin()->GetDLLEntry (th))->DoAbortTransaction();
  IAmInTransaction = FALSE;
  }
DLLExport void _export FAR PASCAL TimeStamp (LPSTR Msg)
  {
  DLLHANDLE th = GetTransactionDLL();
  (GetDLLAdmin()->GetDLLEntry (th))->MakeTimeStamp(Msg);
  }
DLLExport BOOL _export FAR PASCAL InTransaction ()
  {
  return IAmInTransaction;
  }
DLLExport LPSTR _export FAR PASCAL LastErrorText ()
  {
  DLLHANDLE th = GetTransactionDLL();
  return (GetDLLAdmin()->GetDLLEntry (th))->DBGetLastErrorText();
  }
DLLExport void _export FAR PASCAL ResetTransactionDLL ()
  {
  DLLHANDLE th = GetTransactionDLL();
  (GetDLLAdmin()->GetDLLEntry (th))->DBReset();
  }

static DWORD LastDBAction[MAXDLLS];
DLLExport void _export FAR PASCAL MarkDBAction (DLLEntry FAR *h)
  {
  for (short i = 0 ; i < MAXDLLS ; i++) {
    if (h == GetDLLAdmin()->GetDLLEntry (i)) {
      LastDBAction[i] = GetTickCount ();
      }
    }
  }

DLLExport DWORD _export FAR PASCAL GetLastDBAction (DLLHANDLE dllh)
  {
  return LastDBAction [dllh] ;
  }


