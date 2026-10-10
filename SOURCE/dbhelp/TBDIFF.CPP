//////////////////////////////////////////////////////////////////////
//  Bilden von Tabellendifferenzen
//////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/tbdiff.cpv   1.8   05 Oct 1998 11:09:42   Gerhold  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/tbdiff.cpv  $
// 
//    Rev 1.8   05 Oct 1998 11:09:42   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   30 Mar 1998 20:28:18   Hannes
// SameIDs pruefen
// 
//    Rev 1.6   25 Nov 1997 19:37:12   Hannes
// 
//    Rev 1.5   24 Oct 1997 08:38:02   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.4   27 May 1997 11:13:36   Hannes
// Modulnummer
// 
//    Rev 1.3   06 Dec 1996 14:13:24   HANNES
// VarsToDrop besser bestimmt
// 
//    Rev 1.2   03 Dec 1996 21:11:22   HANNES
// 
//    Rev 1.1   26 Nov 1996 19:06:08   HANNES
// Variablen, die nur im _ID teil dazugekommen sind, ignorieren
// 
//    Rev 1.0   26 Nov 1996 07:55:10   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 181
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"

#include "tbdiff.hpp"

LPVOID Push(LPVOID old,LPVOID data,int Size)
  {
  LPVOID res;
  if (old) {
    res = GetGlobMem (GetBlockSize (old) + Size);
    lmemcpy (res,old,GetBlockSize(old));
    lmemcpy (LPSTR(res) + GetBlockSize(old),data,Size);
    }
  else {
    res = GetGlobMem (Size);
    lmemcpy (res,data,Size);
    }
  return res;
  }

_v2v FAR *Push(_v2v FAR *old,_v2v FAR *v)
  {
  return (_v2v FAR *) Push (old,v,sizeof(*v));
  }
short FAR *Push (short FAR *old,short i)
  {
  return (short FAR *) Push (old,&i,sizeof(i));
  }

LPCLKEYDEF GetKeySeg (LPTABLEDEF t,int KeyNmbr,int SegNmbr)
  {
  int s = 0 ;
  for (int i = 0 ; i < t->GetAnzKeySegs() ; i++) {
    LPCLKEYDEF r = t->GetKeyDef(i);
    if (r->KeyNmbr == WORD (KeyNmbr)) {
      if (s == SegNmbr) return r;
      else              s ++ ;
      }
    }
  return NULL;
  }
DLLExport short _export WINAPI TableDifference::VarIDFrom (short VarIDTo)
  {
  int j = AnzVarsToCopy() ;
  for (int i = 0 ; i < j ; i++)
    if (v2v[i].vTo == VarIDTo) return v2v[i].vFrom ;
  return -1;
  }
DLLExport BOOL _export WINAPI TableDifference::IsToModify (short vTo)
  {
  int j = AnzModified() ;
  for (int i = 0 ; i < j ; i++)
    if (Modified[i] == vTo) return TRUE ;
  return FALSE ;
  }
DLLExport BOOL _export WINAPI TableDifference::IsSameKey (LPTABLEDEF t1,LPTABLEDEF t2,int KeyNmbr,BOOL FAR *doStop,BOOL FAR *r1Found,BOOL FAR *r2Found)
  {
  *doStop  = FALSE ;
  *r1Found = FALSE ;
  *r2Found = FALSE ;
  for (int i = 0 ; ; i++) {
    LPCLKEYDEF r1 = GetKeySeg (t1,KeyNmbr,i);
    LPCLKEYDEF r2 = GetKeySeg (t2,KeyNmbr,i);
    if (r1 != NULL) *r1Found = TRUE ;
    if (r2 != NULL) *r2Found = TRUE ;
    if ((r1 == NULL) && (r2 == NULL)) {
      *doStop = (i == 0);
      return TRUE ;
      }
    if ((r1 != NULL) && (r2 != NULL)) {
      if (lstrcmp (r1->name,r2->name))     return FALSE ;
      if (r1->Attribute != r2->Attribute)  return FALSE ;
      if ((WORD(VarIDFrom (r1->VarID)) != r2->VarID) ||
          (IsToModify (r1->VarID)))        return FALSE ;
      }
    else
      return FALSE ;
    }
  }
