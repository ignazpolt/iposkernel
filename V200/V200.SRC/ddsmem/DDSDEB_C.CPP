/*-----< Debuggerunterstuetzung im Hauptprogramm >-------*/
//
//  $Header:   P:/marille/clinicum/ddsmem/rev/ddsdeb_c.cpv   1.15   07 Jun 2000 10:37:28   Wolfgang  $
//  $Log:   P:/marille/clinicum/ddsmem/rev/ddsdeb_c.cpv  $
// 
//    Rev 1.15   07 Jun 2000 10:37:28   Wolfgang
// 1.) LogMapView ueber DEBUGMAPVIEW einschaltbar.
// 2.) BringWindowToTop und SetForeGroundWindow wieder rein, von wegen doppelt 
//     haelt besser (GetFocus etc.). (WIEDER AUSKOMMENTIERT!)
// 3.) Exceptions in Debug-Kommunikation fuehren nicht mehr zu Endlosschleife,
//     sondern zu "normaler" Exception.
// 
//    Rev 1.14   17 May 2000 18:27:32   Wolfgang
// 1.) DDS macht jetzt SetForegroundWindow fuer Rstool (NT2000).
// 2.) WIN32 entfernt.
// 
//    Rev 1.13   09 Mar 1999 17:04:40   Wolfgang
// 1.) Auch Fehler die im RESTOOL angezeigt werden, werden mitgeloggt.
// 
//    Rev 1.12   05 Oct 1998 11:10:06   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   10 Jul 1998 10:41:54   Gerhold
// Setforegroundwindow auskommentiert bei WMC_DOSTEP, WMC_DOSTEPINTO
// Da gab es Probleme unter Windows 95 mit der ShowQuickWatch
// 
//    Rev 1.10   19 May 1998 16:19:52   Martin
// Exception() Exception - frei gemacht
// 
//    Rev 1.9   17 Dec 1997 12:09:08   Gerhold
// void GetData (LPVOID data, ...) ... kein Rueckgabewert
// 
//    Rev 1.8   21 Nov 1997 15:55:10   Hannes
// Feinschliff Debugger
// 
//    Rev 1.7   19 Nov 1997 18:49:16   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.6   05 May 1997 11:37:14   Hannes
// GlobalUnlock
// 
//    Rev 1.5   30 Apr 1997 10:47:06   Hannes
// 
//    Rev 1.4   19 Feb 1997 12:07:22   Hannes
// Scriptfunktionen -> Erweiterung um die Funktionsadresse
// 
//    Rev 1.3   21 Oct 1996 18:52:18   HANNES
// Erweiterte Debuggerkommandos
// 
//    Rev 1.2   04 Feb 1996 15:25:20   GERHOLD
// 
//    Rev 1.1   02 Feb 1996 10:41:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Aug 1995 00:13:10   HANNES
// Initial revision.
//

//define DEBUGMAPVIEW

#include <windows.h>
#include <stdio.h>
#ifdef DEBUGMAPVIEW
#include <dos.h>
#endif

#include <tlhelp32.h>

#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"

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

#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "scdb.hpp"
#include "communic.hpp"

#define MODULENUM  145
#include "winass.hpp"

BOOL BlockIsActive ;


#ifdef DEBUG
#define SHAREMEM
#endif

#define MEMSIZE 0x1000
#ifdef SHAREMEM
static HANDLE hMapObject;
static LPVOID MapView;

#ifdef DEBUGMAPVIEW
static char logmapviewstr[1024];
static BOOL logmapviewactive = FALSE;
DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name);
DLLExport void _export WINAPI LogMapView (LPSTR type, LPSTR data, int totalsize, int offset, int size)
  {
  if (logmapviewactive)
    return;
  logmapviewactive = TRUE;
  OFSTRUCT Of;
  LPSTR fname = GetStationLogFile ("mapviewd.log");
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        }
      else {
        f = OpenFile (fname,&Of,OF_CREATE);
        _lclose(f);
        }
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    static char dump[32];
    int dumpSize = size;
    if (dumpSize > 16)
      dumpSize = 16;
    LPSTR h, dumpData;
    int i;
    for (dumpData = data + offset, i = 0, h = dump; (i < dumpSize) ; h++, dumpData++, i++) {
      if ((*dumpData >= 32) && (*dumpData <= 127))
        *h = *dumpData;
      else
        *h = '.';
      }
    *h = '\0';
    // TYPE(nnnnnnnn->nnnnnnnn(nnnnnnnn)) t:nnnnn o:nnnnn s:nnnnn d:XxxxxXxxxxXxxxxX
    wsprintf (logmapviewstr,"%s(%8lx->%8lx(%8lx)) t:%5d o:%5d s:%5d d:%s\r\n",type,data,MapView,hMapObject,totalsize,offset,size,dump);
    _lwrite (f,logmapviewstr,lstrlen(logmapviewstr));
    _lclose (f);
    }
  else
    MessageBeep (0);
  logmapviewactive = FALSE;
  }
