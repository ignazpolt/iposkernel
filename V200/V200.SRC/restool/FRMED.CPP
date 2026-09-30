///////////////////////////////////////////////////////////////////
//  Implementierung des Formulareditors
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/frmed.cpv   1.26   05 Oct 1998 11:26:08   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/frmed.cpv  $
// 
//    Rev 1.26   05 Oct 1998 11:26:08   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.25   05 Nov 1997 09:13:18   Gerhold
// 32 Bit
// 
//    Rev 1.24   28 Aug 1997 15:49:18   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.23   24 Mar 1996 12:16:34   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.22   02 Feb 1996 10:50:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.21   27 Aug 1995 13:00:32   HANNES
// 
//    Rev 1.20   23 Aug 1995 11:05:18   GERHOLD
// 
//    Rev 1.19   12 Aug 1995 14:57:28   GERHOLD
// Verschieben der Elemente mit Hilfe der Cursortasten
// 
//    Rev 1.18   07 Aug 1995 20:55:38   GERHOLD
// Formular vergroessert sich (MDI-Child ist sofort maximiert)
// 
//    Rev 1.17   23 May 1995 12:20:20   GERHOLD
// 
//    Rev 1.16   23 May 1995 12:00:10   GERHOLD
// bessere Seitenverwaltung fuer Dokumente
// 
//    Rev 1.15   31 Mar 1995 18:23:36   HANNES
//  
// 
//    Rev 1.14   31 Mar 1995 12:49:40   GERHOLD
// MI_DESTROYDIALOG, MI_STOREDIALOG kommen jetzt wieder durch
// 
//    Rev 1.13   21 Mar 1995 16:25:14   HANNES
// 
//    Rev 1.12   20 Mar 1995 08:44:50   HANNES
//  
// 
//    Rev 1.11   08 Mar 1995 09:13:18   GERHOLD
// 
//    Rev 1.10   02 Jan 1995 09:29:50   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.8   17 Oct 1994 14:54:32   HANNES
// Tracing eingebaut
// 
//    Rev 1.7   06 Oct 1994 19:25:30   HANNES
// Erweiterung der DLLCHILD Funktionen
// 
//    Rev 1.6   20 Sep 1994 11:26:00   HANNES
// Verschiedene neue Funktionen
// 
//    Rev 1.5   10 Aug 1994 12:07:46   GERHOLD
// Doppelclick fuer Edit-Elemente in RESTOOL
// 
//    Rev 1.4   05 Aug 1994 20:55:02   HANNES
// FrmTime
// 
//    Rev 1.3   25 Jul 1994 17:15:00   HANNES
// 
//    Rev 1.2   25 Jul 1994 10:43:18   HANNES
// 
//    Rev 1.1   25 Jul 1994 09:39:56   HANNES
// 
//    Rev 1.0   12 Jul 1994 14:43:38   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "wonscrip.hpp"
#define MODULENUM 28
#include "winass.hpp"

#define JUST_EM
#include "dds.hpp"

#include "font.hpp"
#include "cfield.hpp"
#define NODLL
#include "toolbar.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"

#include "drdrop.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define DLLCHILD_MAIN
#include "dllchild.hpp"

#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "image.hpp"
#include "frmobj3.hpp"

#include "template.hpp"
#include "hlines.hpp"

#include "misc.hpp"

#include "msdntb.h"
#include "blandmdi.h"
#include "blandmdi.hpp"   // MakeNewChild

//#include "statbar.hpp"

extern HINSTANCE MyInstance;
extern HWND hOptWnd ;
extern HWND hRefWnd;
extern hash FAR *defines;
extern hash *objHash;
extern char _MyObjectName [32];
extern char _MyScreenName [32];
extern WORD FrmType;
extern LPDIALOGELEM firstElem;

extern LPSTR IniFile();


extern int GetAnzSides ();
extern LPSHOWOBJECT FindShowForElem (LPDIALOGELEM x);
extern int GetSideFromShow (LPSHOWOBJECT so);


HWND hWndToolbarForm = NULL;

static BOOL bPreviewForm = FALSE;     // Formular nur sehen, nicht bearbeiten
static BOOL bShowRaster = FALSE;

static int AnzSides = 0;
static int ActSide = 0;


static int XRasterIn_mm = 5;
static int YRasterIn_mm = 5;

inline BOOL IsRasterEnabled ()
  { return bShowRaster; }

inline void EnableRaster (BOOL bEnable)
  { bShowRaster = bEnable; }
  
inline void GetRasterUnits (int FAR *x, int FAR *y)
  { *x = XRasterIn_mm; *y = YRasterIn_mm; }

inline void SetRasterUnits (int x, int y)
  { XRasterIn_mm = x; YRasterIn_mm = y; }

inline char *FRMName() { return "FrmEdit" ; }

void ReadFrmPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetPrivateProfileInt (FRMName(),"_X",100,IniFile());
  *y = GetPrivateProfileInt (FRMName(),"_Y",100,IniFile());
  *w = GetPrivateProfileInt (FRMName(),"_W",200,IniFile());
  *h = GetPrivateProfileInt (FRMName(),"_H",200,IniFile());
  }

