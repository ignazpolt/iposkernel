////////////////////////////////////////////////////////////////////////////
//  Generieren des Datadictionarys fuer Haupttabellen, neue Konvention
////////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genrtbl.cpv   1.25   05 Oct 1998 11:26:48   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/genrtbl.cpv  $
// 
//    Rev 1.25   05 Oct 1998 11:26:48   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.24   05 Aug 1998 08:39:32   Hannes
// Syntaxverbesserungen Property
// 
//    Rev 1.23   04 Aug 1998 17:49:08   Hannes
// Timestamp
// 
//    Rev 1.22   28 Jul 1998 19:59:14   Hannes
// Properties
// 
//    Rev 1.21   28 Aug 1997 15:51:50   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.20   28 Apr 1997 11:16:24   Hannes
// 
//    Rev 1.19   13 Mar 1997 19:04:24   Hannes
// Blobs in DDD's
// 
//    Rev 1.18   19 Feb 1997 12:14:24   Hannes
// Parent von Tabellendefinition / Scriptfunktionen neu
// 
//    Rev 1.17   26 Nov 1996 19:08:22   HANNES
// 
//    Rev 1.16   26 Nov 1996 08:10:26   HANNES
// Automatischer Update
// 
//    Rev 1.15   08 Nov 1996 13:30:40   HANNES
// QLong,Replikator
// 
//    Rev 1.14   21 Jun 1996 15:27:22   GERHOLD
// _StoreTable ... InitializeTableID ( ... , ...-1)
// 
//    Rev 1.13   17 Jun 1996 16:53:48   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.12   04 Feb 1996 21:49:30   HANNES
// 
//    Rev 1.11   04 Feb 1996 17:00:38   HANNES
// Protyp LogMsg
// 
//    Rev 1.10   02 Feb 1996 10:51:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   31 Jan 1996 18:18:18   HANNES
// null=... in der Syntax des Table - Compilers
// 
//    Rev 1.8   27 Aug 1995 13:00:36   HANNES
// 
//    Rev 1.7   09 Jun 1995 00:28:54   HANNES
// Erweiterung in Varelem
// 
//    Rev 1.6   02 May 1995 16:29:20   HANNES
// 
//    Rev 1.5   26 Apr 1995 15:26:36   HANNES
// 
//    Rev 1.4   02 Apr 1995 13:33:24   HANNES
//  
// 
//    Rev 1.3   31 Mar 1995 18:23:34   HANNES
//  
// 
//    Rev 1.2   24 Feb 1995 11:00:42   HANNES
// 
//    Rev 1.1   16 Feb 1995 12:35:18   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.0   29 Jan 1995 11:47:38   HANNES
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

#include "get_put.hpp"


extern HINSTANCE MyInstance;
HWND hTbWnd;
class TbCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);
  virtual DLLExport void _export FAR PASCAL InstallBuffer(LPVOID d);

  TbCompiler () : compiler (NULL) { }
  };

LPVOID GetBuffer;
extern LPSTR GetFName(LPVOID fname);
static LPSTR _NameZuSchreiben;
extern BOOL mystrcmp (LPSTR s1,LPSTR s2);
void TbCompiler::InstallBuffer(LPVOID d)
  {
  compiler::InstallBuffer (d);
  if (wError == 0) {
    int v,vg;
    // Ueberpruefen, ob es sich wirklum um die neueste Version handelt
    if (mystrcmp (buffer_start,"_Version")) {
      LPSTR h = buffer_start + 9 ;
      for (v = 0 ; ((*h >= '0') && (*h <= '9')) ; h++)
        v = v * 10 + *h - '0' ;
      }
    else
      v = 0 ;
    char errmsg[256];
    int Size;
    GetBuffer = ReadBlock (&Size,-1,GetFName(d),FALSE,errmsg,FALSE);
    if (GetBuffer != NULL) {
      LPSTR h = LPSTR(GetBuffer) + 9 ;
      for (vg = 0 ; ((*h >= '0') && (*h <= '9')) ; h++)
        vg = vg * 10 + *h - '0' ;
      if (vg > v) {
        // Die geholte Variante muss genommen werden
        GlobalUnlock (hText);
        GlobalFree (hText);
        hText = 0;
        wError = FILENOTFOUND ;
        }
      FreeGlobMem (GetBuffer);
      GetBuffer = NULL ;
      }
    }
  if (wError == FILENOTFOUND) {
    lstrcpy (_NameZuSchreiben,GetFName(d));
    _NameZuSchreiben[lstrlen(_NameZuSchreiben)-1] = '~' ;
    // Es wird mit einem Get Probiert !!!
    char errmsg[256];
    int Size;
    GetBuffer = ReadBlock (&Size,-1,GetFName(d),FALSE,errmsg,FALSE);
    if (GetBuffer != NULL) {
      buffer_start = LPSTR(GetBuffer) ;
      actptr = buffer_start;
      wError = 0 ;
      }
    }
  }

