////////////////////////////////////////////////////////////////////////////
//  Generieren der globalen Tabellen
////////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/gengtbl.cpv   1.21   05 Oct 1998 11:26:24   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/gengtbl.cpv  $
// 
//    Rev 1.21   05 Oct 1998 11:26:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.20   17 Aug 1998 17:58:52   Hannes
// Syntax - Korrigieren
// 
//    Rev 1.19   04 Aug 1998 17:49:06   Hannes
// Timestamp
// 
//    Rev 1.18   28 Aug 1997 14:28:18   Gerhold
// 32-Bit-Umstellung
// 
//    Rev 1.17   11 Jul 1997 11:27:52   Hannes
// 
//    Rev 1.16   29 Apr 1997 08:07:20   Hannes
// Doppeltes Generieren der globalen Tabellen raus
// 
//    Rev 1.15   13 Mar 1997 19:04:10   Hannes
// Blobs in GDD's
// 
//    Rev 1.14   19 Feb 1997 12:13:06   Hannes
// Ableitungen von Strukturen
// 
//    Rev 1.13   26 Nov 1996 08:10:38   HANNES
// Automatischer Update
// 
//    Rev 1.12   08 Nov 1996 13:30:28   HANNES
// QLong,Replikator
// 
//    Rev 1.11   12 Sep 1996 23:13:22   HANNES
// Indexname fuer Segmentierte Hash - Indizess auf globale Structs
// 
//    Rev 1.10   17 Jun 1996 16:53:22   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.9   04 Feb 1996 21:49:14   HANNES
// 
//    Rev 1.8   04 Feb 1996 17:00:36   HANNES
// Protyp LogMsg
// 
//    Rev 1.7   02 Feb 1996 10:50:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   09 Jun 1995 00:28:42   HANNES
// static, indexed eingebaut
// 
//    Rev 1.5   15 May 1995 08:29:54   HANNES
// structs direkt im script definieren
// 
//    Rev 1.4   26 Apr 1995 15:26:32   HANNES
// 
//    Rev 1.3   02 Apr 1995 13:33:28   HANNES
//  
// 
//    Rev 1.2   31 Mar 1995 18:23:38   HANNES
//  
// 
//    Rev 1.1   24 Feb 1995 11:00:38   HANNES
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
#define MODULENUM 21
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

