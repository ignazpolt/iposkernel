////////////////////////////////////////////////////////////////////
//  Zur Verfuegung Stellen eines Fenstertyps, das mit Hilfe von
//  cField eine Formatierte Einagebe erlaubt
//
//  $Header:   P:/marille/clinicum/dmwapi/rev/wordwin.cpv   1.51   31 Mar 1999 14:56:44   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/wordwin.cpv  $
// 
//    Rev 1.51   31 Mar 1999 14:56:44   Gerhold
// htmlhelp
// 
//    Rev 1.50   09 Oct 1998 18:02:10   Gerhold
// Farben in Strings
// 
//    Rev 1.49   09 Aug 1998 22:36:02   Hannes
// Verbesserungen Kontextmenue
// 
//    Rev 1.48   30 Jul 1998 11:13:40   Gerhold
// WinHelp angepasst fuer HELP_FINDER
// 
//    Rev 1.47   12 Jan 1998 18:14:30   Hannes
// WMC_GETTEXT
// 
//    Rev 1.46   07 Jan 1998 08:05:48   Hannes
// 
//    Rev 1.45   12 Dec 1997 14:54:00   Gerhold
// Fehler in 16Bit (GetWindowWord(GWW_STYLE) ... gibt's nicht)
// 
//    Rev 1.44   28 Nov 1997 17:49:10   Hannes
// Fontabmessung in Dialogboxen auch fuer Drucker!
// 
//    Rev 1.43   19 Nov 1997 18:49:32   Gerhold
// Scrollbar bei mehrzeiligen Feldern
// 
//    Rev 1.42   10 Nov 1997 20:19:18   Hannes
// Einzeilige ToolEdits
// 
//    Rev 1.41   14 Aug 1997 22:01:30   Hannes
// Statt WM_KEYDOWN -> WW_KEYDOWN (?!?!?)
// 
//    Rev 1.40   22 Apr 1997 12:09:38   Hannes
// 
//    Rev 1.39   10 Apr 1997 11:41:30   Hannes
// WWNextExplizit mit Angabe des Flags
// 
//    Rev 1.38   08 Apr 1997 17:44:28   gerhold
// WinHelp (...GetHelpFile() ...)
// 
//    Rev 1.37   21 Mar 1997 11:27:50   Hannes
// weiterleiten von WW_KEYDOWN
// 
//    Rev 1.36   03 Mar 1997 11:46:22   Hannes
// WWSetNextExplicit
// 
//    Rev 1.35   28 Feb 1997 14:27:22   Hannes
// WWSetCaretTo
// 
//    Rev 1.34   19 Feb 1997 12:10:48   Hannes
// InsertStringAtCaret
// 
//    Rev 1.33   28 Sep 1996 15:51:24   GERHOLD
// WM_COMMAND ... Winhelp eingebaut
// 
//    Rev 1.32   18 Sep 1996 20:48:30   HANNES
// 
//    Rev 1.31   05 Sep 1996 14:02:18   GERHOLD
// WW_IsFieldSelected ... Sind Zeichen im Text selektiert?
// 
//    Rev 1.30   16 Jun 1996 18:58:10   martin
// WWClipBoard (Aufruf der Clipboard Funktionen fuer ToolEdit)
// 
//    Rev 1.29   22 May 1996 17:55:44   MARTIN
// Kommando zurueck !!!!
// 
//    Rev 1.28   22 May 1996 09:51:14   GERHOLD
// MAKECHUNKsc ... LO-Value und HI-Value waren vertauscht!
// 
//    Rev 1.27   11 Apr 1996 09:01:34   GERHOLD
// _export WWSetOutColor  =>  cField->SetOutColor
// 
//    Rev 1.26   24 Mar 1996 12:10:58   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.25   22 Mar 1996 12:13:22   HANNES
// Aenderungen Hannes
// 
//    Rev 1.24   04 Feb 1996 15:42:30   HANNES
// Trennung COMPILE - DDSMEM
// 
//    Rev 1.23   02 Feb 1996 10:46:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.22   10 Jan 1996 18:16:12   HANNES
// FormatMaps
// 
//    Rev 1.21   02 Jan 1996 22:12:16   HANNES
// Formatierung von Feldern
// 
//    Rev 1.20   12 Dec 1995 17:31:20   GERHOLD
// Selektierte Eingabefelder die einen Knopf haben zeichnen den Text 
// mit Hintergrund COLOR_HIGHLIGHT und den Text mit COLOR_HIGHLIGHTTEXT
// 
//    Rev 1.19   12 Dec 1995 12:09:42   GERHOLD
// OnKillFocus hat als Parameter das Fensterhandle das den Focus bekommt 
// 
//    Rev 1.18   05 Dec 1995 14:02:20   GERHOLD
// WWGetMode ... liefert den Feldmodus fuer ein Eingabefeld
// 
//    Rev 1.17   11 Sep 1995 20:23:38   MARTIN
// OnSetFocusProc
// 
//    Rev 1.16   27 Aug 1995 12:47:34   HANNES
// Sortierung im Editor
// 
//    Rev 1.15   20 May 1995 16:19:34   HANNES
// WW_SETMAXTEXTLEN
// 
//    Rev 1.14   02 May 1995 12:48:42   HANNES
// 
//    Rev 1.13   05 Apr 1995 16:43:00   GERHOLD
// 
//    Rev 1.12   31 Mar 1995 13:10:38   HANNES
//  
// 
//    Rev 1.11   15 Dec 1994 18:23:24   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.10   15 Dec 1994 14:20:04   GERHOLD
// 
//    Rev 1.9   28 Nov 1994 20:04:02   GERHOLD
// > Selektierte Zeichen werden bei Eingabe eines Zeichens geloescht.
// 
//    Rev 1.8   31 Oct 1994 09:48:02   GERHOLD
// WWSetBuddy eingefuegt (fuer ComboButton und UpDown).
// WM_LBUTTONDOWN prueft im SenMessage auf EditCallBack (fuer RESTOOL).
// 
//    Rev 1.7   25 Oct 1994 12:04:42   GERHOLD
// Editierfelder die Disabled sind, werden grau dargestellt
// 
//    Rev 1.6   20 Oct 1994 17:49:32   GERHOLD
// Clipboard-Handling
// 
//    Rev 1.5   13 Oct 1994 18:21:48   GERHOLD
// Mausaufrufe fuer cField erweitert
// im cField-Konstruktor von TRANSPARENT auf OPAQUE
// 
//    Rev 1.4   13 Oct 1994 12:36:40   GERHOLD
// Rechteck zeichnen in WM_PAINT raus!
// 
//    Rev 1.3   02 Oct 1994 16:58:10   HANNES
// 
//    Rev 1.2   24 Aug 1994 19:43:06   HANNES
// Fehlerhafter Invalidate
// 
//    Rev 1.1   09 Aug 1994 13:23:40   GERHOLD
// Doppelclick fuer Edit-Elemente in Restool
// 
//    Rev 1.0   24 Jun 1994 16:49:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.11   14 Apr 1994 16:57:46   HANNES
// Overwritemodus in (Dialog)Editfeldern
// 
//    Rev 1.10   14 Feb 1994 19:50:38   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.9   20 Jan 1994 23:56:04   HANNES
// WW_RBUTTON
// 
//    Rev 1.8   13 Jan 1994 16:01:08   HANNES
// WWM_SETCARETTOEND
// 
//    Rev 1.7   18 Oct 1993 19:46:44   HANNES
// WWSetFormat
// 
//    Rev 1.6   06 Oct 1993 09:55:28   HANNES
// Einsatz in normalen Dialogboxen
// 
//    Rev 1.5   22 Sep 1993 10:18:12   HANNES
// Version nach St. Poelten
// 
//    Rev 1.4   24 Aug 1993 10:36:38   HANNES
// 
//    Rev 1.3   18 Aug 1993 10:49:14   HANNES
// Verschiedene Verbesserungen
// 
//    Rev 1.2   03 Jun 1993 11:00:44   HANNES
// Groesse des Fensters herabgesetzt
// 
//    Rev 1.1   02 Jun 1993 19:38:06   HANNES
// WWCreateWinEx...
// 
//    Rev 1.0   12 May 1993 17:23:52   HANNES
// Initial revision.
//
////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>

