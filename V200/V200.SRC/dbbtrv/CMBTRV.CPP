///////////////////////////////////////////////////////////
//  Compiler fuer das Datadictionary
///////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/dbbtrv/rev/cmbtrv.cpv   1.31   04 Mar 1999 17:57:32   HANNES  $
// $Log:   P:/marille/clinicum/dbbtrv/rev/cmbtrv.cpv  $
// 
//    Rev 1.31   04 Mar 1999 17:57:32   HANNES
// 1.) AUTOINC nur im eigenen Key als AUTOINC sonst als integer.
// 
//    Rev 1.30   13 Oct 1998 13:04:00   Gerhold
// HINSTANCE hLibInst wegen VC6
// 
//    Rev 1.29   10 Aug 1998 17:03:40   Hannes
// Umstellen des Timestamps auf UNSIGNED
// 
//    Rev 1.28   04 Aug 1998 17:55:32   Hannes
// Timestamp
// 
//    Rev 1.27   30 Apr 1997 08:55:56   Hannes
// 
//    Rev 1.26   23 Dec 1996 14:36:54   MARTIN
// _SetBit auch bei BlobIsPushed
// 
//    Rev 1.25   03 Dec 1996 21:07:16   HANNES
// Blocked - Variablen muessen nicht hinten vorkommen
// 
//    Rev 1.24   26 Nov 1996 08:00:10   HANNES
// Automatischer Update
// 
//    Rev 1.23   08 Nov 1996 13:26:36   HANNES
// QLong, Replikator
// 
//    Rev 1.22   05 Jul 1996 08:04:50   GERHOLD
// GlobalRealloc funktionierte in 32 Bit nicht => anders geloest
// 
//    Rev 1.21   17 Jun 1996 15:38:24   HANNES
// Einbau von BLOBS
// 
//    Rev 1.20   04 Feb 1996 17:27:08   HANNES
// 
//    Rev 1.19   02 Feb 1996 10:42:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.18   20 Sep 1995 14:34:36   MARTIN
// ddt-Kompiler zum laufen gebracht
// 
//    Rev 1.17   26 Apr 1995 15:33:12   HANNES
// 
//    Rev 1.16   20 Mar 1995 12:10:18   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.15   16 Feb 1995 12:46:22   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.14   29 Jan 1995 11:45:10   HANNES
// 
//    Rev 1.13   24 Jan 1995 10:58:54   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.12   09 Dec 1994 19:43:48   HANNES
// 
//    Rev 1.11   08 Dec 1994 22:04:42   HANNES
// DivLong,on_notfiltersatisfy
// 
//    Rev 1.10   08 Nov 1994 12:42:38   HANNES
// Parameter als Resultat
// 
//    Rev 1.9   07 Nov 1994 11:42:24   HANNES
// ZStrings mit Alternate collating sequenz vergleichen
// 
//    Rev 1.8   31 Oct 1994 10:36:20   hannes
// Den Typ unsigned als interger bekanntgegeben (wegen nwsql)
// 
//    Rev 1.7   19 Oct 1994 22:30:38   hannes
// Schluesselwort Continue
// 
//    Rev 1.6   24 Aug 1994 19:40:58   HANNES
// Fehler im Erzeugen der Schluesseldefinition
// 
//    Rev 1.5   17 Aug 1994 11:30:16   HANNES
// Fehler in PutKeyDesc... Freigegebene Zeiger sollten nicht mehr verwendet werd
// werden
// 
//    Rev 1.4   05 Aug 1994 17:08:06   HANNES
// 
//    Rev 1.3   17 Jul 1994 14:38:06   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.2   13 Jul 1994 21:22:34   HANNES
// 
//    Rev 1.1   04 Jul 1994 14:57:20   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:43:18   HANNES
// Neuuebernahme clinicum
// 
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "tbkw.h"
#include "tbbtrv.hpp"
#include "tbfnc.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 78
#include "winass.hpp"

/*---------------------------------------------------------------*/
/*  Klasse TableCompiler: Kompilieren von Tabellenbeschreibungen */
/*---------------------------------------------------------------*/
class TableCompiler : public compiler {
 public :
  virtual DLLExport BOOL _export AllowOperator()
    { return (*actptr != '-') ; }
  
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  LPSTR GetActPtr()
    { return actptr ; }

  TableCompiler () : compiler (NULL) { }
  };
typedef TableCompiler FAR *LPTABLECOMPILER;

