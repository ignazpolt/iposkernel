// $Header:   F:/marille/clinicum/frmobj/rev/trcobj.cpv   1.46   01 Jun 2000 02:31:04   Hannes  $
// $Log:   F:/marille/clinicum/frmobj/rev/trcobj.cpv  $
// 
//    Rev 1.46   01 Jun 2000 02:31:04   Hannes
// ContainObj: Auch einfache Werte anzeigen
// 
//    Rev 1.45   13 Sep 1999 13:54:24   Wolfgang
// 1.) Bei Loeschen von cnt immer auch PtCount auf 0 setzen.
// 
//    Rev 1.44   28 Apr 1999 19:02:04   Martin
// Marker: optionaler Parameter Skalierungsfaktor
// 
//    Rev 1.43   20 Nov 1998 10:42:54   Martin
// neue Unlock-Keys
// 
//    Rev 1.42   18 Nov 1998 18:21:56   Martin
// LT10
// 
//    Rev 1.41   05 Oct 1998 11:22:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.40   25 May 1998 13:38:28   Hannes
// 
//    Rev 1.39   08 May 1998 10:01:20   Hannes
// 
//    Rev 1.38   07 May 1998 15:24:32   Hannes
// Kreuzchen in der ContainLinie
// 
//    Rev 1.37   29 Apr 1998 20:39:22   Hannes
// 
//    Rev 1.36   27 Apr 1998 18:11:36   Hannes
// Diverse Fehlerkorrekturen an Trc_DefContain2
// 
//    Rev 1.35   27 Apr 1998 12:51:38   Hannes
// Trc_DefContain2
// 
//    Rev 1.34   21 Apr 1998 19:32:06   Hannes
// Erweiterung um den Containerbausteines
// 
//    Rev 1.33   02 Mar 1998 19:13:42   Hannes
// Trc_DefEllipse
// 
//    Rev 1.32   15 Sep 1997 20:59:28   Hannes
// Bilder mit Blobs
// 
//    Rev 1.31   11 Sep 1997 19:00:56   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.30   08 Sep 1997 11:04:38   Gerhold
// WORD-Parameter in WPARAM-Parameter umgewandelt
// 
//    Rev 1.29   18 Aug 1997 18:13:34   Martin
// VTO Formular-faehig
// 
//    Rev 1.27   16 Jul 1997 12:30:28   Martin
// Rasterbild aus BLOB
// 
//    Rev 1.26   16 Jul 1997 12:03:18   Hannes
// 
//    Rev 1.25   11 Jul 1997 15:57:38   Hannes
// 
//    Rev 1.24   11 Jul 1997 10:16:22   Hannes
// 
//    Rev 1.23   08 Jul 1997 12:00:50   Hannes
// 
//    Rev 1.22   25 Jun 1997 16:27:22   Hannes
// GetMinMax: Auf jeden Fall mitLoad
// 
//    Rev 1.21   16 Jun 1997 07:49:16   Hannes
// Ausgabe des Resultierenden Rechteckes (fuer Konvertierungszwecke)
// 
//    Rev 1.20   05 May 1997 17:24:38   Hannes
// 
//    Rev 1.19   17 Mar 1997 16:38:40   Martin
// Trc_RectImage erweitert (2.Punkt)
// 
//    Rev 1.18   13 Mar 1997 13:53:36   Hannes
// Rechteckzeichnen verbessert (damit Linien moeglich sind)
// 
//    Rev 1.17   19 Feb 1997 12:11:12   Hannes
// Rechteck so gezeichnet, dass auch die angegebene Position inkludiert ist
// 
//    Rev 1.16   17 Dec 1996 11:06:02   GERHOLD
// 32 Bit
// 
//    Rev 1.15   10 Jun 1996 10:12:44   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.14   22 May 1996 09:53:02   GERHOLD
// Aufruf von "Chg()" mit "(int FAR &)rc.." gecastet
// 
//    Rev 1.13   24 Mar 1996 12:12:10   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.12   16 Feb 1996 15:16:34   GERHOLD
// IMGOpenSoloe erst einmal #ifdef WIN32 (noch keine Library)
// 
//    Rev 1.11   02 Feb 1996 10:49:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   04 Sep 1995 15:39:28   MARTIN
// TrcRectImage: noetigenfalls ein GetMinMax beim Paint
// 
//    Rev 1.9   30 Aug 1995 11:01:56   HANNES
// Connection auf die Rotation bei Patterns
// 
//    Rev 1.8   24 Aug 1995 00:15:30   MARTIN
// 
//    Rev 1.7   14 Aug 1995 08:23:34   HANNES
// Erweiterungen SetConnection
// 
//    Rev 1.6   21 Mar 1995 16:23:32   HANNES
// 
//    Rev 1.5   20 Mar 1995 12:14:28   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.4   10 Nov 1994 14:30:36   MARTIN
// top < bottom
// 
//    Rev 1.3   20 Sep 1994 11:25:14   HANNES
// Trc_DefFilledCont
// 
//    Rev 1.2   03 Sep 1994 19:50:22   HANNES
// GetMinMaxInt ... top < bottom (fuer Editor notwendig)
// 
//    Rev 1.1   27 Jun 1994 11:11:56   MARTIN
// exportierte virtuelle Funktionen nicht mehr inline
// 
//    Rev 1.0   24 Jun 1994 16:45:50   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.24   13 Apr 1994 14:36:40   HANNES
// Update der Farbe bei MovePatterns
// 
//    Rev 1.23   20 Jan 1994 23:57:34   HANNES
// Besseren HitTest in MovePattern, SetCursor unterstuetzt
// 
//    Rev 1.22   13 Jan 1994 16:17:22   HANNES
// dfield inc. raus
// 
//    Rev 1.21   12 Jan 1994 11:11:24   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.20   18 Oct 1993 19:56:56   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.19   05 Aug 1993 13:11:48   HANNES
// Division durch 0 unterbunden (PatternBaseclass::GetBitmap)
// 
//    Rev 1.18   05 Jul 1993 14:33:20   MARTIN
// Aenderung in DefMovePattern (kein Invalidate() wenn nicht noetig)
// 
//    Rev 1.17   14 Jun 1993 17:24:16   MARTIN
// Fehlerkorrektur bei Patterns: Systemresourcen wurden weniger
// 
//    Rev 1.16   07 Jun 1993 15:10:56   MARTIN
// neues Object DefMovePattern
// 
//    Rev 1.15   03 May 1993 15:46:16   HANNES
// Einbau eines vorlauefigen Clipboard - Handlings
// 
//    Rev 1.14   22 Apr 1993 21:03:28   MARTIN
// Erweiterungen von TrcContObj fuer geschnittene Konturen
// 
//    Rev 1.13   19 Apr 1993 01:36:44   MARTIN
// Aenderungen in TrcContObj fuer geschnittene Konturen
// 
//    Rev 1.12   16 Apr 1993 19:44:12   MARTIN
// Bunte Patterns
// 
//    Rev 1.11   02 Apr 1993 17:38:28   HANNES
// Strukturbereinigung, beschleunigung
// 
//    Rev 1.10   10 Mar 1993 21:21:12   MARTIN
// Objekt DefPattern
// 
//    Rev 1.9   02 Mar 1993 20:53:34   MARTIN
// Korrektur in TrcArcObj::Update
// 
//    Rev 1.8   02 Mar 1993 19:41:22   MARTIN
// neues Objekt TrcArcObj
// 
//    Rev 1.7   24 Feb 1993 21:36:18   MARTIN
// Verwendung von Bitmaps zur schnelleren Ausgabe von
// Metafile-Objekten (TrcPattern)
// 
//    Rev 1.6   17 Feb 1993 15:23:42   MARTIN
// Umbau auf FrmObjects
// 
//    Rev 1.5   14 Feb 1993 16:10:56   MARTIN
// Verbesserung von IsToPaint (RectVisible)
// 
//    Rev 1.4   02 Feb 1993 12:04:00   MARTIN
// Trc_LineObj
// 
//    Rev 1.3   01 Feb 1993 12:01:48   MARTIN
// PaintTrans implementiert
// 
//    Rev 1.2   29 Jan 1993 21:10:42   MARTIN
// Entwicklung
// 
//    Rev 1.1   21 Jan 1993 23:47:52   MARTIN
// Trc_DefCont und Trc_DefPattern erste Version fertig.
// 
//    Rev 1.0   20 Jan 1993 16:18:10   MARTIN
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"

#include "l_bitmap.h"
#define LT_SUPPORT_GIF "78BY1jl78"
#define LT_SUPPORT_TIF "oam5302FDio"

#include "winass.hpp"
#define MODULENUM 1
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "wmfcache.hpp"


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

#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "fcontain.hpp"

DLLExport _export WINAPI TrcMarkObj::TrcMarkObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI TrcLineObj::TrcLineObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI TrcGridObj::TrcGridObj(LPVOID p, mdiChild *c) : TrcLineObj (p, c) { }
DLLExport _export WINAPI TrcArcObj::TrcArcObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI PatternBaseClass::PatternBaseClass(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI TrcPatternObj::TrcPatternObj(LPVOID p, mdiChild *c, BOOL doInv) : PatternBaseClass (p, c)
  { doInvert = doInv; }
DLLExport _export WINAPI PatternObj::PatternObj(LPVOID p, mdiChild *c) : PatternBaseClass (p, c)
  { first_call = TRUE; }
DLLExport _export WINAPI MovePatternObj::MovePatternObj(LPVOID p, mdiChild *c) : PatternObj (p, c) { }
DLLExport _export WINAPI TrcContObj::TrcContObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI TrcRectangleObj::TrcRectangleObj(LPVOID p, mdiChild *c) : TrcLineObj (p, c) { }
DLLExport _export WINAPI TrcEllipseObj::TrcEllipseObj (LPVOID p, mdiChild *c) : TrcRectangleObj (p, c) { }
DLLExport _export WINAPI TrcFilledContObj::TrcFilledContObj(LPVOID p, mdiChild *c) : TrcContObj (p, c) { }
DLLExport _export WINAPI TrcRectImageObj::TrcRectImageObj(LPVOID p, mdiChild *c) : FrmObject (p, c) { }
DLLExport _export WINAPI TrcContainObj::TrcContainObj(LPVOID p, mdiChild *c) : TrcContObj (p,c) { }
DLLExport _export WINAPI TrcContain2Obj::TrcContain2Obj(LPVOID p, mdiChild *c) : TrcContainObj (p,c) { }

//#define DO_PROFILE
#ifdef DO_PROFILE
extern BOOL UseLines () ;
extern BOOL UseFields () ;
extern BOOL UsePatterns () ;
extern BOOL UseSetconn () ;
extern BOOL UseShow () ;

extern void IncAnzFields ();
extern void IncAnzLines ();
extern void IncAnzPatterns ();
extern void IncAnzShows ();
extern void IncAnzSetData ();
extern void IncAnzGetData ();
extern void IncAnzUpdate ();
extern void IncAnzSetConnection ();
#endif

const double pi = 3.1415927464;

////////////////////////// Mark - Objekt ///////////////////////////

#define FKASTL 57.0

void TrcMarkObj::GetMinMax()
  {
  ResetLogRectList ();
  int width = m.HalfPenWidth(color);
  switch (type) {
    case MARK_SQUARE :
      width += int(FKASTL * sf);
      RECT rcLogRect;
      rcLogRect.left   = px - width;
      rcLogRect.right  = px + width;
      rcLogRect.bottom = py + width;
      rcLogRect.top    = py - width;
      SetLogRect (&rcLogRect, ErsteSeite());
      break ;
    }
  schwerx = px;
  schwery = py;
  }
  
  
void TrcMarkObj::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  TrcMarkObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcMarkObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  TrcMarkObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcMarkObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DWORD olddipen = pc->actdiPen;
  pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  int x, y;
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9))
    Sc2dLog(sc, &x, &y, px, py);
  else
    x = px, y = py;

  switch (type) {
    case MARK_SQUARE :
      {
      int KASTL = int(FKASTL * sf);
      *pc << Line (x+KASTL,y-KASTL,x+KASTL,y+KASTL);
      *pc << Line (x+KASTL,y+KASTL,x-KASTL,y+KASTL);
      *pc << Line (x-KASTL,y+KASTL,x-KASTL,y-KASTL);
      *pc << Line (x-KASTL,y-KASTL,x+KASTL,y-KASTL);
      }
      break ;
    }
  pc->diPen(olddipen);
  }


void TrcMarkObj::Load()
  {
  Update();
  }


void TrcMarkObj::Update()
  {
  fpt FAR *pt = (fpt FAR *)(m.ReadData(Par()->ptR, Par()->ptI));
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->colR, Par()->colI));
  type = m.GetConstInt (Par()->rtype);
  if (Par()->hd.par_Size >= sizeof(*Par())) {
    float *lpsf = (float *)m.ReadlData(Par()->ScaleFact);
    if (lpsf != NULL)
      sf = *lpsf;
    else
      sf = 1.0;
    }
  else
    sf = 1.0;
  if ((pt != NULL) && (pt->x < 1.0E9) && (col != NULL)) {
    px = m.WorldToLog(pt->x);
    py = m.WorldToLog(pt->y);
    color = *col;
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  }


void TrcMarkObj::SetConnection()
  {
  m.SetConnection (Par()->ptR, Par()->ptI, Offset());
  m.SetConnection (Par()->colR, Par()->colI, Offset());
  }


void TrcMarkObj::Reset(BOOL Clear)
  {
  m.ClearConnection (Par()->ptR, Par()->ptI, Offset());
  m.ClearConnection (Par()->colR, Par()->colI, Offset());
  }


////////////////////////// Line - Objekt ///////////////////////////

void TrcLineObj::GetMinMax()
  {
  RECT rcLogRect;
  ResetLogRectList ();
  int width = m.HalfPenWidth(color);
  if (p1x < p2x) {
    rcLogRect.left  = p1x - width;
    rcLogRect.right = p2x + width;
    }
  else {
    rcLogRect.left  = p2x - width;
    rcLogRect.right = p1x + width;
    }
  if (p1y > p2y) {
    rcLogRect.bottom = p1y + width;
    rcLogRect.top    = p2y - width;
    }
  else {
    rcLogRect.bottom = p2y + width;
    rcLogRect.top    = p1y - width;
    }
  schwerx = (p1x + p2x) / 2;
  schwery = (p1y + p2y) / 2;

  SetLogRect (&rcLogRect, ErsteSeite());
  }
  
  
void TrcLineObj::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  TrcLineObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcLineObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  TrcLineObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcLineObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DWORD olddipen = pc->actdiPen;
  pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    int x1, y1, x2, y2;
    Sc2dLog(sc, &x1, &y1, p1x, p1y);
    Sc2dLog(sc, &x2, &y2, p2x, p2y);
    *pc << Line (x1,y1,x2,y2);
    }
  else
    *pc << Line (p1x,p1y,p2x,p2y);
  pc->diPen(olddipen);
  }

void TrcGridObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  int cx = pc->XPHYStoLOG(1);
  int r = 0 ;
  int c = 0 ;
  for (int x = p1x ; x < p2x ; x = p1x + int (double (r) * double(dx))) {
    c = 0 ;
    for (int y = p1y ; y < p2y ; y = p1y + int (double (c) * double(dy))) {
      *pc << Line (x - cx,y,x + 2 * cx,y);
      *pc << Line (x,y - cx,x,y + 2 * cx);
      c ++ ;
      }
    r ++ ;
    }
  }

void TrcGridObj::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  TrcGridObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcGridObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  TrcGridObj::PaintTrans(pc, Seite, NULL);
  }

void TrcGridObj::Update()
  {
  float FAR *lpdx = (float FAR *)m.ReadlData(Par()->dx);
  float FAR *lpdy = (float FAR *)m.ReadlData(Par()->dy);
  if (lpdx != NULL) dx = *lpdx ;
  else              dx = (float)224.0 ;
  if (lpdy != NULL) dy = *lpdy ;
  else              dy = (float)224.0 ;
  TrcLineObj::Update();
  }

void TrcLineObj::Load()
  {
  Update();
  }


void TrcLineObj::Update()
  {
  fpt FAR *pt1 = (fpt FAR *)(m.ReadData(Par()->pt1R, Par()->pt1I));
  fpt FAR *pt2 = (fpt FAR *)(m.ReadData(Par()->pt2R, Par()->pt2I));
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->colR, Par()->colI));
  if ((pt1 != NULL) && (pt2 != NULL) &&
      (pt1->x < 1.0E9) && (pt2->x < 1.0E9) && (col != NULL)) {
    p1x = m.WorldToLog(pt1->x);
    p1y = m.WorldToLog(pt1->y);
    p2x = m.WorldToLog(pt2->x);
    p2y = m.WorldToLog(pt2->y);
    color = *col;
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  }


void TrcLineObj::SetConnection()
  {
  m.SetConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.SetConnection (Par()->pt2R, Par()->pt2I, Offset());
  m.SetConnection (Par()->colR, Par()->colI, Offset());
  }

void TrcGridObj::SetConnection()
  {
  m.SetlConnection (Par()->dx,Offset());
  m.SetlConnection (Par()->dy,Offset());
  TrcLineObj::SetConnection();
  }

void TrcLineObj::Reset(BOOL Clear)
  {
  m.ClearConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.ClearConnection (Par()->pt2R, Par()->pt2I, Offset());
  m.ClearConnection (Par()->colR, Par()->colI, Offset());
  }

void TrcGridObj::Reset(BOOL doClear)
  {
  m.ClearlConnection (Par()->dx,Offset());
  m.ClearlConnection (Par()->dy,Offset());
  TrcLineObj::Reset (doClear);
  }

/////////////////// Rectangle - Objekt /////////////////////////////
#define PS_NONE   7
void TrcRectangleObj::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcRectangleObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  PaintTrans(pc, Seite, NULL);
  }
  
void TrcRectangleObj::PaintIt(HDC hDC,int x1,int y1,int x2,int y2)
  {
  Rectangle (hDC,x1,y1,x2,y2);
  }

void TrcEllipseObj::PaintIt(HDC hDC,int x1,int y1,int x2,int y2)
  {
  Ellipse (hDC,x1,y1,x2,y2);
  }

void TrcRectangleObj::PaintTrans(PaintContext *pc,int Seite, tr2 FAR *sc)
  {
  int Style = pc->PenStyle(color) ;
  DBWIN_ASSERT(Initialized);
  DWORD olddipen = pc->actdiPen;
  HPEN OldPen;
  if (Style >= PS_NONE)
    OldPen = (HPEN)SelectObject (pc->hDC,GetStockObject (NULL_PEN));
  else
    pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  LOGBRUSH lb;
  lb.lbStyle = brushStyle;
  lb.lbColor = brushColor & 0x00FFFFFF;
  lb.lbHatch = brushHatch;
  HBRUSH hbr = CreateBrushIndirect (&lb);
  HBRUSH hOld = (HBRUSH)SelectObject (pc->hDC,hbr);
  int x1, y1, x2, y2;
  int dx = pc->XPHYStoLOG (1); // Er soll gefaelligst auch die Endpunkte einschliessen
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    Sc2dLog(sc, &x1, &y1, p1x, p1y);
    Sc2dLog(sc, &x2, &y2, p2x, p2y);
    PaintIt (pc->hDC,x1,y1,x2 + dx,y2 + dx);
    }
  else {
    int x1,x2,y1,y2;
    if ((p1x != p2x) && (p1y != p2y)) {
      if (p1x > p2x) x2 = p1x + dx, x1 = p2x ;
      else           x2 = p2x + dx, x1 = p1x ;
      if (p1y > p2y) y2 = p1y + dx, y1 = p2y ;
      else           y2 = p2y + dx, y1 = p1y ;
      PaintIt (pc->hDC,x1,y1,x2,y2);
      }
    else {
      MoveToEx (pc->hDC,p1x,p1y,NULL);
      LineTo (pc->hDC,p2x,p2y);
      }
    }
  DeleteObject(SelectObject(pc->hDC,hOld));
  if (Style >= PS_NONE)
    SelectObject (pc->hDC,OldPen);
  pc->diPen(olddipen);
  }

void TrcRectangleObj::Update ()
  {
  brushStyle = m.GetConstInt (Par()->rbrushStyle);
  brushColor = m.GetConstLong (Par()->rbrushColor);
  brushHatch = m.GetConstInt (Par()->rbrushHatch);
  TrcLineObj::Update ();
  }

void TrcRectangleObj::Reset (BOOL doClear)
  {
  TrcLineObj::Reset(doClear);
  m.ClearlConnection (Par()->rbrushStyle, Offset());
  m.ClearlConnection (Par()->rbrushColor, Offset());
  m.ClearlConnection (Par()->rbrushHatch, Offset());
  }

void TrcRectangleObj::SetConnection()
  {
  TrcLineObj::SetConnection();
  m.SetlConnection (Par()->rbrushStyle, Offset());
  m.SetlConnection (Par()->rbrushColor, Offset());
  m.SetlConnection (Par()->rbrushHatch, Offset());
  }

////////////////////////// Arc - Objekt ///////////////////////////

void TrcArcObj::GetSCos(double FAR *dres, double dx, double dy)
  {
  // 360 Grad ergibt 0.0 , 0 Grad ergibt 4.0 
  double l = hypot (dx,dy);
  if (l > 0.01) {
    double res = dx / l;
    if (dy < 0.0) 
      res = 1.0 - res;
    else
      res += 3.0 ;
    *dres = res;
    }
  else *dres = 0.0 ;
  }


BOOL TrcArcObj::VectInside(double cc, double c1, double c2)
  {
  if (c1 < c2)
    return ((cc <= c1) || (cc >= c2)) ;
  else 
    return ((cc <= c1) && (cc >= c2));
  }


void TrcArcObj::GetMinMax()
  {
  ResetLogRectList ();
  int px[6], py[6], anzpts = 0;
  // Die Randpunkte mussen auf jeden fall beruecksichtigt werden
  px[anzpts] = p1x;  py[anzpts] = p1y;  anzpts++;
  px[anzpts] = p2x;  py[anzpts] = p2y;  anzpts++;
  double c1, c2;
  GetSCos(&c1, p1x - mx, p1y - my);
  GetSCos(&c2, p2x - mx, p2y - my);
  if (VectInside(4.0, c1, c2)) {
    // pos. X - Achse gehoert dazu
    px[anzpts] = mx + r;  py[anzpts] = my;  anzpts++;
    }
  if (VectInside(3.0, c1, c2)) {
    // pos. Y - Achse gehoert dazu
    px[anzpts] = mx;  py[anzpts] = my + r;  anzpts++;
    }
  if (VectInside(2.0, c1, c2)) {
    // neg. X - Achse gehoert dazu
    px[anzpts] = mx - r;  py[anzpts] = my;  anzpts++;
    }
  if (VectInside(1.0, c1, c2)) {
    // neg. Y - Achse gehoert dazu
    px[anzpts] = mx;  py[anzpts] = my - r;  anzpts++;
    }
  int xmin, ymin, xmax, ymax;
  xmin = ymin =  32000;
  xmax = ymax = -32000;
  for (int i = 0; i < anzpts; i++) {
    if (px[i] < xmin) xmin = px[i];
    if (px[i] > xmax) xmax = px[i];
    if (py[i] < ymin) ymin = py[i];
    if (py[i] > ymax) ymax = py[i];
    }
  int width = m.HalfPenWidth(color);

  RECT rcLogRect;
  rcLogRect.left   = xmin - width;
  rcLogRect.right  = xmax + width;
  rcLogRect.top    = ymin - width;
  rcLogRect.bottom = ymax + width;
  schwerx = (rcLogRect.left + rcLogRect.right) / 2;
  schwery = (rcLogRect.bottom + rcLogRect.top) / 2;
  SetLogRect (&rcLogRect, ErsteSeite());
  }
  
  
void TrcArcObj::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  TrcArcObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcArcObj::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  TrcArcObj::PaintTrans(pc, Seite, NULL);
  }
  
  
void TrcArcObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DWORD olddipen = pc->actdiPen;
  pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    int x, y, x1, y1, x2, y2;
    Sc2dLog(sc, &x, &y, mx, my);
    Sc2dLog(sc, &x1, &y1, p1x, p1y);
    Sc2dLog(sc, &x2, &y2, p2x, p2y);
    Arc(pc->hDC, x-r, y-r, x+r, y+r, x1, y1, x2, y2);
    }
  else
    Arc(pc->hDC, mx-r, my-r, mx+r, my+r, p1x, p1y, p2x, p2y);
  pc->diPen(olddipen);
  }


void TrcArcObj::Load()
  {
  Update();
  }


void TrcArcObj::Update()
  {
  fpt FAR *mm = (fpt FAR *)(m.ReadData(Par()->mR, Par()->mI));
  fpt FAR *pt1 = (fpt FAR *)(m.ReadData(Par()->pt1R, Par()->pt1I));
  fpt FAR *pt2 = (fpt FAR *)(m.ReadData(Par()->pt2R, Par()->pt2I));
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->colR, Par()->colI));
  if ((mm != NULL) && (pt1 != NULL) && (pt2 != NULL) &&
      (mm->x < 1.0E9) && (pt1->x < 1.0E9) && (pt2->x < 1.0E9) && (col != NULL)) {
    mx = m.WorldToLog(mm->x);
    my = m.WorldToLog(mm->y);
    p1x = m.WorldToLog(pt1->x);
    p1y = m.WorldToLog(pt1->y);
    int dx = p1x - mx, dy = p1y - my;
    r = int(hypot (dx, dy));
    p2x = m.WorldToLog(pt2->x);
    p2y = m.WorldToLog(pt2->y);
    int dx2 = p2x - mx, dy2 = p2y - my;
    double r2 = hypot(dx2, dy2);
    if (r2 > 1.0E-3) {
      r2 = double(r) / r2;
      p2x = mx + int(double(dx2) * r2);
      p2y = my + int(double(dy2) * r2);
      }
    else {
      p2x = p1x;
      p2y = p1y;
      }
    color = *col;
    if ((dx != 0) || (dy != 0))
      Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  }


void TrcArcObj::SetConnection()
  {
  m.SetConnection (Par()->mR, Par()->mI, Offset());
  m.SetConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.SetConnection (Par()->pt2R, Par()->pt2I, Offset());
  m.SetConnection (Par()->colR, Par()->colI, Offset());
  }


void TrcArcObj::Reset(BOOL Clear)
  {
  m.ClearConnection (Par()->mR, Par()->mI, Offset());
  m.ClearConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.ClearConnection (Par()->pt2R, Par()->pt2I, Offset());
  m.ClearConnection (Par()->colR, Par()->colI, Offset());
  }


////////////////////////// Pattern - Objekte ///////////////////////////

////////////////////////// Basisklasse /////////////////////////////////

#define ABS(x) (((x) < 0) ? -(x) : (x))
#define RATIO_EPS 1.0E-3

void PatternBaseClass::GetBitMap(PaintContext *pc, tr2 FAR *sc)
  {
  tr2 sch;
  RECT rh;
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    Combine2d(&sch, (tr2 FAR *)(&scale), sc);
    GetMinMaxInt(&sch, &rh, pc->actdiPen);
    }
  else {
    lmemcpy(&sch, &scale, sizeof(tr2));
    LPRECT logr = GetLogRect (ErsteSeite());
    lmemcpy(&rh, logr, sizeof(RECT));
    }
  int dx, dy;
  POINT lb, rt;
  lb.x = rh.left;  lb.y = rh.bottom;
  rt.x = rh.right;  rt.y = rh.top;
  LPtoDP(pc->hDC, &lb, 1);
  LPtoDP(pc->hDC, &rt, 1);
  dx = rt.x - lb.x;  dy = rt.y - lb.y;
  int ratiomode = (sch.A[0][0] < 0.0) ? COS_NEG : COS_POS;
  ratiomode    += (sch.A[0][1] < 0.0) ? SIN_NEG : SIN_POS;
  float ratio;
  if (fabs(sch.A[0][0]) < fabs(sch.A[0][1])) {
    ratiomode += MOD_TAN;
    ratio = sch.A[0][0] / sch.A[0][1];
    }
  else {
    ratiomode += MOD_COT;
    ratio = sch.A[0][1] / sch.A[0][0];
    }
  if (hBitmap) {
    BOOL freebm = TRUE;
    int xdiff = bmdx - dx;  int ydiff = bmdy - dy;
    if ((oldpenstyle == (pc->actdiPen & 0xFF000000)) &&
        (ABS(xdiff) <= 1) && (ABS(ydiff) <= 1)) {
      if (QUADRANT(ratiomode) == QUADRANT(oldratiomode)) {
        if (TANORCOT(ratiomode) == TANORCOT(oldratiomode))
          freebm = fabs(ratio - oldratio) > RATIO_EPS;
        else
          if (fabs(fabs(ratio) - 1.0) < 0.1)  // ca. 45 Grad usw.
            freebm = fabs((1.0 / ratio) - oldratio) > RATIO_EPS;
        }
      }
    if (freebm)
      FreeBitMap();
    }
  bmx = (dx < 0) ? rh.right : rh.left;
  bmy = (dy < 0) ? rh.top : rh.bottom;
  if (!hBitmap) {
    oldpenstyle = pc->actdiPen & 0xFF000000;
    bmdx = dx;
    bmdy = dy;
    oldratio = ratio;
    oldratiomode = ratiomode;
    tr2 sctobitmap;
    if ((rh.right != rh.left) && (rh.top != rh.bottom)) {
      sctobitmap.A[0][0] = float(bmdx) / float(rh.right - rh.left);
      sctobitmap.A[1][1] = float(bmdy) / float(rh.top - rh.bottom);
      }
    else {
      // Irgend etwas muss gegen den floatingpoint - Error getan werden
      sctobitmap.A[0][0] = float(1.0) ;
      sctobitmap.A[1][1] = float(1.0) ;
      }
    sctobitmap.A[0][1] = sctobitmap.A[1][0] = float(0.0);
    sctobitmap.B[0] = float(-bmx) * sctobitmap.A[0][0];
    sctobitmap.B[1] = float(-bmy) * sctobitmap.A[1][1];
    Combine2d(&sch, &sch, &sctobitmap);
    PaintContext mem(pc, BLACK_PEN, BLACK_BRUSH);
    hBitmap = CreateBitmap(ABS(bmdx)+1, ABS(bmdy)+1, 1, 1, NULL);
    hBitmap = (HBITMAP)SelectObject(mem.hDC, hBitmap);
    Rectangle(mem.hDC, 0, 0, ABS(bmdx)+1, ABS(bmdy)+1);
    WORD tmode = TRANSLATE_PEN;
    mem.ScaledMetaOut(hmf, &sch, tmode, pc->actdiPen | 0x00FFFFFF, 0);
    hBitmap = (HBITMAP)SelectObject(mem.hDC, hBitmap);
    }
  }


