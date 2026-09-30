//---------------------------------------------------------------------------
//   MDI-Child zum Verwalten von weiteren Kindfenstern
//---------------------------------------------------------------------------
//   $Header:   P:/marille/clinicum/restool/rev/wndinmdi.cpv   1.9   02 Jan 1998 10:06:48   Gerhold  $
//   $Log:   P:/marille/clinicum/restool/rev/wndinmdi.cpv  $
// 
//    Rev 1.9   02 Jan 1998 10:06:48   Gerhold
// 16 -> 32 Bit Fehlerkorrektur
// 
//    Rev 1.8   05 Nov 1997 09:07:16   Gerhold
// 32 Bit
// 
//    Rev 1.7   28 Aug 1997 15:51:00   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   21 Oct 1996 18:56:36   HANNES
// Erweiterte Debugfunktionalitaet
// 
//    Rev 1.5   02 Feb 1996 10:50:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   15 May 1995 08:51:58   GERHOLD
// 
//    Rev 1.3   26 Apr 1995 15:27:08   HANNES
// 
//    Rev 1.2   24 Apr 1995 15:43:58   GERHOLD
// 
//    Rev 1.1   31 Mar 1995 18:23:42   HANNES
//  
// 
//    Rev 1.0   16 Feb 1995 12:43:52   GERHOLD
// Initial revision.
//---------------------------------------------------------------------------
#define MODULENUM 27

#include <windows.h>
#include "dds32.h"

#include "winass.hpp"
#include "BlandMDI.hpp"


class FAR ChildInMDI {
 public:
  HWND hWnd;
  HWND hWndParent;
  int  x0, y0, x1, y1;

  ChildInMDI FAR *Next;
  
  ChildInMDI (LPWNDDEF ChildDef, HWND hParent);
  
  void GetDeviceCoordinates (int cx, int cy, LPINT x0, LPINT y0, LPINT x1, LPINT y1);
  };
typedef ChildInMDI FAR *LPCHILDINMDI;

#define   MAXX    1000
#define   MAXY    1000

BOOL RegisterDummyWindow ();


ChildInMDI::ChildInMDI (LPWNDDEF ChildDef, HWND hParent)
  {
  hWndParent = hParent;
  Next = NULL;

  x0 = ChildDef->x0;
  y0 = ChildDef->y0;
  x1 = ChildDef->x1;
  y1 = ChildDef->y1;

  RECT rc;
  GetClientRect (hWndParent, &rc);
  int cx = rc.right - rc.left;
  int cy = rc.bottom - rc.top;

  int dx0, dy0, dx1, dy1;
  GetDeviceCoordinates (cx, cy, &dx0, &dy0, &dx1, &dy1);
  hWnd = CreateWindow ("Dummy", NULL, WS_CHILD | /*WS_BORDER |*/ WS_VISIBLE | WS_CLIPSIBLINGS,
                        dx0, dy0, dx1-dx0, dy1-dy0, hWndParent, 0, MyInstance, NULL);
  ChildDef->hWnd = hWnd;
  }

//--------------------------  GetDeviceCoordinates  -------------------------
//
// wandelt die logischen Koordinaten in Geraetekoordinaten um
//---------------------------------------------------------------------------
#define BORDER 2
void ChildInMDI::GetDeviceCoordinates  (int cx, int cy, LPINT dx0, LPINT dy0, LPINT dx1, LPINT dy1)
  {
  *dx0 = MulDiv (cx, x0, MAXX) + BORDER;
  *dy0 = MulDiv (cy, y0, MAXY) + BORDER;

  *dx1 = MulDiv (cx, x1, MAXX) - 2*BORDER;
  *dy1 = MulDiv (cy, y1, MAXY) - 2*BORDER;
  }



static HMENU MyMenu;
BOOL FAR CreateChildWindowsInMDI (LPSTR Title, int AnzChilds, LPWNDDEF ChildArray, LONG ExitProc, HMENU hMenu)
  {
  if (!RegisterDummyWindow())
    return FALSE;

  LPCHILDINMDI FirstChild = NULL;

  MyMenu = hMenu;
  HMENU hMenuWndInMDIWindow = GetSubMenu(MyMenu, 3);
  if (GetMenu (hwndFrame) != MyMenu) {

#ifdef WIN32
    SendMessage (hwndMDIClient, WM_MDISETMENU, (WPARAM)MyMenu, (LPARAM)hMenuWndInMDIWindow);
#else
    SendMessage (hwndMDIClient, WM_MDISETMENU, 0, MAKELONG(MyMenu, hMenuWndInMDIWindow));
#endif

    DrawMenuBar (hwndFrame);  
    }

  HWND hWndMDIChild = MakeNewChildContainer (Title);
  
  for (int i = 0; i < AnzChilds; i++) {
    LPCHILDINMDI lpc = new ChildInMDI (&ChildArray[i], hWndMDIChild);
    WIN_ASSERT (lpc != NULL);

    lpc->Next = FirstChild;
    FirstChild = lpc;
    }
  SetFocus (hWndMDIChild);

  SetWindowLong (hWndMDIChild,4,LONG(FirstChild));

  return TRUE;  
  }


int AnzWindows (LPCHILDINMDI FirstChild)
  {
  int res = 0;
  for (LPCHILDINMDI lpc = FirstChild; lpc != NULL; lpc = lpc->Next, res++);
  
  return res;
  }

