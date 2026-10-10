//------------------------------------------------------
//      Steuerung der vom Compiler gelieferten          
//                    Anweisungen                             
//------------------------------------------------------
//
// $Header:   P:/marille/clinicum/rev/interpr.cpv   1.111   14 Dec 1999 13:10:44   Hannes  $
// $Log:   P:/marille/clinicum/rev/interpr.cpv  $
// 
//    Rev 1.111   14 Dec 1999 13:10:44   Hannes
// Updatereihenfolge bei Expressions in if
// 
//    Rev 1.110   30 Nov 1999 12:52:50   Hannes
// 
//    Rev 1.109   30 Nov 1999 12:14:50   Hannes
// Verbesserte Fehlerausgabe..
// 
//    Rev 1.108   20 Oct 1999 07:50:44   Hannes
// 
//    Rev 1.107   07 Jul 1999 07:51:36   Hannes
// Updatereihenfolge von Funktionsargumenten...
// 
//    Rev 1.106   07 Jun 1999 09:15:10   Hannes
// GetListData
// 
//    Rev 1.105   12 May 1999 17:16:38   Wolfgang
// 1.) Bei nicht Finden in DoForAll pruefen, ob korrekte Segmente angegeben.
// 
//    Rev 1.104   03 May 1999 15:57:20   Wolfgang
// 1.) SetCmpData auf abgeleitete Strukturen umgebaut.
// 2.) Find benutzt nur mehr FindRecord mit Mode Parameter.
// 3.) Compare benutzt CompareEqual Funktion.
// 
//    Rev 1.103   29 Mar 1999 11:35:58   Hannes
// Fehlerkorrektur bei DoInsert: c->InListFunction -> fp->c->InListFunction
// 
//    Rev 1.102   26 Mar 1999 18:15:48   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.101   17 Feb 1999 21:02:52   Hannes
// With mit leeren Listen
// 
//    Rev 1.100   28 Jan 1999 12:20:04   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.99   11 Jan 1999 08:20:30   Hannes
// Update von Funktionen in Listen
// 
//    Rev 1.98   26 Jun 1998 12:33:58   Martin
// OnThrowRecord: beim ExCuteWith im Extra==NULL Fall auch die ExtraSize retten
// 
//    Rev 1.97   11 Jun 1998 23:46:26   Hannes
// Wiederherstellung des Contextes nach dem CallCommand (ClearQueue)...
// 
//    Rev 1.96   14 May 1998 16:34:26   Martin
// for ... select -100 from ... -> der Cursor wird nicht offengelassen
// (selbes Verhalten wie eine Anzeigeliste)
// 
//    Rev 1.95   27 Apr 1998 12:52:24   Hannes
// Aktive - Forschleife im Hauptprogramm
// 
//    Rev 1.94   10 Feb 1998 18:26:54   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.93   30 Jan 1998 19:43:52   Hannes
// 
//    Rev 1.92   29 Jan 1998 11:06:24   Hannes
// Fuktionsaufrufe in DruckKopf - Zeilen: InListFunction () ohne ExtraDaten..
// 
//    Rev 1.91   16 Jan 1998 15:27:32   Hannes
// Listenfarben
// 
//    Rev 1.90   15 Jan 1998 21:31:18   Hannes
// Fehlerkorrektur Aufruf Funktionen in Listen
// 
//    Rev 1.89   12 Jan 1998 18:17:52   Hannes
// 
//    Rev 1.88   05 Jan 1998 07:54:00   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.87   01 Dec 1997 19:38:16   Hannes
// Diverse Anpassungen
// 
//    Rev 1.86   21 Nov 1997 10:39:00   Hannes
// Verbesserung des For - STatements
// 
//    Rev 1.85   19 Nov 1997 18:47:46   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.84   13 Nov 1997 12:40:50   Hannes
// diverse Fehlerkorrekturen
// 
//    Rev 1.83   10 Nov 1997 15:23:28   Hannes
// ForNextResult im dodowith / Resetzweig richtig gesetzt
// 
//    Rev 1.82   05 Nov 1997 16:41:48   Hannes
// PREFIX_VIRTCALL -> DelCommandFifo...
// 
//    Rev 1.81   29 Oct 1997 19:00:44   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.80   27 Oct 1997 19:50:20   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.79   24 Oct 1997 08:37:38   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.78   21 Oct 1997 11:44:26   Martin
// Result auch im Reset-Zweig neu initialisieren
// 
//    Rev 1.77   17 Sep 1997 09:21:40   Hannes
// PREFIX_STVIRTCALL ... Auch beim Update ausfuehren der Funktion
// 
//    Rev 1.76   28 Aug 1997 10:56:54   Hannes
// OnEmptyList -> FehlerKorrektur
// 
//    Rev 1.75   21 Aug 1997 15:02:14   Martin
// dummy auch bei ExCuteBlock
// 
//    Rev 1.74   05 Aug 1997 22:41:50   Hannes
// 
//    Rev 1.73   23 Jul 1997 18:35:38   Hannes
// 
//    Rev 1.72   22 Jul 1997 21:08:32   Hannes
// 
//    Rev 1.71   14 Jul 1997 19:23:24   Martin
// dummy fuer 32 BIT-optimizer
// 
//    Rev 1.70   11 Jul 1997 10:14:40   Hannes
// 
//    Rev 1.69   08 Jul 1997 11:59:06   Hannes
// 
//    Rev 1.68   18 Jun 1997 08:02:10   Hannes
// Fehlerkorrektur Aliasvergabe fuer Listen
// 
//    Rev 1.67   09 Jun 1997 13:10:54   Hannes
// 
//    Rev 1.66   27 May 1997 11:30:42   Hannes
// Zaehlerhandling in With - Anweisungen
// 
//    Rev 1.65   20 May 1997 08:50:02   Hannes
// With - Anweisung: keine PrepareListFunction
// 
//    Rev 1.64   12 May 1997 08:39:30   Hannes
// Angabe von fOffset auch bei Funktionen, die in einer Liste aufgerufen werden
// 
//    Rev 1.63   30 Apr 1997 10:24:16   Hannes
// 
//    Rev 1.62   30 Apr 1997 09:51:42   Hannes
// 
//    Rev 1.61   30 Apr 1997 09:29:40   Hannes
// 
//    Rev 1.60   22 Apr 1997 12:09:54   Hannes
// 
//    Rev 1.59   21 Apr 1997 20:46:16   Hannes
// SetRecHash,ClearRecHash
// 
//    Rev 1.58   21 Apr 1997 17:05:08   Hannes
// Funktionen in Listenprozeduren
// 
//    Rev 1.57   10 Apr 1997 11:44:44   Hannes
// Absicherung der Funktionen in Listen
// 
//    Rev 1.56   11 Mar 1997 13:28:50   Hannes
// statt MaxRecId == 0 BOOL first
// 
//    Rev 1.55   11 Mar 1997 09:17:52   Hannes
// 
//    Rev 1.54   28 Feb 1997 14:43:54   Hannes
// Fehlerkorrekturen bei Funktionshandling
// 
//    Rev 1.53   19 Feb 1997 12:23:18   Hannes
// Scriptfunktionen
// 
//    Rev 1.52   08 Jan 1997 16:03:22   HANNES
// 
//    Rev 1.51   12 Dec 1996 12:17:42   HANNES
// Call in einer Multiproc
// 
//    Rev 1.50   03 Dec 1996 16:40:18   HANNES
// BlockIsActive ...
// 
//    Rev 1.49   26 Nov 1996 08:14:12   HANNES
// Automatischer Update
// 
//    Rev 1.48   08 Nov 1996 13:33:22   HANNES
// 
//    Rev 1.47   31 Oct 1996 16:47:18   HANNES
// ClearConnection auf Parameter bei insert into ...
// 
//    Rev 1.46   30 Oct 1996 17:41:56   HANNES
// 
//    Rev 1.45   30 Oct 1996 08:43:16   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.44   28 Oct 1996 08:37:46   HANNES
// Structname vom Compiler
// 
//    Rev 1.43   21 Oct 1996 18:48:46   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.42   10 Jun 1996 10:09:12   GERHOLD
// pragma pack
// 
//    Rev 1.41   27 Mar 1996 18:05:18   MARTIN
// ParamBlock.AnzPars
// 
//    Rev 1.40   02 Feb 1996 10:34:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.38   25 Oct 1995 12:23:10   HANNES
// Aenderungen Hannes
// 
//    Rev 1.37   04 Oct 1995 16:03:18   MARTIN
// GetRecordWithListReverse
// 
//    Rev 1.36   25 Sep 1995 20:49:14   HANNES
// 
//    Rev 1.35   16 Sep 1995 22:33:48   HANNES
// 
//    Rev 1.34   14 Sep 1995 09:59:46   HANNES
// 
//    Rev 1.33   07 Sep 1995 09:03:08   HANNES
// NextBitmap
// 
//    Rev 1.32   30 Aug 1995 11:01:32   HANNES
// No change.
// 
//    Rev 1.31   24 Aug 1995 00:19:46   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.30   14 Aug 1995 16:47:08   HANNES
// Fehlerkorrektur im WithHandling
// 
//    Rev 1.29   14 Aug 1995 08:28:00   HANNES
// With - Handling optimiert
// 
//    Rev 1.28   10 Aug 1995 09:28:00   HANNES
// DoRemove ... Extradaten richtig gesetzt, damit der ClearConnection
// funktioniert
// 
//    Rev 1.27   14 Jul 1995 16:54:22   HANNES
// ResetCond ... Addresse raus
// 
//    Rev 1.26   11 Jul 1995 12:47:30   HANNES
// Expressionoptimierung
// 
//    Rev 1.25   04 Jul 1995 15:02:30   HANNES
// DoRemove ... Extradaten richtig gesetzt, damit der Clearconnection
// funktioniert
// 
//    Rev 1.24   02 Jul 1995 18:28:24   HANNES
// Nie endenwollende Fehlerkorrekturen
// 
//    Rev 1.23   11 Jun 1995 10:09:06   HANNES
// Extradaten in Updatecommand richtig behandelt (auch wenn extradata == NULL)
// 
//    Rev 1.22   09 Jun 1995 00:18:12   HANNES
// CSYSRECS
// Ruecksetzen des Datensatzes bei ExcuteWith
// Aufruf von DBList::Findrecord
// 
//    Rev 1.21   29 May 1995 12:45:42   HANNES
// PushOffset fuer Listenfunktionen
// 
//    Rev 1.20   15 May 1995 08:27:20   HANNES
// Spiecherfreigabe beim With - Statement
// 
//    Rev 1.19   08 May 1995 17:13:50   HANNES
// Fehler bei Removerecord
// 
//    Rev 1.18   27 Apr 1995 15:37:26   HANNES
// 
//    Rev 1.17   12 Apr 1995 12:26:12   HANNES
// 
//    Rev 1.16   04 Apr 1995 12:10:02   HANNES
//  
// 
//    Rev 1.15   31 Mar 1995 13:09:20   HANNES
//  
// 
//    Rev 1.14   27 Mar 1995 13:16:48   HANNES
//  
// 
//    Rev 1.13   22 Mar 1995 11:46:34   HANNES
// 
//    Rev 1.12   21 Mar 1995 16:20:48   HANNES
// 
//    Rev 1.11   21 Mar 1995 16:08:12   GERHOLD
// 
//    Rev 1.10   20 Mar 1995 12:06:34   HANNES
// Konstantenhanling, RunNmbr, Schleifen...
// 
//    Rev 1.9   08 Mar 1995 09:14:46   HANNES
// Forschleifen u.a.
// 
//    Rev 1.8   24 Feb 1995 11:17:14   HANNES
//  
// 
//    Rev 1.7   13 Jan 1995 16:55:54   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.6   09 Jan 1995 12:14:32   HANNES
// Debugger eingebaut
// 
//    Rev 1.5   05 Dec 1994 17:42:40   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.4   08 Nov 1994 12:43:34   HANNES
// Script abbrechen
// 
//    Rev 1.3   07 Nov 1994 11:09:40   HANNES
// Loeschen von alten Kommandos in MultiProc
// 
//    Rev 1.2   05 Aug 1994 17:13:26   HANNES
// ExCuteBlock auch fuer EM_UPDATE zugelassen
// 
//    Rev 1.1   13 Jul 1994 21:14:20   HANNES
// Mehrfachausfuehrung einer Prozedur ermoeglichen
// 
//    Rev 1.0   24 Jun 1994 17:05:10   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.13   04 Feb 1994 16:45:18   HANNES
// Dynamisches Linken
// 
//    Rev 1.12   05 Sep 1993 22:17:48   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.11   18 Aug 1993 10:32:26   HANNES
// Zaehler - Logik verbessert
// 
//    Rev 1.10   05 Aug 1993 13:09:08   HANNES
// Eintragen / Rausloeschen des Counters: nur bei EM_RESET..
// 
//    Rev 1.9   22 Jul 1993 20:54:02   HANNES
// Kommandosortierung
// 
//    Rev 1.8   05 Jul 1993 14:47:18   HANNES
// Kommandofifo
// 
//    Rev 1.7   16 Jun 1993 16:52:26   MARTIN
// Sanduhr
// 
//    Rev 1.6   02 Apr 1993 17:36:48   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.5   17 Mar 1993 17:58:52   HANNES
// 32 bit Umstellung Compiler
// 
//    Rev 1.4   02 Mar 1993 22:30:02   HANNES
// ???
// 
//    Rev 1.3   22 Feb 1993 17:09:04   HANNES
// Erweiterung der Kommados auf groesser prog Datensaetze
// 
//    Rev 1.2   08 Feb 1993 10:39:40   HANNES
// Einbau des CallCommand Fifos
// 
//    Rev 1.1   18 Jan 1993 16:46:42   HANNES
// Aenderungen des Handlings von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.0   02 Dec 1992 15:39:28   HANNES
// Initial revision.
//

//
//      Format der Anweisungen
//
//      1. Wort: Laenge der Gesamtanweisungen
//      2. Wort: Beginn des Hauptprogrammes
//          ... Prozeduren
//          ... Hauptprogramm
//      Die Prozeduren und das Hauptprogramm beginnen immer
//      mit der Laenge des auszufuehrenden Blockes
//      Dahinter steht eine Funktionsnummer oder ein Prefix
//      fuer eine Sondersequenz (if, else, call, not ...)
//      Hinter if beginnt eine condition
//      Conditions sind aufgebaut durch die Verknuepfungsart (wenn
//      vorhanden) + rel. Offset des zu verknuepfenden Termes
//      Hinter der Kondition beginnt ein neuer Block
//      Hinter diesem Block kommt eine Funktion oder ein else Block
//      Die Strukturen sind so aufgebaut, dass sich Rekursion zur
//      Ausfuehrung fast schon zwingend anbietet
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "hash.hpp"
#include "dynalink.hpp"

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
#include "multipro.hpp"
#include "for.hpp"
#include "compile.hpp"

#define DDSFUNC_MAIN
#include "fncarr.hpp"
#define MODULENUM 31
#include "winass.hpp"
#include "communic.hpp"
#define HUGE _huge
typedef char HUGE * HPSTR;

#include "scdb.hpp"

void SetCounter (LPCTRLIST h,LPCMDCOUNT x)
  {
  if (h->c == NULL)
    h->c = x->Copy ();
  else
    DBWIN_ASSERT (h->c->counter[-1] == x->counter[-1]);
  }

void RemoveCount (LPCTRLIST h)
  {
  if (h->c == NULL) return ;
  FreeGlobMem (h->c);
  h->c = NULL;
  }

LPCMDCOUNT GetCounter (LPCTRLIST h)
  {
  DBWIN_ASSERT(h->c != NULL);
  return h->c;
  }

// Stackverwaltung fuer Offset's der Conditions
static LPVOID CondOff[MAX_DEPTH];
static WORD CondPtr = 0;
void PushOffset (LPVOID Cmd)
  {
  CondOff[CondPtr++] = Cmd;
  }

void PopOffset ()
  {
  CondPtr --;
  }

LPVOID GetLastOffset (void)
  {
  return CondOff[CondPtr-1];
  }

static void WriteCondRes (WORD FAR *buffer,BOOL res)
  {
  *buffer = WORD(res);
  }

static BOOL GetCondRes (WORD buffer)
  {
  return BOOL (buffer);
  }

BOOL DoIn (mdiChild *c,LPVOID par,WORD mode);
// Untersuchen einer Condition
BOOL mdiChild::CheckCond (LPSTR cnd,DWORD *Len,WORD mode)
  {
  HPSTR h = HPSTR (cnd);
  WORD command = *(WORD FAR *) h ;
  DWORD l1,l2;
  DWORD noplen = 0;
  BOOL res,res1,res2;
  if (command == PREFIX_NOP) {
    h += (noplen = DWORD(*((WORD FAR *) (h + sizeof(WORD))) + sizeof(WORD)));
    command = *(WORD FAR *) h ;
    }
  if ((command >= FIRSTFUNCID) || (command == PREFIX_IN)) {
#ifdef DEBUG
    BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
    PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
    if (command >= FIRSTFUNCID) {
      LPCMDCOUNT old = _ccount->Copy ();
      res = (* ddsfunc [command - FIRSTFUNCID]) (this,LPVOID (h + sizeof (WORD)),mode);
      SetCount (old);
      FreeGlobMem (old);
      }
    else
      res = DoIn (this,LPVOID (h + sizeof (WORD)),mode);
#ifdef DEBUG
    PopFromCallStack ();
#endif

    l1 = sizeof (WORD) + * ((WORD FAR *) h + 1) ; // Laenge des Fkt. Aufrufes
    l2 = 0 ;
    }
  else if (command == PREFIX_NOT) {
    res = !CheckCond (LPSTR (h + sizeof (WORD)),&l1,mode);
    l2 = sizeof (WORD);
    }
  else if ((command == PREFIX_AND) || (command == PREFIX_OR)) {
    res1 = CheckCond (LPSTR (h + sizeof (WORD) + sizeof(DWORD)),&l1,mode);
    res2 = CheckCond (LPSTR (h + * ((DWORD FAR *) (h + sizeof(WORD))) + sizeof (WORD)),
                &l2,mode);
    l1 += sizeof (WORD) + sizeof(DWORD);    // rek. ermittelte Laenge + 2 WORD Prefix
    if (command == PREFIX_AND)
      res = res1 && res2 ;
    else
      res = res1 || res2 ;
    }
  *Len = l1 + l2 + noplen;
  return res ;
  }

