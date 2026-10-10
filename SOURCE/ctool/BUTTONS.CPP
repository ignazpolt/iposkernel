////////////////////////////////////////////////////////////////////
//  Button - Klasse (fuer die Kontrollelemente in DDSLIST)
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ctool/rev/buttons.cpv   1.19   16 Jun 2000 17:10:10   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/buttons.cpv  $
// 
//    Rev 1.19   16 Jun 2000 17:10:10   Gerhold
// Beim FormTool werden jetzt Extradaten mitgespeichert
// (wegen des Kontextes im ExcuteProc)
// 
//    Rev 1.18   06 Apr 2000 13:18:50   Wolfgang
// 1.) Mousewheel-Support komplettiert.
// 
//    Rev 1.17   24 Mar 2000 18:03:00   Wolfgang
// 1.) Erster Versuch eines Mousewheel-Supports.
// 
//    Rev 1.16   05 Oct 1998 11:06:14   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.15   25 Jul 1996 19:55:32   GERHOLD
// Mausposition 32 Bit
// 
//    Rev 1.14   25 Mar 1996 11:54:00   GERHOLD
// aller guten Dinge sind drei (fuer den dummen Gerhold)
// LButtonDblClk ueberprueft ob der Doppelklick nur in der Knopfleiste war!
// 
//    Rev 1.13   25 Mar 1996 11:31:56   GERHOLD
// In CheckMsg (DBLCLK) zusaetzliche Abfrage ob ActiveItem != NULL
// *done wird zwar auf TRUE gesetzt, aber der Status bleibt BTNSTATE_INIT
// 
//    Rev 1.12   25 Mar 1996 10:47:58   GERHOLD
// Der Doppelcklick wir nicht mehr an die DDSLIST weitergegeben.
// 
//    Rev 1.11   24 Mar 1996 12:10:06   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.10   18 Mar 1996 16:36:08   GERHOLD
// Dramatische Aenderungen!!!
// Basisklassen fuer Knoepfe und Listen erzeugt (jetzt ist es so richtig schoen
// objektorientiert). Bravo Gerhold
// 
//    Rev 1.9   02 Feb 1996 10:41:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   12 Oct 1995 11:44:06   GERHOLD
// Die graue Flaeche zwischen den Knoepfen wird bei WM_LBUTTONDOWN zu PgUp,
// PgDown umfunktioniert.
// 
//    Rev 1.7   14 Sep 1995 10:05:28   GERHOLD
// Wenn die Listbox zu klein ist, dann werden nicht mehr alle Knoepfe gezeichnet
// 
//    Rev 1.6   26 Jun 1995 10:14:34   GERHOLD
// ein bisschen effizienter zeichnen
// 
//    Rev 1.5   22 Sep 1994 16:08:00   GERHOLD
// 
//    Rev 1.4   05 Sep 1994 13:16:46   GERHOLD
// Reihenfolge der Knoepfe geaendert
// 
//    Rev 1.3   10 Aug 1994 12:12:40   GERHOLD
// Knoepfe anders angeordnet
// 
//    Rev 1.2   12 Jul 1994 14:43:08   GERHOLD
// Kn”pfe in der DDSList an die Fenstergr”áe und den Header angepaát
// 
//    Rev 1.1   05 Jul 1994 15:32:32   GERHOLD
// Initial Code
//

// Damit die Mouse-Wheel Konstanten in WINUSER.H (ueber WINDOWS.H) definiert werden:
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include "dds32.h"
#include "globmem.h"

#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif

#include "cfield.hpp"
#include "buttons.hpp"
#include "toolbar.hpp"

extern HINSTANCE hLibInst;

#define   XBORDER  3
#define   YBORDER  3

UINT wheelScrollLines = 0;

