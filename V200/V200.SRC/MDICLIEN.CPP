// $Header:   P:/marille/clinicum/rev/mdiclien.cpv   1.51   05 Oct 1998 11:55:38   Gerhold  $
// $Log:   P:/marille/clinicum/rev/mdiclien.cpv  $
// 
//    Rev 1.51   05 Oct 1998 11:55:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.50   20 Mar 1998 15:28:34   Hannes
// 
//    Rev 1.49   10 Mar 1998 09:15:20   Gerhold
// EndCreateMappe invalidiert das MDI-Client Fenster
// 
//    Rev 1.48   10 Feb 1998 18:27:28   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.47   02 Jan 1998 16:17:00   Gerhold
// AddMapElem ... (Der Hotkey ist an 8 * DWORD nicht 9 * DWORD)
// 
//    Rev 1.46   19 Nov 1997 18:47:52   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.45   18 Aug 1997 17:24:48   GERHOLD
// schnelle Loesung: hbrBackGround = GetStockObject  statt COLOR_xxxx
// 
//    Rev 1.44   10 Jul 1997 08:58:04   Hannes
// 
//    Rev 1.43   19 Jun 1997 15:57:12   Gerhold
// StartCreateMappe ... Anzahl der Faecher pro Reihe ist keine Konstante mehr
// 
//    Rev 1.42   28 Apr 1997 17:01:00   Martin
// ent-warning-isiert
// 
//    Rev 1.41   28 Apr 1997 14:57:26   Martin
// Grrmtjfxx !
// 
//    Rev 1.40   28 Apr 1997 14:13:36   Hannes
// Verbesserter Aufruf fuer 32 Bit
// 
//    Rev 1.39   11 Apr 1997 11:39:06   Gerhold
// Statuszeile hat jetzt Vorder- und Hintergrundfarbe
// 
//    Rev 1.38   08 Apr 1997 17:41:40   gerhold
// SetFlapHeight, SetMapOffset
// 
//    Rev 1.37   07 Apr 1997 19:13:24   gerhold
// mdiClient::SetWndPos ... Parameter wP gibt den Zustand des WM_SIZE an
// Vorbereitung der neuen Funktion SetMapFont
// 
//    Rev 1.36   25 Feb 1997 12:13:48   Gerhold
// Mausnachrichten an die Mappe weiterleiten. AddMappElem wurde um Hilfetext
// und Bitmap erweitert.
// 
//    Rev 1.35   21 Jan 1997 11:24:46   HANNES
// Aenderung an ActivateMapElem
// 
//    Rev 1.34   09 Dec 1996 18:23:00   HANNES
// Fehlerkorrektur beim Abbau von Mappenschirmen
// 
//    Rev 1.33   12 Nov 1996 14:37:06   GERHOLD
// EndCreateMappe ... BuildMap bekommt einen Parameter der angibt ob die Mappe
//                    einen Screen als Parent hat (scl != NULL)
// 
//    Rev 1.32   08 Nov 1996 13:34:18   HANNES
// 
//    Rev 1.31   24 Sep 1996 16:32:46   MARTIN
// StatText loeschen bei Destroy eines MDIChild
// 
//    Rev 1.30   10 Jun 1996 10:09:30   GERHOLD
// pragma pack
// 
//    Rev 1.29   04 Feb 1996 21:45:46   HANNES
// 
//    Rev 1.28   02 Feb 1996 10:41:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.27   31 Jan 1996 19:30:18   GERHOLD
// MapCall...
// 
//    Rev 1.26   10 Nov 1995 12:25:52   HANNES
// Korrektur Hannes
// 
//    Rev 1.25   24 Aug 1995 00:20:04   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.24   14 Aug 1995 12:18:24   HANNES
// Mappenhotkeys
// 
//    Rev 1.23   14 Aug 1995 11:07:28   GERHOLD
// 
//    Rev 1.22   27 Apr 1995 15:37:50   HANNES
// 
//    Rev 1.21   12 Apr 1995 12:26:30   HANNES
// 
//    Rev 1.20   27 Mar 1995 13:17:16   HANNES
//  
// 
//    Rev 1.19   20 Mar 1995 12:05:22   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.18   06 Feb 1995 16:52:40   HANNES
// 
//    Rev 1.17   16 Dec 1994 16:25:30   GERHOLD
// Focus Gschichterln
// 
//    Rev 1.16   15 Dec 1994 23:49:50   HANNES
// Focusgschichtln...
// 
//    Rev 1.15   28 Nov 1994 20:01:04   GERHOLD
// CheckMapHotKey
// 
//    Rev 1.14   17 Nov 1994 18:20:14   GERHOLD
// WM_MDINEXT ... if (IsWindow(NextWindow))
// WM_MDITILE .. if (AnzChilds == 0)
// 
//    Rev 1.13   09 Nov 1994 13:08:40   HANNES
// StatBar::Register
// 
//    Rev 1.12   08 Nov 1994 12:44:14   HANNES
// Statuszeilen - verarbeitung
// 
//    Rev 1.11   07 Nov 1994 19:19:24   GERHOLD
// SetStatus ... Angabe in welches Statusfeld der Text geschrieben wird.
// 
//    Rev 1.10   07 Nov 1994 14:33:12   GERHOLD
// SetWndPos ... IsWindow(PrgStat.MyHandle)
// 
//    Rev 1.9   07 Nov 1994 11:28:48   GERHOLD
// neuen Statusbar erstmalig verwendet.
// 
//    Rev 1.8   03 Oct 1994 18:02:14   HANNES
// Fehlerkorrektur in ExtraRef
// 
//    Rev 1.7   20 Sep 1994 11:40:22   GERHOLD
// mehrere Mappen jetzt gleichzeitig moeglich
// 
//    Rev 1.6   26 Aug 1994 10:12:34   HANNES
// ActivateMapElem
// 
//    Rev 1.5   17 Aug 1994 09:36:48   HANNES
// Mappe ... Groessenangabe, Extradaten muessen nicht mehr zwingend angegeben
// werden
// 
//    Rev 1.4   05 Aug 1994 17:09:44   GERHOLD
// Farb Parameter in Mappe eingefuegt
// 
//    Rev 1.3   17 Jul 1994 14:45:38   HANNES
// Mappenhandling
// 
//    Rev 1.2   13 Jul 1994 21:16:04   HANNES
// Mappenverwaltung (Zwischenversion)
// 
//    Rev 1.1   12 Jul 1994 14:49:44   GERHOLD
// 
//    Rev 1.0   24 Jun 1994 17:05:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.23   13 Jan 1994 16:12:02   HANNES
// dfield inc. raus
// 
//    Rev 1.22   12 Jan 1994 11:10:16   HANNES
// Unnoetige Funktionen raus
// 
//    Rev 1.21   18 Aug 1993 10:33:04   HANNES
// Endgueltige Umstellung auf Toolbar
// 
//    Rev 1.20   22 Jul 1993 20:54:12   HANNES
// ??
// 
//    Rev 1.19   13 Jul 1993 11:09:26   HANNES
// Einstallbare Statuszeile
// 
//    Rev 1.18   05 Jul 1993 14:40:44   HANNES
// Einbindung der Toolbar
// 
//    Rev 1.17   03 Jun 1993 11:17:20   HANNES
// Anderung der Abmasse des Buttonbars
// 
//    Rev 1.16   02 Jun 1993 19:52:00   HANNES
// Position der Clientwindows
// 
//    Rev 1.15   28 May 1993 21:17:16   HANNES
// Verschiedene Versionen, POPUP in OVERLAP | CHILD umgesetzt
// 
//    Rev 1.14   10 May 1993 12:47:08   HANNES
// PatientenNeuaufnahme und globale Patientenverknuepfung rausgenommen
// 
//    Rev 1.13   17 Mar 1993 17:57:58   HANNES
// Hilfe beim Login richtig lesen
// 
//    Rev 1.12   11 Mar 1993 11:37:20   HANNES
// Fehlerkorrektur bei Hilfen
// 
//    Rev 1.11   22 Feb 1993 17:11:36   HANNES
// Verbesserte Hilfetexte
// 
//    Rev 1.10   17 Feb 1993 15:23:06   HANNES
// Verschiedene kleine Verbesserungen
// 
//    Rev 1.9   29 Jan 1993 18:56:42   HANNES
// Neuen Knopf zur Untersuchungsdefinition
// 
//    Rev 1.8   24 Jan 1993 13:05:56   HANNES
// Einbau der Kurzhilfe fuer die Formulare
// 
//    Rev 1.7   18 Jan 1993 16:47:04   HANNES
// Aenderungen des Handlings von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.6   06 Jan 1993 16:55:30   HANNES
// Neues Handling der MDI - Client Window Verwaltung
// 
//    Rev 1.5   17 Dec 1992 15:54:44   HANNES
// 2 neue Knoepfe am linken Rand: Printjoblist, Patientenverknuepfung)
// 
//    Rev 1.4   06 Dec 1992 18:42:22   HANNES
// Index - Korrektur fuer Statusanzeige (NEWPAT,PATLIST..)
// 
//    Rev 1.3   06 Dec 1992 10:57:48   HANNES
// Statusmeldungen der unteren Sonderknoepfen
// 
//    Rev 1.2   05 Dec 1992 15:48:46   HANNES
// Statusstrings der unteren Knoepfe
// 
//    Rev 1.1   04 Dec 1992 19:37:06   HANNES
// ButtonBar um 2 Knoepfe links unten (Patientenneueingabe, Patientenliste)
// erweitert
// 
//    Rev 1.0   02 Dec 1992 15:36:12   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#define MDICLIEN_MAIN
#include "mdiclien.hpp"
#include "globmem.h"
#include "dds.hpp"
#include "ddsmsg.h"    // WMU_DESTROYBUBBLE
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "hash.hpp"
#include "compile.hpp"
#include "cfield.hpp"

