///////////////////////////////////////////////////////////////
//  Anbinden der Toolbar - Library
///////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/rev/ddstool.cpv   1.164   18 May 2000 09:53:20   Dave  $
//  $Log:   F:/marille/clinicum/rev/ddstool.cpv  $
// 
//    Rev 1.164   18 May 2000 09:53:20   Dave
// Drucken: Fehlerhandling beim StartDoc
// 
//    Rev 1.163   01 May 2000 13:41:46   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.162   19 Jan 2000 21:20:48   Martin
// IsPrinting vor jeder Kopie wieder auf TRUE sezten
// 
//    Rev 1.161   23 Dec 1999 20:46:26   Martin
// Rekursives SetExtra...
// 
//    Rev 1.160   21 Dec 1999 23:57:34   Martin
// OldInClientTransaction in SetPrinter
// 
//    Rev 1.159   03 Dec 1999 19:41:14   Martin
// benutzerdefiniertes Papierformat
// 
//    Rev 1.158   28 Oct 1999 00:20:48   Hannes
// Drucken: Schachtaenderung
// 
//    Rev 1.157   20 Oct 1999 07:51:28   Martin
// Wartezeit beim Drucken...
// 
//    Rev 1.156   12 Aug 1999 08:26:46   Hannes
// SetVeryBestWidth ohne nachfolgenden Rescale...
// 
//    Rev 1.155   04 Jun 1999 01:28:18   Hannes
// SetDocVeryBestWidth
// 
//    Rev 1.154   27 Apr 1999 01:45:26   Hannes
// Diverse Speicherfresser
// 
//    Rev 1.153   02 Apr 1999 10:54:02   Hannes
// Absichern gegen Fehlen der OCX - Treiber
// 
//    Rev 1.152   31 Mar 1999 14:55:14   Gerhold
// htmlhelp
// 
//    Rev 1.151   08 Feb 1999 10:29:58   Hannes
// MergeText auch mit leeren Texten
// 
//    Rev 1.150   28 Dec 1998 10:11:54   Hannes
// OpenFileName: mit Multiselektion
// 
//    Rev 1.149   23 Dec 1998 19:13:34   Martin
// bei PrinterChanged auch noch den Standarddrucker sauber beruecksichtigen
// 
//    Rev 1.148   23 Dec 1998 16:04:16   Martin
// Diagnostische prints in printerchanged (auskommentiert !)
// 
//    Rev 1.147   18 Dec 1998 15:50:12   Martin
// Schacht-Handling verbessert
// 
//    Rev 1.146   07 Dec 1998 18:40:50   Martin
// DOCINFO initialisieren
// 
//    Rev 1.145   09 Oct 1998 18:13:04   Hannes
// Farbfunktionen fuer Stringeingaben
// 
//    Rev 1.143   11 Aug 1998 08:42:26   Hannes
// Startparameter
// 
//    Rev 1.142   09 Aug 1998 22:36:14   Hannes
// Verbesserungen Kontextmenue
// 
//    Rev 1.141   07 Aug 1998 00:01:32   Hannes
// SetPrinterCaption
// 
//    Rev 1.140   30 Jul 1998 11:06:50   Gerhold
// CallWindowsHelp angepasst fuer den HELP_FINDER
// 
//    Rev 1.139   27 Jul 1998 09:53:20   Hannes
// Doppelseitiger Druck
// 
//    Rev 1.138   02 Jul 1998 11:09:00   Hannes
// Handling Zeitversetztes Destroy
// 
//    Rev 1.137   29 Jun 1998 18:58:46   Hannes
// GetResFactor
// 
//    Rev 1.136   25 May 1998 16:44:54   Hannes
// GetTextFrom ... Schreiben eines sizeof(DBINT)
// 
//    Rev 1.135   25 May 1998 13:37:44   Hannes
// 
//    Rev 1.134   22 May 1998 12:03:30   Hannes
// Vermerken der Groessen eines Schirms / Update kann korrekt durchgefuehrt
// werden
// 
//    Rev 1.133   30 Mar 1998 19:54:02   Hannes
// GetObjModify ... SetConnection auf Objekt
// 
//    Rev 1.132   20 Mar 1998 15:28:38   Hannes
// 
//    Rev 1.131   17 Mar 1998 19:04:40   Hannes
// SetDocBestSize
// 
//    Rev 1.130   17 Mar 1998 17:57:28   Hannes
// SetPrinter auch innerhalb printdocumentex
// 
//    Rev 1.129   02 Mar 1998 19:14:24   Hannes
// Aktuelle Seite mit sizeof(DBINT)
// 
//    Rev 1.128   18 Feb 1998 10:27:52   Hannes
// Prototyp von tbactive
// 
//    Rev 1.127   10 Feb 1998 18:26:50   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.126   02 Feb 1998 20:32:44   Hannes
// Angabe eines Filenamens->Defaultmaessiges Vorbelegen
// 
//    Rev 1.125   16 Jan 1998 15:27:14   Hannes
// Listenfarben
// 
//    Rev 1.124   05 Jan 1998 07:53:54   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.123   20 Nov 1997 14:54:54   Hannes
// PrintDocumentEx... GetOutContext(c)
// 
//    Rev 1.122   04 Nov 1997 17:55:00   Hannes
// OpenFileName modal
// 
//    Rev 1.121   29 Oct 1997 19:00:14   Hannes
// Textbausteine
// 
//    Rev 1.120   24 Oct 1997 08:37:34   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.119   23 Sep 1997 12:46:54   Hannes
// 
//    Rev 1.118   19 Sep 1997 12:59:38   Gerhold
// SetOnSetFocus mit neuem Parameter bKillProc
// 
//    Rev 1.117   14 Aug 1997 22:03:14   Hannes
// Ueberpruefen von Eindeutigkeiten der Tastendrucke...
// 
//    Rev 1.116   07 Aug 1997 11:53:18   Hannes
// 
//    Rev 1.115   06 Aug 1997 14:13:06   Martin
// Trcaing raus
// 
//    Rev 1.114   01 Jul 1997 14:38:48   Hannes
// No change.
// 
//    Rev 1.113   19 Jun 1997 15:09:04   Hannes
// 
//    Rev 1.112   19 Jun 1997 12:55:20   Hannes
// Read auf den Parentscreen prinzipiell unterbunden
// 
//    Rev 1.111   12 Jun 1997 16:59:32   Martin
// StartFrame ...
// 
//    Rev 1.110   12 Jun 1997 16:07:58   Martin
// NeueSeite ...
// 
//    Rev 1.109   13 May 1997 07:55:42   Hannes
// 
//    Rev 1.108   05 May 1997 11:37:42   Hannes
// Speicherfresser
// 
//    Rev 1.107   11 Apr 1997 11:37:36   Gerhold
// OnScreenButtonDown ... jetzt auch mit optionaler rechter Maustaste
// 
//    Rev 1.106   10 Apr 1997 11:44:28   Hannes
// ToolSelectionInString
// 
//    Rev 1.105   08 Apr 1997 17:40:44   gerhold
// CallWindowsHelp ... SetHelpFile
// 
//    Rev 1.104   04 Apr 1997 15:16:42   Gerhold
// ShowToolList arbeit
// 
//    Rev 1.103   02 Apr 1997 19:21:06   Martin
// ShowToolList: auch schreiben als DBINT !!!!
// 
//    Rev 1.102   26 Mar 1997 14:21:08   Hannes
// Ausgabekontext Setzen von Einem Modul, das bereits einen Ausgabekontext
// besitzt
// 
//    Rev 1.101   13 Mar 1997 18:58:04   Hannes
// ExtChildFromBlob, SetToolRefHandleExplizit
// 
//    Rev 1.100   28 Feb 1997 15:03:38   Gerhold
// AppendContextMenu ... Erweiterung der kontextsensitiven Menus
// 
//    Rev 1.99   28 Feb 1997 14:42:42   Hannes
// SetCaretTo
// 
//    Rev 1.98   19 Feb 1997 12:21:34   Hannes
// InsertStringAtCaret
// 
//    Rev 1.97   28 Jan 1997 11:23:28   GERHOLD
// SetEditCaretToEnd erweitert
// 
//    Rev 1.96   27 Jan 1997 17:26:28   HANNES
// OnOff bei SetObjModify
// 
//    Rev 1.95   18 Dec 1996 17:46:50   HANNES
// pragma pack()
// 
//    Rev 1.94   17 Dec 1996 16:17:56   HANNES
// 
//    Rev 1.93   16 Dec 1996 19:43:12   HANNES
// 
//    Rev 1.92   09 Dec 1996 18:22:52   HANNES
// Mouseprozedur fuer Screen
// 
//    Rev 1.91   05 Dec 1996 19:08:44   HANNES
// 
//    Rev 1.90   05 Dec 1996 15:08:48   HANNES
// 
//    Rev 1.89   26 Nov 1996 08:13:44   HANNES
// Automatischer Update
// 
//    Rev 1.88   08 Nov 1996 13:32:44   HANNES
// HideScreen
// 
//    Rev 1.87   30 Oct 1996 08:43:10   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.86   29 Oct 1996 10:00:14   HANNES
// 
//    Rev 1.85   23 Oct 1996 19:38:44   HANNES
// ShowToolList
// 
//    Rev 1.84   23 Oct 1996 09:43:56   GERHOLD
// GetVarSize
// 
//    Rev 1.83   24 Sep 1996 19:01:38   GERHOLD
// CallWindowsHelp ruft nicht .  auf, sondern setzt HelpKontextNr
// 
//    Rev 1.82   20 Sep 1996 13:24:00   GERHOLD
// . 
// 
//    Rev 1.81   18 Sep 1996 20:47:08   GERHOLD
// 
//    Rev 1.80   06 Sep 1996 17:26:34   HANNES
// 
//    Rev 1.79   03 Sep 1996 10:01:48   HANNES
// Fehlerkorrektur bei Debuggerbreakpoints in Knopfprozeduren
// 
//    Rev 1.78   06 Aug 1996 15:05:02   WOLFGANG
// 1.) initialDir in FileSelector_Box bei path nicht NULL von path holen,
//     anstatt bei path NULL.
// 
//    Rev 1.77   31 Jul 1996 14:49:14   LENS
// WinAssert beim PresentBitmap ausgebaut.
// 
//    Rev 1.76   25 Jul 1996 19:48:56   GERHOLD
// pragma pack(1)
// 
//    Rev 1.75   03 Jul 1996 15:33:54   GERHOLD
// int FAR *  =>  DBINT FAR *
// 
//    Rev 1.74   20 Jun 1996 15:19:02   GERHOLD
// Der Update auf die Position im Dialog war doch nicht so richtig
// Update-Zweig im CreateScreen (lppos)
// 
//    Rev 1.73   17 Jun 1996 17:10:20   HANNES
// 
//    Rev 1.72   04 Jun 1996 13:01:16   GERHOLD
// GetToolCoordinates, SetDialogPos
// 
//    Rev 1.71   14 May 1996 16:03:26   GERHOLD
// #pragma pack(1)
// 
//    Rev 1.70   23 Apr 1996 15:04:34   HANNES
// Makro ENTER, ENTER1: Keine Extradaten -> Aufruf von RestoreListFnc
// 
//    Rev 1.69   19 Apr 1996 17:45:52   MARTIN
// DLL-Anbindung
// 
//    Rev 1.68   04 Apr 1996 18:35:56   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.67   24 Mar 1996 12:08:32   HANNES
// mehrseitige cFields
// 
//    Rev 1.66   22 Mar 1996 12:18:10   HANNES
// Aenderungen Hannes
// 
//    Rev 1.65   18 Mar 1996 16:18:00   GERHOLD
// SetToolObjectColor (aendert die Farbe fuer Dialogelemente)
// 
//    Rev 1.64   16 Feb 1996 13:10:30   MARTIN
// FreeProcInstance(old) raus
// 
//    Rev 1.63   06 Feb 1996 17:51:48   MARTIN
// sizeof(*LastPage)
// 
//    Rev 1.62   02 Feb 1996 10:35:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.60   10 Jan 1996 18:20:34   HANNES
// SetObjModify, GetObjModify, SetObjFormatMaps, SetToolFormatMaps
// 
//    Rev 1.59   02 Jan 1996 22:21:16   HANNES
// 
//    Rev 1.58   05 Dec 1995 14:03:52   GERHOLD
// SetEditMode ... Feldmodus fuer Dialog-Eingabefelder
// 
//    Rev 1.57   23 Nov 1995 13:22:58   GERHOLD
// In ShowToolList koennen nun Breite und Hoehe der Liste angegeben werden.
// 
//    Rev 1.56   20 Nov 1995 11:37:56   HANNES
// TB_FOCUSCHANGING
// 
//    Rev 1.55   15 Nov 1995 17:38:30   GERHOLD
// SetDocBestWidth ... reagiert jetzt auch auf EM_UPDATE
// SetMapExtent ...... Position und Groesse einer Mappe aendern
// 
//    Rev 1.54   18 Oct 1995 11:13:38   GERHOLD
// UpdateScreenImmediate
// 
//    Rev 1.53   04 Oct 1995 16:03:12   MARTIN
// GetRecordWithListReverse
// 
//    Rev 1.52   29 Sep 1995 16:55:46   MARTIN
// GetBaseUnit
// 
//    Rev 1.51   25 Sep 1995 17:33:50   MARTIN
// DBWIN_ASSERT -> WIN_ASSERT
// 
//    Rev 1.50   16 Sep 1995 22:33:22   HANNES
// Version Hannes
// 
//    Rev 1.49   16 Sep 1995 02:28:38   HANNES
// 
//    Rev 1.48   13 Sep 1995 01:22:28   HANNES
// 
//    Rev 1.47   11 Sep 1995 20:24:54   MARTIN
// OnSetFocusProc
// 
//    Rev 1.46   08 Sep 1995 10:13:36   MARTIN
// Farbe auch bei Typ 1 - Bitmaps lesen
// 
//    Rev 1.45   07 Sep 1995 09:03:22   HANNES
// SetToolPalette
// 
//    Rev 1.44   24 Aug 1995 00:19:50   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.43   14 Aug 1995 08:27:02   HANNES
// Referenzfenster fuer normale DialogDocuments
// 
//    Rev 1.42   10 Aug 1995 09:27:20   HANNES
// PrintDocumentEx
// 
//    Rev 1.41   11 Jul 1995 12:47:10   HANNES
// Expressionoptimierung
// 
//    Rev 1.40   07 Jul 1995 17:18:06   GERHOLD
// CreatePostIt
// 
//    Rev 1.39   02 Jul 1995 18:27:44   HANNES
// BitSelect - Hilfsfunktionen, CreateScreen: Update auf w,h
// 
//    Rev 1.38   27 Jun 1995 13:52:34   HANNES
// DefTransparentBitmap
// 
//    Rev 1.37   14 Jun 1995 13:03:26   HANNES
// Extradaten an CTOOL nur im Falle vom EM_LOAD weitergegeben (ansonsten wuerde
// Speicher verschwinden...)
// 
//    Rev 1.36   10 Jun 1995 22:03:58   GERHOLD
// Seite nicht ueberschreiben im falle eines Updates
// 
//    Rev 1.35   09 Jun 1995 14:23:48   GERHOLD
// GetVarSize..
// 
//    Rev 1.34   09 Jun 1995 00:15:26   HANNES
// SetDocSide etwas toleranter: auch ohnen AnzSides ein vernuenftiges Verhalten
// Optimierter Aufruf von InitializeBars
// 
//    Rev 1.33   20 May 1995 16:16:38   MARTIN
// Drucken von BMPs
// GetVarSize
// SetEditMaxSize
// 
//    Rev 1.32   04 May 1995 18:38:26   HANNES
// 
//    Rev 1.31   02 May 1995 21:06:52   HANNES
// Filselektorbox auch fuer Neue Files
// 
//    Rev 1.30   14 Apr 1995 11:03:52   HANNES
// 
//    Rev 1.29   04 Apr 1995 12:10:10   HANNES
//  
// 
//    Rev 1.28   31 Mar 1995 13:09:42   HANNES
//  
// 
//    Rev 1.27   27 Mar 1995 13:16:40   HANNES
//  
// 
//    Rev 1.26   20 Mar 1995 11:55:30   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.25   16 Feb 1995 12:52:04   HANNES
// 
//    Rev 1.24   24 Jan 1995 11:01:50   HANNES
// 
//    Rev 1.23   22 Jan 1995 15:05:18   HANNES
// Beim Laden das Startupprogramm angebbar
// 
//    Rev 1.22   09 Jan 1995 12:14:28   HANNES
// Debugger eingebaut
// 
//    Rev 1.21   16 Dec 1994 16:25:28   GERHOLD
// Focus Gschichterln
// 
//    Rev 1.20   15 Dec 1994 22:14:38   HANNES
// SetFocusToDoc
// 
//    Rev 1.19   08 Dec 1994 22:06:10   HANNES
// 
//    Rev 1.18   05 Dec 1994 17:42:36   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.17   21 Nov 1994 20:39:48   HANNES
// 
//    Rev 1.16   20 Nov 1994 18:42:42   HANNES
// 
//    Rev 1.15   20 Nov 1994 18:02:04   HANNES
// Defaultwert beim GetTextFrom
// 
//    Rev 1.14   18 Nov 1994 19:58:52   HANNES
// No change.
// 
//    Rev 1.13   16 Nov 1994 18:39:04   GERHOLD
// GetDocBestWidth
// 
//    Rev 1.12   12 Nov 1994 14:36:30   GERHOLD
// Probleme bei ShowToolList in Mappen in Dialogfenstern!
// Ab jetzt wird ueberprueft, ob das Parent der Liste den Stil WS_CHILD hat.
// 
//    Rev 1.11   17 Oct 1994 15:03:56   HANNES
// Umstellung von verschiedenen Tools auf den DrawContext()
// 
//    Rev 1.10   11 Oct 1994 09:43:40   HANNES
// Einbau der Zoomrectfunktionen
// 
//    Rev 1.9   20 Sep 1994 11:33:30   HANNES
// Umstellung auf OutContext ....
// 
//    Rev 1.8   14 Sep 1994 19:34:20   HANNES
// ActivateControl ... nur wenn RefWnd != 0 ...
// 
//    Rev 1.7   05 Sep 1994 15:37:24   HANNES
// ColumnList
// 
//    Rev 1.6   24 Aug 1994 19:44:04   HANNES
// ShowMPObjectList
// 
//    Rev 1.5   05 Aug 1994 17:12:42   HANNES
// ShowObjectList eingebaut
// 
//    Rev 1.4   13 Jul 1994 21:14:46   HANNES
// fncarr.hpp ... Indizess haben sich geaendert
// 
//    Rev 1.3   12 Jul 1994 14:50:32   HANNES
// Fehlerkorrektur in UseDocument
// 
//    Rev 1.2   05 Jul 1994 15:46:30   HANNES
// Umstellung in toolbar.hpp
// 
//    Rev 1.1   24 Jun 1994 19:47:24   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.26   14 Apr 1994 16:59:18   HANNES
// SetEditOverwrite
// 
//    Rev 1.25   13 Apr 1994 14:32:24   HANNES
// FreePrinter bei SetDocumentPrinter
// 
//    Rev 1.24   03 Mar 1994 22:08:02   HANNES
// PrintMeta
// 
//    Rev 1.23   04 Feb 1994 16:53:20   MARTIN
// RemoveDIBListElem entfernt
// 
//    Rev 1.22   24 Jan 1994 11:13:42   HANNES
// Testfunktionen, die auch vom Script her aufgerufen werden koennen
// 
//    Rev 1.21   20 Jan 1994 23:56:40   HANNES
// ClearQueue, ShowToolList mit Procedur beim OK - Knopf
// 
//    Rev 1.20   13 Jan 1994 16:03:44   HANNES
// SetEditCaretToEnd
// 
//    Rev 1.19   12 Jan 1994 11:05:50   HANNES
// Alte Druckfunktionen raus
// 
//    Rev 1.18   11 Jan 1994 19:07:42   HANNES
// GetDefaultPrinterName, SetCaretToEnd
// 
//    Rev 1.17   04 Jan 1994 16:33:06   HANNES
// Nummerierung der Seiten
// 
//    Rev 1.16   09 Dec 1993 14:57:12   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.15   16 Nov 1993 04:21:08   HANNES
// Drucken auch hinter dem "offiziellen" Ende
// 
//    Rev 1.14   03 Nov 1993 19:21:48   HANNES
// ToBusyCursor
// 
//    Rev 1.13   18 Oct 1993 19:55:16   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.12   11 Oct 1993 12:16:10   HANNES
// Bemerkungen
// 
//    Rev 1.11   06 Oct 1993 09:49:56   HANNES
// FileHandling, Bemerkungen
// 
//    Rev 1.10   04 Oct 1993 09:37:26   GERHOLD
// Aenderung der Seite von Aussen->PutDocExtraData (ActSideRef)...
// SetWindowDimension
// SetWindowCaption ... Anderungen an eime Screen..
// 
//    Rev 1.9   24 Sep 1993 22:47:34   GERHOLD
// 
//    Rev 1.8   22 Sep 1993 09:16:20   HANNES
// Version nach St. Poelten
// 
//    Rev 1.7   05 Sep 1993 22:17:20   HANNES
// Aufraemarbeiten
// 
//    Rev 1.6   24 Aug 1993 10:33:36   HANNES
// SetFocusToDoc
// 
//    Rev 1.5   23 Aug 1993 19:30:42   HANNES
// ...
// 
//    Rev 1.4   18 Aug 1993 10:25:12   HANNES
// Verschiedene neue Funktion, Printdocument
// 
//    Rev 1.3   05 Aug 1993 13:04:54   HANNES
// SwitchToNextField, SwitchToPrevField
// 
//    Rev 1.2   22 Jul 1993 20:52:58   HANNES
// Tools..
// 
//    Rev 1.1   12 Jul 1993 07:54:04   HANNES
// Erweiterungen um Listen
// 
//    Rev 1.0   05 Jul 1993 14:36:48   HANNES
// Initial revision.
// 
//    Rev 1.0   05 Jul 1993 14:33:56   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <string.h>

#ifdef GetDirMitCLIB
#include "shlobj.h"
#include "cabvw2.h"
#endif
#include "htmlhelp.h"

#ifdef WIN32
  #include <wingdi.h>
  #define _INC_PRINT
#else
  #include <print.h>
#endif

#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "image.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"
#include "multipro.hpp"

#include "winextra.hpp"
#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "mdiclien.hpp"
#define MODULENUM 26
#include "winass.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"
#include "multl.hpp"
#include "dds.h"

#include "testind.hpp"
#include "mappe.hpp"

