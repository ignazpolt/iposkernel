///////////////////////////////////////////////////
//  Kettenlinieninterpolation
///////////////////////////////////////////////////
#include <windows.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#include "cont.hpp"
#define MODULENUM  71
#include "winass.hpp"

// Parameter zwischenmerken, damit nicht so viele
// uebergeben werden muessen
///////////////////////////////////////////////////
static int AnzPt;
static fpt FAR *pts;
static double FAR *gew;
static double jakobi_mat[2][2],iv_mat[2][2];
static double koeffs[2];
static double dkoeffs[2];
static double fault[2];

#define A koeffs[0]
#define B koeffs[1]
static double C;
#define DA dkoeffs[0]
#define DB dkoeffs[1]
#define FA fault[0]
#define FB fault[1]

#define DJ jakobi_mat
#define DI iv_mat

void InvertJakobi ()
  {
  double det = DJ[0][0]*DJ[1][1] - DJ[0][1]*DJ[1][0];
  DI[0][0] = DJ[1][1] / det ;
  DI[1][0] = DI[0][1] = -DJ[0][1] / det ;
  DI[1][1] = DJ[0][0] / det;
  }

void GetFault_Jakobi ()
  {
  lmemset (fault,'\0',sizeof(fault));
  lmemset (DJ,'\0',sizeof(DJ));
  for (int i = 0 ; i < AnzPt ; i++) {
    double cxi = C * double (pts[i].x);
    double shi = sinh(cxi);
    double chi = cosh(cxi);
    double f   = A + B * chi - double(pts[i].y);

    FA += f ;
    FB += f * chi ;

    DJ[0][1] += chi ;
    DJ[1][1] += chi * chi;
    }
  DJ[1][0] = DJ[0][1] ;
  DJ[0][0] = double (AnzPt) ;
  }

void GetDKoeff ()
  {
  DA = DI[0][0] * FA + DI[0][1] * FB;
  DB = DI[1][0] * FA + DI[1][1] * FB;
  }

#define EPS  1.0E-3
BOOL CheckDKoeff ()
  {
  return ((DA * DA + 1000.0 * DB * DB) < EPS) ;
  }

void GetNewKoeff ()
  {
  A -= DA ;
  B -= DB ;
  }

inline double ActAbsFault (int i,double a,double b,double c)
  {
  double h = a + b * cosh (c * double(pts[i].x)) - double(pts[i].y) ;
  return h * h;
  }

void GetAbsFault (double FAR *res,double a,double b,double c)
  {
  *res = 0.0 ;
  for (int i = 0 ; i < AnzPt ; i++)
    *res += ActAbsFault (i,a,b,c);
  }

#define MAXITERATIONS 1000
void GetAB ()
  {
  GetFault_Jakobi () ;
  InvertJakobi () ;
  GetDKoeff ();
  GetNewKoeff ();
  }

void GetAbsFault (double FAR *res,double expc)
  {
  C = exp (expc);
  GetAB ();
  GetAbsFault (res,A,B,C);
  }

void GetPts (fpt FAR *p,BOOL FAR *r,int anz)
  {
  int j = 0 ;
  for (int i = 0 ; i < anz ; i++) {
    if (!r[i])
      pts[j++] = p[i] ;
    }
  }

#define MAXDEPTH 10
DLLExport void _export WINAPI KettenlinienInterpolation (fpt FAR *p,int anz,double FAR *a,double FAR *b,double FAR *c,double direction)
  {
  AnzPt = anz;
  pts = (fpt FAR *) GetGlobMem (AnzPt * sizeof(fpt));
  BOOL FAR *rem = (BOOL FAR *) (GetGlobMem (AnzPt * sizeof(BOOL)));
  GetPts (p,rem,anz);

  // Startlinien
  KoefDesc FAR *k = (KoefDesc FAR *) GetGlobMem (sizeof(*k) * 2);
  k[0].potenz = 0;
  k[1].potenz = 2;

  GetPolintKoeff(&p->x,&p->y,anz,k);

  C = 0.01;
  B = 2.0 * k[1].val / C / C ;
  A = k[0].val - B ;

  FreeGlobMem (k);

  for ( int AnzRemoved = 0 ; ; ) {
    double expc = log(0.05);
    double step = 0.2 ;
    double f0;
    GetAbsFault (&f0,expc);
    for (int depth = 0 ; depth < MAXDEPTH ; depth ++ ) {
      if ((expc - step < -15.0) || (expc + step > -1.5)) break ;
      double dir,fold,oexp,fp,fm ;
      // Untersuchung der Richtung 
      GetAbsFault (&fp,expc+step);
      GetAbsFault (&fm,expc-step);
      if (fp < f0)      dir = 1.0  , fold = fp ;
      else if (fm < f0) dir = -1.0 , fold = fm ;
      else              dir = 0.0 ;
      oexp = expc + dir * step ;

      if (fabs(dir) > 0.01) {
        // In der guten Richtung weitersuchen
        for ( ; ; ) {
          expc = oexp + dir * step ;
          if ((expc < -15.0) || (expc > -1.5)) {
            expc = oexp ;
            break ;
            }
          GetAbsFault (&f0,expc);
          if (f0 > fold) {
            // Es ist wieder schlechter geworden -> aufhoeren
            expc = oexp ;
            f0 = fold ;
            break ;
            }
          oexp = expc ;
          fold = f0 ;
          }
        }
      step /= 2.0 ;     // Schrittweite verkleinern
      }
    C = exp (expc);
    GetAB ();

    if (B * direction >= 0.0) break ; // Alles in Ordnung

    // Scheisse, der Bogen ist umgeklappt -> extermsten Punkt entfernen
    if ((AnzRemoved >= 3) || (anz - AnzRemoved <= 3)) {
      // so auch nicht
      A = B = C = 1.0E10;
      break ;
      }
    double xmax = -1.0E10;
    int doRemove = -1;
    for (int i = 0 ; i < anz ; i++) {
      if ((!rem[i]) && (fabs(p[i].x) > xmax)) {
        xmax = fabs(p[i].x) ;
        doRemove = i;
        }
      }
    WIN_ASSERT (doRemove >= 0);
    rem[doRemove] = TRUE;
    GetPts (p,rem,anz);

    AnzPt -- ;
    AnzRemoved ++ ;
    }

  *a = A ;
  *b = B ;
  *c = C ;

  FreeGlobMem (pts);
  FreeGlobMem (rem);
  }

double arccosh (double x)
  {
  double x2 = x * x;
  if (x2 < 1.0) return 0.0 ;
  else          return log(x + sqrt(x2 - 1.0));
  }

DLLExport void _export WINAPI GetKettenLinie (fpt FAR *cnt,int Anz,KLParam FAR *p)
  {
  WIN_ASSERT (Anz > 2);
  double tstep = (p->xmax - p->xmin) / double (Anz - 1) ;

  double xmin = p->xmin;
  for (int i = 0 ; i < Anz ; i++) {
    double cxi = p->c * xmin ;
    if (fabs(cxi) > 150.0) cxi = 150.0 ;
    double y = p->a + p->b * cosh (cxi);

    double x ;
    if (y > p->ymax) {
      x = arccosh ((p->ymax - p->a) / p->b) / p->c;
      if (xmin < 0.0) x = -x ;
      y = p->ymax ;
      }
    else if (y < p->ymin) {
      x = arccosh ((p->ymin - p->a) / p->b) / p->c;
      if (xmin < 0.0) x = -x ;
      y = p->ymin ;
      }
    else 
      x = xmin ;

    cnt[i].x = float (x) ;
    cnt[i].y = float (y);
    xmin += tstep;
    }
  }

