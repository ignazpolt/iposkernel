//////////////////////////////////////////////////////////
//  Clipboard - Viewer fuer den Dos - Switch
//////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/rev/dswtch.cpv   1.15   02 May 2000 15:19:00   Hannes  $
//  $Log:   F:/marille/clinicum/rev/dswtch.cpv  $
// 
//    Rev 1.15   02 May 2000 15:19:00   Hannes
// Korrektes Abfragen des HIDE - Flags
// 
//    Rev 1.14   06 Apr 2000 09:29:40   Hannes
// 
//    Rev 1.13   25 Apr 1999 19:03:30   Martin
// optionaler Parameter hWnd bei TaskExist
// 
//    Rev 1.12   05 Oct 1998 11:53:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   08 Jun 1998 16:57:32   Wolfgang
// 1.) OnDrawClipboard-Parameter ver32bittet.
// 
//    Rev 1.10   12 Nov 1997 16:34:28   Martin
// OnAppActivation korrigiert, ActivateApp fuer 32 Bit funktionsfaehig gemacht
// 
//    Rev 1.9   13 Feb 1997 11:57:10   martin
// EnumTaskWindows -> EnumWindows
// 
//    Rev 1.8   04 Nov 1996 21:19:16   MARTIN
// TaskExist erweitert um optionale Parameter
// 
//    Rev 1.7   25 Jul 1996 19:49:14   GERHOLD
// #pragma pack(1)
// 
//    Rev 1.6   03 Jul 1996 15:43:26   GERHOLD
// BOOL FAR *  =>  DBBOOL FAR *
// 
//    Rev 1.5   22 May 1996 10:24:54   MARTIN
// 9 Stunden - Absturz
// 
//    Rev 1.4   02 Feb 1996 10:35:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:20:12   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Mar 1995 11:55:40   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 17:04:40   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.7   08 Feb 1994 17:22:16   HANNES
// Syntaxfehler von 1.6 korrigiert
// 
//    Rev 1.6   08 Feb 1994 17:03:38   HANNES
// SC_RESTORE auf SC_MAXIMIZE umgestellt
// 
//    Rev 1.5   13 Oct 1993 12:19:18   HANNES
// Strukturbereinigung
// 
//    Rev 1.4   05 Sep 1993 22:13:34   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.3   24 Aug 1993 10:34:20   HANNES
// Mehrmaliges Versuchen vom Clipboard-schreiben
// 
//    Rev 1.2   23 Aug 1993 19:30:52   HANNES
// ...
// 
//    Rev 1.1   18 Aug 1993 10:27:42   HANNES
// Erweiterungen
//
#include <windows.h>
#include <stdio.h>

#ifdef UEBERLEGT
#ifndef WIN32
#include <toolhelp.h>
#endif
#endif

#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"
#include "data.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "hooks.h"
#define MODULENUM 53
#include "winass.hpp"

#pragma pack(1)
struct ActivateApp_param {
  WORD parSize;
  DWORD nRef;     // Name der Applikation
  DWORD pRef;     // Task - Name (Klasse des Fensters)
  DWORD CheckFullCaption;  // optional: soll Caption auf volle Uebereinstimmung geprueft werden ?
  DWORD CheckClass;        // optional: soll Fensterklasse geprueft werden ?
  DWORD doShowHide;        // optional: Fenster Verstecken / Anzeigen...
  };
#pragma pack()

// Callback - Funktion, um das entsprechende Programm zu finden
#pragma pack(1)
struct EnumWndData {
  BOOL res;
  LPSTR Caption;
  LPSTR ClassName;
  HWND hWnd;
  BOOL CheckFullCaption;
  BOOL CheckClass;
  };
#pragma pack()

BOOL beginswith (LPSTR str, LPSTR partstr)
  {
  while (*partstr)
    if (*str++ != *partstr++)
      return FALSE;
  return TRUE;
  }

