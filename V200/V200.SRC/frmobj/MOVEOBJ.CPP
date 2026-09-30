//  Implementierung der Move - Objekte (fuer "Seite 0")
//
/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/moveobj.cpv   1.10   16 Feb 1998 14:15:48   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/moveobj.cpv  $
// 
//    Rev 1.10   16 Feb 1998 14:15:48   Gerhold
// VC++5.x ... explicit ist jetzt ein Schluesselwort
// 
//    Rev 1.9   15 Dec 1997 17:59:20   Hannes
// Cursor - Handling 32 BIT
// 
//    Rev 1.8   08 Sep 1997 11:04:12   Gerhold
// WORD-Parameter in WPARAM-Parameter umgewandelt
// 
//    Rev 1.7   17 Mar 1997 16:38:44   Martin
// Trc_RectImage erweitert (2.Punkt)
// 
//    Rev 1.6   10 Jun 1996 10:12:42   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.5   04 Apr 1996 18:37:08   HANNES
// Korrekturen der GetMinMax - Funktionen, HelpLine::IsToActivate ... Prototyp
// geaendert
// 
//    Rev 1.4   24 Mar 1996 12:12:02   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 10:49:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:15:32   MARTIN
// 
//    Rev 1.1   10 Aug 1995 09:20:48   HANNES
// Invalidieren beim MoveLine::Move
// 
//    Rev 1.0   11 Jun 1995 10:04:10   MARTIN
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#define CARETHANDLING_DONE
#include "globmem.h"
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#define MODULENUM    152
#include "winass.hpp"

#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "voronoi.hpp"
#include "frmobj.hpp"
#include "image.hpp"
#include "frmobj3.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"
#include "winextra.hpp"

#define SNAPDIST 100
#define KASTL 30
#define MO_DELAY 200
#define MO_XOR_COLOR 0x0000FF00

static void DrawKastl(PaintContext *pc, int x, int y)
  {
  *pc << Line (x - KASTL, y - KASTL, x + KASTL, y - KASTL);
  *pc << Line (x + KASTL, y - KASTL, x + KASTL, y + KASTL);
  *pc << Line (x + KASTL, y + KASTL, x - KASTL, y + KASTL);
  *pc << Line (x - KASTL, y + KASTL, x - KASTL, y - KASTL);
  }

struct HelpLineList {
  struct HelpLineList FAR *next;
  HelpLine FAR *hl;
  };
typedef HelpLineList FAR *LPHLL;

static LPHLL FAR *GetHLLHead(dllChild m)
  {
  LPHLL FAR *res = (LPHLL FAR *)m.GetExtraData(DED_HELPLINELIST);
  if (res == NULL) {
    LPHLL head = NULL;
    m.PutExtraData(DED_HELPLINELIST,&head,sizeof(LPHLL));
    res = (LPHLL FAR *)m.GetExtraData(DED_HELPLINELIST);
    DBWIN_ASSERT(res != NULL);
    }
  return res;
  }

static void AddToSnapList(HelpLine FAR *hl)
  {
  LPHLL FAR *head = GetHLLHead(hl->m);
  LPHLL newhll = (LPHLL)GetGlobMem(sizeof(HelpLineList));
  newhll->hl = hl;
  newhll->next = *head;
  *head = newhll;
  }

static void RemoveFromSnapList(HelpLine FAR *hl)
  {
  LPHLL FAR *last = GetHLLHead(hl->m);
  for (LPHLL act = *last; act != NULL; act = act->next) {
    if (act->hl == hl) {
      *last = act->next;
      FreeGlobMem(act);
      break;
      }
    last = &act->next;
    }
  }

static int SnapX(dllChild m, int x)
  {
  for (LPHLL act = *GetHLLHead(m); act != NULL; act = act->next) {
    if (act->hl->type == HL_VERT) {
      if (abs(act->hl->x1 - x) < SNAPDIST) {
        x = act->hl->x1;
        break;
        }
      }
    }
  return x;
  }

static int SnapY(dllChild m, int y)
  {
  for (LPHLL act = *GetHLLHead(m); act != NULL; act = act->next) {
    if (act->hl->type == HL_HORIZ) {
      if (abs(act->hl->y1 - y) < SNAPDIST) {
        y = act->hl->y1;
        break;
        }
      }
    }
  return y;
  }

LPMOVEOBJ FrmObject::moptr()
  {
  return NULL;
  }

RECT FrmObject::GetSnapOffsets()
  {
  RECT so;
  so.left = so.right = so.top = so.bottom = 0;
  return so;
  }

