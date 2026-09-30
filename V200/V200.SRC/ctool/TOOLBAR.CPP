 //
//  $Header:   P:/marille/clinicum/ctool/rev/toolbar.cpv   1.136   24 May 2000 12:04:16   Wolfgang  $
//  $Log:   P:/marille/clinicum/ctool/rev/toolbar.cpv  $
// 
//    Rev 1.136   24 May 2000 12:04:16   Wolfgang
// 1.) Bei CTOOL_DisableParent 0 zurueckgeben falls kein ActiveTopWindow.
// 
//    Rev 1.135   13 Mar 2000 08:15:00   Hannes
// Beim Update der Hoehe etc.. Position neu initialisiert
// 
//    Rev 1.134   12 Oct 1999 12:06:50   Hannes
// Menue in Stationsgraphik
// 
//    Rev 1.133   06 Sep 1999 20:20:50   Hannes
// MYMDICLIENT auch ausgenommen
// 
//    Rev 1.132   06 Sep 1999 19:07:18   Helmuth
// Endlosloop in ActivateMainToolBar
// 
//    Rev 1.131   31 Mar 1999 14:55:50   Gerhold
// htmlhelp
// 
//    Rev 1.130   28 Oct 1998 18:33:38   Martin
// GWL_SCREEN bei RemoveScreen auf 0L setzen
// 
//    Rev 1.129   28 Oct 1998 15:04:40   Wolfgang
// 1.) In RemoveScreen fall notwendig HookScreen loeschen.
// 
//    Rev 1.128   08 Oct 1998 13:09:26   Gerhold
// #ifdef STRICT  bei CallWindowProc
// 
//    Rev 1.127   05 Oct 1998 11:05:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.126   14 Aug 1998 18:24:58   Gerhold
// InitCommonControls statt InitCommonControlsEx!
// 
//    Rev 1.125   12 Aug 1998 11:50:14   Gerhold
// Hook Prozedur ... Abfrage der Fensterklasse WORDWIN
// 
//    Rev 1.124   04 Aug 1998 15:53:22   Gerhold
// InitCommonControls ist jetzt im Initialize
// 
//    Rev 1.123   02 Aug 1998 14:46:26   Gerhold
// _export EnableToolTips
// 
//    Rev 1.122   30 Jul 1998 11:11:20   Gerhold
// WInHelp angepasst fuer den HELP_FINDER
// 
//    Rev 1.121   29 Jul 1998 14:06:36   Gerhold
// Der ToolTip-Hook GetMsgProc wird nur einmal pro Applikation aufgerufen
// 
//    Rev 1.120   27 Jul 1998 12:15:18   Gerhold
// Tooltips fuer V300
// 
//    Rev 1.119   10 Jul 1998 09:09:50   Hannes
// 
//    Rev 1.118   25 May 1998 13:38:44   Hannes
// No change.
// 
//    Rev 1.117   22 May 1998 12:03:02   Hannes
// Vermerken der Groessen eines Schirms / Update kann korrekt durchgefuehrt
// werden
// 
//    Rev 1.116   31 Mar 1998 11:55:26   Hannes
// Naechste Layerschweinerei...
// 
//    Rev 1.115   05 Mar 1998 13:01:02   Hannes
// Und wieder gehts weiter mit Toolbar Fehlern
// 
//    Rev 1.114   10 Feb 1998 18:25:52   Hannes
// TBActivate
// 
//    Rev 1.113   01 Feb 1998 15:43:52   Gerhold
// Tooltip Verbesserungen
// 
//    Rev 1.112   29 Jan 1998 18:10:10   Hannes
// Problem mit Layerhoehen - Berechnung
// 
//    Rev 1.111   16 Jan 1998 13:28:24   Gerhold
// Vorbereitung auf 32-Bit Tooltip
// 
//    Rev 1.110   05 Jan 1998 07:50:02   Hannes
// 
//    Rev 1.109   30 Dec 1997 16:53:16   Hannes
// CTOOL_GetActiveMouseObject, ECC gleichwertig mit MDIChild behandeln
// 
//    Rev 1.108   06 Nov 1997 10:45:28   Hannes
// RemoveScreen -> Objekt auf NULL setzten
// 
//    Rev 1.107   05 Nov 1997 08:20:32   Hannes
// CTOOL_Enable-,CTOOL_DisableParent
// 
//    Rev 1.106   30 Oct 1997 08:42:16   Hannes
// Fehlerkorrektur Timer, ',' bei ToolFloats
// 
//    Rev 1.105   24 Oct 1997 10:13:56   Gerhold
// Vorbereitung fuer ToolTip
// 
//    Rev 1.104   23 Oct 1997 10:30:16   Gerhold
// Disabled-Bitmap fuer die Mappenfaecher laden (LoadBitmap(HAND))
// 
//    Rev 1.103   19 Sep 1997 12:55:56   Gerhold
// WW_ONKILLFOCUS ruft jetzt ToolEdit->OnKillFocus auf
// 
//    Rev 1.102   02 Sep 1997 16:26:24   gerhold
// Windowsversion = 0 ... Kommentar weg um neuen Knopfstil zu impl.
// 
//    Rev 1.101   29 Aug 1997 16:25:16   gerhold
// InitHotKey und RemoveHotKey alle auskommentiert. Die Hotkeys werden
// jetzt vom Tool selber verwaltet.
// 
//    Rev 1.100   10 Jul 1997 08:58:42   Hannes
// 
//    Rev 1.99   19 Jun 1997 15:03:32   Hannes
// 
//    Rev 1.98   22 Apr 1997 10:29:36   Hannes
// Fehlerkorrektur in tabtonextelement
// 
//    Rev 1.97   11 Apr 1997 11:39:38   Gerhold
// OnScreenDown ... jetzt auch mit rechter Maustaste
// 
//    Rev 1.96   08 Apr 1997 17:43:18   gerhold
// WinHelp (...GetHelpFile()...)
// 
//    Rev 1.95   21 Mar 1997 11:27:26   Hannes
// Aufruf von IsCharCallbackInstalled
// 
//    Rev 1.94   20 Mar 1997 10:47:02   Hannes
// Problem mit den mehreren Screens, wenn hinten einer abgebaut wird, korrigiert
// 
//    Rev 1.93   14 Mar 1997 09:46:24   gerhold
// Versuch der neuen Knopf-Stile (Windows 95 like)
// 
//    Rev 1.92   28 Feb 1997 15:01:44   Gerhold
// Erweiterung der kontextsensitiven Menus durch Scriptbefehl
// 
//    Rev 1.91   25 Feb 1997 11:58:26   Gerhold
// Mappennachrichten (OnRButtonDown, OnMsg) fuer Kurzhilfe im Ohrwaschel
// 
//    Rev 1.90   29 Jan 1997 08:56:32   HANNES
// WW_ONKILLFOCUS -> Aufruf der FocusChangeFunktion
// 
//    Rev 1.89   27 Jan 1997 09:39:50   HANNES
// 
//    Rev 1.88   09 Dec 1996 18:24:06   HANNES
// Mouseprozedure fuer LBUTTONDOWN
// 
//    Rev 1.87   26 Nov 1996 07:58:24   HANNES
// Activate - Handling verbessert
// 
//    Rev 1.86   08 Nov 1996 13:26:02   HANNES
// IsWindowVisible
// 
//    Rev 1.85   21 Oct 1996 18:50:10   HANNES
// Verhindern eines Absturzes bei Fehlendem Screen in der Debugvariante
// 
//    Rev 1.84   24 Sep 1996 18:55:26   GERHOLD
// Aufruf der Hilfe zum Dialog in WM_COMMAND (WinHelp ... HelpContextNr)
// 
//    Rev 1.83   18 Sep 1996 20:47:54   HANNES
// 
//    Rev 1.82   09 Sep 1996 19:58:04   GERHOLD
// HelpCapt wird jetzt in DestroyToolBar aufgerufen.
// 
//    Rev 1.81   29 Aug 1996 16:31:52   GERHOLD
// WM_COMMAND ... lP != 0 ? .... sonst Fehler in WIN32
// 
//    Rev 1.80   17 Aug 1996 18:13:40   GERHOLD
// ueberprueft auf HelpCapt != NULL
// 
//    Rev 1.79   25 Jul 1996 19:57:36   GERHOLD
// WM_INITMENUPOPUP
// 
//    Rev 1.78   16 Jun 1996 18:47:54   GERHOLD
// rechte Maustaste, WM_COMMAND
// 
//    Rev 1.77   26 Feb 1996 16:00:00   HANNES
// 
//    Rev 1.76   16 Feb 1996 14:43:42   GERHOLD
// Bitmaps fuer die Multiselektion aus RC-File laden
// 
//    Rev 1.75   02 Feb 1996 10:41:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.74   11 Jan 1996 03:37:14   HANNES
// HotKeyAction
// 
//    Rev 1.73   08 Jan 1996 18:08:54   HANNES
// Enablen des Vaterfensters etwas defensiver implementiert
// 
//    Rev 1.72   08 Jan 1996 17:43:04   GERHOLD
// WW_LBUTTON und DDSLIST_LBUTTON in WM_COMMAND
// 
//    Rev 1.71   02 Jan 1996 22:13:14   HANNES
// Formatieren von Feldern
// 
//    Rev 1.70   15 Dec 1995 17:52:06   GERHOLD
// ExtChildClass in OnKillFocus
// 
//    Rev 1.69   12 Dec 1995 12:04:48   GERHOLD
// Es wird jetzt verhindert, dass Mappenhotkeys in modalen Dialogen durchkommen.
// Schuld waren die Tool-Elemente die eigene Fenster-Handles hatten, und die bei
// einem KILLFOCUS ihren Parent nicht verstaendigt hatten!
// 
//    Rev 1.68   23 Nov 1995 18:02:36   hannes
// FOCUSMODE_FORWARD, FOCUSMODE_BACKWARD fuer ExternTool
// 
//    Rev 1.67   20 Nov 1995 11:42:56   HANNES
// FocusChanging
// 
//    Rev 1.66   31 Oct 1995 10:44:16   GERHOLD
// TextPushCheckButton
// 
//    Rev 1.65   16 Oct 1995 13:28:00   GERHOLD
// screen->destroyIsdone ist neu
// 
//    Rev 1.64   20 Sep 1995 15:59:52   GERHOLD
// Focus wird von Mappen auf Submappen weitergeleitet
// 
//    Rev 1.63   16 Sep 1995 02:03:50   HANNES
// 
//    Rev 1.62   11 Sep 1995 20:24:04   MARTIN
// OnSetFocusProc
// 
//    Rev 1.61   07 Sep 1995 09:02:04   HANNES
// ToolPalette,BitEdit,BitMerge
// 
//    Rev 1.60   04 Sep 1995 13:08:44   HANNES
// 
//    Rev 1.59   27 Aug 1995 12:46:44   HANNES
// 
//    Rev 1.58   24 Aug 1995 09:36:54   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.57   23 Aug 1995 17:27:28   GERHOLD
// 
//    Rev 1.56   16 Aug 1995 08:52:44   HANNES
// Palettenhandling der 16 Farben Bitmaps
// 
//    Rev 1.55   12 Aug 1995 19:31:20   HANNES
// Palettenhandling
// 
//    Rev 1.54   19 Jul 1995 11:16:02   GERHOLD
// 
//    Rev 1.53   10 Jul 1995 19:56:38   GERHOLD
// ColorRect
// 
//    Rev 1.52   07 Jul 1995 17:25:08   GERHOLD
// GetActiveTopWindow auf gueltiges hWnd ueberprueft
// 
//    Rev 1.51   04 Jul 1995 20:39:38   HANNES
// Palettenhandling
// 
//    Rev 1.50   03 Jul 1995 16:15:34   HANNES
// Fehler im Palettenhandling
// 
//    Rev 1.49   02 Jul 1995 18:19:30   HANNES
// Palettenhandling
// 
//    Rev 1.48   27 Jun 1995 13:53:32   HANNES
// DrawTransparentbitmap
// 
//    Rev 1.47   26 Jun 1995 10:16:00   GERHOLD
// Paletten-Nachrichten weiterleiten.
// 
//    Rev 1.46   14 Jun 1995 13:08:04   GERHOLD
// SetControl (....,privData,...) ... privData nur im EM_LOAD verwenden
// 
//    Rev 1.45   19 May 1995 16:27:40   hannes
// 
//    Rev 1.44   15 May 1995 08:36:40   HANNES
// 
//    Rev 1.43   12 Apr 1995 12:27:28   GERHOLD
// 
//    Rev 1.42   05 Apr 1995 16:39:40   GERHOLD
// 
//    Rev 1.41   04 Apr 1995 16:20:12   GERHOLD
// in EM_RESET | EM_FIXCONNECTION Abfrage auf "Data->MyTool != NULL"
// 
//    Rev 1.40   04 Apr 1995 12:10:58   HANNES
// 
//    Rev 1.39   31 Mar 1995 13:10:10   HANNES
//  
// 
//    Rev 1.38   27 Mar 1995 13:18:36   HANNES
//  
// 
//    Rev 1.37   24 Mar 1995 18:35:52   GERHOLD
// In PaintTheTools "IsToolRectVisible" eingebaut
// 
//    Rev 1.36   20 Mar 1995 13:43:18   HANNES
// 
//    Rev 1.35   03 Mar 1995 18:18:28   GERHOLD
// 
//    Rev 1.34   02 Mar 1995 17:14:56   HANNES
// 
//    Rev 1.33   02 Mar 1995 15:24:52   GERHOLD
// TAB hat noch nicht ganz richtig funktioniert
// 
//    Rev 1.32   24 Feb 1995 11:05:04   GERHOLD
// TabToNextElement ... jetzt koennen auch Submappen mit TAB erreicht werden!
// 
//    Rev 1.31   09 Feb 1995 15:23:34   HANNES
// 
//    Rev 1.30   09 Feb 1995 10:07:30   HANNES
// 
//    Rev 1.29   31 Jan 1995 15:37:54   HANNES
// 
//    Rev 1.28   16 Dec 1994 17:22:06   GERHOLD
// HotKey-Msg-Box ist jetzt hoffentlich immer disabled
// 
//    Rev 1.27   16 Dec 1994 16:25:48   GERHOLD
// Focus Gschichterln
// 
//    Rev 1.26   15 Dec 1994 23:50:16   HANNES
// Focusgschichtln...
// 
//    Rev 1.25   15 Dec 1994 18:22:36   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.24   13 Dec 1994 14:01:24   GERHOLD
// WM_LBUTTONDOWN ... Focus nur an Toolbear geben wenn <> WORDWIN.
// 
//    Rev 1.23   09 Dec 1994 19:40:50   HANNES
// 
//    Rev 1.22   16 Nov 1994 21:08:48   GERHOLD
// ???
// 
//    Rev 1.21   31 Oct 1994 09:45:44   GERHOLD
// WM_COMMAND ... WW_LBUTTON gibt bei EditCallBack != NULL <1> zurueck.
// 
//    Rev 1.20   17 Oct 1994 14:55:34   HANNES
// Nicht modale Dialogboxen
// 
//    Rev 1.19   11 Oct 1994 17:57:06   HANNES
// Lederbmp wieder freigegeben
// 
//    Rev 1.18   22 Sep 1994 16:06:28   HANNES
// Vergroesserungsfaktoren
// 
//    Rev 1.17   20 Sep 1994 11:27:28   HANNES
// Mappen in Dialogboxen
// 
//    Rev 1.16   06 Sep 1994 08:43:34   GERHOLD
// 
//    Rev 1.15   05 Sep 1994 13:17:06   GERHOLD
//  UpDown-Control, Edit-Elemente mit Combo-Button sind nicht mehr editierbar
//  Begin-, Continue-, EndCapture auf On_LButtonDown, On_MouseMove,
//  On_LButtonUp geaendert.
// 
//    Rev 1.14   31 Aug 1994 18:00:22   GERHOLD
// im WM_CREATE auf ScreenNmbr != 0 abgefragt (wegen der Caption-Hoehe)
// 
//    Rev 1.13   31 Aug 1994 15:43:26   GERHOLD
// 
//    Rev 1.12   30 Aug 1994 08:47:26   GERHOLD
// static int OldSize = screen->DesiredClientSize
// 
//    Rev 1.11   29 Aug 1994 12:46:00   GERHOLD
// 
//    Rev 1.10   28 Aug 1994 11:37:24   GERHOLD
// Aenderungen im WM_WINDOWPOSCHANGING. Der Client-Bereich ist nun genau so
// gross, wie in Attr->h in logischen Koordinaten angegeben wird.
// 
//    Rev 1.9   26 Aug 1994 15:58:10   GERHOLD
// 
//    Rev 1.8   17 Aug 1994 09:29:54   HANNES
// Aufloesungsanabhaengigkeit
// 
//    Rev 1.7   10 Aug 1994 12:13:50   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.6   09 Aug 1994 13:23:02   GERHOLD
// Doppelclick fuer Edit-Elemente in Restool
// 
//    Rev 1.5   08 Aug 1994 17:40:18   GERHOLD
// Doppelclick fÅr RESTOOL ermoeglicht.
// 
//    Rev 1.4   05 Aug 1994 11:54:00   GERHOLD
// BmpTextPushButton, XYFromRect
// 
//    Rev 1.3   12 Jul 1994 14:51:58   HANNES
// InitializeExtended
// 
//    Rev 1.2   11 Jul 1994 10:41:30   HANNES
// WM_WINDOWPOSCHANGED
// 
//    Rev 1.1   05 Jul 1994 15:35:40   GERHOLD
// 3D-Zeichenfunktion und einige gro·e énderungen in WndProc
// 
//    Rev 1.0   24 Jun 1994 16:41:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.29   04 May 1994 10:49:50   MARTIN
// Fehler beim Speichern der Fensterposition behoben
// 
//    Rev 1.28   14 Apr 1994 16:56:50   HANNES
// ToolEdit::SetOverwrite
// 
//    Rev 1.27   03 Mar 1994 22:03:52   HANNES
// Besseres Handling beim On_LButtonUp
// 
//    Rev 1.26   20 Jan 1994 23:54:30   HANNES
// WW_RBUTTONDOWN, HelpCap nur erzeugt, wenn sonst noch niemand die Capture
// hat, ToolWithFocus beim ausschalten eines Focus rueckgesetzt
// 
//    Rev 1.25   16 Jan 1994 18:58:52   HANNES
// Ueberfluessier Font nicht mehr erzeugt
// 
//    Rev 1.24   04 Jan 1994 17:23:56   HANNES
// Bubble - Window Handling bei WW_RBUTTON
// 
//    Rev 1.23   09 Dec 1993 15:13:12   HANNES
// 
//    Rev 1.22   29 Nov 1993 08:38:08   HANNES
// BmpFloat
// 
//    Rev 1.21   18 Nov 1993 16:25:48   HANNES
// Abbrechen der Hotkeybearbeitung
// 
//    Rev 1.20   28 Oct 1993 12:40:00   MARTIN
// Help-Bubbles umgebaut
// 
//    Rev 1.19   18 Oct 1993 19:45:06   HANNES
// ToolBEdit
// 
//    Rev 1.18   04 Oct 1993 08:30:00   GERHOLD
// 
//    Rev 1.17   27 Sep 1993 18:30:38   GERHOLD
// 
//    Rev 1.16   24 Sep 1993 11:07:16   GERHOLD
// ???
// 
//    Rev 1.15   22 Sep 1993 09:49:00   GERHOLD
// Version nach St.Poelten
// 
//    Rev 1.14   09 Sep 1993 19:09:04   GERHOLD
// WM_COMMAND fÅr Edit-Element
// 
//    Rev 1.13   24 Aug 1993 10:34:50   GERHOLD
// 
//    Rev 1.12   18 Aug 1993 10:51:52   GERHOLD
// ???
// 
//    Rev 1.11   22 Jul 1993 14:39:18   GERHOLD
// FlapMap
// 
//    Rev 1.10   15 Jul 1993 18:02:46   GERHOLD
// Baseunits veraendert
// 
//    Rev 1.9   15 Jul 1993 16:50:02   GERHOLD
// Linien und Actionbox
// 
//    Rev 1.8   14 Jul 1993 14:50:46   GERHOLD
// statisches Bitmap
// 
//    Rev 1.7   09 Jul 1993 10:55:32   HANNES
// ExternTool
// 
//    Rev 1.6   09 Jul 1993 00:32:22   HANNES
// ToolStatic, GroupBox, WINDOWPOSHANDLING
// 
//    Rev 1.5   08 Jul 1993 11:38:34   HANNES
// CreateToolbar
// 
//    Rev 1.4   07 Jul 1993 17:37:54   GERHOLD
// No change.
// 
//    Rev 1.3   05 Jul 1993 14:54:48   GERHOLD
// 1.Version fÅr Marille
// 
//    Rev 1.2   03 Jun 1993 12:08:58   GERHOLD
// Zwischenversion
// 
//    Rev 1.1   25 May 1993 09:56:54   GERHOLD
// test
// 
//    Rev 1.0   25 May 1993 09:53:56   GERHOLD
// Initial revision.
//
#include <windows.h>
#include <stdio.h>

