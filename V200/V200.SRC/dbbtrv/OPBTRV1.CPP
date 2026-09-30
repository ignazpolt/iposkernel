////////////////////////////////////////////////////////////////////////
//  Durchfuehren der eigentlichen Operationen, SQL - Emulation
////////////////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/dbbtrv/rev/opbtrv1.cpv   1.94   18 Feb 1999 11:07:14   Martin  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/opbtrv1.cpv  $
// 
//    Rev 1.94   18 Feb 1999 11:07:14   Martin
// DT_SPRIVATE im Filter umgemappt auf BDT_BINARY
// 
//    Rev 1.93   13 Oct 1998 13:04:44   Gerhold
// HINSTANCE hLibInst wegen VC6
// 
//    Rev 1.92   17 Aug 1998 16:41:46   Hannes
// DBWIN_ASSERT bei Anzahl Parameter
// 
//    Rev 1.91   10 Aug 1998 17:03:50   Hannes
// Umstellen des Timestamps auf UNSIGNED
// 
//    Rev 1.90   04 Aug 1998 17:55:58   Hannes
// Timestamp
// 
//    Rev 1.89   29 Jun 1998 19:07:20   Hannes
// 
//    Rev 1.88   19 Mar 1998 10:22:32   Hannes
// Fehlerkorrektur PerformInsert
// 
//    Rev 1.87   17 Mar 1998 08:37:08   Hannes
// Fehlerkorrekturen im Protokollieren
// 
//    Rev 1.86   06 Mar 1998 17:07:14   Hannes
// 
//    Rev 1.85   23 Feb 1998 20:44:44   Hannes
// 
//    Rev 1.84   02 Feb 1998 20:35:06   Hannes
// Verbesserungen bei der Commandoermittlung in GetBestKey -> NextDBOpFor
// 
//    Rev 1.83   12 Jan 1998 18:13:06   Hannes
// Chuncks variabl gross
// 
//    Rev 1.82   16 Dec 1997 18:05:38   Hannes
// Dynamische Rejectcountvergroesserung
// 
//    Rev 1.81   01 Dec 1997 19:40:02   Hannes
// Diverse Anpassungen / Replikator
// 
//    Rev 1.80   10 Nov 1997 10:50:14   Hannes
// MakeTimeStamp
// 
//    Rev 1.79   08 Sep 1997 12:20:12   Hannes
// diverse Verbesserungen
// 
//    Rev 1.78   26 Aug 1997 12:25:00   Hannes
// DelRecs... Fehler 22 ignorieren
// 
//    Rev 1.77   18 Jul 1997 11:02:40   Hannes
// 
//    Rev 1.76   18 Jul 1997 08:06:38   Hannes
// 
//    Rev 1.75   01 Jul 1997 12:15:32   Hannes
// 
//    Rev 1.74   28 May 1997 15:28:46   Hannes
// Fehlerkorrektur bei Eindeutigen Schluesseln
// 
//    Rev 1.73   05 May 1997 10:36:54   Hannes
// 
//    Rev 1.72   08 Apr 1997 09:22:20   Hannes
// GetFurtherRecs -> GETFULL -> REJECTCOUNT wird nicht mehr ueberprueft
// 
//    Rev 1.71   29 Jan 1997 14:37:12   HANNES
// Compare bei Stringkeys
// 
//    Rev 1.70   29 Jan 1997 13:02:08   HANNES
// 
//    Rev 1.69   12 Dec 1996 14:20:40   HANNES
// 
//    Rev 1.68   28 Nov 1996 14:15:02   HANNES
// Auch die Parametertypen an die Suquerys weitergeben
// 
//    Rev 1.67   27 Nov 1996 15:53:26   HANNES
// 
//    Rev 1.66   26 Nov 1996 08:00:30   HANNES
// Automatischer Update
// 
//    Rev 1.65   08 Nov 1996 13:26:52   HANNES
// QLong, Replikator
// 
//    Rev 1.64   30 Oct 1996 19:34:22   HANNES
// In Liste Datensatz einzeln abholen
// 
//    Rev 1.63   04 Oct 1996 18:08:42   MARTIN
// SegInfo: wenn in einem Unterbaum das Schluesselsegment verwendet ist,
// und im anderen nicht, dann darf bei einer OR-Verknuepfung der beiden
// dieser Teilbaum nicht verwendet werden.
// 
//    Rev 1.62   02 Oct 1996 16:14:18   MARTIN
// gefaehrliche Aenderung: TestBtrieveSyntax ist jetzt restriktiver
// (jetzt muessen im linken Unterbaum lauter gleiche logische Verknuepfungen
// sein, also auch in rechten Verzweigungen desselben)
// 
//    Rev 1.61   13 Sep 1996 16:45:32   HANNES
// 
//    Rev 1.60   12 Sep 1996 23:11:30   HANNES
// GetInsertRecord ... Fehlerkorrekturen
// 
//    Rev 1.59   06 Sep 1996 11:44:16   HANNES
// Fehler beim GETEQ
// 
//    Rev 1.58   03 Sep 1996 10:08:10   HANNES
// Verbessertes Log
// Abbruchbedingung bei OP_GET
// 
//    Rev 1.57   05 Jul 1996 16:57:46   MARTIN
// DoLog ...
// 
//    Rev 1.56   28 Jun 1996 17:14:46   MARTIN
// Clear() defensiver
// 
//    Rev 1.55   28 Jun 1996 15:30:12   MARTIN
// einige Fehlerkorrekturen
// 
//    Rev 1.54   17 Jun 1996 15:38:46   HANNES
// Einbau von BLOBS
// 
//    Rev 1.45   25 Apr 1996 16:49:32   MARTIN
// req->AnzParam in SubQuerys richtig gesetzt
// 
//    Rev 1.44   04 Apr 1996 18:16:52   HANNES
// 
//    Rev 1.43   26 Mar 1996 17:29:28   MARTIN
// WIN_ASSERT, wenn zu wenig Parameter im Script angegeben sind
// 
//    Rev 1.42   23 Mar 1996 23:11:42   MARTIN
// Testfilter ...
// 
//    Rev 1.41   22 Feb 1996 19:02:56   MARTIN
// doWait nachgebessert
// 
//    Rev 1.40   12 Feb 1996 17:29:06   MARTIN
// Testfilter zuruecksetzen
// 
//    Rev 1.39   04 Feb 1996 21:42:08   HANNES
// 
//    Rev 1.38   04 Feb 1996 17:28:18   HANNES
// 
//    Rev 1.37   04 Feb 1996 15:38:02   HANNES
// 
//    Rev 1.36   02 Feb 1996 10:42:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.34   08 Jan 1996 15:13:50   HANNES
// Statustest beim Update
// 
//    Rev 1.33   16 Nov 1995 19:13:58   HANNES
// BinTree Fehler
// 
//    Rev 1.32   16 Nov 1995 17:57:38   HANNES
// IN Statement, die 24.
// 
//    Rev 1.31   15 Nov 1995 15:42:26   HANNES
// Fehlerkorrektur im IN Statement: IN Statement fuer Liste mit 1 Element
// 
//    Rev 1.30   13 Nov 1995 18:45:30   HANNES
// IN Statement
// 
//    Rev 1.29   10 Nov 1995 12:23:14   MARTIN
// Korrekturen Hannes
// 
//    Rev 1.27   02 Nov 1995 19:12:36   martin
// 
//    Rev 1.26   22 Sep 1995 15:44:58   MARTIN
// GetNextEmptySegmentDBOp korrigiert
// 
//    Rev 1.25   14 Sep 1995 22:39:22   HANNES
// 
//    Rev 1.24   07 Sep 1995 09:04:20   HANNES
// 
//    Rev 1.23   01 Sep 1995 09:03:08   HANNES
// Verbesserung des SQL Interpreters
// 
//    Rev 1.22   24 Aug 1995 00:21:04   HANNES
// 
//    Rev 1.21   25 Jul 1995 12:03:38   HANNES
// 
//    Rev 1.20   25 Jul 1995 10:40:16   HANNES
// Verbesserte Filterpruefung
// 
//    Rev 1.19   14 Jul 1995 16:55:00   HANNES
// Insert ohne GetDirect
// 
//    Rev 1.18   14 Jun 1995 13:10:18   HANNES
// FreeTempararyTable auf jeden Fall aufgerufen
// 
//    Rev 1.17   09 Jun 1995 00:25:20   HANNES
// Rejectcountermittlung ... Optimierungsabnahme von Btrieve - Bloedheiten
// 
//    Rev 1.16   29 May 1995 14:39:30   HANNES
// 
//    Rev 1.15   29 May 1995 12:46:42   martin
// Retries bei Locking - Problemen
// 
//    Rev 1.14   25 May 1995 18:18:48   HANNES
// 
//    Rev 1.13   25 May 1995 17:46:04   HANNES
// 
//    Rev 1.12   24 May 1995 17:11:46   HANNES
// Cache Verwaltung fuer DBOP_GET innerlhalb eines DBOP_GETLIST im SatisfyJoin
// 
//    Rev 1.11   20 May 1995 16:18:28   HANNES
// Statustest beim Update
// 
//    Rev 1.10   09 May 1995 17:09:52   HANNES
// Behandlung der = Bearbeitung bei GetLast
// 
//    Rev 1.9   08 May 1995 17:15:18   HANNES
// Aenderung der Sortierung mitberuecksichtigen
// 
//    Rev 1.8   04 May 1995 18:39:02   HANNES
// 
//    Rev 1.7   26 Apr 1995 15:33:20   HANNES
// 
//    Rev 1.6   03 Apr 1995 18:51:08   HANNES
// 
//    Rev 1.5   03 Apr 1995 15:10:58   HANNES
// 
//    Rev 1.4   02 Apr 1995 18:23:58   JOERG
// 
//    Rev 1.3   27 Mar 1995 13:19:10   HANNES
// 
//    Rev 1.2   20 Mar 1995 12:10:26   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.1   24 Feb 1995 11:14:26   HANNES
//  
// 
//    Rev 1.0   16 Feb 1995 12:45:50   HANNES
// Initial revision.
// 
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 146
#include "winass.hpp"
#include "tbkw.h"
#include "tbfnc.hpp"
#include "dbrecord.hpp"
#include "btrieve.hpp"
#include "opbtrv.hpp"
#include "hash.hpp"

#include "compile.hpp"

extern "C" {
#include "wbtrv.h"
  }
#include "tbkw.h"

/*
**  Caching von einzelnen Gets
*/
class FAR CacheEntry;
CacheEntry FAR *CacheList;
class FAR CacheEntry {
 private :
  LPVOID Param[CB_PARAM];
  LPSTR  SelectionName;
  LPSTR  FileName;
 public :
  LPVOID rBuffer;
  WORD bufferSize;
  CacheEntry FAR *Next;
  CacheEntry (LPVOID buffer,WORD size,LPSTR FName,LPDBREQUEST req)
    {
    SelectionName = LPSTR(GetGlobMem (lstrlen(req->SelectionName)+1));
    lstrcpy (SelectionName,req->SelectionName);
    FileName = LPSTR(GetGlobMem (lstrlen(FName)+1));
    lstrcpy (FileName,FName);
    for (int i = 0 ; i < CB_PARAM ; i++) {
      if (req->Param[i] != NULL) {
        Param[i] = GetGlobMem (GetBlockSize(req->Param[i]));
        lmemcpy (Param[i],req->Param[i],GetBlockSize(Param[i]));
        }
      }
    rBuffer = GetGlobMem (size);
    WIN_ASSERT (rBuffer != NULL);
    bufferSize = size ;
    lmemcpy (rBuffer,buffer,size);

    Next = CacheList ;
    CacheList = this ;
    }
  ~CacheEntry ()
    {
    if (rBuffer) FreeGlobMem (rBuffer);
    if (SelectionName != NULL) FreeGlobMem (SelectionName);
    if (FileName != NULL) FreeGlobMem (FileName);
    for (int i = 0 ; i < CB_PARAM ; i++)
      if (Param[i] != NULL) FreeGlobMem (Param[i]);
    }
  BOOL CheckEntry (LPDBREQUEST req,LPBTRSTATEMENT stmt)
    {
    if (stmt->File == NULL) return FALSE ;
    if (stmt->File->btrBuffer == NULL) return FALSE ;
    if (lstrcmp (stmt->File->Path,FileName)) return FALSE ;
    if (lstrcmp (req->SelectionName,SelectionName)) return FALSE ;
    for (int i = 0 ; i < CB_PARAM ; i++) {
      if ((Param[i] == NULL) && (Param[i] == NULL)) continue ;
      if ((Param[i] != NULL) && (req->Param[i] != NULL) && 
          (GetBlockSize(Param[i]) == GetBlockSize(req->Param[i])) &&
          (lmemcmp (Param[i],req->Param[i],GetBlockSize(Param[i])))) continue ;
      return FALSE ;
      }
    return TRUE ;
    }
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj) 
    { FreeGlobMem (obj); }
  };

static BOOL DoCache ;
static int CacheOnCount ;
void CacheOff ()
  {
  if (-- CacheOnCount == 0) {
    for ( ; CacheList != NULL ; ) {
      CacheEntry FAR *Next = CacheList->Next ;
      delete CacheList ;
      CacheList = Next ;
      }
    DoCache = FALSE ;
    }
  }

void CacheOn ()
  {
  DoCache = TRUE ;
  CacheOnCount ++ ;
  }

#define REJECT_COUNT    60
#define REJECT_NOMORE   64

#define CTYPE_PARAMETER 0
#define CTYPE_INTEGER   1
#define CTYPE_DEC       2
#define CTYPE_STRING    3
class FAR PKeyList;
class FAR SQLCompiler;
class FAR BinTree;
typedef BinTree FAR *LPBINTREE;
struct FAR AggregatList {
  AggregatList FAR *Next;
  LPSTR Str;
  BYTE ActSFnc ;
  };
struct FAR StringArray {
  int AnzStrings;
  LPSTR FAR *Strs;

  void Init()
    { 
    AnzStrings = 0 ;
    Strs = NULL;
    };
  void Clear()
    {
    for (int i = 0 ; i < AnzStrings ; i++) {
      FreeGlobMem (Strs[i]) ;
      }
    if (Strs != NULL) {
      FreeGlobMem (Strs);
      Strs = NULL;
      }
    }
  void Push(LPSTR str)
    {
    LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzStrings + 1) * sizeof(LPSTR));
    if (Strs != NULL) {
      lmemcpy (n,Strs,AnzStrings * sizeof(LPSTR));
      FreeGlobMem (Strs) ;
      }
    Strs = n;
    n[AnzStrings] = LPSTR (GetGlobMem (lstrlen(str)+1));
    lstrcpy (n[AnzStrings],str);
    AnzStrings ++ ;
    }
  };
struct FAR PosArray {
  WORD AnzPos;
  DWORD FAR *Pos;
  void Init()
    { 
    AnzPos = 0 ;
    Pos = NULL;
    };
  void Clear()
    {
    if (Pos != NULL) {
      FreeGlobMem (Pos);
      Pos = NULL;
      }
    }
  void Push (DWORD p)
    {
    DWORD FAR *n = (DWORD FAR *) GetGlobMem ((AnzPos + 1) * sizeof(DWORD));
    if (Pos != NULL) {
      lmemcpy (n,Pos,AnzPos * sizeof(DWORD));
      FreeGlobMem (Pos) ;
      }
    Pos = n;
    n[AnzPos] = p ;
    AnzPos ++ ;
    }
  void Enlarge (int AnzRecords)
    {
    DWORD FAR *n = (DWORD FAR *) GetGlobMem ((AnzPos + AnzRecords) * sizeof(DWORD));
    if (Pos != NULL) {
      lmemcpy (n,Pos,AnzPos * sizeof(DWORD));
      FreeGlobMem (Pos) ;
      }
    Pos = n;
    AnzPos += AnzRecords ;
    }
  void SetPos (int j,DWORD p)
    {
    Pos[j] = p;
    }
  };
struct FAR LocalData {
  LPBTRSTATEMENT stmt;
  LPBTRVTABLE t;
  LPTABLEDEF td;
  PKeyList FAR *PossibleKeys;
  SQLCompiler FAR *SQLCmp;
  BOOL    ExpRead;
  LPVBTRV VarToCheck;
  BYTE    ActCompCode,ActSFnc;
  BOOL    DontCheckExtremes()
    { return (ActSFnc != 0) ; }
  int     rbufferCnt;
  BinTree FAR *rbuffer[32];
  int     cCnt;
  BYTE    cnType[32];
  int     tCnt;
  BYTE    tType[32];
  int     oCnt;
  BYTE    oType[32];
  WORD FAR *actDBOp;
  LPSTR SubQueryStart;
  DBRecord FAR *updateRecord;
  int varToUpdate;
  BOOL performMore;

  StringArray VarNames;
  StringArray TableNames;
  StringArray UpdateCommands;
  PosArray UpdatePos;
  AggregatList FAR *aList;
  void PushPos ()
    { UpdatePos.Push (stmt->recPosition); }
  BOOL performUpdate;
  BOOL performDelete;
  BOOL performInsert;

  void PushConnType (BYTE ct)
    {
    if (cCnt < 32)
      cnType[cCnt++] = ct ;
    }
  BYTE PopConnType ()
    {
    return (cCnt > 0) ? cnType[-- cCnt] : 0 ;
    }
  void PushDataType (BYTE ct)
    {
    if (tCnt < 32)
      tType[tCnt++] = ct ;
    }
  BYTE PopDataType ()
    {
    return (tCnt > 0) ? tType[-- tCnt] : 0 ;
    }
  void PushAOp (BYTE ct)
    {
    if (oCnt < 32)
      oType[oCnt++] = ct ;
    }
  BYTE PopAOp ()
    {
    return (oCnt > 0) ? oType[-- oCnt] : 0 ;
    }
  void PushPointer (BinTree FAR *r)
    { rbuffer[rbufferCnt++] = r ; }
  BinTree FAR *PopPointer ()
    { return (rbufferCnt > 0) ? rbuffer[--rbufferCnt] : NULL ; }
  void RemoveAggregatList ()
    {
    for ( AggregatList FAR *h = aList ; h != NULL ; ) {
      AggregatList FAR *Next = h->Next ;
      if (h->Str != NULL) FreeGlobMem (h->Str) ;
      FreeGlobMem (h);
      h = Next ;
      }
    }
  void PushToAggregatList ()
    {
    AggregatList FAR *n = (AggregatList FAR *) GetGlobMem (sizeof(*n)) ;
    n->Next = aList ;
    aList = n ;
    LPSTR Name = VarNames.Strs[VarNames.AnzStrings-1] ;
    n->Str = LPSTR (GetGlobMem (lstrlen(Name)+1));
    lstrcpy (n->Str,Name);
    n->ActSFnc = ActSFnc ;
    }
  LPSTR outCmd;
  DWORD startT;
  DWORD endT;
  };
LocalData *Context;