#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#include "tbcbd.hpp"

#include "ddsmsg.h"

#define NOFUNCTION
#include "resadmin.hpp"

#define ENTER1(A) if (BlockIsActive) { \
                    A ; \
                    } \
                  else { \
                    if (LPTBD(PrivData)->Extra != NULL) { \
                      SAVEREC old; \
                      LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                      SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                      LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();     \
                      LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;     \
                      A ; \
                      LPTBD(PrivData)->c->RestoreRecs(old);  \
                      } \
                    else { \
                      RestoreListFnc rlf (LPTBD(PrivData)->c);  \
                      A ; \
                      } \
                    }
#define ENTER1DEB(A) if (BlockIsActive) { \
                        PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                        A ; \
                        } \
                      else { \
                        if (LPTBD(PrivData)->Extra != NULL) { \
                          SAVEREC old; \
                          LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                          SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                          PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                          LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();     \
                          LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;     \
                          A ; \
                          LPTBD(PrivData)->c->RestoreRecs(old);  \
                          } \
                        else { \
                          PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                          RestoreListFnc rlf (LPTBD(PrivData)->c);  \
                          A ; \
                          } \
                        }
#define ENTER(A) if (BlockIsActive) { \
                    A ; \
                    } \
                  else { \
                    if (LPTBD(PrivData)->Extra != NULL) { \
                      SAVEREC old; \
                      LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                      SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                      A ; \
                      LPTBD(PrivData)->c->RestoreRecs(old);  \
                      } \
                    else { \
                      RestoreListFnc rlf (LPTBD(PrivData)->c);  \
                      A ; \
                      } \
                    }
#ifdef UEBERLEGT
void DoTBCall (LPTBD PrivData,DWORD CmdOffset,LPVOID par) 
  {
  if (PrivData->Extra != NULL) {
#ifdef DEBUG
    PushToCallStack (PrivData->c,PrivData->c->schd->fName,PrivData->c->GetCmdOffset (par));
#endif
    SAVEREC old;
    PrivData->c->SetRecsForUpdate (old,PrivData->Extra);
    SetExtraInfo s(PrivData->c,PrivData->Extra);
    PushToCallStack (PrivData->c,PrivData->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par));
    PrivData->c->_GetRecExtra()->cmdBase = PrivData->c->GetCmdBase();
    PrivData->c->_GetRecExtra()->cOffs = 0;
    PrivData->c->_GetRecExtra()->fOffs = 0;
    MultiProc FAR *mp = new MultiProc (PrivData->c,CmdOffset);
    SetExtraInfo extra(PrivData->c,mp->CorrOffs());
    mp->AddProcAtTail(0);
    mp->ExCuteLast (EM_LOAD | EM_CHANGETOTRUE,&extra);
    mp->ExCuteLast (EM_RESET,&extra);
    PrivData->c->RestoreRecs(old);
    mp->RemoveLast ();
    delete mp ;
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  else {
#ifdef DEBUG
    PushToCallStack (PrivData->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par));
#endif
    RestoreListFnc rlf (PrivData->c);
    PrivData->c->ExCuteProc (CmdOffset,EM_LOAD | EM_CHANGETOTRUE);
    PrivData->c->ExCuteProc (CmdOffset,EM_RESET);
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  }
#define ENTER(A) if (BlockIsActive) { \
                    A ; \
                    } \
                  else { \
                    if (LPTBD(PrivData)->Extra != NULL) { \
                      SAVEREC old; \
                      LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                      SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                      A ; \
                      LPTBD(PrivData)->c->RestoreRecs(old);  \
                      } \
                    else { \
                      RestoreListFnc rlf (LPTBD(PrivData)->c); \
                      A ; \
                      } \
                    }
#endif
//
//  Callback - Funktionen fuer die toolbar
//
DLLExport void _export WINAPI TBFreePrivData (LPVOID PrivData)
  {
  if (LPTBD (PrivData)->Extra != NULL)
    FreeGlobMem (LPTBD (PrivData)->Extra);
  }
void DDSFreePrivData (LPVOID PrivData)
  {
  if (LPTBD (PrivData)->Extra != NULL)
    FreeGlobMem (LPTBD (PrivData)->Extra);
  }

DLLExport LPVOID _export WINAPI TBGetData (LPVOID PrivData,DWORD Id)
  {
  LPVOID res ;
  ENTER (res = LPTBD (PrivData)->c->ReadlData (Id));
  return res ;
  }

DLLExport int _export WINAPI TBGetVarSize (LPVOID PrivData,DWORD Id)
  {
  int res ;
  ENTER (res = LPTBD (PrivData)->c->GetVarSize (Id));
  return res ;
  }

DLLExport BOOL _export WINAPI TBIsUpdateFrom (LPVOID PrivData,DWORD Id)
  {
  BOOL res ;
  ENTER (res = LPTBD (PrivData)->c->IsUpdatelFromEle (Id));
  return res ;
  }

DLLExport VOID _export WINAPI TBSetData (LPVOID PrivData,DWORD Id,LPVOID Data,int size,LPVOID Cmd)
  {
  if (Data != NULL) {
    ENTER (LPTBD (PrivData)->c->WritelData (Id,Data,size,Cmd));
    }
  else
    ENTER (LPTBD (PrivData)->c->DellData (Id,Cmd));
  }

DLLExport VOID _export WINAPI TBSetConnection (LPVOID PrivData,DWORD Id,LPVOID Cmd)
  {
  ENTER (LPTBD (PrivData)->c->SetlConnection (Id,Cmd));
  }

DLLExport VOID _export WINAPI TBSetConnection_Extended (LPVOID PrivData,DWORD Id,LPVOID Cmd,WORD TableInd,LPVOID RecData)
  {
  SetExtraInfo s(LPTBD (PrivData)->c,TableInd,LPDBRECORD (RecData),0L);
  LPTBD (PrivData)->c->SetlConnection (Id,Cmd);
  }

DLLExport VOID _export WINAPI TBClearConnection (LPVOID PrivData,DWORD Id,LPVOID Cmd)
  {
  ENTER (LPTBD (PrivData)->c->ClearlConnection (Id,Cmd));
  }

DLLExport VOID _export WINAPI TBCallCommand (LPVOID PrivData,DWORD CmdOffset,LPVOID par)
  {
#ifdef DEBUG
  ENTER1DEB (
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_LOAD | EM_CHANGETOTRUE);
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_RESET);
    ) ;
#else
  ENTER1 (
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_LOAD | EM_CHANGETOTRUE);
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_RESET);
         ) ;
#endif
#ifdef DEBUG
  PopFromCallStack ();
#endif
#ifdef UEBERLEGT
  DoTBCall(LPTBD(PrivData),CmdOffset,par);
#endif
  }

extern LPDBRECORD GetRecordWithList (LPVOID list,LPDBRECORD h,mdiChild FAR *c,WORD FAR *TableInd);
DLLExport LPVOID _export WINAPI TBNextBitmap (LPVOID PrivData,DWORD List,DWORD CmdOffset,LPVOID rec)
  {
  BOOL oldBlockIsActive = BlockIsActive;
  BlockIsActive = FALSE;
  LPDBRECORD x = NULL ;
  WORD TableInd;
  ENTER1 (
    x = GetRecordWithList (LPTBD (PrivData)->c->ReadlData (List),LPDBRECORD (rec),LPTBD (PrivData)->c,&TableInd);
    if (x != NULL) {
      LPDBRECORD old = LPTBD (PrivData)->c->rr->GetRecord(TableInd);
      LPTBD (PrivData)->c->rr->SetRecord (TableInd,x);
      LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_LOAD | EM_CHANGETOTRUE);
      LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_RESET);
      LPTBD (PrivData)->c->rr->SetRecord (TableInd,old);
      }
         ) ;
  BlockIsActive = oldBlockIsActive;
  return x ;
  }

DLLExport BOOL _export WINAPI TBockIsActive (BOOL flag)
  {
  BOOL res = BlockIsActive;
  BlockIsActive = flag;
  return res;
  }

extern LPDBRECORD GetRecordWithListReverse (LPVOID list,LPDBRECORD h,mdiChild FAR *c,WORD FAR *TableInd);
DLLExport LPVOID _export WINAPI TBNextTextMerge (LPVOID PrivData,DWORD List,DWORD CmdOffset,LPVOID rec)
  {
  BOOL oldBlockIsActive = BlockIsActive;
  BlockIsActive = FALSE;
  LPDBRECORD x = NULL ;
  WORD TableInd;
  ENTER1 (
    x = GetRecordWithListReverse (LPTBD (PrivData)->c->ReadlData (List),LPDBRECORD (rec),LPTBD (PrivData)->c,&TableInd);
    if (x != NULL) {
      LPDBRECORD old = LPTBD (PrivData)->c->rr->GetRecord(TableInd);
      LPTBD (PrivData)->c->rr->SetRecord (TableInd,x);
      LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_LOAD | EM_CHANGETOTRUE);
      LPTBD (PrivData)->c->ExCuteProc (CmdOffset,EM_RESET);
      LPTBD (PrivData)->c->rr->SetRecord (TableInd,old);
      }
         ) ;
  BlockIsActive = oldBlockIsActive;
  return x ;
  }

DLLExport GLOBALHANDLE _export WINAPI TBGetResource (DWORD Id)
  {
  DWORD DataSize;
  DWORD newId = TransformResID (Id,GetSystemMetrics (SM_CXSCREEN));
  return ReadResourceData (newId,&DataSize);
  }

#define DOEXTERN_SHOWLIST         300
#define DOEXTERN_SHOWPERMLIST     567
#define DOEXTERN_SHOWSTRINGLIST   568
#define DOEXTERN_EXTDOC           596
#define DOEXTERN_EXTWIN           705
#define DOEXTERN_SHOWOBJECTLIST   32
#define DOEXTERN_SHOWMPOBJECTLIST 46
#define DOEXTERN_SHOWCOLUMNLIST   58
#define DOEXTERN_SHOWEXTSTRINGLIST   307
#define DOEXTERN_SHOWEXTCOLLIST      313
#define DOEXTERN_SHOWEXTOBJLIST      314
#define DOEXTERN_SHOWEXTMPOBJLIST    319
#define DOEXTERN_EXTBLOBDOC          804
extern DOEXTERN DoShowListptr ();
extern DOEXTERN DoShowPermListptr ();
extern DOEXTERN DoShowStringListptr ();
extern DOEXTERN DoShowColumnListptr ();
extern DOEXTERN DoShowExtChild ();
extern DOEXTERN DoShowExtBlobChild ();
extern DOEXTERN DoShowExtWindow ();
extern DOEXTERN DoShowObjectListptr ();
extern DOEXTERN DoShowMPObjectListptr ();
extern DOEXTERN DoShowExtStringListptr ();
extern DOEXTERN DoShowExtColListptr ();
extern DOEXTERN DoShowExtObjListptr ();
extern DOEXTERN DoShowExtMPObjListptr ();
DLLExport DOEXTERN _export WINAPI TBGetExtFunc (WORD FncNmbr,DOEXTERN old)
  {
  if (old != NULL) {
#ifndef WIN32
//    FreeProcInstance (FARPROC(old));   wird jetzt erst ganz zum Schluss freigegeben !
#endif
    return NULL;
    }
  else {
    switch (FncNmbr) {
      case DOEXTERN_SHOWLIST     :
        return DoShowListptr ();
      case DOEXTERN_SHOWPERMLIST :
        return DoShowPermListptr ();
      case DOEXTERN_SHOWSTRINGLIST :
        return DoShowStringListptr ();
      case DOEXTERN_SHOWCOLUMNLIST :
        return DoShowColumnListptr ();
      case DOEXTERN_SHOWOBJECTLIST :
        return DoShowObjectListptr ();
      case DOEXTERN_SHOWMPOBJECTLIST :
        return DoShowMPObjectListptr ();
      case DOEXTERN_EXTDOC :
        return DoShowExtChild ();
      case DOEXTERN_EXTBLOBDOC :
        return DoShowExtBlobChild ();
      case DOEXTERN_EXTWIN :
        return DoShowExtWindow ();
      case DOEXTERN_SHOWEXTSTRINGLIST :
        return DoShowExtStringListptr ();
      case DOEXTERN_SHOWEXTCOLLIST    :
        return DoShowExtColListptr ();
      case DOEXTERN_SHOWEXTOBJLIST    :
        return DoShowExtObjListptr ();
      case DOEXTERN_SHOWEXTMPOBJLIST  :
        return DoShowExtMPObjListptr ();
      default :
        return NULL ;
      }
    }
  }

///////////////////////////////////////////////////////////////////
//  Abfrage, ob die Tools verwendet werden sollen
///////////////////////////////////////////////////////////////////
#define TOOLSECTION "Tools"
#define DOSWITCH    "SwitchDos"
#define DOSWICTHDEF "no"

BOOL DoDosSwitch ()
  {
  char cdstr[20];
  static BOOL dosswitch;
  static BOOL dosswitchChecked;
  if (!dosswitchChecked) {
    GetPrivateProfileString (TOOLSECTION,DOSWITCH,DOSWICTHDEF,
                                cdstr,sizeof(cdstr),
                                MYINI
                             );
    if (lstrcmp (cdstr,"yes") == 0) dosswitch = TRUE ;
    else                            dosswitch = FALSE ;
    dosswitchChecked = TRUE ;
    }

  return dosswitch;
  }

///////////////////////////////////////////////////////////////////
//      Initialisieren der Toolbar - Library
///////////////////////////////////////////////////////////////////
static GETDATA         ctgd;
static SETDATA         ctsd;
static SETCONNECTION   ctsc;
static CLEARCONNECTION ctcc;
static CALLCOMMAND     ctccmd;
static GETRESOURCE     ctgs;
static GETEXTFUNC      ctgf;
static ISUPDATEFROM    ciuf;
static SETCONNECTION_EXTENDED scex;
static SETTABLECONTEXT        stc;
static GETTABLECONTEXT        gtc;
static GETVARSIZE             gtv;
static FREEPRIVDATA           fpr;
static NEXTBITMAP             nbm;
static NEXTBITMAP             ntm;
static TBFOCUSCHANGING        tbfc;
static TBACTIVE               tba;

extern DLLExport LPVOID _export WINAPI SetTableContext (LPVOID CallBackData,WORD TableInd,LPVOID recAddr);
extern DLLExport LPVOID _export WINAPI GetTableContext (LPVOID CallBackData,WORD TableInd);
extern DLLExport void _export WINAPI TBFocusChanging (DWORD old,DWORD n);

#ifndef GetDirMitCLIB
HINSTANCE swtoolsDll;
typedef int (CALLBACK *SELECTDIR) (char *pDefault, char *pResult, int resLen);

SELECTDIR lpfnSelectDir;
#endif

void cToolInit ()
  {
  ctgd   = GETDATA         (MakeProcInstance (FARPROC(TBGetData),WBase::hInstance));
  ctsd   = SETDATA         (MakeProcInstance (FARPROC(TBSetData),WBase::hInstance));
  ctsc   = SETCONNECTION   (MakeProcInstance (FARPROC(TBSetConnection),WBase::hInstance));
  ctcc   = CLEARCONNECTION (MakeProcInstance (FARPROC(TBClearConnection),WBase::hInstance));
  ctccmd = CALLCOMMAND     (MakeProcInstance (FARPROC(TBCallCommand),WBase::hInstance));
  ctgs   = GETRESOURCE     (MakeProcInstance (FARPROC(TBGetResource),WBase::hInstance));
  ctgf   = GETEXTFUNC      (MakeProcInstance (FARPROC(TBGetExtFunc),WBase::hInstance));
  ciuf   = ISUPDATEFROM    (MakeProcInstance (FARPROC(TBIsUpdateFrom),WBase::hInstance));

  Initialize (ctgd,ctsd,ctsc,ctcc,ctccmd,ctgs,ctgf,ciuf);

  scex = SETCONNECTION_EXTENDED (MakeProcInstance (FARPROC(TBSetConnection_Extended),WBase::hInstance));
  stc  = SETTABLECONTEXT        (MakeProcInstance (FARPROC(SetTableContext),WBase::hInstance));
  gtc  = GETTABLECONTEXT        (MakeProcInstance (FARPROC(GetTableContext),WBase::hInstance));
  gtv  = GETVARSIZE             (MakeProcInstance (FARPROC(TBGetVarSize),WBase::hInstance));
  fpr  = FREEPRIVDATA           (MakeProcInstance (FARPROC(TBFreePrivData),WBase::hInstance));
  nbm  = NEXTBITMAP             (MakeProcInstance (FARPROC(TBNextBitmap),WBase::hInstance));
  ntm  = NEXTBITMAP             (MakeProcInstance (FARPROC(TBNextTextMerge),WBase::hInstance));
  tbfc = TBFOCUSCHANGING        (MakeProcInstance (FARPROC(TBFocusChanging),WBase::hInstance));
  tba  = TBACTIVE               (MakeProcInstance (FARPROC(TBockIsActive),WBase::hInstance));

  Initialize_Extended (scex,stc,gtc,gtv,fpr,nbm,ntm,tbfc,tba);

  #ifndef GetDirMitCLIB
  swtoolsDll = LoadLibrary ("SWTOOLS.DLL");
  if (!swtoolsDll)
    DBWIN_ASSERT(FALSE);
  lpfnSelectDir = (SELECTDIR) GetProcAddress (swtoolsDll,"SelectDir");
  #endif
  }

void cToolExit ()
  {
#ifdef WIN32
  #ifdef GetDirMitCLIB
  FreeLibrary (swtoolsDll);
  #endif
#else
  FreeProcInstance (FARPROC(ctgd  ));
  FreeProcInstance (FARPROC(ctsd  ));
  FreeProcInstance (FARPROC(ctsc  ));
  FreeProcInstance (FARPROC(ctcc  ));
  FreeProcInstance (FARPROC(ctccmd));
  FreeProcInstance (FARPROC(ctgs  ));
  FreeProcInstance (FARPROC(ctgf  ));
  FreeProcInstance (FARPROC(ciuf  ));

  FreeProcInstance (FARPROC(scex));
  FreeProcInstance (FARPROC(stc ));
  FreeProcInstance (FARPROC(gtc ));
  FreeProcInstance (FARPROC(gtv ));
  FreeProcInstance (FARPROC(fpr ));
  FreeProcInstance (FARPROC(nbm ));
  FreeProcInstance (FARPROC(ntm ));
  FreeProcInstance (FARPROC(tbfc));
#endif
  }

/////////////////////////////////////////////////////////////////
//  Aufbau eines Screens
/////////////////////////////////////////////////////////////////
#pragma pack(1)
struct CreateScreen_param {
  WORD  parSize;
  DWORD ScreenId;
  DWORD ParentScreen;
  DWORD ScreenNmbr;
  DWORD Caption;
  DWORD PosRef;
  DWORD w,h;
  DWORD ModalScreen;
  };
#pragma pack()

static mdiChild *MainToolInst;
static BOOL IsMainControl (mdiChild *c)
  {
  return (c == MainToolInst);
  }
mdiChild FAR *GetMainToolInst ()
  {
  return MainToolInst;
  }