class TBbCompiler : public TbCompiler {
 public :
  virtual DLLExport void _export FAR PASCAL InstallBuffer(LPVOID d);
  };

void TBbCompiler::InstallBuffer(LPVOID d)
  {
  buffer_start = LPSTR (d) ;
  actptr = buffer_start;
  }

DLLExport void _export WINAPI TbCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,TBCMPL_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

#define TBCMPERROR    1000
DLLExport BOOL _export WINAPI TbCompiler::TestError ()
  {
  if (wError == TBCMPERROR) {
    if (GetCommandLineFlag())
      LogMsg ("Definitionsfehler");
    else
      MessageBox (hTbWnd,"Definitionsfehler","Resourcefehler",MB_OK | MB_TASKMODAL);
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static TbCompiler FAR *TCmp;

/////////////////////////////////////////////////////////////////////////
//  Codegenerierung
/////////////////////////////////////////////////////////////////////////
static char CmplBuffer[256];
static VarDef FAR * _v = (VarDef FAR *) CmplBuffer;
LPCLKEYDEF _k = LPCLKEYDEF (CmplBuffer);
LPCLRIDEF _r = LPCLRIDEF (CmplBuffer);
static LPSTR _FName;
TableDef FAR *_td;
/*----< Ende Foreignfunktionen >-----*/
DLLExport void _export _AddExtVarID ()
  {
  WORD dt;
  BOOL found;
  WORD VarID = _td->GetVarID (LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD),&dt,&found);
  GlobalUnlock (TCmp->hPars0);
  if (found) {
    *((WORD FAR *) (LPSTR(_r) + int(_r->structSize))) = VarID;
    _r->AnzSegs ++;
    _r->structSize += sizeof(WORD);
    }
  else 
    TCmp->wError = TBCMPERROR;
  }
DLLExport void _export _SetAccess ()
  {
  LPSTR n = _r->GetERI()->AccessName;
  lstrcpy (n,LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD));
  _r->structSize += lstrlen (n) + 1;
  GlobalUnlock(TCmp->hPars0);
  }
DLLExport void _export _SetForeinTable ()
  {
  lstrcpy (_r->name,LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD));
  _r->structSize = sizeof(*_r) + lstrlen (_r->name);
  _r->AnzSegs = 0;
  GlobalUnlock(TCmp->hPars0);
  }
DLLExport void _export _MarkStandard ()
  {
  _r->Type = CLKR_STANDARD;
  }
DLLExport void _export _MarkExtended ()
  {
  _r->Type = CLKR_EXTENDED;
  }
DLLExport void _export _SetStdVarID ()
  {
  StandardRI FAR *s = (StandardRI FAR *) (LPSTR(_r) + _r->structSize);
  WORD dt;
  BOOL found;
  s->VarID = _td->GetVarID (LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD),&dt,&found);
  GlobalUnlock (TCmp->hPars0);
  if (!found) TCmp->wError = TBCMPERROR;
  else {
    _r->AnzSegs ++;
    _r->structSize += sizeof(*s) + lstrlen(s->ForeignField);
    }
  }
DLLExport void _export _AddForeignVar ()
  {
  StandardRI FAR *s = (StandardRI FAR *) (LPSTR(_r) + _r->structSize);
  lstrcpy (s->ForeignField,LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD));
  GlobalUnlock(TCmp->hPars0);
  }
DLLExport void _export _StoreForeign ()
  {
  _td->AddForeign(_r);
  }
/*----< Ende Foreignfunktionen >-----*/
/*----< Feldfunktionen >--------*/
DLLExport void _export _SetNotNull ()
  {
  _v->Property |= VPROP_NOTNULL ;
  }
