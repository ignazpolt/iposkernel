//---------------------------------------------------------------------------
// Icons, die wie im Programm-Manager in einem Fenster angeordnet sind.
//---------------------------------------------------------------------------
//      $Header:   P:/marille/clinicum/ctool/rev/icontool.cpv   1.22   05 Oct 1998 11:06:44   Gerhold  $
//      $Log:   P:/marille/clinicum/ctool/rev/icontool.cpv  $
// 
//    Rev 1.22   05 Oct 1998 11:06:44   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.21   24 Feb 1998 19:45:42   Hannes
// ToDevKoord...
// 
//    Rev 1.20   24 Mar 1996 12:10:16   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.19   02 Feb 1996 10:42:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.18   16 Jan 1996 15:01:00   GERHOLD
// Sollte beim Ermitteln der Icon-Positionen die Icon-Liste noch nicht erzeugt
// worden sein, dann wird ::Arrange zu einem spaeteren Zeitpunkt erzwungen!
// ---------------------------------------------------------------------------
// Beginn der Portierung auf 32 Bit
// ---------------------------------------------------------------------------
// 
//    Rev 1.17   12 Sep 1995 13:30:56   GERHOLD
// SetFocus in WM_LBUTTONDOWN wird erst nach Find aufgerufen
// 
//    Rev 1.16   11 Sep 1995 10:39:52   GERHOLD
// ::Find prueft jetzt auf Bildhoehe + Texthoehe
// 
//    Rev 1.15   08 Sep 1995 15:47:26   GERHOLD
// 
//    Rev 1.14   06 Sep 1995 11:28:54   GERHOLD
// Bei Mausselektion "huepfen" die Icons nicht mehr so verrueckt
// 
//    Rev 1.13   24 Aug 1995 09:36:50   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.12   27 Jun 1995 13:53:18   HANNES
// DrawTransparentbitmap
// 
//    Rev 1.10   29 May 1995 08:50:42   GERHOLD
// 
//    Rev 1.9   27 Mar 1995 13:18:34   HANNES
//  
// 
//    Rev 1.8   20 Mar 1995 12:12:14   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.7   24 Feb 1995 11:04:20   GERHOLD
// Es gibt jetzt schon beim Start ein selektiertes Icon
//---------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "scripthd.hpp"
#include "icontool.hpp"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"
#include "toolbar.hpp"
#define INDLL
#define MODULENUM   148
#include "winass.hpp"


#define ELEFORMAT   2
#define FOLDERFORMAT 59


#define GROUP_IN_LINE  4
#define XBORDER       10
#define YBORDER       10
#define FLAPHEIGHT    24

#ifdef UEBERLEGT
static HBRUSH FolderBrush;
#endif


static BOOL bForceArrange = FALSE;

class FAR iwo {
 public :
  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };


#define ICONELE_BITMAP  0
#define ICONELE_ICON    1

class IconFolder ;
class IconEle : public ActionElem {
 public :
  LPICONELEDATA  eledata;
  cField         *field;
  IconEle FAR    *Next;
  int             cx, cy;
  int             TextHeight;
  LPSTR           txt;
  int             type;
  int             x, y;
  IconFolder FAR *Parent;

  HWND hWndFolder;
  union FAR {
    LPBITMAPINFO lpbi;
    HICON hico;
    } pict;

  IconEle (HWND hWnd,IconFolder FAR *w,LPSTR t, LPBITMAPINFO lpi,LPICONELEDATA ele);
  IconEle (HWND hWnd,IconFolder FAR *w,LPSTR t, HICON ico,LPICONELEDATA ele);
  ~IconEle ()
    { if (field != NULL) delete field ; 
      if (type == ICONELE_BITMAP) FreeGlobMem (pict.lpbi) ; 
      if (eledata != NULL) FreeGlobMem (eledata);
    }

  int          GetPictHeight ();
  int          GetPictWidth ();
  void         GetSize(HDC hDC,HWND hWnd);
  void         Invalidate (BOOL fRedraw);
  virtual BOOL IsElemEnabled ()                 { return TRUE; }
  void         Notify();
  void         Paint (HDC hDC);
  };
typedef IconEle FAR* LPICONELE;

#define GWL_DATA  0

class IconFolder : public iwo {
 public :
  LPICONELE       iList;
  LPICONELE       Selected;
  LPICONELE       OldSelected;
  int             yPos;     // Position des vertikalen Scrollbars
  int             TotalHeight;
  int             ScrollMax;

  IconFolder ()  { iList = NULL; Selected = NULL; }
  ~IconFolder ();

  void         Add (HWND hWnd,LPSTR t,LPBITMAPINFO lpbi,LPICONELEDATA eledata);
  void         Add (HWND hWnd,LPSTR t,HICON hico,LPICONELEDATA eledata);

  void         Arrange (HWND hWnd);
  void         ChangeSelection (LPICONELE x);
  LPICONELE    GetIconEle (int Nr);
  LPICONELE    GetFirst ();
  int          GetIconNr (LPICONELE e);
  LPICONELE    GetLast ();
  LPICONELE    Find (int x,int y);
  int          GetGroupNmbr();
  int          LineNmbr (LPICONELE x);
  int          LineHeight (LPICONELE hb, LPICONELE he);
  int          LineWidth  (LPICONELE hb, LPICONELE he);
  void         NextDown ();
  void         NextLeft ();
  void         NextRight ();
  void         NextUp ();
  void         Paint (HDC hDC, RECT rcPaint);

  friend DLLExport LONG _export CALLBACK IconWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP);
  };


