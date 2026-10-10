////////////////////////////////////////////////////////
//  Definitionen fuer kubisch interpolierte Konturen  //
////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/cubspl.cpv   1.10   11 Sep 1997 19:00:32   HANNES  $
// $Log:   P:/marille/clinicum/frmobj/rev/cubspl.cpv  $
// 
//    Rev 1.10   11 Sep 1997 19:00:32   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.9   18 Aug 1997 18:05:22   Martin
// VTO Formular-faehig
// 
//    Rev 1.8   11 Apr 1997 15:51:08   Martin
// myacos fuer Werte kleiner -1
// 
//    Rev 1.7   11 Apr 1997 15:09:10   Martin
// myacos ...
// 
//    Rev 1.6   24 Mar 1996 12:11:12   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.5   02 Feb 1996 10:49:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   24 Aug 1995 00:15:02   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.3   20 Mar 1995 12:13:28   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.2   10 Nov 1994 14:30:36   MARTIN
// top < bottom
// 
//    Rev 1.1   27 Jun 1994 10:50:36   HANNES
// Inline Funktionen nicht exportieren
// 
//    Rev 1.0   24 Jun 1994 16:45:38   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.14   13 Jan 1994 16:10:46   HANNES
// dfield inc. weg
// 
//    Rev 1.13   12 Jan 1994 11:03:38   HANNES
// Unnoetige Includes eleminiert
// 
//    Rev 1.12   18 Oct 1993 19:54:56   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.11   05 Sep 1993 22:15:22   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.10   27 Jun 1993 11:52:14   MARTIN
// uCalcSoftVect
// 
//    Rev 1.9   16 Jun 1993 17:01:54   MARTIN
// ChangeCubSplPt: Behandlung von UpdateMode geaendert
// (neu: 0 = nichts, 1 = nur Variable, 2 = nur Kontur, 3 = beides)
// 
//    Rev 1.8   16 Jun 1993 16:49:20   MARTIN
// WriteCubSpl
// 
//    Rev 1.7   15 Jun 1993 23:24:30   MARTIN
// ChangeCubSplPt
// 
//    Rev 1.6   15 Jun 1993 19:20:32   MARTIN
// hGFmem ausgemistet
// 
//    Rev 1.5   02 Jun 1993 12:43:12   MARTIN
// Fehlerkorrektur: WriteData: c->RunNmbr statt 0
// 
//    Rev 1.4   19 May 1993 19:01:38   MARTIN
// uCubSpl
// 
//    Rev 1.3   18 May 1993 17:40:48   MARTIN
// if statt WIN_ASSERT
// 
//    Rev 1.2   19 Apr 1993 01:34:54   MARTIN
// #include "cutcont.hpp"
// 
//    Rev 1.1   09 Mar 1993 22:56:52   MARTIN
// erste funktionsfaehige Version
// 
//    Rev 1.0   03 Mar 1993 15:45:32   MARTIN
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 9
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "dds.h"
#define CARETHANDLING_DONE
#include "cfield.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "cubspl.hpp"


// die ganze Scheibe fuer die Speicherverwaltung

inline LPVOID mymalloc(size_t size)
  {
  return GetGlobMem(size);
  };


inline void myfree(LPVOID obj)
  {
  FreeGlobMem(obj);
  };


LPVOID CubSpl::operator new (size_t size)
  {
  return mymalloc(size);
  }


void CubSpl::operator delete(LPVOID ptr)
  {
  myfree(ptr);
  }


CubSpl::CubSpl()
  {
  head = tail = NULL;
  }


CubSpl::~CubSpl()
  {
  Free();
  }


void CubSpl::AddPt(DWORD m, fpt FAR *p, float wp, float wn, float lp, float ln)
  {
  LPBASEPOINT newpt = (LPBASEPOINT)mymalloc(sizeof(basepoint));
  newpt->m = m;
  newpt->p = *p;
  newpt->wp = wp;
  newpt->wn = wn;
  newpt->lp = lp;
  newpt->ln = ln;
  newpt->next = NULL;
  newpt->prev = tail;
  if (head == NULL)
    head = tail = newpt;
  else
    tail = tail->next = newpt;
  }


void CubSpl::Free()
  {
  LPBASEPOINT tofree, pt = head;
  while (pt != NULL) {
    tofree = pt;
    pt = pt->next;
    myfree(tofree);
    }
  head = tail = NULL;
  }


