////////////////////////////////////////////////////////////////////////////
//  Generieren der internen Tabellen
////////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genitbl.cpv   1.19   05 Oct 1998 11:26:34   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/genitbl.cpv  $
// 
//    Rev 1.19   05 Oct 1998 11:26:34   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.18   19 Jan 1998 20:17:18   Hannes
// 
//    Rev 1.17   06 Nov 1997 19:32:30   Hannes
// Properties in Updatescripts / Views
// 
//    Rev 1.16   28 Aug 1997 14:29:40   Gerhold
// 32-Bit-Umstellung
// 
//    Rev 1.15   04 Jul 1997 19:34:44   Hannes
// 
//    Rev 1.14   19 Feb 1997 12:13:30   Hannes
// Parent in Tabellendefinition (Neueinbau von Scriptfunktionen)
// 
//    Rev 1.13   26 Nov 1996 08:10:26   HANNES
// Automatischer Update
// 
//    Rev 1.12   17 Jun 1996 16:53:44   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.11   04 Feb 1996 21:49:16   HANNES
// 
//    Rev 1.10   04 Feb 1996 17:00:40   HANNES
// Protyp LogMsg
// 
//    Rev 1.9   02 Feb 1996 10:50:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   15 Sep 1995 20:43:12   HANNES
// Zugriff fuer Joins ... Stringgroessenrestriktion raus
// 
//    Rev 1.7   02 May 1995 09:38:24   HANNES
// 
//    Rev 1.6   26 Apr 1995 15:26:34   HANNES
// 
//    Rev 1.5   24 Apr 1995 11:34:28   HANNES
//  
// 
//    Rev 1.4   07 Apr 1995 14:46:08   HANNES
// 
//    Rev 1.3   02 Apr 1995 13:33:22   HANNES
//  
// 
//    Rev 1.2   31 Mar 1995 18:23:40   HANNES
//  
// 
//    Rev 1.1   24 Feb 1995 11:00:40   HANNES
// 
//    Rev 1.0   16 Feb 1995 12:41:08   HANNES
// Initial revision.
// 
// 
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 20
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "itcmpl.hpp"

extern HINSTANCE MyInstance;
HWND hITWnd;
class ITCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  ITCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI ITCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,ITCMPL_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

