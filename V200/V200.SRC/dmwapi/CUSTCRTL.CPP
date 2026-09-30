/*---------------------------------------------------*/
/*    Implementierung einiger Custom - Controls      */
/*---------------------------------------------------*/
// $Header:   P:/marille/clinicum/dmwapi/rev/custcrtl.cpv   1.2   05 Oct 1998 11:11:16   Gerhold  $
// $Log:   P:/marille/clinicum/dmwapi/rev/custcrtl.cpv  $
// 
//    Rev 1.2   05 Oct 1998 11:11:16   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.1   02 Feb 1996 10:46:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:38   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   05 Jul 1993 15:01:44   HANNES
// Recalleintraege loschbar
// 
//    Rev 1.1   23 Jun 1993 11:20:36   HANNES
// Fehlerkorrektur im Kalender
// 
//    Rev 1.0   02 Jun 1993 19:31:38   HANNES
// Initial revision.
// 
//    Rev 1.0   02 Dec 1992 15:22:00   HANNES
// Initial revision.
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "ddsmsg.h"
#include "globmem.h"

struct DayState {
  unsigned Disabled : 1 ;
  unsigned Day : 6 ;
  COLORREF clr;
  };

struct clrselday {
  int AnzDaysSelected;          // Anzahl der Tage, die selektiert sind
  int ActSelected;              // Aktueller Tag (durch Umrahmung angezeigt)
  int LastSelected;
  DWORD MInfo ;
  BOOL dontRedraw;
  DayState DaySelected[1];
  };

/*
**
** Realisierung der Darstellung der Tage eines Monates:
** mit dem Fenster verbunden ist ein Globalhandle, der auf
** eine Datenstruktur vom Typ clrselday zeigt
**
** Verwaltete Meldungen:
**    CLR_SELDAY        ... Selektion eines Tages
**    CLR_DESELDAY      ... Tag Deselktieren
**    CLR_RESET         ... Alle Selektionen aus und neuzeichnen
**    CLR_GETCURSEL     ... Aktuell selektierter Item
**
** Versandte Nachrichten:
**    CLR_SELCHANGE     ... Selektion wurde Getroffen (mit Mouseclick)
**    CLR_DBLCLK        ... Doppelklick eines Items
*/

#ifdef WIN32
  #define GWL_HWINFO      0
#else
  #define GWW_HWINFO      0
#endif
DWORD GetMInfo (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  DWORD res = 0L ;
  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    res = c->MInfo;
    GlobalUnlock (hGmem);
    }
  return res;
  }

void SetMInfo (HWND hWnd,DWORD Info)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    c->MInfo = Info;
    GlobalUnlock (hGmem);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof (clrselday));
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    c->MInfo = Info;
    c->ActSelected = -1;
    GlobalUnlock (hGmem);

#ifdef WIN32
    SetWindowLong (hWnd,GWL_HWINFO,LONG(hGmem));
#else
    SetWindowWord (hWnd,GWW_HWINFO,hGmem);
#endif
    }
  }

static BOOL IsDaySelected (HWND hWnd,int Day,COLORREF FAR *clr = NULL)
  {
  BOOL res = FALSE ;

#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    for (int i = 0 ; i < c->AnzDaysSelected ; i++) {
      if (res = 
          ((c->DaySelected[i].Day == WORD (Day)) && 
           (c->DaySelected[i].clr))
         ) {
        if (clr != NULL)
          *clr = c->DaySelected[i].clr ;
        break ;
        }
      }
    GlobalUnlock (hGmem);
    }
  return res;
  }

static BOOL IsDayDisabled (HWND hWnd,int Day)
  {
  BOOL res = FALSE ;

#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    for (int i = 0 ; i < c->AnzDaysSelected ; i++)
      res = res || 
          ((c->DaySelected[i].Day == WORD (Day)) && (c->DaySelected[i].Disabled)) ;
    GlobalUnlock (hGmem);
    }
  return res;
  }