extern HINSTANCE hLibInst;
DLLExport void _export WINAPI TableCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (hLibInst,TBKW_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

DLLExport BOOL _export WINAPI TableCompiler::TestError (void)
  {
  if (wError > TBCMPERROR_BASE) {
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

/*-----------------------------------------------------------*/
/*  Codegenerierung                                          */
/*-----------------------------------------------------------*/
/*-----< Hilfsfunktionen in der Klasse TbBtrv >---------*/
inline void TbBtrv::SetFileRef (LPSTR Name) 
  { FileRef.ptr = LPSTR(GetGlobMem(lstrlen(Name)+1)) ; lstrcpy (LPSTR(FileRef.ptr),Name) ; }
void TbBtrv::PushVar (LPSTR Name,WORD DataType,WORD VarOffset,WORD VarLen,WORD Dimension)
  {
  WORD eSize = sizeof(VBtrv) + lstrlen(Name);
  LPVARTBL h;
  if (VartblRef.ptr != NULL) {
    h = GetVarRef (TRUE);
    GLOBALHANDLE hGmem = h->g.hGres;
    WORD gSize = h->gSize;
    GlobalUnlock (hGmem);
    hGmem = GlobalReAlloc (hGmem,gSize+eSize,GMEM_MOVEABLE);
    h = LPVARTBL (GlobalLock (hGmem));
    h->g.hGres = hGmem;
    }
  else {
    GLOBALHANDLE hGmem = GlobalAlloc (GMEM_MOVEABLE,sizeof(Vartbl) - sizeof(VBtrv) + eSize);
    h = LPVARTBL (GlobalLock (hGmem));
    h->g.hGres = hGmem;
    h->gSize = sizeof(Vartbl) - sizeof(VBtrv);
    }
  SetVarRef (h);
  LPVBTRV v = LPVBTRV(LPSTR(h)+h->gSize);
  v->EntryLen  = eSize;
  v->DataType  = DataType;
  v->VarOffset = VarOffset;
  v->VarLen    = VarLen;
  v->Dimension = Dimension;
  lstrcpy (v->Name,Name);
  h->gSize += eSize;
  }

VBtrv FAR *VBtrv::Next (WORD gSize,LPVOID base)
  {
  WORD actOffset = LPSTR(this) - LPSTR(base);
  actOffset += EntryLen ;
  if (actOffset >= gSize) return NULL;
  else                    return LPVBTRV(LPSTR(base)+actOffset);
  }

LPVBTRV TbBtrv::GetVar (LPSTR Name,BOOL forCompiler)
  {
  LPVARTBL h = GetVarRef(forCompiler);
  if (h != NULL) {
    LPVBTRV x = &h->v[0];
    for ( ; x != NULL ; x = x->Next (h->gSize,h)) {
      if (lstrcmp (x->Name,Name) == 0) return x ;
      }
    }
  return NULL;
  }

LPVBTRV TbBtrv::GetKeyVar (LPSTR Name,WORD KeyNmbr,BOOL forCompiler)
  {
  LPKEYDEF Key = GetKey (KeyNmbr,forCompiler);
  if (Key == NULL) return NULL;
  LPVARTBL h = LPVARTBL (Key->Name + lstrlen(Key->Name) + 1) ;
  if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
    LPVBTRV x = &h->v[0];
    for ( ; x != NULL ; x = x->Next (h->gSize,h)) {
      if (lstrcmp (x->Name,Name) == 0) return x ;
      }
    }
  return NULL;
  }

void TbBtrv::InitialiseDesc ()
  {
  DescRef.ptr = GetGlobMem (sizeof(RecDesc) - sizeof(KeyDesc));
  LPRECDESC h = GetDescRef (TRUE);
  h->StructSize = GetBlockSize(h);
  h->flags = FA_ALLOC_TEN;
  }

void TbBtrv::AddKeySegment ()
  {
  WORD nwSize = GetBlockSize (DescRef.ptr) + sizeof(KeyDesc);
  LPRECDESC h = LPRECDESC(GetGlobMem (nwSize));
  lmemcpy (h,DescRef.ptr,GetBlockSize (DescRef.ptr));
  h->StructSize = nwSize;
  h->AnzKeySegs ++ ;
  FreeGlobMem (DescRef.ptr);
  DescRef.ptr = h;
  }

static unsigned char altseq [ALTSIZE] = {
/* 0 - 8     */    172,'C','L','I','N','I','C','U','M',
/* 9 - 72    */    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
/* 73 - 96   */    '@','A','C','D','E','F','H','I','J','K','M','N','O','P','Q','S','U','V','W','X','Z','[',']','^',
/* 97 - 128  */    '_','`','a','b','c','d','e','f','g','A','C','D','E','F','H','I','J','K','M','N','O','P','Q','S','U','V','W','X','Z','[',']','^',
/* 129 - 240 */    '_','`','a','{','|','}','~','','€','','‚','ƒ','„','…','†','‡','ˆ','‰','Š','‹','Œ','','Ž','','','‘','’','“','”','•','–','—','˜','™','š','›','œ','','ž','Ÿ',' ','¡','¢','£','¤','¥','¦','§','¨','©','ª','«','¬','­','®','¯','°','±','²','³','´','µ','¶','·','¸','¹','º','»','¼','½','¾','¿','B','B','B','B','B','B','Æ','Ç','G','G','G','G','L','L','L','L','Ð','Ñ','R','R','R','R','R','×','Ø','\\','\\','\\','\\','Ý','Þ','Y','B','B','B','B','B','B','æ','ç',
/* 241 - 255 */    'G','G','G','G','L','L','L','L','ð','ñ','R','R','R','R','R',
/* 256 - 264 */    247,248,92,92,92,92,253,254,255
#ifdef MIT512
,
/* 265 - 512 */    32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
#endif
  };
WORD TbBtrv::LoadAltSeq (LPSTR Name)
  {
#ifdef FROM_FILE
  OFSTRUCT Of;
  HFILE fi = OpenFile (Name,&Of,OF_READ);
  if (fi >= 0) {
    WORD nwSize = GetBlockSize (DescRef.ptr) + ALTSIZE;
    LPRECDESC h = LPRECDESC(GetGlobMem (nwSize));
    lmemcpy (h,DescRef.ptr,GetBlockSize (DescRef.ptr));
    FreeGlobMem (DescRef.ptr);
    DescRef.ptr = h;
    WORD res;
    if (_lread (fi,LPSTR(h)+h->StructSize,ALTSIZE) != ALTSIZE) res = ERROR_ALTFILECORRUPTED;
    else                                                res = 0;
    _lclose (fi);
    h->StructSize = nwSize;
    return res;
    }
  else
    return ERROR_ALTFILENOTFOUND;
#else
  WORD nwSize = GetBlockSize (DescRef.ptr) + ALTSIZE;
  LPRECDESC h = LPRECDESC(GetGlobMem (nwSize));
  lmemcpy (h,DescRef.ptr,GetBlockSize (DescRef.ptr));
  FreeGlobMem (DescRef.ptr);
  DescRef.ptr = h;
  lmemcpy (LPSTR(h)+h->StructSize,altseq,ALTSIZE);
  h->StructSize = nwSize;
#endif
  return 0 ;
  }

LPBTRVTABLE cTable;
LPTABLECOMPILER cTbComp;

/*-----< Offsetverwaltung fuer die Felddefinition >---------------*/
#define MAXLEVEL  10
#define MAXUNION  10
struct FAR OffsetDefinition {
  int OffsLevel;
  int UnionNum;
  WORD Offs[MAXLEVEL][MAXUNION];
  int LastUN[MAXLEVEL];

  void Reset ()
    { OffsLevel = 0 ; UnionNum = 0 ; Offs[0][0] = 0 ; }
  void AddLen (WORD Len)
    { Offs[OffsLevel][UnionNum] += Len ; }
  void PopLevel ();
  void PushLevel ();
  void NextUnion ()
    { UnionNum ++ ; }
  WORD ActOffset ()
    { return Offs[OffsLevel][UnionNum]; }
  };

void OffsetDefinition::PushLevel ()
  { 
  WIN_ASSERT (OffsLevel < MAXLEVEL - 1);
  LastUN[OffsLevel] = UnionNum;
  Offs[OffsLevel+1][0] = Offs[OffsLevel][UnionNum]; 
  OffsLevel ++ ;
  UnionNum = 0;
  for (int i = 1 ; i < MAXUNION ; i++) {
    Offs[OffsLevel][i] = Offs[OffsLevel][0];
    }
  }

void OffsetDefinition::PopLevel ()
  {
  WIN_ASSERT (OffsLevel > 0);
  WORD ml = 0;
  for (int i = 0 ; i < MAXUNION ; i++)
    if (ml < Offs[OffsLevel][i]) ml = Offs[OffsLevel][i] ;
  OffsLevel -- ;
  UnionNum = LastUN[OffsLevel];
  Offs[OffsLevel][UnionNum] = ml;
  }

// Zuordnung Btrieve Schluesseltyp, Datentyp
BYTE GetExtType (WORD DataType,BOOL IsRealTable,BOOL noAutoinc)
  {
  BYTE res;
  switch (DataType) {
    case DT_PRIVATE :
    case DT_SPRIVATE :
      res = BDT_UNSIGNED ;
      break ;
    case DT_LDSTRING :
      res = BDT_LSTRING ;
      break ;
    case DT_KLDATE :
      res = BDT_UNSIGNED ;
      break ;
    default :
      {
      if ((DataType == BDT_AUTOINC) && (noAutoinc || ((IsRealTable) && (OwnCounter()))))
        res = BDT_INTEGER;    // Den Schluessel ohne autoinc erzeugen
      else
        res = BYTE(DataType);
      }
      break ;
    }
  return res;
  }

static OffsetDefinition offs;
static WORD lastDType;
static char lastName[256];
static WORD lastOffset;
static WORD lastLen;
static WORD lastDimension;
LPVOID FAR *ListPtr;
void PushToAccess (LPVOID data,WORD dataSize)
  {
  WORD oSize;
  if (*ListPtr == NULL) oSize = sizeof(LPVOID) + 2 * sizeof(WORD);
  else                  oSize = GetBlockSize (*ListPtr);
  LPVOID res = GetGlobMem (oSize+dataSize);
  if (*ListPtr != NULL) lmemcpy (res,*ListPtr,oSize) , FreeGlobMem (*ListPtr) ;
  lmemcpy (LPSTR(res)+oSize,data,dataSize);
  *ListPtr = res;
  }

#define MAXDEPTH     10
#define MAXBREAKS    10
static WORD OffsBuffer[MAXDEPTH];
static int OffsPtr;
struct BreakLevel {
  int BreakCount;
  WORD BreakList[MAXBREAKS];
  };
static BreakLevel BreakBuffer[MAXDEPTH];
static int BreakPtr;
void PushElseOffset(WORD offs,BOOL Flag)
  {
  if (Flag) offs |= 0x8000;
  OffsBuffer[OffsPtr++] = offs;
  }

WORD PopElseOffset(BOOL FAR *Flag)
  {
  WORD offs = OffsBuffer[--OffsPtr];
  if (offs & 0x8000) *Flag = TRUE ;
  else               *Flag = FALSE ;
  return offs & 0x7FFF;
  }

void MarkForElse (BOOL flag = FALSE)
  {
  PushElseOffset (GetBlockSize (*ListPtr),flag);
  }
void InitializeBreakBuffer ()
  {
  BreakBuffer[BreakPtr].BreakCount = 0;
  BreakPtr++;
  }
void MarkForBreak ()
  {
  BreakBuffer[BreakPtr-1].BreakList[BreakBuffer[BreakPtr-1].BreakCount++] = GetBlockSize(*ListPtr);
  }
BreakLevel FAR *PopBreak ()
  {
  if (BreakPtr > 0)
    return &BreakBuffer[--BreakPtr];
  else
    return 0;
  }

LPACCESSDEF TbBtrv::GetAccess (LPSTR Name,BOOL forCompiler)
  {
  LPACCESSDEF Access;
  if (forCompiler)
    Access = LPACCESSDEF (AccessRef.ptr) ;
  else {
    if (AccessRef.offs) 
      Access = LPACCESSDEF (LPSTR(this) + AccessRef.offs) ;
    else
      Access = NULL ;
    }
  while (Access != NULL) {
    if (lstrcmp (Name,Access->Name) == 0) break ;
    if (Access->next.ptr == NULL)
      Access = NULL ;
    else
      Access = LPACCESSDEF ((forCompiler) ? Access->next.ptr : LPSTR(this)+Access->next.offs);
    }
  return Access;
  }

LPKEYDEF TbBtrv::GetKey (LPSTR Name,BOOL forCompiler,WORD FAR *Num)
  {
  LPKEYDEF Key = GetFirstKey (forCompiler);
  while (Key != NULL) {
    if (lstrcmp (Name,Key->Name) == 0) break ;
    Key = GetNextKey (Key,forCompiler);
    }
  if (Num != NULL) {
    if (Key != NULL) 
      *Num = Key->KeyNmbr;
    else
      *Num = 0xFFFF;
    }
  return Key;
  }

LPKEYDEF TbBtrv::GetKey (WORD KeyNum,BOOL forCompiler,LPSTR Name)
  {
  LPKEYDEF Key = GetFirstKey (forCompiler);
  while (Key != NULL) {
    if (Key->KeyNmbr == KeyNum) break ;
    Key = GetNextKey (Key,forCompiler);
    }
  if ((Key != NULL) && (Name != NULL)) lstrcpy (Name,Key->Name);
  return Key;
  }

LPVOID FAR *KeyList;
static WORD GesKeySize;
static WORD ActKeyNmbr;
void PushToKey (LPVOID data,WORD dataSize)
  {
  WORD oSize;
  if (*KeyList == NULL) oSize = sizeof(LPVOID);
  else                  oSize = GetBlockSize(*KeyList);
  LPVOID h = GetGlobMem (oSize + dataSize);
  if (*KeyList != NULL) lmemcpy (h,*KeyList,oSize), FreeGlobMem (*KeyList);
  lmemcpy (LPSTR(h)+oSize,data,dataSize);
  *KeyList = h;
  }
static WORD KeyToUse;

WORD GetDBOp (int kw)
  {
  struct kwtoop { int kw ; WORD op ; } ;
  kwtoop implementedops[] = {
    { KWGETEQUAL              , B_GETEQ             } ,
    { KWGETPREVEXTENDED       , B_GETPREVEXTENDED   } ,
    { KWGETNEXTEXTENDED       , B_GETNEXTEXTENDED   } ,
    { KWGETLAST               , B_GETLAST           } ,
    { KWGETFIRST              , B_GETFIRST          } ,
    { KWGETLESSEQUAL          , B_GETLE             } ,
    { KWGETLESS               , B_GETL              } ,
    { KWGETGREATEREQUAL       , B_GETGTE            } ,
    { KWGETGREATER            , B_GETGT             } ,
    { KWGETPREV               , B_GETPREV           } ,
    { KWGETNEXT               , B_GETNEXT           } ,
    { KWDELETE                , B_DELETE            } ,
    { KWINSERT                , B_INSERT            } ,
    { KWUPDATE                , B_UPDATE            } ,
    { KWGETDIRECT             , B_GETDIRECT         } ,
    { KWGETPOS                , B_GETPOS            } 
    };
  #define ANZOPS (sizeof(implementedops) / sizeof(kwtoop))
  for (int i = 0 ; i < ANZOPS ; i++) {
    if (implementedops[i].kw == kw) return implementedops[i].op ;
    }
  WIN_ASSERT (FALSE);
  return 0;
  }
/*-----< die eigentlichen Codegenerierungsfunktionen >---------*/
DLLExport void _export NotImplementedYet ()
  {
  cTbComp->wError = ERROR_NOTIMPLEMENTED;
  }

LPWORD bw;
int bit;
DLLExport void _export _SetBit          () { if (bw != NULL) { WORD mask = 1 << bit; *bw |= mask; bw = NULL ; } }
DLLExport void _export _ClearBit        () { if (bw != NULL) { WORD mask = 1 << bit; *bw &= ~mask; bw = NULL ; } }
DLLExport void _export _Create_TbBtrv   () { cTable = LPBTRVTABLE(GetGlobMem (sizeof(*cTable))); }
DLLExport void _export _SetFileRef      () { cTable->SetFileRef (LPSTR(GlobalLock(cTbComp->hPars0)) + sizeof(WORD)) ; GlobalUnlock(cTbComp->hPars0) ; }
DLLExport void _export _SetBDT_STRING   () { lastDType = BDT_STRING   ; }
DLLExport void _export _SetBDT_INTEGER  () { lastDType = BDT_INTEGER  ; }
DLLExport void _export _SetBDT_FLOAT    () { lastDType = BDT_FLOAT    ; }
DLLExport void _export _SetBDT_DATE     () { lastDType = BDT_DATE     ; }
DLLExport void _export _SetBDT_TIME     () { lastDType = BDT_TIME     ; }
DLLExport void _export _SetBDT_DECIMAL  () { lastDType = BDT_DECIMAL  ; }
DLLExport void _export _SetBDT_MONEY    () { lastDType = BDT_MONEY    ; }
DLLExport void _export _SetBDT_LOGICAL  () { lastDType = BDT_LOGICAL  ; }
DLLExport void _export _SetBDT_NUMERIC  () { lastDType = BDT_NUMERIC  ; }
DLLExport void _export _SetBDT_BFLOAT   () { lastDType = BDT_BFLOAT   ; }
DLLExport void _export _SetBDT_LSTRING  () { lastDType = BDT_LSTRING  ; }
DLLExport void _export _SetBDT_ZSTRING  () { lastDType = BDT_ZSTRING  ; }
DLLExport void _export _SetBDT_UNSIGNED () { lastDType = BDT_INTEGER  ; }
DLLExport void _export _SetBDT_AUTOINC  () { lastDType = BDT_AUTOINC  ; }
DLLExport void _export _SetDT_PRIVATE   () { lastDType = DT_PRIVATE   ; }
DLLExport void _export _SetDT_SPRIVATE  () { lastDType = DT_SPRIVATE  ; }
DLLExport void _export _SetDT_LDSTRING  () { lastDType = DT_LDSTRING  ; }
DLLExport void _export _SetDT_KLDATE    () { lastDType = DT_KLDATE    ; }
DLLExport void _export _SetLastName     () 
  { 
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; 
  if (cTable->GetVar (Name) != NULL) cTbComp->wError = ERROR_FIELDALREADYEXIST ; 
  lstrcpy (lastName,Name); 
  GlobalUnlock (cTbComp->hPars0); 
  lastDimension = 1 ; 
  }
DLLExport void _export _SetLastPos      () { lastOffset = offs.ActOffset () ; }
DLLExport void _export _SetLastLen      () { lastLen = int(cTbComp->scv.v.int_val) ; offs.AddLen (WORD(cTbComp->scv.v.int_val)) ; }
DLLExport void _export _SetLastDimension() { lastDimension = int(cTbComp->scv.v.int_val) ; if (lastDimension < 1) cTbComp->wError = ERROR_DIMENSION ; offs.AddLen (lastLen * (lastDimension - 1)) ; }
DLLExport void _export _PushVar         () { cTable->PushVar (lastName,lastDType,lastOffset,lastLen,lastDimension); }
DLLExport void _export _ResetOffs       () { offs.Reset () ; }
DLLExport void _export _PushLevel       () { offs.PushLevel () ; }
DLLExport void _export _PopLevel        () { offs.PopLevel () ; }
DLLExport void _export _NextUnion       () { offs.NextUnion () ; }
DLLExport void _export _SetBlockType0   () { cTable->BlockType = BLOCKTYPE_MARILLE ; cTable->bdsc.lOffset = offs.ActOffset (); }
DLLExport void _export _SetBlockType1   () { cTable->BlockType = BLOCKTYPE_KL ; cTable->bdsc.lOffset = offs.ActOffset (); }
DLLExport void _export _SetBlockType2   () { cTable->BlockType = BLOCKTYPE_MARILLE1 ; cTable->bdsc.lOffset = offs.ActOffset (); }
DLLExport void _export _SetOutRecord    () { cTable->bdsc.LengthMustExist = FALSE ; }
DLLExport void _export _SetInRecord     () { cTable->bdsc.LengthMustExist = TRUE ; offs.AddLen (2) ; }
DLLExport void _export _SetAnzChars     () { cTable->bdsc.AnzChars        = WORD (cTbComp->scv.v.int_val) ; }
DLLExport void _export _InitializeDesc  () { cTable->InitialiseDesc () ; }
DLLExport void _export _SetRecordSize   () 
  { 
#ifdef UEBERLEGT
  if (WORD(cTbComp->scv.v.int_val) < offs.Offs[0][0]) 
    cTbComp->wError = ERROR_RECTOSMALL ; 
#endif
  cTable->GetDescRef(TRUE)->SetRecordSize(WORD(cTbComp->scv.v.int_val)) ; 
  }
DLLExport void _export _SetPageSize     () { cTable->GetDescRef(TRUE)->SetPageSize(WORD(cTbComp->scv.v.int_val)) ; }
DLLExport void _export _PrepVarBit      () { bw = &cTable->GetDescRef(TRUE)->flags ; bit = FAB_VARIABLE ; }
DLLExport void _export _PrepCompBit     () { bw = &cTable->GetDescRef(TRUE)->flags ; bit = FAB_COMPRESS ; }
DLLExport void _export _AddKeySegment   () { cTable->AddKeySegment (); }
BOOL SetKeyDesc (LPSTR Name,BOOL IsRealTable = TRUE,int ExtraOffs = 0,int ExtraLen = 0,int ExtraType = 0,BOOL noAutoinc = FALSE)
  {
  LPVBTRV v = cTable->GetVar (Name);
  if (v == NULL)
    return FALSE ;
  else {
    if (v->Dimension != 1) return FALSE ;
    if (ExtraType == 0) ExtraType = v->DataType;
    if (ExtraLen == 0) ExtraLen = v->VarLen;
    LPRECDESC h = cTable->GetDescRef(TRUE);
    h->k[h->AnzKeySegs-1].position = v->VarOffset + 1 + ExtraOffs;
    h->k[h->AnzKeySegs-1].length   = ExtraLen ;
    h->k[h->AnzKeySegs-1].extType  = GetExtType (ExtraType,IsRealTable,noAutoinc);
    h->k[h->AnzKeySegs-1].flag     = KA_EXTENDED;
    }
  // In der internen Liste das noch vermerken
  LPVBTRV h = LPVBTRV (GetGlobMem (sizeof (*h) + lstrlen (Name)));
  h->EntryLen  = GetBlockSize (h);
  h->DataType  = ExtraType;
  h->VarLen    = ExtraLen;
  h->Dimension = 1;
  h->VarOffset = GesKeySize;
  GesKeySize   += ExtraLen;
  lstrcpy (h->Name,Name);
  int eLen = h->EntryLen;
  PushToKey (h,eLen);
  FreeGlobMem (h);
  // Gesamtlaenge nachtragen
  LPKEYDEF Key = cTable->GetKey (ActKeyNmbr-1,TRUE);
  LPVARTBL x = LPVARTBL (Key->Name + lstrlen(Key->Name) + 1) ;
  x->gSize += eLen;
  return TRUE ;
  }
DLLExport void _export _SetKeyDesc () 
  { 
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; 
  if (!SetKeyDesc (Name))
    cTbComp->wError = ERROR_FIELDDOESNOTEXIST;
  }

DLLExport void _export _PrepDuplicate  () { LPRECDESC h = cTable->GetDescRef(TRUE); bw = &h->k[h->AnzKeySegs-1].flag ; bit = KAB_DUPLICATE ; }
DLLExport void _export _PrepModifiable () { LPRECDESC h = cTable->GetDescRef(TRUE); bw = &h->k[h->AnzKeySegs-1].flag ; bit = KAB_MODIFIABLE ; }
DLLExport void _export _PrepNull       () { LPRECDESC h = cTable->GetDescRef(TRUE); bw = &h->k[h->AnzKeySegs-1].flag ; bit = KAB_NULL ; }
DLLExport void _export _PrepManual     () { LPRECDESC h = cTable->GetDescRef(TRUE); bw = &h->k[h->AnzKeySegs-1].flag ; bit = KAB_MANUAL ; }
DLLExport void _export _PrepAlt        () { LPRECDESC h = cTable->GetDescRef(TRUE); bw = &h->k[h->AnzKeySegs-1].flag ; bit = KAB_ALT ; }
DLLExport void _export _SetSeg         () { LPRECDESC h = cTable->GetDescRef(TRUE); h->k[h->AnzKeySegs-1].flag |= KA_SEGMENTED; }
DLLExport void _export _SetNullVal     () { LPRECDESC h = cTable->GetDescRef(TRUE); h->k[h->AnzKeySegs-1].nullVal = BYTE(cTbComp->scv.v.int_val) ; }
DLLExport void _export _SetNextKey     () { LPKEYDEF kd = LPKEYDEF (*KeyList); kd->KeySize = GesKeySize ; KeyList = &kd->next.ptr ; }
DLLExport void _export _IncAnzKeys     () { LPRECDESC h = cTable->GetDescRef(TRUE); h->NumKeys ++ ; _SetNextKey () ; }
DLLExport void _export _LoadAltSeq     () { LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; cTbComp->wError = cTable->LoadAltSeq (Name); GlobalUnlock (cTbComp->hPars0); }
void SetServerSourceStart ();
DLLExport void _export _SetPtrToRoot   () { ListPtr = &cTable->AccessRef.ptr ; KeyToUse = 0xFFFF ; SetServerSourceStart () ; }
DLLExport void _export _SetAccessName  () { LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; if (cTable->GetAccess(Name,TRUE) != NULL) cTbComp->wError = ERROR_ACCESSDEFINED ; PushToAccess (Name,lstrlen(Name)+1); }
struct ParDef {
  ParDef FAR *Next;
  WORD parNum;
  char Name[1];
  };
ParDef FAR *ParList;
DLLExport void _export _ClearParList ()
  {
  for ( ; ParList != NULL ; ) {
    ParDef FAR *next = ParList->Next ;
    FreeGlobMem (ParList);
    ParList = next;
    }
  }
LPSTR _lastDesc ;
DLLExport void _export _SetAccDesc()
  {
  WIN_ASSERT(_lastDesc == NULL);
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0))+sizeof(WORD);
  _lastDesc = LPSTR(GetGlobMem (lstrlen(Name)+1));
  lstrcpy (_lastDesc,Name);
  GlobalUnlock (cTbComp->hPars0);
  }
