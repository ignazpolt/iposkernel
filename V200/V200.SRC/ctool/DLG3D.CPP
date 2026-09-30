//////////////////////////////////////////////////////////////////////////
//      $Header:   P:/marille/clinicum/ctool/rev/dlg3d.cpv   1.14   05 Oct 1998 11:06:32   Gerhold  $
//      $Log:   P:/marille/clinicum/ctool/rev/dlg3d.cpv  $
// 
//    Rev 1.14   05 Oct 1998 11:06:32   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.13   24 Mar 1996 12:10:16   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.12   02 Feb 1996 10:41:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   02 Nov 1995 20:18:16   GERHOLD
// cField in der Caption hatte als Zeilenanzahl -1; korrigiert auf 1
// 
//    Rev 1.10   10 Aug 1995 09:23:42   GERHOLD
// Caption kann jetzt "on the fly" veraendert werden
// 
//    Rev 1.9   07 Aug 1995 16:28:22   GERHOLD
// WM_SETTEXT zeichnet die Caption
// 
//    Rev 1.8   07 Jul 1995 17:23:40   GERHOLD
// 
//    Rev 1.7   11 Jun 1995 23:24:42   HANNES
// DeleteObject hinter! dem SelectObject (old...)
// 
//    Rev 1.6   24 Feb 1995 11:03:26   GERHOLD
// in der WndProc ein bisschen was veraendert (Rahmen zeichnen etc.)
// 
//    Rev 1.5   21 Nov 1994 17:17:00   GERHOLD
// WM_NCPAINT, WM_NCACTIVATE ... CurrentDlg fuers Zeichnen bestimmen.
// 
//    Rev 1.4   16 Nov 1994 21:08:44   GERHOLD
// ???
// 
//    Rev 1.3   28 Aug 1994 11:36:46   GERHOLD
// Caption an das Schrift-Format angepasst
// 
//    Rev 1.2   26 Jul 1994 13:35:12   GERHOLD
// 
//    Rev 1.1   20 Jul 1994 17:01:30   GERHOLD
// 
//    Rev 1.0   05 Jul 1994 15:44:06   GERHOLD
// Initial revision.
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
//#include <windowsx.h>
#include <memory.h>
#include "dds32.h"
#include "globmem.h"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"
#include "dlg3d.hpp"


//#define BORDER   5
#define TEXT_FORMAT 1
/*
inline int DlgBorder()
  {
  return GetSystemMetrics(SM_CXDLGFRAME);
  }
*/

LPDLGSTRUCT ActiveDlg;
LPDLGSTRUCT CurrentDlg = NULL;
LPDLGSTRUCT FirstDlg = NULL;


// CAPTIONXY is the default size of the system menu icon.  This
// determines the height/width of the caption.
//
// The value that results from the following formula works out
// nicely for the veritcal caption on VGA, 8514 (Large Fonts),
// 8514 (Small Fonts), XGA (Small Fonts), XGA (Large Fonts),
// and TIGA (Small Fonts).  It may not be good on other displays.
//
// The problem is that TT fonts turn into bitmap fonts when they
// are sized below a certain threshold.  The idea is to make the
// size of the caption just big enough to get the smallest TT
// (scalable) font to fit.
//

inline int CAPTIONXY ()
  { 
  return (GetSystemMetrics(SM_CYCAPTION) / 2 + 1); 
  }

inline BOOL TestWinStyle (HWND hWnd, DWORD dwStyleBit) 
  {
  return (((DWORD)GetWindowLong (hWnd, GWL_STYLE) & (DWORD)dwStyleBit) ? TRUE : FALSE);
  }

inline BOOL HASCAPTION (HWND hwnd)   
  {
  return TestWinStyle (hwnd, WS_CAPTION);
  }
                               
inline UINT SETCAPTIONHEIGHT (HWND h, UINT i)
  {
  return (UINT)SetProp (h, "ibSize", (HANDLE)i);
  }
  
inline UINT GETCAPTIONHEIGHT (HWND h)     
  {
  return (UINT)GetProp (h, "ibSize");
  }

inline void FREECAPTIONHEIGHT (HWND h)
  {
  RemoveProp (h, "ibSize");
  }

inline void SETMENUWASUPFLAG (HWND h, UINT i) 
  {
  (UINT)SetProp (h, "ibFlag", (HANDLE)i);
  }
  
inline BOOL GETMENUWASUPFLAG (HWND h)  
  {
  return (BOOL)GetProp (h, "ibFlag");
  }
  
inline void FREEMENUWASUPFLAG (HWND h)
  {
  RemoveProp (h, "ibFlag");
  }
  

void SetMMText (HDC hDC)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }


extern void SetTwips (HDC hDC,int x,int y);


inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt;
  pt.x = x ;
  pt.y = 0 ;
  DPtoLP (hDC,&pt,1);
  return pt.x;
  }


/////////////////////////////////////////////////////////////////////
// Little known fact:
//    ExtTextOut() is the fastest way to draw a filled rectangle
//    in Windows (if you don't want dithered colors or borders).
//
//    Unfortunately there is a bug in the Windows 3.0 8514 driver
//    in using ExtTextOut() to a memory DC.  If you are drawing
//    to an off screen bitmap, then blitting that bitmap to the
//    display, do not #define USE_EXTTEXTOUT below.
//
//    The following macro (DRAWFASTRECT) draws a filled rectangle
//    with no border and a solid color.  It uses the current back-
//    ground color as the fill color.
//////////////////////////////////////////////////////////////////////
#define USE_EXTTEXTOUT
#ifdef USE_EXTTEXTOUT
   #define DRAWFASTRECT(hdc,lprc) ExtTextOut(hdc,0,0,ETO_OPAQUE,lprc,NULL,0,NULL)
#else
   #define DRAWFASTRECT(hdc,lprc) {\
   HBRUSH hbr = CreateSolidBrush( GetBkColor( hdc ) ) ;\
   hbr = SelectObject(hdc, hbr) ;\
   PatBlt(hdc,(lprc)->left,(lprc)->top,(lprc)->right-(lprc)->left,(lprc)->bottom-(lprc)->top,PATCOPY) ;\
   hbr = SelectObject(hdc, hbr) ;\
   DeleteObject( hbr ) ;\
   }
#endif

// The DrawArrow function takes the following to indicate what
// kind of arrow to draw.
//
#define ARROW_UP        0
#define ARROW_DOWN      1
#define ARROW_RESTORE   2

BOOL NEAR PASCAL DepressMinMaxButton( HWND hWnd, UINT uiHT, LPRECT ) ;
BOOL NEAR PASCAL DoMenu( HWND hWnd ) ;
void NEAR PASCAL SetupSystemMenu( HWND hWnd, HMENU hMenu ) ;
BOOL NEAR PASCAL GetCaptionRect( HWND hWnd, LPRECT lprc ) ;
BOOL NEAR PASCAL GetIconRect( HWND hWnd, LPRECT lprc ) ;
BOOL NEAR PASCAL GetButtonRect( HWND hWnd, UINT nPos, LPRECT lprc ) ;
BOOL NEAR PASCAL GetMinButtonRect( HWND hWnd, LPRECT lprc ) ;
BOOL NEAR PASCAL GetMaxButtonRect( HWND hWnd, LPRECT lprc ) ;
BOOL NEAR PASCAL DrawCaption( HDC hDC, HWND hWnd, LPRECT lprc,
                              BOOL fCapt, BOOL fSysMenu, 
                              BOOL fMin, BOOL fMax, BOOL fActive ) ;
