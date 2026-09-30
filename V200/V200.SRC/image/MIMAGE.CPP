/////////////////////////////////////////////////////////////////////
//
//      Arbeiten mit den Tiff - Files
//
/////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/image/rev/mimage.cpv   1.15   18 Nov 1999 18:02:24   Martin  $
// $Log:   P:/marille/clinicum/image/rev/mimage.cpv  $
// 
//    Rev 1.15   18 Nov 1999 18:02:24   Martin
// auch in MapChange() die neue Logik mit den Paletten
// (PAL_IND funktioniert leider nicht)
// 
//    Rev 1.14   17 Aug 1999 11:15:38   Martin
// nicht mehr ueber DIB_PAL_COLORS gehen, Paint und Print zusammengefuehrt
// 
//    Rev 1.13   20 Nov 1998 14:12:40   Martin
// Drucken geht jetzt besser
// 
//    Rev 1.12   13 Oct 1998 13:35:16   Martin
// VC6 Type Casts
// 
//    Rev 1.11   23 Mar 1998 22:44:40   Martin
// Export
// 
//    Rev 1.10   03 Mar 1998 20:04:50   Martin
// True Color
// 
//    Rev 1.9   18 Aug 1997 18:05:58   Martin
// VTO Formular-faehig
// 
//    Rev 1.8   18 Mar 1997 18:20:56   Martin
// GetGlobalMem -> GetGlobMem
// 
//    Rev 1.7   04 Feb 1996 18:36:56   HANNES
// 
//    Rev 1.6   04 Feb 1996 17:36:48   HANNES
// 
//    Rev 1.5   02 Feb 1996 10:49:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   14 Aug 1995 09:28:28   HANNES
// 
//    Rev 1.3   02 Mar 1995 15:38:38   HANNES
// 
//    Rev 1.2   08 Dec 1994 21:48:32   HANNES
// 
//    Rev 1.1   17 Oct 1994 15:02:36   HANNES
// Synchronisation mit Marille
// 
//    Rev 1.0   24 Jun 1994 16:50:58   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.24   13 Apr 1994 20:44:26   MARTIN
// Teile in image.hpp verlagert,
// kleine Aenderungen fuer morphing
// 
//    Rev 1.23   16 Mar 1994 10:29:48   MARTIN
// Fehler bei CalcColorHisto (nur bei HPScanJet II Farbbildern)
// 
//    Rev 1.22   10 Mar 1994 11:21:34   MARTIN
// Weichteil in Bild malen
// 
//    Rev 1.21   02 Mar 1994 20:57:56   MARTIN
// farbige Bilder
// 
//    Rev 1.20   07 Feb 1994 15:40:30   HANNES
// No change.
// 
//    Rev 1.19   07 Feb 1994 14:56:00   HANNES
// new,delete auf FAR PASCAL umgeaendert
// 
//    Rev 1.18   04 Feb 1994 16:45:38   MARTIN
// PixelsPerMeter geaendert
// 
//    Rev 1.17   07 Jan 1994 12:18:00   HANNES
// WaitWin in die dmwapi verlegt -> Funktionsprototypen der Filterfunktionen
// haben sich geaendert, Wartefenster wird direkt in den Filterfunktionen
// aufgerufen
// 
//    Rev 1.16   29 Nov 1993 08:59:30   MARTIN
// Zeichnen des Hintergrundes beim Umrechnen in BMPs
// 
//    Rev 1.15   03 Nov 1993 17:16:12   MARTIN
// Sanduhr bei Device Dependent Bitmap Berechnung
// 
//    Rev 1.14   08 Oct 1993 17:15:16   MARTIN
// bi*pelsPerMeter wenn 0 auf 100 dpi gesetzt
// 
//    Rev 1.13   06 Oct 1993 09:47:34   MARTIN
// Bilder verschiedere Art
// 
//    Rev 1.12   22 Sep 1993 10:58:30   MARTIN
// Version nach St. Poelten
// 
//    Rev 1.11   27 Aug 1993 16:48:40   MARTIN
// LocalContrast optimiert
// 
//    Rev 1.10   25 Aug 1993 15:57:28   MARTIN
// Speicherfreigabe
// 
//    Rev 1.9   23 Aug 1993 18:48:06   MARTIN
// Image-Umstellung (Native-Mode, DIBs)
// 
//    Rev 1.8   02 Aug 1993 17:56:34   MARTIN
// lokale Kontrastanpassung
// 
//    Rev 1.7   07 Jul 1993 17:12:42   MARTIN
// Palettenhandling, SetContrast
// 
//    Rev 1.6   05 Apr 1993 10:44:38   HANNES
// ???
// 
//    Rev 1.5   22 Feb 1993 17:25:48   HANNES
// Vergleich des Massstabes der BartBitmaps
// 
//    Rev 1.4   29 Jan 1993 19:09:08   HANNES
// Implementierung von der Interpretation von Photointerprete
// 
//    Rev 1.3   13 Dec 1992 20:04:48   HANNES
// Korrektur des Querleg - Algorytmus
// 
//    Rev 1.2   07 Dec 1992 14:21:50   HANNES
// Einbauen der 270 Grad Drehung
// 
//    Rev 1.1   03 Dec 1992 15:08:06   HANNES
// Verbesserter Check ob tw. Neuzeichnen noetig (Windows ist doch zu bloed)
// 
//    Rev 1.0   02 Dec 1992 16:23:30   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include "dds32.h"

#include "l_bitmap.h"
#define LT_SUPPORT_GIF "78BY1jl78"
#define LT_SUPPORT_TIF "oam5302FDio"

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#define MIMAGE_CLASS
#include "image.hpp"
#include "math.h"
#define MODULENUM 33
#include "winass.hpp"
#include "waitwin.hpp"

extern DLLExport int _export WINAPI BitsPerPixel (void);

// aus dca_main.c (TWAIN sample source):

