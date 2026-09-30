//--------------------------------------------------------------------------
//  Verwaltung der Post-It's am Bildschirm
//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/rev/post_it.cpv   1.6   05 Oct 1998 11:56:30   Gerhold  $
//  $Log:   P:/marille/clinicum/rev/post_it.cpv  $
// 
//    Rev 1.6   05 Oct 1998 11:56:30   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.5   17 Dec 1996 11:00:54   GERHOLD
// GlobalLock => LPSTR(GlobalLock)
// 
//    Rev 1.4   09 Dec 1996 18:23:34   HANNES
// Freigabe der Extradaten
// 
//    Rev 1.3   05 Dec 1996 19:08:42   HANNES
// 
//    Rev 1.2   24 Mar 1996 12:09:32   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.1   02 Feb 1996 10:35:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   07 Jul 1995 17:19:54   GERHOLD
// Initial revision.
//--------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"

#include "dds.hpp"

#include "font.hpp"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"


#include "sc2d.hpp"
#include "printer.hpp"

#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#define NODLL
#include "toolbar.hpp"


#define WMU_UPDATE   WM_USER + 0
#define TOP_BORDER   10
#define FRAME_BORDER 5

#define HLPFORMAT   2

void DDSFreePrivData (LPVOID PrivData);
class FAR PostIt {
 public: 
  RECT        rcLogWnd;
  mdiChild   *c;
  cField     *field;
  HWND        MyWnd;
  LPVOID     param;
  LPVOID     PrivData;
  PostIt FAR *Next;

  PostIt (mdiChild *cp, LPSTR Text, int x, int y, int cx, int cy, HWND hWnd,int dmx,int Format,LPVOID pr,LPVOID pd,WORD pdSize);
  ~PostIt ()
     {
     if (field != NULL)
       delete field;
     if (PrivData != NULL) {
       DDSFreePrivData (PrivData);
       FreeGlobMem (PrivData);
       }
     }
  void  Paint (HDC hDC, HWND hWnd);
  void  MapChanged ();
  void  SetWindowPos ();
  void  Update ();
  
  
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef PostIt FAR* LPPOSTIT;


void SetMMText (HDC hDC,int y = 0)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void SetTwips (HDC hDC,int x = 0,int y = 0)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440, NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,x,y, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt;
  pt.x = x ;
  pt.y = 0 ;
  DPtoLP (hDC,&pt,1);
  return pt.x;
  }


//-------------------------  PostIt::PostIt  --------------------------------
//
//---------------------------------------------------------------------------
DLLExport void _export WINAPI cFieldCallBackFnc (int cmd,LPVOID Info,LPVOID MyInfo)
  {
  switch (cmd) {
    case CALLBACKCMD_SAVESTR :
      (*((PostIt FAR * FAR *) MyInfo))->Update ();
      break ;
    }
  }
PostIt::PostIt (mdiChild *cp, LPSTR Text, int x, int y, int cx, int cy, HWND hWnd,int dmx,int Format,LPVOID pr,LPVOID pd,WORD pdSize)
  {
  Next = NULL;
  MyWnd = hWnd;
  c = cp;
  SetRect (&rcLogWnd, x, y, x + cx, y + cy);
  param = pr;
  PrivData = GetGlobMem (pdSize);
  lmemcpy (PrivData,pd,pdSize);


  RECT r;

  // die Breite des cFields ist kleiner als die Fensterbreite.
  field = new cField (TRANSPARENT,Format,0,0,cx - dmx,-1,FALSE);

  if (field != NULL) {
    field->SetWindow (hWnd);
    field->SetScale (c->OutScale(),MAPTYPE_TYPOGRAPHIC);
    field->SetVOrg (0, 0, 0);
    *field = Text;
    field->GetFieldRect (&r,0);
    }
  static CFIELDCALLBACK cfb;
  if (cfb == NULL)
    cfb = CFIELDCALLBACK (
       MakeProcInstance (FARPROC(cFieldCallBackFnc),WBase::hInstance)
                         );

  LPVOID h = this;
  field->InstallCallBack (cfb,&h,sizeof(h));
  }

