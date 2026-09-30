///////////////////////////////////////////////////////////////////////
//  Implementierung der Klasse dblist
///////////////////////////////////////////////////////////////////////
//
// $Header:   F:/marille/clinicum/dbhelp/rev/dblist.cpv   1.69   10 Apr 2000 12:34:20   Hannes  $
// $Log:   F:/marille/clinicum/dbhelp/rev/dblist.cpv  $
// 
//    Rev 1.69   10 Apr 2000 12:34:20   Hannes
// Speicherfresser
// 
//    Rev 1.68   01 Dec 1999 16:40:38   Hannes
// VoidCompare...
// 
//    Rev 1.67   20 Oct 1999 07:52:28   Hannes
// Verschiedenste Parameterfunktionen
// 
//    Rev 1.66   09 Sep 1999 22:18:54   Hannes
// SQL Syntax auch in ODBC
// 
//    Rev 1.65   07 Sep 1999 07:57:24   Hannes
// 
//    Rev 1.64   12 May 1999 17:16:26   Wolfgang
// 1.) Neue Methode CheckSegments.
// 2.) Bei nicht Finden in FindRecord pruefen, ob korrekte Segmente angegeben.
// 
//    Rev 1.63   03 May 1999 15:57:06   Wolfgang
// 1.) FindRecord auf abgeleitete Strukturen umgebaut.
// 2.) FindRecord mit optionalem Mode Parameter.
// 3.) IsHashed mit optionalen Parametern die Hashtabelle angeben.
// 4.) Neue Funktion CompareEqual zum Vergleich einiger Segmente eines Records 
//     mit uebergebenen Daten.
// 
//    Rev 1.62   15 Feb 1999 21:43:26   Hannes
// Sortiersegmente auch in der 2. Tabelle
// 
//    Rev 1.61   07 Feb 1999 13:50:12   Hannes
// 
//    Rev 1.60   07 Feb 1999 13:45:00   Hannes
// GetLastError abgesichert
// 
//    Rev 1.59   05 Feb 1999 21:37:12   Martin
// verbessertes Errorhandling
// 
//    Rev 1.58   29 Jan 1999 09:55:14   Hannes
// Rueckgabewert von AddRec*
// 
//    Rev 1.57   28 Jan 1999 12:21:04   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.56   30 Oct 1998 19:03:42   Hannes
// Beim Loeschen auch die Selection - End Flags weitergegeben
// 
//    Rev 1.55   05 Oct 1998 11:09:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.54   04 Aug 1998 17:54:48   Hannes
// Timestamp
// 
//    Rev 1.53   29 Jun 1998 19:06:46   Hannes
// SortList mit mehr als 8000 Elementen
// 
//    Rev 1.52   14 May 1998 12:49:46   Hannes
// SaveOldParams: Verwendung von h->rec statt rec
// 
//    Rev 1.51   28 Apr 1998 18:20:30   Martin
// ParamType auch bei NULL setzen
// 
//    Rev 1.50   28 Apr 1998 11:48:32   Hannes
// Freigeben von Vollstaendigen Saetzen
// 
//    Rev 1.49   19 Dec 1997 09:36:42   Martin
// PVCS-Header, kleine Fehlerkorrektur in DBList::GetPrev
//

#include <windows.h>
#include <stdio.h>
#include <search.h>
#include "dds32.h"

#include "stdlib.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "hash.hpp"
#include "dbrecord.hpp"
#define MODULENUM 88
#include "winass.hpp"
#define NODDSDATA
#include "dds.hpp"

// Funktionen fuer Errorhandling:
static GLE_PROC GLE_proc;
static BEH_PROC BEH_proc;
static EEH_PROC EEH_proc;
DLLExport void _export WINAPI SetErrorHandlingProcs(GLE_PROC GLEproc,BEH_PROC BEHproc,EEH_PROC EEHproc)
  {
  GLE_proc = GLEproc;
  BEH_proc = BEHproc;
  EEH_proc = EEHproc;
  }

DLLExport LPVOID _export WINAPI GetLastErrorCBP(void)
  {
  if (GLE_proc != NULL)
    return (*GLE_proc)();
  else
    return NULL;
  }

DLLExport void _export WINAPI BeginErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd)
  {
  if (BEH_proc != NULL)
    (*BEH_proc)(ErrorCBP,hd);
  }

DLLExport void _export WINAPI EndErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd)
  {
  if (EEH_proc != NULL)
    (*EEH_proc)(ErrorCBP,hd);
  }

LPDBRECORD FindRecordInCycl (LPDBRECORD rs,TableRef FAR *x)
  {
  for (LPDBRECORD h = rs ; h != NULL ; h = h->NextInCycl ) {
    if (lmemcmp (&h->tRef,x,sizeof(*x))) return h ;
    if (h->NextInCycl == rs) break ;
    }
  return NULL ;
  }

DLLExport BOOL _export WINAPI CompareEqual (LPDBRECORD h, TableRef FAR *tr, int FAR *Id, 
                                            LPVOID FAR *Data, int AnzSegs, int *segsFound)
  {
  for (int i = 0 ; i < AnzSegs ; i++) {
    LPDBRECORD x = FindRecordInCycl (h,&tr[i]) ;
    if (x != NULL) {
      if (*segsFound < i)
        *segsFound = i;
      LPVOID d = x->Get(Id[i]) ;
      if ((Data[i] == NULL) && (d == NULL)) continue ;
      if (d == NULL)        return FALSE ;
      if (Data == NULL)  return FALSE ;
      if (GetBlockSize(Data[i]) != GetBlockSize(d)) return FALSE ;
      if (!lmemcmp (d,Data[i],GetBlockSize(d))) return FALSE ;
      }
    else
      return FALSE ;
    }
  return TRUE ;
  }

LPDBRECORDLIST LastEntry;
RecordList FAR *LastList;
void DBRecordList::UseRecord (DWORD OwnerID,DWORD DocumentID,BOOL doUpdate)
  { 
  isUsed = TRUE ;
  if (rec != NULL) {
    if (!doUpdate)
      rec->AvoidUpdates ();
    rec = GetDBRecordAdmin()->Use(rec,OwnerID,DocumentID);
    }
  }

void DBRecordList::ReleaseRecord (DWORD OwnerID,DWORD DocumentID)
  {
  if (rec != NULL) {
    WIN_ASSERT (rec->IsUsedBy (OwnerID));
    GetDBRecordAdmin()->Release (rec,OwnerID,DocumentID);
    }
  for (OutParam FAR *x = op ; x != NULL ; ) {
    OutParam FAR *n = x->Next;
    if (x->Data != NULL)
      FreeGlobMem (x->Data);
    FreeGlobMem (x);
    x = n;
    }
  op = NULL;
  isUsed = FALSE ;
  }

// Verwaltung der Doppelt verketteten Liste
DLLExport LPDBRECORD _export FAR PASCAL RecordList::AddRecAtTail  (LPDBRECORD rec,LPDBREQUEST req,BOOL doUse)
  {
  LPDBRECORDLIST h = LPDBRECORDLIST (GetGlobMem (sizeof(*h)));
  h->rec      = rec;
  if (req != NULL) {
    h->op = req->op ; // Parameterdaten ebenfalls mitabsprechern
    req->op = NULL ;
    }
  h->Next.ptr = NULL;
  h->Prev.ptr = tail;
  if (tail != NULL) tail->Next.ptr = h , tail->Next.SelectionEnd = FALSE ;
  if (head == NULL) head = h;
  tail = h;
  if (!doUse)
    short k = 0;
  if ((doUse) && (!h->isUsed)) {
    h->UseRecord (LONG(this),DocumentID,doUpdate);
    ExtConnections (h->rec,TRUE);
    if (req != NULL)
      h->oldP = req->SaveOldParams (h->rec);
    }
  LastEntry = h;
  LastList = this;

  return h->rec;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::AddRecAtHead  (LPDBRECORD rec,LPDBREQUEST req,BOOL doUse)
  {
  LPDBRECORDLIST h = LPDBRECORDLIST (GetGlobMem (sizeof(*h)));
  h->rec      = rec;
  if (req != NULL) {
    h->op = req->op ; // Parameterdaten ebenfalls mitabsprechern
    req->op = NULL ;
    }
  h->Next.ptr = head;
  h->Prev.ptr = NULL;
  if (head != NULL) head->Prev.ptr = h , head->Prev.SelectionEnd = FALSE ;
  if (tail == NULL) tail = h;
  head = h;
  if ((doUse) && (!h->isUsed)) {
    h->UseRecord (LONG(this),DocumentID,doUpdate);
    ExtConnections (h->rec,TRUE);
    if (req != NULL)
      h->oldP = req->SaveOldParams (h->rec);
    }
  LastEntry = h;
  LastList = this;

  return h->rec;
  }

  
LPDBRECORDLIST RecordList::FindRec (LPDBRECORD rec)
  {
  if ((LastEntry != NULL) && (LastList == this) && (LastEntry->rec == rec)) {
    return LastEntry;
    }
  for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr) {
    if (h->rec == rec)
      return h;
    }
  return NULL;
  }