void InsertDay (HWND hWnd,int Day,COLORREF Color,BOOL Disable)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c;
  if (hGmem) {
    c = (clrselday FAR *) GlobalLock (hGmem);
    int Size = sizeof (clrselday) + c->AnzDaysSelected * sizeof (DayState);
    GlobalUnlock (hGmem);
    hGmem = GlobalReAlloc (hGmem,Size,GMEM_MOVEABLE);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof (clrselday)) ;
    c = (clrselday FAR *) GlobalLock (hGmem);
    c->AnzDaysSelected = 0 ;
    GlobalUnlock (hGmem);
    }
  c = (clrselday FAR *) GlobalLock (hGmem);
  c->DaySelected[c->AnzDaysSelected].Day = Day ;
  c->DaySelected[c->AnzDaysSelected].clr = Color ;
  c->DaySelected[c->AnzDaysSelected].Disabled = Disable ;
  c->AnzDaysSelected += 1 ;
  GlobalUnlock (hGmem);

#ifdef WIN32
  SetWindowLong (hWnd,GWL_HWINFO,LONG(hGmem));
#else
  SetWindowWord (hWnd,GWW_HWINFO,hGmem);
#endif

  }

void DeleteDay (HWND hWnd,int Day)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
  c->AnzDaysSelected -= 1 ;
  BOOL found = FALSE ;
  for (int i = 0 ; i < c->AnzDaysSelected ; i++) {
    if (c->DaySelected[i].Day == WORD (Day)) {
      c->DaySelected[i].clr = 0 ;
      found = (c->DaySelected[i].Disabled == 0) ; // Es darf geloscht werden
      }
    if (found)
      c->DaySelected[i] = c->DaySelected[i+1];
    }
  GlobalUnlock (hGmem);
  }

void GetDayRect (HWND hWnd,int Day,RECT FAR *r)
  {
  RECT cr;
  GetClientRect (hWnd,&cr);
  double dx = double (cr.right) / 7.0 ;
  double dy = double (cr.bottom) / 7.0 ;
  LONG mi = GetMInfo (hWnd);
  int posy = (Day + LOWORD(mi)) % 7 ;
  int posx = (Day + LOWORD(mi)) / 7 + 1 ;
  int x0 = int (double (posx) * dx + 0.5) + 1 ;
  int y0 = int (double (posy) * dy + 0.5) + 1 ;
  int x1,y1 ;
  if (posx == 6) x1 = cr.right - 2 ;
  else           x1 = int (double (posx + 1) * dx + 0.5) - 1 ;
  if (posy == 6) y1 = cr.bottom - 2 ;
  else           y1 = int (double (posy + 1) * dy + 0.5) - 1 ;
  r->left = x0 ;         r->top = y0 ;
  r->right = x1 ;        r->bottom = y1 ;
  }

void SelectDay (HDC hDC,HWND hWnd,int Day,COLORREF Color)
  {
  RECT cr;
  GetClientRect (hWnd,&cr);

  DWORD oldColor = SetTextColor (hDC,Color);

  double dx = double (cr.right) / 7.0 ;
  double dy = double (cr.bottom) / 7.0 ;
  LONG mi = GetMInfo (hWnd);
  int posy = (Day + LOWORD(mi)) % 7 ;
  int posx = (Day + LOWORD(mi)) / 7 + 1 ;
  TEXTMETRIC tm;
  GetTextMetrics (hDC,&tm);
  int x = int (dx * double (posx) + dx / 2.0 + 0.5) ;
  int y = int (dy * double (posy) + dy / 2.0 + double (tm.tmAscent) / 2.0 + 0.5) ;
  char outtxt[10];
  wsprintf (outtxt,"%d",Day+1);
  SetTextAlign (hDC,TA_BASELINE | TA_CENTER) ;
  TextOut (hDC,x,y,outtxt,lstrlen(outtxt));

  SetTextColor (hDC,oldColor);
  }

int CheckDay (HWND hWnd,int x,int y)
  {
  RECT r;
  GetClientRect (hWnd,&r);
  double dx = double (r.right) / 7 ;
  double dy = double (r.bottom) / 7 ;
  int posx = int (double (x) / dx) ;
  int posy = int (double (y) / dy) ;

  if (posx < 1) return -1 ;

  if (posx > 6) posx = 6 ;
  if (posy > 6) posy = 6 ;
  int i = posy + (posx - 1) * 7 ;
  LONG mi = GetMInfo (hWnd);
  int Day = i - LOWORD (mi) ;
  if (Day < 0)                 return -1 ;
  if (WORD (Day) >= HIWORD(mi))       return -1 ;
  if (IsDayDisabled(hWnd,Day)) return -1 ;
  return Day ;
  }

