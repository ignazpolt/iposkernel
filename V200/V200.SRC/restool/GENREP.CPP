////////////////////////////////////////////////////////////////////////////
//  Generieren des Replikationsschemas
////////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genrep.cpv   1.7   05 Oct 1998 11:26:38   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/genrep.cpv  $
// 
//    Rev 1.7   05 Oct 1998 11:26:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.6   01 Dec 1997 19:38:52   Hannes
// Diverse Anpassungen
// 
//    Rev 1.5   19 Nov 1997 18:44:28   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.4   28 Aug 1997 14:30:58   Gerhold
// 32-Bit-Umstellung
// 
//    Rev 1.3   18 Jul 1997 08:07:26   Hannes
// 
//    Rev 1.2   19 Feb 1997 12:14:18   Hannes
// Parent von Tabellendefinition / Scriptfunktionen neu
// 
//    Rev 1.1   26 Nov 1996 08:10:26   HANNES
// Automatischer Update
// 
//    Rev 1.0   08 Nov 1996 13:31:16   HANNES
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 19
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbcmpl.hpp"
#include "dbrecord.hpp"

extern HINSTANCE MyInstance;
HWND hRepWnd;
class RepCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  RepCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI RepCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,REPCMPL_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

#define REPCMPERROR    1000
static char errText[128];
DLLExport BOOL _export WINAPI RepCompiler::TestError ()
  {
  if (wError >= REPCMPERROR) {
    if (GetCommandLineFlag())
      LogMsg (errText);
    else
      MessageBox (hRepWnd,errText,"Resourcefehler",MB_OK | MB_TASKMODAL);
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static RepCompiler FAR *RCmp;

/////////////////////////////////////////////////////////////////////////
//  Codegenerierung
/////////////////////////////////////////////////////////////////////////
static int level;
LPREPNODE rpAct;
LPREPNODE rpStack[32];

int AnzReps;
LPREPNODE FAR *repList;
void AddRepNodeToList(LPREPNODE r)
  {
  LPREPNODE FAR *n = (LPREPNODE FAR *) GetGlobMem (sizeof(*n) * (AnzReps + 1));
  if (repList != NULL) {
    lmemcpy (n,repList,GetBlockSize(repList));
    FreeGlobMem (repList);
    }
  repList = n ;
  n[AnzReps++] = r ;
  }

int FindRIFromTo (LPTABLEDEF from,LPTABLEDEF to,int FAR *foreign,int FAR *primary)
      // foreign ... VarID in der From - Table der Variable, die auf to zeigt
      // primary ... VarID in der To Table, die mit einem eq - Join dazugeladen 
      //             werden kann
  {
  int done = 0 ;
  for (int i = 0 ; i < from->GetAnzRIDefs() ; i++) {
    if (done >= 0) {
      LPCLRIDEF r = from->GetRIDef (i);
      if (lstrcmp (r->name,to->GetName()) == 0) {
        if ((r->AnzSegs == 1) && (r->Type == CLKR_STANDARD)) {
          StandardRI FAR *s = r->GetSRI();
          BOOL primDone = FALSE ;
          *foreign = s->VarID;
          for ( int j = 0 ; j < to->GetAnzVars() ; j++) {
            if (lstrcmp (to->GetVarDef(j)->GetName(),s->ForeignField) == 0) {
              *primary = j ;
              primDone = TRUE ;
              break ;
              }
            }
          if (primDone)
            done ++ ;
          else
            done = -1;
          }
        else
          done = -1 ;
        }
      }
    }
  return done;
  }

static LPSTR TableName,ActSelection;
void FreeTableName ()
  {
  if (TableName != NULL) FreeGlobMem (TableName);
  TableName = NULL;
  }
void FreeSelection ()
  {
  if (ActSelection != NULL) FreeGlobMem (ActSelection);
  ActSelection = NULL;
  }
void SetTableName (LPSTR Name)
  {
  FreeTableName();
  TableName = LPSTR (GetGlobMem (lstrlen (Name) + 1));
  lstrcpy (TableName,Name);
  }

static TableRef atpRef;
static DBINT UpdateModeIndex;
DLLExport void _export _SetActUpdateModeIndexForDelete ()
  {
  UpdateModeIndex = 1 ;
  }
DLLExport void _export _SetExtraSelection ()
  {
  LPSTR Name = TableName ;
  LPSTR VarName = LPSTR (GlobalLock (RCmp->hPars0)) + sizeof(WORD) ;
  BOOL found;
  WORD Version;
  WORD tid = GetTableAdmin()->GetTableID (NULL,Name,&found,&Version);
  if (found) {
    LPTABLEDEF t = GetTableAdmin()->GetTableDef(tid,Version);

    WORD pForeignVar;
    if (level == 0) {
      RCmp->wError = REPCMPERROR ;
      wsprintf (errText,"Zugriffangabe erst fuer Subbaeme gestattet: %s",Name);
      }
    else {
      LPTABLEDEF tParent = GetTableAdmin()->GetTableDef(rpStack[level-1]->tRef.TableNr,rpStack[level-1]->tRef.Version);
      atpRef = rpStack[level-1]->tRef;

      for (int i = 0 ; i < tParent->GetAnzVars() ; i++) {
        if (lstrcmp (tParent->GetVarDef(i)->GetName(),VarName) == 0) break ;
        }

      if (i == tParent->GetAnzVars()) {
        RCmp->wError = REPCMPERROR ;
        wsprintf (errText,"Unbekannte Variable in der Vatertabelle: %s",VarName);
        }
      else 
        pForeignVar = i ;
      GetTableAdmin()->FreeTable(rpStack[level-1]->tRef.TableNr,rpStack[level-1]->tRef.Version);
      }

    if (RCmp->wError == 0) {
      LPREPNODE r = LPREPNODE (GetGlobMem (MAXREPSIZE));
      r->tRef.TableNr = t->GetTableID();
      r->tRef.Version = t->GetVersion();
      r->pForeignVar = pForeignVar ;
      r->pForeignVar1 = 0xFFFF ;
      r->Selection = LPSTR (GetGlobMem (lstrlen(ActSelection) + 1));
      lstrcpy (r->Selection,ActSelection);
      rpAct = r;
      rpStack[level-1]->PushSubNode (r);
      }
    GetTableAdmin()->FreeTable(tid,Version);
    }
  else {
    RCmp->wError = REPCMPERROR ;
    wsprintf (errText,"unbekannte Tabelle: %s",Name);
    }
  }

DLLExport void _export _SetF1 ()
  {
  LPSTR VarName = LPSTR (GlobalLock (RCmp->hPars0)) + sizeof(WORD) ;
  LPTABLEDEF tParent = GetTableAdmin()->GetTableDef(atpRef.TableNr,atpRef.Version);

  for (int i = 0 ; i < tParent->GetAnzVars() ; i++) {
    if (lstrcmp (tParent->GetVarDef(i)->GetName(),VarName) == 0) break ;
    }

  if (i == tParent->GetAnzVars()) {
    RCmp->wError = REPCMPERROR ;
    wsprintf (errText,"Unbekannte Variable in der Vatertabelle: %s",VarName);
    }
  else 
    rpAct->pForeignVar1 = i ;
  GetTableAdmin()->FreeTable(atpRef.TableNr,atpRef.Version);
  }

DLLExport void _export _SetSelection ()
  {
  FreeSelection ();
  LPSTR Name = LPSTR (GlobalLock (RCmp->hPars0)) + sizeof(WORD);
  ActSelection = LPSTR (GetGlobMem (lstrlen(Name) + 1));
  lstrcpy (ActSelection,Name);
  }

WORD actPrio ;
DLLExport void _export _SetTableID ()
  {
  LPSTR Name = TableName ;
  BOOL found;
  WORD Version;
  WORD tid = GetTableAdmin()->GetTableID (NULL,Name,&found,&Version);
  if (found) {
    LPTABLEDEF t = GetTableAdmin()->GetTableDef(tid,Version);
    LPCLKEYDEF k0 = t->GetKeyDef(0);
    LPVARDEF v0;    // Primaerschluessel
    char s[256];
    if ((t->GetAnzKeySegs() > 1) && (t->GetKeyDef(1)->KeyNmbr == k0->KeyNmbr))
      v0 = NULL ;
    else
      v0 = t->GetVarDef(k0->VarID);

    WORD pForeignVar;
    if (level == 0) {
      pForeignVar = 0xFFFF ;
      if (v0 != NULL)
        wsprintf (s,"%s = %%1",v0->GetName());
      else
        RCmp->wError = REPCMPERROR ;
      }
    else {
      LPTABLEDEF tParent = GetTableAdmin()->GetTableDef(rpStack[level-1]->tRef.TableNr,rpStack[level-1]->tRef.Version);
      int fSubKey,fParentKey,pSubKey,pParentKey;
      int AnzSubRI = FindRIFromTo (tParent,t,&fSubKey,&pSubKey);
      int AnzParentRI = FindRIFromTo (t,tParent,&fParentKey,&pParentKey);
      if ((AnzSubRI < 0) || (AnzParentRI < 0) || ((AnzSubRI + AnzParentRI) != 1)) {
        RCmp->wError = REPCMPERROR ;
        wsprintf (errText,"keine gueltige RI - Verbindung zum Vaterknoten: %s",Name);
        }
      else {
        if (AnzSubRI == 1) {
          pForeignVar = fSubKey;
          wsprintf (s,"%s = %%1",t->GetVarDef(pSubKey)->GetName());
          }
        else {
          pForeignVar = pParentKey;
          wsprintf (s,"%s = %%1",t->GetVarDef(fParentKey)->GetName());
          }
        }
      GetTableAdmin()->FreeTable(rpStack[level-1]->tRef.TableNr,rpStack[level-1]->tRef.Version);
      }

    if (RCmp->wError != 0) {
      if (!*errText)
        wsprintf (errText,"mehr als ein Segment auf dem Primaerschluessel: %s",Name);
      }
    else {
      LPREPNODE r = LPREPNODE (GetGlobMem (MAXREPSIZE));
      r->updateModeIndex = UpdateModeIndex ;
      UpdateModeIndex = 0;
      r->tRef.TableNr = t->GetTableID();
      r->tRef.Version = t->GetVersion();
      r->pForeignVar = pForeignVar ;
      r->pForeignVar1 = 0xFFFF ;
      r->Selection = LPSTR (GetGlobMem (lstrlen(s) + 1));
      lstrcpy (r->Selection,s);
      rpAct = r;
      if (level > 0)
        rpStack[level-1]->PushSubNode (r);
      else {
        r->Prio = actPrio;
        actPrio ++ ;
        AddRepNodeToList(r);
        }
      }
    GetTableAdmin()->FreeTable(tid,Version);
    }
  else {
    RCmp->wError = REPCMPERROR ;
    wsprintf (errText,"unbekannte Tabelle: %s",Name);
    }
  }
DLLExport void _export _SetTbName ()
  {
  SetTableName (LPSTR(GlobalLock(RCmp->hPars0)) + sizeof(WORD));
  }

DLLExport void _export _PushRepNode ()
  {
  rpStack[level++] = rpAct ;
  }

DLLExport void _export _PopRepNode ()
  {
  level-- ;
  }

/////////////////////////////////////////////////////////////////////////
//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
extern syntax_node b0,b2,rep0;

syntax_node pn5 = { NULL , NULL , TRUE , INITERM(FREECHAR,0) , _SetTableID } ;
syntax_node pn4 = { NULL , NULL , TRUE , INITERM(KEYWORD,REP_BCC) , NULL } ;
syntax_node pn3b = { &pn4 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetF1 } ;
syntax_node pn3a = { &pn3b , &pn4 , TRUE , INITERM(KEYWORD,REP_COLON) , NULL } ;
syntax_node pn3 = { &pn3a , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetExtraSelection } ;
syntax_node pn2 = { &pn3 , NULL , TRUE , INITERM(KEYWORD,REP_BCO) , NULL } ;
syntax_node pn1 = { &pn2 , &pn5 , TRUE , INITERM(STRING,0) , _SetSelection } ;
syntax_node pn0 = { &pn1 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetTbName } ;

syntax_node b5 = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node b4 = { NULL , NULL , TRUE  , INITERM(KEYWORD,REP_BCC) , _PopRepNode } ;
syntax_node b3 = { &b2  , &b4  , TRUE  , INITERM(KEYWORD,REP_COLON) , NULL } ;
syntax_node b2 = { &b3  , NULL , FALSE , &b0 , NULL } ;
syntax_node b1 = { &b2  , &b5  , TRUE  , INITERM(KEYWORD,REP_BCO) , _PushRepNode } ;
syntax_node b0 = { &b1  , NULL , FALSE , &pn0 , NULL } ;
syntax_node b0a = { &b0  , &b0 , TRUE , INITERM(KEYWORD,REP_DELETE) , _SetActUpdateModeIndexForDelete } ;

syntax_node rep2 = { NULL   , NULL  , TRUE  , INITERM(KEYWORD,REP_SEMICOLON) , NULL } ;
syntax_node rep1 = { &rep0  , &rep2 , TRUE  , INITERM(KEYWORD,REP_COLON) , NULL } ;
syntax_node rep0 = { &rep1  , NULL  , FALSE , &b0a, NULL } ;

// Hilfsfunktionen
///////////////////////
DWORD PushDataToBlock (LPVOID Data,int Size,GLOBALHANDLE FAR *h,DWORD FAR *GSize)
  {
  DWORD nSize = *GSize + DWORD(Size);
  if (*h) *h = GlobalReAlloc (*h,nSize,GHND);
  else    *h = GlobalAlloc (GHND,nSize);
  hmemcpy ((char huge *) GlobalLock (*h) + *GSize,Data,Size);
  DWORD res = *GSize;
  *GSize = nSize;
  GlobalUnlock (*h);
  return res;
  }
DWORD PushNodeToBlock (LPREPNODE r,GLOBALHANDLE FAR *h,DWORD FAR *Size)
  {
  for (int i = 0 ; i < r->AnzSubNodes ; i++) {
    r->rpSub[i] = LPREPNODE (PushNodeToBlock (r->rpSub[i],h,Size));
    }
  LPSTR old = r->Selection;
  r->Selection = LPSTR (PushDataToBlock (r->Selection,lstrlen(r->Selection)+1,h,Size));
  DWORD res = PushDataToBlock (r,r->Size(),h,Size);
  FreeGlobMem (old);
  FreeGlobMem (r);
  return res;
  }

void WriteList ()
  {
  DWORD Size = AnzReps * sizeof(DWORD) + sizeof(short);
  GLOBALHANDLE hGres = GlobalAlloc (GHND,Size);
  short FAR *b = (short FAR *) GlobalLock (hGres);
  *b = AnzReps ;
  GlobalUnlock (hGres);
  for (int i = 0 ; i < AnzReps ; i++) {
    DWORD n = PushNodeToBlock (repList[i],&hGres,&Size);
    DWORD FAR *rList = (DWORD FAR *) (LPSTR (GlobalLock (hGres)) + sizeof(short));
    rList[i] = n ;
    GlobalUnlock (hGres);
    }
  FreeGlobMem (repList);
  repList = NULL ;
  AnzReps = 0 ;

  WriteDataDict (2,"REPLIKATOR",0,0,0,0,hGres,Size);
  GlobalFree (hGres);
  }

void FreeRepNode (LPREPNODE r)
  {
  for (int i = 0 ; i < r->AnzSubNodes ; i++)
    FreeRepNode (r->rpSub[i]);
  FreeGlobMem (r->Selection);
  FreeGlobMem (r);
  }

void FreeRepList ()
  {
  for (int i = 0 ; i < AnzReps ; i++)
    FreeRepNode (repList[i]);

  FreeGlobMem (repList);
  repList = NULL ;
  AnzReps = 0 ;
  }

BOOL GenRepScript (HWND hWnd,LPSTR fname)
  {
  RepCompiler FAR *r = new RepCompiler ();
  RCmp = r;
  hRepWnd = hWnd;
  *errText = '\0';
  AnzReps = 0 ;
  repList = NULL ;
  level = 0;
  rpAct = NULL;
  actPrio = 1;
  r->DoParse (fname,&rep0,NULL);
  WORD error = r->wError ;
  delete r;

  if (error == 0)
    WriteList ();
  else
    FreeRepList ();

  FreeTableName ();
  FreeSelection ();
    
  return (error == 0) ;
  }

