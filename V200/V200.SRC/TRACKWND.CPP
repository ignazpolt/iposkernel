///////////////////////////////////////////////////////////////////
//    Untersuchen der Mouseposition und dementsprechend
//    Versenden WM_HSCROLL, WM_VSCROLL zum zu untersuchenden
//    Fenster
//////////////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/rev/trackwnd.cpv   1.22   19 Apr 2000 15:56:12   Martin  $
// $Log:   P:/marille/clinicum/rev/trackwnd.cpv  $
// 
//    Rev 1.22   19 Apr 2000 15:56:12   Martin
// Kontext-Menue: wP ist jetzt nicht mehr procptr sondern index desselben
// (Ueberlauf !!!!)
// 
//    Rev 1.21   06 Apr 2000 15:15:24   Wolfgang
// 1.) NULL-Strings in PopUpMenu werden ausgefiltert.
// 2.) Strings mit _ vorne erzeugen Separatoren.
// 3.) Header und Log eingefuegt.
//
//////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#define MODULENUM   191
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"

#include "scripthd.hpp"
#include "mdichild.hpp"
#include "cfield.hpp"
#include "dllchild.hpp"
#include "frmobj.hpp"

#include "tbcbd.hpp"

#define TRACKTIMERID    0xA7F
#define DELTA_T         100

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

BOOL externCapture;
static void SetupTracking (HWND hWnd,LPTRACKWNDDATA lptw)
  {
  if (!lptw->IsCaptured) {
    // Capture der Mouse
    SetCapture (hWnd);
    lptw->IsCaptured = TRUE ;
    }
  if (lptw->IsCaptured) {
    if ((!lptw->IsTimerSet) && (!IsInWnd (hWnd))) {
      // Aufsetzen eines Timers
      SetTimer (hWnd,TRACKTIMERID,DELTA_T,NULL);
      lptw->IsTimerSet = TRUE ;
      // Scrollen
      if (!externCapture) Scroll (hWnd);
      }
    else if ((lptw->IsTimerSet) && (IsInWnd (hWnd))) {
      // Loeschen des Timers
      KillTimer (hWnd,TRACKTIMERID);
      lptw->IsTimerSet = FALSE ;
      externCapture = FALSE;
      }
    }
  }

static void EndTracking (HWND hWnd,LPTRACKWNDDATA lptw)
  {
  if (lptw->IsCaptured) {
    if (lptw->IsTimerSet) {
      // Loeschen des Timers
      KillTimer (hWnd,TRACKTIMERID);
      lptw->IsTimerSet = FALSE ;
      }
    // Capture ausschalten
    ReleaseCapture ();
    lptw->IsCaptured = FALSE ;

    externCapture = FALSE;
    }
  }

#pragma pack(1)
struct FAR WaitOnMouseClk_param {
  WORD  parSize;
  DWORD ptres;
  DWORD procToCall;
  DWORD procOnLButtonDown;
  DWORD done;
  DWORD cursor;
  DWORD procOnDblClk;

  BOOL CheckDone ()
    {
    return (parSize >= sizeof(*this) - 2 * sizeof(DWORD)) ;
    }
  BOOL CheckCursor ()
    {
    return (parSize >= sizeof(*this) - sizeof(DWORD)) ;
    }
  BOOL CheckDblClk ()
    {
    return (parSize >= sizeof(*this)) ;
    }
  };
#pragma pack()

struct MouseFunc {
  HWND WaitWnd;
  UINT msg;
  mdiChild FAR *WaitChild;
  WaitOnMouseClk_param FAR *wparam;
  MouseFunc FAR *Next;
  };

static MouseFunc FAR *mfList;
MouseFunc FAR *IsThereWaitProc (HWND hWnd,UINT msg)
  {
  for (MouseFunc FAR *res = mfList ; res != NULL ; res = res->Next) {
    if (((res->msg == msg) || (msg == 0)) && (res->WaitWnd == hWnd))
      break ;
    }
  return res ;
  }