LPDBRECORDLIST RecordList::FindRec (OutParam FAR *op)
  {
  if ((LastEntry != NULL) && (LastList == this) && (LastEntry->op == op)) {
    return LastEntry;
    }
  for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr) {
    if (h->op == op)
      return h;
    }
  return NULL;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::FindRec (LPPRIMKEY k)
  {
  if ((LastEntry != NULL) && (LastList == this) && (*(LastEntry->rec->GetPrimKey()) == *k)) {
    return LastEntry->rec;
    }
  for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr)
    if (*(h->rec->GetPrimKey()) == *k) return h->rec;
  return NULL;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::AddRecBehind (LPDBRECORD rec,LPDBRECORD insertafter,LPDBREQUEST req,BOOL doUse)
  {
  LPDBRECORDLIST p = FindRec (insertafter);
  WIN_ASSERT (p != NULL);
  LPDBRECORDLIST h = LPDBRECORDLIST (GetGlobMem (sizeof(*h)));
  h->rec      = rec;
  h->Next.ptr = p->Next.ptr;
  h->Prev.ptr = p ;
  if (p->Next.ptr != NULL) p->Next.ptr->Prev.ptr = h;
  else                     tail = h;
  p->Next.ptr          = h ;
  p->Next.SelectionEnd = FALSE ;
  if ((doUse) && (!h->isUsed)) {
    h->UseRecord (LONG(this),DocumentID,doUpdate);
    ExtConnections (h->rec,TRUE);
    if (req != NULL)
      h->oldP = req->SaveOldParams (h->rec);
    }
  LastEntry = h;
  LastList = this;

  return h->rec;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::AddRecBefore (LPDBRECORD rec,LPDBRECORD insertbefore,LPDBREQUEST req,BOOL doUse)
  {
  LPDBRECORDLIST p = FindRec (insertbefore);
  WIN_ASSERT (p != NULL);
  LPDBRECORDLIST h = LPDBRECORDLIST (GetGlobMem (sizeof(*h)));
  h->rec      = rec;
  h->Next.ptr = p ;
  h->Prev.ptr = p->Prev.ptr ;
  if (p->Prev.ptr != NULL) p->Prev.ptr->Next.ptr = h;
  else                     head = h;
  p->Prev.ptr          = h ;
  p->Prev.SelectionEnd = FALSE ;
  if ((doUse) && (!h->isUsed)) {
    h->UseRecord (LONG(this),DocumentID,doUpdate);
    ExtConnections (h->rec,TRUE);
    if (req != NULL)
      h->oldP = req->SaveOldParams (h->rec);
    }
  LastEntry = h;
  LastList = this;

  return h->rec;
  }

LPVOID CreateKeyBuffer (LPVOID old,LPVOID Data)
  {
  int s1 = GetBlockSize (old);
  int s2 ;
  if (Data != NULL)
    s2 = GetBlockSize (Data);
  else
    s2 = 1 ;
  LPVOID res = GetGlobMem (s1 + s2);
  if (s1 > 0) {
    lmemcpy (res,old,s1);
    FreeGlobMem (old);
    }
  if (Data != NULL) {
    lmemcpy (LPSTR(res) + s1,Data,s2);
    }
  return res ;
  }

DLLExport void _export WINAPI RecordList::RemoveRecFromHashs (LPDBRECORD r)
  {
  // Setzen der ev. vorhandenen Indizierten Elemente
  for (int i = 0 ; i < AnzElesToIndex ; i++) {
    LPVOID Key = r->Get(IndexedElemes[i]) ;
    LPVOID KeyPtr ;
    int KeySize;
    if (Key != NULL) {
      KeyPtr = Key ;
      KeySize = GetBlockSize (KeyPtr);
      }
    else {
      KeyPtr = "";
      KeySize = 1 ;
      }
    eleHash[i]->DelDatav(KeyPtr,KeySize);
    }
  for (i = 0 ; i < AnzSegIndex ; i++) {
    LPVOID KeyBuffer = NULL ;
    for (int j = 0 ; j < AnzSegsInIndex (i) ; j++)
      KeyBuffer = CreateKeyBuffer (KeyBuffer,r->Get(segIndex[i][j]));
    segHash[i]->DelDatav(KeyBuffer,GetBlockSize(KeyBuffer));
    FreeGlobMem (KeyBuffer);
    }
  }

void RecordList::RemoveRecord (LPDBRECORDLIST h)
  {
  WIN_ASSERT (!h->IsUsed());
  // Aus den eventuell vorhandenen Index - Hashtabellen loeschen
  ///////////////////////////////////////////////////////////////
  if (h->rec != NULL) RemoveRecFromHashs (h->rec);
  if ((h->rec == NULL) || (h->rec->UseCount() == 0))
    h->DeleteRecord();
  for (OutParam FAR *x = h->op ; x != NULL ; ) {
    OutParam FAR *n = x->Next;
    if (x->Data != NULL)
      FreeGlobMem (x->Data);
    FreeGlobMem (x);
    x = n;
    }
  h->op = NULL;
  if (h->Prev.ptr != NULL)
    h->Prev.ptr->Next.ptr = h->Next.ptr;
  else
    head = h->Next.ptr;
  if (h->Next.ptr != NULL)
    h->Next.ptr->Prev.ptr = h->Prev.ptr;
  else
    tail = h->Prev.ptr;
  FreeOldParam (h->oldP);
  FreeGlobMem (h);
  if (h == LastEntry) LastEntry = NULL;
  }

// Resultate eintrage
void DBList::AddRecordsAtHead (LPRECBUFFER data)
  {
  LPDBRECORDLIST prev = NULL;
  for (RecBufferLine FAR *h = data->First() ; h != NULL ; h = h->Next) {
    WIN_ASSERT (h->rec[0] != NULL);   // Es darf nur ein Datensatz geliefert 
    WIN_ASSERT (h->rec[1] == NULL);   // werden
    LPDBRECORD nrec;
    if (prev == NULL)
      nrec = AddRecAtHead (h->rec[0],req,TRUE);
    else
      nrec = AddRecBehind (h->rec[0],prev->rec,req,TRUE);
    prev = FindRec (nrec);
    h->rec[0] = NULL;   // Nicht mehr freigeben bitte
    }
  if (req->op != NULL)
    AddRecAtHead (NULL,req,TRUE);
  }

void DBList::AddRecordsAtTail (LPRECBUFFER data)
  {
  for (RecBufferLine FAR *h = data->First() ; h != NULL ; h = h->Next) {
    WIN_ASSERT (h->rec[0] != NULL);   // Es darf nur ein Datensatz geliefert 
    WIN_ASSERT (h->rec[1] == NULL);   // werden
    AddRecAtTail (h->rec[0],req,TRUE);
    h->rec[0] = NULL;   // Nicht mehr freigeben bitte
    }
  if (req->op != NULL)
    AddRecAtTail (NULL,req,TRUE);
  }

LPSTR Raccess (LPSTR a)
  {
  if ((a[0] == 'M') &&
      (a[1] == 'V'))
    return a + 3;
  else
    return a;
  }
DLLHANDLE GetDLLHandleFromAccess (LPSTR a)
  {
  if ((a[0] == 'M') &&
      (a[1] == 'V')) {
    char dllName[4];
    dllName[0] = 'M' ;
    dllName[1] = 'V' ;
    dllName[2] = a[2] ;
    dllName[3] = '\0' ;
    return GetDLLAdmin()->LoadDLL (dllName);
    }
  else
    return GetTransactionDLL();
  }

int DBList::DoDBCall (WORD Op,LPDBRECORD rec)
  {
  if (req == NULL) {
    int AnzElems = (ElesToGet != NULL) ? 
          GetBlockSize(ElesToGet) / sizeof(*ElesToGet) : -1 ;
    if (td != NULL) {
      if (((td->IsInternTable()) || (td->IsTemporaryTable())) && (AnzElems < 0))
        AnzElems = td->GetAnzVars();   // die volle Interne Tabelle
      }
    else
      AnzElems = NULL;
                                     // ....
    req = InitializeRequest (Raccess(access),AnzElems,(order != NULL) ? DBCALLTYPE_GETLIST : DBCALLTYPE_EXTENDED,DocumentID);
    req->StraightForward = StraightForward ;
    if (order != NULL)
      req->SetOrderStatement (order);
    if (td != NULL) {
      if ((td->IsInternTable()) || (td->IsTemporaryTable())) {
        LPINTTABLE ti = LPINTTABLE(td->GetDLLDef());
        for (WORD i = 0 ; i < ti->AnzTables ; i++) {
          LPPTABLE pt = ti->GetTableByNum (i);
          req->AddTableDef (pt->tRef.TableNr,pt->tRef.Version);
          }
        }
      else 
        req->AddTableDef (td->GetTableID(),td->GetVersion());
      req->SetTableID(td->GetTableID(),td->GetVersion());
      }
    if (ElesToGet != NULL) {
      for (int i = 0 ; i < req->AnzElems ; i++)
        req->SetReqElemDirect (i,ElesToGet[i].TableNumber,ElesToGet[i].VarID);
      }
    else if (req->AnzElems > 0) {
      for (int i = 0 ; i < req->AnzElems ; i++) {
        ReqElem d;
        td->GetReqElem (&d,i);
        req->SetReqElemDirect (i,d.TableNumber,d.VarID);
        }
      }
    if (ElesToGet != NULL)      // Die werden jetzt nicht mehr gebraucht
      FreeGlobMem (ElesToGet) , ElesToGet = NULL;
    if (td != NULL)
      DBWIN_ASSERT_TEXT (req->CheckSortVals (),"Sortiersegmente fehlen!");
    }
  else
    if (order != NULL)
      req->SetOrderStatement (order);
  // Setzen des Primaerschluessels, falls vorhanden
  if (rec != NULL) {
    LPPRIMKEY k = rec->GetPrimKey ();
    req->SetParam (0,k->Data,GetBlockSize (k->Data));
    rec->SetSortVals (req);
    for (int i = 2 ; i < CB_PARAM ; i++) {
      if (pb.ptr[i-2] != NULL)
        req->SetParam(i,pb.ptr[i-2],GetBlockSize(pb.ptr[i-2]));
      req->SetParamType(i,pb.pType[i-2]);
      }
    }
  else {
    // Setzen der Tabellennummer
    if (td != NULL) {
      WORD TableID = td->GetTableID();
      req->SetParam (1,&TableID,sizeof(TableID));
      }
    for (int i = 2 ; i < CB_PARAM ; i++) {
      if (req->Param[i] != NULL) FreeGlobMem (req->Param[i]) , req->Param[i] = NULL;
      if (pb.ptr[i-2] != NULL)
        req->SetParam(i,pb.ptr[i-2],GetBlockSize(pb.ptr[i-2]));
      req->SetParamType(i,pb.pType[i-2]);
      }
    req->AnzParam = pb.AnzPars + 1;
    }
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  DLLHANDLE dh;
  if (td != NULL) dh = req->GetDLLHandle();
  else {
    dh = GetDLLHandleFromAccess(access);
    }
  BeginErrorHandling (ErrorCBP,dh);
  int res = GetDLLAdmin()->GetDLLEntry(dh)->DBCall (Op,cGet,req,&hstmt,&rb);
  EndErrorHandling (ErrorCBP,dh);
  if ((res == DBCALL_ENDOFFILE) || (res == DBCALL_SUCCESS)) {
    switch (Op) {
      case DBOP_GETFIRST  :
        AddRecordsAtTail (&rb);
        MarkHeadAsEnd ();
        if (res == DBCALL_ENDOFFILE) MarkTailAsEnd ();
        break ;
      case DBOP_GETLAST   :
        AddRecordsAtTail (&rb);
        MarkTailAsEnd ();
        if (res == DBCALL_ENDOFFILE) MarkHeadAsEnd ();
        break ;
      case DBOP_GETNEXT   :
        AddRecordsAtTail (&rb);
        if (res == DBCALL_ENDOFFILE) MarkTailAsEnd ();
        break ;
      case DBOP_GETPREV   :
        AddRecordsAtHead (&rb);
        if (res == DBCALL_ENDOFFILE) MarkHeadAsEnd ();
        break ;
      case DBOP_GET       :
        AddRecordsAtTail (&rb);
        if (res == DBCALL_ENDOFFILE) MarkTailAsEnd ();
        break ;
      }
    rb.Clear ();
    }
  req->ClearParams();
  return res;
  }

DLLExport void _export FAR PASCAL DBList::AddElemsToGet (WORD FAR *VarId,int AnzVars)
  {
  WORD oDim;
  if (ElesToGet != NULL) oDim = GetBlockSize (ElesToGet) / sizeof(*ElesToGet);
  else                   oDim = 0;
  LPREQELEM n = LPREQELEM(GetGlobMem ((oDim + AnzVars) * sizeof(*n)));
  if (ElesToGet != NULL) lmemcpy (n,ElesToGet,GetBlockSize(ElesToGet)) ,
                         FreeGlobMem (ElesToGet);
  ElesToGet = n;
  for (int i = 0 ; i < AnzVars ; i++)
    td->GetReqElem (ElesToGet+i+oDim,VarId[i]);
  }

//////////////////////////////////////////////////////////////////
//  Schnittstelle nach aussen
//////////////////////////////////////////////////////////////////
DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetFirstActive ()
  {
  for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr)
    if (h->IsUsed()) break;
  return (h != NULL) ? h->rec : NULL ;
  }

