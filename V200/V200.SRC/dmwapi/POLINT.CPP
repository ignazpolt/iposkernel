/*-------------------------------------------------*/
/* polint.cpp - polynomial interpolation           */
/*-------------------------------------------------*/
//  $Header:   P:/marille/clinicum/dmwapi/rev/polint.cpv   1.1   02 Feb 1996 10:46:18   GERHOLD  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/polint.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:46:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:52   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   23 Feb 1994 18:22:42   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define MODULENUM 70
#include "winass.hpp"
#define JUST_EM
#include "dds.hpp"
#include "cont.hpp"


#define EPS     (float)1E-10
#define EPSD    1E-10
#define EPSD1   1E-5
#define MAXDIM  100

// Loesung eines Gleichnungssystems mit totalpivotisierung
////////////////////////////////////////////////////////////
DLLExport BOOL _export WINAPI SolveEquSys (double FAR *a,double FAR *b,double FAR *res)
  {
  int dim = GetBlockSize (res) / sizeof (*res);
  WIN_ASSERT (GetBlockSize (b) == dim * sizeof (*b));
  WIN_ASSERT (GetBlockSize (a) == dim * dim * sizeof (*a));
  WIN_ASSERT (dim <= MAXDIM);

  int FAR *rIndex = (int FAR *) GetGlobMem (sizeof(int) * dim);
  BOOL FAR *pDone = (BOOL FAR *) GetGlobMem (sizeof(int) * dim);
  for ( int s = 0 ; s < dim ; s++)
    rIndex[s] = -1;

  for ( s = 0 ; s < dim ; s++) {
    double pEle = 0.0 ;
    int pReihe = -1;
    // Suchen des Pivot - Elementes
    for (int r = 0 ; r < dim ; r++)
      if ((!pDone[r]) && (fabs (a[r * dim + s]) > fabs (pEle))) 
        pReihe = r, pEle = a[r * dim + s];
    if ((pReihe == -1) || (fabs (pEle) <= EPSD)) {
      // So nicht
      FreeGlobMem (rIndex);
      FreeGlobMem (pDone);
      return FALSE ;
      }
    // Pivotisieren des Gleichungssystems
    for (r = 0 ; r < dim ; r++) {
      if (r == pReihe) continue ;
      double qi = - a[r * dim + s] / pEle ;
      a[r * dim + s] = 0;
      for (int s1 = s + 1 ; s1 < dim ; s1 ++) {
        a[r * dim + s1] += qi * a[pReihe * dim + s1];
        }
      b[r] += qi * b[pReihe];
      }
    pDone [pReihe] = TRUE ;

    // Index fuer die Loesung noch setzen
    WIN_ASSERT (rIndex[pReihe] == -1);
    rIndex[pReihe] = s;
    }
  // Berechnung der Loesung
  ////////////////////////////
  for (int r = 0 ; r < dim ; r++) {
    // Kontrolle, ob die totalpivotisierung gelungen ist
    WIN_ASSERT (rIndex[r] >= 0);
    for (s = 0 ; s < dim ; s++) {
      if (s == rIndex[r]) continue;
      WIN_ASSERT (fabs (a[r * dim + s]) <= EPSD1);
      }
    res[r] = b[r] / a[r * dim + rIndex[r]] ;
    }
  return TRUE ;
  }

DLLExport void _export WINAPI GetPolintKoeff(float FAR *x, float FAR *y, int Anz, 
                                      KoefDesc FAR *Kx)
  {
  // Untersuchen, ob die Potenzen Sinn ergeben
  // (sie muessen geordnet sein !!)
  int maxKoeff = -1;
  int AnzKoeff = GetBlockSize (Kx) / sizeof (*Kx);
  for (int i = 0 ; i < AnzKoeff ; i++) {
    WIN_ASSERT (Kx[i].potenz > maxKoeff);
    maxKoeff = Kx[i].potenz;
    }

  //                                           Anz
  // Berechnen der Terme xk[k] = [x^k] def. als ä  (x[i]^k)
  //                                          i = 0
  //                                             Anz
  //                     yxk[k] = [yx^k] def. als ä  (y * x[i]^k)
  //                                            i = 0
  double FAR *xk  = (double FAR *) GetGlobMem ((2 * (maxKoeff+1) - 1) * sizeof (double)) ;
  double FAR *yxk = (double FAR *) GetGlobMem ((maxKoeff+1) * sizeof (double)) ;

  for (int p = 0 ; p < maxKoeff ; p++)
    xk[p] = yxk[p] = 0.0 ;

  xk[0] = double (Anz) ;
  float FAR *xact = x ;
  float FAR *yact = y ;
  for (i = 0 ; i < Anz ; i++) {
    double xp = 1.0 ;
    yxk[0] += double (*yact);
    for (p = 1 ; p <= maxKoeff ; p++) {
      xp    *= double (*xact);
      xk[p]  += xp ;
      yxk[p] += double (*yact) * xp ;
      }
    for ( ; p < 2 * (maxKoeff + 1) - 1 ; p++) {
      xp    *= double (*xact);
      xk[p]  += xp ;
      }
    xact += 2 ;     // Achtung, es werden fpts bearbeitet !
    yact += 2 ;
    }

  // Aufstellung des Gleichungssystems
  //////////////////////////////////////
  double FAR *a = (double FAR *) GetGlobMem (sizeof(double) * AnzKoeff * AnzKoeff);
  double FAR *b = (double FAR *) GetGlobMem (sizeof(double) * AnzKoeff);
  for (int r = 0 ; r < AnzKoeff ; r++) {
    b[r] = yxk[Kx[r].potenz] ;
    for (int s = 0 ; s < AnzKoeff ; s++)
      a[r * AnzKoeff + s] = xk[Kx[r].potenz + Kx[s].potenz] ;
    }
  // Berechnen des Gleichnungssystems
  //////////////////////////////////////
  double FAR *res = (double FAR *) GetGlobMem (sizeof(double) * AnzKoeff);
  WIN_ASSERT (SolveEquSys (a,b,res));

  for (r = 0 ; r < AnzKoeff ; r++)
    Kx[AnzKoeff - 1 - r].val = res[r];

  FreeGlobMem (a);
  FreeGlobMem (b);
  FreeGlobMem (xk);
  FreeGlobMem (yxk);
  FreeGlobMem (res);
  }


