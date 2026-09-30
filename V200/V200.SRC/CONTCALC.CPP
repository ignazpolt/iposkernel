/*------------------------------------------------------*/
/*      Berechnungsfunktionen mit Konturen              */
/*------------------------------------------------------*/
// $Header:   P:/marille/clinicum/rev/contcalc.cpv   1.7   21 Apr 1998 19:33:30   Hannes  $
// $Log:   P:/marille/clinicum/rev/contcalc.cpv  $
// 
//    Rev 1.7   21 Apr 1998 19:33:30   Hannes
// Contclip ins frmobj
// 
//    Rev 1.6   19 Nov 1997 18:47:44   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.5   10 Apr 1997 11:42:18   Hannes
// Segmentfehler korrigiert
// 
//    Rev 1.4   10 Apr 1997 10:03:14   Martin
// Fehler in contnea korrigiert
// 
//    Rev 1.3   02 Feb 1996 10:36:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:20:08   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Mar 1995 11:55:02   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 17:04:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.7   17 May 1994 10:55:44   MARTIN
// EstTang
// 
//    Rev 1.6   18 Jun 1993 15:11:08   MARTIN
// Prototyp der Berechnungsfunktionen
// 
//    Rev 1.5   02 Jun 1993 22:20:28   MARTIN
// turnpt
// 
//    Rev 1.4   05 May 1993 11:06:02   MARTIN
// uEstimateTang
// 
//    Rev 1.3   22 Apr 1993 21:01:30   MARTIN
// Anpassung fuer geschnittene Konturen
// 
//    Rev 1.2   02 Apr 1993 17:31:50   HANNES
// contmcro
// 
//    Rev 1.1   03 Dec 1992 14:48:38   HANNES
// Korrektur von contmax bei fehlender Kontur
// 
//    Rev 1.0   02 Dec 1992 15:20:54   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <search.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "cont.hpp"
#include "calcval.hpp"
#include "cutcont.hpp"
#define MODULENUM 25
#include "winass.hpp"

// Extremwerte einer Kontur
void contmax (fpt FAR *res,fpt FAR *cont,fpt FAR *p1,fpt FAR *p2)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  int resi = -1;
  double dx0 = p2->x - p1->x ;
  double dy0 = p2->y - p1->y ;
  double oabst = -1.0E100;
  for (int i = 0 ; i < cntsize ; i++) {
    double dx = cont[i].x - p1->x ;
    double dy = cont[i].y - p1->y ;
    double abst = dx * dy0 - dy * dx0 ;
    if (abst > oabst) {
      oabst = abst ;
      resi = i ;
      }
    }
  if (resi >= 0)
    lmemcpy (res,cont+resi,sizeof(fpt));
  else
    res->x = float(1.0E10);
  }

// Schnittpunkt einer Gerade mit einer Kontur
typedef void FAR *pv;
void contcro (fpt FAR *res,fpt FAR *cont,fpt FAR *p1,fpt FAR *p2,int Nr)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  double dx0 = p2->x - p1->x ;
  double dy0 = p2->y - p1->y ;
  double oabst;
  int j = 0 ;
  for (int i = 0 ; i < cntsize ; i++) {
    double dx = cont[i].x - p1->x ;
    double dy = cont[i].y - p1->y ;
    double abst = dx * dy0 - dy * dx0 ;
    if (i > 0) {
      if (abst * oabst < 0) {
        // Schnittpunkt gefunden
        if (++j == Nr) break ;  // Richtiger Schnittpunkt -> aufhoehren
        }
      }
    oabst = abst ;
    }
  if (i >= cntsize) {
    // nicht gefunden
    res->x = float(1.0E10) ;
    }
  else {
    LPFPT args[5];
    args[1] = p1 ;
    args[2] = p2 ;
    args[3] = cont + i - 1 ;
    args[4] = cont + i ;
    fpt *rli = (fpt *) LinInt ((pv FAR *)args);
    lmemcpy (res,rli,sizeof(fpt));
    }
  }