#ifdef WIN32
  #include <winnt.h>
#endif


#include "dds32.h"
#define TOOLBAR_MAIN
#define MODULENUM   43
#include "winass.hpp"
#include "wordwin.hpp"
#include "toolbar.hpp"
#include "globmem.h"
#define JUST_EM
#include <htmlhelp.h>
#include "dds.hpp"
#include "ddsmsg.h"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"
#include "dlg3d.hpp"

#include "mappe.hpp"

#ifdef TOOLTIP
  #define NOTOOLBAR
  #define NOSTATUSBAR
  #include <commctrl.h>
#endif

//-------------------------------
// multiple monitor support!!!
//-------------------------------
#ifndef COMPILE_MULTIMON_STUBS
#define COMPILE_MULTIMON_STUBS
#include <multimon.h>
#endif

extern LPSTR szListClassName;
extern LPSTR szFolderClass;
LPSTR szWWName;
LPSTR szClassName;


LPVOID wtobj::operator new (size_t size) 
  {
  return GetGlobMem (size);
  }

void wtobj::operator delete (LPVOID obj) 
  {
  FreeGlobMem (obj);
  }



/*------------------------------------------------------------------*\
* function InsertToWndList                                           *
*                                                                    *
* Parameter:  wnd ... Zeiger auf WndList                             *
* Zweck:      f¸gt das Fenster am Anfang der Liste ein.              *
\*------------------------------------------------------------------*/
void InsertToWndList (WndList FAR *wnd)
  {
  wnd->Next = wnd->Parent->FirstWnd;
  wnd->Parent->FirstWnd = wnd;
  }

/*--------------------------------------------------------------------*\
* function DelFromWndList                                              *
*                                                                      *
* Parameter:  wnd ... Zeiger auf WndList                               *
* Zweck:      lˆscht das Fenster aus der Liste.                        *
\*--------------------------------------------------------------------*/
void DelFromWndList (WndList FAR *wnd)
  {
  WndList FAR *prev = NULL ;
  WndList FAR *h = wnd->Parent->FirstWnd ;

  for ( ; ; h = h->Next) {
    if (h == wnd) {                  // Fenster gefunden?

    if (wnd->Parent->nonmodal)
      wnd->Parent->RemoveWindowWithLayer (h->Layer);
    else  
      wnd->Parent->Remove(h->RefWnd);
      if (prev != NULL) {            // ja => gibt es einen VorgÑnger?
        prev->Next = h->Next ;       // ja => wnd aus der Liste ausklammern
        }
      else              
        wnd->Parent->FirstWnd = h->Next ;         // nein => nÑchstes Fenster ist Start der Liste
      break ;                        // und jetzt kein Wort mehr!
      }
    prev = h;
    }
  // Loeschen des Screens
  DestroyToolBar (wnd->Parent);
  }

/*------------------------------------------------------------------*\
* function:  InsertScreen                                            *
\*------------------------------------------------------------------*/
void InsertScreen (ScreenList FAR *sc)
  {
  sc->Next = FirstScreen ;
  FirstScreen = sc ;
  }

/*------------------------------------------------------------------*\
* function:  RemoveScreen                                            *
\*------------------------------------------------------------------*/
static LPSCREEN HookScreen = NULL; // wird von GetMsgProc benoetigt

void RemoveScreen (ScreenList FAR *sc)
  {
  SetWindowLong (sc->hWnd,GWL_SCREEN,0L);
  sc->hWnd = 0;

  // Der Schirm exisitiert nicht mehr, das sollte man den anderen auch
  // noch sagen !
  ////////////////////////////////////////////////////////////////////
  if (sc->ScreenNmbr > 0) {
    (* SetData) (sc->privData,sc->ScreenId,NULL,0,NULL);
    }

  // Loeschen aller noch vorhandenen Elemente ....
  while ((sc->FirstWnd != NULL) && (sc->FirstWnd->first)) {
    LPVOID nullobj = NULL;
    (* SetData) (sc->FirstWnd->first->privData,LPTOOLHEADER(sc->FirstWnd->first->StructData)->ObjId,&nullobj,sizeof(LPVOID),sc->FirstWnd->first->StructData);
    sc->FirstWnd->first->Reset(FALSE);
    delete sc->FirstWnd->first;
    }

  ScreenList FAR *prev = NULL ;
  for ( ScreenList FAR *h = FirstScreen ; h != NULL ; ) {
    if (h == sc) {
      if (prev != NULL) 
        prev->Next  = sc->Next ;
      else              
        FirstScreen = sc->Next ;

      if (HookScreen == sc)
        HookScreen = NULL;
      delete sc ;
      break ;
      }
    prev = h ;
    h = h->Next ;
    }
  }



/*------------------------------------------------------------------*\
* function:  FindScreen                                              *
\*------------------------------------------------------------------*/
ScreenList FAR *FindScreen(int ScreenNmbr)
  {
  for ( ScreenList FAR *sc = FirstScreen ; sc != NULL ; sc = sc->Next)
    if (sc->ScreenNmbr == ScreenNmbr) return sc ;
  DBWIN_ASSERT(FALSE);
  return NULL ;
  }



/********************************************************************\
**********************************************************************
**                                                                  **
**                         Klasse WndList                           **
**                                                                  **
**********************************************************************
\********************************************************************/

/*------------------------------------------------------------------*\
* CONSTRUCTOR WndList                                                *
*                                                                    *  
* Parameter:  RWnd .... Handle auf das Referenz-Fenster              *  
*             PData ... Zeiger auf interne Daten                     *  
*             pSize ... Grî·e der internen Datenstruktur             *
*             L     ... Nr. des Layers                               *
\*------------------------------------------------------------------*/
WndList::WndList (HWND RWnd,int L,ScreenList FAR *p)
  { 
  Layer = L ; 
  RefWnd = RWnd ; 
  first = NULL ;
  Next = NULL ;
  Parent = p;

  InsertToWndList (this);       // Fenster in die Liste einfÅgen
  }

/*------------------------------------------------------------------*\
* DESTRUCTOR WndList                                                 *
\*------------------------------------------------------------------*/
WndList::~WndList ()
  {
  while (first != NULL) {
    first->Reset(FALSE);
    delete first ;
    }
  DelFromWndList (this);
  }


/*---------------------------------------------------------------*\
* member function: void Insert                                    *
*                                                                 *
* Parameter:  Zeiger auf ein Tool-Element                         *
* Zweck:      F¸gt ein Tool-Element in die Tool-Liste ein         *
\*---------------------------------------------------------------*/
void WndList::Insert (tool FAR *elem)
  {
  if (first == NULL)      // gibt es bereits einen Eintrag?
    first = elem;         // nein => erster Eintrag = elem
  else {
    for (tool FAR *h = first ; h->Next != NULL ; h = h->Next);
    h->Next = elem;       // ja => fÅge das Element an das Ende der Liste ein
    }
  }

/*---------------------------------------------------------------*\
* member function: void DelFromList                               *
*                                                                 *
* Parameter:  Zeiger auf ein Tool-Element                         *
* Zweck:      lˆscht ein Tool-Element aus der Tool-Liste          *
\*---------------------------------------------------------------*/
void WndList::DelFromList (tool FAR *elem)
  {
  tool FAR *prev = NULL ;
  tool FAR *h = first ;             // Zeiger auf das erste Element

  for ( ; ; h = h->Next) {
    if (h == elem) {                // Tool gefunden?
      if (prev != NULL) 
        prev->Next = elem->Next;
      else              
        first = elem->Next;

      break ;
      }
    prev = h;
    }
  }

/*------------------------------------------------------------------*\
* member function:  Search                                           *
\*------------------------------------------------------------------*/
tool FAR *WndList::Search (WORD Id)
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next) {
    if (Id == h->Id()) 
      return h;
    }
    
  return NULL ;
  }

/*--------------------------------------------------------------------*\
* member function:  virtual PaintTheTools                              *
*                                                                      *  
* Parameter:  hDC  ..... Geraete-Kontext der Toolbar                   *  
*             hMemDC ... kompatibler Geraete-Kontext fuer Bitmap       *  
* Zweck:      Zeichnet alle Tool-Elemente in der Tool-Liste            *
\*--------------------------------------------------------------------*/  
void WndList::PaintTheTools (HDC hDC,HDC hMemDC)
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next) 
    if (h->IsToolRectVisible (hDC))
      h->PaintTool (hDC,hMemDC);
  }

/*------------------------------------------------------------------*\
* member function:  ActivateTheTools                                 *
\*------------------------------------------------------------------*/
void WndList::ActivateTheTools (BOOL state)
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next) {
    h->OnActivate (state);
    h->Invalidate (TRUE);
    if ((!state) && (Parent->ToolWithFocus == h))
      Parent->ToolWithFocus = NULL ;
    }
  }


/*------------------------------------------------------------------*\
* member function:  ActivateHotKeys                                  *
\*------------------------------------------------------------------*/
void WndList::ActivateHotKeys (BOOL State)
  {
/*
  for (tool FAR *h = first ; h != NULL ; h = h->Next) 
    if (State)
      h->InitHotKey ();
    else  
      RemoveHotKey (h);
*/
  }
  
  
/*------------------------------------------------------------------*\
* member function:  virtual HitTest                                  *
*                                                                    *  
* Parameter:    lp ..... Zeiger auf einen TPoint                     *  
* R¸ckgabewert: Zeiger auf ein Tool-Element                          *
* Zweck:        Sucht in der Fenster-Liste das Element mit den       *
*               gew¸nschten Koordinaten.                             *
\*------------------------------------------------------------------*/
tool FAR * WndList::HitTest (LPPOINT lP)
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next) 
    if (h->HitTest(lP)) return h;
  return NULL ;
  }

/*------------------------------------------------------------------*\
* member function:  Find                                             *
*                                                                    *  
* Parameter:    hWnd ..... Handle auf das gesuchte Fenster           *  
* R¸ckgabewert: Zeiger auf ein Fenster-Listen-Element                *
* Zweck:        Sucht in der Fenster-Liste das Element mit dem       *
*               gewuenschten Handle des Referenzfensters             *
\*------------------------------------------------------------------*/
WndList FAR *WndList::Find (HWND hWnd)
  {
  for ( WndList FAR *res = this; res != NULL ; res = res->Next ) {
    if (res->RefWnd == hWnd) 
      break;
    }
  return res;
  }



WndList FAR *WndList::GetWindowWithLayer (int Layer)
  {
  for ( WndList FAR *res = this; res != NULL ; res = res->Next ) {
    if (res->Layer == Layer)
      break;
    }
  return res;    
  }

tool FAR * WndList::GetFirstTool ()
  {
  for (tool FAR *h = first ; h->Next != NULL ; h = h->Next);
  return h;
  }

tool FAR * WndList::GetLastTool ()
  {
  return first;
  }


/*------------------------------------------------------------------*\
* member function:  ChangeParent                                     *
\*------------------------------------------------------------------*/
void WndList::ChangeParent ()
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next) 
    h->ChangeParent (h->Parent->Parent->hWndToolbar());
  }

void WndList::OnMouseMove (WPARAM wP,LPARAM lP)
  {
  for (tool FAR *h = first ; h != NULL ; h = h->Next)
    h->OnMouseMove (wP,lP);
  }

/********************************************************************\
**********************************************************************
**                                                                  **
**                        Klasse ScreenList                         **
**                                                                  **
**********************************************************************
\********************************************************************/
ScreenList::ScreenList (int ScNmbr,LPVOID pData,int pdSize)
  {
  ScreenNmbr = ScNmbr;

  ToolWithFocus = NULL;
  privData = GetGlobMem (pdSize);
  lmemcpy (privData,pData,pdSize);
  InsertScreen (this);

#ifdef TOOLTIP
  g_hhk = NULL;
  hWndToolTip = NULL;
#endif
  }



/*------------------------------------------------------------------*\
* member function:  GetWnd                                           *
*                                                                    *
* Parameter:    hWnd.... Handle des Referenzfensters                 *
*               Layer... Nr. des Layers im Screen                    *
* R¸ckgabewert: Zeiger auf ein Element aus der Fensterliste          *
\*------------------------------------------------------------------*/
WndList FAR *ScreenList::GetWnd(HWND hWnd,int Layer)
  {
  static int LastLayer = -1;

  WndList FAR *res;

  if (nonmodal) {
    if ((LastLayer != Layer) || ((res = FirstWnd->GetWindowWithLayer(Layer)) == NULL)) {
      res = new WndList (hWnd, Layer, this);
      LastLayer = Layer;
      }
    }
  else {  
    if ((FirstWnd == NULL) || ((res = FirstWnd->Find(hWnd)) == NULL)) {
      res = new WndList (hWnd,Layer,this);
      }
    DBWIN_ASSERT (res->Layer == Layer);
    }
  return res;
  }



