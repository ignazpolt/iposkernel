//////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/cfield.hpv   1.75   03 Sep 1999 05:03:10   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/cfield.hpv  $
// 
//    Rev 1.75   03 Sep 1999 05:03:10   Hannes
// Einrueckung aktiviert...
// 
//    Rev 1.74   16 Aug 1999 18:38:02   Hannes
// Verbesserungen SlantFields
// 
//    Rev 1.73   04 Aug 1999 18:27:36   Wolfgang
// 1.) CheckDirKey hat zusaetzlichen Parameter keyToUse.
// 
//    Rev 1.72   27 Jun 1999 21:55:22   Hannes
// Hilfsfunktionen fuer Rechtschreibpruefung
// 
//    Rev 1.71   02 Feb 1999 21:29:06   Hannes
// SlantFieldHandling
// 
//    Rev 1.70   18 Nov 1998 15:49:08   Hannes
// Diverse Verbesserungen am Farbhandling
// 
//    Rev 1.69   09 Oct 1998 18:14:08   Hannes
// Farben in Strings
// 
//    Rev 1.68   09 Aug 1998 22:39:56   Hannes
// Verbesserungen Kontextmenue
// 
//    Rev 1.67   16 Feb 1998 08:06:52   Gerhold
// VC++5.x ... explicit darf nicht als Var. verwendet werden (Schluesselwort)
// 
//    Rev 1.66   19 Nov 1997 18:45:20   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.65   22 Apr 1997 12:09:42   Hannes
// 
//    Rev 1.64   10 Apr 1997 11:39:26   Hannes
// WWSelectionInString,Prototyp von WWNextExplicit
// 
//    Rev 1.63   21 Mar 1997 11:30:44   Hannes
// IsKeyToUse
// 
//    Rev 1.62   03 Mar 1997 11:46:54   Hannes
// WWNextExplicit, SetDefFormat, GetWidth(),GetDefFromat()
// 
//    Rev 1.61   28 Feb 1997 14:37:28   Martin
// SkipFormat und SkipPrevFormat exportiert
// 
//    Rev 1.60   28 Feb 1997 14:26:56   Hannes
// SetCaretTo,WWSetCaretTo
// 
//    Rev 1.59   19 Feb 1997 12:00:24   Hannes
// OnKillFocusIf,InsertStringAtCaret
// 
//    Rev 1.58   28 Sep 1996 15:52:22   GERHOLD
// FM_NOSELECTIONONFOCUS, BOOL SelectFocusedFields, function SetFocusFlag
// 
//    Rev 1.57   18 Sep 1996 20:48:58   HANNES
// 
//    Rev 1.56   05 Sep 1996 14:01:46   GERHOLD
// cField::IsSomeTextSelected, WWIsFieldSelected
// 
//    Rev 1.55   16 Jun 1996 18:51:30   GERHOLD
// WWClipBoard ,,, Aufruf der Clipboard Funktionen fuer ToolEdit
// 
//    Rev 1.54   22 May 1996 18:00:52   MARTIN
// alten Font wieder zurueckselektieren
// 
//    Rev 1.53   18 May 1996 20:50:12   HANNES
// Fehlerkorrekturen
// 
//    Rev 1.52   09 May 1996 19:19:06   HANNES
// 
//    Rev 1.51   09 May 1996 16:48:28   GERHOLD
// DLLExport ... ZeilenGrenze
// 
//    Rev 1.50   06 May 1996 17:17:44   HANNES
// GetTextPtr()
// 
//    Rev 1.49   06 May 1996 12:56:56   HANNES
// ZeilenGrenze
// 
//    Rev 1.48   30 Apr 1996 17:09:26   HANNES
// Fehlerkorrektur: CompareIVListe, ShiftHandling, FormatSelection
// 
//    Rev 1.47   13 Apr 1996 19:57:52   HANNES
// Passworthandling
// 
//    Rev 1.46   11 Apr 1996 09:02:16   GERHOLD
// WWSetOutColor
// 
//    Rev 1.45   04 Apr 1996 12:15:48   GERHOLD
// FM_NOFIELDRECT
// 
//    Rev 1.44   24 Mar 1996 12:12:30   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.43   22 Mar 1996 12:14:52   HANNES
// Aenderungen Hannes
// 
//    Rev 1.42   26 Feb 1996 16:49:12   GERHOLD
// 
//    Rev 1.41   23 Feb 1996 09:50:36   HANNES
// Flackern, versteckter Trennstrich
// 
//    Rev 1.40   22 Feb 1996 15:31:54   GERHOLD
// GetAnzLines wird jetzt exportiert
// 
//    Rev 1.39   02 Feb 1996 10:59:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.38   10 Jan 1996 21:04:34   HANNES
// 
//    Rev 1.37   10 Jan 1996 18:16:32   HANNES
// 
//    Rev 1.36   10 Jan 1996 17:54:56   HANNES
// FormatMaps
// 
//    Rev 1.35   10 Jan 1996 10:23:22   GERHOLD
// FM_JUSTDEL, FM_BTNWITHINPUT
// 
//    Rev 1.34   08 Jan 1996 17:41:56   HANNES
// Defaultmodify, Wortumbruch
// 
//    Rev 1.33   05 Jan 1996 19:59:26   HANNES
// Fehlerkorrektur Formatierung
// 
//    Rev 1.31   02 Jan 1996 22:21:54   HANNES
// 
//    Rev 1.30   12 Dec 1995 12:13:46   GERHOLD
// OnKillFocus mit Parameter, WW_ONKILLFOCUS
// 
//    Rev 1.29   05 Dec 1995 14:03:18   GERHOLD
// WWGetMode
// 
//    Rev 1.28   23 Nov 1995 17:43:34   GERHOLD
// Cfield::GetFieldMode()
// 
//    Rev 1.27   16 Nov 1995 19:48:12   GERHOLD
// neuer FieldMode FM_UPPERCHAR (Umwandlung in Grossbuchstaben)
// 
//    Rev 1.26   02 Nov 1995 10:40:00   GERHOLD
// FM_NOGERMANCHARS, makeStr
// 
//    Rev 1.25   11 Sep 1995 20:24:44   MARTIN
// OnSetFocusProc
// 
//    Rev 1.24   14 Aug 1995 08:20:50   HANNES
// sWord::Paint angeglichen an cWord::Paint
// 
//    Rev 1.23   10 Jun 1995 22:02:56   HANNES
// Buchstabenbreiten
// 
//    Rev 1.22   10 Jun 1995 13:51:14   GERHOLD
// inline Funktion SetBkMode (int mode)
// 
//    Rev 1.21   09 Jun 1995 00:30:40   HANNES
// Minimale Optimierungen
// 
//    Rev 1.20   23 May 1995 18:59:38   HANNES
// cWord::breakCausedByMaxLen
// ReformatForPrinter
// 
//    Rev 1.19   20 May 1995 16:19:52   HANNES
// WW_SETMAXSIZE
// 
//    Rev 1.18   17 May 1995 10:07:34   GERHOLD
// cField::GetMaxChars, cField::GetAnzChars
// 
//    Rev 1.17   14 Apr 1995 12:06:06   HANNES
// 
//    Rev 1.16   05 Apr 1995 16:46:06   GERHOLD
// 
//    Rev 1.15   04 Apr 1995 16:44:20   HANNES
// 
//    Rev 1.14   03 Mar 1995 18:08:42   GERHOLD
// 
//    Rev 1.13   16 Feb 1995 13:02:08   HANNES
//  
// 
//    Rev 1.12   19 Dec 1994 15:30:06   GERHOLD
// InvalidateFull in cField
// 
//    Rev 1.11   19 Dec 1994 11:28:14   hannes
// 
//    Rev 1.10   28 Nov 1994 20:05:02   GERHOLD
// 
//    Rev 1.9   31 Oct 1994 09:49:42   GERHOLD
// WWSetBuddy
// 
//    Rev 1.8   20 Oct 1994 17:54:06   GERHOLD
// Clipboard-Handling, Selektion
// 
//    Rev 1.7   13 Oct 1994 18:23:00   GERHOLD
// Erweiterung fuer Selektion, OnMouse-Nachrichten erweitert
// 
//    Rev 1.6   11 Oct 1994 09:00:12   HANNES
// 
//    Rev 1.5   09 Aug 1994 10:18:50   GERHOLD
// WW_LBUTTONDBLCLK
// 
//    Rev 1.4   25 Jul 1994 09:39:38   GERHOLD
// 
//    Rev 1.3   11 Jul 1994 14:01:56   HANNES
// Direktes Setzen der Farbe
// 
//    Rev 1.2   11 Jul 1994 12:39:32   HANNES
// Setzen der Farbe
// 
//    Rev 1.1   24 Jun 1994 19:19:00   MARTIN
// Frmobject in DLL
// 
//    Rev 1.23   14 Apr 1994 16:57:32   HANNES
// Overwritemodus in Feldern
// 
//    Rev 1.22   03 Mar 1994 22:05:32   HANNES
// PaintForClipboad
// 
//    Rev 1.21   14 Feb 1994 19:46:42   HANNES
// Fontverwaltung Fensterspezifisch
// 
//    Rev 1.20   20 Jan 1994 23:55:18   HANNES
// WW_RBUTTONDOWN, WW_RBUTTONUP
// 
//    Rev 1.19   12 Jan 1994 11:06:38   HANNES
// FieldHasCaret in anderes ifdef gesetzt
// 
//    Rev 1.18   11 Jan 1994 19:06:02   HANNES
// SetCaretToEnd
// 
//    Rev 1.17   18 Oct 1993 19:45:44   HANNES
// Grossschreibung des 1. Buchstabens
// 
//    Rev 1.16   04 Oct 1993 08:46:56   HANNES
// CaretHandling
// 
//    Rev 1.15   22 Sep 1993 09:23:00   HANNES
// Version nach St. Poelten
// 
//    Rev 1.14   23 Aug 1993 19:45:06   HANNES
// ...
// 
//    Rev 1.13   18 Aug 1993 10:36:00   HANNES
// Prototypen von Wordwin, Formatierung
// 
//    Rev 1.12   20 Jul 1993 12:06:00   HANNES
// Arrange
// 
//    Rev 1.11   05 Jul 1993 14:30:30   HANNES
// Testword
// 
//    Rev 1.10   19 Jun 1993 19:34:24   HANNES
// Erweiterungen in Bezug auf Multiselektionslisten
// 
//    Rev 1.9   17 Jun 1993 09:26:40   HANNES
// Zusammenspiel mit der Multiselektionsliste
// 
//    Rev 1.8   24 May 1993 14:17:58   HANNES
// SlantField...
// 
//    Rev 1.7   12 May 1993 19:24:08   HANNES
// GetActivePos
// 
//    Rev 1.6   12 May 1993 17:22:04   HANNES
// StartExternalPaint,EndExternalPaint
// 
//    Rev 1.5   09 May 1993 17:46:58   HANNES
// Uebernahme des ausgewaehlten Strings
// 
//    Rev 1.4   07 May 1993 09:46:02   HANNES
// GetLeftLower
// 
//    Rev 1.3   06 May 1993 21:32:28   HANNES
// Einbau des Kuerzelsystems
// 
//    Rev 1.2   18 Apr 1993 22:30:32   HANNES
// Destruktor
// 
//    Rev 1.1   05 Apr 1993 10:31:34   HANNES
// Neue Callback - Funktionen (Drucker - Kontext)
// 
//    Rev 1.0   02 Apr 1993 17:57:52   HANNES
// Initial revision.
//////////////////////////////////////////////////////////