DLLExport WORD _export WINAPI DibNumColors (VOID FAR *pv)
{
    int                   Bits;
    LPBITMAPINFOHEADER    lpbi;
    LPBITMAPCOREHEADER    lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*    With the BITMAPINFO format headers, the size of the palette
     *    is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *    is dependent on the bits per pixel ( = 2 raised to the power of
     *    bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        Bits = lpbi->biBitCount;
    }
    else Bits = lpbc->bcBitCount;

    switch (Bits){
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

#define MAXPALETTE 256

HPALETTE CreateBIPalette (LPBITMAPINFOHEADER lpbi)
{
    LOGPALETTE FAR *pPal;
    HPALETTE       hPalette = NULL;
    WORD           nNumColors;
    int            i;
    RGBQUAD        FAR *pRgb;

    if (!lpbi)
        return NULL;

    if (lpbi->biSize != sizeof(BITMAPINFOHEADER))
        return NULL;

    /* Get a pointer to the color table and the number of colors in it */
    pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + (WORD)lpbi->biSize);
    nNumColors = DibNumColors(lpbi);

    if (nNumColors){
        // Allocate for the logical palette structure
        pPal = (LOGPALETTE FAR *)GetGlobMem(sizeof(LOGPALETTE) + nNumColors *
                                            sizeof(PALETTEENTRY));
        if (!pPal)
            return NULL;

        pPal->palNumEntries = nNumColors;
        pPal->palVersion    = 0x300;

        /* Fill in the palette entries from the DIB color table and
         * create a logical color palette.
         */
        for (i = 0; i < (int)nNumColors; i++){
            pPal->palPalEntry[i].peRed   = pRgb[i].rgbRed;
            pPal->palPalEntry[i].peGreen = pRgb[i].rgbGreen;
            pPal->palPalEntry[i].peBlue  = pRgb[i].rgbBlue;
            pPal->palPalEntry[i].peFlags = (BYTE)0;
        }

        hPalette = CreatePalette(pPal);
        FreeGlobMem(pPal);
        }
        else if (lpbi->biBitCount == 24){
                /* A 24 bitcount DIB has no color table entries so, set
                 * the number of to the maximum value (256).
                 */
                nNumColors = MAXPALETTE;
                pPal = (LOGPALETTE FAR *)GetGlobMem(sizeof(LOGPALETTE) + nNumColors * sizeof(PALETTEENTRY));
                if (!pPal)
                    return NULL;

                pPal->palNumEntries = nNumColors;
                pPal->palVersion    = 0x300;

#ifdef SIMPLE_VERSION
                BYTE  Red, Green, Blue;
                Red = Green = Blue = 0;

                /* Generate 256 (= 8*8*4) RGB combinations to fill
                 * the palette entries.
                 */
                for (i = 0; i < (int)pPal->palNumEntries; i++){
                    pPal->palPalEntry[i].peRed   = Red;
                    pPal->palPalEntry[i].peGreen = Green;
                    pPal->palPalEntry[i].peBlue  = Blue;
                    pPal->palPalEntry[i].peFlags = (BYTE)0;

                if (!(Red += 32))
                    if (!(Green += 32))
                        Blue += 64;
                }
#else
#ifdef WAHNSINNS_VERSION
                int anzcols = 0;
                for (int tiefe = 256; anzcols < 256; tiefe /= 2) {
                  for (int bstart = 256; (anzcols < 256) && (bstart != (tiefe / 2)); bstart /= 2) {
                    int b = (bstart == 256) ? 0 : (bstart / 2);
                    while ((anzcols < 256) && (b < 256)) {
                      for (int gstart = 256; (anzcols < 256) && (gstart != (tiefe / 2)); gstart /= 2) {
                        int g = (gstart == 256) ? 0 : (gstart / 2);
                        while ((anzcols < 256) && (g < 256)) {
                          for (int rstart = 256; (anzcols < 256) && (rstart != (tiefe / 2)); rstart /= 2) {
                            int r = (rstart == 256) ? 0 : (rstart / 2);
                            while ((anzcols < 256) && (r < 256)) {
                              if ((rstart == tiefe) ||
                                  (gstart == tiefe) ||
                                  (bstart == tiefe)) {
                                pPal->palPalEntry[anzcols].peRed   = r;
                                pPal->palPalEntry[anzcols].peGreen = g;
                                pPal->palPalEntry[anzcols].peBlue  = b;
                                pPal->palPalEntry[anzcols++].peFlags = (BYTE)0;
                                }
                              if (r == 0) r = 255;
                              else if (r == 255) r = rstart / 2;
                              else r += rstart;
                              }  // while r
                            }  // for rstart
                          if (g == 0) g = 255;
                          else if (g == 255) g = gstart / 2;
                          else g += gstart;
                          }  // while g
                        }  // for gstart
                      if (b == 0) b = 255;
                      else if (b == 255) b = bstart / 2;
                      else b += bstart;
                      }  // while b
                    }  // for bstart
                  }  // for tiefe
#else
                int anzcols = 0;
                // zuerst ein paar Graustufen
                #define GRAYSTEP 32
                for (i = 0; i < 256; ) {
                  pPal->palPalEntry[anzcols].peRed   = i;
                  pPal->palPalEntry[anzcols].peGreen = i;
                  pPal->palPalEntry[anzcols].peBlue  = i;
                  pPal->palPalEntry[anzcols++].peFlags = (BYTE)0;
                  if (i == (256 - GRAYSTEP))
                    i = 255;
                  else
                    i += GRAYSTEP;
                  }
                // jetzt wirds bunt
                for (int tiefe = 256; anzcols < 256; tiefe /= 2) {
                  for (int bstart = 256; (anzcols < 256) && (bstart != (tiefe / 2)); bstart /= 2) {
                    int b = (bstart == 256) ? 0 : (bstart / 2);
                    while ((anzcols < 256) && (b < 256)) {
                      for (int gstart = 256; (anzcols < 256) && (gstart != (tiefe / 2)); gstart /= 2) {
                        int g = (gstart == 256) ? 0 : (gstart / 2);
                        while ((anzcols < 256) && (g < 256)) {
                          for (int rstart = 256; (anzcols < 256) && (rstart != (tiefe / 2)); rstart /= 2) {
                            int r = (rstart == 256) ? 0 : (rstart / 2);
                            while ((anzcols < 256) && (r < 256)) {
                              if (((r != b) || (r != g)) &&
                                  ((rstart == tiefe) ||
                                   (gstart == tiefe) ||
                                   (bstart == tiefe))) {
                                pPal->palPalEntry[anzcols].peRed   = r;
                                pPal->palPalEntry[anzcols].peGreen = g;
                                pPal->palPalEntry[anzcols].peBlue  = b;
                                pPal->palPalEntry[anzcols++].peFlags = (BYTE)0;
                                }
                              if (r == 0) r = 255;
                              else if (r == 255) r = rstart / 2;
                              else r += rstart;
                              }  // while r
                            }  // for rstart
                          if (g == 0) g = 255;
                          else if (g == 255) g = gstart / 2;
                          else g += gstart;
                          }  // while g
                        }  // for gstart
                      if (b == 0) b = 255;
                      else if (b == 255) b = bstart / 2;
                      else b += bstart;
                      }  // while b
                    }  // for bstart
                  }  // for tiefe
#endif
#endif
                hPalette = CreatePalette(pPal);
                FreeGlobMem(pPal);
        }

    return hPalette;
}

static void GetPalIndex(WORD FAR *ind, RGBQUAD FAR *col, HPALETTE pal)
  {
  for (int i = 0 ; i < 256 ; i++)
    ind[i] = GetNearestPaletteIndex(pal, RGB(col[i].rgbRed, col[i].rgbGreen, col[i].rgbBlue));
  }


static BOOL TestGray(LPBITMAPINFOHEADER lpbi)
  {
  if (lpbi->biBitCount == 8) {
    int numcols = int(lpbi->biClrUsed);
    if (numcols == 0) numcols = 256;
    LPRGBQUAD colors = (LPRGBQUAD)(((LPSTR)lpbi) + lpbi->biSize);
    for (int i = 0; i < numcols; i++)
      if ((colors[i].rgbRed != colors[i].rgbGreen) ||
          (colors[i].rgbRed != colors[i].rgbBlue))
        return FALSE;
    return TRUE;
    }
  return FALSE;
  }


DLLExport void _export WINAPI mImage::GetDIBRect (LPRECT r)
  {
  r->left = r->top = 0;
  LPBITMAPINFO lpbi = LPBITMAPINFO (GlobalLock (hBMHeader));
  r->right  = int (lpbi->bmiHeader.biWidth) - 1;
  r->bottom = int (lpbi->bmiHeader.biHeight) - 1;
  GlobalUnlock (hBMHeader);
  }


/////////////////////////////////////////////////////////////////////////
//      Verschiedene Hilfoperationen
/////////////////////////////////////////////////////////////////////////
inline BYTE FAR *hugeptr_add (BYTE FAR *p1,DWORD o)
  { return (BYTE FAR *) ((BYTE huge *)p1 + o); }

inline BYTE FAR *NextScanLine (BYTE FAR *px,BYTE FAR *base)
  {
  DWORD offs = (BYTE huge *) px - (BYTE huge *) base ;
  if ((offs % 4) != 0) {
    px = hugeptr_add (px,4 - (offs % 4));
    }
  return px ;
  }

/*--------------------------
inline BYTE FAR *NextScanLine (BYTE FAR *px)
  {
  if (((FP_OFF(px)) % 4) != 0) {
    px = hugeptr_add (px,4 - (FP_OFF(px) % 4));
    }
  return px ;
  }
----------------------------*/

DLLExport void _export WINAPI mImage::GetHisto (DWORD FAR *PixCount,LPSTR wtxt)
  {
  // Lesen der Informationen
  BITMAPINFO FAR *lpbi;

  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *Px = (BYTE FAR *) GlobalLock (hDIB);
  BYTE FAR *Px0 = Px;

  // Nur fuer 256 Graustufenbilder !!!
  if ((lpbi->bmiHeader.biBitCount == 8) &&
                ((lpbi->bmiHeader.biClrUsed == 256) ||
                 (lpbi->bmiHeader.biClrUsed == 0)) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {

    for (int i = 0 ; i < lpbi->bmiHeader.biHeight ; i++) {
      if (wtxt != NULL)
        ww->SetVal (double(i) / double(lpbi->bmiHeader.biHeight));

      for (int j = 0 ; j < lpbi->bmiHeader.biWidth ; j++) {
        PixCount[*Px] ++ ;
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0);
      }
    }

  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);

  if (wtxt != NULL)
    delete ww;
  }

// Definitionen fuer die lokale Kontrastanpassung
#define NUMPIXELS 40
#define COUNT (double(NUMPIXELS) * double(NUMPIXELS) * 4.0)
#define CHANGEFACT 2
typedef int FAR *HISTO;
typedef HISTO FAR *HISTOROW;
typedef HISTOROW FAR *HISTOTABLE;

DLLExport void _export WINAPI mImage::LocalContrast (LPSTR wtxt)
  {
  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  // Lesen der Informationen
  BITMAPINFO FAR *lpbi;

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *Px = (BYTE FAR *) GlobalLock (hDIB);
  BYTE FAR *Px0 = Px;
  BYTE FAR *PxStart = Px;

  // Nur fuer 256 Graustufenbilder !!!
  if ((lpbi->bmiHeader.biBitCount == 8) &&
                ((lpbi->bmiHeader.biClrUsed == 256) ||
                 (lpbi->bmiHeader.biClrUsed == 0)) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {
#ifdef INVERTIEREN
    for (int i = 0 ; i < lpbi->bmiHeader.biHeight ; i++) {
      if (wtxt != NULL)
        ww->SetVal (double(i) / double(lpbi->bmiHeader.biHeight));

      for (int j = 0 ; j < lpbi->bmiHeader.biWidth ; j++) {
//        PixCount[*Px] ++ ;
        *Px = 255 - *Px ;
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0);
      }
#endif
    // Bild in Quadrate unterteilen
    int numx = (int(lpbi->bmiHeader.biWidth) + NUMPIXELS - 1) / NUMPIXELS;
    int numy = (int(lpbi->bmiHeader.biHeight) + NUMPIXELS - 1) / NUMPIXELS;
    HISTOTABLE histo = (HISTOTABLE)GetGlobMem(numx * sizeof(HISTOROW));
    int x, y;
    for (x = 0; x < numx; x++) {
      histo[x] = (HISTOROW)GetGlobMem(numy * sizeof(HISTO));
      for (y = 0; y < numy; y++) {
        histo[x][y] = (HISTO)GetGlobMem(256 * sizeof(int));
        }
      }
    for (y = 0; y < lpbi->bmiHeader.biHeight; y++) {
      if (wtxt != NULL)
        ww->SetVal (0.25 * double(y) / double(lpbi->bmiHeader.biHeight));
      for (x = 0 ; x < lpbi->bmiHeader.biWidth ; x++) {
        histo[x / NUMPIXELS][y / NUMPIXELS][*Px]++;
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0);
      }
    // jetzt lokale Kontrastanpassung berechnen
    double FAR *p = (double FAR *)GetGlobMem(sizeof(double) * 256);
    for (x = 0; x < (numx - 1); x++) {
      if (wtxt != NULL)
        ww->SetVal (0.25 + 0.25 * double(x) / double(numx - 1));
      for (y = 0; y < (numy - 1); y++) {
        // Berechnung der Wahrscheinlichkeiten der einzelnen Grauwerte
        for (int i = 0; i < 256; i++)
          p[i] = double (histo[x][y][i] + histo[x+1][y][i] +
                         histo[x][y+1][i] + histo[x+1][y+1][i]) / COUNT;
        // Berechnung der lokalen LookUpTable
        double s = 0.0;
        for (i = 0 ; i < 256; i++) {
          s += p[i];
          histo[x][y][i] = int(s * 255.0) - i;  // relative Aenderung merken
          }
        }
      }
    // fuer jedes Pixel gewichtetes Mittel der lokalen LUTs berechnen
    Px = PxStart;
    int lastcolbeg = (numx - 1) * NUMPIXELS;
    for (y = 0; y < lpbi->bmiHeader.biHeight; y++) {
      if (wtxt != NULL)
        ww->SetVal (0.50 + 0.50 * double(y) / double(lpbi->bmiHeader.biHeight));
      int ydiv = y / NUMPIXELS;
      int ymod = y % NUMPIXELS;
      int negymod = (NUMPIXELS - 1) - ymod;
      int ydiv1 = (ydiv > 0) ? ydiv - 1 : ydiv;
      int ydiv2 = (ydiv >= (numy - 1)) ? ydiv - 1 : ydiv;
      for (x = 0 ; x < NUMPIXELS ; x++) {
        int negxmod = (NUMPIXELS - 1) - x;
        int oldpix = (int)*Px;
        long dpix = histo[0]
                          [ydiv1]
                          [oldpix] * long(negxmod * negymod) +
                    histo[0]
                          [ydiv1]
                          [oldpix] * long(x * negymod) +
                    histo[0]
                          [ydiv2]
                          [oldpix] * long(negxmod * ymod) +
                    histo[0]
                          [ydiv2]
                          [oldpix] * long(x * ymod);
        dpix /= 4 * (NUMPIXELS - 1) * (NUMPIXELS - 1) / CHANGEFACT;
        int newpix = oldpix + int(dpix);
        if (newpix < 0) newpix = 0;
        if (newpix > 255) newpix = 255;
        *Px = BYTE(newpix);
        Px = hugeptr_add (Px,1);
        }
      for (x = NUMPIXELS ; x < lastcolbeg ; x++) {
        int xdiv = x / NUMPIXELS;
        int xmod = x % NUMPIXELS;
        int negxmod = (NUMPIXELS - 1) - xmod;
        int oldpix = (int)*Px;
        long dpix = histo[xdiv - 1]
                          [ydiv1]
                          [oldpix] * long(negxmod * negymod) +
                    histo[xdiv]
                          [ydiv1]
                          [oldpix] * long(xmod * negymod) +
                    histo[xdiv - 1]
                          [ydiv2]
                          [oldpix] * long(negxmod * ymod) +
                    histo[xdiv]
                          [ydiv2]
                          [oldpix] * long(xmod * ymod);
        dpix /= 4 * (NUMPIXELS - 1) * (NUMPIXELS - 1) / CHANGEFACT;
        int newpix = oldpix + int(dpix);
        if (newpix < 0) newpix = 0;
        if (newpix > 255) newpix = 255;
        *Px = BYTE(newpix);
        Px = hugeptr_add (Px,1);
        }
      for (x = lastcolbeg ; x < lpbi->bmiHeader.biWidth ; x++) {
        int xdiv = (numx - 2);
        int xmod = x - lastcolbeg;
        int negxmod = (NUMPIXELS - 1) - xmod;
        int oldpix = (int)*Px;
        long dpix = histo[xdiv]
                          [ydiv1]
                          [oldpix] * long(negxmod * negymod) +
                    histo[xdiv]
                          [ydiv1]
                          [oldpix] * long(xmod * negymod) +
                    histo[xdiv]
                          [ydiv2]
                          [oldpix] * long(negxmod * ymod) +
                    histo[xdiv]
                          [ydiv2]
                          [oldpix] * long(xmod * ymod);
        dpix /= 4 * (NUMPIXELS - 1) * (NUMPIXELS - 1) / CHANGEFACT;
        int newpix = oldpix + int(dpix);
        if (newpix < 0) newpix = 0;
        if (newpix > 255) newpix = 255;
        *Px = BYTE(newpix);
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0);
      }
    // Speicher wieder freigeben
    FreeGlobMem(p);
    for (x = 0; x < numx; x++) {
      for (y = 0; y < numy; y++) {
        FreeGlobMem(histo[x][y]);
        }
      FreeGlobMem(histo[x]);
      }
    FreeGlobMem(histo);
    }

  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);
  if (wtxt != NULL)
    delete ww;
  }

/*-------------------------------------------------------*/
/*      Grauwerttransformation mit Lookup - Table        */
/*-------------------------------------------------------*/
DLLExport void _export WINAPI mImage::lutTrans (BYTE FAR *lut,LPSTR wtxt)
  {
  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  BITMAPINFO FAR *lpbi;

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *Px = (BYTE FAR *) GlobalLock (hDIB);
  BYTE FAR *Px0 = Px;

  // Berechnen des Neuen Wertes nach der Formel
  // newColor = lut[oldColor] ;

  if ((lpbi->bmiHeader.biBitCount == 8) &&
                (lpbi->bmiHeader.biClrUsed == 256) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {

    for (int i = 0 ; i < lpbi->bmiHeader.biHeight ; i++) {
      if (wtxt != NULL)
        ww->SetVal (double(i) / double(lpbi->bmiHeader.biHeight));

      for (int j = 0 ; j < lpbi->bmiHeader.biWidth ; j++) {
        *Px = lut[*Px] ;
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0) ;
      }
    }


  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);

  if (wtxt != NULL)
    delete ww;
  }

/*--------------------------------------------------------*/
/*      2dim. Lineare Filter mit Dimension 3x3            */
/*--------------------------------------------------------*/
BYTE FAR *GetLinePtr (BYTE FAR *base,int line,int bytesperline)
  {
  return hugeptr_add (base,DWORD(line) * DWORD(bytesperline));
  }

void GetLine (BYTE FAR *dest,BYTE FAR *base,int line,int bytesperline)
  {
  BYTE FAR *source = GetLinePtr (base,line,bytesperline);
  for (int i = 0 ; i < bytesperline ; i++) {
    *dest ++ = *source ;
    source = hugeptr_add (source,1);
    }
  }

DLLExport void _export WINAPI mImage::linFlt (Filter FAR *f,LPSTR wtxt)
  {
  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  BITMAPINFO FAR *lpbi;

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *PxBase = (BYTE FAR *) GlobalLock (hDIB);

  if ((lpbi->bmiHeader.biBitCount == 8) &&
                (lpbi->bmiHeader.biClrUsed == 256) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {
    int xsize = int (lpbi->bmiHeader.biWidth);
    int bytesperline;
    if (xsize % 4 != 0)
      bytesperline = ((xsize / 4) + 1) * 4 ;
    else
      bytesperline = xsize ;

    // Arbeitsspeicher (3 Zeilen des Orginalbildes)
    GLOBALHANDLE hGW = GlobalAlloc (GHND,sizeof (BYTE) * bytesperline * 3) ;
    BYTE FAR *l1 = (BYTE FAR *) GlobalLock (hGW) ;
    BYTE FAR *l2 = l1 + bytesperline ;
    BYTE FAR *l3 = l2 + bytesperline ;

    // Vorbereitungen
    GetLine (l2,PxBase,0,bytesperline);
    GetLine (l3,PxBase,1,bytesperline);

    for (int j = 1 ; j < lpbi->bmiHeader.biHeight - 1 ; j++) {
      if (wtxt != NULL)
        ww->SetVal (double(j) / double(lpbi->bmiHeader.biHeight));

      int j1 = j+1;
      // Zeilen Umordnen
      memcpy (l1,l2,bytesperline);
      memcpy (l2,l3,bytesperline);
      GetLine (l3,PxBase,j1,bytesperline);
      BYTE FAR *Px = GetLinePtr (PxBase,j,bytesperline);
      Px = hugeptr_add (Px,1);
      for (int k = 1 ; k < xsize - 1 ; k++) {
        int Color = int (l1[k-1]) * f->a[0][0];
        Color += int (l1[k]) * f->a[0][1] ;
        Color += int (l1[k+1]) * f->a[0][2] ;
        Color += int (l2[k-1]) * f->a[1][0];
        Color += int (l2[k]) * f->a[1][1] ;
        Color += int (l2[k+1]) * f->a[1][2] ;
        Color += int (l3[k-1]) * f->a[2][0];
        Color += int (l3[k]) * f->a[2][1] ;
        Color += int (l3[k+1]) * f->a[2][2] ;
        Color /= f->fct ;
        if (Color < 0) Color = 0 ;
        if (Color > 255) Color = 255 ;
        *Px = BYTE (Color);
        Px = hugeptr_add (Px,1);
        }
      }

    // fertig
    GlobalUnlock (hGW);
    GlobalFree (hGW);
    }

  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);

  if (wtxt != NULL)
    delete ww;
  }

BYTE GetMid (BYTE FAR *l1,BYTE FAR *l2,BYTE FAR *l3)
  {
  // Jeweils 3 Element jedes Arrays werden verwendet, diese werden dann
  // sortiert und das Element 4 des so sortierten Arrays wird verwendet
  int i ;
  BYTE res[9] ;
  for (i = 0 ; i < 3 ; i++) {
    res[i] = l1[i] ;
    res[3+i] = l2[i] ;
    res[6+i] = l3[i] ;
    }
  for (i = 0 ; i < 8 ; i++) {
    int j ;
    for (j = i + 1 ; j < 9 ; j++) {
      if (res[j] < res[i]) {
        BYTE h = res[i];
        res[i] = res[j];
        res[j] = h ;
        }
      }
    }
  return res [4] ;
  }

DLLExport void _export WINAPI mImage::MedianFlt (LPSTR wtxt)
  {
  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  BITMAPINFO FAR *lpbi;

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *PxBase = (BYTE FAR *) GlobalLock (hDIB);

  if ((lpbi->bmiHeader.biBitCount == 8) &&
                (lpbi->bmiHeader.biClrUsed == 256) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {
    int xsize = int (lpbi->bmiHeader.biWidth);
    int bytesperline;
    if (xsize % 4 != 0)
      bytesperline = ((xsize / 4) + 1) * 4 ;
    else
      bytesperline = xsize ;

    // Arbeitsspeicher (3 Zeilen des Orginalbildes)
    GLOBALHANDLE hGW = GlobalAlloc (GHND,sizeof (BYTE) * bytesperline * 3) ;
    BYTE FAR *l1 = (BYTE FAR *) GlobalLock (hGW) ;
    BYTE FAR *l2 = l1 + bytesperline ;
    BYTE FAR *l3 = l2 + bytesperline ;

    // Vorbereitungen
    GetLine (l2,PxBase,0,bytesperline);
    GetLine (l3,PxBase,1,bytesperline);

    for (int j = 1 ; j < lpbi->bmiHeader.biHeight - 1 ; j++) {
      if (wtxt != NULL)
        ww->SetVal (double(j) / double(lpbi->bmiHeader.biHeight));

      int j1 = j+1;
      // Zeilen Umordnen
      memcpy (l1,l2,bytesperline);
      memcpy (l2,l3,bytesperline);
      GetLine (l3,PxBase,j1,bytesperline);
      BYTE FAR *Px = GetLinePtr (PxBase,j,bytesperline);
      Px = hugeptr_add (Px,1);
      for (int k = 1 ; k < xsize - 1 ; k++) {
        *Px = GetMid (l1+k-1,l2+k-1,l3+k-1);
        Px = hugeptr_add (Px,1);
        }
      }

    // fertig
    GlobalUnlock (hGW);
    GlobalFree (hGW);
    }

  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);

  if (wtxt != NULL)
    delete ww;
  }

DLLExport void _export WINAPI mImage::SobelFlt (LPSTR wtxt)
  {
  WaitWin FAR *ww;
  if (wtxt != NULL)
    ww = new WaitWin (wtxt);

  BITMAPINFO FAR *lpbi;

  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Zeiger auf die Pixel - Daten
  CheckSecondDIB(TRUE);
  BYTE FAR *PxBase = (BYTE FAR *) GlobalLock (hDIB);

  if ((lpbi->bmiHeader.biBitCount == 8) &&
                (lpbi->bmiHeader.biClrUsed == 256) &&
                (lpbi->bmiHeader.biCompression == BI_RGB)) {
    int xsize = int (lpbi->bmiHeader.biWidth);
    int bytesperline;
    if (xsize % 4 != 0)
      bytesperline = ((xsize / 4) + 1) * 4 ;
    else
      bytesperline = xsize ;

    // Arbeitsspeicher (3 Zeilen des Orginalbildes)
    GLOBALHANDLE hGW = GlobalAlloc (GHND,sizeof (BYTE) * bytesperline * 3) ;
    BYTE FAR *l1 = (BYTE FAR *) GlobalLock (hGW) ;
    BYTE FAR *l2 = l1 + bytesperline ;
    BYTE FAR *l3 = l2 + bytesperline ;

    // Vorbereitungen
    GetLine (l2,PxBase,0,bytesperline);
    GetLine (l3,PxBase,1,bytesperline);

    for (int j = 1 ; j < lpbi->bmiHeader.biHeight - 1 ; j++) {
      if (wtxt != NULL)
        ww->SetVal (double(j) / double(lpbi->bmiHeader.biHeight));

      int j1 = j+1;
      // Zeilen Umordnen
      memcpy (l1,l2,bytesperline);
      memcpy (l2,l3,bytesperline);
      GetLine (l3,PxBase,j1,bytesperline);
      BYTE FAR *Px = GetLinePtr (PxBase,j,bytesperline);
      Px = hugeptr_add (Px,1);
      for (int k = 1 ; k < xsize - 1 ; k++) {
        int H1 = l1[k-1] + l1[k] + l1[k+1] ;
        int H2 = l3[k-1] + l3[k] + l3[k+1] ;
        int V1 = l1[k-1] + l2[k-1] + l3[k-1] ;
        int V2 = l1[k+1] + l2[k+1] + l3[k+1] ;
        H1 -= H2 ;
        if (H1 < 0) H1 = -H1 ;
        V1 -= V2 ;
        if (V1 < 0) V1 = -V1 ;
        H1 += V1 ;
        if (H1 > 255) H1 = 255 ;
        *Px = H1 ;
        Px = hugeptr_add (Px,1);
        }
      }

    // fertig
    GlobalUnlock (hGW);
    GlobalFree (hGW);
    }

  GlobalUnlock (hDIB);

  // Infos wieder freigeben
  GlobalUnlock (hBMHeader);

  if (wtxt != NULL)
    delete ww;
  }

DLLExport void _export WINAPI mImage::InitializeScale (LPSCALEIMAGEINFO si,double scale)
  {
  BITMAPINFO FAR *lpbi;


  si->rotDone = TRUE ;          // Ein gueltiges Image !!!

  // Laden des Headers
  //////////////////////////////////////////////////////////
  lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // Berechnen der Ausdehnung des Images (inkl. beruecksichtigung des
  // Vergroesserungsfaktors)
  si->LogRect.top = si->LogRect.left = 0 ;
  LONG XPelsPerMeter = lpbi->bmiHeader.biXPelsPerMeter;
  LONG YPelsPerMeter = lpbi->bmiHeader.biYPelsPerMeter;
  if (XPelsPerMeter == 0L) {
    if (YPelsPerMeter == 0L)
      XPelsPerMeter = LONG(double (lpbi->bmiHeader.biWidth) * 3936.0 / 700.0);
    else
      XPelsPerMeter = YPelsPerMeter;
    }
  si->LogRect.right =
                int (double (lpbi->bmiHeader.biWidth) * (
#ifdef UEBERLEGT
                25000.0
#else
                56692.91339
#endif
                / scale) / double (XPelsPerMeter));
  if (YPelsPerMeter == 0L)
    YPelsPerMeter = XPelsPerMeter;
  si->LogRect.bottom =
                int (double (lpbi->bmiHeader.biHeight) * (
#ifdef UEBERLEGT
                -25000.0
#else
                56692.91339
#endif
                / scale) / double (YPelsPerMeter));

  GlobalUnlock (hBMHeader);
  }


DLLExport void _export WINAPI mImage::GetPelsPerMeter(LPLONG x, LPLONG y)
  {
  if (hBMHeader) {
    LPBITMAPINFO lpbi = (LPBITMAPINFO) GlobalLock (hBMHeader);
    *x = lpbi->bmiHeader.biXPelsPerMeter;
    *y = lpbi->bmiHeader.biYPelsPerMeter;
    GlobalUnlock(hBMHeader);
    }
  else {
    *x = *y = -1L;
    }
  }


DLLExport void _export WINAPI mImage::SetPelsPerMeter(LONG x, LONG y)
  {
  if (hBMHeader && (x >= 0L) && (y >= 0L)) {
    LPBITMAPINFO lpbi = (LPBITMAPINFO) GlobalLock (hBMHeader);
    lpbi->bmiHeader.biXPelsPerMeter = x;
    lpbi->bmiHeader.biYPelsPerMeter = y;
    GlobalUnlock(hBMHeader);
    lpbi = (LPBITMAPINFO) GlobalLock (hwholeDIB);
    lpbi->bmiHeader.biXPelsPerMeter = x;
    lpbi->bmiHeader.biYPelsPerMeter = y;
    GlobalUnlock(hwholeDIB);
    }
  }


DLLExport LONG _export WINAPI mImage::GetImgWidth(void)
  {
  LONG res = -1L;
  if (hBMHeader) {
    LPBITMAPINFO lpbi = (LPBITMAPINFO) GlobalLock (hBMHeader);
    res = lpbi->bmiHeader.biWidth;
    GlobalUnlock(hBMHeader);
    }
  return res;
  }


DLLExport LONG _export WINAPI mImage::GetImgHeight(void)
  {
  LONG res = -1L;
  if (hBMHeader) {
    LPBITMAPINFO lpbi = (LPBITMAPINFO) GlobalLock (hBMHeader);
    res = lpbi->bmiHeader.biHeight;
    GlobalUnlock(hBMHeader);
    }
  return res;
  }


/*----------------------------------------------------------------*/
/* Arbeiten mit den Teilbitmaps                                   */
/*----------------------------------------------------------------*/
BitmapCollection::BitmapCollection (HPALETTE hPal,int vd,int hd)
  {
  hDibPal = hPal;
  if ((vd * hd < MAXBITMAPS) && (vd > 0) && (hd > 0)) {
    VertDim = vd ;
    HorDim = hd ;
    }
  else {
    VertDim = HorDim = 6;
    }
  }

BitmapCollection::~BitmapCollection ()
  {
  for (int i = 0 ; i < VertDim * HorDim ; i++)
    if (bmps[i]) delete bmps[i];
  }

void BitmapCollection::IniParts()
  {
  for (int i = 0 ; i < VertDim * HorDim ; i++) {
    if (bmps[i] == NULL)
      bmps[i] = new PartBitmap () ;
    }
  }

void BitmapCollection::Divide (int lview,int ldib,int FAR *pview,int FAR *pdib,int NumParts)
  {
  if (NumParts < 1) NumParts = 1 ;

  // Umrechnung view -> dib
#define F(A)  int ((LONG (A) * LONG(ldib) + LONG(lview/2)) / LONG(lview))
  *pview = lview / NumParts ;
  if (*pview * NumParts < lview) *pview += 1 ;

  int pd,ld ;
  for (int i = 0 ; i < 10 ; i++) {
    pd = F(*pview + i);
    ld = F((*pview + i) * NumParts);
    if (pd * NumParts == ld) break ;
    }
  if (i < 10) {
    *pview += i ;
    *pdib  = pd ;
    }
  else {
    *pdib = F(*pview);
    }
  }

void BitmapCollection::SetBitmapRects ()
  {
  // geg: rcWnd (top = 0,left = 0,right > 0,bottom > 0)
  //      rcDIB (top < bottom,right < top) ... Darzustellender
  //      Bereich (kann auch groesser sein als das eigentliche
  //               Bitmap)
  // ges: Aufteilung der Teilrechtecke (und zwar so, dass ein Sprung in
  //      der einen Koordinate ebenfalls einen Sprung in der anderen
  //      Koordinate mit sich bringt)
  Divide (rcWnd.right+1 ,rcDIB.right-rcDIB.left+1,&xbmplen,&xdiblen,HorDim - 1);
  Divide (rcWnd.bottom+1,rcDIB.bottom-rcDIB.top+1,&ybmplen,&ydiblen,VertDim - 1);
  for (int i = 0 ; i < HorDim ; i++) {
    for (int j = 0 ; j < VertDim ; j++) {
      RECT prcWnd,prcDIB;
      prcWnd.left = i * xbmplen;    prcWnd.right  = prcWnd.left + xbmplen - 1;
      prcWnd.top  = j * ybmplen;    prcWnd.bottom = prcWnd.top  + ybmplen - 1;
      prcDIB.left = rcDIB.left + i * xdiblen ;
                prcDIB.right  = prcDIB.left + xdiblen - 1;
      prcDIB.top  = rcDIB.top  + j * ydiblen ;
                prcDIB.bottom = prcDIB.top  + ydiblen - 1;
      bmps[j * HorDim + i]->SetWndRect (&prcWnd);
      bmps[j * HorDim + i]->SetDIBRect (&prcDIB);
      }
    }
  }

void BitmapCollection::Prepare (
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                               )
  {
  IniParts();
  SetWndRect (lprcWnd);
  SetDIBRect (lprcDIB);
  SetVisibleDIBRect (lprcDIBvisible);
  SetBitmapRects ();
  GetBitmaps (hdc,lprcDIBvisible,lprcfullDIB,lpbits,lpbi);
  }

void BitmapCollection::ScrollLeft (
        int dx,         // Ausmass des Scrollens
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                                  )
  {
  int i,j,k;
  // Alle Bitmaps nach links verschieben
  for (i = 0 ; i < HorDim * VertDim ; i++) {
    bmps[i]->Move (dx,0);
    }
  // vordere Spalten, die nicht mehr sichtbar sind, werden geloescht
  // und die hinteren nach links geschoben
  for (i = 0 ; i < HorDim ; i++) {
    RECT rcIntersection;
    IntersectRect (&rcIntersection,&bmps[0]->rcDest,lprcWnd);
    if (IsRectEmpty(&rcIntersection)) {
      for (j = 0 ; j < VertDim ; j++) {
        delete bmps[j * HorDim] ;
        for (k = 0 ; k < HorDim - i - 1; k++)
          bmps[j * HorDim + k] = bmps[j * HorDim + k + 1] ;
        bmps[j * HorDim + k] = NULL ;
        }
      }
    else break ;
    }
  // Hintere Spalten neu berechnen
  if (i == HorDim) {
    // Da ist nichts mehr uebrig geblieben
    Prepare (hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi);
    }
  else {
    for (k = HorDim - i ; k < HorDim ; k++) {
      for (j = 0 ; j < VertDim ; j++) {
        RECT prcWnd,prcDIB;
        CopyRect (&prcWnd,&bmps[j * HorDim + k - 1]->rcDest);
        CopyRect (&prcDIB,&bmps[j * HorDim + k - 1]->rcSource);
        OffsetRect (&prcWnd,xbmplen,0);
        OffsetRect (&prcDIB,xdiblen,0);
        bmps[j * HorDim + k] = new PartBitmap ();
        bmps[j * HorDim + k]->SetWndRect (&prcWnd);
        bmps[j * HorDim + k]->SetDIBRect (&prcDIB);
        bmps[j * HorDim + k]->GetBitmap(hdc,lprcDIBvisible,lprcfullDIB,lpbits,lpbi,hDibPal);
        }
      }
    }
  }

void BitmapCollection::ScrollRight (
        int dx,         // Ausmass des Scrollens
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                                  )
  {
  int i,j,k;
  // Alle Bitmaps nach rechts verschieben
  for (i = 0 ; i < HorDim * VertDim ; i++) {
    bmps[i]->Move (dx,0);
    }
  // hintere Spalten, die nicht mehr sichtbar sind, werden geloescht
  // und die vorderen nach rechts geschoben
  for (i = HorDim - 1 ; i > 0 ; i--) {
    RECT rcIntersection;
    IntersectRect (&rcIntersection,&bmps[HorDim - 1]->rcDest,lprcWnd);
    if (IsRectEmpty(&rcIntersection)) {
      for (j = 0 ; j < VertDim ; j++) {
        delete bmps[j * HorDim + HorDim - 1] ;
        for (k = HorDim - 1 ; k > 0 ; k--)
          bmps[j * HorDim + k] = bmps[j * HorDim + k - 1] ;
        bmps[j * HorDim + 0] = NULL ;
        }
      }
    else break ;
    }
  // vordere Spalten neu berechnen
  if (i == 0) {
    // Da ist nichts mehr uebrig geblieben
    Prepare (hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi);
    }
  else {
    for (k = HorDim - 1 - i ; k > 0 ; k--) {
      for (j = 0 ; j < VertDim ; j++) {
        RECT prcWnd,prcDIB;
        CopyRect (&prcWnd,&bmps[j * HorDim + k]->rcDest);
        CopyRect (&prcDIB,&bmps[j * HorDim + k]->rcSource);
        OffsetRect (&prcWnd,-xbmplen,0);
        OffsetRect (&prcDIB,-xdiblen,0);
        bmps[j * HorDim + k - 1] = new PartBitmap ();
        bmps[j * HorDim + k - 1]->SetWndRect (&prcWnd);
        bmps[j * HorDim + k - 1]->SetDIBRect (&prcDIB);
        bmps[j * HorDim + k - 1]->GetBitmap(hdc,lprcDIBvisible,lprcfullDIB,lpbits,lpbi,hDibPal);
        }
      }
    }
  }

void BitmapCollection::ScrollUp (
        int dy,         // Ausmass des Scrollens
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                                  )
  {
  int i,j,k;
  // Alle Bitmaps nach oben verschieben
  for (i = 0 ; i < HorDim * VertDim ; i++) {
    bmps[i]->Move (0,dy);
    }
  // obere Spalten, die nicht mehr sichtbar sind, werden geloescht
  // und die unteren nach oben geschoben
  for (i = 0 ; i < VertDim ; i++) {
    RECT rcIntersection;
    IntersectRect (&rcIntersection,&bmps[0]->rcDest,lprcWnd);
    if (IsRectEmpty(&rcIntersection)) {
      for (j = 0 ; j < HorDim ; j++) {
        delete bmps[j] ;
        for (k = 0 ; k < VertDim - 1 ; k++)
          bmps[k * HorDim + j] = bmps[(k + 1) * HorDim + j] ;
        bmps[k * HorDim + j] = NULL ;
        }
      }
    else break ;
    }
  // untere Spalten neu berechnen
  if (i == VertDim) {
    // Da ist nichts mehr uebrig geblieben
    Prepare (hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi);
    }
  else {
    for (k = VertDim - i ; k < VertDim ; k++) {
      for (j = 0 ; j < HorDim ; j++) {
        RECT prcWnd,prcDIB;
        CopyRect (&prcWnd,&bmps[(k - 1) * HorDim + j]->rcDest);
        CopyRect (&prcDIB,&bmps[(k - 1) * HorDim + j]->rcSource);
        OffsetRect (&prcWnd,0,ybmplen);
        OffsetRect (&prcDIB,0,ydiblen);
        bmps[k * HorDim + j] = new PartBitmap ();
        bmps[k * HorDim + j]->SetWndRect (&prcWnd);
        bmps[k * HorDim + j]->SetDIBRect (&prcDIB);
        bmps[k * HorDim + j]->GetBitmap(hdc,lprcDIBvisible,lprcfullDIB,lpbits,lpbi,hDibPal);
        }
      }
    }
  }

void BitmapCollection::ScrollDown (
        int dy,         // Ausmass des Scrollens
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                                  )
  {
  int i,j,k;
  // Alle Bitmaps nach unten verschieben
  for (i = 0 ; i < HorDim * VertDim ; i++) {
    bmps[i]->Move (0,dy);
    }
  // obere Spalten, die nicht mehr sichtbar sind, werden geloescht
  // und die unteren nach oben geschoben
  for (i = VertDim - 1; i > 0 ; i--) {
    RECT rcIntersection;
    IntersectRect (&rcIntersection,&bmps[(VertDim - 1) * HorDim]->rcDest,lprcWnd);
    if (IsRectEmpty(&rcIntersection)) {
      for (j = 0 ; j < HorDim ; j++) {
        delete bmps[(VertDim - 1) * HorDim + j] ;
        for (k = VertDim - 1 ; k > 0 ; k--)
          bmps[k * HorDim + j] = bmps[(k - 1) * HorDim + j] ;
        bmps[j] = NULL ;
        }
      }
    else break ;
    }
  // Obere Spalten neu berechnen
  if (i == 0) {
    // Da ist nichts mehr uebrig geblieben
    Prepare (hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi);
    }
  else {
    for (k = VertDim - 1 - i ; k > 0 ; k--) {
      for (j = 0 ; j < HorDim ; j++) {
        RECT prcWnd,prcDIB;
        CopyRect (&prcWnd,&bmps[k * HorDim + j]->rcDest);
        CopyRect (&prcDIB,&bmps[k * HorDim + j]->rcSource);
        OffsetRect (&prcWnd,0,-ybmplen);
        OffsetRect (&prcDIB,0,-ydiblen);
        bmps[(k - 1) * HorDim + j] = new PartBitmap ();
        bmps[(k - 1) * HorDim + j]->SetWndRect (&prcWnd);
        bmps[(k - 1) * HorDim + j]->SetDIBRect (&prcDIB);
        bmps[(k - 1) * HorDim + j]->GetBitmap(hdc,lprcDIBvisible,lprcfullDIB,lpbits,lpbi,hDibPal);
        }
      }
    }
  }

void BitmapCollection::CheckScroll (
        HDC hdc,        // Ausgabekontext
        LPRECT lprcWnd, // Ausgabefenster
        LPRECT lprcDIB, // Darzustellender Bereich des DIB
        LPRECT lprcfullDIB,     // Volles DIB
        LPRECT lprcDIBvisible,  // DIB in Fensterkoordinaten
        char huge *lpbits,      // Image Daten
        LPBITMAPINFO lpbi       // Bitmap - Info
                               )
  {
  if (lprcDIBvisible->left < rcDIBvisible.left) {
    ScrollLeft (lprcDIBvisible->left - rcDIBvisible.left,
                   hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi
               );
    SetVisibleDIBRect (lprcDIBvisible);
    }
  else if (lprcDIBvisible->left > rcDIBvisible.left) {
    ScrollRight (lprcDIBvisible->left - rcDIBvisible.left,
                   hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi
                );
    SetVisibleDIBRect (lprcDIBvisible);
    }

  if (lprcDIBvisible->top < rcDIBvisible.top) {
    ScrollUp (lprcDIBvisible->top - rcDIBvisible.top,
                   hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi
             );
    SetVisibleDIBRect (lprcDIBvisible);
    }
  else if (lprcDIBvisible->top > rcDIBvisible.top) {
    ScrollDown (lprcDIBvisible->top - rcDIBvisible.top,
                   hdc,lprcWnd,lprcDIB,lprcfullDIB,lprcDIBvisible,lpbits,lpbi
               );
    SetVisibleDIBRect (lprcDIBvisible);
    }
  }

void BitmapCollection::GetBitmaps (
        HDC hdc,                // Ausgabe Device Kontext
        LPRECT lprcView,        // gesamtes DIB in DIB - Koordinaten
        LPRECT lprcDIB,         // Groesse des DIB
        char huge *lpbits,      // Image - Pixeldaten
        LPBITMAPINFO lpbi       // Beschreibung des DIB
                                  )
  {
  for (int i = 0 ; i < HorDim ; i++) {
    for (int j = 0 ; j < VertDim ; j++) {
      bmps[j*HorDim + i]->GetBitmap(hdc,lprcView,lprcDIB,lpbits,lpbi,hDibPal);
      }
    }
  }

void BitmapCollection::Paint (HDC hDC)
  {
  HDC hmemDC = CreateCompatibleDC (hDC);
  for (int i = 0 ; i < HorDim * VertDim ; i++)
    bmps[i]->Paint(hDC,hmemDC);
  DeleteDC (hmemDC);
  }

PartBitmap::PartBitmap ()
  {
  }

GLOBALHANDLE GetTinyDIB (char huge *bits,int left,int top,
                                        int width,int height,
                                        LONG orgwidth,WORD BitCount
                                    )
  {
  if (BitCount == 1) {
    WIN_ASSERT((left % 8) == 0);
    }
  else if (BitCount == 4) {
    WIN_ASSERT((left % 2) == 0);
    }
  left = (left * BitCount) / 8;
  LONG bytewidth = ByteWidth (width,BitCount);
  width = (int)ByteWidthNoPad (width,BitCount);
  LONG size = bytewidth * height ;
  GLOBALHANDLE res = GlobalAlloc (GMEM_MOVEABLE,size);
  char huge *dest = (char huge *) GlobalLock (res);
  char huge *source = bits + orgwidth * top + left ;
  for (int i = 0 ; i < height ; i++) {
    char huge *nextsource = source + orgwidth;
    char huge *nextdest = dest + bytewidth;

#ifndef WIN32
    if ((FP_SEG(nextsource) == FP_SEG(source)) &&
        (FP_SEG(nextdest) == FP_SEG(dest)))
#endif
      memcpy (dest,source,width);

#ifndef WIN32
    else
      hmemcpy (dest,source,width);
#endif

    dest   = nextdest ;
    source = nextsource ;
    }
  GlobalUnlock (res);
  return res;
  }


void Trans24to8 (char huge *dst,char huge *src,int width,int height,WORD FAR *palind)
  {
  LONG srcwidth = ByteWidth (width,24);
  LONG dstwidth = ByteWidth (width,8);
  for (int i = 0 ; i < height ; i++) {
    char huge *nextsrc = src + srcwidth;
    char huge *nextdst = dst + dstwidth;

#ifndef WIN32
    if ((FP_SEG(nextsrc) == FP_SEG(src)) &&
        (FP_SEG(nextdst) == FP_SEG(dst))) {
#endif

      unsigned char FAR *s = (unsigned char FAR *)src;
      unsigned char FAR *d = (unsigned char FAR *)dst;
      for (int j = 0; j < width; j++) {
#ifdef OLD_VERSION
        unsigned char b = *s++;
        unsigned char g = *s++;
        unsigned char r = *s++;
        *d++ = (unsigned char)palind[RGBIND(r,g,b)];
#else
        *d++ = (unsigned char)palind[RGBIND(s[2],s[1],s[0])];
        s += 3;
#endif
        }

#ifndef WIN32
      }
    else {
      unsigned char huge *s = (unsigned char huge *)src;
      unsigned char huge *d = (unsigned char huge *)dst;
      for (int j = 0; j < width; j++) {
        unsigned char b = *s++;
        unsigned char g = *s++;
        unsigned char r = *s++;
        *d++ = (unsigned char)palind[RGBIND(r,g,b)];
        }
      }
#endif

    src = nextsrc ;
    dst = nextdst ;
    }
  }

int AnzBitmaps;
void PartBitmap::GetBitmap (
        HDC hdc,        // Context, der zur erzeugung der Bitmaps verwendet
                        // werden kann
        LPRECT lprcView,// Gesamtes DIB in Bildschirm - Koordinaten
        LPRECT lprcDIB, // Gesamtes DIB in DIB - Koordinaten
        char huge *lpbits,
        LPBITMAPINFO lpbi,
        HPALETTE hDibPal
                           )
  {
  // Berechnen des Rechteckes des Bitmaps
  RECT rcBMP;
  IntersectRect (&rcBMP,lprcView,&rcDest);
  if (!IsRectEmpty(&rcBMP)) {
    ptleftupper.x = rcBMP.left - rcDest.left ;
    ptleftupper.y = rcBMP.top  - rcDest.top  ;
    width =  rcBMP.right  - rcBMP.left + 1;
    height = rcBMP.bottom - rcBMP.top  + 1;
    }
  else {
    ptleftupper.x = rcDest.right - rcDest.left ;
    ptleftupper.y = rcDest.bottom - rcDest.top ;
    width = height = 0;
    }
  // Berechnen des zu lesenden Rechteckes
  RECT rcDIB;
  IntersectRect (&rcDIB,lprcDIB,&rcSource);

  // Es kann losgehen
  if ((width > 0) && (height > 0)) {
    hBitmap = CreateCompatibleBitmap (hdc,width,height);
    AnzBitmaps++;
    HDC hmemDC = CreateCompatibleDC (hdc);
    HPALETTE hOldPal;
    if (hDibPal) {
      hOldPal = SelectPalette (hmemDC,hDibPal,TRUE);
      RealizePalette (hmemDC);
      }
    HBITMAP hOldBitmap = (HBITMAP)SelectObject (hmemDC,hBitmap);

    int left = rcDIB.left;
    if (lpbi->bmiHeader.biBitCount == 1)
      left = left & ~7;
    else if (lpbi->bmiHeader.biBitCount == 4)
      left = left & ~1;
    int leftoffs = rcDIB.left - left;
    int dibheight = rcDIB.bottom - rcDIB.top + 1;
    int dibwidth  = rcDIB.right  - left + 1;
    int dibtop = lprcDIB->bottom - rcDIB.top - dibheight + 1;
    GLOBALHANDLE hGtinybmp = GetTinyDIB (lpbits,left,dibtop,
                                       dibwidth,dibheight,
                                       ByteWidth (lpbi->bmiHeader.biWidth,
                                       lpbi->bmiHeader.biBitCount),
                                       lpbi->bmiHeader.biBitCount
                                      );
    LPSTR tinymem = LPSTR(GlobalLock (hGtinybmp));
    int oldwidth = int (lpbi->bmiHeader.biWidth);
    int oldheight = int (lpbi->bmiHeader.biHeight);
    lpbi->bmiHeader.biWidth = dibwidth;
    lpbi->bmiHeader.biHeight = dibheight;

    SetStretchBltMode (hmemDC,STRETCH_DELETESCANS);
    StretchDIBits (hmemDC,0,0,width,height,leftoffs,0,dibwidth - leftoffs,dibheight,
                   tinymem,lpbi,
#ifdef UEBERLEGT
                   ((lpbi->bmiHeader.biBitCount == 8) && hDibPal) ?
                     DIB_PAL_COLORS : DIB_RGB_COLORS,
#endif
                   DIB_RGB_COLORS,
                   SRCCOPY
                  );

    lpbi->bmiHeader.biWidth = oldwidth;
    lpbi->bmiHeader.biHeight = oldheight;
    GlobalUnlock (hGtinybmp);
    GlobalFree (hGtinybmp);

    if (hDibPal) {
      if (hOldPal)
        SelectPalette (hmemDC,hOldPal,TRUE);
      }
    SelectObject (hmemDC,hOldBitmap);
    DeleteDC (hmemDC);
    }
  else hBitmap = 0;
  }

void PartBitmap::Move (int dx,int dy)
  {
  OffsetRect (&rcDest,dx,dy);
  }

void PartBitmap::Paint (HDC hDC,HDC hmemDC)
  {
  HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject(WHITE_PEN));
  RECT rchlp;
  CopyRect (&rchlp,&rcDest);
  InflateRect (&rchlp,1,1);
  if (RectVisible(hDC,&rchlp)) {
    int dx,dy ;
    if (ptleftupper.x > 0)
      // Es ist links ein Streifen zu zeichen
      Rectangle (hDC,rcDest.left,rcDest.top,
                         rcDest.left+ptleftupper.x+1,rcDest.bottom+1);

    if (ptleftupper.y > 0)
      Rectangle (hDC,rcDest.left+ptleftupper.x,rcDest.top,
                     rcDest.right+1,rcDest.top + ptleftupper.y+1);

    if (ptleftupper.x + width < rcDest.right - rcDest.left + 1) {
      dx = rcDest.right - rcDest.left + 1 - ptleftupper.x - width ;
      Rectangle (hDC,rcDest.right-dx,rcDest.top+ptleftupper.y,
                     rcDest.right+1,rcDest.bottom+1);
      }
    else dx = 0 ;

    if (ptleftupper.y + height < rcDest.bottom - rcDest.top + 1) {
      dy = rcDest.bottom - rcDest.top + 1 - ptleftupper.y - height ;
      Rectangle (hDC,rcDest.left+ptleftupper.x,rcDest.bottom-dy,
                     rcDest.right-dx+1,rcDest.bottom+1);
      }

    SelectObject (hDC,hOldPen);
    if (hBitmap) {
      HBITMAP hOldBitmap = (HBITMAP)SelectObject (hmemDC,hBitmap);
      BitBlt (hDC,rcDest.left+ptleftupper.x,rcDest.top+ptleftupper.y,
                  width,height,
                  hmemDC,0,0,SRCCOPY);
      SelectObject (hmemDC,hOldBitmap);
      }
    }
  }


