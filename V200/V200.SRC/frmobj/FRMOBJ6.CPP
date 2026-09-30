//  Implementierung weiterer Objekte (speziell fuer Form)
//
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/frmobj/rev/frmobj6.cpv   1.22   11 Mar 1999 18:17:48   Hannes  $
//  $Log:   P:/marille/clinicum/frmobj/rev/frmobj6.cpv  $
// 
//    Rev 1.22   11 Mar 1999 18:17:48   Hannes
// Drucken von DefProject - Points
// 
//    Rev 1.21   05 Oct 1998 11:22:00   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.20   16 Feb 1998 14:15:40   Gerhold
// VC++5.x ... explicit ist jetzt ein Schluesselwort
// 
//    Rev 1.19   27 Jan 1998 16:01:04   Martin
// Verschiebe-Kastl ist jetzt sichtbar
// 
//    Rev 1.18   02 Jan 1998 13:57:06   Gerhold
// sqrt(double) -> sqrt(3.0)
// 
//    Rev 1.17   12 Sep 1997 08:12:32   Gerhold
// OnL...-Funktionen  WORD -> WPARAM
// 
//    Rev 1.16   25 Jun 1997 10:36:26   Hannes
// 
//    Rev 1.15   22 Apr 1997 12:07:46   Hannes
// Korrektur des Clippings der einzelnen Felder
// 
//    Rev 1.14   17 Sep 1996 17:04:08   HANNES
// 
//    Rev 1.13   04 Sep 1996 12:37:00   HANNES
// Projektpoint wird bei OnLButtonDown nur aktiviert, wenn der Termin
// getroffen wurde
// 
//    Rev 1.12   09 Aug 1996 18:45:44   MARTIN
// bei ProjectCallBack die linke obere Ecke statt der 
// Mausposition zurueckliefern
// 
//    Rev 1.11   10 Jun 1996 10:12:32   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.10   18 May 1996 20:14:40   HANNES
// 
//    Rev 1.9   24 Mar 1996 12:11:52   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.8   02 Feb 1996 10:49:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   07 Dec 1995 18:37:44   MARTIN
// OnKeyDown: nur bei Space reagieren
// 
//    Rev 1.6   06 Dec 1995 19:16:36   MARTIN
// Callback fuer PrinterDC
// 
//    Rev 1.5   26 Jul 1995 14:29:14   HANNES
// ProjectPoint - Erweiterung
// 
//    Rev 1.4   11 Jun 1995 10:05:18   HANNES
// 
//    Rev 1.3   05 Apr 1995 13:31:06   GERHOLD
// 
//    Rev 1.2   04 Apr 1995 12:15:06   HANNES
// No change.
// 
//    Rev 1.1   21 Mar 1995 16:23:30   HANNES
// 
//    Rev 1.0   20 Mar 1995 12:12:42   HANNES
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

#define MODULENUM     150
#include "winass.hpp"

#include "mdiclien.hpp"
#include "frmobj.hpp"
#include "frmobj6.hpp"

extern HANDLE hLibInst;

DLLExport _export WINAPI ProjectPoint::ProjectPoint (LPVOID p,mdiChild *c) : FrmObject (p,c)
  {
  }

DLLExport void _export WINAPI ProjectPoint::Load ()
  {
  Update ();
  }

struct PPCallBackBuffer {
  dllChild m;
  FrmObject FAR *obj;
  };
typedef PPCallBackBuffer FAR *LPPPCALLBACKBUFFER;

Printer *PPGetStaticPrinter()
  {
  static Printer FAR *sp;
  if (sp == NULL)
    sp = GetPrinter(TRUE);
  return sp;
  }

DLLExport void _export WINAPI PPcFieldCallBackFnc (int cmd,LPVOID Info,LPVOID MyInfo)
  {
  Printer *Pr;
  switch (cmd) {
    case CALLBACKCMD_GETPRDC :
      Pr = LPPPCALLBACKBUFFER(MyInfo)->m.Pr();
      if (Pr == NULL) {
        Pr = PPGetStaticPrinter ();
        }
      *((HDC FAR *) Info) = Pr->PrinterDC();
      break ;
    case CALLBACKCMD_RELEASEPRDC :
      Pr = LPPPCALLBACKBUFFER(MyInfo)->m.Pr();
      if (Pr == NULL) {
        Pr = PPGetStaticPrinter ();
        }
      Pr->ReleasePrDC ();
      break ;
    }
  }