#ifndef CFIELD_INCLUDED
#define CFIELD_INCLUDED
class cField;
#define FORMAT_FAULT        1
#define LINEWITH_FAULT      2
#define PROGFAULT           3

#define CODE_HIDDENKEY      12

#define WORDTYPE_CHARS      1
#define WORDTYPE_SPACE      2
#define WORDTYPE_EXTSPACE   3
#define WORDTYPE_CR         4
#define WORDTYPE_HIDDEN     5



#ifndef FM_SINGLELINE
#define FM_NORMAL         0x00
#define FM_OUTLINEONLY    0x01      // Nur Ausgabe
#define FM_NUMBER         0x02      // Nur Integereingabe
#define FM_PUNCT          0x04      // Eingabe eines Dezimalpunktes
#define FM_DECIMAL        (FM_NUMBER | FM_PUNCT)
#define FM_SINGLELINE     0x08      // keine Returns
#define FM_LSELECTION     0x10      // Bei Enter bzw. LButtondown
                                    // vom Vater eine Liste verlangen,
                                    // Ansonsten keine weitere
                                    // Eingabe mehr
                                    // Selektion berichten
#define FM_OVERWRITE      0x20      // Eingabe im Ueberschreibmodus
#define FM_NOSELECTION    0x40      // Selektion nicht zugelassen
#define FM_MSELECTION     0x80      // Bei Enter bzw. LButtondown
                                    // vom Vater eine Liste verlangen,
                                    // Ansonsten keine weitere
                                    // Eingabe mehr
                                    // Selektion berichten
