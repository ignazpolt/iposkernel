//
//  $Header:   P:/marille/clinicum/ctool/rev/bitlist.cpv   1.9   05 May 1997 10:29:28   Hannes  $
//  $Log:   P:/marille/clinicum/ctool/rev/bitlist.cpv  $
// 
//    Rev 1.9   05 May 1997 10:29:28   Hannes
// 
//    Rev 1.8   16 Jun 1996 19:06:24   gerhold
// int -> DBINT
// 
//    Rev 1.7   02 Feb 1996 10:41:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   24 Aug 1995 09:36:50   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   02 Jul 1995 18:19:42   HANNES
// Palettenhandling
// 
//    Rev 1.4   27 Jun 1995 15:05:00   HANNES
// 
//    Rev 1.3   27 Jun 1995 13:52:58   HANNES
// GetBitmapInfo...
// 
//    Rev 1.1   26 Jun 1995 10:19:44   GERHOLD
// Paletten-Information wird in der struct mitgespeichert.
// 
//    Rev 1.0   24 Jun 1994 16:41:16   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   06 Oct 1993 09:54:10   HANNES
// GetBitmap exportiert
// 
//    Rev 1.1   05 Jul 1993 14:54:12   GERHOLD
// 
//    Rev 1.0   03 Jun 1993 12:08:14   GERHOLD
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "toolbar.hpp"
#define MODULENUM 154
#include "winass.hpp"

extern GETRESOURCE GetResource ;


UINT DIBNumColors (LPBITMAPINFOHEADER lpbi)
  {
  WORD  wBitCount;
  DWORD dwClrUsed;
  
  dwClrUsed = lpbi->biClrUsed;
  
  if (dwClrUsed)
    return (UINT) dwClrUsed;
  
  
  // Calculate the number of colors in the color table based on
  //  the number of bits per pixel for the DIB.
  
  wBitCount = lpbi->biBitCount;
  
  switch (wBitCount) {
    case 1:
      return 2;
  
    case 4:
      return 16;
  
    case 8:
      return 256;
  
    default:
      return 0;
    }
  }


HPALETTE ExtractPaletteFromDIB (LPBITMAPINFO lpbmi)
  {
  WORD         wNumColors;
  HANDLE       hLogPal;
  HPALETTE     hPal = NULL;
  LPLOGPALETTE lpPal;
  int          i;

  wNumColors = DIBNumColors (&lpbmi->bmiHeader);

  if (wNumColors) {
    hLogPal = GlobalAlloc (GHND, sizeof (LOGPALETTE) +
                           sizeof (PALETTEENTRY) * wNumColors);

    if (!hLogPal)
       return NULL;

    lpPal = (LPLOGPALETTE) GlobalLock (hLogPal);

    lpPal->palVersion    = 0x300;
    lpPal->palNumEntries = wNumColors;

    for (i = 0;  i < (int)wNumColors;  i++) {
      lpPal->palPalEntry[i].peRed   = lpbmi->bmiColors[i].rgbRed;
      lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
      lpPal->palPalEntry[i].peBlue  = lpbmi->bmiColors[i].rgbBlue;
      lpPal->palPalEntry[i].peFlags = 0;
      }

    hPal = CreatePalette (lpPal);

    GlobalUnlock (hLogPal);
    GlobalFree   (hLogPal);
    }

  return hPal;
  }


BOOL DIBList::Initialize (BOOL bWithPal)
  {
  GLOBALHANDLE hGmem = (* GetResource) (Id);
  if (hGmem) {
    DBINT FAR *i = (DBINT FAR *) GlobalLock (hGmem);
    AnzCols = i[0] ;
    AnzRows = i[1] ;
    LPBITMAPINFOHEADER lpbi = LPBITMAPINFOHEADER (LPSTR (&i[2]) + 
                                  sizeof(BITMAPFILEHEADER)
                                                 );
    LPSTR Color = LPSTR (lpbi + 1);
    int nNumColors;
    if (!(nNumColors = (WORD)lpbi->biClrUsed)) {
      /* no color table for 24-bit, default size otherwise */
      if (lpbi->biBitCount != 24)
        nNumColors = 1 << lpbi->biBitCount; /* standard size table */
      }

    if (lpbi->biClrUsed == 0)
      lpbi->biClrUsed = nNumColors;

    if (lpbi->biSizeImage == 0) {
      lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3)
                           * lpbi->biHeight;
      }
      
    WORD offBits = nNumColors * sizeof(RGBQUAD);
    LPSTR lpbits = Color + offBits;

    // Erzeugen eines MemDC
    HDC hdc = CreateDC ("DISPLAY",NULL,NULL,NULL);
    HDC hdcMem = CreateCompatibleDC (hdc);

    // Erzeugen eines Bitmaps
    //  bmHeight = int ((LONG (bmWidth) * lpbi->biHeight) / lpbi->biWidth) ;
    int bmWidth  = int (lpbi->biWidth) ;
    int bmHeight = int (lpbi->biHeight) ;
  
    hPal = 0;
/*=======================================================*/
    HPALETTE hOldPal;
    if (bWithPal) {
      hPal = ExtractPaletteFromDIB (LPBITMAPINFO (lpbi));
      hOldPal = SelectPalette (hdc, hPal, TRUE);
      RealizePalette (hdc);
      }
/*=======================================================*/      

    if (bWithPal)
      bmp = CreateDIBitmap (hdc, lpbi, CBM_INIT, lpbits,
                            LPBITMAPINFO (lpbi), DIB_RGB_COLORS);
    else {                        
      bmp = CreateCompatibleBitmap (hdc,bmWidth,bmHeight);
      SelectObject (hdcMem,bmp);

#ifdef UEBERLEGT
      SetDIBitsToDevice (hdcMem,0,0,bmWidth,bmHeight,
                            0,0,
                            bmWidth,bmHeight,
                            lpbits,
                            LPBITMAPINFO (lpbi),
                            DIB_RGB_COLORS
                        );
#else
      StretchDIBits (hdcMem,0,0,bmWidth,bmHeight,
                            0,0,
                            bmWidth,bmHeight,
                            lpbits,
                            LPBITMAPINFO (lpbi),
                            DIB_RGB_COLORS,SRCCOPY
                    );
#endif
      }
      
/*=============================================*/
    if (bWithPal) {
      SelectPalette (hdc, hOldPal, TRUE);
      RealizePalette (hdc);
      }
/*==============================================*/    
    // Fertig
    DeleteDC (hdcMem);
    DeleteDC (hdc);

    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    return TRUE ;
    }
  else {
    bmp = NULL ;
    return FALSE ;
    }
  }