//Special ROP code for TransparentBlt.
#define ROP_DSPDxax  0x00E20746
/*
DLLExport void _export FAR PASCAL DrawTransparentBitmap (HDC hDC, HBITMAP hBmp, int XPos, int YPos, 
                                               int XStart, int YStart, int Width, int Height, COLORREF cr)
  {
  HDC         hDCSrc, hDCMid, hMemDC;
  HBITMAP     hBmpMono, hBmpT;
  HBRUSH      hBr, hBrT;
  COLORREF    crBack, crText;

  if (NULL==hBmp)
      return;

    //Get three intermediate DC's
    hDCSrc = CreateCompatibleDC(hDC);
    hDCMid = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);

    SelectObject(hDCSrc, hBmp);

    //Create a monochrome bitmap for masking
    hBmpMono = CreateCompatibleBitmap (hDCMid, Width, Height);
    SelectObject (hDCMid, hBmpMono);

    //Create a middle bitmap
    hBmpT = CreateCompatibleBitmap (hDC, Width, Height);
    SelectObject(hMemDC, hBmpT);

    //Create a monochrome mask where we have 0's in the image, 1's elsewhere.
    crBack = SetBkColor(hDCSrc, cr);
    BitBlt (hDCMid, 0, 0, Width, Height, hDCSrc, XStart, YStart, SRCCOPY);
    SetBkColor (hDCSrc, crBack);

    //Put the unmodified image in the temporary bitmap
    BitBlt(hMemDC, 0, 0, Width, Height, hDCSrc, XStart, YStart, SRCCOPY);

    //Create an select a brush of the background color
    hBr = CreateSolidBrush(GetBkColor(hDC));
    hBrT = SelectObject(hMemDC, hBr);

    //Force conversion of the monochrome to stay black and white.
    crText = SetTextColor(hMemDC, 0L);
    crBack = SetBkColor(hMemDC, RGB(255, 255, 255));

     * Where the monochrome mask is 1, Blt the brush; where the mono mask
     * is 0, leave the destination untouches.  This results in painting
     * around the image with the background brush.  We do this first
     * in the temporary bitmap, then put the whole thing to the screen.
    
    BitBlt (hMemDC, 0, 0, Width, Height, hDCMid, 0, 0, ROP_DSPDxax);
    BitBlt (hDC,    XPos, YPos, Width, Height, hMemDC, 0, 0, SRCCOPY);

    SetTextColor(hMemDC, crText);
    SetBkColor(hMemDC, crBack);

    SelectObject(hMemDC, hBrT);
    DeleteObject(hBr);

    DeleteDC(hMemDC);
    DeleteDC(hDCSrc);
    DeleteDC(hDCMid);
    DeleteObject(hBmpT);
    DeleteObject(hBmpMono);

    return;
  }
*/

DLLExport void _export WINAPI DrawTransparentBitmap (HDC hDC, HBITMAP hBmp, int XPos, int YPos, 
                                               int XStart, int YStart, int Width, int Height, COLORREF cr)
   {
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;

   hdcTemp = CreateCompatibleDC(hDC);
   SelectObject(hdcTemp, hBmp);   // Select the bitmap
   GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hDC);
   hdcObject = CreateCompatibleDC(hDC);
   hdcMem    = CreateCompatibleDC(hDC);
   hdcSave   = CreateCompatibleDC(hDC);
   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.
   // Monochrome DC
   bmAndBack   = CreateBitmap(Width, Height, 1, 1, NULL);
   // Monochrome DC
   bmAndObject = CreateBitmap(Width, Height, 1, 1, NULL);
   bmAndMem    = CreateCompatibleBitmap(hDC, Width, Height);
   bmSave      = CreateCompatibleBitmap(hDC, Width, Height);
   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, Width, Height, hdcTemp, XStart, YStart, SRCCOPY);
   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cr);
   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, Width, Height, hdcTemp, XStart, YStart,
          SRCCOPY);
   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);
   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, Width, Height, hdcObject, 0, 0,
          NOTSRCCOPY);
   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, Width, Height, hDC, XPos, YPos,
          SRCCOPY);
   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, Width, Height, hdcObject, 0, 0, SRCAND);
   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, XStart, YStart, Width, Height, hdcBack, 0, 0, SRCAND);
   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, Width, Height, hdcTemp, XStart, YStart, SRCPAINT);
   // Copy the destination to the screen.
   BitBlt(hDC, XPos, YPos, Width, Height, hdcMem, 0, 0,
          SRCCOPY);
//   BitBlt(hDC, XPos, YPos, Width, Height, hdcObject, 0, 0,
//          SRCCOPY);
          
   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, XStart, YStart, Width, Height, hdcSave, 0, 0, SRCCOPY);
   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));
   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
   }


