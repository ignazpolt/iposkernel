//
//  $Header:   P:/marille/clinicum/rev/movetool.cpv   1.17   05 Oct 1998 11:56:08   Gerhold  $
//  $Log:   P:/marille/clinicum/rev/movetool.cpv  $
// 
//    Rev 1.17   05 Oct 1998 11:56:08   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.16   10 Jun 1996 10:03:14   GERHOLD
// int FAR *  =>  DBINT FAR *
// 
//    Rev 1.15   24 Mar 1996 12:09:20   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.14   18 Mar 1996 16:25:08   GERHOLD
// Umwandeln von BitButton in MBitButton
// 
//    Rev 1.13   02 Feb 1996 10:35:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.12   07 Dec 1995 16:10:06   MARTIN
// statische Variable bei RESET wieder auf 0 setzen !
// 
//    Rev 1.11   07 Dec 1995 15:37:42   GERHOLD
// 
//    Rev 1.10   14 Sep 1995 15:35:20   GERHOLD
// Knoepfe links und rechts haben Pfeilchen
// 
//    Rev 1.9   24 Aug 1995 00:20:22   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.8   10 Aug 1995 10:04:46   HANNES
// 
//    Rev 1.7   05 Apr 1995 13:35:10   GERHOLD
// 
//    Rev 1.6   05 Apr 1995 10:45:48   GERHOLD
// 
//    Rev 1.5   04 Apr 1995 18:55:28   HANNES
// 
//    Rev 1.4   04 Apr 1995 15:39:04   HANNES
// 
//    Rev 1.3   04 Apr 1995 12:09:58   HANNES
//  
// 
//    Rev 1.2   27 Mar 1995 13:17:18   HANNES
//  
// 
//    Rev 1.1   22 Mar 1995 15:27:04   GERHOLD
// 
//    Rev 1.0   20 Mar 1995 08:45:56   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "cfield.hpp"
#include "mover.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "winextra.hpp"
#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "mdiclien.hpp"

#define MODULENUM 151
#include "winass.hpp"

#ifndef WIN32
#define  BF_RECT  2
#endif

#define  ANZBUTTONS  3

#define  LEFTBTN     0
#define  RIGHTBTN    1
#define  MOVEBTN     2


//***************************************************************************
//
//    Klasse MButton (ein einzelner Knopf)
//
//***************************************************************************
MButton::MButton ()
  {
  fsState = STATE_ENABLED;
  SetRectEmpty (&BtnRect);
  }

void MButton::Paint (HDC hDC)
  {
  if (fsState & STATE_PRESSED)
    MyDrawEdge (hDC, &BtnRect, MY_EDGE_BUTTONDOWN, MY_BF_RECT);
  else
    MyDrawEdge (hDC, &BtnRect, MY_EDGE_BUTTONUP, MY_BF_RECT);
  }

void MButton::InvalidateButton (HWND hWnd, BOOL bRedraw)
  {
  InvalidateRect (hWnd, &BtnRect, bRedraw);
  }


MBitButton::MBitButton (HBITMAP hbmp, int cols, int rows, int index) 
  {
  MButton::MButton();
  hBmp = hbmp;
  AnzCol = cols;
  AnzRow = rows;
  Index = index;
  }
  

//----------------------  Paint  --------------------------------------------
//
// zeichnet einen Knopf, in dem ein Bitmap zentriert angeordnet wird
//---------------------------------------------------------------------------
void MBitButton::Paint (HDC hDC)
  {
  MButton::Paint (hDC);                    // leeren Knopf zeichnen

  if (hBmp != 0) {
    BITMAP bi;
    GetObject (hBmp, sizeof(bi), &bi);
    int w = bi.bmWidth / AnzCol;           // errechne die Breite eines Bildes
    int h = bi.bmHeight / AnzRow;          // errechne die Höhe eines Bildes

    int Offset = 0;
    if (fsState & STATE_PRESSED)           // gedrueckter Knopf muss weiter rein
      Offset = 1;
  
    HDC hMemDC = CreateCompatibleDC (hDC);
    HBITMAP OldBitmap = (HBITMAP)SelectObject (hMemDC, hBmp);
    
    BitBlt (hDC, (BtnRect.left + BtnRect.right - w) / 2 + Offset, 
                 (BtnRect.top + BtnRect.bottom - h) / 2 + Offset,
                 w, h,
            hMemDC,
                 Index * w, 0,
                 SRCCOPY
          );

    SelectObject (hMemDC, OldBitmap);
    DeleteDC (hMemDC);
    }
  }

