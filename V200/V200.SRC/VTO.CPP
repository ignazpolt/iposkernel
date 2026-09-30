// $Header:   P:/marille/clinicum/rev/vto.cpv   1.23   05 Oct 1998 11:56:46   Gerhold  $
// $Log:   P:/marille/clinicum/rev/vto.cpv  $
// 
//    Rev 1.23   05 Oct 1998 11:56:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.22   15 Sep 1998 10:51:12   Martin
// IsUpdateFromEle raus
// 
//    Rev 1.21   19 May 1998 16:20:50   Martin
// StoreExtraInfo ...
// 
//    Rev 1.20   24 Oct 1997 08:37:22   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.19   18 Aug 1997 18:02:14   Martin
// VTO Formular-faehig
// 
//    Rev 1.18   07 Jul 1997 08:57:08   Hannes
// FreeExpNodes
// 
//    Rev 1.17   11 Apr 1997 15:50:06   Martin
// myacos
// 
//    Rev 1.16   10 Jun 1996 10:10:12   GERHOLD
// pragma pack
// 
//    Rev 1.15   24 Mar 1996 12:09:34   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.14   02 Feb 1996 10:34:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.13   25 Oct 1995 12:22:54   HANNES
// Aenderungen Hannes
// 
//    Rev 1.12   24 Aug 1995 00:20:08   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.11   31 Mar 1995 13:09:22   HANNES
//  
// 
//    Rev 1.10   29 Mar 1995 19:28:24   sepp
// 
//    Rev 1.9   20 Mar 1995 12:06:02   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.8   05 Dec 1994 17:42:42   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.7   15 Nov 1994 12:13:16   MARTIN
// VtoContext
// 
//    Rev 1.6   10 Nov 1994 14:32:02   MARTIN
// top < bottom
// 
//    Rev 1.5   09 Nov 1994 13:16:42   MARTIN
// AvoidInvalidate
// 
//    Rev 1.4   07 Nov 1994 11:29:12   GERHOLD
// MARTIN ... Mousemove wird in ??? nicht weitergereicht.
// 
//    Rev 1.3   20 Sep 1994 11:38:38   HANNES
// VTO MultiProc Faehig gemacht
// 
//    Rev 1.2   24 Jun 1994 21:09:58   HANNES
// 
//    Rev 1.1   24 Jun 1994 19:47:30   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.35   13 Apr 1994 20:55:12   MARTIN
// frmobj3.hpp
// 
//    Rev 1.34   09 Feb 1994 19:14:32   MARTIN
// Scale following nur fuer direkt bei Gruppe angegebene Objekte
// 
//    Rev 1.33   26 Jan 1994 20:43:48   HANNES
// VTO_Start: 3 Prozeduren um eine Optimierungsmoeglichkeit vom Script aus
// zu schaffen
// 
//    Rev 1.32   24 Jan 1994 11:13:28   HANNES
// 
//    Rev 1.31   13 Jan 1994 16:16:24   HANNES
// dfield inc. raus
// 
//    Rev 1.30   12 Jan 1994 11:13:18   HANNES
// Unnoetige Includes entfernt
// 
//    Rev 1.29   04 Jan 1994 17:44:00   MARTIN
// Skalierungsfaktor fuer Koordinatenausgabe
// 
//    Rev 1.28   29 Nov 1993 08:57:26   HANNES
// Fehlerkorrektur beim Hintergrundloeschen
// 
//    Rev 1.27   04 Nov 1993 11:49:46   MARTIN
// signed / unsigned mismatch warning korrigiert
// 
//    Rev 1.26   03 Nov 1993 19:21:16   HANNES
// Reihenfolge beim Load umgestellt
// 
//    Rev 1.25   18 Oct 1993 19:57:04   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.24   22 Sep 1993 09:16:56   HANNES
// Version nach St. Poelten
// 
//    Rev 1.23   05 Sep 1993 22:14:16   HANNES
// Aufraeumarbeiten, Verbesserungen
// 
//    Rev 1.22   27 Aug 1993 16:46:04   MARTIN
// Vto_SetMode, Vto_Start, Vto_ApplyCut
// 
//    Rev 1.21   15 Jul 1993 16:37:00   HANNES
// Drucker in die DMWAPI ausgelagert
// 
//    Rev 1.20   23 Jun 1993 11:32:38   MARTIN
// Korrektur der movelist (Teilgruppen !)
// 
//    Rev 1.19   18 Jun 1993 15:08:32   MARTIN
// Prototyp von SetConnection
// 
//    Rev 1.18   16 Jun 1993 16:53:12   MARTIN
// flag fuer OnMove (first_call....)
// 
//    Rev 1.17   15 Jun 1993 23:24:46   MARTIN
// Vto_OnMove, Vto_DrawObject, ....
// 
//    Rev 1.16   05 May 1993 18:25:58   MARTIN
// Fehler korrigiert (Konstanten P_* waren falsch definiert)
// 
//    Rev 1.15   22 Apr 1993 21:03:58   MARTIN
// Erweiterungen fuer Chirurgie
// 
//    Rev 1.14   19 Apr 1993 01:36:26   MARTIN
// Entwicklung Chirurgie
// 
//    Rev 1.13   02 Apr 1993 18:03:52   MARTIN
// Diverse Aenderungen
// 
//    Rev 1.12   17 Mar 1993 18:12:34   MARTIN
// 32 Bit Umstellung der Scripts
// und Korrektur in Vto_DefineGroup
// 
//    Rev 1.11   09 Mar 1993 22:57:08   MARTIN
// kleine Aenderung fuer SoftEditObj
// 
//    Rev 1.10   03 Mar 1993 15:33:56   MARTIN
// diverse Mitteilungen an den Script
// (Scriptvariablen vtomode,mode,gn,pn werden richtig beschrieben)
// 
//    Rev 1.9   24 Feb 1993 21:39:04   MARTIN
// Korrektur in Vto_DefineGroup bei EM_UPDATE
// 
//    Rev 1.8   17 Feb 1993 15:24:08   MARTIN
// Umbau auf logische Koordinaten und FrmObjects
// 
//    Rev 1.7   14 Feb 1993 16:10:30   MARTIN
// Entwicklung
// 
//    Rev 1.6   05 Feb 1993 19:33:34   MARTIN
// Entwicklung
// 
//    Rev 1.5   01 Feb 1993 12:15:58   MARTIN
// Entwicklung
// 
//    Rev 1.4   01 Feb 1993 11:52:28   MARTIN
// Entwicklung
// 
//    Rev 1.3   29 Jan 1993 21:49:46   MARTIN
// Entwicklung
// 
//    Rev 1.2   29 Jan 1993 21:43:26   MARTIN
// Entwicklung
// 
//    Rev 1.1   29 Jan 1993 21:10:56   MARTIN
// Entwicklung
// 
//    Rev 1.0   29 Jan 1993 18:35:52   MARTIN
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#define MODULENUM 3
#include "winass.hpp"
#include "ddsmsg.h"
#include "globmem.h"
#include "font.hpp"
#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "dds.h"
#include "cfield.hpp"
#include "frmobj.hpp"
#include "image.hpp"
#include "frmobj3.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "winextra.hpp"

#include "vto.hpp"


inline LPVOID mymalloc(size_t size)
  {
  return GetGlobMem(size);
  };


inline void myfree(LPVOID obj)
  {
  FreeGlobMem(obj);
  };


LPVOID Vto_Group::operator new (size_t size)
  {
  return GetGlobMem(size);
  }

#define ENTER(GRP,COFFS)  SetExtraInfo s(GRP->myinst,GRP->xTableInd,GRP->xRec,COFFS);  \
                          LPDBRECORD old; \
                          if (GRP->xRec != NULL) { \
                            LPDBRECORD old = GRP->myinst->rr->GetRecord(GRP->xTableInd);  \
                            GRP->myinst->rr->SetRecord (GRP->xTableInd,GRP->xRec); \
                            } \
                          else old = NULL;
#define LEAVE(GRP) if (old != NULL)   \
                     GRP->myinst->rr->SetRecord (GRP->xTableInd,old);

void Vto_Group::operator delete (LPVOID obj)
  {
  FreeGlobMem(obj);
  }


Vto_Group::Vto_Group(Vto_DefineGroup_param FAR *par,mdiChild *c)
  {
  next = NULL;
  myinst = c;
  LPDWORD lpid = LPDWORD (c->ReadlData (par->grpid));
  DBWIN_ASSERT (lpid != NULL);
  grpid = (*lpid);
  DBWIN_ASSERT (c->IsConst(par->_modeflags));
  modeflags = *((LONG FAR *) c->ReadlData (par->_modeflags));    // !!!! spaeter Sicherheitsabfragen !!!!
  UpdateProc = par->UpdateProc;
  selmodeR = par->selmodeR;
  selmodeI = par->selmodeI;
  RotObj = NULL;
  SoftObj = NULL;
  CutObj = NULL;
  DBWIN_ASSERT (c->IsConst (par->_SelColor));
  SelColor = *((LONG FAR *) (c->ReadlData (par->_SelColor)));
  scfact = float(1.0);    // default: keine Vergroesserung / Verkleinerung
  idlist = NULL;
  objlist = NULL;
  otherlist = NULL;
  parts = NULL;
  s_to_w.A[0][0] = s_to_w.A[1][1] = (float)1.0;   // default: Einheitsmatrix
  s_to_w.A[0][1] = s_to_w.A[1][0] = (float)0.0;
  s_to_w.B[0]    = s_to_w.B[1]    = float(0.0);
  // Vsum , minmax werden vor jeder Verwendung neu berechnet
  selected = FALSE;
  }