/*------------------------------------------------------------------*\
* function ChangeParentInWndList                                     *
*                                                                    *  
* Parameter:  kein                                                   *  
* R¸ckgabewert:  kein                                                *  
* Zweck:         ƒndert f¸r jedes Fenster das Parenthandle jener     *
*                Tools, die ¸ber eine eigene Fensterklasse verf¸gen. *   
\*------------------------------------------------------------------*/
void ScreenList::ChangeParent ()
  {
  for (WndList FAR *Wnd = FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
    Wnd->ChangeParent ();
  }


/*------------------------------------------------------------------*\
* member function:  MoveBackward                                     *
*                                                                    *  
* Parameter:    start ....                                           *  
* Zweck:        schiebt die Layer-Liste nach oben, um ab start Platz *
*               zu machen.                                           *
\*------------------------------------------------------------------*/
void ScreenList::MoveBackward (int start)
  {
  for (int i = MAXSHOWNLAYERS-1; i > start ; i--)
    ActiveList[i] = ActiveList[i-1];
  }

/*------------------------------------------------------------------*\
* member function:  MoveForward                                      *
*                                                                    *  
* Parameter:    start ....                                           *  
* Zweck:        schiebt die Layer-Liste nach unten, und entfernt     *
*               somit das Element an Position start.                 *
\*------------------------------------------------------------------*/
void ScreenList::MoveForward (int start)
  {
  for (int i = start ; i < MAXSHOWNLAYERS - 1 ; i++) {
    ActiveList[i] = ActiveList[i+1];
    if (ActiveList[i] != NULL) {
      for (tool FAR *h = ActiveList[i]->first ; h != NULL ; h = h->Next)
        h->MoveTool ();
      }
    }
  ActiveList[i] = NULL ;
  }

/*------------------------------------------------------------------*\
* member function:  LayerStart                                       *
\*------------------------------------------------------------------*/
int ScreenList::LayerStart (int Layer)
  {
  int res = 0;
  for (int i = 0 ; i < MAXSHOWNLAYERS ; i++)
    if ((ActiveList[i] != NULL) && (Layer > ActiveList[i]->Layer))
      res += ActiveList[i]->yHeight;
    else
      break ;
  return res;
  }

/*------------------------------------------------------------------*\
* member function:  Insert                                           *
*                                                                    *  
* Parameter:    wnd .... Zeiger auf ein Element der Fenster-Liste    *  
* Zweck:        setzt in der Layer-Liste einen Zeiger auf das        *
*               Fensterlisten-Element wnd.                           *
\*------------------------------------------------------------------*/
void ScreenList::Insert (LPWNDLIST wnd)
  {
  // Ueberpruefung, ob noch nicht drinnen
  ///////////////////////////////////////
  if (wnd == NULL) return;

  if (ToolWithFocus == NULL) {
    for ( tool FAR *h = wnd->first ; h != NULL ; h = h->Next) {
      if (h->HasTabStop()) {
        ToolWithFocus = h;
        break ;
        }
      }
    }

  BOOL found = FALSE ;

  for (int i = 0 ; i < AnzActive ; i++)
    if (wnd == ActiveList[i]) 
      found = TRUE ;

  if (!found) {
    for (i = 0 ; i < AnzActive ; i++) {
      if (ActiveList[i]->Layer > wnd->Layer) break ;

      // Alle Tools des Layers zu Berechnung der Layerhoehe heranziehen
      ActiveList[i]->yHeight = 0 ;
      for (tool FAR *h = ActiveList[i]->first ; h != NULL ; h = h->Next)
        h->GetRect ();
      }


    MoveBackward (i);             // Liste nach oben setzen
    ActiveList[i] = wnd;          // Zeiger positionieren
    AnzActive++ ;                 // ein Fenster mehr
    for ( ; i < AnzActive ; i++) {
      for (tool FAR *h = ActiveList[i]->first ; h != NULL ; h = h->Next)
        h->MoveTool ();
      }
    }
  }

/*------------------------------------------------------------------*\
* member function:  Remove                                           *
*                                                                    *  
* Parameter:    RefWnd ... Handle auf das aktive Fenster             *  
* Zweck:        gibt den Zeiger aus der Layer-Liste der auf das      *
*               Fensterlisten-Element mit dem Handle Refwnd zeigt    *
*               wieder frei.                                         *
\*------------------------------------------------------------------*/
void ScreenList::Remove (HWND RefWnd)
  {
  for (int i = 0 ; i < AnzActive ; i++) {
    if (ActiveList[i]->RefWnd == RefWnd) {
      (ActiveList[i])->ActivateTheTools(FALSE);
      (ActiveList[i])->ActivateHotKeys (FALSE);
      MoveForward (i);
      AnzActive-- ;
      }
    }
  }


void ScreenList::RemoveWindowWithLayer (int Layer)
  {
  for (int i = 0 ; i < AnzActive ; i++) {
    if (ActiveList[i]->Layer == Layer) {
      (ActiveList[i])->ActivateTheTools(FALSE);
      (ActiveList[i])->ActivateHotKeys (FALSE);
      MoveForward (i);
      AnzActive-- ;
      }
    }
  }


/*------------------------------------------------------------------*\
* member function:  OnKillFocus                                      *
*                                                                    *  
* Parameter:    wP ... Fenster, welches den Focus bekommt            *
\*------------------------------------------------------------------*/
extern LPSTR ExtChildClass;
#define  ANZCLASS  3
void ScreenList::OnKillFocus (WPARAM wP)
  {
  if (nonmodal)
    return;

  char  szClass[80];
  LPSTR szDefined[ANZCLASS];
  szDefined[0] = szWWName;
  szDefined[1] = szListClassName;
  szDefined[2] = "ECC";      // dangerous!! ExtChildClass;

  if (!(IsWindow(HWND(wP))))
    return;

  // Ist das Fenster ein WORDWIN oder ein EXTERNTOOL, dann darf der Screen
  // der dieses Element als Child hat die Hotkeys nicht abgeben !!!!!
  GetClassName(HWND(wP), szClass, sizeof(szClass));
  for (BOOL Found = FALSE, i = 0; (i < ANZCLASS) && (!Found); i++)
    if (lstrcmp(szClass, szDefined[i]) == 0)
      Found = TRUE;

  if (hWndToolbar () && (IsChild(hWndToolbar(), HWND(wP))) && (Found))
    return;

  // es war also kein Kindfenster, dann muss ich den Fokus abgeben
  if (ToolWithFocus != NULL) {
    if (tbActive != NULL) (* tbActive) (FALSE);
    ToolWithFocus->SetToolFocus (FALSE);   // dem alten Element Focus wegnehmen
    }

  // alle Dialoge und Mappen (nicht die Haupt-Toolbar) entfernen ihre Hotkeys
#ifdef INITHOTKEYS
  if (ScreenNmbr != 0) {
    for (WndList FAR *Wnd = FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
      for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
        RemoveHotKey (h);
    }
#endif

  // im Falle der Haupt-Toolbar muessen auch die Mappen-Hotkeys entfernt werden
#ifdef INITHOTKEYS
  if (this == MainScreen) {
    // Mal nachsehen obs eine Mappe gibt
    for (ScreenList FAR *h = FirstScreen ; h != NULL ; h = h->Next) {
      if (h->IstMappe) {
          for (WndList FAR *Wnd = h->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next) {
            for (tool FAR *x = Wnd->first ; x != NULL ; x = x->Next)
              RemoveHotKey (x);
          }
        }
      }
    }
#endif
  }

/*------------------------------------------------------------------*\
* member function:  Paint                                            *
*                                                                    *  
* Parameter:    hDC, hmemDC ... Ger‰te Kontexte                      *
* Zweck:        zeichnet in jedem aktiven Layer die dazugehˆrigen    *
*               Elemente                                             *
\*------------------------------------------------------------------*/
void ScreenList::Paint (HDC hDC,HDC hmemDC)
  {
  HPALETTE hOldPal;

  if ((hPal) && (PalUseCount > 0)) {
    hOldPal = SelectPalette (hDC,hPal,TRUE);
    RealizePalette (hDC);
    }
  else
    hOldPal = 0 ;

  for (int i = 0 ; i < AnzActive ; i++)
    ActiveList[i]->PaintTheTools (hDC,hmemDC);

  if (hPal && hOldPal) {
    SelectPalette (hDC,hOldPal,FALSE);
    }
  }

/*------------------------------------------------------------------*\
* member function:  Search                                           *
*                                                                    *  
* Parameter:    Id ...                                               *
* R¸ckgabewert: Zeiger auf ein Listenelement                         *
* Zweck:                                                             *
\*------------------------------------------------------------------*/
tool FAR * ScreenList::Search (WORD Id)
  {
  tool FAR *res = NULL ;
  for (int i = 0 ; ((i < AnzActive) && (res == NULL)) ; i++)
    res = ActiveList[i]->Search (Id);
  return res;
  }


/*------------------------------------------------------------------*\
* member function:  HitTest                                          *
*                                                                    *  
* Parameter:    pt ... Koordinaten f¸r die Mausposition              *
* R¸ckgabewert: Zeiger auf ein Tool-Element.                         *
* Zweck:        ‹berpr¸ft ob bei einem Mausdruck ein Tool-Element    *
*               in einem angezeigten Fenster aktiviert wurde.        *
\*------------------------------------------------------------------*/
tool FAR *ScreenList::HitTest (LPPOINT pt)
  {
  tool FAR *res = NULL ;
  for (int i = 0 ; ((i < AnzActive) && (res == NULL)) ; i++)
    res = ActiveList[i]->HitTest (pt);
  return res;
  }


void ScreenList::OnQueryNewPalette (UINT msg)
  {
  if (hPal) {
    HDC hDC = GetDC (hWnd);
    HPALETTE hOldPal = SelectPalette (hDC, hPal, msg == WM_QUERYNEWPALETTE ? FALSE : TRUE);
  
    int nChanged = RealizePalette (hDC);

    SelectPalette (hDC, hOldPal, TRUE);
    ReleaseDC (hWnd, hDC);

    if (nChanged > 0)
      InvalidateRect (hWnd,NULL,FALSE);
    }
  }
HPALETTE hFirstScreenPal;
ScreenList FAR *PaletteForScreen;
void ScreenList::SetPalette (HPALETTE hP)
  { 
  if (hPal == 0) {
    hPal = hP ;
    if (hFirstScreenPal == 0) {
      hFirstScreenPal = hPal ;
      PaletteForScreen = this;
      }
    }
  else {
    hPal = hP ;   // Loeschen auch zulassen
    }
  }
ScreenList::~ScreenList ()
  {
  if (hFirstScreenPal == hPal) {
    hFirstScreenPal = 0;
    }
  }

void ScreenList::OnMouseMove (WPARAM wP,LPARAM lP)
  {
  for (int i = 0 ; i < AnzActive ; i++)
    ActiveList[i]->OnMouseMove (wP,lP);
  }


/*******************************************************************\
*********************************************************************
**                                                                 **
**                Toolbar spezifische Funktionen                   **              
**                                                                 **
*********************************************************************
\*******************************************************************/

/*------------------------------------------------------------------*\
*  function: IsChildWindow                                           *
*                                                                    *
*  Parameter:  hWnd .... Fensterhandle der Toolbar                   *
*  Zweck:      Testet ob das Fenster ein Kind-Fenster ist.           *
\*------------------------------------------------------------------*/
BOOL IsChildWindow (HWND hWnd)
  {
  DWORD dwWindowStyle;

  dwWindowStyle = GetWindowLong (hWnd, GWL_STYLE);
  if (dwWindowStyle & WS_CHILD)
    return TRUE;
  else
    return FALSE;
  }

/*------------------------------------------------------------------*\
*  function: IsPopUpWindow                                           *
*                                                                    *
*  Parameter:  hWnd .... Fensterhandle der Toolbar                   *
*  Zweck:      Testet ob das Fenster ein PopUp-Fenster ist.          *
\*------------------------------------------------------------------*/
BOOL IsPopUpWindow (HWND hWnd)
  {
  DWORD dwWindowStyle;

  dwWindowStyle = GetWindowLong (hWnd, GWL_STYLE);
  if (dwWindowStyle & WS_POPUP)
    return TRUE;
  else
    return FALSE;
  }


/*------------------------------------------------------------------*\
*  function: ScreenToClientRect                                      *
*                                                                    *
*  Parameter:  hWnd ..... Fensterhandle der Toolbar                  *
*              prRect ... Rechteck das konvertiert wird              *
*  Zweck:      wandelt die Bildschirmkoordinaten des Rechtecks in    *
*              Clientkoordinaten fuer das Fenster hWnd um.           *
\*------------------------------------------------------------------*/
void ScreenToClientRect (HWND hWnd, LPRECT prRect)
  {
  POINT pt;

  pt.x = prRect->left;
  pt.y = prRect->top;
  ScreenToClient (hWnd, &pt);
  prRect->left = pt.x; 
  prRect->top  = pt.y; 
  pt.x = prRect->right;
  pt.y = prRect->bottom;
  ScreenToClient (hWnd, &pt);
  prRect->right = pt.x; 
  prRect->bottom  = pt.y; 
  }

FARPROC DefFunc;


/*------------------------------------------------------------------*\
*  Fensterfunktionen                                                 *
\*------------------------------------------------------------------*/
void ScreenList::DisableParent (HWND hWnd)
  {
  EnableWindow (hWnd,FALSE);
  if (hWnd != hFrameWnd)
    if (IsWindow (hFrameWnd))
      EnableWindow (hFrameWnd,FALSE);
  disabledWindow = hWnd;
  }

static HWND lastModalScreen;
BOOL inPrinting;
DLLExport void _export WINAPI CTOOL_NotifyPrinting (BOOL inProgress)
  {
  inPrinting = inProgress ;
  }
void ScreenList::EnableParent ()
  {
  BOOL doSetPos;
  if (disabledWindow != hFrameWnd) {
    BOOL dontEnable = FALSE ;
    if (IsWindow (disabledWindow)) {
      EnableWindow (disabledWindow,TRUE);
      char cln[60];
      GetClassName (disabledWindow,cln,sizeof(cln));
      if (lstrcmp (cln,szClassName) == 0) {
        ScreenList FAR *sc = (ScreenList FAR *) GetWindowLong (disabledWindow,GWL_SCREEN);
        if ((sc != NULL) && (sc->disabledWindow != 0))
          dontEnable = TRUE ;
        }
      }
    if (!dontEnable) {
      if ((IsWindow (hFrameWnd)) && (!inPrinting))
        EnableWindow (hFrameWnd,TRUE);
      }
    else
      doSetPos = TRUE ;
    }
  else {
    doSetPos = FALSE ;
    if ((!inPrinting) && (IsWindow (disabledWindow)))
      EnableWindow (disabledWindow,TRUE);
    }
  if ((doSetPos) && (IsWindow (disabledWindow)))
    SetWindowPos (disabledWindow,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
  if (IsWindow(modalParent))
    lastModalScreen = modalParent;
    
  if ((IsWindow (disabledWindow)) && (GetFocus() != disabledWindow))
    SetFocus (disabledWindow);
  }

DLLExport HWND _export WINAPI CTOOL_DisableParent (HWND FAR *modalParent)
  {
  HWND disabledWindow;
  *modalParent = NULL;
  if ((IsWindow(lastModalScreen)) && (IsWindowVisible (lastModalScreen))) {
    disabledWindow = lastModalScreen;
    *modalParent = lastModalScreen;
    }
  else {
    HWND hWndActive = CTOOL_GetActiveTopWindow ();
    if (IsWindow (hWndActive))
      disabledWindow = hWndActive;
    else
      disabledWindow = 0;
    }
  if (disabledWindow) {
    EnableWindow (disabledWindow,FALSE);
    if (disabledWindow != hFrameWnd)
      if (IsWindow (hFrameWnd))
        EnableWindow (hFrameWnd,FALSE);
    }
  return disabledWindow;
  }

DLLExport void _export WINAPI CTOOL_EnableParent (HWND disabledWindow,HWND modalParent)
  {
  BOOL doSetPos;
  if (disabledWindow != hFrameWnd) {
    BOOL dontEnable = FALSE ;
    if (IsWindow (disabledWindow)) {
      EnableWindow (disabledWindow,TRUE);
      char cln[60];
      GetClassName (disabledWindow,cln,sizeof(cln));
      if (lstrcmp (cln,szClassName) == 0) {
        ScreenList FAR *sc = (ScreenList FAR *) GetWindowLong (disabledWindow,GWL_SCREEN);
        if ((sc != NULL) && (sc->disabledWindow != 0))
          dontEnable = TRUE ;
        }
      }
    if (!dontEnable) {
      if ((IsWindow (hFrameWnd)) && (!inPrinting))
        EnableWindow (hFrameWnd,TRUE);
      }
    else
      doSetPos = TRUE ;
    }
  else {
    doSetPos = FALSE ;
    if ((!inPrinting) && (IsWindow (disabledWindow)))
      EnableWindow (disabledWindow,TRUE);
    }
  if ((doSetPos) && (IsWindow (disabledWindow)))
    SetWindowPos (disabledWindow,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
  if (IsWindow(modalParent))
    lastModalScreen = modalParent;
    
  if ((IsWindow (disabledWindow)) && (GetFocus() != disabledWindow))
    SetFocus (disabledWindow);
  }

#define   WMU_NEEDFOCUS   WM_USER + 111
//--------------------------  TabToNextElement  -----------------------------
BOOL TabElemExist (WndList FAR *w)
  {
  if (w == NULL) return FALSE ;
  tool FAR *f = w->GetFirstTool ();
  for ( tool FAR *h = f; h != NULL ; ) {
    if (h->HasTabStop()) return TRUE ;
    h = h->GetNext () ;
    if (h == f) break ;
    }
  return FALSE ;
  }

void ScreenList::TabToNextElement ()
  {
  tool FAR* h = ToolWithFocus;
  if (h == NULL) return;

  ToolWithFocus->SetToolFocus (FALSE);   // dem alten Element Focus wegnehmen

  // SHIFT + TAB
  int fmode ;
  if (GetKeyState(VK_SHIFT) & 0x1000) {
    tool FAR *lasttool = NULL;
    fmode = FOCUSMODE_BACKWARD ;

    h = h->GetPrev ();
    if ((AnzActive > 0) && (ActiveList[AnzActive-1] != NULL)) {
      lasttool = ActiveList[AnzActive-1]->GetLastTool ();
      while (!lasttool->HasTabStop() && (lasttool != ToolWithFocus))
        lasttool = lasttool->GetPrev();
      }

    // Ist das naechste Element anwaehlbar, und faengts in der Reihenfolge
    // wieder von vorne an?  
    while ((!h->HasTabStop()) && (h != ToolWithFocus)) {
      h = h->GetPrev ();
      if (h == lasttool)   // also wieder das letzte Element!
        break;
      }
      
    // Beim letzten Element der Screen-Liste wird in einen anderen Screen gewechselt
    if (h == lasttool) {
      // Bin ich ein Screen im Screen?
      if ((ParentScreen != NULL) && (ParentScreen->ActiveList[AnzActive-1] != NULL) && (TabElemExist (ParentScreen->ActiveList[AnzActive-1]))) {
        // dann moechte ich das letzte Element sehen
        h = ParentScreen->ActiveList[AnzActive-1]->GetLastTool ();
        while ((h != NULL) && (!h->HasTabStop()) && (h != ParentScreen->ToolWithFocus))
          h = h->GetPrev ();

        // sage jetzt dem Parent, welches seiner Tools den Focus bekommt
        ParentScreen->ToolWithFocus = h;
        // ich moechte jetzt so schnell wie moeglich den Focus abgeben
        PostMessage (hWnd, WMU_NEEDFOCUS, WPARAM(ParentScreen->hWnd), 0L);
        return;  // es gibt nichts mehr zu tun!
        }
      else if ((ChildScreen != NULL) && (ChildScreen->ActiveList[AnzActive-1] != NULL) && (TabElemExist (ChildScreen->ActiveList[AnzActive-1]))) {
        // Habe ich einen Screen im Screen?
        h = ChildScreen->ActiveList[AnzActive-1]->GetLastTool ();
        while ((h != NULL) && (!h->HasTabStop()) && (h != ChildScreen->ToolWithFocus))
          h = h->GetPrev ();
          
        ChildScreen->ToolWithFocus = h;  
        PostMessage (hWnd, WMU_NEEDFOCUS, WPARAM(ChildScreen->hWnd), 0L);
        return;
        }
      }
    }
  else {
    fmode = FOCUSMODE_FORWARD ;
    tool FAR *nexttool = NULL;
    
    h = h->GetNext ();

    // das Element suchen, welches garantiert "angeTABbt" werden kann!
    if (ActiveList[0] != NULL) {
      nexttool = ActiveList[0]->GetFirstTool ();
      while (!nexttool->HasTabStop() && (nexttool != ToolWithFocus))
        nexttool = nexttool->GetNext();
      }

    while ((!h->HasTabStop()) && (h != ToolWithFocus)) {
      h = h->GetNext ();
      if (h == nexttool)
        break;
      }
      
    if (h == nexttool) {
      if ((ParentScreen != NULL) && (ParentScreen->ActiveList[0] != NULL) && (ParentScreen->ActiveList[0]) && (TabElemExist (ParentScreen->ActiveList[0]))) {
        h = ParentScreen->ActiveList[0]->GetFirstTool ();
        while ((h != NULL) && (!h->HasTabStop()) && (h != ParentScreen->ToolWithFocus))
          h = h->GetNext ();

        ParentScreen->ToolWithFocus = h;
        PostMessage (hWnd, WMU_NEEDFOCUS, WPARAM(ParentScreen->hWnd), 0L);
        return;
        }
      else if ((ChildScreen != NULL) && (ChildScreen->ActiveList[0] != NULL) && (TabElemExist (ChildScreen->ActiveList[0]))) {
        h = ChildScreen->ActiveList[0]->GetFirstTool ();
        while ((h != NULL) && (!h->HasTabStop()) && (h != ChildScreen->ToolWithFocus))
          h = h->GetNext ();
          
        ChildScreen->ToolWithFocus = h;  
        PostMessage (hWnd, WMU_NEEDFOCUS, WPARAM(ChildScreen->hWnd), 0L);
        return;
        }
      }
    }
            
  ToolWithFocus = h;                             // nein -> hab eines gefunden
  ToolWithFocus->SetToolFocus (TRUE,TRUE,fmode); // Focus auf neues Element setzen
  }


static TBFOCUSCHANGING FocusChanging;

#define MI_H_Help_DDS 295
DLLExport LONG _export CALLBACK PopUpToolBarFunc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  HDC          hDC, hMemDC;
  PAINTSTRUCT  PS;
  ScreenList FAR *screen = (ScreenList FAR *) GetWindowLong (hWnd,GWL_SCREEN);
  LPCLIENTMAP map = (LPCLIENTMAP (GetWindowLong (hWnd,GWL_MAPPTR)));
  switch (msg) {
    case WM_PAINT:
      hDC = BeginPaint (hWnd, &PS);
      if (screen != NULL) {
        if (map != NULL) {
          map->PaintMap (hDC);
          }
        if (IsWindowVisible(hWnd)) {
          edcmem e;
          e.hDC = hDC;
          if (EditCallBack != NULL) {
            (* EditCallBack) (NULL,hWnd,EDC_PAINTRASTER,&e);
            (* EditCallBack) (NULL,hWnd,EDC_HLINEPAINT,&e);
            }
          hMemDC = CreateCompatibleDC (hDC);
          screen->Paint (hDC, hMemDC);
          DeleteDC (hMemDC);
          if (EditCallBack != NULL) {
            (* EditCallBack) (NULL,hWnd,EDC_PAINT,&e);
            }
          }
        }
      EndPaint (hWnd, &PS);
      break;

    case WM_MOVE :
      {
#ifdef STRICT
      LONG RetVal = CallWindowProc ((WNDPROC)DefFunc, hWnd, msg, wP, lP);
#else
      LONG RetVal = CallWindowProc ((FARPROC)DefFunc, hWnd, msg, wP, lP);
#endif
      if (screen != NULL) {
        RECT wpos;
        GetWindowRect(hWnd,&wpos);
        screen->WindowPos.ptPos.x = short (wpos.left);
        screen->WindowPos.ptPos.y = short (wpos.top);
        }
      return RetVal;
      }
      break ;

    case WM_SYSCOMMAND :
      if ((wP & 0xFFF0) == SC_CLOSE) {
        MessageBeep (0);
        }
      else
#ifdef STRICT
        return CallWindowProc ((WNDPROC)DefFunc, hWnd, msg, wP, lP);
#else
        return CallWindowProc ((FARPROC)DefFunc, hWnd, msg, wP, lP);
#endif
      break ;

    case WM_DESTROY :
      {
#ifdef STRICT
      LONG RetVal = CallWindowProc ((WNDPROC)DefFunc, hWnd, msg, wP, lP);
#else
      LONG RetVal = CallWindowProc ((FARPROC)DefFunc, hWnd, msg, wP, lP);
#endif
      if (screen != NULL) {
        // screen->hWnd = 0;
        RemoveScreen (screen);
        }
      break;
      }
      
      // intentionally no break
    default:
#ifdef STRICT
      return CallWindowProc ((WNDPROC)DefFunc, hWnd, msg, wP, lP);
#else
      return CallWindowProc ((FARPROC)DefFunc, hWnd, msg, wP, lP);
#endif
    }
  return 0L;
  }

struct ScreenCreateParam {
  int ScreenNmbr;
  DWORD  ScreenId;
  DWORD  PosRef;
  LPVOID privData;
  int    pdSize;
  };


HBITMAP Leather, hBmpMappeDisabled;
#define EDTIMERID   1000
#define EDTIMEOUT   200
void SetTimerForEdit (HWND hWnd)
  {
  SetTimer (hWnd,EDTIMERID,EDTIMEOUT,NULL);
  }

void KillEditTimer (HWND hWnd)
  {
  KillTimer (hWnd,EDTIMERID);
  }

LONG ScreenList::MyDefWindowProc (HWND hWnd, unsigned msg, WPARAM wP, LPARAM lP)
  {
  return (doNCPaint) ? ibDefWindowProc (hWnd, msg, wP, lP) :
                       DefWindowProc (hWnd, msg, wP, lP);
  }

/*------------------------------------------------------------------*\
* export function: ChildToolBarFunc                                  *
*                                                                    *  
* Parameter:    er¸brigt sich                                        *  
* Zweck:                                                             *
\*------------------------------------------------------------------*/
static ScreenList FAR *__tempscreen__;
static int OldSize;

BOOL IsListKey (WORD wP)
  {
  switch (wP) {
    case VK_PRIOR :
    case VK_NEXT :
    case VK_UP :
    case VK_DOWN :
    case VK_HOME :
    case VK_END :
      return TRUE ;
    default :
      return FALSE ;
    }
  }

BOOL SendToList (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP) 
  {
  for ( HWND hWndChild = GetWindow (hWnd,GW_CHILD) ; hWndChild ; hWndChild = GetWindow (hWndChild,GW_HWNDNEXT) ) {
    char className[64];
    GetClassName (hWndChild,className,sizeof(className));
    if (lstrcmp (className,szListClassName) == 0) {
      SendMessage (hWndChild,msg,wP,lP);
      return TRUE ;
      }
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
// HandlePopupMenu (aus WM_RBUTTONUP, WM_COMMAND - WW_RBUTTONUP)
//
// Oeffnet zu jedem Tool das auf die rechte Maustaste reagiert ein Popup-Menu
// dessen Inhalt in den jeweiligen <tool>::OnRButtonDown bestimmt wird.
//---------------------------------------------------------------------------
DLLExport void _export WINAPI HandlePopupMenu (HWND hWnd, POINT pt, tool FAR *HelpCapt,LPMENULIST lpMenu)
  {
  HMENU hmenu;            // menu template          
  HMENU hmenuTrackPopup;  // floating pop-up menu
                                      
  //  Load the menu template containing the pop-up menu from the 
  // application's resources. 
  hmenu = LoadMenu(hLibInst, "PopupMenu"); 
  if (hmenu == NULL) 
    return; 
         
  // Get the first pop-up menu in the menu template. This is the 
  // menu that TrackPopupMenu displays. 
  hmenuTrackPopup = GetSubMenu(hmenu, 0); 
  if (HelpCapt != NULL) {
    HelpCapt->OnRButtonDown (hmenuTrackPopup);

    // die scriptdefinierten Menues hinzufuegen
    //------------------------------------------
    HelpCapt->AppendContextMenu (hmenuTrackPopup);
    }

  for (LPMENULIST l = lpMenu; l != NULL; l = l->Next) {
    // l->Proc wird als ID fuer das WM_COMMAND missbraucht
    //-------------------------------------------------------
    AppendMenu (hmenuTrackPopup, l->Flags, UINT(l->Proc), l->Text);
    }
         
  // TrackPopup uses screen coordinates, so convert the 
  // coordinates of the mouse click to screen coordinates. 
  ClientToScreen(hWnd, (LPPOINT) &pt); 
         
  // Draw and track the floating pop-up menu.  
  RECT rc;
  GetWindowRect (hWnd, &rc);
  TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
      pt.x, pt.y, 0, hWnd, &rc);
         
  // Destroy the menu. 
  DestroyMenu(hmenu); 
  }


#ifdef TOOLTIP

static BOOL bEnableToolTip = TRUE;
//----------------------------------------------------------------------------
// DoCreateToolTips
//
// Zweck: Anzeige von Tooltips fuer die Tools eines jeden Screens.
//        Jeder Screen verwaltet seine eigenen Tooltip-Fenster
//----------------------------------------------------------------------------
HWND DoCreateToolTips (HWND hWndOwner)
  {
  HWND hWndTT = CreateWindowEx (0, TOOLTIPS_CLASS, (LPSTR) NULL, TTS_ALWAYSTIP, 
                                 CW_USEDEFAULT, CW_USEDEFAULT, 
                                 CW_USEDEFAULT, CW_USEDEFAULT, 
                                 hWndOwner, (HMENU) NULL, hLibInst, NULL);
  if (hWndTT) {
    SendMessage (hWndTT, TTM_SETMAXTIPWIDTH, 0, 300L);
    SendMessage (hWndTT, TTM_ACTIVATE, (WPARAM)bEnableToolTip, 0);
    }

  return hWndTT;
  }
#endif

inline void ScreenList::RelayMouseMessageToToolTip (HWND hWnd, UINT message,
                                                    WPARAM wP, LPARAM lP)
  {
#ifdef TOOLTIP
  if (IsWindow(hWndToolTip)) {
    MSG msg;
    msg.hwnd = hWnd;
    msg.message = message;
    msg.wParam = wP;
    msg.lParam = lP;

    SendMessage (hWndToolTip, TTM_RELAYEVENT, 0, LPARAM(LPMSG(&msg)));
    }
#endif
  }

#ifdef TOOLTIP
//----------------------------------------------------------------------------
// GetMsgProc
//
// Zweck: Schicken der Mausbewegungs-Nachrichten an das Screen-eigene Tooltip.
//        Ist notwendig um fuer Tools, welche eigene Fensterhandles haben
//        (ToolEdit, Listen, ...) auch einen Hilfetext ausgeben zu koennen.
//----------------------------------------------------------------------------
static HHOOK g_hhk;
DLLExport LRESULT _export CALLBACK GetMsgProc (int nCode, WPARAM wParam, LPARAM lParam) 
  { 
  MSG *lpmsg; 

  lpmsg = (MSG *) lParam;

//  if (HookScreen == NULL)
//    return 0;

  if ((nCode < 0) || (HookScreen == NULL) || !IsWindow(HookScreen->hWndToolbar())) {
//    || !(IsChild(HookScreen->hWndToolbar(), lpmsg->hwnd)))
      return (CallNextHookEx(g_hhk, nCode, wParam, lParam));
    }

  char szcln[64];
  GetClassName (lpmsg->hwnd, szcln, sizeof(szcln));
  if (lstrcmp(szcln, "WORDWIN"))
    return (CallNextHookEx(g_hhk, nCode, wParam, lParam));

//    return (CallNextHookEx(HookScreen->g_hhk, nCode, wParam, lParam));

  switch (lpmsg->message) { 
    case WM_MOUSEMOVE: 
    case WM_LBUTTONDOWN: 
    case WM_LBUTTONUP: 
    case WM_RBUTTONDOWN: 
    case WM_RBUTTONUP:
//      if (IsWindow(HookScreen->hWndToolTip)) { 
        HookScreen->RelayMouseMessageToToolTip (lpmsg->hwnd, lpmsg->message,
                                                lpmsg->wParam, lpmsg->lParam);
/*
        MSG msg; 

        msg.lParam = lpmsg->lParam; 
        msg.wParam = lpmsg->wParam; 
        msg.message = lpmsg->message; 
        msg.hwnd = lpmsg->hwnd; 
        SendMessage(HookScreen->hWndToolTip, TTM_RELAYEVENT, 0, 
            (LPARAM) (LPMSG) &msg); 
*/
//      } 
      break; 
    default: 
      break; 
    } 
  return (CallNextHookEx(g_hhk, nCode, wParam, lParam)); 
//  return (CallNextHookEx(HookScreen->g_hhk, nCode, wParam, lParam)); 
  } 

#endif



static BOOL bAbsoluteFocus = FALSE;
extern DWORD WINAPI GetHelpContextNr (void);
extern LPSTR WINAPI GetHelpFile (void);
extern LPSTR WINAPI GetHtmlFile (void);
extern HWND  WINAPI htmlhelp (HWND hWnd, LPCSTR lpstr, 
                                        UINT uint , DWORD dword);


HWND GetActiveMDIWnd ();
static tool FAR *HelpCapt;
DLLExport LONG _export CALLBACK ChildToolBarFunc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  PAINTSTRUCT  ps;
  HDC          hDC, hMemDC ;
 
  ScreenList FAR *screen = (ScreenList FAR *) GetWindowLong (hWnd,GWL_SCREEN);
  if (screen == NULL)
    screen = __tempscreen__ ;
  else
    __tempscreen__ = NULL ;

  if (screen == NULL)   // Kann in Sondernfaellen vorkommen
    return DefWindowProc (hWnd,msg,wP,lP);

#ifdef TOOLTIP
  //-----------------------------------------------------------------
  // Des HookScreen wird fuer die Hook-Prozedur verwendet, um fuer
  // die Tools die eigene Fensterhandles haben die Tooltips anzeigen
  // zu koennen.
  //-----------------------------------------------------------------
  HookScreen = screen;
  if (HookScreen->IstMappe && HookScreen->ChildScreen)
    HookScreen = HookScreen->ChildScreen;
#endif

  LPCLIENTMAP map = (LPCLIENTMAP (GetWindowLong (hWnd,GWL_MAPPTR)));

  if (EditCallBack != NULL) {
    // Vielleicht wills der Editor als ganzes abfangen
    edcmem e;
    e.cm.hWnd = hWnd;
    e.cm.msg = msg ;
    e.cm.wP = wP ;
    e.cm.lP = lP ;
    if ((* EditCallBack) (NULL,hWnd,EDC_CHECKMSG,&e)) return e.cm.RetVal ;
    }

  switch (msg) {
    
    case WM_CREATE:
      {
      LPCREATESTRUCT lpcr = LPCREATESTRUCT(lP);
      screen = (ScreenList FAR *) lpcr->lpCreateParams;
        
      // schreibe einen Zeiger der auf Screen-Daten weist in den Fensterspeicher
      if (IsChildWindow (hWnd))
        screen->hWnd = hWnd;
      SetWindowLong (hWnd,GWL_SCREEN,LONG (screen));
      Capture = NULL;

      int CapSize = 0;
      if ((lpcr->style & WS_CAPTION) && (screen->ScreenNmbr != 0))
        CapSize = ibGetCaptionSize(hWnd) + 2 * GetSystemMetrics(SM_CXDLGFRAME);

      screen->DesiredClientSize = lpcr->cy + CapSize;
      OldSize = screen->DesiredClientSize;
      MoveWindow (hWnd, lpcr->x, lpcr->y, lpcr->cx, screen->DesiredClientSize, TRUE);

#ifdef TOOLTIP
      //-----------------------------------------------------------------
      // Jeder Screen oeffnet eine eigene Hook-Prozedur um die Tooltips
      // fuer seine Kindfenster anzuzeigen
      //-----------------------------------------------------------------
      screen->hWndToolTip = DoCreateToolTips (hWnd);

//      if (IsWindow(screen->hWndToolTip))
//        screen->g_hhk = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc,
//                                         (HINSTANCE) NULL, GetCurrentThreadId()); 
#endif

      }
      break;
    case WM_PAINT :
      hDC = BeginPaint (hWnd, &ps);
      hMemDC = CreateCompatibleDC (hDC);
      screen->Paint (hDC, hMemDC);
      DeleteDC (hMemDC);
      if (map != NULL) {
        map->PaintMap (hDC);
        }
      EndPaint (hWnd, &ps);
      break ;
    case WM_TIMER :
      {
      if ((wP == EDTIMERID) && (EditCallBack != NULL)) {
        edcmem e;
        LONG l = GetMessagePos();
        e.pt.x = LOWORD(l);
        e.pt.y = HIWORD(l);
        ScreenToClient (hWnd,&e.pt);
        if ((* EditCallBack) (NULL,hWnd,EDC_SETCURSOR,&e)) return TRUE ;
        KillEditTimer (hWnd);
        }
      else {
        for ( TimerInfo FAR *x = screen->firsttimer ; x != NULL ; x = x->Next ) {
          if (x->Id == wP) {
            x->h->OnTimer ();
            break ;
            }
          }
        DBWIN_ASSERT (x != NULL);
        }
      }
      break ;

    case WM_LBUTTONDOWN:
      {
      screen->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);

      POINT pt;
#ifdef WIN32
      LONG2POINT(lP, pt);
#else
      pt = MAKEPOINT(lP);
#endif
      if (map != NULL)
        map->HitTest (&pt);

      // Ev. noch die Scriptprozedur aufrufen
      screen->MouseDownProc (&pt, msg);

      Capture = screen->HitTest (&pt);

      if (Capture != NULL) {
        DWORD o = (screen->ToolWithFocus != NULL) ? screen->ToolWithFocus->Param()->hd.ObjId : 0L ;
        DWORD n = Capture->Param()->hd.ObjId ;
        if (FocusChanging != NULL)
          (*FocusChanging) (o,n);
        if (wP & MK_CONTROL) {       // Maus+CTRL
          if ((LOWORD(Capture->Param()->hd.HotKey) != 0) ||
                    (EditCallBack != NULL)) { // im Script wird ein Hotkey angegeben
            ActHotkey = GetHotKey (Capture);                // HotKey suchen und global merken
            FARPROC lpDialogProc = MakeProcInstance (FARPROC(HotKeyDlgProc), hLibInst);
            int iReturn = DialogBox (hLibInst, "HOTKEYS", hWnd, (DLGPROC)lpDialogProc);
            FreeProcInstance (lpDialogProc);
            Capture = NULL;
            }
          else {
            POINT nopt;
            nopt.x = nopt.y = -1;
            tool FAR *old = Capture;
            Capture = NULL;
            old->On_LButtonUp (&nopt);
            MessageBeep (0);
            }
          }
        else {
          if (EditCallBack != NULL) {
            edcmem e;
            e.pt.x = LOWORD(lP);
            e.pt.y = HIWORD(lP);
            if (screen->ToolWithFocus != NULL)
              screen->ToolWithFocus->SetToolFocus (FALSE);   // dem alten Element Focus wegnehmen
            screen->ToolWithFocus = Capture;
            screen->ToolWithFocus->SetToolFocus (TRUE);      // Focus auf neues Element setzen
            (* EditCallBack) (Capture->privData,hWnd,EDC_LBUTTONDOWN,&e);
            SetTimerForEdit (hWnd);
            }
          else {
            if (Capture->IsEnabled) {                    // ist das Element aktivierbar?
              if (Capture->HasTabStop()) {
                if (screen->ToolWithFocus != NULL)
                  screen->ToolWithFocus->SetToolFocus (FALSE);   // dem alten Element Focus wegnehmen
                screen->ToolWithFocus = Capture;
                screen->ToolWithFocus->SetToolFocus (TRUE);      // Focus auf neues Element setzen
                }

              POINT pt;
#ifdef WIN32
              LONG2POINT(lP, pt);
#else
              pt = MAKEPOINT(lP);
#endif
              Capture->On_LButtonDown(&pt);           // ja, dann gehts los
              }
            else {
              MessageBeep (0);                           // nein
              Capture = NULL;                            // es gibt also kein Element
              }
            }
          }
        }
      else {
        if (EditCallBack != NULL) {
          edcmem e;
          e.pt.x = LOWORD(lP);
          e.pt.y = HIWORD(lP);
          (* EditCallBack) (NULL,hWnd,EDC_LBUTTONDOWN,&e);
          SetTimerForEdit (hWnd);
          }
        }
      HWND FocusWnd = GetFocus();
      if (IsWindow(FocusWnd)) {
        char lpszClassName[30];
    
        GetClassName (FocusWnd, lpszClassName, sizeof(lpszClassName));
        if ((FocusWnd != hWnd) && (lstrcmp(lpszClassName, szWWName)))
          SetFocus (hWnd);
        }
      else {
        SetFocus (hWnd);
        }
      }  
      break ;

    case WM_LBUTTONUP:
      screen->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);

      if (EditCallBack != NULL) {
        edcmem e;
        e.pt.x = LOWORD(lP);
        e.pt.y = HIWORD(lP);
        (* EditCallBack) ((Capture != NULL) ? Capture->privData : NULL,hWnd,EDC_LBUTTONUP,&e);
        Capture = NULL;
        }
      else {
        if (Capture != NULL) {
          tool FAR *old = Capture;
          Capture = NULL;

          POINT pt;
#ifdef WIN32
          LONG2POINT(lP, pt);
#else
          pt = MAKEPOINT(lP);
#endif
          if (!old->On_LButtonUp(&pt))
            Capture = old;
          }
        }
      HelpCapt = NULL;
      break ;

    case WM_MOUSEMOVE:
      {
      screen->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);

      POINT pt;

#ifdef WIN32
      LONG2POINT(lP, pt);
#else
      pt = MAKEPOINT(lP);
#endif

      if (EditCallBack != NULL) {
        edcmem e;
        e.pt.x = LOWORD(lP);
        e.pt.y = HIWORD(lP);
        (* EditCallBack) ((Capture != NULL) ? Capture->privData : NULL,hWnd,EDC_MOUSEMOVE,&e);
        }
      else {
        if (Capture != NULL) {
          Capture->On_MouseMove(&pt);
          }
        else {
          screen->OnMouseMove (wP,lP);
          }
        }
      }
      break;

    case WM_LBUTTONDBLCLK:
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT(lP, pt);
#else
      pt = MAKEPOINT(lP);
#endif

      Capture = screen->HitTest (&pt);
      if (EditCallBack != NULL) {
        if (Capture != NULL) {
          edcmem e;
          e.pt.x = LOWORD(lP);
          e.pt.y = HIWORD(lP);
          (* EditCallBack) (Capture->privData,hWnd,EDC_LBUTTONDBLCLK,&e);
          }
        }
      else {
        if (Capture != NULL) {
          if (Capture->IsEnabled)
            Capture->On_LButtonDown(&pt);
          else
            Capture = NULL;  
          }
        }
      }
      break;

    case WM_RBUTTONDOWN:
      {
      screen->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);
        
      POINT pt;
#ifdef WIN32
      LONG2POINT(lP, pt);
#else
      pt = MAKEPOINT(lP);
#endif

      if (map != NULL)
        map->OnRButtonDown (&pt);

      screen->MouseDownProc (&pt, msg);

      HelpCapt = screen->HitTest (&pt);
      if (HelpCapt != NULL) {
        HotKey FAR* AHk = GetHotKey (Capture);                // HotKey suchen und global merken

        RECT rc;
        GetClientRect(hWnd, (LPRECT) &rc);
        if (PtInRect((LPRECT) &rc, pt)) {
          HandlePopupMenu (hWnd, pt, HelpCapt,NULL);
          }
        }
      }
      break;

    case WM_RBUTTONUP:
      screen->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);
      // ignorieren
      HelpCapt = NULL;
      break;

    case WM_INITMENUPOPUP :
      {
      // ueberprueft ob Daten in der Zwischenablage => Aenderung des Menueintrages
      HMENU hMenu = HMENU(wP);
      if (OpenClipboard (hWnd)) {
        UINT flag = (IsClipboardFormatAvailable(CF_TEXT) || 
                     IsClipboardFormatAvailable(CF_OEMTEXT)) ? MF_ENABLED : MF_GRAYED;
        EnableMenuItem (hMenu, IDM_PASTE, flag);

        CloseClipboard();  
        return TRUE;
        }
      else            // Clipboard nicht verfuegbar
        return FALSE;  
      }
      
      return TRUE;
      break;


    case WMU_DESTROYBUBBLE:
      {
      if (HelpCapt != NULL) {
        ReleaseCapture ();
        HelpCapt->RemoveHelp();
        HelpCapt = NULL;
        }

      if (map != NULL)
        map->OnMsg (hWnd, msg, wP, lP);

      }
      break;

    case WM_CHAR :
      if (EditCallBack != NULL) {
        edcmem e;
        e.ch = char(wP);
        if (screen->ToolWithFocus != NULL)
          (* EditCallBack) (screen->ToolWithFocus->privData, hWnd, EDC_CHAR, &e);
        }
      break ;
    case WM_KEYDOWN:
      if (((HelpCapt != NULL) && (HelpCapt->hWndBubble != NULL)) ||
          ((map != NULL) && (map->HelpElem != NULL))) {
        SendMessage(hWnd, WMU_DESTROYBUBBLE, 0, 0L);
        break;
        }
      else
      if ((IsListKey (wP)) && (SendToList (hWnd,msg,wP,lP)))
        break ;
      else {
        switch (wP) {
          case VK_TAB : 
            {
            DWORD o = (screen->ToolWithFocus != NULL) ? screen->ToolWithFocus->Param()->hd.ObjId : 0L ;
            screen->TabToNextElement ();
            DWORD n = (screen->ToolWithFocus != NULL) ? screen->ToolWithFocus->Param()->hd.ObjId : 0L ;
            if (FocusChanging != NULL)
              (*FocusChanging) (o,n);
            }
            break;
          default :
            if (screen->ToolWithFocus != NULL)
              screen->ToolWithFocus->OnChar (wP);
          }
        }
      break ;

    case WM_WINDOWPOSCHANGING:
      {
      WINDOWPOS FAR* pwp = (WINDOWPOS FAR*)lP;
      if (screen->IstMappe)
        pwp->flags |= SWP_NOZORDER;
        
      // diesen ganzen Sch... nur weil sich der Dialog-Editor
      // in die Groessen-Aenderung einmischt
      if (EditCallBack != NULL) {
        // zuerst kommt einmal das "MoveWindow" aus "WM_CREATE"
        if (screen->doNCPaint) {
          // nur wenn eine Groessenaenderung erfolgen soll, wird der 
          // Client-Bereich automatisch um die Caption-Hoehe erweitert!
          if (!(pwp->flags & SWP_NOSIZE)) {
            if ((pwp->cy > 0) && (pwp->cy != OldSize)) {  
              screen->DesiredClientSize = pwp->cy + ibGetCaptionSize(hWnd) +
                                          2 * GetSystemMetrics(SM_CXDLGFRAME);
              pwp->cy = screen->DesiredClientSize;
              OldSize = pwp->cy;
              }
            }
          }
        }  
          
      return screen->MyDefWindowProc (hWnd, msg, wP, lP);
      }
      break;

    case WM_WINDOWPOSCHANGED:
      {
      WINDOWPOS FAR* pwp = (WINDOWPOS FAR*)lP;
      if (screen != NULL) {
        LONG RetVal = ibDefWindowProc (hWnd, msg, wP, lP);

        if (screen->hWnd) {    // gibt es ein Kindfenster?
          if (pwp->flags & SWP_NOMOVE) {                   // es darf nicht verschiebbar sein
            HWND hWParent = GetParent(hWnd);
            if (IsWindow (hWParent))
              SendMessage (GetParent(hWnd), UM_TOOLBARCHANGED, 0, 0);
            }
          }
        return RetVal;
        }
      else
        return DefWindowProc (hWnd,msg,wP,lP);
      }
      break;

    //--------------------------------------------------------------
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      //------------------------------------------------------------
      // da wird ein bisschen geschwindelt, weil die Strukturen in
      // lParam verpackt wurden! D.h. man muss aufpassen ob man das
      // echte Fensterhandle benoetigt oder ob das Fensterhandle
      // fuer eine andere Variable missbraucht wurde!
      //------------------------------------------------------------
      WORD wNotify = lP != 0 ? WORD(LOCHUNK(lP)) : 0;
      HWND whWnd   = lP != 0 ? HWND(HICHUNK(lP)) : 0;

      // dieses Kommando kommt nur vom Popupmenu (WM_RBUTTONDOWN)
      if ((HelpCapt != NULL) && (HelpCapt->hWndBubble == NULL)) {
        if (HelpCapt->OnCommand (hWnd, wP)) {
/*
//          HelpCapt = NULL;                 // Danke ich brauch's nimmer mehr
//          break;
//          }
//        else
*/
          if ((HelpCapt != NULL) && (HelpCapt->hWndBubble == NULL))
            HelpCapt = NULL;
          }
        }
        
      if (CRACKER_wID == MI_H_Help_DDS) {

#ifdef WINHELP
        BOOL bResult;
        DWORD ContextNr = GetHelpContextNr();
#ifdef WIN32
        if (ContextNr < 0)
          bResult = WinHelp (hWnd, GetHelpFile(), HELP_FINDER, 0);
        else
#endif

        bResult = WinHelp (hWnd, GetHelpFile(), HELP_CONTEXT, ContextNr);
#else
        HWND wnd = htmlhelp(hWnd, GetHtmlFile(), HH_DISPLAY_TOPIC, NULL);
                                
#endif
        }

      switch (wNotify) {
          case EN_CHANGE :
          {
          tool FAR *t = screen->Search (CRACKER_wID);
          if (t != NULL)
            t->OnChange ();
          }
          break;
        case WW_CHAR :
          if ((HelpCapt != NULL) && (HelpCapt->hWndBubble != NULL)) {
            SendMessage(hWnd, WMU_DESTROYBUBBLE, 0, 0L);
            }
          if ((WORD)whWnd == '\t') {       
            screen->TabToNextElement ();
            return TRUE;
            }
          else {
            ToolEdit FAR *e = (ToolEdit FAR *) screen->Search (CRACKER_wID) ;
            if (e != NULL)
              return LONG (e->OnChar ((WORD)whWnd));
            else
              return FALSE ;
            }
          break;
        case WW_KEYDOWN :
          {
          ToolEdit FAR *e = (ToolEdit FAR *) screen->Search (CRACKER_wID) ;
          if (e != NULL)
            return LONG (e->IsCharCallbackInstalled ((WORD)whWnd));
          else
            return FALSE ;
          }
          break;
        case WW_RBUTTONDOWN :
/*        
          if (GetCapture () == NULL) {
            DBWIN_ASSERT(HelpCapt == NULL);
            HelpCapt = screen->Search(CRACKER_wID) ;
            if (HelpCapt != NULL) {
              LONG h = GetMessagePos();
              POINT pt;

    #ifdef WIN32
              LONG2POINT(h, pt);
    #else
              pt = MAKEPOINT(h);
    #endif

              ScreenToClient (hWnd, &pt);
              HelpCapt->GetHelp (pt);
              if (HelpCapt->hWndBubble != NULL)
                SetCapture (HelpCapt->hWndBubble);
              else
                HelpCapt = NULL;
              }
            }
*/
          HelpCapt = screen->Search(CRACKER_wID) ;
          if (HelpCapt != NULL) {
            LONG h = GetMessagePos();
            POINT pt;

  #ifdef WIN32
            LONG2POINT(h, pt);
  #else
            pt = MAKEPOINT(h);
  #endif

            ScreenToClient (hWnd, &pt);
            HandlePopupMenu (hWnd, pt, HelpCapt,NULL);
            }
          
          break;

        case DDSLIST_LBUTTON :     // linke Maustaste in DIALED.CPP
        case WW_LBUTTON :
          {
          tool *h = screen->Search(CRACKER_wID);
          if (h != NULL) {
            if (wNotify == WW_LBUTTON)
              ((ToolEdit FAR *)h)->OnCaretPosChanged ();
            if (screen->ToolWithFocus != h) {
              if (screen->ToolWithFocus != NULL)
                screen->ToolWithFocus->SetToolFocus (FALSE);

    //            screen->ToolWithFocus = h ;


              if (EditCallBack == NULL)
                while ((!h->HasTabStop()) && (screen->ToolWithFocus != h))
                  h = h->GetNext();   // suche das naechste Element mit Tabstop

              screen->ToolWithFocus = h;
              screen->ToolWithFocus->SetToolFocus (TRUE);
              }
            }
          if (EditCallBack != NULL) {
            edcmem e;
            LONG l = GetMessagePos();
            e.pt.x = LOWORD(l);
            e.pt.y = HIWORD(l);
            ScreenToClient (hWnd,&e.pt);
            (* EditCallBack) ((h != NULL) ? h->privData : h,hWnd,EDC_LBUTTONDOWN,&e);
            SetTimerForEdit (hWnd);
            return (1L);  // zeigt dass es eine CallBack-Funktion gibt!!
            }
          }
          break;
        case WW_LBUTTONDBLCLK :
          {
          tool *h = screen->Search(CRACKER_wID);
          if (EditCallBack != NULL) {
            edcmem e;
            LONG l = GetMessagePos();
            e.pt.x = LOWORD(l);
            e.pt.y = HIWORD(l);
            ScreenToClient (hWnd,&e.pt);
            (* EditCallBack) ((h != NULL) ? h->privData : h, hWnd, EDC_LBUTTONDBLCLK, &e);
            }
          else
            h->HotKeyAction(FALSE);  
          }
          break;
        case WW_CARETPOSCHG :
          {
          ToolEdit FAR *e = (ToolEdit FAR *) screen->Search (CRACKER_wID);
          if (e != NULL)
            e->OnCaretPosChanged ();
          }
          break;
        case WW_WORKON :
          {
          ToolEdit FAR *e = (ToolEdit FAR *) screen->Search (CRACKER_wID);
          if (e != NULL)
            e->OnWorkOn ();
          }
          break;
        case DDSLIST_TABPRESSED :
          screen->TabToNextElement ();
          break;
        case WW_ONSETFOCUS :
          {
          tool *h = screen->Search(CRACKER_wID);
          if (h != NULL)
            h->OnSetFocus ();
          }
          break;
      
        // ein WORDWIN oder ExternTool verliert den Focus
        //-------------------------------------------------
        case WW_ONKILLFOCUS :
          {
          tool *h = screen->Search(CRACKER_wID);
          if (h != NULL) {
            DWORD o = h->Param()->hd.ObjId ;
            if (FocusChanging != NULL)
              (*FocusChanging) (o,0L);

            }
          if (h != NULL) {
            BOOL bCloseScreen = FALSE;
            HWND hWndNewFocus = whWnd;  // wer bekommt den Focus?
            if (IsWindow(hWndNewFocus)) {

              // alle Screens durchgehen und deren Fensterhandles ueberpruefen.
              for (ScreenList FAR *hsc = FirstScreen ; hsc != NULL ; hsc = hsc->Next) {
                // Der eigene Screen darf natuerlich nicht den Focus verlieren,
                // das Handle des Screens muss dem neuen Focus-Window gleichen
                // oder im Falle des CreateScreens war es noch nicht bekannt.
                if ((hsc != screen) && ((hsc->hWnd == hWndNewFocus) || (hsc->hWnd == 0))) {
                  screen->OnKillFocus (WPARAM(whWnd));
                  bCloseScreen = TRUE;
                  break;
                  }
                }

              //---------------------------------------------------------
              // Ueberpruefen ob die Killfocus-Prozedur des ToolEdits
              // aufgerufen werden soll.
              // dazu werden "Owner" oder "Parents" (Kindfenster haben
              // keinen Owner) solange ermittelt, bis das Hauptfenster
              // der Anwendung gefunden wurde oder kein gueltiges Handle
              // vorliegt.  
              // Bei einem Applikationswechsel ist der Owner sofor NULL
              //---------------------------------------------------------
              HWND hWndOwner = NULL;
              if (GetWindowLong(hWndNewFocus, GWL_STYLE) & WS_CHILD)
                hWndOwner = GetParent (hWndNewFocus);
              else
                hWndOwner = GetWindow(hWndNewFocus, GW_OWNER);

              while (hWndOwner && (hWndOwner != hFrameWnd)) {
                if (GetWindowLong(hWndOwner, GWL_STYLE) & WS_CHILD)
                  hWndOwner = GetParent (hWndOwner);
                else
                  hWndOwner = GetWindow(hWndOwner, GW_OWNER);
                }

              if (!bCloseScreen && hWndOwner)
                h->OnKillFocus ();
              }     // IsWindow(hWndNewFocus)
            }  
          }
          break;
        }  // switch (HIWORD(lp))
      break ;
      }

    case WM_PARENTNOTIFY :
      // sucht das Element im Toolbar, welches die Id <lParamHi> hat
      {
      tool FAR *h = screen->Search (HIWORD(lP));
      if (h != NULL) 
        h->OnParentNotify (wP);
      }
      break ;

    case WMU_NEEDFOCUS :
      {
      SetFocus (HWND(wP));
      break;
      }

    case WM_SETFOCUS :
      {
      if (screen->nonmodal) 
        break;
      
      if ((screen->ToolWithFocus != NULL) && (IsWindow(HWND(wP)))) {
        char szFileName[256];
        LPSTR lpszFileName;
        int i;
        
#ifdef WIN32
        GetModuleFileName (HMODULE(GetWindowLong (HWND(wP), GWL_HINSTANCE)), 
                           szFileName, sizeof(szFileName));
#else
        GetModuleFileName (GetWindowWord (HWND(wP), GWW_HINSTANCE), 
                           szFileName, sizeof(szFileName));
#endif
        for (i = lstrlen(szFileName); ((i > 0) && (szFileName[i] != '\\')); i--);
        lpszFileName = szFileName+i+1;

        // wurde das alte Element in der Zwischenzeit disabled, dann wird
        // zum naechsten verfuegbaren Element weitergeschaltet.
        if (screen->ToolWithFocus->HasTabStop())
          screen->ToolWithFocus->SetToolFocus (TRUE, !lstrcmp(lpszFileName, "DDS.EXE"));
        else {
          screen->TabToNextElement ();
          }
        }
#ifdef INITHOTKEYS      
      for (WndList FAR *Wnd = screen->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
        for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
          h->InitHotKey ();

      // Bekommt der Haupt-Toolbar den Focus, werden auch die 
      // Mappen-Hotkeys wieder initialisiert.
      if (screen == MainScreen) {
        // Mal nachsehen obs eine Mappe gibt
        for (ScreenList FAR *h = FirstScreen ; h != NULL ; h = h->Next) {
          if (h->IstMappe) {
              for (WndList FAR *Wnd = h->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next) {
                for (tool FAR *x = Wnd->first ; x != NULL ; x = x->Next)
                  x->InitHotKey ();
              }
            }
          }
        }
#endif      

      
      // bei Mappenschirmen unbedingt auf Submappen achten und den Focus
      // weitergeben
      //-----------------------------------------------------------------
      else if (screen->IstMappe) {
        if (screen->ChildScreen != NULL)
          SetFocus (screen->ChildScreen->hWndToolbar());
        }
        
      SendMessage (hFrameWnd,WM_QUERYNEWPALETTE,NULL,NULL);
      }
      break;

      
    case WM_KILLFOCUS :
      {
      if ((HelpCapt != NULL) ||
          ((map != NULL) && (map->HelpElem != NULL)))
        SendMessage(hWnd, WMU_DESTROYBUBBLE, 0, 0L);
      screen->OnKillFocus (wP);
      break;  
      }

    case WM_SETCURSOR :
      if (EditCallBack != NULL) {
        edcmem e;
        LONG l = GetMessagePos();
        e.pt.x = LOWORD(l);
        e.pt.y = HIWORD(l);
        ScreenToClient (hWnd,&e.pt);
        if ((* EditCallBack) (NULL,hWnd,EDC_SETCURSOR,&e)) return TRUE ;
        }
      return screen->MyDefWindowProc (hWnd, msg, wP, lP);
      break ;

    case WM_ERASEBKGND:
      {
      if (map != NULL)
        map->EraseBkGnd (hWnd,HDC (wP));

      if (screen != MainScreen)
        return screen->MyDefWindowProc (hWnd, msg, wP, lP);
        
      RECT rc;
      HDC  hDC, hMemDC;
      BITMAP bm;
      
      hDC = HDC(wP);
      GetClientRect (hWnd, &rc);
      
      hMemDC = CreateCompatibleDC (hDC);
      SelectObject (hMemDC, Leather);
      GetObject (Leather, sizeof(BITMAP), &bm);
      
      int x;
      int y = 0;
      while (y <= rc.bottom-rc.top) {
        x = 0;
        while (x <= rc.right-rc.left) {
          BitBlt (hDC, x, y, bm.bmWidth, bm.bmHeight,
                  hMemDC, 0, 0, SRCCOPY);
          x += bm.bmWidth;
          }
          
        y += bm.bmHeight;  
        }          

      DeleteDC (hMemDC);
      }
      return 1L;
      break;

    case WM_PALETTECHANGED :
      if (hWnd == HWND(wP))
        break;

    case WM_QUERYNEWPALETTE :
      screen->OnQueryNewPalette (msg);
      return 1L;
      break;

    case WM_DESTROY:
      HelpCapt = NULL;

#ifdef TOOLTIP
//      if (IsWindow(screen->hWndToolTip)) {
      if (screen->hWndToolTip) {
//        UnhookWindowsHookEx (screen->g_hhk);
        screen->g_hhk = NULL;
        DestroyWindow (screen->hWndToolTip);
        screen->hWndToolTip = NULL;
        }
#endif


      // break; ! No Break, damit die Daten wieder freigegeben werden !

    default :
      return screen->MyDefWindowProc (hWnd, msg, wP, lP);
    }
  return 0L;
  }


