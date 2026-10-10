/********************************************************/
/*      Erzeugung des Haupt- und Klientenfensters       */
/********************************************************/
//
// $Header:   P:/marille/clinicum/rev/wbase.cpv   1.79   27 Jun 2000 18:38:58   Martin  $
// $Log:   P:/marille/clinicum/rev/wbase.cpv  $
// 
//    Rev 1.79   27 Jun 2000 18:38:58   Martin
// FrameName ueber Ltx(1) einstellbar
// 
//    Rev 1.78   15 Apr 2000 00:23:38   Martin
// bei ChangeSize=yes nicht maximieren
// 
//    Rev 1.77   01 Mar 2000 08:47:58   Dietmar
// Syntaxerror ausgebessert
//
//    Rev 1.76   01 Mar 2000 08:34:34   Dietmar
// GetClientWindowHandle() implementiert (Hannes)
//
//    Rev 1.75   16 Feb 2000 15:04:06   Wolfgang
// 1.) WMC_GETNEXTINCYCL implementiert.
//
//    Rev 1.74   23 Nov 1999 15:48:24   Wolfgang
// 1.) WMC_GETSCRIPTHD neu.
//
//    Rev 1.73   08 Nov 1999 14:32:38   Wolfgang
// 1.) Keine Timer-Messages in Client-Transaktionen.
//
//    Rev 1.72   08 Nov 1999 03:44:56   Hannes
// In Testrecord ein Refreshlist..
//
//    Rev 1.71   13 Oct 1999 23:28:16   Hannes
// Verbessertes Menuehandling
//
//    Rev 1.70   15 Jun 1999 19:17:46   WOLFGANG
// 1.) ResetSync by TIMECHANGE eingebaut.
//
//    Rev 1.69   15 Jun 1999 16:29:56   WOLFGANG
// 1.) TimeNow-Aufruf beseitigt und stattdessen UnPackSeconds verwendet.
//
//    Rev 1.68   13 Apr 1999 17:24:36   Hannes
// HDC wieder freigeben...
//
//    Rev 1.67   08 Apr 1999 18:25:16   Hannes
// Auch Sekunden
//
//    Rev 1.66   08 Apr 1999 14:48:48   Hannes
//
//    Rev 1.65   03 Apr 1999 11:41:32   Hannes
// Auch Zeit oben anzeigen..ÿ
//
//    Rev 1.64   02 Apr 1999 10:53:54   Hannes
// Menue - Verschoenerung
//
//    Rev 1.63   02 Apr 1999 07:52:06   Hannes
// Kein HTMLCLOSE, wenn nicht HTMLInit....
//
//    Rev 1.62   31 Mar 1999 14:55:28   Gerhold
// htmlhelp
//
//    Rev 1.61   04 Feb 1999 20:23:58   Hannes
// Mainwindow Hidebar
//
//    Rev 1.60   13 Oct 1998 14:03:34   Gerhold
// VC6 noch ein paar kleine Fehler
//
//    Rev 1.59   13 Oct 1998 13:53:52   Gerhold
// VC6 Type casts
//
//    Rev 1.58   13 Oct 1998 13:10:18   Gerhold
// VC6  HANDLE -> HINSTANCE
//
//    Rev 1.57   09 Oct 1998 18:48:10   Wolfgang
// 1.) Reaktion auf WMU_SOCKETEVENT neu.
//
//    Rev 1.56   12 Aug 1998 15:18:34   Gerhold
// FrameIcon in BaseIcon umgetauft
//
//    Rev 1.55   03 Aug 1998 09:22:20   Gerhold
// Ein bloeder Versuch mit WM_GETMINMAXINFO (wurde aber wieder auskommentiert)
//
//    Rev 1.54   21 Jul 1998 09:45:52   Gerhold
// WM_INITMENU ... ExternChild (Stammdatenblatt) hatte nicht funktioniert
//
//    Rev 1.53   02 Jul 1998 11:06:32   Hannes
// Handling Zeitversetztes Destroy
//
//    Rev 1.52   29 Jun 1998 19:04:16   Hannes
//
//    Rev 1.51   08 Jun 1998 16:57:42   Wolfgang
// 1.) DRAWCLIPBOARD (wieder) verarbeiten.
//
//    Rev 1.50   19 Jan 1998 14:23:36   Gerhold
// WM_INITMENU stimmt jetzt in den meisten Faellen
//
//    Rev 1.49   12 Jan 1998 18:18:50   Hannes
//
//    Rev 1.48   19 Nov 1997 18:47:44   Hannes
// Restool 32 Bit umstellung
//
//    Rev 1.47   24 Oct 1997 08:37:28   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
//
//    Rev 1.46   22 Aug 1997 12:29:38   Gerhold
// WMU_DELETEOBJ (OLE1) ... raus!
//
//    Rev 1.45   01 Aug 1997 18:33:46   Martin
// AddMenuCommend: 32 Bit-faehig gemacht (Verhalten von WM_MDIGETACTIVE hat
// sich geaendert !!!!)
//
//    Rev 1.44   23 Jul 1997 18:35:36   Hannes
//
//    Rev 1.43   22 Jul 1997 21:08:20   Hannes
//
//    Rev 1.42   16 Jul 1997 11:57:06   Hannes
//
//    Rev 1.41   30 Apr 1997 11:58:06   Hannes
//
//    Rev 1.40   30 Apr 1997 10:15:38   Hannes
//
//    Rev 1.39   10 Apr 1997 15:59:02   Gerhold
// Menu fuer MDI-Fensterposition ist endlich 2 statt 3 (IDM_WINDOW)
//
//    Rev 1.38   07 Apr 1997 19:15:16   gerhold
// ClientWnd.SetWndPos ... 2.ter Parameter wP aus WM_SIZE
//
//    Rev 1.37   07 Apr 1997 13:43:44   gerhold
// WM_MDIACTIVATE verhaelt sich in 32 Bit anders
//
//    Rev 1.36   13 Mar 1997 18:59:20   Hannes
// ActivateStatBar nur bei echten midChilds aufrufen
//
//    Rev 1.35   19 Feb 1997 12:17:04   Hannes
// No change.
//
//    Rev 1.34   01 Feb 1997 23:38:00   MARTIN
// AddMessageHook
//
//    Rev 1.33   08 Nov 1996 13:35:00   HANNES
// IsFromDestroy...
//
//    Rev 1.32   21 Oct 1996 18:49:28   HANNES
// Verbessertes Debughandling
//
//    Rev 1.31   24 Sep 1996 19:05:22   GERHOLD
// Benutzerdefinierte Menus im Script hatten Probleme mit MDI-Fenstern
//
//    Rev 1.30   17 Aug 1996 18:09:36   GERHOLD
// SC_RESTORE ueberprueft DMW.INI und laesst auch Fenstermodus zu
//
//    Rev 1.29   10 Jun 1996 10:10:14   GERHOLD
// pragma pack
//
//    Rev 1.28   16 Feb 1996 13:39:06   GERHOLD
// Der Text in der MenuZeile wird rot, die Uhrzeit schwarz geschrieben
// Endlich kann man vom ICON aus wieder maximieren!!!!!
//
//    Rev 1.27   07 Feb 1996 11:12:02   MARTIN
// PostMessage erste nach ClientTrans.
//
//    Rev 1.26   05 Feb 1996 18:55:46   MARTIN
// CallCommand innerhalb DDE verhindert
//
//    Rev 1.25   05 Feb 1996 10:50:56   GERHOLD
// SetMenuText (MenuText ist nicht mehr rot sonder schwarz)
//
//    Rev 1.24   04 Feb 1996 15:48:34   gerhold
// SetMenuText ... Farbefehler beim Zeichnen in der Menuleiste
//
//    Rev 1.23   02 Feb 1996 10:36:24   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.22   22 Sep 1995 07:52:02   GERHOLD
// WM_PALETTECHANGED hatte keinen WPARAM (der ist aber notwendig!!!)
//
//    Rev 1.21   21 Sep 1995 10:31:16   GERHOLD
// if (IsWindow(ctoolMain)) SendMessage (ctoolMain, WM_PALETTECHANGED, ...
//
//    Rev 1.20   15 Sep 1995 00:48:20   HANNES
//
//    Rev 1.19   24 Aug 1995 00:20:00   HANNES
// DBWIN_ASSERT
//
//    Rev 1.18   10 Aug 1995 09:25:36   HANNES
// Menuetext vergroessert
//
//    Rev 1.17   24 Jul 1995 16:40:32   GERHOLD
// IsWindow (cToolMain)
//
//    Rev 1.16   11 Jul 1995 12:47:48   HANNES
// Expressionoptimierung
//
//    Rev 1.15   04 Jul 1995 20:40:28   HANNES
// Palettenhandling mit CTOOLs
//
//    Rev 1.14   03 Jul 1995 16:16:34   HANNES
// Palettenhandling auch fuer CTOOLs
//
//    Rev 1.13   02 Jul 1995 18:30:04   GERHOLD
// Palettenhandling fuer extchild
//
//    Rev 1.12   31 Mar 1995 12:45:46   GERHOLD
// WS_CLIPSIBLINGS, WS_CLIPCHILDREN bei MDI_CHILD
//
//    Rev 1.11   20 Mar 1995 12:06:06   HANNES
// Konstantenhanling, RunNmbr...
//
//    Rev 1.10   03 Mar 1995 18:12:36   HANNES
//
//    Rev 1.9   13 Jan 1995 16:55:56   HANNES
// Variablen-Breakpoints
//
//    Rev 1.8   09 Jan 1995 12:14:44   HANNES
// Debugger eingebaut
//
//    Rev 1.7   16 Dec 1994 16:25:32   GERHOLD
// Focus Gschichterln
//
//    Rev 1.6   15 Dec 1994 23:49:52   HANNES
// Focusgschichtln...
//
//    Rev 1.5   08 Nov 1994 12:44:26   HANNES
// Statuszeilenverarbeitung
//
//    Rev 1.4   07 Nov 1994 11:29:58   GERHOLD
// neuen Statusbar erstmalig verwendet.
//
//    Rev 1.3   20 Oct 1994 17:44:30   GERHOLD
// WM_INITMENU
//
//    Rev 1.2   11 Oct 1994 09:44:44   HANNES
// Einbau der Zoomrectfunktionen
//
//    Rev 1.1   20 Sep 1994 11:39:24   HANNES
// Umstellung auf OutContext
//
//    Rev 1.0   24 Jun 1994 17:04:52   HANNES
// Neuuebernahme clinicum
//
//    Rev 1.66   13 Apr 1994 14:37:08   HANNES
// Meldungen vom Testtool entsprechend weiterleiten
//
//    Rev 1.65   10 Mar 1994 11:25:06   MARTIN
// Palette
//
//    Rev 1.64   03 Mar 1994 22:10:52   HANNES
// Behandlung der WMU_OLEDELETEOBJ - Message
//
//    Rev 1.63   14 Feb 1994 19:48:20   HANNES
// Fensterspezifische Fontverwaltung
//
//    Rev 1.62   04 Feb 1994 17:04:28   MARTIN
// XFERDONE (Martin)
// WMU_RECCHANGED weitergeleitet, Dynalink geloescht im Destruktor
//
//    Rev 1.61   26 Jan 1994 17:06:48   MARTIN
// Sound aufraeumen verlegt nach dds.cpp
//
//    Rev 1.60   25 Jan 1994 17:29:08   MARTIN
// WMU_PLAYSOUND nur ausfuehren, wenn command fifo leer ist
//
//    Rev 1.59   25 Jan 1994 16:23:00   MARTIN
// neue Message WMU_PLAYSOUND in FrameWndProc
//
//    Rev 1.58   20 Jan 1994 23:58:18   HANNES
// WM_SIZE bei closed ausgelassen
//
//    Rev 1.57   20 Jan 1994 12:13:00   MARTIN
// Sound eingebaut
//
//    Rev 1.56   12 Jan 1994 11:13:36   HANNES
// Unnoetige Includes entfernt, Nicht mehr Benoetigte Fensterklassen
// dementsprechend auch nicht mehr registriert
//
//    Rev 1.55   07 Jan 1994 12:11:10   HANNES
// Waitwin in die DLL verlegt -> Keine Registrierung der WWND Klasse mehr
//
//    Rev 1.54   04 Jan 1994 17:01:28   HANNES
// Interne Prfung des Recalls raus
//
//    Rev 1.53   09 Dec 1993 15:03:10   HANNES
// Direktes Include der Pascal Files
//
//    Rev 1.52   29 Nov 1993 08:58:04   HANNES
// Loeschen der AvoidWrite - Liste
//
//    Rev 1.51   13 Oct 1993 12:18:58   HANNES
// Strukturbereinigung
//
//    Rev 1.50   04 Oct 1993 09:44:06   HANNES
// Aenderungen am Destruktor von mdiChild
//
//    Rev 1.49   27 Sep 1993 18:29:28   HANNES
// WindowIsDestroyed mehrfach aufgerufen
//
//    Rev 1.48   24 Sep 1993 22:42:40   HANNES
// Freigeben der Help - Variablen
//
//    Rev 1.47   22 Sep 1993 09:17:44   HANNES
// Version nach St. Poelten
//
//    Rev 1.46   05 Sep 1993 22:16:00   HANNES
// Aufraeumarbeiten
//
//    Rev 1.45   18 Aug 1993 10:35:36   HANNES
// Endgueltiger Umbau auf Tools
//
//    Rev 1.44   05 Aug 1993 13:13:30   HANNES
// DrawClipboard behandeln..
//
//    Rev 1.43   22 Jul 1993 20:55:30   HANNES
// Kommandozaehler
//
//    Rev 1.42   13 Jul 1993 11:10:28   HANNES
// In der Schiebelehreversion keine Recall - Tests
//
//    Rev 1.41   12 Jul 1993 07:57:28   HANNES
// Loeschen aller Kommandos aus der Commandoliste beim Zerstoeren eines
// Dokumentes
//
//    Rev 1.40   05 Jul 1993 14:47:30   HANNES
// Einbau der Toolbar
//
//    Rev 1.39   20 Jun 1993 17:12:42   HANNES
// Menueposition bei Vollbild eines Dokumentes
//
//    Rev 1.38   20 Jun 1993 15:58:04   HANNES
// WM_QUERYENDSESSION behandelt, Dis-/EnableWindowMenu
//
//    Rev 1.37   20 Jun 1993 13:43:10   HANNES
// Bei NCACTIVATE Aufruf der virtuellen Funktion OnActivate
//
//    Rev 1.36   19 Jun 1993 19:40:46   HANNES
// Keine Bemerkungen bei Neuaufnahmen
//
//    Rev 1.35   18 Jun 1993 15:07:46   MARTIN
// Prototyp von SetData
//
//    Rev 1.34   17 Jun 1993 15:46:06   HANNES
// !!!
//
//    Rev 1.33   17 Jun 1993 09:24:44   HANNES
// SC_RESTORE deaktiviert
//
//    Rev 1.32   15 Jun 1993 12:28:16   HANNES
// WS_CLIPCHILDS in den MDI - Fenstern raus
//
//    Rev 1.31   14 Jun 1993 18:06:52   HANNES
// WMU_CALLCOMMAND in die FrameWndProc
//
//    Rev 1.30   14 Jun 1993 13:11:58   HANNES
// StoreDefPat beim Schliessen des Dokumentes nur wenn getDocumentCount==0
//
//    Rev 1.29   10 Jun 1993 18:35:44   HANNES
// In der Schiebelehre GetOwner (nicht GetUser..)
//
//    Rev 1.28   09 Jun 1993 15:07:22   HANNES
// Registrierung der neuen Layout Klasse
//
//    Rev 1.27   07 Jun 1993 18:43:14   HANNES
// WM_SYSCOMMAND -> wP & 0xFFF0
//
//    Rev 1.26   07 Jun 1993 16:52:08   HANNES
// InNewPatient
//
//    Rev 1.25   07 Jun 1993 11:29:12   HANNES
// Behandlung von WMU_CALLCOMMAND
//
//    Rev 1.24   02 Jun 1993 20:00:54   HANNES
// Menuposition fuer die Clientfenster
//
//    Rev 1.23   02 Jun 1993 19:54:38   HANNES
// Datumsfunktionen, Registercustomcontrol
//
//    Rev 1.22   28 May 1993 21:12:52   HANNES
// SC_RESTORE abgefangen -> Programm ist nicht mehr verkleinerbar
//
//    Rev 1.21   05 Apr 1993 10:29:14   HANNES
// Einbau der Kommentarabfrage
//
//    Rev 1.20   02 Apr 1993 17:41:46   HANNES
// Strukturbereinigung, Beschleunigung
//
//    Rev 1.19   11 Mar 1993 11:39:14   HANNES
// ???
//
//    Rev 1.18   08 Mar 1993 14:09:06   HANNES
// Check des layouts (nicht mehrfach offen, verbessert Menuezeichnung)
//
//    Rev 1.17   22 Feb 1993 17:17:48   HANNES
// Eintrag des Benutzers im Menue
//
//    Rev 1.16   17 Feb 1993 15:30:18   HANNES
// MDI - Handling
//
//    Rev 1.15   16 Feb 1993 13:17:30   HANNES
// ???
//
//    Rev 1.14   14 Feb 1993 15:54:58   HANNES
// Verallgemeinerte Konfigurationstabelle
//
//    Rev 1.13   08 Feb 1993 10:41:34   HANNES
// Einbau des Callcommand Fifos
//
//    Rev 1.12   29 Jan 1993 19:04:12   HANNES
// Hintergrundfarbe in der Klasse GROUPFRAME
//
//    Rev 1.11   18 Jan 1993 16:50:52   HANNES
// Aenderungen des Handlings von EM_UPDATE, EM_CLEAR
//
//    Rev 1.10   13 Jan 1993 18:53:40   HANNES
// Neue Verwaltung der zu einem Dokument gespeicherten Patienteninfo..
//
//    Rev 1.9   10 Jan 1993 15:09:22   HANNES
// breaks nach WM_COMMAND (ansonsten werden nach MI_QUIT noch programme
// aufgerufen)
//
//    Rev 1.8   06 Jan 1993 16:58:00   HANNES
// Neue Logik in der MDI - Client Window Verwaltung
//
//    Rev 1.7   21 Dec 1992 11:35:26   HANNES
// Einbau von Hotkeys fuer die Knoepfchens
//
//    Rev 1.6   19 Dec 1992 14:21:42   HANNES
// Aufruf der virtuellen Funktion OnActivate (bei WM_MDIACTIVATE)
//
//    Rev 1.5   17 Dec 1992 15:57:06   HANNES
// ???
//
//    Rev 1.4   14 Dec 1992 12:32:54   HANNES
// Aufruf von StoreDefPat wenn neuer Datensatz und Stammdatenblatt
//
//    Rev 1.3   12 Dec 1992 13:46:00   HANNES
// Elemination des Overlap - Button Handles (hat sich nicht bewaehrt)
//
//    Rev 1.2   12 Dec 1992 13:28:02   HANNES
// Bearbeitung der WM_GETMINMAXINFO Message (Verhindern von kleinen Fenstern)
//
//    Rev 1.1   10 Dec 1992 11:50:46   HANNES
// Ermittlen der Anzahl offenere Dokumente
//
//    Rev 1.0   02 Dec 1992 15:47:44   HANNES
// Initial revision.
//
#ifdef WIN32
#define INC_OLE1
#endif

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

