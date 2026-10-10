/********************************************************/
/*      Dokumentenbereich                               */
/********************************************************/
// $Header:   F:/marille/clinicum/rev/document.cpv   1.45   26 Apr 2000 00:47:30   Hannes  $
// $Log:   F:/marille/clinicum/rev/document.cpv  $
// 
//    Rev 1.45   26 Apr 2000 00:47:30   Hannes
// ClearConnection bei GetDataWithCode
// 
//    Rev 1.44   12 Oct 1999 12:07:00   Hannes
// Menue in Stationsgraphik
// 
//    Rev 1.43   05 Mar 1999 10:56:26   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.42   30 Dec 1998 12:57:26   Hannes
// 
//    Rev 1.41   05 Oct 1998 11:57:34   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.40   24 Jul 1998 11:19:46   Martin
// Fehler beim ZoomRectWndProc korrigiert
// 
//    Rev 1.39   01 Jul 1998 18:27:58   Martin
// bei noAutoScroll Focus aufs Dokument setzen (bei WindowScroll)
// 
//    Rev 1.38   02 Mar 1998 19:14:28   Hannes
// Aktuelle Seite mit sizeof(DBINT)
// 
//    Rev 1.37   16 Feb 1998 19:00:50   Hannes
// 
//    Rev 1.36   05 Jan 1998 07:53:36   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.35   16 Dec 1997 12:01:32   Gerhold
// AppendContextMenu: im RESET-Zweig RemoveContextMenu
// 
//    Rev 1.34   13 Nov 1997 12:40:42   Hannes
// diverse Fehlerkorrekturen
// 
//    Rev 1.33   24 Oct 1997 08:37:16   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.32   20 Sep 1997 18:44:30   Martin
// DigiMsg durchlassen !!!
// 
//    Rev 1.31   08 Sep 1997 10:51:26   Gerhold
// WM_COMMAND und AppendFrmContextMenu fuer rechte Maustaste in Formularen
// 
//    Rev 1.30   26 Aug 1997 17:35:56   Hannes
// WM_VSCROLL -> WMU_VSCROLL
// 
//    Rev 1.29   21 Aug 1997 13:23:42   Hannes
// Division by Zero - Fehler
// 
//    Rev 1.28   18 Aug 1997 18:08:30   Martin
// VTO Formular-faehig
// 
//    Rev 1.26   20 Jun 1997 12:36:06   Hannes
// 
//    Rev 1.25   06 May 1997 08:27:12   Hannes
// Fehlerkorrektur in initializescroll
// 
//    Rev 1.24   30 Apr 1997 10:24:20   Hannes
// 
//    Rev 1.23   19 Feb 1997 12:22:34   Hannes
// 
//    Rev 1.22   26 Nov 1996 08:13:52   HANNES
// Automatischer Update
// 
//    Rev 1.21   24 Sep 1996 16:32:44   MARTIN
// StatText loeschen bei Destroy eines MDIChild
// 
//    Rev 1.20   10 Jun 1996 10:07:06   GERHOLD
// pragma pack
// 
//    Rev 1.19   04 Apr 1996 18:35:54   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.18   18 Mar 1996 16:19:34   GERHOLD
// SetNewFormToolDimension in WM_SIZE von mdiChildProc
// 
//    Rev 1.17   16 Feb 1996 15:07:50   GERHOLD
// ResetSLTimer in #defein WIN32
// 
//    Rev 1.16   02 Feb 1996 10:35:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.15   24 Aug 1995 00:20:20   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.14   11 Jul 1995 12:47:26   HANNES
// Expressionoptimierung
// 
//    Rev 1.13   07 Jul 1995 17:17:30   GERHOLD
// UpdatePostitList in MapChanged
// 
//    Rev 1.12   09 Jun 1995 00:16:46   HANNES
// InitializeBars mit / ohne repaint
// 
//    Rev 1.11   20 May 1995 16:13:08   HANNES
// GetDataWithChild_Code (zum Abfragen von Extradaten in anderen mdiChilds..)
// 
//    Rev 1.10   20 Mar 1995 11:55:38   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.9   03 Mar 1995 18:12:18   HANNES
// 
//    Rev 1.8   18 Nov 1994 20:01:04   GERHOLD
// WM_KEYDOWN .... F9 raus!
// 
//    Rev 1.7   15 Nov 1994 22:48:52   MARTIN
// Scanner...
// 
//    Rev 1.6   17 Oct 1994 15:04:44   HANNES
// ZommTool eingebaut
// 
//    Rev 1.5   11 Oct 1994 09:43:56   HANNES
// Einbau der Zoomrectfunktionen
// 
//    Rev 1.4   20 Sep 1994 11:34:18   HANNES
// Umstellung auf OutContext
// 
//    Rev 1.3   05 Aug 1994 20:18:00   HANNES
// Font bei WM_DESTROY wieder freigeben
// 
//    Rev 1.2   05 Aug 1994 17:12:52   HANNES
// 
//    Rev 1.1   24 Jun 1994 19:47:28   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:38   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.63   13 Apr 1994 20:51:52   MARTIN
// frmobj3.hpp
// 
//    Rev 1.62   04 Feb 1994 16:43:56   HANNES
// WMU_RECCHANGED
// 
//    Rev 1.61   24 Jan 1994 11:14:32   HANNES
// Testfunktionen eingebaut
// 
//    Rev 1.60   12 Jan 1994 11:06:22   HANNES
// Alte Druckfunktionen raus, Klasse Text eleminiert
// 
//    Rev 1.59   07 Jan 1994 19:20:48   HANNES
// Funktionsprototyp von CheckMsg
// 
//    Rev 1.58   04 Jan 1994 16:34:20   HANNES
// Neue Meldung WMU_DIGDEL
// Fehlerkorrektur in ToggleScale (type == CHWND_VTO)
// 
//    Rev 1.57   29 Nov 1993 08:50:04   HANNES
// ToggleScale: Rundungen verbessert
// 
//    Rev 1.56   16 Nov 1993 04:21:34   HANNES
// SetMouseScale
// 
//    Rev 1.55   03 Nov 1993 19:20:56   HANNES
// ToBusyCursor beim Togglescale
// 
//    Rev 1.54   18 Oct 1993 19:55:24   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.53   06 Oct 1993 09:50:10   HANNES
// Neue Konvention bei Bemerkungen
// 
//    Rev 1.52   04 Oct 1993 09:38:58   HANNES
// MapChanged beim Scrollen raus (Muss verlagert werden in die einzelnen
//    Scrolls der Dokumente)
// 
//    Rev 1.51   22 Sep 1993 09:18:32   HANNES
// Version nach St. Poelten
// 
//    Rev 1.50   05 Sep 1993 22:12:04   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.49   23 Aug 1993 19:31:10   HANNES
// ...
// 
//    Rev 1.48   18 Aug 1993 12:40:20   MARTIN
// nix
// 
//    Rev 1.47   18 Aug 1993 10:27:02   HANNES
// Endgueltiger Umbau auf Tools
// 
//    Rev 1.46   02 Aug 1993 17:46:08   MARTIN
// TestImage
// 
//    Rev 1.45   15 Jul 1993 16:35:24   HANNES
// Drucker in die DMWAPI ausgelagert
// 
//    Rev 1.44   05 Jul 1993 14:38:32   HANNES
// Einbau der Tools
// 
//    Rev 1.43   19 Jun 1993 19:38:02   HANNES
// von GetProp auf GetwindowWord umgestellt
// 
//    Rev 1.42   18 Jun 1993 15:13:40   MARTIN
// Prototyp von GetData
// 
//    Rev 1.41   15 Jun 1993 13:51:40   HANNES
// Benutzername in der MEMO 
// 
//    Rev 1.40   14 Jun 1993 13:08:54   HANNES
// OK Button zum Defaultknopf in Kommentarmessageboxen
// 
//    Rev 1.39   10 Jun 1993 18:46:08   HANNES
// Mehrfach gleichzeitige Eingabe des Kommentars verhindern
// 
//    Rev 1.38   10 Jun 1993 18:35:16   HANNES
// IsPrinting in PrintSide verlegt
// 
//    Rev 1.37   07 Jun 1993 18:42:32   HANNES
// WM_SYSCOMMAND -> wP & 0xFFF0
// 
//    Rev 1.36   07 Jun 1993 11:27:30   HANNES
// Flag fuer Zusammenspiel mit WMU_COMMENTCHANGED..
// 
//    Rev 1.35   03 Jun 1993 13:19:56   MARTIN
// Fehlerkorrektur (LPVOID)
// 
//    Rev 1.34   03 Jun 1993 11:15:28   HANNES
// Schliessen des Dokumentes noch einmal leicht ueberarbeitet
// 
//    Rev 1.33   02 Jun 1993 19:47:10   HANNES
// Warning eleminiert
// 
//    Rev 1.32   28 May 1993 21:13:34   HANNES
// Meldungen bei nichtexistentem Kommentar geaendert
// 
//    Rev 1.31   24 May 1993 14:13:50   HANNES
// Lock - Handling
// 
//    Rev 1.30   13 May 1993 13:17:58   HANNES
// Verbesserungen von ToggleSize
// 
//    Rev 1.29   18 Apr 1993 22:51:50   HANNES
// ??
// 
//    Rev 1.28   05 Apr 1993 10:26:26   HANNES
// Kommentarabfrage verbessert
// 
//    Rev 1.27   02 Apr 1993 17:46:52   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.26   17 Mar 1993 17:29:18   HANNES
// Strukturbereinigung, 32 bit Offsets
// 
//    Rev 1.25   11 Mar 1993 11:34:26   HANNES
// Fehlerkorrekturen Drucken
// 
//    Rev 1.24   02 Mar 1993 22:28:50   HANNES
// Mehrfachaufruf von subforms
// 
//    Rev 1.23   26 Feb 1993 13:45:28   HANNES
// ??
// 
//    Rev 1.22   22 Feb 1993 17:05:46   HANNES
// Verbesserungen Layout, Stringfeldlisten im Basistyp
// 
//    Rev 1.21   17 Feb 1993 15:22:20   HANNES
// Konfigurationsdatenbank
// 
//    Rev 1.20   16 Feb 1993 13:15:58   HANNES
// Subform - Handling
// 
//    Rev 1.19   14 Feb 1993 16:01:32   HANNES
// Verallgemeinerte Konfigurationsfunktionen
// 
//    Rev 1.18   05 Feb 1993 19:35:18   HANNES
// Einbau des Dokumentenlockings->Sperren der Eingaben
// 
//    Rev 1.17   01 Feb 1993 12:03:12   HANNES
// Einbau der Klasse VTO
// 
//    Rev 1.16   29 Jan 1993 18:52:08   HANNES
// Funktion MultiSelectionAllowed...
// 
//    Rev 1.15   24 Jan 1993 13:04:22   HANNES
// Hilfe zu den einzelnen Feldern
// 
//    Rev 1.14   20 Jan 1993 15:13:36   HANNES
// Hintergrund eines Bildes beim Drucken loeschen
// 
//    Rev 1.13   18 Jan 1993 16:44:16   HANNES
// Aenderung des Handlings von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.12   13 Jan 1993 18:47:26   HANNES
// Aenderungen des Handlings von aktuellen Patienten
// 
//    Rev 1.11   06 Jan 1993 16:49:24   HANNES
// Einbau des Trackings in den Fenstern
// 
//    Rev 1.10   21 Dec 1992 11:34:34   HANNES
// Einbau von Hotkeys fuer die Knoepfchens
// 
//    Rev 1.9   19 Dec 1992 14:19:46   HANNES
// Neue virtuelle Funktion: OnActivate (setzt den globalen Patienten neu)
// 
//    Rev 1.8   18 Dec 1992 12:44:46   HANNES
// Durchschleifen der Meldungen WMU_DIGNEXT und WMU_DIGPREV
// 
//    Rev 1.7   15 Dec 1992 11:13:50   HANNES
// Funktionsprototyp von IsSysButton hat sich geaendert (Verbessertes Handling
// der benutzerdefinierten Knoepfe)
// 
//    Rev 1.6   12 Dec 1992 13:43:36   HANNES
// Elemination der Funktion SetOverlap (Overlap Knopf wurde eleminiert, hat
// sich nicht bewaehrt)
// 
//    Rev 1.5   12 Dec 1992 13:33:06   HANNES
// Begrenzen des von der Konfigurationsdatenbank gelesenen Skalierungsfaktors
// auf (0.5,2.0)
// 
//    Rev 1.4   12 Dec 1992 12:32:50   HANNES
// Aufruf der virt. Funktion OnDestroy (beim WM_DESTROY in daWndProc),
// Implementation einer DummyFunktion fuer mdiChild
// 
//    Rev 1.3   11 Dec 1992 16:21:46   HANNES
// Meldung WMU_SCANSTART durchgeleitet
// 
//    Rev 1.2   06 Dec 1992 16:05:34   HANNES
// Messagehandling von TRYTOUPDATE in GetDocInfo (return TRUE)
// 
//    Rev 1.1   06 Dec 1992 10:56:48   HANNES
// Durchschleifen der Meldungen, die von dmwhook.dll kommen
// 
//    Rev 1.0   02 Dec 1992 15:31:00   HANNES
// Initial revision.

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

