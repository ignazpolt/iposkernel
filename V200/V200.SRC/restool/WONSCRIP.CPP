////////////////////////////////////////////////////
//  Bearbeiten von Scripts
////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/wonscrip.cpv   1.94   26 Jun 2000 15:28:30   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/wonscrip.cpv  $
// 
//    Rev 1.94   26 Jun 2000 15:28:30   Wolfgang
// 1.) Auch Strings mit mehr als 80 Zeichen bringen Tooltip nicht zum Absturz.
// 
//    Rev 1.93   07 Jun 2000 11:51:42   Wolfgang
// 1.) Einbuchstabige Variablen auch mit Tooltip.
// 2.) Bei Tooltip auch Structnamen mitnehmen.
// 3.) Auch Leerstrings in den Tooltip.
// 
//    Rev 1.92   24 May 2000 13:50:30   Wolfgang
// 1.) ToolTips ausschaltbar.
// 
//    Rev 1.91   29 Sep 1999 16:55:46   Wolfgang
// 1.) Vor Generieren Init-/DoneModuleHash aufrufen.
// 
//    Rev 1.90   02 Jul 1999 11:24:26   Wolfgang
// 1.) answer mit IDYES vergleichen, nicht zuweisen!
// 
//    Rev 1.89   26 Apr 1999 18:12:00   Wolfgang
// 1.) Generieren mit Abhaengigkeiten von Modulen.
// 2.) Generieren von MAK-Files.
// 3.) Kein Extragenerieren der abhaengigen IDDs.
// 4.) In CheckError GetFName verwenden, damit Fenstersuche case-insensitiv ist.
// 5.) In CheckError Fehlerzeile auch bei neu geoeffneten Modulen setzen.
// 
// 
//    Rev 1.88   14 Apr 1999 18:14:24   Wolfgang
// 1.) iddError statt iddOk auch bei normalen Generieren mit Abhaengigkeiten.
// 
//    Rev 1.87   26 Mar 1999 18:14:44   Wolfgang
// 1.) Generieren mit Abhaengigkeiten mit Modulsortierung.
// 2.) Messages fuer Toggeln der Case-Sensitiven- und Wort-Suche verarbeiten.
// 3.) OnVKReturn braucht caseSensitive-Parameter.
// 4.) Message fuer Makefile-Generieren verarbeiten.
// 
//    Rev 1.86   24 Mar 1999 15:28:22   Wolfgang
// 1.) GetIncludeFileName vom Source-Pfad.
// 2.) In SaveFileEntry Child-Window auf NULL pruefen.
// 3.) SetCaretTo setzt bei ungueltiger Zeilennummer auf EOF.
// 
//    Rev 1.85   22 Mar 1999 17:24:02   Wolfgang
// 1.) In ShowScript ein SetCaretPos machen, damit Cursor am Textrand und nicht
//     ganz aussen steht.
// 
//    Rev 1.84   22 Mar 1999 14:25:34   Wolfgang
// 1.) Fehlenden replace-Parameter bei SearchIt eingefuegt.
// 
//    Rev 1.83   18 Mar 1999 16:52:28   Wolfgang
// 1.) Vertikales Scrolling auf letzter Seite funktioniert auch bei 
//     Fenstervergroesserung.
// 
//    Rev 1.82   18 Mar 1999 14:07:38   Wolfgang
// 1.) Angabe des Feldes bei SB_SETTEXT ueber Konstante.
// 2.) SaveFileEntry nur, wenn es auch einen Filenamen gibt.
// 
//    Rev 1.81   17 Mar 1999 19:24:22   Wolfgang
// 1.) In SaveAs File in Recent-File-List speichern.
// 2.) Save...Entry-Funktion speichert File entweder in Workspace- oder
//     Recent-File-List.
// 3.) SaveAll...Entrys speichert sich schliessendes File in Recent-File-List.
// 4.) SaveAll schreibt auch Recent-File-List.
// 5.) SaveAll arbeitet nur, wenn nicht gerade im Restore.
// 6.) Bei Oeffnen wird File nicht mehr in Recent-File-List eingetragen.
// 
//    Rev 1.80   16 Mar 1999 19:41:20   Wolfgang
// 1.) MainFile TRUE bei WorkSpace oeffnen.
// 
//    Rev 1.79   16 Mar 1999 17:07:18   Wolfgang
// 1.) SaveAllWorkSpaceEntrys neu und bei Speichern und Oeffnen verwendet.
// 
//    Rev 1.78   16 Mar 1999 16:12:52   Wolfgang
// 1.) Erweiterungen fuer Workspace.
// 2.) ShowScript mit NULL als ParentWindow fuer Anzeige eines neuen Fensters,
//     und Rueckgabe desselben, zur Vermeidung leerer Scriptfenster.
// 
//    Rev 1.77   15 Mar 1999 15:42:10   Wolfgang
// 1.) Bei FileClose Close- statt MDI-Destroy-Message schicken.
// 
//    Rev 1.76   15 Mar 1999 11:27:16   Wolfgang
// 1.) Aufruf und Implementierung von InitWordJump neu.
// 
//    Rev 1.75   12 Mar 1999 14:41:16   Wolfgang
// 1.) Nur auf letzten Fehler setzen, wenn nicht Abbruch durch Benutzer.
// 
//    Rev 1.73   11 Mar 1999 10:58:08   Wolfgang
// 1.) Scrolling bei preferLeft korrigiert.
// 
//    Rev 1.72   10 Mar 1999 19:46:42   Wolfgang
// 1.) hPosMax-Korrektur ausgebaut.
// 2.) xExtra und yExtra bei Vergleich beruecksichtigen.
// 3.) xExtraNeg, yExtraNeg und preferLeft neu, zwecks besserer 
//     Scrollpositionierung.
// 
//    Rev 1.71   09 Mar 1999 16:30:34   Wolfgang
// 1.) NeedNewCaption entfernt.
// 2.) SetCaption bei TextBlock neu und bei FileBlock nur noch als Aufruf davon.
// 
//    Rev 1.70   05 Mar 1999 19:21:02   Wolfgang
// 1.) Debuggen bis zur letzten Zeile. (In ShowProc V-Scrollen auf letzte 
//     Seite ermoeglichen)
// 
//    Rev 1.69   02 Nov 1998 11:49:38   Gerhold
// Syntax Coloring Verbesserungen
// 
//    Rev 1.68   29 Oct 1998 11:01:18   Gerhold
// Syntax Coloring verbessert
// 
//    Rev 1.65   14 Aug 1998 18:56:14   Hannes
// Include / Source Pfad wirklich trennen
// 
//    Rev 1.64   04 May 1998 11:18:34   Gerhold
// ReplaceCombo ... zusaetzlicher Parameter BOOL InsertEmptyString fuer INI
// 
//    Rev 1.63   22 Apr 1998 09:49:22   Gerhold
// Matchingbraces
// 
//    Rev 1.62   07 Jan 1998 15:33:34   Gerhold
// ifdef TOOLTIP hat noch gefehlt
// 
//    Rev 1.61   06 Jan 1998 19:59:34   Gerhold
// Die Tooltips zum Debuggen eingebaut
// 
//    Rev 1.60   02 Jan 1998 10:08:24   Gerhold
// 16 -> 32 Bit Fehlerkorrektur
// 
//    Rev 1.59   19 Nov 1997 18:44:26   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.58   05 Nov 1997 09:01:04   Gerhold
// 32 Bit
// 
//    Rev 1.57   05 Sep 1997 15:21:50   Hannes
// Beschleunigung des Schreibens
// 
//    Rev 1.56   28 Aug 1997 15:49:34   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.55   19 Feb 1997 12:15:54   Hannes
// Compilation von Modulen
// 
//    Rev 1.54   26 Nov 1996 08:10:08   HANNES
// Automatischer Update
// 
//    Rev 1.53   08 Nov 1996 13:30:48   HANNES
// QLong,Replikator
// 
//    Rev 1.52   28 Oct 1996 08:47:20   HANNES
// 
//    Rev 1.51   21 Oct 1996 18:57:04   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.50   25 Sep 1996 18:33:06   MARTIN
// es koennen jetzt 128 FILES_IN_PROJECT sein (+ WIN_ASSERT !)
// 
//    Rev 1.49   03 Sep 1996 09:58:38   HANNES
// Editor mit mehr Text
// 
//    Rev 1.48   23 Jul 1996 15:52:02   GERHOLD
// Verbesserung in MI_SEARCHMORE
// 
//    Rev 1.47   02 Jul 1996 15:59:50   GERHOLD
// SearchUp
// 
//    Rev 1.45   11 Mar 1996 16:35:18   GERHOLD
// GetExtension sucht jetzt von hinten nach vorne
// Der Pfad der Hilfedatei kommt aus der RESTOOL.INI
// 
//    Rev 1.44   19 Feb 1996 18:09:46   GERHOLD
// in ::AnalyseDefine.  Bei unbekannten #defines =>return FALSE statt WIN_ASSERT
// 
//    Rev 1.43   02 Feb 1996 10:51:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.42   07 Sep 1995 09:04:00   HANNES
// 
//    Rev 1.41   27 Aug 1995 13:00:26   HANNES
// 
//    Rev 1.40   24 Aug 1995 00:17:14   GERHOLD
// 
//    Rev 1.39   23 Aug 1995 11:02:42   GERHOLD
// 
//    Rev 1.38   31 Jul 1995 12:04:00   HANNES
// Kompilieren von DDD,IDD,GDD im Editor (noch ohne Inhaltsverzeichnisse)
// 
//    Rev 1.37   07 Jun 1995 12:17:06   GERHOLD
// Suchen und Ersetzen (COMMDLG), Bookmarks
// 
//    Rev 1.36   23 May 1995 12:03:14   GERHOLD
// GetEditorWindow ... prueft ob MDI-Child ein Script-Fenster ist.
// 
//    Rev 1.35   26 Apr 1995 15:26:58   HANNES
// 
//    Rev 1.34   24 Apr 1995 15:44:08   GERHOLD
// 
//    Rev 1.33   10 Apr 1995 10:45:24   GERHOLD
// 
//    Rev 1.32   29 Mar 1995 17:49:24   GERHOLD
// 
//    Rev 1.31   27 Mar 1995 10:40:42   GERHOLD
// Menus verbessert
// 
//    Rev 1.30   20 Mar 1995 08:44:54   HANNES
//  
// 
//    Rev 1.29   08 Mar 1995 09:13:28   GERHOLD
// 
//    Rev 1.28   24 Feb 1995 11:12:32   GERHOLD
// WM_SETCURSOR erweitert
// 
//    Rev 1.27   16 Feb 1995 12:41:44   GERHOLD
// 
//    Rev 1.26   29 Jan 1995 11:48:26   HANNES
// 
//    Rev 1.25   26 Jan 1995 12:24:32   GERHOLD
// Buttons enablen
// 
//    Rev 1.24   26 Jan 1995 10:27:18   HANNES
// 
//    Rev 1.23   24 Jan 1995 09:58:16   GERHOLD
// Menus hin Menus her
// 
//    Rev 1.22   18 Jan 1995 17:05:34   GERHOLD
// Wieder einmal ein parr Menu-Erweiterungen
// 
//    Rev 1.21   17 Jan 1995 15:52:30   Hannes
// Menue - Fehlerkorrektur
// 
//    Rev 1.20   13 Jan 1995 16:54:28   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.19   10 Jan 1995 15:01:10   HANNES
// 
//    Rev 1.18   09 Jan 1995 16:39:30   HANNES
// 
//    Rev 1.17   09 Jan 1995 12:17:24   HANNES
// Debugger eingebaut
// 
//    Rev 1.16   04 Jan 1995 13:40:54   HANNES
// 
//    Rev 1.15   03 Jan 1995 11:48:38   GERHOLD
// 
//    Rev 1.14   02 Jan 1995 18:33:22   HANNES
// 
//    Rev 1.13   02 Jan 1995 16:42:50   GERHOLD
// Font Update im Editor
// 
//    Rev 1.12   02 Jan 1995 12:20:34   HANNES
// 
//    Rev 1.11   02 Jan 1995 09:32:14   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.9   02 Nov 1994 20:28:22   GERHOLD
// CheckError ... actblock->TextMetrics()
// 
//    Rev 1.8   25 Oct 1994 11:52:54   GERHOLD
// TextLine::Paint erzeugt und fuer Syntax-Coloring vorbereitet
// 
//    Rev 1.7   10 Oct 1994 10:42:42   GERHOLD
// sehr viele grosse veraenderungen
// 
//    Rev 1.6   30 Sep 1994 14:39:50   GERHOLD
// Erweiterungen fuer die Zwischenablage
// 
//    Rev 1.5   14 Sep 1994 16:59:00   GERHOLD
// Erweiterungen fuer Statuszeile
// 
//    Rev 1.4   25 Jul 1994 09:38:50   GERHOLD
// Drag & Drop fuer Formate
// 
//    Rev 1.3   12 Jul 1994 18:16:06   HANNES
// 
//    Rev 1.2   12 Jul 1994 14:45:28   HANNES
// 
//    Rev 1.1   04 Jul 1994 14:06:30   HANNES
// Verbessertes Fehlerhandling
// 
//    Rev 1.0   24 Jun 1994 16:54:52   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>

#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "drdrop.hpp"
#include "wonscrip.hpp"
#define MODULENUM 104
#include "winass.hpp"

//#include "subclass.hpp"

#include "scripthd.hpp"

#include "rlist.hpp"
#include "commdlg.h"  // wird fuer MISC.HPP benoetigt
#include "misc.hpp"

#include "font.hpp"
#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "hlines.hpp"
#include "blandmdi.h"
#include "blandmdi.hpp"
#include "communic.hpp"
#include "scdb.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

#include "msdntb.h"
#include "statbar.hpp"

#ifdef TOOLTIP
  #define NOTOOLBAR
  #define NOSTATUSBAR
  #include <commctrl.h>
#endif

#define NEWSCROLLER


extern HINSTANCE MyInstance;

extern HWND hWndProjectList;
extern HWND hWndStatusBar;

extern LPSTR IniFile();


hash FAR *defHash;

//#define CB_TEXTBLOCKS 64

#define FILES_IN_PROJECT   128

class FAR FileBlock {
 public :
  LPTEXTBLOCK actblock;
  LPSTR       FileInProject[FILES_IN_PROJECT];
  BOOL        MainFile;     // ist das ein Haupt-Script?
  HCURSOR     RightCursor;

  BOOL        CaptureDone,TestDone;

  LPLINE      FirstSelectedLine;
  LPLINE      LastSelectedLine;
  LPLINE      FirstDialogLine;
  LPLINE      LastDialogLine;
  LPLINE      l1;

  ScDebugInfo FAR *dbinf;
  FileBlock (GLOBALHANDLE hGtxt);
  FileBlock (LPSTR fname);
  ~FileBlock ();

  void ActivateList ();
  void CheckDrop (HWND hWnd,int x,int h,WORD Type,BOOL last, LPSTR SelWord);
  void SetCaretTo (HWND hWnd,int el,int ec,BOOL doCenter = FALSE);
  void CheckError (HWND hWnd,LPSTR eName,int el,int ec);
  void CheckError (HWND hWnd);
  void CreateDefHash ();
  void CreateIncludes (HWND hWnd);
  void AddToList (HWND hWndList,LPSTR fName,int FAR &j);
  void GetInvalidRect (HWND hWnd,LPLINE f,LPLINE l,LPRECT r);
  void GetDialogSelection ();
  void InsertBsp (HWND hWnd);
  void InvalidateSelected (HWND hWnd,LPLINE f,LPLINE l);
  BOOL IsModifyDone ();
  void Paint (HWND hWnd, HDC hDC, RECT rcPaint);
  void SetActiveBuffer (HWND hWnd,WORD BlockNr);
  void SetCaption (HWND hWnd);
  void StoreFiles (HWND hWnd);
  void StoreFilesUnder (HWND hWnd);
  void TestMPos (HWND hWnd,int y);
  LPSTR ActiveWord();

  LPVOID operator new (size_t size)
    { 
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };


inline int FAR PASCAL GetXMin ()
  {
  return XMIN;
  }

/////////////////////////////////////////////////////////////////
//
//  Implementierung der Klasse Textblock
//
/////////////////////////////////////////////////////////////////
inline int iAbs(int dx)
  {
  return (dx < 0) ? - dx : dx ;
  }
  
void NeedViewFor (HWND hWnd,LPTEXTBLOCK b,int FAR *x,LONG FAR *y,LONG ya,int xExtra,int yExtra,int xExtraNeg,int yExtraNeg,BOOL preferLeft)
  {
  // Rechteck (*x - xExtraNeg, *y - yExtraNeg) (*x + xExtra, *y + yExtra) soll angezeigt werden und
  // das Caret auf (*x, *y) positioniert werden.
  // *x und *y sind dabei in Fensterkoordinaten
  RECT r;
  GetClientRect (hWnd,&r);
  r.bottom -= b->charHeight;
  int xl = *x + b->x0;            // xl = Absolute X-Position in Text in Fensterkoordinaten
  int yl = *y + ya;               // yl = Absolute Y-Position in Text in Fensterkoordinaten
  int setHPos = -1;               // Zu setzende horizontale Position in Chars
  int setVPos = -1;               // Zu setzende vertikale Position in Chars
  BOOL fullLeftPossible = FALSE;  // Positionierung ganz links moeglich

  if (xExtra == 0)
    xExtra = b->charWidth; // Ein Zeichen links vom Cursor, wollen wir immer noch sehen
  BOOL mustScroll = ((*x - xExtraNeg < (GetXMin())) || (*x + xExtra > r.right));
  if (preferLeft || mustScroll) {
    int xl = *x + b->x0;                           // xl = Absolute Position in Text
    int hPos = b->x0 / b->charWidth;               // hPos = Aktuelle linke Spalte der Anzeige
    // hPosMax = maximal moegliche linke Spalte fuer richtige Anzeige, d.h. Anzeige am linken Rand
    int hPosMax = (xl - xExtraNeg - GetXMin()) / b->charWidth;
    // hPosMin = minimal moegliche linke Spalte fuer richtige Anzeige, d.h. Anzeige am rechten Rand
    int hPosMin = (xl + xExtra - r.right + b->charWidth - 1) / b->charWidth;
    hPosMax = min(b->hmax,(max(hPosMax,0)));       // Auf ueberhaupt moegliche Spalten beschraenken
    hPosMin = min(b->hmax,(max(hPosMin,0)));       // Auf ueberhaupt moegliche Spalten beschraenken
    int dMax = iAbs (hPos - hPosMax);              // Zu Scrollen bei Anzeige am linken Rand
    int dMin = iAbs (hPos - hPosMin);              // Zu Scrollen bei Anzeige am rechten Rand

    if (hPosMin == 0)
      fullLeftPossible = TRUE;
    if (mustScroll) {
      if (dMax < dMin) {
        setHPos = hPosMax;
        }
      else {
        setHPos = hPosMin;
        }
      }
    }
  if ((*y - yExtraNeg < LONG (r.top)) || (*y + yExtra >= LONG(r.bottom))) {   // y ... Position im Fenster
    if (*y == 0)
      return;
    LONG yl      = *y + ya;                  // Gesamthoehe des Textes
    int vPos    = b->GetAbsoluteLineNmbr(b->FirstVisibleLine);  // Zeilennnr. erste Zeile
                                         
    int vPosMax = int ((yl - yExtraNeg) / LONG (b->charHeight));
    int vPosMin = int ((yl + yExtra - r.bottom + b->charHeight) / LONG (b->charHeight));
/*
    int vPosMax = int ((yl - yExtra) / LONG (b->charHeight));
    int vPosMin = int ((yl - yExtra + r.bottom + b->charHeight) / LONG (b->charHeight));
*/
    vPosMax = min(b->vmax,(max(vPosMax,0)));
    vPosMin = min(b->vmax,(max(vPosMin,0)));
    int dMax = iAbs (vPos - vPosMax);
    int dMin = iAbs (vPos - vPosMin);

    if (dMax < dMin)
      setVPos = vPosMax;
    else
      setVPos = vPosMin;
    }
  if (preferLeft && fullLeftPossible && ((setHPos != -1) || (setVPos != -1)))
    // Falls gewuenscht und moeglich Anzeige ganz nach links ruecken,
    // aber nur wenn ohnehin irgendwie gescrollt wird.
    setHPos = 0;
  if (setHPos != -1) {
#ifdef WIN32
    SendMessage (hWnd,WM_HSCROLL,MAKEWPARAM(SB_THUMBPOSITION, setHPos), NULL);
#else
    SendMessage (hWnd,WM_HSCROLL,SB_THUMBPOSITION,MAKELPARAM(setHPos,0));
#endif
    *x = xl - b->x0 ;
    b->GetNewCaretPos ();
    }
  if (setVPos != -1) {
#ifdef WIN32
    SendMessage (hWnd,WM_VSCROLL,MAKEWPARAM(SB_THUMBPOSITION, setVPos), NULL);
#else
    SendMessage (hWnd,WM_VSCROLL,SB_THUMBPOSITION,MAKELPARAM(setVPos,0));
#endif
    *y = yl - b->GetFirstVisibleLinePos();
    b->GetNewCaretPos ();
    }
  }

TextBlock::TextBlock (GLOBALHANDLE hGmem)
  {
  LPSTR Buffer = (LPSTR)GlobalLock (hGmem);
  for (LPSTR h = Buffer ; *h ; h = PushLine (h)) ;

#ifdef ANALYSELINE
//  StartLineForAnalyse = FirstVisibleLine;
  AnalyseLines (NULL, NULL, TRUE);
#endif
  InitWordJump ();
  }

TextBlock::TextBlock (LPSTR fname)
  {
  if (fname != NULL) {
    OFSTRUCT Ofs;
    int fi = OpenFile (fname,&Ofs,OF_READ);
    fName = LPSTR(GetGlobMem (lstrlen(fname)+1));
    lstrcpy (fName,fname);
    if (fi >= 0) {
      DWORD len = _llseek (fi,0L,2);    // Datei-Zeiger an das Ende der Datei
      GLOBALHANDLE hGmem = GlobalAlloc (GHND /*GMEM_MOVEABLE*/, len+1);
      LPSTR Buffer = (LPSTR)GlobalLock (hGmem);
      _llseek (fi,0L,0);                // Datei-Zeiger an den Anfang der Datei
      _hread (fi,Buffer,len);
      ((char huge *) Buffer)[len] = '\0';
      // extrahiere aus dem Buffer die einzelnen Saetze fuer den Textblock
      for (LPSTR h = Buffer ; *h ; h = PushLine (h)) ;
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      _lclose (fi);
      }
    }
  else {
    PushLine ("");
    }

  AlreadySelected = FALSE;
  StartSel.Col = 0;
  StartSel.Row = 0;
  EndSel.Col = 0;
  EndSel.Row = 0;
  SelWord = NULL;
  ErrorLine = NULL;
#ifdef TOOLTIP
  hWndToolTip = NULL;
#endif

#ifdef ANALYSELINE
//  StartLineForAnalyse = FirstVisibleLine;
  AnalyseLines (NULL, NULL, TRUE);
#endif
  InitWordJump ();
  }

TextBlock::~TextBlock ()
  {
  if (fName != NULL)
    FreeGlobMem (fName);

  for (LPLINE h = FirstLine ; h != NULL ; ) {
#ifdef ANALYSELINE
    h->ClearQuota ();
    h->ClearComment ();
#endif

#ifdef ANALYSEKEYWORD
    h->ClearKeyWord ();
#endif

    LPLINE n = h->Next;
    FreeGlobMem (h->Text);
    FreeGlobMem (h);
    h = n;
    }

  if (SelWord != NULL)
    FreeGlobMem (SelWord);

#ifdef TOOLTIP
  if (hWndToolTip)
    DestroyWindow (hWndToolTip);
#endif
  }

void TextBlock::InitWordJump () 