#define FM_FIRSTCHARBIG   0x100     // Ersten Buchstaben gross schreiben
#define FM_NOGERMANCHARS  0x200     // Umlaute werden in ihre aequivalente
                                    // zerlegt (ae, oe, ue, ss)
#define FM_UPPERCHAR      0x400     // Alle Buchstaben gross schreiben
#define FM_JUSTDEL        0x800     // Nur Loeschoperationen zulassen, aber keine Eingaben
#define FM_BTNWITHINPUT   0x1000    // Eingaben koennen auch bei Feldern mit 
                                    // einem Knopf daneben, durchgefuehrt werden
#define FM_NOFIELDRECT    0x2000    // kein umgebendes Rechteck in Formularen
#define FM_NOSELECTIONONFOCUS  0x4000   // erh„lt ein Eingabefeld den Fokus, dann
                                    // soll der Text nicht automatisch selektiert sein
#endif


class FAR wobj {
 public :
  DLLExport LPVOID _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (LPVOID);
  };

struct NeedScroll_Info {
  POINT pt;
  int Seite;
  };

class FAR cWord : public wobj {
 public :
  WORD wFormat;     // Format des Wortes
  BYTE wModify;     // Modifizierung des Formates
  BYTE isIndexed;   // Format kommt von einer Indizierung her
  int RelativSeite; // Seite des Wortes gegenueber der ersten Seite
                    // des Feldes
  int xPos;         // x - Position
  int yPos;         // y..
  int xLen;         // Laenge des Wortes
  int yBaseHeight;  // Basishoehe des Wortes
  int yHeight;      // Hoehe des Wortes
  int WordType;     // Typ des Wortes
  int AnzChars;     // Anzahl Zeichen
  LPSTR Text;       // Zeiger auf den Text
  LPSTR oldText;    // Zeiger auf den Alten Text
  int LineNmbr;     // Zeilennummer
  int xExtra;       // Extraoffset wegen Formatierung
  int FAR *chWidth; // Breiten der Zeichen (fuer ExtTextOut);
  BOOL breakCausedByMaxLen; // Zeilenumbruch wurde innerhalb des Wortes gemacht
  DWORD dwColor;    // Farbe des Wortes: 0xFFFFFFFF ist default

  virtual BOOL GetWordWidth (HDC hDC,LPSTR Text,int AnzChars,LPINT FAR *chWidth);
  virtual void DrawBlanks (HDC hDC);
  virtual void Paint (HDC hDC, int Seite, BOOL Inverted = FALSE, int xLeft = 0, int xRight = 0);         // Zeichnen des Wortes
  virtual BOOL GetIVRect (HDC hDC, LPRECT r);
  virtual void Invalidate (HDC hDC, BOOL fErase = TRUE);    // Invalid Setzen des Wortes
  virtual void GetWordRect (LPRECT r);
  BOOL Visible (HDC hDC);

  int xLenToPaint ()
    {
    if ((WordType == WORDTYPE_HIDDEN) && (Next != NULL) && (Next->LineNmbr != LineNmbr)) {
      return chWidth[0] ;
      }
    else
      return xLen ;
    }
  int GetWordType (LPSTR h);
  BOOL IsWordToggle(LPSTR h);
  WORD wOffs (); 
  int CheckAnzChars ();

  // Abarbeiten eines Wortes
  BOOL GetNextLinePos (int FAR &x,int FAR &y,int FAR &Seite,int lc);
  BOOL CheckWord (LPSTR startText,int x,int y,int Format,int Modify,int AnzChars,DWORD actColor);
  LPSTR CheckFormat (LPSTR h,int FAR &Format,int FAR &Modify,DWORD FAR &actColor);
  BOOL IsSingleWordInLine ();
  int NextTabPos (int x);
  int TabMetric (int x,int AnzTabs);
  int xIntermWidth (HDC hDC,int AnzChars);
  BOOL IsLineEndReached (HDC hDC,int AnzChars,BOOL FAR &NextToNextLine,
                        int FAR &lc,BOOL FAR &stop,BOOL FAR &abort,int prevType);
  LPSTR GetNext (LPSTR start,HDC hDC,int FAR &xPos,int FAR &yPos,
                        int FAR &Format,int FAR &Modify,int FAR &LineNmbr,
                        BOOL FAR &stop,BOOL FAR &abort,int prevType,int FAR &Seite,DWORD FAR &actColor);

  void SetExtra (HDC hDC,int x,BOOL doInvalidate);
  BOOL CheckExtra ();

  // Zeiger korrigieren
  void IncPtr (int dt)
    { Text += dt ; }

  cWord FAR *Next,FAR *Prev;
  cField FAR *Parent;

  cWord (cField FAR *p) 
    { Parent = p ; }