void TextButton::GetButtonExtent (HWND hWnd,int FAR *bw,int FAR *bh)
  {
  if (field == NULL) {
    field = new cField (TRANSPARENT,Format,0,0,-1,1,FALSE);
    field->SetWindow (hWnd);
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetVOrg (0,0,0);
    char MaxString [256];
    Parent->GetMaxString (MaxString);
    *field = MaxString;
    RECT r ;
    field->GetFieldRect(&r,0);
    PaintContext pc (hWnd,0xFFFF,0xFFFF,DO_WORK);
    pc.LogicalTwips (0,0);
    y0 = 1 ;
    w = pc.XLOGtoPHYS (r.right) + 2 * y0 + 20 ;
    h = pc.XLOGtoPHYS (r.bottom) + 2 * y0;
    field->SetWidth (r.right);
    field->SetVOrg (y0,y0,0);
    }
  *bw = w ;
  *bh = h ;
  }

void TextButton::Paint (HDC hDC)
  {
  MButton::Paint (hDC);
  if (field != NULL) {
    Parent->WriteValue ();
    PaintContext pc ;
    pc.SetDC (hDC);
    pc.LogicalTwips (BtnRect.left+y0,y0);
    field->Paint (hDC,0,FALSE);
    }
  }
//***************************************************************************
//
//    Klasse MoveButton (das gesamte Steuerelement)
//
//***************************************************************************
MoveButton::MoveButton (BOOL bHorizontal,int Format)
  {
  hMyWnd = 0;
  CurrentPos = 0;
  pCaptureButton = NULL;
  ptCaptured.x = 0;
  ptCaptured.y = 0;

  bTimerSet = FALSE;
  
  bHorz = bHorizontal;
  
  // Bitmap fuer die Knoepfe links und rechts
  hBmp = LoadBitmap (WBase::hInstance, "BUTTONS");
  
  // ACHTUNG: wird das Bitmap geaendert ist der Ofen aus!!!
  //          Das Bitmap besteht aus 12 Teilbitmaps, wobei
  //          die Indizes 2 und 3 verwendet werden.
  if (hBmp != 0) {
    btn[LEFTBTN] = new MBitButton (hBmp, 12, 1, 2);
    btn[RIGHTBTN] = new MBitButton (hBmp, 12, 1, 3);
    }
  else {
    btn[LEFTBTN] = new MButton ();
    btn[RIGHTBTN] = new MButton ();
    }
    
  // der Knopf in dem der Text untergebracht ist
  btn[MOVEBTN] = new TextButton (this,Format);
  }


MoveButton::~MoveButton ()
  {
  delete btn[LEFTBTN];
  delete btn[RIGHTBTN];
  delete btn[MOVEBTN];
  
  if (hBmp)
    DeleteObject (hBmp);
  }

//----------------------  SetWindow  ----------------------------------------
//
// Setzt das Fensterhandle fuer das Steuerelement.
//---------------------------------------------------------------------------
void MoveButton::SetWindow (HWND hWnd)
  {
  hMyWnd = hWnd;
  }

//----------------------  SetMoveArea  --------------------------------------
//
// Die Ausdehnung des Steuerelementes ohne die beiden Rand-Knoepfe.
//---------------------------------------------------------------------------
void MoveButton::SetMoveArea (RECT rc)
  {
  if (bHorz)
    MoveArea = rc.right - btn[LEFTBTN]->BtnRect.right - 
               (btn[RIGHTBTN]->BtnRect.right - btn[RIGHTBTN]->BtnRect.left);
  else             
    MoveArea = rc.bottom - btn[LEFTBTN]->BtnRect.bottom - 
               (btn[RIGHTBTN]->BtnRect.bottom - btn[RIGHTBTN]->BtnRect.top);
  }
  
//----------------------  GetButtonWidth  -----------------------------------
//
// Die Ausdehnung des Knopfes der bewegt werden kann.
//---------------------------------------------------------------------------
int MoveButton::GetButtonWidth ()
  {
  int w,h;
  if (bHorz) {
    ((TextButton FAR *)btn[MOVEBTN])->GetButtonExtent (hMyWnd,&w,&h);
    }
  else
    w = GetSystemMetrics (SM_CXVSCROLL) + 2 * GetSystemMetrics(SM_CXBORDER);  

  return w;
  }

//----------------------  GetButtonWidth  -----------------------------------
//
// Die Ausdehnung des Knopfes der bewegt werden kann.
//---------------------------------------------------------------------------
int MoveButton::GetButtonHeight ()
  {
  int w,h;
  if (bHorz) {
    ((TextButton FAR *)btn[MOVEBTN])->GetButtonExtent (hMyWnd,&w,&h);
    }
  else
    h = 100;

  return h;
  }
  
//----------------------  GetTextFormat  ------------------------------------
//
// 
//---------------------------------------------------------------------------
WORD  MoveButton::GetTextFormat ()
  {
  return 0;
  }

//----------------------  GetMoveArea  --------------------------------------
//
//
//---------------------------------------------------------------------------
int MoveButton::GetMoveArea (void)
  {
  return MoveArea;
  }

