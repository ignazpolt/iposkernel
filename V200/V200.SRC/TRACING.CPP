#ifdef UEBERLEGT

/********************************************************/
/*      Dokumentenbereich                               */
/********************************************************/
// $Header:   P:/marille/clinicum/rev/tracing.cpv   1.12   18 Aug 1997 18:02:14   Martin  $
// $Log:   P:/marille/clinicum/rev/tracing.cpv  $
// 
//    Rev 1.12   18 Aug 1997 18:02:14   Martin
// VTO Formular-faehig
// 
//    Rev 1.11   03 Dec 1996 16:39:10   HANNES
// LoadDone
// 
//    Rev 1.10   04 Apr 1996 18:36:02   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.9   02 Feb 1996 10:35:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   24 Aug 1995 00:20:24   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.7   10 Aug 1995 09:25:04   HANNES
// Rescale .. Nur invalidieren, wenn das neue Rechteck nicht platz haette
// 
//    Rev 1.6   20 Mar 1995 12:05:56   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.5   21 Nov 1994 20:39:14   HANNES
// Fehler in SetPrintSideOpt
// 
//    Rev 1.4   20 Sep 1994 11:38:26   HANNES
// Fehlerkorrektur im Scrolling ...
// 
//    Rev 1.3   24 Jun 1994 21:09:44   HANNES
// 
//    Rev 1.2   24 Jun 1994 21:01:12   MARTIN
// 
//    Rev 1.1   24 Jun 1994 19:51:00   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:05:26   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.32   13 Apr 1994 20:54:52   MARTIN
// unnoetige Skalierungen verhindern
// 
//    Rev 1.31   10 Mar 1994 11:25:16   MARTIN
// Palette
// 
//    Rev 1.30   20 Jan 1994 23:57:04   HANNES
// Verbessertes HScBar, VSCBar um einen normale Groessenaenderung zuzulassen
// 
//    Rev 1.29   12 Jan 1994 11:12:26   HANNES
// Unnoetige Includes Eleminiert, dfield, text.. als ganzes entfernt, 
// Scroll (Horizontal, Vertical) ohne aenderung von xm, ym
// 
//    Rev 1.28   04 Jan 1994 16:59:54   HANNES
// PageDown, PageUp Handling
// L”schen des Eingabepunktes beim Scrollen wegen Tracking
// 
//    Rev 1.27   29 Nov 1993 08:56:02   HANNES
// Neues Define ANZSCROLLS
// 
//    Rev 1.26   18 Oct 1993 19:56:50   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.25   04 Oct 1993 09:40:34   HANNES
// MapChanged in Scrollhorizontal, Scrollvertical
// 
//    Rev 1.24   22 Sep 1993 09:16:30   HANNES
// Version nach St. Poelten
// 
//    Rev 1.23   05 Sep 1993 22:15:14   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.22   23 Aug 1993 19:31:00   HANNES
// ...
// 
//    Rev 1.21   18 Aug 1993 10:35:18   HANNES
// Endgueltiger Umbau auf Tools
// 
//    Rev 1.20   05 Aug 1993 13:11:18   HANNES
// MapChanged an den richtigen Stellen aufrufen, SpcFnc voll implementiert
// 
//    Rev 1.19   15 Jul 1993 16:36:50   HANNES
// Drucker in die DMWAPI ausgelagert
// 
//    Rev 1.18   05 Jul 1993 14:45:38   HANNES
// Toolbarliste eingebaut
// 
//    Rev 1.17   23 Jun 1993 11:26:08   HANNES
// Neuzeichnen nach dem Drucken
// 
//    Rev 1.16   18 Jun 1993 15:14:54   MARTIN
// CloseChilds
// 
//    Rev 1.15   10 Jun 1993 18:36:18   HANNES
// IsPrintig Handling
// 
//    Rev 1.14   03 May 1993 15:45:56   HANNES
// Einbau eines vorlaufigen Clipboard - Handlings
// 
//    Rev 1.13   05 Apr 1993 10:29:00   HANNES
// MapChanged ()
// 
//    Rev 1.12   02 Apr 1993 17:50:24   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.11   17 Mar 1993 18:11:50   MARTIN
// 32 Bit Umstellung der Scripts
// 
//    Rev 1.10   11 Mar 1993 11:39:00   HANNES
// Mehrseitensupport, Druckbare Felder
// 
//    Rev 1.9   02 Mar 1993 22:35:52   HANNES
// ???
// 
//    Rev 1.8   22 Feb 1993 17:17:36   HANNES
// Setzen des Druckers
// 
//    Rev 1.7   17 Feb 1993 15:30:02   HANNES
// Schliessen des Subforms
// 
//    Rev 1.6   16 Feb 1993 13:17:14   HANNES
// Anpassung an die Klasse FrmObject
// 
//    Rev 1.5   14 Feb 1993 15:53:48   HANNES
// Gleiche Objekte fuer formulare und Tracings
// 
//    Rev 1.4   01 Feb 1993 12:09:04   HANNES
// Einbau der Klasse VTO-> Umaenderung der SpcFnc
// 
//    Rev 1.3   18 Jan 1993 16:50:20   HANNES
// Handling von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.2   12 Dec 1992 12:54:44   HANNES
// Nachste Korrektur bei Interger Divide by 0
// 
//    Rev 1.1   12 Dec 1992 12:17:20   HANNES
// Divide by 0 int HScBar und VScBar abfangeb
// 
//    Rev 1.0   02 Dec 1992 15:47:16   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "test.hpp"
#include "dds.hpp"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "globmem.h"
#include "dds.h"
#include "ddsmsg.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"
#define MODULENUM   126
#include "winass.hpp"

