//////////////////////////////////////////////////////////////////
//  Darstellen eines Formulares in einem Externen Fenster
//////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/extchild.cpv   1.34   09 Aug 1999 18:28:24   Wolfgang  $
// $Log:   P:/marille/clinicum/rev/extchild.cpv  $
// 
//    Rev 1.34   09 Aug 1999 18:28:24   Wolfgang
// 1.) Pruefung auf pmdich bei WM_COMMAND wieder ausgebaut (Rev 1.29), da sie 
//     Cut&Paste-Hotkeys in Formularen innerhalb von Dialogen verhindert.
// 
//    Rev 1.33   13 Jul 1999 08:41:22   Hannes
// InitializeBars aufrufen...
// 
//    Rev 1.32   07 Jul 1999 07:52:22   Hannes
// Updatereihenfolge in Subdokementen...
// 
//    Rev 1.31   30 Mar 1999 09:58:08   Hannes
// Beim Weiterleiten von Optionen nicht Optionen ueberschreiben...
// 
//    Rev 1.30   05 Oct 1998 11:53:50   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.29   21 Jul 1998 09:46:54   Gerhold
// WM_COMMAND ... Menubefehle. Pruefen ob pmdich != NULL
// 
//    Rev 1.28   15 Apr 1998 13:15:56   Hannes
// SetFocus nach dem Erzeugen des Kindfensters
// 
//    Rev 1.27   07 Apr 1998 19:51:28   Hannes
// Angabe von -1 fuer das Durchschleifen der Extradaten
// 
//    Rev 1.26   29 Oct 1997 19:00:52   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.25   24 Oct 1997 08:37:26   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.24   05 May 1997 11:37:48   Hannes
// Speicherfresser
// 
//    Rev 1.23   19 Mar 1997 14:47:36   Hannes
// NoFurtherUpdates in ~ExtChild
// 
//    Rev 1.22   13 Mar 1997 19:00:24   Hannes
// ExtChildFromBlob
// 
//    Rev 1.21   19 Feb 1997 12:22:44   Hannes
// 
//    Rev 1.20   03 Dec 1996 16:39:50   HANNES
// LoadDone
// 
//    Rev 1.19   28 Oct 1996 08:36:50   HANNES
// CS_DBLCLKS
// 
//    Rev 1.18   10 Jun 1996 10:07:18   GERHOLD
// pragma pack
// 
//    Rev 1.17   22 Feb 1996 10:28:40   MARTIN
// noch ein MakeProcInstance
// 
//    Rev 1.16   02 Feb 1996 10:36:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.15   23 Nov 1995 17:56:26   hannes
// DO_SETFOCUS (FOCUMODE_FORWARD, FOCUSMODE_BACKWARD)
// 
//    Rev 1.14   01 Sep 1995 09:04:00   HANNES
// 
//    Rev 1.13   24 Aug 1995 00:20:12   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.12   14 Aug 1995 08:27:22   HANNES
// Extchilds sollen sich immer vordraengen fuer das Palettenhandling
// 
//    Rev 1.11   02 Jul 1995 18:29:58   GERHOLD
// Palettenhandling
// 
//    Rev 1.10   27 Apr 1995 15:37:24   HANNES
// 
//    Rev 1.9   14 Apr 1995 15:38:32   HANNES
// 
//    Rev 1.8   04 Apr 1995 19:56:52   HANNES
// 
//    Rev 1.7   31 Mar 1995 13:09:38   HANNES
//  
// 
//    Rev 1.6   27 Mar 1995 13:16:42   HANNES
//  
// 
//    Rev 1.5   20 Mar 1995 11:55:40   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.4   20 Sep 1994 11:34:32   HANNES
// Umstellung auf OutContext
// 
//    Rev 1.3   05 Sep 1994 15:37:30   HANNES
// GetMinMax
// 
//    Rev 1.2   17 Jul 1994 14:43:56   HANNES
// Fehlerkorrektur des Destruktors
// 
//    Rev 1.1   24 Jun 1994 19:47:28   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:42   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#ifdef WIN32
#include <wingdi.h>
#else
#include <print.h>
#endif

#include "dds32.h"
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
#include "dllchild.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"
#include "dds.h"
#include "winextra.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"