#define ITCMPERROR    1000
DLLExport BOOL _export WINAPI ITCompiler::TestError ()
  {
  if (wError == ITCMPERROR) {
    if (GetCommandLineFlag())
      LogMsg ("Definitionsfehler");
    else {
      char outtxt[128];
      wsprintf (outtxt,"Definitionsfehler (%d,%d)",LineNr,column);
      MessageBox (hITWnd,outtxt,"Resourcefehler",MB_OK | MB_TASKMODAL);
      }
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static ITCompiler FAR *ICmp;
/////////////////////////////////////////////////////////////////////////
//  Code - Generierung
////////////////////////////////////////////////////////////////////////
/*----< Hilfsfunktionen fuer die Variablen - Verwaltung >-----*/
static LPPTABLE ActPart;
static LPTABLEDEF nTable;
static LPSTR _IName;
void PushToPartTable (LPSTR Name)
  {
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (ActPart->tRef.TableNr,ActPart->tRef.Version);
  for (int i = 0 ; i < td->GetAnzVars() ; i++) {
    if (lstrcmp(td->GetVarDef(i)->GetName(),Name) == 0) {
      LPPTABLE n = LPPTABLE (GetGlobMem (GetBlockSize(ActPart) + sizeof(WORD)));
      lmemcpy (n,ActPart,GetBlockSize(ActPart));
      FreeGlobMem (ActPart);
      n->VarID[n->AnzVars++] = WORD(i);
      ActPart = n;
      break ;
      }
    }
  GetTableAdmin()->FreeTable (ActPart->tRef.TableNr,ActPart->tRef.Version);
  }

void CreateNewPartTable (WORD TableID,WORD Version)
  {
  ActPart = LPPTABLE (GetGlobMem (sizeof(partTable) - sizeof(WORD)));
  ActPart->tRef.TableNr = TableID;
  ActPart->tRef.Version = Version;
  }
void PushToVarList (LPSTR VarName,LPSTR Alias)
  {
  int size = sizeof(VarDef) + lstrlen(Alias) + sizeof(InternVarCoding);
  LPVARDEF v = LPVARDEF (GetGlobMem(size));
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (ActPart->tRef.TableNr,ActPart->tRef.Version);
  LPVARDEF vr ;
  for (int i = 0 ; i < td->GetAnzVars () ; i++) {
    vr = td->GetVarDef(i);
    if (lstrcmp (vr->name,VarName) == 0) break ;
    }
  if (i < td->GetAnzVars()) {
    v->structSize = DWORD(size);
    v->VarSize = vr->VarSize ;
    v->DLLDataOffs = sizeof(*v) + lstrlen(Alias);
    v->mType = vr->mType ;
    v->VarID = vr->VarID ;
    lstrcpy (v->name,Alias);
    InternVarCoding FAR *i = (InternVarCoding FAR *) (LPSTR(v) + v->DLLDataOffs);
    i->mType = v->mType;
    i->IsPrimary = FALSE ;
    nTable = nTable->AddVar (v);
    FreeGlobMem (v);
    }
  else
    ICmp->wError = ITCMPERROR ;
    
  GetTableAdmin()->FreeTable (ActPart->tRef.TableNr,ActPart->tRef.Version);
  }
void PushPartTable ()
  {
  DWORD nSize = nTable->DLLDefSize + GetBlockSize (ActPart);
  if (nTable->d.hGDLLmem == 0)
    nSize += sizeof(InternTable);
  else
    nSize += sizeof(_reft);
  GLOBALHANDLE hGmem = GlobalAlloc (GHND,nSize);
  LPINTTABLE n = LPINTTABLE (GlobalLock (hGmem));
  DWORD offs;
  if (nTable->d.hGDLLmem) {
    LPINTTABLE old = LPINTTABLE (GlobalLock (nTable->d.hGDLLmem));
    offs = sizeof(*n) + sizeof(_reft) * old->AnzTables ;
    n->AnzTables = old->AnzTables;
    for (int i = 0 ; i < int(old->AnzTables) ; i++) {
      n->pTable[i].Offs = offs ;
      LPPTABLE x = LPPTABLE (LPSTR(old)+old->pTable[i].Offs);
      WORD size = sizeof(*x) + (x->AnzVars-1) * sizeof(x->VarID[0]);
      lmemcpy (LPSTR(n)+n->pTable[i].Offs,LPSTR(old)+old->pTable[i].Offs,size);
      offs += size ;
      }
    GlobalUnlock (nTable->d.hGDLLmem);
    GlobalFree (nTable->d.hGDLLmem);
    }
  else 
    offs = sizeof(*n);
  nTable->d.hGDLLmem = hGmem;
  lmemcpy (LPSTR(n)+offs,ActPart,GetBlockSize(ActPart));
  n->pTable[n->AnzTables].Offs = offs;
  n->AnzTables ++ ;
  GlobalUnlock (nTable->d.hGDLLmem);
  FreeGlobMem (ActPart);
  ActPart = NULL;
  nTable->DLLDefSize = nSize ;
  }
void ModifyDuplicateName (LPSTR AliasName)
  {
  char teststring[64];
  for (int i = -1 ;  ; i++) {
    lstrcpy (teststring,AliasName);
    if (i >= 0) {
      char postfix[2];
      postfix[0] = '1' + i ;
      postfix[1] = '\0';
      lstrcat (teststring,postfix);
      }
    for (int j = 0 ; j < nTable->GetAnzVars() ; j++) {
      if (lstrcmp (nTable->GetVarDef(j)->GetName(),teststring) == 0) break ;
      }
    if (j == nTable->GetAnzVars()) {
      lstrcpy (AliasName,teststring);
      break ;
      }
    }
  }
void PushAllToPartTable (LPSTR Prefix)
  {
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (ActPart->tRef.TableNr,ActPart->tRef.Version);
  for (int i = 0 ; i < td->GetAnzVars() ; i++) {
    PushToPartTable (td->GetVarDef(i)->GetName());
    char AliasName[64];
    if ((Prefix != NULL) && (*Prefix)) {
      lstrcpy (AliasName,Prefix);
      lstrcat (AliasName,"_");
      lstrcat (AliasName,td->GetVarDef(i)->GetName());
      }
    else
      lstrcpy (AliasName,td->GetVarDef(i)->GetName());
    ModifyDuplicateName(AliasName);
    PushToVarList (td->GetVarDef(i)->GetName(),AliasName);
    }
  GetTableAdmin()->FreeTable (ActPart->tRef.TableNr,ActPart->tRef.Version);
  }

/*----< Variablen - Verwaltung >-----*/
static char ICMP_RealName[64];
DLLExport void _export StoreRealName ()
  {
  LPSTR Name = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  lstrcpy (ICMP_RealName,Name);
  GlobalUnlock (ICmp->hPars0);
  }
DLLExport void _export CreateNewVar ()
  {
  LPSTR Alias = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  PushToPartTable (ICMP_RealName);
  PushToVarList (ICMP_RealName,Alias);
  GlobalUnlock (ICmp->hPars0);
  }
DLLExport void _export DelAlias ()
  {
  }
DLLExport void _export StoreAlias ()
  {
  LPSTR Name = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  PushAllToPartTable (Name);
  GlobalUnlock (ICmp->hPars0);
  }
DLLExport void _export StoreTable ()
  {
  PushAllToPartTable (NULL);
  }
static BOOL actUseVersion;
static LPSTR FAR *actTableNamesForUseVersion;
static WORD FAR *actVersionsForUseVersion;
WORD NextFreeTNI ()
  {
  for (WORD i = 0 ; ; ) {
    if (actTableNamesForUseVersion[i] == NULL) break ;
    i ++ ;
    WIN_ASSERT (i < 32) ;
    }
  return i ;
  }
DLLExport void _export CreatePartTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  BOOL found;
  WORD Version,rVersion;
  WORD TableID;
  if (actUseVersion) {
    char tname[64];
    lstrcpy (tname,Name);
    rVersion = GetVersionFrom (tname);
    if (rVersion != 0xFFFF) {
      TableID = GetTableAdmin()->GetTableID (NULL,tname,&found,&Version);
      Version = rVersion;
      WORD tni = NextFreeTNI ();
      actTableNamesForUseVersion [tni] = LPSTR (GetGlobMem (lstrlen(tname) + 1));
      lstrcpy (actTableNamesForUseVersion[tni],tname);
      actVersionsForUseVersion[tni] = Version;
      }
    else
      ICmp->wError = ITCMPERROR;
    }
  else
    TableID = GetTableAdmin()->GetTableID (NULL,Name,&found,&Version);
  if (!found)
    ICmp->wError = ITCMPERROR;
  else
    CreateNewPartTable (TableID,Version);
  GlobalUnlock (ICmp->hPars0);
  }
DLLExport void _export StorePartTable ()
  {
  PushPartTable ();
  }

/*------< Joins mit RI >-------*/
static struct URIDEF {
  LPCLRIDEF r;
  int TableInd;
  } usedRI[32];
static int AnzusedRI;
static BOOL IsRIUsed(LPCLRIDEF r,int TableInd)
  {
  for (int i = 0 ; i < AnzusedRI ; i++) {
    if ((usedRI[i].r == r) && (usedRI[i].TableInd == TableInd)) return TRUE ;
    }
  return FALSE ;
  }
static void SetRIUsed(LPCLRIDEF r,int TableInd)
  {
  usedRI[AnzusedRI].r = r;
  usedRI[AnzusedRI].TableInd = TableInd;
  AnzusedRI++ ;
  }
DLLExport void _export ClearUsedRI()
  {
  AnzusedRI = 0 ;
  }
extern int GetVarsforRI(LPCLRIDEF ri,WORD FAR *rivars);
static BOOL IsRIValid(LPPTABLE p,LPCLRIDEF r)
  {
  WORD rivars[32];
  int AnzVars = GetVarsforRI(r,rivars);
  for (int i = 0 ; i < AnzVars ; i++) {
    BOOL found = FALSE ;
    for (int j = 0 ; ((j < int(p->AnzVars)) && (!found)) ; j++) {
      if (p->VarID[j] == rivars[i]) found = TRUE ;
      }
    if (!found) return FALSE ;
    }
  return TRUE ;
  }
LPCLRIDEF GetRIFor (LPSTR TableName,int FAR *TableNum,TableRef FAR *tr)
  {
  LPINTTABLE old = LPINTTABLE (GlobalLock (nTable->d.hGDLLmem));
  LPCLRIDEF res = NULL ;
  for (int i = 0 ; ((i < int(old->AnzTables)) && (res == NULL)) ; i++ ) {
    LPPTABLE p = old->GetTableByNum(i);
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(p->tRef.TableNr,p->tRef.Version);
    for (int j = 0 ; ((j < td->GetAnzRIDefs()) && (res == NULL)) ; j++) {
      LPCLRIDEF r = td->GetRIDef (j);
      if ((lstrcmp (r->name,TableName) == 0) && (!IsRIUsed(r,i)) && (IsRIValid(p,r))) {
        *TableNum = i;
        lmemcpy (tr,&p->tRef,sizeof(*tr));
        GetTableAdmin()->GetTableDef(p->tRef.TableNr,p->tRef.Version);
        res = r;
        }
      }
    GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
    }
  GlobalUnlock (nTable->d.hGDLLmem);
  return res;
  }
int GetVarIDSFor (LPCLRIDEF ri,int TableNum,WORD FAR *varIDs)
  {
  WORD rivars[32];
  int AnzVars = GetVarsforRI(ri,rivars);
  for (int i = 0 ; i < AnzVars ; i++) {
    LPINTTABLE old = LPINTTABLE (GlobalLock (nTable->d.hGDLLmem));
    LPCLRIDEF res = NULL ;
    BOOL found = FALSE ;
    int l = 0 ;
    for (int j = 0 ; ((j < int(old->AnzTables)) && (!found)) ; j++ ) {
      LPPTABLE p = old->GetTableByNum(j);
      for (int k = 0 ; ((k < int(p->AnzVars)) && (!found)) ; k++ , l++) {
        if ((rivars[i] == p->VarID[k]) && (j == TableNum)) {
          varIDs[i] = l ;
          found = TRUE ;
          }
        }
      }
    }
  return AnzVars ;
  }
LPSTR GetRICommand (LPCLRIDEF r,int AnzVars,LPSTR buffer)
  {
  switch (r->Type) {
    case CLKR_EXTENDED :
      lstrcpy (buffer,r->GetERI()->AccessName);
      break ;
    case CLKR_STANDARD :
      {
      LPSTR h = buffer ;
      StandardRI FAR *s = r->GetSRI();
      for (int i = 0 ; i < AnzVars ; i++) {
        lstrcpy (h,s->ForeignField);
        char cmdstr[32];
        wsprintf (cmdstr," = %%%d",i+1);
        lstrcat (h,cmdstr);
        if (i < AnzVars - 1) lstrcat (h," AND ");
        h += lstrlen(h);
        s = s->GetNextSRI();
        }
      }
      break ;
    }
  return buffer;
  }

void PushJoin (WORD FAR *varIDs,int AnzVars,BYTE riType,BYTE riJoinType,LPSTR command)
  {
  int size = sizeof(ClientRIDef) + lstrlen(command) + sizeof(WORD) * AnzVars ;
  LPCLRIDEF n = LPCLRIDEF (GetGlobMem (size));
  n->structSize = size ;
  n->Type = riType ;
  n->TypeOfJoin = riJoinType ;
  n->AnzSegs = AnzVars ;
  lstrcpy (n->name,command);
  JoinDef FAR *j = n->GetJDef();
  for (int i = 0 ; i < AnzVars ; i++) 
    j->VarID[i] = varIDs[i];
  nTable->AddForeign (n);
  FreeGlobMem (n);
  }

static BYTE actJoinType;
void _export SetRIOuter ()
  {
  actJoinType = CLJT_USEOUTERJOIN ;
  }
void _export SetRIInner ()
  {
  actJoinType = CLJT_USEINNERJOIN ;
  }
void _export SetRIDefault ()
  {
  actJoinType = CLJT_USEDEFAULT ;
  }

DLLExport void _export SetRIJoin ()
  {
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (ActPart->tRef.TableNr,ActPart->tRef.Version);
  int TableNum;
  TableRef tr;
  LPCLRIDEF r = GetRIFor (td->GetName(),&TableNum,&tr);
  if (r != NULL) {
    SetRIUsed(r,TableNum);
    WORD varIDs[32];
    int AnzIntVars = GetVarIDSFor (r,TableNum,varIDs);
    char buffer[256];
    PushJoin (varIDs,AnzIntVars,(r->Type == CLKR_EXTENDED) ? CLJR_RIEXTENDED : CLJR_RISTANDARD,
                     actJoinType,
                     GetRICommand(r,AnzIntVars,buffer));
    }
  else
    ICmp->wError = ITCMPERROR ;
  GetTableAdmin()->FreeTable (ActPart->tRef.TableNr,ActPart->tRef.Version);
  GetTableAdmin()->FreeTable (tr.TableNr,tr.Version);
  }

static LPSTR JoinCommand;
static WORD JoinParam[32];
static int AnzJoinParams;
DLLExport void _export StoreJoinCommand ()
  {
  LPSTR Name = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  if (JoinCommand != NULL) FreeGlobMem(JoinCommand) ;
  JoinCommand = LPSTR (GetGlobMem (lstrlen(Name)+1));
  lstrcpy (JoinCommand,Name);
  GlobalUnlock (ICmp->hPars0);
  AnzJoinParams = 0;
  }
DLLExport void _export PushJoinParam ()
  {
  BOOL found = FALSE ;
  LPSTR Name = LPSTR(GlobalLock (ICmp->hPars0)) + sizeof(WORD);
  for (int i = 0 ; ((i < nTable->GetAnzVars()) && (!found)) ; i++) {
    if (lstrcmp(nTable->GetVarDef(i)->GetName(),Name) == 0) {
      found = TRUE ;
      JoinParam[AnzJoinParams++] = i ;
      }
    }
  GlobalUnlock (ICmp->hPars0);
  }
DLLExport void _export StoreNewJoin ()
  {
  PushJoin (JoinParam,AnzJoinParams,CLJR_NEW,actJoinType,JoinCommand);
  }
LPSTR actTablePrefix;
DLLExport void _export CreatnTable ()
  {
  char tname[64];
  *tname = '\0';
  if (actTablePrefix != NULL)
    lstrcpy (tname,actTablePrefix);
  lstrcat (tname,LPSTR(GlobalLock(ICmp->hPars0)) + sizeof(WORD));
  nTable = GetEmptyTable(tname,_IName);
  GlobalUnlock(ICmp->hPars0);
  }

extern void TestIntTable (LPSTR Caption,WORD Id);
extern void MarkTableForCheck (WORD TableID);
DLLExport void _export StoreTableDef ()
  {
  nTable->InitializeTableID (INTERNTBIDMIN,INTERNTBIDMAX,0);
  MarkTableForCheck (nTable->GetTableID());
  DWORD rSize;
  LPTABLEDEF nw = TableDef_NewPack (nTable,&rSize);
  WriteDataDict (0,nTable->GetName(),nTable->GetTableID(),nTable->GetVersion(),0,0,nw->GetHandle(),rSize);
  TestIntTable (nTable->GetName(),nTable->GetTableID());
  FreeTableDef (nw);
  nTable->Clear ();
  FreeTableDef (nTable);
  }

/////////////////////////////////////////////////////////////////////////
//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
extern syntax_node si5,ji4,itsyntax;

syntax_node si9       = { NULL , &si5 , TRUE , INITERM(KEYWORD,IC_CURBRACECLOSE) , NULL } ;
syntax_node si8       = { &si9 , NULL , TRUE , INITERM(KEYWORD,IC_SEMICOLON) , NULL } ;
syntax_node si7       = { &si8 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , CreateNewVar } ;
syntax_node si6       = { &si7 , NULL , TRUE , INITERM(KEYWORD,IC_EQUAL) , NULL } ;
syntax_node si5       = { &si6 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , StoreRealName } ;
syntax_node si4       = { &si5 , NULL , TRUE , INITERM(KEYWORD,IC_CURBRACEOPEN) , NULL } ;
syntax_node si3       = { NULL , NULL , TRUE , INITERM(FREECHAR,0) , StoreTable } ;
syntax_node si2       = { NULL , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , StoreAlias } ;
syntax_node si1       = { &si2 , &si3 , TRUE , INITERM(KEYWORD,IC_ALIAS) , NULL } ;
syntax_node si0       = { &si1 , NULL , TRUE , INITERM(KEYWORD,IC_ALL) , DelAlias } ;
syntax_node selinfo   = { &si0 , &si4 , TRUE , INITERM(KEYWORD,IC_SELECT) , NULL } ;

syntax_node ji6       = { NULL , NULL , TRUE , INITERM(KEYWORD,IC_BRACECLOSE) , StoreNewJoin } ;
syntax_node ji5       = { &ji4 , &ji6 , TRUE , INITERM(KEYWORD,IC_COLON) , NULL } ;
syntax_node ji4       = { &ji5 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , PushJoinParam } ;
syntax_node ji3       = { &ji4 , NULL , TRUE , INITERM(KEYWORD,IC_BRACEOPEN) , NULL } ;
syntax_node ji2       = { &ji3 , NULL , TRUE , INITERM(STRING,0) , StoreJoinCommand } ;
syntax_node ji1       = { NULL , &ji2 , TRUE , INITERM(KEYWORD,IC_RI) , SetRIJoin } ;
syntax_node ji0       = { &ji1 , NULL , TRUE , INITERM(KEYWORD,IC_WITH) , NULL } ;
syntax_node joinp2    = { &ji0 , &ji0 , TRUE , INITERM(KEYWORD,IC_OUTER) , SetRIOuter } ;
syntax_node joinp1    = { &ji0 , &joinp2 , TRUE , INITERM(KEYWORD,IC_INNER) , SetRIInner } ;
syntax_node joininfo  = { &joinp1 , NULL , TRUE , INITERM(KEYWORD,IC_JOIN) , SetRIDefault } ;

syntax_node tl3       = { NULL , NULL , TRUE  , INITERM(KEYWORD,IC_SEMICOLON) , StorePartTable } ;
syntax_node tl2       = { &tl3 , &tl3 , FALSE , &selinfo , NULL } ;
syntax_node tl1       = { &tl2 , &tl2 , FALSE , &joininfo , NULL } ;
syntax_node tl0       = { &tl1 , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , CreatePartTable } ;
syntax_node tablelist = { &tl0 , NULL , TRUE  , INITERM(KEYWORD,IC_TABLE) , NULL } ;

syntax_node i5       = { NULL , NULL      , TRUE  , INITERM(KEYWORD,IC_CURBRACECLOSE) , StoreTableDef } ;
syntax_node i4       = { &i4  , &i5       , FALSE , &tablelist , NULL } ;
syntax_node i3       = { &i4  , NULL      , TRUE  , INITERM(KEYWORD,IC_CURBRACEOPEN) , NULL } ;
syntax_node ii2      = { &i3  , NULL      , TRUE  , INITERM(KEYWORD,IC_EQUAL) , NULL } ;
syntax_node ii1      = { &ii2 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , CreatnTable } ;
syntax_node itable   = { &ii1 , NULL      , TRUE  , INITERM(KEYWORD,IC_INTERN) , ClearUsedRI } ;

syntax_node i6       = { NULL , &itsyntax , TRUE  , INITERM(KEYWORD,IC_END) , NULL } ;
syntax_node itsyntax = { &i6 , NULL      , FALSE , &itable , NULL } ;

syntax_node i6a       = { NULL , NULL      , TRUE  , INITERM(KEYWORD,IC_SEMICOLON) , NULL } ;
syntax_node itsyntax1 = { &i6a , NULL      , FALSE , &itable , NULL } ;

BOOL GenIntScript (HWND hWnd,LPSTR fname)
  {
  actUseVersion = FALSE ;
  actTablePrefix = NULL ;
  ITCompiler FAR *r = new ITCompiler ();
  ICmp = r;
  hITWnd = hWnd;
  _IName = fname;
  r->DoParse (fname,&itsyntax,NULL);
  WORD error = r->wError ;
  delete r;
  return (error == 0) ;
  }

class ITSCompiler : public ITCompiler {
  virtual DLLExport void _export FAR PASCAL InstallBuffer(LPVOID d);
  };
void ITSCompiler::InstallBuffer(LPVOID d)
  {
  buffer_start = LPSTR (d) ;
  actptr = buffer_start;
  }
DLLExport BOOL _export FAR PASCAL GenerateView (LPSTR fName,LPSTR Buffer,LPSTR prefix,BOOL useVersion,LPSTR FAR *TableNamesForUseVersion,WORD FAR *VersionsForUseVersion)
  {
  actTablePrefix = prefix ;
  actUseVersion = useVersion ;
  actTableNamesForUseVersion = TableNamesForUseVersion;
  actVersionsForUseVersion = VersionsForUseVersion;
  ITSCompiler FAR *r = new ITSCompiler ();
  ICmp = r;
  hITWnd = 0;
  _IName = fName;
  r->DoParse (Buffer,&itsyntax1,NULL);
  WORD error = r->wError ;
  delete r;
  return (error == 0) ;
  }

class SCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  SCompiler () : compiler (NULL) { }
  LPSTR GetBuffer_Start ()
    { return buffer_start; }
  LPSTR GetActPtr ()
    { return actptr; }
  };
