/*
**  Kommunikation zwischen Restool und dem Hauptprogramm
*/
// $Header:   P:/marille/clinicum/restool/rev/communic.cpv   1.30   18 May 2000 12:40:04   Wolfgang  $
// $Log:   P:/marille/clinicum/restool/rev/communic.cpv  $
// 
//    Rev 1.30   18 May 2000 12:40:04   Wolfgang
// 1.) DDSStatus am Anfang von Step... umsetzen, da BringWindowToTop bzw.
//     SetForeGroundWindow u.U. bereits ActivateRestool ausloesen, was Status
//     auf BREAK setzt, der dann falscherweise wieder auf RUN zurueckgesetzt
//     wird.
// 
//    Rev 1.29   17 May 2000 18:27:22   Wolfgang
// 1.) Restool macht jetzt SetForegroundWindow fuer DDS (NT2000).
// 2.) WIN32 entfernt.
// 
//    Rev 1.28   16 Feb 2000 15:03:46   Wolfgang
// 1.) GetNextInCycl neu.
// 
//    Rev 1.27   23 Nov 1999 15:49:08   Wolfgang
// 1.) GetScriptHd neu.
// 
//    Rev 1.26   26 Apr 1999 18:11:00   Wolfgang
// 1.) Kein Absturz mehr bei langen Assert-Texten.
// 
//    Rev 1.25   18 Mar 1999 14:07:16   Wolfgang
// 1.) Angabe des Feldes bei SB_SETTEXT ueber Konstante.
// 
//    Rev 1.24   16 Mar 1999 19:41:10   Wolfgang
// 1.) MainFile TRUE bei ShowScript.
// 
//    Rev 1.23   16 Mar 1999 16:12:32   Wolfgang
// 1.) ShowScript mit NULL zur Fenstererzeugung verwenden.
// 
//    Rev 1.22   26 Feb 1999 17:39:24   Wolfgang
// 1.) Wenn in source nichts zu holen ist, schau ma in forms auch noch nach.
// 
//    Rev 1.21   05 Oct 1998 11:25:34   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.20   14 Aug 1998 18:56:12   Hannes
// Include / Source Pfad wirklich trennen
// 
//    Rev 1.19   19 Jan 1998 20:17:16   Hannes
// 
//    Rev 1.18   01 Dec 1997 19:38:50   Hannes
// Diverse Anpassungen
// 
//    Rev 1.17   21 Nov 1997 15:55:00   Hannes
// Feinschliff Debugger
// 
//    Rev 1.16   19 Nov 1997 18:44:18   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.15   28 Aug 1997 15:48:04   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.14   19 Feb 1997 12:12:10   Hannes
// No change.
// 
//    Rev 1.13   27 Jan 1997 09:23:16   HANNES
// EnumTaskWindow auf EnumWindows umgestellt
// 
//    Rev 1.12   28 Oct 1996 08:47:08   HANNES
// 
//    Rev 1.11   21 Oct 1996 18:56:34   HANNES
// Erweiterte Debugfunktionalitaet
// 
//    Rev 1.10   02 Feb 1996 10:50:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   24 Aug 1995 00:16:46   HANNES
// Debuggerverbesserungen
// 
//    Rev 1.8   11 Jul 1995 12:45:58   HANNES
// Debuggerdefinitionen umgelagert
// 
//    Rev 1.7   13 Jan 1995 16:54:22   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.6   09 Jan 1995 12:17:22   HANNES
// Debugger eingebaut
// 
//    Rev 1.5   09 Jan 1995 09:25:14   HANNES
// 
//    Rev 1.4   04 Jan 1995 13:41:04   HANNES
// 
//    Rev 1.3   03 Jan 1995 12:04:14   HANNES
// 
//    Rev 1.2   02 Jan 1995 15:08:46   HANNES
// 
//    Rev 1.1   02 Jan 1995 12:20:26   HANNES
// 
//    Rev 1.0   02 Jan 1995 12:16:16   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>

