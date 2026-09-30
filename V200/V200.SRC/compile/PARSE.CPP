// $Header:   P:/marille/clinicum/compile/rev/parse.cpv   1.62   18 Aug 2000 17:01:22   Wolfgang  $
// $Log:   P:/marille/clinicum/compile/rev/parse.cpv  $
// 
//    Rev 1.62   18 Aug 2000 17:01:22   Wolfgang
// 1.) dontVarCheck in setvarname nur auf FALSE, wenn nicht in Funktionskopf,
//     damit Warnungen auf unqualifizierte Variablen funktionieren
//     (siehe LEXSCAN.myCheckVar)
// 
//    Rev 1.61   09 May 2000 15:40:22   Wolfgang
// 1.) COUNTVAR in PushParameter eingebaut.
// 
//    Rev 1.60   16 Feb 2000 15:03:06   Wolfgang
// 1.) Neue FDEF-Syntax.
// 
//    Rev 1.59   26 Apr 1999 18:10:18   Wolfgang
// 1.) TryToGetEntry setzt Error auf ERRORINIMPORTED falls Modul Kompilieren
//     fehlschlaegt.
// 2.) TryToGetEntry macht nur bei gelungenem Modul Kompilieren 
//     CreateScriptContent.
// 
//    Rev 1.58   22 Apr 1999 10:24:26   Hannes
// TOFLAG
// 
//    Rev 1.57   26 Mar 1999 18:15:22   Wolfgang
// 1.) VirtualModule eingebaut.
// 2.) GetIncludeFileName vom Source-Pfad.
// 3.) FTYPE_VIRTUAL verarbeiten.
// 
//    Rev 1.56   28 Jan 1999 12:20:38   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.55   19 Aug 1998 20:54:54   Hannes
// NULL Als Parameter von normalen Funktionen
// 
//    Rev 1.54   04 Aug 1998 17:47:14   Hannes
// Timestamp
// 
//    Rev 1.53   26 Jan 1998 19:59:38   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.52   13 Jan 1998 19:30:02   Hannes
// DbSelCond -> DoReverse vorbelegt
// 
//    Rev 1.51   05 Jan 1998 07:49:20   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.50   15 Dec 1997 17:57:44   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.49   06 Nov 1997 19:25:42   Hannes
// Verbesserung der Updatenummer
// 
//    Rev 1.48   22 Sep 1997 20:02:14   Hannes
// Variablen ohne Prefix als lokale Variablen erlaubt
// 
//    Rev 1.47   22 Aug 1997 15:12:42   Hannes
// Fehlerkorrektur / Erweiterung der Speicherfreigabe
// 
//    Rev 1.46   22 Aug 1997 12:01:52   Hannes
// TwoDim: GetGlobalMem ausgebaut
// 
//    Rev 1.45   19 Aug 1997 17:07:54   Martin
// Lookupfehler bei Segmentspruengen im ExpressionCompiler
// 
//    Rev 1.44   22 Jul 1997 21:07:48   Hannes
// 
//    Rev 1.43   14 Jul 1997 17:06:18   Hannes
// 
//    Rev 1.42   08 Jul 1997 12:00:20   Hannes
// 
//    Rev 1.41   16 Jun 1997 07:47:10   Hannes
// TOOBJ 
// 
//    Rev 1.40   09 Jun 1997 16:48:16   Hannes
// 
//    Rev 1.39   27 May 1997 11:21:02   Hannes
// Private Strukturen im Scriptkompilat, L. als Expression
// 
//    Rev 1.38   05 May 1997 10:32:56   Hannes
// 
//    Rev 1.37   14 Mar 1997 12:36:44   gerhold
// 32 Bit .. GlobalLock + sizeof(DWORD)
// 
//    Rev 1.36   13 Mar 1997 19:06:38   Hannes
// Blobs als lokale Variablen
// 
//    Rev 1.35   19 Feb 1997 12:04:26   Hannes
// Scriptfunktionen
// 
//    Rev 1.34   12 Dec 1996 15:04:46   HANNES
// 
//    Rev 1.33   04 Dec 1996 09:10:04   HANNES
// Die Breakhistory in einen Stack
// 
//    Rev 1.32   26 Nov 1996 21:04:02   HANNES
// 
//    Rev 1.31   26 Nov 1996 07:56:50   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.30   08 Nov 1996 13:24:48   HANNES
// Einbau von QLong
// 
//    Rev 1.29   30 Oct 1996 08:41:58   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.28   21 Oct 1996 18:50:56   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.27   17 Jun 1996 15:28:10   HANNES
// Einfuehrung von BLOBS
// 
//    Rev 1.26   04 Feb 1996 15:30:32   gerhold
// Teile aus COMPILE in DDSMEM
// 
//    Rev 1.25   02 Feb 1996 10:41:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.24   02 Jan 1996 22:14:24   HANNES
// push_constflag
// 
//    Rev 1.23   09 Nov 1995 19:43:00   HANNES
// Geschachtelte ForSchleifen
// 
//    Rev 1.22   25 Sep 1995 20:49:04   HANNES
// 
//    Rev 1.21   15 Sep 1995 20:42:20   HANNES
// Syntaxerkennung verbessert
// 
//    Rev 1.20   14 Sep 1995 09:57:12   HANNES
// 
//    Rev 1.19   24 Aug 1995 00:13:36   HANNES
// 
//    Rev 1.18   02 Aug 1995 09:59:24   HANNES
// Prioritaetenhandling, verb. Fehlerabfrage, verb. Kapselung
// 
//    Rev 1.17   11 Jul 1995 12:44:18   HANNES
// Statische Daten in die Klasse
// 
//    Rev 1.16   27 Jun 1995 13:55:40   HANNES
// Fehler bei Expressions in Aufzaehlungen
// 
//    Rev 1.15   09 Jun 1995 00:22:26   HANNES
// Umbau der Konstanten auf normale Tabelle
// 
//    Rev 1.14   15 May 1995 08:22:58   HANNES
// structs im normalen Script
// 
//    Rev 1.13   28 Apr 1995 17:17:14   HANNES
// Verbessertes Konstantenhandling fuer mappings
// 
//    Rev 1.12   31 Mar 1995 18:24:04   HANNES
// 
//    Rev 1.11   20 Mar 1995 12:08:24   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.10   08 Mar 1995 09:11:40   HANNES
// Forschleifen u.a.
// 
//    Rev 1.9   24 Feb 1995 11:10:40   HANNES
// 
//    Rev 1.8   16 Feb 1995 12:43:58   HANNES
// 
//    Rev 1.7   09 Jan 1995 12:07:00   HANNES
// Debugger eingebaut
// 
//    Rev 1.6   08 Dec 1994 22:04:08   HANNES
// 
//    Rev 1.5   05 Dec 1994 17:37:18   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.4   08 Nov 1994 12:38:58   HANNES
// Abort eingebaut
// 
//    Rev 1.3   30 Aug 1994 13:01:14   HANNES
// PutConst fuer strfields ... sizeof(WORD)
// 
//    Rev 1.2   05 Aug 1994 19:32:22   HANNES
// Time eingebaut
// 
//    Rev 1.1   17 Jul 1994 14:36:20   HANNES
// TranformTableId auch bei enums..
// 
//    Rev 1.0   24 Jun 1994 16:30:26   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.26   04 Feb 1994 16:52:56   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.25   04 Jan 1994 17:28:48   HANNES
// RECALLKEY als Datentyp
// 
//    Rev 1.24   09 Dec 1993 15:09:52   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.23   16 Nov 1993 04:26:40   HANNES
// Verallgemeinerung der Benutzerdaten
// 
//    Rev 1.22   27 Oct 1993 20:00:10   HANNES
// dds.hpp Umstellung
// 
//    Rev 1.21   08 Oct 1993 17:55:32   HANNES
// BenData
// 
//    Rev 1.20   24 Sep 1993 22:45:26   HANNES
// Verkettung der Help - Zeiger
// 
//    Rev 1.19   22 Sep 1993 09:24:06   HANNES
// Version nach St. Poelten
// 
//    Rev 1.18   05 Sep 1993 22:06:54   HANNES
// 
//    Rev 1.17   18 Aug 1993 10:44:18   HANNES
// Markierung des Else
// 
//    Rev 1.16   22 Jul 1993 20:59:36   HANNES
// Kommandosortierung
// 
//    Rev 1.15   20 Jul 1993 12:37:00   HANNES
// Icons fuer die Dokumente
// 
//    Rev 1.14   05 Jul 1993 14:53:48   HANNES
// Bitmaps, Commondata
// 
//    Rev 1.13   07 Jun 1993 15:12:34   HANNES
// Bufferhandling
// 
//    Rev 1.12   24 May 1993 14:24:00   HANNES
// Expressions
// 
//    Rev 1.9   05 Apr 1993 10:39:56   NORBERT
// Fehlerkorrektur (GetFuncCopy...)
// 
//    Rev 1.8   02 Apr 1993 18:09:30   HANNES
// ?
// 
//    Rev 1.7   08 Mar 1993 14:19:52   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.6   22 Feb 1993 17:29:56   HANNES
// Einbau von Arraydefinitionen
// 
//    Rev 1.5   29 Jan 1993 20:24:42   HANNES
// Dokumenttyp Simulation (=VTO)
// 
//    Rev 1.4   29 Jan 1993 19:07:56   HANNES
// Implementierung des Datentyp DCDATA
// 
//    Rev 1.3   18 Jan 1993 16:59:06   HANNES
// Neue Datentypen: long und obj
// 
//    Rev 1.2   13 Jan 1993 18:55:16   HANNES
// Verwaltung mehrer Datensaetze in einem Programm
// 
//    Rev 1.1   10 Jan 1993 15:26:36   HANNES
// Verbesserter Syntax - Check...
// 
//    Rev 1.0   02 Dec 1992 16:17:06   HANNES
// Initial revision.

// #define TEST

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#define JUST_EM
#include "dds.hpp"
#include "compile.hpp"
#include "express.hpp"
#include "syntax.hpp"
#include "twodim.hpp"
#include "dds.h"
#define MODULENUM 69
#include "winass.hpp"

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

BOOL BlockIsActive;
/*-------------------------------------------------*/
/*      Code - Generator Funktionen:               */
/*      Da bei dem Aufruf ueber Zeiger die         */
/*         Instanz verloren geht, wird der Zeiger  */
/*         _actcmpl zur Referenzierung der         */
/*         Instanz verwendet                       */
/*-------------------------------------------------*/
void marknumana ()
  {
  WIN_ASSERT(FALSE);
  }

void markgrana ()
  {
  WIN_ASSERT(FALSE);
  }

void markform ()
  {
  _actcmpl->Type = CHWND_FORM;
  }

void marktracing ()
  {
  _actcmpl->Type = CHWND_TRACING;
  }

void markvto ()
  {
  _actcmpl->Type = CHWND_VTO;
  }

void marktext ()
  {
  WIN_ASSERT(FALSE);
  }

void markenter ()
  {
  WIN_ASSERT(FALSE);
  }

void markimage ()
  {
  WIN_ASSERT(FALSE);
  }

void strore_fullname ()
  {
  char FAR *txt = (LPSTR)GlobalLock (_actcmpl->hPars0);
  lstrncpy (_actcmpl->fullname,txt+sizeof(WORD),sizeof (_actcmpl->fullname));
  GlobalUnlock (_actcmpl->hPars0);
  }

void inclevel ()
  {
  _actcmpl->inclevel();
  }
void VarCheckOff ()
  {
  _actcmpl->dontVarCheck = TRUE ;
  }
void VarCheckOff_InFunction ()
  {
  if (_actcmpl->InFunction)
    _actcmpl->dontVarCheckGlobals = TRUE ;
  }
void UnqualifiedOff ()
  {
  _actcmpl->dontUnqualifiedCheck = TRUE ;
  }
void VarCheckOff_InFunction_UnqualifiedOff ()
  {
  VarCheckOff_InFunction ();
  UnqualifiedOff ();
  }
extern void UseTable ();
void VarCheckOn ()
  {
  _actcmpl->dontVarCheck = FALSE ;
  _actcmpl->dontVarCheckGlobals = FALSE ;
  }
void inclevel_CheckOn ()
  {
  _actcmpl->inclevel();
  VarCheckOn ();
  }
void PushBreakAllowed()
  {
  _actcmpl->allowBreak_old[_actcmpl->bstack ++] = _actcmpl->allowBreak ;
  }
BOOL PopBreakAllowed()
  {
  return _actcmpl->allowBreak_old[-- _actcmpl->bstack] ;
  }
void inclevel_breakallowed ()
  {
  _actcmpl->inclevel();
  PushBreakAllowed();
  _actcmpl->allowBreak = TRUE;
  }
void startcond ()
  {
  inclevel ();
  _actcmpl->MarkCond();
  }

void pushparameter (BOOL FAR * freeSet, BOOL setFree)
  {
  if ((freeSet == NULL) || !(*freeSet)) {
    pardsc dsc ;
    if (setFree) {
      dsc.par_kind = PAR_FREE ;
      if (freeSet != NULL)
        *freeSet = TRUE ;
      }
    else {
      switch (_actcmpl->scv.v.k_ident) {
        case PARSCALEVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_SCALE ;
          break ;
        case PARFLAGVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_FLAG ;
          break ;
        case PARSTRARR :
        case COUNTVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_STRARR ;
          break ;
        case PARCONTVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_CONT ;
          break ;
        case PARPOINTVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_POINT ;
          break ;
        case PARDECVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_DEC ;
          break ;
        case PARINTVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_LONG ;
          break ;
        case PARSTRVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_STR ;
          break ;
        case PARSTRING :
          dsc.par_kind = PAR_STR ;
          break ;
        case PARINT :
          dsc.par_kind = PAR_LONG ;
          break ;
        case PARDEC :
          dsc.par_kind = PAR_DEC ;
          break ;
        case PARPICTVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_PICTURE ;
          break ;
        case PARBITMAPVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_BITMAP ;
          break ;
        case PARDATEVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_DATE ;
          break ;
        case PARBLOBVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_BLOB ;
          break ;
        case PARTIMEVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_TIME ;
          break ;
        case PARPROCVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_PROC ;
          break;
        case PARIMAGE :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_IMAGE ;
          break ;
        case PARDWORDVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_LONG ;
          break ;
        case QLONGVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_QLONG ;
          break ;
        case PAROBJVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_OBJ ;
          break ;
        case PARDATETIMEVAR :
          dsc.par_kind = PAR_VAR ;
          dsc.Extra = VAR_DATETIME ;
          break ;
        case KWVOID :  // void: eigentlich nur ein Parameter beliebigen Typs, aber derzeit aequivalent free
        case FREEPAR : // free: beliebige folgende Parameter
          dsc.par_kind = PAR_FREE ;
          if (freeSet != NULL)
            *freeSet = TRUE ;
          break ;
        }
      }
    _actcmpl->pushData (&dsc,sizeof(dsc));
    }
  };

void pushpartype ()
  {
  pushparameter (NULL, FALSE);
  };

void startprototype (void)
  {
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isfdef = FALSE;
  }

void startfdef (void)
  {
  inclevel ();
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isfdef = TRUE;
  }

void endfdef (void)
  {
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isfdef = FALSE;
  }

void startparams (void)
  {
  ((FncCompiler FAR *) _actcmpl)->actParStatus.countPart = 0;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional = FALSE;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptionalInCount = FALSE;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isFree = FALSE;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.wasOptional = FALSE;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.wasFree = FALSE;
  ((FncCompiler FAR *) _actcmpl)->actParStatus.freeSet = FALSE;
  }

void pushprototypepar ()
  {
  BOOL setFree = ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional || 
                 ((FncCompiler FAR *) _actcmpl)->actParStatus.isFree || 
                 (((FncCompiler FAR *) _actcmpl)->actParStatus.countPart > 1) ||
                 (_actcmpl->scv.v.k_ident == FREEPAR);
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.isfdef)
    pushparameter (&((FncCompiler FAR *) _actcmpl)->actParStatus.freeSet, setFree);
  else {
    if (!((FncCompiler FAR *) _actcmpl)->actParStatus.freeSet)
      if (setFree) {
        SetExpArgT (VAR_FREEPAR);
        ((FncCompiler FAR *) _actcmpl)->actParStatus.freeSet = TRUE;
        }
      else
        SetExpArg ();
    }
  };

