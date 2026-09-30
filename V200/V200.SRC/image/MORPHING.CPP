/////////////////////////////////////////////////////////////////////
//
//      Verzerren von Bildern entsprechend einem Vektorfeld
//
/////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/image/rev/morphing.cpv   1.6   03 Mar 1998 20:04:48   Martin  $
// $Log:   P:/marille/clinicum/image/rev/morphing.cpv  $
// 
//    Rev 1.6   03 Mar 1998 20:04:48   Martin
// True Color
// 
//    Rev 1.5   11 Apr 1997 16:20:00   Martin
// int -> short (wegen 32 bit)
// 
//    Rev 1.4   02 Feb 1996 10:49:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   31 Mar 1995 18:23:26   HANNES
//  
// 
//    Rev 1.2   08 Dec 1994 21:48:36   HANNES
// 
//    Rev 1.1   17 Oct 1994 15:02:48   HANNES
// No change.
// 
//    Rev 1.0   24 Jun 1994 16:51:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   13 Apr 1994 20:45:24   MARTIN
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#define MIMAGE_CLASS
#include "image.hpp"
#define MODULENUM 11
#include "winass.hpp"

extern DLLExport int _export WINAPI BitsPerPixel (void);

union FIXPOINT {
  long whole;
  struct {
    short low, high;
    } part;
  };

struct Edge {
  struct Edge FAR *next;
  short x, xmax, y, ymax;                   // aktuelle / maximale Koordinaten
  short numerator, denominator, increment;  // Hilfsvariable f. scan-line algo
  short minxstep;                           // fuer Kanten flacher als 45 Grad
  FIXPOINT dx, dy;                        // aktueller Verzerrungsvektor
  long xinc, yinc;                        // Inkrement fuer Vektor
  };
typedef Edge FAR * LPEDGE;


inline long floattofix(float f)
  {
  return long(f * 65536.0);
  }


inline float fixtofloat(long f)
  {
  return float(f) / float(65536.0);
  }


inline short round_down(float f)
  {
  return short(unsigned(f + 32768.0) - 32768);
  }


