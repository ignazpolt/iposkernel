/*------------------------------------------------------------------*/
/*      Berechnung eines Zyklischen, ausgleichenden Splines         */
/*------------------------------------------------------------------*/
// $Header:   P:/marille/clinicum/rev/cycspl.cpv   1.2   02 Feb 1996 10:36:10   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/cycspl.cpv  $
// 
//    Rev 1.2   02 Feb 1996 10:36:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Sep 1994 11:32:00   HANNES
// Fehlerabsicherungen
// 
//    Rev 1.0   24 Jun 1994 17:04:10   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   05 Feb 1993 19:33:36   HANNES
// Korrekturen fuer den Fall einer Gerade
// 
//    Rev 1.0   02 Dec 1992 15:22:42   HANNES
// Initial revision.

#define WIN_VERS
#ifdef WIN_VERS
  #include <windows.h>
#else
  #define FAR
  #include <stdlib.h>

#endif

#include <stdio.h>
#include <math.h>
#include "dds32.h"

#ifdef WIN_VERS
  #include "dds.hpp"
  #include "globmem.h"
#endif




// Verwendeter Datentyp
typedef float DEC ;

/*------------------------------------------------------------------*/
/*      Loesung fuenfdiagonalen zyklischen Gleichungssystems        */
/*------------------------------------------------------------------*/
#ifndef WIN_VERS

DEC FAR *GetMem (int Degree)
  {
  DEC FAR *res = malloc (Degree * sizeof(DEC)) ;
  for (int i = 0 ; i < Degree ; i++)
    res[i] = 1.0E10 ;
  return res;
  }

void FreeMem (DEC FAR *y)
  {
  free (y) ;
  }
#else

static DEC FAR *GetMem (int Degree)
  {
  return (DEC FAR *) GetGlobMem (sizeof(DEC) * Degree);
  }

static void FreeMem (DEC FAR *y)
  {
  FreeGlobMem (y);
  }

#endif


DEC SumProd (DEC FAR *a,DEC FAR *b,int i0,int i1,int o)
  {
  DEC res = float(0.0) ;
  for (int i = i0 ; i <= i1 ; i++)
    res += a[i] * b[i+o] ;
  return res ;
  }

static void EquZyk5 (DEC FAR *K,DEC FAR *L,DEC FAR *M,
                           DEC FAR *N,DEC FAR *O,DEC FAR *z,int m,DEC FAR *p)
  {
// Anordunung der Matrix :
// -----------------------
// ( M0   N0   O0                                  K0   L0   )
// ( L1   M1   N1   O1                                  K1   )
// ( K2   L2   M2   N2    O2                                 )
// (                                                         )
// (                                                         )
// (                                                         )
// (                                                         )
// ( Om-1                                Km-1 Lm-1 Mm-1 Nm-1 )
// ( Nm   Om                                  Km   Lm   Mm   )
// z .. Stoervektor
// m .. Grad - 1 (Bsp: m = 6 -> 7 Unbekannte)
// p .. Loesung

  DEC a,b,c ;                          // Untere Diagonalmatrix
  DEC FAR *h ;                         // Hilfs - zeilenvektor
  DEC FAR *u,FAR *v,FAR *w,FAR *x ;    // Obere Diagonalmatrix
  DEC FAR *y ;                         // Zwischenvariable
  int i,j ;

  u = GetMem (m+1);
  v = GetMem (m+1);
  w = GetMem (m+1);
  x = GetMem (m+1);
  h = GetMem (m+1);
  y = GetMem (m+1);
  
  for (i = 0 ; i <= m ; i++) {
    if (i == 0) {
      a = M[0] ;
      u[1] = N[0] / a ;
      v[2] = O[0] / a ;
      x[1] = L[0] / a ;
      w[2] = K[0] / a ;
      y[0] = z[0] / a ;
      }
    else if (i == 1) {
      b = L[1] ;
      a = M[1] - b * u[1] ;
      u[2] = (N[1] - b * v[2]) / a ;
      v[3] = O[1] / a ;
      x[2] = (K[1] - b * x[1]) / a ;
      w[3] = - b * w[2] / a ;
      y[1] = (z[1] - b * y[0]) / a ;
      }
    else if (i == m) {
      h[3] = N[i] ;
      h[4] = O[i] - h[3] * u[1] ;
      for (j = 5 ; j <= m ; j++)
        h[j] = - (h[j-2] * v[j-3] + h[j-1] * u[j-3]) ;
      c = K[i] - (u[i-2] * h[i] + v[i-2] * h[i-1]) ;
      b = L[i] - (c * u[i-1] + h[i] * v[i-1] + SumProd (h,w,3,m-1,-1)) ;
      a = M[i] - (b * u[i] + c * v[i] + SumProd (h,x,3,m,-2)) ;
      y[i] = (z[i] - (SumProd (h,y,3,m,-3) + c * y[i-2] + b * y[i-1])) / a ;
      }
    else if (i == m - 1) {
      h[4] = O[m-1] ;
      h[5] = - h[4] * u[1] ;
      for (j = 6 ; j <= m ; j++)
        h[j] = - (h[j-2] * v[j-4] + h[j-1] * u[j-4]) ;
      c = K[i] - (u[i-2] * h[i+1] + v[i-2] * h[i]) ;
      b = L[i] - (u[i-1] * c + v[i-1] * h[m]) ;
      a = M[i] - (SumProd (h,w,4,m,-2) + c * v[i] + b * u[i]) ;
      u[i+1] = (N[i] - (SumProd (h,x,4,m,-3) + c * x[i-1] + b * v[i+1])) / a ;
      y[i] = (z[i] - (SumProd (h,y,4,m,-4) + c * y[i-2] + b * y[i-1])) / a ;
      }
    else {
      c = K[i] ;
      b = L[i] - c * u[i-1] ;
      a = M[i] - c * v[i] - b * u[i] ;
      u[i+1] = (N[i] - b * v[i+1]) / a ;
      v[i+2] = O[i] / a ;
      if (i < m - 2) {
        x[i+1] = - (c * x[i-1] + b * x[i]) / a ;
        if (i < m - 3)
          w[i+2] = - (c * w[i] + b * w[i+1]) / a ;
        }
      y[i] = (z[i] - (c * y[i-2] + b * y[i-1])) / a ;
      }
    }
  // Ganzes Spiel noch mal rueckwaerts zur Bildung der Loesung
  for (i = m ; i >= 0 ; i--) {
    p[i] = y[i] ;
    if (i < m) {
      p[i] -= u[i+1] * p[i+1] ;
      if (i < m - 1) {
        p[i] -= v[i+2] * p[i+2] ;
        if (i < m - 2) {
          p[i] -= x[i+1] * p[m] ;
          if (i < m - 3) {
            p[i] -= w[i+2] * p[m-1] ;
            }
          }
        }
      }
    }
  // fertig, Speicherplatz wieder freigeben
  FreeMem (h) ;
  FreeMem (y) ;
  FreeMem (u) ;
  FreeMem (v) ;
  FreeMem (w) ;
  FreeMem (x) ;
  }