DLLExport void _export WINAPI mImage::Paint (
      HDC hDC,                // Device Kontext, in den zu zeichnen ist
      LPRECT lprcWnd,         // Fenstergroesse
      LPRECT lprcDIB,         // Fenstergroesse in DIB Koordinaten
      LPRECT lprcDIBVisible,  // DIB in Fensterkoordinaten
      BOOL   doPrint          // Auf den Bildschirm oder auf den Drucker ?
                              )
  {
  RECT rcfullDIB;
  GetDIBRect (&rcfullDIB);
  char huge *lpbits;
  if (!hDIB) {
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
    lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    lpbits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
    }
  else
    lpbits = LPSTR(GlobalLock (hDIB));

  BITMAPINFO FAR *lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);
  // eventuell PAL_COLORS in RGB_COLORS umwandeln
  if ((lpbi->bmiHeader.biBitCount == 8) && hDibPal) {
    LPBITMAPINFO oldlpbi = lpbi;
    lpbi = (LPBITMAPINFO)GetGlobMem(WORD(oldlpbi->bmiHeader.biSize + (256 * sizeof(RGBQUAD))));
    lmemcpy(lpbi,oldlpbi,oldlpbi->bmiHeader.biSize);
    RGBQUAD FAR *rgb = (RGBQUAD FAR *)(((LPSTR)lpbi) + lpbi->bmiHeader.biSize);
    WORD FAR *ind = (WORD FAR *)(((LPSTR)oldlpbi) + oldlpbi->bmiHeader.biSize);
    PALETTEENTRY pe;
    for (int i = 0 ; i < 256 ; i++) {
      GetPaletteEntries (hDibPal,ind[i],1,&pe);
      rgb[i].rgbRed = pe.peRed;
      rgb[i].rgbGreen = pe.peGreen;
      rgb[i].rgbBlue = pe.peBlue;
      rgb[i].rgbReserved = 0;
      }
    }

  HPALETTE hOldPal;
  if (hDibPal) {
    hOldPal = SelectPalette (hDC,hDibPal,TRUE);
    RealizePalette (hDC);
    }

  if (doPrint) {
    // Beim Drucken wird kein interne BMPs aufgebaut, sondern es wird
    // direkt mit PaintScaled gearbeitet
    int width  = LogRect.right - LogRect.left + 1;
    int height = LogRect.bottom - LogRect.top;
    if (height < 0) height -= 1 ;
    else            height += 1 ;
    SetStretchBltMode (hDC,STRETCH_DELETESCANS);
    StretchDIBits (hDC,LogRect.left,LogRect.top,
                   width,
                   height,
                   0,0,
                   int (lpbi->bmiHeader.biWidth),
                   int (lpbi->bmiHeader.biHeight),
                   lpbits,
                   lpbi,
#ifdef UEBERLEGT
                   ((lpbi->bmiHeader.biBitCount == 8) && hDibPal) ?
                     DIB_PAL_COLORS : DIB_RGB_COLORS,
#endif
                   DIB_RGB_COLORS,
                   SRCCOPY);
    }
  else {
    if ((bmc == NULL) ||
            (((bmc->rcDIBvisible.right - bmc->rcDIBvisible.left) !=
                (lprcDIBVisible->right - lprcDIBVisible->left)) ||
              ((bmc->rcDIBvisible.bottom - bmc->rcDIBvisible.top) !=
                (lprcDIBVisible->bottom - lprcDIBVisible->top))) ||
            (!lmemcmp (lprcWnd,&bmc->rcWnd,sizeof(*lprcWnd)))) {
#ifdef WITH_CROSS
      ToBusyCursor();   // das kann dauern ....
      HBRUSH cross = CreateHatchBrush(HS_DIAGCROSS, RGB(0x80,0x80,0x80));
      HBRUSH oldBrush = SelectObject(hDC, cross);
      HPEN oldPen = SelectObject(hDC, GetStockObject(NULL_PEN));
      Rectangle(hDC, lprcDIBVisible->left,
                     lprcDIBVisible->top,
                     lprcDIBVisible->right,
                     lprcDIBVisible->bottom);
      SelectObject(hDC, oldPen);
      SelectObject(hDC, oldBrush);
      DeleteObject(cross);
#endif
      if (bmc != NULL)
        delete bmc;
      if (DivFact > 0)
        bmc = new BitmapCollection(hDibPal,DivFact,DivFact);
      else
        bmc = new BitmapCollection(hDibPal);
      bmc->Prepare (hDC,lprcWnd,lprcDIB,&rcfullDIB,lprcDIBVisible,lpbits,lpbi);
      }
    else {
      bmc->CheckScroll (hDC,lprcWnd,lprcDIB,&rcfullDIB,lprcDIBVisible,lpbits,lpbi);
      }
    bmc->Paint (hDC);
    }

  if (hDibPal) {
    if (hOldPal)
      SelectPalette (hDC,hOldPal,TRUE);
    }

  if ((lpbi->bmiHeader.biBitCount == 8) && hDibPal)
    FreeGlobMem(lpbi);

  if (!hDIB)
    GlobalUnlock (hwholeDIB);
  else
    GlobalUnlock (hDIB);

  GlobalUnlock (hBMHeader);
  }

