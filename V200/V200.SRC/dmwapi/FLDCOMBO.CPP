//////////////////////////////////////////////////////////////
//    Combo-Buttons für das cField
//////////////////////////////////////////////////////////////
//    $Header:   P:/marille/clinicum/dmwapi/rev/fldcombo.cpv   1.8   05 Oct 1998 11:11:46   Gerhold  $
//    $Log:   P:/marille/clinicum/dmwapi/rev/fldcombo.cpv  $
// 
//    Rev 1.8   05 Oct 1998 11:11:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   22 Mar 1996 12:13:24   HANNES
// Aenderungen Hannes
// 
//    Rev 1.6   02 Feb 1996 10:46:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   15 Jan 1996 17:58:28   MARTIN
// falsche Berechnung der Feldbreite bei Combo-Button korrigiert
// 
//    Rev 1.4   07 Sep 1995 13:52:06   HANNES
// 
//    Rev 1.3   04 Apr 1995 16:44:20   HANNES
// 
//    Rev 1.2   16 Feb 1995 12:36:40   GERHOLD
// 
//    Rev 1.1   19 Oct 1994 15:02:16   HANNES
// Vergroesserungen bei ViewPortOrg != (0,0)
// 
//    Rev 1.0   25 Jul 1994 09:46:10   GERHOLD
// Initial revision.
//////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"
#include "fldcombo.hpp"


cFieldCombo::cFieldCombo (void)            
  { 
  ListIsDown = FALSE; 
  MyField = NULL; 
  SetRectEmpty (LPRECT(&rcBtn));
  }

int GetLineDimension (cField FAR *field)
  {
  POINT pt[2];
  pt[0].x = 1 ;  pt[0].y = 0 ;
  pt[1].x = 0 ;  pt[1].y = 0 ;
  HDC hDC = field->GetFieldDC();
  DPtoLP (hDC,pt,2);
  field->RestDC (hDC);
  return pt[0].x - pt[1].x;
  }

static BOOL WithoutButton = FALSE;

void cFieldCombo::OnMapChange (cField FAR* field)
  {
  if ((field == MyField) && (field->HasButton)) {
    int h = field->LineHeight ();
    int w = h * 3 / 4 ;
    
    RECT rc;
    int lw = GetLineDimension(field);
    WithoutButton = TRUE;
    field->GetFullTextRect (LPRECT(&rc),field->FirstPage() + field->LastPage());   // Größe des cFields
    WithoutButton = FALSE;
    if (w < 0) w = -w ;
    int mtop;
    if (h < 0)
      mtop = rc.bottom;
    else
      mtop = rc.top;
    rcBtn.left = rc.right+1+lw;             // den Combo-Button berechnen
    rcBtn.top = mtop;
    rcBtn.right = rcBtn.left+w;
    if (h < 0)
      rcBtn.bottom = rcBtn.top+h-lw;
    else
      rcBtn.bottom = rcBtn.top+h+lw;

    // etwas schwindeln um die Poygonkoordinaten an das Rechteck anzupassen.
    // Zuordnung wie oben, nur fehlt "lw".
    rcPoly.left = rc.right+1+lw;
    rcPoly.top = mtop;
    rcPoly.right = rcBtn.left+w-lw;
    rcPoly.bottom = rcBtn.top+h;
    }
  }

void cFieldCombo::OnSetFocus (cField FAR* field)
  {
  MyField = NULL;

  if ((field != NULL) && (field->HasButton)) {
    // Größe des Knopfes ermitteln
    MyField = field;
    OnMapChange (field);
    }
  }
  
BOOL cFieldCombo::GetBtnRect (cField FAR *field,LPRECT r)
  {
  if ((field == MyField) && (MyField->HasButton) && (!WithoutButton)) {
    CopyRect (r,&rcBtn);
    return TRUE ;
    }
  else {
    SetRectEmpty (r);
    return FALSE ;
    }
  }

void cFieldCombo::OnKillFocus (cField FAR* field)
  {
  if (!ListIsDown) 
    MyField = field;
  }

void GetLogPolygon (LPPOINT res, LPPOINT rel, LPRECT r, int Anz)
  {
  for (int i = 0 ; i < Anz ; i++) {
    res[i].x = r->left + int (LONG(rel[i].x) * LONG(r->right - r->left) / 100L);
    res[i].y = r->top + int (LONG(rel[i].y) * LONG(r->bottom - r->top) / 100L);
    }
  }

