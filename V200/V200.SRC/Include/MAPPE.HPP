/////////////////////////////////////////////////////////
//   $Header:   P:/marille/clinicum/include/rev/mappe.hpv   1.24   20 Feb 1998 12:35:04   Hannes  $
//   $Log:   P:/marille/clinicum/include/rev/mappe.hpv  $
// 
//    Rev 1.24   20 Feb 1998 12:35:04   Hannes
// Disable negativ: Hand, Disable Positiv: Grauer Text
// 
//    Rev 1.23   22 Apr 1997 12:08:14   Hannes
// Font,Hoehe und Offset in die Sturktur
// 
//    Rev 1.22   08 Apr 1997 17:45:46   gerhold
// SetMapFont, SetFlapHeight, SetMapOffset
// 
//    Rev 1.21   07 Apr 1997 19:21:58   gerhold
// Variable m_FlapFont
// 
//    Rev 1.20   25 Feb 1997 12:11:46   Gerhold
// Hilfetexte und Bilder in den Ohrwascheln.
// 
//    Rev 1.19   12 Nov 1996 14:40:24   GERHOLD
// in der ClientMap neuen Member m_ChildMap. Gibt an, ob die Mappe als Parent
// einen Screen hat und zeichnet die Mappe dann im WIN32 Stil.
// 
//    Rev 1.18   02 Feb 1996 10:59:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.17   15 Nov 1995 17:36:22   GERHOLD
// SetMapExtent ... Position und Groesse der Mappe aendern
// 
//    Rev 1.16   14 Aug 1995 12:20:08   HANNES
// Hotkeys
// 
//    Rev 1.15   20 May 1995 16:20:02   HANNES
// FirstFlapSet
// 
//    Rev 1.14   12 Apr 1995 12:29:38   HANNES
// 
//    Rev 1.13   06 Feb 1995 16:51:58   HANNES
// 
//    Rev 1.12   28 Nov 1994 20:05:08   GERHOLD
// IsMapHotKey
// 
//    Rev 1.11   28 Oct 1994 10:44:10   GERHOLD
// 
//    Rev 1.10   29 Aug 1994 12:46:18   GERHOLD
// #defines ein bisserl verkleinert (fuer Aufloesungsunabh.)
// 
//    Rev 1.9   25 Aug 1994 14:02:50   HANNES
// 
//    Rev 1.8   17 Aug 1994 09:37:46   HANNES
// Groessenangaben
// 
//    Rev 1.7   05 Aug 1994 17:09:08   GERHOLD
// Farb Parameter in Mappe eingefuegt
// 
//    Rev 1.6   17 Jul 1994 14:42:46   HANNES
// Zwischenversion
// 
//    Rev 1.5   13 Jul 1994 21:17:40   HANNES
// Zwischenversion
// 
//    Rev 1.4   12 Jul 1994 14:47:38   GERHOLD
// Connectionhandling
// 
//    Rev 1.3   08 Jul 1994 12:57:46   GERHOLD
// Disabled als Parameter in CreateMap hinzugefuegt
// 
//    Rev 1.2   05 Jul 1994 15:49:32   GERHOLD
// Initial Code
/////////////////////////////////////////////////////////
#define LEFT_SPACE       4   
#define TOP_SPACE        2
#define RIGHT_SPACE      4
#define BOTTOM_SPACE     2

#define MAX_FLAPS         7
#define FLAP_HEIGHT      12
#define MAP_BORDER       4    // Abstand von der Mappenfläche zum Mappenfenster ("CreateWindow")
#define FLAP_INCREASE     0   // wieviele Pixel ist das nächste Mappenblatt verschoben?
#define FLAP_NEXTROW     10

typedef VOID (WINAPI * MAPCALLCOMMAND) (LPVOID PrivData,DWORD CmdOffs,LPVOID ExtraData,WORD mode,LPVOID CallBackPar,int PageNo);

#ifndef FRECT_DEFINED
  struct FAR fRECT {
    int left,top,right,bottom;
    };
  #define FRECT_DEFINED
#endif


struct MapElemData;
typedef MapElemData FAR* LPMAPELEMDATA;


class FAR ClientMap ;

class FAR MapElem {
 public:
  MapElem FAR* Next;
  fRECT        FlapRect;

  ClientMap FAR *Parent;

  BOOL         isEmpty;

  POINT        ptFlap[8];      // Polygon für die Flappe
  cField*      Title;          // Text in der Flappe als cField
  LPSTR        FlapText;       // Text in der Flappe als LPSTR
  BOOL         Selected;       // Element ausgewaehlt?
  int          Disabled;
  int          ElemType;
  COLORREF     ElemColor;
  HWND         hWndParent;
  LPVOID       _Data;
  LPVOID       _ExtraData;     // Inhalt dieses Zeigers ist ein Tabellenzeiger
  DWORD        _Proc;
  int          Row;            // in welcher Zeile bin ich?
  short        Position;
  HotKeyData   KeyData;

private:
  short        IndexX, IndexY;
  DWORD        BitId;
  LPSTR        HelpText;

public:
  LPVOID GetExtraData ()
    { return (_ExtraData != NULL) ? * ((LPVOID FAR *) _ExtraData) : NULL ; }
 
  MapElem (ClientMap FAR *p,LPSTR Text, WORD Type, COLORREF Color, 
           BOOL disabled, LPRECT rc, HWND hWndOwner, int flaprow, short Pos, 
           LPVOID Data, DWORD Proc, LPVOID ExtraData, BOOL Empty,
           HotKeyData FAR *kd, LPSTR Help, DWORD dwBitId, short bw, short bh);
  ~MapElem ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
    