#include "htmlhelp.h"

#include "dds32.h"
#define WBASE_MAIN
#include "dds.hpp"
#include "ddsmsg.h"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "hash.hpp"
#include "dynalink.hpp"


#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "dds.h"
#include "diagram.hpp"
#include "waitwin.hpp"

#include "mdiclien.hpp"
#include "oneshot.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "ddslist.hpp"
#include "date.hpp"

#include "sound.hpp"

#include "cfield.hpp"

#ifndef WIN32
#include <ole.h>
#endif

#include "ole.hpp"

#include "dmwstst.hpp"

#define MODULENUM 109
#include "winass.hpp"

#define JUST_MSG
#include "communic.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#include "socket.hpp"

/*------------------------------------*/
/********* Private Funktionen *********/
/*------------------------------------*/

/****** Kreation des Klientenfensters *******/
#define IDM_WINDOW  2;

extern LPVOID GetVarValueExtended (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext);
BOOL CreateMdiClientWindow(HWND hWnd)
  {
  CLIENTCREATESTRUCT  ClientCreate;     // MDI-ClientWindow Datenstruktur

  // Bezug zum Menue, das von Windows verwaltet wird
  int WndPos = IDM_WINDOW ;
  ClientCreate.hWindowMenu =  GetSubMenu(WBase::hMenu, WndPos);

  // Eindeutige Kennziffer (Abfrage bei WM_COMMAND im Framewindow moeglich,
  // bzw. wird von DefFrameProc (...) uebernommen)
  ClientCreate.idFirstChild = FIRSTCHILD;

  /*------------< Ausdehnung des Vaterfensters >-----------*/
  WBase::hClient = ClientWnd.CreateMDIClient (hWnd,WBase::hInstance,&ClientCreate);

  if(!WBase::hClient)     FatalExit(0);

  ShowWindow(WBase::hClient, SW_SHOW);
  return TRUE;
  }

