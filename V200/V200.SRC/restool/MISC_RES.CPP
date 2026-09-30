/////////////////////////////////////////////////////////////////////////
//  Dialogbox zum Suchen
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/misc_res.cpv   1.11   26 Mar 1999 18:14:18   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/misc_res.cpv  $
// 
//    Rev 1.11   26 Mar 1999 18:14:18   Wolfgang
// 1.) Funktionen zum Setzen der Case-Sensitiven- und Wort-Suche neu.
// 2.) OnVKReturn braucht caseSensitive-Parameter.
// 
//    Rev 1.10   12 Mar 1999 13:51:08   Wolfgang
// 1.) Suchtext auch waehrend der Suche in Combo-Box anzeigen.
// 
//    Rev 1.9   05 Oct 1998 11:27:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.8   04 May 1998 11:16:24   Gerhold
// ReplaceCombo ... zusaetzlicher Parameter BOOL InsertEmptyString fuer INI
// 
//    Rev 1.7   05 Nov 1997 09:08:04   Gerhold
// 32 Bit
// 
//    Rev 1.6   28 Aug 1997 15:50:06   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.5   21 Oct 1996 18:57:52   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.4   02 Feb 1996 10:50:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   23 Aug 1995 11:05:24   GERHOLD
// 
//    Rev 1.2   07 Jun 1995 12:12:14   GERHOLD
// Suchen und Ersetzen jetzt mit Common-Dialogs realisiert
// 
//    Rev 1.1   02 Jan 1995 09:31:04   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   14 Sep 1994 09:44:30   GERHOLD
// Initial revision.
// 
//    Rev 1.0   14 Sep 1994 09:43:10   GERHOLD
// Initial revision.
// 
//    Rev 1.0   12 Jul 1994 14:44:16   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "rlist.hpp"
#include <dlgs.h>
#include <commdlg.h>
#include "misc.hpp"
#define MODULENUM 119
#include "winass.hpp"
#include "blandmdi.hpp"      // Get-, SetRasterUnits
#include "msdntb.h"

typedef UINT (CALLBACK *DLGHOOKPROC)(HWND, UINT, WPARAM, LPARAM);


HWND            hDlgFind;               //FindText modeless dialog handle
FINDREPLACE     frFind;                 //Persistent structure for FindText
HWND            hDlgReplace;            //ReplaceText modeless dialog handle
char            szFind[256];            //Search string for ReplaceText
char            szReplace[256];         //Replace string for ReplaceText

extern HWND hWndCombo;
extern HINSTANCE MyInstance;
extern HWND hWndToolbar;

/*
 * LSearchMessageHandler
 *
 * Purpose:
 *  Processes the FINDMSGSTRING registered message sent from the
 *  find and replace modeless dialogs.  Various bits in pFR->Flags
 *  instruct us what to do, that is, terminate the dialog, find
 *  the next occurance in the search, replace an occurance, or
 *  replace all occurances.  Simply put, these flags indicate which
 *  button the user pressed.
 *
 * Parameters:
 *  hWnd            HWND of the parent window.
 *  pFR             LPFINDREPLACE pointer to either the frFind or
 *                  frReplace globals we used to call FindText or
 *                  ReplaceText, depending on which dialog box
 *                  originated this message.
 *
 * Return Value:
 *  LONG            Value to return from the main window procedure.
 */

static BOOL act_doCaseSensitive = FALSE ;
static BOOL act_doWholeWord = FALSE ;

void SetDoWholeWord (BOOL value)
  {
  act_doWholeWord = value;
  SendMessage (hWndToolbar, TB_CHECKBUTTON, MI_SEARCHWORD, MAKELPARAM(act_doWholeWord,0));
  }

void SetDoCaseSensitive (BOOL value)
  {
  act_doCaseSensitive = value;
  SendMessage (hWndToolbar, TB_CHECKBUTTON, MI_SEARCHCASE, MAKELPARAM(act_doCaseSensitive,0));
  }