BOOL CALLBACK EnumTaskWndProc (HWND hWnd,LPARAM lP)
  {
  EnumWndData FAR *d = (EnumWndData FAR *) lP ;
  char Title[128];
  char ClassName[128];
  GetWindowText (hWnd,Title,sizeof(Title));
  GetClassName (hWnd,ClassName,sizeof(ClassName));
  if ((d->CheckFullCaption ?
         (lstrcmp (Title,d->Caption) == 0) :
         beginswith(Title,d->Caption)) &&
      ((!d->CheckClass) ||
       (lstrcmp (ClassName,d->ClassName) == NULL))) {
    d->res = TRUE ;
    d->hWnd = hWnd;
    return FALSE ;
    }
  else
    return TRUE ;
  }

HWND GetTaskWindow (LPSTR Caption,LPSTR Class,BOOL CaptionCheck = TRUE,BOOL ClassCheck = TRUE)
  {
  EnumWndData d;
  d.Caption = Caption;
  d.ClassName = Class;
  d.res = FALSE ;
  d.hWnd = 0;
  d.CheckFullCaption = CaptionCheck;
  d.CheckClass = ClassCheck;
  if ((d.Caption != NULL) && ((!ClassCheck) || (d.ClassName != NULL))) {
    FARPROC lpEnumProc = FARPROC (MakeProcInstance(FARPROC (EnumTaskWndProc), WBase::hInstance));
#ifdef UEBERLEGT
    TASKENTRY te;
    te.dwSize = sizeof(te);
    for ( TaskFirst (&te) ; ; ) {
      EnumTaskWindows (te.hTask,lpEnumProc,LONG(LPSTR(&d)));
      if (d.res) break ;
      te.dwSize = sizeof(te);
      if (!TaskNext (&te)) break ;
      }
#endif
    EnumWindows ((WNDENUMPROC)lpEnumProc,LONG(LPSTR(&d)));
    FreeProcInstance (lpEnumProc);
    }
  return d.hWnd;
  }

////////////////////////////////////////////////////////////
//  Suchen eines Task - Fensters und dieses aktivieren
////////////////////////////////////////////////////////////
BOOL ActivateApp (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ActivateApp_param FAR *par = (ActivateApp_param FAR *)param;
    LPSTR cp = LPSTR(c->ReadlData (par->nRef));
    LPSTR cl = LPSTR(c->ReadlData (par->pRef));
    BOOL CheckFullCaption = TRUE;
    if (par->parSize >= sizeof(ActivateApp_param) - 2 * sizeof(DWORD)) {
      DBBOOL FAR *lpCheckFullCaption = (DBBOOL FAR *)c->ReadlData(par->CheckFullCaption);
      if (lpCheckFullCaption != NULL)
        CheckFullCaption = *lpCheckFullCaption;
      else
        CheckFullCaption = FALSE;
      }
    BOOL CheckClass = TRUE;
    if (par->parSize >= sizeof(ActivateApp_param) - sizeof(DWORD)) {
      DBBOOL FAR *lpCheckClass = (DBBOOL FAR *)c->ReadlData(par->CheckClass);
      if (lpCheckClass != NULL)
        CheckClass = *lpCheckClass;
      else
        CheckClass = FALSE;
      }
    BOOL doShow = FALSE;
    BOOL doHide = FALSE;
    if (par->parSize >= sizeof(ActivateApp_param)) {
      DBBOOL FAR *lpHide = (DBBOOL FAR *)c->ReadlData(par->doShowHide);
      if (lpHide != NULL) {
        if (*lpHide) doShow = TRUE ;
        else         doHide = TRUE ;
        }
      }
      
    HWND hWnd = GetTaskWindow (cp,cl,CheckFullCaption,CheckClass);
    if ((hWnd == 0) && (cl != NULL) && (cp != NULL) && 
            (*cp == '\0') && (*cl == '\0'))
      hWnd = WBase::hFrameWin;
    if (hWnd) {
      if (doHide)      ShowWindow (hWnd,SW_HIDE);
      else if (doShow) {
        ShowWindow (hWnd,SW_MAXIMIZE);
#ifdef WIN32
        SetForegroundWindow (hWnd);
#else
        SetActiveWindow (hWnd);
#endif
        }
      else {
#ifdef WIN32
        SetForegroundWindow (hWnd);
#else
        SetActiveWindow (hWnd);
#endif
        }
      SetFocus (hWnd);
      if (hWnd != WBase::hFrameWin)
//        PostMessage (hWnd,WM_SYSCOMMAND,SC_RESTORE,0L);
        PostMessage (hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0L);
      }
    else {
      MessageBeep (0);
      }
    }
  return TRUE ;
  }


