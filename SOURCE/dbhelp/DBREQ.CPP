////////////////////////////////////////////////////////////////
//  Requestbuffer fuer eine Datenbankabfrage
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/dbreq.cpv   1.13   28 Jan 1999 12:21:04   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/dbreq.cpv  $
// 
//    Rev 1.13   28 Jan 1999 12:21:04   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.12   30 Apr 1997 11:27:54   Hannes
// 
//    Rev 1.11   12 Dec 1996 12:19:34   HANNES
// Alte Schluesselsegmente fuer die Foreignkeys
// 
//    Rev 1.10   26 Nov 1996 07:53:16   HANNES
// 
//    Rev 1.9   02 Feb 1996 10:42:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   15 Sep 1995 20:42:40   HANNES
// Zugriff fuer Joins ... Stringgroessenrestriktion raus
// 
//    Rev 1.7   19 Jul 1995 11:10:42   HANNES
// 
//    Rev 1.6   14 Jul 1995 16:56:18   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.5   04 Apr 1995 12:13:44   HANNES
// 
//    Rev 1.4   24 Feb 1995 11:12:38   HANNES
//  
// 
//    Rev 1.3   16 Feb 1995 12:48:46   HANNES
//  
// 
//    Rev 1.2   05 Dec 1994 17:39:56   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   17 Jul 1994 14:33:24   HANNES
// Umbau der Primaerschluesselverwaltung, Durchreichen der Parameter beim Join
// 
//    Rev 1.0   24 Jun 1994 16:44:46   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#define MODULENUM 80
#include "winass.hpp"

DLLExport LPDBREQUEST _export WINAPI InitializeRequest (LPSTR SelectionName,int AnzElems,int Type,DWORD Id)
  {
  LPDBREQUEST res = LPDBREQUEST (GetGlobMem (sizeof(*res)));
  if (AnzElems > 0)
    res->elem = LPREQELEM (GetGlobMem (AnzElems * sizeof(ReqElem)));
  else
    res->elem = NULL;
  res->SelectionName = LPSTR (GetGlobMem (lstrlen(SelectionName)+1));
  lstrcpy (res->SelectionName,SelectionName);
  res->Type = Type;
  res->AnzElems = AnzElems;
  res->DocID = Id ;
  return res;
  }

DLLExport void _export WINAPI DBRequest::SetNewDimension (int na)
  {
  if (na > AnzElems) {
    LPREQELEM ne = LPREQELEM(GetGlobMem (na * sizeof(*ne)));
    if (elem != NULL) {
      lmemcpy (ne,elem,GetBlockSize(elem));
      FreeGlobMem (elem);
      }
    elem = ne;
    AnzElems = na;
    }
  }

DLLExport void _export WINAPI FreeOldParam (LPOLDPARAM oldP)
  {
  if (oldP != NULL) {
    for (int i = 0 ; i < CB_TABLEDEF ; i++) {
      for (int j = 0 ; j < MANZSEGS ; j++) {
        if (oldP->Param[i][j] != NULL)
          FreeGlobMem (oldP->Param[i][j]);
        }
      }
    FreeGlobMem (oldP);
    }
  }

DLLExport void _export WINAPI FreeRequest (LPDBREQUEST req)
  {
  FreeGlobMem (req->SelectionName);
  req->ClearOutParam ();
  if (req->elem != NULL)
    FreeGlobMem (req->elem);
  if (req->OrderStatement)
    FreeGlobMem (req->OrderStatement);
  if (req->AlternateName != NULL)
    FreeGlobMem (req->AlternateName);
  FreeOldParam (req->oldP);
  FreeGlobMem (req);
  }

LPSTR GetAlternatName (DWORD Id,LPSTR Name);
DLLExport void _export WINAPI DBRequest::AddTableDef (LPTABLEDEF td,BOOL ls)
  {
  if (AnzTables == 0) {
    LPSTR an = GetAlternatName (DocID,td->GetName()) ;
    if (an != NULL) {
      AlternateName = LPSTR (GetGlobMem (lstrlen(an) + 1)) ;
      lstrcpy (AlternateName,an);
      }
    }
  WIN_ASSERT (AnzTables < CB_TABLEDEF);
  TableDef[AnzTables] = td;
  WIN_ASSERT (td->GetDLLHandle() == TableDef[0]->GetDLLHandle()); // Keine Spruenge in der DLL
                                                                  // bitte !
  doLock[AnzTables] = ls;
  AnzTables++;
  }

