/////////////////////////////////////////////////////////////
//  Verbindung des Compilers mit dem Datadictionary
/////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/compile/rev/tbvar.cpv   1.21   18 Aug 2000 17:01:02   Wolfgang  $
//  $Log:   P:/marille/clinicum/compile/rev/tbvar.cpv  $
// 
//    Rev 1.21   18 Aug 2000 17:01:02   Wolfgang
// 1.) Programmstelle zum endgueltigen Ausschalten der unqualifizierten 
//     Variablen mit //#ifdef noUnQualifiedVars //#endif gekennzeichnet.
// 
//    Rev 1.20   01 May 2000 13:44:08   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.19   16 Feb 2000 15:03:16   Wolfgang
// 1.) Inkrementelles Compilieren von Prototypen ausser bei FDEF.
// 
//    Rev 1.18   04 Aug 1998 17:47:26   Hannes
// Timestamp
// 
//    Rev 1.17   05 Jan 1998 07:49:18   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.16   27 Oct 1997 19:51:42   Hannes
// Umbau von CheckIfFullVar
// 
//    Rev 1.15   22 Sep 1997 20:02:18   Hannes
// Variablen ohne Prefix als lokale Variablen erlaubt
// 
//    Rev 1.14   22 Sep 1997 12:37:08   Hannes
// Beschleunigung des Blob - Compilers
// 
//    Rev 1.13   11 Jun 1997 12:36:10   Martin
// 32bit-faehig gemacht
// 
//    Rev 1.12   09 Jun 1997 20:33:24   Hannes
// 
//    Rev 1.11   09 Jun 1997 13:09:58   Hannes
// 
//    Rev 1.10   27 May 1997 11:18:22   Hannes
// Private Strukturen im Scriptkompilat, Listenv. als Expression
// 
//    Rev 1.9   19 Feb 1997 12:04:32   Hannes
// Scriptfunktionen
// 
//    Rev 1.8   27 Nov 1996 17:18:50   HANNES
// 
//    Rev 1.7   26 Nov 1996 19:07:06   HANNES
// 
//    Rev 1.6   26 Nov 1996 07:57:12   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.5   21 Oct 1996 18:51:00   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.4   17 Jun 1996 15:28:24   HANNES
// Einfuehrung von BLOBS
// 
//    Rev 1.3   02 Feb 1996 10:41:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Feb 1995 11:10:46   HANNES
// 
//    Rev 1.1   05 Dec 1994 17:37:24   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.0   24 Jun 1994 16:30:28   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "dds32.h"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "resadmin.hpp"
#include "hash.hpp"
#include "btrieve.hpp"
#include "compile.hpp"
#include "scripthd.hpp"
#define MODULENUM 95
#include "winass.hpp"
#include "dbrecord.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "mdichild.hpp"

extern ScriptContent_Entry scent;

// Laden der Funktionsprototypen
//////////////////////////////////////////////
DLLExport void _export WINAPI compiler::OnStartCompile()
  {
  }

void ScriptCompiler::LoadResources ()
  {
  ReadResContent ();
  WORD Nr = 0;
  hash *x = _actcmpl->FixVrHash ();
  for (LPRESCENT h = GetFirstResourceInfo() ; h != NULL ; 
            h = GetNextResourceInfo(h,++Nr)) {
    full_vardef v;
    v.vd.DBNummer = LOWORD(h->ResID);
    v.vd.Ident    = HIWORD(h->ResID);
    v.isexpression  = FALSE ;
    v.isdynamic     = FALSE ;
    v.doubleDefined = FALSE ;
    BOOL doSet = TRUE;
    if (h->Type == RESTYPE_WMF)         v.vartype = VAR_PICTURE;
    else if (h->Type == RESTYPE_BITMAP) v.vartype = VAR_BITMAP;
    else doSet = FALSE;
    if (doSet) {
      WIN_ASSERT (x->SetData (h->GetName(),&v,sizeof(v)));
      }
    }
  _actcmpl->ReleaseVrHash ();
  UnloadResContent ();
  }