RECT FrmField::GetSnapOffsets()
  {
  RECT so;
  so.left = so.right = so.bottom = 0;
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  LPFORMATMETRIC lpfm = GetFormatMetrics (m.MyHandle(),MapType,m.GetConstInt (Par()->rFormat));
  so.top = lpfm->yBaseHeight;
  return so;
  }


// Implementierung der Struktur MoveObj
/////////////////////////////////////////

BOOL MoveObj::CheckNE(LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_NE) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->top;
      hr.bottom = rcLogRect->top + 2 * KASTL;
      hr.left = rcLogRect->right - 2 * KASTL;
      hr.right = rcLogRect->right;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckSE(LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_SE) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->bottom - 2 * KASTL;
      hr.bottom = rcLogRect->bottom;
      hr.left = rcLogRect->right - 2 * KASTL;
      hr.right = rcLogRect->right;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckSW(LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_SW) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->bottom - 2 * KASTL;
      hr.bottom = rcLogRect->bottom;
      hr.left = rcLogRect->left;
      hr.right = rcLogRect->left + 2 * KASTL;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckNW(LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_NW) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->top;
      hr.bottom = rcLogRect->top + 2 * KASTL;
      hr.left = rcLogRect->left;
      hr.right = rcLogRect->left + 2 * KASTL;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckN (LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_N) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->top;
      hr.bottom = rcLogRect->top + 2 * KASTL;
      hr.left = rcLogRect->left;
      hr.right = rcLogRect->right;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckE (LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_E) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->top;
      hr.bottom = rcLogRect->bottom;
      hr.left = rcLogRect->right - 2 * KASTL;
      hr.right = rcLogRect->right;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckS (LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_S) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->bottom - 2 * KASTL;
      hr.bottom = rcLogRect->bottom;
      hr.left = rcLogRect->left;
      hr.right = rcLogRect->right;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckW (LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_W) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      RECT hr;
      hr.top = rcLogRect->top;
      hr.bottom = rcLogRect->bottom;
      hr.left = rcLogRect->left;
      hr.right = rcLogRect->left + 2 * KASTL;
      res = PtInRect (LPRECT (&hr),pt);
      }
    }
  return res;
  }

BOOL MoveObj::CheckM (LPFRMOBJ o, POINT pt)
  {
  BOOL res = FALSE;
  if (EdType & ET_M) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL)
      res = PtInRect (rcLogRect,pt);
    }
  return res;
  }

void MoveObj::DrawXOR(PaintContext *pc, RECT FAR *r)
  {
  if (EdType & ET_RECT) {
    *pc << Line (r->left, r->top, r->right, r->top);
    *pc << Line (r->right, r->top, r->right, r->bottom);
    *pc << Line (r->right, r->bottom, r->left, r->bottom);
    *pc << Line (r->left, r->bottom, r->left, r->top);
    }
  else if (EdType & ET_LINE) {
    if (r->left == -32767) {
      *pc << Line (r->left, r->top, r->right, r->top);
      }
    else if (r->top == -32767) {
      *pc << Line (r->left, r->top, r->left, r->bottom);
      }
    else if (EdType & ET_NW) {
      *pc << Line (r->left, r->top, r->right, r->bottom);
      }
    else if (EdType & ET_NE) {
      *pc << Line (r->right, r->top, r->left, r->bottom);
      }
    }
  }

void MoveObj::SetEdType(WORD et)
  {
  DBWIN_ASSERT((et & (ET_RECT | ET_LINE)) != (ET_RECT | ET_LINE));
  EdType = et;
  }

void MoveObj::SetDblClkProc(DWORD procoffs)
  {
  DblClkProc = procoffs;
  }

void MoveObj::GetMinMax(LPFRMOBJ o)
  {
  LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
  if (rcLogRect != NULL)
    InflateRect (rcLogRect, KASTL, KASTL);
  }

BOOL MoveObj::OnLButtonDown(LPFRMOBJ o, int x, int y)
  {
  BOOL res = FALSE;
  if (o->Initialized) {
    POINT mpt;
    mpt.x = x , mpt.y = y;
    if (CheckNE(o,mpt)) {
      Moving = ET_NE;
      }
    else if (CheckSE(o,mpt)) {
      Moving = ET_SE;
      }
    else if (CheckSW(o,mpt)) {
      Moving = ET_SW;
      }
    else if (CheckNW(o,mpt)) {
      Moving = ET_NW;
      }
    else if (CheckN(o,mpt)) {
      Moving = ET_N;
      }
    else if (CheckE(o,mpt)) {
      Moving = ET_E;
      }
    else if (CheckS(o,mpt)) {
      Moving = ET_S;
      }
    else if (CheckW(o,mpt)) {
      Moving = ET_W;
      }
    else if (CheckM(o,mpt)) {
      Moving = ET_M;
      }
    if (Moving) {
      StartTime = o->m.GetClock();
      StartPos.x = x;
      StartPos.y = y;
      res = TRUE;
      }
    }
  return res;
  }