#define NODLL
#include "toolbar.hpp"
#include "mappe.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define MODULENUM 107
#include "winass.hpp"
#include "statbar.hpp"

#include "winextra.hpp"
#include "tbcbd.hpp"

#define DX      (BBar.GetWidth())
#define DY      (PrgStat.GetHeight())

HINSTANCE MDIInstance;

extern int xToolbarExt ();
void mdiClient::SetWndPos (HWND hWndFrame, WPARAM wP)
  {
  RECT r;
  GetClientRect (hWndFrame,&r);
  if (IsWindow(PrgStat.MyHandle))
    SendMessage (PrgStat.MyHandle, WM_SIZE, wP, MAKELONG(r.right-r.left, r.bottom-r.top));
  r.bottom -= (DY + 1);

  r.left   += xToolbarExt ();

  MoveWindow (MyHandle,r.left,r.top,
                       r.right - r.left + 1,
                       r.bottom - r.top + 1, TRUE);
  }

HWND ChildList[20];
int  AnzChilds;

DLLExport BOOL _export WINAPI EnumMDIClientChildProc (HWND hWndChild, LPARAM lParam)
  {
  char szClassName[40];
  
  GetClassName (hWndChild, szClassName, sizeof(szClassName)-1);

  if (!lstrcmp(szClassName, "MDICHILD"))
    ChildList[AnzChilds++] = hWndChild;

  return 1;
  }