void SetActSelected (HWND hWnd,int Day)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c;
  if (hGmem) {
    c = (clrselday FAR *) GlobalLock (hGmem);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof (clrselday)) ;
    c = (clrselday FAR *) GlobalLock (hGmem);
    c->AnzDaysSelected = 0 ;
    }
  c->LastSelected = c->ActSelected ;
  c->ActSelected = Day ;
  GlobalUnlock (hGmem);

#ifdef WIN32
  SetWindowLong (hWnd,GWL_HWINFO,LONG(hGmem));
#else
  SetWindowWord (hWnd,GWW_HWINFO,hGmem);
#endif
  }

int GetActSelected (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c;
  int res = -1 ;
  if (hGmem) {
    c = (clrselday FAR *) GlobalLock (hGmem);
    res = c->ActSelected ;
    GlobalUnlock (hGmem);
    }
  return res;
  }

int GetLastSelected (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c;
  int res = -1 ;
  if (hGmem) {
    c = (clrselday FAR *) GlobalLock (hGmem);
    res = c->LastSelected ;
    GlobalUnlock (hGmem);
    }
  return res;
  }

void SetDayFocus (HDC hDC,HWND hWnd,int day,BOOL State)
  {
  RECT r;
  GetDayRect (hWnd,day,&r);

  HBRUSH hOldBrush = (HBRUSH)SelectObject (hDC,GetStockObject(NULL_BRUSH));
  HPEN hPen;
  if (State)
    hPen = CreatePen (PS_DOT,1,RGB(0,0,0));
  else
    hPen = CreatePen (PS_DOT,1,RGB(0xFF,0xFF,0xFF));
  HPEN hOldPen = (HPEN)SelectObject (hDC,hPen);
//  int nOldmode = SetROP2 (hDC,R2_XORPEN);

  Rectangle (hDC,r.left,r.top,r.right,r.bottom);

//  SetROP2 (hDC,nOldmode);
  SelectObject (hDC,hOldPen);
  DeleteObject (hPen);
  SelectObject (hDC,hOldBrush);
  }

void InvalidateDay (HWND hWnd,int day)
  {
  RECT r;
  GetDayRect (hWnd,day,&r);

  InvalidateRect (hWnd,&r,TRUE);
  }

void ResetSelDays (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    c->AnzDaysSelected = 0 ;
    GlobalUnlock (hGmem);
    }
  }

void SetRedrawPar (HWND hWnd,WORD wP)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
  if (wP)
    c->dontRedraw = FALSE ;
  else
    c->dontRedraw = TRUE ;
  GlobalUnlock (hGmem);
  }

BOOL DoRedraw (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  BOOL res = TRUE ;
  if (hGmem) {
    clrselday FAR *c = (clrselday FAR *) GlobalLock (hGmem);
    if (c->dontRedraw) res = FALSE ;
    GlobalUnlock (hGmem);
    }
  return res ;
  }


