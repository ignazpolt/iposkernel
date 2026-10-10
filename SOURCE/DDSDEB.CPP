/*-----< Debuggerunterstuetzung im Hauptprogramm >-------*/
//
//  $Header:   P:/marille/clinicum/rev/ddsdeb.cpv   1.8   21 Nov 1997 15:54:38   Hannes  $
//  $Log:   P:/marille/clinicum/rev/ddsdeb.cpv  $
// 
//    Rev 1.8   21 Nov 1997 15:54:38   Hannes
// 
//    Rev 1.7   19 Nov 1997 18:47:42   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.6   18 Aug 1997 17:59:50   Hannes
// 
//    Rev 1.5   02 Feb 1996 10:35:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   24 Aug 1995 00:20:00   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.3   11 Jul 1995 12:47:08   HANNES
// Expressionoptimierung
// 
//    Rev 1.2   20 Mar 1995 11:55:06   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.1   13 Jan 1995 16:55:52   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.0   09 Jan 1995 12:13:58   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>

#ifndef WIN32
  #include <toolhelp.h>
#endif

#include "dds32.h"
#include "globmem.h"
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
#include "communic.hpp"

#define MODULENUM  145
#include "winass.hpp"

#ifdef WIN32
#ifdef DEBUG
#define SHAREMEM
#endif
#endif

BOOL DDSGetCmdFifoInfo (int Nmbr,DebFifoInfo FAR *di)
  {
  BOOL res = GetCmdFifoInfo (Nmbr,di);
  if (res) {
    mdiChild FAR *c = (mdiChild FAR *) (di->DocumentID);
    di->CmdOffset = c->GetCmdOffset (di->Cmd);
    lstrcpy (di->ModuleName,c->schd->fName);
    }
  return res ;
  }

BOOL DDSGetCmdMoreInfo (BYTE CmdNmbr,BYTE HistNmbr,DebFifoInfo FAR *di)
  {
  return GetCmdMoreInfo (CmdNmbr,HistNmbr,di);
  }

/*-------< Memory - Breakpoints >--------*/
struct FAR VarBreakInfo {
  VarBreakInfo FAR *Next;
  VarValExtended ve;
  };
VarBreakInfo FAR *FirstBreakInfo ;
void DDSSetVarBreak (VarValExtended FAR *ve)
  {
  VarBreakInfo FAR *n = (VarBreakInfo FAR *) GetGlobMem (sizeof(*n));
  n->Next = FirstBreakInfo ;
  FirstBreakInfo = n;
  n->ve = *ve ;
  }