/*------< Hilfsfunktionen fuer Datenbankzugriffe >-----*/
static void Fehler (LPSTR str)
  {
  char outstr[256];
  wsprintf (outstr,"SQLINT-Fehler: %s (%s)",str,Context->stmt->File->Name);
  WIN_ASSERT_TEXT (FALSE,outstr);
  }

static char *illegalCmp = "Unerlaubter Vergleich";
static char *illegalConnect = "Unerlaubte Verknüpfung";
static char *doubleInitialized = "Doppelte Initialisierung";
static char *NoKey = "Kein Schlüssel für Sortierung gefunden";
static char *ToManyKeys = "Kein eindeutiger Schlüssel gefunden";
static char *NotBtrieveCompatible = "Nicht mit Btrieve auswertbar";
class FAR PKeyList {
 public :
  PKeyList FAR *Next;
  LPKEYDEF k;
  LPVOID KeyBuffer;
  int AnzSegsDone;
  WORD B_Command;
  // Fuer Order - Statement
  LPVBTRV SegToTest;
  BOOL SegInitDone;

  void SetSegmentValue (LPVBTRV v,LPVOID val);
  BOOL IsAllDone ();
  void FillSegmentValue (LPVBTRV v,WORD DBOp,WORD BCommand);
  int  TestKey (BinTree FAR *t,BOOL FAR *allDone,WORD DBOp,BOOL FAR *IsValid);
  BOOL CheckKeySegment (LPSTR Name);

  PKeyList (LPKEYDEF kd)
    { k = kd ; KeyBuffer = GetGlobMem (k->KeySize) ; }
  ~PKeyList ()
    { FreeGlobMem (KeyBuffer) ; }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };

BOOL PKeyList::IsAllDone ()
  {
  int i = 0;
  if (k != NULL) {
    LPVARTBL h = LPVARTBL (k->Name + lstrlen(k->Name) + 1) ;
    if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
      LPVBTRV x = &h->v[0];
      for ( ; (x != NULL) ; i++ , x = x->Next(h->gSize,h)) ;
      }
    }
  return ((i > 0) && (AnzSegsDone == i)) ;
  }

void PKeyList::SetSegmentValue (LPVBTRV v,LPVOID val)
  {
  lmemcpy (LPSTR(KeyBuffer)+v->VarOffset,val,v->VarLen);
  }
#define OPGET       0
#define OPGETFIRST  1
#define OPGETLAST   2
void PKeyList::FillSegmentValue (LPVBTRV v,WORD DBOp,WORD BCommand)
  {
  if ((DBOp == OPGET) || (DBOp == OPGETFIRST)) {
    if (BCommand == B_GETGT)
      v->SetMaxData (LPSTR(KeyBuffer)+v->VarOffset);
    else
      v->SetMinData (LPSTR(KeyBuffer)+v->VarOffset);
    }
  else {
    if (BCommand == B_GETL)
      v->SetMinData (LPSTR(KeyBuffer)+v->VarOffset);
    else
      v->SetMaxData (LPSTR(KeyBuffer)+v->VarOffset);
    }
  }

// Baum zur Darstellung der Where - Bedingung
#define NT_TERM     0
#define NT_CONST    1
#define NT_NONTERM  2
class FAR BinTree {
 protected :
  BOOL NodeType;
  union {
    struct {
      LPVBTRV v;
      BYTE CmpOp;
      LPVOID Data;
      } term;
    struct {
      BYTE Connection;
      BinTree FAR *Left;
      BinTree FAR *Right;
      } nonterm;
    struct {
      BOOL val;
      } constant ;
    }i;
  void Exchange ()
    {
    BinTree FAR *dummy = i.nonterm.Left ;
    i.nonterm.Left = i.nonterm.Right ;
    i.nonterm.Right = dummy ;
    }

 public :
  BinTree (LPVBTRV v,BYTE CmpOp,LPVOID Val)
    {
    NodeType = NT_TERM ;
    i.term.v = v ; i.term.CmpOp = CmpOp ;
    if (Val != NULL) {
      i.term.Data = GetGlobMem (GetBlockSize (Val)) ; 
      lmemcpy (i.term.Data,Val,GetBlockSize(Val)); 
      }
    }
  BinTree (BinTree FAR *source)
    {
    NodeType = NT_TERM ;
    i.term.v = source->i.term.v ; i.term.CmpOp = source->i.term.CmpOp ; 
    if (source->i.term.Data != NULL) {
      i.term.Data = GetGlobMem (GetBlockSize (source->i.term.Data)) ; 
      lmemcpy (i.term.Data,source->i.term.Data,GetBlockSize(source->i.term.Data)); 
      }
    }
  BinTree (BinTree FAR *r,BinTree FAR *l,BYTE Connection)
    { 
    NodeType = NT_NONTERM ;
    i.nonterm.Connection = Connection;
    i.nonterm.Right = r ; i.nonterm.Left = l ; 
    }
  BinTree (BOOL val)
    { 
    NodeType = NT_CONST ;
    i.constant.val = val;
    }
  void RemoveConstantSubnodes ();
  void ToConst (BOOL val);
  void TakeFrom (BinTree FAR *s);
  BOOL IsValid ()
    {
    return ((NodeType != NT_CONST) || (i.constant.val));
    }
  BOOL IsConst ()
    {
    return (NodeType == NT_CONST);
    }
  BOOL IsAllAnd ();
  BOOL IsAllEqual (LPVBTRV seg);
  BinTree FAR *FindSegToTest (LPVBTRV seg,WORD BOp,BOOL FAR *breakNext);
  BOOL IsAllUsed (PKeyList FAR *k);
  ~BinTree ();
  BOOL TestBtrieveSyntax (BYTE testOp);
  LPVOID CreateFilter (LPVOID filter,WORD FAR &res);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  friend class SegInfo;
  };

#pragma optimize("",off)
BOOL BinTree::IsAllAnd ()
  {
  if (NodeType == NT_CONST) { WIN_ASSERT(FALSE) ; return FALSE ; }
  if (NodeType == NT_TERM) return TRUE ;
  return ((i.nonterm.Left->IsAllAnd()) && (i.nonterm.Right->IsAllAnd()) && (i.nonterm.Connection == BOP_AND)) ;
  }
BOOL BinTree::IsAllEqual (LPVBTRV seg)
  {
  if (NodeType == NT_CONST) { WIN_ASSERT(FALSE) ; return FALSE ; }
  if (NodeType == NT_NONTERM) { return ((i.nonterm.Left->IsAllEqual (seg)) && (i.nonterm.Right->IsAllEqual(seg))) ; }
  if (seg == NULL)                             return ((i.term.CmpOp & 31) == BCMP_EQUAL) ;
  if (lstrcmp (seg->Name,i.term.v->Name) == 0) return ((i.term.CmpOp & 31) == BCMP_EQUAL) ;
  else                                         return TRUE ;
  }
BinTree FAR *BinTree::FindSegToTest (LPVBTRV seg,WORD BOp,BOOL FAR *breakNext)
  {
  if (NodeType == NT_CONST) { WIN_ASSERT(FALSE) ; return NULL ; }
  if (NodeType == NT_NONTERM) { 
    if (i.nonterm.Connection == BOP_OR) return NULL;
    BinTree FAR *res = i.nonterm.Left->FindSegToTest (seg,BOp,breakNext);
    if (res != NULL) return res ;
    return i.nonterm.Right->FindSegToTest(seg,BOp,breakNext);
    }
  if ((lstrcmp (seg->Name,i.term.v->Name) == 0) && 
       ((((BOp == OPGET) || (BOp == OPGETFIRST)) &&
          (((i.term.CmpOp & 31) == BCMP_EQUAL) ||
           ((i.term.CmpOp & 31) == BCMP_LESS) ||
           ((i.term.CmpOp & 31) == BCMP_LESSEQAUL))) ||
        ((BOp == OPGETLAST) &&
          (((i.term.CmpOp & 31) == BCMP_EQUAL) ||
           ((i.term.CmpOp & 31) == BCMP_GREATER) ||
           ((i.term.CmpOp & 31) == BCMP_GREATEREQUAL))))
     ) {
    *breakNext = ((i.term.CmpOp & 31) != BCMP_EQUAL) ;
    return this ;
    }
  else                                                                                  
    return NULL ;
  }
BOOL BinTree::IsAllUsed (PKeyList FAR *k)
  {
  if (NodeType == NT_CONST) { WIN_ASSERT(FALSE) ; return FALSE ; }
  if (NodeType == NT_NONTERM) return ((i.nonterm.Left->IsAllUsed (k)) && (i.nonterm.Right->IsAllUsed(k))) ;
  LPVARTBL h = LPVARTBL (k->k->Name + lstrlen(k->k->Name) + 1) ;
  if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
    LPVBTRV x = &h->v[0];
    for ( int j = 0 ; ((x != NULL) && (j < k->AnzSegsDone)) ; x = x->Next(h->gSize,h) , j++ ) {
      if (lstrcmp (x->Name,i.term.v->Name) == 0) return TRUE ;
      }
    }
  return FALSE ;
  }
void BinTree::TakeFrom (BinTree FAR *s)
  {
  switch (NodeType) {
    case NT_TERM :
      if (i.term.Data != NULL) FreeGlobMem (i.term.Data);
      break ;
    case NT_NONTERM :
      if (i.nonterm.Left != s) delete i.nonterm.Left;
      if (i.nonterm.Right != s) delete i.nonterm.Right;
      break ;
    }
  NodeType = s->NodeType ;
  switch (NodeType) {
    case NT_TERM :
      i.term.CmpOp = s->i.term.CmpOp;
      i.term.v     = s->i.term.v;
      i.term.Data  = s->i.term.Data;
      break ;
    case NT_NONTERM :
      i.nonterm.Connection = s->i.nonterm.Connection ;
      i.nonterm.Left  = s->i.nonterm.Left ;
      i.nonterm.Right = s->i.nonterm.Right ;
      break ;
    case NT_CONST :
      i.constant.val = s->i.constant.val ;
    }
  s->NodeType = NT_CONST ;
  delete s ;
  }
void BinTree::ToConst (BOOL val)
  {
  switch (NodeType) {
    case NT_TERM :
      if (i.term.Data != NULL) FreeGlobMem (i.term.Data);
      break ;
    case NT_NONTERM :
      delete i.nonterm.Left;
      delete i.nonterm.Right;
      break ;
    }
  NodeType = NT_CONST ;
  i.constant.val = val;
  }
BinTree::~BinTree ()
  {
  switch (NodeType) {
    case NT_TERM :
      if (i.term.Data != NULL) FreeGlobMem (i.term.Data);
      break ;
    case NT_NONTERM :
      delete i.nonterm.Left;
      delete i.nonterm.Right;
      break ;
    }
  }
#pragma optimize("",on)

#define TNT         0 // not touched
#define TGT         1 // greater
#define TGE         2 // greater equal
#define TLT         3 // less
#define TLE         4 // less equal
#define TEQ         5 // equal
#define TMN         6 // Minimalwert
#define TMX         7 // Maximalwert

class FAR SegInfo {
 public :
  BYTE Type;
  LPVOID Val;

  SegInfo (LPVBTRV KeySeg,BinTree FAR *t,WORD DBOp,BOOL FAR *IsValid);
  void SetMinVal (LPVBTRV KeySeg);
  void SetMaxVal (LPVBTRV KeySeg);
  BOOL IsMinVal (LPVBTRV KeySeg);
  BOOL IsMaxVal (LPVBTRV KeySeg);
  WORD GetNextDBOp (WORD oldDBOp,WORD OPType);
  WORD GetDBOpFor ();
  void CopyVal (LPVOID v)
    { if (v != NULL) { Val = GetGlobMem (GetBlockSize(v)) ; lmemcpy (Val,v,GetBlockSize(v)); } }
  WORD NextDBOp (WORD DBOp);
  ~SegInfo ()
    { if (Val != NULL) FreeGlobMem (Val); }
  };

#define NOP 0
#define DND 1
#define DEQ 2
#define DGT 3
#define DLT 4
#define DNE 5
#define DGE 6
#define DLE 7

inline void Exchange (SegInfo FAR &left,SegInfo FAR &right)
  {
  BYTE   oType = left.Type;
  LPVOID oVal  = left.Val;
  left.Type    = right.Type;
  left.Val     = right.Val;
  right.Type   = oType;
  right.Val    = oVal;
  }
inline void Exchange (int FAR &i1,int FAR &i2)
  {
  int dummy = i1 ;
  i1 = i2 ;
  i2 = dummy ;
  }

WORD SegInfo::GetDBOpFor ()
  {
  switch (Type) {
    case TEQ :
      return B_GETEQ ;
      break ;
    case TGT :
      return B_GETGT ;
      break ;
    case TLT :
      return B_GETL ;
      break ;
    case TGE :
      return B_GETGTE ;
      break ;
    case TLE :
      return B_GETLE ;
      break ;
    }
  return 0xFFFF ;
  }

WORD SegInfo::GetNextDBOp (WORD oldDBOp,WORD OPType)
  {
  WORD n = GetDBOpFor ();
  if ((n == oldDBOp) || (oldDBOp == B_GETEQ)) return n;
  switch (OPType) {
    case OPGET :
      if (oldDBOp == B_GETLE)  return (n == B_GETL) ? B_GETL : oldDBOp ;
      if (oldDBOp == B_GETGTE) return (n == B_GETGT) ? B_GETGT : oldDBOp ;
      break ;
    case OPGETFIRST :
      if (oldDBOp == B_GETGTE) return (n == B_GETGT) ? B_GETGT : 0xFFFF ;
      if (oldDBOp == B_GETGT)  return ((n == B_GETGT) || (n == B_GETGTE)) ? B_GETGT : 0xFFFF ;
      if (oldDBOp == B_GETL)   return ((n == B_GETL) || (n == B_GETLE)) ? B_GETL : 0xFFFF ;
      break ;
    case OPGETLAST :
      if (oldDBOp == B_GETLE)     return (n == B_GETL) ? B_GETL : 0xFFFF ;
      else if (oldDBOp == B_GETL) return B_GETL;
      break ;
    }
  return 0xFFFF;
  }

#ifdef ALTE_VERSION
WORD GetNextDBOpForEmptySegment (WORD oldDBOp,WORD OPType)
  {
  switch (OPType) {
    case OPGET :
    case OPGETFIRST :
      if (oldDBOp == B_GETEQ)  return B_GETGT ;
      if (oldDBOp == B_GETLE)  return B_GETL ;
      if (oldDBOp == B_GETGTE) return B_GETGT ;
      break ;
    case OPGETLAST :
      if (oldDBOp == B_GETEQ)  return B_GETL ;
      if (oldDBOp == B_GETLE)  return B_GETL ;
      if (oldDBOp == B_GETGTE) return B_GETGT ;
      break ;
    }
  return oldDBOp;
  }
#else
WORD GetNextDBOpForEmptySegment (WORD oldDBOp,WORD OPType)
  {
  switch (OPType) {
    case OPGET :
    case OPGETFIRST :
      if (oldDBOp == B_GETEQ)  return B_GETGTE ;
      break ;
    case OPGETLAST :
      if (oldDBOp == B_GETEQ)  return B_GETLE ;
      break ;
    }
  return oldDBOp;
  }
#endif

void SegInfo::SetMinVal (LPVBTRV KeySeg)
  {
  Type = TGT ;
  Val = GetGlobMem (KeySeg->VarLen);
  WORD oldOffs = KeySeg->VarOffset;
  KeySeg->SetMinData (Val);
  KeySeg->VarOffset = oldOffs;
  }
BOOL SegInfo::IsMinVal (LPVBTRV KeySeg)
  {
  if (Val == NULL) return TRUE ;
  LPVOID Buffer = GetGlobMem (KeySeg->VarLen);
  WORD oldOffs = KeySeg->VarOffset;
  KeySeg->SetMinData (Buffer);
  KeySeg->VarOffset = oldOffs;
  BOOL res = lmemcmp (Val,Buffer,KeySeg->VarLen);
  FreeGlobMem (Buffer);
  return res;
  }
void SegInfo::SetMaxVal (LPVBTRV KeySeg)
  {
  Type = TLT ;
  Val = GetGlobMem (KeySeg->VarLen);
  WORD oldOffs = KeySeg->VarOffset;
  KeySeg->SetMaxData (Val);
  KeySeg->VarOffset = oldOffs;
  }
BOOL SegInfo::IsMaxVal (LPVBTRV KeySeg)
  {
  if (Val == NULL) return TRUE ;
  LPVOID Buffer = GetGlobMem (KeySeg->VarLen);
  WORD oldOffs = KeySeg->VarOffset;
  KeySeg->SetMaxData (Buffer);
  KeySeg->VarOffset = oldOffs;
  BOOL res = lmemcmp (Val,Buffer,KeySeg->VarLen);
  FreeGlobMem (Buffer);
  return res;
  }
typedef void (* COMPAREFNC) (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg);
BOOL Compare (LPVBTRV v,LPVOID v1,LPVOID v2,WORD cmpCode)
  {
  WORD oldOffs = v->VarOffset;
  v->VarOffset = 0;
  if (v->DataType == BDT_ZSTRING) cmpCode += 32 ;      // Mit AlternateSequence vergleichen
  BOOL res = CompareData (Context->stmt,v->DataType,v1,v2,v->VarLen,cmpCode);
  v->VarOffset = oldOffs ;
  return res;
  }
void CheckSame (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob beide Werte gleich sind, wenn ja dann einen nehmen
  if (!Compare (KeySeg,s1->Val,s2->Val,BCMP_EQUAL)) *IsValid = FALSE ;
  res->Type = s1->Type ;
  res->CopyVal (s1->Val);
  }
void CheckEQDisN (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob Wert1 groesser als Wert2 ist, wenn ja, dann Wert1 nehmen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TGT) ? BCMP_GREATER : BCMP_GREATEREQUAL))
    res->Type = s1->Type , res->CopyVal (s1->Val);
#ifdef ALTE_VERSION
  // Ueberpruefen, ob Wert1 groesser als Wert2 ist, wenn ja, dann Wert1 nehmen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TGT) ? BCMP_GREATER : BCMP_GREATEREQUAL))
    res->Type = s2->Type , res->CopyVal (s2->Val);
#endif
  else
    *IsValid = FALSE ;
  }
void CheckEQDisN1 (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob Wert1 kleiner als Wert2 ist, wenn ja, dann Wert1 nehmen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TLT) ? BCMP_LESS : BCMP_LESSEQAUL))
    res->Type = s1->Type , res->CopyVal (s1->Val);
#ifdef ALTE_VERSION
  // Ueberpruefen, ob Wert1 kleiner als Wert2 ist, wenn ja, dann Wert2 nehmen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TLT) ? BCMP_LESS : BCMP_LESSEQAUL))
    res->Type = s2->Type , res->CopyVal (s2->Val);
#endif
  else
    *IsValid = FALSE ;
  }
