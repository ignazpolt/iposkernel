//
//  $Header:   P:/marille/clinicum/ctool/rev/barelem.cpv   1.148   03 Jun 2000 13:37:24   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/barelem.cpv  $
// 
//    Rev 1.148   03 Jun 2000 13:37:24   Gerhold
// Hotkeydarstellung verbessert
// 
//    Rev 1.147   26 Apr 2000 20:16:58   Martin
// PageTool um optionalen Parameter erweitert
// 
//    Rev 1.146   10 Sep 1999 15:09:40   Wolfgang
// 1.) Bei ToolTime vor Zugriff auf Format abfragen ob's eins gibt.
// 
//    Rev 1.145   04 Aug 1999 18:28:10   Wolfgang
// 1.) Datum/Zeit +, - etc. Umbau von OnChar auf IsCharCallbackInstalled.
// 2.) skipNextChar eingebaut.
// 
//    Rev 1.144   28 Jul 1999 16:50:22   Wolfgang
// 1.) Datum mittels (h)eute,(g)estern,(m)orgen,(+),(-) setzbar.
// 2.) Zeit mittels (j)etzt,(+),(-) setzbar.
// 3.) F2 beruecksichtigt bei Zeit auch Format (ueber GetText).
// 
//    Rev 1.143   15 Jun 1999 16:22:00   THOMAS
// 1.) TimeNow durch Now ersetzt.
// 
//    Rev 1.142   11 Jan 1999 08:17:42   Hannes
// ToolEdit: F2 -> Aufruf des Menues
// 
//    Rev 1.141   18 Nov 1998 15:52:44   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.140   09 Oct 1998 18:08:10   Hannes
// Farben in Strings
// 
//    Rev 1.139   05 Oct 1998 11:05:58   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.138   15 Sep 1998 20:06:50   Martin
// AnimationBitmap und TransparentBitmap auf Palette umgestellt
// 
//    Rev 1.137   14 Sep 1998 03:26:10   Hannes
// Update Listen / ToolEdits
// 
//    Rev 1.136   01 Sep 1998 22:10:28   Hannes
// Update von ToolEdit / Position
// 
//    Rev 1.135   28 Aug 1998 17:30:08   Martin
// >= statt > (bei AnimationBitmap)
// 
//    Rev 1.134   17 Aug 1998 19:24:06   Wolfgang
// 1.) In OnChange int durch DBINT ersetzt.
// 
//    Rev 1.133   12 Aug 1998 11:49:30   Gerhold
// Verbesserungen in ::AddToolTip  ("Hilfe" und kurze Hilfetexte weg)
// 
//    Rev 1.132   04 Aug 1998 15:51:50   Gerhold
// AddToolTip muss auch in MoveTool aufgerufen werden, um die
// ToolRect Aenderungen zu uebernehmen
// 
//    Rev 1.131   03 Aug 1998 20:49:30   Martin
// auch noch doppelte FixConnections raus (Grrmtjfx !)
// 
//    Rev 1.130   03 Aug 1998 17:53:14   Martin
// doppelte ClearConnections bei StaticTool raus
// 
//    Rev 1.129   22 Jul 1998 12:37:46   Wolfgang
// 1.) prfloat kann jetzt auch bei gr�sseren negativen Zahlen ein - an.
// 
//    Rev 1.128   10 Jul 1998 15:12:26   Hannes
// Verbessertes Disable - Verhalten der Combo - Edit Felder
// 
//    Rev 1.127   10 Jul 1998 09:09:48   Hannes
// 
//    Rev 1.126   09 Jul 1998 09:06:56   Hannes
// Combo - Edits disablen
// 
//    Rev 1.125   07 Jul 1998 18:28:14   Hannes
// %f bei negativen Zahlen (ToolFloat)
// 
//    Rev 1.124   02 Jul 1998 16:59:04   Hannes
// Erweiterte Sonderzeichen
// 
//    Rev 1.123   29 Jun 1998 19:04:42   Hannes
// +,- in die Liste der LastPressedChar aufgenommen
// 
//    Rev 1.122   29 Jun 1998 17:25:36   Gerhold
// FixConnectioj auf Hotkey
// 
//    Rev 1.121   11 Jun 1998 12:08:02   Hannes
// Checkbox: SIZEOF(DBBOOL)
// 
//    Rev 1.120   11 Jun 1998 23:08:52   Martin
// PageTool reagiert jetzt auf UPDATES auf die Position
// 
//    Rev 1.119   18 May 1998 16:46:00   Gerhold
// Bei Tooltime::FixConnection und Reset war noch Bloedsinn
// 
//    Rev 1.118   15 May 1998 10:40:38   Gerhold
// ToolTime erweitert auf szTimeFormat
// 
//    Rev 1.117   04 May 1998 15:33:24   Hannes
// Update auf Position bei Tooledits und Statictools
// 
//    Rev 1.116   28 Apr 1998 11:18:52   Gerhold
// ToolTime mit Formatangabe
// 
//    Rev 1.115   13 Mar 1998 17:50:42   Hannes
// Abmessungen von Statictools mit negativen Koordinaten
// 
//    Rev 1.114   05 Mar 1998 13:00:56   Hannes
// Und wieder gehts weiter mit Toolbar Fehlern
// 
//    Rev 1.113   23 Feb 1998 19:59:42   Hannes
// No change.
// 
//    Rev 1.112   20 Feb 1998 12:33:56   Hannes
// DPToLP
// 
//    Rev 1.111   18 Feb 1998 10:28:06   Hannes
// MoveTool von ComboButton: TBActive
// 
//    Rev 1.110   16 Feb 1998 19:10:50   Hannes
// Weitere Fehler in MoveTool
// 
//    Rev 1.109   01 Feb 1998 15:41:16   Gerhold
// Tooltip-Verbesserungen
// 
//    Rev 1.108   16 Jan 1998 13:27:36   Gerhold
// Vorbereitung auf 32-Bit ToolTips
// 
//    Rev 1.107   12 Jan 1998 18:13:34   Hannes
// WMC_GETTEXT
// 
//    Rev 1.106   05 Dec 1997 17:48:36   Hannes
// Datumseingabe disablen
// 
//    Rev 1.105   01 Dec 1997 19:39:30   Hannes
// Diverse Anpassungen, Format variabel
// 
//    Rev 1.103   19 Nov 1997 18:47:24   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.102   30 Oct 1997 08:42:22   Hannes
// Fehlerkorrektur Timer, ',' bei ToolFloats
// 
//    Rev 1.101   19 Sep 1997 12:54:16   Gerhold
// Toolbar und SetOnSetFocus wurden um KillFocus (Proc) erweitert
// 
//    Rev 1.100   08 Sep 1997 10:47:18   Gerhold
// GetHKText fuer 32 Bit ... Hotkeys in Buttons werden wieder unterstrichen
// 
//    Rev 1.99   03 Sep 1997 15:14:10   GERHOLD
// DrawDisabledBmp bei PushButton und TextPushButton
// 
//    Rev 1.98   02 Sep 1997 16:26:52   gerhold
// DrawButtonEx ... fuer neues Aussehen der Knoepfe unter WIN95 u. NT
// 
//    Rev 1.97   29 Aug 1997 16:24:56   gerhold
// ::tool  erhaelt ein InitHotKey()
// 
//    Rev 1.96   21 Aug 1997 16:22:14   Martin
// PageTool: Seitennummer erst beim loslassen der Maustaste schreiben
// (keine Updates waehrend capturing erlaubt !)
// 
//    Rev 1.95   13 Aug 1997 13:52:50   Gerhold
// PushButton ... FixConnection auf _x, _y
// 
//    Rev 1.94   01 Aug 1997 10:26:46   Martin
// StaticTool: sollte jetzt auf Updates von x oder y reagieren
// 
//    Rev 1.93   29 Jul 1997 12:59:42   gerhold
// TextPushButton::GetRect ... die Anzahl der angezeigten Textzeilen wird an
//                             die Hoehe des Knopfes angepasst
// 
//    Rev 1.92   27 Jun 1997 20:07:50   Martin
// 
//    Rev 1.91   27 Jun 1997 19:38:20   HANNES
// PageTool:: SetData mit sizeof(DBINT)
// 
//    Rev 1.90   10 Apr 1997 11:38:44   Hannes
// Prototyp von WWNextExplicit hat sich geaendert
// 
//    Rev 1.89   21 Mar 1997 11:27:04   Hannes
// IsCharCallbackInstalled
// 
//    Rev 1.88   14 Mar 1997 09:45:50   gerhold
// Versuch der neuen Knopf-Stile (windows 95 like)
// 
//    Rev 1.87   28 Feb 1997 15:00:38   Gerhold
// Erweiterung der kontextsensitiven Menus durch Scriptbefehl
// 
//    Rev 1.86   19 Feb 1997 12:04:50   Hannes
// Invalidate beim UpDown
// 
//    Rev 1.85   27 Jan 1997 09:39:40   HANNES
// 
//    Rev 1.84   08 Jan 1997 17:36:58   HANNES
// Feldlaengebegrenzung
// 
//    Rev 1.83   08 Nov 1996 13:25:18   HANNES
// Verbesserte Nummerneingabe
// 
//    Rev 1.82   03 Nov 1996 15:52:42   GERHOLD
// im TextCheckButton ist jetzt der Hotkeybuchstabe sichtbar (GetHKText)
// 
//    Rev 1.81   24 Sep 1996 18:54:18   GERHOLD
// Abfrage ob IsEnabled bei ToolEdit::OnRButtonDown
// 
//    Rev 1.80   18 Sep 1996 20:47:48   HANNES
// 
//    Rev 1.79   05 Sep 1996 13:59:20   GERHOLD
// ToolEdit ... Menueintraege bei der rechten Maustaste sind jetzt nur
//              verfuegbar, wenn Feld selektiert oder Zwischenablage Daten hat.
// 
//    Rev 1.78   03 Sep 1996 10:00:06   HANNES
// barelem zerteilt
// 
//    Rev 1.77   17 Aug 1996 18:13:04   GERHOLD
// Die Hotkeys werden direkt im Menu angezeigt
// 
//    Rev 1.76   25 Jul 1996 19:54:40   GERHOLD
// WIN32 CharUpper;  rechte Maustaste .. Menus disabled wenn kein Hilfetext
// 
//    Rev 1.75   21 Jun 1996 16:34:18   GERHOLD
// PageTool (DrawPage) ... Da wurde statt einem Fensterhandle der DC uebergeben!
// 
//    Rev 1.74   16 Jun 1996 18:40:58   GERHOLD
// int -> DBINT, BOOL -> DBBOOL
// CapDC, MemDC gibts in der Klasse nicht mehr (anfordern nur wenn notwendig)
// rechte Maustaste (OnRButtonDown, OnCommand)
// 
//    Rev 1.72   11 Apr 1996 09:00:42   GERHOLD
// ToolEdit::SetObjectColor .... Farbe fuer den Text eines Eingabefeldes
// 
//    Rev 1.71   24 Mar 1996 12:29:00   gerhold
// Umstellung auf mehrseitige cFields
// 
//    Rev 1.69   18 Mar 1996 16:26:56   GERHOLD
// StaticTool::SetObjectColor
// 
//    Rev 1.68   23 Feb 1996 10:30:32   GERHOLD
// Im TextPushButton werden die Texthoehe und die Knopfhoehe verglichen.
// Ist der Text hoeher als der Knopf wird er immer um eine Zeile verkleinert.
// 
//    Rev 1.67   04 Feb 1996 15:32:20   gerhold
// StaticTool hat als optionalen Parameter die Zeilenanzahl
// 
//    Rev 1.66   02 Feb 1996 10:42:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.63   12 Dec 1995 11:39:38   GERHOLD
// ExternTool und ToolEdit setzen den Fokus nur, wenn sie ihn noch nicht hatten
// IsEnabled-Abfrage bei HotkeyAction (damit Elemente die disabled sind nix tun)
// 
//    Rev 1.62   23 Nov 1995 18:00:10   hannes
// Alle SetToolFocus haben einen neuen Parameter "mode"
// 
//    Rev 1.61   20 Nov 1995 11:41:06   HANNES
// SetLastPressedChar, GetLastPressedChar ... Zeichen fuer Eingabe-Combos
// 
//    Rev 1.60   16 Nov 1995 22:02:24   HANNES
// SetToolFocus von TextCheckButton
// 
//    Rev 1.59   16 Nov 1995 19:47:30   HANNES
// Scannen von '\0'
// 
//    Rev 1.58   15 Nov 1995 17:31:54   GERHOLD
// In ComboButton::Load ... ist Combo deaktiviert gibts fuer das Edit-Feld
//                          keine CallProc (Doppelclick geht ins Leere)
// 
//    Rev 1.57   31 Oct 1995 10:42:42   GERHOLD
// Gueltigkeit bei short, long, money - Eingabefeldern
// TextCheckPushButton (unnoetige Arbeit, noch nicht getestet)
// 
//    Rev 1.56   16 Oct 1995 13:09:34   GERHOLD
// Hotkeydata ist 4 Bytes lang.
// 
//    Rev 1.55   27 Sep 1995 17:38:30   GERHOLD
// ToolDate unterstuetzt als letzten Parameter einen FormatString "d.m.y"
// 
//    Rev 1.54   11 Sep 1995 20:23:56   MARTIN
// OnSetFocusProc
// 
//    Rev 1.53   11 Sep 1995 17:10:02   GERHOLD
// 
//    Rev 1.52   04 Sep 1995 13:08:38   HANNES
// 
//    Rev 1.51   27 Aug 1995 21:35:10   HANNES
// 
//    Rev 1.50   27 Aug 1995 12:46:26   HANNES
// ToolLong,ToolMoney
// 
//    Rev 1.49   24 Aug 1995 09:36:42   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.48   19 Jul 1995 11:15:32   GERHOLD
// SetConnections in ColorLine,COlorRect
// 
//    Rev 1.47   11 Jul 1995 12:43:20   HANNES
// Prozeduren von barelem -> barelem1 umgelagert
// 
//    Rev 1.46   10 Jul 1995 20:03:58   GERHOLD
// ColorRect
// 
//    Rev 1.45   02 Jul 1995 18:19:16   HANNES
// Palettenhandling
// 
//    Rev 1.44   26 Jun 1995 10:20:18   GERHOLD
// StaticBitmap und TransparentBitmap jetzt in Palette-Farben.
// 
//    Rev 1.43   10 Jun 1995 22:03:30   HANNES
// 
//    Rev 1.42   23 May 1995 18:42:58   GERHOLD
// kein FM_DECIMAL fuer ToolTime und ToolDate
// 
//    Rev 1.41   20 May 1995 16:17:20   HANNES
// SetEditMaxSize
// 
//    Rev 1.40   19 May 1995 18:56:12   HANNES
// File Zerteilt, Editfenster mit Combo - Enable erweitert
// 
//    Rev 1.39   19 May 1995 15:11:40   martin
// Tool-Date, -Time, -Float, -Shortint werden bei Selektionseingabe geloescht.
// 
//    Rev 1.38   17 May 1995 10:08:20   GERHOLD
// Up-Down Control reagiert jetzt auf KEYUP, KEYDOWN
// 
//    Rev 1.37   13 Apr 1995 12:54:10   HANNES
// 
//    Rev 1.36   12 Apr 1995 12:27:26   HANNES
// 
//    Rev 1.35   05 Apr 1995 16:39:12   GERHOLD
// 
//    Rev 1.34   04 Apr 1995 12:10:48   HANNES
// 
//    Rev 1.33   31 Mar 1995 13:10:02   HANNES
//  
// 
//    Rev 1.32   31 Mar 1995 08:53:12   HANNES
// 
//    Rev 1.31   29 Mar 1995 16:22:44   HANNES
// 
//    Rev 1.30   27 Mar 1995 13:18:20   HANNES
//  
// 
//    Rev 1.29   20 Mar 1995 14:26:44   HANNES
// 
//    Rev 1.28   20 Mar 1995 12:11:26   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.27   03 Mar 1995 18:18:16   GERHOLD
// 
//    Rev 1.26   16 Feb 1995 12:35:30   GERHOLD
// Die DC's bei Button-Up etwas mehr ueberpruefen
// 
//    Rev 1.25   19 Dec 1994 16:24:44   GERHOLD
// ToolEdit::OnChar erweitert
// 
//    Rev 1.24   15 Dec 1994 15:34:44   GERHOLD
// 
//    Rev 1.23   13 Dec 1994 14:00:18   GERHOLD
// Combo-Button gibt den Focus an das Edit-Element weiter.
// 
//    Rev 1.22   20 Nov 1994 17:58:36   HANNES
// Defaultwert bei CheckButtom
// 
//    Rev 1.21   31 Oct 1994 09:44:44   GERHOLD
// WWSetBuddy in ComboButton und UpDown deklariert.
// TextCheckButton um Disabled Knopf erweitert (5 Bitmaps).
// 
//    Rev 1.19   20 Oct 1994 17:45:24   GERHOLD
// im ToolEdit die Texte die mit GetText(Text) ermittelt werden nicht
// statisch sondern dynamisch (GetGlobMem) angelegt.
// 
//    Rev 1.18   17 Oct 1994 14:55:26   HANNES
// 
//    Rev 1.17   11 Oct 1994 17:56:48   HANNES
// CreateSmallFont raus
// 
//    Rev 1.16   06 Oct 1994 13:48:02   GERHOLD
// kleine Fehler im PageTool::Load ausgebessert
// 
//    Rev 1.15   04 Oct 1994 08:48:30   GERHOLD
// Up-Down Element disabled und besser gezeichnet
// 
//    Rev 1.14   20 Sep 1994 11:25:30   GERHOLD
// ???
// 
//    Rev 1.13   07 Sep 1994 16:26:18   GERHOLD
// Combo-Button so gezeichnet, da� er im Edit-Element liegt
// 
//    Rev 1.12   05 Sep 1994 13:14:12   GERHOLD
// UpDown-Control, Edit-Elemente mit Combo-Button sind nicht mehr editierbar
// Begin-, Continue-, EndCapture auf On_LButtonDown, On_MouseMove, 
// On_LButtonUp geaendert.
// 
//    Rev 1.11   31 Aug 1994 15:43:18   GERHOLD
// 
//    Rev 1.10   26 Aug 1994 16:36:58   GERHOLD
// in DrawEdge ein bisserl herumgespielt
// 
//    Rev 1.9   26 Aug 1994 15:57:30   GERHOLD
// ToolTime, ToolShortInt
// 
//    Rev 1.8   16 Aug 1994 08:46:34   GERHOLD
// 
//    Rev 1.7   10 Aug 1994 12:11:30   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.6   05 Aug 1994 11:52:48   GERHOLD
// Bitmap-Text-PushButton
// 
//    Rev 1.5   20 Jul 1994 17:00:30   GERHOLD
// kleine Aenderungen an StaticTool, TextCheckbutton, Groupbox
// 
//    Rev 1.4   12 Jul 1994 16:33:18   HANNES
// Line3d::MoveToExol
// 
//    Rev 1.3   12 Jul 1994 14:42:08   GERHOLD
// Line3D, TextPushbutton mit neuer cField-Farbe disabled
// 
//    Rev 1.2   11 Jul 1994 10:41:20   HANNES
// ToolLine
// 
//    Rev 1.1   05 Jul 1994 15:31:52   GERHOLD
// 
//    Rev 1.0   24 Jun 1994 16:41:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.35   14 Apr 1994 16:56:30   HANNES
// ToolEdit::SetOverwrite
// 
//    Rev 1.34   13 Apr 1994 14:28:56   HANNES
// Invalidieren von GroupBox
// 
//    Rev 1.33   21 Feb 1994 11:45:30   HANNES
// PaintFocus bei TextCheckButtons ohne Text
// 
//    Rev 1.32   14 Feb 1994 19:49:30   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.31   13 Jan 1994 16:01:38   HANNES
// ToolEdit::SetCaretToEnd
// 
//    Rev 1.30   04 Jan 1994 17:18:14   HANNES
// Bubbles auch fuer ExternTools
// 
//    Rev 1.29   18 Nov 1993 16:24:32   HANNES
// TextCheckbutton: SetToolFocus
// 
//    Rev 1.28   28 Oct 1993 12:39:30   MARTIN
// Help-Bubbles umgebaut
// 
//    Rev 1.27   18 Oct 1993 19:44:30   HANNES
// ToolBEdit
// 
//    Rev 1.26   04 Oct 1993 08:29:50   GERHOLD
// 
//    Rev 1.25   24 Sep 1993 22:49:56   GERHOLD
// 
//    Rev 1.24   24 Sep 1993 11:05:54   GERHOLD
// Animationbitmap, SetFocusToObject
// 
//    Rev 1.23   22 Sep 1993 09:48:10   GERHOLD
// Version nach St.Poelten
// 
//    Rev 1.22   09 Sep 1993 19:07:32   GERHOLD
// Bubbles in Zoom, Page, Edit
// 
//    Rev 1.21   08 Sep 1993 09:13:36   HANNES
// Groupboxstyle, FlapMap mit Action nach Endcaption
// 
//    Rev 1.20   24 Aug 1993 10:33:44   GERHOLD
// 
//    Rev 1.19   18 Aug 1993 10:51:16   GERHOLD
// ???
// 
//    Rev 1.18   10 Aug 1993 08:18:42   HANNES
// 
//    Rev 1.17   09 Aug 1993 19:34:14   GERHOLD
// 
//    Rev 1.16   09 Aug 1993 12:58:10   HANNES
// ?
// 
//    Rev 1.15   23 Jul 1993 15:32:20   GERHOLD
// Zeichnen des FlapMaps
// 
//    Rev 1.14   22 Jul 1993 14:38:08   GERHOLD
// FlapMap
// 
//    Rev 1.13   21 Jul 1993 14:50:52   GERHOLD
// InitHotKey fuer Script vorbereiten
// 
//    Rev 1.12   21 Jul 1993 09:44:50   HANNES
// 
//    Rev 1.11   20 Jul 1993 18:29:26   GERHOLD
// ...
// 
//    Rev 1.10   16 Jul 1993 12:56:54   GERHOLD
// siehe 1.9
// 
//    Rev 1.9   16 Jul 1993 09:55:58   GERHOLD
// kleine Aenderungen in den Linien und der ActionBox
// 
//    Rev 1.8   15 Jul 1993 18:15:42   GERHOLD
// kleine Aenderungen in PaintTool bei 3DLine und ActionBox
// 
//    Rev 1.7   15 Jul 1993 16:48:02   GERHOLD
// Linien und ActionBox
// 
//    Rev 1.6   14 Jul 1993 14:49:48   GERHOLD
// statisches Bitmap
// 
//    Rev 1.5   14 Jul 1993 09:54:58   HANNES
// ToDevKoordX, ToDevKoordY nicht als Inline
// 
//    Rev 1.4   09 Jul 1993 12:04:22   GERHOLD
// HotKeyAction fuer CheckButton definiert
// 
//    Rev 1.3   09 Jul 1993 11:51:48   HANNES
// ??
// 
//    Rev 1.2   09 Jul 1993 10:55:02   HANNES
// ExternTool
// 
//    Rev 1.1   09 Jul 1993 00:32:10   HANNES
// ToolStat, GroupBox
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define MODULENUM  44               // Modul-Nummer fuer Fehlermeldung
#include "winass.hpp"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "globmem.h"
#include "cfield.hpp"
#include "wordwin.hpp"
#include "toolbar.hpp"
#include "font.hpp"
#define NODDSDATA
// #define JUST_EM
#include "dds.h"
#include "dds.hpp"
#include "data.hpp"

#include "date.hpp"
#include "ddsmsg.h"


#ifdef TOOLTIP
  #define NOTOOLBAR
  #define NOSTATUSBAR
  #include <commctrl.h>
#endif

/********************************************************************\
*                                                                    *
*                 Implementation der Tool Elemente                   *                                            
*                                                                    *
\********************************************************************/

#define BTN_OUT     0x1
#define BTN_IN      0x2
#define BTN_HOLD    0x4
#define BTN_TEXT    0x8
#define BTN_CHECK   0x10
#define BTN_CHECKED 0x20


BOOL FieldHasCaret;



DLLExport void _export WINAPI stcallback (int Cmd,LPVOID Info,LPVOID extParam)
  {
  if (Cmd == CALLBACKCMD_GETFONTREFWND) {
    FontRefWndBuffer FAR *f = (FontRefWndBuffer FAR *) Info;
    f->IsDone = TRUE ;
    f->RefWnd = 0;
    }
  }


CFIELDCALLBACK GetFieldCallback()
  {
  static CFIELDCALLBACK res ;
  if (res == NULL)
    res = CFIELDCALLBACK (MakeProcInstance(FARPROC(stcallback),hLibInst));
  return res;
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



void PaintFocusRect (HDC hDC, RECT rc)
  {
  LOGBRUSH LogBrush;

  LogBrush.lbStyle = BS_PATTERN;

#ifdef WIN32
  LogBrush.lbHatch = LONG(LoadBitmap(hLibInst, "FOCUSBITS"));
#else
  LogBrush.lbHatch = LoadBitmap(hLibInst, "FOCUSBITS");
#endif

  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, CreateBrushIndirect(&LogBrush));
      
  PatBlt (hDC, rc.left, rc.top, 1, rc.bottom-rc.top-1, 0xA000C9);    // Quelle & Ziel
  PatBlt (hDC, rc.left, rc.top, rc.right-rc.left-1, 1, 0xA000C9);
  PatBlt (hDC, rc.right, rc.top, 1, rc.bottom-rc.top-1, 0xA000C9);
  PatBlt (hDC, rc.left, rc.bottom-1, rc.right-rc.left, 1, 0xA000C9);

  DeleteObject(SelectObject(hDC, OldBrush));
  DeleteObject(HBITMAP(LogBrush.lbHatch));
  }

