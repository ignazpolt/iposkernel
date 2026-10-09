//------------------------------------------------------------
// Klassenbibliothek zum Arbeiten mit Resourcen durch
// SQL - Kommandos
//  $Header:   P:/marille/clinicum/dbhelp/rev/ressql.cpv   1.12   04 Aug 1998 17:54:54   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/ressql.cpv  $
// 
//    Rev 1.12   04 Aug 1998 17:54:54   Hannes
// Timestamp
// 
//    Rev 1.11   05 May 1997 11:36:12   Hannes
// Speicherfresser verbessert
// 
//    Rev 1.10   30 Apr 1997 08:44:00   Hannes
// Unlock vor dem Free von res->g.hGmem (DefineResourceDLL)
// 
//    Rev 1.9   19 Feb 1997 12:06:24   Hannes
// Scriptfunktionen -> Tabellenaufbau von DataDict
// 
//    Rev 1.8   12 Dec 1996 12:19:50   HANNES
// UpdateStep zum Log mit schreiben
// 
//    Rev 1.7   03 Dec 1996 16:41:58   HANNES
// Namen in Hashtabellen
// 
//    Rev 1.6   27 Nov 1996 15:53:48   HANNES
// 
//    Rev 1.5   26 Nov 1996 07:53:48   HANNES
// Automatischer Update
// 
//    Rev 1.4   08 Nov 1996 13:27:38   HANNES
// Einbau des Replikators
// 
//    Rev 1.3   12 Sep 1996 23:29:12   HANNES
// doAdmin in DefineSQLDb
// 
//    Rev 1.2   03 Sep 1996 10:11:20   HANNES
// Richtige Modul - Nummer
// 
//    Rev 1.1   20 Jun 1996 23:14:06   MARTIN
// 
//    Rev 1.0   17 Jun 1996 15:46:58   HANNES
// Initial revision.
//------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 166
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "scripthd.hpp"

hash FAR *ResHash;
WORD CheckResName (LPSTR Name,BOOL FAR *found,WORD FAR *Version)
  {
  TableRef FAR *tref = (TableRef FAR *) ResHash->GetData(Name);
  if (tref != NULL) {
    *found = TRUE ;
    *Version = tref->Version;
    return tref->TableNr;
    }
  return 0;
  }
void DelResHash ()
  {
  if (ResHash != NULL) delete ResHash , ResHash = NULL ;
  }

DLLExport LPTABLEDEF _export WINAPI DefineSQLDB (LPSTR TableName,
                          RVarDef FAR *vDef,int AnzVars,
                          RKeyDef FAR *kDef,int AnzKeys,
                        DLLHANDLE ResDLL,BOOL doAdmin
                       )
  {
  if (ResHash == NULL)
    ResHash = new hash(11,STRKEY);

  // Initialisieren der Tabelle
  LPTABLEDEF res = GetEmptyTable(TableName,"");
  res->tRef.TableNr = GetTableAdmin()->GetTemporaryID(RESOURCEIDMIN);
  res->tRef.Version = 0;

  ResHash->SetData (TableName,&res->tRef,sizeof(res->tRef));

  // Definieren der einzelnen Variablen
  char CmplBuffer[256];
  VarDef FAR * _v = (VarDef FAR *) CmplBuffer;

  for (int i = 0 ; i < AnzVars ; i++) {
    _v->VarSize  = vDef[i].VarSize ;
    _v->VarID    = 0xFFFF;
    _v->mType    = vDef[i].mType;
    _v->Property = vDef[i].Property;
    lstrcpy (_v->name,vDef[i].Name);
    _v->structSize = sizeof(*_v) + lstrlen (_v->name);
    _v->DLLDataOffs = 0;
    res = res->AddVar (_v);
    }


  // Definieren der Schluessel
  for (i = 0 ; i < AnzKeys ; i++) {
    LPCLKEYDEF _k = LPCLKEYDEF (CmplBuffer);
    for (int j = 0 ; j < kDef[i].AnzSegs ; j++) {
      _k->Attribute = kDef[i].Attrib ;
      _k->KeyNmbr = i;
      WORD dt;
      BOOL found;
      _k->VarID = res->GetVarID (kDef[i].KeySeg[j],&dt,&found);
      WIN_ASSERT (found);
      lstrcpy (_k->name,kDef[i].Name);
      _k->structSize = sizeof(*_k) + lstrlen(kDef[i].Name);

      res->AddKey (_k);
      }
    }

  res->SetDLLHandle (ResDLL);
  DWORD gSize;
  LPTABLEDEF res1 = TableDef_NewPack (res,&gSize);
  GlobalUnlock (res1->g.hGmem);
  res1 = InitializeTable (res1->g.hGmem);

  if (doAdmin)
    GetTableAdmin ()->AddTableDef (res1,res1->GetDLLHandle());

  // Fertig mit der Definition
  res->Clear();
  GlobalUnlock (res->g.hGmem);
  GlobalFree (res->g.hGmem);
  return res1;
  }


