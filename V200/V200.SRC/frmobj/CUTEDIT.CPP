///////////////////////////////////
//  Definitionen fuer Chirurgie  //
///////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/cutedit.cpv   1.11   05 Oct 1998 11:18:22   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/cutedit.cpv  $
// 
//    Rev 1.11   05 Oct 1998 11:18:22   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   24 Oct 1997 08:38:22   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.9   11 Sep 1997 19:00:32   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.8   18 Aug 1997 18:05:18   Martin
// VTO Formular-faehig
// 
//    Rev 1.7   24 Mar 1996 12:11:14   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.6   02 Feb 1996 10:49:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   24 Aug 1995 00:15:04   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.4   05 Apr 1995 16:49:44   HANNES
// 
//    Rev 1.3   20 Mar 1995 12:13:30   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.2   10 Nov 1994 14:30:40   MARTIN
// top < bottom
// 
//    Rev 1.1   27 Jun 1994 10:56:14   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:45:40   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.6   13 Jan 1994 16:14:28   HANNES
// dfield inc. raus
// 
//    Rev 1.5   12 Jan 1994 11:03:50   HANNES
// Unnoetige Includes eleminiert
// 
//    Rev 1.4   18 Oct 1993 19:55:02   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.3   05 Sep 1993 22:12:24   HANNES
// Aufraeumarbeiten, Verbesserungen
// 
//    Rev 1.2   15 Jun 1993 19:20:48   MARTIN
// hGFmem ausgemistet
// 
//    Rev 1.1   22 Apr 1993 21:01:52   MARTIN
// Erste brauchbare Version
// 
//    Rev 1.0   19 Apr 1993 01:37:38   MARTIN
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 15
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
#include "cutedit.hpp"


extern HINSTANCE hLibInst;

// Funktionen fuer Behandlung von Konturen

DLLExport BOOL _export WINAPI is_cut(fpt FAR *cont)
  {
  return (cont != NULL) &&
         (cont[0].x > 1.0E9) &&
         (GetBlockSize(cont) > sizeof(fpt));
  }


DLLExport fpt FAR * _export WINAPI get_cont(fpt FAR *cont, int FAR *PtCount)
  {
  if (cont != NULL) {
    int siz = GetBlockSize(cont);
    if (cont[0].x < 1.0E9) {
      *PtCount = siz / sizeof(fpt);
      return cont;
      }
    else if (siz > sizeof(fpt)) {
      LPCUTCONT cc = LPCUTCONT(cont);
      *PtCount = cc->num_org_pts;
      int first_point = sizeof(cut_cont) +
                        cc->num_parts * sizeof(cont_part) +
                        cc->num_pieces * sizeof(cont_piece) +
                        cc->num_links * sizeof(cont_link);
      return (fpt FAR *)(LPSTR(cont) + first_point);
      }
    }
  *PtCount = 0;
  return NULL;
  }


// die ganze Scheibe fuer die Speicherverwaltung

inline LPVOID mymalloc(size_t size)
  {
  return GetGlobMem(size);
  };


inline void myfree(LPVOID obj)
  {
  FreeGlobMem(obj);
  };


LPVOID CutCnt::operator new (size_t size)
  {
  return mymalloc(size);
  }


void CutCnt::operator delete(LPVOID ptr)
  {
  myfree(ptr);
  }


CutCnt::CutCnt()
  {
  cphead = cptail = NULL;
  cnts = NULL;
  }


CutCnt::~CutCnt()
  {
  Free();
  }


void CutCnt::Free()
  {
  FreeCp();
  FreeCnts();
  }


void CutCnt::FreeCp()
  {
  LPCUTPOINT cpfree, cp = cphead;
  while (cp != NULL) {
    cpfree = cp;
    cp = cp->next;
    myfree(cpfree);
    }
  cphead = cptail = NULL;
  }


void CutCnt::FreeCnts()
  {
  LPCONTLIST cntfree, cnt = cnts;
  while (cnt != NULL) {
    LPCONTPARTLIST partfree, part = cnt->parthead;
    while (part != NULL) {
      LPCONTPIECELIST piecefree, piece = part->piecehead;
      while (piece != NULL) {
        piecefree = piece;
        piece = piece->next;
        myfree(piecefree);
        }
      partfree = part;
      part = part->next;
      myfree(partfree);
      }
    LPCONTLINKLIST linkfree, link = cnt->linkhead;
    while (link != NULL) {
      linkfree = link;
      link = link->next;
      myfree(linkfree);
      }
    LPCONTPTLIST ptfree, pt = cnt->pthead;
    while (pt != NULL) {
      ptfree = pt;
      pt = pt->next;
      myfree(ptfree);
      }
    cntfree = cnt;
    cnt = cnt->next;
    myfree(cntfree);
    }
  cnts = NULL;
  }


fpt CutCnt::GetPrevPt(fpt cp, LPCONTPARTLIST part, LPCONTPIECELIST piece, LPCONTPTLIST pt, BOOL try_next)
  {
  fpt prevpt = pt->pt;
  LPCONTPTLIST oldpt = pt;
  while (PtsEqual(&cp, &prevpt)) {
    if (pt != piece->pt_from) {
      pt = pt->prev;
      prevpt = pt->pt;
      }
    else if (piece->prev != NULL) {
      if (PtsEqual(&piece->prev->pt_to->pt, &piece->pt_from->pt)) {
        piece = piece->prev;
        pt = piece->pt_to;
        prevpt = pt->pt;
        }
      else {
        if (try_next) {
          prevpt = GetNextPt(cp, part, piece, pt, FALSE);
          prevpt.x = cp.x - (prevpt.x - cp.x);
          prevpt.y = cp.y - (prevpt.y - cp.y);
          }
        else {
          // jetzt reichts mir aber, einfach irgendwas nehmen
          prevpt.x -= (float)1.0;
          }
        break;
        }
      }
    else if (PtsEqual(&part->piecetail->pt_to->pt, &piece->pt_from->pt)) {
      piece = part->piecetail;
      pt = piece->pt_to;
      prevpt = pt->pt;
      }
    else {
      if (try_next) {
        prevpt = GetNextPt(cp, part, piece, pt, FALSE);
        prevpt.x = cp.x - (prevpt.x - cp.x);
        prevpt.y = cp.y - (prevpt.y - cp.y);
        }
      else {
        // jetzt reichts mir aber, einfach irgendwas nehmen
        prevpt.x -= (float)1.0;
        }
      break;
      }
    if (pt == oldpt) {  // einmal im Kreis gegangen
      prevpt.x -= (float)1.0;  // irgendwas nehmen
      break;
      }
    }
  return prevpt;
  }


fpt CutCnt::GetNextPt(fpt cp, LPCONTPARTLIST part, LPCONTPIECELIST piece, LPCONTPTLIST pt, BOOL try_prev)
  {
  pt = pt->next;
  fpt nextpt = pt->pt;
  LPCONTPTLIST oldpt = pt;
  while (PtsEqual(&cp, &nextpt)) {
    if (pt != piece->pt_to) {
      pt = pt->next;
      nextpt = pt->pt;
      }
    else if (piece->next != NULL) {
      if (PtsEqual(&piece->next->pt_from->pt, &piece->pt_to->pt)) {
        piece = piece->next;
        pt = piece->pt_from;
        nextpt = pt->pt;
        }
      else {
        if (try_prev) {
          nextpt = GetPrevPt(cp, part, piece, pt, FALSE);
          nextpt.x = cp.x - (nextpt.x - cp.x);
          nextpt.y = cp.y - (nextpt.y - cp.y);
          }
        else {
          // jetzt reichts mir aber, einfach irgendwas nehmen
          nextpt.x -= (float)1.0;
          }
        break;
        }
      }
    else if (PtsEqual(&part->piecehead->pt_from->pt, &piece->pt_to->pt)) {
      piece = part->piecehead;
      pt = piece->pt_from;
      nextpt = pt->pt;
      }
    else {
      if (try_prev) {
        nextpt = GetPrevPt(cp, part, piece, pt, FALSE);
        nextpt.x = cp.x - (nextpt.x - cp.x);
        nextpt.y = cp.y - (nextpt.y - cp.y);
        }
      else {
        // jetzt reichts mir aber, einfach irgendwas nehmen
        nextpt.x -= (float)1.0;
        }
      break;
      }
    if (pt == oldpt) {  // einmal im Kreis gegangen
      nextpt.x -= (float)1.0;  // irgendwas nehmen
      break;
      }
    }
  return nextpt;
  }


