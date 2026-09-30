//
//  $Header:   P:/marille/clinicum/ctool/rev/barelem1.cpv   1.42   17 Feb 1999 20:06:14   Martin  $
//  $Log:   P:/marille/clinicum/ctool/rev/barelem1.cpv  $
// 
//    Rev 1.42   17 Feb 1999 20:06:14   Martin
// GroupBox korrigiert
// 
//    Rev 1.41   29 Jan 1999 22:39:52   Martin
// GroupBox::MoveTool korrigiert
// 
//    Rev 1.40   23 Nov 1998 10:51:18   Martin
// BmpFloat funktionsfaehig gemacht
// 
//    Rev 1.39   10 Nov 1998 07:56:50   Hannes
// ColorRect: Auch im Normalfall mit Rectangle (Verhindern von Dithern)
// 
//    Rev 1.38   05 Oct 1998 11:05:48   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.37   08 Jul 1998 16:27:38   Hannes
// 
//    Rev 1.36   12 Jun 1998 16:08:20   Martin
// Line3D reagiert jetzt auf Updates auf die x und y Koorinate
// 
//    Rev 1.35   05 Mar 1998 16:19:18   Gerhold
// XYFromRect ... PosCtrl bekommt auch ein MoveTool
// 
//    Rev 1.34   23 Feb 1998 19:59:58   Hannes
// MoveTool bei Line3d
// 
//    Rev 1.33   18 Feb 1998 20:59:36   Hannes
// TBActivate vor dem SetFocus
// 
//    Rev 1.32   16 Feb 1998 19:10:56   Hannes
// Weitere Fehler in MoveTool
// 
//    Rev 1.31   05 Feb 1998 17:43:58   Hannes
// Naechstes Workaround bei der Groupbox
// 
//    Rev 1.29   25 Aug 1997 10:54:04   gerhold
// ColorRect kann jetzt auch transparente Rechtecke zeichnen
// 
//    Rev 1.28   01 Aug 1997 10:27:20   Martin
// GroupBox: sollte jetzt auf Updates aller Parameter reagieren
// 
//    Rev 1.27   04 Mar 1997 11:19:42   Hannes
// SetFocusToTool -> SetToolFocus (FALSE) auf das alte Element
// 
//    Rev 1.26   28 Feb 1997 15:01:22   Gerhold
// Erweiterung der kontextsensitiven Menus durch Scriptbefehl
// 
//    Rev 1.25   03 Sep 1996 10:00:10   HANNES
// barelem zerteilt
// 
//    Rev 1.24   21 Jun 1996 09:44:08   GERHOLD
// ActionBox mit Status 4 ist jetzt ein unsichtbarer PushButton
// 
//    Rev 1.23   16 Jun 1996 18:44:06   GERHOLD
// int -> DBINT, BOOL -> DBBOOL
// CapDC, MemDC raus
// Funktion GetToolCoordinates
// 
//    Rev 1.22   24 Mar 1996 12:09:54   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.21   18 Mar 1996 16:29:24   GERHOLD
// _export SetToolObjectColor, neuer Stil 4 im ActionRect
// 
//    Rev 1.20   04 Mar 1996 21:11:34   GERHOLD
// DrawEdge in WIN32 anders
// 
//    Rev 1.19   20 Feb 1996 11:35:40   GERHOLD
// Groupbox hat einen neuen Stil "2"
// 
//    Rev 1.18   16 Feb 1996 13:42:02   GERHOLD
// GroupBox::PaintTool hat ein bisschen zu viel gezeichnet
// 
//    Rev 1.17   02 Feb 1996 10:41:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.16   11 Jan 1996 03:37:02   HANNES
// HotKeyAction
// 
//    Rev 1.15   12 Dec 1995 11:43:50   GERHOLD
// SetFocusOnTool (der zweite Parameter von SetToolFocus muss FALSE sein)
// 
//    Rev 1.14   23 Nov 1995 18:00:48   hannes
// SetToolFocus-Funktionen haben einen neuen Parameter "mode"
// 
//    Rev 1.13   19 Nov 1995 15:40:38   GERHOLD
// neuer SelektionsStil (3) in ActionRect
// XYFromRect wird mit DrawEdge umrandet
// 
//    Rev 1.12   24 Aug 1995 09:36:46   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.11   14 Aug 1995 18:00:12   HANNES
// ColorRect ... Laenge des Parameterblockes abgefragt
// 
//    Rev 1.10   12 Aug 1995 19:23:22   GERHOLD
// ColorRect kann auch Muster zeichnen (letzter Parameter)
// 
//    Rev 1.9   19 Jul 1995 11:16:12   GERHOLD
// 
//    Rev 1.8   11 Jul 1995 12:43:26   HANNES
// Prozeduren von barelem -> barelem1 umgelagert
// 
//    Rev 1.7   10 Jun 1995 22:03:34   HANNES
// 
//    Rev 1.6   05 Apr 1995 16:39:30   GERHOLD
// 
//    Rev 1.5   27 Mar 1995 13:18:28   HANNES
//  
// 
//    Rev 1.4   20 Mar 1995 12:11:36   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.3   19 Dec 1994 08:14:22   GERHOLD
// Cursor in XYFromRect
// 
//    Rev 1.2   05 Sep 1994 13:16:24   GERHOLD
//  UpDown-Control, Edit-Elemente mit Combo-Button sind nicht mehr editierbar
//  Begin-, Continue-, EndCapture auf On_LButtonDown, On_MouseMove,
//  On_LButtonUp geaendert.
// 
//    Rev 1.1   05 Aug 1994 11:53:14   GERHOLD
// XYFromRect (Bewegen eines Bitmaps im Koordinatensystem)
// 
//    Rev 1.0   24 Jun 1994 16:41:10   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   29 Nov 1993 08:37:52   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define MODULENUM  60               // Modul-Nummer fuer Fehlermeldung
#include "winass.hpp"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "globmem.h"
#include "font.hpp"
#include "cfield.hpp"
#include "wordwin.hpp"
#include "toolbar.hpp"
#define NODDSDATA
#include "dds.hpp"

////////////////////////////////////////////////////////////
//  Implementierung der Klasse GetBmpFloat
////////////////////////////////////////////////////////////
LPSTR BmpFloat::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }

void BmpFloat::GetRect ()
  {
  int x0,y0;
  ToolRect.left   = x0 = ToDevKoordX(tx);
  ToolRect.top    = y0 = ToDevKoordY(ty, Parent->Layer);
  ToolRect.right  = x0 + ToDevKoordX(tw);
  ToolRect.bottom = y0 + ToDevKoordY(th);
  }

typedef StaticTool FAR *LPSTATIC;

void BmpFloat::Load ()
  {
  DBINT FAR *lpix = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpiy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(* GetData)(privData, Param()->_h);
  DBWIN_ASSERT ((lpix != NULL) && (lpiy != NULL) && (lpw != NULL) && (lph != NULL));
  tx = *lpix;
  ty = *lpiy;
  tw = *lpw;
  th = *lph;
  GetRect();
  DBBOOL FAR *IsDisabled = (DBBOOL FAR *)(* GetData) (privData,Param()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));
  float FAR *lpmin = (float FAR *) (* GetData) (privData,Param()->lpmin);
  float FAR *lpmax = (float FAR *) (* GetData) (privData,Param()->lpmax);
  float FAR *lprmin = (float FAR *) (* GetData) (privData,Param()->rmin);
  float FAR *lprmax = (float FAR *) (* GetData) (privData,Param()->rmax);
  DBWIN_ASSERT ((lpmin != NULL) && (lpmax != NULL) && (lprmin != NULL) && (lprmax != NULL)); 
  xmin = double (*lpmin);
  xmax = double (*lpmax);
  a = double (ToolRect.left  - ToolRect.right) / double (*lprmin - *lprmax);
  b = double (ToolRect.left) - a * double (*lprmin);

  float FAR *lpx = (float FAR *) (* GetData) (privData,Param()->Id);
  DBWIN_ASSERT (lpx != NULL);
  x = double (*lpx);

  x = min (xmax,max(xmin,x));

  LPSTATIC FAR *lpst = (LPSTATIC FAR *) (* GetData) (privData,Param()->staticTool);
  if ((lpst != NULL) && (*lpst != NULL)) {
    st = *lpst ;
    GLOBALHANDLE hGmem;
    *(st->field) >> hGmem ;
    LPSTR txt = LPSTR(GlobalLock (hGmem));
    pattern = LPSTR (GetGlobMem (lstrlen (txt) + 1));
    lstrcpy (pattern,txt);
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    }
  else
    st = NULL , pattern = NULL ;
  SetText ();
  
  DBINT FAR *lpcol = (DBINT FAR *)(* GetData)(privData, Param()->pattern._Col);
  DBINT FAR *lprow = (DBINT FAR *)(* GetData)(privData, Param()->pattern._Row);
  BmpRef.Col = *lpcol;
  BmpRef.Row = *lprow;
  }

void BmpFloat::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection)(privData, Param()->_w, StructData);
  (* ClearConnection)(privData, Param()->_h, StructData);
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);

  if (pattern != NULL) {
    FreeGlobMem (pattern);
    pattern = NULL;
    }
  }

void BmpFloat::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection)(privData, Param()->_w, StructData);
  (* SetConnection)(privData, Param()->_h, StructData);
  }

void BmpFloat::Write ()
  {
  float fx = float(x);
  (* SetData) (privData, Param()->Id, &fx,
               sizeof(float), StructData);
  }

void BmpFloat::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);
    }
  }

void BmpFloat::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 2, 2);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }

void BmpFloat::PaintBmp (HDC hDC,HDC hmemDC)
  {
  int     AnzCols, AnzRows;
  HBITMAP hBmp = GetBitmap (
                      Param()->pattern.bitId, 
                      AnzRows, AnzCols
                           );
  DBWIN_ASSERT((BmpRef.Col < AnzCols) &&
             (BmpRef.Row < AnzRows));
  BITMAP bi;
  GetObject (hBmp, sizeof(bi), &bi);
  int bmWidth  = bi.bmWidth  / AnzCols ;
  int bmHeight = bi.bmHeight / AnzRows ;
  hBmp = (HBITMAP)SelectObject (hmemDC, hBmp);
  int oldmode = SetStretchBltMode (hDC,STRETCH_ANDSCANS);
  StretchBlt (hDC, ToolRect.left, ToolRect.top,
                   ToolRect.right - ToolRect.left + 1,
                   ToolRect.bottom - ToolRect.top + 1,
              hmemDC,
                   int (BmpRef.Col) * bmWidth,
                   int (BmpRef.Row) * bmHeight,
                   bmWidth,bmHeight,
              SRCCOPY
             );
  SetStretchBltMode (hDC,oldmode);
  SelectObject (hmemDC, hBmp);
  }


void BmpFloat::PaintBack (HDC hDC)
  {
  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(WHITE_BRUSH));
  HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
  Rectangle (hDC, ToolRect.left, ToolRect.top, ToolRect.right+1,ToolRect.bottom+1);
  SelectObject (hDC, OldPen);
  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, ToolRect.left-1, ToolRect.bottom+1, NULL);
  LineTo (hDC, ToolRect.left-1, ToolRect.top-1);
  LineTo (hDC, ToolRect.right+1, ToolRect.top-1);
  DeleteObject (SelectObject(hDC, OldPen));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, ToolRect.right+1, ToolRect.top-1, NULL);
  LineTo (hDC, ToolRect.right+1, ToolRect.bottom+1);
  LineTo (hDC, ToolRect.left-1, ToolRect.bottom+1);
  SelectObject (hDC, OldPen);

  SelectObject (hDC, OldBrush);
  }

inline void Chg (int FAR &a,int FAR &b) 
  { 
  int dummy ; dummy = a ; a = b ; b = dummy ; 
  }

void BmpFloat::ShowPos (double xact)
  {

  int x = int (a * xact + b) ;
  if (xold != x) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  
    int old = SetROP2 (hDC,R2_XORPEN);
    HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (WHITE_PEN));
    if (xold >= 0) {
      // Alte Linie wegloeschen
      MoveToEx (hDC,xold,ToolRect.top, NULL);
      LineTo (hDC,xold,ToolRect.bottom);
      }
    MoveToEx (hDC,x,ToolRect.top, NULL);
    LineTo (hDC,x,ToolRect.bottom);
    SelectObject (hDC,hOldPen);
    SetROP2 (hDC,old);
    xold = x;

    ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
    }

  }

void BmpFloat::SetText ()
  {
  if ((st != NULL) && (pattern != NULL)) {
    st->Invalidate (TRUE);
    char txt[64],txt1[16];
    int h = int (x * 10.0) ;
    wsprintf (txt1,"%d",h);
    int l = lstrlen (txt1);
    txt1[l+1] = '\0';
    txt1[l] = txt1[l-1];
    txt1[l-1] = '.';
    lstrcpy (txt,pattern);
    lstrcat (txt,txt1);
    *(st->field) = txt;
    st->GetRect ();
    }
  }

void BmpFloat::PaintTool (HDC hDC, HDC hmemDC)
  {
  PaintBack (hDC);
  PaintBmp (hDC,hmemDC);
  xold = -1;
  ShowPos (x);
  }

BOOL BmpFloat::HitTest (LPPOINT pt)             
  {
  return (PtInRect(LPRECT(&ToolRect), *pt));
  }

void BmpFloat::Transform (int xp,double FAR &x)
  {
  x = (double (xp) - b) / a;
  }

void BmpFloat::On_LButtonDown (LPPOINT pt)
  {
//  CapDC = GetDC(Parent->Parent->hWndToolbar());
  Capturing = TRUE;
  SetCapture (Parent->Parent->hWndToolbar());
  xdold = x ;
  if (HitTest(pt)) {
    Transform (pt->x,x);
    x = min (xmax,max(xmin,x));
    ShowPos (x);
    SetText ();
    }
  }

void BmpFloat::On_MouseMove (LPPOINT pt)
  {
  if (HitTest(pt)) {
    Transform (pt->x,x);
    x = min (xmax,max(xmin,x));
    ShowPos (x);
    SetText ();
    }
  }

BOOL BmpFloat::On_LButtonUp (LPPOINT pt)
  {
  if (HitTest(pt)) {
    Transform (pt->x,x);
    x = min (xmax,max(xmin,x));
    ShowPos (x);
    SetText ();
    Write ();
    }
  else {
    x = xdold;
    SetText ();
    ShowPos (x);
    }
  Capturing = FALSE;
  ReleaseCapture ();
//  ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  CapDC = 0;
  return TRUE;
  }


//****************************************************************************
//*                                                                          *
//*                                                                          *
//*                                                                          *
//****************************************************************************
PosControl::PosControl (LPRECT rc, int x, int y, HBITMAP hBmp, 
                        int width, int height)
  {
  BackGround = 0;

  Update (rc, x, y, hBmp, width, height);
  }

PosControl::~PosControl (void)
  {
  if (BackGround != 0)
    DeleteObject (BackGround);
  }


void PosControl::Update (LPRECT rc, int x, int y, HBITMAP hBmp, 
                         int width, int height)
  {
  CopyRect (LPRECT(&rcParent), LPRECT(rc));
    bmX =  x;   // Startposition des Bitmaps
    bmY =  y;

    bmWidth = width;
    bmHeight = height;


  if ((bitmap = hBmp) != 0) {
//    if (BackGround != 0)
//      DeleteObject (BackGround);
    }
  else {
    bmWidth = (rcParent.right-rcParent.left) / 5;
    bmHeight = (rcParent.bottom-rcParent.top) / 5;
    }
  }


void PosControl::MoveTool (short dy)
  {
  bmY += dy;
  OffsetRect (LPRECT(&rcParent), 0, dy);
  }

BOOL PosControl::HitTest (POINT pt)
  {
  return ((pt.x >= bmX) && (pt.x <= bmX+bmWidth) &&
          (pt.y >= bmY) && (pt.y <= bmY+bmHeight));
  }        
  
  
void PosControl::OnLButtonDown (LPPOINT pt)
  {
  xOld = pt->x;   // Mauskoordinaten merken
  yOld = pt->y;
  xOffs = pt->x - bmX ;
  yOffs = pt->y - bmY ;
  }

void PosControl::OnMouseMove (HWND hWnd, LPPOINT pt)
  {
  HDC hDCOldBk, hDCNewBk, hDCMem, hDCCache, hDCMask;
  HBITMAP hbmOldPrev, hbmNewPrev, hbmNew, hbmMask,
          hbmCache, hbmPrev, hbmPrevCache, hbmTemp, hbmPrevMask;
  COLORREF rgbBack;

  HDC hDC = GetDC (hWnd);

  if (pt->x - xOffs < rcParent.left)              pt->x = rcParent.left + xOffs ;
  if (pt->x - xOffs > rcParent.right - bmWidth)   pt->x = rcParent.right - bmWidth + xOffs ;
  if (pt->y - yOffs < rcParent.top)               pt->y = rcParent.top + yOffs ;
  if (pt->y - yOffs > rcParent.bottom - bmHeight) pt->y = rcParent.bottom - bmHeight + yOffs ;

  int dx = pt->x - xOld;  // Verschiebung zur vorigen Position
  int dy = pt->y - yOld;

  
  bmX += dx;      // Position kann geaendert werden
  xOld = pt->x;   // Maus-Position merken
  pt->x = bmX;

  bmY += dy;
  yOld = pt->y;
  pt->y = bmY;
  
  if ((dx != 0) || (dy != 0)) {
    hDCOldBk = CreateCompatibleDC (hDC);
    hDCNewBk = CreateCompatibleDC (hDC);
    hDCMem   = CreateCompatibleDC (hDC);
    hDCCache = CreateCompatibleDC (hDC);
    hDCMask  = CreateCompatibleDC (hDC);

    rgbBack = SetBkColor (hDCMem, RGB(0, 0, 0));

    // temporaeres Bitmap fuer den neuen Hintergrund
    hbmNew = CreateCompatibleBitmap (hDC, bmWidth, bmHeight);
    hbmMask = CreateCompatibleBitmap (hDCMask, bmWidth, bmHeight);
    hbmCache = CreateCompatibleBitmap (hDC, bmWidth, bmHeight);

    hbmPrev      = (HBITMAP)SelectObject (hDCMem, bitmap);
    hbmNewPrev   = (HBITMAP)SelectObject (hDCNewBk, hbmNew);
    hbmOldPrev   = (HBITMAP)SelectObject (hDCOldBk, BackGround);
    hbmPrevCache = (HBITMAP)SelectObject (hDCCache, hbmCache);
    hbmPrevMask  = (HBITMAP)SelectObject (hDCMask, hbmMask);

    // Maske erzeugen
    BitBlt (hDCMask, 0, 0, bmWidth, bmHeight, 
            hDCMem, 0, 0, SRCCOPY);
    // Bildschirm kopieren
    BitBlt (hDCNewBk, 0, 0, bmWidth, bmHeight, 
            hDC, bmX, bmY, SRCCOPY);
    // Teil des neuen Hintergrundes mit altem Hintergrund ueberschreiben
    BitBlt (hDCNewBk, -dx, -dy, bmWidth, bmHeight, 
            hDCOldBk, 0, 0, SRCCOPY);

    // Sprite auf den alten Hintergrund kopieren
    BitBlt (hDCOldBk, dx, dy, bmWidth, bmHeight, 
            hDCMask, 0, 0, SRCAND);
    BitBlt (hDCOldBk, dx, dy, bmWidth, bmHeight, 
            hDCMem, 0, 0, SRCPAINT);
    // Das Sprite ohne flackern auf den Schirm kopieren
    BitBlt (hDCCache, 0, 0, bmWidth, bmHeight, 
            hDCNewBk, 0, 0, SRCCOPY);
    BitBlt (hDCCache, 0, 0, bmWidth, bmHeight, 
            hDCMask, 0, 0, SRCAND);
    BitBlt (hDCCache, 0, 0, bmWidth, bmHeight, 
            hDCMem, 0, 0, SRCPAINT);

    BitBlt (hDC, bmX, bmY, bmWidth, bmHeight, 
            hDCCache, 0, 0, SRCCOPY);

    // alten Hintergrund auf den Schirm kopieren
    BitBlt (hDC, bmX-dx, bmY-dy, bmWidth, bmHeight, 
            hDCOldBk, 0, 0, SRCCOPY);

    SelectObject (hDCMem, hbmPrev);
    SelectObject (hDCNewBk, hbmNewPrev);
    SelectObject (hDCOldBk, hbmOldPrev);
    SelectObject (hDCCache, hbmPrevCache);
    SelectObject (hDCMask, hbmPrevMask);
    SetBkColor (hDCMem, rgbBack);
  
    hbmTemp = BackGround;
    BackGround = hbmNew;
    hbmNew = hbmTemp;

    DeleteObject (hbmNew);
    DeleteObject (hbmCache);
    DeleteObject (hbmMask);

    DeleteDC (hDCOldBk); 
    DeleteDC (hDCNewBk);
    DeleteDC (hDCMem);
    DeleteDC (hDCMask);
    DeleteDC (hDCCache);
    }

  ReleaseDC (hWnd, hDC);
  }

