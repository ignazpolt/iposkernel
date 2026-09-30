/*----------------------------*/
/*  Bearbeiten der Feldliste  */
/*----------------------------*/
//
// $Header:   P:/marille/clinicum/restool/rev/fldlst.cpv   1.12   05 Oct 1998 11:26:00   Gerhold  $
// $Log:   P:/marille/clinicum/restool/rev/fldlst.cpv  $
// 
//    Rev 1.12   05 Oct 1998 11:26:00   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   05 Nov 1997 09:13:00   Gerhold
// 32 Bit
// 
//    Rev 1.10   28 Aug 1997 15:49:10   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.9   19 May 1996 10:57:16   HANNES
// PaintActiveCombo :: der Seitenparameter hat gefehlt!
// 
//    Rev 1.8   24 Mar 1996 12:16:24   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.7   02 Feb 1996 10:50:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   26 Apr 1995 15:26:22   HANNES
// 
//    Rev 1.5   10 Apr 1995 10:45:04   GERHOLD
// 
//    Rev 1.4   04 Apr 1995 17:34:02   HANNES
// 
//    Rev 1.3   16 Feb 1995 12:33:10   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.2   29 Jan 1995 11:47:58   HANNES
// 
//    Rev 1.1   24 Jan 1995 10:59:58   HANNES
// 
//    Rev 1.0   20 Jan 1995 15:56:34   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "font.hpp"
#include "printer.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "cfield.hpp"
#include "multl.hpp"
#include "drdrop.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

#include "fldlst.hpp"
#include "restool.hpp"

FldLine::FldLine (int AnzFields,WORD LID,FldList FAR *l)
  {
  cList = (LPFIELD FAR *) GetGlobMem (sizeof(*cList) * AnzFields);
  LineID = LID;
  Parent = l;
  }

FldLine::~FldLine ()
  {
  for (int i = 0 ; i < AnzFields() ; i++) {
    if (cList[i] != NULL) delete cList[i];
    }
  FreeGlobMem (cList);
  }

void FldLine::SetFldPos (int Column,int x)
  {
  POINT pt;
  pt.x = x ;
  pt.y = 0 ;
  *(cList[Column]) = pt;
  }

void FldLine::SetYV (int y)
  { 
  yv = y ; 
  SetOrg(Parent->xv,Parent->yv);
  }

void FldLine::Paint(HDC hDC,BOOL Select)
  {
  // Zeichnen der Felder
  DWORD old = SetViewportOrgEx (hDC,Parent->xv,Parent->yv+yv, NULL);
  DWORD oldBkColor ;
  if (Select) {
    oldBkColor = SetBkColor (hDC,GetSysColor(COLOR_HIGHLIGHT));
    for (int i = 0 ; i < AnzFields() ; i++)
      cList[i]->SetOutColor (GetSysColor(COLOR_HIGHLIGHTTEXT));
    }
  for (int i = 0 ; i < AnzFields() ; i++) {
    if (cList[i] != NULL) cList[i]->Paint(hDC,0,FALSE);
    }
  if (Select) {
    SetBkColor (hDC,oldBkColor);
    for (int i = 0 ; i < AnzFields() ; i++)
      cList[i]->UseDefOutColor ();
    }
  SetViewportOrgEx (hDC,LOWORD(old),HIWORD(old), NULL);
  }

void FldLine::ToLog (POINT FAR *pt,DWORD pos,BOOL IsScreen)
  {
  PaintContext pc(Parent->hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (Parent->xv,yv + Parent->yv);
  pt->x = LOWORD(pos);
  pt->y = HIWORD(pos);
  if (IsScreen)
    ScreenToClient (Parent->hWnd,pt);
  DPtoLP (pc.hDC,pt,1);
  }

void FldLine::SetOrg(int x,int y)
  {
  for (int i = 0 ; i < AnzFields() ; i++)
    if (cList[i] != NULL) cList[i]->SetVOrg (x,y + yv,0);
  }

/*---< Anlegen eines neuen Feldes >-------*/
extern HINSTANCE MyInstance;
#define SDX 30
#define FLDOFFS 30

#define STATE_NONE        0
#define STATE_VLINEHIT    1
DLLExport void _export FAR PASCAL cFieldCallBackFnc (int cmd,LPVOID Info,LPVOID MyInfo)
  {
  LPFIELDCALLBACK inf = LPFIELDCALLBACK(MyInfo);
  switch (cmd) {
    case CALLBACKCMD_SAVESTR :
      if (inf->line == inf->list->LastLine) {
        inf->list->Enlarge (NULL);
        }
      inf->list->Save (inf->line,inf->column);
      break ;
    case CALLBACKCMD_NEEDSCROLL :
      inf->list->NeedScroll (LPPOINT(Info)->x,LPPOINT(Info)->y);
      break;
    case CALLBACKCMD_SHOWLIST :
      if (inf->line == inf->list->LastLine) {
        inf->list->Enlarge (NULL);
        }
      inf->list->ShowList (LPSTR (Info),inf->line,inf->column);
      break ;
    case CALLBACKCMD_ISCHARALLOWED :
      {
      TCI FAR *t = (TCI FAR *) Info;
      if (!inf->list->AllowChange (inf->line,inf->column))
        t->wP = 0 ;
      }
      break ;
    }
  }

cField FAR *FldList::GetField (HWND hWnd,int x,int w,int Format,LPSTR Text,LPFIELDCALLBACK cbmem,DWORD mode)
  {
  static CFIELDCALLBACK cfb;
  if (cfb == NULL)
    cfb = CFIELDCALLBACK (
      MakeProcInstance (FARPROC(cFieldCallBackFnc),MyInstance)
                         );

  cField FAR *field = new cField (OPAQUE,Format,x,0,w - 2 * FLDOFFS,1,FALSE);
  if (cbmem != NULL)
    field->InstallCallBack (cfb,cbmem,sizeof(*cbmem));
  field->SetWindow (hWnd);
  field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  field->SetVOrg (yv,xv,0);
  field->SetFieldMode (mode);
  if ((mode & FM_OUTLINEONLY) != 0)
    field->SetSelectionPen (hActivePen,
                            hInactivePen
                          );

  if ((mode & FM_LSELECTION) != 0)
    field->SetButtonField (TRUE);
  *field = Text;

  return field;
  }

int FldList::LineHeight ()
  {
  if (lHeight <= 0) {
    LPFORMATMETRIC fm = GetFormatMetrics (hWnd,MAPTYPE_TYPOGRAPHIC,GetFormat());
    PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
    pc.LogicalTwips (0,0);
    lHeight = pc.YLOGtoPHYS(fm->yHeight);
    }
  return lHeight;
  }

int FldList::BuildHdLine ()
  {
  // Die Zeile erzeugen
  HdLine = new FldLine (AnzColumns(),WORD(-1),this);
  int x = GetX0();
  for (int i = 0 ; i < AnzColumns() ; i++) {
    int w = GetColWidth(i);
    HdLine->SetField(GetField(hWnd,x,w,GetFormat(),GetHdString(i),
                         NULL,FM_OUTLINEONLY),
                     i);
    HdLine->SetYV(0);
    x += w ;
    }
  return LineHeight();
  }

void FldList::BuildLastLine (int y)
  {
  // Die Zeile erzeugen
  LastLine = new FldLine (AnzColumns(),WORD(-1),this);
  int x = GetX0();
  for (int i = 0 ; i < AnzColumns () ; i++) {
    FieldCallBack cbmem;
    cbmem.column = i;
    cbmem.line = LastLine;
    cbmem.list = this;
    int w = GetColWidth(i);
    LastLine->SetField(GetField(hWnd,x,w,GetFormat(),"",
                         &cbmem,GetColMode(i)),
                     i);
    LastLine->SetYV(y);
    x += w ;
    }
  }

int FldList::AddLine (LPVOID Context,int y,BOOL SetScrolls,WORD LId)
  {
  // Die Zeile erzeugen
  LPFLDLINE l = new FldLine (AnzColumns(),LId,this);
  int x = GetX0();
  for (int i = 0 ; i < AnzColumns() ; i++) {
    FieldCallBack cbmem;
    cbmem.column = i;
    cbmem.line = l;
    cbmem.list = this;

    int w = GetColWidth(i);
    l->SetField(GetField(hWnd,x,w,GetFormat(),GetFieldString(Context,i),
                         &cbmem,GetColMode(i)),
                i);
    l->SetYV(y);
    x += w ;
    }

  // In die Zeilenliste eintrage
  if (FirstLine == NULL) FirstLine = l ;
  else {
    for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
      if (h->Next == NULL) {
        h->Next = l;
        break ;
        }
      }
    }

  // Das letzte Feld runtersetzen
  int yres = y + LineHeight();
  if (LastLine != NULL) {
    x = GetX0();
    for (int i = 0 ; i < AnzColumns() ; i++) {
      LastLine->SetFldPos (i,x);
      x += GetColWidth(i);
      }
    LastLine->SetYV (yres);
    }

  // Scrollbalken setzen
  if (SetScrolls)
    DoSetScrolls();

  return yres;
  }

