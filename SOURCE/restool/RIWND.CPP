/*
**  gr. Darstellung der RI zwischen verschiedenen Tabellen
*/
//
//  $Header:   P:/marille/clinicum/restool/rev/riwnd.cpv   1.11   05 Oct 1998 11:27:52   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/riwnd.cpv  $
// 
//    Rev 1.11   05 Oct 1998 11:27:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   07 Aug 1998 13:21:22   Hannes
// StartPrint
// 
//    Rev 1.9   15 Dec 1997 17:37:08   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.8   05 Nov 1997 09:15:10   Gerhold
// 32 Bit
// 
//    Rev 1.7   28 Aug 1997 15:49:02   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   26 Nov 1996 08:09:46   HANNES
// Automatischer Update
// 
//    Rev 1.5   24 Mar 1996 12:16:46   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:50:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   26 Apr 1995 15:27:02   HANNES
// 
//    Rev 1.2   03 Mar 1995 11:05:24   HANNES
// 
//    Rev 1.1   24 Feb 1995 11:11:58   GERHOLD
// 
//    Rev 1.0   16 Feb 1995 12:41:14   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "drdrop.hpp"
#include "font.hpp"
#include "printer.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "cfield.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "riwnd.hpp"
#include "fldlst.hpp"
#include "jlst.hpp"

const int WndExtX = 20000 , WndExtY = 20000 ;
const int gdx = 200  , gdy = 200 ;
const int sdx = 50   , sdy = 50 ;
const int mdx = 100  , mdy = 100 ;
const int TableFormat = 1000;

#define GWL_RILIST    0L
#define SBU_THUMBVAL	    (SB_ENDSCROLL+1)
static BOOL IsCaptured,IsTimerSet;
static void Scroll (HWND hWnd)
  {
  // Untersuchen, ob x und y ausserhalb des Client - Bereiches liegt
  // wenn ja, dann entsprechenden Scroll weiterleiten
  POINT pt;
  GetCursorPos (&pt);
  ScreenToClient (hWnd,&pt);
  RECT r;
  GetClientRect (hWnd,&r);
  if (pt.x < r.left)
    PostMessage (hWnd,WM_HSCROLL,SB_LINEUP,0L);
  if (pt.x > r.right)
    PostMessage (hWnd,WM_HSCROLL,SB_LINEDOWN,0L);
  if (pt.y < r.top)
    PostMessage (hWnd,WM_VSCROLL,SB_LINEUP,0L);
  if (pt.y > r.bottom)
    PostMessage (hWnd,WM_VSCROLL,SB_LINEDOWN,0L);
  }

static BOOL IsInWnd (HWND hWnd)
  {
  POINT pt;
  GetCursorPos (&pt);
  ScreenToClient (hWnd,&pt);
  RECT r;
  GetClientRect (hWnd,&r);
  return PtInRect (&r,pt);
  }

static void SetupTracking (HWND hWnd)
  {
  if (!IsCaptured) {
    // Capture der Mouse
    SetCapture (hWnd);
    IsCaptured = TRUE ;
    }
  if (IsCaptured) {
    if ((!IsTimerSet) && (!IsInWnd (hWnd))) {
      // Aufsetzen eines Timers
      SetTimer (hWnd,0,100,NULL);
      IsTimerSet = TRUE ;
      // Scrollen
      Scroll (hWnd);
      }
    else if ((IsTimerSet) && (IsInWnd (hWnd))) {
      // Loeschen des Timers
      KillTimer (hWnd,0);
      IsTimerSet = FALSE ;
      }
    }
  }

void EndTracking (HWND hWnd)
  {
  if (IsCaptured) {
    if (IsTimerSet) {
      // Loeschen des Timers
      KillTimer (hWnd,0);
      IsTimerSet = FALSE ;
      }
    // Capture ausschalten
    ReleaseCapture ();
    IsCaptured = FALSE ;
    }
  }

DLLExport LONG _export FAR PASCAL riWndProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  LPRISHOW r = LPRISHOW (GetWindowLong (hWnd,GWL_RILIST));
  if (r == NULL) return DefWindowProc (hWnd,msg,wP,lP);
  switch (msg) {
    case WM_VSCROLL :
      r->OnVScroll(wP,lP);
      break ;
    case WM_HSCROLL :
      r->OnHScroll(wP,lP);
      break ;
    case WM_MOUSEMOVE :
      if (wP & MK_LBUTTON)
        SetupTracking (hWnd);
      else
        EndTracking (hWnd);
      r->OnMouseMove (lP);
      break ;
    case WM_LBUTTONDOWN :
      SetupTracking (hWnd);
      r->OnLButtonDown (lP);
      break ;
    case WM_LBUTTONUP :
      EndTracking (hWnd);
      r->OnLButtonUp (lP);
      break ;
    case WM_LBUTTONDBLCLK :
      r->OnDblClk ();
      break ;
    case WM_TIMER :
      if (wP == 0)
        Scroll (hWnd);
      break ;
    case WM_PAINT :
      {
      PaintContext pc (hWnd);
      pc.LogicalTwips (r->xv,r->yv);
      r->PaintGrid(&pc);
      r->Paint (&pc);
      }
      break ;
    case WM_DESTROY :
      delete r;
      break ;
    case WM_CLOSE :
      RetVal = r->OnClose ();
      break ;
    case WM_KEYDOWN :
      if (wP == VK_DELETE) {
        r->DelElem ();
        }
      else if (wP == VK_F7) {
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
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case 102 :
          r->DelElem ();
          break ;
        case 101 :
          r->Print ();
          break ;
        case 100 :
          r->Store ();
          break ;
        }
      }
      break ;
    case WM_SIZE :
      r->DoSetScrolls();
      // No break
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal;
  }

extern HWND hwndFrame;
extern HINSTANCE MyInstance;
static char riClassName[] = "RIWND";

void riShow::DoSetScrolls()
  {
  RECT rc;
  GetClientRect (hWnd,&rc);
  PaintContext pc(hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (0,0);
  int gh = pc.YLOGtoPHYS(WndExtY);
  int gw = pc.XLOGtoPHYS(WndExtX);
  int AnzYScrolls = (gh - rc.bottom) / sdy ;
  int AnzXScrolls = (gw - rc.right) / sdx;
  if (AnzYScrolls > 0) {
    int yo = GetScrollPos (hWnd,SB_VERT);
    SetScrollRange (hWnd,SB_VERT,0,AnzYScrolls,FALSE);
    int yn = GetScrollPos (hWnd,SB_VERT);
    ShowScrollBar (hWnd,SB_VERT,TRUE);
    yv = - sdy * yn;
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
    xv = - xn * sdx ;
    }
  else {
    SetScrollRange (hWnd,SB_HORZ,0,0,FALSE);
    SetScrollPos (hWnd,SB_HORZ,0,FALSE);
    xv = 0;
    ShowScrollBar (hWnd,SB_HORZ,FALSE);
    }
  }

void riShow::Register ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wc;
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = riWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = MyInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = riClassName;

    RegisterClass (&wc);
    Registered = TRUE;
    }
  }