#include "dds32.h"

#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#include "communic.hpp"
#include "blandmdi.hpp"
#include "restool.hpp"
#include "statbar.hpp"

#ifdef DEBUG
#define SHAREMEM
#endif

#ifdef SHAREMEM
static HANDLE hMapObject;
static LPVOID MapView;
#endif

#ifdef SHAREMEM
void ROpenCommunic ()
  {
  if (hMapObject) return ;

  hMapObject = OpenFileMapping (FILE_MAP_WRITE,
                                FALSE,
                                "DEBCOMM");
  if (hMapObject) {
    MapView = MapViewOfFile (hMapObject,
                                   FILE_MAP_WRITE,
                                   0, 0, 0);
    }
  }

void RDestroyCommunic ()
  {
  if (hMapObject) CloseHandle (hMapObject);
  hMapObject = NULL;
  }
#endif

LONG RSetData (LPVOID data,int Size)
  {
#ifdef SHAREMEM
  ROpenCommunic ();
  lmemcpy (MapView,data,Size);
  return LONG(MapView);
#else
  return LONG (data);
#endif
  }

void RGetData (LPVOID res,int Size)
  {
#ifdef SHAREMEM
  lmemcpy (res,MapView,Size);
#endif
  }

LPVOID RGetPointer (LONG lP)
  {
#ifdef SHAREMEM
  ROpenCommunic ();
  if (lP != 0L)
    return MapView;
  else
    return NULL;
#else
  return LPVOID (lP);
#endif
  }

LPVOID RGetPointer (LPVOID Ptr,int Offs)
  {
#ifdef SHAREMEM
  ROpenCommunic ();
  if (Ptr != NULL)
    return LPSTR(MapView) + Offs;
  else
    return NULL;
#else
  return Ptr;
#endif
  }

LPVOID RGetPointer_Size (LONG lP)
  {
#ifdef SHAREMEM
  ROpenCommunic ();
  if ((lP != 0L) && (lP != 1L))
    return LPSTR (MapView) + sizeof(WORD);
  else
    return LPVOID (lP);
#else
  return LPVOID (lP);
#endif
  }

void AddPointer (LPVOID data,int Offs,int Size)
  {
#ifdef SHAREMEM
  ROpenCommunic ();
  lmemcpy ((LPSTR)MapView + Offs,data,Size);
#endif
  }

/*--< Ermitteln des Framewindows der DDS - Anwendung (oder 0) >--*/
struct EnumWndData {
  BOOL res;
  HWND hWnd;
  };

static char *FrameName = "MDIFRAME";
static char *DDSModuleName = "DDS" ;
BOOL CALLBACK EnumTaskWndProc (HWND hWnd,LONG lP)
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

extern HINSTANCE MyInstance;
HWND GetDDSMainWnd ()
  {
  EnumWndData d;
  d.res = FALSE ;
  d.hWnd = 0;

  FARPROC lpEnumProc = FARPROC (MakeProcInstance(FARPROC (EnumTaskWndProc), MyInstance));
#ifdef UEBERLEGT
  TASKENTRY te;
  te.dwSize = sizeof(te);
  for ( TaskFirst (&te) ; ; ) {
    if (lstrcmp (te.szModule,DDSModuleName) == 0) {
      EnumTaskWindows (te.hTask,lpEnumProc,LONG(LPSTR(&d)));
      if (d.res) break ;
      }
    te.dwSize = sizeof(te);
    if (!TaskNext (&te)) break ;
    }
#else
  EnumWindows ((WNDENUMPROC)lpEnumProc,LONG(LPSTR(&d)));
#endif
  FreeProcInstance (lpEnumProc);

#ifdef SHAREMEM
  if (d.hWnd)
    ROpenCommunic ();
  else
    RDestroyCommunic ();
#endif
  return d.hWnd;
  }