LONG FAR PASCAL LSearchMessageHandler (HWND hWnd, LPFINDREPLACE pFR)
  {
  static BOOL JustCanceled = TRUE;

  if (pFR->Flags & FR_DIALOGTERM) {
    /*
     * The dialog is closing on the Close button.  Therefore we must
     * invalidate the handle we saved from FindText or ReplaceText.
     * Since we have two window handles for these dialogs we have to
     * determine which one to invalidate.  Since the FINDMSGSTRING
     * message does not distinguish the two dialogs, we have stored
     * a non-zero in the FINDREPLACE structure's lCustData for
     * FindText and a zero for ReplaceText.
     */

    // bei sofortigem Cancel der Dialog-Box (ohne mind. einem Suchvorgang),
    // wird der Originalzustand der Such-Combo-Box wieder hergestellt.
    if (JustCanceled) {
      SendMessage (hWndCombo, WM_SETTEXT, 0, LPARAM(SearchCombo.GetTopString()));
      JustCanceled = TRUE;
      }
    
    if (pFR->lCustData)
      hDlgFind = NULL;
    else
      hDlgReplace = NULL;

    return 0L;
    }

  /*
   * Perform your searching here.  
   */
  SetDoWholeWord ((pFR->Flags & FR_WHOLEWORD) != 0);
  SetDoCaseSensitive ((pFR->Flags & FR_MATCHCASE) != 0);

  if (pFR->lCustData) {
    SearchCombo.OnVKReturn (GetDlgItem (hDlgFind,cmb1), FALSE, act_doCaseSensitive);
    SearchCombo.FillCombo (hWndCombo);
    SendMessage (hWndCombo, WM_SETTEXT, 0, LPARAM(SearchCombo.GetTopString()));
    if (pFR->Flags & FR_DOWN)
      SendMessage (hWnd, WM_COMMAND, MI_SEARCHMORE, 1L);
    else
      SendMessage (hWnd, WM_COMMAND, MI_SEARCHUP, 1L);
    }
  else {
    SearchCombo.OnVKReturn (GetDlgItem (hDlgReplace,cmb1), FALSE, act_doCaseSensitive);
    SearchCombo.OnInit (hWndCombo);
    if (pFR->Flags & FR_FINDNEXT)
      SendMessage (hWnd, WM_COMMAND, MI_SEARCHMORE, 1L);
    else if (pFR->Flags & FR_REPLACE) {
      ReplaceCombo.OnVKReturn (GetDlgItem (hDlgReplace,cmb2), TRUE, act_doCaseSensitive);
      SendMessage (hWnd, WM_COMMAND, MI_REPLACEMORE, 1L);
      }
    else if (pFR->Flags & FR_REPLACEALL) {
      ReplaceCombo.OnVKReturn (GetDlgItem (hDlgReplace,cmb2), TRUE, act_doCaseSensitive);
      SendMessage (hWnd, WM_COMMAND, MI_REPLACEALL, 1L);
      }
    }

  return 0L;
  }

BOOL doWholeWord()
  {
  return act_doWholeWord ;
  }

BOOL doCaseSensitive()
  {
  return act_doCaseSensitive ;
  }

DLLExport LONG _export FAR PASCAL FindHook (HWND hDlg, UINT msg, WPARAM wP, LPARAM lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      {
      SearchCombo.FillCombo (GetDlgItem(hDlg, cmb1));
      if (!frFind.lCustData) {
        ReplaceCombo.FillCombo (GetDlgItem(hDlg, cmb2));
        }
      return TRUE;
      }
      break;
      
    }

  return FALSE;  
  }

/*
 * SearchDialogs
 *
 * Purpose:
 *  Invokes the FindText and ReplaceText common dialogs.
 *
 * Parameters:
 *  hWndOwner       HWND to use as the owner of the dialog.
 *  iDialog         WORD indicating which dialog variation to invoke.
 *
 * Return Value:
 *  HWND            Handle to the invoked dialog, NULL on failure.
 */