void PatternBaseClass::FreeBitMap()
  {
  if (hBitmap) {
    DeleteObject(hBitmap);
    hBitmap = 0;
    }
  }


void PatternBaseClass::GetMinMaxInt(tr2 FAR *sc, RECT FAR *r, DWORD col)
  {
  fpt pe[4];
  pe[0].x = pe[3].x = float(rmf.left);
  pe[1].x = pe[2].x = float(rmf.right);
  pe[0].y = pe[1].y = float(rmf.top);
  pe[2].y = pe[3].y = float(rmf.bottom);
  float xmin, ymin, xmax, ymax;
  xmin = ymin = float(1.0E10);
  xmax = ymax = float(-1.0E10);
  for (int i = 0; i < 4; i++) {
    Sc2d (sc, pe+i, pe+i);
    if (pe[i].x > xmax) xmax = pe[i].x;
    if (pe[i].x < xmin) xmin = pe[i].x;
    if (pe[i].y > ymax) ymax = pe[i].y;
    if (pe[i].y < ymin) ymin = pe[i].y;
    }
  int width = m.HalfPenWidth(col);
  r->left   = int(xmin) - width;
  r->right  = int(xmax) + width;
  r->top    = int(ymin) - width;
  r->bottom = int(ymax) + width;
  }
  
  
void PatternBaseClass::GetMinMax()
  {
  ResetLogRectList ();
  RECT rcLogRect;
  GetMinMaxInt((tr2 FAR *)(&scale), &rcLogRect, color);
  schwerx = rcLogRect.left / 2 + rcLogRect.right / 2;
  schwery = rcLogRect.bottom / 2 + rcLogRect.top / 2;
  SetLogRect (&rcLogRect,ErsteSeite());
  }


void PatternBaseClass::Paint(PaintContext *pc, int Seite)
  {
  pc->diPen(color);
  PatternBaseClass::PaintTrans(pc, Seite, NULL);
  }


void PatternBaseClass::PaintSel(PaintContext *pc, int Seite)
  {
  pc->diPen(m.SelColor());
  PatternBaseClass::PaintTrans(pc, Seite, NULL);
  }


void DrawMonoBitMap(HDC hDC, HBITMAP hBitmap, int x, int y, DWORD color, BOOL xor)
  {
  int oldhDC = SaveDC(hDC);
  POINT dp;
  dp.x = x;
  dp.y = y;
  LPtoDP(hDC, &dp, 1);
  SetMapMode(hDC, MM_TEXT);
  DPtoLP(hDC, &dp, 1);
  HDC hdcTemp = CreateCompatibleDC(hDC);
  HBITMAP oldTemp = (HBITMAP)SelectObject(hdcTemp, hBitmap);
  BITMAP bm;
  POINT ptSize;
  GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
  ptSize.x = bm.bmWidth;
  ptSize.y = bm.bmHeight;
  DPtoLP(hdcTemp, &ptSize, 1);   // ???? (aus Beispiel uebernommen)
  HDC hdcScreen = CreateCompatibleDC(hDC);
  HBITMAP bmScreen = CreateCompatibleBitmap(hDC, ptSize.x, ptSize.y);
  bmScreen = (HBITMAP)SelectObject(hdcScreen, bmScreen);
  BitBlt(hdcScreen, 0, 0, ptSize.x, ptSize.y, hDC, dp.x, dp.y, SRCCOPY);
  // die folgende Zeile ist notwendig, um zu verhindern, dass das
  // CreateSolidBrush ein Muster erzeugt (eine Art dithering),
  // falls die gewuenschte Farbe nicht verfuegbar ist
  color = GetNearestColor(hDC, color & 0x00FFFFFF);
  HBRUSH hBrush = CreateSolidBrush(color & 0x00FFFFFF);
  hBrush = (HBRUSH)SelectObject(hdcScreen, hBrush);
  BitBlt(hdcScreen, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
    xor ? 0x6A01E9 : 0xE20746);
  hBrush = (HBRUSH)SelectObject(hdcScreen, hBrush);
  DeleteObject(hBrush);
  BitBlt(hDC, dp.x, dp.y, ptSize.x, ptSize.y, hdcScreen, 0, 0, SRCCOPY);
  SelectObject(hdcTemp, oldTemp);
  DeleteObject(SelectObject(hdcScreen, bmScreen));
  DeleteDC(hdcTemp);
  DeleteDC(hdcScreen);
  RestoreDC(hDC, oldhDC);
  }


void PatternBaseClass::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  DBWIN_ASSERT(Initialized);
  DWORD olddipen = pc->actdiPen;
  pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  if ((!trans_color) || (pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)) {
    tr2 sct;
    if ((sc != NULL) && (sc->A[0][0] < 1.0E9))
      Combine2d(&sct, (tr2 FAR *)(&scale), sc);
    else
      lmemcpy (&sct, &scale, sizeof(tr2));
    WORD tmode = trans_color ? TRANSLATE_PEN : 0;
    pc->ScaledMetaOut (hmf, &sct, tmode, pc->actdiPen, 0);
    }
  else {
    GetBitMap(pc, sc);
    DrawMonoBitMap(pc->hDC, hBitmap, bmx, bmy, pc->actdiPen, GetROP2(pc->hDC) == R2_XORPEN);
    }
  pc->diPen(olddipen);
  }
  

void PatternBaseClass::Load()
  {
  WORD picR, picI;
  trans_color = GetPicRef(&picR, &picI);
  hmf = GetHMF (picR, picI);
  PaintContext pchlp (m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
  pchlp.GetMaxInfo (hmf,(RECT FAR *)(&rmf));
  hBitmap = 0;
  PatternBaseClass::Update();
  }


void PatternBaseClass::Update()
  {
  LONG FAR *col = NULL;
  if (trans_color) {
    WORD colR, colI;
    GetColRef(&colR, &colI);
    col = (LONG FAR *)(m.ReadData(colR, colI));
    }
  if ((!trans_color) || (col != NULL)) {
    if (Initialized && hBitmap) {
      if (OtherUpdate())
        FreeBitMap();
      }
    else
      OtherUpdate();
    color = trans_color ? *col : 0x0F000000;
    }
  else {
    if (Initialized && hBitmap)
      FreeBitMap();
    Initialized = FALSE;
    }
  }


void PatternBaseClass::SetConnection()
  {
  if (trans_color) {
    WORD colR, colI;
    GetColRef(&colR, &colI);
    m.SetConnection (colR, colI, Offset());
    }
  OtherSetConn();
  }


void PatternBaseClass::Reset(BOOL Clear)
  {
  DelHMF(hmf);
  FreeBitMap();
  if (trans_color) {
    WORD colR, colI;
    GetColRef(&colR, &colI);
    m.ClearConnection (colR, colI, Offset());
    }
  OtherClearConn();
  }


BOOL PatternBaseClass::GetPicRef(WORD FAR *picR, WORD FAR *picI)
  {
  DBWIN_ASSERT(FALSE);   // muss zur Verfuegung stehen !
  return FALSE;
  }


void PatternBaseClass::GetColRef(WORD FAR *colR, WORD FAR *colI)
  {
  DBWIN_ASSERT(FALSE);   // muss zur Verfuegung stehen !
  }


BOOL PatternBaseClass::OtherUpdate()
  {
  DBWIN_ASSERT(FALSE);   // muss zumindest scale richtig setzen
  Initialized = FALSE;
  return TRUE;
  }


////////////////////////// TrcPatternObj /////////////////////////////////

BOOL TrcPatternObj::GetPicRef(WORD FAR *picR, WORD FAR *picI)
  {
  *picR = Par()->picR;
  *picI = Par()->picI;
  return Par()->hd.par_Size >= sizeof(*Par());
  }


void TrcPatternObj::GetColRef(WORD FAR *colR, WORD FAR *colI)
  {
  DBWIN_ASSERT(trans_color);
  *colR = Par()->colR;
  *colI = Par()->colI;
  }


void TrcPatternObj::CalcPatScale()
  {
  fpt mp1, mp2, p1n, p2n;

  DBINT FAR *lpx1 = (DBINT FAR *) m.ReadlData (Par()->rx1);
  DBINT FAR *lpy1 = (DBINT FAR *) m.ReadlData (Par()->ry1);
  DBINT FAR *lpx2 = (DBINT FAR *) m.ReadlData (Par()->rx2);
  DBINT FAR *lpy2 = (DBINT FAR *) m.ReadlData (Par()->ry2);
  DBWIN_ASSERT ((lpx1 != NULL) && (lpy1 != NULL) && (lpx2 != NULL) && (lpy2 != NULL)) ;
  mp1.x = float(*lpx1);  mp1.y = float(*lpy1);
  mp2.x = float(*lpx2);  mp2.y = float(*lpy2);
  p1n.x = float(p1x);  p1n.y = float(p1y);
  p2n.x = float(p2x);  p2n.y = float(p2y);
  if (doInvert)
    MScale2d((tr2 FAR *)(&scale), &mp1, &mp2, &p1n, &p2n, TRUE, -1.0);
  else
    MScale2d((tr2 FAR *)(&scale), &mp1, &mp2, &p1n, &p2n);
  }


BOOL TrcPatternObj::OtherUpdate()
  {
  BOOL RetVal = TRUE;
  fpt FAR *pt1 = (fpt FAR *)(m.ReadData(Par()->pt1R, Par()->pt1I));
  fpt FAR *pt2 = (fpt FAR *)(m.ReadData(Par()->pt2R, Par()->pt2I));
  if ((pt1 != NULL) && (pt2 != NULL) &&
      (pt1->x < 1.0E9) && (pt2->x < 1.0E9)) {
    if (Initialized) {
      int p1xn = m.WorldToLog(pt1->x);
      int p1yn = m.WorldToLog(pt1->y);
      int p2xn = m.WorldToLog(pt2->x);
      int p2yn = m.WorldToLog(pt2->y);
      if ((p1xn != p1x) || (p1yn != p1y) ||
          (p2xn != p2x) || (p2yn != p2y)) {
        p1x = p1xn;
        p1y = p1yn;
        p2x = p2xn;
        p2y = p2yn;
        CalcPatScale();
        }
      else
        RetVal = FALSE;
      }
    else {
      p1x = m.WorldToLog(pt1->x);
      p1y = m.WorldToLog(pt1->y);
      p2x = m.WorldToLog(pt2->x);
      p2y = m.WorldToLog(pt2->y);
      CalcPatScale();
      }
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  return RetVal;
  }


void TrcPatternObj::OtherSetConn()
  {
  m.SetConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.SetConnection (Par()->pt2R, Par()->pt2I, Offset());
  }


void TrcPatternObj::OtherClearConn()
  {
  m.ClearConnection (Par()->pt1R, Par()->pt1I, Offset());
  m.ClearConnection (Par()->pt2R, Par()->pt2I, Offset());
  }


////////////////////////// PatternObj /////////////////////////////////

BOOL PatternObj::GetPicRef(WORD FAR *picR, WORD FAR *picI)
  {
  *picR = Par()->picR;
  *picI = Par()->picI;
  return Par()->hd.par_Size >= sizeof(*Par());
  }


void PatternObj::GetColRef(WORD FAR *colR, WORD FAR *colI)
  {
  DBWIN_ASSERT(trans_color);
  *colR = Par()->colR;
  *colI = Par()->colI;
  }


void PatternObj::CalcPatScale()
  {
  tr2 sc;
#ifdef UEBERLEGT
  if (first_call) {
#endif
    first_call = FALSE;
    // Verschiebung, sodass Mittelpunkt von rmf Nullpunkt
    fix_sc.A[0][0] = fix_sc.A[1][1] = float(1.0);
    fix_sc.A[0][1] = fix_sc.A[1][0] = float(0.0);
    fix_sc.B[0] = ((float)rmf.left + (float)rmf.right) / (float)-2.0;
    fix_sc.B[1] = ((float)rmf.bottom + (float)rmf.top) / (float)-2.0;
    // Skalierung um xfact und yfact abhaengig von Mappingmode
    float dispfact, yfact;
    int MapType;
    m.GetDocInfo (GETMAPTYPE,0,&MapType);
    if (MapType == MAPTYPE_GEOMETRIC)
      dispfact = float(0.25),  yfact = float(1.0);
    else
      dispfact = float(0.5669291339), yfact = float(-1.0);
    sc.A[0][0] = m.GetConstFloat (Par()->_xfact) * dispfact;
    sc.A[1][1] = m.GetConstFloat (Par()->_yfact) * dispfact * yfact;
    sc.A[0][1] = sc.A[1][0] = float(0.0);
    sc.B[0] = float(0.0);  sc.B[1] = float(0.0);
    Combine2d((tr2 FAR *)(&fix_sc), (tr2 FAR *)(&fix_sc), &sc);
    // Rotation um den Winkel ang
    float FAR *lpang = (float FAR *) m.ReadlData (Par()->_ang) ;
    float ang ;
    if (lpang != NULL)
      ang = *lpang ;
    else
      ang = float(0.0) ;
    float cosang = (float)cos(ang * yfact * (pi / 180.0));
    float sinang = (float)sin(ang * yfact * (pi / 180.0));
    sc.A[0][0] = sc.A[1][1] = cosang;
    sc.A[0][1] = -(sc.A[1][0] = sinang);
    Combine2d((tr2 FAR *)(&fix_sc), (tr2 FAR *)(&fix_sc), &sc);
#ifdef UEBERLEGT
    }
#endif
  // Verschieben auf den Punkt pt
  sc.A[0][0] = sc.A[1][1] = float(1.0);
  sc.A[0][1] = sc.A[1][0] = float(0.0);
  sc.B[0] = float(px);  sc.B[1] = float(py);
  Combine2d((tr2 FAR *)(&scale), (tr2 FAR *)(&fix_sc), &sc);
  }


BOOL PatternObj::OtherUpdate()
  {
  BOOL RetVal = TRUE;
  fpt FAR *pt = (fpt FAR *)(m.ReadData(Par()->ptR, Par()->ptI));
  if ((pt != NULL) && (pt->x < 1.0E9)) {
#ifdef UEBERLEGT
    if (Initialized) {
      int pxn = m.WorldToLog(pt->x);
      int pyn = m.WorldToLog(pt->y);
      if ((pxn != px) || (pyn != py)) {
        px = pxn;
        py = pyn;
        CalcPatScale();
        }
//      else                 sollte sich nie aendern !
        RetVal = FALSE;
      }
    else {
#endif
      px = m.WorldToLog(pt->x);
      py = m.WorldToLog(pt->y);
      CalcPatScale();
#ifdef UEBERLEGT
      }
#endif
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  return RetVal;
  }


void PatternObj::OtherSetConn()
  {
  m.SetConnection (Par()->ptR, Par()->ptI, Offset());
  m.SetlConnection (Par()->_ang, Offset());
  }


void PatternObj::OtherClearConn()
  {
  m.ClearConnection (Par()->ptR, Par()->ptI, Offset());
  m.ClearlConnection (Par()->_ang, Offset());
  }


////////////////////////// MovePatternObj /////////////////////////////////

BOOL MovePatternObj::GetPicRef(WORD FAR *picR, WORD FAR *picI)
  {
  *picR = Par()->picR;
  *picI = Par()->picI;
  return Par()->hd.par_Size >= sizeof(*Par());
  }


void MovePatternObj::GetColRef(WORD FAR *colR, WORD FAR *colI)
  {
  DBWIN_ASSERT(trans_color);
  *colR = Par()->colR;
  *colI = Par()->colI;
  }


void MovePatternObj::CalcPatScale()
  {
  // zuerst Matrix ohne Verschiebung bestimmen
  PatternObj::CalcPatScale();
  // Verschieben um die aktuellen Verschiebungswerte
  tr2 sc;
  sc.A[0][0] = sc.A[1][1] = float(1.0);
  sc.A[0][1] = sc.A[1][0] = float(0.0);
  sc.B[0] = (move_mode & MP_SHOWHORIZ) ? dx : (float)0.0;
  sc.B[1] = (move_mode & MP_SHOWVERT) ? dy : (float)0.0;
  Combine2d((tr2 FAR *)(&scale), (tr2 FAR *)(&scale), &sc);
  }


void MovePatternObj::Load()
  {
  from_load = TRUE;
  move_color = m.GetConstLong (Par()->rmove_color);
  PatternBaseClass::Load();
  }


void MovePatternObj::Update()
  {
  from_load = FALSE;
  move_color = m.GetConstLong (Par()->rmove_color);
  PatternBaseClass::Update();
  }


BOOL MovePatternObj::OtherUpdate()
  {
  BOOL RetVal = TRUE;
  RECT oldrcLogRect;
  SetRectEmpty (&oldrcLogRect);
  if (Initialized) {
    LPRECT logr = GetLogRect (ErsteSeite());
    if (logr == NULL) {
      GetMinMax();
      }
      
    if (logr != NULL)
      oldrcLogRect = *logr;
    }
  DWORD FAR *lpmode = (DWORD FAR *)m.ReadData(Par()->modeR, Par()->modeI);
  move_mode = (lpmode != NULL) ? *lpmode : 0;
  fpt FAR *pt = (fpt FAR *)(m.ReadData(Par()->ptR, Par()->ptI));
  float FAR *lpdec;
  lpdec = (float FAR *)(m.ReadData(Par()->hminR, Par()->hminI));
  hmin = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->hmaxR, Par()->hmaxI));
  hmax = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->hvalR, Par()->hvalI));
  hval = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->hfacR, Par()->hfacI));
  hfac = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)1.0;
  lpdec = (float FAR *)(m.ReadData(Par()->vminR, Par()->vminI));
  vmin = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->vmaxR, Par()->vmaxI));
  vmax = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->vvalR, Par()->vvalI));
  vval = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)0.0;
  lpdec = (float FAR *)(m.ReadData(Par()->vfacR, Par()->vfacI));
  vfac = ((lpdec != NULL) && (*lpdec < 1.0E9)) ? *lpdec : (float)1.0;
  if (hval < hmin) {
    hval = hmin;
    m.WriteData(Par()->hvalR, Par()->hvalI, &hval, sizeof(float), Offset());
    }
  if (hval > hmax) {
    hval = hmax;
    m.WriteData(Par()->hvalR, Par()->hvalI, &hval, sizeof(float), Offset());
    }
  if (vval < vmin) {
    vval = vmin;
    m.WriteData(Par()->vvalR, Par()->vvalI, &vval, sizeof(float), Offset());
    }
  if (vval > vmax) {
    vval = vmax;
    m.WriteData(Par()->vvalR, Par()->vvalI, &vval, sizeof(float), Offset());
    }
  if ((pt != NULL) && (pt->x < 1.0E9)) {
    if (Initialized) {
      int pxn = m.WorldToLog(pt->x);
      int pyn = m.WorldToLog(pt->y);
      int dxn = m.WorldToLog(hval * hfac);
      int dyn = m.WorldToLog(vval * vfac);
      if (((pxn + dxn) != (px + dx)) || ((pyn + dyn) != (py + dy))) {
        px = pxn;
        py = pyn;
        dx = dxn;
        dy = dyn;
        CalcPatScale();
        }
//      else                 sollte sich nie aendern !
        RetVal = FALSE;
      GetMinMax();
      BOOL colorChange;
      if (trans_color) {
        WORD colR, colI;
        GetColRef(&colR, &colI);
        LONG FAR *col = (LONG FAR *)(m.ReadData(colR, colI));
        colorChange = ((col == NULL) || (*col != color));
        }
      else
        colorChange = FALSE ;
      LPRECT logr = GetLogRect (ErsteSeite());
      if ((colorChange) || 
            (!lmemcmp(&oldrcLogRect, logr, sizeof(fRECT)))) {
        SetLogRect (&oldrcLogRect,ErsteSeite());
        Invalidate(m.ActSide());
        GetMinMax();
        Invalidate(m.ActSide());
        m.Rescale (logr);
        }
      }
    else {
      px = m.WorldToLog(pt->x);
      py = m.WorldToLog(pt->y);
      dx = m.WorldToLog(hval * hfac);
      dy = m.WorldToLog(vval * vfac);
      CalcPatScale();
      // if (!from_load) {
        GetMinMax();
        Invalidate(m.ActSide());
        LPRECT logr = GetLogRect (m.ActSide());
        if (logr != NULL)
          m.Rescale (logr);
      //   }
      }
    Initialized = TRUE;
    }
  else {
    if (Initialized)
      Invalidate(m.ActSide());
    Initialized = FALSE;
    }
  return RetVal;
  }