HPSTR DoFor (mdiChild *c,HPSTR h,WORD mode);
HPSTR DoForAll (mdiChild *c,char huge *h,WORD mode);
HPSTR DoDoWith (mdiChild *c,char huge *h,WORD mode);
DWORD FAR *LastFunctionCall_par;
int LastFunctionCall_AnzPars;
mdiChild FAR *LastFunctionChild;
LPVOID FAR *LastFunctionCall_Vals;
void SetLastFunctionData (LPVOID FAR *vals,int ap,mdiChild *c)
  {
  LastFunctionCall_Vals = vals;
  LastFunctionCall_AnzPars = ap ;
  LastFunctionChild = c;
  }
FuncStart FAR *GetFuncStart (MultiProc FAR *mp)
  {
  char FAR *h = mp->TailProc ();
  h += 2 * sizeof(DWORD);
  WORD command = *(WORD FAR *) h;
  if (command == PREFIX_NOP)
    h += (DWORD(*((WORD FAR *) (h + sizeof(WORD))) + sizeof(WORD)));
  return (FuncStart FAR *) h;
  }

extern BOOL DontCheckCallDone;
char huge *mdiChild::DoFunctionCall (char huge *h,WORD mode)
  {
  DWORD FAR *old_LastFunctionCall_par    = LastFunctionCall_par;
  int old_LastFunctionCall_AnzPars       = LastFunctionCall_AnzPars;
  mdiChild FAR *old_LastFunctionChild    = LastFunctionChild;
  LPVOID FAR *old_LastFunctionCall_Vals  = LastFunctionCall_Vals;

#ifdef DEBUG
  BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
  PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
  FunctionCall FAR *fc = (FunctionCall FAR *) (h + sizeof(WORD));
  LastFunctionCall_par = fc->par;
  LastFunctionCall_AnzPars = fc->AnzPars();
  LastFunctionChild = this;
  if ((DontCheckCallDone) && (mode & EM_LOAD) && (fc->mp != NULL))
    mode = EM_UPDATE ;
  if (mode & EM_LOAD) {
    LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
    LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);
    // Es muss eine Multiproc angelegt werden
    //---------------------------------------------
    fc->mp = new MultiProc (this,fc->procAddr);
    if ((IsInListFunction ()) && (_ExtraData != NULL)) {
      SetExtraInfo extra(this,_ExtraData->i.keyData,fc->mp->CorrOffs());
      extra.ci->fOffs = extra.ci->cOffs;
      fc->mp->AddProcAtTail(0);
      fc->mp->ExCuteLast (mode,&extra);
      }
    else {
      SetExtraInfo extra(this,fc->mp->CorrOffs(),fc->mp->CorrOffs());
      fc->mp->AddProcAtTail(0);
      fc->mp->ExCuteLast (mode,&extra);
      }
    // Da vermutlich neue Records angelegt wurden, muessen die alten
    // jetzt wieder restauriert werden
    //---------------------------------------------------------------
    rr->SetRecord (DYNLOCALDATA,r1old);
    rr->SetRecord (STATICLOCALDATA,r2old);
    }
  else if (mode & (EM_RESET | EM_CLEAR)) {
    // Abbau der Multiproc
    LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
    LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);
    if ((IsInListFunction ()) && (_ExtraData != NULL)) {
      SetExtraInfo extra(this,_ExtraData->i.keyData,fc->mp->CorrOffs());
      extra.ci->fOffs = extra.ci->cOffs;
      fc->mp->ExCuteLast (mode,&extra);
      fc->mp->RemoveLast ();
      }
    else {
      SetExtraInfo extra(this,fc->mp->CorrOffs(),fc->mp->CorrOffs());
      fc->mp->ExCuteLast (mode,&extra);
      fc->mp->RemoveLast ();
      }
    delete fc->mp ;
    fc->mp = NULL ;
    // Die Nextsameverbindungen loesen
    LPDBRECORD r1 = rr->GetRecord (DYNLOCALDATA);
    for (int i = 0 ; i < fc->AnzPars() ; i++) {
      LPVARELEM v = r1->GetVarElem (i);
      if (v->NextSame != NULL) {
        for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
        p->NextSame = v->NextSame ;
        if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
        v->NextSame = NULL;
        }
      }
    // Die Records, die von FUNCSTART erzeugt wurden, wieder loeschen
    if (r1 != NULL) { delete r1 ; rr->SetRecord (DYNLOCALDATA,NULL); }
    LPDBRECORD r2 = rr->GetRecord (STATICLOCALDATA);
    if (r2 != NULL) { delete r2 ; rr->SetRecord (STATICLOCALDATA,NULL); }
    rr->SetRecord (DYNLOCALDATA,r1old);
    rr->SetRecord (STATICLOCALDATA,r2old);
    }
  else if (mode & EM_UPDATE) {
    // Nur moeglich, wenn man sich innerhalb eines Listenprozedur befindet
    FuncStart FAR *fs = GetFuncStart (fc->mp);
    LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
    LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);

    rr->SetRecord (DYNLOCALDATA,LPDBRECORD(fs->rec1));
    rr->SetRecord (STATICLOCALDATA,LPDBRECORD(fs->rec2));

    SetExtraInfo extra(this,_ExtraData->i.keyData,fc->mp->CorrOffs());
    extra.ci->fOffs = extra.ci->cOffs;
    fc->mp->ExCuteLast (mode,&extra);

    rr->SetRecord (DYNLOCALDATA,r1old);
    rr->SetRecord (STATICLOCALDATA,r2old);
    }
#ifdef DEBUG
  PopFromCallStack ();
#endif
  h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;
  LastFunctionCall_par    = old_LastFunctionCall_par;
  LastFunctionCall_AnzPars       = old_LastFunctionCall_AnzPars;
  LastFunctionChild    = old_LastFunctionChild;
  LastFunctionCall_Vals  = old_LastFunctionCall_Vals;

  return h;
  }

#ifdef UEBERLEGT
char huge *mdiChild::DoExpFunctionCall (char huge *h,WORD mode)
  {
#ifdef DEBUG
  BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
  PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
  ExpFunctionCall FAR *fc = (ExpFunctionCall FAR *) (h + sizeof(WORD));
  LastFunctionCall_par = fc->par();
  LastFunctionCall_AnzPars = fc->AnzPars();
  LastFunctionChild = this;
  if (mode & EM_LOAD) {
    LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
    LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);
    // Es muss eine Multiproc angelegt werden
    //---------------------------------------------
    LPSCRIPTCONTENT scent = GetScriptEntry (fc->Name);
    DBWIN_ASSERT (scent != NULL);
    fc->ec = new ExpChild (scent);
    fc->ec->ExtDocID = DWORD(this);
    fc->ec->erzContext = GetErzContext();

    fc->ec->_ccount_base = PushBlock (_ccount->Copy());
    fc->ec->outContext = (outContext) ? outContext : this ;
    LPWORD sourceind = fc->Ind();
    WORD restype;
    DWORD procAddr = GetFunctionsAddress (fc->FName(),scent->ExportDef,&fc->destind,&restype);
    DBWIN_ASSERT ((fc->destind != NULL) && (fc->destind[0] == fc->Ind()[-1]));
    fc->ec->SetContextRecords (this,fc->destind[0],fc->destind + 1,fc->Ind());
    DBWIN_ASSERT (procAddr != 0L);
    fc->mp = new MultiProc (fc->ec,procAddr);
    SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
    fc->mp->AddProcAtTail(0);
    fc->ec->ResetCount ();
    fc->mp->ExCuteLast (mode,&extra);
    // Da vermutlich neue Records angelegt wurden, muessen die alten
    // jetzt wieder restauriert werden
    //---------------------------------------------------------------
    rr->SetRecord (DYNLOCALDATA,r1old);
    rr->SetRecord (STATICLOCALDATA,r2old);
    }
  else if (mode & (EM_RESET | EM_CLEAR)) {
    // Abbau der Multiproc
    LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
    LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);
    SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
    fc->ec->ResetCount ();
    fc->mp->ExCuteLast (mode,&extra);
    fc->mp->RemoveLast ();
    delete fc->mp ;
    fc->mp = NULL ;
    // Die Nextsameverbindungen loesen
    LPDBRECORD r1 = fc->ec->rr->GetRecord (DYNLOCALDATA);
    for (int i = 0 ; i < fc->AnzPars() ; i++) {
      LPVARELEM v = r1->GetVarElem (i);
      if (v->NextSame != NULL) {
        for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
        p->NextSame = v->NextSame ;
        if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
        v->NextSame = NULL;
        }
      }
    // Die Records, die von FUNCSTART erzeugt wurden, wieder loeschen
    if (r1 != NULL) { delete r1 ; rr->SetRecord (DYNLOCALDATA,NULL); }
    LPDBRECORD r2 = rr->GetRecord (STATICLOCALDATA);
    if (r2 != NULL) { delete r2 ; rr->SetRecord (STATICLOCALDATA,NULL); }
    rr->SetRecord (DYNLOCALDATA,r1old);
    rr->SetRecord (STATICLOCALDATA,r2old);
    fc->ec->DelContextRecords (fc->destind[0],fc->destind + 1);
    delete fc->ec ;
    fc->ec = NULL ;
    fc->destind = NULL ;
    }
#ifdef DEBUG
  PopFromCallStack ();
#endif
  h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;
  return h;
  }
#endif

struct FuncInfo {
  DWORD procAddr;
  LPSCRIPTCONTENT sc;
  LPWORD destInd;
  };
DWORD VirtFunctionsAddress (LPSTR FunctionName,LPSTR ModName,LPSCRIPTCONTENT FAR *lpsc,LPWORD FAR *destind,BOOL checkOwn,WORD FAR *restyp)
  {
  hash FAR *FuncHash = GetFuncHash ();
  char cmbName[256];
  lstrcpy (cmbName,ModName);
  if (checkOwn)
    lstrcat (cmbName,"%");
  else
    lstrcat (cmbName,"@");
  lstrcat (cmbName,FunctionName);
  FuncInfo FAR *fin = (FuncInfo FAR *) FuncHash->GetData (cmbName);
  if (fin != NULL) {
    *lpsc    = fin->sc ;
    *destind = fin->destInd;
    return fin->procAddr;
    }
  DWORD procAddr;
  LPSCRIPTCONTENT sc = GetScriptEntry (ModName);
  DBWIN_ASSERT_TEXT (sc != NULL,ModName);
  if (checkOwn)
    procAddr = GetFunctionsAddress (FunctionName,sc->ExportDef,destind,restyp);
  else
    procAddr = 0L;
  if (procAddr == 0L) {
    LPSTR h = sc->BaseModules ;
    if (h != NULL) {
      for ( LPSTR x = h ; *x ; x += lstrlen (x) + 1 ) {
        if ((procAddr = VirtFunctionsAddress (FunctionName,x,lpsc,destind,TRUE,restyp)) != 0L)
          break ;
        }
      }
    if (procAddr == 0L) {
      LPSTR h = sc->VirtualModules ;
      if (h != NULL) {
        for ( LPSTR x = h ; *x ; x += lstrlen (x) + 1 ) {
          if ((procAddr = VirtFunctionsAddress (FunctionName,x,lpsc,destind,TRUE,restyp)) != 0L)
            break ;
          }
        }
      }
    }
  else {
    *lpsc = sc ;
    }
  FuncInfo fi ;
  fi.procAddr = procAddr ;
  fi.sc = *lpsc ;
  fi.destInd = *destind;
  FuncHash->SetData(cmbName,&fi,sizeof(fi));
  return procAddr;
  }

void ResetParamBinding (VirtFunctionCall FAR *fc)
  {
  // Die Nextsameverbindungen loesen
  LPDBRECORD r1 = fc->ec->rr->GetRecord (DYNLOCALDATA);
  for (int i = 0 ; i < fc->AnzPars() ; i++) {
    LPVARELEM v = r1->GetVarElem (i);
    if (v->NextSame != NULL) {
      for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
      p->NextSame = v->NextSame ;
      if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
      v->NextSame = NULL;
      }
    }
  }

void mdiChild::UpdateVirtFunction (VirtFunctionCall FAR *fc,SetExtraInfo FAR *extra,WORD FAR *olddestind)
  {
  fc->ec->ResetCount ();
  fc->mp->ExCuteLast (EM_CLEAR | EM_RESET,extra);
  fc->mp->RemoveLast ();
  delete fc->mp ;
  fc->mp = NULL ;
  // Die Nextsameverbindungen loesen
  ResetParamBinding (fc);
  // Die Records, die von FUNCSTART erzeugt wurden, wieder loeschen
  LPDBRECORD r1 = fc->ec->rr->GetRecord (DYNLOCALDATA);
  if (r1 != NULL) delete r1 ;
  LPDBRECORD r2 = fc->ec->rr->GetRecord (STATICLOCALDATA);
  if (r2 != NULL) delete r2 ;
  fc->ec->DelContextRecords (olddestind[0],olddestind + 1);
  delete fc->ec ;
  fc->ec = NULL ;
  }

char huge *mdiChild::DoVirtFunctionCall (char huge *h,WORD mode)
  {
#ifdef DEBUG
  BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
  PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
  VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (h + sizeof(WORD));
  DWORD mref = fc->par()[-1];
  DWORD FAR *old_LastFunctionCall_par    = LastFunctionCall_par;
  int old_LastFunctionCall_AnzPars       = LastFunctionCall_AnzPars;
  mdiChild FAR *old_LastFunctionChild    = LastFunctionChild;
  LPVOID FAR *old_LastFunctionCall_Vals  = LastFunctionCall_Vals;
  if ((DontCheckCallDone) && (fc->ec != NULL) && (mode & EM_LOAD))
    mode = EM_UPDATE ;
  if ((mode & EM_LOAD) || ((mode & EM_UPDATE) && (fc->ec == NULL))) {
    // Es muss eine Multiproc angelegt werden
    //---------------------------------------------
    LPSTR ModName = LPSTR (ReadlData (mref));

    LastFunctionCall_par = fc->par();
    LastFunctionCall_AnzPars = fc->AnzPars();
    LastFunctionChild = this;
    DBWIN_ASSERT (ModName != NULL);
    if (mode & EM_FIXCONNECTION)
      SetlConnection (mref,h);
    LPSCRIPTCONTENT scent = NULL;
    BOOL checkOwn;
    WORD restype;
    if (lstrcmp (ModName,"_Parent") == 0) {
      ModName = schd->fName ;
      checkOwn = FALSE ;
      }
    else
      checkOwn = TRUE ;
    DWORD procAddr = VirtFunctionsAddress (fc->FName,ModName,&scent,&fc->destind,checkOwn,&restype);
    char rstring[512];
    sprintf (rstring,"mod: <%s>, func: <%s>",ModName,fc->FName);
    DBWIN_ASSERT_TEXT (procAddr != 0L,rstring);
    fc->ec = new ExpChild (scent);
    fc->ec->erzContext = GetErzContext();
    fc->ec->_ccount_base = PushBlock (_ccount->Copy());
    fc->ec->outContext = (outContext) ? outContext : this ;
    fc->ec->SetContextRecords (this,fc->destind[0],fc->destind + 1,fc->Ind());
    fc->mp = new MultiProc (fc->ec,procAddr);
    if ((IsInListFunction ()) && (_ExtraData != NULL)) {
      fc->ec->ConnectionAddress = ConnectionAddress ; 
      fc->ec->ConnectionOwnerID = ConnectionOwnerID ;
      fc->ec->dontUpdateDocument = TRUE ;
      fc->ec->InListFunction = TRUE ;
      SetExtraInfo extra(fc->ec,_ExtraData->i.keyData,fc->mp->CorrOffs());
      extra.ci->fOffs = extra.ci->cOffs;
      fc->mp->AddProcAtTail(0);
      fc->ec->ResetCount ();
      WORD mymode;
      if (mode == EM_UPDATE) mymode = EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION;
      else                   mymode = mode;
      fc->mp->ExCuteLast (mymode,&extra);
      }
    else {
      SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
      fc->mp->AddProcAtTail(0);
      fc->ec->ResetCount ();
      fc->mp->ExCuteLast (mode,&extra);
      }
    }
  else if (mode & EM_UPDATE) {
    // Das Modul hat einen Update gekriegt
    LastFunctionCall_par = fc->par();
    LastFunctionCall_AnzPars = fc->AnzPars();
    LastFunctionChild = this;

    LPSTR ModName = LPSTR (ReadlData (mref));
    if (mode & EM_FIXCONNECTION)
      SetlConnection (mref,h);
    LPSCRIPTCONTENT scent = NULL;
    LPWORD olddestind = fc->destind;
    WORD restype;
    DWORD procAddr = VirtFunctionsAddress (fc->FName,ModName,&scent,&fc->destind,TRUE,&restype);
    DBWIN_ASSERT (procAddr != 0L);
    if (lstrcmp (scent->fName,fc->ec->schd->fName) != 0) {
      if ((IsInListFunction ()) && (_ExtraData != NULL)) {
        fc->ec->ConnectionAddress = ConnectionAddress ; 
        fc->ec->ConnectionOwnerID = ConnectionOwnerID ;
        fc->ec->dontUpdateDocument = TRUE ;
        fc->ec->InListFunction = TRUE ;
        SetExtraInfo extra(fc->ec,_ExtraData->i.keyData,fc->mp->CorrOffs());
        extra.ci->fOffs = extra.ci->cOffs;
        UpdateVirtFunction (fc,&extra,olddestind);
        }
      else {
        SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
        UpdateVirtFunction (fc,&extra,olddestind);
        }

      // Und wieder Aufbauen
      fc->ec = new ExpChild (scent);
      fc->ec->erzContext = GetErzContext();
      fc->ec->_ccount_base = PushBlock (_ccount->Copy());
      fc->ec->outContext = (outContext) ? outContext : this ;
      fc->ec->SetContextRecords (this,fc->destind[0],fc->destind + 1,fc->Ind());
      fc->mp = new MultiProc (fc->ec,procAddr);
      if ((IsInListFunction ()) && (_ExtraData != NULL)) {
        fc->ec->ConnectionAddress = ConnectionAddress ; 
        fc->ec->ConnectionOwnerID = ConnectionOwnerID ;
        fc->ec->dontUpdateDocument = TRUE ;
        fc->ec->InListFunction = TRUE ;
        SetExtraInfo extra(fc->ec,_ExtraData->i.keyData,fc->mp->CorrOffs());
        extra.ci->fOffs = extra.ci->cOffs;
        fc->mp->AddProcAtTail(0);
        fc->ec->ResetCount ();
        fc->mp->ExCuteLast (EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,&extra);
        }
      else {
        SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
        fc->mp->AddProcAtTail(0);
        fc->ec->ResetCount ();
        fc->mp->ExCuteLast (EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,&extra);
        }   // 2. Destruktor von SetExtraInfo
      }
    else {
      if ((IsInListFunction ()) && (_ExtraData != NULL)) {
        FuncStart FAR *fs = GetFuncStart (fc->mp);
        LPDBRECORD r1old = rr->GetRecord (DYNLOCALDATA);
        LPDBRECORD r2old = rr->GetRecord (STATICLOCALDATA);

        rr->SetRecord (DYNLOCALDATA,LPDBRECORD(fs->rec1));
        rr->SetRecord (STATICLOCALDATA,LPDBRECORD(fs->rec2));

        SetExtraInfo extra(fc->ec,_ExtraData->i.keyData,fc->mp->CorrOffs());
        extra.ci->fOffs = extra.ci->cOffs;
        fc->mp->ExCuteLast (mode,&extra);

        rr->SetRecord (DYNLOCALDATA,r1old);
        rr->SetRecord (STATICLOCALDATA,r2old);
        }
      }
    }
  else if (mode & (EM_RESET | EM_CLEAR)) {
    // Abbau der Multiproc
    fc->ec->CallScriptDestruktor ();
    LastFunctionCall_par = fc->par();
    LastFunctionCall_AnzPars = fc->AnzPars();
    LastFunctionChild = this;

    ClearlConnection (mref,h);
    if ((IsInListFunction ()) && (_ExtraData != NULL)) {
      fc->ec->ConnectionAddress = ConnectionAddress ; 
      fc->ec->ConnectionOwnerID = ConnectionOwnerID ;
      fc->ec->dontUpdateDocument = TRUE ;
      fc->ec->InListFunction = TRUE ;
      SetExtraInfo extra(fc->ec,_ExtraData->i.keyData,fc->mp->CorrOffs());
      extra.ci->fOffs = extra.ci->cOffs;
      fc->ec->ResetCount ();
      fc->mp->ExCuteLast (mode,&extra);
      fc->mp->RemoveLast ();
      delete fc->mp ;
      fc->mp = NULL ;
      }
    else {
      SetExtraInfo extra(fc->ec,fc->mp->CorrOffs(),fc->mp->CorrOffs());
      fc->ec->ResetCount ();
      fc->mp->ExCuteLast (mode,&extra);
      fc->mp->RemoveLast ();
      delete fc->mp ;
      fc->mp = NULL ;
      }
    // Die Nextsameverbindungen loesen
    LPDBRECORD r1 = fc->ec->rr->GetRecord (DYNLOCALDATA);
    for (int i = 0 ; i < fc->AnzPars() ; i++) {
      LPVARELEM v = r1->GetVarElem (i);
      if (v->NextSame != NULL) {
        for (LPVARELEM p = v->NextSame ; p->NextSame != v ; p = p->NextSame ) ;
        p->NextSame = v->NextSame ;
        if (p->NextSame == p) p->NextSame = NULL ;  // der ist jetzt alleine
        v->NextSame = NULL;
        }
      }
    // Die Records, die von FUNCSTART erzeugt wurden, wieder loeschen
    if (r1 != NULL) delete r1 ;
    LPDBRECORD r2 = fc->ec->rr->GetRecord (STATICLOCALDATA);
    if (r2 != NULL) delete r2 ;
    fc->ec->DelContextRecords (fc->destind[0],fc->destind + 1);
    delete fc->ec ;
    fc->ec = NULL ;
    fc->destind = NULL ;
    }
#ifdef DEBUG
  PopFromCallStack ();
#endif
  h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;
  LastFunctionCall_par    = old_LastFunctionCall_par;
  LastFunctionCall_AnzPars       = old_LastFunctionCall_AnzPars;
  LastFunctionChild    = old_LastFunctionChild;
  LastFunctionCall_Vals  = old_LastFunctionCall_Vals;

  return h;
  }