  {
  GetPrivateProfileString ("EDITOR", "ExtraWordChars", "_", extraWordChars, sizeof(extraWordChars), IniFile());
  char valueStr[20];
  GetPrivateProfileString ("EDITOR", "WordStopFlags", "0", valueStr, sizeof(valueStr), IniFile());
  sscanf (valueStr, "%li", &wordStopFlags);
  }

LPLINE TextBlock::DelLine (LPLINE h, LPLINE FAR *last = NULL)
  {
  if (h == NULL) return h ;

#ifdef ANALYSELINE
  h->ClearQuota ();
  h->ClearComment ();
#endif

#ifdef ANALYSEKEYWORD
  h->ClearKeyWord ();
#endif

  if ((h->Next == NULL) && (h->Prev == NULL)) {
    FreeGlobMem (h->Text);

    h->Text = LPSTR(GetGlobMem (1));
    return h ;
    }
  else {

    FreeGlobMem (h->Text);
    if (h->Next != NULL)        // diese Zeile als Vorgaenger ausklammern
      h->Next->Prev = h->Prev;
    else
      LastLine      = h->Prev;

    if (h->Prev != NULL)        // diese Zeile als Nachfolger ausklammern
      h->Prev->Next = h->Next;
    else
      FirstLine     = h->Next;

    if ((last != NULL) && (*last == h)) 
      *last = h->Prev;
  
    LPLINE n = (h->Next != NULL) ? h->Next : h->Prev ;
    if (FirstVisibleLine == h) FirstVisibleLine = (n != NULL) ? n : FirstLine ;
    if (LastVisibleLine == h) LastVisibleLine = (n != NULL) ? n : FirstLine ;
    if (LastLineAnalyzed == h) LastLineAnalyzed = h->Prev ;
    FreeGlobMem (h);
    return n;                   // gibt die naechste Zeile zurueck
    }
  }


//-------------------------------------------------------------------------
// Rueckgabewert: Zeilen-Nr. der ersten sichtbaren Zeile im gesamten Text
//-------------------------------------------------------------------------
int TextBlock::GetAbsoluteLineNmbr (LPLINE l)
  {
  int res = 0 ;
  for (LPLINE h = FirstLine ; ((h != NULL) && (h != l)) ; h = h->Next , res ++ ) ;
  return res ;
  }

//-------------------------------------------------------------------------
// Rueckgabewert: Y-Position der ersten sichtbaren Zeile im gesamten Text
//-------------------------------------------------------------------------
LONG TextBlock::GetFirstVisibleLinePos ()
  {
  LONG y = 0;
  for (LPLINE h = FirstLine ; ((h != NULL) && (h != FirstVisibleLine)) ; h = h->Next , y += charHeight ) ;
  return y ;
  }

LPLINE TextBlock::GetLineFromLineNr (int LineNr)
  {
  int i = 0 ;
  for (LPLINE h = FirstLine ; ((h != NULL) && (i < LineNr)) ; h = h->Next , i ++ ) ;
  return h;
  }

//-------------------------------------------------------------------------
// Berechnet die maximale Hoehe und die maximale Breite des Textes in Pixel
//-------------------------------------------------------------------------
void TextBlock::GetMinMax ()
  {
  GesHeight = 0L;
  GesWidth  = XMIN + 300 * charWidth;
  for (LPLINE h = FirstLine ; h != NULL ; h = h->Next) {
    int aWidth = charWidth * lstrlen (h->Text) + XMIN;
    if (aWidth > GesWidth) GesWidth = aWidth ;
    GesHeight   += charHeight;
    }
  }


#define STATE_INIT      0
#define STATE_SEL       1
#define STATE_LASTSEL   2
#define STATE_END       3

int TextBlock::GetNextState (int state,LPLINE h,LPLINE f,LPLINE l)
  {
  switch (state) {
    case STATE_INIT :
      if (h == f) state = STATE_SEL ;
      if (h == l) state = STATE_LASTSEL ;
      break ;
    case STATE_SEL :
      if (h == l) state = STATE_LASTSEL ;
      break ;
    case STATE_LASTSEL :
      state = STATE_END ;
      break ;
    }
  return state;
  }


int TextBlock::GetState (LPLINE h, LPLINE f, LPLINE l)
  {
  int state = STATE_INIT;
  if (h == NULL) return state;
  for (LPLINE x = FirstLine ; x != NULL ; x = x->Next) {
    state = GetNextState (state,x,f,l);
    if (x == h) break ;
    }
  return state;
  }


void TextBlock::GetSelRange (int FAR *ystart,int FAR *yend,LPLINE firstLine,LPLINE lastLine)
  {
  *ystart = *yend = -1;
  int state = GetState (FirstVisibleLine->Prev,firstLine,lastLine);
  int y = 0;
  for (LPLINE h = FirstVisibleLine ; ((h != NULL) && (state != STATE_END)) ; h = h->Next) {
    state = GetNextState (state,h,firstLine,lastLine);
    switch (state) {
      case STATE_SEL :
        if (*ystart < 0) *ystart = y ;
        break ;
      case STATE_LASTSEL :
        if (*ystart < 0) *ystart = y ;
        *yend = y + charHeight + 1;
        break ;
      }
    y += charHeight;
    }
  }

//--------------------  TextBlock::GotoBookMark  ----------------------------
//
//---------------------------------------------------------------------------
void TextBlock::GotoBookMark (WORD wP)
  {
  // von der aktuellen Zeile bis zum naechsten BookMark oder bis Ende des Textes suchen
  LPLINE h;
  for (h = LineWithCaret->Next; ((h != NULL) && (!h->IsBookMarkLine())); h = h->Next);
  
  // das Ende des Textes wurde erreicht => vom Anfang bis zur aktuellen Zeile suchen
  if (h == NULL) {
    for (h = FirstLine; ((h != LineWithCaret) && (!h->IsBookMarkLine()) && (h != NULL)); h = h->Next);
    }

  if ((h != NULL) && h->IsBookMarkLine()) {
    iCaret = 0;
    LineWithCaret = h;
    SetNewCPos (MyWnd);
    }
  else
    MessageBeep (0);  
  }

void TextBlock::InsertLine (LPSTR Text)
  {
  LPLINE n = LPLINE (GetGlobMem (sizeof (*n)));
  n->Text = Text;
  n->Next = NULL;
  n->Prev = LastLine;
  n->Style = 0;

#ifdef ANALYSELINE
  n->Comment = NULL;
  n->Quota = NULL;
#endif

#ifdef ANALYSEKEYWORD
  n->KeyWord = NULL;
#endif

  if (FirstLine == NULL) FirstLine = n;
  if (LastLine != NULL)  LastLine->Next = n;
  LastLine = n;
  if (FirstVisibleLine == NULL)   FirstVisibleLine = n;
  }

//-------------------------  InsertLineBehind  ------------------------------
//
// fuegt nach der Zeile <line> eine neue Zeile mit dem Inhalt <txt> an.
//---------------------------------------------------------------------------
LPLINE TextBlock::InsertLineBehind (LPLINE line, LPSTR txt)
  {

  LPLINE n = LPLINE (GetGlobMem (sizeof(*n)));
  n->Text = LPSTR (GetGlobMem (lstrlen (txt) + 1));
/*  
  // Anzahl der Leerzeichen in der Vorgaengerzeile ermitteln
  int i = 0;
  if (line != NULL)
    for ( ; line->Text[i] == ' '; i++);

  // der Text wird also wie die Zeile davor eingerueckt
  n->Text = LPSTR (GetGlobMem (lstrlen (txt) + 1 + i));
  for (int j = 0 ; j < i; n->Text[j++] = ' ');
  for ( ; txt[j-i] != '\0'; n->Text[j] = txt[j-i], j++);
  n->Text[j] = '\0';
*/  

  lstrcpy (n->Text,txt);
  if (line != NULL) {
    n->Next = line->Next;
    if (line->Next != NULL) line->Next->Prev = n;
    else                    LastLine = n;
    n->Prev    = line;
    line->Next = n;
    }
  else {
    n->Next = FirstLine ;
    if (FirstLine != NULL) FirstLine->Prev = n;
    else                   LastLine = n;
    FirstLine = n;
    }

  n->Style = 0;

#ifdef ANALYSELINE
  n->Comment = NULL;
  n->Quota = NULL;
#endif

#ifdef ANALYSEKEYWORD
  n->KeyWord = NULL;
#endif

  SetScrollers (MyWnd);
  return n;
  }

LPLINE TextBlock::InsertLineBefore (LPLINE line,LPSTR txt)
  {
  LPLINE n = LPLINE (GetGlobMem (sizeof(*n)));   // Speicher fuer Klasse anfordern
  n->Text = LPSTR (GetGlobMem (lstrlen (txt) + 1));  // Speicher fuer Text
  lstrcpy (n->Text,txt);
  if (line != NULL) {
    n->Next = line;
    if (line->Prev != NULL) 
      line->Prev->Next = n;
    else
      FirstLine = n;
    n->Prev    = line->Prev;
    line->Prev = n;
    }
  else {
    n->Prev = LastLine ;
    n->Next = NULL;
    if (LastLine != NULL)  LastLine->Prev = n;
    else                   FirstLine = n;
    LastLine = n;
    }

  n->Style = 0;

#ifdef ANALYSELINE
  n->Quota = NULL;
  n->Comment = NULL;
#endif

#ifdef ANALYSEKEYWORD
  n->KeyWord = NULL;
#endif

  SetScrollers (MyWnd);
  return n;
  }

//----------------------------------------------------------------------------
// Funktion: TextBlock::GetSelectionFromTopToBottom
//
// Zweck: stellt in den variablen Parametern sicher, dass die Selektion von 
//        oben nach unten und von links nach rechts ausgeführt wird.
//----------------------------------------------------------------------------
void TextBlock::GetSelectionFromTopToBottom (LPSELSTRUCT SelStart, LPSELSTRUCT SelEnd)
  {
  if (StartSel.Row == EndSel.Row) {     // Selektion in der selben Zeile?
    if (StartSel.Col > EndSel.Col) {
      *SelStart = EndSel;
      *SelEnd   = StartSel;
      }
    else {  
      *SelStart = StartSel;
      *SelEnd = EndSel;
      }
    return;
    }  
  
  if (StartSel.Row > EndSel.Row) {
    *SelStart = EndSel;
    *SelEnd   = StartSel;
    } 
  else {
    *SelStart = StartSel;
    *SelEnd = EndSel;
    }
  }
  
//-----------------------  TextBlock::Paint  --------------------------------
//
//
//---------------------------------------------------------------------------
#define LC_BREAKPOINT     1
#define LC_ACTIVE         2
#define LC_BOOKMARK       4
#define LC_ERROR          8
#define LC_BRACE         16 

COLORREF SELECTION_FORECOLOR, SELECTION_BACKCOLOR;
COLORREF BREAKPOINT_FORECOLOR, BREAKPOINT_BACKCOLOR;
COLORREF ACTIVE_FORECOLOR, ACTIVE_BACKCOLOR;
COLORREF BOOKMARK_FORECOLOR, BOOKMARK_BACKCOLOR;
COLORREF ERROR_FORECOLOR, ERROR_BACKCOLOR;
COLORREF BRACE_FORECOLOR, BRACE_BACKCOLOR;
COLORREF STRING_FORECOLOR, COMMENT_FORECOLOR, KEYWORD_FORECOLOR;

//#define BREAKPOINT_BACKCOLOR   (RGB(0x80,0x00,0x00))
//#define BREAKPOINT_FORECOLOR   (RGB(0xFF,0xFF,0xFF))
//#define ACTIVE_BACKCOLOR       (RGB(0xFF,0xFF,0x00))
//#define ACTIVE_FORECOLOR       (RGB(0x00,0x00,0x00))
//#define BOOKMARK_BACKCOLOR     (RGB(0x00,0x80,0x80))
//#define BOOKMARK_FORECOLOR     (RGB(0x00,0x00,0x00))
//#define ERROR_FORECOLOR        (RGB(0xFF,0xFF,0xFF))
//#define ERROR_BACKCOLOR        (RGB(0x00,0x00,0x80))
//#define BRACE_FORECOLOR        (RGB(0xFF,0x00,0x00))
//#define SELECTION_BACKCOLOR    (RGB(0x00,0x00,0x00))
//#define SELECTION_FORECOLOR    (RGB(0xFF,0xFF,0xFF))

void TextBlock::Paint (HWND hWnd, HDC hDC,LPLINE firstLine,LPLINE lastLine, RECT rcPaint)
  {
  HFONT hOld = (HFONT)SelectObject (hDC, hFontEdit);

  TEXTMETRIC tm;  
  RECT rcClient, rcInvert, rcLine;

  SelStruct SelStart, SelEnd;

  GetSelectionFromTopToBottom (&SelStart, &SelEnd);
    
  COLORREF OldBack = SetBkColor (hDC, RGB(0xFF, 0xFF, 0xFF));
  COLORREF OldTextColor = SetTextColor (hDC, 0L);

  // Zeilennummer innerhalb des gesamten Textbuffers
  int yStart = GetAbsoluteLineNmbr(FirstVisibleLine);
  GetClientRect (hWnd, &rcClient);
  GetTextMetrics (hDC,&tm);
  int x = XMIN;
  LONG y = 0;
  SetTextAlign (hDC,TA_LEFT | TA_TOP) ;

  BOOL bLastVisibleLineFound = FALSE;
  BOOL bDoAnalyse = FALSE;
  int yActLine = yStart + 1;
  for (LPLINE h = FirstVisibleLine ; h != NULL ; h = h->Next , yActLine ++) {

    if (y <= rcClient.bottom) {
      BOOL doBreak = FALSE, doActive = FALSE, doBookMark = FALSE, doError = FALSE ;
      BOOL doBrace = FALSE;
      if ((fName != NULL) && (IsBreakLine (yActLine,fName))) {
        doBreak = TRUE ;
        }
      if ((fName != NULL) && (IsActiveBreakLine (yActLine,fName))) {
        doActive = TRUE ;
        }
      if (h->IsBookMarkLine()) {
        doBookMark = TRUE;
        }
      if (h->IsErrorLine()) {
        doError = TRUE;
        }
      if (h->IsStartBrace() || h->IsEndBrace()) {
        doBrace = TRUE;
        }
      // Rechteck in dem die Zeile geschrieben wird
      SetRect (&rcLine, XMIN, int (y), rcClient.right, int (y+charHeight));
      // schneiden sich beide Bereich dann passiert was
      if (IntersectRect(&rcLine, &rcPaint, &rcLine)) {

        int linecolor = 0 ;
        if (doBreak)    linecolor |= LC_BREAKPOINT ;
        if (doActive)   linecolor |= LC_ACTIVE ;
        if (doBookMark) linecolor |= LC_BOOKMARK;
        if (doError)    linecolor |= LC_ERROR;

        if (linecolor & LC_ACTIVE) {
          SetBkColor (hDC, ACTIVE_BACKCOLOR);
          SetTextColor (hDC, ACTIVE_FORECOLOR);
          }
        else if (linecolor & LC_BREAKPOINT) {
          SetBkColor (hDC, BREAKPOINT_BACKCOLOR);
          SetTextColor (hDC, BREAKPOINT_FORECOLOR);
          }
        else if (linecolor & LC_BOOKMARK) {
          SetBkColor (hDC, BOOKMARK_BACKCOLOR);
          SetTextColor (hDC, BOOKMARK_FORECOLOR);
          }
        else if (linecolor & LC_ERROR) {
          SetBkColor (hDC, ERROR_BACKCOLOR);
          SetTextColor (hDC, ERROR_FORECOLOR);
          }
        else {
          SetBkColor (hDC, RGB(0xFF,0xFF,0xFF));
          SetTextColor (hDC, 0L);
          }

        // Syntax-Coloring nur bei normal gezeichneten Texten (kein Debug, keine Selektion)

        if ((AlreadySelected)) {
          if (((y / charHeight) >= SelStart.Row-yStart) && 
              ((y / charHeight) <= SelEnd.Row-yStart)) {

            rcInvert.left = GetXMin();
            rcInvert.right = rcClient.right;
            rcInvert.top = int (y);
            rcInvert.bottom = int (y+charHeight);
    
            BOOL bColoring = FALSE;
            if (h == SelStart.Line) {
              rcInvert.left = GetXMin()+SelStart.Col*charWidth-x0;
              bColoring = TRUE;
              }
    
            if (h == SelEnd.Line) {
              rcInvert.right = GetXMin()+SelEnd.Col*charWidth-x0;
              bColoring = TRUE;
              }
    
            h->Paint (hDC, x - x0, int (y), &rcLine, bColoring && !linecolor, this);
  
            if (linecolor == 0) {
              SetBkColor (hDC, SELECTION_BACKCOLOR);
              SetTextColor (hDC, SELECTION_FORECOLOR);
              h->Paint (hDC, x - x0, int (y), &rcInvert, FALSE, this);
              }
            }
          else
            h->Paint (hDC, x - x0, int (y), &rcLine, !linecolor, this);
          }  // if (AlreadySelected)
        else {
          h->Paint (hDC, x - x0, int (y), &rcLine, !linecolor, this);

          if (doBrace) {
            BOOL bBraceInLine = FALSE;

            SetBkColor (hDC, BRACE_BACKCOLOR);
            SetTextColor (hDC, BRACE_FORECOLOR);
            if (h->IsStartBrace() && h->IsEndBrace())
              bBraceInLine = TRUE;

            short bcol = h->IsStartBrace() ? StartBrace.Col : EndBrace.Col;
            rcLine.left = GetXMin() + bcol * charWidth - x0;
            rcLine.right = GetXMin() + (bcol + 1) * charWidth - x0;
            h->Paint (hDC, x - x0, int (y), &rcLine, FALSE, this);

            if (bBraceInLine) {
              bcol = EndBrace.Col;
              rcLine.left = GetXMin() + bcol * charWidth - x0;
              rcLine.right = GetXMin() + (bcol + 1) * charWidth - x0;
              h->Paint (hDC, x - x0, int (y), &rcLine, FALSE, this);
              }
            }
          }
      
        }
      }
    else if (!bLastVisibleLineFound) {
      bLastVisibleLineFound = TRUE;
      LastVisibleLine = h;
//      yLastVisibleLine = yActLine - 3;
      }

    y += tm.tmHeight;
    }  // for 

  if (!bLastVisibleLineFound)
    LastVisibleLine = LastLine;

  //----------------------------------------------------------------
  // Ist der Text kuerzer als das angezeigte Fenster, wird der Rest
  // des Fensters geloescht
  //----------------------------------------------------------------
  if (y < LONG(rcClient.bottom)) {
    // Am unteren Ende loeschen
    HBRUSH oldBrush = (HBRUSH)SelectObject (hDC,GetStockObject (WHITE_BRUSH));
    HPEN oldPen = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN));
    Rectangle (hDC,rcClient.left,int (y),rcClient.right,rcClient.bottom);
    SelectObject (hDC,oldPen);
    SelectObject (hDC,oldBrush);
    }

  SetTextColor (hDC, OldTextColor);
  SetBkColor (hDC, OldBack);
  SelectObject (hDC,hOld);
  }

