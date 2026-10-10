/////////////////////////////////////////////////////////////
//   $Header:   P:/marille/clinicum/ctool/rev/mappe.cpv   1.49   16 Jul 1999 02:23:00   Hannes  $
//   $Log:   P:/marille/clinicum/ctool/rev/mappe.cpv  $
// 
//    Rev 1.49   16 Jul 1999 02:23:00   Hannes
// 
//    Rev 1.48   05 Oct 1998 11:06:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.47   02 Sep 1998 10:19:04   Gerhold
// Eine GetClassName-Funktion hatte einen Stack Overflow
// 
//    Rev 1.46   01 Jul 1998 14:40:16   Gerhold
// IsMapHotkey ... Schauen ob ein Formular offen ist
// 
//    Rev 1.45   24 Feb 1998 19:45:44   Hannes
// ToDevKoord...
// 
//    Rev 1.44   20 Feb 1998 12:34:38   Hannes
// Disable negativ: Hand zeichnen, disable Postiov: Grauer Text
// 
//    Rev 1.43   20 Feb 1998 11:12:32   Gerhold
// Das komische Haendchenbitmap wieder ausgebaut
// 
//    Rev 1.42   09 Feb 1998 18:13:06   Hannes
// Erste nicht deaktivierte Mappe aktivieren
// 
//    Rev 1.41   12 Nov 1997 15:44:26   Martin
// Disabled Flaps nicht in weiss darstellen (Befehl vom Haeuptling!)
// 
//    Rev 1.40   23 Oct 1997 10:29:30   Gerhold
// InFaecher die Disabled sind, wird ein Bitmap eingezeichnet (::Paint)
// 
//    Rev 1.39   10 Jul 1997 08:58:40   Hannes
// 
//    Rev 1.38   22 Apr 1997 12:08:32   Hannes
// Font, Hoehe und Offset in die Struktur
// 
//    Rev 1.37   08 Apr 1997 17:42:56   gerhold
// SetFlapHeight, SetMapOffset
// 
//    Rev 1.36   07 Apr 1997 19:20:26   gerhold
// Vorbereitung der neuen Funktion SetMapFont
// 
//    Rev 1.35   14 Mar 1997 09:45:24   gerhold
// Invalidieren einer einreihigen Mappe war noch immer falsch
// 
//    Rev 1.34   10 Mar 1997 14:50:22   gerhold
// einreihige Mappe hatte noch Invalidierungsschwierigkeiten
// 
//    Rev 1.33   25 Feb 1997 12:10:28   Gerhold
// Die Hauptmappe wird jetzt etwas schoener gezeichnet. Es besteht ausserdem die
// Moeglichkeit den Ohrwascheln Bilder und Hilfetexte zuzuordnen.
// 
//    Rev 1.32   29 Jan 1997 15:45:54   GERHOLD
// IsMapHotkey ... keyflag wurde mit den echten VK_... - Daten logisch verknpft
//                 anstatt die #define VK... zu verwenden
// 
//    Rev 1.31   12 Nov 1996 14:38:12   GERHOLD
// neuer Member m_ChildMap ... diese Mappe hat einen Screen als Parent
// 
//    Rev 1.30   16 Apr 1996 13:26:58   GERHOLD
// m_hWndMap wird gar nicht verwendet?! => sinnlose Abfrage in IsMapHotKey
// 
//    Rev 1.29   24 Mar 1996 12:25:18   gerhold
// Umstellung auf mehrseitige cFields
// 
//    Rev 1.28   02 Feb 1996 10:41:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.27   15 Nov 1995 17:34:14   GERHOLD
// void _export SetMapExtent ... Position und Groesse der Mappe aendern
// 
//    Rev 1.26   31 Oct 1995 07:30:30   GERHOLD
// bei der Auswertung der Steuertasten wurde das VK_MENU vergessen
// 
//    Rev 1.25   24 Aug 1995 09:36:56   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.24   14 Aug 1995 12:18:10   HANNES
// Mappenhotkeys erweitert
// 
//    Rev 1.23   20 May 1995 16:17:40   HANNES
// FirstFlapSet eingefuehrt, damit wenigstens eine Flappe immer konstant bleibt
// 
//    Rev 1.22   15 May 1995 08:36:38   HANNES
// 
//    Rev 1.21   04 May 1995 18:38:50   HANNES
// 
//    Rev 1.20   25 Apr 1995 16:52:46   HANNES
// 
//    Rev 1.19   13 Apr 1995 12:48:42   HANNES
// 
//    Rev 1.18   12 Apr 1995 12:27:42   HANNES
// 
//    Rev 1.17   20 Mar 1995 13:43:16   HANNES
// 
//    Rev 1.16   20 Jan 1995 15:50:22   HANNES
// Mappenhotkeys bei disabledem Framwin auch disablen
// 
//    Rev 1.15   28 Nov 1994 20:02:08   GERHOLD
// IsMapHotKey
// 
//    Rev 1.14   28 Oct 1994 10:42:54   GERHOLD
// SetParent ... Abmessungen des MapDocRects bleiben unabhaengig von der
//               Anzahl der Flappenreihen gleich.
// 
//    Rev 1.13   20 Sep 1994 11:27:42   HANNES
// Mappen in Dialogboxen
// 
//    Rev 1.12   29 Aug 1994 12:45:08   GERHOLD
// Systemunabhaengigkeit ein bisserl erweitert
// 
//    Rev 1.11   26 Aug 1994 15:50:36   HANNES
// 
//    Rev 1.10   25 Aug 1994 13:52:24   GERHOLD
// Ohrwaschelflecken bei leeren Elementen raus!
// 
//    Rev 1.9   17 Aug 1994 09:29:40   HANNES
// Weite, Hoehe und AnzOhren angegeben
// 
//    Rev 1.8   16 Aug 1994 08:47:40   GERHOLD
// Markierungsfelder in den Ohrwascheln
// 
//    Rev 1.7   05 Aug 1994 19:33:02   HANNES
// DeleteObject .. vom Brush der elemcolor
// 
//    Rev 1.6   05 Aug 1994 17:08:24   GERHOLD
// Farb Parameter in Mappe eingefuegt
// 
//    Rev 1.5   17 Jul 1994 14:43:00   HANNES
// Zwischenversion
// 
//    Rev 1.4   15 Jul 1994 15:30:40   HANNES
// Invalidate im Updatezweig
// 
//    Rev 1.3   13 Jul 1994 21:20:46   HANNES
// Zwischenversion
// 
//    Rev 1.2   12 Jul 1994 14:45:46   GERHOLD
// Riesige Žnderungen!!!!!  Connections auf die Ohrwascheln,
// Generieren von dynamischen Listen statt statischer Arrays
// 
//    Rev 1.1   05 Jul 1994 15:42:54   GERHOLD
// Initial Code
/////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#ifndef MAPTYPE_GEOMETRIC
#define MAPTYPE_GEOMETRIC    1
#define MAPTYPE_TYPOGRAPHIC  2
#endif

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "ddsmsg.h"

#include "cfield.hpp"
#include "toolbar.hpp"

#include "mappe.hpp"

#define MODULENUM 120
#include "winass.hpp"

static MAPCALLCOMMAND MapCallCommand;

extern HBITMAP hBmpMappeDisabled;

int ClientMap::GetFlapHeight () 
  { 
  return int(FHeight * BaseUnit); 
  }

BOOL DisableText(int Disable)
  {
  return (Disable > 0);
  }
BOOL DisableBild(int Disable)
  {
  return (Disable < 0);
  }


static int LogX,LogY,LogWidth,LogHeight,AnzFlaps,FlapFont,FlapHeight,MapOffset;
static int old_FlapFont,old_FlapHeight,old_MapOffset;
int GetLeftDist (LPRECT r)
  { 
  return (LogWidth > 0) ? (r->right - int (LogWidth * BaseUnit)) / 2 : int (LEFT_SPACE * BaseUnit) ; 
  }
int GetTopDist (LPRECT r)
  { 
  return (LogHeight > 0) ? (r->bottom - int (LogHeight * BaseUnit)) / 2 : int (TOP_SPACE * BaseUnit) ; 
  }
int GetRightDist (LPRECT r)   
  { 
  return (LogWidth > 0) ? (r->right - int (LogWidth * BaseUnit)) / 2 : int (RIGHT_SPACE * BaseUnit) ; 
  }
int GetBottomDist (LPRECT r)
  { 
  return (LogHeight > 0) ? (r->bottom - int (LogHeight * BaseUnit)) / 2 : int (BOTTOM_SPACE * BaseUnit) ; 
  }