void WriteFrmPos (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  int w = r.right - r.left + 1;
  int h = r.bottom - r.top + 1;
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (FRMName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (FRMName(),"_Y",outstring,IniFile());
  wsprintf (outstring,"%d",w);
  WritePrivateProfileString (FRMName(),"_W",outstring,IniFile());
  wsprintf (outstring,"%d",h);
  WritePrivateProfileString (FRMName(),"_H",outstring,IniFile());
  }

#define MAXSCPOS    100
#define STEPWIDTH    50
static int hpos,vpos ;
static float _scale;
static int _AnzSides;
static int _ActSide;
static HPEN _hActivePen;
static HPEN _hInactivePen;
void PaintObjs (PaintContext *pc, int Page);

inline int x0pos() { return MAXSCPOS / 2 * STEPWIDTH ; }
inline int y0pos() { return MAXSCPOS / 2 * STEPWIDTH ; }
inline int xv() { return -(hpos * STEPWIDTH - x0pos()) ; }
inline int yv() { return -(vpos * STEPWIDTH - y0pos()) ; }
void ModifyContext (PaintContext *pc, int Offset = 0)
  {
  switch (FrmType) {
    case FORMTYPE_FORM :
      pc->LogicalTwips (-(hpos * STEPWIDTH - x0pos()) + Offset,-(vpos * STEPWIDTH - y0pos()),_scale);
      break ;
    case FORMTYPE_TRACING :
      pc->Map (_scale,0,0,-(hpos * STEPWIDTH - y0pos()),-(vpos * STEPWIDTH - y0pos()));
      break ;
    }
  }

HWND hFrmWnd;
void toLog (LPPOINT pt)
  {
  PaintContext pc (hFrmWnd,0xFFFF,0xFFFF,DO_WORK);
  ModifyContext (&pc);
  DPtoLP (pc.hDC,pt,1);
  }

void toDev (LPPOINT pt)
  {
  PaintContext pc (hFrmWnd,0xFFFF,0xFFFF,DO_WORK);
  ModifyContext (&pc);
  LPtoDP (pc.hDC,pt,1);
  }

void _FrmObj::ToLogKoords (int FAR *dx,int FAR *dy)
  {
  PaintContext pc (hFrmWnd,0xFFFF,0xFFFF,DO_WORK);
  ModifyContext (&pc);
  if (FrmType == FORMTYPE_FORM) {
    if (dx != NULL)
      *dx = pc.XPHYStoLOG(*dx);
    if (dy != NULL)
      *dy = pc.YPHYStoLOG(*dy);
    }
  else {
    if (dx != NULL)
      *dx = pc.XPHYStoLOG(*dx) * 4 ;
    if (dy != NULL)
      *dy = pc.YPHYStoLOG(*dy) * 4 ;
    }
  }

void _FrmObj::ToAbsLogKoords (int FAR *x,int FAR *y)
  {
  POINT pt;
  pt.x = *x ; pt.y = *y ;
  toLog (&pt);
  if (FrmType == FORMTYPE_FORM) {
    *x = pt.x ; *y = pt.y ;
    }
  else {
    *x = pt.x * 4 ; *y = pt.y * 4 ;
    }
  }

void _FrmObj::ToPointKoords (int x,int y,double FAR *xf,double FAR *yf)
  {
  if (FrmType == FORMTYPE_FORM) {
    *xf = double(x);
    *yf = double(y);
    }
  else {
    *xf = double(x) / 100.0 ;
    *yf = double(y) / 100.0 ;
    }
  }

void _FrmObj::TransformPoint (fpt FAR *p)
  {
  if (FrmType != FORMTYPE_FORM) {
    p->x *= float(100.0) ;
    p->y *= float(100.0) ;
    }
  }

void _FrmObj::ToAbsDevKoords (int FAR *x,int FAR *y)
  {
  POINT pt;
  pt.x = *x ; pt.y = *y ;
  if (FrmType != FORMTYPE_FORM)
    pt.x /= 4 , pt.y /= 4 ;
  toDev (&pt);
  *x = pt.x , *y = pt.y ;
  }

void SetRectMinDimension (LPRECT r)
  {
  if ((r->right - r->left) < 3) r->left -= 2 ; r->right += 2 ;
  if ((r->bottom - r->top) < 3) r->top -= 2 ; r->bottom += 2 ;
  }

LPFRMOBJ GetObjectFromPar (LPVOID param);
inline void swap (int FAR &a,int FAR &b)
  {
  int s = a ;
  a = b ;
  b = s ;
  }

inline void swap (long FAR &a,long FAR &b)
  {
  int s = a ;
  a = b ;
  b = s ;
  }

void GetDevRect (LPDIALOGELEM h,LPRECT r)
  {
  if (!h->IsDeleted) {
    LPFRMOBJ o = GetObjectFromPar (h->parblock);
    if ((o != NULL) && (o->Initialized)) {
      LPRECT rcLogRect = o->GetLogRect (0);
      if (rcLogRect != NULL)
        CopyRect (r,rcLogRect);
      else
        SetRectEmpty (r);

      toDev (LPPOINT(&r->left));
      toDev (LPPOINT(&r->right));
      if (r->top > r->bottom) swap (r->top,r->bottom);
      SetRectMinDimension (r);
      }
    else
      SetRectEmpty(r);
    }
  else
    SetRectEmpty(r);
  }

#define NOHIT 32000
int TestPointInRect (LPRECT r,LPPOINT p)
  {
  if (PtInRect (r,*p)) {
    LONG a = LONG(r->right - r->left) * LONG(r->bottom - r->top);
    return - (NOHIT - int (a / 10)) ;   // Das kleinste Rechteck soll
                                        // die negativste Zahl bringen
    }
  return NOHIT ;
  }

LPDIALOGELEM HitTest (LPPOINT pt)
  {
  LPDIALOGELEM res = NULL;
  int oabst = NOHIT ;
  LPSHOWOBJECT so;
  
  for ( LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next ) {
    if (!h->IsDeleted) {

      so = FindShowForElem (h);         // gib mir das "uFrmShowObject"
      int Side = GetSideFromShow (so);  // und die Seite!
      if (Side > ActSide)               // schon fertig?
        break;                          // dann raus
      else if (Side == ActSide) {       // nein
        RECT r;
        GetDevRect (h,&r);
        int abst = TestPointInRect (&r,pt);
        if (abst < oabst) {
          oabst = abst ;
          res = h;
          }
        }  
      }
    }
  return res;
  }

#define EDTIMERID   1000
#define EDTIMEOUT   200
void SetTimerForEdit (HWND hWnd)
  {
  SetTimer (hWnd,EDTIMERID,EDTIMEOUT,NULL);
  }

void KillEditTimer (HWND hWnd)
  {
  KillTimer (hWnd,EDTIMERID);
  }

LPDIALOGELEM LastDialogElem;
BOOL EnlargeScale()
  {
  if (_scale < 3.5) {
    _scale *= float(8.0 / 7.0) ;
    hpos = (hpos - MAXSCPOS / 2) * 8 / 7 + MAXSCPOS / 2 ;
    hpos = min(MAXSCPOS,max(0,hpos));
    vpos = (vpos - MAXSCPOS / 2) * 8 / 7 + MAXSCPOS / 2 ;
    vpos = min(MAXSCPOS,max(0,vpos));
    return TRUE ;
    }
  return FALSE ;
  }

BOOL DecreaseScale()
  {
  if (_scale > 0.3) {
    _scale *= float(7.0 / 8.0) ;
    hpos = (hpos - MAXSCPOS / 2) * 7 / 8 + MAXSCPOS / 2 ;
    hpos = min(MAXSCPOS,max(0,hpos));
    vpos = (vpos - MAXSCPOS / 2) * 7 / 8 + MAXSCPOS / 2 ;
    vpos = min(MAXSCPOS,max(0,vpos));
    return TRUE ;
    }
  return FALSE ;
  }

void NewScale ()
  {
  for ( LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next ) {
    if (!h->IsDeleted) {
      LPFRMOBJ o = GetObjectFromPar (h->parblock);
      if ((o != NULL) && (o->Initialized)) {
        o->OnMapChange (_scale,(FrmType == FORMTYPE_FORM) ?
                          MAPTYPE_TYPOGRAPHIC : MAPTYPE_GEOMETRIC,
                          -(hpos * STEPWIDTH - x0pos()),-(vpos * STEPWIDTH - y0pos()),0,0
                      );
        o->Reformat (FALSE);
        }
      }
    }
  }


HWND hWndHorzRuler = 0;
HWND hWndVertRuler = 0;
HWND hWndPaint = 0;

static BOOL bFrmElemHasChanged = FALSE;
static HFONT hRulerFont = 0;

#define   HORZ_RULER  0
#define   VERT_RULER  1

#define   RULER_DIM   25

void CreateRulerFont (HWND hWnd)
  {
  if (hRulerFont)
    DeleteObject (hRulerFont);
    
//  PaintContext pc (hFrmWnd,0xFFFF,0xFFFF,DO_WORK);
//  ModifyContext (&pc);
  POINT pt = { 12, 0 };

//  DPtoLP (pc.hDC, &pt, 1);

  toLog (&pt);

  pt.x = int(180 / _scale);
  hRulerFont = CreateFont (pt.x, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 
                           FF_SWISS, "Arial");
  }

//---------------------------  FrmEdProc  -----------------------------------
//
// Fenster-Prozedur fuer das MDI-Fenster mit den Linealen und dem
// Zeichnungsbereich fuer die Formulare.
//
// Hauptfenster - ist ein MDI - Fenster !!
//---------------------------------------------------------------------------
DLLExport LONG _export FAR PASCAL FrmEdProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG ret = 0L;

  // Das Fenster, welches den Formulareditor zeigen wollte!
#ifdef WIN32
  HWND hFrmScriptWindow = (HWND)GetWindowLong (hWnd, 0);
#else
  HWND hFrmScriptWindow = GetWindowWord (hWnd, 0);
#endif
  
  switch (msg) {
    case WM_CREATE :
//      SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, MAKELONG(hWndToolbarForm, 0));
//      SendMessage (hWndToolbarForm, TB_CHECKBUTTON, MI_PREVIEWFORM, MAKELONG(bPreviewForm, 0));
      break;
      
    case WM_MOVE :
      ret = DefMDIChildProc (hWnd, msg, wP, lP);
      WriteFrmPos (hWnd);
      break ;

    case WM_SIZE :
      if (IsWindow(hWndHorzRuler))
        MoveWindow (hWndHorzRuler, RULER_DIM, -1, 
                                   LOWORD(lP) - RULER_DIM + 1, RULER_DIM + 1, 
                                   TRUE);
      if (IsWindow(hWndVertRuler))
        MoveWindow (hWndVertRuler, -1, RULER_DIM, 
                                   RULER_DIM + 1, HIWORD(lP) - RULER_DIM + 1, 
                                   TRUE);
      if (IsWindow(hWndPaint))
        MoveWindow (hWndPaint, RULER_DIM, RULER_DIM, 
                               LOWORD(lP) - RULER_DIM, HIWORD(lP) - RULER_DIM, 
                               TRUE);

      ret = DefMDIChildProc (hWnd, msg, wP, lP);
//      ret = DefWindowProc (hWnd,msg,wP,lP);
      WriteFrmPos (hWnd);
      break ;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {

        case MI_PREVIEWFORM:
          bPreviewForm = LOWORD(SendMessage (hWndToolbarForm, TB_ISBUTTONCHECKED, MI_PREVIEWFORM, 0));
          InvalidateRect (hWndPaint, NULL, TRUE);

          break;
        
        case MI_SETRASTER :
          GetRasterDialog (hWnd);   // Aufruf der Dialogbox
          break;
          
        case MI_DESTROYDIALOG :
          SendMessage(hWnd, WM_CLOSE, 0, 0L);
          break;
          
        case MI_STOREDIALOG :
          SendMessage (hFrmScriptWindow, msg, wP, lP);
          SendMessage (hwndMDIClient, WM_MDIDESTROY, (WPARAM)hWnd, 0L);
          break;

        case MI_DUPLICATE :
        case MI_WORKONELE :
        case MI_MOVEELEMES :
        case MI_DELELE :

        case MI_NEWHLINE :
        case MI_NEWVLINE :
        case MI_DELHLINE :
        case MI_MULTIHLINE  :
        case MI_WORKONHLINE :

        case MI_SHOWSORT :
        case MI_INDENVORDERGRUND :
        case MI_INDENHINTERGRUND :
        case MI_SHOWRASTER:
          SendMessage (hFrmScriptWindow, msg, wP, lP);
          break;

        default :
          SendMessage (hWndPaint, msg, wP, lP);
        }  
      break;
    
    // Tastaturnachrichten weiter an das Formularfenster schicken
    case WM_KEYDOWN :
    case WM_KEYUP :
    case WM_CHAR :
      SendMessage (hWndPaint, msg, wP, lP);
      break;
      
    // hat sich was geaendert, dann schicke dem Scriptfenster ein paar Nachrichten
    case WM_CLOSE :
      // Nix tun bitte
      {
      BOOL bClose;
      if (IsWindow(hFrmScriptWindow)) {
        if (bFrmElemHasChanged) {
          char szBuf[256];
          char szTitle[128];
          // hFrmScriptWindow ist nur das Child im MDI-Fenster => GetParent()
          GetWindowText (GetParent(hFrmScriptWindow), szTitle, sizeof(szTitle));
          wsprintf (szBuf, "Das Formular wurde geändert. Sollen die Änderungen in %s übernommen werden?", szTitle);
          
          bClose = MessageBox (hWnd, szBuf, "FORMULAREDITOR", MB_YESNOCANCEL);
          if (bClose == IDYES) {
            bFrmElemHasChanged = FALSE;
            SendMessage (hFrmScriptWindow, WM_COMMAND, MI_STOREDIALOG, 0L);
            }
          else if (bClose == IDNO)
            SendMessage (hFrmScriptWindow, WM_COMMAND, MI_DESTROYDIALOG, 0L);
          }
        else  
          // es hat sich nichts geaendert => einfach schliessen
          SendMessage (hFrmScriptWindow, WM_COMMAND, MI_DESTROYDIALOG, 0L);

        if (bClose != IDCANCEL)
          SendMessage (hwndMDIClient, WM_MDIDESTROY, (WPARAM)hWnd, 0L);
        }
      }
      break ;

    case WM_DESTROY :
//      SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWndToolbarForm, 0));
      if (hRulerFont)
        DeleteObject (hRulerFont);
      hRulerFont = 0;
      hWndPaint = 0;
      hWndHorzRuler = 0;
      hWndVertRuler = 0;
      break;

    default :
      return DefMDIChildProc(hWnd, msg, wP, lP);
    }
    
  return ret;
  }