void CutCnt::GetSCos(double FAR *dres, double dx, double dy)
  {
  // 360 Grad ergibt 0.0 , 0 Grad ergibt 4.0 
  double l = hypot (dx,dy);
  if (l > 1.0E-4) {
    double res = dx / l;
    if (dy < 0.0) 
      res = 1.0 - res;
    else
      res += 3.0 ;
    *dres = res;
    }
  else *dres = 0.0 ;
  }


short CutCnt::CalcBoneSide(fpt cntA, fpt cntB, fpt cntC, fpt cpD)
  {
  double BA, BC, BD;
  GetSCos(&BA,cntA.x - cntB.x, cntA.y - cntB.y);
  GetSCos(&BC,cntC.x - cntB.x, cntC.y - cntB.y);
  GetSCos(&BD,cpD.x - cntB.x, cpD.y - cntB.y);
  if (BA > BC) {
    return ((BD < BA) && (BD > BC)) ? BS_CC_RIGHT : BS_CC_LEFT;
    }
  else {
    return ((BD > BA) && (BD < BC)) ? BS_CC_LEFT : BS_CC_RIGHT;
    }
  }


void CutCnt::GetNearestContPt(float FAR *res, fpt FAR *p, short one_part)
  {
  fpt cntpt;
  cntpt.x = float(1.0E10);
  float mindist = float(1.0E10);
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next) {
      if ((one_part >= 0) && (one_part != part->part_num)) continue;
      for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
        for (LPCONTPTLIST pt = piece->pt_from; (pt != NULL) && (pt != piece->pt_to); pt = pt->next) {
          DBWIN_ASSERT(pt->next != NULL);
          // Konturpunkt selbst ueberpruefen
          fpt A = pt->pt;
          fpt B = pt->next->pt;
          fpt C = *p;
          float cx = C.x - A.x;
          float cy = C.y - A.y;
          float dist = cx * cx + cy * cy;
          if (dist < mindist) {
            mindist = dist;
            cntpt = A;
            }
          // Linie ueberpruefen
          float ax = B.x - A.x;
          float ay = B.y - A.y;
          float bx = C.x - B.x;
          float by = C.y - B.y;
          if (((ax * cx + ay * cy) >= 0.0) &&
              ((ax * bx + ay * by) <= 0.0)) {
            float help = ax * ax + ay * ay;
            if (help > 1.0E-6) {
              help = (ax * cy - ay * cx) / help;
              cx = ay * help;
              cy = -ax * help;
              dist = cx * cx + cy * cy;
              if (dist < mindist) {
                mindist = dist;
                cntpt.x = C.x + cx;
                cntpt.y = C.y + cy;
                }
              }
            }
          }
        DBWIN_ASSERT(pt != NULL);
        // jetzt noch Endpunkt des Konturstueckes ueberpruefen
        float dx = p->x - pt->pt.x;
        float dy = p->y - pt->pt.y;
        float dist = dx * dx + dy * dy;
        if (dist < mindist) {
          mindist = dist;
          cntpt = pt->pt;
          }
        } // for piece
      } // for part
    } // for cnt
  *p = cntpt;
  *res = (float)sqrt(mindist);
  }


void CutCnt::GetCntPts(LPCONTLIST cnt, fpt FAR *pts, int PtCount)
  {
  LPCONTPTLIST newpt;
  cnt->pthead = cnt->pttail = NULL;
  for (int i = 0; i < PtCount; i++) {
    newpt = (LPCONTPTLIST)mymalloc(sizeof(cont_pt_list));
    newpt->prev = cnt->pttail;
    newpt->next = NULL;
    newpt->pt = pts[i];
    newpt->ind = i;
    if (cnt->pthead == NULL)
      cnt->pthead = newpt;
    else
      cnt->pttail->next = newpt;
    cnt->pttail = newpt;
    }
//  cnt->ptindvalid = TRUE;
  }


void CutCnt::GetCntPP(LPCONTLIST cnt, LPCONTPART cp, int np)
  {
  LPCONTPARTLIST newpart;
  cnt->parthead = cnt->parttail = NULL;
  for (int i = 0; i < np; i++) {
    newpart = (LPCONTPARTLIST)mymalloc(sizeof(cont_part_list));
//    newpart->prev = cnt->parttail;
    newpart->next = NULL;
    newpart->part_num = cp->part_num;
    newpart->bone_side = cp->bone_side;
    int num_pieces = cp->num_pieces;
    cp++;
    newpart->piecehead = newpart->piecetail = NULL;
    // Stuecke einlesen
    LPCONTPIECE piece = (LPCONTPIECE)cp;
    LPCONTPIECELIST newpiece;
    for (int j = 0; j < num_pieces; j++) {
      newpiece = (LPCONTPIECELIST)mymalloc(sizeof(cont_piece_list));
      newpiece->prev = newpart->piecetail;
      newpiece->next = NULL;
      LPCONTPTLIST pt = cnt->pthead;
      for (int k = 0; (pt != NULL) && (k < piece->ptind_from); k++)
        pt = pt->next;
      DBWIN_ASSERT((pt != NULL) && (pt->ind == k));
      newpiece->pt_from = pt;
      for ( ; (pt != NULL) && (k < piece->ptind_to); k++)
        pt = pt->next;
      DBWIN_ASSERT((pt != NULL) && (pt->ind == k));
      newpiece->pt_to = pt;
      if (newpart->piecehead == NULL)
        newpart->piecehead = newpiece;
      else
        newpart->piecetail->next = newpiece;
      newpart->piecetail = newpiece;
      piece++;
      }
    cp = (LPCONTPART)piece;
    if (cnt->parthead == NULL)
      cnt->parthead = newpart;
    else
      cnt->parttail->next = newpart;
    cnt->parttail = newpart;
    }
  }


void CutCnt::GetCntLinks(LPCONTLIST cnt, LPCONTLINK cl, int nl)
  {
  LPCONTLINKLIST newlink;
  cnt->linkhead = cnt->linktail = NULL;
  for (int i = 0; i < nl; i++) {
    newlink = (LPCONTLINKLIST)mymalloc(sizeof(cont_link_list));
    newlink->next = NULL;
    newlink->part_from = cl[i].part_from;
    newlink->part_to = cl[i].part_to;
    LPCONTPTLIST actpt = cnt->pthead;
    for (int j = 0; j < cl[i].ptind_from; j++)
      actpt = actpt->next;
    newlink->pt_from = actpt;
    DBWIN_ASSERT(actpt->ind == cl[i].ptind_from);
    actpt = cnt->pthead;
    for (j = 0; j < cl[i].ptind_to; j++)
      actpt = actpt->next;
    newlink->pt_to = actpt;
    DBWIN_ASSERT(actpt->ind == cl[i].ptind_to);
    if (cnt->linkhead == NULL)
      cnt->linkhead = newlink;
    else
      cnt->linktail->next = newlink;
    cnt->linktail = newlink;
    }
  }


LPCONTLIST CutCnt::UnpackCnt(fpt FAR *cnt)
  {
  LPCONTLIST newcnt = NULL;
  if (is_cut(cnt)) {
    LPCUTCONT cc = LPCUTCONT(cnt);
    LPCONTPART cp = LPCONTPART(cc + 1);
    LPCONTLINK cl = LPCONTLINK(LPSTR(cp + cc->num_parts) +
                               (cc->num_pieces * sizeof(cont_piece)));
    fpt FAR *pts = (fpt FAR *)(cl + cc->num_links);
    newcnt = (LPCONTLIST)mymalloc(sizeof(contlist));
    newcnt->next = NULL;
    newcnt->num_org_pts = cc->num_org_pts;
    GetCntPts(newcnt, pts, cc->num_pts);
    GetCntPP(newcnt, cp, cc->num_parts);
    GetCntLinks(newcnt, cl, cc->num_links);
    }
  else {
    int PtCount;
    fpt FAR *pts = get_cont(cnt, &PtCount);
    if (PtCount > 0) {
      newcnt = (LPCONTLIST)mymalloc(sizeof(contlist));
      newcnt->next = NULL;
      newcnt->num_org_pts = PtCount;
      GetCntPts(newcnt, pts, PtCount);
      newcnt->linkhead = newcnt->linktail = NULL;
      LPCONTPARTLIST newpart = (LPCONTPARTLIST)mymalloc(sizeof(cont_part_list));
//      newpart->prev = NULL;
      newpart->next = NULL;
      newpart->part_num = 0;
      newpart->bone_side = BS_CC_UNKNOWN;
      newcnt->parthead = newcnt->parttail = newpart;
      LPCONTPIECELIST newpiece = (LPCONTPIECELIST)mymalloc(sizeof(cont_piece_list));
      newpiece->prev = newpiece->next = NULL;
      newpiece->pt_from = newcnt->pthead;
      newpiece->pt_to = newcnt->pttail;
      newpart->piecehead = newpart->piecetail = newpiece;
      }
    }
  return newcnt;
  }


