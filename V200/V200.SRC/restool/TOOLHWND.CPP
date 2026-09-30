////////////////////////////////////////////////////
//  Popup - Window mit den wichtigsten Tools
////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/toolhwnd.cpv   1.8   07 May 1999 17:01:30   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/toolhwnd.cpv  $
// 
//    Rev 1.8   07 May 1999 17:01:30   Wolfgang
// 1.) Window-Groessen-Berechnung korrigiert.
// 
//    Rev 1.7   05 Oct 1998 11:28:22   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.6   15 Dec 1997 17:37:06   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.5   28 Aug 1997 15:51:30   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.4   02 Feb 1996 10:50:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   02 Jan 1995 09:31:12   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.2   25 Jul 1994 09:38:32   GERHOLD
// 
//    Rev 1.1   12 Jul 1994 14:45:14   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:54:50   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#define MODULENUM 105
#include "winass.hpp"
#include "drdrop.hpp"
#include "toolbar.hpp"
#include "ddsmsg.h"

extern HINSTANCE MyInstance;
struct PopupTool {
  PopupTool FAR *Next;
  HBITMAP bmp;
  WORD    HelpIndex;
  LPSTR   Name;
  };
typedef PopupTool FAR *LPPTL;
LPPTL ptlist;
void AddToptlist (LPPTL t)
  {
  for (LPPTL FAR *p = &ptlist; *p != NULL ; p = &(*p)->Next) ; *p = t;
  }

static int bx,by;
void AddBitmapTool (LPSTR name,WORD hi)
  {
  LPPTL n = LPPTL (GetGlobMem (sizeof(*n)));
  n->Name = name;
  n->HelpIndex = hi;
  n->bmp = LoadBitmap (MyInstance,n->Name);
  BITMAP bi;
  GetObject (n->bmp,sizeof(bi),&bi);
  if (ptlist == NULL)
    bx = bi.bmWidth , by = bi.bmHeight;
  else
    WIN_ASSERT ((bx == bi.bmWidth) && (by == bi.bmHeight));
  AddToptlist (n);
  }

BOOL BitmapToolsLoaded ()
  {
  return (ptlist != NULL);
  }

void FreeBitmapTools()
  {
  for ( ; ptlist != NULL ; ) {
    LPPTL n = ptlist->Next ;
    DeleteObject (ptlist->bmp);
    FreeGlobMem (ptlist);
    ptlist = n;
    }
  }

int AnzTools()
  {
  int j = 0;
  for (LPPTL p = ptlist ; p != NULL ; p = p->Next)
    j ++ ;
  return j;
  }

#define ANZCOLUMNS 3
void GetToolInfo (HWND hWnd,int x,int y,LPPOINT pt,LPTOOLDD d,BOOL CheckTool)
  {
  pt->x = x ;
  pt->y = y ;
  d->pts = *pt ;
  ClientToScreen (hWnd,&d->pts);
  if (CheckTool) {
    d->ToolName = NULL;
    int ix = x / bx ;
    int iy = y / by ;
    int i = ix + iy * ANZCOLUMNS;
    int j = 0;
    for (LPPTL p = ptlist ; p != NULL ; p = p->Next , j ++) {
      if (i == j)
        d->ToolName = p->Name;
      }
    }
  }

static ToolDropData tdd;
BOOL TOnLButtonDown (HWND hWnd,int x,int y)
  {
  POINT pt;
  GetToolInfo (hWnd,x,y,&pt,&tdd,TRUE);
  return DDOnMouseMove (DDTYPE_TOOL, &tdd,&pt,hWnd,FALSE);
  }

void TOnMouseMove (HWND hWnd,int x,int y)
  {
  POINT pt;
  GetToolInfo (hWnd,x,y,&pt,&tdd,FALSE);
  DDOnMouseMove (DDTYPE_TOOL, &tdd,&pt,hWnd,FALSE);
  }

void TOnLButtonUp (HWND hWnd,int x,int y)
  {
  POINT pt;
  GetToolInfo (hWnd,x,y,&pt,&tdd,FALSE);
  DDOnMouseMove (DDTYPE_TOOL, &tdd,&pt,hWnd,TRUE);
  }