VOID NEAR PASCAL DrawSysMenu( HDC hDC, HWND hWnd, BOOL fInvert ) ;
VOID NEAR PASCAL DrawButton( HDC hDC, HWND hWnd, BOOL fMin, BOOL fDepressed ) ;
VOID NEAR PASCAL DrawArrow( HDC hdc, LPRECT lprc, UINT uiStyle ) ;

// Global vars
//
static BOOL fWin31 ;


///////////////////////////////////////////////////////////////////////
// External/Public functions
///////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//  UINT WINAPI ibGetCaptionSize( HWND hWnd )
//
//  Description: 
//
//    Gets the size of the caption (height if horz, width if
//    vertical).
//
//  Comments:
//
///////////////////////////////////////////////////////////////
DLLExport UINT _export WINAPI ibGetCaptionSize (HWND hWnd)
  {
  return GETCAPTIONHEIGHT(hWnd) + 1;
  }

/////////////////////////////////////////////////////////////////
//  UINT WINAPI ibSetCaptionSize( HWND hWnd, UINT nSize )
//
//  Description: 
//
//    Changes the size of the caption (height if horz, width if
//    vertical).
//
//  Comments:
//
//////////////////////////////////////////////////////////////////
UINT WINAPI ibSetCaptionSize (HWND hWnd, UINT nSize)
  {
  UINT ui ;

  if (nSize <= 0)
    return 0;

  nSize-- ;
  ui = SETCAPTIONHEIGHT(hWnd, nSize);

  // Once we change the window style, we need a WM_NCCALCRECT
  // to be generated.
  //
  // SWP_FRAMECHANGED is not documented in the 3.1 SDK docs,
  // but *is* in WINDOWS.H.
  //
  SetWindowPos( hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | 
                        SWP_NOSIZE | SWP_NOMOVE | 
                        SWP_NOACTIVATE | SWP_NOZORDER) ;

  return ui ;
  } 

