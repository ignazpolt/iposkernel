//////////////////////////////////////////////
//  Definitionen fuer Optimierungsfunktion  //
//////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/opti.cpv   1.6   11 Nov 1997 10:22:10   Martin  $
// $Log:   P:/marille/clinicum/rev/opti.cpv  $
// 
//    Rev 1.6   11 Nov 1997 10:22:10   Martin
// 4 Jahre alten Fehler korrigiert
// 
//    Rev 1.5   18 Mar 1997 18:47:38   Martin
// GetGlobalMem -> GetGlobMem
// 
//    Rev 1.4   03 Jul 1996 15:40:52   GERHOLD
// int FAR *  =>  DBINT FAR *
// 
//    Rev 1.3   02 Feb 1996 10:35:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:20:30   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Mar 1995 12:05:30   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 17:05:20   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   17 May 1994 10:56:24   MARTIN
// MultiDivideCont
// 
//    Rev 1.4   13 Apr 1994 20:54:24   MARTIN
// multidividecont
// 
//    Rev 1.3   07 Mar 1994 20:35:54   MARTIN
// Abbruch der Optimierung, wenn Fehler nicht berechenbar
// 
//    Rev 1.2   12 Jan 1994 11:10:44   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.1   21 May 1993 17:17:42   MARTIN
// Fehlerkorrektur -> erste funktionierende Version
// 
//    Rev 1.0   18 May 1993 17:42:30   MARTIN
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
//#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 22
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

#include "dds.h"
#include "opti.hpp"
#include "cutcont.hpp"


inline LPVOID mymalloc(size_t size)
  {
  return GetGlobMem(size);
  };


inline void myfree(LPVOID obj)
  {
  FreeGlobMem(obj);
  };