//----------------------------------------------------------------------------
LPSTR TextBlock::PushLine (LPSTR start)
  {
  char huge *h = (char huge *) start;
  // Suchen bis '\0' oder CR-LF
  for ( ; ((*h) && (*h != '\r') && (*h != '\n')) ; h ++ ) {
    if (*h == '\t') *h = ' ';
    }
  int len = int (h - (char huge *) start + 1);  // Laenge dieses Satzes
  LPSTR Text = LPSTR (GetGlobMem (len));
  if (len > 1)
    hmemcpy (Text,start,len-1);  // kopiert "len-1" Zeichen vom Buffer
  Text[len-1] = '\0';
  InsertLine (Text);             // Text an den Textblock anhaengen
  if (*h == '\r') h++;           // CR-LF uebergehen
  if (*h == '\n') h++;
  return h;                      // Adresse des naechsten Satzes
  }

//----------------------------------------------------------------------------
void TextBlock::SetActLine (int vPos)
  {
  int i = 0 ;
  for (LPLINE h = FirstLine ; ((h != NULL) && (i < vPos)) ; h = h->Next , i ++ ) ;
  if (h != NULL) FirstVisibleLine = h;
  }

//----------------------------------------------------------------------------
void TextBlock::SetModified ()
  {
  ModifyDone = TRUE ;
  }

//----------------------------------------------------------------------------
void TextBlock::SetScrollers (HWND hWnd)
  {
  SCROLLINFO si;

  TextMetrics ();
  GetMinMax ();
  RECT cr;
  GetClientRect (hWnd,&cr);
  cr.bottom -= GetSystemMetrics (SM_CYHSCROLL);
  cr.right  -= GetSystemMetrics (SM_CXVSCROLL);
#ifdef NEWSCROLLER
  vmax = int (GesHeight / LONG (charHeight));
#else
  vmax = int ((GesHeight - LONG(cr.bottom)) / LONG (charHeight)) + 1;
#endif
  hmax = (GesWidth  - cr.right ) / charWidth + 1;
  if (vmax < ovmax) vmax = ovmax ;
  if (hmax < ohmax) hmax = ohmax ;

#ifdef NEWSCROLLER
  si.cbSize = sizeof(si);
  si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
  si.nMin   = 0;
  si.nMax   = vmax;
  si.nPage  = (cr.bottom / charHeight) + 1;
#endif

  if (vmax > 0) {
    int vPos = GetAbsoluteLineNmbr (FirstVisibleLine);
#ifdef NEWSCROLLER
    vPos = min(vPos, vmax);
    si.nPos   = vPos;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
#else
    SetScrollRange (hWnd,SB_VERT,0,vmax,TRUE);
#endif
    if (vPos > vmax) {
      vPos = vmax;
      SetActLine (vPos);

#ifndef NEWSCROLLER
      SetScrollPos (hWnd,SB_VERT,vPos,TRUE);
#endif
      }
    ovmax = vmax ;
    }
  else {
#ifdef NEWSCROLLER
    si.nPos   = 0;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
#else
    SetScrollRange (hWnd,SB_VERT,0,0,TRUE);
#endif
    FirstVisibleLine = FirstLine;
    }
  if (hmax > 0) {
    SetScrollRange (hWnd,SB_HORZ,0,hmax,TRUE);
    int hPos = x0 / charWidth ;
    if (hPos > hmax) {
      hPos = hmax;
      SetScrollPos (hWnd,SB_HORZ,hPos,TRUE);
      x0 = hPos * charWidth ;
      }
    ohmax = hmax ;
    }
  else {
    SetScrollRange (hWnd,SB_HORZ,0,0,TRUE);
    x0 = 0;
    }
  }


GLOBALHANDLE PutToHandle (GLOBALHANDLE hGmem,DWORD FAR *Size,LPSTR String)
  {
  LPSTR Buffer;
  if (hGmem) {
    Buffer = (LPSTR)GlobalLock (hGmem);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof(char));
    Buffer = (LPSTR)GlobalLock (hGmem);
    *Buffer = '\0';
    }
  GlobalUnlock (hGmem);
  hGmem = GlobalReAlloc (hGmem,*Size + lstrlen(String) + 1,GHND);
  Buffer = (LPSTR)GlobalLock (hGmem);
  hmemcpy ((char _huge *) Buffer + *Size,String,lstrlen(String));
  *Size += lstrlen(String);
  ((char _huge *) Buffer)[*Size] = '\0';
  GlobalUnlock (hGmem);
  return hGmem;
  }

GLOBALHANDLE TextBlock::StoreToHandle (HWND hWnd)
  {
  GLOBALHANDLE hGres = 0;
  DWORD gSize = 0L;
  for (LPLINE l = FirstLine ; (l != NULL) ; l = l->Next) {
    hGres = PutToHandle (hGres,&gSize,l->Text);
    hGres = PutToHandle (hGres,&gSize,"\r\n");
    }
  return hGres;
  }

GLOBALHANDLE hGBuff;
LPSTR GBuffer;
DWORD BuffSize;
#define HGSIZE      0x8000

extern void RemoveSpaces (LPSTR h);

void StartWrite ()
  {
  hGBuff = GlobalAlloc (GHND /*GMEM_MOVEABLE*/ ,HGSIZE);
  GBuffer = LPSTR (GlobalLock (hGBuff));
  BuffSize = 0L;
  }
int WriteToBuff (HFILE fi,LPSTR Buff,DWORD Size)
  {
  int fault = 0 ;
  WIN_ASSERT (Size < HGSIZE);
  if (BuffSize + Size > HGSIZE) {
    fault = (_lwrite (fi,GBuffer,WORD(BuffSize)) != BuffSize);
    BuffSize = 0L ;
    }
  hmemcpy (GBuffer + BuffSize,Buff,Size);
  BuffSize += Size ;

  return fault;
  }

void EndWrite (HFILE fi)
  {
  if (BuffSize > 0L) {
    _lwrite (fi,GBuffer,WORD (BuffSize));
    }
  GlobalUnlock (hGBuff);
  GlobalFree (hGBuff);
  BuffSize = 0L;
  }
void TextBlock::Store (HWND hWnd)
  {
  OFSTRUCT Ofs;
  if (fName == NULL) return ;
  int fi = OpenFile (fName,&Ofs,OF_CREATE | OF_WRITE);
  BOOL fault = FALSE ;
  if (fi >= 0) {
    StartWrite();
    for (LPLINE l = FirstLine ; ((l != NULL) && (!fault)) ; l = l->Next) {
      RemoveSpaces (l->Text);              // Der Dreck gehoert weg

      WORD size = lstrlen (l->Text);   // Text ohne '\0'

      // WORD size = GetBlockSize(l->Text)-1;
      // fault = (_lwrite (fi,l->Text,size) != size);
      // fault = (_lwrite (fi,"\r\n",2) != 2);

      fault = WriteToBuff (fi,l->Text,size);
      fault = WriteToBuff (fi,"\r\n",2);
      }
    EndWrite (fi);
    _lclose (fi);
    }
  else
    fault = TRUE ;
  ModifyDone = fault ;
  if (ModifyDone) {
    char outtxt[128];
    wsprintf (outtxt,"Fehler beim Schreiben von %s",fName);
    MessageBox (hWnd,outtxt,"Fehler",MB_OK | MB_ICONEXCLAMATION);
    }
  }

//-------------------------------------------------------------------------
// ueberprueft ob die Zeile f vor der Zeile l im Text-Buffer enthalten ist
//-------------------------------------------------------------------------
BOOL TextBlock::TestLines (LPLINE f, LPLINE l)
  {
  BOOL fFound = FALSE, lFound = FALSE;
  for (LPLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if (!fFound)                
      if (h == f)      // f gefunden?
        fFound = TRUE ;
    if ((fFound) && (!lFound))  // f gefunden und l nicht?
      if (h == l)      // l gefunden?
        lFound = TRUE ;
    }
  return fFound && lFound;   // TRUE wenn beide gefunden
  }


void TextBlock::TextMetrics ()
  {
  HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
  TEXTMETRIC tm;
//  HFONT hOld = SelectObject (hDC,GetStockObject (ANSI_FIXED_FONT));
  HFONT hOld = (HFONT)SelectObject (hDC, hFontEdit);
  GetTextMetrics (hDC,&tm);
  charHeight = tm.tmHeight;
  charWidth  = tm.tmAveCharWidth;
  SelectObject (hDC,hOld);
  DeleteDC (hDC);
  }

void TextBlock::SetCaption (HWND hWnd)
  {
  char outtxt[128];
  if (fName == NULL) return ;
  if (ModifyDone)
    wsprintf (outtxt,"%s *",fName);
  else
    wsprintf (outtxt,"%s",fName);

  SetWindowText (GetParent(hWnd), outtxt);

  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_STOREED, MAKELONG(ModifyDone, 0));
  }
  
  
////////////////////////////////////////////////////////////////////////
//
//   TextLine
//
////////////////////////////////////////////////////////////////////////
#define INCLUDE   "include"
#define DEFINE    "define"
static BOOL mystrcmp (LPSTR ltxt, LPSTR stxt)
  {
  for ( ; ((*ltxt) && (*stxt) && (*stxt == *ltxt)) ; stxt ++ , ltxt ++ ) ;
  return (*stxt == '\0');
  }

//----------------------------------------------
// fuegt an das Ende eines Satzes einen Text an
//----------------------------------------------
void TextLine::AddText (LPSTR txt)
  {
  LPSTR ntxt = LPSTR(GetGlobMem (lstrlen(Text) + lstrlen(txt) + 1));
  lstrcpy (ntxt,Text);
  lstrcat (ntxt,txt);
  FreeGlobMem (Text);
  Text = ntxt;
  }


//----------------------------------------------------------------------------
// fuegt im Text an der Stelle iPos einen Text ein
// Rueckgabewert : Ende-Position des eingefuegten Textes
//----------------------------------------------------------------------------
int TextLine::InsertText (LPSTR txt, int iPos)
  {
  LPSTR nTxt = NULL;

  // einfuegen innerhalb des Textes
  if (iPos <= lstrlen(Text)) {
    nTxt = LPSTR (GetGlobMem (lstrlen(Text) + lstrlen(txt) + 1)); 
    if (iPos > 0)
      lstrcpyn (nTxt, Text, iPos+1);  // alten Text bis zum Caret rein
    else
      nTxt[0] = '\0';                 // gleich das neue am Anfang
      
    lstrcat (nTxt, txt);
    lstrcat (nTxt, Text+iPos); // Rest vom alten Text
    }
    // Caret befand sich bereits ausserhalb des Textes
  else {
    nTxt = LPSTR (GetGlobMem (iPos + 2 + lstrlen(txt))); 
    int TextLen = lstrlen(Text);   // Text ohne '\0'
    lmemcpy (nTxt, Text, TextLen);
    for (int i = TextLen; i < iPos; i++) // bis zum Caret mit Leerzeichen fuellen
      nTxt[i] = ' ';
    nTxt[i+1] = '\0';                 // mit Zero-Terminator

    lstrcat (nTxt, txt);
    }

  if (nTxt != NULL) {
    FreeGlobMem (Text);
    Text = nTxt;
    }

  iPos += lstrlen(txt);
  return (iPos);
  }


//----------------------------------------------------------------------------
// loescht den Text in der Zeile von <Start> bis <End>
//----------------------------------------------------------------------------
void TextLine::DeleteText (int Start, int End)
  {
  if (Start >= End) 
    return;

  LPSTR nTxt;

  if (End > lstrlen(Text))
    End = lstrlen(Text);
    
  nTxt = LPSTR (GetGlobMem (lstrlen(Text) - (End - Start) + 1)); 

  if (Start > 0)
    lstrcpyn (nTxt, Text, Start+1);  // alten Text bis zum Caret rein
  else
    nTxt[0] = '\0';
    
  lstrcat (nTxt, Text+End);      // Rest vom alten Text

  FreeGlobMem (Text);
  Text = nTxt;
  }


//-------------------------  TextLine::Paint  -------------------------------
//
//
//---------------------------------------------------------------------------
void TextLine::Paint (HDC hDC, int x, int y, LPRECT rcLine, BOOL Analyse, LPTEXTBLOCK lptb)
  {
  RECT rc;
  COLORREF OldTextColor;

  CopyRect (&rc, rcLine);

#ifdef ANALYSELINE
  ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
  if (Analyse) {
    int len;
    int xEnd = 0;
    if (Quota != NULL) {
      OldTextColor = SetTextColor (hDC, STRING_FORECOLOR /*RGB(0x0, 0, 0xFF)*/);
      for (LPANALYSESTRUCT h = Quota; h != NULL; h = h->Next) {
        rc.left = x + h->StartPos * lptb->charWidth;
        if (h->EndPos > h->StartPos) {
          xEnd = (h->EndPos + 1) * lptb->charWidth;
          len = h->EndPos - h->StartPos + 1;
          }
        else {
          xEnd = lstrlen(Text) * lptb->charWidth;
          len = lstrlen(Text) - h->StartPos;
          }
        rc.right = x + xEnd;

        ExtTextOut (hDC, rc.left, y, 
                    ETO_CLIPPED | ETO_OPAQUE, &rc, Text + h->StartPos, len, NULL);
        }
      SetTextColor (hDC, OldTextColor);
      }

    if (Comment != NULL) {
      OldTextColor = SetTextColor (hDC, COMMENT_FORECOLOR/*RGB(0, 0x80, 0)*/);
      for (LPANALYSESTRUCT h = Comment; h != NULL; h = h->Next) {
        rc.left = x + h->StartPos * lptb->charWidth;

        if (h->EndPos > h->StartPos) {
          xEnd = h->EndPos * lptb->charWidth;
          len = h->EndPos - h->StartPos;
          }
        else {
          xEnd = lstrlen(Text) * lptb->charWidth;
          len = lstrlen(Text) - h->StartPos;
          }
        rc.right = x + xEnd;

        ExtTextOut (hDC, rc.left, y, 
                    ETO_CLIPPED | ETO_OPAQUE, &rc, Text + h->StartPos, len, NULL);
        }
      SetTextColor (hDC, OldTextColor);
      }

#ifdef ANALYSEKEYWORD
    if (KeyWord != NULL) {
      OldTextColor = SetTextColor (hDC, KEYWORD_FORECOLOR /*RGB(0xFF, 0, 0)*/);

      for (LPANALYSESTRUCT h = KeyWord; h != NULL; h = h->Next) {
        rc.left = x + h->StartPos * lptb->charWidth;

        xEnd = h->EndPos * lptb->charWidth;
        len = h->EndPos - h->StartPos;

        rc.right = x + xEnd;

        ExtTextOut (hDC, rc.left, y, 
                    ETO_CLIPPED | ETO_OPAQUE, &rc, Text + h->StartPos, len, NULL);
        }
      SetTextColor (hDC, OldTextColor);
      }
#endif

    }
#else
  if (Analyse) {
    int res = AnalyseSpecialChar ('$');  // erstes auftreten vom Kommentar-Zeichen
    if (res >= 0) {
    
      // Text bis zum Kommentar "$"
      OldTextColor = SetTextColor (hDC, 0);
      if (res > 0)
        ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, res, NULL);
  
      // Text ab Kommentar "$"
      SetTextColor (hDC, RGB(0, 0x80, 0));
      rc.left = x + res * lptb->charWidth;
      ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
      SetTextColor (hDC, OldTextColor);
      }
    else {
      if ((res = AnalyseSpecialChar ('#')) >= 0) {
        int endCross = AnalyseSpecialChar (' ', res+1);
        
        OldTextColor = SetTextColor (hDC, RGB(0, 0, 0x80));
        rc.right = x + endCross*lptb->charWidth;
        ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
        SetTextColor (hDC, OldTextColor);
        rc.left = rc.right;
        rc.right = rcLine->right;
        }
  
      ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
  
      char szText = '"';
  //    szText[0] = '"';
  //    szText[1] = '\0';
  
      OldTextColor = SetTextColor (hDC, RGB(0, 0, 0xFF));
      res = 0;
      while ((res = AnalyseSpecialChar ('"', res)) >= 0) {
        int endText = AnalyseSpecialChar ('"', res+1) + 1;
  
        rc.left =  x + res * lptb->charWidth;
        if (endText > res) {
          rc.right = x + endText * lptb->charWidth;
          res = endText;
          }
        else {
          rc.right = rcLine->right;  
          res = lstrlen(Text);
          }
  
        ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
        }
      
      SetTextColor (hDC, OldTextColor);
  
      }
    }
  else
    ExtTextOut (hDC, x, y, ETO_CLIPPED | ETO_OPAQUE, &rc, Text, lstrlen(Text), NULL);
#endif
  }


//****************************************************************************
//*
//*    Analysieren der Hochkomma- und Kommentarinformatin
//*
//****************************************************************************
#ifdef ANALYSELINE


