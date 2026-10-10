//----------------------------------------------------
//      Berechnungsfunktionen mit Konturen            
//----------------------------------------------------
//
// $Header:   P:/marille/clinicum/rev/smooth.cpv   1.2   02 Feb 1996 10:35:38   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/smooth.cpv  $
// 
//    Rev 1.2   02 Feb 1996 10:35:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Aug 1995 00:20:30   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.0   24 Jun 1994 17:05:22   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.3   25 May 1993 15:33:38   MARTIN
// conn_cont korrigiert
// 
//    Rev 1.2   24 May 1993 14:31:18   MARTIN
// connect_cont
// 
//    Rev 1.1   22 Apr 1993 21:03:14   MARTIN
// Anpassung fuer geschnittene Konturen
// 
//    Rev 1.0   02 Dec 1992 15:43:54   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "cont.hpp"
#include "cutcont.hpp"
#define MODULENUM 23
#include "winass.hpp"

#define einsd6 0.166666666
void calspl (float FAR *X,float FAR *Y,float FAR *P,float FAR *A,float FAR *B,
             float FAR *C,float FAR *D,int N ,float FAR *Y2)
/*
X  Abszissenkoordinaten 
Y  Ordinatenkoordinaten 
P  Bewertungen	
A 
B  Koeffizienten des    
C  natuerlichen Splines 
D 
N  Anzahl der Punkte    
Y2 2 . Ableitung (reservierter Speicherplatz)
*/
  {
  /* Hilfsvariablen fuer Zwischenergebniss */
  float MAT0,MAT1,MAT2 ;
  float DXX,DXX1,F ;
  float AL,BE,GA,OBE,OGA,OOGA ;
  
  int K,K1,K2,KM1,KM2 ;
  int N1 = N - 1 ;
  int N2 = N1 - 1 ;
  int N3 = N2 - 1 ;

  K1 = 1 ;
  for (K = 2 ; K <= N ; K++) {
     D[K1] = X[K] - X[K1] ;
     K1 = K ;
     }
  D[0] = (float) 1.0 ;
  D[N] = (float) 1.0 ;

  /**************************************/
  /*  Berechnung der Zweiten Ableitung  */
  /**************************************/
  Y2 [0] = Y2 [N1] = (float) 0.0 ;
  for (K = 1 ; K <= N2 ; K++) {
    K1 = K + 1;
    K2 = K1 + 1;
    KM1 = K - 1 ;
    KM2 = KM1 - 1 ;
    DXX = (float) 1.0/D[K1] + (float) 1.0/D[K] ;
    DXX1 = (float) 1.0/D[KM1] + (float) 1.0/D[K] ;
    /* Inhomogenitaet */
    F = Y[K]/D[K] - Y[K1]*DXX + Y[K2]/D[K1] ;
    
    /* Berechnung der Matrix */
    MAT0 = (float) 1.0/(P[K]*D[K]*D[K]) + (float) 1.0/P[K1]*DXX*DXX +
    	   (float) 1.0/(P[K2]*D[K1]*D[K1]) + (D[K] + D[K1])/(float) 3.0 ;
    MAT1 = - ((float) 1.0/(P[K]*D[K])*DXX1 + (float) 1.0/(P[K1]*D[K])*DXX) + 
    	   D[K]/(float) 6.0 ;
    MAT2 = (float) 1.0/(P[K]*D[KM1]*D[K]) ;

    /*******************************************************************/
    /* Zur Loesung des Gleichungssystems mit dem Ergebnis Y'' wird die */
    /* Koeffizientenmatrix in gewohnter Manier in zwei Teile zerleget. */
    /* Die Zwischenspeicherung der 2. Teilmatrix erfogt in B[] und C[] */
    /*******************************************************************/
    
    if (K >= 3) C[K] = MAT2/OOGA ; else C[K] = (float) 0.0 ;
    if (K >= 2) B[K] = (MAT1 - OBE * C [K])/OGA ; else B[K] = (float) 0.0 ;
    if (K >= 3) AL = MAT2 ; else AL = (float) 0.0 ;
    if (K >= 2) BE = MAT1 - AL * B[KM1] ; else BE = (float) 0.0 ;
    GA = MAT0 - AL * C[K] - BE * B[K] ;
    OBE = BE ;
    OOGA = OGA ;
    OGA = GA ;
    
    /* Berechnung der Zwischenloesung (in A[] abspeichern) */
    if (K > 2) 
       A [K] = (F - AL * A[KM2] - BE * A[KM1]) / GA ;
    else if (K > 1)
       A [K] = (F - BE * A [KM1]) / GA ;
    else
       A [K] = F / GA ;
    
    }
    
  /* Berechnung der Zweiten Ableitung aus der Zwischenloesung */
  
  for (K = N2 ; K >= 1 ; K -- ) {
    if (K < N3)
       Y2 [K] = A [K] - B [K1] * Y2 [K1] - C [K2] * Y2 [K2] ;
    else if (K == N2)
       Y2 [K] = A [K] ;
    else 
       Y2 [K] = A [K] - B [K1] * Y2 [K1] ;
    K2 = K1 ;
    K1 = K ;   
    
    }
    
  /**********************************************************/
  /* Berechnung des neuen Funktionswertes aus der Ableitung */
  /**********************************************************/
  
  for (K = 1 ; K <= N ; K++) {
    KM1 = K - 1 ;
    KM2 = KM1 - 1 ;
    Y [K] *= P [K] ;
    if (K <= N2) 
      Y [K] -= Y2[K]/D[K] ;
    if ((K >= 2) && (K <= N1))
      Y [K] += Y2 [KM1] * ((float) 1.0/D[KM1] + (float) 1.0/D[K]) ;
    if (K >= 3) 
      Y [K] -= Y2 [KM2] / D [KM1] ;
    Y[K] /= P [K] ;
    
    }
        
  /******************************************/
  /* Berechnung der Polinom - Koeffizienten */
  /******************************************/
  
  Y2 [0] = Y2 [N1] = (float) 0.0 ;
  for (K = 1; K <= N1 ; K ++) {
    K1 = K + 1 ;
    KM1 = K -1 ;
    A [K] = (float) einsd6 / D [K] * (Y2 [K] - Y2 [KM1]) ;
    B [K] = (float) 0.5 * Y2 [KM1] ;
    C [K] = (Y[K1] - Y[K]) / D[K] - (float) einsd6 * D[K] * (Y2[K] + (float) 2.0*Y2[KM1]) ;
    D [K] = Y[K] ;
    }

  }