DLLExport void _export WINAPI mImage::MapChange (
      HDC hDC,                // Device Kontext, in den zu zeichnen ist
      LPRECT lprcWnd,         // Fenstergroesse
      LPRECT lprcDIB,         // Fenstergroesse in DIB Koordinaten
      LPRECT lprcDIBVisible   // DIB in Fensterkoordinaten
                                   )
  {
  RECT rcfullDIB;
  GetDIBRect (&rcfullDIB);
  char huge *lpbits;
  if (!hDIB) {
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
    lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    lpbits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
    }
  else
    lpbits = LPSTR(GlobalLock (hDIB));

  BITMAPINFO FAR *lpbi = (BITMAPINFO FAR *) GlobalLock (hBMHeader);

  // eventuell PAL_COLORS in RGB_COLORS umwandeln
  if ((lpbi->bmiHeader.biBitCount == 8) && hDibPal) {
    LPBITMAPINFO oldlpbi = lpbi;
    lpbi = (LPBITMAPINFO)GetGlobMem(WORD(oldlpbi->bmiHeader.biSize + (256 * sizeof(RGBQUAD))));
    lmemcpy(lpbi,oldlpbi,oldlpbi->bmiHeader.biSize);
    RGBQUAD FAR *rgb = (RGBQUAD FAR *)(((LPSTR)lpbi) + lpbi->bmiHeader.biSize);
    WORD FAR *ind = (WORD FAR *)(((LPSTR)oldlpbi) + oldlpbi->bmiHeader.biSize);
    PALETTEENTRY pe;
    for (int i = 0 ; i < 256 ; i++) {
      GetPaletteEntries (hDibPal,ind[i],1,&pe);
      rgb[i].rgbRed = pe.peRed;
      rgb[i].rgbGreen = pe.peGreen;
      rgb[i].rgbBlue = pe.peBlue;
      rgb[i].rgbReserved = 0;
      }
    }

  HPALETTE hOldPal;
  if (hDibPal) {
    hOldPal = SelectPalette (hDC,hDibPal,TRUE);
    RealizePalette (hDC);
    }

  if ((bmc == NULL) ||
          (((bmc->rcDIBvisible.right - bmc->rcDIBvisible.left) !=
              (lprcDIBVisible->right - lprcDIBVisible->left)) ||
            ((bmc->rcDIBvisible.bottom - bmc->rcDIBvisible.top) !=
              (lprcDIBVisible->bottom - lprcDIBVisible->top)))) {
    ToBusyCursor();   // das kann dauern ....
    if (bmc != NULL)
      delete bmc;
    bmc = NULL;
    }
  else {
    bmc->CheckScroll (hDC,lprcWnd,lprcDIB,&rcfullDIB,lprcDIBVisible,lpbits,lpbi);
    }

  if (hDibPal) {
    if (hOldPal)
      SelectPalette (hDC,hOldPal,TRUE);
    }

  if ((lpbi->bmiHeader.biBitCount == 8) && hDibPal)
    FreeGlobMem(lpbi);

  if (!hDIB)
    GlobalUnlock (hwholeDIB);
  else
    GlobalUnlock (hDIB);

  GlobalUnlock (hBMHeader);
  }

