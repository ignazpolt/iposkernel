///////////////////////////////////////////////////////////////////////
//  Implementierung der Klasse mdiChild
///////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/mdichild.cpv   1.122   08 Jun 2000 07:48:18   Hannes  $
//  $Log:   P:/marille/clinicum/rev/mdichild.cpv  $
// 
//    Rev 1.122   08 Jun 2000 07:48:18   Hannes
// 
//    Rev 1.121   14 May 2000 17:35:48   Hannes
// GetFirst & GetNextScript
// 
//    Rev 1.120   26 Apr 2000 00:48:12   Hannes
// Zaehler in ScriptParameter
// 
//    Rev 1.119   21 Apr 2000 20:34:24   Martin
// PopData: nur schreiben, wenn sich Ergebnis geaendert hat
// 
//    Rev 1.118   03 Apr 2000 20:57:02   Hannes
// TryToReadExtra
// 
//    Rev 1.117   14 Dec 1999 13:11:20   Hannes
// Updatereihenfolge bei Expressions in if
// 
//    Rev 1.116   23 Nov 1999 17:23:24   Hannes
// Diverse Erweiterungen..
// 
//    Rev 1.115   12 Oct 1999 12:07:32   Hannes
// Clearconnection in UseDialogDocument
// 
//    Rev 1.114   30 Jul 1999 17:47:02   Hannes
// DataWithName
// 
//    Rev 1.113   27 Jun 1999 21:56:24   Hannes
// UseDialogDocumentFromBlob: Absicherung
// 
//    Rev 1.112   03 Jun 1999 18:04:52   Martin
// NextSame-Handling in DelExpression !
// 
//    Rev 1.111   23 Feb 1999 15:10:14   Hannes
// Code muss keine Konstante sein
// 
//    Rev 1.110   11 Jan 1999 08:19:50   Hannes
// Austausch Records im Aufrufer-> Kontextaustauch in Kindern
// 
//    Rev 1.109   14 Dec 1998 19:04:54   Hannes
// Paramterweitergabe bei Code -1
// 
//    Rev 1.108   26 Nov 1998 08:21:50   Hannes
// GetDataWithName
// 
//    Rev 1.107   18 Nov 1998 15:51:46   Hannes
// ClearConnection bei ScriptInfo
// 
//    Rev 1.106   15 Sep 1998 20:06:00   Hannes
// Absicherungen DelRecData
// 
//    Rev 1.105   14 Sep 1998 03:25:18   Hannes
// Absicherungen DelRecData
// 
//    Rev 1.104   14 Aug 1998 15:47:34   Wolfgang
// 1.) Bei RestoreRecord ueber optionalen Parameter Updates ausloesbar.
// 
//    Rev 1.103   13 Aug 1998 09:24:44   Martin
// MemoryMappedFiles,PostMessage,Halt/ResumeQueue
// 
//    Rev 1.102   31 Jul 1998 18:47:04   Martin
// buffer in GetScriptProperty von 256 auf 512 erhoeht
// (Bitte mit den Script Properties in Zukunft haushalten !!!!)
// 
//    Rev 1.101   08 Jul 1998 13:53:38   Hannes
// ScriptEntry als ScriptFunktion
// 
//    Rev 1.100   02 Jul 1998 11:09:02   Hannes
// Handling Zeitversetztes Destroy
// 
//    Rev 1.99   29 Jun 1998 19:02:54   Hannes
// 
//    Rev 1.98   27 Apr 1998 12:52:20   Hannes
// No change.
// 
//    Rev 1.97   16 Feb 1998 19:00:46   Hannes
// 
//    Rev 1.96   10 Feb 1998 18:27:00   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.95   30 Jan 1998 19:44:04   Hannes
// DocumentToPrinterFromBlobEx
// 
//    Rev 1.94   29 Jan 1998 11:06:18   Hannes
// DocumentToPrinter
// 
//    Rev 1.93   07 Jan 1998 08:05:22   Hannes
// 
//    Rev 1.92   05 Jan 1998 07:54:08   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.91   15 Dec 1997 17:36:28   Hannes
// 
//    Rev 1.90   01 Dec 1997 19:38:24   Hannes
// Diverse Anpassungen
// 
//    Rev 1.89   19 Nov 1997 18:47:50   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.88   29 Oct 1997 19:00:48   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.87   27 Oct 1997 19:50:26   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.86   24 Oct 1997 08:37:30   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.85   24 Sep 1997 21:03:20   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.84   01 Sep 1997 09:27:16   Hannes
// Verbesserungen an Restorerecord
// 
//    Rev 1.83   18 Aug 1997 18:09:02   Martin
// VTO Formular-faehig
// 
//    Rev 1.81   22 Jul 1997 21:08:24   Hannes
// 
//    Rev 1.80   18 Jul 1997 08:06:22   Hannes
// 
//    Rev 1.79   15 Jul 1997 18:21:00   Hannes
// 
//    Rev 1.78   08 Jul 1997 15:08:42   Hannes
// 
//    Rev 1.77   08 Jul 1997 15:03:10   Hannes
// 
//    Rev 1.76   08 Jul 1997 11:59:18   Hannes
// 
//    Rev 1.75   25 Jun 1997 09:03:42   Hannes
// 
//    Rev 1.74   09 Jun 1997 13:11:20   Hannes
// 
//    Rev 1.73   28 May 1997 15:32:48   Hannes
// Abfrage nach dem Optionscript beim Aufruf
// 
//    Rev 1.72   23 May 1997 11:19:46   Hannes
// 
//    Rev 1.71   13 May 1997 07:55:52   Hannes
// 
//    Rev 1.70   05 May 1997 17:24:06   Hannes
// 
//    Rev 1.69   30 Apr 1997 09:25:08   Hannes
// 
//    Rev 1.68   21 Apr 1997 17:05:24   Hannes
// Funktionen in Listenprozeduren
// 
//    Rev 1.67   26 Mar 1997 14:20:14   Hannes
// Parameteruebergabe bei ExternDocumentFromBlob
// 
//    Rev 1.66   19 Mar 1997 14:47:06   Hannes
// NoFurtherUpdates in UseDialogDocumenut und Verwandte
// 
//    Rev 1.65   18 Mar 1997 18:20:02   Hannes
// 
//    Rev 1.64   13 Mar 1997 18:58:40   Hannes
// Mit Blobs MDIChilds erzeugen
// 
//    Rev 1.63   04 Mar 1997 10:25:44   Hannes
// DestroyDocument->NoFurtherUpdates eingebaut
// 
//    Rev 1.62   28 Feb 1997 14:45:12   Hannes
// PopDate updatefaehig
// 
//    Rev 1.61   19 Feb 1997 12:23:30   Hannes
// Scriptfunktionen
// 
//    Rev 1.60   08 Jan 1997 16:02:52   HANNES
// Updatereihenfolge ueber Scripts (sofern mit USEDIALOGDOCUMENT gestartet
// gewaehrleistet
// 
//    Rev 1.59   20 Dec 1996 17:49:02   HANNES
// 
//    Rev 1.58   12 Dec 1996 16:43:20   HANNES
// Fehlerkorrektur in ~SetExtraInfo
// 
//    Rev 1.57   12 Dec 1996 12:17:16   HANNES
// Call in einer Multproc unterstuetzt
// 
//    Rev 1.56   03 Dec 1996 16:39:00   HANNES
// MarkVarStatic, MarkVarDynamic
// 
//    Rev 1.55   28 Nov 1996 14:15:46   HANNES
// DocumentToPrinter: Den Printer vom Ausgabekontext des Vaterdocumentes
// uebernehmen
// 
//    Rev 1.54   26 Nov 1996 08:14:36   HANNES
// Automatischer Update
// 
//    Rev 1.53   08 Nov 1996 13:34:12   HANNES
// Replikatorfunktionen
// 
//    Rev 1.52   30 Oct 1996 20:34:44   MARTIN
// EXTERNDOCUMENT hat jetzt die Nummer 596
// 
//    Rev 1.51   28 Oct 1996 08:39:00   HANNES
// ClearConnection,SetConnection: neuer Funktionsprototyp
// 
//    Rev 1.50   21 Oct 1996 18:49:08   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.49   25 Sep 1996 18:31:10   MARTIN
// RestoreRecord: es koennen im binaeren Block auch weniger Daten
// gespeichert gewesen sein, die restlichen Variablen werden auf NULL
// gesetzt. (notwendig fuer in der Datenbank gespeicherte SaveRecords...)
// 
//    Rev 1.48   03 Sep 1996 10:01:18   HANNES
// Verhindern von Updates nach DestroyWindow
// 
//    Rev 1.47   10 Jun 1996 10:09:24   GERHOLD
// pragma pack
// 
//    Rev 1.46   06 May 1996 12:57:12   HANNES
// CallOnUpdate
// 
//    Rev 1.45   22 Mar 1996 12:21:12   MARTIN
// ClearConn... in CreatePaintDoc usw.
// 
//    Rev 1.44   02 Feb 1996 10:35:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.43   23 Nov 1995 17:45:08   GERHOLD
// SetDocumentTitle (Fenstertext eines MDI-Fensters setzen)
// 
//    Rev 1.42   13 Nov 1995 11:59:30   MARTIN
// Aussagekraeftigere WIN_ASSERTs
// 
//    Rev 1.41   25 Oct 1995 12:22:58   HANNES
// Aenderungen Hannes
// 
//    Rev 1.40   01 Sep 1995 09:04:04   HANNES
// 
//    Rev 1.39   24 Aug 1995 00:19:54   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.38   14 Aug 1995 08:29:00   HANNES
// Parameterhandling...
// 
//    Rev 1.37   10 Aug 1995 09:26:36   HANNES
// DokumentToPrinter, Neuen Konstruktor fuer SetExtraInfo
// 
//    Rev 1.36   11 Jul 1995 12:47:32   HANNES
// Expressionoptimierung
// 
//    Rev 1.35   14 Jun 1995 15:22:18   HANNES
// Zusammenspiel der Expressions mit RestoreListFnc
// 
//    Rev 1.34   14 Jun 1995 13:02:50   HANNES
// Eigene Instanz fuer jede Listenprozedur
// 
//    Rev 1.33   11 Jun 1995 23:25:30   HANNES
// GlobalFree (hGConstMem)
// 
//    Rev 1.32   11 Jun 1995 10:09:42   HANNES
// TryToReadExtraData
// 
//    Rev 1.31   09 Jun 1995 00:20:20   HANNES
// CSYSRECS
// SaveRecord,RestoreRecord
// 
//    Rev 1.30   23 May 1995 15:41:50   HANNES
// CreatePrintDocument
// 
//    Rev 1.29   20 May 1995 16:15:12   HANNES
// Connection auf die Extradaten beim Dokumentaufruf (wegen Expressions..)
// PackData zum Zusammenpacken von kleinen Teildaten
// 
//    Rev 1.28   15 May 1995 08:28:18   HANNES
// Script - Properties
// 
//    Rev 1.27   04 May 1995 18:38:34   HANNES
// 
//    Rev 1.26   28 Apr 1995 17:18:14   HANNES
// Fehler in Getexpressionptr
// 
//    Rev 1.25   31 Mar 1995 13:09:34   HANNES
//  
// 
//    Rev 1.24   29 Mar 1995 16:22:34   HANNES
// 
//    Rev 1.23   21 Mar 1995 16:20:58   HANNES
// 
//    Rev 1.22   20 Mar 1995 12:04:34   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.21   08 Mar 1995 09:14:56   HANNES
// Forschleifen u.a.
// 
//    Rev 1.20   03 Mar 1995 18:12:34   HANNES
// 
//    Rev 1.19   24 Feb 1995 11:17:22   HANNES
//  
// 
//    Rev 1.18   29 Jan 1995 11:50:34   HANNES
// No change.
// 
//    Rev 1.17   20 Jan 1995 15:55:18   HANNES
// 
//    Rev 1.16   13 Jan 1995 16:55:54   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.15   09 Jan 1995 12:14:32   HANNES
// Debugger eingebaut
// 
//    Rev 1.14   05 Dec 1994 17:42:34   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.13   08 Nov 1994 12:44:10   HANNES
// AvoidUpdate
// 
//    Rev 1.12   05 Nov 1994 20:47:58   MARTIN
// CopyFrom/ToRecord
// 
//    Rev 1.11   31 Oct 1994 10:02:40   hannes
// CallOptScript
// 
//    Rev 1.10   17 Oct 1994 15:06:34   HANNES
// IsDocLocked fuer Konstanten
// 
//    Rev 1.9   11 Oct 1994 09:44:24   HANNES
// Einbau der Zoomrectfunktionen, diskrete Skalierung
// 
//    Rev 1.8   06 Oct 1994 19:27:08   HANNES
// CreatePaintDocument ... mit GetMinMax
// 
//    Rev 1.7   20 Sep 1994 11:38:12   HANNES
// Verbesserung von SetExtraInfo
// 
//    Rev 1.6   24 Aug 1994 19:44:22   HANNES
// CreatePaintDocument: Ueberpruefung des Flags NoMDI
// 
//    Rev 1.5   10 Aug 1994 12:04:24   HANNES
// DeleteRecRoot ganz nach hinten in ~mdiChild
// 
//    Rev 1.4   05 Aug 1994 17:14:34   HANNES
// No change.
// 
//    Rev 1.3   17 Jul 1994 14:44:52   HANNES
// Im destruktur WMU_DESTROY... aus der Queue vorziehen
// 
//    Rev 1.2   13 Jul 1994 21:15:40   HANNES
// Prototype von DBRecord::Set, DBRecord::Del neu angepasst
// 
//    Rev 1.1   12 Jul 1994 14:51:10   HANNES
// Fehlerkorrektur in UseDocument
// 
//    Rev 1.0   24 Jun 1994 17:05:12   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#define MDICHILD_MAIN
#include "mdichild.hpp"
#define MODULENUM 96
#include "winass.hpp"