#endif

DLLExport void _export FAR PASCAL CreateCommunic ()
  {
  hMapObject = CreateFileMapping ((HANDLE) 0xFFFFFFFF,
                                  NULL,
                                  PAGE_READWRITE,
                                  0,
                                  MEMSIZE,
                                  "DEBCOMM");
  
  MapView = MapViewOfFile (hMapObject,FILE_MAP_WRITE,0, 0, 0);
  }
DLLExport void _export FAR PASCAL DestroyCommunic ()
  {
  CloseHandle (hMapObject);
  }
#else
DLLExport void _export FAR PASCAL CreateCommunic ()
  {
  }
DLLExport void _export FAR PASCAL DestroyCommunic ()
  {
  }
#endif


DLLExport LPVOID _export FAR PASCAL GetPointer (LONG lP)
  {
#ifdef SHAREMEM
  return MapView;
#else
  return LPVOID (lP);
#endif
  }

void GetData (LPVOID data,int Size)
  {
#ifdef SHAREMEM
  lmemcpy (data,MapView,Size);
#else
//  return LPVOID (data);
#endif
  }

DLLExport LONG _export FAR PASCAL SetPointer (LPVOID data)
  {
#ifdef SHAREMEM
  if (data != NULL) {
    if (LONG(data) != 1L) {
#ifdef DEBUGMAPVIEW
      LogMapView ("FULL", LPSTR(data) - sizeof(WORD), GetBlockSize (data)  + sizeof(WORD), 0, GetBlockSize (data)  + sizeof(WORD));
#endif
      lmemcpy (MapView,LPSTR(data) - sizeof(WORD),GetBlockSize (data) + sizeof(WORD));
      return LONG (MapView);
      }
    else
      return 1L ;
    }
  else
    return 0L;
#else
  return LONG (data);
#endif
  }

LONG SetPointer (LPVOID data,int Size)
  {
#ifdef SHAREMEM
  if (data != NULL) {
#ifdef DEBUGMAPVIEW
    LogMapView ("PART", LPSTR (data), GetBlockSize (data), 0, Size);
#endif
    lmemcpy (MapView,data,Size);
    return LONG(MapView);
    }
  else
    return 0L;
#else
  return LONG(data);
#endif
  }

LONG SetPointer (LPVOID data,int Offs,int Size)
  {
#ifdef SHAREMEM
  if (data != NULL) {
#ifdef DEBUGMAPVIEW
    LogMapView ("OFFS", LPSTR (data), GetBlockSize (data), Offs, Size);
#endif
    lmemcpy (LPSTR (MapView) + Offs,data,Size);
    return LONG(MapView);
    }
  else
    return 0L;
#else
  return LONG(data);
#endif
  }

/*--< Ermitteln des Framewindows der DDS - Anwendung (oder 0) >--*/
struct EnumWndData {
  BOOL res;
  HWND hWnd;
  };

static char *FrameName = "BLANDFRAME";
static char *RestoolModuleName = "RESTOOL" ;
DLLExport BOOL _export WINAPI EnumResTaskWndProc (HWND hWnd,LPARAM lP)
  {
  EnumWndData FAR *d = (EnumWndData FAR *) lP ;
  char ClassName[128];
  GetClassName (hWnd,ClassName,sizeof(ClassName));
  if (lstrcmp (ClassName,FrameName) == NULL) {
    d->res = TRUE ;
    d->hWnd = hWnd;
    return FALSE ;
    }
  else
    return TRUE ;
  }

extern HANDLE MyInstance;

typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot,LPPROCESSENTRY32 lppe); 
typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags,DWORD th32ProcessID); 
static CREATESNAPSHOT pCreateToolhelp32Snapshot = NULL; 
static PROCESSWALK pProcess32First = NULL; 
static PROCESSWALK pProcess32Next  = NULL; 
// Function that initializes tool help functions. 
BOOL InitToolhelp32 (void) 
  { 
  BOOL   bRet  = FALSE; 
  HINSTANCE hKernel = NULL; 
 
  // Obtain the module handle of the kernel to retrieve addresses of 
  // the tool helper functions. 
  hKernel = GetModuleHandle("KERNEL32.DLL"); 
 
  if (hKernel){ 
    pCreateToolhelp32Snapshot = 
        (CREATESNAPSHOT)GetProcAddress(hKernel, 
        "CreateToolhelp32Snapshot"); 
 
    pProcess32First = (PROCESSWALK)GetProcAddress(hKernel, 
        "Process32First"); 
    pProcess32Next  = (PROCESSWALK)GetProcAddress(hKernel, 
        "Process32Next"); 
 
    // All addresses must be non-NULL to be successful. 
    // If one of these addresses is NULL, one of 
    // the needed lists cannot be walked. 
    bRet =  pProcess32First && pProcess32Next && 
            pCreateToolhelp32Snapshot; 
    } 
  else    
    bRet = FALSE; // could not even get the module handle of kernel 
 
  return bRet; 
  }
 
BOOL FindString (LPSTR s1,LPSTR s2)
  {
  int l2 = lstrlen(s2);
  int l1 = lstrlen(s1);
  if (l1 >= l2)
    return (lstrcmp (s1 + (l1 - l2),s2) == 0);
  else
    return FALSE ;
  }

DWORD GetRestoolProcAddress ()
  {
  static BOOL InitDone,InitRes;

  if (!InitDone) {
    InitRes = InitToolhelp32 ();
    InitDone = TRUE ;
    }
  if (InitRes) {
    HANDLE hsnap = (* pCreateToolhelp32Snapshot) (TH32CS_SNAPPROCESS,0L);
    PROCESSENTRY32 pe;
    DWORD res;
    for ( (* pProcess32First) (hsnap,&pe) ; (* pProcess32Next) (hsnap,&pe) ; ) {
      if (FindString (pe.szExeFile,"RESTOOL.EXE"))
        res = pe.th32ProcessID ;
      }
    CloseHandle (hsnap);
    return res;
    }
  else
    return 0L ;
  }

HWND GetResToolWnd ()
  {
  EnumWndData d;
  d.res = FALSE ;
  d.hWnd = 0;
  EnumWindows (WNDENUMPROC (EnumResTaskWndProc),LONG(LPSTR(&d)));
  DWORD hpr = GetRestoolProcAddress ();
  return d.hWnd ;
  }

/*--< Untersuchen, ob Kommando ein Breakpoint ist >--*/
static LastBreakInfo lbi;
DLLExport LastBreakInfo FAR *_export WINAPI GetLBI ()
  {
  return &lbi;
  }
DLLExport int _export WINAPI GetModuleLine (LPSTR fName,DWORD progOffset,LPSTR incName)
  {
  CallStackInfo csh;
  lstrcpy (csh.ProgName,fName);
  csh.progOffs = progOffset;
  HWND hResWnd = GetResToolWnd ();
  if (hResWnd) {
    int res = int (SendMessage (hResWnd,WMC_GETMODULELINE,0,SetPointer (&csh,sizeof(csh))));
    GetData (&csh,sizeof(csh));
    if (incName != NULL)
      lstrcpy (incName,csh.ProgName);
    return res;
    }
  else
    return -1;
  }

void SetLastModuleBreak (LPSTR fName,DWORD progOffset,WORD modeMask)
  {
  lstrcpy (lbi.LastModuleBreak,fName);
  lbi.LastModuleLine = GetModuleLine (fName,progOffset);
  lbi.LastStackBreak = lbi.ActCSPtr;
  lbi.LastModeMask = modeMask;
  }


BOOL ShowScriptWindow (BPInfo FAR *h,WORD mode)
  {
  HWND hResToolWnd = GetResToolWnd ();
  if (hResToolWnd) {
#ifdef SHAREMEM
    if ((h != NULL) && (h->Extra)){
      SetPointer (h->Extra,sizeof(*h),lstrlen(h->Extra) + 1);
      }
#endif
    BringWindowToTop (hResToolWnd);
    SetForegroundWindow (hResToolWnd);
    SendMessage (hResToolWnd,WMC_ACTIVATE,mode,SetPointer (h,sizeof(*h)));
    }
  return (hResToolWnd != 0);
  }