/////////////////////////////////////////////////////////////////
//  LRESULT WINAPI ibDefWindowProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
//
//  Description: 
//
//    This function should be called instead of DefWindowProc() for
//    windows that want to have itsybitsy captions.
//
//  Comments:
//
//////////////////////////////////////////////////////////////////
LRESULT WINAPI ibDefWindowProc( HWND hWnd, UINT uiMsg, WPARAM wP, LPARAM lP)
  {
  LRESULT lRet = 0L ;
  UINT  nCapSize ;

  switch( uiMsg ) {
    case WM_SYSCHAR:
      // If ALT-SPACE 
      // was hit then pop up the menu
      // 
      if (HASCAPTION(hWnd) && (wP == VK_SPACE)) {
        DoMenu( hWnd ) ;
        break ;
        }

      // FALL THROUGH!!!!
      // 

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
      {
      DWORD dw = GetWindowLong( hWnd, GWL_STYLE ) ;

      // Fool DefWindowProc into thinking we do not have
      // a system menu.  Otherwise it will try to
      // pop up its own.
      // 
      SetWindowLong( hWnd, GWL_STYLE, dw &~WS_SYSMENU ) ;
      lRet = DefWindowProc( hWnd, uiMsg, wP, lP ) ;
      SetWindowLong( hWnd, GWL_STYLE, dw ) ;
      return lRet ;
      }
      break ;
        
    case WM_COMMAND:
      {
      // The menu that is poped up for the system menu with
      // TrackPopupMenu() sends it's notifications as WM_COMMAND
      // messages.  We need to translate these into
      // WM_SYSCOMMAND messages.  All standard WM_SYSCOMMAND
      // ids are greater than 0xF000.
      //
      // This could be a possible cause of confusion if the
      // itsybitsy window had children that used SC_MOVE or SC_CLOSE
      // as their IDs.  Take note and be careful.
      //
      // Also, because ibDefWindowProc looks at WM_COMMAND messages,
      // you will need to be careful to call ibDefWindowProc() for
      // any wm_command messages that you would normally ignore.
      // Otherwise the system menu won't work.
      //
      CRACKER_VARS
      CRACK_MESSAGEsc
      
      if (CRACKER_wID >= 0xF000)
      // Call PostMessage() here instead of SendMessage!
      // Here's why:
      //      Our menu was created by TrackPopupMenu().  TPM() does
      //      not return until after the menu has been destroyed 
      //      (and thus the command associated with the menu selection
      //      sent).  Therefore when we get here, we are still
      //      *inside* TPM().  If we Send WM_SYSCOMMAND, SC_CLOSE
      //      to the window, the window will be destroyed before
      //      TPM() returns to our code within DoMenu() below.  Wel...
      //      We do stuff with the window handle after DoMenu()
      //      returns (namely GetProp()).  Since the window has
      //      been destroyed,this is bad.  
        PostMessage( hWnd, WM_SYSCOMMAND, wP, lP ) ;
      }
      return DefWindowProc( hWnd, uiMsg, wP, lP ) ;

    case WM_GETMINMAXINFO:
      {
      nCapSize = GETCAPTIONHEIGHT (hWnd);
      if (HASCAPTION (hWnd) && TestWinStyle (hWnd, WS_THICKFRAME)) {
        LPPOINT lppt = (LPPOINT)lP ;
        RECT    rcMenu ;
        RECT    rcMin ;
        RECT    rcMax ;
        int     nX ;
        int     cx, cy ;    // window frame/border width

        if (TestWinStyle( hWnd, WS_THICKFRAME )) {
          cx = GetSystemMetrics( SM_CXFRAME) ;
          cy = GetSystemMetrics( SM_CYFRAME) ;
          } 
        else
        if (TestWinStyle(hWnd, WS_BORDER )) {
          cx = GetSystemMetrics( SM_CXBORDER ) ;
          cy = GetSystemMetrics( SM_CYBORDER ) ;
          }
                                
        GetIconRect( hWnd, &rcMenu ) ;
        GetMinButtonRect( hWnd, &rcMin ) ;
        GetMaxButtonRect( hWnd, &rcMax ) ;
        nX = (rcMenu.right-rcMenu.left) + 
             (rcMin.right-rcMin.left) +
             (rcMin.right-rcMin.left) ;

        if (TestWinStyle (hWnd, WS_CAPTION)) {
          lppt[3].x = nX + (2* nCapSize);
          lppt[3].y = nCapSize + cy * 2 - 1;
          }
        }
        return DefWindowProc( hWnd, uiMsg, wP, lP ) ;
      }
      break ;

        /////////////////////////////////////////////////////////////////////
        // Non-client area messages.  These are used to allow the
        // minature caption bar to be handled correctly.
        //
    case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcr = LPCREATESTRUCT(lP);
      DWORD dwStyle;
      // Wir haben zwei Dinge, die irgendwo gespeichert werden müssen
      //     1) Die Höhe der Caption (Breite).
      // und 2) Ein Flag welches anzeigt ob das System-Menu aufgeklappt war
      //        oder nicht.
      // 
      // CAPTIONXY is a macro that calls GetSystemMetrics.
      //
      dwStyle = GetWindowLong (hWnd, GWL_EXSTYLE);
      if ((dwStyle & WS_CAPTION) && (dwStyle & WS_EX_DLGMODALFRAME)) {
        dwStyle &= (DWORD)~WS_EX_DLGMODALFRAME;
        SetWindowLong (hWnd, GWL_EXSTYLE, dwStyle);
        }

      dwStyle = GetWindowLong (hWnd, GWL_STYLE);
      if (dwStyle & WS_CAPTION)
        SETCAPTIONHEIGHT (hWnd, GetSystemMetrics(SM_CYCAPTION));
      else  
        SETCAPTIONHEIGHT (hWnd, 0);

      // Set our flag that tells us whether the system menu was
      // 'just up'. 
      //
      SETMENUWASUPFLAG (hWnd, FALSE);

      // Are we in 3.1?  If so we have some neat features
      // we can use like rotated TrueType fonts.
      //
      fWin31 = (BOOL)(LOWORD(GetVersion()) >= 0x030A);

      // If IBS_????CAPTION was specified and the WS_DLGFRAME (or
      // WS_DLGFRAME 'cause it == WS_CAPTION | WS_BORDER)
      // was specified the creator made a mistake.  Things get really
      // ugly if DefWindowProc sees WS_DLGFRAME, so we strip
      // the WS_DLGFRAME part off!
      if ((dwStyle & WS_CAPTION) && (dwStyle & WS_DLGFRAME)) {
        dwStyle &= (DWORD)~WS_DLGFRAME ;
        SetWindowLong (hWnd, GWL_STYLE, dwStyle);
        }

      RECT rcCapt, rcMenu, rcMin, rcMax;
      int w;

      GetCaptionRect (hWnd, &rcCapt);    // die gesamte Groesse der Caption
      GetIconRect (hWnd, &rcMenu);       // Groesse des Sysmenu-Icons
      GetMinButtonRect (hWnd, &rcMin);   // Abmessungen der Min/Max-Buttons
      GetMaxButtonRect (hWnd, &rcMax);
      // was nach Abzug aller Buttons wirklich fuer den Text uebrig bleibt!
      w = (rcCapt.right-rcCapt.left)-    
          ((rcMenu.right-rcMenu.left)+
          (rcMin.right-rcMin.left)+
          (rcMax.right-rcMax.left));
          
      HDC hDC = GetWindowDC (hWnd);
      LPDLGSTRUCT lpdlg = (LPDLGSTRUCT)GetGlobMem (sizeof(*lpdlg));
      lpdlg->hWnd = hWnd;

      SetTwips (hDC, 0, 0);
      lpdlg->cfCaption = new cField (TRANSPARENT, TEXT_FORMAT, 0, 0, XtoLOG(hDC, w), 1, FALSE); 
      lpdlg->cfCaption->SetWindow (hWnd);
      lpdlg->cfCaption->SetScale (1.0, MAPTYPE_TYPOGRAPHIC);
      lpdlg->cfCaption->SetVOrg (0, 0, 0);

      lpdlg->Next = FirstDlg;
      FirstDlg = lpdlg;

      *lpdlg->cfCaption = LPSTR(lpcr->lpszName);

      lpdlg->cfCaption->GetFieldRect (&rcCapt,0);
      POINT pt[2];
      pt[0].x = rcCapt.left  , pt[0].y = rcCapt.top ;
      pt[1].x = rcCapt.right , pt[1].y = rcCapt.bottom ;
      LPtoDP (hDC, pt, 2);           // in Device-Koordinaten umwandeln

      ReleaseDC (hWnd, hDC);

      rcCapt.left  = pt[0].x , rcCapt.top    = pt[0].y ;
      rcCapt.right = pt[1].x , rcCapt.bottom = pt[1].y + 2;

      // ab jetzt wird die Hoehe der Caption durch das Textformat bestimmt
      if (dwStyle & WS_CAPTION) 
        SETCAPTIONHEIGHT (hWnd, rcCapt.bottom-rcCapt.top);
      
      return DefWindowProc (hWnd, uiMsg, wP, lP);
      }

    case WM_DESTROY:
    case WM_NCDESTROY:
      // We store the caption size in a window prop. so we
      // must remove props.
      //
      
      {
      LPDLGSTRUCT Prev = NULL;
      for (LPDLGSTRUCT lpdlg = FirstDlg; lpdlg != NULL; lpdlg = lpdlg->Next) {
        if (lpdlg->hWnd == hWnd) {
          if (Prev == NULL)
            FirstDlg = lpdlg->Next;
          else  
            Prev->Next = lpdlg->Next;

          delete lpdlg->cfCaption;
          FreeGlobMem (lpdlg);
          break;
          }
        
        Prev = lpdlg;  
        }
       
      FREECAPTIONHEIGHT (hWnd);
      FREEMENUWASUPFLAG (hWnd);
      }
      return DefWindowProc (hWnd, uiMsg, wP, lP);

    case WM_NCCALCSIZE:
      // This is sent when the window manager wants to find out
      // how big our client area is to be.  If we have a mini-caption
      // then we trap this message and calculate the client area rect,
      // which is the client area rect calculated by DefWindowProc()
      // minus the width/height of the mini-caption bar
      //
      lRet = DefWindowProc (hWnd, uiMsg, wP, lP);
      if (!IsIconic(hWnd) && HASCAPTION(hWnd)) {
        nCapSize = GETCAPTIONHEIGHT(hWnd)/* + DlgBorder()*/;

        if (TestWinStyle (hWnd, WS_CAPTION)) {
          ((LPRECT)lP)->top += nCapSize;
          }

        if (TestWinStyle(hWnd, WS_BORDER ) && !TestWinStyle(hWnd, WS_THICKFRAME)) {
          int cx = GetSystemMetrics (SM_CXFRAME) - GetSystemMetrics (SM_CXBORDER);
          int cy = GetSystemMetrics (SM_CYFRAME) - GetSystemMetrics (SM_CYBORDER);
          ((LPRECT)lP)->left += cx;
          ((LPRECT)lP)->top += cy;
          ((LPRECT)lP)->right -= cx;
          ((LPRECT)lP)->bottom -= cy;
          }
        }
      return lRet ;

    case WM_NCHITTEST:
            // This message is sent whenever the mouse moves over us.
            // We will depend on DefWindowProc for everything unless
            // there is a mini-caption, in which case we will
            // return HTCAPTION or HTSYSMENU.  When the user clicks
            // or double clicks, NC_LBUTTON/ message are sent with
            // wParam equal to what we return here.
            // This means that this is an ideal place to figure out
            // where we are!
            //
            // let defwindowproc handle the standard borders etc...
            //
      lRet = DefWindowProc( hWnd, uiMsg, wP, lP ) ;
      if (!IsIconic( hWnd ) && HASCAPTION( hWnd ) && lRet == HTNOWHERE) {
        RECT  rc ;
        RECT  rcMenu ;
        RECT  rcMinButton ;
        RECT  rcMaxButton ;
        POINT pt ;

        nCapSize = GETCAPTIONHEIGHT (hWnd);

              // if DefWindowProc returned HTCAPTION then we have to
              // refine the area and return HTSYSMENU if appropriate
              //
        pt.x = LOWORD(lP);
        pt.y = HIWORD(lP);

        GetCaptionRect( hWnd, &rc ) ;  // window coords
        if (PtInRect( &rc, pt )) {
          lRet = HTCAPTION ;

                     // rely on the fact that Get???Rect() return an invalid 
                     // (empty) rectangle if the menu/buttons don't exist
                     //
          GetIconRect( hWnd, &rcMenu ) ;
          GetMinButtonRect( hWnd, &rcMinButton ) ;
          GetMaxButtonRect( hWnd, &rcMaxButton ) ;
     
          if (PtInRect(&rcMenu, pt))
            lRet = HTSYSMENU;

          if (PtInRect(&rcMinButton, pt))
            lRet = HTMINBUTTON ;
          else
            if (PtInRect( &rcMaxButton, pt ))
              lRet = HTMAXBUTTON ;
          }
        }
      
      if (lRet != HTSYSMENU)
        SETMENUWASUPFLAG( hWnd, FALSE ) ;
      return lRet ;

    case WM_NCLBUTTONDBLCLK:
            // Windows recieve WM_NC?BUTTONDBLCLK messages whether they
            // have CS_DBLCLKS or not.  We watch for one of these
            // to see if the user double clicked on the system menu (to
            // close the window) or on the caption (to maximize the window).
            //
      if (!IsIconic( hWnd ) && HASCAPTION( hWnd ) && wP == HTSYSMENU) {
        SendMessage( hWnd, WM_CLOSE, 0, 0L ) ;
        break ;
        }
      return DefWindowProc( hWnd, uiMsg, wP, lP ) ;

    case WM_NCLBUTTONDOWN:
      {
      RECT rc ;

            // If we're iconic or we don't have a caption then 
            // DefWindowProc will do the job just fine.
            //            
      if (IsIconic( hWnd ) || !HASCAPTION( hWnd ))
        return DefWindowProc( hWnd, uiMsg, wP, lP ) ;

            // Here's were we handle the system menu, the min and max buttons.
            // If you wanted to change the behavior of the min/max buttons
            // do something like swap tool palettes or something, you 
            // would change the SendMessage() calls below.
            //
      switch (wP) {
        case HTSYSMENU:
          if (GETMENUWASUPFLAG( hWnd ) == FALSE && DoMenu( hWnd ))
            SETMENUWASUPFLAG( hWnd, TRUE ) ;
          else
            SETMENUWASUPFLAG( hWnd, FALSE ) ;
          break ;
                
        case HTMINBUTTON:
          GetMinButtonRect( hWnd, &rc ) ;
                    // Note that DepressMinMaxButton() goes into
                    // a PeekMessage() loop waiting for the mouse
                    // to come back up.
                    //
          if (DepressMinMaxButton( hWnd, wP, &rc ))
            SendMessage( hWnd, WM_SYSCOMMAND, SC_MINIMIZE, lP ) ;
          break ;
                
        case HTMAXBUTTON:
          GetMaxButtonRect( hWnd, &rc ) ;
                    // Note that DepressMinMaxButton() goes into
                    // a PeekMessage() loop waiting for the mouse
                    // to come back up.
                    //
          if (DepressMinMaxButton( hWnd, wP, &rc )) {
            if (IsZoomed(hWnd))
              SendMessage( hWnd, WM_SYSCOMMAND, SC_RESTORE, lP ) ;
            else
              SendMessage( hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, lP ) ;
            }
          break ;
                
        default:
                    // Well, it appears as though the user clicked somewhere other
                    // than the buttons.  We let DefWindowProc do it's magic.
                    // This is where things like dragging and sizing the
                    // window happen.
                    //
          return DefWindowProc( hWnd, uiMsg, wP, lP ) ;
        }
      }
      break ;

    case WM_SETTEXT:
      lRet = DefWindowProc (hWnd,uiMsg,wP,lP);
    case WM_NCPAINT:
    case WM_NCACTIVATE:
      {
      if (IsIconic(hWnd))
        return DefWindowProc (hWnd, uiMsg, wP, lP);

      RECT  rc, rcWnd;
      HDC   hDC = GetWindowDC(hWnd);

      ActiveDlg = NULL;
      CurrentDlg = NULL;
      for (LPDLGSTRUCT lpdlg = FirstDlg; lpdlg != NULL; lpdlg = lpdlg->Next)
        if (lpdlg->hWnd == hWnd) {
          if (uiMsg == WM_NCACTIVATE)
            ActiveDlg = lpdlg;
          CurrentDlg = lpdlg;
          break;
          }

      if (uiMsg == WM_NCPAINT) {
        GetWindowRect (hWnd, LPRECT(&rcWnd));

        int cx = rcWnd.right - rcWnd.left-1;
        int cy = rcWnd.bottom - rcWnd.top-1;

#ifdef WIN32
        HBRUSH BkBrush = HBRUSH(GetClassLong (hWnd, GCL_HBRBACKGROUND));
#else
        HBRUSH BkBrush = HBRUSH(GetClassWord (hWnd, GCW_HBRBACKGROUND));
#endif

        HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, BkBrush);

        int dx = 0, dy = 0;
        if (TestWinStyle(hWnd, WS_THICKFRAME) || TestWinStyle(hWnd, WS_BORDER)) {
          dx = GetSystemMetrics(SM_CXFRAME);
          dy = GetSystemMetrics(SM_CYFRAME);
          }
        else
        if (TestWinStyle(hWnd, DS_MODALFRAME)) {
          dx = GetSystemMetrics(SM_CXDLGFRAME) + GetSystemMetrics(SM_CXBORDER);
          dy = GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYBORDER);
          }
            
        PatBlt (hDC, 0, 0, dx, cy, PATCOPY);
        PatBlt (hDC, 0, 0, cx, dy, PATCOPY);
        PatBlt (hDC, cx-dx, 0, dx, cy, PATCOPY);
        PatBlt (hDC, 0, cy-dy, cx, dy, PATCOPY);
        SelectObject (hDC, OldBrush);

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

        DeleteObject (SelectObject (hDC, OldPen));
        }

      if (HASCAPTION (hWnd)) {
        RECT  rcCap;
        BOOL  fActive;

        GetCaptionRect (hWnd, &rcCap) ;    // Convert to window coords
        GetWindowRect (hWnd, &rc) ;
        OffsetRect (&rcCap, -rc.left, -rc.top);

//        if (uiMsg == WM_SETTEXT) {
//          *CurrentDlg->cfCaption = LPSTR(lP);
//          }

        if ((uiMsg == WM_NCPAINT) || (uiMsg == WM_SETTEXT))
          fActive = (hWnd == GetActiveWindow());
        else {
          lRet = DefWindowProc (hWnd, uiMsg, wP, lP);
          fActive = wP;
          }

        DrawCaption( hDC, hWnd, &rcCap,
                     TestWinStyle(hWnd, WS_CAPTION),
                     TestWinStyle(hWnd, WS_SYSMENU),
                     TestWinStyle(hWnd, WS_MINIMIZEBOX),
                     TestWinStyle(hWnd, WS_MAXIMIZEBOX),
                     fActive ) ;

        }
      
      ReleaseDC( hWnd, hDC ) ;
      return lRet;
      }
      break;

    default:
      return DefWindowProc( hWnd, uiMsg, wP, lP ) ;
    }
  return 0L ;
  } // ibDefWindowProc()



