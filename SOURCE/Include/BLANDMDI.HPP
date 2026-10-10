//--------------------------------------------------------------------------
// MDI - Include - Datei
//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/include/rev/blandmdi.hpv   1.12   05 Oct 1998 11:24:02   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/blandmdi.hpv  $
// 
//    Rev 1.12   05 Oct 1998 11:24:02   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   02 Feb 1996 11:00:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   23 Aug 1995 11:04:38   GERHOLD
// 
//    Rev 1.9   15 May 1995 08:53:02   GERHOLD
// 
//    Rev 1.8   26 Apr 1995 15:31:40   HANNES
// 
//    Rev 1.7   24 Apr 1995 15:46:00   GERHOLD
// 
//    Rev 1.6   27 Mar 1995 10:41:54   GERHOLD
// 
//    Rev 1.5   16 Feb 1995 12:48:10   GERHOLD
// 
//    Rev 1.4   24 Jan 1995 09:58:40   GERHOLD
// ein bisserl in der Klasse veraendert
// 
//    Rev 1.3   17 Jan 1995 15:52:38   Hannes
// Menue - Fehlerkorrektur
// 
//    Rev 1.2   03 Jan 1995 12:04:14   HANNES
// 
//    Rev 1.1   02 Jan 1995 10:19:58   GERHOLD
// 
//    Rev 1.0   02 Jan 1995 09:49:36   GERHOLD
// Initial revision.
//--------------------------------------------------------------------------
// Copyright 1991 Microsoft Corporation. All rights reserved.
#include "windows.h"


#define   GWW_LISTWINDOW   0

struct FAR WndDef {
  HWND hWnd;
  int  x0, y0, x1, y1;
  };
typedef WndDef FAR* LPWNDDEF;


/* External variable declarations */
extern HINSTANCE MyInstance;  /* application instance handle  */
extern HWND hwndFrame;     /* main window handle           */
extern HWND hwndMDIClient; /* handle of MDI Client window  */
extern HWND hWndToolbar;
extern HWND hWndToolbarDialog;
extern HWND hWndToolbarForm;
extern HWND hWndDock;
extern HWND hWndCombo;
extern HWND hWndStatusbar;
extern HWND hWndProjectList;

extern HMENU hMenuMain, hMenuDialog, hMenuWndInMDI;
// Handle der Popup-Menus in die die Titel der Childs geschrieben werden
extern HMENU hMenuMainWindow, hMenuDialogWindow, hMenuWndInMDIWindow;

extern HFONT hFontEdit;

extern LONG styleDefault;  /* default child creation state */
extern char szChild[];     /* class of child               */

extern BOOL IsRasterEnabled ();
extern void EnableRaster (BOOL bShow);

extern void GetRasterDialog (HWND hWnd);   // Aufruf der Dialogbox
extern void SetRasterUnits (int x, int y);
extern void GetRasterUnits (int FAR *x, int FAR *y);

/* External functions */
extern BOOL WINAPI InitializeApplication(void);
extern BOOL WINAPI InitializeInstance   (LPSTR,WORD);
extern HWND WINAPI MakeNewChild (LPSTR);
extern HWND WINAPI MakeNewChildContainer (LPSTR);
extern DLLExport LONG FAR PASCAL _export BlandFrameWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern DLLExport LONG FAR PASCAL _export BlandMDIChildWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern DLLExport LONG FAR PASCAL _export MDIChildContainerWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern DLLExport LONG FAR PASCAL _export ProjectListWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern BOOL FAR CreateChildWindowsInMDI (LPSTR Title, int AnzChilds, LPWNDDEF ChildArray, LONG ExitProc, HMENU hMenu);