int FldList::FldLines()
  {
  int res = 0 ;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next)
    res ++ ;
  return res;
  }

int FldList::LinesToShow()
  {
  int res = FldLines()+1;
  if (EnableNewContext())
    res ++ ;
  return res;
  }

extern LPSTR IniFile();
int FldList::GetProfInt (LPSTR Name,int def)
  {
  return MyGetProfInt (ProfBase(),Name,def);
  }

void FldList::SetProfInt (LPSTR Name,int val)
  {
  MySetProfInt (ProfBase(),Name,val);
  }

void FldList::Invalidate (LPFLDLINE h,LPRECT r,BOOL doErase)
  {
  PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (xv,h->yv+yv);
  pc.LogRecttoPhys (r,r);
  InflateRect (r,1,1);
  InvalidateRect (hWnd,r,doErase);
  }

void FldList::InvalidateArrow (LPFLDLINE x)
  {
  if (x != NULL) {
    RECT r;
    {
    PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
    pc.LogicalTwips (0,0);
    r.top  = 0 ; r.bottom = pc.YPHYStoLOG(LineHeight());
    r.left = 0 ; r.right = GetX0();
    }
    Invalidate (x,&r,TRUE);
    }
  }

void FldList::WritePos()
  {
  RECT rc;
  GetWindowRect (hWnd,&rc);
  SetProfInt ("LEFT",rc.left);
  SetProfInt ("TOP",rc.top);
  SetProfInt ("CLW",rc.right - rc.left + 1);
  SetProfInt ("CLH",rc.bottom - rc.top + 1);
  }

void FldList::GetPos(int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetProfInt ("LEFT",100);
  *y = GetProfInt ("TOP",100);
  *w = GetProfInt ("CLW",600);
  *h = GetProfInt ("CLH",400);
  }

void FldList::WriteColWidth()
  {
  if (ColWidth != NULL) {
    for (int i = 0 ; i < AnzColumns() ; i++) {
      if (ColWidth[i] != -1) {
        char wstring[32];
        wsprintf (wstring,"Width%d",i);
        SetProfInt (wstring,ColWidth[i]);
        }
      }
    }
  }

int FldList::GesWidth()
  {
  int res = GetX0();
  for (int i = 0 ; i < AnzColumns() ; i++)
    res += GetColWidth(i);
  return res;
  }

void FldList::DoSetScrolls()
  {
  RECT rc;
  GetClientRect (hWnd,&rc);
  PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (0,0);
  int lh = LineHeight();
  int gw = pc.XLOGtoPHYS(GesWidth());
  int AnzYScrolls = LinesToShow() - rc.bottom / lh ;
  int AnzXScrolls = (gw - rc.right) / SDX;
  if (AnzYScrolls > 0) {
    int yo = GetScrollPos (hWnd,SB_VERT);
    SetScrollRange (hWnd,SB_VERT,0,AnzYScrolls,FALSE);
    int yn = GetScrollPos (hWnd,SB_VERT);
    ShowScrollBar (hWnd,SB_VERT,TRUE);
    yv = - LineHeight() * yn;
    }
  else {
    SetScrollRange (hWnd,SB_VERT,0,0,FALSE);
    SetScrollPos (hWnd,SB_VERT,0,FALSE);
    yv = 0;
    ShowScrollBar (hWnd,SB_VERT,FALSE);
    }

  if (AnzXScrolls > 0) {
    int xo = GetScrollPos (hWnd,SB_HORZ);
    SetScrollRange (hWnd,SB_HORZ,0,AnzXScrolls,FALSE);
    int xn = GetScrollPos (hWnd,SB_HORZ);
    ShowScrollBar (hWnd,SB_HORZ,TRUE);
    xv = - xn * SDX ;
    }
  else {
    SetScrollRange (hWnd,SB_HORZ,0,0,FALSE);
    SetScrollPos (hWnd,SB_HORZ,0,FALSE);
    xv = 0;
    ShowScrollBar (hWnd,SB_HORZ,FALSE);
    }

  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next)
    h->SetOrg (xv,yv);
  if (HdLine != NULL)
    HdLine->SetOrg (xv,yv);
  if (LastLine != NULL)
    LastLine->SetOrg (xv,yv);
  }

void FldList::BuildList ()
  {
  int y = BuildHdLine ();
  if (EnableNewContext())
    BuildLastLine (y);

  WORD lId = 0;
  for (LPVOID Context = GetFirstContext() ; Context != NULL ; Context = GetNextContext(Context))
    y = AddLine (Context,y,FALSE,lId ++);

  if (FirstLine != NULL)
    ActiveLine = FirstLine;
  else
    ActiveLine = LastLine;
  DoSetScrolls();
  }

void FldList::SetNewFldPos ()
  {
  int y = 0;
  int x = GetX0();
  for (int i = 0 ; i < AnzColumns () ; i++) {
    HdLine->SetFldPos (i,x);
    int w = GetColWidth(i);
    cField FAR *f = HdLine->GetField(i);
    if (f != NULL) f->SetWidth(w);
    x += w;
    }
  HdLine->SetYV(0);
  y += LineHeight();
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    x = GetX0();
    for (int i = 0 ; i < AnzColumns () ; i++) {
      h->SetFldPos (i,x);
      int w = GetColWidth(i);
      cField FAR *f = h->GetField(i);
      if (f != NULL) f->SetWidth(w);
      x += w;
      }
    h->SetYV(y);
    y += LineHeight();
    }
  if (EnableNewContext()) {
    x = GetX0();
    for (int i = 0 ; i < AnzColumns () ; i++) {
      LastLine->SetFldPos (i,x);
      int w = GetColWidth(i);
      cField FAR *f = LastLine->GetField(i);
      if (f != NULL) f->SetWidth(w);
      x += w;
      }
    LastLine->SetYV (y);
    }
  }

