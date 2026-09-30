//
//  $Header:   P:/marille/clinicum/include/rev/toolbar.hpv   1.106   26 Apr 2000 20:17:18   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/toolbar.hpv  $
// 
//    Rev 1.106   26 Apr 2000 20:17:18   Martin
// PageTool um optionalen Parameter erweitert
// 
//    Rev 1.105   12 Oct 1999 12:06:34   Hannes
// Menue in Stationsgraphik
// 
//    Rev 1.104   04 Aug 1999 18:27:44   Wolfgang
// 1.) skipNextChar neu.
// 2.) Date/Time-OnChar in IsCharCallbackInstalled umgebaut.
// 
//    Rev 1.103   28 Jul 1999 16:50:42   Wolfgang
// 1.) OnChar fuer ToolDate und ToolTime neu.
// 
//    Rev 1.102   11 Jan 1999 08:17:56   Hannes
// ToolEdit: F2 -> Aufruf des Menues
// 
//    Rev 1.101   09 Oct 1998 18:16:24   Hannes
// Einbau Farbfunktionen
// 
//    Rev 1.100   05 Oct 1998 11:23:40   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.99   01 Sep 1998 22:09:56   Hannes
// Update von ToolEdit endgueltig richtig (keine halbeten Sachen)
// 
//    Rev 1.98   02 Aug 1998 14:46:44   Gerhold
// _export EnableToolTips
// 
//    Rev 1.97   27 Jul 1998 12:15:42   Gerhold
// Tooltips fuer V300
// 
//    Rev 1.96   10 Jul 1998 09:09:36   Hannes
// 
//    Rev 1.95   22 May 1998 12:01:52   Hannes
// Vermerken der Groessen eines Schirms / Update kann korrekt durchgefuehrt
// werden
// 
//    Rev 1.94   15 May 1998 10:42:42   Gerhold
// ToolTime erweitert szTimeFormat, FixConnection, Reset
// 
//    Rev 1.93   05 Mar 1998 16:19:50   Gerhold
// PosControl::MoveTool   ist neu
// 
//    Rev 1.92   03 Mar 1998 08:58:58   Gerhold
// SetTooltipFont
// 
//    Rev 1.91   18 Feb 1998 10:25:50   Hannes
// Prototyp von lpactive
// 
//    Rev 1.90   10 Feb 1998 18:26:28   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.89   05 Feb 1998 17:44:38   Hannes
// Groubox::y0old
// 
//    Rev 1.88   01 Feb 1998 15:49:20   Gerhold
// Tooltip Verbesserungen
// 
//    Rev 1.87   16 Jan 1998 13:29:22   Gerhold
// Vorbereitung auf 32-Bit ToolTip
// 
//    Rev 1.86   05 Jan 1998 07:48:08   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.85   01 Dec 1997 19:38:38   Hannes
// Diverse Anpassungen
// 
//    Rev 1.84   19 Nov 1997 18:45:24   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.83   24 Oct 1997 10:13:20   Gerhold
// Vorbereitung fuer ToolTip
// 
//    Rev 1.82   19 Sep 1997 12:56:58   Gerhold
// ToolEdit ... OnKillFocus, KillFocusProc;  SetOnSetFocus (bKillFocus)
// 
//    Rev 1.81   02 Sep 1997 16:24:52   gerhold
// neuer Knopfstil (Win95 like)
// 
//    Rev 1.80   25 Aug 1997 10:54:44   gerhold
// ColorRect um Penhandle2 erweitert
// 
//    Rev 1.79   24 Apr 1997 14:10:28   Hannes
// Beschleungigung von BitMerge
// 
//    Rev 1.78   11 Apr 1997 11:41:38   Gerhold
// OnScreenDown jetzt auch mit rechter Maustaste
// 
//    Rev 1.77   21 Mar 1997 11:31:34   Hannes
// IsCharCallbackInstalled
// 
//    Rev 1.76   14 Mar 1997 10:33:48   Gerhold
// 
//    Rev 1.75   28 Feb 1997 14:52:08   Gerhold
// kontextsensitive Tool-Menus koennen per Scriptbefehl erweitert werden
// 
//    Rev 1.74   21 Jan 1997 09:21:02   HANNES
// 
//    Rev 1.73   19 Dec 1996 08:22:56   HANNES
// POPUPPOS
// 
//    Rev 1.72   09 Dec 1996 18:23:48   HANNES
// Mouseprozedur in Schrimen
// 
//    Rev 1.71   26 Nov 1996 08:08:12   HANNES
// Automatischer Update
// 
//    Rev 1.70   30 Oct 1996 08:42:42   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.69   18 Sep 1996 20:49:02   HANNES
// 
//    Rev 1.68   25 Jul 1996 20:02:56   GERHOLD
// 
//    Rev 1.67   16 Jun 1996 18:52:16   GERHOLD
// rechte Maustaste, CapDC+MemDC raus, GetToolCoordinates
// 
//    Rev 1.65   11 Apr 1996 09:02:38   GERHOLD
// ToolEdit::SetObjectColor
// 
//    Rev 1.64   18 Mar 1996 16:40:34   GERHOLD
// SetToolObjectColor, virtual tool::SetObjectColor,
// ActionRect reagiert auf TABS (HasTabstop = TRUE)
// 
//    Rev 1.63   16 Feb 1996 14:47:08   GERHOLD
// HBITMAP MultiOn, MultiOff
// 
//    Rev 1.62   04 Feb 1996 15:45:42   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.61   02 Feb 1996 10:59:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.60   11 Jan 1996 03:37:24   HANNES
// HotKeyAction
// 
//    Rev 1.59   02 Jan 1996 22:21:58   HANNES
// 
//    Rev 1.58   12 Dec 1995 12:14:32   GERHOLD
// screen::OnKillFocus (neue Prozedur)
// 
//    Rev 1.57   23 Nov 1995 18:03:42   hannes
// FOCUSMODES, SetToolFocus-Funktionen haben eienen neuen Parameter "mode"
// 
//    Rev 1.56   20 Nov 1995 11:45:16   HANNES
// 
//    Rev 1.55   31 Oct 1995 10:57:20   GERHOLD
// TextPushCheckButton
// 
//    Rev 1.54   16 Oct 1995 13:31:40   GERHOLD
// Hotkeys (statt 2 Bytes jetzt 4 Bytes ... HotKeyData)
// class screen ... destroyIsDone
// 
//    Rev 1.53   24 Sep 1995 19:08:20   MARTIN
// 
//    Rev 1.52   16 Sep 1995 02:21:06   HANNES
// 
//    Rev 1.51   16 Sep 1995 02:05:42   HANNES
// 
//    Rev 1.50   11 Sep 1995 20:25:34   HANNES
// OnSetFocusProc
// 
//    Rev 1.49   08 Sep 1995 10:12:14   MARTIN
// GetMixColor
// 
//    Rev 1.48   07 Sep 1995 09:01:48   HANNES
// 
//    Rev 1.47   27 Aug 1995 13:05:48   HANNES
// 
//    Rev 1.46   24 Aug 1995 00:12:20   HANNES
// Debuggerverbesserun
// 
//    Rev 1.45   23 Aug 1995 11:06:44   GERHOLD
// 
//    Rev 1.44   16 Aug 1995 08:53:02   HANNES
// Palettenhandling der 16 Farben Bitmaps
// 
//    Rev 1.43   12 Aug 1995 19:31:24   HANNES
// Palettenhandling
// 
//    Rev 1.42   12 Aug 1995 19:25:16   HANNES
// 
//    Rev 1.41   12 Aug 1995 19:24:22   GERHOLD
// ColorRect kann auch Muster
// 
//    Rev 1.40   10 Jul 1995 19:59:00   GERHOLD
// ColorRect
// 
//    Rev 1.39   04 Jul 1995 20:39:56   HANNES
// 16 Farbenbitmaps
// 
//    Rev 1.38   03 Jul 1995 12:45:44   HANNES
// GetActiveTopWindow
// 
//    Rev 1.37   02 Jul 1995 18:27:06   HANNES
// BitSelect, Palettenhandling ...
// 
//    Rev 1.36   27 Jun 1995 15:05:00   HANNES
// 
//    Rev 1.35   27 Jun 1995 14:02:32   HANNES
// DrawTransparentBitmap
// 
//    Rev 1.34   26 Jun 1995 10:21:48   GERHOLD
// Paletten-Handling in WndList, ScreenList, Static- u. Transparentbitmap.
// 
//    Rev 1.33   20 May 1995 16:20:10   HANNES
// ToolEdit::SetMaxSize
// 
//    Rev 1.32   19 May 1995 18:56:54   HANNES
// Editfenster mit Comboenable erweitert
// 
//    Rev 1.31   19 May 1995 15:09:48   GERHOLD
// Tool-Date, -Time, -Float, -Shortint werden, falls selektiert, bei
// einer Neueingabe geloescht.
// 
//    Rev 1.30   17 May 1995 11:33:00   HANNES
// 
//    Rev 1.29   13 Apr 1995 12:54:06   HANNES
// 
//    Rev 1.28   05 Apr 1995 16:46:14   GERHOLD
// 
//    Rev 1.27   04 Apr 1995 12:09:40   HANNES
// 
//    Rev 1.26   31 Mar 1995 13:12:00   HANNES
//  
// 
//    Rev 1.25   27 Mar 1995 13:17:56   HANNES
// 
//    Rev 1.24   24 Mar 1995 18:35:38   GERHOLD
// 
//    Rev 1.23   20 Mar 1995 12:14:50   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.22   24 Feb 1995 11:07:32   GERHOLD
// ScreenList hat zwei neue Eintraege: ParentScreen u. ChildScreen
// 
//    Rev 1.21   06 Feb 1995 16:51:56   HANNES
// 
//    Rev 1.20   15 Dec 1994 18:58:52   HANNES
// Klassennamen extern vergeben
// 
//    Rev 1.19   13 Dec 1994 14:02:40   GERHOLD
// Combo-Button wurde erweitert.
// 
//    Rev 1.18   09 Dec 1994 16:01:48   GERHOLD
// win_ass_failed mit _export deklariert!
// 
//    Rev 1.17   08 Dec 1994 22:03:38   HANNES
// Reihenfolgenhandling in modalen Dialogboxen
// 
//    Rev 1.16   20 Nov 1994 18:30:28   HANNES
// IconTool::NotifyActiveEle
// 
//    Rev 1.15   31 Oct 1994 09:49:56   GERHOLD
// TextCheck- und TextRadioButton haben jetzt 5 Knoepfe.
// 
//    Rev 1.14   20 Oct 1994 17:47:30   GERHOLD
// Einige member-functions in ToolEDit von void auf LPSTR
// 
//    Rev 1.13   04 Oct 1994 08:49:06   GERHOLD
// #Up-Down Element disabled und besser gezeichnet
// 
//    Rev 1.12   20 Sep 1994 11:28:10   HANNES
// Mappen in Dialogboxen, IconTool
// 
//    Rev 1.11   07 Sep 1994 16:26:50   GERHOLD
// Combo-Button so gezeichnet, da� er im Edit-Element liegt.
// 
//    Rev 1.10   05 Sep 1994 13:17:32   GERHOLD
//  UpDown-Control, Edit-Elemente mit Combo-Button sind nicht mehr editierbar
//  Begin-, Continue-, EndCapture auf On_LButtonDown, On_MouseMove,
//  On_LButtonUp geaendert.
// 
//    Rev 1.9   31 Aug 1994 15:43:30   GERHOLD
// 
//    Rev 1.8   28 Aug 1994 11:36:04   GERHOLD
// DesiredClientSize ... Groesse des Clients in Screen-Koordinaten
// 
//    Rev 1.7   26 Aug 1994 12:18:56   GERHOLD
// ToolTime, ToolShortInt
// 
//    Rev 1.6   17 Aug 1994 09:37:54   HANNES
// Aufloesungsunabhaengigkeit
// 
//    Rev 1.5   05 Aug 1994 11:58:30   GERHOLD
// XYFromRect, BmPTextPushButton
// 
//    Rev 1.4   12 Jul 1994 14:47:56   GERHOLD
// Line3D
// 
//    Rev 1.3   11 Jul 1994 10:41:50   HANNES
// ?
// 
//    Rev 1.2   05 Jul 1994 15:41:12   GERHOLD
// 
//    Rev 1.1   24 Jun 1994 17:56:34   HANNES
// Neuubernahme clinicum
// 
//    Rev 1.44   14 Apr 1994 16:57:04   HANNES
// ToolEdit::SetOverwrite
// 
//    Rev 1.43   13 Apr 1994 14:29:18   HANNES
// Invalidieren von GroupBox
// 
//    Rev 1.42   16 Jan 1994 18:59:16   HANNES
// Ueberfluessiger Font nicht mehr erzeugt
// 
//    Rev 1.41   13 Jan 1994 16:02:04   HANNES
// ToolEdit::SetCaretToEnd
// 
//    Rev 1.40   07 Jan 1994 19:15:30   HANNES
// Invalidate im StaticTool
// 
//    Rev 1.39   04 Jan 1994 17:12:10   HANNES
// GetHelpText auch fuer ExternTool, Verwaltung eines Ids f�r die ExternTools
// 
//    Rev 1.38   29 Nov 1993 08:38:22   HANNES
// BmpFloat, StaticTool::Update
// 
//    Rev 1.37   17 Nov 1993 11:47:42   HANNES
// 
//    Rev 1.36   28 Oct 1993 12:40:40   MARTIN
// Help-Bubbles umgebaut
// 
//    Rev 1.35   18 Oct 1993 19:45:32   HANNES
// ToolBEdit
// 
//    Rev 1.34   06 Oct 1993 09:54:32   HANNES
// GetBitmap exportiert
// 
//    Rev 1.33   04 Oct 1993 08:34:52   HANNES
// Messagebeep von Movetool raus
// 
//    Rev 1.32   29 Sep 1993 12:34:56   GERHOLD
// SetToolbarTitle
// 
//    Rev 1.31   29 Sep 1993 11:02:34   GERHOLD
// ChangeToolbarSize
// 
//    Rev 1.30   27 Sep 1993 18:30:52   GERHOLD
// 
//    Rev 1.29   24 Sep 1993 22:50:14   GERHOLD
// 
//    Rev 1.28   24 Sep 1993 11:06:28   GERHOLD
// AnimationBitmap, SetFocusToObject
// 
//    Rev 1.27   17 Sep 1993 10:38:16   GERHOLD
// ActivateLayerInScreen
// 
//    Rev 1.26   16 Sep 1993 10:40:36   GERHOLD
// RemoveScreenControlFromLayer
// 
//    Rev 1.25   09 Sep 1993 19:06:54   GERHOLD
// Bubbles in Zoom, Page, Edit
// 
//    Rev 1.24   08 Sep 1993 09:14:38   HANNES
// FlapMap
// 
//    Rev 1.23   06 Sep 1993 16:20:58   GERHOLD
// 
//    Rev 1.22   24 Aug 1993 10:35:24   GERHOLD
// 
//    Rev 1.21   18 Aug 1993 10:52:18   GERHOLD
// ???
// 
//    Rev 1.20   10 Aug 1993 08:18:52   HANNES
// 
//    Rev 1.19   09 Aug 1993 19:34:26   GERHOLD
// 
//    Rev 1.18   23 Jul 1993 15:32:50   GERHOLD
// Mausfunktionen des FlapMap
// 
//    Rev 1.17   22 Jul 1993 14:37:48   GERHOLD
// FlapMap
// 
//    Rev 1.16   22 Jul 1993 08:38:34   HANNES
// Def. der tool_map
// 
//    Rev 1.15   21 Jul 1993 14:50:20   GERHOLD
// InitHotKey f�r Script vorbereiten
// 
//    Rev 1.14   21 Jul 1993 09:45:40   HANNES
// ..
// 
//    Rev 1.13   20 Jul 1993 18:29:40   GERHOLD
// ..
// 
//    Rev 1.12   16 Jul 1993 12:57:28   GERHOLD
// siehe 1.11
// 
//    Rev 1.11   16 Jul 1993 09:56:54   GERHOLD
// kleine Aenderungen in den Linien und der ActionBox
// 
//    Rev 1.10   15 Jul 1993 16:52:24   GERHOLD
// Linien un ActionBox
// 
//    Rev 1.9   15 Jul 1993 10:57:52   HANNES
// virtuelle Koordinatenumrechnungsfunktionen
// 
//    Rev 1.8   14 Jul 1993 14:50:18   GERHOLD
// statisches Bitmap
// 
//    Rev 1.7   14 Jul 1993 09:55:44   HANNES
// ToDevKoordX,ToDevKoordY nicht als Inline
// 
//    Rev 1.6   09 Jul 1993 12:06:10   GERHOLD
// HotKeyAction fuer CheckButton definiert
// 
//    Rev 1.5   09 Jul 1993 10:55:12   HANNES
// ExternTool
// 
//    Rev 1.4   09 Jul 1993 00:32:42   HANNES
// ToolStatic,Groupbox
// 
//    Rev 1.3   08 Jul 1993 11:39:14   HANNES
// StaticTool
// 
//    Rev 1.2   05 Jul 1993 14:55:40   GERHOLD
// 1.Version f�r Marille
// 
//    Rev 1.1   03 Jun 1993 12:09:24   GERHOLD
// Zwischenversion
// 
//    Rev 1.0   25 May 1993 09:54:28   GERHOLD
// Initial revision.
//