void startparfree (void)
  {
  if ((((FncCompiler FAR *) _actcmpl)->actParStatus.countPart == 0) && 
      (((FncCompiler FAR *) _actcmpl)->actParStatus.wasFree)) {
    // bereits freier Parameter gewesen
    _actcmpl->wError = DOUBLEFREEPARAM ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.isFree) {
    // Fehler bereits in freiem Parameter
    _actcmpl->wError = RECURSIVEPARAM ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.wasOptional && 
           !((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional) {
    // Fehler fixer Parameter nach optionalem
    _actcmpl->wError = PARAMOUTOFSEQUENCE ;
    }
  else
    ((FncCompiler FAR *) _actcmpl)->actParStatus.isFree = TRUE;
  }
void endparfree (void)
  {
  ((FncCompiler FAR *) _actcmpl)->actParStatus.isFree = FALSE;
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.countPart == 0) {
    ((FncCompiler FAR *) _actcmpl)->actParStatus.wasFree = TRUE;
    }
  }

extern void setopallowed ();
void startparcnt (void)
  {
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.wasFree) {
    // Fehler nach freiem kein count
    _actcmpl->wError = PARAMOUTOFSEQUENCE ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.isFree) {
    // Fehler in freiem kein count
    _actcmpl->wError = RECURSIVEPARAM ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.countPart != 0) {
    // Fehler bereits in Count Parameter
    _actcmpl->wError = RECURSIVEPARAM ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.wasOptional && 
           !((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional) {
    // Fehler fixer Parameter nach optionalem
    _actcmpl->wError = PARAMOUTOFSEQUENCE ;
    }
  else {
    ((FncCompiler FAR *) _actcmpl)->actParStatus.countPart = 1;
    pushpartype();
    setopallowed();
    }
  }
void defparcnt (void)
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  if (lstrcmp(Name,"*") == 0) {
    ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptionalInCount = FALSE;
    ((FncCompiler FAR *) _actcmpl)->actParStatus.countPart = 2;
    }
  else
    _actcmpl->wError = SYNTAX_ERROR ;
  }
void endparcnt (void)
  {
  ((FncCompiler FAR *) _actcmpl)->actParStatus.countPart = 0;
  }

void startparopt (void)
  {
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.wasFree) {
    // Fehler nach freiem kein optionaler
    _actcmpl->wError = PARAMOUTOFSEQUENCE ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.isFree) {
    // Fehler in freiem kein optionaler
    _actcmpl->wError = RECURSIVEPARAM ;
    }
  else if (((FncCompiler FAR *) _actcmpl)->actParStatus.countPart == 0) {
    if (((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional) {
      // Fehler bereits in optionalem Parameter
      _actcmpl->wError = RECURSIVEPARAM ;
      }
    else
      ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional = TRUE;
    }
  else {
    if (((FncCompiler FAR *) _actcmpl)->actParStatus.isOptionalInCount) {
      // Fehler bereits in optionalem Parameter innerhalb von Count
      _actcmpl->wError = RECURSIVEPARAM ;
      }
    else
      ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptionalInCount = TRUE;
    }
  }
void endparopt (void)
  {
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.countPart == 0) {
    ((FncCompiler FAR *) _actcmpl)->actParStatus.wasOptional = TRUE;
    ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional = FALSE;
    }
  else
    ((FncCompiler FAR *) _actcmpl)->actParStatus.isOptionalInCount = FALSE;
  }

void checkparfix (void)
  {
  if (((FncCompiler FAR *) _actcmpl)->actParStatus.wasOptional && 
       !((FncCompiler FAR *) _actcmpl)->actParStatus.isOptional) {
    // Fehler fixer Parameter nach optionalem
    _actcmpl->wError = PARAMOUTOFSEQUENCE ;
    }
  }

void setdescitemname (void)      {}
void setdescitemstring (void)    {}
void enddescitem (void)          {}
void setparflags (void)          {}
void setpardescname (void)       {}
void setpardescstring (void)     {}
void endpardesc (void)           {}
void setdescas (void)            {}
void setresultdescstring (void)  {}

void storefncnumber ()
  {
  _actcmpl->lstFuncNumber = WORD (_actcmpl->scv.v.int_val) ;
  }

void setfunchash ()
  {
  hash *h = _actcmpl->FixFcHash();
  char FAR *fname = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level-1]);
  char FAR *parbuffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  DWORD size = *(DWORD FAR *) parbuffer ;
  // Erzeugen der funcdef - Struktur
  funcdef temp;
  temp.ExtraCount = WORD (_actcmpl->scv.v.int_val) ;
  temp.funcId = _actcmpl->lstFuncNumber ;
  temp.parCount = (WORD(size) - sizeof (funcdef) - sizeof (DWORD)) / sizeof (pardsc);
  // diese Struktur in den Codebuffer kopieren (in setfuncname ist
  // dafuer Platz gemacht worden).
  lmemcpy (parbuffer+sizeof (DWORD),&temp,sizeof (temp));

  // Einordenen der Daten in die Hash - Tabelle
  h->SetData (fname+sizeof (DWORD),parbuffer+sizeof (DWORD),int (size) - sizeof (DWORD));

  // Codebuffer wieder Freigeben
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level-1]);
  _actcmpl->Clear();
  _actcmpl->Clear();
  // fertig
  _actcmpl->ReleaseFcHash();
  }

void setfuncname ()
  {
  _actcmpl->pushPars0();
  _actcmpl->inclevel();                 // Die Parameterbeschreibung geht
                                        // einen Buffer hoeher
  funcdef dummy ;
  _actcmpl->pushData(&dummy,sizeof (dummy)); // eine Stufe Hoeher Platz machen 
                                            // fuer die funcdef
  }

void setdatabasenumber ()
  {
  inclevel ();
  struct full_vardef temp ;
  _actcmpl->lastdatabasenumber = _actcmpl->scv.v.k_ident;

  if (_actcmpl->InFunction) {
    switch (_actcmpl->scv.v.k_ident) {
      case DTLOCAL :
        temp.vd.DBNummer = DYNLOCALDATA ;
        break ;
      case DTHELP :
        temp.vd.DBNummer = STATICLOCALDATA ;
        break ;
      }
    }
  else {
    switch (_actcmpl->scv.v.k_ident) {
      case DTLOCAL :
        temp.vd.DBNummer = 0 ;
        break ;
      case DTHELP :
        temp.vd.DBNummer = HELPDATA ;
        break ;
      }
    }
  _actcmpl->pushData (&temp,sizeof (temp));
  _actcmpl->setdatabasenumberDone = TRUE ;
  }

void VarCheckOn_UseTable ()
  {
  UseTable ();
  _actcmpl->dontVarCheck = FALSE ;
  _actcmpl->dontVarCheckGlobals = FALSE ;
  }
BYTE lastvarTypeSet;
extern void SetExpArgT (BYTE t);
WORD GetActVarType ()
  {
  switch (_actcmpl->scv.v.k_ident) {
    case PARINT :
      return VAR_LONG ;
      break ;
    case PARDEC :
      return VAR_DEC ;
      break ;
    case PARSTRING :
      return VAR_STR ;
      break ;
    case PARPOINT :
      return VAR_POINT ;
      break ;
    case PARDWORD :
      return VAR_LONG ;
      break ;
    case QLONG :
      return VAR_QLONG ;
      break ;
    case PAROBJ :
      return VAR_OBJ ;
      break ;
    case PARCONT :
      return VAR_CONT ;
      break ;
    case VARSTRARR :
      return VAR_STRARR ;
      break ;
    case PARFLAG :
      return VAR_FLAG ;
      break ;
    case PARSCALE :
      return VAR_SCALE ;
      break ;
    case PARPICTURE :
      return VAR_PICTURE ;
      break ;
    case PARBITMAP :
      return VAR_BITMAP ;
      break ;
    case PARDATE :
      return VAR_DATE ;
      break ;
    case PARBLOB :
      return VAR_BLOB ;
      break ;
    case PARTIME :
      return VAR_TIME ;
      break ;
    case PARDATETIME :
      return VAR_DATETIME ;
      break ;
    case VARIMAGE :
      return VAR_IMAGE ;
      break ;
    }
  return 0xFFFF;
  }

void setvartype ()
  {
  if (!_actcmpl->setdatabasenumberDone) {
    WORD oldIdent = _actcmpl->scv.v.k_ident;
    _actcmpl->scv.v.k_ident = DTLOCAL;
    setdatabasenumber ();
    _actcmpl->scv.v.k_ident = oldIdent;
    }
  _actcmpl->setdatabasenumberDone = FALSE ;
  full_vardef FAR *fvd = (full_vardef FAR *) 
        ((LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]) + sizeof (DWORD)) ;

  _actcmpl->lastvartype = _actcmpl->scv.v.k_ident;
  fvd->vartype = BYTE(GetActVarType()) ;

  lastvarTypeSet = fvd->vartype;
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  if (_actcmpl->IsInFuncDefinition) {
    SetExpArgT (lastvarTypeSet);
    _actcmpl->AnzFuncPars += 1 ;
    }
  }

void setvarname ();
void setnextvar ()
  {
  int oldident = _actcmpl->scv.v.k_ident ;
  _actcmpl->scv.v.k_ident = _actcmpl->lastdatabasenumber ;
  setdatabasenumber ();
  _actcmpl->scv.v.k_ident = _actcmpl->lastvartype ;
  setvartype ();
  _actcmpl->scv.v.k_ident = oldident ;
  setvarname ();
  }

void inc2level ()
  {
  _actcmpl->level += 2 ;
  }

void pushpars0 () 
  {
  _actcmpl->pushPars0 ();
  }

void dec2level ()
  {
  _actcmpl->level -= 2 ;  // Buffer 2 darueber bleibt erhalten
                          // 1 darueber wird der Variablenname kommen
  }

extern LPSTR TableForAlias (LPSTR AliasName,int FAR *TableNr);
extern int FindID_Version (WORD TableID,WORD Version);
int GetTnr ()
  {
  LPSTR TableName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr;
  if (TableForAlias (TableName,&tnr) == NULL) {
    WORD rVersion = GetVersionFrom (TableName);
    WORD Version;
    BOOL found;
    WORD TableID = GetTableAdmin()->GetTableID(NULL,TableName,&found,&Version);
    if (found) {
      if (rVersion != 0xFFFF)
        Version = rVersion;
      }
    else {
      char privateName[64];
      lstrcpy (privateName,_actcmpl->actFPrefix);
      lstrcat (privateName,TableName);
      TableID = GetTableAdmin()->GetTableID(NULL,privateName,&found,&Version);
      }
    if ((found) && (_actcmpl->IsTableUsed(TableID,Version)))
      tnr = FindID_Version (TableID,Version);
    else
      tnr = -1 ;
    }
  if (tnr < 0)
    _actcmpl->wError = TABLENOTDEFINED ;
  GlobalUnlock (_actcmpl->hPars0);
  return tnr;
  }
void PushTableInd ()
  {
  _actcmpl->TablesToReuse [++ _actcmpl->AnzTablesToReuse] = WORD(GetTnr());
  }

void setvarname () 
  {
  inclevel ();
  if (!_actcmpl->IsInFuncDefinition) {
    _actcmpl->AnzTablesToReuse = 0 ;
    _actcmpl->dontVarCheck = FALSE;
    _actcmpl->dontVarCheckGlobals = FALSE ;
    }
  _actcmpl->pushPars0 ();
  _actcmpl->dontUnqualifiedCheck = FALSE ;
  }

void setdbldef ()
  {
  _actcmpl->wError = VARALREADYDEFINED ;
  }

static char nullchar = '\0' ;                    // Abschluss mit Doppelnull

void setvardim ()
  {
  _actcmpl->vardim = WORD (_actcmpl->scv.v.int_val) ;
  if ((_actcmpl->edp != NULL) && (_actcmpl->InEdit)) {
    // Im Edit - Bereich darf nur ein einziges Obj - Arr mit dem
    // Name frmed definiert sein
    char FAR *name = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]) + sizeof (DWORD) ;
    if (lstrcmp (name,OBJARRNAME) != 0)
      _actcmpl->wError = EDERROR;
    _actcmpl->edp->AnzObjs = _actcmpl->vardim;
    }
  }

DLLExport void _export WINAPI ScriptCompiler::PushToVarTable (LPSTR name,full_vardef FAR *fvd)
  {
  if (edp != NULL) {
    int ind;
    switch (fvd->vartype) {
      case VAR_DWORD :
        ind = FE_LONGVAR ;
        break ;
      case VAR_DEC :
        ind = FE_DECVAR ;
        break ;
      case VAR_STR :
        ind = FE_STRINGVAR ;
        break ;
      case VAR_STRARR :
        ind = FE_STRINGLISTVAR ;
        break ;
      case VAR_FLAG :
        ind = FE_FLAGVAR ;
        break ;
      case VAR_EDDEF :
        ind = FE_DEFSTR ;
        break ;
      case VAR_DATE :
        ind = FE_DATEVAR ;
        break ;
      case VAR_PICTURE :
        ind = FE_PICTVAR ;
        break ;
      case VAR_DATETIME :
        ind = FE_DATETIME ;
        break ;
      default :
        ind = -1;
      }
    if (ind >= 0) {
      VarNamSeg FAR *vs;
      if (edp->hGVarNam[ind] == 0) {
        edp->hGVarNam[ind] = GlobalAlloc (GHND,2 * sizeof(WORD));
        vs = (VarNamSeg FAR *) GlobalLock (edp->hGVarNam[ind]);
        vs->SegSize = 2 * sizeof(WORD);
        vs->AnzStrs = 0;
        }
      else
        vs = (VarNamSeg FAR *) GlobalLock (edp->hGVarNam[ind]);
      WORD oldsize = vs->SegSize;
      WORD newsize = lstrlen (name) + sizeof(VarNam);
      GlobalUnlock (edp->hGVarNam[ind]);
      edp->hGVarNam[ind] = GlobalReAlloc (edp->hGVarNam[ind],oldsize + newsize,GMEM_ZEROINIT);
      vs = (VarNamSeg FAR *) GlobalLock (edp->hGVarNam[ind]);
      VarNam FAR *vn = (VarNam FAR *) (LPSTR (vs) + oldsize);
      vn->StrLen = lstrlen (name);
      vn->Rec = fvd->vd.DBNummer;
      vn->Id  = fvd->vd.Ident;
      lstrcpy (vn->Txt,name);
      vs->SegSize += newsize;
      vs->AnzStrs += 1;
      GlobalUnlock (edp->hGVarNam[ind]);
      }
    }
  }

static full_vardef lastfvd;
void ScriptCompiler::DefVar (LPSTR name,BOOL isexpression,WORD Ident)
  {
  full_vardef FAR *fvd = (full_vardef FAR *)
        ((LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level-1]) + sizeof (DWORD)) ;
  fvd->vd.Ident = Ident;
  fvd->TableNr = -1;
  fvd->isdynamic = FALSE ;
  fvd->isexpression = isexpression ;
  fvd->doubleDefined = FALSE ;
  lastfvd = *fvd;
  PushToVarTable (name,fvd);      // Fuer den Formulareditor
  hash *h;
  if ((fvd->vd.DBNummer == DYNLOCALDATA) || (fvd->vd.DBNummer == STATICLOCALDATA))
    h = _actcmpl->FixLocals ();
  else
    h = _actcmpl->FixVrHash ();
  if (!h->SetData (name,fvd,sizeof (full_vardef))) {
    full_vardef FAR *x = (full_vardef FAR *) h->GetData (name);
    lmemcpy (x,fvd,sizeof(*fvd));
    // _actcmpl->wError = VARALREADYDEFINED ;
    }
  }

#define MAXPARS 64
static char inlinename [128];
static int anzinlinepars ;
static pardsc inlinefncpar [MAXPARS];
static enumheader actenum;

void storeenum (void);
void setfreevarhash ()
  {
  // in level steht der name, in level - 1 die Struktur, in der noch
  // der Identifier eingetragen werden muss, in level + 1 stehen Daten,
  // die in die Datenbank muessen
  full_vardef FAR *fvd = (full_vardef FAR *)
        ((LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level-1]) + sizeof (DWORD)) ;
  LPSTR name = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]) + sizeof (DWORD) ;
  if (_actcmpl->vardim == 0) {
    WORD nId ;
    switch (fvd->vd.DBNummer) {
      case HELPDATA :
        nId = _actcmpl->ActFreeHVar ++ ;
        break ;
      case STATICLOCALDATA :
        nId = _actcmpl->LocalHVarCount ++;
        break ;
      case DYNLOCALDATA :
        nId = _actcmpl->LocalVarCount ++;
        break ;
      default :
        nId = _actcmpl->ActFreeVar ++ ;
      }
    _actcmpl->DefVar (name,FALSE,nId);
    }
  else {
    char arrname[128];
    arrname[0] = arrname[1] = '_';
    arrname[2] = '\0';
    lstrcat (arrname,name);     // In die Variablentabelle wird __name0 .. 
                                // geschrieven
    actenum.AnzVars = 0;
    // Platz schaffen fuer die enum struktur
    _actcmpl->level++;
    _actcmpl->pushData (&actenum,sizeof(actenum));
    _actcmpl->level--;
    for (int i = 0 ; i < int (_actcmpl->vardim) ; i++) {
      char arrelename[128];
      char number[5];
      lstrcpy (arrelename,arrname);
      wsprintf (number,"%d",i);
      lstrcat (arrelename,number);
      WORD nId ;
      if (fvd->vd.DBNummer != HELPDATA)
        nId = _actcmpl->ActFreeVar ;
      else
        nId = _actcmpl->ActFreeHVar ;
      _actcmpl->DefVar (arrelename,FALSE,nId);
      if (fvd->vd.DBNummer != HELPDATA) _actcmpl->ActFreeVar ++;
      else                              _actcmpl->ActFreeHVar ++;

      // Diese Variable in codebuffer[level+1] fuer den spaeteren enum ablegen
      _actcmpl->level++;
      enumvar ev;
      ev.par_kind = PAR_VAR ;
      lmemcpy (&ev.x.fvd,fvd,sizeof(full_vardef));  // fvd wurde von DefVar
                                                    // gesetzt !!
      _actcmpl->pushData (&ev,sizeof(ev));
      actenum.AnzVars ++ ;
      _actcmpl->level--;
      }
    lstrcpy (inlinename,name);

    _actcmpl->level++;
    actenum.pd.par_kind = PAR_VAR ;
    actenum.pd.Extra = fvd->vartype;
    storeenum ();   // Storeenum wird mit dem neuen Buffer aufraeumen
    }
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level-1]);
  _actcmpl->Clear ();
  _actcmpl->Clear ();
  _actcmpl->vardim = 0;
  }

void setfreevarhash_VarCheckOff_InFunction ()
  {
  setfreevarhash();
  VarCheckOff_InFunction();
  }
void setfreevarhash_withres ()
  {
  if (_actcmpl->ExpAllowed ()) {
    setfreevarhash ();
    _actcmpl->scv.v.vd = lastfvd ;
    copyExpRes ();
    }
  else
    _actcmpl->wError = SYNTAX_ERROR ;
  }