DLLExport _export WINAPI ButtonBase::ButtonBase (LPVOID privdata, int privsize,
                                                 HWND RefWnd, int px, int py, 
                                                 int pw = 0, int ph = 0)
  {
  IsPressed = FALSE;
  Capturing = FALSE;
  HasTimer = FALSE;
  Visible = TRUE;

  hWndParent = RefWnd;

  x = px;
  y = py;
  w = pw;
  h = ph;

  BtnProc = NULL;
  ProcID = 0;

  if (privdata) {
    PrivData = GetGlobMem (privsize);
    lmemcpy (PrivData, privdata, privsize);
    }
  }

inline void ButtonBase::GetRect ()
  {
  SetRect (LPRECT(&ButtonRect), x, y, x+w, y+h);  
  }


/*--------------------------------------------------------------------*\
* DESTRUCTOR:  ButtonBase                                              *
*                                                                     *
\*--------------------------------------------------------------------*/
ButtonBase::~ButtonBase ()                                // DESTRUCTOR
  {
  if (PrivData) {
    (* FreePrivData) (PrivData);
    FreeGlobMem (PrivData);
    }
//  if (Capturing) {
//    if (MemDC != 0)
//      DeleteDC (MemDC);
//    ReleaseCapture ();
//    }
  }

/*--------------------------------------------------------------------*\
* member function:  HitTest                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
inline BOOL ButtonBase::HitTest (LPPOINT pt)             
  {
  return (PtInRect(LPRECT(&ButtonRect), *pt) && Visible);
  }



/*--------------------------------------------------------------------*\
* member function:  PaintState                                         *
*                                                                      *
\*--------------------------------------------------------------------*/
inline void ButtonBase::PaintState ()
  {
  PaintButton (IsPressed);
  }



/*--------------------------------------------------------------------*\
* member function:  PaintButton                                        *
*                                                                      *
\*--------------------------------------------------------------------*/
void ButtonBase::PaintButton (BOOL State)
  {
  HBRUSH   OldBrush;
  HPEN     OldPen;

  HDC hDC = GetDC(hWndParent);              // DC holen

  if (State) {
    OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));  

    Rectangle (hDC, ButtonRect.left+1, ButtonRect.top+1, 
                    ButtonRect.right, ButtonRect.bottom);

    SelectObject (hDC, OldBrush);
    DeleteObject (SelectObject(hDC, OldPen));
    }
  else {
    OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
    Rectangle (hDC, ButtonRect.left+1, ButtonRect.top+1, 
                    ButtonRect.right-1, ButtonRect.bottom-1);

    MoveToEx (hDC, ButtonRect.left+2, ButtonRect.bottom-3, NULL);
    LineTo (hDC, ButtonRect.right-3, ButtonRect.bottom-3);
    LineTo (hDC, ButtonRect.right-3, ButtonRect.top+1);

    SelectObject (hDC, OldBrush);
    DeleteObject (SelectObject(hDC, OldPen));

    OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    MoveToEx (hDC, ButtonRect.left+1, ButtonRect.bottom-3, NULL);
    LineTo (hDC, ButtonRect.left+1, ButtonRect.top+1);
    LineTo (hDC, ButtonRect.right-2, ButtonRect.top+1);
    SelectObject (hDC, OldPen);
    }
    

  // schwarzen Rahmen um den Button zeichnen 
  OldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
  OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));

  Rectangle (hDC, ButtonRect.left, ButtonRect.top, 
                  ButtonRect.right, ButtonRect.bottom);

  SelectObject (hDC, OldPen);
  SelectObject (hDC, OldBrush);

  ReleaseDC (hWndParent, hDC);
  }


/*--------------------------------------------------------------------*\
* member function:  PressIn                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
inline void ButtonBase::PressIn ()
  {
  if (!IsPressed) {
    IsPressed = TRUE ;
    PaintState ();
    }
  }

/*--------------------------------------------------------------------*\
* member function:  PressOut                                           *
*                                                                      *
\*--------------------------------------------------------------------*/
inline void ButtonBase::PressOut ()
  {
  if (IsPressed) {
    IsPressed = FALSE ;
    PaintState ();
    }
  }