void MoveObj::OnLButtonDblClk(LPFRMOBJ o, int x, int y)
  {
  if (o->Initialized) {
    POINT mpt;
    mpt.x = x;
    mpt.y = y;

    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      if (PtInRect (rcLogRect,mpt)) {
        Moving = 0;
        if (DblClkProc != 0)
          o->m.ExCuteProc(DblClkProc,0);
        }
      }
    }
  }

void MoveObj::DoActMove(LPFRMOBJ o, int x, int y, RECT FAR *r, BOOL DoXOR)
  {
  PaintContext pc;
  if (!(EdType & ET_REALTIME)) {
    GetDocumentContext(&pc, o->m);
    SetROP2(pc.hDC,R2_XORPEN);
    pc.diPen(MO_XOR_COLOR);
    if (ClearOld) {
      DrawXOR(&pc, &XORRect);
      ClearOld = FALSE;
      }
    }
  LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
  if (rcLogRect != NULL) {
    if (rcLogRect->left == -32767) {
      r->left = -32767;
      r->right = 32767;
      r->top = y;
      r->bottom = y;
      }
    else if (rcLogRect->top == -32767) {
      r->left = x;
      r->right = x;
      r->top = -32767;
      r->bottom = 32767;
      }
    else {
      r->left   = rcLogRect->left   + KASTL;
      r->right  = rcLogRect->right  - KASTL;
      r->top    = rcLogRect->top    + KASTL;
      r->bottom = rcLogRect->bottom - KASTL;
      int w = r->right - r->left;
      int h = r->bottom - r->top;
      int dx = x - StartPos.x;
      int dy = y - StartPos.y;
      RECT so = o->GetSnapOffsets();
      if (Moving & (ET_NW | ET_W | ET_SW | ET_M)) {
        r->left = SnapX(o->m, r->left + dx + so.left) - so.left;
        }
      if (Moving & (ET_NE | ET_E | ET_SE)) {
        r->right = SnapX(o->m, r->right + dx + so.right) - so.right;
        }
      if (Moving & (ET_NW | ET_N | ET_NE | ET_M)) {
        r->top = SnapY(o->m, r->top + dy + so.top) - so.top;
        }
      if (Moving & (ET_SW | ET_S | ET_SE)) {
        r->bottom = SnapY(o->m, r->bottom + dy + so.bottom) - so.bottom;
        }
      if (Moving & (ET_M)) {
        r->right = r->left + w;
        r->bottom = r->top + h;
        }
      }
    }
  if (DoXOR) {
    if (!(EdType & ET_REALTIME)) {
      XORRect = *r;
      DrawXOR(&pc, &XORRect);
      ClearOld = TRUE;
      }
    }
  }

BOOL MoveObj::OnMouseMove(LPFRMOBJ o, int x, int y, RECT FAR *r)
  {
  BOOL res = FALSE;
  if (o->Initialized && Moving && ((o->m.GetClock() - StartTime) > MO_DELAY)) {
    DoActMove(o, x, y, r, TRUE);
    res = TRUE;
    }
  return res;
  }

BOOL MoveObj::OnLButtonUp(LPFRMOBJ o, int x, int y, RECT FAR *r)
  {
  BOOL res = FALSE;
  if (o->Initialized && Moving && ((o->m.GetClock() - StartTime) > MO_DELAY)) {
    DoActMove(o, x, y, r, FALSE);
    res = TRUE;
    }
  Moving = 0;
  return res;
  }