#include "ddsmsg.h"
#include "winextra.hpp"

#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"

#include "fncarr.hpp"
#include "multipro.hpp"
#define NODLL
#include "toolbar.hpp"
/*------------------< Expressions und Konstanten >--------------*/
typedef char huge *LPHUGESTR;
LPEXPPTR FAR *mdiChild::GetExpPtr (DWORD Id)
  {
  if (_ExtraData != NULL) 
    return (LPEXPPTR FAR *) (LPHUGESTR(_ExtraData->cmdBase)+(DWORD(LOWORD(Id) & 0x00FF) << 16) + DWORD(HIWORD(Id)) - _ExtraData->cOffs);
    // return (LPEXPPTR FAR *) (_ExtraData->cmdBase + HIWORD(Id) - _ExtraData->cOffs);
  else
    return (LPEXPPTR FAR *) (LPHUGESTR(base)+(DWORD(LOWORD(Id) & 0x00FF) << 16) + DWORD(HIWORD(Id)));
  }

BOOL DontCheckCallDone = FALSE;
extern DLLExport void _export WINAPI PushUpdateExtraData();
DLLExport void _export WINAPI PopUpdateExtraData();
LPVOID mdiChild::GetExpression (DWORD Id)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if (*e == NULL) {
    // Die Daten werden jetzt schon angelegt, damit auf das
    // Varelem eine nextsame Verbindung gemacht werden kann
    // (GetExtraVarElem)
    //------------------------------------------------------
    *e = LPEXPPTR (GetGlobMem (sizeof(**e)));
    LPEXPPTR FAR *en;
    if ((_ExtraData != NULL) && (_ExtraData->cOffs))
      en = GetExpNode (_ExtraData->cmdBase);
    else
      en = &ExpNodes ;
    (*e)->Next = *en;
    (*e)->ptrToThis = e ;
    *en = *e;
    }
  if ((!(*e)->callDone) || (DontCheckCallDone)) {
    _ccount->DecrementSingle ();
    _ccount = PushBlock (_ccount);
    CallExpression (LPSTR(e) + sizeof(LPVOID),EM_LOAD);
    (*e)->callDone = TRUE ;
    _ccount = PopBlock (_ccount);
    _ccount->IncrementSingle ();
    }
  return (*e)->v.Get();
  }

LPTSTR mdiChild::GetStrExpression (DWORD Id)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if (*e == NULL) {
    // Die Daten werden jetzt schon angelegt, damit auf das
    // Varelem eine nextsame Verbindung gemacht werden kann
    // (GetExtraVarElem)
    //------------------------------------------------------
    *e = LPEXPPTR (GetGlobMem (sizeof(**e)));
    LPEXPPTR FAR *en;
    if ((_ExtraData != NULL) && (_ExtraData->cOffs))
      en = GetExpNode (_ExtraData->cmdBase);
    else
      en = &ExpNodes ;
    (*e)->Next = *en;
    (*e)->ptrToThis = e ;
    *en = *e;
    }
  if ((!(*e)->callDone) || (DontCheckCallDone)) {
    _ccount->DecrementSingle ();
    _ccount = PushBlock (_ccount);
    CallExpression (LPBYTE(e) + sizeof(LPVOID),EM_LOAD);
    (*e)->callDone = TRUE ;
    _ccount = PopBlock (_ccount);
    _ccount->IncrementSingle ();
    }
  return (*e)->v.GetStr();
  }

LPVARELEM mdiChild::GetExtraVarElem (DWORD Id)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if (*e == NULL) {
    // Es muss auf jeden fall ein Expressionnode angebracht werden,
    // damit die Nextsameverbindung gemacht werden kann
    *e = LPEXPPTR (GetGlobMem (sizeof(**e)));
    LPEXPPTR FAR *en;
    if ((_ExtraData != NULL) && (_ExtraData->cOffs))
      en = GetExpNode (_ExtraData->cmdBase);
    else
      en = &ExpNodes ;
    (*e)->Next = *en;
    (*e)->ptrToThis = e ;
    *en = *e;
    }
  return &((*e)->v);
  }

LPVOID mdiChild::TryToReadExtraData (DWORD Id,BOOL FAR *done)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if ((*e != NULL) && ((*e)->callDone)) {
    if (done != NULL)
      *done = TRUE;
    return (*e)->v.Get();
    }
  else {
    if (done != NULL)
      *done = FALSE ;
    return NULL ;
    }
  }

extern DWORD VirtFunctionsAddress (LPSTR FunctionName,LPSTR ModName,LPSCRIPTCONTENT FAR *lpsc,LPWORD FAR *destind,BOOL checkOwn,WORD FAR *restyp);
WORD mdiChild::GetExpressionType (DWORD Id)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  LPSTR h = LPSTR(e) + sizeof(LPVOID);
  WORD command = *(WORD FAR *) h ;
  WORD Type = 0xFFFF ;
  if (command > FIRSTFUNCID) {
    Type = mTypesForCmd[command - FIRSTFUNCID];
    }
  else {
    if ((*e == NULL) || (!(*e)->callDone)) {
      _ccount->DecrementSingle ();
      _ccount = PushBlock (_ccount);
      CallExpression (LPSTR(e) + sizeof(LPVOID),EM_LOAD | EM_FIXCONNECTION);
      _ccount = PopBlock (_ccount);
      _ccount->IncrementSingle ();
      (*e)->callDone = TRUE ;
      }
    DWORD nfOffs = 0L ;
    LPSCRIPTCONTENT sc = NULL;
    if ((command  == PREFIX_FUNCTIONCALL) || (command == PREFIX_STFUNCTIONCALL)) {
      FunctionCall FAR *fc = (FunctionCall FAR *) (h + sizeof(WORD));
      DWORD nfOffs = fc->procAddr;
      sc = schd;
      }
    else if ((command == PREFIX_VIRTCALL) || (command == PREFIX_STVIRTCALL)) {
      VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (h + sizeof(WORD));
      DWORD mref = fc->par()[-1];
      LPSTR ModName = LPSTR (ReadlData (mref));
      BOOL checkOwn;
      if (lstrcmp (ModName,"_Parent") == 0) {
        ModName = schd->fName ;
        checkOwn = FALSE ;
        }
      else
        checkOwn = TRUE ;
      nfOffs = VirtFunctionsAddress (fc->FName,ModName,&sc,&fc->destind,checkOwn,&Type);
      }
    if (nfOffs > 0L) {
      LPSTR b = LPSTR (sc->ftlist);
      for ( _FuncTypeList FAR *ft = sc->ftlist ; ft != NULL ;
              ft = (ft->d.NextTypeListOffset > 0) ? (_FuncTypeList FAR *) (b + WORD(ft->d.NextTypeListOffset)) : NULL ) {
        if (ft->procPtr == nfOffs) {
          Type = ((BYTE FAR *) (ft + 1)) [0];
          break ;
          }
        }
      }
    else
      WIN_ASSERT(FALSE);
    }
  DBWIN_ASSERT (Type != 0xFFFF);
  return Type;
  }

LPVOID mdiChild::GetExtraData (DWORD Id)
  {
  return GetExpression (Id);
  }

LPTSTR mdiChild::GetStrExtraData (DWORD Id)
  {
  return GetStrExpression (Id);
  }

WORD mdiChild::GetExtraDataType (DWORD Id)
  {
  switch (LOWORD(Id)) {
    case 0 :
      return schd->LocalTypes[HIWORD(Id)];
    case 1 :
      return schd->HelpTypes[HIWORD(Id)];
    case 2 :
      {
      LPVOID Data = rr->GetRecord(2)->Get(HIWORD (Id));
      return (((WORD FAR *)Data)[-2]) ;
      }
    case DYNLOCALDATA :
      {
      WIN_ASSERT ((_ExtraData != NULL) && (_ExtraData->fOffs != 0L)) ;
      LPSTR b = LPSTR (schd->ftlist);
      for ( _FuncTypeList FAR *ft = schd->ftlist ; ft != NULL ;
              ft = (ft->d.NextTypeListOffset > 0) ? (_FuncTypeList FAR *) (b + WORD(ft->d.NextTypeListOffset)) : NULL ) {
        if (ft->procPtr == _ExtraData->fOffs)
          return ((BYTE FAR *) (ft + 1)) [HIWORD (Id)];
        }
      WIN_ASSERT(FALSE);
      }
    case STATICLOCALDATA :
      {
      WIN_ASSERT ((_ExtraData != NULL) && (_ExtraData->fOffs != 0L));
      LPSTR b = LPSTR (schd->ftlist);
      for ( _FuncTypeList FAR *ft = schd->ftlist ; ft != NULL ;
              ft = (ft->d.NextTypeListOffset > 0) ? (_FuncTypeList FAR *) (b + WORD(ft->d.NextTypeListOffset)) : NULL ) {
        if (ft->procPtr == _ExtraData->fOffs)
          return ((BYTE FAR *) (ft + 1) + ft->AnzDynLocals) [HIWORD (Id)];
        }
      WIN_ASSERT(FALSE);
      }
    default :
      return GetExpressionType (Id);
    }
  }

void mdiChild::SetExpression (DWORD Id,LPVOID data,WORD size,LPVOID Cmd,BOOL UpdateSystem)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if (*e == NULL) {
    *e = LPEXPPTR (GetGlobMem (sizeof(**e)));
    LPEXPPTR FAR *en;
    if ((_ExtraData != NULL) && (_ExtraData->cOffs))
      en = GetExpNode (_ExtraData->cmdBase);
    else
      en = &ExpNodes ;
    (*e)->Next = *en;
    (*e)->ptrToThis = e ;
    *en = *e;
    }
  LPVARELEM v = &((*e)->v);
  v->Set(data,size);
  if (UpdateSystem)
    v->Update (Cmd,NULL,_ExtraType,_ExtraData,_ExtraSize);
  if (v->NextSame != NULL) {
    for (LPVARELEM n = v->NextSame ; n != v ; n = n->NextSame) {
      n->Set (data,size) ;
      if ((UpdateSystem) && (!n->isStatic())) n->Update(Cmd,NULL,_ExtraType,_ExtraData,_ExtraSize);
      }
    }
  }

void mdiChild::DelExpression (DWORD Id,LPVOID Cmd,BOOL UpdateSystem)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if (*e == NULL) {
    *e = LPEXPPTR (GetGlobMem (sizeof(**e)));
    LPEXPPTR FAR *en;
    if ((_ExtraData != NULL) && (_ExtraData->cOffs))
      en = GetExpNode (_ExtraData->cmdBase);
    else
      en = &ExpNodes ;
    (*e)->Next = *en;
    (*e)->ptrToThis = e ;
    *en = *e;
    }
  LPVARELEM v = &((*e)->v);
  v->Del();
  if (UpdateSystem)
    v->Update (Cmd,NULL,_ExtraType,_ExtraData,_ExtraSize);
  if (v->NextSame != NULL) {
    for (LPVARELEM n = v->NextSame ; n != v ; n = n->NextSame) {
      n->Del() ;
      if ((UpdateSystem) && (!n->isStatic())) n->Update(Cmd,NULL,_ExtraType,_ExtraData,_ExtraSize);
      }
    }
  }

void mdiChild::ConnectExpression (DWORD Id,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT cnt)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if ((*e == NULL) || (!(*e)->callDone)) {
    _ccount->DecrementSingle ();
    _ccount = PushBlock (_ccount);
    CallExpression (LPSTR(e) + sizeof(LPVOID),EM_LOAD | EM_FIXCONNECTION);
    _ccount = PopBlock (_ccount);
    _ccount->IncrementSingle ();
    (*e)->callDone = TRUE ;
    }
  else {
    _ccount->DecrementSingle ();
    _ccount = PushBlock (_ccount);
    CallExpression (LPSTR(e) + sizeof(LPVOID),EM_FIXCONNECTION);
    _ccount = PopBlock (_ccount);
    _ccount->IncrementSingle ();
    }
  (*e)->v.SetConnection(DocumentID,DocumentID,Cmd,_ccount,_ExtraType,_ExtraData,_ExtraSize);
  }

void mdiChild::ClearExpression (DWORD Id,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT cnt)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  if ((*e != NULL) && ((*e)->callDone)) {
    (*e)->v.ClearConnection(DocumentID,DocumentID,Cmd,_ExtraType,_ExtraData,_ExtraSize);
    (*e)->callDone = FALSE ;
    CallExpression (LPSTR(e) + sizeof(LPVOID),EM_CLEAR | EM_RESET);
    GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID,LPSTR(e) + sizeof(LPVOID)); 
    GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID,Cmd); 
    }
  }

BOOL mdiChild::IsUpdateFromExpression (DWORD Id)
  {
  LPEXPPTR FAR *e = GetExpPtr (Id);
  DBWIN_ASSERT (*e != NULL);
  return IsUpdateFrom (&(*e)->v);
  }