void cFieldCombo::PaintPoly (HDC hDC, HBRUSH hbr, HPEN hPen, LPPOINT pt, int Anz)
  {
  POINT ptbuffer[32];
  GetLogPolygon (ptbuffer, pt, &rcPoly, Anz);
  HPEN hpold = (HPEN)SelectObject (hDC, hPen);
  HBRUSH hbold = (HBRUSH)SelectObject (hDC, hbr);
  Polygon (hDC, ptbuffer, Anz);
  SelectObject (hDC, hbold);
  SelectObject (hDC, hpold);
  }

#define CENTER 47
#define WIDTH  9 
#define X1 CENTER-WIDTH
#define X2 CENTER+WIDTH

static POINT GrauerSchatten [] = 
  { { 0,100 } , { 100, 100 } , { 100, 0 } , { 90 , 10 } , { 90 , 90 } , { 10 , 90 } } ;
static POINT WeisserSchatten [] = 
  { { 0,100 } , { 0, 0 } , { 100, 0 } , { 95 , 5 } , { 5 , 5 } , { 5 , 95 } } ;

static POINT Pfeil[] = 
  { {CENTER-25,30} , {CENTER+25,30} , {CENTER,55} } ;
//  { {X1,25} , {X2,25} , {X2,45} , {CENTER+20,45} , {CENTER,60} , {CENTER-20,45} , {X1,45} } ;

static POINT Line[] = 
  { {CENTER-20,70} , {CENTER+20,70} , {CENTER+20,71} , {CENTER-20, 71} };



void cFieldCombo::OnPaint (HDC hDC, BOOL State,HWND hW)
  {
  HBRUSH hNewBrush;
  HPEN hNewPen;

  // Achtung: In Logischen Koordinaten !!!
  if ((MyField != NULL) && (MyField->HasButton) && (MyField->Wnd == hW)) {
    SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));
    ExtTextOut (hDC, 0, 0, ETO_OPAQUE, LPRECT(&rcBtn), NULL, 0, NULL);

    if (!ListIsDown) {
      hNewBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
      hNewPen = (HPEN)GetStockObject (WHITE_PEN);
      PaintPoly (hDC, hNewBrush, hNewPen, WeisserSchatten, sizeof(WeisserSchatten)/sizeof(POINT));

      hNewBrush = CreateSolidBrush(RGB(0x80, 0x80, 0x80));
      hNewPen = CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
      PaintPoly (hDC, hNewBrush, hNewPen, GrauerSchatten, sizeof(GrauerSchatten)/sizeof(POINT));
      DeleteObject (hNewPen);
      DeleteObject (hNewBrush);
      }
    else {
      hNewBrush = CreateSolidBrush(RGB(0x80, 0x80, 0x80));
      hNewPen = CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
      PaintPoly (hDC, hNewBrush, hNewPen, WeisserSchatten, sizeof(WeisserSchatten)/sizeof(POINT));
      DeleteObject (hNewPen);
      DeleteObject (hNewBrush);
      }

    hNewBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    hNewPen = (HPEN)GetStockObject(BLACK_PEN);
    PaintPoly (hDC, hNewBrush, hNewPen, Pfeil, sizeof(Pfeil)/sizeof(POINT));

    hNewBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    hNewPen = (HPEN)GetStockObject(BLACK_PEN);
    PaintPoly (hDC, hNewBrush, hNewPen, Line, sizeof(Line)/sizeof(POINT));

    hNewBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
    hNewPen = (HPEN)SelectObject(hDC, CreatePen (PS_SOLID, 0, RGB(0, 0, 0)));
    Rectangle (hDC, rcBtn.left, rcBtn.top, rcBtn.right, rcBtn.bottom);
    DeleteObject (SelectObject (hDC, hNewPen));
    SelectObject (hDC, hNewBrush);
    }
  }


void cFieldCombo::BeginList (cField FAR* field)     
  { 
  if (field != NULL)
    if (field->HasButton) 
      ListIsDown = TRUE; 
  MyField = field ;
  }

BOOL cFieldCombo::OnLButtonDown (cField FAR* field, LPPOINT pt)
  {
  if ((field != NULL) && (field == MyField)) {
    if (((LONG(pt->x - rcBtn.left) * LONG(pt->x - rcBtn.right)) <= 0L) &&
        ((LONG(pt->y - rcBtn.top) * LONG(pt->y - rcBtn.bottom)) <= 0L))
      return TRUE;
    }

  return FALSE;
  }



extern cFieldCombo cfBtn;
void setFieldButtonUp ()
  {
  cfBtn.ListIsDown = FALSE ;
  }


