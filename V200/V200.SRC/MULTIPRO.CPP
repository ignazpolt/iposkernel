/////////////////////////////////////////////////////////////////
//  Verwaltung von Prozeduren, die Dupliziert werden sollen
/////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/multipro.cpv   1.10   28 Feb 1997 14:46:02   Hannes  $
//  $Log:   P:/marille/clinicum/rev/multipro.cpv  $
// 
//    Rev 1.10   28 Feb 1997 14:46:02   Hannes
// Hashtabellen fuer Schluesselsuche
// 
//    Rev 1.9   02 Feb 1996 10:34:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   24 Aug 1995 00:19:56   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.7   11 Jul 1995 12:47:44   HANNES
// Expressionoptimierung
// 
//    Rev 1.6   14 Jun 1995 13:02:18   HANNES
// Eigene Liste von ExpPtrs fuer jede Instanz einer Listenprozedur
// 
//    Rev 1.5   20 Mar 1995 12:05:26   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.4   09 Jan 1995 12:14:34   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   05 Dec 1994 17:42:32   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.2   29 Aug 1994 12:45:44   HANNES
// Ausfuehern der Operationen ohne c->base umzusetzen
// 
//    Rev 1.1   24 Aug 1994 19:44:48   HANNES
// Erweiterung auf MultiProzedurFaehigkeit
// 
//    Rev 1.0   05 Aug 1994 17:15:10   HANNES
// Initial revision.
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

#define MODULENUM 121
#include "winass.hpp"

#include "hash.hpp"
#include "multipro.hpp"

#include "compile.hpp"
#include "scdb.hpp"

typedef char _huge * HPSTR;

MultiProc::~MultiProc ()
  {
  DBWIN_ASSERT ((tail == NULL) && (head == NULL)) ;
  FreeGlobMem (pinfo);
  if (kHash != NULL) delete kHash;
  }

MultiProc::MultiProc (mdiChild *m,DWORD p,BOOL useHash)
  {
  pinfo = (ProcInfo FAR *) GetGlobMem (sizeof(*pinfo));
  pinfo[0].Typ = 0;
  pinfo[0].ProcPtr = p ;
  AnzTypes = 1;
  c = m;
  if (useHash) kHash = new hash (57,VOIDKEY);
  }

MultiProc::MultiProc (mdiChild *m,int FAR *t,DWORD FAR *p,int Anz)
  {
  pinfo = (ProcInfo FAR *) GetGlobMem (sizeof(*pinfo) * Anz);
  for (int i = 0 ; i < Anz ; i++) {
    pinfo[i].Typ = t[i];
    pinfo[i].ProcPtr = p[i];
    }
  AnzTypes = Anz;
  c = m;
  kHash = new hash (57,VOIDKEY);
  }

DWORD MultiProc::ProcPtr (int type)
  {
  for (int i = 0 ; i < AnzTypes ; i++) {
    if (pinfo[i].Typ == type) return pinfo[i].ProcPtr ;
    }
  DBWIN_ASSERT (FALSE);
  return 0L;
  }

int MultiProc::ProcSize (int type)
  {
  HPSTR cmd = HPSTR (c->base) + ProcPtr(type) ;
  DWORD p = *(DWORD FAR *) (cmd);
  return int (p) ;
  }

int MultiProc::EntSize (int type)
  {
  return sizeof(ProcEntry) + ProcSize(type) ;
  }

void MultiProc::AddProcAtHead (int type)
  {
  LPPROCENT n = LPPROCENT (GetGlobMem (EntSize(type))) ;
  hmemcpy (n+1,HPSTR(c->base)+ProcPtr(type),ProcSize(type));
  n->Next = head ;
  head->Prev = n ;
  head = n;
  if (tail == NULL) tail = n;
  }

void MultiProc::AddProc (LPPRIMKEY k,int type)
  {
  LPPROCENT n = LPPROCENT (GetGlobMem (EntSize(type))) ;
  n->key = new PrimKey ();
  *(n->key) = *k;
  hmemcpy (n+1,HPSTR(c->base)+ProcPtr(type),ProcSize(type));
  if (head != NULL) {
    n->Next = head ;
    head->Prev = n ;
    }
  head = n;
  if (tail == NULL) tail = n;
  kHash->SetDatav (k->Data,&n,sizeof(n),GetBlockSize(k->Data));
  }

