///////////////////////////////////////////////////////////
//  Definition des Compilates einer Tabellenbescreibung
///////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/tbbtrv.hpv   1.9   17 Jun 1996 14:17:20   HANNES  $
//  $Log:   P:/marille/clinicum/include/rev/tbbtrv.hpv  $
// 
//    Rev 1.9   17 Jun 1996 14:17:20   HANNES
// Einbau von BLOBS
// 
//    Rev 1.8   02 Feb 1996 10:59:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   08 May 1995 17:16:04   HANNES
// No change.
// 
//    Rev 1.6   16 Feb 1995 12:47:04   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.5   24 Jan 1995 10:59:10   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.4   19 Oct 1994 22:31:14   hannes
// 
//    Rev 1.3   05 Aug 1994 17:17:48   HANNES
// 
//    Rev 1.2   17 Jul 1994 14:40:04   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.1   04 Jul 1994 14:56:58   HANNES
// 
//    Rev 1.0   24 Jun 1994 17:01:28   HANNES
// Neuuebernahme clinicum
//
#pragma pack(1)
union PTR_OFFS {
  DWORD  offs;
  LPVOID ptr;
  };

// Maptypen
#define MAPTYPE_FIELD     0
#define MAPTYPE_KLBLOCKED 1
#define MAPTYPE_MBLOCKED  2
#define MAX_KEYSEGS       3
struct TbBtrv;
typedef TbBtrv FAR *LPBTRVTABLE;
union _extDesc {
  WORD dOffs;           // mapType == MAPTYPE_FIELD
  struct {              // mapType == MAPTYPE_KLBLOCKED
    WORD BlockID;       // BlockID
    WORD DataType;      // KL - Datentyp
    int  VarOffset;     // Offset im Block (kann auch negativ sein, fuer DT_SPRIVATE)
    WORD VarLen;        // Laenge der Variable
    } kl;
  struct {              // mapType == MAPTYPE_MBLOCKED
    WORD VarID;         // Marille - Varid (wird ebenfalls mit BlockID zugegriffen)
    } m;
  } ;
struct FAR _foreignDesc {
  WORD SegNames[MAX_KEYSEGS];
  char TableName[1];      // In Welche Tabelle ist das Datenelement
                          // ein Fremdschluessel.
                          // Hinter dem Namen steht der Zugriff, mit dem
                          // ein Get durchgefuehrt werden kann, dahinter der
                          // Zugriff fuer das Kaskadierende Loeschen
  LPSTR GetGetName()
    { return TableName+lstrlen(TableName)+1 ; }
  LPSTR GetDelName()
    { LPSTR g = GetGetName() ; return g+lstrlen(g)+1 ; }
  LPSTR GetTableName()
    { return TableName; }
  LPSTR GetKeySegName (LPSTR base,WORD i)
    { return (SegNames[i] != 0) ? base + SegNames[i] : NULL ; }
  };
typedef _foreignDesc FAR *LPFOREIGNDESC;
struct FAR VarDesc {
  WORD mType;             // Marille Datentyp
  WORD mapType;           // Typ des Mappings
  WORD foreignOffs;       // Relativzeiger fuer die Foreignbeschreibung
  short primaryKey;
  _extDesc b;

  LPVOID Extract(LPBTRVTABLE t,LPVOID dataBuffer,unsigned bufferSize,WORD FAR *rSize,LPVOID FAR *hData=NULL);
  LPVOID Extract_extended(LPBTRVTABLE t,LPVOID dataBuffer,unsigned bufferSize,WORD FAR *rSize);
  void SetData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID data,LPVOID FAR *hData);
  void SetNULLData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID FAR *hData);
  BOOL IsForeignKey ()
    { return (foreignOffs != 0) ; }
  BOOL IsPrimaryKey ()
    { return primaryKey ; }
  LPFOREIGNDESC GetForeignDesc() 
    { return LPFOREIGNDESC (LPSTR(this) + foreignOffs) ; }
  BOOL IsReducedAllowed ()
    { return (mapType == MAPTYPE_FIELD); }
  };
typedef VarDesc FAR *LPDDSVARDESC;
void FreeHData (LPVOID hData);
void SetHData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID hData);

// Btrieve - Datentypen
/////////////////////////////
#define BDT_STRING    0
#define BDT_INTEGER   1
#define BDT_FLOAT     2
#define BDT_DATE      3
#define BDT_TIME      4
#define BDT_DECIMAL   5
#define BDT_MONEY     6
#define BDT_LOGICAL   7
#define BDT_NUMERIC   8
#define BDT_BFLOAT    9
#define BDT_LSTRING   10
#define BDT_ZSTRING   11
#define BDT_UNSIGNED  14
#define BDT_AUTOINC   15