void PushActOfftoList (LPVOID FAR *lbeg,DWORD Offs,BOOL InExp = FALSE)
  {
  LPLUE le = LPLUE (GetGlobMem (sizeof(LookupEle)));
  le->Next = LPLUE (*lbeg) ;
  le->Offs = Offs ;
  le->InExp = InExp;
  *lbeg = le;
  }

void ScriptCompiler::PushOffs (DWORD Offs,WORD Ident)
  {
  hash *hele = FixLUHash ();
  LPVOID FAR *lbeg = (LPVOID FAR *) hele->GetDataW (Ident);
  if (lbeg != NULL)
    PushActOfftoList (lbeg,Offs);
  else {
    LPVOID first = NULL;
    PushActOfftoList (&first,Offs);
    hele->SetDataW (Ident,&first,sizeof(LPVOID));
    }
  ReleaseLUHash ();
  }

void ScriptCompiler::PushExpId (DWORD Offs,WORD Ident)
  {
  hash *hele = FixLUHash ();
  
  LPVOID FAR *lbeg = (LPVOID FAR *) hele->GetDataW (Ident);
  if (lbeg != NULL)
    PushActOfftoList (lbeg,Offs,TRUE);
  else {
    LPVOID first = NULL;
    PushActOfftoList (&first,Offs,TRUE);
    hele->SetDataW (Ident,&first,sizeof(LPVOID));
    }
  ReleaseLUHash ();
  }


DWORD compiler::progOffs ()
  {
  DWORD Offs = 0 ;
  for (int i = level ; i >= 0 ; i--) {
    DWORD ActSize;
    if (codebuffer[i]) {
      LPSTR buffer = (LPSTR)GlobalLock (codebuffer[i]);
      ActSize = *((DWORD FAR *) buffer);
      }
    else {
      ActSize = sizeof(DWORD);
      }
    Offs += ActSize ;
    if (IsCondBuffer(i)) Offs -= sizeof(DWORD);
    if (IsProcBuffer(i)) Offs += sizeof(DWORD);
    }
  Offs -= sizeof(WORD);
  return Offs;
  }

DWORD compiler::ActOffs ()
  {
  DWORD Offs = 0 ;
  for (int i = level ; i >= 0 ; i--) {
    DWORD ActSize;
    if (codebuffer[i]) {
      LPSTR buffer = (LPSTR)GlobalLock (codebuffer[i]);
      ActSize = *((DWORD FAR *) buffer);
      }
    else ActSize = sizeof(DWORD);
    Offs += ActSize ;
    }
  Offs += sizeof(WORD);
  return Offs;
  }

void ScriptCompiler::MarkforLookup (WORD Ident)
  {
  PushOffs (progOffs(),Ident);
  }

void ScriptCompiler::MarkExpForLookup ()
  {
  MarkForExpbinding (progOffs());
  }

void ScriptCompiler::MarkExpForLookup (DWORD Offs)
  {
  MarkForExpbinding (Offs);
  }

extern ScriptContent_Entry scent;
void TransformTableID(vardef FAR *h,int TableNr)
  {
  if (h->DBNummer == HELPDATA) {
    h->DBNummer = 1;
    }
  else if ((h->DBNummer >= CSYSRECS) && (h->DBNummer < 0xEF00)) {
    if (TableNr >= 0)
      h->DBNummer = TableNr + CSYSRECS;
    else {
      for (WORD i = 0 ; i < scent.AnzTables ; i++) {
        if (h->DBNummer == scent.TRef[i].TableNr) {
          h->DBNummer = i + CSYSRECS;
          break ;
          }
        }
      WIN_ASSERT (i < scent.AnzTables);
      }
    }
  }
void setconststr ();
void setconstind ();
void setconstqword ();
void setconstdword ();
void setconstflag ();
void setconstdec ();
BOOL IsCompatible (BYTE type1,BYTE type2)
  {
  if (type1 == type2) return TRUE ;
  if (((type1 == VAR_STRARR) && (type2 == VAR_FLAG)) || 
      ((type1 == VAR_STRARR) && (type2 == VAR_FLAG)) ||
      (type2 == 0xFF)) return TRUE ;
  return FALSE ;
  }
void ScriptCompiler::pushpar ()
  {
  int size ;
  if (actpar > parcount)
    wError = PARERROR ;
  else {
    char FAR *base = (LPSTR)GlobalLock (hPars1) ;
    pardsc FAR *pdsc = ((pardsc FAR *) base) + actpar ;
    switch (scv.type) {
      case T_INTEGER :
        if (pdsc->par_kind == PAR_LONG)
          pushData (&scv.v.int_val,sizeof (LONG)),
          size = sizeof (LONG) ;
        else if (pdsc->par_kind == PAR_FREE) {
          // Defaultmaessig wird ein short int angenommen
          setconstind ();
          vardef constvd ;
          constvd.DBNummer = 2 ;
          constvd.Ident = constOffs ;   
          pushData (&constvd,sizeof (vardef));
          size = sizeof(vardef);
          }
        else if ((pdsc->par_kind == PAR_VAR) && 
                  ((pdsc->Extra == VAR_STRARR) || (pdsc->Extra == VAR_LONG) || (pdsc->Extra == VAR_FLAG))) {
          switch (pdsc->Extra) {
            case VAR_STRARR :
              setconstind ();
              break ;
            case VAR_LONG :
              setconstdword ();
              break ;
            case VAR_QLONG :
              setconstqword ();
              break ;
            case VAR_FLAG :
              setconstflag ();
              break ;
            }
          vardef constvd ;
          constvd.DBNummer = 2 ;
          constvd.Ident = constOffs ;   
          pushData (&constvd,sizeof (vardef));
          size = sizeof(vardef);
          }
        else wError = PARERROR ;
        break ;
      case DECIMAL :
        if (pdsc->par_kind == PAR_DEC)
          pushData (&scv.v.float_val,sizeof (float)),
          size = sizeof (float) ;
        else if (((pdsc->par_kind == PAR_VAR) && (pdsc->Extra == VAR_DEC)) || (pdsc->par_kind == PAR_FREE)) {
          setconstdec ();
          vardef constvd ;
          constvd.DBNummer = 2 ;
          constvd.Ident = constOffs ;   
          pushData (&constvd,sizeof (vardef));
          size = sizeof(vardef);
          }
        else wError = PARERROR ;
        break ;
      case STRING :
        if (pdsc->par_kind == PAR_STR)
          pushPars0 (),
          size = sizePars0 ();
        else if (((pdsc->par_kind == PAR_VAR) && (pdsc->Extra == VAR_STR)) || (pdsc->par_kind == PAR_FREE)) {
          setconststr ();
          vardef constvd ;
          constvd.DBNummer = 2 ;
          constvd.Ident = constOffs ;   
          pushData (&constvd,sizeof (vardef));
          size = sizeof(vardef);
          }
        else wError = PARERROR ;
        break ;
      case UNKNOWNIDENT :
        if ((pdsc->par_kind == PAR_FREE) || 
                ((pdsc->par_kind == PAR_VAR) && (pdsc->Extra == VAR_PROC)))
          // Lookup - Variable
          lookup (),
          size = sizeof (DWORD);
        else wError = PARERROR ;
        break ;
      case VARID :
        if ((pdsc->par_kind == PAR_FREE) || 
                          ((pdsc->par_kind == PAR_VAR) && 
                           (IsCompatible (pdsc->Extra,scv.v.vd.vartype)))) {
          vardef h;
          h = scv.v.vd.vd;
          if ((scv.v.vd.vartype != VAR_PICTURE) && (scv.v.vd.vartype != VAR_BITMAP))
            TransformTableID(&h,scv.v.vd.TableNr);
          pushData (&h,sizeof (vardef));
          if (scv.v.vd.isdynamic) {
            if (InInlineFunction())
              MarkInlineforLookup (scv.v.vd.vd.Ident);
            else
              MarkforLookup (scv.v.vd.vd.Ident);
            }
          if (scv.v.vd.isexpression) {
            if (InInlineFunction())
              MarkExpInlineForLookup ();
            else
              MarkExpForLookup ();
            }
          size = sizeof (vardef) ;
          }
        else wError = PARERROR ;
        break ;
      }
    if (wError == 0) {
      if (pdsc->par_kind != PAR_FREE) actpar ++ ;
      // Eintragen der Laenge des Parameterblockes
      char FAR *h = FixBuffer ();
      * (WORD FAR *) ((char _huge *) h + parlenoffs) += size;
      ReleaseBuffer () ;
      }
    GlobalUnlock (hPars1);
    }
  }

void pushpar ()
  {
  _actcmpl->pushpar ();         // Binden an die Instanz
  }

#define MAX_EXTRA       256
void CheckSegOff()
  {
  _actcmpl->dontCheckSeg = TRUE ;
  }
void CheckSegOn()
  {
  _actcmpl->dontCheckSeg = FALSE ;
  }
void ScriptCompiler::push_funchead (void)
  {
  CheckSegs ();
  CheckSegOff ();

  actpar = 0 ;
  fncstart = actSize() + sizeof(DWORD);
  parcount = scv.v.fd.parCount ;

  // Aktueller Programmoffset fuer den Debugger vorbereiten
  pushWord (scv.v.fd.funcId);

  if (!InInlineFunction())
    PushProgOffs ();

  pushWord (sizeof(WORD)+scv.v.fd.ExtraCount);
                // Aktuelle Groesse des Parameterblockes
  parlenoffs = actSize()+sizeof(WORD) ;
  if (scv.v.fd.ExtraCount) {
    char buffer[MAX_EXTRA];
    lmemset (buffer,'\0',scv.v.fd.ExtraCount);
    pushData (buffer,scv.v.fd.ExtraCount);
    }
  }

void push_funchead (void)
  {
  _actcmpl->push_funchead();
  }

// Kopie der Funktion fuer den Editor erstellen
/////////////////////////////////////////////////
void ScriptCompiler::GetFuncCopy ()
  {
  CheckSegOn ();
  if (!InInlineFunction())
    Debug_SetProgOffs ();

  if (actpar < parcount) {
    char FAR *base = (LPSTR)GlobalLock (hPars1) ;
    pardsc FAR *pdsc = ((pardsc FAR *) base) + actpar ;
    if (pdsc->par_kind != PAR_FREE)
      wError = PARERROR ;
    }

  if ((edp != NULL) && (InEdit)) {
    LPSTR Commands;
    if (edp->hGCommands == 0) {
      edp->hGCommands = GlobalAlloc (GHND,sizeof(WORD));
      Commands = (LPSTR)GlobalLock (edp->hGCommands);
      *(WORD FAR *) Commands = sizeof(WORD);
      }
    else
      Commands = (LPSTR)GlobalLock (edp->hGCommands);

    WORD nwsize = WORD (actSize () - fncstart + sizeof(DWORD));
    WORD oldsize = *(WORD FAR *) Commands;
    GlobalUnlock (edp->hGCommands);
    edp->hGCommands = GlobalReAlloc (edp->hGCommands,oldsize + nwsize,GMEM_ZEROINIT);
    Commands = (LPSTR)GlobalLock (edp->hGCommands);
    LPSTR Buffer = (LPSTR)GlobalLock (codebuffer[level]);
    lmemcpy (Commands + oldsize,Buffer+fncstart,nwsize);
    *(WORD FAR *) Commands += nwsize;

    // Nachtragen des Funktionsendes und des Scriptoffsets
    EdFncDesc FAR *fd = (EdFncDesc FAR *)GlobalLock (edp->hGFncDesc);
    fd[edp->AnzFncs].FncBeg = Commands + oldsize;
    fd[edp->AnzFncs].level = level;
    GlobalUnlock (edp->hGFncDesc);
    edp->AnzFncs += 1;

    // fertig
    GlobalUnlock (edp->hGCommands);
    GlobalUnlock (codebuffer[level]);
    }
  }

void GetFuncCopy ()
  {
  char FAR *base = (LPSTR)GlobalLock (_actcmpl->hPars1) ;
  pardsc FAR *pdsc = ((pardsc FAR *) base) + _actcmpl->actpar ;
  if ((_actcmpl->actpar < _actcmpl->parcount - 1)
            && (pdsc->par_kind!= PAR_FREE))
    _actcmpl->wError = PARERROR ;
  else
    _actcmpl->GetFuncCopy ();
  }

void ScriptCompiler::MarkEdBraceOpen ()
  {
  // Den Zeiger im Hauptbuffer bitte vermerken
  if ((edp != NULL) && (InEdit)) {
    if (edp->hGFncDesc == 0)
      edp->hGFncDesc = GlobalAlloc(GHND,sizeof(EdFncDesc));
    else
      edp->hGFncDesc = GlobalReAlloc (edp->hGFncDesc,
                      (edp->AnzFncs + 1) * sizeof(EdFncDesc),GHND
                                     );
    EdFncDesc FAR *fd = (EdFncDesc FAR *)GlobalLock (edp->hGFncDesc);
    fd[edp->AnzFncs].ParStart = actptr;
    GlobalUnlock (edp->hGFncDesc);
    }
  }

void MarkEdBraceOpen ()
  {
  _actcmpl->MarkEdBraceOpen ();
  }

void pushop (void)
  {
  _actcmpl->pushOp ((_actcmpl->scv.v.k_ident == OPAND) ? PREFIX_AND : PREFIX_OR ) ;
  inclevel () ;
  }

void marknot (void)
  {
  _actcmpl->pushWord (PREFIX_NOT);
  }

void popbuffer (void)
  {
  _actcmpl->ClearCond();
  _actcmpl->Pop () ;
  }

void markif (void)
  {
  _actcmpl->pushWord (PREFIX_IF);
  _actcmpl->pushWord (0);
  _actcmpl->pushDWord (0);      // Commando - Zaehler
  }

void markfor ()
  {
  struct ForHeader fh;
  fh.prefix = PREFIX_FOR ;
  _actcmpl->pushData (&fh,sizeof(fh.prefix));
  _actcmpl->PushProgOffs();
  _actcmpl->Debug_SetProgOffs ();
  fh.forType = FORTYPE_NONE ;
  fh.fp = NULL;
  fh.ctrs = NULL;
  fh.objVar = 0xFFFFFFFF;
  fh.listName = 0xFFFFFFFF;
  fh.AnzParams = 0;
  _actcmpl->pushData (LPSTR(&fh) + sizeof(fh.prefix),fh.Size() - sizeof(fh.prefix));
  _actcmpl->ActForDBSelOffs.Push(0);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActForTypeOffs.Push(*((DWORD FAR *) buffer) - fh.Size());
  }

void fortype_cond ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = FORTYPE_COND ;
  }

void fortype_dbsel ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = FORTYPE_DBLIST ;
  }

void fortype_select ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = FORTYPE_SELECT ;
  }

void SetReverse ()
  {
  _actcmpl->rfortype = FORTYPE_INNEROBJREV ;
  }
void SetNormal ()
  {
  _actcmpl->rfortype = FORTYPE_INNEROBJ ;
  }
void fortype_innerobj ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = _actcmpl->rfortype ;
  }

void fortype_outerobj ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = FORTYPE_OUTEROBJ ;
  }

void fortype_initlist ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->forType = FORTYPE_INIT ;
  }

void pushdbselpar ()
  {
  struct DBSelCondition dbsel;
  dbsel.anzSels = -1;
  dbsel.TableName = 0xFFFFFFFF ;
  dbsel.WhereName = 0xFFFFFFFF ;
  dbsel.OrderName = 0xFFFFFFFF ;
  dbsel.AnzPars = 0;
  dbsel.DoReverse = 0;
  _actcmpl->pushData (&dbsel,dbsel.Size());
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActForDBSelOffs.Pop();
  _actcmpl->ActForDBSelOffs.Push(*((DWORD FAR *) buffer) - dbsel.Size());
  }

void getparexpression (vardef FAR *vd,DWORD varOffset,int FAR *TableNr);
DWORD LevelSize ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  return *((DWORD FAR *) buffer);
  }
void pushselectpar ()
  {
  struct DBSelCondition dbsel;
  dbsel.anzSels = -1;
  dbsel.TableName = 0xFFFFFFFF ;
  dbsel.WhereName = 0xFFFFFFFF ;
  dbsel.OrderName = 0xFFFFFFFF ;
  dbsel.AnzPars = 0;
  dbsel.DoReverse = 0;
  _actcmpl->pushData (&dbsel,dbsel.Size());
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActForDBSelOffs.Pop();
  _actcmpl->ActForDBSelOffs.Push(*((DWORD FAR *) buffer) - dbsel.Size());

  // Die Expression gleich schon mal als whereexpression eintragen
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() - LevelSize() + _actcmpl->ActForDBSelOffs.Top() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->WhereName 
            = MAKELONG(h.DBNummer,h.Ident);

  }

extern int FindAliasTable (LPSTR AliasName);
void SetObjTableNr ()
  {
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr = FindAliasTable (AliasName);
  if (tnr >= 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    *((short FAR *) ((char huge *) buffer + _actcmpl->ActTableNrOffs)) = tnr ;
    GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
    }
  else
    _actcmpl->wError = PARERROR ;
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetObjCondVar ()
  {
  vardef h;
  h = _actcmpl->scv.v.vd.vd;
  TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActTableNrOffs = *((DWORD FAR *) buffer);
  short tnr = -1;
  _actcmpl->pushData (&tnr,sizeof(tnr));
  VarCheckOff ();
  }

void SetDBName ()
  {
  setconststr ();
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->TableName 
            = MAKELONG(2,_actcmpl->constOffs);
  }

void SetDBSelCount ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->anzSels = short (_actcmpl->scv.v.int_val);
  }

void SetDBSelReverse ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->DoReverse = TRUE;
  }

void SetWhereExp ()
  {
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() - LevelSize() + _actcmpl->ActForDBSelOffs.Top() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->WhereName 
            = MAKELONG(h.DBNummer,h.Ident);
  }