// Schnittpunkt einer Gerade mit einer Kontur
void contmcro (fpt FAR *res,fpt FAR *cont,fpt FAR *p1,fpt FAR *p2,fpt FAR *dir)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  double dx0 = p2->x - p1->x ;
  double dy0 = p2->y - p1->y ;
  double abst,oabst;
  int j = 0 ;
  int cp[30];
  for (int i = 0 ; i < cntsize ; i++) {
    double dx = cont[i].x - p1->x ;
    double dy = cont[i].y - p1->y ;
    abst = dx * dy0 - dy * dx0 ;
    if (i > 0) {
      if (abst * oabst < 0) {
        // Schnittpunkt gefunden
        cp[j++] = i;
        }
      }
    oabst = abst ;
    }
  if (j > 0) {
    // nicht gefunden
    res->x = float(1.0E10) ;
    }
  else {
    oabst = -1.0E10;
    for (i = 0 ; i < j ; i++) {
      LPFPT args[5];
      fpt r0;
      args[1] = p1 ;
      args[2] = p2 ;
      args[3] = cont + cp[i] - 1 ;
      args[4] = cont + cp[i] ;
      fpt *rli = (fpt *) LinInt ((pv FAR *)args);
      if (i == 0)
        lmemcpy (&r0,rli,sizeof(r0));
      abst = dir->x * (rli->x - r0.x) +
             dir->y * (rli->y - r0.y);
      if (abst > oabst) {
        lmemcpy (res,rli,sizeof(fpt));
        oabst = abst ;
        }
      }
    }
  }

/*-------< Ermitteln des naehesten Punktes auf einer Kontur >------*/
BOOL ChkPtInLine (fpt FAR *p,fpt FAR *p1,fpt FAR *p2)
  {
  double dx1 = p->x - p1->x ;
  double dx2 = p->x - p2->x ;
  double dy1 = p->y - p1->y ;
  double dy2 = p->y - p2->y ;
  return ((dx1 * dx2 <= 0.0) && (dy1 * dy2 <= 0.0)) ;
  }

void contnea (fpt FAR *res,fpt FAR *cont,fpt FAR *p)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  double oabst = 1.0E10;
  double dx, dy, abst;
  LPFPT args[4];
  args[3] = p ;
  fpt h,cntbuff;
  for (int i = 0 ; i < cntsize ; i++) {
    if (i < cntsize-1) {
      // Untersuchen der Gerade
      args[1] = &cont[i+1] ;
      args[2] = &cont[i] ;
      fpt *hlp = (fpt *) PtPro ((pv FAR *)args);
      if (hlp == NULL) {
        cntbuff = cont[i];
        hlp = &cntbuff;
        }
      if (ChkPtInLine (hlp,&cont[i],&cont[i+1])) {
        dx = hlp->x - p->x ;  dy = hlp->y - p->y ;
        abst = hypot (dx,dy);
        if (abst < oabst) {
          oabst = abst ;
          lmemcpy (&h,hlp,sizeof (fpt));
          }
        }
      }
    // Untersuchen den Punktes
    dx = cont[i].x - p->x ;     dy = cont[i].y - p->y ;
    abst = hypot (dx,dy);
    if (abst < oabst) {
      oabst = abst ;
      lmemcpy (&h,&cont[i],sizeof(fpt));
      }
    }

  lmemcpy (res,&h,sizeof(fpt));
  }