#define SHORTDAY        2000
extern HINSTANCE hLibInst;
DLLExport LONG _export CALLBACK clndrWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  int Day;

  switch (msg) {
    case CLR_SETMINFO :
      SetMInfo (hWnd,lP);
      break ;

    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      RECT cr;

      HDC hDC = BeginPaint (hWnd,&ps);
      GetClientRect (hWnd,&cr);
      double dx = double (cr.right) / 7.0 ;
      double dy = double (cr.bottom) / 7.0 ;

      // Zeichnen der Linien
      int i,x,y ;
      for (i = 0 ; i < 7 ; i++) {
        y = int (dy * double (i) + 0.5) ;
        MoveToEx (hDC,cr.left,y, NULL);
        LineTo (hDC,cr.right,y);
        }
      MoveToEx (hDC,cr.left,cr.bottom - 1, NULL);
      LineTo (hDC,cr.right,cr.bottom - 1);

      for (i = 0 ; i < 7 ; i++) {
        x = int (dx * double (i) + 0.5) ;
        MoveToEx (hDC,x,cr.top, NULL);
        LineTo (hDC,x,cr.bottom);
        }
      MoveToEx (hDC,cr.right - 1,cr.top, NULL);
      LineTo (hDC,cr.right - 1,cr.bottom);

      // Zeichnen der Wochentags - Abkuerzungen
      TEXTMETRIC tm;
      GetTextMetrics (hDC,&tm);
      x = int (dx / 2.0 + 0.5) ;
      SetTextAlign (hDC,TA_BASELINE | TA_CENTER) ;
      for (i = 0 ; i < 7 ; i++) {
        y = int (dy * double (i) + dy / 2.0 + double (tm.tmAscent) / 2.0 + 0.5) ;
        char txt[30];
        LoadString (hLibInst,SHORTDAY + i,txt,sizeof(txt));
        TextOut (hDC,x,y,txt,lstrlen(txt));
        }

      // Den Vater nach genaueren Informationen ueber das Monat fragen
      LONG mi = GetMInfo (hWnd);

      // LOWORD(mi) ... Wochentag des ersten (0 - Montag, ... 6 - Sonntag)
      // HIWORD(mi) ... Ende des Monats (28 - 31)

      // Einzeichnen der Tage
      COLORREF sColor;
      DWORD oldColor;
      for (i = 0 ; i < int (HIWORD(mi)) ; i++) {
        int posy = (i + LOWORD(mi)) % 7 ;
        int posx = (i + LOWORD(mi)) / 7 + 1 ;
        char outtxt[10];
        wsprintf (outtxt,"%d",i+1);

        // Selektion des Tages, wenn noetig
        if (IsDayDisabled (hWnd,i)) {

          int cx, cy;
#ifdef WIN32
          SIZE size;
          GetTextExtentPoint32 (hDC,outtxt,lstrlen (outtxt),&size);
          cx = size.cx;
          cy = size.cy;
#else
          DWORD ext = GetTextExtent (hDC,outtxt,lstrlen (outtxt));
          cx = LOWORD(ext);
          cy = HIWORD(ext);
#endif

          x = int (dx * double (posx) + dx / 2.0 - double (cx) / 2.0 + 0.5) ;
          y = int (dy * double (posy) + dy / 2.0 - double (cy) / 2.0 + 0.5) ;
          GrayString (hDC,(HBRUSH)GetStockObject(GRAY_BRUSH),NULL,(DWORD) (LPSTR) outtxt,
                              lstrlen (outtxt),x,y,cx,cy);
          }
        else {
          x = int (dx * double (posx) + dx / 2.0 + 0.5) ;
          y = int (dy * double (posy) + dy / 2.0 + double (tm.tmAscent) / 2.0 + 0.5) ;

          BOOL selected = IsDaySelected (hWnd,i,&sColor);
          if (selected)
            oldColor = SetTextColor (hDC,sColor);
            
          TextOut (hDC,x,y,outtxt,lstrlen(outtxt));

          if (selected)
            SetTextColor (hDC,oldColor);
          }
        }

      // fertig gezeichnet
      EndPaint (hWnd,&ps);
      }
      break;

    case CLR_DISABLEITEM :
      // Ein Tag soll selektiert werden (in wP steht welcher)
      if (!IsDayDisabled (hWnd,wP)) {
        InsertDay (hWnd,wP,RGB(0,0,0),TRUE);
        }
      break ;

    case CLR_SELDAY :
      // Ein Tag soll selektiert werden (in wP steht welcher)
      // in lp steht die Farbe
      if (!IsDaySelected (hWnd,wP)) {
        InsertDay (hWnd,wP,lP,FALSE);
        if (DoRedraw (hWnd)) {
          HDC hDC = GetDC (hWnd);
          SelectDay (hDC,hWnd,wP,lP);
          ReleaseDC (hWnd,hDC);
          }
        }
      break ;

    case CLR_DESELDAY :
      // Ein Tag soll deselktiert werden (in wP steht welcher)
      if (IsDaySelected (hWnd,wP)) {
        DeleteDay (hWnd,wP);
        if (DoRedraw (hWnd)) {
          HDC hDC = GetDC (hWnd);
          SelectDay (hDC,hWnd,wP,RGB(0,0,0));
          ReleaseDC (hWnd,hDC);
          }
        }
      break ;

    case CLR_RESET :
      // Alle selektierten Daten loeschen
      ResetSelDays (hWnd);
      // Komplettes Neuzeichen veranlassen
      InvalidateRect (hWnd,NULL,TRUE);
      break ;

    case WM_LBUTTONDOWN :
      // Tag umrahmen
      Day = CheckDay (hWnd,LOWORD(lP),HIWORD(lP));
      if (Day >= 0) {
        HDC hDC = GetDC (hWnd);
        SetDayFocus (hDC,hWnd,Day,TRUE);
        ReleaseDC (hWnd,hDC);
        }
      SetActSelected (hWnd,Day);
      break ;

    case WM_MOUSEMOVE :
      if (wP & MK_LBUTTON) {
        Day = CheckDay (hWnd,LOWORD(lP),HIWORD(lP));
        int oldDay = GetActSelected (hWnd);
        if (Day != oldDay) {
          HDC hDC = GetDC (hWnd);
          if (oldDay >= 0) SetDayFocus (hDC,hWnd,oldDay,FALSE);
          if (Day >= 0) SetDayFocus (hDC,hWnd,Day,TRUE);
          SetActSelected (hWnd,Day);
          ReleaseDC (hWnd,hDC);
          }
        }
      break ;

    case WM_LBUTTONUP :
      {
      // Neue Selektion weitermelden
      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, hWnd, CLR_SELCHANGE);

      Day = GetActSelected (hWnd);
      if (Day >= 0) {
        HDC hDC = GetDC (hWnd);
        SetDayFocus (hDC,hWnd,Day,FALSE);
        SetActSelected (hWnd,-1);

#ifdef WIN32
        WPARAM wId = GetWindowLong (hWnd, GWL_ID);
#else
        WPARAM wId = GetWindowWord (hWnd, GWW_ID);
#endif

        SendMessage (GetParent(hWnd),
                     WM_COMMAND,
                     wId,
                     HILOCHUNKPARAM (hilo)
                    );
/*
        SendMessage (GetParent (hWnd),WM_COMMAND,GetWindowWord (hWnd,GWW_ID),
                        MAKELONG (hWnd,CLR_SELCHANGE));
*/
        ReleaseDC (hWnd,hDC);
        }
      }
      break ;

    case WM_LBUTTONDBLCLK :
      Day = CheckDay (hWnd,LOWORD(lP),HIWORD(lP));
      SetActSelected (hWnd,Day);
      if (Day >= 0) {

        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, hWnd, CLR_DBLCLK);

        WPARAM wId;