void EnumerateChildWindows (HWND hWnd)
  {
  AnzChilds = 0;
  WNDENUMPROC wndEnumProc = (WNDENUMPROC)MakeProcInstance ((FARPROC)EnumMDIClientChildProc, MDIInstance);
  EnumChildWindows (hWnd, wndEnumProc, 0L);
  FreeProcInstance (wndEnumProc);
  }


LPCLIENTMAP lpClientMap;
DLLExport LONG _export FAR PASCAL MyClientWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0L;

  switch (msg) {
    case WM_SETFOCUS :
      ActivateMainToolBar (TRUE);
      if (GetFocus () == hWnd) {
#ifdef STRICT
        RetVal = CallWindowProc ((WNDPROC)ClientWnd.DefClientWndProc,hWnd,msg,wP,lP);
#else
        RetVal = CallWindowProc ((FARPROC)ClientWnd.DefClientWndProc,hWnd,msg,wP,lP);
#endif
        }
      break ;
    case WM_PAINT :
      // Meldungen vom Statusfenster loeschen
      {
      PAINTSTRUCT ps;

      HDC hDC = BeginPaint (hWnd,&ps);
      if (lpClientMap != NULL)
        lpClientMap->PaintMap (hDC);
      EndPaint (hWnd,&ps);
      }
      break ;

    case WM_ERASEBKGND :
      if (lpClientMap != NULL) {
        lpClientMap->EraseBkGnd (hWnd,HDC (wP));
        RetVal = 1L;
        }
      else
#ifdef STRICT
        RetVal = CallWindowProc (WNDPROC (ClientWnd.DefClientWndProc),hWnd,msg,wP,lP);
#else
        RetVal = CallWindowProc (FARPROC (ClientWnd.DefClientWndProc),hWnd,msg,wP,lP);
#endif
      break ;

    //------------------------------------------------------------------------
    // sucht in der MDI-Fensterliste das aktuelle MDI-Fensterhandle und 
    // schaltet je nach lParam auf das naechste oder das vorherige Fenster.
    case WM_MDINEXT :
      {
      HWND NewWindow = 0;

      if (FirstChild != LastChild) {
        LPMDIWNDLIST lpc = FirstChild;
        if (lpc != NULL) {
          do {
            if (lpc->hWndChild == HWND(wP)) {
              NewWindow = lP ? lpc->Prev->hWndChild : lpc->Next->hWndChild;
              break;
              }
            else  
              lpc = lpc->Next;
            } while (lpc != FirstChild);
          }  

        if (IsWindow(NewWindow))
          SendMessage (hWnd, WM_MDIACTIVATE, WPARAM(NewWindow), 0L);
        }
      }
      break;

    case WM_MDICASCADE :
      break;
      
    case WM_MDITILE :
      {
//      CallWindowProc (FARPROC (ClientWnd.DefClientWndProc),hWnd,msg,wP,lP);
      EnumerateChildWindows (hWnd);
      if (AnzChilds == 0)
        return RetVal;

      RECT rc, rcChild;
      GetClientRect (hWnd, &rc);   // Abmessungen des MDIClients

      for (int i = 1; ((i*i) < AnzChilds); i++);
      int Cols = ((i*i) == AnzChilds) ? i : i-1;
      if (Cols == 0) Cols++;
      int Rows = AnzChilds / Cols;
      int MulRows = AnzChilds % Cols;
      int ChildHeight = (rc.bottom-rc.top) / Rows;
      int ChildWidth = (rc.right-rc.left) / Cols;
      
      int GoodRows = Rows - MulRows;

      HDWP hdwp = BeginDeferWindowPos (AnzChilds);

      // Alle Fenster mit Cols Spalten
      int cnt;
      for (cnt = 0, i = 0; cnt < AnzChilds; cnt++, i++) {
        if ((i / Cols) < GoodRows) {
          rcChild.left = rc.left + ChildWidth*(cnt % Cols);
          rcChild.top = rc.top + ChildHeight*(cnt / Cols);
          rcChild.right = rcChild.left + ChildWidth;
          rcChild.bottom = rcChild.top + ChildHeight;

          DeferWindowPos (hdwp, ChildList[cnt], HWND_TOP, rcChild.left, rcChild.top,
                          rcChild.right-rcChild.left, rcChild.bottom-rcChild.top,
                          SWP_SHOWWINDOW);
          }
        else
          break;
        }  

      Cols++;
      ChildWidth = (rc.right-rc.left) / Cols;
      
      for ( ; cnt < AnzChilds; cnt++, i++) {
        rcChild.left = rc.left + ChildWidth*((cnt+1) % Cols);
        rcChild.top = rc.top + ChildHeight*((cnt+1) / Cols);
        rcChild.right = rcChild.left + ChildWidth;
        rcChild.bottom = rcChild.top + ChildHeight;

        DeferWindowPos (hdwp, ChildList[cnt], HWND_TOP, rcChild.left, rcChild.top,
                        rcChild.right-rcChild.left, rcChild.bottom-rcChild.top,
                        SWP_SHOWWINDOW);
        }  

      EndDeferWindowPos (hdwp);
      HWND hWndActiveChild = HWND(SendMessage (hWnd, WM_MDIGETACTIVE, 0, 0));
      SendMessage (hWnd, WM_MDIACTIVATE, (WPARAM)(HWND)hWndActiveChild, 0);
      
//      DrawMenuBar (GetParent(hWnd));

      }    
          
      break;
      
    case WM_LBUTTONDOWN :
      if ((lpClientMap != NULL) && (!lpClientMap->DisableFlapChange)) {

        POINT pt;
#ifdef WIN32
        LONG2POINT(lP, pt);
#else
        pt = MAKEPOINT(lP);
#endif

        lpClientMap->HitTest (&pt);
        }
      break ;

    case WM_RBUTTONDOWN :
      if (lpClientMap != NULL) {

        POINT pt;
#ifdef WIN32
        LONG2POINT(lP, pt);
#else
        pt = MAKEPOINT(lP);
#endif

        lpClientMap->OnRButtonDown (&pt);
        }
      break ;

    case WMU_DESTROYBUBBLE:
      if (lpClientMap != NULL)
        lpClientMap->OnMsg (hWnd, msg, wP, lP);
      break;

    case WM_MOUSEMOVE :
      // Meldungen vom Statusfenster loeschen
      PrgStat.SetStatus (NULL,FALSE,20800);
      // no break here
    default :
#ifdef STRICT
      RetVal = CallWindowProc (WNDPROC (ClientWnd.DefClientWndProc),hWnd,msg,wP,lP);
#else
      RetVal = CallWindowProc (FARPROC (ClientWnd.DefClientWndProc),hWnd,msg,wP,lP);
#endif
    }
  return RetVal;
  }