  void SaveOld ()
    {
    if ((oldText == NULL) && (Text != NULL) && (AnzChars > 0)) {
      oldText = LPSTR (GetGlobMem (AnzChars + 1)) ;
      lmemcpy (oldText,Text,AnzChars);
      }
    }
  void ResetOld ()
    {
    if (oldText != NULL)
      FreeGlobMem (oldText);
    oldText = NULL ;
    }

  ~cWord () 
    {
    if (chWidth != NULL) FreeGlobMem (chWidth);
    if (oldText != NULL) FreeGlobMem (oldText) ;
    }
  };

#define CALLBACKCMD_SAVESTR        0
#define CALLBACKCMD_SAVEFLOAT      1
#define CALLBACKCMD_NEEDSCROLL     2
#define CALLBACKCMD_SHOWLIST       3
#define CALLBACKCMD_ISLOCKED       4
#define CALLBACKCMD_SHOWHELP       5
#define CALLBACKCMD_RELEASEHELP    6
#define CALLBACKCMD_GETPRDC        7
#define CALLBACKCMD_RELEASEPRDC    8
#define CALLBACKCMD_INDEXDEL       9
#define CALLBACKCMD_TESTWORD       10
#define CALLBACKCMD_GETWORD        11
#define CALLBACKCMD_SHWORKON       12
#define CALLBACKCMD_TRANSLATECLR   13
#define CALLBACKCMD_ISCHARALLOWED  14
#define CALLBACKCMD_GETNEXTTAB     15
#define CALLBACKCMD_CARETPOSCHG    16
#define CALLBACKCMD_GETFONTREFWND  17
#define CALLBACKCMD_DOOVERWRITE    18
#define CALLBACKCMD_GETMAXANZCHARS 19
#define CALLBACKCMD_ONSETFOCUS     20
#define CALLBACKCMD_ONKILLFOCUS    21
#define CALLBACKCMD_TESTKEYDOWN    22

#define SELSTATE_DOOVERWRITE      1
#define SELSTATE_NONE             0


struct FontRefWndBuffer {
  BOOL IsDone;
  HWND RefWnd;
  };
typedef void (WINAPI * CFIELDCALLBACK) (int Command,
                                              LPVOID cfieldParam,
                                              LPVOID ExtParam
                                           );

struct TWI {
  BOOL res;       // Testword erfolgreich
  BOOL IsFirst;   // Erstes Wort im Feld
  BOOL IsLast;    // Leztes Wort im Feld
  WORD Index;     // Index des gefundenen Wortes
  WORD Format;    // Format, das eingesetzt werden soll
  WORD Modify;    // Modifyer, der eingesetzt werden soll
  LPSTR resWord;  // uebersetztes Wort
  char Text[1];   // Wort, das getestet werden soll
  };
typedef TWI FAR *LPTWI;

struct TCI {
  WORD wP ;       // Gedrueckte Taste (Resultat != Eingang) -> False
  WORD cPos ;     // Position des Carets im gespeicherten Text
  BOOL dontBeep ; // Soll trotz externer pos. Testung nicht gepiepst werden
  BOOL forDel;    // Test fuer eine Delete Taste
  BOOL delUnder;  // Typ der Loeschung, wenn Loeschung
  };
typedef TCI FAR *LPTCI;

struct TCB {
  int xold;
  int xnew;
  int AnzTabs;
  BOOL isdone;
  };

struct FAR FieldSelStruct {
  cWord FAR *SelWord;
  int        CaretPos;
  int        xPos;
  };
typedef FieldSelStruct FAR *LPFSS ;


// modes fuer TestWord
#define CPOS_GETBEG   0
#define CPOS_GETEND   1

class FAR sField;
struct RgnToIv {
  RECT r;
  LPSTR Text;
  int AnzChars;
  int Type;
  WORD Format;
  WORD Modify;
  RgnToIv FAR *Next;
  };
class FAR cField : public wobj {
  friend cWord;

 private :
  double scale;
  int xp,yp,xa,ya;
  HWND RefWnd;

 protected :
  HPEN hAPen,hIPen;
  int MapType;
  int AnzLines;
  WORD ExtraModify;
  DWORD fieldMode;
  LPSTR HelpString;
  int bkmode;
  int doSelect;
  int FAR *FormatMaps;
  int ZeilenAbstandProzent ;
  int ZeilenEinzugZeichen ;
  int EinzugErsteZeile ;
  int ErsteSeite ;
  int yPageMax ;
  int yPageNext ;
 
  FieldSelStruct  StartSel, EndSel;
  BOOL       AlreadySelected;
 
  cWord FAR *prev;    // Fuer interne Verwendung
  int xWidth;
  int DefFormat;
  cWord FAR *First;
  cWord FAR *act;
  WORD cPos;          // Position des Carets relativ zum Text
  int xvPos;          // Vertikale Position des Carets
 public:
  LPVOID CallBackMem; // Speicher fuer die Callback
  CFIELDCALLBACK cfb;
 protected:

  void ResetWords ();

  BOOL IsPrDC;
  void SetGeomMap (HDC hDC);
  void SetTwipsMap (HDC hDC);
  HDC GetFieldDC (int Format,int Modify,HFONT FAR *OldFont);
  // Schoener Gruss von Martin
  HDC GetFormatDC ();
  HDC GetFormatDC (int Format,int Modify);
  HDC GetPrDC ();
  void RestPrDC (HDC hDC);

  void ReformatAct (cWord FAR *formatFrom = NULL);

  int xLeftSpace (int Format);
  int xRightSpace (int Format);
  int yTopHeight (int Format);
  int yBottomHeight (int Format);
  int yBaseHeight (int Format);
  WORD DefModify () ;
  int MappedFormat (int Format);
  int yModifyOffset (HDC hDC,int Format,int Modify);
  int yHeight (int Format);
  int OutFormat (int Format);
  int yLineHeight (int Format);
  int yLineOffs (int Format);

  LPSTR Text;         // Eigentlicher Text


  void DelFollowings (HDC hDC,cWord FAR *);

