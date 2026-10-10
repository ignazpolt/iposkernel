/*
 * MUSCROLL.C
 *
 * Contains the main window procedure of the MicroScroll control
 * that handles mouse logic, and Windows messages.
 *
 * Version 1.1, October 1991, Kraig Brockschmidt
 */
  /*COPYRIGHT:

     (C) Copyright Microsoft Corp. 1993.  All rights reserved.
 
     You have a royalty-free right to use, modify, reproduce and
     distribute the Sample Files (and/or any modified version) in
     any way you find useful, provided that you agree that
     Microsoft has no warranty obligations or liability for any
     Sample Application Files which are modified.*/
 


#include <windows.h>
#define NO_MEMORY_CHECK
#include "dds32.h"
#include "muscrdll.hpp"
#include "muexport.hpp"


//extern LONG PASCAL LMicroScrollAPI(HWND, WORD, WORD, LONG, LPMUSCROLL);


/*
 * MicroScrollWndProc
 *
 * Purpose:
 *  Window Procedure for the MicroScroll custom control.  Handles all
 *  messages like WM_PAINT just as a normal application window would.
 *  Any message not processed here should go to DefWindowProc.
 *
 * Parameters:
 *  hWnd            HWND handle to the control window.
 *  iMsg            WORD message identifier.
 *  wParam          WORD parameter of the message.
 *  lParam          LONG parameter of the message.
 *
 * Return Value:
 *  LONG            Varies with the message.
 *
 */