void SetOrderExp ()
  {
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() - LevelSize() + _actcmpl->ActForDBSelOffs.Top() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->OrderName 
            = MAKELONG(h.DBNummer,h.Ident);
  }

void SetDBForExp ()
  {
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() - LevelSize() + _actcmpl->ActForDBSelOffs.Top() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((DBSelCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzPars ++ ;
  _actcmpl->pushData (&h,sizeof(h));
  }

void setfortable ()
  {
  setconststr ();
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->listName
            = MAKELONG(2,_actcmpl->constOffs);
  }
void setforobj ()
  {
  vardef h;
  h = _actcmpl->scv.v.vd.vd;
  TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->objVar
            = MAKELONG(h.DBNummer,h.Ident);
  }
void setforparam ()
  {
  vardef h;
  h = _actcmpl->scv.v.vd.vd;
  TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((ForHeader FAR *) ((char huge *) buffer + _actcmpl->ActForTypeOffs.Top()))->AnzParams ++ ;
  _actcmpl->pushData (&h,sizeof(h));
  }
void PushInitVar ()
  {
  if (_actcmpl->ActForDBSelOffs.Top() == 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    _actcmpl->ActForDBSelOffs.Pop();
    _actcmpl->ActForDBSelOffs.Push(*((DWORD FAR *) buffer));
    struct InitCondition ic;
    ic.AnzVars = 0 ;
    ic.AnzPars = 0 ;
    _actcmpl->pushData (&ic,ic.Size());
    }
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  int apAct = ((InitCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzPars;
  int avAct = ((InitCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzVars;
  if (avAct > 0) {
    int AnzPerVar = apAct / avAct ;
    if (avAct * AnzPerVar != apAct) _actcmpl->wError = PARERROR ;
    }
  ((InitCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzPars ++ ;
  ((InitCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzVars ++ ;
  vardef h;
  h = _actcmpl->scv.v.vd.vd;
  TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  }
void PushInitListExpression ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((InitCondition FAR *) ((char huge *) buffer + _actcmpl->ActForDBSelOffs.Top()))->AnzPars ++ ;
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  }
void SetWithTable ()
  {
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr = FindAliasTable (AliasName);
  if (tnr >= 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    ((WithParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->TableNr = tnr ;
    GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
    }
  else
    _actcmpl->wError = PARERROR ;
  GlobalUnlock (_actcmpl->hPars0);
  }
void PushWithBlock_base (WORD prefix)
  {
  WithParam wp;
  wp.Prefix_With = prefix ;
  wp.TableNr = -1 ;
  _actcmpl->pushData (&wp,sizeof(wp.Prefix_With));
  _actcmpl->PushProgOffs();
  _actcmpl->Debug_SetProgOffs ();
  wp.BlockSize = sizeof(WORD) + sizeof(WORD) + 4 * sizeof(LPVOID) + sizeof(short) ;
  wp.ctrs = NULL ;
  wp.mp = NULL ;
  wp.oldrec = NULL ;
  wp.wlist = NULL ;
  wp.TableInd = 0;
  wp.TableNr = -1;
  int size = sizeof(wp.Prefix_With) + sizeof(wp.BlockSize) + sizeof(wp.TableNr) + 4 * sizeof(LPVOID) + sizeof(wp.TableInd);
  _actcmpl->pushData (LPSTR(&wp) + sizeof(wp.Prefix_With),size - sizeof(wp.Prefix_With));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActSingOffs = *((DWORD FAR *) buffer) - size;
  }
void PushWithBlock ()
  {
  PushWithBlock_base (PREFIX_WITH);
  }
void PushForAllBlock ()
  {
  PushWithBlock_base (PREFIX_FORALL);
  }
void PushDoWithBlock ()
  {
  PushWithBlock_base (PREFIX_DOWITH);
  }
void PushWithConst ()
  {
  vardef constvd ;
  constvd.DBNummer = 2 ;
  constvd.Ident = _actcmpl->constOffs ;   
  _actcmpl->pushData (&constvd,sizeof (vardef));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((WithParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->BlockSize += sizeof(vardef);
  }
void PushWithVar ()
  {
  vardef h;
  h = _actcmpl->scv.v.vd.vd;
  TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((WithParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->BlockSize += sizeof(vardef);
  }
void PushWithVar_CheckOff ()
  {
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((WithParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->BlockSize += sizeof(vardef);
  VarCheckOff ();
  }
void PushWithExp ()
  {
  vardef h;
  int TableNr;
  getparexpression (&h,_actcmpl->progOffs() + sizeof(DWORD),&TableNr);
  TransformTableID(&h,TableNr);
  _actcmpl->pushData (&h,sizeof(h));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((WithParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->BlockSize += sizeof(vardef);
  }
extern void GetLastTermSym (vardef FAR *h);
extern BOOL CheckLastExp ();
void SetInTableNr ()
  {
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr = FindAliasTable (AliasName);
  if (tnr >= 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    ((InParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->TableNr = tnr ;
    GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
    }
  else
    _actcmpl->wError = PARERROR ;
  GlobalUnlock (_actcmpl->hPars0);
  }
void CheckInHd ()
  {
  BOOL doHeader = TRUE ;
  if (_actcmpl->ActSingOffs != 0L) {
    if (_actcmpl->codebuffer[_actcmpl->level]) {
      LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
      if (_actcmpl->ActSingOffs < GlobalSize (_actcmpl->codebuffer[_actcmpl->level])) {
        InParam FAR *lip = (InParam FAR *) (buffer + _actcmpl->ActSingOffs) ;
        doHeader = (lip->Prefix_In != PREFIX_IN) ;
        }
      }
    }
  if (doHeader) {
    InParam ip;
    ip.Prefix_In = PREFIX_IN ;
    ip.BlockSize = sizeof(WORD) + sizeof(short) ;
    ip.TableNr = -1 ;
    int size = sizeof(ip.Prefix_In) + sizeof(ip.BlockSize) + sizeof(ip.TableNr) ;
    _actcmpl->pushData (&ip,size);
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    _actcmpl->ActSingOffs = *((DWORD FAR *) buffer) - size;
    }
  }
void GetExpRes ()
  {
  CheckInHd ();
  PushWithExp ();
  }
void CheckExpRes ()
  {
  if (CheckLastExp ())
    GetExpRes ();
  }
void SetInsertTableNr ()
  {
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr = FindAliasTable (AliasName);
  if (tnr >= 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    ((InsertParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->TableNr = tnr ;
    GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
    }
  else
    _actcmpl->wError = PARERROR ;
  GlobalUnlock (_actcmpl->hPars0);
  }
void PushInsertBlock ()
  {
  InsertParam ip;
  ip.Prefix_In = PREFIX_INSERT ;
  _actcmpl->pushData (&ip,sizeof(ip.Prefix_In));
  _actcmpl->PushProgOffs();
  _actcmpl->Debug_SetProgOffs ();
  ip.BlockSize = 2 * sizeof(WORD) + sizeof(short) ;
  ip.InsertType = INSERTTYPE_NONE ;
  ip.TableNr = -1;
  int size = ip.BlockSize + sizeof(ip.Prefix_In);
  _actcmpl->pushData (LPSTR(&ip) + sizeof(ip.Prefix_In),size - sizeof(ip.Prefix_In));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActSingOffs = *((DWORD FAR *) buffer) - size;
  }
void SetInsertTypeAfter ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((InsertParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->InsertType = INSERTTYPE_AFTER;
  }
void SetInsertTypeBefore ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  ((InsertParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->InsertType = INSERTTYPE_BEFORE;
  }
void SetRemoveTableNr ()
  {
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  int tnr = FindAliasTable (AliasName);
  if (tnr >= 0) {
    LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
    ((RemoveParam FAR *) ((char huge *) buffer + _actcmpl->ActSingOffs))->TableNr = tnr ;
    GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
    }
  else
    _actcmpl->wError = PARERROR ;
  GlobalUnlock (_actcmpl->hPars0);
  }
void PushRemoveBlock ()
  {
  RemoveParam rp;
  rp.Prefix_In = PREFIX_REMOVE ;
  rp.BlockSize = sizeof(WORD) + sizeof(short) ;
  rp.TableNr = -1;
  _actcmpl->pushData (&rp,sizeof(rp.Prefix_In));
  _actcmpl->PushProgOffs();
  _actcmpl->Debug_SetProgOffs ();
  int size = rp.BlockSize + sizeof(rp.Prefix_In) ;
  _actcmpl->pushData (LPSTR(&rp) + sizeof(rp.Prefix_In),size - sizeof(rp.Prefix_In));
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->ActSingOffs = *((DWORD FAR *) buffer) - size;
  }

void markcase (void)
  {
  _actcmpl->pushWord (PREFIX_CASE);
  }

void markfurther (void)
  {
  _actcmpl->pushWord (0xFFFF);
  _actcmpl->pushDWord (0);      // Commando - Zaehler
  inclevel ();
  }

void markrunnr (void)
  {
  WORD run = WORD (_actcmpl->scv.v.int_val);
  _actcmpl->pushWord (run);
  _actcmpl->pushDWord (0);      // Commando - Zaehler
  inclevel ();
  }

void markelse (void)
  {
  _actcmpl->pushWord (PREFIX_ELSE);
  inclevel ();
  }

void marknoelse (void)
  {
  _actcmpl->pushWord (PREFIX_NOP);
  _actcmpl->pushWord (sizeof(WORD));
  }

void popstatement (void)
  {
  DWORD size = _actcmpl->actSize ();
  _actcmpl->level -- ;
  _actcmpl->pushDWord (size + sizeof (DWORD)) ;
  _actcmpl->level ++ ;
  _actcmpl->Pop ();
  }

void endproc (void)
  {
  DWORD rsize = _actcmpl->actSize ();
  DWORD rOffs = _actcmpl->progOffs () - rsize;
  // Expressions auf das Compilat schmeissen
  DWORD dOffs = _actcmpl->progOffs();

  _actcmpl->AddExpressions ();
  _actcmpl->DoExpDebPush (dOffs);

  char huge *base = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->CorrectExpOffs (base+sizeof(DWORD),rsize,rOffs);
  _actcmpl->FixupExpOffs (base+sizeof(DWORD),rOffs+rsize,rOffs);
  _actcmpl->corr_ptr = 0 ;

  DWORD gsize = _actcmpl->actSize ();
  // Und all diese Groessen noch nachtragen
  _actcmpl->level -- ;
  _actcmpl->pushDWord (gsize + 2 * sizeof (DWORD)) ;
  _actcmpl->pushDWord (rsize + sizeof (DWORD)) ;
  _actcmpl->ClearProcBuffer() ;
  _actcmpl->level ++ ;
  _actcmpl->Pop ();
  _actcmpl->PrevExpProc ();
  }

void ScriptCompiler::PushToLocalHashList (hash FAR *h,DWORD ActFuncAddress)
  {
  LocalHashList FAR *hl = (LocalHashList FAR *) GetGlobMem (sizeof(*h));
  hl->h = h ;
  hl->procOffset = ActFuncAddress;
  hl->Next = lhlist;
  lhlist = hl ;
  }

void endfunction ()
  {
  DWORD rsize = _actcmpl->actSize ();
  DWORD rOffs = _actcmpl->progOffs () - rsize;
  // Expressions auf das Compilat schmeissen
  DWORD dOffs = _actcmpl->progOffs();

  _actcmpl->AddExpressions ();
  _actcmpl->DoExpDebPush (dOffs);

  char huge *base = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->CorrectExpOffs (base+sizeof(DWORD),rsize,rOffs);
  _actcmpl->FixupExpOffs (base+sizeof(DWORD),rOffs+rsize,rOffs);
  _actcmpl->corr_ptr = 0 ;

  DWORD gsize = _actcmpl->actSize ();
  // Und all diese Groessen noch nachtragen
  _actcmpl->level -- ;
  _actcmpl->pushDWord (gsize + 2 * sizeof (DWORD)) ;
  _actcmpl->pushDWord (rsize + sizeof (DWORD)) ;
  _actcmpl->ClearProcBuffer() ;
  _actcmpl->level ++ ;
  // Nachtragen von AnzLocals und AnzStatic
  FuncStart FAR * Base = (FuncStart FAR *)((LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]) + sizeof(DWORD));
  Base->AnzLocals = _actcmpl->LocalVarCount;
  Base->AnzStaticLocals = _actcmpl->LocalHVarCount;
  _actcmpl->Pop ();
  _actcmpl->PrevExpProc ();

  _actcmpl->clearLocals ();
  _actcmpl->InFunction = FALSE ;
  }

void matchexpression_return ()
  {
  matchexpression ();
  // _actcmpl->pushWord (PREFIX_FUNCSTOP);
  }

extern void setexpfnc (LPSTR Name,BYTE FType,hash FAR *FAR *htbl,int offsToSet);
void marknores_UnqualifiedOff ()
  {
  lastvarTypeSet = 0xFF ;
  UnqualifiedOff ();
  }
#define MAX_PARS  64
static BYTE BindTyp [MAX_PARS];
void markvarnobind ()
  {
  BindTyp[_actcmpl->AnzFuncPars] = BIND_STATIC ;
  }

void startfuncdefinition ()
  {
  // Die Bindtypen initialisieren
  if (lastvarTypeSet != 0xFF)
    BindTyp[0] = BIND_RETURN ;
  else
    BindTyp[0] = BIND_DYNAMIC ;
  for (int i = 1 ; i < MAX_PARS ; i++)
    BindTyp[i] = BIND_DYNAMIC ;
  _actcmpl->actres = lastvarTypeSet ;
  _actcmpl->funcVarType = lastvarTypeSet ;
  // In level steht der name, in level - 1 (der nutzlose) Datentyp
  //--------------------------------------------------------------
  LPSTR name = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]) + sizeof (DWORD) ;
  if ((_actcmpl->FType == FTYPE_DECLARE) || (_actcmpl->FType == FTYPE_VIRTUAL)) {
    // Vorne einen "." einfuegen
    char decname[128];
    decname[0] = '.' ;
    lstrncpy (decname + 1,name,sizeof(decname)-2);
    setexpfnc (decname,_actcmpl->FType,&_actcmpl->declareFuncs,1);
    }
  else
    setexpfnc (name,_actcmpl->FType,&_actcmpl->hefHash,0);
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->Clear ();
  if (_actcmpl->actres != 0xFF)     // Auch die fullvardef des Resultats wegnehmen
    _actcmpl->Clear ();
  // Es muessen wieder 2 levels zurueckgenommen werden
  if (lastvarTypeSet == 0xFF) {
    _actcmpl->AnzFuncPars = 0 ;
    _actcmpl->LocalVarCount = 0 ;
    }
  else {
    _actcmpl->AnzFuncPars = 1 ;
    _actcmpl->LocalVarCount = 1 ;   // Eine Variable fuer den Rueckgabewert reservieren
    }
  _actcmpl->IsInFuncDefinition = TRUE ;
  _actcmpl->dontVarCheckGlobals = TRUE;

  _actcmpl->InFunction = TRUE ;
  }

void startfunction ()
  {
  startfuncdefinition ();
  }

LPVOID makecmpltT (funcdef FAR *fd,DWORD procAddr,int AnzBytesBeforeParam,LPWORD ti,int Anzti);
LPVOID makecmpltT (funcdef FAR *fd,DWORD d);
void defopargT (int i);
void defopresT (pardsc FAR *pd);
extern LPSTR GetFName(LPVOID fname);
void markFuncExport ()
  {
  _actcmpl->FType = FTYPE_EXPORT ;
  }
void markFuncOverload ()
  {
  _actcmpl->FType = FTYPE_IMPORT ;
  }
void markFuncExtern ()
  {
  _actcmpl->FType = FTYPE_DECLARE ;
  }
extern BOOL IsDeclared ();
static LPVOID lastcmplt;
void closefuncdefinition ()
  {
  // Erzeugen des Kompilates
  //-------------------------
  funcdef fd;
  // char extraName[32];
  _actcmpl->TablesToReuse[0] = _actcmpl->AnzTablesToReuse;
  if ((_actcmpl->FType == FTYPE_EXPORT) || (_actcmpl->FType == FTYPE_IMPORT)) {
    fd.ExtraCount = 12 ;
    fd.funcId = PREFIX_VIRTCALL ;
    fd.parCount = _actcmpl->AnzFuncPars ;
    lastcmplt = makecmpltT (&fd,0L,int(sizeof(DWORD)),_actcmpl->TablesToReuse,_actcmpl->AnzTablesToReuse + 1);   // Vor den Parametern steht der Modulname
    if ((_actcmpl->FType == FTYPE_IMPORT) && (!IsDeclared()))
      _actcmpl->wError = NOPROTOTYPES;
    }
  else if ((_actcmpl->FType == FTYPE_DECLARE) || (_actcmpl->FType == FTYPE_VIRTUAL)) {
    fd.ExtraCount = 12 ;
    fd.funcId = PREFIX_VIRTCALL ;
    fd.parCount = _actcmpl->AnzFuncPars ;
    lastcmplt = makecmpltT (&fd,0L,int(sizeof(DWORD)),_actcmpl->TablesToReuse,_actcmpl->AnzTablesToReuse + 1);   // Vor den Parametern steht der Modulname
    }
  else {
    if (_actcmpl->AnzTablesToReuse > 0)
      _actcmpl->wError = USENOTALLOWED;
    fd.ExtraCount = 8 ;
    fd.funcId = PREFIX_FUNCTIONCALL ;
    fd.parCount = _actcmpl->AnzFuncPars ;
    lastcmplt = makecmpltT (&fd,0L);
    }

  // Definieren der Argumente: 
  // Fixup des Offsets, kann erst nach erstellung des Kompilates gemacht werden
  if (_actcmpl->actres != 0xFF) {
    pardsc pd;
    pd.par_kind = PAR_VAR;
    pd.Extra = _actcmpl->funcVarType;
    defopresT (&pd);
    // Den Returnwert noch als Variable setzen
    full_vardef fvd;
    fvd.vartype = _actcmpl->funcVarType;
    fvd.vd.Ident = 0;
    fvd.isdynamic = FALSE ;
    fvd.isexpression = FALSE ;
    fvd.doubleDefined = FALSE ;
    fvd.vd.DBNummer = DYNLOCALDATA ;
    hash *h = _actcmpl->FixLocals ();
    h->SetData ("_return",&fvd,sizeof (full_vardef));
    for (int i = 1 ; i < _actcmpl->AnzFuncPars ; i++)
      defopargT (i);
    }
  else {
    for (int i = 1 ; i < _actcmpl->AnzFuncPars + 1 ; i++)
      defopargT (i);
    }

  _actcmpl->IsInFuncDefinition = FALSE ;
  _actcmpl->AnzTablesToReuse = 0;

  if ((_actcmpl->FType == FTYPE_DECLARE) || (_actcmpl->FType == FTYPE_VIRTUAL)) {
    _actcmpl->LocalVarCount = 1 ;
    _actcmpl->LocalHVarCount = 0 ;
    if (_actcmpl->localVars != NULL) {
      delete _actcmpl->localVars;
      }
    _actcmpl->localVars = NULL ;
    _actcmpl->InFunction = FALSE ;
    }
  _actcmpl->FType = FTYPE_NORMAL ;
  _actcmpl->dontVarCheck = FALSE;
  _actcmpl->dontVarCheckGlobals = FALSE ;
  }

void setfreevarhash_closefuncdefinition ()
  {
  setfreevarhash ();
  closefuncdefinition();
  }

void setfreevarhash_closefuncdef ()
  {
  setfreevarhash_closefuncdefinition ();
  }

void SetProcAddr (LPVOID extra,DWORD extraData);
void OnStartFunc ()
  {
  // Vorbereiten des Buffers
  _actcmpl->enterPars0Function ();
  _actcmpl->MarkProcBuffer() ;
  _actcmpl->NextExpProc ();
  inclevel ();
  SetProcAddr (lastcmplt,_actcmpl->ActFuncAddress);
  // Nun wird der Spezialbefehl zum Anlegen der DBRecords und zum Parameterbinding 
  // dazugepusht
  //-------------------------------------------------------------------------------
  _actcmpl->pushWord (PREFIX_FUNCSTART);
  _actcmpl->pushDWord (0L);   // 1. DBRecord
  _actcmpl->pushDWord (0L);   // 2. DBReocrd
  _actcmpl->pushWord (_actcmpl->AnzFuncPars); // AnzPars
  _actcmpl->pushWord (0); // AnzLocals      (muss beim Funktionsende noch nachgetragen werden)
  _actcmpl->pushWord (0); // AnzStaticLocals ;
  _actcmpl->pushData (BindTyp,_actcmpl->AnzFuncPars);   // Parameterbindung
  }

void closefuncdef ()
  {
  closefuncdefinition ();
  }

void prepreturn ()
  {
  if ((_actcmpl->actres != 0xFF) && (_actcmpl->InFunction) && (!_actcmpl->allowBreak)) {
    if (_actcmpl->ExpAllowed ()) {
      _actcmpl->scv.v.vd.vartype = _actcmpl->funcVarType ;
      _actcmpl->scv.v.vd.vd.DBNummer = DYNLOCALDATA ;
      _actcmpl->scv.v.vd.vd.Ident = 0 ;
      _actcmpl->scv.v.vd.isdynamic = FALSE ;
      _actcmpl->scv.v.vd.isexpression = FALSE ;
      _actcmpl->scv.v.vd.doubleDefined = FALSE ;
      _actcmpl->scv.v.vd.TableNr = -1 ;
      copyExpRes ();
      }
    else
      _actcmpl->wError = SYNTAX_ERROR ;
    }
  else
    _actcmpl->wError = SYNTAX_ERROR ;
  }

void pushcall ()
  {
  _actcmpl->pushWord (PREFIX_CALL);
  if (!_actcmpl->InInlineFunction()) {
    _actcmpl->PushProgOffs ();
    _actcmpl->Debug_SetProgOffs ();
    }
  _actcmpl->pushDWord (0L);   // Platz fuer die ev. noetige Multproc
  }

void pushstaticcall ()
  {
  _actcmpl->pushWord (PREFIX_STATICCALL);
  if (!_actcmpl->InInlineFunction()) {
    _actcmpl->PushProgOffs ();
    _actcmpl->Debug_SetProgOffs ();
    }
  }

void pushbreak ()
  {
  if (_actcmpl->allowBreak) {
    _actcmpl->pushWord (PREFIX_BREAK);
    if (!_actcmpl->InInlineFunction()) {
      _actcmpl->PushProgOffs ();
      _actcmpl->Debug_SetProgOffs ();
      }
    }
  else
    _actcmpl->wError = SYNTAX_ERROR ;
  }

void pushcontinue ()
  {
  if (_actcmpl->allowBreak) {
    _actcmpl->pushWord (PREFIX_CONTINUE);
    if (!_actcmpl->InInlineFunction()) {
      _actcmpl->PushProgOffs ();
      _actcmpl->Debug_SetProgOffs ();
      }
    }
  else
    _actcmpl->wError = SYNTAX_ERROR ;
  }

void ScriptCompiler::enterPars0 ()
  {
  DWORD Size = actSize () + sizeof (DWORD) ;
//  if (ImportDone)
//    Size |= 0x80000000;     // Oberstes Bit setzen (fuer Prozeduren in
//                            //          externen Scripts)
  char FAR *pName = (LPSTR)GlobalLock (hPars0) + sizeof (WORD);
  hash *h = FixPcHash ();
  if (!h->SetData (pName,&Size,sizeof (DWORD)))
    wError = PROCREDEF ;
  ReleasePcHash ();

  if (exportThis) {
    // Diese Prozedure auch noch exportieren
    if (!ImportDone) {
      wError = NOEXPORTINTHIS;
      return;
      }
    if (ExportHash == NULL) {
      ExportHash = new hash (37,STRKEY);
      }
    WIN_ASSERT (ExportHash != NULL);
    ExportHash->SetData (pName,&Size,sizeof(DWORD));
    }
  GlobalUnlock (hPars0);
  }

void ScriptCompiler::enterPars0Function ()
  {
  DWORD Size = actSize () + sizeof (DWORD) ;
  _actcmpl->ActFuncAddress = Size ;
  }

void markstart ()
  {
  DWORD Size = _actcmpl->actSize () + sizeof (DWORD) ;
  DWORD FAR *base = (DWORD FAR *) GlobalLock (_actcmpl->codebuffer[0]) + 1 ;
  *base = Size ;
  GlobalUnlock (_actcmpl->codebuffer[0]);
  _actcmpl->NextExpProc ();
  _actcmpl->MarkProcBuffer() ;
  inclevel ();
  }

void markproc ()
  {
  _actcmpl->enterPars0 ();
  _actcmpl->MarkProcBuffer() ;
  _actcmpl->NextExpProc ();
  inclevel ();
  }

void markforBlock ()
  {
  _actcmpl->allowBreak = PopBreakAllowed();
  _actcmpl->MarkProcBuffer();
  _actcmpl->NextExpProc() ;
  inclevel ();
  }
void markwithblock ()
  {
  _actcmpl->MarkProcBuffer();
  _actcmpl->NextExpProc() ;
  inclevel ();
  }
void noforblock ()
  {
  _actcmpl->level -- ;
  _actcmpl->PrevExpProc ();
  _actcmpl->ClearProcBuffer();
  _actcmpl->pushDWord(sizeof(DWORD));
  _actcmpl->ActForDBSelOffs.Pop();
  _actcmpl->ActForTypeOffs.Pop();
  }
void forendproc ()
  {
  endproc ();
  _actcmpl->ActForDBSelOffs.Pop();
  _actcmpl->ActForTypeOffs.Pop();
  }

void markexportproc ()
  {
  _actcmpl->exportThis = TRUE ;
  }

void ScriptCompiler::lookup ()
  {
  // In hPars0 steht der Prozedurname, der Aufgerufen werden
  // soll
  hash *h = FixPcHash ();
  char FAR *pName = (LPSTR)GlobalLock (hPars0) + sizeof (WORD);
  DWORD FAR *res = (DWORD FAR *) h->GetData (pName);

  if (res == NULL)
    wError = UNRESOLVEDCALL ;
  else
    pushDWord (*res);

  GlobalUnlock (hPars0);
  ReleasePcHash () ;
  }


void lookup (void)
  {
  // Funktionsaufruf
  _actcmpl->lookup ();
  }

/*-------------------------------------------------*/
/*      Parser                                     */
/*-------------------------------------------------*/
BOOL compiler::parse (syntax_node FAR *syntax) 
  {
  BOOL correct ;
  BOOL nextdone = FALSE ;

  for ( ; (syntax != NULL) ; ) {

    if (syntax->IsTerm) {
      // Terminalsymbol -> untersuchen !
      if (scv.type == syntax->info.term.type) {
        // Schluesselwoerter werden genauer untersucht
        if (scv.type == KEYWORD) 
          correct = (syntax->info.term.ExtraInfo == WORD (scv.v.k_ident)) ;
        // ansonsten scheint man auf dem korrekten weg zu sein
        else                         
          correct = TRUE ;
        }
      else if (syntax->info.term.type == FREECHAR) {
        PutTermBack () ;
        correct = TRUE ;
        }
      else if (syntax->info.term.type == T_ALL)
        correct = TRUE ;
      else correct = FALSE ;
      }
    else {
      // Rekursion !!!
      correct = parse (syntax->info.nonterm);
      if (wError) return FALSE ;
      }

    // Aufruf des Code - Generators
    if ((correct) && (syntax->codegen != NULL)) {
      (* (syntax->codegen)) ();
      if (wError) return FALSE ;
      }

    // Weiterschalten
    if (correct) {
      syntax = syntax->next ;
      if (syntax != NULL) {
        if (!PrgEnd) NextTerm ();
        else {
          wError = SYNTAX_ERROR ;
          }
        if (wError)
          return FALSE ;
        }
      nextdone = TRUE ;
      }
    else         syntax = syntax->alt ;
    }

  if ((!correct) && (nextdone)) {
    wError = SYNTAX_ERROR ;
    }
  return correct;
  }

static BYTE bit_pattern[] = 
        { 0x01 , 0x02 , 0x04 , 0x08 , 0x10 , 0x20 , 0x40 , 0x80 } ;
WORD BitArr::GetFirstFree ()
  {
  BYTE FAR *h = Arr + firstInd ;
  WORD res = firstInd * 8 ;
  BOOL found = FALSE ;
  for ( ; !found ; ) {
    BYTE act = *h ;
    for (int i = 0 ; i < 8 ; i++) {
      if ((act & 0x01) == 0) {
        found = TRUE ;
        *h |= bit_pattern[res % 8];
        break ;
        }
      act = act >> 1 ;
      res ++ ;
      }
    if (!found) {
      firstInd ++ ;
      h ++ ;
      }
    }
  return res;
  }

void BitArr::MarkUsed (WORD ind)
  {
  BYTE FAR *h = Arr + ind / 8 ;
  *h |= bit_pattern [ind % 8] ;
  }

void *BitArr::operator new (size_t size)
  {
  HANDLE hmem = LocalAlloc (LHND,size);
  void *res = (void *) LocalLock (hmem);
  ((BitArr *) res)->hmem = hmem ;
  return res;
  }

void BitArr::operator delete (void *obj)
  {
  HANDLE hmem = ((BitArr *) obj)->hmem ;
  LocalUnlock (hmem);
  LocalFree (hmem);
  }

WORD ScriptCompiler::GetFreeIdent ()
  {
  BitArr *h = FixBitArr ();
  WORD res = h->GetFirstFree ();
  ReleaseBitArr ();
  return res ;
  }

BOOL SetIdent (BYTE FAR * prog,LPVOID Offset,WORD Ident,WORD LfndNmbr)
  {
  for ( ; Offset ; ) {
    LPLUE le = LPLUE (Offset) ;
    char _huge *pg = (char _huge *) prog;
    char _huge *ex ;

    if (_actcmpl->hGExpBuffer)
      ex = (char _huge *) GlobalLock (_actcmpl->hGExpBuffer);
    
    WORD FAR *IdentToWrite;
    if (le->InExp)
      IdentToWrite = ((WORD FAR *) (&ex[le->Offs]));
    else
      IdentToWrite = ((WORD FAR *) (&pg[le->Offs]));

    if (*IdentToWrite != LfndNmbr) {
      _actcmpl->wError = LOOKUPERROR ;
      return FALSE ;
      }
    *IdentToWrite = Ident ;
    Offset = LPVOID (le->Next) ;
    }
  return TRUE ;
  }

void SetVarIdent (WORD Number,WORD Ident)
  {
  }

void IdentHash::LookUpIdents (BYTE FAR *prog)
  {
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    for (hash_entry FAR *e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        WORD Ident = _actcmpl->GetFreeIdent ();
        WORD Number = e->key.wKey ;
        LPVOID FAR *h = (LPVOID FAR *) e->Data;
        if (!SetIdent (prog,*h,Ident,Number)) return ;
        SetVarIdent (Number,Ident);
        }
      e = NextEnt (e);
      }
    }
  }

void CorrectExpIdents (DWORD start,DWORD end);
void compiler::CorrectLookupIdents (DWORD start,DWORD end)
  {
  IdentHash *h = FixLUHash ();
  h->CorrectLookupIdents (start,end);
  CorrectExpIdents(start,end);
  CorrectProgOffs (start,end);
  ReleaseLUHash ();
  }

void IdentHash::CorrectLookupIdents (DWORD start,DWORD end)
  {
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    for (hash_entry FAR *e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        LPVOID FAR *h = (LPVOID FAR *) e->Data;
        LPLUE le = LPLUE (*h);
        if ((le->Offs >= start) && (le->Offs < end) && (!le->InExp)) {
          le->Offs += sizeof (WORD) + sizeof(DWORD);
          }
        }
      e = NextEnt (e);
      }
    }
  }


static fpt constpt ;
void setptx ()
  {
  constpt.x = _actcmpl->scv.v.float_val;
  }

void setpty ()
  {
  constpt.y = _actcmpl->scv.v.float_val;
  }

void setconstpt ()
  {
  _actcmpl->constOffs = _actcmpl->pushConst (&constpt,sizeof(fpt),VAR_POINT);
  _actcmpl->constType = VAR_POINT ;
  setopallowed ();
  }

void setconststr ()
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->hPars0);
  _actcmpl->constOffs = _actcmpl->pushConst (buffer + sizeof(WORD),
                                    *((WORD FAR *) buffer) - sizeof (WORD),
                                    VAR_STR
                                  );
  _actcmpl->constType = VAR_STR ;
  GlobalUnlock (_actcmpl->hPars0);
  setopallowed ();
  }

void setconstind ()
  {
  _actcmpl->constOffs = _actcmpl->pushConst (&_actcmpl->scv.v.int_val,sizeof (WORD),VAR_STRARR);
  _actcmpl->constType = VAR_STRARR ;
  setopallowed ();
  }

void setconstdword ()
  {
  _actcmpl->constOffs = _actcmpl->pushConst (&_actcmpl->scv.v.int_val,sizeof (LONG),VAR_LONG);
  _actcmpl->constType = VAR_LONG ;
  setopallowed ();
  }

void setconstqword ()
  {
  long double res = _actcmpl->scv.v.ld ;
  _actcmpl->constOffs = _actcmpl->pushConst (&res,sizeof (res),VAR_QLONG);
  _actcmpl->constType = VAR_QLONG ;
  setopallowed ();
  }

void setconstflag ()
  {
  _actcmpl->constOffs = _actcmpl->pushConst (&_actcmpl->scv.v.int_val,sizeof (DBINT),VAR_FLAG);
  _actcmpl->constType = VAR_FLAG ;
  setopallowed ();
  }

void setconstdec ()
  {
  _actcmpl->constOffs = _actcmpl->pushConst (&_actcmpl->scv.v.float_val,sizeof (float),VAR_DEC);
  _actcmpl->constType = VAR_DEC ;
  setopallowed ();
  }

void ScriptCompiler::MarkForConstbinding (DWORD Offs)
  {
  LPLUE le = LPLUE (GetGlobMem (sizeof(*le)));
  le->Next = ConstOffsList ;
  ConstOffsList = le;
  le->Offs = Offs ;
  }

void ScriptCompiler::MarkForExpbinding (DWORD Offs)
  {
  LPLUE le = LPLUE (GetGlobMem (sizeof(*le)));
  le->Next = ExpOffsList ;
  ExpOffsList = le;
  le->Offs = Offs ;
  }

void CorrectExpIdents (DWORD start,DWORD end)
  {
  for (LPLUE h = _actcmpl->ExpOffsList ; h != NULL ; h = h->Next) {
    if ((h->Offs >= start) && (h->Offs < end)) h->Offs += sizeof(WORD) + sizeof(DWORD) ;
    }
  }

void ScriptCompiler::FixupConstOffs (LPSTR buffer,WORD Extra)
  {
  for ( ; ConstOffsList != 0 ; ) {
    LPLUE le = ConstOffsList;
    char _huge *bf = (char _huge *) bf;
    WORD FAR *IdentToUpdate = (WORD FAR *) (bf + le->Offs) ;
    WORD FAR *ConstRec = IdentToUpdate - 1 ;
    if (*ConstRec != 2) {
      wError = CONSTLOOKUPERROR ;
      break ;
      }
    else {
      *IdentToUpdate += Extra ;
      ConstOffsList = le->Next ;
      }
    }
  }

void ScriptCompiler::DestroyConstList ()
  {
  if (hGConstOffsMem) {
    GlobalUnlock (hGConstOffsMem);
    GlobalFree (hGConstOffsMem);
    hGConstOffsMem = 0;
    ConstOffsList = NULL;
    }
  }

void pushconstpar ()
  {
  int size ;
  if (_actcmpl->actpar > _actcmpl->parcount)
    _actcmpl->wError = PARERROR ;
  else {
    char FAR *base = (LPSTR)GlobalLock (_actcmpl->hPars1) ;
    pardsc FAR *pdsc = ((pardsc FAR *) base) + _actcmpl->actpar ;
    if ((pdsc->par_kind == PAR_FREE) || 
                ((pdsc->par_kind == PAR_VAR) && 
                 (pdsc->Extra == _actcmpl->constType))) {
      vardef constvd ;
      constvd.DBNummer = 2 ;
      constvd.Ident = _actcmpl->constOffs ;   
      _actcmpl->pushData (&constvd,sizeof (vardef));
      if (_actcmpl->InInlineFunction())
        _actcmpl->MarkInlineForConstbinding (_actcmpl->fncOffs() - sizeof(vardef)) ;
      else
        _actcmpl->MarkForConstbinding (_actcmpl->progOffs()) ;
      size = sizeof (vardef) ;
      }
    else _actcmpl->wError = PARERROR ;
    if (_actcmpl->wError == 0) {
      if (pdsc->par_kind != PAR_FREE) _actcmpl->actpar ++ ;
      // Eintragen der Laenge des Parameterblockes
      char FAR *h = _actcmpl->FixBuffer ();
      * (WORD FAR *) ((char _huge *) h + _actcmpl->parlenoffs) += size;
      _actcmpl->ReleaseBuffer () ;
      }
    GlobalUnlock (_actcmpl->hPars1);
    }
  }

#define LPDIMENSION    11
void startinlinefunction (void)
  {
  // Aufbauen eine Hashtabelle fuer die Parameter der lokalen Funktionen
  if (_actcmpl->hlPHash)
    _actcmpl->wError = NESTINGERROR ;
  else {
    _actcmpl->hlPHash = new hash (STRKEY,LPDIMENSION) ;
    }
  }

void storeinlinename (void)
  {
  // Zwischenspeichern des Funktionsnamens 
  char FAR *txt = (LPSTR)GlobalLock (_actcmpl->hPars0);
  lstrncpy (inlinename,txt+sizeof(WORD),sizeof (inlinename));
  GlobalUnlock (_actcmpl->hPars0);
  }

void startinlinepar (void)
  {
  inclevel ();
  anzinlinepars = 0;
  }

void endinlinepar (void)
  {
  // Level, der fuer die parameter verwendet wurde, wieder freigeben
  _actcmpl->Clear();
  }

void setfncpar (void)
  {
  // Funktionsparameter in die Hashtabelle ablegen
  hash *h = _actcmpl->FixlPHash();
  char FAR *fname = (LPSTR)GlobalLock (_actcmpl->hPars0);
  char FAR *parbuffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  WORD size = WORD (*(DWORD FAR *) parbuffer) ;

  // Zwischenspeichern der Daten in dem Parameterbuffer
  lmemcpy (&inlinefncpar[anzinlinepars],parbuffer+sizeof(DWORD),sizeof(pardsc));

  // Eintragen der Daten in die Parameter - Tabelle
  fncpardef fpd ;
  lmemcpy (&fpd.pd,parbuffer+sizeof(DWORD),size - sizeof(DWORD));
  fpd.Number = anzinlinepars ;
  h->SetData (fname+sizeof (WORD),&fpd,sizeof(fpd));

  // Vorbereiten fuer den naechsten Parameter
  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->Clear();
  inclevel () ;

  // fertig
  _actcmpl->ReleaselPHash();
  GlobalUnlock (_actcmpl->hPars0);

  anzinlinepars ++ ;
  }

// Verwaltung der 2dim. Liste mit den lookup - Werten
void FreeFList (firstListEle FAR *h)
  {
  for ( ; (h != NULL) ; ) {
    firstListEle FAR *n = h->next ;
    h->FreeMem ();
    FreeGlobMem (h);
    h = n ;
    }
  }
void FreeSList (secondListEle FAR *h)
  {
  for ( ; (h != NULL) ; ) {
    secondListEle FAR *n = h->next ;
    FreeGlobMem (h);
    h = n ;
    }
  }
void ScriptCompiler::DestroyFncLookup ()
  {
  for (int i = 0 ; i < int (hlFHash->hash_dimension) ; i++) {
    for (LPhash_entry e = hlFHash->Table + i ; e != NULL ; ) {
      if (!hlFHash->is_empty (e)) {
        // Schluessel Speichern
        inlinefnc_header FAR *d = (inlinefnc_header FAR *) e->Data ;
        FreeFList (d->LookupList);
        FreeFList (d->ExpLookupList);
        FreeFList (d->LocalLookup);
        FreeFList (d->LocalExpLookup);
        FreeSList (d->ExpressionLookup);
        FreeSList (d->ConstLookup);
        }
      e = hlFHash->NextEnt (e);
      }
    }
  }

// Funktion fertig definiert, alles in einem Buffer zusammen legen
// und mit dem Funktionsnamen speichern
///////////////////////////////////////////////////////////////////
void startfnc ()
  {
  inclevel ();
  _actcmpl->startlevel = _actcmpl->level ;
  }

extern void PushNPtr (LPVOID ptr);
void storefnc ()
  {
  char FAR *fncbuffer = (LPSTR)GlobalLock (_actcmpl->codebuffer[_actcmpl->level]);
  WORD fncSize = WORD (* ((DWORD FAR *) fncbuffer) - sizeof(DWORD));
  WORD parSize  = sizeof(pardsc) * anzinlinepars;
  WORD gessize  = sizeof(inlinefnc_header) + parSize + fncSize ;

  GLOBALHANDLE hGtemp = GlobalAlloc (GHND,gessize);
  LPSTR buffer = (LPSTR)GlobalLock (hGtemp);

  // Zusammenstellen aller Daten
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) buffer ;
  hd->progOffs = sizeof(inlinefnc_header) + parSize ;
  hd->progSize = fncSize ;
  hd->LookupList = _actcmpl->actFncLookup ;
  _actcmpl->actFncLookup   = 0;
  hd->ExpLookupList = _actcmpl->actExpFncLookup ;
  _actcmpl->actExpFncLookup = 0 ;
  hd->LocalLookup = _actcmpl->actLocalLookup ;
  _actcmpl->actLocalLookup = 0;
  hd->LocalExpLookup = _actcmpl->actLocalExpLookup;
  _actcmpl->actLocalExpLookup = 0;
  hd->ConstLookup = _actcmpl->actConstLookup ;
  _actcmpl->actConstLookup = 0;
  hd->anzPars    = anzinlinepars;
  hd->ExpressionLookup = _actcmpl->actExpressionLookup;
  _actcmpl->actExpressionLookup = 0;

  // Expressions
  if (_actcmpl->hGInlineExpPtr) {
    // Es gibt Exprssions in dieser Funktion
    LPSTR Buffer = (LPSTR)GlobalLock (_actcmpl->hGInlineExpPtr);
    ExpPtr FAR * e = (ExpPtr FAR *) (Buffer + sizeof(WORD));
    hd->AnzExpressions = *((WORD FAR *) Buffer);
    hd->ExpPtrs = (ExpPtr FAR *) GetGlobMem (hd->AnzExpressions * sizeof(*hd->ExpPtrs));
    PushNPtr (hd->ExpPtrs);
    lmemcpy (hd->ExpPtrs,e,hd->AnzExpressions * sizeof(*hd->ExpPtrs));
    GlobalUnlock (_actcmpl->hGInlineExpPtr);
    GlobalFree (_actcmpl->hGInlineExpPtr);
    _actcmpl->hGInlineExpPtr = 0;

    // Und noch die Expressions hinten Einfuegen
    Buffer = (LPSTR)GlobalLock (_actcmpl->hGInlineExpBuffer);
    hd->ExpSize = WORD (*((DWORD FAR *) Buffer) - sizeof(DWORD));
    hd->ExpBuffer = GetGlobMem (hd->ExpSize);
    PushNPtr (hd->ExpBuffer);
    lmemcpy (hd->ExpBuffer,Buffer + sizeof(DWORD),hd->ExpSize);
    GlobalUnlock (_actcmpl->hGInlineExpBuffer);
    GlobalFree (_actcmpl->hGInlineExpBuffer);
    _actcmpl->hGInlineExpBuffer = 0;

    // Zeiger aus Expressions von Expressions aus
    if (_actcmpl->hGInlineExpOffs) {
      Buffer = (LPSTR)GlobalLock (_actcmpl->hGInlineExpOffs);
      hd->AnzExpOffs = WORD (*((DWORD FAR *) Buffer) / sizeof(DWORD)) - 1;
      hd->ExpOffs = (DWORD FAR *) GetGlobMem (hd->AnzExpOffs * sizeof(DWORD));
      PushNPtr (hd->ExpOffs);
      lmemcpy (hd->ExpOffs,Buffer + sizeof(DWORD),hd->AnzExpOffs * sizeof(DWORD));
      GlobalUnlock (_actcmpl->hGInlineExpOffs);
      GlobalFree (_actcmpl->hGInlineExpOffs);
      }
    else {
      hd->AnzExpOffs = 0;
      hd->ExpOffs = NULL;
      }

    }
  else {
    hd->AnzExpressions = 0;
    hd->ExpSize = 0;
    hd->ExpPtrs = NULL;
    hd->ExpBuffer = NULL;
    hd->ExpOffs = NULL;
    }

  lmemcpy (hd + 1,inlinefncpar,parSize);
  lmemcpy (buffer + hd->progOffs,fncbuffer + sizeof(DWORD),fncSize);

  // Und ab in die Hashtabelle damit
  hash *h = _actcmpl->FixlFHash ();
  h->SetData (inlinename,buffer,gessize);
  _actcmpl->ReleaselFHash ();

  // fertig
  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);

  GlobalUnlock (_actcmpl->codebuffer[_actcmpl->level]);
  _actcmpl->Clear();

  // Parameterhashtabelle muss geloescht werden
  h = _actcmpl->FixlPHash ();
  delete h;
  _actcmpl->hlPHash = NULL;
  }

DWORD compiler::fncOffs()
  {
  DWORD Offs = 0 ;
  for (int i = level ; i >= _actcmpl->startlevel ; i--) {
    DWORD ActSize;
    if (codebuffer[i]) {
      LPSTR buffer = (LPSTR)GlobalLock (codebuffer[i]);
      ActSize = *((DWORD FAR *) buffer);
      }
    else ActSize = sizeof(DWORD);
    Offs += ActSize ;
    if (IsCondBuffer(i)) Offs -= sizeof(DWORD);
    if (IsProcBuffer(i)) Offs += sizeof(DWORD);
    }
  Offs += sizeof (vardef);
  Offs -= sizeof(DWORD) + 2 * sizeof(WORD);
  return Offs;
  }

void ScriptCompiler::MarkInlineforLookup (WORD Ident)
  {
  dList l(&actLocalLookup);
  l[Ident] += fncOffs() - sizeof(vardef);
  }

void ScriptCompiler::MarkInlineforLookup (DWORD Offset,WORD Ident)
  {
  dList l(&actLocalLookup);
  l[Ident] += Offset;
  }

void ScriptCompiler::PushInlineExpId (DWORD Offset,WORD Ident)
  {
  dList l(&actLocalExpLookup);
  l[Ident] += Offset;
  }

void ScriptCompiler::MarkExpInlineForLookup ()
  {
  eList l(&actExpressionLookup);
  l += fncOffs() - sizeof(sizeof(vardef));
  }

void ScriptCompiler::MarkExpInlineForLookup (DWORD Offs)
  {
  eList l(&actExpressionLookup);
  l += Offs;
  }

void ScriptCompiler::MarkInlineForConstbinding (DWORD Offs)
  {
  eList l(&actConstLookup);
  l += Offs ;
  }

#define MAXBSPSTRLEN  20
void pushfncpar ()
  {
  _actcmpl->pushfncpar ();
  }

void ScriptCompiler::pushfncpar ()
  {
  int size ;
  DWORD Offset;

  char writebuffer[8];
  for (int i = 0 ; i < sizeof(writebuffer) ; i++) {
    writebuffer[i] = LOBYTE (TESTBYTE+i);
    }

  if (actpar > parcount)
    wError = PARERROR ;
  else {
    char FAR *base = (LPSTR)GlobalLock (hPars1) ;
    pardsc FAR *pdsc = ((pardsc FAR *) base) + actpar ;

    Offset = fncOffs () ;

    if ((pdsc->par_kind == PAR_FREE) || 
        ((pdsc->par_kind == PAR_VAR) && (scv.v.pd.pd.par_kind == PAR_VAR) &&
         (pdsc->Extra == scv.v.pd.pd.Extra)) ||
        (pdsc->par_kind == scv.v.pd.pd.par_kind)) {
      switch (scv.v.pd.pd.par_kind) {
        case PAR_VAR :
          pushData (writebuffer,sizeof (vardef));
          size = sizeof(vardef);
          break ;
        case PAR_LONG :
          pushData (writebuffer,sizeof (LONG));
          size = sizeof(LONG);
          break ;
        case PAR_DEC :
          pushData (writebuffer,sizeof (float));
          size = sizeof(float);
          break ;
        default :
          // Strings werden nicht verarbeitet !!!!!
          wError = PARERROR ;
        }
      }
    else wError = PARERROR ;

    if (wError == 0) {
      // Eintragen des Parameters fuer spaeteren Lookup
      dList d(&actFncLookup);
      d[scv.v.pd.Number] += Offset ;

      if (pdsc->par_kind != PAR_FREE) actpar ++ ;
      // Eintragen der Laenge des Parameterblockes
      char FAR *h = FixBuffer ();
      * (WORD FAR *) ((char _huge *) h + parlenoffs) += size;
      ReleaseBuffer () ;
      }
    GlobalUnlock (hPars1);
    }
  }

void ScriptCompiler::pushfncExpPar (WORD Number,DWORD Offset)
  {
  // Eintragen des Parameters in den Expressions fuer spaeteren Lookup
  dList d(&actExpFncLookup);
  d[Number] += Offset ;
  }

extern void FAULT();

void CorrectExpOffsets (LPVOID ListData,LPVOID progData)
  {
  DWORD ProgOffs = *((DWORD FAR *) progData) ;
  DWORD Offset = * ((DWORD FAR *) ListData) + ((DWORD FAR *) progData)[0] ;
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->hProgCopy);
  vardef FAR *r = (vardef FAR *) (buffer + Offset);
  if ((r->DBNummer & 0xFF00) == 0xEF00) {
    DWORD h = MAKELONG(r->Ident,r->DBNummer & 0x00FF);
    h += ((DWORD FAR *) progData)[1] ;
    r->DBNummer = HIWORD(h) | 0xEF00;
    r->Ident = LOWORD(h);
    }
  else
    FAULT ();
  GlobalUnlock (_actcmpl->hProgCopy);
  }

void makeprogcopy ()
  {
  // in hPars0 steht ein inlinefnc_header. Von dem Programm soll eine
  // Kopie angelegt werden, die Expressions werden direkt in den Expression
  // Buffer gelegt
  int i,j;
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->CheckSegs (hd->progSize * _actcmpl->loop_count);
  _actcmpl->hProgCopy = GlobalAlloc (GHND,hd->progSize * _actcmpl->loop_count);
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->hProgCopy);
  for (i = 0 ; i < _actcmpl->loop_count ; i++)
    lmemcpy (buffer + i * hd->progSize,LPSTR(hd) + hd->progOffs,hd->progSize);

  if (hd->ExpSize > 0) {
    // Auch noch 
    for (i = 0 ; i < _actcmpl->loop_count ; i++) {
      LPSTR h = LPSTR (hd->ExpBuffer);
      DWORD Offset = _actcmpl->ExpSize ();
      for (j = 0 ; j < int (hd->AnzExpressions) ; j++) {
        _actcmpl->pushExpression (h,hd->ExpPtrs[j].wSize);
        h += hd->ExpPtrs[j].wSize;
        }
      for (j = 0 ; j < int (hd->AnzExpOffs) ; j++) {
        // Korrigieren der Expression Zeiger
        char _huge * ExpBuffer = (char _huge *) GlobalLock (_actcmpl->hGExpBuffer);
        DWORD rOffs = Offset + hd->ExpOffs[j];
        vardef FAR *h = (vardef FAR *) (ExpBuffer + sizeof(DWORD) + rOffs);
        if ((h->DBNummer & 0xFF00) == 0xEF00) {
          DWORD d = MAKELONG(h->Ident,h->DBNummer & 0x00FF);
          d += Offset ;
          h->DBNummer = HIWORD(d) | 0xEF00 ;
          h->Ident = LOWORD(d);
          _actcmpl->pushExpExpPtr (rOffs);
          }
        else 
          FAULT ();
        GlobalUnlock (_actcmpl->hGExpBuffer);
        }
      // Zeiger auf Expressions von der Inlinefunktion aus
      secondListEle FAR *ExpressionLookup = hd->ExpressionLookup;
      DWORD ProgOffset = _actcmpl->loop_ind * hd->progSize ;
      DWORD progData[2] ;
      progData[0] = ProgOffset - sizeof(WORD);
      progData[1] = Offset;
      eList l(&ExpressionLookup);
      l.Traverse (CorrectExpOffsets,progData);
      }
    }

  // fertig
  GlobalUnlock (_actcmpl->hProgCopy);
  GlobalUnlock (_actcmpl->hPars1);
  }

void startInlineCall ()
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->parcount = hd->anzPars;
  _actcmpl->actpar = 0;
  _actcmpl->loop_ind = 0;
  if (_actcmpl->loop_count == -1)
    _actcmpl->loop_count = 1;
  GlobalUnlock (_actcmpl->hPars1);
  }

void pushprog ()
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  pardsc FAR *pdsc = ((pardsc FAR *) (hd + 1)) + _actcmpl->actpar ;
  if (_actcmpl->actpar < _actcmpl->parcount)
    _actcmpl->wError = PARERROR ;

  // Alle Daten sind up to date, die Kopie kann in das Hauptprogramm
  // eingefuegt werden
  _actcmpl->CheckSegs ();

  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->hProgCopy);

  // Die intern verwendeten Konstanten und Variablen muessen noch
  // up to daten gebracht werden
  _actcmpl->FixupUsedLocals ();
  _actcmpl->FixupUsedExpressions ();
  _actcmpl->FixupUsedConstants ();
  _actcmpl->FixupUsedExpLocals ();

  // und ab ins Hauptprogramm.....
  _actcmpl->pushData (buffer,hd->progSize * _actcmpl->loop_count);

  // fertig
  GlobalUnlock (_actcmpl->hPars1);
  GlobalUnlock (_actcmpl->hProgCopy);
  GlobalFree (_actcmpl->hProgCopy);
  _actcmpl->hProgCopy = 0 ;
  _actcmpl->loop_count = -1 ;
  }

void FixupInProg (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) listdata) + 
                      _actcmpl->loop_ind * hd->progSize;
  int Size = * ((int FAR *) progdata) ;
  LPSTR data = LPSTR (progdata) + sizeof(int);
  char _huge * prog = (LPSTR)GlobalLock (_actcmpl->hProgCopy);
  // Check, ob dort, wo die Daten hingeschrieben werden muessen, auch
  // wirklich Nullen sind
  for (int i = 0 ; i < Size ; i++) {
    if (prog[Offset + i] != char (LOBYTE (TESTBYTE + i))) {
      _actcmpl->wError = INLINELOOKUPERROR ;
      break ;
      }
    }
  // Daten reinschreiben
  hmemcpy (prog+Offset,data,Size);

  // Der waere mal geschafft
  GlobalUnlock (_actcmpl->hProgCopy);
  GlobalUnlock (_actcmpl->hPars1);
  }

void FixupInExp (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) listdata) + 
                      _actcmpl->loop_ind * hd->ExpSize +
                      _actcmpl->ExpSize () - 
                      _actcmpl->loop_count * hd->ExpSize;
  int Size = * ((int FAR *) progdata) ;
  LPSTR data = LPSTR (progdata) + sizeof(int);
  char _huge * exp = (LPSTR)GlobalLock (_actcmpl->hGExpBuffer);
  // Check, ob dort, wo die Daten hingeschrieben werden muessen, auch
  // wirklich Nullen sind
  for (int i = 0 ; i < Size ; i++) {
    if (exp[Offset + i] != char (LOBYTE (TESTBYTE + i))) {
      _actcmpl->wError = INLINELOOKUPERROR ;
      break ;
      }
    }
  // Daten reinschreiben
  hmemcpy (exp+Offset,data,Size);

  // Der waere mal geschafft
  GlobalUnlock (_actcmpl->hGExpBuffer);
  GlobalUnlock (_actcmpl->hPars1);
  }

// Lokale Variable in die Lookup - Liste haengen
struct dynamicvar {
  WORD Ident ;
  DWORD progOffset ;
  };
void PushtoLookup (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) listdata) + _actcmpl->loop_ind * hd->progSize ;
  dynamicvar FAR *def = (dynamicvar FAR *) progdata ;
  _actcmpl->PushOffs (def->progOffset + Offset,def->Ident);
  GlobalUnlock (_actcmpl->hPars1);
  }

void PushtoExpLookup (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) listdata) + 
                   _actcmpl->loop_ind * hd->ExpSize +
                   _actcmpl->ExpSize() - 
                   _actcmpl->loop_count * hd->ExpSize +
                   sizeof(WORD);
  dynamicvar FAR *def = (dynamicvar FAR *) progdata ;
  _actcmpl->PushExpId (Offset,def->Ident);
  GlobalUnlock (_actcmpl->hPars1);
  }

// Konstante in die Konstanten - Liste haengen
void PushtoConstlist (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  WORD Offset = * ((WORD FAR *) listdata) + _actcmpl->loop_ind * hd->progSize ;
  DWORD poffs = * ((DWORD FAR *) progdata) ;
  _actcmpl->MarkForConstbinding (poffs + Offset) ;
  GlobalUnlock (_actcmpl->hPars1);
  }

void PushtoExpressionLookup (LPVOID listdata,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  WORD Offset = * ((WORD FAR *) listdata) + _actcmpl->loop_ind * hd->progSize ;
  DWORD poffs = * ((DWORD FAR *) progdata) ;
  _actcmpl->MarkForExpbinding (poffs + Offset) ;
  GlobalUnlock (_actcmpl->hPars1);
  }

// Die Uebergabeparameter in der lokalen Funktion einfuegen
void ScriptCompiler::FixupInlineFnc (int Nmbr,LPVOID data,int Size)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
  firstListEle FAR *FncLookupList = hd->LookupList;
  dList d(&FncLookupList);
  // Vorbereiten des Datenbuffers fuer die Traverse - Function
  char PrivDataBuffer [100];
  * ((int *) PrivDataBuffer) = Size ;
  lmemcpy (PrivDataBuffer+sizeof(int),data,Size);
  d.Traverse (Nmbr,FixupInProg,PrivDataBuffer);

  // Und nun noch die Parameter in den Expressions eintragen
  firstListEle FAR *ExpLookupList = hd->ExpLookupList;
  dList de(&ExpLookupList);
  de.Traverse (Nmbr,FixupInExp,PrivDataBuffer);

  GlobalUnlock (hPars1);
  }