//#ifdef WIN32
//  #ifndef TOOLTIP
#define TOOLTIP
//  #endif
//#endif

#define UM_TOOLBARCHANGED        WM_USER+130
#define AM_CALCPARENTCLIENTRECT  WM_USER+120
#define WMU_TOOLTIP_TEXTCHANGED  WM_USER+140

#define FOCUSMODE_NONE      0
#define FOCUSMODE_FORWARD   1
#define FOCUSMODE_BACKWARD  2

#define IDM_HELP          100
#define IDM_HOTKEY        101
#define IDM_CUT           102
#define IDM_COPY          103
#define IDM_PASTE         104
#define IDM_TODAY         105
#define IDM_TIME          106
#define IDM_CALENDAR      107

union DoExtern_Param {
  struct {
    LPVOID objData;
    LPVOID privData;
    HWND   hWnd;
    HWND   hWParent;
    int    x,y,w,h;
    } load;
  struct {
    LPVOID objData;
    LPVOID privData;
    } update;
  struct {
    LPVOID objData;
    LPVOID privData;
    BOOL doClear;
    } reset;
  struct {
    LPVOID objData;
    LPVOID privData;
    } fixconnection;
  struct {
    LPVOID objData;
    LPVOID privData;
    LPSTR helpText;
    } gethelptext;
  struct {
    LPVOID objData;
    BOOL flag;
    } activate;
  struct {
    LPVOID objData;
    int mode;
    BOOL done;
    } focus;
  };
typedef DoExtern_Param FAR *LPDEPAR;
typedef void (WINAPI * DOEXTERN) (LPVOID cmd,WORD Action,
                                        LPDEPAR p
                                     );
typedef DOEXTERN (WINAPI * GETEXTFUNC) (WORD FncNmbr,DOEXTERN oldFnc);

#define WITHINDDS
#ifdef WITHINDDS
#define RETIRED                  177
#define TOOLTYPE_PUSHBUTTON      275
#define TOOLTYPE_CHECKBUTTON     276
#define TOOLTYPE_TEXTPUSHBUTTON  277
#define TOOLTYPE_TEXTCHECKBUTTON 278
#define TOOLTYPE_GROUPBOX        298
#define TOOLTYPE_COMBOBUTTON     280
#define TOOLTYPE_TEXTRADIOBUTTON 279
#define TOOLTYPE_ZOOM            282
#define TOOLTYPE_PAGE            283
#define TOOLTYPE_EDIT            281
#define TOOLTYPE_DATE            284
#define TOOLTYPE_FLOAT           285
#define TOOLTYPE_STATIC          299
#define TOOLTYPE_STATICBITMAP    309
#define TOOLTYPE_3DLINE          310
#define TOOLTYPE_COLORLINE       311
#define TOOLTYPE_ACTIONRECT      312
#define TOOLTYPE_FLAPMAP         339
#define TOOLTYPE_PASSWORD        379
#define TOOLTYPE_PUSHCHECKBUTTON 426
#define TOOLTYPE_TRANSPARENTBITMAP 430
#define TOOLTYPE_ANIMATIONBITMAP 431
#define TOOLTYPE_CONTEXTHELP     435
#define TOOLTYPE_BEDIT           486
#define TOOLTYPE_COLORRECT       515
#define TOOLTYPE_BMPFLOAT        516
#define TOOLTYPE_XYFROMRECT        33
#define TOOLTYPE_BMPTEXTPUSHBUTTON 34
#define TOOLTYPE_TIME              50
#define TOOLTYPE_SHORTINT          51
#define TOOLTYPE_UPDOWN            52
#define TOOLTYPE_ICON             124
#define TOOLTYPE_SHOWTRANSPARENTBITMAP  466
#define TOOLTYPE_BITSELECT              468
#define TOOLTYPE_LONGINT          637
#define TOOLTYPE_MONEY            638
#define TOOLTYPE_PALETTE          648
#define TOOLTYPE_BITEDIT          649
#define TOOLTYPE_BITMERGE         651
#define TOOLTYPE_TEXTMERGE        660
#define TOOLTYPE_TEXTPUSHCHECKBUTTON    670

#else
#define TOOLTYPE_PUSHBUTTON      3 
#define TOOLTYPE_CHECKBUTTON     4
#define TOOLTYPE_TEXTPUSHBUTTON  5
#define TOOLTYPE_TEXTCHECKBUTTON 6
#define TOOLTYPE_GROUPBOX        7
#define TOOLTYPE_COMBOBUTTON     8
#define TOOLTYPE_TEXTRADIOBUTTON 9
#define TOOLTYPE_ZOOM            20
#define TOOLTYPE_PAGE            21
#define TOOLTYPE_EDIT            25
#define TOOLTYPE_DATE            268
#define TOOLTYPE_FLOAT           269
#define TOOLTYPE_XYFROMRECT        17
#define TOOLTYPE_BMPTEXTPUSHBUTTON 18
#define TOOLTYPE_TIME              34
#define TOOLTYPE_SHORTINT          35
#endif

#define GWL_SCREEN            0
#define GWL_MAPPTR            4



#define ID_CBCHAR             101
#define ID_CHCTRL             102
#define ID_CHSHIFT            103
#define ID_CHALT              104

class FAR wtobj {
 public :
  LPVOID operator new (size_t size);
  void operator delete (LPVOID obj);
  };


class FAR ActionElem;
class FAR tool;

/*------------------------------------------------------------*\
*               Verwaltung der Tool-Elemente                   *
\*------------------------------------------------------------*/
class FAR WndList;
class FAR ScreenList;

void InsertToWndList (WndList FAR *wndl);
void DelFromWndList (WndList FAR *wndl);

/*--------------------------------------------------------------------*\
*  Liste fuer jedes Fenster das auf dem Schirm gezeigt wird bzw. wurde *
\*--------------------------------------------------------------------*/
typedef WndList FAR *LPWNDLIST ;

class FAR WndList : public wtobj {
 public :
  tool FAR       *first;    // Zeiger auf das erste Tool-Element
  int            Layer;     // Nr. des Layers
  WndList FAR    *Next;     // naechstes Fenster
  ScreenList FAR *Parent;   // Zu welchem Toolbarfenster gehoert der
                            // Schmutz
  HWND           RefWnd;    // Handle dieses Fensters
  int            yHeight;   // Hoehe des Layers in Pixel


  WndList (HWND RWnd,int L,ScreenList FAR *sc);   // Constructor 
  virtual ~WndList ();

  void ActivateHotKeys (BOOL State);
  void ActivateTheTools (BOOL state);
  void ChangeParent ();
  void CheckLayerHeight (int y)      { if (y > yHeight) yHeight = y ; }
  void DelFromList (tool FAR *);                      // Tool loeschen
  WndList FAR *Find (HWND hWnd);         // suche das Element mit dem Handle
  tool FAR * GetFirstTool ();
  tool FAR * GetLastTool ();
  WndList FAR *GetWindowWithLayer (int Layer);
  tool FAR * HitTest (LPPOINT lP);
  void Insert (tool FAR *);                           // Tool einfuegen
  void PaintTheTools (HDC hDC,HDC hMemDC);  // zeichne alle Tools in der Liste
  tool FAR *Search (WORD Id);
  void OnMouseMove (WPARAM wP,LPARAM lP);
  };




/*------------------------------------------------------------------*\
*  TOOLSTRUCT                                                        *
\*------------------------------------------------------------------*/
struct tool_header {
  WORD  ToolType;        // Typ des Tool-Elementes
  WORD  structSize;
  tool FAR *MyTool;     // Zeiger auf ein Tool
  DWORD ObjId;
  DWORD ScreenId;
  DWORD _Layer;
  DWORD _x, _y;
  DWORD HotKey;
  };