BOOL CreateScreen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldBlockIsActive = BlockIsActive ;
    BlockIsActive = FALSE ;
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    DBWIN_ASSERT (c->IsConst (par->ScreenNmbr));
    DBWIN_ASSERT (c->IsConst (par->ModalScreen));
    DBINT ScreenNmbr = *((DBINT FAR *) c->ReadlData (par->ScreenNmbr));
    DBINT FAR *lpw = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *lphg = (DBINT FAR *) c->ReadlData (par->h);
    DBWIN_ASSERT ((lpw != NULL) && (lphg != NULL)) ;
    int w = *lpw;
    int hg = *lphg;
    DBBOOL ModalScreen = *((DBBOOL FAR *) c->ReadlData (par->ModalScreen));
    HWND hWndDDS = (ScreenNmbr > 0) ? c->DrawContext()->GetOutData()->_MyHandle : WBase::hFrameWin ;
    // LPSCREEN FAR *scl = (LPSCREEN FAR *) 
    //      c->ReadlData (par->ParentScreen);
    LPSCREEN FAR *scl = NULL;
    HWND hWndParent = ((scl != NULL) && (*scl != NULL)) ? 
            (* scl)->hWnd : 
            hWndDDS;
    WINDOWATTRSTRUCT attr;
    attr.Title = LPSTR (c->ReadData (LOWORD(par->Caption),HIWORD(par->Caption)));
    attr.w = w;
    int x = 0;
    int y = 0;
    if (ScreenNmbr == 0) {
      MainToolInst = c;
      RECT r;
      GetClientRect (WBase::hFrameWin,&r);
      int sy = r.bottom + 1;
      attr.h = sy - PrgStat.GetHeight();
      x = 0 ;
      }
    else
      attr.h = hg;
    if (ScreenNmbr == 0) 
      attr.Style = 0;
    else {
      attr.Style = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER;
      if (attr.Title != NULL)
        attr.Style |= WS_CAPTION;
      }
    toolbar_cbdata h(c);

    if (hWndParent == 0)
      hWndParent = WBase::hFrameWin;
    HWND hToolWnd = CreateToolBar (par->ScreenId,hWndParent,
                                   int (ScreenNmbr),
                                   par->PosRef,
                                   &attr,&h,sizeof(h),
                                   x,y,
                                   ModalScreen,FALSE,
                                   par
                                  );
    BlockIsActive = oldBlockIsActive;
    }
  if (mode & EM_UPDATE) {
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadlData (par->ScreenId);
    if (llpsc == NULL)
      DBWIN_ASSERT_TEXT (FALSE, "Ungueltiger Dialogbezeichner in CreateScreen(UPDATE)");
    if (c->IsUpdatelFromEle (par->Caption)) {
      LPSTR Caption = LPSTR(c->ReadlData (par->Caption));
      DBWIN_ASSERT (Caption != NULL);
      SendMessage ((*llpsc)->hWnd,WM_SETTEXT,0,LONG(Caption));
      }

    DBINT FAR *lpw = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *lphg = (DBINT FAR *) c->ReadlData (par->h);
    DBWIN_ASSERT ((lpw != NULL) && (lphg != NULL));

    if (((*lpw != (*llpsc)->dlgWidth) || (*lphg != (*llpsc)->dlgHeight)) &&
        ((*llpsc)->ScreenNmbr != 0)) {
      int w = *lpw;
      int hg = *lphg;
      ChangeToolbarSize (*llpsc, w, hg);
      }

    // Ein Update auf die Dialogposition.
//    if (c->IsUpdatelFromEle (par->PosRef)) {
//      POPUPPOS FAR *lpPos = (POPUPPOS FAR *) c->ReadlData (par->PosRef);
//      if (lpPos != NULL)
//        ChangeToolbarPos (*llpsc, lpPos->ptPos.x, lpPos->ptPos.y);
//      }
    }
  if (mode & EM_FIXCONNECTION) {
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    c->SetlConnection (par->w,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->h,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Caption,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->PosRef,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    LPSCREEN FAR *llps = (LPSCREEN FAR *) 
          c->ReadlData (par->ScreenId);
    if ((llps != NULL) && (*llps != NULL)) {
      BOOL oldBlockIsActive = BlockIsActive ;
      BlockIsActive = FALSE ;
      DestroyToolBar (*llps);
      BlockIsActive = oldBlockIsActive ;
      }
    c->ClearlConnection (par->w,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->h,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Caption,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->PosRef,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL CreateMapScreen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    DBWIN_ASSERT (c->IsConst (par->ScreenNmbr));
    DBINT ScreenNmbr = *((DBINT FAR *) c->ReadlData (par->ScreenNmbr));
    LPCLIENTMAP FAR *llp = (LPCLIENTMAP FAR *) c->ReadlData (par->ParentScreen);
    DBWIN_ASSERT ((llp != NULL) && (*llp != NULL));
    HWND hWndParent = (*llp)->m_hWndParent;
    WINDOWATTRSTRUCT attr;
    attr.Title = "";
    attr.h = (*llp)->m_MapScreenRect.bottom - (*llp)->m_MapScreenRect.top ;
    attr.w = (*llp)->m_MapScreenRect.right - (*llp)->m_MapScreenRect.left ;
    POINT pt;
    pt.x = (*llp)->m_MapScreenRect.left;
    pt.y = (*llp)->m_MapScreenRect.top;
    attr.Style = 0;
    toolbar_cbdata h(c);
    HWND hToolWnd = CreateToolBar (par->ScreenId,hWndParent,
                                   ScreenNmbr,
                                   par->PosRef,
                                   &attr,&h,sizeof(h),
                                   pt.x,pt.y,
                                   FALSE,TRUE,
                                   par
                                  );
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CreateScreen_param FAR *par = (CreateScreen_param FAR *) param;
    LPSCREEN FAR *llps = (LPSCREEN FAR *) 
          c->ReadlData (par->ScreenId);
    if ((llps != NULL) && (*llps != NULL)) {
      BOOL oldBlockIsActive = BlockIsActive ;
      BlockIsActive = FALSE ;
      DestroyToolBar (*llps);
      BlockIsActive = oldBlockIsActive ;
      }
    }
  return FALSE ;
  }


#pragma pack(1)
struct SetMapExtent_param {
  WORD  parSize;
  DWORD x;
  DWORD y;
  DWORD w;
  DWORD h;
  };
#pragma pack()

BOOL SetMapExtent (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetMapExtent_param FAR *par = (SetMapExtent_param FAR *) param;
    
    DBINT FAR *x = (DBINT FAR *) c->ReadlData (par->x);
    DBINT FAR *y = (DBINT FAR *) c->ReadlData (par->y);
    DBINT FAR *w = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *h = (DBINT FAR *) c->ReadlData (par->h);
    DBWIN_ASSERT ((x != NULL) && (y != NULL)  && (w != NULL) && (h != NULL));
    
    SetMapExtent (*x, *y, *w, *h);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetMapExtent_param FAR *par = (SetMapExtent_param FAR *) param;
    c->ClearlConnection (par->x,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->y,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->w,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->h,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }


BOOL GenericTool (mdiChild *c,LPVOID param,WORD mode)
  {
  // Direkt an das Tool weiterleiten
  HWND FAR *lpr = (HWND FAR *) c->GetDocumentExtraData (DED_TOOLWND);
  HWND hRefWnd ;
  if (lpr == NULL)
    hRefWnd = (IsMainControl (c)) ? WBase::hFrameWin : c->OutWnd() ;
  else
    hRefWnd = *lpr ;
  if (hRefWnd == 0)
    hRefWnd = WBase::hFrameWin;
  if (mode & EM_LOAD) {
    toolbar_cbdata h(c);
    SetControl (hRefWnd, LPTOOLHEADER(LPSTR(param) - sizeof(WORD)),
                         mode,&h,sizeof(h)
               );
    }
  else {
    BOOL oldActive = BlockIsActive ; // Sicherheitshalber ausschalten,
    BlockIsActive = FALSE ;          // weil auch andere Elemente abgefragt werden
                                     // koennten
    SetControl (hRefWnd, LPTOOLHEADER(LPSTR(param) - sizeof(WORD)),
                         mode,NULL,0
               );
    BlockIsActive = TRUE ;
    }
  return FALSE ;
  }

void ActivateTool (mdiChild *c)
  {
  HWND hRefWnd;
  HWND FAR *lpr = (HWND FAR *) c->GetDocumentExtraData (DED_TOOLWND);
  if (lpr)
    hRefWnd = *lpr;
  else
    hRefWnd = (IsMainControl (c)) ? WBase::hFrameWin : c->DrawContext()->GetOutData()->_MyHandle ;
  if (hRefWnd) {
    ActivateControl (hRefWnd);
    ActivateMainToolBar (TRUE);
    }
  }

int xToolbarExt ()
  {
  if ((!IsMainExistant ()) || (IsMainPopup ())) return 0 ;
  else                                          return ToolBarWidth();
  }

//////////////////////////////////////////////////////////////////////
//  Klasse mdiControl
//////////////////////////////////////////////////////////////////////
extern LPSTR GetStartParam (LPSTR kennung);
LPSTR GetControlName(BOOL forUpdate)
  {
  LPSTR sp = GetStartParam ("Startup") ;
  if (sp) return sp;
  static char res[32];
  GetPrivateProfileString ("Startup","startprg",(forUpdate) ? "UPDATE.TXT" : "CONTROL.TXT",
        res,sizeof(res),MYINI
                          );
  return res;
  }

class mdiControl : public mdiChild {
 public :
  virtual void LoadData ()
    { 
    ExCute (EM_LOAD | EM_FIXCONNECTION);
    }
  virtual void Reset ()
    {
    ExCute (EM_RESET);
    }
  mdiControl(BOOL forUpdate) : mdiChild (GetScriptEntry(GetControlName(forUpdate)))
    {
    GetOutData()->_ObjectList = LPVOID (new FrmObjectList (this));
    }
  virtual ~mdiControl ()
    {
    delete ((FrmObjectList FAR *) GetOutData()->_ObjectList);
    }
  };

static mdiControl *cntrl;
void CreateControl (BOOL forUpdate)
  {
  cntrl = new mdiControl(forUpdate);
  cntrl->LoadData ();
  }

void DestroyControl ()
  {
  if (cntrl != NULL) {
    cntrl->Reset();
    delete cntrl;
    cntrl = NULL;
    }
  }

mdiChild *GetControl ()
  {
  return cntrl;
  }

/////////////////////////////////////////////////////////////
//  Aufrufen einer Scriptprozedur mit einem bestimmten
//  Modus vom Script aus
/////////////////////////////////////////////////////////////
#pragma pack(1)
struct CallProc_param {
  WORD parSize;
  DWORD ProcOffs;
  WORD modeRec,modeId;
  };
#pragma pack()

BOOL CallProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CallProc_param FAR *par = (CallProc_param FAR *) param;
    WORD FAR *lpcallmode = (WORD FAR *) 
          (c->ReadData (par->modeRec,par->modeId));
    WORD callmode = (lpcallmode != NULL) 
        ? (* lpcallmode) : (EM_LOAD | EM_FIXCONNECTION);
#ifdef DEBUG
    PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(param) - sizeof(WORD)));
#endif
    RestoreListFnc rlf(c);
    c->ExCuteProc(par->ProcOffs,callmode);
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  return FALSE ;
  }

#pragma pack(1)
struct CallProcOnMode_param {
  WORD  parSize;
  DWORD ProcOffs;
  DWORD mode;
  };
#pragma pack()

BOOL CallProcOnMode (mdiChild *c,LPVOID param,WORD mode)
  {
  CallProcOnMode_param FAR *par = (CallProcOnMode_param FAR *) param;
  WORD FAR *lpmode = (WORD FAR *) c->ReadlData (par->mode);
  if ((lpmode != NULL) && (mode & (*lpmode)) != 0) {
#ifdef DEBUG
    PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(param) - sizeof(WORD)));
#endif
    c->ExCuteProc(par->ProcOffs,mode);
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  return FALSE ;
  }

// Den ganzen Screen (Popupfenster) aktivieren
/////////////////////////////////////////////////
#pragma pack(1)
struct ActivateScreen_param {
  WORD parSize;
  WORD scRec,scId;
  };
#pragma pack()

BOOL ActivateScreen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ActivateScreen_param FAR *par = (ActivateScreen_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    ActivateWholeScreen (*llpsc);
    }
  return FALSE ;
  }

BOOL UpdateScreenImmediate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ActivateScreen_param FAR *par = (ActivateScreen_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    if (IsWindow((*llpsc)->hWnd))
      UpdateWindow ((*llpsc)->hWnd);
    }
  return FALSE;
  }


BOOL CheckToolHotKey (MSG *msg)
  {
  return IsHotKey (msg);
  }

#pragma pack(1)
struct SetScale_param {
  WORD parSize;
  WORD ScRec,ScId;
  };
#pragma pack()

BOOL SetScale (mdiChild *c,LPVOID param,WORD mode)
  {
  DBWIN_ASSERT (c->outContext == NULL);
  if ((mode & EM_LOAD) && (c->GetOutData()->_MyHandle)) {
    // Skalierung setzen
    SetScale_param FAR *par = (SetScale_param FAR *) param;
    float FAR *scale = (float FAR *) c->ReadData (par->ScRec,par->ScId);
    if (scale != NULL)
      c->GetOutData()->_scale = *scale;
    else {
      float v = float(1.0);
      c->WriteData (par->ScRec,par->ScId,&v,sizeof(v),LPSTR(par) - sizeof(WORD));
      c->GetOutData()->_scale = v;
      }
    DWORD scref = MAKELONG(par->ScRec,par->ScId);
    c->WriteScaleRef (scref);
    }

  if (mode & EM_UPDATE) {
    SetScale_param FAR *par = (SetScale_param FAR *) param;
    float FAR *scale = (float FAR *) c->ReadData (par->ScRec,par->ScId);
    if (fabs(c->GetOutData()->_scale - *scale) >= 1.0E-3) {
      c->GetOutData()->_scale = *scale;
      c->BestScaling ();
      c->InitializeBars (FALSE);
      c->MapChanged ();
      ((FrmObjectList FAR *) c->GetOutData()->_ObjectList)->Reformat ();
      ToBusyCursor ();
      InvalidateRect (c->GetOutData()->_MyHandle,NULL,TRUE);
      UpdateWindow (c->GetOutData()->_MyHandle);
      SetFocus (c->GetOutData()->_MyHandle);
      c->SizeChanged ();
#ifdef UEBERLEGT
      if ((c->schd->Type == CHWND_TRACING) || (c->schd->Type == CHWND_VTO))
        ((Tracing *) c)->scale_set = TRUE ;
#endif
      }
    }

  if (mode & EM_FIXCONNECTION) {
    SetScale_param FAR *par = (SetScale_param FAR *) param;
    c->SetConnection (par->ScRec,par->ScId,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetScale_param FAR *par = (SetScale_param FAR *) param;
    c->ClearConnection (par->ScRec,par->ScId,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL StoreData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    c->Store ();
    }
  return FALSE;
  }

#pragma pack(1)
struct SetDocSide_param {
  WORD parSize;
  DWORD Side;
  WORD AnzSideRec,AnzSideId;
  };
#pragma pack()

typedef SetDocSide_param FAR *LPSDSPAR;

BOOL SetDocSide (mdiChild *c,LPVOID param,WORD mode)
  {
  DBWIN_ASSERT (c->outContext == NULL);
  if ((mode & EM_LOAD) && (c->GetOutData()->_MyHandle)) {
    SetDocSide_param FAR *par = (SetDocSide_param FAR *) param;
    DBINT FAR *lpside = (DBINT FAR *) (c->ReadlData (par->Side));
    DBINT FAR *lpanz = (DBINT FAR *) (c->ReadData (par->AnzSideRec,par->AnzSideId));
    DBWIN_ASSERT (lpanz != NULL);
    if (lpside != NULL)
      c->GetOutData()->_ActSide = min (*lpanz-1,max(0,*lpside));
    else {
      DBINT side = 0;
      c->WritelData (par->Side,&side,sizeof(side),LPSTR(param)-sizeof(WORD));
      c->GetOutData()->_ActSide = 0;
      }
    c->PutDocumentExtraData (DED_DOCSIDEPAR,&par->Side,sizeof(par->Side));
    c->PutDocumentExtraData (DED_SETDOCSIDEPAR,&par,sizeof(par));
    DWORD AnzSideRef = MAKELONG(par->AnzSideRec,par->AnzSideId);
    c->PutDocumentExtraData (DED_ANZAHLSEITENINDEX,&AnzSideRef,sizeof(AnzSideRef));
    }
  if (mode & EM_FIXCONNECTION) {
    SetDocSide_param FAR *par = (SetDocSide_param FAR *) param;
    c->SetConnection (par->AnzSideRec,par->AnzSideId,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Side,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_UPDATE) {
    SetDocSide_param FAR *par = (SetDocSide_param FAR *) param;
    DBINT FAR *nwSide = (DBINT FAR *) (c->ReadlData (par->Side));
    DBINT FAR *nwAnz = (DBINT FAR *) (c->ReadData (par->AnzSideRec,par->AnzSideId));
    int rSide = (nwSide != NULL) ? *nwSide : 0 ;
    int rAnz = (nwAnz != NULL) ? *nwAnz : 1 ;
    int iSide = min (rAnz-1,max(0,rSide));
    if (iSide != c->GetOutData()->_ActSide) {
      ((FrmObjectList FAR *) c->GetOutData()->_ObjectList)->OnKillFocus ();
      c->GetOutData()->_ActSide = iSide;
      c->GetMinMax ();
      c->InitializeBars (FALSE);
      c->MapChanged ();
      InvalidateRect (c->GetOutData()->_MyHandle,NULL,TRUE);
      ((FrmObjectList FAR *) c->GetOutData()->_ObjectList)->OnSetFocus (TRUE);
      SetFocus (c->GetOutData()->_MyHandle);
      }
//    if (iSide != rSide) {
//      c->WritelData (par->Side,&iSide,sizeof(iSide),LPSTR(param)-sizeof(WORD));
//      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetDocSide_param FAR *par = (SetDocSide_param FAR *) param;
    c->ClearConnection (par->AnzSideRec,par->AnzSideId,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Side,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

void mdiChild::ChangeDocSide (int dside)
  {
  LPSDSPAR FAR *lppar = (LPSDSPAR FAR *) GetDocumentExtraData (DED_SETDOCSIDEPAR);
  if (lppar != NULL) {
    LPSDSPAR par = *lppar;
    DBINT FAR *aSide = (DBINT FAR *) (ReadlData (par->Side));
    DBINT FAR *Anz = (DBINT FAR *) (ReadData (par->AnzSideRec,par->AnzSideId));
    DBWIN_ASSERT ((aSide != NULL) && (Anz != NULL));
    if ((*aSide + dside >= 0) && (*aSide + dside < *Anz)) {
      DBINT nSide = *aSide + dside;
      WritelData (par->Side,&nSide,sizeof(nSide),NULL);
      }
    }
  }

#pragma pack(1)
struct FAR SetDocBestSize_param {
  WORD parSize;
  DWORD x0,y0,x1,y1;
  };
#pragma pack()

BOOL SetDocBestSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDocBestSize_param FAR *par = (SetDocBestSize_param FAR *) param;
    if (c->DrawContext()->schd->Type == CHWND_FORM) {
      if (par->parSize >= sizeof(*par)) {
        DBINT FAR *x0 = (DBINT FAR *) c->ReadlData (par->x0);
        DBINT FAR *y0 = (DBINT FAR *) c->ReadlData (par->y0);
        DBINT FAR *x1 = (DBINT FAR *) c->ReadlData (par->x1);
        DBINT FAR *y1 = (DBINT FAR *) c->ReadlData (par->y1);
        DBWIN_ASSERT ((x0 != NULL) && (y0 != NULL) && (x1 != NULL) && (y1 != NULL));
        ((Form *) c->DrawContext())->GetBestSize (*x0,*y0,*x1,*y1);
        }
      else
        ((Form *) c->DrawContext())->GetBestSize ();
      }
#ifdef UEBERLEGT
    else if ((c->DrawContext()->schd->Type == CHWND_TRACING) || (c->schd->Type == CHWND_VTO))
      ((Tracing *) c->DrawContext())->RecalcScale ();
#endif

    DWORD FAR *scref = c->DrawContext()->GetScaleRef();
    if (scref != NULL)
      c->DrawContext()->WritelData (*scref,&c->DrawContext()->GetOutData()->_scale,sizeof(c->DrawContext()->GetOutData()->_scale),NULL);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetDocBestSize_param FAR *par = (SetDocBestSize_param FAR *) param;
    if (par->parSize >= sizeof(*par)) {
      c->ClearlConnection (par->x0,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->y0,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->x1,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->y1,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

BOOL SetDocVeryBestSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DBWIN_ASSERT (c->DrawContext()->schd->Type == CHWND_FORM);
    ((Form *) c->DrawContext())->GetVeryBestSize ();
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetDocVeryBestWith_param {
  WORD parSize;
  DWORD mode;
  };
#pragma pack()

BOOL SetDocVeryBestWith (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DBWIN_ASSERT (c->DrawContext()->schd->Type == CHWND_FORM);
    struct SetDocVeryBestWith_param FAR *par = (SetDocVeryBestWith_param FAR *) param;
    int mode;
    if (par->parSize >= sizeof(*par)) {
      DBINT FAR *lpm = (DBINT FAR *) c->ReadlData (par->mode);
      if ((lpm != NULL) && (*lpm))
        mode = -1;
      }
    else
      mode = TRUE ;
    ((Form *) c->DrawContext())->GetVeryBestWidth (mode);
    }
  return FALSE ;
  }

BOOL SetDocBestWidth (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    if (c->DrawContext()->schd->Type == CHWND_FORM)
      ((Form *) c->DrawContext())->GetBestWidth ();
#ifdef UEBERLEGT
    else if ((c->DrawContext()->schd->Type == CHWND_TRACING) || (c->schd->Type == CHWND_VTO))
      ((Tracing *) c->DrawContext())->RecalcScale ();
#endif

    DWORD FAR *scref = c->DrawContext()->GetScaleRef();
    if (scref != NULL)
      c->DrawContext()->WritelData (*scref,&c->DrawContext()->GetOutData()->_scale,sizeof(c->DrawContext()->GetOutData()->_scale),NULL);
    }
  return FALSE ;
  }

BOOL TileDocuments (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SendMessage(WBase::hClient, WM_MDITILE, 0, 0L);

    LRESULT h = SendMessage (WBase::hClient,WM_MDIGETACTIVE,NULL,NULL);
#ifdef WIN32
    HWND hWnd = HWND(h);
#else
    HWND hWnd = LOWORD(h);
#endif
    if (IsWindow (hWnd)) 
      SetFocus (hWnd);
    }
  return FALSE ;
  }

BOOL ArrangeDocuments (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SendMessage(WBase::hClient, WM_MDICASCADE, 0, 0L);

    LRESULT h = SendMessage (WBase::hClient,WM_MDIGETACTIVE,NULL,NULL);
#ifdef WIN32
    HWND hWnd = HWND(h);
#else
    HWND hWnd = LOWORD(h);
#endif
    if (IsWindow (hWnd)) 
      SetFocus (hWnd);
    }
  return FALSE ;
  }

BOOL SwitchToNextWindow (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldBlockIsActive = BlockIsActive ;
    BlockIsActive = FALSE  ;
    DBWIN_ASSERT (c->outContext == NULL);
    SendMessage (WBase::hClient,WM_MDINEXT,WPARAM(c->GetOutData()->_MyHandle),LPARAM(FALSE));
    BlockIsActive = oldBlockIsActive ;
    }
  return FALSE ;
  }

BOOL SwitchToPrevWindow (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldBlockIsActive = BlockIsActive ;
    BlockIsActive = FALSE  ;
    DBWIN_ASSERT (c->outContext == NULL);
    SendMessage (WBase::hClient,WM_MDINEXT,WPARAM(c->GetOutData()->_MyHandle),LPARAM(TRUE));
    BlockIsActive = oldBlockIsActive ;
    }
  return FALSE ;
  }

extern void EmptyUpdateList ();
BOOL CheckandDestroy()
  {
  HWND hwChild;
  BOOL res = TRUE ;
  ShowWindow(WBase::hClient, SW_HIDE);
  hwChild = GetWindow(WBase::hClient, GW_CHILD);
  mdiChild *pmdich;
  while(hwChild) {
    while(hwChild && GetWindow(hwChild,GW_OWNER))
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);

    if(hwChild) {
      pmdich = GetWindowInst(hwChild);
      if (pmdich->CheckDocExit (FALSE)) {
        PostMessage (hwChild,WM_SYSCOMMAND,SC_CLOSE,0L);
        }
      else {
        res = FALSE ;
        break ;
        }
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);
      }
    else break;
    }
  ShowWindow(WBase::hClient, SW_NORMAL);
  if (!res) {
    ToBusyCursor ();
    SendMessage (WBase::hClient,WM_MDIACTIVATE,WPARAM(hwChild),0L);
    // Jetzt kann auch die Frage gestellt werden...
    EmptyUpdateList ();
    pmdich->CheckDocExit (TRUE) ;
    }
  return res ;
  }

BOOL DestroyAllDocuments (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & EM_LOAD)
    res = CheckandDestroy();
  return res ;
  }

/////////////////////////////////////////////////////////
//  Initialisieren eines Hotkeys
/////////////////////////////////////////////////////////
BOOL InitHk (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    toolbar_cbdata h(c);
    InitHotKey (&h,(HotKeyStruct FAR*) (LPSTR (param) - sizeof(WORD)),mode);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

BOOL SwitchToNextField (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldBlockIsActive = BlockIsActive ;
    BlockIsActive = FALSE  ;
    c->NextField ();
    BlockIsActive = oldBlockIsActive ;
    }
  return FALSE ;
  }

BOOL SwitchToPrevField (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldBlockIsActive = BlockIsActive ;
    BlockIsActive = FALSE  ;
    c->PrevField ();
    BlockIsActive = oldBlockIsActive ;
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////////
//  Anzeigen einer Liste
////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR ShowToolList_param {
  WORD parSize;
  DWORD edObj;
  DWORD res;
  DWORD String;
  DWORD Width;
  DWORD Height;
  DWORD OkProc;
  BOOL CallOnOk ()
    { return (parSize >= sizeof (*this)) ; }
  };