void CheckEQDisX (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob Wert1 kleiner als Wert2 ist, wenn ja, dann minimum setzen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TLT) ? BCMP_LESS : BCMP_LESSEQAUL))
    res->SetMinVal (KeySeg);
  else
    *IsValid = FALSE ;
  }
void CheckEQDisX1 (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob Wert1 groesser als Wert2 ist, wenn ja, dann Maximum setzen
  if (Compare (KeySeg,s1->Val,s2->Val,(s2->Type == TGT) ? BCMP_GREATER : BCMP_GREATEREQUAL))
    res->SetMaxVal (KeySeg);
  else
    *IsValid = FALSE ;
  }
void CheckMax (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Den Maximalwert von s1 und s2 ermitteln
  if (Compare (KeySeg,s1->Val,s2->Val,BCMP_GREATER))
    res->Type = s1->Type , res->CopyVal (s1->Val);
  else
    res->Type = s2->Type , res->CopyVal (s2->Val);
  }
void CheckMin (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Den minimalwert von s1,s2 nehmen
  if (Compare (KeySeg,s1->Val,s2->Val,BCMP_LESS))
    res->Type = (s1->Type == TGT) ? TGT : TGE , res->CopyVal (s1->Val);
  else if (Compare (KeySeg,s2->Val,s1->Val,BCMP_LESS))
    res->Type = (s2->Type == TGT) ? TGT : TGE , res->CopyVal (s2->Val);
  else
    // Gleich gross
    res->Type = TGE , res->CopyVal (s1->Val);
  }
void SetMF (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Den minimalwert von s1 uebernehmen, den Modus vom Kleineren Uebernehmen
  if (Compare (KeySeg,s1->Val,s2->Val,BCMP_LESS))
    res->Type = s1->Type , res->CopyVal (s1->Val);
  else
    res->Type = s2->Type , res->CopyVal (s2->Val);
  }
void CheckMinDisj (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob sich die Werte s1 und s2 ueberschneiden (s1 > , s2 < )
  if (Compare (KeySeg,s1->Val,s2->Val,BCMP_GREATER))
    *IsValid = FALSE ;
  else {
    if (Compare (KeySeg,s1->Val,s2->Val,BCMP_LESS))
      res->Type = (s1->Type) , res->CopyVal (s1->Val);
    else if ((s1->Type == TGE) && (s2->Type == TLE) && (Compare (KeySeg,s1->Val,s2->Val,BCMP_EQUAL)))
      res->Type = TEQ , res->CopyVal (s1->Val);
    else
      *IsValid = FALSE ;
    }
  }
void CheckMaxDisj (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // Ueberpruefen, ob sich die Werte s1 und s2 ueberschneiden (s1 < , s2 > )
  if (Compare (KeySeg,s1->Val,s2->Val,BCMP_LESS))
    *IsValid = FALSE ;
  else {
    if (Compare (KeySeg,s1->Val,s2->Val,BCMP_GREATER))
      res->Type = s1->Type , res->CopyVal (s1->Val);
    else if ((s1->Type == TLE) && (s2->Type == TGE) && (Compare (KeySeg,s1->Val,s2->Val,BCMP_EQUAL)))
      res->Type = TEQ , res->CopyVal (s1->Val);
    else
      *IsValid = FALSE ;
    }
  }
void SetMin (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // res auf Minimalwert setzen
  res->SetMinVal (KeySeg);
  }
void SetMax (SegInfo FAR *res,SegInfo FAR *s1,SegInfo FAR *s2,BOOL FAR *IsValid,LPVBTRV KeySeg)
  { // res auf Maximal setzen
  res->SetMaxVal (KeySeg);
  }

int GetCmdIndex (int type)
  {
  switch (type) {
    case TEQ :
      return 0 ;
    case TGT :
      return 1 ;
    case TGE :
      return 2 ;
    case TLT : 
      return 3 ;
    case TLE : 
      return 4 ;
    }
  return 0 ;
  }
SegInfo::SegInfo (LPVBTRV KeySeg,BinTree FAR *t,WORD DBOp,BOOL FAR *IsValid)
  {
  Val = NULL;
  if (t->NodeType == NT_TERM) {
    if (lstrcmp (t->i.term.v->Name,KeySeg->Name) == 0) {
      static BYTE TypeFromOP [][7] = {
                        /* DNO. DEQ. DGT. DLT. DNE. DGE. DLE */
        /* OPGET      */ { TNT, TEQ, TGT, TLT, TNT, TGE, TLE } ,
        /* OPGETFIRST */ { TNT, TGE, TGT, TMN, TNT, TGE, TMN } ,
        /* OPGETLAST  */ { TNT, TLE, TMX, TLT, TNT, TMX, TLE }
        };
      Type = TypeFromOP [DBOp][t->i.term.CmpOp & 31];
      if (Type != TNT) {
        switch (Type) {
          case TMN :
            SetMinVal (KeySeg);
            break ;
          case TMX :
            SetMaxVal (KeySeg);
            break ;
          default :
            Val = GetGlobMem (KeySeg->VarLen);
            WORD oldOffs = KeySeg->VarOffset;
            KeySeg->SetData (Val,t->i.term.Data);
            KeySeg->VarOffset = oldOffs;
          }
        }
      }
    else {
      Type = TNT;
      }
    }
  else {      // NT_CONST darf an dieser Stelle nicht mehr vorkommen
    SegInfo left (KeySeg,t->i.nonterm.Left,DBOp,IsValid);
    SegInfo right (KeySeg,t->i.nonterm.Right,DBOp,IsValid);

    if (!*IsValid) return ;

    static COMPAREFNC UnionCommand[2][2][5][5] = {
        { // OPGET,OPGETFIRST
          { // DBOP_AND
           /* = */     /* > */       /* >= */      /* < */        /* <= */
/* =  */ { CheckSame , CheckEQDisN , CheckEQDisN , CheckEQDisN1 , CheckEQDisN1 } ,
/* >  */ { NULL      , CheckMax    , CheckMax    , CheckMinDisj , CheckMinDisj } ,
/* >= */ { NULL      , NULL        , CheckMax    , CheckMinDisj , CheckMinDisj } ,
/* <  */ { NULL      , NULL        , NULL        , SetMin       , SetMin       } ,
/* <= */ { NULL      , NULL        , NULL        , NULL         , SetMin       }
          } ,
          { // DBOP_OR
           /* = */    /* > */    /* >= */   /* < */  /* <= */
/* =  */ { CheckMin , CheckMin , CheckMin , SetMin , SetMin } ,
/* >  */ { NULL     , CheckMin , CheckMin , SetMin , SetMin } ,
/* >= */ { NULL     , NULL     , CheckMin , SetMin , SetMin } ,
/* <  */ { NULL     , NULL     , NULL     , SetMin , SetMin } ,
/* <= */ { NULL     , NULL     , NULL     , NULL   , SetMin }
          }
        } ,
        { // OPGETLAST
          { // DBOP_AND
           /* = */     /* > */        /* >= */       /* < */        /* <= */
/* =  */ { CheckSame , CheckEQDisN  , CheckEQDisN   , CheckEQDisN1 , CheckEQDisN1 } ,
/* >  */ { NULL      , SetMax       , SetMax        , CheckMaxDisj , CheckMaxDisj } ,
/* >= */ { NULL      , NULL         , SetMax        , CheckMaxDisj , CheckMaxDisj } ,
/* <  */ { NULL      , NULL         , NULL          , SetMF        , SetMF        } ,
/* <= */ { NULL      , NULL         , NULL          , NULL         , SetMF        }
          } ,
          { // DBOP_OR
           /* = */    /* > */    /* >= */   /* < */  /* <= */
/* =  */ { CheckMax , SetMax   , SetMax   , CheckMax , CheckMax } ,
/* >  */ { NULL     , SetMax   , SetMax   , SetMax   , SetMax   } ,
/* >= */ { NULL     , NULL     , SetMax   , SetMax   , SetMax   } ,
/* <  */ { NULL     , NULL     , NULL     , CheckMax , CheckMax } ,
/* <= */ { NULL     , NULL     , NULL     , NULL     , CheckMax }
          }
        }
      } ;
    if ((left.Val != NULL) && (right.Val != NULL)) {
      int cmdIndex1 = GetCmdIndex (left.Type);
      int cmdIndex2 = GetCmdIndex (right.Type);
      if (cmdIndex1 > cmdIndex2) {
        Exchange (left,right);
        Exchange (cmdIndex2,cmdIndex1);
        }
      int GetCmd = ((DBOp == OPGET) || (DBOp == OPGETFIRST)) ? 0 : 1 ;
      int OpCmd = (t->i.nonterm.Connection == BOP_AND) ? 0 : 1 ;
      COMPAREFNC doCall = UnionCommand [GetCmd][OpCmd][cmdIndex1][cmdIndex2];
      WIN_ASSERT (doCall != NULL);
      (* doCall) (this,&left,&right,IsValid,KeySeg);
      }
    else {
      if (t->i.nonterm.Connection == BOP_AND) {
        if (left.Val == NULL)
          Exchange (left,right);
        Type = left.Type ;
        CopyVal (left.Val);
        }
      else {
        Type = TNT;
        }
      }
    }
  }

BOOL BinTree::TestBtrieveSyntax (BYTE testOp)
  {
  if (NodeType == NT_TERM) return TRUE ;
  else {
    if ((testOp == 0xFF) || (i.nonterm.Connection == testOp)) {
      if (!i.nonterm.Left->TestBtrieveSyntax (i.nonterm.Connection)) {
        Exchange ();
        return ((i.nonterm.Left->TestBtrieveSyntax (i.nonterm.Connection)) && (i.nonterm.Right->TestBtrieveSyntax (testOp)));
        }
      else if (!i.nonterm.Right->TestBtrieveSyntax (testOp)) {
        Exchange ();
        return ((i.nonterm.Left->TestBtrieveSyntax (i.nonterm.Connection)) && (i.nonterm.Right->TestBtrieveSyntax (testOp)));
        }
      else
        return TRUE ;
      }
    else
      return FALSE ;
    }
  }
LPVOID BinTree::CreateFilter (LPVOID filter,WORD FAR &res)
  {
  if (NodeType == NT_TERM) {
    BYTE dt;
    if ((i.term.v->DataType == DT_PRIVATE) ||
        (i.term.v->DataType == DT_SPRIVATE)) dt = BDT_UNSIGNED;
    else                                     dt = BYTE(i.term.v->DataType);
    filter = Context->stmt->PushToFilter (filter,&dt,1);
    filter = Context->stmt->PushToFilter (filter,&i.term.v->VarLen,2);
    filter = Context->stmt->PushToFilter (filter,&i.term.v->VarOffset,2);
    filter = Context->stmt->PushToFilter (filter,&i.term.CmpOp,1);

    // Dummy fuer Operator, der eine Rekursionsstufe hoeher eingefuegt werden wird
    BYTE dummy;
    res = GetBlockSize (filter);
    filter = Context->stmt->PushToFilter (filter,&dummy,1);

    LPVOID Buffer = GetGlobMem (i.term.v->VarLen);
    WORD oldOffset = i.term.v->VarOffset;
    i.term.v->VarOffset = 0;
    i.term.v->SetData (Buffer,i.term.Data);
    i.term.v->VarOffset = oldOffset;
    filter = Context->stmt->PushToFilter (filter,Buffer,i.term.v->VarLen);
    FreeGlobMem (Buffer);

    Context->stmt->IncAnzTerms(filter);
    }
  else {
    WORD Lookup ;
    filter = i.nonterm.Left->CreateFilter(filter,Lookup);
    *(LPSTR(filter)+Lookup) = i.nonterm.Connection;
    filter = i.nonterm.Right->CreateFilter(filter,res);
    }
  return filter;
  }
void BinTree::RemoveConstantSubnodes ()
  {
  if ((NodeType == NT_TERM) || (NodeType == NT_CONST)) return ;
  else {
    i.nonterm.Left->RemoveConstantSubnodes ();
    i.nonterm.Right->RemoveConstantSubnodes ();
    if ((i.nonterm.Left->NodeType == NT_CONST) || (i.nonterm.Right->NodeType == NT_CONST)) {
      if (i.nonterm.Right->NodeType == NT_CONST) Exchange ();
      // Links ist auf jeden Fall Konstant
      switch (i.nonterm.Connection) {
        case BOP_AND :
          if (!(i.nonterm.Left->i.constant.val)) // && FALSE -> Weg damit
            ToConst (FALSE);
          else                                   // Rechts uebernehmen
            TakeFrom (i.nonterm.Right);
          break ;
        case BOP_OR :
          if (i.nonterm.Left->i.constant.val)    // && TRUE -> Weg damit
            ToConst (TRUE);
          else                                   // Rechts uebernehmen
            TakeFrom (i.nonterm.Right);
          break ;
        }
      }
    }
  }

int PKeyList::TestKey (BinTree FAR *t,BOOL FAR *allDone,WORD DBOp,BOOL FAR *IsValid)
  {
  WORD InitCommand = (DBOp == OPGETLAST) ? B_GETLAST : B_GETFIRST ;
  B_Command = InitCommand;
  if ((k != NULL) && (t != NULL)) {
    LPVARTBL h = LPVARTBL (k->Name + lstrlen(k->Name) + 1) ;
    if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
      LPVBTRV x = &h->v[0];
      BOOL DoCheck = TRUE ;
      for ( ; x != NULL ; x = x->Next(h->gSize,h)) {
        if (DoCheck) {
          SegInfo s (x,t,DBOp,IsValid);
          if ((s.Type != TNT) && 
                ((Context->DontCheckExtremes()) || (!s.IsMinVal(x)) && (!s.IsMaxVal(x)))
             ) {
            if (AnzSegsDone == 0)
              B_Command = s.GetDBOpFor ();
            else
              B_Command = s.GetNextDBOp (B_Command,DBOp);
            if (B_Command != 0xFFFF) {
              SetSegmentValue (x,s.Val);
              AnzSegsDone ++ ;
              }
            else
              DoCheck = FALSE ;
            }
          else 
            DoCheck = FALSE ;
          }
        if (!DoCheck) {
          B_Command = GetNextDBOpForEmptySegment (B_Command,DBOp);
          FillSegmentValue (x,DBOp,B_Command);
          }
        }
      }
    }
  *allDone = IsAllDone ();
  return AnzSegsDone;
  }
BOOL PKeyList::CheckKeySegment (LPSTR Name)
  {
  BOOL res = FALSE ;
  if (k != NULL) {
    LPVARTBL h = LPVARTBL (k->Name + lstrlen(k->Name) + 1) ;
    if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
      if (!SegInitDone)
        SegToTest = &h->v[0];
      if (SegToTest == NULL) return FALSE ;
      res = (lstrcmp (Name,SegToTest->Name) == 0) ;
      SegToTest = SegToTest->Next(h->gSize,h);
      SegInitDone = TRUE ;
      }
    }
  return res;
  }

void InitializeKeyList (LPBTRVTABLE t,LPKEYDEF ksingle = NULL)
  {
  if (t == NULL) {
    Context->PossibleKeys = NULL ;
    return ;
    }
  if (ksingle == NULL) {
    Context->PossibleKeys = NULL;
    for (LPKEYDEF k = t->GetFirstKey () ; k != NULL ; k = t->GetNextKey (k)) {
      PKeyList FAR *n = new PKeyList (k);
      n->Next = NULL ;
      for (PKeyList FAR *h = Context->PossibleKeys ; ((h != NULL) && (h->Next != NULL)) ; h = h->Next ) ;
      if (h != NULL) h->Next = n ;
      else           Context->PossibleKeys = n ;
      }
    }
  else {
    Context->PossibleKeys = new PKeyList(ksingle);
    }
  }
PKeyList FAR *FindKey (WORD KeyNmbr)
  {
  for (PKeyList FAR *n = Context->PossibleKeys ; n != NULL ; n = n->Next) {
    if (n->k->KeyNmbr == KeyNmbr) return n ;
    }
  return NULL ;
  }
void RemoveKeyList ()
  {
  for ( ; Context->PossibleKeys != NULL ; ) {
    PKeyList FAR *n = Context->PossibleKeys->Next ;
    delete Context->PossibleKeys;
    Context->PossibleKeys = n;
    }
  }
PKeyList FAR *GetBestKey (BinTree FAR *tree,WORD DBOp)
  {
  int oVal = -1;
  PKeyList FAR *bestkey = Context->PossibleKeys;
  BOOL IsValid = TRUE ;
  for (PKeyList FAR *h = Context->PossibleKeys ; h != NULL ; h = h->Next) {
    BOOL allDone;
    int nVal = h->TestKey (tree,&allDone,DBOp,&IsValid);
    if (!IsValid) return NULL;
    if (nVal > oVal) {
      oVal = nVal ;
      bestkey = h;
      }
    }
  return bestkey;
  }
 
void GetDBPositions (LPSTR buffer)
  {
  RecordImage_header FAR *hd = (RecordImage_header FAR *) buffer;
  RecordImage FAR *img = (RecordImage FAR *) (hd + 1);
  int j = Context->UpdatePos.AnzPos ;
  Context->UpdatePos.Enlarge (hd->AnzRecords) ;
  for (WORD count = 0 ; count < hd->AnzRecords ; count++) {
    Context->UpdatePos.SetPos (j++,img->btrPos);
    img = (RecordImage FAR *) (LPSTR(img + 1) + img->rLength);
    }
  }

class SQLCompiler : public compiler {
 public :
  virtual BOOL isstrsign (void)
    { return (*actptr == '\''); }
  virtual DLLExport BOOL _export AllowOperator()
    { return TRUE ; }
  
  virtual DLLExport void _export WINAPI InstallBuffer(LPVOID d);
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);
  void DeinstallBuffer ();
  LPSTR GetActPtr()
    { return actptr ; }

  SQLCompiler () : compiler (NULL) { }
  };

extern HINSTANCE hLibInst;
#define STOPPARSING 3000
DLLExport BOOL _export WINAPI SQLCompiler::TestError (void)
  {
  if (wError == STOPPARSING) return TRUE ;
  if (wError) {
    lstrncpy (fmname,buffer_start,55);
    if (wError > SQLCMPERROR_BASE) {
      char pattern[64];
      char errstr[64];
      LoadString (hLibInst,SQLCMPERROR_BASE,pattern,sizeof(pattern));
      LoadString (hLibInst,wError,errstr,sizeof(errstr));
      char outtxt[256];
      wsprintf (outtxt,pattern,fmname,LineNr,column,LPSTR(errstr));
      DBWIN_ASSERT_TEXT (FALSE,outtxt);
      LogMsg (MODULENUM,column,buffer_start);
      return TRUE ;
      }
    else {
      DBWIN_ASSERT (FALSE);
      LogMsg (MODULENUM,column,buffer_start);
      return compiler::TestError ();
      }
    }
  else
    return FALSE ;
  }

