/*
**  Ersatz der Getprofile ... zur Speicherung von Hilfsdaten in dem
**  Restool
*/
//
//  $Header:   P:/marille/clinicum/restool/rev/pradmin.cpv   1.3   21 Nov 1997 15:54:58   Hannes  $
//  $Log:   P:/marille/clinicum/restool/rev/pradmin.cpv  $
// 
//    Rev 1.3   21 Nov 1997 15:54:58   Hannes
// Feinschliff Debugger
// 
//    Rev 1.2   02 Feb 1996 10:50:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   31 Jan 1996 18:18:50   HANNES
// rshelp in dlladmin eingebaut
// 
//    Rev 1.0   16 Feb 1995 12:41:12   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "hash.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"

struct ProfList {
  ProfList FAR *Next;
  char Section[64];
  hash FAR *h;
  DBINT changed;
  };

#define TYPE_PROF   0

static ProfList FAR *pFirst;
ProfList FAR *GetProfList (LPSTR Section)
  {
  for (ProfList FAR *h = pFirst ; h != NULL ; h = h->Next) {
    if (lstrcmp (h->Section,Section) == 0) {
      return h ;
      }
    }
  ProfList FAR *n = (ProfList FAR *) GetGlobMem (sizeof(*n));
  n->Next = pFirst ;
  pFirst = n;
  DWORD Size;
  GLOBALHANDLE hGres = GetDLLAdmin()->GetDLLEntry (GetDLLAdmin()->LoadResDLL())->DBHelp_Get (TYPE_PROF,Section,&Size);
  lstrcpy (n->Section,Section);
  n->h = new hash (111,STRKEY,hGres);
  if (hGres) GlobalFree (hGres);
  return n;
  }

int MyGetProfInt (LPSTR Section,LPSTR Name,int def)
  {
  ProfList FAR *x = GetProfList (Section);
  DBINT FAR *res = (DBINT FAR *) x->h->GetData (Name);
  if (res != NULL)
    return *res ;
  else {
    x->h->SetData (Name,&def,sizeof(def));
    x->changed = TRUE ;
    }
  return def;
  }

void MySetProfInt (LPSTR Section,LPSTR Name,int val)
  {
  ProfList FAR *x = GetProfList (Section);
  LPVOID old = x->h->GetData (Name);
  if (old != NULL)
    x->h->DelData (Name);
  x->h->SetData (Name,&val,sizeof(DBINT));
  x->changed = TRUE ;
  }

void MyProfFlush ()
  {
  for (ProfList FAR *h = pFirst ; h != NULL ; h = h->Next) {
    if (h->changed) {
      GLOBALHANDLE hGres = h->h->StoreHash();
      GetDLLAdmin()->GetDLLEntry (GetDLLAdmin()->LoadResDLL())->DBHelp_Put (TYPE_PROF,h->Section,GlobalLock (hGres),GlobalSize(hGres));
      GlobalUnlock (hGres);
      GlobalFree (hGres);
      h->changed = FALSE ;
      }
    }
  }