#include "winextra.hpp"
#include "dds.h"
#include "ddsmsg.h"
#include "schiebe.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"
#include "image.hpp"
#include "frmobj3.hpp"
#include "diagram.hpp"

#include "mdiclien.hpp"
#include "digitize.hpp"
#define MODULENUM 47
#include "winass.hpp"
#include "hash.hpp"
#include "compile.hpp"

#define NODLL
#include "toolbar.hpp"

#include "tbcbd.hpp"

BOOL ZoomRectActive = FALSE;  // globale Variable fuer Rechteckzoomfunktion

LPFRMOBJ ContextObject = NULL;    // ausgewaehltes Objekt bei Mausereignissen


void mdiChild::InitializeBars (BOOL doErase)
  {
  DBWIN_ASSERT (outContext == NULL);
  if (GetOutData()->_MyHandle) {
    HScBar (&GetOutData()->hmin,&GetOutData()->hmax,&GetOutData()->hpos);
    if (GetOutData()->hmax > GetOutData()->hmin) {
      ShowScrollBar (GetOutData()->_MyHandle,SB_HORZ,TRUE);
      SetScrollRange (GetOutData()->_MyHandle,SB_HORZ, GetOutData()->hmin, GetOutData()->hmax, doErase);
      SetScrollPos (GetOutData()->_MyHandle,SB_HORZ, GetOutData()->hpos, doErase);
      }
    else ShowScrollBar (GetOutData()->_MyHandle,SB_HORZ,FALSE);

    VScBar (&GetOutData()->vmin,&GetOutData()->vmax,&GetOutData()->vpos);
    if (GetOutData()->vmax > GetOutData()->vmin) {
      ShowScrollBar (GetOutData()->_MyHandle,SB_VERT,TRUE);
      SetScrollRange (GetOutData()->_MyHandle,SB_VERT, GetOutData()->vmin, GetOutData()->vmax, doErase);
      SetScrollPos (GetOutData()->_MyHandle,SB_VERT, GetOutData()->vpos, doErase);
      }
    else ShowScrollBar (GetOutData()->_MyHandle,SB_VERT,FALSE);
    }
  }

void mdiChild::ToggleSize()
  {
  DBWIN_ASSERT (outContext == NULL);
  HWND dummy;
  if (GetOutData()->maximized) {
    // Maximize Fenster wieder verschwinden lassen
    ShowWindow (GetOutData()->_MyHandle,SW_HIDE);
    // Ruecktauschen der Fensterhandles
    dummy = GetOutData()->hMax ;
    GetOutData()->hMax = GetOutData()->_MyHandle ;
    GetOutData()->_MyHandle = dummy ;

    /*----< Alte Groesse wieder Initialisieren >-----*/
    SetFocus (GetOutData()->_MyHandle);
    ShowWindow (GetOutData()->_MyHandle,SW_SHOW);
    GetOutData()->maximized = FALSE ;
    }
  else {
    // Maximize - Fenster mit der Instanz - Verbinden
    SetWindowLong (GetOutData()->hMax,GWL_HWINFO,LONG(this));
    // Austauschen der Fensterhandles, damit die Funktionen den richtigen
    // Handle kriegen
    dummy = GetOutData()->hMax ;
    GetOutData()->hMax = GetOutData()->_MyHandle ;
    GetOutData()->_MyHandle = dummy ;
    // Und Los gehts
    RECT r;
    GetWindowRect (WBase::hFrameWin,&r);
    MoveWindow (GetOutData()->_MyHandle,r.left,r.top,r.right-r.left+1,r.bottom-r.top+1,FALSE);
    ShowWindow (GetOutData()->_MyHandle,SW_SHOWNORMAL);
    CalcScale();
    InitializeBars();
    InvalidateRect(GetOutData()->_MyHandle,NULL,TRUE);
    UpdateWindow(GetOutData()->_MyHandle);
    SetFocus(GetOutData()->_MyHandle);
    GetOutData()->maximized = TRUE ;
    }
  }

void mdiChild::CalcScale(void) { } // virtuelle Funktion

void mdiChild::SizeChanged(void) { }

/*-----------< Zeichnen (virtuelle Funktion) >----------*/
LONG mdiChild::Paint (PaintContext *pc)
  {
  return 0L ;
  }

LONG mdiChild::ToScreen (HWND hWnd)
  {
  PaintContext pc(hWnd);
  LONG RetVal = 0;
  if (!GetOutData()->IsPrinting)
    RetVal = Paint (&pc);
  return RetVal;
  }

LONG mdiChild::ToPrinter (Printer *Pr,BOOL firstBand,WORD partNo)
  {
  PaintContext pc (Pr);
  LONG RetVal = Paint (&pc);
  return RetVal;
  }

LONG FAR PASCAL mdiChild::SpcFnc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done)
  {
  return 0L ;
  }