//-------------------------  PostIt::Paint  ---------------------------------
//
//---------------------------------------------------------------------------
#define BACKCOLOR RGB(0x80, 0x80, 0)
void PostIt::Paint (HDC hDC, HWND hWnd)
  {
  DWORD OldBackColor = SetBkColor (hDC, BACKCOLOR);
  field->Paint (hDC, 0, FALSE);
  SetBkColor (hDC, OldBackColor);
  }
  
//-------------------------  PostIt::MapChanged  ----------------------------
//
//---------------------------------------------------------------------------
void  PostIt::MapChanged ()
  {
//  static float OldScale = float(0.0);
//  static int OldXp = 0;
//  static int OldYp = 0;
//  static RECT rcOld = { 0, 0, 0, 0 };
  RECT rc;
        
//  if ((OldScale != c->OutScale()) || (OldXp != c->OutXp()) || (OldYp != c->OutYp())) {

//    if (!EqualRect(&rcOld, &rcLogWnd)) {

      PaintContext pc (c->OutWnd(),0xFFFF,0xFFFF,DO_WORK);
    
      // hier muß das Viewport richtig gesetzt werden!!!!!!!!!!!!!!!!!!
      pc.LogicalTwips (c->OutXp(), c->OutYp(), c->OutScale());
    
      field->SetScale (c->OutScale(),MAPTYPE_TYPOGRAPHIC);
      pc.LogRecttoPhys (&rc, &rcLogWnd);
  
      MoveWindow (MyWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, TRUE);
      
//      CopyRect (&rcOld, &rcLogWnd);
//      }
//    OldScale = c->OutScale();
//    OldXp = c->OutXp();
//    OldYp = c->OutYp();
//    }
  }


//-------------------------  PostIt::SetWindowPos  --------------------------
//
//---------------------------------------------------------------------------
extern void UpdatePostIt (LPVOID param,LPVOID PrivData,int x,int y,int w,int h,LPSTR Text);
void PostIt::Update ()
  {
  GLOBALHANDLE hGmem ;
  *field >> hGmem;
  LPSTR Text = (LPSTR)GlobalLock (hGmem);
  UpdatePostIt (param,PrivData,rcLogWnd.left,rcLogWnd.top,
                               rcLogWnd.right - rcLogWnd.left,
                               rcLogWnd.bottom - rcLogWnd.top,Text);
  GlobalUnlock (hGmem);
  GlobalFree (hGmem);
  }
void PostIt::SetWindowPos ()
  {
  PaintContext pc (c->OutWnd(),0xFFFF,0xFFFF,DO_WORK);
      
  RECT rc;
  GetWindowRect (MyWnd, &rc);
  ScreenToClient (c->OutWnd(), LPPOINT(&rc));
  ScreenToClient (c->OutWnd(), LPPOINT(&rc.right));
  pc.LogicalTwips (c->OutXp(), c->OutYp(), c->OutScale());
  DPtoLP (pc.hDC, LPPOINT(&rc), 2);

  CopyRect (&rcLogWnd, &rc);

  Update ();
  }



PostIt FAR *FirstPostIt = NULL;

HINSTANCE hPostItInst = NULL;
HBITMAP hBmpBackGnd = NULL;
HBITMAP hBmpLoch = NULL;
HBRUSH  hBackBrush = NULL;
//-------------------------  AddToPostItList  -------------------------------
//
//---------------------------------------------------------------------------
void AddToPostItList (PostIt FAR *p)
  {
  if (!FirstPostIt) {
    hBmpBackGnd = LoadBitmap (hPostItInst, "POSTITBACK");
    hBmpLoch = LoadBitmap (hPostItInst, "POSTLOCH");

    // hBackBrush = CreatePatternBrush(hBmpBackGnd);
    }

  p->Next = FirstPostIt;
  FirstPostIt = p;
  }

//-------------------------  RemoveFromPostItList  --------------------------
//
//---------------------------------------------------------------------------
void RemoveFromPostItList (PostIt FAR *p)
  {
  PostIt FAR *Prev = NULL;
  for (PostIt FAR *h = FirstPostIt; h != NULL; h = h->Next) {
    if (h == p) {                 
      if (Prev != NULL)           // war's gleich das erste??
        Prev->Next = p->Next;     // nein, dann ausklammern
      else
        FirstPostIt = p->Next;    // ja, das erste ist jetzt das naechste
        
      break;                      // und raus
      }

    Prev = p;
    }

  if (!FirstPostIt) {
    DeleteObject (hBmpBackGnd);
    DeleteObject (hBmpLoch);
    }
  }