#ifdef UEBERLEGT
hash FAR *FcHash,FAR *cmpHash,FAR *efHash,FAR *opHash;
LPOPLIST asList,cndList;
#endif
GLOBALHANDLE hGMyFncs;
DLLExport void _export WINAPI BlobScriptCompiler::OnStartCompile()
  {
  ReadResContent ();
  DWORD DataSize;
  if (hGMyFncs == NULL) 
    hGMyFncs = ReadScriptData (2,"_FDEF",&DataSize);
  if (hGMyFncs)
    LoadFuncHashs(hGMyFncs,this);
  else
    wError = ERROR_NOFUNCDEF;
  LoadResources ();
  }

DLLExport void _export WINAPI ScriptCompiler::OnStartCompile()
  {
  DWORD DataSize;
  GLOBALHANDLE hGFncs = ReadScriptData (2,"_FDEF",&DataSize);
  if (hGFncs) {
    LoadFuncHashs(hGFncs,this);
    GlobalFree (hGFncs);
    }
  else
    wError = ERROR_NOFUNCDEF;
  LoadResources ();
  }

DLLExport void _export WINAPI FncCompiler::OnStartCompile()
  {
  char fileName[_MAX_FNAME];
  _splitpath (fmname, NULL, NULL, fileName, NULL);  
  if (lstrcmpi (fileName, "FDEF") != 0) {
    // Inkrementelles Compilieren
    DWORD DataSize;
    GLOBALHANDLE hGFncs = ReadScriptData (2,"_FDEF",&DataSize);
    if (hGFncs) {
      LoadFuncHashs(hGFncs,this);
      GlobalFree (hGFncs);
      }
    }
  }

// Alle Variablen einer Tabelle als Variablen - Hash installieren
////////////////////////////////////////////////////////////////////
static char TableName[64];
void UseVersion (LPSTR TableName,WORD Version)
  {
  for (UsedVersion FAR *h = _actcmpl->fUse ; h != NULL ; h = h->Next) {
    if (lstrcmp (TableName,h->TableName) == 0) {
      if (h->maxVersion == 0xFFFF) {
        if (h->minVersion > Version) h->maxVersion = h->minVersion , h->minVersion = Version ;
        else                         h->maxVersion = Version ;
        }
      else {
        if (h->minVersion > Version)      h->minVersion = Version ;
        else if (h->maxVersion < Version) h->maxVersion = Version ;
        }
      break ;
      }
    }

  if (h == NULL) {
    UsedVersion FAR *n = (UsedVersion FAR *) GetGlobMem (sizeof(*n));
    n->TableName = LPSTR (GetGlobMem (lstrlen(TableName) + 1));
    lstrcpy (n->TableName,TableName);
    n->minVersion = Version ;
    n->maxVersion = 0xFFFF ;
    n->Next = _actcmpl->fUse ;
    _actcmpl->fUse = n ;
    }
  }
void ResetVersionList ()
  {
  for ( ; _actcmpl->fUse != NULL ; ) {
    UsedVersion FAR *n = _actcmpl->fUse->Next ; 
    FreeGlobMem (_actcmpl->fUse->TableName);
    FreeGlobMem (_actcmpl->fUse);
    _actcmpl->fUse = n ;
    }
  }
BOOL areThereVersions()
  {
  return (_actcmpl->fUse != NULL);
  }
LPSTR PushVersionString (LPSTR old,LPSTR h,LPSTR prefix,char connect)
  {
  LPSTR n;
  if (old != NULL) {
    n = LPSTR (GetGlobMem (GetBlockSize (old) + lstrlen(h) + 1));
    lmemcpy (n,old,GetBlockSize(old));
    n[GetBlockSize(old)-1] = connect;
    lstrcpy (n + GetBlockSize(old),h);
    }
  else {
    if (prefix != NULL) {
      n = LPSTR (GetGlobMem (lstrlen(h) + lstrlen(prefix) + 1));
      lstrcpy (n,prefix);
      }
    else
      n = LPSTR (GetGlobMem (lstrlen(h) + 1));
    lstrcat (n,h);
    }
  return n;
  }