void FldList::Paint (PaintContext *pc)
  {
  // Zeichnen def Kopfzeile
  pc->LogicalTwips (xv,0);
  int yvold = yv;
  yv = 0;
  HdLine->Paint(pc->hDC,FALSE);
  yv = yvold;

  // Zeichnen aller Felder
  int hdHeight = LineHeight();
  RECT rc;
  GetClientRect (hWnd,&rc);
  rc.top = hdHeight;
  HRGN clpRgn = CreateRectRgn (rc.left,rc.top,rc.right,rc.bottom);
  SelectClipRgn (pc->hDC,clpRgn);
  DeleteObject (clpRgn);
  pc->LogicalTwips (xv,yv);
  for (LPFLDLINE l = FirstLine ; l != NULL ; l = l->Next) {
    l->Paint(pc->hDC,((l == ActiveLine) && (!EnableInput())));
    }
  if (LastLine != NULL)
    LastLine->Paint(pc->hDC,((LastLine == ActiveLine) && (!EnableInput())));

  int dy = pc->YPHYStoLOG(LineHeight());
  int yva = LineHeight();
  int dyv = LineHeight();
  // Zeichnen eines Pfeiles fuer die Aktive Zeile
  if ((ActiveLine != NULL) && (GetX0() > 0)) {
    int ymid = dy / 2 ;
    int dx = GetX0() - FLDOFFS;
    int xmid = dx / 2;
    for (l = FirstLine ; l != NULL ; l = l->Next) {
      if (l == ActiveLine) break ;
      yva += dyv ;
      }
    DWORD old = SetViewportOrgEx (pc->hDC,xv,yv+yva, NULL);
    SelectObject (pc->hDC,GetStockObject(BLACK_BRUSH));
    POINT arc[7];
    arc[0].x = dx / 10     ,      arc[0].y = ymid + 3 * dy / 20 ;
    arc[1].x = dx / 10     ,      arc[1].y = ymid - 3 * dy / 20 ;
    arc[2].x = 6 * dx / 10 ,      arc[2].y = ymid - 3 * dy / 20 ;
    arc[3].x = 6 * dx / 10 ,      arc[3].y = ymid - 8 * dy / 20 ;
    arc[4].x = 9 * dx / 10 ,      arc[4].y = ymid  ;
    arc[5].x = 6 * dx / 10 ,      arc[5].y = ymid + 8 * dy / 20 ;
    arc[6].x = 6 * dx / 10 ,      arc[6].y = ymid + 3 * dy / 20 ;
    Polygon (pc->hDC,arc,sizeof(arc)/sizeof(POINT));
    SetViewportOrgEx (pc->hDC,LOWORD(old),HIWORD(old), NULL);
    }
  SelectClipRgn (pc->hDC,NULL);

  // Zeichnen des Gitters
  SelectObject (pc->hDC,GetStockObject(BLACK_PEN));
  int x[40];
  int c = AnzColumns();
  int xact = GetX0() - FLDOFFS;
  int xmin,xmax;
  for (int i = 0 ; i <= c ; i++) {
    POINT pt;
    pt.x = xact ;
    pt.y = 0 ;
    LPtoDP (pc->hDC,&pt,1);
    x[i] = pt.x ;
    if (i == 0)
      xmin = x[i] ;
    if (i < c)
      xact += GetColWidth(i);
    else
      xmax = x[i] ;
    }
  int ymax = LinesToShow() * LineHeight();
  pc->diPen (0L);
  pc->ResetMap ();
  for (i = 0 ; i < c ; i++)
    *pc << Line(x[i],0,x[i],ymax);
  *pc << Line(x[i],0,x[i],ymax);
  int r = LinesToShow();
  int y = dyv ;
  for (i = 0 ; i < r ; i++) {
    *pc << Line(xmin,y,xmax,y);
    y += dyv;
    }

  if ((ActiveLine != NULL) && (GetFocus () == hWnd)) {
    pc->LogicalTwips (xv,yv+ActiveLine->yv);
    PaintActiveCombo (pc->hDC,hWnd,FALSE,0);
    }
  }

void FldList::EraseBkGnd(HDC hDC)
  {
  RECT rc;
  GetClientRect (hWnd,&rc);
  PaintContext pc;
  pc.SetDC (hDC);
  pc.LogicalTwips (xv,yv);
  HPEN oldPen = (HPEN)SelectObject (pc.hDC,GetStockObject (WHITE_PEN));
  HBRUSH oldBrush = (HBRUSH)SelectObject (pc.hDC,GetStockObject (WHITE_BRUSH));

  POINT p[4];
  p[0].x = p[1].x = GetX0();
  p[2].x = p[3].x = GesWidth() - FLDOFFS;
  p[0].y = p[1].y = p[2].y = p[3].y = 0;
  LPtoDP (pc.hDC,p,4);
  p[1].y = p[2].y = LineHeight() * LinesToShow();

  POINT pte;
  pte.x = rc.right;
  pte.y = rc.bottom;
  pc.ResetMap ();

  // 1. den Tabellenbereich weiss lassen
  Rectangle (pc.hDC,p[0].x,p[0].y,p[2].x,p[2].y);

  // 2. das drumherum Grau malen
  SelectObject (pc.hDC,GetStockObject (LTGRAY_BRUSH));
  LOGBRUSH lgo ;
  GetObject (GetStockObject(LTGRAY_BRUSH),sizeof (LOGBRUSH),(LPSTR) &lgo);
  SelectObject (pc.hDC,CreatePen(PS_SOLID,1,lgo.lbColor));
  Rectangle (pc.hDC,0,0,p[0].x,pte.y);
  Rectangle (pc.hDC,p[0].x,p[1].y,p[2].x,pte.y);
  Rectangle (pc.hDC,p[2].x,0,pte.x,pte.y);

  // fertig
  DeleteObject (SelectObject (pc.hDC,oldPen));
  SelectObject (pc.hDC,oldBrush);
  }

#define SBU_THUMBVAL	    (SB_ENDSCROLL+1)
void FldList::OnVScroll(WPARAM wP,LPARAM lP)
  {
  int ay = GetScrollPos (hWnd,SB_VERT);
  int dy = 0;
  switch (wP) {
    case SB_LINEDOWN :
      dy = 1 ;
      break ;
    case SB_LINEUP :
      dy = -1;
      break ;
    case SB_PAGEDOWN :
      dy = 5;
      break ;
    case SB_PAGEUP :
      dy = -5;
      break ;
    case SB_THUMBPOSITION :
      dy = int (LOWORD(lP)) - ay;
      break ;
    case SBU_THUMBVAL :
      dy = LOWORD(lP);
      break ;
    }
  int ny = ay + dy;
  int ymin,ymax;
  GetScrollRange (hWnd,SB_VERT,&ymin,&ymax);
  ny = min(max(ny,ymin),ymax);
  if (ny != ay) {
    SetScrollPos (hWnd,SB_VERT,ny,TRUE);
    yv = - LineHeight() * ny;
    for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next)
      h->SetOrg (xv,yv);
    if (HdLine != NULL)
      HdLine->SetOrg (xv,yv);
    if (LastLine != NULL)
      LastLine->SetOrg (xv,yv);
    InvalidateRect (hWnd,NULL,TRUE);
    }
  }

