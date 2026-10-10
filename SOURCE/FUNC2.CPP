// 
// Funktionen, die in der Scriptsprache zur Verfuegung stehen.
//
// $Header:   P:/marille/clinicum/rev/func2.cpv   1.17   27 Apr 1999 01:44:38   Hannes  $
// $Log:   P:/marille/clinicum/rev/func2.cpv  $
// 
//    Rev 1.17   27 Apr 1999 01:44:38   Hannes
// dosqrt
// 
//    Rev 1.16   18 Nov 1998 15:50:20   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.15   19 Nov 1997 18:47:38   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.14   07 Aug 1997 11:53:16   Hannes
// 
//    Rev 1.13   26 Nov 1996 08:14:12   HANNES
// Automatischer Update
// 
//    Rev 1.12   08 Nov 1996 13:33:16   HANNES
// QLong Funktionen
// 
//    Rev 1.11   25 Jul 1996 19:50:56   GERHOLD
// int far *  =>  DBINT FAR *
// 
//    Rev 1.10   10 Jun 1996 10:08:06   GERHOLD
// pragma pack
// 
//    Rev 1.9   02 Feb 1996 10:36:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   27 Aug 1995 13:04:24   HANNES
// MulShort,DivShort,MulLong,DivLong
// 
//    Rev 1.7   31 Jul 1995 11:39:46   HANNES
// Fehler in DiffTime
// 
//    Rev 1.6   20 Mar 1995 11:56:08   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.5   24 Feb 1995 11:17:08   HANNES
//  
// 
//    Rev 1.4   20 Sep 1994 11:36:56   HANNES
// Fehlerabfrage vom Zyklischen Spline
// 
//    Rev 1.3   07 Sep 1994 10:51:24   HANNES
// Zeitfunktionen
// 
//    Rev 1.2   05 Aug 1994 20:22:08   HANNES
// Vorzeichenfehlerkorrektur in DiffTime
// 
//    Rev 1.1   05 Aug 1994 20:17:56   HANNES
// DiffTime
// 
//    Rev 1.0   24 Jun 1994 17:05:04   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.29   12 Jan 1994 15:38:24   HANNES
// 
//    Rev 1.28   12 Jan 1994 11:15:28   HANNES
// Unnoetige Includes entfernt
// 
//    Rev 1.27   29 Nov 1993 08:54:18   HANNES
// uAddYearsDec
// 
//    Rev 1.26   16 Nov 1993 04:23:00   HANNES
// Konstruktionsfunktionen
// 
//    Rev 1.25   04 Oct 1993 09:41:58   HANNES
// Korrektur der Funktion uAddMonth
// 
//    Rev 1.24   27 Sep 1993 18:28:40   HANNES
// Neue Datumsfunktionen
// 
//    Rev 1.23   22 Sep 1993 09:18:52   HANNES
// Version nach St. Poelten
// 
//    Rev 1.22   05 Sep 1993 22:13:42   HANNES
// Aufraemarbeiten
// 
//    Rev 1.21   24 Aug 1993 10:34:46   HANNES
// uAddDate
// 
//    Rev 1.20   18 Jun 1993 15:13:18   MARTIN
// Prototypen der Berechnungsfunktionen
// 
//    Rev 1.19   02 Jun 1993 22:20:50   MARTIN
// TurnPt
// 
//    Rev 1.18   25 May 1993 15:33:18   MARTIN
// uConnectCont korrigiert
// 
//    Rev 1.17   24 May 1993 14:31:06   MARTIN
// uConnectCont
// 
//    Rev 1.16   21 May 1993 17:17:00   MARTIN
// uStretchCont
// 
//    Rev 1.15   18 May 1993 17:41:58   MARTIN
// uExpVal, uPowVal
// 
//    Rev 1.14   05 May 1993 11:05:44   MARTIN
// uEstimateTang...
// 
//    Rev 1.13   22 Apr 1993 21:03:00   MARTIN
// Anpassung fuer geschnittene Konturen
// 
//    Rev 1.12   18 Apr 1993 21:41:56   HANNES
// ??
// 
//    Rev 1.11   02 Apr 1993 17:34:04   HANNES
// Strukturbereinigung, Beschleunigun
// 
//    Rev 1.10   17 Mar 1993 17:30:40   HANNES
// uDecIndArr (?.)
// 
//    Rev 1.9   16 Feb 1993 13:13:04   HANNES
// Erweiterung der Long Arithmetik
// 
//    Rev 1.8   05 Feb 1993 19:31:32   MARTIN
// uSubVect
// 
//    Rev 1.7   01 Feb 1993 12:05:36   HANNES
// Einbau der Klasse VTO
// 
//    Rev 1.6   21 Jan 1993 22:36:16   HANNES
// Korrekturen...
// 
//    Rev 1.5   21 Jan 1993 20:31:20   HANNES
// Korrekturen an den neuen Funktionen
// 
//    Rev 1.4   21 Jan 1993 20:26:24   HANNES
// uAddVect, uGenVect neu
// 
//    Rev 1.3   06 Jan 1993 16:52:02   HANNES
// Abfragen der Fehler von smoothcont
// 
//    Rev 1.2   18 Dec 1992 12:44:26   HANNES
// Neu Funktion (uCopyCont)
// 
//    Rev 1.1   03 Dec 1992 14:49:24   HANNES
// Korrektur von Contcalc bei fehlender Kontur
// 
//    Rev 1.0   02 Dec 1992 15:28:56   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#include "dds.h"
#include "sc2d.hpp"
#include "globmem.h"
#include "ddsmsg.h"
#include "cont.hpp"
#include "calcval.hpp"
#include "cutcont.hpp"
#include "reconst.hpp"

/*------------------------------------------------------------
        Einige Numersiche Funktionen
------------------------------------------------------------*/
/*------< Abstand zwischen 2 Punkten >-------*/
void * ptdist (pv FAR *args)
  {
  // p[1] ... Punkt 1
  // p[2] ... Punkt 2
  // p[3] ... Vergroesserungsfaktor (muss nicht vorhanden sein)

  pp p[4];
  for (int i = 0 ; i < 4 ; i++) p[i] = LPFPT (args[i]);
  if ((p[1] != NULL) && (p[2] != NULL) && 
        (p[1]->x < 1.0E9) && (p[2]->x < 1.0E9)) {
    result.floatres = float (hypot (p[1]->x - p[2]->x,p[1]->y - p[2]->y)) ;
    if (p[3] != NULL) {
      result.floatres /= * ((float FAR *) (args[3])) ;
      }
    return &result.floatres ;
    }
  else
    return NULL ;
  }

/*------< Standard - Glaettung >-------*/
void *sm_cont (pv FAR *args)
  {
  // args [1] ... Alte Kontur
  // args [2] ... Anzahl der Punkte
  // args [3] ... Glaettungs - Haerte
  if (args[1] != NULL) {
    int PtCount;
    fpt FAR *cnt = get_cont((fpt FAR *) args[1], &PtCount);
    GLOBALHANDLE hGtmp = smooth_cont (cnt, PtCount,
                        *(DBINT FAR *) args[2], *(float FAR *) args[3]) ;
    if (hGtmp) {
      result.cntres.ContSize = *(WORD FAR *) args[2] * sizeof (fpt) ;
      result.cntres.Contmem = hGtmp ;
      return &result.cntres;
      }
    else
      return NULL ;
    }
  else return NULL ;
  }