BOOL MovePatternObj::InvalidOnUpdate()
  {
  return FALSE;
  }


void MovePatternObj::OtherSetConn()
  {
  m.SetConnection (Par()->modeR, Par()->modeI, Offset());
  m.SetConnection (Par()->ptR, Par()->ptI, Offset());
  m.SetConnection (Par()->hminR, Par()->hminI, Offset());
  m.SetConnection (Par()->hmaxR, Par()->hmaxI, Offset());
  m.SetConnection (Par()->hvalR, Par()->hvalI, Offset());
  m.SetConnection (Par()->hfacR, Par()->hfacI, Offset());
  m.SetConnection (Par()->vminR, Par()->vminI, Offset());
  m.SetConnection (Par()->vmaxR, Par()->vmaxI, Offset());
  m.SetConnection (Par()->vvalR, Par()->vvalI, Offset());
  m.SetConnection (Par()->vfacR, Par()->vfacI, Offset());
  }


void MovePatternObj::OtherClearConn()
  {
  m.ClearConnection (Par()->modeR, Par()->modeI, Offset());
  m.ClearConnection (Par()->ptR, Par()->ptI, Offset());
  m.ClearConnection (Par()->hminR, Par()->hminI, Offset());
  m.ClearConnection (Par()->hmaxR, Par()->hmaxI, Offset());
  m.ClearConnection (Par()->hvalR, Par()->hvalI, Offset());
  m.ClearConnection (Par()->hfacR, Par()->hfacI, Offset());
  m.ClearConnection (Par()->vminR, Par()->vminI, Offset());
  m.ClearConnection (Par()->vmaxR, Par()->vmaxI, Offset());
  m.ClearConnection (Par()->vvalR, Par()->vvalI, Offset());
  m.ClearConnection (Par()->vfacR, Par()->vfacI, Offset());
  }


void MovePatternObj::DrawMove()
  {
  DBWIN_ASSERT(Initialized);
  PaintContext pc;
  GetDocumentContext(&pc, m);
  SetROP2(pc.hDC,R2_XORPEN);
  pc.diPen(move_color);
  tr2 sc;
  sc.A[0][0] = sc.A[1][1] = float(1.0);
  sc.A[0][1] = sc.A[1][0] = float(0.0);
  sc.B[0] = float(act_dx);  sc.B[1] = float(act_dy);
  BOOL old_trans_color = trans_color;
  trans_color = TRUE;
  PaintTrans(&pc, m.ActSide(),&sc);
  trans_color = old_trans_color;
  }


void MovePatternObj::CalcMove(int x, int y)
  {
  act_dx = x - old_mx;
  act_dy = y - old_my;
  float dhval = m_LogToWorld(act_dx) / hfac;
  if (hval + dhval < hmin) dhval = hmin - hval;
  if (hval + dhval > hmax) dhval = hmax - hval;
  act_dx = m.WorldToLog(dhval * hfac);
  float dvval = m_LogToWorld(act_dy) / vfac;
  if (vval + dvval < vmin) dvval = vmin - vval;
  if (vval + dvval > vmax) dvval = vmax - vval;
  act_dy = m.WorldToLog(dvval * vfac);
  if (!(move_mode & MP_EDITHORIZ)) act_dx = 0;
  if (!(move_mode & MP_EDITVERT)) act_dy = 0;
  }


BOOL MovePatternObj::IsToActivate ()
  {
  return (move_mode & (MP_EDITHORIZ | MP_EDITVERT)) != 0;
  }

#define DXMIN 100
inline void Chg (int FAR &x,int FAR &y)
  { 
  int dummy = x ; x = y ; y = dummy ;
  }

BOOL MovePatternObj::HitTest(int x, int y)
  {
  LPRECT logr = GetLogRect (m.ActSide());
  if (logr == NULL) return FALSE ;
  RECT rt ;
  rt = *logr ;
  if (rt.left > rt.right)
    Chg ((int FAR &)rt.left,(int FAR &)rt.right);
  if (rt.top > rt.bottom)
    Chg ((int FAR &)rt.top,(int FAR &)rt.bottom);
  int dx = rt.right - rt.left ;
  if (dx < DXMIN) {
    int x0 = (rt.right + rt.left) / 2 ;
    rt.left = x0 - DXMIN / 2;
    rt.right = x0 + DXMIN / 2;
    }
  int dy = rt.bottom - rt.top;
  if (dy < DXMIN) {
    int y0 = (rt.bottom + rt.top) / 2 ;
    rt.top = y0 - DXMIN / 2;
    rt.bottom = y0 + DXMIN / 2;
    }
  return ((x >= rt.left) && (x <= rt.right) && (y >= rt.top) && (y <= rt.bottom));
  }

HCURSOR MovePatternObj::MoveCursor ()
  {
  if (move_mode & MP_EDITHORIZ) return LoadCursor (NULL,IDC_SIZEWE);
  if (move_mode & MP_EDITVERT)  return LoadCursor (NULL,IDC_SIZENS);
  else                          return LoadCursor (NULL,IDC_ARROW);
  }

BOOL MovePatternObj::OnSetCursor (int x,int y,int mode)
  {
  if ((Initialized) && (HitTest (x,y))) {
    SetCursor (MoveCursor());
    return SETCURSOR_DONE ;
    }
  return FALSE ;
  }

DLLExport _export WINAPI ClickPatternObj::ClickPatternObj(LPVOID p, mdiChild *c) : MovePatternObj (p,c)
  {
  }

void ClickPatternObj::WriteVal ()
  {
  if (move_mode & MP_EDITHORIZ) {
    hval += m_LogToWorld(act_dx) / hfac;
    if (hval < hmin) hval = hmin;
    if (hval > hmax) hval = hmax;
    }
  if (move_mode & MP_EDITVERT) {
    vval += m_LogToWorld(act_dy) / vfac;
    if (vval < vmin) vval = vmin;
    if (vval > vmax) vval = vmax;
    m.WriteData(Par()->vvalR, Par()->vvalI, &vval, sizeof(float), Offset());
    }
  m.WriteData(Par()->hvalR, Par()->hvalI, &hval, sizeof(float), Offset());
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WritelData (RefForWrite,&done,sizeof(TRUE),Offset());
    }
  }

BOOL ClickPatternObj::OnLButtonDown(WPARAM wP, int x, int y, int Seite)
  {
  if (Initialized) {
    // Ueberpruefen, ob im gueltigen bereich
    LPRECT rcLogRect = GetLogRect (Seite);
    old_mx = (rcLogRect->left + rcLogRect->right) / 2;  
    old_my = (rcLogRect->top + rcLogRect->bottom) / 2;  
    CalcMove(x,y);
    BOOL clipped = FALSE ;
    float oldvval = vval ;
    float oldhval = hval ;
    if (move_mode & MP_EDITHORIZ) {
      hval += m_LogToWorld(act_dx) / hfac;
      if (hval < hmin) clipped = TRUE ;
      if (hval > hmax) clipped = TRUE ;
      if (move_mode & MP_EDITVERT == 0)
        if ((y < rcLogRect->top) || (y > rcLogRect->bottom)) clipped = TRUE ;
      }
    if (move_mode & MP_EDITVERT) {
      vval += m_LogToWorld(act_dy) / vfac;
      if (vval < vmin) clipped = TRUE ;
      if (vval > vmax) clipped = TRUE ;
      if (move_mode & MP_EDITHORIZ == 0)
        if ((x < rcLogRect->left) || (x > rcLogRect->right)) clipped = TRUE ;
      }
    if (!clipped) {
      moving = TRUE;
      act_dx = act_dy = 0;
      DrawMove();
      clear_old = TRUE;
      vval = oldvval ;
      hval = oldhval ;
      CalcMove(x,y);
      DrawMove();
      DenyBusyCursor();
      WriteVal ();
      vval = oldvval ;
      hval = oldhval ;
      return TRUE;
      }
    else {
      vval = oldvval ;
      hval = oldhval ;
      return FALSE;
      }
    }
  else
    return FALSE;
  }

BOOL MovePatternObj::OnLButtonDown(WPARAM wP, int x, int y, int Seite)
  {
  if ((Initialized) && (HitTest (x,y))) {
    old_mx = x;  old_my = y;
    moving = TRUE;
    act_dx = act_dy = 0;
    DrawMove();
    clear_old = TRUE;
    return TRUE;
    }
  else
    return FALSE;
  }