#define MODULENUM 112
#include "winass.hpp"

#include "tbcbd.hpp"
#include "hash.hpp"
#include "compile.hpp"

#pragma pack(1)
struct FAR ExtraRef {
  LONG Code;
  DWORD Ref;
  };
#pragma pack()

#pragma pack(1)
struct FAR ExtChild_param {
  tool_header hd;
  // weitere Abmessungen und aehnliches
  DWORD Disable;
  LONG  w,h;
  DWORD _Script;      // Script, das ausgefuehrt werden soll
  ExtraRef r[1];

  WORD ScriptVarType (mdiChild *c)
    {
    return c->GetDataType (_Script);
    }
  LPSTR Script (mdiChild *c)
    {
    return LPSTR(c->ReadlData (_Script));
    }
  GLOBALHANDLE hGScript (mdiChild *c)
    {
    return ((BlobDesc FAR *) (c->ReadlData (_Script)))->hGmem;
    }
  int AnzExtra ()
    {
    return (hd.structSize + sizeof(WORD) - (sizeof(*this) - sizeof(r[0]))) / sizeof(r[0]);
    }
  BOOL mitCodeAlleine ()
    {
    if ((AnzExtra() - 1) * sizeof(r[0]) + sizeof(DWORD) + sizeof(*this) - sizeof(WORD) == hd.structSize)
      return TRUE ;
    else
      return FALSE ;
    }
  void SetExtra (mdiChild *res,mdiChild *c);
  DWORD GetVarRef(int Code)
    {
    for (int i = 0 ; i < AnzExtra () ; i++) {
      DBINT Cd = *((DBINT FAR *) LPTBD(hd.MyTool->privData)->c->ReadlData (r[i].Code));
      if (Cd == Code) return r[i].Ref ;
      }
    return 0xFFFFFFFF ;
    }
  };
#pragma pack()

DWORD GetVarRef (ExtChild_param FAR *par,int Code,LPMDICHILD FAR *cd)
  {
  *cd = LPTBD(par->hd.MyTool->privData)->c ;
  return par->GetVarRef(Code);
  }

void ExtChild_param::SetExtra (mdiChild *res,mdiChild *c)
  {
  for (int i = 0 ; i < AnzExtra() ; i++) {
    LPVOID Extra = c->ReadlData (r[i].Ref);
    int Code = c->ReadConstInt (r[i].Code);
    if (Extra != NULL)
      res->PutDocumentExtraData (Code,Extra,GetBlockSize(Extra));
    }
  if (mitCodeAlleine ()) {
    DBINT FAR *lCode = (DBINT FAR *) c->ReadlData (r[i].Code);
    if (*lCode == -1) {
      for ( DocExtraData FAR *h = c->_ed ; (h != NULL) ; h = h->Next) {
        if (!res->GetDocumentExtraData (h->Type))
          res->PutDocumentExtraData (h->Type,h->Data,h->size);
        }
      }
    }
  }

class FAR ExtDocObj : public wobj {
 public :
  ExtChild_param FAR *par;
  LPMDICHILD parent,c;
  ExtDocObj () { }
  virtual mdiChild *GetInst ();
  void Init (LPVOID param,mdiChild *doc,HWND hParent,int x,int y,int w,int h);
  void Register ();
  HWND Create (HWND hParent,int x,int y,int w,int h);
  ~ExtDocObj ();
  };
class FAR ExtBlobObj : public ExtDocObj {
 public :
  ExtBlobObj () : ExtDocObj () { }
  virtual mdiChild *GetInst ();
  };
typedef ExtDocObj FAR *LPEXTDOCOBJ;
void NewExtChild (ExtDocObj FAR *o);
void OnExtChildDestroy (ExtDocObj FAR *o);

LPSTR ExtChildClass = "ECC";

