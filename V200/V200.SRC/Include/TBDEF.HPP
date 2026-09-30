//////////////////////////////////////////////////////////////////////
//  Klasse TableDef
//////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/tbdef.hpv   1.31   27 Jul 1998 17:08:48   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/tbdef.hpv  $
// 
//    Rev 1.31   27 Jul 1998 17:08:48   Hannes
// TablePropertys
// 
//    Rev 1.30   01 Dec 1997 19:38:38   Hannes
// Diverse Anpassungen
// 
//    Rev 1.29   19 Nov 1997 18:45:22   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.28   18 Jul 1997 08:07:08   Hannes
// 
//    Rev 1.27   11 Jul 1997 11:26:32   Hannes
// 
//    Rev 1.26   04 Jul 1997 19:34:52   Hannes
// 
//    Rev 1.25   27 May 1997 11:12:20   Hannes
// GetTableDefFromID
// 
//    Rev 1.24   19 Feb 1997 12:03:38   Hannes
// Scriptfunktionen->Vater in den scripthd
// 
//    Rev 1.23   17 Dec 1996 18:07:44   HANNES
// 
//    Rev 1.22   26 Nov 1996 08:08:10   HANNES
// Automatischer Update
// 
//    Rev 1.21   08 Nov 1996 13:29:50   HANNES
// Replikator
// 
//    Rev 1.20   29 Oct 1996 12:02:18   GERHOLD
// neue Funktion "TableAdmin::GetAnzTables"
// 
//    Rev 1.19   12 Sep 1996 23:30:30   HANNES
// 
//    Rev 1.18   05 Jul 1996 08:11:12   gerhold
// short AnzSegs (32 Bit!)
// 
//    Rev 1.17   20 Jun 1996 23:15:20   MARTIN
// 
//    Rev 1.16   17 Jun 1996 14:17:24   HANNES
// Einbau von BLOBS
// 
//    Rev 1.15   04 Mar 1996 21:15:16   GERHOLD
// pragma pack;   int -> short
// 
//    Rev 1.14   04 Feb 1996 17:53:28   HANNES
// 
//    Rev 1.13   02 Feb 1996 11:08:38   hannes
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   09 Jun 1995 00:32:54   HANNES
// VarElem::Property
// 
//    Rev 1.10   24 Feb 1995 11:16:38   HANNES
//  
// 
//    Rev 1.9   16 Feb 1995 13:02:08   HANNES
//  
// 
//    Rev 1.8   29 Jan 1995 11:47:04   HANNES
// 
//    Rev 1.7   24 Jan 1995 10:58:04   HANNES
// Schluesseldefinition in das Clientdictionary mit aufgenommen
// 
//    Rev 1.6   20 Jan 1995 15:49:38   HANNES
// Erweiterung des Clientdictionarys
// 
//    Rev 1.5   10 Jan 1995 14:58:40   HANNES
// Filename mit abgespeichert
// 
//    Rev 1.4   09 Jan 1995 12:11:50   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   05 Aug 1994 19:55:00   HANNES
// VAR_TIME
// 
//    Rev 1.2   17 Jul 1994 14:35:06   HANNES
// Umorganisieren der Primaerschluesselverwaltung
// 
//    Rev 1.1   04 Jul 1994 14:47:10   HANNES
// IsViewAllowed
// 
//    Rev 1.0   24 Jun 1994 17:02:06   HANNES
// Neuuebernahme clinicum
//

#define HUGE _huge
#pragma pack (1)
union _ref {
  DWORD  offs;
  LPVOID ptr;
  };
#ifndef TABLEREF_DEFINED
struct FAR TableRef {
  WORD Version;
  WORD TableNr;
  };
#define TABLEREF_DEFINED
#endif

// Marille Datentypen
#define VAR_POINT               3
#define VAR_CONT                4
#define VAR_STRARR              5
#define VAR_FLAG                6
#define VAR_SCALE               7
#define VAR_DATE                9
#define VAR_DWORD               12
#define VAR_OBJ                 13
#define VAR_TIME                15