//-------------------------  UpdatePostItList  ------------------------------
//
//---------------------------------------------------------------------------
void UpdatePostItList (mdiChild *c)
  {
  for (PostIt FAR *p = FirstPostIt; p != NULL; p = p->Next) {
    if (p->c == c)
      p->MapChanged ();
    }
  }

char szPostItClassName[] = "POSTITCLASS";

// HilfsStruktur ... beinhaltet das Eltern-MDI und den Text vom Post-It.
struct FAR ParentAndText {
  mdiChild *c;
  LPSTR    Text;
  LPVOID   PrivData;
  WORD     PrivDataSize;
  LPVOID   Param ;
  int      Format ;
  };

DLLExport LONG _export FAR PASCAL WndPostItProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG ret = 0L;
  LPPOSTIT pit = (LPPOSTIT)GetWindowLong (hWnd, 0);
  static BOOL bCaptured = FALSE;

  switch (msg) {
    case WM_CREATE:
      {
      CREATESTRUCT FAR *cs = (CREATESTRUCT FAR *)lP;
      
      // die logischen Koordinaten in physische Koordinaten umwandeln
      PaintContext pc (((ParentAndText *)cs->lpCreateParams)->c->OutWnd(),0xFFFF,0xFFFF,DO_WORK);
      pc.LogicalTwips (((ParentAndText *)cs->lpCreateParams)->c->OutXp(),((ParentAndText *)cs->lpCreateParams)->c->OutYp(), ((ParentAndText *)cs->lpCreateParams)->c->OutScale());

      int dmx = XtoLOG(pc.hDC, 2 * (FRAME_BORDER + 2 + GetSystemMetrics(SM_CXBORDER)));
      pit = new PostIt (((ParentAndText *)cs->lpCreateParams)->c, 
                        ((ParentAndText *)cs->lpCreateParams)->Text,
                        cs->x, cs->y, cs->cx, cs->cy, hWnd,dmx,
                        ((ParentAndText *)cs->lpCreateParams)->Format,
                        ((ParentAndText *)cs->lpCreateParams)->Param,
                        ((ParentAndText *)cs->lpCreateParams)->PrivData,
                        ((ParentAndText *)cs->lpCreateParams)->PrivDataSize
                        );
      if (pit == NULL)
        return -1;

      SetWindowLong (hWnd, 0, LONG(pit));

      RECT rc;
      pc.LogRecttoPhys (&rc, &pit->rcLogWnd);
      MoveWindow (hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);

      AddToPostItList (pit);
      }
      break;

    case WM_SIZE :
      {
      pit->SetWindowPos ();
      PaintContext pc(hWnd);
      pc.LogicalTwips (0, 0, pit->c->OutScale());
      
      pit->field->SetWidth (pit->rcLogWnd.right - pit->rcLogWnd.left - XtoLOG(pc.hDC, 2 * (FRAME_BORDER + 2 + GetSystemMetrics(SM_CXBORDER))));
      InvalidateRect (hWnd,NULL,TRUE);
      }
      break;

    case WM_MOVE :
      {
      pit->SetWindowPos ();
      }
      break;

    case WM_PAINT :
      {
      if (pit != NULL) {
        PaintContext pc(hWnd);
        pc.LogicalTwips (0, 0, pit->c->OutScale());
        pit->Paint (pc.hDC, hWnd);
        }

      break;
      }

    case WM_SETCURSOR :
      if (LOWORD(lP) == HTCLIENT)
        SetCursor (LoadCursor(NULL, IDC_IBEAM));
      else  
        ret = DefWindowProc (hWnd, msg, wP, lP);
/*
      else  
        SetCursor (LoadCursor(NULL, IDC_ARROW));
*/
      break;
//      return TRUE;

    case WM_SETFOCUS :
      {
      pit->field->SetBackMode (OPAQUE);
      pit->field->OnSetFocus (FALSE, WWGetSelect());
      }
      break;

    case WM_KILLFOCUS :
      pit->field->OnKillFocus (wP,0);
      pit->field->SetBackMode (TRANSPARENT);
      break;
    
    case WM_KEYDOWN :
      pit->field->OnKeyDown (wP,0);
      break;
      
    case WM_LBUTTONDOWN :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lP, pt);