BOOL MoveObj::OnSetCursor(LPFRMOBJ o, int x, int y)
  {
  if (o->Initialized) {
    POINT mpt;
    mpt.x = x , mpt.y = y;
    if (CheckNE(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENESW));
      return SETCURSOR_DONE ;
      }
    else if (CheckSE(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENWSE));
      return SETCURSOR_DONE ;
      }
    else if (CheckSW(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENESW));
      return SETCURSOR_DONE ;
      }
    else if (CheckNW(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENWSE));
      return SETCURSOR_DONE ;
      }
    else if (CheckN(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENS));
      return SETCURSOR_DONE ;
      }
    else if (CheckE(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZEWE));
      return SETCURSOR_DONE ;
      }
    else if (CheckS(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZENS));
      return SETCURSOR_DONE ;
      }
    else if (CheckW(o,mpt)) {
      SetCursor (LoadCursor (NULL,IDC_SIZEWE));
      return SETCURSOR_DONE ;
      }
    else if (CheckM(o,mpt)) {
      #ifdef WIN32
      SetCursor (LoadCursor (NULL,IDC_SIZEALL));
      #else
      SetCursor (LoadCursor (NULL,IDC_SIZE));
      #endif
      return SETCURSOR_DONE ;
      }
    }
  return FALSE ;
  }

void MoveObj::Paint(LPFRMOBJ o, PaintContext *pc)
  {
  if (o->IsActive) {
    LPRECT rcLogRect = o->GetLogRect (o->m.ActSide());
    if (rcLogRect != NULL) {
      int xmid = (rcLogRect->left + rcLogRect->right) / 2;
      int ymid = (rcLogRect->top + rcLogRect->bottom) / 2;
      pc->diPen (0x00FF0000);
      if (EdType & ET_N) {
        DrawKastl(pc, xmid, rcLogRect->top + KASTL);
        }
      if (EdType & ET_NE) {
        DrawKastl(pc, rcLogRect->right - KASTL, rcLogRect->top + KASTL);
        }
      if (EdType & ET_E) {
        DrawKastl(pc, rcLogRect->right - KASTL, ymid);
        }
      if (EdType & ET_SE) {
        DrawKastl(pc, rcLogRect->right - KASTL, rcLogRect->bottom - KASTL);
        }
      if (EdType & ET_S) {
        DrawKastl(pc, xmid, rcLogRect->bottom - KASTL);
        }
      if (EdType & ET_SW) {
        DrawKastl(pc,rcLogRect->left + KASTL, rcLogRect->bottom - KASTL);
        }
      if (EdType & ET_W) {
        DrawKastl(pc,rcLogRect->left + KASTL, ymid);
        }
      if (EdType & ET_NW) {
        DrawKastl(pc,rcLogRect->left + KASTL, rcLogRect->top + KASTL);
        }
      if (EdType & ET_RECT) {
        *pc << Line (rcLogRect->left + KASTL, rcLogRect->top + KASTL,
                    rcLogRect->right - KASTL, rcLogRect->top + KASTL);
        *pc << Line (rcLogRect->right - KASTL, rcLogRect->top + KASTL,
                    rcLogRect->right - KASTL, rcLogRect->bottom - KASTL);
        *pc << Line (rcLogRect->right - KASTL, rcLogRect->bottom - KASTL,
                    rcLogRect->left + KASTL, rcLogRect->bottom - KASTL);
        *pc << Line (rcLogRect->left + KASTL, rcLogRect->bottom - KASTL,
                    rcLogRect->left + KASTL, rcLogRect->top + KASTL);
        }
      }
    }
  }


// Implementierung der Klasse MoveField
/////////////////////////////////////////////

DLLExport _export WINAPI MoveField::MoveField (LPVOID p,mdiChild *c) : FrmField (p,c)
  {
  mo.SetEdType(ET_RECT | ET_E | ET_W | ET_M);
  }

LPMOVEOBJ MoveField::moptr ()
  {
  return &mo;
  }

void MoveField::GetMinMax ()
  {
  FrmField::GetMinMax();
  mo.GetMinMax(this);
  }

BOOL MoveField::OnLButtonDown (WPARAM wP,int x,int y,int Seite)
  {
  return mo.OnLButtonDown(this, x, y);
  }

BOOL MoveField::OnLButtonDblClk (WPARAM wP,int x,int y,int Seite) 
  {
  mo.OnLButtonDblClk(this, x, y);
  return FALSE;
  }

BOOL MoveField::OnMouseMove (WPARAM wP,int x,int y,int Seite)
  {
  RECT r;
  mo.OnMouseMove(this, x, y, &r);
  return FALSE;
  }

BOOL MoveField::OnLButtonUp (WPARAM wP,int x,int y,int Seite)
  {
  BOOL res = FALSE ;
  RECT r;
  if (mo.OnLButtonUp(this, x, y, &r)) {
    if (r.left > r.right) {
      int h = r.left;
      r.left = r.right;
      r.right = h;
      }
    fpt pt;
    pt.x = m_LogToWorld(r.left);
    pt.y = m_LogToWorld(r.top);
    m.WriteData(Par()->PtRec, Par()->PtId, &pt, sizeof(fpt), NULL);
    int width = r.right - r.left;
    if (width < 10) width = 10;
    m.WritelData(Par()->rWidth, &width, sizeof(int), NULL);
    }
  return res;
  }