#define MAX_FOREIGNSEGS         4
#define MAX_PRIMARYSEGS         4

#define DBMAXVERSION            0x7FFE

struct FAR ReqElem {
  short TableNumber;      // Index in dem Array TableDef
  WORD VarID;           // Variable, die gefragt wird
  };
typedef ReqElem FAR *LPREQELEM;

#define VPROP_DYNAMIC   0
#define VPROP_STATIC    1
#define VPROP_INDEXED   2
#define VPROP_NOTNULL   4
#define VPROP_CASEINSENSITIVE   8
#define VPROP_LINDEXED          16
#define VPROP_INDEXNUM  0xE0      // Die obersten 3 Bit werden zur Indexnummernvergabe 
                                  // verwendet -> max. 7 segmentierte Indizess
                                  // Indexnummer 0 bedeutet keinen segmentierten Index
inline int IndexNummer(BYTE prop)
  {
  return ((prop & VPROP_INDEXNUM) >> 5) ;
  }

struct FAR VarDef {
 public :
  DWORD structSize;
  WORD  DLLDataOffs;
  WORD  VarSize;            // Groesse der Variable
  BYTE  mType;              // Marille - Typ
  BYTE  Property;           // Eigenschaften der Variable
  WORD  VarID;              // Falls es sich um eine geblockte Variable handelt
  char  name[1];            // Name des Feldes


  int StructSize ()
    { return int (structSize) ; }
  void Initialize () { }

  LPSTR  GetName() { return name ; }
  LPVOID GetDLLData () { return LPSTR(this) + DLLDataOffs ; }

  friend struct TableDef;
  friend VarDef FAR *GetNewVar (LPSTR Name,LPVOID DLLDefData,DWORD DefDataSize);
  };
typedef struct VarDef FAR *LPVARDEF ;
#define CLKD_AUTOINC    0x00000001
#define CLKD_UNIQUE     0x00000002
#define CLKD_NULL       0x00000004
#define CLKD_MODIFYABLE 0x00000008
#define CLKD_CLUSTERED  0x00000010

struct FAR ClientKeyDef {
  DWORD structSize;
  WORD  KeyNmbr;
  WORD  VarID;
  DWORD Attribute;    // siehe CLKD_...
  char  name[1];
  };
typedef struct ClientKeyDef FAR *LPCLKEYDEF ;

#define CLKR_STANDARD   1
#define CLKR_EXTENDED   2
#define CLJR_RIEXTENDED 3
#define CLJR_RISTANDARD 4
#define CLJR_NEW        5

#define CLJT_USEDEFAULT   0
#define CLJT_USEOUTERJOIN 1
#define CLJT_USEINNERJOIN 2

struct FAR JoinDef {
  WORD VarID[1];
  };
struct FAR StandardRI {
  WORD VarID;
  char ForeignField[1];
  StandardRI FAR *GetNextSRI()
    { return (StandardRI FAR *) (LPSTR(this + 1) + lstrlen(ForeignField)) ; }
  };
struct FAR ExtendedRI {
  char AccessName[1];
  // dahinter AnzSegs x VarID;
  WORD FAR *GetVarIDList()
    { return (WORD FAR *) (LPSTR(this + 1) + lstrlen(AccessName)) ; }
  };
struct FAR ClientRIDef {
  DWORD structSize;
  BYTE  Type;       // siehe CLKR_..., CLJR_...
  BYTE  TypeOfJoin; // siehe CLJR_...
  WORD  AnzSegs;    // Anzahl Segmente des Foreign - Schluessels
  char  name[1];    // Name der Fremdtabelle
                    // dahinter: case CLKR_STANDARD : struct AnzSegs x StandardRI
                    //           case CLKR_EXTENDED : struct ExtendedRi
  ExtendedRI FAR *GetERI()
    { return (ExtendedRI FAR *) (LPSTR (this + 1) + lstrlen(name)); }
  StandardRI FAR *GetSRI()
    { return (StandardRI FAR *) (LPSTR (this + 1) + lstrlen(name)); }
  JoinDef FAR *GetJDef()
    { return (JoinDef FAR *) (LPSTR (this + 1) + lstrlen(name)); }
  int GetVarsforRI(WORD FAR *rivars);
  };