void FldList::NeedScroll (int dx,int dy)
  {
  int xunit = SDX,yunit = LineHeight();
  int a ;
  unsigned msg = 0;
  if ((dx != 0) && (xunit != 0)) {
    if (dx < 0) a = dx / xunit - 1 ;
    else        a = dx / xunit + 1 ;
    msg = WM_HSCROLL ;
    }
  if ((dy != 0) && (yunit != 0)) {
    if (dy < 0) a = dy / yunit - 1 ;
    else        a = dy / yunit + 1 ;
    msg = WM_VSCROLL ;
    }
  if (msg)
    SendMessage (hWnd,msg,SBU_THUMBVAL,MAKELONG(a,0));
  }

void FldList::OnHScroll(WPARAM wP,LPARAM lP)
  {
  int ax = GetScrollPos (hWnd,SB_HORZ);
  int dx = 0;
  switch (wP) {
    case SB_LINEDOWN :
      dx = 1 ;
      break ;
    case SB_LINEUP :
      dx = -1;
      break ;
    case SB_PAGEDOWN :
      dx = 5;
      break ;
    case SB_PAGEUP :
      dx = -5;
      break ;
    case SB_THUMBPOSITION :
      dx = int (LOWORD(lP)) - ax;
      break ;
    case SBU_THUMBVAL :
      dx = LOWORD(lP);
      break ;
    }
  int nx = ax + dx;
  int xmin,xmax;
  GetScrollRange (hWnd,SB_HORZ,&xmin,&xmax);
  nx = min(max(nx,xmin),xmax);
  if (nx != ax) {
    SetScrollPos (hWnd,SB_HORZ,nx,TRUE);
    xv = - nx * SDX ;
    for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next)
      h->SetOrg (xv,yv);
    if (HdLine != NULL)
      HdLine->SetOrg (xv,yv);
    if (LastLine != NULL)
      LastLine->SetOrg (xv,yv);
    InvalidateRect (hWnd,NULL,TRUE);
    }
  }

BOOL FldList::CheckVGrid(LPPOINT pt,LONG FAR *res)
  {
  int x = GetX0();
  for (int i = 0 ; i < AnzColumns () ; i++) {
    x += GetColWidth(i);
    if ((pt->x >= x - FLDOFFS) && (pt->x <= x + FLDOFFS)) {
      *res = TRUE ;
      SetCursor (cmove);
      WState = STATE_VLINEHIT;
      ActVLine = i;
      return TRUE ;
      }
    }
  WState = STATE_NONE;
  return FALSE ;
  }

void FldList::ToLog (POINT FAR *pt,DWORD pos,BOOL IsScreen)
  {
  PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (xv,yv);
  pt->x = LOWORD(pos);
  pt->y = HIWORD(pos);
  if (IsScreen)
    ScreenToClient (hWnd,pt);
  DPtoLP (pc.hDC,pt,1);
  }

LONG FldList::OnSetCursor (WPARAM wP,LONG lP)
  {
  POINT pt;
  ToLog (&pt,GetMessagePos(),TRUE);
  LONG RetVal;
  if ((LOWORD(lP) == HTCLIENT) && (CheckVGrid(&pt,&RetVal))) 
    return RetVal ;
  else
    return DefWindowProc (hWnd,WM_SETCURSOR,wP,lP);
  }

void FldList::DrawVLine (PaintContext *pc,int x)
  {
  int xmin = GetX0() + 4 * FLDOFFS ;
  int xact = GetX0();
  int xp = xact;
  for (int i = 0 ; i < AnzColumns () ; i++) {
    xact += GetColWidth(i);
    if (i == ActVLine)
      break ;
    xmin += GetColWidth(i);
    xp = xact;
    }
  int ymax = LinesToShow() * LineHeight();
  HPEN hOldPen = (HPEN)SelectObject (pc->hDC,GetStockObject (WHITE_PEN));
  SetROP2 (pc->hDC,R2_XORPEN);
  if ((x >= 0) && (x < xmin)) x = xmin;
  int xtod = (x < 0) ? xact : x ;
  *pc << Line(xtod,0,xtod,ymax);
  if (x > 0)
    ColWidth[ActVLine] = x - xp ;
  SelectObject (pc->hDC,hOldPen);
  }

LONG FldList::OnLButtonDown (WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  switch (WState) {
    case STATE_VLINEHIT :
      {
      POINT pt;
      ToLog (&pt,lP,FALSE);
      PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
      pc.LogicalTwips (xv,yv);
      DrawVLine (&pc,-1);
      DrawVLine (&pc,max(0,pt.x));
      }
      break ;
    case STATE_NONE :
      {
      POINT pt;
      pt.x = LOWORD(lP);
      pt.y = HIWORD(lP);
      BOOL res = FALSE ;
      DelActFldName();
      LPFLDLINE oldLine = ActiveLine;
      for (LPFLDLINE h = FirstLine ; ((h != NULL) && (!res)) ; h = h->Next) {
        for (int i = 0 ; i < AnzColumns() ; i++) {
          if (res = h->GetField(i)->OnLButtonDown (wP,pt,0)) {
            OnKillFocus ();
            ActiveLine = h ;
            ActiveCol = i ;
            OnSetFocus ();
            GetActFldName();
            // Eventuell noch den Dropserver initialisieren
            int type = GetDropType (DownColumn);
            if (type)
              DDOnMouseMove (type,ActFldName,&pt,hWnd,FALSE);
            }
          }
        }
      if (!res) {
        for (int i = 0 ; i < AnzColumns() ; i++) {
          if (res = ((LastLine != NULL) && 
                    (LastLine->GetField(i)->OnLButtonDown (wP,pt,0)))) {
            OnKillFocus ();
            ActiveLine = LastLine ;
            ActiveCol = i ;
            OnSetFocus ();
            }
          }
        }
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      }
      break ;
    }
  return RetVal;
  }

LPFLDLINE FldList::SearchField (DWORD lP,int FAR *Col)
  {
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    POINT pt;
    h->ToLog (&pt,lP,FALSE);
    for (int i = 0 ; i < AnzColumns () ; i++) {
      RECT r;
      h->GetField(i)->GetFieldRect (&r,0);
      if (PtInRect (&r,pt)) {
        *Col = i;
        return h;
        }
      }
    }
  return NULL;
  }

LONG FldList::OnLButtonUp (WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  switch (WState) {
    case STATE_VLINEHIT :
      {
      POINT pt;
      ToLog (&pt,lP,FALSE);
      PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
      pc.LogicalTwips (xv,yv);
      DrawVLine (&pc,max(0,pt.x));
      DoSetScrolls();
      SetNewFldPos();
      InvalidateRect (hWnd,NULL,TRUE);
      WState = STATE_NONE;
      }
      break ;
    case STATE_NONE :
      if (ActFldName != NULL) {
        POINT pt;
        pt.x = LOWORD(lP) ;
        pt.y = HIWORD(lP) ;
        int type = GetDropType (DownColumn);
        if (type)
          DDOnMouseMove (type,ActFldName,&pt,hWnd,TRUE);
        DelActFldName();
        }
      break ;
    }
  return RetVal;
  }
  
