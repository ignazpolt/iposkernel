////////////////////////////////////////////////////////////////
//  Arbeiten mit Marilleresourcen
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/restool.cpv   1.94   16 Feb 2000 15:31:06   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/restool.cpv  $
// 
//    Rev 1.94   16 Feb 2000 15:31:06   Wolfgang
// 1.) PTY als CPL-Dateien.
// 
//    Rev 1.93   29 Sep 1999 16:55:42   Wolfgang
// 1.) Vor Generieren Init-/DoneModuleHash aufrufen.
// 
//    Rev 1.92   29 Jun 1999 19:18:16   Martin
// IchBinDasRestool
// 
//    Rev 1.91   26 Apr 1999 18:11:40   Wolfgang
// 1.) Fenstername bei Makefile generieren geaendert.
// 2.) MAK-Files bei File Open beruecksichtigt.
// 3.) Menu-Kurzhilfe wegen nicht Funktionierens und Sinnlosigkeit ausgeschaltet.
// 
//    Rev 1.90   26 Mar 1999 18:14:28   Wolfgang
// 1.) Nachrichten fuer Case-Sensitive- und Wort-Suche weiterleiten.
// 2.) Nachricht fuer Makefile-Generieren weiterleiten.
// 
//    Rev 1.89   18 Mar 1999 14:07:30   Wolfgang
// 1.) Angabe des Feldes bei SB_SETTEXT ueber Konstante.
// 
//    Rev 1.88   17 Mar 1999 19:24:16   Wolfgang
// 1.) CloseAll unterscheidet, ob mit Programm schliessen oder nur alle Files.
// 2.) File bei oeffnen aus Recent-File-List entfernen.
// 3.) Restore nach WONSCRIP verschoben.
// 
//    Rev 1.87   16 Mar 1999 19:41:16   Wolfgang
// 1.) MainFile TRUE bei ShowScript.
// 
//    Rev 1.86   16 Mar 1999 17:07:14   Wolfgang
// 1.) SaveAllWorkSpaceEntrys bei Close aufrufen.
// 
//    Rev 1.85   16 Mar 1999 16:12:46   Wolfgang
// 1.) Zuerst alle auf speicherbar pruefen, dann alle schliessen.
// 2.) Workspace speichern und wiederherstellen.
// 3.) ShowScript mit NULL zur Fenstererzeugung verwenden.
// 
//    Rev 1.84   09 Mar 1999 16:30:24   Wolfgang
// 1.) Letzten ausgewaehlten Filter permanent merken.
// 2.) MAK-Files fuer Generiere Scripts.
// 
//    Rev 1.83   02 Nov 1998 11:48:52   Gerhold
// Syntax-Coloring Verbesserungen
// 
//    Rev 1.82   29 Oct 1998 11:00:40   Gerhold
// Syntax-Coloring verbessert
// 
//    Rev 1.81   05 Oct 1998 11:27:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.80   14 Aug 1998 18:56:10   Hannes
// Include / Source Pfad wirklich trennen
// 
//    Rev 1.79   16 Jun 1998 11:09:20   Martin
// ExePath
// 
//    Rev 1.78   22 Apr 1998 09:48:18   Gerhold
// MI_FINDMATCHINBRACES
// 
//    Rev 1.77   03 Feb 1998 18:10:10   Gerhold
// 16-32-Bit Problemchen
// 
//    Rev 1.76   19 Jan 1998 20:17:16   Hannes
// 
//    Rev 1.75   12 Jan 1998 18:19:02   Hannes
// WMC_CLOSE
// 
//    Rev 1.74   02 Jan 1998 10:12:42   Gerhold
// 16 -> 32 Bit Fehlerkorrekturen
// 
//    Rev 1.73   15 Dec 1997 21:57:52   Hannes
// 
//    Rev 1.72   15 Dec 1997 21:46:58   Hannes
// 
//    Rev 1.71   15 Dec 1997 20:32:18   Hannes
// 
//    Rev 1.70   15 Dec 1997 17:37:14   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.69   21 Nov 1997 15:55:00   Hannes
// Feinschliff Debugger
// 
//    Rev 1.68   19 Nov 1997 18:44:20   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.67   17 Nov 1997 09:10:34   Gerhold
// Versuche mit Named Pipes
// 
//    Rev 1.66   06 Nov 1997 19:32:30   Hannes
// Properties in Updatescripts / Views
// 
//    Rev 1.65   05 Nov 1997 09:48:12   Gerhold
// 32 Bit
// 
//    Rev 1.63   28 Aug 1997 15:50:20   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.62   19 Feb 1997 12:14:46   Hannes
// File oeffen -> Anbieten von meheren Extensions
// 
//    Rev 1.61   26 Nov 1996 08:10:04   HANNES
// Automatischer Update
// 
//    Rev 1.60   28 Oct 1996 08:47:12   HANNES
// 
//    Rev 1.59   21 Oct 1996 18:57:08   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.58   02 Jul 1996 15:56:44   GERHOLD
// MI_SEARCHUP
// 
//    Rev 1.55   04 Feb 1996 15:51:58   gerhold
// DMWAPI_SetClassNames
// 
//    Rev 1.54   02 Feb 1996 10:50:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.53   03 Jan 1996 15:48:36   HANNES
// DBClean_Init
// 
//    Rev 1.52   27 Aug 1995 13:00:20   HANNES
// 
//    Rev 1.51   24 Aug 1995 00:16:42   HANNES
// Debuggerverbesserungen
// 
//    Rev 1.50   23 Aug 1995 11:05:14   GERHOLD
// 
//    Rev 1.49   11 Jul 1995 12:46:08   HANNES
// Debuggerdefinitionen umgelagert
// 
//    Rev 1.48   26 Jun 1995 10:26:42   GERHOLD
// Das Generiern der Resourcen wird angezeigt.
// 
//    Rev 1.47   09 Jun 1995 00:30:04   HANNES
// No change.
// 
//    Rev 1.46   07 Jun 1995 12:14:32   GERHOLD
// IsDialogMessage fuer Suchen und Ersetzen in der MessageLoop
// 
//    Rev 1.45   23 May 1995 12:02:04   GERHOLD
// Tabllen-Menu-Kommandos ... pruefen auf geoeffnete MDI-Childs.
// 
//    Rev 1.44   15 May 1995 08:50:52   GERHOLD
// 
//    Rev 1.43   15 May 1995 08:30:22   HANNES
// structs direkt im script definieren
// 
//    Rev 1.42   12 May 1995 15:02:56   GERHOLD
// 
//    Rev 1.41   26 Apr 1995 15:26:48   HANNES
// 
//    Rev 1.40   24 Apr 1995 15:43:40   GERHOLD
// 
//    Rev 1.39   31 Mar 1995 12:50:56   GERHOLD
// bei der CmdLine war noch ein bissel Mist
// 
//    Rev 1.38   29 Mar 1995 15:54:36   HANNES
// 
//    Rev 1.37   27 Mar 1995 10:40:30   GERHOLD
// Menus verbessert
// 
//    Rev 1.36   23 Mar 1995 11:52:08   GERHOLD
// 
//    Rev 1.35   03 Mar 1995 11:05:22   HANNES
// 
//    Rev 1.34   24 Feb 1995 11:11:26   GERHOLD
// 
//    Rev 1.33   16 Feb 1995 19:48:50   GERHOLD
// 
//    Rev 1.32   16 Feb 1995 12:34:08   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.31   29 Jan 1995 11:48:02   HANNES
// 
//    Rev 1.30   26 Jan 1995 11:52:58   GERHOLD
// 
//    Rev 1.29   24 Jan 1995 09:57:04   GERHOLD
// in WM_SIZE vorsichtshalber alle Fenster auf Existenz ueberpruefen!
// 
//    Rev 1.28   20 Jan 1995 15:53:50   HANNES
// 
//    Rev 1.27   18 Jan 1995 17:04:56   GERHOLD
// ein bisserl in der WndProc rumgespielt
// 
//    Rev 1.26   17 Jan 1995 15:52:28   Hannes
// Menue - Fehlerkorrektur
// 
//    Rev 1.25   13 Jan 1995 16:54:24   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.24   10 Jan 1995 15:01:08   HANNES
// 
//    Rev 1.23   09 Jan 1995 16:39:28   HANNES
// 
//    Rev 1.22   09 Jan 1995 14:32:56   GERHOLD
// 
//    Rev 1.21   03 Jan 1995 18:39:06   GERHOLD
// 
//    Rev 1.20   03 Jan 1995 12:04:10   HANNES
// 
//    Rev 1.19   03 Jan 1995 11:26:22   GERHOLD
// Neue Datei oeffnen; Zuletzt bearbeitete Dateien mit <ALT + #> oeffnen
// 
//    Rev 1.18   03 Jan 1995 09:56:56   HANNES
// Debuginfo lesen und wieder aufrauemen
// 
//    Rev 1.17   02 Jan 1995 18:33:26   HANNES
// 
//    Rev 1.16   02 Jan 1995 16:42:34   GERHOLD
// Font Informationen lesen und schreiben
// 
//    Rev 1.15   02 Jan 1995 12:20:32   HANNES
// 
//    Rev 1.14   02 Jan 1995 10:42:30   GERHOLD
// Aenderungen wegen neuer Toolbar
// 
//    Rev 1.13   02 Jan 1995 09:31:06   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.9   07 Nov 1994 11:49:04   GERHOLD
// WM_SIZE ... Statusbar bekommt ebenfalls WM_SIZE
// 
//    Rev 1.8   19 Oct 1994 22:29:00   hannes
// SQL - Converter Aufruf
// 
//    Rev 1.7   30 Sep 1994 14:39:18   GERHOLD
// 
//    Rev 1.6   15 Sep 1994 15:09:56   GERHOLD
// einzelne Teile in der Main_WndProc von hwnd auf hwndMDIClient umgebaut.
// 
//    Rev 1.5   14 Sep 1994 16:58:20   GERHOLD
// Erweiterungen fuer Statuszeile
// 
//    Rev 1.4   01 Aug 1994 16:15:56   HANNES
// FRegisterControl
// 
//    Rev 1.3   25 Jul 1994 09:37:10   GERHOLD
// Formate & Farben
// 
//    Rev 1.1   12 Jul 1994 14:44:24   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:54:50   HANNES
// Neuuebernahme clinicum
//