// Zusaetzliche Datenbanktypen
#define DT_PRIVATE    20
#define DT_LDSTRING   21
#define DT_KLDATE     22
#define DT_SPRIVATE   23

// Flags in der Recordbeschreibung
#define FA_ALLOC_TEN     64
#define FA_VARIABLE      1
#define FAB_VARIABLE     0
#define FA_COMPRESS      8
#define FAB_COMPRESS     3

// Flags in der Keybeschreibung
#define KAB_DUPLICATE    0
#define KA_DUPLICATE     1
#define KAB_MODIFIABLE   1
#define KA_MODIFIABLE    2
#define KAB_NULL         3
#define KA_NULL          8
#define KAB_SEGMENTED    4
#define KA_SEGMENTED     16
#define KAB_ALT          5
#define KAB_MANUAL       9
#define KA_MANUAL        512
#define KA_EXTENDED      256
#define KA_ALT           32

#ifdef STRICT_TEST
#define KA_TESTFLAGS     (1 | 2 | 16 | 32 | 256 | 512)
#else
#define KA_TESTFLAGS     (1 | 2 | 16 | 256 | 512)
#endif

struct FAR KeyDesc {
  WORD  position;
  WORD  length;
  WORD  flag;
  DWORD res1;
  BYTE  extType;
  BYTE  nullVal;
  DWORD res2;
  };

#define ALTSIZE   265
struct FAR RecDesc {
  WORD  StructSize;      // Gesamtgroesse der Struktur
  WORD  AnzKeySegs;      // Anzahl KeySegmente
  /*----< Buffer fuer Btrieve >----*/
  WORD  RecordLength;    // Recordgroesse
  WORD  PageSize;
  WORD  NumKeys;
  DWORD res1;
  WORD  flags;          // FA_...
  WORD  res2;
  WORD  allocation;
  KeyDesc k[1];
  void SetRecordSize (WORD rSize) { RecordLength = rSize ; }
  void SetPageSize (WORD rSize)   { PageSize     = rSize ; }
  };
typedef RecDesc FAR *LPRECDESC ;

struct FAR VBtrv {
  WORD EntryLen;
  WORD DataType;
  WORD VarOffset;
  WORD VarLen;
  WORD Dimension;
  char Name[1];

  VBtrv FAR *Next (WORD gSize,LPVOID base);
  LPVOID Extract (LPVOID dataBuffer,WORD FAR *rSize);
  void SetData (LPVOID res,LPVOID data);
  void SetMinData (LPVOID res);
  void SetMaxData (LPVOID res);
  };
typedef VBtrv FAR *LPVBTRV;

struct FAR Vartbl {
  WORD gSize;
  union {
    GLOBALHANDLE hGres;
    DWORD _reserved;
    } g ;
  VBtrv v[1];
  };
typedef Vartbl FAR *LPVARTBL;

struct FAR AccessDef {
  PTR_OFFS next;
  WORD DescOffs;
  short ViewAllowed;
  char Name[1];
  LPSTR GetDescription()
    { return ((DescOffs) ? (LPSTR(this) + DescOffs) : LPSTR(NULL)); }
  };
typedef AccessDef FAR *LPACCESSDEF;
struct KeyDef {
  PTR_OFFS next;
  WORD KeyNmbr;
  WORD KeySize;
  char Name[1];
  // Hinter dem Namen steht die Struktur Vartbl (wobei hGres nicht verwendet
  // wird...)
  };
typedef KeyDef FAR *LPKEYDEF;

struct FilterHeader {
  BYTE btrDataType;
  WORD VarLen;
  WORD VarOffset;
  BYTE cmpCode;
  };
// Assignmentfunktionen
/////////////////////////
#define ER_KEYELEM      1
#define ER_DATAELEM     2
#define ER_CONSTSTRING  3
#define ER_CONSTINT     4
#define ER_OP           5
#define ER_PARAMETER    6
#define ER_RESULT       7
#define ER_FILTER       8
#define ER_CASCADE      9
#define ER_POP          10
#define ER_PUSH         11
class FAR BtrStatement;
struct FAR ElemRef {
  WORD Type;    // ER_..
  union {
    VBtrv v;          // case ER_KEYELEM, ER_DATAELEM
    char  str[1];     // case ER_CONSTSTRING
    DWORD iVal;       // case ER_CONSTINT
    WORD  op;         // case ER_OP
    WORD  parNum;     // case ER_PARAMETER
    WORD  ResColomn;  // case ER_RESULT
    } x;
  ElemRef FAR *Next();
  void DoIt (BtrStatement FAR *stmt);
  void SetRes (BtrStatement FAR *stmt);
  };