#define SQLKW_EQUAL         0
#define SQLKW_PARPRE        1
#define SQLKW_AND           2
#define SQLKW_OR            3
#define SQLKW_END           4
#define SQLKW_BRACEOPEN     5
#define SQLKW_BRACECLOSE    6
#define SQLKW_GREATER       7
#define SQLKW_GREATEREQUAL  8
#define SQLKW_LESS          9
#define SQLKW_LESSEQUAL     10
#define SQLKW_NOTEQUAL      11
#define SQLKW_COLON         12
#define SQLKW_SUB           13
#define SQLKW_ADD           14
#define SQLKW_DIVIDE        15
#define SQLKW_MULTIPLY      16
#define SQLKW_MAX           17
#define SQLKW_MIN           18
#define SQLKW_LIKE          19
#define SQLKW_IN            20
#define SQLKW_ORDER         21
#define SQLKW_BY            22
#define SQLKW_SELECT        23
#define SQLKW_NOT           24
#define SQLKW_WHERE         25
#define SQLKW_FROM          26
#define SQLKW_UPDATE        27
#define SQLKW_SET           28
#define SQLKW_NULL          29
#define SQLKW_DELETE        30
#define SQLKW_INSERT        31
#define SQLKW_INTO          32
#define SQLKW_VALUES        33

DLLExport void _export WINAPI SQLCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  static char *sqlkws[] = {
    /* SQLKW_EQUAL */       "=" ,
    /* SQLKW_PARPRE */      "%" ,
    /* SQLKW_AND */         "AND" ,
    /* SQLKW_OR */          "OR" ,
    /* SQLKW_END */         "_end_" ,
    /* SQLKW_BRACEOPEN */   "(" ,
    /* SQLKW_BRACECLOSE */  ")" ,
    /* SQLKW_GREATER */     ">" ,
    /* SQLKW_GREATEREQUAL */">=" ,
    /* SQLKW_LESS */        "<" ,
    /* SQLKW_LESSEQUAL */   "<=" ,
    /* SQLKW_NOTEQUAL */    "<>" ,
    /* SQLKW_COLON */       "," ,
    /* SQLKW_SUB */         "-" ,
    /* SQLKW_ADD */         "+" ,
    /* SQLKW_DIVIDE */      "/" ,
    /* SQLKW_MULTIPLY */    "*" ,
    /* SQLKW_MULTIPLY */    "MAX" ,
    /* SQLKW_MULTIPLY */    "MIN" ,
    /* SQLKW_LIKE */        "LIKE",
    /* SQLKW_IN */          "IN" ,
    /* SQLKW_ORDER */       "ORDER" ,
    /* SQLKW_BY */          "BY" ,
    /* SQLKW_SELECT */      "SELECT" ,
    /* SQLKW_NOT */         "NOT",
    /* SQLKW_WHERE */       "WHERE",
    /* SQLKW_FROM */        "FROM",
    /* SQLKW_UPDATE */      "UPDATE",
    /* SQLKW_SET */         "SET",
    /* SQLKW_NULL */        "NULL",
    /* SQLKW_DELETE */      "DELETE",
    /* SQLKW_INSERT */      "INSERT",
    /* SQLKW_INTO */        "INTO",
    /* SQLKW_VALUES */      "VALUES"
    };
  for (WORD i = 0 ; i < sizeof(sqlkws) / sizeof(sqlkws[0]) ; i++) {
    h->SetData (sqlkws[i],&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

void SQLCompiler::DeinstallBuffer ()
  {
  FreeGlobMem (buffer_start) ;
  }

void SQLCompiler::InstallBuffer(LPVOID d)
  {
  int oldsize = lstrlen(LPSTR(d));
  buffer_start = LPSTR (GetGlobMem (oldsize + 7));
  lmemcpy (buffer_start,d,oldsize);
  lstrcpy (buffer_start + oldsize," _end_");
  actptr = buffer_start;

  LineNr = 1;
  IncLineNr = 1;
  column = 1;
  }

/*-----< Codegenerierung - arithmetische Expressions >-------*/
LPSTR GetRealName (LPSTR Alias)
  {
  LPTABLEDEF td = Context->td;
  if (td->IsInternTable()) {
    LPINTTABLE ti = LPINTTABLE (td->GetDLLDef());
    LPPTABLE p = ti->GetTableByNum(0);
    LPTABLEDEF td0 = Context->stmt->req->TableDef[0] ;
    for (int j = 0 ; j < int(p->AnzVars) ; j++) {
      if (lstrcmp (td->GetVarDef(j)->GetName(),Alias) == 0) return td0->GetVarDef(p->VarID[j])->GetName();
      }
    }
  return Alias;
  }
DLLExport void _export OnParameter ()
  {
  DWORD ParNum = Context->SQLCmp->scv.v.int_val+1;
  DBWIN_ASSERT_TEXT(ParNum <= Context->stmt->req->AnzParam,"zuwenige Parameter angegeben !");
  LPVOID res = Context->stmt->req->Param[ParNum];
  Push (res,GetBlockSize(res));
  switch (Context->stmt->req->ParamType[ParNum]) {
    case VAR_LONG :
    case VAR_STRARR :
    case VAR_FLAG :
      Context->PushDataType (CTYPE_INTEGER);
      break ;
    case VAR_STR :
      Context->PushDataType (CTYPE_STRING);
      break ;
    default :
      Context->PushDataType (CTYPE_PARAMETER);
    }
  }
DLLExport void _export OnConstString ()
  {
  LPSTR res = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  Push (res,GetBlockSize(res));
  GlobalUnlock (Context->SQLCmp->hPars0);
  Context->PushDataType (CTYPE_STRING);
  }
DLLExport void _export OnConstDec ()
  {
  Push (&Context->SQLCmp->scv.v.float_val,sizeof(float));
  Context->PushDataType (CTYPE_DEC);
  }
DLLExport void _export OnConstInt ()
  {
  Push (&Context->SQLCmp->scv.v.int_val,sizeof(long));
  Context->PushDataType (CTYPE_INTEGER);
  }
DLLExport void _export OnAOp ()
  {
  Context->PushAOp (BYTE(Context->SQLCmp->scv.v.k_ident));
  }
DLLExport void _export CalcTerm ()
  {
  BYTE op = Context->PopAOp ();
  LPVOID c2 = Pop ();
  LPVOID c1 = Pop ();
  BYTE t2 = Context->PopDataType ();
  BYTE t1 = Context->PopDataType ();
  if (t2 == CTYPE_PARAMETER) t2 = t1 ;
  if (t1 == CTYPE_PARAMETER) t1 = t2 ;
  if ((t2 == t1) && (t1 != CTYPE_PARAMETER) && (t1 != CTYPE_STRING)) {
    if ((c1 != NULL) && (c2 != NULL)) {
      union rdata {
        LONG ires;
        float fres;
        } r;
      switch (op) {
        case SQLKW_ADD :
          if (t1 == CTYPE_INTEGER)
            r.ires = *((LONG FAR *) c1) + *((LONG FAR *) c2);
          else
            r.fres = *((float FAR *) c1) + *((float FAR *) c2);
          break ;
        case SQLKW_SUB :
          if (t1 == CTYPE_INTEGER)
            r.ires = *((LONG FAR *) c1) - *((LONG FAR *) c2);
          else
            r.fres = *((float FAR *) c1) - *((float FAR *) c2);
          break ;
        case SQLKW_MULTIPLY :
          if (t1 == CTYPE_INTEGER)
            r.ires = *((LONG FAR *) c1) * *((LONG FAR *) c2);
          else
            r.fres = *((float FAR *) c1) * *((float FAR *) c2);
          break ;
        case SQLKW_DIVIDE :
          if (t1 == CTYPE_INTEGER)
            r.ires = *((LONG FAR *) c1) / *((LONG FAR *) c2);
          else
            r.fres = *((float FAR *) c1) / *((float FAR *) c2);
          break ;
        }
      Push (&r,sizeof(r));
      }
    else
      Push (NULL,0) ;
    Context->PushDataType (t1);
    }
  else
    Context->SQLCmp->wError = SEM_ERROR ;
  }
/*-----< Codegenerierung >-------*/
DLLExport void _export OnVarName ()
  {
  LPSTR Name = GetRealName (LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD));
  if ((Name == NULL) || ((Context->VarToCheck = Context->t->GetVar (Name,FALSE)) == NULL))
    Context->SQLCmp->wError = SYNTAX_ERROR ;
  GlobalUnlock (Context->SQLCmp->hPars0);
  }
BYTE GetCompCode (int Ident)
  {
  static struct { int Ident; BYTE result ; } KwTOCC [] = {
    { SQLKW_EQUAL           , BCMP_EQUAL        } ,
    { SQLKW_GREATER         , BCMP_GREATER      } ,
    { SQLKW_GREATEREQUAL    , BCMP_GREATEREQUAL } ,
    { SQLKW_LESS            , BCMP_LESS         } ,
    { SQLKW_LESSEQUAL       , BCMP_LESSEQAUL    } ,
    { SQLKW_NOTEQUAL        , BCMP_NOTEQUAL     } ,
    { SQLKW_IN              , BCMP_EQUAL        } ,
    { SQLKW_NOT             , BCMP_NOTEQUAL     } 
    };
  BYTE result = SQLKW_EQUAL ;
  for (int i = 0 ; i < sizeof(KwTOCC) / sizeof(KwTOCC[0]) ; i++)
    if (KwTOCC[i].Ident == Ident) result = KwTOCC[i].result;
  if ((Context->VarToCheck->DataType == BDT_ZSTRING) &&
      ((Context->stmt->File == NULL) ||
       (Context->stmt->File->AlternateDefined))) result += 32;  // Alternate Collating Sequence
  return result;
  }
DLLExport void _export OnCompareType ()
  {
  Context->ActCompCode = GetCompCode (Context->SQLCmp->scv.v.k_ident);
  }
DLLExport void _export SetSFnc ()
  {
  Context->ActSFnc = BYTE(Context->SQLCmp->scv.v.k_ident);
  }
void FNCArg (BYTE ActSFnc)
  {
  LPVOID Buffer = GetGlobMem (Context->VarToCheck->VarLen);
  if (Context->stmt->req->Type == DBCALLTYPE_GETLIST)
    Context->stmt->req->Type = DBCALLTYPE_STANDARDGET ;
  if (ActSFnc == SQLKW_MIN) {
    Context->ActCompCode = BCMP_GREATER ;
    *Context->actDBOp = OPGETFIRST ;
    Context->VarToCheck->SetMinData (Buffer);
    }
  else {
    Context->ActCompCode = BCMP_LESS ;
    *Context->actDBOp = OPGETLAST ;
    Context->VarToCheck->SetMaxData (Buffer);
    }
  Push (Buffer,GetBlockSize(Buffer));
  FreeGlobMem (Buffer);
  }

DLLExport void _export CheckFncArg ()
  {
  if ((Context->ActCompCode & 31) != BCMP_EQUAL)
    Context->SQLCmp->wError = SEM_ERROR ;
  if (lstrcmp (GetRealName (LPSTR(GlobalLock(Context->SQLCmp->hPars0)) + sizeof(WORD)),
                            Context->VarToCheck->Name) != 0)
    Context->SQLCmp->wError = SEM_ERROR ;
  GlobalUnlock (Context->SQLCmp->hPars0);
  FNCArg (Context->ActSFnc);
  }
DLLExport void _export CreateLikeNode ()
  {
  Context->PopDataType ();
  LPSTR str = LPSTR (Pop ());
  if ((str == NULL) || (*str == '\0'))
    Context->PushPointer (new BinTree (FALSE)) ;
  else if (*str == '%')
    Context->PushPointer (new BinTree (TRUE)) ;
  else {
    LPSTR h = str;
    for (int fpos = 0 ; ((*h) && (*h != '%')) ; h ++ , fpos ++ );
    if (*h == '%') {
      LPSTR nstr = LPSTR (GetGlobMem (fpos+1));
      lmemcpy (nstr,str,fpos+1);
      nstr[fpos] = '\0';
      Push (nstr,GetBlockSize(nstr));
      Context->PushDataType (VAR_STR);
      NextChar (Context->stmt) ;   // Wandelt das Top - Element des Stack um
      BYTE opg = BCMP_GREATEREQUAL , opl = BCMP_LESS;
      if (Context->stmt->File->AlternateDefined) { opg += 32 , opl += 32 ; }
      Context->PushPointer (new BinTree (new BinTree (Context->VarToCheck,opl,Pop()),
                                         new BinTree (Context->VarToCheck,opg,nstr),
                                         BOP_AND
                                        )
                          );
      Context->PopDataType ();
      FreeGlobMem (nstr);
      }
    }
  }
DLLExport void _export SetResNull ()
  {
  if (Context->VarToCheck != NULL) {
    Push(NULL,0,TRUE);
    }
  else
    Push(NULL,0);
  }
DLLExport void _export OnExpRes ()
  {
  Context->PopDataType ();
  BOOL ExternNull ;
  LPVOID val = Pop (&ExternNull);
  if ((val == NULL) && (!ExternNull))
    Context->PushPointer (new BinTree (FALSE));
  else
    Context->PushPointer (new BinTree (Context->VarToCheck,Context->ActCompCode,val));
  }
DLLExport void _export OnConnectType ()
  {
  switch (Context->SQLCmp->scv.v.k_ident) {
    case SQLKW_AND :
      Context->PushConnType (BOP_AND);
      break ;
    case SQLKW_OR :
      Context->PushConnType (BOP_OR);
      break ;
    case SQLKW_COLON :
      if ((Context->ActCompCode & 31) == BCMP_EQUAL)
        Context->PushConnType (BOP_OR);
      else
        Context->PushConnType (BOP_AND);
      break ;
    }
  }
DLLExport void _export OnConnectTypeColon ()
  {
  OnConnectType ();
  if (Context->performMore) {
    // Die letzten 2 mal runterholen
    Context->PushPointer (new BinTree(Context->PopPointer(),Context->PopPointer(),Context->PopConnType ()));
    }
  Context->performMore = TRUE ;  
  }
DLLExport void _export InitializePerformMore ()
  {
  Context->performMore = FALSE ;  
  }

DLLExport void _export OnCompareType_InitializePerformMore ()
  {
  Context->ActCompCode = GetCompCode (Context->SQLCmp->scv.v.k_ident);
  Context->performMore = FALSE ;  
  }

DLLExport void _export CreateConstForInOperator ()
  {
  if ((Context->ActCompCode & 31) == BCMP_EQUAL)
    Context->PushPointer (new BinTree (FALSE)) ;
  else
    Context->PushPointer (new BinTree (TRUE)) ;
  }
DLLExport void _export OnEndOperator ()
  {
  Context->PushPointer (new BinTree(Context->PopPointer(),Context->PopPointer(),Context->PopConnType ()));
  }
DLLExport void _export OnEndOperator_List ()
  {
  if (Context->performMore) {
    // Die letzten 2 mal runterholen
    Context->PushPointer (new BinTree(Context->PopPointer(),Context->PopPointer(),Context->PopConnType ()));
    }
  }
DLLExport void _export CheckValidKeySegment ()
  {
  LPSTR Name = GetRealName (LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD));
  if (Name == NULL)
    Context->SQLCmp->wError = SEM_ERROR ;
  else {
    PKeyList FAR *p = NULL ;
    for ( PKeyList FAR *h = Context->PossibleKeys ; h != NULL ; ) {
      PKeyList FAR *n = h->Next ;
      if (!h->CheckKeySegment (Name)) {
        if (p != NULL) p->Next = n ;
        else           Context->PossibleKeys = n;
        delete h ;
        }
      else
        p = h ;
      h = n;
      }
    if (Context->PossibleKeys == NULL) Fehler (NoKey);
    }
  GlobalUnlock (Context->SQLCmp->hPars0);
  }
DLLExport void _export MarkSubQueryStart ()
  {
  Context->SubQueryStart = Context->SQLCmp->GetActPtr() ;
  }
