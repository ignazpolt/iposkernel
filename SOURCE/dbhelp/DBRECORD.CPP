///////////////////////////////////////////////////////////////////////
//  Implementierung der Klasse dbrecord
///////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/dbhelp/rev/dbrecord.cpv   1.98   07 Jun 2000 10:22:16   Wolfgang  $
// $Log:   P:/marille/clinicum/dbhelp/rev/dbrecord.cpv  $
// 
//    Rev 1.98   07 Jun 2000 10:22:16   Wolfgang
// 1.) ParseRecBuffer-Clear neu.
// 
//    Rev 1.97   26 Apr 2000 00:46:12   Hannes
// FreeElem: Aufloesen der NextSame Ketten
// 
//    Rev 1.96   15 Mar 2000 09:44:42   Martin
// MAXJOINRECLIST von 512 auf 4096 erhoeht
// 
//    Rev 1.95   18 Nov 1999 18:28:54   Hannes
// 
//    Rev 1.94   26 Jul 1999 22:16:38   Hannes
// 
//    Rev 1.93   25 Jun 1999 18:03:14   Hannes
// Fehlerkorrektur in ReplacePrimKey...
// 
//    Rev 1.92   07 May 1999 00:19:16   Hannes
// VarSize bei Strings und Oracle um 1 vergroessert
// 
//    Rev 1.91   16 Apr 1999 22:31:24   Hannes
// RecRoot - Speicherverwaltung umgebaut
// 
//    Rev 1.90   11 Mar 1999 18:18:08   Hannes
// CheckOwnerID um ErzContext erweitert...
// 
//    Rev 1.89   08 Mar 1999 19:50:38   Hannes
// ReplacePrimkey richtig gestellt
// 
//    Rev 1.88   17 Feb 1999 21:00:36   Hannes
// Verbesserungen an Moveconnection
// 
//    Rev 1.87   15 Feb 1999 21:43:20   Hannes
// Sortiersegmente auch in der 2. Tabelle
// 
//    Rev 1.86   11 Jan 1999 22:55:26   Hannes
// Kontextweitergabe, Loeschen der Record - Anhaengsel
// 
//    Rev 1.85   12 Nov 1998 14:05:42   Hannes
// DBRecord::Update: Blobs beruecksichtigen
// 
//    Rev 1.84   02 Nov 1998 19:30:26   Hannes
// Verbesserungen des Join - Handlings
// 
//    Rev 1.83   06 Aug 1998 09:27:12   Hannes
// Zuerst alten Record freigeben, dann DoAllJoins mit dem neuen
// 
//    Rev 1.82   16 May 1998 14:12:20   Martin
// SortParam ...
// 
//    Rev 1.81   07 May 1998 12:24:42   Hannes
// Verbesserung CalcPrimKey: Primaerschluessel als String -> Mit '\0' padden,
// damit auch segmentierte Schluessel funktionieren
// 
//    Rev 1.80   28 Apr 1998 18:20:30   Martin
// ParamType auch bei NULL setzen
// 
//    Rev 1.79   10 Feb 1998 18:28:28   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.78   10 Feb 1998 15:14:00   Hannes
// 
//    Rev 1.77   02 Feb 1998 20:34:44   Hannes
// MoveConnections: Auslassen der Listendatensaetze
// 
//    Rev 1.76   26 Jan 1998 20:02:06   Hannes
// 
//    Rev 1.75   30 Dec 1997 16:57:38   Martin
// WIN_ASSERT fuer Beschraenkung eines Records auf 64K in 32 Bit Version raus
// 
//    Rev 1.74   19 Nov 1997 18:45:42   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.73   04 Nov 1997 14:55:02   Hannes
// 
//    Rev 1.72   24 Oct 1997 08:38:06   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.71   20 Oct 1997 12:54:28   Martin
// DeleteRecRoot: Die Zyklischen Records nur im Fall von Positivem ReleaseRecord
// loeschen
// 
// 
//    Rev 1.70   10 Sep 1997 11:57:46   Guenther
// Update beim Neusetzten eines DBRecords
// 
//    Rev 1.69   21 Aug 1997 13:22:24   Hannes
// DoJoins bei ::SetRec im Fall orec != NULL
// 
//    Rev 1.68   18 Aug 1997 18:03:52   Martin
// einmal zuviel CheckOwnerID raus
// 
//    Rev 1.67   05 Aug 1997 22:42:26   Hannes
// 
//    Rev 1.66   30 Jul 1997 21:06:08   Hannes
// Platz fuer 0xFFFF bei KeySegs[] ...
// 
//    Rev 1.65   25 Jul 1997 14:42:48   Hannes
// 
//    Rev 1.64   24 Jul 1997 20:48:48   Hannes
// 
//    Rev 1.63   23 Jul 1997 08:01:32   Hannes
// 
//    Rev 1.62   18 Jul 1997 08:08:58   Hannes
// 
//    Rev 1.61   09 Jun 1997 13:10:16   Hannes
// 
//    Rev 1.60   27 May 1997 11:13:50   Hannes
// ReplacePrimKey
// 
//    Rev 1.59   13 Mar 1997 19:02:44   Hannes
// Blobs auch von lokalen Variablen loeschen
// 
//    Rev 1.58   28 Feb 1997 14:40:46   Hannes
// CheckAdministratedRecords raus
// 
//    Rev 1.57   19 Feb 1997 12:06:00   Hannes
// Scriptfunktionen -> Zyklische Liste mit Ableitungsdatensaetzen
// 
//    Rev 1.56   12 Dec 1996 12:19:22   HANNES
// Refresh -> Update der alten Schluesselsegmente
// 
//    Rev 1.55   03 Dec 1996 16:42:18   HANNES
// Update: IsStatic abgefragt
// 
//    Rev 1.54   26 Nov 1996 07:53:16   HANNES
// 
//    Rev 1.53   08 Nov 1996 13:27:38   HANNES
// Einbau des Replikators
// 
//    Rev 1.52   31 Oct 1996 16:08:52   HANNES
// Fehlerkorrekturen versch. Art
// 
//    Rev 1.51   30 Oct 1996 11:21:40   HANNES
// 
//    Rev 1.50   28 Oct 1996 08:41:22   HANNES
// OwnerID,DocumentID
// 
//    Rev 1.49   27 Sep 1996 14:46:52   MARTIN
// [128] -> [512], WIN_ASSERT...
// 
//    Rev 1.48   17 Jun 1996 15:46:04   HANNES
// Einbau von BLOBS
// 
//    Rev 1.46   05 Mar 1996 14:27:16   MARTIN
// CheckSortVals (hoffentlich) korrigiert
// 
//    Rev 1.45   04 Mar 1996 17:29:52   GERHOLD
// GetVarSize gekuerzt
// 
//    Rev 1.44   16 Feb 1996 13:11:12   MARTIN
// ka Ohnung
// 
//    Rev 1.43   04 Feb 1996 15:36:16   gerhold
// Teile von DBHELP in DDSMEM
// 
//    Rev 1.42   04 Feb 1996 14:25:04   HANNES
// IsValid
// 
//    Rev 1.41   04 Feb 1996 12:23:24   GERHOLD
// 
//    Rev 1.40   02 Feb 1996 10:42:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.39   31 Jan 1996 16:49:56   HANNES
// SetRec im Fall von mehreren NewRecs...
// Handling von OuterJoins
// 
//    Rev 1.38   25 Oct 1995 13:48:16   HANNES
// Aenderungen Hannes
// 
//    Rev 1.37   02 Oct 1995 18:37:46   HANNES
// Records < 1024 nicht mit GlobalAlloc, sondern mit GetGlobMem
// 
//    Rev 1.36   24 Sep 1995 19:03:38   MARTIN
// kj[i] auch loeschen, nicht nur setzen
// 
//    Rev 1.35   27 Aug 1995 13:02:24   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.34   24 Aug 1995 00:14:28   HANNES
// Debuggeroptimierung
// 
//    Rev 1.33   14 Aug 1995 08:24:18   HANNES
// FillIn Exportiert
// 
//    Rev 1.32   10 Aug 1995 09:22:46   HANNES
// JoinRecords ... alte Primaerschluessel aufbewahren
// 
//    Rev 1.31   14 Jul 1995 16:56:10   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.30   11 Jul 1995 12:44:36   HANNES
// 
//    Rev 1.29   02 Jul 1995 18:23:22   HANNES
// doUpdate bei neuLaden eines Datensatzes
// 
//    Rev 1.28   14 Jun 1995 13:10:56   HANNES
// PrimKey::operator = .... Freigeben der alten Daten
// 
//    Rev 1.27   09 Jun 1995 00:34:50   HANNES
// Hashtabelle ueber die Primaerschluessel
// Einzelene Elemente als statisch gekennzeichnet
// 
//    Rev 1.26   24 May 1995 17:13:22   HANNES
// Hashliste der dbrecords fuer FindSame
// 
//    Rev 1.25   15 May 1995 08:25:02   HANNES
// Speicherfreigabe in der Updateliste
// 
//    Rev 1.24   05 Apr 1995 17:10:36   unknown
// 
//    Rev 1.23   03 Apr 1995 15:10:36   HANNES
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "font.hpp"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#define MODULENUM 83
#include "winass.hpp"

#include "hash.hpp"
#include "communic.hpp"

#define NODDSDATA
#include "dds.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "scripthd.hpp"
#include "mdichild.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"

BOOL BlockIsActive;
// #define TEST
////////////////////////////////////////////////////////
//  Primaerschluessel - Verwaltung
////////////////////////////////////////////////////////
DLLExport BOOL _export FAR PASCAL PrimKey::operator == (PrimKey FAR &b)
  {
  return ((Data != NULL) && (b.Data != NULL) &&
          (GetBlockSize (Data) == GetBlockSize (b.Data)) &&
          (lmemcmp (Data,b.Data,GetBlockSize(Data)))) ;
  }

DLLExport void _export FAR PASCAL PrimKey::PushKeySeg (LPVOID SegData,int SegSize)
  {
  int oSize = ((Data != NULL) ? GetBlockSize(Data) : 0);
  int nSize = oSize + SegSize ;
  LPVOID nData = GetGlobMem (nSize);
  if (Data != NULL) {
    lmemcpy (nData,Data,GetBlockSize(Data));
    FreeGlobMem (Data);
    }
  lmemcpy (LPSTR(nData) + oSize,SegData,SegSize) ;
  Data = nData ;
  }

DLLExport BOOL _export FAR PASCAL PrimKey::IsNullKey ()
  {
  if (Data == NULL) return TRUE ;
  WORD i = 0 ;
  for (LPSTR h = LPSTR(Data) ; i < GetBlockSize (Data) ; i++ , h++)
    if (*h) return FALSE ;
  return TRUE ;
  }

DLLExport void _export FAR PASCAL PrimKey::SetKeyNull ()
  {
  if (Data != NULL)
    FreeGlobMem (Data);
  Data = NULL ;
  }