LONG FldList::MouseMove (WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  switch (WState) {
    case STATE_VLINEHIT :
      if (wP & MK_LBUTTON) {
        POINT pt;
        ToLog (&pt,lP,FALSE);
        PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
        pc.LogicalTwips (xv,yv);
        DrawVLine (&pc,-1);
        DrawVLine (&pc,max(0,pt.x));
        }
      break ;
    case STATE_NONE :
      if ((ActFldName != NULL) && (wP & MK_LBUTTON)) {
        POINT pt;
        pt.x = LOWORD(lP) ;
        pt.y = HIWORD(lP) ;
        int type = GetDropType (DownColumn);
        if (type)
          DDOnMouseMove (type,ActFldName,&pt,hWnd,FALSE);
        }
      break ;
    }
  return RetVal;
  }

void FldList::OnKillFocus ()
  {
  if (ActiveLine != NULL) {
    RECT r;
    ActiveLine->GetField(ActiveCol)->OnKillFocus(0, 0);
    ActiveLine->GetField(ActiveCol)->GetFieldRect (&r,0);
    Invalidate (ActiveLine,&r,FALSE);
    }
  }

void FldList::OnSetFocus ()
  {
  if (ActiveLine != NULL) {
    RECT r;
    ActiveLine->GetField(ActiveCol)->OnSetFocus(TRUE,0);
    ActiveLine->GetField(ActiveCol)->GetFieldRect (&r,0);
    Invalidate (ActiveLine,&r,FALSE);
    }
  }

void FldList::OnChar (WPARAM wP)
  {
  if ((wP != '\t') && (EnableInput())) {
    if (ActiveLine != NULL)
      ActiveLine->GetField(ActiveCol)->OnChar(wP,0);
    }
  else
    SearchInList (wP);
  }

void FldList::PrevField ()
  {
  if (ActiveCol > 0)
    ActiveCol -- ;
  else {
    ActiveLine = GetPrevLine (ActiveLine);
    ActiveCol = AnzColumns()-1;
    }
  }

LPFLDLINE FldList::GetLastLine()
  {
  for (LPFLDLINE x = FirstLine ; x != NULL ; x = x->Next) {
    if (x->Next == NULL) return x ;
    }
  return NULL ;
  }

LPFLDLINE FldList::GetNextLine (LPFLDLINE h)
  {
  if (h == LastLine) return (FirstLine != NULL) ? FirstLine : LastLine ;
  else {
    if (h->Next == NULL) return (LastLine != NULL) ? LastLine : FirstLine ;
    else                 return h->Next;
    }
  }

LPFLDLINE FldList::GetPrevLine (LPFLDLINE h)
  {
  if (h == LastLine) return (FirstLine != NULL) ? GetLastLine() : LastLine ;
  for (LPFLDLINE x = FirstLine ; x != NULL ; x = x->Next) {
    if (x->Next == h) return x ;
    }
  return (LastLine != NULL) ? LastLine : GetLastLine() ;
  }

void FldList::NextField ()
  {
  if (ActiveCol < AnzColumns() -1)
    ActiveCol ++ ;
  else {
    ActiveLine = GetNextLine (ActiveLine);
    ActiveCol = 0;
    }
  }

void FldList::NextLine ()
  {
  LPFLDLINE Next = GetNextLine (ActiveLine);
  if (Next != NULL)
    ActiveLine = Next;
  }

void FldList::PrevLine ()
  {
  LPFLDLINE Prev = GetPrevLine (ActiveLine);
  if (Prev != NULL)
    ActiveLine = Prev;
  }

void FldList::OnKeyDown (WPARAM wP)
  {
  LPFLDLINE oldLine = ActiveLine;
  switch (wP) {
    case VK_TAB :
      {
      BOOL ShiftPressed = (GetKeyState (VK_SHIFT) < 0);
      OnKillFocus ();
      if (ShiftPressed) PrevField();
      else              NextField();
      OnSetFocus ();
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      }
      break ;
    case VK_F7 :
      {
      if (GetKeyState (VK_CONTROL) < 0) {
        HWND hWPrev = GetWindow (hWnd,GW_HWNDPREV);
        if (hWPrev == 0) hWPrev = GetWindow (hWnd,GW_HWNDLAST) ;
        if ((hWPrev) && (hWPrev != hWnd)) SetFocus (hWPrev);
        }
      else {
        HWND hWNext = GetWindow (hWnd,GW_HWNDNEXT);
        if (hWNext == 0) hWNext = GetWindow (hWnd,GW_HWNDFIRST) ;
        if ((hWNext) && (hWNext != hWnd)) SetFocus (hWNext);
        }
      }
      break ;
    case VK_DOWN :
      OnKillFocus ();
      NextLine ();
      OnSetFocus ();
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      break ;
    case VK_NEXT :
      {
      int h = LineHeight ();
      RECT r;
      GetClientRect (hWnd,&r);
      int AnzLines = r.bottom / h - 2 ;
      OnKillFocus () ;
      for (int i = 0 ; (i < AnzLines) ; i++) {
        if (ActiveLine == LastLine) break ;
        if ((ActiveLine->Next == NULL) && (LastLine == NULL)) break ;
        NextLine ();
        }
      OnSetFocus ();
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      }
      break ;
    case VK_UP :
      OnKillFocus ();
      PrevLine ();
      OnSetFocus ();
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      break ;
    case VK_PRIOR :
      {
      int h = LineHeight ();
      RECT r;
      GetClientRect (hWnd,&r);
      int AnzLines = r.bottom / h - 2 ;
      OnKillFocus () ;
      for (int i = 0 ; ((ActiveLine != FirstLine) && (i < AnzLines)) ; i++)
        PrevLine ();
      OnSetFocus ();
      if (oldLine != ActiveLine) {
        InvalidateArrow (oldLine);
        InvalidateArrow (ActiveLine);
        }
      }
      break ;
    case VK_RETURN :
      if ((GetKeyState (VK_CONTROL) < 0) && (ActiveLine != NULL) && (EnableNewContext())) {
        OnKillFocus ();
        ActiveLine = Enlarge ((ActiveLine != LastLine) ? ActiveLine : NULL);
        OnSetFocus ();
        }
      if ((ActiveLine != NULL) && (!EnableNewContext()))
        OnDblClk (ActiveLine,ActiveCol);
      break ;
    default :
      if ((ActiveLine != NULL) && (EnableInput()))
        ActiveLine->GetField(ActiveCol)->OnKeyDown(wP,0);
      break ;
    }
  }