void CubSpl::CalcDpDn(LPBASEPOINT pt)
  {
  if (pt->prev != NULL) {
    float dx = pt->prev->p.x - pt->p.x;
    float dy = pt->prev->p.y - pt->p.y;
    float cosw = (float)cos(pt->wp);
    float sinw = (float)sin(pt->wp);
    pt->dp.x = cosw * dx - sinw * dy;
    pt->dp.y = sinw * dx + cosw * dy;
    }
  else {
    // Anfangspunkt: kein BP_*_DEPENDENT !
    DBWIN_ASSERT(!(pt->m & (BP_W_DEPENDENT | BP_L_DEPENDENT)));
    }
  if (pt->next != NULL) {
    float dx = pt->next->p.x - pt->p.x;
    float dy = pt->next->p.y - pt->p.y;
    pt->tend = (float)hypot(dx, dy);
    if (pt->tend < MIN_DISTANCE)
      pt->tend = float(MIN_DISTANCE);
    float cosw, sinw;
    if (pt->m & BP_W_DEPENDENT) {
      dx = (pt->prev->p.x - pt->p.x) / pt->prev->tend * pt->tend;
      dy = (pt->prev->p.y - pt->p.y) / pt->prev->tend * pt->tend;
      cosw = (float)cos(pt->wp + pt->wn);
      sinw = (float)sin(pt->wp + pt->wn);
      }
    else {
      cosw = (float)cos(pt->wn);
      sinw = (float)sin(pt->wn);
      }
    pt->dn.x = cosw * dx - sinw * dy;
    pt->dn.y = sinw * dx + cosw * dy;
    }
  else {
    // Endpunkt: kein BP_*_DEPENDENT !
    DBWIN_ASSERT(!(pt->m & (BP_W_DEPENDENT | BP_L_DEPENDENT)));
    }
  }


void CubSpl::CalcAllDpDn()
  {
  for (LPBASEPOINT pt = head; pt != NULL; pt = pt->next)
    CalcDpDn(pt);
  }

const double pi = 3.1415927464;   // fuer Umrechnung von phi in Grad

double myacos(double x)
  {
  if (x >= 1.0)
    return 0.0;
  else if (x <= -1.0)
    return pi;
  else
    return acos(x);
  }

BOOL CubSpl::ChangePt(LPBASEPOINT pt, fpt FAR *p)
  {
  if (pt->m & BP_P_EDITABLE) {
    fpt oldp = pt->p;
    pt->p = *p;
    LPBASEPOINT npt;  // Nachbarpunkt
    if ((npt = pt->prev) != NULL) {
      fpt dold, dnew;
      dold.x = npt->p.x - oldp.x;
      dold.y = npt->p.y - oldp.y;
      dnew.x = npt->p.x - p->x;
      dnew.y = npt->p.y - p->y;
      float oldlen = npt->tend;
      float newlen = (float)hypot(dnew.x, dnew.y);
      if (newlen <= MIN_DISTANCE) return FALSE;
      float dw = (float)myacos((dold.x * dnew.x + dold.y * dnew.y) / (newlen * oldlen));
      if ((dold.x * dnew.y - dold.y * dnew.x) < 0.0)
        dw = -dw;
      pt->wp -= dw;
      if (npt->m & BP_WN_FOLLOW_N) {
        if (npt->m & BP_W_DEPENDENT)
          npt->wp += dw / (float)2.0;
        }
      else {
        if (!(npt->m & BP_W_DEPENDENT))
          npt->wn -= dw;
        }
      float dl = oldlen / newlen;
      pt->lp *= dl;
      if (npt->m & BP_LN_FOLLOW_N) {
        if (npt->m & BP_L_DEPENDENT)
          npt->lp /= (float)sqrt(dl);
        }
      else {
        if (!(npt->m & BP_L_DEPENDENT))
          npt->ln *= dl;
        }
      CalcDpDn(npt);
      }
    if ((npt = pt->next) != NULL) {
      fpt dold, dnew;
      dold.x = npt->p.x - oldp.x;
      dold.y = npt->p.y - oldp.y;
      dnew.x = npt->p.x - p->x;
      dnew.y = npt->p.y - p->y;
      float oldlen = pt->tend;
      float newlen = (float)hypot(dnew.x, dnew.y);
      pt->tend = newlen;
      if (newlen <= MIN_DISTANCE) return FALSE;
      float dw = (float)myacos((dold.x * dnew.x + dold.y * dnew.y) / (newlen * oldlen));
      if ((dold.x * dnew.y - dold.y * dnew.x) < 0.0)
        dw = -dw;
      if (!(pt->m & BP_W_DEPENDENT))
        pt->wn -= dw;
      if (npt->m & BP_WP_FOLLOW_N) {
        if (npt->m & BP_W_DEPENDENT)
          npt->wp -= dw / (float)2.0;
        }
      else
        npt->wp -= dw;
      float dl = oldlen / newlen;
      if (!(pt->m & BP_L_DEPENDENT))
        pt->ln *= dl;
      if (npt->m & BP_LP_FOLLOW_N) {
        if (npt->m & BP_L_DEPENDENT)
          npt->lp *= (float)sqrt(dl);
        }
      else
        npt->lp *= dl;
      CalcDpDn(npt);
      }
    CalcDpDn(pt);
    return TRUE;
    }
  return FALSE;
  }