void CutCnt::CalcPtInds(LPCONTLIST cnt)
  {
  int i = 0;
  for (LPCONTPTLIST pt = cnt->pthead; pt != NULL; pt = pt->next)
    pt->ind = i++;
//  cnt->ptindvalid = TRUE;
  }


int CutCnt::CntSize(LPCONTLIST cnt)
  {
  int size = sizeof(cut_cont);
  int nparts = 0, npieces = 0;
  for (LPCONTPARTLIST cp = cnt->parthead; cp != NULL; cp = cp->next) {
    nparts++;
    for (LPCONTPIECELIST pp = cp->piecehead; pp != NULL; pp = pp->next)
      npieces++;
    }
  size += nparts * sizeof(cont_part) + npieces * sizeof(cont_piece);
  int n = 0;
  for (LPCONTLINKLIST cl = cnt->linkhead; cl != NULL; cl = cl->next)
    n++;
  size += n * sizeof(cont_link);
//  if (!cnt->ptindvalid)
//    CalcPtInds(cnt);
  size += (cnt->pttail->ind + 1) * sizeof(fpt);
  return size;
  }


void CutCnt::PackCnt(fpt FAR *dcnt, LPCONTLIST scnt)
  {
//  if (!scnt->ptindvalid)
//    CalcPtInds(scnt);
  LPCUTCONT cc = LPCUTCONT(dcnt);
  cc->invalid.x = float(1.0E10);
  cc->num_org_pts = scnt->num_org_pts;
  LPCONTPART dcp = LPCONTPART(cc + 1);
  int nparts = 0, npieces = 0;
  for (LPCONTPARTLIST scp = scnt->parthead; scp != NULL; scp = scp->next) {
    nparts++;
    dcp->part_num = scp->part_num;
    dcp->bone_side = scp->bone_side;
    dcp->num_pieces = 0;
    LPCONTPIECE dpp = LPCONTPIECE(dcp + 1);
    for (LPCONTPIECELIST spp = scp->piecehead; spp != NULL; spp = spp->next) {
      dpp->ptind_from = spp->pt_from->ind;
      dpp->ptind_to = spp->pt_to->ind;
      dpp++;
      dcp->num_pieces++;
      npieces++;
      }
    dcp = (LPCONTPART)dpp;
    }
  cc->num_parts = nparts;
  cc->num_pieces = npieces;
  LPCONTLINK dcl = LPCONTLINK(dcp);
  int n = 0;
  for (LPCONTLINKLIST scl = scnt->linkhead; scl != NULL; scl = scl->next) {
    n++;
    dcl->part_from = scl->part_from;
    dcl->part_to = scl->part_to;
    dcl->ptind_from = scl->pt_from->ind;
    dcl->ptind_to = scl->pt_to->ind;
    dcl++;
    }
  cc->num_links = n;
  fpt FAR *dpts = (fpt FAR *)(dcl);
  for (LPCONTPTLIST spt = scnt->pthead; spt != NULL; spt = spt->next)
    *dpts++ = spt->pt;
  cc->num_pts = scnt->pttail->ind + 1;
  DBWIN_ASSERT((int)GetBlockSize(dcnt) == (LPSTR(dpts) - LPSTR(dcnt)));
  }


short CutCnt::GetFreePartNum()
  {
  short maxno = -1;
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next)
    for (LPCONTPARTLIST cp = cnt->parthead; cp != NULL; cp = cp->next)
      if (cp->part_num > maxno)
        maxno = cp->part_num;
  return maxno + 1;
  }


void CutCnt::CleanCutPoints()
  {
  // alle berechneten Schnittpunkte entfernen
  LPCUTPOINT lastcp = NULL, cp = cphead;
  while (cp != NULL) {
    if (cp->type == CT_CUTCALC) {
      if (lastcp == NULL) {
        cphead = cp->next;
        if (cphead != NULL)
          cphead->prev = NULL;
        myfree(cp);
        cp = cphead;
        }
      else {
        lastcp->next = cp->next;
        if (cp->next != NULL)
          cp->next->prev = lastcp;
        myfree(cp);
        cp = lastcp->next;
        }
      }
    else {
      lastcp = cp;
      cp = cp->next;
      }
    }
  }


BOOL CutCnt::CalcCutPoints()
  {
  // im folgenden sind Punkte durch Grossbuchstaben bezeichnet,
  // Vektoren sind durch Grossbuchstabenpaare bezeichnet
  // Beispiel: AB = Vektor von Punkt A nach Punkt B
  // A, B sind die Punkte der aktuellen Konturlinie
  // C, D sind die Punkte der aktuellen Schnittlinie
  // S ist der berechnete Schnittpunkt
  short partnum = -1;
  fpt C, D;
  DBWIN_ASSERT(cphead->type == CT_CUTBEGIN);
  for (LPCUTPOINT cp = cphead; cp != NULL; cp = cp->next) {
    if (cp->type == CT_CUTBEGIN) {
      C = cp->pt;
      continue;
      }
    D = cp->pt;
    float DCx = C.x - D.x, DCy = C.y - D.y;
    for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
      for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next) {
        for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
          // bei der Gelegenheit gleich Intialisierungen durchfuehren
          piece->parted_by[0] = piece->parted_by[1] = NULL;
          piece->ins_after[0] = piece->ins_after[1] = NULL;
          piece->cut_dir[0] = piece->cut_dir[1] = CD_UNKNOWN;
          piece->part_mark = P_UNKNOWN;
          piece->cut_before = piece->cut_after = NULL;
          piece->link_before = piece->link_after = NULL;
          // und nun zurueck zur eigentlichen Aufgabe von CalcCutPoints
          if (piece->pt_from != piece->pt_to) {
            fpt A = piece->pt_from->pt;
            float ACx = C.x - A.x, ACy = C.y - A.y;
            BOOL CDinCAneg = (DCy * ACx - DCx * ACy) < 0.0;
            for (LPCONTPTLIST pt = piece->pt_from->next; pt != piece->pt_to; pt = pt->next) {
              fpt B = pt->pt;
              float BCx = C.x - B.x, BCy = C.y - B.y;
              BOOL CDinCBneg = (DCy * BCx - DCx * BCy) < 0.0;
              if (CDinCAneg != CDinCBneg) {
                float ABx = B.x - A.x, ABy = B.y - A.y;
                BOOL ABinACneg = (ABy * ACx - ABx * ACy) < 0.0;
                BOOL ABinADneg = (ABy * (ACx - DCx) - ABx * (ACy - DCy)) < 0.0;
                if (ABinACneg != ABinADneg) {
                  // es existiert sicher ein Schnittpunkt -> berechnen
                  fpt S;
                  float ABexDC = ABx * DCy - ABy * DCx;
                  if (fabs(ABexDC) < 1.0E-3) {
                    if ((fabs(ABx) + fabs(ABy)) < (fabs(DCx) + fabs(DCy)))
                      S = A;
                    else
                      S = C;
                    }
                  else {
                    float DSlen = (ABx * ACy - ABy * ACx) / ABexDC;
                    S.x = C.x - DCx * DSlen;
                    S.y = C.y - DCy * DSlen;
                    }
                  // Schnittpunkt in der Naehe eines eingegebenen Punktes ?
                  if ((!PtsEqual(&S, &C)) && (!PtsEqual(&S, &D))) {
                    // pruefen, ob gueltige Teilnummer
                    if (partnum < 0)   // erster berechneter Schnittpunkt
                      partnum = part->part_num;
                    else if (partnum != part->part_num)
                      return FALSE;  // Schnitt geht ueber verschiedene Teile
                    // Schnittpunkt in die Liste einfuegen
                    LPCUTPOINT newcp = (LPCUTPOINT)mymalloc(sizeof(cutpoint));
                    newcp->pt = S;
                    newcp->type = CT_CUTCALC;
                    newcp->prev = cp->prev;
                    cp->prev->next = newcp;
                    cp->prev = newcp;
                    newcp->next = cp;
                    cp = newcp;
                    D = cp->pt;
                    DCx = C.x - D.x, DCy = C.y - D.y;
                    CDinCBneg = (DCy * BCx - DCx * BCy) < 0.0;
                    }
                  }
                }
              A = B, ACx = BCx, ACy = BCy, CDinCAneg = CDinCBneg;
              }
            } // if piece->pt_from != piece->pt_to
          } // for piece
        } // for part
      } // for cnt
    C = D;
    }
  return TRUE;
  }