int CheckOneSel (LPSTR Buffer,LPSTR txt)
  {
#ifdef WIN32
  char ch = (char) (DWORD) CharUpper (LPSTR(*txt));
#else
  char ch = (char) (DWORD) AnsiUpper (LPSTR (MAKELP (0,*txt)));
#endif

  int res = -1 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  for ( ; *Buffer ; ) {
#ifdef WIN32
    if (ch == (char) (DWORD) CharUpper (LPSTR(*Buffer))) {
#else
    if (ch == (char) (DWORD) AnsiUpper (LPSTR (MAKELP(0,*Buffer)))) {
#endif

      if (res >= 0) return -1 ;       // nicht eindeutig
      res = i ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    i++ ;
    }
  return res ;
  }

int CheckBestSel (LPSTR Buffer,LPSTR txt)
  {
#ifdef WIN32
  char ch = (char) (DWORD) CharUpper (LPSTR(*txt));
#else
  char ch = (char) (DWORD) AnsiUpper (LPSTR (MAKELP (0,*txt)));
#endif

  int res = 0 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  int olddiff = 10000;
  for ( ; *Buffer ; ) {
    int diff = int (ch) - 
#ifdef WIN32
          (int) (DWORD) CharUpper (LPSTR(*Buffer));
#else
          (int) (DWORD) AnsiUpper (LPSTR (MAKELP(0,*Buffer)));
#endif

    if ((diff >= 0) && (diff < olddiff)) {
      res = i ;
      if (diff == 0) break ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    i++ ;
    }
  return res ;
  }

LPSTR GetSelText (int wInd,LPSTR txt)
  {
  LPSTR ht;
  for (int i = 0 ; i < int (wInd) ; i++) {
    for (ht = txt ; *ht ; ht++) ;
    ht++;
    if (*ht == '\0') break ;       // Doppel - Null -> letzten Satz
                                   // verwenden
    txt = ht ;
    }

  return txt;
  }

void FldList::ShowList (LPSTR str,LPFLDLINE line,int Column)
  {
  if (line == NULL) return ;
  LPSTR resource = GetResource (Column);
  int ActInd = -1;
  LPFIELD field = line->GetField (Column);
  RECT fldRect;
  field->GetFieldRect (&fldRect,0);

  if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
    // Versuchen, ob die Auswahl eindeutig...
    ActInd = CheckOneSel (resource,str);

  if (ActInd < 0) {
    // Nicht direkt gefunden > Liste aufmachen
    int Ind ;
    if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
      // Suchen in der Liste
      Ind = CheckBestSel (resource,str);
    else {
      // Aktuellen Index verwenden
      GLOBALHANDLE hGtmp;
      *field >> hGtmp;
      LPSTR txt = (LPSTR)GlobalLock (hGtmp);
      Ind = CheckBestSel (resource,txt);
      GlobalUnlock (hGtmp);
      GlobalFree (hGtmp);
      }

    SinglList s(resource,Ind);
    RECT cr,fr;
    GetClientRect (hWnd,&cr);
    {
    PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
    pc.LogicalTwips (xv,yv+line->yv);
    pc.LogRecttoPhys (&fr,&fldRect);
    }
    if (s.WorkOn (hWnd,&fr,&cr))
      ActInd = s.res;
    }

  if (ActInd >= 0) {
    // Neues Resultat -> Update
    LPSTR resstr = GetSelText (ActInd,resource);
    *field = resstr;
    field->Reformat();
    Invalidate (line,&fldRect,TRUE);
    Save (line,Column);
    }
  }
/*---< Fenster registrieren, erzeugen und Fensterfunktion >---*/
DLLExport LONG _export FAR PASCAL FldLstWndProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  LPFLDLIST lst = LPFLDLIST (GetWindowLong (hWnd,GWL_FLDLIST));
  if (lst != NULL) {
    LONG RetVal;
    switch (msg) {
      case WM_SETFOCUS :
        lst->OnSetFocus();
        break ;
      case WM_ERASEBKGND :
        lst->EraseBkGnd((HDC)wP);
        break ;
      case WM_CHAR :
        lst->OnChar(wP);
        break ;
      case WM_KEYDOWN :
        lst->OnKeyDown(wP);
        break ;
      case WM_KILLFOCUS :
        lst->OnKillFocus();
        break ;
      case WM_SIZE :
        lst->DoSetScrolls();
        RetVal = DefWindowProc (hWnd,msg,wP,lP);
        break ;
      case WM_PAINT :
        {
        PaintContext pc (hWnd);
        lst->Paint (&pc);
        }
        break ;
      case WM_VSCROLL :
        lst->OnVScroll(wP,lP);
        break ;
      case WM_HSCROLL :
        lst->OnHScroll(wP,lP);
        break ;
      case WM_SETCURSOR :
        RetVal = lst->OnSetCursor (wP,lP);
        break ;
      case WM_LBUTTONDOWN :
        SetFocus (hWnd);
        SetCapture (hWnd);
        RetVal = lst->OnLButtonDown (wP,lP);
        break ;
      case WM_LBUTTONDBLCLK :
        {
        int Col;
        LPFLDLINE h = lst->SearchField (lP,&Col);
        if (h != NULL)
          lst->OnDblClk (h,Col);
        }
        break ;
      case WM_LBUTTONUP :
        ReleaseCapture ();
        RetVal = lst->OnLButtonUp (wP,lP);
        break ;
      case WM_MOUSEMOVE :
        RetVal = lst->MouseMove (wP,lP);
        break ;
      case WM_COMMAND :
        {
        CRACKER_VARS
        CRACK_MESSAGEsc

        switch (CRACKER_wID) {
          case 1000 :
            if (lst->EnableNewContext ()) {
              lst->OnKillFocus ();
              lst->ActiveLine = lst->RemoveLine(lst->ActiveLine);
              lst->OnSetFocus ();
              }
            break ;
          case 1001 :
            if (lst->EnableNewContext ()) {
              lst->OnKillFocus ();
              lst->ActiveLine = lst->Enlarge((lst->ActiveLine != lst->LastLine) ? lst->ActiveLine : NULL);
              lst->OnSetFocus ();
              }
            break ;
          default :
            lst->OnCommand (CRACKER_wID);
          }
        }
        break ;
      case WM_CLOSE :
        if (lst->AllowClose ())
          DestroyWindow (hWnd);
        RetVal = 0L;
        break ;
      case WM_DESTROY :
        ResetWindowHandles (hWnd);
        lst->WritePos();
        lst->WriteColWidth();
        lst->OnDestroy();
        delete lst;
        break ;
      default :
        RetVal = DefWindowProc (hWnd,msg,wP,lP);
      }
    return RetVal ;
    }
  else
    return DefWindowProc (hWnd,msg,wP,lP);
  }

static char szFldClassName[] = "FLDLIST";
void FldList::Register()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wc;
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = FldLstWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = MyInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = GetMenuName();
    wc.lpszClassName = szFldClassName;

    RegisterClass (&wc);
    Registered = TRUE;
    }
  }

extern HWND hwndFrame;
void FldList::Create(HWND hW)
  {
  if (hW == 0) {
    Register ();

    HMENU hmenu = LoadMenu (MyInstance,GetMenuName());
    int x,y,w,h;
    GetPos (&x,&y,&w,&h);
    hWnd = CreateWindow(szFldClassName, Caption, 
                            WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_HSCROLL | WS_VSCROLL | WS_SYSMENU,
                            x,y,w,h,
                            hwndFrame, hmenu,
                            MyInstance, NULL
                      );
    }
  else {
    hWnd = hW ;
    SetWindowLong (hWnd,GWL_WNDPROC,LONG(FldLstWndProc));
    }
  SetWindowLong (hWnd,GWL_FLDLIST,LONG(this));
  vdrop = new VarList_Drop (hWnd,hWnd);
  vdrop->AddType (DDTYPE_TABLE);

  BuildList ();
  }