PrimKey &PrimKey::operator = (PrimKey FAR &b)
  {
  if (Data != NULL) FreeGlobMem (Data);
  if (b.Data != NULL) {
    Data = GetGlobMem (GetBlockSize(b.Data));
    lmemcpy (Data,b.Data,GetBlockSize(b.Data));
    }
  else
    Data = NULL ;

  return *this;
  }

// Implementierung der Klasse DBRecord
//////////////////////////////////////////////
void DBRecord::Initialize (LPTABLEDEF def)
  {
  Type = DBR_TYPE_FULL;
  tbdef[0] = def;
  GetTableAdmin()->GetTableDef (def->GetTableID(),def->GetVersion());
  AnzVars = tbdef[0]->GetAnzVars();
  DWORD vSize = DWORD(AnzVars) * DWORD(sizeof(VarElem));
  WIN_ASSERT (vSize < 0x0000FFFF);
  if (vSize < 1024) {
    vartbl = LPVARELEM (GetGlobMem (int(vSize)));
    }
  else {
    hGTbl = GlobalAlloc (GHND,vSize);
    vartbl = LPVARELEM (GlobalLock (hGTbl));
    }
  if (def->IsGlobalTable ()) {
    for (int i = 0 ; i < def->GetAnzVars(); i++) {
      LPVARDEF v = def->GetVarDef(i);
      if (v->Property != VPROP_DYNAMIC) {
        vartbl[i].Property |= VEP_STATIC ;
        }
      }
    }
  }


DLLExport _export FAR PASCAL DBRecord::DBRecord (WORD AnzV)
  {
  SetTableID(0,0);
  Type      = DBR_TYPE_FULL;
  AnzTables = 1;
  AnzVars   = AnzV;
  DWORD vSize = DWORD(AnzVars) * DWORD(sizeof(VarElem));
#ifndef WIN32
  WIN_ASSERT (vSize < 0x0000FFFF);
#endif
  if (vSize < 1024) {
    vartbl = LPVARELEM (GetGlobMem (int(vSize)));
    }
  else {
    hGTbl = GlobalAlloc (GHND,vSize);
    vartbl = LPVARELEM (GlobalLock (hGTbl));
    }
  }

DLLExport _export FAR PASCAL DBLocalRecord::DBLocalRecord (WORD AnzV,DWORD Id) : DBRecord (AnzV)
  {
  SetTableID(0,0);
  k.PushKeySeg (&Id,sizeof(Id));
  doUpdate = TRUE ;
  }

DLLExport _export FAR PASCAL DBHelpRecord::DBHelpRecord (WORD AnzV,DWORD Id) : DBLocalRecord (AnzV,Id)
  {
  SetTableID(0xFFFE,0);
  doUpdate = FALSE ;
  }

DLLExport _export FAR PASCAL DBRecord::DBRecord (LPTABLEDEF def)
  {
  WORD Id = def->GetTableID();
  WORD Version = def->GetVersion();
  Initialize (def);
  SetTableID(Id,Version);
  GetTableAdmin()->GetTableDef (Id,Version);
  AnzTables = 1;
  doUpdate = TRUE ;
  }

DLLExport _export FAR PASCAL DBRecord::DBRecord (LPDBREQUEST req)
  {
  if (req->AnzElems > 0) {
    // Redurzierter Ansatz
    Type      = DBR_TYPE_REDUCED;
    AnzTables = WORD(req->AnzTables);
    for (int i = 0 ; i < int (req->AnzTables) ; i++) {
      tbdef[i] = req->TableDef[i];
      GetTableAdmin()->GetTableDef (tbdef[i]->GetTableID(),tbdef[i]->GetVersion());
      if (i == 0) {
        // Sicherheitshalber noch einmal setzten, ~DBRecord gibt den freien Record frei
        GetTableAdmin()->GetTableDef (tbdef[i]->GetTableID(),tbdef[i]->GetVersion());
        }
      }
    AnzVars = WORD(req->AnzElems);
    DWORD vSize = DWORD(AnzVars) * DWORD(sizeof(VarElem));
    WIN_ASSERT (vSize < 0x0000FFFF);
    if (vSize < 1024) {
      vartbl = LPVARELEM (GetGlobMem (int(vSize)));
      }
    else {
      hGTbl = GlobalAlloc (GHND,vSize);
      vartbl = LPVARELEM (GlobalLock (hGTbl));
      }
    elem = LPREQELEM (GetGlobMem (AnzVars * sizeof(*elem)));
    lmemcpy (elem,req->elem,AnzVars * sizeof(*elem));
    }
  else {
    Initialize (req->TableDef[0]);
    GetTableAdmin()->GetTableDef (tbdef[0]->GetTableID(),tbdef[0]->GetVersion());
    AnzTables = 1;
    }
  SetTableID(req->GetTableID(),req->GetVersion());
  doUpdate = TRUE ;
  }

void VarElem::FreeMem()
  {
  // 1. Aus der NextSame Kette ausloesen
  //--------------------------------------------------
  if (NextSame != NULL) {
    for (LPVARELEM p = NextSame ; p->NextSame != this ; p = p->NextSame ) ;
    p->NextSame = NextSame ;
    if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
    NextSame = NULL;
    }

  // 2. Daten freigeben
  if (data != NULL) 
    FreeGlobMem (data);
  // 3. Updateliste
  for ( ; UpdateList != NULL ; ) {
    LPUPDATEELEM h = UpdateList->Next ;
    FreeGlobMem (UpdateList->c);
    if (UpdateList->UpdateExtraData)
      FreeGlobMem (UpdateList->UpdateExtraData);
    FreeGlobMem (UpdateList);
    UpdateList = h;
    }
  }

DLLExport _export FAR PASCAL DBRecord::~DBRecord ()
  {
  if (NextInCycl != NULL) {
    LPDBRECORD nc = NextInCycl ;
    for ( ; nc != this ; ) {
      LPDBRECORD next = nc->NextInCycl ;
      nc->NextInCycl = NULL;
      delete nc ;
      nc = next ;
      }
    }
  WIN_ASSERT (OwnerID == NULL) ;
  for (WORD i = 0 ; i < AnzVars ; i++) {
    BOOL isBlob = FALSE ;
    if ((elem != NULL) && (tbdef[elem[i].TableNumber]->GetVarDef(elem[i].VarID)->mType == VAR_BLOB)) 
      isBlob = TRUE ;
    if ((elem == NULL) &&
        ((GetTableID () != 0) &&
         (GetTableID () != 0xFFFE) &&
         (tbdef[0]->GetVarDef(i)->mType == VAR_BLOB))) isBlob = TRUE ;
    if (isBlob) {
      LPBLOBDESC bd = LPBLOBDESC (vartbl[i].data) ;
      if (bd != NULL)
        bd->FreeHandle ();
      }
#ifdef DEBUG
    WIN_ASSERT (vartbl[i].NextSame == NULL) ;
#endif
    vartbl[i].FreeMem () ;
    }
  if ((GetTableID () != 0) && (GetTableID () != 0xFFFE)) {
    GetTableAdmin()->FreeTable (tbdef[0]->GetTableID(),tbdef[0]->GetVersion());
    }
  if (hGTbl) {
    GlobalUnlock (hGTbl);
    GlobalFree (hGTbl);
    }
  else {
    FreeGlobMem (vartbl);
    }
  if (elem != NULL)
    FreeGlobMem (elem);
  for (i = 0 ; i < CB_TABLEDEF ; i++) {
    if (tbdef[i] != NULL)
      GetTableAdmin()->FreeTable (tbdef[i]->GetTableID(),tbdef[i]->GetVersion());
    if (kj[i] != NULL) delete kj[i] ;
    }
#ifdef TEST
  TableID = 0;
  CheckAdministratiedRecords (0,0);
#endif
  }

DLLExport void _export FAR PASCAL DBRecord::Set (WORD VarID,LPVOID data,WORD dataSize,LPVOID MyCmd,BOOL doUpdate,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  LPVARELEM v = &vartbl[VarID];
  v->Set (data,dataSize);
  if ((doUpdate) && (!v->isStatic())) v->Update(MyCmd,this,ExtraType,UpdateExtraData,ExtraDataSize);
  if (v->NextSame != NULL) {
    for (LPVARELEM n = v->NextSame ; n != v ; n = n->NextSame) {
      n->Set (data,dataSize) ;
      if ((doUpdate) && (!v->isStatic()) && (!n->isStatic())) n->Update(MyCmd,NULL,ExtraType,UpdateExtraData,ExtraDataSize);
      }
    }
  }

DLLExport void _export FAR PASCAL DBRecord::Initialize (WORD VarID,LPVOID data,WORD dataSize)
  {
  LPVARELEM v = &vartbl[VarID];
  v->Initialize (data,dataSize);
  }

DLLExport void _export FAR PASCAL DBRecord::Del (WORD VarID,LPVOID MyCmd,BOOL doUpdate,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  LPVARELEM v = &vartbl[VarID];
  v->Del ();
  if ((doUpdate) && (!v->isStatic())) v->Update(MyCmd,this,ExtraType,UpdateExtraData,ExtraDataSize);
  if (v->NextSame != NULL) {
    for (LPVARELEM n = v->NextSame ; n != v ; n = n->NextSame) {
      n->Del () ;
      if ((doUpdate) && (!v->isStatic()) && (!n->isStatic())) n->Update(MyCmd,NULL,ExtraType,UpdateExtraData,ExtraDataSize);
      }
    }
  }

DLLExport void _export FAR PASCAL DBRecord::UseBy (DWORD Id)
  {
  WORD oSize = GetBlockSize (OwnerID) ;
  LPDWORD n = LPDWORD (GetGlobMem (oSize+sizeof(DWORD)));
  n[0] = Id;
  if (OwnerID != NULL)
    lmemcpy (&n[1],OwnerID,oSize) , FreeGlobMem (OwnerID);
  OwnerID = n;
  }

DLLExport BOOL _export FAR PASCAL DBRecord::IsUsedBy (DWORD Id)
  {
  WORD dimension = GetBlockSize (OwnerID) / sizeof(DWORD) ;
  for (WORD i = 0 ; i < dimension ; i++)
    if (OwnerID[i] == Id) return TRUE ;
  return FALSE ;
  }

DLLExport void _export FAR PASCAL DBRecord::ReleaseFrom (DWORD Id)
  {
  if (IsUsedBy (Id)) {
    WORD dimension = GetBlockSize (OwnerID) / sizeof(DWORD) ;
    LPDWORD n ;
    if (dimension > 1) {
      n = LPDWORD(GetGlobMem (sizeof(*n) * (dimension - 1))) ;
      WORD j = 0 ;
      for (WORD i = 0 ; i < dimension ; i++) {
        if (OwnerID[i] != Id)
          n[j++] = OwnerID[i] ;
        }
      }
    else
      n = NULL;
    FreeGlobMem (OwnerID);
    OwnerID = n;
    }
  }