DLLExport _export WINAPI TableDifference::TableDifference 
  (LPTABLEDEF told,LPTABLEDEF tnew,
  WORD PropFilter,WORD KPropFilter
  )
  {
  v2v = NULL;
  Modified = NULL;
  VarsToAdd = NULL;
  VarsToDrop = NULL;
  KeysToAdd = NULL;
  KeysToDrop = NULL;

  int avnew = tnew->GetAnzVars();
  int avold = told->GetAnzVars();

  t0 = told;
  t1 = tnew;

  for (int i = 0 ; i < avnew ; i++) {
    // 
    // Variablen, die Umkopiert werden muessen, bzw. die neu dazukommen
    //
    LPVARDEF vnew = tnew->GetVarDef(i);
    for (int j = 0 ; j < avold ; j++) {
      LPVARDEF vold = told->GetVarDef(j);
      if (lstrcmp (vold->GetName(),vnew->GetName()) == 0) {
        _v2v v2vn;
        v2vn.vFrom = j ;
        v2vn.vTo = i ;
        v2v = Push(v2v,&v2vn);
        if ((vold->VarSize != vnew->VarSize) ||
            ((vold->VarSize == 0xFFFF) && (vold->VarID != vnew->VarID)) ||
            (vold->mType != vnew->mType) ||
            ((vold->Property & PropFilter) != (vnew->Property & PropFilter)))
          Modified = Push(Modified,i);

        break ;
        }
      }
    if (j >= avold) {
      if (!(vnew->VarSize == 0xFFFF))
        VarsToAdd = Push(VarsToAdd,i);
      }
    }

  // 
  // Variablen, die gedroppt werden
  //
  for (i = 0 ; i < avold ; i++) {
    if (!IsToCopy(i))
      VarsToDrop = Push(VarsToDrop,i);
    }

  //
  // Schluesselsegmente untersuchen
  //
  BOOL doStop = FALSE ;
  for (i = 0 ; (!doStop); i++) {
    BOOL r1found,r2found;
    if (!IsSameKey (tnew,told,i,&doStop,&r1found,&r2found)) {
      if (r1found)
        KeysToAdd = Push (KeysToAdd,i);
      if (r2found)
        KeysToDrop = Push (KeysToDrop,i);
      }
    }
  }

DLLExport BOOL _export WINAPI TableDifference::NoDifference ()
  {
  return ((Modified == NULL) && (VarsToAdd == NULL) && (VarsToDrop == NULL) &&
          (KeysToAdd == NULL) && (KeysToDrop == NULL) && SameSort () && (SameIDs())) ;
  }
DLLExport BOOL _export WINAPI TableDifference::SameSort ()
  {
  int j = AnzVarsToCopy();
  for (int i = 0 ; i < j ; i++) {
    if (v2v[i].vFrom != v2v[i].vTo) return FALSE ;
    }
  return TRUE ;
  }
DLLExport BOOL _export WINAPI TableDifference::SameIDs ()
  {
  BOOL oldWithID = FALSE;
  for (int i = 0 ; i < t0->GetAnzVars () ; i++) {
    if (t0->GetVarDef(i)->VarSize == 0xFFFF)
      oldWithID = TRUE;
    }
  BOOL newWithID = FALSE;
  for (i = 0 ; i < t1->GetAnzVars () ; i++) {
    if (t1->GetVarDef(i)->VarSize == 0xFFFF)
      newWithID = TRUE;
    }
  return (oldWithID == newWithID) ;
  }
DLLExport _export WINAPI TableDifference::~TableDifference ()
  {
  if (v2v != NULL)          FreeGlobMem (v2v);
  if (Modified != NULL)     FreeGlobMem (Modified);
  if (VarsToAdd != NULL)    FreeGlobMem (VarsToAdd);
  if (VarsToDrop != NULL)   FreeGlobMem (VarsToDrop);
  if (KeysToAdd != NULL)    FreeGlobMem (KeysToAdd);
  if (KeysToDrop != NULL)   FreeGlobMem (KeysToDrop);
  }

DLLExport void _export WINAPI InitializeDefVal (DefVal FAR *dv,int AnzDefs,LPTABLEDEF tnew)
  {
  for (int i = 0 ; i < AnzDefs ; i++) {
    for (int j = 0 ; j < tnew->GetAnzVars () ; j++) {
      if (lstrcmp (dv[i].VarName,tnew->GetVarDef(j)->GetName()) == 0)
        dv[i].VarID = j ;
      }
    }
  }