//-----------------------  PaintHorzRuler  ----------------------------------
void PaintHorzRuler (HWND hWnd, PaintContext *pc)
  {
  float  nX_Zaehler, nNextCM;
  char  lpString[6];

  RECT rc;
  GetClientRect (hWnd, &rc);
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);

  int OldBk = SetBkMode (pc->hDC, TRANSPARENT);
  float Step = 1440 / float(2.54);        // 1 cm

  HFONT hOldFont = (HFONT)SelectObject (pc->hDC, hRulerFont);
  
  nNextCM = (hpos / Step + 1) * Step - hpos;  // Scrollposition beruecksichtigen
  for (nX_Zaehler = nNextCM; nX_Zaehler < rc.right + nNextCM; nX_Zaehler += Step) {
    MoveToEx (pc->hDC, int(nX_Zaehler), rc.top, NULL);
    LineTo (pc->hDC, int(nX_Zaehler), rc.top + int(170/_scale));

    wsprintf (lpString, "%d", int((nX_Zaehler + hpos)/Step));
    ExtTextOut(pc->hDC, int(nX_Zaehler+50), rc.top + int(150/_scale), 
               0, NULL, lpString, lstrlen(lpString), NULL);
    }
  SetBkMode (pc->hDC, OldBk);

  SelectObject (pc->hDC, hOldFont);
  
  if (_scale < 2.0)
    Step = float(1440 * 0.2) / float(2.54);
  else  
    Step = float(1440 * 0.1) / float(2.54);

  for (float i = float(0); i < rc.right; i += Step) {
    MoveToEx (pc->hDC, int(i), rc.top, NULL);
    LineTo (pc->hDC, int(i), rc.top + int(90/_scale));
    }

  GetClientRect (hWnd, &rc);
  rc.bottom = rc.top + 1;
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);

  COLORREF OldColor = SetBkColor (pc->hDC, RGB(0xFF, 0xFF, 0xFF));
  ExtTextOut (pc->hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

  GetClientRect (hWnd, &rc);
  rc.top = rc.bottom - 1;
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);
  SetBkColor (pc->hDC, RGB(0x80, 0x80, 0x80));
  ExtTextOut (pc->hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

  SetBkColor (pc->hDC, OldColor);
  }

//-----------------------  PaintVertRuler  ----------------------------------
void PaintVertRuler (HWND hWnd, PaintContext *pc)
  {
  float  nX_Zaehler, nNextCM;
  char  lpString[6];

  RECT rc;
  GetClientRect (hWnd, &rc);
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);

  int OldBk = SetBkMode (pc->hDC, TRANSPARENT);
  float Step = 1440 / float(2.54);        // 1 cm
  
  HFONT hOldFont = (HFONT)SelectObject (pc->hDC, hRulerFont);

  nNextCM = (vpos / Step + 1) * Step - vpos;  // Scrollposition beruecksichtigen
  for (nX_Zaehler = nNextCM; nX_Zaehler < rc.bottom + nNextCM; nX_Zaehler += Step) {
    MoveToEx (pc->hDC, rc.left, int(nX_Zaehler), NULL);
    LineTo (pc->hDC, rc.left + int(170/_scale) ,int(nX_Zaehler));

    wsprintf (lpString, "%d", int((nX_Zaehler + hpos)/Step));
    ExtTextOut(pc->hDC, rc.left + int(150/_scale), int(nX_Zaehler+50), 
               0, NULL, lpString, lstrlen(lpString), NULL);
    }
  SetBkMode (pc->hDC, OldBk);

  SelectObject (pc->hDC, hOldFont);
  
  if (_scale < 2.0)
    Step = float(1440 * 0.2) / float(2.54);
  else  
    Step = float(1440 * 0.1) / float(2.54);

  for (float i = float(0); i < rc.bottom; i += Step) {
    MoveToEx (pc->hDC, rc.left, int(i), NULL);
    LineTo (pc->hDC, rc.left + int(90/_scale), int(i));
    }

  GetClientRect (hWnd, &rc);
  rc.right = rc.left + 1;
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);

  COLORREF OldColor = SetBkColor (pc->hDC, RGB(0xFF, 0xFF, 0xFF));
  ExtTextOut (pc->hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

  GetClientRect (hWnd, &rc);
  rc.left = rc.right - 1;
  DPtoLP (pc->hDC, LPPOINT(&rc), 2);
  SetBkColor (pc->hDC, RGB(0x80, 0x80, 0x80));
  ExtTextOut (pc->hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

  SetBkColor (pc->hDC, OldColor);
  }


DLLExport LONG _export FAR PASCAL FrmRulerProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG ret = 0L;

  WORD RulerType = GetWindowWord (hWnd, 0);

  switch (msg) {
    case WM_PAINT :
      {
      PaintContext pc (hWnd);
      // ab jetzt in "logischen TWIPS"
      ModifyContext (&pc);
      RulerType == HORZ_RULER ? PaintHorzRuler (hWnd, &pc) : PaintVertRuler (hWnd, &pc);
      pc.ResetMap ();
      }
      break;
    
    default :
      ret = DefWindowProc (hWnd, msg, wP, lP);
    }

  return ret;
  }

//----------------------------  PaintPage  ----------------------------------
void PaintPage (HWND hWnd, PaintContext *pc, int Side)
  {
//  float Step = 1440 / 2.54;        // 1 cm

  float nxStartPage = float(0);  // Scrollposition beruecksichtigen
  float nxEndPage = (21.0F * 1440.0F) / 2.54F;
  float nyStartPage = float(0);
  float nyEndPage = float(29.7 * 1440.0) / float(2.54);

  RECT rc;
  SetRect (&rc, int(nxStartPage), int(nyStartPage),
                int(nxEndPage), int(nyEndPage));

  ModifyContext (pc);
  pc->LogRecttoPhys (&rc, &rc);
  pc->ResetMap ();
  OffsetRect (&rc, Side*(rc.right-rc.left+20), 0);

  HBRUSH OldBrush = (HBRUSH)SelectObject (pc->hDC, GetStockObject(WHITE_BRUSH));
  Rectangle (pc->hDC, rc.left, rc.top, rc.right, rc.bottom);
  SelectObject (pc->hDC, OldBrush);

  if (bShowRaster) {
    float RasterX = float ((double(rc.right - rc.left) / 21.0) * (double(XRasterIn_mm) / 10.0));
    float RasterY = float ((double(rc.bottom - rc.top) / 29.7) * (double(YRasterIn_mm) / 10.0));
    if ((RasterX != 0) && (RasterY != 0)) {
    for (float py = float(0.0); py < (rc.bottom - rc.top); py += RasterY)
      for (float px = float(0.0); px < (rc.right - rc.left); px += RasterX)
        SetPixel (pc->hDC, rc.left + int(px), rc.top + int(py), 0);
      }
    }
  }