/*---- Berechnung eines Periodischen Splines ---------*/
/*----------------------------------------------------*/
void PerSpl (DEC FAR *x,DEC FAR *u,DEC FAR *p,int Nz,DEC FAR *y,DEC FAR *y2)
  {
// x[i] ... Abszissenpunkte (0 <= i <= Nz !!)
// u[i] ... Ordinatenpunkte (0 <= i <  Nz !!)
// p[i] ... Gewichtungen    (-"-)
// y[i] ... Resultat (ausgleichende Punkte)
// y2[i] ... 2. Ableitung an den Stuetzpunkten
// Nz + 1 Punkte !!! (u[n] = u[0],p[n] = p[0])

  DEC FAR *a,FAR *b,FAR *c;     // Zyklisch Tridiagonale Matrix B
  DEC d,dp,dn,A,B,C;            // Hilfsvariablen (Matrix A,D);

  DEC dx,dxm1 ;                 // Hilfsvariablen
  DEC f,g,k,l,m,n,o;
  DEC FAR *K,FAR *L,FAR *M,FAR *N,FAR *O,FAR *z;

  a = GetMem (Nz) ;
  b = GetMem (Nz) ;
  c = GetMem (Nz) ;

  K = GetMem (Nz) ;
  L = GetMem (Nz) ;
  M = GetMem (Nz) ;
  N = GetMem (Nz) ;
  O = GetMem (Nz) ;

  z = GetMem (Nz) ;

  int i ;
  for (i = 0 ; i < Nz ; i++) {
    dx = x[i+1] - x[i] ;
    if (i == 0)
      dxm1 = x[Nz] - x[Nz-1] ;
    else
      dxm1 = x[i] - x[i-1] ;

    // Matrix B
    a[i] = DEC (-1.0 / dxm1) ;
    c[i] = DEC (-1.0 / dx) ;
    b[i] = DEC (-(a[i] + c[i])) ;
    }

  // Gesamtmatrix    
  for (i = 0 ; i < Nz ; i++) {
    dx = x[i+1] - x[i] ;
    if (i == 0)
      dxm1 = x[Nz] - x[Nz-1] ;
    else
      dxm1 = x[i] - x[i-1] ;

    // Matrix D
    if (i == 0) {
      dn = DEC (1.0 / p[Nz-1]) ;
      d =  DEC (1.0 / p[0]) ;
      dp = DEC (1.0 / p[1]) ;
      }
    else {
      dn = d ;
      d  = dp ;
      dp = DEC (1.0 /p[i+1]) ;
      }

    A = a[i] * dn ;
    B = b[i] * d ;
    C = c[i] * dp ;

    m = A * a[i] + B * b[i] + C * c[i] ;
    if (i == 0) {
      n = B * a[i+1] + C * b[i+1] ;
      o = C * a[i+2] ;
      k = A * c[Nz-2] ;
      l = A * b[Nz-1] + B * c[Nz-1] ;
      }
    else if (i == 1) {
      n = B * a[i+1] + C * b[i+1] ;
      o = C * a[i+2] ;
      k = A * c[Nz-1] ;
      l = A * b[i-1] + B * c[i-1] ;
      }
    else if (i == Nz - 2) {
      n = B * a[i+1] + C * b[i+1] ;
      o = C * a[0] ;
      k = A * c[i-2] ;
      l = A * b[i-1] + B * c[i-1] ;
      }
    else if (i == Nz - 1) {
      n = B * a[0] + C * b[0] ;
      o = C * a[1] ;
      k = A * c[i-2] ;
      l = A * b[i-1] + B * c[i-1] ;
      }
    else {
      n = B * a[i+1] + C * b[i+1] ;
      o = C * a[i+2] ;
      k = A * c[i-2] ;
      l = A * b[i-1] + B * c[i-1] ;
      }

    f = dx / 6 ;
    g = dxm1 / 6 ;

    K[i] = k ;
    O[i] = o ;
    M[i] = m + 2 * (g + f) ;
    N[i] = n + f ;
    L[i] = l + g ;

    // Stoerfunktion
    z[i] = - b[i] * u[i] ;
    if (i == 0) 
      z[i] -= a[i] * u[Nz-1] ;
    else
      z[i] -= a[i] * u[i-1] ;
    if (i == n-1)
      z[i] -= c[i] * u[0] ;
    else
      z[i] -= c[i] * u[i+1] ;
    }

  // Berechnung der 2. Ableitung (Loesung des Gleichungssystems)
  EquZyk5 (K,L,M,N,O,z,Nz-1,y2);
  y2[Nz] = y2[0] ;       // Periode...

  // Berechnung der Stuetzpunkte (y = D^-1 * (B,transponiert * y2 + D * u))
  for (i = 0 ; i < Nz ; i++) {
    // B,tramsponirt * y2
    if (i == 0)
      y[i] = c[Nz-1] * y2[Nz-1] ;
    else
      y[i] = c[i-1] * y2[i-1] ;
    y[i] += b[i] * y2[i] ;
    if (i == Nz - 1) 
      y[i] += a[0] * y2[0] ;
    else
      y[i] += a[i+1] * y2[i+1] ;

    // + D * y
    y[i] += u[i] * p[i] ;
    // * D^-1
    y[i] /= p[i] ;
    }
  y[Nz] = y[0] ;

  // fertig, Speicher frei geben
  FreeMem (a) ;
  FreeMem (b) ;
  FreeMem (c) ;

  FreeMem (K) ;
  FreeMem (L) ;
  FreeMem (M) ;
  FreeMem (N) ;
  FreeMem (O) ;

  FreeMem (z) ;
  }