DLLExport void _export WINAPI DBRequest::AddTableDef (WORD TableID,WORD Version,BOOL ls)
  {
  AddTableDef (GetTableAdmin ()->GetTableDef(TableID,Version),ls);
  }

DLLExport void _export WINAPI DBRequest::FreeTableDefs ()
  {
  for (int i = 0 ; i < int (AnzTables) ; i++) {
    GetTableAdmin ()->FreeTable (TableDef[i]->GetTableID(),TableDef[i]->GetVersion());
    }
  }

DLLExport void _export WINAPI DBRequest::SetReqElem (int Num,WORD TableID,WORD VarID)
  {
  WIN_ASSERT (Num < int(AnzElems));
  for (int i = 0 ; i < int (AnzTables) ; i++) {
    if (TableDef[i]->GetTableID() == TableID) break ;
    }
  WIN_ASSERT (i < int (AnzTables));
  elem[Num].TableNumber = i;
  elem[Num].VarID = VarID;
  }

DLLExport void _export WINAPI DBRequest::SetReqElemDirect (int Num,WORD TableNumber,WORD VarID)
  {
  WIN_ASSERT (Num < int(AnzElems));
  elem[Num].TableNumber = TableNumber;
  elem[Num].VarID = VarID;
  }

// Suchen einer Variable im Requestbuffer
////////////////////////////////////////////////
DLLExport WORD _export WINAPI DBRequest::GetVarNumber (WORD TableID,WORD VarID,BOOL FAR *done)
  {
  WORD Nr = 0;
  if (AnzElems > 0) {
    if (done != NULL) *done = FALSE ;
    for (int i = 0 ; i < AnzElems ; i++) {
      if ((elem[i].VarID == VarID) && 
              (TableDef[elem[i].TableNumber]->GetTableID() == TableID)) {
        if (done != NULL) *done = TRUE ;
        Nr = WORD(i) ;
        break ;
        }
      }
    }
  else {
    if (done != NULL) *done = TRUE ;
    }
  return Nr;
  }

DLLExport WORD _export WINAPI DBRequest::GetVarNumberByNum (WORD TableNr,WORD VarID,BOOL FAR *done)
  {
  WORD Nr = 0;
  if (AnzElems > 0) {
    if (done != NULL) *done = FALSE ;
    for (int i = 0 ; i < AnzElems ; i++) {
      if ((elem[i].VarID == VarID) && 
              (elem[i].TableNumber == int(TableNr))) {
        if (done != NULL) *done = TRUE ;
        Nr = WORD(i) ;
        break ;
        }
      }
    }
  else {
    Nr = VarID;
    if (done != NULL) *done = TRUE ;
    }
  return Nr;
  }

// Runterholen aller Variablen einer Bestimmten Tabelle
//////////////////////////////////////////////////////////
static LPREQELEM PushRequest (LPREQELEM h,WORD TableID,WORD VarID)
  {
  int dim = (h != NULL) ? GetBlockSize(h) / sizeof(*h) : 0;
  LPREQELEM n = LPREQELEM (GetGlobMem ((dim + 1) * sizeof(*n)));
  if (h != NULL) lmemcpy (n,h,dim * sizeof(*n)) , FreeGlobMem (h);
  n[dim].TableNumber = TableID;
  n[dim].VarID       = VarID;
  return n;
  }

DLLExport LPREQELEM _export WINAPI DBRequest::GetElemsOf (WORD TableNr)
  {
  WIN_ASSERT (AnzElems > 0);
  LPREQELEM h = NULL;
  for (int i = 0 ; i < AnzElems ; i++) {
    if (elem[i].TableNumber == int(TableNr))
      h = PushRequest (h,TableNr,elem[i].VarID);
    }
  return h;
  }

// Setzen der Requests unter gleichzeitigem Setzen der Tabellen
//////////////////////////////////////////////////////////////////
DLLExport void _export WINAPI DBRequest::SetReqElemExtended (int Num,WORD TableID,WORD Version,WORD VarID,BOOL doLock)
  {
  WIN_ASSERT (Num < AnzElems);
  // Untersuchen ob TableDef schon gesetzt
  for (WORD i = 0 ; i < AnzTables ; i++)
    if (TableDef[i]->GetTableID() == TableID) break ;
  if (i == AnzTables) {
    // Noch nicht drinnen -> neu setzen
    AddTableDef (TableID,Version);
    }
  // Noch das Element setzen
  elem[Num].TableNumber = i;
  elem[Num].VarID       = VarID;
  }