DLLExport _export WINAPI mImage::~mImage ()
  {
  if (hwholeDIB)   GlobalFree (hwholeDIB);
  if (hDIB)        GlobalFree (hDIB);
  if (hBMHeader)   GlobalFree (hBMHeader);
  if (hColorHisto) GlobalFree (hColorHisto);
  if (bmc)         delete (bmc);
  }

DLLExport _export WINAPI mImage::mImage ()
  {
  DivFact = -1;
  }

DLLExport void _export WINAPI mImage::SetDIB (GLOBALHANDLE newDIB, LPSTR FileName)
  {
  if ((hwholeDIB != newDIB) && hwholeDIB) GlobalFree (hwholeDIB);
  WIN_ASSERT(FileName == NULL);
  hwholeDIB = newDIB;
  if (hBMHeader   != NULL) GlobalFree(hBMHeader  ), hBMHeader   = NULL;
  if (hDIB        != NULL) GlobalFree(hDIB       ), hDIB        = NULL;
  if (hColorHisto != NULL) GlobalFree(hColorHisto), hColorHisto = NULL;
  hDibPal = NULL;
  if (hwholeDIB   != NULL) {
    SplitDIB();
    CalcColorHisto();
    }
  }

// hwholeDIB in hBMHeader und hDIB aufteilen
void mImage::SplitDIB()
  {
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
  if ((lpbi->biBitCount == 24) && (BitsPerPixel() == 8))
    hBMHeader = GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER) + 256 * sizeof(WORD));
  else
    hBMHeader = GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER) + dwColorTableSize);
  BITMAPINFOHEADER FAR *lpnbi = (BITMAPINFOHEADER FAR *) GlobalLock(hBMHeader);
  lmemset(lpnbi, 0, sizeof(BITMAPINFOHEADER));
  lmemcpy(lpnbi, lpbi, int(lpbi->biSize));
  lpnbi->biSize = sizeof(BITMAPINFOHEADER);
  if ((lpbi->biBitCount == 24) && (BitsPerPixel() == 8)) {
    lpnbi->biBitCount = 8;
    lpnbi->biClrUsed = 256;
    lpnbi->biSizeImage = ByteWidth(lpnbi->biWidth,lpnbi->biBitCount)*lpnbi->biHeight;
    }
  else {
    lmemcpy(((LPSTR)lpnbi) + sizeof(BITMAPINFOHEADER),
            ((LPSTR)lpbi) + lpbi->biSize, (WORD)dwColorTableSize);
    }
  IsGray = TestGray(lpbi);
  GlobalUnlock(hBMHeader);
  GlobalUnlock(hwholeDIB);
  }