// Definition der Scriptdatenbank
/////////////////////////////////////
RVarDef ScriptVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Type"   , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "fName" , 64 , VAR_STR , VPROP_NOTNULL } ,
  { "Data" , sizeof(DWORD) , VAR_BLOB , 0 }
  };
LPSTR ScriptSegs0 [] = {
  "Nummer"
  } ;
LPSTR ScriptSegs1 [] = {
  "Type" ,
  "fName"
  } ;
RKeyDef ScriptKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , ScriptSegs0 } ,
  { "_Name" , 2 , CLKD_UNIQUE , ScriptSegs1 } 
  } ;


// Definition der Resourcendatenbank
/////////////////////////////////////
RVarDef ResVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Type"   , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "fName" , 64 , VAR_STR , VPROP_NOTNULL } ,
  { "Data" , sizeof(DWORD) , VAR_BLOB , 0 }
  };
LPSTR ResSegs0 [] = {
  "Nummer"
  } ;
LPSTR ResSegs1 [] = {
  "Type" ,
  "fName"
  } ;
RKeyDef ResKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , ResSegs0 } ,
  { "_Name" , 2 , CLKD_UNIQUE , ResSegs1 } 
  } ;

// Definition des Datadictionary
/////////////////////////////////////
RVarDef DataDictVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Type"   , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Name" , 64 , VAR_STR , VPROP_NOTNULL } ,
  { "TableID" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Version" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "ParentID" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "ParentVersion" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Data" , sizeof(DWORD) , VAR_BLOB , 0 }
  };
LPSTR DataDictSegs0 [] = {
  "Nummer"
  } ;
LPSTR DataDictSegs1 [] = {
  "Type" ,
  "TableID" ,
  "Version"
  } ;
LPSTR DataDictSegs2 [] = {
  "Type" ,
  "Name" ,
  "Version"
  } ;
LPSTR DataDictSegs3 [] = {
  "Version"
  };
RKeyDef DataDictKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , DataDictSegs0 } ,
  { "_Id" , 3 , CLKD_UNIQUE , DataDictSegs1 } ,
  { "_Name" , 3 , CLKD_UNIQUE , DataDictSegs2 } ,
  { "_Version" , 1 , 0, DataDictSegs3 } 
  } ;

// Definition der DBVersion
/////////////////////////////////////
RVarDef DBVersionVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Name" , 64 , VAR_STR , VPROP_NOTNULL } ,
  { "Version" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL }
  };
LPSTR DBVersionSegs0 [] = {
  "Nummer"
  } ;
LPSTR DBVersionSegs1 [] = {
  "Name"
  } ;
RKeyDef DBVersionKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , DBVersionSegs0 } ,
  { "_Name" , 1 , CLKD_UNIQUE , DBVersionSegs1 } 
  } ;
// Definition der Update Step - Datenbank
///////////////////////////////////////////
RVarDef DBUpdateVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Datum" , 4 , VAR_DATE , VPROP_NOTNULL } ,
  { "Zeit" , 4 , VAR_TIME , VPROP_NOTNULL } ,
  { "Meldung" , 255 , VAR_STR , 0 }
  };
LPSTR DBUpdateSegs0 [] = {
  "Nummer"
  } ;
RKeyDef DBUpdateKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , DBUpdateSegs0 } 
  } ;

