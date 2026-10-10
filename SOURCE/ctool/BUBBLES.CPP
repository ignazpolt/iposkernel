//---------------------------------------------------------------------------
//   Hilfetexte in Form von Comic-Sprechblasen fuer die Dialog-Elemente
//---------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/ctool/rev/bubbles.cpv   1.12   05 Oct 1998 11:06:08   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/bubbles.cpv  $
// 
//    Rev 1.12   05 Oct 1998 11:06:08   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   03 Mar 1998 08:58:28   Gerhold
// SetTooltipFont
// 
//    Rev 1.10   24 Oct 1997 10:13:42   Gerhold
// Vorbereitung fuer ToolTip
// 
//    Rev 1.9   25 Feb 1997 11:57:20   Gerhold
// SetCapture, ReleaseCapture
// 
//    Rev 1.8   12 Nov 1996 14:03:34   GERHOLD
// Breite des Hilfefensters ist jetzt fix 4000 Einheiten!
// 
//    Rev 1.7   08 Nov 1996 13:25:34   HANNES
// Feld nicht mit Breite -1 sondern mit 30000
// 
//    Rev 1.6   16 Jun 1996 18:46:08   GERHOLD
// rechte Maustaste
// 
//    Rev 1.5   24 Mar 1996 12:10:06   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:41:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   20 Sep 1995 15:58:30   GERHOLD
// Micky-Maus-Sprechblasen wurden durch professionelle Rechtecke ersetzt!
// 
//    Rev 1.2   24 Jul 1995 16:41:14   GERHOLD
// Blasen werden jetzt nicht mehr aktiv gezeichnet.
//---------------------------------------------------------------------------
#include <windows.h>
#include <string.h>
#include <math.h>
#include "dds32.h"
#include "ddsmsg.h"
#include "toolbar.hpp"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "globmem.h"
#include "cfield.hpp"


#define CO_BROWN   0x8080
#define CO_YELLOW  0xFFFF

#define BORDER     40


#define RATIO      0.7
#define MAXPOINTS  180
#define Pi180      (3.1415926535/180.0)

#define   TT_RATIO   0.8

int   XPos, YPos;
LPSTR BubbleStr;
//cField FAR *fld;

POINT  AX[MAXPOINTS];

#define HLPFORMAT   2
extern void SetMMText (HDC hDC,int y = 0);
extern void SetTwips (HDC hDC,int x = 0,int y = 0);
int xv0,yv0;

#define SPACING 10
#define SHADOW  5


// Offset der Variablen fuer die Extrabytes in der Fensterklasse
#define  CBWND_WNDOFFS   0
#define  CBWND_FLDOFFS   4


int ToolTipFont = HLPFORMAT;


//---------------------------------------------------------------------------
// Setzt das Font-Format in der Kurzhilfe
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetToolTipFont (int FontNum)
  {
  if (FontNum >= 0)
    ToolTipFont = FontNum;
  }



DLLExport LONG _export CALLBACK BubbleWinFunc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
  LONG ret = 0;
  static BOOL bToolTip;

  cField FAR *fld = (cField FAR *)GetWindowLong (hWnd, CBWND_FLDOFFS);