//----------------------  PaintDecreaseButton  ------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::PaintDecreaseButton (HDC hDC)
  {
  btn[LEFTBTN]->Paint (hDC);
  }

//----------------------  PaintIncreaseButton  ------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::PaintIncreaseButton (HDC hDC)
  {
  btn[RIGHTBTN]->Paint (hDC);
  }

//----------------------  PaintMoveButton  ----------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::PaintMoveButton (HDC hDC)
  {
  btn[MOVEBTN]->Paint (hDC);
  }

//----------------------  PaintMover  ---------------------------------------
//
// zeichnet das gesamte Steuerelement
//---------------------------------------------------------------------------
void MoveButton::PaintMover (HDC hDC)
  {
  GetClientRect (hMyWnd, &rcClient);

  PaintDecreaseButton (hDC);
  PaintIncreaseButton (hDC);
  PaintMoveButton (hDC);
  }

//----------------------  SetButtonTimer  -----------------------------------
//
// Setzt den Timer und gibt Intervallwerte vor.
//---------------------------------------------------------------------------
void MoveButton::SetButtonTimer (void)
  {
  if (!bTimerSet) {
    bTimerSet = TRUE;
    TimerInterval = 0;
    Cnt = 1;
    Incr = 25;
    SetTimer (hMyWnd, 0, 50, NULL);
    }
  }
  
//----------------------  RemoveButtonTimer  --------------------------------
//
// entfernt den Timer.
//---------------------------------------------------------------------------
void MoveButton::RemoveButtonTimer (void)
  {
  if (bTimerSet) {
    KillTimer (hMyWnd, 0);
    CalculateMoveRange (pCaptureButton == btn[MOVEBTN]);
    bTimerSet = FALSE;
    }
  }

//---------------------------------------------------------------------------
// Der Timer laeuft am Anfang langsam ab (3 mal).
// Dann wird die Frequenz verdoppelt (3 mal mit schnellerer Timer), bis das 
// Maximum erreicht ist. Dann wird der Timer ohne Verzoegerung ausgefuehrt
//---------------------------------------------------------------------------
void MoveButton::OnTimer ()
  {
  if (pCaptureButton != NULL) {
    TimerInterval += Incr;
    if (TimerInterval >= 500) {
      Cnt++;
      TimerInterval = 0;

      if (pCaptureButton == btn[LEFTBTN])
        DecreaseValue ();
      else
      if (pCaptureButton == btn[RIGHTBTN])
        IncreaseValue ();
      else {
        // Der Schiebeknopf will was!
        if (pCaptureButton->fsState & STATE_DECREASE)
          DecreaseValue ();
        else if (pCaptureButton->fsState & STATE_INCREASE)
          IncreaseValue ();
        }  
      }
    
    // nach 3 mal wird die Frequenz verdoppelt
    if ((Cnt % 4) == 0) {
      Incr *= 2;
      if (Incr > 500)  // Maximalfrequenz
        Incr = 500;
        
      Cnt = 1;
      }
    }
  }
  
//----------------------  OnLButtonDown  ------------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::OnLButtonDown (POINT pt)
  {
  SetCapture(hMyWnd);
  
  int i;
  BOOL bFound = FALSE;
  for (i = 0; i < ANZBUTTONS; i++) {
    if (PtInRect(&btn[i]->BtnRect, pt)) {
      bFound = TRUE;
      break;
      }
    }
      
  if (bFound) {
    pCaptureButton = btn[i];

    ptCaptured.x = pt.x;
    ptCaptured.y = pt.y;

    ptOffs.x = pt.x - btn[i]->BtnRect.left;
    ptOffs.y = pt.y - btn[i]->BtnRect.top;

    if (btn[i]->fsState & STATE_ENABLED) {
      btn[i]->fsState |= STATE_PRESSED;
      btn[i]->InvalidateButton(hMyWnd, FALSE);
      UpdateWindow (hMyWnd);

      // linker und rechter Knopf loesen den Timer aus und beginnen
      // aber sofort den Wert zu erhoehen oder erniedrigen!
      if (i != 2) {
        SetButtonTimer ();

        if (i == 0)
          DecreaseValue ();
        else
          IncreaseValue ();
        }    
      }
    }    
  }

