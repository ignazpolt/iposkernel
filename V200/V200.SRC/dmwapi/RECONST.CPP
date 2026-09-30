//////////////////////////////////////////////////////////
//  Funktionen zur Konstruktion von Punkten
//////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/dmwapi/rev/reconst.cpv   1.1   02 Feb 1996 10:46:18   GERHOLD  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/reconst.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:46:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:56   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   15 Nov 1993 14:02:54   HANNES
// Initial revision.
//
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "reconst.hpp"

#define HUGE   1.0E21
#define FHUGE  float (HUGE)

DLLExport void _export WINAPI GetThirdPt (LPFPT p1,LPFPT p2,LPFPT p3,LPFLOAT l1,LPFLOAT l2,LPBOOL lpright)
  {
  p3->x = p3->y = FHUGE ;
  if ((p1 != NULL) && (p2 != NULL) && (l1 != NULL) && (l2 != NULL) && (lpright != NULL)) {
    double dx = double (p2->x - p1->x);
    double dy = double (p2->y - p1->y);
    if ((fabs(dx) > 1.0E-3) || (fabs(dy) > 1.0E-3)) {
      double l22 = *l2 * *l2 ;
      double l12 = *l1 * *l1 ;
      double pxa,pxb,pya,pyb;
      BOOL done = FALSE ;
      if (fabs(dx) > fabs(dy)) {
        double b = - dy / dx ;
        double a = (l12 - l22 + dx * dx + dy * dy) / (2.0 * dx) ;
        double g   = 1.0 + b * b ;
        double h_2  = a * b / g ;
        double h_22 = h_2 * h_2 ;
        double i    = (- l12 + a * a) / g ;
        if (h_22 > i) {
          double s = sqrt (h_22 - i);
          pya = - h_2 + s ; pxa = a + b * pya ;
          pyb = - h_2 - s ; pxb = a + b * pyb ;
          done = TRUE ;
          }
        }
      else {
        double b = - dx / dy ;
        double a = (l12 - l22 + dx * dx + dy * dy) / (2.0 * dy) ;
        double g   = 1.0 + b * b ;
        double h_2  = a * b / g ;
        double h_22 = h_2 * h_2 ;
        double i    = (- l12 + a * a) / g ;
        if (h_22 > i) {
          double s = sqrt (h_22 - i);
          pxa = - h_2 + s ; pya = a + b * pxa ;
          pxb = - h_2 - s ; pyb = a + b * pxb ;
          done = TRUE ;
          }
        }
      if (done) {
        BOOL pisright = ((dx * pya - dy * pxa) < 0.0);
        if (((pisright) && (*lpright)) ||
            ((!pisright) && (!*lpright)))
          p3->x = p1->x + float (pxa) ,
          p3->y = p1->y + float (pya) ;
        else
          p3->x = p1->x + float (pxb) ,
          p3->y = p1->y + float (pyb) ;
        }
      }
    }
  }

DLLExport void _export WINAPI GetNAbstPt (LPFPT p1,LPFPT p2,LPFPT p3,LPFPT p4,LPFLOAT a1,LPFLOAT a2)
  {
  p4->x = p4->y = FHUGE ;
  if ((p1 != NULL) && (p2 != NULL) && (p3 != NULL) && (a1 != NULL) && (a2 != NULL)) {
    double dx = p2->x - p1->x ;
    double dy = p2->x - p1->x ;
    double l = sqrt(dx * dx + dy * dy);
    if (l > 1.0E-3) {
      double inprod = (p3->x - p1->x) * dx + (p3->y - p1->y) * dy;
      dx /= l ;
      dy /= l ;
      double t = inprod / l ;
      double p0x = p1->x + t * dx ;
      double p0y = p1->y + t * dy ;
      p4->x = float (p0x + *a2 * dx - *a1 * dy) ;
      p4->y = float (p0y + *a2 * dy + *a1 * dx) ;
      }
    }
  }

DLLExport void _export WINAPI GetRotPt   (LPFPT p1,LPFPT p2,LPFPT p3,LPFLOAT lnew,LPFLOAT phi)
  {
  p3->x = p3->y = FHUGE ;
  if ((p1 != NULL) && (p2 != NULL) && (lnew != NULL) && (phi != NULL)) {
    double dx = p2->x - p1->x ;
    double dy = p2->y - p1->y ;
    double l = sqrt (dx * dx + dy * dy) ;
    if (l > 1.0E-3) {
      dx /= l ;
      dy /= l ;
      double p = *phi * 3.1415 / 180.0 ;
      double cp = cos (p);
      double sp = sin (p);
      double dxn = *lnew * (cp * dx - sp * dy);
      double dyn = *lnew * (sp * dx + cp * dy);
      p3->x = p1->x + float (dxn) ;
      p3->y = p1->y + float (dyn) ;
      }
    }
  }