DLLExport OutParam FAR *_export FAR PASCAL RecordList::GetFirstActiveParam ()
  {
  LPDBRECORDLIST h = head ;
  return (h != NULL) ? h->op : NULL ;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetLastActive ()
  {
  for (LPDBRECORDLIST h = tail ; h != NULL ; h = h->Prev.ptr)
    if (h->IsUsed()) break;
  return (h != NULL) ? h->rec : NULL ;
  }

DLLExport OutParam FAR *_export FAR PASCAL RecordList::GetLastActiveParam ()
  {
  LPDBRECORDLIST h = tail ;
  return (h != NULL) ? h->op : NULL ;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetNextActive (LPDBRECORD rec)
  {
  LPDBRECORDLIST h = FindRec(rec);
  if (h != NULL) {
    h = h->Next.ptr ;
    LastEntry = h;
    LastList = this;
    return ((h != NULL) && (h->IsUsed())) ? h->rec : NULL ;
    }
  else
    return NULL;
  }

DLLExport OutParam FAR *_export FAR PASCAL RecordList::GetNextActiveParam (OutParam FAR *op)
  {
  LPDBRECORDLIST h = FindRec(op);
  if (h != NULL) {
    h = h->Next.ptr ;
    LastEntry = h;
    LastList = this;
    return ((h != NULL) && (h->IsUsed())) ? h->op : NULL ;
    }
  else
    return NULL;
  }

void DBList::TestRes (int res)
  {
  char outtxt[64];
  LPSTR Nm;
  if (td != NULL) Nm = td->GetName();
  else            Nm = "??" ;
  if (res == DBCALL_ERROR) {
    wsprintf (outtxt,"DBCALL_ERROR on %s",Nm);
    WIN_ASSERT_TEXT (FALSE,outtxt);
    }
  else if (res == DBCALL_ERROR_NOACCESS) {
    wsprintf (outtxt,"DBCALL_NOACCESS: %s not defined in %s",access,Nm);
    WIN_ASSERT_TEXT (FALSE,outtxt);
    }
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetFirst  ()
  {
  if (head != NULL) {
    if (!head->IsUsed()) {
      head->UseRecord(LONG(this),DocumentID,doUpdate);
      ExtConnections (head->rec,TRUE);
      }
    LastEntry = head;
    LastList = this;
    return head->rec;
    }
  else
    return NULL ;
  }

DLLExport LPDBRECORD _export FAR PASCAL DBList::GetFirst  ()
  {
  LPDBRECORD res;
  if ((head != NULL) && (head->Prev.SelectionEnd)) {
    if (!head->IsUsed()) {
      head->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (head->rec,TRUE);
      if (req != NULL)
        head->oldP = req->SaveOldParams (head->rec);
      }
    LastEntry = head;
    LastList = this;
    res = head->rec;
    }
  else {
    // Pech gehabt
    ThrowList ();
    TestRes (DoDBCall (DBOP_GETFIRST));
    if (head != NULL) {
      if (!head->isUsed) {
        head->UseRecord(LONG (this),DocumentID,doUpdate);
        ExtConnections (head->rec,TRUE);
        if (req != NULL)
          head->oldP = req->SaveOldParams (head->rec);
        }
      LastEntry = head;
      LastList = this;
      res = head->rec;
      }
    else
      res = NULL;
    }
  return res;
  }

DLLExport OutParam FAR * _export FAR PASCAL DBList::GetFirstParam ()
  {
  OutParam FAR *res;
  if ((head != NULL) && (head->Prev.SelectionEnd)) {
    if (!head->IsUsed()) {
      head->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (head->rec,TRUE);
      if (req != NULL)
        head->oldP = req->SaveOldParams (head->rec);
      }
    LastEntry = head;
    LastList = this;
    res = head->op;
    }
  else {
    // Pech gehabt
    ThrowList ();
    TestRes (DoDBCall (DBOP_GETFIRST));
    if (head != NULL) {
      if (!head->isUsed) {
        head->UseRecord(LONG (this),DocumentID,doUpdate);
        ExtConnections (head->rec,TRUE);
        if (req != NULL)
          head->oldP = req->SaveOldParams (head->rec);
        }
      LastEntry = head;
      LastList = this;
      res = head->op;
      }
    else
      res = NULL;
    }
  return res;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetLast  ()
  {
  if (tail != NULL) {
    if (!tail->IsUsed()) {
      tail->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (tail->rec,TRUE);
      }
    LastEntry = tail;
    LastList = this;
    return tail->rec;
    }
  else
    return NULL ;
  }

DLLExport LPDBRECORD _export FAR PASCAL DBList::GetLast   ()
  {
  LPDBRECORD res;
  if ((tail != NULL) && (tail->Next.SelectionEnd)) {
    LastEntry = tail;
    LastList = this;
    if (!tail->IsUsed()) {
      tail->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (tail->rec,TRUE);
      if (req != NULL)
        tail->oldP = req->SaveOldParams (tail->rec);
      }
    res = tail->rec;
    }
  else {
    // Pech gehabt
    ThrowList ();
    TestRes (DoDBCall (DBOP_GETLAST));
    if (tail != NULL) {
      if (!tail->isUsed) {
        tail->UseRecord(LONG (this),DocumentID,doUpdate);
        ExtConnections (tail->rec,TRUE);
        if (req != NULL)
          tail->oldP = req->SaveOldParams (tail->rec);
        }
      LastEntry = tail;
      LastList = this;
      res = tail->rec;
      }
    else
      res = NULL;
    }
  return res;
  }

DLLExport OutParam FAR * _export FAR PASCAL DBList::GetLastParam ()
  {
  OutParam FAR *res;
  if ((tail != NULL) && (tail->Next.SelectionEnd)) {
    LastEntry = tail;
    LastList = this;
    if (!tail->IsUsed()) {
      tail->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (tail->rec,TRUE);
      if (req != NULL)
        tail->oldP = req->SaveOldParams (tail->rec);
      }
    res = tail->op;
    }
  else {
    // Pech gehabt
    ThrowList ();
    TestRes (DoDBCall (DBOP_GETLAST));
    if (tail != NULL) {
      if (!tail->isUsed) {
        tail->UseRecord(LONG (this),DocumentID,doUpdate);
        ExtConnections (tail->rec,TRUE);
        if (req != NULL)
          tail->oldP = req->SaveOldParams (tail->rec);
        }
      LastEntry = tail;
      LastList = this;
      res = tail->op;
      }
    else
      res = NULL;
    }
  return res;
  }

DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetNext (LPDBRECORD rec)
  {
  LPDBRECORDLIST n = FindRec (rec);
  WIN_ASSERT (n != NULL);
  if (n->Next.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Next.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->rec);
    LastEntry = h;
    LastList = this;
    return h->rec;
    }
  else
    return NULL ;
  }
DLLExport LPDBRECORD _export FAR PASCAL DBList::GetNext (LPDBRECORD rec)
  {
  LPDBRECORD res;
  LPDBRECORDLIST n = FindRec (rec);
  WIN_ASSERT (n != NULL);
  if (n->Next.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Next.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      if (req != NULL)
        h->oldP = req->SaveOldParams (h->rec);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->rec);
    LastEntry = h;
    LastList = this;
    res = h->rec;
    }
  else {
    if (n->Next.SelectionEnd)
      res = NULL;     // Da is nix mehr
    else {
      TestRes (DoDBCall (DBOP_GETNEXT,n->rec));
      if (n->Next.ptr != NULL) {
        LPDBRECORDLIST h = n->Next.ptr;
        if (!h->isUsed) {
          h->UseRecord(LONG (this),DocumentID,doUpdate);
          ExtConnections (h->rec,TRUE);
          if (req != NULL)
            h->oldP = req->SaveOldParams (h->rec);
          }
        if (n->ShouldBeDeleted)
          ThrowRecord (n->rec);
        LastEntry = h;
        LastList = this;
        res = h->rec;
        }
      else
        res = NULL ;
      }
    }
  return res;
  }
DLLExport OutParam FAR *_export FAR PASCAL DBList::GetNextParam (OutParam FAR *op)
  {
  OutParam FAR *res;
  LPDBRECORDLIST n = FindRec (op);
  WIN_ASSERT (n != NULL);
  if (n->Next.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Next.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      if (req != NULL)
        h->oldP = req->SaveOldParams (h->rec);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->op);
    LastEntry = h;
    LastList = this;
    res = h->op;
    }
  else {
    if (n->Next.SelectionEnd)
      res = NULL;     // Da is nix mehr
    else {
      TestRes (DoDBCall (DBOP_GETNEXT,n->rec));
      if (n->Next.ptr != NULL) {
        LPDBRECORDLIST h = n->Next.ptr;
        if (!h->isUsed) {
          h->UseRecord(LONG (this),DocumentID,doUpdate);
          ExtConnections (h->rec,TRUE);
          if (req != NULL)
            h->oldP = req->SaveOldParams (h->rec);
          }
        if (n->ShouldBeDeleted)
          ThrowRecord (n->op);
        LastEntry = h;
        LastList = this;
        res = h->op;
        }
      else
        res = NULL ;
      }
    }
  return res;
  }
DLLExport LPDBRECORD _export FAR PASCAL RecordList::GetPrev (LPDBRECORD rec)
  {
  LPDBRECORDLIST n = FindRec (rec);
  WIN_ASSERT (n != NULL);
  if (n->Prev.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Prev.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->rec);
    LastEntry = h;
    LastList = this;
    return h->rec;
    }
  else {
    return NULL;
    }
  }