//============================================================================
// TextLine::ClearQuota
//
//============================================================================
void TextLine::ClearQuota ()
  {
  if (Quota) {
    for (LPANALYSESTRUCT h = Quota; h != NULL; ) {
      LPANALYSESTRUCT n = h->Next;
      FreeGlobMem (h);
      h = n;
      }
    }

  Quota = NULL;
  }

//============================================================================
// TextLine::ClearComment
//
//============================================================================
void TextLine::ClearComment ()
  {
  if (Comment) {
    for (LPANALYSESTRUCT h = Comment; h != NULL; ) {
      LPANALYSESTRUCT n = h->Next;
      FreeGlobMem (h);
      h = n;
      }
    }

  Comment = NULL;
  }

#ifdef ANALYSEKEYWORD
//============================================================================
// TextLine::ClearKeyWord
//
//============================================================================
void TextLine::ClearKeyWord ()
  {
  if (KeyWord) {
    for (LPANALYSESTRUCT h = KeyWord; h != NULL; ) {
      LPANALYSESTRUCT n = h->Next;
      FreeGlobMem (h);
      h = n;
      }
    }

  KeyWord = NULL;
  }
#endif


//============================================================================
// TextLine::GetAnalyseStatus
//
//
//============================================================================
DWORD TextLine::GetAnalyseStatus (int x)
  {
  if (Comment != NULL) {
    for (LPANALYSESTRUCT h = Comment; h != NULL; h = h->Next) {
      if ((x >= h->StartPos) && ((x <= h->EndPos) || (h->EndPos == -1)))
        return ANALYSE_STATE_COMMENT;
      }
    }

  if (Quota != NULL) {
    for (LPANALYSESTRUCT h = Quota; h != NULL; h = h->Next) {
      if ((x >= h->StartPos) && ((x <= h->EndPos) || (h->EndPos == -1)))
        return ANALYSE_STATE_QUOTAINIT;
      }
    }

  return ANALYSE_STATE_INIT;
  }

//============================================================================
//  TextLine::AnalyseLine
//
//
//============================================================================
BOOL TextLine::AnalyseLine ()
  {
  //-----------------------------------------------
  // Alle vorherigen Zeilen-Eigenschaften loeschen
  //-----------------------------------------------
  ClearQuota ();
  ClearComment ();

#ifdef ANALYSEKEYWORD
  char CurrentWord[256];
  char ch[2];

  lstrcpy (CurrentWord, "");

  ClearKeyWord ();
  short KeyWordStartPos = 0;
#endif

  char PrevChar = '\0';

  if (Prev != NULL) {      // gibt's eine vorhergehende Zeile?
    State = Prev->State;   // dann uebernimm deren Zustand
    //---------------------------------------------------------
    // wurde in der vorhergehenden Zeile ein String geoeffnet?
    //---------------------------------------------------------
    if (State == ANALYSE_STATE_QUOTAINIT) {
      Quota = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
      Quota->StartPos = 0;
      Quota->EndPos = -1;
      Quota->Next = NULL;
      }
    }
  else
    State = ANALYSE_STATE_INIT;   // ganz von vorne beginnen

  LPANALYSESTRUCT CurrentQuota = Quota;

  int i = 0;
  for (LPSTR h = Text ; *h ; h++, i++) {
    switch (*h) {
      //------------------------
      // Kommentare analysieren
      //------------------------
      case '$' :
        {
        //-------------------------------------------------
        // wurde vor dem Kommentar kein Hochkomma gefunden
        // dann ist ab jetzt alles uninteressant => raus
        //-------------------------------------------------
        if (State != ANALYSE_STATE_QUOTAINIT) {
          if (Comment == NULL) {
            Comment = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
            Comment->StartPos = i;       // Kommentar vom aktuellen Zeichen...
            Comment->EndPos = -1;        // bis zum Zeilenende
            Comment->Next = NULL;        // es kan nur eines geben...


            for ( ; (i > 0) && (Text[i-1] == ' ') ; i--);

            //-------------------------------------------------------------
            // wurde das $ ganz am Anfang der Zeile gefunden oder ist dies
            // wirklich eine reine Kommentarzeile dann passe den Status an
            //-------------------------------------------------------------
            if (i == 0) {
              State = ANALYSE_STATE_FULLCOMMENT;
              return TRUE;
              }
            else
              State = ANALYSE_STATE_INIT;  // aber nur bei einzeiligem Kommentar!!!!
              return TRUE;
            }
          }

        }
        break;

      //------------------------
      // Strings analysieren
      //------------------------
      case '"' :
        {
        //--------------------------------------------------
        // innerhalb eines Kommentares gibt's keinen String
        //--------------------------------------------------
        if (State != ANALYSE_STATE_COMMENT) {
          if (CurrentQuota) {
            //----------------------------------------
            // War da nicht gerade ein String-Anfang?
            //----------------------------------------
            if (State == ANALYSE_STATE_QUOTAINIT) {

              // ACHTUNG: <\"> ist ein Zeichen, kein Stringende
              if (PrevChar == '\\') {
                int j = i - 1;
                int k = 0;
                for ( ; Text[j] == '\\'; j--, k++);
                if (k % 2 != 0)
                  break;
                }

              //--------------------------------------------------
              // jetzt ist aber einmal Schluß mit dem Stringzeugs
              //--------------------------------------------------
              CurrentQuota->EndPos = i;
//              State = ANALYSE_STATE_QUOTAEND;
              State = ANALYSE_STATE_INIT;
              }
            else {
              //---------------------------------------------
              // da ist ja noch so ein String in der Zeile!!
              //---------------------------------------------
              LPANALYSESTRUCT h = CurrentQuota;

              LPANALYSESTRUCT n = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
              n->StartPos = i;  // na gut, also fangen wir einmal an
              n->EndPos = -1;   // das Ende ist noch nicht bekannt
              n->Next = NULL;
              h->Next = n;
              State = ANALYSE_STATE_QUOTAINIT;

              CurrentQuota = n;
              }
            }
          else {
            //--------------------------------------------
            // ich bin der erste String in der Zeile!!!!!
            //--------------------------------------------
            Quota = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
            Quota->StartPos = i;   // ab hier beginnt's
            Quota->EndPos = -1;    // aber wo hört das Ganze auf?
            Quota->Next = NULL;
            State = ANALYSE_STATE_QUOTAINIT;

            CurrentQuota = Quota;
            }
          }
        }
        break;
      }
    PrevChar = *h;

#ifdef ANALYSEKEYWORD
    if ((State == ANALYSE_STATE_QUOTAINIT) || ((*h < 65) && !(*h == '#'))) {
      if (CurrentWord[0] != '\0')
        if (AnalyseKeyword (CurrentWord)) {
          LPANALYSESTRUCT n;
          LPANALYSESTRUCT k = KeyWord;
          if (k != NULL)
            for ( ; k->Next != NULL; k = k->Next);

          n = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
          n->StartPos = KeyWordStartPos;
          n->EndPos = i;
          n->Next = NULL;
          if (k != NULL)
            k->Next = n;
          else
            KeyWord = n;
          
//          MessageBeep (0);
          }

      lstrcpy (CurrentWord, "");
      KeyWordStartPos = (i > 0) ? i+1 : i;
      }
    else {
      ch[0] = *h;
      ch[1] = '\0';
      lstrcat (CurrentWord, ch);
      }
#endif

    }

  //-------------------------------------------------------------
  // am Zeilenende muss das Ganze noch einmal ueberprueft werden
  //-------------------------------------------------------------
  if ((State == ANALYSE_STATE_INIT) && (CurrentWord[0] != '\0')) {
    if (AnalyseKeyword (CurrentWord)) {
      LPANALYSESTRUCT n;
      LPANALYSESTRUCT k = KeyWord;
      if (k != NULL)
        for ( ; k->Next != NULL; k = k->Next);

      n = (LPANALYSESTRUCT)GetGlobMem (sizeof(AnalyseStruct));
      n->StartPos = KeyWordStartPos;
      n->EndPos = i;
      n->Next = NULL;
      if (k != NULL)
        k->Next = n;
      else
        KeyWord = n;
      }
    }


  if (State != ANALYSE_STATE_QUOTAINIT)
    State = ANALYSE_STATE_INIT;

  return TRUE;
  }
#endif


#ifdef ANALYSEKEYWORD

LPVOID KeyWords = NULL;
static short AnzKeyWords = 0;

int qcompare (const void *arg1, const void *arg2)
  {
  return lstrcmp (*((LPSTR FAR *)arg1), *((LPSTR FAR *)arg2));
  }


BOOL TextLine::AnalyseKeyword (LPSTR CurrentWord)
  {
  LPSTR FAR *result = (LPSTR FAR *)bsearch (&CurrentWord, KeyWords, AnzKeyWords, sizeof(LPSTR), qcompare);
  return ((result != NULL) && (*result != NULL));
  }


//============================================================================
//  LoadKeyWords
//
//
//============================================================================
void LoadKeyWords ()
  {
  FILE *infile;
  char buffer[512];
  char szKeyFile[256];

  LPSTR n;
  LPVOID h;
  int i = 0;

  KeyWords = GetGlobMem (sizeof(LPSTR));
  int keylen = 0;

  GetPrivateProfileString ("EDITOR","KeyWords","KEYWORDS.TXT",szKeyFile, sizeof(szKeyFile), IniFile());

  if (infile = fopen(szKeyFile, "rb")) {
    while (!feof(infile)) {
      fscanf (infile, "%s", buffer);

      n = LPSTR(GetGlobMem(lstrlen(buffer) + 1));
      lstrcpy (n, buffer);
      
      h = GetGlobMem ((i+1) * sizeof(LPSTR));

      lmemcpy (h, KeyWords, i * sizeof(LPSTR));
      lmemcpy (LPSTR(h) + i * sizeof(LPSTR), &n, sizeof(LPSTR));

      FreeGlobMem (KeyWords);
      KeyWords = h;

      i++;
      }

    fclose (infile);

    AnzKeyWords = i;

    qsort (LPVOID(KeyWords), (size_t)AnzKeyWords, sizeof(LPSTR), qcompare);
    }
  }

#endif


//============================================================================
//  Funktion: LoadSyntaxColors
//
//  Zweck: Liest aus der Datei RESTOOL.INI die Farbeinstellungen fuer die
//         Darstellung des Textes im Editorfenster.
//============================================================================
void LoadSyntaxColors ()
  {
  char szColor[10];
  LPSTR StopString;
  GetPrivateProfileString ("Colors","SelectionForeColor","0xFFFFFF",szColor, sizeof(szColor), IniFile());
  SELECTION_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","SelectionBackColor","0x000000",szColor, sizeof(szColor), IniFile());
  SELECTION_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BreakPointForeColor","0xFFFFFF",szColor, sizeof(szColor), IniFile());
  BREAKPOINT_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BreakPointBackColor","0x000080",szColor, sizeof(szColor), IniFile());
  BREAKPOINT_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","ActiveForeColor","0x000000",szColor, sizeof(szColor), IniFile());
  ACTIVE_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","ActiveBackColor","0x00FFFF",szColor, sizeof(szColor), IniFile());
  ACTIVE_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BookmarkForeColor","0x000000",szColor, sizeof(szColor), IniFile());
  BOOKMARK_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BookmarkBackColor","0x808000",szColor, sizeof(szColor), IniFile());
  BOOKMARK_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","ErrorForeColor","0xFFFFFF",szColor, sizeof(szColor), IniFile());
  ERROR_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","ErrorBackColor","0x800000",szColor, sizeof(szColor), IniFile());
  ERROR_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BraceForeColor","0x0000FF",szColor, sizeof(szColor), IniFile());
  BRACE_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","BraceBackColor","0xFFFFFF",szColor, sizeof(szColor), IniFile());
  BRACE_BACKCOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","StringForeColor","0xFF0000",szColor, sizeof(szColor), IniFile());
  STRING_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","CommentForeColor","0x008000",szColor, sizeof(szColor), IniFile());
  COMMENT_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);

  GetPrivateProfileString ("Colors","KeywordForeColor","0x0000FF",szColor, sizeof(szColor), IniFile());
  KEYWORD_FORECOLOR = (COLORREF)strtoul (szColor, &StopString, 16);
  }


int TextLine::AnalyseComment ()
  {
  int res = -1;
  for (LPSTR h = Text ; ((*h) && (*h != '$')) ; h++);
  if (*h == '$')
    res = h - Text;

  return res;
  }


//----------------------------------------------------------------------------
// Funktion:   TextLine::AnalyseSpecialChar
//
// Sucht das Vorkommen des Zeichens <ch> in der Textzeile, und gibt die
// Position des ersten Auftretens zurück
//----------------------------------------------------------------------------
int TextLine::AnalyseSpecialChar (char ch, int StartPos)
  {
  int res = -1;
  int i = 0;
  for (LPSTR h = Text ; *h && (i < StartPos) ; h++ , i++) ;   // alle Zeichen bis Startpos ueberlesen
  if (i == StartPos) {
    for ( ; ((*h) && (*h != ch)) ; h++);  // suche das erste Vorkommen des Zeichens
    if (*h == ch)
      res = h - Text;
    }  

  return res;
  }

int TextLine::AnalyseSpecialString (LPSTR lpstr, int StartPos, int len)
  {
  char szBuf[80];
  int res = -1;

  if (StartPos < lstrlen(Text))
    for (LPSTR h = Text+StartPos; *h; h++) {
      lstrcpyn (szBuf, h, len+1);
      if (!lstrcmp(szBuf, lpstr)) {  // Strings sind gleich
        res = h - Text;
        break;
        }
      }  

  return res;
  }
    
#define MAXDEFSIZE   512
BOOL TextLine::AnalyseDefine(LPVOID buffer,WORD FAR *size,LPSTR name)
  {
  LPSTR h = Text;
  BOOL found = FALSE ;
  for ( ; ((*h) && (*h != '#') && (*h != '$')) ; h++) ;

  if (*h == '$')   // Kommentar vor "#define"?  -> raus!
    return found;
    
  if (*h == '#') {
    h ++ ;
    if (mystrcmp (h,DEFINE)) {
      for ( ; ((*h) && (*h != ' ') && (*h != '\t')) ; h ++ ) ;    // bis zum ende des defines
      for ( ; ((*h) && ((*h == ' ') || (*h == '\t'))) ; h ++ ) ;  // bis zum beginn des namens
      for ( ; ((*h) && (*h != ' ') && (*h != '\t')) ; )           // namen kopieren
        *name++ = *h ++ ;
      *name ++ = '\0';
      for ( ; ((*h) && ((*h == ' ') || (*h == '\t'))) ; h ++ ) ;  // bis zum start des wertes
      if (((*h >= '0') && (*h <= '9')) || (*h == '-') || (*h == '+')) {
        LONG sign = (*h == '-') ? -1 : +1 ;
        LONG res = 0;
        for ( ; *h ; h ++) {
          if ((*h >= '0') && (*h <= '9'))
            res = res * 10 + *h - '0' ;
          }
        res *= sign;
        *((LONG FAR *) buffer) = res;
        *size = sizeof(LONG);
        found = TRUE ;
        }
      else if (*h == '"') {
        h++ ;
        *size = 0;
        for (LPSTR res = LPSTR(buffer) ; ((*h) && (*h != '"') && (*size < MAXDEFSIZE - 1)) ; ) {
          *res ++ = *h++ ;
          *size += 1;
          }
        *res ++ = '\0';
        *size += 1;
        found = TRUE ;
        }
      else {
        return FALSE;     // nix tun
        }
      }
    }
  return found;
  }


LPSTR TextLine::AnalyseInclude ()
  {
  for ( LPSTR h = Text ; ((*h) && (*h != '#')) ; h++) ;
  if (*h == '#') {
    h++ ;
    if (mystrcmp (h,INCLUDE)) {
      for ( ; ((*h) && (*h != '"')) ; h ++ ) ;
      if (*h == '"') h++ ;
      if (*h) return h ;
      }
    }
  return NULL;
  }


////////////////////////////////////////////////////////////////////////
//
//   FileBlock
//
////////////////////////////////////////////////////////////////////////

#ifdef TOOLTIP
//----------------------------------------------------------------------------
// DoCreateDataTip
// 
// Zweck: Anzeigen der Inhalte von Scriptvariablen
//        Wird der Mauszeiger kurze Zeit auf eine Variablen gestellt, 
//        erscheint under dem Zeiger ein kleines Fenster mit dem Variablenwert
//----------------------------------------------------------------------------
HWND DoCreateDataTip (HWND hWndOwner)
  {
  TOOLINFO ti;
  int id = 0;

  InitCommonControls(); 

  HWND hWndToolTip = CreateWindowEx (0, TOOLTIPS_CLASS, (LPSTR) NULL, TTS_ALWAYSTIP, 
                                CW_USEDEFAULT, CW_USEDEFAULT, 
                                CW_USEDEFAULT, CW_USEDEFAULT, 
                                hWndOwner, (HMENU) NULL, MyInstance, NULL); 

  if (hWndToolTip == (HWND) NULL) 
    return NULL; 

  ti.cbSize = sizeof(TOOLINFO); 
  ti.uFlags = 0; 
  ti.hwnd = hWndOwner; 
  ti.hinst = MyInstance; 
  ti.uId = (UINT) id; 

  ti.lpszText = LPSTR_TEXTCALLBACK; 

  ti.rect.left = 0; 
  ti.rect.top = 0; 
  ti.rect.right = 1000; 
  ti.rect.bottom = 1000; 

  if (!SendMessage(hWndToolTip, TTM_ADDTOOL, 0, 
          (LPARAM) (LPTOOLINFO) &ti)) {
    DestroyWindow (hWndToolTip);
    return NULL;
    }

  SendMessage (hWndToolTip, TTM_SETDELAYTIME, TTDT_AUTOPOP, 32767);
  SendMessage (hWndToolTip, TTM_SETDELAYTIME, TTDT_INITIAL, 200);
  SendMessage (hWndToolTip, TTM_SETDELAYTIME, TTDT_RESHOW, 200);

  return hWndToolTip;
  }
#endif

//----------------------------------------------------------------------------
// CONSTRUCTOR FileBlock
//
//----------------------------------------------------------------------------
FileBlock::FileBlock (LPSTR fname)
  {
  MainFile = FALSE;            // ich behaupte das ist noch keine Hauptdatei
  actblock = new TextBlock (fname);
  if (actblock->FirstLine)
    SetActiveBuffer (0,0);
  else
    delete actblock , actblock = NULL ;

  RightCursor = LoadCursor (MyInstance,"RIGHT");
  }

//----------------------------------------------------------------------------
// CONSTRUCTOR FileBlock
//
//----------------------------------------------------------------------------
FileBlock::FileBlock (GLOBALHANDLE hGTxt)
  {
  MainFile = FALSE;            // ich behaupte das ist noch keine Hauptdatei
  actblock = new TextBlock (hGTxt);
  if (actblock->FirstLine)
    SetActiveBuffer (0,0);
  else
    delete actblock , actblock = NULL ;

  RightCursor = LoadCursor (MyInstance,"RIGHT");
  }

//----------------------------------------------------------------------------
// DESTRUCTOR FileBlock
//
//----------------------------------------------------------------------------
FileBlock::~FileBlock ()
  {
/*
  for (int i = 0 ; i < CB_TEXTBLOCKS ; i++)
    if (blocks[i] != NULL) delete blocks[i];
*/
  for (int i = 0; i < FILES_IN_PROJECT; i++)
    if (FileInProject[i] != NULL)
      FreeGlobMem (FileInProject[i]);

  delete actblock;
  
  if (RightCursor)
    DestroyCursor (RightCursor);

  if (dbinf != NULL)
    delete dbinf;
  }


void FileBlock::CheckDrop (HWND hWnd, int x, int y, WORD Type, BOOL last, LPSTR SelWord)
  {
  POINT pt;
  pt.x = x ;
  pt.y = y ;
  DDOnMouseMove (Type, SelWord, &pt, hWnd, last);
  }


