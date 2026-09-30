///////////////////////////////////////////////////////////
//
//  Linien, wie sie im Hauptprogramm verwendet werden
//
//  $Header:   P:/marille/clinicum/ctool/rev/myline.cpv   1.1   02 Feb 1996 10:41:58   GERHOLD  $
//  $Log:   P:/marille/clinicum/ctool/rev/myline.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:41:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:41:20   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   22 Jul 1993 14:40:36   HANNES
// Style Range Ueberpruefung..
// 
//    Rev 1.0   21 Jul 1993 09:44:34   HANNES
// Initial revision.
///////////////////////////////////////////////////////////
#include <windows.h>
#include <math.h>
#include "dds32.h"

typedef double (* NEXTSTOP) (double *,double,double,int *);

#define STATE_LINE0     0
#define STATE_LINE1     2
#define STATE_SPACE0    1
#define STATE_SPACE1    3

static inline int myround (double x)
  {
  if (x < 0.0) return int (x - 0.5);
  else         return int (x + 0.5);
  }

static double llen,splen,lslen;
double NextDashed (double *lold,double lact,double lges,int *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = llen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }

double NextDotDashed (double *lold,double lact,double lges,int *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = llen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE1 ;
      break ;
    case STATE_LINE1 :
      dl = lslen - *lold ;
      *state = STATE_SPACE1 ;
      break ;
    case STATE_SPACE1 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }

double NextDot (double *lold,double lact,double lges,int *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = splen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }


#define MAXLFNC 4
NEXTSTOP Nextl[MAXLFNC] = {
  NULL ,          // PS_SOLID
  NextDashed ,    // PS_DASHED
  NextDot ,       // PS_DOT
  NextDotDashed , // PS_DOTDASHED
  };

#define PS_NONE   7

static int xold,yold;
static double lold;
static int state;

void MyMoveTo (HDC hDC,int x,int y)
  {
  xold = x ;
  yold = y ;
  lold = 0.0 ;
  state = 0 ;
  MoveToEx (hDC,x,y, NULL);
  }

void MyLineTo (HDC hDC,int x,int y,double mapFact,int Style,int Width)
  {
  // Untersuchung, obs ueberhaupt noetig
  if (Style == PS_NONE) return ;    // so nicht
  if (Style != PS_SOLID) {
    double lact = 0.0 ;
    double dy = double (y - yold);
    double dx = double (x - xold);
    double lges = hypot (dx,dy);
    Style = max(1,min(Style,MAXLFNC-1));
    // Berechnung der Laengen der Teilstuecke
    llen  = 75.0 * mapFact ;
    lslen = splen = 25.0 * mapFact ;
    double w2 = double (Width) / 2.0 ;
    llen -= w2 ;
    lslen -= w2 ;
    splen += w2 ;
    if (lges >= 0.5) {
      for ( int i = state + 1 ; ; i++ ) {
        lact = (* Nextl[Style]) (&lold,lact,lges,&state);
        int xn = xold + myround (lact / lges * dx);
        int yn = yold + myround (lact / lges * dy);
        if (i & 0x01) LineTo (hDC,xn,yn); 
        else          MoveToEx (hDC,xn,yn, NULL);
        if (lact >= lges - 0.5) break ;
        }
      }
    }
  else
    LineTo (hDC,x,y);
  xold = x ; yold = y ;
  }

