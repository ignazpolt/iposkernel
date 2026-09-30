///////////////////////////////////////////////////////////
//  Spielereien mit Bitmaps
///////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ctool/rev/trbit.cpv   1.10   05 Oct 1998 11:05:52   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/trbit.cpv  $
// 
//    Rev 1.10   05 Oct 1998 11:05:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.9   25 Jul 1996 19:57:52   GERHOLD
// int far *  =>  DBINT FAR *
// 
//    Rev 1.8   02 Feb 1996 10:42:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   31 Oct 1995 13:52:22   MARTIN
// SelectPalette(hOldPal) ...
// 
//    Rev 1.6   24 Aug 1995 09:36:52   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   16 Aug 1995 08:52:34   HANNES
// Palettenhandling der 16 Farben Bitmaps
// 
//    Rev 1.4   04 Jul 1995 20:39:44   HANNES
// 16 Farbenbitmaps
// 
//    Rev 1.3   03 Jul 1995 16:15:18   HANNES
// SRCPAINT -> SRCINVERT !?!
// 
//    Rev 1.2   02 Jul 1995 18:18:54   HANNES
// Borders, GetRect, Palettenhandling
// 
//    Rev 1.1   27 Jun 1995 15:04:58   HANNES
// 
//    Rev 1.0   27 Jun 1995 13:54:40   HANNES
// Initial revision.
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
#define MODULENUM   153
#include "winass.hpp"
#define NODDSDATA
#include "dds.hpp"

#define DSna  0x220326
static unsigned char mask[8]  = { 0x80 , 0x40 , 0x20 , 0x10 , 0x08 , 0x04 , 0x02 , 0x01 } ;
void DIBList::GetXVals (int forMono)
  {
  xp0 = (int FAR *) GetGlobMem (sizeof(int) * AnzRows * AnzCols) ;
  xp1 = (int FAR *) GetGlobMem (sizeof(int) * AnzRows * AnzCols) ;
  yp0 = (int FAR *) GetGlobMem (sizeof(int) * AnzRows * AnzCols) ;
  yp1 = (int FAR *) GetGlobMem (sizeof(int) * AnzRows * AnzCols) ;
  for (int by = 0 ; by < AnzRows ; by++) {
    int i0 = by * (h / AnzRows) ;
    int i1 = i0 + (h / AnzRows) ;
    for (int bx = 0 ; bx < AnzCols ; bx++) {
      int j0 = bx * (w / AnzCols) ;
      int j1 = j0 + (w / AnzCols) ;
      int FAR *lpx0 = xp0 + by * AnzCols + bx ;
      int FAR *lpx1 = xp1 + by * AnzCols + bx ;
      int FAR *lpy0 = yp0 + by * AnzCols + bx ;
      int FAR *lpy1 = yp1 + by * AnzCols + bx ;
      int State = 0 ;
      for (int i = i0 ; i < i1 ; i++) {
        LPSTR lpLine = lpbits + i * bw ;
        if (State) State = 1 ;
        for (int j = j0 ; j < j1 ; j++) {
          switch (State) {
            case 0 :  // Am Beginn des Bitmaps
              if (!(((lpLine[j / 8] & mask [j & 7]) != 0) ^ (forMono))) {
                        // inside
                *lpx0 = *lpx1 = j - j0 ;
                *lpy0 = *lpy1 = i - i0 ;
                State = 2 ;
                }
              break ;
            case 1 :  // Am Beginn einer ScanZeile, aktuell 1 - Bits
              *lpy1 = i - i0 ;
              if (!(((lpLine[j / 8] & mask[j & 7]) != 0) ^ (forMono))) {
                        // inside
                if (*lpx0 > (j - j0)) *lpx0 = j - j0 ;
                if (*lpx1 < (j - j0)) *lpx1 = j - j0 ;
                State = 2 ;
                }
              break ;
            case 2 :  // Mitten in einer Scan - Zeile
              if (((lpLine[j / 8] & mask[j & 7]) != 0) ^ (forMono)) {
                        // ! inside
                if (*lpx1 < (j - j0 - 1)) *lpx1 = j - j0 - 1 ;
                State = 3;
                }
              break ;
            case 3 :  // Am Ende einer Scan - Zeile
              if (!(((lpLine[j / 8] & mask[j & 7]) != 0) ^ (forMono))) {
                        // inside
                State = 2 ;
                }
            }
          }
        }
      }
    }
  }