BOOL CubSpl::ChangeDp(LPBASEPOINT pt, fpt FAR *dp)
  {
  DBWIN_ASSERT(pt->prev != NULL);
  if (pt->m & BP_WP_EDITABLE) {
    BOOL changed = FALSE;
    float newlen = (float)hypot(dp->x, dp->y);
    if (pt->m & BP_LP_EDITABLE) {
      pt->lp = newlen / pt->prev->tend;
      changed = TRUE;
      }
    if (newlen > MIN_DISTANCE) {
      float dw = (float)myacos((pt->dp.x * dp->x + pt->dp.y * dp->y) / (newlen * pt->prev->tend));
      if ((pt->dp.x * dp->y - pt->dp.y * dp->x) < 0.0)
        dw = -dw;
      pt->wp += dw;
      changed = TRUE;
      }
    if (changed) CalcDpDn(pt);
    return changed;
    }
  if (pt->m & BP_LP_EDITABLE) {
    fpt norm;
    norm.x = pt->dp.y / pt->prev->tend;
    norm.y = -pt->dp.x / pt->prev->tend;
    pt->lp = (norm.x * dp->y - norm.y * dp->x) / pt->prev->tend;
    CalcDpDn(pt);
    return TRUE;
    }
  return FALSE;
  }


BOOL CubSpl::ChangeDn(LPBASEPOINT pt, fpt FAR *dn)
  {
  DBWIN_ASSERT(pt->next != NULL);
  if (pt->m & BP_WN_EDITABLE) {
    BOOL changed = FALSE;
    float newlen = (float)hypot(dn->x, dn->y);
    if (pt->m & BP_LN_EDITABLE) {
      if (pt->m & BP_L_DEPENDENT)
        pt->lp = newlen / (pt->prev->tend * pt->ln);
      else
        pt->ln = newlen / pt->tend;
      changed = TRUE;
      }
    if (newlen > MIN_DISTANCE) {
      float dw = (float)myacos((pt->dn.x * dn->x + pt->dn.y * dn->y) / (newlen * pt->tend));
      if ((pt->dn.x * dn->y - pt->dn.y * dn->x) < 0.0)
        dw = -dw;
      if (pt->m & BP_W_DEPENDENT)
        pt->wp += dw;
      else
        pt->wn += dw;
      changed = TRUE;
      }
    if (changed) CalcDpDn(pt);
    return changed;
    }
  if (pt->m & BP_LN_EDITABLE) {
    fpt norm;
    norm.x = pt->dn.y / pt->tend;
    norm.y = -pt->dn.x / pt->tend;
    float newlen = norm.x * dn->y - norm.y * dn->x;
    if (pt->m & BP_L_DEPENDENT)
      pt->lp = newlen / (pt->prev->tend * pt->ln);
    else
      pt->ln = newlen / pt->tend;
    CalcDpDn(pt);
    return TRUE;
    }
  return FALSE;
  }


