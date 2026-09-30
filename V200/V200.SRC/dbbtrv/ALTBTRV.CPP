//-----------------------------------------------------------------------------
// ALTER TABLE fuer Btrieve
// $Header:   P:/marille/clinicum/dbbtrv/rev/altbtrv.cpv   1.14   10 Aug 1998 17:03:38   Hannes  $
// $Log:   P:/marille/clinicum/dbbtrv/rev/altbtrv.cpv  $
// 
//    Rev 1.14   10 Aug 1998 17:03:38   Hannes
// Umstellen des Timestamps auf UNSIGNED
// 
//    Rev 1.13   04 Aug 1998 17:55:32   Hannes
// Timestamp
// 
//    Rev 1.12   17 May 1998 17:53:18   Hannes
// Korrektes Schreiben der DDF - Files
// 
//    Rev 1.11   05 May 1998 10:00:46   Hannes
// Laestigen Fehler raus beim Schreiben der DDF - Files
// 
//    Rev 1.10   06 Mar 1998 17:07:02   Hannes
// 
//    Rev 1.9   08 Sep 1997 12:20:08   Hannes
// diverse Verbesserungen
// 
//    Rev 1.8   17 Jan 1997 07:50:24   HANNES
// Fehler in CreateDefinition
// 
//    Rev 1.7   15 Jan 1997 16:02:22   HANNES
// Fehlerkorrektur beim Schreiben von BLOBS
// 
//    Rev 1.6   06 Dec 1996 15:46:20   HANNES
// 
//    Rev 1.5   04 Dec 1996 14:23:48   HANNES
// 
//    Rev 1.4   04 Dec 1996 14:11:34   HANNES
// 
//    Rev 1.3   02 Dec 1996 12:35:12   HANNES
// Fehlerkorrekturen
// 
//    Rev 1.2   27 Nov 1996 17:10:32   HANNES
// 
//    Rev 1.1   27 Nov 1996 13:29:36   HANNES
// 
//    Rev 1.0   26 Nov 1996 07:59:38   HANNES
// Initial revision.
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 172
#include "winass.hpp"
#include "tbkw.h"
#include "tbfnc.hpp"
#include "dbrecord.hpp"
#include "btrieve.hpp"
#include "opbtrv.hpp"
#include "hash.hpp"

#include "compile.hpp"

#include "tbdiff.hpp"

void GetCNVName (LPTABLEDEF td,LPSTR path)
  {
  char p[256];
  GetFileName (td,p,NULL);
  LPSTR Name = p;
  LPSTR lastP = NULL;
  for (LPSTR x = path ; (*Name); ) {
    if (*Name == '.') {
      x[-1] = '~' ;
      lastP = x ;
      }
    *x++ = *Name++ ;
    }
  WIN_ASSERT (lastP);
  lstrcpy (lastP,".CNV");
  }

int MyRename (LPSTR oldName,LPSTR newName)
  {
  static char _tp1[256],_tp2[256];
  lstrcpy (_tp1,oldName);
  lstrcpy (_tp2,newName);
  return rename (_tp1,_tp2);
  }

static char _CNVPath[256];
static LPTABLEDEF _CNVtd;
void MarkNewPath (LPTABLEDEF tnew,LPSTR Path)
  {
  if (_CNVtd == NULL) {
    _CNVtd = tnew;
    lstrcpy (_CNVPath,Path);
    OFSTRUCT Of;
    OpenFile (_CNVPath,&Of,OF_DELETE);  // Sicherheitshalber loeschen
    }
  }

LPSTR GetCNVPath (LPTABLEDEF td)
  {
  if (td == _CNVtd) return _CNVPath;
  else              return NULL;
  }

void RestoreCNV ()
  {
  if (_CNVtd != NULL) {
    // Umbennen des neuen Files (.CNV) auf den org. Namen (.DAT),
    char nName[256];
    LPTABLEDEF tnew = _CNVtd;
    _CNVtd = NULL ;
    GetFileName (tnew,nName,NULL);
    CloseFile (_CNVPath);
    CloseFile (nName);
    OFSTRUCT Of;
    OpenFile (nName,&Of,OF_DELETE);
    WIN_ASSERT_TEXT (MyRename (_CNVPath,nName) == 0,"Löschen geht nicht -> Systemausstieg und reset notwendig -> Bitte nicht mit 'Continue' weitermachen");
    OpenFile (_CNVPath,&Of,OF_DELETE);

    DelDefinition(tnew->GetName());
    CreateDefinition(tnew);
    }
  }