void MultiProc::AddProcAtTail (int type)
  {
  LPPROCENT n = LPPROCENT (GetGlobMem (EntSize(type))) ;
  hmemcpy (n+1,HPSTR(c->base)+ProcPtr(type),ProcSize(type));
  if (tail != NULL) {
    tail->Next = n;
    n->Prev = tail ;
    }
  tail = n;
  if (head == NULL) head = n;
  }

extern BOOL DontCheckCallDone;
BOOL MultiProc::ExCute (LPPRIMKEY k,WORD mode,SetExtraInfo *x)
  {
  LPPROCENT FAR *lph = (LPPROCENT FAR *) kHash->GetDatav (k->Data,GetBlockSize(k->Data));
  if (lph != NULL) {
    x->SetCmdBase (LPSTR((*lph)+1));
    BOOL oldDontCheckCallDone = DontCheckCallDone ;
    if ((mode & EM_UPDATE) != 0)
      DontCheckCallDone = TRUE ;
    BOOL res = c->ExCuteBlock (LPSTR((*lph)+1)+sizeof(DWORD),0L,mode);
    DontCheckCallDone = oldDontCheckCallDone;
    return res ;
    }
  return FALSE ;
  }

BOOL MultiProc::ExCuteLast (WORD mode,SetExtraInfo *x)
  {
  DBWIN_ASSERT (tail != NULL) ;
  x->SetCmdBase (LPSTR(tail+1));
  BOOL res = c->ExCuteBlock (LPSTR(tail+1)+sizeof(DWORD),0L,mode);

  return res;
  }

BOOL MultiProc::ExCuteFirst (WORD mode,SetExtraInfo *x)
  {
  DBWIN_ASSERT (head != NULL) ;
  x->SetCmdBase (LPSTR(head+1));
  BOOL res = c->ExCuteBlock (LPSTR(head+1)+sizeof(DWORD),0L,mode);

  return res;
  }

BOOL MultiProc::RemoveFirst ()
  {
  if (head != NULL) {
    LPPROCENT p = head->Next ;
    if (head->key != NULL) {
      kHash->DelDatav (head->key->Data,GetBlockSize(head->key->Data));
      delete head->key;
      }
    head->RemoveExpressions ();
    FreeGlobMem (head) ;
    head = p;
    if (p != NULL) p->Prev = NULL ;
    if (head == NULL) tail = NULL ;
    return TRUE ;
    }
  return FALSE ;
  }

BOOL MultiProc::Remove (LPPRIMKEY k)
  {
  LPPROCENT FAR *lph = (LPPROCENT FAR *) kHash->GetDatav (k->Data,GetBlockSize(k->Data));
  if (lph != NULL) {
    delete (*lph)->key;
    if ((*lph)->Prev != NULL) (*lph)->Prev->Next = (*lph)->Next ;
    else                      head = (*lph)->Next ;
    if ((*lph)->Next != NULL) (*lph)->Next->Prev = (*lph)->Prev ;
    else                      tail = (*lph)->Prev ;
    (*lph)->RemoveExpressions ();
    FreeGlobMem (*lph);
    kHash->DelDatav (k->Data,GetBlockSize(k->Data));
    return TRUE ;
    }
  return FALSE ;
  }

BOOL MultiProc::RemoveLast ()
  {
  if (tail != NULL) {
    LPPROCENT p = tail->Prev ;
    if (tail->key != NULL) {
      kHash->DelDatav (tail->key->Data,GetBlockSize(tail->key->Data));
      delete tail->key;
      }
    tail->RemoveExpressions ();
    FreeGlobMem (tail) ;
    tail = p;
    if (p != NULL) p->Next = NULL ;
    if (tail == NULL) head = NULL ;
    return TRUE ;
    }
  return FALSE ;
  }

void MultiProc::RemoveAll ()
  {
  for ( ; RemoveFirst () ; ) ;
  }

