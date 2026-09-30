/////////////////////////////////////////////////////
//  Bearbeiten von Scripts (Dialogeditor, ..)
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/wonscrip.hpv   1.29   02 Jul 1999 12:19:28   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/wonscrip.hpv  $
// 
//    Rev 1.29   02 Jul 1999 12:19:28   Wolfgang
// 1.) Neue Methode TestString.
// 
//    Rev 1.28   15 Mar 1999 11:27:28   Wolfgang
// 1.) InitWordJump und IsWordChar neu.
// 2.) wordStopFlags und extraWordChars neu.
// 3.) Defines fuer wordStopFlags neu.
// 
//    Rev 1.27   12 Mar 1999 13:51:58   Wolfgang
// 1.) SearchIt hat neuen Parameter withMessage.
// 
//    Rev 1.26   10 Mar 1999 19:47:04   Wolfgang
// 1.) SearchIt neu.
// 2.) Zusaetzliche xExtraNeg, yExtraNeg und preferLeft Parameter.
// 
//    Rev 1.25   09 Mar 1999 16:30:42   Wolfgang
// 1.) NeedNewCaption eliminiert.
// 2.) SetCaption in TextBlock neu.
// 
//    Rev 1.24   20 Oct 1998 08:41:30   Gerhold
// neues Syntax-Coloring
// 
//    Rev 1.23   24 Aug 1998 07:07:14   Hannes
// CheckNextChar ... Prototypaenderung
// 
//    Rev 1.22   22 Apr 1998 09:51:14   Gerhold
// MatchingBraces
// 
//    Rev 1.21   06 Jan 1998 19:58:24   Gerhold
// ToolTips zum Debuggen eingebaut
// 
//    Rev 1.20   28 Oct 1996 08:46:44   HANNES
// 
//    Rev 1.19   21 Oct 1996 18:55:20   HANNES
// Fehlerkorrektur Editor / Erweiterung Debugger
// 
//    Rev 1.18   03 Sep 1996 11:18:28   HANNES
// 
//    Rev 1.17   02 Feb 1996 11:00:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.16   23 Aug 1995 11:03:44   GERHOLD
// 
//    Rev 1.15   07 Jun 1995 12:20:56   GERHOLD
// BookMark, in der Klasse TextLine neue MemberVariable "Style"
// 
//    Rev 1.14   26 Apr 1995 15:31:38   HANNES
// 
//    Rev 1.13   24 Apr 1995 15:47:26   GERHOLD
// 
//    Rev 1.12   10 Apr 1995 10:47:38   GERHOLD
// 
//    Rev 1.11   24 Feb 1995 11:13:38   GERHOLD
// 
//    Rev 1.10   16 Feb 1995 12:47:40   GERHOLD
// 
//    Rev 1.9   26 Jan 1995 10:27:22   HANNES
// 
//    Rev 1.8   09 Jan 1995 14:33:36   GERHOLD
// 
//    Rev 1.7   02 Jan 1995 18:33:30   HANNES
// 
//    Rev 1.6   02 Jan 1995 09:32:18   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.5   25 Oct 1994 11:53:52   GERHOLD
// 
//    Rev 1.4   10 Oct 1994 10:43:20   GERHOLD
// Zwischenablage, Selektion
// 
//    Rev 1.3   30 Sep 1994 14:40:52   GERHOLD
// Erweiterungen fuer die Zwischenablage
// 
//    Rev 1.2   12 Jul 1994 14:47:26   HANNES
// 
//    Rev 1.1   04 Jul 1994 14:09:06   HANNES
// 
//    Rev 1.0   24 Jun 1994 18:50:34   HANNES
// Initial revision.
//

#ifdef WIN32
  #define TOOLTIP
#endif

#define ANALYSELINE
#define ANALYSEKEYWORD


#define STATE_INIT        0
#define STATE_SEARCHBOPEN 1
#define STATE_PUSHPAR     2

#define XMIN  30

#define GWL_TEXTBLOCK 0        // Extrabytes des Scriptfensters

class FAR TextBlock;
typedef TextBlock FAR *LPTEXTBLOCK;

class FAR FileBlock;
typedef FileBlock FAR *LPFILEBLOCK;


#ifdef ANALYSELINE

  extern DWORD  CurrentAnalyseState;

  #define   ANALYSE_STATE_INIT        0
  #define   ANALYSE_STATE_COMMENT     1
  #define   ANALYSE_STATE_QUOTAINIT   2
  #define   ANALYSE_STATE_QUOTAEND    3
  #define   ANALYSE_STATE_FULLCOMMENT 4


  struct AnalyseStruct {
    int StartPos, EndPos;
    AnalyseStruct FAR *Next; 
    };
  typedef AnalyseStruct FAR* LPANALYSESTRUCT;