static WORD NextDocumentNumber;
#ifdef DEBUG
DLLExport void _export WINAPI PushToMDIList (mdiChild FAR *n);
DLLExport void _export WINAPI PopFromMDIList (mdiChild FAR *n);
#endif
mdiChild::mdiChild (LPSCRIPTCONTENT ent,BOOL GetCommandCopy)
  {
  schd = ent;
  rr = InitializeRecRoot (ent->AnzTables+CSYSRECS);
#ifdef DEBUG
  PushToMDIList (this);
#endif
  // Die lokalen und die Hilfsdaten Datensaetze koennen schon mal 
  // gesetzt werden
  LPDBRECORD crec;
  if (GetCommandCopy)
    ent->GetScriptData (&commands,&hGConstMem,&crec);
  else
    ent->GetCacheScriptData (&commands,&hGConstMem,&crec);
  base = LPSTR(GlobalLock (commands));
  if (ent->AnzLocals > 0) rr->SetRecord (0, new DBLocalRecord(ent->AnzLocals,DocumentID()));
  if (ent->AnzHelps > 0)  rr->SetRecord (1, new DBHelpRecord(ent->AnzHelps,DocumentID()));
  if (ent->AnzConsts > 0) rr->SetRecord (2, crec);
  MyDocumentNumber = NextDocumentNumber ++;
  _ccount = GetCount (MyDocumentNumber);
  }

void mdiChild::FreeExpNodes()
  {
  for ( ; ExpNodes != NULL ; ) {
    LPEXPPTR n = ExpNodes->Next;
    //    DBWIN_ASSERT (!ExpNodes->callDone); (Wenn kein FixConnection
    //                                       gemacht wird, dann wirds auch
    //                                       kein ClearConnection geben)                                
    ExpNodes->v.FreeMem();
    *(ExpNodes->ptrToThis) = NULL ;
    FreeGlobMem (ExpNodes);
    ExpNodes = n;
    }
  }

BOOL IsFromDestroy ;
ExpChild::~ExpChild ()
  {
  WIN_ASSERT (_outData == NULL);
  }

mdiChild::~mdiChild ()
  {
  closed = TRUE ;
  CloseChilds () ;
  FreeExpNodes();
  FreeScriptData(&commands,hGConstMem,rr->GetRecord(2),schd->fName);
#ifdef DEBUG
  PopFromMDIList (this);
#endif
  commands = NULL;
  // GetAsync_cmdfifo()->DelDocumentEntrys(DocumentID());
  if (ExtPrg != NULL)
    delete ExtPrg;
  if ((_outData != NULL) && (IsWindow (GetOutData()->_MyHandle))) {
    char classname[30];
    GetClassName (GetOutData ()->_MyHandle,classname,sizeof(classname));
    if (lstrcmp (classname,"MDICHILD") == 0)
      SendMessage (WBase::hClient,WM_MDIDESTROY,(WPARAM)(HWND)GetOutData()->_MyHandle,0L);
    else
      DestroyWindow (GetOutData ()->_MyHandle);
    }
  DocumentIsDestroyed (DocumentID());

  // Noch alle WMU_DESTOYS und WMU_DESTROYLIST rausholen
  MSG m;
  if (IsFromDestroy) {
    if (IsWindow (WBase::hFrameWin)) {
      while (PeekMessage (&m, WBase::hFrameWin, WMU_DESTROYDDSLIST, WMU_DESTROYDDSLIST, PM_REMOVE))
        CheckMsg (&m);
      while (PeekMessage (&m, WBase::hFrameWin, WMU_DESTROYCHILD, WMU_DESTROYCHILD, PM_REMOVE))
        CheckMsg (&m);
      }
    }

  DeleteRecRoot (rr,DocumentID());
  DeleteDocumentExtraData ();
  if (_ccount != NULL) FreeGlobMem (_ccount);
  if (_ccount_base != NULL) FreeGlobMem (_ccount_base);
  if (_outData != NULL) FreeGlobMem (_outData);
  }

/*---------------< Extradatenverwaltung >-----------------*/
LPVOID mdiChild::GetDocumentExtraData (WORD Type,int FAR *size)
  {
  for (DocExtraData FAR *h = _ed ; h != NULL ; h = h->Next) {
    if (h->Type == Type) {
      if (size != NULL)
        *size = h->size;
      return h->Data;
      }
    }
  return NULL;
  }

void mdiChild::PutDocumentExtraData (WORD Type,LPVOID Data,int size)
  {
  DocExtraData FAR *h = (DocExtraData FAR *)
        GetGlobMem (sizeof(*h) + size - 1);
  h->Type = Type;
  h->size = size;
  lmemcpy (h->Data,Data,size);
  DocExtraData FAR *prev = NULL ;
  if (_ed == NULL) {
    _ed = h ;
    h->Next = NULL;
    }
  else {
    for (DocExtraData FAR *x = _ed ; ; x = x->Next) {
      if (x->Type == Type) {
        // Muss ausgetauscht werden
        if (prev != NULL)
          prev->Next = h ;
        else
          _ed = h;
        h->Next = x->Next ;
        FreeGlobMem (x);
        break ;
        }
      else if (x->Next == NULL) {
        x->Next = h;
        h->Next = NULL;
        break ;
        }
      else
        prev = x;
      }
    }
  }