  BOOL AllSameFormat ();
  BOOL AllSamePage ();
  int TabWidth () { return (MapType == MAPTYPE_GEOMETRIC) ? 250 : 575 ; }
  int yOrientation () { return (MapType == MAPTYPE_GEOMETRIC) ? -1 : +1 ; }
  void Invalidate (int Seite,BOOL fErase);
  void InvalidateFull (int Seite,BOOL fErase);
  void SaveOld ()
    {
    for (cWord FAR *h = First ; h != NULL ; h = h->Next)
      h->SaveOld () ;
    }
  void ResetOld ()
    {
    for (cWord FAR *h = First ; h != NULL ; h = h->Next)
      h->ResetOld () ;
    }

  WORD GetNextWordStart (WORD);
  WORD GetPrevWordStart (WORD);
  cWord FAR *GetPrev (cWord FAR *);
  cWord FAR *GetPrev ();
  cWord FAR *GetLast ();
  cWord FAR *GetWordWithPos (int Pos);

  void toDPKoords (HDC hDC,int FAR &x,int FAR &y);
  void toLPKoords (HDC hDC,int FAR &x,int FAR &y);

  void SetExistingAct ();
  cWord FAR *GetExistingWordWithPos (int pos);
  void DelWord (cWord FAR *h,HDC hDC);
  cWord FAR *GetWordForFormat ();
  void SetActToCaret ();
  LPSTR RemoveFormatFromText (LPSTR pToCorr,LPSTR FormatStart,int fs,LPSTR FAR & pToCorr1,LPSTR FAR & pToCorr2,LPSTR FAR &Text,BOOL mitFeld);
  LPSTR RemoveFormat (LPSTR pToCorr,LPSTR FormatStart,LPSTR FAR & pToCorr1,LPSTR FAR & pToCorr2,LPSTR FAR &Text,BOOL mitFeld);
  LPSTR RemoveColor (LPSTR pToCorr,LPSTR ColorStart,LPSTR FAR & pToCorr1,LPSTR FAR & pToCorr2,LPSTR FAR &Text,BOOL mitFeld);
  LPSTR RemoveModify (LPSTR pToCorr,LPSTR ModifyStart,LPSTR FAR & pToCorr1,LPSTR FAR & pToCorr2,LPSTR FAR &Text,BOOL mitFeld);
  void RemoveNotNeededFormats (LPSTR FAR &Text,BOOL mitFeld);
  void RemoveNotNeededFormats ()
    {
    RemoveNotNeededFormats (Text,TRUE);
    }
  int GetCaretHeight (HDC hDC,int Format,int FAR *logheight = NULL);
  int GetCaretHeight (int FAR *logheight = NULL);
  virtual void GetCaret ();
  virtual void SetCaretToPos (HDC hDC,int x,int y);
  void ReleaseCaret ();
  void CheckCaretHeight (HDC hDC,int Format,int Modify);

  virtual void GetCaretPos (HDC hDC,int FAR &x,int FAR &y,int FAR &LineNmbr,int FAR &Format,int FAR &Modify,BOOL checkAlways = FALSE);

  void PosCaret (HDC hDC = 0, BOOL SetOnNewPosition = FALSE, BOOL ShowMe = TRUE,int FAR *x = NULL);

  void SetCaretInLine (HDC hDC,int l,int x);
  BOOL CheckDirKey (WPARAM wP,int Seite,BOOL keyToUse);

  LPSTR makeStr (LPSTR str,LPSTR s1,char ch,LPSTR s3);
  void  SetSelectionPos (HDC hDC);
  LPSTR makeStr (LPSTR str,char ch);

  void ChangeWordPtrFrom (LPSTR nTxt,LPSTR oTxt,int ds,int from);
  void ChangeWordPtr (LPSTR nTxt,LPSTR oTxt,int ds,BOOL FAR &formatAll);
  void InvalidateWord (cWord FAR *h,HDC FAR &hDC,HFONT FAR *OldFont);
  void DelWordPtr (WORD nPos,WORD ePos,LPSTR oTxt);
  void InsertStr (LPSTR FAR &res,LPSTR str);
  void InsertStr (LPSTR str);
  void DelChar (BOOL wholeWord,BOOL delUnder);

  int GetxSpace (cWord FAR *start,cWord FAR *end,int FAR &AnzIntermChars,
                    BOOL checkBegin = FALSE,BOOL checkEnd = 0);
  cWord FAR *GetLineEnd (cWord FAR *beg,cWord FAR *end = NULL);
  cWord FAR *GetLineStart (cWord FAR *w);
  cWord FAR *GetLineStart ();
  int GetDefPosition (int Format);
  BOOL CheckOutformat (HDC hDC,cWord FAR *start,cWord FAR *end,BOOL doInvalidate,BOOL doCheck = FALSE);

  void ShowList (LPSTR charpressed);
  BOOL IsTextLimited ();
  int  GetMaxChars ();
  int  GetAnzChars ();
  BOOL TestChar (WPARAM wP,BOOL forDel,BOOL delUnder = FALSE);
  BOOL TestDecimal (WPARAM wP);
  BOOL IsLocked ();
  WORD GetRealPos ();
  BOOL IsCharAllowed (WPARAM wP,BOOL FAR *dontBeep,BOOL forDel,BOOL delUnder);
  BOOL IsKeyToUse (WPARAM wP);
  int SearchLineNmbr (HDC hDC,int y, int Seite);
  BOOL IsFormatStr (LPSTR h);
  void MyUnionRect (LPRECT r,LPRECT r1,LPRECT r2);
  BOOL PrevIsFormatStr (LPSTR h,LPSTR Text);

  int GetIndexedLength (LPSTR) ;
  BOOL IsIndexedText (WORD cP);
  WORD SkipIndexed (WORD nP);
  BOOL IsFirstOfIndex (WORD cP,WORD FAR &cStart);