DLLExport void _export WINAPI DrawTransparentBitmap (HDC hDC, LPBITMAPINFO bi, LPSTR lpbits, 
                                               int XPos, int YPos, COLORREF cr)
  {
  HDC         hDCSrc, hDCMid, hMemDC;
  HBITMAP     hBmpMono, hBmpT;
  HBRUSH      hBr, hBrT;
  COLORREF    crBack, crText;

  if (bi == NULL)
    return;

    //Get three intermediate DC's
  hDCSrc = CreateCompatibleDC(hDC);
  hDCMid = CreateCompatibleDC(hDC);
  hMemDC = CreateCompatibleDC(hDC);

  HBITMAP hBitmap = CreateDIBitmap (hDC, &bi->bmiHeader, CBM_INIT,
                                    lpbits, bi, DIB_RGB_COLORS);
  SelectObject (hDCSrc, hBitmap);

  int Width  = int(bi->bmiHeader.biWidth);            // Get width of bitmap
  int Height = int(bi->bmiHeader.biHeight);           // Get height of bitmap

  //Create a monochrome bitmap for masking
  hBmpMono = CreateCompatibleBitmap (hDCMid, Width, Height);
  SelectObject (hDCMid, hBmpMono);

  //Create a middle bitmap
  hBmpT = CreateCompatibleBitmap (hDC, Width, Height);
  SelectObject(hMemDC, hBmpT);

  //Create a monochrome mask where we have 0's in the image, 1's elsewhere.
  crBack = SetBkColor(hDCSrc, cr);
  BitBlt (hDCMid, 0, 0, Width, Height, hDCSrc, 0, 0, SRCCOPY);
  SetBkColor (hDCSrc, crBack);

  //Put the unmodified image in the temporary bitmap
  BitBlt(hMemDC, 0, 0, Width, Height, hDCSrc, 0, 0, SRCCOPY);

  //Create an select a brush of the background color
  hBr = CreateSolidBrush(GetBkColor(hDC));
  hBrT = (HBRUSH)SelectObject(hMemDC, hBr);

  //Force conversion of the monochrome to stay black and white.
  crText = SetTextColor(hMemDC, 0L);
  crBack = SetBkColor(hMemDC, RGB(255, 255, 255));

  /*
   * Where the monochrome mask is 1, Blt the brush; where the mono mask
   * is 0, leave the destination untouches.  This results in painting
   * around the image with the background brush.  We do this first
   * in the temporary bitmap, then put the whole thing to the screen.
   */
  BitBlt (hMemDC, 0, 0, Width, Height, hDCMid, 0, 0, ROP_DSPDxax);
  BitBlt (hDC,    XPos, YPos, Width, Height, hMemDC, 0, 0, SRCCOPY);

  SetTextColor(hMemDC, crText);
  SetBkColor(hMemDC, crBack);

  SelectObject(hMemDC, hBrT);
  DeleteObject(hBr);

  DeleteDC(hMemDC);
  DeleteDC(hDCSrc);
  DeleteDC(hDCMid);
  DeleteObject(hBmpT);
  DeleteObject(hBmpMono);

  DeleteObject (hBitmap);

  return;
  }






/////////////////////////////////////////////////////////////////////////
//  Icon - Element
/////////////////////////////////////////////////////////////////////////
void SetMMText (HDC hDC,int y = 0)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void SetTwips (HDC hDC,int x = 0,int y = 0)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440, NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,x,y, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }


inline int XtoDEV (HDC hDC,int x)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = x ;
  pt[1].y = 0 ;
  LPtoDP (hDC,pt,2);
  return pt[1].x - pt[0].x;
  }

inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = x ;
  pt[1].y = 0 ;
  DPtoLP (hDC,pt,2);
  return pt[1].x - pt[0].x;
  }

inline int YtoDEV (HDC hDC,int y)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = 0 ;
  pt[1].y = y ;
  LPtoDP (hDC,pt,2);
  return pt[1].y - pt[0].y;
  }

WORD DIBNumColors (LPSTR pv)
  {
  int bits;
  LPBITMAPINFOHEADER lpbi;
  LPBITMAPCOREHEADER lpbc;

  lpbi = ((LPBITMAPINFOHEADER)pv);     // assume win 3.0 style DIBs
  lpbc = ((LPBITMAPCOREHEADER)pv);     // assume OS/2 style DIBs

  // With the BITMAPINFO format headers, the size of the palette
  // is in biClrUsed, whereas in the BITMAPCORE - style headers, it
  // is dependent on the bits per pixel ( = 2 raised to the power of
  // bits/pixel).

  if (lpbi->biSize != sizeof(BITMAPCOREHEADER)) {
    if (lpbi->biClrUsed != 0)
      return (WORD)lpbi->biClrUsed;
    bits = lpbi->biBitCount;
    }
  else
    bits = lpbc->bcBitCount;

  switch (bits) {
    case 1:
      return 2;
    case 4:
      return 16;
    case 8:
      return 256;
    default:
      // A 24 bitcount DIB has no color table
      return 0;
    }
  }

WORD PaletteSize (LPSTR pv)
  {
  LPBITMAPINFOHEADER lpbi;
  WORD NumColors;

  lpbi = (LPBITMAPINFOHEADER)pv;
  NumColors = DIBNumColors((LPSTR)lpbi);

  if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
     return NumColors * sizeof(RGBTRIPLE);
  else
     return NumColors * sizeof(RGBQUAD);
  }

#define WIDTHBYTES(i)   ((i+31)/32*4)      /* ULONG aligned ! */
IconEle::IconEle (HWND hWnd,IconFolder FAR *w,LPSTR t, LPBITMAPINFO lpbi,LPICONELEDATA ele)
  { 
  Parent = w; 
  txt = t; 
  hWndFolder = hWnd;
  if (lpbi->bmiHeader.biSizeImage == 0L)
      lpbi->bmiHeader.biSizeImage = 
            WIDTHBYTES(lpbi->bmiHeader.biWidth * lpbi->bmiHeader.biBitCount) *
                                     (lpbi->bmiHeader.biHeight / 2);

  int size = int (*(LPDWORD)lpbi) + int (PaletteSize((LPSTR)lpbi)) + 
              int (lpbi->bmiHeader.biSizeImage);
  pict.lpbi = LPBITMAPINFO (GetGlobMem (size));
  lmemcpy (pict.lpbi,lpbi,size);
  eledata = LPICONELEDATA (GetGlobMem (sizeof(*eledata)));
  *eledata = *ele; 
  type = ICONELE_BITMAP; 
  }


IconEle::IconEle (HWND hWnd,IconFolder FAR *w,LPSTR t, HICON ico,LPICONELEDATA ele)
  { 
  Parent = w; 
  txt = t; 
  hWndFolder = hWnd;
  pict.hico = ico;  
  eledata = LPICONELEDATA (GetGlobMem (sizeof(*eledata)));
  *eledata = *ele; 
  type = ICONELE_ICON; 
  }


#define XSPACE    2
#define YSPACE    2

