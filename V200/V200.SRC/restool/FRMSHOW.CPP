////////////////////////////////////////////////////////////
//  Verwaltung der uFrmShow - Kommandos
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/frmshow.cpv   1.7   02 Feb 1996 10:50:52   GERHOLD  $
//  $Log:   P:/marille/clinicum/restool/rev/frmshow.cpv  $
// 
//    Rev 1.7   02 Feb 1996 10:50:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   23 May 1995 11:56:32   GERHOLD
// GetAnzSides() ... ausgebessert: Rueckgabewert +1 (mind. 1 Seite)
// 
//    Rev 1.5   15 May 1995 08:51:10   GERHOLD
// 
//    Rev 1.4   02 Jan 1995 09:30:20   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.3   02 Aug 1994 14:10:44   HANNES
// 
//    Rev 1.2   25 Jul 1994 10:43:20   HANNES
// 
//    Rev 1.1   12 Jul 1994 18:16:06   HANNES
// 
//    Rev 1.0   12 Jul 1994 14:43:56   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "wonscrip.hpp"
#define MODULENUM 116
#include "winass.hpp"

#define JUST_EM
#include "dds.hpp"

#include "font.hpp"
#include "cfield.hpp"
#define NODLL
#include "toolbar.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"

#include "drdrop.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "image.hpp"
#include "frmobj3.hpp"

#include "template.hpp"
#include "hlines.hpp"

#include "misc.hpp"

extern HANDLE MyInstance;
extern HWND hOptWnd ;
extern HWND hRefWnd;
extern hash FAR *defines;
extern hash *objHash;
extern char _MyObjectName [32];
extern char _MyScreenName [32];
extern WORD FrmType;
extern LPDIALOGELEM firstElem;

static char FrmShowCommand[] = "uFrmShowObject";
LPSHOWOBJECT firstShow;
BOOL CheckFrmName (LPSTR h)
  { return mystrcmp (h,FrmShowCommand); }

void ShowObject::AddToList ()
  {
  LPSHOWOBJECT FAR *h = &firstShow ;
  for ( ; *h != NULL ; h = &(*h)->Next) ;
  *h = this ;
  }

void ShowObject::MarkEnd (LPLINE h,WORD e)
  { 
  eLine = h ; 
  ePos = e ; 
  }

void ShowObject::PushParToParList (LPSTR t)
  {
  LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzParams + 1) * sizeof(LPSTR));
  if (Param != NULL) {
    lmemcpy (n,Param,AnzParams * sizeof(LPSTR));
    FreeGlobMem (Param);
    }
  Param = n;
  if (t != NULL) {
    n[AnzParams] = LPSTR(GetGlobMem (lstrlen(t)+1));
    lstrcpy (n[AnzParams],t);
    }
  else
    n[AnzParams] = LPSTR(GetGlobMem (1));
  AnzParams ++;
  }

LPSTR ShowObject::PushPar (LPSTR t,LPLINE FAR *h,LPLINE last)
  {
  LPSTR res = NULL;
  t = FindEndPar (t,&res,h,last);
  if (t != NULL) {
    PushParToParList (res);
    }
  if (res != NULL) FreeGlobMem (res);
  return t;
  }

LPSTR ShowObject::GetCommand ()
  {
  LPSTR h = PushToCommand (NULL,FrmShowCommand);
  h = PushToCommand (h," (");
  for (WORD i = 0 ; i < AnzParams ; i++) {
    h = PushToCommand (h,Param[i]);
    if (i < AnzParams - 1)
      h = PushToCommand (h,",");
    }
  h = PushToCommand (h,")");

  return h;
  }

extern char StdPrefix[];
extern char StdPostfix[];
LPSTR ShowObject::GetText ()
  {
  LPSTR Text;
  if (sLine != NULL) {
    LPSTR TextBefore = LPSTR (GetGlobMem (sPos + 1));
    lmemcpy (TextBefore,sLine->Text,sPos);
    LPSTR TextBehind = LPSTR (GetGlobMem (lstrlen(eLine->Text) - ePos + 1));
    lmemcpy (TextBehind,eLine->Text+ePos,lstrlen(eLine->Text) - ePos);
    LPSTR Command = GetCommand ();
    Text = LPSTR (GetGlobMem (lstrlen(TextBefore) + lstrlen(Command) + lstrlen(TextBehind) + 1));
    lstrcpy (Text,TextBefore);
    lstrcat (Text,Command);
    lstrcat (Text,TextBehind);

    FreeGlobMem (Command);
    FreeGlobMem (TextBefore);
    FreeGlobMem (TextBehind);
    }
  else {
    LPSTR Command = GetCommand ();
    Text = LPSTR (GetGlobMem (lstrlen(StdPrefix) + lstrlen(Command) + lstrlen(StdPostfix) + 1));
    lstrcpy (Text,StdPrefix);
    lstrcat (Text,Command);
    lstrcat (Text,StdPostfix);

    FreeGlobMem (Command);
    }

  return Text;
  }