static CFIELDCALLBACK cfb;
void SetPPCallback (FrmObject FAR *obj,cField FAR *f,dllChild m)
  {
  if (cfb == NULL)
#ifdef MAIN_VERSION
    cfb = CFIELDCALLBACK (
       MakeProcInstance (FARPROC(PPcFieldCallBackFnc),hLibInst)
                         );
#else
    cfb = CFIELDCALLBACK (PPcFieldCallBackFnc);
#endif

  PPCallBackBuffer p;
  p.m = m;
  p.obj = obj ;
  f->InstallCallBack (cfb,&p,sizeof(p));
  }

cField FAR *ProjectPoint::GetField (prText FAR *p,int x0,int y0,int ymin,int ymax)
  {
  LPSTR Text  = LPSTR (m.ReadlData (p->Text));
  DBINT FAR *xo = (DBINT FAR *) m.ReadlData (p->xoffs);
  DBINT FAR *yo = (DBINT FAR *) m.ReadlData (p->yoffs);
  DBINT FAR *f  = (DBINT FAR *) m.ReadlData (p->Format);
  DBINT FAR *w  = (DBINT FAR *) m.ReadlData (p->with);
  cField FAR *field = NULL ;
  if ((Text != NULL) && (xo != NULL) && (yo != NULL) && (f != NULL) &&
          ((w == NULL) || (*w > 0)) && (y0 + *yo >= ymin - 3) && (y0 + *yo <= ymax + 3)) {
    DBINT FAR *l  = (DBINT FAR *) m.ReadlData (p->AnzLines);
    field = new cField (TRANSPARENT,*f,x0 + *xo,y0 + *yo,(w != NULL) ? *w : -1,
                          (l != NULL) ? *l : -1,FALSE);
    SetCallback (this,field,m) ;
    field->SetWindow (m.MyHandle());
    field->SetScale (m_scale(),MAPTYPE_TYPOGRAPHIC);
    field->SetVOrg (m.xp(),m.yp(),ErsteSeite());
    *field = Text;
    RECT r;
    field->GetFullFieldRect (&r,0);
    if (r.bottom > ymax) {
      delete field ;
      field = NULL ;
      }
    }
  return field ;
  }