void PosControl::OnLButtonUp (LPPOINT pt)
  {
  }



void PosControl::Paint (HDC hDC)
  {
  if (bitmap != 0) {
    HDC hMemDC = CreateCompatibleDC (hDC);

    if (BackGround == 0) {
      HBITMAP hbmNew = CreateCompatibleBitmap (hDC, bmWidth, bmHeight);
      HBITMAP hbmPrev = (HBITMAP)SelectObject (hMemDC, hbmNew);
      BitBlt (hMemDC, 0, 0, bmWidth, bmHeight,
              hDC, bmX, bmY, SRCCOPY);
      BackGround = hbmNew;
      SelectObject (hMemDC, hbmPrev);
      }

    HBITMAP hBmp = (HBITMAP)SelectObject (hMemDC, bitmap);
    BitBlt (hDC, bmX, bmY, bmWidth, bmHeight,
            hMemDC, 0, 0, SRCCOPY);
    SelectObject (hMemDC, hBmp);
    DeleteDC (hMemDC);
    }
  else {  
    COLORREF OldColor = SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));
    SetBkColor (hDC, OldColor);
    }
  }



XYFromRect::XYFromRect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize)        // CONSTRUCTOR
  {
  IsEnabled = TRUE;
  SetRectEmpty (LPRECT(&rcInside));
  }


XYFromRect::~XYFromRect (void)
  {
  if (PosCtrl != NULL)
    delete PosCtrl;
  }


void XYFromRect::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData,Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(* GetData)(privData,Param()->_h);
  tx = *lpx;
  ty = *lpy;
  tw = *lpw;
  th = *lph;

  GetRect ();

  DBINT FAR *lpcol = (DBINT FAR *)(* GetData)(privData, BitRef()->_Col);
  DBINT FAR *lprow = (DBINT FAR *)(* GetData)(privData, BitRef()->_Row);
  BmpRef.Col = *lpcol;
  BmpRef.Row = *lprow;

//--------------------------------------------------
  int AnzRows, AnzCols;
  BITMAP bi;

  HBITMAP hBmp = GetBitmap (              // das Bitmap aus der Datenbank holen
                      BitRef()->bitId, 
                      AnzRows, AnzCols
                           );

  GetObject (hBmp, sizeof(bi), &bi);      // Bitmap-Eigenschaften ermitteln
  int bmWidth  = bi.bmWidth  / AnzCols ;
  int bmHeight = bi.bmHeight / AnzRows ;

  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  HDC hDCMem = CreateCompatibleDC (hDC);   // fuer das Teilbild
  HDC hDCTemp = CreateCompatibleDC (hDC);  // fuer das Datenbank-Bitmap

  HBITMAP hbmTemp = (HBITMAP)SelectObject (hDCTemp, hBmp);  // Datenbankbitmap in den DC

  HBITMAP hbmNew = CreateCompatibleBitmap (hDC, bmWidth, bmHeight);
  HBITMAP hbmPrev = (HBITMAP)SelectObject (hDCMem, hbmNew);  // das wird das Teilbitmap

  // einen Teil des Datenbankbitmaps auswaehlen
  BitBlt (hDCMem, 0, 0, bmWidth, bmHeight,       
          hDCTemp, BmpRef.Col * bmWidth, 
                   BmpRef.Row * bmHeight, 
                   SRCCOPY);
  
  SelectObject (hDCMem, hbmPrev);
  SelectObject (hDCTemp, hbmTemp);
  DeleteDC (hDCTemp);
  DeleteDC (hDCMem);

  ReleaseDC (Parent->Parent->hWndToolbar() ,hDC);

//--------------------------------------------------
  float FAR *XPos = (float FAR *) (* GetData) (privData,Param()->XPos);
  float FAR *YPos = (float FAR *) (* GetData) (privData,Param()->YPos);

  float fx, fy;
  int x, y;
  
  float FAR *lpXStartRange = (float FAR *) (* GetData) (privData,Param()->_XStartRange);
  float FAR *lpYStartRange = (float FAR *) (* GetData) (privData,Param()->_YStartRange);
  float FAR *lpXEndRange = (float FAR *) (* GetData) (privData,Param()->_XEndRange);
  float FAR *lpYEndRange = (float FAR *) (* GetData) (privData,Param()->_YEndRange);
  DBWIN_ASSERT ((lpXStartRange != NULL) && (lpYStartRange != NULL) && (lpXEndRange   != NULL) && (lpYEndRange   != NULL));
  XStartRange = *lpXStartRange ;
  YStartRange = *lpYStartRange ;
  XEndRange   = *lpXEndRange   ;
  YEndRange   = *lpYEndRange   ;

  if (XPos == NULL)
    fx = float (0.0);
  else
    fx = min(max(*XPos, XStartRange), XEndRange);
  x = RetransformX (fx,bmWidth);

  if (YPos == NULL)
    fy = float (0.0);
  else
    fy = min(max(*YPos, YStartRange), YEndRange);
  y = RetransformY (fy,bmHeight);

  if (PosCtrl == NULL)
    PosCtrl = new PosControl (LPRECT(&rcInside), x, y, hbmNew, bmWidth, bmHeight);
  else
    PosCtrl->Update (LPRECT(&rcInside), x, y, hbmNew, bmWidth, bmHeight);

//  PosCtrl->SetBackGround (hbmBack);
  }

void XYFromRect::FixConnection ()
  {
  (* SetConnection) (privData, Param()->XPos, StructData);
  (* SetConnection) (privData, Param()->YPos, StructData);

  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->hd.HotKey, StructData);

  (* SetConnection) (privData, Param()->_w, StructData);
  (* SetConnection) (privData, Param()->_h, StructData);
  }

void XYFromRect::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->XPos, StructData);
  (* ClearConnection) (privData, Param()->YPos, StructData);

  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);
  (* ClearConnection) (privData, Param()->hd.HotKey, StructData);

  (* ClearConnection) (privData, Param()->_w, StructData);
  (* ClearConnection) (privData, Param()->_h, StructData);
  }


void XYFromRect::On_LButtonDown (LPPOINT pt)
  {
//  RECT rc;

  if (HitTest(pt)) {
    if (PosCtrl->HitTest(*pt)) {
      DenyBusyCursor();
      Capturing = TRUE;
      SetCapture (Parent->Parent->hWndToolbar());
//      CapDC = GetDC(Parent->Parent->hWndToolbar());
      PosCtrl->OnLButtonDown(pt);
      }
    }
  }


void XYFromRect::On_MouseMove (LPPOINT pt)
  {
//  RECT  rc;
  
  if (Capturing) {
    DenyBusyCursor();
    PosCtrl->OnMouseMove (Parent->Parent->hWndToolbar(), pt);
  
    float xval, yval;

    if (pt->x > 0) {
      TransformX (pt->x, &xval);
      (* SetData) (privData, Param()->XPos, &xval, sizeof(xval), StructData);
      }

    if (pt->y > 0) {
      TransformY (pt->y, &yval);
      (* SetData) (privData, Param()->YPos, &yval, sizeof(yval), StructData);
      }
    }
  }
  
  
BOOL XYFromRect::On_LButtonUp (LPPOINT pt) 
  {
  if (Capturing) {
    ReleaseCapture ();
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//    CapDC = 0;
    }
    
  AllowBusyCursor();
  Capturing = FALSE;
  return TRUE;
  }

LPSTR XYFromRect::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }


//---------------------------------------------------------------
void XYFromRect::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int x1 = x0 + ToDevX(tw);
  int y1 = y0 + ToDevY(th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);
  CopyRect (LPRECT(&rcInside), LPRECT(&ToolRect));
  InflateRect (LPRECT(&rcInside), -2, -2);
  rcInside.right -= 1;
  
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));
  }


BOOL XYFromRect::HasTabStop ()
  {
  return IsEnabled ;
  }


BOOL XYFromRect::HitTest (LPPOINT pt)
  {
  return (PtInRect(LPRECT(&ToolRect), *pt));
  }
  

void XYFromRect::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT(&ToolRect), doErase);
  }        


