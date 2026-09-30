//////////////////////////////////////////////////////
//  Verzoegertes Ausloesen einer Funktion
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/oneshot.cpv   1.13   29 Sep 1998 17:12:12   Martin  $
//  $Log:   P:/marille/clinicum/rev/oneshot.cpv  $
// 
//    Rev 1.13   29 Sep 1998 17:12:12   Martin
// Timerid anders vergeben
// 
//    Rev 1.12   29 Jun 1998 19:04:06   Hannes
// Verbesserte Debuggerunterstuetzung
// 
//    Rev 1.11   24 Oct 1997 08:37:18   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.10   21 Oct 1997 08:33:08   Martin
// Extradatenberuecksichtigung
// 
//    Rev 1.9   10 Jun 1996 10:09:56   GERHOLD
// pragma pack
// 
//    Rev 1.8   02 Feb 1996 10:36:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   15 Dec 1995 16:23:44   HANNES
// 
//    Rev 1.6   24 Aug 1995 00:19:52   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   11 Jul 1995 12:47:46   HANNES
// Expressionoptimierung
// 
//    Rev 1.4   31 Mar 1995 13:09:42   HANNES
//  
// 
//    Rev 1.3   20 Mar 1995 12:05:28   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.2   09 Jan 1995 12:14:34   HANNES
// Debugger eingebaut
// 
//    Rev 1.1   19 Oct 1994 22:36:40   hannes
// Erweiterungen, CallRepeated
// 
//    Rev 1.0   24 Jun 1994 17:05:20   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "oneshot.hpp"
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
#include "compile.hpp"
#include "scdb.hpp"

#define MODULENUM   187
#include "winass.hpp"

#pragma pack(1)
struct OneShotData {
  OneShotData FAR *Next;
  LPVOID ExtraDataAtCreation;
  DELAYEDCALL func;
  LPVOID data;
  WORD TimerID;
  WORD Multiply;
  };
#pragma pack()

#define MAX_TIMERS 256
#define FIRST_TIMERID 0x4000
char TimerUsed[MAX_TIMERS];
WORD GetFreeTimerId()
  {
  for (WORD i = 0; i < MAX_TIMERS; i++) {
    if (!TimerUsed[i]) {
      TimerUsed[i] = TRUE;
      return i + FIRST_TIMERID;
      }
    }
  DBWIN_ASSERT_TEXT(FALSE,"zu viele Timer !");
  return 0;
  }

void FreeTimerId(WORD id)
  {
  TimerUsed[id - FIRST_TIMERID] = FALSE;
  }

typedef OneShotData FAR *LPONESHOT;
LPONESHOT sList;
void SetOneShot (int delay,DELAYEDCALL func,LPVOID data,int dSize,int Multiply,LPVOID edc)
  {
  LPVOID bData = GetGlobMem (dSize);
  lmemcpy (bData,data,dSize);
  LPONESHOT n = LPONESHOT (GetGlobMem(sizeof(*n)));
  n->TimerID = GetFreeTimerId();
  n->func = func;
  n->data = bData;
  if (edc != NULL) {
    n->ExtraDataAtCreation = GetGlobMem (GetBlockSize(edc));
    lmemcpy (n->ExtraDataAtCreation,edc,GetBlockSize(edc));
    }
  n->Next = sList;
  n->Multiply = Multiply;
  sList = n;
  SetTimer (WBase::hFrameWin,n->TimerID,delay,NULL);
  }

BOOL CheckTimer (WORD wP)
  {
  LPONESHOT p = NULL;
  for ( LPONESHOT h = sList ; h != NULL ; p = h , h = h->Next) {
    if (h->TimerID == wP) {
      if (h->Multiply == 0) {
        KillTimer (WBase::hFrameWin,h->TimerID);
        FreeTimerId(h->TimerID);
        if (p != NULL)
          p->Next = h->Next;
        else
          sList = h->Next;
        (* h->func) (h->data,h->ExtraDataAtCreation);
        FreeGlobMem (h->data);
        if (h->ExtraDataAtCreation)
          FreeGlobMem (h->ExtraDataAtCreation);
        FreeGlobMem (h);
        }
      else
        h->Multiply -- ;
      return TRUE ;
      }
    }
  return FALSE ;
  }

void RemoveShot (LPVOID data,int dSize)
  {
  LPONESHOT p = NULL;
  for ( LPONESHOT h = sList ; h != NULL ; p = h , h = h->Next) {
    if ((dSize == int (GetBlockSize (h->data))) && 
        (lmemcmp (h->data,data,dSize))) {
      KillTimer (WBase::hFrameWin,h->TimerID);
      FreeTimerId(h->TimerID);
      if (p != NULL)
        p->Next = h->Next;
      else
        sList = h->Next;
      if (h->ExtraDataAtCreation)
        FreeGlobMem (h->ExtraDataAtCreation);
      FreeGlobMem (h->data);
      FreeGlobMem (h);
      break ;
      }
    }
  }