void DIBList::GetMask(COLORREF TransparentColor)
  {
  BitCount = lpbi->biBitCount;
  if (lpbi->biSizeImage == 0) {
    lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3)
                        * lpbi->biHeight;
    }

  if (lpbi->biBitCount == 8) {
    // Finden des Index der Farben
    BYTE trIndex;
    for (int i = 0 ; i < 256 ; i++) {
      if ((GetRValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbRed) &&
          (GetGValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbGreen) &&
          (GetBValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbBlue)) {
        trIndex = BYTE(i) ;
        break ;
        }
      }
  
    // Aus diesem Bitmap nun das entsprechende Teilbitmap rausholen
    // Monochrome Bits generieren
    if ((w % 8) == 0)  bw = w / 8 ;
    else               bw = w / 8 + 1 ;
    if ((bw % 2) != 0) bw = ((bw / 2) + 1) * 2 ;
    DBWIN_ASSERT (DWORD(h) * DWORD(bw) < 0x7FFFL) ;
    lpbits = LPSTR(GetGlobMem (h * bw + 1));
    int bpl ;
    if ((int(lpbi->biWidth) % 4) == 0) bpl = int(lpbi->biWidth) ;
    else                               bpl = ((int(lpbi->biWidth) / 4) + 1) * 4 ;

    LPSTR Color = LPSTR (lpbi + 1);
    WORD offBits = 256 * sizeof(RGBQUAD);
    LPSTR lpSrc = Color + offBits;

    for (i = 0 ; i < h ; i++) {
      char huge *lpLine = (char huge *) lpSrc + DWORD (int(lpbi->biHeight) - 1 - i) * DWORD (bpl) ;
      char FAR *lpdest = lpbits + i * bw ; 
      for (int j = 0 ; j < w ; j++) {
        if (*lpLine == trIndex) {
          lpdest[j >> 3] |= mask[j & 7] ;
          }
        lpLine ++ ;
        }
      }

    // Das Maskenbitmap erzeugen
    ///////////////////////////////
    hMask = CreateBitmap (w,h,1,1,lpbits);

    // Das eigentliche Bitmap noch erzeugen
    /////////////////////////////////////////
    HDC hDC     = CreateDC ("DISPLAY",NULL,NULL,NULL);
    HDC hdcMem  = CreateCompatibleDC (hDC);
    HDC hdcMask = CreateCompatibleDC (hDC);

    HPALETTE hOldPal = SelectPalette (hDC,hPal,TRUE);
    RealizePalette (hDC);
    bmp = CreateDIBitmap (hDC, lpbi, CBM_INIT, lpSrc,
                          LPBITMAPINFO (lpbi), DIB_RGB_COLORS);
    SelectObject (hdcMem,bmp);

    // Und noch maskieren
    ///////////////////////////////
    SelectObject (hdcMask,hMask);
    BitBlt (hdcMem,0,0,w,h,hdcMask,0,0,DSna);

    if (hOldPal)
      SelectPalette (hDC, hOldPal, TRUE);

    DeleteDC (hDC);
    DeleteDC (hdcMem);
    DeleteDC (hdcMask);
    GetXVals (0);
    }
  else if (lpbi->biBitCount == 4) {
    // Finden des Index der Farben
    BYTE trIndex,trIndex1;
    for (int i = 0 ; i < 16 ; i++) {
      if ((GetRValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbRed) &&
          (GetGValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbGreen) &&
          (GetBValue (TransparentColor) == LPBITMAPINFO(lpbi)->bmiColors[i].rgbBlue)) {
        trIndex = BYTE(i) ;
        break ;
        }
      }
    trIndex1 = trIndex << 4 ;
  
    // Aus diesem Bitmap nun das entsprechende Teilbitmap rausholen
    // Monochrome Bits generieren
    if ((w % 8) == 0)  bw = w / 8 ;
    else               bw = w / 8 + 1 ;
    if ((bw % 2) != 0) bw = ((bw / 2) + 1) * 2 ;
    DBWIN_ASSERT (DWORD(h) * DWORD(bw) < 0x7FFFL) ;
    lpbits = LPSTR(GetGlobMem (h * bw + 1));
    int bpl = int((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3) ;

    LPSTR Color = LPSTR (lpbi + 1);
    WORD offBits = 16 * sizeof(RGBQUAD);
    LPSTR lpSrc = Color + offBits;

    for (i = 0 ; i < h ; i++) {
      char huge *lpLine = (char huge *) lpSrc + DWORD (int(lpbi->biHeight) - 1 - i) * DWORD (bpl) ;
      char FAR *lpdest = lpbits + i * bw ; 
      for (int j = 0 ; j < w ; j++) {
        if (j & 1) {
          if ((lpLine[j / 2] & 0x0F) == trIndex) {
            lpdest[j >> 3] |= mask[j & 7] ;
            }
          }
        else {
          if ((lpLine[j / 2] & 0xF0) == trIndex1) {
            lpdest[j >> 3] |= mask[j & 7] ;
            }
          }
        }
      }

    // Das Maskenbitmap erzeugen
    ///////////////////////////////
    hMask = CreateBitmap (w,h,1,1,lpbits);

    // Das eigentliche Bitmap noch erzeugen
    /////////////////////////////////////////
    HDC hDC     = CreateDC ("DISPLAY",NULL,NULL,NULL);
    HDC hdcMem  = CreateCompatibleDC (hDC);
    HDC hdcMask = CreateCompatibleDC (hDC);

    bmp = CreateDIBitmap (hDC, lpbi, CBM_INIT, lpSrc,
                          LPBITMAPINFO (lpbi), DIB_RGB_COLORS);
    SelectObject (hdcMem,bmp);

    // Und noch maskieren
    ///////////////////////////////
    SelectObject (hdcMask,hMask);
    BitBlt (hdcMem,0,0,w,h,hdcMask,0,0,DSna);

    DeleteDC (hDC);
    DeleteDC (hdcMem);
    DeleteDC (hdcMask);
    GetXVals (0);
    }
  else if (lpbi->biBitCount == 1) {
    // Das Maskenbitmap normal erzeugen
    LPSTR Color = LPSTR (lpbi + 1);
    int nNumColors = 1 << lpbi->biBitCount; /* standard size table */
    WORD offBits = nNumColors * sizeof(RGBQUAD);
    LPSTR lpSrc = Color + offBits;

    // Die lpBits aus lpSrc uebernehmen
    int bpl = int ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3);
    if ((w % 8) == 0)  bw = w / 8 ;
    else               bw = w / 8 + 1 ;
    if ((bw % 2) != 0) bw = ((bw / 2) + 1) * 2 ;
    DBWIN_ASSERT (DWORD(h) * DWORD(bw) < 0x7FFFL) ;
    // Umkopieren der Bits (Achtung: im DIB gehts von unten nach oben)
    lpbits = LPSTR(GetGlobMem (h * bw + 1));
    for (int i = 0 ; i < h ; i++) {
      for (int j = 0 ; j < bw ; j++)
        lpbits[i * bw + j] = ~lpSrc [(h - 1 - i) * bpl + j];
      }
    hMask = CreateBitmap (w,h,1,1,lpbits);
    GetXVals (1);
    }
  else
    DBWIN_ASSERT (FALSE);
  if (hGBits != 0)
    GlobalFree (hGBits) , hGBits = 0 ;
  }