#ifndef __cplusplus
  #define __cplusplus
#endif  

#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include "dds32.h"

#ifndef WIN32
#include "ctl3d.h"
#endif

#include "globmem.h"
#include "restool.hpp"
#define MODULENUM 143
#include "winass.hpp"
//#include "subclass.hpp"
#include "commdlg.h"
#include "hash.hpp"       // wird benoetigt um COMPILE zufriedenzustellen
#include "compile.hpp"    // GetIncludeFileName

#include "rlist.hpp"
#include "misc.hpp"
#include "font.hpp"

#include "cfield.hpp"
#include "wordwin.hpp"
#define NODLL
#include "toolbar.hpp"

#ifndef WIN32
  #include <custcntl.h>
  #include "muscroll.hpp"
  #include "muexport.hpp"
#endif

#include "statbar.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"


#include "blandmdi.h"
#include "blandmdi.hpp"
#include "msdntb.h"

#include "scdb.hpp"
#include "communic.hpp"

#include "scripthd.hpp"

#ifdef PIPE_ENABLED
  #include "ddspipe.hpp"
#endif

// Fuer div. Includefiles zur sourcecode - Kompatibilitaet
BOOL BlockIsActive;
fifo FAR *AsyncFifoPtr;

UINT        iMSGFind;

HWND hwndFrame = NULL;      // Handle to main window

HWND hwndMDIClient = NULL;      // Handle to MDI client
HWND hWndToolbar = NULL;
HWND hWndToolbarDialog = NULL;
//HWND hWndToolbarForm = NULL;

HWND hWndDock = NULL;
HWND hWndCombo = NULL;
HWND hWndStatusbar = NULL;
HWND hWndProjectList = NULL;

HMENU hMenuMain, hMenuDialog, hMenuWndInMDI;
// Handles der Popup-Menus in das die Childs geschrieben werden
HMENU hMenuMainWindow, hMenuDialogWindow, hMenuWndInMDIWindow;

HFONT hFontEdit = 0;

LONG styleDefault = 0;         // Default style bits for child windows

//static LOGFONT lfEdit = { -13, 0, 0, 0, 400, 0, 0, 0, 0, 1, 2, 1, 31, "Courier"};

BOOL CloseAllChildren (BOOL closeProgram);

#ifdef WIN32
#ifdef DEBUG
#define SHAREMEM
#endif
#endif

DLLExport void _export WINAPI FreeLinMem () ;

extern HFONT GetEditorFont ();
extern void WriteEditorFont (HFONT hFont);

extern LPSTR IniFile();

///////////////////////////////////////////////////////////////////////
//  Ermitteln des Startdirectorys
///////////////////////////////////////////////////////////////////////
extern DLLExport LPSTR _export FAR PASCAL SetStartDir (LPSTR DirName, LPSTR IniName);
extern DLLExport void _export WINAPI SetIchBinDasRestool (void);

static BOOL first_time = TRUE;
static char StartPathName[128] = "";

LPSTR GetStartDirName ()
  {
  if (first_time) {
    _getdcwd(0, StartPathName, 55);
    int len = lstrlen(StartPathName);
    if (StartPathName[len - 1] != '\\')
      StartPathName[len++] = '\\';
    first_time = FALSE;
    }
  return StartPathName;
  }

void SetStartDirName (LPSTR dirname)
  {
  lstrcpy (StartPathName, SetStartDir(dirname, "RESTOOL.INI"));
  if (StartPathName == NULL)
    GetStartDirName ();
  }


