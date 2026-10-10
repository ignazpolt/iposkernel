/*------------------------------------------------------*/
/*      Dokumentenbereich                               */
/*------------------------------------------------------*/
// $Header:   F:/marille/clinicum/rev/form.cpv   1.56   01 May 2000 19:47:20   Hannes  $
// $Log:   F:/marille/clinicum/rev/form.cpv  $
// 
//    Rev 1.56   01 May 2000 19:47:20   Hannes
// Verbesserten Rescale (Ohne doppeltes Abzaehlen der CXVSCROLL)
// 
//    Rev 1.55   19 Apr 2000 15:55:34   Martin
// GetBestWidth: Reserve fuer Scrollbar nur, wenn keine Scrollbar vorhanden!
// 
//    Rev 1.54   11 Apr 2000 01:17:46   Martin
// ActivateTool nur bei Hauptformularen
// 
//    Rev 1.53   12 Aug 1999 08:26:30   Hannes
// SetVeryBestWith ohne nachfolgenden Rescale...
// 
//    Rev 1.52   04 Jun 1999 01:28:18   Hannes
// SetDocVeryBestWidth
// 
//    Rev 1.51   05 Oct 1998 11:54:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.50   20 Jul 1998 17:23:12   Hannes
// Absicherung auf rcScale (GetDocBestSize)
// 
//    Rev 1.49   29 Jun 1998 18:59:22   Hannes
// Nicht ganz so aggresive GetBestWidth
// 
//    Rev 1.48   25 May 1998 13:37:42   Hannes
// 
//    Rev 1.47   17 May 1998 18:19:46   Hannes
// NoAutoscroll
// 
//    Rev 1.46   17 Mar 1998 19:04:42   Hannes
// SetDocBestSize
// 
//    Rev 1.45   18 Feb 1998 10:27:24   Hannes
// Hintergrund loeschen nur auf aktueller Seite
// 
//    Rev 1.44   30 Jan 1998 19:45:06   Hannes
// ToPrinter ... Auch Mit Ausgabecontext
// 
//    Rev 1.43   26 Jan 1998 20:00:34   Hannes
// Skalierung unter 32 Bit Verbessert
// 
//    Rev 1.42   05 Jan 1998 07:53:50   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.41   24 Oct 1997 08:37:20   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.40   08 Sep 1997 10:52:16   Gerhold
// rechte Maustaste fuer Formulare
// 
//    Rev 1.39   26 Aug 1997 17:35:54   Hannes
// WM_VSCROLL -> WMU_VSCROLL
// 
//    Rev 1.38   21 Aug 1997 13:23:44   Hannes
// Division by Zero - Fehler
// 
//    Rev 1.37   18 Aug 1997 18:02:28   Martin
// VTO Formular-faehig
// 
//    Rev 1.36   20 Jun 1997 12:36:04   Hannes
// 
//    Rev 1.35   19 Jun 1997 18:43:32   Martin
// THUMBVAL: 16 Bit restauriert
// 
//    Rev 1.34   19 Jun 1997 16:39:36   Martin
// Schiebelehre in 32 Bit
// 
//    Rev 1.33   19 Jun 1997 15:35:08   Martin
// SBU_THUMBVAL korrigiert
// 
//    Rev 1.32   18 Jun 1997 19:32:10   Martin
// serielle Schiebelehre
// 
//    Rev 1.31   09 Jun 1997 13:10:52   Hannes
// 
//    Rev 1.30   08 Apr 1997 17:47:06   Hannes
// DelActivePen
// 
//    Rev 1.29   19 Feb 1997 12:22:44   Hannes
// 
//    Rev 1.28   06 Dec 1996 18:44:28   HANNES
// 
//    Rev 1.27   03 Dec 1996 16:40:24   HANNES
// 
//    Rev 1.26   26 Nov 1996 08:14:06   HANNES
// Automatischer Update
// 
//    Rev 1.25   08 Nov 1996 13:32:50   HANNES
// 
//    Rev 1.24   04 Apr 1996 18:35:58   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.23   24 Mar 1996 12:08:36   HANNES
// mehrseitige cFields
// 
//    Rev 1.22   22 Mar 1996 12:20:36   GERHOLD
// Aenderungen Hannes
// 
//    Rev 1.21   16 Feb 1996 15:08:22   GERHOLD
// Schiebelehre in #define WIN32
// 
//    Rev 1.20   02 Feb 1996 10:36:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.19   14 Dec 1995 17:03:46   GERHOLD
// Faktor in GetBestWidth von 1.1 auf 1.04 gesetzt (wegen ben.def. Formulare)
// 
//    Rev 1.18   07 Dec 1995 18:24:42   MARTIN
// TerminVarianten fuer STGKK eingebaut
// 
//    Rev 1.17   15 Sep 1995 00:48:18   HANNES
// 
//    Rev 1.16   24 Aug 1995 00:20:22   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.15   10 Aug 1995 09:27:36   HANNES
// ..PrinterOffs ... Positionieren der Formulare auf den Rand
// 
//    Rev 1.14   29 May 1995 12:45:52   HANNES
// ymax auf unsigned gecastet: etwas mehr reserve
// 
//    Rev 1.13   23 May 1995 18:58:06   HANNES
// Rescale ... Anderes Fehlerhandling
// 
//    Rev 1.12   14 Apr 1995 15:38:32   HANNES
// 
//    Rev 1.11   14 Apr 1995 11:31:42   HANNES
// 
//    Rev 1.10   31 Mar 1995 13:09:18   HANNES
//  
// 
//    Rev 1.9   29 Mar 1995 16:22:24   HANNES
// 
//    Rev 1.8   20 Mar 1995 11:56:00   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.7   16 Nov 1994 18:38:56   GERHOLD
// GetDocBestWidth
// 
//    Rev 1.6   03 Nov 1994 15:39:26   GERHOLD
// GetDocInfo ... XUnit, YUnit ausgebessert
// 
//    Rev 1.5   11 Oct 1994 17:03:02   GERHOLD
// GetBestScaling wieder eleminiert
// 
//    Rev 1.4   11 Oct 1994 09:44:04   HANNES
// Einbau einer diskreten Skalierung
// 
//    Rev 1.3   20 Sep 1994 11:34:46   HANNES
// Umstellung auf OutContext
// 
//    Rev 1.2   11 Aug 1994 11:16:34   HANNES
// CallScriptDestuktor im Destruktor
// 
//    Rev 1.1   24 Jun 1994 19:47:32   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:56   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.43   10 Mar 1994 11:25:12   MARTIN
// Palette
// 
//    Rev 1.42   01 Feb 1994 15:17:42   MARTIN
// dc.h und scan.hpp entfernt
// 
//    Rev 1.41   12 Jan 1994 11:07:58   HANNES
// Unnoetige Includes raus, Klasse Text endgueltig eleminiert, ebenso dfield
// 
//    Rev 1.40   04 Jan 1994 16:35:04   HANNES
// N„chste Seite, Vorhergehende Seite mit PageDown, PageUp
// 
//    Rev 1.39   29 Nov 1993 08:50:30   HANNES
// ANZSCROLLS als Define eingefuehrt (aktuell: 20)
// 
//    Rev 1.38   06 Oct 1993 09:51:04   HANNES
// Kleine Aenderungen am Drucken
// 
//    Rev 1.37   04 Oct 1993 09:40:00   HANNES
// Verbesserung des Rescale, MapChanged in Scrollhorizontal, ScrollVertical
// 
//    Rev 1.36   22 Sep 1993 09:17:54   HANNES
// Version nach St. Poelten
// 
//    Rev 1.35   05 Sep 1993 22:15:28   HANNES
// Aufraeumbeiten
// 
//    Rev 1.34   23 Aug 1993 19:04:56   MARTIN
// Image-Umstellung (alte Sachen ausgemistet)
// 
//    Rev 1.33   18 Aug 1993 11:39:38   HANNES
// NextField
// 
//    Rev 1.32   18 Aug 1993 10:28:28   HANNES
// Endgueltiger Umbau auf Tools
// 
//    Rev 1.31   05 Aug 1993 13:07:04   HANNES
// SwitchToNextField, SwitchToPrevField in mdiChild verlagert
// 
//    Rev 1.30   15 Jul 1993 16:35:58   HANNES
// Drucker in die DMWAPI ausgelagert
// 
//    Rev 1.29   05 Jul 1993 14:39:40   HANNES
// Einbindung der Tools
// 
//    Rev 1.28   23 Jun 1993 11:25:34   HANNES
// Neuzeichnen nach dem Drucken
// 
//    Rev 1.27   18 Jun 1993 15:13:46   MARTIN
// Prototzp von GetData
// 
//    Rev 1.26   17 Jun 1993 09:26:56   HANNES
// Weiterschalten der Felder
// 
//    Rev 1.25   10 Jun 1993 18:36:28   HANNES
// IsPrinting - Handling
// 
//    Rev 1.24   07 Jun 1993 15:10:26   MARTIN
// Bearbeitung der WM_LBUTTONUP message
// 
//    Rev 1.23   24 May 1993 14:17:32   HANNES
// Erweiterungen, Verbesserungen
// 
//    Rev 1.22   13 May 1993 13:18:12   HANNES
// Rescale verbessert
// 
//    Rev 1.21   11 May 1993 08:40:36   HANNES
// Rescale
// 
//    Rev 1.20   02 Apr 1993 17:31:20   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.19   17 Mar 1993 17:29:48   HANNES
// (Grosse) Strukturbereinigung
// 
//    Rev 1.18   11 Mar 1993 11:35:02   HANNES
// Mehrseitensupport
// 
//    Rev 1.17   03 Mar 1993 15:35:00   MARTIN
// Erweiterung von FrmObject::OnLButtonDown um den wP Parameter
// (auch fuer OnLButtonDblClk und OnLButtonUp)
// 
//    Rev 1.16   02 Mar 1993 22:33:06   HANNES
// Bestsize nicht bei IsZoomed
// 
//    Rev 1.15   22 Feb 1993 17:06:22   HANNES
// ???
// 
//    Rev 1.14   17 Feb 1993 15:22:38   HANNES
// SetCursor
// 
//    Rev 1.13   16 Feb 1993 13:16:52   HANNES
// Verschiedene Erweiterungen der Klasse FrmObject
// 
//    Rev 1.12   14 Feb 1993 15:54:06   HANNES
// Gleiche Objekte fuer Formulare und Tracings
// 
//    Rev 1.11   05 Feb 1993 19:35:36   HANNES
// Verbesserung der Schiebelehren - Objekte
// 
//    Rev 1.10   01 Feb 1993 12:03:54   HANNES
// Umbau der Felder auf die FrmObj Variante
// 
//    Rev 1.9   29 Jan 1993 18:53:46   HANNES
// Verschiedene Verbesserungen in der Feldhandhabung: Rahmen, Hilfen...
// 
//    Rev 1.8   24 Jan 1993 13:03:32   HANNES
// Hilfe in den Einzelnen Felder
// 
//    Rev 1.7   20 Jan 1993 15:14:10   HANNES
// Zeichnen von Rahmen um die Fenster
// 
//    Rev 1.6   18 Jan 1993 16:45:18   HANNES
// Aenderungen des Handlings von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.5   13 Jan 1993 18:48:46   HANNES
// Aenderungen des Handlings von aktuellen Patientendaten
// 
//    Rev 1.4   06 Jan 1993 16:44:26   HANNES
// Bei leeren Decfeldern einen update mit 0 aussenden
// 
//    Rev 1.3   14 Dec 1992 17:55:32   HANNES
// Korrektur von Frm_Date (Abfrage des Relativ - Punktes auf NULL bei UPDATE
// message)
// 
//    Rev 1.2   12 Dec 1992 12:59:16   HANNES
// Korrektu von HScBar und VScBar (Integer divide by 0)
// 
//    Rev 1.1   06 Dec 1992 17:36:38   HANNES
// Bedingte Eingabe bei Frm_String (... = Frm_ShowString)
// 
//    Rev 1.0   02 Dec 1992 15:26:28   HANNES
// Initial revision.
// #define PROFILE

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "test.hpp"
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "globmem.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "dds.h"
#include "ddsmsg.h"
#include "schiebe.hpp"
#include "cfield.hpp"
#include "frmobj.hpp"