void riShow::Create (HWND hW)
  {
  if (hW == 0) {
    Register ();

    HMENU hmenu = LoadMenu (MyInstance,"RIMENU");
    int x = 100 ,y = 100,w = 400 ,h = 300 ;
    hWnd = CreateWindow(riClassName, FileName, 
                            WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_HSCROLL | WS_VSCROLL | WS_SYSMENU,
                            x,y,w,h,
                            hwndFrame, hmenu,
                            MyInstance, NULL
                      );
    }
  else {
    hWnd = hW ;
    SetWindowLong (hWnd,GWL_WNDPROC,LONG(riWndProc));
    }
  SetWindowLong (hWnd,GWL_RILIST,LONG(this));
  DoSetScrolls();
  td = new Table_Drop (hWnd,hWnd);

  Load ();
  }

riShow FAR *FirstRIShow;
riShow::riShow (LPSTR name)
  {
  FileName = LPSTR (GetGlobMem (lstrlen(name)+1));
  lstrcpy (FileName,name);
  Next = FirstRIShow ;
  FirstRIShow = this;
  }

riShow::~riShow ()
  {
  FreeGlobMem (FileName);
  td->RemoveFromList();
  for ( ; elem != NULL ; )
    delete elem ;

  riShow FAR *prev = NULL;
  for (riShow FAR *h = FirstRIShow; h != NULL ; h = h->Next) {
    if (h == this) {
      if (prev != NULL) prev->Next = h->Next ;
      else              FirstRIShow = h->Next ;
      break ;
      }
    prev = h ;
    }
  }

void riShow::Show ()
  {
  ShowWindow (hWnd,SW_SHOW);
  }

void riShow::Hide ()
  {
  ShowWindow (hWnd,SW_HIDE);
  }

void riShow::OnHScroll(WPARAM wP,LPARAM lP)
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
    xv = - nx * sdx ;
    InvalidateRect (hWnd,NULL,TRUE);
    }
  }

void riShow::InitializeVOrg ()
  {
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next)
    h->InitializeVOrg();
  }

void riShow::OnVScroll(WPARAM wP,LPARAM lP)
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
    yv = - ny * sdy ;
    InvalidateRect (hWnd,NULL,TRUE);
    }
  }

void riShow::PaintGrid(PaintContext *pc)
  {
  int AnzX = WndExtX / gdx ;
  int AnzY = WndExtY / gdy ;
  for (int i = 0 , x = 0 ; i < AnzX ; i++) {
    int y = 0 ;
    for (int i = 0 ; i < AnzY ; i++) {
      SetPixel (pc->hDC,x,y,RGB(0x80,0x80,0x80));
      y += gdy ;
      }
    x += gdx ;
    }
  }

void riShow::Paint(PaintContext *pc)
  {
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next)
    h->Paint (pc,h == ActiveElem);
  }

void riShow::NewTable (LPSTR TableName)
  {
  // Untersuchen, ob diese noch nicht dargestellt wurden ...
  BOOL found = FALSE ;
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next) {
    if (h->ElemType() == ELEMTYPE_TABLE) {
      riTable FAR *t = (riTable FAR *) h;
      if (lstrcmp (t->td->GetName(),TableName) == 0) {
        MessageBox (hWnd,"Tabelle bereits vorhanden","Fehler",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
        found = TRUE ;
        }
      }
    }
  if (!found) {
    POINT pt;
    DWORD p = GetMessagePos ();
    pt.x = LOWORD(p); pt.y = HIWORD(p);
    ScreenToClient (hWnd,&pt);
    riTable FAR *h = new riTable (TableName,this,pt.x,pt.y);
    CheckRI ();
    ChangeDone = TRUE ;
    }
  }

void riShow::NewTable (LPSTR TableName,int x,int y,int w,int h)
  {
  riTable FAR *n = new riTable (TableName,this,x,y,w,h);
  }

void Table_Drop::DoDrop (LPVOID dropData, WORD Type)
  {
  LPSTR TableName = LPSTR (dropData);
  LPRISHOW r = LPRISHOW (GetWindowLong (DropWnd,GWL_RILIST));
  r->NewTable (TableName);
  }