#ifdef WIN32
#ifndef DEBUG
static mdiChild **dummyptr;
#endif
#endif

BOOL mdiChild::ExCuteBlock (LPSTR base,DWORD Offset,WORD mode)
  {
#ifdef WIN32
#ifndef DEBUG
  mdiChild *dummy = this;
  dummyptr = &dummy;
#endif
#endif

#ifdef DEBUG
  MSG msg;
  while (PeekMessage (&msg,WBase::hFrameWin,WMC_BASE,WMC_BASE + WMC_MAX,PM_REMOVE)) {
    CheckMsg (&msg);
    }
#endif
  ActiveBlock startBlock;
  // Base + Offset zeigt auf die Laenge des Blockes, der auszufuehren ist
  HPSTR h;
  
  LPSTR end = LPSTR (HPSTR(base) + 
                        *(DWORD FAR *) (HPSTR (base) + Offset) + 
                          Offset
                    );
  for (h = HPSTR (base) + Offset + sizeof (DWORD) ; h < end ; ) {
    WORD command = *(WORD FAR *) h;
    if (command >= FIRSTFUNCID) {
      // Funktion gefunden -> Ausfuehren
#ifdef DEBUG
      BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
      PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
      (* ddsfunc [command - FIRSTFUNCID]) (this,LPSTR(h) + sizeof (WORD),mode);
#ifdef DEBUG
      PopFromCallStack ();
#endif
      if (mode & EM_FIXCONNECTION)
        _ccount->Increment();

      if (mode & (EM_CHANGETOFALSE | EM_RESET | EM_CLEAR)) {
        GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID(),LPSTR(h)); 
        }

      // Zeiger weiterschalten
      h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;      
                        // Laenge der Parameter stehen hinter
                        // dem Funktionsidentifier
      }
    else {
      switch (command) {
        case PREFIX_NOP :
          h += DWORD (*((WORD FAR *) (h + sizeof(WORD))) + sizeof(WORD));
          break ;
        case PREFIX_CALL :
          // Erwaehnte Rekursion, Achtung:
          // Dieser Call kann raus aus dem aktuellen Block
          // fuehren ...
#ifdef DEBUG
          BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
          PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
          if (mode & EM_LOAD) {
            if (_ExtraData != NULL) {
              // Es muss eine Multiproc angelegt werden
              //---------------------------------------------
              MultiProc FAR *mp = new MultiProc (this,*((DWORD FAR *) (h + sizeof(WORD) + sizeof(LPVOID))));
              SetExtraInfo extra(this,mp->CorrOffs());
              mp->AddProcAtTail(0);
              mp->ExCuteLast (mode,&extra);
              *((MultiProc FAR * FAR *) (h + sizeof(WORD))) = mp;
              }
            else {
              // Ein Call ohne Multiproc
              RestoreListFnc rlf(this);
              if (!ExCuteBlock (*((DWORD FAR *) (h + sizeof(WORD) + sizeof(LPVOID)))+sizeof(DWORD),mode)) return FALSE ;
              }
            }
          else if (mode & (EM_RESET | EM_CLEAR)) {
            MultiProc FAR *mp = *((MultiProc FAR * FAR *) (h + sizeof(WORD)));
            if (mp != NULL) {
              // Abbau der Multiproc
              SetExtraInfo extra(this,mp->CorrOffs());
              mp->ExCuteLast (mode,&extra);
              mp->RemoveLast ();
              delete mp ;
              *((MultiProc FAR * FAR *) (h + sizeof(WORD))) = NULL;
              }
            else {
              // Normaler Abbau
              RestoreListFnc rlf(this);
              if (!ExCuteBlock (*((DWORD FAR *) (h + sizeof(WORD) + sizeof(LPVOID)))+sizeof(DWORD),mode)) return FALSE ; // Fehler
              }
            }
#ifdef DEBUG
          PopFromCallStack ();
#endif
          h += sizeof (WORD) + sizeof(DWORD) + sizeof(LPVOID);
          break ;
        case PREFIX_STATICCALL :
          if (mode & (EM_LOAD | EM_UPDATE)) {
#ifdef DEBUG
            BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
            PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
            RestoreListFnc rlf(this);
            BOOL res = ExCuteBlock (*((DWORD FAR *) (h + sizeof(WORD)))+sizeof(DWORD),EM_LOAD | EM_CHANGETOTRUE) ;
            ExCuteBlock (*((DWORD FAR *) (h + sizeof(WORD)))+sizeof(DWORD),EM_RESET) ;
#ifdef DEBUG
            PopFromCallStack ();
#endif
            if (!res) return FALSE ;
            }
          h += sizeof (WORD) + sizeof(DWORD);
          break ;
        case PREFIX_IF :
          {
          DWORD CondLen;

          PushOffset (GetConnectionAddress(h));
          BOOL res = CheckCond (h + 2 * sizeof (WORD) + sizeof(LPCTRLIST),&CondLen,mode) ;
          if (mode & (EM_CHANGETOFALSE | EM_RESET | EM_CLEAR)) {
            // Nur normale Befehle rausloeschen, der Rest koennte zuviel
            // fuer ihn werden....
            GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID(),GetLastOffset());
            }

          PopOffset ();

          if (mode & EM_FIXCONNECTION) {
            SetCounter ((LPCTRLIST) (h + 2 * sizeof(WORD)),_ccount);
            _ccount->Increment();
            _ccount = PushBlock(_ccount);
            }
          if (mode & (EM_RESET | EM_CLEAR)) {
            RemoveCount ((LPCTRLIST) (h + 2 * sizeof(WORD)));
            }

          BOOL oldRes ;
          if ((mode & EM_LOAD) == 0)
            oldRes = GetCondRes (*(((WORD FAR *) h) + 1));
          else
            oldRes = FALSE ;
          if (mode & (EM_LOAD | EM_UPDATE)) {
            WriteCondRes (((WORD FAR *) h) + 1,res);
            }
          if (mode & (EM_RESET | EM_CLEAR)) {
            // Abhaengig vom alten resultat wird der entsprechende zweig
            // aufgerufen
            // Abhaengig vom Resultat wird der alte Zweig aufgerufen
            h += sizeof (WORD) + sizeof(WORD) + sizeof(LPCTRLIST) + CondLen;
            if (oldRes) {
              if (!ExCuteBlock (h,0L,mode)) return FALSE ;
              }
            h += *(DWORD FAR *) h ;
            if (h < end) {
              command = * (WORD FAR *) h ;
              if (command == PREFIX_ELSE) {
                h += sizeof (WORD);
                if (!oldRes) {
                  if (!ExCuteBlock (h,0L,mode)) return FALSE ;
                  }
                h += *(DWORD FAR *) h ;
                }
              }
            }
          else if (mode & EM_UPDATE) {
            LPCMDCOUNT old = _ccount->Copy ();
            SetCount (GetCounter ((LPCTRLIST) (h + 2 * sizeof(WORD))));
            h += 2 * sizeof (WORD) + sizeof(LPCTRLIST) + CondLen ;
            _ccount = PushBlock (_ccount);
            if (res != oldRes) {
              if (res) {
                ExCuteelse (h,EM_CLEAR | EM_CHANGETOFALSE);
                ExCuteif (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
                }
              else {
                ExCuteif (h,EM_CLEAR | EM_CHANGETOFALSE);
                ExCuteelse (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
                }
              }
            else {
              if (res)
                ExCuteif (h,EM_UPDATE);
              else
                ExCuteelse (h,EM_UPDATE);
              }
            h += *(DWORD FAR *) h ;
            if (h < end) {
              command = * (WORD FAR *) h ;
              if (command == PREFIX_ELSE) {
                h += sizeof (WORD);
                h += *(DWORD FAR *) h ;
                } // PREFIX_ELSE
              }
            SetCount (old);
            FreeGlobMem (old);
            }   // EM_UPDATE
          else {
            h += sizeof (WORD) + sizeof(WORD) + sizeof(LPCTRLIST) + CondLen;
            if (res) {
              // Dahinter Steht ein Block, der wieder mit ExCuteBlock 
              // abgefertigt wird (wenn noetig)
              if (!ExCuteBlock (h,0L,mode)) return FALSE ;
              }
            h += *(DWORD FAR *) h ;
            // Es muss noch untersucht werden, ob vielleicht noch ein Else 
            // dahinter steht
            if (h < end) {
              command = * (WORD FAR *) h ;
              if (command == PREFIX_ELSE) {
                h += sizeof (WORD);
                if (!res) {
                  if (!ExCuteBlock (h,0L,mode)) return FALSE ;
                  }
                h += *(DWORD FAR *) h ;
                } // PREFIX_ELSE
              }   // h < end
            }     // !EM_RESET..
          if (mode & EM_FIXCONNECTION) {
            // Block ist fertig -> kann wieder gepopt werden
            _ccount = PopBlock(_ccount);
            _ccount->Increment();
            }
          }
          break ;       // PREFIX_IF
        case PREFIX_ABORT :
#ifdef DEBUG
          ClearCallStack ();
#endif
          return FALSE ;
          break ;
        case PREFIX_FUNCSTOP :
#ifdef DEBUG
          ClearCallStack ();
#endif
          return FALSE ;
          break ;
        case PREFIX_BREAK :
          fornext_result = BREAK_DONE ;
#ifdef DEBUG
          ClearCallStack ();
#endif
          return FALSE ;
          break ;
        case PREFIX_CONTINUE :
          fornext_result = CONTINUE_DONE ;
#ifdef DEBUG
          ClearCallStack ();
#endif
          return FALSE ;
          break ;
        case PREFIX_FUNCTIONCALL :
          // DBWIN_ASSERT_TEXT ((_ExtraType != EXTRATYPE_LIST),"Aufruf von Funktionen in Listen nur statisch erlaubt");
          h = DoFunctionCall (h,mode);
          if (mode & EM_FIXCONNECTION)
            _ccount->Increment();
          break ;
        case PREFIX_STFUNCTIONCALL :
          if (mode & EM_LOAD) {
            DoFunctionCall (h,EM_LOAD | EM_CHANGETOTRUE);
            h = DoFunctionCall (h,EM_RESET | EM_CLEAR);
            }
          else
            h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;
          if (mode & EM_FIXCONNECTION)
            _ccount->Increment();
          break ;
        case PREFIX_VIRTCALL :
          // DBWIN_ASSERT_TEXT ((_ExtraType != EXTRATYPE_LIST),"Aufruf von Funktionen in Listen nur statisch erlaubt");
          if (mode & (EM_CHANGETOFALSE | EM_RESET | EM_CLEAR)) {
            GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID(),LPSTR(h)); 
            }
          h = DoVirtFunctionCall (h,mode);
          if (mode & EM_FIXCONNECTION)
            _ccount->Increment();
          break ;
        case PREFIX_STVIRTCALL :
          if (mode & (EM_LOAD | EM_UPDATE)) {
            DoVirtFunctionCall (h,EM_LOAD | EM_CHANGETOTRUE);
            h = DoVirtFunctionCall (h,EM_RESET | EM_CLEAR);
            }
          else
            h += *((WORD FAR *) (h + sizeof(WORD))) + sizeof (WORD) ;
          if (mode & EM_FIXCONNECTION)
            _ccount->Increment();
          break ;
        case PREFIX_FUNCSTART :
          // Herstellen der Parameterbindung
          {
          FuncStart FAR *fc = (FuncStart FAR *) h;
          if (mode & EM_LOAD) {
            LPDBRECORD r1,r2;
            if (fc->AnzLocals > 0)
              r1 = new DBLocalRecord (fc->AnzLocals,DocumentID());
            else
              r1 = NULL ;
            if (fc->AnzStaticLocals > 0)
              r2 = new DBHelpRecord (fc->AnzStaticLocals,DocumentID());
            else
              r2 = NULL ;

            // Herstellen der Nextsameverbindungen (Achtung: Von Hinten
            // anfangen, damit zuerst die Paramente gebunden werden und
            // dann erst das rueckgaberesultat)
            //---------------------------------------------------------
            if (LastFunctionCall_Vals != NULL) {
              for (int i = LastFunctionCall_AnzPars - 1 ; i >= 0 ; i--) {
                LPVOID data = LastFunctionCall_Vals[i];
                if (data != NULL)
                  r1->Set (i,data,GetBlockSize(data)) ;
                }
              LastFunctionCall_Vals = NULL ;
              }
            else {
              for ( int i = LastFunctionCall_AnzPars - 1 ; i >= 0 ; i--) {
                LPVARELEM v1 = r1->GetVarElem(i);
                // Es muessen kurzfristig die Extradaten des aufrufenden Scripts
                // gesetzt werden
                RestoreLastExtra ();
                if (fc->BindTyp[i] != BIND_RETURN) {
                  // Zuerst aufruf eines Reads, damit das GetVarElem
                  // auch venuenftige Daten liefert
                  //------------------------------------------------
                  // LastFunctionChild->ReadlData (LastFunctionCall_par[i]);
                  // Fuer den Fall, dass es sich um Funktionen handelt -> Connections setzten
                  if ((LOWORD(LastFunctionCall_par[i]) >= EXPTABLEBASE) && (mode & EM_FIXCONNECTION)) {
                    LPEXPPTR FAR *e = LastFunctionChild->GetExpPtr (LastFunctionCall_par[i]);
                    LastFunctionChild->_ccount->DecrementSingle ();
                    _ccount = PushBlock (_ccount);
                    LastFunctionChild->ReadlData (LastFunctionCall_par[i]);
                    LastFunctionChild->CallExpression (LPSTR(e) + sizeof(LPVOID),EM_FIXCONNECTION);
                    _ccount = PopBlock(_ccount);
                    LastFunctionChild->_ccount->IncrementSingle ();
                    }
                  else
                    LastFunctionChild->ReadlData (LastFunctionCall_par[i]);
                  }
                LPVARELEM v2 = LastFunctionChild->GetVarElem (LastFunctionCall_par[i]);
                SetLastExtra ();
                if (((fc->BindTyp[i] == BIND_DYNAMIC) || (fc->BindTyp[i] == BIND_RETURN)) && (LOWORD(LastFunctionCall_par[i]) != 2)) {
                  v1->FillIn (v2);
                  v1->Property |= VEP_PARAM ;
                  }
                else {
                  LPVOID data = v2->Get();
                  if (data != NULL)
                    v1->Set (data,GetBlockSize(data)) ;
                  }
                if (v2->Erzeuger != 0L)
                  v1->Erzeuger = v2->Erzeuger ;
                else if (LOWORD(LastFunctionCall_par[i]) < EXPTABLEBASE)
                  v1->Erzeuger = DWORD(LastFunctionChild->rr) +  LOWORD(LastFunctionCall_par[i]);
                }
              }

            fc->rec1 = DWORD(r1) ;
            fc->rec2 = DWORD(r2) ;

            // Die neuen Records in den Kontext setzten
            SetRecordToLastExtraInfo (r1,DYNLOCALDATA);
            rr->SetRecord (DYNLOCALDATA,r1);
            SetRecordToLastExtraInfo (r2,STATICLOCALDATA);
            rr->SetRecord (STATICLOCALDATA,r2);
            }
          else if (mode & (EM_RESET | EM_CLEAR)) {
            if (LastFunctionCall_Vals != NULL) {
              LastFunctionCall_Vals = NULL ;
              }
            else {
              RestoreLastExtra ();
              for ( int i = LastFunctionCall_AnzPars - 1 ; i >= 0 ; i--) {
                // Es muessen kurzfristig die Extradaten des aufrufenden Scripts
                // gesetzt werden
                if (fc->BindTyp[i] != BIND_RETURN) {
                  // Fuer den Fall, dass es sich um Funktionen handelt -> Connections loeschen
                  if (LOWORD(LastFunctionCall_par[i]) >= EXPTABLEBASE) {
                    LPEXPPTR FAR *e = LastFunctionChild->GetExpPtr (LastFunctionCall_par[i]);
                    LastFunctionChild->_ccount->DecrementSingle ();
                    LastFunctionChild->_ccount = PushBlock (LastFunctionChild->_ccount);
                    LastFunctionChild->CallExpression (LPSTR(e) + sizeof(LPVOID),EM_CLEAR | EM_RESET);
                    LastFunctionChild->_ccount = PopBlock (LastFunctionChild->_ccount);
                    LastFunctionChild->_ccount->IncrementSingle ();
                    (*e)->callDone = FALSE ;
                    }
                  }
                }
              SetLastExtra ();
              }
            // Die neuen Records in den Kontext setzten
            SetRecordToLastExtraInfo (LPDBRECORD(fc->rec1),DYNLOCALDATA);
            rr->SetRecord (DYNLOCALDATA,LPDBRECORD(fc->rec1));
            fc->rec1 = 0L ;
            SetRecordToLastExtraInfo (LPDBRECORD(fc->rec2),STATICLOCALDATA);
            rr->SetRecord (STATICLOCALDATA,LPDBRECORD(fc->rec2));
            fc->rec2 = 0L ;
            }
          h += sizeof (*fc) + fc->AnzPars - 1 ;
          }
          break ;
        default :
          {
          LPVOID oldCmd = h ;
#ifdef DEBUG
          BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
          PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
          switch (command) {
            case PREFIX_FOR :
              h = DoFor (this,h,mode);
              break ;
            case PREFIX_WITH :
              h = DoWith (this,h,mode);
              break ;
            case PREFIX_INSERT :
              h = DoInsert (this,h,mode);
              break ;
            case PREFIX_REMOVE :
              h = DoRemove (this,h,mode);
              break ;
            case PREFIX_FORALL :
              h = DoForAll (this,h,mode);
              break ;
            case PREFIX_DOWITH :
              h = DoDoWith (this,h,mode);
              break ;
            default :
              DBWIN_ASSERT (FALSE);
            }
#ifdef DEBUG
          PopFromCallStack ();
#endif
          if (mode & EM_FIXCONNECTION)
            _ccount->Increment();

          if (mode & (EM_CHANGETOFALSE | EM_RESET | EM_CLEAR)) {
            GetAsync_cmdfifo()->DelCommandFifoEntry (DocumentID(),LPSTR(oldCmd)); 
            }

          if (fornext_result != FORNEXT_NORMAL)
            return FALSE ;
          }     // case default
        }       // switch
      }         // < FIRSTFUNCID
    }           // for

  return TRUE ;
  }

