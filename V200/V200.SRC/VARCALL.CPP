///////////////////////////////////////////////////////
//      Implemetierung von Prozedur - Arrays
///////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/rev/varcall.cpv   1.12   04 Jun 1999 01:28:40   Hannes  $
// $Log:   P:/marille/clinicum/rev/varcall.cpv  $
// 
//    Rev 1.12   04 Jun 1999 01:28:40   Hannes
// InstallProcedure, FireProcedure
// 
//    Rev 1.11   08 Jul 1997 11:59:02   Hannes
// 
//    Rev 1.10   10 Jun 1996 10:10:10   GERHOLD
// pragma pack
// 
//    Rev 1.9   02 Feb 1996 10:36:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   22 Sep 1995 15:45:40   MARTIN
// par->FromReset ...
// 
//    Rev 1.7   21 Sep 1995 21:18:58   MARTIN
// Im Resetzweig: Clearconnection vor CallProc
// 
//    Rev 1.6   24 Aug 1995 00:19:52   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   11 Jul 1995 12:47:46   HANNES
// Expressionoptimierung
// 
//    Rev 1.4   20 Mar 1995 12:06:00   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.3   06 Feb 1995 16:52:42   HANNES
// 
//    Rev 1.2   09 Jan 1995 12:14:34   HANNES
// Debugger eingebaut
// 
//    Rev 1.1   05 Dec 1994 17:42:38   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.0   24 Jun 1994 17:04:48   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.7   04 Feb 1994 16:50:58   HANNES
// Prototyp von ExCuteBlock
// 
//    Rev 1.6   24 Sep 1993 23:34:04   HANNES
// 
//    Rev 1.5   24 Sep 1993 22:42:18   HANNES
// Richtige Berechnung der Anzahl der Porzeduren
// 
//    Rev 1.4   05 Sep 1993 22:13:48   HANNES
// Aufraeumarbeiten, Verbesserungen
// 
//    Rev 1.3   18 Jun 1993 15:15:04   MARTIN
// Prototyp von GetData
// 
//    Rev 1.2   17 Mar 1993 17:59:42   HANNES
// 32 bit Umstellung
// 
//    Rev 1.1   20 Jan 1993 15:16:22   HANNES
// Verbesserungen in dem Handling von VarCall
// 
//    Rev 1.0   02 Dec 1992 15:45:54   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#define MODULENUM   41
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#include "multipro.hpp"

#pragma pack(1)
struct VarCall_param {
  WORD parSize;
  // Private Daten
  MultiProc FAR *mp;
  WORD oldInd;
  WORD FromReset;    // dreckig: merke mir, ob ich in einem Reset bin
  ctrlist ctrs;
  // Paraemeter
  WORD iRec,iId;        // Index
  DWORD ProcOffset[1];  // Liste der Proceduren
  };
#pragma pack()

void CallProc (mdiChild *c,DWORD Offset,WORD mode,VarCall_param FAR *par)
  {
  if (mode & EM_LOAD) {
    if (c->_GetRecExtra () != NULL) {
      RestoreListFnc rlf(c);    // Achtung: Offset zeigt in das Orginalkompilat
      MultiProc FAR *mp = new MultiProc (c,Offset);
      SetExtraInfo extra(c,mp->CorrOffs());
      mp->AddProcAtTail(0);
      mp->ExCuteLast (mode,&extra);
      par->mp = mp ;
      }
    else {
      RestoreListFnc rlf(c);
      c->ExCuteProc (Offset,mode);
      }
    }
  else if (mode & (EM_RESET | EM_CLEAR)) {
    MultiProc FAR *mp = par->mp ;
    if (mp != NULL) {
      // Abbau der Multiproc
      RestoreListFnc rlf(c);    // Achtung: Offset zeigt in das Orginalkompilat
      SetExtraInfo extra(c,mp->CorrOffs());
      mp->ExCuteLast (mode,&extra);
      mp->RemoveLast ();
      delete mp ;
      par->mp = NULL ;
      }
    else {
      // Normaler Abbau
      RestoreListFnc rlf(c);
      c->ExCuteProc (Offset,mode);
      }
    }
  }

