//
//    $Header:   F:/marille/clinicum/include/rev/ddslist.hpv   1.45   06 Mar 2000 07:10:42   Hannes  $
//    $Log:   F:/marille/clinicum/include/rev/ddslist.hpv  $
// 
//    Rev 1.45   06 Mar 2000 07:10:42   Hannes
// Neuer Prototyp UpdateElem
// 
//    Rev 1.43   19 Dec 1999 21:26:50   Hannes
// ForcePageBreak
// 
//    Rev 1.42   29 Nov 1999 18:21:58   Hannes
// IsFullOnScreen (...,xExtra)
// 
//    Rev 1.41   08 Nov 1999 03:44:16   Hannes
// in testrecord ein RefreshList...
// 
//    Rev 1.40   05 Mar 1999 10:56:02   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.39   26 Nov 1998 08:22:14   Hannes
// SetLineObject ohne Objekte
// 
//    Rev 1.38   27 Jul 1998 15:14:48   Hannes
// lSetUpCallBack
// 
//    Rev 1.37   20 Mar 1998 15:28:06   Hannes
// Refresh im sichtbaren bereich
// 
//    Rev 1.36   13 Mar 1998 18:55:34   Hannes
// Listenklickprozedur
// 
//    Rev 1.35   16 Feb 1998 08:08:22   Gerhold
// IsEmpty hatte keinen Rueckgabewert -> BOOL
// 
//    Rev 1.34   26 Jan 1998 19:58:40   Hannes
// GetFrameType
// 
//    Rev 1.33   16 Jan 1998 15:27:56   Hannes
// 
//    Rev 1.32   01 Jul 1997 14:39:18   Hannes
// 
//    Rev 1.31   29 Jan 1997 12:21:42   HANNES
// 
//    Rev 1.30   29 Jan 1997 08:56:56   HANNES
// Verbesserung bei der Multiselektion bei Listen
// 
//    Rev 1.29   17 Dec 1996 16:39:26   HANNES
// 
//    Rev 1.28   03 Sep 1996 10:05:06   HANNES
// Krankengeschichtseintraege beim Drucken zerteilt
// 
//    Rev 1.27   21 Jun 1996 00:22:18   GERHOLD
// Das kostet ein Bier, Gerhold !
// 
//    Rev 1.26   16 Jun 1996 18:49:04   GERHOLD
// OnRButtonDown
// 
//    Rev 1.25   18 May 1996 20:48:50   HANNES
// Fuellen der Liste in ::Paint ausgelagert
// 
//    Rev 1.24   06 May 1996 17:17:52   HANNES
// Nicht wiederholbare Script
// 
//    Rev 1.23   06 May 1996 12:56:38   HANNES
// SubScrollen
// 
//    Rev 1.22   13 Apr 1996 19:58:14   HANNES
// Eintraege, die groesser als eine Seite sind, verbessert
// 
//    Rev 1.21   26 Mar 1996 18:49:52   MARTIN
// endpage: Parameter last
// 
//    Rev 1.20   16 Feb 1996 14:46:44   GERHOLD
// isMultiSel
// 
//    Rev 1.19   02 Feb 1996 10:59:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.18   20 Nov 1995 11:44:30   HANNES
// DDSLIST_GETSELCOUNT, AnzElemsInSelection
// 
//    Rev 1.17   09 Jun 1995 00:32:02   HANNES
// Verbesserte Initialisierung bei Speicherlisten
// 
//    Rev 1.16   19 May 1995 18:43:24   GERHOLD
// ????
// 
//    Rev 1.15   02 May 1995 13:49:38   HANNES
// Verbessertes Init - Handling, CreateDlgList erweitert
// 
//    Rev 1.14   20 Mar 1995 12:16:04   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.13   06 Feb 1995 16:51:54   HANNES
// 
//    Rev 1.12   20 Jan 1995 15:49:32   HANNES
// Multiselektion
// 
//    Rev 1.11   19 Nov 1994 15:44:00   GERHOLD
// DDSList drucken
// 
//    Rev 1.10   07 Nov 1994 11:45:24   HANNES
// 
//    Rev 1.9   31 Oct 1994 10:42:56   hannes
// DDSLIST_REMOVEELEM
// 
//    Rev 1.8   27 Oct 1994 15:11:18   GERHOLD
// #define DDSLIST_DELBUTTONPRESSED
// 
//    Rev 1.7   22 Sep 1994 16:11:56   GERHOLD
// 
//    Rev 1.6   05 Sep 1994 15:36:14   HANNES
// DrawBottom
// 
//    Rev 1.5   30 Aug 1994 10:42:36   HANNES
// Prototype von DDSListNotify
// 
//    Rev 1.4   11 Aug 1994 09:14:12   HANNES
// DDSLIST_DESTROYLIST
// 
//    Rev 1.3   10 Aug 1994 12:14:44   GERHOLD
// SELCHANGE
// 
//    Rev 1.2   05 Aug 1994 17:16:14   HANNES
// Ladereihenfolge eingebbar
// 
//    Rev 1.1   24 Jun 1994 17:56:18   HANNES
// Neuubernahme clinicum
// 
//    Rev 1.20   07 Jan 1994 19:15:42   HANNES
// Moeglichkeit des Abbruchs in der Liste
// 
//    Rev 1.19   04 Jan 1994 17:05:34   HANNES
// Neu Member Function: IsEmpty
// 
//    Rev 1.18   18 Nov 1993 16:25:18   HANNES
// Verbessertes Scrollbalken - Handling
// 
//    Rev 1.17   18 Oct 1993 19:45:22   HANNES
// SetCharCallBack
// 
//    Rev 1.16   11 Oct 1993 11:46:08   HANNES
// Destroylist exportiert
// 
//    Rev 1.15   09 Sep 1993 19:08:44   HANNES
// Selektionen in der Single - Liste
// 
//    Rev 1.14   03 Sep 1993 15:21:46   GERHOLD
// CheckSelections  public+export
// 
//    Rev 1.13   18 Aug 1993 10:52:24   GERHOLD
// 
//    Rev 1.12   22 Jul 1993 14:48:18   HANNES
// DrawItem mit doPrint parameter
// 
//    Rev 1.11   20 Jul 1993 12:04:18   HANNES
// Drucken verfeinern
// 
//    Rev 1.10   19 Jul 1993 15:14:58   HANNES
// ....
// 
//    Rev 1.9   19 Jul 1993 14:49:26   GERHOLD
// Drucken
// 
//    Rev 1.8   13 Jul 1993 13:38:08   GERHOLD
// Tastaturschnittstelle + ThumbPos
// 
//    Rev 1.7   12 Jul 1993 13:28:26   GERHOLD
// Multiselektionen
// 
//    Rev 1.6   09 Jul 1993 00:45:22   HANNES
// -"-
// 
//    Rev 1.5   09 Jul 1993 00:31:40   HANNES
// Anpassung fuer die endgueltige Einbindung
// 
//    Rev 1.4   08 Jul 1993 12:06:46   HANNES
// 
//    Rev 1.3   08 Jul 1993 12:00:54   GERHOLD
// Vorbereitung fr den Einbau in die CTOOL.DLL
//
// Zeichenfunktion
typedef void (WINAPI * DRAWITEM) (HDC hPaintDC, LPVOID ElemData, LPVOID prevElemData, int x, int y,BOOL doPrint,LPVOID prParam,int y0,int y1);