void VarList_Drop::DoDrop (LPVOID dropData, WORD Type)
  {
  LPFLDLIST lst = LPFLDLIST (GetWindowLong (DropWnd,GWL_FLDLIST));
  DWORD pos = GetMessagePos ();
  POINT pt;
  pt.x = LOWORD(pos);
  pt.y = HIWORD(pos);
  ScreenToClient (DropWnd,&pt);
  lst->DoDrop (pt.x,pt.y,dropData,Type);
  }

void FldList::Show ()
  {
  ShowWindow (hWnd,SW_SHOW);
  }

void FldList::Hide ()
  {
  ShowWindow (hWnd,SW_HIDE);
  }

/*----< Konstruktor, Destruktor >-----*/
FldList FAR *FirstFldList;
FldList::FldList (LPVOID Cntx,LPSTR cptn)
  {
  cmove = LoadCursor (MyInstance,"CMOVE");
  hActivePen = hInactivePen = (HPEN)GetStockObject (NULL_PEN);
  BaseContext = Cntx;
  Caption = LPSTR(GetGlobMem (lstrlen(cptn)+1));
  lstrcpy (Caption,cptn);
  Next = FirstFldList ;
  FirstFldList = this ;
  }

FldList::~FldList ()
  {
  for ( ; FirstLine != NULL ; ) {
    LPFLDLINE Next = FirstLine->Next;
    delete FirstLine;
    FirstLine = Next;
    }
  if (ColWidth != NULL) FreeGlobMem(ColWidth);
  if (LastLine != NULL) delete LastLine;
  if (HdLine != NULL) delete HdLine;
  FreeGlobMem (Caption);
  DestroyCursor (cmove);
  FldList FAR *prev = NULL;

  for (FldList FAR *h = FirstFldList ; h != NULL ; h = h->Next) {
    if (h == this) {
      if (prev != NULL) prev->Next = h->Next;
      else              FirstFldList = h->Next;
      break ;
      }
    prev = h ;
    }
  if (ActFldName != NULL)
    FreeGlobMem (ActFldName);
  vdrop->RemoveFromList();
  }

LPFLDLINE FldList::RemoveLine (LPFLDLINE Line)
  {
  if ((ActiveLine == NULL) ||
      (ActiveLine == LastLine)) return ActiveLine;
  LPFLDLINE prev = NULL;
  LPFLDLINE res = ActiveLine;
  int dy = LineHeight();
  int y = dy;
  BOOL doMove = FALSE ;
  for (LPFLDLINE h = FirstLine ; h != NULL ; ) {
    if (h == Line) {
      LPFLDLINE n =  h->Next;
      if (prev != NULL) prev->Next = h->Next;
      else              FirstLine  = h->Next;
      if (n != NULL) res = n;
      else           res = FirstLine;
      delete h ;
      h = n;
      doMove = TRUE ;
      continue ;
      }
    if (doMove) {
      int x = GetX0();
      for (int i = 0 ; i < AnzColumns () ; i++) {
        h->SetFldPos (i,x);
        x += GetColWidth(i);
        }
      h->SetYV (y);
      }
    y += dy ;
    prev = h;
    h = h->Next;
    }
  if ((doMove) && (LastLine != NULL)) {
    int x = GetX0();
    for (int i = 0 ; i < AnzColumns () ; i++) {
      LastLine->SetFldPos (i,x);
      x += GetColWidth(i);
      }
    LastLine->SetYV (y);
    }
  DoSetScrolls();
  InvalidateRect (hWnd,NULL,TRUE);
  return res;
  }

LPFLDLINE FldList::Enlarge (LPFLDLINE LineBefore)
  {
  LPFLDLINE res = NULL;
  if (LineBefore == NULL) {
    if (LastLine != NULL) {
      LPFLDLINE h = GetLastLine();
      res = LastLine;
      if (h != NULL) h->Next = LastLine;
      else           FirstLine = LastLine;
      int dy = LineHeight();
      h = FirstLine ;
      for (int y = dy ; h != NULL ; h = h->Next)
        y += dy ;
      BuildLastLine (y);
      }
    else {
      LPFLDLINE l = new FldLine (AnzColumns(),WORD(-1),this);
      int x = GetX0();
      int dy = LineHeight();
      int y = dy ;
      for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
        y += dy ;
        if (h->Next == NULL) break ;
        }
      for (int i = 0 ; i < AnzColumns() ; i++) {
        FieldCallBack cbmem;
        cbmem.column = i;
        cbmem.line = l;
        cbmem.list = this;

        int w = GetColWidth(i);
        l->SetField(GetField(hWnd,x,w,GetFormat(),"",
                            &cbmem,GetColMode(i)),
                    i);
        x += w ;
        }
      l->SetYV (y);
      if (h != NULL) h->Next = l;
      else           FirstLine = l;
      res = l;
      }
    }
  else {
    LPFLDLINE prev = NULL ;
    int dy = LineHeight();
    int y = dy ;
    BOOL doMove = FALSE ;
    for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
      if (h == LineBefore) {
        LPFLDLINE l = new FldLine (AnzColumns(),WORD(-1),this);
        int x = GetX0();
        for (int i = 0 ; i < AnzColumns() ; i++) {
          FieldCallBack cbmem;
          cbmem.column = i;
          cbmem.line = l;
          cbmem.list = this;

          int w = GetColWidth(i);
          l->SetField(GetField(hWnd,x,w,GetFormat(),"",
                              &cbmem,GetColMode(i)),
                      i);
          x += w ;
          }
        l->SetYV(y);
        if (prev != NULL) prev->Next = l;
        else              FirstLine = l;
        l->Next = h;
        res = l;
        doMove = TRUE ;
        }
      y += dy ;
      prev = h;

      if (doMove) {
        int x = GetX0();
        for (int i = 0 ; i < AnzColumns () ; i++) {
          h->SetFldPos (i,x);
          x += GetColWidth(i);
          }
        h->SetYV (y);
        }
      }
    int x = GetX0();
    for (int i = 0 ; i < AnzColumns () ; i++) {
      LastLine->SetFldPos (i,x);
      x += GetColWidth(i);
      }
    LastLine->SetYV (y);
    }
  DoSetScrolls();
  InvalidateRect (hWnd,NULL,TRUE);

  return res;
  }

/*--< Implementierung der virtuellen Funktionen fuer Feldbearbeitung >--*/
int FldList::AnzColumns()
  {
  return 1;
  }
int FldList::GetX0()
  {
  return 0 ;
  }

DWORD FldList::GetColMode (int Column)
  {
  return FM_OUTLINEONLY ;
  }

LPSTR FldList::GetFieldString (LPVOID Context,int Column)
  {
  return "";
  }

LPSTR FldList::GetHdString (int Column)
  {
  return "";
  }

void FldList::Save (LPFLDLINE line,int column)
  {
  }

int FldList::GetFormat()
  {
  return 2 ;
  }

LPVOID FldList::GetFirstContext()
  {
  return NULL;
  }

LPVOID FldList::GetNextContext(LPVOID oldContext)
  {
  return NULL;
  }

BOOL FldList::EnableNewContext()
  {
  return FALSE ;
  }

LPSTR FldList::GetMenuName()
  {
  return "";
  }

void FldList::OnDestroy()
  {
  }

LPSTR FldList::ProfBase()
  {
  return "";
  }

LPSTR FldList::GetResource (int Column)
  {
  static char res[2];
  res[0] = res[1] = '\0';
  return res;
  }