/*--------------------------------------------------------------------*\
* member function:  GetPictWidth                                       *
*                                                                      *
\*--------------------------------------------------------------------*/
int IconEle::GetPictWidth ()
  {
  if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL))
    return int(pict.lpbi->bmiHeader.biWidth);
  else if ((type == ICONELE_ICON) && (pict.hico))
    return GetSystemMetrics (SM_CXICON);
  else
    return 32;
  }

/*--------------------------------------------------------------------*\
* member function:  GetPictHeight                                      *
*                                                                      *
\*--------------------------------------------------------------------*/
int IconEle::GetPictHeight ()
  {
  if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL))
    return int(pict.lpbi->bmiHeader.biHeight / 2);
  else if ((type == ICONELE_ICON) && (pict.hico))
    return GetSystemMetrics (SM_CXICON);
  else
    return 32;
  }

/*--------------------------------------------------------------------*\
* member function:  GetSize                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconEle::GetSize (HDC hDC,HWND hWnd)
  {
  int x = GetSystemMetrics (SM_CXICONSPACING) + 4 * XSPACE;
  SetTwips (hDC);
  field = new cField (TRANSPARENT,FOLDERFORMAT,0,0,XtoLOG(hDC,x),-1,FALSE);
  field->SetWindow (hWnd);
  field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  field->SetVOrg (0,0,0);
  *field = txt;
  field->Reformat ();
  RECT Textr;
  field->GetFieldRect (&Textr,0);
  TextHeight = YtoDEV (hDC,Textr.bottom);

  cx = GetSystemMetrics (SM_CXICONSPACING) + 6 * XSPACE ;
  cy = GetSystemMetrics (SM_CXICONSPACING) ;
  SetMMText (hDC);
  }

void ScrollRightFor (int x);
void ScrollLeftFor (int x);


/*--------------------------------------------------------------------*\
* member function:  Paint                                              *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconEle::Paint (HDC hDC)
  {
  RECT rt;
  rt.left = x + XSPACE / 2 ;
  rt.top  = y + YSPACE + GetPictHeight() + 1 - Parent->yPos;
  rt.right = x + cx - XSPACE / 2;
  rt.bottom = rt.top + TextHeight + 1;
    
  if (Parent->Selected == this) {
    COLORREF OldBack;
    COLORREF TextColor;
    if (GetFocus() == hWndFolder) {
      OldBack = SetBkColor (hDC, GetSysColor (COLOR_HIGHLIGHT));
      TextColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
      }
    else {
      OldBack = SetBkColor (hDC, GetSysColor (COLOR_BTNFACE));
      TextColor = GetSysColor(COLOR_BTNTEXT);
      }

    ExtTextOut (hDC, rt.left, rt.top, ETO_OPAQUE, &rt, NULL, 0, NULL);
    SetBkColor (hDC, OldBack);
      
    SetTwips (hDC, x + XSPACE, y + GetPictHeight() + 1 + YSPACE - Parent->yPos);
    field->SetOutColor (TextColor);
    field->Paint (hDC, 0, FALSE);
    field->UseDefOutColor();
    }
  else {
#ifdef WIN32
    HBRUSH BkBrush = HBRUSH(GetClassLong (hWndFolder, GCL_HBRBACKGROUND));
#else
    HBRUSH BkBrush = HBRUSH(GetClassWord (hWndFolder, GCW_HBRBACKGROUND));
#endif
    HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, BkBrush);
    PatBlt (hDC, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top, PATCOPY);
    SelectObject (hDC, OldBrush);

    SetTwips (hDC, x + XSPACE, y + GetPictHeight() + 1 + YSPACE - Parent->yPos);
    field->Paint (hDC, 0, FALSE);
    }

  SetMMText (hDC, -Parent->yPos);

  RECT r;
  r.top = YSPACE - Parent->yPos;
  r.left = (cx - 32) / 2;
  r.right = r.left + GetPictWidth() ;
  r.bottom = r.top + GetPictHeight() ;

  if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL)) {
    int pw = GetPictWidth();
    int ph = GetPictHeight();
    pict.lpbi->bmiHeader.biHeight /= 2;
    LPSTR bits = LPSTR(pict.lpbi) + *(LPDWORD)pict.lpbi + PaletteSize((LPSTR)pict.lpbi);

    DrawTransparentBitmap (hDC, pict.lpbi, bits, r.left+x, r.top+y, RGB(255, 0, 255));

    pict.lpbi->bmiHeader.biHeight *= 2;
    }
  else if ((type == ICONELE_ICON) && (pict.hico)) {
    DrawIcon (hDC,r.left + x,r.top + y,pict.hico);
    }
  else {
    MoveToEx (hDC,r.left + x,r.top + y, NULL);
    LineTo (hDC,r.right + x,r.top + y);
    LineTo (hDC,r.right + x,r.bottom + y);
    LineTo (hDC,r.left + x,r.bottom + y);
    LineTo (hDC,r.left + x,r.top + y);

    MoveToEx (hDC,r.left + x,r.top + y, NULL);
    LineTo (hDC,r.right + x,r.bottom + y);
    MoveToEx (hDC,r.right + x,r.top + y, NULL);
    LineTo (hDC,r.left + x,r.bottom + y);
    }
  }

/*--------------------------------------------------------------------*\
* member function:  Invalidate                                         *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconEle::Invalidate (BOOL fRedraw)
  {
  RECT r, rcClient;

  GetClientRect (hWndFolder, &rcClient);
  r.left = x;
  r.top = y - Parent->yPos ;
  r.right = x + cx ;
//  r.bottom = r.top + cy ;
  r.bottom = r.top + GetPictHeight() + 2 + YSPACE + TextHeight ;

  if (fRedraw) {
    InvalidateRect (hWndFolder, &r, fRedraw);
    UpdateWindow (hWndFolder);
    }

  if (Parent->Selected == this) {
    // Ist nicht das ganze Element sichtbar, dann muss man's ein bisserl
    // raufschieben!
    if ((r.bottom) > (rcClient.bottom-rcClient.top)) {
      int Delta = r.bottom - (rcClient.bottom-rcClient.top);  // wieviel?
      // die neuen Koordinaten invalidieren
      OffsetRect (&r, 0, -Delta);
      InvalidateRect (hWndFolder, &r, fRedraw);
  
      SendMessage (hWndFolder, WM_VSCROLL, SB_THUMBTRACK, 
                   MAKELONG(Delta+Parent->yPos, 0));
      } 
    // wie oben, nur das es 'runter geschoben wird!
    else if (r.top < (rcClient.top+20)) {
      int Delta = r.top - (rcClient.top+20);
      OffsetRect (&r, 0, -Delta);
      InvalidateRect (hWndFolder, &r, fRedraw);
  
      SendMessage (hWndFolder, WM_VSCROLL, SB_THUMBTRACK, 
                   MAKELONG(Delta+Parent->yPos, 0));
      } 
    else
      InvalidateRect (hWndFolder, &r, fRedraw);
    }
  else
    InvalidateRect (hWndFolder, &r, fRedraw);
    
  }

/*--------------------------------------------------------------------*\
* member function:  Notify                                             *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconEle::Notify()
  {
  (* eledata->cbFunc) (eledata,ICN_DOEXCUTE);
  }

static HCURSOR ArrowCursor;

static int IcnCloseWidth,IcnCloseHeight;

#define SCROLLHEIGHT  20
DLLExport LONG _export CALLBACK IconWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  IconFolder FAR *folder = (IconFolder FAR *) GetWindowLong (hWnd,GWL_DATA);
  switch (msg) {
    case WM_PAINT :
      {
      PAINTSTRUCT PS;

      // Die Groesse der Icons wurde noch nicht berechnet;
      // jetzt ist der beste Zeitpunkt
      if (bForceArrange)
        folder->Arrange (hWnd);

      HDC hDC = BeginPaint (hWnd, &PS);
      folder->Paint (hDC, PS.rcPaint);
      EndPaint (hWnd, &PS);
      }
      break ;

    case WM_SETFOCUS :
      if (folder->Selected == NULL)
        folder->Selected = folder->iList;

      folder->ChangeSelection (folder->Selected);

      if (folder->Selected != NULL)
        folder->Selected->Invalidate (FALSE);
      break ;
    
    case WM_KILLFOCUS :
      if (folder->Selected != NULL)
        folder->Selected->Invalidate (FALSE);
      break;
    
    case WM_LBUTTONDOWN :
      {
      LPICONELE e = folder->Find (LOWORD(lP),HIWORD(lP));
      if (e != NULL) {
        folder->ChangeSelection (e);
        }

      if (GetFocus () != hWnd)
        SetFocus (hWnd);
      }  
      break ;

    case WM_LBUTTONDBLCLK :
      {
      LPICONELE e = folder->Find (LOWORD(lP),HIWORD(lP));
      if (e != NULL)
        e->Notify();
      }
      break ;

    //------------------------------------------------------------------
    // yPos .......... Bereich um den das Fenster gescrollt ist
    // ScrollMax ..... die Groesse des Bereiches ausserhalb des Clients
    // TotalHeight ... der gesamte Bereich ueber den gescrollt wird
    // ScrollIncr .... Anzahl Pixel um die gescrollt wird
    //------------------------------------------------------------------
    case WM_VSCROLL :
      {
      int ScrollIncr = 0;
      switch (wP) {
        case SB_TOP:
          ScrollIncr = -folder->yPos;
          break;
        case SB_BOTTOM:
          ScrollIncr = folder->ScrollMax-folder->yPos;
          break;
        case SB_LINEUP:
          ScrollIncr = -SCROLLHEIGHT;
          break;
        case SB_LINEDOWN:
          ScrollIncr = SCROLLHEIGHT;
          break;
        case SB_PAGEUP:
          ScrollIncr = min(-SCROLLHEIGHT, -(folder->TotalHeight-folder->ScrollMax));
          break;
        case SB_PAGEDOWN:
          ScrollIncr = max(SCROLLHEIGHT, folder->TotalHeight-folder->ScrollMax);
          break;
        case SB_THUMBTRACK:
          ScrollIncr = int(LOWORD(lP))-folder->yPos;
          break;
        default:
          ScrollIncr = 0;
        }

      if (ScrollIncr = max(-folder->yPos, min(ScrollIncr, folder->ScrollMax-folder->yPos))) {
        folder->yPos += ScrollIncr;
        ScrollWindow (hWnd, 0, -ScrollIncr, NULL, NULL);
        SetScrollPos (hWnd, SB_VERT, folder->yPos, TRUE);
        UpdateWindow (hWnd);
        }

      }
      break;

    case WM_KEYDOWN :
      switch (wP) {
        case VK_LEFT :
          if (folder->Selected != NULL)
            folder->NextLeft ();
          else
            folder->ChangeSelection (folder->GetLast());
          break ;
        case VK_RIGHT :
          if (folder->Selected != NULL)
            folder->NextRight();
          else
            folder->ChangeSelection (folder->GetFirst());
          break ;
        case VK_UP :
          if (folder->Selected != NULL)
            folder->NextUp ();
          else
            folder->ChangeSelection (folder->GetFirst());
          break ;
        case VK_DOWN :
          if (folder->Selected != NULL)
            folder->NextDown ();
          else
            folder->ChangeSelection (folder->GetLast());
          break ;
        case VK_RETURN :
          if (folder->Selected != NULL)
            folder->Selected->Notify ();
          else
            MessageBeep (0);
          break ;
        // ACHTUNG: SCHWEINEREI! DDSLIST_TABPRESSED wird hier verwendet (von Gerhold)
        case VK_TAB:
          {
          HILOCHUNK hilo;
          MAKECHUNKsc (hilo, 0, DDSLIST_TABPRESSED)

          SendMessage (GetParent (hWnd),WM_COMMAND,0,HILOCHUNKPARAM(hilo));
/*          
          SendMessage (GetParent (hWnd),WM_COMMAND,0,MAKELONG(0,DDSLIST_TABPRESSED));
*/
          }
          break;
        }
      break ;

    case WM_DESTROY :
      delete folder ;
      break ;

    default:
      return (DefWindowProc(hWnd, msg, wP, lP));
    }
  return 0L;
  }