// GetNext, GetPrev..
typedef LPVOID (WINAPI *GETELEM) (LPVOID PrevElem,HDC hDC, int FAR *height,LPVOID prParam);
typedef LPVOID (WINAPI *GETELEMEX) (LPVOID StartData,LPVOID BaseData,HDC hDC, int FAR *height,LPVOID prParam);
typedef LPVOID (WINAPI *UPDATEELEM) (LPVOID PrevElem,HDC hDC, int FAR *height,LPVOID prParam,DWORD TestProc,DWORD TestFlag);

// Berechnung des Scrollposition
typedef int (WINAPI *GETSCROLLPOS) (LPVOID ElemData);

// Berechnung des ersten elementes der Liste
typedef LPVOID (WINAPI *SETSCROLLPOS) (LPVOID bData,int ScrollPos,int FAR *height);

typedef BOOL (WINAPI *ISSELECTED) (LPVOID ElemData);
typedef BOOL (WINAPI *COMPAREDATA) (LPVOID Data1, LPVOID Data2,BOOL data1Full);
typedef LPVOID (WINAPI *GETFIRST) (LPVOID bData, HDC hDC, int FAR *height,LPVOID prParam,BOOL FAR *doBreak);
typedef LONG (WINAPI *PROCESSMSG) (HWND hWnd, UINT Msg, 
                                       WPARAM wParam, LPARAM lParam, BOOL FAR *Done);