#else
      pt = MAKEPOINT (lP);
#endif

      SetFocus (hWnd);
      SetCapture (hWnd);
      bCaptured = TRUE;
      pit->field->OnLButtonDown (wP, pt, 0);
      }
      break;
      
    case WM_MOUSEMOVE :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lP, pt);
#else
      pt = MAKEPOINT (lP);
#endif
      pit->field->OnMouseMove (wP, pt, 0);
      }
      break;
      
    case WM_LBUTTONUP :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lP, pt);
#else
      pt = MAKEPOINT (lP);
#endif
      pit->field->OnLButtonUp (wP, pt, 0);
      if (bCaptured) {
        ReleaseCapture();
        bCaptured = FALSE;
        }
      }
      break;
      
    case WM_LBUTTONDBLCLK :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lP, pt);
#else
      pt = MAKEPOINT (lP);
#endif

      pit->field->OnLButtonDblClk (wP, pt, 0);
      }
      break;
      
    case WM_CHAR :
      pit->field->OnChar (wP,0);
      break;
      
    case WM_DESTROY :
      {
      if (pit != NULL)
        RemoveFromPostItList (pit);
        delete pit;
      }
      break;

    case WM_NCCALCSIZE:
      {
      // This is sent when the window manager wants to find out
      // how big our client area is to be.  If we have a mini-caption
      // then we trap this message and calculate the client area rect,
      // which is the client area rect calculated by DefWindowProc()
      // minus the width/height of the mini-caption bar
      //
      ret = DefWindowProc (hWnd, msg, wP, lP);
      RECT rcTmp;
      CopyRect (&rcTmp, ((LPRECT)lP));

      int cx = /*GetSystemMetrics (SM_CXFRAME) - GetSystemMetrics (SM_CXBORDER) +*/ FRAME_BORDER;
      int cy = /*GetSystemMetrics (SM_CYFRAME) - GetSystemMetrics (SM_CYBORDER) +*/ FRAME_BORDER;
      ((LPRECT)lP)->left += cx;
//      ((LPRECT)lP)->top += cy;
      ((LPRECT)lP)->top += TOP_BORDER;
      ((LPRECT)lP)->right -= cx;
      ((LPRECT)lP)->bottom -= cy;

      CopyRect (&rcTmp, ((LPRECT)lP));
      }
      return ret ;

    case WM_NCHITTEST :
      {
      RECT rc;
      LONG lret = DefWindowProc (hWnd, msg, wP, lP);
      GetWindowRect (hWnd, &rc);
      
      rc.bottom = rc.top + TOP_BORDER;

      int cx = GetSystemMetrics (SM_CXFRAME) - GetSystemMetrics (SM_CXBORDER) + FRAME_BORDER;
      int cy = GetSystemMetrics (SM_CYFRAME) - GetSystemMetrics (SM_CYBORDER) + FRAME_BORDER;

      rc.top += cy;
      rc.left += cx;
      rc.right -= cx;

      POINT pt;
      pt.x = LOWORD(lP);
      pt.y = HIWORD(lP);
//      ScreenToClient (hWnd, &pt);
      if (PtInRect(&rc, pt))
        lret = HTCAPTION;

      return lret;
      }  

    case WM_NCPAINT:
      {
      RECT rcWnd;
      HDC   hDC = GetWindowDC(hWnd);

      GetWindowRect (hWnd, LPRECT(&rcWnd));

      int cx = rcWnd.right - rcWnd.left-1;
      int cy = rcWnd.bottom - rcWnd.top-1;

      int dx = 0, dy = 0;
      dx = GetSystemMetrics(SM_CXFRAME);
      dy = GetSystemMetrics(SM_CYFRAME);

      RECT rc;
      GetClientRect (hWnd, &rc);

      OffsetRect (&rc, FRAME_BORDER + dx, TOP_BORDER + dy);
      // das Client-Fenster soll vom nachfolgenden PatBlt nicht
      // ueberschrieben werden.
      ExcludeClipRect (hDC, rc.left, rc.top, rc.right, rc.bottom);

      // Farbe des Fenster 
      HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, hBackBrush);