BOOL mdiClient::RegisterMDIClient (HINSTANCE hInst)
  {
  WNDCLASS  wc;

  MDIInstance = hInst;
  if (GetClassInfo (NULL,"mdiclient",&wc)) {
    DefClientWndProc = wc.lpfnWndProc;
    wc.lpfnWndProc   = MyClientWndProc;
    wc.hInstance     = hInst;
#ifdef WIN32
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
#else
    wc.hbrBackground = HBRUSH(COLOR_APPWORKSPACE+1);
#endif
    // Register the frame class 
    wc.lpszClassName = MDIClientClass;
    if (RegisterClass(&wc))
      return TRUE;
    }

  return FALSE;
  }

HWND mdiClient::CreateMDIClient (HWND hWnd,HINSTANCE hInst,CLIENTCREATESTRUCT FAR *ccs)
  {
  MyHandle = CreateWindow (MDIClientClass,
             NULL,
             WS_CHILD | WS_CLIPCHILDREN,
             0,
             0,
             0,
             0,
             hWnd,
             0,
             hInst,
             (LPSTR)ccs);
  return MyHandle ;
  }

/////////////////////////////////////////////////////////////////////////
//              Implementation des Statusbars
/////////////////////////////////////////////////////////////////////////
BOOL StatusBar::Register (HINSTANCE hInst)
  {
  MyInst = hInst;
  return TRUE;
  }

#define Y_EXTRA         6
#define FONTS               "Fonts"
#define STATUSBARHEIGHT     "StatusBarHeight"
#define STATUSBARHEIGHTDEF  8
// #define MYINI
HFONT GetStatusBarFont ()
  {
  // Lesen der Hoehe des Fonts aus dem ini - File
  int fntHeight = GetPrivateProfileInt (FONTS,STATUSBARHEIGHT,STATUSBARHEIGHTDEF,MYINI);
  return CreateFont (fntHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0,
                     FF_SWISS, "Ms Sans Serif");
  }

void StatusBar::Init ()
  {
  LRString (20812,StatusStr0,sizeof(StatusStr0));
  }

void StatusBar::Exit ()
  {
  }

BOOL StatusBar::Create (HWND hWnd,HANDLE hInst)
  {
  RECT rc;
  int FieldArray[2];
  
  GetClientRect (hWnd, &rc);
  FieldArray[0] = rc.right-rc.left-8;
  FieldArray[1] = FieldArray[0] - (rc.right-rc.left) / 3;
  
  MyHandle = CreateStatusbar (WS_VISIBLE, "Ready", hWnd, 999);

  if (IsWindow(MyHandle)) {
    SendMessage (MyHandle, SB_SETPARTS, 2, (LONG)(int FAR *)FieldArray);
    height = (int)SendMessage (MyHandle, SB_GETHEIGHT, 0, 0);
    }

  return (MyHandle != NULL);
  }