void ClearCachedProg (LPSTR Name)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    char fname[128];
    lstrcpy (fname,Name);
    LPSTR h = LPSTR(fname);
    LPSTR start = h;
    for ( ; *h ; h++) {
      if ((*h == '\\') || (*h == ':')) start = h+1;
      }
    AnsiUpper (start);
#ifdef SHAREMEM
    lstrcpy (LPSTR(MapView),start);
#endif
    SendMessage (hDDSWnd,WMC_CLEARCEACHE,0,LONG(start));
    }
  }

#define DDSSTATUS_UNKNOWN   0
#define DDSSTATUS_BREAKDONE 1
#define DDSSTATUS_RUN       2
int DDSStatus ;
void RunDDS ()
  {
  if (DDSStatus != DDSSTATUS_BREAKDONE) return ;
  DDSStatus = DDSSTATUS_RUN;
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    PostMessage (hDDSWnd,WMC_CONTINUEEXECUTION,0,0L);
    BringWindowToTop (hDDSWnd);
    SetForegroundWindow (hDDSWnd);
    }
  }

void StepDDS ()
  {
  if (DDSStatus != DDSSTATUS_BREAKDONE) return ;
  DDSStatus = DDSSTATUS_RUN;
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    PostMessage (hDDSWnd,WMC_DOSTEP,0,0L);
#ifdef UEBERLEGT
    // Zur Vermeidung des Flackerns beim Steppen auskommentiert
    BringWindowToTop (hDDSWnd);
    SetForegroundWindow (hDDSWnd);
#endif
    }
  }

void StepIntoDDS ()
  {
  if (DDSStatus != DDSSTATUS_BREAKDONE) return ;
  DDSStatus = DDSSTATUS_RUN;
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    PostMessage (hDDSWnd,WMC_DOSTEPINTO,0,0L);
#ifdef UEBERLEGT
    // Zur Vermeidung des Flackerns beim Steppen auskommentiert
    BringWindowToTop (hDDSWnd);
    SetForegroundWindow (hDDSWnd);
#endif
    }
  }

extern HWND hwndMDIClient;
extern LPSTR PushString (LPSTR old,LPSTR strtopush);
char ActiveBreakModule[13];
int  ActiveBreakLine;
BOOL IsActiveBreakLine (int LineNr,LPSTR fName)
  {
  if ((DDSStatus == DDSSTATUS_BREAKDONE) &&
      (ActiveBreakLine == LineNr) &&
      (lstrcmp (GetFName(fName),ActiveBreakModule) == 0))
    return TRUE ;
  else
    return FALSE ;
  }

void SetModuleActive (LPSTR h_FName,int h_LineNmbr)
  {
  BOOL Found = FALSE;
  HWND hwndT;
  for (hwndT = GetWindow(hwndMDIClient, GW_CHILD) ; hwndT ; ) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow(hwndT, GW_HWNDNEXT);
    if (hwndT) {
      // Durchsuchen, ob das vielleich das richtige ist
      if (CheckWindowForBreak (hwndT,h_FName,h_LineNmbr)) {
        Found = TRUE;
        break;
        }
      else
        hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
      }
    }
  if (!Found) {
    // Das File muss erzeugt werden
    char FName[128],SName[128];
    if (!GetIncludeFileName (h_FName, FName, SName,"source"))
      GetIncludeFileName (h_FName, FName, SName,"forms");
    HWND hWndChild;
    if (hWndChild = ShowScript (NULL, FName, TRUE))
      CheckWindowForBreak (hWndChild,h_FName,h_LineNmbr);
    }
  }