void DBRecord::Update(DBRecord FAR *n)
  {
  DBWIN_ASSERT(AnzVars == n->AnzVars);
  DBWIN_ASSERT((GetPrimKey()->Data == NULL) || (*GetPrimKey() == *n->GetPrimKey()));
  for (WORD i = 0 ; i < AnzVars ; i++) {
    LPVOID dold = Get(i);
    LPVOID dnew = n->Get(i);
    BOOL isBlob = FALSE ;
    if ((elem == NULL) &&
        ((GetTableID () != 0) &&
         (GetTableID () != 0xFFFE) &&
         (tbdef[0]->GetVarDef(i)->mType == VAR_BLOB))) isBlob = TRUE ;
    if ((dold != NULL) && (dnew != NULL)) {
      if ((GetBlockSize (dold) != GetBlockSize(dnew)) || (!lmemcmp(dold,dnew,GetBlockSize(dold)))) {
        if ((isBlob) && (((BlobDesc FAR *) dold)->hGmem != NULL)) GlobalFree (((BlobDesc FAR *)dold)->hGmem);
        Set (i,dnew,GetBlockSize(dnew),NULL,TRUE);
        }
      }
    else {
      if ((dold != NULL) && (dnew == NULL)) {
        if ((isBlob) && (((BlobDesc FAR *) dold)->hGmem != NULL)) GlobalFree (((BlobDesc FAR *)dold)->hGmem);
        Del (i,NULL,TRUE);
        }
      else if (dnew != NULL)
        Set (i,dnew,GetBlockSize(dnew),NULL,TRUE);
      }
    if (isBlob)
      n->Del (i,NULL,FALSE);
    }
  }

DLLExport BOOL _export FAR PASCAL DBRecord::IsUpdateDone ()
  {
  for (WORD i = 0 ; i < AnzVars ; i++)
    if (vartbl[i].IsUpdateDone()) return TRUE ;
  return FALSE ;
  }

DLLExport void _export FAR PASCAL DBRecord::ResetUpdateFlags ()
  {
  for (WORD i = 0 ; i < AnzVars ; i++)
    vartbl[i].ResetUpdateFlag();
  }

DLLExport void _export FAR PASCAL DBRecord::Update(DWORD DocumentID)
  {
  for (WORD i = 0 ; i < AnzVars ; i++) {
    LPVARELEM f = &vartbl[i];
    for ( LPVARELEM h = f ; ; ) {
      h->UpdateMe (DocumentID);
      LPVARELEM Next = h->NextSame ;
      if (Next == NULL) break ;
      if (Next == f) break ;
      h = Next ;
      }
    }
  }

DWORD CheckOwnerID (DWORD updOwnerID,DWORD actOwnerID)
  {
  if (actOwnerID == NULL) return updOwnerID ;
  if (updOwnerID == NULL) return updOwnerID ;
  if (updOwnerID == actOwnerID) return updOwnerID ;
  
  mdiChild FAR *h = ((mdiChild FAR *)updOwnerID) ;
  for ( ; ; ) {
    h = h->outContext ;
    if (h == NULL) break ;
    if (DWORD(h) == actOwnerID) return updOwnerID ;
    }
  h = ((mdiChild FAR *)updOwnerID) ;
  for ( ; ; ) {
    h = h->erzContext ;
    if (h == NULL) break ;
    if (DWORD(h) == actOwnerID) return updOwnerID ;
    }
  return NULL ;
  }

void DBRecord::MoveConnections(DBRecord FAR *n,DWORD DocumentID,DWORD OwnerID)
  {
  // Die Connections werden von n auf this uebernommen
  //--------------------------------------------------
  DBWIN_ASSERT(AnzVars == n->AnzVars);
  for (WORD i = 0 ; i < AnzVars ; i++) {
    vartbl[i].MoveConnections (&n->vartbl[i],DocumentID,OwnerID);
    }
  }
DLLExport void _export FAR PASCAL DBRecord::SetConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,LPCMDCOUNT c,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  if (doUpdate)
    vartbl[VarID].SetConnection(OwnerID,DocID,cmd,c,ExtraType,UpdateExtraData,ExtraDataSize) ; 
  }
DLLExport void _export FAR PASCAL DBRecord::ClearConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  if (doUpdate)
    vartbl[VarID].ClearConnection(OwnerID,DocID,cmd,ExtraType,UpdateExtraData,ExtraDataSize) ; 
  }
DLLExport void _export FAR PASCAL DBHelpRecord::SetConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,LPCMDCOUNT c,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  }
DLLExport void _export FAR PASCAL DBHelpRecord::ClearConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  }
DLLExport void _export FAR PASCAL DBRecord::GetOutTxt (LPSTR res,WORD VarNr)
  {
  WORD VarID;
  LPTABLEDEF tb = GetTableDef (VarNr,&VarID);
  LPVARDEF v = tb->GetVarDef(VarID);
  FormatOutTxt (res,Get(VarNr),v->mType);
  }
DLLExport _export FAR PASCAL DBConstRecord::DBConstRecord (WORD AnzVars,DWORD DocID,GLOBALHANDLE hGConstMem) :
        DBHelpRecord (AnzVars,DocID)
  {
  LPSTR actptr = LPSTR(GlobalLock (hGConstMem)) + 2 * sizeof(WORD) + 2 * sizeof(WORD);
  for (WORD i = 0 ; i < AnzVars ; i++) {
    if (GetBlockSize(actptr) > 0)
      vartbl[i].data = actptr;
    else
      vartbl[i].data = NULL;
    actptr += GetBlockSize(actptr) + 2 * sizeof(WORD);
    }
  GlobalUnlock (hGConstMem);
  }
DLLExport _export FAR PASCAL DBConstRecord::~DBConstRecord ()
  {
  for (WORD i = 0 ; i < AnzVars ; i++)
    vartbl[i].data = NULL ;
  }
////////////////////////////////////////////////////////
// Verbinden der Doppelt vorkommenden Datenelemente
////////////////////////////////////////////////////////
hash FAR *rHash,FAR *pHash,FAR *jHash;
class FAR Table_Key {
 public :
  char buffer[512];
  int Size;
  Table_Key (WORD TableID,WORD Version,LPPRIMKEY k)
    {
     ((WORD FAR *) buffer)[0] = TableID;
     ((WORD FAR *) buffer)[1] = Version;
    lmemcpy (buffer + 2 * sizeof(WORD),k->Data,Size = GetBlockSize(k->Data));
    Size += 2 * sizeof(WORD);
    }
  };
void SetRecordForJoins (LPJOINRECLIST nw,WORD TableID,WORD Version,LPPRIMKEY kext)
  {
  Table_Key kt(TableID,Version,kext);
  LPJOINRECLIST FAR *oldList = (LPJOINRECLIST FAR *) jHash->GetDatav (kt.buffer,kt.Size);
  if (oldList != NULL) {
    LPJOINRECLIST n = LPJOINRECLIST (GetGlobMem (GetBlockSize(*oldList) + sizeof(*nw)));
    lmemcpy (n + 1,*oldList,GetBlockSize(*oldList));
    *n = *nw ;
    FreeGlobMem (*oldList);
    *oldList = n ;
    }
  else {
    LPJOINRECLIST n = LPJOINRECLIST (GetGlobMem (sizeof(*nw)));
    *n = *nw ;
    jHash->SetDatav (kt.buffer,&n,sizeof(n),kt.Size);
    }
  }
void DelRecordForJoins (LPJOINRECLIST nw,WORD TableID,WORD Version,LPPRIMKEY kext)
  {
  Table_Key kt(TableID,Version,kext);
  LPJOINRECLIST FAR *oldList = (LPJOINRECLIST FAR *) jHash->GetDatav (kt.buffer,kt.Size);
  if (oldList != NULL) {
    int Anz = GetBlockSize(*oldList) / sizeof(**oldList) ;
    if (Anz == 1) {
      FreeGlobMem (*oldList);
      jHash->DelDatav (kt.buffer,kt.Size);
      }
    else {
      LPJOINRECLIST n = LPJOINRECLIST (GetGlobMem (GetBlockSize(*oldList) - sizeof(*nw)));
      int j = 0 ;
      BOOL found = FALSE;
      for (int i = 0 ; i < Anz ; i++) {
        if (!lmemcmp ((*oldList) + i,nw,sizeof(*nw)))
          n[j++] = (*oldList)[i];
        else
          found = TRUE;
        }
      WIN_ASSERT(found);
      FreeGlobMem (*oldList);
      *oldList = n ;
      }
    }
  }
void DBRecord::UseRecordForJoins ()
  {
  for (WORD i = 0 ; i < AnzTables ; i++) {
    // Das Element koennte vorkommen
    PrimKey k;
    if (i == 0) k = *GetPrimKey();
    else        CalcPrimKey (i,&k);
    if (!k.IsNullKey()) {
      JoinRecList j;
      j.rec = this;
      j.TableInd = i;
      SetRecordForJoins (&j,tbdef[i]->GetTableID(),tbdef[i]->GetVersion(),&k);
      if (kj[i] == NULL)
        kj[i] = new PrimKey ();
      *(kj[i]) = k ;
      }
    else {
      delete kj[i];
      kj[i] = NULL;
      }
    }
  }
void DBRecord::FreeRecordForJoins ()
  {
  for (WORD i = 0 ; i < AnzTables ; i++) {
    // Das Element koennte vorkommen
    if ((kj[i] != NULL) && (!kj[i]->IsNullKey())) {
      JoinRecList j;
      j.rec = this;
      j.TableInd = i;
      DelRecordForJoins (&j,tbdef[i]->GetTableID(),tbdef[i]->GetVersion(),kj[i]);
      }
    }
  }

BOOL Cmp (LPVOID d1,LPVOID d2)
  {
  if ((d1 == NULL) && (d2 == NULL)) return TRUE ;
  return ((d1 != NULL) && (d2 != NULL) && (GetBlockSize(d1) == GetBlockSize(d2)) &&
            lmemcmp (d1,d2,GetBlockSize(d1))) ;
  }
  
DLLExport void _export FAR PASCAL VarElem::FillIn (LPVARELEM n)
  {
  if (NextSame == NULL) {
    if (n->NextSame == NULL) {
      n->NextSame = this;
      NextSame = n;
      if (!Cmp (data,n->data)) {
        if (n->data != NULL)
          Set (n->data,GetBlockSize(n->data));
        else
          Del ();
        Update (NULL,NULL,0,NULL,0);
        }
      }
    else {
      for (LPVARELEM h = n->NextSame ; h->NextSame != n ; h = h->NextSame) ;
      h->NextSame = this ;
      NextSame = n;
      if (!Cmp (data,n->data)) {
        if (n->data != NULL)
          Set (n->data,GetBlockSize(n->data));
        else
          Del ();
        Update (NULL,NULL,0,NULL,0);
        }
      }
    }
  else {
    for (LPVARELEM h = NextSame ; h != this ; h = h->NextSame) {
      if (h == n) break ; // n ist schon drinnen
      }
    if (h == this) {
      // Noch nicht gefunden -> Einfuegen
      if (n->NextSame == NULL) {
        n->NextSame = NextSame;
        NextSame = n;
        }
      else {
        for (LPVARELEM h = n->NextSame ; h->NextSame != n ; h = h->NextSame) ;
        h->NextSame = NextSame ;
        NextSame = n;
        }
      if (!Cmp (data,n->data)) {
        if (n->data != NULL)
          Set (n->data,GetBlockSize(n->data));
        else
          Del ();
        Update (NULL,NULL,0,NULL,0);
        }
      }
    }
  }