HINSTANCE MyInstance;
static DWORD lastFilterIndex = 0;
BOOL GetCmpName (HWND hWnd,int ResID,LPSTR Name,WORD cbName,BOOL mustExist,int Type)
  {
  char                szname[128];
  BOOL res;
  OPENFILENAME        ofn;
  char HeadLine[128];
  LoadString (MyInstance,ResID,HeadLine,sizeof(HeadLine));

  *szname = '\0' ;
  lmemset (&ofn,'\0',sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.hInstance = MyInstance;
  switch (Type) {
    case 0 :
      ofn.lpstrFilter = (LPSTR)"Text\0*.txt\0Structs\0*.gdd\0Views\0*.idd\0Tables\0*.ddd\0Modules\0*.mod\0Includes\0*.inc\0Mak\0*.mak\0Alle CPL-Dateien\0*.txt;*.gdd;*.idd;*.ddd;*.mod;*.inc;*.pty;*.mak\0Alle Dateien\0*.*\0\0";
      break ;
    case 1 :
      ofn.lpstrFilter = (LPSTR)"Batch\0*.bat\0Alle Dateien\0*.*\0\0";
      break ;
    case 2 :
      ofn.lpstrFilter = (LPSTR)"RI\0*.ri\0Alle Dateien\0*.*\0\0";
      break ;
    case 3 :
      ofn.lpstrFilter = (LPSTR)"Mak\0*.mak\0Text\0*.txt\0Alle Dateien\0*.*\0\0";
      break ;
    }
  ofn.lpstrCustomFilter = NULL;
  ofn.nMaxCustFilter = 0;
  if (Type == 0) {
    if (lastFilterIndex == 0) {
      char instr[256];
      instr[0] = '\0';
      GetPrivateProfileString ("Editor","FilterIndex","1",instr,sizeof(instr),IniFile());
      DWORD scanFilterIndex;
      if (sscanf (instr, "%ld", &scanFilterIndex) != 1)
        lastFilterIndex = 1;
      else
        lastFilterIndex = scanFilterIndex;
      }
    ofn.nFilterIndex = lastFilterIndex;
    }
  else
    ofn.nFilterIndex = 1;
  ofn.lpstrFile = (LPSTR)szname;
  ofn.nMaxFile = sizeof(szname);
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrTitle = HeadLine ;
  ofn.Flags = OFN_PATHMUSTEXIST;
  if (mustExist)
    ofn.Flags |= OFN_FILEMUSTEXIST;
  ofn.nFileOffset = 0;
  ofn.nFileExtension = 0;
  ofn.lpstrDefExt = (LPSTR)"txt";
  ofn.lCustData = 0L;
  ofn.lpfnHook = NULL;
  ofn.lpTemplateName = NULL;

  if (GetOpenFileName(&ofn)) {
    if ((Type == 0) && (lastFilterIndex != ofn.nFilterIndex)) {
      lastFilterIndex = ofn.nFilterIndex;
      char outStr[128];
      wsprintf (outStr, "%ld", lastFilterIndex);
      WritePrivateProfileString ("Editor","FilterIndex",outStr,IniFile());
      }
    lstrcpy (Name,szname);
    res = TRUE ;
    }
  else 
    // Hier (=Abbruch) bekommen wir leider auch keinen ofn.nFilterIndex zurueck, 
    // also brauchen wir auch nichts zu tun
    res = FALSE ;

  return res;
  }



//HWND hwndMDIClient, hWndStatusbar;
BOOL    bIdleOnly = FALSE;
int   nMenuID = NOMENU;
HMENU hMenu, hPopupMenu[10];

static VOID NEAR SetStatbarText(HWND hwnd, int nID,BOOL redrawflg)
  {
  static char szStatBarText[256];

  static int nLastID = -1;

  // Da die Ermittlung des Hilfetexts nur manchmal funktioniert (fuer alle MI_-Items)
  // und fuer Menues ein Kurzhilfetext ohnehin eher sinnlos erscheint
  // loeschen wir nur den Text in der Statusbar
  // if ( nID != nLastID ) {
  //   if ( LoadString(MyInstance, MENU_BASE+nID, szStatBarText, 255) == 0)
      lstrcpy(szStatBarText,"");  // waun i nix find daun schreib' i nix!
  //   }

  if(redrawflg)
    SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(szStatBarText)));
  }


void OnMenuSelect (HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, WORD flags)
  {
  /* Da die Ermittlung des Hilfetexts nur manchmal funktioniert (fuer alle MI_-Items)
     und fuer Menues ein Kurzhilfetext ohnehin eher sinnlos erscheint
     brauchen wir auch keine nMenuID mehr zu setzen.
  int tmpMenuID = 0;

  if (hmenu == NULL && flags == 0xffff) {
    // Exiting menu mode.  hMenu && hmenuPopup are NULL.
    nMenuID = NOMENU;
    SetStatbarText(hwnd, nMenuID,TRUE);
    return;
    }
  else if (flags & MF_SYSMENU) {          // System menu is up
    if (!(flags & MF_POPUP))              // System menu item is selected
      nMenuID = item-MENU_BASE;           // System menu: item contains SC_* code.
    else                                  // System menu and no item is selected
      nMenuID = IDM_SYSMENU;
    }
  else {
    if ((flags & MF_POPUP)) {
      // Pulling down a popup submenu: hmenuPopup contains popup handle.
      for (int i = 0; hPopupMenu[i] != NULL; i++)
        if (hmenuPopup == hPopupMenu[i]) {
          nMenuID = 100*(i+1);
          break;
          }
      
      if (hPopupMenu[i] == NULL)
        nMenuID = item;
      } 
    else
      nMenuID = item;
    }
  if (!bIdleOnly && tmpMenuID != nMenuID)
    SetStatbarText(hwnd, nMenuID, TRUE);
  */
  if (!bIdleOnly)
    SetStatbarText(hwnd, nMenuID, TRUE);
  }

void OnEnterIdle (HWND hwnd, WORD source, HWND hwndSource)
  {
  if (bIdleOnly)
    SetStatbarText(hwnd, nMenuID, TRUE);
  }


//------------------------  InitializeMenu  ---------------------------------
//
//---------------------------------------------------------------------------
extern BOOL IsWatchOpen();
void InitializeMenu (HMENU hMenu)
  {
#ifdef WIN32
  HWND hWnd = HWND(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L));
#else
  HWND hWnd = HWND(LOWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
  HWND hScWnd = GetScWnd();
  UINT bMDIStatus = (IsWindow(hWnd)) ? MF_ENABLED : MF_GRAYED;
  UINT bFileStatus = (IsWindow(hScWnd)) ? MF_ENABLED : MF_GRAYED;
  UINT bWatchStatus = (IsWatchOpen()) ? MF_ENABLED : MF_GRAYED;

  // wenn es ein MDI-Fenster gibt, dann MDI-Menu enablen
  EnableMenuItem (hMenu, IDM_WINDOWTILE, bMDIStatus);
  EnableMenuItem (hMenu, IDM_WINDOWCASCADE, bMDIStatus);
  EnableMenuItem (hMenu, IDM_WINDOWICONS, bMDIStatus);
  EnableMenuItem (hMenu, IDM_WINDOWCLOSEALL, bMDIStatus);
  
  // Datei-Operationen ebenfalls nur bei existierendem MDI-Child
  EnableMenuItem (hMenu, IDM_FILECLOSE, bFileStatus);
  EnableMenuItem (hMenu, MI_STOREED, bFileStatus);
  EnableMenuItem (hMenu, IDM_FILESAVEAS, bFileStatus);
  EnableMenuItem (hMenu, IDM_FILESAVEALL, bFileStatus);

  // Suchen - Menupunkte
  EnableMenuItem (hMenu, MI_SEARCH, bFileStatus);
  EnableMenuItem (hMenu, MI_REPLACE, bFileStatus);

  EnableMenuItem (hMenu, MI_TOGGLEBOOKMARK, bFileStatus);
  EnableMenuItem (hMenu, MI_NEXTBOOKMARK, bFileStatus);
  EnableMenuItem (hMenu, MI_PREVBOOKMARK, bFileStatus);

  EnableMenuItem (hMenu, MI_REPLACE, bFileStatus);

  EnableMenuItem (hMenu, MI_DIALED, bFileStatus);

  // Debugger
  EnableMenuItem (hMenu, MI_SETBREAK, bFileStatus);
  EnableMenuItem (hMenu, MI_WATCHVAR, bFileStatus);

  // Zwischenablage
  EnableMenuItem (hMenu, IDM_COPY, bFileStatus);
  EnableMenuItem (hMenu, IDM_CLEAR, bFileStatus);
  EnableMenuItem (hMenu, IDM_CUT, bFileStatus);
  
  EnableMenuItem (hMenu, MI_INSERTTEMPLATE, bFileStatus);

  EnableMenuItem (hMenu, MI_EXPANDWATCH,bWatchStatus);
  EnableMenuItem (hMenu, MI_DELWATCH   ,bWatchStatus);
  EnableMenuItem (hMenu, MI_WATCHBREAK ,bWatchStatus);
  EnableMenuItem (hMenu, MI_FOCUSTOLIST,bWatchStatus);


  UINT bPasteStatus = MF_GRAYED;
  if ((bMDIStatus == MF_ENABLED) || (bFileStatus == MF_ENABLED)) {
    if (OpenClipboard (hwndFrame)) {
      if (IsClipboardFormatAvailable(CF_TEXT) || 
          IsClipboardFormatAvailable(CF_OEMTEXT))
            bPasteStatus = MF_ENABLED;
  
      CloseClipboard();  
      }
    }
      
  EnableMenuItem (hMenu, IDM_PASTE, bPasteStatus);
  }
  