static int ToolBarLogWidth;
DLLExport int  _export WINAPI ToolBarWidth ()
  {
  return (int)(BaseUnit*ToolBarLogWidth);
  }


/*------------------------------------------------------------------*\
* export function: CreateToolBar                                     *
*                                                                    *  
* Parameter:    ScreenId ....                                        *  
*               Parent ......                                        *
*               ScreenNbr ...                                        *
*               PosRef ......                                        *
*               Attr ........                                        *
*               privData ....                                        *
*               pdSize ......                                        *
*               x, y ........                                        *
* Zweck:                                                             *
\*------------------------------------------------------------------*/
DLLExport HWND _export WINAPI CreateToolBar (DWORD ScreenId,HWND Parent,int ScreenNmbr,
                                       DWORD PosRef, LPWINDOWATTR Attr, LPVOID privData,int pdSize,
                                       int x,int y,BOOL ModalScreen,BOOL MapScreen,
                                       LPVOID par)
  {
  HWND res;

  ScreenList FAR *screen;
  if (ScreenNmbr == 0) {
    //--------------------------
    // erzeuge den Haupt-ToolBar
    hFrameWnd = Parent;

    screen = new ScreenList (ScreenNmbr,privData,pdSize);
    screen->ScreenId = ScreenId;
    screen->PosRef   = PosRef;
    screen->Attr = *Attr;

    __tempscreen__ = screen;
    ToolBarLogWidth = Attr->w;
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER;
    res = CreateWindow (szClassName, "", dwStyle,
                         x, y, ToolBarWidth(), 
                         Attr->h,
                         Parent, 0, hLibInst, LPVOID(screen)
                        );
    SetWindowPos (res, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE);
    MainScreen = LPSCREEN (GetWindowLong (res,GWL_SCREEN));
    }
  else {
    // ab jetzt kommen nur mehr Popup_Toolbars
    POINT  pt;

    //--------------------------------------------------
    // Die Mappe hat nat¸rlich eine vorgegeben Position
    //--------------------------------------------------
    if (MapScreen) {
      pt.x = x ;
      pt.y = y ;
      }
    else {
      POPUPPOS FAR* Pos = (POPUPPOS FAR*) (* GetData) (privData, PosRef);
      // keine Position angegeben => Dialogbox zentrieren
      if (Pos == NULL) {
        //--------------------------------------------------------------------
        // Multiple Monitor support!!!!!
        //--------------------------------------------------------------------
        HMONITOR hMonitor;
        MONITORINFO mi;
        RECT rcMon;

        //---------------------------------------------------------
        // Der Bursche schaut nach wo das Elternfenster liegt und
        // holt sich die Information ueber diesen Schirm.
        //---------------------------------------------------------
        hMonitor = MonitorFromWindow(Parent, MONITOR_DEFAULTTONEAREST);

        mi.cbSize = sizeof(mi);
        GetMonitorInfo(hMonitor, &mi);

        rcMon = mi.rcMonitor;

        //--------------------------------------------------------------------
        // Da man nicht laenger weiss wo der Ursprung des Koordinatensystems
        // ist muss man die Berechnung ueber rcMon durchfuehren. Ist man
        // am primaeren Monitor, dann sind rcMon.left und rcMon.top 0
        //--------------------------------------------------------------------
        pt.x = rcMon.left + ((rcMon.right - rcMon.left) - 
                             (int)(BaseUnit*Attr->w)) / 2;
        pt.y = rcMon.top  + ((rcMon.bottom - rcMon.top)  - 
                             (int)(BaseUnit*Attr->h)) / 2;
        } 
      else {
        pt.x = Pos->ptPos.x;
        pt.y = Pos->ptPos.y;
        }
      }

    if (MapScreen) {
      screen = new MapScreenList (ScreenNmbr,privData,pdSize);
      screen->IstMappe = TRUE;
      // suche den Screen der das Fensterhandle <Parent> hat;
      // Das ist jetzt mein Parent, und ich bin sein Kind!
      for ( ScreenList FAR *sc = FirstScreen ; sc != NULL ; sc = sc->Next)
        if (sc->hWnd == Parent) {
          screen->ParentScreen = sc;
          sc->ChildScreen = screen;
          break;
          }
      }
    else
      screen = new ScreenList (ScreenNmbr,privData,pdSize);
    screen->Attr = *Attr;


    // Popup-Fenster haben natuerlich kein Handle auf ein Kindfenster
    if (ModalScreen) {
      if ((IsWindow(lastModalScreen)) && (IsWindowVisible (lastModalScreen))) {
        Parent = lastModalScreen;
        screen->modalParent = lastModalScreen;
        }
      else {
        HWND hWndActive = CTOOL_GetActiveTopWindow ();
        if (IsWindow (hWndActive))
          Parent = hWndActive;
        }
      screen->doNCPaint = TRUE;
      __tempscreen__ = screen;
      screen->hWnd = 
           CreateWindow (szClassName, screen->Attr.Title, 
                         screen->Attr.Style,
                         pt.x, pt.y, 
                         (int)(BaseUnit*screen->Attr.w), (int)(BaseUnit*screen->Attr.h), 
                         Parent, 0, hLibInst, LPVOID(screen)
                        );
      screen->DisableParent (Parent);
      lastModalScreen = screen->hWnd;
      }
    else if (MapScreen) {
      screen->nonmodal = FALSE ;
      __tempscreen__ = screen ;
      screen->hWnd = 
           CreateWindow (szClassName, "", 
                         WS_OVERLAPPED | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                         pt.x, pt.y, 
                         Attr->w, Attr->h, 
                         Parent, 0, hLibInst, LPVOID(screen)
                        );
      }
    else {
      screen->nonmodal = TRUE ;
      screen->doNCPaint = TRUE;
      __tempscreen__ = screen ;
      screen->hWnd = 
           CreateWindow (szClassName, screen->Attr.Title, 
                         screen->Attr.Style,
                         pt.x, pt.y, 
                         (int)(BaseUnit*screen->Attr.w), (int)(BaseUnit*screen->Attr.h), 
                         GetDesktopWindow(), 0, hLibInst, LPVOID(screen)
                        );
      SetWindowPos (screen->hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
      }

    DefFunc = (FARPROC)SetWindowLong(screen->hWnd,
                                     GWL_WNDPROC, (LONG)PopUpToolBarFunc);
    res = screen->hWnd ;

    screen->WindowPos.ptPos.x = short (pt.x);
    screen->WindowPos.ptPos.y = short (pt.y);

    screen->ScreenId = ScreenId;
    screen->PosRef   = PosRef;
    }

  // schreibe einen Zeiger der auf Screen-Daten weist in die Datenbank
  (* SetData) (privData,ScreenId,&screen,sizeof(LPVOID),NULL);

  screen->dlgWidth = Attr->w;
  screen->dlgHeight = Attr->h;

  return res;
  }

/*------------------------------------------------------------*\
*    DestroyToolBar                                            *
\*------------------------------------------------------------*/
HWND ExchangeWindow (HWND hParent,HWND hMyWnd,HWND hNewModalParent,HWND hNewDisableWindow)
  {
  ScreenList FAR *sc = (ScreenList FAR *) GetWindowLong (hParent,GWL_SCREEN);
  ScreenList FAR *mysc = (ScreenList FAR *) GetWindowLong (hMyWnd,GWL_SCREEN);
  if (mysc != NULL) {
    mysc->disabledWindow = hNewDisableWindow ;
    mysc->modalParent = hNewModalParent ;
    EnableWindow (hNewDisableWindow,FALSE);
    // Da Windows keine Methode zum Aendern des Owners zur Verfuegung 
    // stellt, muss ein neues Fenster erzeugt werden
    SetWindowLong (mysc->hWnd,GWL_SCREEN,0L);
    __tempscreen__ = mysc;
    mysc->hWnd = 
          CreateWindow (szClassName, mysc->Attr.Title, 
                        mysc->Attr.Style,
                        mysc->WindowPos.ptPos.x, mysc->WindowPos.ptPos.y, 
                        (int)(BaseUnit*mysc->Attr.w), (int)(BaseUnit*mysc->Attr.h), 
                        mysc->disabledWindow, 0, hLibInst, LPVOID(mysc)
                      );
    lastModalScreen = mysc->hWnd;
    // Und alle Kindfender des alten Windows dem neuen Window zuordnen
    for (HWND hwChild = GetWindow(hMyWnd,GW_CHILD); hwChild != NULL ; hwChild = GetWindow(hMyWnd,GW_CHILD)) {
      SetParent (hwChild,mysc->hWnd);
      }
    DefFunc = (FARPROC)SetWindowLong(mysc->hWnd,
                              GWL_WNDPROC, (LONG)PopUpToolBarFunc);
    for (WndList FAR *h = mysc->FirstWnd ; h != NULL ; h = h->Next ) {
      for ( tool FAR *x = h->first ; x != NULL ; x = x->Next ) {
        x->NewWindow (mysc->hWnd);
        }
      }
    ShowWindow (mysc->hWnd,SW_SHOW);
    }
  return mysc->hWnd;
  }

DLLExport void _export WINAPI DestroyToolBar (ScreenList FAR *sc)
  {
  DBWIN_ASSERT (sc != NULL);
  // Nur loeschen lassen, wenn alle Elemente verschwunden sind
  //////////////////////////////////////////////////////////////

  HelpCapt = NULL;

  if (sc->WritePosRef ())
    (* SetData) (sc->privData,sc->PosRef,&sc->WindowPos,sizeof(POPUPPOS),NULL);
  sc->destroyIsDone = TRUE ;

  HWND WndStack[30],ParentStack[30];
  if (sc->FirstWnd == NULL) {
    if (sc == MainScreen)  
      MainScreen = NULL;


    if (sc->ParentScreen != NULL) {
      if (sc->ParentScreen->ChildScreen == sc) sc->ParentScreen->ChildScreen = NULL ;
      }

    BOOL newHistorySet = FALSE ;
    if (sc->hWnd == lastModalScreen) lastModalScreen = 0;
    else if ((!sc->nonmodal) && (IsWindow (lastModalScreen))) {
      // Untersuchen, ob der geloeschte Schirm in der Kette des aktuell
      // modalen Schirmes vorkommt -> rausloeschen
      HWND hMyWnd = lastModalScreen;
      HWND hParent = GetParent (hMyWnd);
      for ( int i = 0 ; IsWindow(hParent) ; i ++ ) {
        if (hParent == sc->hWnd) {
          ScreenList FAR *mysc = (ScreenList FAR *) GetWindowLong (hMyWnd,GWL_SCREEN);
          WndStack[i] = hMyWnd;
          ParentStack[i] = hParent; // Das letzte Paar noch einmal auf den Stack geben
          if (mysc != NULL) {
            // Das ganze noch einmal verkehrt herum, wobei die Fenster neu erzeugt werden
            // muessen
            hMyWnd = lastModalScreen ;
            hParent = GetParent (hMyWnd);
            HWND lastWindowCreated,hNewModalParent,hNewDisableWindow;
            for ( int j = i ; j >= 0 ; j -- ) {
              if (j == i) {
                hNewModalParent = sc->modalParent;
                hNewDisableWindow = sc->disabledWindow;
                }
              else {
                hNewModalParent = lastWindowCreated;
                hNewDisableWindow = lastWindowCreated;
                }
              lastWindowCreated = 
                ExchangeWindow (ParentStack[j],WndStack[j],hNewModalParent,hNewDisableWindow) ;
              } ;
            newHistorySet = TRUE ;
            }
          break ;
          }
        WndStack[i] = hMyWnd;
        ParentStack[i] = hParent;
        hMyWnd = hParent;
        hParent = GetParent (hMyWnd);
        }
      }
    if ((sc->doNCPaint) && (!newHistorySet))
      sc->EnableParent ();

    LPVOID privData = sc->privData;
    LPVOID mouseprivData = sc->mouseprivData;
    DWORD ScreenId = sc->ScreenId;
    sc->destroyIsDone = TRUE ;

    // Achtung: Der Screen wird in WM_DESTROY geloescht
    if (IsWindow (sc->hWnd))
      DestroyWindow (sc->hWnd);

    LPVOID nw = NULL ;
    if (ScreenId != 0)
      (* SetData) (privData,ScreenId,&nw,sizeof(LPVOID),NULL);

    // Jetzt koennen auch die privaten Daten freigegeben werden
    (* FreePrivData) (privData);
    FreeGlobMem (privData);
    if (mouseprivData != NULL) {
      (* FreePrivData) (mouseprivData);
      FreeGlobMem (mouseprivData);
      }
    }
  }

float getBaseUnit() {
  double screenRatio = double(GetSystemMetrics (SM_CXSCREEN)) / double(GetSystemMetrics (SM_CYSCREEN));
  if (screenRatio > 1.34)
    return float (double (GetSystemMetrics (SM_CXSCREEN)) / screenRatio * 1.34 / 426.6666) ;
  else
    return float (double (GetSystemMetrics (SM_CXSCREEN)) / 426.6666) ;
  }

/*------------------------------------------------------------------*\
* export function: Initialize                                        *
*                                                                    *  
* Parameter:    g .....                                              *  
*               s .....                                              *
*               sc ....                                              *
*               cc ....                                              *
*               cmd ...                                              *
* Zweck:                                                             *
\*------------------------------------------------------------------*/
HBRUSH MyBackGround;
static float BaseUnit_n;
DLLExport BOOL _export WINAPI Initialize (GETDATA g,SETDATA s,SETCONNECTION sc,CLEARCONNECTION cc,CALLCOMMAND cmd,GETRESOURCE gs,GETEXTFUNC gf,ISUPDATEFROM is)
  {
  WNDCLASS wc;
  LOGBRUSH LBrush;

  GetData = g;
  SetData = s;
  SetConnection = sc ;
  ClearConnection = cc ;
  CallCommand = cmd;
  GetResource = gs;
  GetExtFnc = gf;
  IsUpdateFrom = is;

/*
  dwVersion = GetVersion();
  if (dwVersion < 0x80000000) {
   // Windows NT
   }
   else if (LOBYTE(LOWORD(dwVersion))<4) {
   // Win32s
   } else {
   // Windows 95
   }
*/
/*
  WindowsVersion = LOWORD(GetVersion());       
  WindowsVersion = (((WORD)(LOBYTE(WindowsVersion))) << 8) |
                     (WORD)HIBYTE(WindowsVersion);
*/
#ifdef TOOLTIP
//  INITCOMMONCONTROLSEX iccex;
//  iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
//  iccex.dwICC = ICC_BAR_CLASSES;
//  InitCommonControlsEx(&iccex);
  InitCommonControls();


  g_hhk = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc,
                           (HINSTANCE) NULL, GetCurrentThreadId());
#endif


  HelvFont = CreateFont (8, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0,
                         FF_SWISS, "Ms Sans Serif");

  Leather = (HBITMAP)LoadBitmap (hLibInst, "LEATHER");

  MultiOn = (HBITMAP)LoadBitmap (hLibInst, "MULTION");
  MultiOff = (HBITMAP)LoadBitmap (hLibInst, "MULTIOFF");

  hBmpMappeDisabled = (HBITMAP)LoadBitmap (hLibInst, "HAND");

  HDC hDC = CreateDC ("DISPLAY", 0, 0, 0);
  BaseUnit_n = float (GetDeviceCaps(hDC, LOGPIXELSX)/40.0);
  BaseUnit = getBaseUnit();
  DeleteDC (hDC);

  LBrush.lbStyle = BS_PATTERN;

#ifdef WIN32
  LBrush.lbHatch = LONG(LoadBitmap (hLibInst, "DN_PATTERN"));
#else
  LBrush.lbHatch = LoadBitmap (hLibInst, "DN_PATTERN");
#endif

  DnBrush = CreateBrushIndirect (&LBrush);
  DeleteObject (HBITMAP(LBrush.lbHatch));

  UnrealizeObject (DnBrush);

  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_GLOBALCLASS;
  wc.lpfnWndProc   = ChildToolBarFunc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 2 * sizeof(LPVOID);
  wc.hInstance     = hLibInst;
  wc.hIcon         = 0;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;

  if (!RegisterClass(&wc))
    return FALSE;


  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS | CS_SAVEBITS;
  wc.lpfnWndProc   = BubbleWinFunc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 8;
  wc.hInstance     = hLibInst;
  wc.hIcon         = 0;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szBubbleClassName;
  
  return RegisterClass(&wc);
  }