/*------< Standard - Glaettung >-------*/
extern GLOBALHANDLE smooth_cyccont (fpt FAR *old,int Anzo,int Anzn,double hardness);
void *sm_cyccont (pv FAR *args)
  {
  // args [1] ... Alte Kontur
  // args [2] ... Anzahl der Punkte
  // args [3] ... Glaettungs - Haerte
  if (args[1] != NULL) {
    int PtCount;
    fpt FAR *cnt = get_cont((fpt FAR *) args[1], &PtCount);
    GLOBALHANDLE hGtmp = smooth_cyccont (cnt, PtCount,
                        *(DBINT FAR *) args[2], *(float FAR *) args[3]) ;
    if (hGtmp) {
      result.cntres.ContSize = *(WORD FAR *) args[2] * sizeof (fpt) ;
      result.cntres.Contmem = hGtmp ;
      return &result.cntres;
      }
    else
      return NULL ;
    }
  else return NULL ;
  }

void *smext_cont (pv FAR *args)
  {
  // args[1] ... Alte Kontur
  // args[2] ... Anzahl der gewuenschten Punkte
  // args[3] ... Basishaerte
  // args[4] ... Spitzenhaerte
  // args[5] ... Einzugslaenge
  // args[6] ... Stuetzpunkt 1
  // args[7] ... Stuetzpunkt 2 usw.
  if (args[1] != NULL) {
    LPFPT tmp[5];
    int AnzStp = 0 ;
    for (int i = 0 ; ; i++) {
      if (args[i+6] != NULL) {
        tmp[i] = LPFPT (args[i+6]) ;
        AnzStp ++ ;
        }
      else break ;
      }
    int PtCount;
    fpt FAR *cnt = get_cont((fpt FAR *) args[1], &PtCount);
    GLOBALHANDLE hGtmp = smextcont (cnt, PtCount,
                        *(DBINT FAR *) args[2], *(float FAR *) args[3],
                        *(float FAR *) args[4],*(float FAR *) args[5],
                        AnzStp,tmp);
    result.cntres.ContSize = *(WORD FAR *) args[2] * sizeof (fpt) ;
    result.cntres.Contmem = hGtmp ;
    return &result.cntres;
    }
  else return NULL ;
  }

void *cm_cont (pv FAR *args)
  {
  // args [1] ... Anzahl der Punkte
  // args [2] ... Glaettungs - Haerte
  // args [3] ... Anzahl der zu glaettenden Konturen
  // args [4] ... Alte Kontur 1
  // args [5] ... Alte Kontur 2 ...
  LPFPT conts[7];
  BOOL do_combine = TRUE ;
  for (int i = 0 ; i < *((DBINT FAR *) args[3]) ; i++) {
    conts[i] = ((LPFPT) args[4+i]);
    do_combine = ((do_combine) && (conts[i] != NULL)) ;
    }
  if (do_combine) {
    GLOBALHANDLE hGtmp = combine_cont (conts,*(DBINT FAR *) args[3],
                                         *(DBINT FAR *) args[1],
                                         *(float FAR *) args[2]) ;
    result.cntres.ContSize = *(WORD FAR *) args[1] * sizeof (fpt) ;
    result.cntres.Contmem = hGtmp ;
    return &result.cntres;
    }
  else return NULL ;
  }

void *conn_cont (pv FAR *args)
  {
  // args [1] ... Anzahl der zu glaettenden Konturen
  // args [2] ... Alte Kontur 1
  // args [3] ... Alte Kontur 2 ...
  LPFPT conts[7];
  BOOL do_connect = TRUE ;
  for (int i = 0 ; i < *((DBINT FAR *) args[1]) ; i++) {
    conts[i] = ((LPFPT) args[2+i]);
    do_connect = ((do_connect) && (conts[i] != NULL)) ;
    }
  if (do_connect) {
    int PtCount;
    GLOBALHANDLE hGtmp = connect_cont (conts,*(DBINT FAR *) args[1],&PtCount);
    result.cntres.ContSize = PtCount * sizeof (fpt);
    result.cntres.Contmem = hGtmp ;
    return &result.cntres;
    }
  else return NULL ;
  }

/*------< Berechnung eines neuen Punktes >------*/
void *crpt (pv FAR *args)
  {
  // args[1] ... Punkt 1
  // args[2] ... Punkt 2
  // args[3] ... rel. x
  // args[4] ... rel. y
  if ((args[1] != NULL) && (args[2] != NULL) && 
        (args[3] != NULL) && (args[4] != NULL)) {
    tr2 scale ;
    CalcSc2d (&scale,LPFPT (args[1]),LPFPT (args[2]),TRUE);
    InvSc2d (&scale);
    result.fptres.x = * (float FAR *) args[3] ;
    result.fptres.y = * (float FAR *) args[4] ;
    Sc2d (&scale,&result.fptres,&result.fptres);
    return &result.fptres;
    }
  else return NULL ;
  }

/*--------< Schnittpunkt von 2 Linien >--------*/
void *LinInt (pv FAR *args)
  {
  // args[1] ... Punkt 1, Linie 1
  // args[2] ... Punkt 2, Linie 1
  // args[3] ... Punkt 1, Linie 2
  // args[4] ... Punkt 2, Linie 2
  if ((args[1] != NULL) && (args[2] != NULL) && 
        (args[3] != NULL) && (args[4] != NULL)) {
    double a_x = ((fpt FAR *) (args[2]))->x - ((fpt FAR *) (args[1]))->x; 
    double b_x = ((fpt FAR *) (args[4]))->x - ((fpt FAR *) (args[3]))->x; 
    double a_y = ((fpt FAR *) (args[2]))->y - ((fpt FAR *) (args[1]))->y; 
    double b_y = ((fpt FAR *) (args[4]))->y - ((fpt FAR *) (args[3]))->y; 

    if ( a_x == 0.0 && a_y == 0.0  ||  b_x == 0.0 && b_y == 0.0 )
        return NULL;

    double d ;
    if (( d = a_x * b_y - a_y * b_x ) == 0 ) return NULL;
    d = ( a_y * 
                ( ((fpt FAR *)(args[3]))->x - ((fpt FAR *)(args[1]))->x ) - 
            a_x * 
                   ( ((fpt FAR *)(args[3]))->y - ((fpt FAR *)(args[1]))->y )) / d;

    result.fptres.x = float (double (((fpt FAR *)(args[3]))->x) + d * b_x);
    result.fptres.y = float (double (((fpt FAR *)(args[3]))->y) + d * b_y);
    return &result.fptres ;
    }
  else return NULL ;
  }

/*--------< Projektionspunkt auf linie >--------*/
void *PtPro (pv FAR *args)
  {
  // args[1] ... Punkt 1, Linie 
  // args[2] ... Punkt 2, Linie 
  // args[3] ... Ausgangspunkt
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    double dxl = ((fpt FAR *) (args[2]))->x - ((fpt FAR *) (args[1]))->x; 
    double dxg = ((fpt FAR *) (args[3]))->x - ((fpt FAR *) (args[1]))->x; 
    double dyl = ((fpt FAR *) (args[2]))->y - ((fpt FAR *) (args[1]))->y; 
    double dyg = ((fpt FAR *) (args[3]))->y - ((fpt FAR *) (args[1]))->y; 
    double l = hypot (dxl,dyl);
    if (l > 0.0001) {
      double h = fabs (dxg * dyl - dyg * dxl) / l ;
      double g = hypot (dxg,dyg);
      double x = sqrt (g*g - h*h) / l ;
      if (dxg * dxl + dyg * dyl < 0.0) x = -x ;
      result.fptres.x = float (double (((fpt FAR *) (args[1]))->x) + dxl * x);
      result.fptres.y = float (double (((fpt FAR *) (args[1]))->y) + dyl * x);
      return &result.fptres ;
      }
    else return NULL ;
    }
  else return NULL ;
  }

