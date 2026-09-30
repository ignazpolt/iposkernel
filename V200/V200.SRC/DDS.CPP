/*
**  dds.cpp  06 Nov 1991   Autor : H.S.
**
**    
**  Kurzbeschreibung
**
**      Dies ist das Hauptprogramm fuer die Denatle Diagnostik Software
**
**  Geschrieben fuer Microsoft Windows / Zortech C++.
**
*/
// $Header:   P:/marille/clinicum/rev/dds.cpv   1.100   27 Jun 2000 18:41:18   Martin  $
// $Log:   P:/marille/clinicum/rev/dds.cpv  $
// 
//    Rev 1.100   27 Jun 2000 18:41:18   Martin
// Ltx()
// 
//    Rev 1.99   12 Apr 2000 22:05:20   Martin
// Produktversion in den ErrorContext
// 
//    Rev 1.98   06 Mar 2000 20:01:12   Martin
// SetupDDE nur wenn KEIN Parameter MEMFILE angegeben!
// 
//    Rev 1.97   08 Feb 2000 00:29:56   Hannes
// ddeuninitialize
// 
//    Rev 1.96   20 Aug 1999 03:37:50   Hannes
// Bei Minimierten DDSen keinen DDE Server
// 
//    Rev 1.95   18 Aug 1999 18:47:34   Martin
// %-Variablen-Aufloesung fuer ORBIS
// 
//    Rev 1.94   29 Jun 1999 19:15:36   Martin
// Startup Parameter caseinsensitiv
// _DEBUG
// 
//    Rev 1.93   27 Apr 1999 01:44:06   Hannes
// Diverse Speicherfresser
// 
//    Rev 1.92   09 Apr 1999 17:21:48   Hannes
// WaitMessage nicht mehr nach WM_QUIT
// 
//    Rev 1.91   31 Mar 1999 14:54:56   Gerhold
// htmlhelp
// 
//    Rev 1.90   24 Mar 1999 15:27:46   Wolfgang
// 1.) Nach CheckProfileMsg gleich raus, zur Vermeidung der Verdopplungen 
//     bei ScrollLock.
// 2.) DNormalCusor auch in CheckProfileMsg.
// 
//    Rev 1.89   05 Feb 1999 21:36:46   Martin
// verbessertes Errorhandling
// 
//    Rev 1.88   04 Feb 1999 20:23:16   Hannes
// Mainwindow Hindbar
// 
//    Rev 1.87   19 Jan 1999 19:25:34   Hannes
// Startparameter auch mit "="
// 
//    Rev 1.86   24 Nov 1998 16:20:52   Hannes
// Anfuehrungszeicheninterpretierung bei Startparameter
// 
//    Rev 1.85   07 Nov 1998 17:55:42   Gerhold
// In der Funktion wurde bei MInterprete bei Mi_Cut statt auf CRACKER_wID
// der WPARAM wP ueberprueft (deshalb ging Accel STRG + X) nicht.
// 
//    Rev 1.84   05 Oct 1998 11:53:30   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.83   11 Aug 1998 08:42:24   Hannes
// Startparameter
// 
//    Rev 1.82   30 Jul 1998 13:24:18   Gerhold
// OleInitialize, OleUninitialize
// 
//    Rev 1.81   30 Jul 1998 11:06:16   Gerhold
// WinHelp-Aufruf ein bisserl erweitert
// 
//    Rev 1.80   08 Jul 1998 11:00:46   Hannes
// 
//    Rev 1.79   02 Jul 1998 11:06:30   Hannes
// Handling Zeitversetztes Destroy
// 
//    Rev 1.78   13 Jun 1998 17:26:00   Martin
// ExePath
// 
//    Rev 1.77   16 May 1998 20:20:44   Martin
// Stackpointer statt Stacksegment an SetFromException uebergeben (32 Bit)
// 
//    Rev 1.76   10 Feb 1998 18:27:24   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.75   06 Feb 1998 07:59:52   Hannes
// StartParameter
// 
//    Rev 1.74   05 Dec 1997 17:44:48   Hannes
// diverse Verbesserungen
// 
//    Rev 1.73   19 Nov 1997 18:47:48   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.72   13 Nov 1997 12:39:58   Hannes
// CheckProfileMessage
// 
//    Rev 1.71   31 Oct 1997 12:51:08   Hannes
// Timestampfunktion
// 
//    Rev 1.70   29 Oct 1997 19:00:34   Hannes
// Textbausteine
// 
//    Rev 1.69   24 Oct 1997 08:37:18   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.68   08 Aug 1997 09:04:56   gerhold
// #define NOBITMAP muss raus!! (wegen LeadTools)
// 
//    Rev 1.67   08 Aug 1997 08:58:00   gerhold
// SPLASH-Screen eingebaut
// 
//    Rev 1.66   14 Jul 1997 12:18:30   Martin
// DivideByZero
// 
//    Rev 1.65   08 Jul 1997 11:59:00   Hannes
// 
//    Rev 1.64   20 May 1997 17:30:32   Martin
// 32-Bit-Exceptionhandling
// 
//    Rev 1.63   05 May 1997 11:37:40   Hannes
// Speicherfresser
// 
//    Rev 1.62   30 Apr 1997 11:58:20   Hannes
// 
//    Rev 1.61   30 Apr 1997 10:36:16   Hannes
// 
//    Rev 1.60   30 Apr 1997 09:28:50   Hannes
// 
//    Rev 1.59   08 Apr 1997 19:28:22   gerhold
// MInterprete .... CRACKER wegen WM_COMMAND !!!
// 
//    Rev 1.58   08 Apr 1997 17:39:36   gerhold
// WinHelp (... GetHelpFile() ...)
// 
//    Rev 1.57   19 Feb 1997 12:16:42   Hannes
// FuncHash eingebaut (Scriptfunktionen)
// 
//    Rev 1.56   04 Feb 1997 20:02:54   MARTIN
// FreeAllExternDlls
// 
//    Rev 1.55   17 Dec 1996 11:12:44   HANNES
// EndOfUpdate
// 
//    Rev 1.54   05 Dec 1996 19:08:48   HANNES
// 
//    Rev 1.53   26 Nov 1996 19:23:38   HANNES
// Dies ist ein Testkommentar
// 
//    Rev 1.52   26 Nov 1996 08:13:38   HANNES
// Automatischer Update
// 
//    Rev 1.51   08 Nov 1996 13:32:42   HANNES
// 
//    Rev 1.50   14 Oct 1996 15:29:50   MARTIN
// Sound: erste funktionierende Version
// 
//    Rev 1.49   24 Sep 1996 19:00:36   GERHOLD
// 32 Bit Message-Loop, Winhelp(GetHelpContextNr())
// 
//    Rev 1.48   19 Aug 1996 16:16:02   MARTIN
// Commandline vor Netzwerkadresse abfragen
// 
//    Rev 1.47   25 Jul 1996 19:48:20   GERHOLD
// Statbat_SetClassnames wieder rein fuer WIN32
// 
//    Rev 1.46   05 Jul 1996 08:02:46   GERHOLD
// Debug=yes ... INI-Eintrag fuer 32-Bit
// 
//    Rev 1.45   17 Jun 1996 17:07:22   HANNES
// Konvertierung eingebaut
// 
//    Rev 1.44   10 Jun 1996 10:06:46   GERHOLD
// pragma pack
// 
//    Rev 1.43   18 May 1996 20:11:36   HANNES
// Menuehandling der Bearbeitung
// 
//    Rev 1.42   22 Feb 1996 19:05:50   MARTIN
// Pascalstring -> cstring (nwaddress)
// 
//    Rev 1.41   16 Feb 1996 15:06:48   GERHOLD
// ein bisserl WIN32
// 
//    Rev 1.40   05 Feb 1996 19:29:04   MARTIN
// ErrorContext Netzwerkaddresse
// 
//    Rev 1.39   04 Feb 1996 15:49:00   HANNES
// 
//    Rev 1.38   02 Feb 1996 14:27:56   MARTIN
// CheckGlobalAllocs nur bei DEBUG
// 
//    Rev 1.37   02 Feb 1996 13:00:40   MARTIN
// Exception 1, 3 und 256 ignorieren
// 
//    Rev 1.36   02 Feb 1996 10:36:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.34   26 Jan 1996 14:57:48   HANNES
// 
//    Rev 1.33   02 Jan 1996 22:21:12   HANNES
// 
//    Rev 1.32   27 Aug 1995 16:29:36   HANNES
// 
//    Rev 1.31   27 Aug 1995 13:04:00   HANNES
// DMWAPI_Setclass
// 
//    Rev 1.30   24 Aug 1995 00:20:02   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.29   14 Aug 1995 08:26:34   HANNES
// SetupWithHashs
// 
//    Rev 1.28   11 Jul 1995 12:47:06   HANNES
// Expressionoptimierung
// 
//    Rev 1.27   10 Jun 1995 22:04:24   HANNES
// Kleine Optimierungen
// 
//    Rev 1.26   27 Apr 1995 15:38:00   HANNES
// 
//    Rev 1.25   31 Mar 1995 13:09:40   HANNES
//  
// 
//    Rev 1.24   24 Mar 1995 19:25:56   GERHOLD
// Startverzeichnis setzen
// 
//    Rev 1.23   23 Mar 1995 11:52:28   GERHOLD
// DDS uebernimmt ein jetzt einen CmdLine-Parameter (Startverzeichnis INI)
// 
//    Rev 1.22   22 Mar 1995 11:46:32   HANNES
// 
//    Rev 1.21   20 Mar 1995 11:55:02   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.20   09 Feb 1995 09:09:48   GERHOLD
// DDE Initialisierung ganz an den Anfang gestellt
// 
//    Rev 1.19   06 Feb 1995 16:52:30   HANNES
// 
//    Rev 1.18   24 Jan 1995 16:53:24   HANNES
// 
//    Rev 1.17   20 Jan 1995 15:54:48   HANNES
// Includefiles raus
// 
//    Rev 1.16   13 Jan 1995 16:55:52   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.15   09 Jan 1995 12:14:26   HANNES
// Debugger eingebaut
// 
//    Rev 1.14   15 Dec 1994 18:23:54   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.13   09 Dec 1994 20:44:50   GERHOLD
// CTL3D statt Subclass!
// 
//    Rev 1.12   28 Nov 1994 20:00:16   GERHOLD
// CheckMapHotKey in CheckMsg eingebaut.
// 
//    Rev 1.11   28 Nov 1994 17:06:44   GERHOLD
// 
//    Rev 1.10   20 Nov 1994 18:14:42   HANNES
// 
//    Rev 1.9   19 Nov 1994 19:18:52   GERHOLD
// DDE initialisieren und bei Programmende wieder entfernen
// 
//    Rev 1.8   31 Oct 1994 09:57:54   hannes
// OneShot - Funktionen nachgetragen
// 
//    Rev 1.7   25 Oct 1994 12:41:58   GERHOLD
// Nachrichtenschleife fuer Accelerator
// 
//    Rev 1.6   20 Oct 1994 17:43:14   GERHOLD
// MInterprete -> MI_Copy, MI_Cut, MI_Insert
// CheckMsg    -> TranslateAccelerator
// 
//    Rev 1.5   17 Oct 1994 10:41:50   HANNES
// ZoomMode - Umstellung
// 
//    Rev 1.4   11 Oct 1994 09:43:34   HANNES
// Einbau der Zoomrectfunktionen
// 
//    Rev 1.3   20 Sep 1994 11:32:54   HANNES
// CheckPmHotkey, NewDocInstance ... AnzRecs = 1
// 
//    Rev 1.2   24 Jun 1994 20:21:36   HANNES
// 
//    Rev 1.1   24 Jun 1994 19:47:22   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:10   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.65   11 May 1994 16:21:24   MARTIN
// ToBusy in FlushSyncList (indirekt damit auch in EmptyUpdateList)
// 
//    Rev 1.64   13 Apr 1994 20:51:22   MARTIN
// headers ...
// 
//    Rev 1.63   23 Feb 1994 18:06:26   HANNES
// Aufruf der Statistik - Schreibroutine
// 
//    Rev 1.62   09 Feb 1994 12:26:02   HANNES
// Abbrechen beim Startup abgefragt
// 
//    Rev 1.61   04 Feb 1994 16:52:50   MARTIN
// TWAIN Aufrufe geaendert
// 
//    Rev 1.60   26 Jan 1994 17:06:18   MARTIN
// Sound aufraeumen und QuitDone
// 
//    Rev 1.59   26 Jan 1994 11:45:06   HANNES
// DMWAPI_Shutdown nach vor verlegt, fifo.hpp richtig includiert
// 
//    Rev 1.58   25 Jan 1994 19:23:00   HANNES
// Verbessertes PeekMessage (keine WM_PAINTs..)
// 
//    Rev 1.57   25 Jan 1994 18:43:52   HANNES
// DMWAPI_Setup,DMWAPI_Shutdown
// 
//    Rev 1.56   12 Jan 1994 11:04:28   HANNES
// Unnoetige Includes eleminiert, alte Druckfunktionen raus, Klasse Text
// eleminiert
// 
//    Rev 1.55   08 Jan 1994 19:06:12   HANNES
// Aufruf von GenerateStartUp
// 
//    Rev 1.54   07 Jan 1994 19:21:18   HANNES
// Funktionsprototyp von CheckMsg
// 
//    Rev 1.53   04 Jan 1994 16:32:20   HANNES
// Interne Recallverwaltung raus
// 
//    Rev 1.52   09 Dec 1993 14:57:04   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.51   04 Nov 1993 11:24:48   MARTIN
// Sanduhr in compile.dll (globmem.cpp) ausgelagert
// 
//    Rev 1.50   21 Oct 1993 10:07:26   HANNES
// UseMultiUserbtrieve raus
// 
//    Rev 1.49   18 Oct 1993 19:55:08   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.48   13 Oct 1993 12:21:00   MARTIN
// convbase.hpp
// 
//    Rev 1.47   22 Sep 1993 09:19:02   HANNES
// Version nach St. Poelten
// 
//    Rev 1.46   05 Sep 1993 22:14:46   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.45   23 Aug 1993 19:03:48   MARTIN
// Image-Umstellung (alte Sachen ausgemistet)
// 
//    Rev 1.44   18 Aug 1993 10:24:56   HANNES
// Endgueltiger umbau auf Tools
// 
//    Rev 1.43   22 Jul 1993 20:52:40   HANNES
// Kommandosortierung, verbesserte Freigabe der Kommandos
// 
//    Rev 1.42   20 Jul 1993 12:34:10   HANNES
// Aufruf der Hotkeys fuer die Iconwindows
// 
//    Rev 1.41   15 Jul 1993 16:34:36   HANNES
// Drucker in die DMWPAI ausgelagert
// 
//    Rev 1.40   05 Jul 1993 14:47:04   HANNES
// Toolbar eingebaut
// 
//    Rev 1.39   21 Jun 1993 20:35:04   HANNES
// Kategorie eines neuen Patienten
// 
//    Rev 1.38   20 Jun 1993 17:37:14   HANNES
// IsInPatList
// 
//    Rev 1.37   18 Jun 1993 15:01:56   MARTIN
// GetWindowInst
// 
//    Rev 1.36   16 Jun 1993 17:37:04   MARTIN
// Fehlerkorrektur in RestoreCursor
// 
//    Rev 1.35   16 Jun 1993 16:50:10   MARTIN
// Sanduhr - Behandlung
// 
//    Rev 1.34   15 Jun 1993 12:26:34   HANNES
// Anzeigen des Dokumentenliste
// 
//    Rev 1.33   14 Jun 1993 18:06:38   HANNES
// Ueberpruefung des Fensterhandels
// 
//    Rev 1.32   07 Jun 1993 11:26:36   HANNES
// Aufruf der Fifo pruefungen von aussen
// 
//    Rev 1.31   02 Jun 1993 19:50:54   HANNES
// Recall Reingebaut
// 
//    Rev 1.30   28 May 1993 21:12:14   HANNES
// WM_SETCURSOR abgefangen
// 
//    Rev 1.29   10 May 1993 12:46:50   HANNES
// DGr.. Knopfhandling umgestellt
// 
//    Rev 1.28   19 Apr 1993 01:35:16   MARTIN
// #include "cutcont.hpp"
// 
//    Rev 1.27   18 Apr 1993 22:51:00   HANNES
// Aufruf des Exports
// 
//    Rev 1.26   05 Apr 1993 10:30:02   HANNES
// ??
// 
//    Rev 1.25   02 Apr 1993 18:40:16   HANNES
// Profiling aus
// 
//    Rev 1.24   02 Apr 1993 17:36:28   HANNES
// Strukturbereinigung, Beschleunigung, loginbox
// 
//    Rev 1.23   17 Mar 1993 17:23:20   HANNES
// 32 bit Umstellung der CallCommands
// 
//    Rev 1.22   11 Mar 1993 11:33:46   HANNES
// Printjob alte Version rausgehaut
// 
//    Rev 1.21   08 Mar 1993 14:09:46   HANNES
// Check bei mehrfachoffenem Layout
// 
//    Rev 1.20   26 Feb 1993 13:44:32   HANNES
// Checkdialogmessage fuer den editor
// 
//    Rev 1.19   22 Feb 1993 17:04:22   HANNES
// Login
// 
//    Rev 1.18   17 Feb 1993 13:59:04   MARTIN
// header file dos.h
// 
//    Rev 1.17   17 Feb 1993 13:54:28   HANNES
// header file frmobj.hpp
// 
//    Rev 1.16   14 Feb 1993 15:59:22   HANNES
// Einbau einer verallgemeinerten Konfigurationstabelle
// 
//    Rev 1.15   08 Feb 1993 10:38:34   HANNES
// Einbau des CallCommand Fifos
// 
//    Rev 1.14   05 Feb 1993 19:44:36   HANNES
// (fruehzeitiges) Initialisieren von WBase::hInstance
// 
//    Rev 1.13   05 Feb 1993 19:34:20   HANNES
// Einbau des Lockings -> Login, Logout;
// 
//    Rev 1.12   01 Feb 1993 12:01:58   HANNES
// Neue Klasse VTO
// 
//    Rev 1.11   29 Jan 1993 18:49:04   HANNES
// Einbau der 2 Knoepfchens in der Dokumentenliste
// 
//    Rev 1.10   18 Jan 1993 16:42:50   HANNES
// Aenderung des Handlings bei EM_UPDATE, EM_CLEAR
// 
//    Rev 1.9   13 Jan 1993 18:46:18   HANNES
// Aenderungen bezueglich Dokumente mit mehreren Datentypen
// 
//    Rev 1.8   17 Dec 1992 15:54:04   HANNES
// Sprungleisten fuer die neuen Knoepfe
// 
//    Rev 1.7   12 Dec 1992 00:06:52   NORBERT
// No change.
// 
//    Rev 1.6   11 Dec 1992 16:17:24   HANNES
// Image Cache Statistik aufrufen
// 
//    Rev 1.5   10 Dec 1992 11:49:36   HANNES
// Check der Anzahl offener Dokumente angehaengt (EnterPat),
// Message im Fehlerfall (zuviele Dokumente offen)
// Lesen des Profiles zur Ermittlung der maximal erlaubten offenen Dokumente
// 
//    Rev 1.4   10 Dec 1992 11:26:56   HANNES
// Korrektur in Enterpat, (Lfndr = ind)
// 
//    Rev 1.3   09 Dec 1992 08:48:08   HANNES
// Farbfunktion verbessert (WgList..)
// 
//    Rev 1.2   06 Dec 1992 16:04:50   HANNES
// Aufruf von Patlist mit dem global selektierten Patienten
// 
//    Rev 1.1   04 Dec 1992 19:35:06   HANNES
// Knopfhandling bei Patientenneueingabe und Patientenliste
// (Erweiterung in ButtonBar...)
// 
//    Rev 1.0   02 Dec 1992 15:24:00   HANNES
// Initial revision.
#define USE_TWAIN
#define NOTEXTMETRIC
#define NOSCALABLEFONT
//#define NOBITMAP
#define NOWH
#include  <windows.h>
#include  <mmsystem.h>