#include "vto.hpp"
#include "image.hpp"
#include "frmobj3.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"
#include "hooks.h"

#include "winextra.hpp"
#define MODULENUM 127
#include "winass.hpp"

/*------< Daten Laden >------*/
extern void ActivateTool (mdiChild *c);
void Form::LoadData (void)
  {
  if (GetOutData()->_MyHandle)
    CheckWindow (GetOutData()->_MyHandle,TRUE);
  mode = M_INACTIVE;

  // Drucker Initialisieren
  GetOutData()->_scale = float(1.0) ;       // vorsichtshalber aus Vto::Vto uebernommen
  ExCute (EM_LOAD | EM_FIXCONNECTION);
  SetCreationFlag (FALSE);
  LoadDone = TRUE ;

  if (DrawContext() == this)
    ActivateTool (this);
  }

void Form::Reset (void)
  {
  if ((schd->Type == CHWND_FORM) && (commands)) {
    CallScriptDestruktor ();
    ExCute (EM_RESET);
    }

  if (GetOutData()->_ObjectList != NULL) {
    // Alte Loeschen und Neue aufbauen
    delete ((FrmObjectList FAR *) GetOutData()->_ObjectList) ;
    GetOutData()->_ObjectList = LPVOID (new FrmObjectList (this));
    }

  // weiterer Reset
  GetOutData()->_xp = GetOutData()->_yp = 0 ;
  }