BOOL mdiChild::ExCuteBlock (DWORD Offset,WORD mode)
  {
  return ExCuteBlock (base,Offset,mode);
  }

void mdiChild::ExCute (WORD mode)
  {
  ToBusyCursor();
  ResetCount ();
  ExCuteBlock (* ((DWORD FAR *) base + 1) + sizeof(DWORD),mode);
  }

void mdiChild::ExCuteif (char FAR *blockbeg,WORD mode)
  {
//  ExCuteBlock (HPSTR(blockbeg)-HPSTR(base),mode);
  ExCuteBlock (blockbeg,0L,mode);
  }

void mdiChild::ExCuteelse (char FAR *blockbeg,WORD mode)
  {
  // old version char FAR *base = MK_FP(FP_SEG(blockbeg),0);
  char FAR *elsebeg = LPSTR (HPSTR(blockbeg) + *(DWORD FAR *) blockbeg);
  if (*(WORD FAR *) elsebeg == PREFIX_ELSE)
    ExCuteBlock (elsebeg + sizeof(WORD),0L,mode);
  }

void mdiChild::CallExpression (LPVOID cmd,WORD mode)
  {
#ifdef DEBUG
  BeforeExecution (this,mode,schd->fName,GetCmdOffset (cmd));
  PushToCallStack (this,schd->fName,GetCmdOffset (cmd));
#endif
  if (*(WORD FAR *) cmd == PREFIX_FUNCTIONCALL) {
    // DBWIN_ASSERT_TEXT ((_ExtraType != EXTRATYPE_LIST),"Aufruf von Funktionen in Listen nur statisch erlaubt");
    if (mode & EM_LOAD)
      DoFunctionCall ((char huge *) cmd,mode | EM_FIXCONNECTION);
    else
      DoFunctionCall ((char huge *) cmd,mode);
    }
  else if (*(WORD FAR *) cmd == PREFIX_VIRTCALL) {
    if (mode & EM_LOAD)
      DoVirtFunctionCall ((char huge *) cmd,mode | EM_FIXCONNECTION);
    else
      DoVirtFunctionCall ((char huge *) cmd,mode);
    }
  else if (*(WORD FAR *) cmd  == PREFIX_STFUNCTIONCALL) {
    // if ((mode & EM_LOAD) && (!DontCheckCallDone)) {
    if (mode & EM_LOAD) {
      DoFunctionCall ((char huge *) cmd,EM_LOAD | EM_CHANGETOTRUE);
      DoFunctionCall ((char huge *) cmd,EM_RESET | EM_CLEAR);
      }
    }
  else if (*(WORD FAR *) cmd  == PREFIX_STVIRTCALL) {
    // if ((mode & EM_LOAD) && (!DontCheckCallDone)) {
    if (mode & EM_LOAD) {
      DoVirtFunctionCall ((char huge *) cmd,EM_LOAD | EM_CHANGETOTRUE);
      DoVirtFunctionCall ((char huge *) cmd,EM_RESET | EM_CLEAR);
      }
    }
  else
    (* ddsfunc [*(WORD FAR *) cmd - FIRSTFUNCID]) (this,LPSTR(cmd) + sizeof (WORD),mode);
#ifdef DEBUG
    PopFromCallStack ();
#endif
  }