typedef void (WINAPI *PRINTPAGE) (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID prParam);
typedef void (WINAPI *PRINTENDPAGE) (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID prParam, BOOL last);
typedef void (WINAPI *GETHEADER) (LPVOID bData, HDC hDC, int FAR *height);

typedef BOOL (WINAPI *SELECTSUBLINES) (int dir,int FAR *y1,int FAR *y2,HDC hDC,BOOL firstOfEntry,LPVOID bData,LPVOID lData,BOOL forPrinter);

// Aufruf bei SelChange, Selektion, Doppelklick ..
#define DDSLIST_RELEASEELE        0
#define DDSLIST_SELELE            1
#define DDSLIST_DESELELE          2
#define DDSLIST_DBLCLKELE         3
#define DDSLIST_FOCUSELE          4
#define DDSLIST_DESTRUCT          5
#define DDSLIST_DEFSEL            6
#define DDSLIST_CHARPRESSED       7
#define DDSLIST_SELECT            8
#define DDSLIST_SELCHANGE         9
#define DDSLIST_DESTROYLIST       10
#define DDSLIST_SETPAINTCOLOR     11
#define DDSLIST_RESETPAINTCOLOR   12
#define DDSLIST_DELBUTTONPRESSED  13
#define DDSLIST_REMOVEELE         14
#define DDSLIST_FORCESEL          15
#define DDSLIST_ALLOWMULTISEL     16
#define DDSLIST_GETSELCOUNT       17
#define DDSLIST_ISMULTISEL        18
#define DDSLIST_HEADERCLK         19
#define DDSLIST_FORCESEL_NOREMOVE 20
#define DDSLIST_REMOVESEL         21
#define DDSLIST_SELRANGE_HOME     22
#define DDSLIST_SELRANGE_END      23
#define DDSLIST_SELRANGE_ACTIVE   24
#define DDSLIST_AFTERSTART        25
#define DDSLIST_GETCOLOR          26
#define DDSLIST_GETFRAMETYPE      27
#define DDSLIST_CLICKDONE         28
#define DDSLIST_LBUTTONUP         29

#define LIST_STANDARD           0
#define LIST_DELBUTTON          1

typedef BOOL (WINAPI *DDSLISTNOTIFY) (LPVOID Elem,int Action,LPVOID bData);

struct charNotify {
  char ch;
  DWORD par;
  DWORD proc;
  LPVOID bData;
  };

///////////////////////////////////////////////////////////////
//  Daten, die von GetNext,GetPrev,SetScrollPos kommen,
//  muessen! mit GetGlobMem erhalten worden sein,
//  und werden von der Liste wieder freigegeben
//
//  Die Liste muss so gross sein, dass mindestens 2 Elemente
//  Platz haben, ansonsten koennte es zu Problemen kommen
///////////////////////////////////////////////////////////////
struct ListElem {
  ListElem FAR *Next;
  ListElem FAR *Prev;
  int height;
  BOOL isSel;
  BYTE Data[1]; // Hier stehen die Daten, die mit GetElem
  };