void riShow::ToLog (int FAR *x,int FAR *y)
  {
  PaintContext pc (hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (xv,yv);
  POINT pt;
  pt.x = *x ;  pt.y = *y ;
  DPtoLP (pc.hDC,&pt,1);
  *x = pt.x ; *y = pt.y ;
  }

#ifdef WIN32
void riShow::ToPhys (long FAR *x,long FAR *y)
#else
void riShow::ToPhys (int FAR *x,int FAR *y)
#endif
  {
  PaintContext pc (hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (xv,yv);
  POINT pt;
  pt.x = *x ;  pt.y = *y ;
  LPtoDP (pc.hDC,&pt,1);
  *x = pt.x ;  *y = pt.y ;
  }


int riShow::SnapW (int x,int fact)
  {
  int gx = gdx * fact;
  int xn = x / gx ;
  if (xn * gx < x) return (xn + 1) * gx ;
  else             return xn * gx ;
  }

int riShow::SnapH (int y,int fact)
  {
  int gy = gdy * fact;
  int yn = y / gy ;
  if (yn * gy < y) return (yn + 1) * gy ;
  else             return yn * gy ;
  }

void riShow::Snap (LPPOINT pt)
  {
  pt->x = ((pt->x + gdx / 2) / gdx) * gdx ;
  pt->y = ((pt->y + gdy / 2) / gdy) * gdy ;
  }

void riShow::OnLButtonDown (LPARAM lP)
  {
  int x = LOWORD(lP);
  int y = HIWORD(lP);
  ToLog (&x,&y);
  BOOL found = FALSE ;
  for ( riElem FAR *h = elem ; h != NULL ; h = h->Next) {
    if (h->HitTest (x,y)) {
      found = TRUE ;
      if (ActiveElem != h) {
        if (ActiveElem != NULL) ActiveElem->Invalidate (TRUE);
        }
      ActiveElem = h ;
      ActiveElem->Invalidate (TRUE);
      }
    }
  if ((!found) && (ActiveElem != NULL)) {
    ActiveElem->Invalidate (TRUE);
    ActiveElem = NULL;
    }
  }

void riShow::OnLButtonUp (LPARAM lP)
  {
  int x = LOWORD(lP);
  int y = HIWORD(lP);
  ToLog (&x,&y);
  if (ActiveElem != NULL) ActiveElem->OnLButtonUp (x,y);
  }

void riShow::OnMouseMove (LPARAM lP)
  {
  int x = LOWORD(lP);
  int y = HIWORD(lP);
  ToLog (&x,&y);
  if (ActiveElem != NULL) ActiveElem->OnMouseMove (x,y);
  }

BOOL riShow::LineReferenced (LPVOID k)
  {
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next) {
    if (h->ElemType() == ELEMTYPE_LINE) {
      riLine FAR *l = (riLine FAR *) h;
      if (l->fk == k) return TRUE ;
      }
    }
  return FALSE ;
  }

void riShow::CheckRI()
  {
  for (riElem FAR *x1 = elem ; x1 != NULL ; x1 = x1->Next) {
    if (x1->ElemType() == ELEMTYPE_TABLE) {
      riTable FAR *f1 = (riTable FAR *) x1;
      for (riElem FAR *x2 = elem ; x2 != NULL ; x2 = x2->Next) {
        if (x2->ElemType() == ELEMTYPE_TABLE) {
          riTable FAR *f2 = (riTable FAR *) x2;
          // Ueberpruefen, ob von f1 nach f2 eine Linie gemalt werden muss
          f1->CheckRI(f2);
          }
        }
      }
    }
  }

void riShow::DelLineDefs()
  {
  for (riElem FAR *x = elem ; x != NULL ; ) {
    riElem FAR *n = x->Next;
    if (x->ElemType() == ELEMTYPE_LINE) {
      x->Invalidate (TRUE);
      delete x ;
      }
    x = n;
    }
  }

void riShow::FreeTableDefs (LPSTR Name)
  {
  for (riElem FAR *x = elem ; x != NULL ; x = x->Next) {
    if (x->ElemType() == ELEMTYPE_TABLE) {
      riTable FAR *t = (riTable FAR *) x;
      if (lstrcmp (t->TableName,Name) == 0) {
        t->FreeTableDef ();
        }
      }
    }
  }

void PushToDoneTables(LPRITABLE t,LPRITABLE FAR *alreadydone,int FAR &AnzDone)
  {
  alreadydone[AnzDone++] = t;
  }

BOOL IsAlreadyDone(LPRITABLE t,LPRITABLE FAR *alreadydone,int AnzDone)
  {
  for (int i = 0 ; i < AnzDone ; i++) {
    if (alreadydone[i] == t) return TRUE ;
    }
  return FALSE ;
  }

void riShow::UpdateTableDef (LPSTR Name)
  {
  BOOL somethingdone = FALSE,first = TRUE ;
  LPRITABLE alreadydone[30];
  int AnzDone = 0;
  for ( ; ((first) || (somethingdone)) ; ) {
    first = somethingdone = FALSE ;
    for (riElem FAR *x = elem ; x != NULL ; x = x->Next) {
      if (x->ElemType() == ELEMTYPE_TABLE) {
        riTable FAR *t = (riTable FAR *) x;
        if ((!IsAlreadyDone(t,alreadydone,AnzDone)) &&
            (lstrcmp (t->TableName,Name) == 0)) {
          int x0 = (t->p0.x + t->p1.x) / 2 ;
          int y0 = (t->p0.y + t->p1.y) / 2 ;
          int w = t->p1.x - t->p0.x ;
          int h = t->p1.y - t->p0.y ;
          t->InvalidateFull ();
          for ( ; t->GetAnzLines() > 0 ; )
            delete t->lines[0] ;
          delete t;
          t = new riTable (Name,this,x0,y0,w,h);
          PushToDoneTables (t,alreadydone,AnzDone);
          somethingdone = TRUE ;
          break ;
          }
        }
      }
    }
  CheckRI();
  }

void riShow::OnDblClk ()
  {
  if (ActiveElem != NULL) ActiveElem->OnDblClk ();
  }

void riShow::DelElem ()
  {
  if ((ActiveElem != NULL) && (ActiveElem->ElemType() == ELEMTYPE_TABLE)) {
    riTable FAR *t = (riTable FAR *) ActiveElem;
    t->InvalidateFull ();
    for ( ; t->GetAnzLines() > 0 ; )
      delete t->lines[0] ;
    delete t;
    ActiveElem = NULL;
    ChangeDone = TRUE;
    }
  }

void riShow::Print ()
  {
  Printer *Pr = GetPrinter (TRUE);
  int xvold = xv ;
  int yvold = yv ;
  xv = yv = 0 ;
  Pr->PrinterDC(TRUE);          // Jetzt wirds ernst
  Pr->StartPrint ("RESTOOL");
  {
  PaintContext pc (Pr);
  pc.LogicalTwips (0,0);
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next) {
    h->Paint (&pc,FALSE,TRUE);
    }
  }
  Pr->NewFrame ();
  Pr->EndPrint();
  Pr->ReleaseDC();
  FreePrinter(Pr);
  xv = xvold ;
  yv = yvold ;
  }

LONG riShow::OnClose ()
  {
  if (ChangeDone) {
    int Answer = MessageBox (hWnd,"Sollen die geänderten Daten gespeichert werden ?","Schließen",MB_ICONQUESTION | MB_YESNOCANCEL);
    if (Answer == IDCANCEL) return 0L;
    if (Answer == IDYES)    Store ();
    }
  DestroyWindow (hWnd);
  return 0L;
  }

int riShow::GetTableCount()
  {
  int res = 0;
  for (riElem FAR *h = elem ; h != NULL ; h = h->Next) {
    if (h->ElemType() == ELEMTYPE_TABLE) res ++ ;
    }
  return res;
  }