BYTE *GetBitToSet (BOOL forMonoBitmap)
  {
  static BYTE btos [512];
  static BYTE nbtos [512];
  static BOOL isDone ;
  if (!isDone) {
    for (int i = 1 ; i < 511 ; i++) {
      if ((i & 0x10) != 0) btos[i] = TRUE ;
      else                 nbtos[i] = TRUE ;
      }
    isDone = TRUE ;
    }
  return (forMonoBitmap) ? nbtos : btos ;
  }
inline BYTE Get3Bits (int val,char toshift)
  {
  BYTE res ;
  if (toshift >= 0) res = BYTE(val >> toshift) & 0x07 ;
  else {
    char valx = LOBYTE(val) << 8 + HIBYTE(val) ;
    res = BYTE(valx >> (8 + toshift)) & 0x07 ;
    }
#ifdef OLD_VERSION
  else if (toshift == -1) {
    _asm {
      mov ax,val 
      rol ax,1 ;
      and al,7
      mov res,al ;
      }
    }
  else if (toshift == -2) {
    _asm {
      mov ax,val
      rol ax,1
      rol ax,1
      and al,7
      mov res,al ;
      }
    }
#endif
  return res ;
  }
void DIBList::GetBorder ()
  {
  // Ueberpruefen, ob die Maske wirklich schon existiert
  DBWIN_ASSERT (lpbits != NULL);

  // Monochrome Bits durch Spezialfilter generieren
  LPSTR lpborder = LPSTR(GetGlobMem (h * bw));

  BYTE *bitToSet = GetBitToSet (bmp == 0);
  for (int i = 1 ; i < h-1 ; i++) {
    char FAR *lpdest = lpborder + i * bw ;
    for (int j = 1 ; j < w - 1 ; j++) {
      int k = j - 1 ;
      char FAR *lpsrc0 = lpbits + (i - 1) * bw + (k >> 3) ; 
      char FAR *lpsrc1 = lpsrc0 + bw ;
      char FAR *lpsrc2 = lpsrc1 + bw ;
      int bOffs = k & 7 ;
      char shiftoffs = char(5 - bOffs) ;
      int qval = (int (Get3Bits (* ((int FAR *) lpsrc0),shiftoffs)) << 6) + 
                 (int (Get3Bits (* ((int FAR *) lpsrc1),shiftoffs)) << 3) + 
                  int (Get3Bits (* ((int FAR *) lpsrc2),shiftoffs)) ; 
      if (bitToSet[qval])
        lpdest[j >> 3] |= mask[j & 7] ;
      }
    }

  // Das Umrandungsbitmap erzeugen
  hBorder = CreateBitmap (w,h,1,1,lpborder);

  FreeGlobMem (lpborder);
  }