/*------< Destruktor >--------*/
static HPEN _hActivePen,_hInactivePen;
static int _PenUseCount;
void FreePens ()
  {
  if (-- _PenUseCount == 0) {
    if (_hActivePen)   DeleteObject (_hActivePen)   , _hActivePen = 0;
    if (_hInactivePen) DeleteObject (_hInactivePen) , _hInactivePen = 0;
    }
  }

HPEN GethActivePen ()
  {
  _PenUseCount ++ ;
  if (_hActivePen == 0) 
    _hActivePen = CreatePen (PS_SOLID,0,RGB(0xFF,0,0));
  return _hActivePen;
  }

HPEN GethInactivePen ()
  {
  if (_hInactivePen == 0)
    _hInactivePen = CreatePen (PS_SOLID,0,RGB(0x80,0x80,0x80));
  return _hInactivePen ;
  }

Form::~Form ()
  {
  ZoomInfo FAR *zi = (ZoomInfo FAR *) GetDocumentExtraData (DED_ZOOMBUTTON);
  if ((zi != NULL) && (zi->ZoomCursor)) DestroyCursor (zi->ZoomCursor);
  DestroySchiebeLehre ();
  if (GetOutData()->_MyHandle) {
    CloseSLTimer (GetOutData()->_MyHandle);
    CheckWindow (GetOutData()->_MyHandle,FALSE);
    }

  if ((schd->Type == CHWND_FORM) && (commands)) {
    CallScriptDestruktor ();
    ExCute (EM_RESET);
    }
  DelSelList();
  DBWIN_ASSERT(group == NULL);
  DBWIN_ASSERT(movelist == NULL);

  if ((GetOutData()->hActivePen) && (GetOutData()->hInactivePen))
    FreePens ();
  GetOutData()->hActivePen = GetOutData()->hInactivePen = 0;

  delete ((FrmObjectList FAR *) GetOutData()->_ObjectList);
  GetOutData()->_ObjectList = NULL;
  }

LONG Form::ToScreen (HWND hWnd)
  {
  HideName ();
  PaintContext pc(GetOutData()->_MyHandle);              // PaintContext zum Bildschirm
  LONG RetValue = 0L;
  if (!GetOutData()->IsPrinting) {
    pc.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);         
    RetValue = Paint (&pc);
    }
  if (clear_old)
    DrawGrpMove();
  ShowName ();

  return RetValue ;
  }

LONG Form::ToPrinter (Printer *Pr,BOOL firstpart,WORD partno)
  {
  RECT r ;
  // DBWIN_ASSERT (outContext == NULL);
  Pr->GetPrinterArea (&r);
  // Das linke obere Eck entspricht log. 0/0
  PaintContext pc(Pr);
  pc.LogicalTwips (r.left + xPrinterOffs,r.top + yPrinterOffs,GetOutData()->_scale);
  Paint (&pc);
  return 0L;
  }

LONG Form::Paint (PaintContext *pc)
  {
  if (GetOutData()->CheckMapChanged) {
    if ((FrmObjectList FAR *) OutList() != NULL)
      ((FrmObjectList FAR *) (FrmObjectList FAR *) OutList())->OnMapChange ();
    GetOutData()->CheckMapChanged = FALSE ;
    }
  if ((FrmObjectList FAR *) OutList() != NULL) {
    ((FrmObjectList FAR *) OutList())->Paint (pc);
    }
  ShowName ();
  return 0L;
  }

/*---------< Scroll - Verwaltung >---------*/
// Zuerst muss einmal die Dimension des Formulares berechnet werden
#define ANZSCROLLS  20
void Form::HScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  if ((GetOutData()->veryBestIsDone) || (GetOutData()->veryBestWidthIsDone)) {
    *min = *max = *pos = 0 ;
    return ;
    }
  DBWIN_ASSERT (outContext == NULL);
  GetMinMax ();
  // Berechnen der Scroll - Teilschritte
  int maxwidth = int (GetOutData()->rcLogRect.right);
  int gesdist = maxwidth + maxwidth / 10 ;    // 10 % Reserve (gilt nur nach rechts)
  PaintContext pcscreen(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pcscreen.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);            // Auf 1/20 Punkt umschalten
  int partdist = pcscreen.XPHYStoLOG (pcscreen.cr.right - GetSystemMetrics (SM_CXVSCROLL));
  if (partdist < gesdist) {
    GetOutData()->_xunit = partdist / ANZSCROLLS;
    if (GetOutData()->_xunit < 1) GetOutData()->_xunit = 1 ;
    *max = (gesdist - partdist) / GetOutData()->_xunit + 1 ;
    *min = 0 ;
    int xpdist = pcscreen.XLOGtoPHYS (GetOutData()->_xunit);
    if (xpdist == 0) xpdist = 1 ;
    *pos = int (double(-GetOutData()->_xp) / double(xpdist) + 0.5) ;
    }
  else {
    *max = *min = *pos = 0;
    GetOutData()->_xp = 0 ;
    }
  }

void Form::VScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  if (GetOutData()->veryBestIsDone) {
    *min = *max = *pos = 0 ;
    return ;
    }
  DBWIN_ASSERT (outContext == NULL);
#ifdef WIN32
  LONG maxheight = LONG (GetOutData()->rcLogRect.bottom);
#else
  LONG maxheight = LONG (WORD(GetOutData()->rcLogRect.bottom)); // Damit man wenigstens bis 64000 kommt (ca. 27 Zoll, 2 1/2 Seiten)
#endif
  LONG gesdist = maxheight + maxheight / 10 ;    // HScBar wird immer vor VScBar aufgerufen
  // Berechnung des Bildschirmbereiches
  PaintContext pcscreen(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pcscreen.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);            // Auf 1/20 Punkt umschalten
  LONG partdist = LONG(pcscreen.YPHYStoLOG (pcscreen.cr.bottom - GetSystemMetrics (SM_CYHSCROLL)));
  if (partdist < gesdist) {
    GetOutData()->_yunit = int (partdist / LONG(ANZSCROLLS));
    if (GetOutData()->_yunit < 1) GetOutData()->_yunit = 1 ;
    *max = int ((gesdist - partdist) / LONG(GetOutData()->_yunit + 1)) ;
    *min = 0 ;
    int ypdist = pcscreen.XLOGtoPHYS (GetOutData()->_yunit);
    if (ypdist == 0) ypdist = 1 ;
    *pos = int (double(-GetOutData()->_yp) / double(ypdist) + 0.5) ;
    }
  else {
    *max = *min = *pos = 0;
    GetOutData()->_yp = 0 ;
    }
  }

