//-----------------------------------------------------------------------------
// Implementation einer Statuszeile
//-----------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/statbar/rev/statbar.cpv   1.15   05 Oct 1998 11:51:18   Gerhold  $
//  $Log:   P:/marille/clinicum/statbar/rev/statbar.cpv  $
// 
//    Rev 1.15   05 Oct 1998 11:51:18   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.14   11 Apr 1997 11:42:10   Gerhold
// Vorder- und Hintergrundfarbe einstellbar
// 
//    Rev 1.13   07 Apr 1997 19:23:00   gerhold
// On_Size ... if (State == SIZE_MINIMIZED) berechnet die Groesse nicht neu
// 
//    Rev 1.12   17 Jun 1996 17:38:42   GERHOLD
// 
//    Rev 1.11   16 Feb 1996 15:18:38   GERHOLD
// Einsprungspunkte fuer die DLL in WIN32
// 
//    Rev 1.10   02 Feb 1996 10:51:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   23 Aug 1995 11:07:08   GERHOLD
// 
//    Rev 1.8   31 Mar 1995 10:42:38   GERHOLD
// 
//    Rev 1.7   20 Mar 1995 16:30:48   hannes
// 
//    Rev 1.6   30 Jan 1995 15:05:54   GERHOLD
// 
//    Rev 1.5   15 Dec 1994 18:25:18   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.4   15 Dec 1994 11:39:26   HANNES
// 
//    Rev 1.3   07 Nov 1994 17:31:34   GERHOLD
// 
//    Rev 1.2   07 Nov 1994 14:30:30   GERHOLD
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>

#define NO_MEMORY_CHECK    // kein GGlobalAlloc,...
#include "dds32.h"

#include "statbar.hpp"
#include "globmem.h"
#include "toolbar.hpp"


//RECT    StatRecSizeAdv;
HFONT   hFontStatbar;
int     StatbarHeight;

HINSTANCE hStatusInst;

class FAR StatusField;
typedef StatusField FAR *LPSF;  


class FAR StatusField {
 public:
  int dyBorder;
  int RightPos;
  int Index;
  int Style;
  COLORREF foreColor;    // Farbe des Feld-Textes
  COLORREF backColor;    // Hintergrundfarbe des Feldes
  fRECT rcField;
  LPSF Next;
  
  char FieldText[256];

  StatusField (int FieldPos, int FieldIndex,HWND hWnd);
  void SetFieldRect (LPRECT rc);
  void SetFieldColor (COLORREF crFore, COLORREF crBack)
    { 
    if (crFore != 0xFFFFFFFF) foreColor = crFore; 
    if (crBack != 0xFFFFFFFF) backColor = crBack; 
    }
  void ResetFieldColor ()
    { 
    foreColor = GetSysColor(COLOR_BTNTEXT);
    backColor = GetSysColor(COLOR_BTNFACE);
    }
  void SetText (int FieldStyle, LPSTR szText);
  void WriteText (HDC hDC);
  void Paint (HDC hDC);

