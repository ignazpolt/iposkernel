///////////////////////////////////////////////////
//  Datenstrukturen fuer den Zugriffskontext
///////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/opbtrv.hpv   1.21   06 Mar 1998 17:26:30   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/opbtrv.hpv  $
// 
//    Rev 1.21   06 Mar 1998 17:26:30   Hannes
// Prototyp Transaktionshandling
// 
//    Rev 1.20   12 Jan 1998 18:22:46   Hannes
// 
//    Rev 1.19   14 Oct 1997 18:43:20   Martin
// MAX_CHUNKS auf 64 gezetzt (das muesste wieder ein paar Monate reichen ...)
// 
//    Rev 1.18   03 Dec 1996 16:43:00   HANNES
// 
//    Rev 1.17   26 Nov 1996 08:01:14   HANNES
// 
//    Rev 1.16   17 Jun 1996 14:17:10   HANNES
// Einbau von BLOBS
// 
//    Rev 1.15   23 Mar 1996 23:11:42   MARTIN
// Testfilter ...
// 
//    Rev 1.14   02 Feb 1996 11:00:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.13   10 Nov 1995 12:23:20   MARTIN
// Korrekturen Hannes
// 
//    Rev 1.11   02 Nov 1995 19:12:56   martin
// 
//    Rev 1.10   25 Jul 1995 12:03:44   HANNES
// 
//    Rev 1.9   25 Jul 1995 10:40:30   HANNES
// Verbesserte Filterpruefung
// 
//    Rev 1.8   14 Jul 1995 16:55:24   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.7   14 Jun 1995 13:10:32   HANNES
// FreeTempararyTable auf jeden Fall aufgerufen
// 
//    Rev 1.6   08 May 1995 17:15:46   HANNES
// 
//    Rev 1.5   24 Feb 1995 11:14:54   HANNES
// 
//    Rev 1.4   16 Feb 1995 12:47:04   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.3   31 Oct 1994 10:38:56   hannes
// Continue
// 
//    Rev 1.2   17 Oct 1994 14:56:46   HANNES
// No change.
// 
//    Rev 1.1   05 Aug 1994 17:17:48   HANNES
// 
//    Rev 1.0   24 Jun 1994 17:01:26   HANNES
// Neuuebernahme clinicum
//

// Representation eines Files
//////////////////////////////////////////////
#define PATH_SIZE 128
class FAR bFile {
 public :
  BOOL FileStatDifferent;
  bFile (LPTABLEDEF def,LPSTR alternateName);
  ~bFile ();
  GLOBALHANDLE hGBuffer;
  LPSTR btrBuffer;
  BOOL isOpen;
  char Name[PATH_SIZE];
  char Path[PATH_SIZE];
  LPRECDESC rd;
  LPSTR ErrorName ()
    { return (*Path) ? Path : Name; }
  char pb[128];   // btrieve - Postionblock

  BOOL CompareStat (LPRECDESC d,unsigned buffersize);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  char AlternateSequence [256];
  BOOL AlternateDefined ;

  DWORD LastAccessTime;
  WORD  StmtCount;

  void IncrementUseCount() { StmtCount ++ ; }
  void DecrementUseCount() { StmtCount -- ; }
  void SetTimeStamp()      { LastAccessTime = GetTickCount() ; }
  };
typedef bFile FAR *LPBFILE;

#define LOCK_RETRY_COUNT 50

#pragma pack(1)
// Getnextextended - Buffer
struct RecordImage_header {
  WORD AnzRecords;
  };
struct RecordImage {
  WORD  rLength;
  DWORD btrPos;
  };
#pragma pack()

// Liste aller offenen Files
//////////////////////////////////////////////
struct FAR FileList {
  FileList FAR *Next;
  LPBFILE f;
  };
static FileList FAR *fl;

// Liste der Locks auf dem File
///////////////////////////////
struct LockListElem {
  LockListElem FAR *Next;
  PrimKey key;
  WORD TableID;
  };

// Zugriffskontext...
//////////////////////////////////
#define UPDATECHUNK_RANDOMDIRECT    0x80000000
#define UPDATECHUNK_RANDOMINDIRECT  0x80000001
#define UPDATECHUNK_SKIP            0x80000004
#define GETDIRECTCHUNK_INDIRECT     0x80000001
struct FAR ChunkDescriptor {
  DWORD SubFunction;
  DWORD NumChunks;
  };