//----------------------  OnLButtonUp  --------------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::OnLButtonUp (POINT pt)
  {
  ReleaseCapture ();

  if (pCaptureButton != NULL) {
    int i;
    BOOL bFound = FALSE;
    for (i = 0; i < ANZBUTTONS; i++) {
      if (PtInRect(&btn[i]->BtnRect, pt)) {
        bFound = TRUE;
        break;
        }
      }

    if (bFound) {
      if ((pCaptureButton->fsState & STATE_ENABLED) && 
          (pCaptureButton == btn[i])) {
        }
      }
          
    RemoveButtonTimer ();

    pCaptureButton->fsState &= ~STATE_PRESSED;
    pCaptureButton->InvalidateButton(hMyWnd, TRUE);

    if (bHorz) {
      CurrentPos = (rcClient.right - rcClient.left - GetButtonWidth()) / 2;
      SetRect (&btn[MOVEBTN]->BtnRect, CurrentPos, 0, 
               CurrentPos + GetButtonWidth(), rcClient.bottom);
      }
    else { 
      CurrentPos = (rcClient.bottom - rcClient.top - GetButtonHeight()) / 2;
      SetRect (&btn[MOVEBTN]->BtnRect, 0, CurrentPos,
               rcClient.right, CurrentPos + GetButtonHeight());
      }


    pCaptureButton->InvalidateButton(hMyWnd, FALSE);
    pCaptureButton = NULL;

    // Wenn der Timer gesetzt war, wird CalculateMoveRange halt einmal 
    // zuviel aufgerufen (zuerst in "RemoveButtonTimer"). War aber kein
    // Timer gesetzt, dann ist das hier sehr notwendig!!
    CalculateMoveRange (FALSE);
    DoIt ();
    }
  }

//----------------------  OnMouseMove  --------------------------------------
//
//
//---------------------------------------------------------------------------
void MoveButton::OnMouseMove (POINT pt)
  {
  if ((pCaptureButton != NULL) && (pCaptureButton->fsState & STATE_ENABLED)) {

    int i, Delta;
    
    BOOL bFound = FALSE;
    for (i = 0; i < ANZBUTTONS; i++) {
      if (PtInRect(&btn[i]->BtnRect, pt)) {
        bFound = TRUE;
        break;
        }
      }

    if (pCaptureButton == btn[MOVEBTN]) {
      // Die Maus darf nur im erlaubten Bereich bleiben
      if (bHorz) {
        if (!(pCaptureButton->fsState & STATE_INCREASE)) {
          if (pt.x - ptOffs.x < btn[LEFTBTN]->BtnRect.right) {
            pt.x = btn[LEFTBTN]->BtnRect.right + ptOffs.x;
            pCaptureButton->fsState |= STATE_DECREASE;
            SetButtonTimer ();
            }
          else {
            RemoveButtonTimer ();
            pCaptureButton->fsState &= ~STATE_DECREASE;
            }
          }  
          
        if (!(pCaptureButton->fsState & STATE_DECREASE)) {
          if (pt.x - ptOffs.x > btn[RIGHTBTN]->BtnRect.left - (btn[MOVEBTN]->BtnRect.right - btn[MOVEBTN]->BtnRect.left)) {
            pt.x = btn[RIGHTBTN]->BtnRect.left + ptOffs.x - (btn[MOVEBTN]->BtnRect.right - btn[MOVEBTN]->BtnRect.left);
            pCaptureButton->fsState |= STATE_INCREASE;
            SetButtonTimer ();
            }
          else {
            RemoveButtonTimer ();
            pCaptureButton->fsState &= ~STATE_INCREASE;
            }
          }  

        Delta = pt.x - ptCaptured.x;     // Verschiebung zur vorigen Position
        ptCaptured.x = pt.x;
        }
      else {
        if (!(pCaptureButton->fsState & STATE_INCREASE)) {
          if (pt.y - ptOffs.y < btn[LEFTBTN]->BtnRect.bottom) {
            pt.y = btn[LEFTBTN]->BtnRect.bottom + ptOffs.y;
            pCaptureButton->fsState |= STATE_DECREASE;
            SetButtonTimer ();
            }
          else {
            RemoveButtonTimer ();
            pCaptureButton->fsState &= ~STATE_DECREASE;
            }
          }  
          
        if (!(pCaptureButton->fsState & STATE_DECREASE)) {
          if (pt.y - ptOffs.y > btn[RIGHTBTN]->BtnRect.top - (btn[MOVEBTN]->BtnRect.bottom - btn[MOVEBTN]->BtnRect.top)) {
            pt.y = btn[RIGHTBTN]->BtnRect.top + ptOffs.y - (btn[MOVEBTN]->BtnRect.bottom - btn[MOVEBTN]->BtnRect.top);
            pCaptureButton->fsState |= STATE_INCREASE;
            SetButtonTimer ();
            }
          else {
            RemoveButtonTimer ();
            pCaptureButton->fsState &= ~STATE_INCREASE;
            }
          }

        Delta = pt.y - ptCaptured.y;     // Verschiebung zur vorigen Position
        ptCaptured.y = pt.y;
        }
        
      if (Delta != 0) {
        btn[MOVEBTN]->InvalidateButton (hMyWnd, TRUE);  // altes loeschen

        int Size;

        if (bHorz) {
          OffsetRect (&btn[MOVEBTN]->BtnRect, Delta, 0);     // verschieben
          pt.x = btn[MOVEBTN]->BtnRect.left;
          CurrentPos = pt.x - btn[LEFTBTN]->BtnRect.right;
          Size = GetMoveArea() - GetButtonWidth();
          }
        else {
          OffsetRect (&btn[MOVEBTN]->BtnRect, 0, Delta);     // verschieben
          pt.y = btn[MOVEBTN]->BtnRect.top;
          CurrentPos = pt.y - btn[LEFTBTN]->BtnRect.bottom;
          Size = GetMoveArea() - GetButtonHeight();
          }  
      
        CalculateMoverValue (Size);                   // neuen Wert berechnen

        btn[MOVEBTN]->InvalidateButton (hMyWnd, FALSE);
        }
      }
  
    BOOL fSameButton = bFound && (pCaptureButton == btn[i]);
    if (fSameButton == !(pCaptureButton->fsState & STATE_PRESSED)) {
      pCaptureButton->fsState ^= STATE_PRESSED;
      pCaptureButton->InvalidateButton (hMyWnd, FALSE);
      }
    }
  }  