void ScriptCompiler::FixupPar ()
  {
  LPVOID data;
  vardef constvd ;
  int size ;
  if (actpar > parcount)
    wError = PARERROR ;
  else {
    inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
    pardsc FAR *pdsc = ((pardsc FAR *) (hd + 1)) + actpar ;
    switch (scv.type) {
      case T_INTEGER :
        if (pdsc->par_kind == PAR_LONG)
          data = &scv.v.int_val ,
          size = sizeof (LONG) ;
        else if (pdsc->par_kind == PAR_FREE) {
          // Defaultmaessig wird ein short int angenommen
          setconstind ();
          vardef constvd ;
          constvd.DBNummer = 2 ;
          constvd.Ident = _actcmpl->constOffs ;   
          data = &constvd;
          size = sizeof(vardef);
          }
        else if ((pdsc->par_kind == PAR_VAR) && 
                  ((pdsc->Extra == VAR_STRARR) || (pdsc->Extra == VAR_LONG) || (pdsc->Extra == VAR_FLAG))) {
          switch (pdsc->Extra) {
            case VAR_STRARR :
              setconstind ();
              break ;
            case VAR_LONG :
              setconstdword ();
              break ;
            case VAR_QLONG :
              setconstqword ();
              break ;
            case VAR_FLAG :
              setconstflag ();
              break ;
            }
          constvd.DBNummer = 2 ;
          constvd.Ident = _actcmpl->constOffs ;   
          data = &constvd;
          size = sizeof(vardef);
          }
        else wError = PARERROR ;
        break ;
      case DECIMAL :
        if (pdsc->par_kind == PAR_DEC)
          data = &scv.v.float_val,
          size = sizeof (float) ;
        else if (((pdsc->par_kind == PAR_VAR) && (pdsc->Extra == VAR_DEC)) || (pdsc->par_kind == PAR_FREE)) {
          setconstdec ();
          constvd.DBNummer = 2 ;
          constvd.Ident = _actcmpl->constOffs ;   
          data = &constvd;
          size = sizeof(vardef);
          }
        else wError = PARERROR ;
        break ;
      case VARID :
        if ((pdsc->par_kind == PAR_VAR) && 
                        (pdsc->Extra == scv.v.vd.vartype)) {
          vardef h = scv.v.vd.vd ;
          if ((scv.v.vd.vartype != VAR_PICTURE) && (scv.v.vd.vartype != VAR_BITMAP))
            TransformTableID(&h,scv.v.vd.TableNr);
          data = &h ;
          size = sizeof (vardef) ;
          if (scv.v.vd.isdynamic) {
            // Alle Referenzierungen dieser Variable muessen in den 
            // Progbuffer getan werden
            dynamicvar dv;
            dv.Ident = scv.v.vd.vd.Ident ;
            dv.progOffset = ActOffs ();
            firstListEle FAR *FncLookupList = hd->LookupList;
            dList d(&FncLookupList);
            for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
              d.Traverse (actpar,PushtoLookup,&dv);
            firstListEle FAR *ExpFncLookupList = hd->ExpLookupList;
            dList de(&ExpFncLookupList);
            for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
              de.Traverse (actpar,PushtoExpLookup,&dv);
            }
          }
        else wError = PARERROR ;
        break ;
      }
    if (wError == 0) {
      for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
        FixupInlineFnc (actpar,data,size);
      actpar++ ;
      }
    GlobalUnlock (hPars1);
    }
  }