#include <htmlhelp.h>

#include "dds32.h"
#include "globmem.h"
#include "font.hpp"
#include "cfield.hpp"
#include "wordwin.hpp"
#include "dds.h"
#include "dds.hpp"
#include "printer.hpp"
#include "ddsmsg.h"

extern HINSTANCE hLibInst;
class WordWin : public wobj {
 public :
  HWND hMyWnd;
  cField FAR *field;
  int xp,yp;
  BOOL doOverwrite;
  int MaxAnzChars;
  int sAnzLines;
  WordWin FAR *Next;

  WordWin (HWND hWnd,int format,BOOL password,int AnzLines,int Width,int mAnzChars,int sa);
  void InitScroll ()
    {
    BOOL   bVScroll;
    bVScroll = BOOL(GetWindowLong (hMyWnd, GWL_STYLE) & WS_VSCROLL);

    if (bVScroll) {
      if (field->GetAnzLines() <= sAnzLines) {
        EnableScrollBar (hMyWnd, SB_VERT, ESB_DISABLE_BOTH);
        }
      else {
        EnableScrollBar (hMyWnd, SB_VERT, ESB_ENABLE_BOTH);
        SetScrollRange (hMyWnd, SB_VERT, 0, field->GetAnzLines() - 1,TRUE);
        SetScrollPos (hMyWnd, SB_VERT, field->GetActLine(),TRUE);
        }
      }
    }
  ~WordWin ();
  };