GLOBALHANDLE smooth_cont (fpt FAR *old,int Anzo,int Anzn,double hardness,
        float FAR *P)
  {
  GLOBALHANDLE hGres ;
  GLOBALHANDLE hGtmp ;

  /* Arrays, die zur Berechnung benoetigt werden  */
  float FAR *Ax,FAR *Ay ;   /*				  */
  float FAR *Bx,FAR *By ;   /*	Polinom - Koeffizienten   */
  float FAR *Cx,FAR *Cy ;   /*				  */
  float FAR *Dx,FAR *Dy ;   /*				  */
  float FAR *Xs,FAR *Ys ;   /*  Arbeits - arrays	  */

  float FAR *T; 	   /* Parameter */
  float FAR *Y2 ;	   /* 2. Ableitung (in calspl benoetigt) */
  int mi ;                 /* Anzahl der Punkte */

  /* Hilfsvariablen */
  float U,V,Delta,dxn,dxn2,dxn3,border,TMOM,step_go ;

  int i,i1 ;

  Anzn -- ;
  Anzo ++ ;     // ???

  if (Anzo < 3) return NULL ;
  if (Anzn < 3) return NULL ;

  /* Speicherverwaltung */
  int AnzArrs = (P == NULL) ? 13 : 12 ;
  i = AnzArrs * (Anzo + 1) ;
  hGtmp = GlobalAlloc (GHND,i * sizeof (float)) ;
  Ax = (float FAR *) GlobalLock (hGtmp) ;
  Bx = Ax + Anzo + 1;
  Cx = Bx + Anzo + 1;
  Dx = Cx + Anzo + 1;
  Ay = Dx + Anzo + 1;
  By = Ay + Anzo + 1;
  Cy = By + Anzo + 1;
  Dy = Cy + Anzo + 1;
  T  = Dy + Anzo + 1;
  Y2 = T  + Anzo + 1;
  Xs = Y2 + Anzo + 1;
  Ys = Xs + Anzo + 1;

  if (P == NULL) {
    P  = Ys + Anzo + 1;
    /* Initialisieren der Bewertungen */
    for (i = 0 ; i <= Anzo ; i++)
      P [i] = (float) hardness ;
    }

  /* Berechnung des Parameters 					*/
  /* Als Bezug hierfuer dient der Abstand zwischen den Punkten  */
  T [1] = (float) 0.0 ;
  i1 = 1 ;
  mi = 2 ;
  Xs [1] = old[0].x ;
  Ys [1] = old[0].y ;
  for (i = 1 ; i < Anzo ; i ++) {
    U = old[i-1].x - old[i1-1].x ;
    V = old[i-1].y - old[i1-1].y ;
    Delta = (float) sqrt ((double) (U*U + V*V)) ;
    if (Delta > (float) 0.01) {
      Xs [mi] = old[i-1].x ;
      Ys [mi] = old[i-1].y ;
      P [mi] = P [i] ;
      T [mi] = T [mi-1] + Delta ;
      mi ++ ;
      }
    i1 = i ;
    }
  mi -- ;

  /************************************************************************/
  /* Berechnung der Polinom - Koeffizienten fuer die X- u. Y - Koordinate */
  /************************************************************************/
  
  /* X - Koordinate */
  calspl (T , Xs , P , Ax , Bx , Cx , Dx , mi , Y2 ) ;

  /* Y - Koordinate */
  calspl (T , Ys , P , Ay , By , Cy , Dy , mi , Y2 ) ;
  
  /*========================================================*/
  /*  Berechnung der Kurve aus den Polinom - Koeffizienten  */
  /*========================================================*/

  hGres = GlobalAlloc (GHND,(Anzn + 1) * sizeof (fpt)) ;
  fpt FAR *ptn = (fpt FAR *) GlobalLock (hGres);
  
  step_go = (T[mi] - T[1]) / ((float) Anzn) ;
  i = 1 ;  /* Index der aktuellen Koeffizienten */
  i1 = 0 ; /* Index der Kurvenkoordinaten */
  border = T [mi] + float (step_go/2.0) ;
  /* Schleife ueber alle Punkte */
  for (TMOM = T [1] ; TMOM < border ; TMOM += step_go ) {

     /* Suchen der aktuellen Koeffizienten */
     while ((TMOM > T[i+1]) && (i < mi - 1)) i++ ;
     
     /* Berechnung der Funktionswerte */
     dxn = TMOM - T [i] ; dxn2 = dxn * dxn ; dxn3 = dxn2 * dxn ;
     
     ptn[i1].x = Ax[i] * dxn3 + Bx[i] * dxn2 + Cx[i] * dxn + Dx[i] ;
     ptn[i1].y = Ay[i] * dxn3 + By[i] * dxn2 + Cy[i] * dxn + Dy[i] ;
     i1++ ;
     }
    
  /* Allocierte Speicherplatz wieder freigeben */
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);

  // fertig
  GlobalUnlock (hGres);
  return hGres ;
  }