typedef tool_header FAR *LPTOOLHEADER;

struct BitMapRef {
  DWORD bitId;
  DWORD _Col;             // Spalte der Teil-Bitmap
  DWORD _Row;             // Zeile der Teil-Bitmap
  };

struct tool_simple {
  tool_header hd;
  };

struct tool_help {
  tool_header hd;
  DWORD       Id;    // Adresse von CallCommand
  };

/*------------------------------------------------------------------*\
*  Struktur fuer einen Bit-Button                                    *
\*------------------------------------------------------------------*/
struct tool_button {
  tool_header hd;
  DWORD Id;             // Referenz auf Status
  DWORD Disabled;
  DWORD Help;
  BitMapRef btn[1];     // Array von Teil-Bitmaps fuer diesen Button
  };

struct tool_pushbutton {
  tool_header hd;
  DWORD Id;             // Adresse von CallCommand
  DWORD Disabled;
  DWORD Help;
  BitMapRef btn[1];     // Array von Teil-Bitmaps fuer diesen Button
  };

struct tool_pushcheckbutton {
  tool_header hd;
  DWORD Id;             // Referenz auf Status
  DWORD Disabled;
  DWORD Help;
  DWORD Proc;           // Prozedur, die aufgerufen werden soll
  BitMapRef btn[1];     // Array von Teil-Bitmaps fuer diesen Button
  };

struct textpush_button {
  tool_header hd;
  DWORD Id;             // Adresse von CallCommand
  DWORD Disabled;
  DWORD Help;
  DWORD _w, _h;
  DWORD ButtonText;
  DWORD _Format;
  };

struct textpushcheckbutton {      // Selbe Struktur wie textpush_button
  tool_header hd;
  DWORD Proc;           // Prozedur, die aufgerufen werden soll
  DWORD Disabled;
  DWORD Help;
  DWORD _w, _h;
  DWORD ButtonText;
  DWORD _Format;
  DWORD State;          // Referenz auf Status
  };

struct bmptextpush_button {
  tool_header     hd;
  DWORD Id;             // Adresse von CallCommand
  DWORD Disabled;
  DWORD Help;
  DWORD _w, _h;
  DWORD ButtonText;
  DWORD _Format;

  BitMapRef btn;
  };

struct textcheck_button {
  tool_header hd;
  DWORD Id;             // Adresse von CallCommand
  DWORD Disabled;
  DWORD Help;
  BitMapRef btn[5];     // Array von Teil-Bitmaps fuer diesen Button
  DWORD     CheckText;
  DWORD _Format;
  DWORD _w;
  };

struct textradio_button {
  tool_header hd;
  DWORD Id;             // Adresse des Flags das gesetzt wird
  DWORD Disabled;
  DWORD Help;
  BitMapRef btn[5];     // Array von Teil-Bitmaps fuer diesen Button
  DWORD CheckText;
  DWORD _Format;
  DWORD _Width;
  DWORD Proc;           // Adresse von CallCommand
  };

struct combo_button {
  tool_header hd;
  DWORD Id;
  DWORD Disabled;
  DWORD Help;
  BitMapRef btn[1];     // genau 1 Bitmap
  DWORD EditObj;
  };

struct up_down {
  tool_header hd;          // Prozedur fuer den oberen Knopf
  DWORD       UpProc;      // Prozedur fuer den unteren Knopf
  DWORD       DownProc;
  DWORD       Disabled;
  DWORD       Help;
  DWORD       EditObj;     // anzusteuerndes Edit-Element
  };

struct tool_edit {
  tool_header hd;
  DWORD _Id;
  DWORD _Disabled;
  DWORD Help;
  DWORD _Width;
  DWORD _Format;
  DWORD _AnzLines;
  DWORD DoSelect;
  DWORD intermWidth;
  };

struct FAR tool_float {
  tool_edit ed;
  DWORD txtFormat;
  BOOL IsThereFormat() {
    return ((ed.hd.structSize + sizeof(WORD)) == sizeof(*this)) ;
    };
  };

struct tool_map {
  tool_header hd;
  DWORD Id;         // Referenz auf den String
  DWORD ExternTool; // Referenz auf ein Fenster - Handle (Bsp. einer Liste)
  DWORD Disabled;
  DWORD Help;
  DWORD _Width;      // Breite eines Hebels
  DWORD _AnzLines;   // Anzahl Hebel
  DWORD _dx;         // hor. Abstand von 2 Hebeln
  DWORD StrToWrite;
  DWORD CallOnChange;
  };

struct tool_BmpFloat {
  tool_header hd;
  DWORD Id;         // Referenz auf den Float - Wert
  DWORD Disabled;   // Enable - Flag
  DWORD Help;       // Hilfe - String
  DWORD _w,_h;        // Breite, Hoehe des angezeigten Rechteckes
  DWORD rmin,rmax;  // Randwerte, die fuer die Skalierung genommen werden
  DWORD lpmin,lpmax;// Minima - und Maximal - Werte, auf die Gekappt wird
  DWORD staticTool; // Referenz auf ein Static - Tool, wo der aktuelle Wert
                    // geschrieben wird
  BitMapRef pattern;// Zeichnung, die Unterlagert werden soll
  };

struct FAR HotKeyData {
  BYTE VirtKey;
  BYTE Modify;
  BYTE VirtKey1;
  BYTE Modify1;
  } ;

struct FAR HotKeyStruct {
  WORD  FncNr;             // interne Nr. des Hotkeys;
  WORD  parSize;
  DWORD hkRef;             // Referenz auf die Hotkeydaten
  LONG  VKey;              // Taste
  LONG  Flags;             // SHIFT, CTRL, ALT
  };

struct zoom_tool {
  tool_header hd;
  DWORD Id;                    // Referenz auf den Faktor
  DWORD Disabled;
  DWORD Help;
  DWORD _w, _h;
  DWORD _StartRange, _EndRange;
  DWORD _Sections;             // Anzahl der Spr�nge im Bereich z.B.: 10 Einteilungen 
  DWORD _Type;                 // 0 linear, 1 log. 
  };

struct page_tool {
  tool_header hd;
  DWORD _Id;             // Adresse von CallCommand
  DWORD _Disabled;
  DWORD Help;
  DWORD _w, _h;
  DWORD _AnzPages;
  DWORD _PagesToShow;
  };

struct tool_static {
  tool_header hd;
  DWORD _w;
  DWORD _Format;
  DWORD Text;
  DWORD AnzLines;
  };

struct tool_staticbitmap {
  tool_header hd;
  BitMapRef btn;        // Bitmap
  };

struct tool_transparentbitmap {
  tool_header hd;
  DWORD _TransparentColor;
  BitMapRef btn;        // Bitmap
  };

struct tool_animationbitmap {
  tool_header hd;
  DWORD _LoopCount;
  DWORD _DelayTime;
  DWORD _TransparentColor;
  BitMapRef btn;        // Bitmap
  };

struct tool_groupbox {
  tool_header hd;
  DWORD _w;
  DWORD _h;
  DWORD _Format;
  DWORD Text;
  DWORD _Style;
  DWORD _DrawBkGround;
  DWORD _Color;
  };

struct tool_3Dline {
  tool_header hd;
  DWORD _x1;
  DWORD _y1;
  };

struct tool_line {
  tool_header hd;
  DWORD _x1;
  DWORD _y1;
  DWORD Style;
  };

struct tool_colorrect {
  tool_header hd;
  DWORD _x1;
  DWORD _y1;
  DWORD Style;
  DWORD _FillColor;
  DWORD _FillStyle;
  };

struct tool_actionrect {
  tool_header hd;
  DWORD _w;
  DWORD _h;
  DWORD Id;
  DWORD Color;
  DWORD StateFlag;
  };

struct tool_xyfromrect {
  tool_header hd;
  DWORD       Help;
  DWORD       _w, _h;
  DWORD       _XStartRange, _YStartRange;
  DWORD       _XEndRange, _YEndRange;
  DWORD       XPos;
  DWORD       YPos;
  BitMapRef   btn;
  };

/*------------------------------------------------------------------*\
* Deklaration fuer ein Tool-Rechteck                                  *
\*------------------------------------------------------------------*/
#ifndef FRECT_DEFINED
  struct FAR fRECT {
    int left,top,right,bottom;
    };
  #define FRECT_DEFINED
#endif


#ifndef NODLL
  #ifdef TOOLBAR_MAIN
    double BaseUnit;
  #else
    extern double  BaseUnit;
  #endif
#endif

#ifndef fPOINT_DEFINED
#define fPOINT_DEFINED
struct FAR fPOINT {
  int x, y;
  };
#endif

struct FAR BMPREF {
  int Col;
  int Row;
  };

extern void MyMoveTo (HDC hDC,int x,int y);
extern void MyLineTo (HDC hDC,int x,int y,double mapFact,int Style,int Width);


class FAR ActionElem : public wtobj {
 public:
  virtual BOOL IsTool ()                        { return FALSE; }
  virtual BOOL IsElemEnabled ()                 { return TRUE; }
  virtual void InitHotKey ()                    { }
  virtual void SetHotKey (HotKeyData kd)        { }
  virtual void HotKeyAction (BOOL dontCheckEnabled)                  { }
  };

DLLExport void _export WINAPI DoHotkeyAction (DWORD Tool,LPVOID PrivData);
DLLExport void _export WINAPI SetToolObjectColor (DWORD Tool, LPVOID privData, COLORREF color);
DLLExport void _export WINAPI SetEdFormat (DWORD Tool,LPVOID PrivData,int Format);


//-------------------------------------------------------------------
// Liste zum Verwalten von Menu-Eintraegen fuer die rechte Maustaste
//-------------------------------------------------------------------
struct FAR MenuList {
  MenuList FAR *Next;
  LPSTR    Text;              // Menutext
  DWORD    Proc;              // Prozedur die ausgefuehrt wird
  UINT     Id;                // eindeutiger Menu-Identifier
  UINT     Flags;             // Menu-Flags wie disabled, grayed, etc.
  LPVOID   MenuPrivData;
  LPVOID   MenuProcPar;
  };
typedef MenuList FAR * LPMENULIST;


class FAR tool : public ActionElem {
 public :
  int          tx, ty;        // Position des Tools
  BOOL         IsEnabled;
  tool FAR     *Next;         //  naechstes Tool
  WndList FAR  *Parent;       //  Zeiger auf die Elternliste
  LPVOID       privData;
  LPVOID       StructData;    //  tooleigene Struktur 
  fRECT        ToolRect;      // Abmessungen des umgebenden Rechteckes
  HWND         hWndBubble;    // Handle der Hilfe-Bubble
  int          dxPhys,dyPhys;
  LPMENULIST   lpMenu;        // kontextsensitive Menus

  tool (HWND hRefWnd,LPVOID Data,LPVOID pData,int pdSize);
  virtual ~tool ();        

  tool_simple FAR *Param()              
               { return (tool_simple FAR *) StructData ; }

  virtual BOOL  IsTool ()                        { return TRUE; }
#ifdef TOOLTIP
  virtual void  AddToolTip (HWND hWnd = NULL);
#endif
          void  AppendContextMenu (HMENU hMenu);
  virtual void  CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh) { *bmw = 0; *bmh = 0; }
  virtual void  ChangeParent (HWND hWnd)         { }
  virtual void  FixConnection ();
          void  GetHelp (POINT pt);
  virtual LPSTR GetHelpText ()                   { return NULL; }
  virtual tool  FAR *GetNext ();
  virtual tool  FAR *GetPrev ();
  virtual void  GetRect ()                       { }
  virtual BOOL  HasTabStop()                     { return FALSE ; }
  virtual BOOL  HitTest (LPPOINT pt)             { return FALSE ; }
  virtual void  HotKeyAction (BOOL dontCheckEnabled)                  { }
  virtual WORD  Id()                             { return 0xFFFF ; }
  virtual void  InitHotKey ();
  virtual void  Invalidate (BOOL doErase)        { }
  virtual BOOL  IsElemEnabled ()                 { return IsEnabled; }
  virtual BOOL  IsToolRectVisible (HDC hDC)      { return RectVisible(hDC, LPRECT(&ToolRect)); }
  virtual void  Load ();
  virtual void  MoveTool ()                      { /* MessageBeep (0) ; */ }
  virtual void  OnActivate (BOOL ActivateFlag)   { }
  virtual void  On_LButtonDown (LPPOINT pt)      { }
  virtual BOOL  On_LButtonUp (LPPOINT pt)        { return TRUE ; }                      
  virtual void  OnRButtonDown (HMENU hPopupMenu);
  virtual void  On_MouseMove (LPPOINT pt)        { }
  virtual void  OnChange ()                      { }
  virtual void  OnSetFocus ()                    { }
  virtual void  OnKillFocus ()                   { }
  virtual BOOL  OnChar (WORD wP)                 { return FALSE; }
  virtual void  OnParentNotify (WPARAM wParam)   { }
  virtual BOOL  OnCommand (HWND hWnd, WPARAM wP);
  virtual void  PaintFocus (DWORD State)         { }
  virtual void  PaintTool (HDC hDC, HDC hmemDC)  { }
          void  RemoveContextMenu ();
          void  RemoveHelp ();
