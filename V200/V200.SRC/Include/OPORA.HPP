//
//  Klassen fuer Arbeiten mit Oracle
//
//  $Header:   P:/marille/clinicum/include/rev/opora.hpv   1.17   17 Jan 2000 21:05:46   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/opora.hpv  $
// 
//    Rev 1.17   17 Jan 2000 21:05:46   Martin
// Einbau von UserOrb
// 
//    Rev 1.16   13 Sep 1999 23:37:34   Hannes
// DscList als Member von sybstmt
// 
//    Rev 1.15   05 Mar 1999 10:49:58   Martin
// closeDone richtig setzen
// 
//    Rev 1.14   11 Feb 1999 11:38:34   Martin
// Trigger vor dem Erzeugen loeschen
// 
//    Rev 1.13   08 Feb 1999 15:57:08   Martin
// closedone defaultmaessig auf TRUE setzen
// 
//    Rev 1.12   29 Jan 1999 10:45:04   Hannes
// Prototyp von GetVarString
// 
//    Rev 1.11   28 Jan 1999 12:20:46   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.10   09 Oct 1998 18:15:14   Martin
// Synonymerzeugung, Sequence Ueberpruefung"
// 
//    Rev 1.9   10 Aug 1998 18:05:04   Martin
// Prefix-Fehler bei Sequences
// 
//    Rev 1.8   04 Aug 1998 17:56:30   Hannes
// Timestamp
// 
//    Rev 1.7   13 May 1998 14:03:44   Martin
// Sybase raus
// 
//    Rev 1.6   06 Mar 1998 17:26:36   Hannes
// Prototyp Transaktionshandling
// 
//    Rev 1.5   21 Nov 1997 10:38:32   Hannes
// Verbesserung des For - STatements
// 
//    Rev 1.4   15 Apr 1997 13:01:42   Martin
// Fehlerhandling etwas verbessert
// 
//    Rev 1.3   17 Dec 1996 17:15:28   HANNES
// WIN32 Anpassungen
// 
//    Rev 1.2   17 Dec 1996 11:11:56   HANNES
// Stored Procedures
// 
//    Rev 1.1   05 Dec 1996 11:19:26   HANNES
// 
//    Rev 1.0   26 Nov 1996 08:04:02   HANNES
// Initial revision.
//

extern BOOL DoLog(void);

#ifdef OPORA_MAIN
WORD AnzOpenStatements;
#else
extern WORD AnzOpenStatements;
#endif
class FAR sybstmt;
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
class FAR LongString {
 private :
  GLOBALHANDLE hGmem;
  DWORD Size;
  DWORD SizeAlloced;
  LPSTR base;
  DWORD NextSize (DWORD s)
    {
    return ((s / 4096L) + 1L) * 4096L ;
    }
  void Enlarge (DWORD s)
    {
    if (NextSize (s) != SizeAlloced) {
      SizeAlloced = NextSize(s) ;
      if (hGmem != NULL)
        hGmem = GlobalReAlloc (hGmem,SizeAlloced,GMEM_MOVEABLE);
      else
        hGmem = GlobalAlloc (GMEM_MOVEABLE,SizeAlloced);
      base = LPSTR (GlobalLock (hGmem));
      }
    }
 public :
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  LongString ()
    {
    Size = 0L;
    SizeAlloced = 0L;
    hGmem = 0;
    base = NULL ;
    }
  void Clear ()
    {
    if (hGmem != NULL) GlobalFree (hGmem);
    Size = 0L;
    SizeAlloced = 0L;
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
    hmemcpy ((char huge *) base + Size,str,nsize);
    Size += nsize;
    ((char huge *) base)[Size] = '\0';
    return *this;
    }
  LongString &operator + (PartString FAR &p)
    {
    if (p.len == 0) return *this ;
    if (p.len < 0) {
      // Es muss wieder etwas zurueckgenommen werden
      Size += p.len ;
      ((char huge *) base)[Size] = '\0';
      return *this ;
      }
    int nsize = p.len;
    Enlarge (Size + nsize + 1);
    hmemcpy ((char huge *)base + Size,p.str,p.len);
    Size += nsize;
    base[Size] = '\0';
    return *this;
    }
  LongString &operator + (int i)
    {
    char istr[32];
    sprintf (istr,"%d",i);
    return *this + istr;
    }