extern int DBCall_Work (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
DLLExport void _export DoSubQuery_In ()
  {
  LPSTR command = LPSTR (GetGlobMem (Context->SQLCmp->GetActPtr() - Context->SubQueryStart));
  lmemcpy (command,Context->SubQueryStart,Context->SQLCmp->GetActPtr() - Context->SubQueryStart - 1);
  LPDBREQUEST req = InitializeRequest (command,1,DBCALLTYPE_EXECUTE,Context->stmt->req->DocID);
  for (int i = 2 ; i < CB_PARAM ; i++) {
    if (Context->stmt->req->Param[i] != NULL) {
      req->SetParam (i,Context->stmt->req->Param[i],GetBlockSize(Context->stmt->req->Param[i]));
      req->SetParamType (i,Context->stmt->req->ParamType[i]);
      }
    }
  req->AnzParam = Context->stmt->req->AnzParam;
  LPVOID hstmt = NULL;
  for ( BOOL first = TRUE ; ; ) {
    RecBuffer rb;
    lmemset (&rb,'\0',sizeof(rb));
    int res = DBCall_Work ((first) ? DBOP_GETFIRST : DBOP_GETNEXT,-1,req,&hstmt,&rb);
    if ((res == DBCALL_SUCCESS) || (res == DBCALL_ENDOFFILE)) {
      for (RecBufferLine FAR *h = rb.First() ; h != NULL ; h = h->Next) {
        WIN_ASSERT (h->rec[0]->GetAnzVars() == 1) ;
        LPVOID data = h->rec[0]->Get(0);
        Context->PushPointer (new BinTree (Context->VarToCheck,Context->ActCompCode,data));
        if (!first)
          Context->PushPointer (new BinTree(Context->PopPointer(),Context->PopPointer(),
                                            ((Context->ActCompCode & 31)== BCMP_EQUAL) ? BOP_OR : BOP_AND
                                          )
                              );
        first = FALSE ;
        }
      }
    rb.Clear ();
    if (res != DBCALL_SUCCESS) break;
    } 
  if (first)    // Immer noch nix getan
    Context->PushPointer (new BinTree (((Context->ActCompCode & 31) == BCMP_EQUAL) ? FALSE : TRUE )) ;

  DBCall_Work (DBOP_RESET,0,NULL,&hstmt,NULL);

  req->ClearParams();
  req->FreeTableDefs();
  FreeRequest (req);

  FreeGlobMem (command);
  }
DLLExport void _export DoSubQuery_Sing ()
  {
  LPSTR command = LPSTR (GetGlobMem (Context->SQLCmp->GetActPtr() - Context->SubQueryStart));
  lmemcpy (command,Context->SubQueryStart,Context->SQLCmp->GetActPtr() - Context->SubQueryStart - 1);
  LPDBREQUEST req = InitializeRequest (command,1,DBCALLTYPE_EXECUTE,Context->stmt->req->DocID);
  for (int i = 2 ; i < CB_PARAM ; i++) {
    if (Context->stmt->req->Param[i] != NULL) {
      req->SetParam (i,Context->stmt->req->Param[i],GetBlockSize(Context->stmt->req->Param[i]));
      req->SetParamType (i,Context->stmt->req->ParamType[i]);
      }
    }
  req->AnzParam = Context->stmt->req->AnzParam;
  LPVOID hstmt = NULL;
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  int res = DBCall_Work (DBOP_GETFIRST,1,req,&hstmt,&rb);
  if (res == DBCALL_SUCCESS) {
    RecBufferLine FAR *h = rb.First() ;
    WIN_ASSERT (h->rec[0]->GetAnzVars() == 1) ;
    LPVOID data = h->rec[0]->Get(0);
    Push (data,GetBlockSize(data));
    }
  else
    Push (NULL,0) ;
  rb.Clear ();

  DBCall_Work (DBOP_RESET,0,NULL,&hstmt,NULL);

  req->ClearParams();
  req->FreeTableDefs();
  FreeRequest (req);

  FreeGlobMem (command);
  }

DLLExport void _export InitializeSelect ()
  {
  Context->VarNames.Init();
  Context->TableNames.Init();
  }
DLLExport void _export InitializeUpdate ()
  {
  Context->VarNames.Init();
  Context->TableNames.Init();
  Context->UpdateCommands.Init();
  Context->UpdatePos.Init();
  }
DLLExport void _export PushVarName ()
  {
  LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  Context->VarNames.Push (Name);
  GlobalUnlock (Context->SQLCmp->hPars0);
  }
DLLExport void _export MarkAggregat ()
  {
  Context->PushToAggregatList ();
  }
DLLExport void _export PushAllVars ()
  {
  Context->VarNames.Push ("*");
  }
void StartUpdateCommand ()
  {
  LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  Context->SubQueryStart = Context->SQLCmp->GetActPtr() - lstrlen(Name);
  GlobalUnlock (Context->SQLCmp->hPars0);
  }
DLLExport void _export PushUpdateVarName ()
  {
  PushVarName();
  StartUpdateCommand();
  }
DLLExport void _export EndUpdateCommand ()
  {
  int mlen = 0;
  switch (Context->SQLCmp->scv.v.k_ident) {
    case SQLKW_WHERE :
      mlen = 5;
      break ;
    case SQLKW_COLON :
      mlen = 1 ;
      break ;
    }
  int clen = Context->SQLCmp->GetActPtr() - Context->SubQueryStart - mlen;
  LPSTR command = LPSTR (GetGlobMem (clen + 1));
  lmemcpy (command,Context->SubQueryStart,clen);
  Context->UpdateCommands.Push (command);
  FreeGlobMem (command);
  Context->SQLCmp->PutTermBack();
  }
DLLExport void _export PushTableName ()
  {
  LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  Context->TableNames.Push (Name);
  GlobalUnlock (Context->SQLCmp->hPars0);
  }
DLLExport void _export CreateTempTableFunc (BOOL withPrimKey)
  {
  if (Context->td == NULL) {
    // 
    // Den Primaerschluessel auf jeden Fall auch noch mitnehmen
    // 
    if (withPrimKey) {
      BOOL correct;
      WORD Version;
      WORD TableID = GetTableAdmin()->GetTableID (NULL,Context->TableNames.Strs[0],&correct,&Version);
      if (correct) {
        LPTABLEDEF tmain = GetTableAdmin()->GetTableDef (TableID,Version);
        for (int i = 0 ; i < tmain->GetAnzKeySegs () ; i++) {
          LPCLKEYDEF k = tmain->GetKeyDef (i);
          if (k->KeyNmbr == 0)
            Context->VarNames.Push (tmain->GetVarDef(k->VarID)->GetName());
          }
        GetTableAdmin()->FreeTable(TableID,Version);
        }
      }
    Context->td = GetTableAdmin()->GetTemporaryTable (
            Context->VarNames.AnzStrings,Context->VarNames.Strs,
            Context->TableNames.AnzStrings,Context->TableNames.Strs
                                                     );
    if (Context->td != NULL) {
      Context->stmt->TempTableID = Context->td->GetTableID();
      LPTABLEDEF td = Context->td;
      LPINTTABLE ti = LPINTTABLE(td->GetDLLDef());
      for (WORD i = 0 ; i < ti->AnzTables ; i++) {
        LPPTABLE pt    = ti->GetTableByNum (i);
        Context->stmt->req->AddTableDef (pt->tRef.TableNr,pt->tRef.Version,FALSE);
        }
      Context->stmt->req->SetNewDimension (td->GetAnzVars());
      for (i = 0 ; i < WORD(td->GetAnzVars()) ; i++) {
        ReqElem e;
        ti->GetReqElem (&e,i);
        Context->stmt->req->SetReqElemDirect (i,e.TableNumber,e.VarID);
        }
      Context->stmt->req->SetTableID(td->GetTableID(),td->GetVersion());
      Context->t = LPBTRVTABLE(Context->stmt->req->TableDef[0]->GetDLLDef());
      InitializeKeyList (Context->t,NULL);
      GetFile (Context->stmt,TRUE);
      if (!Context->stmt->File->isOpen)
        Context->SQLCmp->wError = SEM_ERROR;
      }
    else
      Context->SQLCmp->wError = SEM_ERROR;
    }
  Context->VarNames.Clear();
  Context->TableNames.Clear();
  }
DLLExport void _export CreateSelectTempTable ()
  {
  CreateTempTableFunc (FALSE);
  }
DLLExport void _export CreateTempTable ()
  {
  CreateTempTableFunc (TRUE);
  }
DLLExport void _export CreateDelTempTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  Context->TableNames.Push (Name);
  GlobalUnlock (Context->SQLCmp->hPars0);
  BOOL correct = TRUE ;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,Context->TableNames.Strs[0],&correct,&Version);
  if (correct) {
    LPTABLEDEF tdel = GetTableAdmin()->GetTableDef (TableID,Version);
    Context->VarNames.Push (tdel->GetVarDef(0)->GetName());
    GetTableAdmin()->FreeTable(TableID,Version);
    }
  CreateTempTable ();
  if (!correct)
    Context->SQLCmp->wError = SEM_ERROR;
  }
DLLExport void _export PushVar ()
  {
  BOOL pushDone = FALSE ;
  if (Context->updateRecord != NULL) {
    LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
    for (int i = 0 ; i < Context->td->GetAnzVars () ; i++) {
      LPVARDEF v = Context->td->GetVarDef(i) ;
      if (lstrcmp (v->GetName(),Name) == 0) {
        LPVOID val = Context->updateRecord->Get(i);
        Push (val,GetBlockSize(val));
        switch (v->mType) {
          case VAR_LONG :
          case VAR_STRARR :
          case VAR_FLAG :
            Context->PushDataType (CTYPE_INTEGER);
            break ;
          case VAR_STR :
            Context->PushDataType (CTYPE_STRING);
            break ;
          default :
            Context->PushDataType (CTYPE_PARAMETER);
          }
        pushDone = TRUE ;
        break ;
        }
      }
    GlobalUnlock (Context->SQLCmp->hPars0);
    }
  if (!pushDone)
    Context->SQLCmp->wError = SEM_ERROR ;
  }
DLLExport void _export FindVarToUpdate ()
  {
  BOOL found = FALSE ;
  LPSTR Name = LPSTR(GlobalLock (Context->SQLCmp->hPars0)) + sizeof(WORD);
  for (int i = 0 ; i < Context->td->GetAnzVars () ; i++) {
    LPVARDEF v = Context->td->GetVarDef(i) ;
    if (lstrcmp (v->GetName(),Name) == 0) {
      Context->varToUpdate = i;
      found = TRUE ;
      break ;
      }
    }
  GlobalUnlock (Context->SQLCmp->hPars0);
  if (!found)
    Context->SQLCmp->wError = SEM_ERROR ;
  }
DLLExport void _export PushNull ()
  {
  Push (NULL,0);
  }
DLLExport void _export SetVarToUpdate ()
  {
  Context->PopDataType ();
  LPVOID val = Pop();
  if (val != NULL)
    Context->updateRecord->Set(Context->varToUpdate,val,GetBlockSize(val));
  else
    Context->updateRecord->Del(Context->varToUpdate);
  }
DLLExport void _export SetPerformUpdate ()
  {
  Context->performUpdate = TRUE ;
  }
DLLExport void _export SetPerformDelete ()
  {
  Context->performDelete = TRUE ;
  }
DLLExport void _export SetValue ()
  {
  if (Context->varToUpdate < Context->stmt->req->AnzElems) {
    SetVarToUpdate ();
    Context->varToUpdate += 1 ;
    }
  else
    Context->SQLCmp->wError = SEM_ERROR ;
  }
DLLExport void _export CreateEmptyRecord ()
  {
  Context->updateRecord = new DBRecord (Context->stmt->req);
  Context->varToUpdate = 0 ;
  }
void InitializePrimKey (LPTABLEDEF t0)
  {
  LPKEYDEF kd = Context->t->GetKey(WORD(0));
  LPVARTBL h = LPVARTBL (kd->Name + lstrlen(kd->Name) + 1) ;
  if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
    LPVBTRV x = &h->v[0];
    for ( ; (x != NULL) ; x = x->Next(h->gSize,h)) {
      if (x->DataType == BDT_AUTOINC) {
        LPVBTRV f = Context->t->GetVar (x->Name,FALSE);
        if ((t0->IsRealTable()) && (OwnCounter())) {
          DBWIN_ASSERT (f->VarLen == sizeof(DWORD));
          DWORD res = GetCounterValue(t0);
          lmemcpy (Context->stmt->File->btrBuffer+f->VarOffset,&res,f->VarLen);
          }
        else
          lmemset (Context->stmt->File->btrBuffer+f->VarOffset,'\0',f->VarLen);
        }
      }
    }
  }
void GetInsertRecord (WORD pos,LPBTRSTATEMENT stmt,BOOL getPrimKey,LPDBRECORD old)
  {
  DBRecord FAR *r = new DBRecord (stmt->req);
  if (r->GetType () == DBR_TYPE_FULL) {
    LPTABLEDEF d = stmt->req->TableDef[0];
    LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
    for (WORD i = 0 ; i < WORD(d->GetAnzVars()) ; i++) {
      LPVARDEF v = d->GetVarDef(i);
      if (v != NULL) {
        if (v->VarID == 0xFFFF) {
          LPDDSVARDESC vd = LPDDSVARDESC (v->GetDLLData());
          LPVBTRV   vb = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
          if (vb->DataType == BDT_AUTOINC)
            r->Initialize (i,stmt->KeyBuffer,vb->VarLen);
          else {
            LPVOID oldData = old->Get (i);
            if (oldData != NULL) {
              if (v->mType == VAR_BLOB) {
                LPBLOBDESC b = LPBLOBDESC(oldData);
                BlobDesc bn = *b ;
                bn.hGmem = GlobalAlloc (GMEM_MOVEABLE,b->Size);
                hmemcpy (GlobalLock (bn.hGmem),GlobalLock (b->hGmem),b->Size);
                r->Initialize (i,&bn,sizeof(bn));
                }
              else
                r->Initialize (i,oldData,GetBlockSize(oldData));
              }
            }
          }
        else {
          LPVOID oldData = old->Get (i);
          if (oldData != NULL)
            r->Initialize (i,oldData,GetBlockSize(oldData));
          }
        }
      }
    }
  else {
    for (WORD i = 0 ; i < r->GetAnzVars() ; i++) {
      WORD VarID;
      BOOL keyDone = FALSE ;
      LPTABLEDEF d = r->GetTableDef (i,&VarID);
      LPVARDEF v = d->GetVarDef(VarID);
      if (r->GetTableNumber (i) == 0) {
        LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
        if (v != NULL) {
          if (v->VarID == 0xFFFF) {
            LPDDSVARDESC vd = LPDDSVARDESC (v->GetDLLData());
            LPVBTRV   vb = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
            if (vb->DataType == BDT_AUTOINC)
              r->Initialize (i,stmt->File->btrBuffer,vb->VarLen) , keyDone = TRUE ;
            }
          }
        }
      if (!keyDone) {
        LPVOID oldData = old->Get (i);
        if (oldData != NULL) {
          if (v->mType == VAR_BLOB) {
            LPBLOBDESC b = LPBLOBDESC(oldData);
            BlobDesc bn = *b ;
            bn.hGmem = GlobalAlloc (GMEM_MOVEABLE,b->Size);
            hmemcpy (GlobalLock (bn.hGmem),GlobalLock (b->hGmem),b->Size);
            r->Initialize (i,&bn,sizeof(bn));
            }
          else
            r->Initialize (i,oldData,GetBlockSize(oldData));
          }
        }
      }
    }
  if (getPrimKey) {
    PrimKey k;
    r->CalcPrimKey (0,&k);
    r->SetPrimKey (&k);
    stmt->res->AddLine (WORD(stmt->req->AnzTables),pos);
    stmt->res->SetRes (0,r);
    }
  }
BOOL PrimKeyDone(DBRecord FAR *h)
  {
  LPTABLEDEF td = Context->stmt->req->TableDef[0];
  for (int i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    LPCLKEYDEF k = td->GetKeyDef (i);
    if (k->KeyNmbr == 0) {
      BOOL done;
      WORD VarNmbr = Context->stmt->req->GetVarNumberByNum (0,k->VarID,&done);
      if ((done) && (h->Get(VarNmbr) != NULL))
        return TRUE ;
      }
    }
  return FALSE ;
  }

BOOL IsCritical (WORD st)
  {
  if ((st == 5) || (st == 10)) return FALSE ;
  return TRUE ;
  }

BOOL IsReadCritical (WORD st)
  {
  switch (st) {
    case 4:
    case 9:
    case 60:
    case 64:
      return FALSE ;
    }
  return TRUE ;
  }

void doWait (int i)
  {
  for (int j = 0 ; j <= (i % 5) ; j++) {
    DWORD t0 = GetTickCount ();
    while ((GetTickCount() - t0) < 200L);
    }
  }

static int FromManipulate;
void MyManipulate (LPDBRECORD r,short UpdateMode,LPTABLEDEF td = NULL,LPVOID KeyBuffer = NULL)
  {
  FromManipulate ++ ;
  OnManipulate (r,UpdateMode,td,KeyBuffer);
  FromManipulate -- ;
  }
int lastError;
BOOL DoInsert (BOOL IsFullDone)
  {
  BOOL result;
  BOOL transactionDone;
  // Da muss nochn Update gemacht werden....
  LPDBRECORD rold = Context->stmt->res->first->rec[0];
  LPDBRECORD rrec = rold;
  if (!rold->IsValid())
    return FALSE ;
  if ((!IsInTransaction ()) && (!InAlter()))
    DoBeginTransaction (FALSE) , transactionDone = TRUE ;
  else
    transactionDone = FALSE ;
  OnUseKey (0,Context->stmt);
  OnInitializeRecord (NULL,Context->stmt);
  BOOL primKeyDone = PrimKeyDone(rold);
  OnSetRecord (NULL,Context->stmt,SRMODE_IGNOREBLOBS,FALSE);
  if (!primKeyDone)
    InitializePrimKey (Context->stmt->req->TableDef[0]);
  BOOL doRepeat = TRUE;
  for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
    OnDBOp (B_INSERT,0,Context->stmt);
    doRepeat = (Context->stmt->opStatus == 84) ;
    if (doRepeat)
      doWait(count);
    }
  if (IsCritical (Context->stmt->opStatus))
    TestST (Context->stmt->opStatus,Context->stmt->File->Path);

  lastError = Context->stmt->opStatus;

  if (Context->stmt->opStatus != 0) {
    if (transactionDone)
      DoAbortTransaction () , transactionDone = FALSE ;
    result = FALSE;
    }
  else
    result = TRUE;

  if ((!IsFullDone) && (result)) {
    // Der Datensatz muss wieder zurueckgeliefert werden
    GetInsertRecord (ADDLINEPOS_END,Context->stmt,!IsFullDone,rold) ;
    rrec = Context->stmt->res->act->rec[0] ;
    }

  if (result) {
    if (IsFullDone)
      MyManipulate (NULL,UPDATEMODE_INSERT,Context->stmt->req->TableDef[0],Context->stmt->KeyBuffer);
    else
      MyManipulate (rrec,UPDATEMODE_INSERT);
    }
  // Noch den BLOB - Teil
  int resOp = OnSetRecord (NULL,Context->stmt,SRMODE_IGNOREFIXED,TRUE);
  if ((result) && (resOp == B_UPDATECHUNK)) {
    UpdateAllChunks (Context->stmt);
    Context->stmt->ClearChunkBuffers();
    }
    
  if (transactionDone)
    DoEndTransaction ();


  return result ;
  }
DLLExport void _export PerformInsert ()
  {
  Context->performInsert = TRUE ;
  if (Context->varToUpdate == int(Context->stmt->req->AnzElems)) {
    Context->stmt->res->AddLine (1,ADDLINEPOS_END);
    PrimKey k;
    Context->updateRecord->CalcPrimKey(0,&k);
    Context->updateRecord->SetPrimKey(&k);
    Context->stmt->res->SetRes (0,Context->updateRecord);
    DoInsert (TRUE);
    delete Context->updateRecord ;
    Context->updateRecord = NULL;
    Context->stmt->res->act->rec[0] = NULL;

    if (Context->stmt->res->first) {
      if (Context->stmt->res->first->rec[0] != NULL)
        delete Context->stmt->res->first->rec[0];
      RecBufferLine FAR *next =  Context->stmt->res->first->Next;
      if (Context->stmt->res->act == Context->stmt->res->first)
        Context->stmt->res->act = next;
      FreeGlobMem (Context->stmt->res->first);
      Context->stmt->res->first = next;
      }
    }
  else
    Context->SQLCmp->wError = SEM_ERROR ;
  }
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

extern syntax_node wheresyntax,sqlx1,sqlt1,ordersyntax,sqlaexp1,afact1,inp4,
                   sqa,ssqa,inlist,sl1,tlist,ze2,zlist,il2,is7;

