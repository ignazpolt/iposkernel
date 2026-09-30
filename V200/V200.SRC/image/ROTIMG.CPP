/*--------------------------------------------------------------------*/
/*      Drehen eines Tiff - Bildes um 90 Grad und speichern des       */
/*      Bildes wieder als Tiff                                        */
/*--------------------------------------------------------------------*/
//
//      $Header:   P:/marille/clinicum/image/rev/rotimg.cpv   1.4   03 Mar 1998 20:04:48   Martin  $
//      $Log:   P:/marille/clinicum/image/rev/rotimg.cpv  $
// 
//    Rev 1.4   03 Mar 1998 20:04:48   Martin
// True Color
// 
//    Rev 1.3   02 Feb 1996 10:49:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   08 Dec 1994 21:48:38   HANNES
// 
//    Rev 1.1   17 Oct 1994 15:02:50   HANNES
// Synchronisation mit Marille
// 
//    Rev 1.0   24 Jun 1994 16:51:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   13 Apr 1994 20:45:50   MARTIN
// Auslagerung ins header file
// 
//    Rev 1.3   06 Oct 1993 09:47:54   MARTIN
// Bilder verschiedener Art
// 
//    Rev 1.2   23 Aug 1993 18:48:38   MARTIN
// Image-Umstellung (Native-Mode, DIBs)
// 
//    Rev 1.1   13 Dec 1992 20:05:14   HANNES
// Korrektur des Tiff - Schreibens (Row's per Strip)
// 
//    Rev 1.0   07 Dec 1992 14:21:30   HANNES
// Initial revision.
//
//
//
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include "dds32.h"
//#include "tiff.h"
#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#define MIMAGE_CLASS
#include "image.hpp"
#define MODULENUM 46
#include "winass.hpp"

#pragma loop_opt(on)
DLLExport void _export WINAPI mImage::RotatePicture ()
  {
  int i ;

  // Speicher anlegen
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  WIN_ASSERT(lpbi->biBitCount == 8);  // derzeit nur fuer 256 Farben Bilder
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  char huge *Src = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
  GLOBALHANDLE hGLine,hGFlags,hGPtrs,hGRes ;
  int width   = int (lpbi->biWidth);
  int height  = int (lpbi->biHeight);
  int bwidth  = int (ByteWidth (width,lpbi->biBitCount));
  int nbwidth = int (ByteWidth (height,lpbi->biBitCount));
  hGLine = GlobalAlloc (GMEM_MOVEABLE,bwidth);
  hGFlags = GlobalAlloc (GMEM_MOVEABLE,width * sizeof(BYTE));
  hGPtrs = GlobalAlloc (GMEM_MOVEABLE,width * sizeof(LPSTR));
  hGRes = GlobalAlloc (GMEM_MOVEABLE,(LONG (width) * LONG(nbwidth))
                                     + lpbi->biSize + dwColorTableSize);

  // Zeiger Initialisieren
  LPSTR *Ptrs = (LPSTR *) GlobalLock (hGPtrs);
  LPSTR Line  = LPSTR(GlobalLock (hGLine));
  LPSTR Flags = LPSTR(GlobalLock (hGFlags));
  LPBITMAPINFOHEADER lpnbi = (LPBITMAPINFOHEADER)GlobalLock(hGRes);
  lmemcpy(lpnbi, lpbi, int(lpbi->biSize + dwColorTableSize));
  char huge *Res = ((LPSTR)lpnbi) + lpbi->biSize + dwColorTableSize;
  LPSTR h = LPSTR (Res);
  for (i = 0 ; i < width ; i++) {
    Ptrs[i] = h ;
    LPSTR hn = LPSTR ((char huge *) h + nbwidth);
//    if (i)
#ifndef WIN32
      Flags[i] = (FP_SEG(h) != FP_SEG(hn)) ; // Kontrolle, ob Segmentsprung
#else
      Flags[i] = FALSE;
#endif
//    else
//      Flags[i] = FALSE ;
    h = hn ;
    }

  for (i = 0 ; i < height ; i++) {
    LPSTR next = LPSTR (Src + bwidth) ;
    LPSTR src ;

#ifndef WIN32
    if (FP_SEG(Src) != FP_SEG(next)) {
      hmemcpy (Line,Src,bwidth) ;
      src = Line ;
      }
    else
#endif
      src = Src ;

    for (int j = width - 1; j >= 0 ; j--) {
      *(Ptrs[j]) = *src++ ;
      if (Flags[j]) Ptrs[j] = LPSTR ((char huge *) Ptrs[j] + 1);
      else          (Ptrs[j])++ ;
      }
    Src = next ;
    }
  // Nun noch den Header umstellen
  lpnbi->biWidth = height ;
  lpnbi->biHeight = width ;

  // Und die nicht mehr benoetigten Daten umstellen
  GlobalFree (hwholeDIB);
  hwholeDIB = NULL;
  SetDIB(hGRes);
  GlobalFree (hGLine);
  GlobalFree (hGFlags);
  GlobalFree (hGPtrs);
  }