LPTABLEDEF DefineOneResourceDB(LPSTR Name,DLLHANDLE ResDLL,BOOL doAdmin)
  {
  if (!lstrcmp(Name,"ScriptDB"))
    return DefineSQLDB ("ScriptDB",
                         ScriptVars,sizeof(ScriptVars) / sizeof(*ScriptVars) ,
                         ScriptKeys,sizeof(ScriptKeys) / sizeof(*ScriptKeys) ,
                         ResDLL,doAdmin
                       ) ;
  if (!lstrcmp(Name,"ResDB"))
    return DefineSQLDB ("ResDB",
                         ResVars,sizeof(ResVars) / sizeof(*ResVars) ,
                         ResKeys,sizeof(ResKeys) / sizeof(*ResKeys) ,
                         ResDLL,doAdmin
                       ) ;
  if (!lstrcmp(Name,"DataDict"))
    return DefineSQLDB ("DataDict",
                         DataDictVars,sizeof(DataDictVars) / sizeof(*DataDictVars) ,
                         DataDictKeys,sizeof(DataDictKeys) / sizeof(*DataDictKeys) ,
                         ResDLL,doAdmin
                       ) ;
  if (!lstrcmp(Name,"DBVersion"))
    return DefineSQLDB ("DBVersion",
                         DBVersionVars,sizeof(DBVersionVars) / sizeof(*DBVersionVars) ,
                         DBVersionKeys,sizeof(DBVersionKeys) / sizeof(*DBVersionKeys) ,
                         ResDLL,doAdmin   // (DLL von aussen angegeben)
                       ) ;
  if (!lstrcmp(Name,"UpdateStep"))
    return DefineSQLDB ("UpdateStep",
                         DBUpdateVars,sizeof(DBUpdateVars) / sizeof(*DBUpdateVars) ,
                         DBUpdateKeys,sizeof(DBUpdateKeys) / sizeof(*DBUpdateKeys) ,
                         ResDLL,doAdmin   // (DLL von aussen angegeben)
                       ) ;
  return NULL;
  }

LPTABLEDEF ScriptDB,ResDB,DataDict,DBVersion,DBUpdate ;
void DefineResourceDBs()
  {
  DLLHANDLE ResDLL = GetDLLAdmin()->LoadResDLL();
  ScriptDB = DefineSQLDB ("ScriptDB",
                          ScriptVars,sizeof(ScriptVars) / sizeof(*ScriptVars) ,
                          ScriptKeys,sizeof(ScriptKeys) / sizeof(*ScriptKeys) ,
                          ResDLL
                         ) ;
  ResDB = DefineSQLDB ("ResDB",
                        ResVars,sizeof(ResVars) / sizeof(*ResVars) ,
                        ResKeys,sizeof(ResKeys) / sizeof(*ResKeys) ,
                        ResDLL
                      ) ;
  DataDict = DefineSQLDB ("DataDict",
                          DataDictVars,sizeof(DataDictVars) / sizeof(*DataDictVars) ,
                          DataDictKeys,sizeof(DataDictKeys) / sizeof(*DataDictKeys) ,
                          ResDLL
                         ) ;
  DLLHANDLE DefaultDLL = GetDLLAdmin()->LoadDefaultDLL();
  DBVersion = DefineSQLDB ("DBVersion",
                           DBVersionVars,sizeof(DBVersionVars) / sizeof(*DBVersionVars) ,
                           DBVersionKeys,sizeof(DBVersionKeys) / sizeof(*DBVersionKeys) ,
                           DefaultDLL
                          ) ;
  DBUpdate = DefineSQLDB ("UpdateStep",
                           DBUpdateVars,sizeof(DBUpdateVars) / sizeof(*DBUpdateVars) ,
                           DBUpdateKeys,sizeof(DBUpdateKeys) / sizeof(*DBUpdateKeys) ,
                           DefaultDLL
                          ) ;
  DefineRepDBs (ResDLL);
  }


void Assign (LPDBRECORD rec,WORD Id,LPVOID Data,int DataSize)
  {
  rec->Set(Id,Data,DataSize);
  }
void Assign (LPDBRECORD rec,WORD Id,LPSTR str)
  {
  Assign(rec,Id,str,lstrlen(str)+1);
  }
void Assign (LPDBRECORD rec,WORD Id,DWORD l)
  {
  Assign(rec,Id,&l,sizeof(l));
  }
void Assign (LPDBRECORD rec,WORD Id,short s)
  {
  Assign(rec,Id,&s,sizeof(s));
  }
void Assign (LPDBRECORD rec,WORD Id,WORD s)
  {
  Assign(rec,Id,&s,sizeof(s));
  }