BOOL MoveField::OnSetCursor (int x,int y,int mode)
  {
  return mo.OnSetCursor(this, x, y);
  }

BOOL MoveField::IsToActivate ()
  {
  return TRUE;
  }

void MoveField::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate(Seite);
  }

void MoveField::SetInActive (int Seite)
  {
  Invalidate(Seite);
  }

BOOL MoveField::OnKeyDown (WORD wP, int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (wP == VK_SPACE) {

      LPRECT rcLogRect = GetLogRect (Seite);
      if (rcLogRect != NULL) {
        mo.OnLButtonDblClk(this,(rcLogRect->left + rcLogRect->right) / 2,
                                (rcLogRect->top + rcLogRect->bottom) / 2);
        res = TRUE;
        }
      }
    }
  return res;
  }

BOOL MoveField::OnChar (WORD wP, int Seite)
  {
  return FALSE;
  }

BOOL MoveField::OnKeyUp (WORD wP, int Seite)
  {
  return FALSE ;
  }

void MoveField::Paint (PaintContext *pc, int Seite)
  {
  FrmField::Paint(pc, Seite);
  mo.Paint(this, pc);
  }


// Implementierung der Klasse MoveLine
/////////////////////////////////////////////

void MoveLine::SetSuitableEdType()
  {
  WORD et = ET_LINE | ET_M;
  if (Initialized) {
    if (((x1 < x2) && (y1 < y2)) || ((x1 > x2) && (y1 > y2)))
      et |= ET_NW | ET_SE;
    else
      et |= ET_NE | ET_SW;
    }
  mo.SetEdType(et);
  }

DLLExport _export WINAPI MoveLine::MoveLine (LPVOID p,mdiChild *c) : FrmLine (p,c)
  {
  mo.SetEdType(ET_LINE | ET_M);
  }

LPMOVEOBJ MoveLine::moptr ()
  {
  return &mo;
  }

void MoveLine::GetMinMax ()
  {
  FrmLine::GetMinMax();
  mo.GetMinMax(this);
  }

BOOL MoveLine::OnLButtonDown (WPARAM wP,int x,int y, int Seite)
  {
  SetSuitableEdType();
  return mo.OnLButtonDown(this, x, y);
  }

BOOL MoveLine::OnLButtonDblClk (WPARAM wP,int x,int y, int Seite) 
  {
  mo.OnLButtonDblClk(this, x, y);
  return FALSE;
  }

BOOL MoveLine::OnMouseMove (WPARAM wP,int x,int y, int Seite)
  {
  SetSuitableEdType();
  RECT r;
  mo.OnMouseMove(this, x, y, &r);
  return FALSE;
  }

BOOL MoveLine::OnLButtonUp (WPARAM wP,int x,int y, int Seite)
  {
  SetSuitableEdType();
  BOOL res = FALSE ;
  RECT r;
  if (mo.OnLButtonUp(this, x, y, &r)) {
    int x1n, y1n, x2n, y2n;
    if (((x1 < x2) && (y1 < y2)) || ((x1 > x2) && (y1 > y2))) {
      x1n = r.left;
      y1n = r.top;
      x2n = r.right;
      y2n = r.bottom;
      }
    else {
      x1n = r.right;
      y1n = r.top;
      x2n = r.left;
      y2n = r.bottom;
      }
    fpt pt;
    pt.x = m_LogToWorld(x1n);
    pt.y = m_LogToWorld(y1n);
    m.WriteData(Par()->p1Rec, Par()->p1Id, &pt, sizeof(fpt), NULL);
    pt.x = m_LogToWorld(x2n);
    pt.y = m_LogToWorld(y2n);
    m.WriteData(Par()->p2Rec, Par()->p2Id, &pt, sizeof(fpt), NULL);
    }
  return res;
  }

BOOL MoveLine::OnSetCursor (int x,int y,int mode)
  {
  SetSuitableEdType();
  return mo.OnSetCursor(this, x, y);
  }

BOOL MoveLine::IsToActivate ()
  {
  return TRUE;
  }

void MoveLine::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate(Seite);
  }

void MoveLine::SetInActive (int Seite)
  {
  Invalidate(Seite);
  }

