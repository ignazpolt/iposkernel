////////////////////////////////////////////////////////////
//  Verwaltung der Datenbank - DLL's
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/dlladmin.hpv   1.28   03 Dec 1999 02:37:48   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/dlladmin.hpv  $
// 
//    Rev 1.28   03 Dec 1999 02:37:48   Hannes
// ErrorText
// 
//    Rev 1.27   15 Jun 1999 16:21:14   THOMAS
// 1.) DBCurrentDateTime neu.
// 
//    Rev 1.26   07 May 1999 00:19:40   Hannes
// _Fname public
// 
//    Rev 1.25   16 Mar 1999 11:28:06   Hannes
// Prototyp SetErrorRef
// 
//    Rev 1.24   15 Feb 1999 20:04:26   Hannes
// Fehlermeldungen
// 
//    Rev 1.23   05 Feb 1999 21:38:00   Martin
// verbessertes Errorhandling
// 
//    Rev 1.22   19 Jan 1999 19:27:04   Hannes
// SetUserName
// 
//    Rev 1.21   09 Oct 1998 18:46:24   Wolfgang
// 1.) __NET_NWADDRESSSTRTOBIN und __NET_NWADDRESSBINTOSTR neu.
// 2.) NWAddressStrToBin und NWAddressBinToStr neu.
// 3.) __NET_NWSOCKETFAMILY, __NET_NWADDRESSSIZE und __NET_NWSOCKETPROTOCOL neu.
// 4.) NWSocketFamily, NWAddressSize und NWSocketProtocol neu.
// 
//    Rev 1.20   06 Mar 1998 17:26:30   Hannes
// Prototyp Transaktionshandling
// 
//    Rev 1.19   31 Oct 1997 12:50:06   Hannes
// Timestampfunktion
// 
//    Rev 1.18   14 Jan 1997 16:17:20   HANNES
// Neue Prozedure DBPOINTER
// 
//    Rev 1.17   26 Nov 1996 08:08:02   HANNES
// Automatischer Update
// 
//    Rev 1.16   05 Jul 1996 08:10:28   hannes
// typedef short DLLHANDLE
// 
//    Rev 1.15   05 Apr 1996 14:48:10   MARTIN
// Abgleich Schweiz
// 
// 14.03.96 FL Net DLL eingebunden
//
//    Rev 1.14   04 Mar 1996 17:48:12   GERHOLD
// _FName zugaenglich gemacht
// 
//    Rev 1.13   02 Feb 1996 11:04:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   02 Jan 1996 22:18:40   HANNES
// 
//    Rev 1.10   16 Feb 1995 13:02:10   HANNES
//  
// 
//    Rev 1.9   29 Jan 1995 11:46:58   HANNES
// 
//    Rev 1.8   24 Jan 1995 10:57:46   HANNES
// Schluesseldefinition in das Clientdictionary mit aufgenommen
// 
//    Rev 1.7   09 Jan 1995 12:11:42   HANNES
// Debugger eingebaut
// 
//    Rev 1.6   07 Nov 1994 11:45:28   HANNES
// Einbinden von dbbtrv direkt
// 
//    Rev 1.5   31 Oct 1994 10:43:04   hannes
// Transaktionen
// 
//    Rev 1.4   20 Oct 1994 04:08:10   hannes
// Umstellen der Syntax fuer den bloeden 8er Compiler
// 
//    Rev 1.3   19 Oct 1994 22:35:38   hannes
// Einbindung SQL Konverter
// 
//    Rev 1.2   04 Jul 1994 14:56:56   HANNES
// 
//    Rev 1.1   04 Jul 1994 14:47:02   HANNES
// IsViewAllowed
// 
//    Rev 1.0   24 Jun 1994 17:01:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   19 Apr 1994 10:49:04   HANNES
// Initial revision.
//

// forwarddeklaration laesst sich leider nicht umgehen
struct DBRequest;
struct RecBuffer;
typedef DBRequest FAR *LPDBREQUEST;
struct AccessListEntry;
typedef AccessListEntry FAR *LPACCESSLISTENTRY;
struct FAR TableDef;

struct SegNamePtrs {
  LPSTR kn[3];
  };
