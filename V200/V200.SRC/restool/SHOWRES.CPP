////////////////////////////////////////////////////////////////
//  Generieren des Resourcen
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/showres.cpv   1.10   09 Mar 1999 16:04:46   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/showres.cpv  $
// 
//    Rev 1.10   09 Mar 1999 16:04:46   Gerhold
// Mausmeldungen mit (short) .... gecastet
// 
//    Rev 1.9   16 Nov 1998 16:40:48   Gerhold
// Bei klicken mit der linken Maustaste in das resourcenfenster schliesst sich
// der Resourcenlisten-Dialog
// 
//    Rev 1.8   03 Nov 1998 09:19:20   Gerhold
// Das Bitmap Fenster oeffnet sich bereits bei LBN_SELCHANGE
// 
//    Rev 1.7   05 Oct 1998 11:28:02   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.6   22 Apr 1998 08:41:34   Gerhold
// Der Doppelklick in der Resdialog-Proc wurde wieder aktiviert
// 
//    Rev 1.5   05 Nov 1997 09:04:42   Gerhold
// 32 Bit
// 
//    Rev 1.4   28 Aug 1997 15:52:12   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.3   02 Feb 1996 10:50:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   10 Apr 1995 10:45:14   GERHOLD
// 
//    Rev 1.1   02 Jan 1995 09:31:10   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   24 Jun 1994 16:54:50   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 93
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "resadmin.hpp"

//#include "subclass.hpp"

#include "drdrop.hpp"

extern HINSTANCE MyInstance;

struct CreateRsData {
  char  RsName[64];
  DWORD Id;
  };

struct FAR RsDsc {
  WORD Type;
  GLOBALHANDLE hGmem;
  DWORD DataSize;
  BOOL CaptureDone;
  char RsName[64];

  union {
    struct {
      HBITMAP bmp;
      int AnzCols;
      int AnzRows;
      BitmapDropData dd;
      } b;
    struct {
      HMETAFILE hmf;
      } w;
    } info;

  void PaintBitmap (HWND hWnd,HDC hDC);
  void PaintWMF (HWND hWnd,HDC hDC);
  void PaintResource (HWND hWnd,HDC hDC);
  void InitializeBitmap (HWND hWnd);
  void InitializeWMF (HWND hWnd);
  void Initialize(HWND hWnd);

  void OnGetMinMaxInfo (HWND hWnd, LPARAM lP);
  void OnSize (HWND hWnd, int cx, int cy);
  void OnScroll (HWND hWnd, UINT msg, WORD wPos, WORD ScrollType);
  void OnLButtonDown (HWND hWnd,int x,int y);
  void OnMouseMove (HWND hWnd,int x,int y);
  void OnLButtonUp (HWND hWnd,int x,int y);
  };
typedef RsDsc FAR *LPRSDSC;

#define SCROLL_RATIO    4     // WM_VSCROLL scrolls DIB by 1/x of client area.


static HWND hResWnd = NULL;

//---------------------------------------------------------------------
//
// Function:   ReallyGetClientRect
//
// Purpose:    Gets the rectangular area of the client rect including
//             the area underneath visible scroll bars.  Stolen from
//             ShowDIB.
//---------------------------------------------------------------------
void ReallyGetClientRect (HWND hWnd, LPRECT lpRect)
  {
  DWORD dwWinStyle;

  dwWinStyle = GetWindowLong (hWnd, GWL_STYLE);

  GetClientRect (hWnd, lpRect);

  if (dwWinStyle & WS_HSCROLL)
     lpRect->bottom += GetSystemMetrics (SM_CYHSCROLL);

  if (dwWinStyle & WS_VSCROLL)
     lpRect->right  += GetSystemMetrics (SM_CXVSCROLL);
  }