HWND FAR PASCAL SearchDialogs (HWND hWndOwner, WORD iDialog, LPSTR SearchStr, LPSTR ReplaceStr)
  {
  HWND hDlg = NULL;
  static DLGHOOKPROC FindHookProc;
  if (FindHookProc == NULL) 
    FindHookProc = (DLGHOOKPROC) MakeProcInstance ((FARPROC)FindHook,MyInstance);

  /*
   * NOTE:  Since we pass a pointer to the FINDREPLACE structure for
   * a modeless dialog, the structure must persist outside the scope of
   * this function, that is, it must be static or global.  We use a
   * different structure for FindText and ReplaceText since we allow
   * both dialogs to be active at one time.
   */

  SearchCombo.InsertEntry (SearchStr,FALSE);
  switch (iDialog) {
    case MI_SEARCH:
      if (hDlgFind)
          break;

      lmemset (&frFind, '\0', sizeof(FINDREPLACE));
      frFind.lStructSize = sizeof(FINDREPLACE);
      frFind.hwndOwner = hWndOwner;

      frFind.lpstrFindWhat = szFind;
      lstrcpy (szFind,SearchStr);
      frFind.wFindWhatLen = sizeof(szFind);
  
      frFind.Flags = FR_DOWN | FR_ENABLETEMPLATE | FR_ENABLEHOOK;
      frFind.hInstance = MyInstance;
      frFind.lpTemplateName = "FINDDLG";
      frFind.lpfnHook = FindHookProc;

      /*
       * For our own purposes, use lCustData to distinguish
       * an invocation of Find vs. and invocation or Replace
       * within the message processing for FINDMSGSTRING.  Otherwise
       * there's no way to distinguish where that message originated.
       */

      frFind.lCustData = 1L;
      if (act_doWholeWord)      frFind.Flags |= FR_WHOLEWORD;
      if (act_doCaseSensitive)  frFind.Flags |= FR_MATCHCASE;

      hDlgFind = FindText(&frFind);
      
      hDlg = hDlgFind;
      /*
       * FindText returns as soon as the dialog is up. Therefore we
       * have to manage memory and so forth when we are told it's
       * closing.  Memory for the FINDREPLACE structure and the
       * lpstrFindWhat string both must be global or static.
       */
      break;


    case MI_REPLACE:
      if (hDlgReplace)
        break;

      lmemset (&frFind, '\0', sizeof(FINDREPLACE));
      frFind.lStructSize = sizeof(FINDREPLACE);
      frFind.hwndOwner = hWndOwner;

      frFind.lpstrFindWhat = szFind;
      lstrcpy (szFind,SearchStr);
      frFind.wFindWhatLen = sizeof(szFind);

      lstrcpy (szReplace, ReplaceStr);
      frFind.lpstrReplaceWith = szReplace;
      ReplaceCombo.ReadEntrys (TRUE);
      lstrcpy (szReplace, ReplaceCombo.GetTopString());
      frFind.wReplaceWithLen = sizeof(szReplace);

      frFind.Flags = FR_ENABLETEMPLATE | FR_ENABLEHOOK;
      frFind.hInstance = MyInstance;
      frFind.lpTemplateName = "REPLACEDLG";
      frFind.lpfnHook = FindHookProc;

      frFind.lCustData = 0L;
      if (act_doWholeWord)      frFind.Flags |= FR_WHOLEWORD;
      if (act_doCaseSensitive)  frFind.Flags |= FR_MATCHCASE;

      hDlgReplace = ReplaceText (&frFind);
      hDlg = hDlgReplace;
      break;
    }

  return hDlg;
  }

int FAR *adx,FAR *ady;
DLLExport BOOL FAR PASCAL _export MoveDialogProc (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      SetDlgItemInt (hDlg,ID_MOVEDX,0,TRUE);
      SetDlgItemInt (hDlg,ID_MOVEDY,0,TRUE);
      break ;
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          {
          BOOL done1,done2;
          *adx = GetDlgItemInt (hDlg,ID_MOVEDX,&done1,TRUE);
          *ady = GetDlgItemInt (hDlg,ID_MOVEDY,&done2,TRUE);
          if ((done1) && (done2))
            EndDialog (hDlg,TRUE);
          else
            MessageBeep (0);
          }
          break ;
        case IDCANCEL :
          EndDialog (hDlg,FALSE);
          break ;
        }
      break ;
    }
  return RetVal;
  }

BOOL MoveDialog (HWND hWnd,int FAR *dx,int FAR *dy)
  {
  adx = dx ;
  ady = dy ;
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(MoveDialogProc),MyInstance));
  BOOL res = DialogBox (MyInstance,"MOVEDIALOG",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  return res;
  }

static BOOL IsSettingRect ;
static int xStart,yStart;
static int x1old,y1old;
#define IVKOORD   -32767
BOOL SR_LButtonDown (HWND hWnd,int x,int y)
  {
  IsSettingRect = TRUE ;
  SetCapture (hWnd);
  xStart = x ;
  yStart = y ;
  x1old = y1old = IVKOORD;
  return TRUE ;
  }
BOOL PaintRectangle (HWND hWnd,int x,int y,BOOL PaintLast)
  {
  if ((x != x1old) || (y != y1old) || (PaintLast)) {
    HDC hDC = GetDC (hWnd);
    SelectObject (hDC,GetStockObject (WHITE_PEN));
    SelectObject (hDC,GetStockObject (NULL_BRUSH));
    SetROP2 (hDC,R2_XORPEN);
    if (x1old != IVKOORD) {
      Rectangle (hDC,xStart,yStart,x1old,y1old);
      }
    if (!PaintLast) {
      x1old = x ;
      y1old = y ;
      Rectangle (hDC,xStart,yStart,x1old,y1old);
      }
    ReleaseDC (hWnd,hDC);
    return TRUE ;
    }
  return FALSE ;
  }