/*-------< Zeichnungen >-------*/
#define ANZSCROLLS  20
void Tracing::HScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  DBWIN_ASSERT (outContext == NULL);
  float xmid = LogToWorld (rcLogRect.left + rcLogRect.right) / float(2.0) - LogToWorld (int (float(*max) / float(2.0) - float(*pos)) * _xunit);
  PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.Map (_scale);
  int gesdist =  int (double (rcLogRect.right - rcLogRect.left) * 1.05) ;	// 5 % Reserve
  int partdist = pc.XPHYStoLOG (pc.cr.right);
  if (partdist < gesdist) {
    _xunit = partdist / ANZSCROLLS ;	// Eine Scrolleinheit eintspricht einem 
  			        // sechstel des gezeigten Bereiches
    if (_xunit < 1) _xunit = 1;
    *max = gesdist / _xunit ;
    *min = 0 ;
    *pos = (*max + *min) / 2 + WorldToLog ((xmid - LogToWorld(rcLogRect.right + rcLogRect.left) / float (2.0)) * float (1.05)) / _xunit ;
    }
  else {
    *max = *min = *pos = _xunit = 0 ;
    xmid = LogToWorld (rcLogRect.right + rcLogRect.left) / float(2.0);
    }
  // Initialisieren des Mapping - Ursprungs
  _x0 = WorldToLog (xmid) - partdist / 2 ;
  _xp = 0;
  }

void Tracing::VScBar (int FAR *min,int FAR *max,int FAR *pos)
  {
  DBWIN_ASSERT (outContext == NULL);
  float ymid = LogToWorld (rcLogRect.bottom + rcLogRect.top) / float(2.0) + LogToWorld (int (float(*max) / float(2.0) - float(*pos)) * _yunit);
  PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.Map (_scale);
  int gesdist = int (double (rcLogRect.bottom - rcLogRect.top) * 1.05) ;
  int partdist = pc.YPHYStoLOG (-pc.cr.bottom);
  if (partdist < gesdist) {
    _yunit = partdist / ANZSCROLLS ;
    if (_yunit < 1) _yunit = 1;
    *max = gesdist / _yunit ;
    *min = 0 ;
    *pos = (*max + *min) / 2 - WorldToLog ((ymid - LogToWorld(rcLogRect.top + rcLogRect.bottom) / float (2.0)) * float (1.05)) / _yunit ;
    }
  else {
    *max = *min = *pos = _yunit = 0 ;
    ymid = LogToWorld (rcLogRect.bottom + rcLogRect.top) / float(2.0);
    }
  _y0 = WorldToLog (ymid) + partdist / 2 ;
  _yp = 0;
  }