// Berechnen eines Punktes, der Rechtwinklig auf die angegebene Linie steht
void *PerpPt (pv FAR *args)
  {
  // args[1] ... Punkt1
  // args[2] ... Punkt2 
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.fptres.x = ((fpt FAR *) (args[1]))->x -
       (((fpt FAR *) (args[2]))->y - ((fpt FAR *) (args[1]))->y) ;
    result.fptres.y = ((fpt FAR *) (args[1]))->y +
       (((fpt FAR *) (args[2]))->x - ((fpt FAR *) (args[1]))->x) ;
    return &result.fptres ;
    }
  else return NULL ;
  }

// Parallelverschieben eines Punktes
void *ParPt (pv FAR *args)
  {
  // args[1] ... Ausgangspunkt
  // args[2] ... Punkt1
  // args[3] ... Punkt2 
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    result.fptres.x = ((fpt FAR *) (args[1]))->x +
       (((fpt FAR *) (args[3]))->x - ((fpt FAR *) (args[2]))->x) ;
    result.fptres.y = ((fpt FAR *) (args[1]))->y +
       (((fpt FAR *) (args[3]))->y - ((fpt FAR *) (args[2]))->y) ;
    return &result.fptres ;
    }
  else return NULL ;
  }

// Extremwert auf eine Kontur
void *CntMax (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... 1. Punkt der Gerade
  // args[3] ... 1. Punkt der Gerade
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    contmax (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],(LPFPT) args[3]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL;
    }
  else return NULL ;
  }

// Schnittpunkt mit einer Kontur
void *CntCro (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... 1. Punkt der Gerade
  // args[3] ... 1. Punkt der Gerade
  // args[4] ... wievielter Schnittpunkt es sein soll
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    contcro (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],(LPFPT) args[3],*(DBINT FAR *)args[4]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }

// Sehne an eine Kontur
void *CntMaxAng (pv FAR *args) 
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... Referenzpunkt
  // args[3] ... Referenzstrecke
  // args[4] ... Im Uhrzeigersinn, gegen den Uhrzeigersinn
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    contmaxang (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],(LPFPT) args[3],*(DBINT FAR *)args[4]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }

// Naehester Punkt auf der Kontur
void *CntNea (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... zu untersuchender Punkt
  if ((args[1] != NULL) && (args[2] != NULL)) {
    contnea (&result.fptres,(LPFPT) args[1],(LPFPT) args[2]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }

// Tangente an Kontur schaetzen
void *EstTang (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... zu untersuchender Punkt
  // args[3] ... Vektor fuer Richtung des Tangentenvektors
  if ((args[1] != NULL) && (args[2] != NULL)) {
    esttang (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],(LPFPT) args[3]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }

// Wendepunkt in Kontur berechnen
void *TurnPt (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... von welchem Punkt ausgehend
  // args[3] ... in welche Richtung geht Kontur zuerst
  if ((args[1] != NULL) && (args[2] != NULL)) {
    turnpt (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],*(DBINT FAR *)args[3]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }

// Addieren eines fixen Vektors zu einem Punkt
void *AddFixVect (pv FAR *args)
  {
  // args[1] ... Ausgangspunkt
  // args[2] ... x Koordinate des Vektors
  // args[3] ... y Koordinate des Vektors
  if (args[1] != NULL) {
    result.fptres.x = ((fpt FAR *) (args[1]))->x + *((float FAR *) (args[2]));
    result.fptres.y = ((fpt FAR *) (args[1]))->y + *((float FAR *) (args[3]));
    return &result.fptres ;
    }
  else return NULL;
  }

// Ermitteln des Punktes, der weiter von der Linie entfernt ist
void *MaxPt (pv FAR *args)
  {
  // args[1] ... Punkt 1, Linie
  // args[2] ... Punkt 2, Linie
  // args[3] ... Punkt a
  // args[4] ... Punkt b
  if ((args[1] != NULL) && (args[2] != NULL) && 
        (args[3] != NULL) && (args[4] != NULL)) {
    double dx = ((fpt FAR *) (args[2]))->x - ((fpt FAR *) (args[1]))->x; 
    double dx1 = ((fpt FAR *) (args[3]))->x - ((fpt FAR *) (args[1]))->x; 
    double dx2 = ((fpt FAR *) (args[4]))->x - ((fpt FAR *) (args[1]))->x; 
    double dy = ((fpt FAR *) (args[2]))->y - ((fpt FAR *) (args[1]))->y; 
    double dy1 = ((fpt FAR *) (args[3]))->y - ((fpt FAR *) (args[1]))->y; 
    double dy2 = ((fpt FAR *) (args[4]))->y - ((fpt FAR *) (args[1]))->y; 

    if (dx * dy1 - dy * dx1 > dx * dy2 - dy * dx2)
      lmemcpy (&result.fptres,args[4],sizeof (fpt));
    else
      lmemcpy (&result.fptres,args[3],sizeof (fpt));
    return &result.fptres ;
    }
  else return NULL ;
  }

// Berechnen der Differenz in Jahren von 2 Datums
void *DiffYears (pv FAR *args)
  {
  // args[1] .. groesseres Datum
  // args[2] .. kleineres Datum
  if ((args[1] != NULL) && (args[2] != NULL)) {
    // Es ist zwar keine exakte Berechnung, aber was solls
    int dy = ((packdate FAR *) args[1])->year - 
                ((packdate FAR *) args[2])->year ;
    int dm = ((packdate FAR *) args[1])->month - 
                ((packdate FAR *) args[2])->month ;
    int dd = ((packdate FAR *) args[1])->day - 
                ((packdate FAR *) args[2])->day ;
    result.floatres = (float) (double (dy) + double (dm) / 12.0 + double (dd) / 365.0) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void *MulVal (pv FAR *args)
  {
  // args[1] .. Wert 1
  // args[2] .. Wert 2 (Wert 1 * Wert 2)
  if ((args[1] != NULL) && (args[2] != NULL) &&
      (* ((float FAR *) args[1]) < 1.0E9) &&
      (* ((float FAR *) args[2]) < 1.0E9)) {
    result.floatres = * ((float FAR *) args[1]) * 
                                * ((float FAR *) args[2]) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void *ExpVal (pv FAR *args)
  {
  // args[1] .. Wert 1 (e hoch Wert 1)
  if ((args[1] != NULL) &&
      (* ((float FAR *) args[1]) < 1.0E9)) {
    result.floatres = (float)exp (* ((float FAR *) args[1])) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void *PowVal (pv FAR *args)
  {
  // args[1] .. Wert 1
  // args[2] .. Wert 2 (Wert 1 hoch Wert 2)
  if ((args[1] != NULL) && (args[2] != NULL) &&
      (* ((float FAR *) args[1]) < 1.0E9) &&
      (* ((float FAR *) args[2]) < 1.0E9)) {
    result.floatres = (float)pow (* ((float FAR *) args[1]) ,
                                  * ((float FAR *) args[2])) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void *AddVal (pv FAR *args)
  {
  // args[1] .. Wert 1
  // args[2] .. Wert 2 (Wert 1 + Wert 2)
  if ((args[1] != NULL) && (args[2] != NULL) &&
       (* ((float FAR *) args[1]) < 1.0E9) &&
       (* ((float FAR *) args[2]) < 1.0E9)) {
    result.floatres = * ((float FAR *) args[1]) +
                                * ((float FAR *) args[2]) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void *DivVal (pv FAR *args)
  {
  // args[1] .. Wert 1
  // args[2] .. Wert 2 (Wert 1 / Wert 2)
  if ((args[1] != NULL) && (args[2] != NULL) &&
       (* ((float FAR *) args[1]) < 1.0E9) &&
       (* ((float FAR *) args[2]) < 1.0E9)) {
    if (fabs(*((float FAR *) args[2])) > 0.00001) {
      result.floatres = * ((float FAR *) args[1]) /
                                  * ((float FAR *) args[2]) ;
      return &result.floatres ;
      }
    else
      return NULL ;
    }
  else return NULL ;
  }

void *SubVal (pv FAR *args)
  {
  // args[1] .. Wert 1
  // args[2] .. Wert 2 (Wert 1 + Wert 2)
  if ((args[1] != NULL) && (args[2] != NULL) &&
       (* ((float FAR *) args[1]) < 1.0E9) &&
       (* ((float FAR *) args[2]) < 1.0E9)) {
    result.floatres = * ((float FAR *) args[1]) -
                                * ((float FAR *) args[2]) ;
    return &result.floatres ;
    }
  else return NULL ;
  }

void * ptndist (pp FAR *p)
  {
  // p[1] ... Punkt 1
  // p[2] ... Punkt 2
  // p[3] ... Ausgangspunkt
  // p[4] ... Vergroesserungsfaktor (muss nicht vorhanden sein)

  if ((p[1] != NULL) && (p[2] != NULL) && (p[3] != NULL) &&
      (p[1]->x <= 1.0E9) && (p[2]->x <= 1.0E9) && (p[3]->x <= 1.0E9)) {
    double dxl = p[2]->x - p[1]->x ;
    double dyl = p[2]->y - p[1]->y ;
    double l = hypot (dxl,dyl) ;
    if (l > 0.00001) {
      double dxp = p[3]->x - p[1]->x ;
      double dyp = p[3]->y - p[1]->y ;
      result.floatres = float ((dxp * dyl - dyp * dxl) / l) ;
      if (p[4] != NULL)
        result.floatres /= * (float FAR *) (p[4]) ;
      return &result.floatres ;
      }
    else return NULL ;
    }
  else
    return NULL ;
  }

void * ptpdist (pp FAR *p)
  {
  // p[1] ... Punkt 1
  // p[2] ... Punkt 2
  // p[3] ... Ausgangspunkt
  // p[4] ... Vergroesserungsfaktor (muss nicht vorhanden sein)

  if ((p[1] != NULL) && (p[2] != NULL) && (p[3] != NULL) &&
      (p[1]->x <= 1.0E9) && (p[2]->x <= 1.0E9) && (p[3]->x <= 1.0E9)) {
    double dxl = p[2]->x - p[1]->x ;
    double dyl = p[2]->y - p[1]->y ;
    double l = hypot (dxl,dyl) ;
    if (l > 0.00001) {
      double dxp = p[3]->x - p[1]->x ;
      double dyp = p[3]->y - p[1]->y ;
      double h = (dxp * dyl - dyp * dxl) / l ;
      double g = hypot (dxp,dyp);
      result.floatres = float (sqrt (g * g - h * h));
      if (p[4] != NULL)
        result.floatres /= * (float FAR *) (p[4]) ;
      return &result.floatres ;
      }
    else return NULL ;
    }
  else
    return NULL ;
  }

const double pi = 3.1415927464;
const double half_pi = 1.5707963732;
double arcus (double y, double x)
  {
  double res;
  unsigned flag;

  if (flag = y < 0.0) y = -y;
   
  if (y < fabs (x))
    res = 0.0;
  else
    {
    res = x; x = y; y = -res;   /* rotate half_pi */
    res = half_pi;
    }
  if (x < 0.0) res += pi;

  if (fabs(x) > 0.001)
    res += atan (y / x);
  else
    res = 1.0E10;
  if (flag) return (-res);
  return (res);
  }

void * DiffAng (pp FAR *p)
  {
  // p[1] ... Punkt 1, Linie 1
  // p[2] ... Punkt 2, Linie 1
  // p[3] ... Punkt 1, Linie 2
  // p[4] ... Punkt 2, Linie 2

  if ((p[1] != NULL) && (p[2] != NULL) && (p[3] != NULL) && (p[4] != NULL) &&
       (p[1]->x <= 1.0E9) && (p[2]->x <= 1.0E9) && 
       (p[3]->x <= 1.0E9) && (p[4]->x <= 1.0E9)) {
    double dx1 = p[2]->x - p[1]->x ;
    double dy1 = p[2]->y - p[1]->y ;
    double dx2 = p[4]->x - p[3]->x ;
    double dy2 = p[4]->y - p[3]->y ;
    double a2 = arcus (dy2,dx2);
    double a1 = arcus (dy1,dx1);
    if ((a1 < 1.0E9) && (a2 < 1.0E9)) {
      result.floatres = float ((a2 - a1) * 180.0 / pi) ;
      if (result.floatres < float (- 180.0)) 
        result.floatres += float (360.0) ;
      if (result.floatres > float (180.0)) 
        result.floatres -= float (360.0) ;
      
      return &result.floatres ;
      }
    else return NULL ;
    }
  else
    return NULL ;
  }

void * ValRange (pv FAR *args)
  {
  // args[1] ... Zu untersuchender Wert
  // args[2] - [n] ... Grenzen
  if (args[1] != NULL) {
    for (int i = 0 ; ; i++) {
      if (args[i+2] == NULL) break ;
      if (* ((float FAR *) args[1]) < * ((float FAR *) args[i+2])) break ;
      }
    result.inres = i ;
    return &result.inres ;
    }
  else return NULL ;
  }


void * GetDevInd (pv FAR *args)
  {
  // args[1] ... Zu untersuchender Wert
  // args[2] ... Norm
  // args[3] ... Standardabweichung
  // args[4] ... Anzahl der Indizess (nur 3, 5, und 7 erlaubt!)
  BOOL docalc = TRUE ;
  for (int i = 1 ; i <= 3 ; i++)
    docalc = ((docalc) && (args[i] != NULL)) ;
  if (docalc) {
    float ind = (*((float FAR *) args[1]) - *((float FAR *) args[2])) /
                        *((float FAR *) args[3]);
    int AnzVals = int (*((DBINT FAR *) args[4]));
    int ig = (ind <= 0.0) ? int (-ind) : int (ind);
    int si = (ind <= 0.0) ? -1 : 1 ;
    switch (AnzVals) {
#define CLIP(A) { if (ig > A) ig = A ; }
      case 3 :
        CLIP(1);
        result.inres = 1 + ig * si;
        break ;
      case 5 :
        CLIP(2);
        result.inres = 2 + ig * si;
        break ;
      case 7 :
        CLIP(3);
        result.inres = 3 + ig * si;
        break ;
#undef CLIP
      default :
        return NULL;
      }
    return &result.inres;
    }
  else return NULL;
  }

void * GetTrcDevInd (pv FAR *args)
  {
  // args[1] ... Zu untersuchender Wert
  // args[2] ... Norm
  // args[3] ... Standardabweichung
  BOOL docalc = TRUE ;
  for (int i = 1 ; i <= 3 ; i++)
    docalc = ((docalc) && (args[i] != NULL)) ;
  if (docalc) {
    float ind = (*((float FAR *) args[1]) - *((float FAR *) args[2])) /
                        *((float FAR *) args[3]);
    int ig = (ind <= 0.0) ? int (-ind) : int (ind);
    if (ig > 2) ig = 2 ;
    result.inres = ig;
    return &result.inres;
    }
  else return NULL;
  }


void *GetSymmetrieLine (pv FAR *args)
  {
  // args[1] ... p1     (p1 - p2) Linie 1
  // args[2] ... p2
  // args[3] ... p3     (p3 - p2) Linie 2
#define PT1     ((fpt FAR *) (args[1]))
#define PT2     ((fpt FAR *) (args[2]))
#define PT3     ((fpt FAR *) (args[3]))

  if ((PT1 != NULL) && (PT2 != NULL) && (PT3 != NULL) &&
      (PT1->x < 1.0E9) && (PT2->x < 1.0E9) && (PT3->x < 1.0E9)) {
    double dx1 = PT1->x - PT2->x ;
    double dy1 = PT1->y - PT2->y ;
    double dx2 = PT3->x - PT2->x ;
    double dy2 = PT3->y - PT2->y ;
    double l1 = hypot (dx1,dy1);
    double l2 = hypot (dx2,dy2);
    if ((l1 > 1.0E-3) && (l2 > 1.0E-3)) {
      dx1 *= l2 / l1 ;
      dy1 *= l2 / l1 ;
      result.fptres.x = PT2->x + (float) dx1 + (float) dx2 ;
      result.fptres.y = PT2->y + (float) dy1 + (float) dy2 ;
      return &result.fptres ;
      }
    else return NULL ;
    }
  else return NULL ;

#undef PT1
#undef PT2
#undef PT3
  }

void *Get33Arr (pv FAR *args)
  {
  // args[1] ... 1. Index (Hauptindex)
  // args[2] ... 2. Index (Nebenindex)
  // args[3] - args[12] Array - Elemente
#define I1      ((DBINT FAR *) (args[1]))
#define I2      ((DBINT FAR *) (args[2]))
#define Arr(I)  (*((float FAR *) (args[3+I])))

  if ((I1 != NULL) && (I2 != NULL)) {
    if ((*I1 >= 0) && (*I1 <= 2) && 
          (*I2 >= 0) && (*I2 <= 2)) {
      int ind = *I1 * 3 + *I2 ;
      result.floatres = Arr(ind);
      return &result.floatres;
      }
    else return NULL ;
    }
  else return NULL ;
#undef Arr
#undef I1
#undef I2
  }

void *GetIndDec (pv FAR *args)
  {
  // args[1] ... 1. Index (Hauptindex)
  // args[2] - args[..] Array - Elemente
#define I1      ((DBINT FAR *) (args[1]))
#define Arr(I)  ((float FAR *) (args[2+I]))

  int ind;
  if ((I1 != NULL) && (*I1 >= 0) && (*I1 < MAXARRDIM) && 
          (Arr(*I1) != NULL))
    ind = *I1;
  else
    ind = 0;
  result.floatres = *Arr(ind);
  return &result.floatres;
#undef Arr
#undef I1
  }

void *doContDivide (pv FAR *args)
  {
  // args[1] ... Kontur
  // args[2] ... Punkt an dem Geteilt werden soll
  // args[3] ... Vektor, der zur Kontrolle der resultierenden Richtung
  // verwendet wird
#define PT  ((fpt FAR *) (args[2]))
#define V   ((fpt FAR *) (args[3]))

  int oldSize;
  fpt FAR *CNT = get_cont((fpt FAR *)args[1], &oldSize);
  if ((CNT != NULL) && (PT != NULL) && (V != NULL) && (PT->x < 1.0E9)) {
    double oabst = 1.0E10 ;
    int res = 0 ;

    for (int i = 0 ; i < oldSize ; i++) {
      double abst = hypot (PT->x - CNT[i].x,PT->y - CNT[i].y) ;
      if (abst < oabst) {
        res = i;
        oabst = abst ;
        }
      }
    fpt FAR *fbase;
    int      fcount;
    double inp,inm;
    if ((res > 0) && (res < oldSize - 1)) {
      // Es wurde der erste Punkt der Kontur gefunden
      double dxp = CNT[res+1].x - CNT[res].x ;
      double dyp = CNT[res+1].y - CNT[res].y ;
      double lp = sqrt (dxp * dxp + dyp * dyp);

      double dxm = CNT[res-1].x - CNT[res].x ;
      double dym = CNT[res-1].y - CNT[res].y ;
      double lm = sqrt (dxm * dxm + dym * dym);

//      inp = V->x * (CNT[res+1].x - CNT[res].x) +
//                V->y * (CNT[res+1].y - CNT[res].y) ;
//      inm = V->x * (CNT[res-1].x - CNT[res].x) +
//                V->y * (CNT[res-1].y - CNT[res].y) ;
//      if (inp > inm) {
      if (lm * (V->x * dxp + V->y * dyp) > lp * (V->x * dxm + V->y * dym)) {
        // Der hintere Teil wird genommen
        fbase = &(CNT[res]);
        fcount = oldSize - res ;
        }
      else {
        // Der vordere Teil wird genommen
        fbase = CNT ;
        fcount = res + 1 ;
        }
      }
    else if (res == 0) {
      inp = V->x * (CNT[res+1].x - CNT[res].x) +
                       V->y * (CNT[res+1].y - CNT[res].y) ;
      if (inp > 0.0) {
        fcount = oldSize ;
        fbase = CNT ;
        }
      else fcount = 0;
      }
    else if (res == oldSize - 1) {
      // Es wurde der letzte Punkt der Kontur gefunden
      inm = V->x * (CNT[res-1].x - CNT[res].x) +
                V->y * (CNT[res-1].y - CNT[res].y) ;
      if (inm > 0.0) {
        fcount = oldSize ;
        fbase = CNT ;
        }
      else fcount = 0;
      }
    if (fcount > 0) {
      GLOBALHANDLE hGCont = GlobalAlloc (GHND,sizeof(fpt) * fcount);
      LPSTR f = LPSTR(GlobalLock (hGCont));
      lmemcpy (f,fbase,sizeof(fpt) * fcount);
      GlobalUnlock (hGCont);
      result.cntres.ContSize = fcount * sizeof (fpt);
      result.cntres.Contmem = hGCont ;
      return &result.cntres;
      }
    else return NULL ;
    }
  else return NULL ;

#undef PT
#undef V
  }

void *GenAgeNorm (pv FAR *args)
  {
  // args[1] ... float FAR *Norm9a
  // args[2] ... BOOL FAR *Sex
  // arsg[3] ... float FAR *dAge / a    (geschlechstspezifisch geklippt)
  // args[4] ... dNorm / male
  // args[5] ... dNorm / female

#define NORM9A   (*((float FAR *) (args[1])))
#define DNORM(I) (*((float FAR *) (args[4+I])))
#define LPSEX    ((BOOL FAR *) (args[2]))
#define LPAGE    ((float FAR *) (args[3]))

  if (LPAGE != NULL) {
    int ind ;
    if (LPSEX != NULL) {
      if (*LPSEX) ind = 1 ;
      else        ind = 0 ;
      }
    else ind = 0 ;
    result.floatres = NORM9A + DNORM(ind) * (*LPAGE);
    return &result.floatres;
    }
  else return NULL ;

#undef NORM9A   
#undef DNORM
#undef LPSEX    
#undef LPAGE    
  }

// Berechnung der Schnittpunkte eines Kreises mit einer Linie
void *ArcInt (pv FAR *args)
  {
  // args[1] ... Mittelpunkt des Kreises
  // args[2] ... Radius des Kreises
  // args[3] ... Linie Punkt1
  // args[4] ... Linie Punkt2
  // args[5] ... Punkt der dem (zweideutigen) Resultat naeher sein soll
#define P3 ((fpt FAR *) (args[3]))
#define P2 ((fpt FAR *) (args[4]))
#define P1 ((fpt FAR *) (args[1]))
#define PV ((fpt FAR *) (args[5]))
#define R  (*((float FAR *) (args[2])))

  if ((args[1] == NULL) || (args[2] == NULL) ||
       (args[3] == NULL) || (args[4] == NULL) || (args[5] == NULL) ||
       (P1->x >= 1.0E9) || (P2->x >= 1.0E9) || (P3->x >= 1.0E9)) return NULL ;

  double dx = P2->x - P3->x ;
  double dy = P2->y - P3->y ;
  double q = - (R * R) + P1->x * P1->x + P1->y * P1->y +
                P3->x * P3->x + P3->y * P3->y 
              - 2.0 * (P1->x * P3->x + P1->y * P3->y) ;
  double p = 2.0 * (P3->x * dx + P3->y * dy -
                    (P1->x * dx + P1->y * dy)) ;
  double a = dx * dx + dy * dy ;
  if (a > 0.001) {
    p /= a ;
    q /= a ;
    double x = p * p / 4.0 ;
    if (x > q) {
      // Loesen der Quadratischen Gleichung
      double t1 = - p / 2.0 + sqrt (x - q);
      double t2 = - p / 2.0 - sqrt (x - q);
      fpt r1,r2;
      r1.x = P3->x + float (t1 * dx) ;
      r1.y = P3->y + float (t1 * dy) ;
      r2.x = P3->x + float (t2 * dx) ;
      r2.y = P3->y + float (t2 * dy) ;
      double l1 = hypot (r1.x - PV->x,r1.y - PV->y);
      double l2 = hypot (r2.x - PV->x,r2.y - PV->y);
      if (l1 < l2)
        lmemcpy (&result.fptres,&r1,sizeof(fpt));
      else
        lmemcpy (&result.fptres,&r2,sizeof(fpt));
      return &result.fptres;
      }
    else 
      // Linie schneidet den Kreis nicht
      return NULL ;
    }
  else 
   // keine vernuenftige Linie angegeben
   return NULL ;

#undef R
#undef PV
#undef P3
#undef P2
#undef P1
  }

// Berechnung einer mittleren Abweichung
void *CalcMiddDev (pv FAR *args)
  {
  // args[1] ... 3,5,7 (Anzahl der moeglichen Unterteilungen)
  // args[2] ... Anzahl der zu untersuchende Werte
  // args[3+i*4] ... Wert
  // args[4+i*4] ... Norm
  // args[5+i*4] ... Abweichung
  // args[6+i*4] ... Wertigkeit

#define ANZ             int (*((DBINT FAR *) (args[2])))
#define WERT(I)         (*((float FAR *) (args[3+4*(I)])))
#define NORM(I)         (*((float FAR *) (args[4+4*(I)])))
#define DEV(I)          (*((float FAR *) (args[5+4*(I)])))
#define FCT(I)          (*((float FAR *) (args[6+4*(I)])))

  double div = 0.0 ;
  double val = 0.0 ;
  for (int i = 0 ; i < ANZ ; i++) {
    BOOL allexist = TRUE ;
    for (int j = 0 ; j < 4 ; j++) 
      allexist = ((allexist) && (args[3+4*i+j] != NULL));
    if ((allexist) && (DEV(i) > 0.01)) {
      val += ((WERT(i) - NORM(i)) / DEV(i)) * FCT(i) ;
      div += fabs(FCT(i));
#ifdef UEBERLEGT
      if (FCT(i) >= 0.0) {
        val += (WERT(i) - NORM(i)) / DEV(i) ;
        div += FCT(i);
        }
      else {
        val += (NORM(i) - WERT(i)) / DEV(i) ;
        div -= FCT(i);
        }
#endif
      }
    }
  if (div > 0.01) {
    float ind = float (val / div) ;
    int AnzVals = int (*((DBINT FAR *) args[1]));
    int ig = (ind <= 0.0) ? int (-ind) : int (ind);
    int si = (ind <= 0.0) ? -1 : 1 ;
    switch (AnzVals) {
#define CLIP(A) { if (ig > A) ig = A ; }
      case 3 :
        CLIP(1);
        result.inres = 1 + ig * si;
        break ;
      case 5 :
        CLIP(2);
        result.inres = 2 + ig * si;
        break ;
      case 7 :
        CLIP(3);
        result.inres = 3 + ig * si;
        break ;
#undef CLIP
      default :
        return NULL;
      }
    return &result.inres;
    }
  else return NULL ;

#undef ANZ             
#undef WERT
#undef NORM
#undef DEV 
#undef FCT 
  }

void *ArcSin (pv FAR *args)
  {
  // args[1] ... y
  // args[2] ... l
#define Y       (* ((float FAR *) (args[1])))
#define L       (* ((float FAR *) (args[2])))
  if ((args[1] != NULL) && (args[2] != NULL) && 
                (L >= 0.01)) {
    double phi = asin (Y / L) ;
    if (Y < 0.0) phi = -phi ;
    result.floatres = float (phi * 180.0 / pi) ;
    return &result.floatres;
    }
  else return NULL ;
#undef  Y
#undef  L
  }

void *CopyCont (pv FAR *args)
  {
  // args[1] ... zu kopierende Kontur
  if (args[1] != NULL) {
    int Size = GetBlockSize (args[1]);
    GLOBALHANDLE hGtmp = GlobalAlloc (GMEM_MOVEABLE,Size);
    LPSTR Buffer = LPSTR(GlobalLock (hGtmp));
    lmemcpy (Buffer,args[1],Size);
    result.cntres.ContSize = Size ;
    result.cntres.Contmem = hGtmp ;
    return &result.cntres;
    }
  else return NULL;
  }

void *GenVect (pv FAR *args)
  {
  // args[1] ... Laenge des resultierenden Vektors
  // args[2] ... Ursprung des ausgangs - Patterns
  // args[3] ... 2. Punkt der Linie
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    double dx = ((fpt FAR *) (args[3]))->x - ((fpt FAR *) (args[2]))->x ;
    double dy = ((fpt FAR *) (args[3]))->y - ((fpt FAR *) (args[2]))->y ;
    double l  = hypot (dx,dy);
    if (l > 1.0E-3) {
      result.fptres.x = float ((* (float FAR *) args[1]) * dx / l) ;
      result.fptres.y = float ((* (float FAR *) args[1]) * dy / l) ;
      }
    return &result.fptres;
    }
  else return NULL ;
  }

void *AddVect (pv FAR *args)
  {
  // args[1] ... Vektor 1
  // args[2] ... Vektor 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.fptres.x = ((fpt FAR *) (args[1]))->x + ((fpt FAR *) (args[2]))->x ;
    result.fptres.y = ((fpt FAR *) (args[1]))->y + ((fpt FAR *) (args[2]))->y ;
    return &result.fptres;
    }
  else return NULL ;
  }

void *SubVect (pv FAR *args)
  {
  // args[1] ... Vektor 1
  // args[2] ... Vektor 2
  // Vektor 1 minus Vektor 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.fptres.x = ((fpt FAR *) (args[1]))->x - ((fpt FAR *) (args[2]))->x ;
    result.fptres.y = ((fpt FAR *) (args[1]))->y - ((fpt FAR *) (args[2]))->y ;
    return &result.fptres;
    }
  else return NULL ;
  }

void *AddLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.lres = *((long FAR *) (args[1])) + *((long FAR *) (args[2])) ;
    return &result.lres;
    }
  else return NULL ;
  }

void *SubLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.lres = *((long FAR *) (args[1])) - *((long FAR *) (args[2])) ;
    return &result.lres;
    }
  else return NULL ;
  }

void *MulLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.lres = *((long FAR *) (args[1])) * *((long FAR *) (args[2])) ;
    return &result.lres;
    }
  else return NULL ;
  }

void *DivLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL) && (*(long FAR *) args[2] != 0)) {
    result.lres = *((long FAR *) (args[1])) / *((long FAR *) (args[2])) ;
    return &result.lres;
    }
  else return NULL ;
  }

void *MaskLong (pv FAR *args)
  {
  // args[1] .. wert 
  // args[2] .. maske
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.lres = (*((long FAR *) (args[1]))) & (*((long FAR *) (args[2]))) ;
    return &result.lres;
    }
  else return NULL ;
  }


void *FindLong (pv FAR *args)
  {
  // args[1] .. wert 
  // args[2] - args[?] .. Wert
  if (args[1] != NULL) {
    for (int i = 2 ; args[i] ; i++) {
      if (*((long FAR *) (args[i])) ==
            *((long FAR *) (args[1]))) break;
      }
    if (args[i] == NULL)
      i = NULL ;
    else
      i -= 2 ;
    result.inres = i;

    return &result.inres;
    }
  else return NULL ;
  }


void *GetLong (pv FAR *args)
  {
  // args[1] .. index
  // args[2] - args[?] .. Feld
  if ((args[1] != NULL) && (args[2+*((DBINT FAR *) (args[1]))] != NULL)) {
    result.lres = * ((long FAR *) (args[2+*((DBINT FAR *) (args[1]))]));
    return &result.lres;
    }
  else return NULL ;
  }


void *CntmCro (pv FAR *args)
  {
  // args[1] ... zu untersuchende Kontur
  // args[2] ... 1. Punkt der Gerade
  // args[3] ... 1. Punkt der Gerade
  // args[4] ... Punkt in deren Richtung der extremwert gesucht werden soll
  if ((args[1] != NULL) && (args[2] != NULL) && 
      (args[3] != NULL) && (args[4] != NULL)) {
    contmcro (&result.fptres,(LPFPT) args[1],(LPFPT) args[2],(LPFPT) args[3],(LPFPT) args[4]);
    if (result.fptres.x < 1.0E9)
      return &result.fptres;
    else
      return NULL ;
    }
  else return NULL ;
  }


void *StretchCont (pv FAR *args)
  {
  // args[1] ... Kontur
  // args[2] ... definierter Anfangspunkt der Kontur
  // args[3] ... Punkt, an den sich der Anfangspunkt befinden soll
  // args[4] ... Punkt, an dem sich der Endpunkt befinden soll

#define CNTBEG ((fpt FAR *) (args[2]))
#define BEGPT  ((fpt FAR *) (args[3]))
#define ENDPT  ((fpt FAR *) (args[4]))

  int PtCount;
  fpt FAR *CNT = get_cont((fpt FAR *)args[1], &PtCount);
  if ((PtCount > 1) &&
      (CNTBEG != NULL) && (BEGPT != NULL) && (ENDPT != NULL) &&
      (CNTBEG->x < 1.0E9) && (BEGPT->x < 1.0E9) && (ENDPT->x < 1.0E9)) {
    float dx1, dy1, dx2, dy2;
    if (hypot(CNT[0].x - CNTBEG->x, CNT[0].y - CNTBEG->y) < 1.0E-3) {
      dx1 = BEGPT->x - CNT[0].x;
      dy1 = BEGPT->y - CNT[0].y;
      dx2 = ENDPT->x - CNT[PtCount-1].x;
      dy2 = ENDPT->y - CNT[PtCount-1].y;
      }
    else if (hypot(CNT[PtCount-1].x - CNTBEG->x, CNT[PtCount-1].y - CNTBEG->y) < 1.0E-3) {
      dx1 = ENDPT->x - CNT[0].x;
      dy1 = ENDPT->y - CNT[0].y;
      dx2 = BEGPT->x - CNT[PtCount-1].x;
      dy2 = BEGPT->y - CNT[PtCount-1].y;
      }
    else
      return NULL;
    GLOBALHANDLE hGCont = GlobalAlloc (GHND,sizeof(fpt) * PtCount);
    fpt FAR *DST = (fpt FAR *)GlobalLock (hGCont);
    float step = (float)1.0 / (float)(PtCount-1);
    float t = float(0.0);
    for (int i = 0; i < PtCount; i++) {
      float g2 = ((float)3.0 - ((float)2.0 * t)) * t * t;
      float g1 = (float)1.0 - g2;
      DST[i].x = CNT[i].x + g1 * dx1 + g2 * dx2;
      DST[i].y = CNT[i].y + g1 * dy1 + g2 * dy2;
      t += step;
      }
    GlobalUnlock (hGCont);
    result.cntres.ContSize = PtCount * sizeof (fpt);
    result.cntres.Contmem = hGCont ;
    return &result.cntres;
    }
  else return NULL ;

#undef CNTBEG
#undef BEGPT
#undef ENDPT
  }

void *AddDays (pv FAR *args)
  {
  // args[1] ... Ausgangsdatum
  // args[2] ... Anzahl Tage, die dazu gezaehlt werden sollen
  if ((args[1] != NULL) && (args[2] != NULL)) {
    INTTIME t = PackTime ((packdate FAR *) args[1]);
    INTTIME d = INTTIME (*((DBINT FAR *) (args[2])));
    d *= INTTIME (LONG (24) * LONG (60) * LONG (60)) ;
    t += d ;
    UnPackTime (t,&result.pd);
    return &result.pd;
    }
  else return NULL;
  }

void *AddInd (pv FAR *args)
  {
  // args[1] ... Index 1
  // args[2] ... Index 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.inres = *(DBINT FAR *) args[1] + *(DBINT FAR *) args[2];
    return &result.inres ;
    }
  else return NULL;
  }

