//--------------------------------------------------------------------------
// TOOLBAR - Hauptmodul
//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/toolbar/rev/msdntb.cpv   1.12   05 Oct 1998 11:51:50   Gerhold  $
//  $Log:   P:/marille/clinicum/toolbar/rev/msdntb.cpv  $
// 
//    Rev 1.12   05 Oct 1998 11:51:50   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   17 Nov 1997 08:13:24   Gerhold
// 32 Bit
// 
//    Rev 1.10   21 Oct 1996 18:54:20   HANNES
// 
//    Rev 1.9   02 Feb 1996 10:51:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   10 Aug 1995 09:25:08   GERHOLD
// Jetzt wird alles richtig freigegeben
// 
//    Rev 1.7   07 Aug 1995 20:54:46   GERHOLD
// TBD_REMOVETOOLBAR
// 
//    Rev 1.6   16 Feb 1995 12:44:18   GERHOLD
// 
//    Rev 1.5   24 Jan 1995 10:01:24   GERHOLD
// Einige doch wesentliche Aenderungen
// 
//    Rev 1.4   18 Jan 1995 12:12:48   GERHOLD
// weitere Einteilung in class TBButton und TBBmInfo
// 
//    Rev 1.3   13 Jan 1995 15:30:06   GERHOLD
// Popup-Fenster  praesentiert sich jetzt besser.
// 
//    Rev 1.2   10 Jan 1995 10:45:44   GERHOLD
// 
//    Rev 1.1   09 Jan 1995 09:40:50   GERHOLD
// 
//    Rev 1.0   02 Jan 1995 15:45:30   GERHOLD
// Initial revision.
//--------------------------------------------------------------------------
#include <windows.h>

#define NO_MEMORY_CHECK    // kein GGlobalAlloc,...
#include "dds32.h"

#include "msdntb.h"
#include "msdntbi.hpp"
#include <memory.h>

char szToolbarClass[7] = "MSDNTB";
char szPopupDockWindow[] = "POPUPDOCKWINDOW";

extern DLLExport LRESULT _export CALLBACK DockWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define DEFAULTBITMAPX   16
#define DEFAULTBITMAPY   15
#define DEFAULTBUTTONX   24
#define DEFAULTBUTTONY   22
#define DEFAULTBARHEIGHT (GetSystemMetrics (SM_CYMENU) * 2)

#define BUTTONSEPERATOR  8
#define FIRSTBUTTON      8
#define FIRSTY           4

DWORD  rgbFace;
DWORD  rgbShadow;
DWORD  rgbHilight;
DWORD  rgbFrame;

//
// hdcMono is the DC that holds a mono bitmap, hbmMono
// that is used to create highlights
// of button faces.
// hbmDefault hold the default bitmap if there is one.
//

WORD wStateMasks[] = {
    TBSTATE_ENABLED,
    TBSTATE_CHECKED,
    TBSTATE_PRESSED,
    TBSTATE_HIDDEN,
    TBSTATE_INDETERMINATE
  };


HINSTANCE hLibInst;              // Global instance handle for  DLL

DLLExport LONG _export FAR PASCAL ToolbarWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
DLLExport LONG _export FAR PASCAL PopupDockWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

HBITMAP CreateMappedBitmap(HINSTANCE hInstance, int idBitmap );
void FigureXSnap (LPWORD px, LPWORD py, LPTOOLBAR lpTB);
void DrawInvertFrame (LPRECT rcFrame, BOOL bPopup, LPTOOLBAR lpTB);


TBBmInfo::TBBmInfo (HINSTANCE hInstance, WORD wid, int nBtn, HBITMAP hBitmap)
  {
  nButtons = nBtn;
  hInst = hInstance;
  wID = wid;
  hbm = hBitmap;
  Next = NULL;
  }

TBBmInfo::~TBBmInfo ()
  {
  if (hInst && hbm)
    DeleteObject(hbm);
  }

TBButton::TBButton (LPTBBUTTON BtnStruct, LPTOOLBAR parent)
  {
  iBitmap = BtnStruct->iBitmap;
  idCommand = BtnStruct->idCommand;
  fsState = BtnStruct->fsState;
  fsStyle = BtnStruct->fsStyle;
  dwData = BtnStruct->dwData;
  iString = BtnStruct->iString;
  
  Next = NULL;
  Prev = NULL;

  x = 0;
  y = 0;
  if (fsStyle & TBSTYLE_SEP) {
    if (iBitmap <= 0) {
      dx = iBitmap = BUTTONSEPERATOR;
      dy = DEFAULTBUTTONY;
      }
    else {
      dx = iBitmap;
      int Height = LOWORD(dwData);
      if (Height)
        dy = Height;
      else  
        dy = DEFAULTBUTTONY;
      }  
    }
  else {
    dx = DEFAULTBUTTONX;
    dy = DEFAULTBUTTONY;
    }  

  Parent = parent;
  }


void PatB(HDC hdc,int x,int y,int dx,int dy, DWORD rgb)
  {
  RECT    rc;

  rc.left   = x;
  rc.top    = y;
  rc.right  = x + dx;
  rc.bottom = y + dy;

  SetBkColor(hdc,rgb);
  ExtTextOut(hdc,0,0,ETO_OPAQUE,&rc,NULL,0,NULL);
  }

//----------------------------------------------------------------------------
// create a mono bitmap mask:
//   1's where color == COLOR_BTNFACE || COLOR_HILIGHT
//   0's everywhere else
//----------------------------------------------------------------------------
void TBButton::CreateMask(int xoffset, int yoffset, int idx, int idy)
  {
  // initalize whole area with 1's
  PatBlt (Parent->hdcMono, 0, 0, idx, idy, WHITENESS);

  // create mask based on color bitmap
  // convert this to 1's
  SetBkColor(Parent->hdcGlyphs, rgbFace);
  BitBlt(Parent->hdcMono, xoffset, yoffset, DEFAULTBITMAPX, DEFAULTBITMAPY,
      Parent->hdcGlyphs, iBitmap * DEFAULTBITMAPX, 0, SRCCOPY);
  // convert this to 1's
  SetBkColor(Parent->hdcGlyphs, rgbHilight);
  // OR in the new 1's
  BitBlt(Parent->hdcMono, xoffset, yoffset, DEFAULTBITMAPX, DEFAULTBITMAPY,
      Parent->hdcGlyphs, iBitmap * DEFAULTBITMAPX, 0, SRCPAINT);
  }


void TBButton::DrawBlankButton(HDC hdc, int ix, int iy, int idx, int idy, WORD state)
  {
  // face color
  PatB(hdc, ix, iy, idx, idy, rgbFace);

  if (state & TBSTATE_PRESSED) {
    PatB(hdc, ix + 1, iy, idx - 2, 1, rgbFrame);
    PatB(hdc, ix + 1, iy + idy - 1, idx - 2, 1, rgbFrame);
    PatB(hdc, ix, iy + 1, 1, idy - 2, rgbFrame);
    PatB(hdc, ix + idx - 1, iy +1, 1, idy - 2, rgbFrame);
    PatB(hdc, ix + 1, iy + 1, 1, idy-2, rgbShadow);
    PatB(hdc, ix + 1, iy + 1, idx-2, 1, rgbShadow);
    }
  else {
    PatB(hdc, ix + 1, iy, idx - 2, 1, rgbFrame);
    PatB(hdc, ix + 1, iy + idy - 1, idx - 2, 1, rgbFrame);
    PatB(hdc, ix, iy + 1, 1, idy - 2, rgbFrame);
    PatB(hdc, ix + idx - 1, iy + 1, 1, idy - 2, rgbFrame);
    idx -= 2;
    idy -= 2;
    PatB(hdc, ix + 1, iy + 1, 1, idy - 1, rgbHilight);
    PatB(hdc, ix + 1, iy + 1, idx - 1, 1, rgbHilight);
    PatB(hdc, ix + idx, iy + 1, 1, idy, rgbShadow);
    PatB(hdc, ix + 1, iy + idy, idx, 1,   rgbShadow);
    PatB(hdc, ix + idx - 1, iy + 2, 1, idy - 2, rgbShadow);
    PatB(hdc, ix + 2, iy + idy - 1, idx - 2, 1,   rgbShadow);
    }
  }

void TBButton::DrawButton(HDC hdc/*, int x, int y, int dx, int dy, LPTBBUTTON ptButton*/)
  {
  int yOffset;
  HBRUSH hbrOld, hbr;
  BOOL bMaskCreated = FALSE;
  BYTE state;
  int xButton = 0;    // assume button is down
  int dxFace, dyFace;
  int xCenterOffset;
  
  int ix, iy, idx, idy;
  ix = x;
  iy = y;
  idx = dx;
  idy = dy;
  
  dxFace = dx;
  dyFace = dy;

  // make local copy of state and do proper overriding
  state = fsState;
  if (state & TBSTATE_INDETERMINATE) {
    if (state & TBSTATE_PRESSED)
      state &= ~TBSTATE_INDETERMINATE;
    else if (state & TBSTATE_ENABLED)
      state = TBSTATE_INDETERMINATE;
    else
      state &= ~TBSTATE_INDETERMINATE;
    }

    // get the proper button look - up or down.
  if (!(state & (TBSTATE_PRESSED | TBSTATE_CHECKED))) {
    xButton = dx; // use 'up' version of button
    dxFace -= 2;  
    dyFace -= 2;  // extents to ignore button highlight
    }

  DrawBlankButton(hdc, ix, iy, idx, idy, state);

  // move coordinates inside border and away from upper left highlight.
  // the extents change accordingly.
  ix += 2;
  iy += 2;
  dxFace -= 3;    
  dyFace -= 3;

  if (!Parent->SelectBM(Parent->hdcGlyphs, iBitmap))
    return;

  // calculate offset of face from (x,y).  y is always from the top,
  // so the offset is easy.  x needs to be centered in face.
  yOffset = 1;
  xCenterOffset = (dxFace - DEFAULTBITMAPX)/2;
  if (state & (TBSTATE_PRESSED | TBSTATE_CHECKED)) {
    // pressed state moves down and to the right
    // (x moves automatically as face size grows)
    yOffset++;
    }

  // now put on the face
  if (state & TBSTATE_ENABLED) {
    // regular version
    BitBlt(hdc, ix+xCenterOffset, iy + yOffset, DEFAULTBITMAPX, DEFAULTBITMAPY,
            Parent->hdcGlyphs, iBitmap * DEFAULTBITMAPX, 0, SRCCOPY);
    } 
  else {
    // disabled version (or indeterminate)
    bMaskCreated = TRUE;
    CreateMask(xCenterOffset, yOffset, dxFace, dyFace);

    SetTextColor(hdc, 0L);   // 0's in mono -> 0 (for ROP)
    SetBkColor(hdc, 0x00FFFFFF); // 1's in mono -> 1

    // draw glyph's white understrike
    if (!(state & TBSTATE_INDETERMINATE)) {
      hbr = CreateSolidBrush(rgbHilight);
      if (hbr) {
        hbrOld = (HBRUSH)SelectObject(hdc, hbr);
        if (hbrOld) {
          // draw hilight color where we have 0's in the mask
          BitBlt(hdc, ix + 1, iy + 1, dxFace, dyFace, Parent->hdcMono, 0, 0, 0x00B8074A);
          SelectObject(hdc, hbrOld);
          }
        DeleteObject(hbr);
        }
      }

    // gray out glyph
    hbr = CreateSolidBrush(rgbShadow);
    if (hbr) {
      hbrOld = (HBRUSH)SelectObject(hdc, hbr);
      if (hbrOld) {
        // draw the shadow color where we have 0's in the mask
        BitBlt(hdc, ix, iy, dxFace, dyFace, Parent->hdcMono, 0, 0, 0x00B8074A);
        SelectObject(hdc, hbrOld);
        }
      DeleteObject(hbr);
      }

    if (state & TBSTATE_CHECKED) {
      BitBlt(Parent->hdcMono, 1, 1, dxFace - 1, dyFace - 1, Parent->hdcMono, 0, 0, SRCAND);
      }
    }

  if (state & (TBSTATE_CHECKED | TBSTATE_INDETERMINATE)) {
    hbrOld = (HBRUSH)SelectObject(hdc, Parent->hbrDither);
    if (hbrOld) {
      if (!bMaskCreated)
        CreateMask(xCenterOffset, yOffset, dxFace, dyFace);

      SetTextColor(hdc, 0L);    // 0 -> 0
      SetBkColor(hdc, 0x00FFFFFF);  // 1 -> 1

      // only draw the dither brush where the mask is 1's
      BitBlt(hdc, ix, iy, dxFace, dyFace, Parent->hdcMono, 0, 0, 0x00E20746);
      
      SelectObject(hdc, hbrOld);
      }
    }
  }