/*--------< Bearbeitungsfunktion >-------*/
LONG FAR PASCAL Form::SpcFnc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done)
  {
  BOOL ontop = TRUE;
  switch (msg) {
    case WMU_VALREAD :
      // Schiebelehre hat einen Wert zu vermelden
      ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnValRead (double (lP) / 100.0) ;
      break ;

    case WM_TIMER :
      if (wP == VTOTIMERID) {
        KillTimer(hWnd, VTOTIMERID);
        if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
          DBWIN_ASSERT(actsel != NULL);
          if ((mode == M_MOVE) && (actsel->grp->modeflags & GRP_MOVEABLE)) {
            CalcTransMat(old_lP);
            DrawGrpMove();
            clear_old = TRUE;
            state = S_MOVING; 
            }
          else if ((mode == M_SOFT) && (actsel->grp->modeflags & GRP_SOFTEDIT)) {
            if (actsel->grp->SoftObj->OnLButtonDown(old_wP, oldmousex, oldmousey,actSide())) {
              int x, y;
              MouseToLog(old_lP, &x, &y);
              actsel->grp->SoftObj->OnMouseMove(old_wP, x, y,actSide());
              state = S_SOFTEDITING;
              }
            else
              state = S_GRPSELECTED;
            }
          }
        }
      else
        CheckTimer (hWnd,wP,lP);
      break ;

    case WM_MOUSEMOVE :
      // Untersuchen der aktuellen Mouseposition
      if ((state == S_MOVING) ||
          (state == S_ROTATING) ||
          (state == S_CENTMOVING)) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        if (state == S_MOVING)
          CalcTransMat(lP);
        else if (state == S_ROTATING)
          CalcRotMat(lP);
        else
          CalcRotCent(lP);
        DrawGrpMove();
        clear_old = TRUE;
        }
      else if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
        old_lP = lP;
        old_wP = wP;
        }
      else if (state == S_SOFTEDITING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->SoftObj->OnMouseMove(wP, x, y,actSide());
        }
      else if (state == S_CUTTING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->CutObj->OnMouseMove(wP, x, y,actSide());
        }
      else
        ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnMouseMove (wP,lP);
      break ;

    case WM_LBUTTONDBLCLK :
      if ((mode == M_CUT) && (state == S_GRPSELECTED) &&
          (actsel->grp->modeflags & GRP_CUTABLE)) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->CutObj->OnLButtonDblClk(wP, x, y,actSide());
        }
      ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnLButtonDblClk (wP,lP);
      break ;

    case WMU_MOUSEOUTOFWND :
      ClearName ();
      break ;

    case WM_LBUTTONUP :
      if (state == S_TIMERWAIT) {
        KillTimer(hWnd, VTOTIMERID);
        state = S_GRPSELECTED;
        }
      else if (state == S_TIMERWAITSEL) {
        KillTimer(hWnd, VTOTIMERID);
        DeselectGrp();
        DelSelList();
        GenSelList(lP);
        if (actsel != NULL)
          SelectGrp(), state = S_GRPSELECTED;
        else
          state = S_NONESELECTED;
        }
      else if (state == S_MOVING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcTransMat(lP);
        DoGrpMove();
        state = S_GRPSELECTED;
        }
      else if (state == S_SOFTEDITING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        if (actsel->grp->SoftObj->OnLButtonUp(wP, x, y, actSide()))
        state = S_GRPSELECTED;
        }
      else if (state == S_CUTTING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        if (actsel->grp->CutObj->OnLButtonUp(wP, x, y,actSide()))
        state = S_GRPSELECTED;
        }
      else
        ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnLButtonUp (wP,lP);
      break ;

    case WM_LBUTTONDOWN :
      // Mouse wurde gedrueckt -> Zuerst einmal untersuchen,
      // welches Feld gemeint werden koennte
      if (mode != M_INACTIVE) {
        ClearName ();
        MouseToLog(lP, &oldmousex, &oldmousey);
        if (((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnButtonDown (wP,lP,msg)) {
          if (state != S_NONESELECTED) {
            DeselectGrp();
            DelSelList();
            state = S_NONESELECTED;
            }
          }
        else {
          if (mode == M_CUT) {
            if (state == S_GRPSELECTED) {
              if ((actsel->grp->modeflags & GRP_CUTABLE) &&
                  (actsel->grp->CutObj->OnLButtonDown(wP, oldmousex, oldmousey,actSide())))
                state = S_CUTTING;
              else {
                DeselectGrp();
                DelSelList();
                state = S_NONESELECTED;
                }
              }
            if (state == S_NONESELECTED) {
              GenSelList(lP);
              if (actsel != NULL) {
                SelectGrp();
                state = S_GRPSELECTED;
                }
              }
            }
          else {
            if (state == S_GRPSELECTED) {
              DBWIN_ASSERT(actsel != NULL);
              if (!MouseInGrpRect(lP, actsel->grp)) {
                DeselectGrp();
                DelSelList();
                state = S_NONESELECTED;
                }
              else
                state = S_TIMERWAITSEL;
              }
            if (state == S_NONESELECTED) {
              GenSelList(lP);
              if (actsel != NULL) {
                SelectGrp();
                state = S_TIMERWAIT;
                }
              }
            if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
              SetTimer(hWnd, VTOTIMERID, VTODELAY, NULL);
              old_lP = lP;
              old_wP = wP;
              }
            }
          }
        }
      else
        ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnButtonDown (wP,lP,msg);
      break ;

    case WM_ERASEBKGND :
      {
      // Vielleicht ist ein image Angezeigt, dann dieses (um Flackern
      // zu verhindern) bitte nicht anzeigen
      LPIMGBG ib = LPIMGBG (GetDocumentExtraData (DED_IMGBG));
      if ((ib != NULL) && (ib->Seite == actSide())) {

#ifdef WIN32
        HBRUSH hbgr = HBRUSH(GetClassLong (hWnd,GCL_HBRBACKGROUND));
#else
        HBRUSH hbgr = GetClassWord (hWnd,GCW_HBRBACKGROUND);
#endif

        HDC hDC = HDC(wP);
        HBRUSH hbold = (HBRUSH)SelectObject (hDC,hbgr);
        HPEN   hpold = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN));
        RECT ri,cr;
        GetClientRect (hWnd,&cr);
        {
        PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
        pc.LogicalTwips (GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
        pc.LogRecttoPhys (&ri,&ib->r);
        IntersectRect (&ri,&ri,&cr);
        }
        if (ri.right < cr.right)
          Rectangle (hDC,ri.right-1,cr.top-1,cr.right+1,cr.bottom + 1);
        if (ri.left > cr.left)
          Rectangle (hDC,cr.left-1,cr.top-1,ri.left+1,cr.bottom + 1);
        if (ri.bottom < cr.bottom)
          Rectangle (hDC,ri.left-1,ri.bottom-1,ri.right+1,cr.bottom + 1);
        if (ri.top > cr.top)
          Rectangle (hDC,ri.left-1,cr.top-1,ri.right+1,ri.top + 1);
        SelectObject (hDC,hpold);
        SelectObject (hDC,hbold);
        *done = TRUE ;
        return 1L;
        }
      }
      break ;

    case WM_CHAR :
      if (skip_next_char)
        skip_next_char = FALSE;
      else
        ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnChar (wP);
      break ;

    case WM_SETFOCUS :
      ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnSetFocus ();
      break ;

    case WM_SETCURSOR :
      if (LOWORD(lP) == HTCLIENT)
        return (*done = ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnSetCursor());
      break ;

    case WM_KEYDOWN :