#endif


#define LS_BOOKMARK    0x1          // TextZeile hat ein Lesezeichen
#define LS_ERROR       0x2          // Textzeile ist fehlerhaft
#define LS_STARTBRACE  0x4
#define LS_ENDBRACE    0x8
#define LS_STRINGLINE  0x10         // Diese Zeile beinhaltet einen String

struct FAR TextLine {
  TextLine FAR *Next;
  TextLine FAR *Prev;
  LPSTR    Text;
  DWORD    Style;

  void  AddText (LPSTR txt);
  int   AnalyseComment ();
  BOOL  AnalyseDefine (LPVOID buffer,WORD FAR *size,LPSTR name);
  LPSTR AnalyseInclude ();

#ifdef ANALYSELINE
  LPANALYSESTRUCT Quota;
  LPANALYSESTRUCT Comment;
  DWORD           State;

  BOOL  AnalyseLine ();
  void  ClearQuota ();
  void  ClearComment ();
  DWORD GetAnalyseStatus (int x);
#endif

#ifdef ANALYSEKEYWORD
  LPANALYSESTRUCT KeyWord;

  BOOL  AnalyseKeyword (LPSTR CurrentWord);
  void  ClearKeyWord ();
#endif

  int   AnalyseSpecialChar (char ch, int StartPos = 0);
  int   AnalyseSpecialString (LPSTR lpstr, int StartPos = 0, int len = 1);
  void  DeleteText (int Start, int End);
  LPSTR FirstWord ();
  int   InsertText (LPSTR txt, int iPos);

  // Lesezeichen setzen und abfragen
  BOOL  IsBookMarkLine ()      { return ((Style & LS_BOOKMARK) == LS_BOOKMARK); }
  void  ToggleBookMark ()      
        { if (IsBookMarkLine())      // und immer wieder toggeln
            Style &= ~LS_BOOKMARK;
          else
            Style |= LS_BOOKMARK;
        }

  // Fehlerzeile setzen, loeschen und abfragen
  void  SetErrorLine ()        { Style |= LS_ERROR; }
  void  ClearErrorLine ()      { Style &= ~LS_ERROR; }
  BOOL  IsErrorLine ()         { return ((Style & LS_ERROR) == LS_ERROR); }

  void  SetStartBrace ()       { Style |= LS_STARTBRACE; }
  void  ClearStartBrace ()     { Style &= ~LS_STARTBRACE; }
  BOOL  IsStartBrace ()        { return ((Style & LS_STARTBRACE) == LS_STARTBRACE); }
  void  SetEndBrace ()         { Style |= LS_ENDBRACE; }
  void  ClearEndBrace ()       { Style &= ~LS_ENDBRACE; }
  BOOL  IsEndBrace ()          { return ((Style & LS_ENDBRACE) == LS_ENDBRACE); }

  BOOL  IsStringLine ()        { return ((Style & LS_STRINGLINE) == LS_STRINGLINE); }
  void  SetStringLine ()       { Style |= LS_STRINGLINE; }
  void  ClearStringLine ()     { Style &= ~LS_STRINGLINE; }

  LPSTR NextWord (LPSTR h);
  void  Paint (HDC hDC, int x, int y, LPRECT rcLine, BOOL Analyse, LPTEXTBLOCK lptb);
  WORD  GetSPos(LPSTR t)       { return t - Text ; }
  };
typedef TextLine FAR *LPLINE;


struct FAR SelStruct {
  int    Col;
  int    Row;
  LPLINE Line;
  };
typedef SelStruct FAR* LPSELSTRUCT;


#ifndef _DRAGDROP_DEFINED
  class FAR Drag_Drop;
  typedef Drag_Drop FAR *LPDRAGDROP;
  #define _DRAGDROP_DEFINED
#endif


struct BraceStruct {
  LPLINE Line;
  short  Col;
  };


#define WORDSTOP_LEFT_WORDEND   0x01
#define WORDSTOP_LEFT_EOL       0x02
#define WORDSTOP_RIGHT_WORDEND  0x10
#define WORDSTOP_RIGHT_EOL      0x20

#define WORDSTOP_JUMP_SHIFT      0
#define WORDSTOP_DELETE_SHIFT    8
#define WORDSTOP_SELECT_SHIFT   16