//  ibAdjustWindowRect( HWND hWnd, LPRECT lprc )
//
//    Does the same thing as the USER function AdjustWindowRect(),
//    but knows about itsybitsy windows.  AdjustWindowRect() is
//    bogus for stuff like this.
//

VOID WINAPI ibAdjustWindowRect (HWND hWnd, LPRECT lprc)
  {
  short    cx = 0, cy = 0 ;
  UINT     nCapSize ;
    
  nCapSize = GETCAPTIONHEIGHT( hWnd ) ;
    
  // First check Windows's styles, then our own.
  //
  if (TestWinStyle( hWnd, WS_THICKFRAME )) {
    cx = GetSystemMetrics( SM_CXFRAME ) ;
    cy = GetSystemMetrics( SM_CYFRAME ) ;
    }
  else
  if (TestWinStyle(hWnd, DS_MODALFRAME )) {
    cx = GetSystemMetrics( SM_CXDLGFRAME ) + GetSystemMetrics( SM_CXBORDER ) ;
    cy = GetSystemMetrics( SM_CYDLGFRAME ) + GetSystemMetrics( SM_CYBORDER ) ;
    }
  else
  if (TestWinStyle(hWnd, WS_BORDER )) {
    cx = GetSystemMetrics( SM_CXBORDER ) ;
    cy = GetSystemMetrics( SM_CYBORDER ) ;
    }
    
  InflateRect (lprc, cx, cy);
    
  if (TestWinStyle (hWnd, WS_CAPTION))
    lprc->top -= nCapSize ;

  } // ibAdjustWindowRect() 