DLLExport void _export WINAPI MyDrawEdge (HDC hDC, LPRECT lprc, UINT EdgeType, UINT Flags)
  {
  RECT rc;

  COLORREF BtnFace, WindowFrame, BtnHighlight, BtnShadow;
  HPEN hOldPen, Pen1, Pen2, Pen3, Pen4;
  
  BtnFace = GetSysColor (COLOR_BTNFACE);
  BtnShadow = GetSysColor (COLOR_BTNSHADOW);
  BtnHighlight = GetSysColor (COLOR_BTNHIGHLIGHT);
  WindowFrame = GetSysColor (COLOR_WINDOWFRAME);

  CopyRect (&rc, LPRECT(lprc));

  switch (Flags) {
    case MY_BF_ADJUST :
      rc.left -= 2;
      rc.top -= 2;
      rc.right += 2;
      rc.bottom += 1;
      break;
    case MY_BF_MIDDLE :
      InflateRect (&rc, -2, -2);
      break;

    case MY_BF_RECT :
      rc.right -= 1;
      rc.bottom -= 1;
      break;
    }

  switch (EdgeType) {
    case MY_EDGE_HWND :
      Pen1 = CreatePen (PS_SOLID, 0, BtnShadow);
      Pen2 = CreatePen (PS_SOLID, 0, BtnHighlight);
      Pen3 = CreatePen (PS_SOLID, 0, WindowFrame);
      Pen4 = CreatePen (PS_SOLID, 0, BtnFace);
      break;
    case MY_EDGE_GROUPBOX3D :
      Pen1 = Pen4 = CreatePen (PS_SOLID, 0, BtnShadow);
      Pen2 = Pen3 = CreatePen (PS_SOLID, 0, BtnHighlight);
      break;
    case MY_EDGE_GROUPBOX :
      Pen1 = CreatePen (PS_SOLID, 0, BtnShadow);
      Pen2 = CreatePen (PS_SOLID, 0, BtnHighlight);
      Pen3 = Pen4 = (HPEN)GetStockObject(NULL_PEN);
      break;
    case MY_EDGE_BUTTONUP :
      Pen1 = CreatePen (PS_SOLID, 0, BtnHighlight);
      Pen2 = CreatePen (PS_SOLID, 0, WindowFrame);
      Pen3 = CreatePen (PS_SOLID, 0, BtnFace);
      Pen4 = CreatePen (PS_SOLID, 0, BtnShadow);
      break;
    case MY_EDGE_BUTTONDOWN :
      Pen1 = CreatePen (PS_SOLID, 0, WindowFrame);
      Pen2 = CreatePen (PS_SOLID, 0, BtnHighlight);
      Pen3 = CreatePen (PS_SOLID, 0, BtnShadow);
      Pen4 = CreatePen (PS_SOLID, 0, BtnFace);
      break;
    }

  // 1.Ebene: linke und obere Linie
  hOldPen = (HPEN)SelectObject (hDC, Pen1);
  MoveToEx (hDC, rc.left, rc.bottom-1,NULL);
  LineTo (hDC, rc.left ,rc.top);
  LineTo (hDC, rc.right-1, rc.top);

  // 1.Ebene: untere und rechte Linie
  SelectObject (hDC, Pen2);
  MoveToEx (hDC, rc.left, rc.bottom,NULL);
  LineTo (hDC, rc.right-1, rc.bottom); //!! -1
  LineTo (hDC, rc.right-1, rc.top-1);  //!! -1

  // 2.Ebene: linke und obere Linie
  SelectObject (hDC, Pen3);
  MoveToEx (hDC, rc.left+1, rc.bottom-2,NULL);
  LineTo (hDC, rc.left+1 ,rc.top+1);
  LineTo (hDC, rc.right-2, rc.top+1);

  // 2.Ebene: untere und rechte Linie
  SelectObject (hDC, Pen4);
  MoveToEx (hDC, rc.left+1, rc.bottom-1,NULL);
  LineTo (hDC, rc.right-2, rc.bottom-1);  // !!-1 -> -2
  LineTo (hDC, rc.right-2, rc.top+1);     // !! -1 -> -2
                                          
  SelectObject (hDC, hOldPen);
  DeleteObject (Pen1);
  DeleteObject (Pen2);
  DeleteObject (Pen3);
  DeleteObject (Pen4);
  }


/*------------------------------------------------------------------*\
* CONSTRUCTOR Tool                                                   *
\*------------------------------------------------------------------*/
tool::tool (HWND hRefWnd,LPVOID Data,LPVOID pData,int pdSize)
  {
  StructData = Data;                  // Zeiger auf die Tool-Daten
  privData = GetGlobMem (pdSize);
  lmemcpy (privData,pData,pdSize);
  LPSCREEN FAR *llps = (LPSCREEN FAR *) (* GetData) (privData,LPTOOLHEADER (Data)->ScreenId);
  DBWIN_ASSERT ((llps != NULL) && (*llps != NULL));
  DBINT FAR *lpLayer = (DBINT FAR *) (* GetData) (privData,LPTOOLHEADER (Data)->_Layer);
  DBWIN_ASSERT (lpLayer != NULL);
  WndList FAR *wnd = 
        (* llps)->GetWnd (hRefWnd,*lpLayer);
  Parent = wnd;                    // Zeiger auf das Elternfenster

  InitHotKey ();

  wnd->Insert (this);              // Tool in die Liste einf�gen
  lpMenu = NULL;
  }

/*------------------------------------------------------------------*\
*  DESTRUCTOR Tool                                                   *
\*------------------------------------------------------------------*/
tool::~tool ()
  {
  Param()->hd.MyTool = NULL;
  RemoveHotKey (this);

  RemoveContextMenu ();

  (* FreePrivData) (privData);
  FreeGlobMem (privData);
  Parent->DelFromList (this);            // Tool aus der Liste l�schen
  if (Parent->Parent->ToolWithFocus == this)
    Parent->Parent->ToolWithFocus = NULL;
  if (Parent->first == NULL)             // kein Tool mehr in der Liste?
    delete Parent;                      // => Liste komplett entfernen
  }

//------------------------  FixConnection  ----------------------------------
void tool::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->hd.HotKey, StructData);
  }

//--------------------------  Reset  ----------------------------------------
void tool::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);
  (* ClearConnection) (privData, Param()->hd.HotKey, StructData);

#ifdef TOOLTIP
  RemoveToolTip ();
#endif
  }

//--------------------------  Load  -----------------------------------------
void tool::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  
  GetRect();

#ifdef TOOLTIP
  AddToolTip ();
#endif
  }

#define ISFREEHK(A) (((LOWORD(A) != 0) && (LOWORD(A) <= 0xEF00)) \
                     || (EditCallBack != NULL))

void tool::InitHotKey ()
  {
  HotKey FAR* hk;
  BOOL        ToolIsInHotKeyList = FALSE;
  
  for (hk = FirstHotKey; hk != NULL; hk = hk->Next) 
    if (hk->hkTool == this) {
      ToolIsInHotKeyList = TRUE;
      break;
      }

  if (!ToolIsInHotKeyList) {
    LPHOTKEYS pkd = (LPHOTKEYS) (* GetData) (privData, Param()->hd.HotKey);
    if (pkd != NULL)
      hk = new HotKey (*pkd, ISFREEHK (Param()->hd.HotKey) , this);
    else {
      HotKeyData kd = {0, 0, 0, 0};
      hk = new HotKey (kd, ISFREEHK (Param()->hd.HotKey) ,this);
      }
    }
  }


void tool::SetHotKey (HotKeyData kd)
  {
  (* SetData) (privData, Param()->hd.HotKey, &kd,
                   sizeof(kd), StructData);
  }


int tool::ToDevKoordX (LONG x)
  { return int (float (x) * BaseUnit) + dxPhys; }
int tool::ToDevX (LONG x)
  { return int (float (x) * BaseUnit); }

int tool::ToDevKoordY (LONG y, int Layer)
  { 
  if (y >= 0)
    return int (float (y) * BaseUnit) + Parent->Parent->LayerStart (Layer) + dyPhys;
  else {
    RECT  rc;
    GetClientRect (Parent->Parent->hWndToolbar(), &rc);
    return rc.bottom + int(float(y)*BaseUnit) + dyPhys;
    }
  }
int tool::ToDevY (LONG y)
  { 
  return int (float (y) * BaseUnit);
  }


#ifdef TOOLTIP
//---------------------------------------------------------------------------
// tool::AddToolTip
//
// Wird von jedem Tool aufgerufen, welches ToolTips zulaesst.
// Der Aufruf darf aber natuerlich erst nach der Bekanntgabe des ToolRects
// erfolgen.
// Wichtig ist auch dieser Aufruf aus dem ::MoveTool, da sich das ToolRect
// aendern kann, und diese Aenderung uebernommen werden muss...
//---------------------------------------------------------------------------
void tool::AddToolTip (HWND hWndTool)
  {
  if (!IsWindow(Parent->Parent->hWndToolTip))
    return;

  TOOLINFO ti;

  LPSTR lpstr = GetHelpText();

  if (lpstr && *lpstr) {

    //----------------------------------------------
    // unsinnige und kurze Hilfetexte gelten nicht
    //----------------------------------------------
    int len = lstrlen(lpstr);
    if (!lstrcmp(lpstr, "Hilfe") || (len < 4))
      return;

    char szHelpText[1024];

    int szlen = sizeof(szHelpText);
    lmemset (szHelpText, '\0', szlen);
    if (len > szlen)
      len = szlen;
    lmemcpy (szHelpText, lpstr, len);

    ti.cbSize = sizeof(TOOLINFO);

    if (hWndTool) {
      ti.uFlags = TTF_IDISHWND; 
      ti.uId = (UINT)hWndTool;
      }
    else {
      ti.uFlags = 0;
      ti.uId = (UINT)this;
      }

    ti.hinst = hLibInst;
    // ti.lpszText = szHelpText;
    ti.lpszText = NULL;
    ti.hwnd = Parent->Parent->hWndToolbar(); 

    //---------------------------------------------------------------------
    // Gibt's das Tool bereits? Dann wird ihm das neue Rechteck uebergeben
    //---------------------------------------------------------------------
    if (SendMessage(Parent->Parent->hWndToolTip, TTM_GETTOOLINFO, 0, (LPARAM)(LPTOOLINFO)&ti)) {
      CopyRect (&ti.rect, LPRECT(&ToolRect));
      SendMessage(Parent->Parent->hWndToolTip, TTM_NEWTOOLRECT, 0, 
                (LPARAM)(LPTOOLINFO)&ti);

      }
    else {
      ti.cbSize = sizeof(TOOLINFO); 
      ti.hinst = hLibInst;
      ti.hwnd = Parent->Parent->hWndToolbar(); 
      ti.lpszText = szHelpText;

      if (hWndTool) {
        ti.uFlags = TTF_IDISHWND; 
        ti.uId = (UINT)hWndTool;
        }
      else {
        ti.uFlags = 0; 
        ti.uId = (UINT)this;
        }

      CopyRect (&ti.rect, LPRECT(&ToolRect));

      SendMessage(Parent->Parent->hWndToolTip, TTM_ADDTOOL, 0, 
                  (LPARAM) (LPTOOLINFO) &ti);
      }
    }
  }


//---------------------------------------------------------------------------
// tool::RemoveToolTip
//
//---------------------------------------------------------------------------
void tool::RemoveToolTip (HWND hWndTool)
  {
  if (!IsWindow(Parent->Parent->hWndToolTip))
    return;

  TOOLINFO ti;

  ti.cbSize = sizeof(TOOLINFO);

  if (hWndTool)
    ti.uId = UINT(hWndTool);
  else
    ti.uId = UINT(this);

  ti.hwnd = Parent->Parent->hWndToolbar(); 

  SendMessage(Parent->Parent->hWndToolTip, TTM_DELTOOL, 0, LPARAM(&ti));
  }

#endif


WndList FAR *ScreenList::NextWnd (WndList FAR *w)
  {
  for ( int i = 0 ; i < AnzActive ; i++ ) {
    if (ActiveList[i] == w) {
      return (i < AnzActive - 1) ?
        ActiveList[i+1] : ActiveList[0];
      }
    }
  DBWIN_ASSERT(FALSE);
  return NULL;
  }
  
WndList FAR *ScreenList::PrevWnd (WndList FAR *w)
  {
  for ( int i = 0 ; i < AnzActive ; i++ ) {
    if (ActiveList[i] == w) {
      return (i > 0) ?
        ActiveList[i-1] : ActiveList[AnzActive-1];
      }
    }
  DBWIN_ASSERT(FALSE);
  return NULL;
  }
  
tool FAR *tool::GetNext ()
  { 
  if (Next != NULL)
    return Next;
  else
    return (Parent->Parent->NextWnd(Parent))->first;
  }


tool FAR *tool::GetPrev ()
  { 
  // Durschsucht die Tool-Liste vom Anfang dieses Layers bis vor das gerade fokussierte Element.
  for (tool FAR* f = Parent->first ; (f->Next != this) && (f->Next != NULL) ; f = f->Next);
  if (f->Next != NULL)
    return f;
  else {
    // den vorigen Layer suchen
    WndList FAR *Wnd = Parent->Parent->PrevWnd (Parent);
    for (tool FAR* f = Wnd->first ; f->Next != NULL ; f = f->Next);
    return f;
    }
  }

void tool::GetHelp (POINT pt)
  {
  LPSTR lpstr = GetHelpText();
  if ((lpstr != NULL) && (*lpstr != '\0'))
    hWndBubble = CreateBubbleWindow (pt.x, pt.y, lpstr, Parent->Parent->hWndToolbar());
  else 
    hWndBubble = NULL;
  }

void tool::RemoveHelp ()
  {
  if (hWndBubble) {
    DestroyWindow (hWndBubble);
    hWndBubble = NULL;
    }
  }


void tool::OnRButtonDown (HMENU hPopupMenu)
  {
  LPSTR lpstr = GetHelpText();
  if ((lpstr != NULL) && (*lpstr != '\0'))
    EnableMenuItem (hPopupMenu, 100, MF_BYCOMMAND | MF_ENABLED);
  }


// folgende drei Funktionen sind aus cword.cpp bzw. cword1.cpp uebernommen
// und immer mit diesen synchron zu halten
BOOL IsValidEscape (char ch)
  {
  return ((ch == 'f') || (ch == 'e') || (ch == 'h') || (ch == 'z') || (ch == 'c')) ;
  }
char ModifyChar (WORD modify)
  {
  char res ;
  if (modify < 10)
    res = '0' + char(modify) ;
  else if (modify < 'Z' - 'A' + 10)
    res = 'A' + char(modify) - 10 ;
  else
    res = 'a' + char(modify) - ('Z' - 'A' + 10) ;
  return res ;
  }
WORD ModifyNum (char modifyChar)
  {
  WORD Modify ;
  if ((modifyChar >= '0') && (modifyChar <= '9'))
    Modify = modifyChar - '0' ;
  else if ((modifyChar >= 'A') && (modifyChar <= 'Z'))
    Modify = modifyChar - 'A' + 10 ;
  else
    Modify = modifyChar - 'a' + ('Z' - 'A' + 10) ;
  return Modify ;
  }

void tool::GetHKText (LPSTR res,LPSTR org,int Format)
  {
  lstrcpy (res,org);
  LPHOTKEYS pkd = (LPHOTKEYS) (* GetData) (privData, Param()->hd.HotKey);
  if ((pkd != NULL) && (pkd->VirtKey != 0) && (pkd->Modify != 0)) {
    int len = lstrlen(org);
    LPSTR p = org;
    WORD lastModifier = 0;
    while (*p) {
      if (*p == '\\') {
        if (IsValidEscape(p[1]) || (p[1] == '\\')) {
          p++;
          while (*p && (*p != '\\'))
            p++;
          }
        else if (p[1] == 'm') {
          p += 2;
          if (*p)
            lastModifier = ModifyNum(*p++);
          }
        else // ungueltiges Format
          p++;
        }
      else {
#ifdef WIN32
        unsigned char ch;
        ch = *p;

        BYTE chu = (BYTE)LOWORD(CharUpper (LPTSTR(ch)));
        if (pkd->VirtKey == chu)
#else
        if (pkd->VirtKey == (BYTE) (DWORD) AnsiUpper (LPSTR (MAKELP (0,*p))))
#endif
          {
          LPFORMATINFO finfo = GetFormatInfo (Format);
          char szUnderLine[10];
          char szEndUnderLine[10];
          WORD hotkeyModifier = lastModifier | 2;
          if (finfo->fi.lf.lfWeight >= 500)  // Font ist fett
            hotkeyModifier |= 1;
          sprintf(szUnderLine,"\\m%c",ModifyChar(hotkeyModifier));
          sprintf(szEndUnderLine,"\\m%c",ModifyChar(lastModifier));
          int Pos = p-org;
          LPSTR h = res ;
          if (Pos != 0)
            lmemcpy (h, org, Pos);
          h += Pos;
          lmemcpy (h, szUnderLine, lstrlen(szUnderLine));
          h += lstrlen (szUnderLine);
          *h = org[Pos] ;
          h += 1 ;
          lmemcpy (h, szEndUnderLine, lstrlen(szEndUnderLine));
          h += lstrlen(szEndUnderLine);
          lmemcpy (h, org+Pos+1, len-Pos-1);
          h += len-Pos-1;
          *h = '\0' ;
          break;
          }
        p++;
        }
      }
    }
  }

//---------------------------------------------------------------------------
// OnCommand
//   Wird in der Toolbar-WndProc bei WM_COMMAND aufgerufen (rechte Maustaste)
//---------------------------------------------------------------------------
BOOL tool::OnCommand (HWND hWnd, WPARAM wID)
  {
  BOOL res = FALSE;
  if (wID == IDM_HELP) {
    POINT pt;
          
    pt.x = (ToolRect.right + ToolRect.left) / 2;
    pt.y = ToolRect.bottom + 5;
  
    GetHelp (pt);
    if (hWndBubble != NULL)
      SetCapture (hWndBubble);

    res = TRUE;
    }
  else
  if (wID == IDM_HOTKEY) {
//-------------------------------------------------------------
// momentan nix machen wenn das Hotkey-Menu gedrueckt wird!!!!
/**************************************************************
    if (LOWORD(Param()->hd.HotKey) != 0) {
      ActHotkey = GetHotKey (this);                // HotKey suchen und global merken
      FARPROC lpDialogProc = MakeProcInstance (FARPROC(HotKeyDlgProc), hLibInst);
      int iReturn = DialogBox (hLibInst, "HOTKEYS", hWnd, lpDialogProc);
      FreeProcInstance (lpDialogProc);
      }
**************************************************************/
    res = TRUE;
    }
  else {
    if (lpMenu != NULL) {
      for (LPMENULIST l = lpMenu; l != NULL; l = l->Next)
        
        // l->Proc wurde als ID fuer das WM_COMMAND missbraucht
        //-------------------------------------------------------
        if (l->Proc == wID)
          (* CallCommand) (l->MenuPrivData, l->Proc, l->MenuProcPar);
      }
    }
  return res;
  }
  

void tool::SetContextMenu (LPVOID menuprocparam, LPVOID menuprivData, int menuprivdatasize,
                           LPSTR text, DWORD proc, UINT flags, WORD mode) 
  {
  // im Ladezweig wird ein Element erzeugt und befuellt
  //----------------------------------------------------
  if (mode & EM_LOAD) {
    LPMENULIST lpml = (LPMENULIST)GetGlobMem (sizeof(*lpml));

    if (menuprivData) {
      lpml->MenuPrivData = GetGlobMem (menuprivdatasize);
      lmemcpy (lpml->MenuPrivData, menuprivData, menuprivdatasize);
      }

    lpml->MenuProcPar = menuprocparam;

    lpml->Text = (LPSTR)GetGlobMem (lstrlen(text)+1);
    lstrcpy (lpml->Text, text);

    lpml->Flags = flags;
    lpml->Proc = proc;
    lpml->Next = NULL;

    if (lpMenu != NULL) {
      for (LPMENULIST l = lpMenu; l->Next != NULL; l = l->Next);
      l->Next = lpml;
      }
    else
      lpMenu = lpml;
    }
  else {
  // im Updatezweig wird das Element gesucht und der Text bzw. die Flags
  // werden geaendert. (Auf die Proc ist keine Connection gesetzt; 
  // d.h. sie ist konstant und wird deshalb missbraucht, um das passende 
  // Menu in der Liste zu finden
  //---------------------------------------------------------------------
    for (LPMENULIST l = lpMenu; l != NULL; l = l->Next)
      if (l->Proc == proc) {
        if (l->Text != NULL)          // alten Text loeschen
          FreeGlobMem (l->Text);

        l->Text = (LPSTR)GetGlobMem (lstrlen(text)+1);
        lstrcpy (l->Text, text);

        l->Flags = flags;
        break;
        }
    }
  }

void tool::AppendContextMenu (HMENU hMenu)
  {
  if (lpMenu != NULL) {
    for (LPMENULIST l = lpMenu; l != NULL; l = l->Next) {

      // l->Proc wird als ID fuer das WM_COMMAND missbraucht
      //-------------------------------------------------------
      AppendMenu (hMenu, l->Flags, UINT(l->Proc), l->Text);
      }
    }
  }

void tool::RemoveContextMenu ()
  {
  if (lpMenu != NULL) {

    LPMENULIST Next = NULL;
    for (LPMENULIST l = lpMenu; l != NULL; ) {
      Next = l->Next;
      if (l->Text != NULL)
        FreeGlobMem (l->Text);

      if (l->MenuPrivData) {
        (* FreePrivData) (l->MenuPrivData);
        FreeGlobMem (l->MenuPrivData);
        }

      FreeGlobMem (l);
      l = Next;
      }
    }
  }


void HelpTool::GetRect ()
  {
  SetRectEmpty (LPRECT(&ToolRect));
  }

void HelpTool::HotKeyAction (BOOL dontCheckEnabled)
  {
  (* CallCommand) (privData, Param()->Id,Param());
  }


void DrawButtonEx (HDC hDC, LPRECT ToolRect, DWORD Style)
  {
  HBRUSH  OldBrush;
  HPEN    OldPen;

  if (Style & BTN_OUT) {
    OldPen = (HPEN)SelectObject (hDC, GetStockObject (NULL_PEN));
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
    Rectangle (hDC, ToolRect->left+1, ToolRect->top+1, 
                    ToolRect->right-1, ToolRect->bottom-1);
    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);

    RECT rc;
    CopyRect (&rc, ToolRect);
    InflateRect (&rc, -1, -1);

    MyDrawEdge (hDC, ToolRect, MY_EDGE_BUTTONUP, MY_BF_RECT);
    }
  else if ((Style & BTN_IN) || (Style & BTN_HOLD) || (Style & BTN_CHECKED)) {
    OldPen = (HPEN)SelectObject (hDC, GetStockObject (NULL_PEN));

    if (((Style & BTN_IN) || (Style & BTN_HOLD)) && !(Style & BTN_CHECKED))
      OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
    else {
      UnrealizeObject (DnBrush);
#ifdef WIN32
      SetBrushOrgEx (hDC, ToolRect->left, ToolRect->top+1, NULL);
#else
      SetBrushOrg (hDC, ToolRect->left, ToolRect->top+1);
#endif
      OldBrush = (HBRUSH)SelectObject (hDC, DnBrush);
      }

    Rectangle (hDC, ToolRect->left+1, ToolRect->top+1, 
                    ToolRect->right-1, ToolRect->bottom-1);
    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);

    RECT rc;
    CopyRect (&rc, ToolRect);
    InflateRect (&rc, -1, -1);

    MyDrawEdge (hDC, ToolRect, MY_EDGE_BUTTONDOWN, MY_BF_RECT);
    }
  }


/********************************************************************\
*                            Push-Button                             *
\********************************************************************/

PushButton::PushButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize)        // CONSTRUCTOR
  {
//  CapDC = 0;
//  MemDC = 0;
  IsPressed = FALSE;
  Capturing = FALSE;
  IsEnabled = TRUE;
  }

BOOL PushButton::HasTabStop ()
  {
  return IsEnabled ;
  }

void PushButton::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  int AnzRows, AnzCols;
  HBITMAP hBmp = GetBitmap (
                      BitRef()[0].bitId, 
                      AnzRows, AnzCols
                           );
  BITMAP bi;

  int bmWidth,bmHeight;
  if (hBmp) {
    GetObject (hBmp,sizeof(bi),&bi);
    bmWidth  = bi.bmWidth  / AnzCols ;
    bmHeight = bi.bmHeight / AnzRows ;
    }
  else
    bmWidth  = bmHeight = 0;
    
  int x0 = ToDevKoordX (tx);
  int y0 = ToDevKoordY (ty, Parent->Layer);

  // Breite des Bitmaps + Rahmen und Schattierung
  SetRect (LPRECT (&ToolRect), x0, y0, x0+bmWidth+8, y0+bmHeight+7);
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + bmHeight + 7);
  }

void PushButton::MoveTool ()
  {
  int y0 = Gety0 ();
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);

#ifdef TOOLTIP
    AddToolTip ();        // neue Position mitteilen
#endif
    }
  }

PushButton::~PushButton ()                                // DESTRUCTOR
  {
  if (Capturing) {
//    if (MemDC != 0)
//      DeleteDC (MemDC);
//    if (CapDC != 0)
//      ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
    ReleaseCapture ();
    }
  }

void PushButton::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);

  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));

  tx = *lpx;
  ty = *lpy;

  GetRect();

#ifdef TOOLTIP
  AddToolTip ();
#endif

  AnzButtons = GetAnzButtons();
  DBBOOL FAR *IsDisabled = (DBBOOL FAR *)(* GetData) (privData,Param()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));

  if (lpBmpRef == NULL) {
    lpBmpRef = (BMPREF FAR *) GetGlobMem (AnzButtons * sizeof(*lpBmpRef));
    for (int i = 0; i < AnzButtons; i++) {
      DBINT FAR *lpcol = (DBINT FAR *)(* GetData)(privData, BitRef()[i]._Col);
      DBINT FAR *lprow = (DBINT FAR *)(* GetData)(privData, BitRef()[i]._Row);
      lpBmpRef[i].Col = lpcol != NULL ? *lpcol : 0;
      lpBmpRef[i].Row = lprow != NULL ? *lprow : 0;
      }
    }  
  }

void PushButton::Reset (BOOL doClear)
  {
  tool::Reset (doClear);
  (* ClearConnection) (privData,Param()->Disabled,StructData);

  if (lpBmpRef != NULL) {
    FreeGlobMem (lpBmpRef);
    lpBmpRef = NULL;
    }
  }

//***************************************************************************
// HotKeyAction
//
// Zweck: Aufruf der Script-Prozedur
//***************************************************************************
void PushButton::HotKeyAction (BOOL dontCheckEnabled)
  {
  if (!GetCapture())
    if ((IsEnabled) || (dontCheckEnabled))
      (* CallCommand) (privData, Param()->Id,Param());
  }


LPSTR PushButton::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }

BOOL PushButton::HitTest (LPPOINT pt)             
  {
  return (PtInRect(LPRECT(&ToolRect), *pt));
  }



void PushButton::PaintTool (HDC hDC, HDC hMemDC)
  {
  PaintState ();
  }



void PushButton::CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh)
  {
  if (State & BTN_CHECK)
    tool::CalcOffset (State, bmw, bmh);
  else  
    switch (State) {
      case BTN_OUT  : 
        *bmw = 3;
        *bmh = 3;
        break;
      case BTN_IN   : 
        *bmw = 4;
        *bmh = 4;
        break;
      case BTN_HOLD : 
        *bmw = 5;
        *bmh = 5;
        break;
      }
  }