// hDIB noetigenfalls erzeugen (z.B. fuer Filter)
void mImage::CheckSecondDIB(BOOL DoCopy)
  {
  if (!hDIB) {
    WIN_ASSERT(hBMHeader);
    BITMAPINFOHEADER FAR *lpnbi = (BITMAPINFOHEADER FAR *) GlobalLock(hBMHeader);
    hDIB = GlobalAlloc(GMEM_MOVEABLE,lpnbi->biSizeImage);
    GlobalUnlock(hBMHeader);
    if (DoCopy) {
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
      lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
      DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
      LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
      LPSTR lpnBits = (LPSTR)GlobalLock(hDIB);
      hmemcpy(lpnBits, lpBits, lpbi->biSizeImage);
      GlobalUnlock(hDIB);
      }
    GlobalUnlock(hwholeDIB);
    }
  }

DLLExport void _export WINAPI mImage::SetPal(HPALETTE pal, GLOBALHANDLE hPalInd, BOOL doMorph)
  {
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
  BITMAPINFOHEADER FAR *lpnbi = (BITMAPINFOHEADER FAR *) GlobalLock(hBMHeader);
  if ((BitsPerPixel() == 8) || IsGray)
    hDibPal = pal;
  else
    hDibPal = NULL;
  WORD FAR *palind = (WORD FAR *)(((LPSTR)lpnbi) + sizeof(BITMAPINFOHEADER));
  if ((lpbi->biBitCount == 8) && (hDibPal != NULL)) {
    GetPalIndex(palind,
                (LPRGBQUAD)(((LPSTR)lpbi) + lpbi->biSize),
                hDibPal);
    }
  else if ((lpbi->biBitCount == 24) && (BitsPerPixel() == 8)) {
    for (int i = 0; i < 256; i++)
      palind[i] = i;
    }
  if (!doMorph) {
    if ((lpbi->biBitCount == 24) && (BitsPerPixel() == 8)) {
      // umwandeln in 256 Farben Bild
      CheckSecondDIB(FALSE);
      WIN_ASSERT(hPalInd != NULL);
      palind = (WORD FAR *)GlobalLock(hPalInd);
      LPSTR lpnBits = (LPSTR)GlobalLock(hDIB);
      Trans24to8(lpnBits, lpBits, (int)lpnbi->biWidth, (int)lpnbi->biHeight, palind);
      GlobalUnlock(hPalInd);
      GlobalUnlock(hDIB);
      }
    }
  GlobalUnlock(hBMHeader);
  GlobalUnlock(hwholeDIB);
  }