// Berechnen der Koeffizienten fuer den Spline
void calPerSpl (DEC FAR *x,DEC FAR *u,DEC FAR *p,int n,DEC FAR *A,DEC FAR *B,DEC FAR *C,DEC FAR *D)
  {
  // x .. OrdinatenWerte (n + 1 Punkte !!!!)
  // u .. (ungeglaettet Abszissenwerte) (n Punkte)
  // p .. Gewichtungen (n + 1 Punkte)
  // A,B,C,D ... Resultate (n Punkte)
  // Berechnung von y und y2 ;
  DEC FAR *y  = GetMem (n + 1);
  DEC FAR *y2 = GetMem (n + 1);

  PerSpl (x,u,p,n,y,y2);

  for (int i = 0 ; i < n ; i++) {
    DEC dx = x[i+1] - x[i] ;
    DEC dy = y[i+1] - y[i] ;
    A[i] = DEC ((y2[i+1] - y2[i]) / (6.0 * dx)) ;
    B[i] = DEC (y2[i] / 2.0) ;
    C[i] = DEC (dy / dx - (y2[i+1] + 2.0 * y2[i]) * dx / 6.0) ;
    D[i] = y[i] ;
    }
  // Fertig ;
  FreeMem (y) ;
  FreeMem (y2) ;
  }

