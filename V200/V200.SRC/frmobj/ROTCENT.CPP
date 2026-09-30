// $Header:   P:/marille/clinicum/frmobj/rev/rotcent.cpv   1.7   11 Sep 1997 19:00:58   HANNES  $
// $Log:   P:/marille/clinicum/frmobj/rev/rotcent.cpv  $
// 
//    Rev 1.7   11 Sep 1997 19:00:58   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.6   18 Aug 1997 18:05:22   Martin
// VTO Formular-faehig
// 
//    Rev 1.5   24 Mar 1996 12:12:02   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:49:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   24 Aug 1995 00:15:06   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.2   20 Mar 1995 12:14:28   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.1   10 Nov 1994 14:30:42   MARTIN
// top < bottom
// 
//    Rev 1.0   24 Jun 1994 16:45:48   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.4   13 Jan 1994 16:15:24   HANNES
// dfield inc. raus
// 
//    Rev 1.3   12 Jan 1994 11:11:50   HANNES
// Unnoetige Includes Eleminiert
// 
//    Rev 1.2   18 Oct 1993 19:56:28   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.1   15 Jun 1993 19:21:02   MARTIN
// hGFmem ausgemistet
// 
//    Rev 1.0   03 Mar 1993 15:46:04   MARTIN
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 8
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

#define CARETHANDLING_DONE
#include "cfield.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "rotcent.hpp"
DLLExport _export WINAPI RotCentObj::RotCentObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }


////////////////////////// RotCent - Objekt ///////////////////////////

void RotCentObj::GetMinMax()
  {
  int width = m.HalfPenWidth(color);
  RECT rcLogRect;
  rcLogRect.left   = px - RCENT_WIDTH - width;
  rcLogRect.right  = px + RCENT_WIDTH + width;
  rcLogRect.top    = py - ROT_LEVER_LEN - width;
  rcLogRect.bottom = py + RCENT_WIDTH + width;
  schwerx = px;
  schwery = py;
  SetLogRect (&rcLogRect, ErsteSeite());
  }


void RotCentObj::Paint(PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT(Initialized);
  if (pc->mode == DO_WORK)
    Invalidate(Seite);
  }


void RotCentObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  RotCentObj::PaintTrans(pc, Seite, NULL);
  }


void RotCentObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  int x = px;
  int x2 = px;
  int y = py;
  int y2 = py - ROT_LEVER_LEN;
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    Sc2dLog(sc, &x, &y, x, y);
    Sc2dLog(sc, &x2, &y2, x2, y2);
    }
  *pc << Line (x+RCENT_WIDTH,y-RCENT_WIDTH,x+RCENT_WIDTH,y+RCENT_WIDTH);
  *pc << Line (x+RCENT_WIDTH,y+RCENT_WIDTH,x-RCENT_WIDTH,y+RCENT_WIDTH);
  *pc << Line (x-RCENT_WIDTH,y+RCENT_WIDTH,x-RCENT_WIDTH,y-RCENT_WIDTH);
  *pc << Line (x-RCENT_WIDTH,y-RCENT_WIDTH,x+RCENT_WIDTH,y-RCENT_WIDTH);
  *pc << Line (x,y,x2,y2);
  }


BOOL RotCentObj::OnLButtonDblClk(WPARAM wP, int x, int y, int Seite)
  {
  if (wtos.A[0][0] < 1.0E9) {
    fpt hpt;
    hpt.x = m_LogToWorld(x);
    hpt.y = m_LogToWorld(y);
    tr2 invsc;
    lmemcpy(&invsc, &wtos, sizeof(tr2));
    InvSc2d(&invsc);
    Sc2d(&invsc, &hpt, &hpt);
    m.WriteData(Par()->ptR, Par()->ptI, &hpt, sizeof(fpt), 0, FALSE);
    BOOL inval = Initialized;
    if (inval) Invalidate(Seite);
    Update();
    GetMinMax();
    if (inval) Invalidate(Seite);
    }

  return FALSE;
  }


void RotCentObj::Load()
  {
  LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)(m.ReadData(Par()->hd.ObjRec, Par()->hd.ObjId));
  DBWIN_ASSERT((lpobj == NULL) || (*lpobj == NULL));
  Update();
  }


void RotCentObj::Update()
  {
  fpt FAR *pt = (fpt FAR *)(m.ReadData(Par()->ptR, Par()->ptI));
  tr2 FAR *sc = (tr2 FAR *)(m.ReadData(Par()->scR, Par()->scI));
  if (sc == NULL)
    wtos.A[0][0] = float(1.0E10);
  else
    lmemcpy(&wtos, sc, sizeof(ftr2));
  if ((pt != NULL) && (pt->x < 1.0E9) && (wtos.A[0][0] < 1.0E9)) {
    fpt hpt = *pt;
    Sc2d((tr2 FAR *)(&wtos), &hpt, &hpt);
    px = m.WorldToLog(hpt.x);
    py = m.WorldToLog(hpt.y);
    color = m.GetConstLong (Par()->rcolor);
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  }


void RotCentObj::SetConnection()
  {
  m.SetConnection (Par()->ptR, Par()->ptI, Offset());
  m.SetConnection (Par()->scR, Par()->scI, Offset());
  }


void RotCentObj::Reset(BOOL Clear)
  {
  m.ClearConnection (Par()->ptR, Par()->ptI, Offset());
  m.ClearConnection (Par()->scR, Par()->scI, Offset());
  }

