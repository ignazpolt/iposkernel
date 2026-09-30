//////////////////////////////////////////////////////
//  Ermitteln einer Eindeutigen Nummer aus einem 
//  laengeren Schluessel
/////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/getword.cpv   1.1   02 Feb 1996 10:46:16   GERHOLD  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/getword.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:46:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:48   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   04 Jan 1994 17:40:08   HANNES
// Initial revision.
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "getword.hpp"

DLLExport _export WINAPI UniqueWord::UniqueWord (int s)
  {
  keySize = s;
  l = NULL ;
  }

DLLExport _export WINAPI UniqueWord::~UniqueWord ()
  {
  for ( LPUWENT h = l ; h != NULL ; ) {
    LPUWENT n = h->Next ;
    FreeGlobMem (h);
    h = n ;
    }
  }

DLLExport LPVOID _export WINAPI UniqueWord::operator new (size_t s)
  {
  return GetGlobMem (s);
  }

DLLExport void _export WINAPI UniqueWord::operator delete (LPVOID obj)
  {
  FreeGlobMem (obj);
  }

DLLExport void _export WINAPI UniqueWord::RemoveNum (WORD n)
  {
  LPUWENT p = NULL ;
  for (LPUWENT h = l ; h != NULL ; h = h->Next) {
    if (h->Nmbr == n) {
      if (p != NULL) p->Next = h->Next ;
      else           l = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    p = h ;
    }
  }

DLLExport WORD _export WINAPI UniqueWord::GetNum (LPVOID data)
  {
  WORD res = WMIN ;
  for (LPUWENT h = l ; h != NULL ; h = h->Next) {
    if (lmemcmp (data,h->kData,keySize))
      return h->Nmbr;
    if (h->Nmbr >= res) res = h->Nmbr + 1;
    }
  LPUWENT n = LPUWENT (GetGlobMem (sizeof (*n) + keySize - 1)) ;
  n->Next = l ;
  l = n ;
  n->Nmbr = res ;
  lmemcpy (n->kData,data,keySize);
  return res;
  }

DLLExport WORD _export WINAPI UniqueWord::FindNum (LPVOID data)
  {
  for (LPUWENT h = l ; h != NULL ; h = h->Next) {
    if (lmemcmp (data,h->kData,keySize))
      return h->Nmbr;
    }
  return 0;
  }

DLLExport LPVOID _export WINAPI UniqueWord::GetKey (WORD Nmbr)
  {
  for (LPUWENT h = l ; h != NULL ; h = h->Next) {
    if (h->Nmbr == Nmbr)
      return h->kData;
    }
  return NULL ;
  }