#ifdef WIEDERMITTEST
//***************************************************************************
//* 
//*  Ableitung der Basisklasse zu Testzwecken
//*
//***************************************************************************
//----------------------  SetMinMaxValues  ----------------------------------
//
// Die maximalen Werte die erreicht werden koennen.
//---------------------------------------------------------------------------
void LongButton::SetMinMaxValues (LONG lMin, LONG lMax)
  {
  Min = lMin;
  Max = lMax;
  }

//----------------------  SetMoveRange  -------------------------------------
//
// Die Werte die innerhalb des bewegenden Bereiches sichtbar sind.
//---------------------------------------------------------------------------
void LongButton::SetMoveRange (LONG rMin, LONG rMax)
  {
  MinMove = rMin;
  MaxMove = rMax;
  }

//----------------------  GetRange  -----------------------------------------
//
// Gibt das Intervall von Minimal- bis Maximalwert zurueck.
//---------------------------------------------------------------------------
int LongButton::GetRange (void)
  {
  return (int)(MaxMove - MinMove);
  }

//----------------------  CalculateMoveRange  -------------------------------
//
// Berechnet anhand des aktuellen Wertes das Intervall.
// Parameter :  <bOffset> ... TRUE => dem Minimalwert fuer den "Move-Bereich"
//                                    muss der aktuelle Wert der "Move"-
//                                    Variablen zugewiesen werden.
//                            FALSE => der Minimalwert ist der Variablenwert
//                                     abzueglich dem halben "Move-Bereich".
//---------------------------------------------------------------------------
void LongButton::CalculateMoveRange (BOOL bOffset)
  {
  DWORD iRange = GetRange ();  // den Bereich merken

  LONG lMinMove;
  if (bOffset)
    lMinMove = DummyValue;
  else
    lMinMove = DummyValue - (iRange / 2);

  LONG lMaxMove = lMinMove + iRange;

  SetMoveRange (lMinMove, lMaxMove);  // da drin kann ich mich bewegen
  }

//----------------------  WriteValue  ---------------------------------------
//
//
//---------------------------------------------------------------------------
void LongButton::WriteValue (LONG lValue)
  {
  static char szBuf[10];

  wsprintf (szBuf, "%ld", lValue);
  LPTEXTBUTTON(btn[MOVEBTN])->SetText (szBuf);

  btn[MOVEBTN]->InvalidateButton (hMyWnd, TRUE);
  }

//----------------------  IncreaseValue  ------------------------------------
//
//
//---------------------------------------------------------------------------
void LongButton::IncreaseValue (void)
  {
  if (++DummyValue > Max)
    DummyValue = Max;

  WriteValue (DummyValue);
  }
  
//----------------------  DecreaseValue  ------------------------------------
//
//
//---------------------------------------------------------------------------
void LongButton::DecreaseValue (void)
  {
  static char szBuf[10];
  
  if (--DummyValue < Min)
    DummyValue = Min;

  WriteValue (DummyValue);
  }

//----------------------  CalculateMoverValue  ------------------------------
//
// Berechnet den Wert, der sich aus der Bewegung des Knopfes ergibt.
// Parameter:  <Size> ... Groesse des zur verfuegung stehenden Bereiches
//                        abzueglich der Abmessungen des Knopfes.
//---------------------------------------------------------------------------
void LongButton::CalculateMoverValue (int Size)
  {
  static char szBuf[10];

  float fDVal = (float(CurrentPos) / float(Size)) * GetRange() + MinMove;
  LONG DVal = LONG(fDVal);
  DummyValue = DVal;

  WriteValue (DummyValue);
  }