void mdiChild::RemoveDocumentExtraData (WORD Type)
  {
  DocExtraData FAR *prev = NULL;
  for (DocExtraData FAR *h = _ed ; h != NULL ; h = h->Next) {
    if (h->Type == Type) {
      if (prev != NULL)
        prev->Next = h->Next ;
      else
        _ed = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    prev = h;
    }
  }

void mdiChild::DeleteDocumentExtraData ()
  {
  for (DocExtraData FAR *h = _ed ; _ed != NULL ; ) {
    _ed = h->Next ;
    FreeGlobMem (h);
    h = _ed ;
    }
  }

SetExtraInfo FAR *lastExtraInfo;
WORD lastExtraType;
#define EISTACKDEPTH    256
static SetExtraInfo FAR *lEIStack[EISTACKDEPTH];
static WORD lETStack[EISTACKDEPTH];
static WORD lETStackPtr;
static GLOBALHANDLE hGExtraInfo;
static LPSTR ExtraFreePtr;
static LPSTR ExtraFreeBase;
void InitExtraMem ()
  {
  hGExtraInfo = GlobalAlloc (GMEM_MOVEABLE,0x4000);
  ExtraFreePtr = LPSTR (GlobalLock (hGExtraInfo));
  ExtraFreeBase = ExtraFreePtr;
  }
void FreeExtraMem ()
  {
  GlobalUnlock (hGExtraInfo);
  GlobalFree (hGExtraInfo);
  }
#define MAXTBINTS       20
#define EXTRAMEMSIZE  (sizeof(ConnectionExtraInfo) + sizeof(tableptrdsc) * MAXTBINTS)
LPVOID GetExtraMem (WORD size)
  {
  *(WORD FAR *) ExtraFreePtr = size ;
  LPVOID res = ExtraFreePtr + sizeof(WORD) ;
  ExtraFreePtr = ExtraFreePtr + sizeof(WORD) + EXTRAMEMSIZE ;
  #ifdef DEBUG
  DBWIN_ASSERT (size < EXTRAMEMSIZE);
  DBWIN_ASSERT (ExtraFreePtr < ExtraFreeBase + 0x4000);
  #endif
  lmemset (res,'\0',EXTRAMEMSIZE);
  return res;
  }
void FreeExtraMem (LPVOID ptr)
  {
  #ifdef DEBUG
  WIN_ASSERT (LPSTR(ptr) + EXTRAMEMSIZE == ExtraFreePtr);
  #endif
  ExtraFreePtr = LPSTR(ptr) - sizeof(WORD) ;
  }

/*---------< Extraconnections >------------*/
LPCONNEXTRAINFO EnlargeExtra (LPCONNEXTRAINFO old,int TableInd,LPDBRECORD r)
  {
  LPCONNEXTRAINFO res ;
  if (old != NULL) {
    int AnzTables = old->AnzTables();
    for (int i = 0 ; i < AnzTables ; i++) {
      if (old->i.t[i].TableInd == WORD(TableInd)) break ;
      }
    if (i == AnzTables) {
      res = LPCONNEXTRAINFO (GetExtraMem (sizeof(*res) + sizeof(res->i.t[0]) * AnzTables)) ;
      lmemcpy (res,old,GetBlockSize(old));
      res->i.t[AnzTables].TableInd = TableInd ;
      res->i.t[AnzTables].r = r ;
      }
    else {
      res = LPCONNEXTRAINFO (GetExtraMem (GetBlockSize(old))) ;
      lmemcpy (res,old,GetBlockSize(old));
      res->i.t[i].r = r ;
      }
    }
  else {
    res = LPCONNEXTRAINFO (GetExtraMem (sizeof(*res))) ;
    res->i.t[0].TableInd = TableInd ;
    res->i.t[0].r = r ;
    }
  return res ;
  }

void EnlargeExtraInto (LPCONNEXTRAINFO old,int TableInd,LPDBRECORD r)
  {
  if (old != NULL) {
    int AnzTables = old->AnzTables();
    for (int i = 0 ; i < AnzTables ; i++) {
      if (old->i.t[i].TableInd == WORD(TableInd)) break ;
      }
    if (i == AnzTables) {   // nicht gefunden -> dynamisch vergroessern
      DBWIN_ASSERT (sizeof(*old) + sizeof(old->i.t[0]) * AnzTables < EXTRAMEMSIZE);
      ((WORD FAR *) old)[-1] = sizeof(*old) + sizeof(old->i.t[0]) * AnzTables;
      old->i.t[AnzTables].TableInd = TableInd ;
      old->i.t[AnzTables].r = r ;
      }
    else {
      old->i.t[i].r = r ;
      }
    }
  else {
    WIN_ASSERT (FALSE);
    }
  }

void PushLastExtra (WORD let,SetExtraInfo FAR *h)
  {
  WIN_ASSERT (lETStackPtr < EISTACKDEPTH);
  lEIStack[lETStackPtr] = lastExtraInfo ;
  lETStack[lETStackPtr] = lastExtraType ;
  lETStackPtr ++ ;
  lastExtraInfo = h;
  lastExtraType = let;
  }

void PopLastExtra ()
  {
  lETStackPtr -- ;
  lastExtraInfo = lEIStack[lETStackPtr] ;
  lastExtraType = lETStack[lETStackPtr] ;
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,WORD TableInd,LPDBRECORD r,DWORD cOffs)
  {
  if (r != NULL) {
    whereisset = c;
    if ((c->_ExtraData != NULL) && (c->_ExtraType == EXTRATYPE_REC))
      ci = EnlargeExtra (LPCONNEXTRAINFO (c->_ExtraData),TableInd,r);
    else
      ci = EnlargeExtra (NULL,TableInd,r);

    ci->cOffs = cOffs;
    ci->cmdBase = c->base;
    if (c->_ExtraData != NULL) {
      oldci   = c->_ExtraData;
      oldSize = c->_ExtraSize;
      oldType = c->_ExtraType;
      }
    else
      oldci = NULL;

    c->_ExtraType = EXTRATYPE_REC ;
    c->_ExtraSize = GetBlockSize(ci);
    c->_ExtraData = ci;

    PushLastExtra (EXTRATYPE_REC,this);
    }
  else
    whereisset = NULL;
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,WORD TableInd,LPDBRECORD r,DWORD cOffs,BOOL replace)
  {
  if (r != NULL) {
    whereisset = c;
    ci = EnlargeExtra (NULL,TableInd,r);

    ci->cOffs = cOffs;
    ci->cmdBase = c->base;
    if (c->_ExtraData != NULL) {
      oldci   = c->_ExtraData;
      oldSize = c->_ExtraSize;
      oldType = c->_ExtraType;
      }
    else
      oldci = NULL;

    c->_ExtraType = EXTRATYPE_REC ;
    c->_ExtraSize = GetBlockSize(ci);
    c->_ExtraData = ci;

    PushLastExtra (EXTRATYPE_REC,this);
    }
  else
    whereisset = NULL;
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,LPPRIMKEY k,DWORD cOffs)
  {
  whereisset = c;
  ci = LPCONNEXTRAINFO (GetExtraMem (sizeof(*ci)));
  ci->i.keyData = k->Data;
  ci->cOffs = cOffs;
  ci->cmdBase = c->base;
  if (c->_ExtraData != NULL) {
    oldci   = c->_ExtraData;
    oldSize = c->_ExtraSize;
    oldType = c->_ExtraType;
    }
  else
    oldci = NULL;

  c->_ExtraType = EXTRATYPE_LIST ;
  c->_ExtraSize = sizeof(*ci);
  c->_ExtraData = ci;

  PushLastExtra (EXTRATYPE_LIST,this);
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,LPVOID keyData,DWORD cOffs)
  {
  whereisset = c;
  ci = LPCONNEXTRAINFO (GetExtraMem (sizeof(*ci)));
  ci->i.keyData = keyData;
  ci->cOffs = cOffs;
  ci->cmdBase = c->base;
  if (c->_ExtraData != NULL) {
    oldci   = c->_ExtraData;
    oldSize = c->_ExtraSize;
    oldType = c->_ExtraType;
    }
  else
    oldci = NULL;

  c->_ExtraType = EXTRATYPE_LIST ;
  c->_ExtraSize = sizeof(*ci);
  c->_ExtraData = ci;

  PushLastExtra (EXTRATYPE_LIST,this);
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,LPCONNEXTRAINFO extra)
  {
  whereisset = c;
  ci = LPCONNEXTRAINFO (GetExtraMem (GetBlockSize (extra)));
  lmemcpy (ci,extra,GetBlockSize(extra));
  if (c->_ExtraData != NULL) {
    oldci   = c->_ExtraData;
    oldSize = c->_ExtraSize;
    oldType = c->_ExtraType;
    }
  else
    oldci = NULL;

  c->_ExtraType = EXTRATYPE_REC ;
  c->_ExtraSize = GetBlockSize(ci);
  c->_ExtraData = ci;

  PushLastExtra (EXTRATYPE_REC,this);
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,DWORD cOffs)
  {
  whereisset = c;
  oldci       = c->_ExtraData;
  if (c->_ExtraData == NULL) {
    c->_ExtraData = LPCONNEXTRAINFO (GetExtraMem (sizeof(ConnectionExtraInfo) - sizeof(tableptrdsc)));
    }
  else {
    c->_ExtraData = LPCONNEXTRAINFO (GetExtraMem (GetBlockSize(oldci)));
    lmemcpy (c->_ExtraData,oldci,GetBlockSize(oldci));
    }
  ci = c->_ExtraData;
  oldSize     = c->_ExtraSize;
  oldType     = c->_ExtraType;
  ci->cOffs   = cOffs;
  ci->cmdBase = c->base;
  c->_ExtraType = EXTRATYPE_REC ;
  c->_ExtraSize = GetBlockSize(ci);

  PushLastExtra (EXTRATYPE_REC,this);
  }

SetExtraInfo::SetExtraInfo (mdiChild *c,DWORD cOffs,DWORD fOffs)
  {
  whereisset = c;
  oldci       = c->_ExtraData;
  if (c->_ExtraData == NULL) {
    c->_ExtraData = LPCONNEXTRAINFO (GetExtraMem (sizeof(ConnectionExtraInfo) - sizeof(tableptrdsc)));
    }
  else {
    c->_ExtraData = LPCONNEXTRAINFO (GetExtraMem (GetBlockSize(oldci)));
    lmemcpy (c->_ExtraData,oldci,GetBlockSize(oldci));
    }
  ci = c->_ExtraData;
  oldSize     = c->_ExtraSize;
  oldType     = c->_ExtraType;
  ci->cOffs   = cOffs;
  ci->fOffs   = fOffs;
  ci->cmdBase = c->base;
  c->_ExtraType = EXTRATYPE_REC ;
  c->_ExtraSize = GetBlockSize(ci);

  PushLastExtra (EXTRATYPE_REC,this);
  }

void RestoreLastExtra ()
  {
  lastExtraInfo->whereisset->_ExtraData = lastExtraInfo->oldci;
  if (lastExtraInfo->oldci) {
    lastExtraInfo->whereisset->_ExtraSize = lastExtraInfo->oldSize;
    lastExtraInfo->whereisset->_ExtraType = lastExtraInfo->oldType;
    }
  else {
    lastExtraInfo->whereisset->_ExtraSize = 0;
    lastExtraInfo->whereisset->_ExtraType = 0;
    }
  }

void SetLastExtra ()
  {
  lastExtraInfo->whereisset->_ExtraSize = GetBlockSize (lastExtraInfo->ci);
  lastExtraInfo->whereisset->_ExtraType = lastExtraType;
  lastExtraInfo->whereisset->_ExtraData = lastExtraInfo->ci;
  }

void SetRecordToLastExtraInfo (LPDBRECORD r,WORD TableInd)
  {
  DBWIN_ASSERT (lastExtraInfo != NULL);
  if (lastExtraType == EXTRATYPE_REC) {
    EnlargeExtraInto (lastExtraInfo->ci,TableInd,r);
    lastExtraInfo->whereisset->_ExtraData = lastExtraInfo->ci;
    lastExtraInfo->whereisset->_ExtraSize = GetBlockSize (lastExtraInfo->ci);
    }
  }

void SetExtraInfo::SetCmdBase (LPSTR cmdBase)
  {
  ci->cmdBase = cmdBase;
  }

SetExtraInfo::~SetExtraInfo ()
  {
  if (whereisset != NULL) {
    if (oldci != NULL) {
      whereisset->_ExtraData = oldci;
      whereisset->_ExtraSize = oldSize;
      whereisset->_ExtraType = oldType;
      }
    else {
      whereisset->_ExtraType = 0;
      whereisset->_ExtraSize = 0;
      whereisset->_ExtraData = NULL;
      }
    FreeExtraMem (ci);
    PopLastExtra ();
    }
  }

/*--------------------< Erzeugen eines Formulares >---------------*/
struct FAR ExtraRef {
  DWORD rCode;
  DWORD Ref;
  };

#pragma pack(1)
struct FAR CreatePaintDocument_param {
  WORD parSize;
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  };
#pragma pack()


extern mdiChild *NewDocInstance (LPSTR docName);
BOOL CreatePaintDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData(par->DocName));
    if (docName != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (docName);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      if (!res->schd->NoMDI)
        res->Create (res->schd->Name);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      res->GetMinMax ();
      if (!res->schd->NoMDI) {
        if (res->BestScaling ())
          res->MapChanged();
        SetFocus (res->GetOutData ()->_MyHandle);
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

extern mdiChild *NewDocInstance (GLOBALHANDLE hGmem);
BOOL CreatePaintDocumentFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    LPBLOBDESC docName = LPBLOBDESC (c->ReadlData(par->DocName));
    if (docName != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (docName->hGmem);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      if (!res->schd->NoMDI)
        res->Create (res->schd->Name);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      res->GetMinMax ();
      if (!res->schd->NoMDI) {
        if (res->BestScaling ())
          res->MapChanged();
        SetFocus (res->GetOutData ()->_MyHandle);
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    c->ClearlConnection (par->DocName,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL CreatePrintDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData(par->DocName));
    if (docName != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (docName);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      res->GetMinMax ();
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL CreatePrintDocumentFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    LPBLOBDESC docName = LPBLOBDESC (c->ReadlData(par->DocName));
    if (docName != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (docName->hGmem);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      res->GetMinMax ();
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    c->ClearlConnection (par->DocName,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL CallOptScript (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePaintDocument_param FAR *par = 
            (CreatePaintDocument_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData (par->DocName));
    DBWIN_ASSERT (docName != NULL);
    LPSCRIPTCONTENT ent = GetScriptEntry(docName);
    char watxt[60];
    wsprintf(watxt,"Script %s nicht gefunden !",docName);
    DBWIN_ASSERT_TEXT (ent != NULL,watxt);
    if (ent->OptionScript != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (ent->OptionScript);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      delete res;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFullDocumentName_param {
  WORD parSize;
  DWORD scRef;      // Script - Filename
  DWORD NameRef;    // Resultat: vollername
  };
#pragma pack()

BOOL GetFullDocumentName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFullDocumentName_param FAR *par = (GetFullDocumentName_param FAR *) param;
    LPSTR scname = LPSTR (c->ReadlData (par->scRef));
    DBWIN_ASSERT (scname != NULL);
    LPSCRIPTCONTENT ent = GetScriptEntry(scname);
    if (ent != NULL)
      c->WritelData (par->NameRef,ent->Name,
                    lstrlen (ent->Name)+1,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->NameRef,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

void mdiChild::ExCuteProc(DWORD Offset, WORD mode)
  {
  ExCuteBlock(Offset + sizeof(DWORD), mode);
  }

// Speichern von Daten
void mdiChild::Store ()
  {
  }

void mdiChild::CallScriptDestruktor ()
  {
  for (int i = 0 ; i < 10 ; i++) {
    LPDWORD Destruktor = LPDWORD(GetDocumentExtraData (DED_SCRIPTDESTRUKTOR + i));
    if (Destruktor != NULL) {
  #ifdef DEBUG
      PushToCallStack (this,schd->fName,0);
  #endif
      ExCuteProc (*Destruktor,EM_LOAD | EM_CHANGETOTRUE);
      ExCuteProc (*Destruktor,EM_RESET);
  #ifdef DEBUG
      PopFromCallStack ();
  #endif
      }
    else
      break ;
    }
  }

#pragma pack(1)
struct FAR CallOnUpdate_param {
  WORD parSize;
  DWORD procPtr;
  DWORD nichtmehrverwendeter_mode;
  DWORD updateVal[1];
  int AnzVals () 
    { return (int (parSize) - sizeof(*this)) / sizeof(DWORD) + 1 ; }
  };
#pragma pack()

extern BOOL IsFromSyncList ();
BOOL CallOnUpdate (mdiChild *c,LPVOID param,WORD mode)
  {
  if ((mode & EM_UPDATE) && (!IsFromSyncList())) {
    CallOnUpdate_param FAR *par = (CallOnUpdate_param FAR *) param;
#ifdef DEBUG
    PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
    RestoreListFnc rlf(c);
    c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc (par->procPtr,EM_RESET | EM_CLEAR);
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  if (mode & EM_FIXCONNECTION) {
    CallOnUpdate_param FAR *par = (CallOnUpdate_param FAR *) param;
    for (int i = 0 ; i < par->AnzVals() ; i++)
      c->SetlConnection (par->updateVal[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CallOnUpdate_param FAR *par = (CallOnUpdate_param FAR *) param;
    for (int i = 0 ; i < par->AnzVals() ; i++)
      c->ClearlConnection (par->updateVal[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL DestroyDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    c->closed = TRUE ;
    GetAsync_cmdfifo()->DelDocumentEntrys(c->DocumentID());
    NoFurtherUpdates (c->DocumentID());
    PostMessage (WBase::hFrameWin,WMU_DESTROYCHILD,0,LONG(c));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CreateDialogDocument_param {
  WORD parSize;
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  };
#pragma pack()


BOOL CreateDialogDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateDialogDocument_param FAR *par = 
            (CreateDialogDocument_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData (par->DocName));
    if (docName != NULL) {
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (docName);
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      res->LoadData ();
#ifdef DEBUG
      PopFromCallStack ();
#endif
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreateDialogDocument_param FAR *par = 
            (CreateDialogDocument_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// Anlegen eines Dokumentes im Loadzweig und im Resetzweig das Dokument
// wieder zerstoeren
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct UseDialogDocument_extra {
  mdiChild *callerDocument;
  mdiChild *newDocument;
  };
#pragma pack()

#pragma pack(1)
struct FAR UseDialogDocument_param {
  WORD parSize;
  UseDialogDocument_extra FAR *x;
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  DWORD GetVarRef(int Code)
    {
    for (int i = 0 ; i < AnzExtra () ; i++) {
      DBINT Cd = *((DBINT FAR *) x->callerDocument->ReadlData (r[i].rCode));
      if (Cd == Code) return r[i].Ref ;
      }
    return 0xFFFFFFFF ;
    }
  BOOL mitCodeAlleine ()
    {
    if ((AnzExtra() - 1) * sizeof(r[0]) + sizeof(DWORD) + sizeof(*this) == parSize)
      return TRUE ;
    else
      return FALSE ;
    }
  };
#pragma pack()

BOOL UseDialogDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData (par->DocName));
    DBWIN_ASSERT (docName != NULL);
    // Und los kanns gehen
    mdiChild *res = NewDocInstance (docName);
    // Damit die Updatereihenfolge Scriptuebergreifend gewaehrleistet ist
    //--------------------------------------------------------------------
    res->_ccount_base = PushBlock (c->_ccount->Copy());
    DBWIN_ASSERT (res != NULL);
    res->GetOutData ()->_scale = float (1.0);
    for (int i = 0 ; i < par->AnzExtra () ; i++) {
      LPVOID Extra = c->ReadlData (par->r[i].Ref);
      if (Extra != NULL) {
        // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
        DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
        if (Code != NULL)
          res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
        }
      }
    if (par->mitCodeAlleine ()) {
      DBINT FAR *lCode = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
      if (*lCode == -1) {
        for ( DocExtraData FAR *h = c->_ed ; (h != NULL) ; h = h->Next) {
          res->PutDocumentExtraData (h->Type,h->Data,h->size);
          }
        }
      }
    res->cp.use = par ;
    par->x = (UseDialogDocument_extra FAR *) GetGlobMem (sizeof(*(par->x)));
    par->x->callerDocument = c;
    par->x->newDocument = res;
    res->LoadData ();
    }
  if (mode & EM_FIXCONNECTION) {
    // Eine Connection auf alle Extradaten setzten
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->SetlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    c->ClearlConnection (par->DocName,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    if (par->x->newDocument->commands) {
      GetAsync_cmdfifo()->DelDocumentEntrys(par->x->newDocument->DocumentID());
      NoFurtherUpdates (par->x->newDocument->DocumentID());
      par->x->newDocument->Reset ();
      par->x->newDocument->FreeExpNodes ();
      GlobalUnlock (par->x->newDocument->commands) ;
      GlobalFree (par->x->newDocument->commands) ;
      par->x->newDocument->commands = 0;
      }
    BOOL oldIsFromDestroy = IsFromDestroy ;
    IsFromDestroy = FALSE ;
    delete par->x->newDocument ;  // Synchorn aufbauen - Synchron abbauen
    IsFromDestroy = oldIsFromDestroy ;
    FreeGlobMem (par->x);
    par->x = NULL;
    }
  return FALSE ;
  }

BOOL UseDialogDocumentFormBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    BlobDesc FAR *b = (BlobDesc FAR *) c->ReadlData (par->DocName);
    if (b != NULL) {
      // DBWIN_ASSERT (b != NULL);
      // Und los kanns gehen
      mdiChild *res = NewDocInstance (b->hGmem);
      // Damit die Updatereihenfolge Scriptuebergreifend gewaehrleistet ist
      //--------------------------------------------------------------------
      res->_ccount_base = PushBlock (c->_ccount->Copy());
      DBWIN_ASSERT (res != NULL);
      res->GetOutData ()->_scale = float (1.0);
      for (int i = 0 ; i < par->AnzExtra () ; i++) {
        LPVOID Extra = c->ReadlData (par->r[i].Ref);
        if (Extra != NULL) {
          // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
          DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
          if (Code != NULL)
            res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
          }
        }
      res->cp.use = par ;
      par->x = (UseDialogDocument_extra FAR *) GetGlobMem (sizeof(*(par->x)));
      par->x->callerDocument = c;
      par->x->newDocument = res;
      res->CallerContext = c;
      res->LoadData ();
      }
    }
  if (mode & EM_FIXCONNECTION) {
    // Eine Connection auf alle Extradaten setzten
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->SetlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    UseDialogDocument_param FAR *par = 
            (UseDialogDocument_param FAR *) param;
    if (par->x != NULL) {
      if (par->x->newDocument->commands) {
        GetAsync_cmdfifo()->DelDocumentEntrys(par->x->newDocument->DocumentID());
        NoFurtherUpdates (par->x->newDocument->DocumentID());
        par->x->newDocument->Reset ();
        par->x->newDocument->FreeExpNodes ();
        GlobalUnlock (par->x->newDocument->commands) ;
        GlobalFree (par->x->newDocument->commands) ;
        par->x->newDocument->commands = 0;
        }
      BOOL oldIsFromDestroy = IsFromDestroy ;
      IsFromDestroy = FALSE ;
      delete par->x->newDocument ;  // Synchorn aufbauen - Synchron abbauen
      IsFromDestroy = oldIsFromDestroy ;
      FreeGlobMem (par->x);
      par->x = NULL;
      }
    c->ClearlConnection (par->DocName,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// Anlegen eines Dokumentes im Loadzweig und im Resetzweig das Dokument
// wieder zerstoeren, zusaetzlich Parameterblockadresse schreiben
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR UseDialogDocumentTellPar_param {
  WORD parSize;
  mdiChild *c;
  DWORD MyPar;      // an diese Referenz teile ich meinen Parameterblock mit
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  };
#pragma pack()

typedef UseDialogDocumentTellPar_param FAR *LPUDDTP;

BOOL UseDialogDocumentTellPar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    UseDialogDocumentTellPar_param FAR *par = 
            (UseDialogDocumentTellPar_param FAR *) param;
    LPSTR docName = LPSTR (c->ReadlData(par->DocName));
    DBWIN_ASSERT (docName != NULL);
    // Und los kanns gehen
    mdiChild *res = NewDocInstance (docName);
    DBWIN_ASSERT (res != NULL);
    res->GetOutData ()->_scale = float (1.0);
    for (int i = 0 ; i < par->AnzExtra () ; i++) {
      LPVOID Extra = c->ReadlData (par->r[i].Ref);
      if (Extra != NULL) {
        // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
        DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
        if (Code != NULL)
          res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
        }
      }
    res->LoadData ();
    par->c = res;
    // jetzt noch meine Parameterblockadresse schreiben
    c->WritelData (par->MyPar,&par,sizeof(LPUDDTP),LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    UseDialogDocumentTellPar_param FAR *par = 
            (UseDialogDocumentTellPar_param FAR *) param;
    if (par->c->commands) {
      GetAsync_cmdfifo()->DelDocumentEntrys(par->c->DocumentID());
      NoFurtherUpdates (par->c->DocumentID());
      par->c->Reset ();
      par->c->FreeExpNodes ();
      GlobalUnlock (par->c->commands) ;
      GlobalFree (par->c->commands) ;
      par->c->commands = 0;
      }
    SendMessage (WBase::hFrameWin,WMU_DESTROYCHILD,0,LONG(par->c));
    par->c = NULL;
    c->DellData (par->MyPar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// mdiChilds von zwei UseDialogDocuments austauschen
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR ChangeUseDialogDocumentPars_param {
  WORD parSize;
  DWORD par1;
  DWORD par2;
  };
#pragma pack()

BOOL ChangeUseDialogDocumentPars (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ChangeUseDialogDocumentPars_param FAR *par = 
            (ChangeUseDialogDocumentPars_param FAR *) param;
    LPUDDTP FAR *lppar1 = (LPUDDTP FAR *)c->ReadlData(par->par1);
    LPUDDTP FAR *lppar2 = (LPUDDTP FAR *)c->ReadlData(par->par2);
    DBWIN_ASSERT ((lppar1 != NULL) && (lppar2 != NULL));
    mdiChild *help = (*lppar1)->c;
    (*lppar1)->c = (*lppar2)->c;
    (*lppar2)->c = help;
    }

  return FALSE ;
  }

BOOL mdiChild::BestScaling ()
  {
  BOOL res = FALSE ;
  int MapType ;
  if ((schd->Type == CHWND_TRACING) || (schd->Type == CHWND_VTO))
    MapType = MAPTYPE_GEOMETRIC ;
  else
    MapType = MAPTYPE_TYPOGRAPHIC ;
  if (MapType == MAPTYPE_TYPOGRAPHIC) {
    if (GetOutData ()->Pr == NULL)
      GetOutData ()->Pr = GetPrinter (TRUE);
    res = GetBestScaling (GetOutData()->_MyHandle,MapType,&(GetOutData ()->_scale),GetOutData ()->Pr->PrinterDC());
    GetOutData()->Pr->ReleasePrDC();
    }
  return res;
  }

// Kopieren von Datenelementen aus einem anderen Datensatz (nur im LOAD !)
///////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR CopyFromRecord_param {
  WORD parSize;
  DWORD dst;
  DWORD src;
  DWORD ptr;
  };
#pragma pack()

BOOL CopyFromRecord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR Offset = LPSTR(param) - sizeof(WORD);
    CopyFromRecord_param FAR *par =
            (CopyFromRecord_param FAR *) param;
    LPDBRECORD FAR *rec = (LPDBRECORD FAR *) (c->ReadlData (par->ptr));
    DBWIN_ASSERT (rec != NULL);
    WORD TableInd = LOWORD(par->src);
    // Tabellentypen muessen uebereinstimmen
    DBWIN_ASSERT ((c->schd->TRef[TableInd-CSYSRECS].TableNr == (*rec)->GetTableID()) &&
                  (c->schd->TRef[TableInd-CSYSRECS].Version == (*rec)->GetVersion()));

    LPDBRECORD old = c->rr->GetRecord(TableInd);
    // voruebergehend auf den Quellrecord umschalten
    c->rr->SetRecord (TableInd,*rec);
    LPVOID data = c->ReadlData(par->src);
    // wieder zurueckschalten auf den eigenen record
    c->rr->SetRecord (TableInd,old);
    if (data != NULL)
      c->WritelData(par->dst,data,GetBlockSize(data),Offset);
    else
      c->DellData(par->dst,Offset);
    }

  return FALSE ;
  }

// Kopieren von Datenelementen in einen anderen Datensatz (nur im LOAD !)
///////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR CopyToRecord_param {
  WORD parSize;
  DWORD dst;
  DWORD src;
  DWORD ptr;
  };
#pragma pack()

BOOL CopyToRecord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR Offset = LPSTR(param) - sizeof(WORD);
    CopyToRecord_param FAR *par =
            (CopyToRecord_param FAR *) param;
    LPDBRECORD FAR *rec = (LPDBRECORD FAR *) (c->ReadlData (par->ptr));
    DBWIN_ASSERT (rec != NULL);
    LPVOID data = c->ReadlData(par->src);
    WORD TableInd = LOWORD(par->dst);
    // Tabellentypen muessen uebereinstimmen
    DBWIN_ASSERT ((c->schd->TRef[TableInd-CSYSRECS].TableNr == (*rec)->GetTableID()) &&
                  (c->schd->TRef[TableInd-CSYSRECS].Version == (*rec)->GetVersion()));

    LPDBRECORD old = c->rr->GetRecord(TableInd);
    // voruebergehend auf den Zielrecord umschalten
    c->rr->SetRecord (TableInd,*rec);
    if (data != NULL)
      c->WritelData(par->dst,data,GetBlockSize(data),Offset);
    else
      c->DellData(par->dst,Offset);
    // wieder zurueckschalten auf den eigenen record
    c->rr->SetRecord (TableInd,old);
    }

  return FALSE ;
  }

mdiChild *NewDocInstance (LPSTR docName)
  {
  LPSCRIPTCONTENT ent = GetScriptEntry(docName);
  char watxt[60];
  wsprintf(watxt,"Script %s nicht gefunden !",docName);
  DBWIN_ASSERT_TEXT (ent != NULL,watxt);
  switch (ent->Type) {
    case CHWND_FORM :
      return new Form (ent);
    case CHWND_TRACING :
    case CHWND_VTO :
      DBWIN_ASSERT_TEXT(FALSE,"typ tracing und simulation nicht mehr unterstuetzt !");
      break;
    default :
      DBWIN_ASSERT(FALSE);
    }

  return NULL ;
  }

mdiChild *NewDocInstance (GLOBALHANDLE hGmem)
  {
  LPSCRIPTCONTENT ent = GetScriptEntry(hGmem);
  switch (ent->Type) {
    case CHWND_FORM :
      return new Form (ent);
    case CHWND_TRACING :
    case CHWND_VTO :
      DBWIN_ASSERT_TEXT(FALSE,"typ tracing und simulation nicht mehr unterstuetzt !");
      break;
    default :
      DBWIN_ASSERT(FALSE);
    }

  SetHDataNULL (ent->fName);
  return NULL ;
  }

#pragma pack(1)
struct GetScriptProperty_param {
  WORD parSize;
  DWORD res;
  DWORD Script;
  DWORD Property;
  };
#pragma pack()

BOOL GetScriptProperty (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetScriptProperty_param FAR *par = (GetScriptProperty_param FAR *) param;
    LPSTR sc = LPSTR (c->ReadlData (par->Script));
    DBWIN_ASSERT (sc != NULL);
    LPSCRIPTCONTENT ent = GetScriptEntry(sc);
    char watxt[60];
    wsprintf(watxt,"Script %s nicht gefunden !",sc);
    DBWIN_ASSERT_TEXT (ent != NULL,watxt);
    LPSTR p = LPSTR (c->ReadlData (par->Property)) ;
    DBWIN_ASSERT (p != NULL);
    char buffer[512];
    if (ent->GetProperty (p,buffer,sizeof(buffer)))
      c->WritelData (par->res,buffer,lstrlen(buffer)+1,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetScriptProperty_Int (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetScriptProperty_param FAR *par = (GetScriptProperty_param FAR *) param;
    LPSTR sc = LPSTR (c->ReadlData (par->Script));
    DBWIN_ASSERT (sc != NULL);
    LPSCRIPTCONTENT ent = GetScriptEntry(sc);
    char watxt[60];
    wsprintf(watxt,"Script %s nicht gefunden !",sc);
    DBWIN_ASSERT_TEXT (ent != NULL,watxt);
    LPSTR p = LPSTR (c->ReadlData (par->Property)) ;
    DBWIN_ASSERT (p != NULL);
    char buffer[256];
    BOOL done = FALSE;
    if (ent->GetProperty (p,buffer,sizeof(buffer))) {
      int res ;
      if (done = (sscanf (buffer,"%d",&res) == 1))
        c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    if (!done)
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFirstScript_param {
  WORD parSize;
  DWORD res;
  DWORD name;
  DWORD prop[1];
  BOOL mitName ()
    { return parSize > (sizeof(WORD) + sizeof(DWORD)); }
  int anzProp ()
    { return (parSize >= (sizeof(WORD) + 3 * sizeof(DWORD))) ? (parSize - sizeof(*this)) / sizeof(DWORD) + 1 : 0 ; }
  };
#pragma pack()

BOOL GetFirstScriptInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFirstScript_param FAR *par = (GetFirstScript_param FAR *) param;
    char name[256];
    LPSTR prop[10];
    for ( int i = 0 ; i < par->anzProp() ; i++) {
      prop[i] = LPSTR(c->ReadlData (par->prop[i]));
      }
    LPSCRIPTCONTENT ent = GetFirstScript(par->anzProp(),prop,name);
    if (ent != NULL) {
      c->WritelData (par->res,&ent,sizeof(ent),LPSTR(param)-sizeof(WORD));
      if (par->mitName())
        c->WritelData (par->name,name,lstrlen(name) + 1,LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      if (par->mitName())
        c->DellData (par->name,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetNextScript_param {
  WORD parSize;
  DWORD res;
  DWORD old;
  DWORD name;
  DWORD prop[1];
  BOOL mitName ()
    { return parSize > (sizeof(WORD) + 2 * sizeof(DWORD)); }
  int anzProp ()
    { return (parSize >= (sizeof(WORD) + 4 * sizeof(DWORD))) ? (parSize - sizeof(*this)) / sizeof(DWORD) + 1 : 0 ; }
  };
#pragma pack()
BOOL GetNextScriptInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetNextScript_param FAR *par = (GetNextScript_param FAR *) param;
    LPSCRIPTCONTENT FAR *old = (LPSCRIPTCONTENT FAR *) c->ReadlData (par->old);
    DBWIN_ASSERT (old != NULL);
    char name[256];
    LPSTR prop[10];
    for ( int i = 0 ; i < par->anzProp() ; i++) {
      prop[i] = LPSTR(c->ReadlData (par->prop[i]));
      }
    LPSCRIPTCONTENT ent = GetNextScript(*old,par->anzProp(),prop,name);
    if (ent != NULL) {
      c->WritelData (par->res,&ent,sizeof(ent),LPSTR(param)-sizeof(WORD));
      if (par->mitName())
        c->WritelData (par->name,name,lstrlen(name) + 1,LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      if (par->mitName())
        c->DellData (par->name,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetScriptInfo_param {
  WORD parSize;
  DWORD res;
  DWORD ent;
  DWORD Num;
  };
#pragma pack()

#define SI_NAME                               0
#define SI_FNAME                              1
#define SI_CATEGORY                           2
#define SI_TYPE                               3
#define SI_DARFINFACHSEIN                     4
#define SI_DARFIMVERZEICHNISVORKOMMEN         5
#define SI_DARFINKRANKENGESCHICHTEVORKOMMEN   6
#define SI_ISTVERWEISERZEUGER                 7
#define SI_ISTVERWEISSPEICHERER               8
#define SI_NOMDI                              9
#define SI_BEARBEITESELEKTOR                  10
#define SI_DEFAULTVERWEISERZEUGER             11
#define SI_DEFAULTVERWEISSPEICHERER           12
#define SI_OPTIONSCRIPT                       13
#define SI_FORMTYPE                           14

BOOL GetScriptInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetScriptInfo_param FAR *par = (GetScriptInfo_param FAR *) param;
    LPSCRIPTCONTENT FAR *ent = (LPSCRIPTCONTENT FAR *) c->ReadlData (par->ent);
    DBWIN_ASSERT ((ent != NULL) && (*ent != NULL)) ;
    int ind = c->ReadConstInt (par->Num);
    switch (ind) {
      case SI_NAME                               :
        c->WritelData (par->res,(*ent)->Name,lstrlen((*ent)->Name) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_FNAME                              :
        c->WritelData (par->res,(*ent)->fName,lstrlen((*ent)->fName) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_CATEGORY                           :
        c->WritelData (par->res,&(*ent)->Category,sizeof((*ent)->Category),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_TYPE                               :
        c->WritelData (par->res,&(*ent)->Type,sizeof((*ent)->Type),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_DARFINFACHSEIN                     :
        c->WritelData (par->res,&(*ent)->DarfInFachsein,sizeof((*ent)->DarfInFachsein),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_DARFIMVERZEICHNISVORKOMMEN         :
        c->WritelData (par->res,&(*ent)->DarfImVerzeichnisVorkommen,sizeof((*ent)->DarfImVerzeichnisVorkommen),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_DARFINKRANKENGESCHICHTEVORKOMMEN   :
        c->WritelData (par->res,&(*ent)->DarfInKrankengeschichteVorkommen,sizeof((*ent)->DarfInKrankengeschichteVorkommen),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_ISTVERWEISERZEUGER                 :
        c->WritelData (par->res,&(*ent)->IstVerweisErzeuger,sizeof((*ent)->IstVerweisErzeuger),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_ISTVERWEISSPEICHERER               :
        c->WritelData (par->res,&(*ent)->IstVerweisSpeicherer,sizeof((*ent)->IstVerweisSpeicherer),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_NOMDI                              :
        c->WritelData (par->res,&(*ent)->NoMDI,sizeof((*ent)->NoMDI),LPSTR(param)-sizeof(WORD));
        break ;
      case SI_BEARBEITESELEKTOR                  :
        c->WritelData (par->res,(*ent)->BearbeiteSelektor,lstrlen((*ent)->BearbeiteSelektor) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_DEFAULTVERWEISERZEUGER             :
        c->WritelData (par->res,(*ent)->DefaultVerweisErzeuger,lstrlen((*ent)->DefaultVerweisErzeuger) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_DEFAULTVERWEISSPEICHERER           :
        c->WritelData (par->res,(*ent)->DefaultVerweisSpeicherer,lstrlen((*ent)->DefaultVerweisSpeicherer) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_OPTIONSCRIPT                       :
        c->WritelData (par->res,(*ent)->OptionScript,lstrlen((*ent)->OptionScript) + 1,LPSTR(param)-sizeof(WORD));
        break ;
      case SI_FORMTYPE                           :
        c->WritelData (par->res,&(*ent)->FormType,sizeof((*ent)->FormType),LPSTR(param)-sizeof(WORD));
        break ;
      default :
        DBWIN_ASSERT (FALSE);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetScriptInfo_param FAR *par = (GetScriptInfo_param FAR *) param;
    c->ClearlConnection (par->ent,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetScriptEntry (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetScriptInfo_param FAR *par = (GetScriptInfo_param FAR *) param;
    LPSTR nam = (LPSTR) c->ReadlData (par->ent);
    if (nam != NULL) {
      LPSCRIPTCONTENT res = GetScriptEntry(nam);
      if (res != NULL)
        c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR PackData_param {
  WORD parSize;
  DWORD pd;
  struct vDef {
    DWORD Id;
    DWORD obj;
    } v[1];
  int AnzVars()
    {
    return (parSize - (sizeof(*this) - sizeof(v[0]))) / sizeof(v[0]) ;
    }
  };
#pragma pack()

#pragma pack(1)
struct FAR vHeader {
  WORD count;
  };
struct FAR vElem {
  WORD Id;
  WORD dSize;
  vElem FAR *Next (int act,int count) 
    {
    if (act < count) return (vElem FAR *) (LPSTR(this + 1) + dSize) ;
    else             return NULL ;
    }
  };
#pragma pack()

LPVOID PushTinyData (LPVOID old,int VarID,LPVOID Data) 
  {
  if (Data == NULL) return old ;
  int oSize,nSize;
  if (old) oSize = GetBlockSize (old);
  else     oSize = sizeof(vHeader);
  nSize = oSize + GetBlockSize (Data) + sizeof (vElem);
  vHeader FAR *n = (vHeader FAR *) (GetGlobMem (nSize)) ;
  if (old) {
    lmemcpy (n,old,oSize);
    FreeGlobMem (old);
    }
  n->count += 1 ;
  vElem FAR *r = (vElem FAR *) (LPSTR (n) + oSize) ;
  r->Id = VarID ;
  r->dSize = GetBlockSize (Data);
  lmemcpy (r + 1,Data,r->dSize);

  return n ;
  }

BOOL PackData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PackData_param FAR * par = (PackData_param FAR *)param;
    // Die Daten extrahieren
    vHeader FAR *h = (vHeader FAR *) c->ReadlData (par->pd);
    if (h != NULL) {
      for (int i = 0 ; i < par->AnzVars () ; i++) {
        int j = 0 ;
        WORD VarId = WORD (c->ReadConstInt (par->v[i].Id)) ;
        for ( vElem FAR *e = (vElem FAR *) (h + 1) ; e != NULL ; j ++ , e = e->Next (j,h->count) ) {
          if (e->Id == VarId) {
            c->WritelData (par->v[i].obj,e+1,e->dSize,LPSTR(param)-sizeof(WORD));
            break ;
            }
          }
        if (e == NULL) {
          c->DellData (par->v[i].obj,LPSTR(param)-sizeof(WORD));
          }
        }
      }
    else {
      for (int i = 0 ; i < par->AnzVars () ; i++) {
        c->DellData (par->v[i].obj,LPSTR(param)-sizeof(WORD));
        }
      }
    }
  else if (mode & EM_UPDATE) {
    PackData_param FAR * par = (PackData_param FAR *)param;
    LPVOID res = NULL ;
    for (int i = 0 ; i < par->AnzVars() ; i++)
      res = PushTinyData (res,WORD(c->ReadConstInt(par->v[i].Id)),c->ReadlData (par->v[i].obj));
    if (res != NULL) {
      c->WritelData (par->pd,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->pd,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    PackData_param FAR * par = (PackData_param FAR *)param;
    for (int i = 0 ; i < par->AnzVars () ; i++)
      c->SetlConnection (par->v[i].obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    PackData_param FAR * par = (PackData_param FAR *)param;
    for (int i = 0 ; i < par->AnzVars () ; i++)
      c->ClearlConnection (par->v[i].obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SaveRecord_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  };
#pragma pack()

#pragma pack(1)
struct FAR RestoreRecord_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  DWORD fehlerFlag;
  DWORD doUpdateFlag;
  BOOL MitFehler ()
    {
    return (parSize >= sizeof(*this) - sizeof(DWORD));
    }
  BOOL MitDoUpdateFlag ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

LPVOID PushRecData (LPVOID old,int Num,LPVOID d)
  {
  if (old == NULL) {
    old = GetGlobMem (sizeof(WORD));
    *(WORD FAR *) old = 0 ;
    }
  int size = GetBlockSize(old) + GetBlockSize(d) + sizeof(WORD);
  LPVOID n = GetGlobMem (size);
  lmemcpy (n,old,GetBlockSize(old));
  (*(WORD FAR *) n) += 1 ;
  WORD FAR *sref = (WORD FAR *) (LPSTR(n) + GetBlockSize(old));
  *sref = GetBlockSize(d);
  if (d != NULL)
    lmemcpy (sref + 1,d,GetBlockSize(d));
  FreeGlobMem (old);
  return n ;
  }

LPVOID PushRecDataNum (LPVOID old,int Num,LPVOID d)
  {
  if (old == NULL) {
    old = GetGlobMem (sizeof(WORD));
    *(WORD FAR *) old = 0 ;
    }
  int size = GetBlockSize(old) + GetBlockSize(d) + 2 * sizeof(WORD);
  LPVOID n = GetGlobMem (size);
  lmemcpy (n,old,GetBlockSize(old));
  (*(WORD FAR *) n) += 1 ;
  WORD FAR *hdref = (WORD FAR *) (LPSTR(n) + GetBlockSize(old));
  hdref[0] = Num;
  hdref[1] = GetBlockSize(d);
  if (d != NULL)
    lmemcpy (hdref + 2,d,GetBlockSize(d));
  FreeGlobMem (old);
  return n ;
  }

LPVOID DelRecData (LPVOID old,WORD Num)
  {
  if (old == NULL) return NULL ;
  int count = *(WORD FAR *) old ;
  LPSTR h = LPSTR(old) + sizeof(WORD);
  LPSTR end = LPSTR (old) + GetBlockSize (old) ;
  for (int i = 0 ; i < count ; i++) {
    int size = ((WORD FAR *) h)[1] ;
    if (h + 2 * sizeof(WORD) + size > end) {
      // Daten sind bereits korrupt, wieder reparieren und zurueck
      LPSTR n = LPSTR (GetGlobMem (h - LPSTR(old)));
      lmemcpy (n,old,h - LPSTR(old));
      ((WORD FAR *) n)[0] = i + 1 ;
      FreeGlobMem (old);
      return n;
      }
    if (((WORD FAR *) h)[0] == Num) {
      LPSTR n = LPSTR(GetGlobMem (GetBlockSize(old) - 2 * sizeof(WORD) - size));
      lmemcpy (n,old,h - LPSTR(old));
      int rOffs = h - LPSTR(old) + size + 2 * sizeof(WORD);
      int rOffsN = h - LPSTR(old) ;
      int rsize = GetBlockSize (old) - rOffs ;
      if (rsize > 0)
        lmemcpy (n + rOffsN,h + 2 * sizeof(WORD) + size,rsize);
      ((WORD FAR *) n)[0] -= 1 ;
      if (((WORD FAR *) n)[0] == 0) FreeGlobMem (n) , n = NULL ;
      FreeGlobMem (old);
      return n ;
      }
    h += 2 * sizeof(WORD) + size ;
    }
  return old ;
  }

LPVOID GetRecData (LPVOID old,WORD Num,int FAR *lpsize,WORD gSize)
  {
  if (old == NULL) return NULL ;
  int count = *(WORD FAR *) old ;
  LPSTR h = LPSTR(old) + sizeof(WORD);
  LPSTR end = LPSTR(old) + gSize;
  for (int i = 0 ; i < count ; i++) {
    int size = ((WORD FAR *) h)[1] ;
    if (*(WORD FAR *) h == Num) {
      *lpsize = size ;
      return h + 2 * sizeof(WORD) ;
      }
    LPSTR hNew = h + 2 * sizeof(WORD) + size ;
    if (hNew < end) h = hNew ;
    else            return NULL ;
    }
  return NULL ;
  }

BOOL SaveRecord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SaveRecord_param FAR *par = (SaveRecord_param FAR *) param ;
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    WORD tid,Version;
    int ti = GetTableNr (c->schd,&tid,&Version,TableName);
    DBWIN_ASSERT(ti >= 0);
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(tid,Version);
    LPDBRECORD rec = c->rr->GetRecord (ti);
    if (rec != NULL) {
      LPVOID p = NULL ;
      for (int i = 0 ; i < int(rec->GetAnzVars()) ; i++) {
        p = PushRecData (p,i,rec->Get(i));
        }
      c->WritelData (par->res,p,GetBlockSize(p),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (p);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  return FALSE ;
  }

#define MAXSIZE   20000
BOOL RestoreRecord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RestoreRecord_param FAR *par = (RestoreRecord_param FAR *) param ;
    LPVOID p = c->ReadlData (par->res);
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    BOOL doUpdate;
    if (par->MitDoUpdateFlag() && (*(LPBOOL (c->ReadlData (par->doUpdateFlag)))))
      doUpdate = UPDATE_ASYNCHRON;
    else
      doUpdate = FALSE;
    WIN_ASSERT (TableName);
    WORD tid,Version;
    int ti = GetTableNr (c->schd,&tid,&Version,TableName);
    DBWIN_ASSERT(ti >= 0);
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(tid,Version);
    LPDBRECORD rec = c->rr->GetRecord (ti);
    DBWIN_ASSERT (rec != NULL);
    DBBOOL Fehler = FALSE ;
    if (p != NULL) {
      WORD FAR *sref = (WORD FAR *) p ;
      WORD savedanz = *sref;
      DBWIN_ASSERT (savedanz <= rec->GetAnzVars()) ;
      for (int i = int(savedanz); i < int(rec->GetAnzVars()); i++)
        rec->Del (i,LPSTR(param)-sizeof(WORD),doUpdate);

      LPSTR ende = LPSTR (sref) + GetBlockSize (sref);
      sref += 1 ;
      for (i = 0 ; ((i < int(savedanz)) && (!Fehler)) ; i++) {
        WORD offs = *sref;
        if ((offs < MAXSIZE) && (LPSTR(sref) + sizeof(WORD) + offs <= ende)) {
          WORD FAR *next = (WORD FAR *) (LPSTR(sref) + sizeof(WORD) + *sref) ;
          if (*sref != 0)
            rec->Set (i,sref + 1,*sref,LPSTR(param)-sizeof(WORD),doUpdate);
          else
            rec->Del (i,LPSTR(param)-sizeof(WORD),doUpdate);
          sref = next;
          }
        else
          Fehler = TRUE ;
        }
      }
    else {
      for (int i = 0 ; i < int(rec->GetAnzVars()) ; i++)
        rec->Del (i,LPSTR(param)-sizeof(WORD),NULL,doUpdate);
      }
    if (par->MitFehler())
      c->WritelData (par->fehlerFlag,&Fehler,sizeof(Fehler),LPSTR(param)-sizeof(WORD));

    GetTableAdmin()->FreeTable(td->GetTableID(),Version);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR PushData_param {
  WORD parSize;
  DWORD handle;
  struct {
    DWORD Code;
    DWORD Data;
    } p[1];
  int AnzPairs ()
    {
    return (parSize - (sizeof(*this) - sizeof(p[0]))) / sizeof(p[1]) ;
    }
  };
#pragma pack()

BOOL PushData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    LPVOID obj = c->TryToReadData (par->handle);
    LPVOID objc ;
    if (obj != NULL) {
      objc = GetGlobMem (GetBlockSize(obj));
      lmemcpy (objc,obj,GetBlockSize(obj));
      }
    else
      objc = NULL ;
    for (int i = 0 ; i < par->AnzPairs () ; i++) {
      DBINT FAR *code = (DBINT FAR *) c->ReadlData (par->p[i].Code);
      DBWIN_ASSERT (code != NULL);
      LPVOID data = c->ReadlData (par->p[i].Data);
      objc = DelRecData (objc,*code);
      if (data != NULL)
        objc = PushRecDataNum (objc,*code,data);
      }
    if (objc != NULL) {
      c->WritelData (par->handle,objc,GetBlockSize(objc),LPSTR(param) - sizeof(WORD));
      FreeGlobMem (objc);
      }
    else
      c->DellData (par->handle,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    for (int i = 0 ; i < par->AnzPairs () ; i++) {
      c->ClearlConnection (par->p[i].Data,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->p[i].Code,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

BOOL PushDataMit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    LPVOID obj = c->ReadlData (par->handle);
    LPVOID objc ;
    if (obj != NULL) {
      objc = GetGlobMem (GetBlockSize(obj));
      lmemcpy (objc,obj,GetBlockSize(obj));
      }
    else
      objc = NULL ;
    for (int i = 0 ; i < par->AnzPairs () ; i++) {
      DBINT FAR *code = (DBINT FAR *) c->ReadlData (par->p[i].Code);
      DBWIN_ASSERT (code != NULL);
      LPVOID data = c->ReadlData (par->p[i].Data);
      objc = DelRecData (objc,*code);
      if (data != NULL)
        objc = PushRecDataNum (objc,*code,data);
      }
    if (objc != NULL) {
      c->WritelData (par->handle,objc,GetBlockSize(objc),LPSTR(param) - sizeof(WORD));
      FreeGlobMem (objc);
      }
    else
      c->DellData (par->handle,LPSTR(param) - sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    for (int i = 0 ; i < par->AnzPairs () ; i++)
      c->SetlConnection (par->p[i].Data,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    for (int i = 0 ; i < par->AnzPairs () ; i++) {
      c->ClearlConnection (par->p[i].Data,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->p[i].Code,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

BOOL PopData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    LPVOID obj = c->ReadlData (par->handle);
    for (int i = 0 ; i < par->AnzPairs () ; i++) {
      DBINT FAR *code = (DBINT FAR *) c->ReadlData (par->p[i].Code);
      LPVOID data ;
      int size;
      if ((obj) && (code))
        data = GetRecData (obj,*code,&size,GetBlockSize(obj));
      else
        data = NULL ;
      BOOL done = FALSE;
      LPVOID old = c->TryToReadData (par->p[i].Data,&done);
      if (data) {
        if ((old == NULL) ||
            (GetBlockSize(old) != size) ||
            (!lmemcmp (old,data,size)))
          c->WritelData (par->p[i].Data,data,size,LPSTR(param)-sizeof(WORD));
        }
      else {
        if ((old != NULL) || (!done))
          c->DellData (par->p[i].Data,LPSTR(param)-sizeof(WORD));
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    c->SetlConnection (par->handle,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPairs () ; i++)
      c->SetlConnection (par->p[i].Code,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PushData_param FAR *par = (PushData_param FAR *) param;
    c->ClearlConnection (par->handle,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPairs () ; i++)
      c->ClearlConnection (par->p[i].Code,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

inline mdiChild *GetOutContext(mdiChild *c)
  {
  return (c->outContext != NULL) ? c->outContext : c ; 
  }

#pragma pack(1)
struct FAR DocumentToPrinter_param {
  WORD parSize;
  mdiChild *c;
  DWORD PrinterDocument;
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  };
#pragma pack()

BOOL DocumentToPrinter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DocumentToPrinter_param FAR *par = 
            (DocumentToPrinter_param FAR *) param;
    LPMDICHILD FAR *pd = (LPMDICHILD FAR *) c->ReadlData (par->PrinterDocument);
    DBWIN_ASSERT ((pd != NULL) && (*pd != NULL)) ;
    LPSTR docName = LPSTR (c->ReadlData (par->DocName));
    DBWIN_ASSERT (docName != NULL);
    // Und los kanns gehen
    mdiChild *res = NewDocInstance (docName);
    DBWIN_ASSERT (res != NULL);
    res->GetOutData()->_scale = float (1.0);
    for (int i = 0 ; i < par->AnzExtra () ; i++) {
      LPVOID Extra = c->ReadlData (par->r[i].Ref);
      if (Extra != NULL) {
        // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
        DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
        if (Code != NULL)
          res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
        }
      }
    res->LoadData ();
    par->c = res;
    res->ToPrinter (GetOutContext(*pd)->GetOutData()->Pr,TRUE,0);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    DocumentToPrinter_param FAR *par = 
            (DocumentToPrinter_param FAR *) param;
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    if (par->c->commands) {
      par->c->Reset ();
      par->c->FreeExpNodes();
      GlobalUnlock (par->c->commands) ;
      GlobalFree (par->c->commands) ;
      par->c->commands = 0;
      }
    SendMessage (WBase::hFrameWin,WMU_DESTROYCHILD,0,LONG(par->c));
    par->c = NULL;
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR DocumentToPrinterFromBlobEx_param {
  WORD parSize;
  mdiChild *c;
  DWORD PrinterDocument;
  DWORD DocName;    // Name des Dokumentes, das erzeugt werden soll
  DWORD xOffs,yOffs;    // Extra - Offset in Logischen Einheiten
  ExtraRef r[1];
  int AnzExtra ()
    { return (parSize - (sizeof (*this) - sizeof(r[0]))) / sizeof(r[0]) ; }
  };
#pragma pack()

BOOL DocumentToPrinterFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DocumentToPrinterFromBlobEx_param FAR *par = 
            (DocumentToPrinterFromBlobEx_param FAR *) param;
    LPMDICHILD FAR *pd = (LPMDICHILD FAR *) c->ReadlData (par->PrinterDocument);
    DBWIN_ASSERT ((pd != NULL) && (*pd != NULL)) ;
    LPBLOBDESC docName = LPBLOBDESC (c->ReadlData (par->DocName));
    DBWIN_ASSERT (docName != NULL);
    // Und los kanns gehen
    mdiChild *res = NewDocInstance (docName->hGmem);
    DBWIN_ASSERT (res != NULL);
    res->GetOutData()->_scale = float (1.0);
    for (int i = 0 ; i < par->AnzExtra () ; i++) {
      LPVOID Extra = c->ReadlData (par->r[i].Ref);
      if (Extra != NULL) {
        // DBWIN_ASSERT (c->IsConst (par->r[i].rCode));
        DBINT FAR *Code = (DBINT FAR *) c->ReadlData (par->r[i].rCode);
        if (Code != NULL)
          res->PutDocumentExtraData (*Code,Extra,GetBlockSize(Extra));
        }
      }
    res->LoadData ();
    par->c = res;
    PaintContext pcprinter (GetOutContext(*pd)->GetOutData()->Pr);
    pcprinter.LogicalTwips (0,0,float(1.0));
    DBINT FAR *x = (DBINT FAR *) c->ReadlData (par->xOffs);
    DBINT FAR *y = (DBINT FAR *) c->ReadlData (par->yOffs);
    ((Form FAR *) res)->xPrinterOffs = - pcprinter.XLOGtoPHYS(*x);
    ((Form FAR *) res)->yPrinterOffs = - pcprinter.YLOGtoPHYS(*y);
    res->ToPrinter (GetOutContext(*pd)->GetOutData()->Pr,TRUE,0);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    DocumentToPrinterFromBlobEx_param FAR *par = 
            (DocumentToPrinterFromBlobEx_param FAR *) param;
    c->ClearlConnection (par->DocName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->xOffs,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yOffs,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzExtra () ; i++)
      c->ClearlConnection (par->r[i].Ref,LPSTR(param)-sizeof(WORD));
    if (par->c->commands) {
      par->c->Reset ();
      par->c->FreeExpNodes();
      GlobalUnlock (par->c->commands) ;
      GlobalFree (par->c->commands) ;
      par->c->commands = 0;
      }
    SendMessage (WBase::hFrameWin,WMU_DESTROYCHILD,0,LONG(par->c));
    par->c = NULL;
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetParameter_param {
  WORD parSize;
  DWORD cfRef;
  DWORD Code;
  };
#pragma pack()

extern DWORD GetVarRef (ExtChild_param FAR *par,int Code,LPMDICHILD FAR *cd);
#define EXTERNDOCUMENT          596
#define EXTERNDOCUMENTFROMBLOB  804
DWORD GetVarRef (mdiChild *c,int Code,LPMDICHILD FAR *callerDocument)
  {
  if (c->cp.ext != NULL) {
    if ((LPTOOLHEADER(c->cp.ext)->ToolType == EXTERNDOCUMENT) ||
        (LPTOOLHEADER(c->cp.ext)->ToolType == EXTERNDOCUMENTFROMBLOB))
      return GetVarRef (c->cp.ext,Code,callerDocument);
    else {
      *callerDocument = c->cp.use->x->callerDocument ;
      return c->cp.use->GetVarRef (Code);
      }
    }
  else return 0L;
  }

BOOL GetScriptParameter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetParameter_param FAR *par = (GetParameter_param FAR *) param ;
    int Code = c->ReadConstInt (par->Code);
    int size;
    LPVOID Data = c->GetDocumentExtraData (Code,&size);
    if (Data != NULL)
      c->WritelData (par->cfRef,Data,size,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->cfRef,LPSTR(param)-sizeof(WORD));
    if (c->cp.use != NULL) {
      LPVARELEM v1 = c->GetVarElem (par->cfRef);
      LPMDICHILD callerDocument;
      DWORD oRef = GetVarRef (c,Code,&callerDocument);
      LPVARELEM v2;
      if (oRef != 0xFFFFFFFF)
        v2 = callerDocument->GetVarElem (oRef);
      else
        v2 = NULL ;
      if ((v1 != NULL) && (v2 != NULL)) {
        v1->FillIn (v2);
        v1->Property |= VEP_PARAM ;
        v1->AnzahlVerwendetMitParameter ++ ;
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    GetParameter_param FAR *par = (GetParameter_param FAR *) param ;
    LPVARELEM v = c->GetVarElem (par->cfRef);
    v->AnzahlVerwendetMitParameter -- ;
    if (v->AnzahlVerwendetMitParameter == 0) {
      if (v->NextSame != NULL) {
        for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
        p->NextSame = v->NextSame ;
        if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
        v->NextSame = NULL;
        }
      }
    }
  return FALSE ;
  }


#pragma pack(1)
struct SetDocCaption_param {
  WORD parSize;
  DWORD txt;
  };
#pragma pack()

BOOL SetDocumentTitle (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetDocCaption_param FAR *par = (SetDocCaption_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    HWND hWnd = c->OutWnd();
    if (IsWindow(hWnd))
      SetWindowText (hWnd, txt);
    }
  if (mode & EM_FIXCONNECTION) {
    SetDocCaption_param FAR *par = (SetDocCaption_param FAR *) param;
    c->SetlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetDocCaption_param FAR *par = (SetDocCaption_param FAR *) param;
    c->ClearlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }
  
BOOL DoDBRep (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    CheckDBOut ();
  return FALSE ;
  }

BOOL DoDBRepIn (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    CheckDBIn ();
  return FALSE ;
  }

#pragma pack(1)
struct GetDBToken_param {
  WORD parSize;
  DWORD lres;
  DWORD fres;
  DWORD tName;
  DWORD pKey;
  };
#pragma pack()

extern BOOL InClientTransaction;
extern void deleteAllOpenChilds ();
BOOL GetDBToken (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDBToken_param FAR *par = (GetDBToken_param FAR *) param ;
    LPSTR TableName = LPSTR(c->ReadlData (par->tName));
    LPVOID pKey = c->ReadlData (par->pKey);
    DBWIN_ASSERT ((TableName != NULL) && (pKey));
    BOOL showLockedScreen;
    InClientTransaction = TRUE ;
    LONG lRes = GetDBToken (TableName,pKey,&showLockedScreen);
    InClientTransaction = FALSE ;
    // Sicherheitshalber eine WMU_CALLCOMMAND reinstellen
    PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
    deleteAllOpenChilds ();
    if (lRes > 0L) {
      c->DellData (par->fres,LPSTR (param) - sizeof(WORD));
      c->WritelData (par->lres,&lRes,sizeof(lRes),LPSTR (param) - sizeof(WORD));
      }
    else {
      c->WritelData (par->fres,&showLockedScreen,sizeof(showLockedScreen),LPSTR (param) - sizeof(WORD));
      c->DellData (par->lres,LPSTR (param) - sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct UnlockDBToken_param {
  WORD parSize;
  DWORD tnum;
  };
#pragma pack()
BOOL UnlockDBToken (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    UnlockDBToken_param FAR *par = (UnlockDBToken_param FAR *) param ;
    LPDWORD lptnum = LPDWORD (c->ReadlData (par->tnum));
    DBWIN_ASSERT (lptnum != NULL);
    UnlockDBToken (*lptnum);
    }
  return FALSE ;
  }

BOOL ClearMyTokens (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ClearMyTokens ();
    }
  return FALSE ;
  }

#pragma pack(1)
struct MarkVar_param {
  WORD parSize;
  DWORD ref;
  };
#pragma pack()
BOOL MarkVarStatic (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MarkVar_param FAR *par = (MarkVar_param FAR *) param ;
    LPDBRECORD r = c->rr->GetRecord(LOWORD(par->ref)) ;
    LPVARELEM v = r->GetVarElem(HIWORD(par->ref));
    v->Property |= VEP_STATIC ;
    }
  return FALSE ;
  }

BOOL MarkVarDynamic (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MarkVar_param FAR *par = (MarkVar_param FAR *) param ;
    LPDBRECORD r = c->rr->GetRecord(LOWORD(par->ref)) ;
    LPVARELEM v = r->GetVarElem(HIWORD(par->ref));
    v->Property &= ~VEP_STATIC ;
    }
  return FALSE ;
  }

LPDBRECORD FindRecordInCycl (LPDBRECORD rs,TableRef FAR *x)
  {
  for (LPDBRECORD h = rs ; h != NULL ; h = h->NextInCycl ) {
    if (lmemcmp (&h->tRef,x,sizeof(*x))) return h ;
    if (h->NextInCycl == rs) break ;
    }
  return NULL ;
  }

void PushToCycl (LPDBRECORD rs,LPDBRECORD rd)
  {
  if (rs->NextInCycl) rd->NextInCycl = rs->NextInCycl , rs->NextInCycl = rd ;
  else                rs->NextInCycl = rd , rd->NextInCycl = rs ;
  }

void mdiChild::SetContextRecords (mdiChild *source,int AnzRecords,LPWORD destInd,LPWORD sourceInd)
  {
  for (int i = 0 ; i < AnzRecords ; i++) {
    LPDBRECORD rs = source->rr->GetRecord(sourceInd[i] + CSYSRECS);
    if (rs == NULL) {
      char outtxt[256];
      wsprintf (outtxt,"Tabelle %s nicht im Kontext!",GetTableAdmin()->GetTableDef (source->schd->TRef[sourceInd[i]].TableNr,source->schd->TRef[sourceInd[i]].Version)->GetName());
      DBWIN_ASSERT_TEXT (FALSE,outtxt);
      }

    // Herstellen der doppelt verketteten RecRoot - Liste
    RecRootRef FAR *pr = rr->PrevInKontext + destInd[i] + CSYSRECS;
    RecRootRef FAR *nr = rr->NextInKontext + destInd[i] + CSYSRECS;

    pr->rr = source->rr;
    pr->tnr = sourceInd[i] + CSYSRECS;
    pr->rrOwner = source;

    *nr = source->rr->NextInKontext[sourceInd[i] + CSYSRECS];

    pr->rr->NextInKontext[pr->tnr].rr = rr;
    pr->rr->NextInKontext[pr->tnr].tnr = destInd[i] + CSYSRECS;
    pr->rr->NextInKontext[pr->tnr].rrOwner = this;

    if (nr->rr != NULL) {
      nr->rr->PrevInKontext[nr->tnr].rr = rr;
      nr->rr->PrevInKontext[nr->tnr].tnr = destInd[i] + CSYSRECS;
      nr->rr->PrevInKontext[nr->tnr].rrOwner = this;
      }

    int j = 0 ;
    BOOL oneFound = FALSE ;
    for ( TableRef x = schd->TRef[destInd[i]] ; x.TableNr != 0 ; ) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (x.TableNr,x.Version);
      LPDBRECORD rd = FindRecordInCycl (rs,&x);
      if (rd == NULL) {
        rd = new DBRecord (td);
        PushToCycl (rs,rd);
        }
      else
        oneFound = TRUE ;
      rr->SetRecord (destInd[i] + j + CSYSRECS,rd);
      TableRef xnext = td->tRefParent ;
      GetTableAdmin()->FreeTable (x.TableNr,x.Version);
      j ++ ;
      x = xnext ;
      }
    DBWIN_ASSERT (oneFound);
    }
  }

void mdiChild::DelContextRecords (int AnzRecords,LPWORD destInd)
  {
  for (int i = 0 ; i < AnzRecords ; i++) {
    int j = 0 ;
    for ( TableRef x = schd->TRef[destInd[i]] ; x.TableNr != 0 ; ) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (x.TableNr,x.Version);
      rr->SetRecord (destInd[i] + j + CSYSRECS,NULL);
      TableRef xnext = td->tRefParent ;
      GetTableAdmin()->FreeTable (x.TableNr,x.Version);
      j ++ ;
      x = xnext ;
      }
    }
  }

BOOL DenyBusy (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) DenyBusyCursor();
  return FALSE ;
  }

BOOL AllowBusy (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) AllowBusyCursor();
  return FALSE ;
  }

DLLExport void _export WINAPI NoManipulate (WORD TableNr,WORD Version,LPSTR VersionFromTable);
#pragma pack(1)
struct NoManipulate_param {
  WORD parSize;
  DWORD TableName;
  DWORD VersionFrom;
  };
#pragma pack()
BOOL NoManipulate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    NoManipulate_param FAR *par = (NoManipulate_param FAR *) param;
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    LPSTR VersionFrom = LPSTR (c->ReadlData (par->VersionFrom));
    DBWIN_ASSERT ((TableName != NULL) && (VersionFrom != NULL));
    BOOL found;
    WORD Version;
    WORD TableId = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
    DBWIN_ASSERT (found);
    NoManipulate (TableId,Version,VersionFrom);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CreateMemoryFile_param {
  WORD parSize;
  DWORD handle;
  DWORD FileName;
  };

#define MEMSIZE 0x4000
struct FAR MFHandle {
  HANDLE hMapObject;
  LPVOID MapView;
  };
#pragma pack()

BOOL CreateMemoryFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateMemoryFile_param FAR *par = (CreateMemoryFile_param FAR *) param;
    LPSTR fn = (LPSTR)c->ReadlData (par->FileName);
    DBWIN_ASSERT(fn != NULL);
    MFHandle h;
    h.hMapObject = CreateFileMapping ((HANDLE) 0xFFFFFFFF,
                                     NULL,
                                     PAGE_READWRITE,
                                     0,
                                     MEMSIZE,
                                     fn);
  
    h.MapView = MapViewOfFile (h.hMapObject,FILE_MAP_WRITE,0, 0, 0);
    c->WritelData (par->handle,&h,sizeof(h),LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CreateMemoryFile_param FAR *par = (CreateMemoryFile_param FAR *) param;
    c->ClearlConnection (par->FileName,LPSTR(param)-sizeof(WORD));
    MFHandle FAR *h = (MFHandle FAR *)c->ReadlData (par->handle);
    DBWIN_ASSERT(h != NULL);
    CloseHandle (h->hMapObject);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR ReadMemoryFile_param {
  WORD parSize;
  DWORD handle;
  DWORD pos;
  DWORD size;
  DWORD res;
  };
#pragma pack()

BOOL ReadMemoryFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ReadMemoryFile_param FAR *par = (ReadMemoryFile_param FAR *) param;
    MFHandle FAR *h = (MFHandle FAR *)c->ReadlData (par->handle);
    DBWIN_ASSERT(h != NULL);
    LPDWORD lppos = (LPDWORD)c->ReadlData (par->pos);
    LPDWORD lpsize = (LPDWORD)c->ReadlData (par->size);
    if ((lppos != NULL) && (lpsize != NULL)) {
      DBWIN_ASSERT((*lppos + *lpsize) < MEMSIZE);
      c->WritelData (par->res,LPSTR(h->MapView) + *lppos,(int)*lpsize,LPSTR(param) - sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ReadMemoryFile_param FAR *par = (ReadMemoryFile_param FAR *) param;
    c->ClearlConnection (par->pos,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR WriteMemoryFile_param {
  WORD parSize;
  DWORD handle;
  DWORD pos;
  DWORD data;
  };
#pragma pack()

BOOL WriteMemoryFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteMemoryFile_param FAR *par = (WriteMemoryFile_param FAR *) param;
    MFHandle FAR *h = (MFHandle FAR *)c->ReadlData (par->handle);
    DBWIN_ASSERT(h != NULL);
    LPDWORD lpdata = (LPDWORD)c->ReadlData (par->data);
    LPDWORD lppos = (LPDWORD)c->ReadlData (par->pos);
    if ((lpdata != NULL) && (lppos != NULL)) {
      WORD size = GetBlockSize(lpdata);
      DBWIN_ASSERT((*lppos + size) < MEMSIZE);
      lmemcpy(LPSTR(h->MapView) + *lppos,lpdata,size);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WriteMemoryFile_param FAR *par = (WriteMemoryFile_param FAR *) param;
    c->ClearlConnection (par->data,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->pos,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR PostWinMessage_param {
  WORD parSize;
  DWORD handle;
  DWORD msg;
  DWORD wP;
  DWORD lP;
  };
#pragma pack()

BOOL PostWinMessage (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef WIN32
  if (mode & EM_LOAD) {
    PostWinMessage_param FAR *par = (PostWinMessage_param FAR *) param;
    LPDWORD lphandle = (LPDWORD)c->ReadlData (par->handle);
    LPDWORD lpmsg = (LPDWORD)c->ReadlData (par->msg);
    LPDWORD lpwP = (LPDWORD)c->ReadlData (par->wP);
    LPDWORD lplP = (LPDWORD)c->ReadlData (par->lP);
    if ((lphandle != NULL) && (lpmsg != NULL) && (lpwP != NULL) && (lplP != NULL))
      PostMessage ((HWND)*lphandle,*lpmsg,*lpwP,*lplP);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PostWinMessage_param FAR *par = (PostWinMessage_param FAR *) param;
    c->ClearlConnection (par->handle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->msg,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->wP,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->lP,LPSTR(param)-sizeof(WORD));
    }
#endif
  return FALSE ;
  }

BOOL HaltQueue (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    InClientTransaction = TRUE;
  return FALSE ;
  }

extern BOOL CallCommandInClientTransaction;
BOOL ResumeQueue (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct DataWithName_param {
  WORD parSize;
  DWORD res;
  DWORD dt;
  DWORD recPtr;
  DWORD Name;
  };
#pragma pack()

BOOL DataWithName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DataWithName_param FAR *par = (DataWithName_param FAR *) param;
    LPDBRECORD FAR *lprec = (LPDBRECORD FAR *) c->ReadlData (par->recPtr);
    LPSTR lpName = LPSTR (c->ReadlData (par->Name));
    BOOL found = FALSE;
    if ((lprec != NULL) && (*lprec != NULL) && (lpName != NULL)) {
      WORD dt;
      WORD tid = (*lprec)->GetTableID();
      WORD tv = (*lprec)->GetVersion();
      LPTABLEDEF td = GetTableAdmin()->GetTableDef(tid,tv);
      WORD VarID = td->GetVarID (lpName,&dt,&found);
      GetTableAdmin()->FreeTable(tid,tv);
      if (found) {
        c->WritelData (par->dt,&dt,sizeof(dt),LPSTR(param)-sizeof(WORD));
        LPVOID res = (*lprec)->Get (VarID);
        if (res != NULL)
          c->WritelData (par->res,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
        else
          c->DellData (par->res,LPSTR (param) - sizeof(WORD));
        }
      }
    if (!found) {
      c->DellData (par->res,LPSTR (param) - sizeof(WORD));
      c->DellData (par->dt,LPSTR (param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DataWithName_param FAR *par = (DataWithName_param FAR *) param;
    c->ClearlConnection (par->Name,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->recPtr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