#define MAXEXTRALEN 221
extern void UpdateVals ();
void ActivateRestool (HWND hWnd,WORD mode,LONG lP)
  {
  BPInfo FAR *h = (BPInfo FAR *) RGetPointer (lP);
  char outtxt[256];

  DDSStatus = DDSSTATUS_BREAKDONE;

  if (h == NULL) return;

  if (h->LineNmbr < 0) {
    if (mode == 0xFFFF)
      wsprintf (outtxt,"unknown Exception/Varbreak in %s",h->FName);
    else if (mode == 0xFFFE) {
      char extratxt[MAXEXTRALEN + 1];
      LPSTR extraptr = (LPSTR) RGetPointer (h->Extra,sizeof(*h));
      int extralen = lstrlen (extraptr);
      if (extralen > MAXEXTRALEN)
        extralen = MAXEXTRALEN;
      lmemcpy (extratxt, extraptr, extralen);
      extratxt [extralen] = '\0';
      wsprintf (outtxt,"unknown WIN_ASSERT in %s: %s",h->FName,extratxt);
      }
    else
      wsprintf (outtxt,"unknown Break in %s",h->FName);
    SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
    return ;
    }

  ActiveBreakLine = h->LineNmbr;
  lstrcpy (ActiveBreakModule,h->FName);

  // Durchsuchen aller offenen Fenster
  SetModuleActive (h->FName,h->LineNmbr);

  if (mode < 0xFFFE) {
    LPSTR modestring = NULL;
    if (mode & EM_LOAD)
      modestring = PushString (modestring,"EM_LOAD");
    if (mode & EM_CHANGETOTRUE) {
      if (modestring != NULL) modestring = PushString (modestring," | ");
      modestring = PushString (modestring,"EM_CHANGETOTRUE");
      }
    if (mode & EM_FIXCONNECTION) {
      if (modestring != NULL) modestring = PushString (modestring," | ");
      modestring = PushString (modestring,"EM_FIXCONNECTION");
      }
    if (mode & EM_UPDATE) {
      if (modestring != NULL) modestring = PushString (modestring," | ");
      modestring = PushString (modestring,"EM_UPDATE");
      }
    if (mode & EM_RESET) {
      if (modestring != NULL) modestring = PushString (modestring," | ");
      modestring = PushString (modestring,"EM_RESET");
      }
    if (mode & EM_CLEAR) {
      if (modestring != NULL) modestring = PushString (modestring," | ");
      modestring = PushString (modestring,"EM_CLEAR");
      }
    if (modestring != NULL)
      wsprintf (outtxt,"Break in %s, Line %d, Mode %s",h->FName,h->LineNmbr,modestring);
    else
      wsprintf (outtxt,"Break in %s, Line %d, Mode <NONE>",h->FName,h->LineNmbr);
    if (modestring != NULL) FreeGlobMem (modestring);
    }
  else {
    if (mode == 0xFFFF)
      wsprintf (outtxt,"Exception/Varbreak in %s, Line %d",h->FName,h->LineNmbr);
    else {
      char extratxt[MAXEXTRALEN + 1];
      LPSTR extraptr = (LPSTR) RGetPointer (h->Extra,sizeof(*h));
      int extralen = lstrlen (extraptr);
      if (extralen > MAXEXTRALEN)
        extralen = MAXEXTRALEN;
      lmemcpy (extratxt, extraptr, extralen);
      extratxt [extralen] = '\0';
      wsprintf (outtxt,"WIN_ASSERT in %s, Line %d: %s",h->FName,h->LineNmbr,extratxt);
      }
    }
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
  UpdateVals ();
  }

void SetDDSBreak (BPInfo FAR *h)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    AddPointer (LPSTR (h->pOffs) - sizeof(WORD),sizeof(*h),GetBlockSize (h->pOffs) + sizeof(WORD));
    SendMessage (hDDSWnd,WMC_SETBREAKPOINT,0,RSetData (h,sizeof(*h)));
    }
  }

void ClearDDSBreak (BPInfo FAR *h)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    SendMessage (hDDSWnd,WMC_REMOVEBREAKPOINT,0,RSetData (h,sizeof(*h)));
    }
  }