/*----------< Zerstoerung aller Kindfenster >----------------------*/

void DestroyMdiChildren(void)
  {
  HWND hwChild;

  ShowWindow(WBase::hClient, SW_HIDE);  // das Client-Fenster wird versteckt,
                                      // um unnoetiges Neumalen zu vermeiden

  while(hwChild = GetWindow(WBase::hClient, GW_CHILD)) {
    // Die Liste der vom Window-Manager verwalteten Kindfenster nach
    // MDI-Kindfenstern durchsuchen, und diese per WM_MDIDESTROY
    // Nachricht zerstoeren

    while(hwChild && GetWindow(hwChild,GW_OWNER)) {
      // der vorliegende Fensterbezug ist kein MDI-Kindfenster,
      // sondern ein Handle auf das Untertitelfenster eines Icons.
      // Da ein solches Fenster nicht wie ein MDI-Fenster behandelt
      // werden darf, ist es zu uebergehen ...
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);
      }

    if(hwChild) { // Endlich gefunden
      mdiChild *pmdich = GetWindowInst(hwChild);
      delete pmdich ;   // invoke destructor, invoke wm_destroy....
      }
    else break;
    }
  ShowWindow(WBase::hClient, SW_NORMAL);  // Client-Fenster wieder sichtbar machen
  }

/********* Kreation eines Kindfensters *********/
HWND CreateMdiChildWindow(LPSTR name,LPMDICHILD inst,int x,int y,int w,int h)
  {
  MDICREATESTRUCT    MdiCreate;     // Datenstruktur zur Erzeugung eines
                                    // MDI-Kindfensters
  MdiCreate.szClass = "MDICHILD";
  MdiCreate.szTitle = name;
  MdiCreate.style   = WS_CHILD | MDIS_ALLCHILDSTYLES | WS_MAXIMIZE |
                      WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  MdiCreate.hOwner  = WBase::hInstance;         // Instanzenbezug zur
                                                // erzeugenden Applikation

  MdiCreate.x       = CW_USEDEFAULT; // X-Position des MDI-Kindfensters
  MdiCreate.y       = CW_USEDEFAULT; // Y-Position  "         "
  MdiCreate.cx      = CW_USEDEFAULT; // Breite      "         "
  MdiCreate.cy      = CW_USEDEFAULT; // Hoehe       "         "

  MdiCreate.lParam  = LONG(inst);

  return (HWND) SendMessage(WBase::hClient, WM_MDICREATE, 0,
                                 (LONG) (LPMDICREATESTRUCT) &MdiCreate);
  }

/*------< Funktionspointer Liste >------*/
static LPSTR MenuText;
int oldL = 20000 ;
static void DrawUser_Time ()
  {
  if (IsIconic(WBase::hFrameWin))      // im verkleinerten Zustand raus!!!!
    return;

  HDC hDC = GetWindowDC (WBase::hFrameWin);
  SetBkColor (hDC,GetSysColor (COLOR_MENU));
  SetTextAlign (hDC,TA_BOTTOM | TA_RIGHT);

  char TimeStr[50];
  char outstr[128];
  int resolution = GetSystemMetrics (SM_CXSCREEN);
  LPSTR pfmt;
  if (resolution > 1000)
    pfmt = "%60.60s  " ;
  else
    pfmt = "%35.35s  " ;
  if (MenuText != NULL)
    wsprintf (outstr,pfmt,MenuText);
  else
    wsprintf (outstr,pfmt,LPSTR(""));
  packdate pdl;
  INTTIME t = Now() ;
  UnPackTime (t, &pdl);
  FormatDate (TimeStr,&pdl,"d.m.yyyy ");
  packtime pt;
  UnPackSeconds (t, &pt);
  FormatTime (TimeStr + lstrlen(TimeStr),&pt,"hh:mm:ss");
  int TimeLen = lstrlen(TimeStr);

  int len = lstrlen(outstr);
  RECT rcWnd;
  RECT rTxt;
  GetWindowRect (WBase::hFrameWin,&rcWnd);
  rTxt.bottom = GetSystemMetrics (SM_CYCAPTION) +
                GetSystemMetrics (SM_CYMENU) +
                2 * GetSystemMetrics (SM_CYBORDER) ;
  rTxt.top    = rTxt.bottom - (GetSystemMetrics (SM_CYMENU)
                               - 2 * GetSystemMetrics (SM_CYBORDER)
                              );
#ifdef WIN32
  int rc = 3 * GetSystemMetrics (SM_CXSMSIZE);  // vergroessern, verkleinern, Schliessen
#else
  int rc = GetSystemMetrics (SM_CXVSCROLL);
#endif

  int cx, cxTime;
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDC,outstr,len,&size);
  cx = size.cx;
  GetTextExtentPoint32 (hDC,TimeStr,TimeLen,&size);
  cxTime = size.cx;
