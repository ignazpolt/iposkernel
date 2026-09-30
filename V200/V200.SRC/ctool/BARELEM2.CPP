//
//  $Header:   P:/marille/clinicum/ctool/rev/barelem2.cpv   1.16   18 Nov 1998 19:12:54   Hannes  $
//  $Log:   P:/marille/clinicum/ctool/rev/barelem2.cpv  $
// 
//    Rev 1.16   18 Nov 1998 19:12:54   Hannes
// Ohne Vertiefung bei Klasse EWCG
// 
//    Rev 1.15   14 Sep 1998 03:26:16   Hannes
// Update Listen / ToolEdits
// 
//    Rev 1.14   08 Jul 1998 16:27:44   Hannes
// No change.
// 
//    Rev 1.13   08 Jul 1998 16:19:28   Hannes
// Connection auf die Koordinaten in ExternTool
// 
//    Rev 1.12   29 Aug 1996 16:32:50   GERHOLD
// ExternTool::OnRButtonDown  =>  tool::OnRButtonDown
// 
//    Rev 1.11   16 Jun 1996 18:45:16   GERHOLD
// int -> DBINT, BOOL -> DBBOOL
// rechte Maustaste
// 
//    Rev 1.10   06 May 1996 23:52:34   HANNES
// ExternTool::Reset anders herum aufgezogen
// 
//    Rev 1.9   24 Mar 1996 12:10:06   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.0   29 Nov 1993 08:37:52   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define MODULENUM  111
#include "winass.hpp"
#include "toolbar.hpp"
#include "globmem.h"

typedef tool FAR *LPTOOL;
DLLExport void _export WINAPI MoveElems (LPMOVEELEMPAR par,LPVOID privData)
  {
  if (par->AnzElems() == 0) return ;
  // Berechnen des Umgebenden Rechteckes
  RECT r;
  SetRectEmpty (&r);
  HWND hWndParent = 0;
  int xSpace,ySpace;
  for ( int i = 0 ; i < par->AnzElems() ; i++) {
    LPTOOL FAR *t = (LPTOOL FAR *) ((* GetData) (privData,par->elem[i]));
    DBWIN_ASSERT ((t != NULL) && (*t != NULL));
    (*t)->dxPhys = (*t)->dxPhys = 0 ;
    (*t)->GetRect();
    UnionRect (&r,&r,LPRECT(&(*t)->ToolRect));
    HWND hWnd = (*t)->Parent->Parent->hWndToolbar();
    DBWIN_ASSERT ((hWndParent == 0) || (hWndParent == hWnd));
    hWndParent = hWnd;
    if (i == 0) {
      DBINT FAR *lpx = (DBINT FAR *) (* GetData) (privData,par->xSpace);
      DBINT FAR *lpy = (DBINT FAR *) (* GetData) (privData,par->ySpace);
      DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL)) ;
      xSpace = (*t)->ToDevKoordX(*lpx);
      ySpace = (*t)->ToDevKoordX(*lpy);
      }
    }
  // Berechnung der Verschiebung
  RECT rc;
  GetClientRect (hWndParent,&rc);
  int dx,dy;
  if (xSpace < 0)
    // An die rechte Kante
    dx = rc.right - r.right - int(- xSpace);
  else if (xSpace > 0)
    // An die linke Kante
    dx = int (xSpace) - r.left ;
  else
    dx = 0;

  if (ySpace < 0)
    // An die untere Kante
    dy = rc.bottom - r.bottom - int(- ySpace);
  else if (ySpace > 0)
    dy = int(ySpace) - r.top ;
  else
    dy = 0;

  // Nun die eigentliche Verschiebung
  for ( i = 0 ; i < par->AnzElems() ; i++) {
    LPTOOL FAR *t = (LPTOOL FAR *) ((* GetData) (privData,par->elem[i]));
    DBWIN_ASSERT ((t != NULL) && (*t != NULL));
    (*t)->dxPhys = dx;
    (*t)->dyPhys = dy;
    (*t)->GetRect();
    }
  }