BOOL uOptimize(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uOptimize_param FAR *par = (uOptimize_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // zuerst Variablen initialisieren
    c->ExCuteProc(par->InitProc, EM_LOAD);
    c->ExCuteProc(par->InitProc, EM_RESET);
    // erstmalige Berechnung des Fehlers
    c->ExCuteProc(par->ErrorProc, EM_LOAD);
    c->ExCuteProc(par->ErrorProc, EM_RESET);
    float FAR *val = (float FAR *)c->ReadData(par->ErrorR, par->ErrorI);
    DBWIN_ASSERT((val != NULL) && (*val < 1.0E9));
    if (val != NULL) {
      float olderror = *val;
      // jetzt Optimierung durchfuehren
      // Variablen laden in interne Struktur
      LPOPTVAR varhead = NULL;
      var FAR *vars = (var FAR *)(par + 1);
      DBWIN_ASSERT (c->IsConst (par->numvars));
      DBINT numvars = *((DBINT FAR *) c->ReadlData (par->numvars));
      for (int i = 0; i < numvars; i++) {
        LPOPTVAR newvar = (LPOPTVAR)mymalloc(sizeof(optvar));
        newvar->v = vars[i];
        val = (float FAR *)c->ReadData(vars[i].R, vars[i].I);
        DBWIN_ASSERT((val != NULL) && (*val < 1.0E9));
        newvar->value = *val;
        DBWIN_ASSERT (c->IsConst (vars[i].maxstep));
        newvar->laststep = *((float FAR *) c->ReadlData (vars[i].maxstep)); // zu Beginn groesste Schrittweite
        newvar->next = varhead;
        varhead = newvar;
        }
      BOOL better;
      do {
        better = FALSE;
        for (LPOPTVAR actvar = varhead ; actvar != NULL; actvar = actvar->next) {
          // Iterationsschritt fuer eine Variable durchfuehren
          // zuerst addieren probieren
          DBWIN_ASSERT (c->IsConst (actvar->v.minstep));
          float minstep = *((float FAR *) c->ReadlData (actvar->v.minstep));
          float maxstep = *((float FAR *) c->ReadlData (actvar->v.maxstep));

          float testval = actvar->value + actvar->laststep;
          c->WriteData(actvar->v.R, actvar->v.I, &testval, sizeof(float), Offset);
          c->ExCuteProc(par->ErrorProc, EM_LOAD);
          c->ExCuteProc(par->ErrorProc, EM_RESET);
          val = (float FAR *)c->ReadData(par->ErrorR, par->ErrorI);
          DBWIN_ASSERT((val != NULL) && (*val < 1.0E9));
          float adderror = *val;
          // dann subtrahieren probieren
          testval = actvar->value - actvar->laststep;
          c->WriteData(actvar->v.R, actvar->v.I, &testval, sizeof(float), Offset);
          c->ExCuteProc(par->ErrorProc, EM_LOAD);
          c->ExCuteProc(par->ErrorProc, EM_RESET);
          val = (float FAR *)c->ReadData(par->ErrorR, par->ErrorI);
          DBWIN_ASSERT((val != NULL) && (*val < 1.0E9));
          float suberror = *val;
          if (suberror < adderror) {
            if (suberror < olderror) {
              // yeah !!!! (ein Schritt in die richtige Richtung)
              olderror = suberror;
              actvar->value -= actvar->laststep;
              actvar->laststep *= (float)2.0;
              if (actvar->laststep > maxstep)
                actvar->laststep = maxstep;
              better = TRUE;
              }
            else {
              actvar->laststep /= (float)2.0;
              if (actvar->laststep < minstep)
                actvar->laststep = minstep;
              else
                better = TRUE;  // auf jeden Fall noch einmal mit kleinerer
              }                 // Schrittweite probieren
            }
          else {
            if (adderror < olderror) {
              // yeah !!!! (ein Schritt in die richtige Richtung)
              olderror = adderror;
              actvar->value += actvar->laststep;
              actvar->laststep *= (float)2.0;
              if (actvar->laststep > maxstep)
                actvar->laststep = maxstep;
              better = TRUE;
              }
            else {
              actvar->laststep /= (float)2.0;
              if (actvar->laststep < minstep)
                actvar->laststep = minstep;
              else
                better = TRUE;  // auf jeden Fall noch einmal mit kleinerer
              }                 // Schrittweite probieren
            }
          // Variable auf jeden Fall richtig in die Datenbank zurueckschreiben
          c->WriteData(actvar->v.R, actvar->v.I, &actvar->value, sizeof(float), Offset);
          }
        } while (better);
      // interne Struktur wieder freigeben
      LPOPTVAR tofree;
      while (varhead != NULL) {
        tofree = varhead;
        varhead = varhead->next;
        myfree(tofree);
        }
      }
    // dann noch Nachbearbeitung starten
    c->ExCuteProc(par->PostProc, EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc(par->PostProc, EM_CLEAR | EM_CHANGETOFALSE);
    }

  if (mode & EM_FIXCONNECTION) {
    DBWIN_ASSERT (c->IsConst (par->numvars));
    DBINT numvars = *((DBINT FAR *) c->ReadlData (par->numvars));
    int num_refs = (par->ParSize - (sizeof(uOptimize_param) + numvars * sizeof(var))) / sizeof(Referenz);
    Referenz FAR *Ref = (Referenz FAR *)(((var FAR *)(par + 1)) + numvars);
    for (int i = 0; i < num_refs; i++)
      c->SetConnection(Ref[i].R, Ref[i].I, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    DBWIN_ASSERT (c->IsConst (par->numvars));
    DBINT numvars = *((DBINT FAR *) c->ReadlData (par->numvars));
    int num_refs = (par->ParSize - (sizeof(uOptimize_param) + numvars * sizeof(var))) / sizeof(Referenz);
    Referenz FAR *Ref = (Referenz FAR *)(((var FAR *)(par + 1)) + numvars);
    for (int i = 0; i < num_refs; i++)
      c->ClearConnection(Ref[i].R, Ref[i].I, Offset);
    }

  return FALSE;
  }


BOOL uContDist(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uContDist_param FAR *par = (uContDist_param FAR *)param;

  DBWIN_ASSERT (c->IsConst (par->num_points));
  DBINT num_points = *((DBINT FAR *) c->ReadlData (par->num_points));
  if (mode & (EM_LOAD | EM_UPDATE)) {
    fpt FAR *cnt1 = (fpt FAR *)c->ReadData(par->cnt1R, par->cnt1I);
    fpt FAR *cnt2 = (fpt FAR *)c->ReadData(par->cnt2R, par->cnt2I);
    int PtCount1, PtCount2;
    cnt1 = get_cont(cnt1, &PtCount1);
    cnt2 = get_cont(cnt2, &PtCount2);
    float dist = float(1.0E10);
    if ((PtCount1 >= 2) && (PtCount2 >= 2)) {
      float FAR *len1 = (float FAR *)mymalloc((PtCount1 - 1) * sizeof(float));
      float len1sum = float(0.0);
      for (int i = 1; i < PtCount1; i++)
        len1sum += (len1[i - 1] = (float)hypot(cnt1[i].x - cnt1[i - 1].x,
                                               cnt1[i].y - cnt1[i - 1].y));
      float len1step = len1sum / (float)num_points;
      float FAR *len2 = (float FAR *)mymalloc((PtCount2 - 1) * sizeof(float));
      float len2sum = float(0.0);
      for (i = 1; i < PtCount2; i++)
        len2sum += (len2[i - 1] = (float)hypot(cnt2[i].x - cnt2[i - 1].x,
                                               cnt2[i].y - cnt2[i - 1].y));
      float len2step = len2sum / (float)num_points;
      if (hypot(cnt1[0].x - cnt2[0].x,
                cnt1[0].y - cnt2[0].y) < 1.0E-3) {
        if (hypot(cnt1[PtCount1 - 1].x - cnt2[PtCount2 - 1].x,
                  cnt1[PtCount1 - 1].y - cnt2[PtCount2 - 1].y) < 1.0E-3) {
          // Anfangspunkt und Endpunkt passen jeweils zusammen
          float actlen1 = len1step, actlen2 = len2step;
          int ind1 = 0, ind2 = 0;
          dist = float(0.0);
          for (int step = 1; step < num_points; step++) {
            while ((ind1 < (PtCount1 - 1)) && (actlen1 > len1[ind1]))
              actlen1 -= len1[ind1++];
            float p1x, p1y;
            if (len1[ind1] < 1.0E-3) {
              p1x = cnt1[ind1].x;
              p1y = cnt1[ind1].y;
              }
            else {
              float fact = actlen1 / len1[ind1];
              p1x = cnt1[ind1].x + (cnt1[ind1 + 1].x - cnt1[ind1].x) * fact;
              p1y = cnt1[ind1].y + (cnt1[ind1 + 1].y - cnt1[ind1].y) * fact;
              }
            while ((ind2 < (PtCount2 - 1)) && (actlen2 > len2[ind2]))
              actlen2 -= len2[ind2++];
            float p2x, p2y;
            if (len2[ind2] < 1.0E-3) {
              p2x = cnt2[ind2].x;
              p2y = cnt2[ind2].y;
              }
            else {
              float fact = actlen2 / len2[ind2];
              p2x = cnt2[ind2].x + (cnt2[ind2 + 1].x - cnt2[ind2].x) * fact;
              p2y = cnt2[ind2].y + (cnt2[ind2 + 1].y - cnt2[ind2].y) * fact;
              }
            p1x -= p2x;
            p1y -= p2y;
            dist += (p1x * p1x) + (p1y * p1y);
            actlen1 += len1step, actlen2 += len2step;
            }
          }
        }
      else if (hypot(cnt1[0].x - cnt2[PtCount2 - 1].x,
                     cnt1[0].y - cnt2[PtCount2 - 1].y) < 1.0E-3) {
        if (hypot(cnt1[PtCount1 - 1].x - cnt2[0].x,
                  cnt1[PtCount1 - 1].y - cnt2[0].y) < 1.0E-3) {
          // Anfangspunkt passt mit Endpunkt zusammen und umgekehrt
          float actlen1 = len1step, actlen2 = len2step;
          int ind1 = 0, ind2 = PtCount2 - 2;
          dist = float(0.0);
          for (int step = 1; step < num_points; step++) {
            while ((ind1 < (PtCount1 - 1)) && (actlen1 > len1[ind1]))
              actlen1 -= len1[ind1++];
            float p1x, p1y;
            if (len1[ind1] < 1.0E-3) {
              p1x = cnt1[ind1].x;
              p1y = cnt1[ind1].y;
              }
            else {
              float fact = actlen1 / len1[ind1];
              p1x = cnt1[ind1].x + (cnt1[ind1 + 1].x - cnt1[ind1].x) * fact;
              p1y = cnt1[ind1].y + (cnt1[ind1 + 1].y - cnt1[ind1].y) * fact;
              }
            while ((ind2 > 0) && (actlen2 > len2[ind2]))
              actlen2 -= len2[ind2--];
            float p2x, p2y;
            if (len2[ind2] < 1.0E-3) {
              p2x = cnt2[ind2].x;
              p2y = cnt2[ind2].y;
              }
            else {
              float fact = actlen2 / len2[ind2];
              p2x = cnt2[ind2 + 1].x + (cnt2[ind2].x - cnt2[ind2 + 1].x) * fact;
              p2y = cnt2[ind2 + 1].y + (cnt2[ind2].y - cnt2[ind2 + 1].y) * fact;
              }
            p1x -= p2x;
            p1y -= p2y;
            dist += (p1x * p1x) + (p1y * p1y);
            actlen1 += len1step, actlen2 += len2step;
            }
          }
        }
      myfree(len1);
      myfree(len2);
      }
    if (dist > 1.0E9)
      c->DelData(par->distR, par->distI, Offset);
    else
      c->WriteData(par->distR, par->distI, &dist, sizeof(float), Offset);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->cnt1R, par->cnt1I, Offset);
    c->SetConnection(par->cnt2R, par->cnt2I, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->cnt1R, par->cnt1I, Offset);
    c->ClearConnection(par->cnt2R, par->cnt2I, Offset);
    }

  return FALSE;
  }


BOOL uMultiDivideCont(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uMultiDivideCont_param FAR *par = (uMultiDivideCont_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    int state = 0;
    int num_pars = ((par->ParSize - sizeof(uMultiDivideCont_param)) /
                   sizeof(par->pts[0])) + 1;
    fpt FAR *cnt = (fpt FAR *)c->ReadlData(par->cnt);
    int PtCount;
    cnt = get_cont(cnt, &PtCount);
    fpt FAR *begpt = (fpt FAR *)c->ReadlData(par->begpt);
    if ((PtCount >= 2) && (begpt != NULL) && (begpt->x < 1.0E9)) {
      float FAR *len = (float FAR *)mymalloc((PtCount - 1) * sizeof(float));
      float lensum = float(0.0);
      for (int i = 1; i < PtCount; i++)
        lensum += (len[i - 1] = (float)hypot(cnt[i].x - cnt[i - 1].x,
                                             cnt[i].y - cnt[i - 1].y));
      float lenstep = lensum / (float)(num_pars + 1);
      if (hypot(cnt[0].x - begpt->x,
                cnt[0].y - begpt->y) < 1.0E-3) {
        state = 1;
        }
      else if (hypot(cnt[PtCount - 1].x - begpt->x,
                     cnt[PtCount - 1].y - begpt->y) < 1.0E-3) {
        state = -1;
        }
      if (state) {
        float actlen = lenstep;
        int ind = 0;
        for (int step = 0; step < num_pars; step++) {
          while ((ind < (PtCount - 1)) && (actlen > len[ind]))
            actlen -= len[ind++];
          fpt p;
          if (len[ind] < 1.0E-3) {
            p.x = cnt[ind].x;
            p.y = cnt[ind].y;
            }
          else {
            float fact = actlen / len[ind];
            DBWIN_ASSERT (c->IsConst (par->mode));
            DBINT parMode = *((DBINT FAR *) c->ReadlData (par->mode));
            if (parMode != 0L) {
              if (fact < 0.5) {     // naeher bei vorigem Punkt
                p.x = cnt[ind].x;
                p.y = cnt[ind].y;
                }
              else {                // naeher bei naechstem Punkt
                p.x = cnt[ind + 1].x;
                p.y = cnt[ind + 1].y;
                }
              }
            else {
              p.x = cnt[ind].x + (cnt[ind + 1].x - cnt[ind].x) * fact;
              p.y = cnt[ind].y + (cnt[ind + 1].y - cnt[ind].y) * fact;
              }
            }
          c->WritelData(par->pts[(state > 0) ? step : num_pars - step - 1],
                        &p, sizeof(fpt), Offset);
          actlen += lenstep;
          }
        }
      myfree(len);
      }
    if (state == 0) {
      for (int i = 0; i < num_pars; i++)
        c->DellData(par->pts[i], Offset);
      }
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->cnt, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->cnt, Offset);
    }

  return FALSE;
  }

