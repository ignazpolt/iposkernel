/////////////////////////////////////////////////////////////////
//    Implementierung der Klasse cWord,cField;
//
/////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/cword.cpv   1.151   29 Jun 2000 15:28:16   Wolfgang  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/cword.cpv  $
// 
//    Rev 1.151   29 Jun 2000 15:28:16   Wolfgang
// 1.) Bei Aenderung Zeilenabstand in ReformatAct alle Zeilen neu positionieren.
// 
//    Rev 1.150   17 May 2000 17:32:36   Wolfgang
// 1.) JustStringsSelected ignoriert doppelte Backslashes.
// 
//    Rev 1.149   02 Mar 2000 16:31:22   Wolfgang
// 1.) Zeilenumbruch bei lauter Tabs in einer Zeile verursacht keine
//     Endlosschleife mehr.
// 
//    Rev 1.148   01 Mar 2000 14:56:34   Wolfgang
// 1.) Invalidate nur bei existierendem Parent.
// 
//    Rev 1.147   16 Feb 2000 12:08:10   Martin
// nochmal WIN_ASSERT raus
// 
//    Rev 1.146   19 Jan 2000 20:05:26   Martin
// WIN_ASSERTs raus
// 
//    Rev 1.145   03 Sep 1999 05:03:38   Hannes
// Einrueckung aktiviert
// 
//    Rev 1.144   16 Aug 1999 18:37:48   Hannes
// Verbesserungen SlantFields
// 
//    Rev 1.143   04 Aug 1999 18:27:54   Wolfgang
// 1.) IsKeyToUse aus CWORD1 uebernommen.
// 2.) IsKeyToUse in OnKeyDown immer aufrufen.
// 3.) CheckDirKey bekommt Ergebnis von IsKeyToUse als Parameter.
// 
//    Rev 1.142   09 Jul 1999 14:16:02   Hannes
// Translatealways
// 
//    Rev 1.141   27 Jun 1999 21:55:40   Hannes
// Hilfsfunktionen fuer Rechtschreibpruefung
// 
//    Rev 1.140   31 May 1999 09:02:48   Hannes
// Seitenumbruchsproblem...
// 
//    Rev 1.139   29 Apr 1999 19:52:44   Martin
// "Termin-S   uche" korrigiert
// 
//    Rev 1.138   29 Apr 1999 19:42:32   Hannes
// operator =: SaveSel ev. reseten
// 
//    Rev 1.137   25 Nov 1998 10:06:36   Hannes
// outColor hat doch hoechste Prio
// 
//    Rev 1.136   24 Nov 1998 19:15:00   Hannes
// Beim Setfocus auf anderes Feld: ResetFormat
// 
//    Rev 1.135   18 Nov 1998 15:48:20   Hannes
// Diverse Verbesserungen am Farbhandling
// 
//    Rev 1.134   10 Nov 1998 07:58:12   Hannes
// Ev. Abschliessen mit FormatEnde
// 
//    Rev 1.133   09 Oct 1998 18:02:14   Gerhold
// Farben in Strings
// 
//    Rev 1.132   02 Sep 1998 09:26:44   Hannes
// Viewportsetzen: Im cfield::Paint
// 
//    Rev 1.131   01 Sep 1998 23:49:38   Hannes
// Umsetzen des ViewPorts bei Koordinaten > 32000
// 
//    Rev 1.130   09 Aug 1998 22:36:00   Hannes
// Verbesserungen Kontextmenue
// 
//    Rev 1.129   09 Jul 1998 10:49:40   Hannes
// \ - Handling im Clipboard
// 
//    Rev 1.128   07 Apr 1998 19:50:06   Hannes
// Verbessertes Refreshverhalten / Setzen von AnzLines, Mode
// 
//    Rev 1.127   16 Feb 1998 14:18:24   Gerhold
// VC++5.x ... explicit ist jetzt ein Schluesselwort
// 
//    Rev 1.126   30 Jan 1998 19:51:54   Hannes
// 
//    Rev 1.125   26 Jan 1998 20:02:46   Hannes
// 
//    Rev 1.124   16 Jan 1998 15:30:00   Hannes
// Diverse Druckverbesserungen
// 
//    Rev 1.123   19 Nov 1997 18:46:08   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.122   23 Oct 1997 20:29:40   Hannes
// Verbesserungen am Blocksatz
// 
//    Rev 1.121   24 Sep 1997 20:33:38   Hannes
// Formatumsetzung bei Mappings
// 
//    Rev 1.120   19 Sep 1997 15:48:14   Hannes
// 
//    Rev 1.119   14 Aug 1997 21:16:50   Hannes
// Hintergrundzeichnen unabhaengig vom Modus..
// 
//    Rev 1.118   02 Jul 1997 08:15:12   Hannes
// 
//    Rev 1.117   23 Apr 1997 15:32:14   Hannes
// 
//    Rev 1.116   10 Apr 1997 11:41:20   Hannes
// SelectionInString
// 
//    Rev 1.115   28 Feb 1997 14:27:14   Hannes
// SetCaretTo
// 
//    Rev 1.114   19 Feb 1997 12:10:44   Hannes
// InsertStringAtCaret
// 
//    Rev 1.113   05 Feb 1997 16:24:04   GERHOLD
// 
//    Rev 1.112   05 Feb 1997 14:06:28   HANNES
// 
//    Rev 1.111   05 Feb 1997 13:50:46   HANNES
// 
//    Rev 1.110   05 Feb 1997 13:02:52   HANNES
// 
//    Rev 1.109   05 Feb 1997 12:50:40   HANNES
// 
//    Rev 1.108   31 Jan 1997 15:39:00   HANNES
// 
//    Rev 1.107   29 Jan 1997 18:10:46   HANNES
// 
//    Rev 1.106   27 Jan 1997 17:26:02   HANNES
// Verbesserungen an der Formatierung
// 
//    Rev 1.105   08 Jan 1997 14:39:46   HANNES
// BreakAllowed verbessert, mehrseitige Felder verbessert
// 
//    Rev 1.104   28 Oct 1996 08:41:58   HANNES
// Aufruf von WorkOn auch bei Feldern mit Knoepfen
// 
//    Rev 1.103   30 Sep 1996 16:09:10   GERHOLD
// ::OnSetFocus  if (doSelect) ... else { ... SetCaretToEnd; }
// 
//    Rev 1.102   28 Sep 1996 15:48:04   GERHOLD
// Funktion SetFocusFlag und fieldMode FM_NOSELECTIONONFOCUS
// 
//    Rev 1.101   27 Sep 1996 17:53:26   MARTIN
// WORDTYPE_SPACE wird in IsLineEndReached jetzt frueher abgefragt
// 
//    Rev 1.100   05 Sep 1996 07:01:28   HANNES
// F2 nicht bei Knopf - Feldern
// 
//    Rev 1.99   04 Sep 1996 15:54:54   HANNES
// 
//    Rev 1.98   28 May 1996 16:37:46   HANNES
// 
//    Rev 1.97   22 May 1996 18:00:50   MARTIN
// alten Font wieder zurueckselektieren
// 
//    Rev 1.96   20 May 1996 17:33:08   HANNES
// Ab Koordinate 30000 nix mehr weitermachen!
// 
//    Rev 1.95   18 May 1996 20:56:36   HANNES
// FehlerKorrekturen
// 
//    Rev 1.94   09 May 1996 19:10:28   HANNES
// Fehlerkorrekturen
// 
//    Rev 1.93   07 May 1996 18:09:52   HANNES
// 
//    Rev 1.92   06 May 1996 12:59:22   HANNES
// ZeilenGrenze
// 
//    Rev 1.91   30 Apr 1996 17:08:44   HANNES
// Fehlerkorrektur: CompareIVListe, ShiftHandling, FormatSelection
// 
//    Rev 1.90   13 Apr 1996 21:56:28   HANNES
// OnSetFocus: act != NULL ...
// 
//    Rev 1.89   13 Apr 1996 19:55:56   HANNES
// Verbesserung von Mehrseitigen Feldern, Passworthandling
// 
//    Rev 1.88   04 Apr 1996 20:31:48   HANNES
// 
//    Rev 1.87   04 Apr 1996 19:33:52   HANNES
// Formatieren: Startselektion verbessert
// 
//    Rev 1.86   04 Apr 1996 18:34:52   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.85   04 Apr 1996 12:16:04   GERHOLD
// FM_NOFIELDRECT
// 
//    Rev 1.84   24 Mar 1996 12:10:52   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.83   22 Mar 1996 12:13:16   HANNES
// Aenderungen Hannes
// 
//    Rev 1.82   23 Feb 1996 09:50:30   HANNES
// Flackern, versteckter Trennstrich
// 
//    Rev 1.81   16 Feb 1996 15:25:04   hannes
// 
//    Rev 1.80   02 Feb 1996 10:46:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.79   15 Jan 1996 17:58:00   MARTIN
// richtige Breite bei bunten Feldern
// 
//    Rev 1.78   11 Jan 1996 04:49:22   HANNES
// 
//    Rev 1.77   11 Jan 1996 03:34:56   HANNES
// 
//    Rev 1.76   10 Jan 1996 21:04:44   HANNES
// 
//    Rev 1.75   10 Jan 1996 18:16:04   HANNES
// FormatMaps
// 
//    Rev 1.74   10 Jan 1996 17:54:20   HANNES
// RemoveFormatInfo, FormatMaps
// 
//    Rev 1.73   10 Jan 1996 15:04:12   GERHOLD
// Soll ein Combo-Formularfeld Eingaben zulassen muss nach dem fieldMode
// FM_BTNWITHINPUT abgefragt werden.
// 
//    Rev 1.72   08 Jan 1996 17:41:30   HANNES
// Defaultmodify, Wortumbruch
// 
//    Rev 1.71   05 Jan 1996 20:00:16   HANNES
// Fehlerkorrektur Formatierung
// 
//    Rev 1.69   02 Jan 1996 22:11:20   HANNES
// Formatierung von Feldern, Zertrennung von cword.cpp
// 
//    Rev 1.67   12 Dec 1995 12:07:54   GERHOLD
// cField::OnKillFocus hat als Parameter das Fensterhandle das den Focus bekommt
// dieses wird ueber die Callback-Funktion an die Toolbar weitergereicht.
// 
//    Rev 1.66   06 Dec 1995 14:42:04   MARTIN
// MyUnionRect korrigiert (r->left = r2->top --> r->left = r2->left)
// 
//    Rev 1.65   04 Dec 1995 18:06:00   MARTIN
// un-Woerter nicht bei GetMinMax beruecksichtigen
// 
//    Rev 1.64   23 Nov 1995 17:42:48   GERHOLD
// exportierte Klassenfunktion cField::GetFieldMode()
// 
//    Rev 1.63   16 Nov 1995 19:45:20   GERHOLD
// neuer FieldMode  FM_UPPERCHAR (Umwandlung in Grossbuchstaben)
// 
//    Rev 1.62   02 Nov 1995 20:11:08   GERHOLD
// 
//    Rev 1.61   02 Nov 1995 10:39:00   GERHOLD
// FM_NOGERMANCHARS (wandelt Umlaute um)
// 
//    Rev 1.60   31 Oct 1995 07:35:04   GERHOLD
// Unterstrich bei Eingabefeldern war manchmal auch oben -> swap top,bottom
// 
//    Rev 1.59   18 Oct 1995 11:10:44   GERHOLD
// Eingabefelder haben keinen Rahmen mehr, sondern sind unterstrichen.
// 
//    Rev 1.58   11 Sep 1995 20:23:30   MARTIN
// OnSetFocusProc
// 
//    Rev 1.57   07 Sep 1995 13:52:02   HANNES
// No change.
// 
//    Rev 1.56   24 Aug 1995 00:15:58   HANNES
// Positionierung des Buttons
// 
//    Rev 1.55   14 Aug 1995 08:25:02   HANNES
// sWord::Paint an cWord::Paint angegelichen
// 
//    Rev 1.54   10 Aug 1995 09:22:06   HANNES
// Drucken ohne Clipping
// 
//    Rev 1.53   02 Jul 1995 18:25:20   GERHOLD
// Zeilenumbruch bei Beistrichen ohne Space
// 
//    Rev 1.52   11 Jun 1995 19:16:18   MARTIN
// 
//    Rev 1.51   11 Jun 1995 13:46:20   GERHOLD
// hDC beim GetFieldPrinteDC abfragen
// 
//    Rev 1.50   10 Jun 1995 22:01:40   HANNES
// Verwendung von MyGetTextExtent
// 
//    Rev 1.49   09 Jun 1995 18:05:56   GERHOLD
// POSTITCLASS
// 
//    Rev 1.48   09 Jun 1995 00:27:02   HANNES
// Minimale Optimierungen
// 
//    Rev 1.47   25 May 1995 17:15:42   HANNES
// ResetWords: Auch die Selektionen loeschen..
// 
//    Rev 1.46   23 May 1995 18:59:04   HANNES
// ReformatForPrinter
// cWord::breakCausedByMaxlen
// 
//    Rev 1.45   22 May 1995 11:17:56   HANNES
// Verbesserung der Zeilenumbruchsroutine fuer Woerter, die mehr als 2 Zeilen
// in Anspruch nehmen
// 
//    Rev 1.44   20 May 1995 14:13:44   HANNES
// Clipping - Probleme, Zeilenumbruch bei Worten, die groesser als eine Zeile
// sind
// 
//    Rev 1.43   19 May 1995 17:36:24   gerhold
// Selektion in mehrzeiligem funktioniert jetzt.
// 
//    Rev 1.42   17 May 1995 10:06:26   GERHOLD
// WM_KEYDOWN wird bei Combo- bzw. Up-Down-Control mittels WM_CHAR
// weitergeleitet.
// 
//    Rev 1.41   15 May 1995 14:03:26   HANNES
// Verbesserte Hoehenberechnung, Uninitialisierte Variable beim SetBkColor
// 
//    Rev 1.40   02 May 1995 13:27:22   GERHOLD
// Selektion verhaelt sich jetzt anders. Geloescht wird jetzt nut mehr mit DEL
// bzw. nur bei einem Eingabefeld fuer Zahlen.
// 
//    Rev 1.39   14 Apr 1995 12:05:58   HANNES
// 
//    Rev 1.38   05 Apr 1995 16:42:44   GERHOLD
// 
//    Rev 1.37   05 Apr 1995 09:29:30   GERHOLD
// 
//    Rev 1.36   04 Apr 1995 19:34:10   HANNES
// 
//    Rev 1.35   04 Apr 1995 18:40:56   HANNES
// 
//    Rev 1.34   04 Apr 1995 16:44:12   HANNES
// 
//    Rev 1.33   04 Apr 1995 14:51:48   GERHOLD
// 
//    Rev 1.32   04 Apr 1995 11:59:02   GERHOLD
// 
//    Rev 1.31   31 Mar 1995 13:10:40   HANNES
//  
// 
//    Rev 1.30   02 Mar 1995 15:25:52   GERHOLD
// "\" ist jetzt einmal eliminiert
// 
//    Rev 1.29   16 Feb 1995 12:50:04   HANNES
// 
//    Rev 1.28   30 Jan 1995 15:03:22   GERHOLD
// 
//    Rev 1.27   25 Jan 1995 16:50:06   HANNES
// 
//    Rev 1.26   24 Jan 1995 11:01:24   HANNES
// 
//    Rev 1.25   20 Jan 1995 15:50:50   HANNES
// OnMouseMove bei Feldern mit HasButton
// 
//    Rev 1.24   16 Jan 1995 18:19:14   GERHOLD
// 
//    Rev 1.23   19 Dec 1994 15:30:36   GERHOLD
// InvalidateFull in SetFocus, KillFocus
// 
//    Rev 1.22   16 Dec 1994 16:26:14   GERHOLD
// Focus Gschichterln
// 
//    Rev 1.21   15 Dec 1994 21:12:24   HANNES
// 
//    Rev 1.20   15 Dec 1994 18:23:18   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.19   15 Dec 1994 14:20:10   GERHOLD
// 
//    Rev 1.18   11 Dec 1994 14:40:06   HANNES
// RemoveFormatInfoFrom
// 
//    Rev 1.17   09 Dec 1994 19:42:38   HANNES
// 
//    Rev 1.16   28 Nov 1994 20:03:02   GERHOLD
// Selektierte Zeichen werden bei Eingabe eines Zeichens geloescht.
// 
//    Rev 1.15   21 Nov 1994 20:41:36   HANNES
// 
//    Rev 1.14   21 Nov 1994 09:52:40   HANNES
// 
//    Rev 1.13   19 Nov 1994 16:31:50   HANNES
// GetLeftlower auch mit unterschiedlichen Formaten
// 
//    Rev 1.12   19 Nov 1994 15:16:12   GERHOLD
// ~CWord ... statt DestroyCaret -> ReleaseCaret
// 
//    Rev 1.11   17 Nov 1994 18:08:26   GERHOLD
// nach SHIFT-INSERT und SHIFZ-DEL wird jetzt die Selektion zurueckgesetzt.
// 
//    Rev 1.10   31 Oct 1994 09:46:52   GERHOLD
// Mauseingaben die hinter dem letzten Wort stehen setzen das Caret an die 
// hinterste Position.
// SetCaretInLine ... Berechnen der optimalen Mausposition im Zeichen.
// 
//    Rev 1.9   25 Oct 1994 12:03:24   GERHOLD
// Der Zwischenablage ein bisschen zu viel Speicher weggenommen (Sorry!)
// 
//    Rev 1.8   20 Oct 1994 17:49:10   GERHOLD
// Clipboard Handling, Selektion
// 
//    Rev 1.7   13 Oct 1994 18:21:04   GERHOLD
// Beginn fuer Maus- und Cursor Selektion
// 
//    Rev 1.6   02 Oct 1994 17:00:24   HANNES
// Referenzhandle fuer unbekannte Fenster aus 0 gesetzt
// 
//    Rev 1.5   20 Sep 1994 11:24:18   HANNES
// No change.
// 
//    Rev 1.4   05 Sep 1994 10:48:56   HANNES
// OnKillFocus .. Invalidate vom Knopf
// 
//    Rev 1.3   10 Aug 1994 18:38:00   HANNES
// Fehler Im Invalidate (In Verbindung mit dem Knoepfchen)
// 
//    Rev 1.2   25 Jul 1994 09:40:26   GERHOLD
// cfieldcombo eingefuegt
// 
//    Rev 1.1   11 Jul 1994 14:01:42   HANNES
// Direktes Setzen der Farbe
// 
//    Rev 1.0   24 Jun 1994 16:48:40   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.35   14 Apr 1994 16:58:12   HANNES
// Overwritemodus in (Dialog)Editfeldern
// 
//    Rev 1.34   13 Apr 1994 14:30:06   HANNES
// Umstellung der SlantFields
// 
//    Rev 1.33   03 Mar 1994 22:13:08   HANNES
// PaintToMeta
// 
//    Rev 1.32   14 Feb 1994 19:50:16   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.31   11 Jan 1994 19:04:46   HANNES
// SetCaretToEnd
// 
//    Rev 1.30   04 Nov 1993 18:25:14   HANNES
// Fehlerkorrektur im Loadstring
// 
//    Rev 1.29   03 Nov 1993 17:45:36   HANNES
// Escape Taste nicht mehr bedingt
// 
//    Rev 1.28   18 Oct 1993 19:46:10   HANNES
// Grosschreibung des 1. Buchstabens
// 
//    Rev 1.27   04 Oct 1993 08:46:16   HANNES
// - Vernuenftiges Caret - Handling
// - operator = ohne Caretaenderung bei gleichem Text
// 
//    Rev 1.26   22 Sep 1993 10:18:36   HANNES
// Version nach St. Poelten
// 
//    Rev 1.25   24 Aug 1993 10:36:22   HANNES
// 
//    Rev 1.24   18 Aug 1993 10:47:24   HANNES
// Formatierung..
// 
//    Rev 1.23   05 Aug 1993 13:19:50   HANNES
// Verschiedene Rechteckfunktionen fuer MAPTYPE_GEOMETRIC
// 
//    Rev 1.22   20 Jul 1993 12:06:12   HANNES
// Arrange
// 
//    Rev 1.21   05 Jul 1993 15:01:14   HANNES
// Verbesserte Eingenschaften in Verbindung mit den Multiselektionslisten
// 
//    Rev 1.20   19 Jun 1993 19:34:44   HANNES
// Erweiterungen in Bezug auf Multiselektionslisten
// 
//    Rev 1.19   17 Jun 1993 09:30:12   HANNES
// Zusammenspiel mit den Multiselektionsfelder
// 
//    Rev 1.18   14 Jun 1993 19:18:36   HANNES
// Weite -1 -> Invalidate
// 
//    Rev 1.17   02 Jun 1993 19:40:54   HANNES
// DrawBlanks nicht mit bkmode==TRANSPARENT
// 
//    Rev 1.16   31 May 1993 12:52:16   HANNES
// abs->iabs
// 
//    Rev 1.15   28 May 1993 21:25:14   HANNES
// Einzeilige Felder -> besserer Test
// Caret beim Loeschen ebenfalls loeschen
// 
//    Rev 1.14   24 May 1993 14:21:04   HANNES
// Slant Felder
// 
//    Rev 1.13   13 May 1993 13:20:26   HANNES
// Verschiedene Verbesserungen des Carethandlings
// 
//    Rev 1.12   12 May 1993 19:23:56   HANNES
// GetActivePos
// 
//    Rev 1.11   12 May 1993 17:21:44   HANNES
// StartExternalPaint, EndExternalPaint
// 
//    Rev 1.10   11 May 1993 09:48:54   HANNES
// Fehler in ChangeText..
// 
//    Rev 1.9   11 May 1993 08:38:52   HANNES
// Korrektur Uebernahme des Wortes
// 
//    Rev 1.8   10 May 1993 12:54:48   HANNES
// verbesserte Fehlerabfragen
// 
//    Rev 1.7   09 May 1993 17:45:02   HANNES
// Uebernahme des ausgesuchten Wortes aus shlist
// 
//    Rev 1.6   07 May 1993 09:45:32   HANNES
// GetLeftLower
// 
//    Rev 1.5   06 May 1993 21:28:32   HANNES
// Kuerzelsystem eingebunden
// 
//    Rev 1.4   22 Apr 1993 10:27:34   HANNES
// Korrekturen des Rechteckhandlings fuer Tracings
// 
//    Rev 1.3   18 Apr 1993 22:29:30   HANNES
// Speicherfreigaben korrigiert
// 
//    Rev 1.2   06 Apr 1993 21:14:12   MARTIN
// Fehler: bei leerem Eingabefeld delete oder backspace druecken
// produzierte eine Exeption #13
// Loesung: in OnChar und bei VK_DELETE abfragen, ob Text != NULL,
// sonst Del/BS ignorieren
// 
//    Rev 1.1   05 Apr 1993 10:34:08   HANNES
// Verbesserungen der Layout Funktionen
// 
//    Rev 1.0   02 Apr 1993 18:12:50   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#define CFIELD_MAIN
#include "font.hpp"
#include "cfield.hpp"
#include "fldcombo.hpp"
#define MODULENUM 140
#include "winass.hpp"


