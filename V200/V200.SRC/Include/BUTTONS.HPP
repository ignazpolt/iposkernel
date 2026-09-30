////////////////////////////////////////////////////////////////////
//  Button - Klasse (fuer die Kontrollelemente in DDSLIST)
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/buttons.hpv   1.9   16 Jun 2000 17:13:12   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/buttons.hpv  $
// 
//    Rev 1.9   16 Jun 2000 17:13:12   Gerhold
// Beim FormTool werden jetzt Extradaten mitgespeichert
// (wegen des Kontextes im ExcuteProc)
// 
//    Rev 1.8   24 Mar 2000 18:02:52   Wolfgang
// 1.) Erster Versuch eines Mousewheel-Supports.
// 
//    Rev 1.7   25 Mar 1996 10:49:04   GERHOLD
// RemoveButtonTimer
// 
//    Rev 1.6   18 Mar 1996 16:39:24   GERHOLD
// Einfuehrung von Basisklassen fuer Listen und Knoepfe
// 
//    Rev 1.5   02 Feb 1996 11:01:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   14 Sep 1995 10:06:16   GERHOLD
// 
//    Rev 1.3   12 Jul 1994 14:47:10   GERHOLD
// Connectionhandling wurde eingefuehrt!
// 
//    Rev 1.2   05 Jul 1994 15:48:12   GERHOLD
// Initial Code
//

#define BUTTON_INCLUDED

#ifndef FRECT_DEFINED
  struct FAR fRECT {
    int left,top,right,bottom;
    };
  #define FRECT_DEFINED
#endif


typedef VOID (WINAPI * BTNPROC) (LPVOID c, DWORD CmdOffs, LPVOID par);



//***************************************************************************
//
// Basisklasse fuer Knoepfe
//
//***************************************************************************
class FAR ButtonBase {
 public:
  int   x, y, w, h;
  HWND  hWndParent;
//  HDC   CapDC;
//  HDC   MemDC;
  BOOL  Capturing;
  BOOL  IsPressed;
  BOOL  HasTimer;
  fRECT ButtonRect;
  BOOL  Visible;

  DWORD   ProcID;
  BTNPROC BtnProc;

  LPVOID  PrivData;
  LPVOID  Data;

  DLLExport _export WINAPI ButtonBase (LPVOID privdata, int privsize,
                                       HWND RefWnd, int px, int py, int pw, int ph);
  virtual /*DLLExport _export WINAPI*/ ~ButtonBase ();

  virtual BOOL OnLButtonDown (LPPOINT pt);
  virtual BOOL OnMouseMove (LPPOINT pt);
  virtual BOOL OnLButtonUp (LPPOINT pt);
  virtual void GetRect ();
  virtual int  GetWidth () { return ButtonRect.right-ButtonRect.left; };
  virtual int  GetHeight () { return ButtonRect.bottom-ButtonRect.top; };
  virtual BOOL HitTest (LPPOINT pt);
  virtual void SetXYPos (int px, int py) { OffsetRect(LPRECT (&ButtonRect), px-x, py-y); x = px; y = py; };
 
  virtual void PaintButton (BOOL State);
  virtual void PaintState ();

          void PressIn();
          void PressOut();
          void SetButtonTimer (HWND hWnd, UINT id, UINT interval);
          void RemoveButtonTimer (HWND hWnd, UINT id);
          void AllowTimer (void);
  
  DLLExport void _export WINAPI SetButtonProc (BTNPROC btnproc, DWORD procid, LPVOID par);
          void CallButtonProc ();
  
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

typedef ButtonBase FAR* LPBUTTONBASE;

//***************************************************************************
//
// Knopf mit einem Bild
//
//***************************************************************************
class FAR BitButton : public ButtonBase {
 public:
  int   AnzButtons;
  int   AnzCol, AnzRow;
  int   BmpWidth, BmpHeight;
  int   XIndex, YIndex;
  LPSTR szBmpName;
  HBITMAP hBmp;
  
  DLLExport _export WINAPI BitButton (LPVOID privdata, int privsize,
                                      HWND RefWnd, int px, int py, int pw, int ph, 
                                      HBITMAP hBitmap, int Col, int Row, 
                                      int nIndX, int nIndY);
  virtual /*DLLExport _export WINAPI*/ ~BitButton ()  { };

  virtual void           GetRect ();
          void           SetBmpIndex (int nXIndex, int nYIndex = 1) 
                           { 
                           XIndex = nXIndex; 
                           YIndex = nYIndex; 
                           };