DLLExport void _export WINAPI GetResolutionCF (double FAR *ratio)
  {
  if (BaseUnit < 0.01) {
    HDC hDC = CreateDC ("DISPLAY", 0, 0, 0);
    BaseUnit_n = float (GetDeviceCaps(hDC, LOGPIXELSX)/40.0);
    BaseUnit = getBaseUnit();
    DeleteDC (hDC);
    }
  *ratio = BaseUnit / BaseUnit_n * 0.8 ; 
  }

DLLExport BOOL _export WINAPI Initialize_Extended (SETCONNECTION_EXTENDED sce,SETTABLECONTEXT stc,GETTABLECONTEXT gtc,GETVARSIZE gtv,FREEPRIVDATA fpr,NEXTBITMAP nbm,NEXTBITMAP ntm,TBFOCUSCHANGING tbfc,TBACTIVE tba)
  {
  SetConnection_Extended = sce;
  SetTableContext = stc;
  GetTableContext = gtc;
  GetVarSize = gtv;
  FreePrivData = fpr;
  NextBitMap = nbm;
  NextTextForMerge = ntm;
  FocusChanging = tbfc;
  tbActive = tba;

  return TRUE ;
  }

DLLExport void _export WINAPI SetFrameWnd (HWND hWnd)
  {
  hFrameWnd = hWnd;
  }