typedef struct ClientRIDef FAR *LPCLRIDEF ;


// 
// Aufbau einer internen Tabelle:
// Der Inhalt folgender Struktur wird statt den DLL Daten unter dem
// DLL Namen GetInternDLLName() abgespeichert
//
inline LPSTR GetInternDLLName() { return "_intern" ; }
struct FAR TableDef;
typedef TableDef FAR *LPTABLEDEF ;
struct FAR partTable {
  TableRef tRef;    // Referenz der Tabelle, die an dem join beteiligt ist
  LPTABLEDEF td;    // Nur temporaer genuetzt
  short doLock;     // Soll die Teiltabelle gelockt werden
  WORD AnzVars;     // Anzahl Variablen, die rausgeklaubt werden sollen
  WORD VarID[1];    // Variablen der Reihe nach
  };
typedef partTable FAR *LPPTABLE;
union _reft {
  DWORD Offs;
  LPPTABLE ptr;
  };

struct FAR InternTable {
  WORD AnzTables;       // Wieviel Tabellen sind gespeichert
  _reft pTable[1];      // Beschreibung der Teil - Tabellen

  LPPTABLE GetTableByNum(WORD i,BOOL forCompiler = FALSE)
    { return ((forCompiler) ? pTable[i].ptr : LPPTABLE(LPSTR(this) + pTable[i].Offs)); }
  DLLExport BOOL _export WINAPI IsTableReferenced (LPSTR TableName);
  DLLExport BOOL _export WINAPI AddVar (LPSTR VarName,WORD DataType);
  DLLExport void _export WINAPI GetReqElem (LPREQELEM e,WORD VarID);
  BOOL GetPartLock (WORD i)
    { return (LPPTABLE(LPSTR(this) + pTable[i].Offs))->doLock; }
  };
typedef InternTable FAR *LPINTTABLE;
DLLExport int _export WINAPI AddTablePart (LPINTTABLE FAR *tbl,LPSTR TableName,BOOL checkOrder,BOOL doLock);
DLLExport void _export WINAPI CreateEmptyInternTable (LPINTTABLE FAR *tbl);
DLLExport LPINTTABLE _export WINAPI Pack (LPINTTABLE t,GLOBALHANDLE FAR *hGres,DWORD FAR *gSize);
DLLExport void _export WINAPI Clear (LPINTTABLE t);

#define ATP_SUCCESS                 0
#define ATP_TABLENOTFOUND           1
#define ATP_ORDER                   2
#define ATV_SUCCESS                 0
#define ATV_VARNOTFOUND             1
#define ATV_DATATYPE                2

//
// Funktionen um einen DLL - Eintrag fuer die interne Tabelle zu realisieren
//
struct InternVarCoding {
  WORD mType;
  short IsPrimary;
  };
typedef InternVarCoding FAR *LPINTVARDESC;
DLLExport LPVOID _export WINAPI Intern_DATADICT_TABLEDEF (LPVOID InitData,LPSTR TableString,BOOL FAR *error,DWORD FAR *size);
DLLExport void _export WINAPI Intern_DATADICT_FREETABLEDEF (LPVOID TableData);
DLLExport LPVOID _export WINAPI Intern_DATADICT_VARDEF (LPVOID InitData,WORD mType,LPVOID TableData,LPSTR VarString,BOOL FAR *error,DWORD FAR *size);
DLLExport void _export WINAPI Intern_DATADICT_FREEVARDEF (LPVOID VarData);
DLLExport WORD _export WINAPI Intern_DATADICT_GETMTYPE (LPVOID VarData);
DLLExport LPACCESSLISTENTRY _export WINAPI Intern_DATADICT_GETACCESSLIST (LPVOID TableData);
DLLExport void _export WINAPI Intern_GETVARDESCEXTRA (LPVOID VarData,LPSTR txt,WORD txtSize);
DLLExport BOOL _export WINAPI Intern_ISPRIMARY (LPVOID VarData);
DLLExport BOOL _export WINAPI Intern_DATADICT_ISACCESSFORVIEW (LPVOID TableData,LPSTR AccessName);
DLLExport BOOL _export WINAPI Intern_DATADICT_GETVARPROPERTY (LPVOID TableData,LPVOID VarData,WORD PropCmd,LPVOID PropData);