void esttang (fpt FAR *res,fpt FAR *cont,fpt FAR *p,fpt FAR *vect)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  if (cntsize < 3) {
    if (cntsize == 2) {
      res->x = cont[1].x - cont[0].x;
      res->y = cont[1].y - cont[0].y;
      }
    else {
      res->x = res->y = float(1.0E10);
      }
    }
  else {
    double oabst = 1.0E10;
    double dx, dy, abst;
    int ind;
    for (int i = 0 ; i < cntsize ; i++) {
      // Suchen den Punktes auf der Kontur
      dx = cont[i].x - p->x ;     dy = cont[i].y - p->y ;
      abst = hypot (dx,dy);
      if (abst < oabst) {
        oabst = abst ;
        ind = i;
        }
      }
    fpt dnext, dprev;
    if (ind == 0) {
      dnext.x = cont[1].x - cont[0].x;
      dnext.y = cont[1].y - cont[0].y;
      float lnext = (float)hypot(dnext.x, dnext.y);
      if (lnext > 1.0E-3) {
        dnext.x /= lnext;
        dnext.y /= lnext;
        }
      fpt dnnext;
      dnnext.x = cont[2].x - cont[1].x;
      dnnext.y = cont[2].y - cont[1].y;
      float lnnext = (float)hypot(dnnext.x, dnnext.y);
      if (lnnext > 1.0E-3) {
        dnnext.x /= lnnext;
        dnnext.y /= lnnext;
        }
      float f = (float)2.0 * (dnext.x * dnnext.x + dnext.y * dnnext.y);
      dprev.x = dnext.x * f - dnnext.x;
      dprev.y = dnext.y * f - dnnext.y;
      }
    else if (ind == (cntsize - 1)) {
      dnext.x = cont[cntsize - 2].x - cont[cntsize - 1].x;
      dnext.y = cont[cntsize - 2].y - cont[cntsize - 1].y;
      float lnext = (float)hypot(dnext.x, dnext.y);
      if (lnext > 1.0E-3) {
        dnext.x /= lnext;
        dnext.y /= lnext;
        }
      fpt dnnext;
      dnnext.x = cont[cntsize - 3].x - cont[cntsize - 2].x;
      dnnext.y = cont[cntsize - 3].y - cont[cntsize - 2].y;
      float lnnext = (float)hypot(dnnext.x, dnnext.y);
      if (lnnext > 1.0E-3) {
        dnnext.x /= lnnext;
        dnnext.y /= lnnext;
        }
      float f = (float)2.0 * (dnext.x * dnnext.x + dnext.y * dnnext.y);
      dprev.x = dnext.x * f - dnnext.x;
      dprev.y = dnext.y * f - dnnext.y;
      }
    else {
      // mitten in der Kontur -> Vektor Richtung vorigen und naechsten mitteln
      dnext.x = cont[ind + 1].x - cont[ind].x;
      dnext.y = cont[ind + 1].y - cont[ind].y;
      float lnext = (float)hypot(dnext.x, dnext.y);
      if (lnext > 1.0E-3) {
        dnext.x /= lnext;
        dnext.y /= lnext;
        }
      dprev.x = cont[ind].x - cont[ind - 1].x;
      dprev.y = cont[ind].y - cont[ind - 1].y;
      float lprev = (float)hypot(dprev.x, dprev.y);
      if (lprev > 1.0E-3) {
        dprev.x /= lprev;
        dprev.y /= lprev;
        }
      }
    dnext.x = dnext.x + dprev.x;
    dnext.y = dnext.y + dprev.y;
    float lnext = (float)hypot(dnext.x, dnext.y);
    if (lnext > 1.0E-3) {
      dnext.x /= lnext;
      dnext.y /= lnext;
      }
    if (vect != NULL) {
      if ((vect->x * dnext.x + vect->y * dnext.y) < 0.0) {
        dnext.x = -dnext.x;
        dnext.y = -dnext.y;
        }
      }
    lmemcpy (res,&dnext,sizeof(fpt));
    }
  }

// EX-Produkt zweier Vektoren
inline float EX(float ax, float ay, float bx, float by)
  {
  return ax * by - ay * bx;
  }

void turnpt (fpt FAR *res,fpt FAR *cont,fpt FAR *p,int left)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  DBWIN_ASSERT(cntsize >= 4);
  fpt FAR *tmpcnt = (fpt FAR *)GetGlobMem(cntsize * sizeof(fpt));
  if (hypot(cont[0].x - p->x, cont[0].y - p->y) <
      hypot(cont[cntsize - 1].x - p->x, cont[cntsize - 1].y - p->y))
    lmemcpy(tmpcnt, cont, cntsize * sizeof(fpt));
  else
    for (int ii = 0; ii < cntsize; ii++)
      tmpcnt[ii] = cont[cntsize - 1 - ii];
  float dx1 = tmpcnt[1].x - tmpcnt[0].x, dy1 = tmpcnt[1].y - tmpcnt[0].y;
  float dx2 = tmpcnt[2].x - tmpcnt[1].x, dy2 = tmpcnt[2].y - tmpcnt[1].y;
  int i = 3;
  int lastdir = EX(dx1,dy1,dx2,dy2) < 0.0;