BOOL IsSameClass (HWND h1,HWND h2)
  {
  if (!IsWindow (h1)) return TRUE ;
  if (!IsWindow (h2)) return TRUE ;
  char c1[64],c2[64];
  GetClassName (h1,c1,sizeof(c1));
  GetClassName (h2,c2,sizeof(c2));
  return (lstrcmp (c1,c2) == 0) ;
  }

DLLExport LONG FAR PASCAL _export MDIChildContainerWndProc (HWND hwnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  switch (msg) {
    case WM_MDIACTIVATE :
      {
      BOOL bActivate;
      HWND hWndActivate, hWndDeactivate;

#ifdef WIN32
      bActivate = (hwnd == HWND(lP));
      hWndActivate = HWND(lP);
      hWndDeactivate = HWND(wP);
#else
      bActivate = wP;
      hWndActivate = HWND(LOWORD(lP));
      hWndDeactivate = HWND(HIWORD(lP));
#endif

      if (bActivate) {
        if (!IsSameClass (hWndActivate, hWndDeactivate)) {
          HMENU hMenuWndInMDIWindow = GetSubMenu(MyMenu, 3);

#ifdef WIN32
          SendMessage (hwndMDIClient, WM_MDISETMENU, (WPARAM)MyMenu, (LPARAM)hMenuWndInMDIWindow);
#else
          SendMessage (hwndMDIClient, WM_MDISETMENU, 0, MAKELONG(MyMenu, hMenuWndInMDIWindow));
#endif
          DrawMenuBar (hwndFrame);  
          }
        }
      else {
        if (!IsSameClass (hWndActivate, hWndDeactivate)) {
#ifdef WIN32
          SendMessage (hwndMDIClient, WM_MDISETMENU, (WPARAM)hMenuMain, (LPARAM)hMenuMainWindow);
#else
          SendMessage (hwndMDIClient, WM_MDISETMENU, 0, MAKELONG(hMenuMain, hMenuMainWindow));
#endif
          DrawMenuBar (hwndFrame);  
          }
        }
      }
      return 0;
      
    case WM_SETFOCUS :
      {
      HWND hWChild = GetWindow (hwnd,GW_CHILD);
      if (IsWindow(hWChild))
        SetFocus (hWChild);
      }
      break ;
      
    case WM_SIZE:
      {
      int dx0, dy0, dx1, dy1;
      int cx = LOWORD(lP);
      int cy = HIWORD(lP);

      LPCHILDINMDI FirstChild = LPCHILDINMDI (GetWindowLong (hwnd,4));

      int aw = AnzWindows(FirstChild);
      if (aw > 0) {
        HDWP hdwp = BeginDeferWindowPos (aw);
        if (hdwp) {
          for (LPCHILDINMDI lpc = FirstChild; lpc != NULL; lpc = lpc->Next) {
            lpc->GetDeviceCoordinates (cx, cy, &dx0, &dy0, &dx1, &dy1);
            DeferWindowPos (hdwp, lpc->hWnd, 0, dx0, dy0, dx1-dx0, dy1-dy0,
                            SWP_NOZORDER | SWP_SHOWWINDOW);
            }

          EndDeferWindowPos (hdwp);
          }
        }
      
      break;
      }

    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      RECT rc, rcClient;
      
      LPCHILDINMDI FirstChild = LPCHILDINMDI (GetWindowLong (hwnd,4));
      
      GetClientRect (hwnd, &rcClient);
      int cx = rcClient.right;
      int cy = rcClient.bottom;
    
      int dx0, dy0, dx1, dy1;

      HDC hDC = BeginPaint (hwnd, &ps);
      for (LPCHILDINMDI lpc = FirstChild; lpc != NULL; lpc = lpc->Next) {
        lpc->GetDeviceCoordinates (cx, cy, &dx0, &dy0, &dx1, &dy1);

        SetBkColor (hDC, RGB(0x80, 0x80, 0x80));
        SetRect (&rc, dx0, dy0-1, dx1+1, dy0);
        ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
        SetRect (&rc, dx0-1, dy0-1, dx0, dy1+1);
        ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
      
        SetBkColor (hDC, RGB(0xFF, 0xFF, 0xFF));
        SetRect (&rc, dx1, dy0, dx1+1, dy1);
        ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
        SetRect (&rc, dx0, dy1, dx1, dy1+1);
        ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
        }
      EndPaint (hwnd, &ps);  
      }
      return 0;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      LPCHILDINMDI FirstChild = LPCHILDINMDI (GetWindowLong (hwnd,4));
      for ( ; ((FirstChild != NULL) && (FirstChild->Next != NULL)) ; FirstChild = FirstChild->Next) ;
      if ((FirstChild != NULL) && ((CRACKER_wID == 110) || (CRACKER_wID == 111)))
        return SendMessage (FirstChild->hWnd,WM_COMMAND,wP,lP);
      }
      return 0;

    }
  return DefMDIChildProc(hwnd, msg, wP, lP);
  }


DLLExport LONG FAR PASCAL _export DummyWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
  return DefWindowProc (hwnd, msg, wParam, lParam);
  }


static BOOL bDummyRegistered = FALSE;
BOOL RegisterDummyWindow ()
  {
  if (!bDummyRegistered) {
    WNDCLASS wc;
    wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DummyWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LONG);
    wc.hInstance = MyInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
#ifdef WIN32
    wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
#else
    wc.hbrBackground = COLOR_WINDOW + 1;
#endif
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Dummy";

    if (RegisterClass(&wc))
      bDummyRegistered = TRUE;
    }
    
  return bDummyRegistered;
  }