  BOOL AskForWordDel ();
  WORD GetIndex (LPSTR Text);
  void GetWordBeg_End (WORD cP,WORD FAR &beg,WORD FAR &end,WORD FAR &Index);
  TWI FAR * GetWord(WORD cP,WORD FAR &beg,WORD FAR &end,BOOL allowend = FALSE);
  LPSTR GetIndexPref (LPTWI r,int FAR &Indl);
  LPSTR GetIndexMod0 (LPTWI r,int FAR &m0l);
  LPSTR GetIndexMod1 (LPTWI r,int FAR &m1l);
  LPSTR GetFormatPrefix (WORD format,int FAR &fl);
  LPSTR GetIndexForm0 (LPTWI r,int FAR &f0l);
  LPSTR GetIndexForm1 (LPTWI r,int FAR &f1l,WORD beg);
  LPSTR GetIndexLength (LPTWI r,int FAR &Ll,int gl);
  BOOL TestWord (int cP,WORD FAR &nPos,WORD mode);
  BOOL IsFirstPrintable (WORD cP);
  BOOL SameText (LPSTR Txt,int len);
  WORD GetStoredTextLength (LPSTR Txt);
  WORD GetStoredTextLength ()
    {
    return GetStoredTextLength (Text);
    }
  void StoreText (LPSTR Txt,LPSTR res);
  void StoreText (LPSTR res)
    {
    StoreText (Text,res);
    }
  WORD GetFormatUntil (WORD cP);
  BOOL actIsValid ();
  BOOL EstimatedRect (LPRECT r,int Seite);
  void ChangeText (LPTWI actWord,WORD beg,WORD end,WORD FAR &nPos,
                         WORD mode);
  void LoadString ();
  BOOL IsSHWorkKey (WPARAM wP);
  BOOL IsHiddenKey (WPARAM wP);

  int GetWordCount ();
  int GetMaxWidth ();
  void UnionWordRects (LPRECT r);
  int ArrangeWords (int width);
  void CenterWords (int width);

  HWND CalcFontRefWnd ();
  HWND GetFontRefWnd ()
    { return RefWnd ; }

  int sel_state;
  virtual void InvertText (HDC hDC);
  void TestSelState (int Seite);
  void ResetSelState (int Seite);
  void ResetAndDeleteSelState (WPARAM wP,int Seite);

  void InvalidateSelectedWords ();
  void GetSelectionFromLeftToRight (LPFSS SelStart, LPFSS SelEnd);
  void InvalidateWordRange (cWord FAR *StartWord, cWord FAR *EndWord);
  void ClearSelection ();
  BOOL IsInsertAllowed (LPSTR StrToInsert);
  BOOL BreakInLineAllowed (cWord FAR *h);

 public :
  void CheckScroll (int Seite,BOOL checkAlways = FALSE);
  void SetExtraModify(WORD em)
    {
    ExtraModify = em ;
    }
  virtual BOOL SameChars (LPSTR t1,LPSTR t2,int FAR *res,int count);
  virtual int PhysWidth (HDC hDC,LPSTR Text,int AnzChars);
  void CompareIV (HDC hDC,RgnToIv FAR *r1,RgnToIv FAR *r2,HWND hWnd,
                  HFONT FAR *OldFont,BOOL FAR *firstCompare);
  void InvalidateIVList (HWND hWnd,HDC hDC,HFONT FAR *OldFont);
  int FirstPage ()
    { return ErsteSeite ; }
  LPSTR TextPtr()
    { return Text ; }
  int LastPage ();
  BOOL IsWordEndChar (WPARAM wP);

  HWND Wnd;
  int x0,y0;
  BOOL HasButton;   // ein ComboButton für dieses cField
  HDC GetFieldDC ();
  void RestDC (HDC hDC);
  virtual BOOL GetFullTextRect (LPRECT r,int Seite);
  DLLExport BOOL _export WINAPI ZeilenGrenze (int l,int FAR *y1,int FAR *y2);

  COLORREF outcolor;
  COLORREF GetOutColor (int Format);

  DLLExport void _export WINAPI SetFormatMaps (int FAR *Maps,int AnzMaps);

  void SetBackMode (int mode) { bkmode = mode; }

  DLLExport void _export WINAPI SetButtonField (BOOL flag);
  int LineHeight ();

  virtual void ModifyDC (HDC hDC,int Format,int Modify,HFONT FAR *OldFont,BOOL full = FALSE);
  DLLExport _export WINAPI cField (WORD bkmode,int format,int x,int y,int width,
                                int anzlines,BOOL doSelect);

  virtual DLLExport void _export WINAPI Paint (HDC hDC,int Seite,BOOL forPrinting);
  virtual DLLExport void _export WINAPI PaintToMeta (HDC hmDC);
  void ReformatForPrinter (HDC hDC);
  DLLExport void _export WINAPI Reformat (HDC hDC = 0);
  DLLExport void _export WINAPI SetWidth (int w);
  int GetWidth ()
    {
    return xWidth;
    }
  int GetDefFormat ()
    {
    return DefFormat;
    }

  DLLExport void _export WINAPI SetDefFormat (int f);
  DLLExport BOOL _export WINAPI GetFieldRect (RECT FAR *r,int Seite);
  DLLExport cField FAR & _export WINAPI operator >> (POINT FAR &pt);
  DLLExport cField FAR & _export WINAPI operator >> (GLOBALHANDLE FAR &hGmem);
  DLLExport cField FAR & _export WINAPI operator = (LPSTR Txt);
  DLLExport cField FAR & _export WINAPI operator = (POINT pt);