///////////////////////////////////////////////////////////////////////
// Internal functions
///////////////////////////////////////////////////////////////////////

// DepressMinMaxButton()
//
// This function is called when the user has pressed either the min or
// max button (i.e. WM_NCLBUTTONDOWN).  We go into a Peekmessage() loop,
// waiting for the mouse to come back up.  This allows us to make the
// button change up/down state like a real button does.
//
// lprc points to the rectangle that describes the button the
// user has clicked on.
//
BOOL NEAR PASCAL DepressMinMaxButton( HWND hWnd, UINT uiHT, LPRECT lprc )
{             
    BOOL    fDepressed = TRUE ;
    MSG     msg ;
                      
    // Draw button in down state
    DrawButton( NULL, hWnd, uiHT == HTMINBUTTON, fDepressed ) ;
    SetCapture( hWnd ) ;
    
    while (TRUE)
    {
        if (PeekMessage((LPMSG)&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
        {
            switch (msg.message)
            {
                case WM_LBUTTONUP:
                    if (fDepressed)
                        DrawButton( NULL, hWnd, uiHT == HTMINBUTTON, !fDepressed ) ;
                    ReleaseCapture();
                return PtInRect( lprc, msg.pt ) ;
                
                case WM_MOUSEMOVE:
                    if (PtInRect( lprc, msg.pt ))
                    {
                        if (!fDepressed)
                            DrawButton( NULL, hWnd, uiHT == HTMINBUTTON, fDepressed = TRUE ) ;
                    }
                    else
                    {
                        if (fDepressed)
                            DrawButton( NULL, hWnd, uiHT == HTMINBUTTON, fDepressed = FALSE ) ;
                    }
                break;
            }
        }
    }
    
} // DepressMinMaxButton()  

// DrawCaption( HDC hDC, HWND hWnd, LPRECT lprc,
//                   BOOL fCapt, BOOL fSysMenu, BOOL fActive )
//
//    This function draws an itsy bitsy caption bar with or
//    without system menu to the dc specified by hDC.  The
//    caption is drawn to fit within the lprc RECT and is
//    drawn//withOut/ borders.
//
BOOL NEAR PASCAL DrawCaption (HDC hDC, HWND hWnd, LPRECT lprc,
                              BOOL fCapt, BOOL fSysMenu, BOOL fMin, 
                              BOOL fMax, BOOL fActive)
  {
  RECT        rcCap ;
  COLORREF    rgbCaptionBG ;
  COLORREF    rgbText ;
  COLORREF    rgbWindowFrame ;
  UINT        ui ;
  UINT        nCapSize ;
    
  nCapSize = GETCAPTIONHEIGHT (hWnd) ;
    
  // Farben für die Caption ermitteln
  rgbWindowFrame = GetSysColor(COLOR_WINDOWFRAME);
    
  // haben wir den Focus nehmen wir die "Aktiv-Farbe"
  // sonst zeichne mit der "Inaktiv-Farbe"   
  if (fActive) {
    rgbText = GetSysColor (COLOR_CAPTIONTEXT) ;
    rgbCaptionBG = GetSysColor (COLOR_ACTIVECAPTION);
    }
  else {
    if (fWin31)
      rgbText = RGBGRAY;
//      rgbText = GetSysColor(COLOR_INACTIVECAPTIONTEXT);
    else
      rgbText = GetSysColor(COLOR_CAPTIONTEXT);
//    rgbCaptionBG = GetSysColor (COLOR_INACTIVECAPTION);
    rgbCaptionBG = RGBLTGRAY;
    }

  rcCap = *lprc;   // die wirklichen Ausdehnungen der Caption
    
  if (fSysMenu) {              // bei System-Menue wird die Caption um deren Groesse verringert
    if (fCapt)
      rcCap.left += nCapSize;
    }
    
  if (fMax) {                  // bei Maximize-Button wird die Caption um dessen Groesse verringert
    if (fCapt)
      rcCap.right -= nCapSize ;
    }
    
  if (fMin) {                  // bei Minimize-Button wird die Caption um dessen Groesse verringert
    if (fCapt)
      rcCap.right -= nCapSize ;
    }

  COLORREF OldBack = SetBkColor (hDC, rgbCaptionBG);
  if (fCapt)    // die eigentliche Caption mit dem Text zeichnen
    DRAWFASTRECT (hDC, &rcCap);

  SetBkColor (hDC, OldBack);

  // 3D- Linien um die Caption zeichnen
  HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, rcCap.left, rcCap.bottom-1, NULL);
  LineTo (hDC, rcCap.right, rcCap.bottom-1);
  LineTo (hDC, rcCap.right, rcCap.top);
  SelectObject (hDC, OldPen);

  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGBGRAY));
  MoveToEx (hDC, rcCap.left, rcCap.bottom-1, NULL);
  LineTo (hDC, rcCap.left, rcCap.top);
  LineTo (hDC, rcCap.right-1, rcCap.top);
  DeleteObject (SelectObject (hDC, OldPen));
    
  // Draw caption text here.  Only do it in 3.1 'cause 3.1 gives
  // us 'small fonts'.
  //
  ui = GetWindowTextLength (hWnd);   // gibt die Länge des Titeltextes zurück

  if (CurrentDlg != NULL) {
    LPSTR szTitle = (LPSTR)GetGlobMem(ui+1);
    GetWindowText (hWnd, szTitle, ui+1);

    *(CurrentDlg->cfCaption) = szTitle;
    CurrentDlg->cfCaption->SetOutColor (rgbText);

    rcCap.left += 5;
    SetTwips (hDC, rcCap.left/*+DlgBorder()*/, rcCap.top);
    CurrentDlg->cfCaption->Paint (hDC, 0, FALSE);
    SetMMText (hDC);
    rcCap.left -= 5;

    CurrentDlg->cfCaption->UseDefOutColor ();
    FreeGlobMem (szTitle);
    }

    
  if (fSysMenu)
    DrawSysMenu (hDC, hWnd, FALSE ) ;
    
  if (fMin)
    DrawButton( hDC, hWnd, TRUE, FALSE ) ;

  if (fMax)
    DrawButton( hDC, hWnd, FALSE, FALSE ) ;
    
  return TRUE ;
    
} // DrawCaption()