#else
  cx = LOWORD(GetTextExtent (hDC,outstr,len));
  cxTime = LOWORD(GetTextExtent (hDC,TimeStr,TimeLen));
#endif

  rTxt.right  = rcWnd.right - rcWnd.left - 20 - rc;

  // Ausgabe des Datums und der Uhrzeit
  rTxt.left   = rTxt.right - cxTime - 20 - rc;

  ExtTextOut (hDC, rcWnd.right - rcWnd.left - 30 - rc,
                   rTxt.bottom,
                   ETO_OPAQUE | ETO_CLIPPED,
                   &rTxt,
                   TimeStr,
                   TimeLen,
                   LPINT (NULL)
             );


  rTxt.right = rTxt.left;
  rTxt.left   = rTxt.right - cx - 20 - rc;

  COLORREF OldColor = SetTextColor (hDC,RGB(0xFF,0,0));
  ExtTextOut (hDC,rTxt.right,
               rTxt.bottom,
               ETO_OPAQUE | ETO_CLIPPED,
               &rTxt,
               outstr,
               len,
               LPINT (NULL)
             );
  SetTextColor (hDC, OldColor);

  if (oldL < rTxt.left) {
    rTxt.right = rTxt.left ;
    rTxt.left = oldL ;
//    HPEN hP = SelectObject (hDC,GetStockObject (WHITE_PEN));
//    Rectangle (hDC,rTxt.left,rTxt.top,rTxt.right,rTxt.bottom);

    ExtTextOut (hDC,rTxt.left, rTxt.top,
                ETO_OPAQUE,
                &rTxt,
                NULL,
                0,
                LPINT (NULL)
               );

//    SelectObject (hDC,hP);
    oldL = rTxt.right ;
    }
  else
    oldL = rTxt.left ;

  // Schwarze Linie unter dem Menue
  #ifdef UEBERLEGT
  if (IsWindow (WBase::hClient)) {
    RECT rcClient;
    GetWindowRect (WBase::hClient,&rcClient);
    POINT pt;
    pt.x = rcClient.left;
    pt.y = rcClient.top + 4 * GetSystemMetrics (SM_CYBORDER) ;
    // ScreenToClient (WBase::hFrameWin,&pt);
    HPEN hP = HPEN (SelectObject (hDC,GetStockObject (BLACK_PEN)));

    MoveToEx (hDC,0,pt.y,NULL);
    LineTo (hDC,rcWnd.right - rcWnd.left,pt.y);

    SelectObject (hDC,hP);

    }
  #endif
  ReleaseDC (WBase::hFrameWin,hDC);
  }

static void DrawPendingRecalls ()
  {
  }

/******** Call Backfunktion des Hauptfensters ********/
#define SYSTIME_TIMER   100
extern void CheckAsyncFifo ();
extern void DestroyControl ();
extern void FrameIsActivated ();
void TestActivationMore ();
BOOL CheckScriptMenus (WORD wP);
BOOL CheckScriptMessageHooks (UINT m, WPARAM wP, LPARAM lP);
extern BOOL ZoomRectActive;
extern HWND GetActiveExtChild ();
extern BOOL IsFromDestroy ;
extern LONG FAR PASCAL MInterprete(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP);
extern BOOL InClientTransaction;
extern BOOL CallCommandInClientTransaction;
extern void SetBreakImmediately ();
extern void OnDrawClipboard (HWND hWnd,WPARAM wParam,LPARAM lParam);

/*
extern void EnumerateChildWindows (HWND hWnd);
*/

void doDelete (LONG lP)
  {
  BOOL OldIsFromDestroy = IsFromDestroy ;
  IsFromDestroy = TRUE ;
  LPMDICHILD inst = LPMDICHILD (lP);
  delete (inst);
  IsFromDestroy = OldIsFromDestroy ;
  }
static struct _OCL {
  LPMDICHILD inst;
  _OCL FAR *Next;
  } FAR *lpopenChildList;

void MarkToDelete (LONG lP)
  {
  _OCL FAR *h = (_OCL FAR *) GetGlobMem (sizeof (*h));
  h->Next = lpopenChildList;
  h->inst = LPMDICHILD (lP);
  lpopenChildList = h;
  }

static hash FAR *loadInsts;
void LoadIsInProgress (mdiChild *c)
  {
  if (loadInsts == NULL) loadInsts = new hash (57,LONGKEY);
  BOOL isDone = TRUE;
  loadInsts->SetData (LONG(c),&isDone,sizeof(isDone));
  }
void LoadIsDone (mdiChild *c)
  {
  if (loadInsts == NULL) loadInsts = new hash (57,LONGKEY);
  loadInsts->DelData (LONG(c));
  }
void delInstances ()
  {
  if (loadInsts)
    delete loadInsts;
  loadInsts = NULL;
  }
void deleteAllOpenChilds ()
  {
  if (lpopenChildList != NULL) {
    if (loadInsts == NULL) loadInsts = new hash (57,LONGKEY);
    BOOL oldBlockIsActive = BlockIsActive;
    BlockIsActive = FALSE;
    _OCL FAR *prev = NULL;
    for ( _OCL FAR *h = lpopenChildList ; h != NULL ; ) {
      _OCL FAR *next = h->Next;
      LPVOID isInLoad = loadInsts->GetData (LONG(h->inst));
      if (!isInLoad) {
        delete h->inst;
        FreeGlobMem (h);

        if (prev != NULL) prev->Next = next;
        else              lpopenChildList = next;
        }
      else
        prev = h;
      h = next;
      }
    BlockIsActive = oldBlockIsActive;
    }
  }


#ifndef WINHELP
extern DWORD dwCookie;   // fuer die HTML Hilfe, deklariert in DDSTOOL
#endif