inline int MaxFlaps ()      
  { 
  return (AnzFlaps > 0) ? AnzFlaps : MAX_FLAPS; 
  }


#define NOTYPE  0
#define SELECTION_OFFSET  2   // Wenn in einer Kindmappe ein Reiter selektiert
                              // ist, wird er um diesen Wert nach links, oben
                              // und rechts vergroessert dargestellt
#define DEFAULT_FONT     16

#define  ANY_ELEM_IN_ROW     0
#define  FIRST_ELEM_IN_ROW   1
#define  LAST_ELEM_IN_ROW    2


static HBRUSH BRUSH_TYPE_0, BRUSH_TYPE_1, BRUSH_TYPE_2;


HBRUSH GetBrush (WORD Type)
  {
  switch (Type) {
    case 0:
      return BRUSH_TYPE_0;
      break;
    case 1:
      return BRUSH_TYPE_1;
      break;
    case 2:
      return BRUSH_TYPE_2;
      break;
    default:
      return (HBRUSH)GetStockObject (LTGRAY_BRUSH);
    }

  }


HBRUSH GetColor (WORD Type)
  {
  return GetBrush (Type);
  }

void MappeSetMMText (HDC hDC,int y = 0)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void MappeSetTwips (HDC hDC,int x = 0,int y = 0)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440, NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,x,y, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }


inline int XtoDEV (HDC hDC,int x)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = x ;
  pt[1].y = 0 ;
  LPtoDP (hDC,pt,2);
  return pt[1].x - pt[0].x;
  }

inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = x ;
  pt[1].y = 0 ;
  DPtoLP (hDC,pt,2);
  return pt[1].x - pt[0].x;
  }

inline int YtoDEV (HDC hDC,int y)
  {
  POINT pt[2];
  pt[0].x = 0 ;
  pt[0].y = 0 ;
  pt[1].x = 0 ;
  pt[1].y = y ;
  LPtoDP (hDC,pt,2);
  return pt[1].y - pt[0].y;
  }

void MapElem::Update (LPSTR Text,WORD Type,COLORREF Color,int disabled,LPVOID ExtraData)
  {
  if ((!isEmpty) && (_ExtraData != NULL) && 
      (lmemcmp (_ExtraData,ExtraData,GetBlockSize(_ExtraData)))) {
    FlapText = LPSTR(GetGlobMem ((Text != NULL) ? lstrlen(Text) + 1 : 1));
    if (Text != NULL)
      lstrcpy (FlapText,Text);
    Disabled = disabled;
    ElemType = Type;
    ElemColor = Color;
    Invalidate (TRUE);
    }
  }

#define FSPACE 4    // war 20
MapElem::MapElem (ClientMap FAR *p,LPSTR Text, WORD Typ, COLORREF Color, BOOL disabled, 
                  LPRECT rc, HWND hWndOwner,int flaprow, short Pos, LPVOID Data, DWORD Proc, 
                  LPVOID ExtraData, BOOL Empty,HotKeyData FAR *kd, 
                  LPSTR Help, DWORD dwBitId, short Ix, short Iy
                 )
  {
  Parent = p ;
  Selected = FALSE;
  Next = NULL;
  hWndParent = hWndOwner;
  Row = flaprow;
  Position = Pos;
  SetElemRect (rc);
  if (kd != NULL) KeyData = *kd ;

  _Data = Data;
  _ExtraData = ExtraData;
  _Proc = Proc;

  FlapText = LPSTR(GetGlobMem ((Text != NULL) ? lstrlen(Text) + 1 : 1));
  if (Text != NULL)
    lstrcpy (FlapText,Text);
  Disabled = disabled;
  ElemType = Typ;
  ElemColor = Color;

  HelpText = LPSTR(GetGlobMem ((Help != NULL) ? lstrlen(Help) + 1 : 1));
  if (Help != NULL)
    lstrcpy (HelpText,Help);

  BitId = dwBitId;
  IndexX = Ix;
  IndexY = Iy;

  HDC hDC = GetDC (hWndOwner);
  MappeSetTwips (hDC);
  Title = new cField (TRANSPARENT, p->FFont, 
                      0, 0, XtoLOG(hDC, rc->right-rc->left-FSPACE),
                      -1, FALSE);

  Title->SetWindow (hWndOwner);
  Title->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  Title->SetVOrg (0,0,0);
  *Title = FlapText;

  ReleaseDC (hWndOwner, hDC);
  }


MapElem::~MapElem () 
  { 
  if (FlapText != NULL)
    FreeGlobMem (FlapText);

  if (HelpText != NULL)
    FreeGlobMem (HelpText);
    
  if (Title != NULL)  
    delete Title; 

  if (_Data != NULL) {
    (* FreePrivData) (_Data);
    FreeGlobMem (_Data);
    }

  if (_ExtraData != NULL)
    FreeGlobMem (_ExtraData);
  }


#define CORNER  2

void MapElem::SetElemRect (LPRECT rc)
  {
  CopyRect (LPRECT(&FlapRect), rc);

  ptFlap[0].x = rc->left;
  ptFlap[0].y = rc->bottom/*+CORNER*/;
  ptFlap[1].x = rc->left;
  ptFlap[1].y = rc->top+CORNER;
  ptFlap[2].x = rc->left+CORNER;
  ptFlap[2].y = rc->top;
  ptFlap[3].x = rc->right-CORNER;
  ptFlap[3].y = rc->top;
  ptFlap[4].x = rc->right;
  ptFlap[4].y = rc->top+CORNER;
  ptFlap[5].x = rc->right;
  ptFlap[5].y = rc->bottom/*+CORNER*/;

  ptFlap[6].x = rc->right;
  ptFlap[6].y = ptFlap[5].y+2*CORNER;
  ptFlap[7].x = rc->left;
  ptFlap[7].y = ptFlap[5].y+2*CORNER;
  }