void CubSpl::InitCalc()
  {
  DBWIN_ASSERT(head != tail);  // mindestens 2 Stuetzpunkte
  tmax = float(0.0);
  for (LPBASEPOINT pt = head, npt = pt->next;
       npt != NULL;
       pt = npt, npt = npt->next) {
    tmax += pt->tend;
    float ln;
    GetLN(&ln, pt);
    if (fabs(ln) < MIN_DISTANCE) {  // Steigung im 1. Punkt unbekannt
      if (fabs(npt->lp) < MIN_DISTANCE) {  // Steigung im 2. Punkt unbekannt
        // lineare Funktion
        pt->ax = pt->bx = float(0.0);
        pt->cx = (npt->p.x - pt->p.x) / pt->tend;
        pt->dx = pt->p.x;
        pt->ay = pt->by = float(0.0);
        pt->cy = (npt->p.y - pt->p.y) / pt->tend;
        pt->dy = pt->p.y;
        }
      else {
        // quadratische Funktion
        float dx = -npt->lp * npt->dp.x;
        float dy = -npt->lp * npt->dp.y;
        float invt = (float)1.0 / pt->tend;
        pt->ax = float(0.0);
        pt->bx = ((pt->p.x - npt->p.x) * invt + dx) * invt;
        pt->cx = dx - (float)2.0 * pt->bx * pt->tend;
        pt->dx = pt->p.x;
        pt->ay = float(0.0);
        pt->by = ((pt->p.y - npt->p.y) * invt + dy) * invt;
        pt->cy = dy - (float)2.0 * pt->by * pt->tend;
        pt->dy = pt->p.y;
        }
      }
    else if (fabs(npt->lp) < MIN_DISTANCE) { // Steigung im 2. Pkt. unbekannt
      // quadratische Funktion
      float dx = ln * pt->dn.x;
      float dy = ln * pt->dn.y;
      float invt = (float)1.0 / pt->tend;
      pt->ax = float(0.0);
      pt->bx = ((npt->p.x - pt->p.x) * invt - dx) * invt;
      pt->cx = dx;
      pt->dx = pt->p.x;
      pt->ay = float(0.0);
      pt->by = ((npt->p.y - pt->p.y) * invt - dy) * invt;
      pt->cy = dy;
      pt->dy = pt->p.y;
      }
    else {
      // kubische Funktion
      float dx1 = ln * pt->dn.x;
      float dy1 = ln * pt->dn.y;
      float dx2 = -npt->lp * npt->dp.x;
      float dy2 = -npt->lp * npt->dp.y;
      float invt = (float)1.0 / pt->tend;
      float zr1 = ((npt->p.x - pt->p.x) * invt - dx1) * invt;
      float zr2 = (dx2 - dx1) * invt - (float)2.0 * zr1;
      pt->ax = zr2 * invt;
      pt->bx = zr1 - zr2;
      pt->cx = dx1;
      pt->dx = pt->p.x;
      zr1 = ((npt->p.y - pt->p.y) * invt - dy1) * invt;
      zr2 = (dy2 - dy1) * invt - (float)2.0 * zr1;
      pt->ay = zr2 * invt;
      pt->by = zr1 - zr2;
      pt->cy = dy1;
      pt->dy = pt->p.y;
      }
    }
  }


void CubSpl::EvalFunc(float t, fpt FAR *res)
  {
  DBWIN_ASSERT(head != tail);  // mindestens 2 Stuetzpunkte
  float tsum = float(0.0);
  LPBASEPOINT pt = head;
  do {
    tsum += pt->tend;
    pt = pt->next;
    } while ((tsum < t) && (pt->next != NULL));
  pt = pt->prev;
  t -= (tsum - pt->tend);
  res->x = ((pt->ax * t + pt->bx) * t + pt->cx) * t + pt->dx;
  res->y = ((pt->ay * t + pt->by) * t + pt->cy) * t + pt->dy;
  }


void CubSpl::CalcCont(fpt FAR *cnt, int numpts)
  {
  if (numpts > 1) {
    InitCalc();
    float dt = tmax / (float)(numpts - 1), t = float(0.0);
    for (int i = 0; i < numpts; i++, t += dt)
      EvalFunc(t, cnt + i);
    }
  }

void CubSpl::GetLN(float FAR *res, LPBASEPOINT pt) 
  {  // berechnet wenn noetig ln
  if (pt->m & BP_L_DEPENDENT)
    *res = pt->lp * pt->prev->tend * pt->ln / pt->tend;
  else
    *res = pt->ln;
  };

////////////////////////// SoftEdit - Objekt ///////////////////////////

SoftEditObj::SoftEditObj(LPVOID p, mdiChild *c) : FrmObject (p, c)
  {
  cs = new CubSpl();
  ed_state = ED_NOTHING;
  clear_old = FALSE;
  actpt = NULL;
  }


SoftEditObj::~SoftEditObj()
  {
  delete cs;
  }

#define KASTL 57