void XYFromRect::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    OffsetRect (LPRECT(&rcInside),0,dy);

    if (PosCtrl != NULL)
      PosCtrl->MoveTool (dy);

    Invalidate (FALSE);
    }
  }

BOOL XYFromRect::OnChar (WORD wP)
  {
//  POINT  pt;

  switch (wP) {
    case VK_UP :
      {
/*
      pt.x = rcArrow.left+1;
      pt.y = OldRect.bottom-5;
      if (pt.y < rcArrow.top)
        pt.y = rcArrow.top;
      On_LButtonDown (&pt);
      On_LButtonUp (&pt);
      SetCaretPos (OldRect.left+2, OldRect.bottom-1);
*/
      }
      break;
    case VK_DOWN :
      {
/*
      pt.x = rcArrow.left+1;
      pt.y = OldRect.bottom+5;
      if (pt.y > rcArrow.bottom)
        pt.y = rcArrow.bottom;
      On_LButtonDown (&pt);
      On_LButtonUp (&pt);
      SetCaretPos (OldRect.left+2, OldRect.bottom-1);
*/
      }
      break ;
    }

  return TRUE;
  }




void XYFromRect::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  if (state) {
/*
    CreateCaret (Parent->Parent->hWndToolbar(), NULL, OldRect.right-OldRect.left-4, 2);
    SetCaretPos (OldRect.left+2, OldRect.bottom-1);
    ShowCaret (Parent->Parent->hWndToolbar());
*/
    }
  else {
//    DestroyCaret ();
    }
  }

  
void XYFromRect::TransformX (int x, float FAR *val)
  {
  int x0 = rcInside.left;
  int x1 = rcInside.right - PosCtrl->GetBMWidth();
  *val = float (x - x0) * (XEndRange-XStartRange) /
                float (x1 - x0) + XStartRange;
  }

int XYFromRect::RetransformX (double val,int bmWidth)
  {
  int x0 = rcInside.left;
  int x1 = rcInside.right - bmWidth;
  return int ((val-XStartRange) * double (x1 - x0) /
                (XEndRange-XStartRange) + x0); 
  }

void XYFromRect::TransformY (int y, float FAR *val)
  {
  int y0 = rcInside.top;
  int y1 = rcInside.bottom - PosCtrl->GetBMHeight();
  *val = float (y - y0) * (YEndRange-YStartRange) /
                float (y1 - y0) + YStartRange;
  }

int XYFromRect::RetransformY (double val,int bmHeight)
  {
  int y0 = rcInside.top;
  int y1 = rcInside.bottom - bmHeight;
  return int ((val-YStartRange) * double (y1 - y0) /
                (YEndRange-YStartRange) + y0); 
  }

void XYFromRect::PaintTool (HDC hDC, HDC hmemDC)
  {
  COLORREF OldBack = SetBkColor (hDC, GetSysColor(COLOR_WINDOW));
  ExtTextOut (hDC, ToolRect.left, ToolRect.top, ETO_OPAQUE, LPRECT(&ToolRect), NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  MyDrawEdge (hDC, LPRECT(&ToolRect), MY_EDGE_HWND, MY_BF_RECT);
/*  
  HBRUSH OldBrush = SelectObject (hDC, GetStockObject(WHITE_BRUSH));
  Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, ToolRect.right-1, ToolRect.bottom-1);
  SelectObject (hDC, OldBrush);

  HPEN OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, ToolRect.left, ToolRect.bottom, NULL);
  LineTo (hDC, ToolRect.left, ToolRect.top);
  LineTo (hDC, ToolRect.right, ToolRect.top);
  DeleteObject (SelectObject(hDC, OldPen));

  OldPen = SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, ToolRect.right-1, ToolRect.top, NULL);
  LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);
  LineTo (hDC, ToolRect.left-1, ToolRect.bottom-1);
  SelectObject (hDC, OldPen);
*/
  if (PosCtrl != NULL)
    PosCtrl->Paint (hDC);

  }

/*****************************************************************************\
*                                                                             *
*                                                                             *
*    FLAP - MAP                                                               *
*                                                                             *
*                                                                             *
\*****************************************************************************/
FlapMap::FlapMap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) : tool (RefWnd,Data,pData,pSize)        
  {
  FlapFont = 0;
  }


FlapMap::~FlapMap ()
  {
  if (FlapFont)
    DeleteObject (FlapFont);
  if (FlapRects != NULL)
    FreeGlobMem (FlapRects);
  }



void FlapMap::On_LButtonDown (LPPOINT pt)
  {
  if (HitTest(pt)) {
    for (int i = 0; i < AnzLines; i++) {
      
      if (PtInRect (&FlapRects[i], *pt)) {
        char FlapStr[2];

        FlapChar = char ((26.0 / AnzLines) * i) + 'A';
        FlapStr[0] = FlapChar;
        FlapStr[1] = '\0';
        (* SetData) (privData, Param()->StrToWrite, LPSTR(&FlapStr), sizeof(FlapStr), StructData);
        Update ();
        break;
        }   //  if (PtInRect)
      }   //  for
    }   //  if (HitTest)
  }

BOOL FlapMap::On_LButtonUp (LPPOINT pt)
  {
  (* CallCommand) (privData, Param()->CallOnChange,Param());
  return TRUE ;
  }

void FlapMap::FixConnection ()
  {
  (* SetConnection) (privData, Param()->Id, StructData);
  (* SetConnection) (privData, Param()->_Width, StructData);
  }


void FlapMap::GetRect ()
  {
  typedef ExternTool FAR *LPEXTERNTOOL;
  RECT    rcExtern;
  int     x0, y0, x1, y1;

  LPEXTERNTOOL FAR *MyTool = (LPEXTERNTOOL FAR *)(* GetData) (privData, Param()->ExternTool);
  if (MyTool != NULL) {
    CopyRect (&rcExtern, LPRECT(&((* MyTool)->ToolRect)));

    x0 = rcExtern.right + 5;
    y0 = rcExtern.top;
    x1 = x0 + ToDevX(long(tw + (AnzLines * dx)));
    y1 = rcExtern.bottom;

    (* SetData) (privData, Param()->hd._x, &(* MyTool)->tx,
                 sizeof((* MyTool)->tx), StructData);
    (* SetData) (privData, Param()->hd._y, &(* MyTool)->ty,
                 sizeof((* MyTool)->ty), StructData);

/*  
    Param()->hd.x = ((* MyTool)->Param())->hd.x;
    Param()->hd.y = ((* MyTool)->Param())->hd.y;
*/
    }
  else {
    x0 = ToDevKoordX(tx);
    y0 = ToDevKoordY(ty, Parent->Layer);
    x1 = x0+ToDevX (tw + int(AnzLines * dx));
    y1 = y0;
    }  

  SetRect (LPRECT(&ToolRect), x0, y0,  x1, y1);
  
  if (ty >= 0)
    Parent->CheckLayerHeight (ToolRect.bottom);
  FlapWidth = ToDevX (tw);

  if (FlapFont)                                          // existierende Fonts loeschen
    DeleteObject (FlapFont);
  FlapHeight = (ToolRect.bottom-ToolRect.top) / int(AnzLines);  // Hoehe einer Flappe
  
  FlapFont = CreateFont(FlapHeight/2, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0,
                          FF_SWISS, "Arial");
  }


BOOL FlapMap::HitTest (LPPOINT pt)
  {
  return (PtInRect(LPRECT (&ToolRect), *pt));
  }


void FlapMap::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }


int FlapMap::RightOffs (int i,int AnzElems,int Deepest)
  {
  int j = i - Deepest ;
  return (j + AnzElems - 1) % AnzElems ;
  }


#define CONSTOFFS 5
void FlapMap::SetFlapRect (int i, int Deepest)
  {
  int x0 = ToolRect.left + CONSTOFFS +
    int (double (RightOffs (i, int(AnzLines), Deepest)) * dx);
  int y0 = ToolRect.top+(i*FlapHeight);
  FlapRects[i].left = x0 ;
  FlapRects[i].right = x0 + FlapWidth;
  FlapRects[i].top = y0;
  FlapRects[i].bottom = y0 + FlapHeight - 1;
  }


void FlapMap::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBBOOL FAR *IsDisabled = (DBBOOL FAR *) 
          (* GetData) (privData,Param()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));

  DBINT FAR *lpw = (DBINT FAR *)(* GetData) (privData,Param()->_Width);
  DBWIN_ASSERT (lpw != NULL);
  tw = *lpw;

  DBINT FAR *lpdx = (DBINT FAR *)(* GetData) (privData,Param()->_dx);
  DBWIN_ASSERT (lpdx != NULL);
  dx = *lpdx;

  DBINT FAR *lpAnzLines = (DBINT FAR *)(* GetData) (privData, Param()->_AnzLines);
  AnzLines = (lpAnzLines != NULL) ? *lpAnzLines : 1;

  LPSTR lpstr = (LPSTR) (* GetData) (privData, Param()->Id);
  FlapChar = (lpstr != NULL) ? *lpstr : 'A' ;

#ifdef WIN32
  FlapChar = char(DWORD(CharUpper(&FlapChar)));
#else
  FlapChar = char(DWORD(AnsiUpper(LPSTR(MAKELP(0,FlapChar)))));
#endif

  if (FlapChar <= 'A') FlapChar = 'A';
  if (FlapChar >= 'Z') FlapChar = 'Z';

  if (FlapRects == NULL)
    FlapRects = (LPRECT)GetGlobMem (sizeof(*FlapRects) * int (AnzLines));

  Highest = int (double(FlapChar - 'A'+1) / double(26.0 / AnzLines));
  if (Highest >= AnzLines)
    Highest = int(AnzLines)-1;
  int Deepest = Highest - 1 ;
  if (Deepest < 0) 
    Deepest += int(AnzLines);

  GetRect ();
  for (int i = 0 ; i < AnzLines ; i++)
    SetFlapRect (i, Deepest);
  }