/*--------------------------------------------------------------------*\
* member function:  BeginCapture                                       *
*                                                                      *
\*--------------------------------------------------------------------*/
inline BOOL ButtonBase::OnLButtonDown (LPPOINT pt)
  {
  IsPressed = FALSE;
  Capturing = TRUE;
  SetCapture (hWndParent);                // dieses Fenster bekommt alle Maus-Events
  BOOL res = HitTest(pt); 
  if (res)
    PressIn ();
    
  return res;
  }

/*--------------------------------------------------------------------*\
* member function:  ContinueCapture                                    *
*                                                                      *
* Bewegen der Maus bei gedrücktem linken Mausknopf                     *
\*--------------------------------------------------------------------*/
inline BOOL ButtonBase::OnMouseMove (LPPOINT pt)
  {
  if (HitTest(pt)) {
    PressIn();
    return TRUE;
    }
  else {
    PressOut();
    return FALSE;
    }
  }


/*--------------------------------------------------------------------*\
* member function:  OnLButtonUp                                        *
*                                                                      *
* Diese Routine loest auch die Knopfprozedur aus                       *
*                                                                      *
\*--------------------------------------------------------------------*/
inline BOOL ButtonBase::OnLButtonUp (LPPOINT pt)
  {
  ReleaseCapture ();
  PressOut();
  Capturing = FALSE;

  CallButtonProc ();

  return (HitTest(pt));
  }

//---------------------------------------------------------------------------
// Dem Knopf wird das mdiChild, die CallBack-Funktion und die ID der 
// Prozedur bekanntgegeben.
//---------------------------------------------------------------------------
DLLExport void _export WINAPI ButtonBase::SetButtonProc (BTNPROC btnproc, DWORD procid,
                                                         LPVOID par)
  {
  BtnProc = btnproc;
  ProcID = procid;
  Data = par;
  }

//---------------------------------------------------------------------------
// Die Callback-Funktion fuer die Prozedur aufgerufen
//---------------------------------------------------------------------------
inline void ButtonBase::CallButtonProc ()
  {
  if ((BtnProc != NULL) && (ProcID != 0) && (PrivData != NULL))
    (* BtnProc) (PrivData, ProcID, Data);
  }

void ButtonBase::AllowTimer (void)
  {
  HasTimer = TRUE;
  }


inline void ButtonBase::SetButtonTimer (HWND hWnd, UINT id, UINT interval)
  {
  if (HasTimer)
    SetTimer (hWnd, id, interval, NULL);  
  }

inline void ButtonBase::RemoveButtonTimer (HWND hWnd, UINT id)
  {
  if (HasTimer)
    KillTimer (hWnd, id);  
  }



//---------------------------------------------------------------------------
//
// Klasse  <BitButton>
//     leitet sich von ButtonBase ab
//
//---------------------------------------------------------------------------
DLLExport _export WINAPI BitButton::BitButton (LPVOID privdata, int privsize,
                                               HWND RefWnd, int px, int py, int pw, int ph, 
                                               HBITMAP hbitmap, int Col, int Row, 
                                               int nIndX, int nIndY) 
                : ButtonBase (privdata, privsize, RefWnd, px, py, pw, ph)
  {
  XIndex = nIndX;
  YIndex = nIndY;
  hBmp = hbitmap;

  AnzCol = Col;   // Spalten des Bitmaps
  AnzRow = Row;   // Zeilen des Bitmaps 

  GetRect();
  }

/*--------------------------------------------------------------------*\
* member function:  GetRect                                            *
*                                                                      *
* Berechne die Ausdehnung des Buttons                                  *
\*--------------------------------------------------------------------*/
void BitButton::GetRect ()
  {
  BITMAP bi;

  if (hBmp) {
    GetObject (hBmp, sizeof(bi), &bi);
    BmpWidth = bi.bmWidth / AnzCol;        // errechne die Breite eines Bildes
    BmpHeight = bi.bmHeight / AnzRow;      // errechne die Höhe eines Bildes
    }
  else
    BmpWidth = BmpHeight = 0;

  // umgebendes Rechteck inklusive Rahmen und 3D-Linien  
  int iw = (w == 0) ? x + BmpWidth + 7 : x + w;
  int ih = (h == 0) ? y + BmpHeight + 7 : y + h;
  
  SetRect (LPRECT(&ButtonRect), x, y, iw, ih);  
  }