int DBRecord::GetVarSize (WORD VarNr)
  {
  WORD VarID;
  LPTABLEDEF tb = GetTableDef (VarNr,&VarID);
  LPVARDEF v = tb->GetVarDef(VarID);
  if (v->mType == VAR_STR) {
    if (lstrcmp ((GetDLLAdmin()->GetDLLEntry (GetTransactionDLL()))->_Fname,"ddsora.dll") == 0)
      return v->VarSize + 1;
    else
      return v->VarSize + 1;
    }
  else
    return v->VarSize ;
  }

BOOL SameExtraData(int aType,LPVOID aData,int nType,LPVOID nData,int nSize)
  {
  if ((aData == NULL) && (nData == NULL)) return TRUE ;
  if (aData == NULL)                      return FALSE ;
  if (nData == NULL)                      return FALSE ;
  if (aType != nType)                     return FALSE ;
  if (int(GetBlockSize (aData)) != nSize) return FALSE;
  return lmemcmp (aData,nData,nSize);
  }

DLLExport void _export FAR PASCAL VarElem::SetConnection (DWORD OwnerID,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT c,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  if (isStatic ()) return ;
  LPUPDATEELEM p = NULL;
  // Untersuchung, ob nicht doppelt
#ifdef CHECKDOUBLE
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; p = h , h = h->Next) {
    if ((h->DocumentID == DocumentID) && 
        (h->Cmd        == Cmd) &&
        (SameExtraData(h->UpdateExtraType,h->UpdateExtraData,
                       ExtraType,UpdateExtraData,ExtraDataSize))) break ;
    }
  // Einfuegen
  if (h == NULL) {
#else
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; p = h , h = h->Next) ;
#endif
    LPUPDATEELEM n = LPUPDATEELEM(GetGlobMem(sizeof(*n)));
    n->OwnerID    = OwnerID;
    n->DocumentID = DocumentID;
    n->Cmd        = Cmd;
    n->c          = c->Copy();
    if (UpdateExtraData != NULL) {
      n->UpdateExtraType = ExtraType;
      n->UpdateExtraData = GetGlobMem (ExtraDataSize);
      lmemcpy (n->UpdateExtraData,UpdateExtraData,ExtraDataSize);
      }
    n->Next       = NULL;
    if (p != NULL) p->Next = n;
    else           UpdateList = n;
#ifdef CHECKDOUBLE
    }
#endif
  }

BOOL doMove (
    mdiChild *cc,         // mdiChild, mit dem die Connections gesetzt worden sind
    mdiChild *c,          // mdiChild, das einen SetRec durchfuehrt
    DWORD cOwnerID,       // OwnerID vom Setconnection
    DWORD OwnerID,        // OwnerID vom SetRec
    WORD cTyp             // Typ der Connection
    )
  {
  if (OwnerID == 0L) return TRUE ;
  if (c == NULL) return TRUE ;
  if ((cc != NULL) && (cc->GetErzContext () == c) && (cTyp != EXTRATYPE_LIST)) {
    // Nur dann die Connections verschieben, wenn es sich um
    // ein Subaufruf handelt (cc != c) oder wenn die OwnerID ubereinstimmt
    // (Es handelt sich auch wirklich um die gleiche Tabelle...)
    if (cc != c) return TRUE ;
    if (cOwnerID == OwnerID) return TRUE ;
    }
  return FALSE ;
  }


void VarElem::MoveConnections(LPVARELEM o,DWORD DocumentID,DWORD OwnerID)
  {
  LPUPDATEELEM op = NULL;
  // Suchen des Endes der Aktuellen Liste
  for (LPUPDATEELEM p = UpdateList ; ((p != NULL) && (p->Next != NULL)) ; p = p->Next);
  LPUPDATEELEM last_old = p;
  for (LPUPDATEELEM oh = o->UpdateList ; oh != NULL ; ) {
#ifdef UEBERLEGT
    if (CheckOwnerID (oh->DocumentID,OwnerID))
#endif
    // if (((oh->DocumentID != NULL) && (((mdiChild *) oh->DocumentID)->GetErzContext()->DocumentID() == OwnerID) && (oh->UpdateExtraType != EXTRATYPE_LIST)) ||
         // (OwnerID == 0L)) {
    // if (((oh->OwnerID == OwnerID) && (oh->UpdateExtraType != EXTRATYPE_LIST)) ||
         // (OwnerID == 0L)) {
    if (doMove ((mdiChild *) oh->DocumentID,
                (mdiChild *) DocumentID,
                oh->OwnerID,
                OwnerID,
                oh->UpdateExtraType)) {
      // oh muss von der alten in die neue (== this) verschoben werden
      if (op != NULL) op->Next      = oh->Next;
      else            o->UpdateList = oh->Next;
      if (p != NULL)  p->Next       = oh;
      else            UpdateList    = oh;
      oh->Next = NULL;
      p = oh;
      oh = (op != NULL) ? op->Next : o->UpdateList;
      }
    else {
      op = oh;
      oh = op->Next;
      }
    }
  }

void VarElem::ClearConnection (DWORD OwnerID,DWORD DocumentID,LPVOID Cmd,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  {
  LPUPDATEELEM p = NULL;
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; ) {
    if ((h->Cmd        == Cmd) &&
        (h->DocumentID == DocumentID) && 
        (h->OwnerID    == OwnerID) &&
        (SameExtraData(h->UpdateExtraType,h->UpdateExtraData,
                       ExtraType,UpdateExtraData,ExtraDataSize))) {
      LPUPDATEELEM n = h->Next;
      if (p != NULL) p->Next    = n;
      else           UpdateList = n;
      if (h->UpdateExtraData != NULL) {
        // In diesem Fall muss das Ding sich selber um die Reinhaltung der 
        // CmdFifo kuemmern, da im Interpretemode dies nicht moeglich ist ...
        GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID,Cmd,h->UpdateExtraType,h->UpdateExtraData) ;
        FreeGlobMem (h->UpdateExtraData);
        }
      FreeGlobMem (h->c);
      FreeGlobMem (h);
      h = n;
#ifndef CHECKDOUBLE
      break ;
#endif
      }
    else
      p = h , h = h->Next;
    }
  }

void VarElem::DelConnections (DWORD OwnerID)
  {
  LPUPDATEELEM p = NULL ;
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; ) {
    if (h->DocumentID == OwnerID) {
      LPUPDATEELEM n = h->Next;
      if (p != NULL) p->Next    = n;
      else           UpdateList = n;
      FreeGlobMem (h->c);
      if (h->UpdateExtraData != NULL) FreeGlobMem (h->UpdateExtraData);
      FreeGlobMem (h);
      h = n;
      }
    else
      p = h , h = h->Next;
    }
  }

BOOL SameTypes (LPVOID rec,LPVOID eData)
  {
  WORD rtoupdate = LPDBRECORD (rec)->GetTableID();
  LPCONNEXTRAINFO eiatwrite = LPCONNEXTRAINFO(eData);
  for (int i = 0 ; i < eiatwrite->AnzTables () ; i++) {
    if (rtoupdate == eiatwrite->i.t[i].r->GetTableID()) return TRUE ;
    }
  return FALSE ;
  }

BOOL UpdateElem::CheckExtaType (int Type,LPVOID ExtraData,int DataSize,LPVOID recData)
  {
  return TRUE ;
  }

DLLExport void _export FAR PASCAL VarElem::Update(LPVOID MyCmd,LPVOID recData,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize)
  { 
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; h = h->Next) {
    if (h->CheckExtaType (ExtraType,UpdateExtraData,ExtraDataSize,recData)) {
      GetAsync_cmdfifo()->PutCommandFifo (h->DocumentID,MODE_UPDATE,h->Cmd,
                                          MyCmd,this,h->c,h->UpdateExtraType,h->UpdateExtraData,GetBlockSize(h->UpdateExtraData)
                                          );
      }
    }
  }

void VarElem::UpdateMe(DWORD OwnerID)
  { 
  for (LPUPDATEELEM h = UpdateList ; h != NULL ; h = h->Next) {
    if (CheckOwnerID (h->DocumentID,OwnerID)) {
      mdiChild *x = (mdiChild *) h->DocumentID;
      GetAsync_cmdfifo()->PutCommandFifo (h->DocumentID,MODE_UPDATE,h->Cmd,
                                          NULL,this,h->c,h->UpdateExtraType,h->UpdateExtraData,GetBlockSize(h->UpdateExtraData)
                                         );
      }
    }
  }

void DBRecord::DelConnections (DWORD OwnerID)
  {
  for (WORD i = 0 ; i < AnzVars ; i++)
    vartbl[i].DelConnections (OwnerID);
  }

void DBRecord::FillIn (LPVARELEM v,int TableNr,WORD VarID)
  {
  if (!doUpdate) return ;
  if (elem == NULL) {
    // es handelt sich um eine Volle Tabelle
    if (tbdef[0]->GetVarDef(VarID)->mType != VAR_BLOB)
      vartbl[VarID].FillIn (v);
    }
  else {
    // es handelt sich um eine reduzierte Tabelle
    for (WORD i = 0 ; i < AnzVars ; i++) {
      if ((elem[i].TableNumber == TableNr) && (elem[i].VarID == VarID)) {
        if (tbdef[TableNr]->GetVarDef(VarID)->mType != VAR_BLOB)
          vartbl[i].FillIn (v);
        break ;
        }
      }
    }
  }

#define MAXJOINRECLISTS 4096
// Die Zyklischen Listen von gleichen Elementen in verschiedenen Tabellen
// herstellen
//////////////////////////////////////////////////////////////////////////
void DBRecord::DoAllJoins ()
  {
  if (!doUpdate) return ;
  JoinRecList lt[MAXJOINRECLISTS];
  // Suchen aller Teiltabellen, die mit den aktuellen Teiltabellen 
  // uebereinstimmen
  if (elem == NULL) {
    // Eine Volle Tabelle
    WORD j = 0;
    j = GetDBRecordAdmin()->GetSameRecords (this,GetTableID(),GetVersion(),GetPrimKey(),lt);
    // Und jetzt alle Variablen untereinander verbinden
    for (WORD l = 0 ; l < j ; l++) {
      for (WORD m = 0 ; m < AnzVars ; m++) {
        lt[l].rec->FillIn (&vartbl[m],lt[l].TableInd,m);
        }
      }
    }
  else {
    // Teiltabellen -> Untersuchung aller Teiltabellen
    PrimKey pk;
    for (WORD i = 0 ; i < AnzTables ; i++) {
      if (tbdef[i]->IsGlobalTable ()) continue ;    // Sicherheitshalber nicht probieren...
      if (i == 0) pk = *GetPrimKey();
      else        CalcPrimKey (i,&pk);
      if (!pk.IsNullKey()) {
        WORD j = GetDBRecordAdmin()->GetSameRecords (this,tbdef[i]->GetTableID(),tbdef[i]->GetVersion(),&pk,lt);
        // Jetzt noch die Verkettung herstellen
        for (WORD l = 0 ; l < j ; l++) {
          for (WORD m = 0 ; m < AnzVars ; m++) {
            if (WORD(elem[m].TableNumber) != i) continue;
            lt[l].rec->FillIn (&vartbl[m],lt[l].TableInd,elem[m].VarID);
            }
          }
        }
      }
    }
  }