int CutCnt::AssignCutPoints()
  {
  for (LPCUTPOINT cp = cphead; cp != NULL; cp = cp->next) {
    cp->part_num = -1;  // noch keinem alten Teil zugeordnet
    cp->part_left = P_UNKNOWN;
    }
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    cnt->parted_by[0] = cnt->parted_by[1] = NULL;
    for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next) {
      int num_cuts = 0;
      for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
        for (LPCONTPTLIST pt = piece->pt_from; pt != piece->pt_to; pt = pt->next) {
          BOOL same_line = FALSE;
          fpt A = pt->pt, B = pt->next->pt;
          float ABx = B.x - A.x, ABy = B.y - A.y;
          float ABlen = (float)hypot(ABx, ABy);
          if (ABlen < 1.0E-3) continue;
          ABx /= ABlen, ABy /= ABlen;   // normieren
          for (LPCUTPOINT cp = cphead; cp != NULL; cp = cp->next) {
            fpt C = cp->pt;
            float ACx = C.x - A.x, ACy = C.y - A.y;
            if (fabs(ABy * ACx - ABx * ACy) < 1.0E-3) {
              float ABinAC = ABx * ACx + ABy * ACy;
              float BAinBC = ABx * (B.x - C.x) + ABy * (B.y - C.y);
              if ((ABinAC >= 0.0) && (BAinBC >= 0.0)) {
                // Schnittpunkt liegt innerhalb der aktuellen Konturlinie
                short new_bone_side;
                int cut_dir = CD_UNKNOWN;
                if (IsCutLineBegin(cp)) {
                  // Anfangspunkt einer Schnittlinie
                  // -> nachsehen, in welche Richtung der Schnitt geht
                  new_bone_side = CalcBoneSide(
                                    GetPrevPt(cp->pt, part, piece, pt),
                                    cp->pt,
                                    GetNextPt(cp->pt, part, piece, pt),
                                    cp->next->pt);
                  if (new_bone_side == BS_CC_LEFT)
                    cut_dir = CD_LEFT;
                  else
                    cut_dir = CD_RIGHT;
                  }
                else if (IsCutLineEnd(cp)) {
                  // Endpunkt einer Schnittlinie
                  // -> nachsehen, in welche Richtung der Schnitt geht
                  new_bone_side = CalcBoneSide(
                                    GetPrevPt(cp->pt, part, piece, pt),
                                    cp->pt,
                                    GetNextPt(cp->pt, part, piece, pt),
                                    cp->prev->pt);
                  if (new_bone_side == BS_CC_LEFT)
                    cut_dir = CD_RIGHT;
                  else
                    cut_dir = CD_LEFT;
                  }
                else {
                  // eingegebener oder berechneter Zwischenpunkt einer
                  // Schnittlinie oder Schnitt besteht nur aus einem Punkt
                  // -> bone_side nicht beruecksichtigen
                  // aber zuerst cut_dir bestimmen
                  if (cp->next != NULL) {
                    new_bone_side = CalcBoneSide(
                                      GetPrevPt(cp->pt, part, piece, pt),
                                      cp->pt,
                                      GetNextPt(cp->pt, part, piece, pt),
                                      cp->next->pt);
                    if (new_bone_side == BS_CC_LEFT)
                      cut_dir = CD_LEFT;
                    else
                      cut_dir = CD_RIGHT;
                    }
                  else {
                    cut_dir = CD_LEFT;  // irgendwas (Schnitt ist nur Punkt)
                    }
                  new_bone_side = BS_CC_UNKNOWN;
                  }
                if (part->bone_side == BS_CC_UNKNOWN) {
                  // bone_side bis jetzt unbekannt ->
                  // ab jetzt Richtung Schnitt
                  part->bone_side = new_bone_side;
                  }
                else {
                  if ((new_bone_side != BS_CC_UNKNOWN) &&
                      (part->bone_side != new_bone_side))
                    // alte und neue bone_side widersprechen sich
                    // -> nicht schneiden
                    // spaeter wird ueberprueft, ob ein Schnittpunkt keinem
                    // Stueck zugeordnet werden kann -> es handelt sich
                    // um genau diesen Fall -> AC_MULTIPART
                    continue;
                  }
                // gueltiger Schnitt gefunden
                if ((cp->part_num != -1) && (cp->part_num != part->part_num))
                  // Schnittpunkt war bereits in anderem Teil gueltig
                  return AC_MULTIPART;
                for (int i = 0; i < 2; i++) {
                  if (piece->parted_by[i] == NULL)
                    break;
                  if (piece->parted_by[i] == cp)
                    // Schnittp. wurde in diesem Stueck schon beruecksichtigt
                    break;
                  }
                if (i < 2) {
                  if (piece->parted_by[i] == NULL) {
                    if (same_line && (i == 1)) {
                      // zweiter Schnitt innerhalb der selben Konturlinie
                      // -> Reihenfolge der beiden Schnitte bestimmen
                      // ([0] = naeherer zu A)
                      fpt D = piece->parted_by[0]->pt;
                      float ADx = D.x - A.x, ADy = D.y - A.y;
                      if ((ACx * ACx + ACy * ACy) <
                          (ADx * ADx + ADy * ADy)) {
                        piece->parted_by[1] = piece->parted_by[0];
                        piece->ins_after[1] = piece->ins_after[0];
                        piece->cut_dir[1] = piece->cut_dir[0];
                        i = 0;
                        }
                      }
                    // Schnittpunkt eintragen
                    cp->part_num = part->part_num;
                    piece->parted_by[i] = cp;
                    piece->ins_after[i] = pt;
                    piece->cut_dir[i] = cut_dir;
                    if (num_cuts >= 2) return AC_TOOMANY;
                    cnt->parted_by[num_cuts++] = cp;
                    same_line = TRUE;
                    }
                  else {
                    // Schnittp. wurde in diesem Stueck schon beruecksichtigt
                    continue;
                    }
                  }
                else {
                  // Stueck ist bereits zweimal geschnitten ->
                  // zuviele Schnitte im selben Teil
                  return AC_TOOMANY;
                  }
                } // if innerhalb Strecke A -> B
              } // if Abstand von Gerade < 1.0E-3
            } // for cp
          } // for pt
        } // for piece
      } // for part
    } // for cnt
  // jetzt noch checken ob alle Schnittpunkte demselben Teil zugeordnet sind
  int common_part_num = -1;
  for (cp = cphead; cp != NULL; cp = cp->next) {
    if (cp->type == CT_CUTMID) continue;  // braucht nicht zugeordnet sein
    if (cp->part_num == -1)
      // Schnitt geht nach 'aussen'
      return AC_NOTBONE;
    if (common_part_num == -1)
      common_part_num = cp->part_num;
    else if (common_part_num != cp->part_num)
      return AC_MULTIPART;
    }
  return AC_CUTOK;
  }


void CutCnt::MarkCutLine(LPCUTPOINT cp, int part_left)
  {
  LPCUTPOINT hcp = cp;
  while (hcp->type != CT_CUTBEGIN) {
    hcp->part_left = part_left;
    hcp = hcp->prev;
    }
  hcp->part_left = part_left;
  hcp = cp->next;
  while ((hcp != NULL) && (hcp->type != CT_CUTBEGIN)) {
    hcp->part_left = part_left;
    hcp = hcp->next;
    }
  }