Vto_Group::~Vto_Group()
  {
  LPVTOIDLIST idfree, idnext;
  idnext = idlist;
  while (idnext != NULL) {
    idfree = idnext;
    idnext = idnext->next;
    myfree(idfree);
    }
  if (!(modeflags & GRP_ISPART)) {
    LPVTOOBJLIST objfree, objnext;
    objnext = objlist;
    while (objnext != NULL) {
      objfree = objnext;
      objnext = objnext->next;
      myfree(objfree);
      }
    }
  LPVTOOTHERLIST otherfree, othernext;
  othernext = otherlist;
  while (othernext != NULL) {
    otherfree = othernext;
    othernext = othernext->next;
    myfree(otherfree);
    }
  if (parts != NULL)
    delete parts;
  }


LPVTOGRP Vto_Group::GetGroup(DWORD id)
  {
  for (LPVTOGRP grp = this;
       (grp != NULL) && (grp->grpid != id);
       grp = grp->next);
  return grp;
  }


void Vto_Group::CalcSelInfo(int ptx, int pty)
  {
  for (LPVTOGRP grp = this; grp != NULL; grp = grp->next) {
    grp->Vsumx = 32000;
    for (LPVTOGRP part = grp->parts; part != NULL; part = part->parts)
      part->Vsumx = 32000;
    }
  for (grp = this; grp != NULL; grp = grp->next) {
    grp->CalcSelInt(this, ptx, pty);
    }
  }


void Vto_Group::CalcSelInt(LPVTOGRP grp, int ptx, int pty)
  {
  long sumx, sumy;
  if (Vsumx < 32000) return;   // schon berechnet
  DBWIN_ASSERT((idlist != NULL) || (objlist != NULL));
  sumx = sumy = 0;
  int anz_pts = 0;
  grpLogRect.left = grpLogRect.top = 32000;
  grpLogRect.right = grpLogRect.bottom = -32000;
  for (LPVTOIDLIST id = idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = grp->GetGroup(id->grpid);
    subgrp->CalcSelInt(grp, ptx, pty);   // rekursiver Aufruf
    if (subgrp->Vsumx < 32000) {
      sumx += subgrp->Vsumx;  sumy += subgrp->Vsumy;
      anz_pts++;
      if (subgrp->grpLogRect.left < grpLogRect.left) grpLogRect.left = subgrp->grpLogRect.left;
      if (subgrp->grpLogRect.top < grpLogRect.top) grpLogRect.top = subgrp->grpLogRect.top;
      if (subgrp->grpLogRect.right > grpLogRect.right) grpLogRect.right = subgrp->grpLogRect.right;
      if (subgrp->grpLogRect.bottom > grpLogRect.bottom) grpLogRect.bottom = subgrp->grpLogRect.bottom;
      }
    }
  for (LPVTOOBJLIST obj = objlist; obj != NULL; obj = obj->next) {
    LPFRMOBJ o = obj->obj;
    if ((o != NULL) && (o->Initialized)) {
      if (o->IsCont()) {
        if (modeflags & GRP_ISPART)
          ((TrcContObj FAR *)o)->SelectPart((short)grpid);
        else
          ((TrcContObj FAR *)o)->SelectPart(-1);
        }
      int vx, vy;
      if (o->GetPtToObjVect(ptx, pty, &vx, &vy)) {
        sumx += vx;  sumy += vy;
        anz_pts++;
        LPRECT logr = o->GetLogRect (o->ErsteSeite());
        WIN_ASSERT (logr != NULL);
        if (logr->left   < grpLogRect.left  ) grpLogRect.left   = logr->left;
        if (logr->top    < grpLogRect.top   ) grpLogRect.top    = logr->top;
        if (logr->right  > grpLogRect.right ) grpLogRect.right  = logr->right;
        if (logr->bottom > grpLogRect.bottom) grpLogRect.bottom = logr->bottom;
        }
      }
    }
  if (anz_pts > 0) {
    Vsumx = int(sumx / long(anz_pts));  // gewichten mit Anzahl der Objekte
    Vsumy = int(sumy / long(anz_pts));
    }
  else {
    Vsumx = 32000;   // Gruppe enthaelt zur Zeit keine Objekte
    }
  // jetzt noch selbiges fuer Teile
  if (parts != NULL)
    parts->CalcSelInt(grp, ptx, pty);
  }


void Vto_Group::CalcSchwerSum(LPVTOGRP first, fpt FAR *pt, int FAR *anz_pts)
  {
  for (LPVTOIDLIST id = idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = first->GetGroup(id->grpid);
    DBWIN_ASSERT(subgrp != NULL);
    subgrp->CalcSchwerSum(first, pt, anz_pts);
    }
  for (LPVTOOBJLIST obj = objlist; obj != NULL; obj = obj->next) {
    LPFRMOBJ o = obj->obj;
    if ((o != NULL) && (o->Initialized)) {
      if (!o->rcLogRectInitialized) {
        o->GetMinMax ();
        o->rcLogRectInitialized = TRUE ;
        }
      pt->x += float(o->schwerx);
      pt->y += float(o->schwery);
      (*anz_pts)++;
      }
    }
  }


#ifdef UEBERLEGT
Vto::~Vto()
  {
  if (_MyHandle)
    CheckWindow (_MyHandle,FALSE);
  if (commands) {
    FreeExpNodes();
    ExCute (EM_RESET);
    GlobalFree (commands);
    commands = 0;
    }
  DelSelList();
  DBWIN_ASSERT(group == NULL);
  DBWIN_ASSERT(movelist == NULL);
  }


void ActivateTool (mdiChild *c);
void Vto::LoadData()
  {
  if (_MyHandle)
    CheckWindow (_MyHandle,TRUE);
  mode = M_INACTIVE;

  /*-----< Laden / Berechnen der Daten >-------*/
  // Alle Records loeschen
  _scale = float(1.0) ;         // Ansonsten werden sich
                                // die Felder ganz nett schoen
                                // aufregen
  ExCute (EM_LOAD | EM_FIXCONNECTION) ;
  SetCreationFlag (FALSE);
  ActivateTool (this);

  // Fuer den Fall, dass noch ueberhaupt kein Punkt existiert ->
  // vernuenftig vorbelegen
  if (_MyHandle) {
    GetMinMax ();
    _xm = (rcLogRect.left + rcLogRect.right) / 2;
    _ym = (rcLogRect.top + rcLogRect.bottom) / 2 ;

    // Berechnung des Default - Mappings, damit alles Platz hat
    CalcScale ();
    InitializeBars();
    MapChanged ();

    ((FrmObjectList FAR *) _ObjectList)->Reformat ();
    }
  }