extern LPSTR szWordWinClass;
cFieldCombo cfBtn;

char _startFormat[4];
char _endFormat[4];
char _startColor[11];
char _endColor[11];
DWORD _actColor;
void ResetActFormats ()
  {
  *_startFormat = *_endFormat = *_endColor = *_startColor = '\0' ;
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
void SetStartFormat (WORD modify)
  {
  _startFormat[0] = '\\' ;
  _startFormat[1] = 'm' ;
  _startFormat[2] = ModifyChar (modify) ;
  _startFormat[3] = '\0' ;
  }
void SetEndFormat (WORD modify)
  {
  _endFormat[0] = '\\' ;
  _endFormat[1] = 'm' ;
  _endFormat[2] = ModifyChar (modify);
  _endFormat[3] = '\0' ;
  }
LPSTR FarbFormat (DWORD Color)
  {
  if ((Color == 0L) || (Color == 0xFFFFFFFF))
    return "\\c:-\\" ;
  else {
    static char res[11];
    wsprintf (res,"\\c:%lX\\",Color);
    return res;
    }
  }
void SetStartColor (DWORD Color)
  {
  if (Color == 0xFFFFFFFF)
    _actColor = 0L;
  else
    _actColor = Color;
  lstrcpy (_startColor,FarbFormat (Color));
  }
void SetEndColor (DWORD Color)
  {
  lstrcpy (_endColor,FarbFormat (Color));
  }
LPSTR cField::makeStr (LPSTR str,char ch)
  {
  BOOL done = FALSE;
  int i = 0;
  if (ch == '\\') { str[0] = ch; str[1] = ch; str[2] = '\0' ; i = 2; done = TRUE; }
  if (fieldMode & FM_NOGERMANCHARS) {
    switch (ch) {
      case '\xE4' : str[i++] = 'a'; str[i++] = 'e'; done = TRUE; break;
      case '\xC4' : str[i++] = 'A'; str[i++] = 'e'; done = TRUE; break;
      case '\xF6' : str[i++] = 'o'; str[i++] = 'e'; done = TRUE; break;
      case '\xD6' : str[i++] = 'O'; str[i++] = 'e'; done = TRUE; break;
      case '\xFC' : str[i++] = 'u'; str[i++] = 'e'; done = TRUE; break;
      case '\xDC' : str[i++] = 'U'; str[i++] = 'e'; done = TRUE; break;
      case '\xDF' : str[i++] = 's'; str[i++] = 's'; done = TRUE; break;
      }
    
    if (done)
      str[i] = '\0';
    }

  if (!done) {
    str[0] = ch ; 
    str[1] = '\0' ; 
    }
    
  return str ; 
  }
LPSTR cField::makeStr (LPSTR str,LPSTR s1,char ch,LPSTR s2)
  {
  lstrcpy (str,s1);
  makeStr (str+lstrlen(s1),ch);
  lstrcat (str,s2);
  return str ;
  }

void ShowFieldCaret (HWND hWnd)
  {
  if (!CaretIsVisible) {
    HWND hActWnd = GetFocus();
    ShowCaret (hWnd);
    CaretIsVisible = TRUE;
    }
  }

void HideFieldCaret (HWND hWnd)
  {
  if (CaretIsVisible) {
    HWND hActWnd = GetFocus();
    HideCaret (hWnd);
    CaretIsVisible = FALSE;
    }
  }

void ShowRes (LPSTR txt)
  {
  MessageBox (GetActiveWindow (),txt,"Info",MB_ICONINFORMATION | MB_OK);
  }

void ShowRes (LPSTR txt,int r1,int r2 = 0,int r3 = 0,int r4 = 0)
  {
  char outtxt[128];
  wsprintf (outtxt,txt,r1,r2,r3,r4);
  ShowRes (outtxt);
  }

void ShowRes (LPSTR txt,LPSTR s,int r1,int r2 = 0,int r3 = 0,int r4 = 0)
  {
  char outtxt[128];
  wsprintf (outtxt,txt,s,r1,r2,r3,r4);
  ShowRes (outtxt);
  }

DLLExport LPVOID _export WINAPI wobj::operator new (size_t size) {
  return GetGlobMem (size);
  }

DLLExport void _export WINAPI wobj::operator delete (LPVOID obj) {
  FreeGlobMem (obj);
  }

void cWord::DrawBlanks (HDC hDC)
  {
  if (Parent->bkmode != TRANSPARENT) {
    HPEN hP = (HPEN)SelectObject (hDC,GetStockObject (WHITE_PEN));
    HBRUSH hB = (HBRUSH)SelectObject (hDC,GetStockObject (WHITE_BRUSH));
    RECT r,r1;
    r.left = xPos + Parent->x0;
    r.top = yPos - yBaseHeight + Parent->y0;
    r.right = r.left + xLen;
    r.bottom = r.top + yHeight;
    if (Parent->EstimatedRect (&r1,Parent->ErsteSeite))
      IntersectRect (&r,&r,&r1);
    Rectangle (hDC,r.left,r.top,r.right,r.bottom);
    SelectObject (hDC,hB);
    SelectObject (hDC,hP);
    }
  }

#define INFDX   50
static BOOL isActPrinting;
void cWord::Paint (HDC hDC, int Seite, BOOL Inverted, int xLeft, int xRight)
  {
  HFONT OldFont = 0;
  Parent->ModifyDC (hDC,wFormat,wModify,&OldFont);
  COLORREF OldBackColor, OldTextColor;

  LPSTR TextToPaint ;
  if ((AnzChars > 0) && (*Text != '\r')) {
    RECT r,r1;
    if (WordType == WORDTYPE_HIDDEN) {
      if ((Next != NULL) && (Next->LineNmbr != LineNmbr)) {
        GetWordRect (&r);
        r.right = r.left + xIntermWidth (hDC,1);
        TextToPaint = "-" ;
        }
      else {
        if (OldFont)
          SelectObject(hDC,OldFont);
        return ;  // sowieso nix tun (Verstecktes Trennzeichen)
        }
      }
    else {
      GetWordRect (&r);
      TextToPaint = Text ;
      }
    if (Parent->EstimatedRect (&r1,Seite))
      IntersectRect (&r,&r,&r1);

    // nur Felder die eine Selektion erlauben
    BOOL bkDone = FALSE ;
    BOOL txDone = FALSE ;
    UINT bkMode = 0;

    int ac = (WordType == WORDTYPE_EXTSPACE) ? 0 : AnzChars ;

    if ((Parent->bkmode == OPAQUE) || (Inverted)) {
      if (isActPrinting)
        bkMode = ETO_OPAQUE;
      else
        bkMode = ETO_CLIPPED | ETO_OPAQUE;
      RECT rs = r ;
      rs.left = xLeft + Parent->x0 - 1;
      rs.right = xRight + Parent->x0 + 1;

      if ((Inverted) && (lmemcmp (&r,&rs,sizeof(r)))) {
        OldBackColor = SetBkColor (hDC, GetSysColor(COLOR_HIGHLIGHT));
        OldTextColor = SetTextColor (hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        bkDone = TRUE;
        ExtTextOut (hDC,xPos+Parent->x0 + xExtra,yPos+Parent->y0 + 
                          Parent->yModifyOffset (hDC,wFormat,wModify),
                        bkMode, &rs,TextToPaint,ac,chWidth);
        }
      else {
        if (dwColor != 0xFFFFFFFF) {
          DWORD dwnColor;
          if ((Parent->outcolor & 0xFF000000) != 0)
            dwnColor = Parent->outcolor & 0x00FFFFFF ;
          else
            dwnColor = dwColor;

          if (Parent->cfb != NULL)
            (* Parent->cfb) (CALLBACKCMD_TRANSLATECLR,&dwnColor,Parent->CallBackMem);

          OldTextColor = SetTextColor (hDC,dwnColor);
          txDone = TRUE ;
          }
        ExtTextOut (hDC,xPos+Parent->x0 + xExtra,yPos+Parent->y0 +
                          Parent->yModifyOffset (hDC,wFormat,wModify),
                      bkMode, &r,TextToPaint,ac,chWidth);
        if (Inverted) {
          OldBackColor = SetBkColor (hDC, GetSysColor(COLOR_HIGHLIGHT));
          if (dwColor != 0xFFFFFFFF) {
            SetTextColor (hDC, GetSysColor(COLOR_HIGHLIGHTTEXT)); // OldTextColor schon belegt
            txDone = FALSE ;
            }
          else
            OldTextColor = SetTextColor (hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
          bkDone = TRUE;
          ExtTextOut (hDC,xPos+Parent->x0 + xExtra,yPos+Parent->y0 + 
                          Parent->yModifyOffset (hDC,wFormat,wModify),
                          bkMode, &rs,TextToPaint,ac,chWidth);
          }
        }
      }
    else
      if ((WordType != WORDTYPE_HIDDEN) ||
          ((Next != NULL) && (Next->LineNmbr != LineNmbr))) {
        if (dwColor != 0xFFFFFFFF) {
          DWORD dwnColor;
          if ((Parent->outcolor & 0xFF000000) != 0)
            dwnColor = Parent->outcolor & 0x00FFFFFF ;
          else
            dwnColor = dwColor;

          if (Parent->cfb != NULL)
            (* Parent->cfb) (CALLBACKCMD_TRANSLATECLR,&dwnColor,Parent->CallBackMem);

          OldTextColor = SetTextColor (hDC,dwnColor);
          txDone = TRUE ;
          }
        ExtTextOut (hDC,xPos+Parent->x0 + xExtra,yPos+Parent->y0 + 
                      Parent->yModifyOffset (hDC,wFormat,wModify),
                      bkMode, &r,TextToPaint,ac,chWidth);
        }

    if (bkDone) {
      SetTextColor (hDC, OldTextColor);
      SetBkColor (hDC, OldBackColor);
      }
    if (txDone)
      SetTextColor (hDC,OldTextColor);
    }
  if (OldFont)
    SelectObject(hDC,OldFont);
  }

BOOL cWord::GetIVRect (HDC hDC, LPRECT r)
  {
  int myLen ;
  if ((AnzChars > 0) && (WordType == WORDTYPE_HIDDEN)) {
    if (chWidth != NULL) myLen = chWidth[0] ;
    else                 myLen = 0 ;    // Kommt von der Umwandlung '\r' -> versteckter Bindestrich ;
    }
  else
    myLen = xLen ;
  if ((AnzChars > 0) && (myLen > 0)) {
    r->left   = xPos + xExtra + Parent->x0;
    r->top    = yPos - yBaseHeight + Parent->y0;
    r->right  = r->left + myLen;
    r->bottom = r->top + yHeight;
    int swap ;
    if (r->top > r->bottom)
      swap = r->top, r->top = r->bottom, r->bottom = swap;
    RECT r1;
    if (Parent->EstimatedRect (&r1,Parent->ErsteSeite))
      IntersectRect (r,r,&r1);
    LPtoDP (hDC,LPPOINT(r),2);
    r->left  -= 1;
    r->right += 1;
    if (r->top > r->bottom)
      swap = r->top, r->top = r->bottom, r->bottom = swap;
    r->top -= 1;
    r->bottom += 1;
    return TRUE ;
    }
  return FALSE ;
  }
void cWord::Invalidate (HDC hDC, BOOL fErase)
  {
  RECT r ;
  if ((Parent != NULL) && (Parent->Wnd != NULL) && GetIVRect (hDC, &r))
    InvalidateRect (Parent->Wnd,&r, fErase);
  }

void cWord::GetWordRect (LPRECT r)
  {
  if (AnzChars > 0) {
    r->left = xPos + xExtra + Parent->x0;
    r->top = yPos - yBaseHeight + Parent->y0;
    r->right = r->left + xLen ;
    r->bottom = r->top + yHeight ;

    int swap;
    if (r->top > r->bottom) swap = r->top, r->top = r->bottom, r->bottom = swap;

    r->left -= 1;     r->top    -= Parent->yOrientation() ;
    r->right += 1;    r->bottom += Parent->yOrientation() ;
    }
  else
    SetRectEmpty (r);
  }

BOOL cWord::Visible (HDC hDC)
  {
  RECT r;
  if (WordType == WORDTYPE_HIDDEN) 
    return TRUE ; // Der wird meist sowieso nicht gezeichnet
  else {
    GetWordRect (&r);
    return RectVisible (hDC,&r);
    }
  }

int InterpreteFormat (LPSTR FAR *h)
  {
  int res = 0 ;
  for ( ; ((**h != '\\') && (**h)) ; (*h) ++ )
    res = res * 10 + **h - '0' ;
  if (**h == '\\') (*h) ++ ;
  else
    res = 0;  // WIN_ASSERT (FALSE);
  return res ;
  }

DWORD InterpreteColor (LPSTR FAR *h)
  {
  if (**h == '-') {
    (*h) ++ ;
    if (**h == '\\') (*h) ++ ;
    // else
    //   WIN_ASSERT (FALSE);
    return 0xFFFFFFFF ;
    }
  DWORD res = 0L ;
  for ( ; ((**h != '\\') && (**h)) ; (*h) ++ ) {
    if ((**h >= '0') && (**h <= '9'))
      res = res * 0x10 + **h - '0' ;
    else
      res = res * 0x10 + **h - 'A' + 10 ;
    }
  if (**h == '\\') (*h) ++ ;
  else
    res = 0L;  // WIN_ASSERT (FALSE);
  return res ;
  }

BOOL cWord::GetNextLinePos (int FAR &x,int FAR &y,int FAR &Seite,int lc)
  {
  int res = 0 ;
  x = Parent->xLeftSpace (wFormat) + (lc == 0) ? Parent->EinzugErsteZeile : Parent->ZeilenEinzugZeichen ;

  if (Parent->yPageMax > 0) {
    // Mit Seitenumbruch im Feld
    int dymax = Parent->yPageMax - Parent->y0 ;
    if (y + Parent->yLineOffs (wFormat) > dymax) {
      y = Parent->yPageNext - Parent->y0 + Parent->yTopHeight (wFormat) + Parent->yBaseHeight (wFormat);
      Seite = Seite + 1 ;
      }
    else {
      y += Parent->yLineOffs (wFormat) ;
      }
    }
  else
    y += Parent->yLineOffs (wFormat) ;

  return FALSE;
  }

BOOL cField::IsFormatStr (LPSTR h)
  { 
  return (*h == '\\') ;
  }

BOOL NextIsFormatStr (LPSTR h)
  { 
  if (*h == '\\') {
    return ((h[1] == 'f') || (h[1] == 'm') || (h[1] == 'i') || (h[1] == 'h') || (h[1] == 'e') || (h[1] == 'z') || (h[1] == 'c')) ;
    }
  else
    return FALSE ;
  }

BOOL cField::PrevIsFormatStr (LPSTR h,LPSTR Text)
  {
  char ch1,ch2,ch3 ;
  if (h > Text)
    ch1 = *(h-1);
  else
    ch1 = '\0';
  if (h > Text + 1)
    ch2 = *(h-2) ;
  else
    ch2 = '\0' ;
  if (h > Text + 2)
    ch3 = *(h-3) ;
  else
    ch3 = '\0' ;

  if (*h == '\\')
    return ch1 != '\\' ;  // "\\" ist kein Format, sonst muss es sich um 
                          // ein Format handeln
  else
    return ((ch1 == 'm') && (ch2 == '\\') && (ch3 != '\\')) ;  // Bsp. \\m0
  }

LPSTR cField::SkipFormat (LPSTR h)
  {
  while ((IsFormatStr(h)) && (!(h[1] == '\\'))) {
    h++;
    switch (*h) {
      case 'f' :
      case 'c' :
      case 'h' :
      case 'e' :
      case 'z' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        for ( ; ((*h) && (*h != '\\')) ; ) h++ ;
        h ++ ;
        break ;
        
      case 'm' :
        h += 2 ;
        break ;
        
      case 'i' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        for ( ; ((*h) && (*h != '\\')) ; ) h ++ ;
        h ++ ;
        break ;
        
      case '@' :  
        h++;
        break;

      case '\\' :
        return h;
        break;
        
      // default :
      //  WIN_ASSERT (FALSE);
      }
    }
    
  return h;
  }

LPSTR cField::SkipPrevFormat (LPSTR h)
  {
  // Setzt das Caret auf den Start der Formatierinfo
  ///////////////////////////////////////////////////
  BOOL ready = FALSE ;
  BOOL done = FALSE ;
  while (!ready) {
    if ((h > Text) && (IsFormatStr (h))) {
      // Formatierungsanweisung
      if (h > Text) {
        if (h[-1] == '\\') return h;
        h -- ;
        }
      while ((h > Text) && (!IsFormatStr(h))) h -- ;
      if (h > Text)
        h -- , done = TRUE ;
      }
    else if (((h > Text + 1) && (h[-1] == '\\') && (*h == 'm')) &&
             (!((h >= Text + 2) && (h[-2] == '\\')))) {
      if (h > Text + 2) h -= 2 , done = TRUE ;
      else              h = Text ;
      done = TRUE ;
      }
    else if (((h >= Text + 2) && (h[-2] == '\\') && (h[-1] == 'm')) &&
             (!((h >= Text + 3) && (h[-3] == '\\')))) {
      if (h > Text + 3) h -= 3 , done = TRUE ;
      else              h = Text;
      }
    else ready = TRUE ;
    }
  if (done)
    return h + 1 ;
  else
    return h ;
  }

LPSTR CheckFormat (LPSTR h,int FAR &Format,int FAR &Modify,DWORD FAR &actColor)
  {
  while ((h[0] == '\\') && (h[1] != '\\')) {
    h++;
    switch (*h) {
      case 'f' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        Format = InterpreteFormat (&h);
        break ;
      case 'c' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        actColor = InterpreteColor (&h);
        break ;
      case 'm' :
        h++ ;
        if ((*h >= '0') && (*h <= '9'))
          Modify = *h - '0' ;
        else if ((*h >= 'A') && (*h <= 'Z'))
          Modify = *h - 'A' + 10 ;
        else
          Modify = *h - 'a' + ('Z' - 'A' + 10) ;
        h++ ;
        break ;
      case 'i' :
      case 'e' :
      case 'h' :
      case 'z' :
        // Die sachen werden einfach geskippt
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        for ( ; ((*h) && (*h != '\\')) ; ) h ++ ;
        h ++ ;
        break ;

      case '@' :  
        h++;
        break;

      case '\\' :
        return h;
        break;

      // default :
      //  WIN_ASSERT (FALSE);
      }
    }

  return h;
  }

LPSTR cWord::CheckFormat (LPSTR h,int FAR &Format,int FAR &Modify,DWORD FAR &actColor)
  {
  while ((h[0] == '\\') && (h[1] != '\\')) {
    h++;
    switch (*h) {
      case 'f' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        Format = InterpreteFormat (&h);
        break ;
      case 'c' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        actColor = InterpreteColor (&h);
        break ;
      case 'm' :
        h++ ;
        Modify = ModifyNum (*h);
        h++ ;
        break ;
      case 'h' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        Parent->ZeilenAbstandProzent = InterpreteFormat (&h);
        break ;
      case 'e' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        Parent->ZeilenEinzugZeichen = InterpreteFormat (&h); 
        break ;
      case 'z' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        h++ ;
        Parent->EinzugErsteZeile = InterpreteFormat (&h); 
        break ;
      case 'i' :
        if ((* (++ h)) != ':') {
          // WIN_ASSERT (FALSE);
          h--;
          break;
          }
        for ( ; ((*h) && (*h != '\\')) ; ) h ++ ;
        h ++ ;
        break ;

      case '@' :  
        h++;
        break;

      case '\\' :
        return h;
        break;

      // default :
      //   WIN_ASSERT(FALSE);
      }
    }

  return h;
  }

// Nachsehen, ob Wort noch in der Zeile Platz hat.
// Wenn es nicht Platz hat, dann wird untersucht, ob es das
// einzige Wort in der Zeile ist.
// Wenn es das einzige Wort in der Zeile ist, dann wird das bereits
// abgearbeitete Wort unterbrochen und in der naechsten Zeile weiter
// gemacht.
// Sollte es nicht das einzige Wort sein, dann wird das ganze Wort
// in die naechste Zeile verschoben und dort weitergemacht.
///////////////////////////////////////////////////////////////
BOOL cWord::IsSingleWordInLine ()
  {
  cWord FAR *prev = Parent->GetPrev (this);
  if (prev == NULL) 
    return TRUE ;
  else 
    return (xPos == Parent->xLeftSpace(wFormat));
  }

int cWord::NextTabPos (int x)
  {
  return (x / (Parent->TabWidth ()) + 1) * Parent->TabWidth ();
  }

int cWord::TabMetric (int x,int AnzTabs)
  {
  int xold = x;
  TCB buffer;
  buffer.xold = buffer.xnew = x;
  buffer.AnzTabs = AnzTabs;
  buffer.isdone = FALSE ;
  if (Parent->cfb != NULL) {
    (* (Parent->cfb)) (CALLBACKCMD_GETNEXTTAB,&buffer,Parent->CallBackMem);
    }
  if (!buffer.isdone) {
    for (int i = 0 ; i < AnzTabs ; i++) {
      x = NextTabPos (x);
      }
    }
  else
    x = buffer.xnew;
  return x - xold;
  }

//----------------------------------------------------------------------------
// gibt den Offset des Wortes im gesamten Text zurueck
//----------------------------------------------------------------------------
WORD cWord::wOffs ()
  { 
  return (Text - Parent->Text); 
  }

//----------------------------------------------------------------------------
// gibt die Laenge des Wortes mit "AnzChars" Zeichen zurueck
//----------------------------------------------------------------------------
int cWord::xIntermWidth (HDC hDC,int AnzCharsToTest)
  {
  int res = 0;

  HFONT OldFont = 0;
  Parent->ModifyDC (hDC,wFormat,wModify,&OldFont);
  if (AnzCharsToTest > 0) {
    if (AnzCharsToTest > AnzChars) AnzCharsToTest = AnzChars ;
    if (WordType == WORDTYPE_EXTSPACE)
      res = TabMetric (xPos,AnzCharsToTest);
    else if (WordType == WORDTYPE_CR)
      res = 0;
    else if (WordType == WORDTYPE_HIDDEN) {
      if ((Next == NULL) || (Next->WordType != WORDTYPE_CHARS) || (Next->LineNmbr == LineNmbr))
        res = 0 ;
      else
        res = MyGetTextExtent (hDC,"-",1,NULL);
      }
    else
      res = MyGetTextExtent (hDC,Text,AnzCharsToTest,NULL);
    }

  if (OldFont)
    SelectObject(hDC,OldFont);
  return res;
  }

BOOL AllDigits (cWord FAR *w,int anzchars)
  {
  BOOL res = (w->AnzChars > 0);
  for (int i = 0 ; ((i < anzchars) && (res)) ; i++)
    res = res && (((w->Text[i] >= '0') && (w->Text[i] <= '9')) || (w->Text[i] == '.') || (w->Text[i] == ','));
  return res;
  }
inline BOOL cmpText (LPSTR t1,LPSTR t2,int AnzChars)
  {
  for ( int j = 0 ; ((*t1) && (*t2) && (*t1 == *t2)) ; t1 ++ , t2 ++ , j++) ;
  return ((*t1 == '\0') && (j == AnzChars)) ;
  }
BOOL IsUnit (cWord FAR *w,int AnzChars)
  {
  static LPSTR Units[] = {
    "%","kg","g","ml","mm","m","l"
    };
  for ( int i = 0 ; i < (sizeof(Units) / sizeof(*Units)) ; i++ )
    if (cmpText (Units[i],w->Text,AnzChars)) return TRUE ;
  return FALSE ;
  }
BOOL BreakAllowed (cWord FAR *w,cWord FAR *prev,cWord FAR *pprev,int AnzChars)
  {
  // Untersuchung, ob das Wort w in die naechste Zeile gestellt werden darf
  //-----------------------------------------------------------------------
  int prevType;
  BOOL pSingle;
  char lastChar;
  if (prev != NULL) {
    pSingle = prev->breakCausedByMaxLen;
    prevType = prev->WordType ;
    lastChar = (prev->AnzChars > 0) ? prev->Text[prev->AnzChars-1] : ',';
    }
  else {
    prevType = -1 ;
    }

  if (w->WordType == WORDTYPE_CHARS) {
    if (pSingle) return TRUE ;
    // Das Vorzeichen darf nicht von der Zahl getrennt werden
    if (((lastChar == '+') || (lastChar == '-') || (lastChar == '.') || (lastChar == ',')) && (AllDigits (w,w->AnzChars))) return FALSE ;
    if (((w->Text[0] == '?') || (w->Text[0] == '!')) &&
        ((prevType == WORDTYPE_SPACE) || (prevType == WORDTYPE_EXTSPACE)) && (pprev != NULL) && (pprev->WordType == WORDTYPE_CHARS))
      return FALSE ;
    if (((prevType == WORDTYPE_SPACE)  || (prevType == WORDTYPE_EXTSPACE))&& (pprev != NULL) && (IsUnit (w,AnzChars))) {
      // Die Einheit darf nicht von der Zahl getrennt werden
      //-----------------------------------------------------
      if (AllDigits (pprev,pprev->AnzChars)) return FALSE ;
      }
    if (w->Parent->IsWordEndChar (lastChar)) return TRUE ;
    return (prevType != WORDTYPE_CHARS);
    }
  else
    return FALSE ;
  }

BOOL cField::BreakInLineAllowed (cWord FAR *h)
  {
  cWord FAR *s = GetLineStart(h) ;
  if ((s == NULL) || (s == h)) return FALSE ;
  for (cWord FAR *x = s->Next ; (x != NULL) ; x = x->Next) {
    if (BreakAllowed(x,x->Prev,((x->Prev) != NULL) ? x->Prev->Prev : NULL,x->AnzChars)) return TRUE ;
    if (x == h) return FALSE ;
    }
  return FALSE ;
  }

BOOL cWord::GetWordWidth (HDC hDC,LPSTR Text,int AnzChars,LPINT FAR *chWidth)
  {
  return MyGetTextExtent (hDC,Text,AnzChars,chWidth);
  }
BOOL cWord::IsLineEndReached (HDC hDC,int AnzChars,BOOL FAR &NextToNextLine,
                                      int FAR &lc,BOOL FAR &stop,BOOL FAR &abort,int prevType)
  {
  if (WordType == WORDTYPE_EXTSPACE)
    xLen = TabMetric (xPos,AnzChars);
  else if (WordType == WORDTYPE_HIDDEN) {
    int xLen0 = MyGetTextExtent (hDC,"-",AnzChars,&chWidth);
    if (chWidth == NULL) {
      chWidth = (int FAR *) GetGlobMem (sizeof(int)) ;
      chWidth[0] = xLen0 ;
      }
    xLen = 0 ;
    }
  else if (WordType == WORDTYPE_CR)
    xLen = 0 ;
  else
    xLen = GetWordWidth (hDC,Text,AnzChars,&chWidth);

  yHeight = Parent->yLineOffs (wFormat);

  breakCausedByMaxLen = FALSE ;

  if ((xPos + xLen > Parent->xWidth - Parent->xRightSpace(wFormat)) &&
      (Parent->xWidth > 0)) {
    if ((WordType == WORDTYPE_SPACE) || (WordType == WORDTYPE_EXTSPACE)) {
      NextToNextLine = TRUE ;
      return FALSE ;
      }
    cWord FAR *prev = Parent->GetPrev(this);
    if (!Parent->BreakInLineAllowed (this)) {
      if (AnzChars > 1) {
        int space = Parent->xWidth - Parent->xRightSpace(wFormat) - xPos ;
        for (int charsForNext = 0 ; ((charsForNext < AnzChars - 1) && (xLen > space)) ; charsForNext ++ ) {
          if (WordType == WORDTYPE_EXTSPACE)
            xLen = TabMetric (xPos,AnzChars - charsForNext);
          else if (WordType == WORDTYPE_HIDDEN)
            xLen = 0 ;
          else
            xLen = GetWordWidth (hDC,Text,AnzChars - charsForNext,&chWidth);
          }

        yHeight = Parent->yLineOffs (wFormat);

        NextToNextLine = TRUE ;
        breakCausedByMaxLen = TRUE ;
        if ((Parent->AnzLines > 0) && (LineNmbr >= Parent->AnzLines - 1)) {
          stop = TRUE ;
          }
        return TRUE ;     // Aufhoehren damit
        }
      else {
        return TRUE ;
        }
      }
    else {
      if (BreakAllowed(this,prev,(prev != NULL) ? prev->Prev : NULL,AnzChars)) {
        // Wort nach vorne in die naechste Zeile setzen
        // und dort weitermachen
        lc ++ ;
        if ((Parent->AnzLines > 0) && (LineNmbr >= Parent->AnzLines - 1)) {
          AnzChars -- ;   // Abschneiden und fertig
          if (WordType == WORDTYPE_EXTSPACE)
            xLen = TabMetric (xPos,AnzChars);
          else if (WordType == WORDTYPE_HIDDEN)
            xLen = 0 ;
          else
            xLen = GetWordWidth (hDC,Text,AnzChars,&chWidth);
          stop = TRUE ;
          return TRUE ;
          }
        else {
          LineNmbr ++ ;
          return GetNextLinePos (xPos,yPos,RelativSeite,LineNmbr);
          }
        }
      else {
        // frueher war die Abfrage auf SPACE hier
        if ((Parent->AnzLines > 0) && (LineNmbr >= Parent->AnzLines - 1)) {
          AnzChars -- ;   // Abschneiden und fertig
          if (WordType == WORDTYPE_EXTSPACE)
            xLen = TabMetric (xPos,AnzChars);
          else if (WordType == WORDTYPE_HIDDEN)
            xLen = 0 ;
          else
            xLen = GetWordWidth (hDC,Text,AnzChars,&chWidth);
          stop = TRUE ;
          return TRUE ;
          }
        // Das Wort, in dem der Umbruch erlaubt ist, wird in die 
        // nacheste Zeile gesetzt
        cWord FAR *x = this ;
        for ( cWord FAR *h = Parent->GetPrev (this) ; h != NULL ; x = h , h = Parent->GetPrev (h)) {
          if (BreakAllowed(x,h,(h != NULL) ? h->Prev : NULL,(x == this) ? AnzChars : x->AnzChars)) break;
          }
        // das Wort x gehoert nach vorne in die naechste Zeile, die folgenden
        // Worte muessen up to date gebracht werden
        if (x != NULL) {
          lc ++ ;
          x->Invalidate (hDC);
          x->LineNmbr = lc ;
          x->GetNextLinePos (x->xPos,x->yPos,x->RelativSeite,lc);
          int _x_ = x->xPos + x->xLen ;
          int _y_ = x->yPos ;
          int _Seite_ = x->RelativSeite ;
          x->Invalidate (hDC);
          for ( x = x->Next ; x != NULL ; x = x->Next ) {
            x->Invalidate (hDC);
            x->LineNmbr = lc ;
            x->xPos = _x_ ;
            _x_ += x->xLen ;
            x->yPos = _y_ ;
            x->RelativSeite = _Seite_ ;
            x->Invalidate (hDC);
            if (x == this) break ;
            }
          }
        return FALSE ;
        }
      }
    }
  return FALSE ;
  }

// Interpretieren des Textes und abmessen des Wortes
///////////////////////////////////////////////////////////
int cWord::GetWordType (LPSTR h)
  {
  if (*h == ' ')                 return WORDTYPE_SPACE ;
  else if (*h == '\t')           return WORDTYPE_EXTSPACE ;
  else if (*h == '\r')           return WORDTYPE_CR ;
  else if (*h == CODE_HIDDENKEY) return WORDTYPE_HIDDEN ;
  else                           return WORDTYPE_CHARS ;
  }

BOOL cWord::IsWordToggle (LPSTR h)
  {
  return (WordType != GetWordType (h));
  }

//----------------------------------------------------------------------------
// liefert aus dem tring h das naechste Wort
//----------------------------------------------------------------------------
#define YMAX  30000
LPSTR cWord::GetNext (LPSTR h,HDC hDC,int FAR &x,
                      int FAR &y,int FAR &Format,int FAR &Modify,
                      int FAR &lc,BOOL FAR &stop,BOOL FAR &abort,
                      int prevType,int FAR &Seite,DWORD FAR &actColor
                     )
  {
  int oldFormat = Format;
  int oldModify = Modify;
  Text = h = CheckFormat (h,Format,Modify,actColor);
  LineNmbr = lc;

  AnzChars = 0;
  wFormat = Format;
  dwColor = actColor;
  wModify = BYTE(Modify);

  xPos = x ;
  yPos = y ;
  RelativSeite = Seite ;
  xLen = 0;

  HFONT dummy = 0;
  if ((oldFormat != Format) || (oldModify != Modify))
    Parent->ModifyDC (hDC,Format,Modify,&dummy);
  yBaseHeight = Parent->yBaseHeight (Format);

  WordType = GetWordType (h);  // SPACE, TAB, CR od. CHAR

  BOOL IsMDone = FALSE ;
  BOOL NextToNextLine = FALSE ;

  BOOL breakWord = FALSE ;
  BOOL ilDone ;
  int AnzExtra = 0 ;
  for ( ; ; ) {
    if ((ilDone = FALSE , *h == '\0') || (breakWord) || 
            (NextIsFormatStr(h)) || 
            // ((h[0] == '\\') && (h[1] == '\\') && (AnzChars > 0)) ||
            (*h == '\r') || 
            (IsWordToggle(h)) || 
            (ilDone = TRUE , IsMDone = IsLineEndReached(hDC,AnzChars+1,NextToNextLine,lc,stop,abort,prevType))
      ) break ;
    if ((WordType == WORDTYPE_SPACE) && (*h == ' '))
      breakWord = FALSE ;
    else if ((h[0] == '\\') && (h[1] == '\\')) {
      if (AnzChars == 0) {
        breakWord = TRUE ;
        h += 2 ;
        AnzChars = 1 ;
        AnzExtra = 1 ;
        }
      else 
        xLen = GetWordWidth (hDC,Text,AnzChars,&chWidth);
      break ;
      }
    else
      breakWord = Parent->IsWordEndChar(*h);
    h++;
    AnzChars ++;
    }

  if (!abort) {
    x = xPos + xLen ;
    y = yPos;
    Seite = RelativSeite ;
    if ((*h == '\r') && (h == Text)) {
      // Das einzige Zeichen in dem Wort
      AnzChars = 1;
      h ++ ;
      lc ++ ;
      GetNextLinePos (x,y,Seite,lc);
      if ((Parent->AnzLines > 0) && (lc > Parent->AnzLines - 1)) stop = TRUE ;
      }
    if (NextToNextLine) {
      lc ++ ;
      GetNextLinePos (x,y,Seite,lc);
      if ((Parent->AnzLines > 0) && (lc > Parent->AnzLines - 1)) stop = TRUE ;
      }
    }

  if (!ilDone)   // Wichtige Daten muessen auf jeden Fall berechnet werden
    IsLineEndReached (hDC,AnzChars,NextToNextLine,lc,stop,abort,prevType);

#ifndef WIN32
  if (Parent->y0 + yPos >= YMAX) abort = TRUE ;
#endif
  return Text + AnzChars + AnzExtra;
  }

int cWord::CheckAnzChars ()
  {
  LPSTR h = Text;
  for (int i = 0 ; ; i++) {
    if ((NextIsFormatStr(h)) || (IsWordToggle(h)) || (*h == '\0')) break ;
    h++ ;
    }
  return i ;
  }

BOOL cWord::CheckWord (LPSTR h,int x,int y,int Format,int Modify,int AnzChars,DWORD actColor)
  {
  h = CheckFormat (h,Format,Modify,actColor);
  if (Text != NULL)
    WordType = GetWordType (Text);
  BOOL res = ((h == Text) &&
              (x == xPos) && 
              (y == yPos) &&
              (wFormat == WORD(Format)) &&
              (wModify == BYTE(Modify)) &&
              (dwColor == actColor) &&
              (AnzChars == AnzChars) &&
              (CheckExtra ())
             );
  return res;
  }

void cWord::SetExtra (HDC hDC,int x,BOOL doInvalidate) 
  {
  if (xExtra != x) {
    if (doInvalidate) Invalidate (hDC);
    xExtra = x;
    if (doInvalidate) Invalidate (hDC);
    }
  }

// Loeschen Aller Worte
/////////////////////////////
FieldSelStruct SaveStart, SaveEnd;
BOOL SaveAlreadySelected;
cField FAR *SavecField;
void cField::ResetWords ()
  {
  cWord FAR *w = First ;
  for ( ; w != NULL ; ) {
    cWord FAR *n = w->Next ;
    delete w ;
    w = n ;
    }
  First = NULL ;
  act = NULL ;

  StartSel.SelWord = NULL ;
  StartSel.CaretPos = 0 ;
  EndSel.SelWord = NULL ;
  EndSel.CaretPos = 0 ;

  #ifdef UEBERLEGT
  SaveStart.SelWord = NULL ;
  SaveStart.CaretPos = 0 ;
  SaveEnd.SelWord = NULL ;
  SaveEnd.CaretPos = 0 ;
  SavecField = NULL;
  SaveAlreadySelected = FALSE ;
  #endif

  AlreadySelected = FALSE ;
  }

//
//    Voller Reformat
/////////////////////////////////////////////////////////
int cField::GetxSpace (cWord FAR *start,cWord FAR *end,int FAR &AnzIntermChars,BOOL checkBegin,BOOL checkEnd)
  {
  int res = xWidth;
  BOOL fWordOccured = FALSE ;
  AnzIntermChars = 0;
  int endchars = 0 ;
  int endspace = 0;
  for (cWord FAR *h = start ; h != NULL ; h = h->Next) {
    if (h->WordType == WORDTYPE_CHARS) fWordOccured = TRUE ;
    if ((checkBegin) && (!fWordOccured)) continue;
    if (h->WordType != WORDTYPE_CHARS) {
      AnzIntermChars ++ ;
      endchars ++ ;
      endspace += h->xLen;
      }
    else {
      endspace = 0;
      endchars = 0;
      }
    res -= h->xLen ;
    if (h == end)
      break ;
    }
  AnzIntermChars -= endchars;
  if (checkEnd) res += endspace;
  if (res < 0) res = 0;
  return res ;
  }

//----------------------------------------------------------------------------
// liefert das letzte Wort einer Zeile
//----------------------------------------------------------------------------
cWord FAR *cField::GetLineEnd (cWord FAR *beg,cWord FAR *end)
  {
  for (cWord FAR *h = beg ; h->Next != NULL ; h = h->Next) {
    if (h->Next->LineNmbr != beg->LineNmbr) break ;
    if (h == end) break ;
    }
  return h;
  }

BOOL cWord::CheckExtra ()
  {
  return Parent->CheckOutformat (NULL,this,NULL,FALSE,TRUE);
  }

void ExpandFormat (LPSTR endFormat,LPSTR h)
  {
  int l = lstrlen (endFormat);
  lmemcpy (endFormat + l,h,3);
  endFormat[l + 3] = '\0' ;
  }

BOOL dontSetSelection = FALSE;
DLLExport BOOL _export WINAPI cField::FormatSelection (WORD modify, BOOL doOff)
  {
  // 1. Die Selektion wird von dem KillFocus restauriert
  ///////////////////////////////////////////////////////
  FieldSelStruct SelStart, SelEnd;
  if (this == ActiveField) {
    if (AlreadySelected) {
      SaveStart = StartSel ;
      SaveEnd = EndSel ;
      GetSelectionFromLeftToRight (&SelStart, &SelEnd);
      }
    }
  else if (this == SavecField) {
    StartSel = SaveStart;
    EndSel = SaveEnd;
    AlreadySelected = SaveAlreadySelected;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);
    }
  if ((StartSel.SelWord != NULL) && (AlreadySelected)) {
    // Es ist etwas selektiert
    //---------------------------
    if (SelStart.CaretPos < int(SelStart.SelWord->wOffs()))
      SelStart.CaretPos = SelStart.SelWord->wOffs() ;
    LPSTR nTxt = LPSTR (GetGlobMem (GetBlockSize(Text) + 2 * 3)) ;
    BOOL ready = FALSE ;
    LPSTR x = nTxt ;
    char endFormat[128];
    endFormat[0] = '\\' ;
    endFormat[1] = 'm' ;
//    if (!doOff)
      endFormat[2] = ModifyChar(SelStart.SelWord->wModify) ;
//    else
//      endFormat[2] = ModifyChar(SelStart.SelWord->wModify & ~modify) ;
    endFormat[3] = '\0' ;
    LPSTR v = Text ;
    for (LPSTR h = Text ; ; ) {
      if (*h == '\0')
        break ;
      if (h < Text + SelStart.CaretPos) {
        // normal Umkopieren
        *x ++ = *h ++ ; 
        v ++ ;
        }
      else if (h < Text + SelEnd.CaretPos) {
        if (h == Text + SelStart.CaretPos) {
          if (!doOff) {
            // Den Modify einfuegen
            *x++ = '\\' ;
            *x++ = 'm' ;
            if (modify & (FI_LOW | FI_HIGH))
              *x++ = ModifyChar ((SelStart.SelWord->wModify & (~(FI_LOW | FI_HIGH))) | modify);
            else
              *x++ = ModifyChar (SelStart.SelWord->wModify | modify);
            ChangeWordPtrFrom (Text,Text,-3,v - Text);
            v += 3 ;
            }
          else {
            // Sicherheitshalber diese Attribute noch einmal ausschalten
            //------------------------------------------------------------
            *x++ = '\\' ;
            *x++ = 'm' ;
            *x++ = ModifyChar(SelStart.SelWord->wModify & ~modify);
            ChangeWordPtrFrom (Text,Text,-3,v - Text);
            v += 3 ;
            }
          }
        // Die Modifys zusammentragen, die Texte uebernehmen
        if ((*h == '\\') && (h[1] == 'm')) {
          *x ++ = *h ++ ; v ++ ;
          *x ++ = *h ++ ; v ++ ;
          endFormat[2] = *h ;
          if (!doOff) {
            if (modify & (FI_LOW | FI_HIGH))
              *x = ModifyChar ((ModifyNum (*h) & (~(FI_LOW | FI_HIGH))) | modify);
            else
              *x = ModifyChar (ModifyNum (*h) | modify);
            }
          else {
            *x = ModifyChar (ModifyNum (*h) & ~modify);
            }
          x ++ ; h ++ ; v ++ ;
          }
        else {
          // Normal kopieren
          *x ++ = *h ++ ;
          v ++ ;
          }
        }
      else if (h == Text + SelEnd.CaretPos) {
        // Das Endformat reinholen
        int l = lstrlen (endFormat);
        lstrcpy (x,endFormat);
        x += l;
        ChangeWordPtrFrom (Text,Text,-l,v - Text);
        // Das Zeichen normal kopieren
        *x ++ = *h ++ ;
        }
      else {
        // Normal kopieren, v muss nicht mehr mitgefuehrt werden
        *x ++ = *h ++ ;
        }
      }

    // Die Wortzeiger endgueltig korrigieren
    ChangeWordPtrFrom (nTxt,Text,0,0);
    FreeGlobMem (Text);
    Text = nTxt ;

    // Die nun ueberfluessigen Modifier raus
    RemoveNotNeededFormats ();

    // Reformat
    SetExistingAct ();
    SaveStart.SelWord = GetExistingWordWithPos (SaveStart.CaretPos);
    SaveEnd.SelWord = GetExistingWordWithPos (SaveEnd.CaretPos);
    StartSel = SaveStart;
    EndSel = SaveEnd;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);
    ReformatAct (SelStart.SelWord);

    // Den Focus auf das Fenster setzen
    StartSel.SelWord = GetExistingWordWithPos (SaveStart.CaretPos);
    EndSel.SelWord = GetExistingWordWithPos (SaveEnd.CaretPos);
    dontSetSelection = TRUE;
    SetFocus (Wnd);
    dontSetSelection = FALSE;

    if (cfb != NULL)
      (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
    }
  else {
    // Vermerken welches Format als naechstes gewuenscht wird
    ///////////////////////////////////////////////////////////////
    cWord FAR *fAct = GetWordForFormat ();
    WORD newModify;
    if (fAct != NULL) {
      SetEndFormat (fAct->wModify) ;
      newModify = fAct->wModify;
      }
    else {
      SetEndFormat (0);
      newModify = 0 ;
      }
    if (_startFormat[0])
      newModify = ModifyNum (_startFormat[2]);
    if (doOff) newModify = (newModify & (~modify)) ;
    else       newModify = (newModify | modify) ;
    SetStartFormat (newModify);
    dontSetSelection = TRUE;
    SetFocus (Wnd);
    dontSetSelection = FALSE;
    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI cField::ColorSelection (DWORD color)
  {
  // 1. Die Selektion wird von dem KillFocus restauriert
  ///////////////////////////////////////////////////////
  FieldSelStruct SelStart, SelEnd;
  if (this == ActiveField) {
    if (AlreadySelected) {
      SaveStart = StartSel ;
      SaveEnd = EndSel ;
      GetSelectionFromLeftToRight (&SelStart, &SelEnd);
      }
    }
  else if (this == SavecField) {
    StartSel = SaveStart;
    EndSel = SaveEnd;
    AlreadySelected = SaveAlreadySelected;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);
    }
  if ((StartSel.SelWord != NULL) && (AlreadySelected)) {
    // Es ist etwas selektiert
    //---------------------------
    if (SelStart.CaretPos < int(SelStart.SelWord->wOffs()))
      SelStart.CaretPos = SelStart.SelWord->wOffs() ;
    LPSTR nTxt = LPSTR (GetGlobMem (GetBlockSize(Text) + 2 * 10)) ;   // Ein Farbformat kann max. 10 Zeichen lang sein
    BOOL ready = FALSE ;
    LPSTR x = nTxt ;
    DWORD endColor = SelStart.SelWord->dwColor ;
    LPSTR v = Text ;
    for (LPSTR h = Text ; ; ) {
      if (*h == '\0')
        break ;
      if (h < Text + SelStart.CaretPos) {
        // normal Umkopieren
        *x ++ = *h ++ ; 
        v ++ ;
        }
      else if (h < Text + SelEnd.CaretPos) {
        if (h == Text + SelStart.CaretPos) {
          // Den Modify einfuegen
          LPSTR FFormat = FarbFormat(color);
          lstrcpy (x,FFormat);
          int l = lstrlen (FFormat);
          x += l;
          ChangeWordPtrFrom (Text,Text,-l,v - Text);
          v += l ;
          }
        if ((*h == '\\') && (h[1] == 'c') && (h[2] == ':')) {
          // Die Endfarben aktualisieren
          h += 3 ;
          LPSTR hHinterFarbe = h;
          endColor = InterpreteColor (&hHinterFarbe);
          v += 3 + hHinterFarbe - h;
          h = hHinterFarbe;
          }
        else {
          // Normal kopieren (die Texte uebernehmen)
          *x ++ = *h ++ ;
          v ++ ;
          }
        }
      else if (h == Text + SelEnd.CaretPos) {
        // Das Endformat reinholen
        LPSTR FFormat = FarbFormat(endColor);
        lstrcpy (x,FFormat);
        int l = lstrlen (FFormat);
        x += l;
        ChangeWordPtrFrom (Text,Text,-l,v - Text);
        // Das Zeichen normal kopieren
        *x ++ = *h ++ ;
        }
      else {
        // Normal kopieren, v muss nicht mehr mitgefuehrt werden
        *x ++ = *h ++ ;
        }
      }

    // Die Wortzeiger endgueltig korrigieren 
    //   (nTxt muss dabei noch einmal umkopiert werden, 
    //    da ansonsten nicht gewaehrleistet ist, dass nTxt exakt die richtige Laenge aufweist)
    LPSTR xText = LPSTR (GetGlobMem (lstrlen (nTxt) + 1));
    lstrcpy (xText,nTxt);
    ChangeWordPtrFrom (xText,Text,0,0);
    FreeGlobMem (Text);
    FreeGlobMem (nTxt);
    Text = xText ;

    // Die nun ueberfluessigen Modifier raus
    RemoveNotNeededFormats ();

    // Reformat
    SetExistingAct ();
    SaveStart.SelWord = GetExistingWordWithPos (SaveStart.CaretPos);
    SaveEnd.SelWord = GetExistingWordWithPos (SaveEnd.CaretPos);
    StartSel = SaveStart;
    EndSel = SaveEnd;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);
    ReformatAct (SelStart.SelWord);

    // Den Focus auf das Fenster setzen
    StartSel.SelWord = GetExistingWordWithPos (SaveStart.CaretPos);
    EndSel.SelWord = GetExistingWordWithPos (SaveEnd.CaretPos);
    dontSetSelection = TRUE;
    SetFocus (Wnd);
    dontSetSelection = FALSE;

    if (cfb != NULL)
      (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
    }
  else {
    // Vermerken welches Format als naechstes gewuenscht wird
    ///////////////////////////////////////////////////////////////
    cWord FAR *fAct = GetWordForFormat ();
    if (fAct != NULL)
      SetEndColor (fAct->dwColor) ;
    else
      SetEndColor (0L);
    SetStartColor (color);
    dontSetSelection = TRUE;
    SetFocus (Wnd);
    dontSetSelection = FALSE;
    }
  return FALSE ;
  }

BOOL cField::CheckOutformat (HDC hDC,cWord FAR *start,cWord FAR *end,BOOL doInvalidate,BOOL doCheck)
  {
  int of = OutFormat (start->wFormat);
  int AnzIntermChars;
  int xSpace;
  end = GetLineEnd (start,end);
  switch (of) {
    case FR_CENTERED :
      if (xWidth > 0) {
        xSpace = GetxSpace (start,end,AnzIntermChars);
        if (doCheck) return (start->xExtra == (xSpace / 2));
        for (cWord FAR *h = start ; h != NULL ; h = h->Next) {
          h->SetExtra (hDC,xSpace / 2,doInvalidate);
          if (h == end) break;
          }
        break ;
        }

    case FR_BLOCK :
      if ((xWidth > 0) && (end != NULL) && 
            (end->Next != NULL) && (end->WordType != WORDTYPE_CR)) {
        if (doCheck) return (start->xExtra == 0);
        xSpace = GetxSpace (start,end,AnzIntermChars,FALSE,TRUE);
        int j = 0 ;
        for (cWord FAR *h = start ; ((h != NULL) && (AnzIntermChars > 0)) ; 
                        h = h->Next) {
          h->SetExtra (hDC,(j >= 0) ? 
                               (j * xSpace) / AnzIntermChars : 0,
                               doInvalidate
                      );
          if (h->WordType != WORDTYPE_CHARS)
            j++;
          if (h == end) break;
          }
        break ;
        }
    case FR_RIGHT :
      if ((of == FR_RIGHT) && (xWidth > 0)) {
        xSpace = GetxSpace (start,end,AnzIntermChars,FALSE,TRUE);
        if (doCheck) return (start->xExtra == xSpace);
        for (cWord FAR *h = start ; h != NULL ; h = h->Next) {
          h->SetExtra (hDC,xSpace,doInvalidate);
          if (h == end) break;
          }
        break ;
        }
    default :
      if (doCheck) return (start->xExtra == 0);
      for (cWord FAR *h = start ; h != NULL ; h = h->Next) {
        h->SetExtra (hDC,0,doInvalidate);
        if (h == end) break;
        }
    
    }
  return FALSE ;
  }

void cField::SetSelectionPos (HDC hDC)
  {
  // ermittelt nach dem Reformat die selektierten Woerter anhand der 
  // Cursor-Positionen, und den Start bzw. das Ende der Selektion
  // in logischen Koordinaten (sinnvoll bei einer Skalierungsaenderung)
  if (AlreadySelected) {
    StartSel.SelWord = GetExistingWordWithPos (StartSel.CaretPos);
    cWord FAR *s = StartSel.SelWord;
    if (s != NULL) {
      if (WORD(StartSel.CaretPos) > s->wOffs())
        StartSel.xPos = s->xPos + 
                      s->xIntermWidth (hDC, StartSel.CaretPos - s->wOffs()) + s->xExtra ;
      else
        StartSel.xPos = s->xPos + s->xExtra ;
      }

    EndSel.SelWord = GetExistingWordWithPos (EndSel.CaretPos);
    cWord FAR *e = EndSel.SelWord;
    if (e != NULL) {
      if (WORD(EndSel.CaretPos) > e->wOffs())
        EndSel.xPos = e->xPos + 
                    e->xIntermWidth (hDC, EndSel.CaretPos - e->wOffs()) + e->xExtra ;
      else
        EndSel.xPos = e->xPos + e->xExtra ;
      }
    }
  }

void cField::Reformat (HDC hDC)
  {
  ResetWords ();

  if ((Text == NULL) || (*Text == '\0')) return ;

  LPSTR h = Text;
  cWord FAR *w;
  int Format = DefFormat;
  int Modify = DefModify ();
  DWORD actColor = 0xFFFFFFFF ;
  ZeilenAbstandProzent = 0 ;
  CheckFormat (Text,Format,Modify,actColor);   // Vielleicht steht ganz am Anfang
                                      // schon ein Formatstring

  BOOL doRelease;
  HFONT OldFont = 0;
  if (hDC == 0) hDC = GetFieldDC (Format,Modify,&OldFont)  , doRelease = TRUE ;
  else          ModifyDC (hDC,Format,Modify,&OldFont,TRUE) , doRelease = FALSE ;

  int x = xLeftSpace (Format) ;
  int y = yTopHeight (Format) + yBaseHeight (Format);
  int Seite = 0 ;
  int lc = 0;

  BOOL stop = FALSE ;
  BOOL abort = FALSE ;

  cWord FAR *ws = NULL;

  int prevType = -1 ;
  for ( prev = NULL ; ((h != NULL) && (*h) && (!stop) && (!abort)) ; ) {
    w = GetWord ();        // legt ein neues Wort an (mit new)
    if (First == NULL)
      First = w;
    else {
      w->Prev = prev;
      prev->Next = w;
      }
    if (ws == NULL) ws = w ;
    int olc = lc ;
    h = w->GetNext (h,hDC,x,y,Format,Modify,lc,stop,abort,prevType,Seite,actColor);
    prevType = w->WordType;
    if (abort) {
      if (prev != NULL)
        prev->Next = NULL ;
      else
        First = NULL ;
      delete w ;
      }
    else {
      prev = w;
      if ((olc != lc) && (ws != NULL)) {
        CheckOutformat (hDC,ws,w,FALSE);
        if (w->LineNmbr == olc)
          ws = NULL;
        else {
          ws = w;
          while ((ws->Prev != NULL) && (ws->LineNmbr == ws->Prev->LineNmbr))
            ws = ws->Prev;
          }
        }
      }
    }

  if (ws != NULL)
    CheckOutformat (hDC,ws,NULL,FALSE);

  if (ActiveField == this)
    PosCaret (hDC,TRUE);

  SetSelectionPos (hDC);

  if (OldFont)
    SelectObject(hDC,OldFont);
  if (doRelease)
    RestDC (hDC);
  }

void cField::ReformatForPrinter (HDC hDC)
  {
  if (First == NULL) Reformat (hDC);
#ifdef UEBERLEGT
  WIN_ASSERT (hDC);
  int Format = DefFormat;
  int Modify = DefModify();
  DWORD actColor = 0xFFFFFFFF ;
  CheckFormat (Text,Format,Modify,actColor);   // Vielleicht steht ganz am Anfang
                                      // schon ein Formatstring
  ModifyDC (hDC,Format,Modify,TRUE);

  int x0 = xLeftSpace (Format) ;
  int y = yTopHeight (Format) + yBaseHeight (Format);
  int olc = 0;

  cWord FAR *ws = NULL;

  int x = x0 ;
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next ) {
    if (ws == NULL) ws = w ;
    ModifyDC (hDC,w->wFormat,w->wModify);
    if (olc != w->LineNmbr)
      x = x0 ;
    w->xPos = x ;
    DWORD dwext = GetTextExtent (hDC,w->Text,w->AnzChars);
    if (w->WordType == WORDTYPE_EXTSPACE)
      w->xLen = w->TabMetric (w->xPos,w->AnzChars);
    else
      w->xLen = LOWORD(dwext);
    x = w->xPos + w->xLen ;
    if ((olc != w->LineNmbr) && (ws != NULL)) {
      CheckOutformat (hDC,ws,w,FALSE);
      if (w->LineNmbr == olc)
        ws = NULL;
      else {
        ws = w;
        while ((ws->Prev != NULL) && (ws->LineNmbr == ws->Prev->LineNmbr))
          ws = ws->Prev;
        }
      }
    olc = w->LineNmbr;
    }
  if (ws != NULL)
    CheckOutformat (hDC,ws,NULL,FALSE);
#endif
  }

void cField::SetWidth (int w)
  {
  xWidth = w;
  if (First != NULL) ResetWords();
  }

void cField::DelFollowings (HDC hDC,cWord FAR *w)
  {
  prev = GetPrev (w) ;

  if (prev) prev->Next = NULL ;
  else      First = NULL;

  for ( ; w != NULL ; ) {
    cWord FAR *next = w->Next;
    w->Invalidate(hDC);
    delete w;
    w = next;
    }
  }

//----------------------------------------------------------------------------
// gibt das erste Wort einer Zeile zur�ck
//----------------------------------------------------------------------------
cWord FAR *cField::GetLineStart (cWord FAR *w)
  {
  if (w == NULL) return w ;
  for (cWord FAR *h = w ; ((h->Prev != NULL) && (h->Prev->LineNmbr == w->LineNmbr)) ; h = h->Prev) ;
  return h ;
  }

cWord FAR *cField::GetLineStart ()
  {
  return GetLineStart (act);
  }

static RgnToIv FAR *rivList;
#define IVTYPE_OLD    0
#define IVTYPE_NEW    1
#define IVTYPE_NONE   2
void PushToIVList (cWord FAR *w,HDC hDC,int Type)
  {
  RECT r;
  if (w->GetIVRect (hDC,&r)) {
    RgnToIv FAR *rv = (RgnToIv FAR *) GetGlobMem (sizeof(*rv)) ;
    CopyRect (&rv->r,&r);
    LPSTR tToCopy ;
    int anz ;
    if ((Type == IVTYPE_OLD) && (w->oldText != NULL)) {
      tToCopy = w->oldText ;
      anz = GetBlockSize (w->oldText) - 1 ;
      }
    else if (Type = IVTYPE_NEW) {
      tToCopy = w->Text ;
      anz = w->AnzChars ;
      }
    else
      tToCopy = NULL ;
    if (tToCopy != NULL) {
      rv->Text = LPSTR (GetGlobMem (anz + 1));
      rv->AnzChars = anz ;
      lmemcpy (rv->Text,tToCopy,anz);
      }
    rv->Type = Type ;
    rv->Format = w->wFormat ;
    rv->Modify = w->wModify ;
    rv->Next = rivList ;
    rivList = rv ;
    }
  }
void InvalidateWhole (HWND hWnd)
  {
  for (RgnToIv FAR *r = rivList ; r != NULL ; r = r->Next) {
    if (r->Type != IVTYPE_NONE) InvalidateRect (hWnd,&r->r,TRUE) ;
    }
  }
void DeleteIVList ()
  {
  for ( ; rivList != NULL ; ) {
    RgnToIv FAR *n = rivList->Next ;
    if (rivList->Text != NULL)
      FreeGlobMem (rivList->Text) ;
    FreeGlobMem (rivList) ;
    rivList = n ;
    }
  }
int cField::PhysWidth (HDC hDC,LPSTR Text,int AnzChars)
  {
  int lw = MyGetTextExtent (hDC,Text,AnzChars,NULL);
  POINT pt[2];
  pt[0].x = 0 ;  pt[0].y = 0 ;
  pt[1].x = lw ; pt[1].y = 0 ;
  LPtoDP (hDC,pt,2);
  return pt[1].x - pt[0].x ;
  }
BOOL cField::SameChars (LPSTR t1,LPSTR t2,int FAR *res,int count)
  {
  for ( *res = 0 ; *res < count ; t1 ++ , t2 ++) {
    if (*t1 == *t2) (*res) ++ ;
    else break ;
    }
  return (*res > 0) ;
  }
void cField::CompareIV (HDC hDC,RgnToIv FAR *r1,RgnToIv FAR *r2,HWND hWnd,HFONT FAR *OldFont,BOOL FAR *firstCompare)
  {
  int AnzChars ;
  if ((r1->Type != IVTYPE_NONE) && (r2->Type != IVTYPE_NONE) &&
      (r1->AnzChars > 0) && (r2->AnzChars > 0) &&
      (r1->Format == r2->Format) &&
      (r1->Modify == r2->Modify) &&
      (r1->r.left == r2->r.left) &&
      (r1->r.top == r2->r.top) &&
      (r1->r.bottom == r2->r.bottom) &&
      (r1->Type != r2->Type) &&
      (SameChars (r1->Text,r2->Text,&AnzChars,min(r1->AnzChars,r2->AnzChars)))) {
    // Es muss nur die Schnittmenge der beiden Rechtecke invalidiert werden
    RECT r ;
    r.top = r1->r.top ;
    r.bottom = r1->r.bottom ;
    r.right = max(r1->r.right,r2->r.right);
    HFONT MyOldFont = 0;
    ModifyDC (hDC,r1->Format,r1->Modify,&MyOldFont);
    if (*firstCompare) {
      *OldFont = MyOldFont;
      *firstCompare = FALSE;
      }
    r.left = r1->r.left + PhysWidth (hDC,r1->Text,AnzChars);
    if (r.right > r.left)
      InvalidateRect (hWnd,&r,TRUE);
    r1->Type = r2->Type = IVTYPE_NONE ;
    }
  }
void cField::InvalidateIVList (HWND hWnd,HDC hDC,HFONT FAR *OldFont)
  {
  BOOL firstCompare = TRUE;
  *OldFont = 0;
  for (RgnToIv FAR *r1 = rivList ; r1 != NULL ; r1 = r1->Next) {
    for (RgnToIv FAR *r2 = r1->Next ; r2 != NULL ; r2 = r2->Next) {
      CompareIV (hDC,r1,r2,hWnd,OldFont,&firstCompare);
      }
    }
  InvalidateWhole (hWnd) ;
  DeleteIVList () ;
  }
void cField::DelWord (cWord FAR *h,HDC hDC)
  {
  if (h->Prev != NULL)
    h->Prev->Next = h->Next ;
  else
    First = h->Next ;
  if (h->Next != NULL)
    h->Next->Prev = h->Prev ;
  PushToIVList (h,hDC,IVTYPE_OLD);
  delete h ;
  }
void cField::ReformatAct (cWord FAR *formatFrom)
  {
  short oldZeilenAbstandProzent = ZeilenAbstandProzent;
  LPSTR h ;
  if (formatFrom == NULL) formatFrom = act ;
  if (formatFrom == NULL) {
    // Untersuchen, ob nicht hinten eingegeben wurde..
    if (cPos >= WORD(lstrlen(Text)))
      formatFrom = GetPrev(GetLineStart(GetLast ()));
    if (formatFrom == NULL)
      formatFrom = First ;
    }

  HDC hDC = GetFieldDC ();
  cWord FAR *w ;
  if (formatFrom != NULL) {
    int aType = -1 ;
    for ( w = GetPrev(formatFrom) ; ; ) {
      if (w == NULL) break ;
      if (aType == -1) aType = w->WordType ;
      if (w->WordType != aType) break ;
      w = GetPrev (w);
      }
    }
  else
    w = NULL ;
  if (w == NULL)      w = First,h = Text;
  else if (w != NULL) h = w->Text;

  HFONT OldFont = 0;
  if (w != NULL) {
    int Format,Modify,lc,x,y,Seite;
    DWORD actColor;
    if (w != First) {
      x = w->xPos;
      y = w->yPos;
      Seite = w->RelativSeite ;
      lc = w->LineNmbr ;
      Format = w->wFormat;
      Modify = w->wModify;
      actColor = w->dwColor;
      }
    else {
      Format = DefFormat;
      Modify = DefModify();
      actColor = 0xFFFFFFFF;
      ZeilenAbstandProzent = 0 ;
      h = Text;
      if (Text != NULL)
        CheckFormat (Text,Format,Modify,actColor);   // Vielleicht steht ganz am Anfang
                                            // schon ein Formatstring
      x = xLeftSpace (Format) ;
      y = yTopHeight (Format) + yBaseHeight (Format);
      Seite = 0 ;
      lc = 0 ;
      }

    ModifyDC (hDC,Format,Modify,&OldFont,TRUE);

    BOOL stop = FALSE ;
    BOOL abort = FALSE ;
    cWord FAR *ws = GetLineStart (w);
    cWord FAR *pw = GetPrev(w);
    cWord FAR *nextline;
    if (formatFrom != NULL) {
      nextline = GetLineEnd(formatFrom,NULL)->Next; // Beginn der naechsten Zeile 
      if ((nextline != NULL) && 
          ((nextline->Next == NULL) || (formatFrom == nextline))) nextline = NULL ; // da is nix, womit synchronisiert werden koennte
      }
    else
      nextline = NULL ;
    int prevType;
    if (pw == NULL) prevType = -1 ;
    else            prevType = pw->WordType;
    for ( ; ; ) {
      if (ws == NULL) ws = w;
      PushToIVList (w,hDC,IVTYPE_OLD);
      int olc = lc ;
      h = w->GetNext (h,hDC,x,y,Format,Modify,lc,stop,abort,prevType,Seite,actColor);
      prevType = w->WordType;
      if (stop) MessageBeep (0);
      if (!abort) {
        // w->Invalidate (hDC);
        PushToIVList (w,hDC,IVTYPE_NEW);
        if ((olc != lc) && (ws != NULL)) {
          CheckOutformat (hDC,ws,w,TRUE);
          if (w->LineNmbr == olc)
            ws = NULL ;
          else {
            ws = w;
            while ((ws->Prev != NULL) && (ws->LineNmbr == ws->Prev->LineNmbr))
              ws = ws->Prev;
            }
          }
        if ((h == NULL) || (*h == '\0') || (stop)) {
          if (w->Next != NULL) {
            DelFollowings (hDC,w->Next);
            }
          w = NULL ;
          }
        else {
          if (w->Next == NULL) 
            w->Next = GetWord ();
          else if (w->Next == nextline) {
            // Wort einschieben, damit noch die Chance besteht, wieder zu synchronisieren
            w->Next = GetWord ();
            w->Next->Next = nextline ;
            if (nextline != NULL)
              nextline->Prev = w->Next ;
            }
          if ((nextline != NULL) && 
              (oldZeilenAbstandProzent == ZeilenAbstandProzent) &&
              (w->CheckWord (nextline->Text,nextline->xPos,nextline->yPos,nextline->wFormat,nextline->wModify,nextline->AnzChars,nextline->dwColor))) {
            // Synchronisierung erfolgreich gelungen -> nextline kann geloescht werden und aufhoehren
            cWord FAR *wToDel = w->Next ;
            w->Next = nextline->Next ;
            if (w->Next != NULL)
              w->Next->Prev = w ;
            for ( ; ; ) {
              cWord FAR *h = wToDel->Next ;
              delete wToDel ;
              wToDel = h ;
              if (wToDel == w->Next) break ;  // Alle worte Loeschen bis w->Next
              }
            break ;
            }
          w->Next->Prev = w ;
          w = w->Next ;
          }
        if (w == NULL) break ;
        }
      else {
        DelFollowings (hDC,w);
        break ;
        }
      }
    if (ws != NULL) {
      CheckOutformat (hDC,ws,NULL,TRUE);
      }
    HFONT dummy = 0;
    InvalidateIVList (Wnd,hDC,&dummy);
    }
  else {
    // Noch nichts da -> voller Reformat und danach die Woerter einzeln
    // invalidieren

    for (w = First ; w != NULL ; w = w->Next)
      PushToIVList (w,hDC,IVTYPE_OLD) ;

    Reformat (hDC);

    for (w = First ; w != NULL ; w = w->Next)
      PushToIVList (w,hDC,IVTYPE_NEW) ;

    InvalidateIVList (Wnd,hDC,&OldFont);
    }
  SetSelectionPos (hDC);

  if (OldFont)
    SelectObject(hDC,OldFont);
  RestDC (hDC);
  ResetOld ();
  }

int cField::MappedFormat (int Format)
  {
  if (FormatMaps == NULL) return Format ;
  else {
    int AnzMaps = GetBlockSize (FormatMaps) / (2 * sizeof(int)) ;
    for (int i = 0 ; i < AnzMaps ; i++)
      if (FormatMaps [2 * i] == Format) return FormatMaps [2 * i + 1] ;
    }
  return Format ;
  }
int cField::xLeftSpace (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd(),MapType,MappedFormat(Format));
  return (lpfm != NULL) ? lpfm->xLeft : 0 ;
  }

//----------------------------------------------------------------------------
int cField::xRightSpace (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return (lpfm != NULL) ? lpfm->xRight : 0 ;
  }

//----------------------------------------------------------------------------
int cField::yTopHeight (int Format)
  {
  return 0;
  }

//----------------------------------------------------------------------------
int cField::yBottomHeight (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return yOrientation () * ((lpfm != NULL) ? lpfm->yExtraHeight : 0) ;
  }

//----------------------------------------------------------------------------
int cField::yBaseHeight (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return yOrientation () * ((lpfm != NULL) ? lpfm->yBaseHeight : 0) ;
  }

WORD cField::DefModify ()
  {
  LPFORMATINFO lpfi = GetFormatInfo (DefFormat);
  return lpfi->fi.DefFormat ;
  }

int cField::yModifyOffset (HDC hDC,int Format,int Modify)
  {
  if (Modify & (FI_LOW)) {
    TEXTMETRIC tm;
    GetTextMetrics (hDC,&tm);
    LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
    int res = - tm.tmHeight + tm.tmAscent - lpfm->yBaseHeight + lpfm->yHeight ;
    return yOrientation() * res ;
    }
  if (Modify & (FI_HIGH)) {
    TEXTMETRIC tm;
    GetTextMetrics (hDC,&tm);
    LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
    int res = tm.tmAscent - lpfm->yBaseHeight ;
    return yOrientation() * res ;
    }
  else
    return 0 ;
  }

//----------------------------------------------------------------------------
int cField::yHeight (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return yOrientation () * ((lpfm != NULL) ? lpfm->yHeight : 0) ;
  }
int cField::yLineOffs (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return yOrientation () * (lpfm->yHeight + 
                            lpfm->yExtraHeight +
                            lpfm->yBaseHeight * ZeilenAbstandProzent / 100);
  }

//----------------------------------------------------------------------------
int cField::LineHeight ()
  {
  return yHeight(DefFormat);
  }

int cField::yLineHeight (int Format)
  {
  LPFORMATMETRIC lpfm = GetFormatMetrics (GetFontRefWnd (),MapType,MappedFormat(Format));
  return yOrientation () * (lpfm->yHeight + 
                            lpfm->yExtraHeight +
                            lpfm->yBaseHeight * ZeilenAbstandProzent / 100);
  }

//----------------------------------------------------------------------------
int cField::OutFormat (int Format)
  {
  FontExtraInfo fei;
  fntGetFontExtraInfo (Format,&fei);
  return fei.FormatMode ;
  }

//----------------------------------------------------------------------------
void cField::RestDC (HDC hDC)
  {
  if (Wnd)
    ReleaseDC (Wnd,hDC);
  else
    (* cfb) (CALLBACKCMD_RELEASEPRDC,&hDC,CallBackMem);
  }

//----------------------------------------------------------------------------
void ExtSetGeomMap (HDC hDC,double scale,int xp,int yp,int xa,int ya)
  {
  SetMapMode (hDC,MM_ISOTROPIC);
  /* Fenster ist nun initialisert wie MM_LOMETRIC
     -> 1 Logische Einheit wird in 1/10 mm abgebildet, entspricht
     eim scale von 2.5 */
  // Berechnen des Aktuellen WindowExt
  POINT ptHelp[2];
  ptHelp[0].x = 0    , ptHelp[0].y = 0 ;
  ptHelp[1].x = 1000 , ptHelp[1].y = 1000 ;
  DPtoLP (hDC,ptHelp,2);
  // Berechnung der gewuenschten WindowExt
  int dx = ptHelp[1].x - ptHelp[0].x ;
  int dy = ptHelp[1].y - ptHelp[0].y ;
  dx = (int) (fabs ((double) dx * 2.5 / scale)) ;
  dy = - (int) (fabs ((double) dy * 2.5 / scale)) ;
  SetWindowExtEx (hDC,dx,dy,NULL);
  SetViewportExtEx (hDC,1000,1000, NULL);
  SetWindowOrgEx (hDC,xa,ya, NULL);
  SetViewportOrgEx (hDC,xp,yp, NULL);
  }

//----------------------------------------------------------------------------
void ExtSetTwipsMap (HDC hDC,double scale,int xp,int yp)
  {
  if (scale < 0.01) scale = 1.0;      // da is was faul
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,int (1440 / scale),int (1440 / scale), NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,xp,yp, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  }

//----------------------------------------------------------------------------
void cField::SetTwipsMap (HDC hDC)
  {
  ExtSetTwipsMap (hDC,scale,xp,yp);
  }

//----------------------------------------------------------------------------
void cField::SetGeomMap (HDC hDC)
  {
  ExtSetGeomMap (hDC,scale,xp,yp,xa,ya);
  }

//----------------------------------------------------------------------------
HDC cField::GetFieldDC ()
  {
  HDC hDC;
  if (Wnd)
    hDC = GetDC (Wnd);
  else
    (* cfb) (CALLBACKCMD_GETPRDC,&hDC,CallBackMem);
  if (MapType == MAPTYPE_GEOMETRIC)
    SetGeomMap (hDC);
  else
    SetTwipsMap (hDC);

  return hDC ;
  }

//----------------------------------------------------------------------------
HDC cField::GetPrDC ()
  {
  HDC hDC;
  (* cfb) (CALLBACKCMD_GETPRDC,&hDC,CallBackMem);
  if (MapType == MAPTYPE_GEOMETRIC)
    SetGeomMap (hDC);
  else
    SetTwipsMap (hDC);

  return hDC ;
  }

//----------------------------------------------------------------------------
void cField::RestPrDC (HDC hDC)
  {
  (* cfb) (CALLBACKCMD_RELEASEPRDC,&hDC,CallBackMem);
  }

//----------------------------------------------------------------------------
HDC cField::GetFieldDC (int Format,int Modify,HFONT FAR *OldFont)
  {
  HDC hDC = GetFieldDC ();

  ModifyDC (hDC,Format,Modify,OldFont,TRUE);

  return hDC ;
  }

//----------------------------------------------------------------------------
COLORREF cField::GetOutColor (int Format)
  {
  DWORD color;
  if ((outcolor & 0xFF000000) != 0)
    color = outcolor & 0x00FFFFFF ;
  else
    color = fntGetFormatColor(MappedFormat(Format));
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_TRANSLATECLR,&color,CallBackMem);

  return color;
  }