DLLExport LPDBRECORD _export FAR PASCAL DBList::GetPrev (LPDBRECORD rec)
  {
  LPDBRECORD res;
  LPDBRECORDLIST n = FindRec (rec);
  WIN_ASSERT (n != NULL);
  if (n->Prev.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Prev.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      if (req != NULL)
        h->oldP = req->SaveOldParams (h->rec);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->rec);
    LastEntry = h;
    LastList = this;
    res = h->rec;
    }
  else {
    if (n->Prev.SelectionEnd)
      res = NULL;     // Da is nix mehr
    else {
      TestRes (DoDBCall (DBOP_GETPREV,n->rec));
      if (n->Prev.ptr != NULL) {
        LPDBRECORDLIST h = n->Prev.ptr;
        if (!h->isUsed) {
          h->UseRecord(LONG(this),DocumentID,doUpdate);
          ExtConnections (h->rec,TRUE);
          if (req != NULL)
            h->oldP = req->SaveOldParams (h->rec);
          }
        if (n->ShouldBeDeleted)
          ThrowRecord (n->rec);
        LastEntry = h;
        LastList = this;
        res = h->rec;
        }
      else
        res = NULL ;
      }
    }
  return res;
  }
DLLExport OutParam FAR * _export FAR PASCAL DBList::GetPrevParam (OutParam FAR *op)
  {
  OutParam FAR *res;
  LPDBRECORDLIST n = FindRec (op);
  WIN_ASSERT (n != NULL);
  if (n->Prev.ptr != NULL) {
    // Schon da
    LPDBRECORDLIST h = n->Prev.ptr;
    if (!h->IsUsed()) {
      h->UseRecord(LONG (this),DocumentID,doUpdate);
      ExtConnections (h->rec,TRUE);
      if (req != NULL)
        h->oldP = req->SaveOldParams (h->rec);
      }
    if (n->ShouldBeDeleted)
      ThrowRecord (n->op);
    LastEntry = h;
    LastList = this;
    res = h->op;
    }
  else {
    if (n->Prev.SelectionEnd)
      res = NULL;     // Da is nix mehr
    else {
      TestRes (DoDBCall (DBOP_GETPREV,n->rec));
      if (n->Prev.ptr != NULL) {
        LPDBRECORDLIST h = n->Prev.ptr;
        if (!h->isUsed) {
          h->UseRecord(LONG(this),DocumentID,doUpdate);
          ExtConnections (h->rec,TRUE);
          if (req != NULL)
            h->oldP = req->SaveOldParams (h->rec);
          }
        if (n->ShouldBeDeleted)
          ThrowRecord (n->op);
        LastEntry = h;
        LastList = this;
        res = h->op;
        }
      else
        res = NULL ;
      }
    }
  return res;
  }