void *MulInd (pv FAR *args)
  {
  // args[1] ... Index 1
  // args[2] ... Index 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.inres = *(DBINT FAR *) args[1] * *(DBINT FAR *) args[2];
    return &result.inres ;
    }
  else return NULL;
  }

void *DivInd (pv FAR *args)
  {
  // args[1] ... Index 1
  // args[2] ... Index 2
  if ((args[1] != NULL) && (args[2] != NULL) && (*(DBINT FAR *) args[2] != 0)) {
    result.inres = *(DBINT FAR *) args[1] / *(DBINT FAR *) args[2];
    return &result.inres ;
    }
  else return NULL;
  }

void *SubInd (pv FAR *args)
  {
  // args[1] ... Index 1
  // args[2] ... Index 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.inres = *(DBINT FAR *) args[1] - *(DBINT FAR *) args[2];
    return &result.inres ;
    }
  else return NULL;
  }

void *AddMonths (pv FAR *args)
  {
  // args[1] ... Ausgangsdatum
  // args[2] ... Anzahl Tage, die dazu gezaehlt werden sollen
  if ((args[1] != NULL) && (args[2] != NULL)) {
    packdate res = *((packdate FAR *) args[1]);
    int dm = *((DBINT FAR *) (args[2]));
    int oy;
    if (dm > 0) {
      int m = res.month + dm;
      oy = (m - 1) / 12 ;
      res.month = (m - 1) % 12 + 1;
      }
    else {
      int m = res.month + dm;
      for ( oy = 0 ; (m <= 0) ; ) {
        m = m + 12 ;
        oy -- ;
        }
      res.month = m ;
      }
    res.year += oy ;
    if (res.day > (unsigned) DaysInMonth (res.year,res.month))
      res.day = DaysInMonth (res.year,res.month);
    lmemcpy (&result.pd,&res,sizeof(res));
    return &result.pd;
    }
  else return NULL;
  }