#ifdef TOOLTIP
  virtual void  RemoveToolTip (HWND hWnd = NULL);
#endif
  virtual void  Reset (BOOL doClear);
          void  SetContextMenu (LPVOID menuprocparam, LPVOID menuprivData, int menuprivdatasize,
                                LPSTR text, DWORD proc, UINT flags, WORD mode);
  virtual void  SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE)  { }
  virtual void  SetHotKey (HotKeyData kd);
  virtual void  SetObjectColor (COLORREF color)  { }
  virtual void  Update ()                        { Invalidate (FALSE); Load (); }
  virtual void  OnTimer ()                       { }
          int   ToDevKoordX (LONG x);
          int   ToDevKoordY (LONG y,int Layer = 0);
          int   ToDevX (LONG x);
          int   ToDevY (LONG y);
  virtual void  OnMouseMove (WPARAM wP,LPARAM lP) { }

  void GetHKText (LPSTR res,LPSTR org,int Format);
  virtual void NewWindow (HWND wnd) { }
  };


class HelpTool : public tool {
 public:
  tool_help FAR *Param()              
              { return (tool_help FAR *) StructData ; }

  HelpTool (HWND RefWnd, LPVOID Data, LPVOID pData, int pSize)
               : tool (RefWnd,Data,pData,pSize) { IsEnabled = FALSE; };
               
  virtual void GetRect ();
  virtual void HotKeyAction (BOOL dontCheckEnabled);
  };



class StaticTool : public tool {
 public :
#ifdef CFIELD_INCLUDED
  cField FAR *field;
#else
  LPVOID field;
#endif
  int tw;

  int Format;

  StaticTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);

  tool_static FAR *Param()              
              { return (tool_static FAR *) StructData ; }

  virtual DWORD FormatRef ()
    { return Param()->_Format ; }
  void SetTwips (HDC hDC);
  void SetMMText (HDC hDC);
  void RectToDev (LPRECT r);

  virtual DWORD TextRef()   { return Param()->Text ; }

  virtual void Load ();
  virtual void Update ()                        { Invalidate (TRUE); Load (); Invalidate (TRUE); }
  virtual void GetRect ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Invalidate (BOOL doErase);
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  virtual void MoveTool ();

  virtual BOOL HitTest (LPPOINT pt);

  virtual void GetTextPos (HDC hDC,LPPOINT p);
  virtual int GetTextWidth (HDC hDC);
  virtual void  SetObjectColor (COLORREF color);
  virtual void NewWindow (HWND wnd);
  };

class BmpFloat : public tool {
 public :
  BmpFloat (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : tool (RefWnd,Data,pData,pSize) { };

  tool_BmpFloat FAR *Param()              
              { return (tool_BmpFloat FAR *) StructData ; }

  double a,b;
  double x,xmin,xmax;
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  StaticTool FAR *st;
  LPSTR  pattern;
  BMPREF BmpRef;
  int    tw, th;

  void SetText ();
  void Write ();
  virtual void Load ();
  void PaintBmp (HDC hDC,HDC hmemDC);
  void PaintBack (HDC hDC);
//  HDC CapDC;
  int xold;
  double xdold;
  BOOL Capturing;
  void Transform (int xp,double FAR &x);
  void ShowPos (double xact);
  virtual void FixConnection ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void MoveTool ();
  virtual void Invalidate (BOOL doErase);
  virtual void Reset (BOOL doClear);
  virtual BOOL HitTest (LPPOINT pt);
  virtual void On_LButtonDown (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);

  };


class StaticBitmap : public tool {
 public:
  int    AnzButtons;
  BMPREF BmpRef;

  tool_staticbitmap FAR *Param()
                     { return (tool_staticbitmap FAR *) StructData; }

  StaticBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : tool (RefWnd,Data,pData,pSize) { };

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual BOOL HitTest (LPPOINT pt);

  virtual BitMapRef FAR *BitRef ()
    { return &(((tool_staticbitmap FAR *) StructData)->btn) ; }
  virtual int GetAnzButtons ()
    { return 1 ; }
  virtual int Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };

class TransparentBitmap : public StaticBitmap {
 public:
  DWORD TransparentColor;

  TransparentBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : StaticBitmap (RefWnd,Data,pData,pSize) { };

  tool_transparentbitmap FAR *Param()
                     { return (tool_transparentbitmap FAR *) StructData; }
                     
  virtual BitMapRef FAR *BitRef ()
    { return &(((tool_transparentbitmap FAR *) StructData)->btn) ; }
  virtual int GetAnzButtons ()
    { return 1 ; }

  virtual void  Load ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  };


class AnimationBitmap : public StaticBitmap {
 public:
  BOOL StopAnimation;
  BOOL bTimerSet;
  int  LoopCount;
  
  AnimationBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);

  tool_animationbitmap FAR *Param()
                     { return (tool_animationbitmap FAR *) StructData; }
                     
  virtual BitMapRef FAR *BitRef ()
    { return &(((tool_animationbitmap FAR *) StructData)->btn) ; }
  virtual void Load ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);

  int ActBitmap ;
  int ActLoopCount ;
  virtual void OnTimer ();
  };


class Line3D : public tool {
 public:
  int  X0, Y0, X1, Y1;
  int  tx1, ty1;

  tool_3Dline FAR *Param()  { return (tool_3Dline FAR *) StructData; }

  Line3D (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : tool (RefWnd,Data,pData,pSize) { };

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual BOOL HitTest (LPPOINT pt);

  virtual int Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };


class LineTool : public tool {
 public:
  COLORREF LineColor;
  WORD     LineWidth, LineStyle;
  double   mapFact;
  HPEN     PenHandle;   // wird in <Load> erzeugt
  int      X0, Y0, X1, Y1;
  int      tx1, ty1;

  tool_line FAR *Param()  { return (tool_line FAR *) StructData; }

  LineTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : tool (RefWnd,Data,pData,pSize) 
           { PenHandle = 0; };
  virtual ~LineTool () 
           { if (PenHandle) DeleteObject(PenHandle); }

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void Update ();                        
  virtual BOOL HitTest (LPPOINT pt);

  virtual int Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };


class ColorRect : public tool {
 public:
//  COLORREF BorderColor;    // Farbe des Rahmens um das Rechteck
  COLORREF FillColor;      // Fuellfarbe
//  int      FillStyle;      // Fuell-Stil (HS_CROSS, HS_HORIZONTAL,....)
  WORD     BorderWidth, BorderStyle;
  double   mapFact;
  HPEN     PenHandle;   // wird in <Load> erzeugt
  HPEN     PenHandle2;   // wird in <Load> erzeugt
  HBRUSH   BrushHandle;
  int      X0, Y0, X1, Y1;
  int      tx1, ty1;

  tool_colorrect FAR *Param()  { return (tool_colorrect FAR *) StructData; }

  ColorRect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
               : tool (RefWnd,Data,pData,pSize) 
           { PenHandle = 0; PenHandle2 = NULL; BrushHandle = 0; };
  virtual ~ColorRect () 
           { if (PenHandle) DeleteObject(PenHandle); 
             if (PenHandle2) DeleteObject(PenHandle2); 
             if (BrushHandle) DeleteObject (BrushHandle); }

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void Update ();                        
  virtual BOOL HitTest (LPPOINT pt);

  virtual int Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };

class ActionRect : public tool {
 public:
  BOOL     IsPressed;
  COLORREF BkColor;
  int      StateFlag;
//  HDC      CapDC;
  BOOL     Capturing;

  int      tw, th;

  tool_actionrect FAR *Param()  { return (tool_actionrect FAR *) StructData; }

  ActionRect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) : tool (RefWnd, Data, pData, pSize)  
    { IsPressed = FALSE; Capturing = FALSE; /*CapDC = FALSE;*/ }

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual BOOL  HasTabStop ()
    { return IsEnabled ; }
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintState ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);

  void PressIn();
  void PressOut();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void On_LButtonDown (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);

  virtual int Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };


#define DO_LOAD             0
#define DO_SETCONNECTION    1
#define DO_RESET            2
#define DO_UPDATE           3
#define DO_GETHELP          4
#define DO_ACTIVATE         5
#define DO_SETFOCUS         6
struct ExternTool_param {
  tool_header hd;
  DWORD Disabled;
  DWORD _w;
  DWORD _h;
  };

struct ShowTransparentBitmap_param {
  tool_header hd;
  DWORD obj ;
  };

struct BitSelect_param {
  tool_header hd;
  DWORD obj;
  DWORD Color;
  DWORD MoveColor;
  DWORD procPtr;
  };

struct IconTool_param {
  ExternTool_param ehd;
  DWORD cbProc;
  DWORD TableName;
  };

class FAR BitmapObject;
class ShowTransparentBitmap : public tool {
 protected :
  BitmapObject FAR *bo ;
 public :
  ShowTransparentBitmap_param FAR *Par()
    { return (ShowTransparentBitmap_param FAR *) StructData ; }
  ShowTransparentBitmap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);
  virtual void Load ();  
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void GetRect ();
  virtual void Reset (BOOL doClear);
  virtual void FixConnection ();
  virtual void Invalidate (BOOL doErase);
  };

class BitSelect : public ShowTransparentBitmap {
 public :
  DWORD Color,MoveColor;
  int State;
  BitSelect_param FAR *Par()
    { return (BitSelect_param FAR *) StructData ; }
  BitSelect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);
  virtual void Load ();  
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void OnMouseMove (WPARAM wP,LPARAM lP);
  BOOL Hit(LPPOINT lP);
  virtual BOOL HitTest (LPPOINT pt);
  void ResetSelection();
  void Select();
  };

class ExternTool : public tool {
 public :
  DOEXTERN ExtFnc;       // Funktion, die die Arbeit zu erledigen hat
  LPVOID extObj;
  HWND hExtWnd;          // Fenster, um das ein Rahmen gezeichnet werden
                         // soll
  int tw,th;

  // Konstruktor: Ermittelt die Externe Funktion
  ExternTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);
  virtual ~ExternTool ();

  ExternTool_param FAR *ExtPar ()
    { return (ExternTool_param FAR *) StructData ; }

  virtual void ChangeParent (HWND hWnd)         
    { SetParent (hExtWnd,hWnd); }
  virtual void FixConnection ();
  virtual void GetRect ();
  virtual BOOL HasTabStop ();
  virtual void HotKeyAction (BOOL dontCheckEnabled);
  virtual void Invalidate (BOOL doErase);
  virtual BOOL IsToolRectVisible (HDC hDC)      
    { RECT rc; CopyRect (&rc, LPRECT(&ToolRect)); InflateRect (&rc, 3, 2);
      return RectVisible(hDC, &rc); }
  virtual void Load ();  
  virtual void MoveTool ();
  virtual void OnActivate (BOOL ActivateFlag);
  virtual void OnRButtonDown (HMENU hPopupMenu);
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void Update ();
  virtual LPSTR GetHelpText ();
  virtual WORD Id();
  };

class IconTool : public ExternTool {
 public :
  IconTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) :
    ExternTool (RefWnd,Data,pData,pSize) { }

  IconTool_param FAR *IconPar ()
    { return (IconTool_param FAR *) StructData ; }

  virtual void Load ();  
  virtual void Reset (BOOL doClear);
  virtual void Update ();
  virtual LPSTR GetHelpText ();
  virtual void FixConnection ();
  virtual void OnActivate (BOOL ActivateFlag);

  DLLExport void _export AddPmEle (LPSTR Name,LPBITMAPINFO bi,LPVOID ExtraData);
  DLLExport void _export AddPmEle (LPSTR Name,HICON bi,LPVOID ExtraData);
  DLLExport void _export WINAPI NotifyActiveEle ();
  };

typedef IconTool FAR *LPICONTOOL ;

class FlapMap : public tool {
 public:
  char FlapChar;
  HFONT FlapFont;
  int   FlapHeight;
  int   FlapWidth;
  int   Highest;
  LPRECT FlapRects;

  int   AnzLines;
  int   tw;
  int   dx;
  
