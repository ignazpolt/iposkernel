//--------------------------------------------------------------
//      2 - Dimensionale Koordiantentransformationen            
//--------------------------------------------------------------
//
// $Header:   P:/marille/clinicum/frmobj/rev/sc2d.cpv   1.1   02 Feb 1996 10:49:12   GERHOLD  $
// $Log:   P:/marille/clinicum/frmobj/rev/sc2d.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:49:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:45:48   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.16   07 Feb 1994 13:55:02   HANNES
// Rausloeschen der GetRunDatas...
// 
//    Rev 1.15   12 Jan 1994 11:12:00   HANNES
// Unnoetige Includes eleminiert
// 
//    Rev 1.14   29 Nov 1993 08:54:52   HANNES
// Updatemodus beim Schreiben
// 
//    Rev 1.13   22 Sep 1993 09:17:34   HANNES
// Version nach St. Poelten
// 
//    Rev 1.12   18 Aug 1993 10:34:42   HANNES
// Fehlerkorrektur in Bringtooverlap
// 
//    Rev 1.11   18 Jun 1993 15:07:56   MARTIN
// GetData
// 
//    Rev 1.10   02 Jun 1993 17:23:46   MARTIN
// Fehlerkorrektur: lokale Kopie des Punktes ungueltig setzen,
//                  wenn Skalierung nicht moeglich ist
// 
//    Rev 1.9   01 Jun 1993 12:46:42   MARTIN
// Korrektur in uScPt (ein DelData zuviel)
// 
//    Rev 1.8   28 May 1993 21:15:20   HANNES
// DelData eingefuehrt
// 
//    Rev 1.7   19 Apr 1993 01:09:42   MARTIN
// neue Funktion uScContPart
// (und uScCont vereinfacht)
// 
//    Rev 1.6   02 Apr 1993 17:47:18   HANNES
// Strukturbereinigung
// 
//    Rev 1.5   17 Mar 1993 18:11:22   MARTIN
// 32 Bit Umstellung der Scripts
// 
//    Rev 1.4   05 Feb 1993 19:33:00   MARTIN
// uScExplicit und uScSkipScale
// 
//    Rev 1.3   02 Feb 1993 19:08:42   MARTIN
// uInvScale
// 
//    Rev 1.2   02 Feb 1993 18:45:24   HANNES
// Umbau auf einzelne Durchlaeufe
// 
//    Rev 1.1   29 Jan 1993 19:02:16   HANNES
// Verbesserte Algorythmen zur Handhabung von Sklierungen
// 
//    Rev 1.0   02 Dec 1992 15:41:30   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"

#include "printer.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "cutcont.hpp"

/*---------------------------------------------------------------------*/
/*      Durchfuehrung eines Skalierung (res = A * x + B)               */
/*---------------------------------------------------------------------*/
DLLExport void _export WINAPI Sc2d (tr2 FAR *m,fpt FAR *res,fpt FAR *x)
  {
  float xo = x->x ;     // Fuer den Fall, das der gleiche Zeiger zweimal
  float yo = x->y ;     // verwendet wird
  res->x = m->A[0][0] * xo + m->A[0][1] * yo + m->B[0] ;
  res->y = m->A[1][0] * xo + m->A[1][1] * yo + m->B[1] ;
  }

/*---------------------------------------------------------------------*/
/*       Berechnung der Matrix, die die Punkte p1 nach 0,0 und         */
/*       Punkt p2 nach l,0 transformatier                              */
/*       (ortogonale Matrix !, l = Dis1. von p1 nach p2                */
/*       Normalize == TRUE: Transformation nach 0,0 und 1,0            */
/*---------------------------------------------------------------------*/
DLLExport void _export WINAPI CalcSc2d (tr2 FAR *m,fpt FAR *p1,fpt FAR *p2,BOOL Normalize)
  {
  float dx = p2->x - p1->x;
  float dy = p2->y - p1->y;
  float l = float (hypot (dx,dy)) ;
  if (l > float (1.0E-3)) {
    // Normalfall: Berechenbar
    m->A[0][0] = m->A[1][1] = dx / l ;
    m->A[0][1] =              dy / l ;
    m->A[1][0] =             -m->A[0][1] ;
    }
  else {
    // Trivial - Fall: Punkt faellt zusammen -> keine Skalierung
    m->A[0][0] = m->A[1][1] = float(1.0) ;
    m->A[0][1] = m->A[1][0] = float(0.0) ;
    }
  // Vorbereitung fuer die Hilfsskalierung
  m->B[0] = m->B[1] = float(0.0);
  fpt h;
  Sc2d (m,&h,p1);
  m->B[0] = -h.x ;
  m->B[1] = -h.y ;
  if (Normalize) {
    if (l > 1.0E-3)
      Stretch2d (m,1.0/l);
    // Invaliden Fall gar nicht erst lange bearbeiten
    }
  }

/*------------------------------------------------------------------*/
/*              Strecken eines Koordinatensystemes                  */
/*     (Punkt der urspr. in den Nullpunkt transformiert wurde,      */
/*      wird weiterhin in den Ursprung transformaiert)              */
/*------------------------------------------------------------------*/
DLLExport void _export WINAPI Stretch2d (tr2 FAR *m,double f)
  {
  int i,j ;
  for (i = 0 ; i < 2 ; i++) {
    for (j = 0 ; j < 2 ; j++)
      m->A[i][j] *= float (f) ;
    m->B[i] *= float (f) ;
    }
  }

