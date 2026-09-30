////////////////////////////////////////////////////////////
//
//      Zeichnen des Namens neben dem Mousecursor
//
//      $Header:   P:/marille/clinicum/frmobj/rev/namfld.cpv   1.2   05 Oct 1998 11:22:14   Gerhold  $
//      $Log:   P:/marille/clinicum/frmobj/rev/namfld.cpv  $
// 
//    Rev 1.2   05 Oct 1998 11:22:14   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.1   02 Feb 1996 10:49:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:45:46   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.5   14 Dec 1992 18:23:08   HANNES
// Rueckgabe bei Clear, ob vorher gezeichnet wurde
// 
//    Rev 1.4   07 Dec 1992 14:19:38   HANNES
// WM_MOUSEMOVE auf Koordinaten < 0 abgefangen
// 
//    Rev 1.3   06 Dec 1992 18:56:24   HANNES
// Berechnung der Namensposition (Umsetzten auf rechts, wenns links nicht
// geht, sonst kein vernuenftiget Blit..)
//
////////////////////////////////////////////////////////////
#include <windows.h>
#include "dds32.h"
#include "namfld.hpp"
#include "globmem.h"

void MouseName::CreateFont (HDC hDC)
  {
  if (hFnt == 0) {
    // Minimale Initialisierungen von lf. (10 Punkt Arial Bold)
    LOGFONT lf;
    lmemset (&lf,'\0',sizeof(lf));
    lf.lfHeight = - MulDiv (10,GetDeviceCaps (hDC,LOGPIXELSY),72);
    lf.lfWeight = FW_BOLD;
    lstrcpy (lf.lfFaceName,"Arial");
    hFnt = CreateFontIndirect (&lf);
    }
  SelectObject (hDC,hFnt);
  }

void MouseName::Create (HWND hWnd,LPSTR Name)
  {
  // Loeschen des alten Bildes (sicher ist sicher)
  Clear (hWnd);

  // Schirm - Kontext
  HDC hDisplay = GetDC (hWnd);

  // Altes Bitmap zerstoeren
  DeleteBitmaps ();

  // Erzeugen eines Memory - Kontextes
  HDC hMemDC = CreateMemDC (hDisplay);

  // Font und selektieren erzeugen
  CreateFont (hMemDC);

  // Abmessen des Namens
  HFONT hOldFont = (HFONT)SelectObject (hDisplay,hFnt);
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDisplay, Name, lstrlen(Name), &size);
#else
  DWORD dwext = GetTextExtent (hDisplay,Name,lstrlen(Name));
#endif  
  SelectObject (hDisplay,hOldFont);

  // Bitmap erzeugen
  int cx, cy;
#ifdef WIN32
  cx = size.cx;
  cy = size.cy;
#else
  cx = LOWORD(dwext);
  cy = HIWORD(dwext);
#endif

  CreateBitmaps (hMemDC,hDisplay,cx,cy);
  SelectBitmap (hMemDC);

  // Und los geht's
  SetTextAlign (hMemDC,TA_TOP | TA_LEFT);
  SetTextColor (hMemDC,RGB(255,255,255));
  SetBkColor (hMemDC,RGB(0,0,0));
  TextOut (hMemDC,0,0,Name,lstrlen(Name));

  // fertig
  DeleteDC (hMemDC);
  ReleaseDC (hWnd,hDisplay);
  }

void MouseName::ReadBk (HDC hDisplay,HDC hMemDC,int x,int y)
  {
  BITMAP bm;
  SelectBkBitmap (hMemDC);
  GetObject (hBkBitmap,sizeof(bm),&bm);
  BitBlt (hMemDC,0,0,bm.bmWidth,bm.bmHeight,
                   hDisplay,x,y,SRCCOPY
         );
  }

void MouseName::RestoreBk (HDC hDisplay,HDC hMemDC,int x,int y)
  {
  BITMAP bm;
  SelectBkBitmap (hMemDC);
  GetObject (hBkBitmap,sizeof(bm),&bm);
  BitBlt (hDisplay,x,y,bm.bmWidth,bm.bmHeight,
                   hMemDC,0,0,SRCCOPY
         );
  }

// Rausschreiben des Bitmaps auf der aktuellen Mouseposition
void MouseName::Blit (HDC hDisplay,HDC hMemDC,int x,int y)
  {
  BITMAP bm;
  SelectBitmap (hMemDC);
  GetObject (hBitmap,sizeof(bm),&bm);
  HBRUSH hBr = (HBRUSH)CreateSolidBrush (RGB(255,0,0));
  HBRUSH hOldBrush = (HBRUSH)SelectObject (hDisplay,hBr);
  BitBlt (hDisplay,x,y,bm.bmWidth,bm.bmHeight,
                   hMemDC,0,0,0x00E20746
         );
  SelectObject (hDisplay,hOldBrush);
  DeleteObject (hBr);
  }

void MouseName::GetWrPos (HWND hWnd,POINT &pt)
  {
  BITMAP bm;
  RECT r;
  GetObject (hBitmap,sizeof(BITMAP),&bm);
  GetClientRect (hWnd,&r);
  if (pt.x + bm.bmWidth + NF_XOFF < r.right)
    pt.x += NF_XOFF ;   // rechts vom Cursor
  else if (pt.x - NF_XOFF - bm.bmWidth > 1)
    pt.x -= NF_XOFF + bm.bmWidth ;
  else
    pt.x += NF_XOFF ;   // rechts vom Cursor, das links nicht platz hat
  if (pt.y + bm.bmHeight < r.bottom)
    pt.y += NF_YOFF ;   // unter dem Cursor
  else
    pt.y -= NF_YOFF + bm.bmHeight ;
  }

void MouseName::Show (HWND hWnd)
  {
  if (hBitmap) {
    HDC hDisplay = GetDC (hWnd);
    HDC hMemDC = CreateMemDC (hDisplay);
    POINT mpos;
  
    if (xold >= 0)
      RestoreBk (hDisplay,hMemDC,xold,yold);
  
    GetCursorPos (&mpos);
    ScreenToClient (hWnd,&mpos);
  
    GetWrPos (hWnd,mpos);
    xold = mpos.x ;
    yold = mpos.y ;
    if ((xold >= 0) && (yold >= 0)) {
      ReadBk (hDisplay,hMemDC,xold,yold);
      Blit (hDisplay,hMemDC,xold,yold);
      }
    else
      xold = -1;

    ReleaseDC (hWnd,hDisplay);
    DeleteDC (hMemDC);
    }
  }

BOOL MouseName::Clear (HWND hWnd)
  {
  BOOL res ;
  if ((xold >= 0) && (hBitmap)) {
    HDC hDisplay = GetDC (hWnd);
    HDC hMemDC = CreateMemDC (hDisplay);

    RestoreBk (hDisplay,hMemDC,xold,yold);
  
    ReleaseDC (hWnd,hDisplay);
    DeleteDC (hMemDC);
    res = TRUE ;
    }
  else
    res = FALSE ;
  xold = yold = -1 ;
  return res ;
  }