#ifdef UEBERLEGT
      if ((wP == VK_INSERT) && (GetKeyState (VK_CONTROL) < 0)) {
        HDC hdcMeta = CreateMetaFile (NULL);
        PaintContext pc;
        pc.mode = DO_EXTERN ;
        pc.hOldPen = pc.hPen = 0 ;
        pc.hOldBrush = 0 ;
        pc.x0 = pc.y0 = 0 ;
        pc.hDC = hdcMeta;
        pc.Map (1.0,GetOutData()->rcLogRect.left,GetOutData()->rcLogRect.bottom);
        Paint(&pc);
        pc.mode = NO_MODE ;
        HANDLE hMF = CloseMetaFile (hdcMeta);
        HANDLE hPict = GlobalAlloc (GMEM_DDESHARE, sizeof (METAFILEPICT));
        LPMETAFILEPICT lppict = (LPMETAFILEPICT)GlobalLock (hPict) ;
        lppict->mm   =  MM_ISOTROPIC;
        lppict->hMF  =  hMF;
        int dx = GetOutData()->rcLogRect.left - GetOutData()->rcLogRect.right;
        int dy = GetOutData()->rcLogRect.top - GetOutData()->rcLogRect.bottom;
        if (dx < 0) dx = -dx ;
        if (dy < 0) dy = -dy ;
        lppict->xExt =  dx;
        lppict->yExt =  dy;

        OpenClipboard (hWnd);
        EmptyClipboard ();
        SetClipboardData(CF_METAFILEPICT, hPict);
        CloseClipboard ();
        break ;
        }
#endif
      {
      BOOL call_trac_spcfnc = TRUE;
      if (wP == VK_TAB) {
        if (state == S_GRPSELECTED) {
          DBWIN_ASSERT(actsel != NULL);
          DeselectGrp();
          if (GetKeyState (VK_SHIFT) < 0) {
            if (actsel->prev != NULL)
              actsel = actsel->prev;
            }
          else {
            if (actsel->next != NULL)
              actsel = actsel->next;
            }
          SelectGrp();
          skip_next_char = TRUE;
          call_trac_spcfnc = FALSE;
          }
        }
      if (call_trac_spcfnc) {
        if (wP == VK_PRIOR)
          ChangeDocSide (-1);
        else if (wP == VK_NEXT)
          ChangeDocSide (1);
        else
          ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnKeyDown (wP);
        }
      }
      break ;

    case WM_KILLFOCUS :
      ClearName ();
      ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnKillFocus ();
      break ;

    case WM_RBUTTONDOWN :
      {
      BOOL call_trac_spcfnc = TRUE;
      ClearName ();
      if (actsel != NULL) {
        if ((mode == M_MOVE) && (actsel->grp->modeflags & GRP_ROTABLE)) {
          if (state == S_GRPSELECTED) {
            if (NearRotCent(lP))
              state = S_CENTMOVING;
            else {
              state = S_ROTATING;
              oldphi = float(0.0);
              CalcRotMat(lP);
              oldphi = act_phi;
              }
            call_trac_spcfnc = FALSE;
            }
          }
        else if (mode == M_SOFT) {
          // derzeit nicht verwendet
          }
        else if (mode == M_CUT) {
          // letzten Punkt rueckgaengig machen
          if (state == S_GRPSELECTED) {
            if (actsel->grp->modeflags & GRP_CUTABLE)
              actsel->grp->CutObj->OnLButtonDown(0, 1, 0,actSide());
            call_trac_spcfnc = FALSE;
            }
          }
        }
      else 
        call_trac_spcfnc = !((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnButtonDown (wP, lP, msg);

      if (call_trac_spcfnc && !GetOutData()->veryBestIsDone && !GetOutData()->veryBestWidthIsDone)
        ToggleScale ();
      }
      break ;

    case WM_RBUTTONUP:
      if (state == S_ROTATING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcRotMat(lP);
        DoGrpMove();
        state = S_GRPSELECTED;
        }
      else if (state == S_CENTMOVING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcRotCent(lP);
        DoRotCentMove();
        state = S_GRPSELECTED;
        }
      break;

    case WM_PALETTECHANGED:
      *done = TRUE;
      if (GetOutData()->_MyHandle == (HWND) wP)
        return FALSE;
      ontop = FALSE;
    case WM_QUERYNEWPALETTE:
      *done = TRUE;
      return ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnPalChange (hWnd, ontop);
    }
  return 0L ;
  }


void mdiChild::NextField ()
  {
  FrmObjectList FAR *ol = ((FrmObjectList FAR *) OutList ());

  ol->OnKillFocus ();
  ol->NextActive ();
  ol->OnSetFocus (TRUE);

  SetFocus (OutWnd());
  }

void mdiChild::PrevField ()
  {
  FrmObjectList FAR *ol = ((FrmObjectList FAR *) OutList ());

  ol->OnKillFocus ();
  ol->PrevActive ();
  ol->OnSetFocus (TRUE);

  SetFocus (OutWnd());
  }

void Form::SizeChanged(void) 
  {
  if (GetOutData()->veryBestIsDone > 0)
    GetVeryBestSize();
  if (GetOutData()->veryBestWidthIsDone > 0)
    GetVeryBestWidth();
  LPDWORD SizeProc = LPDWORD (GetDocumentExtraData (DED_SIZEPROC));
  if (SizeProc != NULL) {
    ExCuteProc (*SizeProc,EM_LOAD | EM_CHANGETOTRUE);
    ExCuteProc (*SizeProc,EM_RESET);
    }
  }

void Form::GetMinMax (BOOL forScreen)
  {
  RECT r;
  DBWIN_ASSERT (outContext == NULL);
  ((FrmObjectList FAR *) GetOutData()->_ObjectList)->GetMinMax (&r,forScreen);
  CopyRect (LPRECT(&GetOutData()->rcLogRect),&r);
  }