void CalSplVal (DEC FAR *t,DEC FAR *xn,int endpt,int Anzn,DEC FAR *A,DEC FAR *B,DEC FAR *C,DEC FAR *D)
  {
  DEC dt = t[endpt] / (Anzn - 1) ;
  DEC ta = float(0.0) ;
  int i,it ;
  for (i = it = 0 ; i < Anzn ; i++) {
    // Suchen des richtigen Abschnittes
    for ( ; ((ta > t[it+1]) && (it < endpt - 1)) ; ) it ++ ;
    DEC dta = ta - t[it] ;
    DEC dta2 = dta * dta ;
    xn[i] = A[it] * dta2 * dta + B[it] * dta2 + C[it] * dta + D[it] ;
    ta += dt ;
    }
  }

BOOL CycParSpline (DEC FAR *x,DEC FAR *y,int Anzo,int Anzn,DEC FAR *xn,DEC FAR *yn,DEC Gew)
  {
  // Berechnung des Parameters,
  // Saeubern der Punkte (dx != 0 !!!),
  // Suchen des Endpunktes ;

  DEC FAR *t = GetMem (Anzo + 1) ;
  DEC FAR *xs = GetMem (Anzo + 1) ;
  DEC FAR *ys = GetMem (Anzo + 1) ;

  int i,i1;
  int endpt = -1 ;

  t[0] = float(0.0) ;
  xs[0] = x[0] ;
  ys[0] = y[0] ;

  DEC oldabst = float(1.0E20) ;
  BOOL do_check = FALSE ;
  DEC minabst = float(-0.1) ;
  for (i = i1 = 1 ; i < Anzo ; i++) {
    DEC dx = x[i] - x[i-1] ;
    DEC dy = y[i] - y[i-1] ;
    DEC dl = DEC (hypot (dx,dy));
    if (fabs(dl) > 1.0E-3) {
      xs[i1] = x[i] ;
      ys[i1] = y[i] ;
      t[i1] = t[i1-1] + dl ;
      i1 ++ ;
      }
    }
  // Am Ende den Parameter noch justieren
  endpt = i1 ;
  if (endpt < 5) {
    FreeMem (t);
    FreeMem (xs);
    FreeMem (ys);
    return FALSE ;
    }
  t[endpt] = t[endpt-1] + DEC (hypot (xs[endpt-1] - x[0],ys[endpt-1]-ys[0]));
  xs[endpt] = x[0];
  ys[endpt] = y[0];
  
  // Berechnen der Spline - Paramete
  DEC FAR *A = GetMem (endpt) ;
  DEC FAR *B = GetMem (endpt) ;
  DEC FAR *C = GetMem (endpt) ;
  DEC FAR *D = GetMem (endpt) ;
  DEC FAR *p = GetMem (endpt+1) ;
  // Paramete initialisieren
  for (i = 0 ; i <= endpt ; i++) p[i] = Gew;

  // Berechnen der neuen X - Werte
  calPerSpl (t,xs,p,endpt,A,B,C,D);
  CalSplVal (t,xn,endpt,Anzn,A,B,C,D);

  // Berechnen der neuen Y - Werte
  calPerSpl (t,ys,p,endpt,A,B,C,D);
  CalSplVal (t,yn,endpt,Anzn,A,B,C,D);

  // fertig
  FreeMem (A);
  FreeMem (B);
  FreeMem (C);
  FreeMem (D);

  FreeMem (t);
  FreeMem (p);
  FreeMem (xs);
  FreeMem (ys);

  return TRUE ;
  }

GLOBALHANDLE smooth_cyccont (fpt FAR *old,int Anzo,int Anzn,double hardness)
  {
  // Umkopieren der Kontur in zwei Arrays
  int i ;

  if (Anzo < 5) return NULL ;

  DEC FAR *xo = GetMem (Anzo);
  DEC FAR *yo = GetMem (Anzo);

  for (i = 0 ; i < Anzo ; i++)
    xo[i] = old[i].x ,
    yo[i] = old[i].y ;

  // Speicher fuer neue Kontur
  DEC FAR *xn = GetMem (Anzn) ;
  DEC FAR *yn = GetMem (Anzn) ;

  // Und los gehts
  GLOBALHANDLE hGres = 0;
  if (CycParSpline (xo,yo,Anzo,Anzn,xn,yn,DEC (hardness))) {
    // Umspeichern in Globalen Handle als Kontur
    hGres = GlobalAlloc (GHND,Anzn * sizeof (fpt)) ;
    fpt FAR *ptn = (fpt FAR *) GlobalLock (hGres);

    for (i = 0 ; i < Anzn ; i++) {
      ptn[i].x = xn[i] ;
      ptn[i].y = yn[i] ;
      }
    }

  // fertig
  FreeMem (yn);
  FreeMem (xn);
  FreeMem (xo);
  FreeMem (yo);

  if (hGres) 
    GlobalUnlock (hGres);
  return hGres ;
  }