LPVOID GetScriptHd (CHAR FAR * ProgName)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LPVOID res;
  if (hDDSWnd)
    res = RGetPointer (SendMessage (hDDSWnd,WMC_GETSCRIPTHD,0,RSetData (ProgName, lstrlen(ProgName) + 1)));
  else
    res = NULL;
  return res;
  }

LPVOID GetVarValue (WORD TableNr,WORD VarNr)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LPVOID res;
  if (hDDSWnd)
    res = RGetPointer_Size (
          SendMessage (hDDSWnd,WMC_GETVARVAL,0,MAKELONG(TableNr,VarNr))
                           );
  else
    res = NULL;
  return res;
  }

LPVOID GetVarValueExtended (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LPVOID res;
  if (hDDSWnd) {
    VarValExtended ve;
    lstrcpy (ve.Scope,Scope);
    ve.TableID = TableID;
    ve.VarID = VarID;
    ve.actContext = actContext;
    res = RGetPointer_Size (SendMessage (hDDSWnd,WMC_GETVARVAL_SCOPE,0,RSetData (&ve,sizeof(ve))));
    }
  else
    res = NULL;
  return LPVOID (res);
  }

BOOL GetFirstContext (ContextBuffer FAR *vc)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    vc->c = NULL ;
    SendMessage (hDDSWnd,WMC_GETFIRSTCONTEXT,0,RSetData (vc,sizeof(*vc)));
    RGetData (vc,sizeof(*vc));
    return (vc->c != NULL) ;
    }
  else
    return FALSE ;
  }

BOOL GetNextContext (ContextBuffer FAR *vc)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    vc->c = NULL ;
    SendMessage (hDDSWnd,WMC_GETNEXTCONTEXT,0,RSetData (vc,sizeof(*vc)));
    RGetData (vc,sizeof(*vc));
    return (vc->c != NULL) ;
    }
  else
    return FALSE ;
  }

BOOL SetVarBreak (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LONG res;
  if (hDDSWnd) {
    VarValExtended ve;
    lstrcpy (ve.Scope,Scope);
    ve.TableID = TableID;
    ve.VarID = VarID;
    ve.actContext = actContext;
    res = SendMessage (hDDSWnd,WMC_SETVARBREAK,0,RSetData(&ve,sizeof(ve)));
    }
  return (hDDSWnd != 0) ;
  }

BOOL ClearVarBreak (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LONG res;
  if (hDDSWnd) {
    VarValExtended ve;
    lstrcpy (ve.Scope,Scope);
    ve.TableID = TableID;
    ve.VarID = VarID;
    ve.actContext = actContext ;
    res = SendMessage (hDDSWnd,WMC_CLEARVARBREAK,0,RSetData(&ve,sizeof(ve)));
    }
  return (hDDSWnd != 0) ;
  }

/*-----< Suchen der ScDebugInfo in den Offenen Fenstern >-------*/
ScDebugInfo FAR *SearchDebugInfo (LPSTR fName,BOOL doOpen)
  {
  // Durchsuchen aller offenen Fenster
  BOOL Found = FALSE;
  HWND hwndT;
  ScDebugInfo FAR *res = NULL;
  for (hwndT = GetWindow(hwndMDIClient, GW_CHILD) ; hwndT ; ) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow(hwndT, GW_HWNDNEXT);
    if (hwndT) {
      // Durchsuchen, ob das vielleich das richtige ist
      res = GetDebugInfoFromWindow (hwndT,fName,&Found,TRUE);
      if (Found)
        break ;
      else
        hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
      }
    }
  if ((!Found) && (doOpen)) {
    // Das File muss erzeugt werden
    char FName[128],SName[128];
    if (!GetIncludeFileName (fName, FName, SName,"source"))
      GetIncludeFileName (fName, FName, SName,"forms");
    HWND hWndChild;
    if (hWndChild = ShowScript (NULL, FName, TRUE))
      res = GetDebugInfoFromWindow (hWndChild,fName,&Found,TRUE);
    }
  return res;
  }

