/*-------------------------------------------------*/
/* extdll.cpp - Aufruf von Fremd-DLL-Funktionen    */
/*-------------------------------------------------*/
//  $Header:   P:/marille/clinicum/rev/extdll.cpv   1.20   25 Apr 2000 18:16:54   Martin  $
//  $Log:   P:/marille/clinicum/rev/extdll.cpv  $
// 
//    Rev 1.20   25 Apr 2000 18:16:54   Martin
// WIN_ASSERT in ScriptCallBack entschaerft (<= statt ==)
// 
//    Rev 1.19   01 Mar 2000 08:33:56   Dietmar
// ClientExtWindow implementiert (Hannes)
//
//    Rev 1.18   18 Nov 1998 19:12:44   Hannes
// Grauer Hintergrund
//
//    Rev 1.17   09 Nov 1998 15:22:56   Martin
// Pascal Calling Convention in 32 Bit: von rechts nach links pushen
//
//    Rev 1.16   05 Oct 1998 11:54:00   Gerhold
// Vorbereitung auf C6 (Type Casts)
//
//    Rev 1.15   18 Aug 1998 19:28:16   Martin
// CallDllProcDynamic
//
//    Rev 1.14   25 Jun 1998 16:25:40   Martin
// TestDllProc
//
//    Rev 1.13   20 Nov 1997 19:33:48   Martin
// DataFromPointer
//
//    Rev 1.12   26 Aug 1997 19:24:28   Martin
// 16 Bit faehig
//
//    Rev 1.11   25 Aug 1997 14:54:42   Martin
// CreateDBDesc
//
//    Rev 1.10   01 Jul 1997 18:21:48   Martin
// FILTERDLLMSG -> FilterDllMsg, PROCESSDLLIDLE -> ProcessDllIdle
//
//    Rev 1.9   10 Mar 1997 14:47:42   gerhold
// WIN32 ... LoadLibrary hat keine Fehlernummer, sondern Pointer als return
//
//    Rev 1.8   10 Feb 1997 17:48:08   martin
// VT_DWORD geht jetzt auch fuer negative Zahlen ...
//
//    Rev 1.7   04 Feb 1997 20:03:06   MARTIN
// FreeAllExternDlls, WIN_ASSERTs bei GetProcPtr
//
//    Rev 1.6   27 Jan 1997 13:45:22   MARTIN
// ExeIs32Bit
//
//    Rev 1.5   17 Dec 1996 11:02:16   GERHOLD
// ProcessDLLIdle, FilterDLLMsg fuer 32 Bit
//
//    Rev 1.4   25 Jul 1996 19:50:14   GERHOLD
// #pragma pack(1);   WIN32 ... _asm PUSH DWORD
//
//    Rev 1.3   25 Apr 1996 19:01:18   MARTIN
// VT_RET* nicht pushen !
//
//    Rev 1.2   25 Apr 1996 15:35:20   MARTIN
// AnzParam kann jetzt auch keine Parameter richtig
//
//    Rev 1.1   19 Apr 1996 17:58:52   MARTIN
// WriteWindowHandle aufgerufen
//
//    Rev 1.0   19 Apr 1996 17:46:50   MARTIN
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "ddsmsg.h"
#include "dds.hpp"
#include "globmem.h"

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

#include "cfield.hpp"
#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "tbcbd.hpp"

#define MODULENUM 164
#include "winass.hpp"

extern "C" {
#include "cbdesc.h"
}
#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"

#include "jni.h"
#include "jmwrap.h"

struct ProcList {
  struct ProcList FAR *next;
  char ProcName[64];
  FARPROC ProcPtr;
  };

typedef ProcList FAR *LPPROCLIST;

typedef BOOL (CALLBACK*     FILTERPROC)(LPMSG msg);
struct DllList {
  struct DllList FAR *next;
  char DllName[64];
  HINSTANCE DllHandle;
  LPPROCLIST Procs;
  FILTERPROC FilterDLLMsg;
  FARPROC ProcessDLLIdle;
  };
typedef DllList FAR *LPDLLLIST;

static LPDLLLIST LoadedDlls = NULL;