DLLExport void _export FAR PASCAL DBRecord::DelJoins (WORD Tbnr)
  {
  if (!doUpdate) return ;
  // Alte Joins loeschen
  for (WORD i = 0 ; i < AnzVars ; i++) {
    if (WORD(elem[i].TableNumber) == Tbnr) {
      LPVARELEM v = &vartbl[i];
      if (v->NextSame != NULL) {
        for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
        p->NextSame = v->NextSame ;
        if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
        v->NextSame = NULL;
        }
      }
    }
  }

DLLExport void _export FAR PASCAL DBRecord::NewJoins (WORD Tbnr)
  {
  if (!doUpdate) return ;
  JoinRecList lt[MAXJOINRECLISTS];
  // Suchen aller Teiltabellen, die mit den aktuellen Teiltabellen 
  // uebereinstimmen
  PrimKey pk;
  CalcPrimKey (Tbnr,&pk);
  if (!pk.IsNullKey()) {
    WORD j = GetDBRecordAdmin()->GetSameRecords (this,tbdef[Tbnr]->GetTableID(),tbdef[Tbnr]->GetVersion(),&pk,lt);
    // Jetzt noch die Verkettung herstellen
    for (WORD l = 0 ; l < j ; l++) {
      for (WORD m = 0 ; m < AnzVars ; m++) {
        if (WORD(elem[m].TableNumber) != Tbnr) continue;
        lt[l].rec->FillIn (&vartbl[m],lt[l].TableInd,elem[m].VarID);
        }
      }
    }
  }

// Die Zyklische Liste wieder aufloesen
//////////////////////////////////////////
void Ausloesen (LPVARELEM v,LPVARELEM FAR &p)
  {
  if (v->NextSame) {
    for (p = v->NextSame ; (p->NextSame != v) ; p = p->NextSame) ;
    p->NextSame = v->NextSame ;
    if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
    v->NextSame = NULL;
    }
  else
    p = NULL;
  }

void DBRecord::FreeJoins()
  {
  if (!doUpdate) return ;
  for (WORD i = 0 ; i < AnzVars ; i++) {
    LPVARELEM v = &vartbl[i];
    if (v->NextSame != NULL) {
      LPVARELEM p;
      Ausloesen (v,p);
      // Jetzt ist v alleine, jetzt muss alles wieder zurueckgeholt werden, was
      // eine Erzeugernummer hat
      for ( LPVARELEM pold = p ; ; ) {
        if (p->Erzeuger) {
          LPVARELEM exp = p;
          Ausloesen (exp,p);
          if (v->NextSame) {
            exp->NextSame = v->NextSame ;
            v->NextSame = exp ;
            }
          else {
            exp->NextSame = v;
            v->NextSame = exp;
            }
          if ((exp == pold) && (p)) {
            pold = p;   // pold muss neu gesetzt werden, 
                        // und es muss weitergemacht werden
            continue ;
            }
          }
        else
          p = p->NextSame ;
        if ((!p) || (p == pold)) {
          break ;
          }
        }
      }
    }
  }

void DBRecord::FreeAllJoins()
  {
  if (!doUpdate) return ;
  for (WORD i = 0 ; i < AnzVars ; i++) {
    LPVARELEM v = &vartbl[i];
    if (v->NextSame != NULL) {
      for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
      p->NextSame = v->NextSame ;
      if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
      v->NextSame = NULL;
      }
    }
  }

void DBRecord::FreeJoins(DWORD eNummer)
  {
  if (!doUpdate) return ;
  for (WORD i = 0 ; i < AnzVars ; i++) {
    LPVARELEM v = &vartbl[i];
    if (v->NextSame != NULL) {
      LPVARELEM NormaleJoins = NULL ;
      LPVARELEM prev = v ;
      LPVARELEM LetzterNormale = NULL;
      for (LPVARELEM h = v->NextSame ; ; ) {
        LPVARELEM Next = h->NextSame ;
        if ((!h->isParam()) && (eNummer == h->Erzeuger)) {
          prev->NextSame = h->NextSame ;
          if (NormaleJoins == NULL) {
            NormaleJoins = h ;
            h->NextSame = h ;   // Zylkus, der leer ist
            }
          else {
            LetzterNormale->NextSame = h;
            h->NextSame = NormaleJoins;
            }
          LetzterNormale = h ;
          }
        else
          prev = h ;
        h = Next ;
        if (h == v) break;
        }
      if ((NormaleJoins != NULL) && (NormaleJoins->NextSame == NormaleJoins))
        NormaleJoins->NextSame = NULL;
      if (v->NextSame == v)
        v->NextSame = NULL;
      }
    }
  }

// Verwaltung der Klasse RecBuffer
////////////////////////////////////
DLLExport void _export FAR PASCAL RecBuffer::AddLine (WORD AnzTables,WORD position)
  {
  WIN_ASSERT ((position == ADDLINEPOS_START) || 
              (position == ADDLINEPOS_END  ));
  RecBufferLine FAR *h = (RecBufferLine FAR *) 
          GetGlobMem (sizeof(*h) + (AnzTables - 1) * sizeof(LPDBRECORD));
  if (first == NULL)
    first = h;
  else {
    if (position == ADDLINEPOS_END) {
      for (RecBufferLine FAR *x = first ; x->Next != NULL ; x = x->Next) ;
      x->Next = h;
      }
    else {
      h->Next = first ;
      first = h;
      }
    }
  act = h;
  }

DLLExport void _export FAR PASCAL RecBuffer::Clear ()
  {
  for ( ; first != NULL ; ) {
    for (int i = 0 ; i < ANZRECSPERLINE ; i++)
      if (first->rec[i] != NULL) delete first->rec[i];
    RecBufferLine FAR *n = first->Next;
    FreeGlobMem (first);
    first = n;
    }
  }

DLLExport void _export FAR PASCAL ParseRecBuffer::Clear ()
  {
  RecBuffer::Clear();
  if (errorMsg != NULL)
    FreeGlobMem (errorMsg);
  errorMsg = NULL;
  if (parseCmd != NULL)
    FreeGlobMem (parseCmd);
  parseCmd = NULL;
  }

/////////////////////////////////////////////////////////////////////////
// Implementierung der Klasse DBRecordAdmin
/////////////////////////////////////////////////////////////////////////
static DBRecordAdmin dra;
DLLExport LPDBRECORDADMIN _export FAR PASCAL GetDBRecordAdmin()
  {
  return &dra;
  }

// Suchen eines Records anhand des Primaerschluessels und des TabellenIDs
DLLExport LPDBRECORD _export FAR PASCAL DBRecordAdmin::Find (LPPRIMKEY k,WORD TableID,WORD Version)
  {
  if ((k != NULL) && (k->Data != NULL)) {
    Table_Key kt(TableID,Version,k);
    LPGRECLIST FAR *lrl = (LPGRECLIST FAR *) pHash->GetDatav (kt.buffer,kt.Size);
    return (lrl != NULL) ? (*lrl)->rec : NULL ;
    }
  return NULL;
  }

BOOL DBRecordAdmin::FindSame (LPDBRECORD r)
  {
  return (rHash->GetData (LONG (r)) != NULL) ;
  }

// Neuen Record in die Liste haengen
void DBRecordAdmin::Add (LPDBRECORD r)
  {
  WIN_ASSERT (rHash->GetData (LONG(r)) == NULL);
  LPGRECLIST n = LPGRECLIST (GetGlobMem (sizeof(*n)));
  n->rec   = r ;
  n->Next  = rl;
  if (n->Next != NULL)
    n->Next->Prev = n;
  rl = n;
  rHash->SetData (LONG (r),&rl,sizeof(rl));

  LPPRIMKEY k = r->GetPrimKey();
  if ((k != NULL) && (k->Data != NULL)) {
    Table_Key kt(r->GetTableID(),r->GetVersion(),k);
    pHash->SetDatav (kt.buffer,&rl,sizeof(rl),kt.Size);
    }
  r->UseRecordForJoins ();
  }

DLLExport void _export FAR PASCAL ReplacePrimKey (LPDBRECORD n,LPPRIMKEY kn)
  {
  Table_Key ktold(n->GetTableID(),n->GetVersion(),n->GetPrimKey());
  LPGRECLIST FAR *lrl = (LPGRECLIST FAR *) pHash->GetDatav (ktold.buffer,ktold.Size);
  LPGRECLIST rl = *lrl ;
  n->FreeRecordForJoins ();
  pHash->DelDatav (ktold.buffer,ktold.Size);
  n->SetPrimKey (kn);
  Table_Key ktnew(n->GetTableID(),n->GetVersion(),kn);
  pHash->DelDatav (ktnew.buffer,ktnew.Size);    // Sicherheitshalber den eintrag loeschen, bekanntlich wird ja der neue gueltig
  pHash->SetDatav (ktnew.buffer,&rl,sizeof(rl),ktnew.Size);
  n->UseRecordForJoins ();
  }

void ReplaceNextSame (LPDBRECORD o,LPDBRECORD n)
  {
  for (WORD i = 0 ; i < o->GetAnzVars() ; i++) {
    LPVARELEM v1 = o->GetVarElem(i);
    if (v1->NextSame != NULL) {
      LPVARELEM v1a = n->GetVarElem(i);
      LPVARELEM prev = v1 ;
      for (LPVARELEM h = v1->NextSame ; ; ) {
        LPVARELEM Next = h->NextSame;
        prev->NextSame = h->NextSame ;
        h->NextSame = NULL ;
        h->FillIn (v1a);

        if (Next == v1)
          break ;
        else
          h = Next ;
        }
      if (v1->NextSame == v1) v1->NextSame = NULL ;
      }
    }
  }

void ReplaceNextSameForFunctions (LPDBRECORD o,LPDBRECORD n)
// Alle Nextsameverbindungen, die wegen Funktionen vorhanden sind, muessen
// Weigergegeben werden
  {
  for (WORD i = 0 ; i < o->GetAnzVars() ; i++) {
    LPVARELEM v1 = o->GetVarElem(i);
    if (v1->NextSame != NULL) {
      LPVARELEM v1a = n->GetVarElem(i);
      LPVARELEM prev = v1 ;
      for (LPVARELEM h = v1->NextSame ; ; ) {
        LPVARELEM Next = h->NextSame;
        if (h->Erzeuger) {
          prev->NextSame = h->NextSame ;
          h->NextSame = NULL ;
          h->FillIn (v1a);
          }
        else
          prev = h ;

        if (Next == v1)
          break ;
        else
          h = Next ;
        }
      if (v1->NextSame == v1) v1->NextSame = NULL ;
      }
    }
  }