typedef SegNamePtrs FAR *LPSEGNAMEPTRS;
#define DLL_NOTIMPLEMENTED  -1;
typedef WORD (FAR PASCAL * __DATARES_SETTABLEDEF) (LPSTR DLLName,LPSTR TableName,WORD TableIdMin,WORD TableIdMax,LPVOID TableData,DWORD TableSize,BOOL FAR *changed);
typedef WORD (FAR PASCAL * __DATARES_SETROWDEF) (LPSTR DLLName,WORD TableIdent,LPSTR VarName,LPVOID VarData,DWORD VarSize,BOOL FAR *changed);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETTABLEDEF) (LPSTR DLLName,WORD TableId,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *Size);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETFIRSTROWDEF) (LPSTR DLLName,WORD TableIdent,LPSTR RowName,WORD FAR *RowIdent,DWORD FAR *HeaderSize,DWORD FAR *RowSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETNEXTROWDEF) (LPSTR DLLName,WORD TableIdent,WORD PrevRow,LPSTR RowName,WORD FAR *RowIdent,DWORD FAR *HeaderSize,DWORD FAR *RowSize);
typedef void (FAR PASCAL * __DATARES_SETFULLTABLEDEF) (LPSTR DLLName,WORD TableIdent,LPSTR TableName,LPVOID TableData,DWORD TableSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETFULLTABLEDEF) (LPSTR DLLName,WORD TableIdent,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize);
typedef BOOL (FAR PASCAL * __DATARES_GETFIRSTTABLEDEF) (WORD FAR *TableIdent,LPSTR TableName);
typedef BOOL (FAR PASCAL * __DATARES_GETNEXTTABLEDEF) (WORD PrevIdent,WORD FAR *TableIdent,LPSTR TableName);
typedef void (FAR PASCAL * __DATARES_SETDICTCONT) (LPVOID Data,DWORD DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETDICTCONT) (DWORD FAR *HeaderSize,DWORD FAR *DataSize);
typedef void (FAR PASCAL * __DATARES_SETDOCDEF) (LPSTR DocName,LPVOID DocData,DWORD DataSize);
typedef void (FAR PASCAL * __DATARES_SETFUNCDEF) (LPVOID DocData,DWORD DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETDOCDEF) (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETFUNCDEF) (DWORD FAR *HeaderSize,DWORD FAR *DocSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETFIRSTDOC) (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETNEXTDOC) (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize);
typedef void (FAR PASCAL * __DATARES_SETDOCCONT) (LPVOID DocData,DWORD DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETDOCCONT) (DWORD FAR *HeaderSize,DWORD FAR *DocSize);
typedef DWORD (FAR PASCAL * __DATARES_SETRESOURCE) (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETRESOURCE) (DWORD ResId,DWORD FAR *HeaderSize,DWORD FAR *DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETFIRSTRESOURCE) (WORD Type,DWORD FAR *Id,LPSTR ResName,DWORD FAR *HeaderSize,DWORD FAR *DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETNEXTRESOURCE) (WORD Type,DWORD FAR *Id,LPSTR ResName,DWORD FAR *HeaderSize,DWORD FAR *DataSize);
typedef void (FAR PASCAL * __DATARES_SETRESCONT) (WORD Type,LPVOID Data,DWORD DataSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETRESCONT) (WORD Type,DWORD FAR *HeaderSize,DWORD FAR *DataSize);
typedef void (FAR PASCAL * __DATARES_CLEARROWDEFS) (LPSTR DLLName,WORD TableIdent);
typedef void (FAR PASCAL * __DATARES_DELTABLEDEF) (LPSTR DLLName,WORD TableIdent);

typedef LPVOID (FAR PASCAL * __DATADICT_TABLEDEF) (LPVOID InitData,LPSTR TableString,BOOL FAR *error,DWORD FAR *size);
typedef void (FAR PASCAL * __DATADICT_FREETABLEDEF) (LPVOID TableData);
typedef LPVOID (FAR PASCAL * __DATADICT_VARDEF) (LPVOID InitData,WORD mType,LPVOID TableData,LPSTR VarString,BOOL FAR *error,DWORD FAR *size);
typedef void (FAR PASCAL * __DATADICT_FREEVARDEF) (LPVOID VarData);
typedef WORD (FAR PASCAL * __DATADICT_GETMTYPE) (LPVOID VarData);
typedef LPACCESSLISTENTRY (FAR PASCAL * __DATADICT_GETACCESSLIST) (LPVOID TableData);
typedef void (FAR PASCAL * __DATADICT_GETVARDESCEXTRA) (LPVOID VarData,LPSTR txt,WORD txtSize);
typedef BOOL (FAR PASCAL * __DATADICT_ISFOREIGNKEY) (LPVOID VarData,LPSTR TableName,int TableNameSize,LPSTR AccessName,int AccessNameSize,LPSTR DelName,int DelNameSize,LPSEGNAMEPTRS keysegs);
typedef BOOL (FAR PASCAL * __DATADICT_ISPRIMARY) (LPVOID VarData);
typedef BOOL (FAR PASCAL * __DATADICT_ISACCESSFORVIEW) (LPVOID DLLData,LPSTR SelectionName);
typedef LPSTR (FAR PASCAL * __DATADICT_GETSQLPART) (WORD Type,LPSTR Name,LPVOID TableData,WORD VarID,WORD KeyID,LPSTR Buffer,WORD BuffSize);
typedef void (FAR PASCAL * __DAVOIDFUNC) (void);
typedef void (FAR PASCAL * __DABOOLFUNC) (BOOL largeTransaction);
typedef BOOL (FAR PASCAL * __DATADICT_GETVARPROPERTY) (LPVOID TableData,LPVOID VarData,WORD PropCmd,LPVOID PropData);
typedef GLOBALHANDLE (FAR PASCAL * __DATARES_GETSERVERSOURCE) (LPSTR DLLName,WORD TableIdent,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize);
typedef void (FAR PASCAL * __DATARES_SETSERVERSOURCE) (LPSTR DLLName,WORD TableIdent,LPSTR TableName,LPVOID TableData,DWORD TableSize);
typedef GLOBALHANDLE (FAR PASCAL * __DATADICT_LASTSERVERSOURCE) ();
typedef LPVOID (FAR PASCAL * __DATADICT_NEWTABLEDEF) (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size);
typedef void (FAR PASCAL * __DBSETLOGFUNC) (BOOL logState, LPSTR logFile);