#pragma pack()

inline char doUpper (char ch)
  {
#ifdef WIN32
  char chtmp[2];
  chtmp[0] = ch;
  chtmp[1] = '\0';

  return (char) (DWORD) CharUpper (chtmp);
#else
  return (char) (DWORD) AnsiUpper (LPSTR (MAKELP (0,ch)));
#endif
  }
int CheckOneSel (LPSTR Buffer,LPSTR txt)
  {
  cField FAR *field = new cField (TRANSPARENT,0,0,0,-1,-1,FALSE);
        // Nur fuer das SkipFormat !?!
  char ch = doUpper (*txt);
  int res = -1 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  Buffer = field->SkipFormat(Buffer);
  for ( ; *Buffer ; ) {
    if (ch == doUpper (*Buffer)) {
      if (res >= 0) return -1 ;       // nicht eindeutig
      res = i ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    Buffer = field->SkipFormat(Buffer);
    i++ ;
    }
  return res ;
  }

int CheckBestSel (LPSTR Buffer,LPSTR txt)
  {
  cField FAR *field = new cField (TRANSPARENT,0,0,0,-1,-1,FALSE);
        // Nur fuer das SkipFormat !?!
  char ch = doUpper (*txt);
  int res = 0 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  Buffer = field->SkipFormat(Buffer);
  int olddiff = 10000;
  for ( ; *Buffer ; ) {
    int diff = int (ch) - (int) doUpper (*Buffer);
    if ((diff >= 0) && (diff < olddiff)) {
      res = i ;
      if (diff == 0) break ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    Buffer = field->SkipFormat(Buffer);
    i++ ;
    }
  return res ;
  }

void ShowToolList_base (mdiChild *c,HWND hParent,LPRECT rcFieldInParent,LPVOID param,WORD mode,char lastPressedChar)
  {
  // Lesen aller Daten
  ShowToolList_param FAR *par = (ShowToolList_param FAR *) param;
  LPSTR txt = LPSTR(c->ReadlData (par->String));
  DBINT FAR *ind = (DBINT FAR *) c->ReadlData (par->res);
  if (txt != NULL) {
    char str[2] ;
    str[0] = lastPressedChar;
    str[1] = '\0';
    int ActInd = CheckOneSel (txt,str);
    DBINT dbres ;
    BOOL doIt = FALSE;
    if (ActInd < 0) {
      // Nicht direkt gefunden > Liste aufmachen
      int Ind ;
      if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
        // Suchen in der Liste
        Ind = CheckBestSel (txt,str);
      else
        // Aktuellen Index verwenden
        Ind = (ind != NULL) ? *ind : 0 ;
    
      // Berechnen Edit - Koordinaten
      SinglList s(txt,Ind) ;
      RECT cr, rcField = *rcFieldInParent;

      DBINT FAR *lpw = NULL;
      DBINT FAR *lph = NULL;
      if (par->parSize > (sizeof(WORD) + 3*sizeof(DWORD))) {
        lpw = (DBINT FAR *) c->ReadlData (par->Width);
        lph = (DBINT FAR *) c->ReadlData (par->Height);
        }
      int w = (lpw != NULL) ? *lpw : 0;
      int h = (lph != NULL) ? *lph : 0;

      double dbu;
      GetBaseUnit (&dbu);
      w = int (double(w) * dbu);
      h = int (double(h) * dbu);

      GetWindowRect (hParent,&cr);        // Screen-Koordinaten verwenden !!
    
      if (s.WorkOn (hParent, LPRECT(&rcField), &cr, w, h)) {
        dbres = DBINT(s.res);
        doIt = TRUE ;
        }
      }
    else {
      dbres = DBINT (ActInd);
      doIt = TRUE ;
      }

    if (doIt) {
      c->WritelData (par->res,&dbres,sizeof(dbres),LPSTR(param)-sizeof(WORD));
      if (par->CallOnOk ()) {
#ifdef DEBUG
        PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(param) - sizeof(WORD)));
#endif
        c->ExCuteProc (par->OkProc,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (par->OkProc,EM_RESET | EM_CLEAR);
#ifdef DEBUG
        PopFromCallStack ();
#endif
        }
      }
    }
  else
    MessageBeep (0);
  }
typedef ToolEdit FAR *LPTOOLEDIT;
BOOL ShowToolList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ShowToolList_param FAR *par = (ShowToolList_param FAR *) param;
    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->edObj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    HWND hParent = GetParent ((*e)->hWndEdit);
    RECT rcField;

    GetWindowRect ((*e)->hWndEdit, &rcField);    // Screen-Koordinaten verwenden!!
//    CopyRect (&rcField, LPRECT (&(*e)->ToolRect));
    ShowToolList_base (c,hParent,&rcField,param,mode,char (GetLastPressedChar ()));
    }

  return FALSE ;
  }

BOOL ShowFormList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ShowToolList_param FAR *par = (ShowToolList_param FAR *) param;
    LPFRMFIELD FAR *e = (LPFRMFIELD FAR *) c->ReadlData (par->edObj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    HWND hParent = c->OutWnd ();
    RECT rcField;
    PaintContext pc;
    GetDocumentContext (&pc,c);
    LPRECT logr = (*e)->GetLogRect (c->actSide());
    WIN_ASSERT (logr != NULL);
    pc.LogRecttoPhys (&rcField,logr);
    ShowToolList_base (c,hParent,&rcField,param,mode,char(GetLastFormPressedChar()));

    SetFocus (hParent);
    }

  return FALSE ;
  }

#pragma pack(1)
struct FAR GetTextFrom_param {
  WORD parSize;
  DWORD res;
  DWORD str;
  DWORD ind;
  DWORD checkindexist;

  BOOL IndMustExist ()
    { return ((parSize >= sizeof(GetTextFrom_param)) && (checkindexist)) ; }
  };
#pragma pack()

BOOL GetTextFrom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetTextFrom_param FAR *par = (GetTextFrom_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    DBINT FAR *lpind = (DBINT FAR *) c->ReadlData (par->ind);
    int i = 0;
    BOOL found = FALSE ;
    int ind;
    if (par->IndMustExist ())
      ind = (lpind != NULL) ? *lpind : -1;
    else {
      ind = (lpind != NULL) ? *lpind : 0;
      if (lpind == NULL)
        c->WritelData (par->ind,&ind,sizeof(DBINT),LPSTR(param)-sizeof(WORD),FALSE);
      }

    LPSTR end = str + GetBlockSize (str);
    if ((str != NULL) && (GetBlockSize(str) > 2)) {
      for ( LPSTR h = str ; h < end ; ) {
        if (i++ == ind) {
          c->WritelData (par->res,h,lstrlen(h)+1,
                          LPSTR(param)-sizeof(WORD));
          found = TRUE ;
          break ;
          }
        h += lstrlen (h) + 1;
        if (*h == '\0') break ;
        }
      }
    if (!found)
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetTextFrom_param FAR *par = (GetTextFrom_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->ind,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetTextFrom_param FAR *par = (GetTextFrom_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ind,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////
//  Drucken eines Dokumentes
////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR PrintDocument_param {
  WORD parSize;
  DWORD FirstPage;
  DWORD LastPage;
  DWORD DriverName;
  DWORD doPortrait;
  DWORD doLandscape;
  DWORD xLeft,yTop,xRight,yBottom;
  DWORD AutoScale;
  DWORD Scale;
  DWORD headText;
  DWORD bottomText;
  DWORD MetaFile;
  DWORD xMetaOffs;
  DWORD yMetaOffs;
  DWORD Metascalex;
  DWORD Metascaley;
  };
#pragma pack()

int Rand (mdiChild *c,DWORD id)
  { 
  float FAR *r = (float FAR *) c->ReadlData (id) ; 
  if (r != NULL) return int (*r * 25.0) ;
  else           return 0 ;
  }

inline mdiChild *GetOutContext(mdiChild *c)
  {
  return (c->outContext != NULL) ? c->outContext : c ; 
  }

void PrintHead (PaintContext *pc,int x,int y,int w,int FAR *height,mdiChild *c,DWORD rtxt)
  {
  *height = 0;
  LPSTR txt = LPSTR (c->ReadlData (rtxt));
  if (txt != NULL) {
    GLOBALHANDLE hGPar = GlobalAlloc (GHND,sizeof(ParData));
    ParData FAR *pd = (ParData FAR *) GlobalLock (hGPar);
    pd->hBaseInst = pd->hExtInst = GetOutContext(c);
    GlobalUnlock (hGPar);

    GLOBALHANDLE hGtxt = ConvertText (txt,hGPar);
    GlobalFree (hGPar);
    LPSTR ntxt = LPSTR(GlobalLock (hGtxt));
    pc->LogicalTwips (x,y);
    int width = pc->XPHYStoLOG (w);
    HWND hWnd = (c->OutWnd() != 0) ? c->OutWnd() : WBase::hFrameWin ;
    cField *f = new cField (TRANSPARENT,2,0,0,width,-1,FALSE);
    f->SetWindow (hWnd);
    f->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    f->SetVOrg (x,y,0);
    *f = ntxt ;

    f->Reformat ();
    RECT rb;
    f->GetFieldRect (&rb,0);

    f->Paint (pc->hDC,0,TRUE);

    GlobalUnlock (hGtxt);
    GlobalFree (hGtxt);

    *height = pc->YLOGtoPHYS (rb.bottom);
    }
  }

void PrintTail (PaintContext *pc,int x,int y,int w,int FAR *height,mdiChild *c,DWORD rtxt)
  {
  *height = 0;
  LPSTR txt = LPSTR (c->ReadlData (rtxt));
  if (txt != NULL) {
    GLOBALHANDLE hGPar = GlobalAlloc (GHND,sizeof(ParData));
    ParData FAR *pd = (ParData FAR *) GlobalLock (hGPar);
    pd->hBaseInst = pd->hExtInst = GetOutContext(c);
    GlobalUnlock (hGPar);

    GLOBALHANDLE hGtxt = ConvertText (txt,hGPar);
    GlobalFree (hGPar);
    LPSTR ntxt = LPSTR(GlobalLock (hGtxt));
    pc->LogicalTwips (x,y);
    int width = pc->XPHYStoLOG (w);
    HWND hWnd = (c->OutWnd() != 0) ? c->OutWnd() : WBase::hFrameWin ;
    cField *f = new cField (TRANSPARENT,2,0,0,width,-1,FALSE);
    f->SetWindow (hWnd);
    f->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    f->SetVOrg (x,y,0);
    *f = ntxt ;

    f->Reformat ();
    RECT rb;
    f->GetFieldRect (&rb,0);
    POINT pt;
    pt.x = 0;
    pt.y = -rb.bottom;
    *f = pt;
    f->Paint (pc->hDC,0,TRUE);

    GlobalUnlock (hGtxt);
    GlobalFree (hGtxt);

    *height = pc->YLOGtoPHYS (rb.bottom);
    }
  }

HMETAFILE MyGetMetaFile (LPSTR fname)
  {
  OFSTRUCT Of;
  int mfile = OpenFile (fname,&Of,OF_READ) ;
  HMETAFILE res = 0;
  if (mfile >= 0) {
#define MAXSIZE 0x0000FFFF
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND,MAXSIZE);
    char FAR *source = LPSTR(GlobalLock (hGtmp));
    WORD Size = _lread (mfile,source,MAXSIZE);
    _lclose (mfile);
    // Test, ob Metafile wohl nicht corrupt ist
    METAHEADER FAR *hd = (METAHEADER FAR *) source ;
    if (hd -> mtHeaderSize != sizeof (METAHEADER) / 2) {
      // Probieren, 22 Byte hinter dem Beginn
      hd = (METAHEADER FAR *) (source + 22) ;                // !!! ??? !!!
      if (hd->mtHeaderSize != sizeof (METAHEADER) / 2) {
        hd = NULL ;
        GlobalUnlock (hGtmp);
        GlobalFree (hGtmp);
        hGtmp = 0 ;
        }
      else {
        Size -= 22 ;
        // Neuen Buffer anlegen, Kopieren ohne die 22 Byte
        GLOBALHANDLE hGtmp1 = GlobalAlloc (GHND,Size);
        source = LPSTR(GlobalLock (hGtmp1));
        lmemcpy (source,hd,Size);
        GlobalUnlock (hGtmp1);
        GlobalUnlock (hGtmp);
        GlobalFree (hGtmp);
        hGtmp = hGtmp1 ;        // In hGtmp wieder das Resultat
        }
      }
    else {
      // Realloc machen
      GlobalUnlock (hGtmp);
      hGtmp = GlobalReAlloc (hGtmp,Size,GMEM_MOVEABLE);
      }
    if (hGtmp) {

#ifdef WIN32
      res = SetMetaFileBitsEx (Size, LPBYTE(hGtmp));
#else
      res = SetMetaFileBits (hGtmp);
#endif

      }
    }
  return res;
  }

// Hilfsfunktionen fuer Windows DIBs:
inline LONG MyByteWidth (LONG w, WORD BitCount)
  { return (((w * (DWORD)BitCount) + 31) & ~31) >> 3; }

static WORD MyDibNumColors (VOID FAR *pv)
  {
    int                   Bits;
    LPBITMAPINFOHEADER    lpbi;
    LPBITMAPCOREHEADER    lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*    With the BITMAPINFO format headers, the size of the palette
     *    is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *    is dependent on the bits per pixel ( = 2 raised to the power of
     *    bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        Bits = lpbi->biBitCount;
    }
    else Bits = lpbc->bcBitCount;

    switch (Bits){
        case 1:
        return 2;

        case 4:
        return 16;

        case 8:
        return 256;

        default:
        // A 24 bitcount DIB has no color table
        return 0;
    }
  }

void PrintImage(LPSTR fname,HDC hDC,float dx,float dy,float scalex,float scaley)
  {
  GLOBALHANDLE hDIB = ImportImage(fname);
  if (hDIB != NULL) {
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
    lpbi->biSizeImage = MyByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
    DWORD dwColorTableSize = (DWORD)(MyDibNumColors(lpbi) * sizeof(RGBQUAD));
    LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
    // Berechnen der Ausdehnung des Images (inkl. beruecksichtigung des
    // Vergroesserungsfaktors)
    RECT LogRect;
    LogRect.top = LogRect.left = 0 ;
    LONG XPelsPerMeter = lpbi->biXPelsPerMeter;
    LONG YPelsPerMeter = lpbi->biYPelsPerMeter;
    if (XPelsPerMeter == 0L) {
      if (YPelsPerMeter == 0L)
        XPelsPerMeter = LONG(double (lpbi->biWidth) * 3936.0 / 700.0);
      else
        XPelsPerMeter = YPelsPerMeter;
      }
    LogRect.right =
                  int (double (lpbi->biWidth) * (25000.0 * scalex)
                          / double (XPelsPerMeter));
    if (YPelsPerMeter == 0L)
      YPelsPerMeter = XPelsPerMeter;
    LogRect.bottom = -
                  int (double (lpbi->biHeight) * (25000.0 * scaley)
                          / double (YPelsPerMeter));
    LogRect.left   += int(dx * 25.0);
    LogRect.right  += int(dx * 25.0);
    LogRect.top    += int(dy * -25.0);
    LogRect.bottom += int(dy * -25.0);
    SetStretchBltMode (hDC,STRETCH_DELETESCANS);
    int width  = LogRect.right - LogRect.left + 1;
    int height = LogRect.bottom - LogRect.top;
    if (height < 0) height -= 1 ;
    else            height += 1 ;
    StretchDIBits (hDC,LogRect.left,LogRect.top,width,height,
                  0,0,int(lpbi->biWidth),int(lpbi->biHeight),
                  lpBits,(LPBITMAPINFO)lpbi,DIB_RGB_COLORS,SRCCOPY);
    GlobalUnlock(hDIB);
    GlobalFree(hDIB);
    }
  }

void PrintMeta (PaintContext *pc,int x,int y,int w,mdiChild *c,PrintDocument_param FAR *par)
  {
  if (par->parSize >= sizeof(*par)) {
    float FAR *dx = (float FAR *) c->ReadlData (par->xMetaOffs);
    float FAR *dy = (float FAR *) c->ReadlData (par->yMetaOffs);
    float FAR *scalex = (float FAR *) c->ReadlData (par->Metascalex);
    float FAR *scaley = (float FAR *) c->ReadlData (par->Metascaley);
    LPSTR fname = LPSTR(c->ReadlData (par->MetaFile));
    if ((fname != NULL) && (dx != NULL) && (dy != NULL) && 
        (scalex != NULL) && (scaley != NULL)) {
      // Moeglicherweise kann da was gemacht werden
      pc->Map (1.0,0,0,x,y);
      char extension[5];
      lstrcpy(extension,fname+(lstrlen(fname)-4));
      AnsiUpperBuff(extension,4);
      if (lstrcmp(extension,".WMF")) {
        PrintImage(fname,pc->hDC,*dx,*dy,*scalex,*scaley);
        }
      else {
        HMETAFILE hmf = MyGetMetaFile (fname);
        RECT r;
        pc->GetMaxInfo (hmf,&r);
        tr2 sct;
        sct.B[0] = *dx * float(25.0) - float(r.left) * *scalex ;
        sct.B[1] = - *dy * float(25.0) - float(r.top) * *scaley ;
        sct.A[0][0] = *scalex;
        sct.A[1][1] = *scaley;
        sct.A[0][1] = 
        sct.A[1][0] = float (0.0);
        pc->ScaledMetaOut (hmf, &sct, 0, pc->actdiPen, 0);

        if (hmf != NULL)
          DeleteMetaFile (hmf);
        }
      }
    }
  }

extern BOOL InClientTransaction;
extern BOOL CallCommandInClientTransaction;
void deleteAllOpenChilds ();
static LPSTR PrinterCaption;
LPSTR GetPrinterHeader ()
  {
  if (PrinterCaption) return PrinterCaption ;
  else                return "CLINICWARE: Druck" ;
  }
void SetPrinterHeader (LPSTR Caption)
  {
  if (PrinterCaption) FreeGlobMem (PrinterCaption);
  PrinterCaption = LPSTR (GetGlobMem (lstrlen (Caption) + 1));
  lstrcpy (PrinterCaption,Caption);
  }
void FreePrinterCaption ()
  {
  if (PrinterCaption != NULL) FreeGlobMem (PrinterCaption);
  }

BOOL PrintDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PrintDocument_param FAR *par = (PrintDocument_param FAR *) param;
    DBWIN_ASSERT (par->parSize >= sizeof(*par));

    GetOutContext(c)->GetOutData()->IsPrinting = TRUE ;

    // Ermitteln des Druckers
    if (GetOutContext(c)->GetOutData()->Pr == NULL)
      GetOutContext(c)->GetOutData()->Pr = GetPrinter (TRUE);
    GetOutContext(c)->GetOutData()->Pr->PrinterDC(TRUE);          // Jetzt wirds ernst
    if (!GetOutContext(c)->GetOutData()->Pr->StartPrint(GetPrinterHeader())) {
      GetOutContext(c)->GetOutData()->Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben
      GetOutContext(c)->GetOutData()->IsPrinting = FALSE ;
      return FALSE ;
      }

    int x0old = GetOutContext(c)->GetOutData()->_x0 ; int y0old = GetOutContext(c)->GetOutData()->_y0 ;
    GetOutContext(c)->GetOutData()->xpold = GetOutContext(c)->GetOutData()->_xp ; GetOutContext(c)->GetOutData()->ypold = GetOutContext(c)->GetOutData()->_yp ;
    GetOutContext(c)->GetOutData()->oldscale = GetOutContext(c)->GetOutData()->_scale ;

    DBINT FAR *FirstPage = (DBINT FAR *) c->ReadlData (par->FirstPage);
    DBINT FAR *LastPage  = (DBINT FAR *) c->ReadlData (par->LastPage);
    int oldsides = GetOutContext(c)->GetOutData()->_AnzSides ;
    int oldact   = GetOutContext(c)->GetOutData()->_ActSide ;
    DBWIN_ASSERT ((FirstPage != NULL) && (LastPage != NULL));
    GetOutContext(c)->GetOutData()->_AnzSides = max(c->GetOutData()->_AnzSides,*LastPage);
    int side = GetOutContext(c)->GetOutData()->_ActSide = *FirstPage;

    DBINT FAR *lpas = (DBBOOL FAR *) c->ReadlData(par->AutoScale);
    BOOL autoscale = (lpas != NULL) ? ((*lpas) & 0x0001) : TRUE ;
    BOOL doNewFrame;
    if (lpas != NULL) {
      if ((*lpas) & 0x0002) doNewFrame = FALSE;
      else                  doNewFrame = TRUE;
      }
    else
      doNewFrame = TRUE;
    float FAR *lpsc = (float FAR *) c->ReadlData (par->Scale);
    double sc = (lpsc != NULL) ? *lpsc : 1.0 ;
    sc = min(4.0,max(0.25,sc));
    // Ermitteln des Druckbereiches
    RECT rp,rpold;
    GetOutContext(c)->GetOutData()->Pr->PaperSize (&rp);
    CopyRect (&rpold,&rp);
    {
    PaintContext pc(GetOutContext(c)->GetOutData()->Pr);
    pc.Map (1.0);
    rp.left  += pc.XLOGtoPHYS(Rand(c,par->xLeft));
    rp.top   -= pc.YLOGtoPHYS(Rand(c,par->yTop));
    rp.right -= pc.XLOGtoPHYS(Rand(c,par->xRight));
    rp.bottom += pc.YLOGtoPHYS(Rand(c,par->yBottom));
    }

    // Und los gehts
    for ( ; ; ) {
      if (doNewFrame)
        GetOutContext(c)->GetOutData()->Pr->StartFrame ();

      // Drucken Aller Seiten
      int hdheight,theight;
      GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rp);

      PaintContext pc(GetOutContext(c)->GetOutData()->Pr);

      int s = side + 1;
      GetOutContext(c)->PutDocumentExtraData (DED_PRSIDE,&s,sizeof(s));
      GetOutContext(c)->PutDocumentExtraData (DED_PRANZSIDE,LastPage,sizeof(*LastPage));
      PrintMeta   (&pc,rp.left,rp.top,rp.right - rp.left + 1,c,par);
      PrintHead   (&pc,rp.left,rp.top,rp.right - rp.left + 1,&hdheight,c,par->headText);
      PrintTail   (&pc,rp.left,rp.bottom,rp.right - rp.left + 1,&theight,c,par->bottomText);
      GetOutContext(c)->RemoveDocumentExtraData (DED_PRSIDE);
      GetOutContext(c)->RemoveDocumentExtraData (DED_PRANZSIDE);

      RECT rd;
      CopyRect (&rd,&rp);
      rd.top    += hdheight;
      rd.bottom -= theight;
      GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rd);

      HRGN hRgnClip = CreateRectRgn (rd.left,rd.top,rd.right,rd.bottom);
      SelectClipRgn (pc.hDC,hRgnClip);
      DeleteObject (hRgnClip);

      GetOutContext(c)->SetPrintSideOpt (autoscale,sc);
      GetOutContext(c)->GetOutData()->_ActSide = s;
      GetOutContext(c)->ToPrinter (GetOutContext(c)->GetOutData()->Pr,TRUE,side);

      SelectClipRgn (pc.hDC,NULL);  // Clipping wieder aufheben

      GetOutContext(c)->GetOutData()->Pr->NewFrame ();
      if (side >= *LastPage - 1)
        GetOutContext(c)->GetOutData()->_AnzSides = 0 ;  // IsSidePrinted muss auf jeden Fall FALSE liefern
      if (GetOutContext(c)->IsSidePrinted()) break ;
      else                                   side++;
      }

    GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rpold);
    GetOutContext(c)->GetOutData()->_AnzSides = oldsides;
    GetOutContext(c)->GetOutData()->_ActSide = oldact;
    GetOutContext(c)->GetOutData()->_xp = GetOutContext(c)->GetOutData()->xpold ; GetOutContext(c)->GetOutData()->_yp = GetOutContext (c)->GetOutData()->ypold ;
    GetOutContext(c)->GetOutData()->_x0 = x0old ; GetOutContext(c)->GetOutData()->_y0 = y0old ;
    GetOutContext(c)->GetOutData()->_scale = GetOutContext(c)->GetOutData()->oldscale ;
    GetOutContext(c)->GetOutData()->IsPrinting = FALSE ;

    GetOutContext(c)->GetOutData()->Pr->EndPrint();
    GetOutContext(c)->GetOutData()->Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////