DLLExport LPDBRECORD _export FAR PASCAL DBList::Get (LPPARAM Params)
  {
  WIN_ASSERT (FALSE);
  return NULL;
  }

// Daten wieder freigeben
////////////////////////////////
void RecordList::ClearCached ()
  {
  if (cCache <= 0) return ;
  LPDBRECORD r = GetFirstActive ();
  if (r != NULL) {
    LPDBRECORDLIST h = FindRec (r);
    // Alle am Beginn der Liste loeschen
    int c = 0;
    for ( h = h->Prev.ptr ; h != NULL ; ) {
      WIN_ASSERT (!h->IsUsed());
      LPDBRECORDLIST p = h->Prev.ptr;
      if (c++ >= cCache)
        RemoveRecord (h);
      h = p;
      }

    r = GetLastActive ();
    h = FindRec (r);
    // Alle am Ende der Liste loeschen
    c = 0;
    for ( h = h->Next.ptr ; h != NULL ; ) {
      WIN_ASSERT (!h->IsUsed());
      LPDBRECORDLIST n = h->Next.ptr;
      if (c++ >= cCache)
        RemoveRecord (h);
      h = n;
      }
    }
  else {
    int c = 0;
    for (LPDBRECORDLIST h = head ; h != NULL ; ) {
      WIN_ASSERT (!h->IsUsed());
      LPDBRECORDLIST n = h->Next.ptr;
      if (c++ >= cCache)
        RemoveRecord (h);
      h = n;
      }
    }
  }

DLLExport void _export FAR PASCAL RecordList::ThrowRecord (LPDBRECORD rec)
  {
  LPDBRECORDLIST h = FindRec (rec);
  if (h != NULL) {
    ExtConnections (h->rec,FALSE);
    h->ReleaseRecord (LONG (this),DocumentID);
    RemoveRecord (h);
    }
  }

DLLExport void _export FAR PASCAL RecordList::ThrowRecord (OutParam FAR *op)
  {
  LPDBRECORDLIST h = FindRec (op);
  if (h != NULL) {
    ExtConnections (h->rec,FALSE);
    h->ReleaseRecord (LONG (this),DocumentID);
    RemoveRecord (h);
    }
  }

DLLExport void _export FAR PASCAL RecordList::ThrowAtHead (LPDBRECORD rec)
  {
  LPDBRECORDLIST f = FindRec (rec);
  WIN_ASSERT ((f != NULL) && (f->IsUsed()));
  for (LPDBRECORDLIST h = f->Prev.ptr ; h != NULL ; )
    if (h->IsUsed()) { 
      ExtConnections (h->rec,FALSE);
      h->ReleaseRecord (LONG (this),DocumentID);
      LPDBRECORDLIST n = h->Next.ptr;
      RemoveRecord (h);
      n = h;
      }
    else             break ;
  }

DLLExport void _export FAR PASCAL RecordList::ThrowAtHeadParam (OutParam FAR *op)
  {
  LPDBRECORDLIST f = FindRec (op);
  WIN_ASSERT ((f != NULL) && (f->IsUsed()));
  for (LPDBRECORDLIST h = f->Prev.ptr ; h != NULL ; )
    if (h->IsUsed()) { 
      ExtConnections (h->rec,FALSE);
      h->ReleaseRecord (LONG (this),DocumentID);
      LPDBRECORDLIST n = h->Next.ptr;
      RemoveRecord (h);
      n = h;
      }
    else             break ;
  }

DLLExport void _export FAR PASCAL RecordList::ThrowAtTail (LPDBRECORD rec)
  {
  LPDBRECORDLIST f = FindRec (rec);
  WIN_ASSERT ((f != NULL) && (f->IsUsed()));
  for (LPDBRECORDLIST h = f->Next.ptr ; h != NULL ; )
    if (h->IsUsed()) {
      ExtConnections (h->rec,FALSE);
      h->ReleaseRecord (LONG (this),DocumentID);
      LPDBRECORDLIST n = h->Next.ptr;
      RemoveRecord (h);
      n = h;
      }
    else             break ;
  }

DLLExport void _export FAR PASCAL RecordList::ThrowList ()
  {
  for (LPDBRECORDLIST h = head ; h != NULL ; h = head) {
    if (h->IsUsed()) {
      ExtConnections (h->rec,FALSE);
      h->ReleaseRecord (LONG (this),DocumentID);
      }
    RemoveRecord (h);
    }
  }

DLLExport void _export FAR PASCAL RecordList::ThrowFirstUsed()
  {
  ThrowRecord (GetFirstActive());
  }

DLLExport void _export FAR PASCAL RecordList::ThrowLastUsed()
  {
  ThrowRecord (GetLastActive());
  }

DLLExport BOOL _export FAR PASCAL RecordList::IsMoreOnHead()
  {
  LPDBRECORDLIST h = FindRec(GetFirstActive());
  if ((h != NULL) && ((h->Prev.ptr != NULL) || (!h->Prev.SelectionEnd))) return TRUE ;
  else                                                  return FALSE ;
  }

DLLExport BOOL _export FAR PASCAL RecordList::IsMoreOnTail()
  {
  LPDBRECORDLIST h = FindRec(GetLastActive());
  if ((h != NULL) && ((h->Next.ptr != NULL) || (!h->Next.SelectionEnd))) return TRUE ;
  else                                                  return FALSE ;
  }

void FreeParamCopy (LPPARAM p)
  {
  for (int i = 0 ; i < p->AnzPars ; i++) {
    if (p->ptr[i] != NULL) 
      FreeGlobMem (p->ptr[i]);
    p->ptr[i] = NULL ;
    }
  p->AnzPars = 0 ;
  }
void GetParamCopy (LPPARAM p1,LPPARAM p2)
  {
  for (int i = 0 ; i < p2->AnzPars ; i++) {
    if (p2->ptr[i] != NULL) {
      p1->ptr[i] = GetGlobMem (GetBlockSize(p2->ptr[i]));
      lmemcpy (p1->ptr[i],p2->ptr[i],GetBlockSize(p2->ptr[i]));
      }
    p1->pType[i] = p2->pType[i];
    }
  p1->AnzPars = p2->AnzPars ;
  }
DLLExport void _export FAR PASCAL DBList::SetParams (LPPARAM Params)
  {
  FreeParamCopy (&pb);
  if (Params != NULL) {
    GetParamCopy (&pb,Params);
    }
  if (req != NULL) {
    for (int i = 2 ; i < CB_PARAM ; i++) {
      if (pb.ptr[i-2] != NULL)
        req->SetParam(i,pb.ptr[i-2],GetBlockSize(pb.ptr[i-2]));
      req->SetParamType(i,pb.pType[i-2]);
      }
    req->AnzParam = pb.AnzPars + 1;
    }
  }
  