void RemoveFromWaitList (MouseFunc FAR *mf)
  {
  MouseFunc FAR *prev = NULL ;
  for (MouseFunc FAR *h = mfList ; h != NULL ; h = h->Next) {
    if (h == mf) {
      if (prev != NULL) prev->Next = h->Next ;
      else              mfList = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    else
      prev = h ;
    }
  }

void InsertIntoWaitList (HWND _WaitWnd,UINT _msg,mdiChild FAR *_WaitChild,WaitOnMouseClk_param FAR *_wparam)
  {
  MouseFunc FAR *mf = (MouseFunc FAR *) GetGlobMem (sizeof (*mf)) ;
  mf->Next = mfList ;
  mfList = mf ;
  mf->WaitWnd   = _WaitWnd ;
  mf->msg       = _msg ;
  mf->WaitChild = _WaitChild ;
  mf->wparam    = _wparam ;
  }

short lastCursor = 0;
BOOL InWaitProc;
BOOL DoWaitProc (MouseFunc FAR *mf,HWND hWnd,int x,int y,BOOL writelButton,BOOL lButtonIsDown,BOOL doRemove,BOOL callDblClk = FALSE)
  {
  BOOL res;
  if ((mf->WaitChild != NULL) && ((!callDblClk) || (mf->wparam->CheckDblClk()))) {
    if (!InWaitProc) {
      {
      POINT pt;
      pt.x = x ;
      pt.y = y ;
      PaintContext pc;
      GetDocumentContext (&pc,mf->WaitChild);
      DPtoLP (pc.hDC,&pt,1);
      fpt fp;
      fp.x = mf->WaitChild->LogToWorld(pt.x) ;
      fp.y = mf->WaitChild->LogToWorld(pt.y) ;
      mf->WaitChild->WritelData (mf->wparam->ptres,&fp,sizeof(fp),LPSTR(mf->wparam) - sizeof(WORD));
      if (writelButton)
        mf->WaitChild->WritelData (mf->wparam->procOnLButtonDown,&lButtonIsDown,sizeof(lButtonIsDown),LPSTR(mf->wparam) - sizeof(WORD));
      }
      InWaitProc = TRUE ;
      if (callDblClk) {
        mf->WaitChild->ExCuteProc (mf->wparam->procOnDblClk,EM_LOAD | EM_CHANGETOTRUE);
        mf->WaitChild->ExCuteProc (mf->wparam->procOnDblClk,EM_RESET | EM_CLEAR);
        }
      else {
        mf->WaitChild->ExCuteProc (mf->wparam->procToCall,EM_LOAD | EM_CHANGETOTRUE);
        mf->WaitChild->ExCuteProc (mf->wparam->procToCall,EM_RESET | EM_CLEAR);
        }
      InWaitProc = FALSE ;

      if (mf->wparam->CheckCursor()) {
        short FAR *lpicursor = (short FAR *) mf->WaitChild->ReadlData (mf->wparam->cursor);
        if (lpicursor != NULL)
          lastCursor = *lpicursor ;
        else
          lastCursor = 0;
        }
      else
        lastCursor = 0;

      if (doRemove)
        RemoveFromWaitList (mf);
      }
    res = TRUE ;
    }
  else
    res = FALSE ;

  return res;
  }

BOOL DoLButtonDownProc (MouseFunc FAR *mf,HWND hWnd,int x,int y)
  {
  BOOL res;
  if (mf->wparam->CheckDone()) {
    if (!InWaitProc) {
      {  
      POINT pt;
      pt.x = x ;
      pt.y = y ;
      PaintContext pc;
      GetDocumentContext (&pc,mf->WaitChild);
      DPtoLP (pc.hDC,&pt,1);
      fpt fp;
      fp.x = mf->WaitChild->LogToWorld(pt.x) ;
      fp.y = mf->WaitChild->LogToWorld(pt.y) ;
      mf->WaitChild->WritelData (mf->wparam->ptres,&fp,sizeof(fp),LPSTR(mf->wparam) - sizeof(WORD));
      }
      InWaitProc = TRUE ;
      mf->WaitChild->ExCuteProc (mf->wparam->procOnLButtonDown,EM_LOAD | EM_CHANGETOTRUE);
      mf->WaitChild->ExCuteProc (mf->wparam->procOnLButtonDown,EM_RESET | EM_CLEAR);
      InWaitProc = FALSE ;

      DBBOOL FAR *lpDone = (DBBOOL FAR *) mf->WaitChild->ReadlData (mf->wparam->done);
      if (lpDone != NULL) res = *lpDone;
      else                res = TRUE ;
      }
    else
      res = TRUE ;
    }
  else
    res = TRUE ;

  return res;
  }

BOOL WaitOnMouseClk (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MouseFunc FAR *mf = IsThereWaitProc (c->OutWnd(),WM_LBUTTONUP);
    if (mf == NULL)
      InsertIntoWaitList (c->OutWnd(),WM_LBUTTONUP,c,(WaitOnMouseClk_param FAR *) param);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    MouseFunc FAR *mf = IsThereWaitProc (c->OutWnd(),WM_LBUTTONUP);
    if (mf != NULL)
      RemoveFromWaitList (mf);
    }
  return FALSE ;
  }

static BOOL lDownDone ;
struct CursorList {
  short Id;
  HCURSOR hCur;
  LPSTR Name;
  } clist[2] = { { 1 , NULL , "nodrop" } , { 2 , NULL , "dodrop" } } ;