// Einen Record der Klasse DBRecordAdmin bekannt geben
LPDBRECORD DBRecordAdmin::Use (LPDBRECORD n,DWORD OwnerID,DWORD DocumentID)
  {
  LPDBRECORD h = Find (n->GetPrimKey(),n->GetTableID(),n->GetVersion());
  if (h == NULL) {
    if (FindSame (n))   // Untersuchen, ob er nicht doch
                        // schon drinnen ist (ohne Primaerschluessel durchaus
                        // moeglich)
      h = n ;
    }
  if (h != NULL) {
    if (h == n) {
      // Fuer Listen: der Record wird mehrmals geladen
      DBWIN_ASSERT (!h->IsUsedBy(OwnerID));
      h->UseBy(OwnerID);
      return h;
      }
    else if ((!n->isLocked()) && (h->isLocked())) {
      // Fall a: der bereits geladene Record ist gelockt
      DBWIN_ASSERT (!h->IsUsedBy(OwnerID));
      h->UseBy(OwnerID);
      // Der uebergebene Record kann nicht gebraucht werden
      ReplaceNextSame (n,h);
      h->MoveConnections(n,NULL,NULL);
      delete n;
      return h;
      }
    else {
      // Fall b: der bereits geladene Record ist nicht gelockt
      // -> dieser Record muss upgedated werden
      if ((h->doUpdate) || (n->doUpdate))
        h->doUpdate = TRUE ;
      ReplaceNextSame (n,h);
      h->MoveConnections(n,NULL,NULL);
      h->Update (n);
      if (n->isLocked()) h->setLocked();
      DBWIN_ASSERT (!h->IsUsedBy(OwnerID));
      h->UseBy(OwnerID);
      // Der uebergebene Record kann nicht gebraucht werden
      delete n;
      return h;
      }
    }
  else {
    // In die Liste einfuegen
    Add (n);
    // Die Joins verbinden
    n->DoAllJoins ();
    // Und den neuen zuruekgeben
    n->UseBy (OwnerID);
    return n;
    }
  }

WORD DBRecordAdmin::GetSameRecords (LPDBRECORD samethan,WORD TableID,WORD Version,LPPRIMKEY k,LPJOINRECLIST jl)
  {
  if (k->IsNullKey()) return 0;
  Table_Key kt(TableID,Version,k);
  LPJOINRECLIST FAR *List = (LPJOINRECLIST FAR *) jHash->GetDatav (kt.buffer,kt.Size);
  if (List != NULL) {
    WORD j = 0 ;
    int Anz = GetBlockSize(*List) / sizeof(*jl);
    for (int i = 0 ; i < Anz ; i++) {
      if ((*List)[i].rec != samethan) {
        WIN_ASSERT(j < MAXJOINRECLISTS);
        jl[j++] = (*List)[i] ;
        }
      }
    return j;
    }
  else
    return 0;
  }

// Einen Record der Klasse DBRecordAdmin wieder entziehen
DLLExport BOOL _export FAR PASCAL DBRecordAdmin::Release (LPDBRECORD n,DWORD OwnerID,DWORD DocumentID)
  {
  // Ueberpruefung, ob n ueberhaupt gueltig
  LPGRECLIST FAR * res = (LPGRECLIST FAR *) rHash->GetData (LONG (n));
  if (res != NULL) {
    // Record gueltig
    n->ReleaseFrom (OwnerID);
    if (n->UseCount() == 0) {
      // Datensatz darf geloescht werden
      n->FreeAllJoins();
      if ((*res)->Prev != NULL)
        (*res)->Prev->Next = (*res)->Next ;
      else
        rl = (*res)->Next ;
      if ((*res)->Next != NULL)
        (*res)->Next->Prev = (*res)->Prev ;
      FreeGlobMem (*res);
      rHash->DelData (LONG (n));
      LPPRIMKEY k = n->GetPrimKey();
      if ((k != NULL) && (k->Data != NULL)) {
        Table_Key kt(n->GetTableID(),n->GetVersion(),k);
        pHash->DelDatav (kt.buffer,kt.Size);
        }
      n->FreeRecordForJoins ();
      return TRUE ;
      }
    else {
      n->DelConnections (OwnerID);   // Der wird andersweitig noch 
                                        // Gebraucht
      return FALSE ;
      }
    }
  return FALSE ; // h == NULL ... perverser Zustand (Zeiger auf 
                 // Record exist noch, obwohl der Record nicht
                 // nicht mehr existiert, kann in Verbindung mit ReUse
                 // durchaus vorkommen
  }

///////////////////////////////////////////////////////////////////////
//  Arbeiten mit RecRoot
///////////////////////////////////////////////////////////////////////
DLLExport LPRECROOT _export FAR PASCAL InitializeRecRoot (WORD AnzTables)
  {
  WORD AnzRecs   = AnzTables;
  LPRECROOT res  = LPRECROOT (GetGlobMem (sizeof(*res) + (AnzTables - 1) * sizeof(LPDBRECORD)));
  // res->rec = (LPDBRECORD FAR *) GetGlobMem (AnzRecs * sizeof(LPDBRECORD));
  res->NextInKontext = (RecRootRef FAR *) GetGlobMem (AnzRecs * sizeof(RecRootRef));
  res->PrevInKontext = (RecRootRef FAR *) GetGlobMem (AnzRecs * sizeof(RecRootRef));
  res->AnzTables = AnzTables;
  return res;
  }

void CheckAdministratiedRecords(DWORD OwnerID,DWORD DocumentID)
  {
#ifdef TEST
  if (DocumentID == 0) {
    for (LPGRECLIST h = GetDBRecordAdmin()->rl ; h != NULL ; h = h->Next ) {
      WIN_ASSERT (h->rec->GetTableID() != 0);
      }
    return ;
    }
#endif
#ifdef DEBUG
  for (LPGRECLIST h = GetDBRecordAdmin()->rl ; h != NULL ; h = h->Next ) {
    if (h->rec->IsUsedBy (OwnerID)) {
      WIN_ASSERT (FALSE);
      LPDBRECORD x = h->rec ;
      if (GetDBRecordAdmin()->Release(x,OwnerID,DocumentID))
        delete x ;
      }
    }
#endif
  }

void FreeBlobs (LPDBRECORD r,BYTE FAR *Types)
  {
  if (r != NULL) {
    for (WORD i = 0 ; i < r->GetAnzVars () ; i++) {
      if (Types[i] == VAR_BLOB) {
        BlobDesc FAR *b = (BlobDesc FAR *) r->Get(i);
        if ((b != NULL) && (b->hGmem))
          GlobalFree (b->hGmem);
        r->Del(i);
        }
      }
    }
  }

DLLExport void _export FAR PASCAL DeleteRecRoot (LPRECROOT rr,DWORD DocumentID)
  {
  FreeBlobs (rr->GetRecord(0),((mdiChild *)DocumentID)->schd->LocalTypes);
  FreeBlobs (rr->GetRecord(1),((mdiChild *)DocumentID)->schd->HelpTypes);
  delete rr->GetRecord(0);                  // Lokale Variablen
  delete rr->GetRecord(1);                  // Hilfsvariablen

  for (WORD j = CSYSRECS ; j < rr->AnzTables ; j++) {
    RecRootRef FAR *pr = rr->PrevInKontext + j ;
    RecRootRef FAR *nr = rr->NextInKontext + j ;

    if (pr->rr != NULL) {
      pr->rr->NextInKontext[pr->tnr].rr = nr->rr;
      pr->rr->NextInKontext[pr->tnr].tnr = nr->tnr;
      pr->rr->NextInKontext[pr->tnr].rrOwner = nr->rrOwner;
      }
    if (nr->rr != NULL) {
      nr->rr->PrevInKontext[nr->tnr].rr = pr->rr;
      nr->rr->PrevInKontext[nr->tnr].tnr = pr->tnr;
      nr->rr->PrevInKontext[nr->tnr].rrOwner = pr->rrOwner;
      }
    LPDBRECORD x = rr->GetRecord(j);
    if (x != NULL) {
      // Alle Records, die in der Zykliste vorkommen, koennen bedenkenlos geloescht werden
      if (GetDBRecordAdmin()->Release(x,DWORD(rr) + j,DocumentID)) {
        for ( LPDBRECORD h = x->NextInCycl ; ((h != NULL) && (h != x)) ; ) {
          LPDBRECORD n = h->NextInCycl ;
          for (WORD k = j + 1 ; k < rr->AnzTables ; k ++) {
            if (rr->GetRecord(k) == h) {
              rr->SetRecord(k,NULL) ;
              break ;
              }
            }
          h->NextInCycl = NULL;
          delete h ;
          h = n ;
          }
        x->NextInCycl = NULL;
        delete x;
        }
      }
    // CheckAdministratiedRecords(DWORD(rr) + j,DocumentID);
    }

  // FreeGlobMem (rr->rec);
  FreeGlobMem (rr->NextInKontext);
  FreeGlobMem (rr->PrevInKontext);
  FreeGlobMem (rr);
  }