LPVOID actContext;
DLLExport LPVOID _export WINAPI DDSGetVarValExtended (VarValExtended FAR *ve)
  {
  LPVOID res ;
  if (IsValidChild(ve->actContext))
    res = DDSGetVarVal (ve->actContext,ve->TableID,ve->VarID);
  else
    res = LPVOID(1L) ;
  return res;
  }

DLLExport LPVOID _export WINAPI DDSGetVarVal (LPVOID Context,WORD TableNr,WORD VarNr)
  {
  LPVOID res = NULL;
  mdiChild FAR *c ;
  if (Context != NULL)
    c = (mdiChild *) Context ;
  else
    c = (mdiChild *) actContext ;
  if (c != NULL) {
    LPDBRECORD rec;
    LPRECROOT rr = c->rr ;
    if (rr->AnzTables > TableNr)
      rec = rr->GetRecord(TableNr);
    else
      rec = NULL ;
    if ((rec != NULL) && (rec->GetAnzVars() > VarNr))
      res = rec->Get (VarNr);
    else
      res = LPVOID(1L);
    }
  return res;
  }

DLLExport BOOL _export WINAPI IsInDebugMode ()
  {
  return (actContext != NULL) ;
  }
                                        
EXTCHKMSG exch;
HWND hFrameWin;
DLLExport BOOL _export WINAPI WaitForRestool (mdiChild *c,BPInfo FAR *h,WORD mode,LPSTR fName,DWORD progOffs,WORD modeMask)
  {
  static BOOL waitingForRestool = FALSE;
  SetLastModuleBreak (fName,progOffs,modeMask);
  actContext = c;
  if (!waitingForRestool && ShowScriptWindow (h,mode)) {
    waitingForRestool = TRUE;
    for ( ; ; ) {
      if (!IsWindow (hFrameWin))
        break ;

      MSG msg ;
      if (PeekMessage (&msg,0,WMC_CONTINUEEXECUTION,WMC_CONTINUEEXECUTION,PM_REMOVE)) {
        actContext = NULL;
//        BringWindowToTop (hFrameWin);
//        SetForegroundWindow (hFrameWin);
        break ;
        }

      if (PeekMessage (&msg,0,WMC_DOSTEP,WMC_DOSTEP,PM_REMOVE)) {
        actContext = NULL;
        lbi.dbMode = DBMODE_STEP ;
//        BringWindowToTop (hFrameWin);
        // SetForegroundWindow (hFrameWin); Wegen Problemen mit Tooltips auskommentiert !?
        break ;
        }

      if (PeekMessage (&msg,0,WMC_DOSTEPINTO,WMC_DOSTEPINTO,PM_REMOVE)) {
        actContext = NULL;
        lbi.dbMode = DBMODE_STEPINTO ;
//        BringWindowToTop (hFrameWin);
        // SetForegroundWindow (hFrameWin); Wegen Problemen mit Tooltips auskommentiert !?
        break ;
        }

      if (PeekMessage (&msg,0,WM_KEYFIRST,WM_KEYLAST,PM_NOREMOVE)) {
        if (!ShowScriptWindow (NULL,0)) {
          // Restool ist gestorben -> wieder weitermachen lassen !!!
          actContext = NULL;
          break ;
          }
        }
      if (PeekMessage (&msg,0,WM_MOUSEFIRST,WM_MOUSELAST,PM_REMOVE)) {
        if (!ShowScriptWindow (NULL,0)) {
          // Restool ist gestorben -> wieder weitermachen lassen !!!
          actContext = NULL;
          break ;
          }
        }

      /*----< Alle Meldungen, ausser Tastatur, Maus und User durchlasse >---*/
      if ((PeekMessage (&msg,0,WM_NULL,WM_KEYFIRST-1,PM_REMOVE)) ||
          (PeekMessage (&msg,0,WM_KEYLAST+1,WM_MOUSEFIRST-1,PM_REMOVE)) ||
          (PeekMessage (&msg,0,WM_MOUSELAST+1,WM_USER-1,PM_REMOVE))) {
        (* exch) (&msg);
        }
      }
    waitingForRestool = FALSE;
    return TRUE ;
    }
  else {
    actContext = NULL ;
    return FALSE ;
    }
  }