  LPVOID operator new (size_t size)
    { return GetGlobMem(size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
  
#define GWL_LPSF  0L

LPSF FirstField (HWND hWnd)
  {
  return LPSF(GetWindowLong (hWnd,GWL_LPSF));
  }

void SetFirstField (HWND hWnd,LPSF ptr)
  {
  SetWindowLong (hWnd,GWL_LPSF,LONG(ptr));
  }

void InsertToFieldList (LPSF lpsf,HWND hWnd)
  {
  if (FirstField(hWnd) == NULL) {
    SetFirstField (hWnd,lpsf);
    FirstField(hWnd)->Next = NULL;
    }
  else {
    for (LPSF s = FirstField(hWnd); s->Next != NULL; s = s->Next);
    s->Next = lpsf;
    lpsf->Next = NULL;
    }
  }


StatusField::StatusField (int FieldPos, int FieldIndex,HWND hWnd)
  {
  RightPos = FieldPos;
  Index = FieldIndex;
  FieldText[0] = '\0';
  SetRectEmpty (LPRECT(&rcField));
  ResetFieldColor ();

  InsertToFieldList (this,hWnd);
  }
  
void StatusField::SetText (int FieldStyle, LPSTR szText)
  {
  Style = FieldStyle << 8;
  lstrcpy (FieldText, szText);
  }

void StatusField::WriteText (HDC hDC)
  {
  HFONT OldFont = (HFONT)SelectObject (hDC, hFontStatbar);
  COLORREF OldColor = SetTextColor (hDC, foreColor);
  COLORREF OldBack = SetBkColor (hDC, backColor);

  ExtTextOut(hDC, rcField.left+5, rcField.top,
             ETO_OPAQUE | ETO_CLIPPED, LPRECT(&rcField), (LPSTR)FieldText,
             lstrlen((LPSTR)FieldText), NULL);
  SetBkColor (hDC, OldBack);
  SetTextColor (hDC, OldColor);
  SelectObject (hDC, OldFont);
  }


void StatusField::SetFieldRect (LPRECT rc)
  {
  CopyRect (LPRECT(&rcField), rc);
  }

void StatusField::Paint (HDC hDC)
  {
  RECT rcEdge;
  
  CopyRect (&rcEdge, LPRECT(&rcField));
  InflateRect (&rcEdge, 1, 1);

  if (Style & SBT_NOBORDERS) {
    COLORREF OldBack = SetBkColor(hDC, backColor);
    ExtTextOut (hDC, rcEdge.left, rcEdge.top, ETO_OPAQUE, &rcEdge, NULL, 0, NULL);
    SetBkColor (hDC, OldBack);
    WriteText (hDC);
    }
  else {
    WriteText (hDC);
    MyDrawEdge (hDC, LPRECT(&rcEdge), MY_EDGE_GROUPBOX, -1);
    }
  }

static HFONT __hfnt;
static int fntUseCount;
static char szHelv[] = "Helv";
HFONT GetStatbarFont (int Fntheight)
  {
  if (__hfnt == 0) {
    __hfnt = CreateFont(Fntheight, 0, 0, 0, 400, 0, 0, 0,
          ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
          DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szHelv);
    }
  fntUseCount ++ ;
  return __hfnt;
  }

void DelStatbarFont ()
  {
  fntUseCount -- ;
  if (fntUseCount == 0) {
    DeleteObject (__hfnt);
    __hfnt = 0;
    }
  }

void InitStatBar (HWND hWnd)
  {
  HDC           hDC;
  TEXTMETRIC    tm;
  int           Fntheight;                  // Height of the font

  int dyBorder = GetSystemMetrics(SM_CYBORDER);

  hDC = GetDC(NULL);
  Fntheight = MulDiv(-10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
  hFontStatbar = GetStatbarFont (Fntheight);
  SelectObject(hDC, hFontStatbar);

  GetTextMetrics(hDC, &tm);
  ReleaseDC(NULL, hDC);

  StatbarHeight = tm.tmHeight + tm.tmExternalLeading + (9*dyBorder);
/*
  GetClientRect(GetParent(hWnd), &StatRecSizeAdv);
  StatRecSizeAdv.top = StatRecSizeAdv.bottom-StatbarHeight-1;

  MoveWindow (hWnd, StatRecSizeAdv.left, StatRecSizeAdv.top,
                    StatRecSizeAdv.right-StatRecSizeAdv.left,
                    StatRecSizeAdv.bottom-StatRecSizeAdv.top,
                    TRUE);
*/
  }


void StatBar_OnCreate(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
  {
  InitStatBar (hwnd);
  }

void Statbar_OnSetText (HWND hWnd, WPARAM wParam, LPARAM lParam)
  {
  RECT rcEdge;

  for (LPSF lpsf = FirstField(hWnd); lpsf != NULL; lpsf = lpsf->Next)
    if (lpsf->Index == int(LOBYTE(wParam))) {
      lpsf->SetText (HIBYTE(wParam), LPSTR(lParam));
      CopyRect (&rcEdge, LPRECT(&lpsf->rcField));
//      InflateRect (&rcEdge, -1, -1);
      InvalidateRect (hWnd, &rcEdge, FALSE);
      UpdateWindow (hWnd);
      }
  }

void StatBar_OnDestroy(HWND hwnd)
  {
  LPSF n;
  LPSF s = FirstField(hwnd);
  for ( ; s != NULL ; ) {
    n = s->Next;
    delete s;
    s = n;
    }

  DelStatbarFont ();
  }

void PaintStatbar (HWND hwnd, HDC hDC)
  {
  RECT rc;
  GetClientRect(hwnd, &rc);

  COLORREF OldBack = SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  rc.bottom = rc.top++;
  OldBack = SetBkColor (hDC, 0);
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  rc.top++;
  rc.bottom++;
  OldBack = SetBkColor (hDC, RGB(0xFF, 0xFF, 0xFF));
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  GetClientRect(hwnd, &rc);
  rc.top = rc.bottom--;
  OldBack = SetBkColor (hDC, RGB(0x80, 0x80, 0x80));
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  
  for (LPSF s = FirstField(hwnd); s != NULL; s = s->Next)
    s->Paint (hDC);
  }

static BOOL SizeDone;
void StatBar_OnPaint(HWND hwnd)
  {
  PAINTSTRUCT ps;
  HDC hdc;

  hdc = BeginPaint(hwnd, &ps);

  if (SizeDone)
    PaintStatbar(hwnd, hdc);

  EndPaint(hwnd, &ps);
  }

static int oldcx = 0, oldcy = 0;
static BOOL bSizeChanged = FALSE;
void StatBar_OnSize (HWND hwnd, WORD state, int cx, int cy)
  {
  if (FirstField(hwnd) == NULL)
    return;

  SizeDone = TRUE ;
  RECT rc, rcStat;
  
  GetClientRect (GetParent(hwnd), &rc);

  GetClientRect(hwnd, &rcStat);
//  if (IsRectEmpty(&rcStat)) {
//    MoveWindow (hwnd, rc.left, rc.bottom-StatbarHeight, rc.right-rc.left, StatbarHeight, TRUE);
//    }

  if (state == SIZE_MINIMIZED) {
    bSizeChanged = TRUE;
    return;
    }
    
  int Delta = 0;
  if ((rcStat.right - rcStat.left) > 0)
    Delta = (rcStat.right-rcStat.left) - cx ;

//  if (Delta != 0) {
    LPSF s = FirstField(hwnd);
    if (s != NULL) {
      for ( ; s != NULL; s = s->Next)
        s->RightPos -= Delta; 
      
      for (s = FirstField(hwnd) ; s != NULL; s = s->Next) {
        rc.right = s->RightPos;
        if (s->Next != NULL)
          rc.left = s->Next->RightPos+8;
        else
          rc.left = 8;
      
        rc.top = 5;
        rc.bottom = StatbarHeight-4;
        s->SetFieldRect (&rc);
        }
      }
//    }  
      
//    InvalidateRect (hwnd, NULL, FALSE);

  if (!bSizeChanged) {
    bSizeChanged = TRUE;
    GetClientRect (GetParent(hwnd), &rc);
    MoveWindow (hwnd, rc.left, rc.bottom-StatbarHeight, rc.right-rc.left, StatbarHeight, TRUE);
    }
  else
    UpdateWindow (hwnd);  
    
  bSizeChanged = FALSE;
  }



DLLExport LONG _export FAR PASCAL StatBar_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
  LONG res = 0L;
  switch (msg) {
    case WM_CREATE : 
      StatBar_OnCreate (hWnd, LPCREATESTRUCT(lParam));
      return TRUE;
      break;
    case WM_PAINT :
      StatBar_OnPaint (hWnd);
      break;
    case WM_DESTROY :
      StatBar_OnDestroy (hWnd);
      break;
    case WM_SIZE : 
      StatBar_OnSize (hWnd, WORD(wParam), (int)LOWORD(lParam), (int)HIWORD(lParam));
      break;
    case WM_ERASEBKGND:
      res = 1L;
      break;

    case SB_SETTEXT :
      Statbar_OnSetText (hWnd, wParam, lParam);
      break;
    case SB_SETPARTS :
      {
      for (int i = 0; i < int(wParam); i++)
        new StatusField (((int FAR *)lParam)[i], i,hWnd);
      }
      break;
    case SB_GETHEIGHT :
      return LONG(StatbarHeight);
      break;

    default:
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }

  return res;
  }


LPSTR szStatBarClassName;
DLLExport BOOL _export FAR PASCAL StatBar_Register(HINSTANCE hInstance)
  {
  WNDCLASS cls;
  static BOOL IsRegistered;

  if (!IsRegistered) {
    cls.hCursor         = LoadCursor(NULL, IDC_ARROW);
    cls.hIcon           = 0;
    cls.lpszMenuName    = NULL;
    cls.hInstance       = hInstance;
    cls.lpszClassName   = szStatBarClassName;
    cls.hbrBackground   = HBRUSH(COLOR_BTNFACE + 1);
    cls.lpfnWndProc     = (WNDPROC)StatBar_WndProc;
    cls.style           = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    cls.cbWndExtra      = sizeof(LPVOID);
    cls.cbClsExtra      = 0;
  
    IsRegistered = TRUE ;
    if (!RegisterClass(&cls))
      return 0;
    }
    
  return 1;  
  }

DLLExport HWND _export FAR PASCAL CreateStatusbar (DWORD Style, LPSTR StartText, HWND hParent, int wID)
  {
  HWND hwndstatusbar;

  StatBar_Register (hStatusInst);

  if (Style & WS_BORDER)
    Style &= ~WS_BORDER;
  hwndstatusbar = CreateWindowEx(0L, szStatBarClassName, NULL, WS_CHILD | Style,
                                 0, 0, 0, 0, hParent, (HMENU)wID, hStatusInst, NULL);

  SendMessage (hwndstatusbar, SB_SETTEXT, 0, LPARAM(StartText));
  return hwndstatusbar;
  }

DLLExport void _export FAR PASCAL STATBAR_SetClassNames (LPSTR StatBarClassName)
  {
  szStatBarClassName = StatBarClassName;
  }

DLLExport void _export FAR PASCAL SetFieldColor (HWND hWnd, int FieldNum, COLORREF crFore, COLORREF crBack)
  {
  int i = 0;
  for (LPSF s = FirstField(hWnd); (s != NULL) && (i < FieldNum); s = s->Next, i++);

  if ((i == FieldNum) && (s != NULL))
    s->SetFieldColor (crFore, crBack);
  }

DLLExport void _export FAR PASCAL ResetFieldColor (HWND hWnd, int FieldNum)
  {
  int i = 0;
  for (LPSF s = FirstField(hWnd); (s != NULL) && (i < FieldNum); s = s->Next, i++);

  if ((i == FieldNum) && (s != NULL))
    s->ResetFieldColor ();
  }


//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
  {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hStatusInst = hModule;
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
extern "C" {
int WINAPI WEP (int nShutdownFlag)
  {
  return 1 ;
  }

int WINAPI LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  hStatusInst = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1 ;
  }
}

#endif