DLLExport LPDBRECORD _export WINAPI ConvertRecord (LPTABLEDEF tnew,LPDBRECORD h,TableDifference FAR *td,int AnzDefs,DefVal FAR *dv)
  {
  LPDBRECORD n = new DBRecord (tnew);
  int anzToCopy = td->AnzVarsToCopy();
  for (int i = 0 ; i < anzToCopy ; i++) {
    LPVOID data = h->Get(td->v2v[i].vFrom);
    if (data != NULL) {
      LPVARDEF vNew = tnew->GetVarDef(td->v2v[i].vTo);
      if (vNew->mType == VAR_LONG) {
        int siz = GetBlockSize(data);
        if (siz < sizeof(LONG)) {
          LONG lData = *(DBINT FAR *)data;
          n->Initialize(td->v2v[i].vTo,&lData,sizeof(lData));
          }
        else
          n->Initialize(td->v2v[i].vTo,data,GetBlockSize(data));
        }
      else
        n->Initialize(td->v2v[i].vTo,data,GetBlockSize(data));
      }
    }
  for (i = 0 ; i < AnzDefs ; i++) {
    WIN_ASSERT (td->IsToAdd (dv[i].VarID));
    n->Initialize(dv[i].VarID,dv[i].DefaultValue,GetBlockSize (dv[i].DefaultValue));
    }

  return n;
  }

//------------------------------------------------------------------------
// Update der Zwischentabellen
//------------------------------------------------------------------------
static HWND outDlg;
extern DLLExport BOOL FAR PASCAL _export ConvertDlgProc (HWND hDlg, UINT message, WPARAM wP,
                                                               LPARAM lP);
extern HINSTANCE hLibInst;
DLLExport void _export WINAPI aAltSuccess (DWORD s)
  {
  MSG m;
  char textstr[64];
  wsprintf (textstr, "%ld", s);
  SetDlgItemText (outDlg,102,textstr);
  while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage (&m);
    DispatchMessage (&m);
    }
  }
DLLExport void _export WINAPI UpdateIntermediate ()
  {
  MSG m;
  DBList FAR *res = GetAllTempDataDict ();
  for (LPDBRECORD h = res->GetFirst () ; h ; h = res->GetNext(h) ) {
    LPSTR Name = LPSTR(h->Get(1));
    WORD Version;
    BOOL found;
    WORD TableID = GetTableAdmin()->GetTableID(NULL,Name,&found,&Version);

    LPTABLEDEF tdold = GetTableAdmin()->GetTableDef(TableID,DBMAXVERSION);
    LPTABLEDEF tdnew = GetTableAdmin()->GetTableDef(TableID,Version);

    if ((tdold != NULL) && (tdnew != NULL)) {
      if (!IsWindow (outDlg)) {
        outDlg = CreateDialog (hLibInst,"DIALOG_1",GetActiveWindow(),DLGPROC(ConvertDlgProc));
        EnableWindow (GetDlgItem(outDlg,IDCANCEL),FALSE);
        }
      SetDlgItemText (outDlg,101,tdnew->GetName());
      while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage (&m);
        DispatchMessage (&m);
        }
      int st = GetDLLAdmin()->GetDLLEntry(tdnew->GetDLLHandle())->DBAlter (tdold,tdnew,aAltSuccess);
      if (st != 0) {
        char msgstr[256];
        wsprintf (msgstr,"Fehler beim ALTER: %s,%d",Name,st);
        WIN_ASSERT_TEXT (FALSE,msgstr);
        }
      else {
        // Die Sicherheitskopie kann (muss) geloescht werden
        DelDataDict (0,TableID,DBMAXVERSION);
        EndTransaction();
        }
      }

    if (tdold != NULL) GetTableAdmin()->FreeTable(TableID,DBMAXVERSION);
    if (tdnew != NULL) GetTableAdmin()->FreeTable(TableID,Version);
    }
  delete res ;
  if (IsWindow (outDlg)) {
    DestroyWindow (outDlg);
    outDlg = NULL ;
    }
  }