DLLExport void _export _SetVarType ()
  {
  static struct kwToVt { int kw ; WORD vType ; } ktv [] = {
    { TC_VAR_LONG     , VAR_LONG   } ,
    { TC_VAR_DEC      , VAR_DEC    } ,
    { TC_VAR_STR      , VAR_STR    } ,
    { TC_VAR_POINT    , VAR_POINT  } ,
    { TC_VAR_CONT     , VAR_CONT   } ,
    { TC_VAR_STRARR   , VAR_STRARR } ,
    { TC_VAR_FLAG     , VAR_FLAG   } ,
    { TC_VAR_SCALE    , VAR_SCALE  } ,
    { TC_VAR_DATE     , VAR_DATE   } ,
    { TC_VAR_TIME     , VAR_TIME   } ,
    { TC_VAR_DWORD    , VAR_DWORD  } ,
    { TC_VAR_OBJ      , VAR_OBJ    } ,
    { TC_VAR_QLONG    , VAR_QLONG  } ,
    { TC_VAR_BLOB     , VAR_BLOB   } ,
    { TC_VAR_DATETIME , VAR_DATETIME }
    };
  #define ANZKW (sizeof(ktv) / sizeof (kwToVt))
  _v->mType = 0xFF;
  for (int i = 0 ; i < ANZKW ; i++) {
    if (int (TCmp->scv.v.k_ident) == ktv[i].kw) {
      _v->mType = BYTE(ktv[i].vType) ;
      }
    }
  WIN_ASSERT (_v->mType != 0xFF);
  }
DLLExport void _export _SetVarSize ()
  {
  _v->VarSize = WORD(TCmp->scv.v.int_val) ;
  _v->VarID   = 0xFFFF;
  }
DLLExport void _export _SetVarId ()
  {
  _v->VarID   = WORD(TCmp->scv.v.int_val) ;
  _v->VarSize = 0xFFFF;
  }
DLLExport void _export _SetVarName ()
  {
  lstrcpy (_v->name,LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD));
  _v->structSize = sizeof(*_v) + lstrlen (_v->name);
  _v->Property = 0 ;
  _v->DLLDataOffs = 0 ;
  GlobalUnlock(TCmp->hPars0);
  }
DLLExport void _export _StoreField ()
  {
  _td = _td->AddVar (_v);
  }
/*----< Ende Feldfunktionen >--------*/

/*----< Schluesselfunktionen >--------*/
static char ActKeyName[128];
static DWORD ActAttrib;
static int ActKeyNmbr;
DLLExport void _export _SetActKeyName ()
  {
  lstrcpy (ActKeyName,LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD));
  GlobalUnlock(TCmp->hPars0);
  ActAttrib = 0;
  ActKeyNmbr ++;
  }
static BOOL AnswerIsYes;
DLLExport void _export _SetNo ()
  {
  AnswerIsYes = FALSE ;
  }
DLLExport void _export _SetYes ()
  {
  AnswerIsYes = TRUE ;
  }
DLLExport void _export _SetNull ()
  {
  if (AnswerIsYes)
    ActAttrib |= CLKD_NULL;
  else
    ActAttrib &= ~CLKD_NULL;
  }
DLLExport void _export _SetClustered ()
  {
  if (AnswerIsYes)
    ActAttrib |= CLKD_CLUSTERED;
  else
    ActAttrib &= ~CLKD_CLUSTERED;
  }
DLLExport void _export _SetModify ()
  {
  if (AnswerIsYes)
    ActAttrib |= CLKD_MODIFYABLE;
  else
    ActAttrib &= ~CLKD_MODIFYABLE;
  }
DLLExport void _export _SetUnique ()
  {
  if (AnswerIsYes)
    ActAttrib |= CLKD_UNIQUE;
  else
    ActAttrib &= ~CLKD_UNIQUE;
  }
DLLExport void _export _SetAutoinc ()
  {
  if (AnswerIsYes)
    ActAttrib |= CLKD_AUTOINC;
  else
    ActAttrib &= ~CLKD_AUTOINC;
  }
