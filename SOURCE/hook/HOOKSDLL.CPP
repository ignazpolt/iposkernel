//---------------------------------------------------------------------------
//  Mousehook, um eine Meldung fuer Verlassen der Mouse des Fensters
//  zu generieren.
//
//  Abgeschrieben von Windows hooks Sample Application
//
//---------------------------------------------------------------------------

#include <windows.h>

#ifdef UEBERLEGT
#ifndef WIN32
  #include <toolhelp.h>
#endif
#endif

#include "dds32.h"

#include "hooks.h"
#include "ddsmsg.h"


//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

#ifndef WIN32
extern "C" {
int   WINAPI LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine);
  }
int   WINAPI WEP (int bSystemExit);
#endif

DLLExport int   _export WINAPI MouseFunc (int nCode, WORD wParam, DWORD lParam );

#ifdef WIN32
  DLLExport LRESULT CALLBACK CBTFunc (int nCode, WPARAM wParam, LPARAM lParam );
#else
  DLLExport int   _export WINAPI CBTFunc (int nCode, WORD wParam, DWORD lParam );
#endif

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------

HINSTANCE	hInstance;		// Global instance handle for  DLL
int	InitCalled = 0; 	// Has the Init function been called ?
//
//  My Hook States
//
int HookStates[NUMOFHOOKS] = { 0,0,0,0,0,0,0,0,0 } ; // State Table of my hooks

//
//  Hook Codes
//
int HookCodes[NUMOFHOOKS] = {
			       WH_CALLWNDPROC,
			       WH_CBT,
			       WH_GETMESSAGE,
			       WH_JOURNALPLAYBACK,
			       WH_JOURNALRECORD,
			       WH_KEYBOARD,
			       WH_MOUSE,
			       WH_MSGFILTER,
			       WH_SYSMSGFILTER
			    };

//
// Filter Function Addresses
//
FARPROC lpfnHookProcs[NUMOFHOOKS] = {
				      NULL,
              (FARPROC) CBTFunc,
				      NULL,
				      NULL,
				      NULL,
				      NULL,
				      (FARPROC) MouseFunc,
				      NULL,
				      NULL,
				    };

//
// Hook Handles
//
HHOOK hhookHooks[NUMOFHOOKS];

//---------------------------------------------------------------------------
// LibMain
//---------------------------------------------------------------------------
//extern "C" {
//int FAR PASCAL LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine)
//  {
//  hInstance = hModule;
//  return 1;
//  }
//
//}
//#pragma alloc_text(FIXEDSEG, WEP)

//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
//int FAR PASCAL WEP (int bSystemExit)
//  {
//  return(1);
//  }
//---------------------------------------------------------------------------
// InstallSysMsgFilter
//
// Install / Remove Filter function for the WH_SYSMSGFILTER
//
//---------------------------------------------------------------------------
DLLExport void _export WINAPI InstallFilter (int nHookIndex, int nCode )
  {
  if ( nCode ) {
    if (!HookStates[nHookIndex]) {
      hhookHooks[nHookIndex] =
         SetWindowsHookEx(HookCodes[nHookIndex], (HOOKPROC) lpfnHookProcs[nHookIndex], hInstance,NULL);
      HookStates[nHookIndex] = TRUE;
      }
    }
  else {
    if (HookStates[nHookIndex]) {
      UnhookWindowsHookEx(hhookHooks[nHookIndex]);
      HookStates[nHookIndex] = FALSE;
      }
    }
  }


//---------------------------------------------------------------------------
// MouseFunc
//
// Filter function for the WH_MOUSE
//
//---------------------------------------------------------------------------
#define MAXWNDS 25

class FAR WndList {
 public :
  HWND hWndToCheck[MAXWNDS];
  BOOL LastMsgInWnd[MAXWNDS];
  int AnzWnds;

  BOOL IsWindowHooked (HWND hWnd);
  void InsertWindowToHook (HWND hWnd);
  void RemoveWindowFromHook (HWND hWnd);
  BOOL IsWindowCorrect(int i);
  };
WndList MFWnd,CBTWnd;

BOOL WndList::IsWindowHooked (HWND hWnd)
  {
  for (int i = 0 ; i < AnzWnds ; i++)
    if (hWndToCheck[i] == hWnd) return TRUE ;
  return FALSE ;
  }