void FileBlock::SetCaretTo (HWND hWnd,int el,int ec,BOOL doCenter)
  {
  actblock->TextMetrics();
  actblock->FirstVisibleLine = actblock->FirstLine;
  actblock->LineWithCaret = actblock->GetLineFromLineNr (el-1);
  if (actblock->LineWithCaret == NULL) {
    if (el-1 > 0) {
      actblock->LineWithCaret = actblock->LastLine;
      if ((actblock->LineWithCaret != NULL) && (actblock->LineWithCaret->Text != NULL))
        actblock->iCaret = max (strlen (actblock->LineWithCaret->Text) - 1, 0);
      else
        actblock->iCaret = 0;
      }
    else {
      actblock->LineWithCaret = actblock->FirstLine;
      actblock->iCaret = 0;
      }
    }
  else
    actblock->iCaret = ec-1;
  int yExtra;
  if (doCenter) {
    RECT rc ;
    GetClientRect (hWnd,&rc);
    yExtra = (rc.bottom - rc.top) / 4 ;
    }
  else
    yExtra = 0 ;
  InvalidateRect (hWnd,NULL,TRUE);
  SetFocus (hWnd);
  actblock->SetNewCPos (hWnd,0,yExtra,0,yExtra);
  SendMessage (hwndMDIClient,WM_MDIACTIVATE,WPARAM(HWND(GetParent(hWnd))),0L);
  SetFocus (hWnd);
  }

void FileBlock::CheckError (HWND hWnd,LPSTR eName,int el,int ec)
  {
  HWND hwndT;
  BOOL Found = FALSE;
  LPFILEBLOCK fbl = NULL;
  
  if (actblock->fName == NULL) return ;

  hwndT = GetWindow(hwndMDIClient, GW_CHILD);
  while (hwndT) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow(hwndT, GW_HWNDNEXT);
         
    if (hwndT) {
      HWND hScWnd = GetWindow (hwndT,GW_CHILD);
      if (hScWnd) {
        fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
        if (lstrcmp (GetFName (fbl->actblock->fName),eName) == 0) {
          fbl->SetCaretTo (hScWnd,el,ec);
          Found = TRUE;
          break;
          }
        }
      hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
      }
    }  
  
  if (*eName) {
    if (!Found) {
      char fname[128];
      char sname[64];
      GetIncludeFileName (eName, fname, sname, "source");
  
      HWND hWndChild;
      if (hWndChild = ShowScript (NULL, fname)) {
        HWND hScWnd = GetWindow (hWndChild,GW_CHILD);
        if (IsWindow(hScWnd)) {
          fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
          fbl->SetCaretTo (hScWnd,el,ec);
          }
        }
      }
//    else {
      // Fehlerzeile setzen und faerbig anzeigen
      if (fbl != NULL) {
        fbl->actblock->ErrorLine = fbl->actblock->LineWithCaret;
        if (fbl->actblock->ErrorLine != NULL) {
          fbl->actblock->ErrorLine->SetErrorLine ();
          fbl->actblock->InvalidateLine (hWnd, fbl->actblock->ErrorLine);
          }
        }  
      MessageBeep (0);
      }
//    }
  }

void FileBlock::CheckError (HWND hWnd)
  {
  if (!IsCompileAborted()) {
    int el,ec;
    LPSTR errfile = GetErrorInfo (&el,&ec);
    CheckError (hWnd,GetFName (errfile),el,ec);
    }
  }

BOOL CheckWindowForBreak (HWND hwndT,LPSTR FName,int LineNmbr)
  {
  HWND hScWnd = GetWindow (hwndT,GW_CHILD);
  if (hScWnd) {
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
    if ((fbl->actblock->fName != NULL) && (lstrcmp (GetFName (fbl->actblock->fName),FName) == 0)) {
      fbl->SetCaretTo (hScWnd,LineNmbr,1,TRUE);
      return TRUE ;
      }
    }
  return FALSE ;
  }

ScDebugInfo FAR *GetDebugInfoFromWindow (HWND hwndT,LPSTR fName,BOOL FAR *Found,BOOL withIncFiles)
  {
  HWND hScWnd = GetWindow (hwndT,GW_CHILD);
  *Found = FALSE ;
  if (hScWnd) {
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
    if (fbl->actblock->fName == NULL) return NULL;
    if (lstrcmp (GetFName (fbl->actblock->fName),fName) == 0) {
      *Found = TRUE ;
      return fbl->dbinf;
      }
    if (withIncFiles) {
      if ((fbl->dbinf != NULL) && (fbl->dbinf->hGDInfo)) {
        int IncNmbr = fbl->dbinf->GetIncNmbr (fName);
        if (IncNmbr >= 0) {
          *Found = TRUE ;
          return fbl->dbinf;
          }
        }
      }
    }
  return NULL ;
  }

void FileBlock::CreateDefHash ()
  {
  defHash = new hash (117,STRKEY);
/*
  for (WORD i = 0 ; i < CB_TEXTBLOCKS ; i++) {
    if (blocks[i] != NULL) {
      char name[64];
      char dBuffer[MAXDEFSIZE];
      WORD size;
      for (LPLINE h = blocks[i]->FirstLine ; h != NULL ; h = h->Next ) {
        if (h->AnalyseDefine(dBuffer,&size,name,sizeof(dBuffer)))
          defHash->SetData (name,dBuffer,size);
        }
      }
    }
*/
  char name[64];
  char dBuffer[512];
  WORD size;
  for (LPLINE h = actblock->FirstLine ; h != NULL ; h = h->Next ) {
    if (h->AnalyseDefine(dBuffer,&size,name))
      defHash->SetData (name,dBuffer,size);
    }

  }

LPSTR AnalyseFileName(LPSTR h)
  {
  static char res[13];
  LPSTR d = res;
  for ( ; ((*h) && (*h != '"')) ; h++) {
    if ((*h == ':') || (*h == '\\') || (*h == '/')) d = res;
    else *d++ = *h ;
    }
  *d = '\0';
  AnsiUpper (res);
  return res;
  }

void FileBlock::AddToList (HWND hWndList,LPSTR fName,int FAR &j)
  {
  char name[13];
  lstrcpy (name,fName);
  AnsiUpper(name);
  int count = int (SendMessage(hWndList,LB_GETCOUNT,0,0L));
  BOOL found = FALSE ;
  for (int i = 0 ; i < count ; i++) {
    char res[256];
    SendMessage(hWndList,LB_GETTEXT,i,LPARAM(LPSTR(res)));
    if (lstrcmp(res,name) == 0) found = TRUE ;
    }
  if (!found) {
    SendMessage (hWndList,LB_ADDSTRING,0,LPARAM(LPSTR(name)));
    WIN_ASSERT(j < FILES_IN_PROJECT);
    FileInProject[j] = LPSTR(GetGlobMem (lstrlen(name)+1));
    lstrcpy (FileInProject[j++], name);
    }
  }

void FileBlock::ActivateList ()
  {
#ifdef WIN32
  HWND hWndList = (HWND)GetWindowLong (hWndProjectList, GWW_LISTWINDOW);
#else
  HWND hWndList = GetWindowWord (hWndProjectList, GWW_LISTWINDOW);
#endif
  SendMessage (hWndList, LB_RESETCONTENT, 0, 0L);
  for (int i = 0 ; i < FILES_IN_PROJECT ; i++) {
    if (FileInProject[i] != NULL)
      SendMessage (hWndList,LB_ADDSTRING,0,LPARAM(FileInProject[i]));
    else
      break ;
    }
  }

void FileBlock::CreateIncludes (HWND hWnd)
  {
  if (actblock->fName == NULL) return ;

#ifdef WIN32
  HWND hWndList = (HWND)GetWindowLong (hWndProjectList, GWW_LISTWINDOW);
#else
  HWND hWndList = GetWindowWord (hWndProjectList, GWW_LISTWINDOW);
#endif

  SendMessage (hWndList, LB_RESETCONTENT, 0, 0L);

  int j = 0 ;
  for (LPLINE l = actblock->FirstLine ; l != NULL ; l = l->Next ) {
    LPSTR h = l->AnalyseInclude ();
    if (h != NULL) {
      LPSTR s = AnalyseFileName(h);
      AddToList (hWndList,s,j);
      }
    }
  // Laden des Scriptheaders
#ifdef UEBERLEGT
  LoadScriptContent ();
  LPSCRIPTCONTENT schd = GetScriptEntry(GetFName(actblock->fName));
  if (schd != NULL) {
    for (int i = 0 ; (i < int (schd->AnzTables)) ; i++) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TableNr[i]);
      if (td != NULL) {
        AddToList (hWndList,td->GetFileName(),j);
        GetTableAdmin()->FreeTable(schd->TableNr[i]);
        }
      }
    }
#endif
  }


void FileBlock::GetInvalidRect (HWND hWnd,LPLINE f,LPLINE l,LPRECT r)
  {
  int ystart,yend;
  actblock->GetSelRange (&ystart,&yend,f,l);
  GetClientRect (hWnd,r);
  r->top    = max(ystart,0);
  r->bottom = min(yend,r->bottom);
  }

/*
WORD FileBlock::GetNextBuffNmbr ()
  {
  for (WORD i = 0 ; i < CB_TEXTBLOCKS ; i++) {
    if (actblock == blocks[i]) return (blocks[i+1] != NULL) ? i + 1 : 0 ;
    }
  return 0;
  }
*/
static char ScreenName[32];
static char ObjectName[32];
DLLExport BOOL FAR PASCAL _export BspDialog (HWND hDlg, UINT msg, WORD wP, LONG lP);

void FileBlock::InsertBsp (HWND hWnd)
  {
  *ScreenName = *ObjectName = 0;
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(BspDialog),MyInstance));
  BOOL res = DialogBox (MyInstance,"INSERTSCREEN",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  if (res) {
    if ((*ScreenName) && (*ObjectName)) {
      for ( int i = 0 ; i < 3 ; i++) {
        char instring[128],outstring[128];
        LoadString (MyInstance,IDDLGBSP_BASE+i,instring,sizeof(instring));
        switch (i) {
          case 0 :
            wsprintf (outstring,instring,LPSTR(ScreenName),LPSTR(ObjectName));
            break ;
          case 1 :
            wsprintf (outstring,instring,LPSTR(ScreenName));
            break ;
          case 2 :
            wsprintf (outstring,instring,LPSTR(ObjectName),LPSTR(ScreenName));
            break ;
          }
        LastSelectedLine = actblock->InsertLineBehind (LastSelectedLine,outstring);
        }
      InvalidateRect (hWnd,NULL,TRUE);
      }
    else
      MessageBeep (0);
    }
  actblock->SetModified ();
  }

void FileBlock::InvalidateSelected (HWND hWnd,LPLINE f,LPLINE l)
  {
  RECT r;
  GetInvalidRect (hWnd,f,l,&r);
  InvalidateRect (hWnd,&r,FALSE);
  }


BOOL FileBlock::IsModifyDone ()
  {
  BOOL res = FALSE ;
/*
  for (int i = 0 ; ((i < CB_TEXTBLOCKS) && (!res)) ; i++)
    res = ((blocks[i] != NULL) && (blocks[i]->ModifyDone));
*/
  res = ((actblock != NULL) && (actblock->ModifyDone));
  return res;
  }


void FileBlock::Paint (HWND hWnd, HDC hDC, RECT rcPaint)
  {
  if (!actblock->TestLines (FirstSelectedLine, LastSelectedLine))
    FirstSelectedLine = LastSelectedLine = NULL ;

  actblock->Paint (hWnd, hDC, FirstSelectedLine, LastSelectedLine, rcPaint);
  }



BOOL IsPrChar (char ch)
  {
  return (IsCharAlphaNumeric(ch));
  }


LPSTR FileBlock::ActiveWord ()
  {
  static char VarNamBuffer[256];
  VarNamBuffer[0] = '\0';
  int LineNr = actblock->YAbsCaret;
  LPLINE h = actblock->LineWithCaret;
  if (h != NULL) {
    int charNr = actblock->iCaret;
    if ((charNr < lstrlen(h->Text)) && actblock->IsWordChar(h->Text[charNr], TRUE)) {
      // da isn wort
      for (int b = charNr ; (b > 0) ; b --)
        if (!actblock->IsWordChar(h->Text[b],TRUE)) { b ++ ; break ; }
      for (int e = charNr ; ; e ++)
        if (!actblock->IsWordChar(h->Text[e],TRUE)) { e -- ; break ; }
      if (e >= b) {
        int j = 0 ;
        for (int i = b ; i <= e ; i++)
          VarNamBuffer[j++] = h->Text[i];
        VarNamBuffer[j] = '\0';
        }
      }
    }
  return VarNamBuffer;
  }

void FileBlock::SetActiveBuffer (HWND hWnd,WORD BlockNr)
  {
//  if ((actblock != NULL) && (hWnd))
//    actblock->OnKillFocus (hWnd);
//  actblock = blocks[BlockNr];
  FirstSelectedLine = LastSelectedLine = l1 = NULL;
  if ((actblock != NULL) && (hWnd)) {
    actblock->TextMetrics ();
    actblock->OnSetFocus (hWnd);
    }
  }


//----------------------------------------------------------------------------
// Achtung: da der FileBlock keine eigene Caption besitzt (er ist ja ein Kind
//          des MID-Childs), muß der Parent (MDI-Child) sein Caption aendern.
//----------------------------------------------------------------------------
void FileBlock::SetCaption (HWND hWnd)
  {
  actblock->SetCaption (hWnd);
  }
  
BOOL GetStoreFileName (HWND hWnd,LPSTR wndTitle,LPSTR fname,int sz,int Type = 0)
  {
  BOOL res;
  OPENFILENAME        ofn;
  lmemset (&ofn,'\0',sizeof(OPENFILENAME));
  *fname = '\0';

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.hInstance = MyInstance;
  if (Type == 3) {
    ofn.lpstrFilter = (LPSTR)"Mak\0*.mak\0Text\0*.txt\0Alle Dateien\0*.*\0\0";
    ofn.lpstrDefExt = (LPSTR)"mak";
    }
  else {
    ofn.lpstrFilter = (LPSTR)"Text\0*.txt\0Alle Dateien\0*.*\0\0";
    ofn.lpstrDefExt = NULL;
    }
  ofn.lpstrCustomFilter = NULL;
  ofn.nMaxCustFilter = 0;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = fname;
  ofn.nMaxFile = sz;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrTitle = wndTitle ;
  ofn.Flags = OFN_PATHMUSTEXIST;
  ofn.nFileOffset = 0;
  ofn.nFileExtension = 0;
  ofn.lCustData = 0L;
  ofn.lpfnHook = NULL;
  ofn.lpTemplateName = NULL;

  if (GetSaveFileName(&ofn)) res = TRUE ;
  else                       res = FALSE ;

  return res;
  }

void FileBlock::StoreFiles (HWND hWnd)
  {
  if ((actblock != NULL) && (actblock->ModifyDone)) {
    if ((actblock->fName == NULL) || (*actblock->fName == '\0')) {
      char fname[256];
      if (GetStoreFileName (hWnd,"Datei speichern", fname,sizeof(fname))) {
        actblock->fName = LPSTR(GetGlobMem (lstrlen (fname) + 1)) ;
        lstrcpy (actblock->fName,fname);
        }
      else return ;
      }
    actblock->Store (hWnd);
    }
  }

void FileBlock::StoreFilesUnder (HWND hWnd)
  {
  if (actblock != NULL) {
    char fname[256];
    if (GetStoreFileName (hWnd,"Datei speichern unter",fname,sizeof(fname))) {
      if (actblock->fName != NULL) FreeGlobMem (actblock->fName);
      actblock->fName = LPSTR(GetGlobMem (lstrlen (fname) + 1)) ;
      lstrcpy (actblock->fName,fname);
      SourceFileNames.InsertEntry (actblock->fName, TRUE, FALSE, FALSE, 
                                   actblock->YAbsCaret, actblock->iCaret);
      }
    else return ;
    actblock->Store (hWnd);
    }
  }


void FileBlock::TestMPos (HWND hWnd, int y)
  {
  int LineNr = y / actblock->charHeight;   // Zeilennummer (relativ)
  LPLINE h = actblock->FirstVisibleLine;
  // suche die Zeile auf die y zutrifft
  for (int i = 0 ; ((i < LineNr) && (h->Next != NULL)) ; i++ , h = h->Next);
  if (l1 == NULL) l1 = h;   // l1 wird und bleibt die gefundene Zeile

  LPLINE f, l;
  if (FirstSelectedLine != NULL)
    f = FirstSelectedLine;
  else
    f = h;  // nix selektiert => f wird die gefundene Zeile

  l = h;    
  if (actblock->TestLines (l1, h))  // Zeile h hinter Zeile l1?
    f = l1 , l = h ;
  else
    f = h , l = l1 ;

  // FirstSelectedLine und LastSelectedLine neu bestimmen
  if ((f != FirstSelectedLine) || (h != LastSelectedLine)) {
    if (FirstSelectedLine != NULL)
      InvalidateSelected (hWnd, FirstSelectedLine, LastSelectedLine);
    InvalidateSelected (hWnd, f, l);
    FirstSelectedLine = f;
    LastSelectedLine = l;
    }
  }


void FileBlock::GetDialogSelection ()
  {
  if (actblock->AlreadySelected) {
    if (actblock->StartSel.Row < actblock->EndSel.Row) {
      FirstSelectedLine = actblock->StartSel.Line;
      LastSelectedLine = actblock->EndSel.Line;
      }
    else {
      FirstSelectedLine = actblock->EndSel.Line;
      LastSelectedLine = actblock->StartSel.Line;
      }
    }
  else {
    FirstSelectedLine = LastSelectedLine = NULL;
    }  
  }

//----------------------  MouseInSelectedText  ------------------------------
//
//---------------------------------------------------------------------------
BOOL TextBlock::MouseInSelectedText (POINT pt)
  {
  pt.x -= XMIN;
  BOOL bChangeCursor = FALSE;
  SelStruct  SelStart, SelEnd;
        
  GetSelectionFromTopToBottom (&SelStart, &SelEnd);

  // suche die Start- und die End-Koordinaten
  int y0 = GetYPos (SelStart.Line);
  int y1 = y0;
  if (SelStart.Line != SelEnd.Line) {
    for (LPLINE h = SelStart.Line; ((h != NULL) && (h != SelEnd.Line)) ; 
                        h = h->Next , y1 += charHeight);
    if ((SelStart.Col > 0) && (SelEnd.Col > 0))
      y1 += charHeight;
    }                    
  else
    y1 += charHeight;

  // vertikal innerhalb dieses Bereiches?
  if ((pt.y >= y0) && (pt.y <= y1)) {
    // mehrzeilige Selektion
    if (SelStart.Line != SelEnd.Line) {
      // Cursor in der ersten selektierten Zeile?
      if ((pt.y >= y0) && (pt.y <= y0 + charHeight)) {
        // auch horizontal in der Selektion?
        if (pt.x >= SelStart.Col * charWidth)
          bChangeCursor = TRUE;
        }  
      else
      // Cursor in der letzten selektierten Zeile?
      if ((pt.y >= y1 - charHeight) && (pt.y <= y1)) {
        // horizontal noch in der Selektion?
        if (pt.x <= SelEnd.Col * charWidth)
          bChangeCursor = TRUE;
        }
      else
        bChangeCursor = TRUE;    
      }
    else
      // einzeilige Selektion
      if ((pt.x >= SelStart.Col * charWidth) &&
          (pt.x <= SelEnd.Col * charWidth))
        bChangeCursor = TRUE;
    }
  return bChangeCursor;
  }  

inline LPSTR ScWndEntName()
  {
  return "ScriptView";
  }