  LongString &operator + (LONG i)
    {
    char istr[32];
    sprintf (istr,"%ld",i);
    return *this + istr;
    }

  LongString &operator + (WORD i)
    {
    char istr[32];
    sprintf (istr,"%u",i);
    return *this + istr;
    }

  LongString &operator + (DWORD i)
    {
    char istr[32];
    sprintf (istr,"%lu",i);
    return *this + istr;
    }

  LPSTR Ptr()
    {
    return base;
    }
  DWORD size()
    {
    return Size ;
    }
  LPSTR SkipSpace (LPSTR h,LPSTR FAR &lastStart);
  LPSTR AnalyseSeq (sybstmt FAR *stmt,LPSTR source,BOOL transalteNull,LPTABLEDEF ti = NULL,LPDBREQUEST req = NULL,BOOL useAlias = TRUE,BOOL useOld = FALSE,sybstmt FAR *s = NULL,BOOL whereFound = TRUE,int AnzJoinSegs = 0,LPSTR JoinName[] = NULL,int tnum = 0,BOOL UseOuter = FALSE);
  LPSTR AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,LPSTR FAR *JoinSel,BOOL FAR *UseOuter,BOOL useOld,sybstmt FAR *s,BOOL translateNull);
  LPSTR InsertDescending (LPSTR h);
  LPSTR InsertSyncCond (LPSTR sync,LPDBREQUEST req,LPSTR c,LPSTR ce,BOOL FAR &doAnd);
  };
extern LPSTR GetAliasName (LPSTR Name);
extern LPSTR GetSequenceName (LPTABLEDEF td);
extern void DoSynonym (LPSTR NewName,LPSTR OldName,LPSTR Rights);
extern void DropSynonym (LPSTR Synonym);
extern void UserOrb (LPSTR ObjName);

class FAR sybase {
  void FetchTableNames ();
  void AlterSession();
  BOOL TablesFetched;
  
public :     
  BOOL TestTableDef (LPTABLEDEF td);
  BOOL CreateTable (LPTABLEDEF td,BOOL withIndex = TRUE);

  /*---- Hash Tabellen fuer Tabellen, die bereits getestet wurden ----*/
  hash *TableHash;
  
  /*---- Sybase spezifische Daten ------*/
  Lda_Def       slda;             // local data area 
  ub1           shda[HDA_SIZE];   // host data area 
  Lda_Def       *lda;             // pointer to local data area, also called the CS_CONNECTION
  ub1           *hda;             // pointer to host data area  (hda[HDA_SIZE])

  /* --- Hilfsvariablen -----*/
  BOOL TestTable (LPTABLEDEF td);
  
  CS_RETCODE Init ();
  CS_RETCODE Connect (LPSTR username, LPSTR password,LPSTR appname);
  
  void StartTableTest ();
  sybase (LPSTR _user,LPSTR _password,LPSTR _appname,BOOL forUpdate);
  ~sybase () ;
  void Reset () ;
  
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  
  friend void _export FAR PASCAL DoBeginTransaction (BOOL large);
  friend void _export FAR PASCAL DoEndTransaction ();
  friend void _export FAR PASCAL DoAbortTransaction ();
  void Testsequence (LPTABLEDEF td);
  };

#ifdef OPORA_MAIN
sybase FAR *dbase;
#else
extern sybase FAR *dbase;
#endif

/*-------------------------------------------------
  Fifo mit Daten, die dynamisch gebunden werden
-------------------------------------------------*/
struct BndList {
  BndList FAR *Next ;
  LPVOID data;
  char prefix ;
  int Num;
  int Type ;
  int Size ;
  int parNr ;

  // Daten fuer das Binden von Rueckgabevariablen
  ub2 VarLen,VarRetCode;
  sb2 VarInd;

  // Daten fuer das Binden von IN/OUT Variablen
  ub2 FAR *alen;
  sb2 FAR *indp;
  };

struct BndMem {
  BndMem FAR *Next;
  LPVOID data;
  int parNr;
  sb2 ind;
  ub2 alen;
  };