//  Kontext - Testfunktionen
////////////////////////////////////////////////////////
BOOL IsInJobList (mdiChild *c,LPVOID param,WORD mode)
  {
  // Noch nicht implementiert
  return FALSE ;
  }

//////////////////////////////////////////////////////////////////////
//  Verschiedene Aktionen beim Suchen aller Fenster....
//////////////////////////////////////////////////////////////////////
typedef BOOL (* TESTCHILD) (mdiChild *c,LPVOID param);
BOOL ForAllChilds (TESTCHILD fnc,mdiChild *me,LPVOID param)
  {
  HWND hwChild;
  hwChild = GetWindow(WBase::hClient, GW_CHILD) ;

  BOOL res = FALSE ;
  while (hwChild) {
    while(hwChild && GetWindow(hwChild,GW_OWNER)) {
      hwChild = GetWindow(hwChild,GW_HWNDNEXT);
      }

    if(hwChild) { // Endlich gefunden
      mdiChild *pmdich = GetWindowInst(hwChild);
      if ((pmdich != NULL) && (pmdich != me)) {
        res = (* fnc) (pmdich,param);
        if (res) break ;
        }
      hwChild = GetWindow (hwChild,GW_HWNDNEXT);
      }
    }
  return res;
  }

#pragma pack(1)
struct IsDocOpen_param {
  WORD parSize;
  DWORD RecType;
  };

struct IsDocOpenName_param {
  WORD parSize;
  DWORD Name;
  };

struct ActivateDoc_param {
  WORD parSize;
  DWORD Name;
  };

struct GetDocFName_param {
  WORD parSize;
  DWORD Name;
  };
#pragma pack()

BOOL IsDocOpenFnc (mdiChild *c,LPVOID param)
  {
  IsDocOpen_param FAR *par = (IsDocOpen_param FAR *) param;
  return (c->schd->TRef[0].TableNr == WORD(par->RecType));
  }

extern BOOL GetProgFName (int Lfndr,LPSTR DocName,int size);
BOOL IsDocOpenNameFnc (mdiChild *c,LPVOID param)
  {
  LPSTR ntst = LPSTR (param);
  if (*ntst) {
    return (lstrcmp (ntst,c->schd->fName) == 0);
    }
  else
    return TRUE ;
  }

BOOL ActivateDocFnc (mdiChild *c,LPVOID param)
  {
  LPSTR ntst = LPSTR (param);
  if (lstrcmp (ntst,c->schd->fName) == 0) {
    SendMessage (WBase::hClient,WM_MDIACTIVATE,WPARAM(c->GetOutData()->_MyHandle),0L);
    return TRUE ;
    }
  else
    return FALSE ;
  }

BOOL IsDocOpen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    return ForAllChilds (IsDocOpenFnc,c,param);
  else
    return FALSE ;
  }

BOOL IsDocOpenName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    IsDocOpenName_param FAR *par = (IsDocOpenName_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->Name));
    if (Name != NULL)
      return ForAllChilds (IsDocOpenNameFnc,c,Name);
    else
      return FALSE ;
    }
  else
    return FALSE ;
  }

BOOL ActivateDoc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ActivateDoc_param FAR *par = (ActivateDoc_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->Name));
    if (Name != NULL)
      ForAllChilds (ActivateDocFnc,c,Name);
    }
  return FALSE ;
  }

BOOL GetDocFName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDocFName_param FAR *par = (GetDocFName_param FAR *) param;
    c->WritelData (par->Name,c->schd->fName,lstrlen(c->schd->fName)+1,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct DoHotkeyAction_param {
  WORD parSize;
  DWORD tool;
  };
#pragma pack()
BOOL DoHotkeyAction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DoHotkeyAction_param FAR *par = (DoHotkeyAction_param FAR *) param;
    toolbar_cbdata h(c);
    DoHotkeyAction (par->tool,&h);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

DLLExport void _export WINAPI SetOnEditChar (DWORD Edit,LPVOID privData,WORD vKey,WORD vModify,DWORD procOffset);
#pragma pack(1)
struct SetCharCallback_param {
  WORD parSize;
  DWORD tool;
  DWORD hktxt;      // Nur erstes Zeichen wird untersucht
  DWORD procOffset;
  };
#pragma pack()

BOOL SetCharCallback (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetCharCallback_param FAR *par = (SetCharCallback_param FAR *) param;
    toolbar_cbdata h(c);
    LPSTR txt = LPSTR (c->ReadlData (par->hktxt));
    if ((txt != NULL) && (*txt)) {
      SetOnEditChar (par->tool,&h,*txt,0,par->procOffset);
      }
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetSetFocusProc_param {
  WORD parSize;
  DWORD tool;
  DWORD procOffset;
  DWORD bCallOnKillFocus;
  };
#pragma pack()

BOOL SetSetFocusProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetSetFocusProc_param FAR *par = (SetSetFocusProc_param FAR *) param;
    toolbar_cbdata h(c);

    BOOL bKill = FALSE;
    if (par->parSize >= sizeof(*par)) {
      DBINT FAR *pbKill = (DBINT FAR *) c->ReadlData (par->bCallOnKillFocus);
      bKill = (pbKill != NULL) ? (BOOL)*pbKill : FALSE;
      }

    SetOnSetFocus (par->tool, &h, par->procOffset, bKill);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }


BOOL PrgExit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PostMessage (WBase::hFrameWin,WM_COMMAND,MI_QUIT,0L);
    }
  return FALSE ;
  }

#pragma pack(1)
struct WinExit_param {
  WORD parSize;
  DWORD Cmd;
  DWORD Par;
  };
#pragma pack()
extern BOOL DoWindowsExit;
extern char DosPrgToExit[],DosPrgParam[];
BOOL WinExit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PostMessage (WBase::hFrameWin,WM_COMMAND,MI_QUIT,0L);
    WinExit_param FAR *par = (WinExit_param FAR *) param;
    if (par->parSize >= sizeof(*par)) {
      lstrcpy (DosPrgToExit,LPSTR(c->ReadlData(par->Cmd)));
      lstrcpy (DosPrgParam,LPSTR(c->ReadlData(par->Par)));
      }
    DoWindowsExit = TRUE ;
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetWndFormat_param {
  WORD parSize;
  DWORD ed;
  DWORD format;
  };
#pragma pack()

BOOL SetWndFormat (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetWndFormat_param FAR *par = (SetWndFormat_param FAR *) param;
    DBINT FAR *ind = (DBINT FAR *) c->ReadlData (par->format);
    if (ind != NULL) {
      toolbar_cbdata h(c);
      SetEdFormat (par->ed,&h,*ind);
      if (h.Extra != NULL) FreeGlobMem (h.Extra);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFormatStrings_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

static LPSTR PushString (LPSTR old,LPSTR txt)
  {
  int offs;
  if (old != NULL)
    offs = GetBlockSize (old);
  else
    offs = 0;
  int size = lstrlen (txt) + 1;
  LPSTR n = LPSTR (GetGlobMem (offs + size));
  if (old != NULL) {
    lmemcpy (n,old,offs);
    FreeGlobMem (old);
    }
  lstrcpy (n + offs,txt);
  return n;
  }

BOOL GetFormatStrings (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFormatStrings_param FAR *par = (GetFormatStrings_param FAR *) param;
    
    LPSTR h = NULL ;
    for ( LPFORMATINFO fl = GetFormatFirst (); fl != NULL ; 
              fl = GetFormatNext (fl))
      h = PushString (h,fl->fi.FormatName);
    h = PushString (h,"\0");
    c->WritelData (par->res,h,GetBlockSize(h),LPSTR(param)-sizeof(WORD));
    FreeGlobMem (h);
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFieldCallback_param {
  WORD parSize;
  DWORD tool;
  DWORD StrId;
  };
#pragma pack()

BOOL GetFieldFormat (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    toolbar_cbdata h(c);
    GetFieldFormat (par->tool,&h,par->StrId);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

BOOL GetFieldModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    toolbar_cbdata h(c);
    GetFieldModify (par->tool,&h,par->StrId);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFieldModify_param {
  WORD parSize;
  DWORD field;
  DWORD Modify;
  DWORD Set_Clear;
  };
#pragma pack()

BOOL SetFieldModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    short FAR *lpModify = (short FAR *) c->ReadlData (par->Modify);
    DBBOOL FAR *lpSet_Clear = (DBBOOL FAR *) c->ReadlData (par->Set_Clear);
    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL) && (lpModify != NULL) && (lpSet_Clear != NULL))
      (*ed)->SetFieldModify (*lpModify,*lpSet_Clear);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;
    c->ClearlConnection (par->Modify,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Set_Clear,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetFocusToDoc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFocus (c->OutWnd());
    }
  return FALSE ;
  }

BOOL SynchorizeUpdate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    EmptyUpdateList ();
    }
  return FALSE ;
  }

BOOL CloseDocument (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LRESULT h = SendMessage (WBase::hClient,WM_MDIGETACTIVE,NULL,NULL);

#ifdef WIN32
    HWND hWnd = HWND(h);
#else
    HWND hWnd = LOWORD(h);
#endif

    if (IsWindow (hWnd))
      PostMessage (hWnd,WM_SYSCOMMAND,SC_CLOSE,0L);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFNrRef_param {
  WORD parSize;
  DWORD FNrRef;
  };
#pragma pack()

BOOL SetFNrRef (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFNrRef_param FAR *par = (SetFNrRef_param FAR *) param;
    c->PutDocumentExtraData (DED_FNRREF,&par->FNrRef,sizeof(par->FNrRef));
    }
  return FALSE ;
  }

BOOL ShowDocMaximized (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LRESULT h = SendMessage (WBase::hClient,WM_MDIGETACTIVE,NULL,NULL);

#ifdef WIN32
    HWND hWnd = HWND(h);
#else
    HWND hWnd = LOWORD(h);
#endif

    if (IsWindow (hWnd)) {
      WINDOWPLACEMENT wp ;
      lmemset (&wp,'\0',sizeof(wp));
      wp.length = sizeof(wp);
      GetWindowPlacement (hWnd,&wp);
      if (wp.showCmd != SW_SHOWMAXIMIZED)
        ShowWindow (hWnd,SW_SHOWMAXIMIZED);
      SetFocus (hWnd);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct CallOnDestroy_param {
  WORD parSize;
  DWORD res;
  DWORD ptrOffs;
  };
#pragma pack()
typedef CallOnDestroy_param FAR *LPCALLONDESTROY;

BOOL mdiChild::CallOnClose ()
  {
  BOOL res = TRUE;
  LPCALLONDESTROY FAR *lpc = (LPCALLONDESTROY FAR *) GetDocumentExtraData (DED_ONDESTROYPAR1);
  if (lpc != NULL) {
#ifdef DEBUG
    PushToCallStack (this,schd->fName,0L);
#endif
    ExCuteProc ((*lpc)->ptrOffs,EM_LOAD);
#ifdef DEBUG
    PopFromCallStack ();
#endif
    DBBOOL FAR *lpres = (DBBOOL FAR *) ReadlData ((*lpc)->res);
    res = ((lpres == NULL) || (*lpres));
    }
  else
    res = TRUE ;
  return res;
  }

BOOL CallOnDestroy (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    // Die Dinge vermerken, Sie werden spaeter sicher noch gebraucht
    c->PutDocumentExtraData (DED_ONDESTROYPAR1,&param,sizeof(param));
    }
  return FALSE ;
  }



#pragma pack(1)
struct Layer_param {
  WORD parSize;
  WORD scRec, scId;
  DWORD Layer;
  };
#pragma pack()

BOOL RemoveControlFromLayer (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Layer_param FAR *par = (Layer_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    DBWIN_ASSERT (c->IsConst (par->Layer));
    DBINT Layer = *((DBINT FAR *) c->ReadlData (par->Layer));
    RemoveScreenControlFromLayer (*llpsc,Layer);
    }
  return FALSE;
  }

BOOL ActivateScreenLayer (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Layer_param FAR *par = (Layer_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    DBWIN_ASSERT (c->IsConst (par->Layer));
    DBINT Layer = *((DBINT FAR *) c->ReadlData (par->Layer));
    ActivateLayerInScreen (*llpsc, Layer);
    }
  return FALSE ;
  }



#pragma pack(1)
struct DoSetFocus_param {
  WORD parSize;
  DWORD tool;
  DWORD State;
  };
#pragma pack()

BOOL SetFocusToObject (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    DoSetFocus_param FAR *par = (DoSetFocus_param FAR *) param;
    toolbar_cbdata h(c);
    DBBOOL state ;
    if (par->parSize >= sizeof(*par)) {
      DBWIN_ASSERT (c->IsConst (par->State));
      state = *((DBBOOL FAR *) c->ReadlData (par->State));
      }
    else
      state = TRUE ;
    SetFocusOnTool (par->tool, &h, state);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

#pragma pack(1)
struct RecRef_param {
  WORD parSize;
  DWORD RefCount;
  DWORD FNr;
  };
#pragma pack()

#pragma pack(1)
struct WinHelp_param {
  WORD parSize;
  DWORD KontextNr;
  DWORD HelpFile;
  };
#pragma pack()

BOOL CallWindowsHelp (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WinHelp_param FAR *par = (WinHelp_param FAR *) param;
    DBINT FAR *lpHelpContextNr = (DBINT FAR *)c->ReadlData (par->KontextNr);
    DWORD dwHelpContextNr = ((lpHelpContextNr != NULL) && *lpHelpContextNr) ? *lpHelpContextNr : 1;

    SetHelpContextNr (dwHelpContextNr);

    LPSTR lpHelpFile = NULL;
    if (par->parSize >= sizeof(*par))
      lpHelpFile = (LPSTR)c->ReadlData (par->HelpFile);

    if (lpHelpFile && *lpHelpFile)
      SetHelpFile (lpHelpFile);
    else
      SetHelpFile ("DDS.HLP");
/*
    HWND hRefWnd = (IsMainControl (c)) ? WBase::hFrameWin : c->_MyHandle ;
    WinHelp (hRefWnd, "DDS.HLP", HELP_CONTEXT, par->KontextNr);
*/
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
#ifdef WIN32
    SetHelpContextNr (-1);
#else
    SetHelpContextNr (1);
    SetHelpFile ("DDS.HLP");
#endif
    }

  return FALSE ;
  }


#pragma pack(1)
struct windim_param {
  WORD  parSize;
  WORD  scRec, scId;
  DWORD w, h;
  };
#pragma pack()

BOOL SetWindowDimension (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    windim_param FAR *par = (windim_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    DBWIN_ASSERT (c->IsConst (par->w));
    DBWIN_ASSERT (c->IsConst (par->h));
    DBINT w = *((DBINT FAR *) c->ReadlData (par->w));
    DBINT h = *((DBINT FAR *) c->ReadlData (par->h));
    ChangeToolbarSize (*llpsc, w, h);
    }
  return FALSE ;
  }


#pragma pack(1)
struct title_param {
  WORD parSize;
  WORD scRec, scId;
  DWORD Caption; 
  };
#pragma pack()

BOOL SetWindowTitle (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR Title;
    title_param FAR *par = (title_param FAR *) param;
    LPSCREEN FAR *llpsc = (LPSCREEN FAR *) 
          c->ReadData (par->scRec,par->scId);
    DBWIN_ASSERT (llpsc != NULL);
    Title = LPSTR (c->ReadData (LOWORD(par->Caption),HIWORD(par->Caption)));
    SetToolbarTitle (*llpsc, Title);
    }
  return FALSE ;
  }

#pragma pack(1)
struct DeleteFile_param {
  WORD parSize;
  DWORD fName;
  };
#pragma pack()

