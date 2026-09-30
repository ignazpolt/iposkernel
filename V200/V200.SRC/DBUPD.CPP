//------------------------------------------------------------------------
// Funktionen zum Update des Programmes
// $Header:   P:/marille/clinicum/rev/dbupd.cpv   1.28   20 Aug 1999 20:17:14   Martin  $
// $Log:   P:/marille/clinicum/rev/dbupd.cpv  $
// 
//    Rev 1.28   20 Aug 1999 20:17:14   Martin
// CreateAllTables
// 
//    Rev 1.27   09 Jul 1998 15:10:42   Hannes
// Returnwert bei SystemUpdate
// 
//    Rev 1.26   02 Feb 1998 20:33:58   Hannes
// VersionFrom, VersionTo mitprotokollieren
// 
//    Rev 1.25   09 Jan 1998 10:34:04   Hannes
// 
//    Rev 1.24   09 Dec 1997 16:22:56   Hannes
// 
//    Rev 1.23   01 Dec 1997 19:38:14   Hannes
// Diverse Anpassungen
// 
//    Rev 1.22   06 Nov 1997 19:25:58   Hannes
// diverse Fehlerkorrekturen
// 
//    Rev 1.21   24 Oct 1997 08:37:32   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.20   05 Aug 1997 22:41:38   Hannes
// Verbesserter Update - Check
// 
//    Rev 1.19   18 Jul 1997 08:07:24   Hannes
// 
//    Rev 1.18   18 Mar 1997 18:04:52   Hannes
// Set Versions vor Updatescripts
// 
//    Rev 1.17   05 Mar 1997 10:55:36   Hannes
// 
//    Rev 1.16   28 Feb 1997 17:04:38   Hannes
// 
//    Rev 1.15   28 Feb 1997 16:24:00   Hannes
// 
//    Rev 1.14   27 Feb 1997 14:41:34   Hannes
// 
//    Rev 1.13   21 Jan 1997 14:46:40   HANNES
// 
//    Rev 1.12   20 Jan 1997 17:18:02   HANNES
// Fehlerkorrektur in GetMaxVersion
// 
//    Rev 1.11   17 Jan 1997 10:38:20   HANNES
// Updatescripts wieder aufraeumen (ehm...)
// 
//    Rev 1.10   10 Jan 1997 12:37:12   HANNES
// 
//    Rev 1.9   08 Jan 1997 17:53:18   HANNES
// GetMaxVersion () besser abgefragt
// 
//    Rev 1.8   17 Dec 1996 11:12:26   HANNES
// EndOfUpdate
// 
//    Rev 1.7   12 Dec 1996 12:17:54   HANNES
// Schreiben eines Updatelogs unterstuetzt, CreateTable
// 
//    Rev 1.6   04 Dec 1996 14:37:18   HANNES
// 
//    Rev 1.5   04 Dec 1996 14:25:08   HANNES
// 
//    Rev 1.4   04 Dec 1996 10:46:46   HANNES
// doStop
// 
//    Rev 1.3   04 Dec 1996 10:01:40   HANNES
// Automatischer Create hinten anhaengen
// 
//    Rev 1.2   27 Nov 1996 13:29:24   HANNES
// 
//    Rev 1.1   26 Nov 1996 19:05:50   HANNES
// Weitere Fehlerkorrekturen
// 
//    Rev 1.0   26 Nov 1996 08:15:18   HANNES
// Initial revision.
//------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "cont.hpp"
#define MODULENUM 171
#include "winass.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"

static BOOL UpdateError;
BOOL MarkUpdateError (mdiChild *c,LPVOID param,WORD mode)
  {
  UpdateError = TRUE ;

  return FALSE ;
  }

#pragma pack(1)
struct SystemUpdate_param {
  WORD parSize;
  DWORD msgStr;
  DWORD startStep;
  DWORD endStep;
  DWORD count;
  DWORD midStep;
  };
#pragma pack()
static DBList FAR *VersionList;
static mdiChild FAR *_updc;
static SystemUpdate_param FAR *_updpar;
DLLExport void _export WINAPI AltSuccess (DWORD s)
  {
  _updc->WritelData (_updpar->count,&s,sizeof(s),LPSTR(_updpar)-sizeof(WORD));
  _updc->ExCuteProc (_updpar->midStep,EM_LOAD | EM_CHANGETOTRUE);
  _updc->ExCuteProc (_updpar->midStep,EM_RESET | EM_CLEAR);
  }