class FAR sybstmt {
 public :
  int  retVal;
  WORD Op;
  int  RecsToGet;
  RecBuffer FAR *res;
  LPDBREQUEST req;
  LPSTR oldStatement ;
  BOOL  prepareDone;
  LPVOID oldParam[CB_PARAM-2];
  WORD oldParamType[CB_PARAM-2];
  int dbCols;
  int dbMaxRows;
  BOOL noResult;
  LPCLKEYDEF k0;
  LPDBRECORD old;
  BOOL doNext,doIt;

  BndList FAR *LastDsc,FAR *TopDsc;

  void PushToDscList (int ParNum,LPDBREQUEST req);
  void ResetDscList ();

  struct _COLINFO {
    VARLEN_TYPE     FAR *VarLen;
    LPVOID              VarData;
    CS_DATAFMT          VarFormat;
    VARRETCODE_TYPE FAR *VarRetCode; 
    VARIND_TYPE     FAR *VarInd;    
    } FAR *ColInfo ;
  int blobCol;

  // Virtuelle Funktionen zum Handling der verschiedenen 
  // des Datenbindung und Speicherung
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE);
  virtual int nRowsToGet (LPTABLEDEF ti)
    { return nRows (ti) ; }
  virtual int nCols (LPTABLEDEF ti);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);

  // Datenbindung
  LPVOID GetSybDataType (CS_DATAFMT FAR *fmt,WORD mType,int maxSize,int nRows);
  LPVOID GetSybDataType_f (ub2 *ml,ub2 *dt,WORD mType,int maxSize);
  BOOL BindColData (CS_COMMAND FAR *cmd, LPTABLEDEF ti); 
  
  // Ausfueheren eines Kommandos
  CS_COMMAND FAR  *cmd;
  CS_COMMAND       cmd_struct;  // structure containing the cmd
  CS_COMMAND       cmd_fetch_struct;
  BOOL closeDone;

  CS_RETCODE sybstmt::FetchMore (LPTABLEDEF ti);
  CS_RETCODE real_execute (LPSTR cmdbuf,LPTABLEDEF ti,CS_CONNECTION *conn,LPBLOBDESC bdsc,BOOL doCursorClose,LPSTR procName);
  CS_RETCODE execute (LPSTR cmdbuf,LPTABLEDEF ti,CS_CONNECTION *conn = NULL,LPBLOBDESC bdsc = NULL,BOOL doCursorClose = TRUE);

  LPVOID BlockedData;
  BOOL ThereAreBlockedData ;
  void PushToBlocked (LPVOID Data,WORD VarID);
  LPVOID FindData (LPVOID BlockData,WORD VarID,int FAR *Size);

  void GetOldStatementCopy ()
    {
    oldStatement = LPSTR (GetGlobMem (lstrlen(req->SelectionName)+1));
    lstrcpy (oldStatement,req->SelectionName);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (req->Param[i+2] != NULL) {
        oldParam[i] = GetGlobMem (GetBlockSize (req->Param[i+2]));
        lmemcpy (oldParam[i],req->Param[i+2],GetBlockSize(req->Param[i+2]));
        oldParamType[i] = req->ParamType[i+2];
        }
      else {
        if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
        oldParam[i] = NULL ;
        }
      }
    }

  sybstmt ()
    {
    cmd = (CS_COMMAND FAR *) &cmd_struct;
    ColInfo = NULL;           // >> FL 1.3.96 added to initialize properly
    AnzOpenStatements ++ ;
    dbCols = -1 ;
    blobCol = -1 ;
    closeDone = TRUE ;
    }

  virtual ~sybstmt ()
    {
    ResetDscList ();
    if ((cmd != NULL) && (!closeDone)) {
      oclose((Cda_Def *) cmd);
      ocirethandling(dbase->lda, cmd);
      }
    AnzOpenStatements -- ;
    if (oldStatement != NULL)
      FreeGlobMem (oldStatement);
    for (int i = 0 ; i < CB_PARAM - 2 ; i++) {
      if (oldParam[i] != NULL) FreeGlobMem (oldParam[i]);
      }
    if (ColInfo != NULL) {
      for (int i = 0 ; i < dbCols ; i++) {
        if (ColInfo[i].VarData != NULL) {
          FreeGlobMem (ColInfo[i].VarLen);
          FreeGlobMem (ColInfo[i].VarData);
          FreeGlobMem (ColInfo[i].VarRetCode);
          FreeGlobMem (ColInfo[i].VarInd);
          }
        }
      FreeGlobMem (ColInfo);
      }
    if (BlockedData != NULL)
      FreeGlobMem (BlockedData);
    }

  void StmtExit ()
    {
    if (BlockedData != NULL)
      FreeGlobMem (BlockedData);
    BlockedData = NULL ;
    ThereAreBlockedData = FALSE ;
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }

  int StandardDelete ();
  int StandardGet ();
  void SelectStatement (LPTABLEDEF td,LongString FAR &s,int KeyNmbr = -1,LPSTR hint = NULL);
  void WhereStatement (LongString FAR &s,LPTABLEDEF td,LPTABLEDEF ti,BOOL FAR &wheredone,BOOL useOld = FALSE);
  void OrderStatement (LongString FAR &s,LPTABLEDEF td,WORD Op,BOOL UsePrimary);
  void SyncStatement (LongString FAR &s,LPDBREQUEST req,LPTABLEDEF td,LPSTR c,LPSTR ce,BOOL whereDone);

  void RowcountStatement (LongString FAR &w,LPDBREQUEST req, int rowcnt, BOOL &whereDone);

  #if defined(ORACLE_SHOWRESULTS)
    void ShowResult (LPVARDEF v,LPVOID data,int Size);
  #endif // ORACLE_SHOWRESULTS

  LPVOID ConvertToMData (LPVARDEF v,LPVOID data,int Size,int FAR *rSize);
  LPVOID ConvertToMData_f (WORD mType,LPVOID data,int Size,int FAR *rSize);
  LPDBRECORD StoreRow (LPTABLEDEF ti,int row);
  int StandardList (BOOL first,BOOL doCursorClose);
  BOOL EnlargeInsert (LPVARDEF vd,int VarNr,LongString FAR &s,LongString FAR &v,int FAR *AnzPars,LPBLOBDESC FAR *bdsc);
  BOOL EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars);
  BOOL EnlargeUpdate (LPVARDEF vd,int VarNr,LongString FAR &s,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0,LPBLOBDESC FAR *bdsc);
  BOOL EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first);
  LPDBRECORD GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize);
  int StandardUpdate ();
  int StandardExcute ();
  int StandardInsert ();
  BOOL CheckOverwriteSequence(LPVARDEF vdauto, int *OverwriteVarNr);
  BOOL EnlargeInsertWithSequence (int overwriteVarNr, LPVARDEF vdauto,LongString FAR &s,LongString FAR &v,int *AnzPars);
  void SynchronizeSequence(LPVARDEF vdauto, int OverwriteVarNr);
  };
typedef sybstmt FAR *LPSYBSTMT;

extern BOOL CreateIndex (LPTABLEDEF td,int KeyNmbr);
extern BOOL CreateAllIndex (LPTABLEDEF td);
extern LPSTR ORAGetTableName (LPTABLEDEF t,BOOL usePrefix);
extern LPSTR GetVarString (LPVOID data,int mType,BOOL FAR *doFree,int Size,BOOL doStatic,int parNr);
extern int _export FAR PASCAL DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
extern LPSTR GetSequenceName (LPSTR TableName);
extern LPSTR GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0);

extern BOOL CheckFile(LPSYBSTMT stmt,BOOL first,BOOL forUpdate);
extern BOOL InAlter();
extern void DelFromTableHash(LPTABLEDEF td);
extern LPSTR GetKeyFieldName(LPSTR FieldName);
extern BOOL TriggerStatement(sybstmt *h,LongString FAR &s,LPTABLEDEF tnew);
extern BOOL IgnoreOracleError(int errnr,BOOL State);

extern DLLExport BOOL _export FAR PASCAL DBIgnoreError (int ErrType,BOOL State);

void DropPackage ();
BOOL CreatePackage ();
LPSTR ProcName (LPSTR Stmt);