BOOL TBButton::GetItemRect (HWND hWnd, LPRECT lpRect)
  {
  lpRect->left = x;
  lpRect->top = y;
  lpRect->right = x+dx;
  lpRect->bottom = y+dy;
  return(TRUE);
  }


BOOL TBButton::HitTest (int xPos, int yPos)
  {
  BOOL res = FALSE;
  if ((fsState & TBSTATE_HIDDEN) || (fsStyle & TBSTYLE_SEP))
    return res;

  if ((xPos >= x) && (yPos >= y) && (xPos <= (x+dx)) && (yPos <= (y+dy)))
    res = TRUE;
  
  return res;
  }

void TBButton::InvalidateButton (HWND hwnd)
  {
  RECT rc;

  if (GetItemRect (hwnd, &rc)) {
    InvalidateRect(hwnd, &rc, FALSE);
    }
  }



HBRUSH CreateSizeInvBrush (void)
  {
  HBITMAP hBM = (HBITMAP)LoadBitmap (hLibInst, "SIZEINV");
  HBRUSH  hBr = CreatePatternBrush (hBM);

  DeleteObject (hBM);
  return hBr;
  }
  


ToolBar::ToolBar (HWND ToolBarWindow, HWND hWndParent, LPSTR WindowName)
  {
  Result = 0;
  hParent = hWndParent;
  hWnd = ToolBarWindow;
  hWndDock = 0;
  hdcMono = NULL;
  hbmMono = NULL;
  hbmDefault = NULL;
  hdcGlyphs = NULL;           // globals for fast drawing
  hSizeInvBrush = CreateSizeInvBrush();
  hbrDither = NULL;

//  Title = WindowName;
  lstrcpy (Title, WindowName);

//  nSelectedBM = -1;
//  int iDitherCount = 0;
//  int iInitCount   = 0;
  ParentIsPopUp = FALSE;

  Next = NULL;
  FirstButton = NULL;
  FirstBitmap = NULL;
  SelectedBitmap = NULL;
  pCaptureButton = NULL;
  hWndCommand = GetParent (hWndParent);

  SetRectEmpty (LPRECT(&rcChild));
  SetRectEmpty (LPRECT(&rcPopup));
  SetRectEmpty (LPRECT(&rcMove));
  ptSave.x = 0;
  ptSave.y = 0;
  bMoveToolbar = FALSE;

  rcPopup.left = GetSystemMetrics (SM_CXSCREEN) / 3;
  rcPopup.top  = GetSystemMetrics (SM_CYSCREEN) / 3;

  if (CreateDitherBrush(FALSE)) {
    if (!InitGlobalObjects()) {
      Result = -1;
      }
    }  
  else
    Result = -1;  
/*    
      hglbTBHdr = GlobalAlloc (GPTR, sizeof(TBHDR)-sizeof(TBBUTTON));
      pTBHdr = (LPTBHDR) GlobalLock (hglbTBHdr);
      if (pTBHdr)
        hWndCommand = GetParent(hWndParent);
      else  
        Result = -1;
      }
    else {  
      FreeGlobalObjects();
      Result = -1;
      }
    }
  else
    Result = -1;    
*/
  }


ToolBar::~ToolBar ()
  {
//  if (pTBHdr) {
//    int i;

  FreeGlobalObjects();
  FreeDitherBrush();
  
    /* Free all the bitmaps before exiting
     */
  LPTBBMINFO NextBm;
  for (; FirstBitmap != NULL; ) {
    NextBm = FirstBitmap->Next;
    delete FirstBitmap;
    FirstBitmap = NextBm;
    }

  LPTBBUTT NextBtn;
  for (; FirstButton != NULL; ) {
    NextBtn = FirstButton->Next;
    delete FirstButton;
    FirstButton = NextBtn;
    }
    
    
/*     
    for (pTemp=pTBHdr->pBitmaps, i=pTBHdr->nBitmaps-1; i>=0; ++pTemp, i--) {
      if (pTemp->hInst && pTemp->hbm)
      DeleteObject(pTemp->hbm);
      }
  
    GlobalUnlock (hglbBMInfo);
    GlobalFree (hglbBMInfo);
    hglbBMInfo = NULL;
//            FREEWINDOWPOINTER(pTBHdr);
    GlobalUnlock (hglbTBHdr);
    GlobalFree (hglbTBHdr);
*/
//    }
  if (hSizeInvBrush)
    DeleteObject (hSizeInvBrush);
  }


BOOL ToolBar::InitGlobalObjects(void)
  {
  hdcGlyphs = CreateCompatibleDC(NULL);
  if (!hdcGlyphs)
    return FALSE;
  hdcMono = CreateCompatibleDC(NULL);
  if (!hdcMono)
    return FALSE;

  hbmMono = CreateBitmap(DEFAULTBUTTONX, DEFAULTBUTTONY, 1, 1, NULL);
  if (!hbmMono)
    return FALSE;

  hbmDefault = (HBITMAP)SelectObject(hdcMono, hbmMono);

//  iInitCount++;

  return TRUE;
  }


void ToolBar::FreeGlobalObjects ()
  {
//  --iInitCount;
/*
  if ( iInitCount )
    return;
*/
  if (hdcMono) {
    if (hbmDefault)
      SelectObject(hdcMono, hbmDefault);
    DeleteDC(hdcMono);    // toast the DCs
    }
  hdcMono = NULL;

  if (hdcGlyphs)
    DeleteDC(hdcGlyphs);
  hdcGlyphs = NULL;

  if (hbmMono)
    DeleteObject(hbmMono);
  hbmMono = NULL;
  }


/* Given a button number, the corresponding bitmap is loaded and selected in,
 * and the Window origin set.
 * Returns NULL on Error, 1 if the necessary bitmap is already selected,
 * or the old bitmap otherwise.
 */
HBITMAP ToolBar::SelectBM (HDC hDC, int nButton)
  {
  LPTBBMINFO pbm;
  HBITMAP hRet;
  int nBitmap, nTot;
  
  nBitmap = 0;
  nTot = 0;
  for (pbm = FirstBitmap; pbm != NULL; pbm = pbm->Next, ++nBitmap) {
    if (nButton < nTot + pbm->nButtons)
      break;
      
    nTot += pbm->nButtons;  
    }
    
  if (pbm == NULL)
    return (NULL);
    
  // Special case when the required bitmap is already selected
  if (pbm == SelectedBitmap)
    return((HBITMAP)1);

  // kein Bitmap oder es konnte nicht geladen werden
  if (!pbm->hbm || (hRet = (HBITMAP)SelectObject(hDC, pbm->hbm)) == NULL) {
    if (pbm->hbm)
      DeleteObject(pbm->hbm);

    if (pbm->hInst)
      pbm->hbm = CreateMappedBitmap(pbm->hInst, pbm->wID);
    else
      pbm->hbm = (HBITMAP)pbm->wID;

    if (!pbm->hbm || (hRet = (HBITMAP)SelectObject(hDC, pbm->hbm)) == NULL)
      return(NULL);
    }

  SelectedBitmap = pbm;
  SetWindowOrgEx (hDC, nTot * DEFAULTBITMAPX, 0, NULL);
  
  return(hRet);
  }


void ToolBar::ToolbarPaint ()
  {
  RECT        rc, rcWnd;
  HDC         hdc;
  PAINTSTRUCT ps;
  HBITMAP     hbmOldGlyphs;
  int         iCacheWidth = 0;
  int         dx,dy;
  LPTBBUTT    pb;
  
  GetSysColors();

  hdc = BeginPaint(hWnd, &ps);

  GetClientRect(hWnd, &rc);
  CopyRect  (&rcWnd, &rc);

  if (!rc.right)
    goto Error1;

  // Zeichnet oben eine weiße Linie und unten eine dunkelgraue Linie
  RECT rcLine;
  COLORREF    OldBack;

  OldBack = SetBkColor (hdc, rgbFace);

  ExtTextOut (hdc, 0, 0, ETO_OPAQUE, &rcWnd, NULL, 0, NULL);

  SetBkColor (hdc, rgbHilight);
  CopyRect (&rcLine, &rc);
  rcLine.bottom = rcLine.top+1;
  ExtTextOut (hdc, 0, 0, ETO_OPAQUE, &rcLine, NULL, 0, NULL);

  CopyRect (&rcLine, &rc);
  rcLine.right = rcLine.left+1;
  ExtTextOut (hdc, rcLine.left, rcLine.top, ETO_OPAQUE, &rcLine, NULL, 0, NULL);
  
  SetBkColor (hdc, rgbShadow);
  CopyRect (&rcLine, &rc);
  rcLine.top = rc.bottom-1;
  ExtTextOut (hdc, 0, rcLine.top, ETO_OPAQUE, &rcLine, NULL, 0, NULL);

  CopyRect (&rcLine, &rc);
  rcLine.left = rcLine.right-1;
  ExtTextOut (hdc, rcLine.left, rcLine.top, ETO_OPAQUE, &rcLine, NULL, 0, NULL);
  SetBkColor (hdc, OldBack);

  dx = DEFAULTBUTTONX;         // 24
  dy = DEFAULTBUTTONY;         // 22

  SelectedBitmap = NULL;
  hbmOldGlyphs = SelectBM(hdcGlyphs, 0);
  if (!hbmOldGlyphs)
    goto Error1;

  for (pb = FirstButton; pb != NULL; pb = pb->Next)
    if (!((pb->fsState & TBSTATE_HIDDEN) || (pb->fsStyle == TBSTYLE_SEP)))
      pb->DrawButton (hdc);
  
  SelectObject(hdcGlyphs, hbmOldGlyphs);

Error1:
  EndPaint(hWnd, &ps);
  }