//----------------------------------------------------------------------------
// diese Callback-Funktion wird fuer jedes exisitierende MDI-Child aufgerufen
// ACHTUNG: alle Kindfenster werden aufgelistet; also auch Nicht-MDIs!!
//----------------------------------------------------------------------------
void ShowBreakList ();
void FocusToWatchList ();
DLLExport BOOL _export FAR PASCAL EnumMDIClientProc (HWND hWndChild, LPARAM lP)
  {
  SendMessage (hWndChild, WMU_FONTHASCHANGED, 0, 0);

  return 1;
  }

BOOL GenerateScript (HWND hWnd,LPSTR fName)
  {
  int res = DoCompile (hWnd,fName);
  return res == 0 ;
  }

extern HWND GetEditorWindow ();
extern BOOL RestoreFileEntry (LPSTR fname, int Zeile, int Spalte);

extern HWND hWndContext,hWndWatchList,hWatchToolbar;
BOOL ToggleWatchWnd ();
void ExpandWatch ();
void DelWatch ();
void BreakWatch ();
void ContextChanged (LONG lParam);
void WatchChanged (LONG lParam);
void DestroyDDS ();
void BreakDDS ();
DLLExport long FAR PASCAL _export BlandFrameWndProc (HWND hwnd,UINT message,WPARAM wP,LPARAM lP)
  {
  switch (message) {
    case WM_CREATE :
      {
      SourceFileNames.SetMenuWnd (hwnd ,0);  // zuletzt geoeffnete Dateien im Menu 0
      SourceFileNames.ReadEntrys ();

//--------------------------------------------------------
      CLIENTCREATESTRUCT ccs;
  
      // Find window menu where children will be listed 
  
      ccs.hWindowMenu = hMenuMainWindow;
      ccs.idFirstChild = IDM_WINDOWCHILD;
  
      // Create the MDI client 
      hwndMDIClient = CreateWindow("mdiclient", NULL, WS_CHILD |
                                     WS_CLIPCHILDREN | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, 
                                     0, 0, 0, 0, hwnd, 0, MyInstance,
                                     (LPSTR)&ccs);
      ShowWindow(hwndMDIClient, SW_SHOW);
//--------------------------------------------------------


      hMenu = GetMenu(hwnd);
      for (int i = 0; i < 10; i++)
        hPopupMenu[i] = GetSubMenu(hMenu, i);
      
      SetStatbarText(hwnd, nMenuID, FALSE);
      }
      break ;

    case WM_SIZE :
      {
      RECT rc, rcStat;
      int cxClient = LOWORD(lP);
      int cyClient = HIWORD(lP);
      int cyDock = 0;
      int cyStatus = 0;

      // ich sag' Dir wie gross ich bin; Du sagst mir wie gross Du bist!
      if (IsWindow(hWndDock)) {
        SendMessage (hWndDock, WM_SIZE, wP, lP);
        GetWindowRect (hWndDock, &rc);
        cyDock = rc.bottom - rc.top;
        }

      if (IsWindow(hWndStatusbar)) {
        SendMessage (hWndStatusbar, WM_SIZE, wP, lP);
        GetWindowRect (hWndStatusbar, &rcStat);
        cyStatus = rcStat.bottom-rcStat.top;
        }

      int cy = cyClient - cyDock - cyStatus;
      MoveWindow (hwndMDIClient, 0, cyDock, cxClient, cy, TRUE);
      
      if (IsWindow(hWndToolbar)) {
        SetRectEmpty (&rc);
        SendMessage (hWndToolbar, TB_GETITEMRECT, ID_SEARCHCOMBO, LPARAM(LPRECT(&rc)));
        MoveWindow (hWndCombo, rc.left, rc.top-1, rc.right-rc.left, rc.top+120, FALSE);
        }

      if (IsWindow(hWatchToolbar)) {
        SetRectEmpty (&rc);
        SendMessage (hWatchToolbar, TB_GETITEMRECT, ID_CONTEXTCOMBO, LPARAM(LPRECT(&rc)));
        MoveWindow (hWndContext, rc.left, rc.top-1, rc.right-rc.left, rc.top+120, FALSE);
        SetRectEmpty (&rc);
        SendMessage (hWatchToolbar, TB_GETITEMRECT, ID_WATCHLIST, LPARAM(LPRECT(&rc)));
        MoveWindow (hWndWatchList, rc.left, rc.top-1, rc.right-rc.left, rc.bottom - rc.top, FALSE);
        }
      }
      break;
      
/*
    // ACHTUNG:  diese Code-Sequenz ist auch fuer WM_SIZE relevant!!!!
    case WM_MOVE :
      {
      RECT rc;
      
      if (IsWindow(hWndToolbar) && (IsWindow(hWndProjectList))) {
        SendMessage (hWndToolbar, TB_GETITEMRECT, IDB_PROJECTFILES, LPARAM(LPRECT(&rc)));
        POINT pt;
        pt.x = rc.left;
        pt.y = 30;
        ClientToScreen (GetParent(hWndProjectList), &pt), 
        MoveWindow (hWndProjectList, pt.x, pt.y, 150, 150, TRUE);
        }
      }
      break;
*/
    case WM_INITMENU :
      InitializeMenu (HMENU(wP));
      break;

    case WM_MENUSELECT :
#ifdef WIN32
       OnMenuSelect (hwnd, (HMENU)lP, (HIWORD(wP) & MF_POPUP) ? 0 : LOWORD(wP), 
                                      (HIWORD(wP) & MF_POPUP) ? HMENU(lP) : 0, 
                                      HIWORD(wP));
#else
       OnMenuSelect (hwnd, (HMENU)HIWORD(lP), LOWORD(lP & MF_POPUP) ? 0 : wP, 
                                                     LOWORD(lP & MF_POPUP) ? HMENU(wP) : 0, 
                                                     LOWORD(lP));
#endif
       break;
    case WM_ENTERIDLE :
#ifdef WIN32
      OnEnterIdle (hwnd, wP, HWND(lP));
#else
      OnEnterIdle (hwnd, wP, HWND(LOWORD(lP)));
#endif
      break;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDM_FILENEW:
          {
          // Make an empty MDI child window 
          HWND hWndChild = MakeNewChild (NULL);
          ShowScript (hWndChild, NULL, FALSE);
          }
          break;
     
        case IDM_FILEEXIT:
           // Close application 
           SendMessage(hwnd, WM_CLOSE, 0, 0L);
           break;
     
        case IDM_WINDOWTILE:
           // Tile MDI windows 
           SendMessage(hwndMDIClient, WM_MDITILE, 0, 0L);
           break;
     
        case IDM_WINDOWCASCADE:
           // Cascade MDI windows 
           SendMessage(hwndMDIClient, WM_MDICASCADE, 0, 0L);
           break;
     
        case IDM_WINDOWICONS:
           // Auto - arrange MDI icons 
           SendMessage(hwndMDIClient, WM_MDIICONARRANGE, 0, 0L);
           break;
     
        case IDM_WINDOWCLOSEALL:
           CloseAllChildren(FALSE);
           break;

        case IDB_PROJECTFILES:        
          if (IsWindow(hWndToolbar) && (IsWindow(hWndProjectList))) {
            RECT  rc;
            POINT pt;
            SendMessage (hWndToolbar, TB_GETITEMRECT, IDB_PROJECTFILES, LPARAM(LPRECT(&rc)));
            pt.x = rc.left;
            pt.y = rc.bottom;
            ClientToScreen (GetParent(hWndProjectList), &pt), 
            SetWindowPos (hWndProjectList, HWND_TOP, pt.x, pt.y, 150, 150, SWP_SHOWWINDOW);
            }
          break;

        case IDB_OPENPROJECT:
          OpenProjects (hwnd);
          break;
          
        case MI_TABLELIST :
          {
          HWND hScWnd = GetEditorWindow ();
          if (IsWindow(hScWnd)) {
            char szActiveWord[128];
            SendMessage (hScWnd, WMU_GETACTIVEWORD, 0, LPARAM(LPSTR(szActiveWord)));
//            FileBlock FAR *fbl = (FileBlock FAR *) (GetWindowLong (hwnd,GWL_TEXTBLOCK));
            OpenDBList (szActiveWord);
            }
          else  
            OpenDBList (NULL);
          }
          break ;
        case MI_CLEARSCREEN :
          FreeMsgs ();
          InvalidateRect (hwndMDIClient,NULL,TRUE);
          break ;
        case MI_OUTPUTOPT :
          ToggleOutputState (GetMenu(hwnd));
          break ;
        case MI_GENRES :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_GENRC,FName,sizeof(FName))) {
            HWND hWndChild = MakeNewChild (FName);
            GenRScript (hWndChild,FName);
            SendMessage (hwndMDIClient, WM_MDIDESTROY, WPARAM(HWND(hWndChild)), 0);
            }
          }
          break ;
        case MI_SHOWRES :
          ShowResources (hwnd);
          break ;
        case MI_SHOWFMT:
          ShowFormat (hwnd);
          break;
        case MI_SHOWCOLOR:
          {
          COLORREF Color = ShowColor (hwnd);
          break;
          }
        case MI_SETFNC :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_FNCPROT,FName,sizeof(FName))) 
            GenFncProt (hwndMDIClient,FName);
          }
          break ;

        case MI_SCRIPTLIST :
          WorkOnScripts (hwnd);
          break ;

        case MI_GENERATESCRIPT :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_GENINT,FName,sizeof(FName),FALSE,3)) {
            FreeMsgs ();
            CHAR wndName[128];
            lstrcpy (wndName, "Make ");
            lstrcat (wndName, GetFName (FName));
            HWND hWndChild = MakeNewChild (wndName);
            InitModuleHash ();
            GenerateFull (hWndChild, FName); 
            DoneModuleHash ();
            }
          }
          break;

        case MI_GENINT :
          {
          HWND hScWnd = GetEditorWindow ();
          if (IsWindow(hScWnd)) {
            char szActiveWord[128],szActivePrefix[128];
            SendMessage (hScWnd, WMU_GETACTIVEWORD, 0, LPARAM(LPSTR(szActiveWord)));
            SendMessage (hScWnd, WMU_GETACTIVEPREFIX, 0, LPARAM(LPSTR(szActivePrefix)));
            OpenIntList (szActivePrefix,szActiveWord);
            }
          else  
            OpenIntList (NULL,NULL);
          }  
          break ;

        case MI_SHOWGLOB :
          {
          HWND hScWnd = GetEditorWindow ();
          if (IsWindow(hScWnd)) {
            char szActiveWord[128],szActivePrefix[128];
            SendMessage (hScWnd, WMU_GETACTIVEWORD, 0, LPARAM(LPSTR(szActiveWord)));
            SendMessage (hScWnd, WMU_GETACTIVEPREFIX, 0, LPARAM(LPSTR(szActivePrefix)));
            OpenGlobList (szActivePrefix,szActiveWord);
            }
          else  
            OpenGlobList (NULL,NULL);
          }
          break ;

        case MI_RIDIAGS :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_CREATERI,FName,sizeof(FName),FALSE,2)) {
            CreateRIView (FName);
            }
          }
          break ;
        case MI_CONNECTTOSQL :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_CONNECTTOSQL,FName,sizeof(FName),FALSE,1)) {
            ConnectToSQL (hwndMDIClient,FName);
            SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Connection aufgenommen")));
            MessageBeep(0);
            }
          }
          break ;
        case MI_OPENFORSCRIPTED :
          {
          char FName[128];
          if (GetCmpName (hwndMDIClient,IDHEADLINE_SHOWSCRIP,FName,sizeof(FName))) {
            ShowScript (NULL, FName, TRUE);
            }
          }
          break;

        // Einstellungen fuer den Font im Editor
        case IDM_EDITORFONT :
          {
          LOGFONT lfEdit;
          GetObject (hFontEdit, sizeof(lfEdit), &lfEdit);

          CHOOSEFONT cf;
          cf.lStructSize = sizeof(CHOOSEFONT);
          cf.hwndOwner = hwnd;
          cf.lpLogFont = &lfEdit;
          cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | 
                     CF_FIXEDPITCHONLY ;
          
          ChooseFont (&cf);
          if (hFontEdit)
            DeleteObject (hFontEdit);
          lmemcpy (&lfEdit, cf.lpLogFont, sizeof(lfEdit));
          hFontEdit = CreateFontIndirect(&lfEdit);
          WIN_ASSERT (hFontEdit != 0);

          WriteEditorFont (hFontEdit);   // in INI-Datei schreiben

          WNDENUMPROC wndEnumProc = MakeProcInstance ((WNDENUMPROC)EnumMDIClientProc, MyInstance);
          EnumChildWindows (hwnd, wndEnumProc, NULL);
          FreeProcInstance (wndEnumProc);
          }  
          break;
          
        case ID_SEARCHCOMBO:
          SearchCombo.OnCommand (wP, lP);
          break;  

        // Accelerator- bzw. Menukommando zum Aufrufen der zuletzt
        // bearbeiteten Dateien.
        case MI_WFILECOMMAND :
        case MI_WFILECOMMAND+1 :
        case MI_WFILECOMMAND+2 :
        case MI_WFILECOMMAND+3 :
        case MI_WFILECOMMAND+4 :
        case MI_WFILECOMMAND+5 :
        case MI_WFILECOMMAND+6 :
        case MI_WFILECOMMAND+7 :
        case MI_WFILECOMMAND+8 :
        case MI_WFILECOMMAND+9 :
          {
          char str [256];
          int zeile, spalte;
          LPSTR t = SourceFileNames.CheckCommand (CRACKER_wID, TRUE, str, &zeile, &spalte);
          if (t != NULL) {
            if (!RestoreFileEntry (t, zeile, spalte))
              SourceFileNames.InsertEntry (t, TRUE, FALSE, FALSE, 
                                           zeile, spalte);
            }
          SourceFileNames.WriteEntrys ();
          }
          break;

        case MI_RUN :
          RunDDS();
          break ;
        case IDM_CUT:
        case IDM_COPY :
        case IDM_PASTE:
        case IDM_DELLINE:
        case CMD_TB_BASE+100:
        case IDM_HELPONITEM:
        case MI_CLOSESC :
        case MI_STOREED :
        case MI_GENED :
        case MI_GENED_DEPEND :
        case MI_GENMAKEFILE :
        case MI_SETBREAK :
        case MI_STEP :
        case MI_STEPINTO :
        case MI_WATCHVAR :
        case MI_SHOWSTACK :
        case MI_SHOWUPDATE :
        case MI_CREATEWATCH :
        case MI_DIALED :
        case MI_STOREDIALOG :
        case MI_DESTROYDIALOG :
        case MI_DUPLICATE :
        case MI_WORKONELE :
        case MI_MOVEELEMES :
        case MI_WORKONSCREEN :
        case MI_DELELE :
        case MI_INSETDLGBSP :
        case MI_SEARCH :
        case MI_REPLACE :
        case MI_SEARCHCASE:
        case MI_SEARCHWORD:
        case MI_SEARCHMORE :
        case MI_REPLACEMORE :
        case MI_SEARCHUP :
        case MI_NEWHLINE :
        case MI_NEWVLINE :
        case MI_DELHLINE :
        case MI_MULTIHLINE  :
        case MI_WORKONHLINE :
        case MI_SHOWSORT :
        case MI_INDENVORDERGRUND :
        case MI_INDENHINTERGRUND :
        case MI_INSERTTEMPLATE :
        case MI_PREVIEWFORM :
        case MI_SHOWRASTER :            // Anzeigen eines definierten Rasters
        case MI_SETRASTER :             // Dialog fuer Raster-Einstellungen
        case MI_TOGGLEBOOKMARK :
        case MI_NEXTBOOKMARK :          // naechstes mit Ctrl-F2 definiertes Lesezeichen
        case MI_PREVBOOKMARK :          // vorheriges .................................
        case IDM_FILESAVEAS :
        case IDM_FILECLOSE :
        case MI_FINDMATCHINGBRACES :
        case 110 :
        case 111 :
          {
          HWND hScWnd = GetScWnd();
          if (IsWindow(hScWnd))
            SendMessage (hScWnd, message, wP, lP);
          }
          
          break;
        case MI_BREAKLIST :
          ShowBreakList ();
          break ;
        case MI_SHOWWATCHVAR :
          ToggleWatchWnd();
          break ;
        case MI_EXPANDWATCH    :
          ExpandWatch ();
          break ;
        case MI_DELWATCH       :
          DelWatch ();
          break ;
        case MI_WATCHBREAK     :
          BreakWatch ();
          break ;
        case ID_CONTEXTCOMBO :
          ContextChanged (lP);
          break ;
        case ID_WATCHLIST :
          WatchChanged (CRACKER_wNotify);
          break ;
        case MI_FOCUSTOLIST :
          FocusToWatchList ();
          break ;
        case MI_DESTROYDDS :
          DestroyDDS ();
          break ;
        case MI_BREAKDDS :
          BreakDDS ();
          break ;

        case MI_CALLVISUALC :
          DebugBreak ();
          break;

        default :
          return DefFrameProc(hwnd, hwndMDIClient, WM_COMMAND, wP, lP);

        }
        return 0;
      }
      break ;

    case WM_CLOSE :
      if (CloseAllChildren(TRUE))
        DestroyWindow (hwnd);
      break ;

    case WM_DESTROY:

#ifdef PIPE_ENABLED
      CloseClientPipe (hClientPipe);
#endif

      DestroyTables ();
      SourceFileNames.WriteEntrys ();
      SourceFileNames.DelEntrys ();
      PostQuitMessage (0) ;
      break;

    case WMC_ACTIVATE :
      ActivateRestool (hwnd,wP,lP);
      break ;

    case WMC_GETMODULELINE :
      {
      CallStackInfo FAR *csi = (CallStackInfo FAR *) RGetPointer (lP);
      LONG res = SearchModuleLine (hwnd,csi,csi->ProgName);
      RSetData (csi,sizeof(*csi));
      return res;
      }
      break ;

    case WMC_INQUIREBPLIST :
      SetBreakList ();
      break ;

    default:
      return DefFrameProc(hwnd, hwndMDIClient, message, wP, lP);
    }

  // use DefFrameProc() instead of DefWindowProc(), since there
  // are things that have to be handled differently because of MDI
  return 0;
  }




/*--------------------BlandMDIChildWndProc  ----------------------*/
/*
 *
 *  FUNCTION: BlandMDIChildWndProc ( hwnd, msg, wParam, lParam )
 *
 *  NOTE: If cases are added for WM_CHILDACTIVATE, WM_GETMINMAXINFO,
 *        WM_MENUCHAR, WM_MOVE, WM_NEXTMENU, WM_SETFOCUS, WM_SIZE,
 *        or WM_SYSCOMMAND, these messages should be passed on
 *        to DefMDIChildProc even if we handle them. See the SDK
 *        Reference entry for DefMDIChildProc
 *
 */