#ifndef WIN32
  #include <toolhelp.h>
  #include <ole2.h>
#endif

#include  <stdio.h>  
#include "dds32.h"

#include <htmlhelp.h>

#define DDS_MAIN
#ifndef WIN32
  #include "ctl3d.h"
#endif

#include "lisencr.hpp"
#include "globmem.h"
#include "dds.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
// #include "scripthd.hpp"
struct FAR ScriptContent_Entry;
typedef ScriptContent_Entry FAR *LPSCRIPTCONTENT;
DLLExport void _export WINAPI LoadScriptContent ();
DLLExport void _export WINAPI UnloadScriptContent ();
DLLExport void _export WINAPI ClearFuncHash();
#include "mdichild.hpp"

#include "dds.h"
#include "cfield.hpp"

#include "oneshot.hpp"
#include        "wmfcache.hpp"
#include        "mdiclien.hpp"
#include        "ddsmsg.h"

#ifndef WIN32
  #include        "statbar.hpp"
#endif

#define MODULENUM 12
#include        "winass.hpp"
#include        "schiebe.hpp"

#define NODLL

#include        "sound.hpp"
#include        "ddsdde.hpp"

#include "l_bitmap.h"
#include "cntmenu.hpp"

#include "communic.hpp"


#ifdef DEBUG
extern DLLExport void _export WINAPI InquireBreakPoints ();
extern DLLExport void RemoveAllBreakPoints ();
#endif
extern DLLExport void _export WINAPI COMPILE_Setup (HWND FrameWnd,EXTCHKMSG ech);
extern void DelKTypeList ();

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdln, int cmd);