LPTBBUTT ToolBar::TBHitTest (int xPos, int yPos)
  {
  for (LPTBBUTT pb = FirstButton; pb != NULL; pb = pb->Next)
    if (pb->HitTest(xPos, yPos)) 
      return pb;

  return NULL;
  }


int ToolBar::PositionFromID (int id)
  {
  int i;

  i = 0;
  for (LPTBBUTT pb = FirstButton; pb != NULL; pb = pb->Next, i++)
    if (pb->idCommand == id)
      return i;

  return -1;    // ID not found!
  }

LPTBBUTT ToolBar::ButtonFromID (int id)
  {
  int i = 0;
  for (LPTBBUTT pb = FirstButton; pb != NULL; pb = pb->Next, i++)
    if (pb->idCommand == id)
      return pb;

  return NULL;    // ID not found!
  }


// check a radio button by button index.
// the button matching idCommand was just pressed down.  this forces
// up all other buttons in the group.
// this does not work with buttons that are forced up with
void ToolBar::MakeGroupConsistant(HWND hWnd, int idCommand)
  {
  LPTBBUTT pFirst, pLast;
  
  LPTBBUTT pButton = ButtonFromID (idCommand);
  if (pButton == NULL)
    return;

  if (!(pButton->fsState & TBSTATE_CHECKED))
    return;         // no, can't do anything

  for (pFirst = pButton; ((pFirst != NULL) &&
                          (pFirst->fsStyle & TBSTYLE_GROUP)); )
    if (pFirst->fsStyle & TBSTYLE_GROUP)
      pFirst = pFirst->Prev;
    else
      break;
      
  for (pLast = pButton; ((pLast != NULL) &&
                          (pLast->fsStyle & TBSTYLE_GROUP)); )
    if (pLast->fsStyle & TBSTYLE_GROUP)
      pLast = pLast->Next;
    else
      break;

  for (LPTBBUTT pB = pFirst; pB <= pLast; pB = pB->Next) {
    if (pB != pButton) {
      // is this button down?
      if (pB->fsState & TBSTATE_CHECKED) {
        pB->fsState &= ~TBSTATE_CHECKED;     // pop it up
        pB->InvalidateButton (hWnd);
        break;          // only one button is down right?
        }
      }
    }

  }

/* Adds a new bitmap to the list of BMs available for this toolbar.
 * Returns the index of the first button in the bitmap or -1 if there
 * was an error.
 */
int ToolBar::AddBitmap (int nButtons, HINSTANCE hBMInst, WORD wBMID)
  {
  LPTBBMINFO pTemp;
  int nIndex = 0;
  BOOL JustAllocated = FALSE;

  if (FirstBitmap != NULL) {
    for (pTemp = FirstBitmap; pTemp != NULL; pTemp = pTemp->Next) {
      if ((pTemp->hInst == hBMInst) && (pTemp->wID == wBMID)) {
        // We already have this bitmap, but have we "registered" all
        // the buttons in it?
        if (pTemp->nButtons >= nButtons)
          return (nIndex);

        pTemp->nButtons = nButtons;
        return (nIndex);
        }
      nIndex += pTemp->nButtons;  
      }
      
      // Bitmap in die Liste rein!
    pTemp = new TBBmInfo (hBMInst, wBMID, nButtons, NULL);
      

    }
  else {
    // erstes Bitmap anlegen!!!
    pTemp = new TBBmInfo (hBMInst, wBMID, nButtons, NULL);
    if (pTemp == NULL)
      return (-1);
    JustAllocated = TRUE;
    }  

  pTemp->Next = FirstBitmap;
  FirstBitmap = pTemp;

  if (!JustAllocated)
    for (pTemp = FirstBitmap; pTemp != NULL; pTemp = pTemp->Next)
      nButtons += pTemp->nButtons;
      
  return (nButtons);    
    
    
  }


BOOL ToolBar::InsertButtons (UINT uWhere, UINT uButtons, LPTBBUTTON lpButtons)
  {
  LPTBBUTT pIn, /*pOut,*/ pTemp;
  int i;

  if (uWhere > (UINT)ButtonCount())
    for (pTemp = FirstButton; (pTemp != NULL) && (pTemp->Next != NULL); pTemp = pTemp->Next);
  else
    for (pTemp = FirstButton, i = 0; 
           ((pTemp != NULL) && (UINT(i) < uWhere)); 
             pTemp = pTemp->Next, i++);
    

  for (i = 0; UINT(i) < uButtons; i++) {
    pIn = new TBButton (lpButtons + i, this);
    
    if (FirstButton == NULL)
      FirstButton = pTemp = pIn;
    else { 
      if (pTemp != NULL) {
        pIn->Next = pTemp->Next;
        if (pIn->Next != NULL)
          pIn->Next->Prev = pIn;
        pTemp->Next = pIn;
        pIn->Prev = pTemp;
        pTemp = pIn;
        }
      }
    }
    
  /* We need to completely redraw the toolbar at this point.
   */
  InvalidateRect(hWnd, NULL, TRUE);

  return(TRUE);
  }


BOOL ToolBar::DeleteButton (UINT uIndex)
  {
//  LPTBBUTTON pIn, pOut;

  int i = 0;
  for (LPTBBUTT pb = FirstButton; ((pb != NULL) && (UINT(i) < uIndex)); pb = pb->Next, i++);
  if (pb != NULL) {
    if (pb->Prev != NULL)
      pb->Prev->Next = pb->Next;
    if (pb->Next != NULL)
      pb->Next->Prev = pb->Prev;
    delete pb;  
    }
    
  // We need to completely redraw the toolbar at this point.
  InvalidateRect(hWnd, NULL, TRUE);

  return(TRUE);
  }

//----------------------  SizeOnParent  -------------------------------------
// wird verwendet, um dem Toolbar-Fenster mitzuteilen, dass sich das 
// Elternfenster veraendert hat (nur bei Popup).
// Sind die Ausdehnungsparameter (cx, cy) 0, wird der Toolbar eine
// fingierte WM_SIZE geschickt, um vernuenftige Abmessungen zu erhalten.
//---------------------------------------------------------------------------
void ToolBar::SizeOnParent (HWND hParent, int x, int y, int cx, int cy)
  {
  if ((cx > 0) && (cy > 0))
    MoveWindow (hWnd, x, y, cx, cy, TRUE);
  else
    SendMessage (hWnd, WM_SIZE, 0, 0L);  
  }


static BOOL ShowAsPopup;  // Zeichnen eines Popup- oder eines Child-Rahmens!
RECT rcTmpChild;
//----------------------------  OnLButtonDown  ------------------------------
BOOL ToolBar::OnLButtonDown (POINT pt)
  {
  BOOL Found = FALSE;

  SetCapture(hWnd);
  LPTBBUTT ptbButton = TBHitTest(pt.x, pt.y);
  if (ptbButton != NULL) {
    pCaptureButton = ptbButton;

    if (ptbButton->fsState & TBSTATE_ENABLED) {
      ptbButton->fsState |= TBSTATE_PRESSED;
      ptbButton->InvalidateButton(hWnd);
      UpdateWindow(hWnd);         // imedeate feedback
      }

    SendMessage(hWndCommand, WM_COMMAND, GETWINDOWID(hWnd), MAKELONG(pCaptureButton->idCommand, TBN_BEGINDRAG));
    Found = TRUE;
    }
  else {
    bMoveToolbar = TRUE;
    ShowAsPopup = ParentIsPopUp;
    if (ShowAsPopup) {
      POINT ptTmp;
      ptTmp.x = pt.x;
      ptTmp.y = pt.y;
      ClientToScreen (hWnd, &ptTmp);
      // Das Kindfenster muss sich dem Popupfenster sofort anpassen!!!!!
      int ChildHeight = rcChild.bottom - rcChild.top;
      int ChildWidth = rcChild.right - rcChild.left;
      if (ptTmp.y > (rcPopup.top + ChildHeight)) {
        rcTmpChild.bottom = ptTmp.y;
        rcTmpChild.top = rcTmpChild.bottom - ChildHeight;
        }
      else {
        rcTmpChild.top = rcPopup.top;
        rcTmpChild.bottom = rcTmpChild.top + ChildHeight;
        }  
        
      rcTmpChild.left = rcPopup.left;
      rcTmpChild.right = rcTmpChild.left + ChildWidth;
    
      CopyRect (LPRECT(&rcMove), LPRECT(&rcPopup));
      }
    else {
      GetWindowRect (hWnd, LPRECT(&rcMove));
      CopyRect (&rcTmpChild, LPRECT(&rcMove));
      }

    DrawInvertFrame (LPRECT(&rcMove), ShowAsPopup, this);
    ptSave.x = pt.x;
    ptSave.y = pt.y;
    }
  
  return Found;
  }



//----------------------------  OnLButtonUp  --------------------------------
BOOL ToolBar::OnLButtonUp (POINT pt)
  {
  BOOL ret = FALSE;

  ReleaseCapture();
  if (pCaptureButton != NULL) {
    int idCommand;

    idCommand = pCaptureButton->idCommand;

    SendMessage(hWndCommand, WM_COMMAND, GETWINDOWID(hWnd), MAKELONG(idCommand, TBN_ENDDRAG));

    LPTBBUTT ptbButton = TBHitTest(pt.x, pt.y);
    if ((pCaptureButton->fsState & TBSTATE_ENABLED) && (ptbButton != NULL)
              && (pCaptureButton == ptbButton)) {
       pCaptureButton->fsState &= ~TBSTATE_PRESSED;

       if (pCaptureButton->fsStyle & TBSTYLE_CHECK) {
         if (pCaptureButton->fsStyle & TBSTYLE_GROUP) {

        // group buttons already checked can't be force
        // up by the user.

           if (pCaptureButton->fsState & TBSTATE_CHECKED) {
             pCaptureButton = NULL;
             return TRUE;  // bail!
             }

           pCaptureButton->fsState |= TBSTATE_CHECKED;
           MakeGroupConsistant(hWnd, idCommand);
           } 
         else {
           pCaptureButton->fsState ^= TBSTATE_CHECKED; // toggle
           }
         }

       pCaptureButton->InvalidateButton(hWnd);
       pCaptureButton = NULL;
       SendMessage(hWndCommand, WM_COMMAND, idCommand, 0L);
       }
     else {
       pCaptureButton = NULL;
       }
       
     ret = TRUE;  
     }
  else {
    if (bMoveToolbar) {
      DrawInvertFrame (LPRECT(&rcMove), ShowAsPopup, this);

      if (ParentIsPopUp) {
        if (ShowAsPopup)
          CopyRect (LPRECT(&rcPopup), LPRECT(&rcMove));

        // bei einem Popup-Toolbar wird das Eltern-Fenster verschoben
        SetWindowPos (GetParent(hWnd), 0, rcPopup.left, rcPopup.top, 0, 0,
                      SWP_NOSIZE | SWP_NOZORDER);
        }
      else {
        if (ShowAsPopup)
          CopyRect (LPRECT(&rcPopup) ,LPRECT(&rcMove));
/*
        else  
          CopyRect (LPRECT(&rcChild) ,LPRECT(&rcMove));
*/
        }

      SendMessage (hParent, TBD_POSCHANGED, ShowAsPopup != ParentIsPopUp, LONG(LPTOOLBAR(this)));

      bMoveToolbar = FALSE;
      SetRectEmpty (LPRECT(&rcMove));
      SetRectEmpty (&rcTmpChild);
      }
    }
    
  return ret;     
  }
  