class FAR wlobj {
 public :
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };


#define GWL_LISTPTR 0

/*------------------------------------------------------------------*\
*                                                                    *
*                          Klasse DDSList                            *
*                                                                    *
\*------------------------------------------------------------------*/
#define REFRESHMODE_START   0
#define REFRESHMODE_END     1
class FAR DDSList : public wlobj {
 public:
  HWND    hWndList, DoNotify;
  int     x, y;
  DWORD   ccPar,ccProc;

  // CONSTRUCTOR
#ifdef EINSCHOENESBEISPIEL
  DLLExport _export WINAPI DDSList 
          (int px, int py,DRAWITEM draw,GETELEM Init,UPDATEELEM Update,GETELEM Next,GETELEM prev,
                   GETSCROLLPOS getscrollpos,SETSCROLLPOS setscrollpos,DDSLISTNOTIFY notify,
                   ISSELECTED IsSel, COMPAREDATA Compare, GETFIRST getfirst, GETLAST getlast,
                   int yscrollmax, LPVOID StartData,LPVOID bData, HWND donotify
          );
#endif
  DLLExport _export WINAPI DDSList 
          (int px, int py,
           int yscrollmax, LPVOID StartData,LPVOID bData, HWND donotify
          );
  void DLLExport _export WINAPI SetPrCallbacks (PRINTPAGE drawheadline, PRINTPAGE drawbottomline,PRINTPAGE startPage,PRINTENDPAGE endPage);
  BOOL InPrinting;
  void StartPrinting ()
    {
    InPrinting = TRUE ;
    }
  void EndPrinting ()
    {
    InPrinting = FALSE ;
    }
                        
  // DESTRUCTOR
  virtual DLLExport _export WINAPI ~DDSList ();

  DLLExport void _export WINAPI Create(HWND hWndParent,DWORD Style,int x,int y,int w,int h);
  DLLExport void _export WINAPI InsertElem (LPVOID StartElem, LPVOID ElemToInsert);
  DLLExport HWND _export WINAPI ListWnd ();
  DLLExport void _export WINAPI PrintList (Printer FAR *Pr,LPVOID param);
  DLLExport void _export WINAPI RefreshList (int mode,LPVOID StartData = NULL);
  DLLExport void _export WINAPI InnerUpdateList (DWORD utp,DWORD utf);
  DLLExport void _export WINAPI RemoveElem (LPVOID ElemToRemove);
  DLLExport void _export WINAPI ReleaseElem (LPVOID ElemToRelease);
  DLLExport void _export WINAPI Show (BOOL SubSelFollows);
  DLLExport void _export WINAPI Adjust ();
  DLLExport void _export WINAPI UpdateElement (LPVOID ElemToUpDate);
  DLLExport void _export WINAPI CheckSelections (BOOL doIV);
  DLLExport void _export WINAPI DestroyList ();
  DLLExport void _export WINAPI SetCharCallback (DWORD parameter,DWORD procPtr);
  DLLExport BOOL _export WINAPI TryToSetCurrentElem (LPVOID ElemToSetCurrent);

  virtual void           OnRButtonDown (HMENU hPopupMenu);

  DLLExport void _export WINAPI CheckSelections_scroll (BOOL lower,BOOL doIV);
  void SelectWholeRange (ListElem FAR *h,WORD Command);
  BOOL AdditionalMultiSel ();
  BOOL isMultiSel ();