#define WFACT 1.005
void Form::GetBestSize (int xmin,int ymin,int xmax,int ymax)
  {
  DBWIN_ASSERT (outContext == NULL);
  GetMinMax ();
  PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips(0,0,float(1.0));
  int dxl = pc.XPHYStoLOG (pc.cr.right);
  int dyl = pc.XPHYStoLOG (pc.cr.bottom);
  double scx,scy,scExt;
  RECT rcScale;
  if (xmax > 0) {
    SetRect (&rcScale,xmin,ymin,xmax,ymax);
    scExt = 1.0;
    }
  else {
    CopyRect (&rcScale,LPRECT(&GetOutData()->rcLogRect));
    // scExt = 1.1;
    scExt = WFACT;
    }
  if (rcScale.right > rcScale.left) {
    scx = double (dxl) / (double (rcScale.right - rcScale.left) * scExt) ;
    }
  else
    scx = 1.0 ;
  if ((GetOutData()->rcLogRect.bottom > 0) && (rcScale.bottom > rcScale.top)) {
    scy = double (dyl) / (double (rcScale.bottom - rcScale.top) * scExt) ;
    }
  else
    scy = 1.0 ;
  GetOutData()->_scale = float (min (4.0,max(0.25,min(scx,scy))));
#ifdef UEBERLEGT
  GetBestScaling (_MyHandle,MAPTYPE_TYPOGRAPHIC,&_scale);
#endif
  pc.LogicalTwips(0,0,GetOutData()->_scale);
  GetOutData()->_xp = - pc.XLOGtoPHYS(rcScale.left);
  GetOutData()->_yp = - pc.YLOGtoPHYS(rcScale.top);

  // Client neu zeichnen
  InitializeBars();

  MapChanged ();
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  }

extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
#define MYINI           GetIniName ()
#endif

void Form::GetVeryBestSize ()
  {
  DBWIN_ASSERT (outContext == NULL);
  GetMinMax ();
  PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips(0,0,float(1.0));
  RECT r;
  CopyRect (&r,LPRECT (&pc.cr));

  static int TerminVariante = GetPrivateProfileInt ("STGKK","TerminVariante",3,MYINI);
  if (TerminVariante & 1) {
    // Durchsuchen aller Kindfenster
    HWND hwChild = GetWindow (GetOutData()->_MyHandle,GW_CHILD);
    for ( int WindowCount = 1; IsWindow (hwChild) ; hwChild = GetWindow (hwChild,GW_HWNDNEXT)) {
      if (TerminVariante & 4) {
        if (WindowCount > 1) {
          char str[50];
          wsprintf(str,"%d. Kindfenster im Terminbuch !",WindowCount);
          WIN_ASSERT_TEXT(FALSE,str);
          }
        }
      char ClassName[50];
      GetClassName(hwChild,ClassName,49);
      if (TerminVariante & 4) {
        if ((lstrcmp(ClassName,"MOVER")) && (lstrcmp(ClassName,"FORMTOOL"))) {
          char str[100];
          wsprintf(str,"Unerwartete Klasse (%s) !",ClassName);
          WIN_ASSERT_TEXT(FALSE,str);
          }
        }
      if (((WindowCount == 1) || (TerminVariante & 2)) &&
          (!((TerminVariante & 8) && 
             (lstrcmp(ClassName,"MOVER") || lstrcmp(ClassName,"FORMTOOL"))))) {
        RECT r1 ;
        GetWindowRect (hwChild,&r1);
        POINT pt;
        pt.x = r1.left ;
        pt.y = r1.top ;
        ScreenToClient (GetOutData()->_MyHandle,&pt);
        if ((pt.x < r.right) && (pt.x > 0)) r.right = pt.x ;
        if ((pt.y < r.bottom) && (pt.y > 0)) r.bottom = pt.y ;
        }
      WindowCount++;
      }
    }
  if (TerminVariante & 16) {
    r.bottom -= 20;   // Auf die harte Tour ...
    }

  int dxl = pc.XPHYStoLOG (r.right);
  int dyl = pc.YPHYStoLOG (r.bottom);
  double scx,scy;
  if (GetOutData()->rcLogRect.right > 0) {
    scx = double (dxl) / (double (GetOutData()->rcLogRect.right) * 1.01) ;
    }
  else
    scx = 1.0 ;
  if (GetOutData()->rcLogRect.bottom > 0) {
    scy = double (dyl) / (double (GetOutData()->rcLogRect.bottom) * 1.01) ;
    }
  else
    scy = 1.0 ;
  GetOutData()->_scale = float (min (4.0,max(0.25,min(scx,scy))));
  GetOutData()->_xp = GetOutData()->_yp = 0;

  GetOutData()->veryBestIsDone = TRUE ;
  MapChanged ();
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  }

void Form::GetVeryBestWidth (int mode)
  {
  DBWIN_ASSERT (outContext == NULL);
  GetMinMax ();
  PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips(0,0,float(1.0));

  RECT r;
  GetWindowRect (GetOutData()->_MyHandle,&r);
  int ww = r.right - r.left;

  int dxl = pc.XPHYStoLOG (ww - GetSystemMetrics (SM_CXVSCROLL));
  double scx;
  if (GetOutData()->rcLogRect.right > 0) {
    scx = double (dxl) / (double (GetOutData()->rcLogRect.right) * 1.01) ;
    }
  else
    scx = 1.0 ;
  GetOutData()->_scale = float(scx);
  GetOutData()->_xp = 0;

  GetOutData()->veryBestWidthIsDone = mode ;
  MapChanged ();
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  }

void Form::GetBestWidth ()
  {
  DBWIN_ASSERT (outContext == NULL);
  GetMinMax ();
  PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips(0,0,float(1.0));
  LONG style = GetWindowLong(GetOutData()->_MyHandle,GWL_STYLE);
  int xKorrektur, yKorrektur;
  if (style & WS_VSCROLL)
    xKorrektur = 0;
  else
    xKorrektur = GetSystemMetrics (SM_CXVSCROLL);
  if (style & WS_HSCROLL)
    yKorrektur = 0;
  else
    yKorrektur = GetSystemMetrics (SM_CXHSCROLL);
  int dxl = pc.XPHYStoLOG (pc.cr.right - xKorrektur);
  int dyl = pc.XPHYStoLOG (pc.cr.bottom - yKorrektur);
  double scx;
  if (GetOutData()->rcLogRect.right > 0) {
    scx = double (dxl) / (double (GetOutData()->rcLogRect.right) * WFACT) ;
    }
  else
    scx = 1.0 ;
  GetOutData()->_scale = float (min (2.0,max(0.5,scx)));
#ifdef UEBERLEGT
  GetBestScaling (_MyHandle,MAPTYPE_TYPOGRAPHIC,&_scale);
#endif
  GetOutData()->_xp = GetOutData()->_yp = 0;

  // Client neu zeichnen
  InitializeBars();

  MapChanged ();
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
  if (IsWindow(GetOutData()->_MyHandle))
    InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  }