DLLExport void _export FAR PASCAL DBList::RefreshJoins (LPVOID FAR *ExtParams,int AnzExtra)
  {
  // Von allen Records in der (aktuellen) Liste die Joins neu setzen
  for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr) {
    if ((req != NULL) && (req->foreignDone)) {
      for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
        h->rec->RefreshJoin (req,i,ExtParams,AnzExtra,h->oldP);
        }
      }
    }
  }

DLLExport _export FAR PASCAL RecordList::RecordList (LPTABLEDEF tb,DWORD Id,int RecsToCache,BOOL Update)
  {
  // Die Tabelle auf jeden Fall Noch mal verwenden
  if (tb != NULL) GetTableAdmin()->GetTableDef (tb->GetTableID(),tb->GetVersion());
  td         = tb;
  cCache     = RecsToCache;
  DocumentID = Id;
  // DocumentID = LONG(this);
  doUpdate = Update;
  // Hashtabellen aufbaueen
  int IId[64];
  int HD[64];
  #define MAXSEGINDEX 7
  int SIId[MAXSEGINDEX][8];
  int SHD[MAXSEGINDEX];
  int SIIdLen[MAXSEGINDEX];
  for (int i = 0 ; i < MAXSEGINDEX ; i++)
    SIIdLen[i] = 0 ;
  int indNr;
  if (tb != NULL) {
    if (tb->IsGlobalTable()) {
      for (i = 0 ; i < tb->GetAnzVars () ; i++) {
        if (tb->GetVarDef(i)->Property & (VPROP_INDEXED | VPROP_LINDEXED)) {
          if ((indNr = IndexNummer(tb->GetVarDef(i)->Property)) > 0) {
            if (indNr > AnzSegIndex)
              AnzSegIndex = indNr ;
            SIId[indNr-1][SIIdLen[indNr-1] ++] = i ;
            if (tb->GetVarDef(i)->Property & (VPROP_INDEXED))
              SHD[indNr-1] = 29 ;
            else
              SHD[indNr-1] = 257 ;
            }
          else {
            if (tb->GetVarDef(i)->Property & (VPROP_INDEXED))
              HD[AnzElesToIndex] = 29 ;
            else
              HD[AnzElesToIndex] = 257 ;
            IId[AnzElesToIndex ++] = i ;
            }
          }
        }
      }
    }

  if (AnzElesToIndex > 0) {
    eleHash = (hash FAR * FAR *) GetGlobMem (sizeof(hash FAR *) * AnzElesToIndex);
    for (int i = 0 ; i < AnzElesToIndex ; i++)
      eleHash[i] = new hash (HD[i],VOIDKEY);
    IndexedElemes = (int FAR *) GetGlobMem (sizeof(int) * AnzElesToIndex);
    lmemcpy (IndexedElemes,IId,sizeof(int) * AnzElesToIndex);
    }
  if (AnzSegIndex > 0) {
    segHash = (hash FAR * FAR *) GetGlobMem (sizeof(hash FAR *) * AnzSegIndex);
    for (int i = 0 ; i < AnzSegIndex ; i++)
      segHash[i] = new hash (SHD[i],VOIDKEY);
    segIndex = (int FAR * FAR *) GetGlobMem (sizeof(int FAR *) * AnzSegIndex);
    for (i = 0 ; i < AnzSegIndex ; i++) {
      segIndex[i] = (int FAR *) GetGlobMem (sizeof(int) * SIIdLen[i]) ;
      lmemcpy (segIndex[i],SIId[i],sizeof(int) * SIIdLen[i]);
      }
    }
  }

DLLExport _export FAR PASCAL DBList::DBList (LPTABLEDEF tb,DWORD Id,LPSTR AccessName,int AnzRecsToGet,int RecsToCache,LPPARAM Params,BOOL Update)
      : RecordList (tb,Id,RecsToCache,Update)
  {
  access     = LPSTR(GetGlobMem (lstrlen(AccessName)+1));
  lstrcpy (access,AccessName);
  cGet       = AnzRecsToGet;
  if (Params != NULL)
    GetParamCopy (&pb,Params);
  ErrorCBP = GetLastErrorCBP();
  }

void RecordList::ExtConnections (LPDBRECORD r,BOOL doSet)
  {
  if (r == NULL) return;
  if (doSet) {
    // Setzen der ev. vorhandenen Indizierten Elemente
    for (int i = 0 ; i < AnzElesToIndex ; i++) {
      LPVOID Key = r->Get(IndexedElemes[i]) ;
      LPVOID KeyPtr ;
      int KeySize;
      if (Key != NULL) {
        KeyPtr = Key ;
        KeySize = GetBlockSize (KeyPtr);
        }
      else {
        KeyPtr = "";
        KeySize = 1 ;
        }
      eleHash[i]->SetDatav(KeyPtr,&r,sizeof(r),KeySize);
      }
    for (i = 0 ; i < AnzSegIndex ; i++) {
      LPVOID KeyBuffer = NULL ;
      for (int j = 0 ; j < AnzSegsInIndex (i) ; j++)
        KeyBuffer = CreateKeyBuffer (KeyBuffer,r->Get(segIndex[i][j]));
      segHash[i]->SetDatav(KeyBuffer,&r,sizeof(r),GetBlockSize(KeyBuffer));
      FreeGlobMem (KeyBuffer);
      }
    }
  }

DLLExport LPDBRECORD _export WINAPI 
  RecordList::FindRecord (TableRef FAR *tr,int FAR *Id,LPVOID FAR *Data,int AnzSegs, int Mode)
  {
  BOOL done = FALSE ;
  BOOL isSeg;
  int segNr;
  if (IsHashed (tr,Id,AnzSegs,&isSeg,&segNr)) {
    if (!isSeg) {
      LPVOID cmpPtr ;
      int cmpSize;
      if (Data[0] == NULL) {
        cmpPtr = "" ;
        cmpSize = 1 ;
        }
      else {
        cmpPtr = Data[0] ;
        cmpSize = GetBlockSize(cmpPtr);
        }
      LPDBRECORD FAR *res = (LPDBRECORD FAR *) eleHash[segNr]->GetDatav(cmpPtr,cmpSize);
      if (res != NULL) return *res;
      else             return NULL ;
      }
    else {
      LPVOID KeyBuffer = NULL ;
      for (int j = 0 ; j < AnzSegs ; j++)
        KeyBuffer = CreateKeyBuffer (KeyBuffer,Data[j]);

      LPDBRECORD FAR *res = (LPDBRECORD FAR *) segHash[segNr]->GetDatav(KeyBuffer,GetBlockSize(KeyBuffer));
      FreeGlobMem (KeyBuffer);
      if (res != NULL) return *res;
      else             return NULL ;
      }
    }
  else {
    // Normales Suchen
    LPDBRECORD res = NULL;
    int segsFound = -1;
    for ( LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr ) {
      BOOL correct = TRUE ;
      if (CompareEqual (h->rec, tr, Id, Data, AnzSegs, &segsFound)) {
        res = h->rec ;
        if (Mode == FIND_FIRST)
          break;
        }
      }
    if (res == NULL) {
      DBWIN_ASSERT_TEXT (CheckSegments (tr, AnzSegs, segsFound),"Falsches Segment!");
      }
    return res;
    }
  }

DLLExport BOOL _export FAR PASCAL RecordList::IsHashed (TableRef FAR *tr,int FAR *Id,int AnzSegs,
                                                        BOOL FAR *isSeg, int FAR *segNr)
  {
  if (AnzSegs == 1) {
    if ((tr[0].TableNr != td->GetTableID()) || (tr[0].Version != td->GetVersion())) 
      return FALSE ; // wenn gesuchtes Segment nicht in Basisstruct => sicher kein Index
    for (int i = 0 ; i < AnzElesToIndex ; i++) {
      if (Id[0] == IndexedElemes[i])  {
        if (isSeg != NULL)
          *isSeg = FALSE;
        if (segNr != NULL)
          *segNr = i;
        return TRUE ;
        }
      }
    }
  // Suchen eines passenden Index
  for (int i = 0 ; i < AnzSegIndex ; i++) {
    if (AnzSegs == AnzSegsInIndex (i)) {
      BOOL found = TRUE ;
      for (int j = 0 ; ((j < AnzSegs) && (found)) ; j++) {
        if ((tr[j].TableNr != td->GetTableID()) || (tr[j].Version != td->GetVersion())) 
          return FALSE ; // wenn ein gesuchtes Segment nicht in Basisstruct => sicher kein Index
        if (Id[j] != segIndex[i][j])
          found = FALSE ; // der nicht
        }
      if (found) {
        if (isSeg != NULL)
          *isSeg = TRUE;
        if (segNr != NULL)
          *segNr = i;
        return TRUE ;
        }
      }
    }
  return FALSE;
  }