extern LPSTR IniFile();
inline char *TBName() { return "Toolbar" ; }
void ReadTbPos (int FAR *x,int FAR *y)
  {
  *x = GetPrivateProfileInt (TBName(),"_X",400,IniFile());
  *y = GetPrivateProfileInt (TBName(),"_Y",100,IniFile());
  }

void WriteTbPos (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (TBName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (TBName(),"_Y",outstring,IniFile());
  }

HWND ShowHelpWindow(POINT pt,HWND hWnd)
  {
  int ix = pt.x / bx ;
  int iy = pt.y / by ;
  int i = ix + iy * ANZCOLUMNS;
  int j = 0;
  WORD hi;
  for (LPPTL p = ptlist ; p != NULL ; p = p->Next , j ++) {
    if (i == j) {
      hi = p->HelpIndex;
      break ;
      }
    }

  char helptext[256];
  *helptext = '\0';

  LoadString (MyInstance,hi,helptext,sizeof(helptext));

  return CreateBubbleWindow (pt.x, pt.y, helptext, hWnd);
  }

static HWND ctw;
static HWND hwbubble;
DLLExport LONG _export FAR PASCAL ToolPopupProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  LONG RetVal = 0;
  static BOOL CaptureDone;

  switch (msg) {
    case WM_LBUTTONDOWN :
      if (TOnLButtonDown (hWnd,short (LOWORD(lP)),short (HIWORD(lP)))) {
        SetCapture (hWnd);
        CaptureDone = TRUE ;
        }
      break ;
    case WM_MOUSEMOVE :
      if (CaptureDone)
        TOnMouseMove (hWnd,short(LOWORD(lP)),short(HIWORD(lP)));
      break ;
    case WM_LBUTTONUP :
      if (CaptureDone) {
        TOnLButtonUp (hWnd,short(LOWORD(lP)),short(HIWORD(lP)));
        ReleaseCapture ();
        }
      CaptureDone = FALSE ;
      break ;
    case WM_MOVE :
      WriteTbPos (hWnd);
      break ;
    case WM_RBUTTONDOWN :
      {
      POINT pt;

#ifdef WIN32
  LONG2POINT (lP, pt);
#else
  pt = MAKEPOINT (lP);
#endif

      SetCapture (hwbubble = ShowHelpWindow(pt,hWnd));
      }
      break ;
    case WMU_DESTROYBUBBLE:
      ReleaseCapture ();
      DestroyWindow (hwbubble);
      break ;
    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd, &ps) ;
      HDC MemDC = CreateCompatibleDC(hDC);
      int i = 0 ;
      for (LPPTL p = ptlist ; p != NULL ; p = p->Next , i++) {
        SelectObject (MemDC,p->bmp);
        int ix = i % ANZCOLUMNS ;
        int iy = i / ANZCOLUMNS ;
        BitBlt (hDC, ix * bx, iy * by,
                     bx, by,
                MemDC,
                     0,0,
                     SRCCOPY
               );
        }
      DeleteDC (MemDC);
        EndPaint (hWnd, &ps) ;
      }
      break;
    case WM_DESTROY :
      ctw = 0;
      break;
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;
    }
  return RetVal;
  }

void RegisterToolWnd ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = ToolPopupProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = 0 ;
    wndclass.lpszClassName = "TPWND" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

int AnzRows (int AnzTools,int AnzColumns)
  {
  int r1 = AnzTools / AnzColumns;
  int r2 = ((AnzTools % AnzColumns) != 0) ? 1 : 0 ;
  return r1 + r2 ;
  }

void CreateToolWnd (HWND hParent)
  {
  RegisterToolWnd ();
  int x,y;
  ReadTbPos (&x,&y);
  ctw = CreateWindow ("TPWND","Tools",
                      WS_POPUP | WS_CAPTION | 
                      WS_BORDER | WS_VISIBLE ,
                      x,y,
                      ANZCOLUMNS * bx + 2 * GetSystemMetrics(SM_CXFIXEDFRAME),
                      AnzRows (AnzTools(),ANZCOLUMNS) * by + 2 * GetSystemMetrics(SM_CYFIXEDFRAME) +
                        GetSystemMetrics (SM_CYCAPTION),
                      hParent,
                      NULL,                   
                      MyInstance,              
                        NULL
                     ) ;
  SetWindowPos (ctw,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
  }

void DestroyToolWnd ()
  {
  if (ctw)
    DestroyWindow (ctw);
  FreeBitmapTools();
  }