typedef ExternTool FAR *LPEXTERNTOOL ;
DLLExport void _export WINAPI SetExtToolDimension (LPEXTTOOLDIM par,LPVOID privData)
  {
  LPEXTERNTOOL FAR *t = (LPEXTERNTOOL FAR *) ((* GetData) (privData,par->exttool));
  DBWIN_ASSERT ((t != NULL) && (*t != NULL));
  RECT rWnd,rParent;
  GetWindowRect ((*t)->hExtWnd,&rWnd);
  GetClientRect (GetParent((*t)->hExtWnd),&rParent);
  ScreenToClient ((*t)->Parent->Parent->hWndToolbar(),LPPOINT(&rWnd.left));
  ScreenToClient ((*t)->Parent->Parent->hWndToolbar(),LPPOINT(&rWnd.right));
  int dx,dy;
  DBINT FAR *lpx = (DBINT FAR *) (* GetData) (privData,par->x);
  DBINT FAR *lpy = (DBINT FAR *) (* GetData) (privData,par->y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL)) ;
  int x = (*t)->ToDevKoordX(*lpx);
  int y = (*t)->ToDevKoordX(*lpy);
  if (x > 0) {
    dx = x - rWnd.right;
    }
  else if (x < 0) {
    dx = rParent.right + x - rWnd.right ;
    }
  else
    dx = 0;
  if (y > 0) {
    dy = y - rWnd.bottom;
    }
  else if (y < 0) {
    dy = rParent.bottom + y - rWnd.bottom ;
    }
  else
    dy = 0;

  if ((dx != 0) || (dy != 0)) {
    SetWindowPos ((*t)->hExtWnd,NULL,0,0,rWnd.right - rWnd.left + dx,rWnd.bottom - rWnd.top + dy,
                                SWP_NOZORDER | SWP_NOMOVE
                 );
    (*t)->GetRect ();
    }
  }



/*****************************************************************************\
*                                                                             *
*        EXTERN - TOOL                                                        *
*                                                                             *
\*****************************************************************************/
ExternTool::ExternTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
      : tool (RefWnd,Data,pData,pSize)
  {
  ExtFnc = (* GetExtFnc) (Param()->hd.ToolType,NULL);
  }

void ExternTool::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBINT FAR *lpw = (DBINT FAR*)(* GetData)(privData, ExtPar()->_w);
  DBINT FAR *lph = (DBINT FAR*)(* GetData)(privData, ExtPar()->_h);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL) && (lpw != NULL) && (lph != NULL));
  tx = *lpx;
  ty = *lpy;
  tw = *lpw;
  th = *lph;
  DBWIN_ASSERT (ExtFnc != NULL);
  DBBOOL FAR *IsDisabled = (DBBOOL FAR *) 
          (* GetData) (privData,ExtPar ()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));

  DoExtern_Param p;
  p.load.privData = privData;
  HWND hWParent = Parent->Parent->hWndToolbar();
  int x = ToDevKoordX (tx);
  int y = ToDevKoordY (ty, Parent->Layer);
  int w = ToDevX (tw);
  int h = ToDevKoordY (ty + th,Parent->Layer) - y ;

  p.load.hWParent = Parent->Parent->hWndToolbar();
  p.load.x = ToDevKoordX (tx);
  p.load.y = ToDevKoordY (ty, Parent->Layer);
  p.load.w = ToDevX (tw);
  p.load.h = ToDevKoordY (ty + th,Parent->Layer) -
                p.load.y ;
  (* ExtFnc) (StructData, DO_LOAD, &p);
  extObj = p.load.objData;
  
  hExtWnd = p.load.hWnd;
  DBWIN_ASSERT (hExtWnd != 0);

  GetRect ();
  }

WORD ExternTool::Id()
  {
  if (hExtWnd)

#ifdef WIN32
    return LOWORD(GetWindowLong (hExtWnd,GWL_ID));
#else
    return GetWindowWord (hExtWnd,GWW_ID);
#endif

  else
    return 0xFFFF;
  }

LPSTR ExternTool::GetHelpText ()
  {
  DoExtern_Param p;
  p.gethelptext.privData = privData;
  p.gethelptext.objData = extObj;
  (* ExtFnc) (StructData,DO_GETHELP,&p);

  return p.gethelptext.helpText;
  }

void ExternTool::GetRect ()
  {
  GetWindowRect (hExtWnd,LPRECT(&ToolRect));
  ScreenToClient (Parent->Parent->hWndToolbar(),LPPOINT(&ToolRect.left));
  ScreenToClient (Parent->Parent->hWndToolbar(),LPPOINT(&ToolRect.right));
  if (ty >= 0)
    Parent->CheckLayerHeight (ToolRect.bottom);
  }

void ExternTool::Update ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBINT FAR *lpw = (DBINT FAR*)(* GetData)(privData, ExtPar()->_w);
  DBINT FAR *lph = (DBINT FAR*)(* GetData)(privData, ExtPar()->_h);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL) && (lpw != NULL) && (lph != NULL));
  if ((tx != *lpx) || (ty != *lpy) || (tw != *lpw) || (th != *lph)) {
    Invalidate (TRUE);
    tx = *lpx;
    ty = *lpy;
    tw = *lpw;
    th = *lph;
    int xw = ToDevKoordX (tx);
    int yw = ToDevKoordY (ty, Parent->Layer);
    int ww = ToDevX (tw);
    int hw = ToDevKoordY (ty + th,Parent->Layer) - yw;
    MoveWindow (hExtWnd,xw,yw,ww,hw,TRUE);
    GetRect ();
    Invalidate (TRUE);
    }
  else {
    DoExtern_Param p;
    p.update.objData = extObj;
    p.update.privData = privData;
    (* ExtFnc) (StructData,DO_UPDATE,&p);
    }
  }