//////////////////////////////////////////////////////////////////////////
//  Untersuchung der Joins
//////////////////////////////////////////////////////////////////////////
int ClientRIDef::GetVarsforRI(WORD FAR *rivars)
  {
  switch (Type) {
    case CLKR_EXTENDED :
      {
      ExtendedRI FAR *ei = GetERI();
      WORD FAR *v = ei->GetVarIDList();
      for (int i = 0 ; i < int(AnzSegs) ; i++) {
        rivars[i] = v[i];
        }
      }
      break ;
    case CLKR_STANDARD :
      {
      StandardRI FAR *si = GetSRI();
      for (int i = 0 ; i < int(AnzSegs) ; i++) {
        rivars[i] = si->VarID;
        si = si->GetNextSRI();
        }
      }
      break ;
    case CLJR_RIEXTENDED :
    case CLJR_RISTANDARD :
    case CLJR_NEW        :
      {
      JoinDef FAR *jd = GetJDef();
      for (int i = 0 ; i < int(AnzSegs) ; i++) {
        rivars[i] = jd->VarID[i];
        }
      }
      break ;
    }
  return AnzSegs;
  }

DLLExport LPREQELEM _export WINAPI DBRequest::BuildForeign ()
  {
  LPREQELEM ElesToRequest = NULL;
  LPTABLEDEF td;
  if (AnzTables > 1)
    td = GetTableAdmin()->GetTableDef(tRef.TableNr,tRef.Version);
  for (WORD i = 1 ; i < AnzTables ; i++) {
    LPCLRIDEF r = td->GetRIDef (i-1);
    WIN_ASSERT (r != NULL);

    // Suchen des Foreignkeys
    WORD VarID[4];
    int AnzSegs = r->GetVarsforRI (VarID);

    if (AnzElems > 0) {
      for (int j = 0 ; j < MANZSEGS ; j++) {
        if (j >= AnzSegs)
          fdsc[i].VarID[j] = 0xFFFF;
        else
          fdsc[i].VarID[j] = VarID[j];
        }
      }

    // Rausholen aller Variablen, die so geholt werden sollen
    if (AnzElems > 0)
      ElesToRequest = GetElemsOf (i);

    // Aufbau des Requests
    int ETRCount = (ElesToRequest != NULL) ? 
            GetBlockSize(ElesToRequest) / sizeof(*ElesToRequest) : -1;
    fdsc[i].Type = r->Type ;
    fdsc[i].freq = InitializeRequest (r->name,ETRCount,
              (r->Type == CLJR_RIEXTENDED) ? DBCALLTYPE_EXTENDED : DBCALLTYPE_STANDARDGET,DocID
                                     );
    fdsc[i].freq->tRef.TableNr = TableDef[i]->GetTableID();
    fdsc[i].freq->tRef.Version = TableDef[i]->GetVersion();
    for (int j = 0 ; j < ETRCount ; j++) 
      fdsc[i].freq->SetReqElemExtended (j,
                    TableDef[ElesToRequest[j].TableNumber]->GetTableID(),
                    TableDef[ElesToRequest[j].TableNumber]->GetVersion(),
                    ElesToRequest[j].VarID,
                    doLock[ElesToRequest[j].TableNumber]
                                       );
    // Berechnung der Zuordnung zu den Orginalvariablen
    if (ETRCount > 0) {
      fdsc[i].VarIndex = LPWORD(GetGlobMem (ETRCount * sizeof(WORD)));
      for (j = 0 ; j < ETRCount ; j++)
        fdsc[i].VarIndex[j] = GetVarNumberByNum(ElesToRequest[j].TableNumber,ElesToRequest[j].VarID) ;
      }
    // Returnwert wird nicht gebraucht
    if (ElesToRequest != NULL)
      FreeGlobMem (ElesToRequest) ;
    ElesToRequest = NULL;
    }
  if (AnzTables > 1)
    GetTableAdmin()->FreeTable(tRef.TableNr,tRef.Version);

  foreignDone = TRUE ;

  return ElesToRequest ;
  }

DLLExport void _export WINAPI DBRequest::ClearForeign ()
  {
  for (WORD i = 1 ; i < AnzTables ; i++) {
    if (fdsc[i].freq != NULL) {
      fdsc[i].freq->ClearForeign();
      fdsc[i].freq->FreeTableDefs();
      if (fdsc[i].VarIndex != NULL)
        FreeGlobMem (fdsc[i].VarIndex);
      FreeRequest (fdsc[i].freq);
      }
    fdsc[i].freq = NULL;
    }
  foreignDone = FALSE;
  }