DLLExport void _export WINAPI ProjectPoint::Update ()
  {
  // Lesen der Poligonkoordinaten
  fpt FAR *lppt = (fpt FAR *) m.ReadlData (Par()->ptorg) ;
  DBINT FAR *w    = (DBINT FAR *) m.ReadlData (Par()->xwith) ;
  DBINT FAR *h    = (DBINT FAR *) m.ReadlData (Par()->yheight) ;
  DBINT FAR *tw   = (DBINT FAR *) m.ReadlData (Par()->triangwith) ;

  int x0,y0;

  DBINT FAR *lpymin = (DBINT FAR *) m.ReadlData (Par()->ymin);
  DBINT FAR *lpymax = (DBINT FAR *) m.ReadlData (Par()->ymax);
  int ymin,ymax;
  if (lpymin != NULL) ymin = *lpymin ; else ymin = -32000 ;
  if (lpymax != NULL) ymax = *lpymax ; else ymax = 32000 ;
  BOOL clipped = FALSE ;
  if ((lppt != NULL) && (w != NULL) && ((h != NULL) || (tw != NULL))) {
    Initialized = TRUE ;
    x0 = m.WorldToLog (lppt->x);
    y0 = m.WorldToLog (lppt->y);
    if (h != NULL) {
      // Rechteck zeichnen
      int x1 = x0 + *w ;
      int y1 = y0 + *h ;
      if (y0 > ymax) Initialized = FALSE ;
      if (y1 < ymin) Initialized = FALSE ;
      if (y0 < ymin) y0 = ymin , clipped = TRUE ;
      if (y1 > ymax) y1 = ymax , clipped = TRUE ;
      pt[0].x = pt[3].x = x0 ;
      pt[1].x = pt[2].x = x1 ;
      pt[0].y = pt[1].y = y0 ;
      pt[2].y = pt[3].y = y1 ;
      AnzPoints = 4 ;
      }
    else {
      // Dreieck zeichnen
      int th = int (float(*tw) * sqrt(3.0) / 2.0) ;
      int y1 = y0 + th ;
      int xm = x0 + *w / 2 ;
      if (y0 > ymax) Initialized = FALSE ;
      if (y1 < ymin) Initialized = FALSE ;
      if (Initialized) {
        if (y0 < ymin) {
          clipped = TRUE ;
          int dx = int (double(ymin - y0) / sqrt(3.0)) ;
          pt[0].x = xm - *tw / 2 + dx ;
          pt[1].x = xm + *tw / 2 - dx ;
          pt[2].x = xm ;
          pt[0].y = pt[1].y = ymin ;
          pt[2].y = y1 ;
          AnzPoints = 3 ;
          }
        else if (y1 > ymax) {
          clipped = TRUE ;
          int dx = int (double(ymax - y0) / sqrt(3.0)) ;
          pt[0].x = xm - *tw / 2 ;
          pt[1].x = xm + *tw / 2 ;
          pt[2].x = xm + *tw / 2 - dx ;
          pt[3].x = xm - *tw / 2 + dx ;
          pt[0].y = pt[1].y = y0 ;
          pt[2].y = pt[3].y = ymax ;
          AnzPoints = 4 ;
          }
        else {
          pt[0].x = xm - *tw / 2 ;
          pt[1].x = xm + *tw / 2 ;
          pt[2].x = xm ;
          pt[0].y = pt[1].y = y0 ;
          pt[2].y = y1 ;
          AnzPoints = 3 ;
          }
        }
      }
    }
  else
    Initialized = FALSE ;

  if (Initialized) {
    // Lesen der Farben
    inactivePenColor   = m.GetConstLong (Par()->inactPen   );
    activePenColor     = m.GetConstLong (Par()->actPen     );
    DWORD FAR *lpinactiveBrushColor = (DWORD FAR *) m.ReadlData (Par()->inactBrush );
    DWORD FAR *lpactiveBrushColor   = (DWORD FAR *) m.ReadlData (Par()->actBrush );
    if (lpinactiveBrushColor)
      inactiveBrushColor = *lpinactiveBrushColor ;
    else
      inactiveBrushColor = 0xFFFFFFFF ;
    if (lpactiveBrushColor)
      activeBrushColor = *lpactiveBrushColor ;
    else
      activeBrushColor = 0xFFFFFFFF ;
    }

  if (Initialized) {
    // Erzeugen der Felder
    AnzFields = Par()->AnzTexts () ;
    for (int i = 0 ; i < AnzFields ; i++) {
      if (flds[i] != NULL) delete flds[i] ;
      flds[i] = GetField (&(Par()->t[i]),x0,y0,ymin,ymax);
      }
    }
  else {
    for (int i = 0 ; i < AnzFields ; i++)
      if (flds[i] != NULL) delete flds[i] , flds[i] = NULL;
    AnzFields = 0;
    }
  if (Initialized) {
    DBINT FAR *lpdoActivate = (DBINT FAR *) m.ReadlData (Par()->doActivate);
    doActivate = (lpdoActivate != NULL) ? *lpdoActivate : FALSE ;
    }

  }

DLLExport void _export WINAPI ProjectPoint::GetMinMax ()
  {
  if (Initialized) {
    RECT rcLogRect;
    rcLogRect.left   = pt[0].x - m.HalfPenWidth(activePenColor);
    rcLogRect.right  = pt[1].x + m.HalfPenWidth(activePenColor);
    rcLogRect.top    = pt[0].y - m.HalfPenWidth(activePenColor);
    rcLogRect.bottom = pt[2].y + m.HalfPenWidth(activePenColor);

    for (int i = 0 ; i < AnzFields ; i++) {
      if (flds[i] != NULL) {
        RECT r;
        flds[i]->GetFieldRect (&r,ErsteSeite());
        if (!IsRectEmpty (&r))
          MyUnionRect (&rcLogRect,&rcLogRect,&r);
        }
      }
    SetLogRect (&rcLogRect,ErsteSeite());
    }
  }