LPSTR GetUpdateProperty_From ()
  {
  LPSTR res = NULL;
  for (UsedVersion FAR *h = _actcmpl->fUse ; h != NULL ; h = h->Next) {
    char rname[64];
    wsprintf (rname,"%s.%d",h->TableName,h->minVersion);
    res = PushVersionString (res,rname,"FromVersion=",' ');
    }
  return res ;
  }
LPSTR GetUpdateProperty_To ()
  {
  LPSTR res = NULL;
  for (UsedVersion FAR *h = _actcmpl->fUse ; h != NULL ; h = h->Next) {
    if (h->maxVersion != 0xFFFF) {
      char rname[64];
      wsprintf (rname,"%s.%d",h->TableName,h->maxVersion);
      res = PushVersionString (res,rname,"ToVersion=",' ');
      }
    }
  return res ;
  }

Alias FAR *PushAlias (LPSTR AliasName,LPSTR TableName)
  {
  Alias FAR *n = (Alias FAR *) GetGlobMem (sizeof(*n));
  n->AliasName = LPSTR (GetGlobMem (lstrlen(AliasName) + 1));
  n->TableName = LPSTR (GetGlobMem (lstrlen(TableName) + 1));
  lstrcpy (n->AliasName,AliasName);
  lstrcpy (n->TableName,TableName);
  n->Next = _actcmpl->FirstAlias ;
  _actcmpl->FirstAlias = n ;
  n = _actcmpl->FirstAlias ;

  return n ;
  }
void ResetAlias ()
  {
  for ( ; _actcmpl->FirstAlias != NULL ; ) {
    Alias FAR *n = _actcmpl->FirstAlias->Next ;
    FreeGlobMem (_actcmpl->FirstAlias->AliasName);
    FreeGlobMem (_actcmpl->FirstAlias->TableName);
    FreeGlobMem (_actcmpl->FirstAlias);
    _actcmpl->FirstAlias = n ;
    }
  }
LPSTR TableForAlias (LPSTR AliasName,int FAR *TableNr)
  {
  for ( Alias FAR *n = _actcmpl->FirstAlias ; n != NULL ; n = n->Next ) {
    if (lstrcmp (n->AliasName,AliasName) == 0) {
      *TableNr = n->TableNr;
      return n->TableName ;
      }
    }
  return NULL ;
  }
int FindAliasTable (LPSTR AliasName)
  {
  char privateName[64];
  lstrcpy (privateName,_actcmpl->actFPrefix);
  lstrcat (privateName,AliasName);
  for ( Alias FAR *n = _actcmpl->FirstAlias ; n != NULL ; n = n->Next ) {
    if (lstrcmp (n->AliasName,AliasName) == 0) {
      return n->TableNr ;
      }
    }
  for (int i = 0 ; i < int (scent.AnzTables) ; i++) {
    if (scent.TRef[i].TableNr == 0) continue ;
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (scent.TRef[i].TableNr,scent.TRef[i].Version);
    BOOL found = (lstrcmp (AliasName,td->GetName()) == 0) ;
    if (!found) {
      found = (lstrcmp (privateName,td->GetName()) == 0) ;
      }
    GetTableAdmin()->FreeTable (scent.TRef[i].TableNr,scent.TRef[i].Version);
    if (found) return i ;
    }
  return -1 ;
  }
void SetTableName ()
  {
  LPSTR tn = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  lstrcpy (TableName,tn);
  GlobalUnlock (_actcmpl->hPars0);
  _actcmpl->ActAlias = NULL ;
  }
void SetTableName_extern (LPSTR StructName)
  {
  lstrcpy (TableName,StructName);
  }