void MapElem::Paint (HDC hDC)
  {
  HPEN hOldPen;

  POINT ptTmp[8];
  lmemcpy (ptTmp, ptFlap, sizeof(ptFlap));


  int Offset = 0;
  if (Parent->m_ChildMap) {

    if (Selected)
      Offset = SELECTION_OFFSET;

    HBRUSH hOldBrush;

    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));
    if (Selected) {
      hOldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
      Rectangle (hDC, FlapRect.left-Offset, FlapRect.top-Offset, 
                      FlapRect.right+Offset, FlapRect.bottom+1);
      SelectObject (hDC, hOldBrush);
      }

    hOldBrush = (HBRUSH)SelectObject(hDC, GetBrush(ElemType));
    Polygon (hDC, LPPOINT(&ptFlap), 6);    // Polygon ohne Rahmen zeichnen
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldBrush);

    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));

    MoveToEx (hDC, ptFlap[0].x-Offset, ptFlap[0].y, NULL);
    LineTo (hDC, ptFlap[1].x-Offset, ptFlap[1].y-Offset);
    LineTo (hDC, ptFlap[2].x-Offset, ptFlap[2].y-Offset);
    LineTo (hDC, ptFlap[3].x+Offset, ptFlap[3].y-Offset);

    SelectObject (hDC, hOldPen);

    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
    MoveToEx (hDC, ptFlap[3].x+Offset, ptFlap[3].y+1-Offset, NULL);
    LineTo (hDC, ptFlap[4].x-1+Offset, ptFlap[4].y-Offset);
    LineTo (hDC, ptFlap[5].x-1+Offset, ptFlap[5].y);
    SelectObject (hDC, hOldPen);

    HPEN NewPen = CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
    hOldPen = (HPEN)SelectObject (hDC, NewPen);

    MoveToEx (hDC, ptFlap[5].x-2+Offset, ptFlap[3].y+2-Offset, NULL);
    LineTo (hDC, ptFlap[5].x-2+Offset, ptFlap[5].y);
    SelectObject (hDC, hOldPen);
    DeleteObject (NewPen);
    }
  else {

    // Die selektierten Ohrwascheln werden etwas erhoeht und etwas
    // breiter gezeichnet.
    // Dabei ist aber bei den Randelementen Vorsicht geboten; diese
    // duerfen sich entweder nur nach rechts (linke Elemente) oder 
    // nach links (rechte Elemente) ausdehnen.
    //--------------------------------------------------------------
    BOOL bShadow = FALSE;
    if (Selected) {
      ptTmp[1].y -= SELECTION_OFFSET;   // nach oben gehen alle Elemente
      ptTmp[2].y -= SELECTION_OFFSET;
      ptTmp[3].y -= SELECTION_OFFSET;
      ptTmp[4].y -= SELECTION_OFFSET;

      if (Position == FIRST_ELEM_IN_ROW) {
        ptTmp[3].x += SELECTION_OFFSET;     // nur nach rechts ausdehnen
        ptTmp[4].x += SELECTION_OFFSET;
        ptTmp[6].x = ptTmp[5].x = ptTmp[4].x;
        bShadow = TRUE;
        }
      else if (Position == LAST_ELEM_IN_ROW) {
        ptTmp[2].x -= SELECTION_OFFSET;     // nur nach links ausdehnen
        ptTmp[7].x -= SELECTION_OFFSET;
        ptTmp[0].x = ptTmp[1].x = ptTmp[7].x;
        }
      else {
        ptTmp[3].x += SELECTION_OFFSET;     // nach rechts und links
        ptTmp[4].x += SELECTION_OFFSET;
        ptTmp[6].x = ptTmp[5].x = ptTmp[4].x;
        ptTmp[2].x -= SELECTION_OFFSET;
        ptTmp[7].x -= SELECTION_OFFSET;
        ptTmp[0].x = ptTmp[1].x = ptTmp[7].x;
        bShadow = TRUE;
        }
      }

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetBrush(ElemType));
    HPEN NewPen = CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));

    Polygon (hDC, LPPOINT(&ptTmp), 8);    // Polygon ohne Rahmen zeichnen

    SelectObject (hDC, hOldPen);

    // linke und obere Linie
    //-----------------------
    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
    if (Position == FIRST_ELEM_IN_ROW)
      MoveToEx (hDC, ptFlap[7].x+1, ptFlap[7].y-CORNER+2, NULL);
    else
      MoveToEx (hDC, ptTmp[0].x+1, ptTmp[0].y, NULL);
    LineTo (hDC, ptTmp[1].x+1, ptTmp[1].y);
    LineTo (hDC, ptTmp[2].x, ptTmp[2].y+1);
    LineTo (hDC, ptTmp[3].x, ptTmp[3].y+1);
    SelectObject (hDC, hOldPen);

    // rechte Linie
    //-----------------------
    hOldPen = (HPEN)SelectObject (hDC, NewPen);
    LineTo (hDC, ptTmp[4].x-1, ptTmp[4].y);
    if (Position == LAST_ELEM_IN_ROW)
      LineTo (hDC, ptTmp[6].x-1, ptTmp[6].y-CORNER+3);
    else
      LineTo (hDC, ptTmp[5].x-1, ptTmp[5].y+1);
    SelectObject(hDC, hOldPen);

    if (Selected) {

      hOldPen = (HPEN)SelectObject (hDC, NewPen);

      if (Position == LAST_ELEM_IN_ROW)
        MoveToEx (hDC, ptTmp[6].x-2, ptTmp[6].y-CORNER+2, NULL);
      else
        MoveToEx (hDC, ptTmp[5].x-2, ptTmp[5].y, NULL);
      LineTo (hDC, ptTmp[4].x-2, ptTmp[4].y);
      LineTo (hDC, ptTmp[3].x, ptTmp[3].y+1);

      // zeichnet einen Schatten rechts neben dem Ohrwaschel
      //----------------------------------------------------
      if (bShadow) {
        POINT ptShadow[4];

        ptShadow[0].x = ptTmp[4].x;
        ptShadow[0].y = ptTmp[4].y;
        ptShadow[1].x = ptTmp[4].x+6;
        ptShadow[1].y = ptTmp[4].y+6;
        ptShadow[2].x = ptShadow[1].x;
        ptShadow[2].y = ptTmp[5].y;
        ptShadow[3].x = ptShadow[0].x;
        ptShadow[3].y = ptShadow[2].y;

        HRGN hRgn = CreatePolygonRgn (ptShadow, 4, ALTERNATE);
        HRGN hOldRgn = (HRGN)SelectObject (hDC, hRgn);
        SelectClipRgn (hDC, hRgn);

        LOGBRUSH LogBrush;

        // Schatten besteht aus 1-0-Bitmap und laesst den Hintergrund durchscheinen
        //-------------------------------------------------------------------------
        LogBrush.lbStyle = BS_PATTERN;

  #ifdef WIN32
        LogBrush.lbHatch = LONG(LoadBitmap(hLibInst, "FOCUSBITS"));
  #else
        LogBrush.lbHatch = LoadBitmap(hLibInst, "FOCUSBITS");
  #endif

        HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, CreateBrushIndirect(&LogBrush));

        PatBlt (hDC, ptShadow[0].x, ptShadow[0].y, ptShadow[2].x, ptShadow[2].y, 0xA000C9);    // Quelle & Ziel

        DeleteObject(SelectObject(hDC, OldBrush));
        DeleteObject(HBITMAP(LogBrush.lbHatch));
        
        
        SelectObject (hDC, hOldRgn);
        DeleteObject (hRgn);
        SelectClipRgn (hDC, NULL);
        }

      SelectObject(hDC, hOldPen);

      hOldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
      MoveToEx (hDC, ptTmp[3].x-1, ptTmp[3].y+2, NULL);
      LineTo (hDC, ptTmp[2].x, ptTmp[2].y+2);
      LineTo (hDC, ptTmp[1].x+2, ptTmp[1].y);
      if (Position == FIRST_ELEM_IN_ROW)
        LineTo (hDC, ptFlap[7].x+2, ptFlap[7].y-CORNER+3);
      else
        LineTo (hDC, ptTmp[0].x+2, ptTmp[0].y);

      SelectObject(hDC, hOldPen);

      hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
      if (Position == FIRST_ELEM_IN_ROW) {
        MoveToEx (hDC, ptTmp[0].x, ptTmp[0].y+1, NULL);
        LineTo (hDC, ptTmp[7].x, ptTmp[7].y+1);
        }

      if (Position == LAST_ELEM_IN_ROW) {
        MoveToEx (hDC, ptFlap[6].x, ptFlap[6].y, NULL);
        LineTo (hDC, ptFlap[5].x, ptFlap[5].y-1);
        }
      else {
        MoveToEx (hDC, ptTmp[5].x, ptTmp[5].y, NULL);
        LineTo (hDC, ptTmp[5].x, ptTmp[5].y+1);
        }

      SelectObject(hDC, hOldPen);
      }

    DeleteObject (NewPen);

    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));

    Polyline (hDC, LPPOINT(&ptTmp), 6);   // schwarzen Rahmen

    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldBrush);
    }

  int TextOffsetX = FSPACE / 2;

  //---------------------------------------------------------------------
  // Ist das Ohrwaschel disabled, dann wird es speziell gekennzeichnet;
  // ist es anwaehlbar, dann wird ueberprueft, ob es ein Bitmap anzeigen
  // kann, oder ob man einen Farbfleck zeichnet.
  //---------------------------------------------------------------------
  if (DisableBild (Disabled)) {
    if (hBmpMappeDisabled) {
      BITMAP bi;
      GetObject (hBmpMappeDisabled ,sizeof(bi),&bi);
      TextOffsetX = bi.bmWidth + 2;

      DrawTransparentBitmap(hDC, hBmpMappeDisabled, ptFlap[2].x+2+Offset,
                            ptFlap[1].y+2-Offset,
                            0, 0,
                            bi.bmWidth, bi.bmHeight, 0xC0C0C0);
      }
    }
  else {
    if (BitId != 0) {
      int AnzRows, AnzCols;
      HBITMAP hBmp = GetBitmap (
                          BitId, 
                          AnzRows, AnzCols
                              );
      if (hBmp != NULL) {
        BITMAP bi;
        GetObject (hBmp,sizeof(bi),&bi);
        int bmWidth  = bi.bmWidth  / AnzCols ;
        int bmHeight = bi.bmHeight / AnzRows ;

        TextOffsetX = bmWidth + 2;

        if (ElemColor != 0xFFFFFFFF)
          DrawTransparentBitmap(hDC, hBmp, ptFlap[2].x+2+Offset,
                                ptFlap[1].y+2-Offset,
                                int(IndexX * bmWidth),             // horizontaler Offset im Bitmap
                                int(IndexY * bmHeight),            // vertikaler Offset im Bitmap
                                bmWidth, bmHeight, COLORREF(ElemColor));
        else {
          HDC hMemDC = CreateCompatibleDC(hDC);

          HBITMAP OldBitmap = (HBITMAP)SelectObject (hMemDC, hBmp);
          BitBlt (hDC, ptFlap[2].x+2+Offset, ptFlap[1].y+2-Offset,
                      bmWidth, bmHeight,
                  hMemDC,
                      int (IndexX * bmWidth),
                      int (IndexY * bmHeight),
                      SRCCOPY);
          SelectObject (hMemDC, OldBitmap);

          DeleteDC (hMemDC);
          }
        }
      }
    else {


      // Mappe noch speziell kennzeichnen
      // (durch einen Farbfleck im Ohrwaschel)
      if (ElemColor != 0xFFFFFFFF) {
        RECT rc;
        rc.left = ptFlap[2].x;
        rc.top =  ptFlap[1].y;
        rc.right = rc.left+7;
        rc.bottom = rc.top+15;
        OffsetRect (&rc, 2, 4);
  
        COLORREF OldBk = SetBkColor (hDC, ElemColor);
        ExtTextOut (hDC, rc.left, rc.top, ETO_OPAQUE, &rc, NULL, 0, NULL);
        SetBkColor (hDC, OldBk);

        InflateRect (&rc, 1, 1);
        hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
        MoveToEx (hDC, rc.left, rc.bottom-1, NULL);
        LineTo (hDC, rc.left, rc.top);
        LineTo (hDC, rc.right, rc.top);
        DeleteObject (SelectObject(hDC, hOldPen));

        hOldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
        MoveToEx (hDC, rc.right, rc.top+1, NULL);
        LineTo (hDC, rc.right, rc.bottom);
        LineTo (hDC, rc.left, rc.bottom);
        SelectObject(hDC, hOldPen);

        hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
        MoveToEx (hDC, rc.left+1, rc.bottom-1, NULL);
        LineTo (hDC, rc.left+1, rc.top+1);
        LineTo (hDC, rc.right-1, rc.top+1);
        SelectObject(hDC, hOldPen);

        TextOffsetX = 10 + FSPACE / 2;
        }
      }
    }
  
  if (Title != NULL) {
    MappeSetTwips (hDC, FlapRect.left+TextOffsetX+Offset, FlapRect.top+5-Offset);

    Title->SetWidth (XtoLOG(hDC, FlapRect.right - FlapRect.left - FSPACE - TextOffsetX));

    if (DisableText (Disabled))
      Title->SetOutColor (RGB(0x80, 0x80, 0x80));

    Title->Paint (hDC, 0, FALSE);

    MappeSetMMText (hDC);

    if (DisableText (Disabled)) {
      MappeSetTwips (hDC, FlapRect.left+TextOffsetX+1+Offset, FlapRect.top+6-Offset);
      Title->SetOutColor (RGB(0xFF, 0xFF, 0xFF));
      Title->Paint (hDC, 0, FALSE);
      Title->UseDefOutColor();
      MappeSetMMText (hDC);
      }
    }
  }