DLLExport void _export WINAPI SCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,SCMPL_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

DLLExport BOOL _export WINAPI SCompiler::TestError ()
  {
  if ((wError) && (wError != FILENOTFOUND))
    compiler::TestError();
  return (wError != 0);
  }

SCompiler FAR *SCmp;
GLOBALHANDLE FAR *lpPre,FAR *lpPost;
LPSTR TableStart,TableEnd,ActName;
DLLExport void _export MarkTableStart ()
  {
  if (TableStart == NULL) TableStart = SCmp->GetActPtr() - 4;
  }

DLLExport void _export MarkStructTableStart ()
  {
  if (TableStart == NULL) TableStart = SCmp->GetActPtr() - 6;
  }

DLLExport void _export MarkTableEnd ()
  {
  if ((TableStart != NULL) && (TableEnd == NULL)) TableEnd = SCmp->GetActPtr();
  }

void DoTableStart ()
  {
  if (TableStart > SCmp->GetBuffer_Start()) {
    *lpPre = InitializeHandleForPush();
    PushDataToHandle (SCmp->GetBuffer_Start(),TableStart-SCmp->GetBuffer_Start(),lpPre);
    }
  }

DLLExport void _export CreateTableStart ()
  {
  LPSTR Name = LPSTR(GlobalLock (SCmp->hPars0)) + sizeof(WORD);
  if (lstrcmp (Name,ActName) == 0) {
    DoTableStart ();
    }
  else
    TableStart = NULL;
  GlobalUnlock (SCmp->hPars0);
  }

