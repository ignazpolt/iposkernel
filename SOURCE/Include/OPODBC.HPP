//
// $Header:   P:/marille/clinicum/include/rev/opodbc.hpv   1.9   09 Sep 1999 22:18:16   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/opodbc.hpv  $
// 
//    Rev 1.9   09 Sep 1999 22:18:16   Hannes
// SQL Syntax auch in ODBC
//
/*------< Klasse database zur Herstellung der Verbindung >--------*/
struct TableData {
  BOOL IsTested;
  };
struct ColData {
  char TypeName[32];
  };
class FAR PartString {
 public :
  int len;
  LPSTR str;
  PartString (LPSTR h,int size)
    {
    str = h ;
    len = size;
    }
  };
class FAR odbcstmt;
class FAR LongString {
 private :
  GLOBALHANDLE hGmem;
  int Size;
  int SizeAlloced;
  LPSTR base;
  int NextSize (int s)
    {
    return ((s / 4096) + 1) * 4096 ;
    }
  void Enlarge (int s)
    {
    if (NextSize (s) != SizeAlloced) {
      SizeAlloced = NextSize(s) ;
      if (hGmem != NULL)
        hGmem = GlobalReAlloc (hGmem,SizeAlloced,GMEM_MOVEABLE);
      else
        hGmem = GlobalAlloc (GMEM_MOVEABLE,SizeAlloced);
      base = LPSTR(GlobalLock (hGmem));
      }
    }
 public :
  LongString ()
    {
    Size = 0;
    SizeAlloced = 0;
    hGmem = 0;
    base = NULL ;
    }
  void Clear ()
    {
    if (hGmem != NULL) GlobalFree (hGmem);
    Size = 0;
    SizeAlloced = 0;
    hGmem = 0;
    base = NULL ;
    }
  ~LongString ()
    {
    if (hGmem != NULL) GlobalFree (hGmem);
    }
  LongString &operator + (LPSTR str)
    {
    if (str == NULL) return *this ;
    int nsize = lstrlen(str);
    Enlarge (Size + nsize + 1);
    lstrcpy (base + Size,str);
    Size += nsize;
    base[Size] = '\0';
    return *this;
    }
  LongString &operator + (PartString FAR &p)
    {
    if (p.len == 0) return *this ;
    int nsize = p.len;
    Enlarge (Size + nsize + 1);
    lmemcpy (base + Size,p.str,p.len);
    Size += nsize;
    base[Size] = '\0';
    return *this;
    }
  LongString &operator + (int i)
    {
    char istr[32];
    wsprintf (istr,"%d",i);
    return *this + istr;
    }
  UCHAR FAR *Ptr()
    {
    return (UCHAR FAR *) base;
    }
  LPSTR SkipSpace (LPSTR h,LPSTR FAR &lastStart);
  LPSTR AnalyseSeq (LPSTR source,int FAR *ParNums,int FAR *AnzPars,BOOL translateNull,LPTABLEDEF ti = NULL,LPDBREQUEST req = NULL,BOOL FAR *IdentityInsert = NULL,LPSTR IdentityInsertTable = NULL,odbcstmt FAR *stmt = NULL);
  LPSTR AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,BOOL FAR *UseOuter,int FAR *ParNums,int FAR *AnzPars);
  };

struct MBlockHeader {
  WORD AnzVars;
  WORD BlockSize;
  };
struct MBlockVarHeader {
  WORD VarID;
  WORD VarSize;
  };

// Konstanten fuer database.DatabaseType
#define DT_SYBASEANYWHERE    0
#define DT_MSSQLSERVER       1
#define DT_ACCESS            2

class FAR database {
public :
  HDBC hdbc ;
  HENV henv ;
private :
  GLOBALHANDLE hGVarBuffer;
  GLOBALHANDLE hGBlockBuffer;
  BOOL TableFetched ;