  FlapMap (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);
  virtual ~FlapMap ();

  tool_map FAR* Param() { return (tool_map FAR *) StructData; }
  virtual void On_LButtonDown (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  virtual void FixConnection ();
  virtual void GetRect ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();  
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
           int RightOffs (int i,int AnzElems,int Deepest);
  virtual void Update ();
          void SetFlapRect (int i, int Deepest);

  virtual int  Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) ; }
  };

class PushButton : public tool {
 public:
  int   AnzButtons;
//  HDC   CapDC;
  BOOL  Capturing;
  BOOL  IsPressed;
//  HDC   MemDC;
  BMPREF FAR* lpBmpRef;


  PushButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);
  virtual ~PushButton ();

  // Funktion mit Zeiger auf struct <tool_button>
  tool_pushbutton FAR   *Param()         { return (tool_pushbutton FAR *) StructData ; }

  virtual BitMapRef FAR *BitRef ()       { return ((tool_pushbutton FAR *) StructData)->btn ; }
  virtual int GetAnzButtons ()
    { return (Param()->hd.structSize + sizeof(WORD) - 
                        sizeof (tool_pushbutton)) / sizeof(BitMapRef) + 1;
    }
  virtual void           On_LButtonDown (LPPOINT pt);
  virtual void           CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh);
  virtual void           On_MouseMove (LPPOINT pt);
  virtual BOOL           On_LButtonUp (LPPOINT pt);
  virtual void           OnRButtonDown (HMENU hPopupMenu);
  virtual void           FixConnection ();
  virtual LPSTR          GetHelpText ();
  virtual void           GetRect ();
  virtual int            Gety0 ()                  { return ToDevKoordY(ty,Parent->Layer) ; }
  virtual BOOL           HasTabStop();
  virtual BOOL           HitTest (LPPOINT pt);
  virtual void           HotKeyAction (BOOL dontCheckEnabled);
  virtual void           Invalidate (BOOL doErase);

  virtual void           Load ();
  virtual void           MoveTool ();
  virtual BOOL           OnChar (WORD wP);
  virtual void           PaintButton (DWORD Style, int Index);
  virtual void           PaintFocus (DWORD State);
  virtual void           PaintState ();
  virtual void           PaintTool (HDC hDC, HDC hmemDC);
          void           PressIn();
          void           PressOut();
  virtual void           Reset (BOOL doClear);
  virtual void           SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void           Update ()                 { Invalidate (TRUE); Load (); Invalidate(FALSE); }
  };


//----------------------------------------------------------------------------
//  Checkbutton
//----------------------------------------------------------------------------
class CheckButton : public PushButton {
 public :
  BOOL ButtonState;

  CheckButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : PushButton (RefWnd,Data,pData,pSize) { };
  virtual ~CheckButton () { } ;

  tool_button FAR *Param()              
              { return (tool_button FAR *) StructData ; }

  virtual BitMapRef FAR *BitRef ()               { return ((tool_button FAR *) StructData)->btn ; }
  virtual int GetAnzButtons ()
    { return (Param()->hd.structSize + sizeof(WORD) - 
                        sizeof (tool_button)) / sizeof(BitMapRef) + 1;
    }
  virtual BOOL           On_LButtonUp (LPPOINT pt);
  virtual void           FixConnection ();
  virtual void           HotKeyAction (BOOL dontCheckEnabled);
  virtual void           Load ();
  virtual BOOL           OnChar (WORD wP);
  virtual void           PaintState ();
  virtual void           Reset (BOOL doClear);
  };

//----------------------------------------------------------------------------
//  PushCheckbutton
//----------------------------------------------------------------------------
class PushCheckButton : public CheckButton {
 public :
  BOOL ButtonState;

  PushCheckButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : CheckButton (RefWnd,Data,pData,pSize) { };
  virtual ~PushCheckButton () { } ;

  tool_pushcheckbutton FAR *Param()              
              { return (tool_pushcheckbutton FAR *) StructData ; }

  virtual BitMapRef FAR *BitRef ()               { return ((tool_pushcheckbutton FAR *) StructData)->btn ; }
  virtual int GetAnzButtons ()
    { return (Param()->hd.structSize + sizeof(WORD) - 
                        sizeof (tool_pushcheckbutton)) / sizeof(BitMapRef) + 1;
    }
  virtual BOOL           On_LButtonUp (LPPOINT pt);
  virtual void           HotKeyAction (BOOL dontCheckEnabled);
  };

//----------------------------------------------------------------------------
//  TextPushbutton
//----------------------------------------------------------------------------
#define DEFFORMAT     2
class TextPushButton : public PushButton {
 public: 
  LPSTR ButtonText;
  int   tw, th;      // Breite und Hoehe des Knopfes
  fRECT TextRect;

#ifdef CFIELD_INCLUDED
  cField FAR *field;
#else
  LPVOID field;
#endif
  int Format;
  
  TextPushButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : PushButton (RefWnd,Data,pData,pSize) { };
  virtual ~TextPushButton () { } ;

  textpush_button FAR *Param()              
              { return (textpush_button FAR *) StructData ; }
  virtual DWORD FormatRef ()
    { return Param()->_Format ; }

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintFocus (DWORD State);
  virtual void PaintButton (DWORD Style, int Index);
  virtual void Reset (BOOL doClear);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void DrawButtonText (HDC hDC, int Offset);

  void SetTwips (HDC hDC,int x = 0,int y = 0);
  void SetMMText (HDC hDC);
  void RectToDev (LPRECT r);

  virtual DWORD TextRef()   { return Param()->ButtonText ; }
  virtual void GetTextPos (HDC hDC,LPPOINT p);
  virtual int GetTextWidth (HDC hDC);
  };

class TextPushCheckButton : public TextPushButton {
 public :
  BOOL ButtonState;

  textpushcheckbutton FAR *Param()              
              { return (textpushcheckbutton FAR *) StructData ; }

  TextPushCheckButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
       : TextPushButton (RefWnd,Data,pData,pSize) { };
  virtual ~TextPushCheckButton () { } ;

  virtual void Load ();
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  virtual void PaintState ();
  virtual void HotKeyAction (BOOL dontCheckEnabled);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  };

//----------------------------------------------------------------------------
//  BmpTextPushbutton
//----------------------------------------------------------------------------
class BmpTextPushButton : public TextPushButton {
 private:
   int bmWidth, bmHeight;
 
 public:
  BmpTextPushButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
       : TextPushButton (RefWnd,Data,pData,pSize) { };
  virtual ~BmpTextPushButton () { } ;

  bmptextpush_button FAR *Param()              
              { return (bmptextpush_button FAR *) StructData ; }
  virtual DWORD FormatRef ()
    { return Param()->_Format ; }
  virtual BitMapRef FAR *BitRef ()
    { return &(((bmptextpush_button FAR *) StructData)->btn); }
  virtual int GetAnzButtons ()
    { return 1 ; }

  virtual void Load ();
  virtual void GetRect ();
  virtual void PaintButton (DWORD Style, int Index);
  virtual int GetTextWidth (HDC hDC);
  virtual void DrawButtonText (HDC hDC, int Offset);
  };



//----------------------------------------------------------------------------
//  Groupbox
//----------------------------------------------------------------------------
class GroupBox : public StaticTool {
 public:
  GroupBox (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : StaticTool (RefWnd,Data,pData,pSize) { };
  
  tool_groupbox FAR *Param()              
              { return (tool_groupbox FAR *) StructData ; }

  int xb,xe,yb,th;
  int oldy0;
  BOOL firstMove;
  int Style;
  int DrawBkGround;
  DWORD Color;

  fRECT rcPaint;
  virtual DWORD TextRef()
    { return Param()->Text ; }
  virtual DWORD FormatRef ()
    { return Param()->_Format ; }

  virtual void FixConnection ();
  virtual void GetTextPos (HDC hDC,LPPOINT p);
  virtual int GetTextWidth (HDC hDC);

  virtual void Load ();
  virtual void GetRect ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Invalidate (BOOL doErase);
  virtual void Reset (BOOL doClear);

  void MyRectangle (HDC hDC,int x0,int y0,int x1,int y1);
  void MyFillRectangle (HDC hDC,int x0,int y0,int x1,int y1);
  };

//----------------------------------------------------------------------------
//  TextCheckbutton
//----------------------------------------------------------------------------
class TextCheckButton : public CheckButton {
 private:
  int    tw;         // Breite
  int    Format;
  fRECT  TextRect;

 public:
#ifdef CFIELD_INCLUDED
  cField FAR *field;
#else
  LPVOID field;
#endif

  textcheck_button FAR *Param()              
              { return (textcheck_button FAR *) StructData ; }

  TextCheckButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : CheckButton (RefWnd,Data,pData,pSize) { };
  virtual ~TextCheckButton () { } ;
  virtual DWORD FormatRef ()
    { return Param()->_Format ; }

  virtual void Load ();
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  virtual void GetRect ();
  virtual void MoveTool ();
  virtual void PaintFocus (DWORD State);
  virtual void PaintState ();
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void SetObjectColor (COLORREF color);

  void SetTwips (HDC hDC,int x = 0,int y = 0);
  void SetMMText (HDC hDC);
  void RectToDev (LPRECT r);
  virtual int GetTextWidth (HDC hDC);

  DWORD CheckText()
    {
    return Param()->CheckText;
    }
  };

class TextRadioButton : public TextCheckButton {
 public:
  textradio_button FAR *Param()              
              { return (textradio_button FAR *) StructData ; }
  TextRadioButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : TextCheckButton (RefWnd,Data,pData,pSize) { };

  virtual BOOL           On_LButtonUp (LPPOINT pt);
  virtual void  HotKeyAction (BOOL dontCheckEnabled) ;
  virtual DWORD FormatRef ()
    { return Param()->_Format ; }
  };


class ComboButton : public PushButton {
 public: 
  ComboButton (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : PushButton (RefWnd,Data,pData,pSize) { GetRect (); };    // CONSTRUCTOR

  combo_button FAR *Param()              
              { return (combo_button FAR *) StructData ; }
 
  virtual void Load ();
  virtual void GetRect ();
  virtual BOOL HasTabStop();
  virtual void CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh);
  virtual int  Gety0 ()
    { return ToDevKoordY(ty,Parent->Layer) - 3 ; }
  virtual void MoveTool();
  virtual BOOL OnChar (WORD wP);
  virtual void PaintButton (DWORD Style, int Index);
  virtual void PaintFocus (DWORD State) { };
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void On_LButtonDown (LPPOINT pt);
  };


#define  CCOLORS  5

class UpDown : public tool {
 private:
  COLORREF rgbClr[CCOLORS];
//  BOOL     IsEnabled;
  WORD     State;
//  HDC      CapDC;
  BOOL     FirstTimer, SecondTimer;
  
 public: 
  UpDown (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize);

  up_down FAR *Param()              
              { return (up_down FAR *) StructData ; }
 
//  virtual void GetRect ();
//  virtual void CalcOffset (DWORD State, int FAR* bmw, int FAR* bmh);
          void CalcClickedRect (LPRECT rc);
  virtual int  Gety0 ()
                     { return ToDevKoordY(ty,Parent->Layer) - 3 ; }

  virtual void GetRect ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual BOOL OnChar (WORD wP);
  virtual void On_LButtonDown (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual void OnTimer ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  };


#define MAXTEXTSIZE 256
#define TYPE_CHARTEST     0
#define TYPE_CHARSETFNC   1
#define TYPE_MODIFYFNC    2
#define TYPE_COLORFNC     3
struct ExtraCharList {
  WORD Type;
  union {
    struct {
      WORD vKey;
      WORD vModify;       // Vorerst nicht unterstuetzt
      DWORD procOffset;
      } ci;
    struct {
      DWORD SetStrId;
      } csf;
    } vlist;
  ExtraCharList FAR *Next;
  };
typedef ExtraCharList FAR *LPECL;

DLLExport void _export WINAPI SetOnEditChar (DWORD Edit,LPVOID privData,WORD vKey,WORD vModify,DWORD procOffset);
DLLExport void _export WINAPI GetFieldFormat (DWORD Edit,LPVOID privData,DWORD FieldVar);
DLLExport void _export WINAPI GetFieldModify (DWORD Edit,LPVOID privData,DWORD FieldVar);
DLLExport void _export WINAPI SetOnSetFocus (DWORD Edit,LPVOID privData,DWORD procOffset,BOOL bOnKillFocus);

struct tool_palette {
  tool_header hd;
  DWORD SelIndex;
  DWORD w;
  DWORD h;
  DWORD Disabled;
  DWORD Help;
  };
class ToolPalette : public tool {
 public :
  int tx,ty,tw,th;
  int ActColor;
  int dx,dy;