DLLExport LPDBRECORD _export WINAPI Ask (LPTABLEDEF td,LPSTR Selection,LPVOID p1,int s1,WORD m1,
                                              LPVOID p2,int s2,WORD m2,
                                              LPVOID p3,int s3,WORD m3)
  {
  LPDBREQUEST req ;
  WORD TableID = td->GetTableID();
  WORD Version = td->GetVersion();
  if ((td->IsInternTable()) || (td->IsTemporaryTable())) {
    req = InitializeRequest (Selection,td->GetAnzVars(),DBCALLTYPE_STANDARDGET,0L);
    LPINTTABLE ti = LPINTTABLE(td->GetDLLDef());
    for (WORD i = 0 ; i < ti->AnzTables ; i++) {
      LPPTABLE pt = ti->GetTableByNum (i);
      req->AddTableDef (pt->tRef.TableNr,pt->tRef.Version);
      }
    for (int j = 0 ; j < req->AnzElems ; j++) {
      ReqElem d;
      td->GetReqElem (&d,j);
      req->SetReqElemDirect (j,d.TableNumber,d.VarID);
      }
    }
  else {
    req = InitializeRequest (Selection,-1,DBCALLTYPE_STANDARDGET,0L);
    req->AddTableDef (TableID,Version);
    }
  req->SetTableID(TableID,Version);
  req->SetParam (1,&TableID,sizeof(TableID));
  int ap = 1 ;
  if (p1 != NULL) {
    req->SetParam(2,p1,s1);
    req->SetParamType(2,m1);
    ap = 2 ;
    if (p2 != NULL) {
      req->SetParam(3,p2,s2);
      req->SetParamType(3,m2);
      ap = 3 ;
      if (p3 != NULL) {
        req->SetParam(4,p3,s3);
        req->SetParamType(4,m3);
        ap = 4 ;
        }
      }
    }
  req->AnzParam = ap;
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  LPVOID hstmt = NULL;
  int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,1,req,&hstmt,&rb);
  LPDBRECORD rec ;
  if (res == DBCALL_SUCCESS) {
    rec = rb.act->rec[0];
    rb.act->rec[0] = NULL;
    }
  else
    rec = NULL ;
  GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
  rb.Clear ();
  req->ClearParams();
  req->FreeTableDefs();
  FreeRequest (req);

  return rec ;
  }

DLLExport void _export WINAPI Excute (LPSTR Command,DLLHANDLE dllh,LPVOID p1,int s1,WORD m1,
                           LPVOID p2,int s2,WORD m2,
                           LPVOID p3,int s3,WORD m3)
  {
  LPDBREQUEST req = InitializeRequest (Command,1,DBCALLTYPE_EXECUTE,0L);
  int ap = 1 ;
  if (p1 != NULL) {
    req->SetParam(2,p1,s1);
    req->SetParamType(2,m1);
    ap = 2 ;
    if (p2 != NULL) {
      req->SetParam(3,p2,s2);
      req->SetParamType(3,m2);
      ap = 3 ;
      if (p3 != NULL) {
        req->SetParam(4,p3,s3);
        req->SetParamType(4,m3);
        ap = 4 ;
        }
      }
    }
  req->AnzParam = ap;
  LPDLLENTRY ent = GetDLLAdmin()->GetDLLEntry(dllh);
  LPVOID hstmt = NULL;
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  int res = ent->DBCall (DBOP_GETFIRST,-1,req,&hstmt,&rb);
  rb.Clear ();

  ent->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);

  if (req->tRef.TableNr != 0)
    GetTableAdmin()->FreeTemporaryTable (req->tRef.TableNr);

  req->ClearParams();
  req->FreeTableDefs();
  FreeRequest (req);
  }

DLLExport BOOL _export WINAPI Out (LPDBRECORD rec,int hGresID,WORD op,DWORD FAR *Id0,LPSTR Selection,LPVOID p1,int s1,WORD m1,
                                                             LPVOID p2,int s2,WORD m2,
                                                             LPVOID p3,int s3,WORD m3)
  {
  // rec muss von einer vollen Tabelle abgeleitet sein !!!
  /////////////////////////////////////////////////////////
  LPTABLEDEF td = GetTableAdmin()->GetTableDef(rec->GetTableID(),rec->GetVersion());
  LPDBREQUEST req = InitializeRequest (Selection,-1,op,0L);
  WORD TableID = td->GetTableID();
  WORD Version = td->GetVersion();
  req->SetTableID(TableID,Version);
  req->AddTableDef (TableID,Version);
  req->SetParam (1,&TableID,sizeof(TableID));
  int ap = 1 ;
  if (p1 != NULL) {
    req->SetParam(2,p1,s1);
    req->SetParamType(2,m1);
    ap = 2 ;
    if (p2 != NULL) {
      req->SetParam(3,p2,s2);
      req->SetParamType(3,m2);
      ap = 3 ;
      if (p3 != NULL) {
        req->SetParam(4,p3,s3);
        req->SetParamType(4,m3);
        ap = 4 ;
        }
      }
    }
  req->AnzParam = ap;
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  rb.AddLine (1,ADDLINEPOS_START);
  rb.act->rec[0] = rec ;
  LPVOID hstmt = NULL;
  int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,1,req,&hstmt,&rb);
  GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
  if ((op == DBCALLTYPE_STANDARDINSERT) && (hGresID >= 0) &&
      (rb.act != NULL) && (rb.act->rec[0] != NULL)) {
    rb.act->rec[0]->Del(hGresID);
    }
  if ((op == DBCALLTYPE_STANDARDINSERT) && (res == DBCALL_SUCCESS) && (Id0 != NULL) &&
      (rb.act != NULL) && (rb.act->rec[0] != NULL)) {
    LPVOID nData = rb.act->rec[0]->Get(0);
    if (GetBlockSize (nData) == 4)
      *Id0 = *((DWORD FAR *) nData);
    else
      *Id0 = *((short FAR *) nData);
    }

  rb.Clear ();
  req->ClearParams();
  req->FreeTableDefs();
  FreeRequest (req);

  return (res == DBCALL_SUCCESS) ;
  }