int IconFolder::GetIconNr (LPICONELE e)
  {
  int res = 0;
  for (LPICONELE x = iList; x != NULL; x = x->Next, res++) {
    if (x == e)
      break;
    }
  
  return res;
  }

LPICONELE IconFolder::GetIconEle (int Nr)
  {
  int res = 0;
  for (LPICONELE x = iList; x != NULL; x = x->Next) {
    if (Nr == res)
      break;
    res++;
    }
  return x;
  }

/*--------------------------------------------------------------------*\
* member function:  GetFirst                                           *
*                                                                      *
\*--------------------------------------------------------------------*/
LPICONELE IconFolder::GetFirst ()
  {
  return iList;
  }

/*--------------------------------------------------------------------*\
* member function:  GetLast                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
LPICONELE IconFolder::GetLast ()
  {
  for (LPICONELE e = iList; e->Next != NULL; e = e->Next);
  return e;
  }

/*--------------------------------------------------------------------*\
* member function:  LineNmbr                                           *
*                                                                      *
* Rueckgabewert:  Zeilennummer in der sich das Element befindet.       *
\*--------------------------------------------------------------------*/
int IconFolder::LineNmbr (LPICONELE x)
  {
  int res = -1 ;
  int yold = -1;
  for (LPICONELE h = iList ; h != NULL ; h = h->Next) {
    if (h->y != yold) {            // schon in der naechsten Zeile?
      res ++ ;                     // ja, erhoehe den Zeilenzaehler
      yold = h->y;
      }
    if (h == x) break ;
    }

  return res;
  }