void MapElem::SetActive (BOOL State, BOOL redraw,int PageNo) 
  { 
  Selected = State; 
  if (!State)
    *Title = FlapText;
  else {  
    char OutText[128];
    wsprintf (OutText, "\\m1%s", FlapText);  // gib mir ein "Fett"-Attribut!
    *Title = OutText;
    }
  if (State)
    (* MapCallCommand) (_Data,_Proc,_ExtraData,EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,Parent->CallBackPar,PageNo);
  else
    (* MapCallCommand) (_Data,_Proc,_ExtraData,EM_CLEAR | EM_RESET,Parent->CallBackPar,-1);
  if (redraw)
    RePaint(); 
  };

void MapElem::Invalidate (BOOL erase)
  {
  RECT rc;
  CopyRect (&rc, LPRECT(&FlapRect));

  // die horizontale Vergroesserung loescht den Schatten neben dem Element
  //----------------------------------------------------------------------
  InflateRect (&rc, 8, 3);
  InvalidateRect (hWndParent,&rc,erase);
  }

void MapElem::RePaint (void)
  {
  HRGN hRgn = 0;
  HDC hDC = GetDC (hWndParent);

  if ((!Selected) && (Row == 0)) {
    hRgn = CreateRectRgn (FlapRect.left, FlapRect.top, FlapRect.right, FlapRect.top+Parent->GetFlapHeight());
    SelectClipRgn (hDC, hRgn);
    }
  
  Paint (hDC);
  
  if (hRgn != 0) {
    SelectClipRgn (hDC, NULL);
    DeleteObject (hRgn);
    }
  ReleaseDC (hWndParent, hDC);
  }


BOOL MapElem::HitTest (LPPOINT pt)
  {
  if ((((FlapText != NULL) && (*FlapText)) || (BitId != 0)) && (!Disabled))
    return (PtInRect(LPRECT(&FlapRect), *pt));
    
  return FALSE;  
  }


void MapElem::GetHelp (LPPOINT pt)
  {
  if ((HelpText != NULL) && (*HelpText != '\0'))
    Parent->hWndBubble = CreateBubbleWindow (pt->x, pt->y, HelpText, hWndParent);
  else 
    Parent->hWndBubble = NULL;
  }

void MapElem::RemoveHelp ()
  {
  if (Parent->hWndBubble) {
    DestroyWindow (Parent->hWndBubble);
    Parent->hWndBubble = NULL;
    }
  }


/*-------------------------------------------------------------------------*\
*  CONSTRUCTOR ClientMap                                                    *
*                                                                           *
*  Parameter    :                                                           *
\*-------------------------------------------------------------------------*/
ClientMap::ClientMap (int FlapCnt, LPMAPELEMDATA lpmed, LPVOID cbp, BOOL ChildMap)
  {
  FFont = FlapFont;
  FHeight = FlapHeight;
  MOffset = MapOffset;

  m_FlapCnt = FlapCnt;

  m_MapElemData = lpmed;
  m_ChildMap = ChildMap;

  m_FlapRows = m_FlapCnt/MaxFlaps();    

  if (m_FlapCnt % MaxFlaps() != 0)
    m_FlapRows++;
    
  m_FlapCnt = m_FlapRows*MaxFlaps();
  
  m_FlapCols = (m_FlapCnt < (MaxFlaps()) ? m_FlapCnt : MaxFlaps());  // nur eine Reihe??
  SetRectEmpty (LPRECT(&m_MapRect));

  FirstFlap = FirstFlapSet = NULL;
  ActiveFlap = NULL;
  StartFlap = NULL;
  CallBackPar = cbp;

  HelpElem = NULL;
  hWndBubble = NULL;
  }


/*-------------------------------------------------------------------------*\
*  DESTRUCTOR ClientMap                                                     *
*                                                                           *
\*-------------------------------------------------------------------------*/
ClientMap::~ClientMap ()
  {
  MapElem FAR *prev = NULL;
  
  if (ActiveFlap != NULL)
    ActiveFlap->SetActive (FALSE, FALSE,-1);

  for (MapElem FAR* e = FirstFlap; ((e == FirstFlap) && (e != StartFlap) && (e)) ; e = e->Next) {
    if (prev != NULL)
      delete prev;

    RemoveFlap (e);
    prev = e;
    }

  if (prev != NULL)
    delete prev;
  if (StartFlap != NULL)
    delete StartFlap;

  if (m_hWndMap != 0) {
    DestroyWindow (m_hWndMap);
    m_hWndMap = 0;
    }
  }