#define BLOCKTYPE_MARILLE1  3
#define BLOCKTYPE_KL        2
#define BLOCKTYPE_MARILLE   1
#define BLOCKTYPE_NONE      0
struct KLBlockDesc {
  WORD lOffset;         // Offset der Laengenbeschreibung
  WORD AnzChars;        // 1 oder 2 Byte
  short LengthMustExist; // Ist Laengenwort im Fixen teil?
  };

struct FAR TbBtrv {
  DWORD    StructSize;      // Groesse des gesamtblockes (wenn gepackt)
  union {
    HGLOBAL  hGmem;           // Wird nur gebraucht, um Daten nach dem Speichern
                              // wieder freizugeben
    DWORD _reserved;
    } g ;
  WORD BlockType;           // BLOCKTYPE_...
  KLBlockDesc bdsc;         // und die beschreibung dazu
 private :
  PTR_OFFS FileRef;         // Referenz auf den Filenamen
  PTR_OFFS DescRef;         // Referenz auf die Beschreibung
  PTR_OFFS VartblRef;       // Referenz auf die Variablen
  PTR_OFFS KeyRef;          // Schluesselbeschreibung
  PTR_OFFS AccessRef;       // Referenz auf die Liste mit den Selektionen

  void SetVarRef (LPVARTBL h)
    { VartblRef.ptr = h ; }
 public :

  /*------< Kompiler >-------*/
  inline void SetFileRef (LPSTR Name);
  void PushVar (LPSTR Name,WORD DataType,WORD VarOffs,WORD VarLen,WORD Dimension);

  /*------< Zugriff auf die einzelnen Komponenten >------*/
  LPSTR GetFileRef (BOOL forCompiler = FALSE) 
    { return LPSTR ((forCompiler) ? FileRef.ptr : LPSTR(this) + FileRef.offs) ; }
  LPVARTBL GetVarRef (BOOL forCompiler = FALSE)
    { return LPVARTBL ((forCompiler) ? VartblRef.ptr : LPSTR(this) + VartblRef.offs) ; }
  LPVBTRV GetVar (LPSTR Name,BOOL forCompiler = TRUE);
  LPRECDESC GetDescRef (BOOL forCompiler = FALSE)
    { return LPRECDESC ((forCompiler) ? DescRef.ptr : LPSTR(this) + DescRef.offs) ; }
  void InitialiseDesc ();
  void AddKeySegment ();
  WORD LoadAltSeq (LPSTR Name);
  LPACCESSDEF GetAccess (LPSTR Name,BOOL forCompiler = FALSE);
  LPACCESSDEF GetFirstAccess (BOOL forCompiler = FALSE)
    { return LPACCESSDEF ((forCompiler) ? AccessRef.ptr : LPSTR(this) + AccessRef.offs) ; }
  LPACCESSDEF GetNextAccess (LPACCESSDEF a,BOOL forCompiler = FALSE)
    { if (a->next.offs == 0L) return NULL ; else return LPACCESSDEF ((forCompiler) ? a->next.ptr : LPSTR(this) + a->next.offs) ; }
  LPKEYDEF GetKey (LPSTR Name,BOOL forCompiler = FALSE,WORD FAR *Num = NULL);
  LPKEYDEF GetKey (WORD KeyNmbr,BOOL forCompiler = FALSE,LPSTR KeyName = NULL);
  LPVBTRV GetKeyVar (LPSTR Name,WORD KeyNmbr,BOOL forCompiler = FALSE);
  LPKEYDEF GetFirstKey (BOOL forCompiler = FALSE)
    { return LPKEYDEF ((forCompiler) ? KeyRef.ptr : ((KeyRef.offs != 0L) ? LPSTR(this) + KeyRef.offs : NULL)) ; }
  LPKEYDEF GetNextKey (LPKEYDEF a,BOOL forCompiler = FALSE)
    { if (a->next.offs == 0L) return NULL ; else return LPKEYDEF ((forCompiler) ? a->next.ptr : LPSTR(this) + a->next.offs) ; }

  /*------< Verwaltungsfunktionen >------*/
  void Clear ();
  TbBtrv FAR *Pack ();

  friend DLLExport void _export _SetPtrToRoot   () ;
  friend DLLExport void _export _SetFirstKey    () ;
  };
typedef TbBtrv FAR *LPBTRVTABLE;

// Beschreibung der Blockstruktur wie im Kliniksystem
////////////////////////////////////////////////////////
typedef LPWORD LPBTRVCOMMAND;

#define BCMP_NOTEQUAL       4
#define BCMP_LESSEQAUL      6
#define BCMP_LESS           3
#define BCMP_GREATEREQUAL   5
#define BCMP_GREATER        2
#define BCMP_EQUAL          1
#define BCMP_LIST           100

#define BOP_AND             1
#define BOP_OR              2
#define BOP_END             0
#pragma pack()