DLLExport void _export WINAPI Intern_DBRESET ();
DLLExport int _export WINAPI Intern_DBCALL (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
#define TEMPORARYTBIDMIN 0x7000
#define TEMPORARYTBIDMAX 0x7EFF
#define RESOURCEIDMIN  0x7F00
#define RESOURCEIDMAX  0x7FFF
#define INTERNTBIDMIN  0x6000
#define INTERNTBIDMAX  0x6FFF
#define GLOBALTBIDMIN  0x5000
#define GLOBALTBIDMAX  0x5FFF

//
// Aufbau von TableDef:
//    - Header
//    - DLL - Definition
//    - Zeiger auf Schluesseldefinition
//    - Liste von Zeigern auf die Spaltendefinitionen (wobei die Startadresse
//      durch 4 teilbar sein muss -> hugearithmetik)
//    - Spaltendefinitionen werden durch einzelne Zeiger implementiert
//    - Liste von Zeigern auf Schluesseldefinitionen
//
typedef BOOL (WINAPI * CHECKKEYALLOWED) (WORD TableID,WORD VarID,LPVOID h);
struct RVarDef {
  LPSTR Name ;
  WORD VarSize ;
  BYTE mType ;
  BYTE Property;
  };
struct RKeyDef {
  LPSTR Name;
  short AnzSegs;
  DWORD Attrib;
  LPSTR FAR *KeySeg;
  };
struct FAR TableDef {
 private :
  union {
    GLOBALHANDLE hGmem;
    DWORD _res;
    } g;
  short AnzVars;
  TableRef tRef;
  _ref  Name;
  _ref  File;
  TableRef tRefParent;

  void  IncAnzVars () { AnzVars ++ ; }

  DLLHANDLE UsedDLL;

  union {                               
    _ref  DLLDef;
    GLOBALHANDLE hGDLLmem;    // Nur temporaer beim Zusammensammeln der
                              // Daten verwendet
    } d;
  DWORD DLLDefSize;
  short AnzKeySegs;
  short AnzRIDefs;
  _ref  VarTable;
  _ref  KeyTable;
  _ref  RITable;

  // Hilfsfunktionen
  void           SetTableID       (WORD  id,WORD Version) { tRef.TableNr = id ; tRef.Version = Version ; }
  void           SetName          (LPSTR Name);
  void           SetFileName      (LPSTR FileName);
  TableDef FAR * PushVar (WORD RowNumber,LPVARDEF var);

  WORD GetVarInd(LPSTR Name);
  int GetKeySegs (int KeyNum,WORD FAR *VarID);
 public :
  // Funktionen, die nach aussen sichtbar sind
  int      GetAnzVars()      { return AnzVars ; }
  WORD     GetTableID()      { return tRef.TableNr ; }
  WORD     GetVersion()      { return tRef.Version ; }
  WORD     GetParentID()     { return tRefParent.TableNr ; }
  WORD     GetParentVersion(){ return tRefParent.Version ; }
  void     SetParent (WORD pID,WORD v) { tRefParent.TableNr = pID ; tRefParent.Version = v ; }
  LPSTR     GetName   ()      { return LPSTR(Name.ptr) ; }
  LPSTR     GetFileName ()    { return LPSTR(File.ptr) ; }
  LPVOID    GetDLLDef ()      { return d.DLLDef.ptr ; }
  LPVARDEF  GetVarDef (int i) { return ((LPVARDEF HUGE *) VarTable.ptr)[i] ; }
  void      SetVarDef (LPVARDEF v,int i) { ((LPVARDEF HUGE *) VarTable.ptr)[i] = v; }
  DLLHANDLE GetDLLHandle ()   { return UsedDLL ; }
  void      SetDLLHandle (DLLHANDLE d)   { UsedDLL = d ; }
  
  LPACCESSLISTENTRY GetAccessList () 
    { return GetDLLAdmin()->GetDLLEntry(UsedDLL)->DataDict_GetAccessList(GetDLLDef()) ; }
  DLLExport WORD _export WINAPI GetVarID (LPSTR VarName,WORD FAR *DataType,BOOL FAR *found);
  DLLExport int _export WINAPI GetTableProperty (LPSTR Name,LPSTR Buffer,int Size);

  BOOL IsInternTable ()
    { return ((tRef.TableNr >= INTERNTBIDMIN) && (tRef.TableNr <= INTERNTBIDMAX)); }
  BOOL IsGlobalTable ()
    { return ((tRef.TableNr >= GLOBALTBIDMIN) && (tRef.TableNr <= GLOBALTBIDMAX)); }
  BOOL IsTemporaryTable ()
    { return ((tRef.TableNr >= TEMPORARYTBIDMIN) && (tRef.TableNr <= TEMPORARYTBIDMAX)); }
  BOOL IsRealTable ()
    { return (tRef.TableNr < GLOBALTBIDMIN); }
  BOOL IsResourceTable ()
    { return ((tRef.TableNr >= RESOURCEIDMIN) && (tRef.TableNr <= RESOURCEIDMAX)); }
  DLLExport void _export WINAPI GetReqElem (LPREQELEM e,WORD VarID);

  BOOL IsForeignKey (int VarNr,LPSTR TableName,int TableNameSize,LPSTR AccessName,int AccessNameSize,LPSTR DelName,int DelNameSize,LPSEGNAMEPTRS keysegs)
    { return GetDLLAdmin()->GetDLLEntry(GetDLLHandle())->
             DataDict_IsForeignKey (GetVarDef(VarNr)->GetDLLData(),
                          TableName,TableNameSize,
                          AccessName,AccessNameSize,
                          DelName,DelNameSize,
                          keysegs
                                   ) ;
    }

  BOOL IsPrimaryKey (int VarNr)
    { return GetDLLAdmin()->GetDLLEntry(GetDLLHandle())->
             DataDict_IsPrimary (GetVarDef(VarNr)->GetDLLData()) ; }

  GLOBALHANDLE GetHandle()
    {
    return g.hGmem ;
    }

  DLLExport BOOL _export WINAPI HasForeignKeysFor (LPTABLEDEF td,WORD FAR *VarID,
                CHECKKEYALLOWED ckafnc,LPVOID data,LPSTR AccessName,LPSTR DelName = NULL);
  DLLExport BOOL _export WINAPI IsViewAllowed (LPSTR AccessName);
  DLLExport BOOL _export WINAPI GetPrimKeySegs (WORD FAR *VarID);
  int GetAnzKeySegs () { return AnzKeySegs ; }
  LPCLKEYDEF GetKeyDef (int i) { return ((LPCLKEYDEF HUGE *) KeyTable.ptr)[i] ; }
  int GetAnzRIDefs () { return AnzRIDefs ; }
  LPCLRIDEF  GetRIDef (int i) { return ((LPCLRIDEF HUGE *) RITable.ptr)[i] ; }

  // Fuer die Exportierung der DLL
  DLLExport void _export WINAPI SetDLLDef (LPVOID data,DWORD Size);
  DLLExport void _export WINAPI Clear();
  DLLExport LPTABLEDEF _export WINAPI AddVar (LPVARDEF v);
  DLLExport void _export WINAPI AddKey (LPCLKEYDEF k);
  DLLExport void _export WINAPI AddForeign (LPCLRIDEF r);
  DLLExport void _export WINAPI InitializeTableID (WORD idmin,WORD idmax,WORD Version);
  DLLExport BOOL _export WINAPI HoldBlobs ();

  // Hilfsfunktionen
  friend TableDef FAR *TableDef_New (LPSTR Name,LPSTR FileName,WORD TableId,WORD Version,LPVOID DLLData,DWORD Size);
  friend TableDef FAR *TableDef_PushVar (WORD RowNumber,TableDef FAR *table,LPVARDEF var);
  friend TableDef FAR *TableDef_Pack (TableDef FAR *table,DWORD FAR *GesSize);
  friend DLLExport TableDef FAR * _export WINAPI TableDef_NewPack (TableDef FAR *table,DWORD FAR *GesSize);
  friend DLLExport void _export WINAPI FreeTableDef (TableDef FAR *res);
  friend DLLExport TableDef FAR * _export WINAPI InitializeTable (GLOBALHANDLE hGmem);

  friend DLLExport LPTABLEDEF _export WINAPI GetEmptyTable (LPSTR Name,LPSTR FileName);
  friend void PushPartTable ();
  friend void PushToVarList (LPSTR VarName,LPSTR Alias);
  friend LPCLRIDEF GetRIFor (LPSTR TableName,int FAR *TableNum,TableRef FAR *tr);
  friend int GetVarIDSFor (LPCLRIDEF ri,int TableNum,WORD FAR *varIDs);
  friend void PushJoin (WORD FAR *varIDs,int AnzVars,BYTE riType,BYTE riJoinType,LPSTR command);

  friend class TableAdmin;
  friend DLLExport LPTABLEDEF _export WINAPI DefineSQLDB (LPSTR TableName,
                          RVarDef FAR *vDef,int AnzVars,
                          RKeyDef FAR *kDef,int AnzKeys,
                          DLLHANDLE ResDLL,BOOL doAdmin = TRUE
                                );
  friend DLLExport void _export WINAPI SaveOldVersion (short type,WORD TableID,LPSTR Name,WORD oldVersion);
  friend class mdiChild;
  friend DLLExport WORD GetTableDefFromID (DWORD Id,WORD AnzVars,BYTE FAR *mType);
  };

// Laden der Definition von der Datenbank
DLLExport TableDef FAR * _export WINAPI InitializeTable (GLOBALHANDLE hGmem);

TableDef FAR * TableDef_New (LPSTR Name,WORD TableId,LPVOID DLLData,DWORD Size);
TableDef FAR * TableDef_PushVar (WORD RowNumber,LPTABLEDEF table,LPVARDEF var);
TableDef FAR * TableDef_Pack (TableDef FAR *table,DWORD FAR *GesSize);
DLLExport void _export WINAPI FreeTableDef (TableDef FAR *res);

/*------< Klasse TableAdmin: Verwaltung aller Tabellendefinitionen >----*/
struct FAR ContEntry {
  WORD Len;
  TableRef tRef;
  TableRef ParentRef;
  char TableName[1];
  ContEntry FAR *Next (LPVOID Base,DWORD ContSize);
  };
typedef ContEntry FAR *LPCONTENTRY;

struct FAR DataDictCont {
 private :
  DWORD ContSize;
  WORD AnzTables;
  ContEntry ent0;

  friend GLOBALHANDLE PushEntry (GLOBALHANDLE hGold,WORD TableID,WORD Version,WORD ParentID,WORD ParentVersion,LPSTR TableName);
  friend BOOL FindEntry (GLOBALHANDLE hGold,WORD TableID,WORD Version,LPSTR TableName);
  friend DLLExport void _export WINAPI CreateDataDictContent ();

  friend class TableAdmin;
 public :
  DLLExport LPCONTENTRY _export WINAPI First ();
  DLLExport LPCONTENTRY _export WINAPI Next (LPCONTENTRY prev);
  };
typedef DataDictCont FAR *LPDDCONT;
#pragma pack ()

DLLExport void _export WINAPI CreateDataDictContent ();

struct FAR TableNode {
  TableNode FAR *Next;
  TableRef tRef;
  WORD Count;
  LPTABLEDEF def;
  };
typedef TableNode FAR *LPTABLENODE;

struct AccessListEntry {
  AccessListEntry FAR *Next;
  LPSTR Name;
  LPSTR Description;
  };
typedef AccessListEntry FAR *LPACCESSLISTENTRY;

struct FAR TableEntry {
  TableEntry FAR *Next;
  LPTABLEDEF td;
  WORD SelCount;
  };

void DefineResourceDBs();
DLLExport WORD _export WINAPI GetVersionFrom (LPSTR Name);
class FAR TableAdmin {
 private :
  WORD MaxTables;
  GLOBALHANDLE hGContMem;   // Speicher des Inhaltsverzeichnisses
  LPDDCONT     Content;

  void LoadDataDictContent ();

  TableNode FAR *TableList;
  TableNode FAR *Find (WORD TableId,WORD Version);
  WORD GetTableCount ();
  void CleanUnused ();
  void GetDLLFor (LPSTR DLLName,WORD TableID);
 public :
  LPDDCONT     GetContent()
    { return Content ; }

  DLLExport void _export WINAPI Initialize (BOOL doTest = FALSE);
  DLLExport void _export WINAPI OnExit ();
  DLLExport void _export WINAPI ReInitialize ();
  DLLExport BOOL _export WINAPI CheckDataDictContent (LPSTR Name,WORD Id,WORD Version,WORD ParentID,WORD ParentVersion);
  DLLExport BOOL _export WINAPI DelTableDef (LPSTR Name);

  DLLExport WORD _export WINAPI GetTableID (LPSTR ScriptPrefix,LPSTR TableName,BOOL FAR *found,WORD FAR *Version);

  DLLExport LPTABLEDEF _export WINAPI GetTableDef (WORD TableID,WORD Version);
  DLLExport void _export WINAPI FreeTable (WORD TableID,WORD Version);

  DLLExport LPTABLEDEF _export WINAPI GetTableDefByNr (int Nr);

  DLLExport LPTABLEDEF _export WINAPI GetFirstTableDef (LPVOID FAR *h);
  DLLExport LPTABLEDEF _export WINAPI GetNextTableDef (LPVOID FAR *h);

  DLLExport TableEntry FAR *_export WINAPI CreateTableList ();
  DLLExport void _export WINAPI DestroyTableList (TableEntry FAR *aList);
  LPDDCONT GetDDContent()
    { return Content ; }

  WORD GetTemporaryID (WORD IdMin);
  WORD GetTemporaryID ();
  void CleanTableNode (WORD TableID,WORD Version);
  DLLExport LPTABLEDEF _export WINAPI GetTemporaryTable (int AnzFields,LPSTR FAR *FieldNames,int AnzTables,LPSTR FAR *TableNames);
  DLLExport void _export WINAPI FreeTemporaryTable (WORD TableID);

  void AddTableDef (LPTABLEDEF res,DLLHANDLE hDLL);
  int GetAnzTables ();

  friend DLLExport void _export WINAPI DBTest (BOOL doCreate);
  friend DLLExport WORD GetTableDefFromID (DWORD Id,WORD AnzVars,BYTE FAR *mType);
  };

typedef TableAdmin FAR *LPTABLEADMIN;

#define REP_MAXSUBNODES 32
#pragma pack(1)
#define UPDATEMODE_INSERT     0
#define UPDATEMODE_UPDATE     1
#define UPDATEMODE_DELETE     2
struct FAR RepNode {
  TableRef tRef;         // Tabelle, die mit Aufgenommen werden muss
  WORD  updateModeIndex; // Modus, fuer den der Knoten gilt
  WORD  pForeignVar;     // Fremdfeldnummer im Vatersatz
  WORD  pForeignVar1;    // Fremdfeldnummer im Vatersatz
  WORD  Prio;
  LPSTR Selection;      // Zugriff fuer Sohnsatz
  short AnzSubNodes;    // Anzahl Subknoten
  RepNode FAR *rpSub[1];

  int Size()
    { return sizeof(*this) + sizeof(rpSub[0]) * (AnzSubNodes - 1) ; }
  BOOL PushSubNode (RepNode FAR *r)
    {
    if (AnzSubNodes < REP_MAXSUBNODES) {
      rpSub[AnzSubNodes++] = r ;
      return TRUE ;
      }
    else
      return FALSE ;
    }
  BOOL checkUpdateMode (DBINT um)
    {
    if (um == UPDATEMODE_DELETE) return (updateModeIndex == 1);
    else                         return (updateModeIndex == 0);
    }
  };
#pragma pack()
typedef RepNode FAR *LPREPNODE;
// Aufbau der Replikatordaten auf der Datei (Table = DataDict,TableID = 0,Type = 2):
// short AnzRepNodes;
// AnzRepNodes x LPREPNODE ...
//    Auf der Datei sind alle Zeiger relativ angegeben -> 
//    Beim Laden muss eine Relokation vorgonommen werden
//
#define MAXREPSIZE (sizeof(RepNode) + sizeof(RepNode FAR *) * (REP_MAXSUBNODES - 1))

extern DLLExport DLLHANDLE _export WINAPI GetTransactionDLL ();

DLLExport LPTABLEADMIN _export WINAPI GetTableAdmin ();
DLLExport LPSTR _export WINAPI GetMTypeName(WORD Type);
DLLExport LPSTR _export WINAPI GetRealMTypeName(WORD Type);
DLLExport void _export WINAPI GetDLLForTable (LPSTR DLLName,LPSTR TableName);
DLLExport void _export WINAPI ConnectToSQL (LPTABLEDEF t,DLLHANDLE actdll,LPSTR FName);

DLLExport GLOBALHANDLE _export WINAPI ReadScriptData (short type,LPSTR fName,DWORD FAR *DataSize);
DLLExport void _export WINAPI WriteScriptData (short type,LPSTR fName,GLOBALHANDLE hGmem,DWORD DataSize);
class FAR DBList ;
DLLExport DBList FAR *_export WINAPI GetAllScriptData (short type);

DLLExport GLOBALHANDLE _export WINAPI ReadResourceData (DWORD Id,DWORD FAR *DataSize);
DLLExport GLOBALHANDLE _export WINAPI ReadResourceData (short type,LPSTR fName,DWORD FAR *DataSize);
DLLExport void _export WINAPI WriteResourceData (short type,LPSTR fName,GLOBALHANDLE hGres,DWORD DataSize);
DLLExport DBList FAR *_export WINAPI GetAllResourceData (short type);

DLLExport DBList FAR *_export WINAPI GetAllDataDict (short type);
DLLExport void _export WINAPI WriteDataDict (short type,LPSTR Name,short TableID,short Version,short ParentID,short ParentVersion,GLOBALHANDLE hGres,DWORD DataSize);
DLLExport GLOBALHANDLE _export WINAPI ReadDataDict (short type,WORD TableID,WORD Version,DWORD FAR *DataSize);
DLLExport void _export WINAPI DelDataDict (short type,WORD TableID,WORD Version);
DLLExport WORD _export WINAPI ReadTableID (short type,LPSTR Name,WORD idmin,WORD idmax);
DLLExport WORD _export WINAPI ReadMaxVersion (short type,WORD TableID);
DLLExport void _export WINAPI DBConvert (LPSTR ConvertTo);
DLLExport DBList FAR *_export WINAPI GetDBVersionList ();

DLLExport BOOL _export WINAPI OwnCounter ();
DLLExport DWORD _export WINAPI GetCounterValue (LPTABLEDEF t);

void DefineRepDBs (DLLHANDLE ResDLL);
void LoadTableIdents (BOOL doCreate);

#define FIRSTVERSION 1
DLLExport short _export WINAPI GetDBVersion(LPSTR TableName);
DLLExport void _export WINAPI SetDBVersion(LPSTR TableName,short Version);

DLLExport BOOL _export WINAPI EntwicklungsUmgebung ();
DLLExport void _export WINAPI GetPrefix (LPSTR res,LPSTR name);
DLLExport DBList FAR *_export WINAPI GetAllTempDataDict ();

DLLExport void _export WINAPI UpdateIntermediate ();