/********** Interpreter fuer das Menue ********/
/*-------------< Dokumentenliste >---------------------*/
extern void DestroyMdiChildren(void);
extern void ShowAbout (HINSTANCE hInst);

// Lesen der maximal erlaubten Dokumente aus dem DMW - Ini File
/////////////////////////////////////////////////////////////////
extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
#define MYINI           GetIniName ()
#endif
static int MaxDocuments;
#define DOCSECTION              "Documents"
#define DOCCOUNT                "MaxDocCount"
#define DOCCOUNTDEF             5
int GetMaxDocCount () 
  {
  if (MaxDocuments <= 0)
    // Lesen aus dem INI - File
    MaxDocuments = GetPrivateProfileInt (DOCSECTION,DOCCOUNT,
                                         DOCCOUNTDEF,MYINI
                                        );
  return MaxDocuments ;
  }

static BOOL CheckSetCursor (MSG *msg)
  {
  return (msg->message == WM_SETCURSOR) && IsBusyCursor();
  }

BOOL MsgInQueue = FALSE;
static BOOL _isfromSyncList;
void LoadIsInProgress (mdiChild *c);
void LoadIsDone (mdiChild *c);
void deleteAllOpenChilds ();
void CheckAsyncFifo ()
  {
  LPCMDFIFO h ;
  if (h = AsyncFifoPtr->GetCommandFifo ()) {
    // Aufruf der Funktion
    /////////////////////////
    mdiChild *c = LPMDICHILD (h->DocumentID);
    LoadIsInProgress (c);
    c->CallCommand (h->Cmd,h->mode);
    LoadIsDone (c);
    deleteAllOpenChilds ();

    // Eine Aufforderung zum naechsten (asynchronen) Update senden
    MsgInQueue = FALSE ;
    if (!AsyncFifoPtr->IsCommandFifoEmpty()) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      MsgInQueue = TRUE ;
      }
    AsyncFifoPtr->FreeFifoEntry (h);
    }
  }

HACCEL hAccelTable;
static DWORD Magic = 0x0532FACD;
extern BOOL CheckToolHotKey (MSG *msg);
extern BOOL CheckMapHotKey (MSG *msg);   // MDICLIEN.CPP

extern BOOL ZoomRectActive;
inline BOOL CheckDialogMessage (MSG *msg)
  {
  return FALSE ;
  }

DLLExport BOOL _export WINAPI ProcessDCMessage(LPMSG);
DLLExport VOID _export WINAPI DCInitialize (HWND);
DLLExport VOID _export WINAPI DCExit (VOID);

BOOL DNormalCusor;
BOOL IsInExternCall;