//#define POSTIT
#ifdef POSTIT      
extern void UpdatePostItWindow ();
#endif
//---------------------------  FrmPaintProc  --------------------------------
//
// Eines der Unterfenster des MDI-Fensters.                      
// Zeichnungsbereich fuer die Formulare.
//
// Elternfenster - ist ein MDI - Fenster !!
//---------------------------------------------------------------------------
DLLExport LONG _export FAR PASCAL FrmPaintProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  BOOL done;
  LONG RetVal = TrackMsgProc (hWnd,msg,wP,lP,&done);
  if (done) return RetVal ;
  RetVal = SR_CheckMSG (hWnd,msg,wP,lP,&done);
  if (done) return RetVal ;
  RetVal = CheckHLineMSG (hWnd,msg,wP,lP,&done);
  if (done) return RetVal ;
  edcmem e;
  static int repeat = 0;

  switch (msg) {
    case WM_CREATE :
      {
      AnzSides = GetAnzSides ();

      TBBUTTON tb[7] = {
                  { 0,  MI_PREVIEWFORM    ,   TBSTATE_ENABLED, TBSTYLE_CHECK, 0L, 0 }, 
                  {-1,  0                 ,   TBSTATE_ENABLED, TBSTYLE_SEP  , 0L, 0 }, 
                  };

      for (int i = 1; (i <= AnzSides) && (i < 8); i++) {
        tb[i+1].iBitmap = i;                   // index into bitmap of this button's picture
        tb[i+1].idCommand = MI_PREVIEWFORM+i;  // WM_COMMAND menu ID that this button sends
        tb[i+1].fsState = TBSTATE_ENABLED;     // button's state
        tb[i+1].fsStyle = TBSTYLE_CHECKGROUP;  // button's style
        tb[i+1].dwData = 0L;
        tb[i+1].iString = 0;
//        SendMessage (hWndToolbarForm, TB_INSERTBUTTON, 0xFFFF, LONG(LPTBBUTTON(&tb)));
        }

      hWndToolbarForm = CreateToolbar ("Formular", hWndDock,       // Parent
                                         0, 
                                         CMD_TB_BASE, 
                                         6,             // Anzahl der Bildchen im Bitmap
                                         MyInstance, 
                                         IDR_PREVIEW, 
                                         tb, 
                                         i+1            // Anzahl der Knöpfe inkl. Separator
                                         );

#ifdef WIN32
      SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, LPARAM(hWndToolbarForm));
#else
      SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, MAKELONG(hWndToolbarForm, 0));
#endif
      SendMessage (hWndToolbarForm, TB_CHECKBUTTON, MI_PREVIEWFORM, MAKELONG(bPreviewForm, 0));
//      SendMessage (hWndToolbarForm, TB_CHECKBUTTON, MI_SHOWRASTER, MAKELONG(bShowRaster, 0));

      ShowScrollBar (hWnd,SB_HORZ,TRUE);
      SetScrollRange (hWnd,SB_HORZ, 0, MAXSCPOS, FALSE);
      SetScrollPos (hWnd,SB_HORZ, hpos = MAXSCPOS / 2, FALSE);
      ShowScrollBar (hWnd,SB_VERT,TRUE);
      SetScrollRange (hWnd,SB_VERT, 0, MAXSCPOS, FALSE);
      SetScrollPos (hWnd,SB_VERT, vpos = MAXSCPOS / 2, FALSE);
      hFrmWnd = hWnd;
      new Tool_Drop (hWnd);
      }
      break ;

    case WM_SIZE :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;

    case WM_PAINT :
      {
      int i;
      PaintContext pc (hWnd);
      e.hDC = pc.hDC;

#ifdef POSTIT      
      UpdatePostItWindow ();
#endif

      if (bPreviewForm) {
        for (i = 0; i < AnzSides+1; i++)
          PaintPage (hWnd, &pc, i);
        }
      else {
        PaintPage (hWnd, &pc, ActSide);
        
        }
            
      ModifyContext (&pc);

      if (bPreviewForm) {
        for (i = 0; i < AnzSides+1; i++)
          PaintObjs (&pc, i);
        }
      else
        PaintObjs (&pc, ActSide);
          
      pc.ResetMap ();
      DoEditCallBack (NULL,hWnd,EDC_HLINEPAINT,&e);
      DoEditCallBack (NULL,hWnd,EDC_PAINT,&e);
      }
      break ;

    case WM_LBUTTONDOWN :
      {
      POINT pt;
      pt.x = LOWORD(lP);
      pt.y = HIWORD(lP);
      e.pt = pt;
      
      if (!bPreviewForm) {
        LastDialogElem = HitTest (&pt);
//        pc.ResetMap ();
        
        DoEditCallBack (LastDialogElem,hWnd,EDC_LBUTTONDOWN,&e);
        if (LastDialogElem != NULL)
          SetTimerForEdit (hWnd);
        }  
      }
      break ;

    case WM_LBUTTONUP:
      if (bPreviewForm)
        break;

      e.pt.x = LOWORD(lP);
      e.pt.y = HIWORD(lP);
      if (DoEditCallBack (LastDialogElem,hWnd,EDC_LBUTTONUP,&e))
        //********************************************************
        //   ab jetzt muss man Aenderungen speichern!!!!
        //********************************************************
        bFrmElemHasChanged = TRUE;

      LastDialogElem = NULL;
      break ;

    case WM_LBUTTONDBLCLK:
      if (bPreviewForm)
        break;

      e.pt.x = LOWORD(lP);
      e.pt.y = HIWORD(lP);
      DoEditCallBack (LastDialogElem,hWnd,EDC_LBUTTONDBLCLK,&e);
      LastDialogElem = NULL;
      break ;

    case WM_MOUSEMOVE:
      if (bPreviewForm)
        break;
    
      e.pt.x = LOWORD(lP);
      e.pt.y = HIWORD(lP);

      DoEditCallBack (LastDialogElem,hWnd,EDC_MOUSEMOVE,&e);
      break;

    // mit den Cursortasten kann der Mauszeiger bewegt werden.
    // Belibt man laenger auf den Tasten, wird der Mauszeiger
    // immer schneller zu einer weiter entfernten Position bewegt.
    case WM_KEYDOWN :
      {
      POINT pt;
      BOOL bMoved = FALSE;
      
      GetCursorPos (&pt);
      
      switch (wP) {
        case VK_LEFT :
          pt.x -= repeat;
          bMoved = TRUE;
          break;
          
        case VK_RIGHT :
          pt.x += repeat;
          bMoved = TRUE;
          break;
          
        case VK_UP:
          pt.y -= repeat;
          bMoved = TRUE;
          break;
          
        case VK_DOWN:
          pt.y += repeat;
          bMoved = TRUE;
          break;
        }
      
      if (bMoved) {
        repeat++;   
        SetCursorPos (pt.x, pt.y);
        SendMessage (hWnd, WM_MOUSEMOVE, 0, MAKELONG(pt.x, pt.y));
        }
      }
      break;
    
    // nach jedem KEYUP wird der Mauszeiger bei neuerlichem KEYDOWN
    // nur um eine Einheit weiter bewegt.
    case WM_KEYUP :
      repeat = 1;    
      break;

    case WM_CHAR :
      e.ch = char(wP);
      DoEditCallBack (NULL,hWnd,EDC_CHAR,&e);
      break;

    case WM_HSCROLL :
      {
      int hold = hpos;
      int xvold = xv();
      switch (wP) {
        case SB_LINEDOWN :
          hpos = min(MAXSCPOS,hpos+1);
          break ;
        case SB_LINEUP :
          hpos = max(0,hpos-1);
          break ;
        case SB_PAGEDOWN :
          hpos = min(MAXSCPOS,hpos+5);
          break ;
        case SB_PAGEUP :
          hpos = max(0,hpos-5);
          break ;
        }
      if (hold != hpos) {
        StartScrolling (hWnd);
        UpdateWindow (hWnd);
        ScrollWindow (hWnd,xv() - xvold,0,NULL,NULL);
        SetScrollPos (hWnd,SB_HORZ,hpos,TRUE);
        ScrollPTStart (xv() - xvold,0);
        UpdateWindow (hWnd);
        EndScrolling (hWnd,xv() - xvold,0);

        InvalidateRect (hWndHorzRuler, NULL, TRUE);
        }
      }
      break ;

    case WM_VSCROLL :
      {
      int vold = vpos;
      int yvold = yv();
      switch (wP) {
        case SB_LINEDOWN :
          vpos = min(MAXSCPOS,vpos+1);
          break ;
        case SB_LINEUP :
          vpos = max(0,vpos-1);
          break ;
        case SB_PAGEDOWN :
          vpos = min(MAXSCPOS,vpos+5);
          break ;
        case SB_PAGEUP :
          vpos = max(0,vpos-5);
          break ;
        }
      if (vold != vpos) {
        StartScrolling (hWnd);
        UpdateWindow (hWnd);
        ScrollWindow (hWnd,0,yv() - yvold,NULL,NULL);
        SetScrollPos (hWnd,SB_VERT,vpos,TRUE);
        ScrollPTStart (0,yv() - yvold);
        UpdateWindow (hWnd);
        EndScrolling (hWnd,0,yv() - yvold);

        InvalidateRect (hWndVertRuler, NULL, TRUE);
        }
      }
      break ;

    case WM_TIMER :
      if (wP == EDTIMERID) {
        LONG l = GetMessagePos();
        e.pt.x = LOWORD(l);
        e.pt.y = HIWORD(l);
        ScreenToClient (hWnd,&e.pt);
        if (DoEditCallBack (NULL,hWnd,EDC_SETCURSOR,&e)) return TRUE ;
        KillEditTimer (hWnd);
        }
      break ;

    case WM_SETCURSOR :
      {
      LONG l = GetMessagePos();
      e.pt.x = LOWORD(l);
      e.pt.y = HIWORD(l);
      ScreenToClient (hWnd,&e.pt);
      if (DoEditCallBack (NULL,hWnd,EDC_SETCURSOR,&e)) return TRUE ;
      RetVal = DefWindowProc (hWnd, msg, wP, lP);
      }
      break ;

    case WM_DESTROY :
      if (hWndToolbarForm) {
        DestroyWindow (hWndToolbarForm);
        hWndToolbarForm = 0;
        }

      RemoveAll (hWnd);
      hFrmWnd = 0;
      break ;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case MI_BIGGERSCALE :
          if (EnlargeScale()) {
            SetScrollPos (hWnd,SB_HORZ,hpos,TRUE);
            SetScrollPos (hWnd,SB_VERT,vpos,TRUE);
            NewScale ();
            CreateRulerFont (hWnd);
            InvalidateRect (hWnd,NULL,TRUE);
            InvalidateRect (hWndHorzRuler, NULL, TRUE);
            InvalidateRect (hWndVertRuler, NULL, TRUE);
            }
          break ;
        case MI_SMALLERSCALE :
          if (DecreaseScale()) {
            SetScrollPos (hWnd,SB_HORZ,hpos,TRUE);
            SetScrollPos (hWnd,SB_VERT,vpos,TRUE);
            NewScale ();
            CreateRulerFont (hWnd);
            InvalidateRect (hWnd,NULL,TRUE);
            InvalidateRect (hWndHorzRuler, NULL, TRUE);
            InvalidateRect (hWndVertRuler, NULL, TRUE);
            }
          break ;
        }
      break ;
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;
    }
  return RetVal ;
  }