//-----------------------  SetupScroller  -----------------------------------
//
//---------------------------------------------------------------------------
void SetupScroller (HWND hWnd, int cxDIB, int cyDIB)
  {
  RECT        rect;                         // Client Rectangle.
  BOOL        bNeedXScrollBars = FALSE;      // Need Scroll bars?
  BOOL        bNeedYScrollBars = FALSE;      // Need Scroll bars?
  unsigned    cxWindow,                     // Width of client area.
              cyWindow;                     // Height of client area.
  int         cxRange         = 0,          // Range needed for horz bar.
              cyRange         = 0;          // Range needed for vert bar.

  // Do some initialization.
//  ReallyGetClientRect (hWnd, &rect);
  GetClientRect (hWnd, &rect);

  cxWindow = rect.right - rect.left;
  cyWindow = rect.bottom - rect.top;


  // Now determine if we need the scroll bars.  Since the
  //  window is not allowed to be larger than the DIB, if
  //  we need one scroll bar, we need _both_.  Since if
  //  one scroll bar is turned on, it eats up some of
  //  the client area.
  if (cxWindow < (unsigned) cxDIB)
    bNeedXScrollBars = TRUE;

  if (cyWindow < (unsigned) cyDIB)
    bNeedYScrollBars = TRUE;

  // Setup the scroll bar ranges.  We want to be able to
  //  scroll the window so that all the DIB can appear
  //  within the client area.  Take into account that
  //  if the opposite scroll bar is activated, it eats
  //  up some client area.
  if (bNeedXScrollBars)
    cxRange = (unsigned) cxDIB - cxWindow - 1 + GetSystemMetrics (SM_CXVSCROLL);

  if (bNeedYScrollBars)
    cyRange = (unsigned) cyDIB - cyWindow - 1 + GetSystemMetrics (SM_CYHSCROLL);

  // Set the ranges we've calculated (0->0 means invisible scrollbar).
  SetScrollRange (hWnd, SB_VERT, 0, cyRange, TRUE);
  SetScrollRange (hWnd, SB_HORZ, 0, cxRange, TRUE);
  }

//-----------------------  InitializeBitmap  --------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::InitializeBitmap (HWND hWnd)
  {
  if (hGmem) {
    DBINT FAR *i = (DBINT FAR *) GlobalLock (hGmem);
    info.b.AnzCols = i[0] ;
    info.b.AnzRows = i[1] ;
    LPBITMAPINFOHEADER lpbi = LPBITMAPINFOHEADER (LPSTR (&i[2]) + 
                                  sizeof(BITMAPFILEHEADER)
                                                 );
    LPSTR Color = LPSTR (lpbi + 1);
    int nNumColors;
    if (!(nNumColors = (WORD)lpbi->biClrUsed)) {
      /* no color table for 24-bit, default size otherwise */
      if (lpbi->biBitCount != 24)
        nNumColors = 1 << lpbi->biBitCount; /* standard size table */
      }
    WORD offBits = nNumColors * sizeof(RGBQUAD);
    LPSTR lpbits = Color + offBits;

    // Erzeugen eines MemDC
    HDC hdc = CreateDC ("DISPLAY",NULL,NULL,NULL);
    HDC hdcMem = CreateCompatibleDC (hdc);
  
    // Erzeugen eines Bitmaps
    int bmWidth  = int (lpbi->biWidth) ;
    int bmHeight = int (lpbi->biHeight) ;
  
    info.b.bmp = CreateCompatibleBitmap (hdc,bmWidth,bmHeight);
    SelectObject (hdcMem,info.b.bmp);
  
    StretchDIBits (hdcMem,0,0,bmWidth,bmHeight,
                          0,0,
                          bmWidth,bmHeight,
                          lpbits,
                          LPBITMAPINFO (lpbi),
                          DIB_RGB_COLORS,SRCCOPY
                  );
  
    // Fertig
    DeleteDC (hdcMem);
    DeleteDC (hdc);

    GlobalFree (hGmem);
    hGmem = 0;

    SetWindowPos (hWnd, 0, 0, 0, bmWidth, bmHeight, SWP_NOMOVE | SWP_NOZORDER);

    char capt[128];
    char addtxt[24];
    GetWindowText (hWnd,capt,sizeof(capt));
    wsprintf (addtxt," %d x %d",info.b.AnzCols,info.b.AnzRows);
    lstrcat (capt,addtxt);
    SetWindowText (hWnd,capt);
    }
  }

//-----------------------  InitializeWMF  -----------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::InitializeWMF (HWND hWnd)
  {
  if (hGmem) {

#ifdef WIN32
    DWORD dwSize;
    info.w.hmf = SetMetaFileBitsEx (UINT(dwSize), (CONST BYTE *)hGmem);
#else
    info.w.hmf = SetMetaFileBits (hGmem);
#endif

    hGmem = 0;
    }
  }