#ifdef WIN32
        wId = GetWindowLong (hWnd, GWL_ID);
#else
        wId = GetWindowWord (hWnd, GWW_ID);
#endif

        SendMessage (GetParent(hWnd),
                     WM_COMMAND,
                     wId,
                     HILOCHUNKPARAM (hilo)
                    );
/*
        SendMessage (GetParent (hWnd),WM_COMMAND,GetWindowWord (hWnd,GWW_ID),
                        MAKELONG (hWnd,CLR_DBLCLK));
*/
        }
      break ;

    case CLR_GETCURSEL :
      RetVal = GetLastSelected (hWnd);
      break ;

    case WM_SETREDRAW :
      SetRedrawPar(hWnd,wP);
      break ;

    case WM_DESTROY :
      // Fensterdaten wieder freigeben
      ResetSelDays (hWnd);
      break ;

    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal;
  }

struct hbuttondata {
  DWORD TxtColor;
  WORD Timer;
  WORD TimEvents;
  BOOL State[2];
  char WText[1];
  };

/*
**      
**      Implementierung eines Pfeilknopfes
**      In den Extra - Bytes ist ein GlobalHandle auf hbuttondata
**      abgelegt.
**
**      Abhaengig vom Style werden verschiedene Knoepfe gezeichnet
**              (siehe obige defines)
**
*/

RECT *GetButtonRect (HWND hWnd,int Button)
  {
  static RECT r;
  GetClientRect (hWnd,&r);
  if (Button == 0)
    r.right = r.bottom ;
  else
    r.left = r.right - r.bottom ;
  return &r ;
  }