  virtual DLLExport BOOL _export WINAPI GetFullFieldRect (LPRECT r,int Seite);
  DLLExport void _export WINAPI SetSelectionPen (HPEN hActivePen,HPEN hInactivePen);
  DLLExport int  _export WINAPI GetAnzLines ();
  DLLExport int  _export WINAPI GetActLine ();
  DLLExport void _export WINAPI SetActLine (int l);
  DLLExport void _export WINAPI SetAnzLines (int AnzL);
  DLLExport void _export WINAPI SetFieldMode (DWORD mode);
  DLLExport DWORD _export WINAPI GetFieldMode (void);
  DLLExport void _export WINAPI SetHelpString (LPSTR hlp);
  DLLExport BOOL _export WINAPI HasCaretPos ();
  DLLExport void _export WINAPI SetCaretToStart ();
  DLLExport void _export WINAPI SetCaretToEnd ();
  DLLExport void _export WINAPI SetCaretTo (int Line,int Col);
  DLLExport void _export WINAPI OnSetFocus (BOOL bexplicit, int Seite, BOOL doSelect = TRUE);
  DLLExport void _export WINAPI OnKillFocus (WPARAM wp,int Seite);
  DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM wP, POINT pt,int Seite);
  DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM wP, POINT pt,int Seite);
  DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM wP, POINT pt,int Seite);
  DLLExport BOOL _export WINAPI OnMouseMove (WPARAM wP, POINT pt,int Seite);
  DLLExport BOOL _export WINAPI OnKeyDown (WPARAM wP,int Seite);
  DLLExport BOOL _export WINAPI OnChar (WPARAM wP,int Seite);
  DLLExport void _export WINAPI InstallCallBack (CFIELDCALLBACK cfb,LPVOID par,int size);
  DLLExport void _export WINAPI GetLeftLower (LPPOINT pt,int Seite);

  DLLExport void _export WINAPI SetOutColor (COLORREF color);
  DLLExport void _export WINAPI UseDefOutColor ();

  void SetWindow (HWND hWnd)
    { Wnd = hWnd ; }
  DLLExport void _export WINAPI SetScale (double sc,int type);
  DLLExport void _export WINAPI SetVOrg (int x,int y,int ErsteSeite);
  DLLExport void _export WINAPI SetWOrg (int x,int y);

  DLLExport void _export WINAPI StartExternPaint ();
  DLLExport void _export WINAPI EndExternPaint ();

  DLLExport void _export WINAPI GetActivePos (LPPOINT pt);

  DLLExport virtual _export WINAPI ~cField ();
  virtual cWord FAR *GetWord ()
    { return new cWord (this); }

  DLLExport void _export WINAPI Arrange (int relHeight);
  DLLExport void _export WINAPI SetFormat (int format);
  DLLExport int _export WINAPI GetActFormat ();
  DLLExport DWORD _export WINAPI GetActColor ();
  DLLExport WORD _export WINAPI GetActModify ();

  DLLExport BOOL _export WINAPI CopyToClipBoard (HWND hWnd);
  DLLExport BOOL _export WINAPI PasteFromClipBoard (HWND hWnd);
  DLLExport BOOL _export WINAPI DeleteSelectedLines ();
  void DeleteTextOut (cWord FAR *wToFormat,int nPos,int ePos);
  DLLExport BOOL _export WINAPI JustStringsSelected ();
  DLLExport BOOL _export WINAPI FormatSelection (WORD modify,BOOL doOff);
  DLLExport BOOL _export WINAPI ColorSelection (DWORD color);
  DLLExport short _export WINAPI GetLineHeight ();
  DLLExport void _export WINAPI SetLineHeight (int height);
  DLLExport void _export WINAPI SetSelection (int sPos,int sLen,int aktuelleSeite);
  DLLExport void _export WINAPI ChangeSelection (int sPos,int sLen,LPSTR ntxt);

  DLLExport void _export WINAPI SetPageBreak (int ymax,int y0Next);

  BOOL IsSomeTextSelected () { return AlreadySelected; }

  friend HDC FontPrDC (HDC oldDC,LPVOID data);
  friend DLLExport void _export WINAPI InsertAtCaret (cField FAR *f,LPSTR str);
  friend DLLExport void _export WINAPI SetAtCaret (cField FAR *f,LPSTR str);

  DLLExport LPSTR _export WINAPI SkipFormat (LPSTR);
  DLLExport LPSTR _export WINAPI SkipPrevFormat (LPSTR);
  };

#ifdef CFIELD_MAIN
cField FAR *ActiveField;
int oldCaretHeight;
int oldCaretIsShown;
BOOL CaretIsVisible = FALSE;
BOOL bEnableSelect = TRUE;
BOOL SelectFocusedFields = TRUE;    // Windows Standard
#endif
#ifdef CFIELD_ALSO
extern cField FAR *ActiveField;
extern int oldCaretHeight;
extern int oldCaretIsShown;
extern BOOL CaretIsVisible;
extern BOOL bEnableSelect;
extern BOOL SelectFocusedFields;
#endif


#ifndef FR_LEFT
#define FR_LEFT            0
#define FR_CENTERED        1
#define FR_RIGHT           2
#define FR_BLOCK           3
#endif

#endif

///////////////////////////////////////////////////////////////////
//    Schiefe Felder
///////////////////////////////////////////////////////////////////
class sWord : public cWord {
 public :
  virtual void DrawBlanks (HDC hDC);
  virtual void Paint (HDC hDC, int Seite, BOOL Inverted = FALSE, int xLeft = 0, int xRight = 0);         // Zeichnen des Wortes
  virtual void Invalidate (HDC hDC);    // Invalid Setzen des Wortes
  virtual void GetWordRect (LPRECT r);

  sWord (cField FAR *p) : cWord (p) { } 
  };

class sField : public cField {
 public :
  HBITMAP hcrtbmp;
  double ang;
  double ca,sa;
  int CaretDX;
  DLLExport _export WINAPI sField (WORD bkmode,int format,int x,int y,int width,
                                int anzlines,BOOL doSelect,double ang,int Maptype);
  virtual DLLExport _export WINAPI ~sField ();
  virtual DLLExport void _export WINAPI Paint (HDC hDC,int Seite,BOOL forPrinting);
  virtual DLLExport void _export WINAPI GetFullFieldRect (LPRECT r);

  virtual void ModifyDC (HDC hDC,int Format,int Modify,HFONT FAR *OldFont,BOOL full = FALSE);
  virtual BOOL GetFullTextRect (LPRECT r,int Seite);
  void TransformPoint (LPPOINT pt);
  void TransformRect (LPRECT r);
  void GetPaintRect (LPPOINT pt);