//-----------------------  PaintBitmap  -------------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::PaintBitmap (HWND hWnd,HDC hDC)
  {
  BITMAP bi;
  HDC hMemDC = CreateCompatibleDC (hDC);

  int xScroll = GetScrollPos (hWnd, SB_HORZ);
  int yScroll = GetScrollPos (hWnd, SB_VERT);

  GetObject (info.b.bmp,sizeof(bi),&bi);
  int bmWidth  = bi.bmWidth  / info.b.AnzCols ;
  int bmHeight = bi.bmHeight / info.b.AnzRows ;

  SetupScroller (hWnd, bi.bmWidth, bi.bmHeight);

  HBITMAP OldBitmap = (HBITMAP)SelectObject (hMemDC, info.b.bmp);

  for (int i = 0 ; i < info.b.AnzCols ; i++) {
    for (int j = 0 ; j < info.b.AnzRows ; j ++ ) {
      BitBlt (hDC, i * bmWidth + i + 1 - xScroll,
                   j * bmHeight + j + 1 - yScroll,
                   bmWidth, bmHeight,
                   hMemDC,
                   bmWidth * i,bmHeight * j,
                   SRCCOPY
            );
      }
    }
  for (i = 0 ; i <= info.b.AnzCols ; i++) {
    MoveToEx (hDC,i * bmWidth + i - xScroll, 0, NULL);
    LineTo (hDC,i * bmWidth + i - xScroll, info.b.AnzRows * bmHeight + info.b.AnzRows);
    }
  for (int j = 0 ; j <= info.b.AnzRows ; j ++ ) {
    MoveToEx (hDC, 0, j * bmHeight + j - yScroll, NULL);
    LineTo (hDC, info.b.AnzCols * bmWidth + info.b.AnzCols, j * bmHeight + j - yScroll);
    }
  SelectObject (hMemDC, OldBitmap);
  DeleteDC (hMemDC);

  SetWindowOrgEx (hDC, GetScrollPos(hWnd, SB_HORZ),
                       GetScrollPos(hWnd, SB_VERT),
                  NULL);
  }


//-----------------------  OnSize  ------------------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::OnSize (HWND hWnd, int cx, int cy)
  {
  RECT rc;
  int cxScroll, cyScroll;
  GetClientRect (hWnd, &rc);
  cxScroll = GetScrollPos (hWnd, SB_HORZ);
  cyScroll = GetScrollPos (hWnd, SB_VERT);
      
  BITMAP bi;
  GetObject (info.b.bmp, sizeof(bi), &bi);
  
  int cxDIB = bi.bmWidth;
  int cyDIB = bi.bmHeight;

  if ((cxScroll + rc.right > cxDIB) || (cyScroll + rc.bottom > cyDIB))
    InvalidateRect (hWnd, NULL, FALSE);
        
  SetupScroller (hWnd, cxDIB, cyDIB);
  }

//-----------------------  OnGetMinMaxInfo  ---------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::OnGetMinMaxInfo (HWND hWnd, LPARAM lP)
  {
  MINMAXINFO FAR *lpmmi;
  lpmmi = (MINMAXINFO FAR *)lP;

  BITMAP bi;
  GetObject (info.b.bmp, sizeof(bi), &bi);
  
  int xScreen = GetSystemMetrics (SM_CXSCREEN);
  int yScreen = GetSystemMetrics (SM_CYSCREEN);
  
  xScreen -= xScreen / 10;
  yScreen -= yScreen / 5;

  RECT rc;
  GetWindowRect (hWnd, &rc);
  xScreen -= rc.left;

  xScreen = min(xScreen, bi.bmWidth);
  yScreen = min(yScreen, bi.bmHeight);

  lpmmi->ptMaxTrackSize.x = xScreen + 2*GetSystemMetrics(SM_CXFRAME) +
                                      GetSystemMetrics(SM_CXVSCROLL);
  lpmmi->ptMaxTrackSize.y = yScreen + GetSystemMetrics(SM_CYCAPTION) +
                                      2*GetSystemMetrics(SM_CYFRAME) +
                                      GetSystemMetrics(SM_CYHSCROLL);
  
  lpmmi->ptMinTrackSize.x;  lpmmi->ptMaxTrackSize.x;
  lpmmi->ptMinTrackSize.y = lpmmi->ptMaxTrackSize.y;
  }