BOOL MoveLine::OnKeyDown (WORD wP, int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (wP == VK_SPACE) {
      LPRECT rcLogRect = GetLogRect (Seite);
      if (rcLogRect != NULL) {
        mo.OnLButtonDblClk(this,(rcLogRect->left + rcLogRect->right) / 2,
                                (rcLogRect->top + rcLogRect->bottom) / 2);
        res = TRUE;
        }
      }
    }
  return res;
  }

BOOL MoveLine::OnChar (WORD wP, int Seite)
  {
  return FALSE;
  }

BOOL MoveLine::OnKeyUp (WORD wP, int Seite)
  {
  return FALSE ;
  }

void MoveLine::Paint (PaintContext *pc, int Seite)
  {
  SetSuitableEdType();
  FrmLine::Paint(pc, Seite);
  mo.Paint(this, pc);
  }


// Implementierung der Klasse MoveRect
/////////////////////////////////////////////

DLLExport _export WINAPI MoveRect::MoveRect (LPVOID p,mdiChild *c) : TrcRectangleObj (p,c)
  {
  mo.SetEdType(ET_RECT | ET_M | ET_NW | ET_SE | ET_NE | ET_SW | ET_N | ET_S | ET_W | ET_E);
  }

LPMOVEOBJ MoveRect::moptr ()
  {
  return &mo;
  }

void MoveRect::GetMinMax ()
  {
  TrcRectangleObj::GetMinMax();
  mo.GetMinMax(this);
  }

BOOL MoveRect::OnLButtonDown (WPARAM wP,int x,int y, int Seite)
  {
  return mo.OnLButtonDown(this, x, y);
  }

BOOL MoveRect::OnLButtonDblClk (WPARAM wP,int x,int y, int Seite) 
  {
  mo.OnLButtonDblClk(this, x, y);
  return FALSE;
  }

BOOL MoveRect::OnMouseMove (WPARAM wP,int x,int y, int Seite)
  {
  RECT r;
  mo.OnMouseMove(this, x, y, &r);
  return FALSE;
  }

BOOL MoveRect::OnLButtonUp (WPARAM wP,int x,int y, int Seite)
  {
  BOOL res = FALSE ;
  RECT r;
  if (mo.OnLButtonUp(this, x, y, &r)) {
    int x1n, y1n, x2n, y2n;
    if (((p1x < p2x) && (p1y < p2y)) || ((p1x > p2x) && (p1y > p2y))) {
      x1n = r.left;
      y1n = r.top;
      x2n = r.right;
      y2n = r.bottom;
      }
    else {
      x1n = r.right;
      y1n = r.top;
      x2n = r.left;
      y2n = r.bottom;
      }
    fpt pt;
    pt.x = m_LogToWorld(x1n);
    pt.y = m_LogToWorld(y1n);
    m.WriteData(Par()->l.pt1R, Par()->l.pt1I, &pt, sizeof(fpt), NULL);
    pt.x = m_LogToWorld(x2n);
    pt.y = m_LogToWorld(y2n);
    m.WriteData(Par()->l.pt2R, Par()->l.pt2I, &pt, sizeof(fpt), NULL);
    }
  return res;
  }

BOOL MoveRect::OnSetCursor (int x,int y,int mode)
  {
  return mo.OnSetCursor(this, x, y);
  }

BOOL MoveRect::IsToActivate ()
  {
  return TRUE;
  }

void MoveRect::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate(Seite);
  }

void MoveRect::SetInActive (int Seite)
  {
  Invalidate(Seite);
  }

BOOL MoveRect::OnKeyDown (WORD wP, int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (wP == VK_SPACE) {
      LPRECT rcLogRect = GetLogRect (Seite);
      mo.OnLButtonDblClk(this,(rcLogRect->left + rcLogRect->right) / 2,
                              (rcLogRect->top + rcLogRect->bottom) / 2);
      res = TRUE;
      }
    }
  return res;
  }

BOOL MoveRect::OnChar (WORD wP, int Seite)
  {
  return FALSE;
  }

BOOL MoveRect::OnKeyUp (WORD wP, int Seite)
  {
  return FALSE ;
  }

void MoveRect::Paint (PaintContext *pc, int Seite)
  {
  TrcRectangleObj::Paint(pc, Seite);
  mo.Paint(this, pc);
  }


// Implementierung der Klasse MoveRectImage
/////////////////////////////////////////////

DLLExport _export WINAPI MoveRectImage::MoveRectImage (LPVOID p,mdiChild *c) : TrcRectImageObj (p,c)
  {
  mo.SetEdType(ET_RECT | ET_M);   // einstweilen nur verschieben
  }

LPMOVEOBJ MoveRectImage::moptr ()
  {
  return &mo;
  }