HPEN GetPen (HBRUSH brush)
  {
  LOGBRUSH lgo ;
  GetObject (brush,sizeof (LOGBRUSH),(LPSTR) &lgo);
  return CreatePen (PS_SOLID,1,lgo.lbColor);
  }

void StatusBar::Paint ()
  {
  RECT r;

  GetClientRect (MyHandle,&r);
  PAINTSTRUCT ps;
  HDC hDC = BeginPaint (MyHandle,&ps);
  EndPaint (MyHandle,&ps);
  }

void StatusBar::GetStatusStr (UINT FieldPos)
  {
  if (!oldstatusType) {
    if (FieldPos == 0)
      LoadString (MyInst,oldstatusNmbr,StatusStr0,GetTextLength0());
    else
      LoadString (MyInst,oldstatusNmbr,StatusStr1,GetTextLength1());
    }
  }

void StatusBar::SetStatus (HINSTANCE hInst, BOOL type, int Nmbr, UINT FieldPos,
                           COLORREF foreColor, COLORREF backColor)
  {
  if (((oldstatusType != type) || (Nmbr != oldstatusNmbr) ||
        (actInst != hInst)) && (!IsCaretShown())) {
    oldstatusNmbr = Nmbr ;
    oldstatusType = type ;
    actInst = hInst;
    GetStatusStr (FieldPos);

    SetFieldColor (MyHandle, FieldPos, foreColor, backColor);

    if (FieldPos == 0)
      SendMessage (MyHandle, SB_SETTEXT, FieldPos, LONG(LPSTR(StatusStr0)));
    else
      SendMessage (MyHandle, SB_SETTEXT, FieldPos, LONG(LPSTR(StatusStr1)));
    }
  }

void StatusBar::SetStatus (LPSTR str, UINT FieldPos, COLORREF foreColor, COLORREF backColor)
  {
  if (FieldPos == 0) {
    if ((lstrcmp (StatusStr0,str) != 0) && ((!IsCaretShown()) || (FieldPos != 1))) {
      StatusStr0[GetTextLength0()-1] = '\0';
      lstrncpy (StatusStr0,str,GetTextLength0()-1);

      if (*str)
        SetFieldColor (MyHandle, FieldPos, foreColor, backColor);
      else
        ResetFieldColor (MyHandle, FieldPos);

      SendMessage (MyHandle, SB_SETTEXT, FieldPos, LONG(LPSTR(StatusStr0)));
      oldstatusType = 0xFFFF;
      }
    }
  else {
    if ((lstrcmp (StatusStr1,str) != 0) && ((!IsCaretShown()) || (FieldPos != 1))) {
      StatusStr1[GetTextLength1()-1] = '\0';
      lstrncpy (StatusStr1,str,GetTextLength1()-1);

      if (*str)
        SetFieldColor (MyHandle, FieldPos, foreColor, backColor);
      else
        ResetFieldColor (MyHandle, FieldPos);

      SendMessage (MyHandle, SB_SETTEXT, FieldPos, LONG(LPSTR(StatusStr1)));
      oldstatusType = 0xFFFF;
      }
    }
  }

static DWORD ExtraRef,lastExtraRef;
MAPCALLCOMMAND mcmd;
#pragma pack(1)
struct FAR StartCreateMappe_param {
  WORD parSize;
  DWORD obj;
  DWORD refPar;
  DWORD _AnzFlaps;
  DWORD _lw;
  DWORD _lh;
  DWORD _PageInd;

  BOOL doExtra()
    { return (parSize >= sizeof(*this)) ; }
  };
#pragma pack()
struct ParToCStart {
  StartCreateMappe_param FAR *p;
  mdiChild *cStart;
  };
#define MDIM 32
static ParToCStart c2p[MDIM];
void SetC2Par (StartCreateMappe_param FAR *p,mdiChild *cStart)
  {
  for (int i = 0 ; i < MDIM ; i++) {
    if (c2p[i].p == NULL) {
      c2p[i].p = p;
      c2p[i].cStart = cStart;
      return ;
      }
    }
  DBWIN_ASSERT(FALSE);
  }
void DelC2Par (StartCreateMappe_param FAR *p)
  {
  for (int i = 0 ; i < MDIM ; i++) {
    if (c2p[i].p == p) {
      c2p[i].p = NULL;
      c2p[i].cStart = NULL;
      return ;
      }
    }
  DBWIN_ASSERT(FALSE);
  }
mdiChild FAR *GetCStart (StartCreateMappe_param FAR *p)
  {
  for (int i = 0 ; i < MDIM ; i++) {
    if (c2p[i].p == p)
      return c2p[i].cStart;
    }
  DBWIN_ASSERT(FALSE);
  return NULL;
  }
DLLExport VOID _export WINAPI _MapCallCommand (LPVOID PrivData,DWORD CmdOffset,LPVOID ExtraData,WORD mode,LPVOID CallBackPar,int PageNo)
  {
  StartCreateMappe_param FAR *par = (StartCreateMappe_param FAR *) CallBackPar ;
  if (LPTBD(PrivData)->Extra != NULL) {
    SAVEREC old;
    LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra);
    SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra);

    LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();
    LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;

    if (ExtraData != NULL)