void mdiChild::CallCommand (LPVOID cmd,WORD mode)
  {
#ifdef WIN32
#ifndef DEBUG
  mdiChild *dummy = this;
  dummyptr = &dummy;
#endif
#endif
  ActiveBlock startBlock;
  int ExtraType;
  LPCONNEXTRAINFO Extra = LPCONNEXTRAINFO(GetUpdateExtraData (&ExtraType));
  SAVEREC old;
  LPCONNEXTRAINFO oldExtra;
  WORD oldSize,oldType;
  if ((Extra != NULL) && (ExtraType == EXTRATYPE_REC))
    SetRecsForUpdate (old,Extra);
  else {
    oldExtra = _ExtraData ;
    oldSize = _ExtraSize;
    oldType = _ExtraType;
    _ExtraData = NULL;
    }
  HPSTR h = HPSTR (cmd);
  WORD command = *(WORD FAR *) h ;
  if (command == PREFIX_IF) {
    // Condition, die sich aendern koennte
    DWORD CondLen;
    WORD FAR *oldres = (WORD FAR *) (h + sizeof (WORD));
    PushOffset (GetConnectionAddress(h));
    LPCMDCOUNT old = _ccount->Copy ();
    SetCount (GetCounter ((LPCTRLIST) (h + 2 * sizeof(WORD))));
    if ((Extra != NULL) && (ExtraType == EXTRATYPE_REC)) {
      // ExtraDaten wieder setzten
      SetExtraInfo s(this,Extra);

      BOOL res = CheckCond (h + 2 * sizeof (WORD) + sizeof(LPCTRLIST),&CondLen,mode) ;
      PopOffset ();
      if (res != GetCondRes (*oldres)) {
        WriteCondRes (oldres,res);
        h += 2 * sizeof (WORD) + sizeof(LPCTRLIST) + CondLen ;
        _ccount = PushBlock (_ccount);
        if (res) {
          ExCuteelse (h,EM_CLEAR | EM_CHANGETOFALSE);
          ExCuteif (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
          }
        else {
          ExCuteif (h,EM_CLEAR | EM_CHANGETOFALSE);
          ExCuteelse (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
          }
        }
      }
    else {
      BOOL res = CheckCond (h + 2 * sizeof (WORD) + sizeof(LPCTRLIST),&CondLen,mode) ;
      PopOffset ();
      if (res != GetCondRes (*oldres)) {
        WriteCondRes (oldres,res);
        h += 2 * sizeof (WORD) + sizeof(LPCTRLIST) + CondLen ;
        _ccount = PushBlock (_ccount);
        if (res) {
          ExCuteelse (h,EM_CLEAR | EM_CHANGETOFALSE);
          ExCuteif (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
          }
        else {
          ExCuteif (h,EM_CLEAR | EM_CHANGETOFALSE);
          ExCuteelse (h,EM_LOAD | EM_FIXCONNECTION | EM_CHANGETOTRUE);
          }
        }
      }
    SetCount (old);
    FreeGlobMem (old);
    }
  else if (command == PREFIX_FOR) {
    LPCMDCOUNT old = _ccount->Copy ();
    // ExtraDaten wieder setzten
    if ((Extra != NULL) && (ExtraType == EXTRATYPE_REC)) {
      SetExtraInfo s(this,Extra);
#ifdef DEBUG
      BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
      PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
      _ccount = PushBlock (_ccount);
      DoFor (this,h,mode);
#ifdef DEBUG
      PopFromCallStack ();
#endif
      }
    else {
#ifdef DEBUG
      BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
      PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
      _ccount = PushBlock (_ccount);
      DoFor (this,h,mode);
#ifdef DEBUG
      PopFromCallStack ();
#endif
      }
    SetCount (old);
    FreeGlobMem (old);
    }
  else {
    // Normale Funktion
    if ((Extra != NULL) && (ExtraType == EXTRATYPE_REC)) {
      // ExtraDaten wieder setzten
      SetExtraInfo s(this,Extra);
#ifdef DEBUG
      BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
      PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
      switch (command) {
        case PREFIX_WITH :
          DoWith (this,h,mode);
          break ;
        case PREFIX_INSERT :
          DoInsert (this,h,mode);
          break ;
        case PREFIX_REMOVE :
          DoRemove (this,h,mode);
          break ;
        case PREFIX_FORALL :
          DoForAll (this,h,mode);
          break ;
        case PREFIX_DOWITH :
          DoDoWith (this,h,mode);
          break ;
        case PREFIX_VIRTCALL :
          DoVirtFunctionCall (h,mode);
          break ;
        default :
          (* ddsfunc [command - FIRSTFUNCID]) (this,h + sizeof (WORD),mode);
        }
#ifdef DEBUG
      PopFromCallStack ();
#endif
      }
    else {
#ifdef DEBUG
      BeforeExecution (this,mode,schd->fName,GetCmdOffset (h));
      PushToCallStack (this,schd->fName,GetCmdOffset (h));
#endif
      switch (command) {
        case PREFIX_WITH :
          DoWith (this,h,mode);
          break ;
        case PREFIX_INSERT :
          DoInsert (this,h,mode);
          break ;
        case PREFIX_REMOVE :
          DoRemove (this,h,mode);
          break ;
        case PREFIX_FORALL :
          DoForAll (this,h,mode);
          break ;
        case PREFIX_DOWITH :
          DoDoWith (this,h,mode);
          break ;
        case PREFIX_VIRTCALL :
          DoVirtFunctionCall (h,mode);
          break ;
        default :
          (* ddsfunc [command - FIRSTFUNCID]) (this,h + sizeof (WORD),mode);
        }
#ifdef DEBUG
      PopFromCallStack ();
#endif
      }
    }
  if ((Extra != NULL) && (ExtraType == EXTRATYPE_REC)) {
    RestoreRecs (old) ;
    }
  else {
    _ExtraData = oldExtra;
    _ExtraSize = oldSize;
    _ExtraType = oldType;
    }
  }

/////////////////////////////////////////////////////////////////
//  Dynamisches Linken
/////////////////////////////////////////////////////////////////
BOOL dynalink::Load(LPSTR fn)
  {
  if (*fname == '\0') {
    // Das erste mal, dass geladen wird
    DBWIN_ASSERT (lstrlen(fn) <= 12);
    lstrcpy (fname,fn);

    // Laden der Kommandos
    LPSCRIPTCONTENT scent = GetScriptEntry(fname);
    if (scent != NULL) {
      GLOBALHANDLE hGPmem;
      scent->GetScriptData (&hGExtCommands,&hGPmem,NULL);
      ExtBase = (LPSTR)GlobalLock (hGExtCommands);
      ProcHash = new hash (111,STRKEY);
      GlobalUnlock (hGExtCommands);
      ProcHash->GetHash (hGPmem);
      GlobalFree (hGPmem);
      }
    }
  return (hGExtCommands != 0);
  }

DWORD dynalink::GetProcAddr (LPSTR Name)
  {
  DBWIN_ASSERT (ProcHash != NULL);
  LPSTR Data = LPSTR (ProcHash->GetData (Name));
  DWORD res ;
  if (Data != NULL) {
    res = * ((DWORD FAR *) Data);
    }
  else {
    char outtxt[128];
    wsprintf (outtxt,"Prozedur %s nicht gefunden",Name);
    DBWIN_ASSERT_TEXT (FALSE,outtxt);
    res = 0;
    }
  return res;
  }

#pragma pack(1)
struct CallExternProc_param {
  WORD parSize;
  DWORD fname;
  DWORD procName;
  };
#pragma pack()

BOOL CallExternProc (mdiChild *c,LPVOID param,WORD mode)
  {
  CallExternProc_param FAR *par = 
            (CallExternProc_param FAR *) param;
  LPSTR fname = LPSTR (c->ReadlData (par->fname));
  BOOL res = FALSE ;
  if (c->ExtPrg == NULL)
    c->ExtPrg = new dynalink() ;
  if (c->ExtPrg->Load(fname)) {
    LPSTR procName = LPSTR (c->ReadlData (par->procName));
    DWORD addr = c->ExtPrg->GetProcAddr (procName);
    if (addr > 0)
      res = c->ExCuteBlock (addr+sizeof(DWORD),mode);
    }
  return res;
  }

WORD CountToBase (LPTABLEDEF FAR *td,mdiChild *c,WORD FAR *TableInd)
  {
  WORD res = 1 ;
  for ( TableRef x = c->schd->TRef[*TableInd - CSYSRECS] ; ; ) {
    TableRef xnext;
    xnext.TableNr = (*td)->GetParentID();
    xnext.Version = (*td)->GetParentVersion();
    if (xnext.TableNr != 0) {
      GetTableAdmin()->FreeTable (x.TableNr,x.Version);
      res ++ ;
      (*TableInd)++ ;
      x = xnext ;
      *td = GetTableAdmin()->GetTableDef (x.TableNr,x.Version);
      }
    else
      break ;
    }
  return res;
  }

LPTABLEDEF GetTableDef (LPSTR Name,mdiChild *c,WORD FAR *TableInd,WORD FAR *Anz,int TableNr)
  {
  if (TableNr >= 0) {
    *TableInd = TableNr + CSYSRECS ;
    LPTABLEDEF res = GetTableAdmin()->GetTableDef(c->schd->TRef[TableNr].TableNr,c->schd->TRef[TableNr].Version);
    *Anz = CountToBase (&res,c,TableInd);
    // DBWIN_ASSERT (res->GetParentID() == 0);
    return res ;
    }
  else {
    WORD tid,Version ;
    int tnr = GetTableNr (c->schd,&tid,&Version,Name);
    if (tnr >= 0) {
      *TableInd = tnr;
      LPTABLEDEF res = GetTableAdmin()->GetTableDef(tid,Version);
      *Anz = CountToBase (&res,c,TableInd);
      // DBWIN_ASSERT (res->GetParentID() == 0);
      return res ;
      }
    }
  char debugInfo[2048];
  char nameBuf[128];
  if ((Name != NULL) && (*Name != '\0'))
    lstrcpyn (nameBuf,Name,sizeof(nameBuf));
  else
    lstrcpy (nameBuf,"<null>");
  wsprintf (debugInfo,
            "GetTableDef failed: Name=%s, TableNrArg=%d, AnzTables=%u",
            nameBuf,TableNr,c->schd->AnzTables);
  int foundByName = -1;
  WORD foundTid = 0;
  WORD foundVer = 0;
  if ((Name != NULL) && (*Name != '\0')) {
    for (int si = 0 ; si < int(c->schd->AnzTables) ; si++) {
      WORD scanTid = c->schd->TRef[si].TableNr;
      WORD scanVer = c->schd->TRef[si].Version;
      if (scanTid <= 0)
        continue;
      LPTABLEDEF scanTd = GetTableAdmin()->GetTableDef (scanTid,scanVer);
      if (scanTd != NULL) {
        BOOL isMatch = (lstrcmp (scanTd->GetName(),Name) == 0);
        GetTableAdmin()->FreeTable (scanTid,scanVer);
        if (isMatch) {
          foundByName = si;
          foundTid = scanTid;
          foundVer = scanVer;
          break;
          }
        }
      }
    }
  if (foundByName >= 0) {
    char matchInfo[96];
    wsprintf (matchInfo,"; NameMatch=TRef[%d]=%u/%u",foundByName,foundTid,foundVer);
    if ((lstrlen(debugInfo) + lstrlen(matchInfo)) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,matchInfo);
    }
  else {
    if ((lstrlen(debugInfo) + 20) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,"; NameMatch=<none>");
    }
  int found20480 = -1;
  WORD found20480ver = 0;
  for (int si = 0 ; si < int(c->schd->AnzTables) ; si++) {
    if (c->schd->TRef[si].TableNr == 20480) {
      found20480 = si;
      found20480ver = c->schd->TRef[si].Version;
      break;
      }
    }
  if (found20480 >= 0) {
    char table20480Info[64];
    wsprintf (table20480Info,"; TRefContains20480=TRef[%d]/%u",found20480,found20480ver);
    if ((lstrlen(debugInfo) + lstrlen(table20480Info)) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,table20480Info);
    }
  else {
    if ((lstrlen(debugInfo) + 25) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,"; TRefContains20480=<none>");
    }
  int maxDump = c->schd->AnzTables;
  if (maxDump > 10)
    maxDump = 10;
  if (c->schd->AnzTables > maxDump) {
    char limInfo[48];
    wsprintf (limInfo,"; DumpLimit=%d",maxDump);
    if ((lstrlen(debugInfo) + lstrlen(limInfo)) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,limInfo);
    }
  for (int di = 0 ; di < maxDump ; di++) {
    char part[180];
    WORD dumpTid = c->schd->TRef[di].TableNr;
    WORD dumpVer = c->schd->TRef[di].Version;
    if (dumpTid > 0) {
      LPTABLEDEF dumpTd = GetTableAdmin()->GetTableDef (dumpTid,dumpVer);
      if (dumpTd != NULL) {
        wsprintf (part,"; TRef[%d]=%u/%u:%s",di,dumpTid,dumpVer,dumpTd->GetName());
        GetTableAdmin()->FreeTable (dumpTid,dumpVer);
        }
      else
        wsprintf (part,"; TRef[%d]=%u/%u:<missing>",di,dumpTid,dumpVer);
      }
    else
      wsprintf (part,"; TRef[%d]=%u/%u:<temp-or-const>",di,dumpTid,dumpVer);
    if ((lstrlen(debugInfo) + lstrlen(part)) < int(sizeof(debugInfo) - 1))
      lstrcat (debugInfo,part);
    }
  DBWIN_ASSERT_TEXT (FALSE,debugInfo);  // Tabelle nicht deklariert !!
  return NULL ;
  }

void DoRemoveObjEnt (LPVOID lo,LPDBRECORD r);
void OnThrowRecord (LPDBRECORD r);
#define LISTID  0x10001L
#pragma pack(1)
struct ListPtrData {
  LPVOID ptr;
  char magic[5];
  };
#pragma pack()
static char magicdata[5] = { 12 , 2 , 0 , 7 , 0x7E } ;
extern LPDBRECORD FindRecordInCycl (LPDBRECORD rs,TableRef FAR *x);
extern void PushToCycl (LPDBRECORD rs,LPDBRECORD rd);
LPDBRECORD GetCyclRecord (LPDBRECORD rs,TableRef t)
  {
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (t.TableNr,t.Version);
  LPDBRECORD rd = FindRecordInCycl (rs,&t);
  if (rd == NULL) {
    rd = new DBRecord (td);
    PushToCycl (rs,rd);
    }
  GetTableAdmin()->FreeTable (t.TableNr,t.Version);
  return rd;
  }
class FAR ForParam {
 public :
  WORD TableInd;
  RecordList FAR *lst;
  ForHeader FAR *hd;
  LPTABLEDEF td;
  LPSTR AliasName;
  MultiProc FAR *mp;
  mdiChild *c;
  int   MaxRecID;
  HPSTR InitBeg;
  HPSTR CondBeg;
  HPSTR NextBeg;
  HPSTR BlockBeg;
  HPSTR EndFor;
  LPCONNEXTRAINFO ExtraDataAtCreation ;
  LPVOID OutputObj;

  ForParam (ForHeader FAR *h,mdiChild *child)
    {
    hd = h ;
    c = child;
    LPCONNEXTRAINFO ec = c->_GetRecExtra() ;
    if (ec != NULL) {
      ExtraDataAtCreation = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize (ec)));
      lmemcpy (ExtraDataAtCreation,ec,GetBlockSize (ec));
      }
    }

  virtual ~ForParam ()
    {
    if (ExtraDataAtCreation != NULL)
      FreeGlobMem (ExtraDataAtCreation);
    if (AliasName != NULL)
      FreeGlobMem (AliasName);
    }

  void WriteRes (LPVOID ptr)
    {
    if (hd->objVar != 0xFFFFFFFF) {
      SAVEREC s;
      if (ExtraDataAtCreation != NULL)
        c->SetRecsForUpdate (s,ExtraDataAtCreation);
      if ((ptr != NULL) && (lst != NULL)) {
        #ifdef DEBUG
        ListPtrData d;
        d.ptr = ptr;
        lmemcpy (d.magic,magicdata,sizeof(magicdata));
        c->WritelData (hd->objVar,&d,sizeof(d),hd);
        #else
        c->WritelData (hd->objVar,&ptr,sizeof(ptr),hd);
        #endif
        }
      else
        c->DellData (hd->objVar,hd);
      if (ExtraDataAtCreation != NULL)
        c->RestoreRecs (s);
      }
    }
  void SetExtraConnections (mdiChild *c)
    {
    for (int i = 0 ; i < int(hd->AnzParams) ; i++)
      c->SetlConnection (hd->Par[i],hd);
    }
  void ClearExtraConnections (mdiChild *c)
    {
    for (int i = 0 ; i < int(hd->AnzParams) ; i++)
      c->ClearlConnection (hd->Par[i],hd);
    }
  void ThrowList ()
    {
    for (LPDBRECORD h = lst->GetFirst () ; h != NULL ; h = lst->GetNext(h)) {
      OnThrowRecord (h);
      }
    lst->ThrowList ();
    }
  void SetStartPtrs (HPSTR first)
    {
    InitBeg = first ;
    CondBeg = InitBeg + *((DWORD FAR *) (InitBeg));
    }
  void SetEndPtrs (DWORD CondLen)
    {
    // Die Ganzen Zeiger muss auf jeden Fall im Source - Script abrennen
    // damit RestoreListFnc auch richtig funktioniert
    //------------------------------------------------------------------
    NextBeg  = CondBeg + CondLen ;
    BlockBeg = NextBeg + *((DWORD FAR *) (NextBeg));
    EndFor   = BlockBeg + *((DWORD FAR *) (BlockBeg));
    // if ((c->_ExtraData != NULL) && (c->_ExtraType == EXTRATYPE_REC)) {
    //  NextBeg = (NextBeg - HPSTR(c->_ExtraData->cmdBase) + c->_ExtraData->cOffs) + c->base;
    //  }
    // BlockBeg = (BlockBeg - HPSTR(c->_ExtraData->cmdBase) + c->_ExtraData->cOffs) + c->base;
    // EndFor = (EndFor - HPSTR(c->_ExtraData->cmdBase) + c->_ExtraData->cOffs) + c->base;
    // }
    }
  void RemoveMP (mdiChild *c,WORD mode)
    {
    if ((TableInd != 0xFFFF) && (lst != NULL) && (mp != NULL)) {
      LPDBRECORD old = c->rr->GetRecord(TableInd);
      for (LPDBRECORD r = lst->GetFirst () ; r != NULL ; r = lst->GetNext (r) ) {
        c->rr->SetRecord (TableInd,r);
        if (c->IsInListFunction ()) {
          SetExtraInfo extra(c,c->_ExtraData->i.keyData,mp->CorrOffs());
          extra.actci()->fOffs = extra.actci()->cOffs;
          mp->ExCute (r->GetPrimKey(),mode,&extra);
          mp->Remove (r->GetPrimKey());
          }
        else {
          SetExtraInfo s(c,TableInd,r,mp->CorrOffs());
          mp->ExCute (r->GetPrimKey(),mode,&s);
          mp->Remove (r->GetPrimKey());
          }
        }
      c->rr->SetRecord (TableInd,old);
      }
    }
  void RemoveOutList ()
    {
    if (lst != NULL) {
      for (LPDBRECORD r = lst->GetFirst () ; r != NULL ; r = lst->GetNext (r) ) {
        if (OutputObj != NULL) DoRemoveObjEnt (OutputObj,r);
        }
      }
    }
  
  virtual void ResetCond (mdiChild *c)
    {
    DWORD cLen;
    PushOffset (c->GetConnectionAddress(hd));
    c->CheckCond (CondBeg,&cLen,EM_RESET | EM_CLEAR);
    PopOffset ();
    }
  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    PushOffset (c->GetConnectionAddress(hd));
    BOOL doIt = c->CheckCond (CondBeg,cLen,myMode);
    PopOffset ();
    *n = NULL ;
    *TableInd = 0xFFFF ;
    return doIt;
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    DWORD cLen;
    PushOffset (c->GetConnectionAddress(hd));
    c->CheckCond (CondBeg,&cLen,EM_RESET | EM_CLEAR);
    BOOL doIt = c->CheckCond (CondBeg,&cLen,myMode);
    PopOffset ();
    *n = NULL ;
    return doIt;
    }
  void SetPrimKeyToRecord (LPDBRECORD r)
    {
    PrimKey k ;
    k.PushKeySeg (&hd,sizeof(hd));
    k.PushKeySeg (&MaxRecID,sizeof(MaxRecID));
    MaxRecID ++ ;
    r->SetPrimKey (&k);
    }
  void AddMP (mdiChild *c,HPSTR h,WORD mode)
    {
    BOOL doIt = TRUE ;
    WORD myMode = (mode & EM_UPDATE) ? EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION : mode ;
    WORD TableInd1,Anz1;
    int next_result = FORNEXT_NORMAL;
    BOOL first = TRUE ;
    for (
        MaxRecID = 0 ,
        // Ausfuehren der Init - Prozedur
        c->ExCuteBlock (InitBeg,0L,EM_LOAD | EM_CHANGETOTRUE) ,
        c->ExCuteBlock (InitBeg,0L,EM_RESET | EM_CLEAR);
        doIt ;
        MaxRecID ++ 
        ) {
      // Ueberpruefen der Condition
      DWORD cLen;
      LPDBRECORD old,old1[10],n,n1;
      if (first) {
        doIt = GetFirstCond (c,&n1,&TableInd1,&Anz1,myMode,&cLen) , SetEndPtrs (cLen) ;
        c->_ccount->Increment();
        c->_ccount = PushBlock(c->_ccount);
        first = FALSE ;
        }
      else               
        doIt = GetNextCond (c,&n1,myMode,*(DWORD FAR *) BlockBeg > 2 * sizeof(DWORD));
      if ((mp == NULL) && (*(DWORD FAR *) BlockBeg > 2 * sizeof(DWORD)) && (lst != NULL)) {
        DWORD ptr;
        if (c->_ExtraData != NULL)
          ptr = (BlockBeg - HPSTR(c->_ExtraData->cmdBase) + c->_ExtraData->cOffs);
        else
          ptr = BlockBeg - HPSTR(c->base) ;
        mp = new MultiProc (c,ptr,TRUE);
        }
      if (doIt) {
        // Erzeugen eines Datensatzes und diesen in den Kontext setzen
        PrimKey k ;
        if (lst != NULL) {
          k.PushKeySeg (&h,sizeof(h));
          k.PushKeySeg (&MaxRecID,sizeof(MaxRecID));
          n = new DBRecord(td);
          n->setLocked ();
          n->SetPrimKey (&k);
          old = c->rr->GetRecord(TableInd);
          c->rr->SetRecord (TableInd,n);
          }
        if (TableInd1 != 0xFFFF) {
          for (WORD i = 0 ; i < Anz1 ; i++) {
            old1[i] = c->rr->GetRecord(TableInd1 - i);
            c->rr->SetRecord (TableInd1 - i,(i == 0) ? n1 : GetCyclRecord (n1,c->schd->TRef[TableInd1 - i - CSYSRECS]));
            }
          }

        // Ausfuehren der Next - Prozedur
        c->InitializeForResult();
        if (lst != NULL) {
          // RestoreListFnc rlf(c);
          c->ExCuteBlock (NextBeg,0L,EM_LOAD | EM_CHANGETOTRUE) ;
          next_result = c->GetForResult ();
          c->InitializeForResult();
          c->ExCuteBlock (NextBeg,0L,EM_RESET | EM_CLEAR) ; 
          lst->AddRecAtTail (n,NULL,TRUE);
          }
        else {
          // RestoreListFnc rlf(c);
          c->ExCuteBlock (NextBeg,0L,EM_LOAD | EM_CHANGETOTRUE) ;
          next_result = c->GetForResult ();
          c->InitializeForResult();
          c->ExCuteBlock (NextBeg,0L,EM_RESET | EM_CLEAR) ; 
          }
        // next_result = c->GetForResult ();
        c->InitializeForResult();

        // Ausfuehren des Blockes
        if ((mp != NULL) && (next_result == FORNEXT_NORMAL)) {
          RestoreListFnc rlf(c);
          SetExtraInfo s(c,TableInd,n,mp->CorrOffs());
          c->_ccount->Increment();
          c->_ccount = PushBlock(c->_ccount,MaxRecID);
          mp->AddProc (n->GetPrimKey());
          mp->ExCute (n->GetPrimKey(),myMode,&s);
          c->_ccount = PopBlock(c->_ccount);
          }
        if (lst != NULL)
          c->rr->SetRecord (TableInd,old);
        if (TableInd1 != 0xFFFF) {
          for (WORD i = 0 ; i < Anz1 ; i++)
            c->rr->SetRecord (TableInd1 - i,old1[i]);
          }
        if ((next_result != FORNEXT_NORMAL) && (lst != NULL)) {
          // Aus der Liste den Block wieder raushauen
          lst->ThrowRecord (n);
          }
        if (next_result == BREAK_DONE)
          doIt = FALSE ;
        }
      }
    c->_ccount = PopBlock(c->_ccount);
    }
  LPVOID operator new (size_t size)
    { return GetGlobMem(size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };

extern LPTABLEDEF CheckInnerList (LPVOID obj,RecordList FAR *FAR *lst);
class FAR InnerObjectParam : public ForParam {
 public :
  InnerObjectParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c)
    { }
  LPTABLEDEF extTableDef ;
  WORD TableInd1 ;
  RecordList FAR *ExternList ;
  LPDBRECORD LastGot;

  virtual LPDBRECORD MyGetFirst ()
    {
    return ExternList->GetFirst ();
    }
  virtual LPDBRECORD MyGetNext (LPDBRECORD h)
    {
    return ExternList->GetNext (h);
    }

  LPTABLEDEF GetExternList (LPVOID extData,LPSTR FAR *alias)
    {
    LPTABLEDEF td = CheckInnerList (extData,&ExternList);
    if (td == NULL) {
      ForParam FAR *p = (ForParam FAR *) extData;
      td = p->td;
      ExternList = p->lst ;
      *alias = p->AliasName;
      }
    return td;
    }

  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    ObjCondition FAR *oc = (ObjCondition FAR *) CondBeg;
    LPVOID FAR *extData = (LPVOID FAR *) c->ReadlData (oc->objvar);
    if ((extData != NULL) && (*extData != NULL)) {
      LPSTR Name;
      LPTABLEDEF td = GetExternList (*extData,&Name);
      *n = LastGot = MyGetFirst ();
      // Ermitteln des TableInds im aktuellen Kontext
      GetTableDef (Name,c,&TableInd1,AnzRecsToSave,oc->TableNr);
      GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
      }
    else {
      *n = LastGot = NULL ;
      ExternList = NULL ;
      }
    *cLen = sizeof (*oc);
    if (*n == NULL)
      *TableInd = 0xFFFF ;
    else
      *TableInd = TableInd1;
    // Eine Connection auf die Listenvariable setzten
    if (myMode & EM_FIXCONNECTION)
      c->SetlConnection (oc->objvar,hd);
    return (*n != NULL);
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    if ((ExternList != NULL) && (LastGot != NULL)) {
      *n = LastGot = MyGetNext (LastGot);
      }
    else {
      *n = LastGot = NULL ;
      }
    return (*n != NULL);
    }
  virtual void ResetCond (mdiChild *c)
    {
    ObjCondition FAR *oc = (ObjCondition FAR *) CondBeg;
    c->ClearlConnection (oc->objvar,hd);
    }
  };

class FAR InnerRevObjectParam : public InnerObjectParam {
 public :
  InnerRevObjectParam (ForHeader FAR *hd,mdiChild *c) : InnerObjectParam (hd,c)
    { }

  virtual LPDBRECORD MyGetFirst ()
    {
    return ExternList->GetLast ();
    }
  virtual LPDBRECORD MyGetNext (LPDBRECORD h)
    {
    return ExternList->GetPrev (h);
    }

  };