/*--------------------------------------------------------------------*\
* member function:  PaintButton                                        *
*                                                                      *
\*--------------------------------------------------------------------*/
void BitButton::PaintButton (BOOL State)
  {
  HBITMAP  OldBitmap;
  int      OffsetX, OffsetY;


  //-----------------------------------------------------
  // zuerst einmal wird der Knopf ohne Inhalt gezeichnet
  //-----------------------------------------------------
  ButtonBase::PaintButton (State);

  OffsetX = State ? 1 : 0;
  OffsetY = State ? 1 : 0;
    
  if (hBmp != 0) {
    HDC hDC = GetDC(hWndParent);              // DC holen
    HDC hMemDC = CreateCompatibleDC(hDC);     // und einen für das Bitmap

    OldBitmap = (HBITMAP)SelectObject (hMemDC, hBmp);
    
    int bmpx, bmpy;
    if (w == 0)
      bmpx = ButtonRect.left + XBORDER;
    else
      bmpx = (BmpWidth < w-7) ? (ButtonRect.left + ButtonRect.right - BmpWidth) / 2
                              : ButtonRect.left + XBORDER;
    
    if (h == 0)
      bmpy = ButtonRect.top + YBORDER;
    else
      bmpy = (BmpHeight < h-7) ? (ButtonRect.top + ButtonRect.bottom - BmpHeight) / 2
                              : ButtonRect.top + YBORDER;

      BitBlt (hDC, bmpx + OffsetX, bmpy + OffsetY,
                   BmpWidth, BmpHeight,
              hMemDC,
                   (XIndex-1) * BmpWidth, (YIndex-1) * BmpHeight,
                   SRCCOPY
            );

    SelectObject (hMemDC, OldBitmap);

    DeleteDC (hMemDC);
    ReleaseDC (hWndParent, hDC);
    }
  }


//---------------------------------------------------------------------------
//
// Klasse  <TextButton>
//
//---------------------------------------------------------------------------
inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt;
  pt.x = x ;
  pt.y = 0 ;
  DPtoLP (hDC,&pt,1);
  return pt.x;
  }

extern void SetTwips (HDC hDC,int x = 0,int y = 0);
extern void SetMMText (HDC hDC,int y = 0);


inline void RectToDev (HDC hDC, LPRECT r)
  {
  SetTwips (hDC);
  POINT pt[2];
  pt[0].x = r->left  , pt[0].y = r->top ;
  pt[1].x = r->right , pt[1].y = r->bottom ;
  LPtoDP (hDC, pt, 2);

  r->left  = pt[0].x , r->top    = pt[0].y ;
  r->right = pt[1].x , r->bottom = pt[1].y ;
  }

//---------------------------------------------------------------------------
//
// CONSTRUCTOR  <TextButton>
//     leitet sich von ButtonBase ab
//
//---------------------------------------------------------------------------
DLLExport _export TextButton::TextButton (LPVOID privdata, int privsize,
                                          HWND RefWnd, int px, int py, int pw, int ph, 
                                          LPSTR Text, int Format) 
                : ButtonBase (privdata, privsize, RefWnd, px, py, pw, ph)
  {
  TextFormat = Format;

  HDC hDC = GetDC (RefWnd);
  SetTwips (hDC);
  int w = XtoLOG (hDC, pw);
  ReleaseDC (RefWnd ,hDC);

  field = new cField (TRANSPARENT, Format, 0, 0, w, 1, FALSE);
  field->SetWindow (RefWnd);
  field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  field->SetVOrg (0,0,0);

  if (Text != NULL)
    *field = Text;
  else
    *field = "";
  
  GetRect();
  }