//----------------------------  OnMouseMove  --------------------------------
BOOL ToolBar::OnMouseMove (POINT pt)
  {
  BOOL ret = FALSE;
  
  if ((pCaptureButton != NULL) && (pCaptureButton->fsState & TBSTATE_ENABLED)) {
    LPTBBUTT ptbButton = TBHitTest(pt.x, pt.y);
    BOOL fSameButton = ((ptbButton != NULL) && (pCaptureButton == ptbButton));
    if (fSameButton == !(pCaptureButton->fsState & TBSTATE_PRESSED)) {
      pCaptureButton->fsState ^= TBSTATE_PRESSED;
      pCaptureButton->InvalidateButton (hWnd);
      }
    ret = TRUE;  
    }
  else {
    if (bMoveToolbar) {
      // altes Rechteck loeschen
      DrawInvertFrame (LPRECT(&rcMove), ShowAsPopup, this);
  
      // Verschiebungsoffset berechnen
      int DeltaX = ptSave.x - pt.x;
      int DeltaY = ptSave.y - pt.y;
      
      ptSave.x = pt.x;
      ptSave.y = pt.y;

      OffsetRect (LPRECT(&rcTmpChild), -DeltaX, -DeltaY);

      RECT rcParent;
      GetWindowRect (hParent, &rcParent);  // Position des echten Docking-Fensters

      if (ShowAsPopup) {
        if ((rcTmpChild.top < rcParent.bottom) &&
            (rcTmpChild.bottom > rcParent.top)) {
          CopyRect (LPRECT(&rcMove), LPRECT(&rcTmpChild));
//*************************************************
          ShowAsPopup = FALSE;
//*************************************************
          }
        }
      else {
        // Bewegen unter das Docking-Fenster
        if ((rcTmpChild.top > rcParent.bottom) ||
            (rcTmpChild.bottom < rcParent.top)) {
          POINT ptTmp;
          ptTmp.x = pt.x;
          ptTmp.y = pt.y;
          
          int PopupWidth = rcPopup.right - rcPopup.left;
          int PopupHeight = rcPopup.bottom - rcPopup.top;

          if (ptTmp.x > PopupWidth) {    // Mausposition im Child groesser als das Popup
            ClientToScreen (hWnd, &ptTmp);
            rcMove.left = ptTmp.x - PopupWidth / 2;   // Rahmen des Popup-Fenster setzen
            }
          else
            rcMove.left = rcTmpChild.left;
              
          rcMove.right = rcMove.left + PopupWidth;
          if (rcTmpChild.top > rcParent.bottom) {
            rcMove.top = rcTmpChild.top;
            rcMove.bottom = rcMove.top + PopupHeight;
            }
          else {
            rcMove.bottom = rcTmpChild.bottom;
            rcMove.top = rcMove.bottom - PopupHeight;
            }
//*************************************************
          ShowAsPopup = TRUE;
//*************************************************
          }
        // Bewegen ueber das Docking-Fenster
        }  
      
      // neues Rechteck zeichnen
      OffsetRect (LPRECT(&rcMove), -DeltaX, -DeltaY);
      DrawInvertFrame (LPRECT(&rcMove), ShowAsPopup, this);
      }  
    }  
    
  return ret;  
  }

static BOOL bChangeState = FALSE;
//----------------------------  ChangeState  --------------------------------
void ToolBar::ChangeState (BOOL bFromDblClk)
  {
  bChangeState = TRUE;
  if (!ParentIsPopUp) {
    ParentIsPopUp = TRUE;
/*          
    WORD w = 150;
    WORD h;
    FigureXSnap (&w, &h, lptb);
    w += 2*GetSystemMetrics(SM_CXFRAME);
    h += 2*GetSystemMetrics(SM_CYFRAME);
*/
    WORD w = rcPopup.right - rcPopup.left;
    WORD h = rcPopup.bottom - rcPopup.top;
    FigureXSnap (&w, &h, this);
    w += 2*GetSystemMetrics(SM_CXFRAME);
    h += 2*GetSystemMetrics(SM_CYFRAME);
          
    hWndDock = CreateWindow (szPopupDockWindow, "DockWindow", 
                             WS_BORDER | WS_VISIBLE | WS_CLIPCHILDREN | WS_THICKFRAME | WS_POPUP,
                             rcPopup.left, rcPopup.top, w, h, 
                             hParent, NULL, hLibInst, NULL);
    SetWindowLong (hWndDock, 0, LONG(this));
    SetParent (hWnd, hWndDock);
  
    SizeOnParent (hWndDock, 0, 0, w-1, h-1);
    }
  else {
    ParentIsPopUp = FALSE;
    SetParent (hWnd, hParent);
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    SizeOnParent (hParent, 0, 0, 0, 0);
/***************************
    RECT rc;
    CopyRect (&rc, LPRECT(&rcChild));
    ScreenToClient (hWnd, LPPOINT(&rc));
    ScreenToClient (hWnd, LPPOINT(&rc.right));
    if (bFromDblClk)
      SizeOnParent (hParent, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
*****************************/
    if (bFromDblClk)
      SizeOnParent (hParent, rcChild.left, rcChild.top, rcChild.right-rcChild.left, rcChild.bottom-rcChild.top);

    DestroyWindow (hWndDock);
    hWndDock = 0;
    }
  }
  
//----------------------------  OnSetState  ---------------------------------
BOOL ToolBar::OnSetState (WPARAM wParam, LPARAM lParam)
  {
/*
  int iPos = PositionFromID((int)wParam);
  if (iPos < 0)
    return(FALSE);
*/
  LPTBBUTT ptbButton = ButtonFromID (int(wParam));
  if (ptbButton == NULL)
    return (FALSE);

  BYTE fsState = (BYTE)(LOWORD(lParam) ^ ptbButton->fsState);
  ptbButton->fsState = (BYTE)LOWORD(lParam);

  if (fsState & TBSTATE_HIDDEN)
    InvalidateRect(hWnd, NULL, TRUE);
  else if (fsState)
    ptbButton->InvalidateButton(hWnd);

  return(TRUE);
  }
  
//----------------------------  OnGetState  ---------------------------------
LONG ToolBar::OnGetState (WPARAM wParam)
  {
/*
  int iPos = PositionFromID((int)wParam);
  if (iPos < 0)
    return(-1L);
    
  return(pTBHdr->Buttons[iPos].fsState);
*/
  LPTBBUTT ptbButton = ButtonFromID (int(wParam));
  if (ptbButton == NULL)
    return (-1L);
    
  return ptbButton->fsState;  
  }
  
//----------------------------  OnTBSetState  -------------------------------
BOOL ToolBar::OnTBSetState (UINT wMsg, WPARAM wParam, LPARAM lParam)
  {
/*
  int iPos = PositionFromID((int)wParam);
  if (iPos < 0)
    return(FALSE);

  LPTBBUTTON ptbButton = &pTBHdr->Buttons[iPos];
*/
  LPTBBUTT ptbButton = ButtonFromID(int(wParam));
  if (ptbButton == NULL)
    return (FALSE);
    
  BYTE fsState = ptbButton->fsState;

  if (LOWORD(lParam))
    ptbButton->fsState |= wStateMasks[wMsg - TB_ENABLEBUTTON];
  else
    ptbButton->fsState &= ~wStateMasks[wMsg - TB_ENABLEBUTTON];

  // did this actually change the state?
  if (fsState != ptbButton->fsState) {
    // is this button a member of a group?
    if ((wMsg == TB_CHECKBUTTON) && (ptbButton->fsStyle & TBSTYLE_GROUP))
         MakeGroupConsistant(hWnd, (int)wParam);

    if (wMsg == TB_HIDEBUTTON)
      InvalidateRect(hWnd, NULL, TRUE);
    else
      ptbButton->InvalidateButton(hWnd);
    }
  return(TRUE);
  }
  
//----------------------------  OnTBGetState  -------------------------------
LONG ToolBar::OnTBGetState (UINT wMsg, WPARAM wParam)
  {
/*
  int iPos = PositionFromID((int)wParam);
  if (iPos < 0)
    return(-1L);
*/
  LPTBBUTT ptbButton = ButtonFromID(int(wParam));
  if (ptbButton == NULL)
    return (-1L);

  return (LRESULT)ptbButton->fsState & wStateMasks[wMsg - TB_ISBUTTONENABLED];
  }
  
//----------------------------  GetButton  ----------------------------------
BOOL ToolBar::GetButton (WPARAM wParam, LPARAM lParam)
  {
//  if (wParam >= (UINT)pTBHdr->iNumButtons)
//    return(FALSE);
  int i = 0;
  for (LPTBBUTT pb = FirstButton; ((UINT(i) < wParam) && (pb != NULL)); pb = pb->Next, i++);
  if (pb == NULL)
    return FALSE;

  TBBUTTON btnstruct;
  btnstruct.iBitmap   = pb->iBitmap;
  btnstruct.idCommand = pb->idCommand;
  btnstruct.fsState   = pb->fsState;
  btnstruct.fsStyle   = pb->fsStyle;
  
  *((LPTBBUTTON)lParam) = btnstruct;

  return(TRUE);
  }
  
//----------------------------  ButtonCount  --------------------------------
int ToolBar::ButtonCount ()
  {
  int i = 0;
  for (LPTBBUTT pb = FirstButton; (pb != NULL); pb = pb->Next, i++);
  return i;
  }
  
//----------------------------  CommandToIndex  -----------------------------
int ToolBar::CommandToIndex (WPARAM wParam)
  {
  return(PositionFromID((int)wParam));
  }
  
BOOL ToolBar::OnGetItemRect (WPARAM wParam, LPARAM lParam)
  {
  RECT rc;

  LPTBBUTT ptbButton = ButtonFromID(int(wParam));
  if (ptbButton == NULL)
    return (FALSE);
/*
  int iPos = PositionFromID ((int)wParam);
  if (iPos < 0)
    return(FALSE);
*/  
  BOOL res = ptbButton->GetItemRect(hWnd, &rc); 
//      *((LPRECT)lParam) = res ? rc : NULL;
  if (!res)
    SetRectEmpty (&rc);
//      *((LPRECT)lParam) = rc;
  CopyRect (((LPRECT)lParam), LPRECT(&rc));
  return res;
  }
  