extern LPDBRECORD GetSelRec (LPVOID rec,int FAR *ind,LPTABLEDEF FAR *td,LPSTR FAR *AliasName,BOOL FAR *doMore);
class FAR OuterObjectParam : public ForParam {
 public :
  OuterObjectParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c)
    { }
  LPTABLEDEF extTableDef ;
  WORD TableInd1 ;
  LPVOID ExternList ;
  int LastInd;

  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    ObjCondition FAR *oc = (ObjCondition FAR *) CondBeg;
    ExternList = c->ReadlData (oc->objvar);
    BOOL doMore = FALSE;
    if (ExternList != NULL) {
      LPTABLEDEF td;
      LastInd = 0 ;
      LPSTR Name;
      *n = GetSelRec (ExternList,&LastInd,&td,&Name,&doMore);
      // Ermitteln des TableInds im aktuellen Kontext
      if (*n != NULL) {
        GetTableDef (Name,c,&TableInd1,AnzRecsToSave,oc->TableNr);
        GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
        }
      }
    else {
      *n = NULL ;
      }
    *cLen = sizeof (*oc);
    if (*n == NULL) {
      *TableInd = 0xFFFF ;
      *AnzRecsToSave = 0;
      }
    else {
      *TableInd = TableInd1;
      *AnzRecsToSave = 1;
      }
    return ((*n != NULL) || (doMore)) ;
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    BOOL doMore = FALSE;
    if (ExternList != NULL) {
      LastInd ++ ;
      *n = GetSelRec (ExternList,&LastInd,NULL,NULL,&doMore);
      }
    else
      *n = NULL ;
    return ((*n != NULL) || (doMore));
    }
  virtual void ResetCond (mdiChild *c)
    {
    }
  };

class FAR DBListParam : public ForParam {
 public :
  DBList FAR *dblist;
  LPTABLEDEF td;
  LPDBRECORD LastGot;
  WORD TableInd1;
  DBListParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c) 
    {
    }
  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    *cLen = DWORD(oc->Size());
    LPSTR TableName = LPSTR(c->ReadlData (oc->TableName));
    LPSTR where = LPSTR(c->ReadlData (oc->WhereName));
    LPSTR order ;
    if (oc->OrderName != 0xFFFFFFFF)
      order = LPSTR(c->ReadlData (oc->OrderName));
    else
      order = "" ;
    DBWIN_ASSERT (TableName != NULL);
    DBWIN_ASSERT (where != NULL);
    DBWIN_ASSERT (order != NULL);
    td = GetTableDef (TableName,c,&TableInd1,AnzRecsToSave,-1);
    ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    for (int i = 0 ; i < int(oc->AnzPars) ; i++) {
      p.ptr[i] = c->ReadlData (oc->Par[i]);
      p.pType[i] = c->GetDataType (oc->Par[i]);
      }
    p.AnzPars = int(oc->AnzPars);
    short AbsAnzSels;
    if (oc->anzSels < -1)
      AbsAnzSels = -oc->anzSels;
    else
      AbsAnzSels = oc->anzSels;
    dblist = new DBList (td,
                         c->DocumentID(),
                         where,
                         AbsAnzSels,
                         AbsAnzSels,
                         &p,
                         FALSE
                        );
    dblist->SetOrder (order);

    if (oc->anzSels > 0)
      dblist->SetSimpleList ();

    if (oc->DoReverse)
      *n = LastGot = dblist->GetLast();
    else
      *n = LastGot = dblist->GetFirst();
    if (*n == NULL) {
      *TableInd = 0xFFFF ;
      }
    else
      *TableInd = TableInd1 ;
    if (myMode & EM_FIXCONNECTION) {
      for (i = 0 ; i < int (oc->AnzPars) ; i++)
        c->SetlConnection (oc->Par[i],hd);
      c->SetlConnection (oc->WhereName,hd);
      }

    *AnzRecsToSave = 1;
    return (*n != NULL);
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    LPDBRECORD h = LastGot;
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    if (oc->DoReverse)
      *n = LastGot = dblist->GetPrev (LastGot);
    else
      *n = LastGot = dblist->GetNext (LastGot);
    if ((*n == NULL) && (!withActive)) {
      dblist->ThrowList();
      }
    if ((!withActive) && (*n != NULL)) {
      if (oc->DoReverse)
        dblist->ThrowAtTail (h);
      else
        dblist->ThrowAtHead (h);
      }
    return (*n != NULL);
    }
  virtual void ResetCond (mdiChild *c)
    {
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
    for (int i = 0 ; i < int (oc->AnzPars) ; i++)
      c->ClearlConnection (oc->Par[i],hd);
    c->ClearlConnection (oc->WhereName,hd);
    delete dblist , dblist = NULL;
    }
  };

BOOL IstAusgabeParameter (OutParam FAR *h,WORD i)
  {
  for ( ; h != NULL ; h = h->Next ) {
    if (h->parNum == i) return TRUE ;
    }
  return FALSE ;
  }

class FAR SelectListParam : public ForParam {
 public :
  DBList FAR *dblist;
  OutParam FAR *LastGot;
  SelectListParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c) 
    {
    }
  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    *n = NULL;
    *TableInd = 0xFFFF;
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    *cLen = DWORD(oc->Size());
    LPSTR where = LPSTR(c->ReadlData (oc->WhereName));
    DBWIN_ASSERT (where != NULL);
    ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    for (int i = 0 ; i < int(oc->AnzPars) ; i++) {
      p.ptr[i] = c->ReadlData (oc->Par[i]);
      p.pType[i] = c->GetDataType (oc->Par[i]);
      }
    p.AnzPars = int(oc->AnzPars);
    dblist = new DBList (NULL,
                         c->DocumentID(),
                         where,
                         1,
                         1,
                         &p,
                         FALSE
                        );
    dblist->SetOrder ("");
    dblist->SetSimpleList ();

    OutParam FAR *h = dblist->GetFirstParam();
    if (myMode & EM_FIXCONNECTION) {
      for (i = 0 ; i < int (oc->AnzPars) ; i++) {
        if (!IstAusgabeParameter (h,i + 1)) c->SetlConnection (oc->Par[i],hd);
        }
      c->SetlConnection (oc->WhereName,hd);
      }

    for ( OutParam FAR *x = h ; x != NULL ; x = x->Next) {
      if (x->Data) c->WritelData (oc->Par[x->parNum - 1],x->Data,GetBlockSize(x->Data),hd);
      else         c->DellData (oc->Par[x->parNum - 1],hd);
      }

    LastGot = h;
    return (h != NULL);
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    *n = NULL;
    OutParam FAR *h = LastGot;
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    LastGot = dblist->GetNextParam (LastGot);
    if ((LastGot == NULL) && (!withActive)) {
      dblist->ThrowList();
      }
    if ((!withActive) && (LastGot != NULL)) {
        dblist->ThrowAtHeadParam (h);
      }

    for ( OutParam FAR *x = LastGot ; x != NULL ; x = x->Next) {
      if (x->Data) c->WritelData (oc->Par[x->parNum - 1],x->Data,GetBlockSize(x->Data),hd);
      else         c->DellData (oc->Par[x->parNum - 1],hd);
      }

    return (LastGot != NULL);
    }
  virtual void ResetCond (mdiChild *c)
    {
    DBSelCondition FAR *oc = (DBSelCondition FAR *) CondBeg;
    for (int i = 0 ; i < int (oc->AnzPars) ; i++)
      c->ClearlConnection (oc->Par[i],hd);
    c->ClearlConnection (oc->WhereName,hd);
    delete dblist , dblist = NULL;
    }
  };

class FAR ForInitParam : public ForParam {
 public :
  int dim;
  int LastInd;
  ForInitParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c) 
    {
    }
  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    InitCondition FAR *ic = (InitCondition FAR *) CondBeg;
    *cLen = DWORD(ic->Size());
    DBWIN_ASSERT ((ic->AnzPars % ic->AnzVars) == 0);
    dim = int(ic->AnzPars / ic->AnzVars) - 1 ;
    DBWIN_ASSERT (dim >= 1);
    for (int i = 0 ; i < int (ic->AnzVars) ; i++) {
      LPVOID ptr;
      DWORD FAR *parbase = &ic->Par[i * (dim + 1)] ;
      if ((ptr = c->ReadlData (parbase[1])) != NULL)
        c->WritelData (parbase[0],ptr,GetBlockSize(ptr),hd);
      else
        c->DellData (parbase[0],hd);
      c->SetlConnection (parbase[1],hd);
      }
    LastInd = 0;
    *n = NULL ;
    *TableInd = 0xFFFF ;
    return TRUE ;
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    InitCondition FAR *ic = (InitCondition FAR *) CondBeg;
    *n = NULL ;
    if (++ LastInd < dim) {
      for (int i = 0 ; i < int (ic->AnzVars) ; i++) {
        LPVOID ptr;
        DWORD FAR *parbase = &ic->Par[i * (dim + 1)] ;
        if ((ptr = c->ReadlData (parbase[LastInd + 1])) != NULL)
          c->WritelData (parbase[0],ptr,GetBlockSize(ptr),hd);
        else
          c->DellData (parbase[0],hd);
        c->SetlConnection (parbase[LastInd + 1],hd);
        }
      return TRUE ;
      }
    else
      return FALSE ;
    }
  virtual void ResetCond (mdiChild *c)
    {
    InitCondition FAR *ic = (InitCondition FAR *) CondBeg;
    for (int i = 0 ; i < int(ic->AnzVars) ; i++) {
      DWORD FAR *parbase = &ic->Par[i * (dim + 1)] ;
      for (int j = 0 ; j < dim ; j++)
        c->ClearlConnection (parbase[j + 1],hd);
      }
    }
  };

class FAR ForNoneParam : public ForParam {
 public :
  ForNoneParam (ForHeader FAR *hd,mdiChild *c) : ForParam (hd,c) 
    {
    }
  virtual BOOL GetFirstCond (mdiChild *c,LPDBRECORD FAR *n,WORD FAR *TableInd,WORD FAR *AnzRecsToSave,WORD myMode,DWORD *cLen)
    {
    *cLen = 0 ;
    *n = NULL ;
    *TableInd = 0xFFFF ;
    return FALSE ;
    }
  virtual BOOL GetNextCond (mdiChild *c,LPDBRECORD FAR *n,WORD myMode,BOOL withActive)
    {
    *n = NULL ;
    return FALSE ;
    }
  virtual void ResetCond (mdiChild *c)
    {
    }
  };

void GetTableDef (ForHeader FAR *fh,mdiChild *c)
  {
  ForParam FAR *par = (ForParam FAR *) fh->fp;
  if (fh->listName == 0xFFFFFFFF)
    par->td = NULL , par->TableInd = 0xFFFF;
  else {
    LPSTR Name = LPSTR(c->ReadlData (fh->listName));
    if (*Name == '\0')
      par->td = NULL , par->TableInd = 0xFFFF;
    else {
      par->AliasName = LPSTR (GetGlobMem (lstrlen(Name) + 1));
      lstrcpy (par->AliasName,Name);
      WORD Ar;
      par->td = GetTableDef (Name,c,&par->TableInd,&Ar,-1);
      WIN_ASSERT (Ar == 1);
      }
    }
  }

HPSTR DoFor (mdiChild *c,HPSTR h,WORD mode)
  {
  ForHeader FAR *fh = (ForHeader FAR *) h;
  HPSTR end;
  if (mode & EM_LOAD) {
    // Anlegen des Forparams
    ForParam FAR *par;
    switch (fh->forType) {
      case FORTYPE_COND :
        par = new ForParam (fh,c);
        break ;
      case FORTYPE_INNEROBJ :
        par = new InnerObjectParam (fh,c);
        break ;
      case FORTYPE_INNEROBJREV :
        par = new InnerRevObjectParam (fh,c);
        break ;
      case FORTYPE_OUTEROBJ :
        par = new OuterObjectParam (fh,c);
        break ;
      case FORTYPE_DBLIST :
        par = new DBListParam (fh,c);
        break ;
      case FORTYPE_INIT :
        par = new ForInitParam (fh,c);
        break ;
      case FORTYPE_SELECT :
        par = new SelectListParam (fh,c);
        break ;
      case FORTYPE_NONE :
        par = new ForNoneParam (fh,c);
        break ;
      }
    fh->fp = par ;

    // Speichern des Zaehlers
    SetCounter ((LPCTRLIST) &fh->ctrs,c->_ccount);
    // Erzeugen der inneren Liste
    GetTableDef (fh,c);
    if (par->td != NULL)
      par->lst = new RecordList (par->td,c->DocumentID(),0,TRUE);
    else
      par->lst = NULL ;

    // Ermitteln der Zeiger fuer die Bereiche, soweit moeglich
    par->SetStartPtrs (HPSTR(fh)+fh->Size());

    if (mode & EM_FIXCONNECTION) {    // Der Fixconnection muss vor dem eigentlichen
                                      // AddMP durchgefuehrt werden, sonst gibts Probleme 
                                      // mit den Counters
      ForParam FAR *par = (ForParam FAR *) fh->fp;
      par->SetExtraConnections (c);
      end = par->EndFor;
      }

    // Und den ganzen Salat durchfuehren
    par->AddMP (c,h,mode);

    // fertig
    par->WriteRes (par);
    end = par->EndFor;
    }
  if (mode & EM_UPDATE) {
    ForParam FAR *par = (ForParam FAR *) fh->fp;
    par->ResetCond (c);
    c->SetCount (GetCounter ((LPCTRLIST) &fh->ctrs));
    par->RemoveOutList ();
    if (par->mp != NULL)
      par->RemoveMP (c,EM_RESET | EM_CLEAR);
    if (par->lst != NULL) {
      par->ThrowList ();
      }
    par->AddMP (c,h,mode);

    // fertig
    par->WriteRes (par);
    end = par->EndFor;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    // Freigeben des forparams
    ForParam FAR *par = (ForParam FAR *) fh->fp;
    end = par->EndFor;

    par->ResetCond (c);
    par->RemoveOutList ();
    if (par->OutputObj != NULL) DoRemoveObjEnt (par->OutputObj,NULL);
    if (par->mp != NULL) {
      par->RemoveMP (c,mode);
      delete par->mp ;
      }
    if (par->lst != NULL) {
      par->ThrowList ();
      delete par->lst;
      }
    if (par->td != NULL)
      GetTableAdmin()->FreeTable (par->td->GetTableID(),par->td->GetVersion());
      
    par->WriteRes (NULL);
    par->ClearExtraConnections (c);
    delete par;
    fh->fp = NULL ;
    RemoveCount ((LPCTRLIST) &fh->ctrs);
    }
  return end;
  }

void OnEmptyList (LPVOID obj)
  {
  ForParam FAR *fp = (ForParam FAR *) obj;
  fp->RemoveOutList ();
  if (fp->mp != NULL) {
    if (fp->ExtraDataAtCreation != NULL) {
      // ExtraDaten wieder setzten
      SAVEREC sr;
      SetExtraInfo s(fp->c,fp->ExtraDataAtCreation);
      fp->c->SetRecsForUpdate (sr,fp->ExtraDataAtCreation);
      fp->RemoveMP (fp->c,EM_RESET | EM_CLEAR);
      fp->c->RestoreRecs (sr);
      }
    else
      fp->RemoveMP (fp->c,EM_RESET | EM_CLEAR);
    }
  if (fp->lst != NULL)
    fp->ThrowList ();
  fp->MaxRecID = 0 ;
  }

RecordList FAR * GetListFromForParam (LPVOID obj,LPVOID outobj)
  {
  ((ForParam FAR *) obj)->OutputObj = outobj;
  return ((ForParam FAR *) obj)->lst ;
  }

RecordList FAR * GetListFromForParam_noset (LPVOID obj)
  {
  return ((ForParam FAR *) obj)->lst ;
  }

class ListWork {
  RecordList FAR *List;
  int AnzSegs;
  int segsFound;
  int RecordID[32];
  TableRef tr[32];
  LPVOID CmpData[32];
 public :
  ListWork (RecordList FAR *l)
    {
    List = l;
    AnzSegs = 0;
    }
  ~ListWork ()
    {
    for (int i = 0 ; i < AnzSegs ; i++)
      if (CmpData[i]) FreeGlobMem (CmpData[i]) ;
    }
  void SetCmpData (LPVOID d,mdiChild *c,DWORD Id)
    {
    RecordID[AnzSegs] = HIWORD(Id);
    tr[AnzSegs] = c->schd->TRef[LOWORD(Id) - CSYSRECS];

    if (d != NULL) {
      CmpData[AnzSegs] = GetGlobMem (GetBlockSize(d));
      lmemcpy (CmpData[AnzSegs],d,GetBlockSize(d));
      }
    else
      CmpData[AnzSegs] = NULL ;
    AnzSegs ++ ;
    segsFound = -1;
    }
  BOOL Compare (LPDBRECORD h)
    {
    return CompareEqual (h, tr, RecordID, CmpData, AnzSegs, &segsFound);
    }
  BOOL Check ()
    {
    return List->CheckSegments (tr, AnzSegs, segsFound);
    }
  LPDBRECORD FindExtended ()
    {
    return List->FindRecord (tr,RecordID,CmpData,AnzSegs);
    }
  LPDBRECORD Find (int Mode)
    {
    return List->FindRecord (tr,RecordID,CmpData,AnzSegs,Mode);
    }
  };

LPDBRECORD r0 (LPDBRECORD FAR *rb)
  {
  return (rb != NULL) ? rb[0] : NULL ;
  }