static void copycont (fpt FAR *dest,fpt FAR *source,int len)
  {
  lmemcpy (dest,source,len * sizeof (fpt));
  }

static void copyivcont (fpt FAR *dest,fpt FAR *source,int len)
  {
  fpt FAR *d = dest + len - 1 ;
  fpt FAR *s = source ;
  for (int i = len ; i > 0 ; i--) {
    lmemcpy (d,s,sizeof (fpt));
    d -- ;
    s ++ ;
    }
  }

static void ivcont (fpt FAR *c,int len)
  {
  fpt FAR *b = c ;
  fpt FAR *e = c + len - 1 ;
  for ( ; b < e ; ) {
    fpt dummy ;
    lmemcpy (&dummy,b,sizeof (fpt));
    lmemcpy (b,e,sizeof(fpt));
    lmemcpy (e,&dummy,sizeof(fpt));
    b++ ;
    e-- ;
    }
  }

static double distpt (fpt FAR *p1,fpt FAR *p2)
  {
  return hypot (p1->x - p2->x,p1->y - p2->y) ;
  }

GLOBALHANDLE combine_cont (LPFPT *oldconts,int AnzOldConts,int newPt,double hard)
  {
  int anzold[6];
  int gessize ;
  fpt FAR *cmbcont ;
  int i ;
  for (i = gessize = 0 ; i < AnzOldConts ; i++) {
    oldconts[i] = get_cont(oldconts[i], anzold + i);
    gessize += anzold[i] ;
    }
  GLOBALHANDLE hGtmp = GlobalAlloc (GHND,sizeof (fpt) * gessize) ;
  cmbcont = (fpt FAR *) GlobalLock (hGtmp);

  // Zusammensetzen einer Gesamt - Kontur
  int cmbsize = 0 ;

  // 1. Kontur 1 : 1 uebernehmen
  copycont (cmbcont,oldconts[0],anzold[0]) ;
  cmbsize = anzold[0] ;

  for (i = 1 ; i < AnzOldConts ; i++) {
    int nst0 ;     // Punkt in der anzuhaengenden Kontur, der dem 1.Punkt 
                   // der Gesamtkontur am naehsten ist
    int nstc ;     // - " - letzten -"-
    double d0 ;    // Abstand anzuhaengender Kontur zum 1. Punkt der Gesamtkontur
    double dc ;    // - " - letzten -"-

    // Berechnen der oben genannten Daten
    fpt FAR *act;
    fpt FAR *ec = cmbcont + cmbsize - 1 ;
    d0 = dc = 1.0E100;
    int j ;
    for (j = 0 , act = oldconts[i] ; j < anzold[i] ; j++ , act ++) {
      double actd0 = distpt (cmbcont,act);
      double actdc = distpt (ec,act);
      if (actd0 < d0) {
        d0 = actd0 ;
        nst0 = j ;
        }
      if (actdc < dc) {
        dc = actdc ;
        nstc = j ;
        }
      }

    // Richtiges zusammenhaengen
    if (d0 < dc) {
      // Resultierende Kontur muss umgedreht werden
      // (Kann eigentlich bei den zu erwartenden Anwendungen 
      // nur das erste mal passieren)
      ivcont (cmbcont,cmbsize);
      nstc = nst0 ;     // nstc ist das einzige, was zaehlt
      }

    if (nstc > anzold[i] - nstc) {
      // Anzuhaengende Kontur muss verkehrt angehaengt werden
      copyivcont (cmbcont + cmbsize,oldconts[i],nstc) ;
      cmbsize += nstc ;
      }
    else {
      // Anzuhaengende Kontur kann ab nstc richtig angehaengt werden
      copycont (cmbcont + cmbsize,oldconts[i] + nstc + 1,anzold[i] - nstc - 1);
      cmbsize += anzold[i] - nstc - 1 ;
      }
    }
 
  // Glaetten der Gesamt - Kontur
  GLOBALHANDLE hGres = smooth_cont (cmbcont,cmbsize,newPt,hard);
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  // fertig
  return hGres;
  }