BOOL CutCnt::DividePieces(short part_num)
  {
  BOOL res = FALSE;
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next) {
      if (part->part_num != part_num) continue;
      for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
        for (int i = 0; (i < 2) && (piece->parted_by[i] != NULL); i++) {
          if (piece->parted_by[i]->part_left != P_UNKNOWN) {
            // Stueck in zwei Stuecke trennen
            LPCONTPIECELIST newpiece = (LPCONTPIECELIST)mymalloc(sizeof(cont_piece_list));
            newpiece->prev = piece;
            newpiece->next = piece->next;
            newpiece->pt_to = piece->pt_to;
            LPCONTPTLIST newpt = (LPCONTPTLIST)mymalloc(sizeof(cont_pt_list));
            LPCONTPTLIST newpt2 = (LPCONTPTLIST)mymalloc(sizeof(cont_pt_list));
            newpt2->pt = newpt->pt = piece->parted_by[i]->pt;
            newpt->prev = piece->ins_after[i];
            newpt->next = newpt2;
            newpt2->prev = newpt;
            newpt2->next = piece->ins_after[i]->next;
            newpt2->next->prev = newpt2;
            newpt->prev->next = newpt;
//            cnt->ptindvalid = FALSE;
            CalcPtInds(cnt);
            if (piece->pt_from->ind < cnt->num_org_pts)
              cnt->num_org_pts += 2;  // zwei Punkte eingefuegt
            piece->pt_to = newpt;
            newpiece->pt_from = newpt2;
            if (i == 0) {
              newpiece->parted_by[0] = piece->parted_by[1];
              if (piece->ins_after[0] == piece->ins_after[1])
                newpiece->ins_after[0] = newpt2;
              else
                newpiece->ins_after[0] = piece->ins_after[1];
              newpiece->cut_dir[0] = piece->cut_dir[1];
              piece->parted_by[1] = NULL;
              piece->ins_after[1] = NULL;
              }
            else {
              newpiece->parted_by[0] = NULL;
              newpiece->ins_after[0] = NULL;
              }
            newpiece->parted_by[1] = NULL;
            newpiece->ins_after[1] = NULL;
            newpiece->part_mark = P_UNKNOWN;
            newpiece->cut_before = newpiece->cut_after = NULL;
            newpiece->link_before = newpiece->link_after = NULL;
            piece->next = newpiece;
            if (newpiece->next == NULL)
              part->piecetail = newpiece;
            else
              newpiece->next->prev = newpiece;
            // jetzt noch Stuecke den beiden neuen Konturteilen zuweisen
            DBWIN_ASSERT(piece->cut_dir[i] != CD_UNKNOWN);
            // im Stueck vermerken, ob es zum alten oder neuen Teil gehoert
            int pprev, pnext;
            if (piece->cut_dir[i] == CD_LEFT) {
              pprev = piece->parted_by[i]->part_left;
              pnext = P_INVERS(pprev);
              }
            else {
              pnext = piece->parted_by[i]->part_left;
              pprev = P_INVERS(pnext);
              }
            for (LPCONTPIECELIST markp = piece; (markp != NULL) && (markp->part_mark == P_UNKNOWN); markp = markp->prev) {
              if ((markp->parted_by[0] != NULL) &&
                  ((i > 0) || (markp != piece))) {
                // Schnittlinie markieren
                MarkCutLine(markp->parted_by[0],
                            (markp->cut_dir[0] == CD_LEFT) ? pnext : pprev);
                break;  // ????
                }
              else {
                // Stueck markieren
                markp->part_mark = pprev;
                }
              }
            for (markp = newpiece; (markp != NULL) && (markp->part_mark == P_UNKNOWN); markp = markp->next) {
              if (markp->parted_by[0] != NULL) {
                // Schnittlinie markieren
                MarkCutLine(markp->parted_by[0],
                            (markp->cut_dir[0] == CD_LEFT) ? pnext : pprev);
                break;  // ????
                }
              else {
                // Stueck markieren
                markp->part_mark = pnext;
                }
              }
            // neuen Link erzeugen
            LPCONTLINKLIST newlink = (LPCONTLINKLIST)mymalloc(sizeof(cont_link_list));
            newlink->next = NULL;
            newlink->pt_from = piece->pt_to;
            newlink->pt_to = newpiece->pt_from;
            piece->link_after = newpiece->link_before = newlink;
            piece->cut_after = newpiece->cut_before = piece->parted_by[i];
            piece->parted_by[i] = NULL;  // Aufteilung durchgefuehrt
            piece->ins_after[i] = NULL;  // -> Eintrag loeschen
            res = TRUE;  // Rueckgabewert: mind. ein Schnitt durchgefuerht
            } // if part_left fuer diesen Teilschnitt bekannt
          } // for i
        } // for piece
      } // for part
    } // for cnt
  return res;
  }


LPCONTPIECELIST CutCnt::CutLineToPieces(LPCONTLIST cnt, LPCUTPOINT cp, BOOL reverse)
  {
  BOOL donext = TRUE, doprev = TRUE, calced = FALSE;
  if (IsCutLineBegin(cp))
    doprev = FALSE;
  else if (IsCutLineEnd(cp))
    donext = FALSE;
  else if (cp->type == CT_CUTBEGIN)
    return NULL;  // einzelner Schnittpunkt
  else
    calced = TRUE;
  // nachsehen, ob noch ein weiterer Schnittpunkt mit dieser Kontur
  // in diesem Teilschnitt vorhanden ist
  BOOL cpfound = FALSE;
  LPCUTPOINT othercp = NULL;
  if (doprev) {
    cpfound = TRUE;
    othercp = cp;
    do {
      othercp = othercp->prev;
      } while ((othercp != NULL) &&
               (othercp != cnt->parted_by[0]) &&
               (othercp != cnt->parted_by[1]) &&
               (cpfound = (othercp->type != CT_CUTBEGIN)));
    if (cpfound)
      donext = FALSE;
    }
  if (donext) {
    cpfound = TRUE;
    othercp = cp;
    do {
      othercp = othercp->next;
      } while ((othercp != NULL) &&
               (othercp != cnt->parted_by[0]) &&
               (othercp != cnt->parted_by[1]) &&
               (cpfound = ((othercp->next != NULL) &&
                           (othercp->next->type != CT_CUTBEGIN))));
    if (cpfound)
      doprev = FALSE;
    }
  if ((!cpfound) && calced)
    return NULL;
  DBWIN_ASSERT((othercp != NULL) && (othercp != cp));
  // jetzt auf jeden Fall Linie erzeugen
  LPCUTPOINT actcp, tocp;
  if (reverse) {
    if ((othercp == cnt->parted_by[0]) || (othercp == cnt->parted_by[1]))
      // anderer Schnittpunkt auf selber Kontur -> erst dort einfuegen
      return NULL;
    tocp = cp;
    actcp = othercp;
    doprev = !doprev;
    donext = !donext;
    }
  else {
    actcp = cp;
    tocp = othercp;
    }
  DBWIN_ASSERT(doprev != donext);  // darf nur in eine Richtung gehen
  int act_ind = cnt->pttail->ind + 1;
  LPCONTPIECELIST piecehead = NULL, piecetail = NULL;
  do {
    LPCONTPIECELIST newpiece = (LPCONTPIECELIST)mymalloc(sizeof(cont_piece_list));
    newpiece->prev = piecetail;
    newpiece->next = NULL;
    LPCONTPTLIST newpt1 = (LPCONTPTLIST)mymalloc(sizeof(cont_pt_list));
    newpt1->prev = cnt->pttail;
    newpt1->next = NULL;
    newpt1->pt = actcp->pt;
    newpt1->ind = act_ind++;
    cnt->pttail->next = newpt1;
    cnt->pttail = newpt1;
    if (doprev)
      actcp = actcp->prev;
    else
      actcp = actcp->next;
    LPCONTPTLIST newpt2 = (LPCONTPTLIST)mymalloc(sizeof(cont_pt_list));
    newpt2->prev = cnt->pttail;
    newpt2->next = NULL;
    newpt2->pt = actcp->pt;
    newpt2->ind = act_ind++;
    cnt->pttail->next = newpt2;
    cnt->pttail = newpt2;
    newpiece->pt_from = newpt1;
    newpiece->pt_to = newpt2;
    if (piecehead == NULL)
      piecehead = newpiece;
    else
      piecetail->next = newpiece;
    piecetail = newpiece;
    } while (actcp != tocp);
  return piecehead;
  }


