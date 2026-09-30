/*
 *
 *  MODULE   : BlandIni.c
 *
 *  PURPOSE  : Contains initialization code for BlandMDI.
 *
 *  FUNCTIONS:
 *
 *      InitializeApplication() - Sets up Class data structure
 *                                and registers window class.
 *
 *      InitializeInstance ()   - Does a per-instance initialization
 *                                of BlandMDI. Creates the "frame"
 *                                and MDI client.
 *
 *      MakeNewChild ()         - Creates a new MDI child window
 *
 */
// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.

/*------------------------  #includes  --------------------------------*/
#include <windows.h>
#include <stdio.h>        // wegen size_t in GlobMem
#include "dds32.h"

#include "restool.hpp"
#include "rlist.hpp"

#include "BlandMDI.h"
#include "BlandMDI.hpp"

#include "msdntb.h"

#include "statbar.hpp"

#include "globmem.h"      // wegen new in DRDROP
#include "drdrop.hpp"

/*------------------------  global variables  -------------------------*/

char szFrame[] = "BLANDFRAME";   // Class name for "frame" window

char szChild[] = "bland child";   // Class name for MDI window
char szChildContainer[] = "ChildContainer";

FARPROC lpfnSubClassProc;
FARPROC lpfnOldWndProc;

BOOL IsEditorWindow (HWND hWnd)
  {
  char cl1[32];
  GetClassName (hWnd,cl1,sizeof(cl1));
  return (lstrcmp (cl1,szChild) == 0);
  }

/*--------------------- InitializeApplication  -------------------------*/
/*
 *
 *  FUNCTION   : InitializeApplication ()
 *
 *  PURPOSE    : Sets up the class data structures and does a one-time
 *               initialization of the app by registering the window classes
 *
 *  RETURNS    : TRUE  - If RegisterClass() was successful for both classes.
 *               FALSE - otherwise.
 *
 */


BOOL FAR PASCAL InitializeApplication ()
  {
  WNDCLASS wc;

  // Register the frame class 

  wc.style = 0;
  wc.lpfnWndProc = BlandFrameWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = MyInstance;
  wc.hIcon = LoadIcon(MyInstance, "RESTOOL");
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
#ifdef WIN32
  wc.hbrBackground = HBRUSH(COLOR_APPWORKSPACE + 1);
#else
  wc.hbrBackground = COLOR_APPWORKSPACE + 1;
#endif
  wc.lpszMenuName = "Menu";
  wc.lpszClassName = szFrame;
  if (RegisterClass(&wc)) {
    // Register the MDI child class 
    wc.lpfnWndProc = BlandMDIChildWndProc;
    wc.hIcon = LoadIcon(MyInstance, "RESCHILD");
    wc.lpszMenuName = NULL;
    wc.cbWndExtra = 2 * sizeof(LPVOID);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = szChild;
    if (RegisterClass(&wc)) {
      // Registriere das MDI-Child das mehrere Kindfenster aufnehmen kann
      wc.lpfnWndProc = MDIChildContainerWndProc;
      wc.hIcon = LoadIcon(MyInstance, "RESCHILD");
      wc.lpszMenuName = NULL;
      wc.cbWndExtra = 2 * sizeof(LPVOID);
      wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
      wc.lpszClassName = szChildContainer;
      if (RegisterClass(&wc)) {
        if (StatBar_Register(MyInstance)) {
          wc.lpfnWndProc = ProjectListWndProc;
          wc.hIcon = 0;
          wc.lpszMenuName = NULL;
          wc.cbWndExtra = sizeof(HWND);
          wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
          wc.lpszClassName = "ProjectWindow";
          if (RegisterClass(&wc))
            return TRUE;
          }
        }
      }  
    }    
  return FALSE;
  }

extern BOOL doCaseSensitive();