////////////////////////////////////////////////////////////
//  Schreiben eines Clipboard - Strings
////////////////////////////////////////////////////////////
static BOOL StartSetClpData ()
  {
  BOOL res;
  if (res = OpenClipboard (WBase::hFrameWin))
    EmptyClipboard ();
  return res;
  }

static BOOL EndSetClpData ()
  {
  CloseClipboard ();
  return TRUE ;
  }

static BOOL SetClpData (WORD Format,LPSTR txt)
  {
  if (StartSetClpData ()) {
    // An das Clipboard die moeglichen Formate mitteilen
    GLOBALHANDLE hGtxt = GlobalAlloc (GMEM_MOVEABLE | GMEM_LOWER,GetBlockSize(txt));
    LPSTR buffer = (LPSTR)GlobalLock (hGtxt);
    lmemcpy (buffer,txt,GetBlockSize(txt));
    SetClipboardData (CF_TEXT,hGtxt);
    EndSetClpData ();
    return TRUE ;
    }
  return FALSE ;
  }

#pragma pack(1)
struct WriteClpBoard_param {
  WORD parSize;
  DWORD rFormat;
  DWORD txt;
  };
#pragma pack()

#define MAXTRYS 100
BOOL WriteClpBoard (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteClpBoard_param FAR *par = (WriteClpBoard_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    BOOL done = FALSE ;
    if (txt != NULL) {
      for ( int i = 0 ; i < MAXTRYS ; i++) {
        if (done = SetClpData (c->ReadConstInt(par->rFormat),txt)) break ;
        }
      if (!done) {
        for (int i = 0 ; i < 20 ; i++)
          MessageBeep (0);
        }
      }
    }
  return FALSE ;
  }


////////////////////////////////////////////////////////////////////////
//  Installieren eines Observers
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct InstallClpObserver_param {
  WORD parSize;
  mdiChild *c;    // Fuer den Proceduraufruf im Erfolgsfall
  DWORD rFormat;
  DWORD rString;
  DWORD fString;
  DWORD procOffset;
  };
#pragma pack()

static InstallClpObserver_param FAR *_ico_param;
static HWND hNextViewer;
GLOBALHANDLE GetClpData (UINT FAR *PrioList,WORD *pFormat,HWND hWnd)
  {
  GLOBALHANDLE res = NULL;
  if ((hWnd) &&
       (OpenClipboard (hWnd) != 0)) {
    *pFormat = GetPriorityClipboardFormat (PrioList,1) ;
    if (*pFormat == WORD(_ico_param->c->ReadConstInt (_ico_param->rFormat))) {
      GLOBALHANDLE hGClp = GetClipboardData (*pFormat);
      // Anlegen einer Kopie
      res = GlobalAlloc (GHND,GlobalSize(hGClp));
      LPSTR lpdest = (LPSTR)GlobalLock (res);
      LPSTR lpsource = (LPSTR)GlobalLock (hGClp);
      lstrcpy (lpdest,lpsource);
      GlobalUnlock (hGClp);
      GlobalUnlock (res);
      }
    CloseClipboard ();
    }
  return res;
  }

static LPSTR IsFormatCorrect (LPSTR txt, LPSTR fstr)
  {
  for ( ; ((*fstr) && (*txt) && (*txt == *fstr)) ; )
    fstr ++ , txt ++ ;
  return (*fstr) ? NULL : txt ;
  }

static BOOL TestClpContent (HWND hWnd)
  {
  BOOL res;
  UINT PrioList = _ico_param->c->ReadConstInt (_ico_param->rFormat);
  WORD wFormat;
  GLOBALHANDLE hGtxt ;
  if ((hGtxt = GetClpData (&PrioList,&wFormat,hWnd)) != 0) {
    LPSTR txt = LPSTR (GlobalLock (hGtxt));
    LPSTR fstr = LPSTR (_ico_param->c->ReadlData (_ico_param->fString));
    if ((txt = IsFormatCorrect(txt,fstr)) != NULL) {
      _ico_param->c->WritelData (_ico_param->rString,txt,lstrlen(txt)+1,LPSTR(_ico_param)-sizeof(WORD));
      _ico_param->c->ExCuteProc (_ico_param->procOffset,EM_LOAD);
      }
    GlobalUnlock (hGtxt);
    GlobalFree (hGtxt);
    }
  else res = FALSE ;

  return res;
  }