void SoftEditObj::GetMinMax()
  {
  int xmin = 32000, xmax = -32000, ymin = 32000, ymax = -32000;
  for (LPBASEPOINT bp = cs->head; bp != NULL; bp = bp->next) {
    fpt pt;
    Sc2d((tr2 FAR *)&wtos, &pt, &bp->p);
    int px = m.WorldToLog(pt.x);
    int py = m.WorldToLog(pt.y);
    if (bp->m & BP_P_EDITABLE) {
      if ((px - KASTL) < xmin) xmin = px - KASTL;
      if ((px + KASTL) > xmax) xmax = px + KASTL;
      if ((py - KASTL) < ymin) ymin = py - KASTL;
      if ((py + KASTL) > ymax) ymax = py + KASTL;
      }
    else {
      if (px < xmin) xmin = px;
      if (px > xmax) xmax = px;
      if (py < ymin) ymin = py;
      if (py > ymax) ymax = py;
      }
    if (bp != cs->head) {
      pt.x = bp->p.x + bp->dp.x * bp->lp * dispfact;
      pt.y = bp->p.y + bp->dp.y * bp->lp * dispfact;
      Sc2d((tr2 FAR *)&wtos, &pt, &pt);
      int px = m.WorldToLog(pt.x);
      int py = m.WorldToLog(pt.y);
      if (bp->m & (BP_WP_EDITABLE | BP_LP_EDITABLE)) {
        if ((px - KASTL) < xmin) xmin = px - KASTL;
        if ((px + KASTL) > xmax) xmax = px + KASTL;
        if ((py - KASTL) < ymin) ymin = py - KASTL;
        if ((py + KASTL) > ymax) ymax = py + KASTL;
        }
      else {
        if (px < xmin) xmin = px;
        if (px > xmax) xmax = px;
        if (py < ymin) ymin = py;
        if (py > ymax) ymax = py;
        }
      }
    if (bp != cs->tail) {
      float ln;
      cs->GetLN(&ln, bp);
      pt.x = bp->p.x + bp->dn.x * ln * dispfact;
      pt.y = bp->p.y + bp->dn.y * ln * dispfact;
      Sc2d((tr2 FAR *)&wtos, &pt, &pt);
      int px = m.WorldToLog(pt.x);
      int py = m.WorldToLog(pt.y);
      if (bp->m & (BP_WN_EDITABLE | BP_LN_EDITABLE)) {
        if ((px - KASTL) < xmin) xmin = px - KASTL;
        if ((px + KASTL) > xmax) xmax = px + KASTL;
        if ((py - KASTL) < ymin) ymin = py - KASTL;
        if ((py + KASTL) > ymax) ymax = py + KASTL;
        }
      else {
        if (px < xmin) xmin = px;
        if (px > xmax) xmax = px;
        if (py < ymin) ymin = py;
        if (py > ymax) ymax = py;
        }
      }
    }
  int width = m.HalfPenWidth(color);
  RECT rcLogRect;
  rcLogRect.left   = xmin  - width;
  rcLogRect.right  = xmax  + width;
  rcLogRect.top    = ymin  - width;
  rcLogRect.bottom = ymax  + width;
  SetLogRect (&rcLogRect,ErsteSeite());

  schwerx = (xmin + xmax) / 2;
  schwery = (ymin + ymax) / 2;
  }


void SoftEditObj::Paint(PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT(Initialized);
  if (pc->mode == DO_WORK)
    Invalidate(Seite);
  }


void SoftEditObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  SoftEditObj::PaintTrans(pc, Seite, NULL);
  }


void SoftEditObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DBWIN_ASSERT(sc == NULL);
  for (LPBASEPOINT bp = cs->head; bp != NULL; bp = bp->next) {
    fpt pt;
    Sc2d((tr2 FAR *)&wtos, &pt, &bp->p);
    int px = m.WorldToLog(pt.x);
    int py = m.WorldToLog(pt.y);
    if (bp->m & BP_P_EDITABLE)
      DrawMark(pc, Seite, px, py);
    if (bp != cs->head) {
      pt.x = bp->p.x + bp->dp.x * bp->lp * dispfact;
      pt.y = bp->p.y + bp->dp.y * bp->lp * dispfact;
      Sc2d((tr2 FAR *)&wtos, &pt, &pt);
      int dpx = m.WorldToLog(pt.x);
      int dpy = m.WorldToLog(pt.y);
      if (bp->m & (BP_WP_EDITABLE | BP_LP_EDITABLE))
        DrawMark(pc, Seite, dpx, dpy);
      DrawLine(pc, Seite, px, py, dpx, dpy);
      }
    if (bp != cs->tail) {
      float ln;
      cs->GetLN(&ln, bp);
      pt.x = bp->p.x + bp->dn.x * ln * dispfact;
      pt.y = bp->p.y + bp->dn.y * ln * dispfact;
      Sc2d((tr2 FAR *)&wtos, &pt, &pt);
      int dpx = m.WorldToLog(pt.x);
      int dpy = m.WorldToLog(pt.y);
      if (bp->m & (BP_WN_EDITABLE | BP_LN_EDITABLE))
        DrawMark(pc, Seite, dpx, dpy);
      DrawLine(pc, Seite, px, py, dpx, dpy);
      }
    }
  }