void WndList::InsertWindowToHook (HWND hWnd)
  {
  if (!IsWindowHooked(hWnd)) {
    hWndToCheck[AnzWnds] = hWnd ;
    LastMsgInWnd[AnzWnds] = FALSE ;
    }
  AnzWnds ++;
  }

void WndList::RemoveWindowFromHook (HWND hWnd)
  {
  BOOL found = FALSE ;
  for (int i = 0 ; i < AnzWnds ; i++) {
    if (hWndToCheck[i] == hWnd) {
      found = TRUE ;
      AnzWnds -- ;
      }
    if ((found) && (i < AnzWnds)) {
      hWndToCheck[i] = hWndToCheck[i+1];
      LastMsgInWnd[i] = LastMsgInWnd[i+1];
      }
    }
  }

BOOL WndList::IsWindowCorrect(int i) 
  {
  if (IsWindow (hWndToCheck[i])) return TRUE ;
  else {
    RemoveWindowFromHook (hWndToCheck[i]);
    return FALSE ;
    }
  }

DLLExport void _export WINAPI CheckWindow (HWND hWnd,BOOL On_Off)
  {
  // Installieren der Hookfunktion
  InstallFilter (MOUSEINDEX,On_Off);
  if (On_Off)
    MFWnd.InsertWindowToHook (hWnd);
  else
    MFWnd.RemoveWindowFromHook (hWnd);
  }

DLLExport void _export WINAPI AvoidActivation (HWND hWnd,int state)
  {
  InstallFilter (CBTINDEX,TRUE);    // Filter auf jeden Fall erst am Ende
                                    // ausschalten
  if (state == DONTAVOID)
    CBTWnd.RemoveWindowFromHook (hWnd);
  else
    CBTWnd.InsertWindowToHook (hWnd);
  }

DLLExport int _export WINAPI MouseFunc (int nCode, WORD wParam, DWORD lParam )
  {
  LPMOUSEHOOKSTRUCT MouseHookParam;

  if ( nCode >= 0 ) {
    MouseHookParam = (MOUSEHOOKSTRUCT FAR *) lParam;
    for (int i = 0 ; i < MFWnd.AnzWnds ; ) {
      if ((MFWnd.LastMsgInWnd[i]) && 
                ((MouseHookParam->hwnd != MFWnd.hWndToCheck[i]) || 
                 (MouseHookParam->wHitTestCode != HTCLIENT))) {
        if (MFWnd.IsWindowCorrect(i)) {
          PostMessage (MFWnd.hWndToCheck[i],WMU_MOUSEOUTOFWND,0,0L);
          MFWnd.LastMsgInWnd[i] = FALSE ;
          i++;
          }
        }
      else if ((!MFWnd.LastMsgInWnd[i]) && 
                  ((MouseHookParam->hwnd == MFWnd.hWndToCheck[i]) &&
                   (MouseHookParam->wHitTestCode == HTCLIENT))) {
        if (MFWnd.IsWindowCorrect(i)) {
          PostMessage (MFWnd.hWndToCheck[i],WMU_MOUSEINWND,0,0L);
          MFWnd.LastMsgInWnd[i] = TRUE ;
          i++;
          }
        }
      else
        i++;
      }
    }

  return( (int)CallNextHookEx(hhookHooks[MOUSEINDEX], nCode, wParam, lParam));
  }

//////////////////////////////////////////////////////////////////////
//  CBT - Filter
//////////////////////////////////////////////////////////////////////
static HWND WatchDestroyWnd,hAvoidWnd;
DLLExport void _export WINAPI InstallDestroyServer (HWND hWnd,BOOL state,HWND hAWnd)
  {
  if (state)
    WatchDestroyWnd = hWnd;
  else
    WatchDestroyWnd = 0;
  hAvoidWnd = hAWnd;
  if (WatchDestroyWnd != 0)
    InstallFilter (CBTINDEX,TRUE);
  }

static char c_Caption[256];
static char c_Classname[64];
static HWND hAvoidActivation;
static BOOL do_WatchCreate;
DLLExport void _export WINAPI WatchCreate (BOOL state,LPSTR Caption,LPSTR ClassName,HWND hMyWnd)
  {
  if (Caption != NULL)
    lstrcpy (c_Caption,Caption);
  if (ClassName != NULL)
    lstrcpy (c_Classname,ClassName);
  hAvoidActivation = hMyWnd;
  do_WatchCreate = state;
  if (do_WatchCreate)
    InstallFilter (CBTINDEX,TRUE);
  }