#define CALC_NEXT_DIR  { \
    dx1 = dx2, dy1 = dy2; \
    dx2 = tmpcnt[i].x - tmpcnt[i - 1].x, dy2 = tmpcnt[i].y - tmpcnt[i - 1].y; \
    lastdir = EX(dx1,dy1,dx2,dy2) < 0.0; \
    i++; \
    }

  do {
    while ((i < cntsize) && (lastdir != left))
      CALC_NEXT_DIR;
    if (i < cntsize)
      CALC_NEXT_DIR;
    } while ((i < cntsize) && (lastdir != left));
  int firstind = 0;
  do {
    do {
      CALC_NEXT_DIR;
      } while ((i < cntsize) && (lastdir == left));
    if ((i - firstind) > 2)  // mindestens zweimal hintereinander nach links
      firstind = i;          // -> diesen Index merken
    if (i < cntsize)
      CALC_NEXT_DIR;
    } while ((i < cntsize) && (lastdir == left));
  if (i < cntsize) {
    res->x = (tmpcnt[firstind - 2].x + tmpcnt[i - 4].x) / (float)2.0;
    res->y = (tmpcnt[firstind - 2].y + tmpcnt[i - 4].y) / (float)2.0;
    }
  else {
    res->x = res->y = float(1.0E10);
    }
  FreeGlobMem(tmpcnt);
  }

/*--------< Berechnung einer Sehne an eine Kontur >---------*/
#define CLOCKWISE       1
void contmaxang (fpt FAR *res,fpt FAR *cont,fpt FAR *p,fpt FAR *g,int mode)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  double l = hypot (g->x,g->y);
  double xl = g->x / l;
  double yl = g->y / l;         // Normierung
  double maxang = (mode == CLOCKWISE) ? - 2.0 : 4.0 ;
  for (int i = 0 ; i < cntsize ; i++) {
    double xg = cont[i].x - p->x ;
    double yg = cont[i].y - p->y ;
    double lg = hypot (xg,yg);
    if (lg < 0.001) continue ;
    xg /= lg ; yg /= lg ;
    // Inprodukt (l1 * l2 * cos (phi) = cos (phi) wegen Normierung
    double inp = xg * xl + yg * yl ;
    // Exprodukt (l1 * l2 * sin (phi) -> > 0 fuer pos. Winkel, 
    // < 0 fuer neg. Winkel
    double exp = xg * yl - yg * xl ;
    if (exp < 0.0) inp = 2.0 - inp ;    // Umwandlung in stetige Funktion
    if (mode == CLOCKWISE) {
      if (inp > maxang) {
        maxang = inp ;
        lmemcpy (res,&cont[i],sizeof(fpt));
        }
      }
    else {
      if (inp < maxang) {
        maxang = inp ;
        lmemcpy (res,&cont[i],sizeof(fpt));
        }
      }
    }
  }

BOOL ptincont (fpt FAR *p,fpt FAR *cont)
  {
  int cntsize;
  cont = get_cont (cont, &cntsize);
  double dx0 = 100.0 ;
  double dy0 = 0.0 ;
  double oabst;
  int j = 0 ;
  int Anz = 0 ;
  for (int i = 0 ; i <= cntsize ; i++) {
    int ind = (i == cntsize) ? 0 : i ;
    double dx = cont[ind].x - p->x ;
    double dy = cont[ind].y - p->y ;
    double abst = dx * dy0 - dy * dx0 ;
    if (i > 0) {
      if (abst * oabst <= 0.0) {
        // Schnittpunkt gefunden
        fpt p2;
        p2.x = p->x + float(100.0) ;
        p2.y = p->y ;
        LPFPT args[5];
        args[1] = p ;
        args[2] = &p2 ;
        if (i < cntsize) {
          args[3] = cont + i - 1 ;
          args[4] = cont + i ;
          }
        else {
          args[3] = cont + i - 1 ;
          args[4] = cont ;
          }
        fpt *rli = (fpt *) LinInt ((pv FAR *)args);
        if (rli->x >= p->x)
          Anz ++ ;
        }
      }
    oabst = abst ;
    }
  return Anz % 2;
  }