void SoftEditObj::DrawMark(PaintContext *pc, int Seite, int px, int py)
  {
  *pc << Line (px+KASTL, py-KASTL, px+KASTL, py+KASTL);
  *pc << Line (px+KASTL, py+KASTL, px-KASTL, py+KASTL);
  *pc << Line (px-KASTL, py+KASTL, px-KASTL, py-KASTL);
  *pc << Line (px-KASTL, py-KASTL, px+KASTL, py-KASTL);
  }


void SoftEditObj::DrawLine(PaintContext *pc, int Seite, int px1, int py1, int px2, int py2)
  {
  *pc << Line (px1, py1, px2, py2);
  }


BOOL SoftEditObj::NearPt(int x, int y, fpt FAR *p)
  {
  fpt pt;
  Sc2d((tr2 FAR *)&wtos, &pt, p);
  int px = m.WorldToLog(pt.x);
  int py = m.WorldToLog(pt.y);
  return (x >= px - KASTL) && (x <= px + KASTL) &&
         (y >= py - KASTL) && (y <= py + KASTL);
  }


void SoftEditObj::MovePt(int x, int y)
  {
  DBWIN_ASSERT(ed_state != ED_NOTHING);
  DBWIN_ASSERT(actpt != NULL);
  if (clear_old)
    DrawMove(m.ActSide());
  fpt pt;
  pt.x = m_LogToWorld(x);
  pt.y = m_LogToWorld(y);
  Sc2d((tr2 FAR *)&stow, &pt, &pt);
  if (ed_state == ED_POINT)
    cs->ChangePt(actpt, &pt);
  else {
    pt.x = (pt.x - actpt->p.x) / dispfact;
    pt.y = (pt.y - actpt->p.y) / dispfact;
    if (ed_state == ED_LEFT)
      cs->ChangeDp(actpt, &pt);
    else if (ed_state == ED_RIGHT)
      cs->ChangeDn(actpt, &pt);
    else
      DBWIN_ASSERT(FALSE);
    }
  DrawMove(m.ActSide());
  clear_old = TRUE;
  }


void SoftEditObj::DrawMove(int Seite)
  {
  DBWIN_ASSERT(Initialized);
  DBWIN_ASSERT(ed_state != ED_NOTHING);
  PaintContext pc;
  GetDocumentContext(&pc, m);
  SetROP2(pc.hDC,R2_XORPEN);
  pc.diPen(MoveColor);
  PaintTrans(&pc, Seite, NULL);
  // Kontur zeichnen
  fpt FAR *hcnt = (fpt FAR *)mymalloc(ptCount * sizeof(fpt));
  cs->CalcCont(hcnt, ptCount);
  int x, y;
  fpt pt;
  Sc2d((tr2 FAR *)&wtos, &pt, hcnt);
  x = m.WorldToLog(pt.x);
  y = m.WorldToLog(pt.y);
  pc.PolyMoveTo(x, y);
  for (int i = 1; i < ptCount; i++) {
    Sc2d((tr2 FAR *)&wtos, &pt, hcnt + i);
    x = m.WorldToLog(pt.x);
    y = m.WorldToLog(pt.y);
    pc.PolyLineTo(x, y);
    }
  myfree(hcnt);
  }


void SoftEditObj::DoMove(int Seite)
  {
  DBWIN_ASSERT(Initialized);
//  DBWIN_ASSERT(ed_state != ED_NOTHING);
  WORD i = 0;
  for (LPBASEPOINT bp = cs->head; bp != NULL; bp = bp->next) {
    if (bp != cs->head) {
      m.WriteData(Par()->fp[i].l.R, Par()->fp[i].l.I, &bp->lp, sizeof(float), 0);
      i++;
      m.WriteData(Par()->fp[i].w.R, Par()->fp[i].w.I, &bp->wp, sizeof(float), 0);
      i++;
      }
    DBWIN_ASSERT((i % 6) == 0);
    i++;
    m.WriteData(Par()->fp[i].p.R, Par()->fp[i].p.I, &bp->p, sizeof(fpt), 0);
    i++;
    if (bp != cs->tail) {
      m.WriteData(Par()->fp[i].w.R, Par()->fp[i].w.I, &bp->wn, sizeof(float), 0);
      i++;
      m.WriteData(Par()->fp[i].l.R, Par()->fp[i].l.I, &bp->ln, sizeof(float), 0);
      i++;
      }
    }
  WORD numfree = ScriptParam->par_Size - sizeof(DefSoftEdit_param);
  numfree = (numfree + sizeof(Par()->fp)) / sizeof(Referenz);
  DBWIN_ASSERT(i == numfree);
  }