COLORREF rgbFace    = GetSysColor(COLOR_BTNFACE);
COLORREF rgbShadow  = GetSysColor(COLOR_BTNSHADOW);
COLORREF rgbHilight = GetSysColor(COLOR_BTNHIGHLIGHT);
COLORREF rgbFrame   = GetSysColor(COLOR_WINDOWFRAME);

void DrawDisabledBmp (HDC hdc, HBITMAP hBmp, int x, int y, int w, int h,
                      int ix, int iy)
  {
  HBRUSH hbrOld;

  HDC hdcMono = CreateCompatibleDC(NULL);
  HBITMAP hbmMono = CreateBitmap(w, h, 1, 1, NULL);
  HBITMAP hbmDefault = (HBITMAP)SelectObject(hdcMono, hbmMono);

  HDC hdcGlyphs = CreateCompatibleDC (NULL);
  HBITMAP hBmpT = (HBITMAP)SelectObject (hdcGlyphs, hBmp);
  
  // Initalize whole area with 1's.
  PatBlt(hdcMono, 0, 0, w, h, WHITENESS);

  // Create mask based on color bitmap.
  // Convert this to 1's.
  SetBkColor(hdcGlyphs, rgbFace);
  BitBlt(hdcMono, 0, 0, w, h, hdcGlyphs, ix, iy, SRCCOPY);
  // Convert this to 1's.
  SetBkColor(hdcGlyphs, rgbHilight);
  // OR in the new 1's.
  BitBlt(hdcMono, 0, 0, w, h, hdcGlyphs, ix, iy, SRCPAINT);

  // Disabled version (or indeterminate)

  SetTextColor(hdc, 0L);      // 0's in mono -> 0 (for ROP)
  SetBkColor(hdc, 0x00FFFFFF); // 1's in mono -> 1

  // Draw glyph's white understrike.
  HBRUSH hbr = CreateSolidBrush(rgbHilight);
  if (hbr) {
    hbrOld = (HBRUSH)SelectObject(hdc, hbr);
    if (hbrOld) {
      // Draw highlight color where we have 0's
      // in the mask.
      BitBlt(hdc, x + 1, y + 1, w, h, hdcMono, 0, 0, 0x00B8074A);
      SelectObject(hdc, hbrOld);
      }
    DeleteObject(hbr);
    }

  // Gray out glyph.
  hbr = CreateSolidBrush(rgbShadow);
  if (hbr) {
    hbrOld = (HBRUSH)SelectObject(hdc, hbr);
    if (hbrOld) {
      // Draw the shadow color where we have 0's in the mask.
      BitBlt(hdc, x, y, w, h, hdcMono, 0, 0, 0x00B8074A);
      SelectObject(hdc, hbrOld);
      }
    DeleteObject(hbr);
    }

//  if (state & TBSTATE_CHECKED) {
//    BitBlt(hdcMono, 1, 1, w - 1, h - 1, hdcMono, 0, 0, SRCAND);
//    }

  SelectObject(hdcMono, hbmDefault);
  DeleteDC(hdcMono);    // toast the DCs
  DeleteObject (hbmMono);

  SelectObject (hdcGlyphs, hBmpT);
  DeleteDC (hdcGlyphs);
  }


void PushButton::PaintButton (DWORD Style, int Index)
  {
#ifndef WIN32
  HBRUSH   OldBrush;
  HPEN     OldPen;
#endif

  HBITMAP  OldBitmap;
  int      AnzCols, AnzRows;

  HDC hDC = GetDC(Parent->Parent->hWndToolbar());
  HDC hMemDC = CreateCompatibleDC(hDC);

  HBITMAP hBmp = GetBitmap (
                      BitRef()[Index].bitId, 

                      AnzRows, AnzCols
                           );
  int bmWidth,bmHeight ;
  if ((hBmp != 0) && (lpBmpRef[Index].Col < AnzCols) &&
                     (lpBmpRef[Index].Row < AnzRows)) {
    BITMAP bi;
    GetObject (hBmp,sizeof(bi),&bi);
    bmWidth  = bi.bmWidth  / AnzCols ;
    bmHeight = bi.bmHeight / AnzRows ;
    }
  else
    bmWidth  = bmHeight = 0;

  int OffX = bmWidth;
  int OffY = bmHeight;
  
  CalcOffset (Style, &OffX, &OffY);
  if (Style & BTN_CHECK) {
    } 
  else {
    switch (Style) {
      case BTN_OUT  :
#ifdef WIN32
        DrawButtonEx (hDC, LPRECT(&ToolRect), Style);
#else
        OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
        OldBrush = SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
        Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                        ToolRect.right-1, ToolRect.bottom-1);

        MoveToEx (hDC, ToolRect.left+2, ToolRect.bottom-3, NULL);
        LineTo (hDC, ToolRect.right-3, ToolRect.bottom-3);
        LineTo (hDC, ToolRect.right-3, ToolRect.top+1);

        SelectObject (hDC, OldBrush);
        DeleteObject (SelectObject(hDC, OldPen));

        OldPen = SelectObject (hDC, GetStockObject(WHITE_PEN));
        MoveToEx (hDC, ToolRect.left+1, ToolRect.bottom-3,NULL);
        LineTo (hDC, ToolRect.left+1, ToolRect.top+1);
        LineTo (hDC, ToolRect.right-2, ToolRect.top+1);
        SelectObject (hDC, OldPen);
#endif

        break;
      case BTN_IN   : 

#ifdef WIN32
        if (AnzButtons > 1)
          Style |= BTN_CHECKED;

        DrawButtonEx (hDC, LPRECT(&ToolRect), Style);
#else
        OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));

        if (AnzButtons > 1) {
          OldBrush = SelectObject (hDC, DnBrush);
          DnBrush = SelectObject (hDC, OldBrush);
          UnrealizeObject (DnBrush);
          SetBrushOrg (hDC, ToolRect.left, ToolRect.top+1);
          OldBrush = SelectObject (hDC, DnBrush);
          }
        else 
          OldBrush = SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));  

        Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                        ToolRect.right, ToolRect.bottom);

        DeleteObject (SelectObject(hDC, OldPen));
        SelectObject (hDC, OldBrush);
#endif

        break;
      case BTN_HOLD : 

#ifdef WIN32
        DrawButtonEx (hDC, LPRECT(&ToolRect), Style);
#else
        OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
        OldBrush = SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
        Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                        ToolRect.right, ToolRect.bottom);
        MoveToEx (hDC, ToolRect.left+2, ToolRect.bottom-1,NULL);
        LineTo (hDC, ToolRect.left+2, ToolRect.top+2);
        LineTo (hDC, ToolRect.right-1, ToolRect.top+2);

        SelectObject (hDC, OldBrush);
        DeleteObject (SelectObject(hDC, OldPen));
#endif

        break;
    }
  }

  if (hBmp != 0) {
    OldBitmap = (HBITMAP)SelectObject (hMemDC, hBmp);

    BitBlt (hDC, ToolRect.left+OffX+1, ToolRect.top+OffY,
                  bmWidth, bmHeight,
            hMemDC,
                  int (lpBmpRef[Index].Col) * bmWidth,
                  int (lpBmpRef[Index].Row) * bmHeight,
                  SRCCOPY
          );

    SelectObject (hMemDC, OldBitmap);
    }


  if (Style & BTN_CHECK) {
    }
  else {
    // schwarzen Rahmen um den Button zeichnen 
#ifndef WIN32
    OldBrush = SelectObject(hDC, GetStockObject(NULL_BRUSH));
    OldPen = SelectObject (hDC, GetStockObject(BLACK_PEN));

    MoveToEx (hDC, ToolRect.left+1, ToolRect.top, NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.top);
    MoveToEx (hDC, ToolRect.left+1, ToolRect.bottom-1, NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);

    MoveToEx (hDC, ToolRect.left, ToolRect.top+1, NULL);
    LineTo (hDC, ToolRect.left, ToolRect.bottom-1);
    MoveToEx (hDC, ToolRect.right-1, ToolRect.top+1, NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);

    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);
#endif
    }
  
  if (!IsEnabled) {
    if ((Index < 2) && (hBmp)) {
      // Gitter darueber legen
      DrawDisabledBmp (hDC, hBmp, ToolRect.left+OffX+1, ToolRect.top+OffY, 
                       bmWidth, bmHeight,
                       int (lpBmpRef[Index].Col) * bmWidth,
                       int (lpBmpRef[Index].Row) * bmHeight);
      
/*
      LOGBRUSH LogBrush;

      OldBitmap = SelectObject (hMemDC, hBmp);
   
      OldBrush = SelectObject(hDC, CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0)));
      PatBlt (hDC, ToolRect.left+OffX+1, ToolRect.top+OffY, bmWidth, bmHeight, PATCOPY);
      DeleteObject (SelectObject(hDC, OldBrush));

      LogBrush.lbStyle = BS_PATTERN;
#ifdef WIN32
      LogBrush.lbHatch = long(LoadBitmap(hLibInst, "DisableBits"));
#else
      LogBrush.lbHatch = LoadBitmap(hLibInst, "DisableBits");
#endif
      OldBrush = SelectObject (hDC, CreateBrushIndirect(&LogBrush));
      
      BitBlt (hDC, ToolRect.left+OffX+1, ToolRect.top+OffY, bmWidth, bmHeight,
              hMemDC, 
              int (lpBmpRef[Index].Col) * bmWidth,
              int (lpBmpRef[Index].Row) * bmHeight,
              0x00A803A9);

      DeleteObject(SelectObject(hDC, OldBrush));
      DeleteObject(HBITMAP(LogBrush.lbHatch));

      SelectObject (hMemDC, OldBitmap);
*/
      }
    }

  DeleteDC (hMemDC);
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }



void PushButton::PaintFocus (DWORD State) 
  {
  if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());

#ifdef WIN32    
    HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
    HPEN   OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));

    Rectangle (hDC, ToolRect.left, ToolRect.top, ToolRect.right-1, ToolRect.bottom);

    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);

    if (IsPressed) {
      HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
      HPEN   OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));

      Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                      ToolRect.right-2, ToolRect.bottom-1);

      DeleteObject (SelectObject (hDC,OldPen));
      SelectObject (hDC, OldBrush);
      }
    else {
      RECT rc;
      CopyRect (&rc,LPRECT (&ToolRect));
      InflateRect (&rc, -1, -1);

      if (State & BTN_CHECKED)
        MyDrawEdge (hDC, &rc, MY_EDGE_BUTTONDOWN, MY_BF_RECT);
      else
        MyDrawEdge (hDC, &rc, MY_EDGE_BUTTONUP, MY_BF_RECT);
      }
#else
    HBRUSH OldBrush = SelectObject(hDC, GetStockObject(NULL_BRUSH));
    HPEN   OldPen = SelectObject (hDC, GetStockObject(BLACK_PEN));

    Rectangle (hDC, ToolRect.left-1, ToolRect.top, ToolRect.right+1, ToolRect.bottom);
    Rectangle (hDC, ToolRect.left, ToolRect.top-1, ToolRect.right, ToolRect.bottom+1);

    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);
#endif

    ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
    }
  } 



void PushButton::PaintState ()
  {
  int BtnSInd;
  int BtnEInd;

  if ((IsPressed) && (AnzButtons > 1))  // Knopf gedr�ckt und Multibitmap
    BtnSInd = 1 ;
  else
    BtnSInd = 0 ;

  if ((!IsEnabled) && (AnzButtons > 2)) // Knopf disabled und Multibitmap
    BtnEInd = 2 ;
  else
    BtnEInd = 0 ;

  BtnSInd += BtnEInd;
  if (BtnSInd > 2)
    BtnSInd = 2;

  DWORD State;

  State = IsPressed ? BTN_IN : BTN_OUT;

  PaintButton (State, BtnSInd);
  PaintFocus (State);
  }


void PushButton::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  const int BORDER = 3;

  RECT rc, rcFrame;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, BORDER-2, BORDER-1);

  CopyRect (&rcFrame, &rc);
  rcFrame.right = rcFrame.left+BORDER;
  InvalidateRect (Parent->Parent->hWndToolbar(), &rcFrame, TRUE);

  CopyRect (&rcFrame, &rc);
  rcFrame.bottom = rcFrame.top+BORDER;
  InvalidateRect (Parent->Parent->hWndToolbar(), &rcFrame, TRUE);

  CopyRect (&rcFrame, &rc);
  rcFrame.left = rcFrame.right-BORDER;
  InvalidateRect (Parent->Parent->hWndToolbar(), &rcFrame, TRUE);

  CopyRect (&rcFrame, &rc);
  rcFrame.top = rcFrame.bottom-BORDER;
  InvalidateRect (Parent->Parent->hWndToolbar(), &rcFrame, TRUE);

  // Focus natuerlich nur setzen, wenn vorher keiner da war
  if (state && /*(this != Parent->Parent->ToolWithFocus) &&*/
      (GetFocus() != Parent->Parent->hWndToolbar()))
    SetFocus (Parent->Parent->hWndToolbar());
  }


void PushButton::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 2, 2);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }

/*--------------------------------------------------------------------*\
* member function:  PressIn                                            *
*                                                                      *
\*--------------------------------------------------------------------*/
void PushButton::PressIn ()
  {
  if ((!IsPressed) && (IsEnabled)) {
    IsPressed = TRUE ;

    Invalidate (FALSE);
//    PaintState ();
    }
  }

/*--------------------------------------------------------------------*\
* member function:  PressOut                                           *
*                                                                      *
\*--------------------------------------------------------------------*/
void PushButton::PressOut ()
  {
  if (IsPressed) {
    IsPressed = FALSE ;

    Invalidate (FALSE);
//    PaintState ();
    }
  }

/*--------------------------------------------------------------------*\
* member function:  On_LButtonDown                                     *
*                                                                      *
\*--------------------------------------------------------------------*/
void PushButton::On_LButtonDown (LPPOINT pt)
  {
  IsPressed = FALSE;
  Capturing = TRUE;
  SetCapture (Parent->Parent->hWndToolbar());
  if (HitTest(pt)) 
    PressIn ();
  }

/*--------------------------------------------------------------------*\
* member function:  On_MouseMove                                       *
*                                                                      *
\*--------------------------------------------------------------------*/
void PushButton::On_MouseMove (LPPOINT pt)
  {
    if (HitTest(pt))
      PressIn();
    else
      PressOut();
  }



/*--------------------------------------------------------------------*\
* member function:  On_LButtonUp                                       *
*                                                                      *
\*--------------------------------------------------------------------*/
BOOL PushButton::On_LButtonUp (LPPOINT pt)
  {
  ReleaseCapture ();
  PressOut();
  Capturing = FALSE;
//  if (MemDC > 0)
//    DeleteDC (MemDC);
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  MemDC = 0;
//  CapDC = 0;

  if (HitTest(pt)) {
    (* CallCommand) (privData, Param()->Id,Param());
    }
  return TRUE;
  }


extern void InterpreteHotkey (int iVirtKey, int iModify, LPSTR szHotKey);

void PushButton::OnRButtonDown (HMENU hPopupMenu)
  {
  tool::OnRButtonDown (hPopupMenu);

  UINT Flags = MF_STRING;

  char szMenuText[40];
  char szHotKey[20];
  
  // ein bisschen was steht schon einmal im Menu

  lstrcpy (szMenuText, "Hotkey\t");
  HotKey FAR *hk = GetHotKey (this);

  // Hotkeydaten auswerten und in Text umwandeln

  if (hk != NULL) {
    InterpreteHotkey (hk->KeyData.VirtKey, hk->KeyData.Modify, szHotKey);
    if (szHotKey[0] != '\0') {
      lstrcat (szMenuText, szHotKey);
      InterpreteHotkey (hk->KeyData.VirtKey1, hk->KeyData.Modify1, szHotKey);
      if (szHotKey[0] != '\0') {
        lstrcat (szMenuText, ", ");
        lstrcat (szMenuText, szHotKey);
        }
      }
    }
  else
    Flags |= MF_GRAYED;  // keine Hotkeydaten

  AppendMenu (hPopupMenu, Flags, IDM_HOTKEY, szMenuText);
  }

void PushButton::FixConnection ()
  {
  tool::FixConnection ();
  (* SetConnection) (privData,Param()->Disabled,StructData);
  }

BOOL PushButton::OnChar (WORD wP)
  {
  if (wP == VK_SPACE) {
    HotKeyAction (FALSE);
    return TRUE;
    }
  else
    return FALSE;  
  }

/********************************************************************\
*                           Check-Button                             *
\********************************************************************/


/*--------------------------------------------------------------------*\
* member function:  virtual void Load                                  *
* wird von der Funktion SetControl aufgerufen                          *
*                                                                      *
* Aufruf der Prozedur GetData mit                                      *
*   Parameter:    Root->PrivData ... Daten des Elternfensters          *
*                 Param()->Id ...... Id aus der struct <tool_button>   *
*   R�ckgabewert: Zeiger auf einen BOOLEAN                             *
*                                                                      *
* Setzt den Button-Status auf den R�ckgabewert von GetData             *
\*--------------------------------------------------------------------*/
void CheckButton::Load ()
  {
  PushButton::Load ();
  AnzButtons = (Param()->hd.structSize + sizeof(WORD) - 
                        sizeof (tool_button)) / sizeof(BitMapRef) + 1;
  DBBOOL FAR *lpState = (DBBOOL FAR *) (* GetData) (privData,Param()->Id);
  if (lpState != NULL)
    ButtonState = *lpState;
  else {
    ButtonState = FALSE;
    (* SetData) (privData,Param()->Id,&ButtonState,sizeof(DBBOOL),StructData);
    }
  }


void CheckButton::FixConnection ()
  {
  PushButton::FixConnection ();
  (* SetConnection) (privData, Param()->Id, StructData);
  }

void CheckButton::Reset (BOOL doClear)
  {
  PushButton::Reset (doClear);
  (* ClearConnection) (privData, Param()->Id, StructData);
  }


//***************************************************************************
// HotKeyAction
//
// Zweck: Setzen des Knopfstatus im Script
//***************************************************************************
void CheckButton::HotKeyAction (BOOL dontCheckEnabled)
  {
  if (!GetCapture()) {
    if ((IsEnabled) || (dontCheckEnabled)) {
      ButtonState = !ButtonState;
  
      PressOut();
      Invalidate (FALSE);
  
      (* SetData) (privData, Param()->Id, &ButtonState,
                  sizeof(DBBOOL), StructData);
      }
    }
  }


/*--------------------------------------------------------------------*\
* member function:  On_LButtonUp                                       *
*                                                                      *
\*--------------------------------------------------------------------*/
BOOL CheckButton::On_LButtonUp (LPPOINT pt)
  {
    ReleaseCapture ();
    Capturing = FALSE;

    if (HitTest(pt)) {
/*
      ButtonState = !ButtonState;

      PressOut();

      (* SetData) (privData, Param()->Id, &ButtonState,
                   sizeof(DBBOOL), StructData);
*/
      HotKeyAction (FALSE);
      }

    return TRUE;
  }


void CheckButton::PaintState ()
  {
  int BtnSInd;
  
  if (AnzButtons > 1) {
    if ((ButtonState) && (!IsPressed))  
      BtnSInd = 1;
    else
      BtnSInd = 0;
    }
  else
    BtnSInd = 0;

  DWORD State;

  if ((!IsPressed) && (!ButtonState))
    State = BTN_OUT;      // Knopf raus
  else
    if (IsPressed) 
      State = BTN_HOLD;   // Knopf ganz tief
    else
    if (ButtonState) 
      State = BTN_IN;     // Knopf gedr�ckt

  PaintButton (State, BtnSInd);

  if (BtnSInd == 1)
    State |= BTN_CHECKED;

  PushButton::PaintFocus (State);
  }


BOOL CheckButton::OnChar (WORD wP)
  {
  if (wP == VK_SPACE)
    HotKeyAction (FALSE);
  return TRUE;
  }


/********************************************************************\
*                        PushCheckButton                             *
\********************************************************************/
void PushCheckButton::HotKeyAction (BOOL dontCheckEnabled)
  {
  if (!GetCapture()) {
    if ((IsEnabled) || (dontCheckEnabled)) {
      (* CallCommand) (privData, Param()->Proc,Param());
      IsPressed = FALSE;
      Invalidate (FALSE);
      }
    }
  }

BOOL PushCheckButton::On_LButtonUp (LPPOINT pt)
  {
  ReleaseCapture ();
  Capturing = FALSE;

  if (HitTest(pt))
    HotKeyAction (TRUE);

//  if (MemDC > 0)
//    DeleteDC (MemDC);
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  MemDC = 0;
//  CapDC = 0;

  return TRUE;
  }

/********************************************************************\
*                        Text - Push - Button                        *
\********************************************************************/
void TextPushButton::Load ()
  {
  DBINT FAR *lpw = (DBINT FAR *)(*GetData)(privData, Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(*GetData)(privData, Param()->_h);
  DBINT FAR *lpFormat = (DBINT FAR *)(*GetData)(privData, FormatRef());
  DBWIN_ASSERT ((lpw != NULL) && (lph != NULL) && (lpFormat != NULL));
  tw = *lpw;
  th = *lph;
  Format = *lpFormat;

  if (field == NULL) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    SetRectEmpty (LPRECT (&TextRect));
    SetTwips (hDC);
    int w = GetTextWidth (hDC);
    ReleaseDC (Parent->Parent->hWndToolbar() ,hDC);

    field = new cField (TRANSPARENT, Format, 0, 0, w, -1, FALSE);
    int dummy;
    field->InstallCallBack (GetFieldCallback(), &dummy, sizeof(dummy));
    field->SetWindow (Parent->Parent->hWndToolbar());
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetWOrg (0,0);
    }

  LPSTR Text = (LPSTR) (* GetData) (privData,Param()->ButtonText);
  if (Text != NULL) {
    char iText[256];
    GetHKText (iText,Text,Format);
    *field = iText;
    }
  else
    *field = "";

  PushButton::Load ();
  }


void TextPushButton::FixConnection ()
  {
  PushButton::FixConnection ();
  (* SetConnection) (privData, Param()->ButtonText, StructData);
  (* SetConnection) (privData, Param()->_w, StructData);
  (* SetConnection) (privData, Param()->_h, StructData);
  }


void TextPushButton::Reset (BOOL doClear)
  {
  PushButton::Reset (doClear);
  (* ClearConnection) (privData, Param()->ButtonText, StructData);
  if (ButtonText != NULL) FreeGlobMem (ButtonText);
  ButtonText = NULL;
  if (field != NULL)
    delete field;
    
  field = NULL;  

  (* ClearConnection) (privData, Param()->_w, StructData);
  (* ClearConnection) (privData, Param()->_h, StructData);
  }


#define BTXT_SPACING 5
void TextPushButton::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  RECT r;
  field->GetFieldRect (&r,0);
  RectToDev (&r) ;
  int textwidth = r.right  - r.left + 1;
  int textheight = r.bottom - r.top  + 1;

  int x0 = ToDevKoordX (tx);
  int y0 = ToDevKoordY (ty, Parent->Layer);
  int x1 = x0 + ToDevX (tw);
  int y1 = y0 + ToDevY (th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));

  int xm = (ToolRect.left + ToolRect.right)  / 2;
  int ym = (ToolRect.top  + ToolRect.bottom) / 2;
  TextRect.left   = ToolRect.left + BTXT_SPACING + r.left;
  TextRect.right  = TextRect.left + textwidth + 1;
  TextRect.top    = ym - textheight / 2 ;
  TextRect.bottom = ym + textheight / 2 ;
  
  //---------------------------------------------------------------------
  // passt der Text von der Hoehe nicht in den Knopf wird die Anzahl der
  // Zeilen die der Text benoetigt solange verringert, bis der Text
  // im Knopf Platz hat. Dadurch geht leider auch Text verloren
  //---------------------------------------------------------------------
  int Lines = field->GetAnzLines ();
  while ((Lines > 1) && ((TextRect.bottom - TextRect.top) > (ToolRect.bottom - ToolRect.top - 8))) {
    field->SetAnzLines (Lines - 1);
    field->Reformat();
    Lines = field->GetAnzLines ();

    //-------------------------------------------------
    // Ausdehnung des neu formatierten Textes berechnen
    field->GetFieldRect (&r,0);
    RectToDev (&r) ;
    textwidth = r.right  - r.left + 1;
    textheight = r.bottom - r.top  + 1;
    
    TextRect.left   = ToolRect.left + BTXT_SPACING + r.left;
    TextRect.right  = ToolRect.right - 5;
    TextRect.top    = ym - textheight / 2 ;
    TextRect.bottom = ym + textheight / 2 ;
    }
  }

void TextPushButton::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    OffsetRect (LPRECT(&TextRect),0,dy);

    Invalidate (FALSE);

#ifdef TOOLTIP
    AddToolTip ();        // neue Position mitteilen
#endif

    }
  }

void TextPushButton::GetTextPos (HDC hDC,LPPOINT p)
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  p->x = ToDevKoordX (tx) ;
  p->y = ToDevKoordY (ty, Parent->Layer) ;
  DPtoLP (hDC,p,1);
  }

int TextPushButton::GetTextWidth (HDC hDC)
  {
  return XtoLOG (hDC,ToDevX(tw) - 2 * BTXT_SPACING);
  }

void TextPushButton::RectToDev (LPRECT r)
  {
  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  SetTwips (hDC);
  POINT pt[2];
  pt[0].x = r->left  , pt[0].y = r->top ;
  pt[1].x = r->right , pt[1].y = r->bottom ;
  LPtoDP (hDC, pt, 2);
  ReleaseDC (Parent->Parent->hWndToolbar() ,hDC);

  r->left  = pt[0].x , r->top    = pt[0].y ;
  r->right = pt[1].x , r->bottom = pt[1].y ;
  }

void TextPushButton::SetMMText (HDC hDC)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void TextPushButton::SetTwips (HDC hDC,int x,int y)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440, NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,x,y, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }


void TextPushButton::DrawButtonText (HDC hDC, int Offset)
  {
  int x = ToolRect.left+BTXT_SPACING;
  if (IsEnabled) {
    SetTwips (hDC, x+Offset, TextRect.top+Offset);
    field->Paint (hDC, 0, FALSE);
    }
  else {
    SetTwips (hDC, x, TextRect.top);
    field->SetOutColor (RGB(0x80, 0x80, 0x80));
    field->Paint (hDC, 0, FALSE);
    SetTwips (hDC, x+1, TextRect.top+1);
    field->SetOutColor (RGB(0xFF, 0xFF, 0xFF));
    field->Paint (hDC, 0, FALSE);
    field->UseDefOutColor();
    }
  SetMMText (hDC);  
  }