BOOL uVarCall (mdiChild *c,void FAR *param,WORD mode)
  {
  VarCall_param FAR *par = (VarCall_param FAR *) param;
  WORD ind,FAR *lpi;

  if (mode & EM_FIXCONNECTION)
    // Den Fixconnection schon sehr frueh ausfuehren, damit es moeglich ist
    // eine Statemachine zu programmieren
    c->SetConnection (par->iRec,par->iId,LPSTR(param)-sizeof(WORD));

  if (mode & (EM_LOAD | EM_UPDATE)) {
    lpi = (WORD FAR *) c->ReadData (par->iRec,par->iId);
    if (lpi != NULL) {
      ind = *lpi ;
      }
    else
      ind = 0;
    
    WORD maxind = (par->parSize - (sizeof (*par) - sizeof(DWORD))) / sizeof(DWORD) ;
    DBWIN_ASSERT (ind < maxind);
    ind = min (ind,maxind-1);

    if (mode & EM_LOAD) {
      SetCounter (&par->ctrs,c->_ccount);
      c->_ccount = PushBlock(c->_ccount);
      CallProc (c,par->ProcOffset[ind],mode,par);
      c->_ccount = PopBlock (c->_ccount);
      par->oldInd = ind;
      }
    else {
      if ((!par->FromReset) && (ind != par->oldInd)) {
        CallProc (c,par->ProcOffset[par->oldInd],EM_CLEAR | EM_CHANGETOFALSE,par);

        LPCMDCOUNT old = c->_ccount->Copy ();
        c->SetCount (GetCounter (&par->ctrs));
        c->_ccount = PushBlock(c->_ccount);
        CallProc (c,par->ProcOffset[ind],EM_LOAD | EM_CHANGETOTRUE | EM_FIXCONNECTION,
                      par);
        c->SetCount (old);
        FreeGlobMem (old);
        par->oldInd = ind;
        }
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->iRec,par->iId,LPSTR(param)-sizeof(WORD));
    int oldind = int(par->oldInd);
    par->FromReset = TRUE;
    CallProc (c,par->ProcOffset[oldind],mode,par);
    par->FromReset = FALSE;
    RemoveCount (&par->ctrs);
    }

  return FALSE ;
  }

#pragma pack(1)
struct InstallProcedure_Param {
  WORD parSize;
  DWORD Name;
  DWORD proc;
  };
#pragma pack()

int SetKey (LPSTR Buffer,mdiChild *c,LPSTR Name)
  {
  *(LPMDICHILD FAR *) Buffer = c;
  lstrcpy (Buffer + sizeof(LPMDICHILD FAR *),Name);
  return lstrlen (Name) + sizeof(LPMDICHILD FAR *);
  }

static hash *insProc;
BOOL InstallProcedure (mdiChild *c,void FAR *param,WORD mode)
  {
  InstallProcedure_Param FAR *par = (InstallProcedure_Param FAR *) param;
  char Buffer[128];

  if (mode & EM_LOAD) {
    LPSTR Name = LPSTR (c->ReadlData (par->Name));
    int kSize = SetKey (Buffer,c,Name);

    if (insProc == NULL)
      insProc = new hash (37,VOIDKEY);

    DBWIN_ASSERT (insProc->SetDatav (Buffer,&par->proc,4,kSize));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LPSTR Name = LPSTR (c->ReadlData (par->Name));
    int kSize = SetKey (Buffer,c,Name);

    insProc->DelDatav (Buffer,kSize);
    }

  return FALSE ;
  }

#pragma pack(1)
struct FireProcedure_Param {
  WORD  parSize;
  DWORD inst;
  DWORD Name;
  DWORD proc;
  };
#pragma pack()

BOOL FireProcedure (mdiChild *c,void FAR *param,WORD mode)
  {
  FireProcedure_Param FAR *par = (FireProcedure_Param FAR *) param;
  if (mode & EM_LOAD) {
    LPMDICHILD FAR *inst = (LPMDICHILD FAR *) c->ReadlData (par->inst);
    LPSTR Name = LPSTR (c->ReadlData (par->Name));

    if ((Name != NULL) && (inst != NULL) && (*inst != NULL)) {
      char Buffer[128];

      int kSize = SetKey (Buffer,*inst,Name);

      if (insProc == NULL)
        insProc = new hash (37,VOIDKEY);

      LPDWORD proc = (LPDWORD) insProc->GetDatav (Buffer,kSize);
      if (proc != NULL) {
        (*inst)->ExCuteProc (*proc,EM_LOAD | EM_CHANGETOTRUE);
        (*inst)->ExCuteProc (*proc,EM_RESET | EM_CLEAR);
        }
      }
    }
  return FALSE;
  }