extern void ShowTestMsg ();
void mdiChild::ScrollHorizontal(int y) { }
void mdiChild::ScrollVertikal(int x) { }

static void DrawZoomRect(PaintContext *pc,int x1,int y1,int x2,int y2)
  {
  SetROP2(pc->hDC,R2_XORPEN);
  pc->diPen(RGB(0xFF,0x00,0x00));
  MoveToEx(pc->hDC,x1,y1,NULL);
  LineTo(pc->hDC,x2,y1);
  LineTo(pc->hDC,x2,y2);
  LineTo(pc->hDC,x1,y2);
  LineTo(pc->hDC,x1,y1);
  }

/*-----------< Fensterfunktion fuer den Arbeitsbereich >---------*/
void mdiChild::HScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  *max = *min = *pos = -1 ;
  }

void mdiChild::VScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  *max = *min = *pos = -1 ;
  }

void mdiChild::NewScale (double Scale) { }   // virtuelle Funktion

void mdiChild::LoadData () { }

void mdiChild::Reset () { }

#define ANZFREESUBS   2
static int subforms_dedind[ANZFREESUBS] = {
  DED_HELPWIN ,
  DED_GAUSSWIN
  };
typedef mdiChild *LPMDIC;
void mdiChild::CloseChilds () 
  { 
  for (int i = 0 ; i < ANZFREESUBS ; i++) {
    LPMDIC FAR *p = (LPMDIC FAR *) GetDocumentExtraData (subforms_dedind[i]);
    if ((p != NULL) && (*p != NULL))
      delete *p ;
    }
  }

double MyGaussFunc (double x,GLOBALHANDLE hPP,int Nr)
  {
  GaussPar FAR *p = (GaussPar FAR *) GlobalLock (hPP);
  double y ;
  if (Nr < p->AnzLines) {
    double dx = x - p->gp[Nr].x0 ;
    double arg = - dx * dx * p->gp[Nr].dev22 ;
    if (arg >= -1.0E-7)
      y = 1.0 ;
    else
      y = exp (arg) ;
    }
  else
    y = 1.0E11 ;
  GlobalUnlock (hPP);
  return y ;
  }

void MyGaussCursor (double *x,double *y,GLOBALHANDLE hPP,int Nr)
  {
  GaussPar FAR *p = (GaussPar FAR *) GlobalLock (hPP);
  if (Nr < p->AnzLines) {
    *x = p->gp[Nr].xact ;
    *y = MyGaussFunc (*x,hPP,Nr);
    }
  else
    *x = *y = 1.0E11 ;
  GlobalUnlock (hPP);
  }

typedef sDiag *LPSD;
void mdiChild::CreateGaussWin()
  {
  LPSD FAR *s = (LPSD FAR *) GetDocumentExtraData (DED_GAUSSWIN);
  if ((s == NULL) || (*s == NULL)) {
    sDiag *hg = new sDiag (GetOutData()->_MyHandle,IDC_DG_BASE,
            WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION | WS_BORDER 
            | WS_VISIBLE,TRUE);
    hg->SetDiagramMode (DS_XVALUES | DS_XAXIS | DS_YAXIS | 
                        DS_XPARTDOWN | DS_XPARTUP | DS_SCFORMAT(2)) ;
    hg->SetLineFunc (MyGaussFunc);
    hg->SetCursorFunc (MyGaussCursor);
    hg->Create ("");
    PutDocumentExtraData (DED_GAUSSWIN,&hg,sizeof(hg));
    }
  }

GLOBALHANDLE mdiChild::GetGaussPar (double FAR *val,double FAR *norm,
                                  double FAR *dev,int AnzRun)
  {
  GLOBALHANDLE hGtemp = 0 ;

  for (int i = 0 ; i < AnzRun ; i++) {
    if ((val[i] < 1.0E9) && (norm[i] < 1.0E9) && (dev[i] < 1.0E9)) {
      int size = sizeof (GaussPar) + i * sizeof (GaussLinePar) ;
      if (hGtemp)
        hGtemp = GlobalReAlloc (hGtemp,size,GMEM_MOVEABLE);
      else
        hGtemp = GlobalAlloc (GHND,size);

      GaussPar FAR *p = (GaussPar FAR *) GlobalLock (hGtemp);
      p->gp[i].x0   = norm[i] ;
      p->gp[i].xact = val[i] ;
      p->gp[i].dev22 = 1.0 / (dev[i] * dev[i] * 2) ;

      // Extremwerte
      double xmin = norm[i] - dev[i] * 3.0 ;
      double xmax = norm[i] + dev[i] * 3.0 ;
      double xm1 = p->gp[i].x0 + (p->gp[i].xact - p->gp[i].x0) * 1.1 ;
      if (xm1 < xmin) xmin = xm1 ;
      if (xm1 > xmax) xmax = xm1 ;

      if (i == 0) {
        // Initialwerte der Extremwerte
        p->xmin = xmin ;
        p->xmax = xmax ;
        }
      else {
        // Extremwerte up to date bringen
        if (xmin < p->xmin) p->xmin = xmin ;
        if (xmax > p->xmin) p->xmax = xmax ;
        }

      p->AnzLines = i + 1;
      GlobalUnlock (hGtemp);
      }
    }

  return hGtemp ;
  }

void mdiChild::ShowGauss (double FAR *val,double FAR *norm,double FAR *dev,
                            int AnzRec,
                            LPSTR caption
                       )
  {
  LPSD FAR *s = (LPSD FAR *) GetDocumentExtraData (DED_GAUSSWIN);
  if ((s != NULL) && (*s != NULL)) {
    BOOL correct = TRUE ;
    for (int i = 0 ; ((i < AnzRec) && (correct)) ; i++)
      correct = ((correct) && (val[i] < 1.0E9) && (norm[i] < 1.0E9)
                                && (dev[i] < 1.0E9) && (dev[i] > 1.0E-3));
    if (correct) {
      GLOBALHANDLE hGhlp = GetGaussPar (val,norm,dev,AnzRec);
      (*s)->SetPaintParam (hGhlp);
      GaussPar FAR *p = (GaussPar FAR *) GlobalLock (hGhlp);
      (*s)->SetAxValues (p->xmin,p->xmax,0.0,1.1,p->gp[0].x0,0.0);
      GlobalUnlock (hGhlp);
      if ((*s)->GetOutData()->_MyHandle) 
        SetWindowText ((*s)->GetOutData()->_MyHandle,caption);
      (*s)->Rescale ();
      }
    }       
  }

void mdiChild::CloseGauss ()
  {
  // Fenster mit der Verteilungskurve wuenscht geschlossen zu werden
  SetFocus (GetOutData()->_MyHandle);
  LPMDIC FAR *p = (LPMDIC FAR *) GetDocumentExtraData (DED_GAUSSWIN);
  if ((p != NULL) && (*p != NULL))
    delete *p;
  RemoveDocumentExtraData (DED_GAUSSWIN);
  }

void mdiChild::GetMinMax (BOOL forScreen) { }

typedef GLOBALHANDLE FAR *LPGLOBALHANDLE;