/*--------------------------------------------------------------------*\
* member function:  NextLeft                                           *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::NextLeft ()
  {
  int lSoll = LineNmbr(Selected);
  LPICONELE best = NULL ;
  int xbest = 3200;
  for ( LPICONELE x = iList ; x != NULL ; x = x->Next) {
    if ((Selected != x) && (LineNmbr(x) == lSoll) &&
        (x->x < Selected->x) && ((Selected->x - x->x) < xbest))
      xbest = Selected->x - x->x , best = x;
    }
  if (best != NULL)
    ChangeSelection(best);
  }

/*--------------------------------------------------------------------*\
* member function:  NextRight                                          *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::NextRight ()
  {
  int lSoll = LineNmbr(Selected);
  LPICONELE best = NULL ;
  int xbest = 3200;
  for ( LPICONELE x = iList ; x != NULL ; x = x->Next) {
    if ((Selected != x) && (LineNmbr(x) == lSoll) &&
          (x->x > Selected->x) && ((x->x - Selected->x) < xbest))
              xbest = x->x - Selected->x , best = x;
    }
  if (best != NULL)
    ChangeSelection(best);
  }

/*--------------------------------------------------------------------*\
* member function:  NextUp                                             *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::NextUp ()
  {
  int lSoll = LineNmbr(Selected) - 1;
  LPICONELE best = NULL ;
  int xbest = 3200;
  int x0 = Selected->x + Selected->cx / 2 ;
  for ( LPICONELE x = iList ; x != NULL ; x = x->Next) {
    int x1 = x->x + x->cx / 2 ;
    int dx = x1 - x0 ;
    if (dx < 0) dx = -dx ;
    if ((Selected != x) && (LineNmbr(x) == lSoll) && (dx < xbest))
                xbest = dx , best = x;
    }
  if (best != NULL)
    ChangeSelection(best);

  }

/*--------------------------------------------------------------------*\
* member function:  NextDown                                           *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::NextDown ()
  {
  int lSoll = LineNmbr(Selected) + 1;          // Nr. der n„chsten Zeile
  LPICONELE best = NULL ;
  int xbest = 3200;
  int x0 = Selected->x + Selected->cx / 2 ;
  for ( LPICONELE x = iList ; x != NULL ; x = x->Next) {
    int x1 = x->x + x->cx / 2 ;
    int dx = x1 - x0 ;
    if (dx < 0) dx = -dx ;
    if ((Selected != x) && (LineNmbr(x) == lSoll) && (dx < xbest))
              xbest = dx , best = x;
    }
  if (best != NULL)
    ChangeSelection(best);
  }

/*--------------------------------------------------------------------*\
* member function:  ChangeSelection                                    *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::ChangeSelection (LPICONELE x)
  {
  if (x != Selected) {
    Selected = x;
    if (OldSelected != NULL)
      OldSelected->Invalidate (FALSE);  // vorher selektiertes loeschen
    if (x != NULL)
      x->Invalidate (FALSE);
    OldSelected = Selected;
    }
  }
 
/*--------------------------------------------------------------------*\
* member function:  Paint                                              *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::Paint (HDC hDC, RECT rcPaint)
  {
  RECT rc;

  // hier werden nur die Elemente gezeichnet, die in dem von PAINTSTRUCT
  // angegebenen Rechteck liegen!
  for (LPICONELE e = iList; e != NULL; e = e->Next) {
    SetRect (&rc, e->x, e->y - yPos, e->x + e-> cx, e->y + e->cy - yPos);
    if (IntersectRect(&rc, &rc, &rcPaint))
      e->Paint (hDC);
    }
  }


/*--------------------------------------------------------------------*\
* member function:  LineWidth                                          *
*                                                                      *
\*--------------------------------------------------------------------*/
int IconFolder::LineWidth (LPICONELE b,LPICONELE e)
  {
  int res = 0;
  for (LPICONELE h = b ; h != NULL ; h = h->Next) {
    res += h->cx ;
    if (h == e) break ;
    }
  return res;
  }