//----------------------------------------------------------------------------
HDC FontPrDC (HDC oldDC,LPVOID data)
  {
  HDC hDC = 0;
  cField FAR *d = (cField FAR *) data ;
  if (oldDC) {
    RestoreDC (oldDC,-1);
    (* d->cfb) (CALLBACKCMD_RELEASEPRDC,&oldDC,d->CallBackMem);
    }
  else {
    if (d->cfb != NULL) {
      (* d->cfb) (CALLBACKCMD_GETPRDC,&hDC,d->CallBackMem);

      if (hDC) {
        SaveDC (hDC);
        if (d->MapType == MAPTYPE_GEOMETRIC)
          ExtSetGeomMap (hDC,1.0,0,0,0,0);
        else
          ExtSetTwipsMap (hDC,1.0,0,0);
        }
      }
    }
  return hDC;
  }

void cField::ModifyDC (HDC hDC,int Format,int Modify,HFONT FAR *OldFont,BOOL full)
  {
  *OldFont = (HFONT)SelectObject (hDC,GetFontHandle(GetFontRefWnd (),MapType,MappedFormat(Format),Modify | ExtraModify,0,FontPrDC,this));
  DWORD color = GetOutColor(Format);
  SetTextColor (hDC,color);
  if (full) {
    SetTextAlign (hDC,TA_LEFT | TA_BASELINE);
    SetBkMode (hDC,bkmode);
    }
  }