DLLExport void _export WINAPI SetEditCallBack (EDITCALLBACK edc)
  {
  EditCallBack = edc;
  }

/*------------------------------------------------------------------*\
* export function: ActivateControl                                   *
*                                                                    *  
* Parameter:    RefWnd ...                                           *  
* Zweck:                                                             *
\*------------------------------------------------------------------*/
DLLExport void _export WINAPI ActivateControl (HWND RefWnd)
  {
  WndList FAR *wnd = NULL;
  for (ScreenList FAR *h = FirstScreen ; h != NULL ; h = h->Next) 
    h->Insert (wnd = h->FirstWnd->Find(RefWnd));

  if (wnd != NULL) {
    wnd->ActivateTheTools(TRUE);
    wnd->ActivateHotKeys (TRUE);
    }
  }


DLLExport void _export WINAPI SetMouseDownProc (LPSCREEN sc,
                                                DWORD LeftDownProc,
                                                DWORD RightDownProc,
                                                DWORD DownPos,
                                                LPVOID mouseprocPar,
                                                LPVOID mouseprivData,
                                                int mouseprivDataSize)
  {
  sc->LeftDownProc  = LeftDownProc;
  sc->RightDownProc = RightDownProc;
  sc->DownPos       = DownPos;
  sc->mouseprocPar  = mouseprocPar;
  if (sc->mouseprivData) {
    (* FreePrivData) (sc->mouseprivData);
    FreeGlobMem (sc->mouseprivData) ;
    sc->mouseprivData = NULL ;
    }
  if (mouseprivData) {
    sc->mouseprivData = GetGlobMem (mouseprivDataSize);
    lmemcpy (sc->mouseprivData,mouseprivData,mouseprivDataSize);
    }
  }