BOOL CutCnt::DividePart(short part_num, short new_part_num1, short new_part_num2)
  {
  BOOL res = TRUE;
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    for (LPCONTPARTLIST part = cnt->parthead; (part != NULL) && (part->part_num != part_num); part = part->next);
    if (part != NULL) {
      cnt->already_parted = TRUE;
      LPCONTPARTLIST newpart1 = (LPCONTPARTLIST)mymalloc(sizeof(cont_part_list));
      LPCONTPARTLIST newpart2 = (LPCONTPARTLIST)mymalloc(sizeof(cont_part_list));
      newpart1->piecehead = newpart1->piecetail = NULL;
      newpart2->piecehead = newpart2->piecetail = NULL;
      newpart1->part_num = new_part_num1;
      newpart2->part_num = new_part_num2;
      LPCONTPIECELIST piece = part->piecehead;
      while (piece != NULL) {
        LPCONTPIECELIST nextpiece = piece->next;
        if (piece->part_mark != P_UNKNOWN) {
          DBWIN_ASSERT(cnt->already_parted);  // alles oder nichts bekannt
          LPCONTPARTLIST addto = (piece->part_mark == P_OLD) ? newpart1 : newpart2;
          // gegebenenfalls Schnitt anhaengen
          if (piece->cut_before != NULL) {
            piece->link_before->part_to = addto->part_num;
            LPCONTPIECELIST newpiece = CutLineToPieces(cnt, piece->cut_before, TRUE);
            if (newpiece != NULL) {
              if (addto->piecehead == NULL)
                addto->piecehead = newpiece;
              else
                addto->piecetail->next = newpiece;
              newpiece->prev = addto->piecetail;
              while (newpiece->next != NULL)
                newpiece = newpiece->next;
              addto->piecetail = newpiece;
              }
            }
          // altes Stueck anhaengen
          piece->prev = addto->piecetail;
          piece->next = NULL;
          if (addto->piecehead == NULL) {
            addto->piecehead = addto->piecetail = piece;
            }
          else {
            addto->piecetail->next = piece;
            piece->prev = addto->piecetail;
            addto->piecetail = piece;
            }
          // gegebenenfalls Schnitt anhaengen
          if (piece->cut_after != NULL) {
            piece->link_after->part_from = addto->part_num;
            LPCONTPIECELIST newpiece = CutLineToPieces(cnt, piece->cut_after, FALSE);
            if (newpiece != NULL) {
              if (addto->piecehead == NULL)
                addto->piecehead = newpiece;
              else
                addto->piecetail->next = newpiece;
              newpiece->prev = addto->piecetail;
              while (newpiece->next != NULL)
                newpiece = newpiece->next;
              addto->piecetail = newpiece;
              }
            }
          }
        else {
          cnt->already_parted = FALSE;
          res = FALSE;  // mindestens ein Stueck konnte nicht zugeteilt werden
          }
        piece = nextpiece;
        }
      if (cnt->already_parted) {
        if (newpart1->piecehead == NULL)  // leerer Teil
          *newpart1 = *newpart2, newpart2->piecehead = NULL;
        if (newpart1->piecehead != NULL) {
          part->piecehead = newpart1->piecehead;
          part->piecetail = newpart1->piecetail;
          part->part_num = newpart1->part_num;
          }
        myfree(newpart1);
        if (newpart2->piecehead != NULL) {
          newpart2->next = NULL;
          newpart2->bone_side = part->bone_side;
          cnt->parttail->next = newpart2;
          cnt->parttail = newpart2;
          }
        else
          myfree(newpart2);
        }
      else {
        myfree(newpart1);
        myfree(newpart2);
        }
      }
    }
  return res;
  }


fpt CutCnt::CalcPartSchwer(short part_num, LPCONTLIST onecnt)
  {
  fpt schwer;
  schwer.x = schwer.y = float(0.0);
  int anzpts = 0;
  for (LPCONTLIST cnt = (onecnt == NULL) ? cnts : onecnt;
       cnt != NULL;
       (onecnt == NULL) ? (cnt = cnt->next) : (cnt = NULL)) {
    for (LPCONTPARTLIST part = cnt->parthead; (part != NULL) && (part->part_num != part_num); part = part->next);
    if (part != NULL) {
      for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
        for (LPCONTPTLIST pt = piece->pt_from; pt != piece->pt_to; pt = pt->next) {
          schwer.x += pt->pt.x;
          schwer.y += pt->pt.y;
          anzpts++;
          }
        schwer.x += pt->pt.x;   // noch einmal fuer piece->pt_to
        schwer.y += pt->pt.y;
        anzpts++;
        }
      }
    }
  if (anzpts > 0) {
    schwer.x /= (float)anzpts;
    schwer.y /= (float)anzpts;
    }
  return schwer;
  }


void CutCnt::PartRest(short part_num, short new_part_num1, short new_part_num2)
  {
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    if (!cnt->already_parted) {
      short new_part_num = -1;
      fpt S = CalcPartSchwer(part_num, cnt);
      fpt P1 = S, P2 = S;
      float dist1, dist2;
      GetNearestContPt(&dist1, &P1, new_part_num1);
      GetNearestContPt(&dist2, &P2, new_part_num2);
      if (fabs(dist1 - dist2) < 1.0E-3) {
        fpt S1 = CalcPartSchwer(new_part_num1);
        fpt S2 = CalcPartSchwer(new_part_num2);
        S1.x -= P1.x, S1.y -= P1.y;
        S2.x -= P2.x, S2.y -= P2.y;
        float S1len = (float)hypot(S1.x, S1.y);
        float S2len = (float)hypot(S2.x, S2.y);
        if ((S1len > 1.0E-3) && (S2len > 1.0E-3)) {
          S1.x /= S1len, S1.y /= S1len;
          S2.x /= S2len, S2.y /= S2len;
          if ((S1.x * (S.x - P1.x) + S1.y * (S.y - P1.y)) >
              (S2.x * (S.x - P2.x) + S2.y * (S.y - P2.y)))
            new_part_num = new_part_num1;
          else
            new_part_num = new_part_num2;
          }
        }
      if (new_part_num < 0) {
        if (dist1 < dist2)
          new_part_num = new_part_num1;
        else
          new_part_num = new_part_num2;
        }
      for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next)
        if (part->part_num == part_num)
          part->part_num = new_part_num;
      }
    }
  }


void CutCnt::AddLinks()
  {
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next) {
      for (LPCONTPIECELIST piece = part->piecehead; piece != NULL; piece = piece->next) {
        if (piece->link_after != NULL) {
          if (cnt->linkhead == NULL)
            cnt->linkhead = piece->link_after;
          else
            cnt->linktail->next = piece->link_after;
          cnt->linktail = piece->link_after;
          }
        }
      }
    }
  }


void CutCnt::AssignLinks()
  {
  for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next) {
    for (LPCONTLINKLIST link = cnt->linkhead; link != NULL; link = link->next) {
      for (int i = 0; i < 2; i++) {
        int pt_ind = (i == 0) ? link->pt_from->ind : link->pt_to->ind;
        BOOL found = FALSE;
        for (LPCONTPARTLIST part = cnt->parthead; (!found) && (part != NULL); part = part->next) {
          for (LPCONTPIECELIST piece = part->piecehead; (!found) && (piece != NULL); piece = piece->next) {
            if ((pt_ind >= piece->pt_from->ind) && (pt_ind <= piece->pt_to->ind)) {
              if (i == 0)
                link->part_from = part->part_num;
              else
                link->part_to = part->part_num;
              found = TRUE;
              }
            } // for piece
          } // for part
        DBWIN_ASSERT(found);
        } // for i
      } // for link
    } // for cnt
  }


BOOL CutCnt::PartClosed(short part_num)
  {
  return FALSE;
  }