BOOL DeleteFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DeleteFile_param FAR *par = (DeleteFile_param FAR *) param;
    LPSTR fName = LPSTR (c->ReadlData (par->fName));
    if (fName != NULL) {
      OFSTRUCT Of;
      int handle = OpenFile (GetFullDIBName (fName),&Of,OF_DELETE);
      DBWIN_ASSERT (handle != HFILE_ERROR);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FileSelector_Box_param {
  WORD parSize;
  DWORD res;
  DWORD title;
  DWORD path;
  DWORD pattern;
  DWORD father;
  DWORD mustExist;
  DWORD allowMulti;
  };
#pragma pack()

DLLExport void _export WINAPI CTOOL_EnableParent (HWND disabledWindow,HWND modalParent);
DLLExport HWND _export WINAPI CTOOL_DisableParent (HWND FAR *modalParent);

BOOL FileSelector_Box (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FileSelector_Box_param FAR * par = (FileSelector_Box_param FAR *) param;
    LPSTR ores    = LPSTR (c->ReadlData (par->res));
    LPSTR title   = LPSTR (c->ReadlData (par->title));
    LPSTR path    = LPSTR (c->ReadlData (par->path));
    LPSTR pattern = LPSTR (c->ReadlData (par->pattern));

    DBWIN_ASSERT (title != NULL);

    char                szname[2048];

    OPENFILENAME        ofn;

    *szname = '\0' ;
    lmemset (&ofn,'\0',sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
#ifdef UEBERLEGT
    if (par->parSize >= sizeof(*par) - sizeof(WORD)) {
      LPSCREEN FAR *scl = (LPSCREEN FAR *) 
            c->ReadlData (par->father);
      ofn.hwndOwner = ((scl != NULL) && (*scl != NULL)) ? 
            (* scl)->hWnd : 
            c->_MyHandle;
      
      }
    else
      ofn.hwndOwner = c->OutWnd();
#else
    HWND modalParent;
    HWND owner = CTOOL_DisableParent (&modalParent);
    ofn.hwndOwner = owner ;
#endif
    ofn.hInstance = WBase::hInstance;
    if ((pattern != NULL) && (*pattern))
      ofn.lpstrFilter = pattern;
    else
      ofn.lpstrFilter = LRString (10059);
    if (ores != NULL)
      lstrncpy (szname,ores,sizeof(szname) - 1);
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = (LPSTR)szname;
    ofn.nMaxFile = sizeof(szname);
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    if (path != NULL)
      ofn.lpstrInitialDir = path;
    else
      ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = title;
    BOOL mustExist ;
    if (par->parSize >= sizeof(*par) - sizeof(DWORD)) {
      DBBOOL FAR *lpmustExist = (DBBOOL FAR *) c->ReadlData (par->mustExist);
      if (lpmustExist != NULL) mustExist = *lpmustExist ;
      else                     mustExist = TRUE;
      }
    else
      mustExist = TRUE ;

    BOOL allowMulti ;
    if (par->parSize >= sizeof(*par)) {
      DBBOOL FAR *lpallowMulti = (DBBOOL FAR *) c->ReadlData (par->allowMulti);
      if (lpallowMulti != NULL) allowMulti = *lpallowMulti ;
      else                      allowMulti = FALSE;
      }
    else
      allowMulti = FALSE ;

    ofn.Flags = OFN_PATHMUSTEXIST;
    if (mustExist)
      ofn.Flags = ofn.Flags | OFN_FILEMUSTEXIST ;
    if (allowMulti)
      ofn.Flags = ofn.Flags | OFN_ALLOWMULTISELECT | OFN_EXPLORER ;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = NULL;
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;

    if (GetOpenFileName(&ofn)) {
      if (allowMulti) {
        for (int size = 0; size < sizeof(szname) ; size++) {
          if ((szname[size] == '\0') && (szname[size + 1] == '\0')) {
            size += 2 ;
            break ;
            }
          }
        c->WritelData (par->res,szname,size,LPSTR(param)-sizeof(WORD));
        }
      else
        c->WritelData (par->res,szname,lstrlen(szname) + 1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    CTOOL_EnableParent (owner,modalParent);
    }
  return FALSE ;
  } //FileSelector_Box_param

#pragma pack(1)
struct DirSelector_Box_param {
  WORD  parSize;
  DWORD res;
  DWORD title;
  DWORD mode;
  };
#pragma pack()

BOOL DirSelector_Box (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DirSelector_Box_param FAR * par = (DirSelector_Box_param FAR *) param;
    LPSTR ores    = LPSTR (c->ReadlData (par->res));
    LPSTR title   = LPSTR (c->ReadlData (par->title));

    DBWIN_ASSERT (title != NULL);

    char       dispname[MAX_PATH];
    char       szname[MAX_PATH];

    HWND modalParent;
    HWND owner = CTOOL_DisableParent (&modalParent);

    #ifdef GetDirMitCLIB
    BROWSEINFO bfi ;

    bfi.hwndOwner      = owner ;
    bfi.pidlRoot       = NULL ;
    bfi.pszDisplayName = dispname ;
    bfi.lpszTitle      = title;
    bfi.ulFlags        = c->ReadConstLong (par->mode) ;
    bfi.lpfn           = NULL ;
    bfi.lParam         = NULL ;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bfi);
    if (pidl) {
      BOOL bSuccess = SHGetPathFromIDList (pidl, szname);
      ILFree(pidl);
      if (bSuccess)
        c->WritelData (par->res,szname,lstrlen(szname) + 1,LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    #else
    int bres = (*lpfnSelectDir)(ores,szname,MAX_PATH);
    if (bres) {
      c->WritelData (par->res,szname,lstrlen(szname) + 1,LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    #endif
    CTOOL_EnableParent (owner,modalParent);
    }
  return FALSE ;
  }  //DirSelector_Box

//============================================================================
//
// ChooseColorDialog
//
// Anzeige des Farbauswahldialoges aus Windows
//============================================================================
#pragma pack(1)
struct ChooseColorDialog_param {
  WORD parSize;
  DWORD rgbCurrent;    // Rueckgabewert ist gewaehlte Farbe
  DWORD clr[16];       // 16 frei definierbare Farben
  };
#pragma pack()

BOOL ChooseColorDialog (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ChooseColorDialog_param FAR * par = (ChooseColorDialog_param FAR *) param;

    DWORD rgbCurrent;
    LPCOLORREF lprgbCurrent = LPCOLORREF (c->ReadlData (par->rgbCurrent));

    if (lprgbCurrent == NULL) {
//      kein ASSERT, da es sich ja um eine nichtinitialisierte Variable 
//      handeln kann, und das ist kein schwerwiegender Fehler.
//      DBWIN_ASSERT_TEXT (FALSE, "Der Initialwert f�r den Farbauswahldialog fehlt!");
      rgbCurrent = 0;
      }
    else
      rgbCurrent = *lprgbCurrent;

    static COLORREF acrCustClr[16]; // array of custom colors 

    int i;
    for (i = 0; i < 16; i++)
      acrCustClr[i] = RGB(255, 255, 255);

    LPCOLORREF clr;
    //------------------------------------------------------------------
    // Wieviele frei definierbare Farben wurden im Script angegeben?
    // normalerweise sollten es 16 sein, aber wenn's der Programmierer
    // vergessen hat, soll's auch nicht abstuerzen.
    // iParamSize = ParameterSize - rgbCurrent - parSize
    //------------------------------------------------------------------
    int iParamSize = par->parSize - sizeof(DWORD) - sizeof(WORD);
    for (i = 0; ((int(i * sizeof(DWORD))) < iParamSize) && (i < 16); i++) {
      clr = (COLORREF FAR *) c->ReadlData (par->clr[i]);
      if (clr != NULL) 
        acrCustClr[i]  = *clr;
      }

    CHOOSECOLOR cc;                 // common dialog box structure 

    // Initialize CHOOSECOLOR 
    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.lpCustColors = (LPDWORD) acrCustClr;
    cc.rgbResult = rgbCurrent;
    cc.Flags = CC_RGBINIT;
    if (iParamSize <= 0)
      cc.Flags |= CC_PREVENTFULLOPEN;
    cc.lCustData = 0L;
    cc.lpfnHook = (LPCCHOOKPROC)(FARPROC)NULL;


    HWND modalParent;
    HWND owner = CTOOL_DisableParent (&modalParent);
    cc.hwndOwner = owner ;

    BOOL OldInClientTransaction = InClientTransaction;
    InClientTransaction = TRUE;
    if (ChooseColor(&cc) != 0) {
      c->WritelData (par->rgbCurrent, &cc.rgbResult, sizeof(cc.rgbResult),LPSTR(param)-sizeof(WORD));
      for (i = 0; ((int(i * sizeof(DWORD))) < iParamSize) && (i < 16); i++) {
        c->WritelData (par->clr[i], &acrCustClr[i], sizeof(acrCustClr[i]),LPSTR(param)-sizeof(WORD));
        }
      }
    else
      c->DellData (par->rgbCurrent, LPSTR(param)-sizeof(WORD));

    if (!OldInClientTransaction) {
      InClientTransaction = FALSE;
      if (CallCommandInClientTransaction) {
        PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
        CallCommandInClientTransaction = FALSE;
        }
      deleteAllOpenChilds ();
      }

    CTOOL_EnableParent (owner,modalParent);
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    ChooseColorDialog_param FAR * par = (ChooseColorDialog_param FAR *) param;

    c->ClearlConnection (par->rgbCurrent, LPSTR(param)-sizeof(WORD));
    int iParamSize = par->parSize - sizeof(DWORD) - sizeof(WORD);
    for (int i = 0; ((int(i * sizeof(DWORD))) < iParamSize) && (i < 16); i++)
      c->ClearlConnection (par->clr[i], LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct GetPrinterType_param FAR {
  WORD parSize;
  DWORD devname;
  DWORD portrait;
  DWORD landscape;
  DWORD defaultsource;
  DWORD papersize;
  DWORD DevModeParam;
  DWORD paperlength;
  DWORD paperwidth;
  BOOL MitDevMode ()
    {
    return (parSize >= (sizeof(*this) - (2 * sizeof(DWORD))));
    }
  BOOL MitLength ()
    {
    return (parSize >= (sizeof(*this) - sizeof(DWORD)));
    }
  BOOL MitWidth ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

void GetDevModeParam (GetPrinterType_param FAR *par,mdiChild *c,
      LPSTR dn,int FAR &orientation,int FAR &dsource,int FAR &psize,LPVOID FAR &devMode
                     )
  {
  LPSTR devname   = LPSTR (c->ReadlData (par->devname));
  DBBOOL FAR *portrait  = (DBBOOL FAR *) c->ReadlData (par->portrait);
  DBBOOL FAR *landscape = (DBBOOL FAR *) c->ReadlData (par->landscape);
  DBINT FAR *defaultsource = (DBINT FAR *) c->ReadlData (par->defaultsource);
  DBINT FAR *papersize = (DBINT FAR *) c->ReadlData (par->papersize);

  if (par->MitDevMode()) {
    devMode = c->ReadlData (par->DevModeParam);
    }
  else
    devMode = NULL;

  if (devMode != NULL) {
    DEVMODE *dm = (DEVMODE *)devMode;
    if (par->MitLength()) {
      float *pl = (float *)c->ReadlData (par->paperlength);
      if (pl != NULL) {
        dm->dmFields |= DM_PAPERLENGTH;
        dm->dmPaperLength = int(*pl * 10.0);
        }
      }
    if (par->MitWidth()) {
      float *pw = (float *)c->ReadlData (par->paperwidth);
      if (pw != NULL) {
        dm->dmFields |= DM_PAPERWIDTH;
        dm->dmPaperWidth = int(*pw * 10.0);
        }
      }
    }
  if (devname != NULL)
    lstrcpy (dn,devname);
  else
    *dn = '\0';     // Default Drucker
  if ((landscape != NULL) && (portrait != NULL)) {
    if (*landscape) orientation = DMORIENT_LANDSCAPE ;
    else            orientation = DMORIENT_PORTRAIT ;
    }
  else
    orientation = -1;
  if (defaultsource != NULL)
    dsource = *defaultsource ;
  else
    dsource = 0;  // ehemals dsource = -1;
  if (papersize != NULL)
    psize = *papersize;
  else
    psize = -1;
  }

BOOL GetPrinterType (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetPrinterType_param FAR *par = (GetPrinterType_param FAR *) param;

    char dn[64];
    int orientation,dsource,psize;
    LPVOID DevMode,DevModeOut;
    GetDevModeParam (par,c,dn,orientation,dsource,psize,DevMode);
    if (PrinterConfig (GetActiveWindow(),dn,
                            orientation,dsource,psize,DevMode,DevModeOut)) {
      // Der Benutzer will wirklich einen neuen Drucker
      if (*dn)
        // Spezial - Drucker verwenden
        c->WritelData (par->devname,dn,lstrlen(dn)+1,LPSTR(param)-sizeof(WORD));
      else
        // Default - Drucker verwenden
        c->DellData (par->devname,LPSTR(param)-sizeof(WORD));

      BOOL p,l;
      if (orientation == DMORIENT_PORTRAIT)
        p = TRUE , l = FALSE ;
      else
        p = FALSE , l = TRUE ;
      c->WritelData (par->portrait,&p,sizeof(p),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->landscape,&l,sizeof(l),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->defaultsource,&dsource,sizeof(dsource),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->papersize,&psize,sizeof(psize),LPSTR(param)-sizeof(WORD));
      if (par->MitDevMode()) {
        if (DevModeOut) {
          c->WritelData (par->DevModeParam,DevModeOut,GetBlockSize(DevModeOut),LPSTR(param)-sizeof(WORD));
          FreeGlobMem (DevModeOut);
          }
        else
          c->DellData (par->DevModeParam,LPSTR(param)-sizeof(WORD));
        }
      }
    }
  return FALSE ;
  }

BOOL PrinterChanged (Printer FAR *Pr,LPSTR dn,int orientation,int dsource,int psize,BOOL FAR *scChanged)
  {
  int OldSource = Pr->DevMode->dmDefaultSource;
  if (OldSource == 0) OldSource = Pr->DefaultSource;
  int NewSource = dsource;
  if (NewSource == 0) NewSource = Pr->DefaultSource;
  char DriverName[128];
  if (*dn)
    lstrcpy(DriverName,dn);
  else
    GetDefaultPrinterName(DriverName);

// #define DIAGNOSTICPRINT 1
#ifdef DIAGNOSTICPRINT
  if (OldSource != NewSource) {
    char DiagStr[512];
    wsprintf(DiagStr,"Schacht hat gewechselt: alt = %d, neu = %d, default = %d",
             Pr->DevMode->dmDefaultSource,dsource,Pr->DefaultSource);
    WIN_ASSERT_TEXT(FALSE,DiagStr);
    }
  if (lstrcmp (DriverName,Pr->DeviceName) != 0) {
    char DiagStr[512];
    wsprintf(DiagStr,"Drucker hat gewechselt: alt = %s, neu = %s",
             Pr->DeviceName,DriverName);
    WIN_ASSERT_TEXT(FALSE,DiagStr);
    }
#endif

  *scChanged = (OldSource != NewSource);
  // if ((lstrcmp (DriverName,Pr->DeviceName) != 0) || (*scChanged))
  if (lstrcmp (DriverName,Pr->DeviceName) != 0)
    return TRUE ;
  else
    return FALSE ;
  }

extern DLLExport void _export WINAPI ModifyPrinterSource(Printer *Pr,int defSource);
BOOL SetPrinter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    BOOL OldInClientTransaction = InClientTransaction;
    InClientTransaction = TRUE;
    GetPrinterType_param FAR *par = (GetPrinterType_param FAR *) param;

    char dn[64];
    int orientation,dsource,psize;
    LPVOID DevMode;
    GetDevModeParam (par,c,dn,orientation,dsource,psize,DevMode);

    if ((GetOutContext(c)->GetOutData()->IsPrinting) && (GetOutContext(c)->GetOutData()->Pr != NULL)) {
      BOOL scchg;
      if (PrinterChanged (GetOutContext(c)->GetOutData()->Pr,dn,orientation,dsource,psize,&scchg)) {
        GetOutContext(c)->GetOutData()->Pr->EndPrint();
        GetOutContext(c)->GetOutData()->Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben

        if (GetOutContext(c)->GetOutData()->Pr != NULL)
          FreePrinter (GetOutContext(c)->GetOutData()->Pr);

        GetOutContext(c)->GetOutData()->Pr = GetPrinter (dn,orientation,dsource,psize,DevMode);
        DBWIN_ASSERT (GetOutContext(c)->GetOutData()->Pr != NULL);

        GetOutContext(c)->GetOutData()->Pr->PrinterDC(TRUE);          // Jetzt wirds ernst
        GetOutContext(c)->GetOutData()->Pr->StartPrint(GetPrinterHeader());
        GetOutContext(c)->GetOutData()->Pr->StartFrame ();
        }
      else if (scchg) {
        // Auf dem gleichen Drucker in anderem Schacht weitermachen
        ModifyPrinterSource(GetOutContext(c)->GetOutData()->Pr,dsource);
        GetOutContext(c)->GetOutData()->Pr->StartFrame ();
        }
      else
        // Auf dem gleichen Drucker weitermachen
        GetOutContext(c)->GetOutData()->Pr->StartFrame ();
      }
    else {
      GetOutContext(c)->GetOutData()->Pr = GetPrinter (dn,orientation,dsource,psize,DevMode);
      DBWIN_ASSERT (GetOutContext(c)->GetOutData()->Pr != NULL);

      GetOutContext(c)->GetOutData()->Pr->PrinterIC ();
      }

    if (!OldInClientTransaction) {
      InClientTransaction = FALSE;
      if (CallCommandInClientTransaction) {
        PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
        CallCommandInClientTransaction = FALSE;
        }
      deleteAllOpenChilds ();
      }
    }
#ifdef UEBERLEGT
  if (mode & EM_FIXCONNECTION) {
    GetPrinterType_param FAR *par = (GetPrinterType_param FAR *) param;
    c->SetlConnection (par->devname,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->portrait,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->landscape,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->defaultsource,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->papersize,LPSTR(param)-sizeof(WORD));
    }
#endif
  if (mode & (EM_RESET | EM_CLEAR)) {
    GetPrinterType_param FAR *par = (GetPrinterType_param FAR *) param;
    c->ClearlConnection (par->devname,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->portrait,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->landscape,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->defaultsource,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->papersize,LPSTR(param)-sizeof(WORD));

    if ((GetOutContext(c)->GetOutData()->Pr != NULL) && (!GetOutContext(c)->GetOutData()->IsPrinting)) {
      FreePrinter (GetOutContext(c)->GetOutData()->Pr);
      GetOutContext(c)->GetOutData()->Pr = NULL;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetDefaultPrinterName_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetDefaultPrinterName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDefaultPrinterName_param FAR *par = (GetDefaultPrinterName_param FAR *) param;
    char res[128];
    GetDefaultPrinterName (res);
    c->WritelData (par->res,res,lstrlen(res)+1,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//-----------------------------------------------------------------------
// Die Funktion SetCaretToEnd war urspruenglich fuer ein ShowToolList 
// programmiert. Sie wird aber auch in einem normalen ToolEdit benoetigt.
// Da sich im ShowToolList_param das edObj ebenfalls an zweiter Stelle 
// befindet, wird diese Prozedur daher ein bisschen zweckentfremdet.
//-----------------------------------------------------------------------
#pragma pack(1)
struct SetCaretToEnd_param {
  WORD parSize;
  DWORD edObj;   // das Element so nennen wie im ShowToolList
  };
#pragma pack()

BOOL SetEditCaretToEnd (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    // Lesen aller Daten

    // zuerst einmal probieren ob es nur ein CaretToEnd ist!!
    SetCaretToEnd_param FAR *par = (SetCaretToEnd_param FAR *) param;

    // wenn nicht, dann muss es ein ShowToolList sein
    if (par->parSize >= sizeof(*par))
      ShowToolList_param FAR *par = (ShowToolList_param FAR *) param;

    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->edObj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    (*e)->SetCaretToEnd ();
    }
  return FALSE ;
  }

BOOL ClearQueue (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MSG msg;
    while (PeekMessage (&msg,0,0,0,PM_REMOVE))
      CheckMsg (&msg);
    }
  return FALSE ;
  }

DWORD t0;
BOOL doTest = FALSE ;
struct TestCounter {
  int type;
  mdiChild *c;
  LPSTR name;
  DWORD count;
  } tcount[MAXTESTTYPES];

#pragma pack(1)
struct FAR Start_TimeMark_param {
  WORD parSize;
  struct {
    DWORD type;
    DWORD tstr;
    } x[1];
  int AnzTests () { return (parSize >= sizeof(*this)) ?
                        (parSize - sizeof (*this)) / sizeof(x[0]) + 1 :
                        0 ;
                  };
  };
#pragma pack()

void ResetNames ()
  {
  for (int i = 0 ; i < MAXTESTTYPES ; i++) {
    if (tcount[i].name != NULL) FreeGlobMem (tcount[i].name) ;
    tcount[i].name = NULL;
    }
  }

BOOL Start_TimeMark (mdiChild *c,LPVOID param,WORD mode)
  {
  static BOOL ProfSetupDone;
  if (mode & EM_LOAD) {
    if (!ProfSetupDone) {
#ifndef WIN32
      ProfSetup (512,0);
      ProfClear ();
#endif
      }
    t0 = GetTickCount ();
    doTest = TRUE ;
    Start_TimeMark_param FAR *par = (Start_TimeMark_param FAR *)param;
    ResetNames ();
    for (int i = 0 ; i < par->AnzTests () ; i++) {
      DBWIN_ASSERT (par->x[i].type < MAXTESTTYPES);
      LPSTR name = LPSTR (c->ReadlData (par->x[i].tstr));
      tcount[i].name = LPSTR (GetGlobMem (lstrlen(name)+1));
      lstrcpy (tcount[i].name,name);
      DBWIN_ASSERT (c->IsConst (par->x[i].type));
      DBINT type = *((DBINT FAR *) c->ReadlData (par->x[i].type));
      tcount[i].type = type;
      tcount[i].c = c;
      tcount[i].count = 0;
      }
#ifndef WIN32
    ProfStart ();
#endif
    }

  return FALSE ;
  }

void IncTestCount (mdiChild *c,int type)
  {
  if (doTest) {
    DBWIN_ASSERT (type < MAXTESTTYPES);
    if (tcount[type].c == c)
      tcount[type].count += 1;
    }
  }

void ShowTestMsg ()
  {
  if (doTest) {
    // Anzeigen der benoetigen Zeit

#ifndef WIN32
    ProfFlush ();
    ProfStop ();
#endif

    DWORD t1 = GetTickCount ();
    char outtxt[128];
    wsprintf (outtxt,"Zeitbedarf: %ld",t1-t0);
    WIN_ASSERT_TEXT (FALSE,outtxt);

    for (int i = 0 ; i < MAXTESTTYPES ; i++) {
      if (tcount[i].name != NULL) {
        wsprintf (outtxt,tcount[i].name,tcount[i].count);
        WIN_ASSERT_TEXT (FALSE,outtxt);
        }
      }
    // Anzeigen ev. noetiger Variablen
    doTest = FALSE ;
    }
  }

#pragma pack(1)
struct SetEditOverwrite_param {
  WORD parSize;
  DWORD objRef;
  };
#pragma pack()

BOOL SetEditOverwrite (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetEditOverwrite_param FAR *par = (SetEditOverwrite_param FAR *) param;
    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->objRef);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    (*e)->SetOverwrite ();
    }
  return FALSE ;
  }

BOOL MoveToolGroup (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPMOVEELEMPAR par = LPMOVEELEMPAR (param);
    toolbar_cbdata h(c);
    MoveElems (par,&h);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

BOOL SetToolExtension (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPEXTTOOLDIM par = LPEXTTOOLDIM (param);
    toolbar_cbdata h(c);
    SetExtToolDimension (par,&h);
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetOutContext_param {
  WORD parSize;
  DWORD c;
  };
#pragma pack()

BOOL SetOutContext (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOutContext_param FAR *par = (SetOutContext_param FAR *) param;
    LPMDICHILD FAR *out = (LPMDICHILD FAR *)c->ReadlData(par->c);
    DBWIN_ASSERT (out != NULL);
    for ( LPMDICHILD res = *out ; res->outContext != NULL ; res = res->outContext ) ;
    c->outContext = res;
    }
  return FALSE ;
  }

BOOL SetToolRefHandle (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOutContext_param FAR *par = (SetOutContext_param FAR *) param;
    LPMDICHILD FAR *out = (LPMDICHILD FAR *)c->ReadlData(par->c);
    DBWIN_ASSERT ((out != NULL) && (*out != NULL)) ;
    int size;
    LPVOID oldExtra = (*out)->GetDocumentExtraData (DED_TOOLWND,&size);
    if (oldExtra != NULL)
      c->PutDocumentExtraData (DED_TOOLWND,oldExtra,size);
    else
      c->PutDocumentExtraData (DED_TOOLWND,&(*out)->GetOutData()->_MyHandle,sizeof((*out)->GetOutData()->_MyHandle));
    }
  return FALSE ;
  }

BOOL SetToolRefHandleExplizit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOutContext_param FAR *par = (SetOutContext_param FAR *) param;
    LPVOID extra = c->ReadlData(par->c);
    if (extra != NULL)
      c->PutDocumentExtraData (DED_TOOLWND,extra,GetBlockSize(extra));
    }
  return FALSE ;
  }

struct MDIClienData {
  HWND hMDIClient;
  FARPROC DefChildProc;
  };
extern DLLExport LONG _export FAR PASCAL ChildWndProc(HWND hWnd, UINT msg, WPARAM wP, LPARAM lP);
BOOL GetMDIClienData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOutContext_param FAR *par = (SetOutContext_param FAR *) param;
    MDIClienData mc;
    mc.hMDIClient = WBase::hClient;
    mc.DefChildProc = (FARPROC) ChildWndProc;
    c->WritelData(par->c,&mc,sizeof(mc),LPSTR (param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetVarSize_param {
  WORD parSize;
  DWORD res;
  DWORD var;
  };
#pragma pack()

BOOL GetVarSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetVarSize_param FAR *par = (GetVarSize_param FAR *) param;
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (c->schd->TRef[LOWORD(par->var)-CSYSRECS].TableNr,c->schd->TRef[LOWORD(par->var)-CSYSRECS].Version);
    LPVARDEF v = td->GetVarDef(HIWORD(par->var));
    int res ;

    if (v->VarID == 0xFFFF)
      res = v->VarSize;
    else
      res = -1;

    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    GetTableAdmin()->FreeTable (c->schd->TRef[LOWORD(par->var)-CSYSRECS].TableNr,c->schd->TRef[LOWORD(par->var)-CSYSRECS].TableNr);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetEditSize_param {
  WORD parSize;
  DWORD obj;
  DWORD size;
  };
#pragma pack()

BOOL SetEditSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetEditSize_param FAR *par = (SetEditSize_param FAR *) param ;
    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    DBINT FAR *size = (DBINT FAR *) c->ReadlData (par->size);
    if (size != NULL) {
      (*e)->SetMaxSize (*size);
      }
    }
  return FALSE ;
  }

BOOL DefTransparentBitmap (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    toolbar_cbdata h(c);
    DefBitmapObject (param,mode,&h,sizeof(h));
    if (h.Extra != NULL)
      FreeGlobMem (h.Extra);
    }
  else
    DefBitmapObject (param,mode,NULL,0);
  return FALSE ;
  }

#pragma pack(1)
struct SetBitSelectMode_param {
  WORD parSize;
  DWORD obj;
  DWORD mode;
  };
#pragma pack()
BOOL SetBitSelectMode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetBitSelectMode_param FAR *par = (SetBitSelectMode_param FAR *) param;
    BitSelect FAR *FAR *lpbs = (BitSelect FAR *FAR *) c->ReadlData (par->obj);
    DBBOOL FAR *lpmode = (DBBOOL FAR *) c->ReadlData (par->mode);
    if ((lpbs != NULL) && (lpmode != NULL))
      CTOOL_SetBitSelectMode (*lpbs,*lpmode);
    }
  return FALSE ;
  }