//      LPTBD (PrivData)->c->WritelData (ExtraRef,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
      LPTBD (PrivData)->c->WritelData (par->refPar,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
    if ((par->doExtra()) && (PageNo >= 0))
      GetCStart (par)->WritelData (par->_PageInd,&PageNo,sizeof(PageNo),par,FALSE);
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,mode);
    LPTBD(PrivData)->c->RestoreRecs(old);
    }
  else {
    if (ExtraData != NULL)
//      LPTBD (PrivData)->c->WritelData (ExtraRef,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
      LPTBD (PrivData)->c->WritelData (par->refPar,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
    if ((par->doExtra()) && (PageNo >= 0))
      LPTBD (PrivData)->c->WritelData (par->_PageInd,&PageNo,sizeof(PageNo),par,FALSE);
    LPTBD (PrivData)->c->ExCuteProc (CmdOffset,mode);
    }
  }

MAPCALLCOMMAND GetMapCallCommand ()
  {
  if (mcmd == NULL)
    mcmd = MAPCALLCOMMAND (MakeProcInstance (FARPROC(_MapCallCommand),WBase::hInstance));
  return mcmd;
  }

BOOL StartCreateMappe (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    StartCreateMappe_param FAR *par = (StartCreateMappe_param FAR *) param;
    SetC2Par (par,c);
    lastExtraRef = par->refPar;

    DBINT FAR *lpAnzFlaps = (DBINT FAR *) c->ReadlData (par->_AnzFlaps);
    DBWIN_ASSERT ((lpAnzFlaps != NULL) && (*lpAnzFlaps != NULL));

//    DBWIN_ASSERT (c->IsConst (par->_AnzFlaps));
    DBINT AnzFlaps = *((DBINT FAR *) c->ReadlData (par->_AnzFlaps));
    DBWIN_ASSERT (c->IsConst (par->_lw));
    DBINT lw = *((DBINT FAR *) c->ReadlData (par->_lw));
    DBWIN_ASSERT (c->IsConst (par->_lh));
    DBINT lh = *((DBINT FAR *) c->ReadlData (par->_lh));
    StartSetmap (AnzFlaps,lw,lh,par);
    if (par->doExtra()) {
      DBINT FAR *page = (DBINT FAR *) c->ReadlData (par->_PageInd);
      if ((page != NULL) && (*page >= 0))
        SetStartInd (*page);
      }
    }

  if (mode & EM_FIXCONNECTION) {
    StartCreateMappe_param FAR *par = (StartCreateMappe_param FAR *) param;
    c->SetlConnection (par->_AnzFlaps,LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    StartCreateMappe_param FAR *par = (StartCreateMappe_param FAR *) param;

    c->ClearlConnection (par->_AnzFlaps,LPSTR(param)-sizeof(WORD));

    LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));
    (*lpobj)->DoActivate (FALSE);
    DelC2Par (par);
    }
  return FALSE ;
  }

#pragma pack(1)
struct AddMappElem_param {
  WORD  parSize;
  LPVOID oldcbData;
  DWORD obj;
  DWORD Text;
  DWORD Type;
  DWORD Color;     // Farbfleck bzw. Transparentfarbe bei Bild
  DWORD disabled;
  DWORD Proc;
  DWORD cbData;
  DWORD hk;        // Hotkey
  DWORD Help;      // Hilfetext
  DWORD Bitmap;    // Bild im Mappenfach
  DWORD IndexX;    // Bildindex
  DWORD IndexY;    // Bildindex
  };
#pragma pack()