BOOL CutCnt::ApplyCut()
  {
  if (cphead == NULL) return AC_NOCUT;
  if (CalcCutPoints()) {
    int res = AssignCutPoints();
    if (res != AC_CUTOK) return res;
    MarkCutLine(cphead, P_OLD);
    while (DividePieces(cphead->part_num));
    for (LPCUTPOINT cp = cphead; cp != NULL; cp = cp->next)
      if (cp->part_left == P_UNKNOWN)  // muesste jetzt bekannt sein
        return AC_NOTCONN;  // unzusammenhaengende Teilschnitte
    short old_part_num, new_part_num1, new_part_num2;
    old_part_num = cphead->part_num;
    new_part_num1 = GetFreePartNum();
    new_part_num2 = new_part_num1 + 1;
    for (LPCONTLIST cnt = cnts; cnt != NULL; cnt = cnt->next)
      for (LPCONTPARTLIST part = cnt->parthead; part != NULL; part = part->next)
        if (part->part_num == old_part_num)
          part->part_num = new_part_num2;
    old_part_num = new_part_num2;
    new_part_num2 = cphead->part_num;
    if (!DividePart(old_part_num, new_part_num1, new_part_num2)) {
      // restliche Stuecke mit Schwerpunktaufteilung behandeln
      PartRest(old_part_num, new_part_num1, new_part_num2);
      }
    AddLinks();
    AssignLinks();
#ifdef VERWENDET
    if (PartClosed(cntpart))
      if (numcuts < 2)
        return AC_TOOFEW;
    DBWIN_ASSERT(numcuts <= 2);
#endif
    return AC_CUTOK;
    }
  else
    return AC_MULTIPART;
  }

BOOL CutCnt::PtsEqual(fpt FAR *pt1, fpt FAR *pt2)    // sind zwei Punkte gleich ?
  {
#define EPS_QUADR 1.0E-6
  float dx = pt1->x - pt2->x;
  float dy = pt1->y - pt2->y;
  return (dx * dx + dy * dy) < EPS_QUADR;
  }

BOOL CutCnt::IsCutLineBegin(LPCUTPOINT cp)
  {
  return (cp->type == CT_CUTBEGIN) &&
          (cp->next != NULL) && (cp->next->type != CT_CUTBEGIN);
  }

BOOL CutCnt::IsCutLineEnd(LPCUTPOINT cp)
  {
  return (cp->type != CT_CUTBEGIN) &&
          ((cp->next == NULL) || (cp->next->type == CT_CUTBEGIN)) &&
          (cp->prev != NULL);
  }

////////////////////////// Chirurgie - Objekt ///////////////////////////

CutEditObj::CutEditObj(LPVOID p, mdiChild *c) : FrmObject (p, c)
  {
  cc = new CutCnt();
  ed_state = ED_INIT;
  clear_old = FALSE;
  actcp = NULL;
  }


CutEditObj::~CutEditObj()
  {
  delete cc;
  }

#define KASTL 57

void CutEditObj::GetMinMax()
  {
  RECT rcLogRect;
  fpt pt;
  int px, py, xmin, xmax, ymin, ymax;
  if (cc->cphead == NULL) {
    if (cc->cnts != NULL) {
      Sc2d((tr2 FAR *)&wtos, &pt, &cc->cnts->pthead->pt);
      px = m.WorldToLog(pt.x);
      py = m.WorldToLog(pt.y);
      xmin = px, xmax = px, ymin = py, ymax = py;
      }
    else {
      SetRectEmpty (LPRECT (&rcLogRect));
      return ;
      }
    }
  else {
    xmin = ymin = 32000;
    xmax = ymax = -32000;
    }
  for (LPCUTPOINT cp = cc->cphead; cp != NULL; cp = cp->next) {
    Sc2d((tr2 FAR *)&wtos, &pt, &cp->pt);
    px = m.WorldToLog(pt.x);
    py = m.WorldToLog(pt.y);
    if ((px - KASTL) < xmin) xmin = px - KASTL;
    if ((px + KASTL) > xmax) xmax = px + KASTL;
    if ((py - KASTL) < ymin) ymin = py - KASTL;
    if ((py + KASTL) > ymax) ymax = py + KASTL;
    }
  int width = m.HalfPenWidth(color);
  rcLogRect.left   = xmin  - width;
  rcLogRect.right  = xmax  + width;
  rcLogRect.top    = ymin  - width;
  rcLogRect.bottom = ymax  + width;

  SetLogRect (&rcLogRect,ErsteSeite());

  schwerx = (xmin + xmax) / 2;
  schwery = (ymin + ymax) / 2;
  }


void CutEditObj::Paint(PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT(Initialized);
  if (pc->mode == DO_WORK)
    Invalidate(Seite);
  }


void CutEditObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  CutEditObj::PaintTrans(pc, Seite, NULL);
  }


void CutEditObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DBWIN_ASSERT(sc == NULL);
  int pxold, pyold;
  for (LPCUTPOINT cp = cc->cphead; cp != NULL; cp = cp->next) {
    fpt pt;
    Sc2d((tr2 FAR *)&wtos, &pt, &cp->pt);
    int px = m.WorldToLog(pt.x);
    int py = m.WorldToLog(pt.y);
    DrawMark(pc, Seite, px, py);
    if (cp->type != CT_CUTBEGIN)
      DrawLine(pc, Seite, pxold, pyold, px, py);
    pxold = px;
    pyold = py;
    }
  }


void CutEditObj::DrawMark(PaintContext *pc, int Seite, int px, int py)
  {
  *pc << Line (px+KASTL, py-KASTL, px+KASTL, py+KASTL);
  *pc << Line (px+KASTL, py+KASTL, px-KASTL, py+KASTL);
  *pc << Line (px-KASTL, py+KASTL, px-KASTL, py-KASTL);
  *pc << Line (px-KASTL, py-KASTL, px+KASTL, py-KASTL);
  }


void CutEditObj::DrawLine(PaintContext *pc, int Seite, int px1, int py1, int px2, int py2)
  {
  *pc << Line (px1, py1, px2, py2);
  }


BOOL CutEditObj::NearPt(int x, int y, fpt FAR *p)
  {
  fpt pt;
  Sc2d((tr2 FAR *)&wtos, &pt, p);
  int px = m.WorldToLog(pt.x);
  int py = m.WorldToLog(pt.y);
  return (x >= px - KASTL) && (x <= px + KASTL) &&
         (y >= py - KASTL) && (y <= py + KASTL);
  }


BOOL CutEditObj::NearCont(int x, int y, fpt FAR *p)
  {
  p->x = m_LogToWorld(x);
  p->y = m_LogToWorld(y);
  Sc2d((tr2 FAR *)&stow, p, p);
  float dist;
  cc->GetNearestContPt(&dist,p);
  return m.WorldToLog(float (dist * 56.69291339)) <= KASTL;
  }


void CutEditObj::MovePt(int x, int y)
  {
  DBWIN_ASSERT((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV));
  DBWIN_ASSERT(actcp != NULL);
  if (clear_old)
    DrawMove(m.ActSide());
  fpt pt;
  pt.x = m_LogToWorld(x);
  pt.y = m_LogToWorld(y);
  Sc2d((tr2 FAR *)&stow, &pt, &pt);
  if ((actcp->type == CT_CUTBEGIN) || (actcp->type == CT_CUTEND)) {
    float dummy;
    cc->GetNearestContPt(&dummy, &pt);
    }
  actcp->pt = pt;
  DrawMove(m.ActSide());
  clear_old = TRUE;
  }


void CutEditObj::DrawMove(int Seite)
  {
  DBWIN_ASSERT(Initialized);
  DBWIN_ASSERT((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV));
  PaintContext pc;
  GetDocumentContext(&pc, m);
  SetROP2(pc.hDC,R2_XORPEN);
  pc.diPen(MoveColor);
  PaintTrans(&pc, Seite, NULL);
  }


void CutEditObj::DoMove(int Seite)
  {
  DBWIN_ASSERT(Initialized);
  Invalidate(Seite);
  GetMinMax();
  Invalidate(Seite);
  LPRECT rcLogRect = GetLogRect (Seite);
  if (rcLogRect != NULL)
    m.Rescale(rcLogRect);
  }