class FAR BitmapObject {
 public :
  DIBList FAR *lst;
  int x,y,xpInd,xOffs,yOffs;
  int w,h;
  COLORREF tColor;

  ~BitmapObject ()
    {
    }

  BitmapObject (DWORD bitId,int bx,int by,int xs,int ys,DWORD TransparentColor)
    {
    tColor = TransparentColor;
    int AnzRows,AnzCols;
    HPALETTE hPal;
    lst = GetBitmapInfo (bitId,AnzRows,AnzCols,hPal);

    DBWIN_ASSERT ((bx < AnzCols) && (by < AnzRows)) ;
    x = xs ;
    y = ys ;
    // Aus diesem Bitmap nun das entsprechende Teilbitmap rausholen
    w = int(lst->w) / AnzCols ;
    h = int(lst->h) / AnzRows ;

    if (lst->hMask == 0) lst->GetMask (TransparentColor);
    xOffs = w * bx ;
    yOffs = h * by ;
    xpInd = by * AnzCols + bx ;
    }
  void GetBorder ()
    {
    if (lst->hBorder == 0) lst->GetBorder ();
    }
  void Paint (HDC hDC,HDC hdcMem)
    {
    if (lst->bmp) {
      // Hilfsbitmap erzeugen
      HBITMAP oldBmp = (HBITMAP)SelectObject (hdcMem,CreateCompatibleBitmap (hDC,w,h));

      // DC fuer das bereits maskierte Bitmap
      HDC hdcTemp = CreateCompatibleDC (hDC);
      SelectObject (hdcTemp,lst->bmp);   

      // Hintergrund in den Arbeitskontext
      BitBlt(hdcMem, 0, 0, w, h, hDC, x, y,
             SRCCOPY);

      // Vom Hintergrund entsprechend ausmaskieren
      HDC hdcMask = CreateCompatibleDC (hDC);
      SelectObject (hdcMask,lst->hMask);
      BitBlt(hdcMem, 0, 0, w, h, hdcMask, xOffs, yOffs, SRCAND);

      // Die entsprechenden Bitmaps zusammenmischen
//      BitBlt(hdcMem, 0, 0, w, h, hdcTemp, xOffs, yOffs, SRCPAINT);
      BitBlt(hdcMem, 0, 0, w, h, hdcTemp, xOffs, yOffs, SRCINVERT);

      // Und auf den Bildschirm
      BitBlt(hDC, x, y, w, h, hdcMem, 0, 0,
            SRCCOPY);

      DeleteDC (hdcMask);
      DeleteObject (SelectObject (hdcMem,oldBmp));
      DeleteDC (hdcTemp);
      }
    else {
      // Hilfsbitmap erzeugen
      HBITMAP oldBmp = (HBITMAP)SelectObject (hdcMem,CreateCompatibleBitmap (hDC,w,h));

      // DC fuer das Maskenbitmap
      HDC hdcTemp = CreateCompatibleDC (hDC);
      SelectObject (hdcTemp,lst->hMask);   

      // Hintergrund in den Arbeitskontext
      BitBlt(hdcMem, 0, 0, w, h, hDC, x, y,
             SRCCOPY);

      // In den Hilfskontext die Umrandung reinmalen
      COLORREF bcolor = GetNearestColor(hDC, tColor & 0x00FFFFFF);
      HBRUSH hOldBrush = (HBRUSH)SelectObject (hdcMem,CreateSolidBrush(bcolor));
      BitBlt(hdcMem, 0, 0, w, h, hdcTemp, xOffs, yOffs, 0xE20746);
      DeleteObject (SelectObject (hdcMem,hOldBrush));

      // Und auf den Bildschirm
      BitBlt(hDC, x, y, w, h, hdcMem, 0, 0,
            SRCCOPY);

      DeleteObject (SelectObject (hdcMem,oldBmp));
      DeleteDC (hdcTemp);
      }
    }
  void PaintBorder (HDC hDC,HDC hdcMem,COLORREF Color)
    {
    // Hilfsbitmap erzeugen
    HBITMAP oldBmp = (HBITMAP)SelectObject (hdcMem,CreateCompatibleBitmap (hDC,w,h));

    // DC fuer das Umrandungsbitmap
    HDC hdcTemp = CreateCompatibleDC (hDC);
    SelectObject (hdcTemp,lst->hBorder);   

    // Hintergrund in den Arbeitskontext
    BitBlt(hdcMem, 0, 0, w, h, hDC, x, y,
           SRCCOPY);

    // In den Hilfskontext die Umrandung reinmalen
    COLORREF bcolor = GetNearestColor(hDC, Color & 0x00FFFFFF);
    HBRUSH hOldBrush = (HBRUSH)SelectObject (hdcMem,CreateSolidBrush(bcolor));
    BitBlt(hdcMem, 0, 0, w, h, hdcTemp, xOffs, yOffs, 0xE20746);
    DeleteObject (SelectObject (hdcMem,hOldBrush));

    // Und auf den Bildschirm
    BitBlt(hDC, x, y, w, h, hdcMem, 0, 0,
          SRCCOPY);

    DeleteObject (SelectObject (hdcMem,oldBmp));
    DeleteDC (hdcTemp);
    }
  void GetRect (LPRECT r)
    {
    r->left   = x + lst->xp0[xpInd] - 1;
    r->top    = y + lst->yp0[xpInd] - 1;
    r->right  = x + lst->xp1[xpInd] + 1;
    r->bottom = y + lst->yp1[xpInd] + 1;
    }
  };