syntax_node aopl1   = { NULL , NULL   , TRUE , INITERM(KEYWORD,SQLKW_SUB) , OnAOp } ;
syntax_node aopl    = { NULL , &aopl1 , TRUE , INITERM(KEYWORD,SQLKW_ADD) , OnAOp } ;
syntax_node aoph1   = { NULL , NULL   , TRUE , INITERM(KEYWORD,SQLKW_DIVIDE) , OnAOp } ;
syntax_node aoph    = { NULL , &aoph1 , TRUE , INITERM(KEYWORD,SQLKW_MULTIPLY) , OnAOp } ;
syntax_node aterm71 = { NULL     , NULL     , TRUE  , INITERM(KEYWORD,SQLKW_NULL) , SetResNull } ;
syntax_node aterm61 = { NULL     , &aterm71 , TRUE  , INITERM(UNKNOWNIDENT,0) , PushVar } ;
syntax_node ssqa3   = { &ssqa , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node ssqa2   = { &ssqa , NULL  , FALSE , &sqa , NULL } ;
syntax_node ssqa1   = { &ssqa2, &ssqa3 , TRUE , INITERM(KEYWORD,SQLKW_BRACEOPEN) , NULL } ;
syntax_node ssqa    = { NULL  , &ssqa1 , TRUE , INITERM(KEYWORD,SQLKW_BRACECLOSE) , NULL } ;
syntax_node aterm53 = { NULL  , NULL  , FALSE , &sqa , DoSubQuery_Sing } ;
syntax_node aterm52 = { &aterm53 , NULL , TRUE , INITERM(KEYWORD,SQLKW_SELECT) , NULL } ;
syntax_node aterm51 = { &aterm52 , &aterm61 , TRUE , INITERM(KEYWORD,SQLKW_BRACEOPEN) , MarkSubQueryStart } ;
syntax_node aterm41 = { NULL     , &aterm51 , TRUE , INITERM(STRING,0) , OnConstString } ;
syntax_node aterm31 = { NULL     , &aterm41 , TRUE , INITERM(DECIMAL,0) , OnConstDec } ;
syntax_node aterm21 = { NULL     , &aterm31 , TRUE , INITERM(T_INTEGER,0) , OnConstInt } ;
syntax_node aterm11 = { NULL     , NULL     , TRUE , INITERM(T_INTEGER,0) , OnParameter } ;
syntax_node aterm   = { &aterm11 , &aterm21 , TRUE , INITERM(KEYWORD,SQLKW_PARPRE) , NULL } ;
syntax_node afact3  = { NULL    , NULL    , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node afact2  = { &afact1 , NULL    , FALSE , &aterm , CalcTerm } ;
syntax_node afact1  = { &afact2 , &afact3 , FALSE , &aoph  , NULL } ;
syntax_node afact   = { &afact1 , NULL    , FALSE , &aterm , NULL } ;
syntax_node sqlaexp3 = { NULL      , NULL      , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node sqlaexp2 = { &sqlaexp1 , NULL      , FALSE , &afact , CalcTerm } ;
syntax_node sqlaexp1 = { &sqlaexp2 , &sqlaexp3 , FALSE , &aopl  , NULL } ;
syntax_node sqlaexp  = { &sqlaexp1 , NULL      , FALSE , &afact , NULL } ;

syntax_node sqa3    = { &sqa  , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node sqa2    = { &sqa  , NULL  , FALSE , &sqa , NULL } ;
syntax_node sqa1    = { &sqa2 , &sqa3 , TRUE , INITERM(KEYWORD,SQLKW_BRACEOPEN) , NULL } ;
syntax_node sqa     = { NULL  , &sqa1 , TRUE , INITERM(KEYWORD,SQLKW_BRACECLOSE) , NULL } ;
syntax_node inl3    = { NULL  , NULL , TRUE , INITERM(KEYWORD,SQLKW_BRACECLOSE) , OnEndOperator_List } ;
syntax_node inl2    = { NULL  , NULL , FALSE , &inlist , NULL } ;
syntax_node inl1    = { &inl2 , &inl3 , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , OnConnectTypeColon } ;
syntax_node inlist  = { &inl1 , NULL , FALSE , &sqlaexp , OnExpRes } ;
syntax_node inp5    = { NULL  , NULL , FALSE , &inlist , NULL } ;
syntax_node inp4    = { NULL  , &inp5 , TRUE , INITERM(KEYWORD,SQLKW_BRACECLOSE) , CreateConstForInOperator } ;
syntax_node inp2    = { NULL  , NULL  , FALSE , &sqa , DoSubQuery_In } ;
syntax_node inp1    = { &inp2 , &inp4 , TRUE , INITERM(KEYWORD,SQLKW_SELECT) , NULL } ;
syntax_node inp     = { &inp1 , NULL , TRUE , INITERM(KEYWORD,SQLKW_BRACEOPEN) , MarkSubQueryStart } ;
syntax_node likep2  = { NULL    , NULL    , TRUE , INITERM(T_INTEGER,0) , OnParameter } ;
syntax_node likep1  = { &likep2 , NULL    , TRUE , INITERM(KEYWORD,SQLKW_PARPRE) , NULL } ;
syntax_node likep   = { NULL    , &likep1 , TRUE , INITERM(STRING,0) , OnConstString } ;
syntax_node sqlp5   = { NULL   , NULL , FALSE , &inp , NULL } ;
syntax_node sqlp4   = { &sqlp5 , NULL , TRUE , INITERM(KEYWORD,SQLKW_IN) , InitializePerformMore } ;
syntax_node sqlp3   = { &sqlp4 , NULL , TRUE  , INITERM(KEYWORD,SQLKW_NOT) , OnCompareType } ;
syntax_node sqlp2   = { &sqlp5 , &sqlp3 , TRUE  , INITERM(KEYWORD,SQLKW_IN) , OnCompareType_InitializePerformMore } ;
syntax_node sqlp1   = { NULL   , NULL , FALSE , &likep , CreateLikeNode } ;
syntax_node sqlpred = { &sqlp1 , &sqlp2 , TRUE  , INITERM(KEYWORD,SQLKW_LIKE) , NULL } ;
syntax_node sqlcmp6 = { NULL , NULL     , TRUE  , INITERM(KEYWORD,SQLKW_LESSEQUAL) , OnCompareType } ;
syntax_node sqlcmp5 = { NULL , &sqlcmp6 , TRUE  , INITERM(KEYWORD,SQLKW_LESS) , OnCompareType } ;
syntax_node sqlcmp4 = { NULL , &sqlcmp5 , TRUE  , INITERM(KEYWORD,SQLKW_GREATEREQUAL) , OnCompareType } ;
syntax_node sqlcmp3 = { NULL , &sqlcmp4 , TRUE  , INITERM(KEYWORD,SQLKW_GREATER) , OnCompareType } ;
syntax_node sqlcmp2 = { NULL , &sqlcmp3 , TRUE  , INITERM(KEYWORD,SQLKW_NOTEQUAL) , OnCompareType } ;
syntax_node sqlcmp1 = { NULL , &sqlcmp2 , TRUE  , INITERM(KEYWORD,SQLKW_EQUAL) , OnCompareType } ;
syntax_node sqlc3   = { NULL   , NULL   , FALSE , &sqlpred , NULL } ;
syntax_node sqlc2   = { NULL   , NULL   , FALSE , &sqlaexp , OnExpRes } ;
syntax_node sqlc1   = { &sqlc2 , &sqlc3 , FALSE , &sqlcmp1 , NULL } ;
syntax_node sqlcond = { &sqlc1 , NULL   , TRUE  , INITERM(UNKNOWNIDENT,0) , OnVarName } ;

syntax_node sqlf3       = { NULL   , NULL    , TRUE  , INITERM(KEYWORD,SQLKW_BRACECLOSE) , NULL } ;
syntax_node sqlf2       = { &sqlf3 , NULL    , FALSE , &wheresyntax , NULL } ;
syntax_node sqlf1       = { &sqlf2 , NULL    , TRUE  , INITERM(KEYWORD,SQLKW_BRACEOPEN) , NULL } ;
syntax_node wherefaktor = { NULL   , &sqlf1  , FALSE , &sqlcond , NULL } ;
syntax_node sqlt3       = { NULL   , NULL    , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node sqlt2       = { &sqlt1 , NULL    , FALSE , &wherefaktor , OnEndOperator } ;
syntax_node sqlt1       = { &sqlt2 , &sqlt3  , TRUE  , INITERM(KEYWORD,SQLKW_AND) , OnConnectType } ;
syntax_node whereterm   = { &sqlt1 , NULL    , FALSE , &wherefaktor , NULL } ;
syntax_node sqlx4       = { NULL   , NULL    , TRUE  , INITERM(FREECHAR,0) , NULL } ; 
syntax_node sqlx3       = { NULL   , NULL    , TRUE  , INITERM(FREECHAR,0) , NULL } ; 
syntax_node sqlx2       = { &sqlx1 , NULL    , FALSE , &whereterm , OnEndOperator } ;
syntax_node sqlx1       = { &sqlx2 , &sqlx3  , TRUE  , INITERM(KEYWORD,SQLKW_OR) , OnConnectType } ;
syntax_node wheresyntax = { &sqlx1 , NULL    , FALSE , &whereterm , NULL } ;
syntax_node sqlwe       = { NULL   , NULL    , TRUE  , INITERM(KEYWORD,SQLKW_END) , NULL } ;
syntax_node whereexp    = { &sqlwe , NULL    , FALSE , &wheresyntax , NULL } ;

syntax_node oexp2       = { NULL         , NULL   , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node oexp1       = { &ordersyntax , &oexp2 , TRUE , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
syntax_node ordersyntax = { &oexp1       , NULL   , TRUE , INITERM(UNKNOWNIDENT,0) , CheckValidKeySegment } ;
syntax_node ordere      = { NULL      , NULL   , TRUE , INITERM(KEYWORD,SQLKW_END) , NULL } ;
syntax_node orderexp    = { &ordere   , NULL   , FALSE , &ordersyntax , NULL } ;

syntax_node il5           = { NULL   , NULL  , TRUE  , INITERM(FREECHAR,0) , PushAllVars } ;
syntax_node il4           = { NULL   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_BRACECLOSE) , NULL } ;
syntax_node il3           = { &il2   , &il4  , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
syntax_node il2           = { &il3   , NULL  , TRUE  , INITERM(UNKNOWNIDENT,0) , PushVarName } ;
syntax_node il1           = { &il2   , &il5  , TRUE  , INITERM(KEYWORD,SQLKW_BRACEOPEN) , NULL } ;

syntax_node is10          = { NULL   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_END) , NULL } ;
syntax_node is9           = { &is10  , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_BRACECLOSE) , PerformInsert } ;
syntax_node is8           = { &is7   , &is9  , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
//syntax_node is7           = { &is8   , NULL  , FALSE , &aterm , SetValue } ;
syntax_node is7           = { &is8   , NULL  , FALSE , &sqlaexp , SetValue } ;
syntax_node is6           = { &is7   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_BRACEOPEN) , CreateEmptyRecord } ;
syntax_node is5           = { &is6   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_VALUES) , NULL } ;
syntax_node is4           = { &is5   , NULL  , FALSE , &il1 , CreateSelectTempTable } ;
syntax_node is3           = { &is4   , NULL  , TRUE  , INITERM(UNKNOWNIDENT,0) , PushTableName } ;
syntax_node is2           = { &is3   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_INTO) , NULL } ;
syntax_node is1           = { &is2   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_INSERT) , InitializeUpdate } ;

syntax_node ds6           = { NULL   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_END) , SetPerformDelete } ;
syntax_node ds5           = { &ds6   , NULL  , FALSE , &wheresyntax , NULL } ;
syntax_node ds4           = { &ds5   , &ds6  , TRUE  , INITERM(KEYWORD,SQLKW_WHERE) , NULL } ;
syntax_node ds3           = { &ds4   , NULL  , TRUE  , INITERM(UNKNOWNIDENT,0) , CreateDelTempTable } ;
syntax_node ds2           = { &ds3   , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_FROM) , NULL } ;
syntax_node ds1           = { &ds2   , &is1  , TRUE  , INITERM(KEYWORD,SQLKW_DELETE) , InitializeUpdate } ;

syntax_node upt2          = { NULL   , NULL  , FALSE , &sqlaexp , NULL } ;
syntax_node updterm       = { NULL   , &upt2 , TRUE  , INITERM(KEYWORD,SQLKW_NULL) , PushNull } ;
syntax_node uex2          = { NULL   , NULL  , FALSE , &updterm , SetVarToUpdate } ;
syntax_node uex1          = { &uex2  , NULL  , TRUE  , INITERM(KEYWORD,SQLKW_EQUAL) , NULL } ;
syntax_node updExp        = { &uex1  , NULL  , TRUE  , INITERM(UNKNOWNIDENT,0) , FindVarToUpdate } ;

syntax_node ze5           = { &ze2   , NULL , TRUE  , INITERM(T_ALL,0) , NULL } ;
syntax_node ze4           = { NULL   , &ze5 , TRUE  , INITERM(KEYWORD,SQLKW_END) , EndUpdateCommand } ;
syntax_node ze3           = { NULL   , &ze4 , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , EndUpdateCommand } ;
syntax_node ze2           = { NULL   , &ze3 , TRUE  , INITERM(KEYWORD,SQLKW_WHERE) , EndUpdateCommand } ;
syntax_node ze1           = { &ze2   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_EQUAL) , NULL } ;
syntax_node zelem         = { &ze1   , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , PushUpdateVarName } ;
syntax_node zl2           = { NULL   , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node zl1           = { &zlist , &zl2 , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
syntax_node zlist         = { &zl1   , NULL , FALSE , &zelem , NULL } ;
syntax_node us7           = { NULL   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_END) , SetPerformUpdate } ;
syntax_node us6           = { &us7   , NULL , FALSE , &wheresyntax , NULL } ;
syntax_node us5           = { &us6   , &us7 , TRUE  , INITERM(KEYWORD,SQLKW_WHERE) , NULL } ;
syntax_node us4           = { &us5   , NULL , FALSE , &zlist , CreateTempTable } ;
syntax_node us3           = { &us4   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_SET) , NULL } ;
syntax_node us2           = { &us3   , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , PushTableName } ;
syntax_node us1           = { &us2   , &ds1 , TRUE  , INITERM(KEYWORD,SQLKW_UPDATE) , InitializeUpdate } ;

syntax_node sfn1     = { NULL , NULL  , TRUE , INITERM(KEYWORD,SQLKW_MIN) , SetSFnc } ;
syntax_node sfncname = { NULL , &sfn1 , TRUE , INITERM(KEYWORD,SQLKW_MAX) , SetSFnc } ;
syntax_node tl2           = { NULL   , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node tl1           = { &tlist , &tl2 , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
syntax_node tlist         = { &tl1   , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , PushTableName } ;
syntax_node sl7           = { NULL   , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node sl6           = { &sl1   , &sl7 , TRUE  , INITERM(KEYWORD,SQLKW_COLON) , NULL } ;
syntax_node sl5           = { &sl6   , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , PushVarName } ;
syntax_node sl4           = { &sl6   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_BRACECLOSE) , MarkAggregat } ;
syntax_node sl3           = { &sl4   , NULL , TRUE  , INITERM(UNKNOWNIDENT,0) , PushVarName } ;
syntax_node sl2           = { &sl3   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_BRACEOPEN) , NULL } ;
syntax_node sl1           = { &sl2   , &sl5 , FALSE , &sfncname, NULL } ;
syntax_node slist         = { NULL   , &sl1 , TRUE  , INITERM(KEYWORD,SQLKW_MULTIPLY) , NULL } ;
syntax_node fse           = { NULL   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_END) , NULL } ; 
syntax_node fs7           = { &fse   , NULL , FALSE , &ordersyntax , NULL } ;
syntax_node fs6           = { &fs7   , &fse , TRUE  , INITERM(KEYWORD,SQLKW_ORDER) , NULL } ;
syntax_node fs5           = { &fs6   , NULL , FALSE , &wheresyntax , NULL } ;
syntax_node fs4           = { &fs5   , &fse , TRUE  , INITERM(KEYWORD,SQLKW_WHERE) , NULL } ;
syntax_node fs3           = { &fs4   , NULL , FALSE , &tlist , CreateSelectTempTable } ;
syntax_node fs2           = { &fs3   , NULL , TRUE  , INITERM(KEYWORD,SQLKW_FROM) , NULL } ;
syntax_node fs1           = { &fs2   , NULL , FALSE , &slist , NULL } ;
syntax_node fullstatement = { &fs1   , &us1 , TRUE  , INITERM(KEYWORD,SQLKW_SELECT) , InitializeSelect } ;

// Variablen fuer Kontextwiederherstellung
static BOOL InJoin = FALSE;
static LPBFILE ParentFile;
static BOOL RestorePos;
static DWORD SavedPos;

/*-----< Einige Hilfsfunktionen >--------*/
int NextRejectCount (int AnzDone,BOOL RejectCountSet,int actRes)
  {
  if ((actRes > 1) && (RejectCountSet)) {
    if (AnzDone == 0) {
      if (actRes <= 20) actRes = 100 ;
      else if (actRes <= 100) actRes = 1000 ;
      else if (actRes <= 1000) actRes = 5000 ;
      }
    else
      actRes = 20 ;
    }
  return actRes;
  }