#pragma pack(1)
struct InstallSelectMode_param {
  WORD parSize;
  DWORD Id;
  };
#pragma pack()
BOOL InstallSelectMode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InstallSelectMode_param FAR *par = (InstallSelectMode_param FAR *) param;
    CTOOL_InstallSelectMode (par->Id);
    }
  return FALSE ;
  }


#pragma pack(1)
struct CreatePostIt_param {
  WORD  parSize;
  DWORD x;
  DWORD y;
  DWORD w;
  DWORD h;
  DWORD Format;
  DWORD Text;
  };
#pragma pack()

HWND CreatePostItWindow (mdiChild *c, HINSTANCE hInst, int x, int y, int w, int h, int Format, LPSTR Text,LPVOID Param,LPVOID PrivData,WORD privDataSize);

static void doUpdatePostIt (CreatePostIt_param FAR *par,LPVOID PrivData,int x,int y,int w,int h,LPSTR Text)
  {
  LPTBD (PrivData)->c->WritelData (par->x,&x,sizeof(DBINT),LPSTR(par) - sizeof(WORD)) ;
  LPTBD (PrivData)->c->WritelData (par->y,&y,sizeof(DBINT),LPSTR(par) - sizeof(WORD)) ;
  LPTBD (PrivData)->c->WritelData (par->w,&w,sizeof(DBINT),LPSTR(par) - sizeof(WORD)) ;
  LPTBD (PrivData)->c->WritelData (par->h,&h,sizeof(DBINT),LPSTR(par) - sizeof(WORD)) ;
  LPTBD (PrivData)->c->WritelData (par->Text,Text,lstrlen(Text) + 1,LPSTR(par) - sizeof(WORD)) ;
  }
void UpdatePostIt (LPVOID param,LPVOID PrivData,int x,int y,int w,int h,LPSTR Text)
  {
  CreatePostIt_param FAR *par = (CreatePostIt_param FAR *) param;
  ENTER(doUpdatePostIt (par,PrivData,x,y,w,h,Text));
  }

BOOL CreatePostIt (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    CreatePostIt_param FAR *par = (CreatePostIt_param FAR *) param;
    DBINT x = *((DBINT FAR *) c->ReadlData (par->x));
    DBINT y = *((DBINT FAR *) c->ReadlData (par->y));
    DBINT w = *((DBINT FAR *) c->ReadlData (par->w));
    DBINT h = *((DBINT FAR *) c->ReadlData (par->h));
    DBINT Format = *((DBINT FAR *) c->ReadlData (par->Format));
    LPSTR Text = LPSTR(c->ReadlData (par->Text));

//    PaintContext pc;
//    GetDocumentContext (&pc, c);
//    HWND hWParent = c->_MyHandle;
    toolbar_cbdata hd(c);
    CreatePostItWindow (c, WBase::hInstance, x, y, w, h, Format,Text,par,&hd,sizeof(hd));
    }

  return FALSE;
  }

// Druckausgabe mit Scriptprozeduren
/////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR PrintDocumentEx_param {
  WORD parSize;
  DWORD FirstPage;
  DWORD LastPage;
  DWORD AnzCopys;
  DWORD preProc;
  DWORD printProc;
  DWORD xLeft,yTop,xRight,yBottom;
  DWORD AutoScale;
  DWORD Scale;
  };
#pragma pack()

BOOL PrintDocumentEx (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL OldInClientTransaction = InClientTransaction;
    InClientTransaction = TRUE;
    PrintDocumentEx_param FAR *par = (PrintDocumentEx_param FAR *) param;
    DBWIN_ASSERT (par->parSize >= sizeof(*par));

    GetOutContext(c)->GetOutData()->IsPrinting = TRUE ;

    // Ermitteln des Druckers
    if (GetOutContext(c)->GetOutData()->Pr == NULL)
      GetOutContext(c)->GetOutData()->Pr = GetPrinter (TRUE);
    GetOutContext(c)->GetOutData()->Pr->PrinterDC(TRUE);          // Jetzt wirds ernst
    if (!GetOutContext(c)->GetOutData()->Pr->StartPrint(GetPrinterHeader())) {
      GetOutContext(c)->GetOutData()->Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben
      GetOutContext(c)->GetOutData()->IsPrinting = FALSE ;
      return FALSE;
      }

    int x0old = GetOutContext(c)->GetOutData()->_x0 ; int y0old = GetOutContext(c)->GetOutData()->_y0 ;
    GetOutContext(c)->GetOutData()->xpold = GetOutContext(c)->GetOutData()->_xp ; GetOutContext(c)->GetOutData()->ypold = GetOutContext(c)->GetOutData()->_yp ;
    GetOutContext(c)->GetOutData()->oldscale = GetOutContext(c)->GetOutData()->_scale ;

    // Aufruf der Pre - Prozedur
    //------------------------------------------------------------
    c->ExCuteProc (par->preProc,EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc (par->preProc,EM_RESET | EM_CLEAR);

    // Ermitteln von Druckspezifisichen Daten
    //------------------------------------------------------------
    DBINT FAR *FirstPage = (DBINT FAR *) c->ReadlData (par->FirstPage);
    DBINT FAR *LastPage  = (DBINT FAR *) c->ReadlData (par->LastPage);
    int oldsides = GetOutContext(c)->GetOutData()->_AnzSides ;
    int oldact   = GetOutContext(c)->GetOutData()->_ActSide ;
    DBWIN_ASSERT ((FirstPage != NULL) && (LastPage != NULL));

    DBBOOL FAR *lpas = (DBBOOL FAR *) c->ReadlData(par->AutoScale);
    DBBOOL autoscale = (lpas != NULL) ? ((*lpas) & 0x01) : FALSE ;
    float FAR *lpsc = (float FAR *) c->ReadlData (par->Scale);
    double sc = (lpsc != NULL) ? *lpsc : 1.0 ;
    sc = min(4.0,max(0.25,sc));


    BOOL doNewFrame;
    if (lpas != NULL) {
      if ((*lpas) & 0x0002) doNewFrame = FALSE;
      else                  doNewFrame = TRUE;
      }
    else
      doNewFrame = TRUE;

    RECT rp,rpold;
    GetOutContext(c)->GetOutData()->Pr->PaperSize (&rpold);

    // Und los gehts
    DBINT FAR *lpAnzCopys = (DBINT FAR *) c->ReadlData (par->AnzCopys);
    DBWIN_ASSERT (lpAnzCopys != NULL);
    int AnzCopys = *lpAnzCopys;
    for (int i = 0 ; i < AnzCopys ; i++) {
      // IsPrinting koennte von IsSidePrinted() zurueckgesetzt worden sein !
      GetOutContext(c)->GetOutData()->IsPrinting = TRUE ;
      int side = GetOutContext(c)->GetOutData()->_ActSide = *FirstPage;
      GetOutContext(c)->GetOutData()->_AnzSides = max(GetOutContext(c)->GetOutData()->_AnzSides,*LastPage);
      for ( ; ; ) {
        if (doNewFrame)
          GetOutContext(c)->GetOutData()->Pr->StartFrame ();

        // Seiten - Daten in die Extradaten schreiben, damit das Script 
        // eventuell darauf zugreifen kann ....
        ///////////////////////////////////////////////////////////////
        int s = side + 1;
        GetOutContext(c)->PutDocumentExtraData (DED_PRSIDE,&s,sizeof(s));
        GetOutContext(c)->PutDocumentExtraData (DED_PRANZSIDE,LastPage,sizeof(*LastPage));

        // Drucken der Druckvorlage
        /////////////////////////////////
        GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rpold);
        c->ExCuteProc (par->printProc,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (par->printProc,EM_RESET | EM_CLEAR);

        GetOutContext(c)->RemoveDocumentExtraData (DED_PRSIDE);
        GetOutContext(c)->RemoveDocumentExtraData (DED_PRANZSIDE);


        // Seitenraender neu lesen (die Printprozedure koennte diese
        // verstellt haben ....
        ////////////////////////////////////////////////////////////////////
        CopyRect (&rp,&rpold);
        {
        PaintContext pc(GetOutContext(c)->GetOutData()->Pr);
        pc.Map (1.0);
        rp.left  += pc.XLOGtoPHYS(Rand(c,par->xLeft));
        rp.top   -= pc.YLOGtoPHYS(Rand(c,par->yTop));
        rp.right -= pc.XLOGtoPHYS(Rand(c,par->xRight));
        rp.bottom += pc.YLOGtoPHYS(Rand(c,par->yBottom));
        }

        // Drucken der Daten
        GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rp);
        PaintContext pc(GetOutContext(c)->GetOutData()->Pr);
        GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rp);

        HRGN hRgnClip = CreateRectRgn (rp.left,rp.top,rp.right,rp.bottom);
        SelectClipRgn (pc.hDC,hRgnClip);
        DeleteObject (hRgnClip);

        GetOutContext(c)->SetPrintSideOpt (autoscale,sc);
        GetOutContext(c)->GetOutData()->_ActSide = side;
        GetOutContext(c)->ToPrinter (GetOutContext(c)->GetOutData()->Pr,TRUE,side);

        SelectClipRgn (pc.hDC,NULL);  // Clipping wieder aufheben

        GetOutContext(c)->GetOutData()->Pr->NewFrame ();
        char cdstr[64];
        GetPrivateProfileString ("Config","NewFrameWait","0",
                                    cdstr,sizeof(cdstr),
                                    MYINI
                                );
        int msToWait;
        if (sscanf (cdstr,"%d",&msToWait) != 1)
          msToWait = 0;

        // Endlosschleife
        //------------------
        for ( DWORD t = GetTickCount(); (GetTickCount() < t + msToWait) ; ) ;
        if (side >= *LastPage - 1)
          GetOutContext(c)->GetOutData()->_AnzSides = 0 ;  // IsSidePrinted muss auf jeden Fall FALSE liefern
        if (GetOutContext(c)->IsSidePrinted()) break ;
        else                                   side++;
        }
      }

    GetOutContext(c)->GetOutData()->Pr->SetPrinterArea (&rpold);
    GetOutContext(c)->GetOutData()->_AnzSides = oldsides;
    GetOutContext(c)->GetOutData()->_ActSide = oldact;
    GetOutContext(c)->GetOutData()->_xp = GetOutContext(c)->GetOutData()->xpold ; GetOutContext(c)->GetOutData()->_yp = GetOutContext (c)->GetOutData()->ypold ;
    GetOutContext(c)->GetOutData()->_x0 = x0old ; GetOutContext(c)->GetOutData()->_y0 = y0old ;
    GetOutContext(c)->GetOutData()->_scale = GetOutContext(c)->GetOutData()->oldscale ;
    GetOutContext(c)->GetOutData()->IsPrinting = FALSE ;

    GetOutContext(c)->GetOutData()->Pr->EndPrint();
    GetOutContext(c)->GetOutData()->Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben

    if (!OldInClientTransaction) {
      InClientTransaction = FALSE;
      if (CallCommandInClientTransaction) {
        PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
        CallCommandInClientTransaction = FALSE;
        }
      deleteAllOpenChilds ();
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct InterpreteHdString_param {
  WORD parSize;
  DWORD res;
  DWORD rtxt;
  };
#pragma pack()

BOOL InterpreteHdString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InterpreteHdString_param FAR *par = (InterpreteHdString_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->rtxt));
    if (txt != NULL) {
      GLOBALHANDLE hGPar = GlobalAlloc (GHND,sizeof(ParData));
      ParData FAR *pd = (ParData FAR *) GlobalLock (hGPar);
      pd->hBaseInst = pd->hExtInst = GetOutContext(c);
      GlobalUnlock (hGPar);

      GLOBALHANDLE hGtxt = ConvertText (txt,hGPar);
      GlobalFree (hGPar);
      LPSTR ntxt = LPSTR(GlobalLock (hGtxt));
      c->WritelData (par->res,ntxt,lstrlen(ntxt) + 1,LPSTR(param)-sizeof(WORD));
      GlobalUnlock (hGtxt);
      GlobalFree (hGtxt);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetToolPalette (mdiChild *c,LPVOID param,WORD mode)
  {
  toolbar_cbdata h(c);
  SetToolPalette (&h,param,mode);
  if (h.Extra != NULL) FreeGlobMem (h.Extra);
  return FALSE ;
  }

BOOL BitEditMode (mdiChild *c,LPVOID param,WORD mode)
  {
  toolbar_cbdata h(c);
  SetBitEditMode (&h,param,mode);
  if (h.Extra != NULL) FreeGlobMem (h.Extra);
  return FALSE ;
  }

#pragma pack(1)
struct PresentBitmap_param {
  WORD parSize;
  DWORD pID;
  DWORD x0;
  DWORD y0;
  DWORD w;
  DWORD h;
  DWORD type;
  DWORD mHorz;
  DWORD mVert;
  DWORD plane;
  DWORD color;
  DWORD pict;
  };
#pragma pack()

BOOL PresentBitmap (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RECT r;
    PresentBitmap_param FAR *par = (PresentBitmap_param FAR *) param;
    LPDWORD lppID = LPDWORD (c->ReadlData (par->pID));
    DBWIN_ASSERT (lppID != NULL) ;
    DBINT FAR *lpx0 = (DBINT FAR *)(c->ReadlData (par->x0));
    DBWIN_ASSERT (lpx0 != NULL) ;
    DBINT FAR *lpy0 = (DBINT FAR *)(c->ReadlData (par->y0));
    DBWIN_ASSERT (lpy0 != NULL) ;
    DBINT FAR *lpw = (DBINT FAR *)(c->ReadlData (par->w));
    DBWIN_ASSERT (lpw != NULL) ;
    DBINT FAR *lph = (DBINT FAR *)(c->ReadlData (par->h));
    DBWIN_ASSERT (lph != NULL) ;
    DBINT FAR *lptype = (DBINT FAR *)(c->ReadlData (par->type));
    DBWIN_ASSERT (lptype != NULL) ;
    DBBOOL FAR * lpmHorz = (DBBOOL FAR *) (c->ReadlData (par->mHorz));
    DBWIN_ASSERT (lpmHorz != NULL) ;
    DBBOOL FAR * lpmVert = (DBBOOL FAR *) (c->ReadlData (par->mVert));
    DBWIN_ASSERT (lpmVert != NULL) ;
    BYTE FAR * lppict = (BYTE FAR *) (c->ReadlData (par->pict));
    DBWIN_ASSERT (lppict != NULL) ;

    if ((lppID != NULL) &&
        (lpx0 != NULL) &&
        (lpy0 != NULL) &&
        (lpw != NULL) &&
        (lph != NULL) &&
        (lptype != NULL) &&
        (lpmHorz != NULL) &&
        (lpmVert != NULL) &&
        (lppict != NULL)) {
      r.left = *lpx0;
      r.top = *lpy0;
      r.right = r.left + *lpw;
      r.bottom = r.top + *lph;
      int type = *lptype;
      DWORD plane;
      int color = 0;
      BOOL correct = TRUE ;
      if (type == 1) {
        LPDWORD lpplane = LPDWORD (c->ReadlData (par->plane));
//        DBWIN_ASSERT (lpplane != NULL) ;
        if (lpplane != NULL)
          plane = c->ReadConstLong(par->plane);
        else
          correct = FALSE ;
        }
      if (type != 0) {
        DBINT FAR *lpcolor = (DBINT FAR *)(c->ReadlData (par->color));
        DBWIN_ASSERT (lpcolor != NULL) ;
        if (lpcolor != NULL)
          color = c->ReadConstInt (par->color);
        else
          correct = FALSE ;
        }
      if (correct)
        AddBitmap (&r,type,plane,*lppID,
                  *lpmVert,*lpmHorz,
                  color,lppict);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct PresentText_param {
  WORD parSize;
  DWORD dx;
  DWORD dy;
  DWORD w;
  DWORD anz;
  DWORD txt;
  DWORD color;
  DWORD format;
  DWORD wichtig;
  DWORD wichtigOben;
  };
#pragma pack()

static char leer[] = "";
BOOL PresentText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PresentText_param FAR *par = (PresentText_param FAR *)param;
    DBINT FAR *dx = (DBINT FAR *) c->ReadlData (par->dx);
    DBWIN_ASSERT (dx != NULL) ;
    DBINT FAR *dy = (DBINT FAR *) c->ReadlData (par->dy);
    DBWIN_ASSERT (dy != NULL) ;
    DBINT FAR *w = (DBINT FAR *) c->ReadlData (par->w);
    DBWIN_ASSERT (w != NULL) ;
    DBINT FAR *anz = (DBINT FAR *) c->ReadlData (par->anz);
    DBWIN_ASSERT (anz != NULL) ;
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    if (txt == NULL) txt = leer;
    DBINT FAR *color = (DBINT FAR *) c->ReadlData (par->color);
    DBWIN_ASSERT (color != NULL) ;
    DBINT FAR *format = (DBINT FAR *) c->ReadlData (par->format);
    DBWIN_ASSERT (format != NULL) ;
    DBBOOL FAR *wichtig = (DBBOOL FAR *) c->ReadlData (par->wichtig);
    DBWIN_ASSERT (wichtig != NULL) ;
    DBBOOL FAR *wichtigOben = (DBBOOL FAR *) c->ReadlData (par->wichtigOben);
    DBWIN_ASSERT (wichtigOben != NULL) ;
    AddMergeText (*dx,*dy,*w,*anz,txt,*color,*format,*wichtig,*wichtigOben);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PresentText_param FAR *par = (PresentText_param FAR *)param;
    c->ClearlConnection (par->dx,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dy,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetBaseUnit_param {
  WORD parSize;
  DWORD bu;
  };
#pragma pack()

BOOL GetBaseUnit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetBaseUnit_param FAR *par = (GetBaseUnit_param FAR *) param;
    double bu;
    GetBaseUnit (&bu);
    float fbu = float(bu);
    c->WritelData (par->bu,&fbu,sizeof(fbu),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma pack(1)
struct SetEditMode_param {
  WORD parSize;
  DWORD obj;         // Dialog-Eingabefeld
  DWORD fieldmode;   // Modus z.b. FM_NOGERMANCHARS, FM_DECIMAL, ...
  };
#pragma pack()

BOOL SetEditMode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetEditMode_param FAR *par = (SetEditMode_param FAR *) param;
    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));

    // aktuellen Modus lesen, mit dem neuen ODER verknuepfen und setzen!
    DWORD fieldmode = WWGetMode ((*e)->hWndEdit);
    fieldmode |= c->ReadConstLong(par->fieldmode);
    WWSetMode ((*e)->hWndEdit, fieldmode);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetFormatMap_param {
  WORD parSize ;
  DWORD Tool;
  DWORD i[2];
  int AnzPairs ()
    {
    return (parSize - sizeof(*this)) / sizeof(i) + 1 ;
    }
  };
#pragma pack()

void ReadMaps (mdiChild *c,int FAR *res,SetFormatMap_param FAR *par)
  {
  for (int i = 0 ; i < 2 * par->AnzPairs () ; i++) {
    DBINT FAR *lpi = (DBINT FAR *) c->ReadlData (par->i[i]) ;
    res[i] = *lpi ;
    }
  }

BOOL SetEditFormatMaps (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFormatMap_param FAR *par = (SetFormatMap_param FAR *) param;
    LPTOOLEDIT FAR *e = (LPTOOLEDIT FAR *) c->ReadlData (par->Tool);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));

    // aktuellen Modus lesen, mit dem neuen ODER verknuepfen und setzen!
    int maps[256];
    ReadMaps (c,maps,par);
    WWSetFormatMap ((*e)->hWndEdit, maps, par->AnzPairs());
    }
  return FALSE ;
  }

BOOL SetObjFormatMaps (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFormatMap_param FAR *par = (SetFormatMap_param FAR *) param;
    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->Tool);
    DBWIN_ASSERT ((ed != NULL) && (*ed != NULL));

    // aktuellen Modus lesen, mit dem neuen ODER verknuepfen und setzen!
    int maps[256];
    ReadMaps (c,maps,par);
    (*ed)->field->SetFormatMaps (maps, par->AnzPairs());
    }
  return FALSE ;
  }

BOOL SetObjModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    short FAR *lpModify = (short FAR *) c->ReadlData (par->Modify);
    DBBOOL FAR *lpSet_Clear = (DBBOOL FAR *) c->ReadlData (par->Set_Clear);

    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL) && (lpModify != NULL) && (lpSet_Clear != NULL))
      (*ed)->field->FormatSelection (*lpModify,*lpSet_Clear);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;
    c->ClearlConnection (par->Modify,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ColorObjSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    DWORD FAR *lpColor = (DWORD FAR *) c->ReadlData (par->Modify);

    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL) && (lpColor != NULL))
      (*ed)->field->ColorSelection (*lpColor);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;
    c->ClearlConnection (par->Modify,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetToolModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    short FAR *lpModify = (short FAR *) c->ReadlData (par->Modify);
    DBBOOL FAR *lpSet_Clear = (DBBOOL FAR *) c->ReadlData (par->Set_Clear);

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL) && (lpModify != NULL) && (lpSet_Clear != NULL))
      WWFormatSelection ((*ed)->hWndEdit,*lpModify,*lpSet_Clear);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;
    c->ClearlConnection (par->Modify,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ColorToolSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    DWORD FAR *lpColor = (DWORD FAR *) c->ReadlData (par->Modify);

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL) && (lpColor != NULL))
      WWColorSelection ((*ed)->hWndEdit,*lpColor);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;
    c->ClearlConnection (par->Modify,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL bToolSelectionInString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldModify_param FAR *par = (SetFieldModify_param FAR *) param;

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    if ((ed != NULL) && (*ed != NULL))
      return WWSelectionInString ((*ed)->hWndEdit);
    else
      return FALSE ;
    }
  else
    return FALSE ;
  }

BOOL GetObjModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->tool);
    if ((ed != NULL) && (*ed != NULL))
      (*ed)->SetModifyParam (par->StrId);
    }
  if (mode & EM_FIXCONNECTION) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    c->SetlConnection (par->tool,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    c->ClearlConnection (par->tool,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetToolModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->tool);
    if ((ed != NULL) && (*ed != NULL))
      (*ed)->SetModifyParam (par->StrId);
    }
  return FALSE ;
  }