void Tracing::ScrollHorizontal (int dist)
  {
  DBWIN_ASSERT (outContext == NULL);
  PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  RestorePTB (&pc);
  pc.Map (_scale,_x0,_y0,_xp,_yp);
  _xp = pc.XScroll(-_xunit * dist);
  MapChanged ();
  UpdateWindow (_MyHandle);
  pc.Map (_scale,_x0,_y0,_xp,_yp);
  ReadPTB (&pc,_MyHandle,_scale,_x0,_y0,_xp,_yp);
  }

void Tracing::ScrollVertikal (int dist)
  {
  DBWIN_ASSERT (outContext == NULL);
  PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  RestorePTB (&pc);
  pc.Map (_scale,_x0,_y0,_xp,_yp);
  _yp = pc.YScroll(_yunit * dist);
  MapChanged ();
  UpdateWindow (_MyHandle);
  pc.Map (_scale,_x0,_y0,_xp,_yp);
  ReadPTB (&pc,_MyHandle,_scale,_x0,_y0,_xp,_yp);
  }

void Tracing::Reset ()
  {
  CallScriptDestruktor ();
  ExCute (EM_RESET);

  if (_ObjectList != NULL) {
    // Alte Loeschen und Neue aufbauen
    delete ((FrmObjectList FAR *) _ObjectList) ;
    _ObjectList = LPVOID (new FrmObjectList (this));
    }

  if (_MyHandle)
    InvalidateRect (_MyHandle,NULL,TRUE);
  _xp = _yp = _xm = _ym = 0 ;
  _x0 = _y0 = 0 ;
  }

extern void FreePens ();
extern HPEN GethActivePen ();
extern HPEN GethInactivePen ();
Tracing::~Tracing ()
  {
  if (commands) {
    ExCute (EM_RESET);
    }

  FreePens ();
  hActivePen = hInactivePen = 0;

  delete ((FrmObjectList FAR *) _ObjectList);
  _ObjectList = NULL;
  }

/***** Beispielgrapfik ******/
void ActivateTool (mdiChild *c);
void Tracing::LoadData () 
  {
  /*-----< Laden / Berechnen der Daten >-------*/
  // Alle Records loeschen
  _scale = float(1.0) ;         // Ansonsten werden sich
                                // die Felder ganz nett schoen
                                // aufregen
  ExCute (EM_LOAD | EM_FIXCONNECTION) ;
  LoadDone = TRUE ;
  SetCreationFlag (FALSE);

  if (outContext == NULL) {
    ActivateTool (this);

    // Fuer den Fall, dass noch ueberhaupt kein Punkt existiert ->
    // vernuenftig vorbelegen
    GetMinMax ();
    _xm =  (rcLogRect.right + rcLogRect.left) / 2 ;
    _ym =  (rcLogRect.top + rcLogRect.bottom) / 2 ;

    // Berechnung des Default - Mappings, damit alles Platz hat
    CalcScale ();
    InitializeBars();
    MapChanged ();

    ((FrmObjectList FAR *) _ObjectList)->Reformat ();
    }
  }

/*------< Aenderung des Skalierungsfaktors >----------*/
void Tracing::NewScale (double nscale)
  {
  DBWIN_ASSERT (outContext == NULL);
  _scale = float (nscale) ;
  scale_set = TRUE ;
  // Neuerliche Berechnung des ganzen Fensters
  InitializeBars();
  InvalidateRect (_MyHandle,NULL,TRUE);
  MapChanged ();
  ((FrmObjectList FAR *) _ObjectList)->Reformat ();
  }