/*--------------------------------------------------------------------*\
* member function:  PaintButton                                        *
*                                                                      *
\*--------------------------------------------------------------------*/
void TextButton::PaintButton (BOOL State)
  {
  int      OffsetX, OffsetY;

  ButtonBase::PaintButton (State);

  OffsetX = State ? 1 : 0;
  OffsetY = State ? 1 : 0;
    
  HDC hDC = GetDC(hWndParent);              // DC holen

  if (field != NULL) {
    RECT rc;
    
    field->GetFieldRect (&rc,0);

    // logische Koordinaten in Geraetekoordinaten
    RectToDev (hDC, &rc) ;

    // y-Position im Knopf berechnen
    int textheight = rc.bottom - rc.top  + 1;
    int texty = (ButtonRect.top + ButtonRect.bottom - textheight) / 2;
    
    SetTwips (hDC, ButtonRect.left + OffsetX, texty + OffsetY);
    field->Paint (hDC, 0, FALSE);
    SetMMText (hDC);
    }

  ReleaseDC (hWndParent, hDC);
  }



//***************************************************************************
//*
//* Basisklasse fuer die Verwaltung von Knopf-Elementen
//*
//***************************************************************************
DLLExport _export BtnList::BtnList (HWND hWnd) 
  { 
  First = NULL; 
  State = BTNSTATE_INIT;
  hWndParent = hWnd;
  }

//---------------------------------------------------------------------------
// Einfuegen eines Knopfes in die Knopfliste
//---------------------------------------------------------------------------
void BtnList::Insert (LPBUTTONBASE lpItem)
  {
  LPLISTITEM NewItem = new ListItem;

  NewItem->Next = First;
  NewItem->Item = lpItem;
  First = NewItem;
  }
  
DLLExport _export BtnList::~BtnList ()
  {
  for ( ; First != NULL ; ) {
    LPLISTITEM Next = First->Next ;
    delete First->Item;
    delete First;
    First = Next;
    }
  }

LPLISTITEM BtnList::HitTest (LPPOINT pt)
  {
  LPLISTITEM p = NULL;
  for (p = First; p != NULL; p = p->Next) {
    if (p->Item->HitTest(pt))
      break;
    }
    
  return p;
  }


void BtnList::Paint (HDC hDC)
  {
  for (LPLISTITEM p = First; p != NULL; p = p->Next)
    if (p->Item->Visible)
      p->Item->PaintState ();
  }


//---------------------------------------------------------------------------
// Die Maus-Prozeduren der Liste rufen die Mausprozeduren des aktuellen
// Knopfes (ActiveItem) auf
//---------------------------------------------------------------------------
BOOL BtnList::OnLButtonDown (HWND hWnd, LPPOINT pt)
  {
  //----------------------------------------------------------------
  // Durchsuche einmal alle Knoepfe, die sich in der Liste befinden
  //----------------------------------------------------------------
  BOOL res = (ActiveItem = HitTest(pt)) != NULL;
  
  if (res) 
    ActiveItem->Item->OnLButtonDown(pt);   // auf geht's

  return (res);
  }

BOOL BtnList::OnLButtonDblClk (HWND hWnd, LPPOINT pt)
  {
  return ((ActiveItem != NULL) && ActiveItem->Item->OnLButtonDown (pt));
  }
  
BOOL BtnList::OnMouseMove (HWND hWnd, LPPOINT pt)
  {
  return FALSE;
  }
  
BOOL BtnList::OnLButtonUp (HWND hWnd, LPPOINT pt)
  {
  BOOL res = ActiveItem->Item->OnLButtonUp(pt);

  return res;
  }

void BtnList::OnTimer (HWND hWnd)
  {
  }

void BtnList::OnMouseWheel (HWND hWnd, LPPOINT pt, WORD fwKeys, short zDelta)
  {
  }