//      Informationsfunktionen
/////////////////////////////////////////////////////////////////////////
void mdiChild::GetDocInfo (int Cmd,DWORD FldId,LPVOID Buffer)
  {
  switch (Cmd) {
    case GETDRAWINGWINDOW :
      *((HWND FAR *) Buffer) = OutWnd();
      break ;
    case GETSCALE :
      *((float FAR *) Buffer) = OutScale();
      break ;
    case GETCHARHANDLE :
      DBWIN_ASSERT(FALSE);
      break ;
    case GETMAPTYPE :
      *((int FAR *) Buffer) = MAPTYPE_TYPOGRAPHIC ;
      break ;
    case GETWINDOWORG :
      ((POINT FAR *) Buffer)->x = 
      ((POINT FAR *) Buffer)->y = 0 ;
      break ;
    case GETVIEWPORTORIGIN :
      ((POINT FAR *) Buffer)->x = OutXp() ;
      ((POINT FAR *) Buffer)->y = OutYp() ;
      break ;
    case ISDRAWINGALLOWED :
      *((BOOL FAR *) Buffer) = !GetOutData()->IsPrinting;
      break ;
    case GETPRINTERHANDLE :
      *((LPPRINTER FAR *) Buffer) = GetOutData()->Pr ;
      break ;
    case GETFLDMEM :
      DBWIN_ASSERT(FALSE);
      break ;
    case FORMATFORSCREEN :
      *((BOOL FAR *) Buffer) = !GetOutData()->IsPrinting;
      break ;
    case TRYTOUPDATE :
      *((BOOL FAR *) Buffer) = !(IsDocLocked(schd->TRef[0].TableNr)) ;
      break ;
    case INFORMABOUTUPDATE :
      DBWIN_ASSERT (FALSE);
      if (FldId) {
        CallCommand (base + FldId,EM_SAVE);
        }
      break ;
    case GETLISTITEMS :
      DBWIN_ASSERT (FALSE);
      // Das Feld will die Konfigurationsdatei haben
      DrawContext()->GetOutData()->sli.res = 0;
      if (FldId) {
        CallCommand (base + ((StrListInfo FAR *) Buffer)->Id,EM_PRIVATE0);
        }
      lmemcpy (Buffer,&DrawContext()->GetOutData()->sli,sizeof(DrawContext()->GetOutData()->sli));
      break;
    case GETTABPOS :
      // Tab - Positionen fuer das Feld
      DBWIN_ASSERT (FALSE);
      DrawContext()->GetOutData()->tabx = ((WORD FAR *) Buffer)[1] ;
      if (FldId) {
        CallCommand (base + *((DWORD FAR *) Buffer),EM_PRIVATE1);
        }
      *((WORD FAR *) (LPSTR (Buffer) + sizeof(DWORD))) = DrawContext()->GetOutData()->tabx;
      break ;
    case SETLISTITEM :
      // Das Feld hat einen neuen Index
      DBWIN_ASSERT (FALSE);
      lmemcpy (&DrawContext()->GetOutData()->sli,Buffer,sizeof(DrawContext()->GetOutData()->sli));
      if (FldId) {
        CallCommand (base + ((StrListInfo FAR *) Buffer)->Id,EM_SAVE);
        }
      break ;
    case GETSELSTR :
      DBWIN_ASSERT (FALSE);
      lmemcpy (&DrawContext()->GetOutData()->sli,Buffer,sizeof(DrawContext()->GetOutData()->sli));
      if (FldId) {
        CallCommand (base + ((StrListInfo FAR *) Buffer)->Id,EM_PRIVATE2);
        }
      lmemcpy (Buffer,&DrawContext()->GetOutData()->sli,sizeof(DrawContext()->GetOutData()->sli));
      break ;
    case NEEDSCROLL :
      if ((DrawContext() != NULL) && (DrawContext () != this)) {
        DrawContext ()->GetDocInfo (Cmd,FldId,Buffer);
        }
      break ;
    }
  }

BOOL mdiChild::IsSidePrinted ()
  {
  return TRUE;
  }

void mdiChild::SetPrintSideOpt(BOOL autoscale,double sc)
  {
  }

// Erklaerung des Dokumentes
#define DOCEXPLAIN_BASE         20000
void DocExplain (mdiChild *c)
  {
  if (c != NULL) {
    if (c->StatusStrId)
      PrgStat.SetStatus (0,FALSE,c->StatusStrId);
    else
      PrgStat.SetStatus (0,FALSE,DOCEXPLAIN_BASE + c->schd->Type);
    }
  }


void mdiChild::ToggleScale ()
  {
  DBWIN_ASSERT (outContext == NULL);
  // Berechnen der Aktellen Position der Mouse
  DWORD dws = GetMessagePos ();

  POINT ptw, ptv;

#ifdef WIN32
  LONG2POINT (dws, ptw);
  LONG2POINT (dws, ptv);
#else
  ptw = MAKEPOINT (dws);
  ptv = MAKEPOINT (dws);
#endif

  ScreenToClient (GetOutData()->_MyHandle,&ptv);
  ScreenToClient (GetOutData()->_MyHandle,&ptw);
  {
  PaintContext pc;
  GetDocumentContext (&pc,this);
  DPtoLP (pc.hDC,&ptw,1);     // Mouseposition in Weltkoordinaten
  }   // invoke Destruktor for pc
  if (GetOutData()->_scale < float (1.3)) {
    GetOutData()->_scale = float (2.0) ;
    BestScaling ();
    }
  else {
    GetOutData()->_scale = float (1.0) ;
    BestScaling ();
    }

  InitializeBars ();

  int sxp,syp;
  int xdphys,ydphys;
  {
  PaintContext pc;
  GetDocumentContext (&pc,this);

  // Berechnen von xp,yp mit dem neuen Skalierungsfaktor
  SIZE  dwext, dvext;
  POINT dworg;
  
  GetWindowExtEx (pc.hDC, &dwext);
  GetViewportExtEx (pc.hDC, &dvext);
  GetWindowOrgEx (pc.hDC, &dworg);

  sxp = ptv.x - int (
                 double (ptw.x - int(dworg.x)) * double (int(dvext.cx)) /
                 double (int (dwext.cx))
                    );
  syp = ptv.y - int (
                 double (ptw.y - int(dworg.y)) * double (int(dvext.cy)) /
                 double (int (dwext.cy))
                    );

  xdphys = pc.XLOGtoPHYS(GetOutData()->_xunit);
  ydphys = pc.YLOGtoPHYS(GetOutData()->_yunit);
  }   // invoke Destruktor for pc

  if (schd->Type == CHWND_FORM) {
    if ((GetOutData()->hmax > 0) && (xdphys > 0)) {
      // Abpruefen, ob noch im gueltigen Berech
      if (sxp > 0) GetOutData()->_xp = 0 ;
      else         GetOutData()->_xp = max (- GetOutData()->hmax * xdphys, sxp);
      double hh = double (- GetOutData()->_xp) / double (xdphys);
      GetOutData()->hpos = (hh >= 0.0) ? int (hh + 0.5) : int (hh - 0.5);
      GetOutData()->_xp = -GetOutData()->hpos * xdphys;
      SetScrollPos (GetOutData()->_MyHandle,SB_HORZ, GetOutData()->hpos, TRUE);
      }

    if ((GetOutData()->vmax > 0) && (ydphys > 0)) {
      if (syp > 0) GetOutData()->_yp = 0 ;
      else         GetOutData()->_yp = max (- GetOutData()->vmax * ydphys, syp);
      double hv = double (- GetOutData()->_yp) / double (ydphys);
      GetOutData()->vpos = (hv >= 0.0) ? int (hv + 0.5) : int (hv - 0.5);
      GetOutData()->_yp = -GetOutData()->vpos * ydphys;
      SetScrollPos (GetOutData()->_MyHandle,SB_VERT, GetOutData()->vpos, TRUE);
      }
    }
#ifdef UEBERLEGT
  else {
    static int xd1 = -1 ;
    static int yd1 = 1 ;
    static int xd2 = 1 ;
    static int yd2 = 1 ;
    static int xd3 = -1 ;
    static int yd3 = 1 ;

    if (xdphys != 0) {
      double hdx = double (xd1 * sxp) / double (xdphys);
      int hx;
      if (hdx >= 0) hx = int (hdx + 0.5);
      else          hx = int (hdx - 0.5);
      if (hpos + hx * xd2 < 0) {
        if (hx < 0) hx = -hpos ;
        else        hx = hpos ;
        }
      if (hpos + hx * xd2 > hmax) {
        if (hx < 0) hx = hmax - hpos ;
        else        hx = -(hmax - hpos);
        }
      if (hx != 0) {
        hpos += hx * xd2 ;
        _xp = hx * xd3 * xdphys ;
        SetScrollPos (_MyHandle,SB_HORZ, hpos, TRUE);
        }
      }

    if (ydphys != 0) {
      double hdy = double (yd1 * syp) / double (ydphys);
      int hy;
      if (hdy >= 0) hy = int (hdy + 0.5);
      else          hy = int (hdy - 0.5);
      if (vpos + hy * yd2 < 0) {
        if (hy < 0) hy = -vpos ;
        else        hy = vpos ;
        }
      if (vpos + hy * yd2 > vmax) {
        if (hy < 0) hy = vmax - vpos ;
        else        hy = -(vmax - vpos);
        }
      if (hy != 0) {
        vpos += hy * yd2 ;
        _yp = hy * yd3 * ydphys;
        SetScrollPos (_MyHandle,SB_VERT, vpos, TRUE);
        }
      }
    ((Tracing *) this)->scale_set = TRUE ;
    }
#endif

  ToBusyCursor ();
  MapChanged ();
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->Reformat ();
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  DWORD FAR *scref = GetScaleRef();
  if (scref != NULL)
    WritelData (*scref,&GetOutData()->_scale,sizeof(GetOutData()->_scale),NULL);
  UpdateWindow (GetOutData()->_MyHandle);
  SizeChanged ();
  }