BOOL ClickPatternObj::OnMouseMove (WPARAM wP,int x,int y, int Seite)
  {
  BOOL res = MovePatternObj::OnMouseMove(wP,x,y,Seite);
  if (moving) {
    float oldvval = vval ;
    float oldhval = hval ;
    WriteVal ();
    vval = oldvval ;
    hval = oldhval ;
    }
  return res;
  }

BOOL MovePatternObj::OnMouseMove(WPARAM wP, int x, int y, int Seite)
  {
  if (moving) {
    if (clear_old)
      DrawMove();
    CalcMove(x, y);
    DrawMove();
    clear_old = TRUE;
    }
  return FALSE;
  }

BOOL ClickPatternObj::OnLButtonUp(WPARAM wP, int x, int y, int Seite)
  {
  if (moving) {
    AllowBusyCursor ();
    MovePatternObj::OnLButtonUp (wP,x,y,Seite);
    }
  return FALSE;
  }

BOOL MovePatternObj::OnLButtonUp(WPARAM wP, int x, int y, int Seite)
  {
  if (moving) {
    if (clear_old) {
      DrawMove();
      clear_old = FALSE;
      }
    CalcMove(x, y);
    if (move_mode & MP_EDITHORIZ) {
      hval += m_LogToWorld(act_dx) / hfac;
      if (hval < hmin) hval = hmin;
      if (hval > hmax) hval = hmax;
      m.WriteData(Par()->hvalR, Par()->hvalI, &hval, sizeof(float), 0);
      }
    if (move_mode & MP_EDITVERT) {
      vval += m_LogToWorld(act_dy) / vfac;
      if (vval < vmin) vval = vmin;
      if (vval > vmax) vval = vmax;
      m.WriteData(Par()->vvalR, Par()->vvalI, &vval, sizeof(float), 0);
      }
    m.WriteData(Par()->hvalR, Par()->hvalI, &hval, sizeof(float), Offset());
    if (RefForWrite != 0L) {
      DBINT done = TRUE ;
      m.WritelData (RefForWrite,&done,sizeof(TRUE),Offset());
      }
    moving = FALSE;
    }
  return FALSE;
  }


////////////////////////// Kontur - Objekt ///////////////////////////

void TrcContObj::GetMinMax()
  {
  DBWIN_ASSERT(PtCount > 0);
  int xmin, ymin, xmax, ymax;
  xmin = ymin =  32000;
  xmax = ymax = -32000;
  long lsx = 0, lsy = 0;
  for (int i = 0; i < int(PtCount); i++) {
    if (cnt[i].x < xmin) xmin = cnt[i].x;
    if (cnt[i].x > xmax) xmax = cnt[i].x;
    if (cnt[i].y < ymin) ymin = cnt[i].y;
    if (cnt[i].y > ymax) ymax = cnt[i].y;
    lsx += cnt[i].x;  lsy += cnt[i].y;
    }
  int width = m.HalfPenWidth(color);

  RECT rcLogRect;
  rcLogRect.left   = xmin - width;
  rcLogRect.right  = xmax + width;
  rcLogRect.top    = ymin - width;
  rcLogRect.bottom = ymax + width;
  schwerx = int(lsx / long(PtCount));  schwery = int (lsy / long(PtCount));
  SetLogRect (&rcLogRect, ErsteSeite());
  }
  

BOOL TrcContObj::GetPtToObjVect(int Ptx, int Pty, int FAR *Vectx, int FAR *Vecty)
  {
  if (cut && (act_part >= 0)) {
    long pschwerx = 0, pschwery = 0;
    int anzpts = 0;
    LPCONTPART part = LPCONTPART(cc + 1);
    for (short partn = 0; partn < cc->num_parts; partn++) {
      if (part->part_num == act_part) {
        LPCONTPIECE piece = LPCONTPIECE(part + 1);
        for (short piecen = 0; piecen < part->num_pieces; piecen++) {
          for (short ptn = piece->ptind_from; ptn <= piece->ptind_to; ptn++) {
            pschwerx += cnt[ptn].x;
            pschwery += cnt[ptn].y;
            anzpts++;
            }
          piece++;
          }
        break;
        }
      part = LPCONTPART(LPCONTPIECE(part + 1) + part->num_pieces);
      }
    if (anzpts > 0)
      pschwerx /= anzpts, pschwery /= anzpts;
    else
      return FALSE;
    *Vectx = (int)pschwerx - Ptx;
    *Vecty = (int)pschwery - Pty;
    }
  else {
    *Vectx = schwerx - Ptx;
    *Vecty = schwery - Pty;
    }
  return TRUE;
  }


void TrcContObj::Paint(PaintContext *pc, int Seite)
  {
  TrcContObj::PaintTransInt(pc, NULL, PTI_NORMAL);
  }


void TrcContObj::PaintSel(PaintContext *pc, int Seite)
  {
  TrcContObj::PaintTransInt(pc, NULL, PTI_SEL);
  }


void TrcContObj::PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc)
  {
  TrcContObj::PaintTransInt(pc, sc, PTI_TRANS);
  }


DLLExport void _export WINAPI FreeLineList(LPLINELIST l)
  {
  LPLINELIST tofree;
  while (l != NULL) {
    tofree = l;
    l = l->next;
    FreeGlobMem(tofree);
    }
  }


void TrcContObj::UseLineList(LPLINELIST FAR *lines)
  {
  linehead = lines;
  }


void TrcContObj::LineFrom(PaintContext *pc, int x, int y)
  {
  pc->PolyMoveTo(x, y);  // MoveTo kann auf jeden Fall gemacht werden
  lastx = x, lasty = y;
  }


void TrcContObj::LineTo(PaintContext *pc, short ptind, int x, int y)
  {
  if ((linehead == NULL) || (ptind < cc->num_org_pts))
    pc->PolyLineTo(x, y);  // Originalkonturpunkt -> auf jeden Fall zeichnen
  else {
    // checken, ob Linie schon gezeichnet
    for (LPLINELIST l = *linehead; l != NULL; l = l->next) {
      if ((x < l->x1) ? ((l->x1 - x) <= 1) : ((x - l->x1) <= 1))
        if ((y < l->y1) ? ((l->y1 - y) <= 1) : ((y - l->y1) <= 1))
          if ((lastx < l->x2) ? ((l->x2 - lastx) <= 1) : ((lastx - l->x2) <= 1))
            if ((lasty < l->y2) ? ((l->y2 - lasty) <= 1) : ((lasty - l->y2) <= 1))
              break;
      if ((x < l->x2) ? ((l->x2 - x) <= 1) : ((x - l->x2) <= 1))
        if ((y < l->y2) ? ((l->y2 - y) <= 1) : ((y - l->y2) <= 1))
          if ((lastx < l->x1) ? ((l->x1 - lastx) <= 1) : ((lastx - l->x1) <= 1))
            if ((lasty < l->y1) ? ((l->y1 - lasty) <= 1) : ((lasty - l->y1) <= 1))
              break;
      }
    if (l == NULL) {
      // noch nicht gezeichnet -> in die Liste einhaengen
      LPLINELIST newl = (LPLINELIST)GetGlobMem(sizeof(line_list));
      newl->x1 = lastx, newl->y1 = lasty;
      newl->x2 = x, newl->y2 = y;
      newl->next = *linehead;
      *linehead = newl;
      // und natuerlich zeichnen
      pc->PolyLineTo(x, y);
      }
    }
  lastx = x, lasty = y;
  }


void TrcContObj::PaintTransInt(PaintContext *pc, tr2 FAR *sc, int mode)
  {
  DBWIN_ASSERT(Initialized && (PtCount > 0));
  DWORD olddipen = pc->actdiPen;
  DWORD selcolor;
  if (mode == PTI_NORMAL)
    pc->diPen(color);
  else if (mode == PTI_SEL)
    pc->diPen(selcolor = (color & 0xFF000000) | (m.SelColor() & 0x00FFFFFF));
  else
    pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  int x, y;
  if ((sc != NULL) && (sc->A[0][0] < 1.0E9)) {
    DBWIN_ASSERT(mode == PTI_TRANS);
    if (cut) {
      LPCONTPART part = LPCONTPART(cc + 1);
      for (short partn = 0; partn < cc->num_parts; partn++) {
        LPCONTPIECE piece = LPCONTPIECE(part + 1);
        for (short piecen = 0; piecen < part->num_pieces; piecen++) {
          if ((act_part < 0) || (part->part_num == act_part)) {
            short ptn = piece->ptind_from;
            Sc2dLog(sc, &x, &y, cnt[ptn].x, cnt[ptn].y);
            LineFrom(pc, x, y);
            for (ptn++; ptn <= piece->ptind_to; ptn++) {
              Sc2dLog(sc, &x, &y, cnt[ptn].x, cnt[ptn].y);
              LineTo(pc, ptn, x, y);
              }
            }
          piece++;
          }
        part = LPCONTPART(piece);
        }
      LPCONTLINK link = LPCONTLINK(part);
      for (short linkn = 0; linkn < cc->num_links; linkn++) {
        BOOL draw_link = FALSE;
        short ptn = link->ptind_from;
        if ((act_part < 0) || (link->part_from == act_part))
          draw_link = TRUE, Sc2dLog(sc, &x, &y, cnt[ptn].x, cnt[ptn].y);
        else
          x = cnt[ptn].x, y = cnt[ptn].y;
        LineFrom(pc, x, y);
        ptn = link->ptind_to;
        if ((act_part < 0) || (link->part_to == act_part))
          draw_link = TRUE, Sc2dLog(sc, &x, &y, cnt[ptn].x, cnt[ptn].y);
        else
          x = cnt[ptn].x, y = cnt[ptn].y;
        if (draw_link)
          LineTo(pc, cc->num_org_pts, x, y);
        link++;
        }
      }
    else {
      Sc2dLog(sc, &x, &y, cnt[0].x, cnt[0].y);
      pc->PolyMoveTo(x, y);
      for (int i = 1; i < int(PtCount); i++) {
        Sc2dLog(sc, &x, &y, cnt[i].x, cnt[i].y);
        pc->PolyLineTo(x, y);
        }
      }
    }
  else {
    if (cut) {
      LPCONTPART part = LPCONTPART(cc + 1);
      for (short partn = 0; partn < cc->num_parts; partn++) {
        LPCONTPIECE piece = LPCONTPIECE(part + 1);
        for (short piecen = 0; piecen < part->num_pieces; piecen++) {
          if (mode == PTI_SEL) {
            if ((act_part < 0) || (part->part_num == act_part))
              pc->diPen(selcolor);
            else
              pc->diPen(color);
            }
          if ((mode != PTI_TRANS) ||
              (act_part < 0) ||
              (part->part_num == act_part)) {
            short ptn = piece->ptind_from;
            LineFrom(pc, cnt[ptn].x, cnt[ptn].y);
            for (ptn++; ptn <= piece->ptind_to; ptn++)
              LineTo(pc, ptn, cnt[ptn].x, cnt[ptn].y);
            }
          piece++;
          }
        part = LPCONTPART(piece);
        }
      LPCONTLINK link = LPCONTLINK(part);
      for (short linkn = 0; linkn < cc->num_links; linkn++) {
        LineFrom(pc, cnt[link->ptind_from].x, cnt[link->ptind_from].y);
        if (mode == PTI_SEL) {
          if ((act_part < 0) ||
              (link->part_from == act_part) ||
              (link->part_to == act_part))
            pc->diPen(selcolor);
          else
            pc->diPen(color);
          }
        if ((mode != PTI_TRANS) ||
            (act_part < 0) ||
            (link->part_from == act_part) ||
            (link->part_to == act_part))
          LineTo(pc, cc->num_org_pts, cnt[link->ptind_to].x, cnt[link->ptind_to].y);
        link++;
        }
      }
    else {
      pc->PolyMoveTo(cnt[0].x, cnt[0].y);
      for (int i = 1; i < int(PtCount); i++)
        pc->PolyLineTo(cnt[i].x, cnt[i].y);
      }
    }
  if (mode == PTI_TRANS)
    pc->diPen(olddipen);
  linehead = NULL;
  }
  
  
BOOL TrcContObj::IsCont()
  {
  return TRUE;
  }


void TrcContObj::SelectPart(short part_num)
  {
  if (cut) act_part = part_num;
  }


void TrcContObj::Load()
  {
  act_part = -1;
  linehead = NULL;
  Update();
  }


void TrcContObj::Update()
  {
  WORD oldCount;
  if (Initialized)
    oldCount = PtCount;
  else
    oldCount = 0;
  if (cc != NULL) {
    FreeGlobMem(cc);
    cc = NULL;
    }
  fpt FAR *ncnt = (fpt FAR *)(m.ReadData(Par()->cntR, Par()->cntI));
  if ((cut = is_cut(ncnt)) != FALSE) {
    LPCUTCONT cch = LPCUTCONT(ncnt);
    int header_len = sizeof(cut_cont) +
                     cch->num_parts * sizeof(cont_part) +
                     cch->num_pieces * sizeof(cont_piece) +
                     cch->num_links * sizeof(cont_link);
    cc = (LPCUTCONT)GetGlobMem(header_len);
    lmemcpy(cc, cch, header_len);
    PtCount = (GetBlockSize(ncnt) - header_len) / sizeof(fpt);
    ncnt = (fpt FAR *)(LPSTR(ncnt) + header_len);
    }
  else
    ncnt = get_cont(ncnt, (int FAR *)&PtCount);
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->colR, Par()->colI));
  if ((PtCount > 0) && (col != NULL)) {
    if (oldCount != PtCount) {
      if (cnt != NULL) FreeGlobMem(cnt);
      cnt = (LogPt FAR *)GetGlobMem(PtCount * sizeof(fpt));
      }
    for (WORD i = 0; i < PtCount; i++) {
      cnt[i].x = m.WorldToLog(ncnt[i].x);
      cnt[i].y = m.WorldToLog(ncnt[i].y);
      }
    color = *col;
    Initialized = TRUE;
    }
  else {
    if (cnt != NULL) FreeGlobMem(cnt);
    cnt = NULL;
    Initialized = FALSE;
    PtCount = 0;
    }
  // Kontur muss Update weiterleiten (fuer Aufteilung)
  LPFRMOBJ obj = this;
  m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                &obj, sizeof(LPFRMOBJ), Offset());
  }


void TrcContObj::SetConnection()
  {
  m.SetConnection (Par()->cntR, Par()->cntI, Offset());
  m.SetConnection (Par()->colR, Par()->colI, Offset());
  }


void TrcContObj::Reset(BOOL Clear)
  {
  if (cnt != NULL) FreeGlobMem(cnt);
  cnt = NULL;
  if (cc != NULL) FreeGlobMem(cc);
  cc = NULL;
  m.ClearConnection (Par()->cntR, Par()->cntI, Offset());
  m.ClearConnection (Par()->colR, Par()->colI, Offset());
  }