void *AddYears (pv FAR *args)
  {
  // args[1] ... Ausgangsdatum
  // args[2] ... Anzahl Tage, die dazu gezaehlt werden sollen
  if ((args[1] != NULL) && (args[2] != NULL)) {
    packdate res = *((packdate FAR *) args[1]);
    res.year += *(DBINT FAR *) (args[2]);
    if (res.day > (unsigned) DaysInMonth (res.year,res.month))
      res.day = DaysInMonth (res.year,res.month);
    lmemcpy (&result.pd,&res,sizeof(res));
    return &result.pd;
    }
  else return NULL;
  }

void *fGetThirdPt (pv FAR *args)
  {
  GetThirdPt (LPFPT(args[1]),LPFPT(args[2]),&result.fptres,LPFLOAT(args[3]),LPFLOAT(args[4]),LPBOOL(args[5]));
  if (result.fptres.x < 1.0E20)
    return &result.fptres;
  else
    return NULL ;
  }

void *fGetNAbstPt (pv FAR *args)
  {
  GetNAbstPt (LPFPT(args[1]),LPFPT(args[2]),LPFPT(args[3]),&result.fptres,LPFLOAT(args[4]),LPFLOAT(args[5]));
  if (result.fptres.x < 1.0E20)
    return &result.fptres;
  else
    return NULL ;
  }