static BOOL SetCaseInsensitive;
DLLExport void _export _AddKey ()
  {
  _k->KeyNmbr = ActKeyNmbr;
  _k->Attribute = ActAttrib;
  lstrcpy (_k->name,ActKeyName);
  _k->structSize = sizeof(*_k) + lstrlen(ActKeyName);
  WORD dt;
  BOOL found;
  _k->VarID = _td->GetVarID (LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD),&dt,&found);
  LPVARDEF v = _td->GetVarDef(_k->VarID);
  if ((v->mType == VAR_STR) && (SetCaseInsensitive) && (ActKeyNmbr > 0))
    v->Property |= VPROP_CASEINSENSITIVE ;
  GlobalUnlock (TCmp->hPars0);
  if (!found) TCmp->wError = TBCMPERROR;
  else {
    _td->AddKey (_k);
    }
  }
/*----< Ende Schluesselfunktionen >--------*/

/*----< Speichern >--------*/
extern void TestTable (LPSTR Name,WORD Id,WORD Version);
WORD _Version;
DLLExport void _export _SetCaseInsensitive()
  {
  SetCaseInsensitive = TRUE ;
  }
DLLExport void _export _SetVersion ()
  {
  SetCaseInsensitive = FALSE ;
  _Version = WORD(TCmp->scv.v.int_val);
  }
BOOL isFirstCompile;
WORD FromVersion,ToVersion;
#define MAXTBSIZE 512
extern LPSTR IniFile();
extern void MarkTableForCheck (WORD TableID);
DLLExport void _export _StoreTable ()
  {
  _td->InitializeTableID (CSYSRECS,GLOBALTBIDMIN-1,_Version);
  MarkTableForCheck (_td->GetTableID());
  if (isFirstCompile) {
    WORD DBActVersion = ReadMaxVersion (0,_td->GetTableID());
    if (EntwicklungsUmgebung()) {
      WORD DBVersion = GetDBVersion (_td->GetName());
      if ((DBActVersion == _Version) && (DBVersion == DBINT(_Version))) {
        // Die aktuelle Tabellendefinition muss gerettet werden (auf DBMAXVERSION)
        SaveOldVersion (0,_td->GetTableID(),_td->GetName(),DBActVersion);
        }
      else if (DBVersion < _Version) {
        // Beim naechsten Programmstart muss ein _UPDATE durchgefuehrt werden
        GLOBALHANDLE hGres = GlobalAlloc (GHND,sizeof(WORD));
        WriteDataDict (5,"_UPDATE",0,0,0,0,hGres,sizeof(WORD));
        GlobalFree (hGres);
        }
      }
    if ((_Version >= 2) && (DBActVersion < WORD (_Version - 1))) {
      FromVersion = DBActVersion + 1 ;
      ToVersion = _Version ;

      // Testen, ob der Zugriff auch gehen wuerde!
      int Size;
      char errmsg[256];
      LPSTR Buffer = ReadBlock (&Size,int(FromVersion),GetFName(_FName),FALSE,errmsg,FALSE);
      if (Buffer == NULL) {
        WIN_ASSERT_TEXT (FALSE,"Cannot access old Versions / compilation aborted!");
        TCmp->wError = TBCMPERROR;
        }
      else
        FreeGlobMem (Buffer);
      }
    isFirstCompile = FALSE ;
    }
  if (TCmp->wError == 0) {
    DWORD rSize ;
    LPTABLEDEF nw = TableDef_NewPack (_td,&rSize);
    WriteDataDict (0,_td->GetName(),_td->GetTableID(),_td->GetVersion(),0,0,nw->GetHandle(),rSize);
    TestTable (_td->GetName(),_td->GetTableID(),_td->GetVersion());
    nw = InitializeTable (nw->GetHandle());

    char DLLName[64],SQLName[128];
    // Das SQL - File schreiben
    GetDLLForTable (DLLName,nw->GetName());
    ConnectToSQL (nw,GetDLLAdmin()->LoadDLL(DLLName),SQLName);
    FreeTableDef (nw);
    }
  }
DLLExport void _export _SetDLLString ()
  {
  _td->SetDLLDef (LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD),
                  lstrlen (LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD)) + 1);
  }

/*----< Ende Speichern >--------*/
DLLExport void _export _SetTableName ()
  {
  _td = GetEmptyTable(LPSTR(GlobalLock(TCmp->hPars0))+sizeof(WORD),_FName);
  GlobalUnlock(TCmp->hPars0);
  ActKeyNmbr = -1;
  }