void FlapMap::MoveTool ()
  {
  int y0 = Gety0 ();
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);
    }
  }


void FlapMap::Update ()
  {
  LPSTR lpstr = (LPSTR) (* GetData) (privData, Param()->Id);
  FlapChar = (lpstr != NULL) ? *lpstr : 'A' ;
#ifdef WIN32
  FlapChar = char(DWORD(CharUpper(&FlapChar)));
#else
  FlapChar = char(DWORD(AnsiUpper(LPSTR(MAKELP(0,FlapChar)))));
#endif
  if (FlapChar <= 'A') FlapChar = 'A';
  if (FlapChar >= 'Z') FlapChar = 'Z';
  int nwh = int (double (FlapChar-'A'+1) / double (26.0 / AnzLines));
  if (nwh != Highest) {
    Invalidate (TRUE);
    Load ();
    }
  }


void FlapMap::PaintTool (HDC hDC, HDC hmemDC)
  {
  int    i, DeepestElem;
  HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));
  HPEN   OldPen;
  HFONT  OldFont = (HFONT)SelectObject (hDC, FlapFont);
  UINT   OldAlign = SetTextAlign(hDC, TA_TOP | TA_LEFT);

  HRGN   hRgn; 
  
  int    FlapEll = FlapHeight/4;

  double incr = 26.0 / double (AnzLines);
  char   ch[2];
  
  ch[0] = 'A' ;
  ch[1] = '\0';

  hRgn = CreateRectRgn (ToolRect.left, ToolRect.top, ToolRect.right, ToolRect.bottom);
  SelectClipRgn (hDC, hRgn);

  DWORD oldc = SetTextColor (hDC, RGB(0, 0, 0));  // dia alte Farbe merken

  DeepestElem = Highest-1;
  if (DeepestElem < 0) 
    DeepestElem += int (AnzLines);

  for (i = DeepestElem; i >= 0; i--) {
    RoundRect (hDC, FlapRects[i].left-FlapEll, FlapRects[i].top, 
                    FlapRects[i].right, FlapRects[i].bottom,
                    FlapEll, FlapEll);
    Rectangle (hDC, ToolRect.left, ToolRect.top,
                    FlapRects[i].left+1, ToolRect.bottom);

    OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    MoveToEx (hDC, FlapRects[i].left, FlapRects[i].top+1, NULL);
    LineTo (hDC, FlapRects[i].left, FlapRects[i].bottom-1);
    SelectObject (hDC, OldPen);

    ch[0] = char (incr * double(i)) + 'A';
    if (i == Highest)
      SetTextColor (hDC,RGB(0,0,255));
    else
      SetTextColor (hDC,RGB(0,0,0));
    DrawText(hDC, (char FAR *)ch, -1, &FlapRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
    }

  for (i = int(AnzLines)-1; i > DeepestElem; i--) {
    RoundRect (hDC, FlapRects[i].left-FlapEll, FlapRects[i].top, 
                    FlapRects[i].right, FlapRects[i].bottom,
                    FlapEll, FlapEll);
    Rectangle (hDC, ToolRect.left, ToolRect.top,
                    FlapRects[i].left+1, ToolRect.bottom);
    
    OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    MoveToEx (hDC, FlapRects[i].left, FlapRects[i].top+1, NULL);
    LineTo (hDC, FlapRects[i].left, FlapRects[i].bottom-1);
    SelectObject (hDC, OldPen);

    ch[0] = char (incr * double(i)) + 'A';
    if (i == Highest)
      SetTextColor (hDC,RGB(0,0,255));
    else
      SetTextColor (hDC,RGB(0,0,0));
    DrawText(hDC, (char FAR *)ch, -1, &FlapRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
    }

  DeleteObject (hRgn);
  SelectClipRgn (hDC, NULL);

  SetTextColor (hDC, oldc);
  SetTextAlign (hDC, OldAlign);
  SelectObject (hDC, OldFont);
  SelectObject (hDC, OldPen);
  SelectObject (hDC, OldBrush);
  }


void FlapMap::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->Id, StructData);
  (* ClearConnection) (privData, Param()->_Width, StructData);
  }

///////////////////////////////////////////////////////////
//  Explizites Ausloesen der Hotkey - Aktion
///////////////////////////////////////////////////////////
typedef tool FAR *LPTOOL;
DLLExport void _export WINAPI DoHotkeyAction (DWORD Tool,LPVOID privData)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) 
      (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL)) {
    if ((*MyTool)->Parent->Parent->ToolWithFocus != NULL)
      (*MyTool)->Parent->Parent->ToolWithFocus->SetToolFocus(FALSE);
    (*MyTool)->Parent->Parent->ToolWithFocus = *MyTool;
    (*MyTool)->SetToolFocus(TRUE);
    (*MyTool)->HotKeyAction (FALSE);
    }
  }

//---------------------------------------------------------------------------
// SetToolObjectColor
// .... Ruft fuer das Element <Tool> eine virtuelle Funktion auf, um die
//      Farbe ueber das Script zu aendern.
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetToolObjectColor (DWORD Tool, LPVOID privData, COLORREF color)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) 
      (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL))
    (*MyTool)->SetObjectColor (color);
  }

typedef ToolEdit FAR *LPTOOLEDIT;
DLLExport void _export WINAPI SetEdFormat (DWORD Tool,LPVOID privData,int Format)
  {
  LPTOOLEDIT FAR *MyTool = (LPTOOLEDIT FAR *) 
      (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL)) {
    WWSetFormat ((*MyTool)->hWndEdit,Format);
    }
  }



DLLExport void _export WINAPI SetFocusOnTool (DWORD Tool, LPVOID  privData, BOOL State)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) 
      (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL)) {
    if ((*MyTool)->Parent->Parent->ToolWithFocus != NULL) {
      BOOL oldActive;
      if (tbActive != NULL) 
        oldActive = (* tbActive) (FALSE);
      (*MyTool)->Parent->Parent->ToolWithFocus->SetToolFocus(FALSE);
      if (tbActive != NULL) 
        (* tbActive) (oldActive);
      }
    (*MyTool)->Parent->Parent->ToolWithFocus = *MyTool;
    (*MyTool)->SetToolFocus (State, FALSE);
    }
  }

//---------------------------------------------------------------------------
// GetToolCoordinates
// ... Liefert die Koordinaten fuer das angegebene Tool (in Dialogeinheiten)
//---------------------------------------------------------------------------
DLLExport void _export WINAPI GetToolCoordinates (DWORD Tool, LPVOID  privData, 
                                                  int FAR *x, int FAR *y,
                                                  int FAR *w, int FAR *h,
                                                  BOOL absolute)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) 
      (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL)) {
    RECT rc;

    // jedes Tool hat ein ToolRect => her damit!
    CopyRect (&rc, LPRECT(&(*MyTool)->ToolRect));

    // beziehen sich die Koordinaten auf den gesamten Bildschirm?
    if (absolute) {
      ClientToScreen ((*MyTool)->Parent->Parent->hWndToolbar(), LPPOINT(&rc));
      ClientToScreen ((*MyTool)->Parent->Parent->hWndToolbar(), LPPOINT(&rc.right));
      }

    // <int> schneidet <floats> ab => aufrunden!
    *x = int(float(rc.left) / BaseUnit + 0.5);
    *y = int(float(rc.top) / BaseUnit + 0.5);
    *w = int(float(rc.right - rc.left) / BaseUnit + 0.5);
    *h = int(float(rc.bottom - rc.top) / BaseUnit + 0.5);
    }
  }


DLLExport void _export WINAPI AppendContextMenu (DWORD Tool, LPVOID menuprocpar,
                                                 LPVOID menuprivData, int menuprivdatasize,
                                                 LPSTR MenuText, DWORD MenuProc, 
                                                 UINT Flags, WORD mode)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) (* GetData) (menuprivData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL))
    (*MyTool)->SetContextMenu (menuprocpar, menuprivData, menuprivdatasize,
                               MenuText, MenuProc, Flags, mode);
  }

DLLExport void _export WINAPI RemoveContextMenu (DWORD Tool, LPVOID privData)
  {
  LPTOOL FAR *MyTool = (LPTOOL FAR *) (* GetData) (privData,Tool);
  if ((MyTool != NULL) && (*MyTool != NULL))
    (*MyTool)->RemoveContextMenu ();
  }

/*****************************************************************************\
*                                                                             *
*        faerbiges - Rechteck                                                 *
*                                                                             *
\*****************************************************************************/
#define HIT_BORDER  5

inline void ExChange(int FAR &x1,int FAR &x2)
  {
  int dummy = x1 ;
  x1 = x2 ;
  x2 = dummy ;
  }

void ColorRect::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Style, StructData);
  if (Param()->hd.structSize >= (sizeof(tool_colorrect) - sizeof(WORD)))
    (* SetConnection) (privData,Param()->_FillStyle, StructData);
  (* SetConnection) (privData,Param()->_FillColor, StructData);
  (* SetConnection) (privData,Param()->hd._x, StructData);
  (* SetConnection) (privData,Param()->hd._y, StructData);
  (* SetConnection) (privData,Param()->_x1, StructData);
  (* SetConnection) (privData,Param()->_y1, StructData);
  }

BOOL ColorRect::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL) {
    RECT rcTmp;
    BOOL GotIt;
    
    CopyRect (&rcTmp, LPRECT(&ToolRect));
    InflateRect (&rcTmp, HIT_BORDER, HIT_BORDER);
    GotIt = PtInRect (&rcTmp, *pt);
    if (GotIt) {
      InflateRect (&rcTmp, -2*HIT_BORDER, -2*HIT_BORDER);
      GotIt = !PtInRect (&rcTmp, *pt);
      }

    return GotIt;
    }
  else
    return FALSE ;
  }