//***************************************************************************
//* 
//*  Ableitung der Basisklasse zu Testzwecken
//*
//***************************************************************************
//----------------------  SetMinMaxValues  ----------------------------------
//
// Die maximalen Werte die erreicht werden koennen.
//---------------------------------------------------------------------------
void floatButton::SetMinMaxValues (float lMin, float lMax)
  {
  Min = lMin;
  Max = lMax;
  }

//----------------------  SetMoveRange  -------------------------------------
//
// Die Werte die innerhalb des bewegenden Bereiches sichtbar sind.
//---------------------------------------------------------------------------
void floatButton::SetMoveRange (float rMin, float rMax)
  {
  MinMove = rMin;
  MaxMove = rMax;
  }

//----------------------  GetRange  -----------------------------------------
//
// Gibt das Intervall von Minimal- bis Maximalwert zurueck.
//---------------------------------------------------------------------------
float floatButton::GetRange (void)
  {
  return (float)(MaxMove - MinMove);
  }

//----------------------  CalculateMoveRange  -------------------------------
//
// Berechnet anhand des aktuellen Wertes das Intervall.
//---------------------------------------------------------------------------
void floatButton::CalculateMoveRange (BOOL bOffset)
  {
  float fRange = GetRange ();
  float fMinMove = floatValue - (fRange / 2);
  float fMaxMove = fMinMove + fRange;

  SetMoveRange (fMinMove, fMaxMove);  // da drin kann ich mich bewegen
  }

void prfloat (LPSTR szBuf, float f)
  {
  }

void floatButton::WriteValue (float fValue)
  {
  static char szBuf[10];
  
  prfloat (szBuf, fValue);
  LPTEXTBUTTON(btn[MOVEBTN])->SetText (szBuf);

  btn[MOVEBTN]->InvalidateButton (hMyWnd, TRUE);
  }

//----------------------  IncreaseValue  ------------------------------------
//
//
//---------------------------------------------------------------------------
void floatButton::IncreaseValue (void)
  {
  floatValue += fStep;
  if (floatValue > Max)
    floatValue = Max;

  WriteValue (floatValue);
  }
  
//----------------------  DecreaseValue  ------------------------------------
//
//
//---------------------------------------------------------------------------
void floatButton::DecreaseValue (void)
  {
  floatValue -= fStep;
  if (floatValue < Min)
    floatValue = Min;

  WriteValue (floatValue);
  }

//----------------------  CalculateMoverValue  ------------------------------
//
// Berechnet den Wert, der sich aus der Bewegung des Knopfes ergibt.
// Parameter:  <Size> ... Groesse des zur verfuegung stehenden Bereiches
//                        abzueglich der Abmessungen des Knopfes.
//---------------------------------------------------------------------------
void floatButton::CalculateMoverValue (int Size)
  {
  float fDVal = (float(CurrentPos) / float(Size)) * GetRange() + MinMove;

  WriteValue (floatValue);
  }
#endif


long FAR PASCAL MoverWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
  LPMOVEBUTTON lpmb = (LPMOVEBUTTON)GetWindowLong (hWnd, 0);

  switch (message) {
    case WM_CREATE:
      {
      }
      break;

    // nimmt die Abmessungen des Elternfensters, und paßt sich an
    case WM_SIZE:
      {
      if (lpmb != NULL) {
        RECT rc;
        GetClientRect (GetParent(hWnd), &rc);
  
        int w = lpmb->GetButtonWidth();
        int h = lpmb->GetButtonHeight();
  
        if (lpmb->bHorz) {
          SetRect (&lpmb->btn[LEFTBTN]->BtnRect, 0, 0, h, h-1);
          SetRect (&lpmb->btn[RIGHTBTN]->BtnRect, rc.right-h, 0, rc.right, h-1);
          }
        else {
          SetRect (&lpmb->btn[LEFTBTN]->BtnRect, 0, 0, w, w-1);
          SetRect (&lpmb->btn[RIGHTBTN]->BtnRect, 0, rc.bottom-w, w, rc.bottom);
          }  

        lpmb->SetMoveArea (rc);
        if (lpmb->bHorz) {
          lpmb->CurrentPos = (rc.right - rc.left - lpmb->GetButtonWidth()) / 2;

          SetRect (&lpmb->btn[MOVEBTN]->BtnRect, lpmb->CurrentPos, 0, 
                   lpmb->CurrentPos + lpmb->GetButtonWidth(), h-1);
  
          MoveWindow (hWnd, -1, rc.bottom-h, rc.right+2, h+1, TRUE);
          }
        else {
          lpmb->CurrentPos = (rc.bottom - rc.top - lpmb->GetButtonHeight()) / 2;

          SetRect (&lpmb->btn[MOVEBTN]->BtnRect, 0, lpmb->CurrentPos,
                   w-1, lpmb->CurrentPos + lpmb->GetButtonHeight());
  
          MoveWindow (hWnd, rc.right-w, -1, w+1, rc.bottom+1, TRUE);
          }  
        }
      }
      break;
      
    case WM_PAINT:
      {
      PAINTSTRUCT PS;
      HDC hDC = BeginPaint (hWnd, &PS);

      lpmb->PaintMover (hDC);

      EndPaint (hWnd, &PS);
      }
      break;

    case WM_LBUTTONDOWN :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif
      lpmb->OnLButtonDown (pt);
      }
      break;

    case WM_LBUTTONUP :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif
      lpmb->OnLButtonUp (pt);
      }
      break;
      
    case WM_MOUSEMOVE :
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lParam, pt);
#else
      pt = MAKEPOINT (lParam);