extern HINSTANCE MyInstance;
static HWND hGWnd;
class GLCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  GLCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI GLCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,RSKW_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    char name[150];
    WORD j;
    AnalyseAlias (h,instring,name,i,&j);
    h->SetData (name,&j,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

static WORD GVType;
static BYTE GVProp;
DLLExport BOOL _export WINAPI GLCompiler::TestError ()
  {
  if (wError > RSCMPERROR_BASE) {
    char pattern[64];
    char errstr[64];
    LoadString (MyInstance,RSCMPERROR_BASE,pattern,sizeof(pattern));
    LoadString (MyInstance,wError,errstr,sizeof(errstr));
    char outtxt[256];
    wsprintf (outtxt,pattern,fmname,LineNr,column,LPSTR(errstr));
    if (GetCommandLineFlag())
      LogMsg (outtxt);
    else {
      HWND hWnd = NULL;
      if (hGWnd) hWnd = hWnd;
      else       hWnd = GetActiveWindow ();
      MessageBox (hGWnd,outtxt,"Definitionsfehler",MB_OK | MB_TASKMODAL);
      }
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static GLCompiler FAR *GLCmp;
static LPSTR _GName;
static LPTABLEDEF gTable;
DLLExport void _export SetGType ()
  {
  static struct kwToVt { int kw ; WORD vType ; } ktv [] = {
    { KWVARLONG    , VAR_LONG    } ,
    { KWVARDEC     , VAR_DEC     } ,
    { KWVARSTR     , VAR_STR     } ,
    { KWVARPOINT   , VAR_POINT   } ,
    { KWVARCONT    , VAR_CONT    } ,
    { KWVARSTRARR  , VAR_STRARR  } ,
    { KWVARFLAG    , VAR_FLAG    } ,
    { KWVARSCALE   , VAR_SCALE   } ,
    { KWVARDATE    , VAR_DATE    } ,
    { KWVARTIME    , VAR_TIME    } ,
    { KWVARDWORD   , VAR_LONG    } ,
    { KWVAROBJ     , VAR_OBJ     } ,
    { KWVARQLONG   , VAR_QLONG   } ,
    { KWVARBLOB    , VAR_BLOB    } ,
    { KWVARDATETIME , VAR_DATETIME }
    };
  #define ANZKW (sizeof(ktv) / sizeof (kwToVt))
  GVType = 0xFFFF;
  for (int i = 0 ; i < ANZKW ; i++) {
    if (int (GLCmp->scv.v.k_ident) == ktv[i].kw) {
      GVType = ktv[i].vType ;
      }
    }
  }
DLLExport void _export SetModifyNull ()
  {
  GVProp = VPROP_DYNAMIC;
  }
static char _IndexNames[7][64];
static int _AnzSegIndex;
DLLExport void _export ResetIndexNames ()
  {
  _AnzSegIndex = 0 ;
  }
DLLExport void _export TestIndexName ()
  {
  LPSTR Name = LPSTR(GlobalLock (GLCmp->hPars0)) + sizeof(WORD);
  for (int i = 0 ; i < _AnzSegIndex ; i++) {
    if (lstrcmp (_IndexNames[i],Name) == 0) break ;
    }
  if ((i == _AnzSegIndex) && (i < 7)) {
    lstrcpy (_IndexNames[i],Name);
    }
  if (i < 7) {
    GVProp = GVProp | BYTE((i + 1) << 5) ;
    }
  GlobalUnlock (GLCmp->hPars0);
  }
DLLExport void _export SetModifyIndex ()
  {
  GVProp = VPROP_INDEXED ;
  }
DLLExport void _export SetModifyLIndex ()
  {
  GVProp = VPROP_LINDEXED ;
  }
DLLExport void _export SetModifyStatic ()
  {
  GVProp = VPROP_STATIC;
  }
DLLExport void _export AddGVar ()
  {
  LPSTR Name = LPSTR(GlobalLock (GLCmp->hPars0)) + sizeof(WORD);
  int size = sizeof(VarDef) + lstrlen(Name) + sizeof(InternVarCoding);
  LPVARDEF v = LPVARDEF (GetGlobMem (size));
  v->structSize = size ;
  v->mType = BYTE(GVType);
  v->Property = GVProp;
  v->VarSize = 0xFFFF;
  v->VarID = 0xFFFF;
  v->DLLDataOffs = sizeof(VarDef) + lstrlen(Name);
  lstrcpy (v->name,Name);
  InternVarCoding FAR *i = (InternVarCoding FAR *) (LPSTR(v) + v->DLLDataOffs);
  i->mType = GVType;
  i->IsPrimary = FALSE ;
  gTable = gTable->AddVar (v);
  FreeGlobMem (v);
  GlobalUnlock (GLCmp->hPars0);
  }
static char actTableName[64];
static LPSTR actTablePrefix;
static WORD ActTableID;
static WORD ActParentID,ActParentVersion;
DLLExport void _export CreateGTable ()
  {
  LPSTR tbname = LPSTR(GlobalLock(GLCmp->hPars0)) + sizeof(WORD);
  *actTableName = '\0';
  if (actTablePrefix)
    lstrcpy (actTableName,actTablePrefix);
  lstrcat (actTableName,tbname);
  ActParentID = ActParentVersion = 0;
  gTable = GetEmptyTable(actTableName,_GName);
  GlobalUnlock(GLCmp->hPars0);
  }
DLLExport void _export GetParentID ()
  {
  LPSTR tbname = LPSTR(GlobalLock (GLCmp->hPars0)) + sizeof(WORD) ;
  BOOL found;
  ActParentID = GetTableAdmin()->GetTableID (NULL,tbname,&found,&ActParentVersion);
  if (found)
    gTable->SetParent (ActParentID,ActParentVersion);
  else
    GLCmp->wError = RSCMPERROR_BASE;
  GlobalUnlock(GLCmp->hPars0);
  }
extern void TestGTable (LPSTR Caption,WORD Id,WORD ParentID,WORD ParentVersion);
extern void MarkTableForCheck (WORD TableID);
DLLExport void _export StoreGTable ()
  {
  gTable->InitializeTableID (GLOBALTBIDMIN,GLOBALTBIDMAX,0);
  MarkTableForCheck (gTable->GetTableID());
  DWORD rSize;
  int itdata = 0;
  gTable->SetDLLDef (&itdata,sizeof(itdata));
  LPTABLEDEF nw = TableDef_NewPack (gTable,&rSize);
  WriteDataDict (0,gTable->GetName(),gTable->GetTableID(),gTable->GetVersion(),gTable->GetParentID(),gTable->GetParentVersion(),nw->GetHandle(),rSize);
  TestGTable (gTable->GetName(),gTable->GetTableID(),gTable->GetParentID(),gTable->GetParentVersion());
  FreeTableDef (nw);
  ActTableID = gTable->GetTableID();
  gTable->Clear();
  FreeTableDef (gTable);
  }

/////////////////////////////////////////////////////////////////////////
//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
extern syntax_node gl4a,gsyntax;
syntax_node gtype13   = { NULL , NULL     , TRUE , INITERM(KEYWORD,KWVARBLOB ) , SetGType } ;
syntax_node gtype12   = { NULL , &gtype13 , TRUE , INITERM(KEYWORD,KWVARDATETIME ) , SetGType } ;
syntax_node gtype11   = { NULL , &gtype12 , TRUE , INITERM(KEYWORD,KWVARQLONG ) , SetGType } ;
syntax_node gtype10   = { NULL , &gtype11 , TRUE , INITERM(KEYWORD,KWVARLONG  ) , SetGType } ;
syntax_node gtype9    = { NULL , &gtype10 , TRUE , INITERM(KEYWORD,KWVARDEC   ) , SetGType } ;
syntax_node gtype8    = { NULL , &gtype9  , TRUE , INITERM(KEYWORD,KWVARSTR   ) , SetGType } ;
syntax_node gtype7    = { NULL , &gtype8  , TRUE , INITERM(KEYWORD,KWVARPOINT ) , SetGType } ;
syntax_node gtype6    = { NULL , &gtype7  , TRUE , INITERM(KEYWORD,KWVARCONT  ) , SetGType } ;
syntax_node gtype5    = { NULL , &gtype6  , TRUE , INITERM(KEYWORD,KWVARSTRARR) , SetGType } ;
syntax_node gtype4    = { NULL , &gtype5  , TRUE , INITERM(KEYWORD,KWVARFLAG  ) , SetGType } ;
syntax_node gtype3    = { NULL , &gtype4  , TRUE , INITERM(KEYWORD,KWVARSCALE ) , SetGType } ;
syntax_node gtype2a   = { NULL , &gtype3  , TRUE , INITERM(KEYWORD,KWVARTIME  ) , SetGType } ;
syntax_node gtype2    = { NULL , &gtype2a , TRUE , INITERM(KEYWORD,KWVARDATE  ) , SetGType } ;
syntax_node gtype1    = { NULL , &gtype2  , TRUE , INITERM(KEYWORD,KWVARDWORD ) , SetGType } ;
syntax_node gtype     = { NULL , &gtype1  , TRUE , INITERM(KEYWORD,KWVAROBJ   ) , SetGType } ;

syntax_node gm4     = { NULL  , NULL , TRUE  , INITERM(FREECHAR,0) , SetModifyNull } ;
syntax_node gm3     = { NULL  , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node gm2     = { NULL  , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , TestIndexName } ;
syntax_node gm1     = { &gm2  , &gm3 , TRUE  , INITERM(KEYWORD,KWINDEXNAME) , NULL } ;
syntax_node gm0a    = { &gm1  , &gm4 , TRUE  , INITERM(KEYWORD,KWLINDEX) , SetModifyLIndex } ;
syntax_node gm0     = { &gm1  , &gm0a , TRUE  , INITERM(KEYWORD,KWINDEX) , SetModifyIndex } ;
syntax_node gmodify = { NULL  , &gm0 , TRUE  , INITERM(KEYWORD,KWSTATIC) , SetModifyStatic } ;

extern syntax_node gl5;
syntax_node ptb1    = { NULL , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , GetParentID } ;
syntax_node ptable  = { &ptb1 , NULL , TRUE , INITERM(KEYWORD,KWDOPPELPUNKT) , NULL } ;

syntax_node gl8     = { NULL  , NULL , TRUE  , INITERM(KEYWORD,KWSEMICOLON)      , StoreGTable } ;
syntax_node gl7     = { &gl8  , &gl4a , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , NULL } ;
syntax_node gl6a    = { &gl5  , NULL , TRUE  , INITERM(KEYWORD,KWCOLON)          , NULL } ;
syntax_node gl6     = { &gl7  , &gl6a , TRUE  , INITERM(KEYWORD,KWSEMICOLON)     , NULL } ;
syntax_node gl5     = { &gl6  , NULL , TRUE  , INITERM(UNKNOWNIDENT,0)           , AddGVar } ;
syntax_node gl4     = { &gl5  , NULL , FALSE , &gtype                            , NULL } ;
syntax_node gl4a    = { &gl4  , NULL , FALSE , &gmodify                          , NULL } ;
syntax_node gl3     = { &gl4a , NULL , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN)   , ResetIndexNames } ;
syntax_node gl2a    = { &gl3  , &gl3 , FALSE , &ptable                           , NULL } ;
syntax_node gl2     = { &gl2a , NULL , TRUE  , INITERM(UNKNOWNIDENT,0)           , CreateGTable } ;
syntax_node gtable  = { &gl2  , NULL , TRUE  , INITERM(KEYWORD,KWGLOBAL)         , NULL } ;

syntax_node gsyntax_end = { NULL         , &gsyntax  , TRUE  , INITERM(KEYWORD,KWENDRES) , NULL } ;
syntax_node gsyntax     = { &gsyntax_end , &gsyntax_end , FALSE , &gtable              , NULL } ;

BOOL GenGScript (HWND hWnd,LPSTR fname)
  {
  actTablePrefix = NULL;
  GLCompiler FAR *r = new GLCompiler ();
  GLCmp = r;
  hGWnd = hWnd;
  _GName = fname;
  r->DoParse (fname,&gsyntax,NULL);
  WORD error = r->wError ;
  delete r;
  return (error == 0) ;
  }

class GLSCompiler : public GLCompiler {
  virtual DLLExport void _export FAR PASCAL InstallBuffer(LPVOID d);
  };

void GLSCompiler::InstallBuffer(LPVOID d)
  {
  buffer_start = LPSTR (d) ;
  actptr = buffer_start;
  }

DLLExport BOOL _export FAR PASCAL GenerateStruct (LPSTR fName,LPSTR Buffer,LPSTR prefix)
  {
  actTablePrefix = prefix;
  GLSCompiler FAR *r = new GLSCompiler ();
  GLCmp = r;
  hGWnd = 0;
  _GName = fName;
  r->DoParse (Buffer,&gtable,NULL);
  WORD error = r->wError ;
  delete r;
  return (error == 0);
  }