void ExCuteWith (mdiChild *c,MultiProc FAR *mp,LPVOID param,WORD TableInd,WORD mode,LPDBRECORD FAR *r,HPSTR IfBeg,HPSTR ElseBeg,BOOL doLoad,WORD AnzRecsToSet)
  {
  WithParam FAR *par = (WithParam FAR *) param ;
  if ((mode & EM_LOAD) || (mode & (EM_RESET | EM_CLEAR)) || 
          r0 ((LPDBRECORD FAR *) par->oldrec) != r0(r)) {
#ifdef DEBUG
    BeforeExecution (c,mode,c->schd->fName,c->GetCmdOffset (par));
    PushToCallStack (c,c->schd->fName,c->GetCmdOffset (par));
#endif
    // RestoreListFnc rlf(c);   !!!!!!! Notwendigkeit wird stark bezweifelt
    if (mode & (EM_UPDATE | EM_RESET | EM_CLEAR)) {
      // Alten raushauen
      if (par->oldrec == NULL) {
        if (ElseBeg != NULL)
          c->ExCuteBlock (ElseBeg,0L,EM_CLEAR | EM_RESET);
        }
      else {
        LPDBRECORD oldSet[10];
        SetExtraInfo s(c,TableInd,((LPDBRECORD FAR *) par->oldrec)[0],mp->CorrOffs());
        for (WORD i = 0 ; i < AnzRecsToSet ; i++) {
          LPDBRECORD oldrec = ((LPDBRECORD FAR *) par->oldrec)[i];
          oldSet[i] = c->rr->GetRecord (TableInd - i);
          c->rr->SetRecord (TableInd - i,oldrec);
          if (i > 0)
            SetRecordToLastExtraInfo (oldrec,TableInd - i);
          }
        mp->ExCuteLast (EM_RESET | EM_CLEAR,&s);
        mp->RemoveLast ();
        for (i = 0 ; i < AnzRecsToSet ; i++)
          c->rr->SetRecord (TableInd - i,oldSet[i]);
        }
      }
    // Neuen Record reinladen
    if (doLoad) {
      WORD myMode = (mode & EM_UPDATE) ? EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION : mode ;
      if ((r != NULL) && (r[0] != NULL)) {
        LPDBRECORD oldSet[10];
        SetExtraInfo s(c,TableInd,r[0],mp->CorrOffs());
        oldSet[0] = c->rr->GetRecord (TableInd);
        c->rr->SetRecord (TableInd,r[0]);
        for (WORD i = 1 ; i < AnzRecsToSet ; i++) {
          r[i] = GetCyclRecord (r[0],c->schd->TRef[TableInd - i - CSYSRECS]);
          oldSet[i] = c->rr->GetRecord (TableInd - i);
          c->rr->SetRecord (TableInd - i,r[i]);
          SetRecordToLastExtraInfo (r[i],TableInd - i);
          }
        mp->AddProcAtTail ();
        mp->ExCuteLast (myMode,&s);
        for (i = 0 ; i < AnzRecsToSet ; i++)
          c->rr->SetRecord (TableInd - i,oldSet[i]);
        }
      else {
        if (ElseBeg != NULL)
          c->ExCuteBlock (ElseBeg,0L,myMode);
        }
      }
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  else {
    // Zumindesten r muss neu gesetzt werden
    if (par->oldrec != NULL)
      lmemcpy (r,par->oldrec,AnzRecsToSet * sizeof(LPDBRECORD));
    }
  }

//
// Da es bekanntlich toedlich ist, eine Multiproc zu reseten, wenn der 
// Datensatz nicht mehr existiert, muss wie ein Haftlmacher darauf geachtet
// werden, dass vor dem Throwrecord die Multiproc noch aufgeraumt wird...
// Daher eine Liste mit allen aktiven with - Statements, die im Falle
// des Throwrecords ueberprueft wird.
//
void SetOldRec (WithParam FAR *par,LPDBRECORD FAR *r,WORD Anz);
struct FAR DoWithList {
  WithParam FAR *par;
  mdiChild *c;
  HPSTR IfBeg;
  HPSTR ElseBeg;
  BOOL mpIsCleared;
  DoWithList FAR *Next;
  DoWithList FAR *Prev;
  LPCONNEXTRAINFO Extra;
  BOOL IsToRemove (LPDBRECORD r)
    {
    if (r0((LPDBRECORD FAR *) par->oldrec) == r) return TRUE ;
    if (Extra != NULL) {
      int Anz = Extra->AnzTables ();
      for (int i = 0 ; i < Anz ; i++) {
        if (Extra->i.t[i].r == r) return TRUE ;
        }
      }
    return FALSE ;
    }

  void OnThrowRecord ()
    {
    SAVEREC old;
    if (Extra != NULL) {
      c->SetRecsForUpdate (old,Extra);
      SetExtraInfo s(c,Extra);
      ExCuteWith (c,(MultiProc FAR *) par->mp,par,par->TableInd,EM_CLEAR | EM_RESET,NULL,IfBeg,ElseBeg,FALSE,GetBlockSize(par->oldrec) / sizeof(LPDBRECORD));
      c->RestoreRecs (old) ;
      }
    else {
      LPCONNEXTRAINFO oldExtra = c->_ExtraData ;
      WORD oldExtraType = c->_ExtraType;
      int oldExtraSize = c->_ExtraSize;
      c->_ExtraData = NULL;
      c->_ExtraType = 0;
      c->_ExtraSize = 0;
      ExCuteWith (c,(MultiProc FAR *) par->mp,par,par->TableInd,EM_CLEAR | EM_RESET,NULL,IfBeg,ElseBeg,FALSE,GetBlockSize(par->oldrec) / sizeof(LPDBRECORD));
      c->_ExtraData = oldExtra ;
      c->_ExtraType = oldExtraType;
      c->_ExtraSize = oldExtraSize;
      }
    mpIsCleared = TRUE ;
    SetOldRec (par,NULL,0);
    }
  };
typedef DoWithList FAR *LPWLIST;
DoWithList FAR *WList;
// hash FAR *parHash;
DoWithList FAR *GetWithPar(WithParam FAR *par)
  {
  return par->wlist;
  // LPWLIST FAR *lplpwl = (LPWLIST FAR *) parHash->GetDatav (&par,sizeof(par));
  // return (lplpwl != NULL) ? *lplpwl : NULL ;
  }
void RemoveFromRecHash (WithParam FAR *par,LPDBRECORD r)
  {
  if (r == NULL) return ;
  LPWITHANCHORE prev = NULL;
  for ( LPWITHANCHORE x = r->lpWithAnchore ; x != NULL ; ) {
    LPWITHANCHORE Next = x->Next ;
    if (x->w->par == par) {
      // Den Nachfoler reinziehen (Liste ist sicher noch nicht leer !)
      if (prev != NULL) prev->Next = x->Next ;
      else              r->lpWithAnchore = x->Next ;
      FreeGlobMem (x);
      }
    else
      prev = x ;
    x = Next ;
    }
  }
void InsertIntoRecHash (LPWLIST w,LPDBRECORD r)
  {
  LPWITHANCHORE n = LPWITHANCHORE (GetGlobMem (sizeof(*n)));
  n->w = w ;
  n->Next = r->lpWithAnchore;
  r->lpWithAnchore = n ;
  }
void RemoveFromHashs (LPWLIST w)
  {
  // Aus den RecordLists loeschen
  if (w != NULL) {
    if (w->par->oldrec != NULL)
      RemoveFromRecHash (w->par,((LPDBRECORD FAR *) w->par->oldrec)[0]);
    // parHash->DelDatav (&w->par,sizeof(w->par));
    w->par->wlist = NULL ;
    }
  }
void OnThrowRecord (LPDBRECORD r)
  {
  BOOL doIt;
  do {
    doIt = FALSE ;
    for ( LPWITHANCHORE x = r->lpWithAnchore ; x != NULL ; x = x->Next) {
      if (!x->w->mpIsCleared) {
        x->w->OnThrowRecord() ;
        doIt = TRUE ;
        break ; // Noch einmal von vorne beginnen, da sich die Liste geaendert haben koennte
        }
      }
    } while (doIt) ;
  }
void SetOldRec (WithParam FAR *par,LPDBRECORD FAR *r,WORD Anz)
  {
  if (par->oldrec != NULL) {
    RemoveFromRecHash (par,((LPDBRECORD FAR *)par->oldrec)[0]);
    FreeGlobMem (par->oldrec);
    par->oldrec = NULL ;
    }
  if ((r != NULL) && (r[0] != NULL)) {
    InsertIntoRecHash (GetWithPar(par),r[0]);
    par->oldrec = GetGlobMem (sizeof(LPDBRECORD) * Anz);
    lmemcpy (par->oldrec,r,sizeof(LPDBRECORD) * Anz);
    }
  }
void InsertToWithList (WithParam FAR *par,mdiChild *c,HPSTR IfBeg,HPSTR ElseBeg)
  {
  DoWithList FAR *n = (DoWithList FAR *) GetGlobMem (sizeof(*n)) ;
  n->Next = WList ;
  if (WList != NULL) WList->Prev = n ;
  WList = n;
  n->par = par ;
  n->c = c ;
  n->IfBeg = IfBeg ;
  n->ElseBeg = ElseBeg ;
  LPCONNEXTRAINFO x = c->_GetRecExtra ();
  if (x != NULL) {
    n->Extra = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize(x)));
    lmemcpy (n->Extra,x,GetBlockSize(x));
    }
  // parHash->SetDatav (&par,&n,sizeof(n),sizeof(par));
  par->wlist = n;
  if (par->oldrec != NULL)
    InsertIntoRecHash (n,((LPDBRECORD FAR *)par->oldrec)[0]);
#ifdef UEBERLEGT
  if (n->Extra != NULL) {
    int Anz = n->Extra->AnzTables ();
    for (int i = 0 ; i < Anz ; i++) {
      InsertIntoRecHash (n,n->Extra->i.t[i].r);
      }
    }
#endif
  }

BOOL ChangeToLoad (WithParam FAR *par)
  {
  BOOL res = FALSE ;
  DoWithList FAR *h = GetWithPar(par);
  if (h != NULL) {
    res = h->mpIsCleared ;
    h->mpIsCleared = FALSE ;
    }
  return res ;
  }

void RemoveFromWithList (WithParam FAR *par)
  {
  LPWLIST w = GetWithPar(par);
  if (w != NULL) {
    RemoveFromHashs (w);
    if (w->Prev != NULL) w->Prev->Next = w->Next ;
    else                 WList = w->Next;
    if (w->Next != NULL) w->Next->Prev = w->Prev;
    if (w->Extra != NULL)
      FreeGlobMem (w->Extra);
    FreeGlobMem (w);
    }
  }

HPSTR DoWith (mdiChild *c,char huge *h,WORD mode)
  {
  WithParam FAR *par = (WithParam FAR *) h ;
  int AnzPars = ((par->BlockSize - sizeof(*par) + sizeof(WORD) + sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 - sizeof(DWORD) - sizeof(WORD) + sizeof(*par));
  HPSTR IfBeg   = HPSTR (&par->BlockSize) + par->BlockSize ;
  HPSTR ElseBeg = IfBeg + *(DWORD FAR *) IfBeg ;
  WORD ecommand = *(WORD FAR *) ElseBeg ;
  HPSTR end;
  ElseBeg += sizeof(WORD);
  if (ecommand == PREFIX_ELSE) {
    end = ElseBeg + *(DWORD FAR *) ElseBeg ;
    }
  else
    end = ElseBeg + sizeof(WORD) , ElseBeg = NULL ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->objvar);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    LPSTR Alias;
    if ((lpp != NULL) && (*lpp != NULL)) {
      if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
        l = LPINNERLISTDESC (*lpp)->list;
        td = LPINNERLISTDESC (*lpp)->td;
        Alias = NULL ;
        }
      else {
        l = ((ForParam FAR *) (*lpp))->lst;
        td = ((ForParam FAR *) (*lpp))->td;
        Alias = ((ForParam FAR *) (*lpp))->AliasName;
        }
      }
    BOOL done = FALSE ;
    MultiProc FAR *mp = (MultiProc FAR *) par->mp;
    if (mp == NULL) {
      DWORD ptr;
      if (c->_ExtraData != NULL)
        ptr = (IfBeg - HPSTR(c->_ExtraData->cmdBase) + c->_ExtraData->cOffs);
      else
        ptr = IfBeg - HPSTR(c->base) ;
      mp = new MultiProc (c,ptr);
      par->mp = mp ;
      }
    LPCMDCOUNT oldcnt;
    if (mode & EM_FIXCONNECTION) {
      // Damit der Counter noch nicht gesetzt ist !
      for (int i = 0 ; i < AnzPars ; i++)
        c->SetlConnection (par->Par[2 * i],par);
      c->SetlConnection (par->objvar,par);
      }
    if (mode & EM_LOAD) {
      if (mode & EM_FIXCONNECTION) {
        c->_ccount->Increment();
        c->_ccount = PushBlock(c->_ccount);
        }
      SetCounter ((LPCTRLIST) &par->ctrs,c->_ccount);
      }
    else {
      oldcnt = c->_ccount->Copy ();
      c->SetCount (GetCounter ((LPCTRLIST) &par->ctrs));
      }
    if (mode & EM_LOAD)
      InsertToWithList (par,c,IfBeg,ElseBeg);
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[2 * i]), c, par->Par[2 * i + 1]);
      LPDBRECORD r[10];
      r[0] = w.FindExtended ();
      WORD TableInd,Anz;
      DBWIN_ASSERT (GetTableDef (Alias,c,&TableInd,&Anz,par->TableNr) != NULL);
      WORD MyMode = mode ;
      if ((mode == EM_UPDATE) && (ChangeToLoad (par)))
        MyMode = EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION ;
      ExCuteWith (c,mp,par,TableInd,MyMode,r,IfBeg,ElseBeg,TRUE,Anz);
      SetOldRec (par,r,Anz);
      GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
      par->TableInd = TableInd;
      }
    if (mode & EM_UPDATE) {
      c->SetCount (oldcnt);
      FreeGlobMem (oldcnt);
      }
    if (mode & EM_FIXCONNECTION) {
      c->_ccount->Increment();
      c->_ccount = PopBlock(c->_ccount);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    if (!ChangeToLoad (par))
      ExCuteWith (c,(MultiProc FAR *) par->mp,par,par->TableInd,mode,NULL,IfBeg,ElseBeg,FALSE,GetBlockSize(par->oldrec) / sizeof(LPDBRECORD));
    for (int i = 0 ; i < AnzPars ; i++)
      c->ClearlConnection (par->Par[2 * i],par);
    c->ClearlConnection (par->objvar,par);
    RemoveCount ((LPCTRLIST) &par->ctrs);
    RemoveFromWithList (par);
    MultiProc FAR *mp = (MultiProc FAR *) par->mp;
    if (mp != NULL) delete mp ;
    par->mp = NULL;
    SetOldRec (par,NULL,0);
    }
  return end;
  }

HPSTR DoForAll (mdiChild *c,char huge *h,WORD mode)
  {
  WithParam FAR *par = (WithParam FAR *) h ;
  int AnzPars = ((par->BlockSize - sizeof(*par) + sizeof(WORD) + sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 - sizeof(DWORD) - sizeof(WORD) + sizeof(*par));
  HPSTR IfBeg   = HPSTR (&par->BlockSize) + par->BlockSize ;
  HPSTR ElseBeg = IfBeg + *(DWORD FAR *) IfBeg ;
  WORD ecommand = *(WORD FAR *) ElseBeg ;
  HPSTR end;
  ElseBeg += sizeof(WORD);
  if (ecommand == PREFIX_ELSE) {
    end = ElseBeg + *(DWORD FAR *) ElseBeg ;
    }
  else
    end = ElseBeg + sizeof(WORD) , ElseBeg = NULL ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->objvar);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    LPSTR Alias;
    if ((lpp != NULL) && (*lpp != NULL)) {
      if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
        l = LPINNERLISTDESC (*lpp)->list;
        td = LPINNERLISTDESC (*lpp)->td;
        Alias = NULL;
        }
      else {
        l = ((ForParam FAR *) (*lpp))->lst;
        td = ((ForParam FAR *) (*lpp))->td;
        Alias = ((ForParam FAR *) (*lpp))->AliasName;
        }
      }
    BOOL done = FALSE ;
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[2 * i]), c, par->Par[2 * i + 1]);
      WORD TableInd,Anz;
      DBWIN_ASSERT (GetTableDef (Alias,c,&TableInd,&Anz,par->TableNr) != NULL);
      LPDBRECORD old[10];
      for (WORD j = 0 ; j < Anz ; j++)
        old[j] = c->rr->GetRecord (TableInd - j);
      int segsFound = -1;
      for ( LPDBRECORD h = l->GetFirst () ; h != NULL ; h = l->GetNext(h)) {
        if (w.Compare (h)) {
          for (j = 0 ; j < Anz ; j++)
            c->rr->SetRecord (TableInd - j,(j == 0) ? h : GetCyclRecord (h,c->schd->TRef[TableInd - j - CSYSRECS]));
          c->ExCuteBlock (IfBeg,sizeof(DWORD),EM_LOAD | EM_CHANGETOTRUE) ,
          c->ExCuteBlock (IfBeg,sizeof(DWORD),EM_RESET | EM_CLEAR);
          done = TRUE ;
          }
        }
      if (!done) {
        DBWIN_ASSERT_TEXT (w.Check (),"Falsches Segment!");
        }
      for (j = 0 ; j < Anz ; j++)
        c->rr->SetRecord (TableInd - j,old[j]);
      }
    if ((!done) && (ElseBeg != NULL)) {
      c->ExCuteBlock (ElseBeg,0L,EM_LOAD | EM_CHANGETOTRUE) ,
      c->ExCuteBlock (ElseBeg,0L,EM_RESET | EM_CLEAR);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    for (int i = 0 ; i < AnzPars ; i++)
      c->SetlConnection (par->Par[2 * i],par);
    c->SetlConnection (par->objvar,par);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    for (int i = 0 ; i < AnzPars ; i++)
      c->ClearlConnection (par->Par[2 * i],par);
    c->ClearlConnection (par->objvar,par);
    }
  return end;
  }