struct BitmapObject_param {
  WORD parSize;
  // private Daten (12 Byte)
  DWORD _color;
  int _bx,_by,_xp,_yp;
  // nun die Scriptdaten
  DWORD res;
  DWORD xp,yp;
  DWORD pIndex;
  DWORD bx,by;
  DWORD color;
  };

DLLExport void _export WINAPI DefBitmapObject (LPVOID param,WORD mode,LPVOID privData,int pdSize)
  {
  if (mode & EM_LOAD) {
    BitmapObject_param FAR *par = (BitmapObject_param FAR *) param;
    DBINT FAR *xp = (DBINT FAR *) (* GetData) (privData,par->xp);
    DBINT FAR *yp = (DBINT FAR *) (* GetData) (privData,par->yp);
    DBINT FAR *bx = (DBINT FAR *) (* GetData) (privData,par->bx);
    DBINT FAR *by = (DBINT FAR *) (* GetData) (privData,par->by);
    DWORD FAR *color = (DWORD FAR *) (* GetData) (privData,par->color);
    DBWIN_ASSERT ((xp != NULL) &&
                (yp != NULL) &&
                (bx != NULL) &&
                (by != NULL) &&
                (color != NULL)) ;
    par->_bx = *bx ;
    par->_by = *by ;
    par->_xp = *xp ;
    par->_yp = *yp ;
    par->_color = *color ;
    (* SetData) (privData,par->res,&par,sizeof(par),LPSTR(param)-sizeof(WORD));
    }
  }