  ToolPalette (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize) 
      { };    // CONSTRUCTOR
  virtual ~ToolPalette ()                 { };    // DESTRUCTOR

  tool_palette FAR *Param()              
              { return (tool_palette FAR *) StructData ; }

  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual BOOL IsToolRectVisible (HDC hDC)      
    { RECT rc; CopyRect (&rc, LPRECT(&ToolRect)); InflateRect (&rc, 3, 2);
      return RectVisible(hDC, &rc); }
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  };

struct bit_merge {
  tool_header hd;
  DWORD bmList;     // Liste mit den Bitmaps
  DWORD cbProc;     // Funktion zum Ermitteln der Bilder
  DWORD w,h;        // Breite / hoehe in Pixel
  };
struct bit_edit {
  bit_merge bm;
  DWORD pict;  // Bitmap
  DWORD SelIndex;  // Farbe (nur im fall von 0)
  DWORD maxX;  // max. Breite in log. Koordinaten
  DWORD maxY;  // max. Hoehe in log. Koordinaten
  DWORD Disabled;
  DWORD Help;
  DWORD typ;       // 0 ... 16 Farben, 1 ... 32 Planes, 2 ... monochrome
  DWORD plane;     // nur im Fall von 32 bits
  };

struct FAR IDList {
  DWORD pict;
  BOOL mVert;
  BOOL mHorz;
  int type;
  DWORD plane;
  int Color;
  IDList FAR *Next;
  BOOL IsDone;
  };
struct FAR RIList {
  RECT r;
  IDList FAR *idl;
  RIList FAR *Next;
  BOOL IsCorrect;
  BOOL TestID (int type,DWORD pictID,BOOL mVert,BOOL mHorz,DWORD plane,int Color);
  void InsertID (int type,DWORD pictID,BOOL mVert,BOOL mHorz,DWORD plane,int Color);
  void PrepareTest ();
  };
class BitMerge : public tool {
 public :
  int tx,ty,gx,gy; // Abmessungen in log. Koordinaten
  BYTE huge *lpGBits;
  int obw;
  int State;
  RIList FAR *l;
  DWORD bmList;
  GLOBALHANDLE hGmem ;

  void AddBitmap (LPRECT r,int type,DWORD plane,BOOL mVert,BOOL mHorz,int Color,BYTE FAR *bData);
  void AB_16L (LPRECT r,BYTE FAR * source,BOOL mVert);
  void AB_16R (LPRECT r,BYTE FAR * source,BOOL mVert);
  void AB_32L (LPRECT r,DWORD plane,DWORD FAR * source,BOOL mVert,int Color);
  void AB_32R (LPRECT r,DWORD plane,DWORD FAR * source,BOOL mVert,int Color);
  void AB_1L (LPRECT r,BYTE FAR * bsource,BOOL mVert,int Color);
  void AB_1R (LPRECT r,BYTE FAR * bsource,BOOL mVert,int Color);
  void EmptyRect (LPRECT r);

  void Invalidate (LPRECT r);
  RIList FAR *InsertRIList (LPRECT r);
  RIList FAR *GetRIList (LPRECT r);
  void PrepareTest ();
  void LoadBitmap ();
  void CleanLists ();
  #ifdef STRKEY
  hash *riHash ;
  #else
  LPVOID riHash ;
  #endif

  bit_merge FAR *Param()
    { return (bit_merge FAR *) StructData ; }

  BitMerge (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : tool (RefWnd,Data,pData,pSize) 
      { };    // CONSTRUCTOR

  void DeleteRIList ();

  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void GetRect ();
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  virtual void Update ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  };

#define BMODE_SETFOCUS    0
#define BMODE_SETPOINT    1
#define BMODE_SETLINE     2
#define BMODE_SETRECT     3
#define BMODE_FILL        4
#define BMODE_TOGGLEGRID  100
class BitEdit : public BitMerge {
 public :
  int type;        // Aktueller Typ
  int ActColor;    // Aktuelle Farbe
  DWORD plane;     // Aktuelle Plane
  int dx;          // Abmessungen eines Pixels
  int px,py;       // Pixelanzahls..
  int x,y;         // Aktuelle Mouseposition
  int x1,y1;       // 2. Position fuer Linie, Rechteck ...
  int pbw;
  int EditMode;
  LPBYTE lpNwBits;  // Pixel des Bitmaps
  BOOL drawGrid;