void ScriptCompiler::FixupEnumPar ()
  {
  LPVOID data = NULL;
  int size ;
  vardef h;
  if (actpar > parcount)
    wError = PARERROR ;
  else {
    inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
    pardsc FAR *pdsc = ((pardsc FAR *) (hd + 1)) + actpar ;
    enumheader FAR *eh = (enumheader FAR *) GlobalLock (hPars2);
    DWORD ActOffset = ActOffs ();
    if (eh->AnzVars != loop_count)
      wError = ENUMVARSIZE ;
    for (loop_ind = 0 ; ((loop_ind < loop_count) && (wError == 0)) ; loop_ind ++) {
      enumvar FAR *ev = ((enumvar FAR *) (eh + 1)) + loop_ind ;
      switch (pdsc->par_kind) {
        case PAR_LONG :
          if (eh->pd.par_kind == PAR_LONG) {
            data = &ev->x.l ;
            size = sizeof (LONG) ;
            }
          else wError = PARERROR ;
          break ;
        case PAR_DEC :
          if (eh->pd.par_kind == PAR_DEC) {
            data = &ev->x.f;
            size = sizeof (float) ;
            }
          else wError = PARERROR ;
          break ;
        case PAR_VAR :
          if ((eh->pd.par_kind == PAR_VAR) && 
              (pdsc->Extra == eh->pd.Extra)) {
            if (ev->par_kind == PAR_VAR) {
              h = ev->x.fvd.vd ;
              if ((ev->x.fvd.vartype != VAR_PICTURE) && (ev->x.fvd.vartype != VAR_BITMAP))
#ifdef ALTE_VERSION
                TransformTableID(&h,_actcmpl->scv.v.vd.TableNr);
#else
                TransformTableID(&h,ev->x.fvd.TableNr);
#endif
              data = &h ;
              size = sizeof (vardef) ;
              if (ev->x.fvd.isdynamic) {
                // Alle Referenzierungen dieser Variable muessen in den 
                // Progbuffer getan werden
                dynamicvar dv;
                dv.Ident = ev->x.fvd.vd.Ident ;
                dv.progOffset = ActOffset ;
                firstListEle FAR *FncLookupList = hd->LookupList;
                dList d(&FncLookupList);
                d.Traverse (actpar,PushtoLookup,&dv);
                firstListEle FAR *ExpFncLookupList = hd->ExpLookupList;
                dList de(&ExpFncLookupList);
                de.Traverse (actpar,PushtoExpLookup,&dv);
                }
              }
            else if (ev->par_kind == PAR_CONSTVAR) {
              data = &ev->x.fvd.vd ;
              size = sizeof (vardef) ;
              firstListEle FAR *FncLookupList = hd->LookupList;
              dList c(&FncLookupList);
              c.Traverse (actpar,PushtoConstlist,&ActOffset);
              }
            else wError = PARERROR ;
            }
          else wError = PARERROR ;
          break ;
        default :
          wError = PARERROR ;
        }       // for looo_ind ...
      // Und rein mit den Daten
      if (data == NULL) wError = PARERROR ;
      if (wError == 0)
        FixupInlineFnc (actpar,data,size);
      else
        break ;
      }
    if (wError == 0) {
      actpar++ ;
      }
    GlobalUnlock (hPars2);
    GlobalUnlock (hPars1);
    }
  }