typedef WordWin FAR *LPWORDWIN;

static class WordWin FAR *wwfirst;
static int x0pos,y0pos;
static WordWin FAR *FindWW (HWND hWnd)
  {
  for (WordWin FAR *res = wwfirst ; res != NULL ; res = res->Next) {
    if (res->hMyWnd == hWnd) break ;
    }
  return res;
  }

extern void ExtSetTwipsMap (HDC hDC,double scale,int xp,int yp);

void Getx0y0Pos ()
  {
  static BOOL x0y0Poscalced;
  if (!x0y0Poscalced) {
    HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
    ExtSetTwipsMap (hDC,1.0,0,0);
    POINT pt[2];
    pt[0].x = pt[0].y = 0;
    pt[1].x = pt[1].y = 2;
    DPtoLP(hDC,pt,2);
    x0pos = pt[1].x + 1;
    y0pos = pt[1].y + 1;
    DeleteDC (hDC);
    x0y0Poscalced = TRUE ;
    }
  }

int xTOLP (int width)
  {
  HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
  ExtSetTwipsMap (hDC,1.0,0,0);
  POINT pt[2];
  pt[0].x = pt[0].y = 0;
  pt[1].x = width - 4;
  pt[1].y = 0;
  DPtoLP(hDC,pt,2);
  DeleteDC (hDC);
  return pt[1].x;
  }

int toDP (HWND hWnd,int x)
  {
  HDC hDC = GetDC (hWnd);
  ExtSetTwipsMap (hDC,1.0,0,0);
  POINT pt[2];
  pt[0].x = pt[1].y = 0 ;
  pt[0].x = x ; pt[1].y = 0 ;
  LPtoDP (hDC,pt,2);
  int res = pt[1].x - pt[0].x ;
  ReleaseDC (hWnd,hDC);
  return res;
  }

Printer *GetStaticPrinter()
  {
  static Printer FAR *sp;
  if (sp == NULL)
    sp = GetPrinter(TRUE);
  return sp;
  }