//-----------------------  OnScroll  ----------------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::OnScroll (HWND hWnd, UINT msg, WORD wPos, WORD wScrollType)
  {
  int  xBar;                       // Where scrollbar is now.
  int  nMin;                       // Minumum scroll bar value.
  int  nMax;                       // Maximum scroll bar value.
  int  dx;                         // How much to move.
  int  nOneUnit;                   // # of pixels for LINEUP/LINEDOWN
  int  cxClient;                   // Width of client area.
  int  nHorzOrVert;                // Doing the horizontal or vertical?
  RECT rect;                       // Client area.


  GetClientRect (hWnd, &rect);

  if (msg == WM_HSCROLL)
     {
     nHorzOrVert = SB_HORZ;
     cxClient    = rect.right - rect.left;
     }
  else
     {
     nHorzOrVert = SB_VERT;
     cxClient    = rect.bottom - rect.top;
     }

     // One a SB_LINEUP/SB_LINEDOWN we will move the DIB by
     //  1/SCROLL_RATIO of the client area (i.e. if SCROLL_RATIO
     //  is 4, it will scroll the DIB a quarter of the client
     //  area's height or width.

  nOneUnit = cxClient / SCROLL_RATIO;
  if (!nOneUnit)
     nOneUnit = 1;

  xBar = GetScrollPos (hWnd, nHorzOrVert);
  GetScrollRange (hWnd, nHorzOrVert, &nMin, &nMax);

  switch (wScrollType)
     {
     case SB_LINEDOWN:             // One line right.
        dx = nOneUnit;
        break;

     case SB_LINEUP:               // One line left.
        dx = -nOneUnit;
        break;

     case SB_PAGEDOWN:             // One page right.
        dx = cxClient;
        break;

     case SB_PAGEUP:               // One page left.
        dx = -cxClient;
        break;

     case SB_THUMBPOSITION:        // Absolute position.
        dx = wPos - xBar;
        break;

     default:                      // No change.
        dx = 0;
        break;
     }

  if (dx)
     {
     xBar += dx;

     if (xBar < nMin)
        {
        dx  -= xBar - nMin;
        xBar = nMin;
        }

     if (xBar > nMax)
        {
        dx  -= xBar - nMax;
        xBar = nMax;
        }

     if (dx)
        {
        SetScrollPos (hWnd, nHorzOrVert, xBar, TRUE);

        if (nHorzOrVert == SB_HORZ)
           ScrollWindow (hWnd, -dx, 0, NULL, NULL);
        else
           ScrollWindow (hWnd, 0, -dx, NULL, NULL);

        UpdateWindow (hWnd);
        }
     }
  }


//-----------------------  OnLButtonDown  -----------------------------------
//
//---------------------------------------------------------------------------
void RsDsc::OnLButtonDown (HWND hWnd,int x,int y)
  {
  POINT pt;

  HDC hDC = GetDC (hWnd);
  SetWindowOrgEx (hDC, GetScrollPos(hWnd, SB_HORZ),
                       GetScrollPos(hWnd, SB_VERT),
                  NULL);
  ReleaseDC (hWnd, hDC);

  pt.x = x;
  pt.y = y;
  
  x += GetScrollPos (hWnd, SB_HORZ);
  y += GetScrollPos (hWnd, SB_VERT);

  switch (Type) {
    case RESTYPE_BITMAP :
      {
      BITMAP bi;
      GetObject (info.b.bmp,sizeof(bi),&bi);
      int bmWidth  = bi.bmWidth  / info.b.AnzCols ;
      int bmHeight = bi.bmHeight / info.b.AnzRows ;
      if ((x < bi.bmWidth + 1 + info.b.AnzCols) && 
              (y < bi.bmHeight + 1 + info.b.AnzRows)) {
        info.b.dd.BitmapName = RsName;
        info.b.dd.x = (x - 1) / (bmWidth + 1) ;
        info.b.dd.y = (y - 1) / (bmHeight + 1) ;
        CaptureDone = DDOnMouseMove(DDTYPE_BITMAP,&info.b.dd,&pt,hWnd,FALSE);
        }
      else
        CaptureDone = FALSE ;
      }
      break ;
    default :
      CaptureDone = FALSE ;
    }
  if (CaptureDone) {
//    SetCapture (GetParent(hResWnd));
    EndDialog (hResWnd, TRUE);
    hResWnd = NULL;
    SetCapture (hWnd);
    }
  }