#define ASSIGN(A,B)  Assign (rec,A,B);
#define ASSIGN1(A,B,C)  Assign (rec,A,B,C);

/*-------------------------------------------------------------------*/
/*  SCRIPTDATENBANK                                                  */
/*-------------------------------------------------------------------*/
DLLExport GLOBALHANDLE _export WINAPI ReadScriptData (short type,LPSTR fName,DWORD FAR *DataSize)
  {
  LPDBRECORD h = Ask (ScriptDB,"Type = %1 AND fName = %2",&type,sizeof(type),VAR_STRARR,fName,lstrlen(fName)+1,VAR_STR);
  GLOBALHANDLE hGres = 0 ;
  *DataSize = 0 ;
  if (h != NULL) {
    LPBLOBDESC r = LPBLOBDESC (h->Get (3));
    if (r != NULL) {
      *DataSize = r->Size ;
      hGres = r->hGmem ;
      h->Del (3) ; // Im Destruktor nicht mehr freigeben
      }
    delete h ;
    }
  return hGres ;
  }

DLLExport void _export WINAPI WriteScriptData (short type,LPSTR fName,GLOBALHANDLE hGres,DWORD DataSize)
  {
  LPDBRECORD rec = new DBRecord (ScriptDB);
  ASSIGN (1,type);
  ASSIGN (2,fName);
  // Setzen der Daten
  struct BlobDesc d ;
  d.Size = DataSize ;
  d.hGmem = hGres;
  ASSIGN1 (3,&d,sizeof(d)); // Der Globalhandle wird im Destruktor von DBRecord freigegeben !

  // Abfragen, ob das Script schon existiert
  /////////////////////////////////////////////
  static LPSTR q1n [] = { "Nummer" } ;
  static LPSTR q1t [] = { "ScriptDB" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  WIN_ASSERT (q1 != NULL);

  LPDBRECORD h = Ask (q1,"Type = %1 AND fName = %2",&type,sizeof(type),VAR_STRARR,fName,lstrlen(fName)+1,VAR_STR);
  if (h != NULL) {
    // Update ist erforderlich
    LPVOID pNummer = h->Get(0);
    WIN_ASSERT (pNummer != NULL);
    DWORD Nummer = *(DWORD FAR *) pNummer;
    ASSIGN(0,Nummer);
    delete h ;
    WIN_ASSERT (Out (rec,3,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",&Nummer,4,VAR_LONG));
    }
  else {
    // Neues Script -> Insert
    WIN_ASSERT (Out (rec,3,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());

  // Fertig
  rec->Del(3);    // Handle bitte nicht freigeben
  delete rec ;
  }

DLLExport DBList FAR *_export WINAPI GetAllScriptData (short type)
  {
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  p.AnzPars = 1;
  p.ptr[0] = GetGlobMem (sizeof(type)) ;
  *(short FAR *) p.ptr[0] = type;
  p.pType[0] = VAR_STRARR;

  DBList FAR *res = new DBList (ScriptDB,0L,"Type = %1",30,30,&p,FALSE);
  res->SetOrder ("Type,fName");
  res->GetFirst (); // Durch den Getfirst werden die Parameterwerte uebernommen und koennen
                    // dann wieder freigegeben werden
  FreeGlobMem (p.ptr[0]);

  return res;
  }

/*-------------------------------------------------------------------*/
/*  RESOURCEDATENBANK                                                */
/*-------------------------------------------------------------------*/
DLLExport GLOBALHANDLE _export WINAPI ReadResourceData (DWORD Id,DWORD FAR *DataSize)
  {
  LPDBRECORD h = Ask (ResDB,"Nummer = %1",&Id,sizeof(DWORD),VAR_LONG);
  GLOBALHANDLE hGres = 0 ;
  *DataSize = 0 ;
  if (h != NULL) {
    LPBLOBDESC r = LPBLOBDESC (h->Get (3));
    if (r != NULL) {
      *DataSize = r->Size ;
      hGres = r->hGmem ;
      h->Del (3) ; // Im Destruktor nicht mehr freigeben
      }
    delete h ;
    }
  return hGres ;
  }

DLLExport GLOBALHANDLE _export WINAPI ReadResourceData (short type,LPSTR fName,DWORD FAR *DataSize)
  {
  LPDBRECORD h = Ask (ResDB,"Type = %1 AND fName = %2",&type,sizeof(type),VAR_STRARR,fName,lstrlen(fName)+1,VAR_STR);
  GLOBALHANDLE hGres = 0 ;
  *DataSize = 0 ;
  if (h != NULL) {
    LPBLOBDESC r = LPBLOBDESC (h->Get (3));
    if (r != NULL) {
      *DataSize = r->Size ;
      hGres = r->hGmem ;
      h->Del (3) ; // Im Destruktor nicht mehr freigeben
      }
    delete h ;
    }
  return hGres ;
  }

DLLExport void _export WINAPI WriteResourceData (short type,LPSTR fName,GLOBALHANDLE hGres,DWORD DataSize)
  {
  LPDBRECORD rec = new DBRecord (ResDB);
  ASSIGN (1,type);
  ASSIGN (2,fName);
  // Setzen der Daten
  struct BlobDesc d ;
  d.Size = DataSize ;
  d.hGmem = hGres;
  ASSIGN1 (3,&d,sizeof(d)); // Der Globalhandle wird im Destruktor von DBRecord freigegeben !

  // Abfragen, ob das Bild schon existiert
  /////////////////////////////////////////////
  static LPSTR q1n [] = { "Nummer" } ;
  static LPSTR q1t [] = { "ResDB" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;

  LPDBRECORD h = Ask (q1,"Type = %1 AND fName = %2",&type,sizeof(type),VAR_STRARR,fName,lstrlen(fName)+1,VAR_STR);
  if (h != NULL) {
    // Update ist erforderlich
    DWORD Nummer = *(DWORD FAR *) h->Get(0);
    ASSIGN(0,Nummer);
    delete h ;
    WIN_ASSERT (Out (rec,3,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",&Nummer,4,VAR_LONG));
    }
  else
    // Neues Bild -> Insert
    WIN_ASSERT (Out (rec,3,DBCALLTYPE_STANDARDINSERT,NULL,""));
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());

  // Fertig
  rec->Del(3);    // Handle bitte nicht freigeben
  delete rec ;
  }

DLLExport DBList FAR *_export WINAPI GetAllResourceData (short type)
  {
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  p.AnzPars = 1;
  p.ptr[0] = GetGlobMem (sizeof(type)) ;
  *(short FAR *) p.ptr[0] = type;
  p.pType[0] = VAR_STRARR;

  static LPSTR q1n [] = { "Nummer" , "fName" , "Type" } ;
  static LPSTR q1t [] = { "ResDB" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  DBList FAR *res = new DBList (q1,0L,"Type = %1",30,30,&p,FALSE);
  res->SetOrder ("Type,fName");
  res->GetFirst (); // Durch den Getfirst werden die Parameterwerte uebernommen und koennen
                    // dann wieder freigegeben werden
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());  // Beim delete von res wird die Tabelle endgueltig 
                                                                   // freigegeben
  FreeGlobMem (p.ptr[0]);

  return res;
  }

/*----------------------------------------------------------------------*/
/*  DATADICTIONARY                                                      */
/*----------------------------------------------------------------------*/
DLLExport DBList FAR *_export WINAPI GetAllDataDict (short type)
  {
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  p.AnzPars = 1;
  p.ptr[0] = GetGlobMem (sizeof(type)) ;
  *(short FAR *) p.ptr[0] = type;
  p.pType[0] = VAR_STRARR;

  static LPSTR q1n [] = { "Nummer" , "Name" , "TableID" , "Type" , "Version" , "ParentID" , "ParentVersion" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  DBList FAR *res = new DBList (q1,0L,"Type = %1",30,30,&p,FALSE);
  res->SetOrder ("Type,fName");
  res->GetFirst (); // Durch den Getfirst werden die Parameterwerte uebernommen und koennen
                    // dann wieder freigegeben werden
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());  // Beim delete von res wird die Tabelle endgueltig 
                                                                   // freigegeben
  FreeGlobMem (p.ptr[0]);

  return res;
  }

DLLExport DBList FAR *_export WINAPI GetAllTempDataDict ()
  {
  short Version = DBMAXVERSION ;
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  p.AnzPars = 1;
  p.ptr[0] = GetGlobMem (sizeof(Version)) ;
  *(short FAR *) p.ptr[0] = Version;
  p.pType[0] = VAR_STRARR;

  static LPSTR q1n [] = { "Nummer" , "Name" , "TableID" , "Type" , "Version" , "ParentID" , "ParentVersion" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  DBList FAR *res = new DBList (q1,0L,"Version = %1",-1,-1,&p,FALSE);
  res->SetOrder ("Version");
  res->GetFirst (); // Durch den Getfirst werden die Parameterwerte uebernommen und koennen
                    // dann wieder freigegeben werden
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());  // Beim delete von res wird die Tabelle endgueltig 
                                                                   // freigegeben
  FreeGlobMem (p.ptr[0]);

  return res;
  }

DLLExport void _export WINAPI WriteDataDict (short type,LPSTR Name,short TableID,short Version,short ParentID,short ParentVersion,GLOBALHANDLE hGres,DWORD DataSize)
  {
  LPDBRECORD rec = new DBRecord (DataDict);
  ASSIGN (1,type);
  ASSIGN (2,Name);
  ASSIGN (3,TableID);
  ASSIGN (4,Version);
  ASSIGN (5,ParentID);
  ASSIGN (6,ParentVersion);
  // Setzen der Daten
  struct BlobDesc d ;
  d.Size = DataSize ;
  d.hGmem = hGres;
  ASSIGN1 (7,&d,sizeof(d)); // Der Globalhandle wird im Destruktor von DBRecord freigegeben !

  // Abfragen, ob die Version schon existiert
  ///////////////////////////////////////////
  static LPSTR q1n [] = { "Nummer" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  WIN_ASSERT (q1 != NULL);

  LPDBRECORD h = Ask (q1,"Type = %1 AND TableID = %2 AND Version = %3",&type,sizeof(type),VAR_STRARR,&TableID,sizeof(TableID),VAR_STRARR,&Version,sizeof(Version),VAR_STRARR);
  if (h != NULL) {
    // Update ist erforderlich
    LPVOID pNummer = h->Get(0);
    WIN_ASSERT (pNummer != NULL);
    DWORD Nummer = *(DWORD FAR *) pNummer;
    ASSIGN(0,Nummer);
    delete h ;
    WIN_ASSERT (Out (rec,7,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",&Nummer,4,VAR_LONG));
    }
  else {
    // Neue Tabelle -> Insert
    WIN_ASSERT (Out (rec,7,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());

  // Fertig
  rec->Del(7);    // Handle bitte nicht freigeben
  delete rec ;

  }

DLLExport GLOBALHANDLE _export WINAPI ReadDataDict (short type,WORD TableID,WORD Version,DWORD FAR *DataSize)
  {
  LPDBRECORD h = Ask (DataDict,"Type = %1 AND TableID = %2 AND Version = %3",&type,sizeof(type),VAR_STRARR,&TableID,sizeof(TableID),VAR_STRARR,&Version,sizeof(Version),VAR_STRARR);
  GLOBALHANDLE hGres = 0 ;
  *DataSize = 0 ;
  if (h != NULL) {
    LPBLOBDESC r = LPBLOBDESC (h->Get (7));
    if (r != NULL) {
      *DataSize = r->Size ;
      hGres = r->hGmem ;
      h->Del (7) ; // Im Destruktor nicht mehr freigeben
      }
    delete h ;
    }
  return hGres ;
  }

DLLExport void _export WINAPI DelDataDict (short type,WORD TableID,WORD Version)
  {
  Excute ("DELETE FROM DataDict WHERE Type = %1 AND TableID = %2 AND Version = %3",GetDLLAdmin()->LoadResDLL(),&type,sizeof(type),VAR_STRARR,&TableID,sizeof(TableID),VAR_STRARR,&Version,sizeof(Version),VAR_STRARR);
  }

DLLExport WORD _export WINAPI ReadTableID (short type,LPSTR Name,WORD idmin,WORD idmax)
  {
  static LPSTR q1n [] = { "Nummer" , "TableID" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;

  WORD res = idmin ;
  LPDBRECORD h = Ask (q1,"Type = %1 AND Name = %2",&type,sizeof(type),VAR_STRARR,Name,lstrlen(Name)+1,VAR_STR);
  if (h != NULL) {
    res = *((WORD FAR *) h->Get(1)) ;
    delete h ;
    }
  else {
    h = Ask (q1,"Type = %1 AND TableID = (SELECT MAX(TableID) FROM DataDict WHERE Type = %1 AND TableID < %2)",&type,sizeof(type),VAR_STRARR,&idmax,sizeof(idmax),VAR_STRARR);
    if (h != NULL) {
      WORD resm1 = *((WORD FAR *) h->Get(1)) ;
      if (resm1 >= idmin)
        res = resm1 + 1 ;
      delete h ;
      }
    }
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
  return res ;
  }

DLLExport WORD _export WINAPI ReadMaxVersion (short type,WORD TableID)
  {
  static LPSTR q1n [] = { "Nummer" , "Version" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;

  WORD res = 0;
  WORD maxVersion = DBMAXVERSION ;
  LPDBRECORD h = Ask (q1,"Type = %1 AND TableID = %2 AND Version = (SELECT MAX(Version) FROM DataDict WHERE Type = %1 AND TableID = %2 AND Version < %3)",&type,sizeof(type),VAR_STRARR,&TableID,sizeof(TableID),VAR_STRARR,&maxVersion,sizeof(maxVersion),VAR_STRARR);
  if (h != NULL) {
    res = *((WORD FAR *) h->Get(1)) ;
    delete h ;
    }
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
  return res ;
  }

DLLExport void _export WINAPI SaveOldVersion (short type,WORD TableID,LPSTR Name,WORD oldVersion)
  {
  static LPSTR q1n [] = { "Nummer" , "Version" } ;
  static LPSTR q1t [] = { "DataDict" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;

  WORD res = 0;
  WORD maxVersion = DBMAXVERSION ;
  LPDBRECORD h = Ask (q1,"Type = %1 AND TableID = %2 AND Version = %3",&type,sizeof(type),VAR_STRARR,&TableID,sizeof(TableID),VAR_STRARR,&maxVersion,sizeof(maxVersion),VAR_STRARR);
  if (h == NULL) {    // Es existiert noch kein Backup -> eins anlegen
    DWORD Size;
    GLOBALHANDLE hGres = ReadDataDict (type,TableID,oldVersion,&Size);
    LPTABLEDEF td = LPTABLEDEF (GlobalLock (hGres));
    td->SetTableID(td->GetTableID(),DBMAXVERSION);
    GlobalUnlock (hGres);
    WriteDataDict (type,Name,TableID,DBMAXVERSION,0,0,hGres,Size);
    GlobalFree (hGres);
    }
  else
    delete h ;
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
  }

/*----------------------------------------------------------------------*/
/*  DBVERSION                                                           */
/*----------------------------------------------------------------------*/
DLLExport short _export WINAPI GetDBVersion(LPSTR TableName)
  {
  LPDBRECORD h = Ask (DBVersion,"Name = %1",TableName,lstrlen(TableName)+1,VAR_STR);
  short res = FIRSTVERSION ;
  if (h != NULL) {
    res = *(short FAR *) h->Get(2);
    delete h ;
    }
  return res ;
  }

DLLExport void _export WINAPI SetDBVersion(LPSTR TableName,short Version)
  {
  LPDBRECORD rec = new DBRecord (DBVersion);
  ASSIGN (1,TableName);
  ASSIGN (2,Version);
  LPDBRECORD h = Ask (DBVersion,"Name = %1",TableName,lstrlen(TableName)+1,VAR_STR);
  if (h != NULL) {
    if (*(short FAR *) h->Get(2) != Version) {
      // Update ist erforderlich
      DWORD Nummer = *(DWORD FAR *) h->Get(0);
      ASSIGN(0,Nummer);
      WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",&Nummer,4,VAR_LONG));
      }
    delete h ;
    }
  else {
    if (Version > 1)
      WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }

  delete rec ;
  }

DLLExport DBList FAR *_export WINAPI GetDBVersionList ()
  {
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  p.AnzPars = 0;

  DBList FAR *res = new DBList (DBVersion,0L,"",-1,-1,&p,FALSE);
  res->SetOrder ("Name");
  res->GetFirst (); // Durch den Getfirst werden die Parameterwerte uebernommen und koennen
                    // dann wieder freigegeben werden

  return res;
  }

#undef ASSIGN
