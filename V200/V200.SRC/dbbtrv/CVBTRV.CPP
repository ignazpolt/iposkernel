//////////////////////////////////////////////////////////////////////////
//  Kompilieren der Variablendeklarationen
//////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbbtrv/rev/cvbtrv.cpv   1.14   13 Oct 1998 13:04:02   Gerhold  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/cvbtrv.cpv  $
// 
//    Rev 1.14   13 Oct 1998 13:04:02   Gerhold
// HINSTANCE hLibInst wegen VC6
// 
//    Rev 1.13   04 Aug 1998 17:55:34   Hannes
// Timestamp
// 
//    Rev 1.12   08 Nov 1996 13:26:38   HANNES
// QLong, Replikator
// 
//    Rev 1.11   07 Nov 1996 08:03:38   GERHOLD
// DBINT statt int
// 
//    Rev 1.10   17 Jun 1996 15:38:26   HANNES
// Einbau von BLOBS
// 
//    Rev 1.9   04 Feb 1996 17:28:22   HANNES
// 
//    Rev 1.8   02 Feb 1996 10:42:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   16 Feb 1995 12:46:18   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.6   29 Jan 1995 11:45:12   HANNES
// 
//    Rev 1.5   24 Jan 1995 10:58:58   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.4   10 Jan 1995 17:28:08   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.3   02 Jan 1995 09:43:20   HANNES
// 
//    Rev 1.2   31 Oct 1994 10:36:44   hannes
// Initialize verbessert
// 
//    Rev 1.1   10 Aug 1994 12:07:28   HANNES
// Time eingebaut
// 
//    Rev 1.0   24 Jun 1994 16:43:20   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "tbkw.h"
#include "tbbtrv.hpp"
#define MODULENUM 82
#include "winass.hpp"
#include "tbdef.hpp"

/*---------------------------------------------------------------*/
/*  Klasse VarCompiler: Kompilieren von Variablenbeschreibungen  */
/*---------------------------------------------------------------*/
class VarCompiler : public compiler {
 public :
  virtual DLLExport BOOL _export AllowOperator()
    { return (*actptr != '-') ; }
  
  virtual DLLExport void _export WINAPI InstallBuffer(LPVOID d)
    { actptr = buffer_start = begstr = LPSTR(d) ; }
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  VarCompiler () : compiler (NULL) { }
  };
typedef VarCompiler FAR *LPVARCOMPILER;