// ehemalige inline - Funktionen:
DLLExport void _export WINAPI PatternBaseClass::OtherSetConn() { }    // zusaetzliche Connections
DLLExport void _export WINAPI PatternBaseClass::OtherClearConn() { }  // der abgeleiteten Klassen
DLLExport BOOL _export WINAPI MovePatternObj::AnalysePar (LPSTR,LPVOID FAR *)
  { return FALSE; }

void TrcFilledContObj::Update ()
  {
  brushStyle = m.GetConstInt (Par()->rbrushStyle);
  brushColor = m.GetConstLong (Par()->rbrushColor);
  brushHatch = m.GetConstInt (Par()->rbrushHatch);
  TrcContObj::Update ();
  }

void TrcFilledContObj::Paint(PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT (!cut);
  DBWIN_ASSERT(Initialized);
  pc->diPen(color);
  DWORD olddipen = pc->actdiPen;
  HPEN OldPen;
  int Style = pc->PenStyle(color) ;
  if (Style >= PS_NONE)
    OldPen = (HPEN)SelectObject (pc->hDC,GetStockObject (NULL_PEN));
  else
    pc->diPen((color & 0xFF000000) | (pc->actdiPen & 0x00FFFFFF));
  LOGBRUSH lb;
  lb.lbStyle = brushStyle;
  lb.lbColor = brushColor & 0x00FFFFFF;
  lb.lbHatch = brushHatch;
  HBRUSH hbr = CreateBrushIndirect (&lb);
  HBRUSH hOld = (HBRUSH)SelectObject (pc->hDC,hbr);
  int oldMode = SetBkMode(pc->hDC,TRANSPARENT);
  Polygon (pc->hDC,LPPOINT(cnt),PtCount);
  SetBkMode(pc->hDC,oldMode);
  DeleteObject(SelectObject(pc->hDC,hOld));
  if (Style >= PS_NONE)
    SelectObject (pc->hDC,OldPen);
  pc->diPen(olddipen);
  }

void TrcFilledContObj::Reset (BOOL doClear)
  {
  TrcContObj::Reset(doClear);
  m.ClearlConnection (Par()->rbrushStyle, Offset());
  m.ClearlConnection (Par()->rbrushColor, Offset());
  m.ClearlConnection (Par()->rbrushHatch, Offset());
  }

void TrcFilledContObj::SetConnection()
  {
  TrcContObj::SetConnection();
  m.SetlConnection (Par()->rbrushStyle, Offset());
  m.SetlConnection (Par()->rbrushColor, Offset());
  m.SetlConnection (Par()->rbrushHatch, Offset());
  }


////////////////////////// RectImage - Objekt ///////////////////////////

void TrcRectImageObj::GetMinMax()
  {
  RECT rmf;
  if (hImage != NULL) {
    float LogicalUnitsPerMillimeter, negfact;
    int MapType;
    m.GetDocInfo (GETMAPTYPE,0,&MapType);
    if (MapType == MAPTYPE_GEOMETRIC)
      LogicalUnitsPerMillimeter = float(25.0),  negfact = float(1.0);
    else
      LogicalUnitsPerMillimeter = float(56.69291339), negfact = float(-1.0);
    if (IsWMF) {
      PaintContext pchlp (m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
      pchlp.GetMaxInfo (hImage,&rmf);
      tr2 fix_sc,sc;
      // Verschiebung, sodass linke obere Ecke von rmf Nullpunkt
      fix_sc.A[0][0] = fix_sc.A[1][1] = float(1.0);
      fix_sc.A[0][1] = fix_sc.A[1][0] = float(0.0);
      fix_sc.B[0] = -(float)rmf.left;
      fix_sc.B[1] = -(float)rmf.top;
      // Skalierung um xfact und yfact abhaengig von Mappingmode
      sc.A[0][0] = scalex * (LogicalUnitsPerMillimeter / float(100.0));
      sc.A[1][1] = scaley * (LogicalUnitsPerMillimeter / float(100.0)) * negfact;
      sc.A[0][1] = sc.A[1][0] = float(0.0);
      sc.B[0] = float(0.0);  sc.B[1] = float(0.0);
      Combine2d(&fix_sc, &fix_sc, &sc);
      // Rotation um den Winkel ang
      float cosang = (float)cos(ang * negfact * (pi / 180.0));
      float sinang = (float)sin(ang * negfact * (pi / 180.0));
      sc.A[0][0] = sc.A[1][1] = cosang;
      sc.A[0][1] = -(sc.A[1][0] = sinang);
      Combine2d(&fix_sc, &fix_sc, &sc);
      fpt pe[4];
      pe[0].x = pe[3].x = float(rmf.left);
      pe[1].x = pe[2].x = float(rmf.right);
      pe[0].y = pe[1].y = float(rmf.top);
      pe[2].y = pe[3].y = float(rmf.bottom);
      float xmin, ymin, xmax, ymax;
      xmin = ymin = float(1.0E10);
      xmax = ymax = float(-1.0E10);
      for (int i = 0; i < 4; i++) {
        Sc2d (&fix_sc, pe+i, pe+i);
        if (pe[i].x > xmax) xmax = pe[i].x;
        if (pe[i].x < xmin) xmin = pe[i].x;
        if (pe[i].y > ymax) ymax = pe[i].y;
        if (pe[i].y < ymin) ymin = pe[i].y;
        }
      int width = m.HalfPenWidth(167772160L);  // Linien hoechstens 5 pt dick
      rmf.left   = int(xmin) - width;
      rmf.right  = int(xmax) + width;
      rmf.top    = int(ymin) - width;
      rmf.bottom = int(ymax) + width;
      // Verschieben auf den Punkt (0,0)
      sc.A[0][0] = sc.A[1][1] = float(1.0);
      sc.A[0][1] = sc.A[1][0] = float(0.0);
      sc.B[0] = float(-rmf.left);  sc.B[1] = float(-rmf.top);
      Combine2d((tr2 FAR *)(&scale), &fix_sc, &sc);
      ImageRect.left = int(dx);
      ImageRect.right = rmf.right - rmf.left + int(dx);
      ImageRect.top = int(dy);
      ImageRect.bottom = rmf.bottom - rmf.top + int(dy);
      }
    else {
      BITMAPINFO FAR *lpbi = (BITMAPINFO FAR *) GlobalLock (hImage);
      rmf.top = rmf.left = 0 ;
      LONG XPelsPerMeter = lpbi->bmiHeader.biXPelsPerMeter;
      LONG YPelsPerMeter = lpbi->bmiHeader.biYPelsPerMeter;
      if (XPelsPerMeter == 0L) {
        if (YPelsPerMeter == 0L)
          XPelsPerMeter = 3936L;   // default: 100 dpi
        else
          XPelsPerMeter = YPelsPerMeter;
        }
      rmf.right =   int (double (lpbi->bmiHeader.biWidth) *
                        (LogicalUnitsPerMillimeter * 1000.0 * scalex)
                          / double (XPelsPerMeter));
      if (YPelsPerMeter == 0L)
        YPelsPerMeter = XPelsPerMeter;
      rmf.bottom = -int (double (lpbi->bmiHeader.biHeight) *
                        (LogicalUnitsPerMillimeter * negfact * 1000.0 * scaley)
                            / double (YPelsPerMeter));

      GlobalUnlock (hImage);
      ImageRect.left = rmf.left + int(dx);
      ImageRect.right = rmf.right + int(dx);
      if (ImageRect.left > ImageRect.right) {
        int width = ImageRect.left - ImageRect.right;
        ImageRect.left += width;
        ImageRect.right += width;
        }
      ImageRect.top = rmf.top + int(dy);
      ImageRect.bottom = rmf.bottom + int(dy);
      if (ImageRect.top > ImageRect.bottom) {
        int height = ImageRect.top - ImageRect.bottom;
        ImageRect.top += height;
        ImageRect.bottom += height;
        }
      }
    }
  else {
    ImageRect.left = int(dx);
    if (SecondPoint)
      ImageRect.right = int(dx2);
    else
      ImageRect.right = int(dx) + 1000;
    ImageRect.top = int(dy);
    if (SecondPoint)
      ImageRect.bottom = int(dy2);
    else
      ImageRect.bottom = int(dy) + 1000;
    }
  // eventuell einpassen in Rechteck
  if (SecondPoint && hImage) {
    float w = float(fabs(float (ImageRect.right - ImageRect.left + 1)));
    float h = float(fabs(float (ImageRect.bottom - ImageRect.top + 1)));
    float wtoh = w / h;
    float ww = dx2 - dx;
    float hw = dy2 - dy;
    float wtohw = ww / hw;
    int MapType;
    m.GetDocInfo (GETMAPTYPE,0,&MapType);
    if (MapType == MAPTYPE_GEOMETRIC)
      wtohw = -wtohw;
    float ddx, ddy, ssx, ssy;
    if ((flags & (RI_LINKS | RI_RECHTS | RI_OBEN | RI_UNTEN)) ==
        (RI_LINKS | RI_RECHTS | RI_OBEN | RI_UNTEN)) {
      ddx = float(0.0);
      ddy = float(0.0);
      ssx = ww / w;
      ssy = hw / h;
      }
    else if ((flags & (RI_LINKS | RI_RECHTS)) ==
             (RI_LINKS | RI_RECHTS)) {
      ddx = float(0.0);
      if (flags & RI_OBEN)
        ddy = float(0.0);
      else if (flags & RI_UNTEN)
        ddy = hw - (ww / wtoh);
      else
        ddy = (hw - (ww / wtoh)) / (float)2.0;
      ssx = ww / w;
      ssy = ssx;
      }
    else if ((flags & (RI_OBEN | RI_UNTEN)) ==
             (RI_OBEN | RI_UNTEN)) {
      if (flags & RI_LINKS)
        ddx = float(0.0);
      else if (flags & RI_RECHTS)
        ddx = ww - (wtoh * hw);
      else
        ddx = (ww - (wtoh * hw)) / (float)2.0;
      ddy = float(0.0);
      ssy = hw / h;
      ssx = ssy;
      }
    else {
      if (wtoh < wtohw) {
        ssy = hw / h;
        ssx = ssy;
        ddy = float(0.0);
        if (flags & RI_LINKS)
          ddx = float(0.0);
        else if (flags & RI_RECHTS)
          ddx = ww - (wtoh * hw);
        else
          ddx = (ww - (wtoh * hw)) / (float)2.0;
        }
      else {
        ssx = ww / w;
        ssy = ssx;
        ddx = float(0.0);
        if (flags & RI_OBEN)
          ddy = float(0.0);
        else if (flags & RI_UNTEN)
          ddy = hw - (ww / wtoh);
        else
          ddy = (hw - (ww / wtoh)) / (float)2.0;
        }
      }
    if (MapType == MAPTYPE_GEOMETRIC)
      ddy = -ddy;
    if (IsWMF) {
      tr2 sc;
      sc.A[0][0] = ssx;
      sc.A[1][1] = ssy;
      sc.A[0][1] = sc.A[1][0] = float(0.0);
      sc.B[0] = float(0.0);  sc.B[1] = float(0.0);
      Combine2d((tr2 FAR *)(&scale), (tr2 FAR *)(&scale), &sc);
      sc.A[0][0] = sc.A[1][1] = float(1.0);
      sc.A[0][1] = sc.A[1][0] = float(0.0);
      sc.B[0] = ddx;  sc.B[1] = ddy;
      Combine2d((tr2 FAR *)(&scale), (tr2 FAR *)(&scale), &sc);
      }
    ImageRect.left = int(((float(ImageRect.left) - dx) * ssx) + ddx + dx);
    ImageRect.right = int(((float(ImageRect.right) - dx) * ssx) + ddx + dx);
    ImageRect.top = int(((float(ImageRect.top) - dy) * ssy) + ddy + dy);
    ImageRect.bottom = int(((float(ImageRect.bottom) - dy) * ssy) + ddy + dy);
    }
  RECT rcLogRect;
  if (ImageRect.left < ImageRect.right) {
    rcLogRect.left   = ImageRect.left  ;
    rcLogRect.right  = ImageRect.right ;
    }
  else {
    rcLogRect.left   = ImageRect.right ;
    rcLogRect.right  = ImageRect.left  ;
    }
  if (ImageRect.top < ImageRect.bottom) {
    rcLogRect.top    = ImageRect.top   ;
    rcLogRect.bottom = ImageRect.bottom;
    }
  else {
    rcLogRect.top    = ImageRect.bottom;
    rcLogRect.bottom = ImageRect.top   ;
    }
  schwerx = (rcLogRect.left + rcLogRect.right) / 2;
  schwery = (rcLogRect.bottom + rcLogRect.top) / 2;
  SetLogRect (&rcLogRect, ErsteSeite());
  }


HMETAFILE MetaFromBlob (GLOBALHANDLE hGTmp,DWORD Size,BOOL doCopy,BOOL doFree)
  {
  BOOL doConvert = TRUE;
  HMETAFILE res = 0;

  // Test, ob Metafile wohl nicht corrupt ist
  char huge *source = LPSTR(GlobalLock (hGTmp));
  METAHEADER FAR *hd = (METAHEADER FAR *) source ;

  if (hd -> mtHeaderSize != sizeof (METAHEADER) / 2) {
    // Probieren, 22 Byte hinter dem Beginn
    hd = (METAHEADER FAR *) (source + 22) ;                // !!! ??? !!!
    if (hd->mtHeaderSize == sizeof (METAHEADER) / 2) {
      Size -= 22 ;
      // Neuen Buffer anlegen, Kopieren ohne die 22 Byte
      GLOBALHANDLE hGtmp1 = GlobalAlloc (GHND,Size);
      source = LPSTR(GlobalLock (hGtmp1));
      hmemcpy (source,hd,Size);
      GlobalUnlock (hGtmp1);
      GlobalUnlock (hGTmp);
      if (doFree)
        GlobalFree (hGTmp);
      hGTmp = hGtmp1 ;        // In hGtmp wieder das Resultat
      }
    }
  else {
    if (doCopy) {
      GLOBALHANDLE hGNew = GlobalAlloc (GMEM_MOVEABLE,Size);
      LPSTR s1 = LPSTR(GlobalLock (hGNew));
      hmemcpy (s1,source,Size);
      GlobalUnlock (hGTmp);
      GlobalUnlock (hGNew);
      hGTmp = hGNew;
      source = LPSTR (GlobalLock (hGTmp));
      }
    else
      GlobalUnlock (hGTmp);
    }
  if (hGTmp)
#ifdef WIN32
    res = SetMetaFileBitsEx (Size, (CONST BYTE *)source);
#else
    res = SetMetaFileBits (hGTmp);
#endif
  return res;
  }

HMETAFILE MyGetMetaFile (LPSTR fname)
  {
  OFSTRUCT Of;
  int mfile = OpenFile (fname,&Of,OF_READ) ;
  HMETAFILE res = 0;
  if (mfile >= 0) {
    LONG MAXSIZE = _llseek(mfile, 0L, SEEK_END);
    DBWIN_ASSERT (_llseek(mfile, 0L, SEEK_SET) == 0L);
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND,MAXSIZE);
    char huge *source = LPSTR(GlobalLock (hGtmp));
    DWORD Size = _hread (mfile,source,MAXSIZE);
    GlobalUnlock (hGtmp);
    _lclose (mfile);
    hGtmp = GlobalReAlloc (hGtmp,Size,GMEM_MOVEABLE);
    res = MetaFromBlob (hGtmp,Size,FALSE,TRUE);
    }
  return res;
  }