/*-------------------------------------------------------------------------*\
*  member function:  SetParent                                              *
*                                                                           *
*  Parameter    :                                                           *
*  Rückgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
static int IndToActivate;
MapElem FAR *GetPrevMapElem(MapElem FAR *h)
  {
  for ( MapElem FAR *x = h->Next ; ; x = x->Next )
    if (x->Next == h) return x;
  }
void ClientMap::SetParent (HWND hWnd)
  {
  m_hWndParent = hWnd;

  RECT rc;
  GetClientRect (m_hWndParent, &rc);              
  // auf allen vier Seiten einen Rand zum MDIClient lassen
  
  if (LogX > 0)
    m_MapRect.left   = rc.left + int(LogX * BaseUnit);
  else
    m_MapRect.left   = rc.left+GetLeftDist(&rc)-((m_FlapRows-1)*MOffset) / 2;
    
  if (LogY > 0)
    m_MapRect.top = rc.top + int(LogY * BaseUnit);
  else
    m_MapRect.top    = rc.top+GetTopDist(&rc)-(GetFlapHeight()*m_FlapRows) / 2;
    
  if (LogX > 0)
    m_MapRect.right  = m_MapRect.left + int(LogWidth * BaseUnit) + ((m_FlapRows-1)*MOffset);
  else
    m_MapRect.right  = rc.right-GetRightDist(&rc)+((m_FlapRows-1)*MOffset) / 2;

  if (LogY > 0)
    m_MapRect.bottom = m_MapRect.top + int(LogHeight * BaseUnit) + (GetFlapHeight()*m_FlapRows);
  else
    m_MapRect.bottom = rc.bottom-GetBottomDist(&rc)+(GetFlapHeight()*m_FlapRows) / 2;


  // m_MapDocRect ist das Rechteck, mit dessen Koordinaten ein "CreateWindow" aufgerufen wird
  CopyRect (LPRECT(&m_MapDocRect), LPRECT(&m_MapRect));
  m_MapDocRect.top += GetFlapHeight()*m_FlapRows;     // um die Anzahl der Reihen verkleinern
  m_MapDocRect.right -= (m_FlapRows-1)*MOffset;  // die dahinterliegenden Reihen rechts
  int FlapWidth = (m_MapDocRect.right-m_MapDocRect.left) / (MaxFlaps());   // die Flappenbreite

  // Fehleranpassung:  die Breite der Flappe wurde durch die Integer-Division abgerundet 
  // => die Laengen der Rechtecke werden an die neuen Breiten angepasst.
  m_MapDocRect.right = m_MapDocRect.left+MaxFlaps()*FlapWidth;
  m_MapRect.right = m_MapDocRect.right + (m_FlapRows-1)*MOffset;
  if (m_ChildMap) {
    m_MapDocRect.right++;
    m_MapDocRect.left -= 2;
    }

  int FlapRow;
  MapElem FAR* pme;

  for (int i = 0; i < m_FlapCnt; i++) {
    LPMAPELEMDATA Next;
    if (m_MapElemData != NULL)
      Next = m_MapElemData->Next ;
    else
      Next = NULL ;
    FlapRow = i/m_FlapCols;
    rc.left   = m_MapDocRect.left+FlapWidth*(i % m_FlapCols) + FlapRow*MOffset;
    if (m_ChildMap)
      rc.left += 2;
    rc.top    = m_MapDocRect.top - GetFlapHeight()*(FlapRow+1);
    rc.right  = rc.left+FlapWidth;
    rc.bottom = rc.top+GetFlapHeight();


    short Position;

    if (!(i % m_FlapCols))
      Position = FIRST_ELEM_IN_ROW;
    else if ((i % MaxFlaps()) == (MaxFlaps() - 1))
      Position = LAST_ELEM_IN_ROW;
    else
      Position = ANY_ELEM_IN_ROW;
  
    if (m_MapElemData != NULL)
      pme = new MapElem (this,
                         m_MapElemData->_Text, 
                         m_MapElemData->_Type, 
                         m_MapElemData->_Color, 
                         m_MapElemData->_Disabled, 
                         &rc, 
                         hWnd, 
                         FlapRow,
                         Position,
                         m_MapElemData->_CallBackData,
                         m_MapElemData->_CallBackProc,
                         m_MapElemData->_ExtraData ,
                         FALSE,
                         (m_MapElemData->kdset) ? &m_MapElemData->hk : NULL,
                         m_MapElemData->_Help,
                         m_MapElemData->_BitId,
                         m_MapElemData->_IndexX,
                         m_MapElemData->_IndexY
                        );
    else
      pme = new MapElem (this,
                         NULL,
                         0,
                         COLORREF(-1),   // Farbe
                         FALSE,
                         &rc, 
                         hWnd, 
                         FlapRow,
                         Position,
                         NULL,
                         0L,
                         NULL,
                         TRUE,
                         NULL,
                         NULL,
                         NULL,
                         0, 0
                        );
    InsertFlap (pme);

    if (StartFlap == NULL)
      StartFlap = pme;

    if (m_MapElemData != NULL) {
      FreeGlobMem (m_MapElemData->_Text);
      if (m_MapElemData->_Help)
        FreeGlobMem (m_MapElemData->_Help);
      FreeGlobMem (m_MapElemData);
      }
    m_MapElemData = Next;
    }

  if (StartFlap != NULL)
    StartFlap->Next = FirstFlap;

  if (ActiveFlap == NULL) {
    if (IndToActivate == -1) {
      for ( MapElem FAR *h = StartFlap ; ((ActiveFlap == NULL) && (h != NULL)) ; ) {
        if ((!h->Disabled) && (h->FlapText) && (*h->FlapText)) 
          ActiveFlap = h ;
        h = GetPrevMapElem(h);
        if (h == StartFlap) break ;
        }
      if (ActiveFlap == NULL)
        ActiveFlap = StartFlap;
      }
    else {
      int Cnt = 0;
      for (MapElem FAR *e = FirstFlapSet; 
            (((e != FirstFlapSet) || (Cnt == 0)) && (Cnt != IndToActivate) && (e)) ; e = e->Next, Cnt++) ;
      ActiveFlap = e ;
      if ((ActiveFlap != NULL) && (ActiveFlap->FlapText != NULL) && (*ActiveFlap->FlapText))
        CheckForReplacement (ActiveFlap,Cnt);
      else
        ActiveFlap = StartFlap ;
      }
    }

  // das mit CreateWindow erzeugte Fenster wird etwas kleiner 
  CopyRect (LPRECT (&m_MapScreenRect),LPRECT(&m_MapDocRect));
  InflateRect (LPRECT(&m_MapScreenRect), -int (MAP_BORDER * BaseUnit), 
                                         -int (MAP_BORDER * BaseUnit));
  }

/*-------------------------------------------------------------------------*\
*  member function:  InsertFlap                                             *
*                                                                           *
*  Parameter    :                                                           *
*  Rückgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void ClientMap::InsertFlap (MapElem FAR* pme)
  {
  pme->Next = FirstFlap;
  FirstFlap = pme;
  if (FirstFlapSet == NULL)
    FirstFlapSet = pme;
  }

/*-------------------------------------------------------------------------*\
*  member function:  RemoveFlap                                             *
*                                                                           *
*  Parameter    :                                                           *
*  Rückgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void ClientMap::RemoveFlap (MapElem FAR *pme)
  {
  MapElem FAR *prev = NULL;
  MapElem FAR *e    = FirstFlap;
  
  for ( ; e->Next != FirstFlap ; e = e->Next) {
    if (e == pme) {                // Element gefunden?
      if (prev != NULL)            // gibt es einen Vorgänger?
        prev->Next = pme->Next;    // Der Vorgänger zeigt auf meinen Nachfolger (d.h. ich bin weg!)
      else
        FirstFlap = pme->Next;     // ich war der erste, jetzt ist dies mein Nachfolger
        
      break;   
      }
    prev = e;  
    }
  }
  
/*-------------------------------------------------------------------------*\
*  member function:  PaintMap                                               *
*                                                                           *
*  Parameter     :                                                          *
*  Rueckgabewert :                                                          *
*  Zweck         :                                                          *
\*-------------------------------------------------------------------------*/
DLLExport void _export ClientMap::PaintMap (HDC hDC)
  {
  HBRUSH hOldBrush;
  HPEN   hOldPen;
  HPEN hNewPen = CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
  int i;

  // zeichnet fuer jede Reihe rechts ein Rechteck, um das dahinterliegende 
  // Fenster darzustellen
  hOldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
  if (m_FlapRows > 0) {
    RECT rc;
    CopyRect (&rc, LPRECT(&m_MapRect));
    rc.left = rc.right-MOffset-1;    // Rechteck nur so gross wie noetig zeichnen!
    rc.top += GetFlapHeight();
    rc.bottom = rc.top+m_MapDocRect.bottom-m_MapDocRect.top;
    for (i = 1; i < m_FlapRows; i++) {
      Rectangle (hDC, rc.left-2, rc.top-1, rc.right+1, rc.bottom);

      hOldPen = (HPEN)SelectObject (hDC, hNewPen);
      MoveToEx (hDC, rc.right-1, rc.top, NULL);
      LineTo (hDC, rc.right-1, rc.bottom-2);
      LineTo (hDC, rc.left, rc.bottom-2);
      SelectObject (hDC, hOldPen);

      OffsetRect (&rc, -MOffset, GetFlapHeight());
      }
    }
  SelectObject (hDC,hOldBrush);
  DeleteObject (hNewPen);

  i = 0;
  if (FirstFlap != NULL) 
    for (MapElem FAR* e = FirstFlap; !((e == FirstFlap) && (i > 0)); e = e->Next, i++)
      e->Paint (hDC);

  hOldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));
  hOldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
  Rectangle (hDC, m_MapDocRect.left, m_MapDocRect.top, m_MapDocRect.right+1, m_MapDocRect.bottom);
  SelectObject (hDC,hOldBrush);
  SelectObject (hDC, hOldPen);

    
  if (ActiveFlap != NULL) {
    hOldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
    if (m_ChildMap) {
      MoveToEx (hDC, m_MapDocRect.left, m_MapDocRect.bottom, NULL);
      LineTo (hDC, m_MapDocRect.right, m_MapDocRect.bottom);
      LineTo (hDC, m_MapDocRect.right, m_MapDocRect.top-1);
      } 
    else {
      MoveToEx (hDC, ActiveFlap->ptFlap[0].x, m_MapDocRect.top, NULL);
      LineTo (hDC, m_MapDocRect.left, m_MapDocRect.top);
      LineTo (hDC, m_MapDocRect.left, m_MapDocRect.bottom-1);
      LineTo (hDC, m_MapDocRect.right, m_MapDocRect.bottom-1);
      LineTo (hDC, m_MapDocRect.right, m_MapDocRect.top);
      LineTo (hDC, ActiveFlap->ptFlap[5].x, m_MapDocRect.top);
      }
    SelectObject (hDC, hOldPen);

    if (m_ChildMap) {
      hOldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
      MoveToEx (hDC, ActiveFlap->ptFlap[0].x-SELECTION_OFFSET, 
                     m_MapDocRect.top, NULL);
      LineTo (hDC, m_MapDocRect.left, m_MapDocRect.top);
      LineTo (hDC, m_MapDocRect.left, m_MapDocRect.bottom-1);

      MoveToEx  (hDC, m_MapDocRect.right-2, m_MapDocRect.top, NULL);
      LineTo (hDC, ActiveFlap->ptFlap[5].x-1, m_MapDocRect.top);
      SelectObject (hDC, hOldPen);
      }
    else {
      hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 2, RGB(0xFF, 0xFF, 0xFF)));
      MoveToEx (hDC, ActiveFlap->ptFlap[0].x+2, m_MapDocRect.top+2, NULL);
      LineTo (hDC, m_MapDocRect.left+2, m_MapDocRect.top+2);
      LineTo (hDC, m_MapDocRect.left+2, m_MapDocRect.bottom-2);
    
      MoveToEx  (hDC, m_MapDocRect.right-2, m_MapDocRect.top+2, NULL);
      LineTo (hDC, ActiveFlap->ptFlap[5].x, m_MapDocRect.top+2);
      DeleteObject (SelectObject (hDC, hOldPen));
      }

    if (!m_ChildMap) {
      hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0xC0, 0xC0, 0xC0)));
      MoveToEx (hDC, m_MapDocRect.left+3, m_MapDocRect.top+3, NULL);
      LineTo (hDC, m_MapDocRect.right-3, m_MapDocRect.top+3);
      DeleteObject (SelectObject (hDC, hOldPen));
      }

    if (m_ChildMap) {
      hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
      MoveToEx (hDC, m_MapDocRect.left+1, m_MapDocRect.bottom-1, NULL);
      LineTo (hDC, m_MapDocRect.right-1, m_MapDocRect.bottom-1);
      LineTo (hDC, m_MapDocRect.right-1, m_MapDocRect.top-1);
      DeleteObject (SelectObject (hDC, hOldPen));
      }
    else {
      hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 2, RGB(0x80, 0x80, 0x80)));
      MoveToEx (hDC, m_MapDocRect.left+3, m_MapDocRect.bottom-2, NULL);
      LineTo (hDC, m_MapDocRect.right-1, m_MapDocRect.bottom-2);
      LineTo (hDC, m_MapDocRect.right-1, m_MapDocRect.top+2);
      DeleteObject (SelectObject (hDC, hOldPen));
      }

    ActiveFlap->RePaint();
    }
  }