void SetAliasTable ()
  {
  int TableNr;
  LPSTR AliasName = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  if (TableForAlias (AliasName,&TableNr) != NULL)
    _actcmpl->wError = TABLEALREADYUSED ; 
  else
    _actcmpl->ActAlias = PushAlias (AliasName,TableName);
  GlobalUnlock (_actcmpl->hPars0);
  }
void MarkPrivateID (LPSTR TableName,WORD pid)
  {
  PrivateStruct FAR *n = (PrivateStruct FAR *) GetGlobMem (sizeof(*n));
  n->Next = _actcmpl->ps;
  n->constOffs = pid;
  n->Name = LPSTR (GetGlobMem(lstrlen(TableName) + 1));
  lstrcpy (n->Name,TableName);
  _actcmpl->ps = n;
  }
BOOL IsPrivateID (LPSTR Name,WORD FAR *pid)
  {
  for (PrivateStruct FAR *h = _actcmpl->ps; h != NULL ; h = h->Next) {
    if (lstrcmp (h->Name,Name) == 0) {
      *pid = h->constOffs;
      return TRUE ;
      }
    }
  return FALSE ;
  }
extern WORD GetActVarType ();
void EnlargeStructData ()
  {
  if (_actcmpl->actStructData == NULL) {
    _actcmpl->actStructData = LPSTR (GetGlobMem(lstrlen(TableName) + 1 + sizeof(WORD) + sizeof(BYTE)));
    lstrcpy (_actcmpl->actStructData,TableName);
    }
  else {
    LPSTR n = LPSTR (GetGlobMem (GetBlockSize (_actcmpl->actStructData) + 1));
    lmemcpy (n,_actcmpl->actStructData,GetBlockSize (_actcmpl->actStructData));
    FreeGlobMem (_actcmpl->actStructData);
    _actcmpl->actStructData = n;
    }
  BYTE FAR *actm = (BYTE FAR *) (_actcmpl->actStructData + GetBlockSize(_actcmpl->actStructData) - 1);
  WORD FAR *anz = (WORD FAR *) (_actcmpl->actStructData + lstrlen(_actcmpl->actStructData) + 1);
  (*anz)++ ;
  *actm = BYTE (GetActVarType ());
  }
WORD IndToOffset (WORD ind)
  {
  LPSTR buffer = (LPSTR)GlobalLock (_actcmpl->constbuffer);
  WORD gSize = *(WORD FAR *)buffer;
  WORD j = 0 ;
  for (WORD act = 2 * sizeof(WORD) + 2 * sizeof(WORD); 
                act < gSize; 
                        act += 2 * sizeof(WORD) + ((WORD FAR *) (buffer + act))[-1] ) {
    if (j == ind) break ;
    j ++ ;
    }
  GlobalUnlock (_actcmpl->constbuffer);
  return act ;
  }
void PushStructDataToConst()
  {
  _actcmpl->actPrivateID = IndToOffset (_actcmpl->pushConst (_actcmpl->actStructData,GetBlockSize (_actcmpl->actStructData),VAR_BLOB));
  FreeGlobMem (_actcmpl->actStructData);
  _actcmpl->actStructData = NULL ;
  }