void riShow::Store ()
  {
  OFSTRUCT Of;
  HFILE fi = OpenFile (FileName,&Of,OF_CREATE);
  if (fi > 0) {
    for (riElem FAR *h = elem ; (h != NULL) ; h = h->Next) {
      if (h->ElemType() == ELEMTYPE_TABLE) {
        riTable FAR *t = (riTable FAR *) h;
        char outstring [128];
        wsprintf (outstring,"%s (%d,%d,%d,%d)\r\n",t->td->GetName(),
                        (t->p0.x+t->p1.x) / 2,
                        (t->p0.y+t->p1.y) / 2,
                        (t->p1.x-t->p0.x),
                        (t->p1.y-t->p0.y)
                 );
        _lwrite (fi,outstring,lstrlen(outstring));
        }
      }
    _lwrite (fi,"end\r\n",5);
    _lclose (fi);
    ChangeDone = FALSE ;
    }
  }

/*-----< Implementierung der Klasse riElem >-------*/
riElem::riElem (riShow FAR *p)
  {
  Parent = p;
  if (p->elem == NULL) {
    p->elem = this ;
    }
  else {
    for (riElem FAR *h = p->elem ; h != NULL ; h = h->Next) {
      if (h->Next == NULL) {
        h->Next = this ;
        break ;
        }
      }
    }
  }

riElem::~riElem ()
  {
  riElem FAR *prev = NULL;
  for (riElem FAR *h = Parent->elem ; h != NULL ; h = h->Next) {
    if (h == this) {
      if (prev != NULL) prev->Next = h->Next ;
      else              Parent->elem = h->Next;
      break ;
      }
    prev = h ;
    }
  if (Parent->ActiveElem == this) Parent->ActiveElem = NULL;
  }

void riElem::Paint (PaintContext *pc,BOOL IsActive,BOOL forPrinter)
  {
  }

void riElem::InitializeVOrg()
  {
  }

void riElem::Invalidate (BOOL doErase)
  {
  }

BOOL riElem::HitTest (int x,int y)
  {
  return FALSE ;
  }

void riElem::OnLButtonUp (int x,int y)
  {
  }

void riElem::OnMouseMove (int x,int y)
  {
  }

/*-----< Implementierung der Klasse riLine >-------*/
inline void Sort (int FAR &a,int FAR &b)
  {
  if (a > b) {
    int dummy = b;
    b = a;
    a = dummy ;
    }
  }

inline void Sort (long FAR &a,long FAR &b)
  {
  if (a > b) {
    int dummy = b;
    b = a;
    a = dummy ;
    }
  }

void riLine::Paint (PaintContext *pc,BOOL Selected,BOOL forPrinter)
  {
  if (pt != NULL) {
    HPEN hOldPen = (HPEN)SelectObject (pc->hDC,CreatePen (PS_SOLID,10,RGB(0,0,0)));
    Polyline (pc->hDC,pt,AnzPts());
    DeleteObject (SelectObject (pc->hDC,hOldPen));
    HBRUSH hOldBrush = (HBRUSH)SelectObject (pc->hDC,GetStockObject (BLACK_BRUSH));
    // Punkt am Ursprung
    POINT v;
    Table1->GetOutVect (pstart.Side,&v);
    int x0,y0,x1,y1;
    if (v.y == 0) {
      // Horizontale Startline
      x0 = pt[0].x ;
      x1 = pt[0].x + v.x * mdx ;
      Sort (x0,x1);
      y0 = pt[0].y - mdx / 2 ;
      y1 = pt[0].y + mdx / 2 ;
      }
    else {
      // Verikale Startline
      y0 = pt[0].y ;
      y1 = pt[0].y + v.y * mdy ;
      Sort (y0,y1);
      x0 = pt[0].x - mdx / 2 ;
      x1 = pt[0].x + mdx / 2 ;
      }
    Ellipse (pc->hDC,x0,y0,x1,y1);
    // Pfeil am Ende
    Table2->GetOutVect (pend.Side,&v);
    POINT pfeil[3];
    POINT pte = pt[AnzPts()-1];
    pfeil[0] = pte ;
    if (v.y == 0) {
      pfeil[1].x = pfeil[2].x = pte.x + v.x * 2 * mdx ;
      pfeil[1].y = pte.y - mdx / 2 ;
      pfeil[2].y = pte.y + mdx / 2 ;
      }
    else {
      pfeil[1].y = pfeil[2].y = pte.y + v.y * 2 * mdy ;
      pfeil[1].x = pte.x - mdx / 2 ;
      pfeil[2].x = pte.x + mdx / 2 ;
      }
    Polygon (pc->hDC,pfeil,3);
    SelectObject (pc->hDC,hOldBrush);
    }
  }

void riLine::Invalidate (BOOL doErase)
  {
  RECT r;
  PaintContext pc(Parent->hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (Parent->xv,Parent->yv);
  for (int i = 0 ; i < AnzPts()-1 ; i++) {
    r.left = pt[i].x , r.top = pt[i].y ;
    r.right = pt[i+1].x , r.bottom = pt[i+1].y ;
    Sort (r.left,r.right);
    Sort (r.top,r.bottom);
    if (i == AnzPts() - 2)
      InflateRect (&r,2 * mdx,2 * mdy);
    else if (i == 0)
      InflateRect (&r,mdx,mdy);
    LPtoDP (pc.hDC,LPPOINT(&r.left),2);
    InflateRect (&r,1,1);
    InvalidateRect (Parent->hWnd,&r,doErase);
    }
  }

inline int abs (int x)
  {
  return (x < 0) ? - x : x ;
  }

void riLine::SetLine (LPPOINT p1,LPPOINT p2)
  {
  if (pt != NULL) FreeGlobMem (pt);
  pt = LPPOINT (GetGlobMem (sizeof(POINT) * 2));
  pt[0] = *p1 ;
  pt[1] = *p2 ;
  }
void riLine::SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3)
  {
  if (pt != NULL) FreeGlobMem (pt);
  pt = LPPOINT (GetGlobMem (sizeof(POINT) * 3));
  pt[0] = *p1 ;
  pt[1] = *p2 ;
  pt[2] = *p3 ;
  }
void riLine::SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3,LPPOINT p4)
  {
  if (pt != NULL) FreeGlobMem (pt);
  pt = LPPOINT (GetGlobMem (sizeof(POINT) * 4));
  pt[0] = *p1 ;
  pt[1] = *p2 ;
  pt[2] = *p3 ;
  pt[3] = *p4 ;
  }
void riLine::SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3,LPPOINT p4,LPPOINT p5)
  {
  if (pt != NULL) FreeGlobMem (pt);
  pt = LPPOINT (GetGlobMem (sizeof(POINT) * 5));
  pt[0] = *p1 ;
  pt[1] = *p2 ;
  pt[2] = *p3 ;
  pt[3] = *p4 ;
  pt[4] = *p5 ;
  }