void WriteScWndPos (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  int h = r.bottom - r.top  + 1;
  int w = r.right  - r.left + 1;
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (ScWndEntName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (ScWndEntName(),"_Y",outstring,IniFile());
  wsprintf (outstring,"%d",w);
  WritePrivateProfileString (ScWndEntName(),"_Width",outstring,IniFile());
  wsprintf (outstring,"%d",h);
  WritePrivateProfileString (ScWndEntName(),"_Height",outstring,IniFile());
  }

void ReadScWndPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetPrivateProfileInt (ScWndEntName(),"_X",100,IniFile());
  *y = GetPrivateProfileInt (ScWndEntName(),"_Y",100,IniFile());
  *w = GetPrivateProfileInt (ScWndEntName(),"_Width",500,IniFile());
  *h = GetPrivateProfileInt (ScWndEntName(),"_Height",300,IniFile());
  }

#define DELTA_T         100
HWND hScriptWindow = 0;
static int y0 = 0;
static int OldYAbsCaret = -1;
BOOL bSelectWholeLine;
extern WORD hLineType;
extern BOOL InHLineEdit;

extern HWND hWndCombo;
BOOL OnCloseChild (HWND hmdiWnd)
  {
  HWND hwndChild = GetWindow (hmdiWnd,GW_CHILD);
  LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hwndChild,GWL_TEXTBLOCK));
  BOOL res = FALSE ;
  if ((fbl != NULL) && (AllowAnalyse())) {
    if (fbl->IsModifyDone ()) {
      int answer = MessageBox (hwndChild,"Soll das Script gespeichert werden?",fbl->actblock->fName,
                              MB_ICONQUESTION | MB_YESNOCANCEL);
      if (answer == IDYES) {
        fbl->StoreFiles (hwndChild);
        res = TRUE ;
        }
      if (answer == IDNO) {
        res = TRUE ;
        }
      }
    else  
      res = TRUE ;
    }
  else
    res = FALSE ;
  return res;
  }

void SaveFileEntry (HWND hmdiWnd, BOOL toWorkSpace)
  {
  HWND hwndChild = GetWindow (hmdiWnd,GW_CHILD);
  if (hwndChild != NULL) { // Aus Erfahrung lernt man, das hier manchmal NULL kommt, warum???
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hwndChild,GWL_TEXTBLOCK));
    if (fbl->actblock->fName) {
      if (toWorkSpace)
        WorkSpaceNames.InsertEntry (fbl->actblock->fName, FALSE, FALSE, TRUE, 
                                    fbl->actblock->YAbsCaret, fbl->actblock->iCaret);
      else
        SourceFileNames.InsertEntry (fbl->actblock->fName, TRUE, FALSE, FALSE, 
                                     fbl->actblock->YAbsCaret, fbl->actblock->iCaret);
      }
    }
  }

BOOL RestoreFileEntry (LPSTR fname, int Zeile, int Spalte)
  {
  HWND hWndChild;
  if (hWndChild = ShowScript (NULL, fname, TRUE)) {
    HWND hScWnd = GetWindow (hWndChild,GW_CHILD);
    if (IsWindow(hScWnd)) {
      LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
      fbl->SetCaretTo (hScWnd,Zeile+1,Spalte+1);
      }
    return TRUE;
    }
  else
    return FALSE;
  }

extern BOOL IsEditorWindow (HWND hWnd);

static BOOL beforeWorkSpaceRestore = TRUE;

void SaveAllWorkSpaceEntrys (HWND closingWindow) 
  {
  if (!beforeWorkSpaceRestore) {
    WorkSpaceNames.DelEntrys();
    HWND hwndT = GetWindow(hwndMDIClient, GW_CHILD);
    while (hwndT) {
      if (!GetWindow(hwndT, GW_OWNER)) { // No icon title windows
        if (IsEditorWindow (hwndT)) {
          SaveFileEntry (hwndT, (hwndT != closingWindow));
          }
        }
      hwndT = GetWindow (hwndT, GW_HWNDNEXT);
      }
    if (closingWindow != NULL)
      SourceFileNames.WriteEntrys();
    WorkSpaceNames.WriteEntrys();
    }
  }

void RestoreAllWorkSpaceEntrys ()
  {
  beforeWorkSpaceRestore = TRUE;
  WorkSpaceNames.ReadEntrys ();
  for (LPRENT x = WorkSpaceNames.First ; x != NULL ; x = x->Next) {
    RestoreFileEntry (x->Text, x->Zeile, x->Spalte);
    }
  beforeWorkSpaceRestore = FALSE;
  }

LPSTR GetExtension (LPSTR fName)
  {
  static char res[16];
  res[0] = '\0';
  for (int i = lstrlen(fName) - 1; i >= 0; i--) {
    if (fName[i] == '.') {
      lstrcpy(res,&fName[i+1]);
      break;
      }
    }
  AnsiUpper (res);
  return res;
  }

LPSTR GetNameOnly (LPSTR fName)
  {
  static char res[256];
  lstrcpy (res, fName);
  for (int i = lstrlen(res) - 1; i >= 0; i--) {
    if (res[i] == '.') {
      res [i] = '\0';
      break;
      }
    }
  AnsiUpper (res);
  return res;
  }

#define MAXMENUS 10
static HMENU hTempMenu[MAXMENUS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//----------------------------------------------------------------------------
// Wechselt das Menu in der Spalte "MenuPos" in den Titel "MenuText"
//----------------------------------------------------------------------------
/*
void ChangePopupMenus (LPSTR MenuID, LPSTR MenuText, int MenuPos)
  {
  HMENU hMainMenu = GetMenu (hwndFrame);

  // wenn das MDI-Child maximiert ist, wird leider das System-Menu als eigener
  // Menupunkt (0) verwendet. D.h. das zu veraendernde Menu ist jetzt um einen
  // Eintrag verschoben => ACHTUNG! nur bei GetSubMenu wird MenuPos erhoeht!
  BOOL bMDI_IsMaximized = BOOL(HIWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
  HMENU hEditMenu = GetSubMenu (hMainMenu, (bMDI_IsMaximized ? MenuPos+1 : MenuPos));

  if (hTempMenu[MenuPos])
    DestroyMenu (hTempMenu[MenuPos]);
  hTempMenu[MenuPos] = LoadMenu (MyInstance, MenuID);
  HMENU hDialogMenu = GetSubMenu (hTempMenu[MenuPos], 0);

  ModifyMenu (hMainMenu, MenuPos, MF_POPUP | MF_BYPOSITION, UINT(hDialogMenu), MenuText);
  DrawMenuBar (hwndFrame);
  }
*/

static HCURSOR __hDDCursor = 0;
static int __CursorCount = 0;
void CreateDDCursor ()
  {
  if (__hDDCursor == 0) {
    __hDDCursor = LoadCursor (0, IDC_ARROW);
    }
  __CursorCount++ ;
  }

void DelDDCursor ()
  {
  __CursorCount-- ;
  if (__CursorCount == 0) {
    if (__hDDCursor)
      DestroyCursor (__hDDCursor);
    __hDDCursor = 0;
    }
  }


#ifdef TOOLTIP
inline void TextBlock::RelayMouseMessageToToolTip (HWND hWnd, UINT message, 
                                                   WPARAM wP, LPARAM lP)
  {
  if (IsWindow(hWndToolTip)) {
    MSG msg;
    msg.hwnd = hWnd;
    msg.message = message;
    msg.wParam = wP;
    msg.lParam = lP;

    SendMessage (hWndToolTip, TTM_RELAYEVENT, 0, LPARAM(LPMSG(&msg)));
    }
  }
#endif

#define   MAX_TOOLTIP_LEN   256

void TextBlock::GetTextFromMousePos (LPFILEBLOCK fbl, LPSTR szText, POINT pt)
  {
  static short useToolTips = -1;
  if (useToolTips < 0) {
    CHAR toolTips[10];
    GetPrivateProfileString ("EDITOR", "ToolTips", "yes", toolTips, sizeof(toolTips), IniFile());
    if (lstrcmp (toolTips, "no") != 0)
      useToolTips = 1;
    else
      useToolTips = 0;
    }
  int LineNr = pt.y / charHeight;
  int PosInLine = -1;

  LPLINE h = FirstVisibleLine;
  if (LineNr >= 0)
    for (int i = 0 ; ((i < LineNr) && (h->Next != NULL)) ; i++ , h = h->Next);
  else   
    for (int i = 0 ; ((i > LineNr) && (h->Prev != NULL)) ; i-- , h = h->Prev);

  if (h != NULL) {
    int charNr = (pt.x - GetXMin() + x0) / charWidth ;
    PosInLine = max(charNr, 0);

    if (PosInLine < lstrlen(h->Text)) {
      for (int b = PosInLine; (b > 0) ; b--)
        if (!IsWordChar(h->Text[b]) && (h->Text[b] != '.')) { b++ ; break ; }
      for (int e = PosInLine; ; e++)
        if (!IsWordChar(h->Text[e])) { e-- ; break ; }
        
      if (b <= e) {
        char szVar[MAX_TOOLTIP_LEN];
        char szRes[MAX_TOOLTIP_LEN];

        int len = min(MAX_TOOLTIP_LEN, e - b + 1);
        lmemcpy (szVar, h->Text + b, len);
        szVar[len] = '\0';

        szRes[0] = '\0';
        if (useToolTips) {
          WatchVar (fbl->dbinf,MyWnd,szVar,szRes);
  
          if (lstrcmp(szRes, "???") != 0)
            wsprintf (szText, "%s = %s", szVar, szRes);
          else 
            szText[0] = '\0';
          }
        else 
          szText[0] = '\0';
/*
        lstrcpy (szText, szVar);
        lstrcat (szText, " = ");
        lstrcat (szText, szRes);
*/
        }
      }
    }
  }


//---------------------------------------------------------------------------
// liefert das Fensterhandle des aktiven MDI-Childs, bzw. im Falle eines
// Script-Fensters das Fensterhandle des Text-Editors.
//---------------------------------------------------------------------------
BOOL IsScriptActive()
  {
  HWND hWnd = GetFocus();
  if (IsWindow(hWnd)) {
    char szClassName[64];

    GetClassName (hWnd, szClassName, sizeof(szClassName));
    if (lstrcmp(szClassName, "SCWND") == 0)
      return TRUE;
    else
      return FALSE;
    }
  else
    return FALSE;
  }

#define M_STATE_NONE       0
#define M_STATE_WONELE     1
#define M_STATE_MOVETEXT   2
#define M_STATE_SELECTTEXT 3
#define M_STATE_DRAGDROP   4

extern BOOL GenTbScript (HWND hWnd,LPSTR fname);
extern BOOL GenRepScript (HWND hWnd,LPSTR fname);
extern BOOL GenIntScript (HWND hWnd,LPSTR fname);
extern BOOL GenGScript (HWND hWnd,LPSTR fname);
extern BOOL doCaseSensitive();
extern BOOL doWholeWord();
extern void SetDoCaseSensitive(BOOL value);
extern void SetDoWholeWord(BOOL value);
extern void CheckClearUp ();
extern void SetCheck (BOOL value);
extern void SetCheckToMakeFile (BOOL value);
extern BOOL GenerateNextSource (BOOL *error);
extern BOOL SortSourcesToGenerate (HWND hWnd);
extern BOOL IsCheckToMakeFile ();
extern BOOL ExistEntry ();
extern BOOL WriteSourcesToMakeFile (LPSTR fName);
extern void MarkSourceGenerated (LPSTR FileName);
extern void MarkModuleForCheck (HWND hWnd, LPSTR modulName);
extern void PushToMakeFile (LPSTR FileName);

DLLExport LONG _export FAR PASCAL ShowProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  /*
   * If we get the Find/Replace message, pass it to a handler doing
   * the appropriate typecast of lParam to a pointer to a FINDREPLACE.
   */
  if (msg == iMSGFind)
      return LSearchMessageHandler(hWnd, (LPFINDREPLACE)lP);

  LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hWnd,GWL_TEXTBLOCK));

  static WORD MouseState = M_STATE_NONE;
  static char szToolTipText[MAX_TOOLTIP_LEN];

#ifdef WIN32
  HRGN hRgnText = HRGN(GetWindowLong(hWnd, 4));
#else
  HRGN hRgnText = LOWORD(GetWindowLong(hWnd, 4));
#endif

  LONG RetVal = 0L;
  switch (msg) {
    //--------------------------------------------------------------------
    case WM_CREATE :
      fbl = LPFILEBLOCK (((LPCREATESTRUCT)(lP))->lpCreateParams);
      // INCLUDE-Dateien nur dann checken wenn es ein Haupt-Script ist!
      if (fbl->MainFile)
        fbl->CreateIncludes (hWnd);
      fbl->SetCaption (hWnd);
      fbl->CreateDefHash ();
      SetWindowLong (hWnd,GWL_TEXTBLOCK,LONG (fbl));

      hRgnText = CreateRectRgn (0, 0, 10, 10);
#ifdef WIN32
      SetWindowLong (hWnd, 4, (LONG)hRgnText);
#else
      SetWindowLong (hWnd, 4, MAKELONG(hRgnText, 0));
#endif

      fbl->actblock->editdrop = new Editor_Drop (hWnd, hWnd);
      fbl->actblock->editdrop->AddType (DDTYPE_TABLE);
      fbl->actblock->editdrop->AddType (DDTYPE_VARNAME);
      fbl->actblock->editdrop->AddType (DDTYPE_INTTABLE);

      CreateDDCursor ();

#ifdef TOOLTIP
      fbl->actblock->hWndToolTip = DoCreateDataTip (hWnd);
#endif

      SaveAllWorkSpaceEntrys (NULL);
      break ;
    //--------------------------------------------------------------------
    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd, &ps) ;

      if (hRgnText)
        SelectClipRgn (hDC, hRgnText);
      fbl->Paint (hWnd, hDC, ps.rcPaint);
      SelectClipRgn (hDC, NULL);
      EndPaint (hWnd, &ps) ;
      }
      break ;
    //--------------------------------------------------------------------
    case WM_SIZE :
      if (hRgnText != 0)
        SetRectRgn (hRgnText, GetXMin(), 0, LOWORD(lP), HIWORD(lP));

    case WM_MOVE :
      WriteScWndPos (hWnd);
      if (fbl != NULL)
        fbl->actblock->SetScrollers (hWnd);
      break ;

#ifdef TOOLTIP
    //--------------------------------------------------------------------
    // WM_NOTIFY
    //--------------------------------------------------------------------
    case WM_NOTIFY :
      {
      NMHDR *lpnmh = (NMHDR *)lP;
      if (lpnmh->hwndFrom == fbl->actblock->hWndToolTip) {
        if (lpnmh->code == TTN_SHOW) {
          }
        else if (lpnmh->code == TTN_NEEDTEXT) {
          TOOLTIPTEXT *lpttt = (TOOLTIPTEXT *)lP;
          // char szBuf[MAX_TOOLTIP_LEN];
          POINT pt;
          RECT rc;

          GetCursorPos (&pt);
          ScreenToClient (hWnd, &pt);

          GetClientRect (hWnd, &rc);
          if (PtInRect(&rc, pt)) {

//            char szText[MAX_TOOLTIP_LEN];

            szToolTipText[0] = '\0';
            fbl->actblock->GetTextFromMousePos (fbl, szToolTipText, pt);

            lpttt->lpszText = szToolTipText;
            }
          }
        }
      }
      break;
#endif

    //--------------------------------------------------------------------
    case WM_LBUTTONDOWN :
      {
      if (GetActiveWindow() != hWnd)
        SetFocus (hWnd);

#ifdef TOOLTIP
      fbl->actblock->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);
#endif

      // Eigenschaftsfenster fuer die Dialogbearbeitung ist offen!
      if (IsDialogOpen()) {
        if (IsWOnEleOpen()) {
          MouseState = M_STATE_WONELE;
          fbl->FirstSelectedLine = fbl->LastSelectedLine = NULL;
          fbl->actblock->OnLButtonDown (hWnd, wP, lP);    // Cursor setzen
          fbl->actblock->OnLButtonDblClk (hWnd, wP, lP);  // Wort selektieren
          if (fbl->actblock->StartSel.Col != fbl->actblock->EndSel.Col)
            fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_TEXT, FALSE, fbl->actblock->SelWord);
          }  
        }
      else 
      // Text ist selektiert und der Cursor ist in der Selektion!!!
      if ((fbl->actblock->AlreadySelected) && (MouseState == M_STATE_DRAGDROP)) {
        HANDLE hText;
        fbl->actblock->CopySelectedTextToGlobalHandle (&hText);
        if (hText) {
          MouseState = M_STATE_MOVETEXT;
          if (fbl->actblock->SelWord != NULL)
            FreeGlobMem (fbl->actblock->SelWord);
          fbl->actblock->SelWord = LPSTR(GetGlobMem (UINT(GlobalSize(hText))));
          lstrcpy (fbl->actblock->SelWord, LPSTR(GlobalLock(hText)));
          GlobalUnlock (hText);
          GlobalFree (hText);
          hText = NULL;

          fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_EDITOR, FALSE, fbl->actblock->SelWord);
          }
        }
      // sonst beginne den Text zu selektieren
      else {
        MouseState = M_STATE_SELECTTEXT;
        fbl->FirstSelectedLine = fbl->LastSelectedLine = NULL;
        fbl->actblock->OnLButtonDown (hWnd, wP, lP);

        SetTimer (hWnd, 0, DELTA_T, NULL);
        }

      SetCapture (hWnd);
      }
      break ;
    //--------------------------------------------------------------------
    case WM_MOUSEMOVE :
      {
      switch (MouseState) {
        case M_STATE_SELECTTEXT:
          fbl->actblock->OnMouseMove (hWnd, wP, lP);
          break;
          
        case M_STATE_WONELE:  
          fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_TEXT, FALSE, fbl->actblock->SelWord);
          break;
          
        case M_STATE_MOVETEXT:
          // Zeigt durch das Caret die Position, an die der Text kopiert/verschoben wird.
          fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_EDITOR, FALSE, fbl->actblock->SelWord);
          fbl->actblock->SetCaretWithMouse (hWnd, LOWORD(lP), HIWORD(lP));
          break;

#ifdef TOOLTIP
        default:
          {
          fbl->actblock->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);

          if (IsWindow(fbl->actblock->hWndToolTip)) {
            POINT pt;
            pt.x = LOWORD(lP);
            pt.y = HIWORD(lP);

            char szText[MAX_TOOLTIP_LEN];

            szText[0] = '\0';
            fbl->actblock->GetTextFromMousePos (fbl, szText, pt);
            if ((szText[0] == '\0') || (lstrcmp(szText, szToolTipText))) {
              SendMessage (fbl->actblock->hWndToolTip, TTM_ACTIVATE, WPARAM(FALSE), 0);
              }

            if (szText[0] != '\0') {
              SendMessage (fbl->actblock->hWndToolTip, TTM_ACTIVATE, WPARAM(TRUE), 0);
              lstrcpy (szToolTipText, szText);
              }
            }
/*
          int i = HitTest(pt);
          if ((i < 0) || (i != iElement)) {
            SendMessage (hWndToolTip, TTM_ACTIVATE, WPARAM(FALSE), 0);
            }

          if (i >= 0) {
            SendMessage (hWndToolTip, TTM_ACTIVATE, WPARAM(TRUE), 0);
            iElement = i;
            }
*/
          }