extern HINSTANCE hLibInst;
DLLExport void _export WINAPI VarCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (hLibInst,VRKW_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

DLLExport BOOL _export WINAPI VarCompiler::TestError (void)
  {
  if (wError > VRCMPERROR_BASE) {
    char pattern[64];
    char errstr[64];
    LoadString (hLibInst,TBCMPERROR_BASE,pattern,sizeof(pattern));
    LoadString (hLibInst,wError,errstr,sizeof(errstr));
    char outtxt[256];
    wsprintf (outtxt,pattern,fmname,LineNr,column,LPSTR(errstr));
    MessageBox (GetActiveWindow(),outtxt,"Definitionsfehler",MB_OK | MB_TASKMODAL);
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static union {
  VarDesc h;
  char x[128];
  } VarBuffer;
struct VarDesc FAR &lastVar = VarBuffer.h;
LPBTRVTABLE actTable;
static LPVARCOMPILER cVrComp;

#define MAXCOMPATIBLES 5
#define MAX_MTYPES     19
struct CompatibleTypes {
  WORD dType[MAXCOMPATIBLES] ; 
  } CompMatrix[MAX_MTYPES] = {
  /* VAR_LONG   */ { BDT_AUTOINC , BDT_INTEGER , BDT_UNSIGNED , WORD(-1) ,    WORD(-1)    } ,
  /* VAR_DEC    */ { BDT_FLOAT ,   BDT_INTEGER , BDT_UNSIGNED , WORD(-1) ,    WORD(-1)    } ,
  /* VAR_STR    */ { BDT_STRING ,  BDT_LSTRING , BDT_ZSTRING ,  DT_LDSTRING , DT_SPRIVATE } ,
  /* VAR_POINT  */ { DT_PRIVATE ,  WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_CONT   */ { DT_PRIVATE ,  DT_SPRIVATE , WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_STRARR */ { BDT_INTEGER , BDT_UNSIGNED ,BDT_AUTOINC ,  WORD(-1) ,    WORD(-1)    } ,
  /* VAR_FLAG   */ { BDT_LOGICAL , BDT_INTEGER , BDT_UNSIGNED , WORD(-1) ,    WORD(-1)    } ,
  /* VAR_SCALE  */ { DT_PRIVATE ,  WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_PICTURE*/ { WORD(-1) ,    WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_DATE   */ { BDT_DATE ,    DT_KLDATE ,   WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_PROC   */ { WORD(-1) ,    WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_IMAGE  */ { WORD(-1) ,    WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_DWORD  */ { BDT_UNSIGNED ,BDT_AUTOINC , BDT_INTEGER ,  BDT_TIME ,    BDT_MONEY   } ,
  /* VAR_OBJ    */ { BDT_INTEGER , BDT_UNSIGNED ,DT_PRIVATE ,   DT_SPRIVATE , WORD(-1)    } ,
  /* VAR_BITMAP */ { WORD(-1) ,    WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_TIME   */ { BDT_TIME ,    WORD(-1) ,    WORD(-1) ,     WORD(-1) ,    WORD(-1)    } ,
  /* VAR_QLONG  */ { DT_PRIVATE , WORD(-1) , WORD(-1) , WORD(-1) , WORD(-1) } ,
  /* VAR_BLOB   */ { DT_PRIVATE , WORD(-1) , WORD(-1) , WORD(-1) , WORD(-1) } ,
  /* VAR_DATETIME */ { DT_PRIVATE , WORD(-1) , WORD(-1) , WORD(-1) , WORD(-1) }
  };

BOOL CheckDataTypes (WORD mType,WORD dType)
  {
  for (WORD i = 0 ; i < MAXCOMPATIBLES ; i++) {
    if (dType == CompMatrix[mType].dType[i]) return TRUE ;
    }
  return FALSE ;
  }

// Codegenerierung
static WORD cmpSize;
DLLExport void _export _SetMapType_Field () { lastVar.mapType = MAPTYPE_FIELD ; cmpSize = sizeof(lastVar) - sizeof (_extDesc) + sizeof(WORD) ; } 
BOOL SetVarOffs (LPSTR Name)       
  { 
  LPVBTRV v = actTable->GetVar (Name,FALSE);
  if (v != NULL) {
    lastVar.b.dOffs = LPSTR(v) - LPSTR(actTable->GetVarRef(FALSE));
    return (CheckDataTypes (lastVar.mType,v->DataType));
    }
  else
    return FALSE ;
  }
DLLExport void _export _SetVarOffs ()       
  { 
  LPSTR Name = LPSTR(GlobalLock (cVrComp->hPars0)) + sizeof(WORD) ; 
  if (!SetVarOffs (Name)) cVrComp->wError = VERROR_FIELDNOTDEFINED;
  GlobalUnlock (cVrComp->hPars0);
  }

DLLExport void _export _SetVLength () 
  { 
  lastVar.b.kl.VarLen = WORD(cVrComp->scv.v.int_val);
  }
DLLExport void _export _SetVOffset () 
  { 
  lastVar.b.kl.VarOffset = int(cVrComp->scv.v.int_val);
  }
DLLExport void _export _SetVIdent  () 
  { 
  lastVar.b.kl.BlockID = WORD(cVrComp->scv.v.int_val);
  }
DLLExport void _export _CheckKBlocked () 
  { 
  lastVar.mapType = MAPTYPE_KLBLOCKED;
  if (actTable->BlockType != BLOCKTYPE_KL)
    cVrComp->wError = VERROR_BLOCKTYPE;
  else
    cmpSize = sizeof(lastVar);
  }

DLLExport void _export _CheckMBlocked () 
  { 
  lastVar.mapType = MAPTYPE_MBLOCKED;
  if ((actTable->BlockType != BLOCKTYPE_MARILLE) && (actTable->BlockType != BLOCKTYPE_MARILLE1))
    cVrComp->wError = VERROR_BLOCKTYPE;
  else
    cmpSize = sizeof(lastVar) - sizeof(_extDesc) + sizeof(WORD);
  }
DLLExport void _export _SetVDT_KLDATE     () { lastVar.b.kl.DataType = DT_KLDATE    ; }
DLLExport void _export _SetVDT_LDSTRING   () { lastVar.b.kl.DataType = DT_LDSTRING  ; }
DLLExport void _export _SetVDT_SPRIVATE   () { lastVar.b.kl.DataType = DT_SPRIVATE  ; }
DLLExport void _export _SetVDT_PRIVATE    () { lastVar.b.kl.DataType = DT_PRIVATE   ; }
DLLExport void _export _SetVBDT_AUTOINC   () { lastVar.b.kl.DataType = BDT_AUTOINC  ; }
DLLExport void _export _SetVBDT_UNSIGNED  () { lastVar.b.kl.DataType = BDT_UNSIGNED ; }
DLLExport void _export _SetVBDT_ZSTRING   () { lastVar.b.kl.DataType = BDT_ZSTRING  ; }
DLLExport void _export _SetVBDT_LSTRING   () { lastVar.b.kl.DataType = BDT_LSTRING  ; }
DLLExport void _export _SetVBDT_BFLOAT    () { lastVar.b.kl.DataType = BDT_BFLOAT   ; }
DLLExport void _export _SetVBDT_NUMERIC   () { lastVar.b.kl.DataType = BDT_NUMERIC  ; }
DLLExport void _export _SetVBDT_LOGICAL   () { lastVar.b.kl.DataType = BDT_LOGICAL  ; }
DLLExport void _export _SetVBDT_MONEY     () { lastVar.b.kl.DataType = BDT_MONEY    ; }
DLLExport void _export _SetVBDT_DECIMAL   () { lastVar.b.kl.DataType = BDT_DECIMAL  ; }
DLLExport void _export _SetVBDT_TIME      () { lastVar.b.kl.DataType = BDT_TIME     ; }
DLLExport void _export _SetVBDT_DATE      () { lastVar.b.kl.DataType = BDT_DATE     ; }
DLLExport void _export _SetVBDT_FLOAT     () { lastVar.b.kl.DataType = BDT_FLOAT    ; }
DLLExport void _export _SetVBDT_INTEGER   () { lastVar.b.kl.DataType = BDT_INTEGER  ; }
DLLExport void _export _SetVBDT_STRING    () { lastVar.b.kl.DataType = BDT_STRING   ; }
DLLExport void _export _CheckDataTypes    () 
  {
  if (!CheckDataTypes (lastVar.mType,lastVar.b.kl.DataType)) cVrComp->wError = VERROR_INCOMPATIBLETYPE;
  }
static WORD SegNum;
char KeySegName[3][128];
DLLExport void _export _EndForeignAccess () 
  {
  _foreignDesc FAR *f = (_foreignDesc FAR *) (VarBuffer.x + lastVar.foreignOffs);
  for (WORD i = 0 ; i < SegNum ; i++) {
    f->SegNames[i] = cmpSize;
    lstrcpy (VarBuffer.x + cmpSize,KeySegName[i]);
    cmpSize += lstrlen(KeySegName[i])+1;
    }
  }
void SetForeignGetAccess (LPSTR Name) 
  {
  lstrcpy (VarBuffer.x + cmpSize,Name);
  cmpSize += lstrlen(Name)+1;
  }
DLLExport void _export _SetForeignGetAccess () 
  {
  LPSTR Name = LPSTR(GlobalLock (cVrComp->hPars0)) + sizeof(WORD);
  SetForeignGetAccess (Name) ;
  GlobalUnlock (cVrComp->hPars0);
  }
DLLExport void _export _SetForeignDelAccess () 
  {
  LPSTR Name = LPSTR(GlobalLock (cVrComp->hPars0)) + sizeof(WORD);
  lstrcpy (VarBuffer.x + cmpSize,Name);
  cmpSize += lstrlen(Name)+1;
  GlobalUnlock (cVrComp->hPars0);
  }
DLLExport void _export _SetNoForeignDelAccess () 
  {
  lstrcpy (VarBuffer.x + cmpSize,"");
  cmpSize += 1;
  }
void GetForeignTable (LPSTR Name)
  {
  _foreignDesc FAR *f = (_foreignDesc FAR *) (VarBuffer.x + cmpSize);
  lstrcpy (f->TableName,Name);
  lastVar.foreignOffs = cmpSize;
  cmpSize += sizeof(*f) + lstrlen(Name);
  SegNum = 0;
  f->SegNames[0] = 
  f->SegNames[1] = 
  f->SegNames[2] = 0;
  }
DLLExport void _export _GetForeignTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (cVrComp->hPars0)) + sizeof(WORD);
  GetForeignTable(Name);
  GlobalUnlock (cVrComp->hPars0);
  }

DLLExport void _export _SetPrimary ()
  {
  lastVar.primaryKey = TRUE ;
  }

void AddForeignSeg (LPSTR Name)
  {
  lstrcpy (KeySegName[SegNum],Name);
  SegNum ++ ;
  }

DLLExport void _export _AddForeignSeg ()
  {
  if (SegNum >= 3) cVrComp->wError = VERROR_MAXKEYSEGS;
  LPSTR Name = LPSTR(GlobalLock (cVrComp->hPars0)) + sizeof(WORD);
  AddForeignSeg (Name);
  GlobalUnlock (cVrComp->hPars0);
  }

// Syntaxdefinition
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

syntax_node kldtype17  = { NULL , NULL       , TRUE , INITERM(KEYWORD,KWVKLDATE  ) , _SetVDT_KLDATE    } ; 
syntax_node kldtype16  = { NULL , &kldtype17 , TRUE , INITERM(KEYWORD,KWVLDSTRING) , _SetVDT_LDSTRING  } ; 
syntax_node kldtype15  = { NULL , &kldtype16 , TRUE , INITERM(KEYWORD,KWVSPRIVATE) , _SetVDT_SPRIVATE  } ; 
syntax_node kldtype14  = { NULL , &kldtype15 , TRUE , INITERM(KEYWORD,KWVPRIVATE ) , _SetVDT_PRIVATE   } ; 
syntax_node kldtype13  = { NULL , &kldtype14 , TRUE , INITERM(KEYWORD,KWVAUTOINC ) , _SetVBDT_AUTOINC  } ; 
syntax_node kldtype12  = { NULL , &kldtype13 , TRUE , INITERM(KEYWORD,KWVUNSIGNED) , _SetVBDT_UNSIGNED } ; 
syntax_node kldtype11  = { NULL , &kldtype12 , TRUE , INITERM(KEYWORD,KWVZSTRING ) , _SetVBDT_ZSTRING  } ; 
syntax_node kldtype10  = { NULL , &kldtype11 , TRUE , INITERM(KEYWORD,KWVLSTRING ) , _SetVBDT_LSTRING  } ; 
syntax_node kldtype9   = { NULL , &kldtype10 , TRUE , INITERM(KEYWORD,KWVBFLOAT  ) , _SetVBDT_BFLOAT   } ; 
syntax_node kldtype8   = { NULL , &kldtype9  , TRUE , INITERM(KEYWORD,KWVNUMERIC ) , _SetVBDT_NUMERIC  } ; 
syntax_node kldtype7   = { NULL , &kldtype8  , TRUE , INITERM(KEYWORD,KWVLOGICAL ) , _SetVBDT_LOGICAL  } ; 
syntax_node kldtype6   = { NULL , &kldtype7  , TRUE , INITERM(KEYWORD,KWVMONEY   ) , _SetVBDT_MONEY    } ; 
syntax_node kldtype5   = { NULL , &kldtype6  , TRUE , INITERM(KEYWORD,KWVDECIMAL ) , _SetVBDT_DECIMAL  } ; 
syntax_node kldtype4   = { NULL , &kldtype5  , TRUE , INITERM(KEYWORD,KWVTIME    ) , _SetVBDT_TIME     } ; 
syntax_node kldtype3   = { NULL , &kldtype4  , TRUE , INITERM(KEYWORD,KWVDATE    ) , _SetVBDT_DATE     } ; 
syntax_node kldtype2   = { NULL , &kldtype3  , TRUE , INITERM(KEYWORD,KWVFLOAT   ) , _SetVBDT_FLOAT    } ; 
syntax_node kldtype1   = { NULL , &kldtype2  , TRUE , INITERM(KEYWORD,KWVINTEGER ) , _SetVBDT_INTEGER  } ; 
syntax_node kldtype    = { NULL , &kldtype1  , TRUE , INITERM(KEYWORD,KWVUSTRING ) , _SetVBDT_STRING   } ; 

syntax_node mblocked1 = { NULL       , NULL       , TRUE  , INITERM(T_INTEGER,0) , _SetVIdent          } ;
syntax_node mblocked  = { &mblocked1 , NULL       , TRUE  , INITERM(KEYWORD,KWVIDENT) , _CheckMBlocked } ;

syntax_node blocked6  = { NULL      , NULL       , TRUE  , INITERM(T_INTEGER,0) , _SetVLength } ;
syntax_node blocked5  = { &blocked6 , NULL       , TRUE  , INITERM(KEYWORD,KWVLENGTH) , NULL  } ;
syntax_node blocked4  = { &blocked5 , NULL       , TRUE  , INITERM(T_INTEGER,0) , _SetVOffset } ;
syntax_node blocked3  = { &blocked4 , NULL       , TRUE  , INITERM(KEYWORD,KWVOFFSET) , NULL  } ;
syntax_node blocked2  = { &blocked3 , NULL       , FALSE , &kldtype , _CheckDataTypes         } ;
syntax_node blocked1  = { &blocked2 , NULL       , TRUE  , INITERM(T_INTEGER,0) , _SetVIdent  } ;
syntax_node blocked   = { &blocked1 , &mblocked  , TRUE  , INITERM(KEYWORD,KWBIDENT) , _CheckKBlocked } ;

syntax_node map1 = { NULL  , NULL     , TRUE , INITERM(UNKNOWNIDENT,FALSE) , _SetVarOffs } ;
syntax_node map  = { &map1 , &blocked , TRUE , INITERM(KEYWORD,KWVMAP) ,     _SetMapType_Field } ;

extern syntax_node othersegs1;
syntax_node othersegs3 = { NULL        , NULL        , TRUE , INITERM(FREECHAR,0)        , NULL } ;
syntax_node othersegs2 = { &othersegs1 , &othersegs3 , TRUE , INITERM(KEYWORD,KWCOLON)   , NULL } ;
syntax_node othersegs1 = { &othersegs2 , NULL        , TRUE , INITERM(UNKNOWNIDENT,0)    , _AddForeignSeg } ;
syntax_node othersegs  = { &othersegs1 , NULL        , TRUE , INITERM(KEYWORD,KWVKEYCAT) , NULL } ;


syntax_node foreign8 = { NULL      , NULL      , TRUE  , INITERM(FREECHAR,0) , _SetNoForeignDelAccess     } ;
syntax_node foreign7 = { NULL      , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetForeignDelAccess   } ;
syntax_node foreign6 = { &foreign7 , &foreign8 , TRUE  , INITERM(KEYWORD,KWVDEL) , NULL                   } ;
syntax_node foreign5 = { &foreign6 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetForeignGetAccess   } ;
syntax_node foreign4 = { &foreign5 , NULL      , TRUE  , INITERM(KEYWORD,KWVGET) , NULL             } ;
syntax_node foreign3 = { &foreign4 , &foreign4 , FALSE , &othersegs , NULL } ;
syntax_node foreign2 = { &foreign3 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0) , _GetForeignTable } ;
syntax_node foreign1 = { &foreign2 , NULL      , TRUE  , INITERM(KEYWORD,KWVTO) , NULL              } ;
syntax_node foreign  = { &foreign1 , NULL      , TRUE  , INITERM(KEYWORD,KWVFOREIGN) , NULL         } ;

syntax_node primary  = { NULL      , NULL , TRUE , INITERM(KEYWORD,KWVPRIMARY) , _SetPrimary  } ;

syntax_node var3 = { NULL  , NULL  , TRUE  , INITERM(KEYWORD,KWVSEMICOLON) , NULL } ;
syntax_node var2 = { &var3 , &var3 , FALSE , &primary , NULL } ;
syntax_node var1 = { &var2 , &var2 , FALSE , &foreign , _EndForeignAccess } ;
syntax_node var  = { &var1 , NULL  , FALSE , &map , NULL } ;
// Durchfueren der Variablenkompilierung
//////////////////////////////////////////////////
DLLExport LPVOID _export WINAPI DataDict_VarDef (LPVOID InitData,WORD mType,LPVOID TableData,LPSTR VarString,BOOL FAR *error,DWORD FAR *size)
  {
  VarCompiler FAR *t  = new VarCompiler ();

  actTable            = LPBTRVTABLE (TableData);
  lastVar.mType       = mType;
  lastVar.foreignOffs = 0;
  lastVar.primaryKey  = FALSE;
  cVrComp             = t;

  lstrcpy (t->fmname,"Variablendefinition");
  t->DoParse (VarString,&var,NULL);
  LPVOID res ;
  if (t->wError)
    res = NULL , *size = 0 , *error = TRUE ;
  else
    res = &lastVar , *size = cmpSize , *error = FALSE ;
  delete t;

  return res;
  }

void CheckForeignDef (LPTABLEDEF td,WORD VarNr)
  {
  for (int i = 0 ; i < td->GetAnzRIDefs() ; i++) {
    LPCLRIDEF r = td->GetRIDef(i);
    if (r->Type == CLKR_EXTENDED) {
      ExtendedRI FAR *ei = r->GetERI();
      WORD FAR *IDList = ei->GetVarIDList();
      if (IDList[0] == VarNr) {
        // Na ja, dann halt los
        GetForeignTable (r->name);
        if (r->AnzSegs > 1) {
          for (WORD j = 1 ; j < r->AnzSegs ; j++) 
            AddForeignSeg (td->GetVarDef(IDList[j])->GetName());
          }
        SetForeignGetAccess (ei->AccessName) ;
        _SetNoForeignDelAccess ();
        _EndForeignAccess ();
        }
      }
    }
  }

void CheckPrimary(LPTABLEDEF td,WORD VarNr)
  {
  for (int i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    LPCLKEYDEF k = td->GetKeyDef(i);
    if ((k->VarID == VarNr) && (k->KeyNmbr == 0))
      _SetPrimary ();
    }
  }

void CompleteVarDef (LPTABLEDEF td,LPBTRVTABLE t)
  {
  BOOL correct = TRUE ;
  actTable  = t;
  for (int i = 0 ; ((i < td->GetAnzVars ()) && (correct)) ; i++) {
    LPVARDEF v = td->GetVarDef (i);
    lastVar.mType       = v->mType;
    lastVar.foreignOffs = 0;
    lastVar.primaryKey  = FALSE;
    if (v->VarID == 0xFFFF) {
      // direkt gemappte Variable
      _SetMapType_Field ();
      correct = SetVarOffs (v->GetName());
      CheckForeignDef(td,WORD(i));
      CheckPrimary(td,WORD(i));
      }
    else {
      lastVar.mapType = MAPTYPE_MBLOCKED;
      lastVar.b.kl.BlockID = v->VarID;
      }
    LPVARDEF n = LPVARDEF (GetGlobMem (int(v->structSize) + cmpSize));
    lmemcpy (n,v,int(v->structSize));
    n->DLLDataOffs = int(v->structSize);
    lmemcpy (LPSTR(n)+int(v->structSize),&lastVar,cmpSize);
    n->structSize = GetBlockSize (n);
    td->SetVarDef (n,i);
    }
  }

/*-----------------------------------------------------------*/
/*  Freigeben der Variablendefinition nach dem Speichern ... */
/*-----------------------------------------------------------*/
DLLExport void _export WINAPI DataDict_FreeVarDef (LPVOID VarDef)
  {
  WIN_ASSERT (VarDef == LPVOID (&lastVar));
  }

DLLExport WORD _export WINAPI DataDict_GetMType (LPVOID VarData)
  {
  return LPDDSVARDESC (VarData)->mType;
  }

DLLExport void _export WINAPI DataDict_GetVarDescExtra (LPVOID VarData,LPSTR txt,WORD txtSize)
  {
  LPDDSVARDESC vd = LPDDSVARDESC (VarData);
  if (vd->IsForeignKey()) {
    LPFOREIGNDESC f = vd->GetForeignDesc ();
    char pattern[64];
    LoadString (hLibInst,FOREIGNDESC_PATTERN,pattern,sizeof(pattern));
    wsprintf (txt,pattern,f->GetTableName(),f->GetGetName());
    }
  }

DLLExport BOOL _export WINAPI DataDict_IsForeignKey (LPVOID VarData,LPSTR TableName,int TableNameSize,LPSTR AccessName,int AccessNameSize,LPSTR DelName,int DelNameSize,LPSEGNAMEPTRS ks)
  {
  LPDDSVARDESC vd = LPDDSVARDESC (VarData);
  if (vd->IsForeignKey()) {
    LPFOREIGNDESC f = vd->GetForeignDesc ();
    lstrcpy (TableName,f->GetTableName());
    lstrcpy (AccessName,f->GetGetName());
    if (DelName != NULL) {
      lstrcpy (DelName,f->GetDelName());
      }
    for (int i = 0 ; i < 3 ; i++)
      ks->kn[i] = f->GetKeySegName (LPSTR(VarData),i);
    return TRUE ;
    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI DataDict_IsPrimary (LPVOID VarData)
  {
  LPDDSVARDESC vd = LPDDSVARDESC (VarData);
  return vd->IsPrimaryKey();
  }

DLLExport BOOL _export WINAPI DataDict_GetVarProperty (LPVOID TableData,LPVOID VarData,WORD propCmd,LPVOID propCmdData)
  {
  LPDDSVARDESC vd;
  LPBTRVTABLE t = LPBTRVTABLE (TableData);
  LPVBTRV v;
  BOOL res = TRUE ;
  switch (propCmd) {
    case VPROP_DATASIZE :
      vd = LPDDSVARDESC (VarData);
      v = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
      if (vd->mapType == MAPTYPE_FIELD) {
        *((DBINT FAR *) (propCmdData)) = DBINT(v->VarLen);
        }
      else
        *((DBINT FAR *) (propCmdData)) = -1;
      break ;
    case VPROP_DATAID :
      vd = LPDDSVARDESC (VarData);
      v = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
      if (vd->mapType == MAPTYPE_MBLOCKED) {
        *((WORD FAR *) (propCmdData)) = vd->b.m.VarID;
        }
      else if (vd->mapType == MAPTYPE_KLBLOCKED) {
        *((WORD FAR *) (propCmdData)) = vd->b.kl.BlockID;
        }
      else
        *((WORD FAR *) (propCmdData)) = 0xFFFF;
      break ;
    case VPROP_GETANZKEYSEGS :
      {
      LPRECDESC r = t->GetDescRef (FALSE);
      *((DBINT FAR *) propCmdData) = r->AnzKeySegs;
      }
      break ;
    case VPROP_GETKEYSEGINFO :
      {
      int Nr = int (DWORD (VarData));
      LPKEYDEF Key = t->GetFirstKey (FALSE);
      if (Key == NULL) return FALSE ;
      LPVARTBL h = LPVARTBL (Key->Name + lstrlen(Key->Name) + 1) ;
      LPVBTRV x = &h->v[0];
      res = FALSE ;
      int KeyNmbr = 0;
      RecDesc FAR *rd = t->GetDescRef (FALSE);
      if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
        for ( int i = 0 ; ; i++) {
          if (i == Nr) {
            LPCLKEYDEF r = LPCLKEYDEF (propCmdData);
            r->KeyNmbr = KeyNmbr;
            r->Attribute = 0L;
            if ((rd->k[i].flag & KA_DUPLICATE) == 0)
              r->Attribute |= CLKD_UNIQUE ;
            if (rd->k[i].flag & KA_MODIFIABLE)
              r->Attribute |= CLKD_MODIFYABLE ;
            if (rd->k[i].flag & KA_NULL)
              r->Attribute |= CLKD_NULL ;
            if (x->DataType == BDT_AUTOINC)
              r->Attribute |= CLKD_AUTOINC ;
            lstrcpy (r->name,Key->Name);
            r->structSize = sizeof(*r) + lstrlen(r->name);
            lstrcpy (LPSTR(r)+int(r->structSize),x->Name);
            return TRUE ;
            }
          x = x->Next (h->gSize,h);
          if (x == NULL) {
            KeyNmbr ++ ;
            Key = t->GetNextKey (Key,FALSE);
            if (Key == NULL) return FALSE ;
            h = LPVARTBL (Key->Name + lstrlen(Key->Name) + 1) ;
            if (h->gSize > (sizeof(*h) - sizeof(h->v[0])))
              x = &h->v[0];
            else
              return FALSE ;
            }
          }
        }
      }
      break ;
    case VPROP_GETFOREIGNDATA :
      vd = LPDDSVARDESC (VarData);
      v = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
      if (vd->IsForeignKey()) {
        LPSTR h = LPSTR(propCmdData);
        LPFOREIGNDESC f = vd->GetForeignDesc ();
        lstrcpy (h,f->GetTableName());
        h += lstrlen(h) + 1;
        lstrcpy (h,f->GetGetName());
        h += lstrlen(h) + 1;
        lstrcpy (h,v->Name);
        h += lstrlen(h) + 1;
        for (int i = 0 ; i < 3 ; i++) {
          LPSTR n = f->GetKeySegName(LPSTR(VarData),i);
          if (n != NULL) {
            lstrcpy (h,n);
            h += lstrlen(h) + 1;
            }
          }
        *h = '\0';
        return TRUE ;
        }
      else
        return FALSE ;
      break ;
    default :
      res = FALSE ;
    }
  return res;
  }