void mdiChild::ZoomRect (int x1,int y1,int x2,int y2)
  {
  if (x1 == x2) x2 = x1 + 1;
  if (y1 == y2) y2 = y1 + 1;
  int xcr, ycr;
  {
  PaintContext pc;
  GetDocumentContext (&pc,DrawContext());
  xcr = pc.XPHYStoLOG (pc.cr.right);
  ycr = pc.YPHYStoLOG (-pc.cr.bottom);
  }   // invoke Destruktor for pc
  float xscale = (float)fabs(float(xcr) / float (x2 - x1));
  float yscale = (float)fabs(float(ycr) / float (y2 - y1));
  if (xscale < yscale)
    DrawContext()->GetOutData()->_scale *= xscale;
  else
    DrawContext()->GetOutData()->_scale *= yscale;
  if (DrawContext()->GetOutData()->_scale < float(0.25)) DrawContext()->GetOutData()->_scale = float(0.25);
  if (DrawContext()->GetOutData()->_scale > float(4.0))  DrawContext()->GetOutData()->_scale = float(4.0);

  InitializeBars ();

  int xdphys,ydphys;
  POINT ptw, ptv;
  {
  PaintContext pc;
  GetDocumentContext (&pc,this);

  ptw.x = (x1 + x2) / 2;
  ptw.y = (y1 + y2) / 2;
  ptv.x = pc.cr.right / 2;
  ptv.y = pc.cr.bottom / 2;

  // Berechnen von xp,yp mit dem neuen Skalierungsfaktor
  SIZE  dwext, dvext;
  POINT dworg;
  
  GetWindowExtEx (pc.hDC, &dwext);
  GetViewportExtEx (pc.hDC, &dvext);
  GetWindowOrgEx (pc.hDC, &dworg);

  DrawContext()->GetOutData()->_xp = ptv.x - int (
                 double (ptw.x - int(dworg.x)) * double (int(dvext.cx)) /
                 double (int (dwext.cx))
                    );
  DrawContext()->GetOutData()->_yp = ptv.y - int (
                 double (ptw.y - int(dworg.y)) * double (int(dvext.cy)) /
                 double (int (dwext.cy))
                    );

  xdphys = pc.XLOGtoPHYS(DrawContext()->GetOutData()->_xunit);
  ydphys = pc.YLOGtoPHYS(DrawContext()->GetOutData()->_yunit);
  }   // invoke Destruktor for pc

  if (schd->Type == CHWND_FORM) {
    if ((GetOutData()->hmax > 0) && (xdphys > 0)) {
      // Abpruefen, ob noch im gueltigen Berech
      if (DrawContext()->GetOutData()->_xp > 0) DrawContext()->GetOutData()->_xp = 0 ;
      else                                      DrawContext()->GetOutData()->_xp = max (- DrawContext()->GetOutData()->hmax * xdphys, DrawContext()->GetOutData()->_xp);
      double hh = double (- DrawContext()->GetOutData()->_xp) / double (xdphys);
      DrawContext()->GetOutData()->hpos = (hh >= 0.0) ? int (hh + 0.5) : int (hh - 0.5);
      SetScrollPos (OutWnd(),SB_HORZ, DrawContext()->GetOutData()->hpos, TRUE);
      }

    if ((GetOutData()->vmax > 0) && (ydphys > 0)) {
      if (DrawContext()->GetOutData()->_yp > 0) DrawContext()->GetOutData()->_yp = 0 ;
      else                                      DrawContext()->GetOutData()->_yp = max (- DrawContext()->GetOutData()->vmax * ydphys, DrawContext()->GetOutData()->_yp);
      double hv = double (- DrawContext()->GetOutData()->_yp) / double (ydphys);
      DrawContext()->GetOutData()->vpos = (hv >= 0.0) ? int (hv + 0.5) : int (hv - 0.5);
      SetScrollPos (OutWnd(),SB_VERT, DrawContext()->GetOutData()->vpos, TRUE);
      }
    }

  InitializeBars ();

  ToBusyCursor ();
  MapChanged ();
  if (OutList() != NULL)
    ((FrmObjectList FAR *) OutList())->Reformat ();
  InvalidateRect (OutWnd(),NULL,TRUE);
  DWORD FAR *scref = DrawContext()->GetScaleRef();
  if (scref != NULL)
    DrawContext()->WritelData (*scref,&DrawContext()->GetOutData()->_scale,sizeof(DrawContext()->GetOutData()->_scale),NULL);
  UpdateWindow (OutWnd());
  DrawContext()->SizeChanged ();
  }

extern BOOL IsFromSyncList ();
extern void UpdatePostItList (mdiChild *c);

void mdiChild::MapChanged()
  {
  if (IsFromSyncList())
    GetOutData()->CheckMapChanged = TRUE ;
  else {
    if (GetOutData()->_ObjectList != NULL)
      ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnMapChange ();
    UpdatePostItList (this);
    }
  }

void GetDateString (PSTR str,LONG time)
  {
  packdate pdl;
  UnPackTime (time,&pdl);
  writeShortDateStr (str,&pdl);
  }

extern void CheckScriptScroll (mdiChild *c,int Num);
void mdiChild::StartExternPaint ()
  {
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->StartExternPaint ();
  CheckScriptScroll (this,0);
  }

void mdiChild::EndExternPaint ()
  {
  if (GetOutData()->_ObjectList != NULL)
    ((FrmObjectList FAR *) GetOutData()->_ObjectList)->EndExternPaint ();
  CheckScriptScroll (this,1);
  }

// Zeiger auf Instanz eines Dokumentes mit Windowhandle holen
mdiChild *GetWindowInst(HWND hWnd)
  {
  return LPMDICHILD (GetWindowLong (hWnd,GWL_HWINFO));
  }

void mdiChild::WriteScaleRef (DWORD ScaleRef)
  {
  PutDocumentExtraData (DED_SCALEREC,&ScaleRef,sizeof(ScaleRef));
  }

DWORD FAR *mdiChild::GetScaleRef ()
  {
  return (DWORD FAR *) GetDocumentExtraData (DED_SCALEREC);
  }

void mdiChild::SetCreationFlag (BOOL flag)
  {
  PutDocumentExtraData (DED_CREATIONFLAG,&flag,sizeof(flag));
  }

//---------------------------------------------------------------------------
//  GetDataWithCodeData
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct GetDataWithCode_param {
  WORD parSize;
  DWORD cfRef;
  DWORD Code;
  };
#pragma pack()