// DrawSysMenu( HDC hDC, hWnd, BOOL fInvert )
//
// Draws the little system menu icon.
//
VOID NEAR PASCAL DrawSysMenu (HDC hDC, HWND hWnd, BOOL fInvert)
  {
  RECT         rcIcon ;
  RECT         rcTemp ;
  RECT         rc ;
  COLORREF     rgbIconFace ;
  COLORREF     rgbWindowFrame ;
  BOOL         fDC ;
  UINT         nCapSize ;
        
  nCapSize = GETCAPTIONHEIGHT( hWnd ) ;
    
  if (!hDC) {
    fDC = TRUE ;
    hDC = GetWindowDC (hWnd);
    }
  else
    fDC = FALSE ;
    
  if (hDC) {
    rgbIconFace    = GetNearestColor (hDC, RGBLTGRAY);
    rgbWindowFrame = GetSysColor (COLOR_WINDOWFRAME);
        
    GetIconRect (hWnd, &rcIcon);
    GetWindowRect (hWnd, &rc);
           
    OffsetRect (&rcIcon, -rc.left, -rc.top);
        
    rcTemp = rcIcon;
        
    if (TestWinStyle(hWnd, WS_CAPTION)) {
      rc = rcIcon ;      // separator line
      rc.left = ++rc.right - 1 ;
      }

    SetBkColor (hDC, RGBWHITE);
    DRAWFASTRECT (hDC, &rcTemp);

    rcTemp.left++;
    rcTemp.top++;
    SetBkColor (hDC, RGBGRAY);
    DRAWFASTRECT (hDC, &rcTemp);
    
    rcTemp.right--;
    rcTemp.bottom--;

    // zeichnet die graue Fläche
    SetBkColor (hDC, rgbIconFace);
    DRAWFASTRECT (hDC, &rcTemp);
        
    // Draw separator line
    SetBkColor (hDC, rgbWindowFrame);
    DRAWFASTRECT (hDC, &rc);

    rc.left = rcIcon.left;
    rc.top = rcIcon.bottom;
    rc.bottom++;
    DRAWFASTRECT (hDC, &rc);
        
    if (nCapSize > 4) {
      // Draw the little horizontal doo-hickey
      //
      rcTemp.top = rcIcon.top + ((nCapSize-1) / 2) ;
      rcTemp.bottom = rcTemp.top + 3 ;
      rcTemp.left  = rcTemp.left + 3 ; 
      rcTemp.right = rcTemp.right - 1 ;
                
      SetBkColor (hDC, RGBGRAY);
      DRAWFASTRECT (hDC, &rcTemp);
                
      rc = rcTemp;
      OffsetRect (&rc, -1, -1 );
      SetBkColor (hDC, RGBBLACK);
      DRAWFASTRECT(hDC, &rc);
                
      InflateRect (&rc, -1, -1);
      SetBkColor (hDC, RGBWHITE);
      DRAWFASTRECT (hDC, &rc);
      }
        
    if (fInvert)
      InvertRect (hDC, &rcIcon);
    
    if (fDC)
      ReleaseDC (hWnd, hDC);
    }
  } // DrawSysMenu()


// DoMenu( HWND hWnd )
//
//    Pops up the system menu.
//
BOOL NEAR PASCAL DoMenu( HWND hWnd )
{
    HDC    hDC ;
    RECT   rcIcon ;
    RECT   rc ;
    POINT  pt ;
    HMENU  hMenu ;
    DWORD  dw ;

    if (!TestWinStyle(hWnd, WS_SYSMENU))
        return FALSE ;
    
    if (hDC = GetWindowDC( hWnd ))
    {
        // Invert the icon
        //
        DrawSysMenu( hDC, hWnd, TRUE ) ;
        
        // Pop up the menu
        //
        if (TestWinStyle( hWnd, WS_CAPTION ))
        {
            pt.x = 0 ;
            pt.y = -1 ;
        }
        
        GetIconRect( hWnd, &rcIcon ) ;
        GetWindowRect( hWnd, &rc ) ;
        OffsetRect( &rcIcon, -rc.left, -rc.top ) ;
        
        ClientToScreen( hWnd, &pt ) ;
        ClientToScreen( hWnd, (LPPOINT)&rc.right ) ;
        
        dw = GetWindowLong( hWnd, GWL_STYLE ) ;
        SetWindowLong( hWnd, GWL_STYLE, dw | WS_SYSMENU ) ;
        
        hMenu = GetSystemMenu( hWnd, FALSE ) ;
        SetupSystemMenu( hWnd, hMenu ) ;
        
        SetWindowLong( hWnd, GWL_STYLE, dw ) ;

        TrackPopupMenu( hMenu, 0, //TPM_LEFTALIGN,
                    pt.x,
                    pt.y,
                    0,
                    hWnd,
                    &rc ) ;
    
        DrawSysMenu( hDC, hWnd, FALSE ) ;
        ReleaseDC( hWnd, hDC ) ;
    }
    return TRUE ;

} // DoMenu()

// SetupSystemMenu( HWND hWnd, HMENU hMenu )
//
//    Enables/Disables the appropriate menu items on the
//    menu passed for the window passed.
//
void NEAR PASCAL SetupSystemMenu( HWND hWnd, HMENU hMenu )
{
    UINT     wMove ;        
    UINT     wSize ;
    UINT     wMinBox ;
    UINT     wMaxBox ;
    UINT     wRestore ;
    
    // Assume all should be grayed.
    //
    wSize = wMove = wMinBox = wMaxBox = wRestore = MF_GRAYED ;
    
    if (TestWinStyle( hWnd, WS_MAXIMIZEBOX ) || IsIconic( hWnd ))
        wMaxBox = MF_ENABLED ;
    
    if (TestWinStyle( hWnd, WS_MINIMIZEBOX ))
        wMinBox = MF_ENABLED ;
    
    if (IsZoomed( hWnd ))
        wRestore = MF_ENABLED ;

    if (!IsZoomed( hWnd ) &&
        !IsIconic( hWnd ) &&
        TestWinStyle( hWnd, WS_CAPTION ) )
        wMove = MF_ENABLED ;
    
    EnableMenuItem( hMenu, SC_MOVE,     wMove ) ;
    EnableMenuItem( hMenu, SC_SIZE,     wSize ) ;
    EnableMenuItem( hMenu, SC_MINIMIZE, wMinBox ) ;
    EnableMenuItem( hMenu, SC_MAXIMIZE, wMaxBox ) ;
    EnableMenuItem( hMenu, SC_RESTORE,  wRestore ) ;
                        
} // SetupSystemMenu()