void CheckProfileMsg (MSG *msg)
  {
  if ((!AsyncFifoPtr->IsCommandFifoEmpty()) ||
      (!AsyncFifoPtr->IsCommandFifoEmpty()) ||
      (IsInExternCall)) {
    ToBusyCursor();
    }
#ifdef DEBUG
  if (Magic != 0x0532FACD) {
    FatalAppExit (0,"Da is' was faul");
    }
#endif
  // Abarbeiten der synchronen command - Fifo
  if (msg->message == WMU_CALLCOMMAND)
    CheckAsyncFifo ();
  else {
    CheckControlAction (msg);
    if (!ProcessDCMessage (msg)) {
      if (ZoomRectActive) {
        /*--- keine Hotkeychecks ---*/
        if (msg->message == WM_KEYDOWN) {
          if (msg->wParam == VK_ESCAPE)
            PostMessage(GetCapture(),WMU_EXITZOOMMODE,0,0L);
          }
        else {   // keine Tasten an die Toolbar schicken
          TranslateMessage (msg) ;
          DispatchMessage (msg) ;
          }
        }
      else {
        if ((!IsWindowEnabled(WBase::hFrameWin)) || !TranslateAccelerator (WBase::hFrameWin, hAccelTable, msg)) {
          if (!TranslateAccelerator (msg->hwnd, hAccelTable, msg)) {
            if (!CheckMapHotKey (msg)) {
              if (!CheckSetCursor (msg)) {
                if (!CheckDialogMessage (msg)) {
                  if( /*--- Weiterleitung von MDI-(Tastatur-)Eingabekuerzel
                    an das entsprechende MDI-Fenster             ---*/
                    !TranslateMDISysAccel(WBase::hClient, msg)
                          && !CheckToolHotKey (msg))
                    {
                    /*--- "normale" Nachrichtenverarbeitung ---*/
                    TranslateMessage (msg) ;
                    DispatchMessage (msg) ;
                    }
                  }
                }
              }
            }  
          }
        }
      }
    }
  if (AsyncFifoPtr->IsCommandFifoEmpty() && (!DNormalCusor) && (!IsInExternCall)) {
    RestoreCursor();
    }
  }

BOOL DoProfile ()
  {
  return ((GetKeyState(VK_SCROLL) & 1) == 1);
  }

void CheckMsg (MSG *msg)
  {
#ifdef DEBUG
  if (DoProfile ()) {
    CheckProfileMsg (msg);
    return;
    }
#endif
  if ((!AsyncFifoPtr->IsCommandFifoEmpty()) ||
      (!AsyncFifoPtr->IsCommandFifoEmpty()) ||
      (IsInExternCall)) {
    ToBusyCursor();
    }
#ifdef DEBUG
  if (Magic != 0x0532FACD) {
    FatalAppExit (0,"Da is' was faul");
    }
#endif
  // Abarbeiten der synchronen command - Fifo
  if (msg->message == WMU_CALLCOMMAND)
    CheckAsyncFifo ();
  else {
    CheckControlAction (msg);
    if (!ProcessDCMessage (msg)) {
      if (ZoomRectActive) {
        /*--- keine Hotkeychecks ---*/
        if (msg->message == WM_KEYDOWN) {
          if (msg->wParam == VK_ESCAPE)
            PostMessage(GetCapture(),WMU_EXITZOOMMODE,0,0L);
          }
        else {   // keine Tasten an die Toolbar schicken
          TranslateMessage (msg) ;
          DispatchMessage (msg) ;
          }
        }
      else {
        if ((!IsWindowEnabled(WBase::hFrameWin)) || !TranslateAccelerator (WBase::hFrameWin, hAccelTable, msg)) {
          if (!TranslateAccelerator (msg->hwnd, hAccelTable, msg)) {
            if (!CheckMapHotKey (msg)) {
              if (!CheckSetCursor (msg)) {
                if (!CheckDialogMessage (msg)) {
                  if( /*--- Weiterleitung von MDI-(Tastatur-)Eingabekuerzel
                    an das entsprechende MDI-Fenster             ---*/
                    !TranslateMDISysAccel(WBase::hClient, msg)
                          && !CheckToolHotKey (msg))
                    {
                    /*--- "normale" Nachrichtenverarbeitung ---*/
                    TranslateMessage (msg) ;
                    DispatchMessage (msg) ;
                    }
                  }
                }
              }
            }  
          }
        }
      }
    }
  if ((AsyncFifoPtr->IsCommandFifoEmpty()) && (!DNormalCusor) && (!IsInExternCall)) {
    RestoreCursor();
    }
  }

BOOL QuitDone = FALSE;
DLLExport void _export WINAPI _ClearQueue (void)
  {
  MSG m;
  while (PeekMessage (&m, NULL, 0, 0, PM_NOREMOVE)) {
    if ((m.message != WM_PAINT) && (!QuitDone)) {
      PeekMessage (&m, NULL, 0, 0, PM_REMOVE);
      CheckMsg (&m);
      }
    else
      break ;
    }
  }

DLLExport void _export WINAPI _ExternCheck (MSG FAR *lpmsg)
  {
  MSG ml;
  ml = *lpmsg;
  CheckMsg (&ml);
  }

extern void DestroyControl ();
extern mdiChild *GetControl ();
BOOL DoWindowsExit;
char DosPrgToExit[128],DosPrgParam[128];