ShowTransparentBitmap::ShowTransparentBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) : tool (RefWnd,Data,pData,pSize)
  {
  }
void ShowTransparentBitmap::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Par()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Par()->hd._y);
  BitmapObject_param FAR * FAR *db = (BitmapObject_param FAR * FAR *) (* GetData) (privData,Par()->obj);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  bo = new BitmapObject ((*db)->pIndex,(*db)->_bx,(*db)->_by,
                         ToDevKoordX (*lpx) + (*db)->_xp,
                         ToDevKoordY (*lpy,Parent->Layer) + (*db)->_yp,
                         (*db)->_color);
  if (bo->lst->BitCount == 8) {
    Parent->Parent->SetPalette (bo->lst->hPal);
    Parent->Parent->IncPalUseCount();
    }
  GetRect ();
  }
void ShowTransparentBitmap::PaintTool (HDC hDC, HDC hmemDC)
  {
  bo->Paint(hDC,hmemDC);
  }
void ShowTransparentBitmap::GetRect ()
  {
  bo->GetRect (LPRECT(&ToolRect));
  Parent->CheckLayerHeight (ToolRect.bottom);
  }
void ShowTransparentBitmap::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  if (bo->lst->BitCount == 8)
    Parent->Parent->DecPalUseCount();
  delete bo ;
  bo = NULL ;
  }
void ShowTransparentBitmap::FixConnection ()
  {
  }
void ShowTransparentBitmap::Invalidate (BOOL doErase)
  {
  RECT rc;
  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 2, 2);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }
// Bitmap - Umrandung
///////////////////////////////////////////////////
BitSelect::BitSelect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) : ShowTransparentBitmap (RefWnd,Data,pData,pSize)
  {
  }

void BitSelect::Load ()
  {
  ShowTransparentBitmap::Load();
  bo->GetBorder();
  DWORD FAR *lpcolor = (DWORD FAR *) (* GetData) (privData,Par()->Color);
  DBWIN_ASSERT (lpcolor != NULL);
  Color = *lpcolor;
  lpcolor = (DWORD FAR *) (* GetData) (privData,Par()->MoveColor);
  DBWIN_ASSERT (lpcolor != NULL);
  MoveColor = *lpcolor ;
  IsEnabled = TRUE ;
  }

