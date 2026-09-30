/////////////////////////////////////////////////////////////////
//  Innere Listen (meist schon retired)
/////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/list1.cpv   1.10   02 Feb 1999 13:10:22   Hannes  $
//  $Log:   P:/marille/clinicum/rev/list1.cpv  $
// 
//    Rev 1.10   02 Feb 1999 13:10:22   Hannes
// EmptyInnerList: ClearConnection
// 
//    Rev 1.9   26 Nov 1998 08:21:38   Hannes
// SetLineObjects ohne Objekte
// 
//    Rev 1.8   27 Jul 1998 15:15:42   Hannes
// lSetUpCallBack
// 
//    Rev 1.7   31 Jan 1998 22:24:58   Martin
// list.hpp, einige Funktionen aus list.cpp verlagert
// 
//    Rev 1.6   05 Jan 1998 07:53:50   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.5   10 Jul 1997 08:58:02   Hannes
// 
//    Rev 1.4   09 Jun 1997 13:11:16   Hannes
// 
//    Rev 1.3   12 Dec 1996 12:17:32   HANNES
// AddRecAtTail
// 
//    Rev 1.2   26 Nov 1996 08:14:30   HANNES
// Automatischer Update
// 
//    Rev 1.1   10 Jun 1996 10:08:46   GERHOLD
// pragma packinterpr.cpp
// 
//    Rev 1.0   06 May 1996 12:57:56   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#ifdef WIN32
#include <wingdi.h>
#else
#include <print.h>
#endif

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
#include "dllchild.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "ddslist.hpp"

#include "winextra.hpp"
#define MODULENUM 100
#include "winass.hpp"

#include "oneshot.hpp"
#include "multipro.hpp"
#include "ddsmsg.h"

#include "list.hpp"

#define LIST_MAIN
#include "for.hpp"
#include "tbcbd.hpp"

//////////////////////////////////////////////////////////////////////////
//  Verwaltung von Listen, die im Speicher erzeugt werden
//////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR CreateInnerList_param {
  WORD parSize;
  LPINNERLISTDESC res;
  DWORD lPtr;
  DWORD TableName;

  LPTABLEDEF GetTableDef(mdiChild *c,WORD FAR *TableId);
  WORD GetTableInd(mdiChild *c,WORD TableInd);
  };
#pragma pack()

LPTABLEDEF CreateInnerList_param::GetTableDef (mdiChild *c,WORD FAR *TableId)
  {
  LPSTR Name = LPSTR(c->ReadlData (TableName));
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(c->schd->TRef[i].TableNr,c->schd->TRef[i].Version);
    if (lstrcmp(Name,td->GetName()) == 0) {
      *TableId = td->GetTableID();
      return td;
      }
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }
WORD CreateInnerList_param::GetTableInd (mdiChild *c,WORD TableId)
  {
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    if (c->schd->TRef[i].TableNr == TableId) return (i + CSYSRECS);
    }
  return 0xFFFF;
  }
BOOL CreateInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateInnerList_param FAR *par = (CreateInnerList_param FAR *) param;
    LPINNERLISTDESC d = LPINNERLISTDESC(GetGlobMem (sizeof(*d)));
    d->td = par->GetTableDef (c,&d->TableId);
    d->list = new RecordList (d->td,c->DocumentID(),0,TRUE);
    c->WritelData (par->lPtr,&d,sizeof(d),LPSTR(param)-sizeof(WORD));
    par->res = d;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreateInnerList_param FAR *par = (CreateInnerList_param FAR *) param;
    par->res->list->ThrowList ();
    delete par->res->list;
    GetTableAdmin()->FreeTable(par->res->td->GetTableID(),par->res->td->GetVersion());
    c->DellData (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
LPTABLEDEF CheckInnerList (LPVOID obj,RecordList FAR *FAR *lst)
  {
  if (GetBlockSize (obj) == sizeof(InnerListDesc)) {
    *lst = LPINNERLISTDESC (obj)->list ;
    return LPINNERLISTDESC (obj)->td ;
    }
  else
    return NULL ;
  }

#pragma pack(1)
struct FAR AddRecToInnerList_param {
  WORD parSize;
  DWORD lPtr;
  DWORD procPtr;
  DWORD kval[1];

  int AnzKVal()
    { return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(kval[0]); }
  WORD GetTableInd (mdiChild *c,WORD TableId);
  };
#pragma pack()

WORD AddRecToInnerList_param::GetTableInd (mdiChild *c,WORD TableId)
  {
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    if (c->schd->TRef[i].TableNr == TableId) return (i + CSYSRECS);
    }
  return 0xFFFF;
  }