  void Invalidate (BOOL erase);
  void Update (LPSTR Text,WORD Type, COLORREF Color,BOOL disabled,LPVOID ExtraData);

  void Disable (void) { Disabled = TRUE; };
  void Enable (void) { Disabled = FALSE; };

  void Paint (HDC hDC);
  BOOL HitTest (LPPOINT pt);
  void RePaint (void);
  void SetActive (BOOL State, BOOL redraw,int PageNo);
  void SetElemRect (LPRECT rc);

  void GetHelp (LPPOINT pt);
  void RemoveHelp ();
  };


class FAR ClientMap {
  public:
  int         m_FlapCnt;       // Gesamt Anzahl der Flappen
  int         m_FlapRows;      // wieviele Flappen-Zeilen hat die Mappe
  int         m_FlapCols;      // wieviele Spalten sind es wirklich
  BOOL        m_ChildMap;      // Mappe ist in einem Dialog oder eine 
                               // Untermappe in der grossen Mappe

  int FFont,FHeight,MOffset;
  LPMAPELEMDATA m_MapElemData;

  int          m_LogX;         // Startpositionen der Mappe
  int          m_LogY;

  fRECT        m_MapRect;       // gesamte Ausdehnung der Mappe inkl. Flappen und Rand
  fRECT        m_MapDocRect;    // in diesem Bereich kann jetzt gezeichnet werden
  fRECT        m_MapScreenRect; // in diesem Bereich kann jetzt gezeichnet werden
  int          m_ActiveFlap;    // die aktive Flappe
  HWND         m_hWndParent;    // Elternfenster der Mappe
  HWND         m_hWndMap;
  BOOL         DisableFlapChange;
  LPVOID       CallBackPar;

  MapElem FAR* FirstFlap;
  MapElem FAR* ActiveFlap;
  MapElem FAR* StartFlap;
  MapElem FAR* FirstFlapSet;

  HWND hWndBubble;
  MapElem FAR* HelpElem;

  ClientMap (int FlapCnt, LPMAPELEMDATA lpmed, LPVOID CallBackPar, BOOL ChildMap);
  ~ClientMap ();

  DLLExport void _export WINAPI DoActivate (BOOL state = TRUE);
  DLLExport void _export WINAPI Update (LPSTR Text,WORD Type, COLORREF Color,BOOL disable,LPVOID cbData);
  int   GetPageNo(MapElem FAR *e);

  DLLExport void _export WINAPI PaintMap (HDC hDC);
  DLLExport void _export WINAPI EraseBkGnd (HWND hWnd,HDC hDC);
  void SetParent (HWND hWnd);
  void InsertFlap (MapElem FAR* pme);
  void RemoveFlap (MapElem FAR *pme);
  DLLExport void _export WINAPI HitTest (LPPOINT pt);
  void CheckForReplacement (MapElem FAR* pme, int ElemCnt);
  
  DLLExport LPVOID _export WINAPI GetFirstExtraData (LPVOID FAR *x);
  DLLExport LPVOID _export WINAPI GetNextExtraData (LPVOID FAR *x);
  DLLExport void _export WINAPI SetActive (LPVOID x);

  DLLExport void _export WINAPI OnRButtonDown (LPPOINT pt);
  DLLExport void _export WINAPI OnMsg (HWND hWnd, UINT msg,
                                       WPARAM wParam, LPARAM lParam);

  int GetFlapHeight () ;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef ClientMap FAR* LPCLIENTMAP ;



struct FAR MapElemData {
  LPSTR    _Text;
  LPSTR    _Help;
  WORD     _Type;
  COLORREF _Color;
  BOOL     _Disabled;
  LPVOID   _CallBackData;
  LPVOID   _ExtraData;
  DWORD    _CallBackProc;
  short    _IndexX, _IndexY;
  DWORD    _BitId;

  
  LPMAPELEMDATA Next;
  HotKeyData hk;
  BOOL kdset;
  };


DLLExport LPCLIENTMAP _export WINAPI BuildMap (HWND hWParent,MAPCALLCOMMAND mcmd, BOOL ChildMap);
DLLExport void _export WINAPI NextMapElem (LPSTR Text, WORD Type, COLORREF Color, BOOL Disabled,
                                     LPVOID Data, int cbSize, DWORD cbp,
                                     LPVOID ExtraData,HotKeyData FAR *kd,
                                     LPSTR Help,
                                     DWORD dwBitId, short Ix, short Iy);
DLLExport void _export WINAPI StartSetmap (int af = -1,int lw = -1,int lh = -1,LPVOID CallBackPar = NULL);
DLLExport void _export WINAPI DestroyMap (LPCLIENTMAP map);
BOOL RegisterFlapMap (HINSTANCE hInstance);
DLLExport void _export WINAPI DisableMap (LPCLIENTMAP pClientMap);
DLLExport void _export WINAPI EnableMap (LPCLIENTMAP pClientMap);
DLLExport BOOL _export WINAPI IsMapHotKey (LPMSG lpmsg, LPCLIENTMAP pClientMap);
DLLExport void _export WINAPI SetStartInd (int ind);
DLLExport void _export WINAPI SetMapExtent (int lx, int ly, int lw, int lh);
DLLExport void _export WINAPI SetMapFont (short Format);
DLLExport void _export WINAPI SetFlapHeight (short Height);
DLLExport void _export WINAPI SetMapOffset (short Offset);