double Myhypot (double x,double y)
  {
  return sqrt (x*x + y*y);
  }

DLLExport void _export WINAPI polint_parametric(fpt FAR *pts, KoefDesc FAR *Kx, 
                                         KoefDesc FAR *Ky
                                        )
  {
  fpt FAR *t;

  /* Speicher fuer den Parameter allocieren */
  int n = GetBlockSize (pts) / sizeof (*pts);
  t = (fpt FAR *) GetGlobMem (n * sizeof(fpt));

  /* Erzeugen des Parameters */
  t[0].x = float (0.0);
  for(int i = 1 ; i < n; i++)
    t[i].x = t[i-1].x + float (Myhypot(pts[i].x - pts[i-1].x, pts[i].y - pts[i-1].y));

  /* Skalieren */
  WIN_ASSERT (fabs(t[n-1].x) > EPS);
  for(i = 1; i < n - 1; i++) {
    t[i].x /= t[n-1].x;
    }
  t[n-1].x = float (1.0);

  /* Berechnen der Koeffizienten fuer die X - Koordinaten */
  GetPolintKoeff (&t->x, &pts->x, n, Kx);
  /* Berechnen der Koeffizienten fuer die Y - Koordinaten */
  GetPolintKoeff (&t->x, &pts->y, n, Ky);

  /* Speicherplatz fuer den Parameter wieder freigeben */
  FreeGlobMem (t);
  }

DLLExport void _export WINAPI GetPolCnt (fpt FAR *cnt,int Anz,double xmin,
                                    double xmax,KoefDesc FAR *k
                                  )
  {
  WIN_ASSERT (Anz >= 2);
  double tstep = (xmax - xmin) / double (Anz - 1);
  int AnzKoeff = GetBlockSize (k) / sizeof (*k);
  for (int i = 0 ; i < Anz ; i++) {
    double y = 0 ;
    double xp = 1.0 ;
    int j = 0 ; 
    for (int p = 0 ; ; p++ , xp *= xmin) {
      if (p == k[j].potenz) {
        y += xp * k[j].val ;
        if (j == AnzKoeff - 1) {
          cnt[i].x = float (xmin) ;
          cnt[i].y = float (y) ;
          break ;
          }
        j++ ;
        }
      }
    xmin += tstep;
    }
  }

DLLExport void _export WINAPI GetPolCnt (fpt FAR *cnt,int Anz,double tmin,
                                    double tmax,KoefDesc FAR *kx,KoefDesc FAR *ky
                          )
  {
  WIN_ASSERT (Anz >= 2);
  double tstep = (tmax - tmin) / double (Anz - 1);
  int xKoeff = GetBlockSize (kx) / sizeof (*kx);
  int yKoeff = GetBlockSize (ky) / sizeof (*ky);
  for (int i = 0 ; i < Anz ; i++) {
    double y = 0.0,x = 0.0,tp = 1.0 ;
    int jx = 0,jy = 0 ; 
    BOOL xdone = FALSE,ydone = FALSE ;
    for (int p = 0 ; !((xdone) && (ydone)); p++ , tp *= tmin) {
      if (p == kx[jx].potenz) {
        x += tp * kx[jx].val ;
        if (jx == xKoeff - 1) {
          cnt[i].x = float (x);
          xdone = TRUE ;
          }
        jx++ ;
        }
      if (p == ky[jy].potenz) {
        y += tp * ky[jy].val ;
        if (jy == yKoeff - 1) {
          cnt[i].y = float (y);
          ydone = TRUE ;
          }
        jy++ ;
        }
      }
    tmin += tstep;
    }
  }