void WINAPI WWCallBack (int Cmd,LPVOID Info,LPVOID MyInfo)
  {
  switch (Cmd) {
    case CALLBACKCMD_SAVESTR    :
      {
      // EN_CHANGE Meldung weiterleiten
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, EN_CHANGE, ww->hMyWnd);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      SendMessage (GetParent(ww->hMyWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );

      ww->InitScroll ();
      }
      break ;
    case CALLBACKCMD_NEEDSCROLL :
      {
      // xp muss veraendert werden
      LPPOINT pt = LPPOINT(Info);
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      if (ww->sAnzLines > 1) pt->x = 0 ;
      if ((pt->x != 0) || (pt->y != 0)) {
        int xold = ww->xp ;
        int yold = ww->yp ;
        ww->xp -= pt->x;
        ww->yp -= pt->y;
        ww->xp = min (ww->xp,0);
        ww->yp = min (ww->yp,0);
        if ((ww->xp != xold) || (ww->yp != yold)) {
          ww->field->SetVOrg (ww->xp,ww->yp,0);
          InvalidateRect (ww->hMyWnd,NULL,TRUE);
          }
        ww->InitScroll ();
        }
      }
      break ;
    case CALLBACKCMD_ISCHARALLOWED :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      TCI FAR *t = (TCI FAR *) Info;

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_CHAR, t->wP);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      LRESULT res =SendMessage (GetParent(ww->hMyWnd),
                                WM_COMMAND,
                                wId,
                                HILOCHUNKPARAM (hilo)
                               );
      if (res != 0) {
        t->wP = 0;  // Nicht bearbeiten
        t->dontBeep = TRUE ;
        }
      }
      break ;
    case CALLBACKCMD_TESTKEYDOWN :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      TCI FAR *t = (TCI FAR *) Info;

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_KEYDOWN, t->wP);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      LRESULT res =SendMessage (GetParent(ww->hMyWnd),
                                WM_COMMAND,
                                wId,
                                HILOCHUNKPARAM (hilo)
                               );
      if (res != 0) {
        t->wP = 0;  // Nicht bearbeiten
        t->dontBeep = TRUE ;
        }
      }
      break ;
    case CALLBACKCMD_CARETPOSCHG :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_CARETPOSCHG, ww->hMyWnd);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      SendMessage (GetParent(ww->hMyWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
      }
      break ;
    case CALLBACKCMD_SHWORKON :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_WORKON, ww->hMyWnd);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      SendMessage (GetParent(ww->hMyWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
/*
      SendMessage (GetParent (ww->hMyWnd),
                   WM_COMMAND,
                   GetWindowWord (ww->hMyWnd,GWW_ID),
                   MAKELONG(ww->hMyWnd,WW_WORKON)
                  );
*/
      InvalidateRect (ww->hMyWnd,NULL,TRUE);
      }
      break ;
    case CALLBACKCMD_GETFONTREFWND :
      {
      FontRefWndBuffer FAR *f = (FontRefWndBuffer FAR *) Info;
      f->IsDone = TRUE ;
      f->RefWnd = 0;
      }
      break ;
    case CALLBACKCMD_GETPRDC :
      *((HDC FAR *) Info) = GetStaticPrinter ()->PrinterDC();
      break ;
    case CALLBACKCMD_RELEASEPRDC :
      GetStaticPrinter ()->ReleasePrDC ();
      break ;
      break ;
    case CALLBACKCMD_DOOVERWRITE :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      BOOL FAR *f = (BOOL FAR *) Info;
      *f = ww->doOverwrite;
      }
      break ;
    case CALLBACKCMD_GETMAXANZCHARS :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      int FAR *f = (BOOL FAR *) Info;
      *f = ww->MaxAnzChars ;
      }
      break ;
    case CALLBACKCMD_ONSETFOCUS  :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_ONSETFOCUS, ww->hMyWnd);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      SendMessage (GetParent(ww->hMyWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
/*
      SendMessage (GetParent (ww->hMyWnd),
                              WM_COMMAND,
                              GetWindowWord (ww->hMyWnd,GWW_ID),
                              MAKELONG(ww->hMyWnd,WW_ONSETFOCUS)
                  );
*/
      }
      break ;

    case CALLBACKCMD_ONKILLFOCUS  :
      {
      WordWin FAR *ww = *((LPWORDWIN FAR *) MyInfo);
      WPARAM FAR *wP = (WPARAM FAR *)Info;

      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_ONKILLFOCUS, *wP);

      WPARAM wId;
#ifdef WIN32
      wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
      wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

      SendMessage (GetParent(ww->hMyWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
/*
      SendMessage (GetParent (ww->hMyWnd),
                              WM_COMMAND,
                              GetWindowWord (ww->hMyWnd,GWW_ID),
                              MAKELONG(*wP, WW_ONKILLFOCUS)
                  );
*/
      }
      break ;
    }
  }

WordWin::WordWin (HWND hWnd,int format,BOOL password,int AnzLines,int Width,int mAnzChars,int sa)
  {
  xp = 0 ;
  // Listenverkettung herstellen
  Next = wwfirst;
  wwfirst = this ;
  hMyWnd = hWnd;
  MaxAnzChars = mAnzChars ;
  sAnzLines = sa;

  // Berechnen des natuerlichen Ursprungs
  Getx0y0Pos();

  // Aufbau des Feldes
  if (password)
    field = new pField(OPAQUE,format,x0pos,y0pos,Width,AnzLines,TRUE);
  else
    field = new cField(OPAQUE,format,x0pos,y0pos,Width,AnzLines,TRUE);
  WordWin FAR *ww = this;
  field->InstallCallBack (WWCallBack,&ww,sizeof(ww));
  field->SetWindow (hWnd);
  field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  field->SetVOrg (0,0,0);
  if (AnzLines == 1)
    field->SetFieldMode (field->GetFieldMode () | FM_SINGLELINE);
  }

WordWin::~WordWin ()
  {
  delete field ;
  field = NULL ;
  WordWin FAR *prev = NULL ;
  
  // Rausloeschen aus der Liste
  for ( WordWin FAR *ww = wwfirst ; ww != NULL ; ww = ww->Next ) {
    if (ww == this) {
      if (prev != NULL) prev->Next = Next ;
      else              wwfirst    = Next ;
      break ;
      }
    prev = ww;
    }
  }

static BOOL dontWMCREATE;
static BOOL bCaptured = FALSE;
WWPAINTCALLBACK pncall;
BOOL nextExplicit;
DLLExport void _export WINAPI WWNextExplicit (BOOL val)
  {
  nextExplicit = val ;
  }