DLLExport void _export WINAPI ProjectPoint::SetConnection()
  {
  m.SetlConnection (Par()->ptorg,Offset());
  m.SetlConnection (Par()->xwith,Offset());
  m.SetlConnection (Par()->yheight,Offset());
  m.SetlConnection (Par()->triangwith,Offset());
  for (int i = 0 ; i < Par()->AnzTexts () ; i++) {
    prText FAR *p = Par()->t + i ;
    m.SetlConnection (p->with,Offset());
    m.SetlConnection (p->Text,Offset());
    m.SetlConnection (p->xoffs,Offset());
    m.SetlConnection (p->yoffs,Offset());
    m.SetlConnection (p->AnzLines,Offset());
    }
  }

DLLExport void _export WINAPI ProjectPoint::Reset(BOOL doClear)
  {
  m.ClearlConnection (Par()->ptorg,Offset());
  m.ClearlConnection (Par()->xwith,Offset());
  m.ClearlConnection (Par()->yheight,Offset());
  m.ClearlConnection (Par()->triangwith,Offset());
  for (int i = 0 ; i < Par()->AnzTexts () ; i++) {
    prText FAR *p = Par()->t + i ;
    m.ClearlConnection (p->with,Offset());
    m.ClearlConnection (p->Text,Offset());
    m.ClearlConnection (p->xoffs,Offset());
    m.ClearlConnection (p->yoffs,Offset());
    m.ClearlConnection (p->AnzLines,Offset());
    if (flds[i] != NULL)
      delete flds[i] ;
    }
  }

DLLExport void _export WINAPI ProjectPoint::Paint (PaintContext *pc, int Seite)
  {
  HBRUSH oldBrush = 0;
  if (IsActive) {
    pc->diPen (activePenColor);
    if (activeBrushColor != 0xFFFFFFFF)
      oldBrush = (HBRUSH)SelectObject (pc->hDC,CreateSolidBrush (activeBrushColor));
    else
      SelectObject (pc->hDC,GetStockObject (NULL_BRUSH));
    }
  else {
    pc->diPen (inactivePenColor);
    if (inactiveBrushColor != 0xFFFFFFFF)
      oldBrush = (HBRUSH)SelectObject (pc->hDC,CreateSolidBrush (inactiveBrushColor));
    else
      SelectObject (pc->hDC,GetStockObject (NULL_BRUSH));
    }
  Polygon (pc->hDC,pt,AnzPoints) ;
  for (int i = 0 ; i < AnzFields ; i++) {
    if (flds[i] != NULL) {
      if (IsActive)
        flds[i]->SetOutColor (activePenColor);
      else
        flds[i]->UseDefOutColor ();
      if (pc->mode == DO_EXTERN)
        flds[i]->PaintToMeta (pc->hDC);
      else
        flds[i]->Paint (pc->hDC,Seite,(pc->mode == DO_PRINT));
      }
    }
  if (oldBrush)
    DeleteObject (SelectObject (pc->hDC,oldBrush));
  }

DLLExport void _export WINAPI ProjectPoint::Reformat (BOOL forPrinter)
  {
  for (int i = 0 ; i < AnzFields ; i++)
    if (flds[i] != NULL)
      flds[i]->Reformat ((forPrinter) ? PrinterContext() : 0);
  }

void ProjectPoint::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  for (int i = 0 ; i < AnzFields ; i++) {
    if (flds[i] != NULL) {
      flds[i]->SetScale (scale,MapType);
      flds[i]->SetVOrg (xp,yp,ErsteSeite());
      flds[i]->SetWOrg (x0,y0);
      }
    }
  }

void ProjectPoint::StartExternPaint ()
  {
  for (int i = 0 ; i < AnzFields ; i++)
    if (flds[i] != NULL)
      flds[i]->StartExternPaint ();
  }

void ProjectPoint::EndExternPaint ()
  {
  for (int i = 0 ; i < AnzFields ; i++)
    if (flds[i] != NULL)
      flds[i]->EndExternPaint ();
  }

DLLExport BOOL _export WINAPI ProjectPoint::IsToActivate ()
  {
  return ((Initialized) && (doActivate)) ;
  }