static BOOL bAllowDblClk = TRUE;
static BOOL bInitializePopupSize = TRUE;
DLLExport LONG _export FAR PASCAL ToolbarWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
  {
  LPTOOLBAR lptb = LPTOOLBAR (GetWindowLong (hWnd, 0));
  
  switch (wMsg) {
    case WM_CREATE:
      {
      LPCREATESTRUCT lpcs  = (LPCREATESTRUCT)lParam;

      lptb = new ToolBar (hWnd, lpcs->hwndParent, LPSTR(lpcs->lpszName));
      if ((lptb != NULL) && (lptb->Result != 0))
        return -1;
  
      SetWindowLong (hWnd, 0, LONG(lptb));
      }
      break;
    //-----------------------------------------------------------------------
    case WM_DESTROY:
//      if (IsWindow(lptb->hWndDock))
//        DestroyWindow (lptb->hWndDock);

      // aus der Toolbar-Liste des Parents ausklinken
      if (IsWindow(lptb->hParent))
        SendMessage (lptb->hParent, TBD_REMOVETOOLBAR, 0, LPARAM(lptb));
      delete lptb;
      SetWindowLong (hWnd, 0, 0);
      break;

    //-----------------------------------------------------------------------
    case WM_PAINT:
      lptb->ToolbarPaint ();
      break;

    //-----------------------------------------------------------------------
    case WM_SIZE:
      {
      RECT rcParent;
      HWND hwndParent;
      hwndParent = GetParent(hWnd);
      static BOOL bSizeChanged = FALSE;

      WORD w = LOWORD(lParam);
      WORD h = HIWORD(lParam);

      bInitializePopupSize = ((lptb->rcPopup.right-lptb->rcPopup.left <= 0) || 
                              (lptb->rcPopup.bottom-lptb->rcPopup.top <= 0));

      if (!lptb->ParentIsPopUp) {
        lptb->rcChild.right = lptb->rcChild.left + w;
        lptb->rcChild.bottom = lptb->rcChild.top + h;
        }
      else {
/*      
        if (bChangeState || bInitializePopupSize) {
          w += 2*GetSystemMetrics(SM_CXFRAME);
          h += 2*GetSystemMetrics(SM_CYFRAME);
          }
*/
        lptb->rcPopup.right = lptb->rcPopup.left + w;
        lptb->rcPopup.bottom = lptb->rcPopup.top + h;
        }  

      if ((lptb->ButtonCount() > 0) && (!bSizeChanged)) {
        // zuerst einmal die Abmessungen fuer die beiden Rechtecke ermitteln
        if (bInitializePopupSize) {
//          ClientToScreen (hWnd, LPPOINT(LPRECT(&lptb->rcChild.right)));
          w = 150;
          FigureXSnap (&w, &h, lptb);
          w += 2*GetSystemMetrics(SM_CXFRAME);
          h += 2*GetSystemMetrics(SM_CYFRAME);
          lptb->rcPopup.right = lptb->rcPopup.left + w;
          lptb->rcPopup.bottom = lptb->rcPopup.top + h;
          bInitializePopupSize = FALSE;

          w = GetSystemMetrics(SM_CXSCREEN);  // maximale Groesse versuchen
          FigureXSnap (&w, &h, lptb);  // optimale Abmessungen ermitteln

//          GetClientRect (hWnd, LPRECT(&lptb->rcChild));
//          ClientToScreen (hWnd, LPPOINT(LPRECT(&lptb->rcChild)));
/**************************************
          GetWindowRect (hWnd, LPRECT(&lptb->rcChild));
****************************************/
          GetClientRect (hWnd, LPRECT(&lptb->rcChild));
          lptb->rcChild.right = lptb->rcChild.left + w;
          lptb->rcChild.bottom = lptb->rcChild.top + h;
          }  
           
        if ((IsWindow(hwndParent)) && (!bSizeChanged)) {
          if (!lptb->ParentIsPopUp) {
//            w = GetSystemMetrics(SM_CXSCREEN);  // maximale Groesse versuchen
            FigureXSnap (&w, &h, lptb);  // optimale Abmessungen ermitteln

            bSizeChanged = TRUE;
//            MoveWindow (hWnd, NULL, 0, 0, int(w), int(h), TRUE);
            RECT rc;
            CopyRect (&rc, LPRECT(&lptb->rcChild));
//            ScreenToClient (hWnd, LPPOINT(&rc));

            SetWindowPos (hWnd, NULL, rc.left, rc.top,
                          int(w), int(h),
                          SWP_NOZORDER | SWP_NOMOVE);
/*
            SetWindowPos (hWnd, NULL, 0, 0,
                          int(w), int(h),
                          SWP_NOZORDER | SWP_NOMOVE);
*/                          
            bSizeChanged = FALSE;              
            }

          if (!IsWindowVisible(hWnd))
            return 0L;
  
          // schickt dem Elternfenster eine WM_SIZE-Nachricht,
          // obwohl keine Groessenanderung passiert!!
          if (bChangeState) {
            bChangeState = FALSE;
            GetClientRect(GetParent(hwndParent), &rcParent);
            SendMessage (GetParent(hwndParent), WM_SIZE, wParam, 
                         MAKELONG(rcParent.right-rcParent.left,
                                  rcParent.bottom-rcParent.top)
                         );
            }
          }
        }  // if (iNumButtons > 0) ...

      break;
      }

    //-----------------------------------------------------------------------
    case WM_LBUTTONDBLCLK:
      {
      if (bAllowDblClk) {
        if (lptb->ParentIsPopUp) {
          // bei einem Popup-Fenster wird vorgeschwindelt, dass man die
          // Toolbar mit der Maus in das Dockingfenster bewegt hat.
          CopyRect (LPRECT(&lptb->rcMove), LPRECT(&lptb->rcChild));
          ClientToScreen (lptb->hParent, LPPOINT(&lptb->rcMove));
          ClientToScreen (lptb->hParent, LPPOINT(&lptb->rcMove.right));
          }
        SendMessage (lptb->hParent, TBD_POSCHANGED, TRUE, LONG(LPTOOLBAR(lptb)));
//        lptb->ChangeState (TRUE);
        }
      }  
      break;
      
    //-----------------------------------------------------------------------
    case WM_COMMAND:
    case WM_DRAWITEM:
    case WM_MEASUREITEM:
    case WM_VKEYTOITEM:
    case WM_CHARTOITEM:
      SendMessage(lptb->hWndCommand, wMsg, wParam, lParam);
      break;

    //-----------------------------------------------------------------------
    case WM_LBUTTONDOWN:
      {
      bAllowDblClk = TRUE;    

      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif
      if (!lptb->OnLButtonDown (pt)) {
/*
        if (!lptb->ParentIsPopUp) {
        
//          SendMessage (hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
//          SendMessage (GetParent(hWnd), WM_NCLBUTTONDOWN, HTCAPTION, lParam);
          }
*/
        }
      else
        bAllowDblClk = FALSE;    
      }
      break;

    //-----------------------------------------------------------------------
    case WM_MOUSEMOVE:
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif

      lptb->OnMouseMove (pt);
      }
      break;

    //-----------------------------------------------------------------------
    case WM_LBUTTONUP:
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif

      lptb->OnLButtonUp (pt);
      }
      break;

    //-----------------------------------------------------------------------
    case TB_SETSTATE:
      return lptb->OnSetState (wParam, lParam);

    //-----------------------------------------------------------------------
    case TB_GETSTATE:
      return lptb->OnGetState (wParam);

    //-----------------------------------------------------------------------
    case TB_ENABLEBUTTON:
    case TB_CHECKBUTTON:
    case TB_PRESSBUTTON:
    case TB_HIDEBUTTON:
    case TB_INDETERMINATE:
      return lptb->OnTBSetState (wMsg, wParam, lParam);

    case TB_ISBUTTONENABLED:
    case TB_ISBUTTONCHECKED:
    case TB_ISBUTTONPRESSED:
    case TB_ISBUTTONHIDDEN:
    case TB_ISBUTTONINDETERMINATE:
      return lptb->OnTBGetState (wMsg, wParam);

    case TB_ADDBITMAP:
#ifdef WIN32
      return lptb->AddBitmap (LOWORD(lParam), (HINSTANCE)wParam, HIWORD(lParam));
#else
      return lptb->AddBitmap (wParam, (HINSTANCE)LOWORD(lParam), HIWORD(lParam));
#endif

    case TB_ADDBUTTONS:
      return lptb->InsertButtons (UINT(-1), wParam, (LPTBBUTTON)lParam);

    case TB_INSERTBUTTON:
      return lptb->InsertButtons (wParam, 1, (LPTBBUTTON)lParam);

    case TB_DELETEBUTTON:
      return lptb->DeleteButton (wParam);

    case TB_GETBUTTON:
      return lptb->GetButton (wParam, lParam);

    case TB_BUTTONCOUNT:
      return lptb->ButtonCount ();

    case TB_COMMANDTOINDEX:
      return lptb->CommandToIndex (wParam);

    case TB_GETITEMRECT:
      return lptb->OnGetItemRect (wParam, lParam);

    case TB_GETTOOLBARSTATE:
      return lptb->ParentIsPopUp;

    case TB_GETCLASSPTR:
      return LONG(lptb);
      break;

    case TB_REMOVETOOLBAR:
      if (lptb)
        if (IsWindow(lptb->hParent))
          SendMessage (lptb->hParent, TBD_REMOVETOOLBAR, 0, LPARAM(lptb));
      break;
/*
    case TB_SHOWTOOLBAR:
      {
      RECT rc;
      
      UINT bShowFlag = (wParam == SW_SHOW) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
      bChangeState = TRUE;
      GetWindowRect (lptb->hWnd, &rc);
      SetWindowPos (lptb->hWnd, 0, 0, 0, 
                    rc.right-rc.left, 
                    rc.bottom-rc.top, 
                    SWP_NOZORDER | SWP_NOMOVE | bShowFlag);
      }
      break;
*/        
    default:
      return DefWindowProc(hWnd, wMsg, wParam, lParam);
    }

  return 0L;
  }