DLLExport LONG _export CALLBACK WordWinProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;
  WordWin FAR *ww;
  switch (msg) {
    // Fensterspezifische Meldungen, die an das Feld weitergeleitet werden
    // koennen
    ///////////////////////////////////////////////////////////////////////
    case WM_CREATE :
      {
      LPCREATESTRUCT lpcs = LPCREATESTRUCT (lP);
      if (lpcs->style & WS_VSCROLL)
         EnableScrollBar (hWnd, SB_VERT, ESB_DISABLE_BOTH);

      if (!dontWMCREATE) {
        RECT r;
        GetClientRect (hWnd,&r);
        WordWin FAR *ww = new WordWin (hWnd,WWDEFFORMAT,FALSE,1,-1,-1,1);
        }
      }
      break ;
    case WM_ENABLE :
      InvalidateRect (hWnd, NULL, TRUE);
      break;
    case WM_KEYDOWN :
      if ((ww = FindWW(hWnd)) != NULL) {
        ww->field->OnKeyDown (wP,0);
        }
      break ;
    case WM_CHAR :
      if ((ww = FindWW(hWnd)) != NULL) {
        ww->field->OnChar (wP,0);
        }
      break ;
    case WM_LBUTTONDOWN :
      {
      if ((ww = FindWW(hWnd)) != NULL) {
        if (GetFocus () != hWnd) 
          SetFocus (hWnd); // ??

        POINT pt;
#ifdef WIN32
        LONG2POINT (lP, pt);
#else
        pt = MAKEPOINT(lP);
#endif
        ww->field->OnLButtonDown (wP, pt, 0);

        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, WW_LBUTTON, ww->hMyWnd);

        WPARAM wId;
#ifdef WIN32
        wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
        wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

        if (!SendMessage (GetParent(ww->hMyWnd),
                          WM_COMMAND,
                          wId,
                          HILOCHUNKPARAM (hilo)
                         )) {
/*
        if (!SendMessage (GetParent (ww->hMyWnd),
                         WM_COMMAND,
                         GetWindowWord (ww->hMyWnd,GWW_ID),
                         MAKELONG(ww->hMyWnd,WW_LBUTTON))) {
*/
          bCaptured = TRUE;
          SetCapture (hWnd);
          }
        }
      }
      break ;
    case WM_RBUTTONDOWN :
    case WM_RBUTTONUP :
      if ((ww = FindWW(hWnd)) != NULL) {
        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, (msg == WM_RBUTTONDOWN) ? WW_RBUTTONDOWN :
                                                     WW_RBUTTONUP, 
                           ww->hMyWnd);

        WPARAM wId;
#ifdef WIN32
        wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
        wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

        SendMessage (GetParent(ww->hMyWnd),
                     WM_COMMAND,
                     wId,
                     HILOCHUNKPARAM (hilo)
                    );