DLLExport LONG _export FAR PASCAL FrameWndProc(HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG RetVal=0L;

  if (CheckScriptMessageHooks (msg, wP, lP))
    return 0L;

  switch (msg) {

    case WM_DRAWCLIPBOARD :
      OnDrawClipboard (hWnd,wP,lP);
      break ;

    //-------------------------------------------------------------------------
    // Menuleiste des Hauptfensters...
    // Die Menu-Eintraege werden je nach aktiven Eingabefeldern und dem Inhalt
    // der Zwischenablage enabled oder disabled (Cut, Copy, Paste)
    //-------------------------------------------------------------------------
    case WM_INITMENU :
      // ueberprueft ob Daten in der Zwischenablage => Aenderung des Menueintrages
      if (wP == (WPARAM(GetMenu(hWnd)))) {
        BOOL bInsertAllowed = FALSE;
        BOOL bCopyAllowed = FALSE;
        BOOL bCutAllowed = FALSE;


        //----------------------
        // Wer hat den Focus?
        //----------------------
        HWND hWndFocus = GetFocus ();
        if (IsWindow (hWndFocus)) {
          char lpszClassName[32];

          //-------------------------------------------
          // ist der Cursor in einem ToolEdit-Fenster?
          //-------------------------------------------
          GetClassName (hWndFocus, lpszClassName, sizeof(lpszClassName));
          if (!lstrcmp(lpszClassName, "WORDWIN")) {
            bInsertAllowed = TRUE;
            if (WWIsFieldSelected (hWndFocus)) {    // ist Text selektiert?
              bCopyAllowed = TRUE;
              bCutAllowed = TRUE;
              }
            }
          else {
            //---------------------------------------------------------------------
            // Sonst kann es sich nur um ein Formular oder ein Externchild handeln
            //---------------------------------------------------------------------
            cField FAR *field = GetActiveField();  // Hat ein cField den Fokus?
            if (field != NULL) {
              bInsertAllowed = TRUE;

              if (field->IsSomeTextSelected()) {   // ist dort Text selektiert?
                bCopyAllowed = TRUE;
                bCutAllowed = TRUE;
                }
              }
            }
          }


        if (OpenClipboard (hWnd)) {
          if (IsClipboardFormatAvailable(CF_TEXT) ||
              IsClipboardFormatAvailable(CF_OEMTEXT)) {
            EnableMenuItem (HMENU(wP), MI_Insert, bInsertAllowed ? MF_ENABLED : MF_GRAYED);
            }
          else {
            EnableMenuItem (HMENU(wP), MI_Insert, MF_GRAYED);
            }

          EnableMenuItem (HMENU(wP), MI_Copy, bCopyAllowed ? MF_ENABLED : MF_GRAYED);
          EnableMenuItem (HMENU(wP), MI_Cut, bCutAllowed ? MF_ENABLED : MF_GRAYED);

          CloseClipboard();
          return TRUE;
          }
        else            // Clipboard nicht verfuegbar
          return FALSE;
        }

      return TRUE;
      break;

//    case WM_INITMENUPOPUP :
//      if (BOOL(HIWORD(lP)))
//        EnableMenuItem (HMENU(wP),SC_RESTORE,MF_GRAYED);
//      break ;

    case WM_QUERYENDSESSION :
      AskUser (8022,MB_ICONEXCLAMATION | MB_OK);
      SetActiveWindow (hWnd);
      return 0;     // Die Marille gehoert zu der Sorte der Programme,
                    // die sich nicht so ohne weiteres Schliessen
                    // lassen !!
      break ;

    case WMU_PLAYSOUND:
      if (!GetAsync_cmdfifo()->IsCommandFifoEmpty()) {
        PostMessage(hWnd, msg, wP, lP);
        break;
        }
    case MM_WIM_OPEN:
    case MM_WIM_CLOSE:
    case MM_WIM_DATA:
    case MM_WOM_OPEN:
    case MM_WOM_CLOSE:
    case MM_WOM_DONE:
      SndOnSoundMsg(msg, wP, lP);
      break;

    case WM_TIMER:
      if (!InClientTransaction) {
        if (!CheckTimer (wP)) {
          DrawUser_Time ();
          DrawPendingRecalls ();
          TestActivationMore ();
          }
        }
      break ;

    case WM_TIMECHANGE:
      ResetSync();
      break ;

    case WM_CREATE:
      RetVal = CreateMdiClientWindow(hWnd);   // Clientwindow erzeugen...
      // Timer Erzeugen
      SetTimer (hWnd,SYSTIME_TIMER,1000,NULL);
      break ;

    case WM_DESTROY:                         // Applikation beenden
      // Abspeichern aller relevanten Konfigurationsdaten
#ifdef WINHELP
      WinHelp (hWnd, "DDS.HLP", HELP_QUIT, 0);
#else
      if (dwCookie)
        htmlhelp(NULL,
                NULL,
                HH_UNINITIALIZE,
                (DWORD)dwCookie) ; // Pass in cookie.
#endif
      PostQuitMessage(NULL);
      break;

    case WMU_DESTROYDDSLIST:
      {
      // DDSList FAR *ptr = (DDSList FAR *) lP;
      // delete ptr;
      }
      break ;

    case WM_SIZE :
      RetVal = DefFrameProc (hWnd, WBase::hClient, msg, wP, lP);
      ClientWnd.SetWndPos (hWnd, wP);
      break ;

#ifdef UEBERLEGT
#ifdef WIN32
    case WM_GETMINMAXINFO :
      {
      LPMINMAXINFO lpmmi = (LPMINMAXINFO)lP;

      int nx = GetSystemMetrics (SM_CXSCREEN);
      int ny = GetSystemMetrics (SM_CYSCREEN);
      int bx = GetSystemMetrics (SM_CXBORDER);
      int by = GetSystemMetrics (SM_CYBORDER);

      lpmmi->ptMaxSize.x = nx + 2 * bx;
      lpmmi->ptMaxSize.y = ny + 2 * by;
      }
      break;
#endif
#endif

    case UM_TOOLBARCHANGED :
      ClientWnd.SetWndPos (hWnd, 0);
      break ;

    case WMU_DESTROYCHILD:
      {
      if (InClientTransaction)
        MarkToDelete (lP);
      else
        doDelete (lP);
      }
      break ;
/*
    case WMU_DELETEOBJ:
      {
      OnWMUDeleteObj (lP);
      }
      break ;
*/
    case WM_QUERYNEWPALETTE:
    case WM_PALETTECHANGED:
      {
      if (msg == WM_QUERYNEWPALETTE) {
        static BOOL bInQueryPal = FALSE;
        if (bInQueryPal)
          break;
        bInQueryPal = TRUE;
        LRESULT temp = SendMessage(WBase::hClient,WM_MDIGETACTIVE, NULL, NULL);

#ifdef WIN32
        HWND tmpwin = HWND(temp);
#else
        HWND tmpwin = LOWORD(temp);
#endif

        HWND ctoolMain = 0;
        if (!IsWindow (tmpwin))
          tmpwin = GetActiveExtChild ();
        if (!IsWindow (tmpwin))
          tmpwin = ctoolMain = CTOOL_GetActiveTopWindow ();

        if (IsWindow(tmpwin)) {
          WORD changed = (WORD)SendMessage(tmpwin, WM_QUERYNEWPALETTE, NULL, NULL);
          if (!changed) {
            toAllDocuments (WM_PALETTECHANGED, WPARAM(tmpwin), NULL);
            if ((tmpwin != ctoolMain) && IsWindow(ctoolMain))
              SendMessage (ctoolMain,WM_PALETTECHANGED,WPARAM(tmpwin),0L);
            }
          RetVal = changed;
          }
        bInQueryPal = FALSE;
        }
      else {
        static BOOL bInPalChange = FALSE;
        if (bInPalChange)
          break;
        bInPalChange = TRUE;
        toAllDocuments (WM_PALETTECHANGED, wP, lP);
        HWND ctoolMain = CTOOL_GetActiveTopWindow ();
        if (IsWindow(ctoolMain))
          SendMessage (ctoolMain,WM_PALETTECHANGED,wP,lP);
        bInPalChange = FALSE;
        }
      }
      break ;

    case WMU_XFERDONE:
      toAllDocuments (msg, wP, lP);
      break;

    case WM_COMMAND:
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      if (!CheckScriptMenus (CRACKER_wID)) {
        if (CRACKER_wID >= FIRSTCHILD) {
          // Diese Kategorie von Befehlen geht den Interpreter gar nichts
          // an...
          RetVal = DefFrameProc(hWnd, WBase::hClient, WM_COMMAND, wP, lP);
          }
        else {
          switch (CRACKER_wID) {

            /*-----< Menuepunkte zur Anordnung der MDI-Kindfenster >------*/
            case MI_CASCADE:        // MDI-Kindfenster kaskadiert anordnen
              SendMessage(WBase::hClient, WM_MDICASCADE, 0, 0L);
              break;

            case MI_TILE:           // MDI-Kindfenster gekachelt anordnen
              SendMessage(WBase::hClient, WM_MDITILE, 0, 0L);
              break;

            case MI_ARRANGE:        // MDI-Symbole (Icons) neu ordnen
              SendMessage(WBase::hClient, WM_MDIICONARRANGE, 0, 0L);
              break;

            default:
              RetVal = MInterprete (hWnd,msg,wP,lP);
              break;
            }// switch wP

          }
        }
      }
      break ;

    case WM_NCPAINT :
      RetVal = DefFrameProc(hWnd, WBase::hClient, msg, wP, lP);
      DrawUser_Time ();
      DrawPendingRecalls ();
      break ;

    case WMU_CALLCOMMAND :
      if (InClientTransaction)
        CallCommandInClientTransaction = TRUE;
      else
        CheckAsyncFifo ();
      break ;

    case WMU_SOCKETEVENT :
      CheckSocketEvent( wP, lP );
      break ;

    case WM_SYSCOMMAND :
      //---------------------------------------------------------------------
      // bei RESTORE wird das Fenster sofort maximiert, ausser in der DMW.INI
      // gibt es einen Eintrag der das doch erlaubt!
      //---------------------------------------------------------------------
      if ((wP & 0xFFF0) == SC_RESTORE) {

        char retstr[5];

        // gibts einen Eintrag in der DMW.INI ?
        GetPrivateProfileString ("Profile", "ChangeSize", "no",
                                retstr,sizeof(retstr),
                                MYINI
                                );
        if (!lstrcmp (retstr,"yes"))
          //--------------------------------
          // ja Groesse aendern ist erlaubt
          RetVal = DefFrameProc(hWnd, WBase::hClient, msg, wP, lP);
        else
          //-----------------------------------------------
          // keine Groessenaenderung => maximiert = default
          RetVal = SendMessage (hWnd, msg, SC_MAXIMIZE, lP);
        }
      else if ((wP & 0xFFF0) == SC_CLOSE) {
        // Bitte an zentraler Stelle den Scheiss verarbeiten
        if (!ZoomRectActive)
          PostMessage (hWnd, WM_COMMAND, MI_QUIT, 0L);
        RetVal = 0L;
        }
      else
        RetVal = DefFrameProc(hWnd, WBase::hClient, msg, wP, lP);
      break ;

#ifdef UEBERLEGT
    case WM_ACTIVATE :
#endif
    case WM_SETFOCUS :
      ActivateMainToolBar (TRUE);
      if (GetFocus () == hWnd) {
        RetVal = DefFrameProc(hWnd, WBase::hClient, msg, wP, lP);
        }
      break ;

    case WM_ACTIVATEAPP :
      if (wP) FrameIsActivated ();
      break ;

    /*---------< Messages vom Testtool >---------------*/
    case WMU_GETDOCFIRSTNMBR :
    case WMU_GETDOCNEXTNMBR :
    case WMU_GETDOCTYPE :
    case WMU_OPENDOC :
    case WMU_DOCDATAEXIST :
    case WMU_GETTSTLIST :
      //      RetVal = TestToolFunc (msg,wP,lP);
      break ;

    case WM_CLOSE:
      if (ZoomRectActive)
        break;

    /*--------< Debug - Meldungen >---------*/
    case WMC_CLEARCEACHE :
      ClearCachedScript (LPSTR(GetPointer(lP)));
      break ;

    case WMC_SETBREAKPOINT :
      AddBreakpoint ((BPInfo FAR *) GetPointer (lP));
      break ;

    case WMC_REMOVEBREAKPOINT :
      RemoveBreakpoint ((BPInfo FAR *) GetPointer (lP));
      break ;

    case WMC_GETVARVAL :
      return SetPointer (DDSGetVarVal (NULL,LOWORD(lP),HIWORD(lP)));
      break ;

    case WMC_GETVARVAL_SCOPE :
      return SetPointer (DDSGetVarValExtended ((VarValExtended FAR *) GetPointer (lP)));
      break ;

    case WMC_GETSCRIPTHD :
      return LONG (DDSCopyScriptEntry (GetScriptEntry((CHAR FAR * ) GetPointer (lP))));
      break ;

    case WMC_SETVARBREAK :
      DDSSetVarBreak ((VarValExtended FAR *) GetPointer (lP));
      return 0L;
      break ;

    case WMC_CLEARVARBREAK :
      DDSClearVarBreak ((VarValExtended FAR *) GetPointer (lP));
      return 0L;
      break ;

    case WMC_GETSTACKINFO :
      return GetStackInfo (wP,(CallStackInfo FAR *) GetPointer (lP));
      break ;

    case WMC_GETCMDFIFOINFO :
      return LONG(DDSGetCmdFifoInfo (short (wP),(DebFifoInfo FAR *) GetPointer (lP)));
      break ;

    case WMC_FURTHERINFO :
      return LONG(DDSGetCmdMoreInfo (LOBYTE(wP),HIBYTE(wP),(DebFifoInfo FAR *) GetPointer(lP)));
      break ;

    case WMC_GETFIRSTCONTEXT :
      return GetDDSFirstContext ((ContextBuffer FAR *) GetPointer (lP));
      break ;

    case WMC_GETNEXTCONTEXT :
      return GetDDSNextContext ((ContextBuffer FAR *) GetPointer (lP));
      break ;

    case WMC_GETRECORDPTR :
      return LONG (DDSGetRecordPtr ((DBGGetRecordPtr FAR *) GetPointer (lP)));
      break ;

    case WMC_ISLISTPTR :
      return DDSIsListPtr ((DBGIsListPtr FAR *) GetPointer (lP));
      break ;

    case WMC_GETFUNCOFFS :
      {
      mdiChild *c = (mdiChild *) lP ;
      LPCONNEXTRAINFO e = c->_GetRecExtra() ;
      DWORD fOffs = (e != NULL) ? e->fOffs : 0L ;
      return fOffs ;
      }
      break ;

    case WMC_BREAKIMMEDIATELY :
      {
      SetBreakImmediately ();
      }
      break ;
    case WMC_GETRECDATA :
      {
      LPDBRECORD r = LPDBRECORD (lP) ;
      return SetPointer (r->Get(wP));
      }
      break ;
    case WMC_GETRECTABLE :
      {
      LPDBRECORD r = LPDBRECORD (lP) ;
      return MAKELONG(r->GetTableID(),r->GetVersion());
      }
      break ;
    case WMC_GETNEXTINCYCL :
      {
      LPDBRECORD r = LPDBRECORD (lP) ;
      if (r != NULL)
        return LONG (r->NextInCycl);
      else
        return NULL;
      }
      break ;
    case WMC_CLOSE :
      FatalAppExit (0,"Restool Debugger sends Close");
      break ;
    default:
      if (msg >= WM_USER) {
        RetVal = MInterprete (hWnd,msg,wP,lP);
        }
      else {
        RetVal = DefFrameProc (hWnd, WBase::hClient, msg, wP, lP);
        }

      break;
    }// switch msg

  return RetVal ;
  }