#endif
        }
      }
      break ;
    //--------------------------------------------------------------------
    case WM_LBUTTONUP :
      {
      ReleaseCapture ();

#ifdef TOOLTIP
      fbl->actblock->RelayMouseMessageToToolTip (hWnd, msg, wP, lP);
#endif

      switch (MouseState) {
        case M_STATE_SELECTTEXT:
          KillTimer (hWnd, 0);
          fbl->actblock->OnLButtonUp (hWnd, wP, lP);
          fbl->GetDialogSelection();
          break;
          
        case M_STATE_WONELE:  
          fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_TEXT, TRUE, fbl->actblock->SelWord);
          break;
          
        case M_STATE_MOVETEXT:  
          fbl->CheckDrop (hWnd, LOWORD(lP), HIWORD(lP), DDTYPE_EDITOR, TRUE, fbl->actblock->SelWord);

          if (fbl->actblock->SelWord != NULL) {
            FreeGlobMem (fbl->actblock->SelWord);
            fbl->actblock->SelWord = NULL;
            }
          fbl->actblock->AlreadySelected = TRUE;
          fbl->actblock->InvalidateSelectedLines (hWnd);
          fbl->actblock->SetSelection (NULL, NULL);  
          fbl->actblock->InvalidateSelectedLines (hWnd);
          fbl->actblock->AlreadySelected = FALSE;
          break;
        }

      MouseState = M_STATE_NONE;
      }
      break ;
    //--------------------------------------------------------------------
    case WM_TIMER :
      if (MouseState == M_STATE_SELECTTEXT) {
        DWORD l = GetMessagePos ();
        POINT pt;
        pt.x = LOWORD(l);
        pt.y = HIWORD(l);
        ScreenToClient (hWnd,&pt);
        RECT r;
        GetClientRect (hWnd,&r);
        PostMessage (hWnd,WM_MOUSEMOVE,0,MAKELONG(pt.x, pt.y));
        }
      break;
    //--------------------------------------------------------------------
    case WM_LBUTTONDBLCLK :
      fbl->actblock->OnLButtonDblClk (hWnd, wP, lP);
      
      break;
    //--------------------------------------------------------------------
    case WM_KEYDOWN :
      if (!IsDialogOpen())
        fbl->actblock->OnKeyDown (hWnd, wP);
      break ;
    //--------------------------------------------------------------------
    case WM_CHAR :
      if (fbl->FirstSelectedLine != NULL)
        fbl->InvalidateSelected (hWnd,fbl->FirstSelectedLine,fbl->LastSelectedLine);
      fbl->FirstSelectedLine = fbl->LastSelectedLine = fbl->l1 = NULL;
      if (!IsDialogOpen())
        fbl->actblock->OnChar (hWnd,wP);
      break ;
    //--------------------------------------------------------------------
    case WM_HSCROLL :
      {
      LPTEXTBLOCK bl = fbl->actblock;
      int hPos = bl->x0 / bl->charWidth ;
      int hOldPos = hPos;
      RECT rc;
      GetClientRect (hWnd,&rc);
      int anz = (rc.right / bl->charWidth) / 2 ;
#ifdef WIN32
      switch (LOWORD(wP)) {
#else
      switch (wP) {
#endif
        case SB_BOTTOM    :
          hPos = bl->hmax;
          break ;
        case SB_TOP       :
          hPos = 0;
          break ;
        case SB_LINEUP    :
          if (hPos > 0) hPos -= 1;
          break ;
        case SB_LINEDOWN  :
          if (hPos < bl->hmax) hPos += 1;
          break ;
        case SB_PAGEUP    :
          if (hPos > anz) hPos -= anz;
          else          hPos = 0;
          break ;
        case SB_PAGEDOWN  :
          if (hPos < bl->hmax - anz) hPos += anz;
          else                       hPos = bl->hmax;
          break ;
        case SB_THUMBPOSITION :
#ifdef WIN32
          hPos = HIWORD(wP);
#else
          hPos = LOWORD(lP);
#endif
          break ;
        }
      if (hPos != hOldPos) {
        int x0 = hPos * bl->charWidth ;
        int dx = x0 - bl->x0;
        if (!fbl->CaptureDone)
          bl->HideCaretFrom (hWnd);

        RECT rc;
        GetClientRect (hWnd, &rc);
        rc.left += GetXMin();

        ScrollWindow (hWnd,-dx,0,NULL,&rc);
        bl->x0 = x0;
        SetScrollPos (hWnd,SB_HORZ,hPos,TRUE);
        UpdateWindow (hWnd);
        if (!fbl->CaptureDone)
          bl->ShowCaretIn (hWnd);
        }
      }
      break ;
    //--------------------------------------------------------------------
    case WM_VSCROLL :
      {
      LPTEXTBLOCK bl = fbl->actblock;
      int vPos = bl->GetAbsoluteLineNmbr(bl->FirstVisibleLine);
      int vOldPos = vPos;
      RECT rc;
      GetClientRect (hWnd,&rc);
      int anz = (rc.bottom / bl->charHeight) * 3 / 4 ;

#ifdef WIN32
      switch (LOWORD(wP)) {
#else
      switch (wP) {
#endif
        case SB_BOTTOM    :
          vPos = bl->vmax;
          break ;
        case SB_TOP       :
          vPos = 0;
          break ;
        case SB_LINEUP    :
          if (vPos > 0) vPos -= 1;
          break ;
        case SB_LINEDOWN  :
          if (vPos < bl->vmax) vPos += 1;
          break ;
        case SB_PAGEUP    :
          if (vPos > anz) vPos -= anz;
          else          vPos = 0;
          break ;
        case SB_PAGEDOWN  :
          if (vPos < bl->vmax - anz) vPos += anz;
          else                     vPos = bl->vmax;
          break ;
        case SB_THUMBPOSITION :
#ifdef WIN32
          vPos = HIWORD(wP);
#else
          vPos = LOWORD(lP);
#endif
          break ;
        }
      if (vPos != vOldPos) {
#ifdef NEWSCROLLER
        if ((vPos > ((bl->GesHeight - rc.bottom) / bl->charHeight) + 2) && (vPos >= vOldPos)) {
          // Wenn die neue obere Kante auf der letzten Seite ist und unter der alten liegt
          if (vOldPos > ((bl->GesHeight - rc.bottom) / bl->charHeight) + 2) 
            // und die alte obere Kante auch schon auf der letzten Seite war => nichts zu tun
            break;
          else
            // wenn wir vorher woanders waren => letzte Seite anzeigen
            vPos = ((bl->GesHeight - rc.bottom) / bl->charHeight) + 2;
          }
#endif
        y0    = vPos * bl->charHeight;    // erste Zeile (absolut)
        int y0old = vOldPos * bl->charHeight;
        int dy = y0 - y0old;                  // Anzahl Pixel um die gescrollt wird
        if (!fbl->CaptureDone)
          bl->HideCaretFrom (hWnd);
        bl->SetActLine (vPos);

        RECT rc;
        GetClientRect (hWnd, &rc);
        rc.left += GetXMin();
        ScrollWindow (hWnd,0,-dy,NULL,&rc);
#ifdef NEWSCROLLER
        SCROLLINFO si;

        si.cbSize = sizeof(si);
        si.fMask = SIF_POS;
        si.nPos = vPos;
        SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
#else
        SetScrollPos (hWnd,SB_VERT,vPos,TRUE);
#endif
        UpdateWindow (hWnd);
        if (!fbl->CaptureDone)
          bl->ShowCaretIn (hWnd);
        }
      }
      break ;

    //--------------------------------------------------------------------
    case WM_SETCURSOR :
      if (LOWORD(lP) == HTCLIENT) {
        MouseState = M_STATE_NONE;

        DWORD l = GetMessagePos ();
        POINT pt;
        pt.x = LOWORD(l);
        pt.y = HIWORD(l);
        ScreenToClient (hWnd,&pt);
        if ((pt.x <= XMIN) && (fbl != NULL)) {
          SetCursor (fbl->RightCursor);
          return TRUE ;
          }
        else 
        // wird der Cursor ueber einen selektierten Text bewegt, aendert sich 
        // seine Form


        if (fbl->actblock->AlreadySelected) {
          if (fbl->actblock->MouseInSelectedText (pt)) {
            MouseState = M_STATE_DRAGDROP;
            if (__hDDCursor) {
              SetCursor (__hDDCursor);
              }
            return TRUE ;
            }
          }  
        }
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;

    //--------------------------------------------------------------------
    // ACHTUNG:  da dies ein Kindfenster ist, bekommt es diese Nachricht
    //           NICHT!!! von Windows, sondern vom Parent (MDI-Child)!!!
    //--------------------------------------------------------------------
    case WM_SETFOCUS :
      if (!IsDialogOpen ()) {
        if ((fbl != NULL) && (fbl->actblock != NULL)) {
          fbl->ActivateList ();
          fbl->actblock->OnSetFocus (hWnd);
          }
        }
      break ;
    //--------------------------------------------------------------------
    case WM_KILLFOCUS :
      if (fbl != NULL)
        fbl->actblock->OnKillFocus (hWnd);
      break ;
    //--------------------------------------------------------------------

    case WMU_GETACTIVEWORD :
      lstrcpy (LPSTR(lP), fbl->ActiveWord ());
      break;

    case WMU_GETACTIVEPREFIX :
      lstrcpy (LPSTR(lP), fbl->actblock->fName);
      break;
    
    // wird von COMPILE aufgerufen, und setzt den Fehlertext
    case WMU_SETERRORTEXT :
      SetFieldColor (hWndStatusbar, STATBAR_TEXT, RGB(0xFF, 0xFF, 0xFF), RGB(0, 0, 0x80));
      SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, lP);
      break;
    
      
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDM_CUT:
        case IDM_COPY :
          if (IsScriptActive()) {
            fbl->actblock->CopyToClipBoard(hWnd);
            if (CRACKER_wID == IDM_CUT)
              fbl->actblock->DeleteSelectedLines(hWnd);
            }
          else
            if (CRACKER_wID == IDM_CUT)
              SendMessage (GetFocus(), WM_CUT, 0, 0);
            else if (CRACKER_wID == IDM_COPY)
              SendMessage (GetFocus(), WM_COPY, 0, 0);
          break;
        case IDM_PASTE:
          if (IsScriptActive())
            fbl->actblock->PasteFromClipBoard(hWnd);
          else
            SendMessage (GetFocus(), WM_PASTE, 0, 0);
          break;
        case IDM_DELLINE:
          if (IsScriptActive())
            fbl->actblock->DelLineWithCaret(hWnd);
          else
            SendMessage (GetFocus(), msg, wP, lP);
          break;
            
        case CMD_TB_BASE+100:
          SetFocus (hWndCombo);
          break;

        //-----------------------------------------------------------
        // Aufruf der RESTOOL-Hilfe
        case IDM_HELPONITEM:
          {
          char szPath[256];
          GetPrivateProfileString ("Help", "HelpPath", "", szPath, sizeof(szPath), IniFile());
          if (szPath[0] == '\0')
            lstrcpy (szPath, "RESTOOL.HLP");
          else
            lstrcat (szPath, "RESTOOL.HLP");
            
          OFSTRUCT of;
          if (OpenFile (szPath, &of, OF_EXIST) != HFILE_ERROR)
            WinHelp (hWnd, szPath, HELP_KEY, DWORD(fbl->ActiveWord ()));
          else
            MessageBox (hWnd, "Hilfe Datei konnte nicht gefunden werden", "RESTOOL.HLP", MB_OK);
          }
          break;

        case MI_CLOSESC :
          DestroyWindow (hWnd);
          break ;

        case IDM_FILECLOSE :
          SendMessage (GetParent(hWnd),WM_CLOSE,0L,0L);
          break ;

        case MI_STOREED :
          fbl->StoreFiles (hWnd);
          fbl->SetCaption (hWnd);
          SaveAllWorkSpaceEntrys (NULL);
          break ;
        case IDM_FILESAVEAS :
          fbl->StoreFilesUnder (hWnd);
          fbl->SetCaption (hWnd);
          SaveAllWorkSpaceEntrys (NULL);
          break ;
        case MI_GENMAKEFILE:
          if (IsCheckToMakeFile ()) {
            if (ExistEntry ()) {
              char makeFileName [256];
              if (GetStoreFileName (hWnd,"Makefile speichern",makeFileName,sizeof(makeFileName),3)) {
                SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Sorting Makefile")));
                SortSourcesToGenerate (hWnd) ;
                SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Writing Makefile")));
                if (WriteSourcesToMakeFile (makeFileName)) {
                  CheckClearUp();
                  ShowScript (NULL, makeFileName, TRUE);
                  }
                else {
                  int answer = MessageBox (hWnd, "Fehler beim Schreiben.\r\n\r\nWollen Sie es später noch einmal versuchen?", "Fehler",
                                           MB_ICONQUESTION | MB_YESNO);
                  if (answer == IDNO) {
                    CheckClearUp();
                    }
                  }
                SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("")));
                }
              else {
                int answer = MessageBox (hWnd, "Soll die Liste der Module verworfen werden?", "Makefile erzeugen abbrechen",
                                         MB_ICONQUESTION | MB_YESNO);
                if (answer == IDYES) {
                  CheckClearUp();
                  }
                }
              }
            else {
              CheckClearUp();
              }
            }
          else {
            SetCheck (TRUE);
            SetCheckToMakeFile (TRUE);
            }
          break;
        case MI_GENED :
        case MI_GENED_DEPEND :
          InitModuleHash ();
          BOOL checkOnly, compOk;
          checkOnly = FALSE;
          compOk = FALSE;

          if ((CRACKER_wID == MI_GENED_DEPEND) && !IsCheckToMakeFile ())
            SetCheck (TRUE);
          if (fbl->actblock->ErrorLine != NULL) {
            fbl->actblock->ErrorLine->ClearErrorLine();
            fbl->actblock->InvalidateLine (hWnd, fbl->actblock->ErrorLine);
            
            ResetFieldColor (hWndStatusbar, STATBAR_TEXT);
            
            char outtxt[] = "";
            SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
            }
          fbl->StoreFiles (hWnd);
          fbl->SetCaption (hWnd);
          SaveAllWorkSpaceEntrys (NULL);
          if (lstrcmp(GetExtension (fbl->actblock->fName),"MAK") == 0) {
            BOOL doGenerate = TRUE;
            if (IsCheckToMakeFile ()) {
              int answer = MessageBox (hWnd, "Sollen wirklich alle Einträge im aktuellen Makefile generiert werden, und mit ihren Abhängigkeiten ins neue Makefile aufgenommen werden?", "Makefile mit Abhängigkeiten generieren",
                                       MB_ICONQUESTION | MB_YESNO);
              doGenerate = (answer == IDYES);
              }
            else if (CRACKER_wID == MI_GENED_DEPEND) {
              int answer = MessageBox (hWnd, "Sollen die Einträge im aktuellen Makefile nach den Abhängigkeiten sortiert und in einem neuem Makefile gespeichert werden?\r\rACHTUNG! Funktionsprototypen, Resourcen und Kommentare gehen verloren!", "Makefile nach Abhängigkeiten sortieren",
                                       MB_ICONQUESTION | MB_YESNO);
              if (answer == IDYES)
                checkOnly = TRUE;
              else
                doGenerate = FALSE;
              }
            if (doGenerate) {
              FreeMsgs ();
              CHAR wndName[128];
              lstrcpy (wndName, "Make ");
              lstrcat (wndName, GetFName (fbl->actblock->fName));
              HWND hWndChild = MakeNewChild (wndName);
              compOk = GenerateFull (hWndChild, fbl->actblock->fName, checkOnly); 
              if (!compOk) fbl->CheckError (hWnd);
              }
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"PTY") == 0) {
            compOk = GenFncProt (hWnd,fbl->actblock->fName);
            if (!compOk) 
              fbl->CheckError (hWnd);
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"DDD") == 0) {
            compOk = GenTbScript (hWnd,fbl->actblock->fName);
            if (!compOk) fbl->CheckError (hWnd);
            else MarkSourceGenerated (GetFName (fbl->actblock->fName));
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"REP") == 0) {
            compOk = GenRepScript (hWnd,fbl->actblock->fName);
            if (!compOk) fbl->CheckError (hWnd);
            else MarkSourceGenerated (GetFName (fbl->actblock->fName));
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"IDD") == 0) {
            compOk = GenIntScript (hWnd,fbl->actblock->fName);
            if (!compOk) fbl->CheckError (hWnd);
            else MarkSourceGenerated (GetFName (fbl->actblock->fName));
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"GDD") == 0) {
            compOk = GenGScript (hWnd,fbl->actblock->fName);
            if (!compOk) fbl->CheckError (hWnd);
            else MarkSourceGenerated (GetFName (fbl->actblock->fName));
            }
          else if (lstrcmp(GetExtension (fbl->actblock->fName),"MOD") == 0) {
            int res = DoCompileMod (hWnd,fbl->actblock->fName);
            if (res != 0) {
              fbl->CheckError (hWnd);
              compOk = FALSE;
              }
            else {
              MarkModuleForCheck (hWnd, GetFName (fbl->actblock->fName));
              CreateScriptContent(fbl->actblock->fName);
              ClearCachedProg (fbl->actblock->fName);
              if (fbl->dbinf != NULL) delete fbl->dbinf;
              fbl->dbinf = new ScDebugInfo (fbl->actblock->fName);
              DestroyBreakPointsFrom (fbl->actblock->fName);
              MarkSourceGenerated (GetFName (fbl->actblock->fName));
              compOk = TRUE;
              }
            }
          else {
            if (fbl->actblock->fName) {
              compOk = GenerateScript (hWnd,fbl->actblock->fName);
              if (compOk) {
                CreateScriptContent(fbl->actblock->fName);
                ClearCachedProg (fbl->actblock->fName);
                if (fbl->dbinf != NULL) delete fbl->dbinf;
                fbl->dbinf = new ScDebugInfo (fbl->actblock->fName);
                DestroyBreakPointsFrom (fbl->actblock->fName);
                MarkSourceGenerated (GetFName (fbl->actblock->fName));
                }
              else {
                // Ein Error ist gefunden
                fbl->CheckError (hWnd);
                }
              }
            else
              MessageBeep (0);
            }
          if ((CRACKER_wID == MI_GENED_DEPEND) && !IsCheckToMakeFile ()) {
            SetCheck (FALSE);
            SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Sorting Modules")));
            SortSourcesToGenerate (hWnd) ;
            if (checkOnly) {
              char makeFileName [256];
              if (GetStoreFileName (hWnd,"Sortiertes Makefile speichern",makeFileName,sizeof(makeFileName),3)) {
                int answer = IDNO;
                do {
                  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Writing Makefile")));
                  if (!WriteSourcesToMakeFile (makeFileName))
                    answer = MessageBox (hWnd, "Fehler beim Schreiben.\r\n\r\nWollen Sie es noch einmal versuchen?", "Fehler",
                                         MB_ICONQUESTION | MB_YESNO);
                  else {
                    answer = IDNO;
                    ShowScript (NULL, makeFileName, TRUE);
                    }
                  }
                while (answer == IDYES);
                }
              SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("")));
              }
            else {
              BOOL compError;
              SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Compiling")));
              for ( ; GenerateNextSource (&compError) ; ) ;
              if (compError) {
                fbl->CheckError (hWnd);
                compOk = FALSE;
                }
              else
                compOk = TRUE;
              }
            CheckClearUp();
            }
          if (compOk)
            SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Compilation successful.")));
          DoneModuleHash ();
          break ;
        case MI_SETBREAK :
          if (fbl->dbinf != NULL) {
            if (fbl->dbinf->SetBreakPoint (fbl->actblock->YAbsCaret+1,fbl->actblock->fName)) {
              // Invalidieren der aktuellen Zeile
              fbl->actblock->InvalidateLine (hWnd,fbl->actblock->LineWithCaret);
              }
            else
              MessageBeep (0);
            }
          break ;
        case MI_RUN :
          RunDDS();
          break ;
        case MI_STEP :
          StepDDS();
          break ;
        case MI_STEPINTO :
          StepIntoDDS();
          break ;
        case MI_WATCHVAR :
          WatchVar (fbl->dbinf,hWnd,fbl->ActiveWord());
          break ;
        case MI_SHOWSTACK :
          WatchStack (hWnd);
          break ;
        case MI_SHOWUPDATE :
          WatchUpdateList (hWnd);
          break ;
        case MI_CREATEWATCH :
          AddWatchLine (fbl->ActiveWord(),fbl->actblock->fName,GetActContext(fbl->actblock->fName));
          break ;

        // slektierten Bereich analysieren und Dialog aufbauen
        case MI_DIALED :
          fbl->GetDialogSelection ();
          if ((fbl->FirstSelectedLine != NULL) && (AllowAnalyse())) {
#ifdef WIN32
            SendMessage (hwndMDIClient, WM_MDISETMENU, 
                         (WPARAM)hMenuDialog, (LPARAM)hMenuDialogWindow) ;
#else
            SendMessage (hwndMDIClient, WM_MDISETMENU, 0,
                         MAKELONG (hMenuDialog, hMenuDialogWindow)) ;
#endif
            DrawMenuBar (hwndFrame);

#ifdef WIN32
            SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, LPARAM(hWndToolbarDialog));