//----------------------------------------------------------------------------
BOOL InExternPaint;
DLLExport void _export WINAPI cField::Paint (HDC hDC,int Seite,BOOL forPrinting)
  {
  BOOL oldPrinting = isActPrinting;
  isActPrinting = forPrinting ;
  if (First == NULL)
    Reformat (hDC);
  else if (forPrinting) {
    ReformatForPrinter (hDC);
    }
  SetTextAlign (hDC,TA_LEFT | TA_BASELINE);
  SetBkMode (hDC,bkmode);
  
  if ((StartSel.SelWord != NULL) && (EndSel.SelWord != NULL)) {
    StartSel.SelWord = GetExistingWordWithPos (StartSel.CaretPos);
    EndSel.SelWord = GetExistingWordWithPos (EndSel.CaretPos);
    SetSelectionPos (hDC);
    }
  FieldSelStruct SelStart, SelEnd;
  GetSelectionFromLeftToRight (&SelStart, &SelEnd);
  
  BOOL bSelected = FALSE;
  int xLeft = 0;
  int xRight = 0;

  int AnzahlSeiten = 1 ;
  POINT ovo,ovn;
  LONG dyPos = 0;
  LONG actLinePos = -1;
  BOOL ViewPosSet = FALSE;
  GetViewportOrgEx (hDC,&ovo);
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next ) {
    // Umsetzung des Viewport Origins
    LONG oldyPos = w->yPos;
    if ((w->yPos > 32000) && (w->yPos != actLinePos)) {
      // Scheiss Windows 95!!! (Und sowas schimpft sich 32 bit)
      SIZE we,ve;
      GetWindowExtEx (hDC,&we);
      GetViewportExtEx (hDC,&ve);

      LONG dyG = w->yPos / 32000 * 32000 ;  // Eine Ungefaeher Veraenderung
      LONG dvy = dyG * ve.cy / we.cy ;      // Aus dieser die Aenderung des VO
      dyPos = dvy * we.cy / ve.cy ;         // Aus dieser die Aenderung des WO

      ovn = ovo ;
      ovn.y += dvy;     // Viewport vergroessern

      SetViewportOrgEx (hDC,ovn.x,ovn.y,0);
      ViewPosSet = TRUE;

      w->yPos -= dyPos;    // Logische Koordinate verkleinern...
      }
    actLinePos = w->yPos;

    if (AnzahlSeiten <= w->RelativSeite)
      AnzahlSeiten = w->RelativSeite + 1;
    if ((yPageMax > 0) && (w->Next == NULL) && (w->WordType == WORDTYPE_CR)) {
      RECT rw;
      w->GetWordRect (&rw);
      int h = rw.bottom - rw.top + 1;
      if (rw.bottom + h > yPageMax) AnzahlSeiten = AnzahlSeiten + 1 ;
      }
    if ((ErsteSeite + w->RelativSeite == Seite) && (w->Visible (hDC))) {          // Wort im Update-Bereich?
      if (w == SelStart.SelWord) {
        // Selektion befindet sich in einem Wort
        if (SelStart.SelWord == SelEnd.SelWord) {
          xLeft = SelStart.xPos;
          xRight = SelEnd.xPos;
          bSelected = (xLeft != xRight) ;
          }
        else {
          xLeft = SelStart.xPos ;
          xRight = w->xPos + w->xExtra + w->xLen;
          bSelected = TRUE;            // die Selektion beginnt jetzt
          }  
        }
      else if (w == SelEnd.SelWord) {
        xLeft = w->xPos + w->xExtra ;
        xRight = SelEnd.xPos;
        }
      else {
        xLeft = w->xPos + w->xExtra;
        xRight = w->xPos + w->xExtra + w->xLenToPaint ();
        }
      
      w->Paint (hDC, Seite, bSelected, xLeft, xRight);
        
      if (w == SelEnd.SelWord)
        bSelected = FALSE;
      }
    else {
      // Wort wird zwar nicht gezeichnet, aber trotzdem mitteilen, da� die
      // Selektion jetzt beginnt.
      if (w == SelStart.SelWord)  
        bSelected = TRUE;
      if (w == SelEnd.SelWord)
        bSelected = FALSE;
      }  

    w->yPos = oldyPos;
    }
  if (ViewPosSet)
    SetViewportOrgEx (hDC,ovo.x,ovo.y,NULL);
      
  // Zeichnen des umgebenden Rechteckes
  if ((doSelect) && !(fieldMode & FM_NOFIELDRECT) && 
      (hAPen != 0) && (hIPen != 0) && (!forPrinting)) {
    BOOL bFieldIsActive = (this == ActiveField);
    SelectObject (hDC, bFieldIsActive ? hAPen : hIPen);
    RECT r;
    GetFullTextRect (&r,Seite);
    InflateRect (&r,1,1);

    int swap ;
    if (abs(r.top) > abs(r.bottom))
      swap = r.top, r.top = r.bottom, r.bottom = swap;

    if (Seite == ErsteSeite + AnzahlSeiten - 1) {
      MoveToEx (hDC,r.left,r.bottom, NULL);
      LineTo (hDC,r.right,r.bottom);
      }
    else
      MoveToEx (hDC,r.right,r.bottom, NULL);
    if (bFieldIsActive) {
      LineTo (hDC,r.right,r.top);
      if (Seite == ErsteSeite)
        LineTo (hDC,r.left,r.top);
      else
        MoveToEx (hDC,r.left,r.top, NULL);
      LineTo (hDC,r.left,r.bottom);
      }
    else if (GetAnzLines() > 1) {
      MoveToEx (hDC,r.left,r.bottom, NULL);
      LineTo (hDC,r.left,r.top);
      }
    }
  // Eventuelle Invertierungen
  if (!forPrinting)
    InvertText (hDC);
  if ((ActiveField == this) && (!HasButton || (fieldMode & FM_BTNWITHINPUT))) {
    if ((oldCaretHeight == 0) && (!InExternPaint))
      GetCaret ();
    PosCaret (hDC, TRUE, !InExternPaint);
    }
  if (forPrinting) ResetWords ();
  isActPrinting = oldPrinting;
  }