LPMDIWNDLIST FirstChild, LastChild;


MDIWndList::MDIWndList (HWND hWnd)
  {
  hWndChild = hWnd;
  }


void InsertMDIList (LPMDIWNDLIST lpmdiwndlist)
  {
  if (FirstChild == NULL) {
    FirstChild = lpmdiwndlist;
    FirstChild->Next = lpmdiwndlist;
    FirstChild->Prev = lpmdiwndlist;
    LastChild = FirstChild;
    }
  else {
    lpmdiwndlist->Next = FirstChild;
    lpmdiwndlist->Prev = LastChild;
    FirstChild->Prev = lpmdiwndlist;
    LastChild->Next = lpmdiwndlist;
    FirstChild = lpmdiwndlist;
    }
  }

void DeleteMDIList (HWND hWnd)
  {
  if ((FirstChild == LastChild) && (FirstChild->hWndChild == hWnd)) {
    delete FirstChild;
    FirstChild = NULL;
    LastChild = NULL;
    return;
    }

  for (LPMDIWNDLIST lpc = FirstChild; lpc != LastChild; lpc = lpc->Next)
    if (lpc->hWndChild == hWnd) {
      lpc->Prev->Next = lpc->Next;
      lpc->Next->Prev = lpc->Prev;

      if (lpc == LastChild)
        LastChild = lpc->Prev;
      if (lpc == FirstChild)
        FirstChild = lpc->Next;

      delete lpc;
      break;
      }

  }


DLLExport LONG _export FAR PASCAL ChildWndProc(HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG RetVal;
  mdiChild *pmdich = GetWindowInst(hWnd);
  // Aufruf von DefDocProc

  switch (msg) {
    case WM_CREATE:
      {
      LPCREATESTRUCT    lpCreate;
      LPMDICREATESTRUCT lpMdiCreate;

      lpCreate    = (LPCREATESTRUCT)    lP;
      lpMdiCreate = (LPMDICREATESTRUCT) lpCreate->lpCreateParams;
      SetWindowLong(hWnd, GWL_HWINFO, (lpMdiCreate->lParam));
      pmdich = LPMDICHILD (lpMdiCreate->lParam) ;
      // DefaultHandler muss gueltig sein, wenn zusaetzliches WindowWord
      // gesetzt wurde
      pmdich->DefaultHandler_base = (FARPROC) DefMDIChildProc;

      LPMDIWNDLIST lpMDIWndList = new MDIWndList(hWnd);
      InsertMDIList (lpMDIWndList);
      }
      break;

    case WM_MDIACTIVATE :
      {
      BOOL bActivate;
#ifdef WIN32
      bActivate = (hWnd == HWND(lP));
#else
      bActivate = wP;
#endif

      if (bActivate) {
        ActivateControl (hWnd);
        SendMessage(WBase::hFrameWin, WM_QUERYNEWPALETTE, NULL, NULL);
        }
      else
        DeactivateControl (hWnd);
      if (pmdich)
        ActivateStatBar (pmdich,bActivate);
      }
      break;

    case WM_DESTROY:
      DeleteMDIList (hWnd);
      // hier wird kein break benoetigt
    default:
      BOOL done = FALSE ;

      if (pmdich != NULL)
        RetVal = pmdich->ChildProc (hWnd,msg,wP,lP,&done);

      if (!done)
        RetVal = DefMDIChildProc(hWnd, msg, wP, lP);

      break;
    }
  return RetVal ;
  }