GLOBALHANDLE connect_cont (LPFPT *oldconts,int AnzOldConts,int FAR *PtCount)
  {
  DBWIN_ASSERT(AnzOldConts >= 2);
  int anzold[8];
  int gessize = 1;
  for (int i = 0 ; i < AnzOldConts ; i++) {
    oldconts[i] = get_cont(oldconts[i], anzold + i);
    DBWIN_ASSERT(oldconts[i] != NULL);
    gessize += (anzold[i] - 1);
    }
  GLOBALHANDLE hGtmp = GlobalAlloc (GHND,sizeof (fpt) * gessize);
  fpt FAR *cmbcont = (fpt FAR *) GlobalLock (hGtmp);

  int actpos = 0;
  if ((hypot(oldconts[0][0].x - oldconts[1][0].x,
             oldconts[0][0].y - oldconts[1][0].y) < 1.0E-3) ||
      (hypot(oldconts[0][0].x - oldconts[1][anzold[1]-1].x,
             oldconts[0][0].y - oldconts[1][anzold[1]-1].y) < 1.0E-3)) {
    for (int j = anzold[0] - 1; j >= 0; j--)
      cmbcont[actpos++] = oldconts[0][j];
    }
  else {
    lmemcpy(cmbcont, oldconts[0], anzold[0] * sizeof(fpt));
    actpos = anzold[0];
    }
  for (i = 1; i < AnzOldConts; i++) {
    if (hypot(oldconts[i][0].x - cmbcont[actpos-1].x,
              oldconts[i][0].y - cmbcont[actpos-1].y) < 1.0E-3) {
      for (int j = 1; j < anzold[i]; j++)
        cmbcont[actpos++] = oldconts[i][j];
      }
    else if (hypot(oldconts[i][anzold[i]-1].x - cmbcont[actpos-1].x,
               oldconts[i][anzold[i]-1].y - cmbcont[actpos-1].y) < 1.0E-3) {
      for (int j = anzold[i] - 2; j >= 0; j--)
        cmbcont[actpos++] = oldconts[i][j];
      }
    else {
      DBWIN_ASSERT(FALSE);
      }
    }

  GlobalUnlock (hGtmp);
  *PtCount = actpos;
  return hGtmp;
  }

GLOBALHANDLE smextcont (fpt FAR *cont,int anzo,int anzn,
                double bhard,double ehard,double lb,int anzpt,LPFPT *pts)
  {
  // Berechnen der Haerten der einzelnen Punkte
  GLOBALHANDLE hGp = GlobalAlloc (GHND,sizeof(float) * (anzo + 1));
  float FAR *P = (float FAR *) GlobalLock (hGp);
  P[0] = float (bhard) ;
  ehard -= bhard ;

  for (int i = 0 ; i < anzo ; i++) {
    P[i+1] = float (bhard) ;
    for (int j = 0 ; j < anzpt ; j++) {
      double abst = hypot (cont[i].x - pts[j]->x,cont[i].y - pts[j]->y);
      double extra = ehard * exp (- abst / lb) ;
      P[i+1] += float (extra) ;
      }
    }

  // Durchfuehrung der Glaettung
  GLOBALHANDLE hGcont = smooth_cont (cont,anzo,anzn,0.0,P);
  GlobalUnlock (hGp);
  GlobalFree (hGp);
  return hGcont ;
  }