BOOL CutEditObj::OnLButtonDown(WPARAM wP, int x, int y, int Seite)
  {
  if (wP & MK_LBUTTON) {
    if ((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV)) return FALSE;
    for (LPCUTPOINT cp = cc->cphead; cp != NULL; cp = cp->next) {
      if (NearPt(x, y, &cp->pt)) {
        ed_state = (ed_state == ED_INIT) ? ED_INIMOV : ED_ADDMOV;
        actcp = cp;
        MovePt(x, y);
        return TRUE;
        }
      }
    fpt pt;
    BOOL near_cont = NearCont(x, y, &pt);
    if ((ed_state != ED_INIT) || near_cont) {
      LPCUTPOINT newcp = (LPCUTPOINT)mymalloc(sizeof(cutpoint));
      newcp->prev = cc->cptail;
      newcp->next = NULL;
      if (ed_state == ED_INIT) {
        newcp->type = CT_CUTBEGIN;
        ed_state = ED_ADDMOV;
        }
      else {
        if (near_cont) {
          newcp->type = CT_CUTEND;
          ed_state = ED_INIMOV;
          }
        else {
          newcp->type = CT_CUTMID;
          ed_state = ED_ADDMOV;
          pt.x = m_LogToWorld(x);
          pt.y = m_LogToWorld(y);
          Sc2d((tr2 FAR *)&stow, &pt, &pt);
          }
        }
      newcp->pt = pt;
      if (cc->cphead == NULL)
        cc->cphead = newcp;
      else
        cc->cptail->next = newcp;
      cc->cptail = newcp;
      actcp = newcp;
      MovePt(x, y);
      return TRUE;
      }
    }
  else {
    if (x == 0) {
      // Spezialmodus: Schnitt durchfuehren
      int res = cc->ApplyCut();
      cc->CleanCutPoints();
      if (res == AC_CUTOK) {
        // Jubel
        // Konturen in die Datenbank schreiben
        int numcnts = ((ScriptParam->par_Size - sizeof(DefCutEdit_param)) /
                      sizeof(Par()->CntRef[0])) + 1;
        LPCONTLIST cnt = cc->cnts;
        for (int i = numcnts - 1; i >= 0; i--) {
          DBWIN_ASSERT(cnt != NULL);
          int siz = cc->CntSize(cnt);
          fpt FAR *dcnt = (fpt FAR *)mymalloc(siz);
          cc->PackCnt(dcnt, cnt);
          m.WriteData(Par()->CntRef[i].R, Par()->CntRef[i].I, dcnt, siz, 0);
          myfree(dcnt);
          cnt = cnt->next;
          }
        // Schnitt wieder freigeben
        cc->FreeCp();
        ed_state = ED_INIT;
        actcp = NULL;
        }
      else {
#define CUT_MESSAGES 15000
        char InZeile0  [100];
        char InZeile1 [100];
        LoadString (hLibInst,CUT_MESSAGES,InZeile0,sizeof (InZeile0));
        LoadString (hLibInst,CUT_MESSAGES+res,InZeile1,sizeof (InZeile1));
        MessageBox (GetActiveWindow(), InZeile1, InZeile0,
                    MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
        }
      }
    else if (x == 1) {
      // Spezialmodus: letzten Schnittpunkt rueckgaengig machen
      if ((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV)) return FALSE;
      if (cc->cptail == NULL) return FALSE;
      LPCUTPOINT lastcp = cc->cptail;
      cc->cptail = lastcp->prev;
      if (cc->cptail == NULL) {
        cc->cphead = NULL;
        ed_state = ED_INIT;
        }
      else {
        cc->cptail->next = NULL;
        if (cc->cptail->type == CT_CUTEND)
          ed_state = ED_INIT;
        else
          ed_state = ED_ADD;
        }
      myfree(lastcp);
      actcp = NULL;
      DoMove(Seite);
      }
    else {
      DBWIN_ASSERT(FALSE);
      }
    }
  return FALSE;
  }


BOOL CutEditObj::OnLButtonDblClk(WPARAM wP, int x, int y, int Seite)
  {
  if ((ed_state != ED_ADD) && (ed_state != ED_INIT)) return FALSE;
  if (cc->cptail == NULL) return FALSE;  // noch kein Punkt eingegeben
  if (cc->cptail->type == CT_CUTBEGIN) return FALSE;
  fpt pt;  // letzten Schnittpunkt umwandeln in Anfangspunkt
  if (NearCont(x, y, &pt)) {
    cc->cptail->type = CT_CUTBEGIN;
    cc->cptail->pt = pt;
    ed_state = ED_INIMOV;
    DoMove(Seite);
    ed_state = ED_ADD;
    return TRUE;
    }
  return FALSE;
  }


BOOL CutEditObj::OnMouseMove(WPARAM wP, int x, int y, int Seite)
  {
  if ((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV)) {
    MovePt(x, y);
    return TRUE;
    }
  else
    return FALSE;
  }


BOOL CutEditObj::OnLButtonUp(WPARAM wP, int x, int y, int Seite)
  {
  DBWIN_ASSERT((ed_state == ED_INIMOV) || (ed_state == ED_ADDMOV));
  MovePt(x, y);
  if (clear_old) {
    DrawMove(Seite);
    clear_old = FALSE;
    }
  DoMove(Seite);
  ed_state = (ed_state == ED_INIMOV) ? ED_INIT : ED_ADD;
  actcp = NULL;
  return TRUE;
  }


void CutEditObj::Load()
  {
  LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)(m.ReadData(Par()->hd.ObjRec, Par()->hd.ObjId));
  DBWIN_ASSERT((lpobj == NULL) || (*lpobj == NULL));
  MoveColor = m.GetConstLong (Par()->rMoveColor);
  color = m.GetConstLong (Par()->rcolor);
  Update();
  }


void CutEditObj::Update()
  {
  if (Initialized) {
    if (clear_old) {
      DrawMove(m.ActSide());
      clear_old = FALSE;
      }
    cc->FreeCnts();
    }
  tr2 FAR *sc = (tr2 FAR *)(m.ReadData(Par()->scR, Par()->scI));
  if (sc != NULL) {
    lmemcpy(&wtos, sc, sizeof(ftr2));
    stow = wtos;
    InvSc2d((tr2 FAR *)&stow);
    DBWIN_ASSERT(ScriptParam->par_Size >= sizeof(DefCutEdit_param));
    int numcnts = ((ScriptParam->par_Size - sizeof(DefCutEdit_param)) /
                  sizeof(Par()->CntRef[0])) + 1;
    for (int i = 0; i < numcnts; i++) {
      fpt FAR *cnt = (fpt FAR *)(m.ReadData(Par()->CntRef[i].R, Par()->CntRef[i].I));
      LPCONTLIST newcnt = cc->UnpackCnt(cnt);
      if (newcnt != NULL) {
        newcnt->next = cc->cnts;
        cc->cnts = newcnt;
        }
      }
    for (LPCUTPOINT cp = cc->cphead; cp != NULL; cp = cp->next)
      if (cp->type != CT_CUTMID) {
        float dummy;
        cc->GetNearestContPt(&dummy, &cp->pt);
        }
    Initialized = TRUE;
    }
  else {
    cc->FreeCp();
    Initialized = FALSE;
    }
  }


void CutEditObj::SetConnection()
  {
  m.SetConnection (Par()->scR, Par()->scI, Offset());
  int numcnts = ((ScriptParam->par_Size - sizeof(DefCutEdit_param)) /
                sizeof(Par()->CntRef[0])) + 1;
  for (int i = 0; i < numcnts; i++)
    m.SetConnection(Par()->CntRef[i].R, Par()->CntRef[i].I, Offset());
  }


void CutEditObj::Reset(BOOL Clear)
  {
  if (Initialized) {
    if (clear_old) {
      DrawMove(m.ActSide());
      clear_old = FALSE;
      }
    }
  m.ClearConnection (Par()->scR, Par()->scI, Offset());
  int numcnts = ((ScriptParam->par_Size - sizeof(DefCutEdit_param)) /
                sizeof(Par()->CntRef[0])) + 1;
  for (int i = 0; i < numcnts; i++)
    m.ClearConnection(Par()->CntRef[i].R, Par()->CntRef[i].I, Offset());
  }