/******* Methoden fuer WBase **********/
extern LPSTR SucheParameter (LPSTR kennung);
WBase::WBase(HINSTANCE hInst)
  {
  WNDCLASS    WndClass;

  // Initialisierung der Statischen Daten
  hInstance = hInst;     // aktuelle Instanz sichern
  hClient   = NULL ;
  hFrameWin = NULL ;
  hMenu     = NULL ;

  /*---------< Registrierung der MDI-FrameWindow-Fensterklasse >-------*/
  WndClass.style         = CS_VREDRAW | CS_HREDRAW ;
  WndClass.lpfnWndProc   = WNDPROC (FrameWndProc) ;
  WndClass.cbClsExtra    = 0 ;
  WndClass.cbWndExtra    = 0 ;
  WndClass.hInstance     = hInst ;
  WndClass.hIcon         = LoadIcon (hInst, (LPSTR) "BaseIcon") ;
  WndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
  WndClass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
  WndClass.lpszMenuName  = (LPSTR) "Menu";
  WndClass.lpszClassName = (LPSTR) "MDIFRAME" ;

  if (!RegisterClass (&WndClass)) FatalExit(0);

  /*---------< Registrierung des Client - Fensters >----------*/
  ClientWnd.RegisterMDIClient (hInst);

  /*--------< Registrierung der MDI-Kindfenster-Fensterklasse >------*/
  WndClass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
  WndClass.lpfnWndProc   = WNDPROC (ChildWndProc) ;
  WndClass.cbWndExtra    = sizeof(LPMDICHILD);
  WndClass.hIcon         = LoadIcon (hInst, (LPSTR) "ChildIcon") ;
  WndClass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
  WndClass.lpszMenuName  = NULL;          // MDI-Kindfenster
                                          // besitzen kein Menue
  WndClass.lpszClassName = (LPSTR) "MDICHILD" ;
  if (!RegisterClass (&WndClass)) FatalExit(0);

  /*--------< Registrierung der Group-Fensterklasse >------*/
  WndClass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
  WndClass.style |= CS_DBLCLKS;
  WndClass.lpszClassName = "Group";
  if (!RegisterClass(&WndClass)) FatalExit(0);

  /*--------< Registrierung der Diagramm-Fensterklasse >------*/
  WndClass.style         = 0 ;
  WndClass.lpfnWndProc   = WNDPROC (sDiagWndProc) ;
  WndClass.cbWndExtra    = sizeof(LPMDICHILD);
  WndClass.hIcon         = LoadIcon (hInst, (LPSTR) "ChildIcon") ;
  WndClass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
  WndClass.lpszMenuName  = NULL;
  WndClass.lpszClassName = (LPSTR) "DIAGWND" ;
  if (!RegisterClass (&WndClass)) FatalExit(0);

  /*--------< Laden des Menues >------------------*/
  hMenu     = LoadMenu(hInstance, (LPSTR) "Menu");

  /*--------< Initialisieren der Status - Leiste >-------------*/

  PrgStat.Init ();
  PrgStat.Register (hInstance);

  LPSTR FrameName = Ltx(1);
  if (FrameName == NULL)
    FrameName = LRString (FRAMENAMEID);
  hFrameWin = CreateWindow ((LPSTR) "MDIFRAME", FrameName,
                          WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_MAXIMIZE,
                          0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL,
                          hMenu,
                          hInstance, NULL) ;

  if(!hFrameWin)      FatalExit(0);

  SndSetMsgWnd(hFrameWin);


  /*-------< Erzeugen des Status - Bar's >-----*/
  PrgStat.Create (hFrameWin,hInstance);

  /*-------< Erzeugen eines Voll - Bildschirm - Fensters >-----*/
  if (SucheParameter ("MEMFILENAME") != NULL)
    ShowWindow(hFrameWin, SW_HIDE);
  else {
    // gibts einen Eintrag in der DMW.INI ?
    char retstr[5];
    GetPrivateProfileString ("Profile", "ChangeSize", "no",
                            retstr,sizeof(retstr),
                            MYINI
                            );
    if (!lstrcmp (retstr,"yes")) {
      ShowWindow(hFrameWin, SW_SHOW);
      int w = GetSystemMetrics (SM_CXSCREEN);
      int h = GetSystemMetrics (SM_CYSCREEN);
      SetWindowPos(hFrameWin,NULL,0,0,w,h,SWP_NOZORDER);
      }
    else
      ShowWindow(hFrameWin, SW_MAXIMIZE);   // !!! Volle Bulle
    }
  UpdateWindow(hFrameWin);
  }

void mdiChild::Create (LPSTR Name)
  {
  GetOutData()->_MyHandle = CreateMdiChildWindow (Name,this,0,0,0,0);
  }

/*--------< Senden einer Meldung an alle Dokumente >------*/
extern void toAllExtChilds (UINT msg, WPARAM wP, LPARAM lP);
void toAllDocuments (UINT msg, WPARAM wP, LPARAM lP)
  {
  HWND hwChild;
  hwChild = GetWindow(WBase::hClient, GW_CHILD) ;

  while (hwChild) {
    while(hwChild && GetWindow(hwChild,GW_OWNER)) {
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);
      }

    if(hwChild) { // Endlich gefunden
      SendMessage (hwChild,msg,wP,lP);
      hwChild = GetWindow (hwChild,GW_HWNDNEXT);
      }
    }
  toAllExtChilds (msg,wP,lP);
  }

/*------< Ermitteln der Anzahl der Angezeigten Dokumente >-----*/
int GetDocumentCount ()
  {
  HWND hwChild;
  int Res = 0 ;
  hwChild = GetWindow(WBase::hClient, GW_CHILD) ;

  while (hwChild) {
    Res ++ ;
    while(hwChild && GetWindow(hwChild,GW_OWNER)) {
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);
      }

    if(hwChild) { // Endlich gefunden
      hwChild = GetWindow (hwChild,GW_HWNDNEXT);
      }
    }
  return Res ;
  }

BOOL IsAnyMaximized ()
  {
  HWND hWnd = HWND (SendMessage (WBase::hClient,WM_MDIGETACTIVE,0,0L));
  return ((IsWindow(hWnd)) && (IsZoomed(hWnd)));
  }

void DisableWindowMenu ()
  {
  int WndPos = MI_WINDOW ;
  if (IsAnyMaximized ()) WndPos += 1;
  EnableMenuItem (WBase::hMenu,WndPos,MF_BYPOSITION | MF_GRAYED);
  DrawMenuBar (WBase::hFrameWin);
  }

void EnableWindowMenu ()
  {
  int WndPos = MI_WINDOW ;
  if (IsAnyMaximized ()) WndPos += 1;
  EnableMenuItem (WBase::hMenu,WndPos,MF_BYPOSITION | MF_ENABLED);
  DrawMenuBar (WBase::hFrameWin);
  }

/////////////////////////////////////////////////////////////////
//  Allgemeine Scriptfunktionen
/////////////////////////////////////////////////////////////////
#pragma pack(1)
struct SetMenuText_param {
  WORD parSize;
  DWORD txt;
  };
#pragma pack()