void UseTable ()
  {
  BOOL found;
  WORD Version ;
  int TableNr;
  if (_actcmpl->actPrivateID != 0) {
    TableNr = _actcmpl->SetTableUsed (0,_actcmpl->actPrivateID);
    MarkPrivateID (TableName,_actcmpl->actPrivateID);
    _actcmpl->actPrivateID = 0;
    }
  else if ((IsPrivateID (TableName,&Version)) && (_actcmpl->ActAlias != NULL)) {
    TableNr = _actcmpl->SetTableUsed (0,Version);
    _actcmpl->ActAlias->TableNr = TableNr ;
    _actcmpl->ActAlias = NULL;
    }
  else {
    WORD rVersion = GetVersionFrom (TableName);
    WORD TableID = GetTableAdmin()->GetTableID(NULL,TableName,&found,&Version);
    if ((!found) && (_actcmpl->ActAlias)) { // ev. muss der Private Name genommen werden
      char privateName[64];
      lstrcpy (privateName,_actcmpl->actFPrefix);
      lstrcat (privateName,TableName);
      TableID = GetTableAdmin()->GetTableID(NULL,privateName,&found,&Version);
      }
    if (rVersion != 0xFFFF) {
      Version = rVersion;
      if (Version == 0)
        _actcmpl->wError = ILLEGAL_VERSION ; 
      else
        UseVersion (TableName,Version);
      }
    if ((areThereVersions()) && (rVersion == 0xFFFF) && (Version != 0))
      _actcmpl->wError = ILLEGALMODE;
    if (!found) _actcmpl->wError = UNKNOWNTABLE;
    if (_actcmpl->wError) return ;
    if (_actcmpl->ActAlias == NULL) {
      if (_actcmpl->IsTableUsed (TableID,Version)) { 
        GetTableAdmin()->FreeTable(TableID,Version);
        _actcmpl->wError = TABLEALREADYUSED ; 
        return ; 
        }
      }
    else {
      if (!_actcmpl->IsTableUsed (TableID,Version)) {
        GetTableAdmin()->FreeTable(TableID,Version);
        _actcmpl->wError = TABLENOTDEFINED ;
        }
      }
    TableNr = -1 ;
    for ( int j = 0 ; ; ) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef(TableID,Version);
      hash *h = _actcmpl->FixVrHash ();
      if (TableNr == -1)
        TableNr = _actcmpl->SetTableUsed (TableID,Version);
      else
        _actcmpl->SetTableUsed (TableID,Version);   
              // Platz reservieren fuer weitere Tabelle
#ifdef noUnQualifiedVars
      for (int i = 0 ; i < td->GetAnzVars() ; i++) {
        LPVARDEF v = td->GetVarDef(i);
        if (v != NULL) {
          full_vardef fvd;
          fvd.TableNr = TableNr + j;
          fvd.vd.DBNummer = TableID;
          fvd.vd.Ident    = WORD(i);
          fvd.vartype     = BYTE(v->mType);
          fvd.isdynamic     = FALSE ;
          fvd.isexpression  = FALSE ;
          fvd.doubleDefined = FALSE ;    // mal sehen, obs so bleibt
          if (!h->SetData (v->GetName(),&fvd,sizeof (full_vardef))) {
            // Da is schon was drin
            full_vardef FAR *d = (full_vardef FAR *)h->GetData(v->GetName());
            #ifdef UEBERLEGT
            if ((d->vd.DBNummer == 0) || (d->vd.DBNummer == HELPDATA) ||
                  (d->vartype == VAR_PICTURE) || (d->vartype == VAR_BITMAP))
              _actcmpl->wError = VARALREADYDEFINED;   // so was darf nicht 
                                                      // ueberdefiniert werden
            else
              d->doubleDefined = TRUE ;  // Vermerken und dann spaeter einen
                                        // Fehler bei Verwendung ausgeben
            #else
            if (!((d->vd.DBNummer == 0) || (d->vd.DBNummer == HELPDATA) ||
                  (d->vartype == VAR_PICTURE) || (d->vartype == VAR_BITMAP)))
              d->doubleDefined = TRUE ;  // Vermerken und dann spaeter einen
                                        // Fehler bei Verwendung ausgeben
            #endif
            }
          }
        }
#endif
      _actcmpl->ReleaseVrHash ();
      WORD PId = td->GetParentID(),PV = td->GetParentVersion();
      GetTableAdmin()->FreeTable(TableID,Version);
      if (PId > 0) {
        TableID = PId;
        Version = PV;
        j ++ ;
        }
      else
        break ;
      }
    if (_actcmpl->ActAlias != NULL) {
      _actcmpl->ActAlias->TableNr = TableNr ;
      _actcmpl->ActAlias = NULL;
      }
    }
  }