void ShowObject::FreeLines (LPLINE FAR *lSelected,LPLINE FAR *last)
  {
  if ((sLine != NULL) && (sLine != eLine)) {
    // Alle Nachfolgenden Zeilen loeschen
    for (LPLINE n = sLine->Next ; n != NULL ; ) {
      sLine->Next = n->Next ;
      if (n->Next != NULL) n->Next->Prev = sLine ;
      else                 *last = sLine;
      FreeGlobMem (n->Text);
      FreeGlobMem (n);
      if (n == *lSelected) *lSelected = sLine;
      if (n == eLine) break ;
      n = sLine->Next;
      }
    }
  }
LPLINE ShowObject::SetCommand (LPSTR Text,LPLINE ActLine,LPTEXTBLOCK bl)
  {
  if (sLine != NULL) {
    FreeGlobMem (sLine->Text);
    sLine->Text = LPSTR(GetGlobMem (lstrlen(Text)+1));
    lstrcpy (sLine->Text,Text);
    return sLine;
    }
  else
    return bl->InsertLineBefore (ActLine,Text);
  }

void ShowObject::SetElem ()
  {
  char actname[64];
  LPSTR n = ScanString (Param[0]);
  lstrcpy (actname,n);
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (!h->IsDeleted) {
      LPSTR n1 = ScanString (h->Param[0]);
      if (lstrcmp (actname,n1) == 0) {
        elem = h ;
        return ;
        }
      }
    }
  }

void SetElemPtrs ()
  {
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; h = h->Next)
    h->SetElem ();
  }

LPSHOWOBJECT FindShowForElem (LPDIALOGELEM x)
  {
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; h = h->Next)
    if (h->elem == x) return h;
  return NULL;
  }
LPSHOWOBJECT GetShowElem (LPSTR t,LPLINE l,WORD sPos)
  {
  if (CheckFrmName (t)) return new ShowObject (l,sPos);
  return NULL;
  }

void DeleteShows()
  {
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; ) {
    LPSHOWOBJECT n = h->Next;
    delete h ;
    h = n ;
    }
  firstShow = NULL;
  }

void MarkShowForDel(LPDIALOGELEM x)
  {
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; h = h->Next) {
    if (h->elem == x) {
      h->IsDeleted = TRUE ;
      break ;
      }
    }
  }

int GetShownNmbr(LPDIALOGELEM elem)
  {
  int i = 0;
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; h = h->Next , i++) {
    if (h->elem == elem) return i ;
    }
  return -1;
  }
LPDIALOGELEM GetShownElemByNmbr(int Num)
  {
  int i = 0;
  for (LPSHOWOBJECT h = firstShow ; h != NULL ; h = h->Next , i++) {
    if (i == Num) return h->elem ;
    }
  return NULL;
  }

int GetSide()
  {
  int res ;
  if ((firstShow != NULL) && (firstShow->AnzParams > 1))
    res = int(ScanInt (firstShow->Param[1]));
  else
    res = 0;
  return res;
  }

//---------------------  GetSideFromShow  -----------------------------------
//
// auf welcher Seite befindet sich das Objekt?                            
//---------------------------------------------------------------------------
int GetSideFromShow (LPSHOWOBJECT so)
  {
  int res ;
  if ((so != NULL) && (so->AnzParams > 1))
    res = int(ScanInt (so->Param[1]));
  else
    res = 0;
  return res;
  }

//---------------------  GetAnzSides  ---------------------------------------
//
// gibt bei existiertendem "uFrmShowObject" die Anzahl der Seiten zurueck.
//---------------------------------------------------------------------------
int GetAnzSides ()
  {
  if (firstShow == NULL)
    return 1;
    
  for (LPSHOWOBJECT h = firstShow ; h->Next != NULL ; h = h->Next);  // alle durch
  return (GetSideFromShow (h)+1);
  }


void NewShow(LPSTR objName)
  {
  LPSHOWOBJECT n = new ShowObject (NULL,0);
  int Side = GetSide ();
  n->PushParToParList (objName);
  if (Side != 0) {
    char sidetxt[32];
    wsprintf (sidetxt,"%d",Side);
    n->PushParToParList (objName);
    }
  n->SetElem ();
  }

#define XCHG(A,B)               \
  lmemcpy (dummy,&A,sizeof(A)); \
  A = B;                        \
  lmemcpy (&B,dummy,sizeof(B))
BOOL ExChangeShow (LPDIALOGELEM e1,LPDIALOGELEM e2)
  {
  LPSHOWOBJECT x1 = FindShowForElem (e1);
  LPSHOWOBJECT x2 = FindShowForElem (e2);
  if ((x1 != NULL) && (x2 != NULL)) {
    // Die entscheidenden Elemente austauschen
    ////////////////////////////////////////////
    char dummy[128];
    XCHG(x1->IsDeleted ,x2->IsDeleted );
    XCHG(x1->AnzParams ,x2->AnzParams );
    XCHG(x1->Param     ,x2->Param     );
    XCHG(x1->elem      ,x2->elem      );
    return TRUE ;
    }
  return FALSE ;
  }