BOOL SetMenuText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    if (MenuText != NULL) FreeGlobMem (MenuText);
    MenuText = NULL;
    SetMenuText_param FAR *par = (SetMenuText_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    if (txt != NULL) {
      MenuText = LPSTR(GetGlobMem (lstrlen(txt)+1));
      lstrcpy (MenuText,txt);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetMenuText_param FAR *par = (SetMenuText_param FAR *) param;
    c->SetlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetMenuText_param FAR *par = (SetMenuText_param FAR *) param;
    if (MenuText != NULL) FreeGlobMem (MenuText);
    MenuText = NULL;
    c->ClearlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct AddMenuCommand_param {
  WORD  parSize;
  DWORD txt;
  DWORD procPtr;
  DWORD _PopNr;
  DWORD _CmdId;
  DWORD _parFlag;
  DWORD _MainText;
  };
#pragma pack()

#pragma pack(1)
struct MenuCommandList {
  MenuCommandList FAR *Next;
  WORD  CmdId;
  DWORD ProcPtr;
  mdiChild *c;
  };
#pragma pack()

typedef MenuCommandList FAR *LPMCL;
LPMCL MenuCommands;
BOOL AddToMenuList (WORD Id,DWORD Cmd,mdiChild *c)
  {
  for ( LPMCL FAR *h = &MenuCommands ; *h != NULL ; h = &(*h)->Next) {
    if ((*h)->CmdId == Id) return FALSE ;
    }
  LPMCL n = LPMCL (GetGlobMem (sizeof(*n)));
  n->CmdId = Id ;
  n->ProcPtr = Cmd;
  n->c = c;
  *h = n;

  return TRUE ;
  }

BOOL CheckScriptMenus (WORD wP)
  {
  for ( LPMCL h = MenuCommands ; h != NULL ; h = h->Next) {
    if (h->CmdId == wP) {
      h->c->ExCuteProc (h->ProcPtr,EM_LOAD | EM_CHANGETOTRUE);
      h->c->ExCuteProc (h->ProcPtr,EM_RESET);  // ist wohl besser so (Martin)
      return TRUE ;
      }
    }
  return FALSE ;
  }

void RemoveFromMenuList (WORD Id)
  {
  for ( LPMCL FAR *h = &MenuCommands ; *h != NULL ; h = &(*h)->Next) {
    if ((*h)->CmdId == Id) {
      LPMCL x = *h;
      *h = x->Next;
      FreeGlobMem (x);
      break ;
      }
    }
  }

BOOL AddMenuCommand (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    HMENU     MainMenu = GetMenu (WBase::hFrameWin);
    AddMenuCommand_param FAR *par = (AddMenuCommand_param FAR *) param;

    //--------------------------------------------------------------------------
    // wenn ein MDI-Fenster geoeffnet ist und sich das Fenster im Vollbild-Modus
    // befindet, verschiebt sich der Menuindex fuer die Submenus um das
    // Systemmenu des MDI-Fensters
    //--------------------------------------------------------------------------

    BOOL bMDI_IsMaximized;
#ifdef WIN32
    SendMessage(WBase::hClient, WM_MDIGETACTIVE, 0, LPARAM(&bMDI_IsMaximized));
#else
    bMDI_IsMaximized = BOOL(HIWORD(SendMessage(WBase::hClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
    int Index = bMDI_IsMaximized ? 1 : 0;

    DBINT flags;
    if (par->parSize >= sizeof(*par) - sizeof(DWORD))
      flags = c->ReadConstInt (par->_parFlag);
    else
      flags = 0;

    int mid = c->ReadConstInt(par->_PopNr) + Index;
    HMENU  hSub = GetSubMenu (MainMenu,mid);
    if (par->parSize >= sizeof(*par)) {
      char resTxt[256];
      LPSTR MainText = LPSTR (c->ReadlData (par->_MainText));
      if ((!hSub) ||
          (GetMenuString (MainMenu,mid,resTxt,sizeof(resTxt),MF_BYPOSITION) == 0) ||
          (lstrcmp (resTxt,MainText) != 0)) {
        hSub = CreateMenu ();
        InsertMenu (MainMenu,mid,MF_STRING | MF_POPUP | MF_BYPOSITION,UINT (hSub),MainText);
        }
      }
    LPSTR Text = LPSTR(c->ReadlData (par->txt));
    DBWIN_ASSERT (Text != NULL);
    WORD CmdId = WORD(c->ReadConstInt(par->_CmdId));
    if (AddToMenuList (CmdId,par->procPtr,c)) {
      AppendMenu (hSub,MF_STRING | flags,CmdId,Text);
      DrawMenuBar (WBase::hFrameWin);
      }
    else {
      ModifyMenu (hSub,CmdId,MF_BYCOMMAND | MF_STRING | flags,CmdId,Text);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    AddMenuCommand_param FAR *par = (AddMenuCommand_param FAR *) param;
    c->SetlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    if (par->parSize >= sizeof(*par) - sizeof(DWORD))
      c->SetlConnection (par->_parFlag,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    HMENU     MainMenu = GetMenu (WBase::hFrameWin);
    AddMenuCommand_param FAR *par = (AddMenuCommand_param FAR *) param;

    BOOL bMDI_IsMaximized;
#ifdef WIN32
    SendMessage(WBase::hClient, WM_MDIGETACTIVE, 0, LPARAM(&bMDI_IsMaximized));
#else
    bMDI_IsMaximized = BOOL(HIWORD(SendMessage(WBase::hClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
    int Index = bMDI_IsMaximized ? 1 : 0;

    int mpos = c->ReadConstInt(par->_PopNr) + Index;
    HMENU  hSub = GetSubMenu (MainMenu,mpos);
    WORD CmdId = WORD(c->ReadConstInt(par->_CmdId));
    RemoveFromMenuList (CmdId);
    RemoveMenu (hSub,CmdId,MF_BYCOMMAND);
    c->ClearlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    if (par->parSize >= sizeof(*par) - sizeof(DWORD))
      c->ClearlConnection (par->_parFlag,LPSTR(param)-sizeof(WORD));
    if (par->parSize >= sizeof(*par)) {
      c->ClearlConnection (par->_MainText,LPSTR(param)-sizeof(WORD));
      char resTxt[256];
      if (GetMenuString (hSub,0,resTxt,sizeof(resTxt),MF_BYPOSITION) == 0) {
        RemoveMenu (MainMenu,mpos,MF_BYPOSITION);
        DestroyMenu (hSub);
        }
      }
    DrawMenuBar (WBase::hFrameWin);
    }
  return FALSE ;
  }

//////////////////////////////////////////////////////////
//  Setzen des Textes des Hauptfensters
//////////////////////////////////////////////////////////
#pragma pack(1)
struct SetPrgCaption_param {
  WORD parSize;
  DWORD txt;
  };
#pragma pack()

BOOL SetPrgCaption (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetPrgCaption_param FAR *par = (SetPrgCaption_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    SetWindowText (WBase::hFrameWin,txt);
    }
  if (mode & EM_FIXCONNECTION) {
    SetPrgCaption_param FAR *par = (SetPrgCaption_param FAR *) param;
    c->SetlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetPrgCaption_param FAR *par = (SetPrgCaption_param FAR *) param;
    c->ClearlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct AddMessageHook_param {
  WORD  parSize;
  DWORD result;
  DWORD ProcPtr;
  DWORD msg;
  DWORD wParam;
  DWORD lParam;
  };
#pragma pack()

#pragma pack(1)
struct MessageHookList {
  MessageHookList FAR *next;
  mdiChild *c;
  AddMessageHook_param FAR *p;
  };
#pragma pack()

typedef MessageHookList FAR *LPMHL;

LPMHL MessageHooks = NULL;
BOOL CheckScriptMessageHooks (UINT m, WPARAM wP, LPARAM lP)
  {
  for (LPMHL h = MessageHooks; h != NULL; h = h->next) {
    h->c->WritelData(h->p->msg,&m,sizeof(m),NULL);
    h->c->WritelData(h->p->wParam,&wP,sizeof(wP),NULL);
    h->c->WritelData(h->p->lParam,&lP,sizeof(lP),NULL);
    h->c->ExCuteProc(h->p->ProcPtr,EM_LOAD | EM_CHANGETOTRUE);
    h->c->ExCuteProc(h->p->ProcPtr,EM_RESET);
    LPWORD lpres = (LPWORD)h->c->ReadlData(h->p->result);
    if ((lpres != NULL) && (*lpres != 0))
      return TRUE;
    }
  return FALSE ;
  }

BOOL AddMessageHook (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPMHL n = LPMHL (GetGlobMem (sizeof(*n)));
    n->p = (AddMessageHook_param FAR *) param;
    n->c = c;
    n->next = MessageHooks;
    MessageHooks = n;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    for ( LPMHL FAR *h = &MessageHooks ; *h != NULL ; h = &(*h)->next) {
      if ((*h)->p == (AddMessageHook_param FAR *) param) {
        LPMHL tofree = *h;
        *h = tofree->next;
        FreeGlobMem (tofree);
        break ;
        }
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFrameWindowHandle_param {
  WORD  parSize;
  DWORD hWnd;
  };
#pragma pack()

BOOL GetFrameWindowHandle (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFrameWindowHandle_param FAR *par = (GetFrameWindowHandle_param FAR *) param;
    c->WritelData(par->hWnd,&WBase::hFrameWin,sizeof(WBase::hFrameWin),NULL);
    }
  return FALSE ;
  }

BOOL GetClientWindowHandle (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFrameWindowHandle_param FAR *par = (GetFrameWindowHandle_param FAR *) param;
    HWND hWnd = c->OutWnd();
    c->WritelData(par->hWnd,&hWnd,sizeof(hWnd),NULL);
    }
  return FALSE ;
  }