static char FrmEdClass[] = "FRMED";
static char FrmPaintClass[] = "FRMPAINT";
static char FrmRulerClass[] = "FRMRULER";
static void Register ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wndclass.lpfnWndProc   = FrmEdProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(HWND) ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = FrmEdClass ;

    if (RegisterClass (&wndclass)) {
      wndclass.lpfnWndProc   = FrmPaintProc;
      wndclass.lpszClassName = FrmPaintClass;
      wndclass.cbWndExtra    = 0 ;
      wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;

      if (RegisterClass (&wndclass)) {
        wndclass.lpfnWndProc   = FrmRulerProc;
        wndclass.lpszClassName = FrmRulerClass;
        wndclass.cbWndExtra    = 2 ;
        wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;

        if (RegisterClass (&wndclass))
          Registered = TRUE ;
        }
      }  
    }
  }


#ifdef POSTIT
extern HWND CreatePostItWindow (HWND hWParent, int x, int y, int w, int h, LPSTR Text);
#endif

HWND CreatePaintObjectWindow (HWND hWParent, int x, int y, int w, int h)
  {
  HWND hWnd = CreateWindow (FrmPaintClass, NULL,
                            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                            x, y, w, h,
                            hWParent, 0, MyInstance, NULL
                            );
#ifdef POSTIT
  HWND hWndChild = CreatePostItWindow (hWnd, 1000, 1000, 5000, 5000, NULL);
#endif

  return hWnd;
  }

HWND CreateRulerWindow (HWND hWndParent, int x, int y, int w, int h, WORD RulerType)
  {
  HWND hWnd = CreateWindow (FrmRulerClass, NULL,
                            WS_CHILD | WS_VISIBLE | WS_BORDER,
                            x, y, w, h,
                            hWndParent, 0, MyInstance, NULL
                            );
  SetWindowWord (hWnd, 0, RulerType);
  return hWnd;
  }


//---------------------  MakeNewFormChild  ----------------------------------
//
// erzeugt das MDI-Fenster fuer Formulare
//---------------------------------------------------------------------------
HWND FAR PASCAL MakeNewFormChild (HWND hWndScript, LPSTR pName)
  {
  HWND hwnd;
//  char sz[160];
  MDICREATESTRUCT mcs;

  if (pName != NULL)
    mcs.szTitle = (LPSTR)pName; /* Fully qualified pathname*/
    
  mcs.szClass = FrmEdClass;
  mcs.hOwner = MyInstance;
  mcs.x = mcs.cx = CW_USEDEFAULT;  // Use the default size for the window
  mcs.y = mcs.cy = CW_USEDEFAULT;
  mcs.style = styleDefault | WS_CLIPCHILDREN | WS_MAXIMIZE;   // Set the style DWORD of the window
   // to default

   
  // tell the MDI Client to create the child 
#ifdef WIN32
  hwnd = (HWND)SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
  SetWindowLong (hwnd, 0, (LONG)hWndScript);
#else
  hwnd = (WORD)SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
  SetWindowWord (hwnd, 0, hWndScript);
#endif


  ShowWindow(hwnd, SW_SHOW);
  return hwnd;
  }


HWND CreateFrmObjWindow (HWND hWParent)
  {
/*
  int x,y,w,h;
  ReadFrmPos (&x,&y,&w,&h);
*/
  Register ();
  _scale = float(1.0);
  _AnzSides = 1;
  _ActSide = 0;
  _hInactivePen = CreatePen (PS_SOLID,0,RGB(0x80,0x80,0x80));
  _hActivePen = CreatePen (PS_SOLID,0,RGB(0xFF,0,0));
//  HMENU hMenu = LoadMenu(MyInstance,"FRMENU");
/*
  HWND hWndForm = CreateWindow (FrmEdClass,"Formulareditor",
                       WS_POPUP | WS_VISIBLE | WS_THICKFRAME | WS_CAPTION,
                       x, y, w, h,
                       hWParent,hMenu,MyInstance,NULL
                      );
*/
  HWND hWndForm = MakeNewFormChild (hWParent, "Formulareditor");

  RECT rc;            
  GetClientRect (hWndForm, &rc);
  hWndHorzRuler = CreateRulerWindow (hWndForm, RULER_DIM, -1, 
                                               rc.right - RULER_DIM+1, RULER_DIM + 1, 
                                               HORZ_RULER);
  hWndVertRuler = CreateRulerWindow (hWndForm, -1, RULER_DIM, 
                                               RULER_DIM + 1, rc.bottom - RULER_DIM+1, 
                                               VERT_RULER);

  hFrmWnd = hWndPaint = CreatePaintObjectWindow (hWndForm, RULER_DIM, RULER_DIM, 
                                                 rc.right - RULER_DIM, 
                                                 rc.bottom - RULER_DIM);
  CreateRulerFont (hFrmWnd);
  
//  SetWindowPos (hWndForm, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  return hWndForm;
  }




struct ObjHd {
  WORD FncId;
  WORD parSize;
  LPFRMOBJ r;
  };
typedef ObjHd FAR *LPOBJHD;

void DelObjectFromPar (LPVOID param)
  {
  LPOBJHD h = LPOBJHD (param);
  h->r = NULL;
  }

LPFRMOBJ GetObjectFromPar (LPVOID param)
  {
  LPOBJHD h = LPOBJHD (param);
  return h->r;
  }

void WriteObjectToPar (LPVOID param,LPFRMOBJ o)
  {
  LPOBJHD h = LPOBJHD (param);
  h->r = o;
  }


void PaintObjs (PaintContext *pc, int ActSide)
  {
  LPSHOWOBJECT so;
  
  float nxEndPage = (21.0F * 1440.0F) / 2.54F;  // Breite einer Seite in log. Koord.
  int PageWidth = pc->XLOGtoPHYS (int(nxEndPage));  //  -- " --       in phys. Koord.

  int Offset = ActSide * (PageWidth + 20);      // Offset fuer ViewPortOrg
  ModifyContext (pc, Offset);

  // Alle Formular-Elemente durchmarschieren
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (!h->IsDeleted) {
      so = FindShowForElem (h);         // gib mir das "uFrmShowObject"
      int Side = GetSideFromShow (so);  // und die Seite!
      if (Side > ActSide)               // schon fertig?
        break;                          // dann raus
      else if (Side == ActSide) {       // nein, ich muß noch zeichnen
        LPFRMOBJ o = GetObjectFromPar (h->parblock);
        if ((o != NULL) && (o->Initialized))
          o->Paint (pc, 0);
        }  
      }
    }
  
  ModifyContext (pc);    // ViewPort wieder ruecksetzen

/*  
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (!h->IsDeleted) {
      LPFRMOBJ o = GetObjectFromPar (h->parblock);
      if ((o != NULL) && (o->Initialized))
        o->Paint (pc);
      }
    }
*/
  }