/*---------< Stack Info in der Marille >----------*/
#define MAX_CSINF   128
CallStackInfo CSInf[MAX_CSINF];
DLLExport void _export WINAPI PushToCallStack (mdiChild *c,LPSTR fName,DWORD progOffs)
  {
  if (lbi.ActCSPtr < MAX_CSINF) {
    CSInf[lbi.ActCSPtr].c = c;
    lstrcpy (CSInf[lbi.ActCSPtr].ProgName,fName);
    CSInf[lbi.ActCSPtr].progOffs = progOffs;
    lbi.ActCSPtr ++;
    }
  }

DLLExport void _export WINAPI PopFromCallStack ()
  {
  if (lbi.ActCSPtr > 0)
    lbi.ActCSPtr --;
  }

DLLExport void _export WINAPI ClearCallStack ()
  {
  lbi.ActCSPtr = 0;
  }

DLLExport LONG _export WINAPI GetStackInfo (WORD wP,CallStackInfo FAR *csi)
  {
  if (int (wP) < lbi.ActCSPtr) {
    *csi = CSInf[wP];
    return 1L ;
    }
  else {
    csi->c = (mdiChild FAR *) actContext ;
    return 0L ;
    }
  }

DLLExport LONG _export WINAPI GetLastStackAddress ()
  {
  return CSInf[lbi.ActCSPtr-1].progOffs;
  }
mdiChild *GetLastStackChild ()
  {
  return CSInf[lbi.ActCSPtr-1].c;
  }

DLLExport BOOL _export WINAPI Exception (mdiChild *c,WORD mode,LPSTR extra)
  {
  DWORD progOffs = GetLastStackAddress ();
  if (c == NULL) c = GetLastStackChild ();
  if (c == NULL) {
    char outtxt[512];
    wsprintf (outtxt,"DBWIN_ASSERT kann Script nicht ermitteln! (%s)",extra);
    WIN_ASSERT_TEXT (FALSE,outtxt);
    return TRUE;
    }
  else {
    BPInfo h;
    lstrcpy (h.PName,c->schd->fName);
    h.LineNmbr = GetModuleLine (c->schd->fName,progOffs,h.FName);
    h.Extra = extra;

    return WaitForRestool (c,&h,mode,c->schd->fName,progOffs,0xFFFF);
    }
  }

DLLExport void _export WINAPI dbwin_ass_failed      (int modnum, int line)
  {
  HWND hResToolWnd = GetResToolWnd ();
  if ((hResToolWnd) && (exch != NULL)) {
    LogMsg (modnum,line,NULL);
    char outtxt[128];
    wsprintf (outtxt,"%s/%d",ModName(modnum),line);
    Exception (NULL,0xFFFE,outtxt);
    }
  else
    win_ass_failed (modnum,line);
  }

DLLExport void _export WINAPI dbwin_ass_failed_text (int modnum, int line,LPSTR text)
  {
  HWND hResToolWnd = GetResToolWnd ();
  if ((hResToolWnd) && (exch != NULL)) {
    LogMsg (modnum,line,text);
    char outtxt[512];
    if (lstrlen(text) > 450) {
      wsprintf (outtxt,"%s/%d (%.450s)",ModName(modnum),line,text);
    }
    else {
      wsprintf (outtxt,"%s/%d (%s)",ModName(modnum),line,text);
      }
    Exception (NULL,0xFFFE,outtxt);
    }
  else
    win_ass_failed_text (modnum,line,text);
  }

DLLExport void _export WINAPI COMPILE_Setup (HWND FrameWnd,EXTCHKMSG ech)
  {
  hFrameWin = FrameWnd;
  exch = ech ;
  }

DLLExport void _export WINAPI InquireBreakPoints ()
  {
  HWND hResToolWnd = GetResToolWnd ();
  if (hResToolWnd) {
    SendMessage (hResToolWnd,WMC_INQUIREBPLIST,0,0L);
    }
  }

MDIListEntry FAR *MDILEFirst;
OldMDIListEntry FAR *OLDMDILEFirst;

DLLExport MDIListEntry FAR *_export WINAPI GetMDILEFirst()
  {
  return MDILEFirst;
  }