int GetFurtherRecs (LPSTR buffer,WORD Op,PKeyList FAR *k,BOOL IsFullDone,int result,BOOL doStore = TRUE)
  {
  WORD BOp,Pos ;
  int RecsRead = 0 ;
  int anzRecsDone = 0 ;
  int MyRejectCount = 0 ;

  for ( ; Context->stmt->opStatus == 0 ; ) {
    WORD fOffs = SetFilter (Context->stmt,buffer,Context->stmt->filter);
    WORD Cmd = SetFieldsToExtract (buffer,fOffs,Context->stmt->req,0,Context->stmt->RecsToGet);
    switch (Cmd) {
      case USE_GETNEXTEXTENDED :
        if (Op == DBOP_GET) {
          if ((k->B_Command == B_GETL) || (k->B_Command == B_GETLE))
            BOp = B_GETPREVEXTENDED , Pos = ADDLINEPOS_START ;
          else
            BOp = B_GETNEXTEXTENDED , Pos = ADDLINEPOS_END ;
          }
        else if ((Op == DBOP_GETFIRST) ||  (Op == DBOP_GETNEXT))
          BOp = B_GETNEXTEXTENDED , Pos = ADDLINEPOS_END ;
        else
          BOp = B_GETPREVEXTENDED , Pos = ADDLINEPOS_START ;
        Context->stmt->bufferSize = BUFFER_SIZE;
        Context->stmt->opStatus = 
          BTRCALL (BOp,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                    LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                    (char) k->k->KeyNmbr
                  );
        // neue Stelle von GetDBPositions
        // (fuer den Fall, dass StoreMulti den Inhalt des buffers zerstoert)
        if ((Context->performUpdate) || (Context->performDelete))
          GetDBPositions (buffer);
        if ((!Context->performDelete) && (doStore)) {
          BOOL oldInJoin = InJoin;
          if (!oldInJoin) {
            InJoin = TRUE;
            ParentFile = Context->stmt->File;
            RestorePos = FALSE;
            }
          if ((Context->stmt->opStatus == 0) || 
                (Context->stmt->opStatus == ENDOFFILE) ||
                (Context->stmt->opStatus == REJECT_COUNT) ||
                (Context->stmt->opStatus == REJECT_NOMORE))
            anzRecsDone = ((RecordImage_header FAR *) Context->stmt->File->btrBuffer)->AnzRecords;
          else
            anzRecsDone = 0 ;

          StoreMulti (Pos,Context->stmt,!IsFullDone,k->KeyBuffer,char (k->k->KeyNmbr));
          if (!oldInJoin) {
            InJoin = FALSE;
            if (RestorePos) {
              // Join auf selbe Tabelle -> Kontext muss wiederhergestellt werden
              Context->stmt->bufferSize = BUFFER_SIZE;
              *(LPDWORD)buffer = SavedPos;
              WORD myopStatus = 
                BTRCALL (B_GETDIRECT,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                          LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                          (char) k->k->KeyNmbr
                        );
              TestST (myopStatus,Context->stmt->File->Path);
              }
            }
          }
        else {
          RecordImage_header FAR *hd = (RecordImage_header FAR *) buffer;
          Context->stmt->RecsToGet -= hd->AnzRecords ;
          }
        // ehemalige Stelle von GetDBPositions
        if ((Context->stmt->opStatus == ENDOFFILE) ||
            (Context->stmt->opStatus == REJECT_NOMORE))
          result = (Op == DBOP_GET) ? DBCALL_NODATA : DBCALL_ENDOFFILE ;
        else {
          if (IsReadCritical (Context->stmt->opStatus))
            TestST (Context->stmt->opStatus,Context->stmt->File->Path);
          result = (Context->stmt->opStatus != 0) ? DBCALL_NODATA : DBCALL_SUCCESS ;
          }
        if (Context->stmt->RecsToGet == 0) break ;
        if ((Context->stmt->opStatus == REJECT_COUNT) && ((Context->stmt->RejectCount > 1) || (!Context->stmt->RejectCountSet))) {
          // Da muss noch haendisch getestet werden
          WORD GetCommand = (BOp == B_GETNEXTEXTENDED) ? B_GETNEXT : B_GETPREV ;
          Context->stmt->bufferSize = BUFFER_SIZE ;
          WORD myopStatus = 
            BTRCALL (GetCommand,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                      LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                      (char) k->k->KeyNmbr
                  );
          if (myopStatus == 0) {
            if (TestFilter (Context->stmt)) {
              // Datensatz ist gueltig -> weiterverarbeiten
              if ((!Context->performDelete) && (doStore)) {
                BOOL oldInJoin = InJoin;
                if (!oldInJoin) {
                  InJoin = TRUE;
                  ParentFile = Context->stmt->File;
                  RestorePos = FALSE;
                  }
                WORD oldStatus = Context->stmt->opStatus ;
                Context->stmt->opStatus = 0 ;
                OnStore (Pos,Context->stmt,!IsFullDone);
                Context->stmt->opStatus = oldStatus ;
                if (!oldInJoin) {
                  InJoin = FALSE;
                  if (RestorePos) {
                    // Join auf selbe Tabelle -> Kontext muss wiederhergestellt werden
                    Context->stmt->bufferSize = BUFFER_SIZE;
                    *(LPDWORD)buffer = SavedPos;
                    WORD myopStatus = 
                      BTRCALL (B_GETDIRECT,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                                LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                                (char) k->k->KeyNmbr
                              );
                    TestST (myopStatus,Context->stmt->File->Path);
                    }
                  }
                }
              else {
                Context->stmt->RecsToGet -= 1;
                }
              if ((Context->performUpdate) || (Context->performDelete)) {
                OnDBOp (B_GETPOS,0,Context->stmt);
                Context->PushPos ();
                }
        
              // Und weiter wird gemacht...
              result = DBCALL_SUCCESS ;
              Context->stmt->opStatus = 0 ;  
              }
            else {
              if (TestFilter (Context->stmt->Testfilter,Context->stmt)) {
                // Der Datensatz ist zwar nicht gueltig, aber trotzdem sollte
                // weitergemacht werden, da der Beweis, dass nichts mehr kommt,
                // nicht gelungen ist....
                result = DBCALL_SUCCESS ;
                Context->stmt->opStatus = 0 ;  
                Context->stmt->RejectCount = NextRejectCount (anzRecsDone,Context->stmt->RejectCountSet,Context->stmt->RejectCount);
                }
              else
                // Da kann sicher nichts mehr kommen -> abbrechen
                result = (Op == DBOP_GET) ? DBCALL_NODATA : DBCALL_ENDOFFILE ;
              }
            }
          else
            result = (Op == DBOP_GET) ? DBCALL_NODATA : DBCALL_ENDOFFILE ;
          }
        else
          result = (Op == DBOP_GET) ? DBCALL_NODATA : DBCALL_ENDOFFILE ;
        break ;
      case USE_GETFULL :
      case USE_GETPART :
        if ((Op == DBOP_GETFIRST) || (Op == DBOP_GET) || (Op == DBOP_GETNEXT))
          BOp = B_GETNEXT , Pos = ADDLINEPOS_END ;
        else
          BOp = B_GETPREV , Pos = ADDLINEPOS_START ;
        if (Cmd == USE_GETFULL)
          Context->stmt->bufferSize = BUFFER_SIZE;
        else
          Context->stmt->bufferSize = Context->stmt->GetFirstBufferSize();
        Context->stmt->opStatus = 
          BTRCALL (BOp,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                    LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                    (char) k->k->KeyNmbr
                  );
        if ((Context->stmt->opStatus == 22) && (Cmd == USE_GETPART))
          Context->stmt->opStatus = 0 ;
        if (Context->stmt->opStatus == 0) {
          if (TestFilter (Context->stmt)) {
            RecsRead ++ ;
            MyRejectCount = 0 ;
            if ((!Context->performDelete) && (doStore)) {
              BOOL oldInJoin = InJoin;
              if (!oldInJoin) {
                InJoin = TRUE;
                ParentFile = Context->stmt->File;
                RestorePos = FALSE;
                }
              OnStore (Pos,Context->stmt,!IsFullDone);
              if (!oldInJoin) {
                InJoin = FALSE;
                if (RestorePos) {
                  // Join auf selbe Tabelle -> Kontext muss wiederhergestellt werden
                  Context->stmt->bufferSize = BUFFER_SIZE;
                  *(LPDWORD)buffer = SavedPos;
                  WORD myopStatus = 
                    BTRCALL (B_GETDIRECT,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                              LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                              (char) k->k->KeyNmbr
                            );
                  TestST (myopStatus,Context->stmt->File->Path);
                  }
                }
              }
            else {
              Context->stmt->RecsToGet -= 1 ;
              }
            if ((Context->performUpdate) || (Context->performDelete)) {
              // Position vermerken
              int j = Context->UpdatePos.AnzPos ;
              Context->UpdatePos.Enlarge (1) ;
              DWORD recPosition;
              unsigned bs = sizeof(DWORD);
              WORD myopStatus = 
                BTRCALL (B_GETPOS,Context->stmt->File->pb,LPSTR(&recPosition),&bs,
                          NULL,0,(char) Context->stmt->KeyNmbr
                        );
              TestST (myopStatus,Context->stmt->File->Path);
              Context->UpdatePos.SetPos (j++,recPosition);
              }
            }
          else {
            // Datensatz entspricht nicht der Spezifikation
            if (((Context->stmt->Testfilter != NULL) &&
                (!TestFilter (Context->stmt->Testfilter,Context->stmt))) ||
                ((Context->stmt->Testfilter == NULL) && (Context->stmt->RejectCount == 1))) {
              // Er entspricht nicht einmal der minimalspezifikation
              Context->stmt->opStatus = REJECT_NOMORE ;
              }
#ifdef UEBERLEGT
            // Rejectcount - Handling nicht mitnehmen
            else if (Context->stmt->Testfilter == NULL) {
              // Rejectcount wird simuliert
              MyRejectCount ++ ;
              int MaxReject = (Context->stmt->RejectCountSet) ? Context->stmt->RejectCount : 0x7FFF ;
              if (MyRejectCount >= MaxReject)
                Context->stmt->opStatus = REJECT_COUNT ;
              }
#endif
            }
          }
        if (IsReadCritical (Context->stmt->opStatus))
          TestST (Context->stmt->opStatus,Context->stmt->File->Path);
        if (Context->stmt->opStatus != 0) {
          if (Op == DBOP_GET) result = DBCALL_NODATA ;
          else                result = DBCALL_ENDOFFILE ;
          }
        else
          result = DBCALL_SUCCESS ;
        if (Context->stmt->RecsToGet == 0) break ;
        break ;
      }
          
    if (Context->stmt->RecsToGet == 0) break ;
    }
  return result;
  }

void UpdateRecs (BOOL reread)
  {
  BOOL transactionDone;
  // Da muss nochn Update gemacht werden....
  if (!IsInTransaction ())
    DoBeginTransaction (FALSE) , transactionDone = TRUE ;
  else
    transactionDone = FALSE ;
  
  OnUseKey (0,Context->stmt);
  
  RecBufferLine FAR *h = Context->stmt->res->First();
  for (int i = 0 ; i < int (Context->UpdatePos.AnzPos) ; i++ , h = Context->stmt->res->First() ) {
    Context->updateRecord = h->rec[0];
    if ((reread) || (Context->UpdatePos.AnzPos > 1)) {
      Context->stmt->recPosition = Context->UpdatePos.Pos[i];
      OnDBOp (B_GETDIRECT,0,Context->stmt);
      TestST (Context->stmt->opStatus,Context->stmt->File->Path);
      }
    for (int j = 0 ; j < Context->UpdateCommands.AnzStrings ; j++) {
      Context->SQLCmp->DoParse (Context->UpdateCommands.Strs[j],&updExp,NULL);
      Context->SQLCmp->DeinstallBuffer ();
      }
    OnSetRecord (NULL,Context->stmt);
    BOOL doRepeat = TRUE;
    for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
      OnDBOp (B_UPDATE,0,Context->stmt);
      doRepeat = (Context->stmt->opStatus == 84) ;
      if (doRepeat)
        doWait(i);
      }
    if (IsCritical (Context->stmt->opStatus))
      TestST (Context->stmt->opStatus,Context->stmt->File->Path);
    if (Context->stmt->opStatus == 0) {
      PrimKey k;
      Context->updateRecord->CalcPrimKey (0,&k);
      Context->updateRecord->SetPrimKey (&k);
      MyManipulate (Context->updateRecord,UPDATEMODE_UPDATE);
      }
    delete Context->updateRecord ;
    Context->updateRecord = NULL ;
    if (Context->stmt->opStatus != 0) {
      if (transactionDone) {
        DoAbortTransaction () , transactionDone = FALSE ;
        }
      break ;
      }
    }
  if (transactionDone)
    DoEndTransaction ();

  Context->UpdateCommands.Clear();
  Context->UpdatePos.Clear();

  Context->stmt->res->Clear ();
  }
void DelRecs (BOOL reread)
  {
  BOOL transactionDone;
  // Da muss nochn Update gemacht werden....
  if (!IsInTransaction ())
    DoBeginTransaction (FALSE) , transactionDone = TRUE ;
  else
    transactionDone = FALSE ;
  
  OnUseKey (0,Context->stmt);
  for (int i = 0 ; i < int (Context->UpdatePos.AnzPos) ; i++ ) {
    if ((reread) || (Context->UpdatePos.AnzPos > 1)) {
      Context->stmt->recPosition = Context->UpdatePos.Pos[i];
      OnDBOp (B_GETDIRECT,0,Context->stmt);
      if (Context->stmt->opStatus == 22)  // Der wird einfach ignoriert
        Context->stmt->opStatus = 0 ;
      TestST (Context->stmt->opStatus,Context->stmt->File->Path);
      MyManipulate (NULL,UPDATEMODE_DELETE,Context->stmt->req->TableDef[0],Context->stmt->KeyBuffer);
      }
    BOOL doRepeat = TRUE ;
    for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
      OnDBOp (B_DELETE,0,Context->stmt);
      doRepeat = (Context->stmt->opStatus == 84) ;
      if (doRepeat)
        doWait (count);
      }
    TestST (Context->stmt->opStatus,Context->stmt->File->Path);
    if (Context->stmt->opStatus != 0) {
      if (transactionDone) {
        DoAbortTransaction () , transactionDone = FALSE ;
        }
      break ;
      }
    }
  if (transactionDone)
    DoEndTransaction ();

  Context->UpdatePos.Clear();

  Context->stmt->res->Clear ();
  }

BOOL IsUnique(PKeyList FAR *k)
  {
  LPRECDESC d = Context->t->GetDescRef (FALSE);
  WORD anmbr = 0;
  for (int i = 0 ; i < int(d->AnzKeySegs) ; i++) {
    if (anmbr == k->k->KeyNmbr) break ;
    if ((d->k[i].flag & KA_SEGMENTED) == 0) anmbr ++ ;
    }
  return ((d->k[i].flag & KA_DUPLICATE) == 0);
  }

#define OWNTESTREJECT 20
int GetRejectCount (BinTree FAR *t,PKeyList FAR *k,LPBINTREE FAR &TestBaum,WORD BOp)
  {
  TestBaum = NULL;
  // 1. Suchen eines Testbaumes, der fuer internen Checkverwendet werden 
  // koennte 
  LPVARTBL h = LPVARTBL (k->k->Name + lstrlen(k->k->Name) + 1) ;
  BOOL segDone = TRUE ;
  BOOL breakNext;
  if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
    LPVBTRV x = &h->v[0];
    for ( int i = 0 ; (x != NULL) ; x = x->Next(h->gSize,h) , i++) {
      // Diesen Teil in den Testbaum aufnehmen
      if (segDone) {
        BinTree FAR *seg = t->FindSegToTest(x,BOp,&breakNext);
        if (seg != NULL) {
          if (TestBaum != NULL) {
            Context->PushPointer (TestBaum);
            Context->PushPointer (new BinTree (seg));
            Context->PushPointer (new BinTree (Context->PopPointer(),Context->PopPointer(),BOP_AND));
            }
          else
            Context->PushPointer (new BinTree (seg));
          TestBaum = Context->PopPointer();
          if (breakNext) segDone = FALSE ;
          }
        else
          segDone = FALSE ;
        }
      }
    }

  // 2. Ueberpruefen, ob alle Verknuepfungen mit und realisiert sind
  if (!t->IsAllAnd ())  {
    if (TestBaum == NULL) return 0x7FFF ;
    else                  return OWNTESTREJECT ;
    }

  // 2. Alle Segmente bis AnzSegs - 1 duerfen nur mit equal in der bedingung stehen
  h = LPVARTBL (k->k->Name + lstrlen(k->k->Name) + 1) ;
  if (h->gSize > (sizeof(*h) - sizeof(h->v[0]))) {
    LPVBTRV x = &h->v[0];
    for ( int i = 0 ; ((x != NULL) && (i < k->AnzSegsDone - 1)) ; x = x->Next(h->gSize,h) , i++) {
      if (!t->IsAllEqual (x)) {
        if (TestBaum == NULL) return 0x7FFF ;
        else                  return OWNTESTREJECT ;
        }
      }
    }

  // 3. alle Bedingungen ueberpruefen, ob sie in den Segmenten vorkommen
  if (!t->IsAllUsed (k)) {
    if (TestBaum == NULL) return 0x7FFF ;
    else                  return OWNTESTREJECT ;
    }

  // Der Testbaum wird nicht benoetigt, da Btrieve die Syntax selber vollstaendig 
  // ueberpruefen kann
  delete TestBaum ;
  TestBaum = NULL ;

  return 1;
  }

static BOOL _doSubLog;
BOOL DoLog(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL doLog;
  static BOOL ScrollLockOnly;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("DataBase","DoLog", "no", buf, sizeof(buf),GetIniName());
    doLog = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","ScrollLockOnly", "no", buf, sizeof(buf),GetIniName());
    ScrollLockOnly = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","SubQueryLog", "no", buf, sizeof(buf),GetIniName());
    _doSubLog = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog;
  }

BOOL doSubLog ()
  {
  DoLog();
  return _doSubLog;
  }

// static char outString [128];
static LPSTR outString;
static DWORD startT ;
LPSTR CallTypeName (WORD Type)
  {
  switch (Type) {
    case DBCALLTYPE_EXTENDED         : return "EXTENDED" ;
    case DBCALLTYPE_STANDARDGET      : return "STANDARDGET" ;
    case DBCALLTYPE_GETLIST          : return "GETLIST" ;
    case DBCALLTYPE_STANDARDUPDATE   : return "STANDARDUPDATE" ;
    case DBCALLTYPE_STANDARDDELETE   : return "STANDARDDELETE" ;
    case DBCALLTYPE_STANDARDINSERT   : return "STANDARDINSERT" ;
    case DBCALLTYPE_EXECUTE          : return "EXECUTE" ;
    case DBCALLTYPE_EXECUTESINGLE    : return "EXECUTESINGLE" ;
    case DBCALLTYPE_TEST             : return "TEST" ;
    }
  return "unknown" ;
  }
void LogCmd (LPSTR t1,LPSTR t2,LPSTR t3,LPSTR t4)
  {
  OFSTRUCT Of;
  static char *fname = "btrcmds.log";
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        retry++;
        }
      else {
        f = OpenFile (fname,&Of,OF_CREATE);
        _lclose(f);
        }
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    if (t1 != NULL)
      _lwrite (f,t1,lstrlen(t1));
    if (t2 != NULL)
      _lwrite (f,t2,lstrlen(t2));
    if (t3 != NULL)
      _lwrite (f,t3,lstrlen(t3));
    if (t4 != NULL)
      _lwrite (f,t4,lstrlen(t4));
    _lwrite (f,"\r\n",2);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }
static char ParStr[256];
LPSTR GetParStr (LPSTR r,LPVOID data,WORD mType)
  {
  if (data == NULL)
    lstrcpy (r,"NULL,");
  else if (mType == VAR_STR)
    wsprintf (r,"%.30s,",data);
  else if (mType == VAR_OBJ)
    lstrcpy (r,"BINARY,");
  else {
    FormatOutTxt (r,data,mType);
    lstrcat (r,",");
    }
  return r + lstrlen(r);
  }
void GetParStrs (LPDBREQUEST req)
  {
  *ParStr = '<' ;
  LPSTR h = GetParStr (ParStr + 1,req->Param[2],req->ParamType[2]);
  h = GetParStr (h,req->Param[3],req->ParamType[3]);
  h = GetParStr (h,req->Param[4],req->ParamType[4]);
  lstrcpy (h,"...>");
  }

void CatMulti (LPSTR s1,LPSTR s2 = NULL,LPSTR s3 = NULL,LPSTR s4 = NULL,LPSTR s5 = NULL,LPSTR s6 = NULL,LPSTR s7 = NULL,LPSTR s8 = NULL)
  {
  int l1 = (s1 != NULL) ? lstrlen(s1) : 0 ;
  int l2 = (s2 != NULL) ? lstrlen(s2) : 0 ;
  int l3 = (s3 != NULL) ? lstrlen(s3) : 0 ;
  int l4 = (s4 != NULL) ? lstrlen(s4) : 0 ;
  int l5 = (s5 != NULL) ? lstrlen(s5) : 0 ;
  int l6 = (s6 != NULL) ? lstrlen(s6) : 0 ;
  int l7 = (s7 != NULL) ? lstrlen(s7) : 0 ;
  int l8 = (s8 != NULL) ? lstrlen(s8) : 0 ;

  int l = l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 + 1;
  if (outString != NULL) FreeGlobMem (outString);
  outString = LPSTR (GetGlobMem (l));
  if (s1 != NULL) lstrcat (outString,s1);
  if (s2 != NULL) lstrcat (outString,s2);
  if (s3 != NULL) lstrcat (outString,s3);
  if (s4 != NULL) lstrcat (outString,s4);
  if (s5 != NULL) lstrcat (outString,s5);
  if (s6 != NULL) lstrcat (outString,s6);
  if (s7 != NULL) lstrcat (outString,s7);
  if (s8 != NULL) lstrcat (outString,s8);
  }