void DeleteCNV ()
  {
  if (_CNVtd != NULL) {
    CloseFile (_CNVPath);
    OFSTRUCT Of;
    HFILE hFile = OpenFile (_CNVPath,&Of,OF_DELETE);
    _CNVtd = NULL ;
    }
  }

BOOL InAlter ()
  {
  return (_CNVtd != NULL) ;
  }

#define STEPWITH  100L
DLLExport BOOL _export WINAPI DBAlter (LPTABLEDEF told,LPTABLEDEF tnew,int AnzDefs,DefVal FAR *dv,__ALTERSUCCESS alts)
  {
  TableDifference td(told,tnew,WORD (~VPROP_CASEINSENSITIVE),WORD (~VPROP_CASEINSENSITIVE));

  BOOL error = FALSE;
  DBList FAR *res = NULL;

  if (!td.NoDifference()) {
    // 1. Fuer die neue Datenbank einen Namen geben
    char CNVPath[256];
    if (!error)
      GetCNVName (tnew,CNVPath);

    // 2. Diese Setzen vermerken, dass beim Endtransaction
    //    der Rename gemacht werden muss
    if (!error)
      MarkNewPath (tnew,CNVPath);

    // 4. Bilden einer Liste auf das alte file
    if (!error) {
      static ParamBlock p;
      lmemset (&p,'\0',sizeof(p));
      p.AnzPars = 0;

      res = new DBList (told,0L,"",100,100,&p,FALSE);
      res->SetOrder ("");
      if (res == NULL) error = TRUE ;
      }

    // 5. Alle Datensaetze in das neue File umkopieren
    if (!error) {
      InitializeDefVal (dv,AnzDefs,tnew);
      DWORD row = 0L ;
      BOOL insIsDone ();

      // Die CNV Auf jeden Fall Anlegen
      LPDBREQUEST req = InitializeRequest ("",1,DBCALLTYPE_TEST,NULL);
      req->AddTableDef (tnew);
      LPVOID hstmt = NULL;
      int rtest = DBCall_Work (DBOP_GET,-1,req,&hstmt,NULL);
      DBCall_Work (DBOP_RESET,-1,req,&hstmt,NULL);
      FreeRequest (req);
      for (LPDBRECORD h = res->GetFirst(); ((h != NULL) && (!error)) ; h = res->GetNext(h)) {
        DBRecord FAR *n = ConvertRecord (tnew,h,&td,AnzDefs,dv);

        LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
        WORD TableID = tnew->GetTableID();
        WORD Version = tnew->GetVersion();
        req->SetTableID(TableID,Version);
        req->AddTableDef (TableID,Version);
        req->SetParam (1,&TableID,sizeof(TableID));
        req->AnzParam = 0;

        RecBuffer rb;
        lmemset (&rb,'\0',sizeof(rb));
        rb.AddLine (1,ADDLINEPOS_START);
        rb.act->rec[0] = n ;

        LPVOID hstmt = NULL;
        int stat = DBCall_Work (DBOP_GET,1,req,&hstmt,&rb);
        DBCall_Work (DBOP_RESET,0,NULL,&hstmt,NULL);

        if (!error)
          rb.Clear ();
        req->ClearParams();
        req->FreeTableDefs();
        FreeRequest (req);

        error = (stat != DBCALL_SUCCESS);

        if (!error)
          delete n ;

        res->ThrowAtHead(h);

        row ++ ;
        if ((row % STEPWITH) == 0L)
          (* alts) (row) ;
        }
      }
    if (res != NULL)
      delete res ;
    }
  else {
    WIN_ASSERT (AnzDefs == 0);
    }
  if (error)
    DeleteCNV ();

  // 6. Nun kann mit dem Begintransaction begonnen werden
  BeginTransaction (FALSE);

  if (!error)
    return DBCALL_SUCCESS;
  else
    return DBCALL_ERROR;
  }