void *fGetRotPt (pv FAR *args)
  {
  GetRotPt (LPFPT(args[1]),LPFPT(args[2]),&result.fptres,LPFLOAT(args[3]),LPFLOAT(args[4]));
  if (result.fptres.x < 1.0E20)
    return &result.fptres;
  else
    return NULL ;
  }

void *GetSin (pv FAR *args)
  {
  if (args[1] != NULL) {
    double ang = double (*((float FAR *) args[1])) * pi / 180.0;
    result.floatres = float (sin (ang));
    return &result.floatres;
    }
  else
    return NULL;
  }

void *GetCos (pv FAR *args)
  {
  if (args[1] != NULL) {
    double ang = double (*((float FAR *) args[1])) * pi / 180.0;
    result.floatres = float (cos (ang));
    return &result.floatres;
    }
  else
    return NULL;
  }

void *AddYearsDec (pv FAR *args)
  {
  // args[1] ... Ausgangsdatum
  // args[2] ... Anzahl Jahre, die dazu gezaehlt werden sollen
  if ((args[1] != NULL) && (args[2] != NULL)) {
    packdate res = *((packdate FAR *) args[1]);
    float d = *(float FAR *) (args[2]);
    res.year += int (d);
    d -= float(int(d));
    d *= float (12.0) ;   // Anzahl Monate
    int m = res.month + int (d);
    int oy = (m - 1) / 12 ;
    res.month = (m - 1) % 12 + 1;
    res.year += oy ;
    if (res.day > (unsigned) DaysInMonth (res.year,res.month))
      res.day = DaysInMonth (res.year,res.month);
    lmemcpy (&result.pd,&res,sizeof(res));
    return &result.pd;
    }
  else return NULL;
  }