void MoveRectImage::GetMinMax ()
  {
  TrcRectImageObj::GetMinMax();
  mo.GetMinMax(this);
  }

BOOL MoveRectImage::OnLButtonDown (WPARAM wP,int x,int y, int Seite)
  {
  return mo.OnLButtonDown(this, x, y);
  }

BOOL MoveRectImage::OnLButtonDblClk (WPARAM wP,int x,int y, int Seite) 
  {
  mo.OnLButtonDblClk(this, x, y);
  return FALSE;
  }

BOOL MoveRectImage::OnMouseMove (WPARAM wP,int x,int y, int Seite)
  {
  RECT r;
  mo.OnMouseMove(this, x, y, &r);
  return FALSE;
  }

BOOL MoveRectImage::OnLButtonUp (WPARAM wP,int x,int y, int Seite)
  {
  BOOL res = FALSE ;
  RECT r;
  if (mo.OnLButtonUp(this, x, y, &r)) {
    fpt pt;
    pt.x = float(int(r.left));
    pt.y = float(int(r.top));
    m.WritelData(Par()->pt, &pt, sizeof(fpt), NULL);
    }
  return res;
  }

BOOL MoveRectImage::OnSetCursor (int x,int y,int mode)
  {
  return mo.OnSetCursor(this, x, y);
  }

BOOL MoveRectImage::IsToActivate ()
  {
  return TRUE;
  }

void MoveRectImage::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate(Seite);
  }

void MoveRectImage::SetInActive (int Seite)
  {
  Invalidate(Seite);
  }

BOOL MoveRectImage::OnKeyDown (WORD wP, int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (wP == VK_SPACE) {
      LPRECT rcLogRect = GetLogRect (Seite);
      mo.OnLButtonDblClk(this,(rcLogRect->left + rcLogRect->right) / 2,
                              (rcLogRect->top + rcLogRect->bottom) / 2);
      res = TRUE;
      }
    }
  return res;
  }

BOOL MoveRectImage::OnChar (WORD wP, int Seite)
  {
  return FALSE;
  }

BOOL MoveRectImage::OnKeyUp (WORD wP, int Seite)
  {
  return FALSE ;
  }

void MoveRectImage::Paint (PaintContext *pc, int Seite)
  {
  TrcRectImageObj::Paint(pc, Seite);
  mo.Paint(this, pc);
  }


// Implementierung der Klasse HelpLine
/////////////////////////////////////////////

void HelpLine::GetTemporaryMinMax()
  {
  if (Initialized) {
    RECT rcLogRect;
    if (type == HL_HORIZ) {
      rcLogRect.left = -32767;
      rcLogRect.right = 32767;
      rcLogRect.top = y1 - KASTL;
      rcLogRect.bottom = y1 + KASTL;
      }
    else {   // HL_VERT
      rcLogRect.left = x1 - KASTL;
      rcLogRect.right = x1 + KASTL;
      rcLogRect.top = -32767;
      rcLogRect.bottom = 32767;
      }
    SetLogRect (&rcLogRect, ErsteSeite());
    }
  rcLogRectInitialized = TRUE;
  }

BOOL HelpLine::IsToPaint (int Seite, PaintContext *pc)
  {
  if (!Initialized) return FALSE ;
  return TRUE;
  }

void HelpLine::Load ()
  {
  if (Initialized)
    RemoveFromSnapList(this);
  float FAR *k = (float FAR *) m.ReadData (Par()->kRec,Par()->kId);
  DBINT FAR *t = (DBINT FAR *) m.ReadData (Par()->tRec,Par()->tId);
  LONG FAR *color = (LONG FAR *) m.ReadData (Par()->cRec,Par()->cId);
  if ((k != NULL) && (t != NULL) && (color != NULL)) {
    type = *t;
    if (type == HL_HORIZ) {
      x1 = -32767 ;    y1 = m.WorldToLog (*k) ;
      x2 =  32767 ;    y2 = m.WorldToLog (*k) ;
      }
    else {   // HL_VERT
      x1 = m.WorldToLog (*k) ;    y1 = -32767 ;
      x2 = m.WorldToLog (*k) ;    y2 =  32767 ;
      }
    diPen = *color;
    Initialized = TRUE ;
    AddToSnapList(this);
    GetTemporaryMinMax();
    Invalidate(m.ActSide());
    GetMinMax();
    }
  else
    Initialized = FALSE ;
  }

void HelpLine::Update ()
  {
  GetTemporaryMinMax();
  Invalidate(m.ActSide());
  GetMinMax();
  Load ();
  GetTemporaryMinMax();
  Invalidate(m.ActSide());
  GetMinMax();
  }