typedef GLOBALHANDLE (FAR PASCAL *__DBHELP_GET) (WORD Type,LPSTR Name,DWORD FAR *TableSize);
typedef void (FAR PASCAL * __DBHELP_PUT) (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize);

typedef void (FAR PASCAL * __DBRESET) ();
typedef int (FAR PASCAL * __DBCALL) (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);

struct DefVal {
  short  VarID;
  LPSTR  VarName;
  LPVOID DefaultValue;
  WORD   mType;
  };
typedef void (FAR PASCAL * __ALTERSUCCESS) (DWORD success);
typedef int (FAR PASCAL * __DBALTER) (TableDef FAR *told,TableDef FAR *tnew,int AnzDefs,DefVal FAR *dv,__ALTERSUCCESS alts);
#define ERRTYPE_ALLERRORS    -2
#define ERRTYPE_USERDEFINED  -1
#define ERRTYPE_OBJEXISTS     1
#define ERRTYPE_DUPLICATEKEY  2
#define ERRTYPE_OBJNOTEXISTS  3
#define ERRTYPE_NOPRIVILEGS   4
typedef BOOL (FAR PASCAL * __DBIGNOREERROR) (int ErrType,BOOL state);
typedef LPVOID (FAR PASCAL * __DBPOINT) ();
typedef void (FAR PASCAL * __MAKETIMESTAMP) (LPSTR Msg);

// API to the NET DLL:
typedef int   (FAR PASCAL * __NET_NWSOCKETFAMILY      ) ();
typedef int   (FAR PASCAL * __NET_NWADDRESSSIZE       ) ();
typedef int   (FAR PASCAL * __NET_NWSOCKETPROTOCOL    ) (int type);
typedef void  (FAR PASCAL * __NET_GETUNIQUEADDRESS    ) (LPSTR str, int size);
typedef BOOL  (FAR PASCAL * __NET_NWADDRESSSTRTOBIN   ) (LPVOID binAddr, int *size, LPSTR str, DBINT port);
typedef BOOL  (FAR PASCAL * __NET_NWADDRESSBINTOSTR   ) (LPSTR str, int size, DBINT *port, LPVOID binAddr);
typedef DWORD (FAR PASCAL * __NET_SETSTATIONSEMAPHOR  ) (LPSTR uniqueID);          
typedef void  (FAR PASCAL * __NET_CLEARSTATIONSEMAPHOR) (DWORD Handle);
typedef BOOL  (FAR PASCAL * __NET_CHECKSTATIONSEMAPHOR) (LPSTR uniqueID);
typedef DWORD (FAR PASCAL * __NET_SETSEMA             ) (LPSTR Name, WORD FAR *Count);
typedef void  (FAR PASCAL * __NET_CLEARSEMA           ) (DWORD Handle);
typedef BOOL  (FAR PASCAL * __NET_TESTSEMA            ) (LPSTR Name);
typedef int   (FAR PASCAL * __NET_GETCONNECTIONNMBR   ) ();
typedef BOOL  (FAR PASCAL * __NET_SEMAPHOREAVAILABLE  ) ();

typedef void  (FAR PASCAL * __SETUSERNAME             ) (LPSTR un,LPSTR pw);
typedef int   (FAR PASCAL * __DBGETLASTERROR          ) ();
typedef BOOL  (FAR PASCAL * __DBCURRENTDATETIME       ) (LPVOID pdt);
typedef LPSTR (FAR PASCAL * __DBGETLASTERRORTEXT      ) ();

#define MAXDLLPROC                      73

class FAR DLLEntry {
 private :
  FARPROC DLLProc [MAXDLLPROC];
  HINSTANCE hDLLInst;

  BOOL doUpdate;

  char _name[64];

 public :
  char _Fname[64];
  DLLEntry (LPSTR DLLName,BOOL doTest);
  ~DLLEntry ();
  