DLLExport GLOBALHANDLE _export WINAPI mImage::ReadPart (GLOBALHANDLE hGBitInfo,GLOBALHANDLE hGbits,
        int x0,int y0,int width,int height)
  {
  // ACHTUNG: x0 muss bei 1-Bit-Bildern durch 8
  //             bzw. bei 4-Bit-Bildern durch 2 teilbar sein !!!!

  LPBITMAPINFO lpbi = (LPBITMAPINFO) GlobalLock (hGBitInfo);
  char huge *bits = (char huge *) GlobalLock (hGbits);
  y0 = int (lpbi->bmiHeader.biHeight) - y0 - height + 1;
  GLOBALHANDLE res = GetTinyDIB (bits,x0,y0,width,height,
                                        ByteWidth(lpbi->bmiHeader.biWidth,
                                        lpbi->bmiHeader.biBitCount),
                                        lpbi->bmiHeader.biBitCount
                                );
  lpbi->bmiHeader.biWidth  = width;
  lpbi->bmiHeader.biHeight = height;
  GlobalUnlock (hGbits);
  GlobalUnlock (hGBitInfo);
  return res;
  }

DLLExport void _export WINAPI mImage::ResetBMPs()
  {
  delete bmc;
  bmc = NULL;
  }

void GetLinTrans (double FAR *a,double FAR *b,int x1o,int x2o,int x1n,int x2n)
  {
  // x1o * a + b = x1n
  // x2o * a + b = x2n
  if ((x1o - x2o) != 0)
    *a = double (x1n - x2n) / double (x1o - x2o) ;
  else
    *a = 1.0;
  *b = double (x1n) - double (x1o) * *a ;
  }

DLLExport void _export WINAPI CalcDIBKoords (LPRECT rcView,LPRECT rcLog,LPRECT rcPhys)
  {
  double ax,ay,bx,by;
  GetLinTrans (&ax,&bx,rcPhys->left,rcPhys->right,rcLog->left,rcLog->right);
  GetLinTrans (&ay,&by,rcPhys->top,rcPhys->bottom,rcLog->top,rcLog->bottom);
  rcView->left   = int (double (rcView->left)   * ax + bx) ;
  rcView->top    = int (double (rcView->top)    * ay + by) ;
  rcView->right  = int (double (rcView->right)  * ax + bx) ;
  rcView->bottom = int (double (rcView->bottom) * ay + by) ;
  }

DLLExport UINT _export WINAPI mImage::OnPaletteChanged(HWND hWnd, BOOL ontop)
  {
  UINT changed = 0;
  if (hDibPal) {
    HDC hDC     = GetDC (hWnd);
    HPALETTE hOldPal = SelectPalette (hDC, hDibPal, TRUE);

    changed = RealizePalette (hDC);
    if (!ontop)
      UpdateColors (hDC);

    if (hOldPal)
      SelectPalette (hDC, hOldPal, TRUE);

    ReleaseDC (hWnd, hDC);
    }

  if (ontop)
    InvalidateRect(hWnd, NULL, FALSE);

  return changed;
  }


PartBitmap::~PartBitmap ()
  {
  if (hBitmap) DeleteObject (hBitmap) , AnzBitmaps--;
  }

DLLExport void FAR * _export WINAPI farObj::operator new (size_t size)
  {
  return GetGlobMem (size);
  }

DLLExport void _export WINAPI farObj::operator delete (void FAR *obj)
  {
  FreeGlobMem (obj);
  }


static BYTE OrigGrayVals[256];
static int GrayPalCount = 0;

#ifdef ALTE_VERSION

inline float ContrastFunc(float x, float h)
  {
  x = x * (float)2.0 - (float)1.0;
  if (x < 0.0)
    x = (float)-pow(-x,exp(h));
  else
    x = (float)pow(x,exp(h));
  return (x + (float)1.0) / (float)2.0;
  }


inline float BrightnessFunc(float x, float h)
  {
  return (float)pow(x,exp(h));
  }


static int CalcContrast(BYTE greyval, float c, float b)
  {
  // x muss zwischen 0.0 und 1.0 liegen (inklusive)
  float x = (float)greyval / (float)255.0;
//  int res = (int)(((ContrastFunc(x,c) + BrightnessFunc(x,b)) / 2.0) * 255.0);
//  int res = (int)(ContrastFunc(x,c) * 255.0);
//  int res = (int)(BrightnessFunc(x,b) * 255.0);
  int res = (int)(ContrastFunc(BrightnessFunc(x,b),c) * 255.0);
  if ((res < 0) || (res > 255))
    res = 256;
  return res;
  }

#else

#define MINCONTR 0.3

static int CalcContrast(BYTE greyval, float steig, float off)
  {
  // x muss zwischen 0.0 und 1.0 liegen (inklusive)
  float x = (float)greyval / (float)255.0;
  int res = int((steig * (x - 0.5) + off + 0.5) * 255.0);
  if (res < 0) res = 0;
  if (res > 255) res = 255;
  return res;
  }

#endif


DLLExport void _export WINAPI SetContrast(HPALETTE hGrayPalette, HDC hDC,
                            float contrast, float brightness)
  {
  if (GrayPalCount > 0) {
#ifdef ALTE_VERSION
    contrast = (float)50.0 - contrast;
    brightness -= (float)50.0;
    contrast /= (float)100.0;
    brightness /= (float)100.0;
#else
    float steig = (float)pow(MINCONTR,1.0 - (contrast / 50.0));
    double maxoff;
    float cdurch50 = contrast / (float)50.0;
    if (cdurch50 < 1.0)
      maxoff = 0.5 + cdurch50 * (0.5 - MINCONTR);
    else
      maxoff = (1.0 - MINCONTR) + (cdurch50 - 1.0) * (0.5 * 1.0 / MINCONTR - (1.0 - MINCONTR));
    float off = float(maxoff - (2.0 * maxoff * (brightness / 100.0)));
#endif
    GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,
                                      sizeof(PALETTEENTRY) * GrayPalCount);
    LPPALETTEENTRY pe = LPPALETTEENTRY (GlobalLock (hGtemp));
    for (int i = 0; i < GrayPalCount; i++) {
      pe[i].peRed =
      pe[i].peGreen =
      pe[i].peBlue =
#ifdef ALTE_VERSION
        (BYTE)CalcContrast(OrigGrayVals[i],contrast,brightness);
#else
        (BYTE)CalcContrast(OrigGrayVals[i],steig,off);
#endif
      pe[i].peFlags = PC_RESERVED;
      }
    HPALETTE hOldPal = SelectPalette (hDC,hGrayPalette,FALSE);
    AnimatePalette(hGrayPalette, 0, GrayPalCount, pe);
    SelectPalette (hDC,hOldPal,TRUE);
    GlobalUnlock (hGtemp);
    GlobalFree (hGtemp);
#ifdef AUF_FILE
    // Ausgabe der Funktion auf ein Textfile
    OFSTRUCT ofs;
    HFILE fil = OpenFile("contrast.fnc",&ofs,OF_WRITE);
    if (fil == HFILE_ERROR) fil = OpenFile("contrast.fnc",&ofs,OF_CREATE|OF_WRITE);
    char str[260];
    sprintf(str,"\r\ncontrast = %d.%03d, brightness = %d.%03d\r\n",
            (int)contrast, ((int)(fabs(contrast) * (float)1000.0)) % 1000,
            (int)brightness, ((int)(fabs(brightness) * (float)1000.0)) % 1000);
    _lwrite(fil,str,strlen(str));
    for (int x = 0; x < 256; x++) {
      int y = CalcContrast((BYTE)x,contrast,brightness);
      sprintf(str,"x = %3d, y = %3d: ", x, y);
      _lwrite(fil,str,strlen(str));
      char *s = str;
      for (int dy = 0; dy < y; dy++)
        *s++ = ' ';
      *s++ = '*';
      *s++ = '\r';
      *s++ = '\n';
      *s++ = '\0';
      _lwrite(fil,str,strlen(str));
      }
    _lclose(fil);
#endif
    }
  }


DLLExport GLOBALHANDLE _export WINAPI GetEmptyColorHisto()
  {
  return GlobalAlloc (GHND, long(TOTALCOLORS) * long(sizeof(DWORD)));
  }


void mImage::CalcColorHisto()
  {
  if (hColorHisto) GlobalFree(hColorHisto);
  hColorHisto = NULL;
  WIN_ASSERT(hwholeDIB != NULL);
  if (hwholeDIB == NULL) return;
  if (IsGray) return;
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  if (lpbi->biBitCount == 24) {
    hColorHisto = GlobalAlloc (GHND, long(TOTALCOLORS) * long(sizeof(DWORD)));
    DWORD FAR *ColorHisto = (DWORD FAR *)GlobalLock (hColorHisto);
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    char huge *src = ((char huge *)lpbi) + lpbi->biSize + dwColorTableSize;
    LONG srcwidth = ByteWidth (lpbi->biWidth,24);
    for (int i = 0 ; i < lpbi->biHeight ; i++) {
      char huge *nextsrc = src + srcwidth;

#ifndef WIN32
      if (FP_SEG(nextsrc) == FP_SEG(src)) {
#endif
        unsigned char FAR *s = (unsigned char FAR *)src;
        for (int j = 0 ; j < lpbi->biWidth ; j++) {
#ifdef OLD_VERSION
          unsigned char b = *s++;
          unsigned char g = *s++;
          unsigned char r = *s++;
          ColorHisto[RGBIND(r,g,b)]++;
#else
          ColorHisto[RGBIND(s[2],s[1],s[0])]++;
          s += 3;
#endif
          }

#ifndef WIN32
        }
      else {
        unsigned char huge *s = (unsigned char huge *)src;
        for (int j = 0 ; j < lpbi->biWidth ; j++) {
          unsigned char b = *s++;
          unsigned char g = *s++;
          unsigned char r = *s++;
          ColorHisto[RGBIND(r,g,b)]++;
          }
        }
#endif

      src = nextsrc ;
      }
    GlobalUnlock (hColorHisto);
    }
  else if (lpbi->biBitCount == 8) {
    hColorHisto = GlobalAlloc (GHND,256 * sizeof(DWORD));
    DWORD FAR *ColorHisto = (DWORD FAR *) GlobalLock (hColorHisto);
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    BYTE FAR *Px = ((BYTE FAR *)lpbi) + lpbi->biSize + dwColorTableSize;
    BYTE FAR *Px0 = Px;
    for (int i = 0 ; i < lpbi->biHeight ; i++) {
      for (int j = 0 ; j < lpbi->biWidth ; j++) {
        ColorHisto[*Px]++;
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px, Px0);
      }
    GlobalUnlock (hColorHisto);
    }
  else if (lpbi->biBitCount == 4) {
    // voruebergehend keine Palette
    }
  else if (lpbi->biBitCount == 1) {
    // voruebergehend keine Palette
    }
  else {
    // nanu ?
    WIN_ASSERT(FALSE);
    }
  GlobalUnlock (hwholeDIB);
  }