void ScreenList::MouseDownProc (LPPOINT pt, UINT msg)
  {
  if ((msg == WM_LBUTTONDOWN) && (LeftDownProc != 0L)) {
    fpt p;
    p.x = float(pt->x);
    p.y = float(pt->y);
    (* SetData) (mouseprivData,DownPos,&p,sizeof(p),mouseprocPar);
    (* CallCommand) (mouseprivData, LeftDownProc, mouseprocPar);
    }
  else
  if ((msg == WM_RBUTTONDOWN) && (RightDownProc != 0L)) {
    fpt p;
    p.x = float(pt->x);
    p.y = float(pt->y);
    (* SetData) (mouseprivData,DownPos,&p,sizeof(p),mouseprocPar);
    (* CallCommand) (mouseprivData, RightDownProc, mouseprocPar);
    }
  }

DLLExport void _export WINAPI RemoveScreenControlFromLayer (LPSCREEN sc, int Layer)
  {
  WndList FAR *wnd = sc->FirstWnd;
/*
  for (ScreenList FAR *sc = FirstScreen; sc != NULL; sc = sc->Next)
    if (wnd = sc->FirstWnd->Find(RefWnd))
      break;
  
  if (wnd != NULL)
*/
    while ((wnd != NULL) && (wnd->first)) {
      if (wnd->Layer == Layer) {
        wnd->first->Reset(FALSE);
        delete wnd->first;
        }
      else  
        wnd = wnd->Next;
      }  
  }



DLLExport void _export WINAPI ActivateLayerInScreen (LPSCREEN sc, int Layer)
  {
  WndList FAR *wnd = sc->FirstWnd;

  for ( ; wnd != NULL ; wnd = wnd->Next) {
    if (wnd->Layer == Layer) {
      sc->Insert (wnd);
      wnd->ActivateTheTools(TRUE);
      wnd->ActivateHotKeys (TRUE);
      }
    }
  }