/*------------------------------------------------------------------*/
/*      Asymmetrisches Strecken eines Koordinatensystems            */
/*------------------------------------------------------------------*/
DLLExport void _export WINAPI Stretch2dy (tr2 FAR *m,double f)
  {
#ifdef OLD_VERSION
  tr2 tmp;
  // Berechnung der Invertierung
  lmemcpy (&tmp,m,sizeof (tmp));
  InvSc2d (&tmp);       // B entspricht x0
  m->A[1][0] *= f ;
  m->A[1][1] *= f ;
  m->B[0] = m->B[1] = 0.0 ;
  fpt h;
  h.x = -tmp.B[0];
  h.y = -tmp.B[1];
  Sc2d (m,&h,&h);
  m->B[0] = h.x ;
  m->B[1] = h.y ;
#else
  m->A[1][0] *= float (f) ;
  m->A[1][1] *= float (f) ;
  m->B[1] *= float (f) ;
#endif
  }

/*------------------------------------------------------------------*/
/*          Invertieren einer Koordinaten - Transformation          */
/*------------------------------------------------------------------*/
DLLExport void _export WINAPI InvSc2d (tr2 FAR *m)
  {
  // Bildung der Inversen
  double det1 = 1.0 / 
                (m->A[0][0] * m->A[1][1] - m->A[0][1] * m->A[1][0]) ;
  double h = m->A[0][0] ;
  m->A[0][0] = float (double (m->A[1][1]) * det1) ;
  m->A[1][1] = float (h * det1) ;
  m->A[0][1] *= - float (det1) ;
  m->A[1][0] *= - float (det1) ;
  // Transformieren des Offsets
  fpt n;
  n.x = -m->B[0];   m->B[0] = float(0.0) ;
  n.y = -m->B[1];   m->B[1] = float(0.0) ;
  Sc2d (m,&n,&n);
  m->B[0] = n.x ;
  m->B[1] = n.y ;
  }

/*--------------------------------------------------------------*/
/*      Zusammenziehen von 2 Koordinatensystemen                */
/*--------------------------------------------------------------*/
DLLExport void _export WINAPI Combine2d (tr2 FAR *res,tr2 FAR *m1,tr2 FAR *m2)
  {
  tr2 tmp;      // Fuer den Fall, dass einer der Zeiger doppelt verwendet
                // wird
  // Matrizenmultiplikation
  tmp.A[0][0] = m2->A[0][0] * m1->A[0][0] + m2->A[0][1] * m1->A[1][0] ;
  tmp.A[0][1] = m2->A[0][0] * m1->A[0][1] + m2->A[0][1] * m1->A[1][1] ;
  tmp.A[1][0] = m2->A[1][0] * m1->A[0][0] + m2->A[1][1] * m1->A[1][0] ;
  tmp.A[1][1] = m2->A[1][0] * m1->A[0][1] + m2->A[1][1] * m1->A[1][1] ;
  // Berechnung des neuen Offsets
  fpt h;
  h.x = m1->B[0];
  h.y = m1->B[1];
  Sc2d (m2,&h,&h);
  tmp.B[0] = h.x ;
  tmp.B[1] = h.y ;
  // fertig
  lmemcpy (res,&tmp,sizeof(tmp));
  }


/*-------------------------------------------------------------------*/
/*      Transformationsmatrix, um Muster zu skalieren                */
/*      Es wird die Matrix berechnet, die die Punkte p1o, p2o        */
/*      in die Punkte p1n, p2n orthogonal transformiert              */
/*      Normalize == FALSE -> Keine Laengenaenderung, nur Drehung    */
/*      und verschiebung                                             */
/*-------------------------------------------------------------------*/
DLLExport void _export WINAPI MScale2d (tr2 FAR *t,fpt FAR *p1o,fpt FAR *p2o,
        fpt FAR *p1n,fpt FAR *p2n,BOOL Normalize,double f)
  {
  tr2 t1,t2 ;
  CalcSc2d (&t1,p1o,p2o,Normalize);     // Matrix, um die alten Punkte
                                        // in die X - Achse zu transformieren
  if (fabs(f - 1.0) > 1.0E-3)
    Stretch2dy (&t1,f);                 // Eventuelle Deformation
  CalcSc2d (&t2,p1n,p2n,Normalize);     // Matrix, um die neuen Punkte
                                        // in die X - Achse zu transformieren
  InvSc2d (&t2);                        // wird umgedreht (invertiert)
  Combine2d (t,&t1,&t2);                // und zusammengesetzt
  // fertig
  }


//--------------------------------------------------------
//       Durchfuehren einer lineare Transformation
//--------------------------------------------------------
const double pi = 3.1415927464;

DLLExport void _export WINAPI CalcLinTrans (tr2 FAR *sc,fpt FAR *p0,double dx,double dy,double phi)
  {
  // Berechnung der ortogonalen Matrix
  double a = phi * pi / 180.0 ;
  sc->A[0][0] = sc->A[1][1] = float (cos(a));
  sc->A[0][1] = -(sc->A[1][0] = float (sin (a)));
  // Ursprung skalieren, damit die Verschiebung des Ursprungs festgestellt 
  // werden kann
  fpt pn ;
  lmemcpy (&pn,p0,sizeof(fpt));
  sc->B[0] = sc->B[1] = float(0.0) ;
  Sc2d (sc,&pn,p0);
  sc->B[0] = p0->x - pn.x + float (dx) ;
  sc->B[1] = p0->y - pn.y + float (dy) ;
  // fertig
  }

