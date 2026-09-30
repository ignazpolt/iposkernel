//////////////////////////////////////////////////////////////////
//      Globale Klasse zur Bearbeitung der MDI - Client
//              Meldungen
//////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/mdiclien.hpv   1.9   05 Oct 1998 11:24:10   Gerhold  $
// $Log:   P:/marille/clinicum/include/rev/mdiclien.hpv  $
// 
//    Rev 1.9   05 Oct 1998 11:24:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.8   11 Apr 1997 11:41:04   Gerhold
// Statuszeile jetzt mit Vorder- und Hintergrundfarbe
// 
//    Rev 1.7   07 Apr 1997 19:22:30   gerhold
// SetWndPos ... 2.ter Parameter wParam ist neu
// 
//    Rev 1.6   24 Sep 1996 17:21:18   MARTIN
// StatText loeschen bei Destroy eines MDIChild
// 
//    Rev 1.5   04 Feb 1996 21:45:56   HANNES
// 
//    Rev 1.4   02 Feb 1996 10:59:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   20 May 1995 14:19:42   HANNES
// 
//    Rev 1.2   07 Nov 1994 19:20:04   GERHOLD
// Default-Parameter fuer eines der beiden Status-Felder.
// 
//    Rev 1.1   07 Nov 1994 11:30:38   GERHOLD
// Statusbar
// 
//    Rev 1.0   24 Jun 1994 17:01:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.9   28 May 1993 21:21:38   HANNES
// Bitmaps in das EXE ...
// 
//    Rev 1.8   10 May 1993 12:51:58   HANNES
// Knopfe aus der Symbolleiste ausgenommen
// 
//    Rev 1.7   29 Jan 1993 18:38:42   HANNES
// Verbesserte Hilfetexte, Einbau des Untersuchungsknoepfchens
// 
//    Rev 1.6   24 Jan 1993 13:07:58   HANNES
// Einbau der Kurzhilfe in der Feldverwaltung
// 
//    Rev 1.5   18 Jan 1993 16:53:40   HANNES
// Neuen Knopf: Datensatzliste
// 
//    Rev 1.4   06 Jan 1993 17:01:40   HANNES
// Logik der Klientenfensterverwaltung hat sich geaendert
// 
//    Rev 1.3   17 Dec 1992 15:58:16   HANNES
// Neue Knoepfe auf der Seite
// 
//    Rev 1.2   04 Dec 1992 19:37:56   HANNES
// Erweiterung der Klasse ButtonBar um 2 Standardknoepfe
// 
//    Rev 1.1   03 Dec 1992 13:56:06   HANNES
// No change.
// 
//    Rev 1.0   02 Dec 1992 16:01:54   HANNES
// Initial revision.

#ifdef MDICLIEN_MAIN
static char *_MyMDIClient = "MYMDICLIENT";
static char *_StatusBar = "StatusBarT";
#define MDIClientClass  _MyMDIClient
#define STATUSBARCLASS  _StatusBar

#endif

#ifndef DDL
#define MAXCHILDS       20

class mdiClient {
 protected :
  HWND MyHandle;
  WNDPROC DefClientWndProc;
 public :
  HWND GetClientHandle ()
    { return MyHandle ; }
  void SetWndPos (HWND, WPARAM);
  BOOL RegisterMDIClient (HINSTANCE);
  HWND CreateMDIClient (HWND,HINSTANCE,CLIENTCREATESTRUCT FAR *);

  friend DLLExport LONG _export FAR PASCAL MyClientWndProc (HWND,UINT,WPARAM,LPARAM);
  };

class StatusBar {
 private:
  BOOL oldstatusType;
  BOOL oldstatusNmbr;
  HINSTANCE MyInst;
  HINSTANCE actInst;
  HFONT statusFont;
  char StatusStr0[128];
  char StatusStr1[128];
 public :
  HWND MyHandle;
  int height;

  void Init ();
  void Exit ();
  int GetHeight()
    { return height ; }
  int GetTextLength0 ()
    { return sizeof (StatusStr0) ; }
  int GetTextLength1 ()
    { return sizeof (StatusStr1) ; }
  BOOL Register(HINSTANCE);
  BOOL Create (HWND,HANDLE);
  void Show ()
    { ShowWindow (MyHandle,SW_NORMAL); }
  void Paint ();
  void SetStatus (HINSTANCE,BOOL,int,UINT FieldPos = 1,
                  COLORREF foreColor = 0xFFFFFFFF, COLORREF backColor = 0xFFFFFFFF);
  void SetStatus (LPSTR, UINT FieldPos = 1,
                  COLORREF foreColor = 0xFFFFFFFF, COLORREF backColor = 0xFFFFFFFF);

  void GetStatusStr (UINT FieldPos);
  };

#ifdef MDICLIEN_MAIN
  mdiClient ClientWnd;
  StatusBar PrgStat;
#else
  extern mdiClient ClientWnd;
  extern StatusBar PrgStat;
#endif

#endif