LONG FAR PASCAL MInterprete(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  CRACKER_VARS
  CRACK_MESSAGEsc

  switch (CRACKER_wID) {
    case MI_H_Help_DDS :
      {
#ifdef WINHELP
      BOOL bResult;
      int ContextNr = GetHelpContextNr();
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
      break;

    case MI_ABOUT:
      ShowAbout (WBase::hInstance);
      break ;

    case MI_QUIT:
      // Programm Beenden
      if (GetControl()->CallOnClose ()) {
        // Dem System noch ein bisschen Verschnaufpause 
        // Vergoennen
        QuitDone = TRUE ;
        SndSetMsgWnd(NULL);  // Sound aufraeumen
        MSG m;
        while(PeekMessage (&m, NULL, 0, 0, PM_REMOVE))
          CheckMsg (&m);
        DestroyControl ();
        DestroyWindow(hWnd);
        }
      if (DoWindowsExit) {

#ifndef WIN32
        if (*DosPrgToExit)
          ExitWindowsExec (DosPrgToExit,DosPrgParam);
        else
#endif

          ExitWindows (0,0);
        }
      break ;
    //---------------------------------------------------
    // Kopieren eines Texteintrages in die Zwischenablage
    case MI_Copy :
    case MI_Cut :
      {
      cField FAR * ActiveField = GetActiveField();
      if (ActiveField != NULL) {       // deklariert in CFIELD.HPP
        if (ActiveField->CopyToClipBoard (hWnd))
          if (CRACKER_wID == MI_Cut) {
            ActiveField->DeleteSelectedLines();
            // EnableMenuItem (GetMenu(hWnd), MI_Cut, MF_GRAYED); // Wozu das ganze
            }
        }
      }
      break;  
    //---------------------------------------------------
    // Einfuegen eines Textes aus der Zwischenablage
    case MI_Insert :
      {
      cField FAR * ActiveField = GetActiveField();
      if (ActiveField != NULL) {       // deklariert in CFIELD.HPP
        ActiveField->PasteFromClipBoard (hWnd);
        // EnableMenuItem (GetMenu(hWnd), MI_Cut, MF_ENABLED); // ???
        }
      }
      break;  
    default :
      return DefFrameProc(hWnd, WBase::hClient, WM_COMMAND, wP, lP);
    }
  return 0L;
  }

// Berechnen der Dokument - Instanz
BOOL IsFromSyncList ()
  {
  return _isfromSyncList;
  }

void FlushSyncList ()
  {
  }

//  So lange updaten, bis alle Listen leer sind..
/////////////////////////////////////////////////////
void EmptyUpdateList ()
  {
  LPCMDFIFO h;
  for ( ; ((h = AsyncFifoPtr->GetCommandFifo ()) != NULL) ; ) {
    mdiChild *c = LPMDICHILD (h->DocumentID);
    c->CallCommand (h->Cmd,h->mode);
    AsyncFifoPtr->FreeFifoEntry (h);
    }
  }

extern void cToolInit ();
extern void cToolExit ();
extern void FreeListProcs ();
extern void SetPrinterCallBack ();
extern void ReadFormatInfo (void);
extern void CreateControl (BOOL forUpdate);

extern DLLExport LPSTR _export WINAPI SetStartDir (LPSTR dirname, LPSTR IniName);

extern void InitFrmObjDll(void);
typedef VOID (WINAPI * WWPAINTCALLBACK) (HWND hWnd,HDC hDC);
DLLExport void _export WINAPI DMWAPI_SetClassNames (LPSTR WordWinClass,WWPAINTCALLBACK pcallback,double rfact);
DLLExport void _export WINAPI CTOOL_SetClassNames (LPSTR ListClassName,LPSTR ClassName,LPSTR WWName,LPSTR BubbleName,LPSTR FolderClass);
DLLExport void _export WINAPI STATBAR_SetClassNames (LPSTR ClassName);
DLLExport void _export WINAPI SetFrameWnd (HWND hWnd);
DLLExport void _export WINAPI ToolBarCleanUp ();
extern void PrepareWithHashs ();
extern void FreeWithHashs ();

DLLExport void _export WINAPI WriteSizeStat ();
extern DLLExport void _export WINAPI DBClean_Init();

extern BOOL _export FAR PASCAL InTransaction();
extern void _export FAR PASCAL ResetTransactionDLL();

// Exception - Handling
#ifndef WIN32
extern void _export FAR PASCAL SetFromException(WORD actSS, WORD actCS, WORD actIP, WORD actBP);

extern "C" {
void __export CALLBACK MyFaultHandler(void);

/*  MyCFaultHandler
 *      This routine is used to prove that C routines can be used to
 *      make fault handlers.  As can be seen here, the parameters are
 *      actually pointing into the stack frame.  Two important notes:
 *          1) This function MUST be declared as _cdecl so that the
 *              parameters are not popped off the stack!
 *          2) This function may change these values with the understanding
 *              that they are actually passed "by value" implying that
 *              any changes are for real.
 *      As defined in MyFaultHandler (TEST2.ASM), 0 nukes app, 1 restarts
 *      the instruction, 2 chains on.
 */

char szText[200];
WORD __export _cdecl MyCFaultHandler(WORD wES, WORD wDS, WORD wDI, WORD wSI, WORD wBP, WORD wSP, WORD wBX,
    WORD wDX, WORD wCX, WORD wOldAX, WORD wOldBP, WORD wRetIP, WORD wRetCS, WORD wRealAX,
    WORD wNumber, WORD wHandle, WORD wIP, WORD wCS, WORD wFlags)
  {
  static WORD wReentry = 0;

  /* See if we're already here.  If so, tell routine to chain on */
  if (wReentry)
      return 2;
  wReentry = 1;

  if ((wNumber != 1) && (wNumber != 3) && (wNumber != 256)) {
    WORD wSS;
    __asm {
      mov ax,ss;
      mov wSS,ax;
      }
    wsprintf(szText, "Exception #%d", wNumber);
    SetFromException(wSS,wCS,wIP,wBP);
    WIN_ASSERT_TEXT(FALSE,szText);
    }

  /* We're getting out now, so undo reentry flag */
  wReentry = 0;

  return 2;
  }
}
#else
extern DLLExport void _export WINAPI SetFromException(DWORD actSS, DWORD actCS, DWORD actIP, DWORD actBP);
char szText[200];
int My32BitCFaultHandler(LPEXCEPTION_POINTERS ep)
  {
  static WORD wReentry = 0;

  /* See if we're already here.  If so, tell routine to chain on */
  if (wReentry)
    return EXCEPTION_CONTINUE_SEARCH;
  wReentry = 1;

  int wNumber = ep->ExceptionRecord->ExceptionCode;
//  if ((wNumber != 1) && (wNumber != 3) && (wNumber != 256)) {
    wsprintf(szText, "Exception #%X", wNumber);
    SetFromException(ep->ContextRecord->Esp,ep->ContextRecord->SegCs,ep->ContextRecord->Eip,ep->ContextRecord->Ebp);
    WIN_ASSERT_TEXT(FALSE,szText);
//    }

  /* We're getting out now, so undo reentry flag */
  wReentry = 0;

  return EXCEPTION_CONTINUE_SEARCH;
  }
#endif

DLLExport void _export WINAPI GetResolutionCF (double FAR *ratio);
extern DLLExport void _export WINAPI SetOnWinAssertProc(FARPROC actOnWinAssert);
extern void _export WINAPI SetErrorContextStr (LPSTR txt);
DLLExport void _export WINAPI GetNWAddress (LPSTR,int);
static char MyErrorContext[64];
extern void GetProductVersion(LPSTR outstr);
static char MyVersionAndErrorContext[128];
DLLExport BOOL _export WINAPI OnWinAssertProc (void)
  {
  BOOL res = TRUE;
  // gegebenenfalls offene Transaktion abbrechen
  if (InTransaction()) {
    res = FALSE;
    AbortTransaction();
    ResetTransactionDLL();
    }
  return res;
  }

static BOOL mylstrcmp (LPSTR s1,LPSTR s2) 
  {
  for ( ; ((*s2) && (*s1) && (*s2 == *s1)) ; s1 ++ , s2 ++ ) ;
  return ((*s2 == '\0') || (*s1 == '\0')) ;
  }

static LPSTR FindNextWord (LPSTR s)
  {
  for ( ; *s != ' ' ; s ++ ) ;
  for ( ; *s == ' ' ; s ++ ) ;
  return s ;
  }


//===========================================================================
// Da hat der kleine Gerhold wieder eine rechte Freude mit seinen 
// Splash-Screens, die sofort beim Starten des CLINICWARES aufgerufen werden
//===========================================================================
DLLExport LONG _export FAR PASCAL SplashWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG RetVal = 0L;
  static BITMAPHANDLE LeadBitmap;

  switch (msg) {
    case WM_CREATE:
      {
      LPCREATESTRUCT lpcs = LPCREATESTRUCT(lP);

      if (L_LoadBitmap(LPSTR(lpcs->lpCreateParams),&LeadBitmap,0,ORDER_BGR) < SUCCESS)
        return -1;

      int w, h;
      w = LeadBitmap.Width;
      h = LeadBitmap.Height;

      SetTimer (hWnd, 444, 5000, NULL);

      int sx = GetSystemMetrics (SM_CXSCREEN);
      int sy = GetSystemMetrics (SM_CYSCREEN);
      SetWindowPos (hWnd, HWND_TOP, (sx - w) / 2, (sy -h) / 2, w, h,
                    SWP_SHOWWINDOW);
      }
      break;

    case WM_TIMER:
      {
      KillTimer (hWnd, wP);
      DestroyWindow (hWnd);
      }
      break;

    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      RECT r;
      HDC hDC = BeginPaint (hWnd, &ps);

      GetClientRect (hWnd, &r);

      HPALETTE hPal = L_CreatePaintPalette (hDC, &LeadBitmap);

      HPALETTE hOldPal = SelectPalette (hDC, hPal, FALSE);
      RealizePalette (hDC);

      SetRect(&r, 0, 0, LeadBitmap.Width, LeadBitmap.Height);
      int ret = L_PaintDC (hDC, &LeadBitmap, NULL, NULL, &r, NULL, SRCCOPY);


      SelectPalette (hDC, hOldPal, FALSE);

      EndPaint (hWnd, &ps);
      }
      break;

    case WM_DESTROY:
      break;

    default:
      RetVal = DefWindowProc (hWnd, msg, wP, lP);
      break;
    }


  return RetVal;
  }


BOOL RegisterSplashWindow (HINSTANCE hInst)
  {
  WNDCLASS WndClass;

  WndClass.style         = CS_VREDRAW | CS_HREDRAW ;
  WndClass.lpfnWndProc   = WNDPROC (SplashWndProc) ;
  WndClass.cbClsExtra    = 0 ;
  WndClass.cbWndExtra    = 0 ;
  WndClass.hInstance     = hInst ;
  WndClass.hIcon         = NULL;
  WndClass.hCursor       = LoadCursor (NULL, IDC_WAIT);
  WndClass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
  WndClass.lpszMenuName  = NULL;
  WndClass.lpszClassName = "SPLASHWINDOW" ;

  return RegisterClass (&WndClass);
  }


extern void InitExtraMem ();
extern void FreeExtraMem ();

/********** Windows Hauptprogramm ************/
#ifdef WIN32
extern BOOL FAR PASCAL FilterDLLMsgForExternDLL (LPMSG lpMsg);
extern void FAR PASCAL ProcessDLLIdleForExternDLL();
#endif

DLLExport void _export FAR PASCAL RemoveMDIHandleList ();
extern void FreeAllExternDlls(void);
extern void FreeAllArgs ();

extern void DelBackBrush ();
extern void FreeAllTrackCursors ();

#pragma optimize("",off)
static void DivideByZero()
  {
  int a = 1;
  int b = 0;
  int c = a / b;
  }
#pragma optimize("",on)

