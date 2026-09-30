//////////////////////////////////////////////////////
//  Zusammenmischen von Texten
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ctool/rev/mergetxt.cpv   1.8   25 Jul 1996 19:56:34   GERHOLD  $
//  $Log:   P:/marille/clinicum/ctool/rev/mergetxt.cpv  $
// 
//    Rev 1.8   25 Jul 1996 19:56:34   GERHOLD
// int far *  =>  DBINT FAR *
// 
//    Rev 1.7   24 Mar 1996 12:10:26   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.6   02 Feb 1996 10:42:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   13 Oct 1995 17:53:56   MARTIN
// TextMerge verbessert
// 
//    Rev 1.4   04 Oct 1995 20:02:40   MARTIN
// Invalidieren richtig
// 
//    Rev 1.3   02 Oct 1995 18:16:48   MARTIN
// erste funktionierende Version
// 
//    Rev 1.2   24 Sep 1995 19:08:32   MARTIN
// 
//    Rev 1.1   16 Sep 1995 22:23:18   HANNES
// Version Hannes
// 
//    Rev 1.0   16 Sep 1995 02:03:42   HANNES
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#define MODULENUM  160
#include "winass.hpp"
#ifndef MAPTYPE_GEOMETRIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "globmem.h"
#include "cfield.hpp"
#include "wordwin.hpp"
#include "toolbar.hpp"
#include "font.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "data.hpp"

extern CFIELDCALLBACK GetFieldCallback();
inline int XtoLOG (HDC hDC,int x)
  {
  POINT pt;
  pt.x = x ;
  pt.y = 0 ;
  DPtoLP (hDC,&pt,1);
  return pt.x;
  }

class FAR TextPosten : public wtobj {
 public :
  TextPosten FAR *Next;
  int x,y,w,h,wd;
  int lastFormat;
  LPINT Format;
  LPSTR FAR *TextOben;
  LPSTR FAR *TextUnten;
  LPSTR outTxt;
  int AnzahlGesamt;
  LPINT color;
  LPINT oldcolor;
  BOOL WichtigOben;
  cField FAR *field;