  void FetchTableNames (HSTMT hstmt);
  void FetchColNames (HSTMT hstmt,hash *ColHash);
  BOOL TestTableDef (LPTABLEDEF td);
public :     
  short DatabaseType;
  hash *TableHash;
  hash *AliasNames;
  LPSTR VarBuffer;
  LPSTR BlockBuffer;
  SDWORD BlockSize;
  BOOL BlockValid;
  LPVOID FindData (WORD VarID,SDWORD FAR *Size)
    {
    MBlockHeader FAR *hd = (MBlockHeader FAR *) BlockBuffer ;
    MBlockVarHeader FAR *vhd = (MBlockVarHeader FAR *) (hd + 1) ;
    for (WORD i = 0 ; i < hd->AnzVars ; i++) {
      if (vhd->VarID == VarID) {
        *Size = int (vhd->VarSize) ;
        return (vhd + 1) ;
        }
      vhd = (MBlockVarHeader FAR *) (LPSTR (vhd + 1) + vhd->VarSize);
      }
    return NULL ;
    }
  LPSTR GetAliasName (LPSTR Name)
    {
    char buffer[256];
    #ifdef DEBUG
    DBWIN_ASSERT (strlen(Name) < 256);
    #endif
    lstrcpy (buffer,Name);
    AnsiUpper (buffer);
    LPSTR a = LPSTR (AliasNames->GetData(buffer));
    return (a != NULL) ? a : Name ;
    }
  PartString FAR &GetAliasName (PartString FAR &p)
    {
    if (p.len >= 64) return p;
    char buffer[64];
    lmemcpy (buffer,p.str,p.len);
    buffer[p.len] = '\0' ;
    AnsiUpper (buffer);
    LPSTR a = LPSTR (AliasNames->GetData(buffer));
    if (a != NULL) {
      p.len = lstrlen(a);
      p.str = a ;
      }
    return p ;
    }
  int fehlertext (HSTMT hstmt,int retCode,LPSTR errorMessage,BOOL doIgnore) ;
  int fehler (HSTMT hstmt,int retCode) ;
  void LogForeign (LPSTR cmd,HSTMT hstmt,RETCODE retCode) ;
  BOOL TestRetCode (HSTMT hstmt,RETCODE retCode)
    {
    if ((retCode == SQL_ERROR) || (retCode == SQL_SUCCESS_WITH_INFO))
      retCode = fehler (hstmt,retCode);
    if ((retCode == SQL_SUCCESS) || (retCode == SQL_SUCCESS_WITH_INFO))
      return TRUE;
    else
      return FALSE;
    }
  HSTMT GetStatementHandle ()
    {
    HSTMT hstmt;
    int retCode = SQLAllocStmt (hdbc, &hstmt) ;
    if (retCode != SQL_SUCCESS ) retCode = fehler (SQL_NULL_HSTMT,retCode) ;
    return hstmt;
    }
  void FreeStatementHandle (HSTMT hstmt)
    {
    SQLFreeStmt (hstmt, SQL_DROP);
    }
  BOOL CreateAllIndex (LPTABLEDEF td);
  BOOL CreateTable (LPTABLEDEF td,BOOL withIndex);
  BOOL CreateForeignKeys (LPTABLEDEF td);
  BOOL TestTable (LPTABLEDEF td);
  LPSTR GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0);
  LPSTR BlockVarName ();
  LPSTR BlockTypeName ();

  void StartTableTest ();
  database (UCHAR FAR * _server,UCHAR FAR * _user,UCHAR FAR *_password);
  ~database () ;
  void Reset () ;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  friend DLLExport void _export WINAPI DoBeginTransaction (BOOL doLarge);
  friend DLLExport void _export WINAPI DoEndTransaction ();
  friend DLLExport void _export WINAPI DoAbortTransaction ();
  friend DLLExport LPVOID _export WINAPI GetDBPointer ();
  };

class FAR ConvertBuffer {
 public :
  LPVOID ptr[64];
  int AnzPointers;
  ConvertBuffer ()
    {
    AnzPointers = 0 ;
    }
  ~ConvertBuffer ()
    {
    for (int i = 0 ; i < AnzPointers ; i++)
      if (ptr[i] != NULL) FreeGlobMem (ptr[i]);
    }
  LPVOID GetBuffer (int size)
    {
    ptr[AnzPointers] = GetGlobMem (size);
    return ptr[AnzPointers++];
    }
  };

#ifdef OPODC_MAIN
database FAR *dbase;
#else
extern database FAR *dbase;
#endif

extern BOOL InAlter();
extern SLONG GetTypePrecision (WORD mType,LPVOID parData,WORD VarSize = 0xFFFF);
extern LPVOID ConvertTo(WORD mType,LPVOID parData,ConvertBuffer FAR *cb,SDWORD FAR *length);
extern SWORD GetCType(WORD mType);
extern SWORD GetSQLType(WORD mType,SLONG VarSize = -1);
typedef odbcstmt FAR *LPODBCSTMT;
extern BOOL CheckFile (LPODBCSTMT stmt,BOOL first);

extern WORD AnzOpenStatements;
struct BndList {
  BndList FAR *Next ;
  DWORD VarLen;
  WORD Num,Type ;

  // Daten fuer das Binden von Rueckgabevariablen
  LPSTR retBuffer;
  SDWORD retStatus;
  };