DLLExport void _export WINAPI cField::PaintToMeta (HDC hmDC)
  {
  HDC hDC = GetPrDC ();
  Reformat (hDC);
  SetTextAlign (hmDC,TA_LEFT | TA_BASELINE);
  SetBkMode (hmDC,bkmode);
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next )
    w->Paint (hmDC,ErsteSeite);
  ResetWords ();
  RestPrDC (hDC);
  }

inline int min4 (int x1,int x2,int x3,int x4)
  {
  int xm1 = min(x1,x2);
  int xm2 = min(x3,x4);
  return min(xm1,xm2);
  }

inline int max4 (int x1,int x2,int x3,int x4)
  {
  int xm1 = max(x1,x2);
  int xm2 = max(x3,x4);
  return max(xm1,xm2);
  }

void cField::MyUnionRect (LPRECT r,LPRECT r1,LPRECT r2)
  {
  if (IsRectEmpty (r1)) {
    int ymin = min(r2->top,r2->bottom);
    int ymax = max(r2->top,r2->bottom);
    r->top = ymin;
    r->bottom = ymax;
    r->left = r2->left;
    r->right = r2->right;
    }
  else {
    int xmin = min(r1->left,r2->left);
    int xmax = max(r1->right,r2->right);
    int ymin = min4(r1->top,r2->top,r1->bottom,r2->bottom);
    int ymax = max4(r1->top,r2->top,r1->bottom,r2->bottom);
    r->top = ymin;
    r->bottom = ymax;
    r->left = xmin;
    r->right = xmax;
    }
  }