int DoDBGet (LPBTRVTABLE t,WORD Op,int AnzLines,LPDBREQUEST req,LPBTRSTATEMENT stmt,RecBuffer FAR *res)
  {
  BOOL doLog = DoLog();

  // Die Daten auf dem Stack ablegen und Zeiger umbiegen, damit Rekursion
  //      moeglich wird
  LocalData ActContext,*OldContext = Context;
  if ((doLog) && (doSubLog())) {
    if (Context != NULL) {
      // Merken des alten Strings
      if (outString != NULL) {
        Context->outCmd = LPSTR (GetGlobMem (lstrlen(outString) + 1));
        lstrcpy (Context->outCmd,outString);
        Context->startT = startT ;
        }
      }
    else
      // Einfuegen einer Leerzeile zur Kennzeichnung, dass es sich
      // um ein eigenstaendiges Programm handelt
      LogCmd (NULL,NULL,NULL,NULL);
    }
  Context = &ActContext;
  Context->t = t;
  Context->performUpdate = Context->performDelete = Context->performInsert = FALSE ;
  Context->updateRecord = NULL ;
  Context->VarToCheck = NULL ;
  Context->aList = NULL ;
  CacheEntry FAR *ce = NULL ;
  BOOL OwnCache = FALSE;
  if (req->GetTableID()) {
    Context->td = GetTableAdmin()->GetTableDef(req->GetTableID(),req->GetVersion());
    if ((doLog) && ((OldContext == NULL) || (doSubLog()))) {
      startT = GetTickCount();
      if (req->SelectionName != NULL)
        CatMulti ("<",CallTypeName(req->Type)," ON ",Context->td->GetName(),"> \"",req->SelectionName,"\"");
      else
        CatMulti ("<FURTHER ON ",Context->td->GetName(),">");
      }
    }
  else {
    if ((doLog) && ((OldContext == NULL) || (doSubLog()))) {
      startT = GetTickCount();
      if (req->SelectionName != NULL) {
        CatMulti ("<",CallTypeName(req->Type),"> \"",req->SelectionName,"\"");
        }
      }
    Context->td = NULL;
    }
  Context->stmt = stmt;
  int result = DBCALL_NODATA ;
  if ((Op != DBOP_GETNEXT) && (Op != DBOP_GETPREV)) {
    Context->rbufferCnt = Context->cCnt = Context->tCnt = Context->oCnt = 0;
    Context->SQLCmp = new SQLCompiler ();
    Context->ExpRead = TRUE ;
    if ((stmt->oldOrder != NULL) && (req->OrderStatement != NULL)) {
      if (lstrcmp (stmt->oldOrder,req->OrderStatement) != 0)
        stmt->ActKey = NULL ;
      FreeGlobMem (stmt->oldOrder);
      stmt->oldOrder = NULL;
      }
    if ((stmt->oldOrder == NULL) && (req->OrderStatement != NULL)) {
      stmt->oldOrder = LPSTR (GetGlobMem (lstrlen (req->OrderStatement) + 1));
      lstrcpy (stmt->oldOrder,req->OrderStatement);
      }
    BOOL IsFullDone = FALSE ;
    InitializeKeyList (t,stmt->ActKey);
    stmt->ClearFilter ();

    syntax_node *firstToGen = &whereexp,*secondToGen = NULL;
    LPSTR firstBuffer = ((req->SelectionName != NULL) && (*req->SelectionName)) ? 
                              req->SelectionName : NULL , secondBuffer = NULL ;
    WORD DBOp;

    switch (req->Type) {
      case DBCALLTYPE_STANDARDGET     :
        {
        DBOp = OPGET ;
        OwnCache = TRUE ;
        CacheOn ();
        if (!FromManipulate) {
          for ( CacheEntry FAR *h = CacheList ; ((h != NULL) && (ce == NULL)) ; h = h->Next)
            if (h->CheckEntry (req,stmt)) ce = h ;
          }
        }
        break ;
      case DBCALLTYPE_GETLIST         :
        DBOp = (Op == DBOP_GETFIRST) ? OPGETFIRST : OPGETLAST ;
        if (stmt->ActKey == NULL) {
          // Orderstatement einbauen
          secondBuffer = firstBuffer , secondToGen = firstToGen ;
          firstBuffer = ((req->OrderStatement != NULL) && (*req->OrderStatement)) ? 
                              req->OrderStatement : NULL , firstToGen = &orderexp ;
          }
        break ;
      case DBCALLTYPE_STANDARDUPDATE  : 
        DBOp = OPGET ;
        Context->performUpdate = TRUE ;
        InitializeUpdate ();
        break ;
      case DBCALLTYPE_STANDARDINSERT  : 
        firstToGen  = NULL ;
        firstBuffer = NULL ;
        Context->performInsert = TRUE ;
        if (DoInsert (FALSE)) result = DBCALL_SUCCESS ;
        else                  result = DBCALL_NODATA ;
        break ;
      case DBCALLTYPE_EXECUTE         : 
        if (stmt->RecsToGet == 1) req->Type = DBCALLTYPE_STANDARDGET     , DBOp = OPGET      , Op = DBOP_GET      ;
        else                      req->Type = DBCALLTYPE_GETLIST         , DBOp = OPGETFIRST , Op = DBOP_GETFIRST ;
        firstToGen = &fullstatement ;
        IsFullDone = TRUE ;
        break ;
      case DBCALLTYPE_STANDARDDELETE :
        DBOp = OPGETFIRST ;
        Op = DBOP_GETFIRST ;
        req->Type = DBCALLTYPE_GETLIST ;
        Context->performDelete = TRUE ;
        stmt->RecsToGet = WORD(-1);
        InitializeUpdate ();
        break ;
      default :
        WIN_ASSERT (FALSE);
      }
    if (ce == NULL) {
      Context->actDBOp = &DBOp;
      Context->ActSFnc = 0;
      if (firstBuffer != NULL) {
        Context->SQLCmp->DoParse (firstBuffer,firstToGen,NULL);
        Context->SQLCmp->DeinstallBuffer ();
        }
      if (secondBuffer != NULL) {
        Context->SQLCmp->DoParse (secondBuffer,secondToGen,NULL);
        Context->SQLCmp->DeinstallBuffer ();
        }
      // Die Aggregatfunktionen noch genauer untersuchen
      for (AggregatList FAR *h = Context->aList ; h != NULL ; h = h->Next) {
        if ((h->ActSFnc == SQLKW_MIN) || (h->ActSFnc == SQLKW_MAX)) {
          BOOL connDone ;
          if (Context->rbufferCnt == 1) // Zum aktuellen Aktuellen Baum noch was Dazutun
            Context->PushConnType (BOP_AND) , connDone = TRUE ;
          else
            connDone = FALSE ;
          if ((Context->t != NULL) && ((Context->VarToCheck = Context->t->GetVar (h->Str,FALSE)) != NULL)) {
            FNCArg (h->ActSFnc);
            OnExpRes ();
            if (connDone)
              OnEndOperator ();
            }
          else {
            if (connDone) 
              Context->PopPointer ();
            }
          }
        }
      BinTree FAR *rtree = Context->PopPointer();
      PKeyList FAR *k;
      BOOL IsValid = TRUE ;
      if (rtree != NULL) {
        rtree->RemoveConstantSubnodes ();
        if (rtree->IsConst()) {
          if (!rtree->IsValid()) {
            IsValid = FALSE ;
            }
          delete rtree ;
          rtree = NULL ;
          }
        }
      if (rtree != NULL) {
        if (!rtree->TestBtrieveSyntax (0xFF)) Fehler (NotBtrieveCompatible);
        }
      if ((IsValid) && (!Context->performInsert)) {
        k = GetBestKey (rtree,DBOp);
        if ((rtree != NULL) && (k != NULL)) {
          BinTree FAR *TestBaum = NULL;
          stmt->RejectCount = GetRejectCount (rtree,k,TestBaum,DBOp);
          stmt->RejectCountSet = TRUE ;
          WIN_ASSERT (stmt->Testfilter == NULL) ;
          if (TestBaum != NULL) {
            WORD offs ;
            stmt->Testfilter = TestBaum->CreateFilter (stmt->Testfilter,offs);
            *(LPSTR (stmt->Testfilter) + offs) = BOP_END ;
            delete TestBaum;    // Zum testen reicht der Testfilter
            }
          }
        else
          stmt->RejectCountSet = FALSE ;
        }
      else
        k = NULL;
      if (k != NULL) {
        stmt->ActKey = k->k ;
        if (rtree != NULL) {
          WORD offs ;
          stmt->filter = rtree->CreateFilter (stmt->filter,offs);
          *(LPSTR (stmt->filter) + offs) = BOP_END ;
          }
        if (InJoin && (!RestorePos) &&
            (Context->stmt->File == ParentFile)) {
          unsigned bs = sizeof(DWORD);
          WORD myopStatus = 
            BTRCALL (B_GETPOS,Context->stmt->File->pb,LPSTR(&SavedPos),&bs,
                      NULL,0,(char) Context->stmt->KeyNmbr
                    );
          TestST (myopStatus,Context->stmt->File->Path);
          RestorePos = TRUE;
          }
        LPSTR buffer = stmt->File->btrBuffer;
        stmt->bufferSize = stmt->GetFirstBufferSize();
        BOOL doRepeat = TRUE ;
        for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
          stmt->opStatus = 
            BTRCALL (k->B_Command,stmt->File->pb,buffer,&stmt->bufferSize,
                      LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                      (char) k->k->KeyNmbr
                  );
          if (stmt->opStatus == 22) {
            // Eventuell korrigieren
            if ((req->TableDef[0] != NULL) && (req->TableDef[0]->HoldBlobs()))
              stmt->opStatus = 0 ;
            }
          doRepeat = (stmt->opStatus == 84) ;
          if (doRepeat)
            doWait (count);
          }

        if (IsReadCritical (Context->stmt->opStatus))
          TestST (Context->stmt->opStatus,Context->stmt->File->Path);

        switch (req->Type) {
          case DBCALLTYPE_STANDARDGET :
            if ((stmt->opStatus == 0) && (TestFilter (stmt))) {
              if (DoCache)
                new CacheEntry (stmt->File->btrBuffer,stmt->bufferSize,stmt->File->Path,stmt->req);
              stmt->RecsToGet = 1 ;
              OnStore (ADDLINEPOS_END,stmt,!IsFullDone) ;
              result = (stmt->RecsToGet == 0) ? DBCALL_SUCCESS : DBCALL_ENDOFFILE ;
              }
            else {
              // Huelft nix, es muss weitergesucht werden
              if ((stmt->opStatus == 0) && ((k->B_Command != B_GETEQ) || 
                    (!IsUnique(k)))) {
                if (TestFilter (Context->stmt->Testfilter,Context->stmt))
                  result = GetFurtherRecs (buffer,Op,k,IsFullDone,result);
                }
              }
            break ;
          case DBCALLTYPE_GETLIST :
            CacheOn ();
            if ((stmt->opStatus == 0) && (TestFilter (stmt))) {
              if (!Context->performDelete) {
                BOOL oldInJoin = InJoin;
                if (!oldInJoin) {
                  InJoin = TRUE;
                  ParentFile = Context->stmt->File;
                  RestorePos = FALSE;
                  }
                OnStore (ADDLINEPOS_END,stmt,!IsFullDone) ;
                if (!oldInJoin) {
                  InJoin = FALSE;
                  if (RestorePos) {
                    // Join auf selbe Tabelle -> Kontext muss wiederhergestellt werden
                    Context->stmt->bufferSize = BUFFER_SIZE;
                    *(LPDWORD)buffer = SavedPos;
                    WORD myopStatus = 
                      BTRCALL (B_GETDIRECT,Context->stmt->File->pb,buffer,&Context->stmt->bufferSize,
                                LPSTR(k->KeyBuffer),(unsigned char) GetBlockSize(k->KeyBuffer),
                                (char) k->k->KeyNmbr
                              );
                    TestST (myopStatus,Context->stmt->File->Path);
                    }
                  }
                }
              if ((Context->performUpdate) || (Context->performDelete)) {
                OnDBOp (B_GETPOS,0,stmt);
                Context->PushPos ();
                }
              result = DBCALL_SUCCESS ;
              }

            if (stmt->opStatus == 0) {
              BOOL reread = FALSE ;
              if (stmt->RecsToGet != 0) {
                if ((k->B_Command != B_GETEQ) || (!IsUnique(k)))
                  result = GetFurtherRecs (buffer,Op,k,IsFullDone,result) , reread = TRUE ;
                else
                  result = DBCALL_ENDOFFILE ;
                }

              if (Context->performUpdate)
                UpdateRecs (reread);
              if (Context->performDelete)
                DelRecs (reread);

              // Filter fuer ev. spaeteren Update
              stmt->StoreOldFilter();
              }
            CacheOff ();
            break ;
          case DBCALLTYPE_STANDARDUPDATE :
            if ((stmt->opStatus != 0) || (!TestFilter (stmt))) {
              // Hurans Glump!, weiterg'macht muass wera.. '
              if ((stmt->opStatus == 0) && ((k->B_Command != B_GETEQ) || 
                    (!IsUnique(k)))) {
                result = GetFurtherRecs (buffer,Op,k,IsFullDone,result,FALSE);
                if (result == DBCALL_SUCCESS) {
                  Context->stmt->recPosition = Context->UpdatePos.Pos[0];
                  OnUseKey (k->k->KeyNmbr,Context->stmt);
                  OnDBOp (B_GETDIRECT,0,Context->stmt);
                  TestST (Context->stmt->opStatus,Context->stmt->File->Path);
                  }
                else
                  stmt->opStatus = REQNOTFOUND ;
                }
              else
                if (IsCritical (stmt->opStatus))
                  TestST (Context->stmt->opStatus,Context->stmt->File->Path);
              }
          
            if ((stmt->opStatus == 0) && (TestFilter (stmt))) {
              // Den erhaltenen Datensatz updaten
              BOOL transactionDone;
              if ((!IsInTransaction ()) && (!InAlter()))
                DoBeginTransaction (FALSE) , transactionDone = TRUE ;
              else
                transactionDone = FALSE ;
              OnUseKey (k->k->KeyNmbr,Context->stmt);
              LPDBRECORD ract = stmt->res->First()->rec[0];
              WORD resOp = OnSetRecord (NULL,Context->stmt,SRMODE_DOBOTH,TRUE);
              BOOL doRepeat = TRUE ;
              if (resOp == B_UPDATECHUNK) {
                UpdateAllChunks (Context->stmt);
                stmt->ClearChunkBuffers();
                }
              else {
                for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
                  OnDBOp (resOp,0,Context->stmt);
                  doRepeat = (stmt->opStatus == 84) ;
                  if (doRepeat)
                    doWait (count);
                  }
                if (IsCritical (Context->stmt->opStatus))
                  TestST (Context->stmt->opStatus,Context->stmt->File->Path);
                }
              if (stmt->doSkipChunk) {
                stmt->SkipChunk();
                }
              if (IsCritical (Context->stmt->opStatus))
                TestST (Context->stmt->opStatus,Context->stmt->File->Path);
              if (Context->stmt->opStatus == 0) {
                if (transactionDone)
                  DoEndTransaction () , transactionDone = FALSE ;
                result = DBCALL_SUCCESS ;
                MyManipulate (ract,UPDATEMODE_UPDATE);
                }
              else {
                if (transactionDone)
                  DoAbortTransaction () , transactionDone = FALSE ;
                result = DBCALL_NODATA ;
                }
              }
            break ;
          }
        }
      if (rtree != NULL)
        delete rtree ;
      }
    else {
      lmemcpy (stmt->File->btrBuffer,ce->rBuffer,ce->bufferSize);
      stmt->bufferSize = ce->bufferSize;
      OnStore (ADDLINEPOS_END,stmt,!IsFullDone) , result = DBCALL_SUCCESS ;
      }
    delete Context->SQLCmp;
    Context->RemoveAggregatList();
    WIN_ASSERT (Context->rbufferCnt == 0) ;
    RemoveKeyList ();
    }
  else {  // GetNextExtendend weitermachen...
    CacheOn();
    BOOL doBlobs = ((req->TableDef[0] != NULL) && (req->TableDef[0]->HoldBlobs())) ;
    InitializeKeyList (Context->t);
    PKeyList FAR *k = NULL ;
    if (stmt->ActKey != NULL) {
      OnUseKey (0,stmt);
      OnSetPrimKey (NULL,stmt);
      OnDBOp (B_GETEQ,0,stmt);
      k = FindKey (stmt->ActKey->KeyNmbr);
      if ((stmt->opStatus == 22) && (doBlobs))
        stmt->opStatus = 0 ;
      TestST (stmt->opStatus,stmt->File->Path);
      if (stmt->ActKey->KeyNmbr != 0) {
        OnDBOp (B_GETPOS,0,stmt);
        OnUseKey (stmt->ActKey->KeyNmbr,stmt);
        OnDBOp (B_GETDIRECT,0,stmt);
        if ((stmt->opStatus == 22) && (doBlobs))
          stmt->opStatus = 0 ;
        }
      stmt->SetOldFilter ();
      result = GetFurtherRecs (stmt->File->btrBuffer,Op,k,FALSE,result,TRUE);
      }
    RemoveKeyList ();
    CacheOff ();
    }
  if (Context->td != NULL)
    GetTableAdmin()->FreeTable(Context->td->GetTableID(),Context->td->GetVersion());
  Context = OldContext;
  if (OwnCache) CacheOff ();
  if (doLog) {
    if ((Context == NULL) || (doSubLog())) {
      LPSTR Prefix ;
      if (Context != NULL)
        Prefix = "  S: " ;
      else
        Prefix = "" ;
      DWORD endt = GetTickCount () ;
      char timestr[32];
      wsprintf (timestr,"[%ld - %ld (= %ld)]",startT,endt,endt - startT);
      GetParStrs (req);

      LogCmd (Prefix,timestr,outString,ParStr);

      if (Context != NULL) {
        CatMulti (Context->outCmd);
        FreeGlobMem (Context->outCmd);
        startT = Context->startT ;
        }
      }
    }

  return result;
  }

DLLExport int _export WINAPI GetDBLastError ()
  {
  return lastError ;
  }

static DWORD LastEndT;
DLLExport void _export WINAPI MakeTimeStamp (LPSTR Msg)
  {
  DWORD endt = GetTickCount () ;
  if (DoLog()) {
    char timestr[32];
    wsprintf (timestr,"[%ld - %ld (= %ld)]",LastEndT,endt,endt - LastEndT);

    LogCmd ("",timestr,Msg,"");
    }
  LastEndT = endt;
  }