void ToolBar::GetSysColors()
  {
  static COLORREF rgbSaveFace    = 0xffffffffL,
                  rgbSaveShadow  = 0xffffffffL,
                  rgbSaveHilight = 0xffffffffL,
                  rgbSaveFrame   = 0xffffffffL;

  rgbFace    = GetSysColor(COLOR_BTNFACE);
  rgbShadow  = GetSysColor(COLOR_BTNSHADOW);
  rgbHilight = GetSysColor(COLOR_BTNHIGHLIGHT);
  rgbFrame   = GetSysColor(COLOR_WINDOWFRAME);

  if (rgbSaveFace!=rgbFace || rgbSaveShadow!=rgbShadow
     || rgbSaveHilight!=rgbHilight || rgbSaveFrame!=rgbFrame) {
//    int i;
//    LPTBBMINF pBitmap;

    rgbSaveFace    = rgbFace;
    rgbSaveShadow  = rgbShadow;
    rgbSaveHilight = rgbHilight;
    rgbSaveFrame   = rgbFrame;

    // Update the brush for pushed-in buttons
    CreateDitherBrush(TRUE);

    /* Reset all of the bitmaps if the sys colors have changed
     * since the last time the bitmaps were created.
     */
/*     
    for (i = pTBHdr->nBitmaps-1, pBitmap = pTBHdr->pBitmaps; i >= 0; i--, ++pBitmap) {
      if (pBitmap->hInst && pBitmap->hbm) {
        DeleteObject(pBitmap->hbm);
        pBitmap->hbm = NULL;
        }
      }
*/
    for (LPTBBMINFO pbm = FirstBitmap; pbm != NULL; pbm = pbm->Next) {
      if (pbm->hInst && pbm->hbm) {
        DeleteObject(pbm->hbm);
        pbm->hbm = NULL;
        }
      }

    }
  }

/*
int   FAR PASCAL LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine);
int   FAR PASCAL WEP (int bSystemExit);
*/


HBITMAP CreateDitherBitmap()
  {
  LPBITMAPINFO lpbmi;
  HBITMAP hbm;
  HDC hdc;
  int i;
  long patGray[8];
  DWORD rgb;

  HGLOBAL hglbbmi = GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 16));
  lpbmi = (LPBITMAPINFO)GlobalLock(hglbbmi);
  if (!lpbmi)
    return NULL;

  lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  lpbmi->bmiHeader.biWidth = 8;
  lpbmi->bmiHeader.biHeight = 8;
  lpbmi->bmiHeader.biPlanes = 1;
  lpbmi->bmiHeader.biBitCount = 1;
  lpbmi->bmiHeader.biCompression = BI_RGB;

  rgb = GetSysColor(COLOR_BTNFACE);
  lpbmi->bmiColors[0].rgbBlue  = GetBValue(rgb);
  lpbmi->bmiColors[0].rgbGreen = GetGValue(rgb);
  lpbmi->bmiColors[0].rgbRed   = GetRValue(rgb);
  lpbmi->bmiColors[0].rgbReserved = 0;

  rgb = GetSysColor(COLOR_BTNHIGHLIGHT);
  lpbmi->bmiColors[1].rgbBlue  = GetBValue(rgb);
  lpbmi->bmiColors[1].rgbGreen = GetGValue(rgb);
  lpbmi->bmiColors[1].rgbRed   = GetRValue(rgb);
  lpbmi->bmiColors[1].rgbReserved = 0;


  /* initialize the brushes */

  for (i = 0; i < 8; i++)
    if (i & 1)
      patGray[i] = 0xAAAA5555L;   //  0x11114444L; // lighter gray
    else
      patGray[i] = 0x5555AAAAL;   //  0x11114444L; // lighter gray

  hdc = GetDC(NULL);

  hbm = CreateDIBitmap(hdc, &lpbmi->bmiHeader, CBM_INIT, patGray, lpbmi, DIB_RGB_COLORS);

  ReleaseDC(NULL, hdc);

  GlobalUnlock (hglbbmi);
  GlobalFree(hglbbmi);

  return hbm;
  }

BOOL ToolBar::CreateDitherBrush (BOOL bIgnoreCount)
  {
  HBITMAP hbmGray;
  HBRUSH hbrSave;
/*
  if (bIgnoreCount && !iDitherCount)
    return TRUE;

  if ((iDitherCount > 0) && !bIgnoreCount) {
    iDitherCount++;
    return TRUE;
    }
*/
  hbmGray = CreateDitherBitmap();
  if (hbmGray) {
    hbrSave = hbrDither;
    hbrDither = CreatePatternBrush(hbmGray);
    DeleteObject(hbmGray);
    if (hbrDither) {
      if (hbrSave)
        DeleteObject(hbrSave);
/*
      if (!bIgnoreCount)
        iDitherCount = 1;
*/
      return TRUE;
      }
    else
      hbrDither = hbrSave;
    }

  return FALSE;
  }

BOOL ToolBar::FreeDitherBrush(void)
  {
/*
  iDitherCount--;

  if (iDitherCount > 0)
    return FALSE;
*/
  if (hbrDither)
  DeleteObject(hbrDither);
  hbrDither = NULL;

  return TRUE;
  }

typedef struct tagCOLORMAP
  {
  COLORREF bgrfrom;
  COLORREF bgrto;
  COLORREF sysColor;
  } COLORMAP;

// these are the default colors used to map the dib colors
// to the current system colors

#define BGR_BUTTONTEXT      (RGB(000,000,000))  // black
#define BGR_BUTTONSHADOW    (RGB(128,128,128))  // dark grey
#define BGR_BUTTONFACE      (RGB(192,192,192))  // bright grey
#define BGR_BUTTONHILIGHT   (RGB(255,255,255))  // white
#define BGR_BACKGROUNDSEL   (RGB(255,000,000))  // blue
#define BGR_BACKGROUND      (RGB(255,000,255))  // magenta
#define FlipColor(rgb)      (RGB(GetBValue(rgb), GetGValue(rgb), GetRValue(rgb)))