//----------------------------------------------------------------------------
// CheckMsg wird am Anfang der eigentlichen <WndProc> aufgerufen.
// Im Normalfall wird in der <WndProc> die Variable <done> geprueft, und falls
// TRUE die <WndProc> verlassen
//----------------------------------------------------------------------------
LONG BtnList::CheckMsg (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP, BOOL FAR *done)
  {  
  LONG RetVal = 0L;
  *done = FALSE;
  if (msg == WM_SETTINGCHANGE)
    wheelScrollLines = 0; 
  switch (State) {
    case BTNSTATE_INIT :       // vor dem LButtonDown
      switch (msg) {
        //--------------------------------------------------------------------
        case WM_MOUSEWHEEL:
          {
          POINT         pt;

#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif      
          OnMouseWheel (hWnd, &pt, LOWORD (wP), (short) HIWORD (wP));
          }

        //--------------------------------------------------------------------
        case WM_LBUTTONDOWN :
          {
          POINT         pt;

#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif      
          *done = OnLButtonDown (hWnd, &pt);

          if (*done)
            State = BTNSTATE_DOWN;  // jetzt ist er drin...
          }
          break;

        //------------------------------------------------------------------
        // deshalb im BTNSTATE_INIT, weil vor dem DBLCLK ein LBUTTONUP kommt
        //------------------------------------------------------------------
        case WM_LBUTTONDBLCLK:
          {
          POINT         pt;

#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif      
          *done = OnLButtonDblClk (hWnd, &pt);
          if (*done && (ActiveItem != NULL))
            State = BTNSTATE_DOWN;
          }
          break;

        }
      break ;
      
    case BTNSTATE_DOWN :
    case BTNSTATE_DOWNOUT:
      switch (msg) {
        //--------------------------------------------------------------------
        case WM_LBUTTONUP :
          {
          POINT         pt;

#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif      

          OnLButtonUp (hWnd, &pt);
          State = BTNSTATE_INIT;
          *done = TRUE;
          }
          break;

        //--------------------------------------------------------------------
        case WM_TIMER :
          OnTimer (hWnd);
          *done = TRUE;
          break ;

        //--------------------------------------------------------------------
        case WM_MOUSEMOVE :
          {
          POINT         pt;

#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif      
          OnMouseMove (hWnd, &pt);
          // Maus gedrückt aber nicht auf dem Knopf
          if (!ActiveItem->Item->OnMouseMove (LPPOINT(&lP)))   
            State = BTNSTATE_DOWNOUT;
          else
            State = BTNSTATE_DOWN;  
          
          *done = TRUE;
          }
          break ;
        }
  
    }
  return RetVal;
  }


int BtnList::GetHeight ()
  {
  return First->Item->GetHeight();
  }


int BtnList::GetWidth ()
  {
  return First->Item->GetWidth();
  }



//***************************************************************************
//*
//* abgeleitete Klasse fuer die Knoepfe in der DDSLIST
//*
//***************************************************************************
#define ID_TIMER  123
BOOL InitFastTimer;

void SingleList::PaintListButtons (HDC hDC, LPRECT rcList)
  {
  RECT rc;

  switch (ButtonPos) {
    case BTN_BOTTOM_POS:
      SetRect (&rc, 0, rcList->bottom-GetHeight()+1, rcList->right, rcList->bottom+1);
    case BTN_RIGHT_POS:
      SetRect (&rc, rcList->right, rcList->top, rcList->right+GetWidth(), rcList->bottom+1);
    }

  if (RectVisible(hDC, &rc)) {    
    HBRUSH hOldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(RGB(0x80, 0x80, 0x80)));
    HPEN hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
    Rectangle (hDC, rc.left, rc.top, rc.right, rc.bottom);
    SelectObject (hDC, hOldPen);
    DeleteObject(SelectObject (hDC, hOldBrush));

    Paint (hDC);
    }
  }