LONG SearchModuleLine (HWND hWnd,CallStackInfo FAR * csi,LPSTR SName,BOOL doOpen)
  {
  ScDebugInfo FAR *sci = SearchDebugInfo (csi->ProgName,doOpen);
  if (sci != NULL) {
    return sci->GetLineFromAddress (csi->progOffs,SName);
    }
  else
    return -1L;
  }

BOOL GetContextBuffer (ContextBuffer FAR *vc,int sel)
  {
  int i = 0 ;
  for ( BOOL res = GetFirstContext (vc) ; res ; res = GetNextContext (vc) ) {
    if (i == sel) return TRUE ;
    i ++ ;
    }
  return FALSE ;
  }

LPVOID GetRecordPointer (LPVOID ListPtr,int Index,BOOL FAR *IsActive)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LPVOID res = NULL;
  *IsActive = FALSE ;
  if (hDDSWnd) {
    DBGGetRecordPtr dr;
    dr.ListPtr = ListPtr;
    dr.Index = Index;
    lmemcpy (LPSTR(MapView) + sizeof(dr),LPSTR (ListPtr) - sizeof(WORD),GetBlockSize(ListPtr) + sizeof(WORD));
    res = LPVOID (SendMessage (hDDSWnd,WMC_GETRECORDPTR,0,RSetData(&dr,sizeof(dr))));
    RGetData (&dr,sizeof(dr));
    if (res) *IsActive = dr.IsActive ;
    }
  return res ;
  }

LPVOID GetRecData (LPVOID r,int i)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LPVOID res;
  if (hDDSWnd)
    res = RGetPointer_Size (SendMessage (hDDSWnd,WMC_GETRECDATA,i,LONG(r)));
  else
    res = NULL;
  return res ;
  }

LONG GetFuncFOffs (LPVOID c)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  LONG res;
  if (hDDSWnd)
    res = SendMessage (hDDSWnd,WMC_GETFUNCOFFS,0,LONG(c));
  else
    res = 0L;
  return res ;
  }

BOOL IsListPtr (LPVOID ListPtr,int FAR *AnzRecs,LPSTR Name)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  BOOL res = NULL;
  *AnzRecs = 0;
  if (hDDSWnd) {
    DBGIsListPtr dr;
    memmove (LPSTR (MapView) + sizeof(dr),MapView,*(WORD FAR *)MapView + sizeof(WORD));
    dr.ListPtr = ListPtr;
    res = BOOL (SendMessage (hDDSWnd,WMC_ISLISTPTR,0,RSetData(&dr,sizeof(dr))));
    RGetData (&dr,sizeof(dr));
    if (res) {
      *AnzRecs = dr.AnzRecs;
      lstrcpy (Name,dr.StructName);
      }
    memmove (MapView,LPSTR (MapView) + sizeof(dr),*(WORD FAR *)(LPSTR (MapView) + sizeof(dr)) + sizeof(WORD));
    }
  return res ;
  }

void GetRecTable (LPVOID r,TableRef FAR *tr)
  {
  tr->TableNr = 0;
  tr->Version = 0;
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    LONG res = SendMessage (hDDSWnd,WMC_GETRECTABLE,0,LONG(r));
    tr->TableNr = LOWORD(res);
    tr->Version = HIWORD(res);
    }
  }

void GetNextInCycl (LPVOID r, LPVOID *nr) 
  {
  *nr = NULL;
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd) {
    LONG res = SendMessage (hDDSWnd,WMC_GETNEXTINCYCL,0,LONG(r));
    *nr = LPVOID (res);
    }
  }

void DestroyDDS ()
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd)
    PostMessage (hDDSWnd,WMC_CLOSE,0,0L);
  }

void BreakDDS ()
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  if (hDDSWnd)
    PostMessage (hDDSWnd,WMC_BREAKIMMEDIATELY,0,0L);
  }