void ExternTool::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 3, 3);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }

void ExternTool::FixConnection ()
  {
  DoExtern_Param p;
  p.fixconnection.objData = extObj;
  p.fixconnection.privData = privData;
  (* ExtFnc) (StructData,DO_SETCONNECTION,&p);
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->hd.HotKey, StructData);
  (* SetConnection) (privData, ExtPar()->_w, StructData);
  (* SetConnection) (privData, ExtPar()->_h, StructData);
  }

void ExternTool::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  DoExtern_Param p;
  p.reset.objData = extObj;
  p.reset.privData = privData;
  p.reset.doClear = doClear;
  hExtWnd = 0;
  (* ExtFnc) (StructData,DO_RESET,&p);
  extObj = p.reset.objData;
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);
  (* ClearConnection) (privData, Param()->hd.HotKey, StructData);
  (* ClearConnection) (privData, ExtPar()->_w, StructData);
  (* ClearConnection) (privData, ExtPar()->_h, StructData);
  }

void ExternTool::PaintTool (HDC hDC, HDC hmemDC)
  {
//  RECT rc;

  char ClassName[64];
  GetClassName (hExtWnd,ClassName,sizeof(ClassName));
  if (lstrcmp (ClassName,"EWCG") == 0) return;
  if (IsWindow(hExtWnd)) {
    MyDrawEdge (hDC, LPRECT(&ToolRect), MY_EDGE_HWND, MY_BF_ADJUST);
/*
    CopyRect (&rc, LPRECT(&ToolRect));
    InflateRect (&rc, 3, 2);

    HBRUSH OldBrush = SelectObject (hDC, GetStockObject(NULL_BRUSH));
    HPEN OldPen = SelectObject(hDC, GetStockObject(WHITE_PEN));
    Rectangle (hDC, rc.left, rc.top, 
                    rc.right, rc.bottom+1);
    SelectObject (hDC, OldPen);

    OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
    MoveToEx (hDC, rc.left, rc.bottom-1, NULL);
    LineTo (hDC, rc.left, rc.top);
    LineTo (hDC, rc.right-1, rc.top);
    DeleteObject (SelectObject(hDC, OldPen));

    OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0xC0, 0xC0, 0xC0)));
    Rectangle (hDC, rc.left+1, rc.top+1, rc.right-1, rc.bottom);
    DeleteObject (SelectObject(hDC, OldPen));

    SelectObject (hDC, OldBrush);

    OldPen = SelectObject(hDC, GetStockObject(BLACK_PEN));
    MoveToEx (hDC, rc.left+1, rc.bottom-2, NULL);
    LineTo (hDC, rc.left+1, rc.top+1);
    LineTo (hDC, rc.right-2, rc.top+1);
    SelectObject (hDC, OldPen);
*/
    }
  }

ExternTool::~ExternTool ()
  {
  (* GetExtFnc) (Param()->hd.ToolType,ExtFnc);
  }

void ExternTool::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT (&ToolRect),0,dy);
    MoveWindow (hExtWnd,ToolRect.left,ToolRect.top,
                        ToolRect.right - ToolRect.left + 1,
                        ToolRect.bottom - ToolRect.top + 1,TRUE
               );
    Invalidate (FALSE);
    }
  }

void ExternTool::OnActivate (BOOL ActivateFlag)
  {
  DoExtern_Param p;
  p.activate.objData = extObj;
  
  p.activate.flag = ActivateFlag;
  if (ExtFnc != NULL)
    (* ExtFnc) (StructData,DO_ACTIVATE,&p);
  ShowWindow (hExtWnd, (ActivateFlag) ? SW_SHOW : SW_HIDE);
  }

void ExternTool::OnRButtonDown (HMENU hPopupMenu)
  {
  tool::OnRButtonDown (hPopupMenu);
  // AppendMenu (hPopupMenu, MF_SEPARATOR, -1, NULL);
  // hier kommt dann der Aufruf einer (* ExtFnc)
  }

BOOL ExternTool::HasTabStop ()
  {
  return IsEnabled ;
  }

void ExternTool::HotKeyAction (BOOL dontCheckEnabled)
  {
  SetFocus (hExtWnd);
  }

void ExternTool::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  DoExtern_Param p;
  p.focus.done = FALSE ;
  p.activate.objData = extObj;
  if ((mode != FOCUSMODE_NONE) && (state)) {
    p.focus.mode = mode ;
    if (ExtFnc != NULL)
      (* ExtFnc) (StructData,DO_SETFOCUS,&p);
    }
    
  // Focus natuerlich nur setzen, wenn er nicht schon da war!
  if (!p.focus.done) {
    if (state && ((GetFocus() != hExtWnd) || (Parent->Parent->ToolWithFocus != this))) 
      SetFocus (hExtWnd);
    }
  }