void Tracing::CalcScale ()
  {
  DBWIN_ASSERT (outContext == NULL);
  if ((!scale_set) && (_MyHandle)) {
    PaintContext pc (_MyHandle,0xFFFF,0xFFFF,DO_WORK);
    pc.Map (1.0);
    int dxs = pc.XPHYStoLOG (pc.cr.right);
    int dys = pc.YPHYStoLOG (-pc.cr.bottom);
    int dxl = int (float (rcLogRect.right - rcLogRect.left) * float (1.1)) ;	// 10 % Reserve
    int dyl = int (float (rcLogRect.top - rcLogRect.bottom) * float (1.1)) ;
    if (dxl < 0) dxl = -dxl ;
    if (dyl < 0) dyl = -dyl ;
    if ((dxl > 1) && (dyl > 1)) {
      float xfact = float (dxs) / float (dxl) ;
      float yfact = float (dys) / float (dyl) ;
      _scale = min (float (4.0), max (float (0.25) , min (xfact,yfact))) ;
      }
    else
      _scale = float(1.0);      // Da ist was hoechst faul
    }
  }

LONG Tracing::ToScreen (HWND hWnd)
  {
  DBWIN_ASSERT (outContext == NULL);
  PaintContext pc (hWnd);
  LONG RetValue = 0L;
  if (!IsPrinting) {
    pc.Map (_scale,_x0,_y0,_xp,_yp);
    RetValue = Paint (&pc) ;
    }
  return RetValue ;
  }

LONG Tracing::ToPrinter (Printer *Pr,BOOL firstBand,WORD partNo)
  {
  DBWIN_ASSERT (outContext == NULL);
  PaintContext pc (Pr) ;
  pc.Map (_scale,_x0,_y0,_xp,_yp);
  LONG RetValue = Paint (&pc) ;
  return RetValue;
  }

LONG Tracing::Paint (PaintContext *pc)
  {
  if (CheckMapChanged) {
    if (_ObjectList != NULL)
      ((FrmObjectList FAR *) _ObjectList)->OnMapChange ();
    CheckMapChanged = FALSE ;
    }
  // Zeichnen der Objekt - Graphik
  if (_ObjectList != NULL) {
    ((FrmObjectList FAR *) _ObjectList)->Paint (pc);
    }
    
  ShowName ();
  return 0L ;
  }

void Tracing::GetMinMax (BOOL forScreen)
  {
  RECT r;
  ((FrmObjectList FAR *) _ObjectList)->GetMinMax (&r,forScreen);
  CopyRect(LPRECT(&rcLogRect),&r);
  MyUnionRect (LPRECT(&rcLogRect),LPRECT(&rcLogRect),LPRECT(&rcLogRect));
  }

void Tracing::RecalcScale ()
  {
  // Skalierungsfaktor setzten
  DBWIN_ASSERT (outContext == NULL);
  scale_set = FALSE ;

  GetMinMax ();

  _xm = (rcLogRect.left + rcLogRect.right) / 2 ;
  _ym = (rcLogRect.top  + rcLogRect.bottom) / 2 ;

  float oldscale = _scale;
  CalcScale ();
  if (fabs(_scale - oldscale) > 1.0E-4) {
    // Client neu zeichnen
    InitializeBars();

    MapChanged ();
    if (_ObjectList != NULL)
      ((FrmObjectList FAR *) _ObjectList)->Reformat ();
    InvalidateRect (_MyHandle,NULL,TRUE);
    }
  }