#else          
            SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, MAKELONG(hWndToolbarDialog, 0));
#endif
            AnalyseBlock (hWnd,
                          fbl->actblock,
                          fbl->FirstDialogLine = fbl->FirstSelectedLine,
                          fbl->LastDialogLine = fbl->LastSelectedLine,
                          defHash);
            }
          else
            MessageBeep (0);
          break ;

        case MI_STOREDIALOG :
          if (StoreDialog (fbl->actblock, &fbl->LastDialogLine, &fbl->FirstDialogLine)) {
            fbl->FirstSelectedLine = fbl->FirstDialogLine;
            fbl->LastSelectedLine  = fbl->LastDialogLine;
            // eventuelle Zeilenaenderungen an den Textblock weitergeben
            fbl->actblock->SetSelection (fbl->FirstSelectedLine, fbl->LastSelectedLine);

            fbl->SetCaption (hWnd);
            fbl->actblock->SetScrollers (hWnd);
            InvalidateRect (hWnd,NULL,TRUE);
            SetWindowPos (hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
            }
          else
            MessageBeep (0);

#ifdef WIN32
          SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, LPARAM(hWndToolbarDialog));
          SendMessage (hwndMDIClient, WM_MDISETMENU, 
                       (WPARAM)hMenuMain, (LPARAM)hMenuMainWindow) ;
#else
          SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWndToolbarDialog, 0));
          SendMessage (hwndMDIClient, WM_MDISETMENU, 0,
                       MAKELONG (hMenuMain, hMenuMainWindow)) ;
#endif

          DrawMenuBar (hwndFrame);

          break ;

        case MI_DESTROYDIALOG :
          {
          if (!DestroyEdDialog ())
            MessageBeep (0);
          else
            SetWindowPos (hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

#ifdef WIN32
          SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, LPARAM(hWndToolbarDialog));
          SendMessage (hwndMDIClient, WM_MDISETMENU, 
                       (WPARAM)hMenuMain, (LPARAM)hMenuMainWindow) ;
#else
          SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWndToolbarDialog, 0));
          SendMessage (hwndMDIClient, WM_MDISETMENU, 0,
                       MAKELONG (hMenuMain, hMenuMainWindow)) ;
#endif

          DrawMenuBar (hwndFrame);
#ifdef WIN32
          SetForegroundWindow (hWnd);
#endif
          }  
          break ;

        case MI_DUPLICATE :
          Duplicate ();
          break ;
        case MI_WORKONELE :
          if (!WorkOnEle (hWnd))
            MessageBeep (0);
          break ;
        case MI_MOVEELEMES :
          if (!MoveElems ())
            MessageBeep (0);
          break ;
        case MI_WORKONSCREEN :
          if (!WorkOnScreen (hWnd))
            MessageBeep (0);
          break ;
        case MI_DELELE :
          if (!RemoveCommand ())
            MessageBeep (0);
          break ;

        case MI_INSERTTEMPLATE :
          {
          ShowDialogWithTemplates (hWnd);
          }
          break;
          
        case MI_INSETDLGBSP :
          if (fbl->LastSelectedLine != NULL) {
            fbl->InsertBsp (hWnd);
            fbl->SetCaption (hWnd);
            }
          else
            MessageBeep (0);
          break ;
        case MI_SEARCH :
        case MI_REPLACE :
          {
          LPSTR SearchStr = fbl->ActiveWord();  // Wort auf dem der Cursor steht
          if ((SearchStr == NULL) || (*SearchStr == '\0'))   // nix Wort da
            SearchStr = SearchCombo.GetTopString();          // dann nimm' altes

          LPSTR ReplaceStr = ReplaceCombo.GetTopString(TRUE);
          SearchDialogs(hWnd, CRACKER_wID, SearchStr, ReplaceStr);
          }
          break ;
        case MI_SEARCHCASE:
          SetDoCaseSensitive (!doCaseSensitive ());
          break;
        case MI_SEARCHWORD:
          SetDoWholeWord (!doWholeWord ());
          break;
        case MI_SEARCHMORE :
        case MI_REPLACEMORE :
        case MI_SEARCHUP:
        case MI_REPLACEALL :
          {
          LPSTR SearchWord;
          //-----------------------------------------------------------------
          // wurde in der Such-Combobox RETURN gedrueckt (neues Wort suchen)?
          //-----------------------------------------------------------------
          if (lP == 0) {                                      // nein
            if (GetFocus () != GetWindow(hWndCombo, GW_CHILD)) {
              if (fbl->actblock->SelWord != NULL) {
                if (SearchCombo.InsertEntry (fbl->actblock->SelWord,FALSE,doCaseSensitive())) {
                  SearchCombo.WriteEntrys();
                  SendMessage (hWndCombo, WM_SETTEXT, 0, LPARAM(fbl->actblock->SelWord));
                  }
                }
              }
            else {
              SearchCombo.OnVKReturn (hWndCombo, FALSE, doCaseSensitive ());
              SendMessage (hwndMDIClient,WM_MDIACTIVATE,WPARAM(HWND(GetParent(GetScWnd()))),0L);
              SetFocus (GetScWnd());
              }
            SearchWord = SearchCombo.GetTopString();
            }
          else {
            //-----------------------------------
            // ja, dann Wort aus der Combo-Liste!
            //-----------------------------------
            SearchWord = SearchCombo.GetTopString();
            SendMessage (hwndMDIClient,WM_MDIACTIVATE,WPARAM(HWND(GetParent(GetScWnd()))),0L);
            SetFocus (GetScWnd());
            }

          if (CRACKER_wID == MI_SEARCHUP)
            fbl->actblock->SearchUp (hWnd, SearchWord,
                                     doCaseSensitive(),doWholeWord()
                                    );
          else if (CRACKER_wID == MI_REPLACEALL) {
            for ( ; fbl->actblock->Search (hWnd, SearchWord,
                              ReplaceCombo.GetTopString(TRUE), doCaseSensitive(),
                              (CRACKER_wID == MI_SEARCHMORE) ? FALSE : TRUE,
                              doWholeWord()
                             ) ; ) ;
            }
          else
            fbl->actblock->Search (hWnd, SearchWord,
                              ReplaceCombo.GetTopString(TRUE), doCaseSensitive(),
                              (CRACKER_wID == MI_SEARCHMORE) ? FALSE : TRUE,
                              doWholeWord()
                             );
          }
          break ;

        case MI_TOGGLEBOOKMARK :
          fbl->actblock->LineWithCaret->ToggleBookMark ();
          fbl->actblock->InvalidateLine (hWnd,fbl->actblock->LineWithCaret);
          break;
          
        case MI_NEXTBOOKMARK :
        case MI_PREVBOOKMARK :
          fbl->actblock->GotoBookMark (CRACKER_wID);
          break;
          
        case MI_NEWHLINE :
          if (HLineAllowed ()) {
            hLineType = HLINE_HORZ;
            SetCapture (GetHLineWnd());
            InitializeHMove ();
            InHLineEdit = TRUE ;
            }
          else
            MessageBeep (0);
          break ;
        case MI_NEWVLINE :
          if (HLineAllowed ()) {
            hLineType = HLINE_VERT;
            SetCapture (GetHLineWnd());
            InitializeHMove ();
            InHLineEdit = TRUE ;
            }
          else
            MessageBeep (0);
          break ;
        case MI_DELHLINE :
          if (HLineAllowed ())
            DeleteHLine ();
          else
            MessageBeep (0);
          break ;
        case MI_MULTIHLINE  :
          if (HLineAllowed ())
            SetMultiHLine ();
          else
            MessageBeep (0);
          break ;
        case MI_WORKONHLINE :
          if (HLineAllowed ())
            WorkOnHLine ();
          else
            MessageBeep (0);
          break ;
        case MI_SHOWSORT :
          TogglePaintNums();
          break ;
        case MI_INDENVORDERGRUND :
          IndenVordergrund ();
          break ;
        case MI_INDENHINTERGRUND :
          IndenHintergrund ();
          break ;

        case MI_SHOWRASTER :
          {
          BOOL bRaster = LOWORD(SendMessage (hWndToolbarDialog, TB_ISBUTTONCHECKED, MI_SHOWRASTER, 0));
          SetDialogRaster (bRaster);
//          InvalidateRect (hWndPaint, NULL, TRUE);
          }
          break;

        case MI_FINDMATCHINGBRACES :
          fbl->actblock->FindMatchingBraces (hWnd, TRUE, TRUE);

        default :
          if ((CRACKER_wID >= MI_INCLUDE) && (CRACKER_wID < MI_DLGCOMMAND)) {
              MessageBeep (0);
            }
          if (CRACKER_wID >= MI_DLGCOMMAND) {
            InsertCommand (CRACKER_wID);
            }
          break ;
        }
      }
      break ;
    //--------------------------------------------------------------------
    case WM_DESTROY :
      {
      if (fbl->MainFile) {   // eine Hauptdatei muss die Include-Listbox leeren
#ifdef WIN32
        HWND hWndList = (HWND)GetWindowLong (hWndProjectList, GWW_LISTWINDOW);
#else
        HWND hWndList = GetWindowWord (hWndProjectList, GWW_LISTWINDOW);
#endif
        SendMessage (hWndList, LB_RESETCONTENT, 0, 0L);
        }
      if (hRgnText != 0)
        DeleteObject (hRgnText);
        
      DelDDCursor ();
      fbl->actblock->editdrop->RemoveFromList ();
      hScriptWindow = 0;
      DestroyEdDialog ();
      delete defHash;
      defHash = NULL;
      delete fbl;
      DelStrBuffer ();
      }
      break ;
      
    case WMU_FONTHASCHANGED :
      fbl->actblock->TextMetrics ();
      InvalidateRect (hWnd, NULL, TRUE);
      UpdateWindow (hWnd);
      break;
        
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;
    }
  return RetVal;
  }

void RegisterScriptWin ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    wndclass.lpfnWndProc   = ShowProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 2*sizeof(LPTEXTBLOCK);
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_IBEAM) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = "SCWND" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }


//---------------------  Editor_Drop::DoDrop  -------------------------------
//
// Reagiert auf das Fallenlassen von Elementen im Text-Editor
//---------------------------------------------------------------------------
void Editor_Drop::DoDrop (LPVOID Data, WORD Type)
  {
  POINT pt;
  DWORD dw = GetMessagePos();
  pt.x = LOWORD(dw);
  pt.y = HIWORD(dw);
        
  ScreenToClient (DropWnd, &pt);

  switch (Type) {
    case DDTYPE_TABLE:
    case DDTYPE_VARNAME:
    case DDTYPE_INTTABLE:
      {
      LPSTR TableName = LPSTR (Data);
      char buffer[256];
      if (Type == DDTYPE_VARNAME) {
        LPSTR VarName = LPSTR(Data);
        wsprintf (buffer,"%s.%s",VarName + lstrlen(VarName) + 1,VarName);
        TableName = buffer ;
        }
      
      LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (DropWnd,GWL_TEXTBLOCK));
      if ((fbl != NULL) && (fbl->actblock != NULL)) {
        SetFocus (DropWnd);
        SendMessage (hwndMDIClient,WM_MDIACTIVATE,WPARAM(HWND(GetParent(DropWnd))),0L);
        fbl->actblock->SetCaretWithMouse (DropWnd, pt.x, pt.y);
        fbl->actblock->LineWithCaret->InsertText (TableName, fbl->actblock->iCaret);
        fbl->actblock->SetModified();
        fbl->SetCaption (DropWnd);

        RECT rc;
        GetClientRect (DropWnd, &rc);
        rc.top = fbl->actblock->YCaret * fbl->actblock->charHeight;
        rc.bottom = rc.top + fbl->actblock->charHeight;
        InvalidateRect (DropWnd, &rc, TRUE);
        }
      }
      break;

    // Verschieben oder Kopieren innerhalb des Editors
    case DDTYPE_EDITOR:
      {
      LPSTR TextBlock = LPSTR(Data);

      LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (DropWnd,GWL_TEXTBLOCK));
      if ((fbl != NULL) && (fbl->actblock != NULL)) {

        if (!fbl->actblock->MouseInSelectedText (pt)) {
          // bei gedrueckter SHIFT-Taste wird der Text verschoben
          if (GetKeyState(VK_SHIFT) < 0)
            fbl->actblock->DeleteSelectedLines(DropWnd);
  
          fbl->actblock->SetCaretWithMouse (DropWnd, pt.x, pt.y);
          fbl->actblock->InsertLinesInTextFromBuffer (DropWnd, TextBlock);
          }
        }  
      }
      break;
    }
  }


//---------------------------------------------------------------------------
// liefert das Fensterhandle des aktiven MDI-Childs, bzw. im Falle eines
// Script-Fensters das Fensterhandle des Text-Editors.
//---------------------------------------------------------------------------
HWND GetScWnd()
  {
#ifdef WIN32
  HWND hWnd = HWND(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL));
#else
  HWND hWnd = HWND(LOWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
  if (IsWindow(hWnd)) {
    char szClassName[64];

    GetClassName (hWnd, szClassName, sizeof(szClassName));
    if (lstrcmp(szClassName, "bland child") == 0)
      hScriptWindow = GetWindow (hWnd, GW_CHILD);
    else
      hScriptWindow = hWnd;  
    }
  else
    hScriptWindow = 0;
  return hScriptWindow;
  }

//-------------------------  GetEditorWindow  -------------------------------
//
// liefert nur das HANDLE des echten Editors
//---------------------------------------------------------------------------
HWND GetEditorWindow ()
  {
#ifdef WIN32
  HWND hWnd = HWND(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L));
#else
  HWND hWnd = HWND(LOWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif

  if (IsWindow(hWnd)) {
    char szClassName[64];

    GetClassName (hWnd, szClassName, sizeof(szClassName));
    if (lstrcmp(szClassName, "bland child") == 0)
      hWnd = GetWindow (hWnd, GW_CHILD);
    else
      hWnd = 0;  
    }  
  return hWnd;
  }

//-------------------------  GetEditorMDI  ----------------------------------
//
// liefert das HANDLE des MDI-Fensters vom Text-Editor
//---------------------------------------------------------------------------
HWND GetEditorMDI ()
  {
#ifdef WIN32
  HWND hWnd = HWND(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L));
#else
  HWND hWnd = HWND(LOWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif

  if (IsWindow(hWnd)) {
    char szClassName[64];

    GetClassName (hWnd, szClassName, sizeof(szClassName));
    if (lstrcmp(szClassName, "bland child") != 0)
      hWnd = 0;
    }

  return hWnd;
  }

void ShowScript (HWND hParent,FileBlock FAR *fbl,LPSTR fname,BOOL MainFile)
  {
  RegisterScriptWin ();
  // konnte mit dieser Datei eine neue Klasse erzeugt werden?
  if (fbl->actblock) {
    if (MainFile) {
      fbl->MainFile = TRUE;
      fbl->dbinf = new ScDebugInfo (fname);
      }

    RECT rc;
    GetClientRect (hParent, &rc);
    int x,y,w,h;
    ReadScWndPos (&x,&y,&w,&h);
    HWND hWnd /*hScriptWindow*/ = CreateWindow (
                                  "SCWND",
                                  "",
                                  WS_CHILD | WS_CLIPSIBLINGS | 
                                  WS_HSCROLL | WS_VSCROLL |
                                  WS_VISIBLE ,
                                  rc.left,rc.top,
                                  rc.right-rc.left, rc.bottom-rc.top,
                                  hParent,
                                  0, /*hMenu,*/
                                  MyInstance,
                                  fbl
                                 );
    fbl->actblock->MyWnd = hWnd;
    BOOL bFlag = IsWindow(hWnd);
    if (bFlag) {
      }

    SendMessage (hWndToolbar, TB_ENABLEBUTTON, IDB_PROJECTFILES, MAKELONG(bFlag, 0));
    SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_SEARCHMORE, MAKELONG(bFlag, 0));
    fbl->SetCaretTo (hWnd,1,1); // Caret soll nicht ganz links aussen stehen, sondern am Textrand
    }
  }

HWND ShowScript (HWND hParent,LPSTR fname,BOOL MainFile)
  {
  RegisterScriptWin ();
  FileBlock FAR *fbl = new FileBlock (fname);
  if (fbl->actblock == NULL) {
    delete fbl;
    char outstring[256];
    wsprintf (outstring,"Kann %s nicht finden,\reventuell zuerst mit PVCS holen !",fname);
    MessageBox (hParent,outstring,"Fehler",MB_OK | MB_TASKMODAL);
    return NULL;
    }
  else {
    if (hParent == NULL)
      hParent = MakeNewChild (fname);
    ShowScript (hParent,fbl,fname,MainFile);
    return hParent;
    }
  }

void ShowScript (HWND hParent,GLOBALHANDLE hGTxt,BOOL MainFile)
  {
  RegisterScriptWin ();
  FileBlock FAR *fbl = new FileBlock (hGTxt);
  if (fbl->actblock != NULL)
    ShowScript (hParent,fbl,NULL,FALSE);
  }

DLLExport BOOL FAR PASCAL _export BspDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_COMMAND :
      switch (wP) {
        case IDOK :
          GetDlgItemText (hDlg,ID_SCREENNAME,ScreenName,sizeof(ScreenName));
          GetDlgItemText (hDlg,ID_OBJECTNAME,ObjectName,sizeof(ObjectName));
          EndDialog (hDlg,TRUE);
          break ;
        case IDCANCEL :
          EndDialog (hDlg,FALSE);
          break ;
        }
      break ;
    }
  return RetVal;
  }

//-----------------------  InsertTextIntoScript  ----------------------------
//
// fuegt den Text <text> an der aktuellen Caret-Position ein. Endet der Text
// mit CR-LF wird das Caret an die nullte Position der naechsten Zeile bewegt.
//---------------------------------------------------------------------------
void InsertTextIntoScript (LPSTR text)
  {
  HWND hWndScript = GetScWnd ();
  if (IsWindow(hWndScript)) {
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hWndScript, GWL_TEXTBLOCK));
    fbl->actblock->InsertLinesInTextFromBuffer (hWndScript, text);
    }
  }

BOOL SearchTextInScript (LPSTR SearchText, BOOL bCaseSensitive, BOOL bSearchDown)
  {
  BOOL ret = FALSE;
  HWND hWndScript = GetScWnd ();
  if (IsWindow(hWndScript)) {
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hWndScript, GWL_TEXTBLOCK));
    ret = fbl->actblock->SearchIt (FALSE, hWndScript, SearchText, NULL, bCaseSensitive, FALSE, TRUE, 
                                   bSearchDown, FALSE);
    }
  return ret;  
  }

BOOL IsScriptOpen()
  {
  return (GetScWnd() != NULL);
  }

GLOBALHANDLE GetSrcText (HWND hWnd)
  {
  LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hWnd,GWL_TEXTBLOCK));
  if (fbl != NULL) {
    return fbl->actblock->StoreToHandle (hWnd);
    }
  return NULL;
  }

BOOL InvlidateBreakLine (HWND hWnd,LPSTR FName,int LineNmbr)
  {
  HWND hScWnd = GetWindow (hWnd,GW_CHILD);
  if (hScWnd) {
    LPFILEBLOCK fbl = LPFILEBLOCK (GetWindowLong (hScWnd,GWL_TEXTBLOCK));
    if (fbl->actblock->fName == NULL) return FALSE;
    if (lstrcmp (GetFName (fbl->actblock->fName),FName) == 0) {
      LPLINE h = fbl->actblock->GetLineFromLineNr (LineNmbr);
      if (h != NULL)
        fbl->actblock->InvalidateLine (hWnd, h);
      return TRUE ;
      }
    }
  return FALSE ;
  }