HCURSOR GetCursor (short Id)
  {
  for (int i = 0 ; i < sizeof(clist) / sizeof(*clist) ; i++) {
    if (clist[i].Id == Id) {
      if (!clist[i].hCur)
        clist[i].hCur = LoadCursor(WBase::hInstance,clist[i].Name);
      return clist[i].hCur;
      }
    }
  return NULL;
  }

void FreeAllTrackCursors ()
  {
  for (int i = 0 ; i < sizeof(clist) / sizeof(*clist) ; i++)
    if (clist[i].hCur) DestroyCursor (clist[i].hCur) , clist[i].hCur = 0 ;
  }

BOOL TrackWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,LPTRACKWNDDATA lptw)
  {
  BOOL res = FALSE;
  POINT pt;
  MouseFunc FAR *mf;
  switch (msg) {
    case WM_SETCURSOR :
      if (lastCursor != 0) {
        HCURSOR hcur = GetCursor (lastCursor);
        if (!hcur) hcur = LoadCursor (NULL,MAKEINTRESOURCE(lastCursor));
        if (hcur)
          SetCursor (hcur);
        res = TRUE ;
        }
      else
        res = FALSE ;
      break ;
    case WM_DESTROY :
      lastCursor = 0;
      break ;
    case WM_LBUTTONDOWN :
    case WM_RBUTTONDOWN :
      SetupTracking (hWnd,lptw);
      if ((mf = IsThereWaitProc (hWnd,WM_LBUTTONUP)) != NULL) {
        if (GetFocus () != hWnd) {
          SetFocus (hWnd);
          }
        res = lDownDone = DoLButtonDownProc (mf,hWnd,LOWORD(lP),HIWORD(lP)) ;
        }
      break ;

#ifdef UEBERLEGT
    case WM_KEYDOWN :
      GetCursorPos (&pt);
      ScreenToClient (hWnd,&pt);
      wP = (GetKeyState (VK_LBUTTON) < 0) ? MK_LBUTTON : 0 ;
#endif
    case WM_MOUSEMOVE :
      mf = IsThereWaitProc (hWnd,WM_MOUSEMOVE);
      if (msg == WM_MOUSEMOVE)
        pt.x = LOWORD(lP) , pt.y = HIWORD(lP);
      if (mf != NULL) {
        DoWaitProc (mf,hWnd,pt.x,pt.y,TRUE,((wP & MK_LBUTTON) != 0),FALSE);
        }
      if ((msg == WM_MOUSEMOVE) && (wP & MK_LBUTTON) || (wP & MK_RBUTTON)) {
        SetupTracking (hWnd,lptw);
        if (((mf = IsThereWaitProc (hWnd,WM_LBUTTONUP)) != NULL) && (lDownDone))
          res = TRUE ;
        }
      else
        EndTracking (hWnd,lptw);
      if (msg == WM_KEYDOWN)
        res = FALSE ;
      break ;

    case WM_TIMER :
      if (wP == TRACKTIMERID) {
        if (!externCapture) Scroll (hWnd);
        res = TRUE ;
        }
      break ;

    case WM_LBUTTONUP :
    case WM_RBUTTONUP :
      EndTracking (hWnd,lptw);
      if (((mf = IsThereWaitProc (hWnd,WM_LBUTTONUP)) != NULL) && (lDownDone)) {
        res = DoWaitProc (mf,hWnd,LOWORD(lP),HIWORD(lP),FALSE,FALSE,TRUE);
        }
      lDownDone = FALSE ;
      break ;

    case WM_LBUTTONDBLCLK :
    case WM_RBUTTONDBLCLK :
      if ((mf = IsThereWaitProc (hWnd,WM_LBUTTONUP)) != NULL) {
        res = DoWaitProc (mf,hWnd,LOWORD(lP),HIWORD(lP),FALSE,FALSE,FALSE,TRUE);
        }
      lDownDone = FALSE ;
      break ;
    }
  return res;
  }

BOOL MouseMoveProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MouseFunc FAR *mf = IsThereWaitProc (c->OutWnd(),WM_MOUSEMOVE);
    if (mf == NULL)
      InsertIntoWaitList (c->OutWnd(),WM_MOUSEMOVE,c,(WaitOnMouseClk_param FAR *) param);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    MouseFunc FAR *mf = IsThereWaitProc (c->OutWnd(),WM_MOUSEMOVE);
    if (mf != NULL)
      RemoveFromWaitList (mf);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetDDSCapture_param {
  WORD  parSize;
  DWORD child;
  };
#pragma pack()