  virtual void           PaintButton (BOOL State);
  };

//***************************************************************************
//
// Knopf mit einem Text
//
//***************************************************************************
class FAR TextButton : public ButtonBase {
 public:

#ifdef CFIELD_INCLUDED
  cField FAR *field;
#else
  LPVOID field;
#endif

  int   TextFormat;
  
  DLLExport _export WINAPI TextButton (LPVOID privdata, int privsize,
                                       HWND RefWnd, int px, int py, int pw, int ph, 
                                       LPSTR Text, int Format);
  virtual /*DLLExport _export WINAPI*/ ~TextButton ()  { delete field; };

  virtual void PaintButton (BOOL State);
  };

//***************************************************************************
//
// ein statisches Textfeld
//
//***************************************************************************
/*
class FAR StaticField : public TextButton {

  DLLExport _export WINAPI StaticField (HWND RefWnd, int px, int py, int pw, int ph, LPSTR Text, int Format);

  virtual void PaintState ()  { PaintButton (FALSE); };
  virtual void PaintButton (BOOL State);
  };
*/

typedef BitButton FAR *LPBITBUTTON;
typedef TextButton FAR *LPTEXTBUTTON;


class FAR BtnList;
class FAR SingleList;
typedef BtnList    FAR *LPBTNLIST;
typedef SingleList FAR *LPSINGLELIST;


struct ListItem;
typedef ListItem FAR *LPLISTITEM;

struct FAR ListItem {
  LPLISTITEM Next;
  LPBUTTONBASE Item;
  
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };


#define BTN_BOTTOM_POS      0
#define BTN_RIGHT_POS       1
#define BTN_LEFT_POS        2
#define BTN_TOP_POS         3
             
#define BTNSTATE_INIT       0
#define BTNSTATE_DOWN       1
#define BTNSTATE_DOWNOUT    2

#define BTN_IND_HOME            1
#define BTN_IND_PREVPAGE        2
#define BTN_IND_PREV            3
#define BTN_IND_NEXT            4
#define BTN_IND_NEXTPAGE        5
#define BTN_IND_END             6

class FAR BtnList {
 public:
  LPLISTITEM First;
  LPLISTITEM ActiveItem;
  WORD State;
  HWND hWndParent;
  UINT ButtonPos;

  DLLExport _export WINAPI BtnList (HWND hWnd);
  virtual DLLExport _export WINAPI ~BtnList ();
  
  DLLExport void _export WINAPI Insert (LPBUTTONBASE lpItem);
  virtual LPLISTITEM HitTest (LPPOINT pt);
          UINT GetButtonPos ()  { return ButtonPos; };
  DLLExport void _export WINAPI Paint (HDC hDC);
          int GetHeight ();
          int GetWidth ();
  virtual void ArrangeButtons (UINT Position, LPRECT rc)   { };

  virtual BOOL OnLButtonDown (HWND hWnd, LPPOINT pt);
  virtual BOOL OnLButtonDblClk (HWND hWnd, LPPOINT pt);
  virtual BOOL OnMouseMove (HWND hWnd, LPPOINT pt);
  virtual BOOL OnLButtonUp (HWND hWnd, LPPOINT pt);
  virtual void OnTimer (HWND hWnd);
  virtual void OnMouseWheel (HWND hWnd, LPPOINT pt, WORD fwKeys, short zDelta);

  DLLExport LONG _export WINAPI CheckMsg (HWND hWnd, unsigned msg, WPARAM wP, LPARAM lP, BOOL FAR *done);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

        
class FAR SingleList : public BtnList {
 public:
  LONG wheelDelta;
  SingleList (HWND hWnd) : BtnList (hWnd) { } ;

  virtual BOOL OnLButtonDown (HWND hWnd, LPPOINT pt);
  virtual BOOL OnLButtonDblClk (HWND hWnd, LPPOINT pt);
  virtual BOOL OnMouseMove (HWND hWnd, LPPOINT pt);
  virtual BOOL OnLButtonUp (HWND hWnd, LPPOINT pt);
  virtual void OnTimer (HWND hWnd);
  virtual void OnMouseWheel (HWND hWnd, LPPOINT pt, WORD fwKeys, short zDelta);
  
  virtual LPLISTITEM HitTest (LPPOINT pt);
  virtual void ArrangeButtons (UINT Position, LPRECT rc);

          void PaintListButtons (HDC hDC, LPRECT rcList);

//  virtual LONG CheckMsg (HWND hWnd, unsigned msg, WPARAM wP, LPARAM lP, BOOL FAR *done);
  };