void RsDsc::OnMouseMove (HWND hWnd,int x,int y)
  {
  if (CaptureDone) {
    POINT pt;
    pt.x = x ;
    pt.y = y ;

    switch (Type) {
      case RESTYPE_BITMAP :
        DDOnMouseMove(DDTYPE_BITMAP,&info.b.dd,&pt,hWnd,FALSE);
        break ;
      }
    }
  }

void RsDsc::OnLButtonUp (HWND hWnd,int x,int y)
  {
  if (CaptureDone) {
    POINT pt;
    pt.x = x ;
    pt.y = y ;
    switch (Type) {
      case RESTYPE_BITMAP :
        DDOnMouseMove(DDTYPE_BITMAP,&info.b.dd,&pt,hWnd,TRUE);
        break ;
      }
    ReleaseCapture ();
    DestroyWindow (hWnd);
    }
  }

extern void ScaledMetaOut (HDC hDC,HWND hWnd,HMETAFILE hMF,LPRECT r);
extern void GetMaxInfo (HDC hDC,HMETAFILE hMF,RECT FAR *r);
void RsDsc::PaintWMF (HWND hWnd,HDC hDC)
  {
  RECT r;
  GetMaxInfo (hDC,info.w.hmf,&r);
  ScaledMetaOut (hDC,hWnd,info.w.hmf,&r);
  }

void RsDsc::PaintResource (HWND hWnd,HDC hDC) 
  {
  switch (Type) {
    case RESTYPE_BITMAP :
      PaintBitmap (hWnd,hDC);
      break ;
    case RESTYPE_WMF :
      PaintWMF (hWnd,hDC);
      break ;
    }
  }

void RsDsc::Initialize(HWND hWnd)
  {
  switch (Type) {
    case RESTYPE_BITMAP :
      InitializeBitmap (hWnd);
      break ;
    case RESTYPE_WMF :
      InitializeWMF (hWnd);
      break ;
    }
  }

extern LPSTR IniFile();
inline LPSTR ResEntName()
  {
  return "ResourceView";
  }

void WriteResPos (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  int h = r.bottom - r.top  + 1;
  int w = r.right  - r.left + 1;
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (ResEntName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (ResEntName(),"_Y",outstring,IniFile());
  wsprintf (outstring,"%d",w);
  WritePrivateProfileString (ResEntName(),"_Width",outstring,IniFile());
  wsprintf (outstring,"%d",h);
  WritePrivateProfileString (ResEntName(),"_Height",outstring,IniFile());
  }

DLLExport LONG _export FAR PASCAL RsProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LPRSDSC h = NULL;
  LONG RetVal = 0L;
  switch (msg) {

    case WM_CREATE :
      {
      CreateRsData FAR *d = (CreateRsData FAR *) (((LPCREATESTRUCT)(lP))->lpCreateParams);
      DWORD Id = d->Id;
      h = LPRSDSC (GetGlobMem (sizeof(*h)));
      lstrcpy (h->RsName,d->RsName);
      h->hGmem = GetResource (Id,&h->Type,&h->DataSize);
      SetWindowLong (hWnd,0,LONG(h));
      h->Initialize(hWnd);
      }
      break ;

    case WM_GETMINMAXINFO:
      h = LPRSDSC (GetWindowLong (hWnd,0));
      if (h != NULL)
        h->OnGetMinMaxInfo (hWnd, lP);
      break;

    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      h = LPRSDSC (GetWindowLong (hWnd,0));
      HDC hDC = BeginPaint (hWnd, &ps) ;
      h->PaintResource (hWnd,hDC);
      EndPaint (hWnd, &ps) ;
      }
      break ;

    case WM_MOVE :
      WriteResPos (hWnd);
      break ;

    case WM_SIZE :
      {
      WriteResPos (hWnd);

      h = LPRSDSC (GetWindowLong (hWnd,0));
      h->OnSize (hWnd,LOWORD(lP),HIWORD(lP));
      }
      break ;
    
    case WM_LBUTTONDOWN :
      h = LPRSDSC (GetWindowLong (hWnd,0));
      h->OnLButtonDown (hWnd,(short)LOWORD(lP),(short)HIWORD(lP));
      break ;

    case WM_MOUSEMOVE :
      h = LPRSDSC (GetWindowLong (hWnd,0));
      h->OnMouseMove (hWnd,(short)LOWORD(lP),(short)HIWORD(lP));
      break ;

    case WM_LBUTTONUP :
      h = LPRSDSC (GetWindowLong (hWnd,0));
      h->OnLButtonUp (hWnd,(short)LOWORD(lP),(short)HIWORD(lP));
      break ;

    case WM_VSCROLL:
    case WM_HSCROLL:
      h = LPRSDSC (GetWindowLong (hWnd,0));
      h->OnScroll (hWnd, msg, LOWORD(lP), wP);
      break;

    case WM_DESTROY :
      h = LPRSDSC (GetWindowLong (hWnd,0));
      if (h->hGmem)
        GlobalFree (h->hGmem);
      if ((h->Type == RESTYPE_BITMAP) && (h->info.b.bmp))
        DeleteObject (h->info.b.bmp);
      if ((h->Type == RESTYPE_WMF) && (h->info.w.hmf))
        DeleteMetaFile (h->info.w.hmf);
      FreeGlobMem (h);

      break ;

    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal;
  }