void PressButton (HWND hWnd,int Button)
  {
  // Knopf einschalten
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  hbuttondata FAR *bd = (hbuttondata FAR *) GlobalLock (hGmem);
  if (!bd->State[Button]) {
    bd->State[Button] = TRUE ;
    InvalidateRect (hWnd,GetButtonRect(hWnd,Button),FALSE);
    bd->TimEvents = 20;    // 1 Sekunde warten bis zur naechsten Meldung
    bd->Timer = SetTimer (hWnd,1,50,NULL);
    int msg = (Button) ? HBT_TRACKRIGHT : HBT_TRACKLEFT ;

    HILOCHUNK hilo;
    MAKECHUNKsc (hilo, hWnd, msg);
    WPARAM wId;

#ifdef WIN32
    wId = GetWindowLong (hWnd, GWL_ID);
#else
    wId = GetWindowWord (hWnd, GWW_ID);
#endif

    SendMessage (GetParent(hWnd),
                 WM_COMMAND,
                 wId,
                 HILOCHUNKPARAM (hilo)
                );
/*
    SendMessage (GetParent (hWnd),WM_COMMAND,GetWindowWord (hWnd,GWW_ID),
                    MAKELONG (hWnd,msg));
*/
    }
  GlobalUnlock (hGmem);
  }

void ReleaseButton (HWND hWnd)
  {
  // Knopf ausschalten
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  hbuttondata FAR *bd = (hbuttondata FAR *) GlobalLock (hGmem);
  for (int i = 0 ; i < 2 ; i++) {
    if (bd->State[i]) {
      bd->State[i] = FALSE ;
      InvalidateRect (hWnd,GetButtonRect(hWnd,i),FALSE);
      if (bd->Timer) KillTimer (hWnd,1), bd->Timer = 0 ;
      }
    GlobalUnlock (hGmem);
    }
  }

int CheckMouse (HWND hWnd,int x,int y)
  {
  RECT r;
  GetClientRect (hWnd,&r);
  RECT r1,r2;
  lmemcpy (&r1,&r,sizeof(RECT));
  lmemcpy (&r2,&r,sizeof(RECT));
  r1.right = r.bottom ;
  r2.left = r.right - r.bottom ;
  int res ;
  POINT pt;
  pt.x = x , pt.y = y;
  if (PtInRect (&r1,pt))      res = 0 ;
  else if (PtInRect (&r2,pt)) res = 1 ;
  else                        res = -1;
  return res ;
  }

void CheckTimer (HWND hWnd)
  {
#ifdef WIN32
  GLOBALHANDLE hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
  GLOBALHANDLE hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

  hbuttondata FAR *bd = (hbuttondata FAR *) GlobalLock (hGmem);
  // Zuerst einmal ueberpruefen, ob Mouse noch im Fenster ist
  POINT ptmouse;
  GetCursorPos (&ptmouse);
  ScreenToClient (hWnd,&ptmouse);
  int Button = CheckMouse (hWnd,ptmouse.x,ptmouse.y);
  if (Button >= 0) {
    bd->TimEvents -- ;
    if (bd->TimEvents == 0) {
      bd->TimEvents = 5 ;       // Nur mehr 250 ms warten
      int msg = (Button) ? HBT_TRACKRIGHT : HBT_TRACKLEFT ;

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, hWnd, msg);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (hWnd, GWL_ID);
#else
      wId = GetWindowWord (hWnd, GWW_ID);
#endif

      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
/*
      SendMessage (GetParent (hWnd),WM_COMMAND,GetWindowWord (hWnd,GWW_ID),
                    MAKELONG (hWnd,msg));
*/
      }
    }
  else {
    // Knopf ausschalten
    ReleaseButton (hWnd);
    }
  
  GlobalUnlock (hGmem);
  }