void _FrmObj::DoEdit (LPDIALOGELEM h,WORD mode)
  {
  static BOOL DLLInitDone;
  if ((mode & EM_LOAD) && (hFrmWnd == 0)) {
    HWND Wnd = CreateFrmObjWindow (hRefWnd);
    }
  if ((mode & EM_LOAD) && (!DLLInitDone)) {
    DLLInitDone = TRUE ;
    InitFrmObjDll();
    }
  if (mode & EM_LOAD) {
    LPFRMOBJ obj = LPFRMOBJ (GetObject (h));
    WIN_ASSERT (obj != NULL);
    WriteObjectToPar (h->parblock,obj);
    obj->Load ();
    obj->GetMinMax ();
    obj->Write (obj,UPDATE_SYNCHRON);
    if (mode & EM_CHANGETOTRUE)
      h->Invalidate (hFrmWnd,TRUE);
    }
  if (mode & EM_RESET) {
    if (h->parblock != NULL) {
      LPFRMOBJ obj = GetObjectFromPar (h->parblock);
      if (obj->Initialized)
        obj->Invalidate(0);
      obj->SetInActiveIf(0);
      obj->Reset (TRUE);
      obj->Write (NULL,UPDATE_SYNCHRON);
      DelObjectFromPar (h->parblock);
      delete obj;
      }
    }
  if (mode & EM_PRIVATE1) {
    DoEdit (h,EM_RESET);     // Objekt bekommt einen RESET
    DoEdit (h,EM_LOAD);      // Objekt wird neu geladen
    }
  }

void DestroyFrmWindow ()
  {
/*
  if (hFrmWnd)
    DestroyWindow (hFrmWnd);
  hFrmWnd = 0;
*/
  if (_hActivePen)   DeleteObject (_hActivePen)   , _hActivePen = 0;
  if (_hInactivePen) DeleteObject (_hInactivePen) , _hInactivePen = 0;
  }

int GetFieldYSnapOffs (int Format)
  {
  int MapType = (FrmType == FORMTYPE_FORM) ?
            MAPTYPE_TYPOGRAPHIC : MAPTYPE_GEOMETRIC ;
  LPFORMATMETRIC m = GetFormatMetrics (hFrmWnd,MapType,Format);
  return m->yBaseHeight;
  }
#define FORMATPARNUM  5
int _DefFrmField::SnapYOffs (LPDIALOGELEM e)
  {
  int Format ;
  GetIntParWithNum (e,FORMATPARNUM,&Format);
  int h = GetFieldYSnapOffs (Format);
  if (FrmType == FORMTYPE_TRACING) h /= -4 ;
  return h;
  }
#define WIDTHPARNUM   5
int _DefCheckBox::SnapYOffs (LPDIALOGELEM e)
  {
  int w ;
  GetIntParWithNum (e,WIDTHPARNUM,&w);
  if (FrmType == FORMTYPE_TRACING) w /= -4 ;
  return w;
  }