void TextPushButton::PaintButton (DWORD Style, int Index)
  {
#ifndef WIN32
  HBRUSH  OldBrush;
  HPEN    OldPen;
#endif

  int     Offset;

  HDC hDC = GetDC(Parent->Parent->hWndToolbar());
  HDC hMemDC = CreateCompatibleDC(hDC);

//  switch (Style) {
//    case BTN_OUT  : 
  if (Style == BTN_OUT) {
    Offset = 0;
#ifdef WIN32
    DrawButtonEx (hDC, LPRECT(&ToolRect), Style);
#else
    OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
    OldBrush = SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
    Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                    ToolRect.right-1, ToolRect.bottom-1);

    MoveToEx (hDC, ToolRect.left+2, ToolRect.bottom-3,NULL);
    LineTo (hDC, ToolRect.right-3, ToolRect.bottom-3);
    LineTo (hDC, ToolRect.right-3, ToolRect.top+1);

    SelectObject (hDC, OldBrush);
    DeleteObject (SelectObject(hDC, OldPen));

    OldPen = SelectObject (hDC, GetStockObject(WHITE_PEN));
    MoveToEx (hDC, ToolRect.left+1, ToolRect.bottom-3,NULL);
    LineTo (hDC, ToolRect.left+1, ToolRect.top+1);
    LineTo (hDC, ToolRect.right-2, ToolRect.top+1);

    MoveToEx (hDC, ToolRect.left+2, ToolRect.bottom-4,NULL);
    LineTo (hDC, ToolRect.left+2, ToolRect.top+2);
    LineTo (hDC, ToolRect.right-3, ToolRect.top+2);

    SelectObject (hDC, OldPen);
#endif
    }
  else if ((Style & BTN_IN) | (Style & BTN_HOLD)) {
//      break;
//    case BTN_IN   : 
//    case BTN_HOLD :
    Offset = 1;

#ifdef WIN32
    DrawButtonEx (hDC, LPRECT(&ToolRect), Style);
#else
    OldPen = SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  
    if (Style == BTN_IN) 
      OldBrush = SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
    else {
      UnrealizeObject (DnBrush);
      SetBrushOrg (hDC, ToolRect.left, ToolRect.top+1);
      OldBrush = SelectObject (hDC, DnBrush);
      }

    Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, 
                    ToolRect.right, ToolRect.bottom);

    DeleteObject (SelectObject(hDC, OldPen));
    SelectObject (hDC, OldBrush);
#endif
    }
//      break;
//    }

////////////////////////////////////////////////////////
  DrawButtonText (hDC, Offset);

//  OldBrush = SelectObject(hDC, GetStockObject(NULL_BRUSH));
#ifndef WIN32
    OldPen = SelectObject (hDC, GetStockObject(BLACK_PEN));

    MoveToEx (hDC, ToolRect.left+1, ToolRect.top,NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.top);
    MoveToEx (hDC, ToolRect.left+1, ToolRect.bottom-1,NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);

    MoveToEx (hDC, ToolRect.left, ToolRect.top+1,NULL);
    LineTo (hDC, ToolRect.left, ToolRect.bottom-1);
    MoveToEx (hDC, ToolRect.right-1, ToolRect.top+1,NULL);
    LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);

    SelectObject (hDC, OldPen);
#endif
//  SelectObject (hDC, OldBrush);


  if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
    RECT rc;
    CopyRect (&rc,LPRECT (&TextRect));
    OffsetRect (&rc, Offset-1, Offset);
    InflateRect (&rc, 1, 1);

    PaintFocusRect (hDC, rc);
    }
    
  DeleteDC (hMemDC);
  ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
  }


void TextPushButton::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  RECT  rc;

  PushButton::SetToolFocus (state, select,mode);
  
  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, -4, -4);
  InvalidateRect (Parent->Parent->hWndToolbar(), &rc, FALSE);
  }
  


void TextPushButton::PaintFocus (DWORD State) 
  {
  if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
    PushButton::PaintFocus (State);

/*    
    HBRUSH OldBrush = SelectObject(hDC, GetStockObject(NULL_BRUSH));
    HPEN   OldPen = SelectObject (hDC, GetStockObject(BLACK_PEN));

    Rectangle (hDC, ToolRect.left-1, ToolRect.top, ToolRect.right+1, ToolRect.bottom);
    Rectangle (hDC, ToolRect.left, ToolRect.top-1, ToolRect.right, ToolRect.bottom+1);

    SelectObject (hDC, OldPen);
    SelectObject (hDC, OldBrush);
*/
    }
  }

//***************************************************************************
// HotKeyAction
//
// Zweck: Aufruf der Script-Prozedur
//***************************************************************************
void TextRadioButton::HotKeyAction (BOOL dontCheckEnabled)
  {
  if (!GetCapture())
    if (IsEnabled)
      (* CallCommand) (privData, Param()->Proc,Param());
  }

BOOL TextRadioButton::On_LButtonUp (LPPOINT pt)
  {
    ReleaseCapture ();
    Capturing = FALSE;

//    DeleteDC (MemDC);
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//    MemDC = 0;
//    CapDC = 0;

    if (HitTest(pt)) {
      Invalidate (TRUE);
      HotKeyAction (TRUE);
      IsPressed = FALSE;
      }


    return TRUE;
  }

/********************************************************************\
*                                                                    *
*               Text - Push - Check - Button                         *
*                                                                    *
\********************************************************************/
void TextPushCheckButton::Load ()
  {
  TextPushButton::Load ();
  
  DBBOOL FAR *lpState = (DBBOOL FAR *) (* GetData) (privData,Param()->State);
  if (lpState != NULL)
    ButtonState = *lpState;
  else {
    ButtonState = FALSE;
    (* SetData) (privData,Param()->State,&ButtonState,sizeof(DBBOOL),StructData);
    }
  }


void TextPushCheckButton::FixConnection ()
  {
  TextPushButton::FixConnection ();
  (* SetConnection) (privData, Param()->State, StructData);
  }

void TextPushCheckButton::Reset (BOOL doClear)
  {
  TextPushButton::Reset (doClear);
  (* ClearConnection) (privData, Param()->State, StructData);
  }


void TextPushCheckButton::PaintState ()
  {
  DWORD State;

  if ((!IsPressed) && (!ButtonState))
    State = BTN_OUT;      // Knopf raus
  else
    if (IsPressed) 
      State = BTN_IN;   // Knopf ganz tief
    else
    if (ButtonState)
      State = BTN_HOLD | BTN_CHECKED;     // Knopf gedrueckt

  PaintButton (State, 0);
  TextPushButton::PaintFocus (State);
  }

/*
BOOL TextPushCheckButton::OnChar (WORD wP)
  {
  if (wP == VK_SPACE)
    HotKeyAction ();
  return TRUE;
  }
*/

//***************************************************************************
// HotKeyAction
//
// Zweck: Aufruf der Script-Prozedur
//***************************************************************************
void TextPushCheckButton::HotKeyAction (BOOL dontCheckEnabled)
  {
  if (!GetCapture()) {
    if ((IsEnabled) || (dontCheckEnabled)) {
      (* CallCommand) (privData, Param()->Proc, Param());
      IsPressed = FALSE;
      Invalidate (FALSE);
      }
    }
  }

BOOL TextPushCheckButton::On_LButtonUp (LPPOINT pt)
  {
  ReleaseCapture ();
  Capturing = FALSE;

  if (HitTest(pt))
    HotKeyAction (TRUE);

//  if (MemDC > 0)
//    DeleteDC (MemDC);
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  MemDC = 0;
//  CapDC = 0;

  return TRUE;
  }


/********************************************************************\
*               Bitmap - Text - Push - Button                        *
\********************************************************************/
void BmpTextPushButton::Load ()
  {
  int AnzRows, AnzCols;
  BITMAP bi;


  HBITMAP hBmp = GetBitmap (BitRef()->bitId, 
                            AnzRows, AnzCols);
  if (hBmp) {
    GetObject (hBmp,sizeof(bi),&bi);
    bmWidth  = bi.bmWidth  / AnzCols ;
    bmHeight = bi.bmHeight / AnzRows ;
    }
  else
    bmWidth  = bmHeight = 0;

  TextPushButton::Load ();
  }
  

int BmpTextPushButton::GetTextWidth (HDC hDC)
  {
  return XtoLOG (hDC,ToDevX(tw) - 3 * BTXT_SPACING - bmWidth);
  }


void BmpTextPushButton::GetRect ()
  {
  RECT r;
  field->GetFieldRect (&r,0);
  RectToDev (&r) ;
  int textwidth = r.right  - r.left + 1;
  int textheight = r.bottom - r.top  + 1;

  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int x1 = x0 + ToDevX(tw);
  int y1 = y0 + ToDevY(th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));

  int xm = (ToolRect.left + 2 * BTXT_SPACING + bmWidth + ToolRect.right)  / 2;
  int ym = (ToolRect.top  + ToolRect.bottom) / 2;
  TextRect.left   = ToolRect.left + 2 * BTXT_SPACING + bmWidth + r.left;
  TextRect.right  = TextRect.left + textwidth+1;
  TextRect.top    = ym - textheight / 2 ;
  TextRect.bottom = ym + textheight / 2 ;
  
  //---------------------------------------------------------------------
  // passt der Text von der Hoehe nicht in den Knopf wird die Anzahl der
  // Zeilen die der Text benoetigt solange verringert, bis der Text
  // im Knopf Platz hat. Dadurch geht leider auch Text verloren
  //---------------------------------------------------------------------
  int Lines = field->GetAnzLines ();
  while ((Lines > 1) && ((TextRect.bottom - TextRect.top) > (ToolRect.bottom - ToolRect.top - 8))) {
    field->SetAnzLines (Lines - 1);
    field->Reformat();
    Lines = field->GetAnzLines ();

    //-------------------------------------------------
    // Ausdehnung des neu formatierten Textes berechnen
    field->GetFieldRect (&r,0);
    RectToDev (&r) ;
    textwidth = r.right  - r.left + 1;
    textheight = r.bottom - r.top  + 1;
    
    TextRect.left   = ToolRect.left + 2 * BTXT_SPACING + bmWidth + r.left;
    TextRect.right  = ToolRect.right - 5;
    TextRect.top    = ym - textheight / 2 ;
    TextRect.bottom = ym + textheight / 2 ;
    }
  }


void BmpTextPushButton::DrawButtonText (HDC hDC, int Offset)
  {
  int x = ToolRect.left + 2 * BTXT_SPACING + bmWidth;
  if (IsEnabled) {
    SetTwips (hDC, x+Offset, TextRect.top+Offset);
    field->Paint (hDC, 0, FALSE);
    }
  else {
    SetTwips (hDC, x, TextRect.top);
    field->SetOutColor (RGB(0x80, 0x80, 0x80));
    field->Paint (hDC, 0, FALSE);
    SetTwips (hDC, x+1, TextRect.top+1);
    field->SetOutColor (RGB(0xFF, 0xFF, 0xFF));
    field->Paint (hDC, 0, FALSE);
    field->UseDefOutColor();
    }
  SetMMText (hDC);  
  }

  
void BmpTextPushButton::PaintButton (DWORD Style, int Index)
  {
  TextPushButton::PaintButton (Style, Index);

  HDC hDC = GetDC(Parent->Parent->hWndToolbar());
  HDC hMemDC = CreateCompatibleDC(hDC);
  
  int AnzCols, AnzRows;
  HBITMAP hBmp = GetBitmap (BitRef()->bitId, 
                            AnzRows, AnzCols);
  int OffX = bmWidth;
  int OffY = bmHeight;
  
  CalcOffset (Style, &OffX, &OffY);
  int ym = (ToolRect.top  + ToolRect.bottom) / 2;
  
  if (hBmp != 0) {
    if (IsEnabled) {
      HBITMAP OldBitmap = (HBITMAP)SelectObject (hMemDC, hBmp);
      BitBlt (hDC, ToolRect.left+OffX+BTXT_SPACING, ym-bmWidth/2+OffY-1,
                  bmWidth, bmHeight,
              hMemDC,
                  int (lpBmpRef[0].Col) * bmWidth,
                  int (lpBmpRef[0].Row) * bmHeight,
                  SRCCOPY);
      SelectObject (hMemDC, OldBitmap);
      }
    else
      DrawDisabledBmp (hDC, hBmp, ToolRect.left+OffX+BTXT_SPACING, 
                                  ym-bmWidth/2+OffY-1, 
                       bmWidth, bmHeight,
                       int (lpBmpRef[0].Col) * bmWidth,
                       int (lpBmpRef[0].Row) * bmHeight);
    }

  DeleteDC (hMemDC);
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }




/********************************************************************\
*                        Text - Check - Button                       *
\********************************************************************/

/*--------------------------------------------------------------------*\
* member function:  virtual void Load                                  *
* wird von der Funktion SetControl aufgerufen                          *
*                                                                      *
* Aufruf der Prozedur GetData mit                                      *
*   Parameter:    Root->PrivData ... Daten des Elternfensters          *
*                 Param()->Id ...... Id aus der struct <tool_button>   *
*   R�ckgabewert: Zeiger auf einen BOOLEAN                             *
*                                                                      *
* Setzt den Button-Status auf den R�ckgabewert von GetData             *
\*--------------------------------------------------------------------*/
void TextCheckButton::Load ()
  {
  DBINT FAR *lpw = (DBINT FAR *)(*GetData)(privData, Param()->_w);
  DBINT FAR *lpFormat = (DBINT FAR *)(*GetData)(privData, FormatRef());
  DBINT FAR *lpx = (DBINT FAR *)(*GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR *)(*GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpw != NULL) && (lpFormat != NULL) && (lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  tw = *lpw;
  Format = *lpFormat;
  if (field == NULL) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    SetRectEmpty (LPRECT (&TextRect));
    SetTwips (hDC);
    int w = GetTextWidth (hDC);
    ReleaseDC (Parent->Parent->hWndToolbar() ,hDC);

    field = new cField (TRANSPARENT, Format, 0, 0, w, -1, FALSE);
    int dummy;
    field->InstallCallBack (GetFieldCallback(), &dummy, sizeof(dummy));
    field->SetWindow (Parent->Parent->hWndToolbar());
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetWOrg (0,0);
    }

  LPSTR Text = (LPSTR) (* GetData) (privData,CheckText());
  if (Text != NULL) {
    char iText[256];
    GetHKText (iText,Text,Format);
    *field = iText;
    }
  else
    *field = "";

  CheckButton::Load ();
  }


void TextCheckButton::FixConnection ()
  {
  CheckButton::FixConnection ();
  (* SetConnection) (privData, Param()->CheckText, StructData);
  (* SetConnection) (privData, Param()->_w, StructData);
  }

void TextCheckButton::Reset (BOOL doClear)
  {
  CheckButton::Reset (doClear);
  (* ClearConnection) (privData, Param()->CheckText, StructData);
  (* ClearConnection) (privData, Param()->_w, StructData);

  if (field != NULL)
    delete field;
    
  field = NULL;  
  }

void TextCheckButton::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    OffsetRect (LPRECT(&TextRect),0,dy);

    Invalidate (FALSE);
    }

#ifdef TOOLTIP
    AddToolTip ();        // neue Position mitteilen
#endif

  }

int TextCheckButton::GetTextWidth (HDC hDC)
  {
  return XtoLOG (hDC, ToDevX(tw) - 2 * BTXT_SPACING);
  }


//---------------------------------------------------------------------------
// Bestimmt die Groesse des TextCheckButtons.
// Hat der TextCheckButton keinen Text, dann beschraenkt sich die Groesse
// lediglich auf das Bitmap, sonst wird der Text mit eingerechnet.
//---------------------------------------------------------------------------
void TextCheckButton::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  RECT r;
  int AnzRows, AnzCols;
  HBITMAP hBmp = GetBitmap (
                      BitRef()[0].bitId, 
                      AnzRows, AnzCols
                           );
  BITMAP bi;

  int bmWidth,bmHeight;
  if (hBmp) {
    GetObject (hBmp,sizeof(bi),&bi);
    bmWidth  = bi.bmWidth  / AnzCols ;
    bmHeight = bi.bmHeight / AnzRows ;
    }
  else
    bmWidth = bmHeight = 0;


  // hat das Element ueberhaupt einen Text?
  GLOBALHANDLE hgMem;
  *field >> hgMem;
  LPSTR txt = LPSTR(GlobalLock(hgMem));
  BOOL WithText = txt[0] != '\0'; 
  GlobalUnlock (hgMem);
  GlobalFree (hgMem);


  int textheight = 0;
  int textwidth = 0;
  if (WithText) {
    field->GetFieldRect (&r, 0);
    RectToDev (&r);
    textwidth = r.right-r.left+1;
    textheight = r.bottom-r.top+1;
    }


  // Abmessungen des Elementes inklusive Text bestimmen
  int Offset = WithText ? 8 : 0;

  int x0 = ToDevKoordX(tx);
  int x1 = x0 + bmWidth + Offset + textwidth;
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int y1 = (bmHeight > textheight ? y0+bmHeight : y0+textheight);

  SetRect (LPRECT(&ToolRect), x0, y0, x1, y1);

  if (WithText) {
    int TextOffs = (bmHeight > textheight ? textheight/2+1 : bmHeight/2);  // Bitmap > Texth�he ? Text etwas verschieben 

    TextRect.left   = x0+bmWidth+4;
    TextRect.top    = y0+bmHeight/2-TextOffs;
    TextRect.right  = x0+bmWidth+8+textwidth;
    TextRect.bottom = (bmHeight > textheight ? y0+bmHeight/2+TextOffs : y1);
    }

  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + y1-y0);
  }


void TextCheckButton::PaintState ()
  {
  int BtnSInd;
  DWORD State = BTN_OUT | BTN_CHECK;
  
  if (AnzButtons > 1) {
    if (ButtonState) {   // Zeichnung im gedrueckten Zustand
      if (IsPressed)
        BtnSInd = 3;     // Maus ist gerade drauf und gedrueckt
      else {
        if (IsEnabled)
          BtnSInd = 1;   // Maus nicht drauf
        else
          BtnSInd = 4;     
        }    
      }
    else {
      if (IsPressed || !IsEnabled)
        BtnSInd = 2;
      else
        BtnSInd = 0;
      }
    
    if ((!IsPressed) && (!ButtonState))
      State = BTN_OUT | BTN_CHECK;      // Knopf raus
    else {
      if (IsPressed) 
        State = BTN_HOLD | BTN_CHECK;   // Knopf ganz tief
      else
      if (ButtonState) 
        State = BTN_IN | BTN_CHECK;     // Knopf gedrueckt
      } 

    PaintButton (State, BtnSInd);      // Knopf raus
    }
  else
    PushButton::PaintState ();

  HDC hDC = GetDC (Parent->Parent->hWndToolbar());

  if (IsEnabled) {
    SetTwips (hDC, TextRect.left, TextRect.top);
    field->Paint (hDC, 0, FALSE);
    }
  else {
    SetTwips (hDC, TextRect.left, TextRect.top);
    field->SetOutColor (RGB(0x80, 0x80, 0x80));
    field->Paint (hDC, 0, FALSE);
    SetTwips (hDC, TextRect.left+1, TextRect.top+1);
    field->SetOutColor (RGB(0xFF, 0xFF, 0xFF));
    field->Paint (hDC, 0, FALSE);
    field->UseDefOutColor();
    }
  SetMMText (hDC);  
  
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);

  PaintFocus (State);
  }



void TextCheckButton::PaintFocus (DWORD State) 
  {
  if ((Parent->Parent->ToolWithFocus == this) && 
        (GetFocus() == Parent->Parent->hWndToolbar()))
    { 
    RECT  rc;

    CopyRect (&rc, LPRECT(&TextRect));
    InflateRect (&rc, 1, 1);

    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    PaintFocusRect (hDC, rc);
    ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
    }
  }



void TextCheckButton::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  RECT  rc;

  CopyRect (&rc, LPRECT(&TextRect));
  InflateRect (&rc, 2, 2);
  InvalidateRect (Parent->Parent->hWndToolbar(), &rc, !state);

  if (state && /* (this != Parent->Parent->ToolWithFocus) && */
      (GetFocus() != Parent->Parent->hWndToolbar()))
    SetFocus (Parent->Parent->hWndToolbar());  
  }


void TextCheckButton::RectToDev (LPRECT r)
  {
  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  SetTwips (hDC);
  POINT pt[2];
  pt[0].x = r->left  , pt[0].y = r->top ;
  pt[1].x = r->right , pt[1].y = r->bottom ;
  LPtoDP (hDC, pt, 2);
  ReleaseDC (Parent->Parent->hWndToolbar() ,hDC);

  r->left  = pt[0].x , r->top    = pt[0].y ;
  r->right = pt[1].x , r->bottom = pt[1].y ;
  }

void TextCheckButton::SetMMText (HDC hDC)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void TextCheckButton::SetTwips (HDC hDC,int x,int y)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440, NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,x,y, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void  TextCheckButton::SetObjectColor (COLORREF color)
  {
  field->SetOutColor (color);
  }



/********************************************************************\
*                          Combo-Button                              *
\********************************************************************/
typedef ToolEdit FAR *LPTOOLEDIT;


void ComboButton::Load ()
  {
  PushButton::Load();
  // dem Edit-Element die Prozedur fuer den Combo-Button mitteilen
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *)(* GetData)(privData,Param()->EditObj);
  if ((MyEdit != NULL) && (*MyEdit != NULL)/* && IsEnabled*/) {
    (*MyEdit)->SetComboProc (Param()->Id,IsEnabled,this);
    EnableWindow ((*MyEdit)->hWndEdit, IsEnabled);
    }
  }

BOOL ComboButton::HasTabStop ()
  {
  return FALSE;
  }

void ComboButton::MoveTool ()
  {
  // ich nix bewegen, weil ich ja mit dem Edit-Element mitgehe!
  BOOL oldActive;
  if (tbActive != NULL)
    oldActive = (* tbActive) (FALSE);
  GetRect ();
  if (tbActive != NULL)
    (* tbActive) (oldActive);

#ifdef TOOLTIP
    AddToolTip ();        // neue Position mitteilen
#endif
  }

void ComboButton::GetRect ()  
  {
  RECT rc;

  BOOL oldActive;
  if (tbActive != NULL)
    oldActive = (* tbActive) (FALSE);
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *)(* GetData)(privData,Param()->EditObj);
  if (tbActive != NULL)
    (* tbActive) (oldActive);
  if ((MyEdit != NULL) && (*MyEdit != NULL)) {
    CopyRect (&rc, LPRECT(&((* MyEdit)->ToolRect)));
    SetRect (LPRECT(&ToolRect), rc.right+1, rc.top-1, 
                                rc.right+1+((rc.bottom-rc.top)*3)/4+3,
                                rc.bottom+2);
    ty = (* MyEdit)->ty;

    // cField mitteilen, dass es ein zusaetzliches Control besitzt
    WWSetBuddy ((*MyEdit)->hWndEdit, TRUE);
    }
  }
  
void ComboButton::CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh)
  {
  int offx = ((ToolRect.right-ToolRect.left)-*bmw) / 2;
  int offy = ((ToolRect.bottom-ToolRect.top)-*bmh) / 2;
  
  switch (State) {
    case BTN_OUT  : 
      *bmw = offx;
      *bmh = offy;
      break;
    case BTN_IN   : //return offx+4;
      *bmw = offx+1;
      *bmh = offy+1;
      break;
    case BTN_HOLD : //return offx+5;
      *bmw = offx+2;
      *bmh = offy+2;
      break;
    }
  }

void ComboButton::PaintButton (DWORD Style, int Index)
  {
  PushButton::PaintButton (Style, Index);
  
  HDC hDC = GetDC(Parent->Parent->hWndToolbar());
  HDC hMemDC = CreateCompatibleDC(hDC);

  // jetzt kommt die ganze Zeichnerei, um den Combo-Button so darzustellen
  // als ob er in der Edit-Box liegen wuerde.
  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
  HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));

  Rectangle (hDC, ToolRect.left, ToolRect.top, ToolRect.right, ToolRect.bottom);
  SelectObject (hDC, OldPen);
  SelectObject (hDC, OldBrush);

  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, ToolRect.left, ToolRect.top-1,NULL);
  LineTo (hDC, ToolRect.right, ToolRect.top-1);
  DeleteObject (SelectObject (hDC, OldPen));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, ToolRect.left, ToolRect.bottom,NULL);
  LineTo (hDC, ToolRect.right, ToolRect.bottom);
  LineTo (hDC, ToolRect.right, ToolRect.top-2);
  SelectObject (hDC, OldPen);

  DeleteDC (hMemDC);
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }

void ComboButton::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *) (* GetData) (privData,Param()->EditObj);
  if ((MyEdit != NULL) && (*MyEdit != NULL))
    (*MyEdit)->SetToolFocus (state, TRUE,mode);
  }

  
void ComboButton::On_LButtonDown (LPPOINT pt)
  {
  PushButton::On_LButtonDown (pt);
  SetToolFocus (TRUE, TRUE);
  }
  
  
BOOL ComboButton::OnChar (WORD wP)
  {
  if (!PushButton::OnChar(wP)) {
    if (wP == VK_DOWN)
      HotKeyAction (FALSE);
      return TRUE;
    }
  return FALSE;
  }

//*---------------------------------------------------------------------------
//*                          Up-Down-Control                            
//*---------------------------------------------------------------------------
WORD rgColorDef[CCOLORS] = {COLOR_BTNFACE,
                            COLOR_BTNTEXT,
                            COLOR_BTNSHADOW,
                            COLOR_BTNHIGHLIGHT,
                            COLOR_WINDOWFRAME};
const int CLR_FACE = 0;
const int CLR_ARROW = 1;
const int CLR_SHADOW = 2;
const int CLR_HIGHLIGHT = 3;
const int CLR_FRAME = 4;

const int STATE_CLEAR    = 0x0000;
const int STATE_GRAYED   = 0x0001;
const int STATE_HIDDEN   = 0x0002;
const int STATE_MOUSEOUT = 0x0004;
const int STATE_UP       = 0x0008;
const int STATE_DOWN     = 0x0010;
const int STATE_CLICKED  = STATE_UP | STATE_DOWN;

const int CTICKS_FIRSTCLICK = 400;
const int CTICKS_HOLDCLICK  = 50;