//      HBRUSH OldBrush = SelectObject (hDC, CreateSolidBrush(RGB(0x80, 0x80, 0)));
      PatBlt (hDC, 0, 0, cx, cy, PATCOPY);
      DeleteObject (SelectObject (hDC, OldBrush));

      HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
      MoveToEx (hDC, 0, cy, NULL);
      LineTo (hDC, cx, cy);
      LineTo (hDC, cx, -1);

      SelectObject (hDC, GetStockObject(WHITE_PEN));
      MoveToEx (hDC, 1, cy-2, NULL);
      LineTo (hDC, 1, 1);
      LineTo (hDC, cx-2, 1);
      SelectObject (hDC, OldPen);

      OldPen = (HPEN)SelectObject (hDC,CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
      MoveToEx (hDC, cx-1, 1, NULL);
      LineTo (hDC, cx-1, cy-1);
      LineTo (hDC, 0, cy-1);
      DeleteObject (SelectObject (hDC,OldPen));

      OldPen = (HPEN)SelectObject (hDC,CreatePen(PS_SOLID, 0, RGB(0xC0, 0xC0, 0xC0)));
      MoveToEx (hDC, 0, cy-1, NULL);
      LineTo (hDC, 0, 0);
      LineTo (hDC, cx, 0);
      DeleteObject (SelectObject (hDC,OldPen));

//      DrawEdge (hDC, &rc, EDGE_HWND, BF_ADJUST);
/*
      BITMAP bm;
      GetObject (hBmpLoch, sizeof(BITMAP), &bm);

      for (int i = 10; i < cx - 20; i += (bm.bmWidth + 15))
        DrawTransparentBitmap (hDC, hBmpLoch, i, 10, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0x80, 0, 0));
*/
//      SetBkColor (hDC, OldBack);
      ReleaseDC (hWnd, hDC);
      }
      break;
      
    default:
      ret = DefWindowProc (hWnd, msg, wP, lP);
    }
  
  return ret;
  }



BOOL RegisterPostItWindow (HINSTANCE hInst)
  {
  static BOOL bRegistered = FALSE;
  
  if (!bRegistered) {
    LOGBRUSH LogBrush;
#ifdef WIN32
    LogBrush.lbHatch = LONG(LoadBitmap(hInst, "POSTITBACK"));
#else
    LogBrush.lbHatch = LoadBitmap(hInst, "POSTITBACK");
#endif
    hBackBrush = CreateBrushIndirect(&LogBrush);
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wndclass.lpfnWndProc   = WndPostItProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 4 ;
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
//    wndclass.hbrBackground = GetStockObject (LTGRAY_BRUSH) ;
//    wndclass.hbrBackground = GetStockObject (WHITE_BRUSH) ;
    wndclass.hbrBackground = hBackBrush ;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = szPostItClassName;

    if (RegisterClass (&wndclass))
      bRegistered = TRUE;

    hPostItInst = hInst;
    }
  return bRegistered;
  }


HWND CreatePostItWindow (mdiChild *c, HINSTANCE hInst, int x, int y, int w, int h, int Format, LPSTR Text,LPVOID Param,LPVOID PrivData,WORD privDataSize)
  {
  HWND hWnd = 0;
  if (RegisterPostItWindow (hInst)) {
    ParentAndText FAR *pt = (ParentAndText FAR *)GetGlobMem (sizeof(ParentAndText));
    pt->c = c;
    pt->Text = Text;
    pt->PrivData = PrivData;
    pt->PrivDataSize = privDataSize;
    pt->Param = Param ;
    pt->Format = Format ;
    hWnd  = CreateWindow (szPostItClassName, NULL, 
                          WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME | WS_CLIPSIBLINGS,
                          x, y, w, h,
                          c->OutWnd(), 0, hInst, LPVOID(pt));
    FreeGlobMem (pt);
    }
  return hWnd;
  }

void DelBackBrush ()
  {
  if (hBackBrush)
    DeleteObject (hBackBrush);
  }