//---------------------  HitTest  -------------------------------------------
//
// sucht in der Liste aller Knoepfe, den Knopf der gedrueckt wurde
//---------------------------------------------------------------------------
LPLISTITEM SingleList::HitTest (LPPOINT pt)
  {
  LPLISTITEM p = BtnList::HitTest (pt);
  
  // Es war keiner der Knoepfe => In der oberen grauen Haelfte .... PrevPage
  //                              In der unteren grauen Haelfte ... NextPage
  if (p == NULL) {
    RECT rc;
  
    GetClientRect (hWndParent, &rc);
    rc.left = rc.right - GetWidth();
    if (PtInRect(&rc, *pt)) {
      int BtnId = (pt->y < (rc.bottom / 2)) ? BTN_IND_PREVPAGE : BTN_IND_NEXTPAGE;
      for (p = First; p != NULL; p = p->Next) {   // den Knopf suchen
        if (BtnId == LPBITBUTTON(p->Item)->XIndex % 6)
          break;
        }
      }
    }

  return p;
  }


BOOL SingleList::OnLButtonDown (HWND hWnd, LPPOINT pt)
  {
  BOOL res = BtnList::OnLButtonDown (hWnd, pt);
  if (res) {

    if (GetFocus() != hWnd)
      SetFocus (hWnd);

    ActiveItem->Item->SetButtonTimer (hWnd, ID_TIMER, 400);
    InitFastTimer = FALSE ;
    }
  
  return res;
  }

BOOL SingleList::OnLButtonDblClk (HWND hWnd, LPPOINT pt)
  {
  BtnList::OnLButtonDblClk (hWnd, pt);
//  return TRUE;   // die Liste soll mit dem Doppelklick nix machen
  return (HitTest (pt) != NULL);
  }

BOOL SingleList::OnMouseMove (HWND hWnd, LPPOINT pt)
  {
  return BtnList::OnMouseMove (hWnd, pt);
  }

BOOL SingleList::OnLButtonUp (HWND hWnd, LPPOINT pt)
  {
  ActiveItem->Item->RemoveButtonTimer (hWnd, ID_TIMER);
  BOOL res = BtnList::OnLButtonUp (hWnd, pt) || (HitTest(pt) != NULL);
  if (res) {
    UINT KeyCode;

    switch (LPBITBUTTON(ActiveItem->Item)->XIndex % 6) {
      case BTN_IND_HOME: KeyCode = VK_HOME;  break;
      case BTN_IND_PREVPAGE: KeyCode = VK_PRIOR;   break;
      case BTN_IND_PREV: KeyCode = VK_UP;  break;
      case BTN_IND_NEXT: KeyCode = VK_DOWN;  break;
      case BTN_IND_NEXTPAGE: KeyCode = VK_NEXT;  break;
      case 0:
      case BTN_IND_END: KeyCode = VK_END;  break;
      default: KeyCode = 0;
      }
    SendMessage (hWnd, WM_KEYDOWN, KeyCode, NULL);
    }

  return res;
  }

void SingleList::OnMouseWheel (HWND hWnd, LPPOINT pt, WORD fwKeys, short zDelta)
  {
  if (wheelScrollLines == 0) {
    if (!SystemParametersInfo (SPI_GETWHEELSCROLLLINES, 0, &wheelScrollLines, 0))
      wheelScrollLines = 3;
    }
  if (wheelScrollLines != 0) {
    wheelDelta += zDelta;
    LONG wheelScroll;
    UINT KeyCode, pgKeyCode;
    if (wheelDelta > 0) {
      KeyCode = VK_UP;
      pgKeyCode = VK_PRIOR;
      wheelScroll = wheelDelta / WHEEL_DELTA;
      }
    else {
      KeyCode = VK_DOWN;
      pgKeyCode = VK_NEXT;
      wheelScroll = (-wheelDelta) / WHEEL_DELTA;
      }
    if (wheelScroll > 0) {
      for (int i = 0; i < wheelScroll; i++)
        if (wheelScrollLines != WHEEL_PAGESCROLL) {
          for (UINT j = 0; j < wheelScrollLines; j++)
            SendMessage (hWnd, WM_KEYDOWN, KeyCode, NULL);
          }
        else
          SendMessage (hWnd, WM_KEYDOWN, pgKeyCode, NULL);
      if (wheelDelta > 0)
        wheelDelta -= wheelScroll * WHEEL_DELTA;
      else
        wheelDelta += wheelScroll * WHEEL_DELTA;
      }
    }
  }