void PASCAL Draw3DButtonRect(HDC hDC, HPEN hPenHigh, HPEN hPenShadow,
                             WORD x1, WORD y1, WORD x2, WORD y2,
                             BOOL fClicked)
  {
  HPEN hPenOrg;

  //Shrink the rectangle to account for borders.
  x1 += 1;
  x2 -= 1;
  y1 += 1;
  y2 -= 1;

  hPenOrg = (HPEN)SelectObject(hDC, hPenShadow);

  if (fClicked) {
    //Shadow on left and top edge when clicked.
    MoveToEx(hDC, x1, y2,NULL);
    LineTo(hDC, x1, y1);
    LineTo(hDC, x2+1, y1);
    }
  else {
    //Lowest shadow line.
    MoveToEx(hDC, x1, y2,NULL);
    LineTo(hDC, x2, y2);
    LineTo(hDC, x2, y1-1);
    SelectObject(hDC, hPenHigh);

    //Upper highlight line.
    MoveToEx(hDC, x1,   y2-1,NULL);
    LineTo(hDC, x1,   y1);
    LineTo(hDC, x2,   y1);
    }

  SelectObject(hDC, hPenOrg);
  }


UpDown::UpDown (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
        : tool (RefWnd,Data,pData,pSize)      
  {
  IsEnabled = TRUE ;
//  CapDC = 0;
  FirstTimer = FALSE;
  SecondTimer = FALSE;
  State = STATE_CLEAR;

  for (int iColor = 0; iColor < CCOLORS; iColor++) 
    rgbClr[iColor] = GetSysColor(rgColorDef[iColor]);
  }


void UpDown::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);

  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));

  tx = *lpx;
  ty = *lpy;

  GetRect();

#ifdef TOOLTIP
  AddToolTip ();
#endif

  DBBOOL FAR *IsDisabled = (DBBOOL FAR *) 
          (* GetData) (privData,Param()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));
  if (IsEnabled)
    State &= ~STATE_GRAYED;
  else
    State |= STATE_GRAYED;  
  }


void UpDown::PaintTool (HDC hDC, HDC hmemDC)
  {
  HPEN hPen[CCOLORS];
  POINT       rgpt1[3];
  POINT       rgpt2[3];
  int         xAdd1 = 0, yAdd1 = 0, xAdd2 = 0, yAdd2 = 0;

  // um das ganze einmal den Rahmen wie fuer das Edit-Element zeichnen
  RECT rc;
  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, -1, -1);
  rc.left += 1;

  MyDrawEdge (hDC, LPRECT(&rc), MY_EDGE_HWND, MY_BF_ADJUST);

  for (int iColor = 0; iColor < CCOLORS; iColor++)
    hPen[iColor] = CreatePen(PS_SOLID, 1, rgbClr[iColor]);

  HBRUSH hBrushFace  = CreateSolidBrush(rgbClr[CLR_FACE]);
  HBRUSH hBrushArrow = CreateSolidBrush(rgbClr[CLR_ARROW]);
  HBRUSH hBrushBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);

  int cx = ToolRect.right - ToolRect.left;
  int cy = ToolRect.bottom - ToolRect.top;
  int cx2 = ToolRect.left + (cx  >> 1);
  int cy2 = ToolRect.top + (cy  >> 1);
  int cx4 = ToolRect.left + (cx >> 2);
  int cy4 = ToolRect.top + (cy >> 2);

  //------------------------------------------------------------------
  // Offset fuer die kleinen Pfeilchen im Knopf berechnen
  if (!(State & STATE_MOUSEOUT)) {
    if (State & STATE_UP) {
      xAdd1 = 1;
      yAdd1 = 1;
      }

    if (State & STATE_DOWN) {
      xAdd2 = 1;
      yAdd2 = 1;
      }
    }
  
  
  HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushFace);
  HPEN hOldPen = (HPEN)SelectObject(hDC, hPen[CLR_FRAME]);
  Rectangle(hDC, ToolRect.left, ToolRect.top, ToolRect.right, ToolRect.bottom);


  // Trennlinie zeichnen.
  MoveToEx(hDC, ToolRect.left, cy2,NULL);
  LineTo(hDC, ToolRect.left + cx, cy2);
  SelectObject (hDC, hOldPen);
  SelectObject (hDC, hOldBrush);

  // We do one of three modifications for drawing the borders:
  //  1) Both halves un-clicked.
  //  2) Top clicked,   bottom unclicked.
  //  3) Top unclicked, bottom clicked.
  //
  // Case 1 is xAdd1==xAdd2==0
  // Case 2 is xAdd1==1, xAdd2=0
  // Case 3 is xAdd1==0, xAdd2==1
  //
  // beide Knopfrahmen zeichnen
  Draw3DButtonRect(hDC, hPen[CLR_HIGHLIGHT],
                   hPen[CLR_SHADOW],
                   ToolRect.left, ToolRect.top, ToolRect.left+cx-1, cy2,  xAdd1);

  Draw3DButtonRect(hDC, hPen[CLR_HIGHLIGHT],
                   hPen[CLR_SHADOW],
                   ToolRect.left, cy2, ToolRect.left+cx-1, ToolRect.top+cy-1, xAdd2);

  // Select default line color.
  hOldPen = (HPEN)SelectObject(hDC, hPen[CLR_ARROW]);

  //Draw the arrows depending on the enable state.
  if (State & STATE_GRAYED) {
    // Draw arrow color lines in the upper left of the
    // top arrow and on the top of the bottom arrow.
    // Pen was already selected as a default.
    MoveToEx (hDC, cx2,   cy4-1,NULL);      //Top arrow
    LineTo (hDC, cx2-3, cy4+2);
    MoveToEx(hDC, cx2-3, cy2+cy4-1-ToolRect.top,NULL);  //Bottom arrow
    LineTo(hDC, cx2+3, cy2+cy4-1-ToolRect.top);

    // Draw highlight color lines in the bottom of the
    // top arrow and on the upper right of the bottom arrow.
    SelectObject(hDC, hPen[CLR_HIGHLIGHT]);
    MoveToEx(hDC,   cx2-3, cy4+2,NULL);      //Top arrow
    LineTo(hDC,   cx2+3, cy4+2);
    MoveToEx(hDC,   cx2+3, cy2+cy4-1-ToolRect.top,NULL);  //Bottom arrow
    LineTo(hDC,   cx2,   cy2+cy4+2-ToolRect.top);
    SetPixel(hDC, cx2,   cy2+cy4+2-ToolRect.top, rgbClr[CLR_HIGHLIGHT]);
    }
  else {
    //Top arrow polygon
    rgpt1[0].x = xAdd1+cx2;
    rgpt1[0].y = yAdd1+cy4-1;
    rgpt1[1].x = xAdd1+cx2-3;
    rgpt1[1].y = yAdd1+cy4+2;
    rgpt1[2].x = xAdd1+cx2+3;
    rgpt1[2].y = yAdd1+cy4+2;

    //Bottom arrow polygon
    rgpt2[0].x = xAdd2+cx2;
    rgpt2[0].y = yAdd2+cy2+cy4+2-ToolRect.top;
    rgpt2[1].x = xAdd2+cx2-3;
    rgpt2[1].y = yAdd2+cy2+cy4-1-ToolRect.top;
    rgpt2[2].x = xAdd2+cx2+3;
    rgpt2[2].y = yAdd2+cy2+cy4-1-ToolRect.top;

        //Draw the arrows
    hOldBrush = (HBRUSH)SelectObject(hDC, hBrushArrow);
    Polygon(hDC, (LPPOINT)rgpt1, 3);
    Polygon(hDC, (LPPOINT)rgpt2, 3);
    SelectObject (hDC, hOldBrush);
    }

  SelectObject (hDC, hOldPen);
  DeleteObject(hBrushFace);
  DeleteObject(hBrushArrow);

  for (iColor = 0; iColor < CCOLORS; iColor++)
    DeleteObject(hPen[iColor]);
  }


void UpDown::CalcClickedRect (LPRECT rc)
  {
  CopyRect (rc, LPRECT(&ToolRect));
  int cx = (rc->left + rc->right)  >> 1;
  int cy = (rc->top + rc->bottom) >> 1;

  if (State & STATE_DOWN)
    rc->top = cy;

  if (State & STATE_UP)
    rc->bottom = cy+1;
  }


void UpDown::On_LButtonDown (LPPOINT pt)
  {
  SetCapture (Parent->Parent->hWndToolbar());
  if (HitTest(pt)) {
    int cx = (ToolRect.left + ToolRect.right)  >> 1;
    int cy = (ToolRect.top + ToolRect.bottom) >> 1;
    WORD tmpState = (pt->y > cy) ? STATE_DOWN : STATE_UP;

    State |= tmpState;
    RECT rc;
    CalcClickedRect (&rc);
    InvalidateRect(Parent->Parent->hWndToolbar(), &rc, TRUE);
    UpdateWindow(Parent->Parent->hWndToolbar());

//    PaintTool (CapDC, 0);
    if (State & STATE_UP)
      (* CallCommand) (privData, Param()->UpProc,Param());
    else if (State & STATE_DOWN)
      (* CallCommand) (privData, Param()->DownProc,Param());
    }

  Parent->Parent->InsertToTimerList (this, CTICKS_FIRSTCLICK, NextFreeTimerId++);
  FirstTimer = TRUE;
  }

void UpDown::On_MouseMove (LPPOINT pt)
  {
  // wenn kein Button gedrueckt wurde, dann is nix zu tun
  if (!(State & STATE_CLICKED))
    return;
    
  RECT rc;
  CalcClickedRect (&rc);
  WORD tmpState = State;
  if (PtInRect(&rc, *pt))
    State &= ~(STATE_MOUSEOUT);
  else 
    State |= STATE_MOUSEOUT;

  if (tmpState != State) {
    InvalidateRect(Parent->Parent->hWndToolbar(), &rc, TRUE);
    UpdateWindow(Parent->Parent->hWndToolbar());
    }
//    PaintTool (CapDC, 0);
//      PressIn();
//    else
//      PressOut();
  }

BOOL UpDown::On_LButtonUp (LPPOINT pt)
  {
  Parent->Parent->RemoveFromTimerList (this);
  FirstTimer = FALSE;
  SecondTimer = FALSE;
  ReleaseCapture ();

  if ((State & STATE_CLICKED) && (!(State & STATE_MOUSEOUT))) {
    //Calculate the rectangle before clearing states.
    RECT rc;
    CalcClickedRect (&rc);

    //Clear the states so we repaint properly.
    State &= (~STATE_MOUSEOUT);
    State &= (~STATE_CLICKED);

    InvalidateRect(Parent->Parent->hWndToolbar(), &rc, TRUE);
    UpdateWindow(Parent->Parent->hWndToolbar());
    }
  
  State &= (~STATE_MOUSEOUT);
  State &= (~STATE_CLICKED);
//  PaintTool (CapDC, 0);

//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  CapDC = 0;
  return TRUE;
  }

void UpDown::OnTimer ()
  {
  if (FirstTimer) {
    Parent->Parent->RemoveFromTimerList (this);
    FirstTimer = FALSE;
    }
  if (!SecondTimer) {
    Parent->Parent->InsertToTimerList (this, CTICKS_HOLDCLICK, NextFreeTimerId++);
    SecondTimer = TRUE;
    }

  if (!(State & STATE_MOUSEOUT)) {
    if (State & STATE_UP)
      (* CallCommand) (privData, Param()->UpProc,Param());
    else if (State & STATE_DOWN)
      (* CallCommand) (privData, Param()->DownProc,Param());
    }
  }

void UpDown::MoveTool ()
  {
  }

void UpDown::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 2, 2);
  InvalidateRect (Parent->Parent->hWndToolbar(), &rc, doErase);
  }

void UpDown::GetRect ()  
  {
  RECT rc;

  BOOL oldActive;
  if (tbActive != NULL)
    oldActive = (* tbActive) (FALSE);
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *) 
                           (* GetData) (privData,Param()->EditObj);
  if (tbActive != NULL)
    (* tbActive) (oldActive);
  // Die Groesse des Controls an das Edit-Element anpassen
  if ((MyEdit != NULL) && (*MyEdit != NULL)) {
    CopyRect (&rc, LPRECT(&((* MyEdit)->ToolRect)));
    // das Verhaeltnis Breite zu Hoehe wurde von 3/4 auf 15/23 geaendert!
    SetRect (LPRECT(&ToolRect), rc.right+1, rc.top-1, 
                                rc.right+1+((rc.bottom-rc.top)*15)/23+3,
                                rc.bottom+2);

    ty = (* MyEdit)->ty;
  
    (*MyEdit)->SetUpDownProc (Param()->UpProc, Param()->DownProc);
    // cField mitteilen, dass es ein zusaetzliches Control besitzt
    WWSetBuddy ((*MyEdit)->hWndEdit, TRUE);  
    }
  }
  

BOOL UpDown::HitTest (LPPOINT pt)             
  {
  BOOL GotIt = PtInRect(LPRECT (&ToolRect), *pt);

  return GotIt;
  }

void UpDown::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Disabled,StructData);
  }

void UpDown::Reset (BOOL doClear)
  {
  Parent->Parent->RemoveFromTimerList (this);
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Disabled,StructData);

#ifdef TOOLTIP
  RemoveToolTip ();
#endif
  }


//----------------------------  OnChar  -------------------------------------
//
//
//---------------------------------------------------------------------------
BOOL UpDown::OnChar (WORD wP)
  {
  switch (wP) {
    case VK_UP :
      (* CallCommand) (privData, Param()->UpProc,Param());
      break;
      
    case VK_DOWN :
      (* CallCommand) (privData, Param()->DownProc,Param());
      break;
        
    }
    
  return TRUE;
  }
/*
void UpDown::CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh)
  {
  int offx = ((ToolRect.right-ToolRect.left)-*bmw) / 2;
  int offy = ((ToolRect.bottom-ToolRect.top)-*bmh) / 2;
  
  switch (State) {
    case BTN_OUT  : 
      *bmw = offx;
      *bmh = offy;
      break;
    case BTN_IN   : //return offx+4;
      *bmw = offx+1;
      *bmh = offy+1;
      break;
    case BTN_HOLD : //return offx+5;
      *bmw = offx+2;
      *bmh = offy+2;
      break;
    }
  }
*/


/********************************************************************\
**********************************************************************
**                                                                  **
**                           Tool-Edit                              **
**                                                                  **
**********************************************************************
\********************************************************************/
DLLExport void _export WINAPI SetOnEditChar (DWORD Edit,LPVOID privData,WORD vKey,WORD vModify,DWORD procOffset)
  {
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *)(* GetData) (privData,Edit);
  if ((MyEdit != NULL) && (*MyEdit != NULL)) {
    LPECL n = LPECL (GetGlobMem (sizeof(*n)));
    n->Type = TYPE_CHARTEST ;
    n->vlist.ci.vKey = vKey;
    n->vlist.ci.vModify = vModify;
    n->vlist.ci.procOffset = procOffset;
    n->Next = (*MyEdit)->ecl ;
    (*MyEdit)->ecl = n;
    }
  }

DLLExport void _export WINAPI GetFieldFormat (DWORD Edit,LPVOID privData,DWORD FieldVar)
  {
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *)(* GetData) (privData,Edit);
  if ((MyEdit != NULL) && (*MyEdit != NULL)) {
    LPECL n = LPECL (GetGlobMem (sizeof(*n)));
    n->Type = TYPE_CHARSETFNC ;
    n->vlist.csf.SetStrId = FieldVar;
    n->Next = (*MyEdit)->ecl ;
    (*MyEdit)->ecl = n;
    (*MyEdit)->OnCaretPosChanged();
    }
  }

DLLExport void _export WINAPI GetFieldModify (DWORD Edit,LPVOID privData,DWORD FieldVar)
  {
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *)(* GetData) (privData,Edit);
  if ((MyEdit != NULL) && (*MyEdit != NULL)) {
    LPECL n = LPECL (GetGlobMem (sizeof(*n)));
    n->Type = TYPE_MODIFYFNC ;
    n->vlist.csf.SetStrId = FieldVar;
    n->Next = (*MyEdit)->ecl ;
    (*MyEdit)->ecl = n;
    (*MyEdit)->OnCaretPosChanged();
    }
  }

DLLExport void _export WINAPI SetOnSetFocus (DWORD Edit,LPVOID privData,
                                             DWORD procOffset, BOOL bOnKillFocus)
  {
  LPTOOLEDIT FAR *MyEdit = (LPTOOLEDIT FAR *) (* GetData) (privData,Edit);
  if ((MyEdit != NULL) && (*MyEdit != NULL))
    if (bOnKillFocus)
      (*MyEdit)->CallOnKillFocus = procOffset;
    else
      (*MyEdit)->CallOnSetFocus = procOffset;
  }

DLLExport void _export WINAPI ToolEdit::SetOverwrite ()
  {
  WWSetOverwrite (hWndEdit);
  }

DLLExport void _export WINAPI ToolEdit::SetFieldModify (int Modify,BOOL Set_Clear)
  {
  WWSetModify (hWndEdit,Modify,Set_Clear);
  }

void ToolEdit::OnCaretPosChanged()
  {
  for (LPECL h = ecl; h != NULL ; h = h->Next) {
    if (h->Type == TYPE_CHARSETFNC) {
      DBINT FAR *oldind = (DBINT FAR *)
        (* GetData) (privData,h->vlist.csf.SetStrId);
      int newind = WWGetActFormat (hWndEdit);
      if ((oldind == NULL) || (*oldind != newind))
        (* SetData) (privData,h->vlist.csf.SetStrId,&newind,sizeof(newind),
                      StructData);
      }
    if (h->Type == TYPE_MODIFYFNC) {
      WORD newModify = WWGetActModify (hWndEdit);
      WORD FAR *oldModify = (WORD FAR *)
        (* GetData) (privData,h->vlist.csf.SetStrId);
      if ((oldModify == NULL) || (*oldModify != newModify))
        (* SetData) (privData,h->vlist.csf.SetStrId,&newModify,sizeof(newModify),
                      StructData);
      }
    if (h->Type == TYPE_COLORFNC) {
      DWORD newColor = WWGetActColor (hWndEdit);
      DWORD FAR *oldColor = (DWORD FAR *)
        (* GetData) (privData,h->vlist.csf.SetStrId);
      if ((oldColor == NULL) || (*oldColor != newColor))
        (* SetData) (privData,h->vlist.csf.SetStrId,&newColor,sizeof(newColor),
                      StructData);
      }
    }
  }

//----------------------------------------------------------------------------
// Das Modul, welches die Fensterklasse fuer das "WORDWIN" verwaltet, sendet
// aus einer Callback-Funktion ein "WM_COMMAND" mit "wParam = WW_CHAR" an das
// Elternfenster des Edit-Elementes (in diesem Fall "DMWSToolbar").
// Die Toolbar ruft die Funktion "ToolEdit::OnChar" auf, und prueft vor
// Weitergabe des Characters unter "wP", auf Zeichen die gesondert behandelt
// werden muessen.
//----------------------------------------------------------------------------
static WORD LastPressedChar;
DLLExport WORD _export WINAPI GetLastPressedChar ()
  {
  return LastPressedChar ;
  }
BOOL IsPrintable (WORD wP)
  {
  return ((wP == '+') || 
          (wP == '-') || 
          (wP == '*') || 
          (wP == '/') || 
          (wP == '%') || 
          (wP == '$') || 
          (wP == '#') || 
          (wP == '|') || 
          (wP == '?') || 
          (wP == '.') || 
          (wP == '!') || 
          (wP == ':') || 
          (wP == '!'));
  }
void SetLastPressedChar (WORD wP)
  {
  if ((IsCharAlphaNumeric(char (wP))) || (wP == '') || (wP == '\b') ||
      (IsPrintable (wP)))
    LastPressedChar = wP ;
  else
    LastPressedChar = 0 ;
  }
BOOL ToolEdit::IsCharCallbackInstalled (WORD wP)
  {
  BOOL found = FALSE ;
  for (LPECL h = ecl; h != NULL ; h = h->Next) {
    if ((h->Type == TYPE_CHARTEST) && (h->vlist.ci.vKey == wP)) {
      found = TRUE ;
      break ;
      }
    }  
  return found;
  }

BOOL ToolEdit::OnChar (WORD wP)
  {
  // Suchen, ob nicht etwas in der ExtraChar - Liste gefunden wird
  BOOL found = FALSE ;
  
  if (!skipNextChar) {
    if (ComboProc != NULL) {
      if (cmbIsEnabled) {
        SetLastPressedChar (wP);
        HotKeyAction (FALSE);          // Combo-Buttons geben die Zeichen nicht weiter!
        SetLastPressedChar (0);
        }
      found = TRUE;
      }
    else if ((UpProc != NULL) && (DownProc != NULL)) {
        if (wP == VK_UP)
          (* CallCommand) (privData, UpProc,Param());
        else if (wP == VK_DOWN)
          (* CallCommand) (privData, DownProc,Param());
          
        found = TRUE;  
        }
    else {
      for (LPECL h = ecl; h != NULL ; h = h->Next) {
        if ((h->Type == TYPE_CHARTEST) && (h->vlist.ci.vKey == wP)) {
          found = TRUE ;
          (* CallCommand) (privData, h->vlist.ci.procOffset,Param());
          break ;
          }
        }
      }  
    }
  else {
    found = TRUE;
    skipNextChar = FALSE;
    }
  return found;
  }

void ToolEdit::OnRButtonDown (HMENU hPopupMenu)
  {
  tool::OnRButtonDown (hPopupMenu);

  if (IsEnabled && (ComboProc == NULL) && (UpProc == NULL) && (DownProc == NULL)) {
    AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);

    //---------------------------------------------------------------------
    // Der Text kann nur ausgeschnitten oder kopiert werden, wenn auch ein
    // Teil des selben selektiert ist!
    //---------------------------------------------------------------------
    UINT Modify = MF_STRING;
    if (!WWIsFieldSelected (hWndEdit))
      Modify |= MF_GRAYED;
      
    AppendMenu (hPopupMenu, Modify, IDM_CUT, "Ausschneiden\tStrg+X");
    AppendMenu (hPopupMenu, Modify, IDM_COPY, "Kopieren\tStrg+C");

    //---------------------------------------------------------------------
    // Nur wenn siche lesbare Daten in der Zwischenablage befinden
    // koennen diese eingefuegt werden!
    //---------------------------------------------------------------------
    Modify = MF_STRING | MF_GRAYED;
    if (IsClipboardFormatAvailable(CF_TEXT) || IsClipboardFormatAvailable(CF_OEMTEXT))
      Modify &= ~MF_GRAYED;

    AppendMenu (hPopupMenu, Modify, IDM_PASTE, "Einf�gen\tStr+V");
    }
  }


BOOL ToolEdit::OnCommand (HWND hWnd, WPARAM wID)
  {
  BOOL res = tool::OnCommand (hWnd, wID);
  if (!res) {
    switch (wID) {
      case IDM_CUT:
        WWClipBoard (hWndEdit, MI_Cut);
        res = TRUE;
        break;

      case IDM_COPY:
        WWClipBoard (hWndEdit, MI_Copy);
        res = TRUE;
        break;

      case IDM_PASTE:
        WWClipBoard (hWndEdit, MI_Insert);
        res = TRUE;
        break;
      }
    }
    
  return res;
  }

void ToolEdit::OnWorkOn ()
  {
  if (lpMenu != NULL)
    (* CallCommand) (lpMenu->MenuPrivData, lpMenu->Proc, lpMenu->MenuProcPar);
  }

BOOL ToolEdit::HasTabStop ()
  {
  return IsEnabled ;
  }

void ToolEdit::Update ()
  {
  Load ();
  InvalidateRect (hWndEdit,NULL,TRUE);
  }

void ToolEdit::HotKeyAction (BOOL dontCheckEnabled)
  {
  if ((IsEnabled) || (dontCheckEnabled)) {
    if (ComboProc != NULL)
      (* CallCommand) (privData, ComboProc,Param());
    else  
      SetFocus (hWndEdit);
    }
  }

void ToolEdit::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  if (state) {
    if ((ComboProc != NULL) || (UpProc != NULL) || (DownProc != NULL)) {
      if ((Parent->Parent->ToolWithFocus != NULL) &&
          (Parent->Parent->ToolWithFocus != this))
        Parent->Parent->ToolWithFocus->SetToolFocus (FALSE);

      Parent->Parent->ToolWithFocus = this;  // jetzt krieg' ich endlich auch den Focus
      }

    if (!select)
      WWEnableSelect (FALSE);

    WWNextExplicit(TRUE);
    SetFocus (hWndEdit);
    WWNextExplicit(FALSE);

    if (!select)
      WWEnableSelect (TRUE);
    }
  else {                           // mu� ihn leider wieder weggeben
    LPSTR txt = GetText ();        // einmal schaugen was da eingegeben wurde
    SetWindowText (hWndEdit, txt); // und in das kleine Fensterlein schreiben
    Invalidate (FALSE);
    }
  }

void ToolEdit::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);

  (* SetConnection) (privData,Param()->_Disabled,StructData);
  (* SetConnection) (privData, Param()->_Id, StructData);

  (* SetConnection)(privData, Param()->_Width, StructData);
  (* SetConnection)(privData, Param()->_AnzLines, StructData);
  (* SetConnection)(privData, Param()->_Format, StructData);
  }

void ToolEdit::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  if ((doClear) || (Parent->Parent == MainScreen)) {
    // Diese Abfrage nach dem ToolWithFocus ist notwendig, da beim Zerstoeren
    // des Edit-Feldes der Dialog wieder den Fokus bekommt. In der SetFocus
    // des Dialoges wird aber dem ToolWithFocus der Focus gegeben. War dieses
    // Tool das Eingabefeld (welches aber gerade zerstoert wurde), so bekommt
    // der Dialog ein KillFocus und das Eingabefeld ein KillFocus usw...
    // => ich gehe davon aus, dass hier der Dialog beendet wird, und somit
    //    kein Tool mehr den Focus benoetigt!
    if (Parent->Parent->ToolWithFocus == this)
      Parent->Parent->ToolWithFocus = NULL;

#ifdef TOOLTIP
    RemoveToolTip (hWndEdit);
#endif

    DestroyWindow (hWndEdit);
    }
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);

  (* ClearConnection) (privData,Param()->_Disabled,StructData);
  (* ClearConnection) (privData, Param()->_Id, StructData);
  (* ClearConnection) (privData, Param()->_Width, StructData);
  (* ClearConnection) (privData, Param()->_AnzLines, StructData);
  (* ClearConnection) (privData, Param()->_Format, StructData);

  for ( ; ecl != NULL ; ) {
    LPECL n = ecl->Next ;
    FreeGlobMem (ecl);
    ecl = n ;
    }
  hWndEdit = 0;
  }