void ScriptCompiler::FixupEnumEle ()
  {
  LPVOID data;
  int size ;
  if (actpar > parcount)
    wError = PARERROR ;
  else {
    inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
    pardsc FAR *pdsc = ((pardsc FAR *) (hd + 1)) + actpar ;
    enumheader FAR *eh = (enumheader FAR *) GlobalLock (hPars2);
    if (eh->AnzVars != loop_count)
      wError = ENUMVARSIZE ;
    int actind = int(_actcmpl->scv.v.int_val) ;
    DWORD ActOffset = ActOffs ();
    for (loop_ind = 0 ; ((loop_ind < loop_count) && (wError == 0)) ; loop_ind ++) {
      enumvar FAR *ev = ((enumvar FAR *) (eh + 1)) + actind ;
      switch (pdsc->par_kind) {
        case PAR_LONG :
          if (eh->pd.par_kind == PAR_LONG) {
            data = &ev->x.l ;
            size = sizeof (LONG) ;
            }
          else wError = PARERROR ;
          break ;
        case PAR_DEC :
          if (eh->pd.par_kind == PAR_DEC) {
            data = &ev->x.f;
            size = sizeof (float) ;
            }
          else wError = PARERROR ;
          break ;
        case PAR_VAR :
          if ((eh->pd.par_kind == PAR_VAR) && 
              (pdsc->Extra == eh->pd.Extra)) {
            if (ev->par_kind == PAR_VAR) {
              data = &ev->x.fvd.vd ;
              size = sizeof (vardef) ;
              if (ev->x.fvd.isdynamic) {
                // Alle Referenzierungen dieser Variable muessen in den 
                // Progbuffer getan werden
                dynamicvar dv;
                dv.Ident = ev->x.fvd.vd.Ident ;
                dv.progOffset = ActOffset ;
                firstListEle FAR *FncLookupList = hd->LookupList;
                dList d(&FncLookupList);
                d.Traverse (actpar,PushtoLookup,&dv);
                firstListEle FAR *ExpFncLookupList = hd->ExpLookupList;
                dList de(&ExpFncLookupList);
                de.Traverse (actpar,PushtoExpLookup,&dv);
                }
              }
            else if (ev->par_kind == PAR_CONSTVAR) {
              data = &ev->x.fvd.vd ;
              size = sizeof (vardef) ;
              firstListEle FAR *FncLookupList = hd->LookupList;
              dList c(&FncLookupList);
              c.Traverse (actpar,PushtoConstlist,&ActOffset);
              }
            else wError = PARERROR ;
            }
          else wError = PARERROR ;
          break ;
        }       // for looo_ind ...
      // Und rein mit den Daten
      if (wError == 0)
        FixupInlineFnc (actpar,data,size);
      else
        break ;
      }
    if (wError == 0) {
      actpar++ ;
      }
    GlobalUnlock (hPars2);
    GlobalUnlock (hPars1);
    }
  }

void FixupEnumPar ()
  {
  _actcmpl->FixupEnumPar ();
  }

void FixupEnumEle ()
  {
  _actcmpl->FixupEnumEle ();
  }

void FixupPar ()
  {
  _actcmpl->FixupPar ();
  }

void ScriptCompiler::FixupConstPar ()
  {
  LPVOID data;
  vardef constvd ;
  int size ;
  if (actpar > parcount)
    wError = PARERROR ;
  else {
    inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
    pardsc FAR *pdsc = ((pardsc FAR *) (hd + 1)) + actpar ;
    if ((pdsc->par_kind == PAR_VAR) && (pdsc->Extra == _actcmpl->constType)) {
      constvd.DBNummer = 2 ;
      constvd.Ident = _actcmpl->constOffs ;
      data = &constvd ;
      size = sizeof (vardef) ;
      // Konstante(n) in die Konstantenliste einhanegen
      DWORD actprogOffset = ActOffs ();
      firstListEle FAR *FncLookupList = hd->LookupList;
      dList d(&FncLookupList);
      for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
        d.Traverse (actpar,PushtoConstlist,&actprogOffset);
      }
    else wError = PARERROR ;

    if (wError == 0) {
      for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
        FixupInlineFnc (actpar,data,size);
      actpar++ ;
      }
    GlobalUnlock (hPars1);
    }
  }

void FixupConstPar ()
  {
  _actcmpl->FixupConstPar ();
  }

void PushLocal (WORD Ident,LPVOID ListData,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) ListData) + _actcmpl->loop_ind * hd->progSize ;
  _actcmpl->PushOffs (*((DWORD FAR *) progdata) + Offset,Ident);
  GlobalUnlock (_actcmpl->hPars1);
  }

void PushExpLocal (WORD Ident,LPVOID ListData,LPVOID progdata)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) ListData) + _actcmpl->loop_ind * hd->ExpSize ;
  _actcmpl->PushExpId (*((DWORD FAR *) progdata) + Offset,Ident);
  GlobalUnlock (_actcmpl->hPars1);
  }

void ScriptCompiler::FixupUsedLocals ()
  {
  // alle Lokale Variablen, die in der Inline - Funktion verwendet wurden,
  // muessen noch in die Lookup - Tabelle gebracht werden
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
  firstListEle FAR *LocalLookup = hd->LocalLookup;
  dList d(&LocalLookup);
  DWORD actOffset = ActOffs();
  for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
    d.Traverse (PushLocal,&actOffset);
  GlobalUnlock (hPars1);
  }