static __ALTERSUCCESS GetAltSuccess ()
  {
  static __ALTERSUCCESS alts ;
  if (alts == NULL)
    alts = __ALTERSUCCESS (MakeProcInstance (FARPROC(AltSuccess),WBase::hInstance));
  return alts ;
  }
WORD SearchVersion (LPSTR Name)
  {
  for ( LPDBRECORD h = VersionList->GetFirst() ; h != NULL ; h = VersionList->GetNext(h) ) {
    if (lstrcmp (Name,LPSTR(h->Get(1))) == 0) return *(WORD FAR *) h->Get(2);
    }
  return FIRSTVERSION ;
  }
void ModifyVersionList (LPSTR Name,WORD Version)
  {
  DWORD rNummer = 1;
  for ( LPDBRECORD h = VersionList->GetFirst() ; h != NULL ; h = VersionList->GetNext(h) ) {
    if (lstrcmp (Name,LPSTR(h->Get(1))) == 0) {
      h->Set(2,&Version,sizeof(Version));
      return ;
      }
    LPDWORD lpNummer = LPDWORD(h->Get(0));
    if (*lpNummer >= rNummer) rNummer = *lpNummer + 1;
    }
  LPDBRECORD n = new DBRecord (VersionList->GetTableDef());
  n->Set(0,&rNummer,sizeof(rNummer));
  n->Set(1,Name,lstrlen(Name) + 1);
  n->Set(2,&Version,sizeof(Version));
  PrimKey k;
  n->CalcPrimKey(0,&k);
  n->SetPrimKey(&k);
  VersionList->AddRecAtHead (n,VersionList->GetRequest());
  VersionList->MarkHeadAsEnd ();
  }

#define MAX_BUFFERSIZE  1024
WORD GetMaxVersion (LPSTR Name,WORD minVersion,WORD destVersion,LPSTR fName = NULL)
  {
  WORD res = destVersion;
  for ( LPSCRIPTCONTENT sc = GetFirstUpdateScript (); 
              sc != NULL ; sc = GetNextUpdateScript (sc)) {
    if ((fName != NULL) && (lstrcmp (fName,sc->fName) == 0)) continue ;
    char buffer[MAX_BUFFERSIZE];
    BOOL IsDone = TRUE ;
    if (sc->GetProperty ("ToVersion",buffer,sizeof(buffer))) {
      //
      // Ueberpruefen, ob das schon erledigt wurde
      //
      for (LPSTR h = buffer ; (*h) ; ) {
        for ( LPSTR x = h ; ((*x) && (*x != ' ')) ; x++) ;
        BOOL doMore;
        if (*x == ' ') doMore = TRUE ;
        else           doMore = FALSE ;
        *x = '\0' ;
        WORD mustHave = GetVersionFrom(h);
        WORD actVersion = SearchVersion (h);
        if (actVersion < mustHave) {
          IsDone = FALSE ;
          break ;
          }
        else {
          if (doMore) h = ++ x ;
          else        h = x ;
          }
        }
      }
    if ((!IsDone) && (sc->GetProperty ("FromVersion",buffer,sizeof(buffer)))) {
      for (LPSTR h = buffer ; (*h) ; ) {
        for ( LPSTR x = h ; ((*x) && (*x != ' ')) ; x++) ;
        BOOL doMore;
        if (*x == ' ') doMore = TRUE ;
        else           doMore = FALSE ;
        *x = '\0' ;
        WORD mustHave     = GetVersionFrom(h);
        if (lstrcmp (h,Name) == 0) {
          if ((mustHave >= minVersion) && (mustHave < res))
            res = mustHave ;
          }
        if (doMore) h = ++ x;
        else        break ;
        }
      }
    }
  return res;
  }