DLLExport OldMDIListEntry FAR *_export WINAPI GetOLDMDILEFirst()
  {
  return OLDMDILEFirst;
  }

#define MAX_OLDHANDLES    20
void ClearOldHandles ()
  {
  OldMDIListEntry FAR *h = OLDMDILEFirst ;
  for (int i = 0 ; h != NULL ; h = h->Next , i++) ;
  if (i > MAX_OLDHANDLES) {
    OldMDIListEntry FAR *h = OLDMDILEFirst->Next ;
    GlobalUnlock (OLDMDILEFirst->commands);
    GlobalFree (OLDMDILEFirst->commands);
    FreeGlobMem (OLDMDILEFirst);
    OLDMDILEFirst = h;
    }
  }

void PushToOldHandles (LPSTR Name,GLOBALHANDLE commands)
  {
  if (commands == 0) return ;
  OldMDIListEntry FAR *h = (OldMDIListEntry FAR *) GetGlobMem (sizeof(*h));
  h->Next = NULL;
  lstrcpy (h->fName,Name);
  h->commands = commands;
  if (OLDMDILEFirst == NULL)
    OLDMDILEFirst = h;
  else {
    for ( OldMDIListEntry FAR *x = OLDMDILEFirst ; x != NULL ; x = x->Next ) {
      if (x->Next == NULL) {
        x->Next = h;
        break ;
        }
      }
    }
  }

DLLExport void _export FAR PASCAL RemoveMDIHandleList ()
  {
  for ( OldMDIListEntry FAR *x = OLDMDILEFirst ; OLDMDILEFirst != NULL ; x = OLDMDILEFirst) {
    OLDMDILEFirst = x->Next ;
    if (x->commands) GlobalUnlock (x->commands) , GlobalFree (x->commands);
    FreeGlobMem (x);
    }
  }

DLLExport void _export FAR PASCAL PushToMDIList (mdiChild FAR *n)
  {
  MDIListEntry FAR *ent = (MDIListEntry FAR *) GetGlobMem (sizeof(*ent));
  ent->Next = MDILEFirst;
  ent->ent = n;
  MDILEFirst = ent;
  }

DLLExport void _export FAR PASCAL PopFromMDIList (mdiChild FAR *n)
  {
  MDIListEntry FAR *prev = NULL;
  for (MDIListEntry FAR *h = MDILEFirst ; h != NULL ; h = h->Next) {
    if (h->ent == n) {
      if (prev != NULL) prev->Next = h->Next ;
      else              MDILEFirst = h->Next;
      FreeGlobMem (h);
      ClearOldHandles ();
      PushToOldHandles (n->schd->fName,n->commands);
      break ;
      }
    prev = h;
    }
  }

DLLExport BOOL _export FAR PASCAL IsValidChild (LPVOID c)
  {
  for (MDIListEntry FAR *h = MDILEFirst ; h != NULL ; h = h->Next) {
    if (h->ent == c) {
      return TRUE ;
      }
    }
  return FALSE ;
  }

static MDIListEntry FAR *FirstContext ;
DLLExport LONG _export WINAPI GetDDSFirstContext (ContextBuffer FAR *vc)
  {
  MDIListEntry FAR *h = NULL;

  if (actContext) {
    for (h = MDILEFirst ; h != NULL ; h = h->Next) {
      if (h->ent == (mdiChild *) actContext)
        break ;
      }
    }

  if (h == NULL)
    h = MDILEFirst ; 

  if (h != NULL) {
    FirstContext = h ;
    lstrcpy (vc->fName,h->ent->schd->fName);
    vc->c = h->ent ;
    vc->dummy = h ;
    }
  else
    FirstContext = NULL ;

  return 0L ;
  }

MDIListEntry FAR *NextCycl (MDIListEntry FAR *old) 
  {
  if (old->Next != NULL) return old->Next ;
  else                   return MDILEFirst ;
  }

DLLExport LONG _export WINAPI GetDDSNextContext (ContextBuffer FAR *vc)
  {
  MDIListEntry FAR *h = NextCycl ((MDIListEntry FAR *) vc->dummy) ;
  if (h != FirstContext) {
    lstrcpy (vc->fName,h->ent->schd->fName);
    vc->c = h->ent ;
    vc->dummy = h ;
    }
  return 0L ;
  }