/*--------------------------------------------------------------------*\
* member function:  LineHeight                                         *
*                                                                      *
\*--------------------------------------------------------------------*/
int IconFolder::LineHeight (LPICONELE b,LPICONELE e)
  {
  int res = 0;
  for (LPICONELE h = b ; ((h != e) && (h != NULL)) ; h = h->Next) {
    if (h->cy > res) res = h->cy ;
    }
  return res;
  }

#define FIRST_OFSIDE  2
#define FIRST_OFLINE  0
#define NORMAL        1
/*--------------------------------------------------------------------*\
* member function:  Arrange                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
#define SPACING   15
void IconFolder::Arrange (HWND hWndFolder)
  {
  if (iList == NULL) {
    bForceArrange = TRUE;  // Es gibt noch keine Liste -> zu einem
                           // spaeteren Zeitpunkt aufrufen!!
    return;
    }
  else
    bForceArrange = FALSE;

  int LastHeight;
  RECT rc;
  GetClientRect (hWndFolder, &rc);
  InflateRect (&rc,-4,-10);
  // Berechnen aller Groessen
  HDC hDC = GetDC (hWndFolder);
  for (LPICONELE e = iList ; e != NULL ; e = e->Next)
    e->GetSize (hDC, hWndFolder);
  ReleaseDC (hWndFolder,hDC);

  // Berechnen aller Positionen
  BOOL state = FIRST_OFSIDE ;
  int ypos = rc.top ;
  LPICONELE FirstOfLine = NULL;
  int xpos ;
  for (e = iList ; e != NULL ; ) {
    switch (state) {
      case FIRST_OFSIDE :
        ypos = rc.top ;
        state = FIRST_OFLINE ;
        break ;
      case FIRST_OFLINE :
        xpos = e->x = rc.left + SPACING ;
        e->y = ypos ;
        FirstOfLine = e ;
        state = NORMAL ;
        e->cx = GetSystemMetrics (SM_CXICONSPACING) + 6 * XSPACE ;
        xpos += e->cx;
        e = e->Next ;
        break ;
      case NORMAL :
        if (rc.left + LineWidth(FirstOfLine,e) > rc.right) {
          ypos += LineHeight (FirstOfLine,e);  // um groesstes Element erhoehen
          state = FIRST_OFLINE ;
          }
        else {
          e->x = xpos ;
          e->cx = GetSystemMetrics (SM_CXICONSPACING) + 6 * XSPACE ;
          xpos += e->cx ;
          e->y = ypos ;
          e = e->Next ;
          }
        break ;
      }
    if (FirstOfLine != NULL)
      LastHeight = LineHeight (FirstOfLine,e);
    }

  InflateRect (&rc,20,20);
  TotalHeight = ypos+LastHeight;             // die Hoehe aller Icons+Text
  ScrollMax = max(0, TotalHeight-(rc.bottom-rc.top));  // unsichtbarer Bereich
  ScrollMax = ScrollMax/SCROLLHEIGHT * SCROLLHEIGHT;   // runden
  if (TotalHeight > (rc.bottom-rc.top)) {
    EnableScrollBar (hWndFolder, SB_VERT, ESB_ENABLE_BOTH);
    SetScrollRange (hWndFolder, SB_VERT, 0, ScrollMax, TRUE);
    }
  else
    EnableScrollBar (hWndFolder, SB_VERT, ESB_DISABLE_BOTH);

  }

/*--------------------------------------------------------------------*\
* member function:  Add                                                *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::Add (HWND hWnd,LPSTR txt,LPBITMAPINFO lpbi,LPICONELEDATA ele)
  {
  LPICONELE n = new IconEle (hWnd,this, txt, lpbi, ele);
  n->InitHotKey ();
  if (iList == NULL) {
    iList = n;
    Selected = iList;
    OldSelected = Selected;
    }
  else {
    for (LPICONELE h = iList; ;h = h->Next) {
      if (h->Next == NULL) {
        h->Next = n;
        break; 
        }
      }
    }
  }

/*--------------------------------------------------------------------*\
* member function:  Add                                                *
*                                                                      *
\*--------------------------------------------------------------------*/
void IconFolder::Add (HWND hWnd,LPSTR txt,HICON hico,LPICONELEDATA ele)
  {
  LPICONELE n = new IconEle (hWnd,this,txt,hico,ele);
  n->InitHotKey ();
  if (iList == NULL) {
    iList = n;
    Selected = iList;
    OldSelected = Selected;
    }
  else {
    for ( LPICONELE h = iList ; ; h = h->Next) {
      if (h->Next == NULL) {
        h->Next = n ;
        break ;
        }
      }
    }
  }

/*--------------------------------------------------------------------*\
* member function:  Find                                               *
*                                                                      *
\*--------------------------------------------------------------------*/
LPICONELE IconFolder::Find (int x,int y)
  {
  y += yPos ;
  for ( LPICONELE h = iList ; h != NULL ; h = h->Next) {
    if ((h->x <= x) && (h->x + h->cx > x) &&
        (h->y <= y) && 
        ((h->y + h->GetPictHeight() + 2 + YSPACE + h->TextHeight) > y))
//        (h->y + h->cy > y)) 
      break ;
    }
  return h;
  }