LONG FAR PASCAL Tracing::SpcFnc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done)
  {
  LONG RetVal = 0L;

  BOOL ontop = TRUE;
  switch (msg) {
    case WM_MOUSEMOVE :
      // Untersuchen der aktuellen Mouseposition
      ((FrmObjectList FAR *) _ObjectList)->OnMouseMove (wP,lP);
      break ;

    case WM_LBUTTONDBLCLK :
      ((FrmObjectList FAR *) _ObjectList)->OnLButtonDblClk (wP,lP);
      break ;

    case WM_LBUTTONUP :
      // Mouse wurde gedrueckt -> Zuerst einmal untersuchen,
      // welches Feld gemeint werden koennte
      ((FrmObjectList FAR *) _ObjectList)->OnLButtonUp (wP,lP);
      break ;

    case WM_LBUTTONDOWN :
      ((FrmObjectList FAR *) _ObjectList)->OnLButtonDown (wP,lP);
      break ;

    case WM_CHAR :
      ((FrmObjectList FAR *) _ObjectList)->OnChar (wP);
      break ;

    case WM_SETFOCUS :
      ((FrmObjectList FAR *) _ObjectList)->OnSetFocus ();
      break ;

    case WM_SETCURSOR :
      if (LOWORD(lP) == HTCLIENT)
        return (*done = ((FrmObjectList FAR *) _ObjectList)->OnSetCursor());
      break ;

    case WM_KEYDOWN :
      if ((wP == VK_INSERT) && (GetKeyState (VK_CONTROL) < 0)) {
        HDC hdcMeta = CreateMetaFile (NULL);
        PaintContext pc;
        pc.mode = DO_EXTERN ;
        pc.hOldPen = pc.hPen = 0 ;
        pc.hOldBrush = 0 ;
        pc.x0 = pc.y0 = 0 ;
        pc.hDC = hdcMeta;
        pc.Map (1.0,rcLogRect.left,rcLogRect.bottom);
        Paint(&pc);
        pc.mode = NO_MODE ;
        HANDLE hMF = CloseMetaFile (hdcMeta);
        HANDLE hPict = GlobalAlloc (GMEM_DDESHARE, sizeof (METAFILEPICT));
        LPMETAFILEPICT lppict = (LPMETAFILEPICT)GlobalLock (hPict) ;
        lppict->mm   =  MM_ISOTROPIC;
        lppict->hMF  =  hMF;
        int dx = rcLogRect.left - rcLogRect.right;
        int dy = rcLogRect.top - rcLogRect.bottom;
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
      if (wP == VK_PRIOR)
        ChangeDocSide (-1);
      else if (wP == VK_NEXT)
        ChangeDocSide (1);
      else
        ((FrmObjectList FAR *) _ObjectList)->OnKeyDown (wP);
      break ;

    case WM_KILLFOCUS :
      ((FrmObjectList FAR *) _ObjectList)->OnKillFocus ();
      break ;

    case WM_RBUTTONDOWN :
      ToggleScale ();
      break ;

    case WM_PALETTECHANGED:
      *done = TRUE;
      if (hWnd == (HWND) wP)
        return FALSE;
      ontop = FALSE;
    case WM_QUERYNEWPALETTE:
      *done = TRUE;
      return ((FrmObjectList FAR *) _ObjectList)->OnPalChange (hWnd, ontop);

    default :
      RetVal = mdiChild::SpcFnc (hWnd,msg,wP,lP,done);
      break ;
    }

  return RetVal ;
  }

// #define LEFTTOP
void Tracing::SetPrintSideOpt (BOOL autoscale,double sc)
  {
  RECT r;
  _scale = float(1.0) ;
  Pr->GetPrinterArea (&r);

  GetMinMax ();
  _xp = (r.left + r.right) / 2 ;
  _yp = (r.top + r.bottom) / 2 ;
  _x0 = (rcLogRect.left + rcLogRect.right) / 2;
  _y0 = (rcLogRect.top + rcLogRect.bottom) / 2;
  if (autoscale) {
    PaintContext pcprinter (Pr);
    pcprinter.Map (1.0);
    float xscale,yscale;
    int xlog = pcprinter.XPHYStoLOG (r.right - r.left);
    int xlogmax = int (float (rcLogRect.right - rcLogRect.left) * _scale);
    if (xlog < 0) xlog = -xlog;
    xscale = float (xlog) / float (xlogmax);
    int ylog = pcprinter.YPHYStoLOG (r.bottom - r.top);
    int ylogmax = int (float (rcLogRect.bottom - rcLogRect.top) * _scale);
    if (ylog < 0) ylog = -ylog;
    yscale = float (ylog) / float (ylogmax) ;
    _scale = min (xscale,min(yscale,float (1.0)));
    }
  else
    _scale = float (sc);

  if (_ObjectList != NULL)
    ((FrmObjectList FAR *) _ObjectList)->Reformat ();
  }

BOOL Tracing::IsSidePrinted ()
  {
  if (_ObjectList != NULL)
    ((FrmObjectList FAR *) _ObjectList)->Reformat ();

  return TRUE;
  }

void Tracing::GetDocInfo (int cmd,DWORD FldId,LPVOID Buffer)
  {
  switch (cmd) {
    case GETMAPTYPE :
      *((int FAR *) Buffer) = MAPTYPE_GEOMETRIC ;
      break ;
    case GETWINDOWORG :
      ((POINT FAR *) Buffer)->x = OutX0() ;
      ((POINT FAR *) Buffer)->y = OutY0() ;
      break ;
    default :
      mdiChild::GetDocInfo (cmd,FldId,Buffer);
    }
    
  }

Tracing::Tracing (LPSCRIPTCONTENT scent) : mdiChild (scent)
  { 
  hInactivePen = GethInactivePen ();
  hActivePen   = GethActivePen ();

  _ObjectList = LPVOID (new FrmObjectList (this));
  }

void Tracing::Rescale (LPRECT rcnr)
  {
  // Kontrolle, ob Recteck noch mit dem dargestellten Skalierungsbereich
  // uebereinstimmt
  DBWIN_ASSERT (outContext == NULL);
  RECT r;
  MyUnionRect (&r,LPRECT(&rcLogRect),rcnr);
  BOOL doIt;
  if (!lmemcmp (&r,&rcLogRect,sizeof(r))) {
    CopyRect (LPRECT(&rcLogRect),&r);
    // Ueberpruefung, ob das Rechteck noch in dem Ausgabebereich liegt
    if (IsWindow(_MyHandle)) {
      PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
      pc.Map (_scale,_x0,_y0,_xp,_yp);
      RECT rc,rc1,rc2;
      pc.LogRecttoPhys(&rc,&r);
      int dummy;
      if (rc.top > rc.bottom) 
        dummy = rc.bottom , rc.bottom = rc.top , rc.top = dummy;
      if (rc.left > rc.right) 
        dummy = rc.left , rc.left = rc.right , rc.right = dummy;
      GetClientRect (_MyHandle,&rc1);
      IntersectRect (&rc2,&rc1,&rc);
      if (lmemcmp (&rc2,&rc,sizeof(rc))) doIt = FALSE ;
      else                               doIt = TRUE ;
      }
    _xm = (rcLogRect.left + rcLogRect.right) / 2 ;
    _ym = (rcLogRect.top + rcLogRect.bottom) / 2 ;
    if ((!scale_set) && (IsWindow(_MyHandle)) && (doIt)) {
      CalcScale ();
      InitializeBars ();
      MapChanged ();
      InvalidateRect (_MyHandle,NULL,TRUE);

      DWORD FAR *scref = GetScaleRef();
      if (scref != NULL)
        WritelData (*scref,&_scale,sizeof(_scale),NULL);
      }
    else if (IsWindow (_MyHandle)) {
      int xpold = _xp;
      int ypold = _yp;
      int x0old = _x0;
      int y0old = _y0;
      InitializeBars();
      _xp = xpold ;
      _yp = ypold ;
      _x0 = x0old ; 
      _y0 = y0old ; 
      }
    }
  }

#endif