  BitEdit (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : BitMerge (RefWnd,Data,pData,pSize) 
      { };    // CONSTRUCTOR
  virtual ~BitEdit () { } ;

  bit_edit FAR *Param()              
              { return (bit_edit FAR *) StructData ; }

  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual BOOL IsToolRectVisible (HDC hDC)      
    { RECT rc; CopyRect (&rc, LPRECT(&ToolRect)); InflateRect (&rc, 3, 2);
      return RectVisible(hDC, &rc); }
  virtual BOOL  HasTabStop()                     
    { return IsEnabled ; }
  virtual void Load ();
  virtual void Update ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  void InvalidateAct ();
  void InvalidateAct (int x,int y);
  LPSTR FP ;
  void FillPixel (int x,int y,int color);
  void MarkPixelSet (int x,int y);
  BOOL IsPixelSet (int x,int y);
  virtual BOOL OnChar (WORD wP);
  inline int GetNewColor (int i,int j);
  inline int GetOldColor (int i,int j);
  inline int GetMixColor (int i,int j);
  void SetBits (GLOBALHANDLE hDib);
  inline void SetBit (int i,int j,int Color);
  inline void SetBit (int i,int j);
  inline int ClipX (int x);
  inline int ClipY (int y);
  void SetBitI (int i,int j);
  void PaintLine ();
  void PaintRect ();
  void SetLine ();
  void SetRectangle ();
  void InsertFromClipboard ();
  virtual void On_LButtonDown (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  };

class FAR TextPosten;
struct text_merge {
  tool_header hd;
  DWORD bmList;     // Liste mit den Texten
  DWORD cbProc;     // Funktion zum Ermitteln der Bilder
  };

class TextMerge : public tool {
 private :
  TextPosten FAR *tp;
  void BuildTextPosten ();
 public :
  int x0,y0;
  TextPosten FAR *GetTextPosten (int x,int y);
  TextMerge (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
      : tool (RefWnd,Data,pData,pSize)
      { };
  virtual ~TextMerge () { };

  text_merge FAR *Param()
              { return (text_merge FAR *) StructData ; }

  virtual void FixConnection ();
  virtual void GetRect ();
  virtual void Invalidate (BOOL doErase);
  virtual BOOL IsToolRectVisible (HDC hDC)      
    { RECT rc; CopyRect (&rc, LPRECT(&ToolRect)); InflateRect (&rc, 3, 2);
      return RectVisible(hDC, &rc); }
  virtual void Load ();
  virtual void MoveTool ();
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void Update ();
  };

class ComboButton;
class ToolEdit : public tool {
 public :
  int    CtlId;
  LPECL  ecl;
  HWND   hWndEdit;
  BOOL   cmbIsEnabled;
  DWORD  ComboProc;     // wenn es ein Combo-Element gibt
  DWORD  UpProc;        // Prozeduren fuer Up-Down-Control!
  DWORD  DownProc;
  WORD   Mode;

  int    tw;      // Breite
  int    Format;
  int    AnzLines;

  BOOL   skipNextChar;

  DWORD  CallOnSetFocus;
  DWORD  CallOnKillFocus;

  ToolEdit (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize)
      : tool (RefWnd,Data,pData,pSize)
      { ComboProc = NULL; 
        UpProc = NULL; 
        DownProc = NULL; 
        Mode = 0; 
        CallOnSetFocus = 0;
        CallOnKillFocus = 0; 
        skipNextChar = FALSE;
      };    // CONSTRUCTOR
  virtual ~ToolEdit ()                 { };    // DESTRUCTOR

  tool_edit FAR *Param()
              { return (tool_edit FAR *) StructData ; }

  virtual void ChangeParent (HWND hWnd)       { SetParent (hWndEdit,hWnd); }
  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual LPSTR GetText ();
  virtual BOOL HasTabStop ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void HotKeyAction (BOOL dontCheckEnabled);
  virtual WORD Id()                           { return CtlId ; }
  virtual void Invalidate (BOOL doErase);
  virtual BOOL IsToolRectVisible (HDC hDC)      
    { RECT rc; CopyRect (&rc, LPRECT(&ToolRect)); InflateRect (&rc, 3, 2);
      return RectVisible(hDC, &rc); }
  virtual void Load ();
  virtual void MoveTool ();
  virtual void OnActivate (BOOL ActivateFlag);
  virtual void OnChange ();
  virtual void OnSetFocus ();
  virtual void OnKillFocus ();
  virtual BOOL IsCharCallbackInstalled (WORD wP);
  virtual BOOL OnChar (WORD wP);
  virtual BOOL OnCommand (HWND hWnd, WPARAM wP);
  virtual void OnRButtonDown (HMENU hPopupMenu);
  virtual void OnParentNotify (WPARAM wParam);
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
          void SetComboProc (DWORD Proc,BOOL Enabled,ComboButton FAR *cmb);
          void SetUpDownProc (DWORD UpProc, DWORD DownProc);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  virtual void Update ();
  virtual void OnWorkOn ();
  virtual int  GetMaxAnzChars ();

  virtual void SetObjectColor (COLORREF color);

  DLLExport void _export WINAPI SetCaretToEnd ();
  DLLExport void _export WINAPI SetMaxSize (int size);

  void OnCaretPosChanged();

  DLLExport void _export WINAPI SetOverwrite ();
  DLLExport void _export WINAPI SetFieldModify (int Modify,BOOL Set_Clear);
  DLLExport void _export WINAPI SetModifyParam (DWORD idModify);
  DLLExport void _export WINAPI SetColorParam (DWORD idColor);

  ComboButton FAR *cmb;
  };

class ToolBEdit : public ToolEdit {
 public :
  ToolBEdit (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual void Load ();
  };

class ToolPwd : public ToolEdit {
 public :
  ToolPwd (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual void Load ();
  };

class ToolDate : public ToolEdit {
 public :
  virtual void Load ();
  virtual void OnChange ();
  virtual LPSTR GetText ();
  ToolDate (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual void OnWorkOn ();
  virtual int GetMaxAnzChars () { return -1 ; }
  virtual void OnRButtonDown (HMENU hPopupMenu);
  virtual BOOL  IsCharCallbackInstalled (WORD wP);
  virtual BOOL  OnCommand (HWND hWnd, WPARAM wP);
  };

class ToolTime : public ToolEdit {
 protected :
  LPSTR   szTimeFormat;
 public :
  virtual void Load ();
  virtual void OnChange ();
  virtual LPSTR GetText ();
  ToolTime (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { szTimeFormat = NULL; };    // CONSTRUCTOR
  virtual ~ToolTime ();
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);

  virtual void OnWorkOn ();
  virtual int GetMaxAnzChars () { return -1 ; }
  virtual void OnRButtonDown (HMENU hPopupMenu);
  virtual BOOL  IsCharCallbackInstalled (WORD wP);
  virtual BOOL  OnCommand (HWND hWnd, WPARAM wP);
  };


class ToolFloat : public ToolEdit {
 public :
  virtual void Load ();
  virtual void OnChange ();
  virtual LPSTR GetText ();
  tool_float FAR *fPar() { return (tool_float FAR *) StructData ; }
  LPSTR GetFormat ();
  ToolFloat (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual int GetMaxAnzChars () { return -1 ; }
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  };

class ToolShortInt : public ToolEdit {
 public :
  virtual void Load ();
  virtual void OnChange ();
  virtual LPSTR GetText ();
  ToolShortInt (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolEdit (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual int GetMaxAnzChars () { return -1 ; }
  };

class ToolLongInt : public ToolShortInt {
 public :
  virtual void OnChange ();
  virtual LPSTR GetText ();
  ToolLongInt (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolShortInt (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  };

class ToolMoney : public ToolShortInt {
 public :
  virtual void OnChange ();
  virtual LPSTR GetText ();
  tool_float FAR *fPar() { return (tool_float FAR *) StructData ; }
  BOOL doMoney();
  ToolMoney (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize) 
      : ToolShortInt (RefWnd,Data,pData,pSize) { };    // CONSTRUCTOR
  virtual void FixConnection ();
  virtual void Reset (BOOL doClear);
  };

class ZoomTool : public tool {
 private:
  fRECT   OldRect;
  fRECT   rcArrow;
  BOOL    Inside;
  int     tw, th;
  
  float   StartRange, EndRange;
  int     Sections, Type;

 public:
//  HDC           CapDC;
  BOOL          Capturing;
  ToolEdit FAR *EdTool;

  ZoomTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize); 
   
  zoom_tool FAR *Param()              
              { return (zoom_tool FAR *) StructData ; }

  virtual void On_LButtonDown (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual BOOL HasTabStop ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual BOOL OnChar (WORD wP);
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  int          Retransform (double);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  void         Transform (int,float FAR *);

  };


class PageTool : public tool {
 private:
  int     ActivePage;
  int     AnzPages;
  int     PagesToShow;
  int     tw, th;
  fRECT   LButton, RButton;
  BOOL    LPressed, RPressed;
  fPOINT  PageSize;
  fRECT   ScrollRect;
  HFONT   SmallFont;
  int     StartPage, EndPage;
  
 public:
//  HDC     CapDC;
  BOOL    Capturing;


  PageTool (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize); 
  virtual ~PageTool ()  { if (SmallFont) DeleteObject (SmallFont); }
   
  page_tool FAR *Param()              
              { return (page_tool FAR *) StructData ; }

  virtual void On_LButtonDown (LPPOINT pt);
          void CalcPageRect (RECT FAR* rc, int i);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual BOOL HasTabStop ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual BOOL OnChar (WORD wP);
  void         PaintPage (int Num, LPRECT lprcPage, BOOL Selected);
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  };


class FAR PosControl : public wtobj {
 private:
  HBITMAP bitmap, BackGround;
  int     bmX, bmY;              // aktuelle Position des Bitmaps
  int     bmWidth, bmHeight;     // Breite, Hoehe des Bitmaps
  int     xOld, yOld;            // Mauskoordinaten
  int     xOffs,yOffs;
  fRECT   rcParent;
 
 public:
  PosControl (LPRECT rc, int x, int y, HBITMAP hBmp, 
              int width, int height);
  ~PosControl (void);

  void Update (LPRECT rc, int x, int y, HBITMAP hbmp, 
               int width, int height);
  void MoveTool (short dy);
  void Paint (HDC hDC);
  BOOL HitTest (POINT pt);
  void OnLButtonDown (LPPOINT pt);
  void OnMouseMove (HWND hWnd, LPPOINT pt);
  void OnLButtonUp (LPPOINT pt);

  int GetBMWidth()
    { return bmWidth ; }
  int GetBMHeight()
    { return bmHeight ; }
  };
typedef PosControl FAR* LPPOSCTRL;


class XYFromRect : public tool {
 private:
  LPPOSCTRL PosCtrl;
  
 public:
//  HDC       CapDC;
  BOOL      Capturing;
  fRECT     rcInside;
  int       tw, th;
  BMPREF    BmpRef;
  float     XStartRange,YStartRange;
  float     XEndRange,YEndRange;

  XYFromRect (HWND RefWnd,LPVOID Data,LPVOID pData,int pSize); 
  virtual ~XYFromRect (void);
   
  tool_xyfromrect FAR *Param()              
              { return (tool_xyfromrect FAR *) StructData ; }
  virtual BitMapRef FAR *BitRef ()
    { return &(((tool_xyfromrect FAR *) StructData)->btn); }
  virtual int GetAnzButtons ()
    { return 1 ; }

  virtual void On_LButtonDown (LPPOINT pt);
  virtual void On_MouseMove (LPPOINT pt);
  virtual BOOL On_LButtonUp (LPPOINT pt);
  virtual void FixConnection ();
  virtual LPSTR GetHelpText ();
  virtual void GetRect ();
  virtual BOOL HasTabStop ();
  virtual BOOL HitTest (LPPOINT pt);
  virtual void Invalidate (BOOL doErase);
  virtual void Load ();
  virtual void MoveTool ();
  virtual BOOL OnChar (WORD wP);
  virtual void PaintTool (HDC hDC, HDC hmemDC);
  virtual void Reset (BOOL doClear);
  int          RetransformX (double,int bmWidth);
  int          RetransformY (double,int bmHeight);
  virtual void SetToolFocus (BOOL state, BOOL select = TRUE, int mode = FOCUSMODE_NONE);
  void         TransformX (int,float FAR *);
  void         TransformY (int,float FAR *);
  };



/*------------------------------------------------------------------*\
*  Von Toolbar zur verfuegung gestellte Funktionen                   *
\*------------------------------------------------------------------*/
typedef LPVOID (WINAPI * GETDATA) (LPVOID PrivData,DWORD Id);
typedef VOID (WINAPI * SETDATA) (LPVOID PrivData,DWORD Id,LPVOID data,int DataSize,LPVOID StructOfs);
typedef VOID (WINAPI * SETCONNECTION) (LPVOID PrivData,DWORD Id,LPVOID StructOfs);
typedef VOID (WINAPI * SETCONNECTION_EXTENDED) (LPVOID PrivData,DWORD Id,LPVOID Cmd,WORD TableInd,LPVOID RecData);
typedef LPVOID (WINAPI * SETTABLECONTEXT) (LPVOID CallBackData,WORD TableInd,LPVOID recAddr);
typedef LPVOID (WINAPI * GETTABLECONTEXT) (LPVOID CallBackData,WORD TableInd);
typedef VOID (WINAPI * CLEARCONNECTION) (LPVOID PrivData,DWORD Id,LPVOID StructOfs);
typedef VOID (WINAPI * CALLCOMMAND) (LPVOID PrivData,DWORD CmdOffs,LPVOID par);
typedef BOOL (WINAPI * ISUPDATEFROM) (LPVOID PrivData,DWORD Id);
typedef GLOBALHANDLE (WINAPI *GETRESOURCE) (DWORD BtnId);
typedef int (WINAPI *GETVARSIZE) (LPVOID PrivData,DWORD Id);
typedef VOID (WINAPI *FREEPRIVDATA) (LPVOID PrivData);
typedef LPVOID (WINAPI *NEXTBITMAP) (LPVOID PrivData,DWORD lID,DWORD proc,LPVOID oldRec);
typedef VOID (WINAPI *TBFOCUSCHANGING) (DWORD o,DWORD n);
typedef BOOL (WINAPI *TBACTIVE) (BOOL f);
#define EDC_LBUTTONDOWN     0
#define EDC_LBUTTONUP       1
#define EDC_LBUTTONDBLCLK   2
#define EDC_MOUSEMOVE       3
#define EDC_SETCURSOR       4
#define EDC_PAINT           5
#define EDC_HLINEPAINT      6
#define EDC_CHECKMSG        7
#define EDC_CHAR            8
#define EDC_PAINTRASTER     9
union edcmem {
  HDC   hDC;
  POINT pt;
  struct {
    HWND hWnd;
    unsigned msg;
    WORD wP;
    LONG lP;
    LONG RetVal;
    } cm;
  char ch;
  };
typedef edcmem FAR *LPEDCMEM;
typedef int (WINAPI * EDITCALLBACK) (LPVOID PrivData,HWND hScWnd,WORD Command,LPEDCMEM m);


DLLExport void _export WINAPI SetEditCallBack (EDITCALLBACK edc);
DLLExport BOOL _export WINAPI Initialize (GETDATA g,
                                    SETDATA s,
                                    SETCONNECTION sc,
                                    CLEARCONNECTION cc,
                                    CALLCOMMAND cmd,
                                    GETRESOURCE gs,
                                    GETEXTFUNC GetExtFnc,
                                    ISUPDATEFROM IsUpdateFrom);
DLLExport BOOL _export WINAPI Initialize_Extended (SETCONNECTION_EXTENDED SetConnection_Extended,
                                             SETTABLECONTEXT SetTableContext,
                                             GETTABLECONTEXT GetTableContext,
                                             GETVARSIZE GetVarSize,
                                             FREEPRIVDATA fd,
                                             NEXTBITMAP NextBitmap,
                                             NEXTBITMAP NextMerge,
                                             TBFOCUSCHANGING FocusChanginig,
                                             TBACTIVE act);
DLLExport void _export WINAPI SetFrameWnd (HWND hWnd);
DLLExport void _export WINAPI ActivateControl (HWND RefWnd);
DLLExport void _export WINAPI DeactivateControl (HWND RefWnd);
DLLExport void _export WINAPI SetControl (HWND RefWnd,LPTOOLHEADER Data,WORD mode,LPVOID privData,int pdSize);
DLLExport void _export WINAPI GetBaseUnit (double FAR *unit);
DLLExport void _export WINAPI GetResolutionCF (double FAR *ratio);
DLLExport void _export WINAPI DefBitmapObject (LPVOID param,WORD mode,LPVOID privData,int pdSize);


/*------------------------------------------------------------------*\
*  Deklaration der Klasse, die f�r das Anzeigen der aktuellen Layer  *
*  in der Toolbar verantwortlich ist.                                *
\*------------------------------------------------------------------*/
#define MAXSHOWNLAYERS  20


typedef struct FAR WINDOWPOSSTRUCT
  {
#pragma pack(1)
  struct _shortPoint {
    DBINT x ;
    DBINT y ;
    } ptPos;
#pragma pack()
  } POPUPPOS;     // Achtung, das ding wird in die DB geschrieben !


typedef struct FAR WINDOWATTRSTRUCT
  {
  LPSTR Title;
  int   w, h;
  LONG  Style;
  } WINDOWATTR;

typedef WINDOWATTRSTRUCT FAR* LPWINDOWATTR;
  

struct TimerInfo {
  WORD Id;
  tool FAR *h;
  TimerInfo FAR *Next;
  };

class ScreenList : public wtobj {
 public :
  LPWNDLIST       ActiveList [MAXSHOWNLAYERS];
  int             AnzActive;
  WINDOWATTR      Attr;
  HWND            disabledWindow;
  HWND            modalParent;
  HWND            hWnd;
  BOOL            IstMappe;
  BOOL            destroyIsDone;
  WndList FAR     *FirstWnd;
  ScreenList FAR  *Next;
  ScreenList FAR  *ChildScreen;  // eine Mappe im Fenster!
  ScreenList FAR  *ParentScreen;  // wenn der Screen eine Mappe ist!
  DWORD           PosRef;
  LPVOID          privData;
  DWORD           ScreenId;
  int             ScreenNmbr;
  tool FAR        *ToolWithFocus;
  POPUPPOS        WindowPos;
  int             DesiredClientSize;  // Groesse des Clients <= Attr
  BOOL            IsActivated;        // ActivateScreen schon durchgefuehrt
  DWORD           LeftDownProc;       // Prozedur fuer linke Maustaste
  DWORD           RightDownProc;      // Prozedur fuer rechte Maustaste
  DWORD           DownPos;            // Position beim Druecken der Maus
  LPVOID          mouseprivData;
  LPVOID          mouseprocPar;
  void            MouseDownProc (LPPOINT pt, UINT msg);

  BOOL nonmodal;
  BOOL doNCPaint;
  int dlgWidth,dlgHeight;

#ifdef TOOLTIP
  HWND            hWndToolTip;
  HHOOK           g_hhk;
#endif

  WndList FAR *NextWnd (WndList FAR *w);
  WndList FAR *PrevWnd (WndList FAR *w);
  ScreenList (int ScreenNmbr,LPVOID privData,int pdSize);
  LONG MyDefWindowProc (HWND hWnd, unsigned msg, WPARAM wP, LPARAM lP);
  ~ScreenList ();

  HWND hWndToolbar () 
    {
    return hWnd;
    }
  void          ChangeParent ();
  void          DisableParent (HWND hWnd);
  void          EnableParent ();
  WndList FAR * GetWnd(HWND hWnd,int Layer);
  tool    FAR * HitTest (LPPOINT lP);
  void          Insert (LPWNDLIST wnd);
  int           LayerStart (int Layer) ;
  void          MoveBackward (int start);
  void          MoveForward (int start);
  void          Paint (HDC hDC,HDC hmemDC);
  void          Remove (HWND RefWnd);
  void          RemoveWindowWithLayer (int Layer);
  tool    FAR * Search (WORD Id);
  void          TabToNextElement ();
  void          OnQueryNewPalette (UINT msg);
  void          OnMouseMove (WPARAM wP,LPARAM lP);
  void          OnKillFocus (WPARAM wP);

  TimerInfo FAR *firsttimer;
  HPALETTE hPal;
  int PalUseCount;
  void IncPalUseCount()
    { PalUseCount ++ ; }
  void DecPalUseCount()
    { PalUseCount -- ; }
  void SetPalette (HPALETTE hP);
  void InsertToTimerList (tool FAR *h, UINT interval, WORD Nr);
  void RemoveFromTimerList (tool FAR *h);

  void RelayMouseMessageToToolTip (HWND hWnd, UINT message,
                                   WPARAM wP, LPARAM lP);
#ifdef TOOLTIP
  DLLExport LRESULT _export CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
#endif

  virtual BOOL WritePosRef ()
    { return TRUE ; }
  };

class FAR MapScreenList : public ScreenList {
 public :
  MapScreenList (int ScreenNmbr,LPVOID privData,int pdSize) :
    ScreenList (ScreenNmbr,privData,pdSize) { }
  
  virtual BOOL WritePosRef ()
    { return FALSE ; }
  };

typedef ScreenList FAR *LPSCREEN;
DLLExport void _export WINAPI SetMouseDownProc (LPSCREEN sc,
                                                DWORD LeftDownProc,
                                                DWORD RightDownProc,
                                                DWORD DownPos,
                                                LPVOID mouseprocPar,
                                                LPVOID mouseprivData,
                                                int mouseprivDataSize);

/*------------------------------------------------------------------*\
*                                                                    *
*                 Deklarationen f�r die HotKeys                      *
*                                                                    *
\*------------------------------------------------------------------*/
typedef HotKeyData FAR* LPHOTKEYS;


class FAR HotKey : public wtobj {
 public:
  HotKey FAR* Next;        // Zeiger auf den n�chsten HotKey
  BOOL doModify;           // Aenderungen erlaubt
  HotKeyData  KeyData;
  ActionElem FAR*   hkTool;

  HotKey (HotKeyData keydata, BOOL allowModify, ActionElem FAR *action); // In Liste einhaengen
  virtual ~HotKey ();           // Aus Liste entferne

  void ModifyHotKey (HotKeyData kd);

  friend int operator==(HotKey FAR &hk1, HotKey FAR &hk2);
  };

void RemoveHotKey (ActionElem FAR *t);
HotKey FAR *GetHotKey (ActionElem FAR *);


// Deklarationen fuer DrawEdge
#define MY_BF_ADJUST        0
#define MY_BF_MIDDLE        1
#define MY_BF_RECT          2
#define MY_EDGE_HWND        0
#define MY_EDGE_GROUPBOX3D  1
#define MY_EDGE_GROUPBOX    2
#define MY_EDGE_BUTTONUP    3
#define MY_EDGE_BUTTONDOWN  4

DLLExport void _export WINAPI MyDrawEdge (HDC hDC, LPRECT lprc, UINT EdgeType, UINT Flags);


DLLExport HWND _export WINAPI CreateToolBar (DWORD ScreenId,HWND Parent,int ScreenNmbr,DWORD PosRef,
                                       LPWINDOWATTR Attr, LPVOID privData,int pdSize,int x,int y,
                                       BOOL ModalScreen,BOOL mapScreen,
                                       LPVOID par
                                      );
DLLExport void _export WINAPI DestroyToolBar (ScreenList FAR *sc);
DLLExport HWND _export WINAPI CreateBubbleWindow (int X, int Y, LPSTR str, 
                                                  HWND Parent, BOOL ToolTip = FALSE);
DLLExport void _export WINAPI SetToolTipFont (int FontNum);
DLLExport BOOL _export WINAPI IsMainPopup ();
DLLExport int  _export WINAPI ToolBarWidth ();
DLLExport BOOL _export WINAPI IsMainExistant ();

DLLExport void _export WINAPI ToolBarCleanUp ();
DLLExport LONG _export WINAPI BubbleWinFunc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DLLExport BOOL _export WINAPI HotKeyDlgProc (HWND hDlg, unsigned msg,
                                       WPARAM wP, LPARAM lP);
DLLExport BOOL _export WINAPI IsHotKey (LPMSG lpmsg);
DLLExport void _export WINAPI ActivateWholeScreen (LPSCREEN screen);
DLLExport void _export WINAPI InitHotKey (LPVOID privData, HotKeyStruct FAR* hkParam, WORD mode);

DLLExport void _export WINAPI RemoveAllHotKeys ();
DLLExport void _export WINAPI InitializeAllHotKeys ();

DLLExport void _export WINAPI ActivateMainToolBar (BOOL State);
DLLExport void _export WINAPI DrawTransparentBitmap(HDC hdc, LPBITMAPINFO bi, LPSTR lpbits, int XPos, int YPos, 
                                              COLORREF cTransparentColor);
DLLExport void _export WINAPI DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, int XPos, int YPos, 
                           int xStart, int yStart, int Width, int Height, COLORREF cTransparentColor);


DLLExport void _export WINAPI RemoveScreenControlFromLayer (LPSCREEN sc, int Layer);
DLLExport void _export WINAPI ActivateLayerInScreen (LPSCREEN sc, int Layer);
DLLExport void _export WINAPI SetFocusOnTool (DWORD Tool, LPVOID  privData, BOOL State);
DLLExport void _export WINAPI ChangeToolbarSize (LPSCREEN sc, int w, int h);
DLLExport void _export WINAPI ChangeToolbarPos (LPSCREEN sc, int x, int y);
DLLExport void _export WINAPI SetToolbarTitle (LPSCREEN sc, LPSTR str);


DLLExport HBITMAP _export WINAPI GetBitmap (DWORD Id,int FAR &AnzRows,int FAR &AnzCols);
DLLExport HBITMAP _export WINAPI GetBitmap (DWORD Id,int FAR &AnzRows,int FAR &AnzCols, 
                                             HPALETTE FAR &Palette);
DLLExport void _export WINAPI ResetAllBitSelections (ScreenList FAR *sc,BitSelect FAR *active);

DLLExport void _export WINAPI GetToolCoordinates (DWORD Tool, LPVOID  privData, 
                                                  int FAR *x, int FAR *y,
                                                  int FAR *w, int FAR *h,
                                                  BOOL absolute);


struct FAR DIBList {
  DIBList FAR *Next;
  DWORD Id;
  int AnzRows;
  int AnzCols;
  HBITMAP bmp;
  HPALETTE hPal;
  GLOBALHANDLE hGBits;
  LPBITMAPINFOHEADER lpbi;
  HBITMAP hMask;
  HBITMAP hBorder;
  LPSTR lpbits;
  int w,h,bw;
  int FAR *xp0,FAR *xp1,FAR *yp0,FAR *yp1;  // Extremwerte der Teilbitmaps
  int BitCount;

  void GetXVals(int forMono);
  BOOL Initialize (BOOL bWithPal);
  BOOL GetStruct ();
  void GetMask(COLORREF TransparentColor);
  void GetBorder ();
  };

DIBList FAR *GetBitmapInfo (DWORD Id,int FAR &AnzRows,int FAR &AnzCols,
                                             HPALETTE FAR &Palette);

void CleanBitmapList ();

struct FAR MoveElem_param {
  WORD parSize;
  LONG xSpace;
  LONG ySpace;
  DWORD elem[1];
  int AnzElems()
    { return (parSize - (sizeof(*this) - sizeof(elem[0]))) / sizeof(elem[0]) ; }
  };
typedef MoveElem_param FAR *LPMOVEELEMPAR;

struct FAR ExtToolDimension_param {
  WORD  parSize;
  DWORD exttool;
  LONG  x,y;
  };

typedef ExtToolDimension_param FAR *LPEXTTOOLDIM ;
DLLExport void _export WINAPI MoveElems (LPMOVEELEMPAR par,LPVOID privData);
DLLExport void _export WINAPI SetExtToolDimension (LPEXTTOOLDIM par,LPVOID privData);

extern DLLExport void _export WINAPI win_ass_failed (int modnum, int line);
extern DLLExport void _export WINAPI CTOOL_SetClassNames (LPSTR ListClassName,LPSTR ClassName,LPSTR WWName,LPSTR BubbleName,LPSTR FolderClass);
extern DLLExport void _export WINAPI CTOOL_SetBitSelectMode (BitSelect FAR *bs,BOOL select);
extern DLLExport void _export WINAPI CTOOL_InstallSelectMode (DWORD Id);
extern DLLExport HWND _export WINAPI CTOOL_GetActiveTopWindow ();
extern DLLExport HPALETTE _export WINAPI CTOOL_GetActivePalette ();
extern DLLExport void _export WINAPI CTOOL_SetActivePalette (HPALETTE hNewPal);
extern DLLExport void _export WINAPI SetToolPalette (LPVOID privData,LPVOID param,WORD mode);
DLLExport void _export WINAPI SetBitEditMode (LPVOID privData,LPVOID param,WORD mode);
DLLExport void _export WINAPI AddBitmap (LPRECT r,int type,
      DWORD plane,DWORD pictID,BOOL mVert,BOOL mHorz,int Color,BYTE FAR *bData);
DLLExport void _export WINAPI AddMergeText (int dx,int dy,int w,int AnzahlGesamt,LPSTR txt,int color,int Format,BOOL wichtig,BOOL wichtigOben);
DLLExport WORD _export WINAPI GetLastPressedChar ();
DLLExport void _export WINAPI AppendContextMenu (DWORD Tool, LPVOID menuprocpar,
                                                 LPVOID menuprivData, int menuprivdatasize,
                                                 LPSTR MenuText, DWORD MenuProc, 
                                                 UINT Flags, WORD mode);
DLLExport void _export WINAPI RemoveContextMenu (DWORD Tool, LPVOID privData);
DLLExport tool FAR * _export WINAPI CTOOL_GetActMouseObject ();
DLLExport void _export EnableToolTips (BOOL bEnable);
DLLExport void _export WINAPI HandlePopupMenu (HWND hWnd, POINT pt, tool FAR *HelpCapt,LPMENULIST l);

#ifndef NODLL

static int CtlIdent = 30000;

#ifdef TOOLBAR_MAIN
  HFONT  HelvFont;
  HBRUSH  DnBrush;

  HBITMAP MultiOn, MultiOff;   // Bitmaps fuer Multiselektionslisten

  LPSCREEN MainScreen;
  HWND hFrameWnd;

  HINSTANCE hLibInst;
  LPSTR szBubbleClassName;
  tool FAR *Capture ;

  HotKey FAR* FirstHotKey = NULL;
  HotKey FAR* ActHotkey;
  ScreenList FAR *FirstScreen;

  WORD WindowsVersion;

  GETDATA GetData;
  SETDATA SetData;
  SETCONNECTION SetConnection;
  CLEARCONNECTION ClearConnection;
  SETCONNECTION_EXTENDED SetConnection_Extended;
  SETTABLECONTEXT SetTableContext;
  GETTABLECONTEXT GetTableContext;
  CALLCOMMAND CallCommand;
  GETRESOURCE GetResource;
  GETEXTFUNC  GetExtFnc;
  ISUPDATEFROM IsUpdateFrom;
  NEXTBITMAP NextBitMap;
  NEXTBITMAP NextTextForMerge;
  EDITCALLBACK EditCallBack;
  GETVARSIZE GetVarSize;
  FREEPRIVDATA FreePrivData;
  TBACTIVE tbActive;
  int NextFreeTimerId = 1;
#else
  extern tool FAR *Capture ;
  extern HFONT  HelvFont;
  extern HBRUSH  DnBrush;

  extern HBITMAP MultiOn, MultiOff;   // Bitmaps fuer Multiselektionslisten

  extern LPSCREEN MainScreen;
  extern HWND hFrameWnd;

  extern HINSTANCE hLibInst;
  extern LPSTR szBubbleClassName;

  extern HotKey FAR* FirstHotKey;
  extern HotKey FAR* ActHotkey;
  extern ScreenList FAR *FirstScreen;

  extern WORD WindowsVersion;

  extern GETDATA GetData;
  extern SETDATA SetData;
  extern SETCONNECTION SetConnection;
  extern SETCONNECTION_EXTENDED SetConnection_Extended;
  extern SETTABLECONTEXT SetTableContext;
  extern GETTABLECONTEXT GetTableContext;
  extern CLEARCONNECTION ClearConnection;
  extern CALLCOMMAND CallCommand;
  extern GETRESOURCE GetResource;
  extern GETEXTFUNC  GetExtFnc;
  extern ISUPDATEFROM IsUpdateFrom;
  extern NEXTBITMAP NextBitMap;
  extern NEXTBITMAP NextTextForMerge;
  extern EDITCALLBACK EditCallBack;
  extern GETVARSIZE GetVarSize;
  extern FREEPRIVDATA FreePrivData;
  extern TBACTIVE tbActive;
  extern int NextFreeTimerId;
#endif

#endif