void *DiffTime (pv FAR *args)
  {
  // args[1] ... Zeit1  (muss groesser als t2 sein)
  // args[2] ... Zeit2  
  if ((args[1] != NULL) && (args[2] != NULL)) {
    packtime FAR *t1 = (packtime FAR *) args[1];
    packtime FAR *t2 = (packtime FAR *) args[2];
    int dm,dh ;
    int second,minute,hour;
    second = t1->second - t2->second ;
    if (second < 0) dm = 1 , second = 60 + second ;
    else            dm = 0 ;
    minute = t1->minute - t2->minute - dm ;
    if (minute < 0) dh = 1 , minute = 60 + minute ;
    else            dh = 0;
    hour = t1->hour - t2->hour - dh ;
    if (hour >= 0) {
      packtime t;
      t.hundred_second = 0;
      t.second = second ;
      t.minute = minute ;
      t.hour   = hour   ;
      result.pt = t;
      return &result.pt;
      }
    else
      return NULL ;
    }
  else return NULL;
  }

void *SetTime (pv FAR *args)
  {
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL)) {
    packtime t;
    t.hour = BYTE(min(23,*(WORD FAR *) args[1]));
    t.minute = BYTE(min(59,*(WORD FAR *) args[2]));
    t.second = BYTE(min(59,*(WORD FAR *) args[3]));
    t.hundred_second = 0;
    result.pt = t;
    return &result.pt;
    }
  else return NULL;
  }

void *AddTime (pv FAR *args)
  {
  if ((args[1] != NULL) && (args[2] != NULL)) {
    packtime FAR *t1 = (packtime FAR *) args[1];
    packtime FAR *t2 = (packtime FAR *) args[2];
    packtime t;
    t.hundred_second = 0;
    t.second = t1->second + t2->second ;
    t.minute = t1->minute + t2->minute + t.second / 60 ;
    t.hour = t1->hour + t2->hour + t.minute / 60 ;
    t.second = t.second % 60 ;
    t.minute = t.minute % 60 ;
    t.hour = t.hour % 24 ;
    result.pt = t;
    return &result.pt;
    }
  else return NULL;
  }

void *AddRelTime (pv FAR *args)
  {
  if ((args[1] != NULL) && (args[2] != NULL) && (args[3] != NULL) && (args[4] != NULL)) {
    packtime FAR *t1 = (packtime FAR *) args[1];
    DBINT FAR *h = (DBINT FAR *)(args[2]);
    DBINT FAR *m = (DBINT FAR *)(args[3]);
    DBINT FAR *s = (DBINT FAR *)(args[4]);
    packtime t;
    t.hundred_second = 0;
    int second = int(t1->second) + *s ;
    int ds = (second + 120) / 60 - 2 ; second = (second + 120) % 60 ;
    int minute = int(t1->minute) + *m + ds ;
    int dm = (minute + 120) / 60 - 2 ; minute = (minute + 120) % 60 ;
    int hour = int(t1->hour) + *h + dm ;
    t.second = second;
    t.minute = minute;
    t.hour = (hour + 48) % 24 ;
    result.pt = t;
    return &result.pt;
    }
  else return NULL;
  }

void * GetX (pv FAR *p)
  {
  // p[1] ... Punkt 1
  if (p[1] != NULL) {
    result.floatres = ((fpt FAR *) p[1])->x;
    return &result.floatres;
    }
  else return NULL ;
  }

void * GetY (pv FAR *p)
  {
  // p[1] ... Punkt 1
  if (p[1] != NULL) {
    result.floatres = ((fpt FAR *) p[1])->y;
    return &result.floatres;
    }
  else return NULL ;
  }

void *ClipCont (pv FAR *p)
  {
  // p[1] ... Kontur
  // p[2] ... p1
  // p[3] ... p2
  if ((p[1] != NULL) && (p[2] != NULL) && (p[3] != NULL)) {
    fpt FAR *res = contclip ((fpt FAR *)p[1],(fpt FAR *) p[2],(fpt FAR *) p[3]) ;
    if (res != NULL) {
      result.cntres.ContSize = GetBlockSize(res);
      GLOBALHANDLE hGtmp = GlobalAlloc (GMEM_MOVEABLE,result.cntres.ContSize);
      lmemcpy (GlobalLock (hGtmp),res,result.cntres.ContSize);
      GlobalUnlock (hGtmp);
      FreeGlobMem (res);
      result.cntres.Contmem = hGtmp ;
      return &result.cntres;
      }
    else return NULL ;
    }
  else return NULL ;
  }

void *AddQLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.qlong = *((long double FAR *) (args[1])) + *((long double FAR *) (args[2])) ;
    return &result.qlong;
    }
  else return NULL ;
  }

void *SubQLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.qlong = *((long double FAR *) (args[1])) - *((long double FAR *) (args[2])) ;
    return &result.qlong;
    }
  else return NULL ;
  }

void *MulQLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.qlong = *((long double FAR *) (args[1])) * *((long double FAR *) (args[2])) ;
    return &result.qlong;
    }
  else return NULL ;
  }

void *DivQLong (pv FAR *args)
  {
  // args[1] .. wert 1
  // args[2] .. wert 2
  if ((args[1] != NULL) && (args[2] != NULL) && (*(long double FAR *) args[2] != (long double) 0.0)) {
    result.qlong = *((long double FAR *) (args[1])) / *((long double FAR *) (args[2])) ;
    return &result.qlong;
    }
  else return NULL ;
  }

void *PtInCont (pv FAR *args)
  {
  // args[1] .. punkt
  // args[2] .. contur
  if ((args[1] != NULL) && (args[2] != NULL)) {
    result.inres = DBINT (ptincont ((fpt FAR *) args[1],(fpt FAR *) args[2]));
    return &result.inres;
    }
  else return NULL ;
  }

void *dosqrt (pv FAR *args)
  {
  // args[1] .. wert
  if ((args[1] != NULL) && (* ((float FAR *) args[1]) > 0.0)) {
    result.floatres = float (sqrt (* ((float FAR *) args[1])));
    return &result.floatres;
    }
  else return NULL ;
  }