DLLExport void _export WINAPI ChangeToolbarSize (LPSCREEN sc, int w, int h)
  {
  sc->dlgWidth = w;
  sc->dlgHeight = h;
  int hw = int(BaseUnit * h) ;
  LONG style = GetWindowLong (sc->hWnd,GWL_STYLE);
  if (style & WS_CAPTION)
    hw += ibGetCaptionSize(sc->hWnd) + 2 * GetSystemMetrics(SM_CXDLGFRAME);
  RECT r,rf;
  GetWindowRect (hFrameWnd,&rf);
  GetWindowRect (sc->hWnd,&r);
  r.top = (rf.bottom - rf.top - hw) / 2 + rf.top;
  r.left = (rf.right - rf.left - int(BaseUnit*w)) / 2 + rf.left;

  r.bottom = r.top + hw ;
  r.right = r.left + int(BaseUnit*w) ;
  // UINT mflag = SWP_NOMOVE ;
  UINT mflag = 0 ;
  if (r.bottom > GetSystemMetrics (SM_CYSCREEN)) {
    r.top = max(0,r.top + (GetSystemMetrics (SM_CYSCREEN) - r.bottom));
    mflag = 0 ;
    }
  if (r.right > GetSystemMetrics (SM_CXSCREEN)) {
    r.left = max(0,r.left + (GetSystemMetrics (SM_CXSCREEN) - r.right));
    mflag = 0 ;
    }
  SetWindowPos (sc->hWnd, 0,
                r.left, r.top, int(BaseUnit*w), hw,
                SWP_NOZORDER | mflag);
  }

DLLExport void _export WINAPI ChangeToolbarPos (LPSCREEN sc, int x, int y)
  {
  if (sc->ScreenNmbr > 0) {
    int hx = int(BaseUnit * x);
    int hy = int(BaseUnit * y);
    
    SetWindowPos (sc->hWnd, 0, hx, hy, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
  }


DLLExport void _export WINAPI SetToolbarTitle (LPSCREEN sc, LPSTR str)
  {
  SetWindowText (sc->hWnd, str);
  }

/*------------------------------------------------------------------*\
* export function: DeActivateControl                                 *
*                                                                    *  
* Parameter:    RefWnd ...                                           *  
* Zweck:                                                             *
\*------------------------------------------------------------------*/
DLLExport void _export WINAPI DeactivateControl (HWND RefWnd)
  {
  for (ScreenList FAR *h = FirstScreen ; h != NULL ; h = h->Next)
//////////////////////////
    if (!h->nonmodal)   // nichtmodales Fenster
//////////////////////////
      h->Remove (RefWnd);

  }

/*------------------------------------------------------------------*\
* export function: SetControl                                        *
*                                                                    *  
* Parameter:    RefWnd ...                                           *  
*               Data .....                                           *
*               Mode .....                                           *
* Zweck:                                                             *
\*------------------------------------------------------------------*/
DLLExport void _export WINAPI SetControl (HWND RefWnd,LPTOOLHEADER Data,WORD mode,LPVOID privData,int pSize)
  {
  if (mode & EM_LOAD) {
    LPSCREEN FAR *lpScreen = (LPSCREEN FAR *) (* GetData) (privData, Data->ScreenId);
    #ifdef DEBUG
    BOOL doIt = ((lpScreen != NULL) && (*lpScreen != NULL));
    DBWIN_ASSERT_TEXT (doIt,"Screen nicht definiert");
    if (!doIt) return ;
    #endif
    if (*lpScreen == MainScreen) {
      DBINT FAR * ly = (DBINT FAR *) (* GetData) (privData,Data->_Layer);
      if ((ly != NULL) && (*ly == 0) && (MainScreen->AnzActive > 0))
        RefWnd = MainScreen->ActiveList[0]->RefWnd;
      }
    DBWIN_ASSERT (Data->MyTool == NULL);
    switch (Data->ToolType) {
      case TOOLTYPE_CHECKBUTTON :
        Data->MyTool = new CheckButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_PUSHBUTTON :
        Data->MyTool = new PushButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TEXTCHECKBUTTON :
        Data->MyTool = new TextCheckButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TEXTPUSHBUTTON :
        Data->MyTool = new TextPushButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TEXTRADIOBUTTON :
        Data->MyTool = new TextRadioButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_COMBOBUTTON :
        Data->MyTool = new ComboButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_UPDOWN :
        Data->MyTool = new UpDown (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_EDIT :
        Data->MyTool = new ToolEdit (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_PASSWORD :
        Data->MyTool = new ToolPwd (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_GROUPBOX :
        Data->MyTool = new GroupBox (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_ZOOM :
        Data->MyTool = new ZoomTool (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_PAGE:
        Data->MyTool = new PageTool (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_DATE:
        Data->MyTool = new ToolDate (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TIME:
        Data->MyTool = new ToolTime (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_FLOAT:
        Data->MyTool = new ToolFloat (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_SHORTINT:
        Data->MyTool = new ToolShortInt (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_STATIC:
        Data->MyTool = new StaticTool (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_STATICBITMAP:
        Data->MyTool = new StaticBitmap (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_3DLINE :
        Data->MyTool = new Line3D (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_COLORLINE :
        Data->MyTool = new LineTool (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_COLORRECT :
        Data->MyTool = new ColorRect (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_ACTIONRECT :
        Data->MyTool = new ActionRect (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_FLAPMAP :
        Data->MyTool = new FlapMap (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_PUSHCHECKBUTTON :
        Data->MyTool = new PushCheckButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TRANSPARENTBITMAP :
        Data->MyTool = new TransparentBitmap (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_ANIMATIONBITMAP :
        Data->MyTool = new AnimationBitmap (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_CONTEXTHELP :
        Data->MyTool = new HelpTool (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BEDIT :
        Data->MyTool = new ToolBEdit (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BMPFLOAT:
        Data->MyTool = new BmpFloat (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_XYFROMRECT:
        Data->MyTool = new XYFromRect (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BMPTEXTPUSHBUTTON:
        Data->MyTool = new BmpTextPushButton (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_ICON:
        Data->MyTool = new IconTool (RefWnd,Data,privData,pSize);
        break;
      case TOOLTYPE_SHOWTRANSPARENTBITMAP :
        Data->MyTool = new ShowTransparentBitmap (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BITSELECT :
        Data->MyTool = new BitSelect (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_LONGINT :
        Data->MyTool = new ToolLongInt (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_MONEY :
        Data->MyTool = new ToolMoney (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_PALETTE :
        Data->MyTool = new ToolPalette (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BITEDIT :
        Data->MyTool = new BitEdit (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_BITMERGE :
        Data->MyTool = new BitMerge (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TEXTMERGE :
        Data->MyTool = new TextMerge (RefWnd,Data,privData,pSize);
        break ;
      case TOOLTYPE_TEXTPUSHCHECKBUTTON :
        Data->MyTool = new TextPushCheckButton (RefWnd,Data,privData,pSize);
        break ;
      default :
        // beim rest muss es sich um externtools handeln (oder es knallt)
        Data->MyTool = new ExternTool (RefWnd,Data,privData,pSize);
        break ;
      }
    (* SetData) (privData,Data->ObjId,&(Data->MyTool),sizeof(LPVOID),Data);
    Data->MyTool->Load ();
    Data->MyTool->Invalidate (FALSE);
    if (((*lpScreen)->IsActivated) || (mode & EM_CHANGETOTRUE)) {
      if ((*lpScreen)->IsActivated) {
        Data->MyTool->OnActivate (TRUE);
        if ((Data->MyTool->Parent->Parent->ToolWithFocus == NULL) &&
            (GetFocus () == Data->MyTool->Parent->Parent->hWnd))
          Data->MyTool->SetToolFocus (TRUE) ,
          Data->MyTool->Parent->Parent->ToolWithFocus = Data->MyTool;
        }

      WndList FAR *Parent = Data->MyTool->Parent;
      Parent->yHeight = 0 ;
      for (tool FAR *h = Parent->first ; h != NULL ; h = h->Next)
        h->GetRect ();

      // Alle Tools entsprechend richtig positionieren
      for ( int i = 0 ; i < Parent->Parent->AnzActive ; i++) {
        for (h = Parent->Parent->ActiveList[i]->first ; h != NULL ; h = h->Next)
          h->MoveTool ();
        }
      }
    }
  if (mode & EM_UPDATE) {
    Data->MyTool->Update ();
    }
  if (mode & EM_FIXCONNECTION) {
    Data->MyTool->FixConnection ();
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    if (Data->MyTool != NULL) {
      if (Data->MyTool == Capture) {
        tool FAR *old = Capture;
        Capture = NULL;
        LONG h = GetMessagePos();
        POINT pt;
    #ifdef WIN32
        LONG2POINT(h, pt);
    #else
        pt = MAKEPOINT(h);
    #endif
        ScreenToClient (Data->MyTool->Parent->Parent->hWnd,&pt);
        old->On_LButtonUp(&pt);
        }
      WndList FAR *Parent = Data->MyTool->Parent;
      Parent->yHeight = 0 ;
      BOOL doCheck;
      if (Parent->first->Next != NULL) doCheck = TRUE ;
      else                             doCheck = FALSE ;
      if (Data->MyTool != NULL) {
        if ((Data->MyTool == Data->MyTool->Parent->Parent->ToolWithFocus) &&
            (GetFocus () == Data->MyTool->Parent->Parent->hWnd))
          Data->MyTool->SetToolFocus (FALSE) , Data->MyTool->Parent->Parent->ToolWithFocus = NULL;

        LPVOID nullobj = NULL ;
        (* SetData) (Data->MyTool->privData,Data->ObjId,&nullobj,sizeof(LPVOID),Data);
        Data->MyTool->Reset ((mode & EM_CLEAR) && (!Data->MyTool->Parent->Parent->destroyIsDone));
        delete Data->MyTool;
        Data->MyTool = NULL ;
        }
      if (doCheck) {
        // Alle Tools des Layers zu Berechnung der Layerhoehe heranziehen
        Parent->yHeight = 0 ;
        for (tool FAR *h = Parent->first ; h != NULL ; h = h->Next)
          h->GetRect ();

        // Alle Tools entsprechend richtig positionieren
        for ( int i = 0 ; i < Parent->Parent->AnzActive ; i++) {
          for (h = Parent->Parent->ActiveList[i]->first ; h != NULL ; h = h->Next)
            h->MoveTool ();
          }
        }
      }
    }
  if (mode & EM_PRIVATE1) {
    // Editor
    Data->MyTool->Reset (TRUE);
    Data->MyTool->Load ();
    Data->MyTool->MoveTool ();
    Data->MyTool->OnActivate (TRUE);
    }
  }

extern void DestroyButtonBitmaps ();
extern void DeleteFolderBrush ();
DLLExport void _export WINAPI ToolBarCleanUp ()
  {
#ifdef TOOLTIP
  if (g_hhk) {
    UnhookWindowsHookEx (g_hhk);
    g_hhk = NULL;
    }
#endif

  if (HelvFont)
    DeleteObject (HelvFont);
  if (DnBrush)
    DeleteObject (DnBrush);
  if (Leather)
    DeleteObject (Leather);
  if (MultiOn)
    DeleteObject (MultiOn);
  if (MultiOff)
    DeleteObject (MultiOff);
  if (hBmpMappeDisabled)
    DeleteObject (hBmpMappeDisabled);
  CleanBitmapList ();
  while (FirstScreen != NULL)
    RemoveScreen (FirstScreen);
  DestroyButtonBitmaps ();
  if (MyBackGround)
    DeleteObject (MyBackGround);
  DeleteFolderBrush ();
  }

/////////////////////////////////////////////////////////
//  Ermitteln, ob der Hauptschirm Popup oder Child ist
/////////////////////////////////////////////////////////
DLLExport BOOL _export WINAPI IsMainPopup ()
  {
  return FALSE;
  }

DLLExport BOOL _export WINAPI IsMainExistant ()
  {
  BOOL res = FALSE ;
  for (ScreenList FAR *h = FirstScreen ; ((h != NULL) && (!res)) ; h = h->Next)
    res = (h->ScreenNmbr == 0);
  return res;
  }

DLLExport void _export WINAPI ActivateWholeScreen (LPSCREEN screen)
  {
  screen->IsActivated = TRUE;
  WndList FAR *wnd = screen->FirstWnd;
  for ( ; wnd != NULL ; wnd = wnd->Next) {
    screen->Insert (wnd);
    wnd->ActivateTheTools(TRUE);
    wnd->ActivateHotKeys (TRUE);
    }
  if (screen->IstMappe) {
    ActivateMainToolBar (TRUE);
    }
  }

HWND GetActiveMDIWnd ()
  {
  if (hFrameWnd != 0) {
    for ( HWND hWndChild = GetWindow (hFrameWnd,GW_CHILD) ; hWndChild ; hWndChild = GetWindow (hWndChild,GW_HWNDNEXT) ) {
      char className[64];
      GetClassName (hWndChild,className,sizeof(className));
      if (lstrcmp (className,"MYMDICLIENT") == 0) {
        return HWND(SendMessage (hWndChild,WM_MDIGETACTIVE,0,0L));
        }
      }
    }
  return 0 ;
  }

DLLExport void _export WINAPI ActivateMainToolBar (BOOL State)
  {
#ifdef INITHOTKEYS
  if (MainScreen != NULL) {
    if (State)
      for (WndList FAR *Wnd = MainScreen->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
        for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
          h->InitHotKey ();
    else      
      for (WndList FAR *Wnd = MainScreen->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
        for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
          RemoveHotKey (h);
    }
#endif
  // Ueberpruefen ob eine Mappe offen ist, und ob dem der Focus gegeben werden
  // kann
  if ((State) && (GetActiveMDIWnd () == 0)) {
    HWND hWndFocus = GetFocus ();
    char cln[60];
    if (IsWindow(hWndFocus)) {
      GetClassName (hWndFocus,cln,sizeof(cln));
      if ((lstrcmp (cln,szClassName) != 0) &&
          (lstrcmp (cln,szListClassName) != 0) &&
          (lstrcmp (cln,"ECC") != 0) &&
          (lstrcmp (cln,"MDIFRAME") != 0) &&
          (lstrcmp (cln,"MYMDICLIENT") != 0) &&
          (lstrcmp (cln,"MDICHILD") != 0)) {
        // Untersuchen ob da nicht vielleicht doch eine Mappe ...
        for (ScreenList FAR *h = FirstScreen ; h != NULL ; h = h->Next) {
          if (h->IstMappe)
            SetFocus (h->hWnd);
          }
        }
      }
    }
  }

void ScreenList::InsertToTimerList (tool FAR *h, UINT interval, WORD Nr)
  {
  TimerInfo FAR *n = (TimerInfo FAR *) GetGlobMem (sizeof (*n)) ;
  n->Id = Nr;
  n->h = h ;
  n->Next = firsttimer;
  firsttimer = n;

  SetTimer (hWndToolbar (),Nr,interval,NULL);
  }

void ScreenList::RemoveFromTimerList (tool FAR *h)
  {
  TimerInfo FAR *p = NULL ;
  for (TimerInfo FAR *x = firsttimer ; x != NULL ; ) {
    if (x->h == h) {
      if (p != NULL) p->Next = x->Next ;
      else           firsttimer = x->Next ;
      KillTimer (hWndToolbar (),x->Id);
      FreeGlobMem (x) ;
      break ;
      }
    p = x ;
    x = x->Next ;
    }
  }

DLLExport void _export WINAPI GetBaseUnit (double FAR *unit)
  {
  *unit = BaseUnit;
  }

DLLExport void _export WINAPI CTOOL_SetClassNames (LPSTR ListClassName,LPSTR ClassName,LPSTR WWName,LPSTR BubbleName,LPSTR FolderClass)
  {
  szListClassName = ListClassName;
  szClassName = ClassName;
  szWWName = WWName;
  szBubbleClassName = BubbleName;
  szFolderClass = FolderClass;
  }

DLLExport HWND _export WINAPI CTOOL_GetActiveTopWindow ()
  {
  HWND hWnd = GetFocus(); // Nicht GetActiveWindow() da sonst Probleme mit Modalitaet der FileSelectorBox
  if (IsWindow(hWnd)) {
    char cln[64];
    GetClassName (hWnd,cln,sizeof(cln));
    if (lstrcmp (cln,szClassName) == 0)
      return hWnd;
    else {
      hWnd = GetParent (hWnd);
      if (IsWindow (hWnd)) {
        GetClassName (hWnd,cln,sizeof(cln));
        if (lstrcmp (cln,szClassName) == 0) return hWnd;
        }
      }
    }
  return 0 ;
  }
DLLExport HPALETTE _export WINAPI CTOOL_GetActivePalette ()
  {
  return hFirstScreenPal;
  }
DLLExport void _export WINAPI CTOOL_SetActivePalette (HPALETTE hNewPal)
  {
  DBWIN_ASSERT (hFirstScreenPal);
  PaletteForScreen->hPal = hFirstScreenPal = hNewPal ;
  }

DLLExport tool FAR *_export WINAPI CTOOL_GetActMouseObject ()
  {
  return Capture;
  }

#ifdef TOOLTIP
DLLExport void _export EnableToolTips (BOOL bEnable)
  {
  bEnableToolTip = bEnable;
  for ( ScreenList FAR *sc = FirstScreen ; sc != NULL ; sc = sc->Next) {
    SendMessage (sc->hWndToolTip, TTM_ACTIVATE, (WPARAM)(BOOL)bEnable, 0);
    }
  }
#endif

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

  return 1 ;
  }
}

#endif