LPTABLEDEF GetUltimateParent (LPTABLEDEF FAR *td)

  {
  TableRef x;
  for ( x.TableNr = (*td)->GetParentID(), x.Version = (*td)->GetParentVersion(); 
        x.TableNr != 0; 
        x.TableNr = (*td)->GetParentID(), x.Version = (*td)->GetParentVersion()) {
    GetTableAdmin()->FreeTable ((*td)->GetTableID(),(*td)->GetVersion());
    *td = GetTableAdmin()->GetTableDef (x.TableNr,x.Version);
    }
  return *td;
  }

DLLExport BOOL _export WINAPI
  RecordList::CheckSegments (TableRef FAR *tr, int AnzSegs, int alreadyChecked)

  {
  BOOL res = TRUE;
  // Segmente pruefen, ob nicht falsche (=nicht von Listenstruktur abgeleitete) Struktur angegeben
  LPTABLEDEF listTable = GetTableAdmin()->GetTableDef (GetTableDef()->GetTableID(), 
                                                       GetTableDef()->GetVersion());
  GetUltimateParent (&listTable);
  for (int i = alreadyChecked + 1; res && (i < AnzSegs); i++) {
    LPTABLEDEF compareTable = GetTableAdmin()->GetTableDef (tr[i].TableNr, tr[i].Version);
    if (listTable != GetUltimateParent (&compareTable))
      res = FALSE;
    GetTableAdmin()->FreeTable (compareTable->GetTableID(), compareTable->GetVersion());
    }
  GetTableAdmin()->FreeTable (listTable->GetTableID(), listTable->GetVersion());
  return res;
  }

DLLExport void _export FAR PASCAL RecordList::SetConnectionInfo (LPVOID ca,LPVOID cc)
  {
  }

DLLExport void _export FAR PASCAL DBList::SetConnectionInfo (LPVOID ca,LPVOID cc)
  {
  ConnectionAddress = ca;
  if (cc != NULL) {
    _ccount = GetGlobMem (GetBlockSize(cc));
    lmemcpy (_ccount,cc,GetBlockSize(cc));
    }
  }

void DBList::ExtConnections (LPDBRECORD r,BOOL doSet)
  {
  if (r == NULL) return ;
  if ((!doUpdate) || (ConnectionAddress == NULL)) return ;

  if ((req != NULL) && (req->foreignDone)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (req->fdsc[i].freq != NULL) {
        for (WORD j = 0 ; ((j < MANZSEGS) && (r != NULL)) ; j++) {
          if (req->fdsc[i].VarID[j] != 0xFFFF) {
            if (doSet) r->SetConnection (LONG(this),req->fdsc[i].VarID[j],
                            DocumentID,ConnectionAddress,
                            LPCMDCOUNT (_ccount)
                                        );
            else       r->ClearConnection (LONG(this),req->fdsc[i].VarID[j],
                            DocumentID,ConnectionAddress
                                        );
            }
          }
        }
      }
    }
  }

DLLExport BOOL _export FAR PASCAL RecordList::ExtUpdate ()
  {
  return FALSE ;
  }
DLLExport BOOL _export FAR PASCAL DBList::ExtUpdate ()
  {
  BOOL done = FALSE ;
  if (!doUpdate) return FALSE;
  if ((req != NULL) && (req->foreignDone)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (req->fdsc[i].freq != NULL) {
        for (LPDBRECORDLIST h = head ; h != NULL ; h = h->Next.ptr) {
          LPDBRECORD r = h->rec;
          if ((h->oldP != NULL) && (req->IsUpdateDone (r,i,h->oldP))) {
            r->RefreshJoin (req,i,pb.ptr,CB_PARAM-2,h->oldP);
            done = TRUE ;
            }
          }
        }
      }
    }
  return done ;
  }

DLLExport _export FAR PASCAL DBList::~DBList ()
  {
  if (hstmt != NULL) {
    DLLHANDLE hd;
    if (td != NULL) hd = req->GetDLLHandle();
    else            hd = GetDLLHandleFromAccess (access);
    GetDLLAdmin()->GetDLLEntry(hd)->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
    }
  ThrowList ();
  if (req != NULL) {
    req->ClearForeign();
    req->FreeTableDefs();
    FreeRequest (req);
    }
  if (ElesToGet != NULL)
    FreeGlobMem (ElesToGet) ;
  FreeGlobMem (access);
  if (_ccount != NULL)
    FreeGlobMem (_ccount);
  FreeParamCopy (&pb);
  if (ErrorCBP != NULL)
    FreeGlobMem (ErrorCBP);
  }

DLLExport _export FAR PASCAL RecordList::~RecordList ()
  {
  ThrowList ();
  if (order != NULL)
    FreeGlobMem (order);
  if (eleHash != NULL) {
    for (int i = 0 ; i < AnzElesToIndex ; i++) {
      delete eleHash[i] ;
      }
    FreeGlobMem (eleHash);
    FreeGlobMem (IndexedElemes) ;
    }
  if (segHash != NULL) {
    for (int i = 0 ; i < AnzSegIndex ; i++) {
      delete segHash[i] ;
      FreeGlobMem (segIndex[i]);
      }
    FreeGlobMem (segHash);
    FreeGlobMem (segIndex) ;
    }
  if (td != NULL) GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
  }

#define MAXSORTRECS 2048
static DBRecordList FAR *FAR *slptr;
static int _AnzSegsToSort;
static int FAR *_VarInd;
static TableRef FAR *_VarRef;
static int _dir;
int NoCompare (LPVOID s1,LPVOID s2)
  {
  WIN_ASSERT (FALSE);
  return 0 ;
  }

int CompareString (LPVOID s1,LPVOID s2)
  {
  LPSTR r1 = LPSTR (GetGlobMem (GetBlockSize(s1))) ;
  lstrcpy (r1,LPSTR(s1));
  AnsiUpper (r1);
  LPSTR r2 = LPSTR (GetGlobMem (GetBlockSize(s2))) ;
  lstrcpy (r2,LPSTR(s2));
  AnsiUpper (r2);
  int res = lstrcmp (r1,r2);
  FreeGlobMem (r1);
  FreeGlobMem (r2);
  return res ;
  }

int CompareLong (LPVOID s1,LPVOID s2)
  {
  if (* (LONG FAR *) s1 > *(LONG FAR *) s2) return 1;
  if (* (LONG FAR *) s1 < *(LONG FAR *) s2) return -1 ;
  return 0 ;
  }

int CompareShort (LPVOID s1,LPVOID s2)
  {
  if (* (short FAR *) s1 > *(short FAR *) s2) return 1 ;
  if (* (short FAR *) s1 < *(short FAR *) s2) return -1 ;
  return 0 ;
  }

int CompareFloat (LPVOID s1,LPVOID s2)
  {
  if (* (float FAR *) s1 > *(float FAR *) s2) return 1 ;
  if (* (float FAR *) s1 < *(float FAR *) s2) return -1 ;
  return 0 ;
  }

int CompareDate (LPVOID s1,LPVOID s2)
  {
  packdate FAR *d1 = (packdate FAR *) s1 ;
  packdate FAR *d2 = (packdate FAR *) s2 ;
  if ((d1->year == d2->year) && (d1->month == d2->month) && (d1->day == d2->day))       return 0 ;
  if ((d1->year > d2->year) ||
      ((d1->year == d2->year) && (d1->month > d2->month)) ||
      ((d1->year == d2->year) && (d1->month == d2->month) && (d1->day > d2->day)))
    return 1 ;
  else
    return -1 ;
  }

int CompareTime (LPVOID s1,LPVOID s2)
  {
  packtime FAR *d1 = (packtime FAR *) s1 ;
  packtime FAR *d2 = (packtime FAR *) s2 ;
  if ((d1->hour == d2->hour) && (d1->minute == d2->minute) && (d1->second == d2->second)) return 0 ;
  if ((d1->hour == d2->hour) && (d1->minute == d2->minute) && (d1->second == d2->second)) return 0 ;
  if ((d1->hour > d2->hour) ||
      ((d1->hour == d2->hour) && (d1->minute > d2->minute)) ||
      ((d1->hour == d2->hour) && (d1->minute == d2->minute) && (d1->second > d2->second)))
    return 1 ;
  else
    return -1 ;
  }