DLLExport LONG FAR PASCAL _export MicroScrollWndProc(HWND hWnd, UINT iMsg,
                   WPARAM wParam, LPARAM lParam)
  {
  LPMUSCROLL      lpMS;
  POINT           pt;
  RECT            rect;
  short           x, y;
  short           cx, cy;
  WORD            wState;


  /*
   * Get a pointer to the MUSCROLL structure for this control.
   * Note that if we do this before WM_NCCREATE where we allocate
   * the memory, lpMS will be NULL, which is not a problem since
   * we do not access it until after WM_NCCREATE.
   */
  lpMS = (LPMUSCROLL)GetWindowLong (hWnd, GWW_MUSCROLLHMEM);

  //Let the API handler process WM_USER+xxxx messages
  if (iMsg >= WM_USER)
    return LMicroScrollAPI (hWnd, iMsg, wParam, lParam, lpMS);

  //Handle standard Windows messages.
  switch (iMsg) {
    case WM_NCCREATE:
    case WM_CREATE:
      return LMicroScrollCreate(hWnd, iMsg, lpMS, (LPCREATESTRUCT)lParam);

    case WM_NCDESTROY:
      //Free the control's memory.
      GlobalUnlock (hglb);
      GlobalFree (hglb);
//    FreeGlobMem (lpMS);
      break;

    case WM_ERASEBKGND:
      /*
       * Eat this message to avoid erasing portions that
       * we are going to repaint in WM_PAINT.  Part of a
       * change-state-and-repaint strategy is to rely on
       * WM_PAINT to do anything visual, which includes
       * erasing invalid portions.  Letting WM_ERASEBKGND
       * erase the background is redundant.
       */
      break;


    case WM_PAINT:
      return LMicroScrollPaint(hWnd, lpMS);


    case WM_ENABLE:
      /*
       * Handles disabling/enabling case.  Example of a
       * change-state-and-repaint strategy since we let the
       * painting code take care of the visuals.
       */
      if (wParam)
        StateClear(lpMS, MUSTATE_GRAYED);
      else
        StateSet(lpMS, MUSTATE_GRAYED);

      //Force a repaint since the control will look different.
      InvalidateRect(hWnd, NULL, TRUE);
      UpdateWindow(hWnd);
      break;


    case WM_SHOWWINDOW:
      /*
       * Set or clear the hidden flag. Windows will
       * automatically force a repaint if we become visible.
       */
      if (wParam)
        StateClear(lpMS, MUSTATE_HIDDEN);
      else
        StateSet(lpMS, MUSTATE_HIDDEN);

      break;


    case WM_CANCELMODE:
      /*
       * IMPORTANT MESSAGE!  WM_CANCELMODE means that a
       * dialog or some other modal process has started.
       * we must make sure that we cancel any clicked state
       * we are in, kill the timers, and release the capture.
       */
      StateClear(lpMS, MUSTATE_DOWNCLICK | MUSTATE_UPCLICK);
      KillTimer(hWnd, IDT_FIRSTCLICK);
      KillTimer(hWnd, IDT_HOLDCLICK);
      ReleaseCapture();
      break;


    case WM_TIMER:
      /*
       * We run two timers:  the first is the initial delay
       * after the first click before we begin repeating, the
       * second is the repeat rate.
       */
      if (wParam == IDT_FIRSTCLICK) {
        KillTimer (hWnd, wParam);
        SetTimer (hWnd, IDT_HOLDCLICK, CTICKS_HOLDCLICK, NULL);
        }

      /*
       * Send a new scroll message if the mouse is still in the
       * originally clicked area.
       */
      if (!StateTest(lpMS, MUSTATE_MOUSEOUT))
        PositionChange(hWnd, lpMS);

      break;


    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
      /*
       * When we get a mouse down message, we know that the mouse
       * is over the control.  We then do the following steps
       * to set up the new state:
       *  1.  Hit-test the coordinates of the click to
       *      determine in which half the click occurred.
       *  2.  Set the appropriate MUSTATE_*CLICK state
       *      and repaint that clicked half.  This is another
       *      example of a change-state-and-repaint strategy.
       *  3.  Send an initial scroll message.
       *  4.  Set the mouse capture.
       *  5.  Set the initial delay timer before repeating
       *      the scroll message.
       *
       * A WM_LBUTTONDBLCLK message means that the user clicked
       * the control twice in succession which we want to treat
       * like WM_LBUTTONDOWN.  This is safe since we will receive
       * WM_LBUTTONUP before the WM_LBUTTONDBLCLK.
       */

      //Get the mouse coordinates.
      x=LOWORD(lParam);
      y=HIWORD(lParam);

      /*
       * Only need to hit-test the upper half for a vertical
       * control or the left half for a horizontal control.
       */
      GetClientRect(hWnd, &rect);
      cx=rect.right  >> 1;
      cy=rect.bottom >> 1;

      if (MSS_VERTICAL & lpMS->dwStyle)
        wState= (y > cy) ? MUSTATE_DOWNCLICK : MUSTATE_UPCLICK;
      else
        wState=(x > cx) ? MUSTATE_RIGHTCLICK : MUSTATE_LEFTCLICK;

      //Change-state-and-repaint
      StateSet(lpMS, wState);
      ClickedRectCalc(hWnd, lpMS, &rect);
      InvalidateRect(hWnd, &rect, TRUE);
      UpdateWindow(hWnd);

      PositionChange(hWnd, lpMS);
      SetCapture(hWnd);
      SetTimer(hWnd, IDT_FIRSTCLICK, CTICKS_FIRSTCLICK, NULL);
      break;


    case WM_MOUSEMOVE:
      /*
       * On WM_MOUSEMOVE messages we want to know if the mouse
       * has moved out of the control when the control is in
       * a clicked state.  If the control has not been clicked,
       * then we have nothing to do.  Otherwise we want to set
       * the MUSTATE_MOUSEOUT flag and repaint so the button
       * visually comes up.
       */
      if (!StateTest(lpMS, MUSTATE_CLICKED))
        break;


      //Get the area we originally clicked and the new POINT
      ClickedRectCalc(hWnd, lpMS, &rect);
      pt=MAKEPOINT(lParam);

      wState=lpMS->wState;

      //Hit-Test the rectange and change the state if necessary.
      if (PtInRect(&rect, pt))
        StateClear(lpMS, MUSTATE_MOUSEOUT);
      else
        StateSet(lpMS, MUSTATE_MOUSEOUT);

      /*
       * If the state changed, repaint the appropriate part of
       * the control.
       */
      if (wState!=lpMS->wState) {
        InvalidateRect(hWnd, &rect, TRUE);
        UpdateWindow(hWnd);
        }

      break;


    case WM_LBUTTONUP:
      /*
       * A mouse button up event is much like WM_CANCELMODE since
       * we have to clean out whatever state the control is in:
       *  1.  Kill any repeat timers we might have created.
       *  2.  Release the mouse capture.
       *  3.  Clear the clicked states and repaint, another example
       *      of a change-state-and-repaint strategy.
       */
      KillTimer(hWnd, IDT_FIRSTCLICK);
      KillTimer(hWnd, IDT_HOLDCLICK);

      ReleaseCapture();



      /*
       * Repaint if necessary, only if we are clicked AND the mouse
       * is still in the boundaries of the control.
       */
      if (StateTest(lpMS, MUSTATE_CLICKED) && StateTest(lpMS, ~MUSTATE_MOUSEOUT)) {
        //Calculate the rectangle before clearing states.
        ClickedRectCalc(hWnd, lpMS, &rect);

        //Clear the states so we repaint properly.
        StateClear(lpMS, MUSTATE_MOUSEOUT);
        StateClear(lpMS, MUSTATE_CLICKED);

        InvalidateRect(hWnd, &rect, TRUE);
        UpdateWindow(hWnd);
        }

      //Insure that we clear out the states.
      break;


    default:
      return DefWindowProc(hWnd, iMsg, wParam, lParam);
    }

  return 0L;
  }