void ColorRect::GetRect ()
  {
  X0 = ToDevKoordX(tx);
  Y0 = ToDevKoordY(ty, Parent->Layer);
  X1 = ToDevKoordX(tx1);
  Y1 = ToDevKoordY(ty1);

  SetRect (LPRECT (&ToolRect), X0, Y0, X1, Y1);
  if (ToolRect.right < ToolRect.left)
    ExChange(ToolRect.left,ToolRect.right);
  if (ToolRect.bottom < ToolRect.top)
    ExChange(ToolRect.bottom,ToolRect.top);
  InflateRect (LPRECT(&ToolRect), max(3,BorderWidth/2+1), max(3,BorderWidth/2+1));

  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty1));
  }

void ColorRect::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }

void ColorRect::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lptx1 = (DBINT FAR *)(* GetData)(privData, Param()->_x1);
  DBINT FAR *lpty1 = (DBINT FAR *)(* GetData)(privData, Param()->_y1);
  
  DBWIN_ASSERT ((lptx1 != NULL) && (lpty1 != NULL));

  tx1 = *lptx1;
  ty1 = *lpty1;

  DWORD FAR* lpStyle = (DWORD FAR*)(* GetData) (privData,Param()->Style);

  // wenn keine Daten gelesen werden, wird eine schwarze Linie
  // mit der Strichstaerke 0 und dem Attribut PS_SOLID gezeichnet!
  LONG LineAttr = (lpStyle != NULL) ? *lpStyle : 0;

  DWORD FAR* lpFillColor = (DWORD FAR*)(* GetData) (privData,Param()->_FillColor);
  FillColor = lpFillColor ? *lpFillColor : 0L;

  // der Fuell-Stil-Parameter ist free; ist er ueberhaupt da?
  int FillStyle = -1;
  if (Param()->hd.structSize >= (sizeof(tool_colorrect) - sizeof(WORD))) {
    DBINT FAR *lpFillStyle = (DBINT FAR*)(* GetData) (privData,Param()->_FillStyle);
    FillStyle = lpFillStyle ? *lpFillStyle : -1;
    }

  COLORREF BorderColor = LineAttr & 0x00FFFFFF;
  int Width = int((LineAttr & 0x0F000000) >> 24);
  BorderStyle = int((LineAttr & 0xF0000000) >> 28);
  
  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  mapFact = double (GetDeviceCaps(hDC, LOGPIXELSX)/1440.0);
  BorderWidth = (Width*(GetDeviceCaps(hDC, LOGPIXELSX))/72);

  // Das Handle fuer den Stift wird hier erzeugt
  if (PenHandle != 0)
    DeleteObject (PenHandle);

  if (PenHandle2 != NULL)
    DeleteObject (PenHandle2);

  if (LineAttr != 0xFFFFFFFF)
    PenHandle = CreatePen (PS_SOLID, BorderWidth, BorderColor);
  else
    PenHandle = 0;

  // wird missbraucht um eine zweite Linienfarbe fuer vertieften Rahmen zu erhalten
  if (FillStyle >= 10)
    PenHandle2 = CreatePen (PS_SOLID, BorderWidth, FillColor);
  else
    PenHandle2 = NULL;

  if (BrushHandle != 0) {
    DeleteObject (BrushHandle);
    BrushHandle = 0;
    }
    
  if ((FillStyle != 0xFFFF) && (FillStyle < 10) && (FillStyle >= 0)) {
    LOGBRUSH lb;
    lb.lbStyle = BS_HATCHED;
    lb.lbColor = FillColor;
    lb.lbHatch = FillStyle;
    BrushHandle = CreateBrushIndirect (&lb);
    }
  else if (PenHandle2 == NULL) {
    BrushHandle = CreateSolidBrush (GetNearestColor (hDC,FillColor));
    }
  
  // ACHTUNG: GetRect wird erst hier aufgerufen, da die Liniendicke fuer
  // das <ToolRect> ausschlaggebend ist !!!
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  GetRect ();
  }

void ColorRect::Update ()
  {
  Invalidate (TRUE);
  Load (); 
  Invalidate (FALSE);
  }

void ColorRect::MoveTool ()
  {
  int y0 = Gety0 ();
  int y1 = ToDevKoordY(ty1, Parent->Layer) ;
  int y = min(y0,y1);
  int dy = y - (ToolRect.top + max(3,BorderWidth/2+1));
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);
    }
  }

void ColorRect::PaintTool (HDC hDC, HDC hMemDC)
  {
  RECT rcPaint;

  CopyRect (&rcPaint, LPRECT(&ToolRect));
  int dx = max(3,BorderWidth/2+1);
  InflateRect (&rcPaint, -dx, -dx);

  // wurde also ein "Brush" erzeugt, dann muﬂ man das Rechteck "regulaer" zeichnen.
  if (BrushHandle) {
    HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));
    HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, BrushHandle);
    Rectangle (hDC, rcPaint.left, rcPaint.top, rcPaint.right, rcPaint.bottom);
    SelectObject (hDC, OldBrush);
    SelectObject (hDC, OldPen);
    }
  else {
    // ohne "Brush" kann das Rechteck mit "ExtTextOut" gezeichnet werden.
    if ((FillColor != -1) && (PenHandle2 == NULL))  {
      COLORREF OldBack = SetBkColor (hDC, FillColor);
      ExtTextOut (hDC, X0, Y0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
      SetBkColor (hDC, OldBack);
      }
    else if (PenHandle2 == NULL) {
      InvertRect (hDC, &rcPaint);
      }
    }

  // vertieften Rahmen zeichnen
  if (PenHandle2) {
    HPEN OldPen = (HPEN)SelectObject(hDC, PenHandle);
    MyMoveTo (hDC, X0, Y1);
    MyLineTo (hDC, X0, Y0,mapFact,BorderStyle,BorderWidth);
    MyLineTo (hDC, X1, Y0,mapFact,BorderStyle,BorderWidth);
    SelectObject (hDC, OldPen);

    OldPen = (HPEN)SelectObject (hDC, PenHandle2);
    MyLineTo (hDC, X1, Y1,mapFact,BorderStyle,BorderWidth);
    MyLineTo (hDC, X0, Y1,mapFact,BorderStyle,BorderWidth);
    SelectObject (hDC, OldPen);
    }
  else if (PenHandle) {
    // es wurde ein "Stift" angegeben, also zeichne einen Rahmen.
    HPEN OldPen = (HPEN)SelectObject(hDC, PenHandle);
    MyMoveTo (hDC, X0, Y0);
    MyLineTo (hDC, X1, Y0,mapFact,BorderStyle,BorderWidth);
    MyLineTo (hDC, X1, Y1,mapFact,BorderStyle,BorderWidth);
    MyLineTo (hDC, X0, Y1,mapFact,BorderStyle,BorderWidth);
    MyLineTo (hDC, X0, Y0,mapFact,BorderStyle,BorderWidth);
    SelectObject (hDC, OldPen);
    }
  }



void ColorRect::Reset (BOOL doClear)
  {
  if (PenHandle != 0)
    DeleteObject (PenHandle);
  PenHandle = 0;

  if (PenHandle2 != NULL)
    DeleteObject (PenHandle2);
  PenHandle2 = NULL;

  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Style, StructData);
  if (Param()->hd.structSize >= (sizeof(tool_colorrect) - sizeof(WORD)))
    (* ClearConnection) (privData,Param()->_FillStyle, StructData);
  (* ClearConnection) (privData,Param()->_FillColor, StructData);

  (* ClearConnection) (privData,Param()->hd._x, StructData);
  (* ClearConnection) (privData,Param()->hd._y, StructData);
  (* ClearConnection) (privData,Param()->_x1, StructData);
  (* ClearConnection) (privData,Param()->_y1, StructData);
  }


/*****************************************************************************\
*                                                                             *
*        Action - Rect                                                        *
*                                                                             *
\*****************************************************************************/
void ActionRect::FixConnection ()
  {
  (* SetConnection) (privData, Param()->Color, StructData);
  (* SetConnection) (privData, Param()->StateFlag, StructData);

  (* SetConnection) (privData, Param()->_w, StructData);
  (* SetConnection) (privData, Param()->_h, StructData);
  }


void ActionRect::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int x1 = x0+ToDevX(tw);
  int y1 = y0+ToDevY(th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);

  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));
  }


BOOL ActionRect::HitTest (LPPOINT pt)             
  {
  return (PtInRect(LPRECT (&ToolRect), *pt));
  }


  
void ActionRect::Invalidate (BOOL doErase)
  {
  // das zu invalidierende Rechteck wird ein bisserl groesser um im 
  // Selektionsstil 0 den Rahmen rundherum zeichnen zu koennen
  RECT rc;
  CopyRect (&rc, LPRECT (&ToolRect));
  InflateRect (&rc, 2, 3);
  InvalidateRect (Parent->Parent->hWndToolbar(), &rc, doErase);
  }



void ActionRect::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(* GetData)(privData, Param()->_h);

  DBWIN_ASSERT ((lpw != NULL) && (lph != NULL));

  tw = *lpw;
  th = *lph;

  GetRect ();
  // Farbe fuer den Hintergrund und Flag, ob bei Auswahl invertiert wird
  IsEnabled = TRUE;
  COLORREF FAR *lpColor = (COLORREF FAR*)(* GetData) (privData,Param()->Color);
  DBINT FAR* lpState = (DBINT FAR*)(* GetData) (privData,Param()->StateFlag);

  BkColor = (lpColor != NULL) ? *lpColor : 0xFFFFFF;
  StateFlag = (lpState != NULL) ? *lpState : 0;
  }

void ActionRect::MoveTool ()
  {
  int y0 = Gety0 ();
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);
    }
  }

void ActionRect::PressIn ()
  {
  if (!IsPressed) {
    IsPressed = TRUE;
    Invalidate (TRUE);
//    PaintState ();
    }
  }