/*-------------------------------------------------------------------------*\
*  member function:  EraseBkGnd                                             *
*                                                                           *
*  Parameter    :                                                           *
*  Rückgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport void _export WINAPI ClientMap::EraseBkGnd (HWND hWnd,HDC hDC)
  {
  if (m_ChildMap)
    return;

  BOOL doDelete = FALSE ;
#ifdef WIN32
  HBRUSH hOutBrush = (HBRUSH)GetClassLong (m_hWndParent,GCL_HBRBACKGROUND);
#else
  HBRUSH hOutBrush = GetClassWord (m_hWndParent,GCW_HBRBACKGROUND);
  if (hOutBrush < COLOR_BTNHIGHLIGHT + 1)
    hOutBrush = CreateSolidBrush (GetSysColor (hOutBrush - 1)) , doDelete = TRUE ;
#endif
  HBRUSH hInBrush = (HBRUSH)GetStockObject (LTGRAY_BRUSH);

  RECT rc,cr;
  CopyRect (&rc, LPRECT(&m_MapScreenRect));
  GetClientRect (hWnd,&cr);
  HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN));

  // Alles ausserhalb mit hOutBrush zeichnen
  HBRUSH hOldBrush = (HBRUSH)SelectObject (hDC,hOutBrush);
  Rectangle (hDC,0,0,rc.left+1,cr.bottom+1);
  Rectangle (hDC,rc.right,0,cr.right+1,cr.bottom+1);
  Rectangle (hDC,rc.left,0,cr.right,rc.top+1);
  Rectangle (hDC,rc.left,rc.bottom,cr.right,cr.bottom+1);
  SelectObject (hDC,hOldBrush);

  // Das ScreenObject Grau zeichnen
  hOldBrush = (HBRUSH)SelectObject (hDC,hInBrush);
  Rectangle (hDC,rc.left,rc.top,rc.right + 2 * GetSystemMetrics (SM_CXBORDER),
                                rc.bottom + 2 * GetSystemMetrics (SM_CYBORDER));
  SelectObject (hDC,hOldBrush);

  SelectObject (hDC,hOldPen);
  if (doDelete)
    DeleteObject (hOutBrush);
  }

/*-------------------------------------------------------------------------*\
*  member function:  CheckForReplacement                                    *
*                                                                           *
*  Parameter    :                                                           *
*  Rückgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void ClientMap::CheckForReplacement (MapElem FAR* pme, int ElemCnt)
  {
  RECT rc;
  if (FirstFlap == NULL) return ;
  if (pme->Row > 0) {
    int i = 0;

    for (MapElem FAR *e = FirstFlap; !((e == FirstFlap) && (i > 0)); e = e->Next, i++) {
      if (e->Row < pme->Row)
        break;
      }
    FirstFlap = e;

    i = m_FlapCnt-1;

    MapElem FAR* prev;
    for (e = FirstFlap; !((e == FirstFlap) && (i <= 0)); e = e->Next, i--) {
      int FlapWidth = e->FlapRect.right-e->FlapRect.left;
      e->Row = i/m_FlapCols;

      rc.left   = m_MapDocRect.left+FlapWidth*(i % m_FlapCols) + e->Row*MOffset;
      if (m_ChildMap)
        rc.left += 2;
      rc.top    = m_MapDocRect.top - GetFlapHeight()*(e->Row+1);
      rc.right  = rc.left+FlapWidth;
      rc.bottom = rc.top+GetFlapHeight();

      e->SetElemRect (&rc);
      InflateRect (&rc, 6, 6);
      InvalidateRect (m_hWndParent, &rc, FALSE);
      prev = e;
      }
    
    StartFlap = prev;
    }

  CopyRect (&rc, LPRECT(&m_MapDocRect));
  rc.bottom = rc.top + int (MAP_BORDER * BaseUnit);
  InvalidateRect (m_hWndParent, &rc, FALSE);
  }
  
DLLExport void _export WINAPI ClientMap::HitTest (LPPOINT pt)
  {
  int Cnt = 0;
  if (FirstFlap == NULL) return ;
  for (MapElem FAR *e = FirstFlap; !((e == FirstFlap) && (Cnt > 0)); e = e->Next, Cnt++) {
    if (e->HitTest(pt)) {
      if (e == ActiveFlap) return ;       // Nix tun bitte;

      if (ActiveFlap != NULL) {
        if (!m_ChildMap) {
          RECT rc;

          if (m_FlapRows == 1) {
            SetRect (&rc, ActiveFlap->FlapRect.left-3, ActiveFlap->FlapRect.top-3,
                          ActiveFlap->FlapRect.right+3, ActiveFlap->FlapRect.top+3);
            InvalidateRect (m_hWndParent, &rc, FALSE);
            }
          else
            // da das erste Element erhoeht gezeichnet wurde ist es notwendig
            // diese kleine Erhoehung bei Deaktivieren wieder zu loeschen
            //----------------------------------------------------------------
            if (ActiveFlap->Position == FIRST_ELEM_IN_ROW) {
              SetRect (&rc, ActiveFlap->FlapRect.left, ActiveFlap->FlapRect.top-3,
                            ActiveFlap->FlapRect.left+MOffset, ActiveFlap->FlapRect.top+3);
              InvalidateRect (m_hWndParent, &rc, FALSE);
              }
          }
        ActiveFlap->SetActive (FALSE, FALSE, -1);    // alte Flappe normal zeichnen
        ActiveFlap->Invalidate (FALSE);
        }

      ActiveFlap = e;                               // das wird jetzt die neue Flappe
      if (ActiveFlap != NULL) {
        CheckForReplacement (e, Cnt);
        ActiveFlap->SetActive (TRUE, FALSE, GetPageNo(ActiveFlap));     // neue Flappe selektiert zeichnen
        ActiveFlap->Invalidate (FALSE);
        }

      return ;
      }
    }

  // eine Mappe in einem Dialog darf nicht quitschen
  char szParentClass[30];
  GetClassName (m_hWndParent, szParentClass, sizeof(szParentClass));
  if (!lstrcmp(szParentClass, "MYMDICLIENT"))
    MessageBeep (0);
  return;    
  }

DLLExport void _export WINAPI ClientMap::OnRButtonDown (LPPOINT pt)
  {
  int Cnt = 0;
  if (FirstFlap == NULL) return ;
  for (MapElem FAR *e = FirstFlap; !((e == FirstFlap) && (Cnt > 0)); e = e->Next, Cnt++) {
    if (e->HitTest(pt)) {
      HelpElem = e;
      e->GetHelp (pt);
      return;
      }
    }
  }

DLLExport void _export WINAPI ClientMap::OnMsg (HWND hWnd, UINT msg,
                                                WPARAM wParam, LPARAM lParam)
  {
  if (msg == WMU_DESTROYBUBBLE) {   
    if (HelpElem != NULL) {
      ReleaseCapture ();
      HelpElem->RemoveHelp();
      HelpElem = NULL;
      }
    }
  }


//------------------------------------------------------------------------------------
//
//                               Schnittstellen nach aussen
//
//------------------------------------------------------------------------------------
static int AnzOhren;
static LPMAPELEMDATA lpElemData;
static LPVOID CallBackPar;

static int UseCount ;
static void CreateBrushes ()
  {
  if (BRUSH_TYPE_0 == 0) {
    DBWIN_ASSERT (UseCount == 0);
    BRUSH_TYPE_0 = CreateSolidBrush(RGB(0x80, 0x80, 0x80));
    BRUSH_TYPE_1 = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
    BRUSH_TYPE_2 = CreateSolidBrush(RGB(0x80, 0, 0));
    }
  UseCount ++;
  }

static void DeleteBrushes ()
  {
  DBWIN_ASSERT (UseCount > 0);
  UseCount -- ;
  if (UseCount == 0) {
    DeleteObject (BRUSH_TYPE_0);
    DeleteObject (BRUSH_TYPE_1);
    DeleteObject (BRUSH_TYPE_2);
    BRUSH_TYPE_0 = 0 ;
    BRUSH_TYPE_1 = 0 ;
    BRUSH_TYPE_2 = 0 ;
    }
  }

LPCLIENTMAP CreateMap (HWND hWnd, int AnzOhren, LPMAPELEMDATA lpmed,
                       LPVOID cpb, BOOL ChildMap)
  {
  LPCLIENTMAP pClientMap = new ClientMap (AnzOhren, lpmed, cpb, ChildMap);
  if (pClientMap != NULL)  {
    pClientMap->SetParent (hWnd);
    CreateBrushes ();
    }

  return pClientMap;
  }


DLLExport void _export WINAPI DestroyMap (LPCLIENTMAP pClientMap)
  {
  if (pClientMap != NULL) {
    DeleteBrushes ();
    delete pClientMap;
    }
  }


//----------------------------------------------------------------------------
DLLExport void _export WINAPI StartSetmap (int af,int lw,int lh,LPVOID cbp)
  {
  AnzOhren = 0;
  IndToActivate = -1;
  lpElemData = NULL;
  CallBackPar = cbp;
  if ((lw > 0) && (lh > 0) && (af > 0)) {
    AnzFlaps = af;
    LogWidth = lw ;
    LogHeight = lh ;
    }
  else {
    AnzFlaps = -1;
    LogWidth = LogHeight = -1;
    }
    
  LogX = LogY = -1;

  old_FlapFont = FlapFont;
  old_FlapHeight = FlapHeight;
  old_MapOffset = MapOffset;

  SetMapFont (DEFAULT_FONT);           // statische Variable vorbelegen
  SetFlapHeight (FLAP_HEIGHT);
  SetMapOffset (FLAP_NEXTROW);
  }

//---------------------------------------------------------------------------
// Bestimmt Groesse und Position der Mappe 
// (Aufruf unbedingt vor CreateMapScreen)!!
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetMapExtent (int lx, int ly, int lw, int lh)
  {
  LogX = (lx >= 0) ? lx : -1;
  LogY = (ly >= 0) ? ly : -1;
  if (lw > 0) LogWidth = lw;
  if (lh > 0) LogHeight = lh;
  }

DLLExport void _export WINAPI SetStartInd (int ind)
  {
  IndToActivate = ind ;
  }

//----------------------------------------------------------------------------
DLLExport void _export WINAPI NextMapElem (LPSTR Text, WORD Type, COLORREF Color, 
                                           BOOL Disabled, LPVOID Data, 
                                           int cbSize, DWORD cbp, LPVOID ExtraData,
                                           HotKeyData FAR *kd, LPSTR Help, 
                                           DWORD dwBitId, short Ix, short Iy)
  {
  LPMAPELEMDATA lped = (LPMAPELEMDATA)GetGlobMem (sizeof(MapElemData));

  DBWIN_ASSERT (Text != NULL);
  lped->_Text = LPSTR(GetGlobMem (lstrlen(Text)+1));
  lstrcpy (lped->_Text,Text);
  lped->_Type = Type;
  lped->_Disabled = Disabled;
  lped->_CallBackData = GetGlobMem (cbSize);
  lped->_Color = Color;
  lmemcpy (lped->_CallBackData, Data, cbSize);

  if (ExtraData != NULL) {
    lped->_ExtraData = GetGlobMem (GetBlockSize(ExtraData));
    lmemcpy (lped->_ExtraData, ExtraData, GetBlockSize(ExtraData));
    }
  else
    lped->_ExtraData = NULL;
  if (kd != NULL) {
    lped->kdset = TRUE ;
    lped->hk = *kd ;
    }

  lped->_CallBackProc = cbp;

  lped->_Help = NULL;
  if (Help != NULL) {
    lped->_Help = LPSTR(GetGlobMem (lstrlen(Help)+1));
    lstrcpy (lped->_Help, Help);
    }

  lped->_BitId = dwBitId;
  lped->_IndexX = Ix;
  lped->_IndexY = Iy;

  LPMAPELEMDATA prev = NULL ;
  for (LPMAPELEMDATA h = lpElemData; h != NULL ; h = h->Next) {
    prev = h;
    }
  if (prev != NULL) prev->Next = lped ;
  else              lpElemData = lped ;

  AnzOhren ++;
  }

//----------------------------------------------------------------------------
DLLExport LPCLIENTMAP _export WINAPI BuildMap (HWND hWParent,MAPCALLCOMMAND mcmd,BOOL ChildMap)
  {
  MapCallCommand = mcmd;
  LPCLIENTMAP res = CreateMap (hWParent, AnzOhren, lpElemData, CallBackPar, ChildMap);
  lpElemData = NULL ;

  FlapFont   = old_FlapFont;
  FlapHeight = old_FlapHeight;
  MapOffset  = old_MapOffset;

  return res ;
  }

//----------------------------------------------------------------------------
int ClientMap::GetPageNo(MapElem FAR *e)
  {
  int res = 0 ;
  if (FirstFlapSet == NULL) return 0 ;
  for (MapElem FAR* h = FirstFlapSet; (h != e) ; ) {
    res ++ ;
    h = h->Next ;
    if (h == FirstFlapSet) break ;
    }
  return res;
  }

DLLExport void _export WINAPI ClientMap::DoActivate (BOOL state)
  {
  if (ActiveFlap != NULL)
    ActiveFlap->SetActive (state, FALSE, GetPageNo(ActiveFlap));
  if (!state)
    ActiveFlap = NULL;
  }

//----------------------------------------------------------------------------
DLLExport void _export WINAPI ClientMap::Update (LPSTR Text,WORD Type,COLORREF Color,BOOL disable,LPVOID cbData)
  {
  if (FirstFlap == NULL) return ;
  for (MapElem FAR*h = FirstFlap ; ; ) {
    h->Update (Text,Type,Color,disable,cbData);
    h = h->Next;
    if (h == FirstFlap) break ;
    }
  }

//----------------------------------------------------------------------------
DLLExport void _export WINAPI DisableMap (LPCLIENTMAP pClientMap)
  {
  if ((pClientMap != NULL) && (pClientMap->FirstFlap != NULL)) {
    int i = 0;
    for (MapElem FAR* e = pClientMap->FirstFlap; !((e == pClientMap->FirstFlap) && (i > 0)); e = e->Next, i++)
      e->Disable ();
    }
  }

//----------------------------------------------------------------------------
DLLExport void _export WINAPI EnableMap (LPCLIENTMAP pClientMap)
  {
  if ((pClientMap != NULL) && (pClientMap->FirstFlap != NULL)) {
    int i = 0;
    for (MapElem FAR* e = pClientMap->FirstFlap; !((e == pClientMap->FirstFlap) && (i > 0)); e = e->Next, i++)
      e->Enable ();
    }
  }

#define VKCTRL     0x1
#define VKSHIFT    0x2
#define VKALT      0x4

DLLExport BOOL _export WINAPI IsMapHotKey (LPMSG lpmsg, LPCLIENTMAP pClientMap)
  {
  if ((pClientMap != NULL) && 
/*
  (IsWindow(pClientMap->m_hWndMap) &&
   IsWindowEnabled(pClientMap->m_hWndMap)) &&
*/
                              (IsWindowEnabled(hFrameWnd))) {
    //----------------------------------------------------------------------
    // Hier wird ueberprueft ob die Mappe den Focus besitzt.
    // Denn wird in einem Formular ein Hotkey ausgeloest, dann darf die
    // darunterliegende Mappe auf keinen Fall auf diesen Hotkey reagieren.
    // Beispiel: F2 fuer aktuelles Datum oder Uhrzeit.
    // (Die Mappenhotkeys werden in der Nachrichtenschleife, schon ziemlich
    //  am Anfang abgefangen und draengen sich deshalb vor)
    //----------------------------------------------------------------------
    HWND hWndFocus = GetFocus ();

    if (hWndFocus) {
      BOOL bFound = FALSE;
      char szcln[64];
      GetClassName (hWndFocus, szcln, sizeof(szcln));
      if (lstrcmp(szcln, "DMWSToolBar")) {
        hWndFocus = GetParent (hWndFocus);
        if (hWndFocus) {
          GetClassName (hWndFocus, szcln, sizeof(szcln));
          if (!lstrcmp(szcln, "DMWSToolBar"))
            bFound = TRUE;
          }
        }
      else
        bFound = TRUE;

      if (!bFound)
        return FALSE;
      }


    if ((lpmsg->message == WM_KEYDOWN) || (lpmsg->message == WM_SYSKEYDOWN)) {
      BYTE keyflag = 0;

      keyflag = (GetKeyState(VK_CONTROL) & 0x1000) ? keyflag | VKCTRL : keyflag & ~VKCTRL;
      keyflag = (GetKeyState(VK_SHIFT) & 0x1000) ? keyflag | VKSHIFT : keyflag & ~VKSHIFT;
      keyflag = (GetKeyState(VK_MENU) & 0x1000) ? keyflag | VKALT : keyflag & ~VKALT;

      // Zuerst nachsehen, ob es vielleich ein gewoehnlicher Hotkey ist
      BOOL done = FALSE ;
      for (MapElem FAR *e = pClientMap->FirstFlap ; e != NULL ; e = e->Next) {
        if ((e->FlapText != NULL) && (*e->FlapText) && (!e->Disabled)) {
          if ((lpmsg->wParam == e->KeyData.VirtKey) && (keyflag == e->KeyData.Modify)) {
            done = TRUE ;
            pClientMap->SetActive (e);
            break ;
            }
          }
        if (e->Next == pClientMap->FirstFlap) break ;
        }
      if ((!done) && (lpmsg->wParam == VK_F7) && (keyflag & VKCTRL) && (pClientMap->ActiveFlap != NULL)) {
        BOOL found = FALSE;
        MapElem FAR *e = pClientMap->ActiveFlap->Next;

        //----------------------------------------------
        // CTRL + SHIFT + F7  =>  bewegen rueckwaerts
        if (keyflag & VKSHIFT) {
          for ( ; ; e = e->Next)
            if ((e->FlapText != NULL) && (*e->FlapText) && (!e->Disabled)) {
              found = TRUE;
              break;
              }
          }
        //----------------------------------------------
        // CTRL + F7  =>  bewegen vorwaerts
        else {
          for ( ; ; e = e->Next)
            // bin ich das naechste Element?
            if (e->Next == pClientMap->ActiveFlap) {
              if ((e->FlapText != NULL) && (*e->FlapText) && (!e->Disabled)) {
                found = TRUE;
                break;
                }
              // ich war schon richtig hatte aber leider keinen Text; deshalb
              // so lange suchen, bis das letzte sinnvolle  Element erreicht.
              // Das letzte moegliche Element wurde erreicht!
              else {
                MapElem FAR *tmp = e->Next;
                while ((tmp->FlapText != NULL) && (*tmp->FlapText) && (!tmp->Disabled)) {
                  e = tmp;
                  tmp = tmp->Next;
                  }
                found = TRUE;
                break;
                }
              }
          }

        if (found && (e != pClientMap->ActiveFlap))
          pClientMap->SetActive (e);

        return TRUE;
        }
      }
    }

  return FALSE;
  }