// Hilfsfunktionen fuer Windows DIBs:
inline LONG MyByteWidth (LONG w, WORD BitCount)
  { return (((w * (DWORD)BitCount) + 31) & ~31) >> 3; }

static WORD MyDibNumColors (VOID FAR *pv)
  {
    int                   Bits;
    LPBITMAPINFOHEADER    lpbi;
    LPBITMAPCOREHEADER    lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*    With the BITMAPINFO format headers, the size of the palette
     *    is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *    is dependent on the bits per pixel ( = 2 raised to the power of
     *    bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        Bits = lpbi->biBitCount;
    }
    else Bits = lpbc->bcBitCount;

    switch (Bits){
        case 1:
        return 2;

        case 4:
        return 16;

        case 8:
        return 256;

        default:
        // A 24 bitcount DIB has no color table
        return 0;
    }
  }

void TrcRectImageObj::Paint(PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT(Initialized);
  if (!rcLogRectInitialized) {
    GetMinMax ();
    rcLogRectInitialized = TRUE ;
    }
  if (hImage != NULL) {
    if (IsWMF) {
      tr2 sct;
      sct.B[0] = dx;
      sct.B[1] = dy;
      sct.A[0][0] =
      sct.A[1][1] = float (1.0);
      sct.A[0][1] = 
      sct.A[1][0] = float (0.0);
      Combine2d(&sct,(tr2 FAR *)(&scale), &sct);
      pc->ScaledMetaOut (hImage, &sct, 0, pc->actdiPen, 0);
      }
    else {
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hImage);
      lpbi->biSizeImage = MyByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
      DWORD dwColorTableSize = (DWORD)(MyDibNumColors(lpbi) * sizeof(RGBQUAD));
      LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
      // Berechnen der Ausdehnung des Images (inkl. beruecksichtigung des
      // Vergroesserungsfaktors)
      SetStretchBltMode (pc->hDC,STRETCH_DELETESCANS);
      int width  = ImageRect.right - ImageRect.left;
      if (width < 0) width -= 1;
      else           width += 1;
      int height = ImageRect.bottom - ImageRect.top;
      if (height < 0) height -= 1 ;
      else            height += 1 ;
      StretchDIBits (pc->hDC,ImageRect.left,ImageRect.top,width,height,
                    0,0,int(lpbi->biWidth),int(lpbi->biHeight),
                    lpBits,(LPBITMAPINFO)lpbi,DIB_RGB_COLORS,SRCCOPY);
      GlobalUnlock(hImage);
      }
    }
  else {
    DWORD olddipen = pc->actdiPen;
    pc->diPen(0x00000000);
    *pc << Line (ImageRect.left,ImageRect.top,ImageRect.left,ImageRect.bottom);
    *pc << Line (ImageRect.left,ImageRect.bottom,ImageRect.right,ImageRect.bottom);
    *pc << Line (ImageRect.right,ImageRect.bottom,ImageRect.right,ImageRect.top);
    *pc << Line (ImageRect.right,ImageRect.top,ImageRect.left,ImageRect.top);
    *pc << Line (ImageRect.left,ImageRect.top,ImageRect.right,ImageRect.bottom);
    *pc << Line (ImageRect.left,ImageRect.bottom,ImageRect.right,ImageRect.top);
    pc->diPen(olddipen);
    }
  }

void TrcRectImageObj::Load()
  {
  FromLoad = TRUE;
  Update();
  FromLoad = FALSE;
  }


void TrcRectImageObj::Update()
  {
  fpt FAR *pt = (fpt FAR *)(m.ReadlData(Par()->pt));
  float FAR *lpscx = NULL;
  float FAR *lpscy = NULL;
  float FAR *lpang = NULL;
  fpt FAR *lppt2 = NULL;
  LPDWORD lpflags = NULL;
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 5 * sizeof(DWORD)))
    lpscx = (float FAR *)(m.ReadlData(Par()->scx));
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 4 * sizeof(DWORD)))
    lpscy = (float FAR *)(m.ReadlData(Par()->scy));
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 3 * sizeof(DWORD)))
    lpang = (float FAR *)(m.ReadlData(Par()->ang));
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 2 * sizeof(DWORD)))
    lppt2 = (fpt FAR *)(m.ReadlData(Par()->pt2));
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - sizeof(DWORD)))
    lpflags = (LPDWORD)(m.ReadlData(Par()->flags));
  if ((!FromLoad) &&
      (m.IsUpdatelFromEle(Par()->FileName)) &&
      (hImage != NULL)) {
    if (IsWMF)
      DeleteMetaFile(hImage);
    else
      GlobalFree(hImage);
    hImage = NULL;
    }
  if (hImage == NULL) {
    WORD mType = m.GetMType (Par()->FileName);
    if (mType != VAR_BLOB) {
      LPSTR FileName = (LPSTR)(m.ReadlData(Par()->FileName));
      if (FileName != NULL) {
        char extension[5];
        lstrcpy(extension,FileName+(lstrlen(FileName)-4));
        AnsiUpperBuff(extension,4);
        if (lstrcmp(extension,".WMF")) {
  #ifdef ALTER_SCHEISS
          HANDLE hImgMan = ImgOpenSolo(FileName, NULL);
          if (hImgMan != NULL) {
            hImage = ImgGethDIB(hImgMan, NULL);
            ImgClose(hImgMan);
            }
  #endif
          BITMAPHANDLE LeadBitmap;
          if (L_LoadBitmap(FileName,&LeadBitmap,0,ORDER_BGR) < SUCCESS)
            hImage = NULL;
          else
            hImage = (HMETAFILE)L_ChangeToDIB(&LeadBitmap);
          IsWMF = FALSE;
          }
        else {
          hImage = MyGetMetaFile (FileName);
          IsWMF = TRUE;
          }
        }
      }
    else {
      LPBLOBDESC dsc = (LPBLOBDESC) (m.ReadlData(Par()->FileName));
      if (dsc != NULL) {
        L_CHAR L_FAR *pBuffer = (L_CHAR L_FAR *)GlobalLock(dsc->hGmem);
        FILEINFO fi;
        if ((L_FileInfoMemory(pBuffer,&fi,(L_INT32)dsc->Size
#ifndef LT7
                             ,0
#endif
                             ) == SUCCESS) &&
            (fi.Format != FILE_WMF)) {
          BITMAPHANDLE LeadBitmap;
          if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
            L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
          if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
            L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
          if (L_LoadBitmapMemory(pBuffer,&LeadBitmap,0,ORDER_BGR,(L_INT32)dsc->Size) < SUCCESS)
            hImage = NULL;
          else
            hImage = (HMETAFILE)L_ChangeToDIB(&LeadBitmap);
          IsWMF = FALSE;
          }
        else {
          hImage = MetaFromBlob (dsc->hGmem,dsc->Size,TRUE,FALSE);
          IsWMF = TRUE;
          }
        }
      }
    }
  if (pt != NULL) {
    dx = pt->x;
    dy = pt->y;
    if (lpscx != NULL) {
      scalex = *lpscx;
      if (fabs(scalex) < 1.0E-3)
        scalex = float(1.0);
      }
    else
      scalex = float(1.0);
    if (lpscy != NULL) {
      scaley = *lpscy;
      if (fabs(scaley) < 1.0E-3)
        scaley = float(1.0);
      }
    else
      scaley = scalex;
    if (lpang != NULL)
      ang = *lpang;
    else
      ang = float(0.0);
    if (lppt2 != NULL) {
      SecondPoint = TRUE;
      dx2 = lppt2->x;
      dy2 = lppt2->y;
      if (lpflags != NULL)
        flags = *lpflags;
      else
        flags = 0L;
      }
    else {
      SecondPoint = FALSE;
      }
    Initialized = TRUE;
    }
  else
    Initialized = FALSE;
  if (Initialized) {
    if (Par()->hd.par_Size >= sizeof(Trc_DefRectImage_param)) {
      GetMinMax ();
      rcLogRectInitialized = TRUE ;
      float ratio = float(fabs(float(ImageRect.right - ImageRect.left + 1) /
                               float(ImageRect.top - ImageRect.bottom + 1)));
      m.WritelData(Par()->ratio,&ratio,sizeof(ratio),0);

      if ((lpflags != NULL) && (*lpflags > 256L)) {
        fpt rl;
        rl.x = float (max(ImageRect.right,ImageRect.left));
        rl.y = float (max(ImageRect.bottom,ImageRect.top));
        m.WritelData (Par()->pt2,&rl,sizeof(rl),0);
        }
      }
    }
  }


void TrcRectImageObj::SetConnection()
  {
  m.SetlConnection (Par()->pt, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 5 * sizeof(DWORD)))
    m.SetlConnection (Par()->scx, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 4 * sizeof(DWORD)))
    m.SetlConnection (Par()->scy, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 3 * sizeof(DWORD)))
    m.SetlConnection (Par()->ang, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 2 * sizeof(DWORD)))
    m.SetlConnection (Par()->pt2, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - sizeof(DWORD)))
    m.SetlConnection (Par()->flags, Offset());
  m.SetlConnection (Par()->FileName, Offset());
  }


void TrcRectImageObj::Reset(BOOL Clear)
  {
  m.ClearlConnection (Par()->pt, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 5 * sizeof(DWORD)))
    m.ClearlConnection (Par()->scx, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 4 * sizeof(DWORD)))
    m.ClearlConnection (Par()->scy, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 3 * sizeof(DWORD)))
    m.ClearlConnection (Par()->ang, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - 2 * sizeof(DWORD)))
    m.ClearlConnection (Par()->pt2, Offset());
  if (Par()->hd.par_Size >= (sizeof(Trc_DefRectImage_param) - sizeof(DWORD)))
    m.ClearlConnection (Par()->flags, Offset());
  m.ClearlConnection (Par()->FileName, Offset());
  if (hImage != NULL) {
    if (IsWMF)
      DeleteMetaFile(hImage);
    else
      GlobalFree(hImage);
    hImage = NULL;
    }
  }

inline BOOL ComparePoint (fpt FAR &p1,fpt FAR &p2)
  {
  return ((p1.x != p2.x) || (p1.y != p2.y));
  }
static fpt FAR *AddPointToCont (fpt FAR *old,fpt FAR *pt)
  {
  fpt FAR *res;
  if (old == NULL) {
    res = (fpt FAR *) GetGlobMem (sizeof(fpt)) ;
    res[0] = *pt ;
    }
  else {
    int count = GetBlockSize (old) / sizeof(fpt) ;
    if (ComparePoint (old[count-1],*pt)) {
      res = (fpt FAR *) GetGlobMem ((count + 1) * sizeof(fpt)) ;
      lmemcpy (res,old,GetBlockSize(old)) ;
      FreeGlobMem (old);
      res[count] = *pt ;
      }
    else
      res = old ;
    }
  return res ;
  }

LONG GetFulltime (packdate FAR *d,packtime FAR *t)
  {
  LONG res;
  if ((d != NULL) && (t != NULL)) {
    res = PackTime (d);
    res += LONG(t->hour) * 3600L + LONG(t->minute) * 60L + LONG(t->second);
    }
  return res;
  }

///////////////////////////////////////////////////////////
//  Clipping einer Kontur an eine Rechteck
///////////////////////////////////////////////////////////
BOOL operator != (fpt FAR &p1,fpt FAR &p2)
  {
  return ((fabs(p1.x - p2.x) > 0.001) || (fabs(p1.y - p2.y) > 0.001));
  }

static fpt pts[6];
int CompareXAsc (const void *e1,const void *e2)
  {
  if (((fpt *)e1)->x > ((fpt *)e2)->x) return 1 ;
  if (((fpt *)e1)->x < ((fpt *)e2)->x) return -1 ;
  return 0 ;
  }
int CompareXDesc (const void *e1,const void *e2)
  {
  if (((fpt *)e1)->x < ((fpt *)e2)->x) return 1 ;
  if (((fpt *)e1)->x > ((fpt *)e2)->x) return -1 ;
  return 0 ;
  }
int CompareYAsc (const void *e1,const void *e2)
  {
  if (((fpt *)e1)->y > ((fpt *)e2)->y) return 1 ;
  if (((fpt *)e1)->y < ((fpt *)e2)->y) return -1 ;
  return 0 ;
  }
int CompareYDesc (const void *e1,const void *e2)
  {
  if (((fpt *)e1)->y < ((fpt *)e2)->y) return 1 ;
  if (((fpt *)e1)->y > ((fpt *)e2)->y) return -1 ;
  return 0 ;
  }
class FAR RectClip {
  float x1,y1,x2,y2 ;
  void SchnittX (fpt FAR *res,fpt FAR *p1,fpt FAR *p2,float x)
    {
    double dx  = p2->x - p1->x ;
    double dgx = x - p1->x ;
    double dy = p2->y - p1->y ;
    double dgy = (fabs (dx) > 0.001) ? dy * dgx / dx : 1.0E10 ;
    res->x = x ;
    res->y = p1->y + float (dgy) ;
    }
  void SchnittY (fpt FAR *res,fpt FAR *p1,fpt FAR *p2,float y)
    {
    double dy  = p2->y - p1->y ;
    double dgy = y - p1->y ;
    double dx = p2->x - p1->x ;
    double dgx = (fabs (dy) > 0.001) ? dx * dgy / dy : 1.0E10 ;
    res->y = y ;
    res->x = p1->x + float (dgx) ;
    }
 public :
  RectClip (fpt FAR *p1,fpt FAR *p2)
    {
    x1 = p1->x ; x2 = p2->x ;
    y1 = p1->y ; y2 = p2->y ;
    float dummy ;
    if (x1 > x2) dummy = x1 , x1 = x2 , x2 = dummy ;
    if (y1 > y2) dummy = y1 , y1 = y2 , y2 = dummy ;
    }
  BOOL In (fpt FAR *p)
    {
    return ((p->x >= x1) && (p->y >= y1) && (p->x <= x2) && (p->y <= y2)) ;
    }
  void IntersectPoints (fpt FAR *p1,fpt FAR *p2)
    {
    SchnittX (pts+0,p1,p2,x1);
    SchnittX (pts+1,p1,p2,x2);
    SchnittY (pts+2,p1,p2,y1);
    SchnittY (pts+3,p1,p2,y2);
    pts[4] = *p1 ;
    pts[5] = *p2 ;
    }
  void SortPts (fpt FAR *p1,fpt FAR *p2) 
    {
    float dy = p2->y - p1->y;
    float dx = p2->x - p1->x;
    if (fabs(dy) > fabs(dx)) {
      if (dy > 0) qsort (pts,6,sizeof(pts[0]),CompareYAsc);
      else        qsort (pts,6,sizeof(pts[0]),CompareYDesc);
      }
    else {
      if (dx > 0) qsort (pts,6,sizeof(pts[0]),CompareXAsc);
      else        qsort (pts,6,sizeof(pts[0]),CompareXDesc);
      }
    }
  BOOL BetweenPoints (fpt FAR *p,fpt FAR *p1,fpt FAR *p2)
    {
    double dx = p2->x - p1->x ;
    double dy = p2->y - p1->y ;
    if (fabs (dx) > fabs(dy)) {
      double dx1 = p->x - p1->x ;
      double dx2 = p->x - p2->x ;
      return (dx1 * dx2 <= 0.0) ;
      }
    else {
      double dy1 = p->y - p1->y ;
      double dy2 = p->y - p2->y ;
      return (dy1 * dy2 <= 0.0) ;
      }
    }
  };