BOOL SoftEditObj::OnLButtonDown(WPARAM wP, int x, int y, int Seite)
  {
  if (ed_state != ED_NOTHING) return FALSE;
  for (LPBASEPOINT bp = cs->head; bp != NULL; bp = bp->next) {
    if (bp->m & (BP_WP_EDITABLE | BP_LP_EDITABLE)) {
      fpt pt;
      pt.x = bp->p.x + bp->dp.x * bp->lp * dispfact;
      pt.y = bp->p.y + bp->dp.y * bp->lp * dispfact;
      if (NearPt(x, y, &pt)) {
        ed_state = ED_LEFT;
        actpt = bp;
        MovePt(x, y);
        return TRUE;
        }
      }
    if (bp->m & (BP_WN_EDITABLE | BP_LN_EDITABLE)) {
      fpt pt;
      float ln;
      cs->GetLN(&ln, bp);
      pt.x = bp->p.x + bp->dn.x * ln * dispfact;
      pt.y = bp->p.y + bp->dn.y * ln * dispfact;
      if (NearPt(x, y, &pt)) {
        ed_state = ED_RIGHT;
        actpt = bp;
        MovePt(x, y);
        return TRUE;
        }
      }
    if (bp->m & BP_P_EDITABLE) {
      if (NearPt(x, y, &bp->p)) {
        ed_state = ED_POINT;
        actpt = bp;
        MovePt(x, y);
        return TRUE;
        }
      }
    }
  return FALSE;
  }


BOOL SoftEditObj::OnMouseMove(WPARAM wP, int x, int y, int Seite)
  {
  DBWIN_ASSERT(ed_state != ED_NOTHING);
  MovePt(x, y);
  return TRUE;
  }


BOOL SoftEditObj::OnLButtonUp(WPARAM wP, int x, int y, int Seite)
  {
  DBWIN_ASSERT(ed_state != ED_NOTHING);
  MovePt(x, y);
  if (clear_old) {
    DrawMove(Seite);
    clear_old = FALSE;
    }
  DoMove(Seite);
  ed_state = ED_NOTHING;
  actpt = NULL;
  return TRUE;
  }


void SoftEditObj::Load()
  {
  LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)(m.ReadData(Par()->hd.ObjRec, Par()->hd.ObjId));
  DBWIN_ASSERT((lpobj == NULL) || (*lpobj == NULL));
  Update();
  }