///////////////////////////////////////////////
//  Zaehlen der Fenster mit diesem Namen...
///////////////////////////////////////////////
struct EnumWndData {
  LPSTR Caption;
  LPSTR ClassName;
  int count;
  };

BOOL CALLBACK EnumTaskWndProc (HWND hWnd,LPARAM lP)
  {
  EnumWndData FAR *d = (EnumWndData FAR *) lP ;
  char Title[128];
  char ClassName[128];
  GetWindowText (hWnd,Title,sizeof(Title));
  GetClassName (hWnd,ClassName,sizeof(ClassName));
  if ((lstrcmp (Title,d->Caption) == 0) &&
      (lstrcmp (ClassName,d->ClassName) == NULL))
    d->count ++ ;
  return TRUE ;
  }

int CountTaskWnds ()
  {
  EnumWndData d;
  d.Caption = c_Caption;
  d.ClassName = c_Classname;
  d.count = 0;
#ifdef UEBERLEGT
  TASKENTRY te;
  te.dwSize = sizeof(te);
  for ( TaskFirst (&te) ; ; ) {
    EnumTaskWindows (te.hTask,FARPROC(EnumTaskWndProc),LONG(LPSTR(&d)));
    te.dwSize = sizeof(te);
    if (!TaskNext (&te)) break ;
    }
#endif
  EnumWindows (WNDENUMPROC(EnumTaskWndProc),LONG(LPSTR(&d)));
  return d.count;
  }

//---------------------------------------------------------------------------
//
// CBTFunc
//
//---------------------------------------------------------------------------
#ifdef WIN32
DLLExport LRESULT CALLBACK CBTFunc (int nCode, WPARAM wParam, LPARAM lParam )
#else
DLLExport int _export WINAPI CBTFunc (int nCode, WORD wParam, DWORD lParam )
#endif
  {
  int res = 0;
  switch (nCode) {
    case HCBT_ACTIVATE :
      {
      CBTACTIVATESTRUCT FAR *Active = (CBTACTIVATESTRUCT FAR *) lParam;
      if (CBTWnd.IsWindowHooked (HWND(wParam))) 
        res = 1;
      }
      break ;
    case HCBT_CREATEWND :
      {
      CBT_CREATEWND FAR *cw = (CBT_CREATEWND FAR *) lParam;
      if ((do_WatchCreate) &&
          (cw->lpcs->lpszName != NULL) &&
          (lstrcmp (LPSTR (cw->lpcs->lpszName),c_Caption) == 0) &&
          (cw->lpcs->lpszClass != NULL) &&
          (lstrcmp (LPSTR (cw->lpcs->lpszClass),c_Classname) == 0)) {
        // Nachzaehlen, wieviele es schon gibt
        if (CountTaskWnds () == 0) {
          // Keins da -> darf gestartet werden, aber Marille muss
          // darf nicht aktiviert werden
          AvoidActivation (hAvoidActivation,DOAVOID);
          }
        else {
          res = 1;
          MessageBeep (0);
          }
        }
      }
      break ;
    case HCBT_DESTROYWND :
      if ((HWND(wParam) == WatchDestroyWnd) && (hAvoidWnd != NULL))
        AvoidActivation (hAvoidWnd,DONTAVOID);
      break ;
    }
  if (res == 0)
    res = int (CallNextHookEx(hhookHooks[CBTINDEX],nCode,wParam,lParam));
  return res;
  }



//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
  {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hInstance = hModule;
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      {
      InstallFilter (MOUSEINDEX,FALSE);   // sicher ist sicher
      InstallFilter (CBTINDEX,FALSE);
      }
      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
extern "C" {
int WINAPI LibMain (HANDLE hModule,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  hInstance = hModule;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1;
  }
}

int WINAPI WEP (int bSystemExit)
  {
  InstallFilter (MOUSEINDEX,FALSE);   // sicher ist sicher
  InstallFilter (CBTINDEX,FALSE);
  return(1);
  }
#endif