void riLine::BuildLine ()
  {
  POINT p1,p2,v1,v2;
  Table1->GetXY (&pstart,&p1);
  Table2->GetXY (&pend,&p2);
  Table1->GetOutVect(pstart.Side,&v1);
  Table1->GetOutVect(pend.Side,&v2);
  POINT pm1,pm2 ;
  if ((v1.x * v2.y - v1.y * v2.x) == 0) {
    // Die Linien sind parallel -> 2 Punkte oder 4 Punkte
    if (Table1 == Table2) {
      // Spezialfall : Referenz auf eigene Tabelle
      pm1.x = p1.x + v1.x * 3 * gdx ;  pm1.y = p1.y + v1.y * 3 * gdy ;
      pm2.x = p2.x + v2.x * 3 * gdx ;  pm2.y = p2.y + v2.y * 3 * gdy ;
      SetLine (&p1,&pm1,&pm2,&p2);
      }
    else {
      if ((p1.x == p2.x) || (p1.y == p2.y))
        SetLine (&p1,&p2);
      else {
        if (v1.y == 0) {
          // Horizontaler Anfang und Ende
          pm1.x = pm2.x = (p1.x + p2.x) / 2 ;
          pm1.y = p1.y ;
          pm2.y = p2.y ;
          SetLine (&p1,&pm1,&pm2,&p2);
          }
        else {
          // Vertikaler Anfang und Ende
          pm1.y = pm2.y = (p1.y + p2.y) / 2 ;
          pm1.x = p1.x ;
          pm2.x = p2.x ;
          SetLine (&p1,&pm1,&pm2,&p2);
          }
        }
      }
    }
  else {
    if (Table1 == Table2) {
      pm1.x = p1.x + v1.x * 3 * gdx ;  pm1.y = p1.y + v1.y * 3 * gdy ;
      pm2.x = p2.x + v2.x * 3 * gdx ;  pm2.y = p2.y + v2.y * 3 * gdy ;
      POINT pm3;
      if (v1.x == 0)
        pm3.x = pm2.x , pm3.y = pm1.y ;
      else
        pm3.y = pm2.y , pm3.x = pm1.x ;
      SetLine (&p1,&pm1,&pm3,&pm2,&p2);
      }
    else {
      // Die Dinger stehen normal darauf -> 3 Punkte
      if (v1.y == 0)
        // Horizontaler Anfang, vertikales Ende
        pm1.x = p2.x , pm1.y = p1.y ;
      else
        // Vertikaler Anfang, horizontales Ende
        pm1.x = p1.x , pm1.y = p2.y ;
      SetLine (&p1,&pm1,&p2);
      }
    }
  }

void riLine::FreeStartKnots ()
  {
  pstart.Side = pend.Side = -1;
  }

LONG riLine::SearchBestWay ()
  {
  StartEndPos ps,pe,psbest,pebest;
  LONG oabst = 0x7FFFFFFF ;
  for ( Table1->GetFirstPos (&ps,NULL,this) ; ; ) {
    LONG t1m = Table1->MidFault(&ps);
    POINT pts,pte,vs,ve;
    Table1->GetXY (&ps,&pts);
    Table1->GetOutVect (ps.Side,&vs);
    for ( Table2->GetFirstPos (&pe,&ps,this) ; ; ) {
      Table2->GetXY (&pe,&pte);
      Table2->GetOutVect (pe.Side,&ve);
      LONG otherfault = 0L;
      BOOL isNormal;
      if (ve.x * vs.y - ve.y * vs.x == 0) {
        // Sie stehen parallel zueinander -> Untersuchen, ob der Pfeil in
        // die richtige Richtung stehen wuerde
        if ((pte.x - pts.x) * ve.x + (pte.y - pts.y) * ve.y > 0)
          otherfault += LONG(50 * gdx) ;
        // Untersuchen, ob der Punkt in die richtige Richtung stehen wuerde
        if ((pte.x - pts.x) * vs.x + (pte.y - pts.y) * vs.y < 0)
          otherfault += LONG(50 * gdx) ;
        isNormal = FALSE ;
        }
      else
        isNormal = TRUE ;

      // Untersuchen, ob der Pfeil Platz hat
      if (ve.y == 0) {
        // Horizontale End - Linie
        int space = abs ((isNormal) ? pte.x - pts.x : ((pte.x - pts.x) / 2)) ;
        if (space < 2 * mdx)
          otherfault += LONG(10 * gdx) ;
        }
      else {
        // Verikale End - Linie
        int space = abs ((isNormal) ? pte.y - pts.y : ((pte.y - pts.y) / 2)) ;
        if (space < 2 * mdx)
          otherfault += LONG(10 * gdx) ;
        }
      // Untersuchen, ob der Punkt Platz hat
      if (vs.y == 0) {
        // Horizontale Start - Linie
        int space = abs ((isNormal) ? pte.x - pts.x : ((pte.x - pts.x) / 2)) ;
        if (space < 2 * mdx)
          otherfault += LONG(10 * gdx) ;
        }
      else {
        // Verikale Start - Linie
        int space = abs ((isNormal) ? pte.y - pts.y : ((pte.y - pts.y) / 2)) ;
        if (space < 2 * mdx)
          otherfault += LONG(10 * gdx) ;
        }
      LONG abst = LONG(abs(pts.x - pte.x)) + LONG(abs(pts.y - pte.y)) 
                 + t1m + LONG(Table2->MidFault(&pe)) + otherfault;
      if (abst < oabst) {
        oabst = abst ;
        psbest = ps ;
        pebest = pe ;
        }
      if (!Table2->GetNextPos (&pe,&ps,this)) break ;
      }
    if (!Table1->GetNextPos (&ps,NULL,this)) break ;
    }
  pstart = psbest;
  pend = pebest;
  return oabst;
  }

riLine::riLine (riTable FAR *t1,riTable FAR *t2,LPVOID k) : riElem (t1->Parent)
  {
  Table1 = t1 ;  Table2 = t2 ;
  fk = k ;
  Table1->PushLine (this);
  Table2->PushLine (this);
  }

riLine::~riLine ()
  {
  if (Table1 != NULL) Table1->RemoveLine (this);
  if (Table2 != NULL) Table2->RemoveLine (this);
  if (pt != NULL) FreeGlobMem (pt);
  }