DLLExport void _export WINAPI ProjectPoint::SetActive (int Seite, BOOL bexplicit)
  {
  m.BringToTail (this);
  if (!IsActive)
    Invalidate (Seite);
  }

DLLExport void _export WINAPI ProjectPoint::SetInActive (int Seite)
  {
  Invalidate (Seite);
  }

DLLExport BOOL _export WINAPI ProjectPoint::OnKeyDown (WORD wP, int Seite)
  {
  if (wP == ' ')
    m.ExCuteProc (Par()->callBackProc,0);
  return TRUE ;
  }

DLLExport BOOL _export WINAPI ProjectPoint::OnLButtonDown (WPARAM wP,int x,int y, int Seite)
  {
  RECT r;
  r.left   = pt[0].x ;
  r.right  = pt[1].x ;
  r.top    = pt[0].y ;
  r.bottom = pt[2].y ;
  POINT pt;
  pt.x = x , pt.y = y ;
  if (PtInRect (&r,pt)) {
    xMoveStart = x;
    yMoveStart = y;
    tMoveStart = GetTickCount();
    dxMove = dyMove = 0 ;
    return TRUE ;
    }
  else {
    tMoveStart = 0L;    // Zur Kennzeichnung, dass OnMouseMove nix machen soll
    return FALSE ;
    }
  }

DLLExport BOOL _export WINAPI ProjectPoint::OnLButtonDblClk (WPARAM wP,int x,int y, int Seite)
  {
  if ((OnLButtonDown (wP,x,y,Seite)) && (OnKeyDown (' ',Seite)))
    return TRUE ;
  else
    return FALSE ;
  }

void ProjectPoint::DrawMoving (PaintContext *pc)
  {
  if (isMoveing) {
    HBRUSH oldBrush = (HBRUSH)SelectObject (pc->hDC,GetStockObject (NULL_BRUSH));
//    HPEN oldPen = SelectObject (pc->hDC,CreatePen (PS_SOLID,0,~(RGB(0xFF,0,0))));
    HPEN oldPen = (HPEN)SelectObject (pc->hDC,CreatePen (PS_SOLID,0,RGB(0,0xFF,0xFF)));
    int oldMode = SetROP2 (pc->hDC,R2_XORPEN);
    Rectangle (pc->hDC,pt[0].x+dxMove,pt[0].y+dyMove,pt[1].x+dxMove,pt[2].y+dyMove);
    DeleteObject (SelectObject (pc->hDC,oldPen));
    SelectObject (pc->hDC,oldBrush);
    }
  }

DLLExport BOOL _export WINAPI ProjectPoint::OnMouseMove (WPARAM wP,int x,int y,int Seite)
  {
  if ((wP & MK_LBUTTON) && (GetTickCount() > tMoveStart + 200L) && (tMoveStart > 0L)) {
    PaintContext pc;
    GetDocumentContext (&pc,m);
    DrawMoving (&pc);
    isMoveing = TRUE ;
    dxMove = x - xMoveStart ;
    dyMove = y - yMoveStart ;
    DrawMoving (&pc);
    return TRUE ;
    }
  return FALSE ;
  }

static DWORD ProjectCallBack_x,ProjectCallBack_y,ProjectCallBack;
DLLExport void _export WINAPI SetProjectCallBack(DWORD proc,DWORD x,DWORD y)
  {
  ProjectCallBack_x = y;
  ProjectCallBack_y = x;
  ProjectCallBack = proc;
  }

DLLExport BOOL _export WINAPI ProjectPoint::OnLButtonUp (WPARAM wP,int x,int y,int Seite)
  {
  if (isMoveing) {
    PaintContext pc;
    GetDocumentContext (&pc,m);
    DrawMoving (&pc);
    dxMove = x - xMoveStart ;
    dyMove = y - yMoveStart ;
    short newx = short(pt[0].x+dxMove);
    short newy = short(pt[0].y+dyMove);
    isMoveing = FALSE ;
    if (ProjectCallBack != 0L) {
      m.WritelData (ProjectCallBack_x,&newx,sizeof(newx),Offset ());
      m.WritelData (ProjectCallBack_y,&newy,sizeof(newy),Offset ());
      m.ExCuteProc (ProjectCallBack,EM_LOAD);
      }
    }
  return TRUE ;
  }