FARPROC GetProcPtr(LPSTR DllName,LPSTR ProcName,BOOL WithWinAssert)
  {
  for (LPDLLLIST dll = LoadedDlls; dll != NULL; dll = dll->next)
    if (!lstrcmp(dll->DllName,DllName)) break;
  if (dll == NULL) {
    HINSTANCE newDll = LoadLibrary(DllName);
#ifdef WIN32
    if (newDll != NULL) {
#else
    if (newDll >= HINSTANCE_ERROR) {
#endif
      dll = (LPDLLLIST)GetGlobMem(sizeof(DllList));
      lstrcpy(dll->DllName,DllName);
      dll->DllHandle = newDll;
      dll->next = LoadedDlls;
      dll->FilterDLLMsg = FILTERPROC (GetProcAddress(dll->DllHandle,"FilterDllMsg"));
      dll->ProcessDLLIdle = GetProcAddress (dll->DllHandle,"ProcessDllIdle");
      LoadedDlls = dll;
      }
    else {
      if (WithWinAssert) {
        char Meldung[128];
        sprintf(Meldung,"kann %s nicht finden oder laden (Fehler %d)",DllName,newDll);
        DBWIN_ASSERT_TEXT(FALSE,Meldung);
        }
      return NULL;
      }
    }
  for (LPPROCLIST proc = dll->Procs; proc != NULL; proc = proc->next)
    if (!lstrcmp(proc->ProcName,ProcName)) break;
  if (proc == NULL) {
    FARPROC newProc = GetProcAddress(dll->DllHandle,ProcName);
    if (newProc != NULL) {
      proc = (LPPROCLIST)GetGlobMem(sizeof(ProcList));
      lstrcpy(proc->ProcName,ProcName);
      proc->ProcPtr = newProc;
      proc->next = dll->Procs;
      dll->Procs = proc;
      }
    else {
      if (WithWinAssert) {
        char Meldung[128];
        sprintf(Meldung,"Prozedur %s in %s nicht definiert",ProcName,DllName);
        DBWIN_ASSERT_TEXT(FALSE,Meldung);
        }
      return NULL;
      }
    }
  return proc->ProcPtr;
  }

#pragma pack(1)
struct FAR FreeExternDll_param {
  WORD parSize;
  DWORD DllName;
  };
#pragma pack()

BOOL FreeExternDll (mdiChild *c,LPVOID param,WORD mode)
  {
  FreeExternDll_param FAR *par = (FreeExternDll_param FAR *) param;
  if (mode & EM_LOAD) {
    LPSTR DllName = (LPSTR) c->ReadlData (par->DllName);
    LPDLLLIST last = NULL;
    for (LPDLLLIST dll = LoadedDlls; dll != NULL; dll = dll->next) {
      if (!lstrcmp(dll->DllName,DllName)) {
        if (last == NULL)
          LoadedDlls = dll->next;
        else
          last->next = dll->next;
        LPPROCLIST proc = dll->Procs;
        while (proc != NULL) {
          LPPROCLIST proctofree = proc;
          proc = proc->next;
          FreeGlobMem(proctofree);
          }
        FreeLibrary(dll->DllHandle);
        FreeGlobMem(dll);
        break;
        }
      last = dll;
      }
    }
  return FALSE;
  }

void FreeAllExternDlls(void)
  {
  LPDLLLIST dll = LoadedDlls;
  while (dll != NULL) {
    LPDLLLIST dlltofree = dll;
    dll = dll->next;
    LPPROCLIST proc = dlltofree->Procs;
    while (proc != NULL) {
      LPPROCLIST proctofree = proc;
      proc = proc->next;
      FreeGlobMem(proctofree);
      }
    FreeLibrary(dlltofree->DllHandle);
    FreeGlobMem(dlltofree);
    }
  }

#define VAR_LEN_DEFAULT 256
#define VAR_LEN(x) WORD(x)
#define VAR_TYPE(x) ((x) & 0x00FF0000)
#define VT_WORD            0x00010000
#define VT_DWORD           0x00020000
#define VT_LPIN            0x00030000
#define VT_LPOUTFIX        0x00040000
#define VT_LPOUTVAR        0x00050000
#define VT_RETWORD         0x00060000
#define VT_RETDWORD        0x00070000
#define SET_CONNECTION     0x01000000
#define INIT_LPOUT         0x02000000

struct FAR CallDllParam {
  DWORD VarInfo;
  DWORD Data;
  };

#pragma pack(1)
struct FAR CallDllProc_param {
  WORD parSize;
  DWORD DllName;
  DWORD ProcName;
  CallDllParam p[1];

  int AnzParam ()
    { return (parSize - (sizeof(*this) - sizeof (p[0]))) / sizeof (p[0]) ; }
  };
#pragma pack()

struct CallDllParamInfo {
  DWORD VarInfo;
  DWORD ValToPush;
  };
typedef CallDllParamInfo FAR *LPCDPI;

extern LPVOID GetLastOffset (void);
extern BOOL IsInExternCall;

extern BOOL InClientTransaction;
extern BOOL CallCommandInClientTransaction;

BOOL CallDllProc (mdiChild *c,LPVOID param,WORD mode,BOOL C_Konvention,BOOL CondProc,BOOL dynamic)
  {
  BOOL res = FALSE;
  LPVOID Offset;
  if (CondProc)
    Offset = GetLastOffset();
  else
    Offset = LPSTR(param)-sizeof(WORD);
  CallDllProc_param FAR *par = (CallDllProc_param FAR *) param;
  int AnzParam = par->AnzParam();
  if ((mode & (EM_LOAD | EM_UPDATE)) || ((dynamic) && (mode & (EM_CLEAR | EM_RESET)))) {
    LPSTR DllName = (LPSTR) c->ReadlData (par->DllName);
    LPSTR ProcName = (LPSTR) c->ReadlData (par->ProcName);
    DBWIN_ASSERT_TEXT((DllName != NULL) && (ProcName != NULL),"CallDllProc: DllName oder ProcName fehlt");
    LPCDPI ParamList = (LPCDPI)GetGlobMem(((AnzParam * 2) + 1) * sizeof(CallDllParamInfo));
    int AnzParsToPush = 0;
    if (dynamic) {  // als erstes den mode uebergeben
      ParamList[AnzParsToPush].VarInfo = VT_WORD;
      ParamList[AnzParsToPush].ValToPush = mode;
      AnzParsToPush++;
      }
    for (int i = 0 ; i < AnzParam ; i++) {
      LPDWORD lpVarInfo = (LPDWORD)c->ReadlData (par->p[i].VarInfo);
      DBWIN_ASSERT_TEXT(lpVarInfo != NULL,"CallDllProc: VarInfo ist NULL");
      ParamList[AnzParsToPush].VarInfo = *lpVarInfo;
      switch (VAR_TYPE(*lpVarInfo)) {
        case VT_WORD:
          {
          LPWORD lpw = (LPWORD) c->ReadlData(par->p[i].Data);
          DBWIN_ASSERT_TEXT(lpw != NULL,"CallDllProc: Wertparameter ist NULL");
          ParamList[AnzParsToPush].ValToPush = *lpw;
          }
          break;
        case VT_DWORD:
          {
          LPDWORD lpdw = (LPDWORD) c->ReadlData(par->p[i].Data);
          DBWIN_ASSERT_TEXT(lpdw != NULL,"CallDllProc: Wertparameter ist NULL");
          ParamList[AnzParsToPush].ValToPush = *lpdw;
          }
          break;
        case VT_LPIN:
          {
          LPVOID lp = c->ReadlData(par->p[i].Data);
          ParamList[AnzParsToPush].ValToPush = (DWORD)lp;
          }
          break;
        case VT_LPOUTFIX:
        case VT_LPOUTVAR:
          {
          WORD size = VAR_LEN(*lpVarInfo);
          LPVOID lp;
          WORD oldsize;
          if (*lpVarInfo & INIT_LPOUT) {
            lp = c->ReadlData(par->p[i].Data);
            oldsize = GetBlockSize(lp);
            if (oldsize > size) size = oldsize;
            }
          if (size == 0) size = VAR_LEN_DEFAULT;
          LPVOID buf = GetGlobMem(size);
          if (*lpVarInfo & INIT_LPOUT) {
            if (lp != NULL) lmemcpy(buf,lp,oldsize);
            }
          ParamList[AnzParsToPush].ValToPush = (DWORD)buf;
          if (VAR_TYPE(*lpVarInfo) == VT_LPOUTVAR) {
            LPWORD lpsize = (LPWORD) GetGlobMem(sizeof(WORD));
            *lpsize = size;
            AnzParsToPush++;
            ParamList[AnzParsToPush].VarInfo = VT_LPOUTVAR;
            ParamList[AnzParsToPush].ValToPush = (DWORD)lpsize;
            }
          }
          break;
        case VT_RETWORD:
        case VT_RETDWORD:
          break;
        default:
          DBWIN_ASSERT_TEXT(FALSE,"CallDllProc: unbekannter Variablentyp");
        }
      AnzParsToPush++;
      }
    WORD PushedSize = 0;
#ifndef WIN32
    if (C_Konvention) {
#endif
      for (i = AnzParsToPush - 1; i >= 0; i--) {
        if ((VAR_TYPE(ParamList[i].VarInfo) != VT_RETWORD) &&
            (VAR_TYPE(ParamList[i].VarInfo) != VT_RETDWORD)) {
          if (VAR_TYPE(ParamList[i].VarInfo) == VT_WORD) {
            WORD WordToPush = WORD(ParamList[i].ValToPush);
#ifdef WIN32
            __asm push DWORD PTR WordToPush;
            PushedSize += sizeof(DWORD);
#else
            __asm push WORD PTR WordToPush;
            PushedSize += sizeof(WORD);
#endif
            }
          else {
            DWORD DWordToPush = ParamList[i].ValToPush;
#ifdef WIN32
            __asm push DWORD PTR DWordToPush;
#else
            __asm push WORD PTR DWordToPush+2;
            __asm push WORD PTR DWordToPush;
#endif
            PushedSize += sizeof(DWORD);
            }
          }
        }
#ifndef WIN32
      }
    else {
      for (i = 0; i < AnzParsToPush; i++) {
        if ((VAR_TYPE(ParamList[i].VarInfo) != VT_RETWORD) &&
            (VAR_TYPE(ParamList[i].VarInfo) != VT_RETDWORD)) {
          if (VAR_TYPE(ParamList[i].VarInfo) == VT_WORD) {
            WORD WordToPush = WORD(ParamList[i].ValToPush);
#ifdef WIN32
            __asm push DWORD PTR WordToPush;
            PushedSize += sizeof(DWORD);
#else
            __asm push WORD PTR WordToPush;
            PushedSize += sizeof(WORD);
#endif
            }
          else {
            DWORD DWordToPush = ParamList[i].ValToPush;
#ifdef WIN32
            __asm push DWORD PTR DWordToPush;
#else
            __asm push WORD PTR DWordToPush+2;
            __asm push WORD PTR DWordToPush;
#endif
            PushedSize += sizeof(DWORD);
            }
          }
        }
      }
#endif
    DWORD RetVal = (*GetProcPtr(DllName,ProcName,TRUE)) ();
    if (C_Konvention) {
#ifdef WIN32
      DWORD DPushedSize = DWORD(PushedSize);
      __asm add esp,DWORD PTR DPushedSize;
#else
      __asm add sp,WORD PTR PushedSize;
#endif
      }
    if (CondProc)
      res = BOOL(RetVal);
    AnzParsToPush = 0;
    if (dynamic)
      AnzParsToPush++;
    for (i = 0 ; i < AnzParam ; i++) {
      switch (VAR_TYPE(ParamList[AnzParsToPush].VarInfo)) {
        case VT_WORD:
        case VT_DWORD:
        case VT_LPIN:
          break;
        case VT_LPOUTFIX:
        case VT_LPOUTVAR:
          {
          LPVOID buf = (LPVOID)ParamList[AnzParsToPush].ValToPush;
          WORD size = GetBlockSize(buf);
          if (VAR_TYPE(ParamList[AnzParsToPush].VarInfo) == VT_LPOUTVAR) {
            AnzParsToPush++;
            LPWORD lpsize = (LPWORD) ParamList[AnzParsToPush].ValToPush;
            DBWIN_ASSERT_TEXT(*lpsize <= size,"CallDllProc: Datenbuffer war zu klein !");
            size = *lpsize;
            FreeGlobMem(lpsize);
            }
          if (size > 0)
            c->WritelData (par->p[i].Data,buf,size,Offset);
          else
            c->DellData (par->p[i].Data,Offset);
          FreeGlobMem(buf);
          }
          break;
        case VT_RETWORD:
          {
          WORD RetWord = WORD(RetVal);
          c->WritelData (par->p[i].Data,&RetWord,sizeof(WORD),Offset);
          }
          break;
        case VT_RETDWORD:
          c->WritelData (par->p[i].Data,&RetVal,sizeof(DWORD),Offset);
          break;
        }
      AnzParsToPush++;
      }
    FreeGlobMem(ParamList);
    }
  if (mode & EM_FIXCONNECTION) {
    for (int i = 0 ; i < AnzParam ; i++) {
      LPDWORD lpVarInfo = (LPDWORD)c->ReadlData (par->p[i].VarInfo);
      if ((*lpVarInfo & SET_CONNECTION) != 0L)
        c->SetlConnection (par->p[i].Data,Offset);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    // wegen moeglicher Expressions auf jeden Fall fuer alle Parameter ClearConnection !
    for (int i = 0 ; i < AnzParam ; i++) {
      c->ClearlConnection (par->p[i].VarInfo,Offset);
      c->ClearlConnection (par->p[i].Data,Offset);
      }
    }
  return res ;
  }

BOOL TestDllProc (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    CallDllProc_param FAR *par = (CallDllProc_param FAR *) param;
    LPSTR DllName = (LPSTR) c->ReadlData (par->DllName);
    LPSTR ProcName = (LPSTR) c->ReadlData (par->ProcName);
    DBWIN_ASSERT_TEXT((DllName != NULL) && (ProcName != NULL),"TestDllProc: DllName oder ProcName fehlt");
    if (GetProcPtr(DllName,ProcName,FALSE) != NULL)
      res = TRUE;
    }

  return res;
  }

BOOL CallDllProcP (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallDllProc(c,param,mode,FALSE,FALSE,FALSE);
  }

BOOL CallDllProcC (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallDllProc(c,param,mode,TRUE,FALSE,FALSE);
  }

BOOL CallDllBoolProcP (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallDllProc(c,param,mode,FALSE,TRUE,FALSE);
  }

BOOL CallDllBoolProcC (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallDllProc(c,param,mode,TRUE,TRUE,FALSE);
  }

BOOL CallDllProcDynamic (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallDllProc(c,param,mode,TRUE,FALSE,TRUE);
  }


// Implementierung von ExternWindow:
#pragma pack(1)
struct FAR ExtWindow_param {
  tool_header hd;
  // weitere Abmessungen und aehnliches
  DWORD Disable;
  LONG  w,h;
  DWORD WindowHandle;
  DWORD doGray;
  void WriteWindowHandle (mdiChild *c,HWND hWnd)
    {
    c->WritelData (WindowHandle,&hWnd,sizeof(HWND),LPSTR(this) - sizeof(WORD));
    }
  BOOL mitGray ()
    {
    return (hd.structSize >= sizeof(*this) - sizeof(WORD));
    }
  };
#pragma pack()

void ExtWndRegister ();
class FAR ExtWinObj : public wobj {
 public :
  ExtWindow_param FAR *par;
  LPMDICHILD parent;
  HWND MyWnd;
  ExtWinObj (LPVOID param,mdiChild *doc,HWND hParent,int x,int y,int w,int h);
  HWND Create (HWND hParent,int x,int y,int w,int h,BOOL useGray);
  ~ExtWinObj ();
  };
typedef ExtWinObj FAR *LPEXTDOCOBJ;

LPSTR ExtWindowClass = "EWC";
LPSTR ExtWindowClassG = "EWCG";

DLLExport LONG _export FAR PASCAL ExtWindowProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
#ifdef UEBERLEGT
  LONG RetVal ;
  mdiChild *pmdich = GetWindowInst(hWnd);
  switch (msg) {
    case WM_CREATE:
      {
      LPCREATESTRUCT lpCreate = LPCREATESTRUCT (lP);
      SetWindowLong(hWnd, GWL_HWINFO, LONG(lpCreate->lpCreateParams));
      pmdich = LPMDICHILD (lpCreate->lpCreateParams) ;
      pmdich->DefaultHandler_base = (FARPROC) DefWindowProc;
      }
      break;

    default:
      BOOL done = FALSE ;
      if (pmdich != NULL)
        RetVal = pmdich->ChildProc (hWnd,msg,wP,lP,&done);
      if (!done)
        RetVal = DefWindowProc(hWnd, msg, wP, lP);
      break;
    }
  return RetVal ;
#else
  return DefWindowProc(hWnd, msg, wP, lP);
#endif
  }

void ExtWndRegister ()
  {
  static BOOL Registered,RegisteredG;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = ExtWindowProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(LPMDICHILD) ;
    wndclass.hInstance     = (HINSTANCE)WBase::hInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = ExtWindowClass ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  if (!RegisteredG) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = ExtWindowProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(LPMDICHILD) ;
    wndclass.hInstance     = (HINSTANCE)WBase::hInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = ExtWindowClassG ;

    RegisterClass (&wndclass) ;
    RegisteredG = TRUE ;
    }
  }

static WORD extchildid = 0xA000;
HWND ExtWinObj::Create (HWND hParent,int x,int y,int w,int h,BOOL doGray)
  {
  HWND res = CreateWindow ((doGray) ? ExtWindowClassG : ExtWindowClass,"",WS_CHILDWINDOW,
                           x,y,w,h,
                           hParent,
                           HMENU(extchildid++),
                           WBase::hInstance,
//                           LPVOID(parent)
                           NULL
                          ) ;
  return res;
  }

ExtWinObj::ExtWinObj (LPVOID param,mdiChild *doc,HWND hParent,int x,int y,int w,int h)
  {
  par = (ExtWindow_param FAR *) param ;
  parent = doc;
  ExtWndRegister ();
  BOOL doGray = FALSE;
  if (par->mitGray ()) {
    DBINT FAR *lpdoGray = (DBINT FAR *) (doc->ReadlData (par->doGray)) ;
    if (lpdoGray != NULL) doGray = *lpdoGray;
    }
  MyWnd = Create (hParent,x,y,w,h,doGray);
  par->WriteWindowHandle(doc,MyWnd);
  }

ExtWinObj::~ExtWinObj ()
  {
  DestroyWindow (MyWnd);
  }