extern HINSTANCE hLibInst;
/*--------------------------------------------------------------------*\
* DESTRUCTOR  IconFolder                                               *
*                                                                      *
\*--------------------------------------------------------------------*/
IconFolder::~IconFolder ()
  {
  for ( ; iList != NULL ; ) {
    LPICONELE n = iList->Next;
    delete iList ;
    iList = n;
    }
  }

LPSTR szFolderClass;

static void RegisterFolderWindow()
  {
  static BOOL Registered ;
  
  if (!Registered) {
    WNDCLASS  wc;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS | CS_DBLCLKS ;
    wc.lpfnWndProc = IconWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = hLibInst;
    wc.hIcon = 0;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
#ifdef UEBERLEGT
    wc.hbrBackground = FolderBrush;
#else
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
#endif
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = szFolderClass;

    if (!RegisterClass(&wc))
      Registered = FALSE;
    else   
      Registered = TRUE ;
    }
  }

HWND CreateIconWindow (HWND hWndParent,LPRECT outRect)
  {
#ifdef UEBERLEGT
  if (FolderBrush == 0)
    FolderBrush = CreateSolidBrush (RGB(192, 220, 192));
#endif
  RegisterFolderWindow();

  HWND hWndFolder = CreateWindow (szFolderClass, NULL,
                             WS_CHILD | WS_CLIPSIBLINGS | WS_VSCROLL,
                             outRect->left, outRect->top,
                             outRect->right-outRect->left, 
                             outRect->bottom-outRect->top,
                             hWndParent,
                             NULL,
                             hLibInst,
                             NULL
                             );
  IconFolder FAR *first = new IconFolder ();
  SetWindowLong (hWndFolder,GWL_DATA,LONG(first));

  return hWndFolder;
  }

void DeleteFolderBrush ()
  {
#ifdef UEBERLEGT
  if (FolderBrush)
    DeleteObject (FolderBrush);
#endif
  }

/*---------------------------------------------------------------------------*\
*   _export Function AddPmEle                                                 *
*                                                                             *
*  Parameter:   txt .... Text unter dem Icon                                  *
*               lpbi ... Bitmap-Informationen                                 *
*               ele ....                                                      *
\*---------------------------------------------------------------------------*/
void xAddPmEle (LPSTR txt,HWND hWnd,LPBITMAPINFO lpbi,LPVOID data)
  {
  LPICONELEDATA ele = LPICONELEDATA (data);
  IconFolder FAR *first = (IconFolder FAR *) GetWindowLong (hWnd,GWL_DATA);
  first->Add (hWnd,txt,lpbi,ele);
  }

void xAddPmEle (LPSTR txt,HWND hWnd,HICON hico,LPVOID data)
  {
  LPICONELEDATA ele = LPICONELEDATA (data);
  IconFolder FAR *first = (IconFolder FAR *) GetWindowLong (hWnd,GWL_DATA);
  first->Add (hWnd,txt, hico, ele);
  }


void GroupReady (HWND hWnd)
  {
  IconFolder FAR *first = (IconFolder FAR *) GetWindowLong (hWnd,GWL_DATA);
  first->Arrange (hWnd);
  }

///////////////////////////////////////////////////////
// Implementierung IconTool
///////////////////////////////////////////////////////
void IconTool::Load ()
  {
  RECT r;
  LPINT lpw = (LPINT)(*GetData)(privData, ExtPar()->_w);
  LPINT lph = (LPINT)(*GetData)(privData, ExtPar()->_h);
  LPINT lpx = (LPINT)(*GetData)(privData, Param()->hd._x);
  LPINT lpy = (LPINT)(*GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpw != NULL) && (lph != NULL) && (lpx != NULL) && (lpy != NULL));
  tx = *lpx ;
  ty = *lpy ;
  tw = *lpw ;
  th = *lph ;

  BOOL FAR *IsDisabled = (BOOL FAR *) 
          (* GetData) (privData,ExtPar()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));

  r.left = ToDevKoordX (tx);
  r.top = ToDevKoordY (ty, Parent->Layer);
  r.right = r.left + ToDevX (tw) ;
  r.bottom = r.top+ToDevY (th);

  hExtWnd = CreateIconWindow (Parent->Parent->hWndToolbar(),&r);
  GetRect ();
  }

void IconTool::Reset (BOOL doClear)
  {
  if (doClear)
    DestroyWindow (hExtWnd);
  }

void IconTool::Update ()
  {
  }

LPSTR IconTool::GetHelpText ()
  {
  return NULL;
  }

void IconTool::FixConnection ()
  {
  }

DLLExport void _export IconTool::AddPmEle (LPSTR Name,LPBITMAPINFO bi,LPVOID ExtraData)
  {
  xAddPmEle (Name,hExtWnd,bi,ExtraData);
  }
DLLExport void _export IconTool::AddPmEle (LPSTR Name,HICON bi,LPVOID ExtraData)
  {
  xAddPmEle (Name,hExtWnd,bi,ExtraData);
  }

void IconTool::OnActivate (BOOL ActivateFlag)
  {
  if (ActivateFlag) {
    GroupReady (hExtWnd);
    }
  ShowWindow (hExtWnd, (ActivateFlag) ? SW_SHOW : SW_HIDE);
  ShowScrollBar (hExtWnd, SB_VERT, (ActivateFlag) ? SW_SHOW : SW_HIDE);
  }

DLLExport void _export WINAPI IconTool::NotifyActiveEle ()
  {
  IconFolder FAR *first = (IconFolder FAR *) GetWindowLong (hExtWnd,GWL_DATA);
  if ((first != NULL) && (first->Selected != NULL))
    first->Selected->Notify();
  else
    MessageBeep (0);
  }

