// $Header:   P:/marille/clinicum/compile/rev/twodim.cpv   1.3   22 Aug 1997 14:53:42   Martin  $
// $Log:   P:/marille/clinicum/compile/rev/twodim.cpv  $
// 
//    Rev 1.3   22 Aug 1997 14:53:42   Martin
// FreeMem korrigiert
// 
//    Rev 1.2   22 Aug 1997 12:02:02   Hannes
// TwoDim: GetGlobalMem ausgebaut
// 
//    Rev 1.1   02 Feb 1996 10:41:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 18:04:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   02 Dec 1992 16:17:30   HANNES
// Initial revision.
/////////////////////////////////////////////////////////////
//      Verwaltung einer 2dim. Liste
/////////////////////////////////////////////////////////////
#include <windows.h>
#include "dds32.h"
#include "globmem.h"
#include "twodim.hpp"

dList& dList::operator [] (WORD primind)
  {
  BOOL found = FALSE ;
  for ( actList = *ListStart ; (actList != NULL) ; ) {
    if (actList->Ind == primind) {
      found = TRUE ;
      break ;
      }
    actList = actList->next ;
    }
  if (!found) {
    actList = LPFLE (GetGlobMem (sizeof(*actList)));
    actList->ListStart = NULL;
    actList->Ind = primind;
    actList->next = *ListStart;
    *ListStart = actList ;
    }
  return *this;
  }

void dList::Add (void FAR *data,int size)
  {
  LPSLE le = LPSLE (GetGlobMem (sizeof(*le) + size));
  le->next = actList->ListStart ;
  actList->ListStart = le ;
  lmemcpy (le+1,data,size);
  }

void dList::Traverse (WORD Num,LISTTRFUNCTION fnc,LPVOID prvData)
  {
  for (actList = *ListStart ; actList ; ) {
    if (actList->Ind == Num) {
      // Und diese Liste nun abgrasen
      for ( LPSLE e = actList->ListStart ; (e != NULL) ; ) {
        (* fnc) (e+1,prvData);
        e = e->next ;
        }
      // fertig ;
      break ;
      }
    actList = actList->next ;
    }
  }

void dList::Traverse (FULLLISTTRFUNCTION fnc,LPVOID prvData)
  {
  for (actList = *ListStart ; (actList != NULL) ; ) {
    // Und diese Liste nun abgrasen
    for ( LPSLE e = actList->ListStart ; e ; ) {
      (* fnc) (actList->Ind,e+1,prvData);
      e = e->next ;
      }
    actList = actList->next ;
    }
  }

void eList::Add (void FAR *data,int size)
  {
  LPSLE le = LPSLE (GetGlobMem (sizeof(*le) + size));
  le->next = *ListStart ;
  *ListStart = le ;
  lmemcpy (le+1,data,size);
  }

void eList::Traverse (LISTTRFUNCTION fnc,LPVOID prvData)
  {
  for (LPSLE e = *ListStart ; (e != NULL) ; ) {
    (* fnc) (e+1,prvData);
    e = e->next ;
    }
  }

void firstListEle::FreeMem ()
  {
  for ( ; ListStart != NULL ; ) {
    secondListEle FAR *n = ListStart->next;
    FreeGlobMem(ListStart);
    ListStart = n;
    }
  }