//-----------------------------------------------------------------
// GetCaptionRect( HWND hWnd, LPRECT lprc )
//
//    calculates the rectangle of the mini-caption in screen coords.
//
BOOL NEAR PASCAL GetCaptionRect (HWND hWnd, LPRECT lprc)
  {
  UINT nCapSize;
    
  nCapSize = GETCAPTIONHEIGHT (hWnd);
    
  if (!HASCAPTION (hWnd)) {
    SetRectEmpty (lprc);
    return FALSE;
    }
    
  GetWindowRect (hWnd, lprc);
    
  // the window might have other non-client components like
  // borders 
  //
  if (TestWinStyle (hWnd, WS_THICKFRAME)) {
    lprc->left += GetSystemMetrics (SM_CXFRAME);
    lprc->top  += GetSystemMetrics (SM_CYFRAME);
    lprc->right -= GetSystemMetrics (SM_CXFRAME);
    lprc->bottom -= GetSystemMetrics (SM_CYFRAME);
    }
  else
    if (TestWinStyle (hWnd, DS_MODALFRAME)) { // if it's a dialog box
      lprc->left += GetSystemMetrics( SM_CXDLGFRAME ) + GetSystemMetrics( SM_CXBORDER ) ;
      lprc->top  += GetSystemMetrics( SM_CYDLGFRAME ) + GetSystemMetrics( SM_CYBORDER ) ;
      lprc->right -= GetSystemMetrics( SM_CXDLGFRAME ) + GetSystemMetrics( SM_CXBORDER ) ;
      lprc->bottom -= GetSystemMetrics( SM_CYDLGFRAME ) + GetSystemMetrics( SM_CYBORDER ) ;
      }
  else
    if (TestWinStyle (hWnd, WS_BORDER)) {
      lprc->left += GetSystemMetrics(SM_CXFRAME);
      lprc->top  += GetSystemMetrics(SM_CYFRAME);
      lprc->right -= GetSystemMetrics(SM_CXFRAME);
      lprc->bottom -= GetSystemMetrics(SM_CYFRAME);
      }
    
  if (TestWinStyle (hWnd, WS_CAPTION)) {
//    InflateRect (lprc, -DlgBorder(), -DlgBorder());  // Caption wird ordentlich eingerückt
    lprc->bottom = lprc->top + nCapSize ;
    }
    
  return TRUE ;
  } // GetCaptionRect()

// GetIconRect( HWND hWnd, LPRECT lprc )
//
//    Calculates the rect of the icon in screen coordinates.
//
BOOL NEAR PASCAL GetIconRect (HWND hWnd, LPRECT lprc)
  {
  UINT    nCapSize ;
  BOOL    fMenu, fCapt ;

  fMenu= TestWinStyle (hWnd, WS_SYSMENU);
  fCapt = TestWinStyle (hWnd, WS_CAPTION);

  if (!GetCaptionRect (hWnd, lprc))   // window coords
    return FALSE ;

  if (!fMenu) {
    SetRectEmpty( lprc ) ;
    return FALSE ;
    }

  nCapSize = GETCAPTIONHEIGHT (hWnd);

  if (fCapt)
    lprc->right = lprc->left + nCapSize;  // quadratrisches SysMenu-Icon
    
  lprc->bottom-- ;
  lprc->right-- ;
    
  return TRUE ;
  } // GetIconRect()

// GetMinButtonRect()
//
// Calculates the rect of the minimize button in screen
// coordinates.
//
// For horizontal captions, we have the following situation ('Y' is minimize
// and '^' is maximize or restore):
//
//   +---------------------------------+
//   | - |                     | Y | ^ |
//   +---------------------------------+
//   |                         |.......| <-- This is the width (nSize)
//
// For vertical captions, we have the following:
//
//   |  |
//   |  |
//   |  |
//   |  |
//   |  |
//   |  |
//   |--|--
//   | Y| .
//   |--| . <-- This is the height of the rectangle (nSize)
//   | ^| .
//   +--+--
//
// In order to figure out where the minimize button goes, we first need
// to know if there is a maximize button.  If so, use GetMaxButtonRect()
// to place...
//
BOOL NEAR PASCAL GetMinButtonRect( HWND hWnd, LPRECT lprc )
{
    if (!TestWinStyle( hWnd, WS_MINIMIZEBOX )) 
    {
        SetRectEmpty( lprc ) ;
        return FALSE ;
    }

    // The minimize button can be in either position 1 or 2.  If there
    // is a maximize button, it's in position 2.
    //
    if (TestWinStyle( hWnd, WS_MAXIMIZEBOX ))
        return GetButtonRect( hWnd, 2, lprc ) ;
    else
        return GetButtonRect( hWnd, 1, lprc ) ;
}

// GetMaxButtonRect()
//
// Calculates the rect of the maximize button in screen
// coordinates.
//
// The maximize button, if present, is always to the far right
// or bottom.
//
BOOL NEAR PASCAL GetMaxButtonRect( HWND hWnd, LPRECT lprc )
{
    //The maximize button can only be in position 1.
    //
    if (TestWinStyle( hWnd, WS_MAXIMIZEBOX ))
        return GetButtonRect( hWnd, 1, lprc ) ;
    else
    {
        SetRectEmpty( lprc ) ;
        return FALSE ;
    }
}

// Get the rect where a button would go. 
// 
// This function does not care if it's a min or max, just whether
// it is the first from the right/bottom or second from the right/bottom
// and so on..
//
BOOL NEAR PASCAL GetButtonRect( HWND hWnd, UINT nPos, LPRECT lprc )
{
    UINT    nSize = 0 ;

    if (!GetCaptionRect( hWnd, lprc ))   //window coords
      return FALSE ;

    nSize = GETCAPTIONHEIGHT( hWnd ) ;

    if (TestWinStyle( hWnd, WS_CAPTION))
    {
        lprc->right -= nSize * (nPos-1) ;
        lprc->left = lprc->right - nSize + 1 ;
    }

    return TRUE ;
} // GetButtonRect()