BOOL IsInProperty (LPSTR Name,LPSTR buffer,WORD mustHave)
  {
  for (LPSTR h = buffer ; (*h) ; ) {
    for ( LPSTR x = h ; ((*x) && (*x != ' ')) ; x++) ;
    BOOL doMore;
    if (*x == ' ') doMore = TRUE ;
    else           doMore = FALSE ;
    *x = '\0' ;
    WORD willHave = GetVersionFrom(h);
    if (lstrcmp (h,Name) == 0) {
      return (willHave > mustHave) ;
      }
    if (doMore) h = ++ x;
    else        break ;
    }
  return FALSE ;
  }

void MyTestTable (LPSTR TableName)
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
  WIN_ASSERT (found);
  LPTABLEDEF t = GetTableAdmin()->GetTableDef (TableID,Version);
  LPDBREQUEST req = InitializeRequest ("",1,DBCALLTYPE_CREATE,NULL);
  req->AddTableDef (t);
  LPVOID hstmt = NULL;
  int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,-1,req,&hstmt,NULL);
  GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,-1,req,&hstmt,NULL);
  FreeRequest (req);
  }
void TestDBVersionTable ()
  {
  MyTestTable ("DBVersion");
  }
void TestUpdateStepTable ()
  {
  MyTestTable ("UpdateStep");
  }