LPVOID _DefFrmField::GetObject (LPDIALOGELEM h) { return new FrmField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmDate::GetObject (LPDIALOGELEM h) { return new FrmDate (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmTime::GetObject (LPDIALOGELEM h) { return new FrmTime (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmDec::GetObject (LPDIALOGELEM h) { return new FrmDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmShort::GetObject (LPDIALOGELEM h) { return new FrmShort (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmLong::GetObject (LPDIALOGELEM h) { return new FrmLong (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmMoney::GetObject (LPDIALOGELEM h) { return new FrmMoney (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmSLDec::GetObject (LPDIALOGELEM h) { return new FrmSLDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmStrList::GetObject (LPDIALOGELEM h) { return new FrmStrList (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmLine::GetObject (LPDIALOGELEM h) { return new FrmLine (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmImage::GetObject (LPDIALOGELEM h) { return new FrmImage (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _Trc_DefCont::GetObject (LPDIALOGELEM h) { return new TrcContObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _Trc_DefPattern::GetObject (LPDIALOGELEM h) { return new TrcPatternObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h),FALSE); }
LPVOID _Trc_DefmPattern::GetObject (LPDIALOGELEM h) { return new TrcPatternObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h),TRUE); }
LPVOID _Trc_DefLine::GetObject (LPDIALOGELEM h) { return new TrcLineObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmSozNr::GetObject (LPDIALOGELEM h) { return new FrmSozNr (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmDevDec::GetObject (LPDIALOGELEM h) { return new FrmDevDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefCheckBox::GetObject (LPDIALOGELEM h) { return new FrmCheckBox (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmShortStrList::GetObject (LPDIALOGELEM h) { return new FrmStrShortList (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _Trc_DefArc::GetObject (LPDIALOGELEM h) { return new TrcArcObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefPattern::GetObject (LPDIALOGELEM h) { return new PatternObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmTab::GetObject (LPDIALOGELEM h) { return new FrmTab (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmTabField::GetObject (LPDIALOGELEM h) { return new FrmTabField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTabDecField::GetObject (LPDIALOGELEM h) { return new FrmTabDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmTabShortStrList::GetObject (LPDIALOGELEM h) { return new FrmTabShortStrList (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTabFlagField::GetObject (LPDIALOGELEM h) { return new FrmTabFlag (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefCheckField::GetObject (LPDIALOGELEM h) { return new FrmCheckField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTabCheckField::GetObject (LPDIALOGELEM h) { return new FrmTabCheckField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmStrDivList::GetObject (LPDIALOGELEM h) { return new FrmDivStrList (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTabDate::GetObject (LPDIALOGELEM h) { return new FrmTabDate (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmTabStrList::GetObject (LPDIALOGELEM h) { return new FrmTabStrList (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTabColDec::GetObject (LPDIALOGELEM h) { return new FrmTabColDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmSlantField::GetObject (LPDIALOGELEM h) { return new FrmSlantField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmSlantDec::GetObject (LPDIALOGELEM h) { return new FrmSlantDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmSlantSLDec::GetObject (LPDIALOGELEM h) { return new FrmSlantSLDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefMovePattern::GetObject (LPDIALOGELEM h) { return new MovePatternObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmDefDec::GetObject (LPDIALOGELEM h) { return new FrmDefDec (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmMultiField::GetObject (LPDIALOGELEM h) { return new FrmMultiField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefTrcImage::GetObject (LPDIALOGELEM h) { return new TrcImage (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmStaticBitmap::GetObject (LPDIALOGELEM h) { return new FrmStaticBitmap (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefActivationRegion::GetObject (LPDIALOGELEM h) { return new ActivationRegion (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _DefFrmBField::GetObject (LPDIALOGELEM h) { return new FrmBField (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }
LPVOID _Trc_DefRectangle::GetObject (LPDIALOGELEM h) { return new TrcRectangleObj (LPSTR(h->parblock)+sizeof(WORD),LPMDICHILD(h)); }

////////////////////////////////////////////////////////////////////////
//  Callback - Funktionen
////////////////////////////////////////////////////////////////////////
StrListInfo sli;
static LPVOID ActScanPtr;
int WorldToLog(float val)
  {
  if (FrmType == FORMTYPE_FORM) 
    return int (val);
  else
    return int (val * 25.0);
  }
float LogToWorld(int val)
  {
  if (FrmType == FORMTYPE_FORM) 
    return float (val);
  else
    return float (double(val) / 25.0);
  }
int HalfPenWidth (DWORD color) 
  { 
  if (FrmType == FORMTYPE_FORM) {
    int w = int ((color & 0x0F000000) >> 24) * 10; return (w) ? w : 1 ; 
    }
  else {
    int w = int (((color & 0x0F000000) >> 24) * 9 + 1) / 4; 
    return (w) ? w : 1 ;
    }
  }
Printer *GetTestPrinter ()
  {
  return NULL ; /*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
  }
int GetStdTabX ()
  {
  return 100 ;  /*  !!!!!!!!!!!!!! */
  }
void GetDocInfo(LPDIALOGELEM h,int Cmd, DWORD fldId, LPVOID Buffer)
  {
  switch (Cmd) {
    case GETDRAWINGWINDOW :
      *((HWND FAR *) Buffer) = hFrmWnd;
      break ;
    case GETSCALE :
      *((float FAR *) Buffer) = _scale;
      break ;
    case GETCHARHANDLE :
      WIN_ASSERT(FALSE);
      break ;
    case GETMAPTYPE :
      *((int FAR *) Buffer) = (FrmType == FORMTYPE_FORM) ?
            MAPTYPE_TYPOGRAPHIC : MAPTYPE_GEOMETRIC ;
      break ;
    case GETWINDOWORG :
      ((POINT FAR *) Buffer)->x = 
      ((POINT FAR *) Buffer)->y = 0 ;
      break ;
    case GETVIEWPORTORIGIN :
      ((POINT FAR *) Buffer)->x = -(hpos * STEPWIDTH - x0pos());
      ((POINT FAR *) Buffer)->y = -(vpos * STEPWIDTH - y0pos());
      break ;
    case ISDRAWINGALLOWED :
      *((BOOL FAR *) Buffer) = TRUE ;
      break ;
    case GETPRINTERHANDLE :
      *((LPPRINTER FAR *) Buffer) = GetTestPrinter() ;
      break ;
    case GETFLDMEM :
      WIN_ASSERT(FALSE);
      break ;
    case FORMATFORSCREEN :
      *((BOOL FAR *) Buffer) = TRUE ;
      break ;
    case TRYTOUPDATE :
      *((BOOL FAR *) Buffer) = TRUE ;
      break ;
    case INFORMABOUTUPDATE :
      break ;
    case GETLISTITEMS :
      // Das Feld will die Konfigurationsdatei haben
      sli.res = 0;
      GetObjectFromPar (h->parblock)->GetResource ();
      lmemcpy (Buffer,&sli,sizeof(sli));
      break;
    case GETTABPOS :
      // Tab - Positionen fuer das Feld
      *((WORD FAR *) (LPSTR (Buffer) + sizeof(DWORD))) = GetStdTabX();
      break ;
    case SETLISTITEM :
      // Das Feld hat einen neuen Index
      lmemcpy (&sli,Buffer,sizeof(sli));
      break ;
    case GETSELSTR :
      GetObjectFromPar (h->parblock)->GetSelText ();
      lmemcpy (Buffer,&sli,sizeof(sli));
      break ;
    }
  }
static ScriptContent_Entry hd;
DLLExport LPSCRIPTCONTENT _export FAR PASCAL cb_schd(dllChild FAR *c)
  { hd.Type = (FrmType == FORMTYPE_FORM) ? CHWND_FORM : CHWND_TRACING ; return &hd; }
DLLExport HWND _export FAR PASCAL cb_MyHandle(dllChild FAR *c)
  { return hFrmWnd; }
DLLExport void _export FAR PASCAL cb_Get_scale(dllChild FAR *c, float FAR *sc)
  { *sc = _scale; }
DLLExport int _export FAR PASCAL cb_xp(dllChild FAR *c)
  { return -(hpos * STEPWIDTH - x0pos()); }
DLLExport int _export FAR PASCAL cb_yp(dllChild FAR *c)
  { return -(vpos * STEPWIDTH - y0pos()); }
DLLExport int _export FAR PASCAL cb_x0(dllChild FAR *c)
  { return 0; }
DLLExport int _export FAR PASCAL cb_y0(dllChild FAR *c)
  { return 0; }
DLLExport int _export FAR PASCAL cb_AnzSides(dllChild FAR *c)
  { return _AnzSides; }
DLLExport int _export FAR PASCAL cb_ActSide(dllChild FAR *c)
  { return _ActSide; }
DLLExport DWORD _export FAR PASCAL cb_SelColor(dllChild FAR *c)
  { return DWORD(RGB(255,0,0)); }
DLLExport HPEN _export FAR PASCAL cb_hActivePen(dllChild FAR *c)
  { return _hActivePen; }
DLLExport HPEN _export FAR PASCAL cb_hInactivePen(dllChild FAR *c)
  { return _hInactivePen; }
DLLExport void _export FAR PASCAL cb_GetDocInfo (dllChild FAR *c, int Cmd,DWORD fldId,LPVOID Buffer)
  { GetDocInfo(LPDIALOGELEM(c->PrivData),Cmd, fldId, Buffer); }
DLLExport void _export FAR PASCAL cb_Rescale (dllChild FAR *c, LPRECT rect)
  { }
DLLExport int _export FAR PASCAL cb_WorldToLog (dllChild FAR *c, float val)
  { return WorldToLog(val); }
DLLExport void _export FAR PASCAL cb_Get_LogToWorld (dllChild FAR *c, float FAR *ltw, int val)
  { *ltw = LogToWorld(val); }
DLLExport int _export FAR PASCAL cb_HalfPenWidth (dllChild FAR *c, DWORD color)
  { return HalfPenWidth(color); }
DLLExport Printer FAR * _export FAR PASCAL cb_Pr(dllChild FAR *c)
  { return GetTestPrinter(); }
DLLExport int _export FAR PASCAL cb_tabx(dllChild FAR *c)
  { return GetStdTabX(); }
DLLExport GLOBALHANDLE _export FAR PASCAL cb_Get_sli_res(dllChild FAR *c)
  { return sli.res; }
DLLExport int _export FAR PASCAL cb_Get_sli_Ind(dllChild FAR *c)
  { return sli.Ind; }
DLLExport LPSTR _export FAR PASCAL cb_Get_sli_actTxt(dllChild FAR *c)
  { return sli.actTxt; }
DLLExport void _export FAR PASCAL cb_Set_sli_res(dllChild FAR *c, GLOBALHANDLE res)
  { sli.res = res; }
DLLExport void _export FAR PASCAL cb_Set_sli_Ind(dllChild FAR *c, int Ind)
  { sli.Ind = Ind; }
DLLExport void _export FAR PASCAL cb_Set_sli_actTxt(dllChild FAR *c, LPSTR actTxt)
  { sli.actTxt = actTxt; }
DLLExport LPVOID _export FAR PASCAL cb_ActScanPtr(dllChild FAR *c)
  { return ActScanPtr; }
DLLExport void _export FAR PASCAL cb_Set_ActScanPtr(dllChild FAR *c, LPVOID ActScanPtr)
  { ActScanPtr = ActScanPtr; }
DLLExport void _export FAR PASCAL cb_ExCuteProc(dllChild FAR *c, DWORD Offset, WORD mode)
  { MessageBeep (0) ; }
DLLExport BOOL _export FAR PASCAL cb_IsDocLocked (dllChild FAR *c, WORD RecType,int RunNmbr)
  { return FALSE ; }
DLLExport LPVOID _export FAR PASCAL cb_GetExtraData (dllChild FAR *c, WORD Code,int FAR *size = NULL)
  { return NULL ; }
DLLExport void _export FAR PASCAL cb_PutExtraData (dllChild FAR *c, WORD Type,LPVOID Data,int size)
  { }
DLLExport void _export FAR PASCAL cb_RemoveExtraData (dllChild FAR *c, WORD Type)
  { }
DLLExport void _export FAR PASCAL cb_NextField (dllChild FAR *c)
  { /* !!! */ }
DLLExport void _export FAR PASCAL cb_PrevField (dllChild FAR *c)
  {  /* !!! */ }
DLLExport void _export FAR PASCAL cb_CreateGaussWin(dllChild FAR *c)
  { MessageBeep (0) ; }
DLLExport void _export FAR PASCAL cb_ShowGauss (dllChild FAR *c, double FAR *val,double FAR *norm,double FAR *dev,int AnzRec,LPSTR caption)
  { }
DLLExport GLOBALHANDLE _export FAR PASCAL cb_GetGaussPar (dllChild FAR *c, double FAR *val,double FAR *norm,double FAR *dev,int AnzRun)
  { return NULL ; }
DLLExport void _export FAR PASCAL cb_CloseGauss (dllChild FAR *c)
  { }
DLLExport LPVOID _export FAR PASCAL cb_ReadlData (dllChild FAR *c, DWORD DataRef)
  { return MyGetData (LPDIALOGELEM(c->PrivData),WORD(DataRef)); }
DLLExport void _export FAR PASCAL cb_WritelData (dllChild FAR *c, DWORD DataRef,LPVOID data,int size,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
  { MySetData (LPDIALOGELEM(c->PrivData),WORD(DataRef), data, size, Cmd); }
DLLExport void _export FAR PASCAL cb_SetlConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { }
DLLExport void _export FAR PASCAL cb_SetlOtherConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { }
DLLExport void _export FAR PASCAL cb_ClearlConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { }
DLLExport void _export FAR PASCAL cb_ClearlOtherConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { }
DLLExport void _export FAR PASCAL cb_DellData (dllChild FAR *c, DWORD DataRef,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
  { MySetData (LPDIALOGELEM(c->PrivData),WORD(DataRef), NULL, 0, Cmd); }
DLLExport BOOL _export FAR PASCAL cb_IsUpdatelFromEle (dllChild FAR *c, DWORD DataRef)
  { return FALSE ; }
#ifdef WIN32
DLLExport void _export FAR PASCAL cb_DestroySchiebeLehre (dllChild FAR *c)
  { }
DLLExport void _export FAR PASCAL cb_SetUpSchiebeLehre (dllChild FAR *c)
  { }
#else
DLLExport void _export FAR PASCAL cb_DestroySchiebeLehre (dllChild FAR *c, void)
  { }
DLLExport void _export FAR PASCAL cb_SetUpSchiebeLehre (dllChild FAR *c, void)
  { }
#endif
extern int GetObjSide (FrmObject FAR *obj);
DLLExport int _export FAR PASCAL cb_GetObjSide (dllChild FAR *c, FrmObject FAR *obj)
  { return 0 ; /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */ }
DLLExport FrmObject FAR * _export FAR PASCAL cb_act_obj(dllChild FAR *c)
  {
  return NULL;
  }
DLLExport void _export FAR PASCAL cb_SetActiveExplicit (dllChild FAR *c, FrmObject FAR *obj)
  { }
DLLExport FrmObject FAR * _export FAR PASCAL cb_GetObjectFromPar(dllChild FAR *c, LPVOID param)
  { return GetObjectFromPar(LPSTR(param) - sizeof(WORD)); }
DLLExport int _export FAR PASCAL cb_UpdateEleCount(dllChild FAR *c)
  { return 0 ; }
DLLExport void _export FAR PASCAL cb_EmptyUpdateList(dllChild FAR *c)
  { }
DLLExport void _export FAR PASCAL cb_SetCaretShown(dllChild FAR *c)
  { SetCaretShown(); }
DLLExport void _export FAR PASCAL cb_SetNoCaret(dllChild FAR *c)
  { SetNoCaret(); }
DLLExport void _export FAR PASCAL cb_SetStatus(dllChild FAR *c, LPSTR hlp)
  { }
DLLExport LPTABLEDEF _export FAR PASCAL cb_GetTableDef(dllChild FAR *c,LPSTR Name,WORD FAR *TableInd)
  {
  return NULL;
  }
DLLExport DWORD _export FAR PASCAL cb_GetDocumentID(dllChild FAR *c)
  {
  return 0L;
  }
DLLExport LPDBRECORD _export FAR PASCAL cb_SetRecord(dllChild FAR *c,LPDBRECORD r,WORD TableInd)
  {
  return NULL;
  }
DLLExport void _export FAR PASCAL cb_FreeTableDef(dllChild FAR *c,LPTABLEDEF td)
  {
  }
DLLExport int _export FAR PASCAL cb_GetConstInt (dllChild FAR *c, DWORD DataRef)
  { 
  DBINT FAR *res = (DBINT FAR *) MyGetData (LPDIALOGELEM(c->PrivData),WORD(DataRef));
  WIN_ASSERT (res != NULL);
  if (res != NULL)
    return *res ;
  else
    return 0 ;
  }

DLLExport LONG _export FAR PASCAL cb_GetConstLong (dllChild FAR *c, DWORD DataRef)
  { 
  LONG FAR *res = (LONG FAR *) MyGetData (LPDIALOGELEM(c->PrivData),WORD(DataRef));
  WIN_ASSERT (res != NULL);
  if (res != NULL)
    return *res ;
  else
    return 0 ;
//  return *((LONG FAR *) MyGetData (LPDIALOGELEM(c->PrivData),WORD(DataRef)));
  }

DLLExport void _export FAR PASCAL cb_GetConstFloat (dllChild FAR *c, DWORD DataRef,float FAR *res)
  { 
  *res = *((float FAR *) MyGetData (LPDIALOGELEM(c->PrivData),WORD(DataRef)));
  WIN_ASSERT (res != NULL);
  }



inline void AssignProc(int fncind, FARPROC procaddr)
  {
  dcfunc[fncind] = DCCB_VOID_VOID(MakeProcInstance (procaddr,MyInstance));
  }

void InitFrmObjDll(void)
  {
  AssignProc(DCFUNC_SCHD                 , FARPROC(cb_schd));
  AssignProc(DCFUNC_MYHANDLE             , FARPROC(cb_MyHandle));
  AssignProc(DCFUNC_GET_SCALE            , FARPROC(cb_Get_scale));
  AssignProc(DCFUNC_XP                   , FARPROC(cb_xp));
  AssignProc(DCFUNC_YP                   , FARPROC(cb_yp));
  AssignProc(DCFUNC_X0                   , FARPROC(cb_x0));
  AssignProc(DCFUNC_Y0                   , FARPROC(cb_y0));
  AssignProc(DCFUNC_ANZSIDES             , FARPROC(cb_AnzSides));
  AssignProc(DCFUNC_ACTSIDE              , FARPROC(cb_ActSide));
  AssignProc(DCFUNC_SELCOLOR             , FARPROC(cb_SelColor));
  AssignProc(DCFUNC_HACTIVEPEN           , FARPROC(cb_hActivePen));
  AssignProc(DCFUNC_HINACTIVEPEN         , FARPROC(cb_hInactivePen));
  AssignProc(DCFUNC_GETDOCINFO           , FARPROC(cb_GetDocInfo));
  AssignProc(DCFUNC_RESCALE              , FARPROC(cb_Rescale));
  AssignProc(DCFUNC_WORLDTOLOG           , FARPROC(cb_WorldToLog));
  AssignProc(DCFUNC_GET_LOGTOWORLD       , FARPROC(cb_Get_LogToWorld));
  AssignProc(DCFUNC_HALFPENWIDTH         , FARPROC(cb_HalfPenWidth));
  AssignProc(DCFUNC_PR                   , FARPROC(cb_Pr));
  AssignProc(DCFUNC_TABX                 , FARPROC(cb_tabx));
  AssignProc(DCFUNC_GET_SLI_RES          , FARPROC(cb_Get_sli_res));
  AssignProc(DCFUNC_GET_SLI_IND          , FARPROC(cb_Get_sli_Ind));
  AssignProc(DCFUNC_GET_SLI_ACTTXT       , FARPROC(cb_Get_sli_actTxt));
  AssignProc(DCFUNC_SET_SLI_RES          , FARPROC(cb_Set_sli_res));
  AssignProc(DCFUNC_SET_SLI_IND          , FARPROC(cb_Set_sli_Ind));
  AssignProc(DCFUNC_SET_SLI_ACTTXT       , FARPROC(cb_Set_sli_actTxt));
  AssignProc(DCFUNC_ACTSCANPTR           , FARPROC(cb_ActScanPtr));
  AssignProc(DCFUNC_SET_ACTSCANPTR       , FARPROC(cb_Set_ActScanPtr));
  AssignProc(DCFUNC_EXCUTEPROC           , FARPROC(cb_ExCuteProc));
  AssignProc(DCFUNC_ISDOCLOCKED          , FARPROC(cb_IsDocLocked));
  AssignProc(DCFUNC_GETEXTRADATA         , FARPROC(cb_GetExtraData));
  AssignProc(DCFUNC_PUTEXTRADATA         , FARPROC(cb_PutExtraData));
  AssignProc(DCFUNC_REMOVEEXTRADATA      , FARPROC(cb_RemoveExtraData));
  AssignProc(DCFUNC_NEXTFIELD            , FARPROC(cb_NextField));
  AssignProc(DCFUNC_PREVFIELD            , FARPROC(cb_PrevField));
  AssignProc(DCFUNC_CREATEGAUSSWIN       , FARPROC(cb_CreateGaussWin));
  AssignProc(DCFUNC_SHOWGAUSS            , FARPROC(cb_ShowGauss));
  AssignProc(DCFUNC_GETGAUSSPAR          , FARPROC(cb_GetGaussPar));
  AssignProc(DCFUNC_CLOSEGAUSS           , FARPROC(cb_CloseGauss));
  AssignProc(DCFUNC_READLDATA            , FARPROC(cb_ReadlData));
  AssignProc(DCFUNC_WRITELDATA           , FARPROC(cb_WritelData));
  AssignProc(DCFUNC_SETLCONNECTION       , FARPROC(cb_SetlConnection));
  AssignProc(DCFUNC_SETLOTHERCONNECTION  , FARPROC(cb_SetlOtherConnection));
  AssignProc(DCFUNC_CLEARLCONNECTION     , FARPROC(cb_ClearlConnection));
  AssignProc(DCFUNC_CLEARLOTHERCONNECTION, FARPROC(cb_ClearlOtherConnection));
  AssignProc(DCFUNC_DELLDATA             , FARPROC(cb_DellData));
  AssignProc(DCFUNC_ISUPDATEFROMELE      , FARPROC(cb_IsUpdatelFromEle));
  AssignProc(DCFUNC_DESTROYSCHIEBELEHRE  , FARPROC(cb_DestroySchiebeLehre));
  AssignProc(DCFUNC_SETUPSCHIEBELEHRE    , FARPROC(cb_SetUpSchiebeLehre));
  AssignProc(DCFUNC_GETOBJSIDE           , FARPROC(cb_GetObjSide));
  AssignProc(DCFUNC_ACT_OBJ              , FARPROC(cb_act_obj));
  AssignProc(DCFUNC_SETACTIVEEXPLICIT    , FARPROC(cb_SetActiveExplicit));
  AssignProc(DCFUNC_GETOBJECTFROMPAR     , FARPROC(cb_GetObjectFromPar));
  AssignProc(DCFUNC_UPDATEELECOUNT       , FARPROC(cb_UpdateEleCount));
  AssignProc(DCFUNC_EMPTYUPDATELIST      , FARPROC(cb_EmptyUpdateList));
  AssignProc(DCFUNC_SETCARETSHOWN        , FARPROC(cb_SetCaretShown));
  AssignProc(DCFUNC_SETNOCARET           , FARPROC(cb_SetNoCaret));
  AssignProc(DCFUNC_SETSTATUS            , FARPROC(cb_SetStatus));
  AssignProc(DCFUNC_GETTABLEDEF          , FARPROC(cb_GetTableDef));
  AssignProc(DCFUNC_DOCUMENTID           , FARPROC(cb_GetDocumentID));
  AssignProc(DCFUNC_SETRECORD            , FARPROC(cb_SetRecord));
  AssignProc(DCFUNC_FREETABLEDEF         , FARPROC(cb_FreeTableDef));
  AssignProc(DCFUNC_GETCONSTINT          , FARPROC(cb_GetConstInt));
  AssignProc(DCFUNC_GETCONSTLONG         , FARPROC(cb_GetConstLong));
  AssignProc(DCFUNC_GETCONSTFLOAT        , FARPROC(cb_GetConstFloat));

  InitFrmObjLib(GetParent(hRefWnd), MyInstance, dcfunc, TRUE);
  }