void StartScrolling (HWND hWnd)
  {
  if (IsSettingRect) {
    HDC hDC = GetDC (hWnd);
    SelectObject (hDC,GetStockObject (WHITE_PEN));
    SelectObject (hDC,GetStockObject (NULL_BRUSH));
    SetROP2 (hDC,R2_XORPEN);
    if (x1old != IVKOORD) {
      Rectangle (hDC,xStart,yStart,x1old,y1old);
      }
    x1old = IVKOORD;
    ReleaseDC (hWnd,hDC);
    }
  }
void EndScrolling (HWND hWnd,int dx,int dy)
  {
  if (IsSettingRect) {
    LONG l = GetMessagePos();
    POINT pt;
    pt.x = LOWORD(l);
    pt.y = HIWORD(l);
    ScreenToClient (hWnd,&pt);
    xStart += dx ;
    yStart += dy ;
    PaintRectangle (hWnd,pt.x,pt.y,FALSE);
    }
  }
inline void ExChange (int FAR &x1,int FAR &x2)
  {
  int dummy = x1 ;
  x1 = x2 ;
  x2 = dummy ;
  }

inline void ExChange (long FAR &x1,long FAR &x2)
  {
  long dummy = x1 ;
  x1 = x2 ;
  x2 = dummy ;
  }

LONG SR_CheckMSG (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done)
  {
  LONG RetVal = 0;
  *done = FALSE ;
  if (IsSettingRect) {
    switch (msg) {
      case WM_MOUSEMOVE :
        {
        *done = TRUE ;
        int x = LOWORD(lP);
        int y = HIWORD(lP);
        PaintRectangle (hWnd,x,y,FALSE);
        }
        break ;
      case WM_LBUTTONUP :
        {
        *done = TRUE ;
        int x = LOWORD(lP);
        int y = HIWORD(lP);
        ReleaseCapture ();
        IsSettingRect = FALSE ;
        if (PaintRectangle (hWnd,x,y,TRUE)) {
          RECT r;
          r.left   = xStart ;
          r.top    = yStart ;
          r.right  = x ;
          r.bottom = y ;
          if (r.left > r.right)  ExChange (r.left,r.right);
          if (r.top  > r.bottom) ExChange (r.top,r.bottom);
          SelectElems (hWnd,&r);
          InvalidateRect (hWnd,NULL,TRUE);
          }
        else
          MessageBeep (0);
        }
        break ;
      }
    }
  return RetVal ;
  }

////////////////////////////////////////////////////////////
//  Tracking im Formulareditor
////////////////////////////////////////////////////////////
BOOL TimerIsSet;
#define TRACKTIMERID  1002
#define TRACKTIMEOUT  150
static void GetFullClientRect (HWND hWnd,LPRECT r)
  {
  GetWindowRect (hWnd,r);
  ScreenToClient (hWnd,LPPOINT(&r->left));
  ScreenToClient (hWnd,LPPOINT(&r->right));
  }
static void SetTimerIfNecessary (HWND hWnd,int x,int y)
  {
  if (!TimerIsSet) {
    RECT r;
    GetFullClientRect (hWnd,&r);
    if ((x < r.left) || (x > r.right) || (y < r.top) || (y > r.bottom)) {
      SetTimer (hWnd,TRACKTIMERID,TRACKTIMEOUT,NULL);
      TimerIsSet = TRUE ;
      }
    }
  }
static void DoScroll (HWND hWnd,int x,int y,BOOL pressed)
  {
  if (pressed) {
    RECT r;
    GetFullClientRect (hWnd,&r);
    if (x < r.left)
      SendMessage (hWnd,WM_HSCROLL,SB_LINEUP,0L);
    if (x > r.right)
      SendMessage (hWnd,WM_HSCROLL,SB_LINEDOWN,0L);
    if (y < r.top)
      SendMessage (hWnd,WM_VSCROLL,SB_LINEUP,0L);
    if (y > r.bottom)
      SendMessage (hWnd,WM_VSCROLL,SB_LINEDOWN,0L);
    }
  if (TimerIsSet)
    KillTimer (hWnd,TRACKTIMERID);
  TimerIsSet = FALSE;
  }