int ScriptCompiler::SetTableUsed (WORD TableID,WORD Version)
  {
  // WIN_ASSERT (scent.AnzTables < MAXTBSINENT);
  int res = scent.AnzTables;
  TableRef FAR *nTRef = (TableRef FAR *) GetGlobMem (sizeof(TableRef) * (scent.AnzTables + 1));
  if (scent.TRef != NULL) {
    lmemcpy (nTRef,scent.TRef,GetBlockSize (scent.TRef));
    }
  scent.TRef = nTRef;
  scent.TRef[scent.AnzTables].TableNr = TableID;
  scent.TRef[scent.AnzTables].Version = Version;
  scent.AnzTables++;
  return res ;
  }

BOOL ScriptCompiler::IsTableUsed (WORD TableID,WORD Version)
  {
  for (WORD i = 0 ; i < scent.AnzTables ; i++)
    if ((scent.TRef[i].TableNr == TableID) &&
        (scent.TRef[i].Version == Version)) return TRUE ;
  return FALSE ;
  }

int FindID_Version (WORD TableID,WORD Version)
  {
  for (WORD i = 0 ; i < scent.AnzTables ; i++)
    if ((scent.TRef[i].TableNr == TableID) &&
        (scent.TRef[i].Version == Version)) return i ;
  return FALSE ;
  }

// Ueberpruefen, ob Name ein voll qualifizierter Variablennamen ist
/////////////////////////////////////////////////////////////////////
int myatoi (LPSTR h)
  {
  int res = 0;
  for ( ; *h ; h++) {
    if ((*h >= '0') && (*h <= '9'))
      res = res * 10 + *h - '0' ;
    else
      break ;
    }
  return res ;
  }