BOOL DIBList::GetStruct ()
  {
  hGBits = (* GetResource) (Id);
  if (hGBits) {
    DBINT FAR *i = (DBINT FAR *) GlobalLock (hGBits);
    AnzCols = i[0] ;
    AnzRows = i[1] ;
    lpbi = LPBITMAPINFOHEADER (LPSTR (&i[2]) + 
                                  sizeof(BITMAPFILEHEADER)
                              );

    hPal = ExtractPaletteFromDIB (LPBITMAPINFO (lpbi));

    w = int(lpbi->biWidth) ;
    h = int(lpbi->biHeight) ;

    return TRUE ;
    }
  return FALSE ;
  }

DIBList FAR *FirstDIB;

DLLExport HBITMAP _export WINAPI GetBitmap (DWORD Id,int FAR &AnzRows,int FAR &AnzCols)
  {
  for (DIBList FAR *h = FirstDIB; h != NULL ; h = h->Next) {
    if (h->Id == Id) break ;
    }
  if (h == NULL) {
    h = (DIBList FAR *) GetGlobMem (sizeof(*h));
    h->Next = FirstDIB ;
    h->Id = Id ;
    h->Initialize (FALSE);
    FirstDIB = h;
    }
  AnzRows = h->AnzRows;
  AnzCols = h->AnzCols;
  return h->bmp;
  }

DIBList FAR * GetBitmapInfo (DWORD Id,int FAR &AnzRows,int FAR &AnzCols,HPALETTE FAR &hPal)
  {
  for (DIBList FAR *h = FirstDIB; h != NULL ; h = h->Next) {
    if (h->Id == Id) break ;
    }
  if (h == NULL) {
    h = (DIBList FAR *) GetGlobMem (sizeof(*h));
    h->Next = FirstDIB ;
    h->Id = Id ;
    h->GetStruct ();
    FirstDIB = h;
    }
  DBWIN_ASSERT ((h->hGBits != NULL) || (h->hMask)) ;
  AnzRows = h->AnzRows;
  AnzCols = h->AnzCols;
  hPal = h->hPal;
  return h;
  }

DLLExport HBITMAP _export WINAPI GetBitmap (DWORD Id,int FAR &AnzRows,int FAR &AnzCols, 
                                             HPALETTE far &Palette)
  {
  for (DIBList FAR *h = FirstDIB; h != NULL ; h = h->Next) {
    if (h->Id == Id) break ;
    }
  if (h == NULL) {
    h = (DIBList FAR *) GetGlobMem (sizeof(*h));
    h->Next = FirstDIB ;
    h->Id = Id ;
    h->Initialize (TRUE);
    FirstDIB = h;
    }
  AnzRows = h->AnzRows;
  AnzCols = h->AnzCols;
  Palette = h->hPal;
  return h->bmp;
  }

void CleanBitmapList ()
  {
  for ( DIBList FAR *h = FirstDIB; h != NULL ; ) {
    DIBList FAR *Next = h->Next;
    if (h->bmp) DeleteObject (h->bmp);
    if (h->hPal) DeleteObject (h->hPal);
    if (h->hMask) DeleteObject (h->hMask);
    if (h->hBorder) DeleteObject (h->hBorder);
    if (h->hGBits) GlobalFree (h->hGBits);
    if (h->lpbits) FreeGlobMem (h->lpbits);
    if (h->xp0 != NULL) {
      FreeGlobMem (h->xp0);
      FreeGlobMem (h->xp1);
      FreeGlobMem (h->yp0);
      FreeGlobMem (h->yp1);
      }
    FreeGlobMem (h);
    h = Next ;
    }
  }