#define MAXCHUNKLEN 0x7000
struct FAR ChunkStruct {
  DWORD ChunkOffset;
  DWORD ChunkLen;
  LPVOID ChunkBuffer;

  GLOBALHANDLE AllocateBuffer ()
    {
    GLOBALHANDLE hGmem = GlobalAlloc (GMEM_MOVEABLE,ChunkLen);
    ChunkBuffer = LPVOID (GlobalLock (hGmem));
    return hGmem ;
    }
  void SetBuffer (LPVOID ptr)
    {
    ChunkBuffer = ptr ;
    }
  };
#define B_UPDATECHUNK     53
#define B_GETDIRECTCHUNK  23
class FAR BtrStatement {
 public :
  // Anzahl offener Records
  WORD RecsToGet;
  // Operationswert beim Aufruf
  WORD Op;
  // Returnstatus einer Datenbankoperation
  int   opStatus;
  // Schluesselverwaltung
  WORD KeyNmbr;
  LPVOID KeyBuffer;
  // Und noch das File
  LPBFILE File;
  GLOBALHANDLE FAR *lpChunkHandles;

  // Locks
  LockListElem FAR *lele;

  // Resultat
  RecBuffer FAR *res;
  unsigned bufferSize;
  int retVal;
  DWORD recPosition;

  // Anfrage
  LPDBREQUEST req;
  DWORD SkipChunkFrom;
  BOOL doSkipChunk ;

  void CreateChunk (LPBTRVTABLE t,WORD mode);
  void AddChunk (LPBLOBDESC d);
  void SkipChunk();
  void AddChunk (LPVOID Data,DWORD Size);
  void ClearChunkBuffers();
  int GetFirstBufferSize()
    {
    LPBTRVTABLE t = LPBTRVTABLE(req->TableDef[0]->GetDLLDef());
    if (req->TableDef[0]->HoldBlobs())
      return t->GetDescRef()->RecordLength ;  // Zumindestens die Laenge des BLOBS
    else
      return BUFFER_SIZE ;
    }
  LPSTR ChunkBuffer (int Num)
    {
    ChunkStruct FAR *csi = (ChunkStruct FAR *) ((ChunkDescriptor FAR *) (File->btrBuffer) + 1) + Num ;
    return LPSTR(csi->ChunkBuffer) ;
    }
  LPBLOBDESC ReadBlob (DWORD Size,DWORD recPosition);
  LPBLOBDESC ReadBlob ();

  // Filter
  WORD LastOp;
  LPVOID filter,oldfilter,Testfilter,oldTestfilter;
  LPVOID PushToFilter(LPVOID old,LPVOID data,WORD size);
  void PushToFilter(LPVOID data,WORD size)
    { filter = PushToFilter (filter,data,size) ; }
  void IncAnzTerms(LPVOID filter);
  void IncAnzTerms()
    { IncAnzTerms (filter); }
  void ClearFilter() { 
    if (filter != NULL) FreeGlobMem (filter) , filter = NULL ; 
    if (Testfilter != NULL) FreeGlobMem (Testfilter) , Testfilter = NULL ; 
    }
  BOOL RejectCountSet;
  int  RejectCount;
  void SetOldFilter() 
    { 
    ClearFilter() ; 
    if (oldfilter != NULL) {
      filter = GetGlobMem (GetBlockSize(oldfilter));
      lmemcpy (filter,oldfilter,GetBlockSize(oldfilter)) ; 
      }
    if (oldTestfilter != NULL) {
      Testfilter = GetGlobMem (GetBlockSize(oldTestfilter));
      lmemcpy (Testfilter,oldTestfilter,GetBlockSize(oldTestfilter)) ; 
      }
    }
  // Joins
  BOOL JustInnerJoins;
  BOOL BtrStatement::SatisfyJoin (LPDBRECORD rec);
  void CallCascade (LPVOID key);