void PaintBtBack (HDC hDC,LPRECT cr,BOOL state)
  {
  // Zeichnen eines Grauen Hintergrundes
  HPEN hPen = (HPEN)SelectObject (hDC,GetStockObject (BLACK_PEN));
  HBRUSH hBrush = (HBRUSH)SelectObject (hDC,GetStockObject (LTGRAY_BRUSH));

  Rectangle (hDC,cr->left,cr->top,cr->right,cr->bottom);
  // Zeichnen des Schatten
  if (state) {
    SelectObject (hDC,hPen);
    LOGBRUSH br;
    GetObject (GetStockObject (GRAY_BRUSH),sizeof(br),LPSTR (&br));
    hPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,0,br.lbColor));
    MoveToEx (hDC,cr->left+1,cr->top+1, NULL);
    LineTo (hDC,cr->right - 2,cr->top+1);

    MoveToEx (hDC,cr->left+1,cr->top+1, NULL);
    LineTo (hDC,cr->left+1,cr->bottom - 2);

    DeleteObject (SelectObject (hDC,hPen));
    }
  else {
    SelectObject (hDC,GetStockObject(WHITE_PEN));
    MoveToEx (hDC,cr->left+1,cr->top+1, NULL);
    LineTo (hDC,cr->right - 2,cr->top+1);
    MoveToEx (hDC,cr->left+1,cr->top+2, NULL);
    LineTo (hDC,cr->right - 3,cr->top+2);
    MoveToEx (hDC,cr->left+1,cr->top+1, NULL);
    LineTo (hDC,cr->left+1,cr->bottom-2);
    MoveToEx (hDC,cr->left+2,cr->top+2, NULL);
    LineTo (hDC,cr->left+2,cr->bottom-3);

    SelectObject (hDC,hPen);
    LOGBRUSH br;
    GetObject (GetStockObject (GRAY_BRUSH),sizeof(br),LPSTR (&br));
    hPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,0,br.lbColor));
    MoveToEx (hDC,cr->left+1,cr->bottom-2, NULL);
    LineTo (hDC,cr->right-1,cr->bottom-2);
    MoveToEx (hDC,cr->left+2,cr->bottom-3, NULL);
    LineTo (hDC,cr->right-2,cr->bottom-3);
    MoveToEx (hDC,cr->right-2,cr->top+1, NULL);
    LineTo (hDC,cr->right-2,cr->bottom-1);
    MoveToEx (hDC,cr->right-3,cr->top+2, NULL);
    LineTo (hDC,cr->right-3,cr->bottom-2);

    DeleteObject (SelectObject (hDC,hPen));
    }
  SelectObject (hDC,hBrush);
  }

void PaintArrow (HDC hDC,LPRECT cr,BOOL state,int dir)
  {
  int xc = (cr->left + cr->right) / 2 - 1 ;
  int yc = (cr->top + cr->bottom) / 2 - 1 ;
  if (state) xc ++ , yc ++ ;
  xc += 2 * dir ;
  HPEN hPen = (HPEN)SelectObject (hDC,GetStockObject (BLACK_PEN));
  for (int i = 0 ; i < 5 ; i++) {
    MoveToEx (hDC,xc - i * dir,yc - i, NULL);
    LineTo (hDC,xc - i * dir,yc + i + 1);
    }
  SelectObject (hDC,hPen);
  }