DLLExport void _export WINAPI mImage::AddColorHisto(GLOBALHANDLE hsumcolors)
  {
  WIN_ASSERT(hsumcolors != NULL);
  WIN_ASSERT(hwholeDIB != NULL);
  if (hwholeDIB == NULL) return;
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  int nNumColors = int(DibNumColors(lpbi));
  if (lpbi->biBitCount == 24) {
    DWORD FAR *ColorHisto = (DWORD FAR *)GlobalLock (hColorHisto);
    DWORD FAR *SumColors = (DWORD FAR *)GlobalLock (hsumcolors);
    for (int i = 0; i < TOTALCOLORS; i++)
      *SumColors++ += *ColorHisto++;
    GlobalUnlock (hColorHisto);
    GlobalUnlock (hsumcolors);
    }
  else if (lpbi->biBitCount == 8) {
    DWORD FAR *SumColors = (DWORD FAR *)GlobalLock (hsumcolors);
    if (IsGray) {
      for (int i = 0; i < 256; i++)
        SumColors[RGBIND(i,i,i)] += 1024;
      }
    else {
      DWORD FAR *ColorHisto = (DWORD FAR *) GlobalLock (hColorHisto);
      RGBQUAD FAR *pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + (WORD)lpbi->biSize);
      for (int i = 0; i < nNumColors; i++)
        SumColors[RGBIND(pRgb[i].rgbRed,pRgb[i].rgbGreen,pRgb[i].rgbBlue)]
              += ColorHisto[i];
      GlobalUnlock (hColorHisto);
      }
    GlobalUnlock (hsumcolors);
    }
  else if (lpbi->biBitCount == 4) {
    DWORD FAR *SumColors = (DWORD FAR *)GlobalLock (hsumcolors);
    RGBQUAD FAR *pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + (WORD)lpbi->biSize);
    for (int i = 0; i < nNumColors; i++)
      SumColors[RGBIND(pRgb[i].rgbRed,pRgb[i].rgbGreen,pRgb[i].rgbBlue)]
            += 8192;
    GlobalUnlock (hsumcolors);
    }
  else if (lpbi->biBitCount == 1) {
    DWORD FAR *SumColors = (DWORD FAR *)GlobalLock (hsumcolors);
    RGBQUAD FAR *pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + (WORD)lpbi->biSize);
    for (int i = 0; i < nNumColors; i++)
      SumColors[RGBIND(pRgb[i].rgbRed,pRgb[i].rgbGreen,pRgb[i].rgbBlue)]
            += 65536;
    GlobalUnlock (hsumcolors);
    }
  else {
    // nanu ?
    WIN_ASSERT(FALSE);
    }
  GlobalUnlock (hwholeDIB);
  }


DLLExport HPALETTE _export WINAPI CalcBestPalette(GLOBALHANDLE hcolhist, GLOBALHANDLE FAR *hPalInd)
  {
  DWORD FAR *ColorHisto = (DWORD FAR *)GlobalLock (hcolhist);
  // als erstes Graustufen bevorzugen
  unsigned lastind = 0xffff;
  for (int i = 0; i < 256; i++) {
    unsigned actind = RGBIND(i,i,i);
    if (actind != lastind) {
      ColorHisto[actind] *= 2;
      lastind = actind;
      }
    }
  // jetzt sortieren
  GLOBALHANDLE hSortInds = GlobalAlloc(GHND, TOTALCOLORS * sizeof(int));
  int FAR *SortInds = (int FAR *)GlobalLock(hSortInds);
  int anzsorted = 0;
  // Farbhaeufigkeiten sortieren
  for (i = 0; i < TOTALCOLORS; i++) {
    if (ColorHisto[i] != 0) {
      int minind = 0;
      int maxind = anzsorted;
      if (anzsorted > 0) {
        for (;;) {
          int mid = (maxind + minind) / 2;
          if (ColorHisto[i] <= ColorHisto[SortInds[mid]]) {
            if (mid == minind) {
              minind = maxind;
              break;
              }
            minind = mid;
            }
          else {
            if (mid == minind)
              break;
            maxind = mid;
            }
          }
        }
      // minind enthaelt Index
      if (minind == anzsorted) {
        // einfach hinten einfuegen
        SortInds[minind] = i;
        anzsorted++;
        }
      else {
        // kleinere Eintraege nach hinten schieben
        for (int j = anzsorted; j > minind; j--)
          SortInds[j] = SortInds[j - 1];
        anzsorted++;
        SortInds[minind] = i;
        }
      }
    }
  // aus den haeufigsten 256 Farben Farbpalette bilden
  LOGPALETTE FAR *pPal = (LOGPALETTE FAR *)GetGlobMem(sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));
  pPal->palNumEntries = 256;
  pPal->palVersion = 0x300;
  for (i = 0; i < 256; i++) {
    int ind = SortInds[i];
    pPal->palPalEntry[i].peRed   = RPART(ind);
    pPal->palPalEntry[i].peGreen = GPART(ind);
    pPal->palPalEntry[i].peBlue  = BPART(ind);
    pPal->palPalEntry[i].peFlags = (BYTE)0;
    }
  HPALETTE pal = CreatePalette(pPal);
  FreeGlobMem(pPal);
  // fuer alle Farben naechsten Palettenindex suchen
  *hPalInd = GlobalAlloc(GHND, TOTALCOLORS * sizeof(WORD));
  WORD FAR *PalInd = (WORD FAR *)GlobalLock(*hPalInd);
  for (i = 0; i < anzsorted; i++) {
    int ind = SortInds[i];
    PalInd[ind] = GetNearestPaletteIndex(pal, RGB(RPART(ind), GPART(ind), BPART(ind)));
    }
  // aufraeumen
  GlobalUnlock(hcolhist);
  GlobalFree(hcolhist);
  GlobalUnlock(hSortInds);
  GlobalFree(hSortInds);
  GlobalUnlock(*hPalInd);
  return pal;
  }


static BOOL IsColorSet (int num,int FAR *ColorSet,int AnzColors)
  {
  BOOL res = FALSE ;
  for (int i = 0 ; i < AnzColors ; i++) {
    if (num == ColorSet[i]) {
      res = TRUE ;
      break ;
      }
    }
  return res;
  }

static int SetColor (int num,PALETTEENTRY FAR *pe,
                     int FAR *ColorSet,int AnzColors)
  {
  int res;
  if (!IsColorSet(num,ColorSet,AnzColors)) {
    pe[AnzColors].peRed = 
    pe[AnzColors].peGreen = 
    pe[AnzColors].peBlue = 0xFF - LOBYTE(num);
#define ANIMATION 1
#ifdef ANIMATION
    pe[AnzColors].peFlags = PC_RESERVED;
#else
    pe[AnzColors].peFlags = 0;
#endif
    OrigGrayVals[AnzColors] = 0xFF - (BYTE)(ColorSet[AnzColors] = num) ;
    res = AnzColors + 1;
    }
  else
    res = AnzColors ;
  return res;
  }

#define MAXGRAYSTEPS  128
#define STEPDEPTH       9
static int StepWidth[STEPDEPTH] = 
  { 255 , 128 , 64 , 32 , 16 , 8 , 4 , 2 , 1 } ;

DLLExport HPALETTE _export WINAPI CreateGrayPalette(HPALETTE oldPal)
  {
  HPALETTE res;
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,
                        sizeof(LOGPALETTE)+sizeof(PALETTEENTRY) * 256);
  LPLOGPALETTE pal = LPLOGPALETTE (GlobalLock (hGtemp));
  pal->palVersion = 0x300;

  // Setzen von Paletten eintraegen, die wichtigen nach vorne
  // (0,255,128,64,196...)
  int ColorSet[257];
  int AnzColors = 0;

  if (oldPal) {
    for (int i = 0 ; ((i < 110) && (AnzColors < 256) && 
          (GetPaletteEntries (oldPal,i,1,&pal->palPalEntry[AnzColors]) == 1)) ;
          i ++ , AnzColors ++ ) ;
    }
  memset (ColorSet,0xFF,sizeof(ColorSet));
  for (int i = 0 ; (i < STEPDEPTH) && (AnzColors < MAXGRAYSTEPS); i++) {
    for (int j = 0 ; (j < 256) && (AnzColors < MAXGRAYSTEPS); j += StepWidth[i]) {
      AnzColors = SetColor (j,&pal->palPalEntry[0],ColorSet,AnzColors);
      }
    }
  GrayPalCount = pal->palNumEntries = AnzColors-1 ;
  res = CreatePalette (pal);

  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);

  return res;
  }


DLLExport void _export WINAPI mImage::WriteBMP(LPSTR FileName)
  {
#ifdef ALTE_VERSION
  HFILE dib;
  OFSTRUCT dibof;
  if ((dib = OpenFile(FileName, &dibof, OF_CREATE | OF_WRITE)) >= 0) {
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    DWORD HeaderSize = lpbi->biSize + dwColorTableSize;
    DWORD DIBsize = HeaderSize + lpbi->biSizeImage;
    BITMAPFILEHEADER bmfh;
    memset(&bmfh,'\0',sizeof(bmfh));
    bmfh.bfType = 'B' | ('M' << 8);
    bmfh.bfSize = sizeof(bmfh) + DIBsize;
    bmfh.bfOffBits = HeaderSize + sizeof(bmfh);
    _lwrite(dib, LPSTR(&bmfh), sizeof(bmfh));
    _hwrite(dib, LPSTR(lpbi), DIBsize);
    GlobalUnlock(hwholeDIB);
    _lclose(dib);
    }
#endif
  if (hwholeDIB) {
    for (int i = lstrlen(FileName); i > 0; i--) {
      if (FileName[i] == '.') {
        i++;
        break;
        }
      }
    L_INT nFormat, nQFactor;
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
    L_INT nBitsPerPixel = lpbi->biBitCount;
    lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    char huge *lpbits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
    if (!lstrcmp(FileName + i,"jpg")) {
      nFormat = FILE_JFIF;
      nQFactor = 50;
      }
    else if (!lstrcmp(FileName + i,"gif")) {
      if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
        L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
      nFormat = FILE_GIF;
      nQFactor = 0;
      }
    else if (!lstrcmp(FileName + i,"tif")) {
      if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
        L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
      nFormat = FILE_TIF;
      nQFactor = 0;
      }
    else if (!lstrcmp(FileName + i,"cmp")) {
      if (nBitsPerPixel == 1) {
        nFormat = FILE_LEAD1BIT;
        nQFactor = 0;
        }
      else {
        nFormat = FILE_LEAD;
        nQFactor = QS;
        }
      }
    else {
      nFormat = 0;
      nQFactor = 0;
      }
    BITMAPHANDLE LeadBitmap;
    L_ConvertFromDIB(&LeadBitmap,(LPBITMAPINFO)lpbi,(L_UCHAR L_FAR *)lpbits);
    L_SaveBitmap(FileName,&LeadBitmap,nFormat,nBitsPerPixel,nQFactor);
    L_FreeBitmap(&LeadBitmap);
    GlobalUnlock(hwholeDIB);
    }
  }


static BYTE huge *actbits;
static int actwidth, actheight;
static long actbytewidth;

static BYTE actval;
void CALLBACK DrawPixel8(int x, int y, LPARAM dummy)
  {
  if ((x >= 0) && (x < actwidth) && (y >= 0) && (y < actheight))
    actbits[((long)(actheight - 1 - y) * actbytewidth) + (long)x] = actval;
  }


static BYTE actr, actb, actg;
void CALLBACK DrawPixel24(int x, int y, LPARAM dummy)
  {
  if ((x >= 0) && (x < actwidth) && (y >= 0) && (y < actheight)) {
    long ind = ((long)(actheight - 1 - y) * actbytewidth) + (3L * (long)x);
    actbits[ind++] = actb;
    actbits[ind++] = actg;
    actbits[ind] = actr;
    }
  }


DLLExport void _export WINAPI mImage::DrawContDirect(float FAR *cnt, int PtCount, DWORD color)
  {
  if (int(color >> 28) == 7) return;  // durchsichtiger Stift
  if ((cnt == NULL) || (PtCount <= 1)) return;
  if (hwholeDIB == NULL) return;
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  actwidth = (int)lpbi->biWidth;
  actheight = (int)lpbi->biHeight;
  actbytewidth = ByteWidth(actwidth,lpbi->biBitCount);
  lpbi->biSizeImage = actbytewidth*actheight;
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  actbits = ((BYTE huge *)lpbi) + lpbi->biSize + dwColorTableSize;
  LINEDDAPROC actproc = NULL;
  if (lpbi->biBitCount == 24) {
    color &= 0xFFFFFFL;
    actr = GetRValue(color);
    actg = GetGValue(color);
    actb = GetBValue(color);
    actproc = (LINEDDAPROC)DrawPixel24;
    }
  else if (lpbi->biBitCount == 8) {
    color &= 0xFFFFFFL;
    HPALETTE hPal = CreateBIPalette(lpbi);
    actval = BYTE(GetNearestPaletteIndex(hPal, color));
    DeleteObject(hPal);
    actproc = (LINEDDAPROC)DrawPixel8;
    }
  if (actproc != NULL) {
    int xstart = (int)*cnt++;
    int ystart = (int)*cnt++;
    for (int i = 1; i < PtCount; i++) {
      int xend = (int)*cnt++;
      int yend = (int)*cnt++;
      LineDDA(xstart, ystart, xend, yend, actproc, NULL);
      xstart = xend;
      ystart = yend;
      }
    }
  GlobalUnlock(hwholeDIB);
  }