//----------------------------------------------------------------------------
//
// class TextBlock
//
//----------------------------------------------------------------------------
class FAR TextBlock {
 public :
  HWND   MyWnd;
  LPLINE FirstVisibleLine;    // erste sichtbare Zeile im Fenster
  LPLINE LastVisibleLine;
  LPLINE FirstLine;           // erste Zeile des Text-Buffers
  LPLINE LastLine;            // letzte Zeile des Text-Buffers
  LPLINE ErrorLine;           // letzte fehlerhafte Zeile
#ifdef ANALYSELINE
  LPLINE LastLineAnalyzed;    // ab hier beginnt der SyntaxCheck
#endif
  BOOL   ModifyDone;

  LPSTR  fName;

  LPSTR  SelWord;

  LPDRAGDROP editdrop;

  int    x0;
  int    charHeight;  // Werte aus TEXTMETRIC
  int    charWidth;
  LONG   GesHeight;   // Gesamthoehe des Text-Buffers
  int    GesWidth;    // laengster String des Text-Buffers
  int    hmax,vmax;   // Anzahl nicht sichtbarer Zeilen und Spalten
  int    ohmax,ovmax;

  BOOL      AlreadySelected;
  BOOL      ShiftIsDown;
  SelStruct StartSel, EndSel;

#ifdef TOOLTIP
  HWND      hWndToolTip;
#endif

  CHAR extraWordChars[128];
  LONG wordStopFlags;

  TextBlock (GLOBALHANDLE hGmem);
  TextBlock (LPSTR fname);
  ~TextBlock ();

#ifdef ANALYSELINE
  void   AnalyseLines (LPLINE StartLine = NULL, LPLINE EndLine = NULL, BOOL KeyWord = FALSE);
#endif

  void   InitWordJump ();
  BOOL   CheckNextChar (void);
  BOOL   CheckPrevChar (void);
  BOOL   CopyToClipBoard (HWND hWnd);
  BOOL   CopySelectedTextToGlobalHandle (LPHANDLE hText);
  BOOL   InsertLinesInTextFromBuffer (HWND hWnd, LPSTR lpszText);
  LPLINE DelLine (LPLINE h,LPLINE FAR *last);
  BOOL   DeleteSelectedLines (HWND hWnd);
  void   FindMatchingBraces (HWND hWnd, BOOL bJump, BOOL bMove);
  int    GetAbsoluteLineNmbr (LPLINE l);
  LONG   GetFirstVisibleLinePos ();
  void   GetMinMax ();
  int    GetNextState (int state,LPLINE h,LPLINE f,LPLINE l);
  void   GetSelectionFromTopToBottom (LPSELSTRUCT SelStart, LPSELSTRUCT SelEnd);
  void   GetSelRange (int FAR *ystart,int FAR *yend,LPLINE firstLine,LPLINE lastLine);
  int    GetState (LPLINE h,LPLINE f,LPLINE l);
  void   GotoBookMark (WORD wP);
  void   InsertLine (LPSTR Text);
  LPLINE InsertLineBehind (LPLINE line,LPSTR Text);
  LPLINE InsertLineBefore (LPLINE line,LPSTR Text);
  void   Paint (HWND hWnd, HDC hDC,LPLINE firstLine,LPLINE lastLine, RECT rcPaint);
  BOOL   PasteFromClipBoard (HWND hWnd);
  LPSTR  PushLine (LPSTR h);
  BOOL   TestString (LPSTR s,LPSTR t,BOOL CaseSensitive,BOOL wholeWord,BOOL lineStart);
  BOOL   CheckSelectedLines (LPSTR SearchString,BOOL CaseSensitive,BOOL wholeWord);
  BOOL   SearchIt (BOOL bCycled,
                   HWND hWnd,LPSTR SearchString,LPSTR ReplaceString,
                   BOOL CaseSensitive,BOOL replace,BOOL wholeWord,BOOL directionDown,
                   BOOL withMessage = TRUE);
  BOOL   Search (HWND hWnd,LPSTR SearchString,LPSTR ReplaceString,BOOL cs,BOOL replace,BOOL wholeWord);
  BOOL   SearchUp (HWND hWnd,LPSTR SearchString,BOOL cs,BOOL wholeWord);
  void   SetActLine (int vPos);
  void   SetModified ();
  void   SetScrollers (HWND hWnd);
  void   SetSelection (LPLINE first, LPLINE last);
  void   SetSelWord (LPLINE h,WORD b,WORD e);
  void   Store (HWND hWnd);
  GLOBALHANDLE StoreToHandle (HWND hWnd);
  BOOL   TestLines (LPLINE f,LPLINE l);
  void   TextMetrics ();


  BraceStruct  StartBrace, EndBrace;