BOOL AddMappElem (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    AddMappElem_param FAR *par = (AddMappElem_param FAR *) param ;
    LPVOID cbData;
    if (mode & EM_LOAD) {
      cbData = c->ReadlData(par->cbData);
      if (cbData != NULL)
        lmemcpy (&par->oldcbData,cbData,sizeof(LPVOID));
      else
        par->oldcbData = NULL ;
      }
    LPSTR Text = LPSTR(c->ReadlData (par->Text));
    LPWORD Type = LPWORD(c->ReadlData (par->Type));
    LPLONG Color = LPLONG(c->ReadlData (par->Color));
    DBBOOL FAR *disabled = (DBBOOL FAR *) c->ReadlData (par->disabled);
    HotKeyData FAR *hkdata;

//    if (par->parSize >= sizeof(*par))

    if (par->parSize > sizeof(WORD) + 8 * sizeof(DWORD))
      hkdata = (HotKeyData FAR *) c->ReadlData (par->hk);
    else
      hkdata = NULL ;

    LPSTR HelpText = NULL;
    if (par->parSize > sizeof(WORD) + 9 * sizeof(DWORD))
      HelpText = LPSTR(c->ReadlData (par->Help));

    short IndexX = -1, IndexY = -1;
    DWORD BitId = 0;
    if ((par->parSize > sizeof(WORD) + 10 * sizeof(DWORD)) &&
        (par->parSize < sizeof(WORD) + 13 * sizeof(DWORD))) {

      BitId = par->Bitmap;
      DBINT FAR* lpIndexX = (DBINT FAR *) c->ReadlData (par->IndexX);
      DBINT FAR* lpIndexY = (DBINT FAR *) c->ReadlData (par->IndexY);
      if ((lpIndexX == NULL) && (lpIndexY == NULL)) {
        DBWIN_ASSERT_TEXT (FALSE, "Falscher Index fr Fach-Bitmap");
        }
      else {
        IndexX = *lpIndexX;
        IndexY = *lpIndexY;
        }
      }

    toolbar_cbdata h(c);
    WORD t = WORD((Type != NULL) ? *Type : 0);
    if (mode & EM_LOAD)
      NextMapElem (Text, t, (Color != NULL) ? *Color : 0,
                        (disabled != NULL) ? *disabled : 0,
                        LPVOID(&h),int(sizeof(h)),par->Proc,cbData,hkdata,
                        HelpText, BitId, IndexX, IndexY);
/*-------------------------------------------------------------------------
NextMapElem (LPSTR Text, WORD Type, COLORREF Color, BOOL Disabled,
                                     LPVOID Data, int cbSize, DWORD cbp,
                                     LPVOID ExtraData,HotKeyData FAR *kd);
--------------------------------------------------------------------------*/
    else {
      LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->obj);
      DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));
      (*lpobj)->Update (Text, t, (Color != NULL) ? *Color : 0,
                        (disabled != NULL) ? *disabled : 0, LPVOID(&par->oldcbData));
/*------------------------------------------------------------------------
  void _export FAR PASCAL Update (LPSTR Text,WORD Type, COLORREF Color,
                                  BOOL disable,LPVOID cbData);
-------------------------------------------------------------------------*/
      }

    }
  if (mode & EM_FIXCONNECTION) {
    AddMappElem_param FAR *par = (AddMappElem_param FAR *) param ;
    c->SetlConnection (par->Text,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Type,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->disabled,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AddMappElem_param FAR *par = (AddMappElem_param FAR *) param ;
    c->ClearlConnection (par->Text,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Type,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->disabled,LPSTR(param)-sizeof(WORD));
    par->oldcbData = NULL;
    }
  return FALSE ;
  }

#pragma pack(1)
struct EndCreateMappe_param {
  WORD parSize;
  DWORD obj;
  DWORD ParentScreen;
  };
#pragma pack()