void OnDrawClipboard (HWND hWnd,WPARAM wParam,LPARAM lParam)
  {
  // Inhalt des Clipboards ueberpruefen
  if (_ico_param != NULL) {
    if (hNextViewer)
      SendMessage (hNextViewer,WM_DRAWCLIPBOARD,wParam,lParam);
    TestClpContent (hWnd);
    }
  }

static BOOL InstallObserver ()
  {
  BOOL res;
  hNextViewer = SetClipboardViewer (WBase::hFrameWin);
  res = TestClpContent (WBase::hFrameWin);

  return res;
  }

static void RemoveObserver ()
  {
  ChangeClipboardChain (WBase::hFrameWin,hNextViewer);
  hNextViewer = NULL;
  }

BOOL InstallClpObserver (mdiChild *c,LPVOID param,WORD mode)
  {
  if ((mode & EM_LOAD) && (_ico_param == NULL)) {
    _ico_param = (InstallClpObserver_param FAR *) param;
    _ico_param->c = c;
    InstallObserver ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    _ico_param = NULL;
    RemoveObserver ();
    }
  return FALSE ;
  }

BOOL RemoveObserver (mdiChild *c,LPVOID param,WORD mode)
  {
  if ((mode & EM_LOAD) && (_ico_param != NULL)) {
    _ico_param = NULL;
    RemoveObserver ();
    }
  return FALSE ;
  }

//////////////////////////////////////////////////////
//  Verhindern der illegalen Aktivierung
//////////////////////////////////////////////////////
#pragma pack(1)
struct AvoidActivation_param {
  WORD parSize;
  DWORD caption;
  DWORD classname;
  DWORD rstate;
  };
#pragma pack()

BOOL AvoidActivation (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AvoidActivation_param FAR *par = (AvoidActivation_param FAR *) param;
    LPSTR cp = LPSTR(c->ReadlData (par->caption));
    LPSTR cl = LPSTR(c->ReadlData (par->classname));
    HWND hWnd = GetTaskWindow (cp,cl);
    if ((hWnd == 0) && (cl != NULL) && (cp != NULL) && 
            (*cp == '\0') && (*cl == '\0'))
      hWnd = WBase::hFrameWin;    // Selber deaktivieren / aktivieren
    if (hWnd)
      AvoidActivation (hWnd,c->ReadConstInt (par->rstate));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AvoidActivation_param FAR *par = (AvoidActivation_param FAR *) param;
    LPSTR cp = LPSTR(c->ReadlData (par->caption));
    LPSTR cl = LPSTR(c->ReadlData (par->classname));
    HWND hWnd = GetTaskWindow (cp,cl);
    if ((hWnd == 0) && (cl != NULL) && (cp != NULL) && 
            (*cp == '\0') && (*cl == '\0'))
      hWnd = WBase::hFrameWin;    // Selber deaktivieren / aktivieren
    if (hWnd)
      AvoidActivation (hWnd,DONTAVOID);
    }
  return FALSE ;
  }

#pragma pack(1)
struct TaskExist_param {
  WORD parSize;
  DWORD res;
  DWORD caption;
  DWORD classname;
  DWORD CheckFullCaption;  // optional: soll Caption auf volle Uebereinstimmung geprueft werden ?
  DWORD CheckClass;        // optional: soll Fensterklasse geprueft werden ?
  DWORD hWnd;
  };
#pragma pack()

