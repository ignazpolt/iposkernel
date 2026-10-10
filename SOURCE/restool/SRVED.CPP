/*-----------------------------*/
/*  Bearbeiten der Serverinfo  */
/*-----------------------------*/
//
// $Header:   P:/marille/clinicum/restool/rev/srved.cpv   1.5   05 Oct 1998 11:28:06   Gerhold  $
// $Log:   P:/marille/clinicum/restool/rev/srved.cpv  $
// 
//    Rev 1.5   05 Oct 1998 11:28:06   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   28 Aug 1997 15:51:08   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.3   02 Feb 1996 10:50:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   26 Apr 1995 15:27:06   HANNES
// 
//    Rev 1.1   16 Feb 1995 12:34:06   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.0   29 Jan 1995 11:48:12   HANNES
// Initial revision.
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

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "srved.hpp"
#include "restool.hpp"


#define GWL_SRVINF    0
extern HWND hwndFrame;
void SrvEd::InitializeMenu (HMENU hMenu)
  {
  EnableMenuItem (hMenu,IDM_COPY, MF_ENABLED);
  EnableMenuItem (hMenu,IDM_CUT, MF_ENABLED);
  BOOL bPasteStatus = MF_GRAYED;
  if (OpenClipboard (hwndFrame)) {
    if (IsClipboardFormatAvailable(CF_TEXT) || 
        IsClipboardFormatAvailable(CF_OEMTEXT))
          bPasteStatus = MF_ENABLED;

    CloseClipboard();  
    }
  EnableMenuItem (hMenu, IDM_PASTE, bPasteStatus);
  }

LONG FAR PASCAL SrvEdWndProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  LONG RetVal = 0L;
  SrvEd FAR *s = (SrvEd FAR *) GetWindowLong (hWnd,GWL_SRVINF);
  HWND hWndChild = GetWindow (hWnd, GW_CHILD);
  
  switch (msg) {
    case WM_SETFOCUS:
      if (IsWindow(hWndChild))
        SetFocus (hWndChild);
      break;
      
    case WM_PARENTNOTIFY:
#ifdef WIN32
      if (LOWORD(wP) == WM_CREATE) {
        SetFocus (HWND(lP));
        return 0;
        }
#else
      if (wP == WM_CREATE) {
        SetFocus (LOWORD(lP));
        return 0;
        }
#endif
      break;  
      
    case WM_CHILDACTIVATE:
      if (IsWindow(hWndChild))
        SetFocus (hWndChild);
      break;  

    case WM_PAINT :
      {
      PAINTSTRUCT ps ;
      HDC hdc = BeginPaint (hWnd, &ps) ;
      EndPaint (hWnd, &ps) ;
      }
      return 0L;

    case WM_CLOSE :
      s->Hide();
      RetVal = 0L;
      break ;
    case WM_DESTROY :
      s->WritePos();
      break ;
    case WM_INITMENU :
      s->InitializeMenu (HMENU (wP));
      break ;

    case WM_COMMAND :
      SendMessage(hWndChild,msg,wP,lP);
      break ;

    case WM_SIZE:
      if (IsWindow(hWndChild))
        MoveWindow (hWndChild, 0, 0, LOWORD(lP), HIWORD(lP), TRUE);
      // ACHTUNG WM_SIZE muss weitergeleitet werden!!!!!
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal;
  }

static char szSrvClassName[] = "SRVED";
extern HINSTANCE MyInstance;
void SrvEd::Register()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wc;
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = SrvEdWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = MyInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = "";
    wc.lpszClassName = szSrvClassName;

    RegisterClass (&wc);
    Registered = TRUE;
    }
  }

extern void ShowScript (HWND hWnd, GLOBALHANDLE hGTxt, BOOL IsMain);
extern LPSTR IniFile();
void SrvEd::GetPos(int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetProfInt ("LEFT",100);
  *y = GetProfInt ("TOP",100);
  *w = GetProfInt ("CLW",300);
  *h = GetProfInt ("CLH",400);
  }

void SrvEd::WritePos()
  {
  RECT rc;
  GetWindowRect (hWnd,&rc);
  SetProfInt ("LEFT",rc.left);
  SetProfInt ("TOP",rc.top);
  SetProfInt ("CLW",rc.right - rc.left + 1);
  SetProfInt ("CLH",rc.bottom - rc.top + 1);
  }

int SrvEd::GetProfInt (LPSTR Name,int def)
  {
  return MyGetProfInt ("SRVED",Name,def);
  }

void SrvEd::SetProfInt (LPSTR Name,int val)
  {
  MySetProfInt ("SRVED",Name,val);
  }

void SrvEd::Create()
  {
  Register ();

  HMENU hmenu = LoadMenu (MyInstance,"SRVEDMENU");
  int x,y,w,h;
  GetPos (&x,&y,&w,&h);
  hWnd = CreateWindow(szSrvClassName, Caption, 
                           WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU,
                           x,y,w,h,
                           hwndFrame, hmenu,
                           MyInstance, NULL
                     );
  SetWindowLong (hWnd,GWL_SRVINF,LONG(this));
  ShowScript (hWnd, hGTxt, FALSE);
  GlobalFree (hGTxt);
  hGTxt = 0;
  }

void SrvEd::Show ()
  {
  ShowWindow (hWnd,SW_SHOW);
  }

void SrvEd::Hide ()
  {
  ShowWindow (hWnd,SW_HIDE);
  }

SrvEd FAR *FirstSrvEd;
SrvEd::SrvEd (LPSTR c,GLOBALHANDLE hGT)
  {
  Next = FirstSrvEd;
  FirstSrvEd = this;
  Caption = LPSTR (GetGlobMem (lstrlen(c)+1));
  lstrcpy (Caption,c);
  hGTxt = hGT;
  }

SrvEd::~SrvEd ()
  {
  SrvEd FAR *prev = NULL;
  for (SrvEd FAR *h = FirstSrvEd ; h != NULL ; h = h->Next) {
    if (h == this) {
      if (prev != NULL) prev->Next = Next;
      else              FirstSrvEd = Next;
      break ;
      }
    prev = h;
    }
  if (Caption != NULL) FreeGlobMem (Caption);
  if (IsWindow (hWnd)) DestroyWindow (hWnd);
  }

extern GLOBALHANDLE GetSrcText (HWND hwndChild);
GLOBALHANDLE SrvEd::GetServerInfo ()
  {
  HWND hwndChild = GetWindow (hWnd,GW_CHILD);
  if (hwndChild)
    return GetSrcText (hwndChild);
  else
    return NULL;
  }

HWND GetActiveSrvHandle ()
  {
  HWND hActWnd = GetFocus ();
  HWND hActWnd1;
  if (IsWindow (hActWnd)) hActWnd1 = GetParent(hActWnd);
  else                    hActWnd1 = 0;
  for (SrvEd FAR *h = FirstSrvEd ; h != NULL ; h = h->Next) {
    if ((h->hWnd == hActWnd) || (h->hWnd == hActWnd1)) return h->hWnd;
    }
  return NULL;
  }

static HANDLE SrvAcc;
BOOL CheckSrvAcc (MSG FAR *msg)
  {
  return FALSE ;
  }