DLLExport void _export WINAPI AddEdge(LPVOID FAR *EdgeList, int ymax,
                        fpt FAR *p1, fpt FAR *p2,
                        fpt FAR *v1, fpt FAR *v2)
  {
  if ((p1 == NULL) || (p2 == NULL) || (v1 == NULL) || (v2 == NULL)) return;
#define FULL_CHECK 1
#ifdef FULL_CHECK
  if ((p1->x < -32000.0) || (p1->x > 32000.0) ||
      (p1->y < -32000.0) || (p1->y > 32000.0) ||
      (p2->x < -32000.0) || (p2->x > 32000.0) ||
      (p2->y < -32000.0) || (p2->y > 32000.0) ||
      (v1->x < -32000.0) || (v1->x > 32000.0) ||
      (v1->y < -32000.0) || (v1->y > 32000.0) ||
      (v2->x < -32000.0) || (v2->x > 32000.0) ||
      (v2->y < -32000.0) || (v2->y > 32000.0)) return;
#endif

  if (p1->y > p2->y) {     // eventuell umdrehen
    fpt FAR *h;
    h = p1;  p1 = p2;  p2 = h;
    h = v1;  v1 = v2;  v2 = h;
    }
  short x1 = round_down(p1->x);
  short y1 = round_down(p1->y);
  short x2 = round_down(p2->x);
  short y2 = round_down(p2->y);

  // vertikales clipping:

  if (y1 == y2) return;    // Kante mit Hoehe 0
  if (y2 <= 0) return;     // Kante ganz oberhalb des Bildes
  if (y1 >= (short)ymax) return;  // Kante ganz unterhalb des Bildes
  if (y1 < 0) {            // Kante teilweise oberhalb des Bildes -> clippen
    x1 = round_down(p1->x + (((p1->x - p2->x) * p1->y) / (p2->y - p1->y)));
    y1 = 0;
    }
  // Kante teilweise unterhalb des Bildes -> kein clippen notwendig,
  //   da sowieso nur bis y < ymax gemorpht wird
  // Kante ganz oder teilweise links oder rechts des Bildes:
  //   horizontal muss zeilenweise geclippt werden

  // suchen der Stelle, wo die neue Kante einsortiert gehoert

  LPEDGE FAR *el = (LPEDGE FAR *)EdgeList;
  LPEDGE last = NULL;
  for (LPEDGE e = el[y1]; e != NULL; e = e->next) {
    if (e->x > x1) break;
    if (e->x == x1) {
      if ((e->xmax == x2) && (e->ymax == y2)) return;   // doppelte Kante
      if ((float(e->xmax - x1) / float(e->ymax - y1)) >
          (float(x2 - x1) / float(y2 - y1))) break;
      }
    last = e;
    }

  // neue Kante erzeugen und einfuegen

  LPEDGE newedge = (LPEDGE)GetGlobMem(sizeof(Edge));
  if (last == NULL) {
    newedge->next = el[y1];
    el[y1] = newedge;
    }
  else {
    newedge->next = last->next;
    last->next = newedge;
    }

  // Initialisierung der Kante

  newedge->x = x1;
  newedge->xmax = x2;
  newedge->y = y1;
  newedge->ymax = y2;
  newedge->denominator = y2 - y1;
  newedge->increment = newedge->denominator;
  short dx = x2 - x1;
  if (dx < 0)
    newedge->minxstep = ((dx + 1) / newedge->denominator) - 1;
  else
    newedge->minxstep = dx / newedge->denominator;
  newedge->numerator = dx - newedge->minxstep * newedge->denominator;
  // jetzt noch Verzerrungsvektoren:
  newedge->dx.whole = floattofix(v1->x);
  newedge->dy.whole = floattofix(v1->y);
  float dy = p2->y - p1->y;
  newedge->xinc = floattofix((v2->x - v1->x) / dy);
  newedge->yinc = floattofix((v2->y - v1->y) / dy);
  }


class DoMorph {
 private:
  // alle benoetigten Variable:
  short ColorMode;
  LPEDGE FAR *et;
  char huge *dst;
  char huge *src;
  short width, height;
  WORD FAR *palind;
  long bwidth24, bwidth8;
  LPEDGE aet, laste, e, newe, nexte, estart;
  short acty, actminusy;
  short xstart, xend;
  FIXPOINT dxstart, dystart, dxend, dyend;
  long dxinc, dyinc;
  short srcx, srcy;
  // Hilfsfunktion fuer das Verzerren eines horizontalen Intervalles:
  void MorphActIntervall(void);
 public:
  // die einzige aufzurufende Funktion:
  DoMorph (BOOL cColorMode, LPEDGE FAR *cet,
           char huge *cdst, char huge *csrc,
           short cwidth, short cheight, WORD FAR *cpalind);
  };


