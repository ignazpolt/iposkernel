//////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/cntmenu.cpv   1.2   27 Apr 1999 01:46:20   Hannes  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/cntmenu.cpv  $
// 
//    Rev 1.2   27 Apr 1999 01:46:20   Hannes
// Diverse Speicherfresser
// 
//    Rev 1.1   09 Aug 1998 22:36:00   Hannes
// Verbesserungen Kontextmenue
// 
//    Rev 1.0   29 Oct 1997 18:58:36   Hannes
// Textbausteine
//////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#include "font.hpp"
#include "cfield.hpp"
#include "fldcombo.hpp"

#include "cntmenu.hpp"

struct _CMenuBuffer {
  _CMenuBuffer FAR *Next;
  WORD Kategorie;
  WORD Type;
  WORD Id;
  LPSTR Name;
  DWORD procAddr;
  LPSTR ModName;
  LPSTR FuncName;
  };
_CMenuBuffer FAR *cb;
DLLExport void _export WINAPI FreeGlobalContextMenu ()
  {
  for ( ; cb != NULL ; ) {
    _CMenuBuffer FAR *cbNext = cb->Next ;
    if (cb->Name)     FreeGlobMem (cb->Name);
    if (cb->ModName)  FreeGlobMem (cb->ModName);
    if (cb->FuncName) FreeGlobMem (cb->FuncName);
    FreeGlobMem (cb);
    cb = cbNext ;
    }
  }

DLLExport void _export WINAPI AddGlobalContextMenu (WORD Kategorie,WORD Type,LPSTR Name,LPSTR ModName,LPSTR FuncName)
  {
  _CMenuBuffer FAR *cbNeu = (_CMenuBuffer FAR *) GetGlobMem (sizeof(*cbNeu));
  cbNeu->ModName = LPSTR (GetGlobMem (lstrlen (ModName) + 1));
  lstrcpy (cbNeu->ModName,ModName);
  cbNeu->FuncName = LPSTR (GetGlobMem (lstrlen (FuncName) + 1));
  lstrcpy (cbNeu->FuncName,FuncName);
  cbNeu->Name = LPSTR (GetGlobMem (lstrlen(Name) + 1));
  lstrcpy (cbNeu->Name,Name);
  cbNeu->Type = Type;
  cbNeu->Kategorie = Kategorie;
  
  _CMenuBuffer FAR *h = cb;
  for ( WORD Id = 20000 ; (h != NULL) ; ) {
    Id = Id + 1;
    if (h->Next == NULL) break ;
    else                 h = h->Next;
    }
  if (h != NULL)
    h->Next = cbNeu ;
  else
    cb = cbNeu ;
  cbNeu->Id = Id ;
  }

DLLExport WORD _export WINAPI GetFirstContextMenu (WORD Type,WORD Kategorie,LPSTR Buffer,int bSize)
  {
  for (_CMenuBuffer FAR *h = cb ; (h != NULL) ; h = h->Next) {
    if ((h->Type != Type) || (h->Kategorie != Kategorie))
      continue ;
    lstrncpy (Buffer,h->Name,bSize);
    return h->Id;
    }
  return 0;
  }

DLLExport WORD _export WINAPI GetNextContextMenu (WORD Type,WORD Kategorie,WORD LastID,LPSTR Buffer,int bSize)
  {
  BOOL found = FALSE ;
  for (_CMenuBuffer FAR *h = cb ; (h != NULL) ; h = h->Next) {
    if ((h->Type == Type) && (h->Kategorie == Kategorie) && (found)) {
      lstrncpy (Buffer,h->Name,bSize);
      return h->Id;
      }
    if (h->Id == LastID) found = TRUE ;
    }
  return 0;
  }

CALLCONTEXTFUNCTION CallContextFunction;
DLLExport void _export WINAPI CallContextMenu (WORD Id,LPVOID obj)
  {
  for (_CMenuBuffer FAR *h = cb ; (h != NULL) ; h = h->Next) {
    if (h->Id == Id) {
      (* CallContextFunction) (h->ModName,h->FuncName,obj);
      }
    }
  }