extern BOOL OnCloseChild (HWND hmdiWnd);
extern void SaveFileEntry (HWND hmdiWnd, BOOL toWorkSpace);
extern void SaveAllWorkSpaceEntrys (HWND closingWindow) ;
extern void RestoreAllWorkSpaceEntrys ();

DLLExport LONG FAR PASCAL _export BlandMDIChildWndProc (HWND hwnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  HWND hWndChild = GetWindow (hwnd, GW_CHILD);
  
  switch (msg) {
    case WM_SETFOCUS:
      if (IsWindow(hWndChild))
        SetFocus (hWndChild);
      break;
      
    case WM_MDIACTIVATE :
#ifdef WIN32
      if (IsWindow(HWND(lP))) {   // child being activated
#else
      if (wP) {                   // activation flag
#endif
        if (IsWindow(hWndChild))
          SetFocus (hWndChild);
        }
      return 0;

    case WM_PARENTNOTIFY:
      {
      UINT fwEvent;
      HWND hWndChild;

#ifdef WIN32
      fwEvent = LOWORD(wP);
      hWndChild = (HWND)lP;
#else
      fwEvent = wP;
      hWndChild = LOWORD(lP);
#endif

      if ((fwEvent == WM_CREATE) && (IsWindow(hWndChild))) {
        SetFocus (hWndChild);
        return 0;
        }
      }
      break;
      
    case WM_CHILDACTIVATE:
      if (IsWindow(hWndChild)) {
        SetFocus (hWndChild);
        }

      break;  

    case WM_PAINT :
      {
      PAINTSTRUCT ps ;
      HDC hdc = BeginPaint (hwnd, &ps) ;
      if (!IsWindow (hWndChild))
        PaintMessages (hdc);
      EndPaint (hwnd, &ps) ;
      }
      return 0L;

    case WM_CLOSE :
      if (IsWindow (hWndChild)) {
        if (OnCloseChild (hwnd))
          SaveAllWorkSpaceEntrys (hwnd);
        else
          return 0L;
        }
      break;

    case WM_SIZE:
      {
      if (IsWindow(hWndChild))
        MoveWindow (hWndChild, 0, 0, LOWORD(lP), HIWORD(lP), TRUE);
      break;
      // ACHTUNG WM_SIZE muss weitergeleitet werden!!!!!
      }  
    }
  
  return DefMDIChildProc(hwnd, msg, wP, lP);
  }


/*-------------------  CloseAllChildren  -----------------------------*/
/*
 *
 *  FUNCTION   : CloseAllChildren ()
 *
 *  PURPOSE    : Destroys all MDI child windows.
 *
 */
extern BOOL IsEditorWindow (HWND hWnd);
BOOL CloseAllChildren (BOOL closeProgram)
  {
  HWND hwndT;

  // 1.) Pruefen, ob alle Fenster geschlossen werden duerfen
  // As long as the MDI client has a child ==> pruefen
  hwndT = GetWindow(hwndMDIClient, GW_CHILD);
  while (hwndT) {
    if (!GetWindow(hwndT, GW_OWNER)) { // No icon title windows 
      if (IsEditorWindow (hwndT)) {
        if (!OnCloseChild (hwndT)) 
          return FALSE ;
        }
      }
    hwndT = GetWindow (hwndT, GW_HWNDNEXT);
    }
  WorkSpaceNames.DelEntrys();
  // 2.) Pruefung OK ==> Alle Fenster schliessen
  // As long as the MDI client has a child, destroy it 
  while (hwndT = GetWindow(hwndMDIClient, GW_CHILD)) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow (hwndT, GW_HWNDNEXT);
    if (hwndT) {
      if (IsEditorWindow (hwndT)) {
        SaveFileEntry (hwndT, closeProgram);
        }
      SendMessage (hwndMDIClient, WM_MDIDESTROY, (WORD)hwndT, 0L);
      }
    else
      break;
    }
  WorkSpaceNames.WriteEntrys();
  return TRUE ;
  }