void RegisterRsWindow ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = RsProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(LPRSDSC) ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = "RSWND" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

void ReadResPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetPrivateProfileInt (ResEntName(),"_X",100,IniFile());
  *y = GetPrivateProfileInt (ResEntName(),"_Y",100,IniFile());
  *w = GetPrivateProfileInt (ResEntName(),"_Width",500,IniFile());
  *h = GetPrivateProfileInt (ResEntName(),"_Height",300,IniFile());
  }

static HWND hTableWindow = NULL;

void ShowRs (HWND hParent,LPSTR TypeString,LPSTR Name,DWORD Id)
  {
  RegisterRsWindow ();
  int x,y,w,h;
  ReadResPos (&x,&y,&w,&h);
  char caption[256];
  wsprintf (caption,"%s %s",TypeString,Name);
  CreateRsData d;
  lstrcpy (d.RsName,Name);
  d.Id = Id;

  RECT rc;
  GetWindowRect (hResWnd, &rc);
  x = rc.right;
  y = rc.top;

  hTableWindow = CreateWindow (
                              "RSWND",                
                              caption,
                              WS_POPUPWINDOW | WS_CAPTION | 
                              WS_THICKFRAME | WS_CLIPCHILDREN | 
                              WS_HSCROLL | WS_VSCROLL,
                              x,y,w,h,
                              hParent,
                              NULL,                   
                              MyInstance,              
                             &d
                             ) ;
  SetWindowPos (hTableWindow,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
  UpdateWindow (hTableWindow) ;
  }

DLLExport BOOL FAR PASCAL _export ResDialog (HWND hDlg, UINT msg, WPARAM wP, LPARAM lP)
  {
  BOOL RetVal = FALSE ;
  static int rsstops[] = { 87 , 225 } ;

  switch (msg) {
    case WM_INITDIALOG :
      // Ueberschrift setzen
      hResWnd = hDlg;
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETTABSTOPS,2,LONG(LPINT(rsstops)));
      ReadResContent ();
      FillResDlg (hDlg,ID_LIST);
      RetVal = TRUE ;
      SetWindowPos (hResWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
      break ;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case ID_VIEW :
          {
          char TypeName[32];
          char RsName[64];
          DWORD Id;
          int Sel = int (SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
          if (Sel >= 0) {
            if (hTableWindow)
              DestroyWindow (hTableWindow);

            GetResourceInfo (Sel,TypeName,RsName,&Id);
            ShowRs (GetParent(hDlg),TypeName,RsName,Id);
            SetFocus (hDlg);
//            hResWnd = 0;
//            EndDialog (hDlg,TRUE);
            }
          }
          break ;
        case IDOK :
          UnloadResContent ();
          hResWnd = 0;

          if (hTableWindow)
            DestroyWindow (hTableWindow);

          EndDialog (hDlg,TRUE);
          break ;
        case ID_LIST :
          WORD wNotify;
#ifdef WIN32
          wNotify = HIWORD(wP);
#else
          wNotify = HIWORD(lP);
#endif          
          if (CRACKER_wNotify == LBN_SELCHANGE)
            SendMessage (hDlg,WM_COMMAND,ID_VIEW,0L);
          break ;
        }
      }
      break ;
    }
  return RetVal;
  }

void ShowResources (HWND hWnd)
  {
  if (hResWnd)
    ShowWindow (hResWnd,SW_SHOW);
  else {
    DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(ResDialog),MyInstance));
    DialogBox (MyInstance,"Resource",hWnd,dlgProc);
    FreeProcInstance (dlgProc);
    }
  }