/*
 * ClickedRectCalc
 *
 * Purpose:
 *  Calculates the rectangle of the clicked region based on the
 *  state flags MUSTATE_UPCLICK, MUSTATE_DOWNCLICK, MUSTATE_LEFTCLICK,
 *  and MUSTATE_RIGHTLICK, depending on the style.
 *
 * Parameter:
 *  hWnd            HWND handle to the control window.
 *  lpRect          LPRECT rectangle structure to fill.
 *
 * Return Value:
 *  void
 *
 */

void PASCAL ClickedRectCalc(HWND hWnd, LPMUSCROLL lpMS, LPRECT lpRect)
    {
    short       cx, cy;

    GetClientRect(hWnd, lpRect);
    cx=lpRect->right  >> 1;
    cy=lpRect->bottom >> 1;

    if (MSS_VERTICAL & lpMS->dwStyle)
        {
        if (StateTest(lpMS, MUSTATE_DOWNCLICK))
            lpRect->top=cy;

        if (StateTest(lpMS, MUSTATE_UPCLICK))
            lpRect->bottom=1+cy;
        }
    else
        {
        //MSS_HORIZONTAL
        if (StateTest(lpMS, MUSTATE_RIGHTCLICK))
            lpRect->left=cx;

        if (StateTest(lpMS, MUSTATE_LEFTCLICK))
            lpRect->right=1+cx;
        }

    return;
    }





/*
 * PositionChange
 *
 * Purpose:
 *  Checks what part of the control is clicked, modifies the current
 *  position accordingly (taking MSS_INVERTRANGE into account) and
 *  sends an appropriate message to the associate.  For MSS_VERTICAL
 *  controls we send WM_VSCROLL messages and for MSS_HORIZONTAL controls
 *  we send WM_HSCROLL.
 *
 *  The scroll code in the message is always SB_LINEUP for the upper
 *  or left half of the control (vertical and horizontal, respectively)
 *  and SB_LINEDOWN for the bottom or right half.
 *
 *  This function does not send a message if the position is pegged
 *  on the minimum or maximum of the range if MSS_NOPEGSCROLL is
 *  set in the style bits.
 *
 * Parameters:
 *  hWnd            HWND of the control.
 *  lpMS             PMUSCROLL pointer to control data structure.
 *
 * Return Value:
 *  void
 */

void PASCAL PositionChange(HWND hWnd, LPMUSCROLL lpMS)
    {
    WORD         wScrollMsg;
    WORD         wScrollCode;
    BOOL         fPegged=FALSE;

    if (StateTest(lpMS, MUSTATE_UPCLICK | MUSTATE_LEFTCLICK))
        wScrollCode=SB_LINEUP;

    if (StateTest(lpMS, MUSTATE_DOWNCLICK | MUSTATE_RIGHTCLICK))
        wScrollCode=SB_LINEDOWN;

    wScrollMsg = (MSS_VERTICAL & lpMS->dwStyle) ? WM_VSCROLL : WM_HSCROLL;

    /*
     * Modify the current position according to the following rules:
     *
     * 1. On SB_LINEUP with an inverted range, increment the position.
     *    If the position is already at the maximum, set the pegged flag.
     *
     * 2. On SB_LINEUP with an normal range, decrement the position.
     *    If the position is already at the minimum, set the pegged flag.
     *
     * 3. On SB_LINEDOWN with an inverted range, treat like SB_LINEUP
     *    with a normal range.
     *
     * 4. On SB_LINEDOWN with an normal range, treat like SB_LINEUP
     *    with an inverted range.
     */

    if (wScrollCode == SB_LINEUP) {
      if (MSS_INVERTRANGE & lpMS->dwStyle) {
        if (lpMS->iPos == lpMS->iMax)
          fPegged=TRUE;
        else
          lpMS->iPos++;
        }
      else {
        if (lpMS->iPos==lpMS->iMin)
          fPegged=TRUE;
        else
          lpMS->iPos--;
        }
      }
    else {
      if (MSS_INVERTRANGE & lpMS->dwStyle) {
        if (lpMS->iPos==lpMS->iMin)
          fPegged=TRUE;
        else
          lpMS->iPos--;
        }
      else {
        if (lpMS->iPos==lpMS->iMax)
          fPegged=TRUE;
        else
          lpMS->iPos++;
        }
      }


    /*
     * Send a message if we changed and are not pegged, or did not change
     * and MSS_NOPEGSCROLL is clear.
     */
    if (!fPegged || !(MSS_NOPEGSCROLL & lpMS->dwStyle)) {
      SendMessage(lpMS->hWndAssociate, wScrollMsg, wScrollCode, MAKELONG(lpMS->iPos, hWnd));
      }

    return;
    }