void ToolEdit::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int wwh;
  SetRect (LPRECT (&ToolRect), x0, y0, 
              x0 + ToDevX(tw), 
              y0 + (wwh = int (AnzLines * 
                          WWGetYHeight(int(Format))
                              )
                   )
          );
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + wwh);
  }


void ToolEdit::MoveTool ()
  {
  int y0 = ToDevKoordY(ty,Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT (&ToolRect),0,dy);
                              ToolRect.left,ToolRect.top,
    MoveWindow (hWndEdit,ToolRect.left,ToolRect.top,
                              ToolRect.right - ToolRect.left + 1,
                              ToolRect.bottom - ToolRect.top + 1,TRUE
               );
    Invalidate (FALSE);
#ifdef TOOLTIP
    AddToolTip (hWndEdit);
#endif
    }
  }

LPSTR ToolEdit::GetText ()
  {
  LPSTR h = (LPSTR)(* GetData) (privData,Param()->_Id);
  if (h != NULL)
    return h;
  else
    return "";
  }

int ToolEdit::GetMaxAnzChars ()
  {
  return (* GetVarSize) (privData,Param()->_Id);
  }

void ToolEdit::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  int otx = tx;
  int oty = ty;
  int otw = tw;
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_Width);
  DBWIN_ASSERT (lpw != NULL);
  tw = *lpw;
  DBINT FAR *lpformat = (DBINT FAR *)(* GetData)(privData, Param()->_Format);
  Format = lpformat != NULL ? *lpformat : 0;
  DBINT FAR *lpAnzLines = (DBINT FAR *)(* GetData)(privData, Param()->_AnzLines);
  AnzLines = lpAnzLines != NULL ? *lpAnzLines : 1;
    
  if (hWndEdit == 0) {
    GetRect ();

    CtlId = CtlIdent;

    int xwidth;
    if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD))) {
      double ratio;
      GetResolutionCF (&ratio);
      DBINT FAR *lpxwidth = (DBINT FAR *)(* GetData)(privData, Param()->intermWidth);
      xwidth = lpxwidth != NULL ? int(double (*lpxwidth) * ratio) : -1;
      }
    else
      xwidth = -1;

    hWndEdit = WWCreateWinEx (Parent->Parent->hWndToolbar(),CtlIdent++,int(Format),
                              ToolRect.left,ToolRect.top,
                              ToolRect.right - ToolRect.left + 1,
                              ToolRect.bottom - ToolRect.top + 1,
                              WS_CHILD,
                              FALSE,
                              int (AnzLines),
                              xwidth,
                              GetMaxAnzChars ()
                             );
    }
  else if ((tx != otx) || (ty != oty) || (tw != otw)) {
    if (cmb != NULL) cmb->Invalidate (TRUE);
    Invalidate (TRUE);
    GetRect ();
    Invalidate (TRUE);
    if (cmb != NULL) {
      cmb->GetRect();
      cmb->Invalidate (TRUE);
      }
    MoveWindow (hWndEdit,ToolRect.left,ToolRect.top,ToolRect.right - ToolRect.left + 1,ToolRect.bottom - ToolRect.top + 1,TRUE);
    }
  DBBOOL FAR *IsDisabled = (DBBOOL FAR *) 
          (* GetData) (privData,Param()->_Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));
  
  EnableWindow (hWndEdit,IsEnabled && (cmbIsEnabled || ComboProc == 0L));
  
  LPSTR Text = GetText ();
  SetWindowText (hWndEdit,Text);

#ifdef TOOLTIP
  AddToolTip (hWndEdit);
#endif

  }

DLLExport void _export WINAPI ToolEdit::SetMaxSize (int size)
  {
  SendMessage (hWndEdit,WW_SETTEXTLEN,size,0L);
  }

void ToolEdit::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 3, 3);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }

void ToolEdit::PaintTool (HDC hDC, HDC hmemDC)
  {
  RECT rc;

  if (IsWindow(hWndEdit)) {
    CopyRect (&rc, LPRECT(&ToolRect));
    InflateRect (&rc, 3, 2);

    HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
    HPEN OldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));
    Rectangle (hDC, rc.left, rc.top, 
                    rc.right, rc.bottom+1);
    SelectObject (hDC, OldPen);

    OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
    MoveToEx (hDC, rc.left, rc.bottom-1,NULL);
    LineTo (hDC, rc.left, rc.top);
    LineTo (hDC, rc.right-1, rc.top);
    DeleteObject (SelectObject(hDC, OldPen));

    OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0xC0, 0xC0, 0xC0)));
    Rectangle (hDC, rc.left+1, rc.top+1, rc.right-1, rc.bottom);
    DeleteObject (SelectObject(hDC, OldPen));

    SelectObject (hDC, OldBrush);

    OldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));
    MoveToEx (hDC, rc.left+1, rc.bottom-2,NULL);
    LineTo (hDC, rc.left+1, rc.top+1);
    LineTo (hDC, rc.right-2, rc.top+1);
    SelectObject (hDC, OldPen);
    }
  
  }


//---------------------------------------------------------------------------
// Aendert die Farbe des auszugebenden Textes
//---------------------------------------------------------------------------
void ToolEdit::SetObjectColor (COLORREF color)
  {
  WWSetOutColor (hWndEdit, color);
  }

void ToolEdit::OnChange ()
  {
  WORD Len = WORD (SendMessage (hWndEdit,WM_GETTEXTLENGTH,0,0L));
  LPSTR txt = LPSTR(GetGlobMem (Len+1));
  // GetWindowText (hWndEdit,txt,Len + 1);
  SendMessage (hWndEdit,WMU_GETTEXT,Len+1,LONG(LPSTR(txt)));
  if (lstrlen(txt) > 0)
    (* SetData) (privData, Param()->_Id, txt,
                   lstrlen(txt)+1, StructData
                );
  else
    (* SetData) (privData, Param()->_Id, NULL, 0, StructData);
  FreeGlobMem (txt);
  }

void ToolEdit::OnSetFocus ()
  {
  if (CallOnSetFocus != 0L)
    (* CallCommand) (privData, CallOnSetFocus, Param());
  }

void ToolEdit::OnKillFocus ()
  {
  if (CallOnKillFocus != 0L)
    (* CallCommand) (privData, CallOnKillFocus, Param());
  }

void ToolEdit::OnParentNotify (WPARAM wParam)
  {
  }

void ToolEdit::OnActivate (BOOL ActivateFlag)
  {
  ShowWindow (hWndEdit, (ActivateFlag) ? SW_SHOW : SW_HIDE);
  }

BOOL ToolEdit::HitTest (LPPOINT pt)             
  {
  return (PtInRect(LPRECT(&ToolRect), *pt));
  }

LPSTR ToolEdit::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }

void ToolEdit::SetCaretToEnd ()
  {
  SendMessage (hWndEdit,WWM_CARETTOEND,0,0L);
  }

void ToolEdit::SetComboProc (DWORD Proc,BOOL cIsEnabled,ComboButton FAR *c)
  {
  cmbIsEnabled = cIsEnabled;
  ComboProc = Proc;
  cmb = c;
  }

void ToolEdit::SetUpDownProc (DWORD Up, DWORD Down)
  {
  UpProc = Up;
  DownProc = Down;
  }

DLLExport void _export WINAPI ToolEdit::SetModifyParam (DWORD idModify)
  {
  for (LPECL h = ecl; h != NULL ; h = h->Next) {
    if (h->Type == TYPE_MODIFYFNC) break ;
    }
  if (h == NULL) {
    LPECL n = LPECL (GetGlobMem (sizeof(*n)));
    n->Type = TYPE_MODIFYFNC ;
    n->vlist.csf.SetStrId = idModify;
    n->Next = ecl ;
    ecl = n;
    }
  else
    h->vlist.csf.SetStrId = idModify;
  OnCaretPosChanged();
  }

DLLExport void _export WINAPI ToolEdit::SetColorParam (DWORD idModify)
  {
  for (LPECL h = ecl; h != NULL ; h = h->Next) {
    if (h->Type == TYPE_COLORFNC) break ;
    }
  if (h == NULL) {
    LPECL n = LPECL (GetGlobMem (sizeof(*n)));
    n->Type = TYPE_COLORFNC ;
    n->vlist.csf.SetStrId = idModify;
    n->Next = ecl ;
    ecl = n;
    }
  else
    h->vlist.csf.SetStrId = idModify;
  OnCaretPosChanged();
  }

void ToolBEdit::Load ()
  {
  ToolEdit::Load ();
  WWSetMode (hWndEdit,FM_FIRSTCHARBIG | FM_NOSELECTION);
  }

void ToolPwd::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_Width);
  DBWIN_ASSERT (lpw != NULL);
  tw = *lpw;
  DBINT FAR *lpformat = (DBINT FAR *)(* GetData)(privData, Param()->_Format);
  Format = lpformat != NULL ? *lpformat : 0;
  DBINT FAR *lpAnzLines = (DBINT FAR *)(* GetData)(privData, Param()->_AnzLines);
  AnzLines = lpAnzLines != NULL ? *lpAnzLines : 1;
  if (hWndEdit == 0) {
    GetRect ();

    CtlId = CtlIdent;
    hWndEdit = WWCreateWinEx (Parent->Parent->hWndToolbar(),CtlIdent++,int (Format),
                              ToolRect.left,ToolRect.top,
                              ToolRect.right - ToolRect.left + 1,
                              ToolRect.bottom - ToolRect.top + 1,
                              WS_CHILD | WS_VISIBLE,
                              TRUE,
                              int (AnzLines),
                              -1,
                              GetMaxAnzChars ()
                             );

#ifdef TOOLTIP
    AddToolTip (hWndEdit);
#endif
    }

  DBBOOL FAR *IsDisabled = (DBBOOL FAR *) 
          (* GetData) (privData,Param()->_Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));
  EnableWindow (hWndEdit,IsEnabled);

  LPSTR Text = GetText ();
  SetWindowText (hWndEdit,Text);
  }



//*******************************************************************
//*                                                                 *
//*                  Tool - Date                                    *
//*                                                                 *
//*******************************************************************
static char tmpStr[256];

void ToolDate::Load ()
  {
  ToolEdit::Load ();
//  WWSetMode (hWndEdit,FM_DECIMAL);
  }

LPSTR ToolDate::GetText ()
  {
  packdate FAR *pd = (packdate FAR *) (* GetData) (privData,Param()->_Id);

  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD))) {
    LPSTR szFormat = (LPSTR)(* GetData) (privData,Param()->intermWidth);

    *tmpStr = '\0';
    if (pd != NULL) {
      packdate pdl;
      lmemcpy (&pdl,pd,sizeof(pdl));
      if (szFormat && *szFormat)
        FormatDate (tmpStr, &pdl, szFormat);
      else
        writeDateStr (tmpStr, &pdl);
      }
//    *field = *tmpStr;
    }
  else {
    if (pd != NULL)
      writeShortDateStr (tmpStr,pd);
    else
      *tmpStr = '\0';
    }

  return tmpStr;
  }

#define c_SecsPerDay LONG (86400)

BOOL ToolDate::IsCharCallbackInstalled (WORD wP)
  {
  skipNextChar = FALSE;
  BOOL baseOnNow = TRUE;
  int setDate = 0x8000;
  if (wP == 'G') {
    setDate = -1;
    baseOnNow = TRUE;
    }
  else if (wP == 'H') {
    setDate = 0;
    baseOnNow = TRUE;
    }
  else if (wP == 'M') {
    setDate = 1;
    baseOnNow = TRUE;
    }
  else if ((wP == VK_SUBTRACT) || (wP == VK_DOWN)){
    setDate = -1;
    baseOnNow = FALSE;
    }
  else if ((wP == VK_ADD) || (wP == VK_UP)) {
    setDate = 1;
    baseOnNow = FALSE;
    }
  if (setDate != 0x8000) {
    INTTIME t;
    if (baseOnNow)
      t = Now ();
    else {
      packdate FAR *pdCurrent = (packdate FAR *) (* GetData) (privData,Param()->_Id);
      if (pdCurrent != NULL)
        t = PackTime (pdCurrent);
      else
        return ToolEdit::IsCharCallbackInstalled (wP);
      }
    if (IsEnabled) {
      packdate pd;
      t = t + setDate * c_SecsPerDay;
      UnPackTime (t,&pd);
      (* SetData) (privData,Param()->_Id,&pd,sizeof(pd),StructData);
      SetWindowText (hWndEdit, GetText ());
      }
    skipNextChar = TRUE;
    return TRUE;
    }
  else
    return ToolEdit::IsCharCallbackInstalled (wP);
  }

void ToolDate::OnWorkOn ()
  {
  if (IsEnabled) {
    packdate pd;
    INTTIME t = Now ();
    UnPackTime (t,&pd);
    (* SetData) (privData,Param()->_Id,&pd,sizeof(pd),StructData);

    SetWindowText (hWndEdit, GetText ());
    }
/*
  char txt[256];
  writeShortDateStr (txt,&pd);
  SetWindowText (hWndEdit,txt);
*/
  }

void ToolDate::OnChange ()
  {
  char txt[256];
  // GetWindowText (hWndEdit,txt,sizeof(txt) - 1);
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  txt[sizeof(txt) - 1] = '\0' ;
  packdate pd;
  if (DateFromString (txt,DMY,&pd))
    (* SetData) (privData,Param()->_Id,&pd,sizeof(pd),StructData);
  else
    (* SetData) (privData,Param()->_Id,NULL,0,StructData);
  }

void ToolDate::OnRButtonDown (HMENU hPopupMenu)
  {
  UINT Flags = MF_STRING;

  tool::OnRButtonDown (hPopupMenu);
  if (!IsEnabled)
    Flags |= MF_GRAYED;

  AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);
  AppendMenu (hPopupMenu, Flags, IDM_TODAY, "heutiges Datum\tF2");
//  AppendMenu (hPopupMenu, MF_STRING, IDM_CALENDAR, "Kalender...");
  }

BOOL ToolDate::OnCommand (HWND hWnd, WPARAM wID)
  {
  BOOL res = ToolEdit::OnCommand (hWnd, wID);
  if (!res) {
    if (wID == IDM_TODAY) {
      OnWorkOn ();
      res = TRUE;
      }
    }
    
  return res;
  }

//*******************************************************************
//*                                                                 *
//*                  Tool - Time                                    *
//*                                                                 *
//*******************************************************************
ToolTime::~ToolTime ()
  {
  if (szTimeFormat) FreeGlobMem(szTimeFormat);
  };

//---------------------------------------------------------------------------
// auf das Format wird eine Connection gesetzt
//---------------------------------------------------------------------------
void ToolTime::FixConnection ()
  {
  ToolEdit::FixConnection ();
  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD)))
    (* SetConnection) (privData, Param()->intermWidth, StructData);
  }

void ToolTime::Reset (BOOL doClear)
  {
  ToolEdit::Reset (doClear);
  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD)))
    (* ClearConnection) (privData, Param()->intermWidth, StructData);
  }


void ToolTime::Load ()
  {
  ToolEdit::Load ();
//  WWSetMode (hWndEdit,FM_DECIMAL);
  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD))) {
    LPSTR szFormat = (LPSTR)(* GetData)(privData, Param()->intermWidth);

    if (szFormat && *szFormat) {

      if (szTimeFormat)
        FreeGlobMem (szTimeFormat);
      szTimeFormat = (LPSTR)GetGlobMem (lstrlen(szFormat) + 1);
      lstrcpy (szTimeFormat, szFormat);
      }
    }
  }

LPSTR ToolTime::GetText ()
  {
  packtime FAR *pt = (packtime FAR *) (* GetData) (privData,Param()->_Id);

  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD))) {
    LPSTR szFormat = (LPSTR)(* GetData)(privData, Param()->intermWidth);

    *tmpStr = '\0';

    if (pt != NULL) {
      packtime ptl;
      lmemcpy (&ptl, pt, sizeof(ptl));
      if (szFormat && *szFormat) {

        if (szTimeFormat)
          FreeGlobMem (szTimeFormat);
        szTimeFormat = (LPSTR)GetGlobMem (lstrlen(szFormat) + 1);
        lstrcpy (szTimeFormat, szFormat);

        FormatTime (tmpStr, &ptl, szFormat);
        }
      else
        writeTimeStr (tmpStr, 0, pt);
      }
    }
  else {
    if (pt != NULL)
      writeTimeStr (tmpStr, 0, pt);
    else
      *tmpStr = '\0';
    }
  return tmpStr;
  }

BOOL ToolTime::IsCharCallbackInstalled (WORD wP)
  {
  skipNextChar = FALSE;
  BOOL baseOnNow;
  int setTime = 0x8000;
  if (wP == 'J') {
    setTime = 0;
    baseOnNow = TRUE;
    }
  else if ((wP == VK_SUBTRACT) || (wP == VK_DOWN)) {
    setTime = -1;
    baseOnNow = FALSE;
    }
  else if ((wP == VK_ADD) || (wP == VK_UP)) {
    setTime = 1;
    baseOnNow = FALSE;
    }
  if (setTime != 0x8000) {
    INTTIME t;
    if (baseOnNow)
      t = Now ();
    else {
      packtime FAR *ptCurrent = (packtime FAR *) (* GetData) (privData,Param()->_Id);
      if (ptCurrent != NULL)
        t = PackSeconds (ptCurrent);
      else
        return ToolEdit::IsCharCallbackInstalled (wP);
      }
    if (IsEnabled) {
      int setFactor;
      if (setTime != 0) {
        LPSTR szFormat;
        if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD)))
          szFormat = (LPSTR)(* GetData)(privData, Param()->intermWidth);
        else
          szFormat = NULL;
        if (szFormat && *szFormat) {
          if ((strchr (szFormat, 's') != NULL) || (strchr (szFormat, 'S') != NULL))
            setFactor = 1;    // Sekunden angezeigt
          else if ((strchr (szFormat, 'm') != NULL) || (strchr (szFormat, 'M') != NULL))
            setFactor = 60;   // Minuten angezeigt
          else if ((strchr (szFormat, 'h') != NULL) || (strchr (szFormat, 'H') != NULL))
            setFactor = 3600; // Stunden angezeigt
          else
            setFactor = 1;    // Seltames Format, aber nehmen wir halt Sekunden
          }
        else
          setFactor = 1;
        }
      else
        setFactor = 1;
      packtime pt;
      t = t + setTime * setFactor;
      UnPackSeconds (t,&pt);
      (* SetData) (privData, Param()->_Id, &pt, sizeof(pt), StructData);
      SetWindowText (hWndEdit, GetText ());
      }
    skipNextChar = TRUE;
    return TRUE;
    }
  return ToolEdit::IsCharCallbackInstalled (wP);
  }

void ToolTime::OnWorkOn ()
  {
  if (IsEnabled) {
    packtime pt;
    UnPackSeconds (Now (), &pt);
    (* SetData) (privData, Param()->_Id, &pt, sizeof(pt), StructData);
    SetWindowText (hWndEdit, GetText ());
    }
  }

void ToolTime::OnChange ()
  {
  char txt[256];
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  // GetWindowText (hWndEdit, txt, sizeof(txt) - 1);
  txt[sizeof(txt) - 1] = '\0' ;
  packtime pt;

  //-------------------------------------------------------- 
  // Ist eines der Formatzeichen in Gro�buchstaben, gilt die
  // 24 Stunden Beschraenkung nicht mehr
  //-------------------------------------------------------- 
  BYTE TimeFormat = 0;
  for (LPSTR t = szTimeFormat; t && *t; t++)
    if ((*t == 'M') || (*t == 'H') || (*t == 'S')) {
      TimeFormat = 1;
      break;
      }

  if (readTimeStr (txt, TimeFormat, &pt))
    (* SetData) (privData, Param()->_Id, &pt, sizeof(pt), StructData);
  else
    (* SetData) (privData,Param()->_Id, NULL, 0, StructData);
  }

void ToolTime::OnRButtonDown (HMENU hPopupMenu)
  {
  UINT Flag = MF_STRING;

  tool::OnRButtonDown (hPopupMenu);
  if (!IsEnabled)
    Flag |= MF_GRAYED;

  AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);
  AppendMenu (hPopupMenu, Flag, IDM_TIME, "aktuelle Uhrzeit\tF2");
  }

BOOL ToolTime::OnCommand (HWND hWnd, WPARAM wID)
  {
  BOOL res = ToolEdit::OnCommand (hWnd, wID);
  if (!res) {
    if (wID = IDM_TIME) {
      OnWorkOn ();
      res = TRUE;
      }
    }
    
  return res;
  }

//*******************************************************************
//*                                                                 *
//*                  Tool - Float                                   *
//*                                                                 *
//*******************************************************************
static void prfloat (LPSTR txt, double f,LPSTR format)
  {
  // Ermitteln Anzahl Nachkommastellen
  int AnzNach = 1 ;
  for (LPSTR h = format ; *h ; h++) {
    if ((*h == '.') && (h[1] >= '0') && (h[1] <= '9')) {
      AnzNach = h[1] - '0' ;
      }
    }
  int i = 0 ;
  for (double fact = 1.0 ; i < AnzNach ; fact = fact * 10.0 , i ++) ;
  LONG x ;
  if (f >= 0.0) 
    x = LONG (f * fact + 0.5) ;
  else
    x = LONG (f * fact - 0.5) ;

  if (x < 0) x = -x;
  wsprintf (txt,"%ld",x);
  if (AnzNach > 0) {
    int l = lstrlen (txt);
    char vorkomma[32],nachkomma[32];
    if (l > AnzNach) {
      if (f > -1.0E-10) {
        lmemcpy (vorkomma,txt,l-AnzNach);
        vorkomma[l-AnzNach] = '\0';
        }
      else {
        vorkomma[0] = '-' ;
        lmemcpy (vorkomma+1,txt,l-AnzNach);
        vorkomma[l-AnzNach+1] = '\0';
        }
      lmemcpy (nachkomma,txt+l-AnzNach,AnzNach);
      nachkomma[AnzNach] = '\0';
      }
    else {
      if (f > -1.0E-10) {
        vorkomma[0] = '0' ;
        vorkomma[1] = '\0';
        }
      else {
        vorkomma[0] = '-' ;
        vorkomma[1] = '0' ;
        vorkomma[2] = '\0';
        }
      for (int i = 0 ; i < AnzNach - l ; i++) nachkomma[i] = '0' ;
      lstrcpy (nachkomma + i,txt);
      }
    lstrcpy (txt,vorkomma);
    lstrcat (txt,".") ;
    lstrcat (txt,nachkomma);
    }
  }

//--------------------------------------------
// wandelt <Text> in <float> um
static BOOL scfloat (LPSTR txt, float FAR *f)
  {
  *f = float (0.0);
  BOOL mFound = FALSE ;
  BOOL cFound = FALSE ;
  float ex = float (0.1) ;
  BOOL error = FALSE ;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt >= '0') && (*txt <= '9')) {
      if (cFound)
        *f += float (*txt - '0') * ex , ex *= float(0.1) ;
      else
        *f = *f * float(10.0) + float (*txt - '0') ;
      }
    else if (*txt == '-') {
      if (mFound) 
        error = TRUE ;
      mFound = TRUE ;
      }
    else if ((*txt == '.') || (*txt == ',')) {
      if (cFound) 
        error = TRUE ;
      cFound = TRUE ;
      }
    else
      error = TRUE ;
    }
  if (error)
    *f = float (0.0) ;
  else if (mFound)
    *f *= float(-1.0);

  return !error;
  }

void ToolFloat::Load ()
  {
  ToolEdit::Load ();
  WWSetMode (hWndEdit,FM_DECIMAL);
  }

void ToolFloat::FixConnection ()
  {
  if (fPar()->IsThereFormat())
    (* SetConnection) (privData,fPar()->txtFormat,StructData);
  ToolEdit::FixConnection();
  }

void ToolFloat::Reset (BOOL doClear)
  {
  if (fPar()->IsThereFormat())
    (* ClearConnection) (privData,fPar()->txtFormat,StructData);
  ToolEdit::Reset(doClear);
  }

LPSTR ToolFloat::GetFormat ()
  {
  if (fPar()->IsThereFormat()) {
    return LPSTR ((* GetData) (privData,fPar()->txtFormat));
    }
  else
    return "%.1f" ;
  }

LPSTR ToolFloat::GetText ()
  {
  float FAR* lpfloat = (float FAR *) (* GetData) (privData,Param()->_Id);
  if (lpfloat != NULL)
    prfloat (tmpStr,*lpfloat,GetFormat());
  else
    *tmpStr = '\0';
  return tmpStr;
  }

void ToolFloat::OnChange ()
  {
  char txt[256];
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  // GetWindowText (hWndEdit,txt,sizeof(txt) - 1);
  txt[sizeof(txt) - 1] = '\0' ;
  
  float res;
  BOOL found = ((lstrlen (txt) > 0) && (scfloat(txt,&res)));
  if (found)
    (* SetData) (privData,Param()->_Id,&res,sizeof(res),StructData);
  else  
    (* SetData) (privData,Param()->_Id,NULL,0,StructData);
  }

void ToolShortInt::Load ()
  {
  ToolEdit::Load ();
  WWSetMode (hWndEdit,FM_DECIMAL);
  }

LPSTR ToolShortInt::GetText ()
  {
  DBINT FAR* ptrint = (DBINT FAR *) (* GetData)(privData, Param()->_Id);
  if (ptrint != NULL)
    GetShortStr (tmpStr,*ptrint);
  else
    *tmpStr = '\0';  
  return tmpStr;
  }

LPSTR ToolLongInt::GetText ()
  {
  BOOL doT = FALSE ;
  if (Param()->hd.structSize >= (sizeof(tool_edit) - sizeof(WORD))) {
    LPSTR szFormat = (LPSTR)(* GetData) (privData,Param()->intermWidth);
    doT = (lstrcmp (szFormat,"%l.d") == 0) ;
    }
  long FAR* ptrint = (long FAR *) (* GetData)(privData, Param()->_Id);
  if (ptrint != NULL)
    GetLongStr (tmpStr,*ptrint,doT);
  else
    *tmpStr = '\0';  
  return tmpStr;
  }

BOOL ToolMoney::doMoney()
  {
  if (fPar()->IsThereFormat()) {
    LPSTR format = (LPSTR) (*GetData) (privData,fPar()->txtFormat);
    return ((format == NULL) || (format[1] == 'm'));
    }
  else
    return TRUE ;
  }


void ToolMoney::FixConnection ()
  {
  if (fPar()->IsThereFormat())
    (* SetConnection) (privData,fPar()->txtFormat,StructData);
  ToolShortInt::FixConnection();
  }