void cField::Invalidate (int Seite,BOOL fErase)
  {
  if (IsWindow (Wnd)) {
    HDC hDC = GetFieldDC ();
    RECT r,rb;
    GetFullFieldRect (&r,Seite);
    if (cfBtn.GetBtnRect (this,&rb))
      MyUnionRect (LPRECT(&r),&rb, LPRECT(&r));

    LPtoDP (hDC,LPPOINT (&r),2);
    int swap;
    if (r.bottom < r.top)
      swap = r.bottom , r.bottom = r.top , r.top = swap;
    InflateRect (&r,3,3);
    InvalidateRect (Wnd, &r, fErase);
    RestDC (hDC);
    }
  }

void cField::InvalidateFull (int Seite,BOOL fErase)
  {
  if (IsWindow (Wnd)) {
    char szClassName[32];
    GetClassName(Wnd, szClassName, sizeof(szClassName));
  
    // Element nicht gefunden und Klasse <> WORDWIN => raus!
    if (!lstrcmp(szClassName, szWordWinClass)) {
      RECT rc;
    
      GetClientRect (Wnd, &rc);
      InflateRect (&rc,3,3);
      InvalidateRect (Wnd, &rc, fErase);
      }
    else  
      Invalidate (Seite,fErase);
    }
  }

DLLExport BOOL _export WINAPI cField::GetFieldRect (RECT FAR *r,int Seite)
  {
  if (First == NULL) Reformat ();     // Formatiert muss noch werden
  RECT rw;
  r->left = r->right = x0 ;
  r->top = r->bottom = y0 ;
  BOOL someDone = FALSE ;
  BOOL copyDone = FALSE ;
  BOOL copyBtn = FALSE ;
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next ) {
    if (ErsteSeite + w->RelativSeite != Seite) {
      if ((w->Next == NULL) && (w->WordType == WORDTYPE_CR) && 
          (ErsteSeite + w->RelativSeite == Seite - 1) && 
          (yPageMax > 0)) {
        w->GetWordRect (&rw);
        if (!IsRectEmpty (&rw)) {
          copyBtn = TRUE ;
          int h = rw.bottom - rw.top + 1;
          if (rw.bottom + h > yPageMax) {
            rw.top += h ;
            rw.left = x0 ;
            if (xWidth > 0)
              rw.right = x0 + xWidth ;
            else
              rw.right = rw.left + 1 ;
            rw.top = yPageNext ;
            rw.bottom = rw.top + h ;
            someDone = TRUE ;
            CopyRect (r,&rw);
            }
          }
        }
      continue ;
      }
    else {
      w->GetWordRect (&rw);
      if (!IsRectEmpty (&rw)) {
        if (w->Next == NULL) {
          if (yPageMax) {
            int h = rw.bottom - rw.top + 1;
            if (rw.bottom + h <= yPageMax) 
              copyBtn = TRUE ;
            }
          else
            copyBtn = TRUE ;
          }
        someDone = TRUE ;
        if ((w->Next == NULL) && (w->WordType == WORDTYPE_CR)) {
          int h = rw.bottom - rw.top + 1;
          if ((yPageMax > 0) && (rw.bottom + h < yPageMax))
              // Nur wenn nicht auf der naechsten Seite
            rw.bottom += h ;
          }
        if (!copyDone) {
          CopyRect (r,&rw);
          copyDone = TRUE ;
          }
        else
          MyUnionRect (r,&rw,r);
        }
      }
    }
  RECT rb;
  if ((!someDone) && (Seite == ErsteSeite) && (xWidth > 0)) {
    int lHeight = yLineHeight (DefFormat);
    r->left   = x0 - 1 ;
    r->top    = y0 - yOrientation() ;
    r->right  = x0 + xWidth + 1;
    r->bottom = y0 + lHeight + yOrientation();
    someDone = TRUE ;
    copyBtn = TRUE ;
    }

  if ((someDone) && (copyBtn) && (cfBtn.GetBtnRect (this,&rb)))
    MyUnionRect (r,&rb,r);
  return someDone;
  }