HBITMAP CreateMappedBitmap(HINSTANCE hInstance, int idBitmap )
  {
  HDC       hdc, hdcMem = NULL;
  HRSRC     h;
  DWORD FAR *p;
  LPSTR     lpBits;
  HANDLE    hRes;
  LPBITMAPINFOHEADER  lpBitmapInfo;
  HBITMAP   hbm = NULL, hbmOld;
  int       numcolors, i;
  int       wid, hgt;
  static COLORMAP ColorMap[] = {
    {BGR_BUTTONTEXT,    BGR_BUTTONTEXT,    COLOR_BTNTEXT},     // black
    {BGR_BUTTONSHADOW,  BGR_BUTTONSHADOW,  COLOR_BTNSHADOW},   // dark grey
    {BGR_BUTTONFACE,    BGR_BUTTONFACE,    COLOR_BTNFACE},     // bright grey
    {BGR_BUTTONHILIGHT, BGR_BUTTONHILIGHT, COLOR_BTNHIGHLIGHT},// white
    {BGR_BACKGROUNDSEL, BGR_BACKGROUNDSEL, COLOR_HIGHLIGHT},   // blue
    {BGR_BACKGROUND,    BGR_BACKGROUND,    COLOR_WINDOW}       // magenta
    };

  #define NUM_MAPS (sizeof(ColorMap)/sizeof(COLORMAP))

  h = FindResource(hInstance, MAKEINTRESOURCE(idBitmap), RT_BITMAP);
  if (!h)
    return NULL;

  hRes = LoadResource(hInstance, h);

  /* Lock the bitmap and get a pointer to the color table. */
  lpBitmapInfo = (LPBITMAPINFOHEADER)LockResource(hRes);
  if (!lpBitmapInfo)
    return NULL;

  //
  // So what are the new colors anyway ?
  //
  for (i=0; i < NUM_MAPS; i++) {
    ColorMap[i].bgrto = FlipColor(GetSysColor((int)ColorMap[i].sysColor));
    }

  p = (DWORD FAR *)(((LPSTR)lpBitmapInfo) + lpBitmapInfo->biSize);

  /* Replace button-face and button-shadow colors with the current values
   */
  numcolors = 16;

  while (numcolors-- > 0) {
    for (i = 0; i < NUM_MAPS; i++) {
      if (*p == ColorMap[i].bgrfrom) {
        *p = ColorMap[i].bgrto;
        break;
        }
      }
    p++;
    }

  /* First skip over the header structure */
  lpBits = (LPSTR)(lpBitmapInfo + 1);

  /* Skip the color table entries, if any */
  lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

  /* Create a color bitmap compatible with the display device */
  i = wid = (int)lpBitmapInfo->biWidth;
  hgt = (int)lpBitmapInfo->biHeight;
  hdc = GetDC(NULL);

  hdcMem = CreateCompatibleDC(hdc);
  if (hdcMem) {
    hbm = CreateDiscardableBitmap(hdc, i, hgt);
    if (hbm) {
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);

        // set the main image
        StretchDIBits(hdcMem, 0, 0, wid, hgt, 0, 0, wid, hgt, lpBits,
                   (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
    }

    DeleteObject(hdcMem);
  }

  ReleaseDC(NULL, hdc);

  UnlockResource(hRes);
  FreeResource(hRes);

  return hbm;
}



DLLExport HWND _export FAR PASCAL CreateToolbar(LPSTR Title, HWND hwnd, DWORD ws, WORD wID, int nBitmaps,
                        HINSTANCE hBMInst, WORD wBMID,
                        LPCTBBUTTON lpButtons, int iNumButtons)
  {
  HWND hwndToolbar;

  hwndToolbar = CreateWindowEx(0L, szToolbarClass, Title, WS_CHILD | WS_CLIPSIBLINGS | ws,
                               0, 0, 0, 0, hwnd, (HMENU)wID, hLibInst, NULL);

  if (hwndToolbar) {
#ifdef WIN32
    SendMessage(hwndToolbar, TB_ADDBITMAP, (WPARAM)hBMInst, MAKELONG(nBitmaps, wBMID));
#else
    SendMessage(hwndToolbar, TB_ADDBITMAP, nBitmaps, MAKELONG(hBMInst, wBMID));
#endif

    SendMessage(hwndToolbar, TB_ADDBUTTONS, iNumButtons, (LPARAM)lpButtons);

    LPTOOLBAR lptb = (LPTOOLBAR)SendMessage (hwndToolbar, TB_GETCLASSPTR, 0, 0);
    SendMessage (hwnd, TBD_ADDTOOLBAR, 0, LPARAM(lptb));
    }

  return hwndToolbar;
  }

DLLExport void _export FAR PASCAL RemoveToolbar (HWND hWnd)
  {
  SendMessage (hWnd, TB_REMOVETOOLBAR, 0, 0);
  }

//****************************************************************************
//*                                                                          *
//*                                                                          *
//*                                                                          *
//*                                                                          *
//****************************************************************************
BOOL   gbUserDragging = FALSE;
RECT   grcWindowBorder;
POINT  gMinMaxPts[5];
HICON  hYesIcon;
HICON  hNoIcon;


/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void CheckForMinMaxTroubles (BOOL FAR *pbSatisfiesMinMaxRequirements, LPINT px, LPINT py, int iOldpy, int iOldpx, int IconX, int IconY, BOOL bFavorHoriz )
  {
  *pbSatisfiesMinMaxRequirements = TRUE;

  if (*py < gMinMaxPts[3].y) {   // too small on Y axis
    *pbSatisfiesMinMaxRequirements = FALSE;

    if (bFavorHoriz) {
      *py = iOldpy;
      *px = iOldpx - IconX;
      }
    else {
      *py = iOldpy + IconY;
      *px = iOldpx;
      }
    return;
    }

  if (*py > gMinMaxPts[4].y) {   // too large on Y axis
    *pbSatisfiesMinMaxRequirements = FALSE;

    if (bFavorHoriz) {
      *py = iOldpy;
      *px = iOldpx + IconX;
      }
    else {
      *py = iOldpy - IconY;
      *px = iOldpx;
      }
    return;
    }

  if (*px < gMinMaxPts[3].x) {   // too small on X axis
    *pbSatisfiesMinMaxRequirements = FALSE;

    if (bFavorHoriz) {
      *py = iOldpy;
      *px = iOldpx + IconX;
      }
    else {
      *py = iOldpy - IconY;
      *px = iOldpx;
      }
    return;
    }

  if (*px > gMinMaxPts[4].x) {   // too large on X axis
    *pbSatisfiesMinMaxRequirements = FALSE;

    if (bFavorHoriz) {
      *py = iOldpy;
      *px = iOldpx - IconX;
      }
    else {
      *py = iOldpy + IconY;
      *px = iOldpx;
      }
    return;
    }
  }


/*********************************************************************
*                                                                    
*  Calculates the height given the width
*  if (wWidth == 0) then use max width of all controls, still fit on
*  screen
*                                                                    
*********************************************************************/
WORD HeightGivenWidth (WORD wWidth, LPTOOLBAR lpTB)
  {
//  int   i;
  WORD  y;
  WORD  x;
  int HighestButtonInLine = 0;

  if (!wWidth) wWidth = GetSystemMetrics (SM_CXSCREEN) - GetSystemMetrics (SM_CXICON);

  x = 0;
  y = 0;


  BOOL bElemBreak = FALSE;
  for (LPTBBUTT ptbButton = lpTB->FirstButton; ptbButton != NULL; ptbButton = ptbButton->Next) {
  
    if (ptbButton->fsState & TBSTATE_HIDDEN) {
    // Do nothing
      } 
    // Separator?
    else if (ptbButton->fsStyle & TBSTYLE_SEP) {
      if (ptbButton->idCommand == 0) { // echter Separator
        if (bElemBreak) {
          ptbButton->x = x;
          ptbButton->y = y;

          y += (HighestButtonInLine + FIRSTY);
          x = 0;
          HighestButtonInLine = 0;
          
          bElemBreak = FALSE;
          }
        else {
          if (lpTB->ParentIsPopUp) {
            ptbButton->x = x;
            ptbButton->y = y;
  
            int tx = x + FIRSTBUTTON;
            LPTBBUTT ptb = ptbButton->Next;
            for ( ; ((ptb != NULL) && 
                    !((ptb->fsStyle & TBSTYLE_SEP) && (ptb->idCommand == 0))); ptb = ptb->Next) {
              if (ptb->fsStyle & TBSTYLE_SEP)
                tx += ptb->iBitmap;
              else  
                tx += DEFAULTBUTTONX;
              }
  
            if (tx > int(wWidth)) {
              x = 0;
              y += (HighestButtonInLine + FIRSTY);
              HighestButtonInLine = 0;
              }
            else  
              x += ptbButton->iBitmap;
            }
          else {
            ptbButton->x = x;
            ptbButton->y = y;
            
            x += ptbButton->iBitmap;
            }
          }  
        }
      // kein echter Separator
      else {
        if ((x + ptbButton->iBitmap) > wWidth) {
          x = 0;
          y += HighestButtonInLine;
          }
          
        ptbButton->x = x;
        ptbButton->y = y;
          
        x += ptbButton->iBitmap;
        }  
      }

    // normaler Knopf
    else {
      if ((x + DEFAULTBUTTONX) > wWidth) {
        x = 0;
        y += HighestButtonInLine;
        bElemBreak = TRUE;   // Knopfleiste wurde durchbrochen
        }

      ptbButton->x = x;
      ptbButton->y = y;

      x += DEFAULTBUTTONX - 1;
      }

    if (ptbButton->dy > HighestButtonInLine)
      HighestButtonInLine = ptbButton->dy;
    
    ptbButton->x += FIRSTBUTTON;
    ptbButton->y += FIRSTY;
    }

  y+= HighestButtonInLine;  // noch eine Buttonhoehe und etwas Rand
  return y;
  }

/*********************************************************************
*                                                                    
*  Calculates the width given the height
*  screen
*                                                                    
*********************************************************************/
WORD WidthGivenHeight (WORD wHeight, LPTOOLBAR lpTB)
  {
  int   wMaxToolWidth;
  WORD  wWidth;
  int   wTargetHeight;
  WORD  wIncrement;

  // das laengste Toolbar-Element ermitteln
  wMaxToolWidth = DEFAULTBUTTONX;
  for (LPTBBUTT ptbButton = lpTB->FirstButton; ptbButton != NULL; ptbButton = ptbButton->Next) {
    if (ptbButton->fsStyle & TBSTYLE_SEP) {
      if (ptbButton->iBitmap > wMaxToolWidth)
        wMaxToolWidth = ptbButton->iBitmap;
      } 
    }
    
  wWidth = wMaxToolWidth;
  wIncrement = LOWORD (GetDialogBaseUnits())/8;
  
  do {
    wTargetHeight = HeightGivenWidth (wWidth, lpTB);
    if (WORD(wTargetHeight) > wHeight) {// still not wide enough
      wWidth += wIncrement;  // Add a dialog unit
      }

    if (wTargetHeight <= DEFAULTBUTTONY) // min height
      wTargetHeight = 0;
    }
  while (WORD(wTargetHeight) > wHeight);

  return wWidth;
  }

/*********************************************************************
*                                                                    *
*  This function figures the size of the rect, based on px           *
*                                                                    *
*********************************************************************/
void FigureXSnap ( LPWORD px, LPWORD py, LPTOOLBAR lpTB)
  {
  WORD wWidth;
  WORD wHeight;

  // gibt die Hoehe bei der Breite px zurueck
  wHeight = HeightGivenWidth (*px, lpTB);  
  // wie breit ist die Toolbar dann bei dieser Hoehe?
  wWidth  = WidthGivenHeight (wHeight, lpTB); 
  // muss sich die Hoehe jetzt noch einmal aendern?
  wHeight = HeightGivenWidth (wWidth, lpTB);  

  *px = wWidth + 2*FIRSTBUTTON;
  *py = wHeight + 2*FIRSTY;
  }

/*********************************************************************
*                                                                    *
*  This function figures the size of the rect, based on py           *
*                                                                    *
*********************************************************************/
void FigureYSnap (LPWORD px, LPWORD py, LPTOOLBAR lpTB)
  {
  WORD wWidth;
  WORD wHeight;

  wWidth  = WidthGivenHeight (*py, lpTB); // Figure the best width for this height
  wHeight = HeightGivenWidth (wWidth, lpTB);  // Figure the toolbar's height right here

  *px = wWidth + 2*FIRSTBUTTON;
  *py = wHeight + 2*FIRSTY;
  }

/*********************************************************************
*                                                                    *
* This code is APP specific-- it needs to calculate ok sizes for the *
* toolbar                                                            *
*                                                                    *
*********************************************************************/
void FigureNewDxDyParameters (LPINT px, LPINT py, BOOL bFavorHoriz, LPTOOLBAR lpTB)
  {
  BOOL bSatisfiesMinMaxRequirements;
//  BOOL bLoopStop;

  int iOldpx, iOldpy;
//  int iNumIconsX;
//  int iNumIconsY;
//  int iBlankSpaces;

  int IconX   = GetSystemMetrics(SM_CXICON);
  int IconY   = GetSystemMetrics(SM_CYICON);

  int BorderX = GetSystemMetrics(SM_CXFRAME)*2+1;
  int BorderY = GetSystemMetrics(SM_CYFRAME)*2+1/*+GetSystemMetrics(SM_CYCAPTION)*/;

  bSatisfiesMinMaxRequirements = FALSE;

  if (bFavorHoriz) { // User is dragging horizontally, figure vertical
    // Snap X to an icon width
    while (!bSatisfiesMinMaxRequirements) {
      iOldpx = *px;
      iOldpy = *py;

      // px get the pixels wide for x
      FigureXSnap (LPWORD(px), LPWORD(py), lpTB);

      *py += BorderY;
      *px += BorderX;

      CheckForMinMaxTroubles (&bSatisfiesMinMaxRequirements, px, py, iOldpy, iOldpx, IconX, IconY, bFavorHoriz );
      }
    }
  else {
    // Snap Y to an icon width
    while (!bSatisfiesMinMaxRequirements) {    
      iOldpx = *px;
      iOldpy = *py;

      // px get the pixels wide for x
      FigureYSnap (LPWORD(px), LPWORD(py), lpTB);

      *py += BorderY;
      *px += BorderX;

      CheckForMinMaxTroubles ( &bSatisfiesMinMaxRequirements, px, py, iOldpy, iOldpx, IconX, IconY, bFavorHoriz );
      }
    }
  }

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

#define LEFTPOS   (min (grcWindowBorder.right  - gMinMaxPts[3].x, max(lppt->x,grcWindowBorder.left   - gMinMaxPts[4].x) ))
#define RIGHTPOS  (max (grcWindowBorder.left   + gMinMaxPts[3].x, min(lppt->x,grcWindowBorder.right  + gMinMaxPts[4].x) ))
#define TOPPOS    (min (grcWindowBorder.bottom - gMinMaxPts[3].y, max(lppt->y,grcWindowBorder.top    - gMinMaxPts[4].y) ))
#define BOTTOMPOS (max (grcWindowBorder.top    + gMinMaxPts[3].y, min(lppt->y,grcWindowBorder.bottom + gMinMaxPts[4].y) ))

//----------------------------------------------------------------------------
// wird aus HandleUserDraggingMouse aufgerufen
//----------------------------------------------------------------------------
void FigureNewWindowSize (LPPOINT lppt, LONG lHTCode, LPTOOLBAR lpTB)
  {
  //  This example will keep the aspect ratio such that the window is a square
  int dx, dy;

  switch (lHTCode) {
    case HTLEFT : 
      grcWindowBorder.left   = LEFTPOS;

      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters (&dx, &dy, TRUE, lpTB);

      grcWindowBorder.left   = grcWindowBorder.right - dx;
      grcWindowBorder.bottom = grcWindowBorder.top   + dy;
      break;

    case HTRIGHT : 
      grcWindowBorder.right   = RIGHTPOS;

      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters (&dx, &dy, TRUE, lpTB);

      grcWindowBorder.right  = grcWindowBorder.left  + dx;
      grcWindowBorder.bottom = grcWindowBorder.top   + dy;
      break;

    case HTTOP : 
      grcWindowBorder.top    = TOPPOS;
      dy = grcWindowBorder.bottom - grcWindowBorder.top;

      FigureNewDxDyParameters ( &dx, &dy, FALSE, lpTB);

      grcWindowBorder.right  = grcWindowBorder.left   + dx;
      grcWindowBorder.top    = grcWindowBorder.bottom - dy;
      break;

    case HTBOTTOM : 
      grcWindowBorder.bottom = BOTTOMPOS;

      dy = grcWindowBorder.bottom - grcWindowBorder.top;

      FigureNewDxDyParameters ( &dx, &dy, FALSE, lpTB);

      grcWindowBorder.right     = grcWindowBorder.left   + dx;
      grcWindowBorder.bottom    = grcWindowBorder.top    + dy;
      break;

    case HTTOPLEFT: 
      grcWindowBorder.top    = TOPPOS;
      grcWindowBorder.left   = LEFTPOS;

      dy = grcWindowBorder.bottom - grcWindowBorder.top;
      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters ( &dx, &dy, (dx > dy), lpTB);

      grcWindowBorder.left   = grcWindowBorder.right  - dx;
      grcWindowBorder.top    = grcWindowBorder.bottom - dy;
      break;

    case HTTOPRIGHT : 
      grcWindowBorder.top    = TOPPOS;
      grcWindowBorder.right  = RIGHTPOS;

      dy = grcWindowBorder.bottom - grcWindowBorder.top;
      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters ( &dx, &dy, (dx > dy), lpTB);

      grcWindowBorder.right  = grcWindowBorder.left   + dx;
      grcWindowBorder.top    = grcWindowBorder.bottom - dy;
      break;

    case HTBOTTOMLEFT: 
      grcWindowBorder.bottom = BOTTOMPOS;
      grcWindowBorder.left   = LEFTPOS;

      dy = grcWindowBorder.bottom - grcWindowBorder.top;
      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters ( &dx, &dy, (dx > dy), lpTB);

      grcWindowBorder.left   = grcWindowBorder.right  - dx;
      grcWindowBorder.bottom = grcWindowBorder.top    + dy;
      break;

    case HTBOTTOMRIGHT: 
      grcWindowBorder.bottom = BOTTOMPOS;
      grcWindowBorder.right  = RIGHTPOS;

      dy = grcWindowBorder.bottom - grcWindowBorder.top;
      dx = grcWindowBorder.right - grcWindowBorder.left;

      FigureNewDxDyParameters ( &dx, &dy, (dx > dy), lpTB);

      grcWindowBorder.right  = grcWindowBorder.left   + dx;
      grcWindowBorder.bottom = grcWindowBorder.top    + dy;
      break;
    }
  }


//*************************************************************************
//
//
//
//*************************************************************************
void DrawInvertFrame (LPRECT rcFrame, BOOL bPopup, LPTOOLBAR lpTB)
  {
  HDC     hDC;
  HBRUSH  hOldBrush;
  DWORD   dwROP = PATINVERT;
  WORD    wWidth, wHeight;

  hDC = GetDC (NULL);

  hOldBrush = (HBRUSH)SelectObject (hDC, lpTB->hSizeInvBrush);

  wWidth  = GetSystemMetrics (SM_CXFRAME) - 1;
  wHeight = GetSystemMetrics (SM_CYFRAME) - 1;

  if (bPopup) {
    // Top edge
    PatBlt (hDC, rcFrame->left, rcFrame->top,    rcFrame->right-rcFrame->left, wHeight, dwROP);
    // Bottom edge
    PatBlt (hDC, rcFrame->left, rcFrame->bottom-wHeight, rcFrame->right-rcFrame->left, wHeight, dwROP);
    // Left Edge
    PatBlt (hDC, rcFrame->left,  rcFrame->top+wHeight,   wWidth, rcFrame->bottom-rcFrame->top-wHeight*2, dwROP);
    // Right Edge
    PatBlt (hDC, rcFrame->right-wWidth, rcFrame->top+wHeight,   wWidth, rcFrame->bottom-rcFrame->top-wHeight*2, dwROP);
    }
  else {
    DrawFocusRect (hDC, rcFrame);
    }

  SelectObject (hDC, hOldBrush);
  ReleaseDC (NULL, hDC);
  }



void SizeWindowMyWayDammit (HWND hWnd, LONG lHTCode, LPTOOLBAR lpTB)
  {
  MSG  msg;
  char szText[255];

  SetCapture (hWnd);

  GetWindowRect (hWnd, &grcWindowBorder);

  gMinMaxPts[3].x = GetSystemMetrics (SM_CXMINTRACK);
  gMinMaxPts[3].y = GetSystemMetrics (SM_CYMINTRACK);

  gMinMaxPts[4].x = (GetSystemMetrics (SM_CXSCREEN)+2*GetSystemMetrics(SM_CXFRAME));
  gMinMaxPts[4].y = (GetSystemMetrics (SM_CYSCREEN)+2*GetSystemMetrics(SM_CYFRAME));

  SendMessage ( hWnd, WM_GETMINMAXINFO, NULL, (LONG)(LPPOINT)gMinMaxPts );

  wsprintf ( szText, "MinSize is %dx%d, MaxSize is %dx%d\r\n",
             gMinMaxPts[3].x,
             gMinMaxPts[3].y,
             gMinMaxPts[4].x,
             gMinMaxPts[4].y );

  OutputDebugString ( szText );

  DrawInvertFrame (&grcWindowBorder, TRUE, lpTB);

  while (gbUserDragging) {
    while (PeekMessage (&msg, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD )) {
      TranslateMessage ( &msg );
      DispatchMessage ( &msg );
      }
    }
 
  DrawInvertFrame (&grcWindowBorder, TRUE, lpTB );

  ReleaseCapture ( );

  SetWindowPos (hWnd, 
                NULL,
                grcWindowBorder.left,
                grcWindowBorder.top,
                grcWindowBorder.right - grcWindowBorder.left,
                grcWindowBorder.bottom - grcWindowBorder.top,
                SWP_NOZORDER
               );
  }

/*********************************************************************
*                                                                    *
* wird aus WM_MOUSEMOVE aufgerufen                                   *
*                                                                    *
*********************************************************************/
void HandleUserDraggingMouse (HWND hWnd, LPARAM lParam, LONG lHTCode, LPTOOLBAR lpTB)
  {
  POINT pt;
  RECT  temprcWindowBorder;

  pt.x = LOWORD (lParam);
  pt.y = HIWORD (lParam);

  ClientToScreen (hWnd, &pt);

  temprcWindowBorder = grcWindowBorder;

  FigureNewWindowSize (&pt, lHTCode, lpTB);

  if ((temprcWindowBorder.left   != grcWindowBorder.left  ) ||
      (temprcWindowBorder.right  != grcWindowBorder.right ) ||
      (temprcWindowBorder.top    != grcWindowBorder.top   ) ||
      (temprcWindowBorder.bottom != grcWindowBorder.bottom)) {
    DrawInvertFrame (&temprcWindowBorder, TRUE, lpTB);
    DrawInvertFrame (&grcWindowBorder,    TRUE, lpTB);
    }
  }






/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/
DLLExport LONG _export FAR PASCAL PopupDockWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
  static LONG    lHTCode;
  static HCURSOR hSizeCursor;

//  int          i;
//  int          x, y;
//  int          iNumIcons;
//  RECT         rc;
//  PAINTSTRUCT  ps;
//  HDC          hDC;

  LPTOOLBAR lptb = LPTOOLBAR (GetWindowLong (hWnd, 0));

  switch (msg) {
/*
    case WM_NCCREATE:
      SizeWindowMyWayDammit (hWnd, lHTCode, lptb->pTBHdr);
      return DefWindowProc ( hWnd, msg, wParam, lParam );
      break;
*/      
    case WM_NCHITTEST:
      lHTCode = DefWindowProc (hWnd, msg, wParam, lParam);

#ifdef WIN32
      hSizeCursor = (HCURSOR)GetClassLong (hWnd, GCL_HCURSOR);
#else
      hSizeCursor = GetClassWord (hWnd, GCW_HCURSOR);
#endif

      if (!gbUserDragging)
        switch (lHTCode) {
          case HTLEFT    : 
          case HTRIGHT       : hSizeCursor = LoadCursor (NULL, IDC_SIZEWE); 
                               return HTCLIENT;

          case HTTOP       : 
          case HTBOTTOM      : hSizeCursor = LoadCursor (NULL, IDC_SIZENS); 
                               return HTCLIENT;

          case HTTOPLEFT   : 
          case HTBOTTOMRIGHT : hSizeCursor = LoadCursor (NULL, IDC_SIZENWSE);
                               return HTCLIENT;

          case HTTOPRIGHT   : 
          case HTBOTTOMLEFT  : hSizeCursor = LoadCursor (NULL, IDC_SIZENESW);
                               return HTCLIENT;
          }

      return lHTCode;

    case WM_SIZE:
      if (lptb != NULL) {
        bChangeState = TRUE;
        lptb->SizeOnParent (hWnd, 0, 0, LOWORD(lParam), HIWORD(lParam));
        }
      break;
      
    case WM_GETMINMAXINFO:
      ((LPPOINT)lParam)[3].x = GetSystemMetrics (SM_CXICON)-10;
      break;

    // Cursor-Form nur am Rahmen ändern
    case WM_SETCURSOR:
      {
      HWND hWndCursor = HWND(wParam);  // Fenster das den Cursor besitzt
      if (hWnd == hWndCursor) 
        if (hSizeCursor)
          SetCursor (hSizeCursor);
      }  
      break;

    case WM_MOUSEMOVE:
      if (gbUserDragging)
        HandleUserDraggingMouse (hWnd, lParam, lHTCode, lptb);
      break;
         
    case WM_LBUTTONDOWN:
      switch (lHTCode) {
        case HTLEFT     :
        case HTRIGHT     :
        case HTTOP     :
        case HTTOPLEFT    :
        case HTTOPRIGHT    :
        case HTBOTTOM    :
        case HTBOTTOMLEFT :
        case HTBOTTOMRIGHT : 
          gbUserDragging = TRUE;
          SizeWindowMyWayDammit (hWnd, lHTCode, lptb);
          break;
        }
      break;

    case WM_LBUTTONUP:
      gbUserDragging = FALSE;
      break;

    default :
      return DefWindowProc ( hWnd, msg, wParam, lParam );

    }
  return 0L ;
  }


int InitToolClass (HINSTANCE hInst)
  {
  int res = 1;

  WNDCLASS wc;
  if (!GetClassInfo(hInst, szToolbarClass, &wc)) {
    wc.lpszClassName = szToolbarClass;
    wc.style         = CS_DBLCLKS | CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)ToolbarWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = sizeof(LPVOID);
    wc.hInstance     = hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    wc.lpszMenuName  = NULL;

    if (RegisterClass(&wc)) {
      wc.style |= CS_NOCLOSE;
      wc.lpszClassName = szPopupDockWindow;
      wc.lpfnWndProc   = (WNDPROC)PopupDockWndProc;
      
      if (RegisterClass(&wc)) {
        wc.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW+1);
        wc.lpszClassName = "DOCKWINDOW";
        wc.lpfnWndProc   = (WNDPROC)DockWndProc;

        if (!RegisterClass(&wc))
          res = 0;
        }  
      }
    else  
      res = 0;
    }
  else
    res = 1;

  return res;
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
      hLibInst = hModule;
      InitToolClass (hLibInst);
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
  hLibInst = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return InitToolClass (hLibInst);
  }
}

#endif