void DDSClearVarBreak (VarValExtended FAR *ve)
  {
  VarBreakInfo FAR *prev = NULL;
  for (VarBreakInfo FAR *h = FirstBreakInfo ; h != NULL ; h = h->Next) {
    if ((h->ve.actContext == ve->actContext) &&
        (h->ve.TableID == ve->TableID) &&
        (h->ve.VarID == ve->VarID)) {
      if (prev != NULL) prev->Next     = h->Next ;
      else              FirstBreakInfo = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    prev = h;
    }
  }

BOOL BeforeWrite (mdiChild *c,WORD TableID,WORD VarID)
  {
  BOOL res ;
  LPRECROOT rr = c->rr ;
  LPDBRECORD rec;
  if (rr->AnzTables > TableID)
    rec = rr->GetRecord(TableID);
  else
    rec = NULL ;
  if ((rec != NULL) && (rec->GetAnzVars() > VarID))
    res = TRUE ;
  else {
    static BPInfo h;
    lstrcpy (h.PName,c->schd->fName);
    DWORD progOffs = GetLastStackAddress ();
    h.LineNmbr = GetModuleLine (c->schd->fName,progOffs,h.FName);

    if (!Exception (c)) {
      char outtxt[128];
      wsprintf (outtxt,"No Write allowed for %d/%d in %s",TableID,VarID,c->schd->fName);
      WIN_ASSERT_TEXT (FALSE,outtxt);
      }
    res = FALSE ;
    }
  return res;
  }

void AfterWrite (mdiChild *c,WORD TableID,WORD VarID)
  {
  for (VarBreakInfo FAR *h = FirstBreakInfo ; h != NULL ; h = h->Next) {
    if ((h->ve.actContext == c) && 
                 (h->ve.TableID == TableID) &&
                 (h->ve.VarID == VarID)) {
      // Wenn er schon einen Break haben will, dann soll er ihn haben ...
      static BPInfo h;
      lstrcpy (h.PName,c->schd->fName);
      DWORD progOffs = GetLastStackAddress ();
      h.LineNmbr = GetModuleLine (c->schd->fName,progOffs,h.FName);
      BOOL oldActive = BlockIsActive ;
      BlockIsActive = FALSE ;
      WaitForRestool (c,&h,0xFFFF,c->schd->fName,progOffs,0xFFFF);
      BlockIsActive = oldActive ;
      break ;
      }
    }
  }

BPInfo FAR *FirstBP;
static BOOL doBreakImm;
BPInfo FAR *IsStepBreakPoint (LPSTR fName,DWORD progOffs,WORD mode,WORD FAR *modeMask)
  {
  static BPInfo h;
  LastBreakInfo FAR *lbi = GetLBI();
  if (doBreakImm) {
    lstrcpy (h.PName,fName);
    h.LineNmbr = GetModuleLine (fName,progOffs,h.FName);
    doBreakImm = FALSE ;
    return &h;
    }
  switch (lbi->dbMode) {
    case DBMODE_STEP :
      if (((lbi->ActCSPtr == lbi->LastStackBreak) && (lstrcmp (fName,lbi->LastModuleBreak) == 0)) ||
           (lbi->ActCSPtr < lbi->LastStackBreak)) {
        if (((lstrcmp (fName,lbi->LastModuleBreak) != 0) ||
            (lbi->LastModuleLine != GetModuleLine (fName,progOffs)) ||
            (lbi->LastModuleLine < 0)) && ((mode & lbi->LastModeMask) != 0)
           ) {
          lstrcpy (h.PName,fName);
          h.LineNmbr = GetModuleLine (fName,progOffs,h.FName);
          lbi->dbMode = DBMODE_NORMAL ;
          *modeMask = lbi->LastModeMask ;
          return &h;
          }
        else
          return NULL ;
        }
      else
        return NULL ;
      break ;
    case DBMODE_STEPINTO :
      if (((lstrcmp (fName,lbi->LastModuleBreak) != 0) ||
           (lbi->LastModuleLine != GetModuleLine (fName,progOffs)) ||
           (lbi->LastModuleLine < 0)) && ((mode & lbi->LastModeMask) != 0)
         ) {
        lstrcpy (h.PName,fName);
        h.LineNmbr = GetModuleLine (fName,progOffs,h.FName);
        *modeMask = lbi->LastModeMask ;
        lbi->dbMode = DBMODE_NORMAL ;
        return &h;
        }
      else
        return NULL ;
      break ;
    }
  return NULL ;
  }

void SetBreakImmediately ()
  {
  doBreakImm = TRUE ;
  }

BPInfo FAR *IsBreakPoint (LPSTR fName,DWORD progOffs,WORD mode,WORD FAR *modeMask)
  {
  BOOL found = FALSE ;
  BPInfo FAR *s = IsStepBreakPoint (fName,progOffs,mode,modeMask);
  if (s != NULL) return s;

  for (BPInfo FAR *h = FirstBP ; (h != NULL) ; h = h->Next) {
    if (lstrcmp (fName,h->PName) == 0) {
      int AnzOffs = GetBlockSize (h->pOffs) / sizeof(h->pOffs[0]);
      for (int i = 0 ; i < AnzOffs ; i++) {
        if ((progOffs == h->pOffs[i]) || 
            ((progOffs + sizeof(WORD)) == h->pOffs[i]) || 
            ((progOffs - sizeof(WORD)) == h->pOffs[i])
           ) {
          if ((mode & h->modeMask) != 0) {
            *modeMask = h->modeMask ;
            return h ;
            break ;
            }
          }
        }
      }
    }
  return NULL ;
  }

void BeforeExecution (LPVOID context,WORD mode,LPSTR fName,DWORD progOffs)
  {
  WORD modeMask;
  BPInfo FAR *h = IsBreakPoint (fName,progOffs,mode,&modeMask);
  if (h != NULL) {
    /*----< Es ist ein Breakpoint aufgetreten -> 
            weitere Programmausfuehrung unterbrechen >----*/
    BOOL oldActive = BlockIsActive ;
    BlockIsActive = FALSE ;
    WaitForRestool ((mdiChild *)context,h,mode,fName,progOffs,modeMask);
    BlockIsActive = oldActive ;
    }
  }

void AddBreakpoint (BPInfo FAR *h)
  {
#ifdef SHAREMEM
  DWORD FAR *pOffs = (DWORD FAR *) ((LPSTR) (h + 1) + sizeof(WORD));
#else
  DWORD FAR *pOffs = h->pOffs;
#endif
  // Anlegen einer Kopie von h
  BPInfo FAR *n = (BPInfo FAR *) GetGlobMem (sizeof(*n));
  *n = *h ;
  n->Next = FirstBP ;
  FirstBP = n ;
  n->pOffs = (DWORD FAR *) GetGlobMem (GetBlockSize (pOffs));
  lmemcpy (n->pOffs,pOffs,GetBlockSize (pOffs));
  }

void RemoveBreakpoint (BPInfo FAR *d)
  {
  BPInfo FAR *prev = NULL ;
  for (BPInfo FAR *h = FirstBP ; h != NULL ; h = h->Next) {
    if ((lstrcmp (h->PName,d->PName) == 0) &&
        (lstrcmp (h->FName,d->FName) == 0) &&
        (h->LineNmbr == d->LineNmbr)) {
      if (prev != NULL) prev->Next = h->Next ;
      else              FirstBP = h->Next ;
      FreeGlobMem (h->pOffs) ;
      FreeGlobMem (h);
      break ;
      }
    prev = h ;
    }
  }

void RemoveAllBreakPoints ()
  {
  for ( ; FirstBP != NULL ; ) {
    BPInfo FAR *Next = FirstBP->Next ;
    FreeGlobMem (FirstBP->pOffs) ;
    FreeGlobMem (FirstBP);
    FirstBP = Next ;
    }
  }