void ActionRect::PressOut ()
  {
  if (IsPressed) {
    IsPressed = FALSE;
    Invalidate (TRUE);
//    PaintState ();
    }
  }

void ActionRect::On_LButtonDown (LPPOINT pt)
  {
//  CapDC = GetDC(Parent->Parent->hWndToolbar());
  IsPressed = FALSE;
  Capturing = TRUE;
  SetCapture (Parent->Parent->hWndToolbar());
  if (HitTest(pt)) 
    PressIn ();
  }

void ActionRect::On_MouseMove (LPPOINT pt)
  {
    if (HitTest(pt))
      PressIn();
    else
      PressOut();
  }

BOOL ActionRect::On_LButtonUp (LPPOINT pt)
  {
  ReleaseCapture ();
  Capturing = FALSE;
  PressOut();
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  CapDC = 0;

  if (HitTest(pt)) {
    Invalidate (TRUE);
    (* CallCommand) (privData, Param()->Id,Param());
    }

  return TRUE;
  }

void ActionRect::PaintState ()
  {
  HPEN   OldPen;
  HBRUSH OldBrush;

  if (StateFlag == 4) {
    SetToolFocus (FALSE, FALSE);
    return;
    }

  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  
  OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
  if (IsPressed)
    OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
  else
    OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, BkColor));

  Rectangle (hDC, ToolRect.left+2, ToolRect.top+2, 
                  ToolRect.right-2, ToolRect.bottom-1);

  DeleteObject (SelectObject (hDC, OldPen));
  SelectObject (hDC, OldBrush);

  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }

extern void PaintFocusRect (HDC hDC, RECT rc);

void ActionRect::PaintTool (HDC hDC, HDC hMemDC)
  {
  RECT rc;
  HBRUSH OldBrush;
  HPEN   OldPen;

  CopyRect (&rc, LPRECT(&ToolRect));

  if (IsPressed) {
    InflateRect (&rc, 1, 2);
    PaintFocusRect (hDC, rc);
    InflateRect (&rc, -1, -2);
    }
    
  if (StateFlag == 4)
    return;
/*
  if (StateFlag == 4) {
    if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
      if (IsPressed) {
//
//        COLORREF OldBack = SetBkColor (hDC, BkColor);
//        rc.right++;
//        ExtTextOut (hDC, rc.left, rc.top, ETO_OPAQUE, &rc, NULL, 0, NULL);
//        SetBkColor (hDC, OldBack);
//
//        }
//      else
        PaintFocusRect (hDC, rc);
        }
      }
    return;
    }
*/
  OldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(BkColor));
  OldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));
    
  Rectangle (hDC, rc.left, rc.top, 
                  rc.right, rc.bottom+1);
  SelectObject (hDC, OldPen);
    
  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, rc.left, rc.bottom-1, NULL);
  LineTo (hDC, rc.left, rc.top);
  LineTo (hDC, rc.right-1, rc.top);
  DeleteObject (SelectObject(hDC, OldPen));
    
  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0xC0, 0xC0, 0xC0)));
  Rectangle (hDC, rc.left+1, rc.top+1, rc.right-1, rc.bottom);
  DeleteObject (SelectObject(hDC, OldPen));
    
  DeleteObject (SelectObject (hDC, OldBrush));
    
  OldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));
  MoveToEx (hDC, rc.left+1, rc.bottom-2, NULL);
  LineTo (hDC, rc.left+1, rc.top+1);
  LineTo (hDC, rc.right-2, rc.top+1);
    
  SelectObject (hDC, OldPen);
    
  // selektiert
  if (StateFlag == 3) {
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
    OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
    Rectangle (hDC, rc.left-2, rc.top-2, rc.right+2, rc.bottom+3);
    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);
    }
  else
  if (StateFlag == 2) {
    SetROP2 (hDC, R2_XORPEN);
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
    OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    Rectangle (hDC, rc.left+2, rc.top+2, rc.right-2, rc.bottom-1);
    Rectangle (hDC, rc.left+3, rc.top+3, rc.right-3, rc.bottom-2);
    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);
    SetROP2 (hDC, R2_COPYPEN);
    }
  else
  // invertiert
  if (StateFlag == 1) {
    InflateRect (&rc, -2, -2);
    InvertRect (hDC, &rc);
    }
  }

void ActionRect::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  RECT  rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 1, 1);
  
  InvalidateRect (Parent->Parent->hWndToolbar(), &rc, FALSE);

  // Focus natuerlich nur setzen, wenn vorher keiner da war
  if (state && (GetFocus() != Parent->Parent->hWndToolbar()))
    SetFocus (Parent->Parent->hWndToolbar());
  }


void ActionRect::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->Color, StructData);
  (* ClearConnection) (privData, Param()->StateFlag, StructData);

  (* ClearConnection) (privData, Param()->_w, StructData);
  (* ClearConnection) (privData, Param()->_h, StructData);
  }

void GroupBox::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lph = (DBINT FAR *)(* GetData)(privData, Param()->_h);
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_w);
  DBWIN_ASSERT ((lph != NULL) && (lpw != NULL)) ;
  tw = *lpw;
  th = *lph;
  DBINT FAR *lpStyle = (DBINT FAR *)(* GetData)(privData, Param()->_Style);
  DBINT FAR *lpDrawBkGround = (DBINT FAR *)(* GetData)(privData, Param()->_DrawBkGround);
  DWORD FAR *lpColor = (DWORD FAR *)(* GetData)(privData, Param()->_Color);
  DBWIN_ASSERT ((lpStyle != NULL) && (lpDrawBkGround != NULL) && (lpColor != NULL)) ;
  Style = *lpStyle ;
  DrawBkGround = *lpDrawBkGround;
  Color = *lpColor;

  rcPaint.left   = ToDevKoordX (tx);
  rcPaint.top    = ToDevKoordY (ty, Parent->Layer);
  oldy0 = rcPaint.top;
  rcPaint.right  = ToDevKoordX (tx + tw);
  rcPaint.bottom = ToDevKoordY (ty + th, Parent->Layer);

  StaticTool::Load ();
  }

void GroupBox::FixConnection ()
  {
  (* SetConnection) (privData, Param()->_h, StructData);
  (* SetConnection) (privData, Param()->_Style, StructData);
  (* SetConnection) (privData, Param()->_DrawBkGround, StructData);
  (* SetConnection) (privData, Param()->_Color, StructData);
  StaticTool::FixConnection ();
  }

void GroupBox::Reset (BOOL doClear)
  {
  (* ClearConnection) (privData, Param()->_h, StructData);
  (* ClearConnection) (privData, Param()->_Style, StructData);
  (* ClearConnection) (privData, Param()->_DrawBkGround, StructData);
  (* ClearConnection) (privData, Param()->_Color, StructData);

  // if (IsWindow (Parent->Parent->hWndToolbar()))
    StaticTool::Reset (doClear);
  SetRectEmpty(LPRECT(&ToolRect));
  }

void GroupBox::Invalidate (BOOL doErase)
  {
  RECT r;
  CopyRect (&r,LPRECT (&ToolRect));
  r.top -= 10;
  InvalidateRect (Parent->Parent->hWndToolbar(), &r, doErase);
  }

void GroupBox::GetTextPos (HDC hDC,LPPOINT p)
  {
  p->x = ToDevKoordX (tx + 4) ;
  p->y = ToDevKoordY (ty, Parent->Layer) + 1;
  DPtoLP (hDC,p,1);
  LPFORMATMETRIC lpfm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,Format);
  p->y -= lpfm->yBaseHeight / 2;
  }

int GroupBox::GetTextWidth (HDC hDC)
  {
  return -1;
  }

void GroupBox::GetRect ()
  {
  RECT r;

  field->GetFieldRect (&r,0);
  RectToDev (&r);
  if (IsRectEmpty(LPRECT(&r))) {
    xe = rcPaint.left;
    xb = rcPaint.left;
    yb = rcPaint.top+2;
    }
  else  {  
    xe = r.right + 2;
    xb = r.left - 2;
    yb = r.bottom + 2;
    }
  
  RECT rb;
  CopyRect (&rb,LPRECT(&rcPaint));   // jetzt die Abmessungen der Groupbox
  InflateRect (&rb,1,1);
  UnionRect (LPRECT (&ToolRect),LPRECT (&r),&rb);  // und beide vereinen
  // einen MoveTool simulieren, damit es kompatibel bleibt
  ToolRect.bottom += (rcPaint.top - ToolRect.top) / 2;
  if (ty >= 0)
    Parent->CheckLayerHeight (ToolRect.bottom);
  }


BOOL GroupBox::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL) {
    RECT rcTmp;
    BOOL GotIt;
    
    CopyRect (&rcTmp, LPRECT(&ToolRect));
    InflateRect (&rcTmp, HIT_BORDER, HIT_BORDER);
    GotIt = PtInRect (&rcTmp, *pt);
    if (GotIt) {
      InflateRect (&rcTmp, -2*HIT_BORDER, -2*HIT_BORDER);
      GotIt = !PtInRect (&rcTmp, *pt);
      }

    return GotIt;
    }
  else
    return FALSE ;
  }

void GroupBox::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy;
#ifdef UEBERLEGT
  if (oldy0 > 0)
    dy = y0 - oldy0;
  else
    dy = y0 - ToolRect.top;
#endif
  dy = y0 - oldy0;
  oldy0 = y0;
  if (dy != 0) {
    StaticTool::MoveTool ();
    OffsetRect (LPRECT (&rcPaint),0,dy);
    }
  }

void GroupBox::MyRectangle (HDC hDC,int x0,int y0,int x1,int y1)
  {
  MoveToEx (hDC,xb,y0, NULL);
  LineTo (hDC,x0,y0);
  LineTo (hDC,x0,y1);
  LineTo (hDC,x1,y1);
  LineTo (hDC,x1,y0);
  LineTo (hDC,xe,y0);
  }