void ToolMoney::Reset (BOOL doClear)
  {
  if (fPar()->IsThereFormat())
    (* ClearConnection) (privData,fPar()->txtFormat,StructData);
  ToolShortInt::Reset(doClear);
  }

LPSTR ToolMoney::GetText ()
  {
  long FAR* ptrint = (long FAR *) (* GetData)(privData, Param()->_Id);
  if (ptrint != NULL) {
    if (doMoney()) GetMoneyStr (tmpStr,*ptrint);
    else           GetLongStr (tmpStr,*ptrint,TRUE);
    }
  else
    *tmpStr = '\0';  
  return tmpStr;
  }

void ToolShortInt::OnChange ()
  {
  char txt[256];
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  // GetWindowText (hWndEdit, txt, sizeof(txt) - 1);
  txt[sizeof(txt) - 1] = '\0' ;
  
  int res;
  BOOL found = ((lstrlen (txt) > 0) && (scint(txt, &res)));
  DBINT res1 = (DBINT) res;
  if (found)
    (* SetData) (privData,Param()->_Id, &res1, sizeof(res1), StructData);
  else  
    (* SetData) (privData,Param()->_Id, NULL, 0, StructData);
  }

void ToolLongInt::OnChange ()
  {
  char txt[256];
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  // GetWindowText (hWndEdit, txt, sizeof(txt) - 1);
  txt[sizeof(txt) - 1] = '\0' ;
  
  long res;
  BOOL found = ((lstrlen (txt) > 0) && (sclongint(txt, &res)));
  if (found)
    (* SetData) (privData,Param()->_Id, &res, sizeof(res), StructData);
  else  
    (* SetData) (privData,Param()->_Id, NULL, 0, StructData);
  }

void ToolMoney::OnChange ()
  {
  char txt[256];
  SendMessage (hWndEdit,WMU_GETTEXT,sizeof(txt) - 1,LONG(LPSTR(txt)));
  // GetWindowText (hWndEdit, txt, sizeof(txt) - 1);
  txt[sizeof(txt) - 1] = '\0' ;
  
  long res;
  BOOL found = ((lstrlen (txt) > 0) && (doMoney() ? scmony(txt, &res) : sclongint (txt,&res)));
  if (found)
    (* SetData) (privData,Param()->_Id, &res, sizeof(res), StructData);
  else  
    (* SetData) (privData,Param()->_Id, NULL, 0, StructData);
  }

//*******************************************************************************************
//
//                                      Zoom - Tool
//
//*******************************************************************************************
ZoomTool::ZoomTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize)        // CONSTRUCTOR
  {
  SetRectEmpty (LPRECT(&OldRect));
  SetRectEmpty (LPRECT(&rcArrow));
  Inside = FALSE;
  }


void ZoomTool::On_LButtonDown (LPPOINT pt)
  {
  RECT rc;

  Capturing = TRUE;
  SetCapture (Parent->Parent->hWndToolbar());
  
  if (HitTest(pt)) {
    HDC hDC = GetDC(Parent->Parent->hWndToolbar());

    CopyRect (&rc, LPRECT(&rcArrow));

    if (!IsRectEmpty(LPRECT(&OldRect))) 
      InvertRect (hDC, LPRECT(&OldRect));

    pt->y++;

    rc.bottom = pt->y;
    InvertRect (hDC, &rc);
    CopyRect (LPRECT(&OldRect), LPRECT(&rc));

    ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
    }
  }


void ZoomTool::On_MouseMove (LPPOINT pt)
  {
  RECT  rc;
  
  HDC hDC = GetDC(Parent->Parent->hWndToolbar());
  
  if (HitTest(pt)) {
    Inside = TRUE;
    pt->y++;
    CopyRect (&rc, LPRECT(&OldRect));
    rc.top = OldRect.bottom;
    rc.bottom = pt->y;
    OldRect.bottom = pt->y;
    
    InvertRect (hDC, &rc);
    } 
  else {
    if (Inside)           // war die Maus bei der letzten Bewegung noch innerhalb?
      if (pt->y > (rcArrow.bottom+rcArrow.top)/2) {
        CopyRect (&rc, LPRECT(&OldRect));
        rc.top = OldRect.bottom;
        rc.bottom = rcArrow.bottom;
        InvertRect (hDC, &rc);
        CopyRect (LPRECT(&OldRect), LPRECT(&rcArrow));
        }
      else {
        InvertRect (hDC, LPRECT(&OldRect));
        OldRect.top = rcArrow.top;
        OldRect.bottom = rcArrow.top;
        }
        
    Inside = FALSE;
    }
    
  SetCaretPos (OldRect.left+2, OldRect.bottom-1);

  ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }
  
  
BOOL ZoomTool::On_LButtonUp (LPPOINT pt) 
  {
  ReleaseCapture ();
  Capturing = FALSE;
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  CapDC = 0;

  int y;
  if (HitTest(pt))
    y = pt->y ;
  else {
    if (pt->y > rcArrow.bottom)   y = rcArrow.bottom;
    else if (pt->y < rcArrow.top) y = rcArrow.top;
    else y = pt->y;
    }

  SetCaretPos (OldRect.left+2, OldRect.bottom-1);
  ShowCaret (Parent->Parent->hWndToolbar());

  float val;
  Transform (y,&val);
  (* SetData) (privData, Param()->Id, &val, sizeof(val), StructData);

  return TRUE;
  }

void ZoomTool::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Disabled,StructData);
  (* SetConnection) (privData,Param()->Id,StructData);

  (* SetConnection) (privData,Param()->_w,StructData);
  (* SetConnection) (privData,Param()->_h,StructData);
  }


LPSTR ZoomTool::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }


void ZoomTool::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);

  int x1 = x0 + ToDevX(tw);
  int y1 = y0 + ToDevY(th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);
  CopyRect (LPRECT(&rcArrow), LPRECT(&ToolRect));
  InflateRect (LPRECT(&rcArrow), -2, -2);
  
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));
  }


BOOL ZoomTool::HasTabStop ()
  {
  return IsEnabled ;
  }


BOOL ZoomTool::HitTest (LPPOINT pt)
  {
  return (PtInRect(LPRECT(&rcArrow), *pt));
  }
  

void ZoomTool::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }        


void ZoomTool::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  GetRect ();

//#ifdef TOOLTIP
//  AddToolTip ();
//#endif

  DBBOOL FAR *IsDisabled = (DBBOOL FAR *)(* GetData) (privData,Param()->Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));

  DBINT FAR *lpw = (DBINT FAR *)(* GetData) (privData,Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(* GetData) (privData,Param()->_h);
  DBWIN_ASSERT ((lpw != NULL) && (lph != NULL));

  tw = *lpw;
  th = *lph;

  DBINT FAR *lptype = (DBINT FAR *)(* GetData)(privData, Param()->_Type);
  Type = (lptype != NULL) ? *lptype : 0;

  DBINT FAR *lpsections = (DBINT FAR *)(* GetData)(privData, Param()->_Sections);
  Sections = (lpsections != NULL) ? *lpsections : 1;

  float FAR *lpstartrange = (float FAR *)(* GetData)(privData, Param()->_StartRange);
  DBWIN_ASSERT (lpstartrange != NULL);
  StartRange = *lpstartrange;

  float FAR *lpendrange = (float FAR *)(* GetData)(privData, Param()->_EndRange);
  DBWIN_ASSERT (lpendrange != NULL);
  EndRange = *lpendrange;

  int y ;
  float FAR *val = (float FAR *) (* GetData) (privData,Param()->Id);
  if (val == NULL)
    y = Retransform ((Type == 0) ? 
                       (StartRange + EndRange) / 2.0 :
                       sqrt (StartRange * EndRange)
                    );
  else {
    *val = min(max(*val, StartRange), EndRange);
    y = Retransform (*val);
    }

  CopyRect (LPRECT (&OldRect), LPRECT(&rcArrow));
  OldRect.bottom = y;
  }


void ZoomTool::MoveTool ()
  {
  int y0 = ToDevKoordY(ty,Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    OffsetRect (LPRECT(&rcArrow),0,dy);
    OffsetRect (LPRECT(&OldRect),0,dy);

    Invalidate (FALSE);

#ifdef TOOLTIP
    AddToolTip ();        // neue Position mitteilen
#endif
    }
  }

BOOL ZoomTool::OnChar (WORD wP)
  {
  POINT  pt;

  switch (wP) {
    case VK_UP :
      {
      pt.x = rcArrow.left+1;
      pt.y = OldRect.bottom-5;
      if (pt.y < rcArrow.top)
        pt.y = rcArrow.top;
      On_LButtonDown (&pt);
      On_LButtonUp (&pt);
      SetCaretPos (OldRect.left+2, OldRect.bottom-1);
      }
      break;
    case VK_DOWN :
      {
      pt.x = rcArrow.left+1;
      pt.y = OldRect.bottom+5;
      if (pt.y > rcArrow.bottom)
        pt.y = rcArrow.bottom;
      On_LButtonDown (&pt);
      On_LButtonUp (&pt);
      SetCaretPos (OldRect.left+2, OldRect.bottom-1);
      }
      break ;
    }

  return TRUE;
  }


void ZoomTool::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Disabled,StructData);
  (* ClearConnection) (privData,Param()->Id,StructData);
  (* ClearConnection) (privData,Param()->_w,StructData);
  (* ClearConnection) (privData,Param()->_h,StructData);
  }


int ZoomTool::Retransform (double val)
  {
  if (Type == 0) {
    // Linear
    return int ((val - StartRange) * 
                      double (rcArrow.bottom - rcArrow.top) /
                (EndRange - StartRange)) + rcArrow.top ; 
    }
  else {
    // Logarytmisch
    double b = log (EndRange / StartRange) / 
          double (rcArrow.bottom - rcArrow.top);

    double a = StartRange / exp (b * rcArrow.top);

    return int (log (val / a) / b) ;
    }
  }



void ZoomTool::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  if (state) {
    CreateCaret (Parent->Parent->hWndToolbar(), NULL, OldRect.right-OldRect.left-4, 2);
    SetCaretPos (OldRect.left+2, OldRect.bottom-1);
    ShowCaret (Parent->Parent->hWndToolbar());
    }
  else {
    DestroyCaret ();
    }
      
  }

  

void ZoomTool::Transform (int y,float FAR *val)
  {
  if (Type == 0) {
    // Linear
    *val = float (y - rcArrow.top) * (EndRange - StartRange) /
                float (rcArrow.bottom - rcArrow.top) + StartRange;
    }
  else {
    // Logarytmisch
    double b = log (EndRange / StartRange) / 
          double (rcArrow.bottom - rcArrow.top);

    double a = StartRange / exp (b * rcArrow.top);

    *val = float (a * exp (b * y)) ;
    }
  }
  

void DrawArrow (HDC hDC, int x, int y, int w, int h, COLORREF Color)
  {
  int sw = w/10;
  int aw = w/2 - 2;


  POINT  pt[7];
  HBRUSH OldBrush;
  HPEN   OldPen;

  pt[0].x = x-sw;
  pt[0].y = y;
  pt[1].x = x-aw/2;
  pt[1].y = y+h-aw;
  pt[2].x = x-aw;
  pt[2].y = y+h-aw;
  pt[3].x = x;
  pt[3].y = y+h;
  pt[4].x = x+aw;
  pt[4].y = y+h-aw;
  pt[5].x = x+aw/2;
  pt[5].y = y+h-aw;
  pt[6].x = x+sw;
  pt[6].y = y;

  OldBrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(Color));
  OldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));
  
  Polygon (hDC, pt, 7);
  SelectObject (hDC, OldPen);
  DeleteObject (SelectObject(hDC, OldBrush));
  }


void ZoomTool::PaintTool (HDC hDC, HDC hmemDC)
  {
  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(WHITE_BRUSH));
  Rectangle (hDC, ToolRect.left+1, ToolRect.top+1, ToolRect.right-1, ToolRect.bottom-1);
  HPEN OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, ToolRect.left, ToolRect.bottom,NULL);
  LineTo (hDC, ToolRect.left, ToolRect.top);
  LineTo (hDC, ToolRect.right, ToolRect.top);
  DeleteObject (SelectObject(hDC, OldPen));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, ToolRect.right-1, ToolRect.top,NULL);
  LineTo (hDC, ToolRect.right-1, ToolRect.bottom-1);
  LineTo (hDC, ToolRect.left-1, ToolRect.bottom-1);
  SelectObject (hDC, OldPen);

  DrawArrow (hDC, (rcArrow.left+rcArrow.right)/2+4, rcArrow.top+4, 
                   rcArrow.right-rcArrow.left, rcArrow.bottom-rcArrow.top-4, 
                   RGB(0x80, 0x80, 0x80));
  DrawArrow (hDC, (rcArrow.left+rcArrow.right)/2, rcArrow.top, 
                   rcArrow.right-rcArrow.left, rcArrow.bottom-rcArrow.top-4, 
                   RGB(0xc0, 0xc0, 0xc0));
  SelectObject (hDC, OldBrush);

  InvertRect (hDC, LPRECT(&OldRect));
  }


//////////////////////////////////////////////////////////////////////
//  Gegenseitiger Ausschluss von Radiobuttons
//////////////////////////////////////////////////////////////////////
struct RadioCheck_par {
  WORD fncId;     // just ignore it
  WORD RecSize;
  WORD oldActive;
  DWORD Excl[1];
  };

int AnzStates (RadioCheck_par FAR *par)
  {
  return (par->RecSize + sizeof(WORD) - sizeof(*par)) / sizeof(DWORD) + 1;
  }

DLLExport void _export WINAPI RadioCheck (LPVOID privData,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RadioCheck_par FAR *par = (RadioCheck_par FAR *) param;
    BOOL ButtonState = TRUE ;
    int anzfound = 0;
    int active = 0;

    for (int i = 0 ; i < AnzStates(par) ; i++) {
      DBBOOL FAR *state = 
        (DBBOOL FAR *) (* GetData) (privData, par->Excl[i]);
      if ((state != NULL) && (*state)) {
        active = i ;
        anzfound ++;
        }
      }
    DBWIN_ASSERT(anzfound <= 1);
    if (anzfound == 0)
      (* SetData) (privData, par->Excl[0], &ButtonState,
                     sizeof(DBBOOL), param);
    par->oldActive = active;
    }
  if (mode & EM_UPDATE) {
    RadioCheck_par FAR *par = (RadioCheck_par FAR *) param;
    // Untersuchen, welches Flag neu gesetzt wurde
    BOOL ButtonState = TRUE ;
    int active = -1;
    int anzfound = 0;
    for (int i = 0 ; i < AnzStates(par) ; i++) {
      DBBOOL FAR *state = 
        (DBBOOL FAR *) (* GetData) (privData, par->Excl[i]);
      if ((state != NULL) && (*state)) {
        if (i != int (par->oldActive))
          active = i ;
        anzfound ++;
        }
      }
    if (anzfound == 0) {
      // Er hat alle ausgeschalten
      BOOL ButtonState = TRUE ;
      (* SetData) (privData, par->Excl[0], &ButtonState,
                   sizeof(DBBOOL), param);

      }
    else if (anzfound == 2) {
      // Den oldActive ausschalten
      BOOL ButtonState = FALSE ;
      (* SetData) (privData, par->Excl[par->oldActive], &ButtonState,
                   sizeof(DBBOOL), param);
      par->oldActive = active;
      }
    }
  if (mode & EM_FIXCONNECTION) {
    RadioCheck_par FAR *par = (RadioCheck_par FAR *) param;
    for (int i = 0 ; i < AnzStates(par) ; i++)
      (* SetConnection) (privData,par->Excl[i],param);
    }
  if (mode & EM_RESET) {
    RadioCheck_par FAR *par = (RadioCheck_par FAR *) param;
    for (int i = 0 ; i < AnzStates(par) ; i++)
      (* ClearConnection) (privData,par->Excl[i],param);
    }
  }





// #define PAGE_IN_RECT  5  // maximale Anzahl der angezeigten Seiten im Rechteck
#define PAGE_SPACE    5  // Zwischenraum der Seiten
#define L_BUTTON      0
#define R_BUTTON      1

/*--------------------------------------------------------------------*\
* CONSTRUCTOR PageTool                                                 *
*                                                                      *
\*--------------------------------------------------------------------*/
PageTool::PageTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize)        // CONSTRUCTOR
  {
  SetRectEmpty (LPRECT(&ToolRect));
  SetRectEmpty (LPRECT(&ScrollRect));
  }


/*--------------------------------------------------------------------*\
* member function PageTool::Load                                       *
*                                                                      *
* Zweck: l�dt objektspezifische Daten aus einer Datenbank              *
*                                                                      *
\*--------------------------------------------------------------------*/
void PageTool::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;

  DBBOOL FAR *IsDisabled = (DBBOOL FAR *)(* GetData) (privData,Param()->_Disabled);
  IsEnabled = ((IsDisabled == NULL) || (!*IsDisabled));
  DBINT FAR *lpw = (DBINT FAR *)(* GetData) (privData,Param()->_w);
  DBINT FAR *lph = (DBINT FAR *)(* GetData) (privData,Param()->_h);
  DBWIN_ASSERT ((lpw != NULL) && (lph != NULL));
  tw = *lpw;
  th = *lph;

  WORD FAR *lpAnzPages   = (WORD FAR *) (* GetData) (privData,Param()->_AnzPages);
  WORD FAR *lpActivePage = (WORD FAR *) (* GetData) (privData,Param()->_Id);

  AnzPages = (lpAnzPages != NULL) ? int (*lpAnzPages) : 2;
  ActivePage = (lpAnzPages != NULL) ? int (*lpActivePage) : 1;

  WORD FAR *lpPagesToShow = NULL;
  if (Param()->hd.structSize >= (sizeof(page_tool) - sizeof(WORD)))
    lpPagesToShow =  (WORD FAR *) (* GetData) (privData,Param()->_PagesToShow);
  PagesToShow = (lpPagesToShow != NULL) ? int (*lpPagesToShow) : 5;

  GetRect ();

#ifdef TOOLTIP
  AddToolTip ();
#endif

  if (AnzPages <= PagesToShow) {    // sind mehr Seiten vorhanden als in das Rechteck passen?
    StartPage = 0;                   // nein => beginne mit der ersten Seite ( == 1),
    EndPage = AnzPages-1;            //         und beende mit der letzten Seite ( == AnzPages)
    }
  else {
    EndPage = min (ActivePage + PagesToShow-1,AnzPages-1);
    StartPage = EndPage - (PagesToShow - 1);
    }
  }

void PageTool::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty,Parent->Layer);
  int x1 = x0 + ToDevX(tw);
  int y1 = y0 + ToDevY(th);

  SetRect (LPRECT (&ToolRect), x0, y0, x1, y1);
  CopyRect (LPRECT(&ScrollRect), LPRECT(&ToolRect));

  // die beiden Kn�pfe am Anfang und am Ende des Seiten-Fensters
  SetRect (LPRECT(&LButton), x0, y0, x0+21, y1);
  SetRect (LPRECT(&RButton), x1-21, y0, x1, y1);
  InflateRect (LPRECT(&ScrollRect), -19, 0);      // verkleinere das Seiten-Fenster
    
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty + th));

  // wie breit und wie hoch ist eine gezeichnete Seite?
  PageSize.x = (ScrollRect.right-ScrollRect.left-4-(PagesToShow+1)*PAGE_SPACE) / PagesToShow;
  PageSize.y = (ScrollRect.bottom-ScrollRect.top-4-PAGE_SPACE);
  }

void PageTool::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }        

void PageTool::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->hd._x, StructData);
  (* ClearConnection) (privData, Param()->hd._y, StructData);

  (* ClearConnection) (privData,Param()->_AnzPages,StructData);
  (* ClearConnection) (privData,Param()->_Disabled,StructData);
  (* ClearConnection) (privData,Param()->_Id,StructData);

  (* ClearConnection) (privData, Param()->_w, StructData);
  (* ClearConnection) (privData, Param()->_h, StructData);

#ifdef TOOLTIP
  RemoveToolTip ();
#endif
  }

void PageTool::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    OffsetRect (LPRECT(&ScrollRect),0,dy);
    OffsetRect (LPRECT(&LButton),0,dy);
    OffsetRect (LPRECT(&RButton),0,dy);

    Invalidate (FALSE);
    }
  }

BOOL PageTool::HasTabStop ()
  {
  return IsEnabled ;
  }

BOOL PageTool::HitTest (LPPOINT pt)
  {
  return (PtInRect(LPRECT (&ToolRect), *pt));
  }

LPSTR PageTool::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }

BOOL PageTool::OnChar (WORD wP)
  {
  int OldPage = ActivePage;

  switch (wP) {
    case VK_LEFT :
      if (ActivePage > 0) 
        ActivePage--;
      break;

    case VK_RIGHT :
      if (ActivePage < AnzPages-1) 
        ActivePage++;
      break ;
    }

  if (ActivePage != OldPage) {
    RECT  rc;
    
    CalcPageRect (&rc, OldPage);
    InflateRect (&rc, 3, 3);
    InvalidateRect (Parent->Parent->hWndToolbar(), &rc, FALSE);

    CalcPageRect (&rc, ActivePage);
    InflateRect (&rc, 3, 3);
    InvalidateRect (Parent->Parent->hWndToolbar(), &rc, FALSE);

    (* SetData) (privData,Param()->_Id,&ActivePage,sizeof(DBINT),StructData);
    }

  return TRUE;
  }



inline int MIN (int a, int b)
  {
  if (a < b)
    return a;
  return b;  
  }


/*--------------------------------------------------------------------*\
* function DrawButton                                                  *
*                                                                      *
* Zweck: zeichnet einen Button zum weiterw�hlen der Seiten.            *
* Parameter: hDC ..... Device Kontext                                  *
*            rc  ..... Abmessungen des Buttons                         *
*            State ... Zustand des Buttons (pressed, enabled, disabled)*
*            Pos ..... linker oder rechter Button                      *
\*--------------------------------------------------------------------*/
void DrawButton (HWND hWnd, LPRECT rc, int State, int Pos)
  {
  HDC hDC = GetDC (hWnd);

  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(LTGRAY_BRUSH));
  HPEN DarkGrayPen = CreatePen (PS_SOLID, 0, RGB(0x80, 0x80, 0x80));
  HPEN WhitePen = (HPEN)GetStockObject(WHITE_PEN); 
  HPEN OldPen;

  int w = (rc->right-rc->left) / 3;
  w = MIN (w, (rc->bottom-rc->top) / 3);   // berechne die Abmessungen des Pfeiles im Button
  POINT pt[3];                             // Pfeil-Koordinaten
  pt[0].x = rc->left+w;
  pt[0].y = (rc->top+rc->bottom)/2;
  pt[1].x = pt[0].x+w;
  pt[1].y = pt[0].y-w;
  pt[2].x = pt[1].x;
  pt[2].y = pt[0].y+w;

  if (Pos) {                               // rechter Button ist spiegelverkehrt
    int t = pt[0].x;
    pt[0].x = pt[1].x;
    pt[1].x = t;
    pt[2].x = pt[1].x;
    }
                                           
  if (State == 1)                          // Button gedr�ckt?
    for (int i = 0; i < 3; i++) {          // ja => Pfeil ist etwas versetzt
      pt[i].x++;
      pt[i].y++;
      }
    
  RoundRect (hDC, rc->left, rc->top, rc->right, rc->bottom, 2, 2);  // Rahmen zeichnen
  SelectObject (hDC, OldBrush);
  switch (State) {
    case 0 : 
    case 2 :
      OldPen = (HPEN)SelectObject (hDC, WhitePen);
      MoveToEx (hDC, rc->left+1, rc->bottom-2,NULL);
      LineTo (hDC, rc->left+1, rc->top+1);
      LineTo (hDC, rc->right-2, rc->top+1);
      SelectObject (hDC, DarkGrayPen);
      MoveToEx (hDC, rc->right-2, rc->top+2,NULL);
      LineTo (hDC, rc->right-2, rc->bottom-2);
      LineTo (hDC, rc->left+2, rc->bottom-2);
      MoveToEx (hDC, rc->right-3, rc->top+3,NULL);
      LineTo (hDC, rc->right-3, rc->bottom-3);
      LineTo (hDC, rc->left+3, rc->bottom-3);
      SelectObject (hDC, OldPen);

      break;
    case 1 :
      OldPen = (HPEN)SelectObject (hDC, DarkGrayPen);
      MoveToEx (hDC, rc->left+1, rc->bottom-1,NULL);
      LineTo (hDC, rc->left+1, rc->top+1);
      LineTo (hDC, rc->right-1, rc->top+1);
      SelectObject (hDC, OldPen);

      break;
    }

  if ((State == 0) || (State == 1)) 
    OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(BLACK_BRUSH));
  else 
    OldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(RGB(0x80, 0x80, 0x80)));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject(NULL_PEN));
  Polygon (hDC, pt, 3);
  SelectObject (hDC, OldPen);
  DeleteObject (SelectObject (hDC, OldBrush));

  if (State == 2) {                        // Knopf disabled zeichnen
    OldPen = (HPEN)SelectObject (hDC, WhitePen);
    MoveToEx (hDC, pt[0].x, pt[0].y,NULL);
    LineTo (hDC, pt[2].x, pt[2].y);
    SelectObject (hDC, OldPen);
    }
    
  DeleteObject (DarkGrayPen);

  ReleaseDC (hWnd, hDC);
  }

  
  