inline BOOL CompareData (LPVOID d1,LPVOID d2)
  {
  if ((d1 == NULL) && (d2 == NULL)) return TRUE ;
  if ((d1 != NULL) && (d2 != NULL) &&
      (GetBlockSize (d1) == GetBlockSize (d2)) &&
      (lmemcmp (d1,d2,GetBlockSize(d1)))) return TRUE ;
  return FALSE ;
  }

DLLExport BOOL _export WINAPI DBRequest::IsUpdateDone (LPDBRECORD rec,WORD TablePart,LPOLDPARAM oldP)
  {
  for (int j = 0 ; j < MANZSEGS ; j++) {
    if (fdsc[TablePart].VarID[j] != 0xFFFF) {
      LPVOID keyParam = rec->Get (fdsc[TablePart].VarID[j]);
      if (!CompareData (keyParam,oldP->Param[TablePart][j])) return TRUE ;
      }
    }
  return FALSE ;
  }

DLLExport void _export WINAPI DBRequest::SaveOldParams (LPDBRECORD rec,WORD TablePart,LPOLDPARAM op)
  {
  for (int j = 0 ; j < MANZSEGS ; j++) {
    if (fdsc[TablePart].VarID[j] != 0xFFFF) {
      LPVOID keyParam = rec->Get (fdsc[TablePart].VarID[j]);
      if (op->Param[TablePart][j] != NULL) 
        FreeGlobMem (op->Param[TablePart][j]) , op->Param[TablePart][j] = NULL ;
      if (keyParam != NULL) {
        op->Param[TablePart][j] = GetGlobMem (GetBlockSize (keyParam)) ;
        lmemcpy (op->Param[TablePart][j],keyParam,GetBlockSize (keyParam));
        }
      }
    }
  }

DLLExport LPOLDPARAM _export WINAPI DBRequest::SaveOldParams (LPDBRECORD rec)
  {
  LPOLDPARAM res = LPOLDPARAM (GetGlobMem (sizeof(*res)));
  for (int i = 0 ; i < CB_TABLEDEF ; i++) {
    if (fdsc[i].freq != NULL) SaveOldParams (rec,i,res);
    }
  return res;
  }

DLLExport void _export WINAPI DBRequest::CheckPrimKeySegs ()
  {
  }

// Alternative Namensvergabe fuer die Files zur Horizontalen Teilung von
// Tabellen
////////////////////////////////////////////////////////////////////////
struct FileTranslationTable {
  FileTranslationTable FAR *Next;
  LPSTR oldName;
  LPSTR newName;
  DWORD Id;
  };

struct FileTranslationTable FAR *ft;
DLLExport void _export WINAPI AddFileTranslation (DWORD Id,LPSTR oldName,LPSTR newName)
  {
  FileTranslationTable FAR *n = (FileTranslationTable FAR *) GetGlobMem (sizeof(*n));
  n->oldName = LPSTR (GetGlobMem (lstrlen (oldName) + 1)) ;
  lstrcpy (n->oldName,oldName);
  n->newName = LPSTR (GetGlobMem (lstrlen (newName) + 1)) ;
  lstrcpy (n->newName,newName);
  n->Id = Id ;
  n->Next = ft ;
  ft = n ;
  }

DLLExport void _export WINAPI RemoveFileTranslation (DWORD Id,LPSTR oldName)
  {
  FileTranslationTable FAR *p = NULL ;
  for ( FileTranslationTable FAR *n = ft ; n != NULL ; n = n->Next ) {
    if ((n->Id == Id) && (lstrcmp (n->oldName,oldName) == 0)) {
      if (p != NULL)
        p->Next = n->Next ;
      else
        ft = n->Next ;
      FreeGlobMem (n->oldName);
      FreeGlobMem (n->newName);
      FreeGlobMem (n);
      break ;
      }
    p = n ;
    }
  }

LPSTR GetAlternatName (DWORD Id,LPSTR Name)
  {
  for ( FileTranslationTable FAR *n = ft ; n != NULL ; n = n->Next ) {
    if ((n->Id == Id) && (lstrcmp(Name,n->oldName) == 0)) return n->newName;
    }
  return NULL ;
  }