BOOL EndCreateMappe (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    EndCreateMappe_param FAR *par = (EndCreateMappe_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->ParentScreen);

    HWND hWParent;
    if (scl != NULL)
      hWParent = (* scl)->hWnd;
    else {
      //------------------------------------------------------------------
      // wird eine neue Mappe angelegt die keine Kindmappe ist, also die
      // den MDIClient als Parent hat, wird der Hintergrund einmal
      // komplett invalidiert.
      //------------------------------------------------------------------
      RECT rc;

      hWParent = ClientWnd.GetClientHandle ();
      GetClientRect (hWParent, &rc);
      InvalidateRect (hWParent, &rc, FALSE);
      }
    LPCLIENTMAP obj = BuildMap (hWParent,GetMapCallCommand (), scl != NULL);
//    LPCLIENTMAP obj = BuildMap (hWParent,GetMapCallCommand (), TRUE);
    DBWIN_ASSERT (obj != NULL);
    c->WritelData (par->obj,&obj,sizeof(obj),LPSTR(param)-sizeof(WORD));
    RECT rc;
    CopyRect (&rc,LPRECT(&(obj)->m_MapRect));
    // InvalidateRect (hWParent,NULL,TRUE);
    InflateRect (&rc,2,2);
    InvalidateRect (hWParent,&rc,TRUE);

    if (scl == NULL) {
      ExtraRef = lastExtraRef ;
      lpClientMap = obj ;
      }
    else {
      SetWindowLong ((*scl)->hWndToolbar (),GWL_MAPPTR,LONG(obj));
      }

    obj->DoActivate ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EndCreateMappe_param FAR *par = (EndCreateMappe_param FAR *) param;
    LPSCREEN FAR *scl = (LPSCREEN FAR *) 
          c->ReadlData (par->ParentScreen);
    LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));
    RECT rc;
    CopyRect (&rc,LPRECT(&(*lpobj)->m_MapRect));
    DestroyMap (*lpobj);
    if (*lpobj == lpClientMap) {
      lpClientMap = NULL;
      InvalidateRect (ClientWnd.GetClientHandle (),NULL,TRUE);
      }
    if ((scl != NULL) && (*scl != NULL)) {
      InflateRect (&rc,2,2);
      InvalidateRect ((*scl)->hWndToolbar (),&rc,TRUE);
      SetWindowLong ((*scl)->hWndToolbar (),GWL_MAPPTR,0L);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetMapFont_param {
  WORD parSize;
  DWORD FontIndex;
  };
#pragma pack()

BOOL SetMapFont (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetMapFont_param FAR *par = (SetMapFont_param FAR *) param;

//    LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->obj);
//    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));

    DBINT FAR *lpFormat = (DBINT FAR *) c->ReadlData (par->FontIndex);
    if (lpFormat == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "kein Index fr Schriftarten");
      }

    short Format = lpFormat ? *lpFormat : 0;
    SetMapFont (Format);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetMapFont_param FAR *par = (SetMapFont_param FAR *) param;
    c->ClearlConnection (par->FontIndex,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct FAR SetFlapHeight_param {
  WORD parSize;
  DWORD Height;
  };
#pragma pack()

BOOL SetFlapHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFlapHeight_param FAR *par = (SetFlapHeight_param FAR *) param;

    DBINT FAR *lpHeight = (DBINT FAR *) c->ReadlData (par->Height);
    if (lpHeight == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "ungueltige Hoehe fuer Reiter");
      }

    short Height = lpHeight ? *lpHeight : 10;
    SetFlapHeight (Height);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetFlapHeight_param FAR *par = (SetFlapHeight_param FAR *) param;
    c->ClearlConnection (par->Height,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct FAR SetMapOffset_param {
  WORD parSize;
  DWORD Offset;
  };
#pragma pack()

BOOL SetMapOffset (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetMapOffset_param FAR *par = (SetMapOffset_param FAR *) param;

    DBINT FAR *lpOffset = (DBINT FAR *) c->ReadlData (par->Offset);
    if (lpOffset == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "ungueltiger Mappen-Offset");
      }

    short Offset = lpOffset ? *lpOffset : 0;
    SetMapOffset (Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetMapOffset_param FAR *par = (SetMapOffset_param FAR *) param;
    c->ClearlConnection (par->Offset,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }


#pragma pack(1)
struct FAR ActivateMapElem_param {
  WORD parSize;
  DWORD obj;
  DWORD ProcToCall;
  DWORD Flag;
  DWORD ExtraRef;
  };
#pragma pack()

BOOL ActivateMapElem (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ActivateMapElem_param FAR *par = (ActivateMapElem_param FAR *) param;
    LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));
    LPVOID h;
    for (LPVOID ExtraData = (*lpobj)->GetFirstExtraData (&h) ;
                h != NULL ; ExtraData = (*lpobj)->GetNextExtraData (&h) ) {
      if (ExtraData != NULL) {
        LPVOID PrivData = ((MapElem FAR*) h)->_Data;
        if (LPTBD(PrivData)->Extra != NULL) {
          SAVEREC old;
          LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra);
          SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra);

          LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();
          LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;

          LPTBD (PrivData)->c->WritelData (par->ExtraRef,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
          LPTBD (PrivData)->c->ExCuteProc (par->ProcToCall,EM_LOAD | EM_CHANGETOTRUE);
          LPTBD (PrivData)->c->ExCuteProc (par->ProcToCall,EM_RESET);
          LPTBD(PrivData)->c->RestoreRecs(old);
          DBBOOL FAR *flag = (DBBOOL FAR *) c->ReadlData (par->Flag);
          if ((flag != NULL) && (*flag)) {
            (*lpobj)->SetActive (h);
            break ;
            }
          }
        else {
          LPTBD (PrivData)->c->WritelData (par->ExtraRef,ExtraData,GetBlockSize(ExtraData),NULL,FALSE);
          LPTBD (PrivData)->c->ExCuteProc (par->ProcToCall,EM_LOAD | EM_CHANGETOTRUE);
          LPTBD (PrivData)->c->ExCuteProc (par->ProcToCall,EM_RESET);
          DBBOOL FAR *flag = (DBBOOL FAR *) c->ReadlData (par->Flag);
          if ((flag != NULL) && (*flag)) {
            (*lpobj)->SetActive (h);
            break ;
            }
          }
        }
      }
    }
  return FALSE ;
  }


//----------------------------------------------------------------------------
// Ueberprueft ob die Nachricht (speziell Tastaturnachrichten CTRL-F6, ...),
// fuer die aktuelle Mappe bestimmt ist.
//----------------------------------------------------------------------------
BOOL CheckMapHotKey (MSG *msg)
  {
  return ((lpClientMap != NULL) && (!lpClientMap->DisableFlapChange) && 
                    (IsMapHotKey (msg, lpClientMap)));
  }

#pragma pack(1)
struct DisableFlapChange_param {
  WORD parSize;
  DWORD mRef;
  DWORD _state;
  };
#pragma pack()

BOOL DisableFlapChange (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DisableFlapChange_param FAR *par = (DisableFlapChange_param FAR *) param;
    LPCLIENTMAP FAR *lpobj = (LPCLIENTMAP FAR *) c->ReadlData (par->mRef);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL));
    DBBOOL state = *((DBBOOL FAR *) c->ReadlData (par->_state));
    (*lpobj)->DisableFlapChange = BOOL (state);
    }
  return FALSE ;
  }

void ActivateStatBar (mdiChild *c,BOOL state,COLORREF foreColor,COLORREF backColor)
  {
  LPSTR txt = LPSTR (c->GetDocumentExtraData (DED_RSTATBARTEXT));
  if ((txt != NULL) && (state))
    PrgStat.SetStatus (LPSTR(txt),(UINT) 0,foreColor,backColor);
  else
    PrgStat.SetStatus (LPSTR(""),(UINT) 0,(COLORREF)0xFFFFFFFF,(COLORREF)0xFFFFFFFF);
  }