  // Hilfsmethoden
  //////////////////////
  LPSTR oldOrder;
  WORD TempTableID;
  LPKEYDEF ActKey;
  ~BtrStatement ()
    { 
    if (KeyBuffer != NULL) FreeGlobMem (KeyBuffer); 
    if (filter != NULL) FreeGlobMem (filter) ; 
    if (oldfilter != NULL) FreeGlobMem (oldfilter);
    if (oldTestfilter != NULL) FreeGlobMem (oldTestfilter);
    if (oldOrder != NULL) FreeGlobMem (oldOrder);
    if (Testfilter != NULL) FreeGlobMem (Testfilter);
    }
  void StoreOldFilter ()
    {
    if (oldfilter != NULL) FreeGlobMem (oldfilter);
    if (oldTestfilter != NULL) FreeGlobMem (oldTestfilter) ;
    if (filter != NULL) {
      oldfilter = GetGlobMem (GetBlockSize(filter));
      lmemcpy (oldfilter,filter,GetBlockSize(filter));
      }
    else
      oldfilter = NULL ;
    if (Testfilter != NULL) {
      oldTestfilter = GetGlobMem (GetBlockSize(Testfilter));
      lmemcpy (oldTestfilter,Testfilter,GetBlockSize(Testfilter));
      }
    else
      oldTestfilter = NULL ;
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef BtrStatement FAR *LPBTRSTATEMENT;

int DoDBGet (LPBTRVTABLE t,WORD Op,int AnzLines,LPDBREQUEST req,LPBTRSTATEMENT stmt,RecBuffer FAR *res);

// Stackoperationen
void OnStore (WORD pos,LPBTRSTATEMENT stmt,BOOL getPrimKey);
void Push (LPVOID data,WORD Size,BOOL ExternNull = FALSE);
LPVOID Pop(BOOL FAR *ExternNull = NULL);
WORD StackElemSize();
BOOL TestFilter (LPVOID filter,LPBTRSTATEMENT stmt);
BOOL TestFilter (LPBTRSTATEMENT stmt);
BOOL CompareData (LPBTRSTATEMENT stmt,WORD btrDataType,LPVOID d1,LPVOID d2,WORD VarLen,WORD cmpCode);
WORD SetFilter (LPBTRSTATEMENT stmt,LPVOID buffer,LPVOID filter);
#define USE_GETFULL           0
#define USE_GETPART           1
#define USE_GETNEXTEXTENDED   2
WORD SetFieldsToExtract (LPVOID buffer,WORD fOffs,LPDBREQUEST req,int TableNum,WORD AnzRecs);
WORD StoreMulti (WORD Pos,LPBTRSTATEMENT stmt,BOOL getPrimKey,LPVOID KeyBuffer = NULL,char KeyNmbr = 0);
void OnSetPrimKey (LPVOID params,LPBTRSTATEMENT stmt);
void TestST (int st,LPSTR FileName);
void OnDBOp (WORD Op,WORD ExtraCmd,LPBTRSTATEMENT stmt);
void OnUseKey (WORD Number,LPBTRSTATEMENT stmt) ;
void NextChar (LPBTRSTATEMENT stmt) ;
DLLExport int _export WINAPI DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
BOOL GetFile (LPBTRSTATEMENT stmt,BOOL first);
void OnSetRecord (LPVOID params,LPBTRSTATEMENT stmt);
#define SRMODE_IGNOREBLOBS  0
#define SRMODE_IGNOREFIXED  1
#define SRMODE_DOBOTH       2
WORD OnSetRecord (LPVOID params,LPBTRSTATEMENT stmt,WORD mode,BOOL doRemove);
BOOL IsInTransaction ();
DLLExport void _export WINAPI DoBeginTransaction (BOOL doLarge);
DLLExport void _export WINAPI DoEndTransaction ();
DLLExport void _export WINAPI DoAbortTransaction ();
void OnInitializeRecord (LPVOID params,LPBTRSTATEMENT stmt);

void UpdateAllChunks (LPBTRSTATEMENT stmt);
void doWait (int i);
BOOL IsCritical (WORD st);

void GetFileName (LPTABLEDEF td,LPSTR path,LPSTR AltName);
BOOL CloseFile (LPSTR Name);
BOOL InAlter ();
LPSTR GetCNVPath (LPTABLEDEF td);
void RestoreCNV ();
void DeleteCNV ();
int DBCall_Work (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
void DelDefinition (LPSTR TableName);
void CreateDefinition (LPTABLEDEF td);