 private :
  //--------------------------------------------------------------------
  // Variablen
  //--------------------------------------------------------------------
  BOOL            EndReached,BegReached;
  ListElem FAR    *head, FAR *tail;
  LPVOID          bData;
  ListElem FAR*   CurrentElem;      // fokussiertes Element
  int             gheight;          // Gesamthoehe aller Element in der Liste
                                    // (!= Hoehe des Fensters)
  static BOOL     Registered;
  LPVOID          StartElem;
  int             wheight;          // Höhe des Fensters
  int             hdHeight;
  int             yscrollrange;
#ifdef BUTTON_INCLUDED
  LPSINGLELIST buttons;
#else
  LPVOID buttons;
#endif
  //--------------------------------------------------------------------
  // Funktionszeiger
  //--------------------------------------------------------------------
  GETSCROLLPOS  GetScroll;
  COMPAREDATA   CompareData;
  DRAWITEM      DrawItem;
  GETELEM       GetNext;
  GETELEM       GetPrev;
  GETELEMEX     Initialize;
  UPDATEELEM    Update;
  GETFIRST      GetFirst;
  GETFIRST      GetLast;
  ISSELECTED    IsSelected;
  DDSLISTNOTIFY Notify;
  SETSCROLLPOS  SetScroll;
  BOOL          nonRepeativePaint;

  BOOL SelSub (int dir,BOOL FirstOfEntry,BOOL doScroll);
  int LineStart,LineStop;
  BOOL InsertAtHead ();
  BOOL InsertAtTail ();
  void Scroll (int h);
  void InvalidateElemLine (ListElem FAR *h,int y1,int y2);
  void InvalidateElem (ListElem FAR *h);
  
  void LineUp (BOOL ShiftPressed,BOOL ControlPressed);
  void LineDown (BOOL ShiftPressed,BOOL ControlPressed);
  void Home (BOOL doIV = TRUE,BOOL CheckKeys = TRUE);
  void End (BOOL doIV = TRUE,BOOL SubSelFollows = FALSE,BOOL CheckKeys = TRUE);
  void PageDown (BOOL ShiftPressed,BOOL ControlPressed);
  void PageUp (BOOL ShiftPressed,BOOL ControlPressed);

 public :
  void SetCompareData (LPVOID comparedata) { CompareData = (COMPAREDATA) comparedata ; }
  void SetDrawItem (LPVOID drawitem) { DrawItem = (DRAWITEM) drawitem ; }
  void SetGetNext (LPVOID getnext) { GetNext = (GETELEM) getnext ; }
  void SetGetPrev (LPVOID getprev) { GetPrev = (GETELEM) getprev ; }
  void SetInitialize (LPVOID initialize) { Initialize = (GETELEMEX) initialize ; }
  void SetUpdate (LPVOID update) { Update = (UPDATEELEM) update ; }
  void SetGetFirst (LPVOID getfirst) { GetFirst = (GETFIRST) getfirst ; }
  void SetGetLast (LPVOID getlast) { GetLast = (GETFIRST) getlast ; }
  void SetIsSelected (LPVOID isselected) { IsSelected = (ISSELECTED) isselected ; }
  void SetNotify (LPVOID notify) { Notify = (DDSLISTNOTIFY) notify ; }
  void SetSetScroll (LPVOID setscroll) { SetScroll = (SETSCROLLPOS) setscroll ; }
  void SetGetScroll (LPVOID getscroll) { GetScroll = (GETSCROLLPOS) getscroll ; }
  void SetNonRepeativePaint ()
    { nonRepeativePaint = TRUE ; }


 private :
  PRINTPAGE     DrawHeadLine;
  PRINTPAGE     DrawBottomLine;
  PRINTPAGE     StartPage ;
  PRINTENDPAGE  EndPage ;
  DRAWITEM      DrawHeader;
  DRAWITEM      DrawBottom;
  GETHEADER     GetHeader;
  SELECTSUBLINES SelSubLines;
  LPVOID         SelSubLines_Buffer;

  BOOL          fillbackward;
  void CheckCurrentVisible (BOOL doIV);

  //--------------------------------------------------------------------
  // inline Funktionen
  //--------------------------------------------------------------------
  ListElem FAR *CopyData (LPVOID Data,int height) 
               { ListElem FAR *h = GetEleMem(Data); 
                 MoveData (h,Data,height); 
                 return h; }
  ListElem FAR *GetEleMem (LPVOID Data)
               { return (ListElem FAR *) GetGlobMem (sizeof(ListElem) + 
                                         GetBlockSize(Data)-1) ; }
  void MoveData (ListElem FAR *ele,LPVOID Data,int height)
               { lmemcpy (ele->Data,Data,GetBlockSize (Data)); 
                 ele->height = height; 
                 FreeGlobMem (Data) ; }