BOOL AddRecToInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddRecToInnerList_param FAR *par = (AddRecToInnerList_param FAR *) param;
    LPINNERLISTDESC FAR *d = (LPINNERLISTDESC FAR *) (c->ReadlData (par->lPtr));
    DBWIN_ASSERT ((d != NULL) && (*d != NULL) && ((*d)->list != NULL));
    LPDBRECORD n;
    PrimKey k ;
    BOOL alldone = TRUE ;
    for (int i = 0 ; ((i < par->AnzKVal()) && (alldone)) ; i++) {
      LPVOID data = c->ReadlData (par->kval[i]);
      if (data != NULL)
        k.PushKeySeg (data,GetBlockSize(data));
      else
        alldone = FALSE ;
      }
    if (alldone) {
      LPDBRECORD rec = (*d)->list->FindRec (&k);
      if (rec == NULL) {
        n = new DBRecord((*d)->td);
        n->setLocked ();
        n->SetPrimKey (&k);
      
        WORD TableInd = par->GetTableInd (c,(*d)->TableId);
        LPDBRECORD old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,n);
        RestoreListFnc rlf(c);
        c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (par->procPtr,EM_RESET);
        c->rr->SetRecord (TableInd,old);

        (*d)->list->AddRecAtTail (n,NULL,TRUE);

        if ((*d)->lo != NULL) {
//          (*d)->lo->MyList->RefreshList (REFRESHMODE_START);
          }
        }
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CallOverInnerList_param {
  WORD parSize;
  DWORD lPtr;
  DWORD procPtr;

  WORD GetTableInd (mdiChild *c,WORD TableId);
  };
#pragma pack()

WORD CallOverInnerList_param::GetTableInd (mdiChild *c,WORD TableId)
  {
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    if (c->schd->TRef[i].TableNr == TableId) return (i + CSYSRECS);
    }
  return 0xFFFF;
  }
#define MAX_ARDEPTH 10
static LPDBRECORD ActiveRecord[MAX_ARDEPTH];
static BOOL IsToDel[MAX_ARDEPTH];
static int ARPtr;
void PushToARList (LPDBRECORD r)
  {
  IsToDel[ARPtr] = FALSE ;
  ActiveRecord[ARPtr++] = r;
  }
BOOL PopFromARList ()
  {
  return IsToDel[--ARPtr];
  }
BOOL IsDelAllowed (LPDBRECORD rec)
  {
  BOOL found = FALSE ;
  for (int i = 0 ; i < ARPtr ; i++) {
    if (ActiveRecord[i] == rec) {
      IsToDel[i] = TRUE ;
      found = TRUE ;
      }
    }
  return !found ;
  }


BOOL CallOverInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CallOverInnerList_param FAR *par = (CallOverInnerList_param FAR *) param;
    LPINNERLISTDESC FAR *d = (LPINNERLISTDESC FAR *) (c->ReadlData (par->lPtr));
    DBWIN_ASSERT ((d != NULL) && (*d != NULL) && ((*d)->list != NULL));
    WORD TableInd = par->GetTableInd (c,(*d)->TableId);
    LPDBRECORD old = c->rr->GetRecord(TableInd);

    RestoreListFnc rlf(c);
    for (LPDBRECORD h = (*d)->list->GetFirst() ; h != NULL ; ) {
      LPDBRECORD Next = (*d)->list->GetNext(h);
      c->rr->SetRecord (TableInd,h);
      PushToARList (h);
      c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procPtr,EM_RESET);
      if (PopFromARList()) {
        // Es ist ein RemoveRecFromInnerlist mit diesem
        // Datensatz aufgetaucht !!!
        if ((*d)->lo != NULL) {
//          (*d)->lo->MyList->RemoveElem (h->GetPrimKey()->Data);
          }
        (*d)->list->ThrowRecord (h);
        }
      h = Next;
      }
    c->rr->SetRecord (TableInd,old);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR LoadInnerList_param {
  WORD parSize;
  LPINNERLISTDESC d;
  MultiProc FAR *mp;    // 8 Byte private Daten
  DWORD res;            // Der Zeiger des Parameterblockes
                        // wird in die Datenbank geschrieben
  DWORD lPtr;
  DWORD procPtr;

  WORD GetTableInd (mdiChild *c,WORD TableId);
  };
#pragma pack()
typedef LoadInnerList_param FAR *LPILPAR;