  // Caret - Handling
  LPLINE LineWithCaret;
  int    iCaret;
  int    YCaret, YAbsCaret;
//  int    viCaret;
  BOOL   LineChanged;
  int    xScroll;
  LONG   yScroll,yFirstVisible;
  LONG   yLastVisibleLine;

  void   DelActChar ();
  void   DelCharUnder ();
  void   DelLineWithCaret (HWND hWnd);
  void   DelPrevChar ();
  void   End ();
  LPLINE GetLineFromLineNr (int LineNr);
  void   GetNewCaretPos ();
  void   GetTextFromMousePos (LPFILEBLOCK fbl, LPSTR szText, POINT pt);
  int    GetYPos (LPLINE l);
  void   GiveCaretTo (HWND hWnd);
  void   HideCaretFrom (HWND hWnd);
  void   Home ();
  void   InsertChar (char ch);
  void   InvalidateSelectedLines (HWND hWnd);
  void   InvalidateLine (HWND hWnd,LPLINE h);
  void   InsertSpacesFromLineEndToCaret ();
  BOOL   IsCaretBehindLine () { return (iCaret > lstrlen(LineWithCaret->Text)); }
  BOOL   IsWordChar (char ch, BOOL allowPoint = FALSE);
  void   LineBeg ();
  void   LineBreak (BOOL MoveCaret);
  void   LineEnd ();
  BOOL   MouseInSelectedText (POINT pt);
  void   MoveBlock (HWND hWnd, BOOL MoveLeft);
  void   NextChar ();
  void   NextLine ();
  void   NextSide (HWND hWnd);
  void   NextWord (BOOL forDelete = FALSE);
  void   OnChar (HWND hWnd,WPARAM wP);
  void   OnKeyDown (HWND hWnd, WPARAM wP);
  void   OnKillFocus (HWND hWnd);
  void   OnSetFocus (HWND hWnd);
  void   PosCaret (HWND hWnd,int xExtra = 0,int yExtra = 0,int xExtraNeg = 0,int yExtraNeg = 0,BOOL preferLeft = 0);
  void   PrevChar ();
  void   PrevLine ();
  void   PrevSide (HWND hWnd);
  void   PrevWord (BOOL forDelete = FALSE);
  void   SetCaretWithMouse (HWND hWnd,int x,int y,BOOL MoveCaret = TRUE);
  void   SetNewCPos (HWND hWnd,int xExtra = 0,int yExtra = 0,int xExtraNeg = 0,int yExtraNeg = 0,BOOL preferLeft = 0);
  void   ShowCaretIn (HWND hWnd);
  void   TakeCaretFrom (HWND hWnd);

  void   OnLButtonDown (HWND hWnd, WPARAM wParam, LPARAM lParam);
  void   OnMouseMove (HWND hWnd, WPARAM wParam, LPARAM lParam);
  void   OnLButtonUp (HWND hWnd, WPARAM wParam, LPARAM lParam);
  void   OnLButtonDblClk (HWND hWnd, WPARAM wP, LPARAM lP);
#ifdef TOOLTIP
  void   RelayMouseMessageToToolTip (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP);
#endif

  void SetCaption (HWND hWnd);

  LPVOID operator new (size_t size)
    { 
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };

BOOL AllowAnalyse ();
void AnalyseBlock (HWND hWParent,LPTEXTBLOCK bl,LPLINE first,LPLINE last,hash FAR *h);
void CreateDlgInsertMenu (HWND hWParent);
void DelStrBuffer ();
BOOL DestroyEdDialog ();
void Duplicate ();
//inline int  WINAPI GetXMin ();
void IndenHintergrund ();
void IndenVordergrund ();
void SetDialogRaster (BOOL bShow);
void InsertCommand (WORD wP);
BOOL IsDialogOpen ();
BOOL IsWOnEleOpen();
BOOL MoveElems ();
void NeedViewFor (HWND hWnd,LPTEXTBLOCK b,int FAR *x,LONG FAR *y,LONG ya,int xExtra = 0,int yExtra = 0,int xExtraNeg = 0,int yExtraNeg = 0,BOOL preferLeft = FALSE);
BOOL RemoveCommand ();
void RemoveDlgInsertMenu (HWND hRefWnd);
BOOL StoreDialog (LPTEXTBLOCK bl,LPLINE FAR *lSelected,LPLINE FAR *fSelected);
void TogglePaintNums();
BOOL WorkOnEle (HWND hParent);
BOOL WorkOnScreen (HWND hWnd);
void InsertTextIntoScript (LPSTR text);
BOOL SearchTextInScript (LPSTR SearchText, BOOL bCaseSensitive, BOOL bSearchDown);