  int AnzOben ()
    {
    return (GetBlockSize(TextOben) / sizeof(TextOben[0])) ;
    }
  int AnzUnten ()
    {
    return (GetBlockSize(TextUnten) / sizeof(TextUnten[0])) ;
    }
  void AddOben (LPSTR txt,int Color,int format)
    {
    LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzOben() + 1) * sizeof(LPSTR)) ;
    if (TextOben != NULL)
      lmemcpy (n,TextOben,GetBlockSize(TextOben));
    n[AnzOben()] = LPSTR(GetGlobMem (lstrlen(txt) + 1));
    lstrcpy(n[AnzOben()],txt);
    Format[AnzOben()] = format ;
    color[AnzOben()] = Color ;
    if (TextOben != NULL)
      FreeGlobMem (TextOben);
    TextOben = n ;
    }
  void AddUnten (LPSTR txt,int Color, int format)
    {
    LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzUnten() + 1) * sizeof(LPSTR)) ;
    if (TextUnten != NULL)
      lmemcpy (n,TextUnten,GetBlockSize(TextUnten));
    n[AnzUnten()] = LPSTR(GetGlobMem (lstrlen(txt) + 1));
    lstrcpy(n[AnzUnten()],txt);
    Format[AnzahlGesamt - AnzUnten() - 1] = format ;
    color[AnzahlGesamt - AnzUnten() - 1] = Color ;
    if (TextUnten != NULL)
      FreeGlobMem (TextUnten);
    TextUnten = n ;
    }
  void RemoveOben ()
    {
    DBWIN_ASSERT (AnzOben() >= 1) ;
    FreeGlobMem (TextOben[AnzOben()-1]) ;
    if (AnzOben() > 1) {
      LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzOben() - 1) * sizeof(LPSTR)) ;
      lmemcpy (n,TextOben,GetBlockSize(n));
      FreeGlobMem (TextOben) ;
      TextOben = n ;
      }
    else {
      FreeGlobMem (TextOben) ;
      TextOben = NULL ;
      }
    }
  void RemoveUnten ()
    {
    DBWIN_ASSERT (AnzUnten() >= 1) ;
    FreeGlobMem (TextUnten[AnzUnten()-1]) ;
    if (AnzUnten() > 1) {
      LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzUnten() - 1) * sizeof(LPSTR)) ;
      lmemcpy (n,TextUnten,GetBlockSize(n));
      FreeGlobMem (TextUnten) ;
      TextUnten = n ;
      }
    else {
      FreeGlobMem (TextUnten) ;
      TextUnten = NULL ;
      }
    }
  void AddText (LPSTR Txt,int Color,BOOL Wichtig,BOOL wo,int ag,int f,int x0,int y0,int wdev)
    {
    if (AnzahlGesamt == -1) {
      WichtigOben = wo;
      AnzahlGesamt = ag;
      x = x0 ;
      y = y0 ;
      wd = wdev ;
      Format = LPINT(GetGlobMem (AnzahlGesamt * sizeof(int)));
      color = LPINT(GetGlobMem (AnzahlGesamt * sizeof(int)));
      }
    else {
      DBWIN_ASSERT (WichtigOben == wo);
      DBWIN_ASSERT (AnzahlGesamt == ag);
      }
    lastFormat = f;
    if (Wichtig) {
      if (WichtigOben) {
        if (AnzOben() < AnzahlGesamt)
          AddOben(Txt,Color,f) ;
        if (AnzOben() + AnzUnten() > AnzahlGesamt)
          RemoveUnten() ;
        }
      else {
        if (AnzUnten() < AnzahlGesamt)
          AddUnten(Txt,Color,f) ;
        if (AnzOben() + AnzUnten() > AnzahlGesamt)
          RemoveOben() ;
        }
      }
    else {
      if (AnzOben() + AnzUnten() < AnzahlGesamt) {
        if (WichtigOben)
          AddUnten(Txt,Color,f) ;
        else
          AddOben(Txt,Color,f) ;
        }
      }
    }
  void BuildString ()
    {
    if (outTxt) FreeGlobMem (outTxt);
    int gsize = 0 ;
#define MAX_FONT_NUMBER_SIZE 9
    for (int i = 0 ; i < AnzOben() ; i++ )   gsize += lstrlen(TextOben[i]) + MAX_FONT_NUMBER_SIZE ;
    for (i = 0 ; i < AnzUnten() ; i++ ) gsize += lstrlen(TextUnten[i]) + MAX_FONT_NUMBER_SIZE ;
    gsize += 2 * AnzahlGesamt + 1;   // darfs a bisserl mehr sein ?
    outTxt = LPSTR(GetGlobMem (gsize)) ;

    LPSTR h = outTxt ;
    for (i = 0 ; i < AnzOben() ; i++ )
      wsprintf (h,"\\f:%d\\%s\r",Format[i],TextOben[i]) , h += lstrlen (h) ;
    for ( ; i < AnzahlGesamt - AnzUnten() ; i++ ) *h++ = ' ', *h++ = '\r' ;
    for ( int j = AnzUnten() - 1 ; i < AnzahlGesamt ; i++ , j --)
      wsprintf (h,"\\f:%d\\%s\r",Format[i],TextUnten[j]) , h += lstrlen (h) ;
    }
  void FreeWorkMemory ()
    {
    for (int i = 0 ; i < AnzOben() ; i++)
      FreeGlobMem (TextOben[i]) ;
    for (i = 0 ; i < AnzUnten() ; i++)
      FreeGlobMem (TextUnten[i]) ;
    if (TextOben != NULL)   FreeGlobMem (TextOben);
    if (TextUnten != NULL) FreeGlobMem (TextUnten);
    TextOben   = NULL;
    TextUnten = NULL;
    }
  void SetTwips (HDC hDC)
    {
    int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
    int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
    SetMapMode (hDC,MM_ANISOTROPIC);
    SetWindowExtEx (hDC,1440,1440, NULL);
    SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
    SetViewportOrgEx (hDC,x,y, NULL);
    SetWindowOrgEx (hDC,0,0, NULL);
    }
  void SetMMText (HDC hDC)
    {
    SetMapMode (hDC,MM_TEXT);
    SetViewportOrgEx (hDC,0,0, NULL);
    SetWindowOrgEx (hDC,0,0, NULL);
    }
  void RectToDev (LPRECT r,HWND hWnd)
    {
    HDC hDC = GetDC (hWnd);
    SetTwips (hDC);
    POINT pt[2];
    pt[0].x = r->left  , pt[0].y = r->top ;
    pt[1].x = r->right , pt[1].y = r->bottom ;
    LPtoDP (hDC, pt, 2);
    ReleaseDC (hWnd,hDC);

    r->left  = pt[0].x , r->top    = pt[0].y ;
    r->right = pt[1].x , r->bottom = pt[1].y ;
    }
  BOOL IsEmpty()
    {
    return ((AnzUnten() == 0) && (AnzOben() == 0)) ;
    }
  void ResetColors()
    {
    if (color != NULL) {
      if (oldcolor == NULL) oldcolor = LPINT(GetGlobMem (GetBlockSize(color)));
      lmemcpy (oldcolor,color,GetBlockSize(color));
      for (int i = 0 ; i < AnzahlGesamt ; i++)
        color[i] = 0;
      }
    }
  BOOL CheckUpdate (HWND hWnd)
    {
    BOOL res = TRUE ;
    // Retten des alten Ausgabetextes
    LPSTR old;
    LPINT oldFormat;
    if (outTxt != NULL) {
      old = LPSTR(GetGlobMem (GetBlockSize(outTxt))) , lmemcpy (old,outTxt,GetBlockSize(outTxt));
      oldFormat = LPINT(GetGlobMem (GetBlockSize(Format))) , lmemcpy (oldFormat,Format,GetBlockSize(Format));
      }
    else
      old = NULL ;
    BuildString ();
    if (!IsEmpty()) {
      FreeWorkMemory ();
      if (old != NULL) {
        if ((lstrcmp (old,outTxt) != 0) ||
            (!lmemcmp (color,oldcolor,GetBlockSize(oldcolor))) ||
            (!lmemcmp (Format,oldFormat,GetBlockSize(oldFormat)))) {
          // Das Feld muss upgedated werden
          RECT r ;
          SetRect (&r,x,y,x + w,y + h) ;
          InflateRect(&r,2,2);
          InvalidateRect (hWnd,&r,TRUE);
          *field = outTxt ;
          field->GetFieldRect (&r,0);
          RectToDev (&r,hWnd) ;
          w = r.right  - r.left + 1;
          h = r.bottom - r.top  + 1;
          SetRect (&r,x,y,x + w,y + h) ;
          InflateRect(&r,2,2);
          InvalidateRect (hWnd,&r,TRUE);
          }
        FreeGlobMem (old);
        }
      else {
        // Das Feld muss neu angelegt werden + Weiter Initialisierungen
//        HDC hDC = GetDC (hWnd);
//        SetTwips (hDC);
//        int wl = XtoLOG (hDC,wd);
//        ReleaseDC (hWnd ,hDC);
//        field = new cField (TRANSPARENT, lastFormat, 0, 0, wl, AnzahlGesamt, FALSE);

        field = new cField (TRANSPARENT, lastFormat, 0, 0, -1, AnzahlGesamt, FALSE);
        int dummy;
        field->InstallCallBack (GetFieldCallback(), &dummy, sizeof(dummy));
        field->SetWindow (hWnd);
        field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
        field->SetWOrg (0,0);
        *field = outTxt ;
        RECT r;
        field->GetFieldRect (&r,0);
        RectToDev (&r,hWnd) ;
        w = r.right  - r.left + 1;
        h = r.bottom - r.top  + 1;
        SetRect (&r,x,y,x + w,y + h) ;
        InflateRect(&r,2,2);
        InvalidateRect (hWnd,&r,TRUE);
        }
      }
    else {
      if (old != NULL) {
        FreeGlobMem (old);
        RECT r ;
        SetRect (&r,x,y,x + w,y + h) ;
        InflateRect(&r,2,2);
        InvalidateRect (hWnd,&r,TRUE);
        }
      res = FALSE;
      }
    return res;
    }
  void Paint (HDC hDC)
    {
//    HPEN hOldPen = SelectObject (hDC,GetStockObject (NULL_PEN));
    for (int i = 0 ; i < AnzahlGesamt ; i++) {
//      HBRUSH hOldBrush = SelectObject (hDC,CreateSolidBrush (PALETTEINDEX(color[i])));
//      Rectangle (hDC,x - 1,y + 1 + i * h / AnzahlGesamt,x + w + 1,y + 2 + (i + 1) * h / AnzahlGesamt);
//      DeleteObject (SelectObject (hDC,hOldBrush));
      HBRUSH hBrush = CreateSolidBrush (PALETTEINDEX(color[i]));
      RECT r;
      SetRect (&r,x - 1,y + 1 + i * h / AnzahlGesamt,x + w + 1,y + 2 + (i + 1) * h / AnzahlGesamt);
      FillRect(hDC,&r,hBrush);
      DeleteObject (hBrush);
      }
//    SelectObject (hDC,hOldPen);
    SetTwips (hDC);
    field->Paint (hDC, 0, FALSE);
    SetMMText (hDC);
    }
  void GetRect (LPRECT r)
    {
    SetRect (r,x,y,x+w,y+h);
    }
  TextPosten()
    {
    AnzahlGesamt = -1 ;
    }
  ~TextPosten()
    {
    if (field != NULL)
      delete field ;
    if (color != NULL)
      FreeGlobMem (color) ;
    if (oldcolor != NULL)
      FreeGlobMem (oldcolor) ;
    if (Format != NULL)
      FreeGlobMem (Format) ;
    if (outTxt != NULL)
      FreeGlobMem (outTxt);
    }
  };