DLLExport void _export FAR PASCAL RecRoot::SetRec (LPDBRECORD nrec,WORD TableNr,DWORD DocumentID,BOOL fromInsert)
  {
  LPDBRECORD orec = GetRecord (TableNr);
  if (orec == nrec) return;   // hab ihn eh schon ...
  if (orec != NULL) {
    if (orec->GetPrimKey()->Data == NULL) {
      if (fromInsert) {
        //
        // der alte Datensatz muss upgedatet werden, ohne dass er
        // ausgetauscht wird
        orec->FreeRecordForJoins ();
        orec->FreeJoins (DWORD (this) + TableNr);
        orec->Update (nrec);
        if (nrec->isLocked()) orec->setLocked();
        orec->SetPrimKey(nrec->GetPrimKey());
        orec->UseRecordForJoins ();
        orec->DoAllJoins();

        // Der uebergebene Record kann nicht gebraucht werden
        //
        delete nrec;
        nrec = NULL;
        }
      else {
        // 
        // Der alte Datensatz hat noch keinen Schluessel ->
        // Eigenschaften des alten Datensatzes muessen uebernommen werden,
        // der alte darf ev. geloescht werden
        //
        // nrec->MoveConnections(orec,DWORD(this) + TableNr);
        // nrec->MoveConnections(orec,DocumentID);
        nrec->MoveConnections(orec,((mdiChild *) DocumentID)->GetErzContext()->DocumentID(),DWORD(this) + TableNr);
        nrec->Update(((mdiChild *) DocumentID)->GetErzContext()->DocumentID());
        // nrec->Update (DocumentID);
        if (GetDBRecordAdmin()->Release(orec,DWORD(this) + TableNr,DocumentID)) {
          nrec->MoveConnections(orec,NULL,NULL);
          delete orec;
          }
        }
      }
    else {
      LPDBRECORD h = GetDBRecordAdmin()->Find (nrec->GetPrimKey(),nrec->GetTableID(),nrec->GetVersion());
      if (h == NULL) {
        if (GetDBRecordAdmin()->FindSame (nrec))   // Untersuchen, ob er nicht doch
                                                   // schon drinnen ist (ohne Primaerschluessel durchaus
                                                   // moeglich)
          h = nrec ;
        }
      BOOL doAdd ;
      if ((h != NULL) && (h != nrec)) {
        doAdd = FALSE ;
        // Die Eingenschaften des Neuen Datensatzes werden in den gefundenen
        // Datensatz ubernommen, der neue kann nicht gebrauch werden
        //---------------------------------------------------------------
        if ((!nrec->isLocked()) && (h->isLocked())) {
          // Fall a: der bereits geladene Record ist gelockt
          ReplaceNextSame (nrec,h);
          h->MoveConnections(nrec,NULL,NULL);
          delete nrec;
          nrec = h ;
          }
        else {
          // Fall b: der bereits geladene Record ist nicht gelockt
          // -> dieser Record muss upgedated werden
          if ((h->doUpdate) || (nrec->doUpdate))
            h->doUpdate = TRUE ;
          ReplaceNextSameForFunctions (nrec,h);
          h->FreeRecordForJoins (); // Statt ReplaceNextSame ();
          h->FreeJoins();
          h->MoveConnections(nrec,NULL,NULL);
          h->Update (nrec);
          // Statt ReplaceNextSame ();
          h->UseRecordForJoins ();
          h->DoAllJoins();
          h->Update (DocumentID);
          if (nrec->isLocked()) h->setLocked();
          // Der uebergebene Record kann nicht gebraucht werden
          delete nrec;
          nrec = h;
          }
        }
      else {
        doAdd = (h == NULL);
        }

      // Die Connections muessen neu gesetzt werden
      if (orec != nrec) {
        // nrec->MoveConnections(orec,DWORD(this) + TableNr);
        nrec->MoveConnections(orec,((mdiChild *) DocumentID)->GetErzContext()->DocumentID(),DWORD(this) + TableNr);
        // nrec->MoveConnections(orec,DocumentID);
        if (GetDBRecordAdmin()->Release(orec,DWORD(this) + TableNr,DocumentID)) {
          nrec->MoveConnections(orec,NULL,NULL);
          delete orec;
          }
        nrec->DoAllJoins ();
        // nrec->Update(DWORD(this) + TableNr);
        // nrec->Update(DocumentID);
        nrec->Update(((mdiChild *) DocumentID)->GetErzContext()->DocumentID());
        nrec->UseBy (DWORD(this) + TableNr);
        if (doAdd)
          GetDBRecordAdmin()->Add(nrec);
        SetRecord (TableNr,nrec);
        }
      nrec = NULL ;   // Keine weitern Aktionen mehr
      }
    }
  if (nrec != NULL) {
    nrec = GetDBRecordAdmin()->Use(nrec,DWORD(this) + TableNr,DocumentID);
    SetRecord (TableNr,nrec);
    }
  }

/////////////////////////////////////////////////////////////
//  Die Joins auffrischen ...
/////////////////////////////////////////////////////////////
BOOL IsNullValue (LPVOID key)
  {
  WORD s = GetBlockSize(key);
  for (WORD i = 0 ; i < s ; i++)
    if (LPSTR(key)[i] != '\0') return FALSE ;
  return TRUE ;
  }

DLLExport void _export FAR PASCAL DBRecord::RefreshJoin (LPDBREQUEST req,WORD TablePart,LPVOID FAR *ExtParams,int AnzExtra,LPOLDPARAM oldP)
  {
  if (req->fdsc[TablePart].freq != NULL) {
    FreeRecordForJoins ();
    LPVOID fKey  = Get (req->fdsc[TablePart].VarID[0]);
    WORD   fType = GetDataType (req->fdsc[TablePart].VarID[0]);
    LPVOID sKey[3];
    WORD   sType[3];
    for (WORD j = 0; j < 3 ; j++) {
      if (req->fdsc[TablePart].VarID[j+1] != 0xFFFF) {
        sKey[j] = Get (req->fdsc[TablePart].VarID[j+1]);
        sType[j] = GetDataType (req->fdsc[TablePart].VarID[0]);
        }
      else {
        sKey[j] = NULL;
        }
      }
    BOOL doDelPart = TRUE ;
    DelJoins (TablePart);
    if ((fKey != NULL) && (!IsNullValue (fKey))) {
      // Einen Schluessel gibts, probieren wir mal weiter
      LPVOID nstmt = NULL;
      RecBuffer rn;
      lmemset (&rn,'\0',sizeof(rn));

      // Die Schluessel fuer den Aufruf setzen
      WORD dummy = WORD(-1);
      req->fdsc[TablePart].freq->SetParam(1,&dummy,sizeof(WORD));
      req->fdsc[TablePart].freq->SetParam(2,fKey,GetBlockSize(fKey));
      req->fdsc[TablePart].freq->SetParamType (2,fType);
      for (j = 0 ; j < 3 ; j++) {
        if (req->fdsc[TablePart].VarID[j+1] != 0xFFFF) {
          if (sKey[j] != NULL) {
            req->fdsc[TablePart].freq->SetParam(3+j,sKey[j],GetBlockSize(sKey[j]));
            req->fdsc[TablePart].freq->SetParamType (3+j,sType[j]);
            }
          }
        else
          break ;
        }
      // Die zusaetzlichen Schluessel setzen
      for (int m = 2 ; m < int(req->AnzParam) ; m++) {
        if (req->Param[m] != NULL)
          req->fdsc[TablePart].freq->SetParam(1+j+m,req->Param[m],GetBlockSize(req->Param[m]));
        req->fdsc[TablePart].freq->SetParamType(1+j+m,req->ParamType[m]);
        }

      // Den Datenbankaufruf
      int opCode = GetDLLAdmin()->GetDLLEntry(req->fdsc[TablePart].freq->TableDef[0]->
            GetDLLHandle())->DBCall (DBOP_GET,1,req->fdsc[TablePart].freq,&nstmt,&rn);
      // Statement wieder abbauen
      GetDLLAdmin()->GetDLLEntry(req->fdsc[TablePart].freq->TableDef[0]->
            GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&nstmt,NULL);
      req->fdsc[TablePart].freq->ClearParams ();

      if (opCode == DBCALL_SUCCESS) {
        doDelPart = FALSE ;
        // Resultat speichern
        if (req->AnzElems > 0) {
          for (int j = 0 ; j < req->fdsc[TablePart].freq->AnzElems ; j++) {
            LPVOID data = rn.First()->rec[0]->Get (j);
            LPVOID odata = Get (req->fdsc[TablePart].VarIndex[j]);
            if ((data != NULL) && 
                  ((odata == NULL) || (GetBlockSize(odata) != GetBlockSize(data)) ||
                  (!lmemcmp (odata,data,GetBlockSize(data))))
                )
              Set(req->fdsc[TablePart].VarIndex[j],data,GetBlockSize(data),NULL,TRUE);
            else if ((data == NULL) && (odata != NULL))
              Del(req->fdsc[TablePart].VarIndex[j],NULL,TRUE);
            }
          }
        else {
          DBWIN_ASSERT(FALSE);
          }
        // Weiter Aufrauemarbeiten
        rn.Clear ();
        }
      }
    if (doDelPart) {
      if (req->AnzElems > 0) {
        for (int j = 0 ; j < req->fdsc[TablePart].freq->AnzElems ; j++) {
          LPVOID odata = Get (req->fdsc[TablePart].VarIndex[j]);
          if (odata != NULL)
            Del(req->fdsc[TablePart].VarIndex[j],NULL,TRUE);
          }
        }
      else {
        DBWIN_ASSERT(FALSE);
        }
      }
    // Die aktive Parameter sichern
    req->SaveOldParams (this,TablePart,oldP);
    // Und noch die Joins in Ordnung bringen
    UseRecordForJoins ();
    NewJoins (TablePart);
    }
  }

// Implementierung der Klasse DBRecord
//////////////////////////////////////////////
WORD DBRecord::GetVarNumber (int TableNumber,WORD VarID,BOOL FAR *done)
  {
  if (elem != NULL) {
    for (WORD i = 0 ; i < AnzVars ; i++) {
      if ((elem[i].VarID == VarID) && (elem[i].TableNumber == TableNumber)) {
        *done = TRUE ;
        return i ;
        }
      }
    return 0xFFFF ;
    }
  else {
    *done = TRUE ;
    return VarID ;
    }
  }

DLLExport void _export FAR PASCAL DBRecord::CalcPrimKey (int TableNumber,LPPRIMKEY k)
  {
  WORD KeySeg[MAX_PRIMARYSEGS + 1] ;  // Platz fuer das 0xFFFF !
  if (tbdef[TableNumber]->GetPrimKeySegs (KeySeg)) {
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      BOOL done;
      if (KeySeg[i] == 0xFFFF) break ;
      WORD VarInd = GetVarNumber (TableNumber,KeySeg[i],&done);
      if ((done) && (VarInd != 0xFFFF)) {
        LPVARDEF v = tbdef[TableNumber]->GetVarDef(KeySeg[i]);
        LPVOID Data = Get(VarInd);
        if (Data != NULL) {
          if ((v->mType == VAR_STR) && (v->VarSize != 0xFFFF)) {
            int len = GetBlockSize(Data);
            if (len < v->VarSize) {
              k->PushKeySeg (Data,GetBlockSize(Data));
              LPVOID dummy = GetGlobMem (v->VarSize - len);
              k->PushKeySeg (dummy,v->VarSize - len);
              FreeGlobMem (dummy);
              }
            else
              k->PushKeySeg (Data,GetBlockSize(Data));
            }
          else
            k->PushKeySeg (Data,GetBlockSize(Data));
          }
        else {
          k->SetKeyNull ();
          break ;
          }
        }
      else
        k->SetKeyNull();
      }
    }
  else
    k->SetKeyNull ();
  }

LPSTR SkipComma (LPSTR h)
  {
  for ( ; ((*h) && (*h != ',')) ; h ++) ;
  if (*h == ',') h ++ ;
  return h ;
  }

BOOL mystrcmp (LPSTR s1,LPSTR s2,int tbNum)
  {
  for ( LPSTR x = s2 ; *x ; x ++ ) {
    // Aliasnamen noch wegschneiden
    if (*x == '.') {
      if ((x > s2) && ((x[-1] - '0') == tbNum))
        s2 = ++ x;
      break ;
      }
    }
  for ( ; *s1 ; ) {
    if (*s1 ++ != *s2 ++) return FALSE ;
    }
  return TRUE ;
  }