//----------------------------------------------------------------------------
// Diese WNDPROC ist fuer das kleine Fenster zustaendig, in dem alle, fuer 
// dieses Script relevante Include-Dateien, aufgelistet werden.
// Waehlt man eine dieser Dateien aus, wird (falls noch nicht geoeffnet)
// ein neues Fenster mit diesem Include-File erzeugt. 
//----------------------------------------------------------------------------
DLLExport LONG FAR PASCAL _export ProjectListWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG res = 0;

#ifdef WIN32  
  HWND hWndList = (HWND)GetWindowLong (hWnd, GWW_LISTWINDOW);
#else
  HWND hWndList = GetWindowWord (hWnd, GWW_LISTWINDOW);
#endif

  switch (msg) {
    // Beim Erzeugen ist das Listenfenster unsichtbar!
    case WM_CREATE :
      {
      hWndList = CreateWindow ("LISTBOX", NULL, 
                                WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | 
                                LBS_NOTIFY | WS_VSCROLL, 
                                0, 0, 10, 10, hWnd, 
                                HMENU(IDB_PROJECTFILES), MyInstance, NULL);
#ifdef WIN32
      SetWindowLong (hWnd, GWW_LISTWINDOW, (LONG)hWndList);
#else
      SetWindowWord (hWnd, GWW_LISTWINDOW, hWndList);
#endif
      }                                 
      break;

    // das Listenfenster passt sich dem Elternfenster genau an.
    case WM_SIZE:
      MoveWindow (hWndList, 0, 0, LOWORD(lP), HIWORD(lP), TRUE);
      break;

    // wird ein anderes Fenster aktiv, versteckt man das Listenfenster!
    case WM_ACTIVATE :
      if (wP == WA_INACTIVE)
        ShowWindow (hWnd, SW_HIDE);
      else
        SendMessage (hWndList,LB_SETCURSEL,0,0L);
      break;  

    case WM_KEYDOWN :
      MessageBeep (0);
      break;
    
    // Beim Auswaehlen aus der Liste wird ein Kindfenster geoeffnet!
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      if (CRACKER_wID == IDB_PROJECTFILES) {
//        switch (HIWORD(lP)) {
        switch (CRACKER_wNotify) {
          case LBN_SELCHANGE: {
            int Index = (int)SendMessage (hWndList, LB_GETCURSEL, 0, 0);
            if (Index != LB_ERR) {
              char h[13];
              SendMessage (hWndList, LB_GETTEXT, Index, LPARAM(LPSTR(h)));

              char fname[128];
              char sname[64];
              GetIncludeFileName (h,fname,sname,"source");

              ShowWindow (hWnd, SW_HIDE);


              // sucht in allen offenen Fenstern nach dem Dateinamen in der Caption
              HWND hwndT;
              BOOL Found = FALSE;
              char szTitle[128];
           
              hwndT = GetWindow(hwndMDIClient, GW_CHILD);
              while (hwndT) {
                // Skip the icon title windows 
                while (hwndT && GetWindow(hwndT, GW_OWNER))
                  hwndT = GetWindow(hwndT, GW_HWNDNEXT);
             
                if (hwndT) {
                  GetWindowText (hwndT, szTitle, sizeof(szTitle));
                  if (!lstrcmp(szTitle, fname)) {
                    Found = TRUE;
                    break;
                    }
                  else
                    hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
                  }
                }  
            
              if (!Found)
                ShowScript (NULL, fname);
              else
                MessageBeep (0);  
              }
            break;
            }
          }
        }
      else
        res = DefWindowProc (hWnd, msg, wP, lP);
      break;
        
    default:
      res = DefWindowProc (hWnd, msg, wP, lP);
    }

  return res;
  }


HACCEL hAccelTable;
HACCEL hFrmAccelTable;
HACCEL hDeskAccelTable;
extern HWND hFrmWnd;

//HWND hMainWnd = NULL;   // Fensterhandle der Anwendung
extern BOOL CheckSrvAcc (MSG FAR *msg);
extern BOOL CheckFldListAccellerator (MSG FAR *msg);
BOOL CheckAccellarator (MSG FAR *msg)
  {
  if (CheckSrvAcc (msg))
    return TRUE ;
  if (CheckFldListAccellerator (msg))
    return TRUE ;
  HWND hScWnd = GetScWnd();
  if ((IsWindow(hScWnd)) && (TranslateAccelerator(hScWnd, hAccelTable, msg)))
    return TRUE ;
  if ((IsWindow(hFrmWnd)) && (TranslateAccelerator(hFrmWnd, hFrmAccelTable, msg)))
    return TRUE ;
  if ((IsWindow(hwndFrame)) && (TranslateAccelerator(hwndFrame, hDeskAccelTable, msg)))
    return TRUE ;
  return FALSE ;
  }


void InterpreteCommandLine (LPSTR CmdLine, LPSTR first, LPSTR second)
  {
  // DebugBreak ();
  int len = lstrlen(CmdLine);
  LPSTR p = CmdLine;
  int i = 0;
  for ( ; (i < len) && (*p) && (*p != ',') && (*p != ' ') ; i++, p++);
  
  int Pos = p - CmdLine;
  if ((Pos > 0) && ((CmdLine[0] != '/') || ((CmdLine[1] == 'p') && (CmdLine[2] == ':')))) {
    if ((CmdLine[0] == '/') && (CmdLine[1] == 'p') && (CmdLine[2] == ':'))
      lmemcpy (first, CmdLine + 3, Pos - 3);
    else
      lmemcpy (first, CmdLine, Pos);
    first[Pos] = '\0';
    }
  else {
    Pos = 0 ;
    p = CmdLine;
    }
    
  if (Pos < len) {
    if (*p == ',') p++ ;
    else {
      for ( ; (*p) && (*p != ':') ; p++) ;
      if (*p == ':') p++ ;
      }
    Pos = p - CmdLine;
    }
  if (Pos < len) {
    lmemcpy (second, p, len-Pos);
    second[len-Pos] = '\0';
    }
  }

extern void ReadFormatInfo (void);


#ifdef PIPE_ENABLED

void CloseClientPipe (HANDLE hPipe)
  {
  CloseHandle (hPipe);
  CloseHandle (hEventClientWrt);
  }

VOID ReadDebugPipe (HANDLE *hPipe)
  {
  }
#endif


#define ANALYSEKEYWORDS


#define ANZFIELDS 5