LONG TrackMsgProc (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done)
  {
  LONG RetVal = 0L;
  *done = FALSE ;
  switch (msg) {
    case WM_MOUSEMOVE :
      if (wP & MK_LBUTTON)
        SetTimerIfNecessary (hWnd,LOWORD(lP),HIWORD(lP));
      break ;
    case WM_TIMER :
      {
      if (wP == TRACKTIMERID) {
        LONG l = GetMessagePos ();
        POINT pt;
        pt.x = LOWORD(l);
        pt.y = HIWORD(l);
        ScreenToClient(hWnd,&pt);
        BOOL pressed = (GetAsyncKeyState (VK_LBUTTON) < 0) ;
        DoScroll (hWnd,pt.x,pt.y,pressed);
        if (pressed)
          SetTimerIfNecessary (hWnd,pt.x,pt.y);
        *done = TRUE ;
        }
      }
      break ;
    }
  return RetVal ;
  }

extern HWND hRefWnd;
void WriteInCaption (LPSTR txt)
  {
  static int oldLeft;
  if (IsWindow (hRefWnd)) {
    HDC hDC = GetWindowDC (hRefWnd);
    SetTextColor (hDC,RGB(0xFF,0,0));
    SetBkColor (hDC,GetSysColor (COLOR_MENU));
    SetTextAlign (hDC,TA_BOTTOM | TA_RIGHT);
    int len = lstrlen(txt);
    RECT rcWnd;
    RECT rTxt;
    GetWindowRect (hRefWnd,&rcWnd);
    rTxt.bottom = GetSystemMetrics (SM_CYCAPTION) + 
                  GetSystemMetrics (SM_CYMENU) + 
                  2 * GetSystemMetrics (SM_CYBORDER) ;
    rTxt.top    = rTxt.bottom - (GetSystemMetrics (SM_CYMENU)
                                - 2 * GetSystemMetrics (SM_CYBORDER)
                                );
    int rc = GetSystemMetrics (SM_CXVSCROLL);
    rTxt.right  = rcWnd.right - rcWnd.left - 20 - rc;

    int cx, cy;
#ifdef WIN32
    SIZE size;
    GetTextExtentPoint32 (hDC, txt, len, &size);
    cx = size.cx;
    cy = size.cy;
#else
    DWORD gte = GetTextExtent (hDC,txt,len);
    cx = LOWORD(gte);
    cy = HIWORD(gte);
#endif

    rTxt.left   = rTxt.right - cx - 20 - rc;
    if ((oldLeft > 0) && (rTxt.left > oldLeft))
      rTxt.left = oldLeft;
    ExtTextOut (hDC,rcWnd.right - rcWnd.left - 30 - rc,
                rTxt.bottom,
                ETO_OPAQUE | ETO_CLIPPED,
                &rTxt,
                txt,
                len,
                LPINT (NULL)
              );
    oldLeft = rTxt.left;
    ReleaseDC (hRefWnd,hDC);
    }
  }
void WriteInCaption (int x,int y)
  {
  char outtxt[32];
  wsprintf (outtxt,"X: %d,Y: %d",x,y);
  WriteInCaption (outtxt);
  }


#define ID_X     1000
#define ID_Y     1001
//---------------------------------------------------------------------------
//
// Dialog zum Einstellen des Rasters im Formulareditor
//
//---------------------------------------------------------------------------
DLLExport BOOL FAR PASCAL _export RasterDialogProc (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  int rx, ry;

  switch (msg) {
    case WM_INITDIALOG :
      GetRasterUnits (&rx, &ry);
      SetDlgItemInt (hDlg,ID_X,rx,TRUE);
      SetDlgItemInt (hDlg,ID_Y,ry,TRUE);
      break ;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          {
          BOOL done1,done2;
          rx = GetDlgItemInt (hDlg,ID_X,&done1,TRUE);
          ry = GetDlgItemInt (hDlg,ID_Y,&done2,TRUE);
          if ((done1) && (done2) && (rx != 0) && (ry != 0)) {
            SetRasterUnits (rx, ry);
            EndDialog (hDlg,TRUE);
            }
          else
            MessageBeep (0);
          }
          break ;
        case IDCANCEL :
          EndDialog (hDlg,FALSE);
          break ;
        }
      }
      break ;
    }
  return RetVal;
  }


void GetRasterDialog (HWND hWnd)
  {
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(RasterDialogProc),MyInstance));
  BOOL res = DialogBox (MyInstance,"RASTERDIALOG",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  }
