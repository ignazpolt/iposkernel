//////////////////////////////////////////////////////////////////////
//  Sortierung von Kommandos, um mehrfache Updatevorgaenge zu
//  verhindern
//////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/cmdsort.cpv   1.4   06 May 1997 11:01:42   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/cmdsort.cpv  $
// 
//    Rev 1.4   06 May 1997 11:01:42   Hannes
// 
//    Rev 1.3   02 Feb 1996 10:42:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   25 Oct 1995 13:48:14   HANNES
// Aenderungen Hannes
// 
//    Rev 1.1   24 Aug 1995 00:14:28   HANNES
// Debuggeroptimierung
// 
//    Rev 1.0   24 Jun 1994 16:44:44   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   04 Oct 1993 08:45:14   HANNES
// Sortierung der Kommandos auch ueber mehrere Dokumente hinweg
// 
//    Rev 1.1   18 Aug 1993 10:47:08   HANNES
// Verbesserte Fehlerabfragen
// 
//    Rev 1.0   22 Jul 1993 20:58:08   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"

DLLExport LPCMDCOUNT _export WINAPI GetCount(WORD Nr)
  {
  LPCMDCOUNT res = LPCMDCOUNT (GetGlobMem (sizeof(cmdcount) + sizeof(WORD)));
  res->counter[0] = Nr + 32;
  return res;
  }

DLLExport LPCMDCOUNT _export WINAPI PushBlock(LPCMDCOUNT old,WORD InitVal)
  {
  LPCMDCOUNT res = LPCMDCOUNT (GetGlobMem (GetBlockSize(old) + sizeof(old->counter[0])));
  lmemcpy (res,old,GetBlockSize(old));
  res->counter[res->AnzCounter() - 1] = InitVal ;
  FreeGlobMem (old);
  return res;
  }
  
DLLExport LPCMDCOUNT _export WINAPI PopBlock(LPCMDCOUNT old)
  {
  int size = GetBlockSize(old) - sizeof(old->counter[0]);
  if (size <= 0) {
    for (int i = 0 ; i < 100 ; i++)
      MessageBeep (0);
    }
  LPCMDCOUNT res = LPCMDCOUNT (GetGlobMem (size));
  lmemcpy (res,old,size);
  FreeGlobMem (old);
  return res;
  }

DLLExport int _export WINAPI Compare (LPCMDCOUNT c1,LPCMDCOUNT c2)
  {
  int cc1 = c1->AnzCounter();
  int cc2 = c2->AnzCounter();
  int count = min (cc1,cc2);
  short res = 0;
  for (int i = 0 ; ((i < count) && (res == 0)) ; i++) {
    res = c1->counter[i] - c2->counter[i];
    }
  if (res == 0) {
    res = short (cc1 - cc2) ;
    }
  return res;
  }

DLLExport cmdcount FAR *_export WINAPI cmdcount::Copy ()
  {
  int size = GetBlockSize(this) ;
  cmdcount FAR *res = (cmdcount FAR *) (GetGlobMem(size));
  lmemcpy (res , this , size);
  return res ;
  }