//--------------------------------------------------------------------------------------
// Schreiben / Erzeugen der Datadicts fuer ScalableSQL
//--------------------------------------------------------------------------------------
RVarDef FileVars [] = {
  { "Id"       , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Name"     , 20 , VAR_STR    , VPROP_NOTNULL } ,
  { "Loc"      , 64 , VAR_STR    , VPROP_NOTNULL } ,
  { "Flags"    , 1  , VAR_STRARR , VPROP_NOTNULL } ,
  { "Reserved" , 10 , VAR_STR    , 0 } 
  };
LPSTR FileSegs0 [] = {
  "Id"
  } ;
LPSTR FileSegs1 [] = {
  "Name" 
  } ;
RKeyDef FileKeys [] = {
  { "_Id" , 1 , CLKD_UNIQUE , FileSegs0 } ,
  { "_Name" , 1 , CLKD_UNIQUE | CLKD_MODIFYABLE, FileSegs1 } 
  } ;

RVarDef FieldVars [] = {
  { "Id"       , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "File"     , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Name"     , 20 , VAR_STR    , VPROP_NOTNULL } ,
  { "DataType" , 1  , VAR_STRARR , VPROP_NOTNULL } ,
  { "Offset"   , 2  , VAR_STRARR , VPROP_NOTNULL } ,
  { "Size"     , 2  , VAR_STRARR , VPROP_NOTNULL } ,
  { "Dec"      , 1  , VAR_STRARR , VPROP_NOTNULL } ,
  { "Flags"    , 2  , VAR_STRARR , VPROP_NOTNULL } ,
  };
LPSTR FieldSegs0 [] = {
  "Id"
  } ;
LPSTR FieldSegs1 [] = {
  "File" 
  } ;
LPSTR FieldSegs2 [] = {
  "Name" 
  } ;
LPSTR FieldSegs3 [] = {
  "File" ,
  "Name" 
  } ;
LPSTR FieldSegs4 [] = {
  "File" ,
  "Offset" ,
  "Dec"
  } ;
RKeyDef FieldKeys [] = {
  { "_Id" , 1 , CLKD_UNIQUE , FieldSegs0 } ,
  { "_File" , 1 , 0 , FieldSegs1 } ,
  { "_Name" , 1 , CLKD_MODIFYABLE , FieldSegs2 } ,
  { "_FN"   , 2 , CLKD_UNIQUE | CLKD_MODIFYABLE , FieldSegs3 } ,
  { "_FO"   , 3 , CLKD_MODIFYABLE , FieldSegs4 } 
  } ;

RVarDef IndexVars [] = {
  { "File"     , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Field"    , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Number"   , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Part"     , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Flags"    , sizeof(short) , VAR_STRARR , VPROP_NOTNULL }
  };
LPSTR IndexSegs0 [] = {
  "File"
  } ;
LPSTR IndexSegs1 [] = {
  "Field" 
  } ;
LPSTR IndexSegs2 [] = {
  "File" ,
  "Number" ,
  "Part" 
  } ;
RKeyDef IndexKeys [] = {
  { "_File" , 1 , 0 , IndexSegs0 } ,
  { "_Field" , 1 , 0 , IndexSegs1 } ,
  { "_Key"   , 3 , CLKD_UNIQUE | CLKD_MODIFYABLE, IndexSegs2 } 
  } ;

static LPTABLEDEF XFile,XField,XIndex;
void DefineDDFs ()
  {
  static BOOL areDefined ;
  if (!areDefined) {
    DLLHANDLE DefaultDLL = GetDLLAdmin()->LoadDefaultDLL();
    XFile = DefineSQLDB ("XFile",
                            FileVars,sizeof(FileVars) / sizeof(*FileVars) ,
                            FileKeys,sizeof(FileKeys) / sizeof(*FileKeys) ,
                            DefaultDLL,TRUE
                            ) ;
    XField = DefineSQLDB ("XField",
                            FieldVars,sizeof(FieldVars) / sizeof(*FieldVars) ,
                            FieldKeys,sizeof(FieldKeys) / sizeof(*FieldKeys) ,
                            DefaultDLL,TRUE
                            ) ;
    XIndex = DefineSQLDB ("XIndex",
                            IndexVars,sizeof(IndexVars) / sizeof(*IndexVars) ,
                            IndexKeys,sizeof(IndexKeys) / sizeof(*IndexKeys) ,
                            DefaultDLL,TRUE
                            ) ;
    
    areDefined = TRUE ;
    }
  }

LPSTR ConvertName (LPSTR Name,LPSTR Prefix = NULL)
  {
  static char Buffer[21];
  LPSTR x;
  if (Prefix) lstrcpy (Buffer,Prefix) , x = Buffer + lstrlen(Buffer) ;
  else        x = Buffer;
  int i = 0 ;
  for (LPSTR h = Name ; *h ; h++) {
    if (i == 20)   { break ; }
    if (*h == '_') *x++ = 'x' ;
    else           *x++ = *h ;
    i ++ ;
    }
  *x++ = '\0' ;
  return Buffer;
  }
extern BOOL spacePadd;
void DelDefinition (LPSTR TableName)
  {
  spacePadd = TRUE ;
  DefineDDFs ();
  LPSTR Name = ConvertName (TableName);
  LPDBRECORD h = Ask (XFile,"Name = %1",Name,lstrlen(Name) + 1,VAR_STR);
  if (h != NULL) {
    short Id = *(short FAR *) h->Get(0);
    Excute ("DELETE FROM XField WHERE File = %1",GetDLLAdmin()->LoadDefaultDLL(),&Id,sizeof(short),VAR_STRARR);
    Excute ("DELETE FROM XIndex WHERE File = %1",GetDLLAdmin()->LoadDefaultDLL(),&Id,sizeof(short),VAR_STRARR);
    Excute ("DELETE FROM XFile WHERE Id = %1",GetDLLAdmin()->LoadDefaultDLL(),&Id,sizeof(short),VAR_STRARR);

    delete h ;
    }
  spacePadd = FALSE ;
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
#define ASSIGN(A,B)  Assign (rec,A,B);
#define ASSIGN1(A,B,C)  Assign (rec,A,B,C);
LPSTR SkipPath (LPSTR FileName)
  {
  LPSTR s = FileName ;
  for (LPSTR h = FileName ; *h ; h++) if ((*h == '\\') || (*h == ':')) s = h + 1 ;
  return s ;
  }

void FeldSchreiben (short ifile,int fnum,LPVARDEF v,LPSTR Prefix,WORD extraDT,LPTABLEDEF td,int VarLen,int VarOffs)
  {
  LPDBRECORD rec = new DBRecord (XField);
  ASSIGN(0,short(fnum));
  ASSIGN(1,ifile);
  LPSTR Name = ConvertName (v->GetName(),Prefix) ;
  LPDDSVARDESC vb = LPDDSVARDESC (v->GetDLLData());
  LPBTRVTABLE t = LPBTRVTABLE(td->GetDLLDef());
  LPVBTRV b = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vb->b.dOffs);

  if (VarLen == 0) VarLen = b->VarLen;

  ASSIGN(2,Name);
  if (v->mType == VAR_BLOB) {
    ASSIGN(3,short(13));
    ASSIGN(4,short(b->VarOffset));
    ASSIGN(5,short(32767 - b->VarOffset));
    }
  else {
    if (extraDT == 0xFFFF) { ASSIGN(3,short (b->DataType)); }
    else                   { ASSIGN(3,short (extraDT)); }
    ASSIGN(4,short (b->VarOffset + VarOffs));
    ASSIGN(5,short (VarLen));
    }
  ASSIGN(6,short (0));
  ASSIGN(7,short (0));
  if (EntwicklungsUmgebung()) {
    WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }
  else
    Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
  delete rec ;
  }

WORD VarNum (LPTABLEDEF td,WORD IId)
  {
  WORD j = 0;
  for ( WORD i = 0 ; i < IId ; i++) {
    if (td->GetVarDef(i)->mType == VAR_DATETIME) j += 2;
    else                                         j ++;
    }
  return j;
  }
void CreateDefinition (LPTABLEDEF td)
  {
  spacePadd = TRUE ;
  DefineDDFs ();
  static LPSTR q1n [] = { "Id" } ;
  static LPSTR q1t [] = { "XFile" } ;
  static LPSTR q2n [] = { "Id" } ;
  static LPSTR q2t [] = { "XField" } ;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (sizeof(q1n) / sizeof(*q1n),q1n,1,q1t) ;
  LPTABLEDEF q2 = GetTableAdmin()->GetTemporaryTable (sizeof(q2n) / sizeof(*q2n),q2n,1,q2t) ;
  LPDBRECORD file = Ask (q1,"Id = (SELECT MAX(Id) FROM XFile)");
  LPDBRECORD field = Ask (q2,"Id = (SELECT MAX(Id) FROM XField)");
  short ifile,ifield;
  if (file != NULL) {
    ifile = *(short FAR *) file->Get(0) + 1;
    delete file;
    }
  else
    ifile = 1 ;
  if (field != NULL) {
    ifield = *(short FAR *) field->Get(0) + 1;
    delete field;
    }
  else
    ifield = 1 ;
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
  GetTableAdmin()->FreeTable (q2->GetTableID(),q2->GetVersion());

  LPDBRECORD rec = new DBRecord (XFile);
  ASSIGN (0,ifile);
  LPSTR Name = ConvertName (td->GetName()) ;
  ASSIGN (1,Name);
  char path[128];
  GetFileName (td,path,NULL);
  ASSIGN (2,SkipPath(path));
  ASSIGN (3,short(0));
  if (EntwicklungsUmgebung()) {
    WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }
  else
    Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
  delete rec;

  BOOL blockDone = FALSE ;
  int j = 0 ;
  for ( int i = 0 ; i < td->GetAnzVars() ; i++) {
    LPVARDEF v = td->GetVarDef(i);
    if (v->VarID == 0xFFFF) {
      if (v->mType == VAR_DATETIME) {
        FeldSchreiben (ifile,ifield + j,v,"t",BDT_TIME,td,4,4);
        FeldSchreiben (ifile,ifield + j + 1,v,"d",BDT_DATE,td,4,0);
        j += 2 ;
        }
      else {
        FeldSchreiben (ifile,ifield + j,v,NULL,0xFFFF,td,0,0);
        j += 1 ;
        }
      }
    else
      blockDone = TRUE ;
    }
  if (blockDone) {
    rec = new DBRecord (XField);
    ASSIGN(0,short(ifield + j));
    ASSIGN(1,ifile);
    ASSIGN(2,"mblocked");
    ASSIGN(3,short(12));
    ASSIGN(4,short(LPBTRVTABLE(td->GetDLLDef())->bdsc.lOffset));
    ASSIGN(5,short(32767 - LPBTRVTABLE(td->GetDLLDef())->bdsc.lOffset));
    ASSIGN(6,short (0));
    ASSIGN(7,short (0));
    if (EntwicklungsUmgebung()) {
      WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
      }
    else
      Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
    delete rec ;
    }

  WORD kn = 0xFFFF ;
  short pnum;
  for (i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    rec = new DBRecord (XIndex);
    ASSIGN(0,short(ifile));
    LPCLKEYDEF ck = td->GetKeyDef (i);
    LPVARDEF v = td->GetVarDef (ck->VarID);
    if (v->mType == VAR_DATETIME) {
      continue ;    // Schluessel auslassen
      #ifdef UEBERLEGT
      ASSIGN(1,short(ifield + VarNum (td,ck->VarID)));
      ASSIGN(2,short(ck->KeyNmbr));
      if (ck->KeyNmbr != kn)
        pnum = 0 ;
      kn = ck->KeyNmbr ;
      ASSIGN(3,short(pnum));
      ASSIGN(4,short (LPBTRVTABLE(td->GetDLLDef())->GetDescRef()->k[i].flag));

      if (EntwicklungsUmgebung()) {
        WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
        }
      else
        Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
      pnum ++ ;

      ASSIGN(1,short(ifield + VarNum (td,ck->VarID) + 1));
      ASSIGN(2,short(ck->KeyNmbr));
      kn = ck->KeyNmbr ;
      ASSIGN(3,short(pnum));
      ASSIGN(4,short (LPBTRVTABLE(td->GetDLLDef())->GetDescRef()->k[i].flag));

      if (EntwicklungsUmgebung()) {
        WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
        }
      else
        Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
      pnum ++ ;
      #endif
      }
    else {
      ASSIGN(1,short(ifield + VarNum (td,ck->VarID)));
      ASSIGN(2,short(ck->KeyNmbr));
      if (ck->KeyNmbr != kn)
        pnum = 0 ;
      kn = ck->KeyNmbr ;
      ASSIGN(3,short(pnum));
      ASSIGN(4,short (LPBTRVTABLE(td->GetDLLDef())->GetDescRef()->k[i].flag));

      if (EntwicklungsUmgebung()) {
        WIN_ASSERT (Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
        }
      else
        Out (rec,-1,DBCALLTYPE_STANDARDINSERT,NULL,"");
      pnum ++ ;
      }
    delete rec ;
    }
  spacePadd = FALSE ;
  }