  //--------------------------------------------------------------------
  // private Funktionen (alphabetisch)
  //--------------------------------------------------------------------
  void AddHead (LPVOID Data,int height);
  void AddTail (LPVOID Data,int height);
  void CalculateElemRect (ListElem FAR* h, LPRECT ElemRect,int yOffs = 0);
  void CheckCurrentElem ();
  void CheckTail ();
  BOOL ExistElem(ListElem FAR *x);
  void Fill (int StartYPos,LPVOID StartData = NULL,int startHeight = 0);
  void FillHead (int gheight);
  void FillTail (int actY,BOOL FAR *doBreak = NULL);
  ListElem FAR *Find (LPPOINT pt,BOOL dontResetOld,BOOL setNew);
  void FocusElement (HDC hDC, ListElem FAR *h);
  int  FullHeight();
  void InvertElement (HDC hDC, ListElem FAR *h,BOOL doPaint = TRUE);
  void Paint (HDC hDC);
  void Register ();
  void RemoveHead ();
  void RemoveTail ();
  void ScrollDown ();      
  void ScrollUp ();
  void SetCurrentElem (ListElem FAR * h,BOOL doIV,BOOL dontResetOld);
  void NotifyFocus ();
  void SetTail ();
  BOOL IsFullOnScreen (ListElem FAR *h);
  BOOL IsFullOnScreen (ListElem FAR *h,int xExtra);
  void GetScrollRect (HWND hWnd,LPRECT r);
  int  AnzElems();
  void InitializeSize ();
  void InvalidateFull ();

  LPVOID cbdata;
  BOOL CheckAbortFlag;
  DWORD AbortFlag;
  DWORD InitProc;
  DWORD ExitProc;

  friend DLLExport long WINAPI _export ListWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
  void CallInitAbort ();
  void CallExitAbort ();

  int yOffsToShow ; // Negativ - Wert 
 public :
  BOOL ForceNextPage;

  BOOL IsEmpty ()
    { return (head == NULL) ; }
  void DoSelectSubLines (SELECTSUBLINES subl,int bufSize)
    {
    SelSubLines = subl;
    if (SelSubLines_Buffer)
      FreeGlobMem (SelSubLines_Buffer);
    if (bufSize > 0)
      SelSubLines_Buffer = GetGlobMem (bufSize);
    else
      SelSubLines_Buffer = NULL;
    }

  DLLExport void _export WINAPI SetAbort (LPVOID cbdata,DWORD flag,DWORD InitProc,DWORD ExitProc);
  DLLExport void _export WINAPI ClearAbort ();
  DLLExport BOOL _export WINAPI CheckAbort ();
  DLLExport BOOL _export WINAPI IsToAbort ();
  DLLExport void _export WINAPI SetHeaderCallBack (GETHEADER gHeader,DRAWITEM dHeader);
  void DDSList::SetBottomCallBack (DRAWITEM dBottom)
    {
    DrawBottom = dBottom;
    }
  DLLExport void _export WINAPI SetButtons ();
  void SetBackward (BOOL flag)
    { fillbackward = flag ; }
  DLLExport int _export WINAPI AnzElemsInSelection ();
  DLLExport void _export WINAPI AfterStart ();
  
  DLLExport BOOL _export WINAPI CreateDlgList (HWND hWParent,
                                        LPRECT fRect,LPRECT cRect,
                                        int doShowDelButton,int w,int h,BOOL checkAnzElems = TRUE);
  friend DLLExport BOOL _export CALLBACK DListDlgProc (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP);
  };

typedef DDSList FAR* LPDDSLIST;

#ifdef MAIN_PROG
HWND   hWndParent;
HANDLE hListInst;
#else
extern HWND   hWndParent;
extern HANDLE hListInst;
#endif