#define BSSTATE_NONE      0
#define BSSTATE_MOUSEHIT  1
#define BSSTATE_SELECT    2
void BitSelect::PaintTool (HDC hDC, HDC hmemDC)
  {
  switch (State) {
    case BSSTATE_MOUSEHIT :
      bo->PaintBorder (hDC,hmemDC,MoveColor);
      break ;
    case BSSTATE_SELECT :
      bo->PaintBorder (hDC,hmemDC,Color);
      break ;
    }
  }

DWORD ModeID;
BOOL BitSelect::Hit (LPPOINT pt)
  {
  int x = pt->x;
  int y = pt->y;
  BOOL hit;
  if ((x > ToolRect.left) && (x < ToolRect.right) &&
      (y > ToolRect.top) && (y < ToolRect.bottom)) {
    int line = y - (bo->y - bo->yOffs) ;
    int col  = x - (bo->x - bo->xOffs) ;
    if ((line >= 0) && (line < bo->lst->h) &&
        (col >= 0) && (col < bo->lst->w)) {
      BYTE bit = (*(bo->lst->lpbits + (line * bo->lst->bw) + (col / 8)) & (mask[col & 7]));
      if (bo->lst->bmp) hit = (bit == 0) ;
      else              hit = (bit != 0) ;
      }
    else
      hit = FALSE ;
    }
  else
    hit = FALSE ;
  return hit;
  }

void BitSelect::OnMouseMove (WPARAM wP,LPARAM lP)
  {
  if ((wP & MK_LBUTTON) == 0) {
    POINT pt ;
    pt.x = LOWORD(lP);
    pt.y = HIWORD(lP);
    BOOL hit = Hit(&pt);
    switch (State) {
      case BSSTATE_NONE :
        if (hit) {
          State = BSSTATE_MOUSEHIT ;
          Invalidate (FALSE);
          }
        break ;
      case BSSTATE_MOUSEHIT :
        if (!hit) {
          State = BSSTATE_NONE ;
          Invalidate (TRUE);
          }
        break ;
      }
    }
  }

BOOL BitSelect::HitTest (LPPOINT pt)
  {
  BOOL res;
  if (Hit (pt)) {
    int mode ;
    if (GetKeyState (VK_SHIFT) < 0)        mode = 2 ;
    else if (GetKeyState (VK_CONTROL) < 0) mode = 1 ;
    else                                   mode = 0 ;
    (* SetData) (privData,ModeID,&mode,sizeof(mode),StructData);
    (* CallCommand) (privData,Par()->procPtr,Par());
    res = TRUE ;
    }
  else
    res = FALSE ;
  return res ;
  }

void BitSelect::ResetSelection()
  {
  if (State == BSSTATE_SELECT) {
    DWORD lP = GetMessagePos ();
    POINT pt ;
    pt.x = LOWORD(lP);
    pt.y = HIWORD(lP);
    if (Hit (&pt)) {
      State = BSSTATE_MOUSEHIT ;
      Invalidate (FALSE);
      }
    else {
      State = BSSTATE_NONE ;
      Invalidate (TRUE);
      }
    }
  }

void BitSelect::Select()
  {
  if (State != BSSTATE_SELECT) {
    State = BSSTATE_SELECT ;
    Invalidate (FALSE);
    }
  }

DLLExport void _export WINAPI ResetAllBitSelections (ScreenList FAR *sc,BitSelect FAR *active)
  {
  for (int i = 0 ; i < sc->AnzActive ; i++) {
    for (tool FAR *h = sc->ActiveList[i]->first ; h != NULL ; h = h->Next) {
      int FAR *command = (int FAR *) h->StructData ;
      if ((*command == TOOLTYPE_BITSELECT) && (h != active)) {
        ((BitSelect FAR *) h)->ResetSelection();
        }
      }
    }
  }

DLLExport void _export WINAPI CTOOL_SetBitSelectMode (BitSelect FAR *bs,BOOL select)
  {
  if (bs != NULL) {
    if (select) bs->Select ();
    else        bs->ResetSelection ();
    }
  }

DLLExport void _export WINAPI CTOOL_InstallSelectMode (DWORD Id)
  {
  ModeID = Id;
  }