#endif
      lpmb->OnMouseMove (pt);
      }
      break;

    case WM_TIMER :
      lpmb->OnTimer ();
      break;

    case WM_DESTROY: 
      delete lpmb;
      break;

    default:
      return (DefWindowProc(hWnd, message, wParam, lParam));
    }

  return (NULL);
  }





BOOL InitMover ()
  {
  static BOOL bRegistered = FALSE;

  if (!bRegistered) {
    WNDCLASS  wc;
  
    wc.style = NULL;
    wc.lpfnWndProc = MoverWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = WBase::hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "MOVER";
  
    if (RegisterClass(&wc))
      bRegistered = TRUE;
    }
    
  return bRegistered;  
  }
  
HWND CreateMoverWindow (HWND hWndParent, LPMOVEBUTTON lpmb)
  {
  HWND hWndMover = 0;
  if (InitMover ()) {
    RECT rc;
    GetClientRect (hWndParent, &rc);

    hWndMover = CreateWindow ("MOVER", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                               0, 0, 10, 10,
                               hWndParent, 0, WBase::hInstance, NULL);
    if (hWndMover) {
      SetWindowLong (hWndMover, 0, LONG(lpmb));
      lpmb->SetWindow (hWndMover);
      SendMessage (hWndMover, WM_SIZE, 0, 0);
      }
    }
    
  return hWndMover;  
  }

#pragma pack(1)
struct SetDataMover_param {
  WORD parSize;
  DWORD res;
  DWORD Format;
  DWORD dateFormat;
  DWORD anzDays;
  DWORD incDays;
  DWORD RangeMin;
  DWORD RangeMax;
  };
#pragma pack()

static packdate _res ;
packdate FAR &operator + (packdate FAR &p1,int AnzDays)
  {
  LONG t = PackTime (&p1);
  LONG d = LONG(AnzDays);
  d *= LONG (24) * LONG (60) * LONG (60) ;
  t += d ;
  UnPackTime (t,&_res);
  return _res ;
  }
packdate operator - (packdate FAR &p1,int AnzDays)
  {
  LONG t = PackTime (&p1);
  LONG d = LONG(AnzDays);
  d *= LONG (24) * LONG (60) * LONG (60) ;
  t -= d ;
  UnPackTime (t,&_res);
  return _res ;
  }