/*-----< Implementierung der Klasse riTable >-------*/
riTable::riTable (LPSTR Name,riShow FAR *p,int x,int y,int w,int h) : riElem (p)
  {
  TableName = LPSTR (GetGlobMem (lstrlen(Name)+1));
  lstrcpy (TableName,Name);
  if (w < 0)
    Parent->ToLog (&x,&y);
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,Name,&found,&Version);
  td = GetTableAdmin()->GetTableDef (TableID,Version);
  if (w < 0) {
    field = new cField (OPAQUE,TableFormat,0,0,-1,-1,FALSE);
    field->SetWindow (Parent->hWnd);
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetFieldMode (FM_OUTLINEONLY);
    *field = Name;
    RECT r ;
    field->GetFieldRect (&r, 0);
    w = Parent->SnapW (minw = r.right * 6 / 5,2);
    h = Parent->SnapH (minh = r.bottom,2);
    field->SetVOrg (Parent->yv,Parent->xv,0);
    if (x < w / 2) x = w / 2 ;
    if (y < h) y = w / 2 ;
    p0.x = x - w / 2 ;
    p0.y = y - h ;
    Parent->Snap (&p0);
    p1.x = x + w / 2 ;
    p1.y = y + h ;
    Parent->Snap (&p1);
    field->SetWidth (p1.x - p0.x);
    }
  else {
    field = new cField (OPAQUE,TableFormat,0,0,w,-1,FALSE);
    field->SetWindow (Parent->hWnd);
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetFieldMode (FM_OUTLINEONLY);
    *field = Name;
    RECT r ;
    field->GetFieldRect (&r, 0);
    field->SetVOrg (Parent->yv,Parent->xv,0);
    p0.x = x - w / 2 ;
    p0.y = y - h / 2 ;
    p1.x = x + w / 2 ;
    p1.y = y + h / 2 ;
    }
  POINT pf;
  pf.x = p0.x ;
  pf.y = p0.y + (p1.y - p0.y - LineHeight()) / 2;
  *field = pf;
  Invalidate (TRUE);
  }

void riTable::FreeTableDef ()
  {
  if (td != NULL) {
    GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
    td = NULL;
    }
  }

riTable::~riTable ()
  {
  FreeTableDef ();
  for (int i = 0 ; i < GetAnzLines() ; i++) {
    if (lines[i]->Table1 == this) lines[i]->Table1 = NULL ;
    if (lines[i]->Table2 == this) lines[i]->Table2 = NULL ;
    }
  if (lines != NULL)
    FreeGlobMem (lines);
  if (TableName != NULL)
    FreeGlobMem (TableName);
  }

void riTable::InitializeVOrg()
  {
  field->SetVOrg (Parent->yv,Parent->xv,0);
  }

void riTable::Invalidate (BOOL doErase)
  {
  RECT r;
  r.left = p0.x - mdx, r.top = p0.y - mdy ;
  r.right = p1.x + mdx , r.bottom = p1.y + mdy ;
  Parent->ToPhys (&r.left,&r.top);
  Parent->ToPhys (&r.right,&r.bottom);
  InflateRect (&r,1,1);
  InvalidateRect (Parent->hWnd,&r,doErase);
  }

void riTable::InvalidateFull ()
  {
  Invalidate (TRUE);
  for (int i = 0 ; i < GetAnzLines() ; i++) {
    lines[i]->Invalidate(TRUE);
    }
  }

DWORD riTable::TableColor ()
  {
  return RGB(0,0,0);
  }

void riTable::Paint (PaintContext *pc,BOOL IsSelected,BOOL forPrinter)
  {
  HBRUSH hOldBrush = (HBRUSH)SelectObject (pc->hDC,GetStockObject (NULL_BRUSH));
  HPEN hOldPen = (HPEN)SelectObject (pc->hDC,CreatePen (PS_SOLID,30,TableColor()));
  Rectangle (pc->hDC,p0.x,p0.y,p1.x,p1.y);
  DeleteObject (SelectObject (pc->hDC,hOldPen));
  if (IsSelected) {
    Rectangle (pc->hDC,p0.x-mdx/2,p0.y-mdy/2,p0.x+mdx/2,p0.y+mdy/2);
    Rectangle (pc->hDC,p0.x-mdx/2,p1.y-mdy/2,p0.x+mdx/2,p1.y+mdy/2);
    Rectangle (pc->hDC,p1.x-mdx/2,p1.y-mdy/2,p1.x+mdx/2,p1.y+mdy/2);
    Rectangle (pc->hDC,p1.x-mdx/2,p0.y-mdy/2,p1.x+mdx/2,p0.y+mdy/2);
    }
  SelectObject (pc->hDC,hOldBrush);
  field->SetOutColor (TableColor());
  field->Paint (pc->hDC,0,forPrinter);
  }

BOOL riTable::HitTest (int x,int y)
  {
  BOOL res = FALSE ;
  if ((x >= p0.x) && (y >= p0.y) && 
      (x <= p1.x + 100) && (y <= p1.y + 100)) {
    res = TRUE ;
    xm0 = x ;
    ym0 = y ;
    if ((x >= p1.x - 100) && (x <= p1.x + 100)) {
      State = MSTATE_RIGHT ;
      SetCursor (LoadCursor (NULL,IDC_SIZEWE));
      }
    else if ((y >= p1.y - 100) && (y <= p1.y + 100)) {
      State = MSTATE_BOTTOM ;
      SetCursor (LoadCursor (NULL,IDC_SIZENS));
      }
    else {
      State = MSTATE_MOVE ;
      #ifdef WIN32
      SetCursor (LoadCursor (NULL,IDC_SIZEALL));
      #else
      SetCursor (LoadCursor (NULL,IDC_SIZE));
      #endif
      }
    }
  return res ;
  }

void riTable::SetFldPos ()
  {
  int h = LineHeight();
  POINT pf;
  pf.x = p0.x ;
  pf.y = p0.y + (p1.y - p0.y - h) / 2;
  *field = pf;
  }