/*
        SendMessage (GetParent (ww->hMyWnd),
                     WM_COMMAND,
                     GetWindowWord (ww->hMyWnd,GWW_ID),
                     MAKELONG(ww->hMyWnd,(msg == WM_RBUTTONDOWN) ? 
                                  WW_RBUTTONDOWN : WW_RBUTTONUP)
                    );
*/
        }
      break ;
    case WM_MOUSEMOVE :
      if ((ww = FindWW(hWnd)) != NULL) {
        if (bCaptured) {

          POINT pt;
#ifdef WIN32
          LONG2POINT (lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif
          
          ww->field->OnMouseMove (wP, pt, 0);
          }
        }
      break ;
    case WM_LBUTTONUP :
      if ((ww = FindWW(hWnd)) != NULL) {

        POINT pt;
#ifdef WIN32
        LONG2POINT (lP, pt);
#else
        pt = MAKEPOINT(lP);
#endif

        ww->field->OnLButtonUp (wP, pt, 0);
        ReleaseCapture ();
        bCaptured = FALSE;
        }
      break;
    case WM_LBUTTONDBLCLK :
      if ((ww = FindWW(hWnd)) != NULL) {

        POINT pt;
#ifdef WIN32
        LONG2POINT (lP, pt);
#else
        pt = MAKEPOINT(lP);
#endif

        ww->field->OnLButtonDblClk (wP, pt, 0);

        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, WW_LBUTTONDBLCLK, ww->hMyWnd);

        WPARAM wId;
#ifdef WIN32
        wId = GetWindowLong (ww->hMyWnd, GWL_ID);
#else
        wId = GetWindowWord (ww->hMyWnd, GWW_ID);
#endif

        SendMessage (GetParent(ww->hMyWnd),
                     WM_COMMAND,
                     wId,
                     HILOCHUNKPARAM (hilo)
                    );
/*
        SendMessage (GetParent (ww->hMyWnd),
                     WM_COMMAND,
                     GetWindowWord (ww->hMyWnd,GWW_ID),
                     MAKELONG(ww->hMyWnd,WW_LBUTTONDBLCLK)
                    );
*/
        }
      break ;
    case WM_SETFOCUS :
      if ((ww = FindWW(hWnd)) != NULL) {
        ww->field->OnSetFocus (nextExplicit,0,WWGetSelect());
        nextExplicit = FALSE ;
        }
      break ;
    case WM_KILLFOCUS :
      if ((ww = FindWW(hWnd)) != NULL) {
        ww->field->OnKillFocus (wP,0);
        }
      break ;
    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd,&ps);

      BOOL bFieldWithButton = FALSE;
      if ((ww = FindWW(hWnd)) != NULL) {
        // Ist das Editfeld disabled, wird es dunkel gezeichnet
        if (!IsWindowEnabled(hWnd)/* && !ww->field->HasButton*/) {
          SetBkColor (hDC, GetSysColor(COLOR_BTNFACE));
          ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &ps.rcPaint, NULL, 0, NULL);
          }
        else 
        if ((GetFocus() == hWnd) && (ww->field->HasButton)) {
          bFieldWithButton = TRUE;
          SetBkColor (hDC, GetSysColor(COLOR_HIGHLIGHT));
          ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &ps.rcPaint, NULL, 0, NULL);
          }

        // Ein Feld mit Knopf hat den Focus => die Farbe des Textes aendern
        if (bFieldWithButton)
          ww->field->SetOutColor (GetSysColor(COLOR_HIGHLIGHTTEXT));
        ExtSetTwipsMap (hDC,1.0,ww->xp,ww->yp);
        ww->field->Paint (hDC,0,FALSE);

        // Ein Feld mit Knopf hat den Focus => die Farbe des Textes normal
        if (bFieldWithButton)
          ww->field->UseDefOutColor ();
        }
      if (pncall != NULL) {
        SetMapMode (hDC,MM_TEXT);
        SetViewportOrgEx (hDC,0,0, NULL);
        SetWindowOrgEx (hDC,0,0, NULL);
        (* pncall) (hWnd,hDC);
        }
      EndPaint (hWnd,&ps);
      }
      break ;
    case WM_DESTROY :
      if ((ww = FindWW(hWnd)) != NULL) {
        delete ww ;
        }
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;

    // Editspezifische Meldungen, die simuliert werden
    case WM_SETTEXT :
      if ((ww = FindWW(hWnd)) != NULL) {
        *(ww->field) = LPSTR (lP);
        InvalidateRect (hWnd,NULL,TRUE);
        ww->InitScroll ();
        }
      break ;

    case WMU_GETTEXT :
    case WM_GETTEXTLENGTH :
      if ((ww = FindWW(hWnd)) != NULL) {
        GLOBALHANDLE hGmem;
        *(ww->field) >> hGmem;
        LPSTR base = LPSTR(GlobalLock(hGmem));
        if (msg == WMU_GETTEXT)
          lstrncpy (LPSTR(lP),base,wP);
        else
          RetVal = lstrlen (base);
        GlobalUnlock (hGmem);
        GlobalFree (hGmem);
        }
      break ;

    case WM_GETDLGCODE :
      if ((wP != VK_RETURN) && (wP != VK_ESCAPE) && (wP != VK_TAB))
        return LONG (DLGC_WANTMESSAGE);
      break ;
    case WWM_CARETTOEND :
      if ((ww = FindWW(hWnd)) != NULL) {
        ww->field->SetCaretToEnd ();
        ww->field->CheckScroll (0);
        }
      break ;

    case WM_VSCROLL :
      {
      ww = FindWW(hWnd);
#ifdef WIN32
      switch (LOWORD(wP)) {
#else
      switch (wP) {
#endif
        case SB_LINEUP :
          ww->field->SetActLine (min (ww->field->GetActLine() - 1,0));
          break ;
        case SB_LINEDOWN :
          ww->field->SetActLine (max (ww->field->GetActLine() + 1,ww->field->GetAnzLines() - 1));
          break ;
        case SB_PAGEUP :
          ww->field->SetActLine (min (ww->field->GetActLine() - 5,ww->field->GetAnzLines()));
          break ;
        case SB_PAGEDOWN :
          ww->field->SetActLine (max (ww->field->GetActLine() + 5,ww->field->GetAnzLines() - 1));
          break ;
        case SB_THUMBPOSITION :
#ifdef WIN32
          ww->field->SetActLine (short(HIWORD(wP)));
#else
          ww->field->SetActLine (short(LOWORD(lP)));
#endif
          break ;
        default :
          break ;
        }
      }
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case MI_Copy :
        case MI_Cut :
          if ((ww = FindWW(hWnd)) != NULL) {
            ww->field->CopyToClipBoard (hWnd);
            if (CRACKER_wID == MI_Cut)
              ww->field->DeleteSelectedLines ();
            }
          break;

        case MI_Insert :
          if ((ww = FindWW(hWnd)) != NULL) {
            ww->field->PasteFromClipBoard (hWnd);
            }
          break;

        case MI_H_Help_DDS :
          {
#ifdef WINHELP
          BOOL bResult;
          DWORD ContextNr = GetHelpContextNr();
#ifdef WIN32
          if (ContextNr < 0)
            bResult = WinHelp (hWnd, GetHelpFile(), HELP_FINDER, 0);
          else
#endif

          WinHelp (hWnd, GetHelpFile(), HELP_CONTEXT, ContextNr);
#else
          HWND wnd = htmlhelp(hWnd, GetHtmlFile(), HH_DISPLAY_TOPIC, NULL);
#endif
          }
          break;
        }
      }
      break;

    case WW_SETTEXTLEN :
      if ((ww = FindWW (hWnd)) != NULL) {
        ww->MaxAnzChars = wP ;
        }
      break ;
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal ;
  }