class DateButton : public MoveButton {
 private :
  packdate pi,dmin,dmax,dimin,dimax;
  int mDays,di;
  SetDataMover_param FAR *p;
  LPSTR dateFormat;
  mdiChild *c;
 public :
  void SetMoveRange (int iDays,int incDays)
    { mDays = iDays ; di = incDays ; CalculateMoveRange () ; }
  void SetMinMaxValues (packdate FAR *pmin,packdate FAR *pmax)
    { dmin = *pmin , dmax = *pmax ; } 
  DateButton (mdiChild FAR *m,SetDataMover_param FAR *par,int Format,BOOL bHorizontal) : MoveButton (bHorizontal,Format) 
    { 
    c = m ;
    p = par ;
    packdate FAR *iDate = (packdate FAR *) c->ReadlData (p->res);
    DBINT FAR *AnzDays = (DBINT FAR *) c->ReadlData (p->anzDays);
    DBINT FAR *incDays = (DBINT FAR *) c->ReadlData (p->incDays);
    packdate FAR *mDate = (packdate FAR *) c->ReadlData (p->RangeMin);
    packdate FAR *xDate = (packdate FAR *) c->ReadlData (p->RangeMax);
    dateFormat = LPSTR (c->ReadlData (p->dateFormat));
    DBWIN_ASSERT ((iDate != NULL) && (AnzDays != NULL) && (mDate != NULL) && (xDate != NULL) && (dateFormat != NULL) && (incDays != NULL)) ;
    pi = *iDate ; 
    SetMoveRange (*AnzDays,*incDays);
    SetMinMaxValues (mDate,xDate);
    }
  virtual void CalculateMoveRange (BOOL bOffset = FALSE)
    {
    if (bOffset) {
      if (pCaptureButton->fsState & STATE_INCREASE) {
        dimax = pi ;
        dimin = dimax - mDays * di * 2;
        }
      else {
        dimin = pi ;
        dimax = dimin + mDays * di * 2;
        }
      }
    else {
      dimax = pi + mDays * di ;
      dimin = pi - mDays * di ;
      }
    }
  void WriteValue ()
    {
    char szBuf[128];
    FormatDate (szBuf,&pi,dateFormat);
    LPTEXTBUTTON(btn[MOVEBTN])->SetText (szBuf);
    }
  void SetValue (packdate FAR *di)
    {
    pi = *di ;
    WriteValue ();
    btn[MOVEBTN]->InvalidateButton (hMyWnd, TRUE);
    }
  virtual void IncreaseValue ()
    {
    pi = pi + di ;
    InvalidateButton ();
    }
  virtual void DecreaseValue ()
    {
    pi = pi - di ;
    InvalidateButton ();
    }
  virtual void CalculateMoverValue (int Size)
    {
    LONG t0 = PackTime (&dimin);
    LONG t1 = PackTime (&dimax);
    LONG t = LONG (double(t1 - t0) * double (CurrentPos) / double (Size)) + 
            12L * 60L * 60L * LONG(di);
    t = (t / (24L * 60L * 60L * LONG(di))) * 24L * 60L * 60L * LONG(di) + t0 ;
    UnPackTime (t,&pi);
    InvalidateButton ();
    }
  virtual void DoIt ()
    {
    packdate FAR *oldVal = (packdate FAR *) c->ReadlData (p->res);
    DBWIN_ASSERT (oldVal != NULL);
    if (!lmemcmp (oldVal,&pi,sizeof(pi)))
      c->WritelData (p->res,&pi,sizeof(pi),LPSTR(p)-sizeof(WORD));
    }
  virtual void GetMaxString (LPSTR maxstring) { 
    lstrcpy (maxstring,"31. September 1888") ;
    }
  };

static HWND ChildWithMover = 0;
static HWND hMover = 0;
BOOL SetDateMover (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WIN_ASSERT((ChildWithMover == 0) && (hMover == 0));
    ChildWithMover = c->OutWnd();
    SetDataMover_param FAR * par = (SetDataMover_param FAR *)param ;
    DBINT FAR *lpFormat = (DBINT FAR *) c->ReadlData (par->Format);
    DBWIN_ASSERT (lpFormat != NULL) ;
    hMover = CreateMoverWindow (c->OutWnd(),new DateButton(c,par,*lpFormat,TRUE)) ;
    LONG oldStyle = GetWindowLong (c->OutWnd(),GWL_STYLE);
    SetWindowLong (c->OutWnd(),GWL_STYLE,oldStyle & ~(WS_HSCROLL)) ;
    }
  if (mode & EM_UPDATE) {
    DateButton FAR *lpmb = (DateButton FAR *)GetWindowLong (hMover, 0);
    SetDataMover_param FAR * par = (SetDataMover_param FAR *)param ;
    DBINT FAR *AnzDays = (DBINT FAR *) c->ReadlData (par->anzDays) ;
    DBINT FAR *incDays = (DBINT FAR *) c->ReadlData (par->incDays);
    DBWIN_ASSERT (AnzDays != NULL);
    lpmb->SetMoveRange (*AnzDays,*incDays);
    packdate FAR *di = (packdate FAR *)c->ReadlData (par->res);
    DBWIN_ASSERT (di != NULL);
    lpmb->SetValue (di);
    }
  if (mode & EM_FIXCONNECTION) {
    SetDataMover_param FAR * par = (SetDataMover_param FAR *)param ;
    c->SetlConnection (par->res,LPSTR(param) - sizeof(WORD)) ;
    c->SetlConnection (par->anzDays,LPSTR(param) - sizeof(WORD)) ;
    c->SetlConnection (par->incDays,LPSTR(param) - sizeof(WORD)) ;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetDataMover_param FAR * par = (SetDataMover_param FAR *)param ;
    c->ClearlConnection (par->res,LPSTR(param) - sizeof(WORD)) ;
    c->ClearlConnection (par->anzDays,LPSTR(param) - sizeof(WORD)) ;
    c->ClearlConnection (par->incDays,LPSTR(param) - sizeof(WORD)) ;
    ChildWithMover = 0;
    hMover = 0;
    }
  return FALSE ;
  }

void SetNewMoverDimension (HWND hWnd,LPARAM lP)
  {
  if (hWnd == ChildWithMover)
    MoveWindow (hMover,0,0,LOWORD(lP),HIWORD(lP),TRUE);
  }