BOOL FldList::EnableInput ()
  {
  return FALSE ;
  }

int FldList::GetColWidth(int Column)
  {
  return 4000 ;
  }

void FldList::OnDblClk(LPFLDLINE line,int column)
  {
  }

void FldList::SearchInList (WORD wP)
  {
  }

BOOL FldList::AllowClose()
  {
  return TRUE ;
  }

void FldList::OnCommand (WORD wP)
  {
  }

/*------< Speicherhilfsfunktionen >------*/
BOOL FldList::GetFieldContent (LPSTR res,LPFLDLINE h,int Column)
  {
  GLOBALHANDLE hGTxt;
  cField FAR *f = h->GetField (Column);
  *f >> hGTxt;
  LPSTR t = (LPSTR)GlobalLock (hGTxt);
  lstrcpy (res,t);
  GlobalUnlock (hGTxt);
  GlobalFree (hGTxt);
  for (LPSTR x = res ; *x ; x++) {
    if ((!IsCharAlphaNumeric(*x)) && (!(*x == '_'))) {
      *x = '\0';
      }
    }
  return ((IsCharAlphaNumeric(*res)) || (*res == '_'));
  }

BOOL FldList::GetFieldSent (LPSTR res,LPFLDLINE h,int Column)
  {
  GLOBALHANDLE hGTxt;
  cField FAR *f = h->GetField (Column);
  *f >> hGTxt;
  LPSTR t = (LPSTR)GlobalLock (hGTxt);
  lstrcpy (res,t);
  GlobalUnlock (hGTxt);
  GlobalFree (hGTxt);
  return *res ;
  }

int FldList::GetDropType (int DownColumn)
  {
  return 0 ;
  }

BOOL FldList::GetFieldRes (LPSTR res,LPFLDLINE h,int Column,BOOL mustExist)
  {
  BOOL iscorrect = GetFieldSent (res,h,Column);
  if (!iscorrect) return !mustExist ;
  else            return TRUE ;
  }

BOOL FldList::GetFieldWord (LPSTR res,LPFLDLINE h,int Column,BOOL mustExist)
  {
  BOOL iscorrect = GetFieldContent (res,h,Column);
  if (!iscorrect) return !mustExist ;
  else {
    for (LPSTR h = res ; *h ; h++)
      iscorrect = iscorrect && ((*h >= '0') && (*h <= '9')) ;
    }
  return iscorrect;
  }

void FldList::GetActFldName()
  {
  if (ActFldName != NULL)
    FreeGlobMem (ActFldName);
  char buffer[256];
  DownColumn = 0;
  ActFldName = NULL;
  if (ActiveLine != NULL) {
    if (GetFieldContent (buffer,ActiveLine,ActiveCol)) {
      int s1 = lstrlen (Caption) + 1 ;
      ActFldName = LPSTR (GetGlobMem (lstrlen(buffer)+1 + s1));
      lstrcpy (ActFldName,buffer);
      lstrcpy (ActFldName + lstrlen(buffer) + 1,Caption);
      DownColumn = ActiveCol;
      }
    }
  }

void FldList::DelActFldName()
  {
  if (ActFldName != NULL)
    FreeGlobMem (ActFldName);
  ActFldName = NULL;
  DownColumn = 0;
  }

void FldList::ModifyContent (LPFLDLINE line,int column,LPSTR str)
  {
  RECT r1,r2;
  cField FAR *f = line->GetField(column);
  f->GetFieldRect (&r1, 0) ;
  *f = str ;
  f->GetFieldRect (&r2, 0) ;
  Invalidate (line,&r1,TRUE);
  Invalidate (line,&r2,TRUE);
  }

void FldList::Fehler (LPSTR String)
  {
  MessageBox (hWnd,String,"Fehler",MB_OK | MB_TASKMODAL | MB_ICONEXCLAMATION);
  }

cField FAR *FldList::GetFieldFromPos (int FAR *Column,LPFLDLINE FAR *l,int xp,int yp)
  {
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    POINT pt;
    h->ToLog (&pt,MAKELONG(xp,yp),FALSE);
    int x = GetX0();
    for (int i = 0 ; i < AnzColumns() ; i++) {
      if ((pt.x >= x) && (pt.x <= x + GetColWidth(i)) &&
          ((yp >= h->yv) && (yp < h->yv + LineHeight()))) {
        *Column = i ;
        *l = h ;
        return h->GetField(i);
        }
      x += GetColWidth(i);
      }
    }
  if (LastLine != NULL) {
    POINT pt;
    LastLine->ToLog (&pt,MAKELONG(xp,yp),FALSE);
    int x = GetX0();
    for (int i = 0 ; i < AnzColumns() ; i++) {
      if ((pt.x >= x) && (pt.x <= x + GetColWidth(i)) &&
          ((yp >= LastLine->yv) && (yp < LastLine->yv + LineHeight()))) {
        *Column = i ;
        *l = LastLine ;
        return LastLine->GetField(i);
        }
      x += GetColWidth(i);
      }
    }
  return NULL ;
  }

/*-----< Implementierung der Klasse FldCheck >------*/
BOOL FldCheck::CheckName (LPSTR Name)
  {
  // Ueberpruefen, ob keine Ziffer vorne
  if ((*Name >= '0') && (*Name <= '9')) return FALSE ;

  // Durchsuchen aller bisherigen Namen
  char buffer[256],buffer1[256];
  lstrcpy (buffer,Name);
  AnsiUpper (buffer);
  for (FldName FAR *h = List ; h != NULL ; h = h->Next) {
    lstrcpy (buffer1,h->Name);
    AnsiUpper (buffer1);
    if (lstrcmp (buffer1,buffer) == 0) return FALSE ;
    }
  // Alles in Ordnung, in die Liste haengen
  FldName FAR *n = (FldName FAR *) GetGlobMem (sizeof(*n));
  n->Name = LPSTR (GetGlobMem (lstrlen(Name)+1));
  lstrcpy (n->Name,Name);
  n->Next = List ;
  List = n;
  return TRUE ;
  }

BOOL FldCheck::FieldExist (LPSTR Name)
  {
  // Durchsuchen aller bisherigen Namen
  for (FldName FAR *h = List ; h != NULL ; h = h->Next) {
    if (lstrcmp (h->Name,Name) == 0) return TRUE ;
    }
  return FALSE ;
  }

FldCheck::~FldCheck ()
  {
  for ( ; List != NULL ; ) {
    FldName FAR *n = List->Next ;
    FreeGlobMem (List->Name);
    FreeGlobMem (List);
    List = n;
    }
  }

/*------< Accellerator - Definition >------*/
HWND GetActiveFldWnd ()
  {
  HWND ActWnd = GetFocus ();
  for (FldList FAR *h = FirstFldList ; h != NULL ; h = h->Next)
    if (h->hWnd == ActWnd) return ActWnd;
  return NULL;
  }

static HACCEL FldAcc;
BOOL CheckFldListAccellerator (MSG FAR *msg)
  {
  if (FldAcc == 0) FldAcc = LoadAccelerators (MyInstance,"FldAcc") ;
  HWND FldWnd = GetActiveFldWnd ();
  if (IsWindow (FldWnd))
    return TranslateAccelerator(FldWnd, FldAcc, msg);
  else
    return FALSE ;
  }