DLLExport void _export WINAPI GetMidPts (LPFPT pg1,LPFPT pg2,LPFPT pm1,LPFPT pm2,
                                   LPFPT pl11,LPFPT pl12,LPFPT pl21,LPFPT pl22,
                                   LPFLOAT lpdy,LPFLOAT lpc,LPFPT r1,LPFPT r2)
  {
  // Berechnung von den Punkte so dass:
  //   - Differenz der Normalabstaende r1 und r2 auf gp1,pg2 dy entspricht
  //   - Verhaeltnis der Normalabstaende r1 auf pg1,pg2 und r2 auf pm2,pm1
  //     c entspricht
  //   - r1 auf der Linie pl11,pl12 liegt
  //   - r2 auf der Linie pl21,pl22 liegt
  r1->x = r1->y = r2->x = r2->y = FHUGE ;
  if ((pg1 != NULL) && (pg2 != NULL) && 
      (pm1 != NULL) && (pm2 != NULL) && 
      (pl11 != NULL) && (pl12 != NULL) && 
      (pl21 != NULL) && (pl22 != NULL) && 
      (lpdy != NULL) && (lpc != NULL)) {
    // Normieren der Vektoren pg2-pg1, pm1 - pm2
    double dgx = double (pg2->x - pg1->x) ;
    double dgy = double (pg2->y - pg1->y) ;
    double dmx = double (pm1->x - pm2->x) ;
    double dmy = double (pm1->y - pm2->y) ;
    double lg  = sqrt (dgx * dgx + dgy * dgy);
    double lm  = sqrt (dmx * dmx + dmy * dmy);
    if ((lg < 1.0E-3) || (lm < 1.0E-3)) return ;
    dgx /= lg ; dgy /= lg ;
    dmx /= lm ; dmy /= lm ;
    // Geradengleichung (x = a * y + b)
    double a1x = double (pl12->x - pl11->x);
    double a1y = double (pl12->y - pl11->y);
    double a2x = double (pl22->x - pl21->x);
    double a2y = double (pl22->y - pl21->y);
    if ((fabs (a1y) < 1.0E-3) || (fabs (a2y) < 1.0E-3)) return ;
    double a1 = a1x / a1y ;
    double a2 = a2x / a2y ;
    double b1 = - a1 * double (pl11->y) + double (pl11->x);
    double b2 = - a2 * double (pl21->y) + double (pl21->x);
    // Berechnung von r2y
    //  Nach dem Schema:
    //    I)  (r1 - pg1) X (pg2 - pg1) - (r2 - pg1) X (pg2 - pg1) = dy
    //    II) (r1 - pg1) X (pg2 - pg1) - c * (r2 - pm2) X (pm1 - pm2) = 0
    //    aus I - II) und mit den Geradengleichnungen kann r2 berechnet werden
    //    aus I) mit r2 und den Geradengleichnungen kann r1 berechnet werden
    double a = - dgy * a2 + dgx + double (*lpc) * (a2 * dmy - dmx);
    double b = dgy * (double (pg1->x) - b2) - double (pg1->y) * dgx 
               + double (*lpc) * (dmy * (b2 - double (pm2->x)) +
                                  double (pm2->y) * dmx
                                 ) - double (*lpdy);
    if (fabs(a) < 1.0E-3) return;
    double r2y = - b / a ;
    double r2x = r2y * a2 + b2 ;
    a = a1 * dgy - dgx ;
    b = (b1 - double(pg1->x)) * dgy + double (pg1->y) * dgx
        - ((r2x - double (pg1->x)) * dgy - (r2y - double (pg1->y)) * dgx)
        - double (*lpdy);
    if (fabs(a) < 1.0E-3) return ;
    double r1y = - b / a;
    double r1x = a1 * r1y + b1 ;
    r1->x = float (r1x);
    r1->y = float (r1y);
    r2->x = float (r2x);
    r2->y = float (r2y);
    }
  }