static int AnzPars;
static LPSTR Pars[15];
BOOL DoppelPunktAbarbeitung (LPSTR h)
  {
  BOOL mitDoppelPunkt = FALSE;
  if (*h == '/') {
    h ++ ;    // Parameter muessen mit '/' anfangen
    mitDoppelPunkt = TRUE;
    }
  for ( LPSTR x = h ; *x ; x ++) {
    if (((*x == ':') && (mitDoppelPunkt)) || (*x == '=')) {
      WIN_ASSERT (AnzPars < (sizeof(Pars) / sizeof(*Pars)));
      Pars[AnzPars++] = h ;
      return TRUE ;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct StartParameter_param {
  WORD parSize;
  DWORD res;
  DWORD kennung;
  };
#pragma pack()

LPSTR TesteKennung (LPSTR par,LPSTR kennung)
  {
  for ( ; ((*par) && (*kennung) && (CharUpper(LPSTR(*par)) == CharUpper(LPSTR(*kennung)))) ; par ++ , kennung ++ ) ;
  if ((*kennung == '\0') && ((*par == ':') || (*par == '='))) {
    int offs;
    if (par[1] == '"') offs = 2 ;
    else               offs = 1 ;
    for ( int i = offs ; par[i] ; i++)
      if (par[i] == '"') par[i] = '\0';
    return par + offs;
    }
  else
    return NULL ;
  }

LPSTR SucheParameter (LPSTR kennung)
  {
  if (kennung == NULL) return NULL;
  for (int i = 0 ; i < AnzPars ; i++) {
    LPSTR Next = TesteKennung (Pars[i],kennung);
    if (Next != NULL) {
      return Next;
      break ;
      }
    }
  return NULL;
  }

BOOL StartParameter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    StartParameter_param FAR *par = (StartParameter_param FAR *) param ;
    LPSTR kennung = LPSTR (c->ReadlData (par->kennung));
    LPSTR s = SucheParameter (kennung);
    if (s != NULL)
      c->WritelData (par->res,s,lstrlen(s) + 1,LPSTR(par)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(par)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    StartParameter_param FAR *par = (StartParameter_param FAR *) param ;
    c->ClearlConnection (par->kennung,LPSTR(par)-sizeof(WORD));
    }
  return FALSE ;
  }

LPSTR GetStartParam (LPSTR kennung)
  {
  for (int i = 0 ; i < AnzPars ; i++) {
    LPSTR Next = TesteKennung (Pars[i],kennung);
    if (Next != NULL) {
      return Next;
      break ;
      }
    }
  return NULL;
  }

// Callbackfunktionen fuer DBHelp:
#pragma pack(1)
struct SetErrorRef_param {
  WORD parSize;
  DWORD errorref;
  DWORD toignore[1];
  };
#pragma pack()

static struct error_cb_par {
  mdiChild *c;
  SetErrorRef_param *par;
  } * last_error_cb_par = NULL;

BOOL SetErrorRef (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetErrorRef_param *par = (SetErrorRef_param *) param ;
    WIN_ASSERT(last_error_cb_par == NULL);
    last_error_cb_par = (error_cb_par *)GetGlobMem(sizeof(struct error_cb_par));
    last_error_cb_par->c = c;
    last_error_cb_par->par = par;
    }
  // if (mode & (EM_CLEAR | EM_RESET)) {
  //  absichtlich keine Expressions moeglich !!!!
  //  }
  return FALSE ;
  }

DLLExport LPVOID _export WINAPI CB_GetLastErrorCBP(void)
  {
  error_cb_par *last = last_error_cb_par;
  last_error_cb_par = NULL;
  // FreeGlobMem muss der Aufrufer dieser Callback-Funktion machen
  return last;
  }

DLLExport void _export WINAPI CB_BeginErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd)
  {
  if (ErrorCBP != NULL) {
    error_cb_par *cbp = (error_cb_par *)ErrorCBP;
    int NumPars = ((cbp->par->parSize - sizeof(*cbp->par)) / sizeof(DWORD)) + 1;
    for (int i = 0; i < NumPars; i++) {
      LONG *ErrCode = (LONG *)cbp->c->ReadlData(cbp->par->toignore[i]);
      GetDLLAdmin()->GetDLLEntry(hd)->DBIgnoreError (*ErrCode,TRUE);
      }
    }
  }

DLLExport void _export WINAPI CB_EndErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd)
  {
  if (ErrorCBP != NULL) {
    error_cb_par *cbp = (error_cb_par *)ErrorCBP;
    int NumPars = ((cbp->par->parSize - sizeof(*cbp->par)) / sizeof(DWORD)) + 1;
    for (int i = 0; i < NumPars; i++) {
      LONG *ErrCode = (LONG *)cbp->c->ReadlData(cbp->par->toignore[i]);
      GetDLLAdmin()->GetDLLEntry(hd)->DBIgnoreError (*ErrCode,FALSE);
      }
    LONG LastError = GetDLLAdmin()->GetDLLEntry(hd)->DBGetLastError ();
    cbp->c->WritelData(cbp->par->errorref,&LastError,sizeof(LastError),LPSTR(cbp->par)-sizeof(WORD));
    }
  }

void DoInitDBHelp(void)
  {
  SetErrorHandlingProcs(CB_GetLastErrorCBP,CB_BeginErrorHandling,CB_EndErrorHandling);
  }

extern CALLCONTEXTFUNCTION GetCallContextFunction ();
DLLExport void _export WINAPI FreeLinMem () ;

// aus globmem.cpp (ddsmem.dll)
extern DLLExport void _export WINAPI SetExePath (LPSTR dirname);
extern DLLExport void _export WINAPI SetJustForDebug (void);
typedef char *(__stdcall *RESOLVEVARPROC)(const char*);
extern DLLExport void _export WINAPI SetOrbisCnfName (LPSTR CnfName,RESOLVEVARPROC r);
// aus extdll.cpp
extern FARPROC GetProcPtr(LPSTR DllName,LPSTR ProcName,BOOL WithWinAssert);

typedef BOOL (__stdcall *GETVARPROC)(const char*,char*,int);
char *GetOrbisVar(const char *varname)
  {
  static char Var[512];
  // static GETVARPROC ipc_getvar = (GETVARPROC)GetProcPtr("owpload.dll","_IPC_GETVAR@12",TRUE);
  static GETVARPROC ipc_getvar = (GETVARPROC)GetProcPtr("owpload.dll","IPC_GETVAR",TRUE);
  if ((*ipc_getvar)(varname,Var,sizeof(Var)))
    return Var;
  else
    return NULL;
  }

char * __stdcall ResolveOrbisVar(const char *str)
  {
  static char Res[512];
  char Work[512];
  if (str == NULL)
    *Res = '\0';
  else
    strcpy(Res,str);
  BOOL ProzentGefunden = TRUE;
  while (ProzentGefunden) {
    char *r = Res;
    *Work = '\0';
    char *w = Work;
    ProzentGefunden = FALSE;
    while (*r) {
      while (*r && (*r != '%'))
        *w++ = *r++;
      if (*r) {
        char Var[64];
        char *v = Var;
        char *h = r + 1;
        while (*h && (*h != '%'))
          *v++ = *h++;
        if (*h) {
          *v = '\0';
          char *Val = GetOrbisVar(Var);
          if (Val != NULL) {
            ProzentGefunden = TRUE;
            strcpy(w,Val);
            strcat(w,h + 1);
            r = Res + strlen(Res);
            }
          else {
            *w++ = *r++;
            while (*r && (*r != '%'))
              *w++ = *r++;
            }
          }
        else {
          *w++ = *r++;
          }
        }
      else
        *w = '\0';
      }
    strcpy(Res,Work);
    };
  return Res;
  }

void CheckOrbis (void)
  {
  char outstr[128];
  if (!SearchFSItem ("Kunde",outstr,sizeof(outstr)))
    lstrcpy(outstr,"Clinicum");
  if (!lstrcmp(outstr,"ORBIS")) {
    char *OrbisCnfName = GetOrbisVar("ORBIS.CNF");
    SetOrbisCnfName(OrbisCnfName,ResolveOrbisVar);
    }
  }

#pragma optimize("",off)
void DoSetExePath (HINSTANCE hInstance)
  {
  char szFileName[256];
  GetModuleFileName (hInstance, szFileName, sizeof(szFileName));
  for (int i = lstrlen(szFileName); (i > 0) && (szFileName[i] != '\\') && (szFileName[i] != ':'); i--);
  if (i > 0)
    szFileName[i+1] = '\0';
  else
    *szFileName = '\0';
  SetExePath(szFileName);
  }
#pragma optimize("",on)

// caseinsensitiver String-Vergleich
BOOL IsStrEqual(LPSTR s1,LPSTR s2)
  {
  while ((*s1) && (*s2) &&
         (CharUpper(LPSTR(*s1)) == CharUpper(LPSTR(*s2)))) {
    s1++;
    s2++;
    }
  return (!*s1) && (!*s2);
  }