DLLExport LONG _export FAR PASCAL ExtChildProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
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

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {

        case MI_Copy :
        case MI_Cut :
          {
          // if (pmdich != NULL)
          //   break;

          cField FAR * ActiveField = GetActiveField();
          if (ActiveField != NULL) {       // deklariert in CFIELD.HPP
            if (ActiveField->CopyToClipBoard (hWnd))
              if (CRACKER_wID == MI_Cut) {
                ActiveField->DeleteSelectedLines();
                EnableMenuItem (GetMenu(hWnd), MI_Cut, MF_GRAYED);
                }
            }
          }
          break;
        case MI_Insert :
          {
          // if (pmdich != NULL)
          //   break;

          cField FAR * ActiveField = GetActiveField();
          if (ActiveField != NULL) {       // deklariert in CFIELD.HPP
            ActiveField->PasteFromClipBoard (hWnd);
            EnableMenuItem (GetMenu(hWnd), MI_Cut, MF_ENABLED);
            }
          }
          break ;
        }
      }
      // intentionally no break

    default:
      BOOL done = FALSE ;
      if (pmdich != NULL)
        RetVal = pmdich->ChildProc (hWnd,msg,wP,lP,&done);
      if (!done)
        RetVal = DefWindowProc(hWnd, msg, wP, lP);
      break;
    }
  return RetVal ;
  }

void ExtDocObj::Register ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    wndclass.lpfnWndProc   = ExtChildProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(LPMDICHILD) ;
    wndclass.hInstance     = (HINSTANCE)WBase::hInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = ExtChildClass ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

static WORD extchildid = 0x2000;
HWND ExtDocObj::Create (HWND hParent,int x,int y,int w,int h)
  {
  HWND res = CreateWindow (ExtChildClass,"",WS_CHILDWINDOW,
                           x,y,w,h,
                           hParent,
                           HMENU(extchildid++),
                           WBase::hInstance,              
            	             LPVOID(c)
                          ) ;
  NewExtChild (this);
  return res;
  }

extern mdiChild *NewDocInstance (LPSTR docName);
extern mdiChild *NewDocInstance (GLOBALHANDLE hGmem);
mdiChild *ExtDocObj::GetInst ()
  {
  return NewDocInstance (par->Script(parent));
  }
mdiChild *ExtBlobObj::GetInst ()
  {
  return NewDocInstance (par->hGScript(parent));
  }
void ExtDocObj::Init (LPVOID param,mdiChild *doc,HWND hParent,int x,int y,int w,int h)
  {
  par = (ExtChild_param FAR *) param ; 
  parent = doc;
  c = GetInst ();
  DBWIN_ASSERT (c != NULL);
  c->_ccount_base = PushBlock (doc->_ccount->Copy());
  Register ();
  c->GetOutData()->_scale = float (1.0);
  par->SetExtra (c,parent);
  c->GetOutData()->_MyHandle = Create (hParent,x,y,w,h);
  c->cp.ext = par ;
  c->LoadData ();
  c->LoadDone = TRUE ;

  c->GetMinMax();
  c->InitializeBars();
  if (c->BestScaling ())
    c->MapChanged();
  SetFocus (c->GetOutData()->_MyHandle);
  }

ExtDocObj::~ExtDocObj ()
  {
  BOOL doSendWMQUERYNEWPALETTE;
  if (c->GetDocumentExtraData(DED_PALETTEINFO) != NULL)
    doSendWMQUERYNEWPALETTE = TRUE ;
  else
    doSendWMQUERYNEWPALETTE = FALSE ;
  c->closed = TRUE ;
  GetAsync_cmdfifo()->DelDocumentEntrys(c->DocumentID());
  NoFurtherUpdates (c->DocumentID());
  c->Reset();
  c->closed = FALSE ;
  c->FreeExpNodes();
  GlobalUnlock (c->commands) ;
  GlobalFree (c->commands) ;
  c->commands = 0;
  OnExtChildDestroy (this);
  DestroyWindow (c->GetOutData()->_MyHandle);
  if (doSendWMQUERYNEWPALETTE)
    PostMessage (WBase::hFrameWin,WM_QUERYNEWPALETTE,NULL,NULL);
  }