DLLExport void _export WINAPI SetActVersionFor (LPSTR Name,WORD Version);
DLLExport void _export WINAPI DelActVersionList ();
BOOL SystemUpdate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    StartSystemUpdate();
    // Zuerst die DBVersion testen, ev. Existiert sie noch nicht !!!!
    //---------------------------------------------------------------
    TestDBVersionTable ();
    TestUpdateStepTable ();

    // Der DLL Mitteilen, dass jetzt der Update beginnt
    GetDLLAdmin()->GetDLLEntry(GetTransactionDLL())->DBCall (DBOP_STARTOFUPDATE,-1,NULL,NULL,NULL);

    SystemUpdate_param FAR *par = (SystemUpdate_param FAR *) param;
    _updc = c ;
    _updpar = par ;
    WIN_ASSERT(VersionList == NULL);
    VersionList = GetDBVersionList();
    BOOL doStop = FALSE ;
    for ( BOOL sdone = TRUE ; ((sdone) && (!doStop)) ; ) {
      // 1. Alle Tabellendefinitionen durchgehen und Aendern, was notwendig 
      //      ist (sofern es erlaubt ist)
      //-----------------------------------------------------------------
      LPDDCONT d = GetTableAdmin()->GetDDContent();
      for ( LPCONTENTRY e = d->First() ; ((e != NULL) && (!doStop)) ; e = d->Next(e) ) {
        if (e->tRef.TableNr < GLOBALTBIDMIN) {
          WORD VersionFrom = SearchVersion(e->TableName);
          char ftxt[256];
          wsprintf (ftxt,"Version zu Neu: %s (sollte sein: %d, ist: %d)",LPSTR(e->TableName),e->tRef.Version,VersionFrom);
          WIN_ASSERT_TEXT (VersionFrom <= e->tRef.Version,ftxt);
          WORD VersionTo = GetMaxVersion (e->TableName,VersionFrom,e->tRef.Version);
          if (VersionFrom < VersionTo) {
            char message[256];
            wsprintf (message,"ALTER (%d->%d) %s",int(VersionFrom),int(VersionTo),e->TableName);
            c->WritelData (par->msgStr,message,lstrlen(message) + 1,LPSTR(param)-sizeof(WORD));
            c->ExCuteProc (par->startStep,EM_LOAD | EM_CHANGETOTRUE);
            c->ExCuteProc (par->startStep,EM_RESET | EM_CLEAR);

            LPTABLEDEF tdold = GetTableAdmin()->GetTableDef(e->tRef.TableNr,VersionFrom);
            LPTABLEDEF tdnew = GetTableAdmin()->GetTableDef(e->tRef.TableNr,VersionTo);
            WIN_ASSERT ((tdold != NULL) && (tdnew != NULL));

            int dbres = GetDLLAdmin()->GetDLLEntry(tdnew->GetDLLHandle())->DBAlter (tdold,tdnew,GetAltSuccess ());

            if (tdold != NULL) GetTableAdmin()->FreeTable(e->tRef.TableNr,VersionFrom);
            if (tdnew != NULL) GetTableAdmin()->FreeTable(e->tRef.TableNr,VersionTo);

            if (dbres == 0) {
              SetDBVersion (e->TableName,VersionTo);
              ModifyVersionList (e->TableName,VersionTo);
              wsprintf (message,"OK");
              EndTransaction();
              }
            else {
              wsprintf (message,"ERROR ON ALTER %s, Update stopped",e->TableName);
              doStop = TRUE ;
              AbortTransaction();
              }
            c->WritelData (par->msgStr,message,lstrlen(message) + 1,LPSTR(param)-sizeof(WORD));
            c->ExCuteProc (par->endStep,EM_LOAD | EM_CHANGETOTRUE);
            c->ExCuteProc (par->endStep,EM_RESET | EM_CLEAR);
            }
          }
        }

      // 2. Testen aller Updatescripts, ob Sie ausgefuehrt werden koennen
      //-----------------------------------------------------------------
      sdone = FALSE ;
      for ( ; (!doStop) ; ) {
        BOOL somethingdone = FALSE ;
        for ( LPSCRIPTCONTENT sc = GetFirstUpdateScript (); 
                    ((sc != NULL) && (!doStop)) ; sc = GetNextUpdateScript (sc)) {
          char buffer[MAX_BUFFERSIZE],buffer1[MAX_BUFFERSIZE];
          if (sc->GetProperty ("FromVersion",buffer,sizeof(buffer))) {
            BOOL doIt = TRUE ;
            for (LPSTR h = buffer ; (*h) && (doIt) ; ) {
              for ( LPSTR x = h ; ((*x) && (*x != ' ')) ; x++) ;
              BOOL doMore;
              if (*x == ' ') doMore = TRUE ;
              else           doMore = FALSE ;
              *x = '\0' ;
              WORD mustHave     = GetVersionFrom(h);
              WORD dbActVersion = SearchVersion(h);
              sc->GetProperty ("ToVersion",buffer1,sizeof(buffer1));
              if ((IsInProperty (h,buffer1,mustHave)) && (GetMaxVersion (h,mustHave,mustHave + 1,sc->fName) != mustHave + 1))
                doIt = FALSE;
              else
                doIt = (mustHave == dbActVersion);

              if (doMore) h = ++ x;
              else        break ;
              }

            if (doIt) {
              if (sc->GetProperty ("FromVersion",buffer,sizeof(buffer))) {
                for (LPSTR h = buffer ; (*h) && (doIt) ; ) {
                  for ( LPSTR x = h ; ((*x) && (*x != ' ')) ; x++) ;
                  BOOL doMore;
                  if (*x == ' ') doMore = TRUE ;
                  else           doMore = FALSE ;
                  *x = '\0' ;
                  WORD mustHave     = GetVersionFrom(h);
                  SetActVersionFor (h,mustHave);
                  if (doMore) h = ++ x ;
                  else        break ;
                  }
                }
              char message[256];
              wsprintf (message,"EXECUTING %s",sc->Name);
              c->WritelData (par->msgStr,message,lstrlen(message) + 1,LPSTR(param)-sizeof(WORD));
              c->ExCuteProc (par->startStep,EM_LOAD | EM_CHANGETOTRUE);
              c->ExCuteProc (par->startStep,EM_RESET | EM_CLEAR);

              mdiChild *u = new Form(sc);
              u->GetOutData()->_scale = float (1.0);
#ifdef DEBUG
              PushToCallStack (u,u->schd->fName,u->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
              u->LoadData ();
              delete u ;
#ifdef DEBUG
              PopFromCallStack ();
#endif
              DelActVersionList ();
              if (!UpdateError)
                wsprintf (message,"OK");
              else {
                wsprintf (message,"ERROR ON EXCUTE %s, Update stopped",sc->Name);
                doStop = TRUE ;
                }

              somethingdone = TRUE ;
              sdone = TRUE ;

              c->WritelData (par->msgStr,message,lstrlen(message) + 1,LPSTR(param)-sizeof(WORD));
              c->ExCuteProc (par->endStep,EM_LOAD | EM_CHANGETOTRUE);
              c->ExCuteProc (par->endStep,EM_RESET | EM_CLEAR);
              }
            }
          else
            WIN_ASSERT (FALSE);
          }
        if (!somethingdone) break ;
        }
      }
    delete VersionList;
    VersionList = NULL;

    if (!doStop) {
      // Automatischer CREATE hinten anhaengen
      DBTest (TRUE);
      GetDLLAdmin()->GetDLLEntry(GetTransactionDLL())->DBCall (DBOP_ENDOFUPDATE,-1,NULL,NULL,NULL);
      }
    return !doStop;
    }

  return FALSE ;
  }