DLLExport void _export CreateTableEnd ()
  {
  BOOL doInsrtCR = FALSE ;
  if (TableEnd == NULL) {
    TableStart = SCmp->GetActPtr() - 3 ;
    DoTableStart();
    TableEnd = SCmp->GetActPtr() - 3;
    doInsrtCR = TRUE ;
    }
  else
    doInsrtCR = FALSE ;
  *lpPost = InitializeHandleForPush ();
  if (doInsrtCR)
    PushDataToHandle ("\r\n",2,lpPost);
  PushDataToHandle (TableEnd,SCmp->GetActPtr()-TableEnd,lpPost);
  }

extern syntax_node stablelist,s4,sti1,ssyntax;
syntax_node sti4       = { &sti1        , NULL  , TRUE , INITERM(KEYWORD,SC_SEMICOLON) , NULL } ;
syntax_node sti3       = { &sti1        , &sti4 , TRUE , INITERM(KEYWORD,SC_EQUAL) , NULL } ;
syntax_node sti2       = { &sti1        , &sti3 , TRUE , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node sti1       = { NULL         , &sti2 , TRUE , INITERM(KEYWORD,SC_CURBRACECLOSE) , NULL } ;
syntax_node sti0       = { &sti1        , NULL  , TRUE , INITERM(KEYWORD,SC_CURBRACEOPEN) , NULL } ;

syntax_node st2        = { NULL         , NULL , TRUE  , INITERM(KEYWORD,SC_SEMICOLON) , NULL } ;
syntax_node st1        = { &stablelist  , &st2 , FALSE , &sti0 , NULL } ;
syntax_node st0        = { &stablelist  , &st1 , TRUE  , INITERM(KEYWORD,SC_TABLE) , NULL } ;
syntax_node stablelist = { &stablelist  , &st0 , TRUE  , INITERM(UNKNOWNIDENT,0) , NULL } ;

syntax_node s6      = { NULL , &ssyntax  , TRUE  , INITERM(KEYWORD,SC_END) , CreateTableEnd } ;
syntax_node s5      = { &s6  , NULL      , TRUE  , INITERM(KEYWORD,SC_CURBRACECLOSE) , MarkTableEnd } ;
syntax_node s4      = { &s4  , &s5       , FALSE , &stablelist , NULL } ;
syntax_node ss3     = { &s4  , NULL      , TRUE  , INITERM(KEYWORD,SC_CURBRACEOPEN) , NULL } ;
syntax_node ss2     = { &ss3 , NULL      , TRUE  , INITERM(KEYWORD,SC_EQUAL) , NULL } ;
syntax_node ss1     = { &ss2 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , CreateTableStart } ;
syntax_node ssyntax = { &ss1 , NULL      , TRUE  , INITERM(KEYWORD,SC_INTERN) , MarkTableStart } ;

void GetPrePostParts (LPSTR Caption,LPSTR fName,GLOBALHANDLE FAR *PreText,GLOBALHANDLE FAR *PostText)
  {
  SCompiler FAR *r = new SCompiler ();
  SCmp = r;
  lpPre = PreText,lpPost = PostText;
  *lpPre = *lpPost = 0;
  TableStart = TableEnd = NULL;
  ActName = Caption;
  r->DoParse (fName,&ssyntax,NULL);
  if (r->wError) {
    if (*lpPre)  GlobalFree (*lpPre)  , *lpPre = 0;
    if (*lpPost) GlobalFree (*lpPost) , *lpPost = 0;
    }
  delete r;
  }

//
// Suchen einer globalen Tabelle in einem File
//
class GTCompiler : public SCompiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  };
DLLExport void _export WINAPI GTCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  static char *gtkw[] = { "struct" , "end" , "{" , "}" , ";" } ;
  for (int i = 0 ; i < 5 ; i++) {
    h->SetData (gtkw[i],&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

extern syntax_node gss1,gtsyntax;
syntax_node gss3        = { NULL   , NULL      , TRUE  , INITERM(KEYWORD,4) , MarkTableEnd } ;
syntax_node gss2        = { &gss3  , &gss1     , TRUE  , INITERM(KEYWORD,3) , NULL } ;
syntax_node gss1a       = { &gss2  , NULL      , TRUE  , INITERM(KEYWORD,4) , NULL } ;
syntax_node gss1        = { &gss2  , &gss1a    , TRUE  , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node gstablelist = { &gss2  , NULL      , TRUE  , INITERM(KEYWORD,2) , NULL } ;

syntax_node gts4     = { NULL  , &gtsyntax , TRUE  , INITERM(KEYWORD,1) , CreateTableEnd } ;
syntax_node gts3     = { &gts4 , NULL      , FALSE , &gstablelist , NULL } ;
syntax_node gts2     = { &gts3 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , CreateTableStart } ;
syntax_node gtsyntax = { &gts2 , NULL      , TRUE  , INITERM(KEYWORD,0) , MarkStructTableStart } ;

void GetPrePostGlobParts (LPSTR Caption,LPSTR fName,GLOBALHANDLE FAR *PreText,GLOBALHANDLE FAR *PostText)
  {
  GTCompiler FAR *r = new GTCompiler ();
  SCmp = r;
  lpPre = PreText,lpPost = PostText;
  *lpPre = *lpPost = 0;
  TableStart = TableEnd = NULL;
  ActName = Caption;
  r->DoParse (fName,&gtsyntax,NULL);
  if (r->wError) {
    if (*lpPre)  GlobalFree (*lpPre)  , *lpPre = 0;
    if (*lpPost) GlobalFree (*lpPost) , *lpPost = 0;
    }
  if (JoinCommand) FreeGlobMem (JoinCommand);
  JoinCommand = NULL; 
  delete r;
  }