extern DLLExport void _export WINAPI WriteSizeStat ();
extern DLLExport void _export FAR PASCAL DBClean_Init ();
DLLExport BOOL _export FAR PASCAL GenerateStruct (LPSTR fName,LPSTR Buffer,LPSTR prefix);
DLLExport BOOL _export FAR PASCAL GenerateView (LPSTR fName,LPSTR Buffer,LPSTR prefix,BOOL useVersion,LPSTR FAR *TableNamesForUseVersion,WORD FAR *VersionsForUseVersion);
extern DLLExport void _export FAR PASCAL PaintSortCallBack (HWND hWnd,HDC hPaintDC);
extern BOOL IsWatchDialogMessage (LPMSG lpMsg);

#ifdef ANALYSEKEYWORDS
  extern void LoadKeyWords ();
#endif

extern void LoadSyntaxColors ();

extern DLLExport void _export WINAPI SetExePath (LPSTR dirname);
#pragma optimize("",off)
void DoSetExePath (HINSTANCE hInstance)
  {
  char szFileName[256];
  GetModuleFileName (hInstance, szFileName, sizeof(szFileName));
  int i = lstrlen(szFileName);
  for (; (i > 0) && (szFileName[i] != '\\') && (szFileName[i] != ':'); i--);
  if (i > 0)
    szFileName[i+1] = '\0';
  else
    *szFileName = '\0';
  SetExePath(szFileName);
  }
#pragma optimize("",on)


int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
  {
  // erst mal den EXE-Pfad bestimmen
  DoSetExePath(hInstance);
  SetIchBinDasRestool();

  MSG         msg ;

#ifdef WIN32
//  DebugBreak ();
#endif

#ifdef ANALYSEKEYWORDS
  LoadKeyWords ();
#endif


  MyInstance = hInstance;
  DBClean_Init ();

  CTOOL_SetClassNames ("DDSLISTCLASS1","DMWSToolBar1","WORDWIN1","BubbleWindow1","FOLDERWINDOW1");
  double r ;
  GetResolutionCF (&r);
  DMWAPI_SetClassNames ("WORDWIN1",WWPAINTCALLBACK(MakeProcInstance(FARPROC(PaintSortCallBack),MyInstance)),r);
  STATBAR_SetClassNames ("STATBAR1");

  if (!hPrevInstance)
    if (!InitializeApplication())
       return 0;

  char szGenerateFullParam[128] = "";
  if ((lpszCmdParam != NULL) && (*lpszCmdParam)) {
    char szIniPathParam[128] = "";
    InterpreteCommandLine (lpszCmdParam, szIniPathParam, szGenerateFullParam);
    if (szIniPathParam[0] != '\0')
      SetStartDirName (szIniPathParam);
    }

  // Create the frame and do other initialization
  if (!InitializeInstance(lpszCmdParam, nCmdShow))
    return 0;

#ifndef WIN32
  Ctl3dRegister (MyInstance);
  Ctl3dAutoSubclass (MyInstance);
#endif

#ifndef WIN32
  FRegisterControl (MyInstance);   // MUSCROLL-Element
#endif

  SetGenStruct (GENSTRUCT (MakeProcInstance (FARPROC(GenerateStruct),hInstance)));
  SetGenView (GENVIEW (MakeProcInstance (FARPROC(GenerateView),hInstance)));

  if (szGenerateFullParam[0] != '\0') {
    SetCommandLineFlag (TRUE);
    GetTableAdmin()->Initialize ();
    HWND hWndChild = MakeNewChild (szGenerateFullParam);
    
    InitModuleHash ();
    GenerateFull (hWndChild, szGenerateFullParam); 
    DoneModuleHash ();
    DestroyWindow (hwndFrame);
//    if (hMenuMain)
//      DestroyMenu (hMenuMain);
    if (hMenuDialog)
      DestroyMenu (hMenuDialog);
    if (hMenuWndInMDI)
      DestroyMenu (hMenuWndInMDI);
    }
  else {
    //---------------------------------------------------------
    // RESTOOL wird regulaer aufgerufen (kein "Generate Full")
    //---------------------------------------------------------
#ifdef PIPE_ENABLED
    OVERLAPPED OverLapWrt;
    DWORD      retCode;
    CHAR       fileName[128];
    DWORD      bytesWritten;
    DWORD      lastError;
    DWORD      threadID;

    lstrcpy (fileName, "\\\\.\\PIPE\\DDS");

    hClientPipe = CreateFile (fileName,              // Pipe name.
                              GENERIC_WRITE          // Generic access, read/write.
                            | GENERIC_READ,
                              FILE_SHARE_READ        // Share both read and write.
                            | FILE_SHARE_WRITE ,
                              NULL,                  // No security.
                              OPEN_EXISTING,         // Fail if not existing.
                              FILE_FLAG_OVERLAPPED,  // Use overlap.
                              NULL);                 // No template.

    if (hClientPipe == INVALID_HANDLE_VALUE) {
      retCode = GetLastError();

                                     // This error means pipe wasn't found.
      if ((retCode == ERROR_SEEK_ON_DEVICE) ||
          (retCode == ERROR_FILE_NOT_FOUND)) {
          MessageBox (GetActiveWindow(),
                      "DEBUG - PIPE nicht gefunden\r\rDDS.EXE mu� zuerst gestartet werden",
                      "RESTOOL", 
                      MB_OK);
        }
      }

    hEventClientWrt = CreateEvent (NULL, TRUE, FALSE, NULL);
    OverLapWrt.hEvent = hEventClientWrt;

    char szClient[10];
    lstrcpy (szClient, "RESTOOL");
    retCode = WriteFile (hClientPipe, szClient, sizeof(szClient), &bytesWritten, &OverLapWrt);

    if (!retCode) {
      lastError = GetLastError ();
      if (lastError == ERROR_IO_PENDING)
        WaitForSingleObject (hEventClientWrt, DWORD(-1));
      }

    CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)ReadDebugPipe,
                  (LPVOID)&hClientPipe, 0, &threadID);
#endif

    LoadSyntaxColors ();

    iMSGFind = RegisterWindowMessage(FINDMSGSTRING);  //Find & Replace

    hFontEdit = GetEditorFont ();

    GetTableAdmin()->Initialize ();
    GetStartDirName ();
    ReadFormatInfo ();
    LoadBreakList ();

    hAccelTable = LoadAccelerators (hInstance,"DlgAcc") ;
    hFrmAccelTable = LoadAccelerators (hInstance,"FrmAcc") ;
    hDeskAccelTable = LoadAccelerators (hInstance,"DeskAcc") ;
    
    // Workspace wiederherstellen
    RestoreAllWorkSpaceEntrys ();

    while (GetMessage (&msg, NULL, 0, 0)) {
      // Suchen und Ersetzen - Dialoge sind nichtmodal!!!
      if ((hDlgFind != NULL) && IsDialogMessage(hDlgFind, &msg))
          continue;

      if ((hDlgReplace != NULL) && IsDialogMessage(hDlgReplace, &msg))
          continue;

      if (IsWatchDialogMessage (&msg))
          continue ;


      if (!TranslateMDISysAccel(hwndMDIClient, &msg)) {
        if (!CheckAccellarator (&msg)) {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
          }
        }  
      }

    DestroyBreakList ();
    MyProfFlush ();

    if (hFontEdit)
      DeleteObject (hFontEdit);

    if (hMenuDialog)
      DestroyMenu (hMenuDialog);
    if (hMenuWndInMDI)
      DestroyMenu (hMenuWndInMDI);

    EcToolExit ();
    fntDeleteAllFormats ();
    FreeBitmapTools();
    }
  ToolBarCleanUp ();

#ifndef WIN32
  Ctl3dUnregister (MyInstance);
#endif

  UnloadScriptContent ();
  UnloadUpdateScriptContent ();

#ifdef SHAREMEM
  RDestroyCommunic ();
#endif

  WriteSizeStat ();
  FreeLinMem ();
  return msg.wParam ;
  }