void SingleList::OnTimer (HWND hWnd)
  {
  if (!InitFastTimer) {
    // Timer schneller setzen
    KillTimer (hWnd, ID_TIMER);
    ActiveItem->Item->SetButtonTimer (hWnd, ID_TIMER, 50);
    InitFastTimer = TRUE;
    }
  if (State != BTNSTATE_DOWNOUT) {  // Maus gedrückt aber momentan nicht auf Element
    UINT KeyCode;

    switch (LPBITBUTTON(ActiveItem->Item)->XIndex % 6) {
      case BTN_IND_HOME: KeyCode = VK_HOME;  break;
      case BTN_IND_PREVPAGE: KeyCode = VK_PRIOR;   break;
      case BTN_IND_PREV: KeyCode = VK_UP;  break;
      case BTN_IND_NEXT: KeyCode = VK_DOWN;  break;
      case BTN_IND_NEXTPAGE: KeyCode = VK_NEXT;  break;
      case 0:
      case BTN_IND_END: KeyCode = VK_END;  break;
      default: KeyCode = 0;
      }
    SendMessage (hWnd, WM_KEYDOWN, KeyCode, NULL);
    }
  }


void SingleList::ArrangeButtons (UINT Position, LPRECT rc)
  {
  int x, y, i;
  LPLISTITEM btn;

  ButtonPos = Position;

  switch (Position) {
    case BTN_BOTTOM_POS:
      x = rc->left;
      y = rc->top = rc->bottom-GetHeight();   
      
      i = 1;
      for (btn = First; btn != NULL; btn = btn->Next, i++) {
        btn->Item->SetXYPos (x, y);
        LPBITBUTTON(btn->Item)->SetBmpIndex (i);
        x += GetWidth();
        }

    case BTN_RIGHT_POS:
      {
      POINT pt[6];

      x = rc->right-GetWidth()+1;  // am auesserst rechten Rand der Listbox
      for (i = 0; i < 6; pt[i].x = x, i++);

      if ((6 * First->Item->GetHeight() + 2 * 5) <= rc->bottom) {
        pt[2].y = rc->top-1;         // vorheriger Datensatz
        pt[1].y = pt[2].y+5+First->Item->GetHeight()-1;  // vorherige Seite
        pt[0].y = pt[1].y+First->Item->GetHeight()-1;  // gehe an den Anfang der Liste
  
        pt[3].y = rc->bottom-First->Item->GetHeight()+1;  // naechster Datensatz
        pt[4].y = pt[3].y-5-First->Item->GetHeight()+1;     // naechste Seite
        pt[5].y = pt[4].y-First->Item->GetHeight()+1;     // an das Ende der Liste
        }
      else {
        pt[2].y = rc->top-1;                              // vorheriger Datensatz
        pt[3].y = rc->bottom-First->Item->GetHeight()+1;  // naechster Datensatz
        pt[0].y = pt[1].y = pt[4].y = pt[5].y = -First->Item->GetHeight();
        }
        
      i = 0;
      for (btn = First; ((btn != NULL) && (i < 6)); btn = btn->Next, i++) {
        if (pt[i].y == -First->Item->GetHeight())
          btn->Item->Visible = FALSE;
          
        btn->Item->SetXYPos (pt[i].x, pt[i].y);
        LPBITBUTTON(btn->Item)->SetBmpIndex (7+i);
        }
      }  
    }
  }

  