BOOL GetObjColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->tool);
    if ((ed != NULL) && (*ed != NULL))
      (*ed)->SetColorParam (par->StrId);
    }
  if (mode & EM_FIXCONNECTION) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    c->SetlConnection (par->tool,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    c->ClearlConnection (par->tool,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetToolColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFieldCallback_param FAR *par = (GetFieldCallback_param FAR *) param;
    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->tool);
    if ((ed != NULL) && (*ed != NULL))
      (*ed)->SetColorParam (par->StrId);
    }
  return FALSE ;
  }

#pragma pack(1)
struct PrinterDirect_param {
  WORD parSize;
  DWORD dcobj;
  DWORD str;
  DWORD title;
  };
#pragma pack()

BOOL OpenPrinterDirect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PrinterDirect_param FAR *par = (PrinterDirect_param FAR *) param;
    LPSTR szDevice = (LPSTR) c->ReadlData (par->str);
    LPSTR title = (LPSTR) c->ReadlData (par->title);
    char szDefDevice[64];
    if ((szDevice == NULL) || (!*szDevice)) {
      GetProfileString ("windows","device","",szDefDevice,64);
      szDevice = (LPSTR)_fstrtok (szDefDevice,",");
      }
    char szPrinter[64];
    GetProfileString ("devices",szDevice,"",szPrinter,64);
    LPSTR szDriver = (LPSTR)_fstrtok (szPrinter, ",");
    LPSTR szOutput = (LPSTR)_fstrtok (NULL,      ", ");
    HDC PrDC = CreateDC (szDriver,szDevice,szOutput,NULL);
//    HDC PrDC = CreateDC("BASE9","Generic Epson FX-85 9pin","FILE:",NULL);
    DOCINFO di;
    lmemset(&di,'\0',sizeof(DOCINFO));
    di.cbSize = 10;
    if ((title != NULL) && (*title != '\0'))
      di.lpszDocName = title;
    else
      di.lpszDocName = "Druck ...";
    di.lpszOutput = NULL;
    StartDoc(PrDC,&di);
    c->WritelData (par->dcobj,&PrDC,sizeof(HDC),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL PrintDirect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PrinterDirect_param FAR *par = (PrinterDirect_param FAR *) param;
    HDC FAR *lphDC = (HDC FAR *) c->ReadlData (par->dcobj);
    LPSTR text = (LPSTR) c->ReadlData (par->str);
    if ((text != NULL) && (*text != '\0') &&
        (lphDC != NULL) && (*lphDC != NULL)) {
      struct PrEsc {
        WORD len;
        char txt[1];
        } ;
      WORD textlen = lstrlen(text);
      PrEsc FAR *esc = (PrEsc FAR *)GetGlobMem(textlen + 3);
      esc->len = textlen;
      lstrcpy(esc->txt,text);
      Escape(*lphDC,PASSTHROUGH,NULL,(LPSTR)esc,NULL);
      FreeGlobMem(esc);
      }
    }
  return FALSE ;
  }

BOOL ClosePrinterDirect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PrinterDirect_param FAR *par = (PrinterDirect_param FAR *) param;
    HDC FAR *lphDC = (HDC FAR *) c->ReadlData (par->dcobj);
    if ((lphDC != NULL) && (*lphDC != NULL)) {
      EndDoc(*lphDC);
      DeleteDC(*lphDC);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct CRtoCRLF_param {
  WORD parSize;
  DWORD dst;
  DWORD src;
  };
#pragma pack()

BOOL CRtoCRLF (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CRtoCRLF_param FAR *par = (CRtoCRLF_param FAR *) param ;
    LPSTR src = LPSTR(c->ReadlData (par->src));
    if ((src != NULL) && (*src != '\0')) {
      LPSTR dst = LPSTR(GetGlobMem ((lstrlen(src) * 2) + 1)) ;
      LPSTR h = dst;
      while (*src) {
        if ((*h++ = *src++) == '\r')
          *h++ = '\n';
        }
      *h = '\0';
      c->WritelData (par->dst,dst,lstrlen(dst) + 1,LPSTR(param)-sizeof(WORD));
      FreeGlobMem(dst);
      }
    else
      c->DellData (par->dst,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    CRtoCRLF_param FAR *par = (CRtoCRLF_param FAR *) param ;
    c->SetlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CRtoCRLF_param FAR *par = (CRtoCRLF_param FAR *) param ;
    c->ClearlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//---------------------------------------------------------------------------
// SetToolObjectColor
// .... aendert die Farbe eines Dialog-Elementes
//---------------------------------------------------------------------------
#pragma pack(1)
struct FAR SetObjectColor_param {
  WORD parSize;
  DWORD tool;     // Objekt des Dialog-Elementes
  DWORD color;    // Farbe des Dialog-Elementes
  };
#pragma pack()

BOOL SetToolObjectColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetObjectColor_param FAR *par = (SetObjectColor_param FAR *) param ;
    DWORD FAR *color = (DWORD FAR *) c->ReadlData (par->color);
    if (color != NULL) {
      toolbar_cbdata h(c);                      // private Daten
      SetToolObjectColor (par->tool, &h, COLORREF(*color));
      if (h.Extra != NULL) FreeGlobMem (h.Extra);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    SetObjectColor_param FAR *par = (SetObjectColor_param FAR *) param ;
    c->ClearlConnection (par->color, LPSTR(param)-sizeof(WORD));
    }

  if (mode & EM_FIXCONNECTION) {
    SetObjectColor_param FAR *par = (SetObjectColor_param FAR *) param ;
    c->SetlConnection (par->color, LPSTR(param)-sizeof(WORD));
    }

  return FALSE ;
  }

//---------------------------------------------------------------------------
// GetToolCoordinates
// .... Gibt die Koordinaten eines Tools in Dialog-Einheiten zurueck
//----------------------------------------------------------------------------------
#pragma pack(1)
struct FAR GetToolCoordinates_param {
  WORD parSize;
  DWORD tool;     // Objekt des Dialog-Elementes
  DWORD x;
  DWORD y;
  DWORD w;
  DWORD h;
  DWORD absolute; // bezogen auf den ganzen Schirm oder innerhalb des Dialoges 
  };
#pragma pack()

BOOL GetToolCoordinates (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetToolCoordinates_param FAR *par = (GetToolCoordinates_param FAR *) param ;
    DBBOOL FAR *lpabsolute = (DBBOOL FAR *) c->ReadlData (par->absolute);
    BOOL absolute = (lpabsolute != NULL) ? *lpabsolute : TRUE;
    toolbar_cbdata h(c);                      // private Daten
    int x, y, width, height;
    GetToolCoordinates (par->tool, &h, &x, &y, &width, &height, absolute);
    c->WritelData (par->x, &x, sizeof(x), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->y, &y, sizeof(y), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->w, &width, sizeof(width), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->h, &height, sizeof(height), LPSTR(param)-sizeof(WORD));
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }

  return FALSE ;
  }

//---------------------------------------------------------------------------
// SetDialogPos
// .... Setzt das Positionsobjekt fuer einen Dialog (obj PosRef)
//---------------------------------------------------------------------------
#pragma pack(1)
struct FAR SetDialogPos_param {
  WORD parSize;
  DWORD PosRef;     // Positions-Objekt des Dialog-Elementes
  DWORD x;
  DWORD y;
  };
#pragma pack()

BOOL SetDialogPos (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetDialogPos_param FAR *par = (SetDialogPos_param FAR *) param ;

    DBINT FAR *lpx = (DBINT FAR *) c->ReadlData (par->x);
    DBINT FAR *lpy = (DBINT FAR *) c->ReadlData (par->y);

    int x = max ((lpx != NULL) ? *lpx : 0, 0);
    int y = max ((lpy != NULL) ? *lpy : 0, 0);

    POPUPPOS pos;
    pos.ptPos.x = x;
    pos.ptPos.y = y;

    c->WritelData (par->PosRef, &pos, sizeof(pos), LPSTR(param)-sizeof(WORD));
    }

  return FALSE ;
  }

#pragma pack(1)
struct HideScreen_param {
  WORD  parSize;
  DWORD Screen;
  };
#pragma pack()

BOOL HideScreen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    HideScreen_param FAR *par = (HideScreen_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->Screen);
    DBWIN_ASSERT ((scl != NULL) && (*scl != NULL)) ;
    EnableWindow ((*scl)->disabledWindow,TRUE);
    if ((*scl)->disabledWindow != WBase::hFrameWin)
      EnableWindow (WBase::hFrameWin,TRUE);
    ShowWindow ((*scl)->hWnd,SW_HIDE);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    HideScreen_param FAR *par = (HideScreen_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->Screen);
    DBWIN_ASSERT ((scl != NULL) && (*scl != NULL)) ;
    EnableWindow ((*scl)->disabledWindow,FALSE);
    if ((*scl)->disabledWindow != WBase::hFrameWin)
      EnableWindow (WBase::hFrameWin,FALSE);
    ShowWindow ((*scl)->hWnd,SW_SHOWNORMAL);
    }
  return FALSE ;
  }

#pragma pack(1)
struct OnScreenButtonDown_param {
  WORD  parSize;
  DWORD Screen;
  DWORD DownPos;        // Mausposition beim Druecken
  DWORD LeftDownProc;   // Prozedur fuer linke Maustaste
  DWORD RightDownProc;  // Prozedur fuer rechte Maustaste (optional)
  };
#pragma pack()

BOOL OnScreenButtonDown (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    OnScreenButtonDown_param FAR *par = (OnScreenButtonDown_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->Screen);
    DBWIN_ASSERT ((scl != NULL) && (*scl != NULL)) ;
    toolbar_cbdata h(c);

    DWORD RightDownProc = 0L;         // vorsichtshalber vorbelegen!!!
    if (par->parSize >= sizeof(*par))
      RightDownProc = par->RightDownProc;
      
    SetMouseDownProc (*scl, par->LeftDownProc, RightDownProc,
                            par->DownPos, par, &h, sizeof(h));
    }
  else if (mode & (EM_CLEAR | EM_RESET)) {
    OnScreenButtonDown_param FAR *par = (OnScreenButtonDown_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->Screen);
    if ((scl != NULL) && (*scl != NULL))
      SetMouseDownProc (*scl,0L,0L,0L,NULL,NULL,0);
    }
  return FALSE ;
  }

#pragma pack(1)
struct InsertStrAtCaret_param {
  WORD parSize;
  DWORD field;
  DWORD Str;
  };
#pragma pack()
BOOL InsertStrAtCaretObj (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;

    BOOL oldBlockIsActive = BlockIsActive;
    BlockIsActive = FALSE;
    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->field);
    LPSTR str = LPSTR (c->ReadlData (par->Str));
    if ((ed != NULL) && (*ed != NULL) && ((*ed)->field != NULL) && (str != NULL)) 
      InsertAtCaret ((*ed)->field,str);
    BlockIsActive = oldBlockIsActive;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;
    c->ClearlConnection (par->Str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL InsertStrAtCaretTool (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    LPSTR str = LPSTR (c->ReadlData (par->Str));
    if ((ed != NULL) && (*ed != NULL) && (str != NULL)) 
      WWInsertAtCaret ((*ed)->hWndEdit,str);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;
    c->ClearlConnection (par->Str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetStrAtCaretObj (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;

    BOOL oldBlockIsActive = BlockIsActive;
    BlockIsActive = FALSE;
    LPFRMFIELD FAR *ed = (LPFRMFIELD FAR *) c->ReadlData (par->field);
    LPSTR str = LPSTR (c->ReadlData (par->Str));
    if ((ed != NULL) && (*ed != NULL) && ((*ed)->field != NULL) && (str != NULL)) 
      SetAtCaret ((*ed)->field,str);
    BlockIsActive = oldBlockIsActive;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;
    c->ClearlConnection (par->Str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetStrAtCaretTool (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    LPSTR str = LPSTR (c->ReadlData (par->Str));
    if ((ed != NULL) && (*ed != NULL) && (str != NULL)) 
      WWSetAtCaret ((*ed)->hWndEdit,str);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    InsertStrAtCaret_param FAR *par = (InsertStrAtCaret_param FAR *) param;
    c->ClearlConnection (par->Str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


#pragma pack(1)
struct SetCaretTo_param {
  WORD parSize;
  DWORD field;
  DWORD line;
  DWORD col;
  };
#pragma pack()
BOOL SetCaretTo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetCaretTo_param FAR *par = (SetCaretTo_param FAR *) param;

    LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (par->field);
    DBINT FAR *lpLine = (DBINT FAR *) c->ReadlData (par->line);
    DBINT FAR *lpCol = (DBINT FAR *) c->ReadlData (par->col);

    if ((ed != NULL) && (*ed != NULL) && (lpLine != NULL) && (lpCol != NULL)) 
      WWSetCaretTo ((*ed)->hWndEdit,*lpLine,*lpCol);
    }
  return FALSE ;
  }

#pragma pack(1)
struct AppendContextMenu_param {
  WORD parSize;
  DWORD toolObj;
  DWORD MenuText;
  DWORD MenuProc;
  DWORD Flags;
  };
#pragma pack()
BOOL AppendContextMenu (mdiChild *c,LPVOID param,WORD mode)
  {
  AppendContextMenu_param FAR *par = (AppendContextMenu_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    toolbar_cbdata h(c);                      // private Daten

    LPSTR MenuText = (LPSTR) c->ReadlData (par->MenuText);
    if (MenuText == NULL)
      DBWIN_ASSERT_TEXT (FALSE, "Ung�ltiger Men�bezeichner im kontextsensitiven Men�");

    UINT Flags = 0;
    DBINT FAR *lpFlags = (DBINT FAR *)(c->ReadlData (par->Flags));
    if (lpFlags == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "ung�ltiges Men�flag im kontextsensitiven Men�");
      }
    else
      Flags = *lpFlags;

    AppendContextMenu (par->toolObj, par, &h, sizeof(h), MenuText, 
                       par->MenuProc, Flags, mode);
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    toolbar_cbdata h(c);                      // private Daten
    RemoveContextMenu (par->toolObj, &h);
    c->ClearlConnection (par->MenuText, LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Flags, LPSTR(param)-sizeof(WORD));
    if (h.Extra != NULL) FreeGlobMem (h.Extra);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->MenuText, LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Flags, LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct GetMouseObjectStatus_param {
  WORD parSize;
  DWORD actObj;
  };
#pragma pack()
BOOL GetMouseObject (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetMouseObjectStatus_param FAR *par = (GetMouseObjectStatus_param FAR *) param;
    tool FAR *h = CTOOL_GetActMouseObject ();
    c->WritelData (par->actObj,&h,sizeof(h),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetSysColor_param {
  WORD parSize;
  DWORD res;
  DWORD Item;
  };
#pragma pack()
BOOL GetSysColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetSysColor_param FAR *par = (GetSysColor_param FAR *) param;
    DBINT FAR *lpItem = (DBINT FAR *) c->ReadlData (par->Item);
    if (lpItem != NULL) {
      DWORD res = GetSysColor (*lpItem);
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
      }
    }
  if (mode & EM_CLEAR) {
    GetSysColor_param FAR *par = (GetSysColor_param FAR *) param;
    c->ClearlConnection (par->Item,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetResFactor_param {
  WORD  parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetResFactor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetResFactor_param FAR *par = (GetResFactor_param FAR *) param;
    double cfact;
    GetResolutionCF (&cfact);

    float res = float(cfact);
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL SetPrinterCaption (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetResFactor_param FAR *par = (GetResFactor_param FAR *) param;
    LPSTR Cap = LPSTR (c->ReadlData (par->res));
    SetPrinterHeader (Cap);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetResFactor_param FAR *par = (GetResFactor_param FAR *) param;
    c->ClearlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//============================================================================
//
// HTMLHELP
//
//============================================================================
static BOOL bHtmlInitialized = FALSE;
DWORD dwCookie;

BOOL InitHtmlHelp (LPSTR lpszchmFile, LPSTR lpszHtmlHome, 
                   LPSTR lpszHtmlIndex, LPSTR lpszHtmlKey)
  {
  HINSTANCE inst = LoadLibrary("HHCTRL.OCX");
  if (inst != NULL) {
  //  (FARPROC&) htmlhelp = GetProcAddress(inst, "HtmlHelpA");
    SetHtmlHelp (GetProcAddress(inst, "HtmlHelpA"));
    HWND wnd;


    htmlhelp (NULL, 
              NULL, 
              HH_INITIALIZE, 
              (DWORD)&dwCookie) ; // Cookie returned by Hhctrl.ocx.

    HH_WINTYPE hhWinType;   
    // Initialize all structure members to zero.
    ZeroMemory(&hhWinType, sizeof(HH_WINTYPE));

    // Define a custom message for use with idNotify.
    // You are responsible for ensuring that this ID
    // does not conflict with other Windows/MFC messages.
    #define IDD_HELPTAB 69999   

    // Set the size of the structure.
    hhWinType.cbStruct = sizeof(HH_WINTYPE);

    // Name des Fensters
    hhWinType.pszType = "MyWindowName";

    // Indicate which fields in structure are valid.
    hhWinType.fsValidMembers = HHWIN_PARAM_STYLES |
                              HHWIN_PARAM_PROPERTIES | HHWIN_PARAM_RECT |
                              HHWIN_PARAM_TB_FLAGS | HHWIN_PARAM_NAV_WIDTH |
                              HHWIN_PARAM_SHOWSTATE | HHWIN_PARAM_TABPOS |   
                              HHWIN_PARAM_CUR_TAB;


    // Set up the properties of the HTML window:
    // tripane window, sync topic with index/TOC, and so forth.
    // NOTE: fsValidMembers - HHWIN_PARAM_PROPERTIES must be set.
    hhWinType.fsWinProperties = HHWIN_PROP_TRI_PANE | HHWIN_PROP_AUTO_SYNC | 
                                HHWIN_PROP_TAB_SEARCH | HHWIN_PROP_TAB_ADVSEARCH;

    // Put BACK, HOME, FORWARD, and EXPAND buttons on toolbar pane.
    // NOTE: fsValidMembers - HHWIN_PARAM_TB_FLAGS must be set.
    hhWinType.fsToolBarFlags = HHWIN_BUTTON_BACK | HHWIN_BUTTON_HOME | 
                              HHWIN_BUTTON_FORWARD | HHWIN_BUTTON_EXPAND | HHWIN_BUTTON_SEARCH;

    // The file is in the right pane. The full path is not needed.
    hhWinType.pszFile = lpszHtmlHome;

    // Full Paths or CHM locations of various files (if used).
    // To specify that a file is within a CHM, use the following
    // syntax: "CHMFileName.chm::\\FileName.xxx"   // Home Page:
    hhWinType.pszHome = lpszHtmlHome;   // Table of Contents:
    hhWinType.pszToc = lpszHtmlIndex;   // Index:
    hhWinType.pszIndex = lpszHtmlKey;   // Keywords:

    // Expansion width of navigation pane (left pane):
    // NOTE: fsValidMembers - HHWIN_PARAM_NAV_WIDTH must be set.
    hhWinType.iNavWidth = 175;   // Initial display state:

    // NOTE: fsValidMembers - HHWIN_PARAM_SHOWSTATE must be set.
    hhWinType.nShowState = SW_RESTORE;   // TOC should be activated.

    // NOTE: fsValidMembers - HHWIN PARAM_CUR_TAB must be set.
    hhWinType.curNavType = HHWIN_NAVTYPE_TOC;   // Tabs on top.

    // NOTE: fsValidMembers - HHWIN_PARAM_TABPOS must be set.
    hhWinType.tabpos = HHWIN_NAVTAB_TOP;   
  
    // ID to use in WPARAM in WM_NOTIFY:
    hhWinType.idNotify = IDD_HELPTAB;   
  
    // Title of Help Window:
    hhWinType.pszCaption= "My Title";


    wnd = htmlhelp(WBase::hFrameWin, lpszchmFile,
                  HH_SET_WIN_TYPE, (DWORD) &hhWinType);
    return TRUE ;
    }
  else
    return FALSE ;
  }



#pragma pack(1)
struct htmlhelpinit_param {
  WORD parSize;
  DWORD chmFile;
  DWORD HtmlHome;
  DWORD HtmlIndex;
  DWORD HtmlKey;
  };
#pragma pack()

BOOL HtmlHelpInit (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    htmlhelpinit_param FAR *par = (htmlhelpinit_param FAR *) param;

    LPSTR lpszchmFile = (LPSTR)c->ReadlData (par->chmFile);

    LPSTR lpszHtmlHome = (LPSTR)c->ReadlData (par->HtmlHome);
    LPSTR lpszHtmlIndex = (LPSTR)c->ReadlData (par->HtmlIndex);
    LPSTR lpszHtmlKey = (LPSTR)c->ReadlData (par->HtmlKey);

    if (!(lpszchmFile && *lpszchmFile))
      DBWIN_ASSERT_TEXT (FALSE, "Ung�ltige Parameter f�r die HTML-Hilfe");

    if (!bHtmlInitialized) {
      bHtmlInitialized = InitHtmlHelp (lpszchmFile, lpszHtmlHome, lpszHtmlIndex, lpszHtmlKey);
      }

    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    }

  return FALSE ;
  }


#pragma pack(1)
struct htmlhelp_param {
  WORD parSize;
  DWORD chmFile;
  DWORD HtmlFile;
  };
#pragma pack()

BOOL CallHtmlHelp (mdiChild *c, LPVOID param, WORD mode)
  {
  if (!bHtmlInitialized)
    return FALSE;
  if (mode & EM_LOAD) {
    htmlhelp_param FAR *par = (htmlhelp_param FAR *) param;

    LPSTR lpszchmFile = (LPSTR)c->ReadlData (par->chmFile);
    LPSTR lpszHtmlFile = (LPSTR)c->ReadlData (par->HtmlFile);

    if (!((lpszchmFile && *lpszchmFile) && (lpszHtmlFile && *lpszHtmlFile)))
      DBWIN_ASSERT_TEXT (FALSE, "Ung�ltige Parameter f�r die HTML-Hilfe");

//    wnd = htmlHelp(hWnd, "h:\\dokumente\\onlinehilfe\\handbuch.chm::/cw.htm",
//             HH_DISPLAY_TOPIC, NULL);


    SetHtmlContext (lpszchmFile, lpszHtmlFile);

//    wnd = htmlHelp(hWnd, HtmlFile, HH_DISPLAY_TOPIC, NULL);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
/*
#ifdef WIN32
    SetHelpContextNr (-1);
#else
    SetHelpContextNr (1);
    SetHelpFile ("DDS.HLP");
#endif
*/
    }

  return FALSE ;
  }