static BOOL ViewAllowed;
DLLExport void _export _SetViewAllowed () 
  {
  ViewAllowed = TRUE ;
  }
DLLExport void _export _SetPtrToNext   () 
  { 
  WORD h = DBFNC_END ; 
  PushToAccess (&h,sizeof(h)) ; 
  _ClearParList ();
  if (_lastDesc != NULL) {
    LPACCESSDEF(*ListPtr)->DescOffs = GetBlockSize(*ListPtr);
    PushToAccess (_lastDesc,lstrlen(_lastDesc)+1);
    FreeGlobMem (_lastDesc) , _lastDesc = NULL;
    }
  LPACCESSDEF(*ListPtr)->ViewAllowed = ViewAllowed;
  ListPtr = &(LPACCESSDEF(*ListPtr)->next.ptr) ; 
  ViewAllowed = FALSE ;
  KeyToUse = 0xFFFF ;
  }
DLLExport void _export _SetOpMsg       () { WORD h = DBFNC_MSG ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _StoreMsg       () { LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; PushToAccess (Name,lstrlen(Name)+1) ; GlobalUnlock (cTbComp->hPars0); }
static BOOL InSelect;
DLLExport void _export _SetOnFirst     () { WORD h = DBFNC_ONFIRST ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnLast      () { WORD h = DBFNC_ONLAST   ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnNext      () { WORD h = DBFNC_ONNEXT   ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnPrev      () { WORD h = DBFNC_ONPREV   ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnDelete    () { WORD h = DBFNC_ONDELETE ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnInsert    () { WORD h = DBFNC_ONINSERT ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnUpdate    () { WORD h = DBFNC_ONUPDATE ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnGet       () { WORD h = DBFNC_ONGET    ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnLock        () { WORD h = DBFNC_ONLOCK        ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnSuccess     () { WORD h = DBFNC_ONSUCCESS     ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnError       () { WORD h = DBFNC_ONERROR       ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnFatalError  () { WORD h = DBFNC_ONFATALERROR  ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnEndOfFile   () { WORD h = DBFNC_ONENDOFFILE   ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetOnRecNotFound () { WORD h = DBFNC_ONRECNOTFOUND ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetTestFilter    () { WORD h = DBFNC_TESTFILTER    ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetNotTestFilter () { WORD h = DBFNC_NOTTESTFILTER ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
static WORD EndCmd[MAXDEPTH];
static WORD endCmdPtr;
void PushEndCmd (WORD Cmd) { EndCmd[endCmdPtr++] = Cmd ; }
WORD PopEndCmd ()          { return EndCmd[--endCmdPtr] ; }
DLLExport void _export _SetOnMore        () { WORD h = DBFNC_ONMORE        ; PushToAccess (&h,sizeof(h)) ; MarkForElse (TRUE) ; PushEndCmd (DBFNC_ENDONMORE) ; h = 0 ; PushToAccess (&h,sizeof(h)) ; InitializeBreakBuffer () ; }
DLLExport void _export _SetForAll        () { WORD h = DBFNC_FORALL        ; PushToAccess (&h,sizeof(h)) ; MarkForElse (TRUE) ; PushEndCmd (DBFNC_ENDFORALL) ; h = 0 ; PushToAccess (&h,sizeof(h)) ; InitializeBreakBuffer () ; }
DLLExport void _export _SetOnRepeat      () { WORD h = DBFNC_REPEAT        ; PushToAccess (&h,sizeof(h)) ; MarkForElse (TRUE) ; PushEndCmd (DBFNC_ENDREPEAT) ; h = 0 ; PushToAccess (&h,sizeof(h)) ; InitializeBreakBuffer () ; }
DLLExport void _export _SetOnReduced     () { WORD h = DBFNC_ONREDUCED     ; PushToAccess (&h,sizeof(h)) ; MarkForElse () ; h = 0 ; PushToAccess (&h,sizeof(h)) ; }
DLLExport void _export _SetBreak         () { WORD h = DBFNC_BREAK         ; PushToAccess (&h,sizeof(h)) ; MarkForBreak () ; h = 0 ; PushToAccess (&h,sizeof(h)); }
DLLExport void _export _SetContinue      () { WORD h = DBFNC_CONTINUE      ; PushToAccess (&h,sizeof(h)) ; MarkForBreak () ; h = 0 ; PushToAccess (&h,sizeof(h)); }
DLLExport void _export _LookupElse       ()
  {
  BOOL doPopCmd;
  WORD elseOffset = PopElseOffset (&doPopCmd);
  if (doPopCmd) {
    WORD cmd  = PopEndCmd();  PushToAccess (&cmd,sizeof(cmd));
    short offs = elseOffset - GetBlockSize(*ListPtr); PushToAccess (&offs,sizeof(offs));
    }
  LPWORD h = LPWORD (LPSTR(*ListPtr) + elseOffset);
  *h = GetBlockSize(*ListPtr) - elseOffset ;
  if (doPopCmd) {
    BreakLevel FAR *breakOffs = PopBreak ();
    WIN_ASSERT (breakOffs != NULL);
    for (int i = 0 ; i < breakOffs->BreakCount ; i++) {
      h = LPWORD (LPSTR(*ListPtr) + breakOffs->BreakList[i]);
      *h = GetBlockSize(*ListPtr) - breakOffs->BreakList[i] ;
      }
    }
  }
DLLExport void _export _SetFirstKey    () { KeyList = &cTable->KeyRef.ptr ; ActKeyNmbr = 0 ; }
BOOL SetKeyName (LPSTR Name) 
  {
  if (cTable->GetKey(Name,TRUE) != NULL) return FALSE ;
  PushToKey (&ActKeyNmbr,sizeof(ActKeyNmbr));
  GesKeySize = 0;
  PushToKey (&GesKeySize,sizeof(GesKeySize));
  PushToKey (Name,lstrlen(Name)+1); 
  Vartbl vh;
  lmemset (&vh,'\0',sizeof(vh));
  vh.gSize = sizeof(Vartbl) - sizeof(VBtrv);
  PushToKey (&vh,vh.gSize);
  ActKeyNmbr ++ ;
  return TRUE ;
  }
DLLExport void _export _SetKeyName     () 
  {
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ; 
  if (!SetKeyName (Name))
    cTbComp->wError = ERROR_KEYDEFINED ; 
  GlobalUnlock (cTbComp->hPars0);
  }
DLLExport void _export _SetNoUsedKey () { KeyToUse = 0xFFFF; WORD cmd = DBFNC_USEKEY ; PushToAccess (&cmd,sizeof(cmd)) ; PushToAccess (&KeyToUse,sizeof(KeyToUse)) ; }
DLLExport void _export _SetUsedKey () 
  { 
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  cTable->GetKey (Name,TRUE,&KeyToUse) ; 
  if (KeyToUse == 0xFFFF) cTbComp->wError = ERROR_KEYNOTDEFINED;
  GlobalUnlock (cTbComp->hPars0); 
  WORD cmd = DBFNC_USEKEY ; PushToAccess (&cmd,sizeof(cmd)) ; 
  PushToAccess (&KeyToUse,sizeof(KeyToUse)) ; 
  }
DLLExport void _export _SetNoWaitLock () { WORD modify = DBOP_NOWAITLOCK ; PushToAccess (&modify,sizeof(modify)) ; }
DLLExport void _export _SetKeyOnly () { WORD modify = DBOP_KEYONLY ; PushToAccess (&modify,sizeof(modify)) ; }
DLLExport void _export _SetDBOp () { WORD cmd = DBFNC_DBOP ; PushToAccess (&cmd,sizeof(cmd)) ; WORD op = GetDBOp (cTbComp->scv.v.k_ident) ; PushToAccess (&op,sizeof(op)) ; }
DLLExport void _export _SetDBRes () { WORD cmd = DBFNC_STORE ; PushToAccess (&cmd,sizeof(cmd)) ; }
DLLExport void _export _SetDBResMulti () { WORD cmd = DBFNC_STOREMULTI ; PushToAccess (&cmd,sizeof(cmd)) ; }
DLLExport void _export _SetDirection () { PushToAccess (&cTbComp->scv.v.int_val,sizeof(WORD)) ; }
DLLExport void _export _TestBTRStatus () { WORD cmd = DBFNC_TESTDBSTATUS ; PushToAccess (&cmd,sizeof(cmd)) ; }
DLLExport void _export _SetDBRecord () { WORD cmd = DBFNC_SETRECORD ; PushToAccess (&cmd,sizeof(cmd)) ; }
static WORD sizeOffs;
DLLExport void _export _SetPrimKey ()
  {
  WORD cmd = DBFNC_SETPRIMKEY ;
  PushToAccess (&cmd,sizeof(cmd)) ;
  }
DLLExport void _export _SetJustInner ()
  {
  WORD cmd = DBFNC_SETINNERJOINS ;
  PushToAccess (&cmd,sizeof(cmd)) ;
  }
DLLExport void _export _SetAssignPush () 
  {
  WORD cmd = DBFNC_ASSIGN ;
  PushToAccess (&cmd,sizeof(cmd)) ;
  sizeOffs = GetBlockSize (*ListPtr);
  WORD dummy = 0;
  PushToAccess (&dummy,sizeof(dummy)) ;   // Dahinter wird spaeter die Groesse eingetragen
  ElemRef x;
  lmemset (&x,'\0',sizeof(x));
  x.Type = ER_PUSH ;
  PushToAccess (&x,sizeof(WORD)) ;
  }
DLLExport void _export _SetAssignCascade ()
  {
  WORD cmd = DBFNC_ASSIGN ;
  PushToAccess (&cmd,sizeof(cmd)) ;
  sizeOffs = GetBlockSize (*ListPtr);
  WORD dummy = 0;
  PushToAccess (&dummy,sizeof(dummy)) ;   // Dahinter wird spaeter die Groesse eingetragen
  ElemRef x;
  lmemset (&x,'\0',sizeof(x));
  x.Type = ER_CASCADE ;
  PushToAccess (&x,sizeof(WORD)) ;
  }
LPWORD GetParNum (LPSTR Name)
  {
  for (ParDef FAR *h = ParList; h != NULL ; h = h->Next)
    if (lstrcmp (h->Name,Name) == 0) return &h->parNum;
  return NULL;
  }
DLLExport void _export _SetAssignVar ()
  {
  WORD cmd = DBFNC_ASSIGN ;
  PushToAccess (&cmd,sizeof(cmd)) ;
  sizeOffs = GetBlockSize (*ListPtr);
  WORD dummy = 0;
  PushToAccess (&dummy,sizeof(dummy)) ;   // Dahinter wird spaeter die Groesse eingetragen
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  WORD Type = ER_KEYELEM;
  LPVBTRV x = cTable->GetKeyVar (Name,KeyToUse,TRUE);
  if (x == NULL) x = cTable->GetVar (Name,TRUE) , Type = ER_DATAELEM;
  if (x != NULL) {
    ElemRef h;
    h.Type = Type;
    h.x.v = *x;
    PushToAccess (&h,sizeof(h));
    }
  else {
    // Vielleicht ein parameter
    LPWORD parNum = GetParNum (Name);
    if (parNum != NULL) {
      ElemRef h;
      h.Type = ER_PARAMETER;
      h.x.parNum = *parNum;
      PushToAccess (&h,2 * sizeof(WORD));
      }
    else
      cTbComp->wError = ERROR_UNKNOWNVAR ;
    }
  }
DLLExport void _export _SetAssignSize ()
  {
  WORD ActSize = GetBlockSize (*ListPtr);
  WORD dSize = ActSize - sizeOffs;
  *(LPWORD(LPSTR(*ListPtr)+sizeOffs)) = dSize;
  }
#define MAXOPS  30
static ElemRef FAR *OperatorStack[MAXOPS];
static int OpNum;
WORD GetOperator (int kw)
  {
  struct kwtoop { int kw ; WORD op ; } kto [] = {
    { KWBINCAT        , OPERATOR_BINCAT     } ,
    { KWPADD          , OPERATOR_PADD       } ,
    { KWDIMBRACECLOSE , OPERATOR_EXTRACT    } ,
    { KWSTRCAT        , OPERATOR_STRCAT     } ,
    { KWNEXTCHAR      , OPERATOR_NEXTCHAR   } ,
    { KWADDLONG       , OPERATOR_ADDLONG    } ,
    { KWMULLONG       , OPERATOR_MULLONG    } ,
    { KWINCREMENT     , OPERATOR_INCREMENT  } ,
    { KWDECREMENT     , OPERATOR_DECREMENT  } ,
    { KWDIVLONG       , OPERATOR_DIVLONG    } ,
    { KWSUBLONG       , OPERATOR_SUBLONG    }
    } ;
  #define ANZEXOPS (sizeof(kto) / sizeof(kwtoop))
  for (int i = 0 ; i < ANZEXOPS ; i++) {
    if (kw == kto[i].kw) return kto[i].op ;
    }
  return 0;
  }
DLLExport void _export _MerkeOperator ()
  {
  ElemRef h;
  h.Type = ER_OP;
  h.x.op = GetOperator (cTbComp->scv.v.k_ident);
  OperatorStack[OpNum] = (ElemRef FAR *) GetGlobMem (2 * sizeof(WORD));
  lmemcpy (OperatorStack[OpNum],&h,2 * sizeof(WORD));
  OpNum ++ ;
  }
DLLExport void _export _PushString ()
  {
  LPSTR str = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  ElemRef FAR *h = (ElemRef FAR *)GetGlobMem (sizeof(WORD) + lstrlen(str) + 1);
  h->Type = ER_CONSTSTRING;
  lstrcpy (h->x.str,str);
  PushToAccess (h,GetBlockSize(h));
  FreeGlobMem (h);
  GlobalUnlock (cTbComp->hPars0); 
  }
DLLExport void _export _PushInteger ()
  {
  ElemRef h;
  h.Type = ER_CONSTINT;
  h.x.iVal = DWORD(cTbComp->scv.v.int_val);
  PushToAccess (&h,sizeof(WORD) + sizeof(DWORD));
  }
DLLExport void _export _PushPar ()
  {
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  WORD parNum;
  if (ParList != NULL)
    parNum = ParList->parNum + 1;
  else
    parNum = 0;
  ParDef FAR *n = (ParDef FAR *) GetGlobMem (sizeof(ParDef) + lstrlen(Name));
  n->Next = ParList;
  ParList = n;
  n->parNum = parNum;
  lstrcpy (n->Name,Name);
  GlobalUnlock (cTbComp->hPars0); 
  }
DLLExport void _export _PushVariable ()
  {
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  WORD Type = ER_KEYELEM;
  LPVBTRV x = cTable->GetKeyVar (Name,KeyToUse,TRUE);
  if (x == NULL) x = cTable->GetVar (Name,TRUE) , Type = ER_DATAELEM;
  if (x != NULL) {
    ElemRef h;
    h.Type = Type;
    h.x.v = *x;
    PushToAccess (&h,sizeof(h));
    }
  else {
    LPWORD parNum = GetParNum (Name);
    if (parNum != NULL) {
      ElemRef h;
      h.Type = ER_PARAMETER;
      h.x.parNum = *parNum;
      PushToAccess (&h,2 * sizeof(WORD));
      }
    else {
      cTbComp->wError = ERROR_UNKNOWNVAR;
      }
    }
  GlobalUnlock (cTbComp->hPars0); 
  }
DLLExport void _export _PushResult ()
  {
  WORD Type = ER_RESULT ;
  PushToAccess (&Type,sizeof(Type));
  }
DLLExport void _export _PushResultNum ()
  {
  PushToAccess (&cTbComp->scv.v.int_val,sizeof(WORD));
  }
DLLExport void _export _PushPop ()
  {
  WORD Type = ER_POP ;
  PushToAccess (&Type,sizeof(Type));
  }
DLLExport void _export _PushOperator ()
  {
  WIN_ASSERT (OpNum >= 1);
  PushToAccess (OperatorStack[OpNum - 1],GetBlockSize(OperatorStack[OpNum - 1]));
  FreeGlobMem  (OperatorStack[OpNum - 1]);
  OpNum -- ;
  }
DLLExport void _export _SetAbort ()
  {
  WORD cmd    = DBFNC_ABORT;
  PushToAccess (&cmd,sizeof(cmd));
  WORD RetVal = cTbComp->scv.v.k_ident;
  PushToAccess (&RetVal,sizeof(RetVal));
  }
DLLExport void _export _SetExtract () { _MerkeOperator (); _PushOperator (); }
DLLExport void _export _SetIf () 
  {
  WORD cmd = DBFNC_IF ; PushToAccess (&cmd,sizeof(WORD)); 
  MarkForElse () ; WORD h = 0 ; PushToAccess (&h,sizeof(h)) ;
  }
DLLExport void _export _SetQuestedPar () 
  {
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  LPWORD parNum = GetParNum (Name);
  if (parNum != NULL)
    PushToAccess (parNum,sizeof(WORD));
  else
    cTbComp->wError = ERROR_UNKNOWNVAR;
  GlobalUnlock (cTbComp->hPars0); 
  }
DLLExport void _export _SetQuestedInt ()
  {
  PushToAccess (&cTbComp->scv.v.int_val,sizeof(WORD));
  }
static WORD AnzParamsOffs;
static BOOL prefixNot = FALSE;
DLLExport void _export _SetOnParam () 
  {
  WORD cmd = DBFNC_ONPARAM ; PushToAccess (&cmd,sizeof(WORD)); 
  MarkForElse () ; WORD h = 0 ; PushToAccess (&h,sizeof(h)) ;
  AnzParamsOffs = GetBlockSize (*ListPtr);
  WORD AnzParams = 0 ; PushToAccess (&AnzParams,sizeof(WORD)); 
  prefixNot = FALSE;
  }
DLLExport void _export _NextParamNot ()
  {
  prefixNot = TRUE;
  }
DLLExport void _export _PushExParam ()
  {
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  LPWORD parNum = GetParNum (Name);
  if (parNum != NULL) {
    WORD pNum;
    if (prefixNot) pNum = *parNum | 0x8000;
    else           pNum = *parNum;
    PushToAccess (&pNum,sizeof(WORD));
    }
  else
    cTbComp->wError = ERROR_UNKNOWNVAR;
  prefixNot = FALSE;
  GlobalUnlock (cTbComp->hPars0); 
  LPWORD lpAnzParams = LPWORD(LPSTR(*ListPtr) + AnzParamsOffs);
  (*lpAnzParams)++;
  }
static WORD filterOffset;
DLLExport void _export _SetFilter ()
  {
  WORD cmd = DBFNC_FILTER;  PushToAccess (&cmd,sizeof(cmd));
  filterOffset = GetBlockSize (*ListPtr);
  WORD h = 0;               PushToAccess (&h,sizeof(h));
  }
static BOOL AvoidAssign;
DLLExport void _export _SetMoreFilter ()
  {
  WORD cmd = DBFNC_MOREFILTER;  PushToAccess (&cmd,sizeof(cmd));
  filterOffset = GetBlockSize (*ListPtr);
  WORD h = 0;               PushToAccess (&h,sizeof(h));
  AvoidAssign = TRUE ;
  }
BYTE GetBtrDataType (WORD dt)
  {
  switch (dt) {
    case DT_PRIVATE  :
    case DT_KLDATE   :
    case DT_SPRIVATE :
      return BDT_UNSIGNED ;
    case DT_LDSTRING :
      return BDT_LSTRING ;
    default :
      return BYTE(dt);
    }
  }
BYTE GetBtrCmpBias (WORD dt)
  {
  switch (dt) {
    case BDT_ZSTRING :
      return 32;
    default :
      return 0;
    }
  }
DLLExport void _export _SetAssignFilter ()
  {
  FilterHeader hd;
  LPSTR Name = LPSTR(GlobalLock (cTbComp->hPars0)) + sizeof(WORD) ;
  LPVBTRV v = cTable->GetVar (Name,TRUE);
  GlobalUnlock (cTbComp->hPars0); 
  if (v != NULL) {
    hd.btrDataType = GetBtrDataType (v->DataType);
    hd.VarLen      = v->VarLen;
    hd.VarOffset   = v->VarOffset;
    hd.cmpCode     = GetBtrCmpBias (v->DataType);
    PushToAccess (&hd,sizeof(hd));
    sizeOffs = GetBlockSize (*ListPtr);
    WORD dummy = 0;
    PushToAccess (&dummy,sizeof(dummy)) ;   // Dahinter wird spaeter die Groesse eingetragen
    }
  else
    cTbComp->wError = ERROR_UNKNOWNVAR;
  }
BYTE GetBtrvCmp (int kw)
  {
  struct kwtocmp { int kw ; BYTE cmp ; } ktoc [] = {
    { KWCMNOTEQUAL ,     BCMP_NOTEQUAL     } ,
    { KWCMLESSEQUAL ,    BCMP_LESSEQAUL    } ,
    { KWCMLESS ,         BCMP_LESS         } ,
    { KWCMGREATEREQUAL , BCMP_GREATEREQUAL } ,
    { KWCMGREATER ,      BCMP_GREATER      } ,
    { KWCMEQUAL ,        BCMP_EQUAL        } ,
    { KWINLIST ,         BCMP_LIST         }
    };
  #define ANZKWTOCMP (sizeof(ktoc) / sizeof(kwtocmp))
  for (int i = 0 ; i < ANZKWTOCMP ; i++)
    if (ktoc[i].kw == kw) return ktoc[i].cmp ;
  return 0;
  }
DLLExport void _export _SetCmpOperator ()
  {
  LPSTR lpcmp = LPSTR(*ListPtr) + GetBlockSize(*ListPtr) - sizeof(WORD) - sizeof(BYTE);
  *lpcmp += GetBtrvCmp (cTbComp->scv.v.k_ident);
  }
DLLExport void _export _SetCIOperator()
  {
  BYTE FAR *lpcmp = (BYTE FAR *) (LPSTR(*ListPtr) + GetBlockSize(*ListPtr) - sizeof(WORD) - sizeof(BYTE));
  *lpcmp += 128;
  }
BYTE GetBtrvLogOp (int kw)
  {
  struct kwtolop { int kw ; BYTE op ; } ktol [] = {
    { KWAND ,     BOP_AND     } ,
    { KWOR ,      BOP_OR      } 
    };
  #define ANZKWTOLOP (sizeof(ktol) / sizeof(kwtolop))
  for (int i = 0 ; i < ANZKWTOLOP ; i++)
    if (ktol[i].kw == kw) return ktol[i].op ;
  return 0;
  }
DLLExport void _export _SetLogOp ()
  {
  if (!AvoidAssign)
    _SetAssignSize ();
  BYTE op = GetBtrvLogOp (cTbComp->scv.v.k_ident);
  PushToAccess (&op,sizeof(op));
  AvoidAssign = FALSE ;
  }
DLLExport void _export _SetEndFilter ()
  {
  _SetLogOp ();
  WORD Offset = GetBlockSize (*ListPtr);
  LPWORD o = LPWORD(LPSTR(*ListPtr) + filterOffset);
  *o = Offset - filterOffset;
  }
DLLExport void _export _SetRejectCount () { WORD count = WORD(cTbComp->scv.v.int_val) ; PushToAccess (&count,sizeof(count)) ; }
DLLExport void _export _SetReject () { WORD cmd = DBFNC_SETREJECT ; PushToAccess (&cmd,sizeof(cmd)) ; }
DLLExport void _export _SetInitializeRec () { WORD cmd = DBFNC_INITIALIZERECORD ; PushToAccess (&cmd,sizeof(cmd)) ; }
DLLExport void _export _PushToLockList () { WORD cmd = DBFNC_PUSHTOLOCKLIST ; PushToAccess (&cmd,sizeof(cmd)) ; }

/*------------------------------------*/
/*  Den Text des Servers exportieren  */
/*------------------------------------*/
static GLOBALHANDLE hGLastServerSource;
static char _huge *ServerSourceStartptr;
void SetServerSourceStart ()
  {
  ServerSourceStartptr = (char _huge *) cTbComp->GetActPtr() - 6 ;
  }

DLLExport void _export SetLastServerSource ()
  {
  if (ServerSourceStartptr) {
    char _huge *end = (char _huge *) cTbComp->GetActPtr();
    char _huge *beg = ServerSourceStartptr;
    DWORD Size = end - beg + 1;
    hGLastServerSource = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,Size);
    char _huge *res = (char _huge *) GlobalLock (hGLastServerSource);
    hmemcpy (res,beg,Size-1);
    GlobalUnlock (hGLastServerSource);
    }
  else
    hGLastServerSource = 0;
  }

/*-----------------------------------------------------------*/
/*  Syntax der Tabelle                                       */
/*-----------------------------------------------------------*/
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

syntax_node filename3  = { NULL       , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node filename2  = { &filename3 , NULL , TRUE , INITERM(STRING,0) , _SetFileRef } ;
syntax_node filename1  = { &filename2 , NULL , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node filename   = { &filename1 , NULL , TRUE , INITERM(KEYWORD,KWFILE) , _Create_TbBtrv } ;

syntax_node blocks3     = { NULL     , NULL        , TRUE , INITERM(KEYWORD,KWOUTRECORD) , _SetOutRecord } ;
syntax_node blocks2     = { NULL     , &blocks3    , TRUE , INITERM(KEYWORD,KWINRECORD) , _SetInRecord } ;
syntax_node blocks1     = { &blocks2 , NULL        , TRUE , INITERM(T_INTEGER,0) , _SetAnzChars } ;
syntax_node blocktype1  = { &blocks1 , NULL        , TRUE , INITERM(KEYWORD,KWBLOCKS) , _SetBlockType1 } ;
syntax_node blocktypea  = { NULL     , &blocktype1 , TRUE , INITERM(KEYWORD,KWBLOCKSU) , _SetBlockType2 } ;
syntax_node blocktype   = { NULL     , &blocktypea , TRUE , INITERM(KEYWORD,KWBLOCKSC) , _SetBlockType0 } ;

syntax_node blockdesc2  = { NULL        , NULL , TRUE  , INITERM(KEYWORD,KWSEMICOLON), NULL } ;
syntax_node blockdesc1  = { &blockdesc2 , NULL , FALSE , &blocktype , NULL } ;
syntax_node blockdesc   = { &blockdesc1 , NULL , TRUE , INITERM(KEYWORD,KWBLOCK) , NULL } ;

syntax_node datatype17  = { NULL , NULL        , TRUE , INITERM(KEYWORD,KWKLDATE  ) , _SetDT_KLDATE    } ; 
syntax_node datatype16  = { NULL , &datatype17 , TRUE , INITERM(KEYWORD,KWLDSTRING) , _SetDT_LDSTRING  } ; 
syntax_node datatype15  = { NULL , &datatype16 , TRUE , INITERM(KEYWORD,KWSPRIVATE) , _SetDT_SPRIVATE  } ; 
syntax_node datatype14  = { NULL , &datatype15 , TRUE , INITERM(KEYWORD,KWPRIVATE ) , _SetDT_PRIVATE   } ; 
syntax_node datatype13  = { NULL , &datatype14 , TRUE , INITERM(KEYWORD,KWAUTOINC ) , _SetBDT_AUTOINC  } ; 
syntax_node datatype12  = { NULL , &datatype13 , TRUE , INITERM(KEYWORD,KWUNSIGNED) , _SetBDT_UNSIGNED } ; 
syntax_node datatype11  = { NULL , &datatype12 , TRUE , INITERM(KEYWORD,KWZSTRING ) , _SetBDT_ZSTRING  } ; 
syntax_node datatype10  = { NULL , &datatype11 , TRUE , INITERM(KEYWORD,KWLSTRING ) , _SetBDT_LSTRING  } ; 
syntax_node datatype9   = { NULL , &datatype10 , TRUE , INITERM(KEYWORD,KWBFLOAT  ) , _SetBDT_BFLOAT   } ; 
syntax_node datatype8   = { NULL , &datatype9  , TRUE , INITERM(KEYWORD,KWNUMERIC ) , _SetBDT_NUMERIC  } ; 
syntax_node datatype7   = { NULL , &datatype8  , TRUE , INITERM(KEYWORD,KWLOGICAL ) , _SetBDT_LOGICAL  } ; 
syntax_node datatype6   = { NULL , &datatype7  , TRUE , INITERM(KEYWORD,KWMONEY   ) , _SetBDT_MONEY    } ; 
syntax_node datatype5   = { NULL , &datatype6  , TRUE , INITERM(KEYWORD,KWDECIMAL ) , _SetBDT_DECIMAL  } ; 
syntax_node datatype4   = { NULL , &datatype5  , TRUE , INITERM(KEYWORD,KWTIME    ) , _SetBDT_TIME     } ; 
syntax_node datatype3   = { NULL , &datatype4  , TRUE , INITERM(KEYWORD,KWDATE    ) , _SetBDT_DATE     } ; 
syntax_node datatype2   = { NULL , &datatype3  , TRUE , INITERM(KEYWORD,KWFLOAT   ) , _SetBDT_FLOAT    } ; 
syntax_node datatype1   = { NULL , &datatype2  , TRUE , INITERM(KEYWORD,KWINTEGER ) , _SetBDT_INTEGER  } ; 
syntax_node datatype    = { NULL , &datatype1  , TRUE , INITERM(KEYWORD,KWUSTRING  ) , _SetBDT_STRING  } ; 

syntax_node field7      = { NULL    , NULL      , TRUE  , INITERM(KEYWORD,KWSEMICOLON), _PushVar } ;
syntax_node field6      = { &field7 , NULL      , TRUE  , INITERM(KEYWORD,KWDIMBRACECLOSE), NULL } ;
syntax_node field5      = { &field6 , NULL      , TRUE  , INITERM(T_INTEGER,0), _SetLastDimension } ;
syntax_node field4      = { &field5 , &field7   , TRUE  , INITERM(KEYWORD,KWDIMBRACEOPEN), NULL } ;
syntax_node field3      = { &field4 , NULL      , TRUE  , INITERM(T_INTEGER,0), _SetLastLen } ;
syntax_node field2      = { &field3 , NULL      , TRUE  , INITERM(KEYWORD,KWDOPPELPUNKT), _SetLastPos } ;
syntax_node field1      = { &field2 , NULL      , TRUE  , INITERM(UNKNOWNIDENT,0), _SetLastName } ;
syntax_node field       = { &field1 , NULL      , FALSE , &datatype, NULL } ;

extern syntax_node elem;
extern syntax_node unionblock1;
syntax_node unionblock3  = { NULL         , NULL         , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node unionblock2  = { &unionblock3 , &unionblock1 , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , _NextUnion } ;
syntax_node unionblock1  = { &unionblock2 , NULL         , FALSE , &elem , NULL } ;
syntax_node unionblock   = { &unionblock1 , NULL         , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN) , NULL } ;

extern syntax_node _union2;
syntax_node _union4     = { NULL         , NULL     , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node _union3     = { &_union4     , &_union2 , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , _PopLevel } ;
syntax_node _union2     = { &_union3     , NULL     , FALSE , &unionblock , NULL } ;
syntax_node _union1     = { &_union2     , NULL     , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN) , _PushLevel } ;
syntax_node _union      = { &_union1     , NULL     , TRUE  , INITERM(KEYWORD,KWUNION) , NULL } ;

syntax_node elem1  = { NULL   , NULL   , FALSE , &_union             , NULL } ;
syntax_node elem   = { NULL   , &elem1 , FALSE , &field              , NULL } ;

extern syntax_node fieldlist3;
syntax_node fieldlist6  = { NULL        , NULL         , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetFirstKey } ;
syntax_node fieldlist5  = { &fieldlist6 , NULL         , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , NULL } ;
syntax_node fieldlist4  = { &fieldlist5 , &fieldlist5  , FALSE , &blockdesc , NULL } ;
syntax_node fieldlist3  = { &fieldlist3 , &fieldlist4  , FALSE , &elem , NULL };
syntax_node fieldlist2  = { &fieldlist3 , NULL         , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN) , NULL } ;
syntax_node fieldlist1  = { &fieldlist2 , NULL         , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node fieldlist   = { &fieldlist1 , NULL         , TRUE  , INITERM(KEYWORD,KWFIELD) , _ResetOffs } ;

syntax_node flag1       = { NULL        , NULL         , TRUE  , INITERM(KEYWORD,KWNO) , _ClearBit } ;
syntax_node flag        = { NULL        , &flag1       , TRUE  , INITERM(KEYWORD,KWYES) , _SetBit } ;

syntax_node pagesize2   = { NULL    , NULL , TRUE , INITERM(T_INTEGER,0) , _SetPageSize } ;
syntax_node pagesize1   = { &pagesize2 , NULL , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node pagesize    = { &pagesize1 , NULL , TRUE , INITERM(KEYWORD,KWPAGESIZE) , NULL } ;

syntax_node compress2   = { NULL , NULL , FALSE , &flag , NULL } ;
syntax_node compress1   = { &compress2 , NULL , TRUE , INITERM (KEYWORD,KWEQUAL) , NULL } ;
syntax_node compress    = { &compress1 , NULL , TRUE , INITERM (KEYWORD,KWCOMPRESS) , _PrepCompBit } ;

syntax_node variable2   = { NULL , NULL , FALSE , &flag , NULL } ;
syntax_node variable1   = { &variable2 , NULL , TRUE , INITERM (KEYWORD,KWEQUAL) , NULL } ;
syntax_node variable    = { &variable1 , NULL , TRUE , INITERM (KEYWORD,KWVARIABLE) , _PrepVarBit } ;

syntax_node size2       = { NULL   , NULL , TRUE , INITERM (T_INTEGER,0) , NULL } ;
syntax_node size1       = { &size2 , NULL , TRUE , INITERM (KEYWORD,KWEQUAL) , NULL } ;
syntax_node size        = { &size1 , NULL , TRUE , INITERM (KEYWORD,KWSIZE) , NULL } ;

syntax_node record5     = { NULL , NULL , FALSE , &pagesize , NULL } ;
syntax_node record4     = { &record5 , NULL , FALSE , &compress , NULL } ;
syntax_node record3     = { &record4 , NULL , FALSE , &variable , NULL } ;
syntax_node record2     = { &record3 , NULL , FALSE , &size , _SetRecordSize } ;
syntax_node record1     = { &record2 , NULL , TRUE  , INITERM(KEYWORD,KWDOPPELPUNKT) , NULL } ;
syntax_node record      = { &record1 , NULL , TRUE  , INITERM(KEYWORD,KWRECORD) , _InitializeDesc } ;

syntax_node duplicate2  = { NULL        , NULL , FALSE , &flag , NULL } ;
syntax_node duplicate1  = { &duplicate2 , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node duplicate   = { &duplicate1 , NULL , TRUE  , INITERM(KEYWORD,KWDUPLICATE) , _PrepDuplicate } ;

syntax_node modifiable2 = { NULL         , NULL , FALSE , &flag , NULL } ;
syntax_node modifiable1 = { &modifiable2 , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node modifiable  = { &modifiable1 , NULL , TRUE  , INITERM(KEYWORD,KWMODIFIABLE) , _PrepModifiable } ;

syntax_node alternate2 = { NULL        , NULL , FALSE , &flag , NULL } ;
syntax_node alternate1 = { &alternate2 , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node alternate  = { &alternate1 , NULL , TRUE  , INITERM(KEYWORD,KWALTERNATE) , _PrepAlt } ;

// syntax_node nulle      = { NULL    , NULL , TRUE , INITERM(FREECHAR,0) , NULL } ;
// syntax_node null4      = { NULL    , NULL , FALSE , &value , NULL } ;
// syntax_node null3      = { &null4  , &nulle , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node null2      = { NULL /* &null3 */ , NULL , FALSE , &flag , NULL } ;
syntax_node null1      = { &null2  , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node null       = { &null1  , NULL , TRUE  , INITERM(KEYWORD,KWNULL) , _PrepNull } ;

syntax_node value2     = { NULL    , NULL , TRUE , INITERM(T_INTEGER,0) , _SetNullVal } ;
syntax_node value1     = { &value2 , NULL , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node value      = { &value1 , NULL , TRUE , INITERM(KEYWORD,KWVALUE) , NULL } ;

syntax_node manuale    = { NULL    , NULL , TRUE , INITERM(FREECHAR, 0) , NULL } ;
syntax_node manual4    = { NULL    , NULL , FALSE , &value , NULL } ;
syntax_node manual3    = { &manual4  , &manuale , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node manual2    = { &manual3  , NULL , FALSE , &flag , NULL } ;
syntax_node manual1    = { &manual2  , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node manual     = { &manual1  , NULL , TRUE  , INITERM(KEYWORD,KWMANUAL) , _PrepManual } ;

syntax_node attribute4  = { NULL , NULL , FALSE , &manual , NULL } ;
syntax_node attribute3  = { NULL , &attribute4 , FALSE , &null , NULL } ;
syntax_node attribute2  = { NULL , &attribute3 , FALSE , &alternate , NULL } ;
syntax_node attribute1  = { NULL , &attribute2 , FALSE , &modifiable , NULL } ;
syntax_node attribute   = { NULL , &attribute1 , FALSE , &duplicate , NULL } ;

extern syntax_node keysegment3;
syntax_node keysegment5 = { NULL , NULL , TRUE , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node keysegment4 = { &keysegment3 , &keysegment5 , TRUE , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node keysegment3 = { &keysegment4 , NULL , FALSE , &attribute , NULL } ;
syntax_node keysegment2 = { &keysegment3 , NULL , TRUE , INITERM(KEYWORD,KWDOPPELPUNKT) , NULL } ;
syntax_node keysegment1 = { &keysegment2 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetKeyDesc } ;
syntax_node keysegment  = { &keysegment1 , NULL , TRUE , INITERM(KEYWORD,KWBRACEOPEN) , _AddKeySegment } ;

extern syntax_node key3 ;
syntax_node key5 =   { NULL  , NULL  , TRUE , INITERM(KEYWORD,KWSEMICOLON) , _IncAnzKeys } ;
syntax_node key4 =   { &key3 , &key5 , TRUE , INITERM(KEYWORD,KWPLUS) , _SetSeg } ;
syntax_node key3 =   { &key4 , NULL  , FALSE , &keysegment , NULL } ;
syntax_node key2 =   { &key3 , NULL  , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node key1 =   { &key2 , NULL  , TRUE , INITERM(UNKNOWNIDENT,0) , _SetKeyName } ;
syntax_node key  =   { &key1 , NULL  , TRUE , INITERM(KEYWORD,KWKEY) , NULL } ;

// syntax_node alternatename3 = { NULL            , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node alternatename2 = { NULL /* &alternatename3 */ , NULL , TRUE , INITERM(STRING,0) , _LoadAltSeq } ;
syntax_node alternatename1 = { &alternatename2 , NULL , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node alternatename  = { &alternatename1 , NULL , TRUE , INITERM(KEYWORD,KWNAME) , NULL } ;

syntax_node op_type8  = { NULL , NULL      , TRUE , INITERM(KEYWORD,KWONREDUCED) , _SetOnReduced } ;
syntax_node op_type7  = { NULL , &op_type8 , TRUE , INITERM(KEYWORD,KWONUPDATE) , _SetOnUpdate } ;
syntax_node op_type6  = { NULL , &op_type7 , TRUE , INITERM(KEYWORD,KWONDELETE) , _SetOnDelete } ;
syntax_node op_type5  = { NULL , &op_type6 , TRUE , INITERM(KEYWORD,KWONINSERT) , _SetOnInsert } ;
syntax_node op_type4  = { NULL , &op_type5 , TRUE , INITERM(KEYWORD,KWONLAST) , _SetOnLast } ;
syntax_node op_type3  = { NULL , &op_type4 , TRUE , INITERM(KEYWORD,KWONFIRST) , _SetOnFirst } ;
syntax_node op_type2  = { NULL , &op_type3 , TRUE , INITERM(KEYWORD,KWONPREV) , _SetOnPrev } ;
syntax_node op_type1  = { NULL , &op_type2 , TRUE , INITERM(KEYWORD,KWONNEXT) , _SetOnNext } ;
syntax_node op_type   = { NULL , &op_type1 , TRUE , INITERM(KEYWORD,KWONGET) , _SetOnGet } ;

extern syntax_node extstmt6 ;
syntax_node extstmt9  =  { NULL      , NULL         , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node extstmt8  =  { &extstmt9 , NULL         , TRUE , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node extstmt7  =  { &extstmt6 , &extstmt8    , TRUE , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node extstmt6  =  { &extstmt7 , &extstmt8    , TRUE , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node extstmt5  =  { &extstmt6 , NULL , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node extstmt4  =  { &extstmt5 , NULL , FALSE , &op_type , NULL } ;
syntax_node extstmt3  =  { &extstmt4 , NULL , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node extstmt2  =  { &extstmt3 , NULL , TRUE  , INITERM(STRING,0) , NULL } ;
syntax_node extstmt1  =  { &extstmt2 , NULL , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node extstmt   =  { &extstmt1 , NULL , TRUE  , INITERM(KEYWORD,KWUSE_SELECTION) , NULL } ;

syntax_node unop8        = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWSUBLONG) , _MerkeOperator } ;
syntax_node unop7        = { NULL          , &unop8        , TRUE  , INITERM(KEYWORD,KWDIVLONG) , _MerkeOperator } ;
syntax_node unop6        = { NULL          , &unop7        , TRUE  , INITERM(KEYWORD,KWMULLONG) , _MerkeOperator } ;
syntax_node unop5        = { NULL          , &unop6        , TRUE  , INITERM(KEYWORD,KWDECREMENT) , _MerkeOperator } ;
syntax_node unop4        = { NULL          , &unop5        , TRUE  , INITERM(KEYWORD,KWINCREMENT) , _MerkeOperator } ;
syntax_node unop3        = { NULL          , &unop4        , TRUE  , INITERM(KEYWORD,KWADDLONG) , _MerkeOperator } ;
syntax_node unop2        = { NULL          , &unop3        , TRUE  , INITERM(KEYWORD,KWNEXTCHAR) , _MerkeOperator } ;
syntax_node unop1        = { NULL          , &unop2        , TRUE  , INITERM(KEYWORD,KWSTRCAT) , _MerkeOperator } ;
syntax_node unop         = { NULL          , &unop1        , TRUE  , INITERM(KEYWORD,KWPADD) , _MerkeOperator } ;

syntax_node binop        = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWBINCAT) , _MerkeOperator } ;

extern syntax_node expression;
extern syntax_node operand11;
syntax_node operand42    = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node operand41    = { &operand42    , NULL          , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node operand40    = { &operand41    , NULL          , TRUE  , INITERM(KEYWORD,KWPOP) , _PushPop } ;
syntax_node operand33    = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWDIMBRACECLOSE) , NULL } ;
syntax_node operand32    = { &operand33    , NULL          , TRUE  , INITERM(T_INTEGER,0) , _PushResultNum } ;
syntax_node operand31    = { &operand32    , NULL          , TRUE  , INITERM(KEYWORD,KWDIMBRACEOPEN) , NULL } ;
syntax_node operand30    = { &operand31    , &operand40    , TRUE  , INITERM(KEYWORD,KWRESULT) , _PushResult } ;
syntax_node operand21    = { &operand11    , &operand30    , TRUE  , INITERM(STRING,0) , _PushString } ;
syntax_node operand20    = { &operand11    , &operand21    , TRUE  , INITERM(T_INTEGER,0) , _PushInteger } ;
syntax_node operand16    = { NULL          , NULL          , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node operand15    = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWDIMBRACECLOSE) , _SetExtract } ;
syntax_node operand14    = { &operand15    , NULL          , TRUE  , INITERM(T_INTEGER,0) , _PushInteger } ;
syntax_node operand13    = { &operand14    , NULL          , TRUE  , INITERM(KEYWORD,KWDOPPELPUNKT) , NULL } ;
syntax_node operand12    = { &operand13    , NULL          , TRUE  , INITERM(T_INTEGER,0) , _PushInteger } ;
syntax_node operand11    = { &operand12    , &operand16    , TRUE  , INITERM(KEYWORD,KWDIMBRACEOPEN) , NULL } ;
syntax_node operand10    = { &operand11    , &operand20    , TRUE  , INITERM(UNKNOWNIDENT,0) , _PushVariable } ;
syntax_node operand2     = { &operand11    , NULL          , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node operand1     = { &operand2     , NULL          , FALSE , &expression , NULL } ;
syntax_node operand      = { &operand1     , &operand10    , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;

extern syntax_node expression12;
syntax_node expression14 = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , _PushOperator } ;
syntax_node expression13 = { &expression12 , &expression14 , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node expression12 = { &expression13 , NULL          , FALSE , &expression , NULL } ;
syntax_node expression11 = { &expression12 , NULL          , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node expression10 = { &expression11 , NULL          , FALSE , &unop , NULL } ;
syntax_node expression3  = { NULL          , NULL          , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node expression2  = { NULL          , NULL          , FALSE , &operand , _PushOperator } ;
syntax_node expression1  = { &expression2  , &expression3  , FALSE , &binop , NULL } ;
syntax_node expression   = { &expression1  , &expression10 , FALSE , &operand , NULL } ;

syntax_node assignstmt3  = { NULL          , NULL          , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetAssignSize };
syntax_node assignstmt2  = { &assignstmt3  , NULL         , FALSE , &expression , NULL };
syntax_node assignstmt1  = { &assignstmt2  , NULL         , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL };
syntax_node assignstmt   = { &assignstmt1  , NULL         , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetAssignVar };

syntax_node keystmt4  = { NULL      , NULL      , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node keystmt3  = { &keystmt4 , NULL      , TRUE , INITERM(KEYWORD,KWREMAPKEY) , NULL } ;
syntax_node keystmt2  = { &keystmt4 , NULL      , TRUE , INITERM(UNKNOWNIDENT,0) , _SetUsedKey } ;
syntax_node keystmt1  = { &keystmt4 , &keystmt2 , TRUE , INITERM(KEYWORD,KWNONE) , _SetNoUsedKey } ;
syntax_node keystmt   = { &keystmt1 , &keystmt3 , TRUE , INITERM(KEYWORD,KWUSE) , NULL } ;

syntax_node dbstmt41     = { NULL      , NULL      , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node dbstmt40     = { &dbstmt41 , NULL      , TRUE , INITERM(KEYWORD,KWTESTBTSTATUS) , _TestBTRStatus } ;

syntax_node dbstmt31     = { NULL      , NULL      , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node dbstmt30     = { &dbstmt31 , &dbstmt40 , TRUE , INITERM(KEYWORD,KWSETLINE) , _SetDBRecord } ;

syntax_node dbstmt25     = { NULL      , NULL      , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node dbstmt24     = { &dbstmt25 , NULL      , TRUE , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node dbstmt23     = { &dbstmt24 , NULL      , TRUE , INITERM(T_INTEGER,0) , _SetDirection } ;
syntax_node dbstmt22     = { &dbstmt23 , NULL      , TRUE , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node dbstmt21     = { &dbstmt22 , &dbstmt30 , TRUE , INITERM(KEYWORD,KWSTOREMULTI) , _SetDBResMulti } ;
syntax_node dbstmt20     = { &dbstmt22 , &dbstmt21 , TRUE , INITERM(KEYWORD,KWSETRESULT) , _SetDBRes } ;

syntax_node dbstmt18     = { NULL      , NULL      , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node dbstmt17     = { &dbstmt18 , &dbstmt18 , TRUE , INITERM(KEYWORD,KWNOWAITLOCK) , _SetNoWaitLock } ;
syntax_node dbstmt16     = { &dbstmt18 , &dbstmt17 , TRUE , INITERM(KEYWORD,KWKEYONLY) , _SetKeyOnly } ;
syntax_node dbstmt15     = { &dbstmt16 , &dbstmt20 , TRUE , INITERM(KEYWORD,KWGETPOS) , _SetDBOp } ;
syntax_node dbstmt14     = { &dbstmt16 , &dbstmt15 , TRUE , INITERM(KEYWORD,KWGETDIRECT) , _SetDBOp } ;
syntax_node dbstmt13     = { &dbstmt16 , &dbstmt14 , TRUE , INITERM(KEYWORD,KWDELETE) , _SetDBOp } ;
syntax_node dbstmt12     = { &dbstmt16 , &dbstmt13 , TRUE , INITERM(KEYWORD,KWINSERT) , _SetDBOp } ;
syntax_node dbstmt11     = { &dbstmt16 , &dbstmt12 , TRUE , INITERM(KEYWORD,KWUPDATE) , _SetDBOp } ;
syntax_node dbstmt10     = { &dbstmt16 , &dbstmt11 , TRUE , INITERM(KEYWORD,KWGETPREVEXTENDED) , _SetDBOp } ;
syntax_node dbstmt9      = { &dbstmt16 , &dbstmt10 , TRUE , INITERM(KEYWORD,KWGETNEXTEXTENDED) , _SetDBOp } ;
syntax_node dbstmt8      = { &dbstmt16 , &dbstmt9  , TRUE , INITERM(KEYWORD,KWGETLAST) , _SetDBOp } ;
syntax_node dbstmt7      = { &dbstmt16 , &dbstmt8  , TRUE , INITERM(KEYWORD,KWGETFIRST) , _SetDBOp } ;
syntax_node dbstmt6      = { &dbstmt16 , &dbstmt7  , TRUE , INITERM(KEYWORD,KWGETLESSEQUAL) , _SetDBOp } ;
syntax_node dbstmt5      = { &dbstmt16 , &dbstmt6  , TRUE , INITERM(KEYWORD,KWGETLESS) , _SetDBOp } ;
syntax_node dbstmt4      = { &dbstmt16 , &dbstmt5  , TRUE , INITERM(KEYWORD,KWGETGREATEREQUAL) , _SetDBOp } ;
syntax_node dbstmt3      = { &dbstmt16 , &dbstmt4  , TRUE , INITERM(KEYWORD,KWGETGREATER) , _SetDBOp } ;
syntax_node dbstmt2      = { &dbstmt16 , &dbstmt3  , TRUE , INITERM(KEYWORD,KWGETPREV) , _SetDBOp } ;
syntax_node dbstmt1      = { &dbstmt16 , &dbstmt2  , TRUE , INITERM(KEYWORD,KWGETNEXT) , _SetDBOp } ;
syntax_node dbstmt       = { &dbstmt16 , &dbstmt1  , TRUE , INITERM(KEYWORD,KWGETEQUAL) , _SetDBOp } ;

syntax_node ntestfilter = { NULL , NULL         , TRUE , INITERM(KEYWORD,KWNOTTESTFILTER) , _SetNotTestFilter } ;
syntax_node repeat      = { NULL , &ntestfilter , TRUE , INITERM(KEYWORD,KWREPEAT) , _SetOnRepeat} ;
syntax_node onlock      = { NULL , &repeat      , TRUE , INITERM(KEYWORD,KWONLOCK) , _SetOnLock } ;
syntax_node testfilter  = { NULL , &onlock      , TRUE , INITERM(KEYWORD,KWTESTFILTER) , _SetTestFilter } ;
syntax_node forall      = { NULL , &testfilter  , TRUE , INITERM(KEYWORD,KWFORALL) , _SetForAll } ;
syntax_node onmore      = { NULL , &forall      , TRUE , INITERM(KEYWORD,KWONMORE) , _SetOnMore } ;
syntax_node error_type4 = { NULL , &onmore      , TRUE , INITERM(KEYWORD,KWONFATALERROR) , _SetOnFatalError } ;
syntax_node error_type3 = { NULL , &error_type4 , TRUE , INITERM(KEYWORD,KWONERROR) , _SetOnError } ;
syntax_node error_type2 = { NULL , &error_type3 , TRUE , INITERM(KEYWORD,KWONENDOFFILE) , _SetOnEndOfFile } ;
syntax_node error_type1 = { NULL , &error_type2 , TRUE , INITERM(KEYWORD,KWONRECNOTFOUND) , _SetOnRecNotFound } ;
syntax_node error_type  = { NULL , &error_type1 , TRUE , INITERM(KEYWORD,KWONSUCCESS) , _SetOnSuccess } ;

syntax_node cmdquest5    = { NULL       , NULL , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node cmdquest4    = { &cmdquest5 , NULL , TRUE  , INITERM(T_INTEGER,0) , _SetQuestedInt } ;
syntax_node cmdquest3    = { &cmdquest4 , NULL , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node cmdquest2    = { &cmdquest3 , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetQuestedPar } ;
syntax_node cmdquest1    = { &cmdquest2 , NULL , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node cmdquest     = { &cmdquest1 , NULL , TRUE  , INITERM(KEYWORD,KWIF) , _SetIf } ;

extern syntax_node parexist2;
syntax_node parexist5    = { NULL       , NULL       , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node parexist4    = { &parexist2 , &parexist5 , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node parexist3    = { &parexist4 , NULL       , TRUE  , INITERM(UNKNOWNIDENT,0) , _PushExParam } ;
syntax_node parexist2    = { &parexist3 , &parexist3 , TRUE  , INITERM(KEYWORD,KWNOT) , _NextParamNot } ;
syntax_node parexist1    = { &parexist2 , NULL       , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node parexist     = { &parexist1 , NULL       , TRUE  , INITERM(KEYWORD,KWONPARAM) , _SetOnParam } ;

syntax_node select_type3 = { NULL , NULL          , FALSE , &parexist   , NULL } ;
syntax_node select_type2 = { NULL , &select_type3 , FALSE , &cmdquest   , NULL } ;
syntax_node select_type1 = { NULL , &select_type2 , FALSE , &error_type , NULL } ;
syntax_node select_type  = { NULL , &select_type1 , FALSE , &op_type    , NULL } ;

extern syntax_node statement ;
extern syntax_node switchstmt2 ;
syntax_node switchstmt3 = { NULL         , &switchstmt2 , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , _LookupElse } ;
syntax_node switchstmt2 = { &switchstmt3 , NULL         , FALSE , &statement , NULL } ;
syntax_node switchstmt1 = { &switchstmt2 , NULL         , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN) , NULL } ;
syntax_node switchstmt  = { &switchstmt1 , NULL         , FALSE , &select_type , NULL } ;

extern syntax_node assert2 ;
syntax_node assert6 = { NULL     , NULL     , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node assert5 = { &assert6 , NULL     , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node assert4 = { &assert2 , &assert5 , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node assert3 = { &assert4 , NULL     , TRUE  , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node assert2 = { &assert4 , &assert3 , FALSE , &op_type , NULL } ;
syntax_node assert1 = { &assert2 , NULL     , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;
syntax_node assert  = { &assert1 , NULL     , TRUE  , INITERM(KEYWORD,KWASSERT) , NULL } ;

syntax_node logop1 = { NULL , NULL    , TRUE , INITERM(KEYWORD,KWOR) , _SetLogOp } ;
syntax_node logop  = { NULL , &logop1 , TRUE , INITERM(KEYWORD,KWAND) , _SetLogOp } ;

syntax_node cmpop8 = { NULL    , NULL    , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node cmpop7 = { NULL    , &cmpop8 , TRUE , INITERM(KEYWORD,KWCASEINSENSITIVE) , _SetCIOperator } ;
syntax_node cmpop6 = { &cmpop7 , NULL    , TRUE , INITERM(KEYWORD,KWCMNOTEQUAL) , _SetCmpOperator } ;
syntax_node cmpop5 = { &cmpop7 , &cmpop6 , TRUE , INITERM(KEYWORD,KWINLIST) , _SetCmpOperator } ;
syntax_node cmpop4 = { &cmpop7 , &cmpop5 , TRUE , INITERM(KEYWORD,KWCMLESSEQUAL) , _SetCmpOperator } ;
syntax_node cmpop3 = { &cmpop7 , &cmpop4 , TRUE , INITERM(KEYWORD,KWCMLESS) , _SetCmpOperator } ;
syntax_node cmpop2 = { &cmpop7 , &cmpop3 , TRUE , INITERM(KEYWORD,KWCMGREATEREQUAL) , _SetCmpOperator } ;
syntax_node cmpop1 = { &cmpop7 , &cmpop2 , TRUE , INITERM(KEYWORD,KWCMGREATER) , _SetCmpOperator } ;
syntax_node cmpop  = { &cmpop7 , &cmpop1 , TRUE , INITERM(KEYWORD,KWCMEQUAL) , _SetCmpOperator } ;

syntax_node cmp4   = { NULL  , NULL , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node cmp3   = { &cmp4 , NULL , FALSE , &expression , NULL } ;    
syntax_node cmp2   = { &cmp3 , NULL , FALSE , &cmpop , NULL } ;
syntax_node cmp1   = { &cmp2 , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetAssignFilter } ;
syntax_node cmp    = { &cmp1 , NULL , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;

extern syntax_node filter2;
syntax_node filter4 = { NULL     , NULL     , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetEndFilter } ;
syntax_node filter3 = { &filter2 , &filter4 , FALSE , &logop , NULL } ;
syntax_node filter2 = { &filter3 , NULL     , FALSE , &cmp , NULL } ;
syntax_node filter1 = { &filter2 , NULL     , TRUE  , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node filter  = { &filter1 , NULL     , TRUE  , INITERM(KEYWORD,KWFILTER) , _SetFilter } ;

extern syntax_node mfilter2;
syntax_node mfilter4 = { NULL      , NULL      , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetEndFilter } ;
syntax_node mfilter3 = { &mfilter2 , &mfilter4 , FALSE , &logop , NULL } ;
syntax_node mfilter2 = { &mfilter3 , NULL      , FALSE , &cmp , NULL } ;
syntax_node mfilter1 = { &mfilter2 , NULL      , FALSE , &logop , NULL } ;
syntax_node mfilter  = { &mfilter1 , NULL      , TRUE  , INITERM(KEYWORD,KWMFILTER) , _SetMoreFilter } ;

syntax_node _Push2 = { NULL    , NULL , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetAssignSize } ;
syntax_node _Push1 = { &_Push2 , NULL , FALSE , &expression , NULL } ;
syntax_node _Push  = { &_Push1 , NULL , TRUE  , INITERM(KEYWORD,KWPUSH) , _SetAssignPush } ;

syntax_node cascade2 = { NULL      , NULL      , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , _SetAssignSize } ;
syntax_node cascade1 = { &cascade2 , NULL      , FALSE , &expression , NULL } ;
syntax_node cascade  = { &cascade1 , NULL      , TRUE  , INITERM(KEYWORD,KWCALLCASCADE) , _SetAssignCascade } ;

syntax_node setreject2 = { NULL        , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node setreject1 = { &setreject2 , NULL , TRUE , INITERM(T_INTEGER,0) , _SetRejectCount } ;
syntax_node setreject  = { &setreject1 , NULL , TRUE , INITERM(KEYWORD,KWSETREJECT) , _SetReject } ;

syntax_node reqele5 = { NULL     , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node reqele4 = { &reqele5 , NULL , TRUE , INITERM(KEYWORD,KWVAR) , NULL } ;
syntax_node reqele3 = { &reqele4 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , NULL } ;
syntax_node reqele2 = { &reqele3 , NULL , TRUE , INITERM(KEYWORD,KWTABLE) , NULL } ;
syntax_node reqele1 = { &reqele2 , NULL , TRUE , INITERM(KEYWORD,KWEQUAL) , NULL } ;
syntax_node reqele  = { &reqele1 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , NULL } ;

extern syntax_node request1;
syntax_node request3 = { NULL      , NULL      , TRUE  , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node request2 = { &request1 , &request3 , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node request1 = { &request2 , NULL      , FALSE , &reqele , NULL } ;
syntax_node request  = { &request1 , NULL      , TRUE  , INITERM(KEYWORD,KWREQUEST) , NULL } ;

syntax_node msg2 = { NULL  , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node msg1 = { &msg2 , NULL , TRUE , INITERM(STRING,0) , _StoreMsg } ;
syntax_node msg  = { &msg1 , NULL , TRUE , INITERM(KEYWORD,KWMSG) , _SetOpMsg } ;

syntax_node abstmt2 = { NULL     , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node abstmt1 = { &abstmt2 , NULL , TRUE , INITERM(T_INTEGER,0) , _SetAbort } ;
syntax_node abstmt  = { &abstmt1 , NULL , TRUE , INITERM(KEYWORD,KWABORT) , NULL } ;

syntax_node locklist1    = { NULL       , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node locklist     = { &locklist1 , NULL , TRUE , INITERM(KEYWORD,KWPUSHTOLOCKLIST) , _PushToLockList } ;

syntax_node initializerec1 = { NULL            , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node initializerec  = { &initializerec1 , NULL , TRUE , INITERM(KEYWORD,KWINITREC) , _SetInitializeRec } ;

syntax_node _break1 = { NULL     , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node _break  = { &_break1 , NULL , TRUE , INITERM(KEYWORD,KWBREAK) , _SetBreak } ;

syntax_node _continue1 = { NULL     , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node _continue  = { &_continue1 , NULL , TRUE , INITERM(KEYWORD,KWCONTINUE) , _SetContinue } ;

syntax_node SetPrimKey1 = { NULL         , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node SetPrimKey  = { &SetPrimKey1 , NULL , TRUE , INITERM(KEYWORD,KWSETPRIMKEY) , _SetPrimKey } ;

syntax_node innerjoins1 = { NULL         , NULL , TRUE , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node innerjoins  = { &innerjoins1 , NULL , TRUE , INITERM(KEYWORD,KWINNERJOINS) , _SetJustInner } ;

syntax_node statement20 = { NULL , NULL         , FALSE , &innerjoins , NULL } ;
syntax_node statement19 = { NULL , &statement20 , FALSE , &SetPrimKey , NULL } ;
syntax_node statement18 = { NULL , &statement19 , FALSE , &mfilter , NULL } ;
syntax_node statement17 = { NULL , &statement18 , FALSE , &_Push , NULL } ;
syntax_node statement16 = { NULL , &statement17 , FALSE , &_continue , NULL } ;
syntax_node statement15 = { NULL , &statement16 , FALSE , &_break , NULL } ;
syntax_node statement14 = { NULL , &statement15 , FALSE , &cascade , NULL } ;
syntax_node statement13 = { NULL , &statement14 , FALSE , &locklist , NULL } ;
syntax_node statement12 = { NULL , &statement13 , FALSE , &initializerec , NULL } ;
syntax_node statement11 = { NULL , &statement12 , FALSE , &setreject , NULL } ;
syntax_node statement10 = { NULL , &statement11 , FALSE , &abstmt , NULL } ;
syntax_node statement9  = { NULL , &statement10 , FALSE , &msg , NULL } ;
syntax_node statement8  = { NULL , &statement9  , FALSE , &filter , NULL } ;
syntax_node statement7  = { NULL , &statement8  , FALSE , &request , NULL } ;
syntax_node statement6  = { NULL , &statement7  , FALSE , &extstmt , NULL } ;
syntax_node statement4  = { NULL , &statement6  , FALSE , &assignstmt , NULL } ;
syntax_node statement3  = { NULL , &statement4  , FALSE , &keystmt , NULL } ;
syntax_node statement2  = { NULL , &statement3  , FALSE , &dbstmt , NULL } ;
syntax_node statement1  = { NULL , &statement2  , FALSE , &switchstmt , NULL } ;
syntax_node statement   = { NULL , &statement1  , FALSE , &assert , NULL } ;

syntax_node mtype5  = { NULL , NULL    , TRUE , INITERM(KEYWORD,KWMDATE) , NULL } ;
syntax_node mtype4  = { NULL , &mtype5 , TRUE , INITERM(KEYWORD,KWDEC) , NULL } ;
syntax_node mtype3  = { NULL , &mtype4 , TRUE , INITERM(KEYWORD,KWSTRING) , NULL } ;
syntax_node mtype2  = { NULL , &mtype3 , TRUE , INITERM(KEYWORD,KWINT) , NULL } ;
syntax_node mtype1  = { NULL , &mtype2 , TRUE , INITERM(KEYWORD,KWLONG) , NULL } ;
syntax_node mtype   = { NULL , &mtype1 , TRUE , INITERM(KEYWORD,KWVOID) , NULL } ;

syntax_node parameter4 = { NULL        , NULL        , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node parameter3 = { &parameter4 , NULL        , TRUE  , INITERM(T_INTEGER,0) , NULL } ;
syntax_node parameter2 = { &parameter3 , &parameter4 , TRUE  , INITERM(KEYWORD,KWDOPPELPUNKT) , NULL } ;
syntax_node parameter1 = { &parameter2 , NULL        , TRUE  , INITERM(UNKNOWNIDENT,0) , _PushPar } ;
syntax_node parameter  = { &parameter1 , NULL        , FALSE , &mtype , NULL } ;

extern syntax_node access2;
extern syntax_node access6;
syntax_node access7 = { NULL     , &access6 , TRUE  , INITERM(KEYWORD,KWCURBRACECLOSE) , _SetPtrToNext } ;
syntax_node access6 = { &access7 , NULL     , FALSE , &statement , NULL } ;
syntax_node access5 = { &access7 , NULL     , TRUE  , INITERM(KEYWORD,KWCURBRACEOPEN) , NULL } ;
syntax_node access4 = { &access5 , NULL     , TRUE  , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node access3 = { &access2 , &access4 , TRUE  , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node access2 = { &access3 , NULL     , FALSE , &parameter , NULL } ;
syntax_node access1 = { &access2 , NULL     , TRUE  , INITERM(KEYWORD,KWBRACEOPEN) , _ClearParList } ;
syntax_node desc3   = { &access1 , &access1 , TRUE  , INITERM(KEYWORD,KWVIEWALLOWED) , _SetViewAllowed } ;
syntax_node desc2   = { &desc3   , NULL     , TRUE  , INITERM(STRING,0) , _SetAccDesc } ;
syntax_node desc1   = { &desc2   , &access1 , TRUE  , INITERM(KEYWORD,KWDESCRIPTION) , NULL } ;
syntax_node access  = { &desc1   , NULL     , TRUE  , INITERM(UNKNOWNIDENT,0) , _SetAccessName } ;

#ifdef UEBERLEGT
extern syntax_node accesslist1;
syntax_node accesslist2  = { NULL         , &accesslist1 , TRUE  , INITERM(KEYWORD,KWEND) , SetLastServerSource };
syntax_node accesslist1  = { &accesslist2 , NULL         , FALSE , &access , NULL };
syntax_node accesslist   = { &accesslist2 , NULL         , TRUE  , INITERM (KEYWORD,KWACCESS) , _SetPtrToRoot };
#else
syntax_node accesslist2  = { NULL         , NULL         , TRUE  , INITERM(KEYWORD,KWEND) , SetLastServerSource };
syntax_node accesslist1  = { &accesslist1 , &accesslist2 , FALSE , &access , NULL };
syntax_node accesslist   = { &accesslist1 , NULL         , TRUE  , INITERM (KEYWORD,KWACCESS) , _SetPtrToRoot };
#endif

syntax_node table5 = { NULL    , NULL     , FALSE , &accesslist    , NULL } ;
syntax_node table4 = { &table5 , NULL /* &table5 */ , FALSE , &alternatename , NULL } ;
syntax_node table3 = { &table3 , &table4  , FALSE , &key           , NULL } ;
syntax_node table2 = { &table3 , NULL     , FALSE , &record        , NULL } ;
syntax_node table1 = { &table2 , NULL     , FALSE , &fieldlist     , NULL } ;
syntax_node table  = { &table1 , NULL     , FALSE , &filename      , NULL } ;

syntax_node table_new1 = { NULL        , NULL        , FALSE , &accesslist    , NULL } ;
syntax_node table_new  = { &table_new1 , &table_new1 , FALSE , &alternatename , NULL } ;

/*-----< Managementfunktionen >--------*/
void TbBtrv::Clear ()
  {
  if (FileRef.ptr != NULL) FreeGlobMem (FileRef.ptr);
  LPVARTBL h = GetVarRef(TRUE);
  if (h != NULL) {
    GLOBALHANDLE hGmem = h->g.hGres;
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    }
  if (DescRef.ptr != NULL) FreeGlobMem (DescRef.ptr);
  {
  LPACCESSDEF act = GetFirstAccess (TRUE);
  for ( ; act != NULL ; ) {
    LPACCESSDEF h = GetNextAccess (act,TRUE);
    FreeGlobMem (act);
    act = h;
    }
  }
  {
  LPKEYDEF act = GetFirstKey (TRUE);
  for ( ; act != NULL ; ) {
    LPKEYDEF h = GetNextKey (act,TRUE);
    FreeGlobMem (act);
    act = h;
    }
  }
  }

DWORD Push(LPBTRVTABLE FAR &res,DWORD Size,LPVOID Ptr,WORD ptrSize,DWORD FAR *gSize)
  {
  DWORD nwSize = *gSize = Size + ptrSize;
  WIN_ASSERT (nwSize <= 0xFFFF);
  lmemcpy (LPSTR(res)+Size,Ptr,ptrSize);
  return Size;
  }

LPBTRVTABLE TbBtrv::Pack ()
  {
  LPVARTBL h = GetVarRef(TRUE);

  // Ermitteln der Gesamtgroesse
  DWORD Size = sizeof(*this) ;
  Size += GetBlockSize(FileRef.ptr) ;
  Size += GetBlockSize(DescRef.ptr) ;
  if (h != NULL)
    Size += h->gSize ;
  if (KeyRef.ptr != NULL) {
    Size += GetBlockSize(KeyRef.ptr) ;
    LPKEYDEF act  = GetNextKey(GetFirstKey(TRUE),TRUE);
    for ( ; act != NULL ; ) {
      Size += GetBlockSize(act);
      act  = GetNextKey(act,TRUE);
      }
    }

  g.hGmem = GlobalAlloc (GHND,Size);

  LPBTRVTABLE res = LPBTRVTABLE (GlobalLock (g.hGmem));
  res->g.hGmem      = g.hGmem;
  res->BlockType    = BlockType;
  res->bdsc         = bdsc;
  res->StructSize   = sizeof(*res);

  // Filename
  res->FileRef.offs   = Push (res,res->StructSize,FileRef.ptr,GetBlockSize(FileRef.ptr),&res->StructSize);
  // Beschreibung
  res->DescRef.offs   = Push (res,res->StructSize,DescRef.ptr,GetBlockSize(DescRef.ptr),&res->StructSize);
  // Felder
  if (h != NULL) {
    GLOBALHANDLE hGmem = h->g.hGres;
    h->g.hGres = 0;
    res->VartblRef.offs = Push (res,res->StructSize,h,h->gSize,&res->StructSize);
    h->g.hGres = hGmem;
    }
  else
    res->VartblRef.offs = 0L;
  // Schluessel
  if (KeyRef.ptr != NULL) {
    res->KeyRef.offs = Push (res,res->StructSize,KeyRef.ptr,GetBlockSize(KeyRef.ptr),&res->StructSize);
    LPKEYDEF prev = res->GetFirstKey (FALSE);
    LPKEYDEF act  = GetNextKey(GetFirstKey(TRUE),TRUE);
    for ( ; act != NULL ; ) {
      prev->next.offs = Push (res,res->StructSize,act,GetBlockSize(act),&res->StructSize);
      prev = res->GetNextKey (prev,FALSE);
      act  = GetNextKey(act,TRUE);
      }
    }

  return res;
  }

/*-----------------------------------------------------------*/
/*  Compilieren einer Tabelle                                */
/*-----------------------------------------------------------*/
#define MAXHANDLES  50

struct {
  LPVOID       ptr;
  GLOBALHANDLE hGmem;
  } ptrtohandle[MAXHANDLES];
void PushHandle (LPVOID ptr,GLOBALHANDLE hGmem)
  {
  for (int i = 0 ; i < MAXHANDLES ; i++) {
    if (ptrtohandle[i].ptr == NULL) {
      ptrtohandle[i].ptr   = ptr;
      ptrtohandle[i].hGmem = hGmem;
      return;
      }
    }
  WIN_ASSERT (FALSE);
  }

GLOBALHANDLE GetHandle (LPVOID ptr)
  {
  for (int i = 0 ; i < MAXHANDLES ; i++) {
    if (ptrtohandle[i].ptr == ptr) {
      ptrtohandle[i].ptr   = NULL;
      return ptrtohandle[i].hGmem ;
      }
    }
  WIN_ASSERT (FALSE);
  return 0;
  }

DLLExport LPVOID _export WINAPI DataDict_TableDef (LPVOID InitData,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  hGLastServerSource = 0;
  TableCompiler FAR *t = new TableCompiler ();

  lstrcpy (t->fmname,"Tabellendefinition");
  cTbComp = t;
  _lastDesc = NULL;
  ViewAllowed = FALSE ;
  AvoidAssign = FALSE;
  t->DoParse (TableString,&table,NULL);
  endCmdPtr = OffsPtr = 0;
  if (_lastDesc != NULL)
    FreeGlobMem (_lastDesc) , _lastDesc = NULL;
  LPBTRVTABLE res;
  if (t->wError)
    res = NULL , *size = 0 , *error = TRUE ;
  else
    res = cTable->Pack() , *size = res->StructSize , *error = FALSE ;
  delete t;
  if (cTable != NULL) {
    cTable->Clear ();
    FreeGlobMem (cTable) , cTable = NULL ;
    }

  if (res != NULL) {
    PushHandle (res,res->g.hGmem);
    res->g.hGmem = 0;
    }
  return res;
  }

/*-----------------------------------------------------------*/
/*  Freigeben der Tabellendefinition nach dem Speichern .... */
/*-----------------------------------------------------------*/
DLLExport void _export WINAPI DataDict_FreeTableDef (LPVOID TableDef)
  {
  GLOBALHANDLE hGmem = GetHandle (TableDef);
  GlobalUnlock (hGmem);
  GlobalFree (hGmem);
  }

/*-----------------------------------------------------------*/
/*  Liste aller Zugriffe                                     */
/*-----------------------------------------------------------*/
DLLExport LPACCESSLISTENTRY _export WINAPI DataDict_GetAccessList (LPVOID DLLData)
  {
  LPBTRVTABLE cTable = LPBTRVTABLE (DLLData);
  LPACCESSLISTENTRY res = NULL;
  for ( LPACCESSDEF h = cTable->GetFirstAccess () ; h != NULL ;
                          h = cTable->GetNextAccess (h) ) {
    LPSTR Desc = h->GetDescription();
    LPACCESSLISTENTRY n = LPACCESSLISTENTRY (GetGlobMem (sizeof(*n)));
    n->Next = res ;
    n->Name        = LPSTR(GetGlobMem (lstrlen(h->Name)+1));
    lstrcpy (n->Name,h->Name);
    if ((Desc != NULL) && (*Desc)) {
      n->Description = LPSTR(GetGlobMem (lstrlen(Desc)+1));
      lstrcpy (n->Description,Desc);
      }
    res = n;
    }
  return res;
  }

// Untersuchung, ob Zugriff fuer View geeignet ist
//////////////////////////////////////////////////////////////
DLLExport BOOL _export WINAPI DataDict_IsAccessForView (LPVOID DLLData,LPSTR SelectionName)
  {
  LPBTRVTABLE cTable = LPBTRVTABLE (DLLData);
  LPACCESSDEF access = cTable->GetAccess (SelectionName,FALSE);
  return access->ViewAllowed;
  }

DLLExport GLOBALHANDLE _export WINAPI DataDict_LastServerSource ()
  {
  if (hGLastServerSource)
    return hGLastServerSource;
  else
    return 0;
  }

/*-------< Tabellen - Generator nach der neuen Konvention >---------*/
WORD GetBTRVDataType (LPTABLEDEF td,WORD VarNr,WORD mType,WORD varSize)
  {
  // Untersuchen, ob die Variable in einem Schluessel vorkommt
  BOOL IsAutoinc = FALSE ;
  for (int i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    LPCLKEYDEF k = td->GetKeyDef (i) ;
    if ((k->VarID == VarNr) && ((k->Attribute & CLKD_AUTOINC) != 0))
      IsAutoinc = TRUE ;
    }
  if (IsAutoinc) return BDT_AUTOINC ;
  else {
    static struct mTypeToBType { WORD mType ; WORD bType ; } mtb [] = {
      { VAR_LONG  , BDT_INTEGER } ,
      { VAR_DEC   , BDT_FLOAT   } ,
      { VAR_STR   , BDT_ZSTRING } ,
      { VAR_POINT , DT_PRIVATE  } ,
      { VAR_CONT  , DT_SPRIVATE } ,
      { VAR_STRARR, BDT_INTEGER } ,
      { VAR_FLAG  , BDT_INTEGER } ,
      { VAR_SCALE , BDT_STRING  } ,
      { VAR_DATE  , BDT_DATE    } ,
      { VAR_TIME  , BDT_TIME    } ,
      { VAR_DWORD , BDT_INTEGER } ,
      { VAR_OBJ   , DT_SPRIVATE } ,
      { VAR_QLONG , DT_PRIVATE  } ,
      { VAR_DATETIME , DT_PRIVATE  }
      };
    #define ANZKW (sizeof(mtb) / sizeof (mTypeToBType))
    for (int i = 0 ; i < ANZKW ; i++) {
      if (mType == mtb[i].mType) {
        // Sonderbehandlungen beruecksichtigen
        if ((mType == VAR_DEC) && (varSize == 2))
          return BDT_INTEGER ;
        return mtb[i].bType ;
        }
      }
    WIN_ASSERT (FALSE);
    }
  return BDT_STRING ;
  }

extern void CompleteVarDef (LPTABLEDEF td,LPBTRVTABLE t);
//int ExtraOffs (WORD mType,int j) { if (mType == VAR_DATETIME) return (j == 1) ? 0 : 4 ; else return 0 ; }
//int ExtraLen (WORD mType,int j) { if (mType == VAR_DATETIME) return 4 ; else return 0 ; }
//int ExtraType (WORD mType,int j) { if (mType == VAR_DATETIME) { return (j == 0) ? BDT_DATE : BDT_TIME ; } else return 0 ; }
int ExtraOffs (WORD mType,int j) { return 0 ; }
int ExtraLen (WORD mType,int j) { return 0 ; }
int ExtraType (WORD mType,int j) { if (mType == VAR_DATETIME) return BDT_UNSIGNED ; else return 0 ; }
int AnzSegsPreVar (int mType)
  {
  // return (mType == VAR_DATETIME) ? 2 : 1 ;
  return 1 ;
  }
DLLExport LPVOID _export WINAPI DataDict_NewTableDef (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  LPTABLEDEF td = LPTABLEDEF (ClientTable);
  cTable = LPBTRVTABLE(GetGlobMem (sizeof(*cTable)));
  cTable->SetFileRef(td->GetName());

  // Erstellen der Variablendeklaration
  _lastDesc = NULL;
  BOOL correct = TRUE ;
  WORD VarOffs = 0;
  BOOL BlockIsPushed = FALSE ;
  BOOL BlobIsPushed = FALSE ;
  BOOL doCompress = TRUE ;
  for (int i = 0 ; ((i < td->GetAnzVars()) && (correct)) ; i++) {
    LPVARDEF v = td->GetVarDef(i);
    if (v->mType == VAR_BLOB) {
      doCompress = FALSE ;
      if (BlockIsPushed) correct = FALSE ;
      else {
        BlobIsPushed = TRUE ;
        cTable->PushVar (v->name,GetBTRVDataType (td,i,VAR_OBJ,sizeof(DWORD)),
                        VarOffs,sizeof(DWORD),1);
        VarOffs += sizeof(DWORD);
        }
      }
    else if (v->VarID == 0xFFFF) {
      // Es handelt sich um eine direkt gemappte Variable
      if (BlobIsPushed) correct = FALSE ;
      else {
        cTable->PushVar (v->name,GetBTRVDataType (td,i,v->mType,v->VarSize),
                        VarOffs,v->VarSize,1);
        VarOffs += v->VarSize;
        }
      }
    else {
      if (BlobIsPushed) correct = FALSE ;
      BlockIsPushed = TRUE ;
      }
    }
  if (BlockIsPushed)
    cTable->BlockType = BLOCKTYPE_MARILLE1 ; cTable->bdsc.lOffset = VarOffs;

  // Initialisieren des Records
  if (correct) {
    cTable->InitialiseDesc () ;
    cTable->GetDescRef(TRUE)->SetRecordSize(VarOffs) ; 
    _PrepVarBit ();
    if (BlockIsPushed | BlobIsPushed)
      _SetBit ();
    else
      _ClearBit ();
    if (doCompress) {
      _PrepCompBit ();
      _SetBit ();
      }
    cTable->GetDescRef(TRUE)->SetPageSize(4096);
    }

  // Initialisieren der Schluessel
  BOOL AltDone = FALSE ;
  if (correct) {
    WORD OldKeyNr = 0xFFFF;
    _SetFirstKey ();
    for (i = 0 ; i < td->GetAnzKeySegs() ; i++) {
      LPCLKEYDEF k = td->GetKeyDef (i) ;
      LPVARDEF v = td->GetVarDef(k->VarID);
      for ( int j = 0 ; j < AnzSegsPreVar (v->mType) ; j++) {
        if (k->KeyNmbr != OldKeyNr) {
          if (OldKeyNr != 0xFFFF) _IncAnzKeys ();
          SetKeyName (k->name);
          OldKeyNr = k->KeyNmbr;
          }
        else
          _SetSeg ();
        _AddKeySegment ();
        SetKeyDesc (v->GetName(),td->IsRealTable(),ExtraOffs (v->mType,j),ExtraLen (v->mType,j),ExtraType (v->mType,j),(k->Attribute & CLKD_AUTOINC) == 0) ;
        _PrepDuplicate ();
        if (k->Attribute & CLKD_UNIQUE)
          _ClearBit ();
        else
          _SetBit ();
        _PrepModifiable () ;
        if (k->Attribute & CLKD_MODIFYABLE)
          _SetBit ();
        else
          _ClearBit ();
        _PrepAlt ();
        if (v->mType == VAR_STR)
          _SetBit () , AltDone = TRUE ;
        else
          _ClearBit ();
        }
      }
    if (td->GetAnzKeySegs() > 0)
      _IncAnzKeys ();
    }

  // Noch den Alternate Namen ...
  if (AltDone)
    cTable->LoadAltSeq ("SOFTWORK.ALT");

  // So jetzt gehts erst richtig los
  TableCompiler FAR *t = new TableCompiler ();

  lstrcpy (t->fmname,"Tabellendefinition");
  cTbComp = t;
  ViewAllowed = FALSE ;
  AvoidAssign = FALSE;
#ifdef UEBERLEGT
  if (correct)
    t->DoParse (TableString,&table_new,NULL);
  else
    t->wError = ERROR_NOTIMPLEMENTED;
#else
  t->wError = 0;
#endif
  endCmdPtr = OffsPtr = 0;
  if (_lastDesc != NULL)
    FreeGlobMem (_lastDesc) , _lastDesc = NULL;
  LPBTRVTABLE res;
  if (t->wError)
    res = NULL , *size = 0 , *error = TRUE , correct = FALSE ;
  else
    res = cTable->Pack() , *size = res->StructSize , *error = FALSE ;
  delete t;
  if (cTable != NULL) {
    cTable->Clear ();
    FreeGlobMem (cTable) , cTable = NULL ;
    }

  if (res != NULL) {
    PushHandle (res,res->g.hGmem);
    res->g.hGmem = 0;
    }

  // So jetzt noch die Variablen einzeln eintragen
  if (correct)
    CompleteVarDef (td,res);

  return res;
  }