int CompareDateTime (LPVOID s1,LPVOID s2)
  {
  packdatetime FAR *d1 = (packdatetime FAR *) s1 ;
  packdatetime FAR *d2 = (packdatetime FAR *) s2 ;
  int dd = CompareDate (&d1->pd,&d2->pd);
  if (dd != 0) return dd ;
  else return CompareTime (&d1->pt,&d2->pt);
  }

int CompareBinary (LPVOID s1,LPVOID s2)
  {
  unsigned char *u1 = (unsigned char *) s1;
  unsigned char *u2 = (unsigned char *) s2;
  int z1 = GetBlockSize (s1);
  int z2 = GetBlockSize(s2);
  int s = min(z1,z2);
  for ( int i = min(z1,z2) ; (i > 0) ; i--) {
    if (*u1 > *u2) return 1;
    if (*u1 < *u2) return -1;
    u1 ++ ;
    u2 ++ ;
    }
  if (z1 > z2) return 1;
  if (z1 < z2) return -1;
  return 0 ;
  }

typedef int (* COMPAREDATA) (LPVOID s1,LPVOID s2);
COMPAREDATA CompareData [] = {
  /* VAR_LONG    */ CompareLong ,
  /* VAR_DEC     */ CompareFloat ,
  /* VAR_STR     */ CompareString ,
  /* VAR_POINT   */ NoCompare ,
  /* VAR_CONT    */ NoCompare ,
  /* VAR_STRARR  */ CompareShort ,
  /* VAR_FLAG    */ CompareShort ,
  /* VAR_SCALE   */ NoCompare ,
  /* VAR_PICTURE */ NoCompare ,
  /* VAR_DATE    */ CompareDate ,
  /* VAR_PROC    */ NoCompare ,
  /* VAR_IMAGE   */ NoCompare ,
  /* VAR_DWORD   */ CompareLong ,
  /* VAR_OBJ     */ CompareBinary ,
  /* VAR_BITMAP  */ NoCompare ,
  /* VAR_TIME    */ CompareTime ,
  /* VAR_QLONG     */ NoCompare ,
  /* VAR_BLOB      */ NoCompare , 
  /* VAR_DATETIME  */ CompareDateTime
  } ;
int CompareRec (LPDBRECORD r1,LPDBRECORD r2)
  {
  int res = 0 ;
  for (int i = 0 ; ((i < _AnzSegsToSort) && (res == 0)) ; i++) {
    LPDBRECORD r1x = FindRecordInCycl (r1,&_VarRef[i]) ;
    LPDBRECORD r2x = FindRecordInCycl (r2,&_VarRef[i]) ;
    if (r1x == NULL) 
      if (r2x == NULL)
        res = 0;
      else
        res = 1;
    else if (r2x == NULL)
      res = -1;
    else {
      WORD Type = r1x->GetDataType(_VarInd[i]) ;
      LPVOID d1 = r1x->Get(_VarInd[i]) ;
      LPVOID d2 = r2x->Get(_VarInd[i]) ;
      if ((d1 != NULL) && (d2 != NULL))
        res = (* (CompareData[Type])) (d1,d2) ;
      else if ((d1 == NULL) && (d2 == NULL)) res = 0 ;
      else if (d1 == NULL) res = -1 ;
      else if (d2 == NULL) res = 1 ;
      }
    }
  return res * _dir;
  }
DLLExport int _export FAR PASCAL RecordList::GetAnzCachedRecords ()
  {
  int i = 0 ;
  for (DBRecordList FAR *h = head; h != NULL ; h = h->Next.ptr , i++) ;
  return i ;
  }
void SwapRec (int Low,int High)
  {
  DBRecordList FAR *Temp = slptr[Low];
  slptr[Low] = slptr[High]; 
  slptr[High] = Temp; 
  }
#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))
void QuickSort (int Low, int High)
  {
  int Up, Down;

  DBRecordList FAR *cBreak;

  if (Low < High) {
    /* Only two elements in this subdivision; swap them if they are
    * out of order, then end recursive calls.
    */
    if ((High - Low) == 1) {
      if (CompareRec (slptr[Low]->rec,slptr[High]->rec) > 0)
        SwapRec (Low,High);
      }
    else {
      /* Pick a pivot element at random, then move it to the end. */
      SwapRec (High,getrandom (Low,High));
      cBreak = slptr[High];
      do {
        /* Move in from both sides towards the pivot element. */
        Up = Low;
        Down = High;
        while ((Up < Down) &&
              (CompareRec (slptr[Up]->rec, cBreak->rec) <= 0))
                Up++;
        while ((Down > Up) &&
                (CompareRec (slptr[Down]->rec, cBreak->rec) >= 0))
                Down--;
        /* If we haven't reached the pivot, it means that two
        * elements on either side are out of order, so swap them.
        */
        if (Up < Down)
            SwapRec (Up,Down);
      } while (Up < Down);

      /* Move pivot element back to its proper place in the array. */
      SwapRec (Up,High);

      /* Recursively call the QuickSort procedure (pass the smaller
      * subdivision first to use less stack space).
      */
      if ((Up - Low) < (High - Up)) {
        QuickSort (Low,Up - 1);
        QuickSort (Up + 1,High);
        }
      else {
        QuickSort (Up + 1,High);
        QuickSort (Low,Up - 1);
        }
      }
    }
  }

DLLExport void _export FAR PASCAL RecordList::SortList (int AnzSegsToSort,int FAR *VarInd,TableRef FAR *tr,int dir)
  {
  _AnzSegsToSort = AnzSegsToSort;
  _VarInd = VarInd;
  _VarRef = tr;
  _dir = dir;
  int i = 0 ;
  // Abzaehlen, wieviel Elemente
  for (DBRecordList FAR *h = head; h != NULL ; h = h->Next.ptr , i++);
#ifndef WIN32
  WIN_ASSERT (i < 8192);
#endif
  GLOBALHANDLE hGMem;
  if (i < 8192)
    slptr = (DBRecordList FAR *FAR *) GetGlobMem (i * sizeof(LPDBRECORD));
  else {
    hGMem = GlobalAlloc (GHND,i * sizeof(LPDBRECORD));
    slptr = (DBRecordList FAR *FAR *) GlobalLock (hGMem);
    }
  i = 0;
  for (h = head; h != NULL ; h = h->Next.ptr , i++) {
    slptr[i] = h ;
    }
  int dim = i;
  if (dim > 1) {
    QuickSort (0,dim - 1);
    for (i = 0 ; i < dim ; i++ ) {
      if (i == 0) {
        head = slptr[0] ;
        slptr[0]->Prev.ptr = NULL ;
        slptr[0]->Prev.SelectionEnd = TRUE ;
        }
      else {
        slptr[i]->Prev.ptr = slptr[i-1] ;
        slptr[i]->Prev.SelectionEnd = FALSE ;
        }
      if (i == dim - 1) {
        tail = slptr[i] ;
        slptr[i]->Next.ptr = NULL ;
        slptr[i]->Next.SelectionEnd = TRUE ;
        }
      else {
        slptr[i]->Next.ptr = slptr[i+1] ;
        slptr[i]->Next.SelectionEnd = FALSE ;
        }
      }
    }
  if (dim < 8192)
    FreeGlobMem (slptr);
  else {
    GlobalUnlock (hGMem);
    GlobalFree (hGMem);
    }
  }

DLLExport void _export FAR PASCAL RecordList::MarkRecordUnused (LPDBRECORD rec)
  {
  }

DLLExport void _export FAR PASCAL DBList::MarkRecordUnused (LPDBRECORD rec)
  {
  LPDBRECORDLIST h = FindRec (rec);
  if (h != NULL) {
    h->ShouldBeDeleted = TRUE ;
    if (h->Prev.SelectionEnd)
      if (h->Next.ptr != NULL) h->Next.ptr->Prev.SelectionEnd = TRUE ;
    if (h->Next.SelectionEnd)
      if (h->Prev.ptr != NULL) h->Prev.ptr->Next.SelectionEnd = TRUE ;
    }
  }