BOOL HelpLine::InvalidOnUpdate()
  {
  return FALSE;
  }

void HelpLine::SetConnection()
  {
  m.SetConnection (Par()->kRec,Par()->kId,Offset());
  m.SetConnection (Par()->tRec,Par()->tId,Offset());
  m.SetConnection (Par()->cRec,Par()->cId,Offset());
  }

void HelpLine::Reset (BOOL doClear)
  {
  GetTemporaryMinMax();
  Invalidate(m.ActSide());
  GetMinMax();
  if (Initialized)
    RemoveFromSnapList(this);
  m.ClearConnection (Par()->kRec,Par()->kId,Offset());
  m.ClearConnection (Par()->tRec,Par()->tId,Offset());
  m.ClearConnection (Par()->cRec,Par()->cId,Offset());
  }

DLLExport _export WINAPI HelpLine::HelpLine (LPVOID p,mdiChild *c) : FrmObject (p,c)
  {
  mo.SetEdType(ET_LINE | ET_M);
  }

LPMOVEOBJ HelpLine::moptr ()
  {
  return &mo;
  }

void HelpLine::GetMinMax ()
  {
  RECT rcLogRect;
  rcLogRect.left = rcLogRect.right = rcLogRect.top = rcLogRect.bottom = 0 ;
  SetLogRect (&rcLogRect, ErsteSeite());
  }

BOOL HelpLine::OnLButtonDown (WPARAM wP,int x,int y,int Seite)
  {
  GetTemporaryMinMax();
  BOOL res = mo.OnLButtonDown(this, x, y);
  GetMinMax();
  return res;
  }

BOOL HelpLine::OnLButtonDblClk (WPARAM wP,int x,int y,int Seite) 
  {
  GetTemporaryMinMax();
  mo.OnLButtonDblClk(this, x, y);
  GetMinMax();
  return FALSE;
  }

BOOL HelpLine::OnMouseMove (WPARAM wP,int x,int y,int Seite)
  {
  GetTemporaryMinMax();
  RECT r;
  mo.OnMouseMove(this, x, y, &r);
  GetMinMax();
  return FALSE;
  }

BOOL HelpLine::OnLButtonUp (WPARAM wP,int x,int y,int Seite)
  {
  BOOL res = FALSE ;
  GetTemporaryMinMax();
  RECT r;
  if (mo.OnLButtonUp(this, x, y, &r)) {
    float k;
    if (type == HL_HORIZ)
      k = m_LogToWorld(r.top);
    else     // HL_VERT
      k = m_LogToWorld(r.left);
    m.WriteData(Par()->kRec, Par()->kId, &k, sizeof(float), NULL);
    }
  GetMinMax();
  return res;
  }

BOOL HelpLine::OnSetCursor (int x,int y,int mode)
  {
  GetTemporaryMinMax();
  if (type == HL_HORIZ)
    mo.SetEdType(ET_LINE | ET_N);
  else     // HL_VERT
    mo.SetEdType(ET_LINE | ET_W);
  BOOL res = mo.OnSetCursor(this, x, y);
  mo.SetEdType(ET_LINE | ET_M);
  GetMinMax();
  return res;
  }

BOOL HelpLine::IsToActivate ()
  {
  return TRUE;
  }

void HelpLine::SetActive (int Seite, BOOL bexplicit)
  {
  GetTemporaryMinMax();
  Invalidate(Seite);
  GetMinMax();
  }

void HelpLine::SetInActive (int Seite)
  {
  GetTemporaryMinMax();
  Invalidate(Seite);
  GetMinMax();
  }

BOOL HelpLine::OnKeyDown (WORD wP, int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (wP == VK_SPACE) {
      LPRECT rcLogRect = GetLogRect (Seite);
      mo.OnLButtonDblClk(this,(rcLogRect->left + rcLogRect->right) / 2,
                              (rcLogRect->top + rcLogRect->bottom) / 2);
      res = TRUE;
      }
    }
  return res;
  }

BOOL HelpLine::OnChar (WORD wP,int Seite)
  {
  return FALSE;
  }

BOOL HelpLine::OnKeyUp (WORD wP, int Seite)
  {
  return FALSE ;
  }

void HelpLine::Paint (PaintContext *pc, int Seite)
  {
  if (Initialized) {
    pc->diPen (diPen);
    *pc << Line (x1,y1,x2,y2);
    }
  GetTemporaryMinMax();
  mo.Paint(this, pc);
  GetMinMax();
  }

