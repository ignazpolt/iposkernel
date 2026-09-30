// Deklarationen fuer die Knoepfe und die Toolbar-Nachrichten
//-------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/include/rev/msdntbi.hpv   1.7   05 Oct 1998 11:23:54   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/msdntbi.hpv  $
// 
//    Rev 1.7   05 Oct 1998 11:23:54   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.6   17 Nov 1997 08:13:12   Gerhold
// 32 Bit
// 
//    Rev 1.5   02 Feb 1996 11:01:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   16 Feb 1995 12:44:34   GERHOLD
// 
//    Rev 1.3   24 Jan 1995 10:01:56   GERHOLD
// 
//    Rev 1.2   18 Jan 1995 12:13:54   GERHOLD
// 
//    Rev 1.1   09 Jan 1995 14:58:58   GERHOLD
// 
//    Rev 1.0   02 Jan 1995 10:12:00   GERHOLD
// Initial revision.
//-------------------------------------------------------------------------
#ifdef WIN32
  #define GETWINDOWID(hwnd)       GetWindowLong(hwnd, GWL_ID)
#else
  #define GETWINDOWID(hwnd)       GetWindowWord(hwnd, GWW_ID)
#endif

extern HINSTANCE hLibInst;

struct FAR TBBMINFO {        /* info for recreating the bitmaps */
  int       nButtons;
  HINSTANCE hInst;
  WORD      wID;
  HBITMAP   hbm;
  };
typedef TBBMINFO FAR *LPTBBMINF ;

class FAR TBBmInfo {
 public:
  
  int       nButtons;
  HINSTANCE hInst;
  WORD      wID;
  HBITMAP   hbm;
  TBBmInfo FAR* Next;

  TBBmInfo (HINSTANCE, WORD, int, HBITMAP);
  ~TBBmInfo ();
  };
typedef TBBmInfo FAR *LPTBBMINFO ;



class FAR TBButton {
 public:
  int  iBitmap;        // index into bitmap of this button's picture
  int  idCommand;      // WM_COMMAND menu ID that this button sends
  BYTE fsState;        // button's state
  BYTE fsStyle;        // button's style
  DWORD dwData;
  int   iString;

  int  x, y, dx, dy;

  LPTOOLBAR  Parent;

  TBButton FAR* Prev;
  TBButton FAR* Next;
          
  TBButton (LPTBBUTTON BtnStruct, LPTOOLBAR parent);

  void CreateMask(int xoffset, int yoffset, int dx, int dy);
  void DrawBlankButton(HDC hdc, int x, int y, int dx, int dy, WORD state);
  void DrawButton(HDC hdc);
  void InvalidateButton (HWND hwnd);
  BOOL GetItemRect (HWND hWnd, LPRECT lpRect);
  BOOL HitTest (int xPos, int yPos);
  };
typedef TBButton FAR* LPTBBUTT;


#ifndef FRECT_DEFINED
  struct FAR fRECT {
    int left,top,right,bottom;
    };
  #define FRECT_DEFINED
#endif    

#ifndef fPOINT_DEFINED
  struct FAR fPOINT {
    int x, y;
    };
  #define fPOINT_DEFINED
#endif    


class FAR ToolBar {
 public:
  int        Result;

  HWND       hWnd;
  HWND       hParent;
  HWND       hWndDock;
  HWND       hWndCommand;  // an dieses Fenster werden die Kommandos geschickt

  char       Title[20];

  LPTBBUTT   pCaptureButton;
  LPTBBUTT   FirstButton; 
  LPTBBMINFO FirstBitmap;
  LPTBBMINFO SelectedBitmap;

  HBRUSH     hSizeInvBrush;
  HBRUSH     hbrDither;

  HDC        hdcMono;
  HBITMAP    hbmMono;
  HBITMAP    hbmDefault;
  HDC        hdcGlyphs;           // globals for fast drawing
  BOOL       ParentIsPopUp;

  fRECT      rcChild;
  fRECT      rcPopup;
  fRECT      rcMove;
  fPOINT     ptSave;
  BOOL       bMoveToolbar;
  
  LPTOOLBAR  Next;

  ToolBar (HWND hWnd, HWND hWndParent, LPSTR WindowName);
  ~ToolBar ();

  BOOL CreateDitherBrush(BOOL bIgnoreCount);
  BOOL FreeDitherBrush(void);
  BOOL InitGlobalObjects (void);  
  void FreeGlobalObjects ();
  void ToolbarPaint ();
  void DrawButton(HDC hdc, int x, int y, int dx, int dy, LPTBBUTTON ptButton);
  int  AddBitmap (int nButtons, HINSTANCE hBMInst, WORD wBMID);
  BOOL InsertButtons(UINT uWhere, UINT uButtons, LPTBBUTTON lpButtons);
  void MakeGroupConsistant(HWND hWnd, int idCommand);
  void SizeOnParent (HWND hParent, int x, int y, int cx, int cy);
  BOOL OnLButtonDown (POINT pt);
  BOOL OnLButtonUp (POINT pt);
  BOOL OnMouseMove (POINT pt);
  BOOL OnSetState (WPARAM wParam, LPARAM lParam);
  LONG OnGetState (WPARAM wParam);
  BOOL OnTBSetState (UINT wMsg, WPARAM wParam, LPARAM lParam);
  LONG OnTBGetState (UINT wMsg, WPARAM wParam);
  BOOL DeleteButton (WPARAM wParam);
  BOOL GetButton (WPARAM wParam, LPARAM lParam);
  BOOL ButtonCount ();
  BOOL CommandToIndex (WPARAM wParam);
  BOOL OnGetItemRect (WPARAM wParam, LPARAM lParam);
  int  PositionFromID (int id);
  LPTBBUTT ButtonFromID (int id);
  HBITMAP SelectBM (HDC hDC, int nButton);
  void GetSysColors();
  LPTBBUTT TBHitTest(int xPos, int yPos);
  void ChangeState (BOOL bFromDblClk);
/*
  LPVOID operator new (size_t size)
    { 
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
*/  
  };


extern void BuildButtonTemplates(void);