WORD LoadInnerList_param::GetTableInd (mdiChild *c,WORD TableId)
  {
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    if (c->schd->TRef[i].TableNr == TableId) return (i + CSYSRECS);
    }
  return 0xFFFF;
  }
BOOL LoadInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LoadInnerList_param FAR *par = (LoadInnerList_param FAR *) param;
    LPINNERLISTDESC FAR *d = (LPINNERLISTDESC FAR *) (c->ReadlData (par->lPtr));
    DBWIN_ASSERT ((d != NULL) && (*d != NULL) && ((*d)->list != NULL));
    WORD TableInd = par->GetTableInd (c,(*d)->TableId);
    LPDBRECORD old = c->rr->GetRecord(TableInd);

    par->mp = new MultiProc (c,par->procPtr);
    for (LPDBRECORD r = (*d)->list->GetFirst () ; r != NULL ; r = (*d)->list->GetNext (r) ) {
      par->mp->AddProc (r->GetPrimKey());
      c->rr->SetRecord (TableInd,r);
      SetExtraInfo s(c,TableInd,r,par->mp->CorrOffs());
      WORD mymode = EM_LOAD | EM_CHANGETOTRUE ;
      if (mode & EM_FIXCONNECTION)
        mymode |= EM_FIXCONNECTION ;
      par->mp->ExCute (r->GetPrimKey(),mymode,&s);
      }
    c->rr->SetRecord (TableInd,old);
    par->d = *d;
    c->WritelData (par->res,&par,sizeof(par),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_RESET) {
    LoadInnerList_param FAR *par = (LoadInnerList_param FAR *) param;
    LPINNERLISTDESC d = par->d ;
    DBWIN_ASSERT ((d != NULL) && (d->list != NULL));
    WORD TableInd = par->GetTableInd (c,d->TableId);
    LPDBRECORD old = c->rr->GetRecord(TableInd);

    for (LPDBRECORD r = d->list->GetFirst () ; r != NULL ; r = d->list->GetNext (r) ) {
      c->rr->SetRecord (TableInd,r);
      SetExtraInfo s(c,TableInd,r,par->mp->CorrOffs());
      WORD mymode = EM_RESET | EM_CLEAR ;
      par->mp->ExCute (r->GetPrimKey(),mymode,&s);
      par->mp->Remove (r->GetPrimKey());
      }

    c->rr->SetRecord (TableInd,old);
    delete par->mp ;
    par->d = NULL;
    par->mp = NULL;
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR ActivateInInnerList_param {
  WORD parSize;
  DWORD LoadPtr;
  DWORD kval[1];
  int AnzKVal()
    { return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(kval[0]); }
  };
#pragma pack()

BOOL InnerListActivation (mdiChild FAR *c,LPVOID param,WORD mode,WORD mymode)
  {
  if (mode & EM_LOAD) {
    ActivateInInnerList_param FAR *par = (ActivateInInnerList_param FAR *) param;
    LPILPAR FAR *p = (LPILPAR FAR *) c->ReadlData (par->LoadPtr);
    DBWIN_ASSERT ((p != NULL) && (*p != NULL) && ((*p)->mp != NULL));
    PrimKey k ;
    BOOL alldone = TRUE ;
    for (int i = 0 ; ((i < par->AnzKVal()) && (alldone)) ; i++) {
      LPVOID data = c->ReadlData (par->kval[i]);
      if (data != NULL)
        k.PushKeySeg (data,GetBlockSize(data));
      else
        alldone = FALSE ;
      }
    if (alldone) {
      LPDBRECORD rec = (*p)->d->list->FindRec (&k);
      if (rec != NULL) {
        WORD TableInd = (*p)->GetTableInd (c,(*p)->d->TableId);
        LPDBRECORD old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        SetExtraInfo s(c,TableInd,rec,(*p)->mp->CorrOffs());
        if (mymode & EM_LOAD) {
          (*p)->mp->AddProc (rec->GetPrimKey());
          (*p)->mp->ExCute (rec->GetPrimKey(),mymode,&s);
          }
        else {
          (*p)->mp->ExCute (&k,mymode,&s);
          (*p)->mp->Remove (&k);
          }
        c->rr->SetRecord (TableInd,old);
        }
      }
    }
  return FALSE ;
  }

BOOL ActivateInInnerList (mdiChild FAR *c,LPVOID param,WORD mode)
  {
  return InnerListActivation (c,param,mode,EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION);
  }

BOOL DeActivateInInnerList (mdiChild FAR *c,LPVOID param,WORD mode)
  {
  return InnerListActivation (c,param,mode,EM_RESET | EM_CLEAR);
  }

#pragma pack(1)
struct FAR RemoveRecFromInnerList_param {
  WORD parSize;
  DWORD lPtr;
  DWORD kval[1];

  int AnzKVal()
    { return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(kval[0]); }
  };
#pragma pack()

BOOL RemoveRecFromInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RemoveRecFromInnerList_param FAR *par = (RemoveRecFromInnerList_param FAR *) param;
    LPINNERLISTDESC FAR *d = (LPINNERLISTDESC FAR *) (c->ReadlData (par->lPtr));
    DBWIN_ASSERT ((d != NULL) && (*d != NULL) && ((*d)->list != NULL));
    PrimKey k ;
    BOOL alldone = TRUE ;
    for (int i = 0 ; ((i < par->AnzKVal()) && (alldone)) ; i++) {
      LPVOID data = c->ReadlData (par->kval[i]);
      if (data != NULL)
        k.PushKeySeg (data,GetBlockSize(data));
      else
        alldone = FALSE ;
      }
    if (alldone) {
      LPDBRECORD rec = (*d)->list->FindRec (&k);
      if (IsDelAllowed (rec)) {
        if ((*d)->lo != NULL) {
//          (*d)->lo->MyList->RemoveElem (k.Data);
          }
        if (rec != NULL)
          (*d)->list->ThrowRecord (rec);
        }
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CallInInnerListFor_param {
  WORD parSize;
  DWORD lPtr;
  DWORD procPtr;
  DWORD kval[1];

  int AnzKVal()
    { return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(kval[0]); }
  WORD GetTableInd (mdiChild *c,WORD TableId);
  };
#pragma pack()

WORD CallInInnerListFor_param::GetTableInd (mdiChild *c,WORD TableId)
  {
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    if (c->schd->TRef[i].TableNr == TableId) return (i + CSYSRECS);
    }
  return 0xFFFF;
  }

BOOL CallInInnerListFor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CallInInnerListFor_param FAR *par = (CallInInnerListFor_param FAR *) param;
    LPINNERLISTDESC FAR *d = (LPINNERLISTDESC FAR *) (c->ReadlData (par->lPtr));
    DBWIN_ASSERT ((d != NULL) && (*d != NULL) && ((*d)->list != NULL));
    PrimKey k ;
    WORD TableInd = par->GetTableInd (c,(*d)->TableId);
    BOOL alldone = TRUE ;
    for (int i = 0 ; ((i < par->AnzKVal()) && (alldone)) ; i++) {
      LPVOID data = c->ReadlData (par->kval[i]);
      if (data != NULL)
        k.PushKeySeg (data,GetBlockSize(data));
      else
        alldone = FALSE ;
      }
    if (alldone) {
      LPDBRECORD rec = (*d)->list->FindRec (&k);
      RestoreListFnc rlf(c);
      if (rec != NULL) {
        LPDBRECORD old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (par->procPtr,EM_RESET);
        c->rr->SetRecord (TableInd,old);
        }
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetLineCount_param {
  WORD parSize;
  DWORD res;
  DWORD lPtr;
  };
#pragma pack()
extern RecordList FAR * GetListFromForParam_noset (LPVOID obj);
BOOL GetLineCount (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetLineCount_param FAR *par = (GetLineCount_param FAR *) param;
    RecordList FAR *list = NULL;
    LPVOID FAR *lpo = (LPVOID FAR *) (c->ReadlData (par->lPtr));
    if ((lpo != NULL) && (*lpo != NULL)) {
      if (GetBlockSize (*lpo) == sizeof(InnerListDesc))
        list = LPINNERLISTDESC (*lpo)->list;
      else
        list = GetListFromForParam_noset (*lpo);
      }
    DBINT res = 0;
    if (list != NULL) {
      for (LPDBRECORD h = list->GetFirst() ; h != NULL ; h = list->GetNext(h))
        res ++ ;
      }
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetLineCount_param FAR *par = (GetLineCount_param FAR *) param;
    c->SetlConnection (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetLineCount_param FAR *par = (GetLineCount_param FAR *) param;
    c->ClearlConnection (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//////////////////////////////////////////////////////////////////////
//  Laden einer internen Tabelle
//////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR LoadInternList_param {
  WORD parSize;

  DBList FAR *dblist;
  MultiProc FAR *mp;
  WORD TableInd;

  DWORD AccessName;
  DWORD TableName;
  DWORD procToCall;
  DWORD _AnzPars;
  DWORD Param[1];

  LPTABLEDEF GetTableDef(mdiChild *c,WORD FAR *TableInd);
  LPSTR GetAccessName(mdiChild *c);
  LPPARAM GetLPParams(LPPARAM p,mdiChild *c);
  void SetConnections(mdiChild *c);
  void ClearConnections(mdiChild *c);
  int ReadParData (mdiChild *c,LPVOID FAR *ParData,WORD FAR *Type);
  int AnzPars (mdiChild *c)
    {
    DBWIN_ASSERT(c->IsConst(_AnzPars));
    return *((DBINT FAR *) c->ReadlData (_AnzPars));
    }
  };
#pragma pack()

LPTABLEDEF LoadInternList_param::GetTableDef(mdiChild *c,WORD FAR *TableInd)
  {
  LPSTR Name = LPSTR(c->ReadlData (TableName));
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(c->schd->TRef[i].TableNr,c->schd->TRef[i].Version);
    if (lstrcmp(Name,td->GetName()) == 0) {
      *TableInd = i + CSYSRECS;
      return td;
      }
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }

LPSTR LoadInternList_param::GetAccessName(mdiChild *c)
  {
  return LPSTR (c->ReadlData (AccessName));
  }

LPPARAM LoadInternList_param::GetLPParams(LPPARAM p,mdiChild *c)
  {
  if (AnzPars(c) == 0)
    return NULL;
  else {
    lmemset (p,'\0',sizeof(*p));
    for (int i = 0 ; i < int(AnzPars(c)) ; i++) {
      p->ptr[i] = c->ReadlData (Param[i]);
      p->pType[i] = c->GetDataType (Param[i]);
      }
    p->AnzPars = int(AnzPars(c));
    return p;
    }
  }

int LoadInternList_param::ReadParData (mdiChild *c,LPVOID FAR *ParData,WORD FAR *Type)
  {
  for (int i = 0 ; i < int(AnzPars(c)) ; i++) {
    ParData[i] = c->ReadlData (Param[i]);
    Type[i] = c->GetDataType (Param[i]);
    }
  return i;
  }
void LoadInternList_param::SetConnections(mdiChild *c)
  {
  for (int i = 0 ; i < int(AnzPars(c)) ; i++)
    c->SetlConnection (Param[i],LPSTR(this)-sizeof(WORD));
  }
void LoadInternList_param::ClearConnections(mdiChild *c)
  {
  for (int i = 0 ; i < int(AnzPars(c)) ; i++)
    c->ClearlConnection (Param[i],LPSTR(this)-sizeof(WORD));
  }

#pragma pack(1)
struct InternListDesc {
  DBList FAR *list;
  WORD TableInd;
  };
#pragma pack()
typedef InternListDesc FAR *LPINTLISTDESC;

BOOL LoadInternList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LoadInternList_param FAR *par = (LoadInternList_param FAR *) param;
    ParamBlock p;
    WORD TableInd;
    LPTABLEDEF td = par->GetTableDef(c,&TableInd);
    par->dblist = new DBList (td,
                              c->DocumentID(),
                              par->GetAccessName(c),
                              -1,
                              -1,
                              par->GetLPParams(&p,c)
                             );
    
    LPDBRECORD old = c->rr->GetRecord(TableInd);
    par->mp = new MultiProc (c,par->procToCall,TRUE);
    for (LPDBRECORD r = par->dblist->GetFirst () ; r != NULL ; r = par->dblist->GetNext (r) ) {
      par->mp->AddProcAtTail ();
      c->rr->SetRecord (TableInd,r);
      SetExtraInfo s(c,TableInd,r,par->mp->CorrOffs());
      WORD mymode = EM_LOAD | EM_CHANGETOTRUE ;
      if (mode & EM_FIXCONNECTION)
        mymode |= EM_FIXCONNECTION ;
      par->mp->ExCuteLast (mymode,&s);
      } while (r != NULL);
    c->rr->SetRecord (TableInd,old);
    par->TableInd = TableInd;
    }
  if (mode & EM_UPDATE) {
    LoadInternList_param FAR *par = (LoadInternList_param FAR *) param;
    ParamBlock p ;
#ifdef UEBERLEGT
    par->GetLPParams(&p,c);
    par->dblist->SetParams (&p);
#endif
    par->dblist->SetParams (par->GetLPParams(&p,c));
    par->dblist->RefreshJoins (NULL,0);
    }
  if (mode & EM_FIXCONNECTION) {
    LoadInternList_param FAR *par = (LoadInternList_param FAR *) param;
    par->SetConnections (c);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    LoadInternList_param FAR *par = (LoadInternList_param FAR *) param;
    par->ClearConnections (c);

    WORD TableInd = par->TableInd;
    LPDBRECORD old = c->rr->GetRecord(TableInd);
    WORD i = 0 ;
    for (LPDBRECORD r = par->dblist->GetFirst () ; r != NULL ; r = par->dblist->GetNext (r) ) {
      c->rr->SetRecord (TableInd,r);
      SetExtraInfo s(c,TableInd,r,par->mp->CorrOffs());
      WORD mymode = EM_RESET ;
      c->_ccount = PushBlock(c->_ccount);
      par->mp->ExCuteFirst (mymode,&s);
      c->_ccount = PopBlock(c->_ccount);
      par->mp->RemoveFirst ();
      } 
    c->rr->SetRecord (TableInd,old);

    delete par->mp;
    par->mp = NULL;

    delete par->dblist ;
    GetTableAdmin()->FreeTable(c->schd->TRef[TableInd-CSYSRECS].TableNr,c->schd->TRef[TableInd-CSYSRECS].Version);
    par->dblist = NULL ;
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////////////////////
//  Laden einer Liste, ohne mit Ihr direkt etwas anzufangen
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR LoadList_param {
  WORD parSize;
  LPINTLISTDESC d;
  DWORD listPtr;
  DWORD AccessName;
  DWORD TableName;
  DWORD _AnzPars;
  DWORD Param[1];

  LPTABLEDEF GetTableDef(mdiChild *c,WORD FAR *TableInd);
  LPSTR GetAccessName(mdiChild *c);
  LPPARAM GetLPParams(LPPARAM p,mdiChild *c);
  int AnzPars (mdiChild *c)
    {
    DBWIN_ASSERT(c->IsConst(_AnzPars));
    return *((DBINT FAR *) c->ReadlData (_AnzPars));
    }
  };
#pragma pack()

LPTABLEDEF LoadList_param::GetTableDef(mdiChild *c,WORD FAR *TableInd)
  {
  LPSTR Name = LPSTR(c->ReadlData (TableName));
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(c->schd->TRef[i].TableNr,c->schd->TRef[i].Version);
    if (lstrcmp(Name,td->GetName()) == 0) {
      *TableInd = i + CSYSRECS;
      return td;
      }
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }

LPSTR LoadList_param::GetAccessName(mdiChild *c)
  {
  return LPSTR (c->ReadlData (AccessName));
  }

LPPARAM LoadList_param::GetLPParams(LPPARAM p,mdiChild *c)
  {
  if (AnzPars(c) == 0)
    return NULL;
  else {
    lmemset (p,'\0',sizeof(*p));
    for (int i = 0 ; i < int(AnzPars(c)) ; i++) {
      p->ptr[i] = c->ReadlData (Param[i]);
      p->pType[i] = c->GetDataType (Param[i]);
      }
    p->AnzPars = int(AnzPars(c));
    return p;
    }
  }

BOOL LoadList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LoadList_param FAR *par = (LoadList_param FAR *) param;
    ParamBlock p;
    par->d = LPINTLISTDESC(GetGlobMem (sizeof(*par->d)));
    LPTABLEDEF td = par->GetTableDef(c,&par->d->TableInd);
    par->d->list = new DBList (td,
                               c->DocumentID(),
                               par->GetAccessName(c),
                               -1,
                               -1,
                               par->GetLPParams(&p,c),
                               FALSE
                              );
    c->WritelData (par->listPtr,&par->d,sizeof(par->d),LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    LoadList_param FAR *par = (LoadList_param FAR *) param;
    delete par->d->list;
    GetTableAdmin()->FreeTable(c->schd->TRef[par->d->TableInd-CSYSRECS].TableNr,c->schd->TRef[par->d->TableInd-CSYSRECS].Version);
    }
  return FALSE ;
  }

#pragma pack(1)
struct PackList_param {
  WORD parSize;
  LPVOID res;
  DWORD lpres;
  DWORD list;
  DWORD varToPush;
  };
#pragma pack()

#pragma pack(1)
struct PackedList {
  int AnzRecs;
  int RecSize;
  };
#pragma pack()
typedef PackedList FAR *LPPACKEDLIST;

LPVOID PushToRes (LPVOID o,LPVOID d,int varSize,BOOL freeOld = TRUE)
  {
  if (o == NULL) {
    o = GetGlobMem (sizeof(PackedList));
    PackedList FAR *r = (PackedList FAR *) o;
    r->RecSize = varSize;
    freeOld = TRUE ;
    }
  LPVOID n = GetGlobMem (GetBlockSize(o) + varSize);
  lmemcpy (n,o,GetBlockSize(o));
  lmemcpy (LPSTR(n)+GetBlockSize(o),d,varSize);
  PackedList FAR *r = (PackedList FAR *) n;
  r->AnzRecs += 1;
  if (freeOld)
    FreeGlobMem (o);
  return n;
  }

BOOL PackList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PackList_param FAR *par = (PackList_param FAR *) param;
    LPINTLISTDESC FAR *d = (LPINTLISTDESC FAR *) c->ReadlData (par->list);
    DBWIN_ASSERT ((d != NULL) && (*d != NULL));
    DBWIN_ASSERT (LOWORD(par->varToPush) == (*d)->TableInd);
    DBWIN_ASSERT (par->res == NULL);
    LPDBRECORD old = c->rr->GetRecord((*d)->TableInd);
    WORD i = 0 ;
    int varSize = -1;
    for ( LPDBRECORD r = (*d)->list->GetFirst () ; r != NULL ; r = (*d)->list->GetNext (r) ) {
      c->rr->SetRecord ((*d)->TableInd,r);
      LPVOID data = c->ReadlData (par->varToPush);
      if (data != NULL) {
        int nVarSize = int (GetBlockSize(data));
        if (varSize < 0) varSize = nVarSize ;
        else             { DBWIN_ASSERT (nVarSize == varSize); }
        par->res = PushToRes (par->res,data,varSize);
        }
      }
    c->rr->SetRecord ((*d)->TableInd,old);
    PackedList FAR *p = (PackedList FAR *) par->res;
    if (p != NULL)
      c->WritelData (par->lpres,p,p->AnzRecs*p->RecSize+sizeof(*p),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->lpres,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    PackList_param FAR *par = (PackList_param FAR *) param;
    if (par->res != NULL) {
      FreeGlobMem (par->res);
      par->res = NULL;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct PushToPackList_param {
  WORD parSize;
  DWORD res;
  DWORD key;
  };
#pragma pack()

BOOL PushToPackList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PushToPackList_param FAR *par = (PushToPackList_param FAR *) param;
    LPPACKEDLIST x = LPPACKEDLIST (c->ReadlData (par->res));
    LPVOID key = c->ReadlData (par->key);
    DBWIN_ASSERT (key != NULL);
    x = LPPACKEDLIST (PushToRes (x,key,GetBlockSize(key),FALSE));
    c->WritelData (par->res,x,x->AnzRecs*x->RecSize+sizeof(*x),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetLineObjects (mdiChild FAR *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetLineObjects_param FAR *par = (SetLineObjects_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lst);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    if (par->AnzFlds() == 0)
      obj->SetLineObjects (NULL);
    else
      obj->SetLineObjects (par);
    }
  return FALSE ;
  }


BOOL NonRepeativeObjects (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    NonRepeativeObjects_param FAR *par = (NonRepeativeObjects_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lst);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    obj->NonRepeativeObjects (par);
    }
  return FALSE ;
  }

#pragma pack(1)
struct EmptyInnerList_param {
  WORD parSize;
  DWORD lPtr;
  };
#pragma pack()
extern void OnEmptyList (LPVOID obj);
BOOL EmptyInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    EmptyInnerList_param FAR *par = (EmptyInnerList_param FAR *) param;
    RecordList FAR *list = NULL;
    LPVOID FAR *lpo = (LPVOID FAR *) (c->ReadlData (par->lPtr));
    if ((lpo != NULL) && (*lpo != NULL)) {
      if (GetBlockSize (*lpo) == sizeof(InnerListDesc)) {
        list = LPINNERLISTDESC (*lpo)->list;
        if (LPINNERLISTDESC (*lpo)->lo != NULL) {
          for (LPDBRECORD h = list->GetFirst() ; h != NULL ; ) {
            LPDBRECORD next = list->GetNext(h);
            LPINNERLISTDESC (*lpo)->lo->MyList->RemoveElem (h->GetPrimKey()->Data);
            h = next ;
            }
          list = NULL ;
          }
        }
      else {
        OnEmptyList (*lpo);
        }
      }
    if (list != NULL) {
      list->ThrowList ();
      LPVOID Data = GetGlobMem (GetBlockSize (lpo));
      lmemcpy (Data,lpo,GetBlockSize(lpo));
      c->WritelData (par->lPtr,Data,GetBlockSize(Data),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (Data);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EmptyInnerList_param FAR *par = (EmptyInnerList_param FAR *) param;
    c->ClearlConnection (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
    
  return FALSE ;
  }

#pragma pack(1)
struct FAR bIsSelected_param {
  WORD parSize;
  DWORD lRef;
  DWORD val[1];
  int AnzSegs() 
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; }
  };
#pragma pack()
BOOL bIsSelected (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & EM_LOAD) {
    bIsSelected_param FAR *par = (bIsSelected_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    PrimKey k;
    BOOL alldone = TRUE ;
    for (int i = 0 ; i < par->AnzSegs() ; i++) {
      LPVOID data = c->ReadlData (par->val[i]);
      if (data != NULL)
        k.PushKeySeg (data,GetBlockSize(data));
      else
        alldone = FALSE ;
      }
    if (alldone)
      res = obj->IsKeySelected (&k);
    else
      res = FALSE ;
    }
  return res ;
  }


#pragma pack(1)
struct FAR SetListColor_param {
  WORD parSize;
  DWORD Color;
  DWORD type;
  DWORD lRef;
  BOOL MitListenObjekt ()
    {
    return (parSize >= sizeof(*this));
    }
  };
struct FAR SetFrameType_param {
  WORD parSize;
  DWORD lRef;
  BOOL MitListenObjekt ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()
static DWORD cNormal[2],cSpez[2];
static BOOL nSet[2],sSet[2];
static ListObj FAR *lSpez,FAR *fSpez;
DWORD GetListColor (WORD Type,ListObj FAR *obj)
  {
  DBWIN_ASSERT ((Type >= 0) && (Type <= 1)) ;
  if (obj == lSpez) {
    if (sSet[Type])
      return cSpez[Type];
    }
  else {
    if (nSet[Type])
      return cNormal[Type];
    }
  switch (Type) {
    case 0 :
      return GetSysColor (COLOR_HIGHLIGHT);
    case 1 :
      return GetSysColor (COLOR_GRAYTEXT);
    }
  return 0L;
  }

void OnListDestroy (ListObj FAR *o)
  {
  if (lSpez == o) {
    sSet[0] = FALSE ;
    sSet[1] = FALSE ;
    lSpez = NULL ;
    }
  if (fSpez == o)
    fSpez = NULL ;
  }

BOOL GetFrameType (ListObj FAR *o)
  {
  return (fSpez == o);
  }
BOOL SetFrameType (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetFrameType_param FAR *par = (SetFrameType_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadlData (par->lRef));
    DBWIN_ASSERT((t != NULL) && (*t != NULL));
    fSpez = (ListObj FAR *) (* t)->extObj;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetFrameType_param FAR *par = (SetFrameType_param FAR *) param;
    c->ClearlConnection (par->lRef,LPSTR(par) - sizeof(WORD));
    }
  return FALSE ;
  }
BOOL SetListColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetListColor_param FAR *par = (SetListColor_param FAR *) param;
    LPDWORD lpColor = LPDWORD (c->ReadlData (par->Color));
    DBINT FAR *lptype = (DBINT FAR *) (c->ReadlData (par->type));
    DBWIN_ASSERT ((lptype != NULL) && (*lptype >= 0) && (*lptype <= 1)) ;
    if (par->MitListenObjekt ()) {
      LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadlData (par->lRef));
      DBWIN_ASSERT((t != NULL) && (*t != NULL));
      lSpez = (ListObj FAR *) (* t)->extObj;
      if (lpColor != NULL) { 
        cSpez[*lptype] = *lpColor ; 
        sSet[*lptype] = TRUE ; 
        }
      else
        sSet[*lptype] = FALSE ; 
      }
    else {
      if (lpColor != NULL) { 
        cNormal[*lptype] = *lpColor ; 
        nSet[*lptype] = TRUE ; 
        } 
      else
        nSet[*lptype] = FALSE ; 
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetListColor_param FAR *par = (SetListColor_param FAR *) param;
    c->SetlConnection (par->Color,LPSTR(par) - sizeof(WORD));
    c->SetlConnection (par->type,LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetListColor_param FAR *par = (SetListColor_param FAR *) param;
    c->ClearlConnection (par->Color,LPSTR(par) - sizeof(WORD));
    c->ClearlConnection (par->type,LPSTR(par) - sizeof(WORD));
    if (par->MitListenObjekt ())
      c->ClearlConnection (par->lRef,LPSTR(par) - sizeof(WORD));
    }
  return FALSE ;
  }