DLLExport GLOBALHANDLE _export WINAPI RotateImage(GLOBALHANDLE hDIB)
  {
  // Speicher anlegen
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
  if (lpbi->biBitCount != 8) {
    // derzeit nur fuer 256 Farben Bilder
    GlobalUnlock(hDIB);
    return hDIB;
    }
  lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  char huge *Src = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
  int width   = int (lpbi->biWidth);
  int height  = int (lpbi->biHeight);
  int bwidth  = int (ByteWidth (width,lpbi->biBitCount));
  int nbwidth = int (ByteWidth (height,lpbi->biBitCount));
  GLOBALHANDLE hGLine = GlobalAlloc (GMEM_MOVEABLE,bwidth);
  GLOBALHANDLE hGFlags = GlobalAlloc (GMEM_MOVEABLE,width * sizeof(BYTE));
  GLOBALHANDLE hGPtrs = GlobalAlloc (GMEM_MOVEABLE,width * sizeof(LPSTR));
  GLOBALHANDLE hGRes = GlobalAlloc (GMEM_MOVEABLE,(LONG (width) * LONG(nbwidth))
                                     + lpbi->biSize + dwColorTableSize);

  // Zeiger Initialisieren
  LPSTR *Ptrs = (LPSTR *) GlobalLock (hGPtrs);
  LPSTR Line  = LPSTR(GlobalLock (hGLine));
  LPSTR Flags = LPSTR(GlobalLock (hGFlags));
  LPBITMAPINFOHEADER lpnbi = (LPBITMAPINFOHEADER)GlobalLock(hGRes);
  lmemcpy(lpnbi, lpbi, int(lpbi->biSize + dwColorTableSize));
  char huge *Res = ((LPSTR)lpnbi) + lpbi->biSize + dwColorTableSize;
  LPSTR h = LPSTR (Res);
  for (int i = 0 ; i < width ; i++) {
    Ptrs[i] = h ;
    LPSTR hn = LPSTR ((char huge *) h + nbwidth);

#ifndef WIN32
      Flags[i] = (FP_SEG(h) != FP_SEG(hn)) ; // Kontrolle, ob Segmentsprung
#else
      Flags[i] = FALSE;
#endif

    h = hn ;
    }

  for (i = 0 ; i < height ; i++) {
    LPSTR next = LPSTR (Src + bwidth) ;
    LPSTR src ;

#ifndef WIN32
    if (FP_SEG(Src) != FP_SEG(next)) {
      hmemcpy (Line,Src,bwidth) ;
      src = Line ;
      }
    else
#endif
      src = Src ;

    for (int j = width - 1; j >= 0 ; j--) {
      *(Ptrs[j]) = *src++ ;
      if (Flags[j]) Ptrs[j] = LPSTR ((char huge *) Ptrs[j] + 1);
      else          (Ptrs[j])++ ;
      }
    Src = next ;
    }
  for ( ; i < nbwidth ; i++) {
    for (int j = width - 1; j >= 0 ; j--) {
      *(Ptrs[j]) = '\0';
      if (Flags[j]) Ptrs[j] = LPSTR ((char huge *) Ptrs[j] + 1);
      else          (Ptrs[j])++ ;
      }
    }

  // Nun noch den Header umstellen
  lpnbi->biWidth = height ;
  lpnbi->biHeight = width ;

  // Und die nicht mehr benoetigten Daten freigeben
  GlobalUnlock (hDIB);
  GlobalUnlock (hGLine);
  GlobalUnlock (hGFlags);
  GlobalUnlock (hGPtrs);
  GlobalUnlock (hGRes);
  GlobalFree (hDIB);
  GlobalFree (hGLine);
  GlobalFree (hGFlags);
  GlobalFree (hGPtrs);
  return hGRes;
  }