DLLExport LPVOID _export WINAPI ClientMap::GetFirstExtraData (LPVOID FAR *x)
  {
  if (FirstFlap == NULL) { *x = NULL ; return NULL ; }
  *x = FirstFlap ;
  return FirstFlap->_ExtraData ;
  }

DLLExport LPVOID _export WINAPI ClientMap::GetNextExtraData (LPVOID FAR *x)
  {
  MapElem FAR *h = ((MapElem FAR *) (*x))->Next ;
  *x = h;
  if (h == FirstFlap) { *x = NULL ; return NULL ; }
  else                return h->_ExtraData ;
  }

DLLExport void _export WINAPI ClientMap::SetActive (LPVOID x)
  {
  if (FirstFlap == NULL) return ;
  MapElem FAR *h = (MapElem FAR *) x ;
  int Cnt = 0;
  for (MapElem FAR *e = FirstFlap; !((e == FirstFlap) && (Cnt > 0)); e = e->Next, Cnt++) {
    if (e == h) {
      if (e == ActiveFlap) return ;       // Nix tun bitte;

      if (ActiveFlap != NULL) {
        ActiveFlap->SetActive (FALSE, FALSE,-1);    // alte Flappe normal zeichnen
        ActiveFlap->Invalidate (FALSE);
        }

      ActiveFlap = e;                               // das wird jetzt die neue Flappe
      if (ActiveFlap != NULL) {
        CheckForReplacement (e, Cnt);
        ActiveFlap->SetActive (TRUE, FALSE, GetPageNo(ActiveFlap));     // neue Flappe selektiert zeichnen
        ActiveFlap->Invalidate (FALSE);
        }

      return ;
      }
    }
  }

//---------------------------------------------------------------------------
// Bestimmt die Schriftart in den einzelnen Ohrwascheln 
// (Aufruf unbedingt vor CreateMapScreen)!!
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetMapFont (short Format)
  {
  FlapFont = Format;          // statische Variable
  }

//---------------------------------------------------------------------------
// Bestimmt die Schriftart in den einzelnen Ohrwascheln 
// (Aufruf unbedingt vor CreateMapScreen)!!
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetFlapHeight (short Height)
  {
  FlapHeight = Height;          // statische Variable
  }

//---------------------------------------------------------------------------
// Bestimmt die Schriftart in den einzelnen Ohrwascheln 
// (Aufruf unbedingt vor CreateMapScreen)!!
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetMapOffset (short Offset)
  {
  MapOffset = Offset;          // statische Variable
  }