/*--------------------------------------------------------------------*\
* member function PageTool::On_LButtonDown                               *
*                                                                      *
* Zweck: Reagiert auf das Dr�cken der linken Maustaste.                *
* Parameter: pt ... Position der Maus                                  *
\*--------------------------------------------------------------------*/
void PageTool::On_LButtonDown (LPPOINT pt)
  {
  RECT rc;

  if (AnzPages <= 1)
    return;
    
  Capturing = TRUE;
  SetCapture (Parent->Parent->hWndToolbar());
//  CapDC = GetDC(Parent->Parent->hWndToolbar());
  if (HitTest(pt)) {
    for (int i = 0; i < (EndPage-StartPage+1); i++) {
      // berechne die Rechtecke f�r die angezeigten Seiten
      CalcPageRect (&rc, i);
      if (PtInRect (LPRECT(&rc), *pt)) {     // wurde eine Seite angew�hlt?

        RECT rctmp;                          // Koordinaten der noch aktiven Seite ermitteln
        CalcPageRect (&rctmp, ActivePage-StartPage);

        if ((ActivePage >= StartPage) && (ActivePage <= EndPage))   // aktive Seite noch sichtbar?
          PaintPage (int(ActivePage), &rctmp, FALSE);        // ja => jetzt nicht mehr aktiv 
        ActivePage = StartPage+i;                                   // neue aktive Seite
        PaintPage (int(ActivePage), &rc, TRUE);              // hervorgehoben zeichnen
        // (* SetData) (privData,Param()->_Id,&ActivePage,sizeof(DBINT),StructData);
        break;
        }   //  if (PtInRect)
      }   //  for
    }   //  if (HitTest)
  
    LPressed = FALSE;
    RPressed = FALSE;
    if (PtInRect(LPRECT(&LButton), *pt)) {                   // war die Maus im linken Knopf?
      if (StartPage > 0) {                                   // ja => gibt es noch eine Seite?

        DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 1, L_BUTTON);   // ja => Knopf gedr�ckt zeichnen
        StartPage--;                                         // die sichtbaren Seiten verschieben
        EndPage--;
        PaintTool (0, 0);                                // das ganze neu zeichnen
        if (StartPage > 0) {                                 // gibt es noch ein Seite?
          DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 1, L_BUTTON); // ja => Knopf normal zeichnen
          LPressed = TRUE;
          }
        else 
          DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 2, L_BUTTON); // nein => Knopf wird disabled
        }
      
      }
    else  
    if (PtInRect(LPRECT(&RButton), *pt)) {                   // die ganze Abfrage f�r den rechten Knopf w.o.
      if (EndPage < AnzPages-1) {
        DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 1, R_BUTTON);
        StartPage++;
        EndPage++;
        PaintTool (0, 0);
        if (EndPage < AnzPages-1) {
          RPressed = TRUE;
          DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 1, R_BUTTON);
          }
        else  
          DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 2, R_BUTTON);
        }
      
      }
  }
  
  
/*--------------------------------------------------------------------*\
* member function PageTool::On_LButtonUp                                 *
*                                                                      *
* Zweck: Reagiert auf das Bewegen der Maus bei gedr�ckter Maustaste.   *
* Parameter: pt ... Position der Maus                                  *
\*--------------------------------------------------------------------*/
void PageTool::On_MouseMove (LPPOINT pt)
  {
  if (LPressed) {
    if (PtInRect(LPRECT(&LButton), *pt))            // im linken Button
      DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 1, L_BUTTON);
    else  
      DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 0, L_BUTTON);
    }
  else if (RPressed)  
    if (PtInRect(LPRECT(&RButton), *pt))            // im rechten Button
      DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 1, R_BUTTON);
    else  
      DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 0, R_BUTTON);
  }
  
  
/*--------------------------------------------------------------------*\
* member function PageTool::On_LButtonUp                                 *
*                                                                      *
* Zweck: Reagiert auf das Loslassen der linken Maustaste.              *
* Parameter: pt ... Position der Maus                                  *
* R�ckgabewert: TRUE wenn alles in Ordnung; FALSE sonst                *
\*--------------------------------------------------------------------*/
BOOL PageTool::On_LButtonUp (LPPOINT pt) 
  {
  if (AnzPages <= 1)
    return TRUE;

  if (LPressed) {
    if (StartPage > 0) {
      DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 0, L_BUTTON);
      }
    }
  else  
    if (RPressed)
      if (EndPage < AnzPages-1) 
        DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 0, R_BUTTON);

  (* SetData) (privData,Param()->_Id,&ActivePage,sizeof(DBINT),StructData);

  LPressed = FALSE;
  RPressed = FALSE;

  ReleaseCapture ();
  Capturing = FALSE;
//  if (CapDC > 0)
//    ReleaseDC (Parent->Parent->hWndToolbar(), CapDC);
//  CapDC = 0;

  return TRUE;
  }

void PageTool::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);

  (* SetConnection) (privData,Param()->_AnzPages,StructData);
  (* SetConnection) (privData,Param()->_Disabled,StructData);
  (* SetConnection) (privData,Param()->_Id,StructData);

  (* SetConnection) (privData, Param()->_w, StructData);
  (* SetConnection) (privData, Param()->_h, StructData);
  }

void PageTool::PaintPage (int Num, LPRECT lprcPage, BOOL Selected)
  {

   WORD        wFlap;
   HPEN        hOldPen;
   HBRUSH      hOldBrush;
   RECT        rcNumber;
   DWORD       dwOldBkColor;
   DWORD       dwOldTextColor;
   int         wOldBkMode;
   POINT       ptPage[7];
   char        szNumber[16];

   HDC hDC = GetDC (Parent->Parent->hWndToolbar());

   // Flappe der Seite rechts oben
   wFlap = (lprcPage->right-lprcPage->left)/3;
      
   Num++;
   wsprintf (szNumber, "%d", Num);

   /* define number rectangle */
   CopyRect (&rcNumber,lprcPage);

   HFONT OldFont = (HFONT)SelectObject (hDC, HelvFont);
   /* draw page (based on selection state */
   if (Selected ) {
      
     /* define page polygon */
     ptPage[0].x = lprcPage->left;
     ptPage[0].y = lprcPage->top;
     ptPage[1].x = lprcPage->right - wFlap - 1;
     ptPage[1].y = lprcPage->top;
     ptPage[2].x = lprcPage->right - 1;
     ptPage[2].y = lprcPage->top + wFlap;
     ptPage[3].x = lprcPage->right - 1;
     ptPage[3].y = lprcPage->bottom - 1;
     ptPage[4].x = lprcPage->left;
     ptPage[4].y = lprcPage->bottom - 1;
     ptPage[5].x = lprcPage->left;
     ptPage[5].y = lprcPage->top;

     /* draw page outline */
     hOldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME)));
     Polygon( hDC, ptPage, 6 );
     DeleteObject( SelectObject(hDC,hOldBrush) );

     /* draw flap with background pen color */
     hOldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID,1,GetSysColor(COLOR_WINDOW)));
     MoveToEx( hDC, lprcPage->right - wFlap - 1, lprcPage->top + 1, NULL );
     LineTo( hDC, lprcPage->right - wFlap - 1, lprcPage->top + wFlap );
     LineTo( hDC, lprcPage->right - 1, lprcPage->top + wFlap );
     DeleteObject( SelectObject(hDC,hOldPen) );

     /* draw inverted page number */
     dwOldBkColor = SetBkColor( hDC, GetSysColor(COLOR_WINDOWFRAME));
     dwOldTextColor = SetTextColor (hDC, GetSysColor(COLOR_WINDOW));
     wOldBkMode = SetBkMode (hDC, TRANSPARENT);
     SetTextAlign (hDC,TA_TOP | TA_LEFT);
                
     DrawText(hDC, szNumber, -1, &rcNumber, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP);
     SetBkMode (hDC, wOldBkMode);
     SetTextColor( hDC, dwOldTextColor );
     SetBkColor( hDC, dwOldBkColor );
    
   } 
   else {

     /* define page polygon */
     ptPage[0].x = lprcPage->left;
     ptPage[0].y = lprcPage->top;
     ptPage[1].x = lprcPage->right - wFlap - 1;
     ptPage[1].y = lprcPage->top;
     ptPage[2].x = lprcPage->right - wFlap - 1;
     ptPage[2].y = lprcPage->top + wFlap;
     ptPage[3].x = lprcPage->right - 1;
     ptPage[3].y = lprcPage->top + wFlap;
     ptPage[4].x = lprcPage->right - 1;
     ptPage[4].y = lprcPage->bottom - 1;
     ptPage[5].x = lprcPage->left;
     ptPage[5].y = lprcPage->bottom - 1;
     ptPage[6].x = lprcPage->left;
     ptPage[6].y = lprcPage->top;

     /* draw page outline */
     hOldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(GetSysColor(COLOR_WINDOW)));
     Polygon( hDC, ptPage, 7 );
     DeleteObject( SelectObject(hDC,hOldBrush) );

     /* draw page flap */
     hOldBrush = (HBRUSH)SelectObject (hDC, CreateSolidBrush(GetSysColor(COLOR_WINDOW)));
     Polygon( hDC, &ptPage[1], 3 );
     DeleteObject( SelectObject(hDC,hOldBrush) );

     // draw page number 
     dwOldBkColor = SetBkColor( hDC, GetSysColor(COLOR_WINDOW) );
     dwOldTextColor = SetTextColor( hDC, GetSysColor(COLOR_BTNTEXT) );
     wOldBkMode = SetBkMode (hDC, TRANSPARENT);
     SetTextAlign (hDC,TA_TOP | TA_LEFT);
     DrawText(hDC, szNumber, -1, &rcNumber, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP);
     SetBkMode (hDC, wOldBkMode);
     SetTextColor( hDC, dwOldTextColor );
     SetBkColor( hDC, dwOldBkColor );
/*
     // draw white border 
     hOldPen = SelectObject( hDC, CreatePen(PS_SOLID,1,GetSysColor(COLOR_WINDOW)) );
     MoveToEx( hDC, ptPage[5].x + 1, ptPage[5].y - 1 );
     LineTo( hDC, ptPage[5].x + 1, ptPage[6].y + 1 );
     LineTo( hDC, ptPage[1].x, ptPage[1].y + 1 );
     DeleteObject( SelectObject(hDC,hOldPen) );

     // draw shadow 
     hOldPen = SelectObject( hDC, CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW)) );
     MoveToEx( hDC, ptPage[5].x + 1, ptPage[5].y - 1 );
     LineTo( hDC, ptPage[4].x - 1, ptPage[4].y - 1 );
     LineTo( hDC, ptPage[3].x - 1, ptPage[3].y );
     MoveToEx( hDC, ptPage[5].x + 2, ptPage[5].y - 2 );
     LineTo( hDC, ptPage[4].x - 2, ptPage[4].y - 2 );
     LineTo( hDC, ptPage[3].x - 2, ptPage[3].y );
     DeleteObject( SelectObject(hDC,hOldPen) );
*/
   }
  
  SelectObject (hDC, OldFont);
   
  ReleaseDC (Parent->Parent->hWndToolbar(), hDC); 
  }


void PageTool::PaintTool (HDC hDC, HDC hMemDC)
  {
  BOOL bGetDC = FALSE;
  
  if (hDC == 0) {
    bGetDC = TRUE;
    hDC = GetDC (Parent->Parent->hWndToolbar());
    }

  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(WHITE_BRUSH));
  Rectangle (hDC, ScrollRect.left+1, ScrollRect.top+1, ScrollRect.right-1, ScrollRect.bottom-1);
  HPEN OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  MoveToEx (hDC, ScrollRect.left, ScrollRect.bottom-1, NULL);
  LineTo (hDC, ScrollRect.left, ScrollRect.top);
  LineTo (hDC, ScrollRect.right, ScrollRect.top);
  DeleteObject (SelectObject(hDC, OldPen));

  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, ScrollRect.right-1, ScrollRect.top, NULL);
  LineTo (hDC, ScrollRect.right-1, ScrollRect.bottom-1);
  LineTo (hDC, ScrollRect.left-1, ScrollRect.bottom-1);
  SelectObject (hDC, OldPen);

  if (StartPage == 0)
    DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 2, L_BUTTON);
  else
    DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&LButton), 0, L_BUTTON);
      
  if (EndPage == AnzPages-1)
    DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 2, R_BUTTON);
  else  
    DrawButton (Parent->Parent->hWndToolbar(), LPRECT(&RButton), 0, R_BUTTON);

  // zeichne alle sichtbaren Kn�pfe
  for (int i = 0; i < (EndPage-StartPage+1); i++) {
    RECT rc;
    CalcPageRect (&rc, i);
    if (StartPage+i == ActivePage) {
      PaintPage (StartPage+i, &rc, TRUE);
      if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
        InflateRect (&rc, 2, 2);
        PaintFocusRect (hDC, rc);
        }
      }
    else  
      PaintPage (StartPage+i, &rc, FALSE);
    }

  if (bGetDC)
    ReleaseDC (Parent->Parent->hWndToolbar(), hDC);
  }


void PageTool::CalcPageRect (RECT FAR* rc, int i)
  {
  int x = ScrollRect.left+PAGE_SPACE*(i+1)+PageSize.x*i+2;
  int y = ScrollRect.top+PAGE_SPACE/2+2;
  SetRect (rc, x, y, x+PageSize.x, y+PageSize.y);
  }

void PageTool::SetToolFocus (BOOL state, BOOL select,int mode)
  {
  RECT  rc;

  SetRectEmpty (&rc);
  for (int i = 0; i < (EndPage-StartPage+1); i++) 
    // berechne die Rechtecke f�r die angezeigten Seiten
    if (StartPage+i == ActivePage) {
      CalcPageRect (&rc, i);
      }

  if (!IsRectEmpty(&rc)) {
    InflateRect (&rc, 3, 3);
    InvalidateRect (Parent->Parent->hWndToolbar(), &rc, !state);
    }

  }



//////////////////////////////////////////////////////////////////
//    Tool_Static
//////////////////////////////////////////////////////////////////
StaticTool::StaticTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize)        // CONSTRUCTOR
  {
  IsEnabled = TRUE ;
  Format = -1;
  }

inline int YtoLOG (HDC hDC,int y)
  {
  POINT pt;
  pt.x = 0 ;
  pt.y = y ;
  DPtoLP (hDC,&pt,1);
  return pt.y;
  }

void StaticTool::GetRect ()
  {
  RECT r;
  field->GetFieldRect (&r,0);
  RectToDev (&r);
  CopyRect (LPRECT (&ToolRect), &r);
  if (tw > 0)
    ToolRect.right = ToolRect.left+ToDevKoordX(tw);
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + 
                                  (r.bottom - r.top + 1)
                             );
  }


BOOL StaticTool::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL)
    return (PtInRect(LPRECT(&ToolRect), *pt));
  else
    return FALSE ;
  }

void StaticTool::GetTextPos (HDC hDC,LPPOINT p)
  {
  p->x = ToDevKoordX (tx) ;
  p->y = ToDevKoordY (ty, Parent->Layer) ;
  DPtoLP (hDC,p,1);
  }


int StaticTool::GetTextWidth (HDC hDC)
  {
  return XtoLOG (hDC, ToDevKoordX(tw));
  }


void StaticTool::FixConnection ()
  {
  (* SetConnection) (privData, Param()->hd._x, StructData);
  (* SetConnection) (privData, Param()->hd._y, StructData);
  (* SetConnection) (privData, Param()->_w,StructData);
  (* SetConnection) (privData,TextRef(),StructData);
  (* SetConnection) (privData,FormatRef(),StructData);
  }



void StaticTool::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }

void StaticTool::Load ()
  {
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->_w);
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBINT FAR *lpFormat = (DBINT FAR *)(*GetData)(privData, FormatRef());

  int AnzLines = -1;

  if ((Param()->hd.structSize + sizeof(WORD)) >= sizeof(tool_static)) {
    DBINT FAR *lpAnzLines = (DBINT FAR *)(*GetData)(privData, Param()->AnzLines);
    if ((lpAnzLines != NULL) && (*lpAnzLines))
      AnzLines = *lpAnzLines;
    }

  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL) && (lpFormat != NULL) && (lpw != NULL));
  int otx = tx;
  int oty = ty;
  tx = *lpx;
  ty = *lpy;
  tw = *lpw;

  // hat sich das Format geaendert, und ein cField existiert,
  // dann muss das cField neu erzeugt werden.
  if ((Format != *lpFormat) && (field != NULL)) {
    delete field;
    field = NULL;
    }

  Format = *lpFormat;
  if (field == NULL) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    SetTwips (hDC);
    POINT pt;
    GetTextPos (hDC,&pt);
    int w = GetTextWidth (hDC);
    ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
    field = new cField (TRANSPARENT,Format,pt.x,pt.y,w,AnzLines,FALSE);
    int dummy;
    field->InstallCallBack (GetFieldCallback(),&dummy,sizeof(dummy));
    field->SetWindow (Parent->Parent->hWndToolbar());
    field->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    field->SetWOrg (0,0);
    }
  else if ((tx != otx) || (ty != oty)) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    SetTwips (hDC);
    POINT pt;
    GetTextPos (hDC,&pt);
    int w = GetTextWidth (hDC);
    *field = pt;
    }

  LPSTR txt = LPSTR ((* GetData) (privData,TextRef()));
  if (txt != NULL)
    *field = txt;
  else
    *field = "";

  GetRect ();
  }

//---------------------------------------------------------------------------
// Aendert die Farbe des auszugebenden Textes
//---------------------------------------------------------------------------
void StaticTool::SetObjectColor (COLORREF color)
  {
  field->SetOutColor (color);
  }

void StaticTool::MoveTool ()
  {
  int y0 = ToDevKoordY(ty, Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    POINT pt ;
    OffsetRect (LPRECT(&ToolRect),0,dy);

    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    SetTwips (hDC);
    GetTextPos (hDC,&pt);
    ReleaseDC (Parent->Parent->hWndToolbar(),hDC);

    *field = pt;
    Invalidate (FALSE);
    }
  }

void StaticTool::PaintTool (HDC hDC, HDC hmemDC)
  {
  SetTwips (hDC);
  field->Paint (hDC,0,FALSE);
  SetMMText (hDC);
  }


void StaticTool::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData, Param()->hd._x,StructData);
  (* ClearConnection) (privData, Param()->hd._y,StructData);
  (* ClearConnection) (privData, Param()->_w,StructData);
  (* ClearConnection) (privData,TextRef(),StructData);
  (* ClearConnection) (privData,FormatRef(),StructData);
  if (field != NULL)
    delete field ;
  field = NULL;
  }


void StaticTool::RectToDev (LPRECT r)
  {
  HDC hDC = GetDC (Parent->Parent->hWndToolbar());
  SetTwips (hDC);
  POINT pt[2];
  pt[0].x = r->left  , pt[0].y = r->top ;
  pt[1].x = r->right , pt[1].y = r->bottom ;
  LPtoDP (hDC,pt,2);
  ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
  r->left  = pt[0].x , r->top    = pt[0].y ;
  r->right = pt[1].x , r->bottom = pt[1].y ;
  }



void StaticTool::SetMMText (HDC hDC)
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

void StaticTool::NewWindow (HWND hWnd)
  {
  if (field != NULL)
    field->Wnd = hWnd ;
  }

void StaticTool::SetTwips (HDC hDC)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,1440,1440,NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels,NULL);
  SetViewportOrgEx (hDC,0,0,NULL);
  SetWindowOrgEx (hDC,0,0,NULL);
  }




/*****************************************************************************\
*                                                                             *
*        STATIC BITMAP                                                        *
*                                                                             *
\*****************************************************************************/
void StaticBitmap::FixConnection ()
  {
  }

BOOL StaticBitmap::HitTest (LPPOINT pt)
  {
  if (EditCallBack != NULL)
    return (PtInRect(LPRECT(&ToolRect), *pt));
  else
    return FALSE ;
  }

void StaticBitmap::GetRect ()
  {
  // Berechne die Ausdehnung des Buttons
  int AnzRows, AnzCols;
  HBITMAP hBmp = GetBitmap (
                      BitRef()[0].bitId, 
                      AnzRows, AnzCols) ;
  BITMAP bi;

  int bmWidth,bmHeight;
  if (hBmp) {
    GetObject (hBmp, sizeof(bi), &bi);
    bmWidth  = bi.bmWidth  / AnzCols ;
    bmHeight = bi.bmHeight / AnzRows ;
    }
  else
    bmWidth = bmHeight = 0;
  int x0 = ToDevKoordX (tx);
  int y0 = ToDevKoordY (ty, Parent->Layer);
  SetRect (LPRECT(&ToolRect), x0, y0, x0+bmWidth, y0+bmHeight);
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + bmHeight);
  }

void StaticBitmap::Invalidate (BOOL doErase)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&ToolRect), doErase);
  }

void StaticBitmap::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  GetRect();

  AnzButtons = 1;

  DBINT FAR *lpcol = (DBINT FAR *)(* GetData)(privData, BitRef()->_Col);
  DBINT FAR *lprow = (DBINT FAR *)(* GetData)(privData, BitRef()->_Row);
  BmpRef.Col = (lpcol != NULL) ? *lpcol : 0;
  BmpRef.Row = (lprow != NULL) ? *lprow : 0;
  }

void StaticBitmap::MoveTool ()
  {
  int y0 = Gety0 ();
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT(&ToolRect),0,dy);
    Invalidate (FALSE);
    }
  }

void StaticBitmap::PaintTool (HDC hDC, HDC hMemDC)
  {
  int     AnzCols, AnzRows;

  HBITMAP hBmp = GetBitmap (
                      BitRef()->bitId, 
                      AnzRows, AnzCols
                           );
  if ((hBmp) && (BmpRef.Col < AnzCols) &&
                (BmpRef.Row < AnzRows)) {

    BITMAP bi;
    GetObject (hBmp,sizeof(bi),&bi);
    int bmWidth  = bi.bmWidth  / AnzCols ;
    int bmHeight = bi.bmHeight / AnzRows ;

    hBmp = (HBITMAP)SelectObject (hMemDC, hBmp);

    BitBlt (hDC, ToolRect.left, ToolRect.top,
                  bmWidth, bmHeight,
            hMemDC,
                  int (BmpRef.Col) * bmWidth,
                  int (BmpRef.Row) * bmHeight,
                  SRCCOPY
          );

    SelectObject (hMemDC, hBmp);
    }
  }



void StaticBitmap::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  }



void TransparentBitmap::Load ()
  {
  int AnzCols, AnzRows;
  HPALETTE hPal;
  HBITMAP hBmp = GetBitmap (BitRef()->bitId, AnzRows, AnzCols, hPal);

  DWORD FAR* lpColor = (DWORD FAR *)(* GetData)(privData, Param()->_TransparentColor);
  TransparentColor = (lpColor != NULL) ? *lpColor : 0;
  
  StaticBitmap::Load ();
  }

void TransparentBitmap::PaintTool (HDC hDC, HDC hMemDC)
  {
  int     AnzCols, AnzRows;
  HPALETTE hPal;
  

  HBITMAP hBmp = GetBitmap (
                      BitRef()->bitId, 
                      AnzRows, AnzCols, hPal
                           );

  if ((hBmp) && ((BmpRef.Col < AnzCols) &&
                 (BmpRef.Row < AnzRows))) {

    BITMAP bi;
    GetObject (hBmp,sizeof(bi),&bi);
    int bmWidth  = bi.bmWidth  / AnzCols ;
    int bmHeight = bi.bmHeight / AnzRows ;

    HPALETTE hOldPal1;
    HPALETTE hOldPal2;
    if (hPal != 0) {
      hOldPal1 = SelectPalette (hDC, hPal, FALSE);
      hOldPal2 = SelectPalette (hMemDC, hPal, FALSE);
      
      RealizePalette (hDC);
      }

    DrawTransparentBitmap(hDC, hBmp, ToolRect.left, ToolRect.top, 
                          int(BmpRef.Col)*bmWidth,             // horizontaler Offset im Bitmap
                          int(BmpRef.Row)*bmHeight,            // vertikaler Offset im Bitmap
                          bmWidth, bmHeight, TransparentColor);

    if (hPal != 0) {
      SelectPalette (hDC, hOldPal1, FALSE);
      SelectPalette (hMemDC, hOldPal2, FALSE);
      }
    }
  }



void AnimationBitmap::PaintTool (HDC hDC, HDC hMemDC)
  {
  if (!StopAnimation) {
    int     AnzCols, AnzRows;
    HPALETTE hPal;
  
    HBITMAP hBmp = GetBitmap (
                        BitRef()->bitId, 
                        AnzRows, AnzCols, hPal
                             );
    if ((hBmp) && (BmpRef.Col < AnzCols) &&
                  (BmpRef.Row < AnzRows)) {
  
      BITMAP bi;
      GetObject (hBmp,sizeof(bi),&bi);
      int bmWidth  = bi.bmWidth  / AnzCols ;
      int bmHeight = bi.bmHeight / AnzRows ;

#ifdef UEBERLEGT
      hBmp = SelectObject (hMemDC, hBmp);
      BitBlt (hDC, ToolRect.left, ToolRect.top,
                    bmWidth, bmHeight,
                    hMemDC,
                    ActBitmap * bmWidth,
                    0,
                    SRCCOPY
            );
      SelectObject (hMemDC, hBmp);
#endif

      HPALETTE hOldPal1;
      HPALETTE hOldPal2;
      if (hPal != 0) {
        hOldPal1 = SelectPalette (hDC, hPal, FALSE);
        hOldPal2 = SelectPalette (hMemDC, hPal, FALSE);
      
        RealizePalette (hDC);
        }

      DrawTransparentBitmap(hDC, hBmp, ToolRect.left, ToolRect.top, 
                            ActBitmap * bmWidth,
                            0,
                            bmWidth, bmHeight, 0 /* TransparentColor */ );

      if (hPal != 0) {
        SelectPalette (hDC, hOldPal1, FALSE);
        SelectPalette (hMemDC, hOldPal2, FALSE);
        }
      }
    }
  }

void AnimationBitmap::OnTimer ()
  {
  if (!StopAnimation) {
    int     AnzCols,AnzRows;
    HBITMAP hBmp = GetBitmap (
                        BitRef()->bitId, 
                        AnzRows, AnzCols
                             );
    ActBitmap++ ;
    if (ActBitmap >= AnzCols) {
      ActLoopCount += 1 ;
      ActBitmap = 0 ;
      if ((LoopCount > 0) && (ActLoopCount >= LoopCount)) {
        Invalidate(TRUE);
        StopAnimation = TRUE ;
        }
      else
        Invalidate(FALSE);
      }
    else
      Invalidate(FALSE);
    }
  }

AnimationBitmap::AnimationBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : StaticBitmap (RefWnd,Data,pData,pSize) 
  { 
  ActBitmap = 0 ;
  bTimerSet = FALSE;
  StopAnimation = FALSE; 
  }

void AnimationBitmap::Load ()
  {
  int AnzCols, AnzRows;
  HPALETTE hPal;
  HBITMAP hBmp = GetBitmap (BitRef()->bitId, AnzRows, AnzCols, hPal);

  DBINT FAR *lploopcnt = (DBINT FAR *)(* GetData)(privData, Param()->_LoopCount);
  LoopCount = (lploopcnt != NULL) ? *lploopcnt : 1;

  DBINT FAR *lpdelay = (DBINT FAR *)(* GetData)(privData, Param()->_DelayTime);
  int DelayTime = (lpdelay != NULL) ? *lpdelay : 0;

  if (!bTimerSet) {
    bTimerSet = TRUE;
    Parent->Parent->InsertToTimerList (this, UINT(DelayTime), NextFreeTimerId++);
    }

  StaticBitmap::Load ();
  }

void AnimationBitmap::Reset (BOOL doClear)
  {
  StopAnimation = TRUE;
  StaticBitmap::Reset(doClear);
  Parent->Parent->RemoveFromTimerList (this);
  }