/////////////////////////////////////////////////////////////////////////
//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
extern syntax_node t6,t12,t18,t24,k16,e4,n1;

#ifdef UEBERLEGT
syntax_node s3   = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node s2   = { &s3  , NULL , TRUE  ,INITERM(STRING,0) , _CallServer } ;
syntax_node _s1  = { &s2  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node s0   = { &_s1 , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetServerName } ;
#endif
syntax_node n5   = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node n4   = { &n1  , &n5  , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node n3   = { &n4  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetStdVarID } ;
syntax_node n2   = { &n3  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node n1   = { &n2  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _AddForeignVar } ;
syntax_node n0   = { &n1  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetForeinTable } ;

syntax_node e6   = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node e5   = { &e4  , &e6  , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node e4   = { &e5  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _AddExtVarID } ;
syntax_node e3   = { &e4  , NULL , TRUE  ,INITERM(KEYWORD,TC_BRACECLOSE) , NULL } ;
syntax_node e2   = { &e3  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetAccess } ;
syntax_node e1   = { &e2  , NULL , TRUE  ,INITERM(KEYWORD,TC_BRACEOPEN) , NULL } ;
syntax_node e0   = { &e1  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetForeinTable } ;

syntax_node _r1  = { &n0  , NULL , TRUE  ,INITERM(KEYWORD,TC_STANDARD) , _MarkStandard } ;
syntax_node r0   = { &e0  , &_r1 , TRUE  ,INITERM(KEYWORD,TC_EXTENDED) , _MarkExtended } ;

syntax_node yesno1 = { NULL  , NULL    , TRUE , INITERM(KEYWORD,TC_NO) , _SetNo } ;
syntax_node yesno  = { NULL  , &yesno1 , TRUE , INITERM(KEYWORD,TC_YES) , _SetYes } ;

syntax_node k18  = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node k17  = { &k16 , &k18 , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node k16  = { &k17 , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _AddKey } ;
syntax_node k15  = { &k16 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k14  = { &k15 , NULL , TRUE  ,INITERM(KEYWORD,TC_BRACECLOSE) , NULL } ;
syntax_node k22  = { &k14 , NULL , FALSE ,&yesno , _SetClustered } ;
syntax_node k21  = { &k22 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k20  = { &k21 , NULL , TRUE  ,INITERM(KEYWORD,TC_CLUSTERED) , NULL } ;
syntax_node k19  = { &k20 , &k14 , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node k13  = { &k19 , NULL , FALSE ,&yesno , _SetNull } ;
syntax_node k12  = { &k13 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k11  = { &k12 , NULL , TRUE  ,INITERM(KEYWORD,TC_NULL) , NULL } ;
syntax_node k10a = { &k11 , NULL , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node k10  = { &k10a, NULL , FALSE ,&yesno , _SetModify } ;
syntax_node k9   = { &k10 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k8   = { &k9  , NULL , TRUE  ,INITERM(KEYWORD,TC_MODIFY) , NULL } ;
syntax_node k7a  = { &k8  , NULL , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node k7   = { &k7a , NULL , FALSE ,&yesno , _SetUnique } ;
syntax_node k6   = { &k7  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k5   = { &k6  , NULL , TRUE  ,INITERM(KEYWORD,TC_UNIQUE) , NULL } ;
syntax_node k4a  = { &k5  , NULL , TRUE  ,INITERM(KEYWORD,TC_COLON) , NULL } ;
syntax_node k4   = { &k4a , NULL , FALSE ,&yesno , _SetAutoinc } ;
syntax_node k3   = { &k4  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node k2   = { &k3  , NULL , TRUE  ,INITERM(KEYWORD,TC_AUTOINC) , NULL } ;
syntax_node k1   = { &k2  , NULL , TRUE  ,INITERM(KEYWORD,TC_BRACEOPEN) , NULL } ;
syntax_node k0   = { &k1  , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetActKeyName } ;

syntax_node i2   = { NULL , NULL , TRUE  ,INITERM(T_INTEGER,0) , _SetVarId } ;
syntax_node i1   = { &i2  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node i0   = { &i1  , NULL , TRUE  ,INITERM(KEYWORD,TC_ID) , NULL } ;

syntax_node d2   = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_ARRBRACECLOSE) , NULL } ;
syntax_node d1   = { &d2  , NULL , TRUE  ,INITERM(T_INTEGER,0) , _SetVarSize } ;
syntax_node d0   = { &d1  , NULL , TRUE  ,INITERM(KEYWORD,TC_ARRBRACEOPEN) , NULL } ;

syntax_node y14  = { NULL  , NULL , TRUE  ,INITERM(KEYWORD,TC_VAR_DATETIME ) , _SetVarType } ;
syntax_node y13  = { NULL  , &y14 , TRUE  ,INITERM(KEYWORD,TC_VAR_BLOB  ) , _SetVarType } ;
syntax_node y12  = { NULL  , &y13 , TRUE  ,INITERM(KEYWORD,TC_VAR_QLONG ) , _SetVarType } ;
syntax_node y11  = { NULL  , &y12 , TRUE  ,INITERM(KEYWORD,TC_VAR_LONG  ) , _SetVarType } ;
syntax_node y10  = { NULL  , &y11 , TRUE  ,INITERM(KEYWORD,TC_VAR_DEC   ) , _SetVarType } ;
syntax_node y9   = { NULL  , &y10 , TRUE  ,INITERM(KEYWORD,TC_VAR_STR   ) , _SetVarType } ;
syntax_node y8   = { NULL  , &y9  , TRUE  ,INITERM(KEYWORD,TC_VAR_POINT ) , _SetVarType } ;
syntax_node y7   = { NULL  , &y8  , TRUE  ,INITERM(KEYWORD,TC_VAR_CONT  ) , _SetVarType } ;
syntax_node y6   = { NULL  , &y7  , TRUE  ,INITERM(KEYWORD,TC_VAR_STRARR) , _SetVarType } ;
syntax_node y5   = { NULL  , &y6  , TRUE  ,INITERM(KEYWORD,TC_VAR_FLAG  ) , _SetVarType } ;
syntax_node y4   = { NULL  , &y5  , TRUE  ,INITERM(KEYWORD,TC_VAR_SCALE ) , _SetVarType } ;
syntax_node y3   = { NULL  , &y4  , TRUE  ,INITERM(KEYWORD,TC_VAR_DATE  ) , _SetVarType } ;
syntax_node y2   = { NULL  , &y3  , TRUE  ,INITERM(KEYWORD,TC_VAR_TIME  ) , _SetVarType } ;
syntax_node y1   = { NULL  , &y2  , TRUE  ,INITERM(KEYWORD,TC_VAR_DWORD ) , _SetVarType } ;
syntax_node y0   = { NULL  , &y1  , TRUE  ,INITERM(KEYWORD,TC_VAR_OBJ   ) , _SetVarType } ;

syntax_node f6  = { NULL  , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node f5  = { &f6   , NULL , TRUE  ,INITERM(KEYWORD,TC_NULL) , _SetNotNull } ;
syntax_node f4  = { &f5   , &f6  , TRUE  ,INITERM(KEYWORD,TC_NOT) , NULL } ;
syntax_node f3  = { &f4   , NULL , FALSE ,&i0 , NULL } ;
syntax_node f2  = { &f4   , &f3  , FALSE ,&d0 , NULL } ;
syntax_node f1  = { &f2   , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetVarName } ;
syntax_node f0  = { &f1   , NULL , FALSE ,&y0 , NULL } ;

syntax_node t27 = { NULL , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACECLOSE) , NULL } ;
#ifdef UEBERLEGT
syntax_node t26 = { &t27 , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node t25 = { &t24 , NULL , FALSE ,&s0 , _StoreServer } ;
syntax_node t24 = { &t26 , &t25 , TRUE  ,INITERM(KEYWORD,TC_CURBRACECLOSE) , NULL } ;
syntax_node t23 = { &t24 , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACEOPEN) , NULL } ;
syntax_node t22 = { &t23 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t21 = { &t22 , NULL , TRUE  ,INITERM(KEYWORD,TC_SERVER) , NULL } ;
#endif
syntax_node t20 = { &t27 , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , _StoreTable } ;
syntax_node t19 = { &t18 , NULL , FALSE ,&r0 , _StoreForeign } ;
syntax_node t18 = { &t20 , &t19 , TRUE  ,INITERM(KEYWORD,TC_CURBRACECLOSE) , NULL } ;
syntax_node t17 = { &t18 , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACEOPEN) , NULL } ;
syntax_node t16 = { &t17 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t15 = { &t16 , NULL , TRUE  ,INITERM(KEYWORD,TC_FOREIGNKEY) , NULL } ;
syntax_node t14 = { &t15 , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node t13 = { &t12 , NULL , FALSE ,&k0 , NULL } ;
syntax_node t12 = { &t14 , &t13 , TRUE  ,INITERM(KEYWORD,TC_CURBRACECLOSE) , NULL } ;
syntax_node t11 = { &t12 , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACEOPEN) , NULL } ;
syntax_node t10 = { &t11 , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t9  = { &t10 , NULL , TRUE  ,INITERM(KEYWORD,TC_KEY) , NULL } ;
syntax_node t8  = { &t9  , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node t7  = { &t6  , NULL , FALSE ,&f0 , _StoreField } ;
syntax_node t6  = { &t8  , &t7  , TRUE  ,INITERM(KEYWORD,TC_CURBRACECLOSE) , NULL } ;
syntax_node t5  = { &t6  , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACEOPEN) , NULL } ;
syntax_node t4  = { &t5  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t3  = { &t4  , NULL , TRUE  ,INITERM(KEYWORD,TC_FIELDS) , NULL } ;
syntax_node t2d = { &t3  , NULL , TRUE  ,INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node t2c = { &t2d , NULL , TRUE  ,INITERM(STRING,0) , _SetDLLString } ;
syntax_node t2b = { &t2c , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t2a = { &t2b , &t3  , TRUE  ,INITERM(KEYWORD,TC_PROPERTY) , NULL } ;
syntax_node t2  = { &t2a  , NULL , TRUE  ,INITERM(KEYWORD,TC_CURBRACEOPEN) , NULL } ;
syntax_node _t1 = { &t2  , NULL , TRUE  ,INITERM(KEYWORD,TC_EQUAL) , NULL } ;
syntax_node t0  = { &_t1 , NULL , TRUE  ,INITERM(UNKNOWNIDENT,0) , _SetTableName } ;
syntax_node t0d = { &t0  , NULL , TRUE , INITERM(KEYWORD,TC_TABLE) , NULL } ;
syntax_node t0c = { &t0d , NULL , TRUE , INITERM(KEYWORD,TC_SEMICOLON) , NULL } ;
syntax_node t0b = { &t0c , &t0d , TRUE , INITERM(KEYWORD,TC_CASEINSENSITIVE) , _SetCaseInsensitive } ;
syntax_node t0a = { &t0b , NULL , TRUE , INITERM(T_INTEGER,0) , _SetVersion } ;
syntax_node tbsyntax = { &t0a , NULL , TRUE , INITERM(KEYWORD,TC_VERSION) , NULL } ;

BOOL GenTbScript (HWND hWnd,LPSTR fname)
  {
  TbCompiler FAR *r = new TbCompiler ();
  TCmp = r;
  hTbWnd = hWnd;
  _NameZuSchreiben = fname ;
  char nambuffer[256];
  lstrcpy (nambuffer,fname);
  _FName = nambuffer;
  _td = NULL;
  isFirstCompile = TRUE ;
  FromVersion = ToVersion = 0 ;
  r->DoParse (fname,&tbsyntax,NULL);
  if (_td != NULL) {
    _td->Clear ();
    FreeTableDef (_td);
    }
  WORD error = r->wError ;
  delete r;

  if (GetBuffer != NULL) {
    FreeGlobMem (GetBuffer);
    GetBuffer = NULL;
    }

  if ((FromVersion < ToVersion) && (error == 0)) {
    for (WORD Version = FromVersion ; Version < ToVersion ; Version ++ ) {
      int Size;
      char errmsg[256];
      LPSTR Buffer = ReadBlock (&Size,int(Version),GetFName(fname),FALSE,errmsg,FALSE);
      if (Buffer != NULL) {
        r = new TBbCompiler ();
        TCmp = r;
        _td = NULL;
        _FName = nambuffer;
        r->DoParse (Buffer,&tbsyntax,NULL);
        if (_td != NULL) {
          _td->Clear ();
          FreeTableDef (_td);
          }
        delete r;
        FreeGlobMem (Buffer);
        }
      }
    }
  return (error == 0) ;
  }