DLLExport void _export WINAPI lShowExtWindow (LPVOID param,WORD Action,LPDEPAR p)
  {
  ExtWinObj FAR *obj;
  switch (Action) {
    case DO_LOAD:
      obj = new ExtWinObj (param,LPTBD(p->load.privData)->c,p->load.hWParent,p->load.x,p->load.y,p->load.w,p->load.h);
      p->load.objData = obj;
      p->load.hWnd = obj->MyWnd;
      break ;
    case DO_RESET:
      DBWIN_ASSERT (p->reset.objData != NULL);
      obj = (ExtWinObj FAR *) p->reset.objData;
      delete obj;
      p->reset.objData = NULL ;
      break ;
    case DO_ACTIVATE:
      if (p->activate.flag) {
        DBWIN_ASSERT (p->activate.objData != NULL);
        obj = (ExtWinObj FAR *) p->activate.objData;
        ShowWindow (obj->MyWnd,SW_NORMAL);
        }
      break ;
#ifdef UEBERLEGT
    case DO_SETFOCUS:
      obj = (ExtWinObj FAR *) p->focus.objData;
      if (p->focus.mode == FOCUSMODE_FORWARD) {
        p->focus.done = TRUE ;
        SetFocus (obj->MyWnd);
        }
      else if (p->focus.mode == FOCUSMODE_BACKWARD) {
        p->focus.done = TRUE ;
        SetFocus (obj->MyWnd);
        }
      break ;
#endif
    }
  }


BOOL FAR PASCAL FilterDLLMsgForExternDLL (LPMSG lpMsg)
  {
  BOOL res = FALSE ;
  for (LPDLLLIST dll = LoadedDlls; ((dll != NULL) && (!res)) ; dll = dll->next)
    if (dll->FilterDLLMsg != NULL)
      res = (*dll->FilterDLLMsg) (lpMsg);
  return res ;
  }

void FAR PASCAL ProcessDLLIdleForExternDLL()
  {
  for (LPDLLLIST dll = LoadedDlls; dll != NULL; dll = dll->next) {
    if (dll->ProcessDLLIdle != NULL)
      (*dll->ProcessDLLIdle) ();
    }
  }

BOOL ExeIs32Bit (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef WIN32
  return TRUE;
#else
  return FALSE;
#endif
  }

#define ENTER1(A)   if (ExtraData != NULL) { \
                      SAVEREC old; \
                      c->SetRecsForUpdate (old,ExtraData); \
                      SetExtraInfo s(c,ExtraData); \
                      c->_GetRecExtra()->cmdBase = c->GetCmdBase();     \
                      c->_GetRecExtra()->cOffs = 0;     \
                      A ; \
                      c->RestoreRecs(old);  \
                      } \
                    else { \
                      RestoreListFnc rlf (c);  \
                      A ; \
                      }
#define ENTER1DEB(A)    if (ExtraData != NULL) { \
                          SAVEREC old; \
                          c->SetRecsForUpdate (old,ExtraData); \
                          SetExtraInfo s(c,ExtraData); \
                          PushToCallStack (c,c->schd->fName,c->GetCmdOffset (par)); \
                          c->_GetRecExtra()->cmdBase = c->GetCmdBase();     \
                          c->_GetRecExtra()->cOffs = 0;     \
                          A ; \
                          c->RestoreRecs(old);  \
                          } \
                        else { \
                          PushToCallStack (c,c->schd->fName,c->GetCmdOffset (par)); \
                          RestoreListFnc rlf (c);  \
                          A ; \
                          }

extern "C" {
DLLExport void _export FAR PASCAL ScriptCallBack (LPVOID Desc, WORD AnzPars, LPWORD ParLen, LPVOID FAR *Param)
  {
  LPCBDESC cbd = (LPCBDESC)Desc;
  DBWIN_ASSERT(AnzPars <= cbd->AnzPars);
  mdiChild FAR *c = (mdiChild FAR *)cbd->c;
  LPCONNEXTRAINFO ExtraData;
  LPVOID par = cbd->Offset;
  if (cbd->ExtraSize > 0)
    ExtraData = LPCONNEXTRAINFO(cbd->Ref + AnzPars);
  else
    ExtraData = NULL;

#ifdef UEBERLEGT
  for (WORD i = 0; i < AnzPars; i++) {
    if ((ParLen[i] == 0) || (Param[i] == NULL))
      c->DellData(cbd->Ref[i],0);
    else
      c->WritelData(cbd->Ref[i],Param[i],ParLen[i],0);
    }
  c->ExCuteProc (cbd->proc,EM_LOAD | EM_CHANGETOTRUE);
  c->ExCuteProc (cbd->proc,EM_RESET);
#endif
#ifdef DEBUG
  ENTER1DEB (
            for (WORD i = 0; i < AnzPars; i++) {
              if ((ParLen[i] == 0) || (Param[i] == NULL))
                c->DellData(cbd->Ref[i],0);
              else
                c->WritelData(cbd->Ref[i],Param[i],ParLen[i],0);
              }
            c->ExCuteProc (cbd->proc,EM_LOAD | EM_CHANGETOTRUE);
            c->ExCuteProc (cbd->proc,EM_RESET);
            ) ;
#else
  ENTER1 (
         for (WORD i = 0; i < AnzPars; i++) {
           if ((ParLen[i] == 0) || (Param[i] == NULL))
             c->DellData(cbd->Ref[i],0);
           else
             c->WritelData(cbd->Ref[i],Param[i],ParLen[i],0);
           }
         c->ExCuteProc (cbd->proc,EM_LOAD | EM_CHANGETOTRUE);
         c->ExCuteProc (cbd->proc,EM_RESET);
         ) ;
#endif
#ifdef DEBUG
  PopFromCallStack ();
#endif
  }
}

#pragma pack(1)
struct FAR CreateCBDesc_param {
  WORD parSize;
  DWORD desc;
  DWORD proc;
  DWORD p[1];

  int AnzParam ()
    { return (parSize - (sizeof(*this) - sizeof (p[0]))) / sizeof (p[0]) ; }
  };
#pragma pack()

BOOL CreateCBDesc (mdiChild *c,LPVOID param,WORD mode)
  {
  CreateCBDesc_param FAR *par = (CreateCBDesc_param FAR *) param;
  if (mode & EM_LOAD) {
    int AnzPars = par->AnzParam();
    LPVOID ExtraData = c->_GetRecExtra();
    int ExtraSize = GetBlockSize(ExtraData);
    LPCBDESC cbd = (LPCBDESC)GetGlobMem((sizeof(CBDesc) - sizeof(DWORD)) + (AnzPars * sizeof(DWORD)) + ExtraSize);
    cbd->scb = ScriptCallBack;
    cbd->c = (LPVOID)c;
    cbd->proc = par->proc;
    cbd->Offset = LPSTR(param)-sizeof(WORD);
    cbd->AnzPars = (WORD)AnzPars;
    for (int i = 0; i < AnzPars; i++)
      cbd->Ref[i] = par->p[i];
    if (ExtraSize > 0)
      lmemcpy(cbd->Ref + AnzPars,ExtraData,ExtraSize);
    c->WritelData(par->desc,cbd,GetBlockSize(cbd),LPSTR(param)-sizeof(WORD));
    FreeGlobMem(cbd);
    }
  return FALSE;
  }

#pragma pack(1)
struct FAR DataFromPointer_param {
  WORD parSize;
  DWORD res;
  DWORD ptr;
  DWORD len;   // optional, wenn nicht angegeben -> zero-terminated string
  };
#pragma pack()