void ExtChildBaseProc (LPVOID param,WORD Action,LPDEPAR p)
  {
  ExtDocObj FAR *obj;
  switch (Action) {
    case DO_RESET  :
      DBWIN_ASSERT (p->reset.objData != NULL);
      obj = (ExtDocObj FAR *) p->reset.objData;
      LPTBD(p->load.privData)->c->ClearlConnection (obj->par->_Script,LPSTR(param));
      delete obj;
      p->reset.objData = NULL ;
      break ;
    case DO_ACTIVATE :
      if (p->activate.flag) {
        DBWIN_ASSERT (p->activate.objData != NULL);
        obj = (ExtDocObj FAR *) p->activate.objData;
        ShowWindow (obj->c->GetOutData()->_MyHandle,SW_NORMAL);
        }
      break ;
    case DO_SETFOCUS :
      obj = (ExtDocObj FAR *) p->focus.objData;
      if (p->focus.mode == FOCUSMODE_FORWARD) {
        p->focus.done = TRUE ;
        LPOBJDEF h = ((FrmObjectList FAR *) obj->c->OutList())->GetFirstActive();
        if (h != NULL)
          ((FrmObjectList FAR *) obj->c->OutList())->act = h ;
        SetFocus (obj->c->OutWnd());
        }
      else if (p->focus.mode == FOCUSMODE_BACKWARD) {
        p->focus.done = TRUE ;
        LPOBJDEF h = ((FrmObjectList FAR *) obj->c->OutList())->GetLastActive();
        if (h != NULL)
          ((FrmObjectList FAR *) obj->c->OutList())->act = h ;
        SetFocus (obj->c->OutWnd());
        }
      break ;
    }
  }
DLLExport void _export WINAPI lShowExtChild (LPVOID param,WORD Action,LPDEPAR p)
  {
  ExtDocObj FAR *obj;
  switch (Action) {
    case DO_LOAD  :
      obj = new ExtDocObj ();
      obj->Init (param,LPTBD(p->load.privData)->c,p->load.hWParent,p->load.x,p->load.y,p->load.w,p->load.h);
      p->load.objData = obj;
      p->load.hWnd = obj->c->GetOutData()->_MyHandle;
      break ;
    default :
      ExtChildBaseProc (param,Action,p);
    }
  }

DLLExport void _export WINAPI lShowExtBlobChild (LPVOID param,WORD Action,LPDEPAR p)
  {
  ExtBlobObj FAR *obj;
  switch (Action) {
    case DO_LOAD  :
      obj = new ExtBlobObj ();
      obj->Init(param,LPTBD(p->load.privData)->c,p->load.hWParent,p->load.x,p->load.y,p->load.w,p->load.h);
      p->load.objData = obj;
      p->load.hWnd = obj->c->GetOutData()->_MyHandle;
      break ;
    default :
      ExtChildBaseProc (param,Action,p);
    }
  }

#pragma pack(1)
struct echild_base {
  ExtDocObj FAR *ec;
  echild_base FAR *Next;
  };
#pragma pack()

echild_base FAR *eChildList;
void toAllExtChilds (UINT msg,WPARAM wP,LPARAM lP)
  {
  for (echild_base FAR *e = eChildList ; e != NULL ; e = e->Next) {
    SendMessage (e->ec->c->GetOutData()->_MyHandle,msg,wP,lP);
    }
  }

void NewExtChild (ExtDocObj FAR *o)
  {
  echild_base FAR *eb = (echild_base FAR *) GetGlobMem (sizeof(*eb));
  eb->Next    = eChildList ;
  eb->ec      = o ;
  eChildList  = eb ;
  }

void OnExtChildDestroy (ExtDocObj FAR *o)
  {
  echild_base FAR *prev = NULL ;
  for (echild_base FAR *e = eChildList ; e != NULL ; e = e->Next) {
    if (e->ec == o) {
      if (prev != NULL) prev->Next = e->Next ;
      else              eChildList = e->Next ;
      FreeGlobMem (e);
      break ;
      }
    prev = e ;
    }
  }

HWND GetActiveExtChild ()
  {
  HWND fWnd = GetFocus();
  for (echild_base FAR *e = eChildList ; e != NULL ; e = e->Next) {
    if ((fWnd == e->ec->c->GetOutData()->_MyHandle) || (fWnd == GetParent (e->ec->c->GetOutData()->_MyHandle)))
      return e->ec->c->GetOutData()->_MyHandle ;
    }
  for (e = eChildList ; e != NULL ; e = e->Next) {
    return e->ec->c->GetOutData()->_MyHandle ;
    }
  return 0;
  }