void Form::SetPrintSideOpt (BOOL autoscale,double sc)   // ActSide ist eingestellt
  {
  // Berechnung des Skalierungs - Faktors
  GetMinMax (FALSE);
  {
  RECT r;
  GetOutData()->Pr->GetPrinterArea (&r);
  PaintContext pcprinter (GetOutData()->Pr);
  pcprinter.LogicalTwips (0,0,float(1.0));
  if (autoscale) {
    int xlog = pcprinter.XPHYStoLOG (r.right - r.left);
    int ylog = pcprinter.YPHYStoLOG (r.bottom - r.top);
    float xscale,yscale;
    if ((xlog < (GetOutData()->rcLogRect.right - GetOutData()->rcLogRect.left)) || (GetOutData()->veryBestIsDone) || (GetOutData()->veryBestWidthIsDone))
      xscale = float (xlog) / float (GetOutData()->rcLogRect.right - GetOutData()->rcLogRect.left) ;
    else
      xscale = float(1.0);
    if ((ylog < (GetOutData()->rcLogRect.bottom - GetOutData()->rcLogRect.top)) || (GetOutData()->veryBestIsDone))
      yscale = float (ylog) / float (GetOutData()->rcLogRect.bottom - GetOutData()->rcLogRect.top) ;
    else
      yscale = float(1.0);

    GetOutData()->_scale = max (float (0.25),min(xscale,yscale));
    }
  else
    GetOutData()->_scale = float (sc);

  pcprinter.LogicalTwips (0,0,GetOutData()->_scale);
  xPrinterOffs = - pcprinter.XLOGtoPHYS(GetOutData()->rcLogRect.left);
  yPrinterOffs = - pcprinter.YLOGtoPHYS(GetOutData()->rcLogRect.top);
  }

  // Neu formatieren fuer den Drucker
  MapChanged ();
  ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat (TRUE);
  }

BOOL Form::IsSidePrinted()
  {
  if (GetOutData()->_AnzSides > GetOutData()->_ActSide + 1) {
    GetOutData()->_ActSide ++;
    GetMinMax (FALSE);
    {
    RECT r;
    GetOutData()->Pr->GetPrinterArea (&r);
    PaintContext pcprinter (GetOutData()->Pr);
    pcprinter.LogicalTwips (0,0,float(1.0));
    int xlog = pcprinter.XPHYStoLOG (r.right - r.left);
    int ylog = pcprinter.YPHYStoLOG (r.bottom - r.top);
    float xscale,yscale;
    if (xlog < GetOutData()->rcLogRect.right)
      xscale = float (xlog) / float(GetOutData()->rcLogRect.right) ;
    else
      xscale = float(1.0);
    if (ylog < GetOutData()->rcLogRect.bottom)
      yscale = float (ylog) / float(GetOutData()->rcLogRect.bottom) ;
    else
      yscale = float(1.0);
    GetOutData()->_scale = max (float (0.25),min(xscale,yscale));
    }
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat (TRUE);
    return FALSE ;
    }
  else {
    GetOutData()->IsPrinting = FALSE ;
    GetOutData()->_ActSide = 0;
    GetOutData()->_scale = GetOutData()->oldscale;
    GetOutData()->_xp    = GetOutData()->xpold;
    GetOutData()->_yp    = GetOutData()->ypold;
    GetMinMax ();
    MapChanged ();
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
    if (IsWindow (GetOutData()->_MyHandle))
      InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
    return TRUE ;
    }
  }

void Form::SetUpSchiebeLehre ()
  {
  if (!UseSchiebeLehre) {
    if (GetOutData()->_MyHandle)
      UseSchiebeLehre = SetSLTimer (GetOutData()->_MyHandle);
    SchiebeEntryExist = TRUE ;
    }
  }

void Form::DestroySchiebeLehre ()
  {
  if (UseSchiebeLehre) {
    if (GetOutData()->_MyHandle)
      ResetSLTimer (GetOutData()->_MyHandle);
    UseSchiebeLehre = FALSE ;
    }
  }
  
Form::Form (LPSCRIPTCONTENT scent) : mdiChild (scent)
  {
  GetOutData()->hInactivePen = GethInactivePen ();
  GetOutData()->hActivePen   = GethActivePen ();
  GetOutData()->_ObjectList = LPVOID (new FrmObjectList (this));
  }

void Form::GetActivePos (LPPOINT pt)
  {
  ((FrmObjectList FAR *) GetOutData()->_ObjectList)->FirstActive ();
  LPOBJDEF act = ((FrmObjectList FAR *) GetOutData()->_ObjectList)->act;
  pt->x = pt->y = 0;
  if ((act != NULL) && (act->obj != NULL) && (act->obj->Initialized)) {
    if ((act->obj->IsField()) && (((FrmField FAR *) (act->obj))->MyField() != NULL)) 
      ((FrmField FAR *) (act->obj))->MyField()->GetActivePos (pt);
    else {
      LPRECT logr = act->obj->GetLogRect (actSide());
      if (logr != NULL) {
        pt->x = logr->right ;
        pt->y = logr->top ;
        }
      }
    }
  }