//  static LPRECT ToolRect = NULL;

  switch (msg) {
    case WM_CREATE :
      {
      LPCREATESTRUCT cs = LPCREATESTRUCT(lParam);

      bToolTip = *(BOOL FAR *)cs->lpCreateParams;

      XPos = cs->x;
      YPos = cs->y;

      HDC hDC = GetDC (hWnd);
      RECT r;

      SetTwips (hDC);
      fld = new cField (TRANSPARENT,ToolTipFont,0,0,4000,-1,FALSE);

      if (fld == NULL)
        return -1;

      fld->SetWindow (hWnd);
      fld->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
      fld->SetVOrg (0,0,0);
      *fld = BubbleStr;
//      fld->Arrange (int(100.0 * TT_RATIO));      // h / w soll moeglichst 80 % betragen
      fld->GetFieldRect (&r,0);
      
      POINT pt;
      pt.x = r.right;
      pt.y = r.bottom;
      LPtoDP (hDC,&pt,1);
      pt.x += SPACING ;
      pt.y += SPACING ;

      LPtoDP (hDC, LPPOINT(&r), 2);

      SetMMText (hDC);
      ReleaseDC (hWnd, hDC);
      
      SetWindowLong (hWnd, CBWND_FLDOFFS, LONG(fld));
      
      int Height = r.bottom-r.top + 1 + 3 * SPACING / 2;
      int Width  = r.right-r.left + 1 + 3 * SPACING / 2;
      
      // Fenster von oben nach unten
      BOOL FromUpper = ((YPos + Height) < GetSystemMetrics(SM_CYSCREEN));
      // Fenster von links nach rechts
      BOOL FromLeft = ((XPos + Width) < GetSystemMetrics(SM_CXSCREEN));

      if (!FromLeft)
        XPos = GetSystemMetrics(SM_CXSCREEN) - Width - SPACING;
        
      if (!FromUpper)  
        YPos -= Height;

      SetWindowPos (hWnd, HWND_TOP, XPos + r.left, YPos + r.top, 
                             Width, 
                             Height,
                             SWP_NOACTIVATE);
      break;
      }

    case WMU_TOOLTIP_TEXTCHANGED :
      {
      HDC hDC = GetDC (hWnd);
      RECT r;

      SetTwips (hDC);

      *fld = LPSTR(lParam);
      fld->GetFieldRect (&r,0);

      POINT pt;
      pt.x = r.right;
      pt.y = r.bottom;
      LPtoDP (hDC,&pt,1);

      LPtoDP (hDC, LPPOINT(&r), 2);

      SetMMText (hDC);
      ReleaseDC (hWnd, hDC);
      
      int Height = r.bottom-r.top + 1 + 3 * SPACING / 2;
      int Width  = r.right-r.left + 1 + 3 * SPACING / 2;

      SetWindowPos (hWnd, 0, 0, 0, Width, Height,
                    SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
      }
      break;

    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd, &ps);

      LOGBRUSH LogBrush;
      HBRUSH   OldBrush;
      RECT rc;

      GetClientRect (hWnd, &rc);

      rc.right -= SHADOW;
      rc.bottom -= SHADOW;

      if (!bToolTip) {
        // Schatten besteht aus 1-0-Bitmap und laesst den Hintergrund durchscheinen
        //-------------------------------------------------------------------------
        LogBrush.lbStyle = BS_PATTERN;

  #ifdef WIN32
        LogBrush.lbHatch = LONG(LoadBitmap(hLibInst, "FOCUSBITS"));
  #else
        LogBrush.lbHatch = LoadBitmap(hLibInst, "FOCUSBITS");
  #endif

        OldBrush = (HBRUSH)SelectObject (hDC, CreateBrushIndirect(&LogBrush));

        OffsetRect (&rc, SHADOW, SHADOW);
        PatBlt (hDC, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, 0xA000C9);    // Quelle & Ziel

        DeleteObject(SelectObject(hDC, OldBrush));
        DeleteObject(HBITMAP(LogBrush.lbHatch));

        OffsetRect (&rc, -SHADOW, -SHADOW);
        }

      // das Fenster fuer den Text zeichnen
      //-----------------------------------
      
      LogBrush.lbStyle = BS_PATTERN;
#ifdef WIN32
      LogBrush.lbHatch = LONG(LoadBitmap(hLibInst, "POSTITBACK"));
#else
      LogBrush.lbHatch = LoadBitmap(hLibInst, "POSTITBACK");
#endif
      OldBrush = (HBRUSH)SelectObject (hDC, CreateBrushIndirect(&LogBrush));

      PatBlt (hDC, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, PATCOPY);
      
      DeleteObject(SelectObject(hDC, OldBrush));
      DeleteObject(HBITMAP(LogBrush.lbHatch));

      OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
      Rectangle (hDC, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
      SelectObject(hDC, OldBrush);

      SetTwips (hDC, SPACING/2, SPACING/2);
      fld->Paint (hDC, 0, FALSE);
      SetMMText (hDC);

      EndPaint (hWnd, &ps);
      }
      break;  

//-------------------------------------------------------------------
// ACHTUNG: Das ist erst seit der Version mit der rechten Maustaste
    case WM_KEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
//-------------------------------------------------------------------
    case WM_RBUTTONUP:
      {
      ReleaseCapture ();
      HWND hParent = HWND(GetWindowLong (hWnd, CBWND_WNDOFFS));
      PostMessage(hParent,WMU_DESTROYBUBBLE,0,0L);
      }
      break;
      
    case WM_DESTROY :
      delete fld;
      break ;
      
    default :
      ret = DefWindowProc (hWnd, msg, wParam, lParam);
    }
  
  return ret;
  }



DLLExport HWND _export WINAPI CreateBubbleWindow (int X, int Y, LPSTR str, 
                                                  HWND Parent, BOOL ToolTip)
  {
  POINT pt;
  pt.x = X;
  pt.y = Y;

  ClientToScreen (Parent, &pt);
  BubbleStr = str;

  // das Fenster darf beim Erzeugen noch nicht sichtbar sein
  // Grund: es wuerde sich dann automatisch aktivieren, d.h.
  //        das Elternfenster ist dann deaktiviert.
  HWND newWin = CreateWindow (szBubbleClassName, NULL,
                              WS_POPUP | WS_CLIPSIBLINGS,
                              pt.x, pt.y, 100, 100,
                              Parent, 0, hLibInst, LPVOID(&ToolTip));
  if (newWin != NULL) {
    ShowWindow (newWin, SW_SHOWNOACTIVATE);
    SetWindowLong(newWin, CBWND_WNDOFFS, LONG(Parent));
    if (!ToolTip)
      SetCapture (newWin);
    }
  return newWin;
  }