class FAR odbcstmt {
 public :
  int  retVal;
  WORD Op;
  int  RecsToGet;
  RecBuffer FAR *res;
  LPDBREQUEST req;
  HSTMT hstmt;
  LPSTR oldStatement ;
  BOOL  prepareDone;
  LPVOID oldParam[CB_PARAM-2];
  LPVOID BlockedData;
  BOOL ThereAreBlockedData;
  BndList FAR *LastDsc,FAR *TopDsc;

  void PushToDscList (int ParNum,LPDBREQUEST req);
  void StoreBndParam (BOOL correct=TRUE);

  void GetOldStatementCopy ()
    {
    oldStatement = LPSTR (GetGlobMem (lstrlen(req->SelectionName)+1));
    lstrcpy (oldStatement,req->SelectionName);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (req->Param[i+2] != NULL) {
        oldParam[i] = GetGlobMem (GetBlockSize (req->Param[i+2]));
        lmemcpy (oldParam[i],req->Param[i+2],GetBlockSize(req->Param[i+2]));
        }
      else {
        if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
        oldParam[i] = NULL ;
        }
      }
    }

  odbcstmt ()
    {
    AnzOpenStatements ++ ;
    }
  ~odbcstmt ()
    {
    AnzOpenStatements -- ;
    if (hstmt != NULL)
      dbase->FreeStatementHandle (hstmt);
    if (oldStatement != NULL)
      FreeGlobMem (oldStatement);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
      }
    if (BlockedData != NULL) FreeGlobMem (BlockedData);

    for ( ; TopDsc != NULL ; ) {
      BndList FAR *Next = TopDsc->Next;
      if (TopDsc->retBuffer) FreeGlobMem (TopDsc->retBuffer);
      FreeGlobMem (TopDsc);
      TopDsc = Next;
      }
    LastDsc = NULL;
    }
  BOOL IsPrepareToDo ()
    {
    return ((!prepareDone) || (lstrcmp (oldStatement,req->SelectionName) != 0));
    }
  BOOL IsToExecute()
    {
    return TRUE ;
#ifdef UEBERLEGT
    if (IsPrepareToDo()) return TRUE ;
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if ((oldParam[i] == NULL) && (req->Param[i+2] == NULL)) continue ;
      if ((oldParam[i] != NULL) && (req->Param[i+2] != NULL) &&
            (GetBlockSize(oldParam[i]) == GetBlockSize(req->Param[i+2])) &&
            (lmemcmp (oldParam[i],req->Param[i+2],GetBlockSize(req->Param[i+2])))) continue ;
      return TRUE ;
      }
    return FALSE ;
#endif
    }
  void ClearStmt ()
    {
    dbase->FreeStatementHandle (hstmt);
    hstmt = NULL;
    }
  void GetStatementHandle ()
    {
    hstmt = dbase->GetStatementHandle ();
    }
  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }

  int StandardDelete ();
  int StandardGet ();
  void SelectStatement (LPTABLEDEF td,LongString FAR &s,int FAR *ParNums,int FAR *AnzPars,BOOL forList = FALSE);
  void WhereStatement (LongString FAR &s,int FAR *ParNums,int FAR *AnzPars,LPTABLEDEF td);
  void OrderStatement (LongString FAR &s,LPTABLEDEF td);
  LPVOID ConvertToMData (LPVARDEF v,LPVOID data,SDWORD FAR *Size,BOOL FAR *doFree);
  LPVOID ConvertToMData_T (WORD mType,LPVOID data,SDWORD FAR *Size,BOOL FAR *doFree);
  LPVOID GetColData (LPVARDEF v,UWORD col,SDWORD FAR *Size,BOOL FAR *doFree,BOOL FAR *blockDone);
  LPDBRECORD StoreRow (LPTABLEDEF ti);
  WORD GetColSize (LPVARDEF v);
  BOOL BindColData (LPTABLEDEF ti);
  void StoreExtendedRow (LPTABLEDEF ti,WORD pos);
  int StandardList (BOOL first,short DatabaseType);
  void PushToBlocked (LPVOID Data,WORD VarID);
  BOOL odbcstmt::EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars,int FAR *AnzVars);
  BOOL EnlargeInsert (LPVARDEF vd,int VarID,LongString FAR &s,LongString FAR &v,ConvertBuffer FAR *b,int FAR *AnzPars,int FAR *AnzVars,BOOL doSetNull);
  BOOL EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first);
  BOOL EnlargeUpdate (LPVARDEF vd,int VarID,LongString FAR &s,ConvertBuffer FAR *b,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0);
  LPDBRECORD GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize);
  int StandardInsert (short DatabaseType);
#ifdef WITHAUTOINCLOCK
  BOOL LockForInsert (LPSTR TableName);
  void ClearLock (LPSTR TableName);
#endif
  int StandardUpdate ();
  int StandardExcute ();
  };