extern DLLExport void _export WINAPI doCaptureOff ();
BOOL SetDDSCapture (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    doCaptureOff ();
    SetDDSCapture_param FAR *par = (SetDDSCapture_param FAR *) param;
    LPMDICHILD FAR *wnd = (LPMDICHILD FAR *) c->ReadlData (par->child);
    DBWIN_ASSERT ((wnd != NULL) && (*wnd != NULL));
    externCapture = TRUE;
    SetupTracking ((*wnd)->OutWnd(),&((*wnd)->GetOutData()->twd));
    lDownDone = TRUE;
    }
  return FALSE ;
  }

#pragma pack(1)
struct PopupMenu_param FAR {
  WORD parSize;
  DWORD pos;
  struct {
    DWORD Name;
    DWORD Proc;
    } pp[1];
  int AnzPairs ()
    {
    return (parSize - (sizeof(*this) - sizeof(pp[0]))) / sizeof(pp[0]);
    }
  };
#pragma pack()
static mdiChild *lastPopupChild;
static PopupMenu_param FAR *pmpar;
#ifdef ALTER_SCHEISS
BOOL procFound (WPARAM wp)
  {
  if (pmpar) {
    for ( int i = 0 ; (i < pmpar->AnzPairs()) ; i ++) {
      if (wp == pmpar->pp[i].Proc) return TRUE ;
      }
    }
  return FALSE;
  }

void CheckWMCommand (HWND hWnd,WPARAM wP)
  {
  if ((lastPopupChild != NULL) &&
      (lastPopupChild->OutWnd() == hWnd) &&
      (procFound (wP))) {
    lastPopupChild->ExCuteProc (wP,EM_LOAD | EM_CHANGETOTRUE);
    lastPopupChild->ExCuteProc (wP,EM_CLEAR | EM_RESET);
    }
  }
#endif

void CheckWMCommand (HWND hWnd,WPARAM wP)
  {
  if ((lastPopupChild != NULL) &&
      (lastPopupChild->OutWnd() == hWnd) &&
      (int(wP) >= 1000) &&
      (pmpar != NULL)) {
    DWORD Proc = pmpar->pp[int(wP) - 1000].Proc;
    lastPopupChild->ExCuteProc (Proc,EM_LOAD | EM_CHANGETOTRUE);
    lastPopupChild->ExCuteProc (Proc,EM_CLEAR | EM_RESET);
    }
  }

BOOL ShowPopupMenu (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PopupMenu_param FAR *par = (PopupMenu_param FAR *) param;
    pmpar = par;
    fpt FAR *lfp = (fpt FAR *) c->ReadlData (par->pos);
    if (lfp != NULL) {
      HWND hWnd = c->OutWnd();
      PaintContext pc;
      GetDocumentContext (&pc,c);
      POINT pt;
      pt.x = int (lfp->x);
      pt.y = int (lfp->y);
      LPtoDP (pc.hDC,&pt,1);
      LPMENULIST firstPopup = NULL;
      toolbar_cbdata h(c);
      for ( int i = par->AnzPairs () - 1 ; i >= 0 ; i -- ) {
        LPSTR Name = LPSTR (c->ReadlData (par->pp[i].Name));
        if (Name != NULL) {
          BOOL mitSeparator = FALSE;
          if (*Name == '_') {
            mitSeparator = TRUE;
            Name++;
            }
          LPMENULIST n = LPMENULIST (GetGlobMem (sizeof(*n)));
          n->Next = firstPopup;
          n->Proc = DWORD(i + 1000);   // par->pp[i].Proc;
          n->Text = Name;
          n->MenuPrivData = &h;
          n->MenuProcPar = param;
          n->Flags = MF_STRING;
          firstPopup = n;
          if (mitSeparator) {
            LPMENULIST n = LPMENULIST (GetGlobMem (sizeof(*n)));
            n->Next = firstPopup;
            n->Proc = NULL;
            n->Text = NULL;
            n->MenuPrivData = NULL;
            n->MenuProcPar = NULL;
            n->Flags = MF_SEPARATOR;
            firstPopup = n;
            }
          }
        }

      lastPopupChild = c;
      HandlePopupMenu (hWnd, pt, NULL,firstPopup);

      if (h.Extra != NULL) FreeGlobMem (h.Extra);

      for ( ; (firstPopup != NULL) ; ) {
        LPMENULIST n = firstPopup->Next ;
        FreeGlobMem (firstPopup);
        firstPopup = n;
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    PopupMenu_param FAR *par = (PopupMenu_param FAR *) param;
    for ( int i = par->AnzPairs () - 1 ; i >= 0 ; i -- )
      c->ClearlConnection (par->pp[i].Name,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