  virtual void GetCaret ();
  virtual void SetCaretToPos (HDC hDC,int x,int y);

  virtual cWord FAR *GetWord ()
    { return new sWord (this); }
  void GetTransform();
  };

//////////////////////////////////////////////////////////////////////
//  Passwort - Funktion
//////////////////////////////////////////////////////////////////////
class pWord : public cWord {
 public :
  virtual BOOL GetIVRect (HDC hDC, LPRECT r);
  virtual BOOL GetWordWidth (HDC hDC,LPSTR Text,int AnzChars,LPINT FAR *chWidth);

  pWord (cField FAR *p) : cWord (p) { } 
  };

class pField : public cField {
 protected :
  virtual void GetCaretPos (HDC hDC,int FAR &x,int FAR &y,int FAR &LineNmbr,int FAR &Format,int FAR &Modify,BOOL checkAlways = FALSE);
 public :
  virtual BOOL SameChars (LPSTR t1,LPSTR t2,int FAR *res,int count);
  virtual int PhysWidth (HDC hDC,LPSTR Text,int AnzChars);
  DLLExport _export WINAPI pField (WORD bkmode,int format,int x,int y,int width,
                                int anzlines,BOOL doSelect);

  virtual DLLExport void _export WINAPI Paint (HDC hDC,int Seite,BOOL forPrinting);
  virtual cWord FAR *GetWord ()
    { return new pWord (this); }
  };

DLLExport void _export WINAPI ResetCFieldCaret ();

//////////////////////////////////////////////////////////////////////
//  Wordwin - Funktionen
//////////////////////////////////////////////////////////////////////
DLLExport int _export WINAPI WWGetXWidth (int format,int AnzChars);
DLLExport int _export WINAPI WWGetYHeight (int format);
DLLExport HWND _export WINAPI WWCreateWin (HWND hParent,WORD Id,int format,
                                     int x0,int y0,
                                     int AnzChars,
                                     DWORD style,
                                     HANDLE hInstance
                                    );
DLLExport HWND _export WINAPI WWCreateWinEx (HWND hParent,WORD Id,int format,
                                     int x0,int y0,
                                     int w,int h,
                                     DWORD style,
                                     BOOL password = FALSE,
                                     int AnzLines = 1,
                                     int LogWidth = -1
                                    );
DLLExport void _export WINAPI WWSetFormat (HWND hWnd,int Format);
DLLExport void _export WINAPI WWSetMode (HWND hWnd,DWORD mode);
DLLExport DWORD _export WINAPI WWGetMode (HWND hWnd);
DLLExport int  _export WINAPI WWGetActFormat (HWND hWnd);
DLLExport WORD _export WINAPI WWGetActModify (HWND hWnd);
DLLExport DWORD _export WINAPI WWGetActColor (HWND hWnd);
DLLExport void _export WINAPI WWSetOverwrite (HWND hWnd);
DLLExport void _export WINAPI WWSetModify (HWND hWnd,int Modify,BOOL Set_Clear);
DLLExport void _export WINAPI WWSetBuddy (HWND hWnd, BOOL flag);
DLLExport void _export WINAPI WWEnableSelect (BOOL Select);
DLLExport BOOL _export WINAPI WWGetSelect ();
DLLExport void _export WINAPI WWSetFormatMap (HWND hWnd,int FAR *maps,int AnzPairs);
DLLExport void _export WINAPI WWSetOutColor (HWND hWnd,COLORREF color);
DLLExport void _export WINAPI WWClipBoard (HWND hWnd, WPARAM cmd);
DLLExport BOOL _export WINAPI WWIsFieldSelected (HWND hWnd);
DLLExport void _export WINAPI WWFormatSelection (HWND hWnd,WORD Modify,BOOL doOff);
DLLExport void _export WINAPI WWColorSelection (HWND hWnd,DWORD Color);
DLLExport BOOL _export WINAPI WWSelectionInString (HWND hWnd);
DLLExport void _export WINAPI WWInsertAtCaret (HWND hWnd,LPSTR str);
DLLExport void _export WINAPI WWSetAtCaret (HWND hWnd,LPSTR str);
DLLExport BOOL _export WINAPI WWSetCaretTo (HWND hWnd,int Line,int Col);
DLLExport void _export WINAPI WWNextExplicit (BOOL val);

DLLExport void _export WINAPI PaintActiveCombo (HDC hDC,HWND hWnd,BOOL isPrinting,int Seite);
DLLExport LPSTR _export WINAPI RemoveFormatInfoFromString (LPSTR Str);
DLLExport LPSTR _export WINAPI RemoveAllFormatInfoFromString (LPSTR Str);
DLLExport cField FAR * _export WINAPI GetActiveField ();
DLLExport void _export WINAPI SetFocusFlag (BOOL State);
DLLExport void _export WINAPI OnKillFocusIf (cField FAR *h);


#define WW_CHAR             0x0700
#define WW_RBUTTONDOWN      0x0701
#define WW_LBUTTON          0x0702
#define WW_CARETPOSCHG      0x0703
#define DDSLIST_TABPRESSED  0x0704
#define WW_RBUTTONUP        0x0705
#define WW_WORKON           0x0706
#define WW_LBUTTONDBLCLK    0x0707
#define WW_SETTEXTLEN       0x0708
#define WW_ONSETFOCUS       0x0709
#define WW_ONKILLFOCUS      0x0710
#define DDSLIST_LBUTTON     0x0711
#define WW_KEYDOWN          0x0712

#ifndef CARETHANDLING_DONE
#ifdef DDS_MAIN
BOOL FieldHasCaret ;
#else
extern BOOL FieldHasCaret ;
#endif
inline BOOL IsCaretShown ()
  {
  return FieldHasCaret ;
  }

inline void SetCaretShown ()
  {
  FieldHasCaret = TRUE ;
  }

inline void SetNoCaret ()
  {
  FieldHasCaret = FALSE ;
  }

#define CARETHANDLING_DONE
#endif