void riTable::OnMouseMove (int x,int y)
  {
  int dx = x - xm0 ;
  int dy = y - ym0 ;
  POINT pn0 = p0,pn1 = p1;
  switch(State) {
    case MSTATE_MOVE :
      {
      if ((pn0.x + dx > 0) && (pn0.y + dy > 0)) {
        pn0.x += dx ;      pn0.y += dy ;
        pn1.x += dx ;      pn1.y += dy ;
        Parent->Snap (&pn0);
        Parent->Snap (&pn1);
        dx = pn0.x - p0.x;
        dy = pn0.y - p0.y;
        }
      }
      break ;
    case MSTATE_RIGHT :
      {
      POINT ph1 = p1 ;
      ph1.x += dx ;
      Parent->Snap(&ph1);
      dx = ph1.x - p1.x ;
      int nw = p1.x - p0.x + 2 * dx;
      if ((nw > minw) && ((p1.x + p0.x - nw) / 2 >= 0)) {
        pn0.x = p0.x - dx ;
        pn1.x = p1.x + dx ;
        dx = pn1.x - p1.x;
        dy = 0;
        }
      }
      break ;
    case MSTATE_BOTTOM :
      {
      POINT ph1 = p1 ;
      ph1.y += dy ;
      Parent->Snap(&ph1);
      dy = ph1.y - p1.y ;
      int nh = p1.y - p0.y + 2 * dy;
      if ((nh > minh) && (p1.y + p0.y - nh) / 2 >= 0) {
        pn0.y = p0.y - dy ;
        pn1.y = p1.y + dy ;
        dy = pn1.y - p1.y;
        dx = 0;
        }
      }
      break ;
    }
  if ((pn0.x != p0.x) || (pn0.y != p0.y) ||
      (pn1.x != p1.x) || (pn1.y != p1.y)) {
    Parent->ChangeDone = TRUE ;
    Invalidate (TRUE);
    p0 = pn0 ;  p1 = pn1 ;
    Invalidate (TRUE);

    field->SetWidth (p1.x - p0.x);
    SetFldPos ();
    xm0 += dx ;
    ym0 += dy ;
    for (int i = 0 ; i < GetAnzLines() ; i++)
      lines[i]->FreeStartKnots ();
    for (i = 0 ; i < GetAnzLines() ; i++) {
      lines[i]->Invalidate(TRUE);
      lines[i]->SearchBestWay();
      lines[i]->BuildLine();
      lines[i]->Invalidate(TRUE);
      }
    }
  }

int riTable::LineHeight()
  {
  LPFORMATMETRIC fm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,TableFormat);
  return fm->yHeight;
  }

void riTable::OnLButtonUp (int x,int y)
  {
  OnMouseMove (x,y);
  State = 0;
  }

BOOL riTable::GetFirstPos(LPSEP p)
  {
  p->Side = 0 ;
  p->RPos = 1;
  return (MaxRPos (0) >= 1) ;
  }

int riTable::MaxRPos (int Side)
  {
  switch (Side) {
    case 0 :
    case 2 :
      return ((p1.x - p0.x + gdx / 2) / gdx) - 1 ;
    case 1 :
    case 3 :
      return ((p1.y - p0.y + gdy / 2) / gdy) - 1 ;
    }
  return 0;
  }

BOOL riTable::GetNextPos(LPSEP p)
  {
  if (p->RPos < MaxRPos (p->Side)) p->RPos ++ ;
  else if (p->Side < 3) p->Side += 1 , p->RPos = 1 ;
  else return FALSE ;
  return TRUE ;
  }

BOOL riTable::GetFirstPos(LPSEP p,LPSEP o,riLine FAR *l)
  {
  if (GetFirstPos(p)) {
    for ( ; ; ) {
      if (IsPosFree (p,o,l)) return TRUE ;
      if (!GetNextPos (p)) return FALSE ;
      }
    }
  return FALSE ;
  }

BOOL riTable::GetNextPos(LPSEP p,LPSEP o,riLine FAR *l)
  {
  if (GetNextPos(p)) {
    for ( ; ; ) {
      if (IsPosFree (p,o,l)) return TRUE ;
      if (!GetNextPos (p)) return FALSE ;
      }
    }
  return FALSE ;
  }

BOOL riTable::IsPosFree (LPSEP p,LPSEP e,riLine FAR *l)
  {
  int Anz = GetAnzLines() ;
  if ((l->Table1 == l->Table2) && (e != NULL) && (*p == *e)) return FALSE ;
  for (int i = 0 ; i < Anz ; i++) {
    if ((lines[i]->pstart == *p) && (lines[i]->Table1 == this)) {
      return (lines[i] == l);
      }
    if ((lines[i]->pend == *p) && (lines[i]->Table2 == this)) {
      return (lines[i] == l);
      }
    }
  return TRUE ;
  }

void riTable::PushLine (riLine FAR *l)
  {
  int Anz = GetAnzLines();
  LPRILINE FAR *n = (LPRILINE FAR *) (GetGlobMem ((Anz + 1) * sizeof(*lines))) ;
  if (lines != NULL) {
    lmemcpy (n,lines,Anz * sizeof(*lines));
    FreeGlobMem (lines);
    }
  lines = n ;
  lines[Anz] = l;
  }

void riTable::RemoveLine (riLine FAR *l)
  {
  int Anz = GetAnzLines();
  LPRILINE FAR *n;
  if (Anz >= 1) {
    n = (LPRILINE FAR *) (GetGlobMem ((Anz - 1) * sizeof(*lines))) ;
    int j = 0;
    for (int i = 0 ; i < Anz ; i++) {
      if (lines[i] != l) n[j++] = lines[i];
      }
    }
  else
    n = NULL;
  if (lines != NULL)
    FreeGlobMem (lines);
  lines = n;
  }

void riTable::GetStartPoint (int Side,LPPOINT pt)
  {
  switch (Side) {
    case 0 :
      *pt = p0 ;
      break ;
    case 1 :
      pt->x = p1.x ;
      pt->y = p0.y ;
      break ;
    case 2 :
      *pt = p1 ;
      break ;
    case 3 :
      pt->x = p0.x ;
      pt->y = p1.y ;
      break ;
    }
  }

void riTable::GetSideVect (int Side,LPPOINT pt)
  {
  switch (Side) {
    case 0 :
      pt->x = gdx ;
      pt->y = 0 ;
      break ;
    case 1 :
      pt->x = 0 ;
      pt->y = gdy ;
      break ;
    case 2 :
      pt->x = -gdx ;
      pt->y = 0 ;
      break ;
    case 3 :
      pt->x = 0 ;
      pt->y = -gdy ;
      break ;
    }
  }

void riTable::GetOutVect (int Side,LPPOINT pt)
  {
  switch (Side) {
    case 0 :
      pt->x = 0 ;
      pt->y = -1 ;
      break ;
    case 1 :
      pt->x = 1 ;
      pt->y = 0 ;
      break ;
    case 2 :
      pt->x = 0 ;
      pt->y = 1 ;
      break ;
    case 3 :
      pt->x = -1 ;
      pt->y = 0 ;
      break ;
    }
  }