LPDRAGDROP ComboDrop;
//----------------------------------------------------------------------------
// Subclassing fuer die Combo-Box
//----------------------------------------------------------------------------
DLLExport LONG _export WINAPI SubClassFunc (HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
  {
  LONG res = 0;
  
  switch (Message) {
/*
    case WM_KEYDOWN:
      {
      if ((wParam == VK_UP) || (wParam == VK_DOWN)) {
        SendMessage (hWnd, CB_SHOWDROPDOWN, 1, 0);
        }
      else
        res = CallWindowProc(lpfnOldWndProc, hWnd, Message, wParam, lParam);
      }
      break;
*/
    case WM_KILLFOCUS:
      SearchCombo.OnVKReturn (hWnd, FALSE, doCaseSensitive ());
#ifdef STRICT
      res = CallWindowProc((WNDPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#else
      res = CallWindowProc((FARPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#endif
      break;
    case WM_CHAR:
      {
      switch (wParam) {
        case VK_RETURN:
          {
          SearchCombo.OnVKReturn (hWnd, FALSE, doCaseSensitive ());

          HWND hscwnd = GetScWnd();
          SendMessage (hscwnd, WM_COMMAND, MI_SEARCHMORE, 1L);
          }
          break;
        case VK_ESCAPE:
          {
          SendMessage (hWnd, WM_SETTEXT, 0, LPARAM(SearchCombo.GetTopString()));
          HWND hscwnd = GetScWnd();
          SetFocus (hscwnd);
          }
          break;
        case WM_DESTROY:
          ComboDrop->RemoveFromList ();
          break;
         
        default:  
#ifdef STRICT
          res = CallWindowProc((WNDPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#else
          res = CallWindowProc((FARPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#endif
        }
      }
      break;
/*      
    case WM_SETTEXT:
      res = CallWindowProc(lpfnOldWndProc, hWnd, Message, wParam, lParam);
      break;
*/    
/*    
    case WM_CTLCOLOR:
      switch HIWORD(lParam) {
        case CTLCOLOR_LISTBOX:
          SetTextColor (HDC(wParam), RGB(0xFF, 0xFF, 0xFF));
          SetBkColor (HDC(wParam), RGB(0xFF, 0, 0));
          return GetStockObject(LTGRAY_BRUSH);
        case CTLCOLOR_MSGBOX:
          return GetStockObject(LTGRAY_BRUSH);
        }
*/
    default:
#ifdef STRICT
      res = CallWindowProc((WNDPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#else
      res = CallWindowProc((FARPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#endif
    }

  return res;
  }


#define ANZFIELDS 3
/*----------------------  InitializeInstance  --------------------------*/
/*
 *
 *  FUNCTION   : InitializeInstance ()
 *
 *  PURPOSE    : Performs a per-instance initialization of BlandMDI. It
 *               also creates the frame and one MDI child window.
 *
 *  RETURNS    : TRUE  - If initialization was successful.
 *               FALSE - otherwise.
 *
 */


extern void DefineWacthToolbar ();
BOOL FAR PASCAL InitializeInstance (LPSTR lpCmdLine, WORD nCmdShow)
  {
  extern HWND hwndMDIClient;
  char sz[80];

  // Get the base window title

  LoadString(MyInstance, IDS_APPNAME, sz, sizeof(sz));

  hMenuMain = LoadMenu(MyInstance, (LPSTR) "MAINMENU");
  hMenuMainWindow = GetSubMenu(hMenuMain, MAINWINDOWMENU);
  hMenuDialog = LoadMenu(MyInstance, (LPSTR) "DIALOGMENU");
  hMenuDialogWindow = GetSubMenu(hMenuDialog, DIALOGWINDOWMENU);
  hMenuWndInMDI = LoadMenu(MyInstance, (LPSTR) "WNDINMDIMENU");
  hMenuWndInMDIWindow = GetSubMenu(hMenuWndInMDI, WNDINMDIMENU);

  // Create the frame 
  // MDI Client window is created in frame's WM_CREATE case
  hwndFrame = CreateWindow(szFrame, sz, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                           CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, hMenuMain,
                           MyInstance, NULL);
  
  hWndDock = CreateToolbarDockWindow (hwndFrame);
#ifdef WIN32
  HFONT hFnt = HFONT(SendMessage (hWndDock, TBD_GETCONTROLFONT, 0, 0));
#else
  HFONT hFnt = LOWORD(SendMessage (hWndDock, TBD_GETCONTROLFONT, 0, 0));
#endif

  hWndCombo = CreateWindow ("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                             CBS_DROPDOWN | CBS_HASSTRINGS, 
                            0, 0, 10, 10, hwndFrame, HMENU(ID_SEARCHCOMBO), MyInstance, NULL);
  SendMessage (hWndCombo, WM_SETFONT, WPARAM(hFnt), 1);
  SendMessage (hWndCombo, CB_SETEXTENDEDUI, TRUE, 0);
  
  ComboDrop = new Text_Drop (GetWindow(hWndCombo, GW_CHILD), hWndCombo);
  ComboDrop->AddType (DDTYPE_EDITOR);

  RECT rc;
  GetWindowRect (hWndCombo, &rc);
  DWORD ComboData = MAKELONG ((rc.bottom-rc.top), 0);

  // Installiere einen Hook fuer Dialoge, Menus, oder Message-Boxen
  /**************************************************************
  lpProcInstance = MakeProcInstance (FilterFunc, hInstance);
  if (lpProcInstance == NULL)
    return FALSE;
    
  lpFilterFunc = SetWindowsHook (WH_MSGFILTER, lpProcInstance);
  ***************************************************************/
   
  TBBUTTON tbButton[] = {
              { 9,   IDB_PROJECTFILES  ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },  // alle Dateien im Projekt
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
//              { 10,  IDB_OPENPROJECT   ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },  // Projekt oeffnen
//              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 4,   MI_OPENFORSCRIPTED,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },  // Datei oeffnen
              { 5,   MI_STOREED        ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 200, ID_SEARCHCOMBO    ,   TBSTATE_ENABLED, TBSTYLE_SEP   , ComboData, 0  },  // Suchen - Combo-Box
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 20,  MI_SEARCHUP       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 13,  MI_SEARCHMORE     ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 21,  MI_SEARCHCASE     ,   TBSTATE_ENABLED, TBSTYLE_CHECK,  0L, 0  },
              { 22,  MI_SEARCHWORD     ,   TBSTATE_ENABLED, TBSTYLE_CHECK,  0L, 0  },
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 23,  MI_GENMAKEFILE    ,   TBSTATE_ENABLED, TBSTYLE_CHECK,  0L, 0  },
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 11,  MI_SETBREAK       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 14,  MI_WATCHVAR       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 12,  MI_RUN            ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 15,  MI_STEP           ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 16,  MI_STEPINTO       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { -1,                0   ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
              { 17,  MI_TABLELIST      ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 18,  MI_GENINT         ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 19,  MI_SHOWGLOB       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              };

  TBBUTTON tbButtonDlg[] = {
              { 0,  MI_STOREDIALOG    ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },  // Dialog speichern
              { 2,  MI_WORKONSCREEN   ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },  // Dialog bearbeiten
              { 1,  MI_DESTROYDIALOG  ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },  // Dialog abbrechen
              { -1,                0  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0 },  
              { 3,  MI_WORKONELE      ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  }, // Element bearbeiten
              { 6,  MI_MOVEELEMES     ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 5,  MI_DUPLICATE      ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 4,  MI_DELELE         ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { -1,                0  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0 },  
              { 9,  MI_NEWVLINE       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 10, MI_NEWHLINE       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 12, MI_WORKONHLINE    ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { 11, MI_DELHLINE       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0  },
              { -1,                0  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0 },  
              { 13, MI_SHOWSORT       ,   TBSTATE_ENABLED, TBSTYLE_CHECK , 0L, 0  },
              { 14, MI_SHOWRASTER     ,   TBSTATE_ENABLED, TBSTYLE_CHECK,  0L, 0 }, 
              };

  TBBUTTON tbButtonForm[] = {
              { 0,  MI_PREVIEWFORM    ,   TBSTATE_ENABLED, TBSTYLE_CHECK, 0L, 0 }, 
              };
   
  hWndToolbar = CreateToolbar ("Main",hWndDock,       // Parent
                               WS_VISIBLE, 
                               CMD_TB_BASE, 
                               24,             // Anzahl der Bildchen im Bitmap
                               MyInstance, 
                               IDR_TOOLICONS, 
                               tbButton, 
                               24              // Anzahl der Knöpfe inkl. Separator
                               );
  SetParent (hWndCombo, hWndToolbar);
  SearchCombo.OnInit (hWndCombo);

  hWndToolbarDialog = CreateToolbar ("Dialog",hWndDock,       // Parent
                                     0, 
                                     CMD_TB_BASE, 
                                     15,             // Anzahl der Bildchen im Bitmap
                                     MyInstance, 
                                     IDR_DIALOG, 
                                     tbButtonDlg, 
                                     16              // Anzahl der Knöpfe inkl. Separator
                                     );
#ifdef WIN32
  SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, LPARAM(hWndToolbarDialog));
#else
  SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWndToolbarDialog, 0));
#endif

//  ShowWindow (hWndToolbarDialog, SW_HIDE);
/*
  hWndToolbarForm = CreateToolbar ("Formular", hWndDock,       // Parent
                                     0, 
                                     CMD_TB_BASE, 
                                     14,             // Anzahl der Bildchen im Bitmap
                                     MyInstance, 
                                     IDR_DIALOG, 
                                     tbButtonForm, 
                                     1              // Anzahl der Knöpfe inkl. Separator
                                     );
*/                            
  // alle Knöpfchen ein bisschen disablen, die noch nichts zu tun haben!
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, IDB_PROJECTFILES, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_STOREED, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_SEARCHMORE, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_SETBREAK, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_WATCHVAR, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_RUN, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_STEP, MAKELONG(FALSE, 0));
  SendMessage (hWndToolbar, TB_ENABLEBUTTON, MI_STEPINTO, MAKELONG(FALSE, 0));

  SendMessage (hWndToolbarDialog, TB_CHECKBUTTON, MI_SHOWRASTER, MAKELONG(IsRasterEnabled(), 0));

  DefineWacthToolbar ();

  // Liste aller Dateien zu einem Projekt
  hWndProjectList = CreateWindow ("ProjectWindow", NULL, 
                                   WS_POPUP | WS_BORDER | WS_CLIPCHILDREN,
                                   0, 0, 10, 10, hwndMDIClient, 
                                   NULL, MyInstance, NULL);

  hWndStatusbar = CreateWindow ("STATBAR1",
                                NULL, 
                                WS_CHILD | WS_VISIBLE | 
                                WS_CLIPSIBLINGS,
                                0, 0, 0, 0,
                                hwndFrame,
                                NULL,
                                MyInstance,
                                NULL);

  // GetClientRect (hwndFrame, &rc); Wegen spaeterem Maximize etc. funktioniert das leider nicht,
  int w = GetSystemMetrics (SM_CXSCREEN); // daher direkt ueber Bildschirmbreite
  
  int FieldArray[ANZFIELDS];
  // FieldArray[0] = rc.right-rc.left-8; Wegen spaeterem Maximize etc. funktioniert das leider nicht
  FieldArray[0] = w-8;
  FieldArray[1] = FieldArray[0]-50;
  FieldArray[2] = FieldArray[1]-50;
  SendMessage (hWndStatusbar, SB_SETPARTS, WORD(ANZFIELDS), (LONG)(int FAR *)FieldArray);

  // Subclassing fuer die COMBO-Box
  lpfnSubClassProc = MakeProcInstance((FARPROC)SubClassFunc, MyInstance);
  lpfnOldWndProc = (FARPROC)SetWindowLong(GetWindow(hWndCombo, GW_CHILD), GWL_WNDPROC, 
                                (LONG)lpfnSubClassProc);

#ifdef TEST
  #define ANZCHILDS  3
  WndDef ChildWindows[ANZCHILDS];
  
  ChildWindows[0].x0 = 0;
  ChildWindows[0].y0 = 0;
  ChildWindows[0].x1 = 500;
  ChildWindows[0].y1 = 1000;

  ChildWindows[1].x0 = 500;
  ChildWindows[1].y0 = 0;
  ChildWindows[1].x1 = 1000;
  ChildWindows[1].y1 = 500;

  ChildWindows[2].x0 = 500;
  ChildWindows[2].y0 = 500;
  ChildWindows[2].x1 = 1000;
  ChildWindows[2].y1 = 1000;
  
  CreateChildWindowsInMDI ("Titel", ANZCHILDS, LPWNDDEF(&ChildWindows), NULL);
#endif

  if (hwndFrame && hwndMDIClient) {
    // Display the frame window 
    ShowWindow(hwndFrame, SW_SHOWMAXIMIZED);
    UpdateWindow(hwndFrame);
    return TRUE;
    }

  return FALSE;
  }


//------------------------------  MakeNewChild  ------------------------------
//
//
//  FUNCTION   : MakeNewChild (lpName)
//
//  PURPOSE    : Creates a new MDI child window.
//
//  RETURNS    : HWND  - A handle to the new window.
//----------------------------------------------------------------------------
extern HWND GetEditorMDI ();
HWND GetContainerMDI ()
  {
#ifdef WIN32
  HWND hWnd = HWND(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L));
#else
  HWND hWnd = HWND(LOWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
  if (IsWindow(hWnd)) {
    char szClassName[64];

    GetClassName (hWnd, szClassName, sizeof(szClassName));
    if (lstrcmp(szClassName, szChildContainer) != 0)
      hWnd = 0;
    }

  return hWnd;
  }

HWND FAR PASCAL MakeNewChild (LPSTR pName)
  {
  HWND hwnd;
  char sz[160];
  MDICREATESTRUCT mcs;

  if (!pName) {
   // pName parameter is NULL -- load the "Untitled" string 
   // from STRINGTABLE
    LoadString(MyInstance, IDS_UNTITLED, sz, sizeof(sz));
    mcs.szTitle = (LPSTR)sz;
    }
  else {
    mcs.szTitle = (LPSTR)pName; /* Fully qualified pathname*/
    }

  mcs.szClass = szChild;
  mcs.hOwner = MyInstance;
  mcs.x = mcs.cx = CW_USEDEFAULT;  // Use the default size for the window
  mcs.y = mcs.cy = CW_USEDEFAULT;
  mcs.style = styleDefault | WS_MAXIMIZE;

  // Sicherheitshalber das menu neu setzen
  if (GetMenu (hwndFrame) != hMenuMain) {
#ifdef WIN32
    SendMessage (hwndMDIClient, WM_MDISETMENU, 
                 (WPARAM)hMenuMain, (LPARAM)hMenuMainWindow);
#else
    SendMessage (hwndMDIClient, WM_MDISETMENU, 0, MAKELONG(hMenuMain, hMenuMainWindow));
#endif
    DrawMenuBar (hwndFrame);  
    }

  // ist bereits ein Fenster offen aber nicht maximiert, so wird das
  // neue Fenster ebenfalls nicht maximiert dargestellt.
  HWND hScWnd = GetEditorMDI();
  if (!IsWindow(hScWnd)) 
    hScWnd = GetContainerMDI();

  if (IsWindow(hScWnd)) {
    if (!IsZoomed(hScWnd))
      mcs.style &= ~WS_MAXIMIZE;   
    }

#ifdef WIN32
  hwnd = (HWND)SendMessage(hwndMDIClient, WM_MDICREATE, 0, LPARAM((LPMDICREATESTRUCT)&mcs));
#else
  hwnd = (WORD)SendMessage(hwndMDIClient, WM_MDICREATE, 0, LPARAM((LPMDICREATESTRUCT)&mcs));
#endif
  
  return hwnd;
  }

//----------------------  MakeNewChildContainer  ---------------------
//
// verantwortlich fuer die Verwaltung von mehreren Kindfenstern
// !!!!!!!Darf nicht wie MakeNewChild aufgerufen werden!!!!!!!!!!!!!!!
//--------------------------------------------------------------------
HWND FAR PASCAL MakeNewChildContainer (LPSTR pName)
  {
  HWND hwnd;
  MDICREATESTRUCT mcs;

  if (pName != NULL)
    mcs.szTitle = (LPSTR)pName; /* Fully qualified pathname*/
    
  mcs.szClass = szChildContainer;
  mcs.hOwner = MyInstance;
  mcs.x = mcs.cx = CW_USEDEFAULT;  // Use the default size for the window
  mcs.y = mcs.cy = CW_USEDEFAULT;
  mcs.style = styleDefault | WS_MAXIMIZE;   // Set the style DWORD of the window
                                   // to default
                                   // tell the MDI Client to create the child 
  HWND hScWnd = GetEditorMDI();
  if (!IsWindow(hScWnd)) 
    hScWnd = GetContainerMDI();

  if (IsWindow(hScWnd)) {
    if (!IsZoomed(hScWnd))
      mcs.style &= ~WS_MAXIMIZE;   
    }

#ifdef WIN32
  hwnd = (HWND)SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
#else
  hwnd = (WORD)SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
#endif

  ShowWindow(hwnd, SW_SHOW);
  return hwnd;
  }