BOOL GetDataWithCodeData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDataWithCode_param FAR *par = (GetDataWithCode_param FAR *) param;
    int Code = c->ReadConstInt (par->Code);
    int size ;
    LPVOID Data = c->GetDocumentExtraData (Code,&size);
    if (Data != NULL)
      c->WritelData (par->cfRef,Data,size,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->cfRef,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//  GetDataWithChildCode
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct GetDataWithChild_Codeparam {
  WORD parSize;
  DWORD cfRef;
  DWORD child;
  DWORD Code;
  };
#pragma pack()

BOOL GetDataWithChild_Code (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDataWithChild_Codeparam FAR *par = (GetDataWithChild_Codeparam FAR *) param;
    int Code = c->ReadConstInt (par->Code);
    LPMDICHILD FAR *e = (LPMDICHILD FAR *) c->ReadlData (par->child);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    int size ;
    LPVOID Data = (*e)->GetDocumentExtraData (Code,&size);
    if (Data != NULL)
      c->WritelData (par->cfRef,Data,size,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->cfRef,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetDataWithChild_Codeparam FAR *par = (GetDataWithChild_Codeparam FAR *) param;
    c->ClearlConnection (par->child,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Code,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//  OnDocumentDestroy
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct OnDocumentDestroy_param {
  WORD parSize;
  DWORD flag;     // Flag, das bei allen Ueberlagerungen TRUE sein muss
                  // (oder nicht existieren darf)
  DWORD ExceptionProc;    // Programmteil, 
                          // der bei Problemen aufgerufen wird
  };
#pragma pack()

typedef OnDocumentDestroy_param FAR *LPONDOCDESTROY;

BOOL OnDocumentDestroy (mdiChild *c,LPVOID param,WORD mode)
  {
  // Nix weiter machen, als die Struktur fuer spaetere Zwecke setzen
  ///////////////////////////////////////////////////////////////////
  if (mode & EM_LOAD) {
    c->PutDocumentExtraData (DED_ONDESTROYPAR,&param,sizeof(param));
    }
  return FALSE ;
  }


BOOL mdiChild::CheckDocExit (BOOL doExCute)
  {
  BOOL iscorrect = TRUE ;
  LPONDOCDESTROY FAR *par = (LPONDOCDESTROY FAR *)
        GetDocumentExtraData (DED_ONDESTROYPAR);
  if ((par != NULL) && (*par != NULL)) {
    // Ueberpruefen der Flags
    DBBOOL FAR *lpflag = (DBBOOL FAR *) ReadlData ((*par)->flag);
    iscorrect = ((iscorrect) && ((lpflag == NULL) || (*lpflag)));
    if (!iscorrect) {
      ExCuteProc ((*par)->ExceptionProc,EM_LOAD);
      }
    }
  return iscorrect;
  }

#pragma pack(1)
struct SetMouseScale_param {
  WORD parSize;
  DWORD sc;
  };
#pragma pack()

BOOL SetMouseScale (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetMouseScale_param FAR *par = (SetMouseScale_param FAR *) param;
    tr2 FAR *lpsc = (tr2 FAR *) c->ReadlData (par->sc);
    if (lpsc != NULL)
      c->PutDocumentExtraData (DED_MOUSESCALE,lpsc,sizeof(*lpsc));
    else
      c->RemoveDocumentExtraData (DED_MOUSESCALE);
    }
  if (mode & EM_FIXCONNECTION) {
    SetMouseScale_param FAR *par = (SetMouseScale_param FAR *) param;
    c->SetlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetMouseScale_param FAR *par = (SetMouseScale_param FAR *) param;
    c->ClearlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL mdiChild::CheckOnClose (BOOL doAsk,BOOL doClose)
  {
  return ((CheckDocExit (doAsk)) && (CallOnClose()));
  }

// Funktion fuer den Rechteck-Zoom-Modus
static BOOL ZoomRectWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,mdiChild *c,ZoomInfo FAR *zi)
  {
  BOOL res = FALSE;
  if ((msg == WMU_EXITZOOMMODE) ||
      ((msg >= WM_MOUSEFIRST) && (msg <= WM_MOUSELAST))) {
    PaintContext pc;
    GetDocumentContext(&pc, c->DrawContext());
    POINT pt;
    pt.x = short(LOWORD(lP));
    pt.y = short(HIWORD(lP));
    if (pt.x < 0) pt.x = 0;
    if (pt.x > pc.cr.right) pt.x = pc.cr.right;
    if (pt.y < 0) pt.y = 0;
    if (pt.y > pc.cr.bottom) pt.y = pc.cr.bottom;
    DPtoLP (pc.hDC,&pt,1);
    switch (msg) {
      case WM_LBUTTONDOWN :
        if (zi->state == ZI_STATE_CAPTURED) {
          // zuerst checken, ob Maus ueber dem Zoom-Knopf steht
          LPVOID FAR *lpcbtool = (LPVOID FAR *)zi->zoomChild->ReadlData(zi->ZoomButton);
          if ((lpcbtool != NULL) && (*lpcbtool != NULL)) {
            tool FAR *cbtool = (tool FAR *)(*lpcbtool);
            POINT bpt;
            bpt.x = short(LOWORD(lP));
            bpt.y = short(HIWORD(lP));
            ClientToScreen(c->OutWnd(),&bpt);
            ScreenToClient(cbtool->Parent->Parent->hWndToolbar(),&bpt);
            if (PtInRect(LPRECT(&cbtool->ToolRect),bpt)) {
              zi->state = ZI_STATE_BUTTONUP;
              break;
              }
            }
          zi->state = ZI_STATE_DRAWBOX;
          zi->newx1 = zi->newx2 = pt.x;
          zi->newy1 = zi->newy2 = pt.y;
          DrawZoomRect(&pc,zi->newx1,zi->newy1,zi->newx2,zi->newy2);
          }
        break ;

      case WMU_EXITZOOMMODE :
      case WM_MOUSEMOVE :
      case WM_LBUTTONUP :
        if (zi->state == ZI_STATE_DRAWBOX) {
          DrawZoomRect(&pc,zi->newx1,zi->newy1,zi->newx2,zi->newy2);
          if (msg != WMU_EXITZOOMMODE) {
            zi->newx2 = pt.x;
            zi->newy2 = pt.y;
            DrawZoomRect(&pc,zi->newx1,zi->newy1,zi->newx2,zi->newy2);
            }
          }
        if (msg == WM_MOUSEMOVE) break ;
        BOOL dozoom = TRUE;
        LPVOID FAR *lpcbtool = (LPVOID FAR *)zi->zoomChild->ReadlData(zi->ZoomButton);
        if (msg == WMU_EXITZOOMMODE) {
          dozoom = FALSE;
          }
        else {
          if (zi->state == ZI_STATE_BUTTONUP) {
            DBWIN_ASSERT((lpcbtool != NULL) && (*lpcbtool != NULL));
            tool FAR *cbtool = (tool FAR *)(*lpcbtool);
            POINT bpt;
            bpt.x = short(LOWORD(lP));
            bpt.y = short(HIWORD(lP));
            ClientToScreen(c->OutWnd(),&bpt);
            ScreenToClient(cbtool->Parent->Parent->hWndToolbar(),&bpt);
            if (PtInRect(LPRECT(&cbtool->ToolRect),bpt)) {
              dozoom = FALSE;
              }
            else {
              zi->state = ZI_STATE_CAPTURED;
              break;
              }
            }
          }
        ReleaseCapture();
        zi->state = ZI_STATE_ZOOMDONE;
        ZoomRectActive = FALSE;
        pt.x = pc.cr.left;
        pt.y = pc.cr.top;
        DPtoLP (pc.hDC,&pt,1);
        zi->oldx1 = pt.x;
        zi->oldy1 = pt.y;
        pt.x = pc.cr.right;
        pt.y = pc.cr.bottom;
        DPtoLP (pc.hDC,&pt,1);
        zi->oldx2 = pt.x;
        zi->oldy2 = pt.y;
        if (dozoom)
          c->DrawContext()->ZoomRect(zi->newx1,zi->newy1,zi->newx2,zi->newy2);
        // jetzt noch CheckButton wieder ausschalten
        if ((lpcbtool != NULL) && (*lpcbtool != NULL)) {
          tool FAR *cbtool = (tool FAR *)(*lpcbtool);
          tool_button FAR *cbpar = (tool_button FAR *)cbtool->StructData;
          BOOL dummy = FALSE;
          toolbar_cbdata FAR * tbd = (toolbar_cbdata FAR *) cbpar->hd.MyTool->privData;
          if (tbd->Extra) {
            SAVEREC sr;
            c->SetRecsForUpdate (sr,tbd->Extra);
            SetExtraInfo s (tbd->c,tbd->Extra);
            tbd->c->WritelData (cbpar->Id,&dummy,sizeof(dummy),NULL);
            }
          else
            tbd->c->WritelData (cbpar->Id,&dummy,sizeof(dummy),NULL);
          }
        SetCursor(zi->OldCursor);
        SetFocus (c->OutWnd());
        break ;
      }
    }
  else {
    if (msg != WM_CLOSE)
      res = (BOOL)DefWindowProc (hWnd,msg,wP,lP);
    }

  if (((zi->state == ZI_STATE_CAPTURED) ||
       (zi->state == ZI_STATE_DRAWBOX)) &&
      (msg == WM_MOUSEMOVE)) {
    // zusaetzlich noch Mouse-Cursor setzen
    LPVOID FAR *lpcbtool = (LPVOID FAR *)zi->zoomChild->ReadlData(zi->ZoomButton);
    if ((zi->state == ZI_STATE_CAPTURED) &&
        ((lpcbtool != NULL) && (*lpcbtool != NULL))) {
      tool FAR *cbtool = (tool FAR *)(*lpcbtool);
      POINT bpt;
      bpt.x = short(LOWORD(lP));
      bpt.y = short(HIWORD(lP));
      ClientToScreen(c->OutWnd(),&bpt);
      ScreenToClient(cbtool->Parent->Parent->hWndToolbar(),&bpt);
      if (PtInRect(LPRECT(&cbtool->ToolRect),bpt))
        SetCursor(LoadCursor (NULL, IDC_ARROW));
      else
        SetCursor(zi->ZoomCursor);
      }
    else
      SetCursor(zi->ZoomCursor);
    }

  return res;
  }


//****************************************************************************
//*
//*  ChildProc  (WNDPROC)
//*
//****************************************************************************
extern void SetNewMoverDimension (HWND hWnd,LONG lParam);
extern int SetNewFormToolDimension (HWND hWnd, int cx, int cy);
extern void CheckWMCommand (HWND hWnd,WPARAM wP);
LONG mdiChild::ChildProc(HWND hWnd, UINT msg, WPARAM wP, LPARAM lP, BOOL *done)
  {
  *done = FALSE ;
  LONG RetVal = 0L ;

  int FAR *pmin,FAR *pmax,FAR *ppos;
  /*----< Bearbeitung der Nachrichten >-----*/
  ZoomInfo FAR *zi = (ZoomInfo FAR *) GetDocumentExtraData (DED_ZOOMBUTTON);
  if ((zi != NULL) && (zi->state != ZI_STATE_ZOOMDONE)) {
    // Zoom-Modus aktiv
    ZoomRectWndProc (hWnd,msg,wP,lP,this,zi);
    return 0L;
    }
  if (TrackWndProc (hWnd,msg,wP,lP,&GetOutData()->twd)) {
    *done = TRUE ;
    return 0L;
    }

#ifdef UEBERLEGT
  if ((schd->Type == CHWND_TRACING) || (schd->Type == CHWND_VTO)) {
#endif
    MAPINFO msemap;
    msemap.x0    = GetOutData()->_x0;
    msemap.y0    = GetOutData()->_y0;
    msemap.scale = GetOutData()->_scale;
    msemap.xp    = GetOutData()->_xp;
    msemap.yp    = GetOutData()->_yp;
#ifdef UEBERLEGT
    tr2 FAR *sc  = (tr2 FAR *) GetDocumentExtraData (DED_MOUSESCALE);
    if (sc != NULL) {
      msemap.scdefined = TRUE ;
      lmemcpy (&msemap.sc,sc,sizeof(msemap.sc));
      }
    else
#endif
      msemap.scdefined = FALSE ;
    DigiMsg (hWnd,msg,wP,lP,done,&msemap);
    if (*done) return 0L;
#ifdef UEBERLEGT
    }
#endif

  switch (msg) {
    case WM_CLOSE:
      if (!ZoomRectActive)
        *done = !CheckOnClose (TRUE,TRUE);
      else
        *done = TRUE;
      RetVal = 0L;
      break;

    case WM_GETMINMAXINFO :
      {
      MINMAXINFO FAR *lpmmi = (MINMAXINFO FAR *) lP ;
      lpmmi->ptMinTrackSize.x = GetSystemMetrics (SM_CXSCREEN) / 4 - 1;
      lpmmi->ptMinTrackSize.y = GetSystemMetrics (SM_CYSCREEN) / 3 - 1;
      *done = FALSE ;
      }
      break ;

    case WM_SIZE:
#ifdef STRICT
      RetVal = CallWindowProc ((WNDPROC)DefaultHandler_base,hWnd,msg,wP,lP);
#else
      RetVal = CallWindowProc ((FARPROC)DefaultHandler_base,hWnd,msg,wP,lP);
#endif
      SetNewMoverDimension (hWnd,lP);
      SetNewFormToolDimension (hWnd, LOWORD(lP), HIWORD(lP));
      SizeChanged ();
      break ;

    case WM_DESTROY:
      // So nicht, Schliessen nur durch den Vater
      GetAsync_cmdfifo()->DelDocumentEntrys (DocumentID());
      NoFurtherUpdates (DocumentID());
      if (!closed)
        // Der Vater wird dann die Instanz loeschen
        PostMessage (WBase::hFrameWin,WMU_DESTROYCHILD,0,DocumentID());
      // Position abspeichern
      CloseChilds ();
      ResetWindowHandles (GetOutData()->_MyHandle);
      GetOutData()->_MyHandle = 0;

      PrgStat.SetStatus ("");

#ifndef WIN32
      ResetSLTimer (hWnd) ;
#endif
      break;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      //--------------------------------------------------
      // Diese WM_COMMAND kommt von der rechten Maustaste
      // kontextsensitives Menu
      //--------------------------------------------------
      if (ContextObject != NULL) {
        ContextObject->OnCommand (CRACKER_wID);
        ContextObject = NULL;
        }
      else 
        CheckWMCommand (hWnd,CRACKER_wID);

      break;


    /*----< Paintmessage: weiterreichen >----*/
    case WM_PAINT :
      ToScreen (hWnd);
      break ;
    /*----< Scrollmessage: Bearbeiten und sinnvolle Daten weiterleiten >---*/
    case WM_HSCROLL :
    case WMU_HSCROLL :
      pmin = &GetOutData()->hmin , pmax = &GetOutData()->hmax , ppos = &GetOutData()->hpos ;
    case WM_VSCROLL :
    case WMU_VSCROLL :
      {
      if ((msg == WM_VSCROLL) || (msg == WMU_VSCROLL))
        pmin = &GetOutData()->vmin , pmax = &GetOutData()->vmax , ppos = &GetOutData()->vpos ;
      int oldpos = *ppos ;
#ifdef WIN32
      switch (LOWORD(wP)) {
#else
      switch (wP) {
#endif
        case SB_LINEUP :
          *ppos -= 1 ;
          break ;
        case SB_LINEDOWN :
          *ppos += 1 ;
          break ;
        case SB_PAGEUP :
          *ppos -= 5 ;
          break ;
        case SB_PAGEDOWN :
          *ppos += 5 ;
          break ;
        case SB_THUMBPOSITION :
#ifdef WIN32
          *ppos = short(HIWORD(wP));
#else
          *ppos = short(LOWORD(lP));
#endif
          break ;
        case SBU_THUMBVAL :
#ifdef WIN32
          *ppos += short(HIWORD(wP));
#else
          *ppos += short(LOWORD(lP));
#endif
          break ;
        default :
          break ;
        }
      // Grenzen duerfen nicht ueberschritten werden
      *ppos = max(*pmin,min(*pmax,*ppos));
      if (*ppos != oldpos) {
        if ((msg == WM_HSCROLL) || (msg == WMU_HSCROLL)) {
          int dxs ;
          {
          PaintContext pchlp;
          GetDocumentContext (&pchlp,this);
          dxs = pchlp.XLOGtoPHYS(GetOutData()->_xunit) - 1;
          }
          SetScrollPos (hWnd,SB_HORZ,*ppos,TRUE);
          StartExternPaint ();
          RECT r;
          GetClientRect (hWnd,&r);
          int hx = *ppos - oldpos ;
          if (hx > 0) {
            r.right = r.left + hx * dxs ;
            }
          else {
            r.left = r.right + hx * dxs ;
            }
          ValidateRect (hWnd,&r);
          UpdateWindow (hWnd);  // Vor dem Scrollen muss gueltiger Inhalt
                                // des nach wie vor sichtbaren Bereiches
                                // muss sichergestellt werden
          ScrollHorizontal(*ppos - oldpos);
          EndExternPaint ();
          }
        else {
          int dys ;
          {
          PaintContext pchlp ;
          GetDocumentContext (&pchlp,this);
          dys = pchlp.XLOGtoPHYS(GetOutData()->_yunit) - 1;
          }
          StartExternPaint ();
          SetScrollPos (hWnd,SB_VERT,*ppos,TRUE);
          RECT r;
          GetClientRect (hWnd,&r);
          int hy = *ppos - oldpos ;
          if (hy > 0)
            r.bottom = r.top + hy * dys ;
          else
            r.top = r.bottom + hy * dys ;
          ValidateRect (hWnd,&r);
          UpdateWindow (hWnd);
          ScrollVertikal(*ppos - oldpos);
          EndExternPaint ();
          }
        }
      }
      break ;
    /*-------< Eine Instanz setzt die Balken selber >----*/
    case WMU_VSIZECHANGE :
      if (GetOutData()->vmax >= GetOutData()->vmin) {
        if (GetOutData()->vmax == 0) // Scrollbar noch nicht angezeigt
          ShowScrollBar (hWnd,SB_VERT,TRUE);

        SetScrollRange (hWnd,SB_VERT, GetOutData()->vmin = LOWORD(lP), GetOutData()->vmax = HIWORD(lP), FALSE);
        SetScrollPos (hWnd,SB_VERT,GetOutData()->vpos = wP,TRUE);
        }
      else
        ShowScrollBar (hWnd,SB_VERT,FALSE);
      break ;

    case WMU_HSIZECHANGE :
      if (GetOutData()->hmax >= GetOutData()->hmin) {
        ShowScrollBar (hWnd,SB_HORZ,TRUE);
        SetScrollRange (hWnd,SB_HORZ, GetOutData()->hmin = LOWORD(lP), GetOutData()->hmax = HIWORD(lP), FALSE);
        SetScrollPos (hWnd,SB_HORZ,GetOutData()->hpos = wP,TRUE);
        }
      else
        ShowScrollBar (hWnd,SB_HORZ,FALSE);
      break ;
    case WMU_CLOSEGAUSS:
      CloseGauss ();
      break ;
    /*-------< Meldungen, die an eine speziellere Funktion weitergeleitet
                        werden muessen >--------------*/
    case WM_KEYDOWN:
// funktioniert nicht!!!!
/**************************************************
      if ((msg == WM_KEYDOWN) && (wP == VK_F9)) {
        ToggleSize();
        break ;
        }
***************************************************/
    case WM_CHAR:
    case WMU_DIGITIZED:
    case WMU_DIGNEXT:
    case WMU_DIGPREV:
    case WMU_DIGDEL:
      if ((msg == WMU_DIGITIZED) || (msg == WMU_DIGNEXT) || (msg == WMU_DIGPREV) || (msg == WMU_DIGDEL)) {
        if (schd->Type != CHWND_ENTER) {
          // nur wenn nicht Musterpunkteingabe
          ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnDigitized (msg,GLOBALHANDLE (lP));
          break ;
          }
        }
    case WM_KEYUP:
    case WM_LBUTTONDOWN :
      if ((msg == WM_LBUTTONDOWN) && (GetFocus () != hWnd))
        SetFocus (hWnd);
    case WM_LBUTTONUP :
    case WM_LBUTTONDBLCLK :
    case WM_RBUTTONDOWN :
    case WM_RBUTTONUP :
    case WM_SETCURSOR :
    case WM_MOUSEMOVE :
    case WM_NCMOUSEMOVE :
    case WM_NCLBUTTONDOWN :
    case WM_NCLBUTTONUP :
      if (msg == WM_MOUSEMOVE)
        DocExplain (this);
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
    case WM_TIMER:
    case WM_PALETTECHANGED:
    case WM_PALETTEISCHANGING:
    case WM_QUERYNEWPALETTE:
    case WMU_PARDEACTIVATE:
    case WMU_STATECHANGE:
    case WMU_DOSCROLL:
    case WMU_FIELDVSIZECHANGE:
    case WMU_FIELDHSIZECHANGE:
    case WMU_CLOSEZOOM:
    case WMU_ZOOMWINPRESSED:
    case WMU_SELCHANGE:
    case WMU_CARETSET:
    case WMU_ZOOMSIZECHANGE:
    case WMU_GETLUCORNER:
    case WMU_MOUSEOUTOFWND:
    case WMU_MOUSEINWND:
    case WMU_SCANSTART:
      RetVal = SpcFnc (hWnd,msg,wP,lP,done);
      break ;

    case WM_ERASEBKGND :
      RetVal = SpcFnc (hWnd,msg,wP,lP,done);
      break ;

    case WMU_XFERDONE:
      if (GetOutData()->ActScanPtr != NULL)
        ((FrmImage FAR *)GetOutData()->ActScanPtr)->OnScanReady();
      *done = TRUE;
      break ;

    case WMU_VALREAD:
      if (!IsDocLocked(schd->TRef[0].TableNr))
        RetVal = SpcFnc (hWnd,msg,wP,lP,done);
      break ;
    case WMU_RECCHANGED :
     if ((FrmObjectList FAR *) GetOutData()->_ObjectList != NULL)
       ((FrmObjectList FAR *) GetOutData()->_ObjectList)->OnRecChange (wP);
      break ;
    default:
      *done = FALSE;
      break;
    }

  return RetVal ;
  }

//---------------------------------------------------------------------------
//  OnSizeChanged
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct OnSizeChanged_param {
  WORD parSize;
  DWORD procPtr;
  };
#pragma pack()
BOOL OnSizeChanged(mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    OnSizeChanged_param FAR *par = (OnSizeChanged_param FAR *) param;
    c->PutDocumentExtraData (DED_SIZEPROC,&par->procPtr,sizeof(par->procPtr));
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//  SetDestruktor
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct SetDestruktor_param {
  WORD parSize;
  DWORD procPtr;
  };
#pragma pack()
BOOL SetDestruktor(mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDestruktor_param FAR *par = (SetDestruktor_param FAR *) param;
    for ( int i = 0 ; (i < 10) ; i++) {
      DWORD FAR *lpD = (DWORD FAR *) c->GetDocumentExtraData (DED_SCRIPTDESTRUKTOR + i);
      if (lpD == NULL) {
        c->PutDocumentExtraData (DED_SCRIPTDESTRUKTOR + i,&par->procPtr,sizeof(par->procPtr));
        break ;
        }
      }
    if (i == 10) WIN_ASSERT (FALSE);
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//  ActivateZoom
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct ActivateZoom_param {
  WORD parSize;
  DWORD ZoomButton;   // Objekt
  };
#pragma pack()
typedef ActivateZoom_param FAR *LPACTIVATEZOOM;

BOOL ActivateZoom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPACTIVATEZOOM par = (LPACTIVATEZOOM)param;
    ZoomInfo FAR *zi = (ZoomInfo FAR *)c->DrawContext()->GetDocumentExtraData (DED_ZOOMBUTTON);
    if (zi == NULL) {
      ZoomInfo newzi;
      lmemset(&newzi,'\0',sizeof(ZoomInfo));
      c->DrawContext()->PutDocumentExtraData (DED_ZOOMBUTTON,&newzi,sizeof(ZoomInfo));
      zi = (ZoomInfo FAR *)c->DrawContext()->GetDocumentExtraData (DED_ZOOMBUTTON);
      zi->zoomChild = c;
      zi->ZoomCursor = LoadCursor(WBase::hInstance,"Lupe");
      }
    zi->ZoomButton = par->ZoomButton;
    zi->state = ZI_STATE_CAPTURED;
    ZoomRectActive = TRUE;
    // Ab jetzt Maus-Nachrichten nur mehr an mich !
    SetCapture (c->OutWnd());
    zi->OldCursor = SetCursor(zi->ZoomCursor);
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//  RestoreZoom
//
//---------------------------------------------------------------------------
BOOL RestoreZoom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ZoomInfo FAR *zi = (ZoomInfo FAR *)c->DrawContext()->GetDocumentExtraData (DED_ZOOMBUTTON);
    if (zi != NULL) {
      zi->newx1 = zi->oldx1;
      zi->newy1 = zi->oldy1;
      zi->newx2 = zi->oldx2;
      zi->newy2 = zi->oldy2;
      PaintContext pc;
      GetDocumentContext(&pc, c->DrawContext());
      POINT pt;
      pt.x = pc.cr.left;
      pt.y = pc.cr.top;
      DPtoLP (pc.hDC,&pt,1);
      zi->oldx1 = pt.x;
      zi->oldy1 = pt.y;
      pt.x = pc.cr.right;
      pt.y = pc.cr.bottom;
      DPtoLP (pc.hDC,&pt,1);
      zi->oldx2 = pt.x;
      zi->oldy2 = pt.y;
      c->DrawContext()->ZoomRect(zi->newx1,zi->newy1,zi->newx2,zi->newy2);
      SetFocus (c->OutWnd());
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct WindowScroll_param {
  WORD parSize;
  DWORD unit;   // Objekt
  };
#pragma pack()

#pragma pack(1)
struct SetDocSide_param {
  WORD parSize;
  DWORD Side;
  WORD AnzSideRec,AnzSideId;
  };
#pragma pack()
typedef SetDocSide_param FAR *LPSDSPAR;

//---------------------------------------------------------------------------
//  WindowScroll
//
//---------------------------------------------------------------------------
BOOL WindowScroll (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WindowScroll_param FAR *par = (WindowScroll_param FAR *) param;
    DBINT unit = c->ReadConstInt (par->unit);
    HWND outWnd = c->OutWnd();
    int vmin,vmax,vpos;
    GetScrollRange (outWnd,SB_VERT, &vmin, &vmax);
    vpos = GetScrollPos (outWnd,SB_VERT);

    BOOL changeAllowed = FALSE ;
    LPSDSPAR FAR *lppar = (LPSDSPAR FAR *) c->DrawContext()->GetDocumentExtraData (DED_SETDOCSIDEPAR);
    DBINT Seite = 0,AnzahlSeiten = 1;
    if (lppar != NULL) {
      LPSDSPAR par = *lppar;
      DBINT FAR *aSide = (DBINT FAR *) (c->DrawContext()->ReadlData (par->Side));
      DBINT FAR *Anz = (DBINT FAR *) (c->DrawContext()->ReadData (par->AnzSideRec,par->AnzSideId));
      DBWIN_ASSERT ((aSide != NULL) && (Anz != NULL));
      Seite = *aSide;
      AnzahlSeiten = *Anz;
      }

    if ((vpos == vmax) && (vpos + unit > vmax)) {
      if (Seite < AnzahlSeiten - 1) {
        c->DrawContext()->ChangeDocSide (1);
        unit = -vmax ;
        }
      else
        unit = 0 ;
      }
    else if ((vpos == 0) && (vpos + unit < 0)) {
      if (Seite > 0) {
        c->DrawContext()->ChangeDocSide (-1);
        unit = vmax ;
        }
      else
        unit = 0;
      }
    if (unit != 0) {
#ifdef WIN32
      SendMessage (outWnd,WMU_VSCROLL,MAKELONG(SBU_THUMBVAL,unit),0L);
#else
      SendMessage (outWnd,WMU_VSCROLL,SBU_THUMBVAL,MAKELONG(unit,0));
#endif
      }
    // bei no-auto-scroll Formularen auch noch den Focus aufs Formular setzen
    if (c->DrawContext()->GetOutData()->noAutoScroll)
      SetFocus(c->OutWnd());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WindowScroll_param FAR *par = (WindowScroll_param FAR *) param;
    c->ClearlConnection (par->unit,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//---------------------------------------------------------------------------
//  AppendFrmContextMenu
//
//---------------------------------------------------------------------------
#pragma pack(1)
struct AppendFrmContextMenu_param {
  WORD parSize;
  DWORD frmObj;
  DWORD MenuText;
  DWORD MenuProc;
  DWORD Flags;
  };
#pragma pack()

BOOL AppendFrmContextMenu (mdiChild *c,LPVOID param,WORD mode)
  {
  AppendFrmContextMenu_param FAR *par = (AppendFrmContextMenu_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)c->ReadlData (par->frmObj);

    DBWIN_ASSERT_TEXT ((lpobj != NULL) && (*lpobj != NULL), "Falsches Objekt");

    LPSTR MenuText = (LPSTR) c->ReadlData (par->MenuText);
    if (MenuText == NULL)
      DBWIN_ASSERT_TEXT (FALSE, "Ungültiger Menübezeichner im kontextsensitiven Menü");

    UINT Flags = 0;
    DBINT FAR *lpFlags = (DBINT FAR *)(c->ReadlData (par->Flags));
    if (lpFlags == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "ungültiges Menüflag im kontextsensitiven Menü");
      }
    else
      Flags = *lpFlags;

    ((LPFRMOBJ)(*lpobj))->SetContextMenu (MenuText, par->MenuProc, Flags, mode);
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)c->ReadlData (par->frmObj);

    if ((lpobj != NULL) && (*lpobj != NULL))
      ((LPFRMOBJ)(*lpobj))->RemoveContextMenu ();

    c->ClearlConnection (par->MenuText, LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Flags, LPSTR(param)-sizeof(WORD));
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->MenuText, LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Flags, LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