BOOL TaskExist (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    TaskExist_param FAR *par = (TaskExist_param FAR *) param;
    LPSTR cp = LPSTR(c->ReadlData (par->caption));
    LPSTR cl = LPSTR(c->ReadlData (par->classname));
    BOOL CheckFullCaption = TRUE;
    if (par->parSize >= sizeof(TaskExist_param) - (2 * sizeof(DWORD))) {
      DBBOOL FAR *lpCheckFullCaption = (DBBOOL FAR *)c->ReadlData(par->CheckFullCaption);
      if (lpCheckFullCaption != NULL)
        CheckFullCaption = *lpCheckFullCaption;
      else
        CheckFullCaption = FALSE;
      }
    BOOL CheckClass = TRUE;
    if (par->parSize >= (sizeof(TaskExist_param) - sizeof(DWORD))) {
      DBBOOL FAR *lpCheckClass = (DBBOOL FAR *)c->ReadlData(par->CheckClass);
      if (lpCheckClass != NULL)
        CheckClass = *lpCheckClass;
      else
        CheckClass = FALSE;
      }
    HWND hWnd = GetTaskWindow (cp,cl,CheckFullCaption,CheckClass);
    if (hWnd) {
      BOOL res = TRUE ;
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    if (par->parSize >= sizeof(TaskExist_param)) {
      if (hWnd)
        c->WritelData (par->hWnd,&hWnd,sizeof(HWND),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->hWnd,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct OnTaskDestroy_param {
  WORD parSize;
  DWORD caption;
  DWORD classname;
  };
#pragma pack()

BOOL OnTaskDestroy (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    OnTaskDestroy_param FAR *par = (OnTaskDestroy_param FAR *) param;
    LPSTR cp = LPSTR(c->ReadlData (par->caption));
    LPSTR cl = LPSTR(c->ReadlData (par->classname));
    HWND hWnd = GetTaskWindow (cp,cl);
    InstallDestroyServer (hWnd,TRUE,WBase::hFrameWin);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    InstallDestroyServer (0,FALSE,0);
    }
  return FALSE ;
  }

#pragma pack(1)
struct StartTask_param {
  WORD parSize;
  DWORD modName;
  DWORD rshMode;
  };
#pragma pack()

BOOL StartTask (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    StartTask_param FAR *par = (StartTask_param FAR *) param;
    LPSTR Module = LPSTR (c->ReadlData (par->modName));
    WinExec (Module,c->ReadConstInt (par->rshMode));
    }
  return FALSE ;
  }

#pragma pack(1)
struct WatchCreation_param {
  WORD parSize;
  DWORD caption;
  DWORD classname;
  };
#pragma pack()

BOOL WatchCreation (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WatchCreation_param FAR *par = (WatchCreation_param FAR *) param;
    LPSTR cp = LPSTR(c->ReadlData (par->caption));
    LPSTR cl = LPSTR(c->ReadlData (par->classname));
    WatchCreate (TRUE,cp,cl,WBase::hFrameWin);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WatchCreate (FALSE,NULL,NULL,0);
    }
  return FALSE ;
  }

#pragma pack(1)
struct OnActivation_param {
  WORD parSize;
  DWORD procOffset;
  };
#pragma pack()

static DWORD doCallOnActivation;
static mdiChild *COAmdiChild;

BOOL OnActivation (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    OnActivation_param FAR *par = (OnActivation_param FAR *) param;
    DBWIN_ASSERT (doCallOnActivation == 0L);
    doCallOnActivation = par->procOffset;
    COAmdiChild = c;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    doCallOnActivation = 0L;
    }
  return FALSE ;
  }

#ifdef UEBERLEGT
int AnzActivationsTrys;
#endif
void FrameIsActivated ()
  {
  if (doCallOnActivation != 0) {
    COAmdiChild->ExCuteProc (doCallOnActivation,EM_LOAD | EM_CHANGETOTRUE);
    COAmdiChild->ExCuteProc (doCallOnActivation,EM_RESET);
#ifdef UEBERLEGT
    AnzActivationsTrys = 4;
#endif
    }
  }

void TestActivationMore ()
  {
#ifdef UEBERLEGT
  if (AnzActivationsTrys > 0) {
    AnzActivationsTrys--;
    if (doCallOnActivation != 0) {
      COAmdiChild->ExCuteProc (doCallOnActivation,EM_LOAD | EM_CHANGETOTRUE);
      COAmdiChild->ExCuteProc (doCallOnActivation,EM_RESET);
      }
    }
#endif
  }