void DoMorph::MorphActIntervall()
  {
  if (xstart < xend) {
    long xlen = long(xend - xstart);
    if ((dxstart.part.high == 0) && (dystart.part.high == 0) &&
        (dxend.part.high == 0) && (dyend.part.high == 0)) {
      // eins zu eins uebernehmen
      if (ColorMode == 0) {
        unsigned char huge *srcstart = (unsigned char huge *)src + bwidth24 * long(actminusy) + long(xstart * 3);
        unsigned char huge *dststart = (unsigned char huge *)dst + bwidth8 * long(actminusy) + long(xstart);
        unsigned char huge *srcend = srcstart + xlen * 3;
        unsigned char huge *dstend = dststart + xlen;

#ifndef WIN32
        if ((FP_SEG(srcstart) == FP_SEG(srcend)) &&
            (FP_SEG(dststart) == FP_SEG(dstend))) {
#endif

          unsigned char FAR *s = (unsigned char FAR *)srcstart;
          unsigned char FAR *d = (unsigned char FAR *)dststart;
#ifndef WIN32
          while (FP_OFF(d) < FP_OFF(dstend)) {
#else
          for (int i = 0; i < (int)xlen; i++) {
#endif
            *d++ = (unsigned char)palind[RGBIND(s[2],s[1],s[0])];
            s += 3;
            }

#ifndef WIN32
          }
        else {
          while (xstart < xend) {
            unsigned char b = *srcstart++;
            unsigned char g = *srcstart++;
            unsigned char r = *srcstart++;
            *dststart++ = (unsigned char)palind[RGBIND(r,g,b)];
            xstart++;
            }
          }
#endif

        }
      else if (ColorMode == 1) {
        unsigned char huge *srcstart = (unsigned char huge *)src + bwidth24 * long(actminusy) + long(xstart * 3);
        unsigned char huge *dststart = (unsigned char huge *)dst + bwidth24 * long(actminusy) + long(xstart * 3);
        unsigned char huge *srcend = srcstart + xlen * 3;
        unsigned char huge *dstend = dststart + xlen * 3;

#ifndef WIN32
        if ((FP_SEG(srcstart) == FP_SEG(srcend)) &&
            (FP_SEG(dststart) == FP_SEG(dstend))) {
#endif

          unsigned char FAR *s = (unsigned char FAR *)srcstart;
          unsigned char FAR *d = (unsigned char FAR *)dststart;
#ifndef WIN32
          while (FP_OFF(d) < FP_OFF(dstend)) {
#else
          for (int i = 0; i < (int)xlen; i++) {
#endif
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            }

#ifndef WIN32
          }
        else {
          for (int i = 0; i < (int)xlen; i++) {
            *dststart++ = *srcstart++;
            *dststart++ = *srcstart++;
            *dststart++ = *srcstart++;
            }
          }
#endif

        }
      else {
        long offset = bwidth8 * long(actminusy) + long(xstart);
        unsigned char huge *srcstart = (unsigned char huge *)src + offset;
        unsigned char huge *dststart = (unsigned char huge *)dst + offset;
        unsigned char huge *srcend = srcstart + xlen;
        unsigned char huge *dstend = dststart + xlen;

#ifndef WIN32
        if ((FP_SEG(srcstart) == FP_SEG(srcend)) &&
            (FP_SEG(dststart) == FP_SEG(dstend))) {
#endif

          unsigned char FAR *s = (unsigned char FAR *)srcstart;
          unsigned char FAR *d = (unsigned char FAR *)dststart;
          for (int i = 0; i < (int)xlen; i++)
            *d++ = *s++;

#ifndef WIN32
          }
        else {
          for (int i = 0; i < (int)xlen; i++)
            *dststart++ = *srcstart++;
          }
#endif

        }
      }
    else {
      // jetzt wirds ernst
      dxinc = ((dxend.whole - dxstart.whole) + (xlen << 16)) / xlen;
//      dyinc = (dyend.whole - dystart.whole) / xlen;
      dyinc = (dystart.whole - dyend.whole) / xlen;  // xxxx
      dxstart.whole += long(xstart) << 16;
//      dystart.whole += long(actminusy) << 16;
      dystart.whole = (long(actminusy) << 16) - dystart.whole;  // xxxx
      if (ColorMode == 0) {
        unsigned char huge *dststart = (unsigned char huge *)dst + bwidth8 * long(actminusy) + long(xstart);
        do {
          if (dxstart.part.high < 0) srcx = 0;
          else if (dxstart.part.high >= width) srcx = width - 1;
          else srcx = dxstart.part.high;
          if (dystart.part.high < 0) srcy = 0;
          else if (dystart.part.high >= height) srcy = height - 1;
          else srcy = dystart.part.high;
          unsigned char huge *s = (unsigned char huge *)src + bwidth24 * long(srcy) + long(srcx * 3);
          unsigned char b = *s++;
          unsigned char g = *s++;
          unsigned char r = *s;
          *dststart++ = (unsigned char)palind[RGBIND(r,g,b)];
          dxstart.whole += dxinc;
          dystart.whole += dyinc;
          xstart++;
          } while (xstart < xend);
        }
      else if (ColorMode == 1) {
        unsigned char huge *dststart = (unsigned char huge *)dst + bwidth24 * long(actminusy) + long(xstart * 3);
        do {
          if (dxstart.part.high < 0) srcx = 0;
          else if (dxstart.part.high >= width) srcx = width - 1;
          else srcx = dxstart.part.high;
          if (dystart.part.high < 0) srcy = 0;
          else if (dystart.part.high >= height) srcy = height - 1;
          else srcy = dystart.part.high;
          unsigned char huge *s = (unsigned char huge *)src + bwidth24 * long(srcy) + long(srcx * 3);
          *dststart++ = *s++;
          *dststart++ = *s++;
          *dststart++ = *s;
          dxstart.whole += dxinc;
          dystart.whole += dyinc;
          xstart++;
          } while (xstart < xend);
        }
      else {
        unsigned char huge *dststart = (unsigned char huge *)dst + bwidth8 * long(actminusy) + long(xstart);
        do {
          if (dxstart.part.high < 0) srcx = 0;
          else if (dxstart.part.high >= width) srcx = width - 1;
          else srcx = dxstart.part.high;
          if (dystart.part.high < 0) srcy = 0;
          else if (dystart.part.high >= height) srcy = height - 1;
          else srcy = dystart.part.high;
          *dststart++ = ((unsigned char huge *)src)[bwidth8 * long(srcy) + long(srcx)];
          dxstart.whole += dxinc;
          dystart.whole += dyinc;
          xstart++;
          } while (xstart < xend);
        }
      }
    }
  }


DoMorph::DoMorph(BOOL cColorMode, LPEDGE FAR *cet,
                 char huge *cdst, char huge *csrc,
                 short cwidth, short cheight, WORD FAR *cpalind)
  {
  ColorMode = cColorMode;
  et = cet;
  dst = cdst;
  src = csrc;
  width = cwidth;
  height = cheight;
  palind = cpalind;
  bwidth24 = ByteWidth (width,24);
  bwidth8 = ByteWidth (width,8);
  aet = NULL;
  acty = 0;
  actminusy = height;
  while (acty < height) {
    actminusy--;

    // gegebenenfalls Kanten aus et in aet uebernehmen
    // (dabei richtig einsortieren)

    laste = NULL;
    e = aet;
    newe = et[acty];
    while (newe != NULL) {
      nexte = newe->next;
      while (e != NULL) {
        if (newe->x < e->x) break;
        if (newe->x == e->x) {
          if ((float(e->xmax - e->x) / float(e->ymax - acty)) >
              (float(newe->xmax - newe->x) / float(newe->ymax - newe->y))) break;
          }
        laste = e;
        e = e->next;
        }
      if (laste == NULL) {
        newe->next = aet;
        aet = newe;
        }
      else {
        newe->next = laste->next;
        laste->next = newe;
        }
      laste = newe;
      newe = nexte;
      }
    et[acty] = NULL;

    // jetzt die aktuelle Zeile verarbeiten

    // zuerst Startwerte ermitteln
    xstart = 0;
    estart = NULL;
    for (e = aet; e != NULL; e = e->next) {
      if (e->x > 0) break;
      estart = e;
      }
    if (estart == NULL) {      // keine Kante links des Bildes
      dxstart.whole = 0L;
      dystart.whole = 0L;
      }
    else {                     // Kante (teilweise) links des Bildes
      if (e == NULL) {         // rechts davon keine Kante mehr
        dxstart.whole = 0L;
        dystart.whole = 0L;
        }
      else {                   // clippen an der linken Bildgrenze
        float fact = float(estart->x) / float(e->x - estart->x);
        // (e->x - estart->x) kann hier nie 0 sein !
        dxstart.whole = long(float(estart->dx.whole) +
                        (float(estart->dx.whole - e->dx.whole) * fact));
        dystart.whole = long(float(estart->dy.whole) +
                        (float(estart->dy.whole - e->dy.whole) * fact));
        }
      }

    // dann alle Kantenpaare durchwandern
    while (xstart < width) {
      // Endwerte bestimmen
      if (e == NULL) {         // rechts davon keine Kante mehr
        xend = width;
        dxend.whole = 0L;
        dyend.whole = 0L;
        }
      else {
        if (e->x > width) {    // clippen an der rechten Bildgrenze
          xend = width;
          float fact = float(width - xstart) / float(e->x - xstart);
          // (e->x - xstart) kann hier nie 0 sein !
          dxend.whole = long(float(dxstart.whole) +
                        (float(e->dx.whole - dxstart.whole) * fact));
          dyend.whole = long(float(dystart.whole) +
                        (float(e->dy.whole - dystart.whole) * fact));
          }
        else {                 // Normalfall, Kante mitten im Bild
          xend = e->x;
          dxend = e->dx;
          dyend = e->dy;
          }
        }
      // aktuelles Intervall mit linearer Interpolation verzerren
      MorphActIntervall();
      // Kante weiterschalten
      xstart = xend;
      dxstart = dxend;
      dystart = dyend;
      if (e != NULL)
        e = e->next;
      }

    // weiterschalten auf naechste Zeile
    acty++;

    // Raushauen der nicht mehr benoetigten Kanten
    laste = NULL;
    e = aet;
    while (e != NULL) {
      if (e->ymax == acty) {
        if (laste == NULL) {
          aet = e->next;
          FreeGlobMem(e);
          e = aet;
          }
        else {
          laste->next = e->next;
          FreeGlobMem(e);
          e = laste->next;
          }
        }
      else {
        laste = e;
        e = e->next;
        }
      }

    // fuer alle aktiven Kanten x, dx, dy weiterschalten
    for (e = aet; e != NULL; e = e->next) {
      e->x += e->minxstep;
      e->increment += e->numerator;
      if (e->increment > e->denominator) {
        e->x++;
        e->increment -= e->denominator;
        }
      e->dx.whole += e->xinc;
      e->dy.whole += e->yinc;
      }
    }

  // restliche Kanten aus aet loeschen
  while (aet != NULL) {
    LPEDGE laste = aet;
    aet = aet->next;
    FreeGlobMem(laste);
    }
  }


DLLExport void _export WINAPI mImage::MorphImage(LPVOID FAR *EdgeList, int ymax, GLOBALHANDLE hPalInd)
  {
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hwholeDIB);
  if (int(lpbi->biHeight) == ymax) {
    lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
    DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
    LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
    if ((lpbi->biBitCount == 24) || (lpbi->biBitCount == 8)) {
      if ((lpbi->biBitCount == 8) || (hPalInd != NULL) || (BitsPerPixel() != 8)) {
        CheckSecondDIB(FALSE);
        LPSTR lpnBits = (LPSTR)GlobalLock(hDIB);
        WORD FAR *palind = (WORD FAR *)GlobalLock(hPalInd);
        short ColorMode;
        if (lpbi->biBitCount == 24) {
          if (BitsPerPixel() == 8)
            ColorMode = 0;
          else
            ColorMode = 1;
          }
        else
          ColorMode = 2;
        DoMorph morph(ColorMode, (LPEDGE FAR *)EdgeList, lpnBits, lpBits, (short)lpbi->biWidth, (short)lpbi->biHeight, palind);
        GlobalUnlock(hPalInd);
        GlobalUnlock(hDIB);
        }
      else {
        WIN_ASSERT(FALSE);
        }
      }
    else {
      WIN_ASSERT(FALSE);
      }
    }
  else {
    WIN_ASSERT(FALSE);
    }
  GlobalUnlock(hwholeDIB);
  }