extern void FreeSocketData ();
extern void FreePrinterCaption ();
extern void delInstances ();
int PASCAL WinMain(
HINSTANCE hInstance,       // aktuelle Instanz
HINSTANCE hPrevInstance,   // Vorherige Instanz
LPSTR cmdln,            // Kommandozeile
int cmd                 // Kommando
                  )
  {
// #define SOFORT_DEBUGGEN 1
#ifdef SOFORT_DEBUGGEN
  DivideByZero();
#endif

  // erst mal den EXE-Pfad bestimmen
  DoSetExePath(hInstance);

  BOOL doTest = FALSE ;
  BOOL doCreate = FALSE ;
  BOOL doConvert = FALSE ;
  BOOL doUpdate = FALSE ;
  BOOL doEndOfUpdate = FALSE ;
  BOOL WithStartDir = FALSE ;
  char destDB[20];
  if ((cmdln != NULL) && (*cmdln)) {
    char cmdbuffer[256];
    lstrcpy (cmdbuffer,cmdln);
    for (LPSTR cstart = cmdbuffer ; *cstart ; ) {
      // Alle Zeichen skippen 
      BOOL domore;
      BOOL inString = FALSE ;
      for ( LPSTR cnext = cstart ; ((*cnext) && (!((*cnext == ' ') && (!inString)))) ; cnext ++ ) {
        if (*cnext == '"') inString = !inString;
        }
      if (*cnext == ' ') domore = TRUE ;
      else               domore = FALSE ;
      *cnext = '\0';
      if (IsStrEqual (cstart,"_TEST")) doTest = TRUE ;
      else if (IsStrEqual (cstart,"_CREATE")) doCreate = TRUE ;
      else if (IsStrEqual (cstart,"_CONVERTTO")) {
        // Naehchstes Wort haendisch Finden und weitermachen
        if (domore) cstart = cnext + 1 ;
        else        cstart = cnext ;
        for ( ; ((*cstart) && (*cstart == ' ')) ; cstart ++ ) ;
        for ( cnext = cstart ; ((*cnext) && (*cnext != ' ')) ; cnext ++ ) ;
        lstrcpy (destDB,cstart);
        if (*cnext == '\0') domore = FALSE ;
        doConvert = TRUE ;
        }
      else if (IsStrEqual (cstart,"_UPDATE")) doUpdate = TRUE ;
      else if (IsStrEqual (cstart,"_ENDOFUPDATE")) doEndOfUpdate = TRUE ;
      else if (IsStrEqual (cstart,"_DEBUG")) SetJustForDebug() ;
      else if (!DoppelPunktAbarbeitung (cstart)) {
        SetStartDir (cstart, "DMW.INI");
        WithStartDir = TRUE;
        }
      // Alles bis zum naechsten Zeichen skippen 
      if (domore) cstart = cnext + 1 ;
      else        cstart = cnext ;
      for ( ; ((*cstart) && (*cstart == ' ')) ; cstart ++ ) ;
      }
    }

  if (!WithStartDir)
    CheckOrbis();

#ifdef WIN32
  char retstr[5];

  // gibts einen Eintrag in der DMW.INI ?

  GetPrivateProfileString ("Profile","Debug","no",
                           retstr,sizeof(retstr),
                           MYINI
                          );
  if (!lstrcmp (retstr,"yes")) {
    if (MessageBox (NULL, "start debug session?", "DDS debug enabled",
                    MB_YESNO | MB_ICONQUESTION) == IDYES) {
      DivideByZero();
      }
    }
#endif

  if (!((cmdln != NULL) && (*cmdln))) {
    //-----------------------------------------------
    // In der DMW.INI sollte das Startup-Bitmap sein
    //-----------------------------------------------
    char retstr[128];
    GetPrivateProfileString ("Image","StartScreen","",
                              retstr,sizeof(retstr),
                              MYINI
                            );
    if (retstr[0] != '\0') {
      if (RegisterSplashWindow (hInstance)) {
        HWND hWndSplash = CreateWindowEx (WS_EX_TOPMOST, "SPLASHWINDOW", "TEST", 
                                          WS_POPUP | WS_VISIBLE | WS_BORDER, 
                                          100, 100, 500, 300, 
                                          GetDesktopWindow(), NULL, hInstance, 
                                          LPVOID(retstr));
        if (hWndSplash) {
          ShowWindow (hWndSplash, SW_SHOW);
          UpdateWindow (hWndSplash);
          }
        }
      }
    }

  MSG msg;
  // Exception-Handling 1. Teil:
#ifdef WIN32
  __try {
#else
  FARPROC mfh = MakeProcInstance((FARPROC)MyFaultHandler,hInstance);
  if (!InterruptRegister(NULL, mfh))
    WIN_ASSERT_TEXT(FALSE,"Kann Exception-Handler nicht installieren !");
#endif
  FARPROC owa = MakeProcInstance((FARPROC)OnWinAssertProc,hInstance);
  SetOnWinAssertProc(owa);
  GetNWAddress (MyErrorContext,sizeof(MyErrorContext));
  MyErrorContext[MyErrorContext[0]+1] = '\0';
  GetProductVersion(MyVersionAndErrorContext);
  lstrcat(MyVersionAndErrorContext," / ");
  lstrcat(MyVersionAndErrorContext,MyErrorContext + 1);
  SetErrorContextStr(MyVersionAndErrorContext);
  // Ende Exception-Handling 1. Teil

  // einfache Mehrsprachigkeit mittles Texttabelle
  InitLanguageTextTable();

  DBClean_Init();

  SetMessageQueue (100);
#ifdef MEMCHK
  preplog ();
#endif

  InitExtraMem ();

  DoInitDBHelp();

  CTOOL_SetClassNames ("DDSLISTCLASS","DMWSToolBar","WORDWIN","BubbleWindow","FOLDERWINDOW");
  double r ;
  GetResolutionCF (&r);
  DMWAPI_SetClassNames ("WORDWIN",NULL,r);

  STATBAR_SetClassNames ("STATBAR");

  PrepareWithHashs ();

  WBase::hInstance = hInstance;
  if (hPrevInstance) {
    AskUser (13010,MB_ICONEXCLAMATION | MB_OK);
    return 0;
    }

#ifndef WIN32
  Ctl3dRegister (WBase::hInstance);
  Ctl3dAutoSubclass (WBase::hInstance);
#endif

  if (SucheParameter ("MEMFILENAME") == NULL)
    SetupDDE (WBase::hInstance);
#ifdef WIN32
  OleInitialize (NULL);
#endif

  // Datenbank - Handling initialisieren
  FARPROC olmp;
  FARPROC exch;
  DMWAPI_Setup (CLEARQUEUE(olmp = MakeProcInstance(FARPROC(_ClearQueue),WBase::hInstance)),
                  GetAsync_cmdfifo(),
                  GetAsync_cmdfifo(),
                  GetCallContextFunction ()
               );
  AsyncFifoPtr = GetAsync_cmdfifo();
  GetTableAdmin()->Initialize(doTest || doCreate);

  if (EntwicklungsUmgebung()) {
    // Untersuchung, ob das System einen
    // vollen Update benoetigt (Durch speziellen Datensatz im
    //      Datadictionary mitgeteilt)
    DWORD DataSize;
    GLOBALHANDLE hGres = ReadDataDict (5,0,0,&DataSize);
    if (hGres) {
      doUpdate = TRUE ;
      GlobalFree (hGres);
      DelDataDict (5,0,0);
      }
    if (!doUpdate)
      UpdateIntermediate ();
    }
  if (doEndOfUpdate) {
    GetDLLAdmin()->GetDLLEntry(GetTransactionDLL())->DBCall (DBOP_STARTOFUPDATE,-1,NULL,NULL,NULL);
    GetDLLAdmin()->GetDLLEntry(GetTransactionDLL())->DBCall (DBOP_ENDOFUPDATE,-1,NULL,NULL,NULL);
    }
  if ((doTest) || (doConvert) || (doCreate)) {
    if ((doTest) || (doCreate)) DBTest (doCreate);
    // else                        DBConvert (FindNextWord (cmdln));
    else                        DBConvert (destDB);

#ifndef WIN32
    InterruptUnRegister(NULL);
    FreeProcInstance(mfh);
#endif
    SetOnWinAssertProc(NULL);
    FreeProcInstance(owa);

    GetTableAdmin()->OnExit();
    GetDLLAdmin()->ResetDLLAdmin();
    return 0 ;
    }
  LoadScriptContent ();
  cToolInit ();

  /*---------< Registrierung der MDI-FrameWindow-Fensterklasse >-------*/
  WBase w(hInstance);
  COMPILE_Setup (WBase::hFrameWin,EXTCHKMSG (exch = MakeProcInstance(FARPROC(_ExternCheck),WBase::hInstance)));
  SetupQueue (WBase::hFrameWin,EXTCHKMSG(exch));

  // Exportmenue raushauen, ausser wenn anders gewuenscht (in dmw.ini)
#define CONFIGSECTION "Config"
#define MAYEXPORT     "Export"
#define MAYEXPORTDEF  "no"
  char expstr[20];
  GetPrivateProfileString (CONFIGSECTION,MAYEXPORT,MAYEXPORTDEF,
                           expstr,sizeof(expstr),
                           MYINI
                          );
  if (lstrcmp (expstr,"yes") != 0) {
    HMENU mymenu = GetMenu(WBase::hFrameWin);
    HMENU mypopup = GetSubMenu(mymenu,0);      // Dateimenue
    RemoveMenu(mypopup,2,MF_BYPOSITION);       // &Export
    RemoveMenu(mypopup,1,MF_BYPOSITION);       // SEPARATOR
    }

  SetPrinterCallBack ();
  InitFrmObjDll ();

  /*--------< Laden der Tastaturkuerzel >------------------------------*/
  hAccelTable = LoadAccelerators (hInstance,"Acc") ;

  /*---------< Installieren der Formate >--------------------*/
  Printer *Pr = GetPrinter (TRUE);
  Pr->PrinterDC ();
  ReadFormatInfo ();

  CreateCommunic ();
  SetFrameWnd (WBase::hFrameWin);

#ifdef DEBUG
  InquireBreakPoints ();
#endif

  CreateControl (doUpdate);

  DCInitialize (WBase::hFrameWin);

  #ifdef DOPROFILE
    ProfSetup (1064,0);
  #endif


  /*--------< MSW event loop >-----------------------------------------*/
#ifdef WIN32

  // in der 32 Bit-Version muss auf die Idle-Schleife Ruecksicht genommen 
  // werden, um "Background Processing" zu ermoeglichen
  BOOL doStop = FALSE;

  for ( ; ; ) {
  while(PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT)
      doStop = TRUE ;
    else {
      if (!FilterDLLMsgForExternDLL (&msg))
        CheckMsg (&msg);
      }
    }
  if ((!doStop) && (!QuitDone)) {
    ProcessDLLIdleForExternDLL();
    WaitMessage ();
    }
  else
    break ;
  }
#else
  while(GetMessage (&msg, NULL, 0, 0)) {
    CheckMsg (&msg);
    }
#endif

#ifdef DEBUG
  RemoveAllBreakPoints ();
#endif

#ifdef WIN32
  OleUninitialize();
#endif

  // if (SucheParameter ("MEMFILENAME") == NULL)
  //   UninitializeDDE();

  FreeProcInstance (olmp);
  FreeProcInstance (exch);
  DMWAPI_ShutDown ();

  DestroyControl ();

  DeleteFonts();

  // Restliche Daten noch freigeben
  cToolExit ();
  FreeListProcs ();
  Pr->ReleasePrDC ();
  FreePrinter (Pr);

  DelAllhMF ();
  PrgStat.Exit ();

  FreeAllExternDlls();

  #ifdef PROFILE
    ProfFinish ();
  #endif

  // schadet nie
  DCExit();

  ToolBarCleanUp ();

  UnloadScriptContent ();
  GetTableAdmin()->OnExit();
  GetDLLAdmin()->ResetDLLAdmin();

#ifdef MEMCHK
  closelog ();
#endif

#ifndef WIN32
#ifdef DEBUG
  CheckGlobalAllocs();
#endif
#endif

  DelBackBrush ();
  FreeAllTrackCursors ();
  ClearFuncHash();
  FreeAllArgs ();
  delInstances ();

#ifndef WIN32
  Ctl3dUnregister (WBase::hInstance);
#endif

  FreeWithHashs ();
  fntDeleteAllFormats ();
  RemoveMDIHandleList ();

  SetOnWinAssertProc(NULL);
  FreeProcInstance(owa);
  FreeExtraMem ();
  DelKTypeList ();
  FreeGlobalContextMenu ();

  DestroyCommunic ();

  WriteSizeStat ();
#ifdef WIN32
  }
  __except (My32BitCFaultHandler(GetExceptionInformation()))
    { }