fpt FAR *AnalyseLine (fpt FAR *old,fpt FAR *p1,fpt FAR *p2,RectClip FAR *c)
  {
  fpt FAR *res = old;
  if ((c->In (p1)) && (c->In (p2))) {
    res = AddPointToCont (res,p1) ;
    res = AddPointToCont (res,p2) ;
    }
  else {
    c->IntersectPoints (p1,p2);
    c->SortPts (p1,p2);
    for (int i = 0 ; i < 6 ; i++) {
      if ((c->In (pts+i)) && c->BetweenPoints (pts+i,p1,p2))
        res = AddPointToCont (res,pts+i);
      }
    }
  return res;
  }

DLLExport fpt FAR * _export WINAPI contclip (fpt FAR *cnt,fpt FAR *p1,fpt FAR *p2)
  {
  int count = GetBlockSize (cnt) / sizeof(fpt);
  RectClip c (p1,p2);
  fpt FAR *res = NULL ;
  if (count == 1) {
    if ((cnt[0].x >= p1->x) && (cnt[0].x <= p2->x) &&
        (cnt[0].y >= p1->y) && (cnt[0].y <= p2->y))
      return AddPointToCont (res,cnt + 0) ;
    }
  else {
    for (int i = 0 ; i < count - 1 ; i++)
      res = AnalyseLine (res,cnt+i,cnt+i+1,&c);
    }
  if (res != NULL) {
    if (GetBlockSize (res) <= sizeof(fpt)) FreeGlobMem (res) , res = NULL ;
    }
  return res ;
  }

// Contain - Object
//-------------------
#define E1 ((SortContainElem FAR * FAR *)elem1)
#define E2 ((SortContainElem FAR * FAR *)elem2)
int compareTime (const void *elem1,const void *elem2)
  {
  if ((*E1)->pd.year   < (*E2)->pd.year) return -1;
  if ((*E1)->pd.year   > (*E2)->pd.year) return 1;
  if ((*E1)->pd.month  < (*E2)->pd.month) return -1;
  if ((*E1)->pd.month  > (*E2)->pd.month) return 1;
  if ((*E1)->pd.day    < (*E2)->pd.day) return -1;
  if ((*E1)->pd.day    > (*E2)->pd.day) return 1;
  if ((*E1)->pt.hour   < (*E2)->pt.hour) return -1;
  if ((*E1)->pt.hour   > (*E2)->pt.hour) return 1;
  if ((*E1)->pt.minute < (*E2)->pt.minute) return -1;
  if ((*E1)->pt.minute > (*E2)->pt.minute) return 1;
  if ((*E1)->pt.second < (*E2)->pt.second) return -1;
  if ((*E1)->pt.second > (*E2)->pt.second) return 1;
  else return 0;
  }

void TrcContainObj::GetMinMax()
  {
  int width = m.HalfPenWidth(color);

  RECT rcLogRect;
  rcLogRect.left   = m.WorldToLog (ptClip1.x) - width;
  rcLogRect.right  = m.WorldToLog (ptClip2.x) + width;
  rcLogRect.top    = m.WorldToLog (ptClip1.y) - width;
  rcLogRect.bottom = m.WorldToLog (ptClip2.y) + width;

  SetLogRect (&rcLogRect, ErsteSeite());
  }

void TrcContainObj::Update()
  {
  if (cc != NULL) {
    FreeGlobMem(cc);
    cc = NULL;
    }
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->cnt.colR, Par()->cnt.colI));
  if (col != NULL)
    color = *col;

  DWORD FAR *Kennung = (DWORD FAR *) m.ReadlData (Par()->Kennung);
  hash FAR *FAR *rHash = (hash FAR * FAR *) m.ReadData (Par()->cnt.cntR,Par()->cnt.cntI);
  float FAR *a = (float FAR *) m.ReadlData (Par()->a);
  float FAR *b = (float FAR *) m.ReadlData (Par()->b);
  fpt FAR *pt1 = (fpt FAR *) m.ReadlData (Par()->pt1);
  fpt FAR *pt2 = (fpt FAR *) m.ReadlData (Par()->pt2);
  SCDT_res FAR *sc = (SCDT_res FAR *) m.ReadlData (Par()->dscale);

  // 1. Bilden der Kontur (und Skalieren)
  fpt FAR *hcnt = NULL;
  if ((rHash != NULL) && (*rHash != NULL) && (sc != NULL) && 
      (pt1 != NULL) && (pt2 != NULL) && 
      (a != NULL) && (b != NULL) &&
      (Kennung != NULL)) {

    ptClip1 = *pt1;
    ptClip2 = *pt2;

    SortContainElem FAR * FAR *se = (SortContainElem FAR * FAR *) (*rHash)->GetData (*Kennung);
    int dim = GetBlockSize (se) / sizeof(*se);

    fpt FAR *hcnt = (fpt FAR *) GetGlobMem (sizeof(*hcnt) * dim);
    for (int i = 0 ; i < dim ; i++) {
      hcnt[i].y = *a * * ((float FAR *) se[i]->Daten) + *b ;
      hcnt[i].x = float(sc->a + sc->b * double(GetFulltime (&se[i]->pd,&se[i]->pt)));
      }

    // 2. Clippen
    hcnt = contclip (hcnt,pt1,pt2);

    // 3. Bilden der logischen Koordinaten
    WORD oldCount = PtCount;
    PtCount = GetBlockSize (hcnt) / sizeof(*hcnt);
    if (oldCount != PtCount) {
      if (cnt != NULL) FreeGlobMem(cnt);
      cnt = (LogPt FAR *)GetGlobMem(PtCount * sizeof(LogPt));
      }

    for (i = 0; i < int(PtCount) ; i++) {
      cnt[i].x = m.WorldToLog(hcnt[i].x);
      cnt[i].y = m.WorldToLog(hcnt[i].y);
      }
    Initialized = (PtCount > 0) ;

    FreeGlobMem (hcnt);
    }
  else {
    Initialized = FALSE ;
    if (cnt != NULL) {
      FreeGlobMem (cnt);
      cnt = NULL;
      }
    PtCount = 0;
    }
  }

void TrcContainObj::SetConnection()
  {
  TrcContObj::SetConnection();
  m.SetlConnection (Par()->Kennung, Offset());
  m.SetlConnection (Par()->pt1, Offset());
  m.SetlConnection (Par()->pt2, Offset());
  m.SetlConnection (Par()->a, Offset());
  m.SetlConnection (Par()->b, Offset());
  m.SetlConnection (Par()->dscale, Offset());
  }


void TrcContainObj::Reset(BOOL Clear)
  {
  TrcContObj::Reset(Clear);
  m.ClearlConnection (Par()->Kennung, Offset());
  m.ClearlConnection (Par()->pt1, Offset());
  m.ClearlConnection (Par()->pt2, Offset());
  m.ClearlConnection (Par()->a, Offset());
  m.ClearlConnection (Par()->b, Offset());
  m.ClearlConnection (Par()->dscale, Offset());
  }

void TrcContainObj::Paint(PaintContext *pc, int Seite)
  {
  DWORD olddipen = pc->actdiPen;
  pc->diPen(color);

  pc->PolyMoveTo(cnt[0].x, cnt[0].y);
  for (int i = 1; i < int(PtCount); i++)
    pc->PolyLineTo(cnt[i].x, cnt[i].y);

  for (i = 0; i < int(PtCount); i++) {
    pc->PolyMoveTo(cnt[i].x - 50, cnt[i].y - 50);
    pc->PolyLineTo(cnt[i].x + 50, cnt[i].y + 50);
    pc->PolyMoveTo(cnt[i].x - 50, cnt[i].y + 50);
    pc->PolyLineTo(cnt[i].x + 50, cnt[i].y - 50);
    }
  pc->diPen(olddipen);
  }

DLLExport void _export WINAPI SortContainHash (hash FAR *h)
  {
  for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
    for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
      if (!h->is_empty (e))
        // Daten sortieren
        qsort (e->Data,GetBlockSize (e->Data) / sizeof(SortContainElem FAR *),sizeof(SortContainElem FAR *),compareTime);
      e = e->Next ;
      }
    }
  }

void TrcContain2Obj::Update()
  {
  if (cc != NULL) {
    FreeGlobMem(cc);
    cc = NULL;
    }
  LONG FAR *col = (LONG FAR *)(m.ReadData(Par()->cnt.colR, Par()->cnt.colI));
  if (col != NULL)
    color = *col;

  DWORD FAR *Kennung1 = (DWORD FAR *) m.ReadlData (Par()->Kennung);
  DWORD FAR *Kennung2 = (DWORD FAR *) m.ReadlData (CPar()->b2);
  hash FAR *FAR *rHash = (hash FAR * FAR *) m.ReadData (Par()->cnt.cntR,Par()->cnt.cntI);
  float FAR *a = (float FAR *) m.ReadlData (Par()->a);
  float FAR *b = (float FAR *) m.ReadlData (Par()->b);
  fpt FAR *pt1 = (fpt FAR *) m.ReadlData (Par()->pt1);
  fpt FAR *pt2 = (fpt FAR *) m.ReadlData (Par()->pt2);
  SCDT_res FAR *sc = (SCDT_res FAR *) m.ReadlData (Par()->dscale);

  // 1. Bilden der Kontur (und Skalieren)
  fpt FAR *hcnt = NULL;
  if ((rHash != NULL) && (*rHash != NULL) && (sc != NULL) && 
      (pt1 != NULL) && (pt2 != NULL) && 
      (a != NULL) && (b != NULL) &&
      (Kennung1 != NULL) &&
      (Kennung2 != NULL)) {

    ptClip1 = *pt1;
    ptClip2 = *pt2;

    SortContainElem FAR * FAR *se1 = (SortContainElem FAR * FAR *) (*rHash)->GetData (*Kennung1);
    SortContainElem FAR * FAR *se2 = (SortContainElem FAR * FAR *) (*rHash)->GetData (*Kennung2);
    int dim1 = GetBlockSize (se1) / sizeof(*se1);
    int dim2 = GetBlockSize (se2) / sizeof(*se2);

    fpt FAR *hcnt = (fpt FAR *) GetGlobMem (sizeof(*hcnt) * 2 * max(dim1,dim2));
    int k = 0 ;
    for (int i = 0 ; i < dim1 ; i++) {
      for (int j = 0 ; j < dim2 ; j++) {
        if ((se1[i]->HNr0 == se2[j]->HNr0) &&
            (se1[i]->HNr1 == se2[j]->HNr1) &&
            (lmemcmp (&se1[i]->pd,&se2[j]->pd,sizeof(packdate))) &&
            (lmemcmp (&se1[i]->pt,&se2[j]->pt,sizeof(packtime)))) {
          hcnt[k].y = *a * * ((float FAR *) se1[i]->Daten) + *b ;
          float xact = float(sc->a + sc->b * double(GetFulltime (&se1[i]->pd,&se1[i]->pt)));
          hcnt[k++].x = xact;
          hcnt[k].y = *a * * ((float FAR *) se2[j]->Daten) + *b ;
          hcnt[k++].x = xact;
          break ;
          }
        }
      }

    // 2. Bilden der logischen Koordinaten
    WORD oldCount = PtCount;
    PtCount = k ;
    if (oldCount != PtCount) {
      if (cnt != NULL) FreeGlobMem(cnt);
      cnt = (LogPt FAR *)GetGlobMem(PtCount * sizeof(LogPt));
      }
    for (i = 0; i < int(PtCount) ; i++) {
      cnt[i].x = m.WorldToLog(hcnt[i].x);
      cnt[i].y = m.WorldToLog(hcnt[i].y);
      }
    xc0 = m.WorldToLog (pt1->x);
    yc0 = m.WorldToLog (pt1->y);
    xc1 = m.WorldToLog (pt2->x);
    yc1 = m.WorldToLog (pt2->y);
    Initialized = (PtCount > 0) ;

    FreeGlobMem (hcnt);
    }
  else {
    Initialized = FALSE ;
    if (cnt != NULL) {
      FreeGlobMem (cnt);
      cnt = NULL;
      }
    PtCount = 0;
    }
  }

void TrcContain2Obj::SetConnection()
  {
  TrcContainObj::SetConnection();
  m.SetlConnection (CPar()->b2, Offset());
  }


void TrcContain2Obj::Reset(BOOL Clear)
  {
  TrcContainObj::Reset(Clear);
  m.ClearlConnection (CPar()->b2, Offset());
  }

#define DX    57
void TrcContain2Obj::PaintBar (PaintContext *pc, LogPt FAR *lp)
  {
  if ((lp[0].x > xc0 - DX) && (lp[0].x < xc1 + DX)) {
    if ((lp[0].y > yc0) && (lp[0].y <= yc1)) {
      pc->PolyMoveTo (max(lp[0].x - DX,xc0),lp[0].y);
      pc->PolyLineTo (min(lp[0].x + DX,xc1),lp[0].y);
      }
    if ((lp[1].y > yc0) && (lp[1].y <= yc1)) {
      pc->PolyMoveTo (max(lp[0].x - DX,xc0),lp[1].y);
      pc->PolyLineTo (min(lp[0].x + DX,xc1),lp[1].y);
      }
    }
  int y0 = min(lp[0].y,lp[1].y);
  int y1 = max(lp[0].y,lp[1].y);
  if (((y0 <= yc1) || (y1 >= yc0)) && (lp[0].x >= xc0) && (lp[0].x <= xc1)) {
    pc->PolyMoveTo (lp[0].x,max (y0,yc0));
    pc->PolyLineTo (lp[0].x,min (y1,yc1));
    }
  }

void TrcContain2Obj::Paint (PaintContext *pc, int Seite)
  {
  DBWIN_ASSERT(Initialized && (PtCount > 0));
  DWORD olddipen = pc->actdiPen;
  pc->diPen(color);
  pc->PolyMoveTo(cnt[0].x, cnt[0].y);
  for (int i = 0; i < int(PtCount); i += 2)
    PaintBar (pc, cnt + i);

  linehead = NULL;
  pc->diPen(olddipen);
  }