void GroupBox::MyFillRectangle (HDC hDC,int x0,int y0,int x1,int y1)
  {
  Rectangle (hDC,x0,y0,xb+1,y1);
  Rectangle (hDC,xb,yb,xe+1,y1);
  Rectangle (hDC,xe+1,y0,x1+2,y1+2);
  }

void GroupBox::PaintTool (HDC hDC, HDC hmemDC)
  {
  HPEN   OldPen;
  HBRUSH OldBrush;
  // Zeichnen des Rahmens
  /////////////////////////
  OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
  RECT rcToPaint;
  CopyRect (&rcToPaint,LPRECT(&rcPaint));
  OffsetRect (LPRECT (&rcToPaint),0,(rcPaint.top - ToolRect.top) / 2);
  if (Style < 2) {
    OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    MyRectangle (hDC, rcToPaint.left, rcToPaint.top, rcToPaint.right, rcToPaint.bottom);
    SelectObject (hDC, OldPen);
    }

  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  switch (Style) {
    case 0:
      MyRectangle (hDC, rcToPaint.left-1, rcToPaint.top-1, rcToPaint.right-1, rcToPaint.bottom-1);
      break;
    case 1:
      MoveToEx (hDC, rcToPaint.left, rcToPaint.bottom-1, NULL);
      LineTo (hDC, rcToPaint.left, rcToPaint.top);
      LineTo (hDC, rcToPaint.right-1, rcToPaint.top);
      break;
    case 2:
    default:

      MyDrawEdge (hDC, LPRECT(&rcToPaint), MY_EDGE_HWND, MY_BF_RECT);
      break;
    }

  DeleteObject (SelectObject (hDC, OldPen));
  SelectObject (hDC, OldBrush);
  // Fuellen
  //////////
  if (DrawBkGround) {
    OldPen = (HPEN)SelectObject (hDC,GetStockObject(NULL_PEN));
    HBRUSH hbr = CreateSolidBrush (Color);
    OldBrush = (HBRUSH)SelectObject(hDC,hbr);

    switch (Style) {
      case 0:
        MyFillRectangle (hDC,rcToPaint.left+2, rcToPaint.top+1, rcToPaint.right-2, rcToPaint.bottom-2);
        break;

      case 1:
        MyFillRectangle (hDC,rcToPaint.left+2, rcToPaint.top+1, rcToPaint.right-1, rcToPaint.bottom-1);
        break;

      case 2:
        {
        RECT rc;
        CopyRect (&rc, LPRECT(&rcToPaint));
        InflateRect (&rc, -2, -2);
        rc.bottom += 1;

        COLORREF OldBack = SetBkColor (hDC, Color);
        ExtTextOut (hDC, rc.left, rc.top, ETO_OPAQUE, &rc, NULL, 0, NULL);
        SetBkColor (hDC, OldBack);
        }
        break;
      }

    SelectObject (hDC,OldBrush);
    DeleteObject (hbr);
    SelectObject (hDC,OldPen);
    }
  // Zeichnen des Textes
  ///////////////////////
  StaticTool::PaintTool (hDC,hmemDC);
  }

/*****************************************************************************\
*                                                                             *
*        3D - Linie                                                           *
*                                                                             *
\*****************************************************************************/
void Line3D::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->_x1, StructData);
  (* SetConnection) (privData, Param()->_y1, StructData);
  }

BOOL Line3D::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL)
    return (PtInRect(LPRECT(&ToolRect), *pt));
  else
    return FALSE ;
  }

void Line3D::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  X0 = ToDevKoordX(tx);
  Y0 = ToDevKoordY(ty, Parent->Layer);
  X1 = ToDevKoordX(tx1);
  Y1 = ToDevKoordY(ty1, Parent->Layer);

  SetRect (LPRECT (&ToolRect), X0, Y0, X1, Y1);
  if (ToolRect.right < ToolRect.left)
    ExChange (ToolRect.left, ToolRect.right);
  if (ToolRect.bottom < ToolRect.top)
    ExChange (ToolRect.bottom, ToolRect.top);
  InflateRect (LPRECT(&ToolRect), 3, 3);


  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty1));
  }

void Line3D::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }

void Line3D::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lptx1 = (DBINT FAR *)(* GetData) (privData, Param()->_x1);
  DBINT FAR *lpty1 = (DBINT FAR *)(* GetData) (privData, Param()->_y1);

  DBWIN_ASSERT ((lptx1 != NULL) && (lpty1 != NULL));
  
  tx1 = *lptx1;
  ty1 = *lpty1;
  
  GetRect ();
  }

void Line3D::MoveTool ()
  {
  int y0 = Gety0 ();
  int y1 = ToDevKoordY (ty1, Parent->Layer);
  int y = min(y0, y1);
  int dy = y - (ToolRect.top + 3);
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Y0 += dy;
    Y1 += dy;
    Invalidate (FALSE);
    }
  }

void Line3D::PaintTool (HDC hDC, HDC hMemDC)
  {
  HPEN OldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, X0, Y0,NULL);
  LineTo (hDC, X1, Y1);
  DeleteObject (SelectObject (hDC, OldPen));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject (WHITE_PEN));
  if (X0 == X1) {
    MoveToEx (hDC, X0+1, Y0,NULL);
    LineTo (hDC, X1+1, Y1);
    }
  else {
    MoveToEx (hDC, X0, Y0+1,NULL);
    LineTo (hDC, X1, Y1+1);
    }  

  SelectObject (hDC, OldPen);
  }



void Line3D::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);
  (* ClearConnection) (privData, Param()->_x1, StructData);
  (* ClearConnection) (privData, Param()->_y1, StructData);
  }



/*****************************************************************************\
*                                                                             *
*        faerbige - Linie                                                     *
*                                                                             *
\*****************************************************************************/
void LineTool::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Style, StructData);
  (* SetConnection) (privData,Param()->hd._x, StructData);
  (* SetConnection) (privData,Param()->hd._y, StructData);
  (* SetConnection) (privData,Param()->_x1, StructData);
  (* SetConnection) (privData,Param()->_y1, StructData);
  }

BOOL LineTool::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL)
    return (PtInRect(LPRECT(&ToolRect), *pt));
  else
    return FALSE ;
  }

void LineTool::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  X0 = ToDevKoordX(tx);
  Y0 = ToDevKoordY(ty, Parent->Layer);
  X1 = ToDevKoordX(tx1);
  Y1 = ToDevKoordY(ty1);

  SetRect (LPRECT (&ToolRect), X0, Y0, X1, Y1);
  if (ToolRect.right < ToolRect.left)
    ExChange(ToolRect.left,ToolRect.right);
  if (ToolRect.bottom < ToolRect.top)
    ExChange(ToolRect.bottom,ToolRect.top);
  InflateRect (LPRECT(&ToolRect), max(3,LineWidth/2+1), max(3,LineWidth/2+1));

  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty1));
  }

void LineTool::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }

void LineTool::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lptx1 = (DBINT FAR *)(* GetData)(privData, Param()->_x1);
  DBINT FAR *lpty1 = (DBINT FAR *)(* GetData)(privData, Param()->_y1);
  
  DBWIN_ASSERT ((lptx1 != NULL) && (lpty1 != NULL));

  tx1 = *lptx1;
  ty1 = *lpty1;

  DWORD FAR* lpStyle = (DWORD FAR*)(* GetData) (privData,Param()->Style);

  // wenn keine Daten gelesen werden, wird eine schwarze Linie
  // mit der StrichstÑrke 0 und dem Attribut PS_SOLID gezeichnet!
  LONG LineAttr = (lpStyle != NULL) ? *lpStyle : 0;

  LineColor = LineAttr & 0x00FFFFFF;
  int Width = int((LineAttr & 0x0F000000) >> 24);
  LineStyle = int((LineAttr & 0xF0000000) >> 28);
  
  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  mapFact = double (GetDeviceCaps(hDC, LOGPIXELSX)/1440.0);
  LineWidth = (Width*(GetDeviceCaps(hDC, LOGPIXELSX))/72);
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);

  // Das Handle fuer den Stift wird hier erzeugt
  if (PenHandle != 0)
    DeleteObject (PenHandle);
  PenHandle = CreatePen (PS_SOLID, LineWidth, LineColor);

  // ACHTUNG: GetRect wird erst hier aufgerufen, da die Liniendicke fÅr
  // das <ToolRect> ausschlaggebend ist !!!
  GetRect ();
  }

void LineTool::Update ()
  {
  Invalidate (TRUE);
  Load (); 
  Invalidate (FALSE);
  }

void LineTool::MoveTool ()
  {
  int y0 = Gety0 ();
  int y1 = ToDevKoordY(ty1, Parent->Layer) ;
  int y = min(y0,y1);
  // int dy = y - (ToolRect.top + max(3,LineWidth/2+1));
  int dy = y - Y0;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Y0 += dy ;
    Y1 += dy ;
    Invalidate (FALSE);
    }
  }

void LineTool::PaintTool (HDC hDC, HDC hMemDC)
  {
  HPEN OldPen = (HPEN)SelectObject(hDC, PenHandle);
  MyMoveTo (hDC, X0, Y0);
  MyLineTo (hDC, X1, Y1,mapFact,LineStyle,LineWidth);
  SelectObject (hDC, OldPen);
  }



void LineTool::Reset (BOOL doClear)
  {
  if (PenHandle != 0)
    DeleteObject (PenHandle);
  PenHandle = 0;
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Style, StructData);

  (* ClearConnection) (privData,Param()->hd._x, StructData);
  (* ClearConnection) (privData,Param()->hd._y, StructData);
  (* ClearConnection) (privData,Param()->_x1, StructData);
  (* ClearConnection) (privData,Param()->_y1, StructData);
  }