  // Aufruf der Funktionen
  inline WORD DataRes_SetTableDef (LPSTR DLLName,LPSTR TableName,WORD TableIdMin,WORD TableIdMax,LPVOID TableData,DWORD TableSize,BOOL FAR *changed)
    { 
    if (DLLProc[_DATARES_SETTABLEDEF] != NULL)
      return (* (__DATARES_SETTABLEDEF (DLLProc[_DATARES_SETTABLEDEF]))) (DLLName,TableName,TableIdMin,TableIdMax,TableData,TableSize,changed);
    else
      return 0;
    }
  inline WORD DataRes_SetRowDef (LPSTR DLLName,WORD TableIdent,LPSTR VarName,LPVOID VarData,DWORD VarSize,BOOL FAR *changed)
    { 
    if (DLLProc[_DATARES_SETROWDEF] != NULL)
      return (* (__DATARES_SETROWDEF (DLLProc[_DATARES_SETROWDEF]))) (DLLName,TableIdent,VarName,VarData,VarSize,changed);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetTableDef (LPSTR DLLName,WORD TableId,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *Size)
    { 
    if (DLLProc[_DATARES_GETTABLEDEF] != NULL)
      return (* (__DATARES_GETTABLEDEF (DLLProc[_DATARES_GETTABLEDEF]))) (DLLName,TableId,TableName,HeaderSize,Size);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetFirstRowDef (LPSTR DLLName,WORD TableIdent,LPSTR RowName,WORD FAR *RowIdent,DWORD FAR *HeaderSize,DWORD FAR *RowSize)
    { 
    if (DLLProc[_DATARES_GETFIRSTROWDEF] != NULL)
      return (* (__DATARES_GETFIRSTROWDEF (DLLProc[_DATARES_GETFIRSTROWDEF]))) (DLLName,TableIdent,RowName,RowIdent,HeaderSize,RowSize);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetNextRowDef (LPSTR DLLName,WORD TableIdent,WORD PrevRow,LPSTR RowName,WORD FAR *RowIdent,DWORD FAR *HeaderSize,DWORD FAR *RowSize)
    { 
    if (DLLProc[_DATARES_GETNEXTROWDEF] != NULL)
      return (* (__DATARES_GETNEXTROWDEF (DLLProc[_DATARES_GETNEXTROWDEF]))) (DLLName,TableIdent,PrevRow,RowName,RowIdent,HeaderSize,RowSize);
    else
      return 0;
    }
  inline void DataRes_SetFullTableDef (LPSTR DLLName,WORD TableIdent,LPSTR TableName,LPVOID TableData,DWORD TableSize)
    { 
    if (DLLProc[_DATARES_SETFULLTABLEDEF] != NULL)
      (* ((__DATARES_SETFULLTABLEDEF) DLLProc[_DATARES_SETFULLTABLEDEF])) (DLLName,TableIdent,TableName,TableData,TableSize);
    }
  inline GLOBALHANDLE DataRes_GetFullTableDef (LPSTR DLLName,WORD TableIdent,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize)
    { 
    if (DLLProc[_DATARES_GETFULLTABLEDEF] != NULL)
      return (* (__DATARES_GETFULLTABLEDEF (DLLProc[_DATARES_GETFULLTABLEDEF]))) (DLLName,TableIdent,TableName,HeaderSize,TableSize);
    else
      return 0;
    }
  inline BOOL DataRes_GetFirstTableDef (WORD FAR *TableIdent,LPSTR TableName)
    { 
    if (DLLProc[_DATARES_GETFIRSTTABLEDEF] != NULL)
      return (* (__DATARES_GETFIRSTTABLEDEF (DLLProc[_DATARES_GETFIRSTTABLEDEF]))) (TableIdent,TableName);
    else
      return FALSE;
    }
  inline BOOL DataRes_GetNextTableDef (WORD PrevIdent,WORD FAR *TableIdent,LPSTR TableName)
    { 
    if (DLLProc[_DATARES_GETNEXTTABLEDEF] != NULL)
      return (* (__DATARES_GETNEXTTABLEDEF (DLLProc[_DATARES_GETNEXTTABLEDEF]))) (PrevIdent,TableIdent,TableName);
    else
      return FALSE;
    }
  inline void DataRes_SetDictCont (LPVOID Data,DWORD DataSize)
    { 
    if (DLLProc[_DATARES_SETDICTCONT] != NULL)
      (* ((__DATARES_SETDICTCONT) DLLProc[_DATARES_SETDICTCONT])) (Data,DataSize);
    }
  inline GLOBALHANDLE DataRes_GetDictCont (DWORD FAR *HeaderSize,DWORD FAR *DataSize)
    { 
    if (DLLProc[_DATARES_GETDICTCONT] != NULL)
      return (* (__DATARES_GETDICTCONT (DLLProc[_DATARES_GETDICTCONT]))) (HeaderSize,DataSize);
    else
      return 0;
    }
  inline void DataRes_SetDocDef (LPSTR DocName,LPVOID DocData,DWORD DataSize)
    { 
    if (DLLProc[_DATARES_SETDOCDEF] != NULL)
      (* ((__DATARES_SETDOCDEF) DLLProc[_DATARES_SETDOCDEF])) (DocName,DocData,DataSize);
    }
  inline void DataRes_SetFuncDef (LPVOID DocData,DWORD DataSize)
    { 
    if (DLLProc[_DATARES_SETFUNCDEF] != NULL)
      (* ((__DATARES_SETFUNCDEF) DLLProc[_DATARES_SETFUNCDEF])) (DocData,DataSize);
    }
  inline GLOBALHANDLE DataRes_GetDocDef (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
    { 
    if (DLLProc[_DATARES_GETDOCDEF] != NULL)
      return (* (__DATARES_GETDOCDEF (DLLProc[_DATARES_GETDOCDEF]))) (DocName,HeaderSize,DocSize);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetFuncDef (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
    { 
    if (DLLProc[_DATARES_GETFUNCDEF] != NULL)
      return (* (__DATARES_GETFUNCDEF (DLLProc[_DATARES_GETFUNCDEF]))) (HeaderSize,DocSize);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetFirstDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
    { 
    if (DLLProc[_DATARES_GETFIRSTDOC] != NULL)
      return (* (__DATARES_GETFIRSTDOC (DLLProc[_DATARES_GETFIRSTDOC]))) (DocName,HeaderSize,DocSize);
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetNextDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
    { 
    if (DLLProc[_DATARES_GETNEXTDOC] != NULL)
      return (* (__DATARES_GETNEXTDOC (DLLProc[_DATARES_GETNEXTDOC]))) (DocName,HeaderSize,DocSize);
    else
      return 0;
    }
  inline void DataRes_SetDocCont (LPVOID DocData,DWORD DataSize)
    { 
    if (DLLProc[_DATARES_SETDOCCONT] != NULL)
      (* ((__DATARES_SETDOCCONT) DLLProc[_DATARES_SETDOCCONT])) (DocData,DataSize);
    }
  inline GLOBALHANDLE DataRes_GetDocCont (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
    { 
    if (DLLProc[_DATARES_GETDOCCONT] != NULL)
      return (* (__DATARES_GETDOCCONT (DLLProc[_DATARES_GETDOCCONT]))) (HeaderSize,DocSize);
    else
      return 0;
    }
  inline DWORD DataRes_SetResource (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
    { 
    if (DLLProc[_DATARES_SETRESOURCE] != NULL)
      return (* (__DATARES_SETRESOURCE (DLLProc[_DATARES_SETRESOURCE]))) (Type,Name,Data,DataSize);
    else
      return 0L;
    }
  inline GLOBALHANDLE DataRes_GetResource (DWORD ResId,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
    { 
    if (DLLProc[_DATARES_GETRESOURCE] != NULL)
      return (* (__DATARES_GETRESOURCE (DLLProc[_DATARES_GETRESOURCE]))) (ResId,HeaderSize,DataSize);
    else
      return 0;
    }
  inline void DBReset ()
    { 
    if (DLLProc[_DBRESET] != NULL)
      (* ((__DBRESET) DLLProc[_DBRESET])) ();
    }
  inline LPVOID DataDict_TableDef (LPVOID InitData,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
    {
    if (DLLProc[_DATADICT_TABLEDEF] != NULL)
      return (* (__DATADICT_TABLEDEF (DLLProc[_DATADICT_TABLEDEF]))) (InitData,TableString,error,size);
    else
      return NULL ;
    }
  inline void DataDict_FreeTableDef (LPVOID TableData)
    {
    if (DLLProc[_DATADICT_FREETABLEDEF] != NULL)
      (* ((__DATADICT_FREETABLEDEF) DLLProc[_DATADICT_FREETABLEDEF])) (TableData);
    }
  inline int DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
    {
    if (DLLProc[_DBCALL] != NULL)
      return (* (__DBCALL (DLLProc[_DBCALL]))) (Op,AnzLines,req,hstmt,res);
    else
      return DLL_NOTIMPLEMENTED;
    }
  inline LPVOID DataDict_VarDef (LPVOID InitData,WORD mType,LPVOID TableData,LPSTR VarString,BOOL FAR *error,DWORD FAR *size)
    {
    if (DLLProc[_DATADICT_VARDEF] != NULL)
      return (* (__DATADICT_VARDEF (DLLProc[_DATADICT_VARDEF]))) (InitData,mType,TableData,VarString,error,size);
    else
      return NULL;
    }
  inline void DataDict_FreeVarDef (LPVOID VarData)
    {
    if (DLLProc[_DATADICT_FREEVARDEF] != NULL) {
      (* ((__DATADICT_FREEVARDEF) DLLProc[_DATADICT_FREEVARDEF])) (VarData);
      }
    }
  inline WORD DataDict_GetMType (LPVOID VarData)
    {
    if (DLLProc[_DATADICT_GETMTYPE] != NULL) {
      return (* (__DATADICT_GETMTYPE (DLLProc[_DATADICT_GETMTYPE]))) (VarData);
      }
    else
      return 0xFFFF;
    }
  inline LPACCESSLISTENTRY DataDict_GetAccessList (LPVOID TableData)
    {
    if (DLLProc[_DATADICT_GETACCESSLIST] != NULL) {
      return (* (__DATADICT_GETACCESSLIST (DLLProc[_DATADICT_GETACCESSLIST]))) (TableData);
      }
    else
      return NULL;
    }
  inline void DataDict_GetVarDescExtra (LPVOID VarData,LPSTR txt,WORD txtSize)
    {
    if (DLLProc [_DATADICT_GETVARDESCEXTRA] != NULL) {
      ( * ((__DATADICT_GETVARDESCEXTRA) DLLProc[_DATADICT_GETVARDESCEXTRA])) (VarData,txt,txtSize);
      }
    }
  inline BOOL DataDict_IsForeignKey (LPVOID VarData,LPSTR TableName,int TableNameSize,LPSTR AccessName,int AccessNameSize,LPSTR DelName,int DelNameSize,LPSEGNAMEPTRS keysegs)
    {
    if (DLLProc [_DATADICT_ISFOREIGNKEY] != NULL) {
      return ( * (__DATADICT_ISFOREIGNKEY (DLLProc[_DATADICT_ISFOREIGNKEY]))) (VarData,TableName,TableNameSize,AccessName,AccessNameSize,DelName,DelNameSize,keysegs);
      }
    else
      return FALSE ;
    }
  inline void DataRes_ClearRowDefs (LPSTR DLLName,WORD TableIdent)
    {
    if (DLLProc [_DATARES_CLEARROWDEFS] != NULL)
      ( * ((__DATARES_CLEARROWDEFS) DLLProc[_DATARES_CLEARROWDEFS])) (DLLName,TableIdent);
    }
  inline void DataRes_DelTableDef (LPSTR DLLName,WORD TableIdent)
    {
    if (DLLProc [_DATARES_DELTABLEDEF] != NULL)
      ( * ((__DATARES_DELTABLEDEF) DLLProc[_DATARES_DELTABLEDEF])) (DLLName,TableIdent);
    }
  inline BOOL DataDict_IsPrimary (LPVOID VarData)
    {
    if (DLLProc [_DATADICT_ISPRIMARY] != NULL)
      return ( * (__DATADICT_ISPRIMARY (DLLProc[_DATADICT_ISPRIMARY]))) (VarData);
    else
      return FALSE ;
    }
  inline GLOBALHANDLE DataRes_GetFirstResource (WORD Type,DWORD FAR *Id,LPSTR ResName,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
    {
    if (DLLProc [_DATARES_GETFIRSTRESOURCE] != NULL)
      return ( * (__DATARES_GETFIRSTRESOURCE (DLLProc[_DATARES_GETFIRSTRESOURCE]))) (Type,Id,ResName,HeaderSize,DataSize) ;
    else
      return 0;
    }
  inline GLOBALHANDLE DataRes_GetNextResource (WORD Type,DWORD FAR *Id,LPSTR ResName,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
    {
    if (DLLProc [_DATARES_GETNEXTRESOURCE] != NULL)
      return ( * (__DATARES_GETNEXTRESOURCE (DLLProc[_DATARES_GETNEXTRESOURCE]))) (Type,Id,ResName,HeaderSize,DataSize) ;
    else
      return 0;
    }
  inline void DataRes_SetResCont (WORD Type,LPVOID Data,DWORD DataSize)
    {
    if (DLLProc [_DATARES_SETRESCONT] != NULL)
      ( * ((__DATARES_SETRESCONT) DLLProc[_DATARES_SETRESCONT])) (Type,Data,DataSize) ;
    }
  inline GLOBALHANDLE DataRes_GetResCont (WORD Type,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
    {
    if (DLLProc [_DATARES_GETRESCONT] != NULL)
      return ( * (__DATARES_GETRESCONT (DLLProc[_DATARES_GETRESCONT]))) (Type,HeaderSize,DataSize) ;
    else
      return 0;
    }
  inline BOOL DataDict_IsAccessForView (LPVOID DLLData,LPSTR SelectionName)
    {
    if (DLLProc [_DATADICT_ISACCESSFORVIEW] != NULL)
      return ( * (__DATADICT_ISACCESSFORVIEW (DLLProc[_DATADICT_ISACCESSFORVIEW]))) (DLLData,SelectionName) ;
    else
      return 0;
    }

  LPSTR DataDict_GetSQLPart (WORD Cmd,LPSTR TableName,LPVOID dllData,WORD VarNmbr,WORD KeyNmbr,LPSTR Buffer,WORD BufferSize)
    {
    if (DLLProc [_DATADICT_GETSQLPART] != NULL)
      return ( * (__DATADICT_GETSQLPART (DLLProc[_DATADICT_GETSQLPART]))) (Cmd,TableName,dllData,VarNmbr,KeyNmbr,Buffer,BufferSize);
    else
      return NULL;
    }

  BOOL DataDict_GetVarProperty (LPVOID TableData,LPVOID VarData,WORD PropCmd,LPVOID PropData)
    {
    if (DLLProc [_DATADICT_GETVARPROPERTY] != NULL)
      return ( * (__DATADICT_GETVARPROPERTY (DLLProc[_DATADICT_GETVARPROPERTY]))) (TableData,VarData,PropCmd,PropData);
    else
      return FALSE;
    }

  GLOBALHANDLE DataRes_GetServerSource (LPSTR DLLName,WORD TableIdent,LPSTR TableName,DWORD FAR *HeaderSize,DWORD FAR *TableSize)
    {
    if (DLLProc [_DATARES_GETSERVERSOURCE] != NULL)
      return ( * ((__DATARES_GETSERVERSOURCE) (DLLProc[_DATARES_GETSERVERSOURCE]))) (DLLName,TableIdent,TableName,HeaderSize,TableSize);
    else
      return NULL;
    }
  void DataRes_SetServerSource (LPSTR DLLName,WORD TableIdent,LPSTR TableName,LPVOID TableData,DWORD TableSize)
    {
    if (DLLProc [_DATARES_SETSERVERSOURCE] != NULL)
      ( * ((__DATARES_SETSERVERSOURCE) (DLLProc[_DATARES_SETSERVERSOURCE]))) (DLLName,TableIdent,TableName,TableData,TableSize);
    }
  GLOBALHANDLE DataDict_LastServerSource ()
    {
    if (DLLProc [_DATADICT_LASTSERVERSOURCE] != NULL)
      return ( * ((__DATADICT_LASTSERVERSOURCE) (DLLProc[_DATADICT_LASTSERVERSOURCE]))) ();
    else
      return NULL;
    }
  LPVOID DataDict_NewTableDef (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
    {
    if (DLLProc [_DATADICT_NEWTABLEDEF] != NULL)
      return ( * ((__DATADICT_NEWTABLEDEF) (DLLProc [_DATADICT_NEWTABLEDEF]))) (ClientTable,TableString,error,size);
    else
      return NULL ;
    }
  GLOBALHANDLE DBHelp_Get (WORD Type,LPSTR Name,DWORD FAR *TableSize)
    {
    if (DLLProc [_DBHELP_GET] != NULL)
      return ( * ((__DBHELP_GET) (DLLProc [_DBHELP_GET]))) (Type,Name,TableSize);
    else
      return NULL ;
    }
  void DBHelp_Put (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
    {
    if (DLLProc [_DBHELP_PUT] != NULL)
      ( * ((__DBHELP_PUT) (DLLProc [_DBHELP_PUT]))) (Type,Name,Data,DataSize);
    }

  void DoSetDBLogState (BOOL logState, LPSTR logFile)
    {
    if (DLLProc [_SETDBLOGSTATE] != NULL)
      ( * ((__DBSETLOGFUNC) DLLProc[_SETDBLOGSTATE])) (logState,logFile) ;
    }

  void DoBeginTransaction (BOOL doLarge)
    {
    if (DLLProc [_DOBEGINTRANSACTION] != NULL)
      ( * ((__DABOOLFUNC) DLLProc[_DOBEGINTRANSACTION])) (doLarge) ;
    }
  void DoEndTransaction (void)
    {
    if (DLLProc [_DOENDTRANSACTION  ] != NULL)
      ( * ((__DAVOIDFUNC) DLLProc[_DOENDTRANSACTION  ])) () ;
    }
  void DoAbortTransaction (void)
    {
    if (DLLProc [_DOABORTTRANSACTION] != NULL)
      ( * ((__DAVOIDFUNC) DLLProc[_DOABORTTRANSACTION])) () ;
    }
  int DBAlter (TableDef FAR *told,TableDef FAR *tnew,__ALTERSUCCESS alts,int AnzDefs = 0,DefVal FAR *v = NULL)
    {
    if (DLLProc [_DBALTER] != NULL)
      return ( * ((__DBALTER) (DLLProc [_DBALTER]))) (told,tnew,AnzDefs,v,alts);
    else
      return DLL_NOTIMPLEMENTED ;
    }
  BOOL DBIgnoreError (int ErrType,BOOL State)
    {
    if (DLLProc [_DBIGNOREERROR] != NULL)
      return (* ((__DBIGNOREERROR) (DLLProc [_DBIGNOREERROR]))) (ErrType,State) ;
    else
      return TRUE ;
    }
  void MakeTimeStamp (LPSTR Msg)
    {
    if (DLLProc [_MAKETIMESTAMP] != NULL)
      (* ((__MAKETIMESTAMP) (DLLProc [_MAKETIMESTAMP]))) (Msg) ;
    }

  
/* DNET API */  
  inline int NWSocketFamily () {
    if (DLLProc[_NET_NWSOCKETFAMILY] != NULL)
      return ( * ((__NET_NWSOCKETFAMILY) DLLProc[_NET_NWSOCKETFAMILY])) ();
    else {
      return -1;
      } // if
    } // NWSocketFamily
    
  inline int NWAddressSize () {
    if (DLLProc[_NET_NWADDRESSSIZE] != NULL)
      return ( * ((__NET_NWADDRESSSIZE) DLLProc[_NET_NWADDRESSSIZE])) ();
    else {
      return 0;
      } // if
    } // NWAddressSize
    
  inline int NWSocketProtocol (int type) {
    if (DLLProc[_NET_NWSOCKETPROTOCOL] != NULL)
      return ( * ((__NET_NWSOCKETPROTOCOL) DLLProc[_NET_NWSOCKETPROTOCOL])) (type);
    else {
      return -1;
      } // if
    } // NWSocketProtocol
    
  inline void GetUniqueAddress (LPSTR str, int size) {
    if (DLLProc[_NET_GETUNIQUEADDRESS] != NULL)
      ( * ((__NET_GETUNIQUEADDRESS) DLLProc[_NET_GETUNIQUEADDRESS])) (str, size);
    else {
      *str = 0; // no unique address found
      } // if
    } // GetUniqueAddress           
    
  inline BOOL NWAddressStrToBin (LPVOID binAddr, int *size, LPSTR str, DBINT port) {
    if (DLLProc[_NET_NWADDRESSSTRTOBIN] != NULL)
      return ( * ((__NET_NWADDRESSSTRTOBIN) DLLProc[_NET_NWADDRESSSTRTOBIN])) (binAddr, size, str, port);
    else {
      *size = 0;
      return FALSE;
      } // if
    } // NWAddressStrToBin
    
  inline BOOL NWAddressBinToStr (LPSTR str, int size, DBINT *port, LPVOID binAddr) {
    if (DLLProc[_NET_NWADDRESSBINTOSTR] != NULL)
      return ( * ((__NET_NWADDRESSBINTOSTR) DLLProc[_NET_NWADDRESSBINTOSTR])) (str, size, port, binAddr);
    else {
      *str = 0;
      *port = -1;
      return FALSE;
      } // if
    } // NWAddressBinToStr
    
  inline DWORD NetSetStationsemaphor (LPSTR uniqueID) {
    if (DLLProc[_NET_SETSTATIONSEMAPHOR] != NULL)
      return ( * ((__NET_SETSTATIONSEMAPHOR) DLLProc[_NET_SETSTATIONSEMAPHOR])) (uniqueID);
    else {
      return 0;
      } // if
    } // NetSetStationsemaphor
  
  inline void  NetClearStationSemaphor (DWORD Handle) {
    if (DLLProc[_NET_CLEARSTATIONSEMAPHOR] != NULL)
      ( * ((__NET_CLEARSTATIONSEMAPHOR) DLLProc[_NET_CLEARSTATIONSEMAPHOR])) (Handle);
    else {
      } // if
    } // NetClearStationSemaphor
  
  inline BOOL  NetCheckStationSemaphor (LPSTR uniqueID) {
    if (DLLProc[_NET_CHECKSTATIONSEMAPHOR] != NULL)
      return ( * ((__NET_CHECKSTATIONSEMAPHOR) DLLProc[_NET_CHECKSTATIONSEMAPHOR])) (uniqueID);
    else {
      return (FALSE);
      } // if
    } // NetCheckStationSemaphor
  
  inline DWORD NetSetSema (LPSTR Name, WORD FAR *Count) {
    if (DLLProc[_NET_SETSEMA] != NULL)
      return ( * ((__NET_SETSEMA) DLLProc[_NET_SETSEMA])) (Name, Count);
    else {                                          
      return 0;
      } // if
    } // NetSetSema
  
  inline void  NetClearSema (DWORD Handle) {
    if (DLLProc[_NET_CLEARSEMA] != NULL)
      (* ((__NET_CLEARSEMA) DLLProc[_NET_CLEARSEMA])) (Handle);
    else {
      } // if
    } // NetClearSema
  
  inline BOOL  NetTestSema (LPSTR Name) {
    if (DLLProc[_NET_TESTSEMA] != NULL)
      return ( * ((__NET_TESTSEMA) DLLProc[_NET_TESTSEMA])) (Name);
    else {
      return FALSE;
      } // if
    } // NetTestSema
  
  inline int   NetGetConnectionNmbr () {
    if (DLLProc[_NET_GETCONNECTIONNMBR] != NULL)
      return (* ((__NET_GETCONNECTIONNMBR) DLLProc[_NET_GETCONNECTIONNMBR])) ();
    else {
      return 0;
      } // if
    } // NetGetConnectionNmbr

  inline BOOL  NetSemaphoreAvailable () {
    if (DLLProc[_NET_SEMAPHOREAVAILABLE] != NULL)
      return (* ((__NET_SEMAPHOREAVAILABLE) DLLProc[_NET_SEMAPHOREAVAILABLE])) ();
    else {
      return FALSE;
      } // if
    } // NetSemaphoreAvailable

  inline LPVOID DBGetPointer ()
    {
    if (DLLProc[_DBPOINT] != NULL)
      return (* ((__DBPOINT) DLLProc[_DBPOINT])) ();
    else {
      return FALSE;
      } // if
    }

  inline void SetUserName (LPSTR un,LPSTR pw)
    {
    if (DLLProc[_SETUSERNAME] != NULL)
      (* ((__SETUSERNAME) DLLProc[_SETUSERNAME])) (un,pw);
    }

  inline int DBGetLastError () {
    if (DLLProc[_DBGETLASTERROR] != NULL)
      return (* ((__DBGETLASTERROR) DLLProc[_DBGETLASTERROR])) ();
    else {
      return 0;
      } // if
    } // DBGetLastError

  inline LPSTR DBGetLastErrorText () {
    if (DLLProc[_DBGETLASTERRORTEXT] != NULL)
      return (* ((__DBGETLASTERRORTEXT) DLLProc[_DBGETLASTERRORTEXT])) ();
    else {
      return NULL;
      } // if
    } // DBGetLastErrorText

  inline BOOL DBCurrentDateTime (LPVOID pdt) {
    if (DLLProc[_DBCURRENTDATETIME] != NULL)
      return (* ((__DBCURRENTDATETIME) DLLProc[_DBCURRENTDATETIME])) (pdt);
    else {
      return FALSE;
      } // if
    } // DBCurrentDateTime

  inline void ClearUpdate ()
    { doUpdate = FALSE ; }
  inline BOOL DoUpdateOnWrite ()
    { return doUpdate ; }
  LPSTR GetDLLName ()
    { return _name ; }
  LPSTR GetDLLFName ()
    { return _Fname ; }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  friend class DLLAdmin;
  };
typedef DLLEntry FAR *LPDLLENTRY;

typedef short DLLHANDLE;

#define MAXDLLS   21

class FAR DLLAdmin {
 private :
  LPDLLENTRY dll[MAXDLLS];
  DLLHANDLE  GetFreeEntry();
  DLLHANDLE  GetDLLNmbr(LPSTR DLLName);
 public :
  DLLExport DLLHANDLE _export FAR PASCAL LoadResDLL ();
  DLLExport DLLHANDLE _export FAR PASCAL LoadDefaultDLL ();
  DLLExport DLLHANDLE _export FAR PASCAL LoadDLL (LPSTR DLLName);
  DLLExport void _export FAR PASCAL ResetDLLAdmin();

  LPDLLENTRY GetDLLEntry (DLLHANDLE handle)
    {
    return dll[handle];
    }
  };

DLLExport void _export FAR PASCAL SetDBLogState (BOOL logState, LPSTR logFile);
DLLExport void _export FAR PASCAL BeginTransaction (BOOL Large);
DLLExport void _export FAR PASCAL EndTransaction ();
DLLExport void _export FAR PASCAL AbortTransaction ();

typedef DLLAdmin FAR *LPDLLADMIN;

DLLExport LPDLLADMIN _export FAR PASCAL GetDLLAdmin();

/*----< Property - Kommandos zum Abfragen von Variableneiegenschaften >-----*/
#define VPROP_DATASIZE        0
#define VPROP_DATAID          1
#define VPROP_GETANZKEYSEGS   2
#define VPROP_GETKEYSEGINFO   3
#define VPROP_GETFOREIGNDATA  4