DLLExport void _export FAR PASCAL DBRecord::SetSortVals (LPDBREQUEST req)
  {
  if ((req->OrderStatement == NULL) || (*req->OrderStatement == '\0')) {
    // die Werte des Primaerschluessels setzen
    WORD KeySeg[MAX_PRIMARYSEGS + 1] ;  // Platz fuer das 0xFFFF !
    WIN_ASSERT(tbdef[0]->GetPrimKeySegs (KeySeg));
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      BOOL done;
      if (KeySeg[i] == 0xFFFF) break ;
      WORD VarInd = GetVarNumber (0,KeySeg[i],&done);
      WIN_ASSERT(done);
      LPVOID Data = Get(VarInd);
      DBWIN_ASSERT(i < CB_SORTPARAM);
      req->SetSortParam (i,Data,GetBlockSize(Data));
      req->SetSortParamType (i,GetDataType (VarInd));
      }
    }
  else {
    int j = 0 ;
    // die Sortierfelder lesen und deren Werte setzen
    for (LPSTR h = req->OrderStatement ; *h ; h = SkipComma (h)) {
      for (int i = 0 ; i < int (AnzVars) ; i ++) {
        WORD VarID;
        LPTABLEDEF tb = GetTableDef (i,&VarID);
        LPVARDEF v = tb->GetVarDef(VarID);
        if (mystrcmp (v->GetName(),h,(req->AnzElems > 0) ? elem[i].TableNumber : 0 )) {
          // Gefunden ;
          LPVOID Data = Get (i);
          DBWIN_ASSERT(j < CB_SORTPARAM);
          req->SetSortParam (j,Data,GetBlockSize(Data));
          req->SetSortParamType (j,GetDataType (i));
          j++ ;
          break ;
          }
        }
      if (i == int (AnzVars))
        // Nicht gefunden -> Fehler
        WIN_ASSERT (FALSE); 
      }
    }
  }

BOOL DBRequest::CheckSortVals ()
  {
  if ((OrderStatement == NULL) || (*OrderStatement == '\0')) {
    // die Werte des Primaerschluessels setzen
    WORD KeySeg[MAX_PRIMARYSEGS + 1] ;  // Platz fuer das 0xFFFF !
    if (!TableDef[0]->GetPrimKeySegs (KeySeg))
      return FALSE ;
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      BOOL done;
      if (KeySeg[i] == 0xFFFF) break ;
      WORD VarInd = GetVarNumberByNum (0,KeySeg[i],&done);   // !!!! (Martin: ByNum)
      if (!done)
        return FALSE ;
      }
    }
  else {
    // die Sortierfelder lesen und deren Werte setzen
    int AnzVars = (AnzElems > 0) ? int (AnzElems) : TableDef[0]->GetAnzVars();
    for (LPSTR h = OrderStatement ; *h ; h = SkipComma (h)) {
      for (int i = 0 ; i < int (AnzVars) ; i ++) {
        WORD VarID;
        LPTABLEDEF tb = (AnzElems > 0) ? TableDef[elem[i].TableNumber] : TableDef[0] ;
        if (AnzElems > 0)
          VarID = elem[i].VarID ;
        else
          VarID = i ;
        LPVARDEF v = tb->GetVarDef(VarID);
        if (mystrcmp (v->GetName(),h,(AnzElems > 0) ? elem[i].TableNumber : 0 )) {
          // Gefunden ;
          break ;
          }
        }
      if (i == int (AnzVars)) {
        // Nicht gefunden -> Fehler
        return FALSE ;
        }
      }
    }
  return TRUE ;
  }

/*------------------------------------------*/
/*      Debugger - Hilfsfunktionen          */
/*------------------------------------------*/
void PushDFIVar (DebFifoInfo FAR *ddf,LPSTR Scope,WORD TableID,WORD Version,WORD VarID,int RecordType)
  {
  switch (RecordType) {
    case RECORDTYPE_DBLOCAL  :
      TableID = 0xFFFE;
      Version = 0;
      break ;
    case RECORDTYPE_DBHELP   :
      TableID = 0xFFFE;
      Version = 0;
      break ;
    }
  BOOL found = FALSE ;
  for (int i = 0 ; i < ddf->AnzVars ; i++) {
    if ((ddf->Var[i].VarNr == VarID) && 
        (ddf->Var[i].tRef.TableNr == TableID) &&
        (ddf->Var[i].tRef.Version == Version) &&
        (((*ddf->Var[i].Scope == '\0') && (Scope == NULL)) ||
          (lstrcmp (ddf->Var[i].Scope,Scope) == 0)))
      found = TRUE ;
    }
  if ((!found) && (ddf->AnzVars < MAX_DEBFINFO)) {
    ddf->Var[ddf->AnzVars].VarNr = VarID;
    ddf->Var[ddf->AnzVars].tRef.TableNr = TableID;
    ddf->Var[ddf->AnzVars].tRef.Version = Version;
    if (Scope != NULL) lstrcpy (ddf->Var[ddf->AnzVars].Scope,Scope);
    else               *ddf->Var[ddf->AnzVars].Scope = '\0';
    ddf->AnzVars++ ;
    }
  }

void CheckRecordInHistory(DebFifoInfo FAR *dff,LPDBRECORD rec,LPSTR Scope,LPCMDFIFO res)
  {
  for (WORD i = 0 ; i < rec->GetAnzVars() ; i++) {
    LPVARELEM v = rec->vartbl+i;
    for (int j = 0 ; j < res->HistCount() ; j++) {
      if (res->History[j].EleReferenced (v))
        PushDFIVar (dff,Scope,rec->GetTableID(),rec->GetVersion(),i,rec->GetRecordType());
      }
    }
  }

BOOL CheckVarElemIn (DebFifoInfo FAR *dff,LPDBRECORD rec,LPSTR Scope,LPVARELEM vToSearch)
  {
  for (WORD i = 0 ; i < rec->GetAnzVars() ; i++) {
    LPVARELEM v = rec->vartbl+i;
    if (v == vToSearch) {
      PushDFIVar (dff,Scope,rec->GetTableID(),rec->GetVersion(),i,rec->GetRecordType());
      return TRUE ;
      }
    }
  return FALSE ;
  }

DLLExport BOOL _export FAR PASCAL GetCmdFifoInfo (int Nmbr,DebFifoInfo FAR *dff)
  {
  LPCMDFIFO res = GetAsync_cmdfifo()->GetCmdFifoByNumber(Nmbr);
  dff->AnzVars = 0;
  dff->DocumentID = 0L;
  if (res != NULL) {
    dff->DocumentID = res->DocumentID;
    dff->Cmd = res->Cmd;
    // So, jetzt wirds gemein
    // Zuerst alle Lokalen und Hilfsrecords abfragen...
    for (MDIListEntry FAR *x = GetMDILEFirst() ; x != NULL ; x = x->Next) {
      for (int i = 0 ; i < 5 ; i++) {
        LPDBRECORD dblr = x->ent->rr->GetRecord (i);
        if (dblr)
          CheckRecordInHistory (dff,dblr,x->ent->schd->fName,res);
        }
      }
    // und jetzt noch alle globalen Records abfragen
    for (LPGRECLIST h = GetDBRecordAdmin()->rl ; h != NULL ; h = h->Next ) {
      if (h->rec)
        CheckRecordInHistory (dff,h->rec,NULL,res);
      }
    }
  return (res != NULL) ;
  }

DWORD GetDocumentIDFor(DebFifoInfo FAR *dff,LPVOID Cmd)
  {
  // in den lebenden Scripts nachsehen
  *dff->ModuleName = '\0';
  dff->Cmd = Cmd;
  for (MDIListEntry FAR *x = GetMDILEFirst() ; x != NULL ; x = x->Next) {
    char huge *start = (char huge *) GlobalLock (x->ent->commands);
    char huge *end = start + GlobalSize(x->ent->commands);
    if ((((char huge *) Cmd) > start) && (((char huge *) Cmd) <= end)) {
      lstrcpy (dff->ModuleName,x->ent->schd->fName);
      dff->CmdOffset = ((char huge *) Cmd) - start;
      return DWORD(x->ent);
      }
    }
  // in den alten Scripts zu sehen
  for (OldMDIListEntry FAR *o = GetOLDMDILEFirst() ; o != NULL ; o = o->Next) {
    char huge *start = (char huge *) GlobalLock (o->commands);
    char huge *end = start + GlobalSize(o->commands);
    if ((((char huge *) Cmd) > start) && (((char huge *) Cmd) <= end)) {
      lstrcpy (dff->ModuleName,o->fName);
      dff->CmdOffset = ((char huge *) Cmd) - start;
      return 0L;
      }
    }
  return 0L;
  }

void GetDataInfoFor (DebFifoInfo FAR *dff,LPVARELEM v)
  {
  // Alle Lokalen und Hilfstabellen abklappern
  for (MDIListEntry FAR *x = GetMDILEFirst() ; x != NULL ; x = x->Next) {
    for (int i = 0 ; i < 5 ; i++) {
      LPDBRECORD dblr = x->ent->rr->GetRecord (i);
      if (dblr != NULL)
        if (CheckVarElemIn (dff,dblr,x->ent->schd->fName,v)) return ;
      }
    }
  // und jetzt noch alle globalen Records abfragen
  for (LPGRECLIST h = GetDBRecordAdmin()->rl ; h != NULL ; h = h->Next ) {
    if (CheckVarElemIn (dff,h->rec,NULL,v)) return ;
    }
  }

DLLExport BOOL _export FAR PASCAL GetCmdMoreInfo (BYTE CmdNmbr,BYTE HistNmbr,DebFifoInfo FAR *dff)
  {
  int Nmbr = (CmdNmbr == 0xFF) ? -1 : int(CmdNmbr);
  LPCMDFIFO res = GetAsync_cmdfifo()->GetCmdFifoByNumber(Nmbr);
  dff->AnzVars = 0;
  dff->DocumentID = 0L;
  if ((res != NULL) && (int(HistNmbr) < res->HistCount())) {
    HistEle FAR *h = &res->History[HistNmbr] ;
    dff->DocumentID = GetDocumentIDFor(dff,h->cmd);
    dff->Cmd = h->cmd;
    for (int i = 0 ; i < h->AnzKeys() ; i++)
      GetDataInfoFor (dff,h->fk[i]);
    return TRUE ;
    }
  return FALSE ;
  }

void InitializeRecAdmin ()
  {
  rHash = new hash (137,LONGKEY);
  pHash = new hash (137,VOIDKEY);
  jHash = new hash (137,VOIDKEY);
  }

void ExitRecAdmin ()
  {
  delete rHash;
  delete pHash;
  delete jHash;
  rHash = NULL ;
  pHash = NULL ;
  jHash = NULL ;
  }

DLLExport BOOL WINAPI DBRecord::IsValid ()
  {
  BOOL correct = TRUE ;
  for (WORD i = 0 ; ((i < AnzVars) && (correct)) ; i++) {
    LPVARDEF v ;
    WORD vId ;
    if (elem != NULL) {
      WORD tnr = elem[i].TableNumber;
      if (tnr != 0) continue ;    // Nur die Haupttabelle wird ueberprueft
      vId = elem[i].VarID ;
      }
    else
      vId = i ;
    v = tbdef[0]->GetVarDef(vId);
    if (v->Property & VPROP_NOTNULL) {
      // Autoinc - Spalten duerfen NULL sein !!!
      correct = ((Get(i) != NULL) || 
                 ((tbdef[0]->GetKeyDef(0)->VarID == vId) &&
                  ((tbdef[0]->GetKeyDef(0)->Attribute & CLKD_AUTOINC) != 0))
                ) ;
      }
    }
  return correct ;
  }