// Implementierung der Klasse Textmerge
///////////////////////////////////////////
static TextMerge FAR *tm;
DLLExport void _export WINAPI AddMergeText (int dx,int dy,int w,int AnzahlGesamt,LPSTR txt,int color,int Format,BOOL Wichtig,BOOL WichtigOben)
  {
  DBWIN_ASSERT (tm != NULL) ;
  TextPosten FAR *h = tm->GetTextPosten (tm->x0 + dx,tm->y0 + dy);
  h->AddText (txt,color,Wichtig,WichtigOben,AnzahlGesamt,Format,tm->x0 + dx,tm->y0 + dy,w);
  }
TextPosten FAR *TextMerge::GetTextPosten (int x,int y)
  {
  for ( TextPosten FAR *h = tp ; h != NULL ; h = h->Next)
    if ((h->x == x) && (h->y == y)) return h ;
  // Nix gefunden
  TextPosten FAR *n = new TextPosten ();
  n->Next = tp ;
  tp = n ;
  return tp ;
  }
void TextMerge::BuildTextPosten ()
  {
  // gegebenenfalls alte Farben merken
  for ( TextPosten FAR *h = tp ; h != NULL ; h = h->Next )
    h->ResetColors();

  // Die Ladescripts aufrufen
  tm = this ;
  LPVOID x ;
  for ( x = NULL ; ((x = (* NextTextForMerge) (privData,tm->Param()->bmList,tm->Param()->cbProc,x)) != NULL) ; ) ;
  tm = NULL ;

  // Und die Ausgabestrings erzeugen
  TextPosten FAR *prev = NULL ;
  for ( h = tp ; h != NULL ; ) {
    TextPosten FAR *next = h->Next ;
    if (!h->CheckUpdate (Parent->Parent->hWndToolbar())) {
      // h wird nicht mehr benoetigt
      if (prev != NULL) prev->Next = h->Next ;
      else              tp = h->Next ;
      delete h ;
      }
    else
      prev = h ;
    h = next ;
    }
  }