#pragma pack(1)
struct FAR AlterTable_param {
  WORD parSize;
  DWORD OldTable;
  DWORD NewTable;
  struct {
    DWORD VarName;
    DWORD DefaultValue;
    } xd[1];
  int AnzDefs()
    {
    return (parSize - (sizeof(*this) - sizeof(xd[0]))) / sizeof(xd[0]) ;
    }
  };
#pragma pack()
BOOL AlterTable (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & EM_LOAD) {
    AlterTable_param FAR *par = (AlterTable_param FAR *) param;
    LPSTR lpt1 = LPSTR (c->ReadlData (par->OldTable));
    LPSTR lpt2 = LPSTR (c->ReadlData (par->NewTable));
    char t1[64],t2[64];
    lstrcpy (t1,lpt1);
    lstrcpy (t2,lpt2);
    WORD v1 = GetVersionFrom (t1);
    WORD v2 = GetVersionFrom (t2);
    DBWIN_ASSERT ((v1 != 0xFFFF) && (v2 != 0xFFFF) && (lstrcmp (t1,t2) == 0)) ;
    DefVal FAR *dv;
    if (par->AnzDefs() > 0) {
      dv = (DefVal FAR *) GetGlobMem (par->AnzDefs() * sizeof(*dv));
      for (int i = 0 ; i < par->AnzDefs() ; i++) {
        dv[i].VarName = LPSTR(c->ReadlData (par->xd[i].VarName));
        dv[i].DefaultValue = c->ReadlData (par->xd[i].DefaultValue);
        dv[i].mType = c->GetDataType (par->xd[i].DefaultValue);
        }
      }
    else
      dv = NULL;

    WORD Version;
    BOOL found;
    WORD TableID = GetTableAdmin()->GetTableID(NULL,t1,&found,&Version);
    WIN_ASSERT (found);

    LPTABLEDEF tdold = GetTableAdmin()->GetTableDef(TableID,v1);
    LPTABLEDEF tdnew = GetTableAdmin()->GetTableDef(TableID,v2);

    WIN_ASSERT ((tdold != NULL) && (tdnew != NULL));
    int dbres = GetDLLAdmin()->GetDLLEntry(tdnew->GetDLLHandle())->DBAlter (tdold,tdnew,GetAltSuccess (),par->AnzDefs(),dv);

    if (tdold != NULL) GetTableAdmin()->FreeTable(TableID,v1);
    if (tdnew != NULL) GetTableAdmin()->FreeTable(TableID,v2);

    if (dbres == 0) {
      SetDBVersion (t2,v2);
      ModifyVersionList (t2,v2);
      SetActVersionFor (t2,v2);
      }

    if (dv != NULL)
      FreeGlobMem (dv);
    res = (dbres == 0) ;
    if (!res)
      UpdateError = TRUE ;
    }
  return res ;
  }

#pragma pack(1)
struct FAR CreateTable_param {
  WORD parSize;
  DWORD TableName;
  };
#pragma pack()

BOOL CreateTable (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateTable_param FAR *par = (CreateTable_param FAR *) param;
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    WIN_ASSERT (TableName != NULL);
    MyTestTable (TableName);
    }
  return FALSE ;
  }

BOOL CloseAllFiles (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL oldBlockIsActive = BlockIsActive ;
  BlockIsActive = FALSE ;
  LPDBREQUEST req = InitializeRequest ("",1,DBCALLTYPE_CLOSEALL,NULL);
  LPVOID hstmt = NULL;
  int res = GetDLLAdmin()->GetDLLEntry(GetDLLAdmin()->LoadDefaultDLL())->DBCall (DBOP_GET,-1,req,&hstmt,NULL);
  FreeRequest (req);
  BlockIsActive = oldBlockIsActive ;
  return FALSE ;
  }

BOOL CreateAllTables (mdiChild *c,LPVOID param,WORD mode)
  {
  DBTest(TRUE);
  return FALSE ;
  }