BOOL cField::SameText (LPSTR Txt,int len)
  {
  int tlen = lstrlen (Text);
  if ((len == tlen) && (lmemcmp (Txt,Text,len+1))) return TRUE ;
  if (len > tlen) {
    // Moeglicherweise ist der bereits mit Abschluss vorgesehene Text gemeint,
    // der wird ebenfalls ignoriert.
    int size;
    if (Text != NULL) size = GetStoredTextLength();
    else              size = 1;
    LPSTR buffer = LPSTR(GetGlobMem (size));
    if (Text != NULL)
      StoreText (buffer);

    LPSTR buffer2 = LPSTR(GetGlobMem (lstrlen (Txt) + 1));
    lstrcpy (buffer2,Txt);

    RemoveNotNeededFormats (buffer2,FALSE);

    int size2 = GetStoredTextLength(buffer2);
    LPSTR buffer1 = LPSTR(GetGlobMem (size2));
    StoreText (buffer2,buffer1);
    FreeGlobMem (buffer2);
    int len = lstrlen(buffer1);

    if ((lstrlen (buffer) == len) && (lmemcmp (buffer1,buffer,len+1))) {
      FreeGlobMem (buffer);
      FreeGlobMem (buffer1);
      return TRUE ;
      }
    FreeGlobMem (buffer);
    FreeGlobMem (buffer1);
    }

  return FALSE ;
  }
DLLExport cField FAR & _export WINAPI cField::operator = (LPSTR Txt)
  {
  int len = lstrlen (Txt);
  if ((Text == NULL) || (!SameText (Txt,len))) {
    LPSTR oTxt = Text;
    Text = LPSTR (GetGlobMem (len + 1));
    lstrcpy (Text,Txt);
    if (First != NULL) 
      ResetWords ();
    // Und den Text noch interpretieren
    LoadString ();

    // Caret neu setzen
    SetCaretToStart ();

    if (SavecField == this) {
      SaveStart.SelWord = GetExistingWordWithPos (SaveStart.CaretPos);
      SaveEnd.SelWord = GetExistingWordWithPos (SaveEnd.CaretPos);
      }

    if (oTxt != NULL)
      FreeGlobMem (oTxt);
    }
  return *this;
  }

DLLExport cField FAR & _export WINAPI cField::operator >> (POINT FAR &pt)
  {
  pt.x = x0 ;
  pt.y = y0 ;
  return *this;
  }

DLLExport cField FAR & _export WINAPI cField::operator >> (GLOBALHANDLE FAR &hGmem)
  {
  int size;
  if (Text != NULL) size = GetStoredTextLength();
  else              size = 1;
  hGmem = GlobalAlloc (GMEM_MOVEABLE,size);
  LPSTR buffer = LPSTR(GlobalLock (hGmem));
  if (Text != NULL)
    StoreText (buffer);
  else
    *buffer = '\0';
  GlobalUnlock (hGmem);
  return *this;
  }

BOOL cField::AllSameFormat () 
  {
  if (First == NULL) Reformat ();
  BOOL res = TRUE ;
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    res = res && (int (h->wFormat) == DefFormat) ;
    }
  return res;
  }

BOOL cField::AllSamePage () 
  {
  return (yPageMax == 0) ;
  }

int cField::LastPage () 
  {
  cWord FAR *h = GetLast();
  if (h == NULL) return 0 ;
  if ((h->WordType == WORDTYPE_CR) && (yPageMax > 0)) {
    RECT rw;
    h->GetWordRect (&rw);
    if (!IsRectEmpty (&rw)) {
      int wh = rw.bottom - rw.top + 1;
      if (rw.bottom + wh > yPageMax) {
        return h->RelativSeite + 1;
        }
      }
    }
  return h->RelativSeite ;
  }

BOOL _export FAR PASCAL cField::ZeilenGrenze (int l,int FAR *y1,int FAR *y2)
  {
  BOOL done = FALSE ;
  if (First == NULL) Reformat ();
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if (h->LineNmbr == l) {
      RECT r;
      h->GetWordRect (&r);
      if (!IsRectEmpty (&r)) {
        if ((!done) || (*y1 > r.top))
          *y1 = r.top ;
        if ((!done) || (*y2 < r.bottom))
          *y2 = r.bottom ;
        done = TRUE ;
        }
      }
    }
  return done ;
  }

BOOL cField::GetFullTextRect (LPRECT r,int Seite)
  {
  BOOL allSameFormat = AllSameFormat();
  BOOL allSamePage = AllSamePage();
  BOOL someDone = FALSE ;
  if ((AnzLines >= 1) && (xWidth > 0) && (allSameFormat) && (allSamePage) && (ErsteSeite == Seite)) {
    int lHeight = yLineHeight (DefFormat);
    r->left   = x0 ;
    r->top    = y0 ;
    r->right  = x0 + xWidth ;
    r->bottom = y0 + lHeight * AnzLines ;
    if (r->top > r->bottom) {
      int swap = r->bottom;
      r->bottom = r->top;
      r->top = swap;
      }
    someDone = TRUE ;
    }
  else if ((xWidth > 0) && (allSameFormat) && (allSamePage) && (ErsteSeite == Seite)) {
    int l = GetAnzLines ();
    if (l <= 0) l = 1;
    int lHeight = yLineHeight (DefFormat);
    r->left   = x0 ;
    r->bottom = y0 + lHeight * l;
    r->top    = y0 ;
    r->right  = x0 + xWidth;
    if (r->top > r->bottom) {
      int swap = r->bottom;
      r->bottom = r->top;
      r->top = swap;
      }
    someDone = TRUE ;
    }
  else {
    someDone = GetFieldRect (r,Seite);
    if ((xWidth > 0) /* && (r->right < (r->left + xWidth)) */ )
      r->right = r->left + xWidth;
    }
  return someDone ;
  }

DLLExport BOOL _export WINAPI cField::GetFullFieldRect (LPRECT r,int Seite)
  {
  BOOL someDone = GetFullTextRect (r,Seite);
  RECT rb;
  if ((someDone) && (cfBtn.GetBtnRect (this,&rb)))
    MyUnionRect (r,&rb,r);
  return someDone ;
  }

BOOL cField::EstimatedRect (LPRECT r,int Seite)
  {
  if ((AnzLines >= 1) && (xWidth > 0) && (AllSameFormat()) && (AllSamePage())) {
    int lHeight = yLineHeight(DefFormat);
    r->left   = x0 - 1;
    r->top    = y0 - 1;
    r->right  = x0 + xWidth + 1;
    r->bottom = y0 + lHeight * AnzLines + 1;
    if (r->top > r->bottom) {
      int swap = r->bottom;
      r->bottom = r->top;
      r->top = swap;
      }
    return TRUE ;
    }
  return FALSE ;
  }

DLLExport void _export WINAPI cField::SetSelectionPen (HPEN hActivePen,HPEN hInactivePen)
  {
  hAPen = hActivePen;
  hIPen = hInactivePen;
  doSelect = TRUE ;
  }

DLLExport void _export WINAPI cField::SetAnzLines (int AnzL)
  {
  if (AnzLines != AnzL)
    ResetWords();
  AnzLines = AnzL;
  }

DLLExport void _export WINAPI cField::SetFieldMode (DWORD mode)
  {
  if (AnzLines != 1)
    ResetWords();
  fieldMode = mode;
  if (fieldMode & FM_SINGLELINE) AnzLines = 1;
  }

DLLExport DWORD _export WINAPI cField::GetFieldMode ()
  {
  return fieldMode;
  }

DLLExport void _export WINAPI cField::SetHelpString (LPSTR hlp)
  {
  HelpString = hlp;
  }

DLLExport BOOL _export WINAPI cField::HasCaretPos ()
  {
  return ((Text != NULL) && (int (cPos) <= lstrlen (Text))) ;
  }

DLLExport void _export WINAPI cField::SetCaretToStart ()
  {
  if (Text != NULL)
    cPos = SkipFormat(Text) - Text;
  else 
    cPos = 0 ;
  }

DLLExport void _export WINAPI cField::SetCaretToEnd ()
  {
  if (Text != NULL)
    cPos = lstrlen(Text);
  else 
    cPos = 0 ;
  }

static cField FAR *LastActiveField;
DLLExport void _export WINAPI cField::OnSetFocus (BOOL bexplicit, int Seite, BOOL doSelect)
  {
  if (First == NULL) Reformat ();
  ActiveField = this;
  cfBtn.OnSetFocus (ActiveField);

  //----------------------------------------------------------------
  // der Feldmodus ist die oberste Instanz, um ueber eine Selektion
  // bei Fokuswechsel zu entscheiden, D,h, selbst wenn ein Benutzer 
  // die Selektion wuenscht, kann ein Feld mittels diese Flags das
  // Windows-Standard-Verhalten ausschalten
  //----------------------------------------------------------------
  doSelect = !(fieldMode & FM_NOSELECTIONONFOCUS);

  // globale Variable SelectFocusedFields sollte nur vom Script aus gesetzt werden
  if (doSelect)
    doSelect = SelectFocusedFields;

  if (LastActiveField != ActiveField)
    ResetActFormats ();
    
  if (((dontSetSelection) || (LastActiveField == ActiveField)) && (!bexplicit))
    doSelect = FALSE ;

  if ((doSelect) && (this == SavecField) && (!SaveAlreadySelected))
    doSelect = FALSE;

  if (First != NULL) {
    if (!HasButton  || (fieldMode & FM_BTNWITHINPUT)) {
      if (doSelect) {
        if (StartSel.SelWord == NULL) {
          HDC hDC = GetFieldDC ();
          AlreadySelected = TRUE;
        
          StartSel.SelWord = First;
          cWord FAR *s = StartSel.SelWord;
          StartSel.CaretPos = SkipFormat(Text) - Text;
          StartSel.xPos = s->xPos + s->xExtra + 
                          s->xIntermWidth (hDC, StartSel.CaretPos - s->wOffs());
      
          if (bexplicit) SetCaretToEnd ();
          EndSel.CaretPos = cPos;
          EndSel.SelWord = GetExistingWordWithPos (EndSel.CaretPos);
    
          s = EndSel.SelWord;
          EndSel.xPos = s->xPos + s->xExtra + 
                          s->xIntermWidth (hDC, EndSel.CaretPos - s->wOffs());
      
          RestDC (hDC);
          Invalidate (Seite,TRUE);
          }
        else
          Invalidate (Seite,FALSE);
        }
      else {
        if (this == SavecField) {
          StartSel = SaveStart;
          EndSel = SaveEnd;
          AlreadySelected = SaveAlreadySelected;
          }
        Invalidate (Seite,TRUE);
        if (bexplicit) SetCaretToEnd ();
        }
      }
    else {
      InvalidateFull (Seite,TRUE);  
      AlreadySelected = FALSE;
      }
    }  
  else {
    AlreadySelected = FALSE;
    if (HasButton)
      InvalidateFull (Seite,FALSE);
    else
      Invalidate (Seite,FALSE);
    }
    

  SetExistingAct ();

  if ((act != NULL) && 
      ((ErsteSeite + act->RelativSeite != Seite) ||
       ((yPageMax > 0) && (act->Next == NULL) && 
            (cPos >= WORD (act->wOffs() + act->AnzChars)) &&
            (act->WordType == WORDTYPE_CR) && 
            (act->yPos - act->yBaseHeight + y0 + 2 * act->yHeight > yPageMax)))   // Auf die naechste Seite 
     ) {
    // cPos auf die entsprechende Seite positionieren
    for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
      if (ErsteSeite + h->RelativSeite == Seite) {
        act = h ;
        cPos = act->wOffs() ;
        break ;
        }
      }
    }

  GetCaret ();
  if (!HasButton || (fieldMode & FM_BTNWITHINPUT))
    PosCaret (0, TRUE);

  if (bexplicit)
    CheckScroll (Seite);
  if ((HelpString != NULL) && (cfb != NULL))
    (* cfb) (CALLBACKCMD_SHOWHELP,HelpString,CallBackMem);
  TestSelState (Seite);
  if (cfb != NULL) {
    (* cfb) (CALLBACKCMD_ONSETFOCUS,NULL,CallBackMem);
    WORD nModify;
    if (act != NULL)
      nModify = act->wModify ; 
    else
      nModify = DefModify() ;
    (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
    }
  }

//---------------------------------------------------------------------------
// wird bei WM_KILLFOCUS aufgerufen.
// ACHTUNG: der Parameter WP ist ein Default-Parameter (0), und gibt das
//          Fenster an, welches den Fokus verliert.
//---------------------------------------------------------------------------
DLLExport void _export WINAPI cField::OnKillFocus (WPARAM wP,int Seite)
  {
  ClearSelection ();
  
  if (HasButton)
    InvalidateFull (Seite,TRUE);
  else  
    Invalidate (Seite,TRUE);

  LastActiveField = this;
  ActiveField = NULL;
  cfBtn.OnKillFocus (ActiveField);
  ReleaseCaret ();
  if (cfb != NULL) {
    (* cfb) (CALLBACKCMD_RELEASEHELP,NULL,CallBackMem);
    
    
    (* cfb) (CALLBACKCMD_ONKILLFOCUS, &wP, CallBackMem);
    }
  ResetSelState (Seite);
  }

DLLExport void _export WINAPI OnKillFocusIf (cField FAR *h)
  {
  if (h == ActiveField)
    h->OnKillFocus (0,h->FirstPage());
  }

//----------------------------------------------------------------------------
int cField::SearchLineNmbr (HDC hDC, int y,int Seite)
  {
  if (First == NULL) 
    return 0;
    
  y -= y0;

  RECT r;
  GetFullTextRect (&r,Seite);
  if ((y+y0) < r.top)
    return -1;

  for (cWord FAR *h = First ; h != NULL ; ) {
    if ((ErsteSeite + h->RelativSeite == Seite) && 
            (y < h->yPos - yOrientation() * yBaseHeight(h->wFormat) + h->yHeight)) 
      break;
    h = GetLineEnd (h,NULL);  // nicht gefunden => an das Ende der Zeile
    h = h->Next ;             // naechste Zeile
    }
  if (h != NULL)
    return h->LineNmbr;
  else
    return GetAnzLines()+1;
  }