HPSTR DoDoWith (mdiChild *c,char huge *h,WORD mode)
  {
  WithParam FAR *par = (WithParam FAR *) h ;
  int AnzPars = ((par->BlockSize - sizeof(*par) + sizeof(WORD) + sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 - sizeof(DWORD) - sizeof(WORD) + sizeof(*par));
  HPSTR IfBeg   = HPSTR (&par->BlockSize) + par->BlockSize ;
  HPSTR ElseBeg = IfBeg + *(DWORD FAR *) IfBeg ;
  WORD ecommand = *(WORD FAR *) ElseBeg ;
  HPSTR end;
  ElseBeg += sizeof(WORD);
  if (ecommand == PREFIX_ELSE) {
    end = ElseBeg + *(DWORD FAR *) ElseBeg ;
    }
  else
    end = ElseBeg + sizeof(WORD) , ElseBeg = NULL ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->objvar);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    LPSTR Alias;
    if ((lpp != NULL) && (*lpp != NULL)) {
      if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
        l = LPINNERLISTDESC (*lpp)->list;
        td = LPINNERLISTDESC (*lpp)->td;
        Alias = NULL;
        }
      else {
        l = ((ForParam FAR *) (*lpp))->lst;
        td = ((ForParam FAR *) (*lpp))->td;
        Alias = ((ForParam FAR *) (*lpp))->AliasName;
        }
      }
    BOOL done = FALSE ;
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[2 * i]), c, par->Par[2 * i + 1]);
      WORD TableInd,Anz;
      DBWIN_ASSERT (GetTableDef (Alias,c,&TableInd,&Anz,par->TableNr) != NULL);
      LPDBRECORD old[10];
      for (WORD j = 0 ; j < Anz ; j++)
        old[j] = c->rr->GetRecord (TableInd - j);
      LPDBRECORD h = w.FindExtended ();
      if (h != NULL) {
        for (j = 0 ; j < Anz ; j++)
          c->rr->SetRecord (TableInd - j,(j == 0) ? h : GetCyclRecord (h,c->schd->TRef[TableInd - j - CSYSRECS]));
        c->ExCuteBlock (IfBeg,sizeof(DWORD),EM_LOAD | EM_CHANGETOTRUE) ,
        c->ExCuteBlock (IfBeg,sizeof(DWORD),EM_RESET | EM_CLEAR);
        done = TRUE ;
        }
      for (j = 0 ; j < Anz ; j++)
        c->rr->SetRecord (TableInd - j,old[j]);
      }
    if ((!done) && (ElseBeg != NULL)) {
      c->ExCuteBlock (ElseBeg,0L,EM_LOAD | EM_CHANGETOTRUE) ,
      c->ExCuteBlock (ElseBeg,0L,EM_RESET | EM_CLEAR);
      }
    par->ctrs = LPVOID (c->GetForResult ());
    }
  if (mode & EM_FIXCONNECTION) {
    for (int i = 0 ; i < AnzPars ; i++)
      c->SetlConnection (par->Par[2 * i],par);
    c->SetlConnection (par->objvar,par);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    for (int i = 0 ; i < AnzPars ; i++)
      c->ClearlConnection (par->Par[2 * i],par);
    c->ClearlConnection (par->objvar,par);
    c->SetForResult (int(par->ctrs));
    }
  return end;
  }

BOOL DoIn (mdiChild *c,LPVOID h,WORD mode)
  {
  InParam FAR *par = (InParam FAR *) (LPSTR(h) - sizeof(WORD)) ;
  int AnzPars = ((par->BlockSize - sizeof(WORD) - sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 + sizeof(DWORD) + sizeof(WORD) + sizeof(short));
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->Par[AnzPars]);
    RecordList FAR *l = NULL;
    if ((lpp != NULL) && (*lpp != NULL)) {
      if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
        l = LPINNERLISTDESC (*lpp)->list;
        }
      else {
        l = ((ForParam FAR *) (*lpp))->lst;
        }
      }
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[i]), c, par->Par[i + AnzPars + 1]);
      res = (w.FindExtended () != NULL);
//      res = (w.Find (FIND_FIRST) != NULL);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    for (int i = 0 ; i <= AnzPars ; i++)
      c->SetlConnection (par->Par[i],GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    for (int i = 0 ; i <= AnzPars ; i++)
      c->ClearlConnection (par->Par[i],GetLastOffset());
    }
  return res;
  }

HPSTR DoInsert (mdiChild *c,HPSTR h,WORD mode)
  {
  InsertParam FAR *par = (InsertParam FAR *) h ;
  int AnzPars = ((par->BlockSize - 2 * sizeof(WORD) - sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 + sizeof(DWORD) + 2 * sizeof(WORD) + sizeof(short));
  HPSTR IfBeg   = HPSTR (&par->BlockSize) + par->BlockSize ;
  HPSTR end     = IfBeg + *(DWORD FAR *) IfBeg ;
  if (mode & EM_LOAD) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->Par[2 * AnzPars]);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    ForParam FAR *fp;
    LPSTR Alias;
    if ((lpp != NULL) && (*lpp != NULL)) {
      fp = (ForParam FAR *) *lpp ;
      l = fp->lst;
      td = fp->td;
      Alias = fp->AliasName;
      }
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[2 * i]), c, par->Par[2 * i + 1]);
      WORD TableInd,Anz;
      DBWIN_ASSERT (GetTableDef (Alias,c,&TableInd,&Anz,par->TableNr) != NULL);
      LPDBRECORD old[10];
      for (WORD j = 0 ; j < Anz ; j++)
        old[j] = c->rr->GetRecord (TableInd - j);
      LPDBRECORD r = new DBRecord(td);
      c->rr->SetRecord (TableInd,r);
      for (j = 1 ; j < Anz ; j++)
        c->rr->SetRecord (TableInd - j,GetCyclRecord (r,c->schd->TRef[TableInd - j - CSYSRECS]));
      // RestoreListFnc rlf(c);  // ???
#ifdef DEBUG
//       BeforeExecution (c,mode,c->schd->fName,c->GetCmdOffset (IfBeg));
//       PushToCallStack (c,c->schd->fName,c->GetCmdOffset (IfBeg));
#endif
      c->ExCuteBlock (IfBeg,0L,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteBlock (IfBeg,0L,EM_RESET | EM_CLEAR);
#ifdef DEBUG
//       PopFromCallStack ();
#endif
      LPDBRECORD rref;
      switch (par->InsertType) {
        case INSERTTYPE_NONE :
          l->AddRecAtTail (r,NULL,TRUE);
          break ;
        case INSERTTYPE_AFTER :
          rref = w.Find (FIND_LAST);
          if (rref != NULL)
            l->AddRecBehind (r,rref,NULL,TRUE);
          else
            l->AddRecAtTail (r,NULL,TRUE);
          break ;
        case INSERTTYPE_BEFORE :
          rref = w.Find (FIND_FIRST);
          if (rref != NULL)
            l->AddRecBefore (r,rref,NULL,TRUE);
          else
            l->AddRecAtHead (r,NULL,TRUE);
          break ;
        }
      // Den neuen Datensatz noch aktiv machen
      fp->SetPrimKeyToRecord (r);
      if (fp->mp != NULL) {
        // Der Loadblock muss ausgefuehrt werden (achtung: im Orginalkontext)
        SAVEREC sr;
        if (fp->ExtraDataAtCreation != NULL) {
          fp->c->SetRecsForUpdate (sr,fp->ExtraDataAtCreation);
          }
        RestoreListFnc rlf(fp->c);
        LPDBRECORD cold = fp->c->rr->GetRecord (fp->TableInd);
        fp->c->rr->SetRecord (fp->TableInd,r);
        LPCMDCOUNT oldcnt = fp->c->_ccount->Copy ();
        fp->c->SetCount (GetCounter ((LPCTRLIST) &fp->hd->ctrs));
        fp->c->_ccount = PushBlock(fp->c->_ccount,fp->MaxRecID);
        fp->c->_ccount = PushBlock(fp->c->_ccount);

        if (fp->ExtraDataAtCreation != NULL) {
          SetExtraInfo s1(fp->c,fp->ExtraDataAtCreation);
          SetExtraInfo s(fp->c,fp->TableInd,r,fp->mp->CorrOffs());
          fp->mp->AddProc (r->GetPrimKey());
          fp->mp->ExCute (r->GetPrimKey(),EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,&s);
          fp->WriteRes (fp);
          }
        else {
          if (fp->c->IsInListFunction ()) {
            SetExtraInfo extra(fp->c,c->_ExtraData->i.keyData,fp->mp->CorrOffs());
            extra.ci->fOffs = extra.ci->cOffs;
            fp->mp->AddProc(r->GetPrimKey());
            fp->mp->ExCute (r->GetPrimKey(),EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,&extra);
            fp->WriteRes (fp);
            }
          else {
            SetExtraInfo s(fp->c,fp->TableInd,r,fp->mp->CorrOffs(),TRUE);
            fp->mp->AddProc (r->GetPrimKey());
            fp->mp->ExCute (r->GetPrimKey(),EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,&s);
            fp->WriteRes (fp);
            }
          }

        fp->c->SetCount (oldcnt);
        FreeGlobMem (oldcnt);
        fp->c->rr->SetRecord (fp->TableInd,cold);
        if (fp->ExtraDataAtCreation != NULL)
          fp->c->RestoreRecs (sr);
        }
      else
        fp->WriteRes (fp);
      for (j = 0 ; j < Anz ; j++)
        c->rr->SetRecord (TableInd - j,old[j]);
      GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    for (int i = 0 ; i < AnzPars ; i++)
      c->ClearlConnection (par->Par[2 * i],LPSTR(par)-sizeof(WORD));
    }
  return end;
  }

HPSTR DoRemove (mdiChild *c,HPSTR h,WORD mode)
  {
  RemoveParam FAR *par = (RemoveParam FAR *) h ;
  int AnzPars = ((par->BlockSize - sizeof(WORD) - sizeof(DWORD)) / sizeof(DWORD)) / 2 ;
  DBWIN_ASSERT (par->BlockSize == AnzPars * sizeof(DWORD) * 2 + sizeof(DWORD) + sizeof(WORD) + sizeof(short));
  if (mode & EM_LOAD) {
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->objvar);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    LPSTR Alias;
    ForParam FAR *fp;
    if ((lpp != NULL) && (*lpp != NULL)) {
      fp = (ForParam FAR *) *lpp ;
      l = fp->lst;
      td = fp->td;
      Alias = fp->AliasName;
      }
    if (l != NULL) {
      ListWork w(l);
      for (int i = 0 ; i < AnzPars ; i++)
        w.SetCmpData (c->ReadlData (par->Par[2 * i]), c, par->Par[2 * i + 1]);
      WORD TableInd,Anz;
      DBWIN_ASSERT (GetTableDef (Alias,c,&TableInd,&Anz,par->TableNr) != NULL);
      LPDBRECORD r = w.Find (FIND_FIRST);
      if ((r != NULL) && (fp->mp != NULL)) {
        LPDBRECORD old = fp->c->rr->GetRecord (fp->TableInd);
        SAVEREC sr;
        if (fp->ExtraDataAtCreation != NULL) {
          fp->c->SetRecsForUpdate (sr,fp->ExtraDataAtCreation);
          SetExtraInfo s1(fp->c,fp->ExtraDataAtCreation);
          fp->c->rr->SetRecord (fp->TableInd,r);
          SetExtraInfo s(fp->c,fp->TableInd,r,fp->mp->CorrOffs());
          fp->mp->ExCute (r->GetPrimKey(),EM_RESET | EM_CLEAR,&s);
          fp->c->RestoreRecs (sr);
          }
        else {
          fp->c->rr->SetRecord (fp->TableInd,r);
          SetExtraInfo s(fp->c,fp->TableInd,r,fp->mp->CorrOffs(),TRUE);
          fp->mp->ExCute (r->GetPrimKey(),EM_RESET | EM_CLEAR,&s);
          }

        fp->mp->Remove (r->GetPrimKey());
        if (fp->OutputObj != NULL) DoRemoveObjEnt (fp->OutputObj,r);
        fp->c->rr->SetRecord (fp->TableInd,old);
        OnThrowRecord (r);
        }
      else {
        if (r != NULL) {
          if (fp->OutputObj != NULL) DoRemoveObjEnt (fp->OutputObj,r);
          OnThrowRecord (r);
          }
        }
      if (r != NULL)
        l->ThrowRecord (r);
      GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
      fp->WriteRes (fp);
      }
    }
  return LPSTR(par) + sizeof(WORD) + par->BlockSize;
  }

#pragma pack(1)
struct FAR SortList_param {
  WORD parSize;
  DWORD obj;
  DWORD seg[1];
  int AnzSegs()
    { return (parSize - (sizeof(*this) - sizeof(seg[0]))) / sizeof(seg[0]) ; }
  };
#pragma pack()

BOOL SortList_base (mdiChild *c,LPVOID param,WORD mode,int dir)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SortList_param FAR *par = (SortList_param FAR *) param;
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->obj);
    RecordList FAR *l = NULL;
    if ((lpp != NULL) && (*lpp != NULL)) {
      if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
        l = LPINNERLISTDESC (*lpp)->list;
        }
      else {
        l = ((ForParam FAR *) (*lpp))->lst;
        }
      }
    DBWIN_ASSERT (par->AnzSegs() > 0) ;
    if (l != NULL) {
      int VarID[32];
      TableRef TRef[32];
      for (int i = 0 ; i < par->AnzSegs() ; i++) {
        VarID[i] = HIWORD(par->seg[i]);
        TRef[i] = c->schd->TRef[LOWORD(par->seg[i]) - CSYSRECS] ;
        }
      l->SortList (par->AnzSegs(),VarID,TRef,dir);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SortList_param FAR *par = (SortList_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(par)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SortList_param FAR *par = (SortList_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(par)-sizeof(WORD));
    }
  return FALSE ;
  }
BOOL SortList (mdiChild *c,LPVOID param,WORD mode)
  {
  return SortList_base (c,param,mode,1);
  }
BOOL SortList_neg (mdiChild *c,LPVOID param,WORD mode)
  {
  return SortList_base (c,param,mode,-1);
  }

void PrepareWithHashs ()
  {
  // parHash = new hash (513,VOIDKEY);
  }

void FreeWithHashs ()
  {
  // delete parHash ;
  }

LPDBRECORD GetRecordWithList (LPVOID list,LPDBRECORD h,mdiChild *c,WORD FAR *TableInd)
  {
  if (list != NULL) {
    ForParam FAR *p = * ((ForParam FAR * FAR *)list) ;
    if (p->lst != NULL) {
      WORD Anz;
      if (c != NULL)
        GetTableDef (p->AliasName,c,TableInd,&Anz,-1);
      if (h != NULL) return p->lst->GetNext (h);
      else           return p->lst->GetFirst ();
      }
    else return NULL ;
    }
  else return NULL ;
  }

LPDBRECORD GetRecordWithListReverse (LPVOID list,LPDBRECORD h,mdiChild *c,WORD FAR *TableInd)
  {
  if (list != NULL) {
    ForParam FAR *p = * ((ForParam FAR * FAR *)list) ;
    if (p->lst != NULL) {
      WORD Anz;
      if (c != NULL)
        GetTableDef (p->AliasName,c,TableInd,&Anz,-1);
      if (h != NULL) return p->lst->GetPrev (h);
      else           return p->lst->GetLast ();
      }
    else return NULL ;
    }
  else return NULL ;
  }

BOOL DDSIsListPtr (DBGIsListPtr FAR *d)
  {
#ifdef WIN32
  LPVOID ListPtr = LPVOID (LPSTR (d + 1) + sizeof(WORD));
#else
  LPVOID ListPtr = d->ListPtr;
#endif
  if ((GetBlockSize (ListPtr) == sizeof(ListPtrData)) && 
      (lmemcmp (((ListPtrData FAR *) ListPtr)->magic,magicdata,sizeof(magicdata)))) {
    ForParam FAR *par = (ForParam FAR *) ((ListPtrData FAR *) ListPtr)->ptr;
    if (par->lst != NULL) {
      int i = 0;
      for (LPDBRECORD h = par->lst->GetFirst () ; h != NULL ; h = par->lst->GetNext (h) )
        i ++ ;
      d->AnzRecs = i ;
      lstrcpy (d->StructName,par->AliasName);
      return TRUE ;
      }
    }
  return FALSE ;
  }

LPVOID DDSGetRecordPtr (DBGGetRecordPtr FAR *d)
  {
  LPDBRECORD res = NULL;
  BOOL IsActive = FALSE ;
#ifdef WIN32
  LPVOID ListPtr = LPVOID (LPSTR (d + 1) + sizeof(WORD));
#else
  LPVOID ListPtr = d->ListPtr;
#endif
  if ((GetBlockSize (ListPtr) == sizeof(ListPtrData)) && 
      (lmemcmp (((ListPtrData FAR *) ListPtr)->magic,magicdata,sizeof(magicdata)))) {
    ForParam FAR *par = (ForParam FAR *) ((ListPtrData FAR *) ListPtr)->ptr;
    if (par->lst != NULL) {
      int i = 0;
      for (LPDBRECORD h = par->lst->GetFirst () ; h != NULL ; h = par->lst->GetNext (h) ) {
        if (i == d->Index) {
          res = h ; 
          break ;
          }
        i ++ ;
        }
      if (h != NULL)
        d->IsActive = (h == par->c->rr->GetRecord (par->TableInd));
      }
    }
  return res ;
  }

#pragma pack(1)
struct ClearRecHash_param {
  WORD parSize;
  DWORD list;
  DWORD recPtr;
  };
#pragma pack()
BOOL ClearRecHash (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ClearRecHash_param FAR *par = (ClearRecHash_param FAR *) param;
    LPVOID FAR *lpo = (LPVOID FAR *) c->ReadlData (par->list);
    LPDBRECORD FAR * rec = (LPDBRECORD FAR *) c->ReadlData (par->recPtr);
    if ((lpo != NULL) && (rec != NULL) && (*rec != NULL)) {
      RecordList FAR *list = GetListFromForParam_noset (*lpo);
      if (list != NULL)
        list->RemoveRecFromHashs (*rec);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ClearRecHash_param FAR *par = (ClearRecHash_param FAR *) param;
    c->ClearlConnection (par->recPtr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetRecHash (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ClearRecHash_param FAR *par = (ClearRecHash_param FAR *) param;
    LPVOID FAR *lpo = (LPVOID FAR *) c->ReadlData (par->list);
    LPDBRECORD FAR * rec = (LPDBRECORD FAR *) c->ReadlData (par->recPtr);
    if ((lpo != NULL) && (rec != NULL) && (*rec != NULL)) {
      RecordList FAR *list = GetListFromForParam_noset (*lpo);
      if (list != NULL)
        list->ExtConnections (*rec,TRUE);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ClearRecHash_param FAR *par = (ClearRecHash_param FAR *) param;
    c->ClearlConnection (par->recPtr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// Analysieren eines Listenzeigers
//--------------------------------------------------
void GetListData (LPVOID FAR *lpp,RecordList FAR * &l,LPTABLEDEF &td,LPSTR &Alias)
  {
  if ((lpp != NULL) && (*lpp != NULL)) {
    if (GetBlockSize (*lpp) == sizeof(InnerListDesc)) {
      l = LPINNERLISTDESC (*lpp)->list;
      td = LPINNERLISTDESC (*lpp)->td;
      Alias = NULL ;
      }
    else {
      l = ((ForParam FAR *) (*lpp))->lst;
      td = ((ForParam FAR *) (*lpp))->td;
      Alias = ((ForParam FAR *) (*lpp))->AliasName;
      }
    }
  }