// DrawButton( HDC hDC, HWND hWnd, BOOL fMin, BOOL fDepressed )
// 
// Draws either the min, max, or restore buttons. If fMin is FALSE then it
// will draw either the Max or Restore button.  If fDepressed is TRUE it will
// draw the button in a down state.
//
VOID NEAR PASCAL DrawButton( HDC hDC, HWND hWnd, BOOL fMin, BOOL fDepressed)
{
    RECT            rcButton ;
    RECT            rc ;
    COLORREF        rgbWindowFrame ;
    BOOL            fDC ;
    UINT            nCapSize ;
    UINT            nOffset ;
    int             n ;

    nCapSize = GETCAPTIONHEIGHT( hWnd ) ;

    // If you look at the standard Windows' min/max buttons, you will notice
    // that they have two pixels of 'shadow' to the bottom and right.  Since
    // our buttons can be really, really small, we only want one pixel of 
    // shadow when they are small.  I arbitrarily decided that if the 
    // caption size is greater than or equal to 20 we will use two
    // pixels.  That's what this THREASHOLD stuff does.
    //
    #define THRESHOLD   20
    nOffset = (nCapSize >= THRESHOLD) ? 2 : 1 ;    

    if (!hDC)
    {
        fDC = TRUE ;
        hDC = GetWindowDC( hWnd ) ;
    }
    else
        fDC = FALSE ;
    
    if (hDC)
    {
        rgbWindowFrame = GetSysColor( COLOR_WINDOWFRAME ) ;
        
        if (fMin)
            GetMinButtonRect( hWnd, &rcButton ) ;
        else
            GetMaxButtonRect( hWnd, &rcButton ) ;
        
        GetWindowRect( hWnd, &rc ) ;
        OffsetRect( &rcButton, -rc.left, -rc.top ) ;
        
        rc = rcButton ;
        if (TestWinStyle( hWnd, WS_CAPTION))
        {
            rc = rcButton ;     //separator line
            rc.right = --rc.left + 1 ;
            rcButton.bottom-- ;
        }
        
        //Draw separator line
        SetBkColor( hDC, rgbWindowFrame ) ;
        DRAWFASTRECT( hDC, &rc ) ;
        
        //Fill
        SetBkColor( hDC, RGBLTGRAY ) ;
        DRAWFASTRECT( hDC, &rcButton ) ;
        
        if (!fDepressed)
        {
            //The normal min/max buttons have one pixel on the top and left
            //sides for the highlight, and two pixels on the bottom and
            //right side for the shadow.
            //
            //When our caption is 'small' we only use one pixel on all
            //sides.
            //
            SetBkColor( hDC, RGBWHITE ) ;
            //Draw left side
            rc = rcButton ;
            rc.right = rc.left + 1 ;
            DRAWFASTRECT( hDC, &rc ) ;

            //Draw Top
            rc = rcButton ;
            rc.bottom = rc.top + 1 ;
            DRAWFASTRECT( hDC, &rc ) ;

            SetBkColor( hDC, RGBGRAY ) ;
            //Draw right side
            rc = rcButton ;
            rc.left = rc.right - 1 ;
            DRAWFASTRECT( hDC, &rc ) ;
            if (nCapSize > THRESHOLD)
            {
                rc.left-- ;
                rc.top++ ;
                DRAWFASTRECT( hDC, &rc ) ;
            }

            //Draw bottom
            rc = rcButton ;
            rc.top = rc.bottom - 1 ;
            DRAWFASTRECT( hDC, &rc ) ;
            if (nCapSize > THRESHOLD)
            {
                rc.top-- ;
                rc.left++ ;
                DRAWFASTRECT( hDC, &rc ) ;
            }

            rcButton.left++ ;
            rcButton.top++ ;
            rcButton.right -= nOffset ;
            rcButton.bottom -= nOffset ;
        }
        else
        {
            //Draw depressed state

            SetBkColor( hDC, RGBGRAY ) ;
            //Draw left side
            rc = rcButton ;
            rc.right = rc.left + nOffset ;
            DRAWFASTRECT( hDC, &rc ) ;

            //Draw Top
            rc = rcButton ;
            rc.bottom = rc.top + nOffset ;
            DRAWFASTRECT( hDC, &rc ) ;

            rcButton.left += 2 * nOffset ;
            rcButton.top += 2 * nOffset ;
        }

        // Now draw the arrows.  We do not want the
        // arrows to grow too large when we have a bigger than
        // normal caption, so we restrict their size.
        //
        // rcButton now represents where we can place our
        // arrows.  
        //
        // The maximum size of our arrows (i.e. the width of rcButton)
        // has been empirically determined to be SM_CYCAPTION / 2
        //
        n = ((GetSystemMetrics( SM_CYCAPTION )) / 2) - 
            (rcButton.right - rcButton.left) ;
        if (n < 1)
            InflateRect( &rcButton, n/2-1, n/2-1 ) ;

        if (fMin)
            DrawArrow( hDC, &rcButton, ARROW_DOWN ) ;
        else 
            if (IsZoomed( hWnd ))
            {
                DrawArrow( hDC, &rcButton, ARROW_RESTORE ) ;
            }
            else
                DrawArrow( hDC, &rcButton, ARROW_UP ) ;
        
        if (fDC)
            ReleaseDC( hWnd, hDC ) ;
    }

} // DrawButton()


// DrawArrow
//
// Draws either a up or down arrow.  The arrow is bound by the rectangle
//
VOID NEAR PASCAL DrawArrow( HDC hdc, LPRECT lprc, UINT uiStyle )
{
    int     row ;
    int     xTip ;
    int     yTip ;
    RECT    rc ;
    int     nMax = (lprc->bottom - lprc->top) >> 1 ;

    SetBkColor( hdc, RGBBLACK ) ;

    // We draw the arrow by drawing a series of horizontal lines
    //
    xTip = lprc->left + ((lprc->right - lprc->left+1) >> 1) ;
    switch (uiStyle)
    {
        case ARROW_UP:
            yTip = lprc->top + ((lprc->bottom - lprc->top-1) >> 2) ;
            for (row = 1 ; row <= nMax ; row++ )
            {
                rc.left = xTip - row ;
                rc.right = xTip + row - 1 ;
                rc.top = yTip + row ;
                rc.bottom = rc.top + 1 ;
                DRAWFASTRECT( hdc, &rc ) ;
            }
        break ;

        case ARROW_DOWN:
            yTip = lprc->bottom - ((lprc->bottom - lprc->top-1) >> 2) ;
            for ( row = nMax ; row > 0 ; row-- )
            {
                rc.left = xTip - row ;
                rc.right = xTip + row - 1 ;
                rc.top = yTip - row ;
                rc.bottom = rc.top + 1 ;
                DRAWFASTRECT( hdc, &rc ) ;
            }
        break ;

        case ARROW_RESTORE:
        default:
            yTip = lprc->top + ((lprc->bottom - lprc->top-1) >> 3) - 2;
            for (row = 1 ; row <= nMax ; row++ )
            {
                rc.left = xTip - row ;
                rc.right = xTip + row - 1 ;
                rc.top = yTip + row ;
                rc.bottom = rc.top + 1 ;
                DRAWFASTRECT( hdc, &rc ) ;
            }

            yTip += (nMax+1) * 2 ;
            for ( row = nMax ; row > 0 ; row-- )
            {
                rc.left = xTip - row ;
                rc.right = xTip + row - 1 ;
                rc.top = yTip - row ;
                rc.bottom = rc.top + 1 ;
                DRAWFASTRECT( hdc, &rc ) ;
            }
        break ;
    }

}  // DrawArrow()   

// This function is obsolete.  Some of my apps still call it
// though so that's why it's still here.
//
BOOL WINAPI ibInit( HANDLE hInstance )
{
    return TRUE ;
}

/////////////////////////////////////////////////////////////////////////
// End of File: itsybits.c
/////////////////////////////////////////////////////////////////////////