#else
  // Exception-Handling 2. Teil
  InterruptUnRegister(NULL);
  FreeProcInstance(mfh);
  // Ende Exception-Handling 2. Teil
#endif

  FreeSocketData ();
  FreePrinterCaption ();
  FreeLinMem ();
  return msg.wParam;
  }   // end of WinMain()

/*------< Message - Boxes >------------*/
WORD AskUser (WORD Index,WORD wType)
  {
  char InZeile0  [100];
  char InZeile1 [100];
  LoadString (WBase::hInstance,Index  ,InZeile0,sizeof (InZeile0));
  LoadString (WBase::hInstance,Index+1,InZeile1,sizeof (InZeile1));
  return MessageBox (GetActiveWindow(),InZeile1,InZeile0,wType | MB_TASKMODAL);
  }

WORD AskUser (WORD Index,WORD wType,char *str)
  {
  char InZeile0 [100];
  char InZeile1 [100];
  char outline [100];
  LoadString (WBase::hInstance,Index  ,InZeile0,sizeof (InZeile0));
  LoadString (WBase::hInstance,Index+1,InZeile1,sizeof (InZeile1));
  sprintf (outline,InZeile1,str);
  return MessageBox (GetActiveWindow(),outline,InZeile0,wType | MB_TASKMODAL);
  }

WORD AskUser (HWND hDlg,WORD Index,WORD wType)
  {
  char InZeile0  [100];
  char InZeile1 [100];
  LoadString (WBase::hInstance,Index  ,InZeile0,sizeof (InZeile0));
  LoadString (WBase::hInstance,Index+1,InZeile1,sizeof (InZeile1));
  return MessageBox (hDlg,InZeile1,InZeile0,wType | MB_TASKMODAL);
  }

HWND hPrWnd;
DLLExport void _export WINAPI CTOOL_NotifyPrinting (BOOL inProgress);
DLLExport BOOL _export WINAPI PrCallBack (WORD Action)
  {
  BOOL res = FALSE ;
  switch (Action) {
    case PRCALLBACK_SETSTARTPRINTIG  :
      CTOOL_NotifyPrinting (TRUE);
#ifndef WIN32
      SetStartPrinting ();
#endif
      break ;
    case PRCALLBACK_SETENDPRINTING   :
      CTOOL_NotifyPrinting (FALSE);
#ifndef WIN32
      SetEndPrinting ();
#endif
      break ;
    case PRCALLBACK_DISABLELAYOUT    :
      break ;
    case PRCALLBACK_ENABLELAYOUT     :
      break ;
    case PRCALLBACK_DISABLEFWND      :
      EnableWindow (hPrWnd = GetActiveWindow(),FALSE);
      break ;
    case PRCALLBACK_ENABLEFWND       :
      if (IsWindow (hPrWnd))
        EnableWindow (hPrWnd,TRUE);
      else
        EnableWindow (WBase::hFrameWin,TRUE);
      hPrWnd = 0;
      break ;
    case PRCALLBACK_SETLAYOUTFOCUS   :
      break ;
    case PRCALLBACK_SETFWNDFOCUS     :
      SetFocus (WBase::hFrameWin);
      break ;
    }
  return res;
  }

void SetPrinterCallBack ()
  {
  PRCALLBACK prcbfnc = PRCALLBACK (MakeProcInstance (FARPROC(PrCallBack),WBase::hInstance));
  PrCallback (WBase::hFrameWin,prcbfnc);
  }

#pragma pack(1)
struct Ltx_param {
  WORD parSize;
  DWORD res;
  DWORD id;
  DWORD def;
  };
#pragma pack()

BOOL Ltx(mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Ltx_param FAR *par = (Ltx_param FAR *) param ;
    LPDWORD lpid = LPDWORD (c->ReadlData (par->id));
    LPSTR s = NULL;
    if (lpid != NULL) {
      DWORD id;
      if (GetBlockSize(lpid) == sizeof(DWORD))
        id = *lpid;
      else  // short
        id = DWORD(*LPWORD(lpid));
      s = Ltx (id);
      }
    if ((s == NULL) && (par->parSize >= sizeof(*par))) {
      s = LPSTR (c->ReadlData (par->def));
      }
    if (s != NULL)
      c->WritelData (par->res,s,lstrlen(s) + 1,LPSTR(par)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(par)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Ltx_param FAR *par = (Ltx_param FAR *) param ;
    c->ClearlConnection (par->id,LPSTR(par)-sizeof(WORD));
    if (par->parSize >= sizeof(*par))
      c->ClearlConnection (par->def,LPSTR(par)-sizeof(WORD));
    }
  return FALSE ;
  }