LONG FAR PASCAL Vto::SpcFnc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done)
  {
  LONG RetVal = 0;
  BOOL call_trac_spcfnc = TRUE;

  switch (msg) {

    case WM_KILLFOCUS :
      ClearName ();
      break ;
   
    case WM_MOUSEMOVE:
      call_trac_spcfnc = FALSE;
      if ((state == S_MOVING) ||
          (state == S_ROTATING) ||
          (state == S_CENTMOVING)) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        if (state == S_MOVING)
          CalcTransMat(lP);
        else if (state == S_ROTATING)
          CalcRotMat(lP);
        else
          CalcRotCent(lP);
        DrawGrpMove();
        clear_old = TRUE;
        }
      else if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
        old_lP = lP;
        old_wP = wP;
        }
      else if (state == S_SOFTEDITING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->SoftObj->OnMouseMove(wP, x, y,actSide());
        }
      else if (state == S_CUTTING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->CutObj->OnMouseMove(wP, x, y,actSide());
        }
      else
        call_trac_spcfnc = TRUE;
      break;

    case WM_LBUTTONDBLCLK:
      if ((mode == M_CUT) && (state == S_GRPSELECTED) &&
          (actsel->grp->modeflags & GRP_CUTABLE)) {
        int x, y;
        MouseToLog(lP, &x, &y);
        actsel->grp->CutObj->OnLButtonDblClk(wP, x, y,actSide());
        }
      break;

    case WMU_MOUSEOUTOFWND :
      ClearName ();
      break ;

    case WM_LBUTTONDOWN:
      if (mode != M_INACTIVE) {
        ClearName ();
        MouseToLog(lP, &oldmousex, &oldmousey);
        if (((FrmObjectList FAR *) _ObjectList)->OnLButtonDown (wP,lP)) {
          if (state != S_NONESELECTED) {
            DeselectGrp();
            DelSelList();
            state = S_NONESELECTED;
            }
          }
        else {
          if (mode == M_CUT) {
            if (state == S_GRPSELECTED) {
              if ((actsel->grp->modeflags & GRP_CUTABLE) &&
                  (actsel->grp->CutObj->OnLButtonDown(wP, oldmousex, oldmousey,actSide())))
                state = S_CUTTING;
              else {
                DeselectGrp();
                DelSelList();
                state = S_NONESELECTED;
                }
              }
            if (state == S_NONESELECTED) {
              GenSelList(lP);
              if (actsel != NULL) {
                SelectGrp();
                state = S_GRPSELECTED;
                }
              }
            }
          else {
            if (state == S_GRPSELECTED) {
              DBWIN_ASSERT(actsel != NULL);
              if (!MouseInGrpRect(lP, actsel->grp)) {
                DeselectGrp();
                DelSelList();
                state = S_NONESELECTED;
                }
              else
                state = S_TIMERWAITSEL;
              }
            if (state == S_NONESELECTED) {
              GenSelList(lP);
              if (actsel != NULL) {
                SelectGrp();
                state = S_TIMERWAIT;
                }
              }
            if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
              SetTimer(hWnd, VTOTIMERID, VTODELAY, NULL);
              old_lP = lP;
              old_wP = wP;
              }
            }
          }
        call_trac_spcfnc = FALSE;
        }
      break;

    case WM_TIMER:
      if (wP == VTOTIMERID) {
        KillTimer(hWnd, VTOTIMERID);
        if ((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL)) {
          DBWIN_ASSERT(actsel != NULL);
          if ((mode == M_MOVE) && (actsel->grp->modeflags & GRP_MOVEABLE)) {
            CalcTransMat(old_lP);
            DrawGrpMove();
            clear_old = TRUE;
            state = S_MOVING; 
            }
          else if ((mode == M_SOFT) && (actsel->grp->modeflags & GRP_SOFTEDIT)) {
            if (actsel->grp->SoftObj->OnLButtonDown(old_wP, oldmousex, oldmousey,actSide())) {
              int x, y;
              MouseToLog(old_lP, &x, &y);
              actsel->grp->SoftObj->OnMouseMove(old_wP, x, y,actSide());
              state = S_SOFTEDITING;
              }
            else
              state = S_GRPSELECTED;
            }
          }
        call_trac_spcfnc = FALSE;
        }
      break;

    case WM_LBUTTONUP:
      if (state == S_TIMERWAIT) {
        KillTimer(hWnd, VTOTIMERID);
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      else if (state == S_TIMERWAITSEL) {
        KillTimer(hWnd, VTOTIMERID);
        DeselectGrp();
        DelSelList();
        GenSelList(lP);
        if (actsel != NULL)
          SelectGrp(), state = S_GRPSELECTED;
        else
          state = S_NONESELECTED;
        call_trac_spcfnc = FALSE;
        }
      else if (state == S_MOVING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcTransMat(lP);
        DoGrpMove();
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      else if (state == S_SOFTEDITING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        if (actsel->grp->SoftObj->OnLButtonUp(wP, x, y, actSide()))
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      else if (state == S_CUTTING) {
        int x, y;
        MouseToLog(lP, &x, &y);
        if (actsel->grp->CutObj->OnLButtonUp(wP, x, y,actSide()))
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      break;

    case WM_RBUTTONDOWN:
      ClearName ();
      if (actsel != NULL) {
        if ((mode == M_MOVE) && (actsel->grp->modeflags & GRP_ROTABLE)) {
          if (state == S_GRPSELECTED) {
            if (NearRotCent(lP))
              state = S_CENTMOVING;
            else {
              state = S_ROTATING;
              oldphi = float(0.0);
              CalcRotMat(lP);
              oldphi = act_phi;
              }
            call_trac_spcfnc = FALSE;
            }
          }
        else if (mode == M_SOFT) {
          // derzeit nicht verwendet
          }
        else if (mode == M_CUT) {
          // letzten Punkt rueckgaengig machen
          if (state == S_GRPSELECTED) {
            if (actsel->grp->modeflags & GRP_CUTABLE)
              actsel->grp->CutObj->OnLButtonDown(0, 1, 0,actSide());
            call_trac_spcfnc = FALSE;
            }
          }
        }
      break;

    case WM_RBUTTONUP:
      if (state == S_ROTATING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcRotMat(lP);
        DoGrpMove();
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      else if (state == S_CENTMOVING) {
        if (clear_old) {
          DrawGrpMove();
          clear_old = FALSE;
          }
        CalcRotCent(lP);
        DoRotCentMove();
        state = S_GRPSELECTED;
        call_trac_spcfnc = FALSE;
        }
      break;

    case WM_KEYDOWN:
      if (wP == VK_TAB) {
        if (state == S_GRPSELECTED) {
          DBWIN_ASSERT(actsel != NULL);
          DeselectGrp();
          if (GetKeyState (VK_SHIFT) < 0) {
            if (actsel->prev != NULL)
              actsel = actsel->prev;
            }
          else {
            if (actsel->next != NULL)
              actsel = actsel->next;
            }
          SelectGrp();
          skip_next_char = TRUE;
          call_trac_spcfnc = FALSE;
          }
        }
      else {
        // derzeit noch nicht verwendet
        }
      break;

    case WM_ERASEBKGND :
      {
      // Vielleicht ist ein image Angezeigt, dann dieses (um Flackern
      // zu verhindern) bitte nicht anzeigen
      LPIMGBG ib = LPIMGBG (GetDocumentExtraData (DED_IMGBG));
      if (ib != NULL) {

#ifdef WIN32
        HBRUSH hbgr = HBRUSH(GetClassLong (hWnd,GCL_HBRBACKGROUND));
#else
        HBRUSH hbgr = GetClassWord (hWnd,GCW_HBRBACKGROUND);
#endif

        HDC hDC = HDC(wP);
        HBRUSH hbold = SelectObject (hDC,hbgr);
        HPEN   hpold = SelectObject (hDC,GetStockObject (NULL_PEN));
        RECT ri,cr;
        GetClientRect (hWnd,&cr);
        {
        PaintContext pc(_MyHandle,0xFFFF,0xFFFF,DO_WORK);
        pc.LogicalTwips (_xp,_yp,_scale);
        pc.LogRecttoPhys (&ri,&ib->r);
        IntersectRect (&ri,&ri,&cr);
        }
        if (ri.right < cr.right);
          Rectangle (hDC,ri.right-1,cr.top-1,cr.right+1,cr.bottom + 1);
        if (ri.left > cr.left)
          Rectangle (hDC,cr.left-1,cr.top-1,ri.left+1,cr.bottom + 1);
        if (ri.bottom < cr.bottom)
          Rectangle (hDC,ri.left-1,ri.bottom-1,ri.right+1,cr.bottom + 1);
        if (ri.top > cr.top)
          Rectangle (hDC,ri.left-1,cr.top-1,ri.right+1,ri.top + 1);
        SelectObject (hDC,hpold);
        SelectObject (hDC,hbold);
        RetVal = 1;
        *done = TRUE ;
        }
      }
      break ;

    case WM_CHAR:
      if (skip_next_char) {
        skip_next_char = FALSE;
        call_trac_spcfnc = FALSE;
        }
      break;
    }

  if (call_trac_spcfnc)
    RetVal = Tracing::SpcFnc(hWnd,msg,wP,lP,done);

  return RetVal;
  }


LONG Vto::ToScreen(HWND hWnd)
  {
  HideName ();
  LONG RetValue = Tracing::ToScreen(hWnd);
  if (clear_old)
    DrawGrpMove();
  ShowName ();

  return RetValue ;
  }


void Vto::ScrollHorizontal(int dist)
  {
  ClearName ();
  if (clear_old) {
    DrawGrpMove();
    clear_old = FALSE;
    }
  Tracing::ScrollHorizontal(dist);
  }


void Vto::ScrollVertikal(int dist)
  {
  ClearName ();
  if (clear_old) {
    DrawGrpMove();
    clear_old = FALSE;
    }
  Tracing::ScrollVertikal(dist);
  }
#endif


void Form::MouseToLog(LONG mouse, int FAR *ptx, int FAR *pty)
  {
  int x, y;
  ((FrmObjectList FAR *) GetOutData()->_ObjectList)->GetLogKoords(mouse, &x, &y);
  *ptx = x;
  *pty = y;
  }


void Form::CalcTransMat(LONG mouse)
  {
  if (actsel == NULL) return;
  DBWIN_ASSERT((state == S_TIMERWAIT) || (state == S_TIMERWAITSEL) || (state == S_MOVING) || (state == S_CENTMOVING));
  int dx, dy;
  MouseToLog(mouse, &dx, &dy);
  act_dx = dx - oldmousex;
  act_dy = dy - oldmousey;
  act_phi = float(0.0);
  grp_sc.A[0][0] = grp_sc.A[1][1] = float(1.0);
  grp_sc.A[0][1] = grp_sc.A[1][0] = float(0.0);
  grp_sc.B[0] = float(act_dx);  grp_sc.B[1] = float(act_dy);
  sc_state = (state == S_CENTMOVING) ? S_CENTMOVING : S_MOVING;
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

void Form::CalcRotMat(LONG mouse)
  {
  if (actsel == NULL) return;
  DBWIN_ASSERT(state == S_ROTATING);
  int mx, my;
  MouseToLog(mouse, &mx, &my);
  float dx = float(mx - actsel->grp->RotObj->schwerx);
  float dy = float(my - actsel->grp->RotObj->schwery);
  float len = float (hypot(dx, dy));
  if (len > float(1.0E-3)) {
    dx /= len;
    dy /= len;
    if (dx > 0.0)
      act_phi = - float(myacos(dy));
    else
      act_phi = float(myacos(dy));
    act_phi *= float(180.0 / pi);
    act_phi -= oldphi;
    if (act_phi > float(180.0)) act_phi -= float(360.0);
    if (act_phi < float(-180.0)) act_phi += float(360.0);
    fpt act_rcent;
    act_rcent.x = float(actsel->grp->RotObj->schwerx);
    act_rcent.y = float(actsel->grp->RotObj->schwery);
    CalcLinTrans(&grp_sc, &act_rcent, 0.0, 0.0, act_phi);
    }
  else {
    act_phi = float(0.0);
    grp_sc.A[0][0] = grp_sc.A[1][1] = float(1.0);
    grp_sc.A[0][1] = grp_sc.A[1][0] = float(0.0);
    grp_sc.B[0]    = grp_sc.B[1]    = float(0.0);
    }
  act_dx = 0;
  act_dy = 0;
  sc_state = S_ROTATING;
  }


BOOL Form::NearRotCent(LONG mouse)
  {
  if (actsel == NULL) return FALSE;
  int mx, my;
  MouseToLog(mouse, &mx, &my);
  float dx = float(mx - actsel->grp->RotObj->schwerx);
  float dy = float(my - actsel->grp->RotObj->schwery);
  float len = float (fabs(dx) + fabs(dy));
  return len < float(ROT_CENT_TOLERANCE);
  }


BOOL Form::MouseInGrpRect(LONG mouse, LPVTOGRP grp)
  {
  int mx, my;
  MouseToLog(mouse, &mx, &my);
  return (mx >= grp->grpLogRect.left) && (mx <= grp->grpLogRect.right) &&
         (my >= grp->grpLogRect.top) && (my <= grp->grpLogRect.bottom);
  }


void Form::CalcRotCent(LONG mouse)
  {
  DBWIN_ASSERT((actsel != NULL) && (actsel->grp->RotObj != NULL));
  oldmousex = actsel->grp->RotObj->schwerx;
  oldmousey = actsel->grp->RotObj->schwery;
  CalcTransMat(mouse);
  }


void Form::SelectGrpInt(LPVTOGRP grp)
  {
  for (LPVTOIDLIST id = grp->idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = group->GetGroup(id->grpid);
    SelectGrpInt(subgrp);   // rekursiver Aufruf
    }
  for (LPVTOOBJLIST obj = grp->objlist; obj != NULL; obj = obj->next) {
    LPFRMOBJ o = obj->obj;
    if ((o != NULL) && (o->Initialized) && (o->IsCont())) {
      if (grp->modeflags & GRP_ISPART)
        ((TrcContObj FAR *)o)->SelectPart((short)grp->grpid);
      else
        ((TrcContObj FAR *)o)->SelectPart(-1);
      }
    if (o != NULL)
      ((FrmObjectList FAR *) OutList())->Select(o, grp->SelColor);
    }
  for (LPVTOOTHERLIST other = grp->otherlist; other != NULL; other = other->next) {
    if (other->obj != NULL)
      ((FrmObjectList FAR *) OutList())->Select(other->obj, grp->SelColor);
    }
  grp->selected = TRUE;
  }


void Form::SelectGrp()
  {
  if (actsel != NULL) {
    LPVTOGRP grp = actsel->grp;
    SelectGrpInt(grp);
    if ((mode == M_MOVE) && (grp->RotObj != NULL)) {
      ((FrmObjectList FAR *) OutList())->Select(grp->RotObj, grp->SelColor);
      }
    if ((mode == M_SOFT) && (grp->SoftObj != NULL)) {
      ((FrmObjectList FAR *) OutList())->Select(grp->SoftObj, grp->SelColor);
      }
    if ((mode == M_CUT) && (grp->CutObj != NULL)) {
      ((FrmObjectList FAR *) OutList())->Select(grp->CutObj, grp->SelColor);
      }
    // jetzt noch die Scriptvariablen schreiben
    DBWIN_ASSERT(mode != M_INACTIVE);
    DWORD hmode;
    if (mode == M_MOVE) hmode = VTO_SELFORMOVE;
    else if (mode == M_SOFT) hmode = VTO_SELFORSOFT;
    else if (mode == M_CUT) hmode = VTO_SELFORCUT;
    VtoContext->WriteData(vip->vtomodeR, vip->vtomodeI, &hmode, sizeof(DWORD), 0);
    VtoContext->WriteData(grp->selmodeR, grp->selmodeI, &hmode, sizeof(DWORD), 0);
    if (grp->modeflags & GRP_ISPART) {
      VtoContext->WriteData(vip->gnR, vip->gnI, &grp->next->grpid, sizeof(DWORD), 0);
      VtoContext->WriteData(vip->pnR, vip->pnI, &grp->grpid, sizeof(DWORD), 0);
      hmode = UPD_PART;
      }
    else {
      VtoContext->WriteData(vip->gnR, vip->gnI, &grp->grpid, sizeof(DWORD), 0);
      DWORD partid = DWORD(-1);
      VtoContext->WriteData(vip->pnR, vip->pnI, &partid, sizeof(DWORD), 0);
      hmode = UPD_GROUP;
      }
    VtoContext->WriteData(vip->modeR, vip->modeI, &hmode, sizeof(DWORD), 0);
    }
  }


void Form::DeselectGrpInt(LPVTOGRP grp)
  {
  for (LPVTOIDLIST id = grp->idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = group->GetGroup(id->grpid);
    DeselectGrpInt(subgrp);   // rekursiver Aufruf
    }
  for (LPVTOOBJLIST obj = grp->objlist; obj != NULL; obj = obj->next) {
    if (obj->obj != NULL)
      ((FrmObjectList FAR *) OutList())->Deselect(obj->obj);
    }
  for (LPVTOOTHERLIST other = grp->otherlist; other != NULL; other = other->next) {
    if (other->obj != NULL)
      ((FrmObjectList FAR *) OutList())->Deselect(other->obj);
    }
  grp->selected = FALSE;
  }


void Form::DeselectGrp()
  {
  if (actsel != NULL) {
    LPVTOGRP grp = actsel->grp;
    DeselectGrpInt(grp);
    if (grp->RotObj != NULL)
      ((FrmObjectList FAR *) OutList())->Deselect(grp->RotObj);
    if (grp->SoftObj != NULL)
      ((FrmObjectList FAR *) OutList())->Deselect(grp->SoftObj);
    if (grp->CutObj != NULL)
      ((FrmObjectList FAR *) OutList())->Deselect(grp->CutObj);
    // jetzt noch die Scriptvariablen schreiben
    DWORD hmode = VTO_NOTSEL;
    VtoContext->WriteData(vip->vtomodeR, vip->vtomodeI, &hmode, sizeof(DWORD), 0);
    VtoContext->WriteData(grp->selmodeR, grp->selmodeI, &hmode, sizeof(DWORD), 0);
    }
  }


void Form::GenSelList(LONG mouse)
  {
  DBWIN_ASSERT(sellist == NULL);
  int mx, my;
  MouseToLog(mouse, &mx, &my);
  group->CalcSelInfo(mx, my);
  float dist;
  for (LPVTOGRP gr = group; gr != NULL; gr = gr->next) {
    for (LPVTOGRP grp = gr; grp != NULL; grp = grp->parts) {
      if (grp->Vsumx >= 32000) continue;  // leere Gruppe
      if (mode == M_MOVE) {
        if (!(grp->modeflags & (GRP_MOVEABLE | GRP_ROTABLE))) continue;
        }
      else if (mode == M_SOFT) {
        if ((grp->modeflags & GRP_SOFTEDIT) && (grp->SoftObj != NULL)) {
          // SoftEditObject zu rcLogRect dazugeben
          LPRECT logr = grp->SoftObj->GetLogRect (grp->SoftObj->ErsteSeite());
          if (logr->left   < grp->grpLogRect.left  ) grp->grpLogRect.left   = logr->left;
          if (logr->top    < grp->grpLogRect.top   ) grp->grpLogRect.top    = logr->top;
          if (logr->right  > grp->grpLogRect.right ) grp->grpLogRect.right  = logr->right;
          if (logr->bottom > grp->grpLogRect.bottom) grp->grpLogRect.bottom = logr->bottom;
          }
        else
          continue;
        }
      else if (mode == M_CUT) {
        if ((grp->modeflags & GRP_CUTABLE) && (grp->CutObj != NULL)) {
          // CutEditObject zu rcLogRect dazugeben
          LPRECT logr = grp->CutObj->GetLogRect (grp->CutObj->ErsteSeite());
          WIN_ASSERT (logr != NULL);
          if (logr->left   < grp->grpLogRect.left  ) grp->grpLogRect.left   = logr->left;
          if (logr->top    < grp->grpLogRect.top   ) grp->grpLogRect.top    = logr->top;
          if (logr->right  > grp->grpLogRect.right ) grp->grpLogRect.right  = logr->right;
          if (logr->bottom > grp->grpLogRect.bottom) grp->grpLogRect.bottom = logr->bottom;
          }
        else
          continue;
        }
      else {
        DBWIN_ASSERT(FALSE);
        }
      dist = float(hypot(grp->Vsumx, grp->Vsumy));
      LPVTOSELSORT newsort = LPVTOSELSORT(mymalloc(sizeof(Vto_SelSort)));
      newsort->grp = grp;
      newsort->dist = dist;
      LPVTOSELSORT last = NULL;
      for (LPVTOSELSORT sort = sellist;
          (sort != NULL) && (sort->dist < dist);
          sort = sort->next) {
        last = sort;
        }
      if (last == NULL) {   // Beginn der Liste
        newsort->prev = NULL;
        newsort->next = sort;
        if (sort != NULL)
          sort->prev = newsort;
        sellist = newsort;
        }
      else {
        newsort->prev = last;
        newsort->next = sort;
        last->next = newsort;
        if (sort != NULL)
          sort->prev = newsort;
        }
      } // for grp
    } // for gr
  for (LPVTOSELSORT sort = sellist;
       (sort != NULL) && !MouseInGrpRect(mouse, sort->grp);
       sort = sort->next);
  if (sort == NULL)
    DelSelList();
  actsel = sellist;     // auf ersten Eintrag setzen
  }


void Form::DelSelList()
  {
  LPVTOSELSORT tofree, sort = sellist;
  while (sort != NULL) {
    tofree = sort;
    sort = sort->next;
    myfree(tofree);
    }
  sellist = NULL;
  actsel = NULL;
  }


void Form::TextDxDy(PaintContext *pc)
  {
  char str[50];
  sprintf(str, "dx = %.2f, dy = %.2f",
          LogToWorld(act_dx) / actsel->grp->scfact,
          LogToWorld(act_dy) / -actsel->grp->scfact);
  int x2 = oldmousex;
  int y2 = oldmousey;
  int x = x2 + act_dx;
  int y = y2 + act_dy;
  *pc << Line (x,y,x2,y2);
  POINT dp;
  dp.x = x;  dp.y = y;
  LPtoDP(pc->hDC, &dp, 1);
  PaintContext pchelp(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  DPtoLP(pchelp.hDC, &dp, 1);
  HDC hDisplay = CreateCompatibleDC(pchelp.hDC);
  SelectObject(hDisplay,GetStockObject(SYSTEM_FONT));

  int dx, dy;
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDisplay, str, lstrlen(str), &size);
  dx = size.cx;
  dy = size.cy;
#else
  DWORD dwext = GetTextExtent (hDisplay, str, lstrlen(str));
  dx = LOWORD (dwext);
  dy = HIWORD (dwext);
#endif

  if (x < x2)
    dp.x -= dy / 2 + dx;
  else
    dp.x += dy / 2;
  dp.y -= dy / 2 + dy;
  SetTextAlign (hDisplay, TA_TOP | TA_LEFT);
  SetTextColor(hDisplay, RGB(255,255,255));
  SetBkColor(hDisplay, RGB(0,0,0));
  HBITMAP hBitmap;
  if (hBitmap = CreateBitmap (dx, dy, 1, 1, NULL)) {
    hBitmap = (HBITMAP)SelectObject (hDisplay, hBitmap);
    ExtTextOut (hDisplay, 0, 0, 0, NULL, str, lstrlen(str), NULL);
    BitBlt (pchelp.hDC, dp.x, dp.y, dx, dy, hDisplay, 0, 0, SRCINVERT);
    hBitmap = (HBITMAP)SelectObject (hDisplay, hBitmap);
    DeleteObject (hBitmap);
    }
  DeleteDC(hDisplay);
  }


void Form::TextPhi(PaintContext *pc)
  {
  float neg_act_phi = -act_phi;
  char str[20];
  sprintf(str, "%.2f\260", neg_act_phi);
  POINT dp;
  dp.x = actsel->grp->RotObj->schwerx;
  LPRECT logr = actsel->grp->RotObj->GetLogRect (actsel->grp->RotObj->ErsteSeite());
  WIN_ASSERT (logr != NULL);
  dp.y = logr->top;
  if (grp_sc.A[0][0] < 1.0E9)
    Sc2dLog(&grp_sc, LPINT(&dp.x), LPINT(&dp.y), dp.x, dp.y);
  LPtoDP(pc->hDC, &dp, 1);
  PaintContext pchelp(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  DPtoLP(pchelp.hDC, &dp, 1);
  HDC hDisplay = CreateCompatibleDC(pchelp.hDC);
  SelectObject(hDisplay,GetStockObject(SYSTEM_FONT));

  int dx, dy;
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDisplay, str, lstrlen(str), &size);
  dx = size.cx;
  dy = size.cy;
#else
  DWORD dwext = GetTextExtent (hDisplay, str, lstrlen(str));
  dx = LOWORD (dwext);
  dy = HIWORD (dwext);
#endif

  if (neg_act_phi >= 0.0)
    dp.x -= dy / 2 + dx;
  else
    dp.x += dy / 2;
  dp.y -= dy / 2;
  SetTextAlign (hDisplay, TA_TOP | TA_LEFT);
  SetTextColor(hDisplay, RGB(255,255,255));
  SetBkColor(hDisplay, RGB(0,0,0));
  HBITMAP hBitmap;
  if (hBitmap = CreateBitmap (dx, dy, 1, 1, NULL)) {
    hBitmap = (HBITMAP)SelectObject (hDisplay, hBitmap);
    ExtTextOut (hDisplay, 0, 0, 0, NULL, str, lstrlen(str), NULL);
    BitBlt (pchelp.hDC, dp.x, dp.y, dx, dy, hDisplay, 0, 0, SRCINVERT);
    hBitmap = (HBITMAP)SelectObject (hDisplay, hBitmap);
    DeleteObject (hBitmap);
    }
  DeleteDC(hDisplay);
  }


void Form::DrawGrpMoveInt(LPVTOGRP grp, PaintContext *pc)
  {
  DBWIN_ASSERT((sc_state == S_MOVING) || (sc_state == S_ROTATING));
  for (LPVTOIDLIST id = grp->idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = group->GetGroup(id->grpid);
    DBWIN_ASSERT(subgrp != NULL);
    DrawGrpMoveInt(subgrp, pc);
    }
  LPLINELIST lines = NULL;
  for (LPVTOOBJLIST obj = grp->objlist; obj != NULL; obj = obj->next) {
    LPFRMOBJ o = obj->obj;
    if ((o != NULL) && (o->Initialized)) {
      if (o->IsCont())
        ((TrcContObj FAR *)o)->UseLineList(&lines);
      o->PaintTrans(pc, actSide(),&grp_sc);
      }
    }
  FreeLineList(lines);
  }


void Form::DrawGrpMove()
  {
  if (actsel != NULL) {
    PaintContext pc;
    GetDocumentContext(&pc, this);
    SetROP2(pc.hDC,R2_XORPEN);
    pc.diPen(MoveColor);
    LPVTOGRP grp = actsel->grp;
    if (state == S_CENTMOVING) {
      DBWIN_ASSERT((grp->RotObj != NULL) && grp->RotObj->Initialized);
      grp->RotObj->PaintTrans(&pc, actSide(),&grp_sc);
      }
    else {
      DrawGrpMoveInt(grp, &pc);
      // scale following nur fuer direkt bei dieser Gruppe angegebene Objekte
      for (LPVTOOTHERLIST other = grp->otherlist; other != NULL; other = other->next) {
        LPFRMOBJ o = other->obj;
        if ((o != NULL) && (o->Initialized) && (other->sc.A[0][0] < 1.0E9)) {
          // scale following und refpt beruecksichtigen !
          int vectx, vecty;
          if (other->refpt.x < 1.0E9) {
            int hptx, hpty;
            hptx = WorldToLog(other->refpt.x);
            hpty = WorldToLog(other->refpt.y);
            Sc2dLog(&grp_sc, &vectx, &vecty, hptx, hpty);
            vectx -= hptx;
            vecty -= hpty;
            }
          else {  // refpt nicht definiert -> nur Translation beruecksichtigen
            vectx = act_dx;
            vecty = act_dy;
            }
          Sc2dLog((tr2 FAR *)(&other->sc), &vectx, &vecty, vectx, vecty);
          tr2 sc;
          sc.A[0][0] = sc.A[1][1] = float(1.0);
          sc.A[0][1] = sc.A[1][0] = float(0.0);
          sc.B[0] = float(vectx);  sc.B[1] = float(vecty);
          o->PaintTrans(&pc, actSide(),&sc);
          }
        }
      // Ende scale following
      DBWIN_ASSERT((sc_state == S_MOVING) || (sc_state == S_ROTATING));
      if ((grp->RotObj != NULL) && grp->RotObj->Initialized)
        grp->RotObj->PaintTrans(&pc, actSide(),&grp_sc);
      if (sc_state == S_MOVING) TextDxDy(&pc);
      if (sc_state == S_ROTATING) TextPhi(&pc);
      DWORD grpid = (grp->modeflags & GRP_ISPART) ?
                     grp->next->grpid :
                     grp->grpid;
      BOOL first_time = TRUE;
      for (LPVTOMOVELIST ml = movelist; ml != NULL; ml = ml->next) {
        if (ml->grpid == grpid) {
          if (clear_old) {
            DWORD first_call = 0;
            VtoContext->WriteData(vip->modeR, vip->modeI, &first_call, sizeof(DWORD), 0);
            }
          else {
            DWORD first_call = 1;
            VtoContext->WriteData(vip->modeR, vip->modeI, &first_call, sizeof(DWORD), 0);
            if (first_time) {
              // erst wenn es noetig ist Scriptvariable schreiben
              WriteScriptVars();
              first_time = FALSE;
              }
            }
          {
          ENTER(grp,0L);
          BOOL dummy = TRUE;
          grp->myinst->PutDocumentExtraData (DED_AVOIDINVALIDATE,&dummy,sizeof(dummy));
          grp->myinst->ExCuteProc(ml->MoveProc, EM_LOAD /* | EM_CHANGETOTRUE */ );
          grp->myinst->ExCuteProc(ml->MoveProc, EM_RESET /* | EM_CHANGETOFALSE */ );
          grp->myinst->RemoveDocumentExtraData (DED_AVOIDINVALIDATE);
          LEAVE(grp);
          }
          }
        }
      }
    }
  }


void Form::DoGrpMoveInt(LPVTOGRP grp, DWORD updmode)
  {
  {
  ENTER(grp,0L);
  grp->myinst->ExCuteProc(grp->UpdateProc, EM_LOAD | EM_CHANGETOTRUE);
  grp->myinst->ExCuteProc(grp->UpdateProc, EM_CLEAR | EM_CHANGETOFALSE);
  LEAVE(grp);
  }
  if (updmode != UPD_SELF)  // wenn Aufruf fuer Gruppenbaum - Wurzel
    VtoContext->WriteData(vip->modeR, vip->modeI, &updmode, sizeof(DWORD), 0);
  for (LPVTOIDLIST id = grp->idlist; id != NULL; id = id->next) {
    LPVTOGRP subgrp = group->GetGroup(id->grpid);
    DBWIN_ASSERT(subgrp != NULL);
    DoGrpMoveInt(subgrp, UPD_SELF);
    }
  }


void Form::WriteScriptVars()
  {
  LPVTOGRP grp = actsel->grp;
  fpt wvect;
  wvect.x = LogToWorld(act_dx);
  wvect.y = LogToWorld(act_dy);
  if (grp->s_to_w.A[0][0] < 1.0E9) {
    Sc2d((tr2 FAR *)(&grp->s_to_w), &wvect, &wvect);
    wvect.x -= grp->s_to_w.B[0];
    wvect.y -= grp->s_to_w.B[1];
    }
  float neg_act_phi = -act_phi;
  VtoContext->WriteData(vip->dxR, vip->dxI, &wvect.x, sizeof(float), 0);
  VtoContext->WriteData(vip->dyR, vip->dyI, &wvect.y, sizeof(float), 0);
  VtoContext->WriteData(vip->phiR, vip->phiI, &neg_act_phi, sizeof(float), 0);
  if ((grp->modeflags & GRP_ROTABLE) &&
      (grp->RotObj != NULL) &&
      (grp->RotObj->Initialized)) {
    fpt hpt;
    hpt.x = LogToWorld(grp->RotObj->schwerx);
    hpt.y = LogToWorld(grp->RotObj->schwery);
    if (grp->s_to_w.A[0][0] < 1.0E9)
      Sc2d((tr2 FAR *)(&grp->s_to_w), &hpt, &hpt);
    VtoContext->WriteData(vip->rotptR, vip->rotptI, &hpt, sizeof(fpt), 0);
    }
  }


void Form::DoGrpMove()
  {
  if (actsel != NULL) {
    WriteScriptVars();
    LPVTOGRP grp = actsel->grp;
    DWORD updmode = UPD_SELF;
    VtoContext->WriteData(vip->modeR, vip->modeI, &updmode, sizeof(DWORD), 0);
    if (grp->modeflags & GRP_ISPART) {
      VtoContext->WriteData(vip->gnR, vip->gnI, &grp->next->grpid, sizeof(DWORD), 0);
      VtoContext->WriteData(vip->pnR, vip->pnI, &grp->grpid, sizeof(DWORD), 0);
      updmode = UPD_PART;
      }
    else {
      VtoContext->WriteData(vip->gnR, vip->gnI, &grp->grpid, sizeof(DWORD), 0);
      DWORD partid = DWORD(-1);
      VtoContext->WriteData(vip->pnR, vip->pnI, &partid, sizeof(DWORD), 0);
      updmode = UPD_GROUP;
      }
    DoGrpMoveInt(grp, updmode);
    }
  }


void Form::DoRotCentMove()
  {
  if (actsel != NULL)
    actsel->grp->RotObj->OnLButtonDblClk(0, oldmousex + act_dx, oldmousey + act_dy,actSide());
  }


////////////////////// Script-Funktionen ////////////////////////

#define v ((Form *)c->DrawContext())

BOOL Vto_Init(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR Offset = LPSTR(param) - sizeof(WORD);
    Vto_Init_param FAR *par = (Vto_Init_param FAR *)param;
    v->vip = par;
    DBWIN_ASSERT (c->IsConst (par->_MoveColor));
    v->MoveColor = *((LONG FAR *) c->ReadlData (par->_MoveColor));
    v->VtoContext = c;
    // Datenbankvariablen auf gueltige Werte initialisieren
    DWORD dummy = VTO_NOTSEL;
    c->WriteData(par->vtomodeR, par->vtomodeI, &dummy, sizeof(DWORD), Offset);
    dummy = UPD_SELF;
    c->WriteData(par->modeR, par->modeI, &dummy, sizeof(DWORD), Offset);
    dummy = 0;
    c->WriteData(par->gnR, par->gnI, &dummy, sizeof(DWORD), Offset);
    dummy = DWORD(-1);
    c->WriteData(par->pnR, par->pnI, &dummy, sizeof(DWORD), Offset);
    }

  return FALSE;
  }



static void CalcGrpRotCent(Form *vv, LPVTOGRP grp)
  {
  if ((grp->modeflags & GRP_ROTABLE) && (!grp->RotObj->Initialized)) {
    int anz_pts = 0;
    fpt schwer_sum;
    schwer_sum.x = schwer_sum.y = float(0.0);
    grp->CalcSchwerSum(vv->group, &schwer_sum, &anz_pts);
    if (anz_pts > 0)
      grp->RotObj->OnLButtonDblClk(0, int(schwer_sum.x / float(anz_pts)), int(schwer_sum.y / float(anz_pts)),vv->actSide());
    }
  }


// mit den folgenden Definitionen wird die RunNmbr missbraucht
#define RN_PARTDEF  1    // muss als 1. freier Parameter uebergeben werden
#define RN_STOW     2
#define RN_ROTCENT  3
#define RN_SOFTED   4
#define RN_CUTED    5
#define RN_GRPVAR   6
#define RN_OBJVAR   7
#define RN_SCALE    8
#define RN_REFPT    9
#define RN_OTHER   10

// Zustaende fuer das Abarbeiten der Parameterliste
#define P_ROT 0   // Rotationszentrum moeglich
#define P_SED 1   // Weichteileditierobjekt moeglich
#define P_CED 2   // Schnitteditierobjekt moeglich
#define P_STW 3   // screen to world Matrix moeglich
#define P_GRP 4   // Untergruppe oder Objekt moeglich
#define P_OBJ 5   // Objekt der Gruppe oder scale following Matrix moeglich
#define P_SCM 6   // nur Referenzpunkt moeglich
#define P_SCO 7   // neue scale following oder zugehoerige Objekte moeglich

void StoreExtraInfo(mdiChild *c,LPDBRECORD FAR *xRec,LPWORD xTableInd)
  {
  LPCONNEXTRAINFO ei = c->_GetRecExtra();
  if (ei != NULL) {
    int myAnzTables = 0;
    int ActTable;
    for (int i = 0; i < ei->AnzTables(); i++) {
      if ((ei->i.t[i].TableInd != 3) &&
          (ei->i.t[i].TableInd != 4)) {
        ActTable = i;
        myAnzTables++;
        }
      }
    if (myAnzTables > 0) {
      DBWIN_ASSERT (myAnzTables == 1) ;
      *xRec = ei->i.t[ActTable].r;
      *xTableInd = ei->i.t[ActTable].TableInd;
      }
    }
  }

BOOL Vto_DefineGroup(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Vto_DefineGroup_param FAR *par = (Vto_DefineGroup_param FAR *)param;
  Vto_GrpId tempid;
  int num_pars = (par->ParSize - (sizeof(Vto_DefineGroup_param) - sizeof(DWORD))) / sizeof(DWORD);

  if (mode & EM_LOAD) {
    LPDWORD lpid = LPDWORD (c->ReadlData (par->grpid));
    DBWIN_ASSERT (lpid != NULL);
    DWORD actgrpid = (*lpid);
    DBWIN_ASSERT(v->group->GetGroup(actgrpid) == NULL);
    if (num_pars == 0) {
      tempid.GrpId = 0;
      tempid.LastAction = ACT_DEFINED;
      tempid.oldGrpId = 0;
      }
    else {
      par->partypes = (LPSTR)GetGlobMem(num_pars);
      LPVTOGRP grp = new Vto_Group(par,c);
      StoreExtraInfo (c,&(grp->xRec),&(grp->xTableInd));
      grp->next = v->group;
      v->group = grp;
      float FAR *lpscfact = (float FAR *)c->ReadData(par->scfactR, par->scfactI);
      if ((lpscfact != NULL) && (*lpscfact < 1.0E9)) {
        grp->scfact = *lpscfact;
        }
      else {
        grp->scfact = float(1.0);
        }
      int siz;
      LPVOID dat;
      ftr2 tempsc;
      int tempparnum;
      ffpt temprp;
      int state = P_ROT;
      for (int act_par = (grp->modeflags & GRP_PARTABLE) ? 1 : 0;
           act_par < num_pars;
           act_par++) {
        dat = c->ReadData(par->Ref[act_par].R, par->Ref[act_par].I);
        siz = (dat == NULL) ? 0 : GetBlockSize(dat);
        if (state == P_ROT) {
          state = P_SED;
          if (grp->modeflags & GRP_ROTABLE) {
            DBWIN_ASSERT(siz == sizeof(LPFRMOBJ));
            grp->RotObj = *((LPFRMOBJ FAR *)dat);
            continue;
            }
          }
        if (state == P_SED) {
          state = P_CED;
          if (grp->modeflags & GRP_SOFTEDIT) {
            DBWIN_ASSERT(siz == sizeof(LPFRMOBJ));
            grp->SoftObj = *((LPFRMOBJ FAR *)dat);
            continue;
            }
          }
        if (state == P_CED) {
          state = P_STW;
          if (grp->modeflags & GRP_CUTABLE) {
            DBWIN_ASSERT(siz == sizeof(LPFRMOBJ));
            grp->CutObj = *((LPFRMOBJ FAR *)dat);
            continue;
            }
          }
        if (state == P_STW) {
          state = P_GRP;
          if ((siz == 0) || (siz == sizeof(tr2))) {  // screentoworld
            par->partypes[act_par] = RN_STOW;
            if (siz == 0)
              grp->s_to_w.A[0][0] = float(1.0E10);
            else
              lmemcpy(&grp->s_to_w, dat, sizeof(tr2));
            continue;
            }
          }
        if (((siz == 0) && (state != P_SCM)) || (siz == sizeof(tr2))) {
          // scale following Transformationsmatrix
          par->partypes[act_par] = RN_SCALE;
          DBWIN_ASSERT(state != P_SCM);  // nicht zwei Matritzen hintereinander
          if (siz == 0)
            tempsc.A[0][0] = float(1.0E10);
          else
            lmemcpy(&tempsc, dat, sizeof(ftr2));
          tempparnum = act_par;
          state = P_SCM;
          }
        else if ((siz == 0) || (siz == sizeof(fpt))) {
          par->partypes[act_par] = RN_REFPT;
          DBWIN_ASSERT(state == P_SCM);  // muss nach scale following folgen
          if (siz == 0)
            temprp.x = float(1.0E10);
          else
            lmemcpy(&temprp, dat, sizeof(ffpt));
          state = P_SCO;
          }
        else if (siz == sizeof(Vto_GrpId)) {
          par->partypes[act_par] = RN_GRPVAR;
          DBWIN_ASSERT(state == P_GRP);   // Gruppen nur am Anfang
          if (((Vto_GrpId FAR *)dat)->GrpId != 0) {
            LPVTOIDLIST id = LPVTOIDLIST(mymalloc(sizeof(Vto_IdList)));
            id->next = grp->idlist;
            grp->idlist = id;
            id->grpid = ((Vto_GrpId FAR *)dat)->GrpId;
            }
          }
        else if (siz == sizeof(LPFRMOBJ)) {
          DBWIN_ASSERT(state != P_SCM);   // nicht direkt nach scale following
          if (state == P_SCO) {
            par->partypes[act_par] = RN_OTHER;
            LPVTOOTHERLIST other = LPVTOOTHERLIST(mymalloc(sizeof(Vto_OtherObjList)));
            other->next = grp->otherlist;
            grp->otherlist = other;
            other->obj = *((LPFRMOBJ FAR *)dat);
            other->objId = par->Ref[act_par].I;
            other->sc = tempsc;
            other->sc_parnum = tempparnum;
            other->refpt = temprp;
            }
          else {
            par->partypes[act_par] = RN_OBJVAR;
            LPVTOOBJLIST obj = LPVTOOBJLIST(mymalloc(sizeof(Vto_ObjList)));
            obj->next = grp->objlist;
            grp->objlist = obj;
            obj->obj = *((LPFRMOBJ FAR *)dat);
            obj->objId = par->Ref[act_par].I;
            state = P_OBJ;
            }
          }
        else
          DBWIN_ASSERT(FALSE);
        }
      // Gruppenrotationszentrum gegebenenfalls berechnen
      CalcGrpRotCent(v, grp);
      // jetzt noch Aufteilen, wenn notwendig
      if (grp->modeflags & GRP_PARTABLE) {
        par->partypes[0] = RN_PARTDEF;
        // zuerst die Teilgruppen erzeugen
        for (LPVTOOBJLIST obj = grp->objlist; obj != NULL; obj = obj->next) {
          LPFRMOBJ o = obj->obj;
          if ((o != NULL) && (o->Initialized)) {
            DBWIN_ASSERT(o->IsCont());  // bitte nur Konturen !
            TrcContObj FAR *co = (TrcContObj FAR *)o;
            if (co->cut) {
              LPCONTPART cp = LPCONTPART(co->cc + 1);
              for (short partn = 0; partn < co->cc->num_parts; partn++) {
                DWORD pn = (DWORD)cp->part_num;
                for (LPVTOGRP part = grp->parts; part != NULL; part = part->parts)
                  if (part->grpid == pn) break;
                if (part == NULL) {
                  LPVTOGRP newgrp = new Vto_Group(par,c);
                  StoreExtraInfo (c,&(newgrp->xRec),&(newgrp->xTableInd));
                  newgrp->next = grp;
                  newgrp->grpid = pn;
                  newgrp->modeflags |= GRP_ISPART;
                  newgrp->modeflags &= ~DWORD(GRP_CUTABLE);
                  newgrp->RotObj = grp->RotObj;
                  newgrp->objlist = grp->objlist;
                  newgrp->s_to_w = grp->s_to_w;
                  newgrp->scfact = grp->scfact;
                  newgrp->parts = grp->parts;
                  grp->parts = newgrp;
                  }
                cp = LPCONTPART(LPCONTPIECE(cp + 1) + cp->num_pieces);
                }
              }
            }
          }
        // dann einzelne Objekte zuteilen
        int num_pdef = 0;
        Vto_PartDef FAR *pdef = (Vto_PartDef FAR *)(c->ReadData(par->Ref[0].R, par->Ref[0].I));
        if (pdef != NULL) {
          siz = GetBlockSize(pdef);
          DBWIN_ASSERT((siz % sizeof(Vto_PartDef)) == 0);
          num_pdef = siz / sizeof(Vto_PartDef);
          // entsprechend aufteilen
          }
        }
      // Gruppenvariable schreiben
      tempid.GrpId = grp->grpid;
      tempid.LastAction = ACT_DEFINED;
      tempid.oldGrpId = 0;
      }
    c->WriteData(par->grpR, par->grpI, &tempid, sizeof(Vto_GrpId), Offset);
    DWORD hmode = VTO_NOTSEL;
    c->WriteData(par->selmodeR, par->selmodeI, &hmode, sizeof(DWORD), Offset);
    }

  if (mode & EM_UPDATE) {
    LPDWORD lpid = LPDWORD (c->ReadlData (par->grpid));
    DBWIN_ASSERT (lpid != NULL);
    DWORD actgrpid = (*lpid);
    LPVTOGRP grp = v->group->GetGroup(actgrpid);
    if (TRUE /* c->IsUpdateFromEle(par->scfactR, par->scfactI) */ ) {
      float FAR *lpscfact = (float FAR *)c->ReadData(par->scfactR, par->scfactI);
      if ((lpscfact != NULL) && (*lpscfact < 1.0E9)) {
        grp->scfact = *lpscfact;
        }
      else {
        grp->scfact = float(1.0);
        }
      }
    DBWIN_ASSERT(par->partypes != NULL);
    for (int act_par = 0; act_par < num_pars; act_par++) {
      if (par->partypes[act_par] == 0) continue;
      if (TRUE /* c->IsUpdateFromEle(par->Ref[act_par].R, par->Ref[act_par].I) */ ) {
        int partype = par->partypes[act_par];
        if ((partype == RN_ROTCENT) || (partype == RN_SOFTED) || (partype == RN_CUTED)) {
          // kein SetConnection auf diese Parameter
          // DBWIN_ASSERT(FALSE);
          }
        else {
          DBWIN_ASSERT(grp != NULL);   // wenn update, muss Gruppe definiert sein
          LPVOID dat = c->ReadData(par->Ref[act_par].R, par->Ref[act_par].I);
          int siz = (dat == NULL) ? 0 : GetBlockSize(dat);
          if (partype == RN_PARTDEF) {
            // je nachdem, was sich geaendert hat, Gruppe neu aufteilen
            }
          else if (partype == RN_STOW) {
            DBWIN_ASSERT((siz == 0) || (siz == sizeof(tr2)));
            if (siz == 0)
              grp->s_to_w.A[0][0] = float(1.0E10);
            else
              lmemcpy(&grp->s_to_w, dat, sizeof(tr2));
            for (LPVTOGRP part = grp->parts; part != NULL; part = part->parts)
              part->s_to_w = grp->s_to_w;
            }
          else if (partype == RN_GRPVAR) {
            DBWIN_ASSERT(siz == sizeof(Vto_GrpId));
            DWORD oid = ((Vto_GrpId FAR *)dat)->oldGrpId;
            if (oid != 0) {
              LPVTOIDLIST last = NULL;
              for (LPVTOIDLIST id = grp->idlist;
                  (id != NULL) && (id->grpid != oid);
                  last = id, id = id->next);
              DBWIN_ASSERT(id != NULL);
              if (last == NULL)
                grp->idlist = id->next;
              else
                last->next = id->next;
              myfree(id);
              }
            if (((Vto_GrpId FAR *)dat)->GrpId != 0) {
              DWORD nid = ((Vto_GrpId FAR *)dat)->GrpId;
              for (LPVTOIDLIST id = grp->idlist;
                  (id != NULL) && (id->grpid != nid);
                  id = id->next);
              if (id == NULL) {
                id = LPVTOIDLIST(mymalloc(sizeof(Vto_IdList)));
                id->next = grp->idlist;
                grp->idlist = id;
                id->grpid = nid;
                }
              // else -> diese Gruppe ist schon in der Liste
              }
            }
          else if (partype == RN_OBJVAR) {
            DBWIN_ASSERT(siz == sizeof(LPFRMOBJ));
            for (LPVTOOBJLIST obj = grp->objlist;
                (obj != NULL) && (obj->objId != par->Ref[act_par].I);
                obj = obj->next);
            DBWIN_ASSERT(obj != NULL);
            obj->obj = *((LPFRMOBJ FAR *)dat);
            // wenn noetig aufteilen
            if (grp->modeflags & GRP_PARTABLE) {
              LPFRMOBJ o = obj->obj;
              if ((o != NULL) && (o->Initialized)) {
                DBWIN_ASSERT(o->IsCont());  // bitte nur Konturen !
                TrcContObj FAR *co = (TrcContObj FAR *)o;
                if (co->cut) {
                  LPCONTPART cp = LPCONTPART(co->cc + 1);
                  for (short partn = 0; partn < co->cc->num_parts; partn++) {
                    DWORD pn = (DWORD)cp->part_num;
                    for (LPVTOGRP part = grp->parts; part != NULL; part = part->parts)
                      if (part->grpid == pn) break;
                    if (part == NULL) {
                      LPVTOGRP newgrp = new Vto_Group(par,c);
                      StoreExtraInfo (c,&(newgrp->xRec),&(newgrp->xTableInd));
                      newgrp->next = grp;
                      newgrp->grpid = pn;
                      newgrp->modeflags |= GRP_ISPART;
                      newgrp->modeflags &= ~DWORD(GRP_CUTABLE);
                      newgrp->RotObj = grp->RotObj;
                      newgrp->objlist = grp->objlist;
                      newgrp->s_to_w = grp->s_to_w;
                      newgrp->scfact = grp->scfact;
                      newgrp->parts = grp->parts;
                      grp->parts = newgrp;
                      }
                    cp = LPCONTPART(LPCONTPIECE(cp + 1) + cp->num_pieces);
                    }
                  }
                }
              }
            }
          else if (partype == RN_SCALE) {
            DBWIN_ASSERT((siz == 0) || (siz == sizeof(tr2)));
            for (LPVTOOTHERLIST other = grp->otherlist;
                other != NULL;
                other = other->next) {
              if (other->sc_parnum == act_par) {
                if (siz == 0)
                  other->sc.A[0][0] = float(1.0E10);
                else
                  lmemcpy(&other->sc, dat, sizeof(ftr2));
                }
              }
            }
          else if (partype == RN_REFPT) {
            DBWIN_ASSERT((siz == 0) || (siz == sizeof(fpt)));
            // ein Parameter vorher steht scale following Matrix
            for (LPVTOOTHERLIST other = grp->otherlist;
                other != NULL;
                other = other->next) {
              if (other->sc_parnum == (act_par - 1)) {
                if (siz == 0)
                  other->refpt.x = float(1.0E10);
                else
                  lmemcpy(&other->refpt, dat, sizeof(ffpt));
                }
              }
            }
          else if (partype == RN_OTHER) {
            DBWIN_ASSERT(siz == sizeof(LPFRMOBJ));
            for (LPVTOOTHERLIST other = grp->otherlist;
                (other != NULL) && (other->objId != par->Ref[act_par].I);
                other = other->next);
            DBWIN_ASSERT(other != NULL);
            other->obj = *((LPFRMOBJ FAR *)dat);
            }
          else
            DBWIN_ASSERT(FALSE);
          }
        }
      }
    // wieder mal Rotationszentrum berechnen probieren
    CalcGrpRotCent(v, grp);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->scfactR, par->scfactI, Offset);
    for (int act_par = 0; act_par < num_pars; act_par++)
      if (par->partypes[act_par] != 0)
        c->SetConnection(par->Ref[act_par].R, par->Ref[act_par].I, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    // Gruppenvariable auf Id = 0 setzen (= nicht definiert)
    tempid.GrpId = 0;
    tempid.LastAction = ACT_DEFINED;
    tempid.oldGrpId = 0;
    LPVTOGRP last = NULL;
    LPDWORD lpid = LPDWORD (c->ReadlData (par->grpid));
    DBWIN_ASSERT (lpid != NULL);
    DWORD actgrpid = (*lpid);
    for (LPVTOGRP grp = v->group;
         (grp != NULL) && (grp->grpid != actgrpid);
         last = grp, grp = grp->next);
    if (grp != NULL) {
      tempid.oldGrpId = grp->grpid;
      if (last == NULL)
        v->group = grp->next;
      else
        last->next = grp->next;
      delete grp;
      }
    if (mode & EM_CLEAR)
      c->WriteData(par->grpR, par->grpI, &tempid, sizeof(Vto_GrpId), Offset);
    // jetzt noch die Connetions loesen
    c->ClearConnection(par->scfactR, par->scfactI, Offset);
    for (int act_par = 0; act_par < num_pars; act_par++)
      if (par->partypes[act_par] != 0)
        c->ClearConnection(par->Ref[act_par].R, par->Ref[act_par].I, Offset);
    DBWIN_ASSERT(par->partypes != NULL);
    FreeGlobMem(par->partypes);
    par->partypes = NULL;
    }

  return FALSE;
  }


BOOL Vto_OnMove(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Vto_OnMove_param FAR *par = (Vto_OnMove_param FAR *)param;

  if (mode & EM_LOAD) {
    LPVTOMOVELIST newmove = LPVTOMOVELIST(mymalloc(sizeof(Vto_MoveList)));
    newmove->grpid = c->ReadConstLong (par->grpid);
    newmove->MoveProc = par->MoveProc;
    newmove->next = v->movelist;
    v->movelist = newmove;
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    LPVTOMOVELIST last = NULL;
    LONG pgrpid = c->ReadConstLong (par->grpid);
    for (LPVTOMOVELIST ml = v->movelist; ml != NULL; ml = ml->next) {
      if ((LONG(ml->grpid) == pgrpid) && (ml->MoveProc == par->MoveProc)) {
        if (last == NULL)
          v->movelist = ml->next;
        else
          last->next = ml->next;
        myfree(ml);
        break;
        }
      last = ml;
      }
    }

  return FALSE;
  }


BOOL Vto_DrawObject(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Vto_DrawObject_param FAR *par = (Vto_DrawObject_param FAR *)param;
  DBWIN_ASSERT (c->IsConst (par->_mode));
  DBINT drwmode = *((DBINT FAR *) c->ReadlData (par->_mode));
  DBWIN_ASSERT (c->IsConst (par->_color));
  DWORD color = *((DWORD FAR *) c->ReadlData (par->_color));

  if (mode & EM_LOAD) {               // nur bei EM_LOAD
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)c->ReadData(par->objR, par->objI);
    LPFRMOBJ obj;
    if ((lpobj != NULL) && ((obj = *lpobj) != NULL) && (obj->Initialized)) {
      PaintContext pc;
      GetDocumentContext(&pc, c);
      if (drwmode == DOM_XOR)
        SetROP2(pc.hDC,R2_XORPEN);
      pc.diPen(color);
      obj->PaintTrans(&pc, c->actSide(),NULL);
      }
    }

  return FALSE;
  }


BOOL Vto_SetMode(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Vto_SetMode_param FAR *par = (Vto_SetMode_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    DWORD FAR *lpmode = (DWORD FAR *)c->ReadData(par->modeR, par->modeI);
    if (lpmode != NULL) {
      DBWIN_ASSERT((*lpmode >= M_INACTIVE) && (*lpmode <= M_CUT));
      if ((v->mode != M_INACTIVE) && (v->state != S_NONESELECTED)) {
        v->DeselectGrp();
        v->DelSelList();
        v->state = S_NONESELECTED;
        }
      v->mode = WORD(*lpmode);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->modeR, par->modeI, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->modeR, par->modeI, Offset);
    }
  return FALSE;
  }

#pragma pack(1)
struct FAR Vto_Startparam {
  WORD parSize;
  DWORD preProc;
  DWORD midProc;
  DWORD postProc;
  struct VSDT {
    LONG FNrRef;
    } r[1];
  int AnzRefs()
    { return (parSize - sizeof(*this)) / sizeof(r[0]) + 1; }
  };
#pragma pack()

BOOL Vto_ApplyCut(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    DBWIN_ASSERT(v->mode == M_CUT);
    if ((v->state == S_GRPSELECTED) && (v->actsel->grp->modeflags & GRP_CUTABLE))
      v->actsel->grp->CutObj->OnLButtonDown(0, 0, 0,c->actSide());
    }
  return FALSE;
  }


BOOL Vto_CalcAllRotCents(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    for (LPVTOGRP grp = v->group; grp != NULL; grp = grp->next)
      CalcGrpRotCent(v, grp);
    }
  return FALSE;
  }