BOOL CheckIfFullName (LPSTR Name)
  {
  if (_actcmpl == NULL) return FALSE ;    
          // koennte ausserhalb des Scriptcompilers aufgerufen werden
  // 1. Untersuchung, ob Punkt im Variablennamen vorkommt
  LPSTR lastPoint = NULL ;
  for (LPSTR h = Name ; *h ; h++) if (*h == '.') lastPoint = h ;
  if (lastPoint != NULL)
    h = lastPoint;
  if (*h == '.') {
    // Mal sehen, obs die Tabelle gibt
    BOOL found;
    *h = '\0';
    WORD TableID,Version;
    _actcmpl->scv.v.vd.TableNr = -1 ;
    LPSTR TableName = NULL;
    if (IsPrivateID (Name,&Version)) {
      TableID = 0;
      found = TRUE ;
      }
    else {
      TableName = TableForAlias (Name,&_actcmpl->scv.v.vd.TableNr);
      if (TableName) {
        TableID = scent.TRef[_actcmpl->scv.v.vd.TableNr].TableNr;
        Version = scent.TRef[_actcmpl->scv.v.vd.TableNr].Version;
        found = TRUE ;
        }
      else {
        char MyName[256];
        lstrcpy (MyName,Name);
        WORD rVersion = GetVersionFrom (MyName);
        TableID = GetTableAdmin()->GetTableID(NULL,MyName,&found,&Version);
        if (found) {
          if (rVersion != 0xFFFF) {
            Version = rVersion;
            MyName[lstrlen(MyName)] = '.' ;
            }
          }
        else {
          char privateName[64];
          lstrcpy (privateName,_actcmpl->actFPrefix);
          lstrcat (privateName,Name);
          TableID = GetTableAdmin()->GetTableID(NULL,privateName,&found,&Version);
          }
        }
      }
    *h = '.';
    if ((found) && (_actcmpl->IsTableUsed(TableID,Version))) {
      int tnr;
      if (TableName == NULL)
        tnr = FindID_Version (TableID,Version);
      else
        tnr = _actcmpl->scv.v.vd.TableNr;
      // Na dann schaun wir uns noch den Variablennamen selber an
      if (TableID == 0) {
        // Es sind nur die Nummern erlaubt
        int id = myatoi (h + 2);
        LPSTR MyName = LPSTR (GlobalLock (_actcmpl->constbuffer)) + Version;
        WORD FAR *AnzVars = (WORD FAR *) (MyName + lstrlen (MyName) + 1);
        BYTE FAR *mType = (BYTE FAR *) (AnzVars + 1);
        if ((*(h + 1) == '@') && (WORD(id) < *AnzVars)) {
          _actcmpl->scv.type = VARID ;
          _actcmpl->scv.v.vd.TableNr     = tnr ;
          _actcmpl->scv.v.vd.vd.DBNummer = tnr + CSYSRECS;
          _actcmpl->scv.v.vd.vd.Ident    = WORD(id);
          _actcmpl->scv.v.vd.vartype     = mType[id];
          _actcmpl->scv.v.vd.isdynamic     = FALSE ;
          _actcmpl->scv.v.vd.isexpression  = FALSE ;
          _actcmpl->scv.v.vd.doubleDefined = FALSE ;
          }
        else
          _actcmpl->wError = INVALIDFULLVAR;
        GlobalUnlock (_actcmpl->constbuffer);
        return TRUE ;
        }
      else {
        for ( ; ; ) {
          LPTABLEDEF td = GetTableAdmin()->GetTableDef(TableID,Version);
          for (int i = 0 ; i < td->GetAnzVars() ; i++) {
            LPVARDEF v = td->GetVarDef(i);
            if ((v != NULL) && (lstrcmp(v->GetName(),h+1) == 0)) {
              // Alles ok
              _actcmpl->scv.type = VARID ;
              _actcmpl->scv.v.vd.TableNr     = tnr ;
              _actcmpl->scv.v.vd.vd.DBNummer = tnr + CSYSRECS;
              _actcmpl->scv.v.vd.vd.Ident    = WORD(i);
              _actcmpl->scv.v.vd.vartype     = BYTE(v->mType);
              _actcmpl->scv.v.vd.isdynamic     = FALSE ;
              _actcmpl->scv.v.vd.isexpression  = FALSE ;
              _actcmpl->scv.v.vd.doubleDefined = FALSE ;
              GetTableAdmin()->FreeTable(TableID,Version);
              return TRUE ;
              }
            }
          WORD PId = td->GetParentID() , PV = td->GetParentVersion () ;
          GetTableAdmin()->FreeTable(TableID,Version);
          if (PId > 0) {
            TableID = PId ;
            Version = PV ;
            tnr ++ ;
            }
          else
            break ;
          }
        }
      }
    else {
      // Da is was schiefgegangen
      _actcmpl->wError = INVALIDFULLVAR;
      }
    }
  return FALSE ;
  }

static char AliasName[64];
void SetAliasName ()
  {
  lstrcpy (AliasName,(LPSTR)GlobalLock (_actcmpl->hPars0)+sizeof(WORD));
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetAliasVar ()
  {
  hash *h = _actcmpl->FixVrHash ();
  if (!h->SetData (AliasName,&_actcmpl->scv.v.vd,sizeof(_actcmpl->scv.v.vd)))
    _actcmpl->wError = VARALREADYDEFINED;
  _actcmpl->ReleaseVrHash ();
  }

WORD GetAliasSize (short FAR *Anz)
  {
  WORD res = 0 ;
  *Anz = 0;
  for ( Alias FAR *n = _actcmpl->FirstAlias ; n != NULL ; n = n->Next ) {
    res += sizeof(_AliasDef) + lstrlen(n->AliasName);
    (*Anz) ++ ;
    }
  return res ;
  }

void GetAliasData (char huge *Buffer)
  {
  short dummy;
  WORD size = GetAliasSize (&dummy);
  if (size > 0) {
    LPALIASDEF h = LPALIASDEF (GetGlobMem (size)) ;
    LPALIASDEF first = h ;
    for ( Alias FAR *n = _actcmpl->FirstAlias ; n != NULL ; n = n->Next ) {
      h->TableNr = n->TableNr ;
      lstrcpy (h->AliasName,n->AliasName) ;
      h = h->Next ();
      }
    hmemcpy (Buffer,first,size);
    FreeGlobMem (first);
    }
  }