void ScriptCompiler::FixupUsedExpLocals ()
  {
  // alle Lokale Variablen, die in der Inline - Funktion verwendet wurden,
  // muessen noch in die Lookup - Tabelle gebracht werden
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
  firstListEle FAR *LocalExpLookup = hd->LocalExpLookup;
  dList d(&LocalExpLookup);
  DWORD actOffset = ExpSize () - _actcmpl->loop_count * hd->ExpSize ;
  for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
    d.Traverse (PushExpLocal,&actOffset);
  GlobalUnlock (hPars1);
  }

void PushConstant (LPVOID ListData,LPVOID progData)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) ListData) + _actcmpl->loop_ind * hd->progSize ;
  _actcmpl->MarkForConstbinding (*((DWORD FAR *) progData) + Offset);
  GlobalUnlock (_actcmpl->hPars1);
  }

void PushExpOffs (LPVOID ListData,LPVOID progData)
  {
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (_actcmpl->hPars1);
  DWORD Offset = * ((DWORD FAR *) ListData) + _actcmpl->loop_ind * hd->progSize ;
  _actcmpl->MarkForExpbinding (* ((DWORD FAR *) progData) + Offset - sizeof(WORD));
  GlobalUnlock (_actcmpl->hPars1);
  }

void ScriptCompiler::FixupUsedConstants ()
  {
  // alle Konstanten, die in der Inline - Funktion verwendet wurden,
  // muessen noch in die Konstanten - Fixup Tabelle gebracht werden
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
  secondListEle FAR *ConstLookup = hd->ConstLookup ;
  eList l(&ConstLookup);
  DWORD actOffset = ActOffs();
  for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
    l.Traverse (PushConstant,&actOffset);
  GlobalUnlock (hPars1);
  }

void ScriptCompiler::FixupUsedExpressions ()
  {
  // alle Konstanten, die in der Inline - Funktion verwendet wurden,
  // muessen noch in die Konstanten - Fixup Tabelle gebracht werden
  inlinefnc_header FAR *hd = (inlinefnc_header FAR *) GlobalLock (hPars1);
  secondListEle FAR *ExpressionLookup = hd->ExpressionLookup ;
  eList l(&ExpressionLookup);
  DWORD actOffset = ActOffs();
  for (loop_ind = 0 ; loop_ind < loop_count ; loop_ind++)
    l.Traverse (PushExpOffs,&actOffset);
  GlobalUnlock (hPars1);
  }

void StoreEnumConstVar (void)
  {
  if ((actenum.pd.par_kind == PAR_VAR) &&
               (actenum.pd.Extra == _actcmpl->constType)) {
    enumvar ev;
    ev.par_kind = PAR_CONSTVAR ;
    ev.x.fvd.vd.DBNummer = 2 ;
    ev.x.fvd.vd.Ident = _actcmpl->constOffs ;
    _actcmpl->pushData (&ev,sizeof(ev));
    actenum.AnzVars ++ ;
    }
  else _actcmpl->wError = PARERROR ;
  }

void StoreEnumInt (void)
  {
  if ((actenum.pd.par_kind == PAR_VAR) && (actenum.pd.Extra == VAR_LONG)) {
    setconstdword ();
    StoreEnumConstVar ();
    }
  else if ((actenum.pd.par_kind == PAR_VAR) && (actenum.pd.Extra == VAR_STRARR)) {
    setconstind ();
    StoreEnumConstVar ();
    }
  else _actcmpl->wError = PARERROR ;
  }

void StoreEnumDec (void)
  {
  if ((actenum.pd.par_kind == PAR_VAR) && (actenum.pd.Extra == VAR_DEC)) {
    setconstdec();
    StoreEnumConstVar ();
    }
  else _actcmpl->wError = PARERROR ;
  }

void ScriptCompiler::StoreEnumVar (void)
  {
  if ((actenum.pd.Extra == scv.v.vd.vartype) && 
        (actenum.pd.par_kind == PAR_VAR)) {
    enumvar ev;
    ev.par_kind = PAR_VAR ;
    lmemcpy (&ev.x.fvd,&scv.v.vd,sizeof(full_vardef));
    pushData (&ev,sizeof(ev));
    actenum.AnzVars ++ ;
    }
  else wError = PARERROR ;
  }

void StoreEnumVar (void)
  {
  _actcmpl->StoreEnumVar ();
  }

void storeenum (void)
  {
  // Im Buffer noch die aktuelle AnzVars eintragen
  LPSTR buffer = _actcmpl->FixBuffer ();
  lmemcpy (buffer + sizeof(DWORD),&actenum,sizeof(actenum));
  // Und ab in die Datenbank
  hash *h = _actcmpl->FixenHash ();
  h->SetData (inlinename,buffer+sizeof(DWORD),
                actenum.AnzVars * sizeof(enumvar) + sizeof(enumheader));
  _actcmpl->ReleaseenHash ();
  _actcmpl->ReleaseBuffer ();
  _actcmpl->Clear ();
  }

void storeenumtype (void)
  {
  // Im aktuellen Codebuffer steht die aktuelle pardsc
  LPSTR buffer = _actcmpl->FixBuffer ();
  lmemcpy (&actenum.pd,buffer + sizeof(DWORD),sizeof(pardsc));
  if ((actenum.pd.par_kind == PAR_VAR) ||
      (actenum.pd.par_kind == PAR_LONG) ||
      (actenum.pd.par_kind == PAR_DEC)) {
    // Fertig -> Buffer wieder loeschen
    _actcmpl->ReleaseBuffer();
    _actcmpl->Clear ();
    inclevel ();
    // Den Header vorbereiten
    actenum.AnzVars = 0;
    _actcmpl->pushData (&actenum,sizeof(actenum));  // Damit Platz fuer den Kopf
                                        // vorhanden ist
    }
  else
    _actcmpl->wError = SEM_ERROR ;
  }

void setloopcount (void)
  {
  // In hPars2 steht die enum - Daten
  enumheader FAR *eh = (enumheader FAR *) GlobalLock (_actcmpl->hPars2);
  if (_actcmpl->loop_count == -1)
    _actcmpl->loop_count = eh->AnzVars ;
  else if (_actcmpl->loop_count != eh->AnzVars)
    _actcmpl->wError = ENUMVARSIZE ;
  GlobalUnlock (_actcmpl->hPars2);
  }

DLLExport BOOL _export WINAPI ScriptCompiler::IsCondBuffer (int i)
  {
  return ((bCondBuffer[i] & IS_CONDITION) != 0);
  }

DLLExport BOOL _export WINAPI ScriptCompiler::IsProcBuffer (int i)
  {
  return ((bCondBuffer[i] & IS_PROCEDURE) != 0);
  }

void compiler::SetupLists ()
  {
  if ((_actcmpl != NULL) && (this == _actcmpl)) {
    _actcmpl->ActFreeVar = 0;
    _actcmpl->ActFreeHVar = 0;
    _actcmpl->ConstOffsList = NULL ;
    _actcmpl->actFncLookup = NULL ;
    _actcmpl->actExpFncLookup = NULL ;
    _actcmpl->actLocalLookup = NULL ;
    _actcmpl->actLocalExpLookup = NULL ;
    _actcmpl->actConstLookup = NULL;
    _actcmpl->hGConstOffsMem = 
    _actcmpl->hGLookupmem = 
    _actcmpl->hProgCopy = NULL;
    }
  }

struct BorderBuffer {
  DWORD startOffset;
  DWORD endOffset;
  };

void CorrectIdentOffset(WORD Nmbr,LPVOID Data,LPVOID progData)
  {
  BorderBuffer FAR *lpbb = (BorderBuffer FAR *) progData;
  DWORD FAR *Offset = (DWORD FAR *)Data;
  if ((*Offset >= lpbb->startOffset) && (*Offset < lpbb->endOffset)) {
    *Offset += sizeof(WORD) + sizeof(DWORD);
    }
  }

void ScriptCompiler::CorrectIdentOffsets(DWORD start,DWORD end)
  {
  dList d(&actFncLookup);
  BorderBuffer bb;
  bb.startOffset = start;
  bb.endOffset = end;
  d.Traverse (CorrectIdentOffset,&bb);
  }

void setsingleent ()
  {
  _actcmpl->Category = CATEGORY_SENTER;
  }

void setmpent ()
  {
  _actcmpl->Category = CATEGORY_MPENTER;
  }

void setsubcat ()
  {
  _actcmpl->Category |= (_actcmpl->scv.v.int_val & 0x0FFF);
  }

void storeiconfile ()
  {
  char FAR *txt = (LPSTR)GlobalLock (_actcmpl->hPars0);
  lstrncpy (_actcmpl->IconName,txt+sizeof(WORD),sizeof (_actcmpl->IconName));
  GlobalUnlock (_actcmpl->hPars0);
  }

void markExportKontext ()
  {
  if (_actcmpl->ImportDone)
    _actcmpl->wError = PROGISIMPORTED;
  }

void GetOpHash (GLOBALHANDLE hGmem,hash *res,LPSTR Prefix,int nFType,LPSCRIPTCONTENT sc);
extern LPVOID PushToGlobMem (LPVOID old,LPVOID data,int size);
void SetOpHash (LPSCRIPTCONTENT scent,WORD Ftype)
  {
  if (scent != NULL) {
    if (scent->ExportTypeSize) {
      GLOBALHANDLE hGmem = GlobalAlloc (GMEM_MOVEABLE,scent->ExportTypeSize);
      LPSTR Base = LPSTR (GlobalLock (hGmem));
      hmemcpy (Base,scent->ExportDef,scent->ExportTypeSize);
      GetOpHash (hGmem,_actcmpl->hefHash,"",Ftype,scent);
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    else
      _actcmpl->wError = NOIMPORTSCRIPT ;
    }
  else
    _actcmpl->wError = PROGNOTFOUND ;
  }

extern HWND GetActParent ();
LPSCRIPTCONTENT TryToGetEntry (LPSTR fname)
  {
  LoadScriptContent();
  LPSCRIPTCONTENT lpscent = GetScriptEntry(fname);
  if (lpscent != NULL) return lpscent ;

  // Nachgenerieren des Moduls
  ScriptCompiler FAR *last = _actcmpl ;
  ScriptContent_Entry oldscent = scent;
  char name[128],_xname[128];
  GetIncludeFileName (fname,name,_xname,"source");
  BOOL res = DoCompileMod (GetActParent(),name);
  if (res == 0)
    CreateScriptContent(fname);
  _actcmpl = last ;
  if (res != 0)
    _actcmpl->wError = ERRORINIMPORTED;
  scent = oldscent ;
  return GetScriptEntry(fname);
  }

void importKontext ()
  {
  char FAR *fname = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  _actcmpl->MyImportModules = PushToGlobMem (_actcmpl->MyImportModules,fname,lstrlen(fname) + 1);
  GlobalUnlock (_actcmpl->hPars0);
  LPSCRIPTCONTENT sc = TryToGetEntry (fname);
  if (_actcmpl->wError != ERRORINIMPORTED)
    SetOpHash (sc, FTYPE_IMPORT);
  }

void ImportBaseModules (LPSCRIPTCONTENT sc,WORD Ftype)
  {
  SetOpHash (TryToGetEntry (sc->fName),Ftype); //??? Wozu TryToGetEntry? Wenn nicht in sc, sowieso PATSCH!
  LPSTR h = sc->BaseModules ;
  if (h != NULL) {
    for ( LPSTR x = h ; *x ; x += lstrlen (x) + 1 ) {
      LPSCRIPTCONTENT lpscent = GetScriptEntry(x);
      ImportBaseModules (lpscent,Ftype);
      }
    }
  }

void SetBaseModule ()
  {
  char FAR *fname = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  _actcmpl->MyBaseModules = PushToGlobMem (_actcmpl->MyBaseModules,fname,lstrlen(fname) + 1);
  GlobalUnlock (_actcmpl->hPars0);
  LPSCRIPTCONTENT sc = TryToGetEntry (fname);
  if (sc != NULL) 
    ImportBaseModules (sc,FTYPE_DECLARE);
  else if (_actcmpl->wError != ERRORINIMPORTED)
    _actcmpl->wError = PROGNOTFOUND;
  }

void SetVirtualModule ()
  {
  char FAR *fname = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  _actcmpl->MyVirtualModules = PushToGlobMem (_actcmpl->MyVirtualModules,fname,lstrlen(fname) + 1);
  GlobalUnlock (_actcmpl->hPars0);
  LPSCRIPTCONTENT sc = TryToGetEntry (fname);
  if (sc != NULL) 
    ImportBaseModules (sc,FTYPE_VIRTUAL);
  else if (_actcmpl->wError != ERRORINIMPORTED)
    _actcmpl->wError = PROGNOTFOUND;
  }

void setabort ()
  {
  WORD cmd = PREFIX_ABORT ;
  _actcmpl->pushData (&cmd,sizeof (cmd));
  }

void SetProperty()
  {
  LPSTR r = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD) ;
  _actcmpl->PropertyString = LPSTR (GetGlobMem (lstrlen(r)+1)) ;
  lstrcpy (_actcmpl->PropertyString,r);
  GlobalUnlock (_actcmpl->hPars0) ;
  }

char huge * structStart;
LPSTR StructName;
void MarkStructStart ()
  {
  structStart = _actcmpl->actptr - 6;
  _actcmpl->dontCheckDouble = TRUE;
  }

void MarkViewStart ()
  {
  structStart = _actcmpl->actptr - 4;
  _actcmpl->dontCheckDouble = TRUE;
  }

void MarkStructName ()
  {
  LPSTR r = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  StructName = LPSTR(GetGlobMem (lstrlen(r) + 1));
  lstrcpy (StructName,r);
  GlobalUnlock (_actcmpl->hPars0);
  }

GENSTRUCT GenStruct;
GENVIEW GenView;
DLLExport void _export WINAPI SetGenStruct (GENSTRUCT gs)
  {
  GenStruct = gs;
  }

DLLExport void _export WINAPI SetGenView (GENVIEW gv)
  {
  GenView = gv;
  }

extern void SetTableName_extern (LPSTR StructName);
void GenerateStruct ()
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID(NULL,StructName,&found,&Version);
  if (!found) {
    char huge *structEnd = _actcmpl->actptr;
    DWORD Size = structEnd - structStart;
    GLOBALHANDLE hGmem = GlobalAlloc (GHND,Size + 1);
    LPSTR Buffer = (LPSTR)GlobalLock (hGmem);
    hmemcpy (Buffer,structStart,Size);
    Buffer[Size] = '\0';
    LPSTR fmname = _actcmpl->fmname ;
    ScriptCompiler FAR *act = _actcmpl;
    _actcmpl = NULL ;
    BOOL res = (* GenStruct) (fmname,Buffer,act->actFPrefix) ;
    _actcmpl = act;
    if (!res) _actcmpl->wError = SYNTAX_ERROR ;
    else {
      char myStructName [64];
      lstrcpy (myStructName,act->actFPrefix);
      lstrcat (myStructName,StructName);
      SetTableName_extern (myStructName);
      UseTable ();
      FreeGlobMem (StructName);
      StructName = NULL;
      }
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    _actcmpl->dontCheckDouble = FALSE;
    structStart = NULL ;
    }
  else
    _actcmpl->wError = VARALREADYDEFINED ;
  }

extern BOOL areThereVersions();
extern void UseVersion (LPSTR TableName,WORD Version);
void GenerateView ()
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID(NULL,StructName,&found,&Version);
  if (!found) {
    char huge *structEnd = _actcmpl->actptr;
    DWORD Size = structEnd - structStart;
    GLOBALHANDLE hGmem = GlobalAlloc (GHND,Size + 1);
    LPSTR Buffer = (LPSTR)GlobalLock (hGmem);
    hmemcpy (Buffer,structStart,Size);
    Buffer[Size] = '\0';
    LPSTR fmname = _actcmpl->fmname ;
    ScriptCompiler FAR *act = _actcmpl;
    BOOL wv = areThereVersions();
    _actcmpl = NULL ;
    LPSTR TableNamesForUV[32];
    WORD VersionsForUV[32];
    lmemset (TableNamesForUV,'\0',sizeof(TableNamesForUV));
    BOOL res = (* GenView) (fmname,Buffer,act->actFPrefix,wv,TableNamesForUV,VersionsForUV) ;
    _actcmpl = act;
    for ( int i = 0 ; i < sizeof(TableNamesForUV) / sizeof(TableNamesForUV[0]) ; i++ ) {
      if (TableNamesForUV[i]) {
        UseVersion (TableNamesForUV[i],VersionsForUV[i]);
        FreeGlobMem (TableNamesForUV[i]);
        }
      }
    if (!res) _actcmpl->wError = SYNTAX_ERROR ;
    else {
      char myStructName [64];
      lstrcpy (myStructName,act->actFPrefix);
      lstrcat (myStructName,StructName);
      SetTableName_extern (myStructName);
      UseTable ();
      FreeGlobMem (StructName);
      StructName = NULL;
      }
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    _actcmpl->dontCheckDouble = FALSE;
    structStart = NULL ;
    }
  else
    _actcmpl->wError = VARALREADYDEFINED ;
  }

extern short patchNextType;
void SetNextType ()
  {
  switch (_actcmpl->scv.v.k_ident) {
    case TOSTRING :
      patchNextType = VAR_STR ;
      break ;
    case TOTIME   :
      patchNextType = VAR_TIME ;
      break ;
    case TODATETIME   :
      patchNextType = VAR_DATETIME ;
      break ;
    case TODATE   :
      patchNextType = VAR_DATE ;
      break ;
    case TOFLOAT  :
      patchNextType = VAR_DEC ;
      break ;
    case TOLONG   :
      patchNextType = VAR_LONG ;
      break ;
    case TOSHORT  :
      patchNextType = VAR_STRARR ;
      break ;
    case TOBLOB  :
      patchNextType = VAR_BLOB ;
      break ;
    case TOOBJ  :
      patchNextType = VAR_OBJ ;
      break ;
    case TOFLAG  :
      patchNextType = VAR_FLAG ;
      break ;
    }
  }