DLLExport LONG _export CALLBACK hButtonWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  GLOBALHANDLE hGmem;
  hbuttondata FAR *bd;
  int Button;
  RECT r;

  switch (msg) {
    case WM_CREATE :
      // Welcher Knopf ist gemeint ?
      hGmem = GlobalAlloc (GHND,sizeof (hbuttondata));
      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      GlobalUnlock (hGmem);
      
      // fertig
#ifdef WIN32
      SetWindowLong (hWnd,GWL_HWINFO,LONG(hGmem));
#else
      SetWindowWord (hWnd,GWW_HWINFO,hGmem);
#endif

      break ;

    case WM_PAINT :
      {
#ifdef WIN32
      hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
      hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd,&ps);
      RECT cr;
      GetClientRect (hWnd,&cr);
      int height = cr.bottom;
      cr.right = height ;

      // Zeichnen des linken Knopfes
      PaintBtBack (hDC,&cr,bd->State[0]);
      PaintArrow (hDC,&cr,bd->State[0],-1);

      // Zeichnen des rechten Knopfes
      GetClientRect (hWnd,&cr);
      cr.left = cr.right - height ;
      PaintBtBack (hDC,&cr,bd->State[1]);
      PaintArrow (hDC,&cr,bd->State[1],1);

      // Zeichnen des Textes
      GetClientRect (hWnd,&cr);
      cr.left = height - 1;
      cr.right -= height - 1;
      HPEN hPen = (HPEN)SelectObject (hDC,GetStockObject(BLACK_PEN));
      HBRUSH hBrush = (HBRUSH)SelectObject (hDC,GetStockObject(WHITE_BRUSH));

      Rectangle (hDC,cr.left,cr.top,cr.right,cr.bottom);
      SetTextAlign (hDC,TA_BASELINE | TA_CENTER);
      SetTextColor (hDC,bd->TxtColor);
      TEXTMETRIC tm;
      GetTextMetrics (hDC,&tm);
      TextOut (hDC,(cr.left + cr.right) / 2,
                       (cr.top + cr.bottom) / 2 + tm.tmAscent / 2,
                       bd->WText,lstrlen(bd->WText));

      GlobalUnlock (hGmem);

      SelectObject (hDC,hPen);
      SelectObject (hDC,hBrush);
      EndPaint (hWnd,&ps);
      }
      break ;

    case WM_LBUTTONDOWN :
      Button = CheckMouse (hWnd,LOWORD(lP),HIWORD(lP));
      if (Button >= 0)
        PressButton (hWnd,Button);
      break ;

    case WM_LBUTTONUP :
      ReleaseButton (hWnd);
      break ;

    case WM_MOUSEMOVE :
      if (wP & MK_LBUTTON) {
        Button = CheckMouse (hWnd,LOWORD(lP),HIWORD(lP));
        if (Button >= 0)
          PressButton (hWnd,Button);
        }
      break ;

    case WM_TIMER :
      CheckTimer (hWnd);
      break ;

    case WM_SETTEXT :
      {
#ifdef WIN32
      hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
      hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

      int len = lstrlen (LPSTR (lP));
      hGmem = GlobalReAlloc (hGmem,sizeof (hbuttondata) + len,GMEM_MOVEABLE);
      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      lstrcpy (bd->WText,LPSTR (lP));
      GlobalUnlock (hGmem);
      // Invalid setzen des Bereiches
      GetClientRect (hWnd,&r);
      r.left += r.bottom ;
      r.right -= r.bottom ;
      InvalidateRect (hWnd,&r,FALSE);
      // fertig
#ifdef WIN32
      SetWindowLong (hWnd,GWL_HWINFO,LONG(hGmem));
#else
      SetWindowWord (hWnd,GWW_HWINFO,hGmem);
#endif

      }
      break ;

    case WM_GETTEXT :
#ifdef WIN32
      hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
      hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      lstrncpy (LPSTR(lP),bd->WText,wP);
      GlobalUnlock (hGmem);
      break ;

    case HBT_SETTEXTCOLOR :
#ifdef WIN32
      hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
      hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      bd->TxtColor = lP ;
      GlobalUnlock (hGmem);
      break ;

    case WM_DESTROY :
      // Bitmaps und Daten wieder loeschen
#ifdef WIN32
      hGmem = (GLOBALHANDLE)GetWindowLong (hWnd,GWL_HWINFO);
#else
      hGmem = GetWindowWord (hWnd,GWW_HWINFO);
#endif

      bd = (hbuttondata FAR *) GlobalLock (hGmem);
      if (bd->Timer)  KillTimer (hWnd,1), bd->Timer = 0 ;
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      break ;

    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      
    }
  return RetVal;
  }

/*-----< Registrierung der Custom - Control Elemente >--------*/
DLLExport void _export WINAPI RegisterCustomControl (void)
  {
  static BOOL IsRegistered;
  if (!IsRegistered) {
    WNDCLASS wndclass;
    /*----< Registrierung der Klasse CLNDR >------*/
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_GLOBALCLASS ;
    wndclass.lpfnWndProc = WNDPROC (clndrWndProc);
    wndclass.cbClsExtra = 0 ;
    // VORSICHT!!!! Wird da etwas hinzugefuegt, dann stimmen die Offsets
    // nicht mehr (wegen 16 un 32 Bit)!!!!
    wndclass.cbWndExtra = sizeof (GLOBALHANDLE) ;
    wndclass.hInstance = hLibInst ;
    wndclass.hIcon = NULL;
    wndclass.hCursor = LoadCursor (NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wndclass.lpszMenuName = NULL ;
    wndclass.lpszClassName = "clndr" ;

    RegisterClass (&wndclass);

    /*----< Registrierung der Klasse HButton >------*/
    wndclass.lpfnWndProc = WNDPROC (hButtonWndProc);
    wndclass.cbWndExtra = sizeof (GLOBALHANDLE) ;
    wndclass.lpszClassName = "hbutton" ;

    RegisterClass (&wndclass);
    IsRegistered = TRUE ;
    }

  // Elemente waeren alle definiert
  }