static DWORD LastControlAction;
void CheckControlAction (MSG FAR *m)
  {
  static WORD msgToTest [] = 
    { WM_KEYDOWN , WM_LBUTTONDOWN , WM_LBUTTONUP , WM_KEYUP } ;
  for (int i = 0 ; i < sizeof(msgToTest) / sizeof(msgToTest[0]) ; i++) {
    if (m->message == msgToTest[i]) {
      LastControlAction = GetTickCount();
      break ;
      }
    }
  }

#pragma pack(1)
struct FAR RepeatedCall_Param {
  WORD  parSize;
  DWORD procToCall;
  DWORD rnormalTime;
  DWORD rminSinceRepeating;
  DWORD firstTimeToCall;
  BOOL WaitForFirstCall ()
    {
    return (parSize >= sizeof(*this)) ;
    }
  };
#pragma pack()

#pragma pack(1)
struct FAR RepeatedCall_Data {
  mdiChild *c;
  RepeatedCall_Param FAR *par;
  LONG normalTime;
  LONG minSinceRepeating;

  void DoIt (LPCONNEXTRAINFO  Extra);
  };
#pragma pack()

extern DLLExport BOOL _export WINAPI IsInDebugMode ();
void RepeatedCall_Data::DoIt (LPCONNEXTRAINFO Extra)
  {
  if (!IsInDebugMode ()) {
    if (Extra != NULL) {
      SAVEREC old;
      c->SetRecsForUpdate (old,Extra);
      SetExtraInfo s(c,Extra);
      c->_GetRecExtra()->cmdBase = c->GetCmdBase();
      c->_GetRecExtra()->cOffs = 0;
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      c->ExCuteProc (par->procToCall,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procToCall,EM_CLEAR | EM_RESET);
      c->RestoreRecs(old);
      }
    else {
      RestoreListFnc rlf (c);
#ifdef DEBUG
      PushToCallStack (c,c->schd->fName,c->GetCmdOffset (LPSTR(par)-sizeof(WORD)));
#endif
      c->ExCuteProc (par->procToCall,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procToCall,EM_CLEAR | EM_RESET);
      }
#ifdef DEBUG
    PopFromCallStack ();
#endif
    }
  }

DELAYEDCALL GetRCDelayedCall ();
VOID WINAPI RCDelayedCall (LPVOID Data,LPVOID Extra)
  {
  RepeatedCall_Data FAR *dt = (RepeatedCall_Data FAR *) Data;
  DWORD aDate = GetTickCount();
  if (LONG(aDate - LastControlAction) > dt->minSinceRepeating) {
    SetOneShot (int(dt->normalTime % 0xFFFF),GetRCDelayedCall(),dt,sizeof(*dt),int(dt->normalTime / 0xFFFF));
    dt->DoIt(LPCONNEXTRAINFO (Extra));
    }
  else
    SetOneShot (int(dt->minSinceRepeating % 0xFFFF),GetRCDelayedCall(),dt,sizeof(*dt),int(dt->minSinceRepeating / 0xFFFF));
  }

DELAYEDCALL GetRCDelayedCall ()
  {
  static DELAYEDCALL res;
  if (res == NULL)
    res = DELAYEDCALL (MakeProcInstance (FARPROC (RCDelayedCall),WBase::hInstance));
  return res;
  }

BOOL RepeatedCall (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RepeatedCall_Param FAR *par = (RepeatedCall_Param FAR *) param;
    RepeatedCall_Data d ;
    d.c = c;
    d.par = par;
    d.normalTime = c->ReadConstLong (par->rnormalTime);
    d.minSinceRepeating = c->ReadConstLong (par->rminSinceRepeating);
    if (!par->WaitForFirstCall ()) {
      d.DoIt(c->_GetRecExtra ());
      SetOneShot (int(d.normalTime % 0xFFFF),GetRCDelayedCall(),&d,sizeof(d),int(d.normalTime / 0xFFFF),c->_GetRecExtra ());
      }
    else {
      LONG firstTime = c->ReadConstLong (par->firstTimeToCall);
      SetOneShot (int(firstTime % 0xFFFF),GetRCDelayedCall(),&d,sizeof(d),int(firstTime / 0xFFFF),c->_GetRecExtra ());
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    RepeatedCall_Param FAR *par = (RepeatedCall_Param FAR *) param;
    RepeatedCall_Data d ;
    d.c = c;
    d.par = par;
    d.normalTime = c->ReadConstLong (par->rnormalTime);
    d.minSinceRepeating = c->ReadConstLong (par->rminSinceRepeating);
    RemoveShot (&d,sizeof(d));
    }
  return FALSE ;
  }