BOOL DataFromPointer (mdiChild *c,LPVOID param,WORD mode)
  {
  DataFromPointer_param FAR *par = (DataFromPointer_param FAR *) param;
  if (mode & EM_LOAD) {
    LPVOID ptr = c->ReadlData (par->ptr);
    if (ptr != NULL)
      ptr = *(LPVOID FAR *)ptr;
    WORD len;
    if (ptr != NULL) {
      if (par->parSize >= sizeof(*par)) {
        LPWORD lplen = (LPWORD)c->ReadlData (par->len);
        if (lplen != NULL)
          len = *lplen;
        else
          len = 0;
        }
      else
        len = lstrlen((LPSTR)ptr) + 1;
      }
    else
      len = 0;
    if (len > 0)
      c->WritelData(par->res,ptr,len,LPSTR(param)-sizeof(WORD));
    else
      c->DellData(par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct FAR ClientExtWindow_param {
  WORD parSize;
  DWORD hWnd;
  DWORD hWndRes;
  };
#pragma pack()

BOOL ClientExtWindow (mdiChild *c,LPVOID param,WORD mode)
  {
  ClientExtWindow_param FAR *par = (ClientExtWindow_param FAR *) param;
  if (mode & EM_LOAD) {
    ExtWndRegister ();
    RECT r;
    GetClientRect (c->OutWnd(),&r);
    HWND res = CreateWindow (ExtWindowClassG,"",WS_CHILDWINDOW,
                             0,0,r.right,r.bottom,
                             c->OutWnd(),
                             HMENU(extchildid++),
                             WBase::hInstance,
                             NULL
                            ) ;
    par->hWnd = DWORD(res);
    c->WritelData (par->hWndRes,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    DestroyWindow (HWND(par->hWnd));
    }
  return FALSE;
  }

#pragma pack(1)
struct Jmethod_param {
  WORD  parSize;
  DWORD retVal;
  DWORD object;
  DWORD method;
  DWORD signature;
  DWORD par[1];
  int anzPars ()
    {
    return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(par[0]);
    }
  };

struct Jstaticmethod_param {
  WORD  parSize;
  DWORD retVal;
  DWORD classname;
  DWORD method;
  DWORD signature;
  DWORD par[1];
  int anzPars ()
    {
    return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(par[0]);
    }
  };

struct Jnew_param {
  WORD  parSize;
  DWORD retVal;
  DWORD classname;
  DWORD signature;
  DWORD par[1];
  int anzPars ()
    {
    return (parSize - (sizeof (*this) - sizeof(DWORD))) / sizeof(par[0]);
    }
  };

struct Jnewstring_param {
  WORD  parSize;
  DWORD retVal;
  DWORD par;
  };

struct Jdelete_param {
  WORD  parSize;
  DWORD object;
  };

struct Jstartvm_param {
  WORD  parSize;
  DWORD vmpath;
  DWORD classpath;
  DWORD debug_param;
  DWORD extra_option;
  };

struct Jsetfocus_param {
  WORD  parSize;
  DWORD hwnd;
  };

struct Jcatchexception_param {
  WORD  parSize;
  DWORD exceptionobject;
  };

struct Jlogexception_param {
  WORD  parSize;
  DWORD exceptionobject;
  };

struct Jinstanceof_param {
  WORD  parSize;
  DWORD object;
  DWORD classname;
  };

struct Jmethodexists_param {
  WORD  parSize;
  DWORD object;
  DWORD method;
  DWORD signature;
  };

struct Jstaticmethodexists_param {
  WORD  parSize;
  DWORD classname;
  DWORD method;
  DWORD signature;
  };

struct JBmethodexists_param {
  WORD  parSize;
  DWORD res;
  DWORD object;
  DWORD method;
  DWORD signature;
  };

struct JBstaticmethodexists_param {
  WORD  parSize;
  DWORD res;
  DWORD classname;
  DWORD method;
  DWORD signature;
  };

struct Jgetarraylength_param {
  WORD  parSize;
  DWORD retVal;
  DWORD array;
  };

struct Jgetobjarrayelement_param {
  WORD  parSize;
  DWORD retVal;
  DWORD array;
  DWORD index;
  DWORD type;
  };

struct Jsetreplacemode_param {
  WORD  parSize;
  DWORD mode;
  };

#pragma pack()

static BOOL doReplace = FALSE;
static DWORD replaceMode = 0L;

#ifdef WAS_SOLL_ERSETZT_WERDEN
ag/gwi/co2/shared/Session                               com/agfa/hap/base/Session
ag/gwi/co2/shared/Cache                                 com/agfa/hap/base/Cache
ag/gwi/co2/shared/Identifiable                          com/agfa/hap/base/Identifiable
ag/gwi/co2/shared/GWISession                            com/agfa/hap/base/GWISession

ag/gwi/co2/datadriven                                   com/agfa/hap/base/datadriven
ag/gwi/co2/types                                        com/agfa/hap/base/types

ag/gwi/co2/framework/PKCatalog                          com/agfa/hap/base/catalog/PKCatalog

ag/gwi/co2/framework/flexdata                           com/agfa/hap/base/app/flexdata
ag/gwi/co2/framework/form                               com/agfa/hap/base/app/form
ag/gwi/app/usrmessage                                   com/agfa/hap/base/app/usrmessage

ag/gwi/co2/framework/system                             com/agfa/hap/base/app

/*
ag/gwi/co2/framework/system/PKFacility                  com/agfa/hap/base/app/PKFacility
ag/gwi/co2/framework/system/Facility                    com/agfa/hap/base/app/Facility
ag/gwi/co2/framework/system/PKBaseMedicalCase           com/agfa/hap/base/app/PKBaseMedicalCase
ag/gwi/co2/framework/system/PKBaseOutpatientMedicalCase com/agfa/hap/base/app/PKBaseOutpatientMedicalCase
ag/gwi/co2/framework/system/OrganisationalUnit          com/agfa/hap/base/app/OrganisationalUnit
ag/gwi/co2/framework/system/security                    com/agfa/hap/base/app/security
ag/gwi/co2/framework/system/request                     com/agfa/hap/base/app/request
*/

ag/gwi/co2/repgen                                       com/agfa/hap/base/tools/repgen
ag/gwi/co2/framework                                    com/agfa/hap/base

ag/gwi/co2/components                                   com/agfa/hap/ui/components
ag/gwi/co2/swing                                        com/agfa/hap/ui/swing

ag/gwi/co2/util/xml                                     com/agfa/hap/share/xml
ag/gwi/co2/tool/transfer                                com/agfa/hap/share/transfer

ag/gwi/app/arden                                        com/agfa/hap/metatools/experter
#endif

BOOL stringEqual(LPTSTR *lpptr, LPTSTR str, BOOL movePtr)
  {
  LPTSTR ptr = *lpptr;
  while (*str) {
    if ((!*ptr) || (*str++ != *ptr++))
      return FALSE;
    }
  if (movePtr)
    *lpptr = ptr;
  return TRUE;
  }

void concatNextPart(LPTSTR *ret, LPTSTR *retptr, LPTSTR src, LPTSTR cptr, LPTSTR toStr)
  {
  if (*ret == NULL) {
    *ret = (LPTSTR)GetGlobMem(1024*sizeof(TCHAR));  // sollte auch fuer laengere Signaturen reichen
    *retptr = *ret;
    }
  LPTSTR dst = *retptr;
  // eventuell den Text vor "com.agfa.hap..." kopieren
  while (src < cptr)
    *dst++ = *src++;
  // den toStr dazu
  while (*toStr)
    *dst++ = *toStr++;
  *retptr = dst;
  }

// Ergebnis muss mit FreeGlobMem freigegeben werden, wenn es sich vom Parameter from unterscheidet!
LPTSTR replaceClassName(LPTSTR from)
  {
  if (from == NULL)
    return NULL;
  LPTSTR ret = NULL;
  LPTSTR retptr;
  if (replaceMode == 1L) {  // ag.gwi.co2 to com.agfa.hap migration
    LPTSTR begin = from;
    LPTSTR ptr = from;
    while (*ptr) {
      while (*ptr && (*ptr != 'c')) ptr++;
      LPTSTR cptr = ptr;
      if ((*  ptr == 'c') &&
          (*++ptr == 'o') &&
          (*++ptr == 'm') &&
          (*++ptr == '/') &&
          (*++ptr == 'a') &&
          (*++ptr == 'g') &&
          (*++ptr == 'f') &&
          (*++ptr == 'a') &&
          (*++ptr == '/') &&
          (*++ptr == 'h') &&
          (*++ptr == 'a') &&
          (*++ptr == 'p') &&
          (*++ptr == '/')) {
        ptr++;
        if ((*  ptr == 'b') &&
            (*++ptr == 'a') &&
            (*++ptr == 's') &&
            (*++ptr == 'e') &&
            (*++ptr == '/')) {
          ptr++;
          if (stringEqual(&ptr, _T("Session"), FALSE) ||
              stringEqual(&ptr, _T("Cache"), FALSE) ||
              stringEqual(&ptr, _T("Identifiable"), FALSE) ||
              stringEqual(&ptr, _T("GWISession"), FALSE)) {
            concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/shared/"));
            begin = ptr;
            }
          else if (stringEqual(&ptr, _T("datadriven"), FALSE) ||
              stringEqual(&ptr, _T("types"), FALSE)) {
            concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/"));
            begin = ptr;
            }
          else if (stringEqual(&ptr, _T("catalog/PKCatalog"), TRUE)) {
            concatNextPart(&ret, &retptr, begin, cptr,_T("ag/gwi/co2/framework/PKCatalog"));
            begin = ptr;
            }
          else if ((*  ptr == 'a') &&
                   (*++ptr == 'p') &&
                   (*++ptr == 'p') &&
                   (*++ptr == '/')) {
            ptr++;
            if (stringEqual(&ptr, _T("flexdata"), FALSE) ||
                stringEqual(&ptr, _T("form"), FALSE)) {
              concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/framework/"));
              begin = ptr;
              }
            else if (stringEqual(&ptr, _T("usrmessage"), FALSE)) {
              concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/app/"));
              begin = ptr;
              }
            else if (stringEqual(&ptr, _T("PKHumanBeing"), FALSE)) {
              concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/app/core/"));
              begin = ptr;
              }
            else {
              concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/framework/system/"));
              begin = ptr;
              }
            }
          else if (stringEqual(&ptr, _T("tools/repgen"), TRUE)) {
            concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/repgen"));
            begin = ptr;
            }
          else {
            concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/framework/"));
            begin = ptr;
            }
          }
        else if (stringEqual(&ptr, _T("ui/"), TRUE)) {
          concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/"));
          begin = ptr;
          }
        else if (stringEqual(&ptr, _T("share/xml"), TRUE)) {
          concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/util/xml"));
          begin = ptr;
          }
        else if (stringEqual(&ptr, _T("share/transfer"), TRUE)) {
          concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/co2/tool/transfer"));
          begin = ptr;
          }
        else if (stringEqual(&ptr, _T("metatools/experter"), TRUE)) {
          concatNextPart(&ret, &retptr, begin, cptr, _T("ag/gwi/app/arden"));
          begin = ptr;
          }
        }
      }
    if (ret != NULL)
      lstrcpy(retptr, begin);
    }
  return (ret != NULL) ? ret : from ;
  }

Jcatchexception_param *LastCatchExceptionPar = NULL;
mdiChild *LastCatchExceptionMdiChild = NULL;

typedef DWORD (* CONSTRUCTINTEGER)     (LPASTR type,LPASTR signature,DWORD val);
typedef DWORD (* CONSTRUCTFLOAT)       (LPASTR type,LPASTR signature,double val);
typedef DWORD (* CONSTRUCTDATE)        (LPASTR type,LPASTR signature,DWORD year,DWORD month,DWORD day);
typedef DWORD (* CONSTRUCTTIMESTAMP)   (LPASTR type,LPASTR signature,DWORD year,DWORD month,DWORD day,DWORD hour,DWORD minute,DWORD second);

LPASTR NextSig (LPASTR actSig)
  {
  while (*actSig == '[') actSig++;
  if (*actSig == 'L') {
    for ( ; ((*actSig) && (*actSig != ';')) ; actSig = actSig + 1) ;
    if (*actSig == ';')
      return actSig + 1;
    else
      return actSig;
    }
  else {
    if (*actSig)
      return actSig + 1;
    else
      return actSig;
    }
  }

BOOL myStrcmp (LPASTR txt1,LPASTR txt2)
  {
  for ( ; (*txt1 == *txt2 && *txt1 && *txt2) ; txt1 ++ , txt2 ++ ) ;
  if (*txt2 == '\0')
    return TRUE;
  else
    return FALSE;
  }

void JavaClassInkompatibel (LPASTR retSig, LPASTR cplType)
  {
  TCHAR msg[256];
  _stprintf (msg, _T("CPL-Returntyp %hs inkompatibel mit %hs."), retSig, cplType);
  DBWIN_ASSERT_TEXT (FALSE,msg);
  }

#define DeleteReference(ref) { Delete (ref); /*javaReferences--; now computed in JMODEL*/ }

void WriteRetVal (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, int retSize,
                  LPASTR readMethod, LPASTR readMethodSig)
  {
  if (RetVal->l != 0L) {
    jvalue res;
    memset (&res, 0, sizeof (res));
    CallMethodByName(RetVal->l, readMethod, readMethodSig, &res);
    DeleteReference (RetVal->l);
    c->WritelData (retVal,&res,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else
    c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
  }

void WriteIntegerData (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, LPASTR retSig,
                       int retSize, LPASTR readMethod, LPASTR readMethodSig)

  {
  if (strchr ("ZBCSIJ", *retSig) != NULL) { // Pruefung, ob es einer der primitiven Integer-Typen ist.
    // Integers sind angenehm. Einfach nur die vorderen Bytes nehmen und hoffen,
    // dass es keinen Overflow gibt. (Pruefung koennte man noch einbauen.)
    c->WritelData (retVal,RetVal,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (myStrcmp (retSig, "Ljava/lang/Integer")
           || myStrcmp (retSig, "Ljava/lang/Short")
           || myStrcmp (retSig, "Ljava/lang/Long")) {
    WriteRetVal (c, param, retVal, RetVal, retSize, readMethod, readMethodSig);
    }
  else if (myStrcmp (retSig, "Ljava/lang/Boolean") || myStrcmp(retSig, "Ljava/lang/Object")) {
    WriteRetVal (c, param, retVal, RetVal, retSize, "booleanValue", "()Z");
    }
  else {
    JavaClassInkompatibel ("short/long/flag", retSig);
    }
  }

void WriteFloatData (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, LPASTR retSig, int retSize)

  {
  // Bei Float und Double geht's leider nicht so leicht mit den Bytes abschneiden,
  // deswegen zwei Funktionen.
  if (*retSig == 'F') { // Float
    c->WritelData (retVal,RetVal,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (*retSig == 'D') { // Double
    float f = float (RetVal->d);
    c->WritelData (retVal,&f,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (strchr ("ZBCSIJ", *retSig) != NULL) { // Pruefung, ob es einer der primitiven Integer-Typen ist.
    float f = float (RetVal->j);
    c->WritelData (retVal,&f,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (myStrcmp (retSig, "Ljava/lang/Float")
           || myStrcmp (retSig, "Ljava/lang/Double")
           || myStrcmp (retSig, "Ljava/lang/Integer")
           || myStrcmp (retSig, "Ljava/lang/Short")
           || myStrcmp (retSig, "Ljava/lang/Long")
           || myStrcmp (retSig, "Ljava/lang/Object")) {
    WriteRetVal (c, param, retVal, RetVal, retSize, "floatValue", "()F");
    }
  else {
    JavaClassInkompatibel ("float", retSig);
    }
  }

void WriteDoubleData (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, LPASTR retSig, int retSize)

  {
  // Bei Float und Double geht's leider nicht so leicht mit den Bytes abschneiden,
  // deswegen zwei Funktionen.
  if (*retSig == 'D') { // Double
    c->WritelData (retVal,&RetVal,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (*retSig == 'F') { // Float
    double d = RetVal->f;
    c->WritelData (retVal,&d,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (strchr ("ZBCSIJ", *retSig) != NULL) { // Pruefung, ob es einer der primitiven Integer-Typen ist.
    double d = double (RetVal->j);
    c->WritelData (retVal,&d,retSize,LPBYTE(param) - sizeof(WORD));
    }
  else if (myStrcmp (retSig, "Ljava/lang/Float")
           || myStrcmp (retSig, "Ljava/lang/Double")
           || myStrcmp (retSig, "Ljava/lang/Integer")
           || myStrcmp (retSig, "Ljava/lang/Short")
           || myStrcmp (retSig, "Ljava/lang/Long")
           || myStrcmp (retSig, "Ljava/lang/Object")) {
    WriteRetVal (c, param, retVal, RetVal, retSize, "doubleValue", "()D");
    }
  else {
    JavaClassInkompatibel ("double", retSig);
    }
  }

void GetDateData (packdate FAR * pd, jvalue FAR * RetVal)
  {
  jvalue res;
  CallMethodByName(RetVal->l, "getYear", "()I", &res);
  pd->year = WORD(res.i) + 1900;
  CallMethodByName(RetVal->l, "getMonth", "()I", &res);
  pd->month = BYTE(res.i) + 1;
  CallMethodByName(RetVal->l, "getDate", "()I", &res);
  pd->day = BYTE(res.i);
  }

void GetTimeData (packtime FAR * pt, jvalue FAR * RetVal)
  {
  jvalue res;
  CallMethodByName(RetVal->l, "getHours", "()I", &res);
  pt->hour = BYTE(res.i);
  CallMethodByName(RetVal->l, "getMinutes", "()I", &res);
  pt->minute = BYTE(res.i);
  CallMethodByName(RetVal->l, "getSeconds", "()I", &res);
  pt->second = BYTE(res.i);
  pt->hundred_second = 0;
  }

void WriteDateData (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, LPASTR retSig, int retSize)

  {
  if (myStrcmp (retSig, "Ljava/util/Date") || myStrcmp (retSig, "Ljava/lang/Object")) {
    if (RetVal->l != 0L) {
      packdate FAR pd;
      GetDateData (&pd, RetVal);
      DeleteReference (RetVal->l);
      c->WritelData (retVal,&pd,retSize,LPBYTE(param) - sizeof(WORD));
      }
    else
      c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
    }
  else {
    JavaClassInkompatibel ("date", retSig);
    }
  }

void WriteDatetimeData (mdiChild *c,LPVOID param,DWORD retVal, jvalue FAR *RetVal, LPASTR retSig, int retSize)

  {
  if (myStrcmp (retSig, "Ljava/util/Date") || myStrcmp (retSig, "Ljava/lang/Object")) {
    if (RetVal->l != 0L) {
      packdatetime FAR pdt;
      GetDateData (&pdt.pd, RetVal);
      GetTimeData (&pdt.pt, RetVal);
      DeleteReference (RetVal->l);
      c->WritelData (retVal,&pdt,retSize,LPBYTE(param) - sizeof(WORD));
      }
    else
      c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
    }
  else {
    JavaClassInkompatibel ("datetime", retSig);
    }
  }

BOOL jnewCalled;
struct JParInfo {
  WORD  VarInfo;
  DWORD ValToPush;
  BOOL  jnewCalled;
  BOOL pushAdditionalVal;
  DWORD AdditionalValToPush;
  };

#define TYPE_METHOD         0
#define TYPE_CONSTRUCTOR    1
#define TYPE_STATICMETHOD   2

#define DBWIN_ASSERT_ERR(cond,text) { if (!(cond)) { error = TRUE; DBWIN_ASSERT_TEXT(FALSE,text); } }

void Jmethod_constructor (mdiChild *c,DWORD retVal,DWORD FAR *par,int anzPars,LPTSTR signature,LPTSTR method,DWORD object,int typeToCall,LPVOID param,FARPROC procToCall)
  {
  /*BOOL doLog = IsLogTypeEnabled(LOG_TYPE_JAVA);
  DWORD time;
  LPTSTR LogRetVal;
  if (doLog) {
    time = GetLogStartTime();
    LogRetVal = (LPTSTR)GetGlobMem(256*sizeof(TCHAR));
    lstrcpy(LogRetVal, _T("<none>"));
    }*/

  BOOL oldCatchNextException = GetCatchNextException();
  if (oldCatchNextException) {
    // recursive call -> catch only exceptions thrown by main call!
    SetCatchNextException(FALSE);
    }
  else {
    if (LastCatchExceptionPar != NULL) {
      SetCatchNextException(TRUE);
      }
    }

  int PushedSize = 0;
  JParInfo *ParamList = (JParInfo *)GetGlobMem(anzPars * sizeof(JParInfo));

  BOOL error = FALSE;
  DBWIN_ASSERT_ERR ((signature != NULL) && (method != NULL), _T("Signatur und Methode müssen angegeben sein")) ;

  BOOL logWithoutPars = FALSE;
  if (*method == '-') {
    method++;
    logWithoutPars = TRUE;
    }

#ifdef UNICODE
  LPASTR ansiSignature = UnicodeToAnsi (signature);
  LPASTR ansiMethod = UnicodeToAnsi (method);
#else
  LPASTR ansiSignature = signature;
  LPASTR ansiMethod = method;
#endif
  LPASTR actSig = ansiSignature + 1;     // Die Klammer weg..

  for ( int i = 0 ; i < anzPars ; i ++ ) {
    jnewCalled = FALSE;
    LPVOID val = c->ReadlData (par[i]); // Wertet auch Expressions aus und setzt jnewcalled auf TRUE falls Jnew oder Jmethod
    ParamList[i].jnewCalled = jnewCalled;
    ParamList[i].pushAdditionalVal = FALSE;
    WORD dataType;
    if ((val != NULL) || (*actSig != 'L')) {
      // if val is a NULL-constant and not an empty variable the following will crash.
      // But downward compatibility for VAR_DEC and VAR_QLONG leaves no other choice.
      dataType = c->GetDataType (par[i]);
      }
    else
      dataType = VAR_OBJ; // For val == NULL and an object signature dataType doesn't really matter.
    ParamList[i].VarInfo = dataType;
    DBWIN_ASSERT_ERR ((*actSig != ')') && (*actSig), _T("Mehr Parameter in Signatur als übergeben")) ;
    if ((dataType == VAR_LONG) || (dataType == VAR_STRARR) || (dataType == VAR_FLAG)) {
      // Haengt vom Datentyp ab -> muss noch ein konstruktor dafuer aufgerufen werden...
      //--------------------------------------------------------------------------------
      if (val) {
        DWORD lVal;
        if (dataType == VAR_LONG)
          lVal = * ((DWORD *) val);
        else
          lVal = * ((short *) val);

        if (*actSig == 'I') {
          ParamList[i].ValToPush = lVal;
          }
        else if (*actSig == 'J') {
          __int64 l;
          if (val)
            l = *((long *) val);
          else
            l = 0L; // not reachable
          LPDWORD lpl = (LPDWORD)&l;
          ParamList[i].ValToPush = lpl[0];
          ParamList[i].pushAdditionalVal = TRUE;
          ParamList[i].AdditionalValToPush = lpl[1];
          }
        else if (*actSig == 'Z') {
          ParamList[i].ValToPush = lVal;
          }
        else if (*actSig == 'S') {
          ParamList[i].ValToPush = lVal;
          }
        else if (myStrcmp (actSig, "Ljava/lang/Integer")) {
          ParamList[i].ValToPush = (* ((CONSTRUCTINTEGER) CallConstructor)) ("java/lang/Integer",  "(I)V",lVal);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else if (myStrcmp (actSig, "Ljava/lang/Long") || ((dataType == VAR_LONG) && myStrcmp(actSig, "Ljava/lang/Object"))) {
          TCHAR Nr[256];
          _stprintf (Nr, _T("%ld"),lVal);
          DWORD str = (DWORD)NewStringNative(Nr,lstrlen(Nr));
          /*javaReferences++; now computed in JMODEL*/
          ParamList[i].ValToPush = (* ((CONSTRUCTINTEGER) CallConstructor)) ("java/lang/Long", "(Ljava/lang/String;)V",str);
          DeleteReference ((jobject) str);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else if (myStrcmp (actSig, "Ljava/lang/Boolean") || ((dataType == VAR_FLAG) && myStrcmp(actSig, "Ljava/lang/Object"))) {
          ParamList[i].ValToPush = (* ((CONSTRUCTINTEGER) CallConstructor)) ("java/lang/Boolean", "(Z)V",lVal);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else if (myStrcmp (actSig, "Ljava/lang/Short") || ((dataType == VAR_STRARR) && myStrcmp(actSig, "Ljava/lang/Object"))) {
          ParamList[i].ValToPush = (* ((CONSTRUCTINTEGER) CallConstructor)) ("java/lang/Short", "(S)V",lVal);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else
          DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer short/long"));
        }
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_DATETIME) {
      // Muss der entsprechende Konstruktor aufgerufen werden...
      //--------------------------------------------------------------------------------
      if (val) {
        if (myStrcmp (actSig, "Ljava/util/Date") || myStrcmp(actSig, "Ljava/lang/Object")) {
          DWORD year = DWORD (((packdatetime FAR *) val)->pd.year) - 1900L;
          DWORD month = DWORD (((packdatetime FAR *) val)->pd.month) - 1L;
          DWORD day = ((packdatetime FAR *) val)->pd.day;
          DWORD hour = ((packdatetime FAR *) val)->pt.hour;
          DWORD minute = ((packdatetime FAR *) val)->pt.minute;
          DWORD second = ((packdatetime FAR *) val)->pt.second;
          ParamList[i].ValToPush = (* ((CONSTRUCTTIMESTAMP) CallConstructor)) ("java/util/Date", "(IIIIII)V",year,month,day,hour,minute,second);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else {
          DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer timestamp"));
          ParamList[i].ValToPush = 0L;
          }
        }
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_DATE) {
      // Muss der entsprechende Konstruktor aufgerufen werden...
      //--------------------------------------------------------------------------------
      if (val) {
        if (myStrcmp (actSig, "Ljava/util/Date") || myStrcmp(actSig, "Ljava/lang/Object")) {
          DWORD year = DWORD (((packdate FAR *) val)->year) - 1900L;
          DWORD month = DWORD (((packdate FAR *) val)->month) - 1L;
          DWORD day = ((packdate FAR *) val)->day;
          ParamList[i].ValToPush = (* ((CONSTRUCTDATE) CallConstructor)) ("java/util/Date", "(III)V",year,month,day);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else {
          DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer date"));
          ParamList[i].ValToPush = 0L;
          }
        }
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_TIME) {
      // Muss der entsprechende Konstruktor aufgerufen werden...
      //--------------------------------------------------------------------------------
      DBWIN_ASSERT_ERR (FALSE, _T("Time kann nicht gemappt werden"));
      }
    else if (dataType == VAR_STR) {
      // Muss mit newNativeString erzeugt werden...
      //-------------------------------------------
      if (val) {
#ifdef UNICODE
        LPCPLSTR str = (LPCPLSTR)val;
        if (WITHOUT_BOM(str)){
          LPCPLSTR valUni = AnsiToBomStr((LPASTR)str);
          ParamList[i].ValToPush = (DWORD)NewStringNative(TO_LPTSTR(valUni), lstrlen(TO_LPTSTR(valUni)));
          FreeGlobMem(valUni);
          }
        else
          ParamList[i].ValToPush = (DWORD)NewStringNative(LPTSTR(val) + 1, lstrlen(LPTSTR(val) + 1));  // BOM!
#else
        LPCPLSTR str = (LPCPLSTR)val;
        if (WITH_BOM(str)){
          LPASTR valAnsi = UnicodeToAnsi(LPWSTR(str) + 1);
          ParamList[i].ValToPush = (DWORD)NewStringNative (valAnsi, lstrlen(valAnsi));
          FreeGlobMem(valAnsi);
          }
        else
          ParamList[i].ValToPush = (DWORD)NewStringNative(LPTSTR(val), lstrlen(LPTSTR(val)));
#endif
        ParamList[i].jnewCalled = TRUE;
        /*javaReferences++; now computed in JMODEL*/
        }
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_BLOB) {
      // Muss mit NewArrayNative erzeugt werden...
      //-------------------------------------------
      if (val) {
        BlobDesc *bd = (BlobDesc *)val;
        if ((bd->Size > 0) && bd->hGmem) {
          if (myStrcmp (actSig, "[B")) {
            LPVOID bytes = GlobalLock(bd->hGmem);
            ParamList[i].ValToPush = (DWORD)NewArrayNative(bytes, bd->Size, "B");
            ParamList[i].jnewCalled = TRUE;
            /*javaReferences++; now computed in JMODEL*/
            GlobalUnlock(bd->hGmem);
            }
          else if (myStrcmp (actSig, "Ljava/lang/String")) {
            LPCPLSTR bytes = (LPCPLSTR) GlobalLock(bd->hGmem);
#ifdef UNICODE
            if (WITHOUT_BOM(bytes)){
              LPTSTR newStr = (LPTSTR)GetGlobMem((bd->Size) * sizeof(TCHAR));
              MultiByteToWideChar(CP_THREAD_ACP, 0, (LPASTR)bytes, bd->Size, newStr, bd->Size);
              ParamList[i].ValToPush = (DWORD)NewStringNative(newStr, bd->Size);
              FreeGlobMem(newStr);
              }
            else
              ParamList[i].ValToPush = (DWORD)NewStringNative((LPTSTR)bytes + sizeof (TCHAR), bd->Size - sizeof (TCHAR)); //unicode
#else
            if (WITH_BOM(bytes)){
              int len = bd->Size / sizeof(WCHAR) - 1;
              LPASTR newStr = (LPASTR)GetGlobMem(len);
              WideCharToMultiByte( CP_THREAD_ACP, 0, ((LPWSTR)bytes) + 1, len, newStr, len, NULL, NULL);
              ParamList[i].ValToPush = (DWORD)NewStringNative(newStr, len);
              FreeGlobMem(newStr);
              }
            else
              ParamList[i].ValToPush = (DWORD)NewStringNative((LPTSTR)bytes, bd->Size); //unicode
#endif
            ParamList[i].jnewCalled = TRUE;
            /*javaReferences++; now computed in JMODEL*/
            GlobalUnlock(bd->hGmem);
            }
          else {
            DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer blob"));
            ParamList[i].ValToPush = 0L;
            }
          }
        else
          ParamList[i].ValToPush = 0L;
        }
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_OBJ) {
      // Es ist bereits ein Objekt...
      //-----------------------------
      if (val)
        ParamList[i].ValToPush = * ((DWORD *) val);
      else
        ParamList[i].ValToPush = 0L;
      }
    else if (dataType == VAR_DEC) {
      if (*actSig == 'F') {
        double d;
        if (val) {
          float *lpf = (float *) val;
          d = *lpf;
          }
        else
          d = 0.0;
        LPDWORD lpd = (LPDWORD)&d;
        ParamList[i].ValToPush = lpd[0];
        ParamList[i].pushAdditionalVal = TRUE;
        ParamList[i].AdditionalValToPush = lpd[1];
        }
      else if (myStrcmp (actSig, "Ljava/lang/Float") || myStrcmp(actSig, "Ljava/lang/Object")) {
        if (val) {
          float *lpf = (float *) val;
          double d = *lpf;
          ParamList[i].ValToPush = (* ((CONSTRUCTFLOAT) CallConstructor)) ("java/lang/Float", "(F)V",d);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else
          ParamList[i].ValToPush = 0L;
        }
      else
        DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer float"));
      }
    else if (dataType == VAR_QLONG) {
      if (*actSig == 'D') {
        double d;
        if (val)
          d = *((double *) val);
        else
          d = 0.0;
        LPDWORD lpd = (LPDWORD)&d;
        ParamList[i].ValToPush = lpd[0];
        ParamList[i].pushAdditionalVal = TRUE;
        ParamList[i].AdditionalValToPush = lpd[1];
        }
      else if (myStrcmp (actSig, "Ljava/lang/Double") || myStrcmp(actSig, "Ljava/lang/Object")) {
        if (val) {
          double d = *((double *) val);
          ParamList[i].ValToPush = (* ((CONSTRUCTFLOAT) CallConstructor)) ("java/lang/Double", "(F)V",d);
          ParamList[i].jnewCalled = TRUE;
          /*javaReferences++; now computed in JMODEL*/
          }
        else
          ParamList[i].ValToPush = 0L;
        }
      else
        DBWIN_ASSERT_ERR (FALSE, _T("unbekannte Signatur fuer qlong"));
      }
    else
      DBWIN_ASSERT_ERR (FALSE, _T("unerwarteter Datentyp"));
    actSig = NextSig (actSig);
    }
  DBWIN_ASSERT_ERR (*actSig == ')', _T("Mehr Parameter uebergeben als in Signatur"));

  if (!error) {
    for (i = anzPars - 1; i >= 0; i--) {
      if (VAR_TYPE(ParamList[i].VarInfo) == VT_WORD) {
        WIN_ASSERT_TEXT(FALSE, _T("nanu?"));
        WORD WordToPush = WORD(ParamList[i].ValToPush);
        __asm push DWORD PTR WordToPush;
        PushedSize += sizeof(DWORD);
        }
      else {
        if (ParamList[i].pushAdditionalVal) {
          DWORD DWordToPush = ParamList[i].AdditionalValToPush;
          __asm push DWORD PTR DWordToPush;
          PushedSize += sizeof(DWORD);
          }
        DWORD DWordToPush = ParamList[i].ValToPush;
        __asm push DWORD PTR DWordToPush;
        PushedSize += sizeof(DWORD);
        }
      }

    jvalue res;
    memset (&res, 0, sizeof (res));

    if (typeToCall != TYPE_CONSTRUCTOR) {
      // Resultat kommt als Pointer daher...
      DWORD DWordToPush;
      if (myStrcmp (actSig + 1, "V"))
        DWordToPush = 0L;
      else
        DWordToPush = DWORD (&res);
      __asm push DWORD PTR DWordToPush;
      PushedSize += sizeof(DWORD);
      }

    // Jetzt noch die entsprechenden Einleitungssequenzen pushen
    DWORD DWordToPush;
    // Die Signatur Pushen
    DWordToPush = DWORD (ansiSignature);
    __asm push DWORD PTR DWordToPush;
    PushedSize += sizeof(DWORD);

    // Die Methode (bei Construktoren: der Klassenname) Pushen
    DWordToPush = DWORD (ansiMethod);
    __asm push DWORD PTR DWordToPush;
    PushedSize += sizeof(DWORD);

    if ((typeToCall == TYPE_METHOD) || (typeToCall == TYPE_STATICMETHOD)) {
      // Das Objekt (Klassennamen) an sich pushen
      DWordToPush = object;
      __asm push DWORD PTR DWordToPush;
      PushedSize += sizeof(DWORD);
      }

    BOOL OldInClientTransaction = InClientTransaction;
    InClientTransaction = TRUE;
    IsInExternCall = TRUE ;
    ToBusyCursor();
    DWORD RetVal;
    RetVal = (*procToCall) ();
    IsInExternCall = FALSE ;
    InClientTransaction = OldInClientTransaction;
    if (!OldInClientTransaction && CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }

    // Call Stack wieder herstellen...
    DWORD DPushedSize = DWORD(PushedSize);
    __asm add esp,DWORD PTR DPushedSize;

    if (GetLastExceptionObject() != NULL) {
      if (!c->IsConst (retVal))
        c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
      jobject leo = GetLastExceptionObject();
      LastCatchExceptionMdiChild->WritelData(LastCatchExceptionPar->exceptionobject,&leo,sizeof(leo),LPBYTE(LastCatchExceptionPar)-sizeof(WORD));
      SetLastExceptionObject(NULL);
      LastCatchExceptionPar = NULL;
      LastCatchExceptionMdiChild = NULL;
      SetCatchNextException(FALSE);
      }
    else {
      // Analyse des Return - Wertes
      if (typeToCall == TYPE_CONSTRUCTOR) {
        res.l = (jobject) RetVal;
        /*if (res.l != 0L) javaReferences++; now computed in JMODEL*/
        }
      /*else if ((*(actSig + 1) == 'L') && (res.l != 0L))
          javaReferences++; now computed in JMODEL
      */

      if (!c->IsConst (retVal)) {
        if (typeToCall == TYPE_CONSTRUCTOR) {
          c->WritelData (retVal,&res,sizeof(res.l),LPBYTE(param) - sizeof(WORD));
          /*if (doLog)
            wsprintf(LogRetVal, _T("%ld"), res.l);*/
          }
        else if (myStrcmp (actSig + 1, "V")) {
          c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
          }
        else {
          WORD dataType = c->GetDataType (retVal);
          if (dataType == VAR_OBJ) {
            if (res.l != 0L) {
              c->WritelData (retVal,&res,sizeof(res.l),LPBYTE(param) - sizeof(WORD));
              /*if (doLog)
                wsprintf(LogRetVal, _T("%ld"), res.l);*/
              }
            else {
              c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
              /*if (doLog)
                lstrcpy(LogRetVal, _T("null"));*/
              }
            }
          else if (dataType == VAR_STR) {
            if (myStrcmp (actSig + 1, "Ljava/lang/String") || myStrcmp(actSig + 1, "Ljava/lang/Object")) {
              if (res.l != 0L) {
                int len = GetStringLength((jstring) res.l) + 1;
                DBWIN_ASSERT (len < 64000);
                LPTSTR resStr = LPTSTR (GetGlobMem (len*sizeof(TCHAR)));
                GetStringNativeChars((jstring) res.l,resStr);
                resStr[len - 1] = '\0';
                DeleteReference (res.l);
                c->WritelStrData (retVal,resStr,len,LPBYTE(param) - sizeof(WORD));
                /*if (doLog)
                  wsprintf(LogRetVal, _T("%.250s"), resStr);*/
                FreeGlobMem (resStr);
                }
              else {
                c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
                /*if (doLog)
                  lstrcpy(LogRetVal, _T("null"));*/
                }
              }
            else {
              JavaClassInkompatibel ("string", actSig + 1);
              }
            }
          else if (dataType == VAR_BLOB) {
            if (myStrcmp (actSig + 1,"[B")) {
              /*if (doLog)
                wsprintf(LogRetVal, _T("%ld"), res.l);*/
              if (res.l != 0L) {
                long len = GetArrayLength((jarray) res.l);
                if (len > 0) {
                  BlobDesc bd;
                  bd.Size = len;
                  bd.hGmem = GlobalAlloc (GMEM_MOVEABLE,bd.Size);
                  LPVOID bytes = GlobalLock (bd.hGmem);
                  GetArrayNatives((jarray)res.l, "B", bytes);
                  DeleteReference (res.l);
                  GlobalUnlock (bd.hGmem);
                  c->WritelData (retVal,&bd,sizeof(bd),LPBYTE(param) - sizeof(WORD));
                  }
                else
                  c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
                }
              else
                c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
              }
            else if (myStrcmp (actSig + 1, "Ljava/lang/String")) {
              if (res.l != 0L) {
                int len = GetStringLength((jstring) res.l);
                if (len > 0) {
                  BlobDesc bd;
                  bd.Size = len;
                  bd.hGmem = GlobalAlloc (GMEM_MOVEABLE,bd.Size + 1);
                  //unicode???
                  LPASTR resStr = (LPASTR)GlobalLock(bd.hGmem); // in den Blob wird nur Ansi geschrieben!
                  LPTSTR resUniStr = (LPTSTR)GetGlobMem ((len +1)*sizeof(TCHAR));
                  GetStringNativeChars((jstring) res.l,resUniStr);
#ifdef UNICODE
                  WideCharToMultiByte (CP_THREAD_ACP, NULL, resUniStr, len, resStr, len, NULL, NULL);
#else
                  lstrcpy (resStr, resUniStr);
#endif
                  resStr[len] = '\0';
                  /*if (doLog)
                    wsprintf(LogRetVal, _T("%.250s"), resStr);*/
                  DeleteReference (res.l);
                  GlobalUnlock (bd.hGmem);
                  c->WritelData (retVal,&bd,sizeof(bd),LPBYTE(param) - sizeof(WORD));
                  }
                else {
                  c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
                  /*if (doLog)
                    lstrcpy(LogRetVal, _T("null"));*/
                  }
                }
              else {
                c->DellData (retVal,LPBYTE(param) - sizeof(WORD));
                /*if (doLog)
                  lstrcpy(LogRetVal, _T("null"));*/
                }
              }
            else {
              JavaClassInkompatibel ("blob", actSig + 1);
              }
            }
          else if (dataType == VAR_LONG) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteIntegerData (c, param, retVal, &res, actSig + 1, sizeof (LONG), "intValue", "()I");
            }
          else if (dataType == VAR_STRARR) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteIntegerData (c, param, retVal, &res, actSig + 1, sizeof (DBINT), "shortValue", "()S");
            }
          else if (dataType == VAR_FLAG) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteIntegerData (c, param, retVal, &res, actSig + 1, sizeof (DBBOOL), "shortValue", "()S");
            }
          else if (dataType == VAR_DEC) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteFloatData (c, param, retVal, &res, actSig + 1, sizeof (float));
            }
          else if (dataType == VAR_QLONG) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteDoubleData (c, param, retVal, &res, actSig + 1, sizeof (double));
            }
          else if (dataType == VAR_DATE) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteDateData (c, param, retVal, &res, actSig + 1, sizeof (packdate));
            }
          else if (dataType == VAR_TIME) {
            DBWIN_ASSERT_TEXT (FALSE, _T("Time kann nicht zurueckgegeben werden"));
            }
          else if (dataType == VAR_DATETIME) {
            /*if (doLog)
              wsprintf(LogRetVal, _T("%ld"), res.l);*/
            WriteDatetimeData (c, param, retVal, &res, actSig + 1, sizeof (packdatetime));
            }
          else {
            ACHAR cplType[32];
            sprintf (cplType, "nicht implementierter Typ(%d)", dataType);
            JavaClassInkompatibel (cplType, actSig + 1);
            }
          }
        }
      }
    }

  /*if (doLog) {
    LPTSTR ParamString = NULL;
    TCHAR actParam[256];
    for (i = anzPars - 1 ; i >= 0 ; i--) {
      if (ParamList[i].jnewCalled) {
        jvalue javaStr;
        CallMethodByName((jobject)ParamList[i].ValToPush, "toString", "()Ljava/lang/String;", &javaStr);
        if (javaStr.l) {
          jint len = GetStringLength((jstring)javaStr.l);
          if (len > 0) {
            GLOBALHANDLE hStr = GlobalAlloc (GMEM_MOVEABLE,(len + 1)*sizeof(TCHAR));
            LPTSTR cStr = (LPTSTR)GlobalLock(hStr);
            GetStringNativeChars((jstring)javaStr.l, cStr);
            cStr[len] = '\0';
            wsprintf(actParam, _T("%.250s"), cStr);
            GlobalUnlock(hStr);
            GlobalFree(hStr);
            }
          else
            lstrcpy(actParam, _T("\"\""));
          Delete(javaStr.l);
          }
        else {
          lstrcpy(actParam, _T("<null>"));
          }
        }
      else {
        wsprintf(actParam, _T("%ld"), ParamList[i].ValToPush);
        }
      ParamString = PushParam(ParamString, actParam);
      }

    if (logWithoutPars)
      LogCmd (method,signature,time,NULL,NULL);
    else
      LogCmd (method,signature,time,LogRetVal,ParamString);
    FreeGlobMem(LogRetVal);
    if (ParamString != NULL)
      FreeGlobMem (ParamString);
    }*/

  // Wieder alle Java - Parameter freigeben...
  for (i = 0 ; i < anzPars ; i++) {
    if ((ParamList[i].ValToPush) && (ParamList[i].jnewCalled)) {
      DeleteReference ((jobject) ParamList[i].ValToPush);
      }
    }

  FreeGlobMem (ParamList);
#ifdef UNICODE
  FreeGlobMem (ansiSignature);
  FreeGlobMem (ansiMethod);
#endif

  if (GetCatchNextException()) {
    // Referenz zurücksetzen auch wenn keine Exception autgetreten ist
    LastCatchExceptionPar = NULL;
    LastCatchExceptionMdiChild = NULL;
    }
  SetCatchNextException(oldCatchNextException);

  jnewCalled = TRUE;
  }

BOOL Jmethod (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jmethod_param *par = (Jmethod_param *) param;
    LPTSTR signature = c->ReadlStrData (par->signature);
    LPTSTR method = c->ReadlStrData (par->method);

    LPTSTR sig;
    if (doReplace)
      sig = replaceClassName(signature);
    else
      sig = signature;

    jnewCalled = FALSE;
    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    BOOL jnewCalledObject = jnewCalled;

    Jmethod_constructor (c,par->retVal,par->par,par->anzPars(),sig,method,
                         (lpobject != NULL) ? *lpobject : 0L,
                         TYPE_METHOD,param,(FARPROC)CallMethodByName);

    if (jnewCalledObject && (lpobject != NULL) && (*lpobject)) {
      DeleteReference ((jobject) *lpobject);
      }

    if (sig != signature)
      FreeGlobMem(sig);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jmethod_param *par = (Jmethod_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    for ( int i = 0 ; i < par->anzPars () ; i++ ) {
      c->ClearlConnection (par->par[i],LPBYTE(param) - sizeof(WORD));
      }
    }
  return FALSE;
  }

BOOL Jmethodparallel (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jmethod_param *par = (Jmethod_param *) param;
    LPTSTR signature = c->ReadlStrData (par->signature);
    LPTSTR method = c->ReadlStrData (par->method);

    LPTSTR sig;
    if (doReplace)
      sig = replaceClassName(signature);
    else
      sig = signature;

    jnewCalled = FALSE;
    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    BOOL jnewCalledObject = jnewCalled;

    Jmethod_constructor (c,par->retVal,par->par,par->anzPars(),sig,method,
                         (lpobject != NULL) ? *lpobject : 0L,
                         TYPE_METHOD,param,(FARPROC)CallMethodByNameParallel);

    if (jnewCalledObject && (lpobject != NULL) && (*lpobject)) {
      DeleteReference ((jobject) *lpobject);
      }

    if (sig != signature)
      FreeGlobMem(sig);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jmethod_param *par = (Jmethod_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    for ( int i = 0 ; i < par->anzPars () ; i++ ) {
      c->ClearlConnection (par->par[i],LPBYTE(param) - sizeof(WORD));
      }
    }
  return FALSE;
  }

BOOL Jstaticmethod (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jstaticmethod_param *par = (Jstaticmethod_param *) param;
    LPTSTR signature = c->ReadlStrData (par->signature);
    LPTSTR method = c->ReadlStrData (par->method);

    LPTSTR classname = c->ReadlStrData (par->classname);

    LPTSTR sig;
    LPTSTR clazz;
    if (doReplace) {
      sig = replaceClassName(signature);
      clazz = replaceClassName(classname);
      }
    else {
      sig = signature;
      clazz = classname;
      }
#ifdef UNICODE
    LPASTR ansiClass = UnicodeToAnsi (clazz);
    Jmethod_constructor (c,par->retVal,par->par,par->anzPars(),sig,method,DWORD (ansiClass),TYPE_STATICMETHOD,
                        param,(FARPROC)CallStaticMethodByName);
    FreeGlobMem (ansiClass);
#else
    Jmethod_constructor (c,par->retVal,par->par,par->anzPars(),sig,method,DWORD (clazz),TYPE_STATICMETHOD,
                        param,(FARPROC)CallStaticMethodByName);
#endif

    if (sig != signature)
      FreeGlobMem(sig);
    if (clazz != classname)
      FreeGlobMem(clazz);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jstaticmethod_param *par = (Jstaticmethod_param *) param;
    c->ClearlConnection (par->classname,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    for ( int i = 0 ; i < par->anzPars () ; i++ ) {
      c->ClearlConnection (par->par[i],LPBYTE(param) - sizeof(WORD));
      }
    }
  return FALSE;
  }

BOOL Jnew (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jnew_param *par = (Jnew_param *) param;
    LPTSTR signature = c->ReadlStrData (par->signature);
    LPTSTR classname = c->ReadlStrData (par->classname);

    LPTSTR sig;
    LPTSTR clazz;
    if (doReplace) {
      sig = replaceClassName(signature);
      clazz = replaceClassName(classname);
      }
    else {
      sig = signature;
      clazz = classname;
      }

    Jmethod_constructor (c, par->retVal, par->par, par->anzPars(), sig, clazz, 0L, TYPE_CONSTRUCTOR,
                        param,(FARPROC)CallConstructor);

    if (sig != signature)
      FreeGlobMem(sig);
    if (clazz != classname)
      FreeGlobMem(clazz);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jnew_param *par = (Jnew_param *) param;
    c->ClearlConnection (par->classname,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    for ( int i = 0 ; i < par->anzPars () ; i++ ) {
      c->ClearlConnection (par->par[i],LPBYTE(param) - sizeof(WORD));
      }
    }
  return FALSE;
  }

BOOL Jnewstring (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jnewstring_param *par = (Jnewstring_param *) param;
    LPTSTR str = c->ReadlStrData (par->par);
    DWORD RetVal;
    if (str != NULL) {
      RetVal = (DWORD)NewStringNative(str,lstrlen(str));
      /*javaReferences++; now computed in JMODEL*/
      }
    else
      RetVal = 0L;
    c->WritelData (par->retVal,&RetVal,sizeof(RetVal),LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jnewstring_param *par = (Jnewstring_param *) param;
    c->ClearlConnection (par->par,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jdelete (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jdelete_param *par = (Jdelete_param *) param;

    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    if ((lpobject != NULL) && *lpobject) {
      DeleteReference ((jobject) *lpobject);
      c->DellData (par->object,LPBYTE(param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jdelete_param *par = (Jdelete_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jstartvm (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jstartvm_param *par = (Jstartvm_param *) param;
    LPTSTR vmpath = c->ReadlStrData (par->vmpath);
    LPTSTR classpath = c->ReadlStrData (par->classpath);
    LPTSTR debug_param = c->ReadlStrData (par->debug_param);
    LPTSTR extra_option = c->ReadlStrData (par->extra_option);
#ifdef UNICODE
    LPASTR ansiClasspath, ansiDebug, ansiExtra;
    if (classpath)
      ansiClasspath = UnicodeToAnsi (classpath);
    else
      ansiClasspath = NULL;
    if (debug_param)
      ansiDebug = UnicodeToAnsi (debug_param);
    else
      ansiDebug = NULL;
    if (extra_option)
      ansiExtra = UnicodeToAnsi (extra_option);
    else
      ansiExtra = NULL;
    if (!Start(vmpath, ansiClasspath, ansiDebug, ansiExtra))
      WIN_ASSERT_TEXT(FALSE, _T("error starting JAVA VM"));
    if (ansiClasspath) FreeGlobMem (ansiClasspath);
    if (ansiDebug)     FreeGlobMem (ansiDebug);
    if (ansiExtra)     FreeGlobMem (ansiExtra);
#else
    if (!Start(vmpath, classpath, debug_param, extra_option))
      WIN_ASSERT_TEXT(FALSE, _T("error starting JAVA VM"));
#endif
    AttachCurrentThread();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jstartvm_param *par = (Jstartvm_param *) param;
    c->ClearlConnection (par->vmpath,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->classpath,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->debug_param,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->extra_option,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jdestroyvm (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DetachCurrentThread();
    if (!Destroy()) {
      WIN_ASSERT_TEXT(FALSE, _T("error stopping JAVA VM"));
      }
    }
  return FALSE;
  }

/*BOOL Jsetfocus (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jsetfocus_param *par = (Jsetfocus_param *) param;

    HWND *lphwnd = (HWND *) c->ReadlData (par->hwnd);
    if (lphwnd != NULL)
      SetFocusToJavaWindow(*lphwnd);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jsetfocus_param *par = (Jsetfocus_param *) param;
    c->ClearlConnection (par->hwnd,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }*/

BOOL Jcatchexception (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LastCatchExceptionPar = (Jcatchexception_param *) param;
    LastCatchExceptionMdiChild = c;
    }
  return FALSE;
  }

BOOL Jlogexception (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jlogexception_param *par = (Jlogexception_param *) param;

    DWORD *lpobject = (DWORD *) c->ReadlData (par->exceptionobject);
    if ((lpobject != NULL) && *lpobject) {
      if ((GetLastJavaExceptionCallStack() != NULL) && (GetLastJavaExceptionText() != NULL)) {
        SetJavaExceptionText(GetLastJavaExceptionCallStack());
        WIN_ASSERT_TEXT(FALSE, GetLastJavaExceptionText());
        SetLastJavaExceptionCallStack(NULL);
        SetLastJavaExceptionText(NULL);
        }
      else {
        WIN_ASSERT_TEXT(FALSE, _T("internal error: JAVA exception without description"));
        }
      }
    }
  return FALSE;
  }

BOOL Jinstanceof (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    Jinstanceof_param *par = (Jinstanceof_param *) param;

    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    LPTSTR lpclassname = c->ReadlStrData (par->classname);
    if ((lpobject != NULL) && *lpobject && (lpclassname != NULL)) {
      LPTSTR clazz;
      if (doReplace)
        clazz = replaceClassName(lpclassname);
      else
        clazz = lpclassname;

#ifdef UNICODE
      LPASTR ansiClass = UnicodeToAnsi (clazz);
      res = Instanceof ((jobject) *lpobject, ansiClass);
      FreeGlobMem (ansiClass);
#else
      res = Instanceof ((jobject) *lpobject, clazz);
#endif

      if (clazz != lpclassname)
        FreeGlobMem(clazz);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jinstanceof_param *par = (Jinstanceof_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->classname,LPBYTE(param) - sizeof(WORD));
    }
  return res;
  }

BOOL Jmethodexists (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    Jmethodexists_param *par = (Jmethodexists_param *) param;

    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    LPTSTR lpmethod = c->ReadlStrData (par->method);
    LPTSTR lpsignature = c->ReadlStrData (par->signature);
    if ((lpobject != NULL) && *lpobject && (lpmethod != NULL) && (lpsignature != NULL)) {
      LPTSTR sig;
      if (doReplace)
        sig = replaceClassName(lpsignature);
      else
        sig = lpsignature;

#ifdef UNICODE
      LPASTR ansiMethod = UnicodeToAnsi (lpmethod);
      LPASTR ansiSig = UnicodeToAnsi (sig);
      res = CheckMethod ((jobject) *lpobject, ansiMethod, ansiSig);
      FreeGlobMem (ansiMethod);
      FreeGlobMem (ansiSig);
#else
      res = CheckMethod ((jobject) *lpobject, lpmethod, sig);
#endif

      if (sig != lpsignature)
        FreeGlobMem(sig);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jmethodexists_param *par = (Jmethodexists_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    }
  return res;
  }

BOOL Jstaticmethodexists (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    Jstaticmethodexists_param *par = (Jstaticmethodexists_param *) param;

    LPTSTR lpclassname = c->ReadlStrData (par->classname);
    LPTSTR lpmethod = c->ReadlStrData (par->method);
    LPTSTR lpsignature = c->ReadlStrData (par->signature);
    if ((lpclassname != NULL) && (lpmethod != NULL) && (lpsignature != NULL)) {
      LPTSTR sig;
      LPTSTR clazz;
      if (doReplace) {
        sig = replaceClassName(lpsignature);
        clazz = replaceClassName(lpclassname);
        }
      else {
        sig = lpsignature;
        clazz = lpclassname;
        }

#ifdef UNICODE
      LPASTR ansiMethod = UnicodeToAnsi (lpmethod);
      LPASTR ansiSig = UnicodeToAnsi (sig);
      LPASTR ansiClass = UnicodeToAnsi (clazz);
      res = CheckStaticMethod (ansiClass, ansiMethod, ansiSig);
      FreeGlobMem (ansiMethod);
      FreeGlobMem (ansiSig);
      FreeGlobMem (ansiClass);
#else
      res = CheckStaticMethod (clazz, lpmethod, sig);
#endif

      if (sig != lpsignature)
        FreeGlobMem(sig);
      if (clazz != lpclassname)
        FreeGlobMem(clazz);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jstaticmethodexists_param *par = (Jstaticmethodexists_param *) param;
    c->ClearlConnection (par->classname,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    }
  return res;
  }

BOOL JBmethodexists (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DBINT res = FALSE;
    JBmethodexists_param *par = (JBmethodexists_param *) param;

    DWORD *lpobject = (DWORD *) c->ReadlData (par->object);
    LPTSTR lpmethod = c->ReadlStrData (par->method);
    LPTSTR lpsignature = c->ReadlStrData (par->signature);
    if ((lpobject != NULL) && *lpobject && (lpmethod != NULL) && (lpsignature != NULL)) {
      LPTSTR sig;
      if (doReplace)
        sig = replaceClassName(lpsignature);
      else
        sig = lpsignature;

#ifdef UNICODE
      LPASTR ansiMethod = UnicodeToAnsi (lpmethod);
      LPASTR ansiSig = UnicodeToAnsi (sig);
      res = CheckMethod ((jobject) *lpobject, ansiMethod, ansiSig);
      FreeGlobMem (ansiMethod);
      FreeGlobMem (ansiSig);
#else
      res = CheckMethod ((jobject) *lpobject, lpmethod, sig);
#endif

      if (sig != lpsignature)
        FreeGlobMem(sig);
      }
    c->WritelData (par->res,&res,sizeof(res),LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    JBmethodexists_param *par = (JBmethodexists_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL JBstaticmethodexists (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DBINT res = FALSE;
    JBstaticmethodexists_param *par = (JBstaticmethodexists_param *) param;

    LPTSTR lpclassname = c->ReadlStrData (par->classname);
    LPTSTR lpmethod = c->ReadlStrData (par->method);
    LPTSTR lpsignature = c->ReadlStrData (par->signature);
    if ((lpclassname != NULL) && (lpmethod != NULL) && (lpsignature != NULL)) {
      LPTSTR sig;
      LPTSTR clazz;
      if (doReplace) {
        sig = replaceClassName(lpsignature);
        clazz = replaceClassName(lpclassname);
        }
      else {
        sig = lpsignature;
        clazz = lpclassname;
        }

#ifdef UNICODE
      LPASTR ansiMethod = UnicodeToAnsi (lpmethod);
      LPASTR ansiSig = UnicodeToAnsi (sig);
      LPASTR ansiClass = UnicodeToAnsi (clazz);
      res = CheckStaticMethod (ansiClass, ansiMethod, ansiSig);
      FreeGlobMem (ansiMethod);
      FreeGlobMem (ansiSig);
      FreeGlobMem (ansiClass);
#else
      res = CheckStaticMethod (clazz, lpmethod, sig);
#endif

      if (sig != lpsignature)
        FreeGlobMem(sig);
      if (clazz != lpclassname)
        FreeGlobMem(clazz);
      }
    c->WritelData (par->res,&res,sizeof(res),LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    JBstaticmethodexists_param *par = (JBstaticmethodexists_param *) param;
    c->ClearlConnection (par->classname,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->method,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->signature,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jgetarraylength (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jgetarraylength_param *par = (Jgetarraylength_param *) param;
    DWORD *lpobject = (DWORD *) c->ReadlData (par->array);
    DWORD RetVal;
    if ((lpobject != NULL) && *lpobject)
      RetVal = (DWORD)GetArrayLength((jarray)*lpobject);
    else
      RetVal = 0L;
    c->WritelData (par->retVal,&RetVal,sizeof(RetVal),LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jgetarraylength_param *par = (Jgetarraylength_param *) param;
    c->ClearlConnection (par->array,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jgetobjarrayelement (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jgetobjarrayelement_param *par = (Jgetobjarrayelement_param *) param;
    DWORD *lpobject = (DWORD *) c->ReadlData (par->array);
    LPDWORD lpindex = (LPDWORD) c->ReadlData (par->index);
    LPTSTR type = NULL;
    if (par->parSize >= sizeof (*par))
      type = c->ReadlStrData (par->type);
    if (type == NULL)
      type = _T("L");
    if ((lpobject != NULL) && *lpobject && (lpindex != NULL)) {
      jvalue res;
#ifdef UNICODE
      LPASTR ansiType = UnicodeToAnsi (type);
      GetArrayNativesEx((jarray)*lpobject, ansiType, &res, *lpindex);
      FreeGlobMem (ansiType);
#else
      GetArrayNativesEx((jarray)*lpobject, type, &res, *lpindex);
#endif
      if ((*type == 'L') && (res.l != NULL)) {
        c->WritelData (par->retVal,&res,sizeof(DWORD),LPBYTE(param) - sizeof(WORD));
        /*javaReferences++; now computed in JMODEL*/
        }
      else {
        int retSize = 0;
        if ((*type == 'Z') || (*type == 'B') || (*type == 'C') || (*type == 'S'))
          retSize = sizeof(WORD);
        else if ((*type == 'I') || (*type == 'J'))
          retSize = sizeof(DWORD);
        else if (*type == 'F')
          retSize = sizeof(float);
        else if (*type == 'D')
          retSize = sizeof(double);
        else
          WIN_ASSERT_TEXT(FALSE, _T("unknown JNI data type"));
        if (retSize > 0)
          c->WritelData (par->retVal,&res,retSize,LPBYTE(param) - sizeof(WORD));
        else
          c->DellData (par->retVal,LPBYTE(param) - sizeof(WORD));
        }
      }
    else
      c->DellData (par->retVal,LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jgetobjarrayelement_param *par = (Jgetobjarrayelement_param *) param;
    c->ClearlConnection (par->array,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->index,LPBYTE(param) - sizeof(WORD));
    if (par->parSize >= sizeof (*par))
      c->ClearlConnection (par->type,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL Jsetreplacemode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jsetreplacemode_param *par = (Jsetreplacemode_param *) param;
    LPDWORD lpmode = (LPDWORD) c->ReadlData (par->mode);
    if (lpmode != NULL) {
      doReplace = TRUE;
      replaceMode = *lpmode;
      }
    else
      doReplace = FALSE;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jsetreplacemode_param *par = (Jsetreplacemode_param *) param;
    c->ClearlConnection (par->mode,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }

extern DLLExport void _export WINAPI DoJavaReferencesInc (LPVOID jref);

BOOL JavaReferencesInc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Jdelete_param *par = (Jdelete_param *) param;

    LPVOID *lpobject = (LPVOID *) c->ReadlData (par->object);
    if (lpobject != NULL) {
      DoJavaReferencesInc(*lpobject);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Jdelete_param *par = (Jdelete_param *) param;
    c->ClearlConnection (par->object,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE;
  }