void Form::Rescale (LPRECT rcnr)
  {
  RECT r;
  if (outContext != NULL) {
    outContext->Rescale (rcnr);
    return ;
    }
  MyUnionRect (&r,LPRECT(&GetOutData()->rcLogRect),rcnr);
  if (!lmemcmp (&r,&GetOutData()->rcLogRect,sizeof(r))) {
    CopyRect (LPRECT(&GetOutData()->rcLogRect),&r);
    if (GetOutData()->_MyHandle) {
      BOOL oldBlockIsActive = BlockIsActive ;
      BlockIsActive = FALSE ;
      int xpo = GetOutData()->_xp;
      int ypo = GetOutData()->_yp;
      float scaleo = GetOutData()->_scale;
      InitializeBars ();

      // Bereich so setzen, dass der neu dazugekommene Bereich auf jeden
      // Fall sichtbar ist
      POINT pt;
      GetActivePos (&pt);
      int xdphys,ydphys;
      {
      PaintContext pccalc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
      pccalc.LogicalTwips (GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
      LPtoDP (pccalc.hDC,&pt,1);
      // pt.x += GetSystemMetrics (SM_CXVSCROLL);
      // pt.y += GetSystemMetrics (SM_CYHSCROLL);
      xdphys = pccalc.YLOGtoPHYS(GetOutData()->_xunit);
      ydphys = pccalc.YLOGtoPHYS(GetOutData()->_yunit);
      }
      RECT rc;
      GetClientRect (GetOutData()->_MyHandle,&rc);
      int dx,dy;
      if (pt.x > rc.right)  dx = pt.x - rc.right ;
      else                  dx = 0;
      if (pt.y > rc.bottom) dy = pt.y - rc.bottom ;
      else                  dy = 0;

      int a,b;
      if ((dx != 0) && (xdphys != 0)) {
        if (dx < 0) a = dx / xdphys - 1 ;
        else        a = dx / xdphys + 1 ;
        }
      else
        a = 0;
      if ((dy != 0) && (ydphys != 0)) {
        if (dy < 0) b = dy / ydphys - 1 ;
        else        b = dy / ydphys + 1 ;
        }
      else
        b = 0;

      if (a != 0) {
        a = max(GetOutData()->hmin,min(GetOutData()->hmax,a));
        SetScrollPos (GetOutData()->_MyHandle,SB_HORZ,a,TRUE);
        GetOutData()->_xp = -xdphys * a;
        GetOutData()->hpos = a;
        }

      if (b != 0) {
        b = max(GetOutData()->vmin,min(GetOutData()->vmax,b));
        SetScrollPos (GetOutData()->_MyHandle,SB_VERT,b,TRUE);
        GetOutData()->_yp = -ydphys * b;
        GetOutData()->vpos = b;
        }

      if ((GetOutData()->_xp != xpo) || (GetOutData()->_yp != ypo) || (GetOutData()->_scale != scaleo)) {
        MapChanged ();
        InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
        }

      if (GetOutData()->_scale != scaleo) {
        DWORD FAR *scref = GetScaleRef();
        if (scref != NULL)
          WritelData (*scref,&GetOutData()->_scale,sizeof(GetOutData()->_scale),NULL);
        }
      BlockIsActive = oldBlockIsActive ;
      }
    }
  }

void Form::GetDocInfo (int Cmd,DWORD FldId,LPVOID Buffer)
  {
  switch (Cmd) {
    case TRYTOUPDATE :
      * ((BOOL FAR *) Buffer) = !IsDocLocked (schd->TRef[0].TableNr); 
      break ;

    case NEEDSCROLL :
      if (!DrawContext()->GetOutData()->noAutoScroll) {
        NeedScroll_Info FAR *nsi = (NeedScroll_Info FAR *) Buffer; 
        if (nsi->Seite != DrawContext()->GetOutData()->_ActSide) {
          DWORD FAR *SideRef = (DWORD FAR *) DrawContext()->GetDocumentExtraData (DED_DOCSIDEPAR);
          if (SideRef != NULL)
            DrawContext()->WritelData (*SideRef,&nsi->Seite,sizeof(nsi->Seite),NULL);
          DrawContext()->GetOutData()->_ActSide = nsi->Seite;
          DrawContext()->GetMinMax ();
          DrawContext()->InitializeBars (FALSE);
          DrawContext()->MapChanged ();
          InvalidateRect (OutWnd(),NULL,TRUE);
          }
        int dx,dy ;
          {
          PaintContext pcscreen (OutWnd(),0xFFFF,0xFFFF,DO_WORK);
          pcscreen.LogicalTwips (OutXp(),OutYp(),OutScale());
          dx = pcscreen.XPHYStoLOG (((POINT FAR *) Buffer)->x);
          dy = pcscreen.YPHYStoLOG (((POINT FAR *) Buffer)->y);
          }
        int a ;
        unsigned msg = 0;
        if ((dx != 0) && (XUnit() != 0)) {
          if (dx < 0) a = dx / XUnit() - 1 ;
          else        a = dx / XUnit() + 1 ;
          msg = WMU_HSCROLL ;
          }
        if ((dy != 0) && (YUnit() != 0)) {
          if (dy < 0) a = dy / YUnit() - 1 ;
          else        a = dy / YUnit() + 1 ;
          msg = WMU_VSCROLL ;
          }
        LONG lP = MAKELONG(a,0);
        if (msg)
  #ifdef WIN32
          SendMessage (OutWnd(),msg,MAKELONG(SBU_THUMBVAL,a),0);
  #else
          SendMessage (OutWnd(),msg,SBU_THUMBVAL,lP);
  #endif
        }
      break ;
    case VSIZECHANGE :
      InitializeBars ();
      break ;
    default :
      mdiChild::GetDocInfo (Cmd,FldId,Buffer);
      
    }
  }

void Form::ScrollHorizontal (int dist)
  {
  ClearName ();
  if (clear_old) {
    DrawGrpMove();
    clear_old = FALSE;
    }

  DBWIN_ASSERT (outContext == NULL);
#ifdef UEBERLEGT
  InvalidateRect (_MyHandle,NULL,FALSE);
#endif

  PaintContext pc(GetOutData()->_MyHandle);
  RestorePTB (&pc);
  pc.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
  GetOutData()->_xp = pc.XScroll (-GetOutData()->_xunit * dist);
  MapChanged ();
  UpdateWindow (GetOutData()->_MyHandle);
  pc.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
  ReadPTB (&pc,GetOutData()->_MyHandle,GetOutData()->_scale,GetOutData()->_xp,GetOutData()->_yp);
  }

void Form::ScrollVertikal (int dist)
  {
  ClearName ();
  if (clear_old) {
    DrawGrpMove();
    clear_old = FALSE;
    }

  DBWIN_ASSERT (outContext == NULL);
#ifdef UEBERLEGT
  InvalidateRect (_MyHandle,NULL,FALSE);
#endif

  PaintContext pc(GetOutData()->_MyHandle);
  RestorePTB (&pc);
  pc.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
  GetOutData()->_yp = pc.YScroll (-GetOutData()->_yunit * dist);
  MapChanged ();
  UpdateWindow (GetOutData()->_MyHandle);
  pc.LogicalTwips(GetOutData()->_xp,GetOutData()->_yp,GetOutData()->_scale);
  ReadPTB (&pc,GetOutData()->_MyHandle,GetOutData()->_scale,GetOutData()->_xp,GetOutData()->_yp);
  }

BOOL DeleteActivationPens (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Form FAR *f = (Form FAR *)c->DrawContext();
    if ((f->GetOutData()->hActivePen) && (f->GetOutData()->hInactivePen)) {
      FreePens ();
      f->GetOutData()->hActivePen = 0;
      f->GetOutData()->hInactivePen = 0;
      }
    }
  return FALSE ;
  }

BOOL SetNoAutoScroll (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Form FAR *f = (Form FAR *)c->DrawContext();
    f->GetOutData()->noAutoScroll = TRUE;
    }
  return FALSE ;
  }