LPSTR szWordWinClass;
void RegisterWordWin (HINSTANCE hInstance)
  {
  static BOOL registered;
  if (!registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS | CS_DBLCLKS;
    wndclass.lpfnWndProc   = WordWinProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_IBEAM) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = szWordWinClass ;

    RegisterClass (&wndclass) ;
    registered = TRUE ;
    }
  }

DLLExport int _export WINAPI WWGetXWidth (int format,int AnzChars)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,format);
  int res;
  if (lpfm != NULL) {
    HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
    ExtSetTwipsMap (hDC,1.0,0,0);
    POINT pt[2];
    pt[0].x = pt[0].y = 0;
    pt[1].x = lpfm->xAveWidth * AnzChars ;
    pt[1].y = 0;
    LPtoDP(hDC,pt,2);
    res = pt[1].x + 4;
    DeleteDC (hDC);
    }
  else res = 0;
  return res ;
  }

DLLExport int _export WINAPI WWGetYHeight (int format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,format);
  int res;
  if (lpfm != NULL) {
    HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
    ExtSetTwipsMap (hDC,1.0,0,0);
    POINT pt[2];
    pt[0].x = pt[0].y = 0;
    pt[1].x = 0 ;
    pt[1].y = lpfm->yHeight;
    LPtoDP(hDC,pt,2);
    res = pt[1].y + 4;
    DeleteDC (hDC);
    }
  else res = 0;
  return res ;
  }

DLLExport HWND _export WINAPI WWCreateWin (HWND hParent,WORD Id,int format,
                                     int x0,int y0,
                                     int AnzChars,
                                     DWORD style,
                                     HINSTANCE hInstance
                                    )
  {
  hInstance = hLibInst;
  RegisterWordWin (hInstance);
  dontWMCREATE = TRUE ;
  HWND hWnd = CreateWindow (szWordWinClass,
                            NULL,
                            style,
                            x0,y0,
                            WWGetXWidth (format,AnzChars),
                            WWGetYHeight (format),
                            hParent,
                            HMENU(Id),
                            hInstance,
                            LPVOID(NULL)
                           );
  dontWMCREATE = FALSE ;
  WordWin FAR *ww = new WordWin (hWnd,format,FALSE,1,-1,-1,1);
  return hWnd;
  }

DLLExport HWND _export WINAPI WWCreateWinEx (HWND hParent,WORD Id,int format,
                                      int x0,int y0,
                                      int w,int h,
                                      DWORD style,
                                      BOOL password,
                                      int AnzLines,
                                      int Width,
                                      int mAnzChars
                                      )
  {
  RegisterWordWin (hLibInst);
  dontWMCREATE = TRUE ;

  if (AnzLines > 1)
    style |= WS_VSCROLL;

  HWND hWnd = CreateWindow (szWordWinClass,
                            NULL,
                            style,
                            x0,y0,
                            w,h,
                            hParent,
                            HMENU(Id),
                            hLibInst,
                            LPVOID(NULL)
                           );
  dontWMCREATE = FALSE ;
  // if ((Width < 0) && (AnzLines > 1)) {
  if (AnzLines > 1) {
    Width = xTOLP (w - 2 - GetSystemMetrics (SM_CXVSCROLL));
    }
  WordWin FAR *ww = new WordWin (hWnd,format,password,(AnzLines > 1) ? -1 : 1,Width,mAnzChars,AnzLines);
  ww->InitScroll ();
  return hWnd;
  }

DLLExport void _export WINAPI SetupTestFonts ()
  {
  FontInfo fi,fi1;
  lmemset (&fi,'\0',sizeof(fi));
  lstrcpy (fi.lf.lfFaceName,"Arial");
  fi.lf.lfHeight = -320;
  fi.cf.rgbColors = RGB(255,0,0);
  fntInsertFormat (0,&fi);
  lmemset (&fi,'\0',sizeof(fi));
  lstrcpy (fi.lf.lfFaceName,"Arial");
  fi.lf.lfHeight = -200;
  fntInsertFormat (1,&fi);
  lmemcpy (&fi1,&fi,sizeof(fi1));
  fi1.cf.rgbColors = RGB(255,0,0);
  fntInsertFormat (2,&fi1);
  fi.lf.lfHeight = -140 ;
  fntInsertFormat (3,&fi);
  fi1.lf.lfHeight = -140 ;
  fntInsertFormat (4,&fi1);
  }