void TextMerge::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->bmList, StructData);
  }
void TextMerge::GetRect ()
  {
  SetRectEmpty (LPRECT (&ToolRect));
  for ( TextPosten FAR *x = tp ; x != NULL ; x = x->Next) {
    RECT rp;
    if (IsRectEmpty (LPRECT (&ToolRect)))
      x->GetRect (LPRECT(&ToolRect));
    else {
      x->GetRect (&rp);
      UnionRect (LPRECT(&ToolRect),LPRECT(&ToolRect),&rp);
      }
    }
  InflateRect(LPRECT(&ToolRect),2,2);
  }
void TextMerge::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(),LPRECT(&ToolRect),doErase);
  }
void TextMerge::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  x0 = ToDevKoordX (tx);
  y0 = ToDevKoordY (ty, Parent->Layer);
  BuildTextPosten ();
  GetRect ();
  }
void TextMerge::MoveTool ()
  {
  int yn = ToDevKoordY(ty, Parent->Layer);
  int dy = yn - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);

    Invalidate (FALSE);
    y0 = yn ;
    }
  }
void TextMerge::PaintTool (HDC hDC, HDC hmemDC)
  {
  for ( TextPosten FAR *x = tp ; x != NULL ; x = x->Next)
    x->Paint (hDC);
  }
void TextMerge::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  for ( ; tp != NULL ; ) {
    TextPosten FAR *next = tp->Next ;
    delete tp ;
    tp = next ;
    }
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);
  (* ClearConnection) (privData, Param()->bmList, StructData);
  }
void TextMerge::Update ()
  {
  BuildTextPosten ();
  GetRect ();
  }