void SoftEditObj::Update()
  {
  if (Initialized) {
    if (clear_old) {
      DrawMove(m.ActSide());
      clear_old = FALSE;
      }
    cs->Free();
    }
  ptCount = m.GetConstInt (Par()->rPtCount);
  dispfact = m.GetConstFloat (Par()->rdispfact);
  color = m.GetConstLong (Par()->rcolor);
  MoveColor = m.GetConstLong (Par()->rMoveColor);
  tr2 FAR *sc = (tr2 FAR *)(m.ReadData(Par()->scR, Par()->scI));

  // Der Erste Stuetzpunkt wird auch gleich schon berechnet. Wenn dieser
  // nicht existiert, wird dies gleich behandelt wie eine fehlende 
  // Skalieruns - Matrix. Sollte dieser aber existieren, dann muss
  // alles restliche ebenfalls existieren
  fpt FAR *p;
  p = (fpt FAR *)(m.ReadData(Par()->fp[1].p.R, Par()->fp[1].p.I));
  if ((sc != NULL) && (p != NULL) && (p->x < 1.0E9)) {
    lmemcpy(&wtos, sc, sizeof(ftr2));
    stow = wtos;
    InvSc2d((tr2 FAR *)&stow);
    DBWIN_ASSERT(ScriptParam->par_Size >= sizeof(DefSoftEdit_param));
    WORD numbps = ScriptParam->par_Size - sizeof(DefSoftEdit_param);
    DBWIN_ASSERT((numbps % (6 * sizeof(Referenz))) == 0);
    numbps /= (6 * sizeof(Referenz));
    float wp, wn, lp, ln;
    float FAR *dec;
    // erster Stuetzpunkt
    DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
    dec = (float FAR *)(m.ReadData(Par()->fp[2].w.R, Par()->fp[2].w.I));
    if ((dec == NULL) || (*dec > 1.0E9)) {
      wn = ln = float(0.0);
      }
    else {
      wn = *dec;
      dec = (float FAR *)(m.ReadData(Par()->fp[3].l.R, Par()->fp[3].l.I));
      if ((dec == NULL) || (*dec > 1.0E9))
        ln = float(0.0);
      else
        ln = *dec;
      }
    cs->AddPt(m.GetConstLong (Par()->fp[0].rm), p, float(0.0), wn, float(0.0), ln);
    // Stuetzpunkte in der Mitte
    for (WORD i = 0; i < numbps; i++) {
      dec = (float FAR *)(m.ReadData(Par()->fp[i*6+5].w.R, Par()->fp[i*6+5].w.I));
      if ((dec == NULL) || (*dec > 1.0E9)) {
        wp = lp = float(0.0);
        }
      else {
        wp = *dec;
        dec = (float FAR *)(m.ReadData(Par()->fp[i*6+4].l.R, Par()->fp[i*6+4].l.I));
        if ((dec == NULL) || (*dec > 1.0E9))
          lp = float(0.0);
        else
          lp = *dec;
        }
      p = (fpt FAR *)(m.ReadData(Par()->fp[i*6+7].p.R, Par()->fp[i*6+7].p.I));
      DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
      dec = (float FAR *)(m.ReadData(Par()->fp[i*6+8].w.R, Par()->fp[i*6+8].w.I));
      if ((dec == NULL) || (*dec > 1.0E9)) {
        wn = ln = float(0.0);
        }
      else {
        wn = *dec;
        dec = (float FAR *)(m.ReadData(Par()->fp[i*6+9].l.R, Par()->fp[i*6+9].l.I));
        if ((dec == NULL) || (*dec > 1.0E9))
          ln = float(0.0);
        else
          ln = *dec;
        }
      cs->AddPt(m.GetConstLong(Par()->fp[i*6+6].rm), p, wp, wn, lp, ln);
      }
    // letzter Stuetzpunkt
    dec = (float FAR *)(m.ReadData(Par()->fp[i*6+5].w.R, Par()->fp[i*6+5].w.I));
    if ((dec == NULL) || (*dec > 1.0E9)) {
      wp = lp = float(0.0);
      }
    else {
      wp = *dec;
      dec = (float FAR *)(m.ReadData(Par()->fp[i*6+4].l.R, Par()->fp[i*6+4].l.I));
      if ((dec == NULL) || (*dec > 1.0E9))
        lp = float(0.0);
      else
        lp = *dec;
      }
    p = (fpt FAR *)(m.ReadData(Par()->fp[i*6+7].p.R, Par()->fp[i*6+7].p.I));
    DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
    cs->AddPt(m.GetConstLong (Par()->fp[i*6+6].rm), p, wp, float(0.0), lp, float(0.0));
    // jetzt noch Kontur berechnen und in die Datenbank schreiben
    cs->CalcAllDpDn();
    fpt FAR *hcnt = (fpt FAR *)mymalloc(ptCount * sizeof(fpt));
    cs->CalcCont(hcnt, ptCount);
    m.WriteData(Par()->cntR, Par()->cntI, hcnt, ptCount * sizeof(fpt), 0);
    myfree(hcnt);
    Initialized = TRUE;
    }
  else {
    m.DelData(Par()->cntR, Par()->cntI, 0, 0);
    Initialized = FALSE;
    }
  }


void SoftEditObj::SetConnection()
  {
  m.SetConnection (Par()->scR, Par()->scI, Offset());
  WORD numfree = ScriptParam->par_Size - sizeof(DefSoftEdit_param);
  numfree = (numfree + sizeof(Par()->fp)) / sizeof(Referenz);
  for (WORD i = 0; i < numfree; i++)
    if ((i % 6) != 0)  // keine Connection fuer Modus
      m.SetConnection(Par()->fp[i].p.R, Par()->fp[i].p.I, Offset());
  }


void SoftEditObj::Reset(BOOL Clear)
  {
  if (Initialized) {
    if (clear_old) {
      DrawMove(m.ActSide());
      clear_old = FALSE;
      }
    }
  m.ClearConnection (Par()->scR, Par()->scI, Offset());
  WORD numfree = ScriptParam->par_Size - sizeof(DefSoftEdit_param);
  numfree = (numfree + sizeof(Par()->fp)) / sizeof(Referenz);
  for (WORD i = 0; i < numfree; i++)
    if ((i % 6) != 0)  // keine Connection fuer Modus
      m.ClearConnection(Par()->fp[i].p.R, Par()->fp[i].p.I, Offset());
  }