DLLExport void _export WINAPI WWSetFormat (HWND hWnd,int Format)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    ww->field->SetFormat (Format);
    InvalidateRect (hWnd,NULL,TRUE);
    }
  }

DLLExport void _export WINAPI WWSetMode (HWND hWnd,DWORD mode)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    if (ww->field->GetFieldMode() & FM_SINGLELINE) mode |= FM_SINGLELINE;
    ww->field->SetFieldMode (mode);
    }
  }

DLLExport DWORD _export WINAPI WWGetMode (HWND hWnd)
  {
  DWORD res = 0;
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    res = ww->field->GetFieldMode ();
    }
    
  return res;
  }

DLLExport int _export WINAPI WWGetActFormat (HWND hWnd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    return ww->field->GetActFormat ();
    }
  return 0;
  }

DLLExport WORD _export WINAPI WWGetActModify (HWND hWnd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    return ww->field->GetActModify ();
    }
  return 0;
  }

DLLExport DWORD _export WINAPI WWGetActColor (HWND hWnd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    return ww->field->GetActColor ();
    }
  return 0;
  }

DLLExport void _export WINAPI WWSetOverwrite (HWND hWnd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->doOverwrite = TRUE;
  }

DLLExport void _export WINAPI WWSetModify (HWND hWnd,int Modify,BOOL Set_Clear)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->field->FormatSelection (Modify,Set_Clear);
  }

DLLExport void _export WINAPI WWSetBuddy (HWND hWnd, BOOL flag)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->field->SetButtonField (flag);
  }

double ctool_rfact ;
DLLExport void _export WINAPI DMWAPI_SetClassNames (LPSTR WordWinClass,WWPAINTCALLBACK pcallback,double rfact)
  {
  ctool_rfact = rfact ;
  szWordWinClass = WordWinClass;
  pncall = pcallback;
  }

DLLExport void _export WINAPI WWSetFormatMap (HWND hWnd,int FAR *maps,int AnzPairs)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->field->SetFormatMaps (maps,AnzPairs);
  }


DLLExport void _export WINAPI WWSetOutColor (HWND hWnd,COLORREF color)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    ww->field->SetOutColor (color);
    InvalidateRect (hWnd, NULL, FALSE);
    }
  }

DLLExport void _export WINAPI WWClipBoard (HWND hWnd, WPARAM cmd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    switch (cmd) {
      case MI_Copy:
      case MI_Cut :
        {
        ww->field->CopyToClipBoard (hWnd);
        if (cmd == MI_Cut)
          ww->field->DeleteSelectedLines ();
        }
        break;

      case MI_Insert :
        ww->field->PasteFromClipBoard (hWnd);
        break;
      }
    }
  }

DLLExport void _export WINAPI WWFormatSelection (HWND hWnd,WORD Modify,BOOL doOff)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->field->FormatSelection (Modify,doOff);
  }

DLLExport void _export WINAPI WWColorSelection (HWND hWnd,DWORD Color)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    ww->field->ColorSelection (Color);
  }

DLLExport BOOL _export WINAPI WWSelectionInString (HWND hWnd)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    return ww->field->JustStringsSelected ();
  else
    return FALSE ;
  }

//---------------------------------------------------------------------------
// Hat das angegebene Eingabefeld eine Selektion?
//---------------------------------------------------------------------------
DLLExport BOOL _export WINAPI WWIsFieldSelected (HWND hWnd)
  {
  BOOL Selected = FALSE;
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    Selected = ww->field->IsSomeTextSelected ();

  return Selected;
  }

DLLExport void _export WINAPI WWInsertAtCaret (HWND hWnd,LPSTR str)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    InsertAtCaret (ww->field,str);
  SetFocus (hWnd);
  }

DLLExport void _export WINAPI WWSetAtCaret (HWND hWnd,LPSTR str)
  {
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL)
    SetAtCaret (ww->field,str);
  SetFocus (hWnd);
  }

DLLExport BOOL _export WINAPI WWSetCaretTo (HWND hWnd,int Line,int Col)
  {
  BOOL Selected = FALSE;
  WordWin FAR *ww;
  if ((ww = FindWW(hWnd)) != NULL) {
    ww->field->SetCaretTo (Line,Col);
    SetFocus (hWnd);
    }

  return Selected;
  }