int riTable::MidFault (LPSEP p)
  {
  return abs (2 * p->RPos - (MaxRPos (p->Side) + 1)) * gdx / 5 ;
  }

void riTable::GetXY (LPSEP p,LPPOINT pt)
  {
  POINT v;
  GetStartPoint (p->Side,pt);
  GetSideVect (p->Side,&v);
  pt->x += v.x * p->RPos ;
  pt->y += v.y * p->RPos ;
  }

void riTable::CheckRI(riTable FAR *x)
  {
  for (int i = 0 ; i < td->GetAnzRIDefs () ; i++) {
    LPCLRIDEF k = td->GetRIDef(i);
    if ((lstrcmp (k->name,x->td->GetName()) == 0) &&
        (!Parent->LineReferenced (k))) {
      // Na dann mal los
      riLine FAR *l = new riLine (this,x,k);
      l->SearchBestWay ();
      l->BuildLine ();
      l->Invalidate (TRUE);
      }
    }
  }

extern void WorkOnTable (LPSTR TableName);
void riTable::OnDblClk ()
  {
  WorkOnTable (TableName);
  }

/*-----< Implementierung der Klasse jShow >------*/
void jShow::NewTable (LPSTR TableName)
  {
  // Untersuchen, ob diese noch nicht dargestellt wurden ...
  POINT pt;
  DWORD p = GetMessagePos ();
  pt.x = LOWORD(p); pt.y = HIWORD(p);
  ScreenToClient (hWnd,&pt);
  jTable FAR *h = new jTable (GetTableCount(),TableName,this,pt.x,pt.y);
  h->UpdateName ();
  IntFldList FAR *lst = (IntFldList FAR *) extra ;
  lst->AddTable (h->GetTableNum(),h->TableName);
  ChangeDone = TRUE ;
  }

void jShow::NewTable (LPSTR TableName,int x,int y,int w,int h)
  {
  jTable FAR *n = new jTable (GetTableCount(),TableName,this,x,y,w,h);
  n->UpdateName ();
  }

LONG jShow::OnClose ()
  {
  return 0L;
  }

void jShow::DelElem ()
  {
  if ((ActiveElem != NULL) && (ActiveElem->ElemType() == ELEMTYPE_TABLE)) {
    jTable FAR *t = (jTable FAR *) ActiveElem;
    t->InvalidateFull ();
    int TableToDel = t->GetTableNum();
    for ( ; t->GetAnzLines() > 0 ; )
      delete t->lines[0] ;
    delete t;
    ActiveElem = NULL;
    for (riElem FAR *h = elem ; h != NULL ; h = h->Next) {
      if (h->ElemType() == ELEMTYPE_TABLE) {
        t = (jTable FAR *) h;
        if (t->GetTableNum() > TableToDel) {
          t->TableNum -- ;
          t->UpdateName ();
          if (t->TableNum == 0) t->Invalidate (TRUE);
          }
        }
      }
    IntFldList FAR *lst = (IntFldList FAR *) extra ;
    lst->DelTable (TableToDel);
    ChangeDone = TRUE ;
    }
  }

/*-----< Implementierung der Klasse jTable >------*/
DWORD jTable::TableColor ()
  {
  if (GetTableNum() == 0)
    return RGB(0,0,0);
  else
    return RGB(0x80,0x80,0x80);
  }

void jTable::SetFldPos ()
  {
  int h = LineHeight();
  POINT pf;
  pf.x = p0.x ;
  pf.y = p0.y + (p1.y - p0.y - 2 * h) / 2;
  *field = pf;
  }

void jTable::UpdateName ()
  {
  char rname[128];
  wsprintf (rname,"%d\r%s",TableNum,TableName);
  field->SetWidth (-1);
  *field = rname;
  RECT r ;
  field->GetFieldRect (&r, 0);
  int w = Parent->SnapW (minw = ((r.right - r.left) * 6 / 5),2);
  int h = Parent->SnapH (minh = (r.bottom - r.top),2);
  int x = (p0.x + p1.x) / 2;
  int y = (p0.y + p1.y) / 2;
  if (x < w / 2) x = w / 2 ;
  if (y < h) y = w / 2 ;
  if ((minw > p1.x - p0.x) || (minh > p1.y - p0.y)) {
    p0.x = x - w / 2 ;
    p0.y = y - h ;
    Parent->Snap (&p0);
    p1.x = x + w / 2 ;
    p1.y = y + h ;
    Parent->Snap (&p1);
    field->SetWidth (p1.x - p0.x);
    }
  else
    field->SetWidth (p1.x - p0.x);
  SetFldPos ();
  Invalidate (TRUE);
  }

void jTable::CheckRI(riTable FAR *x)
  {
  jTable FAR *jx = (jTable FAR *) x ;
  if (jx == this) return ;
  IntFldList FAR *lst = (IntFldList FAR *) ((jShow FAR *) Parent)->extra ;
  for (FldLine FAR *h = lst->jlst->FirstLine ; h != NULL ; h = h->Next) {
    if ((!Parent->LineReferenced (h)) &&
        (lst->jlst->GetDestTableNr (h) == jx->GetTableNum()) &&
        (lst->jlst->GetSourceTableNr (h) == GetTableNum())) { 
      // Na dann mal los
      riLine FAR *l = new riLine (this,x,h);
      l->SearchBestWay ();
      l->BuildLine ();
      l->Invalidate (TRUE);
      }
    }
  }

LPSTR jShow::GetTableName (int nr)
  {
  for (riElem FAR *x = elem ; x != NULL ; x = x->Next) {
    if (x->ElemType() == ELEMTYPE_TABLE) {
      jTable FAR *f = (jTable FAR *) x;
      if (int(f->GetTableNum()) == nr) {
        return f->TableName;
        }
      }
    }
  return NULL;
  }


/*------< Aufruf der RI - Tabelle >--------*/
void CreateRIView (LPSTR Name)
  {
  LPRISHOW r = new riShow (Name);
  r->Create (0);
  r->Show ();
  }

void FreeRITableDefs (LPSTR Name)
  {
  for (LPRISHOW h = FirstRIShow ; h != NULL ; h = h->Next)
    h->FreeTableDefs (Name);
  }

void UpdateRITableDef (LPSTR Name)
  {
  for (LPRISHOW h = FirstRIShow ; h != NULL ; h = h->Next)
    h->UpdateTableDef (Name);
  }