//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::OnLButtonDown (WPARAM wP, POINT pt,int Seite)
  {
  HDC hDC = GetFieldDC();
  toLPKoords (hDC,(int &)pt.x,(int &)pt.y);  // in logische Koordinaten
  RECT r;

  GetFullFieldRect (&r,Seite);       // Abmessungen in log. Koordinaten

  BOOL Found = FALSE;
  if (PtInRect (&r,pt)) {             // im Text Rechteck?
    if (cfBtn.OnLButtonDown (this, &pt)) {     // im Combo-Knopf?
      RestDC(hDC);
      OnLButtonDblClk(wP, pt, Seite);                 // dann mache die Liste auf
      return TRUE;
      } 
    else
      Found = TRUE;  
    }
    
  if ((HasButton && !(fieldMode & FM_BTNWITHINPUT)) && (Found)) {
    RestDC (hDC);
    return TRUE;
    }

  char szClassName[32];
  GetClassName(Wnd, szClassName, sizeof(szClassName));

  // Element nicht gefunden und Klasse <> WORDWIN => raus!
  if (!Found && (lstrcmp(szClassName, szWordWinClass) &&
                 lstrcmp(szClassName, "POSTITCLASS"))) {
    RestDC (hDC);
    return FALSE;
    }
    
  int x;
    
  if (AlreadySelected) {
    HideFieldCaret (Wnd);
    InvalidateSelectedWords ();
    }
    
  // ermittelt die neue Caret-Position
  SetCaretInLine (hDC, SearchLineNmbr(hDC, pt.y, Seite), pt.x);
  xvPos = -1 ;
  PosCaret (hDC, TRUE, FALSE,&x);
    
  StartSel.CaretPos = cPos;
  EndSel.CaretPos = StartSel.CaretPos;
  AlreadySelected = TRUE ;

  SetSelectionPos (hDC);

  RestDC (hDC);

  if (cfb != NULL) {
    WORD nModify;
    cWord FAR *fAct = GetWordForFormat ();
    if (fAct != NULL)
      nModify = fAct->wModify ;
    else
      nModify = DefModify() ;
    (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
    }
    
  return TRUE ;
  }

//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::OnMouseMove (WPARAM wP, POINT pt,int Seite)
  {
  if (!(wP & MK_LBUTTON))
    return FALSE;

  int x;
  WORD        OldCaretPos = cPos;
  cWord FAR * OldWordWithCaret = act;
  
  if (HasButton && !(fieldMode & FM_BTNWITHINPUT)) return FALSE;

  if (!AlreadySelected) {      // erst bei der ersten Mausbewegung
    AlreadySelected = TRUE;
    }

  HDC hDC = GetFieldDC ();
  toLPKoords (hDC,(int &)pt.x,(int &)pt.y);  // in logische Koordinaten

  SetCaretInLine (hDC, SearchLineNmbr(hDC, pt.y, Seite), pt.x);  // veraendert cPos!
  RestDC(hDC);

  if ((cPos != OldCaretPos) && (OldWordWithCaret != NULL)) {   // Position geaendert?
    CheckScroll(Seite);
    PosCaret (0,TRUE,FALSE,&x);
    InvalidateWordRange (OldWordWithCaret, act);  // invalidieren
    EndSel.SelWord = act;                  // Ende festlegen
    EndSel.CaretPos = cPos;
    EndSel.xPos = x - x0;

    if (cfb != NULL) {
      WORD nModify;
      if (act != NULL)
        nModify = act->wModify ; 
      else
        nModify = DefModify() ;
      (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
      }
    }
  return FALSE ;
  }

//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::OnLButtonUp (WPARAM wP, POINT pt, int Seite)
  {
  if (HasButton && !(fieldMode & FM_BTNWITHINPUT))
    return FALSE;

  ShowFieldCaret (Wnd);

  // Die Selektion ist natuerlich fuer die Blunz'n, 
  // wenn StartSel und Endsel gleich sind !!!
  if (StartSel.CaretPos == EndSel.CaretPos)
    ClearSelection ();

  return FALSE ;
  }

//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::OnLButtonDblClk (WPARAM wP, POINT pt,int Seite)
  {
  if (((fieldMode & FM_LSELECTION) || (fieldMode & FM_BTNWITHINPUT)) && (!IsLocked())) {
    ShowList ("");
    return TRUE ;
    }
  else
    return FALSE ;
  }

//----------------------------------------------------------------------------
BOOL cField::IsKeyToUse (WPARAM wP)
  {
  WORD orgChar = wP ;
  if (cfb != NULL) {
    TCI t;
    t.wP = wP ;
    t.cPos = GetRealPos ();
    (* cfb) (CALLBACKCMD_TESTKEYDOWN,&t,CallBackMem);
    wP = t.wP ;
    }
  return (wP == orgChar);
  }

//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::OnKeyDown (WPARAM wP,int Seite)
  {
  BOOL res = FALSE;
  BOOL keyToUse = IsKeyToUse (wP);
  if (IsSHWorkKey (wP)) {
    if ((cfb != NULL) && ((!HasButton) || (fieldMode & FM_BTNWITHINPUT))) {
      WORD beg,end;
      TWI FAR *actWord = NULL ;
      if ((Text != NULL) && (!IsIndexedText(cPos))) {
        if (IsWordEndChar (Text[cPos])) {
          if (cPos > 0)
            actWord = GetWord(cPos-1,beg,end,TRUE);
          }
        else
          actWord = GetWord(cPos,beg,end,TRUE);
        }
      if (actWord == NULL) {
        actWord = LPTWI (GetGlobMem (sizeof(*actWord)));
        actWord->Index = 0xFFFF;
        actWord->Format = 0xFFFF;
        actWord->Modify = DefModify();
        actWord->resWord = NULL;
        actWord->IsFirst = TRUE ;
        actWord->IsLast = TRUE ;
        beg = end = cPos;
        }
      (* cfb) (CALLBACKCMD_SHWORKON,actWord,CallBackMem);
      if (actWord->res) {
        SetActToCaret ();
        if (!IsIndexedText (cPos)) {
          ChangeText (actWord,beg,end,cPos,CPOS_GETEND);
          ReformatAct ();
          PosCaret ();
          }
        else
          MessageBeep (0);
        if (cfb != NULL)
          (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
        }
      if (actWord != NULL) FreeGlobMem (actWord);
      }
    else if (((fieldMode & FM_LSELECTION) || (fieldMode & FM_BTNWITHINPUT)) && (!IsLocked())) {
      ShowList ("");
      }
    CheckScroll (Seite);
    res = TRUE ;
    }
  else if (IsHiddenKey (wP)) {
    WORD wP1 = CODE_HIDDENKEY ;
    char str[64];
    //------------------------------------
    // Haessliche Micky-Maus Loesung!!!!!!
    char begstr[32],endstr[32];
    lstrcpy (begstr,_startFormat);
    lstrcat (begstr,_startColor);
    lstrcpy (endstr,_endFormat);
    lstrcat (endstr,_endColor);
    lstrcpy (str, makeStr(str, begstr,char(wP1), endstr));

    int mLen = GetMaxChars();
    int AvailableLen = mLen - GetAnzChars();
    if ((mLen < 0) || (AvailableLen > 0)) {
      if ((mLen > 0) && (lstrlen(str) >= AvailableLen)) {
        str[AvailableLen-1] = '\0';
        }
      
      InsertStr (str);
      // RemoveNotNeededFormats ();

      if (cfb != NULL)
        (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
      }
    CheckScroll (Seite);
    }
  else {
    if (res = CheckDirKey (wP,Seite,keyToUse))
      CheckScroll (Seite);
    }

  BOOL done = FALSE;
  if (cfb != NULL) {
    if (HasButton && !(fieldMode & FM_BTNWITHINPUT)) {    
      // in diesem Feld kann also nichts eingegeben werden (Combo oder UpDown)
      if ((wP == VK_UP) || (wP == VK_DOWN)) {
        OnChar (wP,Seite);     // vielleicht wollen diese Tasten aber behandelt werden.
        done = TRUE;
        }
      }
      
    if (!done) {
      WORD nModify;
      if (act != NULL)
        nModify = act->wModify ; 
      else
        nModify = DefModify() ;
      (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
      CheckScroll (Seite);
      }
    }
  return res;
  }

//--------------------------  IsTextLimited  ---------------------------------
BOOL cField::IsTextLimited ()
  {
  int res = -1 ;
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_GETMAXANZCHARS,&res,CallBackMem);
  if (res > 0) return ((lstrlen (Text) + 1) >= res) ;
  else         return FALSE ;
  }

//---------------------------  GetMaxChars  ----------------------------------
int cField::GetMaxChars ()
  {
  int res = -1 ;
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_GETMAXANZCHARS,&res,CallBackMem);
  return res;
  }

//--------------------------  GetAnzChars  -----------------------------------
int cField::GetAnzChars ()
  {
  return lstrlen(Text);
  }

BOOL cField::IsLocked ()
  {
  BOOL IsLocked = FALSE ;
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_ISLOCKED,&IsLocked,CallBackMem);
  return IsLocked;
  }

#define GRP_NORMAL    0
#define GRP_INDEX     1
#define GRP_LENGTH    2
#define GRP_OTHER     3
WORD cField::GetRealPos ()
  {
  if (Text == NULL) return 0 ;
  WORD res = 0 ;
  int length;
  LPSTR istart;

  WORD state = GRP_NORMAL;
  WORD cP = cPos ;
  // Untersuchen, ob davor ein Idex steht, wenn ja, dann muss er geloescht
  // werden
  if ((cP > 1) && (Text[cP - 1] == '\\')) {
    cP -= 2;
    while ((Text[cP] != '\\') && (cP > 0)) cP -- ;
    }
  for (LPSTR h = Text ; h < Text + cP ; ) {
    switch (state) {
      case GRP_NORMAL :
        if ((h[0] == '\\') && (h[1] == 'i') && (h[2] == ':')) {
          istart = h ;
          length = GetIndexedLength (h);
          res += 3 ;
          h += 3 ;
          state = GRP_INDEX ;
          }
        else {
          if ((h[0] == '\\') && (h[1] != 'm')) state = GRP_OTHER ;
          h++ ;
          res ++ ;
          }
        break ;
      case GRP_INDEX :
        if (*h == 'L')
          state = GRP_LENGTH ;
        h++ ;
        res ++ ;
        break ;
      case GRP_LENGTH :
        h = istart + length ;
        state = GRP_NORMAL ;
        break ;
      case GRP_OTHER :
        if (h[0] == '\\') state = GRP_NORMAL ;
        h++ ;
        res ++ ;
        break ;
      }
    }
  return res;
  }

DLLExport void _export WINAPI cField::SetFormatMaps (int FAR *Maps,int AnzMaps)
  {
  if (FormatMaps != NULL) FreeGlobMem (FormatMaps);
  int size = sizeof (*FormatMaps) * 2 * AnzMaps ;
  FormatMaps = (int FAR *) GetGlobMem (size) ;
  lmemcpy (FormatMaps,Maps,size);

  ResetWords ();
  }

extern int FormatSize (LPSTR FormatStart);
extern BOOL IsValidEscape (char ch);
DLLExport LPSTR _export WINAPI RemoveFormatInfoFromString (LPSTR Str)
  {
  if (Str == NULL) return NULL ;

  // 1. Zaehlen wieviel Zeichen benoetigt werden
  int i = 0 ;
  for ( LPSTR h = Str ; *h ; ) {
    if ((h[0] == '\\') && (h[1] == '\\')) {
      h += 2 ;
      i += 2 ;
      }
    else if ((h[0] == '\\') && (IsValidEscape (h[1])) && (h[2] == ':'))
      h += FormatSize (h) ;
    else {
      h ++ ;
      i ++ ;
      }
    }
  i ++ ;

  // 2. Text allozieren
  LPSTR res = LPSTR (GetGlobMem (i));

  // 3. Umschreiben
  LPSTR x = res ;
  for ( h = Str ; *h ; ) {
    if ((h[0] == '\\') && (IsValidEscape (h[1])) && (h[2] == ':'))
      h += FormatSize (h) ;
    else
      *x++ = *h ++ ;
    }

  return res ;
  }

DLLExport LPSTR _export WINAPI RemoveAllFormatInfoFromString (LPSTR Str)
  {
  if (Str == NULL) return NULL ;

  // 1. Zaehlen wieviel Zeichen benoetigt werden
  int i = 0 ;
  for ( LPSTR h = Str ; *h ; ) {
    if ((h[0] == '\\') && (h[1] == '\\')) {
      h += 2 ;
      i += 2 ;
      }
    else if ((h[0] == '\\') && (h[1] == 'm'))
      h += 3 ;
    else if ((h[0] == '\\') && (IsValidEscape (h[1])) && (h[2] == ':'))
      h += FormatSize (h) ;
    else {
      h ++ ;
      i ++ ;
      }
    }
  i ++ ;

  // 2. Text allozieren
  LPSTR res = LPSTR (GetGlobMem (i));

  // 3. Umschreiben
  LPSTR x = res ;
  for ( h = Str ; *h ; ) {
    if ((h[0] == '\\') && (h[1] == 'm'))
      h += 3 ;
    if ((h[0] == '\\') && (h[1] == '\\'))
      h += 2 ;
    else if ((h[0] == '\\') && (IsValidEscape (h[1])) && (h[2] == ':'))
      h += FormatSize (h) ;
    else
      *x++ = *h ++ ;
    }

  return res ;
  }

DLLExport void _export WINAPI ExchangeEscape (LPSTR Str)
  {
  if (Str == NULL) return ;

  // 1. Zaehlen wieviel Zeichen benoetigt werden
  for ( LPSTR h = Str ; *h ; ) {
    if ((h[0] == '\\') && (h[1] == '\\')) {
      h += 2 ;
      }
    else if ((h[0] == '\\') && (IsValidEscape (h[1])) && (h[2] == ':')) {
      int fs = FormatSize (h) ;
      *h = '';
      h[fs - 1] = '';
      }
    else {
      h ++ ;
      }
    }
  }

DLLExport void _export WINAPI ReexchangeEscape (LPSTR Str)
  {
  if (Str == NULL) return ;

  // 1. Zaehlen wieviel Zeichen benoetigt werden
  for ( LPSTR h = Str ; *h ; h ++ ) {
    if (*h == '') *h = '\\' ;
    }
  }

DLLExport short _export WINAPI cField::GetLineHeight ()
  {
  return ZeilenAbstandProzent;
  }

DLLExport void _export WINAPI cField::SetLineHeight (int za)
  {
  for ( LPSTR h = Text ; *h ; ) {
    if ((h[0] == '\\') && (h[1] == 'h') && (h[2] == ':'))
      break ;
    else
      h ++ ;
    }
  if (*h)    // Alte Info auf jeden Fall raus
    RemoveFormatFromText (Text,h,FormatSize(h),h,h,Text,TRUE);

  // An den Beginn des Textes die neue Info reinholen
  if (za > 0) {
    char prefix[32];
    wsprintf (prefix,"\\h:%d\\",za);
    // Die Wortzeiger korrigieren
    int len = lstrlen(prefix);
    LPSTR nText = LPSTR (GetGlobMem (lstrlen(Text) + len + 1)) ;
    lstrcpy (nText,prefix);
    lstrcat (nText,Text);
    ChangeWordPtrFrom (nText,Text,-len,-1);
    FreeGlobMem (Text);
    Text = nText;
    ReformatAct (First);
    if (cfb != NULL)
      (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
    }
  else {
    if (ZeilenAbstandProzent > 0) {
      ReformatAct (First);
      if (cfb != NULL)
        (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
      }
    }
  SetFocus (Wnd);
  }

DLLExport void _export WINAPI cField::SetPageBreak (int ymax,int y0Next)
  {
  yPageMax = ymax ;
  yPageNext = y0Next ;
  ResetWords ();    // Wenn schon formatiert ist, dann muss auf jeden Fall
                    // neu formatiert werden, da u.U. der Seitenumbruch noch
                    // nicht eingearbeitet ist
//  DBWIN_ASSERT (yPageMax > y0) ;
  }

//---------------------------------------------------------------------------
// Dieses Flag entscheidet, ob bei Erhalten des Fokus der Text im cField
// selektiert dargestellt wird.
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetFocusFlag (BOOL State)
  {
  SelectFocusedFields = State;
  }

DLLExport void _export WINAPI InsertAtCaret (cField FAR *f,LPSTR str)
  {
  f->InsertStr (str);
  // f->ReformatAct ();
  if (f->cfb != NULL) {
    (* f->cfb) (CALLBACKCMD_SAVESTR,f->Text,f->CallBackMem);
    int nModify = 0;
    (* f->cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,f->CallBackMem);
    }
  }

DLLExport void _export WINAPI SetAtCaret (cField FAR *f,LPSTR str)
  {
  *f = str;
  f->ReformatAct ();
  f->SetCaretToEnd ();
  if (f->cfb != NULL) {
    (* f->cfb) (CALLBACKCMD_SAVESTR,f->Text,f->CallBackMem);
    int nModify = 0;
    (* f->cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,f->CallBackMem);
    }
  }

DLLExport void _export WINAPI cField::SetCaretTo (int Line,int Col)
  {
  int l = 1; // Position von 1 an gerechnet
  int c = 1;
  cPos = 0xFFFF ;
  for (LPSTR h = Text ; (*h) ; h++) {
    if ((l == Line) && (c == Col)) {
      cPos = h - Text ;
      break ;
      }
    if (*h == '\r') l ++ , c = 1 ;
    else            c ++ ;
    }
  if (cPos == 0xFFFF) cPos = h - Text ;
  }

DLLExport BOOL _export WINAPI cField::JustStringsSelected ()
  {
  // 1. Die Selektion wird von dem KillFocus restauriert
  ///////////////////////////////////////////////////////
  FieldSelStruct SelStart, SelEnd;
  if (this == ActiveField) {
    if (AlreadySelected) {
      SaveStart = StartSel ;
      SaveEnd = EndSel ;
      GetSelectionFromLeftToRight (&SelStart, &SelEnd);
      }
    }
  else if (this == SavecField) {
    StartSel = SaveStart;
    EndSel = SaveEnd;
    AlreadySelected = SaveAlreadySelected;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);
    }
  if ((StartSel.SelWord != NULL) && (AlreadySelected)) {
    BOOL inString = FALSE ;
    BOOL res = TRUE ;
    BOOL lastWasBackslash = FALSE;
    for (LPSTR h = Text ; (res) ; h++) {
      if (((h - Text == SelStart.CaretPos) ||
           (h - Text == SelEnd.CaretPos)) && (!inString))
        res = FALSE ;
      switch (*h) {
        case '\\' :
          if (lastWasBackslash) 
            lastWasBackslash = !lastWasBackslash; // Doppelte zaehlen nicht!
          break ;
        case '"' :
          if (!lastWasBackslash) 
            inString = !inString ;
          lastWasBackslash = FALSE;
          break ;
        case '\0' :
          return res ;
          break ;
        default :
          lastWasBackslash = FALSE;
          break ;
        }
      }
      
    return res ;
    }
  else
    return FALSE ;
  }

DLLExport void _export WINAPI cField::SetSelection (int sPos,int sLen,int aktuelleSeite)
  {
  if (Text) {
    if ((sPos == 0) && (sLen == 0)) {
      // Reset der Selektion
      InvalidateSelectedWords ();
      ClearSelection ();
      return;
      }
    int rSeite;
    act = GetExistingWordWithPos (cPos);
    if (act != NULL)
      rSeite = act->RelativSeite;
    else
      rSeite = 0;
    InvalidateSelectedWords ();
    LPSTR h = Text;
    for ( int i = 0 ; ; ) {
      if (IsFormatStr(h)) h = SkipFormat (h);
      if (i == sPos) {
        StartSel.CaretPos = h - Text ;
        cPos = h - Text;
        }
      if (i == sPos + sLen) {
        EndSel.CaretPos = h - Text ;
        break ;
        }
      if (!*h) break ;
      h ++ ;
      i ++ ;
      }
    AlreadySelected = TRUE ;
    HDC hDC = GetFieldDC ();
    SetSelectionPos (hDC);
    InvalidateSelectedWords ();
    RestDC (hDC);

    act = GetExistingWordWithPos (cPos);
    WORD nModify;
    if (act != NULL)
      nModify = act->wModify ; 
    else
      nModify = DefModify() ;
    (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld


    if (act != NULL)
      CheckScroll (aktuelleSeite,TRUE);
    }
  }

DLLExport void _export WINAPI cField::ChangeSelection (int sPos,int sLen,LPSTR ntxt)
  {
  if (Text) {
    LPSTR nBuffer = LPSTR (GetGlobMem (lstrlen(Text) + lstrlen(ntxt) + 1));
    LPSTR x = nBuffer;
    LPSTR h = Text;
    BOOL inSelection = FALSE;
    int rSeite;
    if (StartSel.SelWord != NULL)
      rSeite = StartSel.SelWord->RelativSeite;
    else
      rSeite = 0;
    for ( int i = 0 ; ; ) {
      if (IsFormatStr(h)) {
        // Format rueber kopieren
        LPSTR old = h;
        h = SkipFormat (h);
        lmemcpy (x,old,h - old);
        x += (h - old);
        }
      if (i == sPos) {
        inSelection = TRUE;
        lstrcpy (x,ntxt);
        x += lstrlen(x);
        }
      if (i == sPos + sLen) {
        inSelection = FALSE;
        }
      if (!*h) break ;
      if (!inSelection)
        *x++ = *h;
      h ++ ;
      i ++ ;
      }
    FreeGlobMem (Text);
    Text = LPSTR (GetGlobMem (lstrlen (nBuffer) + 1));
    lstrcpy (Text,nBuffer);
    FreeGlobMem (nBuffer);
    Reformat ();
    InvalidateFull (ErsteSeite + rSeite,TRUE);
    if (cfb != NULL)
      (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
    }
  }
