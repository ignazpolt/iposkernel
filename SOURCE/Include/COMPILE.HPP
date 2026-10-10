/*-------------------------------------------------------------**
**                                                             **
**      Kleinen Compiler zur Generierung eine binaeren         **
**          Formates aus Textform mit mehr                     **
**            oder weniger freier Syntax                       **
**                                                             **
**-------------------------------------------------------------*/
// $Header:   P:/marille/clinicum/include/rev/compile.hpv   1.57   07 Jun 2000 11:51:18   Wolfgang  $
// $Log:   P:/marille/clinicum/include/rev/compile.hpv  $
// 
//    Rev 1.57   07 Jun 2000 11:51:18   Wolfgang
// 1.) FunctionPrototypes gibt int zurueck.
// 
//    Rev 1.56   09 May 2000 15:40:08   Wolfgang
// 1.) FncCompiler erlaubt immer Operatoren.
// 
//    Rev 1.55   16 Feb 2000 15:02:38   Wolfgang
// 1.) DOUBLEFUNCTION neu.
// 2.) lastoplist neu.
// 
//    Rev 1.54   03 Dec 1999 17:05:32   Wolfgang
// 1.) Neue Push_Pars0-Methoden.
// 2.) Neue Fehlermeldungen fuer neue FDEF-Syntax.
// 3.) Neue Komponente actParStatus in FncCompiler.
// 
//    Rev 1.53   29 Sep 1999 16:55:06   Wolfgang
// 1.) CYCLICIMPORT neu.
// 2.) Init-/DoneModuleHash neu.
// 
//    Rev 1.52   26 Apr 1999 18:09:34   Wolfgang
// 1.) Fehlermeldung ERRORINIMPORTED neu.
// 
//    Rev 1.51   26 Mar 1999 18:08:08   Wolfgang
// 1.) VirtualModule eingebaut.
// 2.) FTYPE_VIRTUAL neu.
// 
//    Rev 1.50   12 Mar 1999 14:40:54   Wolfgang
// 1.) IsCompileAborted neu.
// 
//    Rev 1.49   01 Mar 1999 13:17:02   Wolfgang
// 1.) WriteDebugInfo hat dritten Parameter.
// 
// 
//    Rev 1.48   26 Feb 1999 17:39:12   Wolfgang
// 1.) DEBUGFORMSENT neu.
// 2.) WriteDebugInfo hat zweiten Parameter.
// 3.) GetIncludeFileName liefert BOOL zurueck.
// 
//    Rev 1.47   23 Feb 1999 14:54:32   Hannes
// Neue Combo - Funktionen
// 
//    Rev 1.46   28 Jan 1999 12:20:46   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.45   14 Aug 1998 18:55:24   Hannes
// Include - Pfad und Source - Pfad vertauschen
// 
//    Rev 1.44   04 Aug 1998 17:48:24   Hannes
// Timestamp
// 
//    Rev 1.43   16 May 1998 18:36:08   Martin
// #ifndef WITHOUT_GETININAME ...
// 
//    Rev 1.42   16 May 1998 18:24:54   Hannes
// PAR_FREEVAR
// 
//    Rev 1.41   02 Feb 1998 20:31:44   Hannes
// BInWAllowed: Woerter durch eckige Klammern abgrenzen
// 
//    Rev 1.40   05 Jan 1998 07:48:18   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.39   19 Nov 1997 18:45:16   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.38   06 Nov 1997 19:25:14   Hannes
// 
//    Rev 1.37   22 Sep 1997 12:37:16   Hannes
// 
//    Rev 1.36   16 Sep 1997 17:10:00   Hannes
// Prototyp von BlobCompiler
// 
//    Rev 1.35   04 Sep 1997 20:12:34   Hannes
// No change.
// 
//    Rev 1.34   29 Aug 1997 16:53:00   gerhold
// BlobScriptCompiler::OpenInclude
// 
//    Rev 1.33   22 Aug 1997 12:02:10   Hannes
// 
//    Rev 1.32   08 Jul 1997 12:00:06   Hannes
// 
//    Rev 1.31   27 May 1997 11:17:06   Hannes
// Definition von Privaten Strukturen
// 
//    Rev 1.30   13 Mar 1997 19:01:38   Hannes
// DoCompileFromBlob
// 
//    Rev 1.29   28 Feb 1997 14:35:26   Hannes
// PrepareParse,ParseNow
// 
//    Rev 1.28   19 Feb 1997 12:00:58   Hannes
// Scriptfunktionen
// 
//    Rev 1.27   26 Nov 1996 08:07:46   HANNES
// Automatischer Update
// 
//    Rev 1.26   08 Nov 1996 13:29:26   HANNES
// QLong
// 
//    Rev 1.25   30 Oct 1996 08:42:26   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.24   21 Oct 1996 18:53:56   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.23   05 Jul 1996 08:10:56   gerhold
// #pragma pack(1)
// 
//    Rev 1.22   18 May 1996 20:59:28   HANNES
// VAR_BLOB
// 
//    Rev 1.21   04 Feb 1996 16:50:10   HANNES
// 
//    Rev 1.20   04 Feb 1996 15:45:18   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.19   02 Feb 1996 10:59:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.18   25 Sep 1995 20:48:48   HANNES
// 
//    Rev 1.17   14 Sep 1995 10:00:04   HANNES
// 
//    Rev 1.16   23 Aug 1995 11:06:40   GERHOLD
// 
//    Rev 1.15   02 Aug 1995 09:59:16   HANNES
// Prioritaetenhandling, verb. Fehlerabfrage, verb. Kapselung
// 
//    Rev 1.14   11 Jul 1995 12:36:30   HANNES
// Statische Daten des Compilers in die Klasse verlegt
// 
//    Rev 1.13   09 Jun 1995 00:31:06   HANNES
// Konstantenhandling
// 
//    Rev 1.12   15 May 1995 08:26:12   HANNES
// Propertys, structdefinition im Script
// 
//    Rev 1.11   24 Mar 1995 18:35:30   GERHOLD
// 
//    Rev 1.10   23 Mar 1995 11:51:36   GERHOLD
// 
//    Rev 1.9   20 Mar 1995 12:15:58   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.8   08 Mar 1995 09:15:36   HANNES
// Forschleifen u.a.
// 
//    Rev 1.7   24 Feb 1995 11:16:40   HANNES
//  
// 
//    Rev 1.6   16 Feb 1995 13:02:12   HANNES
//  
// 
//    Rev 1.5   09 Jan 1995 12:07:18   HANNES
// Debugger eingebaut
// 
//    Rev 1.4   05 Dec 1994 17:37:04   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.3   08 Nov 1994 12:43:06   HANNES
// PREFIX_ABORT
// 
//    Rev 1.2   05 Aug 1994 19:54:52   HANNES
// VAR_TIME
// 
//    Rev 1.1   07 Jul 1994 22:44:56   HANNES
// InterpreteCString
// 
//    Rev 1.0   24 Jun 1994 17:01:04   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.23   03 Apr 1994 18:57:58   HANNES
// pushData auf DWORD umgebaut
// 
//    Rev 1.22   09 Feb 1994 12:16:28   HANNES
// 
//    Rev 1.21   09 Feb 1994 12:09:50   HANNES
// Returnstatus bei DoCompile
// 
//    Rev 1.20   04 Feb 1994 16:51:34   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.19   11 Jan 1994 19:03:24   HANNES
// Fenster der Elternbox dem Compiler uebergeben
// 
//    Rev 1.18   07 Jan 1994 12:08:44   HANNES
// Includefile in der Wartebox angezeigt
// 
//    Rev 1.17   09 Dec 1993 15:04:14   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.16   29 Nov 1993 08:34:58   HANNES
// Bedingte Kompilierung
// 
//    Rev 1.15   20 Jul 1993 12:35:34   HANNES
// Neuen Compile - Header, Icons im Compiler
// 
//    Rev 1.14   05 Jul 1993 14:48:46   HANNES
// Einbau der Bitmaps, COMMONDATA
// 
//    Rev 1.13   10 Jun 1993 18:34:10   HANNES
// MYINI
// 
//    Rev 1.12   07 Jun 1993 15:12:50   HANNES
// Bufferhandling
// 
//    Rev 1.11   24 May 1993 14:26:48   HANNES
// Expressions
// 
//    Rev 1.10   02 Apr 1993 17:58:18   HANNES
// Beschleunigter Durchlauf
// 
//    Rev 1.9   17 Mar 1993 18:01:50   HANNES
// 32 bit Umstellung
// 
//    Rev 1.8   08 Mar 1993 14:16:36   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.7   02 Mar 1993 22:36:50   HANNES
// Verschiedene Verbesserungen im Zusammenhang mit dem Editor
// 
//    Rev 1.6   27 Feb 1993 17:47:18   HANNES
// Erweiterungen fuer Formulareditor
// (put durch MARTIN, da von HANNES vergessen)
// 
//    Rev 1.5   22 Feb 1993 17:20:24   HANNES
// Erweiterung des Kompilers auf Arrays
// 
//    Rev 1.4   08 Feb 1993 10:42:24   HANNES
// Umbau aller Files auf btrFiles
// 
//    Rev 1.3   18 Jan 1993 16:54:40   HANNES
// Neue Variablen - Typen: long, obj
// Im Header: Category
// 
//    Rev 1.2   13 Jan 1993 18:55:46   HANNES
// Veraenderung des Compile - Headers (mehrere Datensaetze fuer ein Dokument)
// 
//    Rev 1.1   06 Dec 1992 15:57:42   HANNES
// Buffergroesse des Compilers vergroessert
// 
//    Rev 1.0   02 Dec 1992 15:52:12   HANNES
// Initial revision.

/*----------------------------------------------------------------------------
**
**      Kurzbeschreibung der Eigenschaften des Parsers
**              - Preprozessor Kommandos: #include, #define
**              - Erlaubt include - Files (#include "name"), keine
**                              mehrfach - includes !!!!
**              - #define von Integer, Strings, und floats
**              - beim Parsen muss Integer und float unterscheidbar sein
**                   -> floats immer mit Dezimalpunkt
**              - Rekursive Definition der Syntax
**              - Parser verwaltet Hashtabelle mit Funktionsnamen
**                      (Aufgebaut muss sie aber im Codegenerator werden,
**                      dafuer werden mehrere Funktionen zur Verfuegung
**                      gestellt)
**              - Parser verwaltet Hashtabelle mit Variablennamen
**                      (Muessen ebenfalls im Codegenerator aufgebaut werden,
**                      Funktionen werden zur Verfuegung gestellt
**              - Kommentare beginnen $ und gehen bis zum Zeilenende
**                      (logischerweise nicht in strings !)
**              - Syntax ist nicht abhaengig von Zeilenposition
**              - Strings koennen ueber mehrere Zeilen gehen, Zeilenumbruch
**                wird dabei vollkommen ignoriert. Zeilenumbrueche oder 
**                andere Sonderzeichen werden mit der c - Syntax in strings
**                gebracht
**              - Es wird immer bis zum ersten Fehler kompiliert, nach dem
**                ersten Fehler (Syntaxfehler...) wird alles gestoppt
**      3.11.92:
**              - fuer lokale Daten muss kein Ident vergeben werden, das 
**                Programm vergibt ihn automatisch
**              - Fuer Konstanten wird hinten ein Block angelegt, sie muessen
**                nicht als Datenelement angelegt und initialisiert werden
**              - Implementierung von inline functions
**              
**--------------------------------------------------------------------------*/

/*-----< Header >------*/
#ifndef difftime
#include <time.h>
#endif

#ifndef HELPDATA
#define HELPDATA  0xFFFE
#endif
#define DYNLOCALDATA      3
#define STATICLOCALDATA   4

#ifdef UEBERLEGT
#define MAXDBNMBR     5
struct cmpl_head {
  time_t cmpltime;      // Zeit des Compilates
  char fullname[100];   // Voller Name des Dokumentes
  WORD type;            // Type des Dokumentes  // IDC_xx_BASE
  int AnzDBNmbr;        // Anzahl der Datentypen, die zur Auswahl
                        // stehen sollen
  char filename[40];    // Filename des Sourcefiles
  WORD Category;        // Kategorie des Dokumentes

  LONG ProgSize;        // Groesse des Gesamten Programmrecords
  WORD PrimRecSize;     // Groesse des 1. Datensatzes
  LONG ConstRecSize;    // Groesse des Konstanten - Records
  DWORD ExtHdSize;      // Groesse des Headers hinter cmpl_head
  BOOL FirstInitialized;// Daten Initialisiert
  int AnzSides;         // nur gueltig, wenn FirstInitialized...
  int AnzExtCommands;   // Anzahl der externen Kommandos
  DWORD extOffs[128];   // --
  };
#endif

/*---< Schluessel der Btrieve - Datenbank >----*/
struct progkey {
  WORD Ident;        // Fuer Programme: fortlaufender Zaehler
  WORD RecordType;   // Fuer Programme: RecordType == 0xFFFF
                     // Fuer Variablenextradeklaratioen: RecordType
  };
typedef progkey FAR *LPPROGKEY;

// Typen die, der Scanner erkennen kann
#define KEYWORD         0       // Schluesselwort
#define FUNCTIONID      1       // Funktionsaufruf
#define VARID           2       // Variable
#define T_INTEGER       3       // Nummer
#define DECIMAL         4       // Dezimalnummer
#define STRING          5       // String (unter " ")
#define UNKNOWNIDENT    6       // String ohne " "
#define FREECHAR        7       // Fuer Syntax - definition, passt immer
                                // zur Synchronisierun verwenden
#define PARID           8       // Variable
#define LOCALFUNCTIONID 9       // inline Funktion
#define ENUMVARID      10       // Enum - Variable
#define BINOP          11       // binaerer Operator
#define FNCEXP         12       // Funktion mit Resultat
#define CMPOP          13       // Vergleichsoperator
#define T_ALL          14       // Fuer Syntaxdefinition, passt immer
#define T_LINTEGER     15       // bsp. 1L
#define T_QINTEGER     16       // bsp. 0.5Q
#define VFNCEXP        17       // virtuelle Funktion

// Moegliche Fehler
#define FILENOTFOUND            1
#define NOBUFFMEM               2
#define INCFILENOTFOUND         3
#define UNKNOWNCHAR             4
#define INVNUMBER               5
#define INVDEC                  6
#define UNKNOWNCOMMAND          7
#define PREPSYNTAXERROR         8
#define DEFALREADYSET           9
#define TERM_TOOCOMPLEX         10
#define SEM_ERROR               11
#define CANNOTOPENOUTFILE       12
#define SYNTAX_ERROR            13
#define VARALREADYDEFINED       14
#define PARERROR                15
#define PROCREDEF               16
#define UNRESOLVEDCALL          17
#define LOOKUPERROR             18
#define INLINELOOKUPERROR       19
#define NESTINGERROR            20
#define ENUMVARSIZE             21
#define CONSTLOOKUPERROR        22
#define NOHELPIDENT             23
#define EDERROR                 24
#define MULTIEDITFIELD          25
#define NOEDITSECTION           26
#define NOMATCH                 27
#define NOEXPORTDONE            28
#define TABLENOTEMPTY           29
#define NOEXPORTINTHIS          30
#define NOEXPORTSDONE           31
#define PROGISIMPORTED          32
#define NOIMPORTFOUND           33
#define ERROR_NOFUNCDEF         34
#define UNKNOWNTABLE            35
#define VARDOUBLEDEFINED        36
#define TABLEALREADYUSED        37
#define INVALIDFULLVAR          38
#define INLINENOTSUPPORTED      39
#define TABLENOTDEFINED         40
#define ILLEGAL_VERSION         41
#define NODESTVERSION           42
#define ILLEGALMODE             43
#define PROGNOTFOUND            44
#define NOIMPORTSCRIPT          45
#define EXPORTNOTALLOWED        46
#define IMPORTNOTALLOWED        47
#define NOPROTOTYPES            48
#define USENOTALLOWED           49
#define INCOMPTABLES            50
#define NOTRANSFERKONTEXT       51
#define NOSTATICALLOWED         52
#define ERRORINIMPORTED         53
#define CYCLICIMPORT            54
#define PARAMOUTOFSEQUENCE      55
#define RECURSIVEPARAM          56
#define DOUBLEFREEPARAM         57
#define DOUBLEFUNCTION          58

#define MAX_ERROR               8100

// Parametertypen
#define PAR_LONG                0       // Long - Parameter
#define PAR_DEC                 1       // Dec. Parameter
#define PAR_STR                 2       // String - Parameter
#define PAR_VAR                 3       // Variable (in ExtraByte steht der Type)
#define PAR_FREE                4       // Ab diesem Parameter duerfen 
                                        // mehrere frei def. Parameter folgen
#define PAR_CONSTVAR            5       // Nur fuer Enum - Variablen

// Variablentypen
#define VAR_LONG                0
#define VAR_DEC                 1
#define VAR_STR                 2
#define VAR_POINT               3
#define VAR_CONT                4
#define VAR_STRARR              5
#define VAR_FLAG                6
#define VAR_SCALE               7
#define VAR_PICTURE             8
#define VAR_DATE                9
#define VAR_PROC                10
#define VAR_IMAGE               11
#define VAR_DWORD               12
#define VAR_OBJ                 13
#define VAR_BITMAP              14
#define VAR_TIME                15
#define VAR_QLONG               16
#define VAR_BLOB                17
#define VAR_DATETIME            18
#define VAR_FREEPAR             0xFD
#define BOOLVARFNC              0xFE
#define VAR_EDDEF               0xFF    // Damit der lex. Scanner dem editor
                                        // was mitteilen kann

// moegliche Prefix - modifiers (fuer Conditions ...)
#define PREFIX_IF               0
#define PREFIX_AND              1
#define PREFIX_OR               2
#define PREFIX_NOT              3
#define PREFIX_ELSE             4
#define PREFIX_CALL             5
#define PREFIX_CASE             6
#define PREFIX_NOP              7
#define PREFIX_ABORT            8
#define PREFIX_FOR              9
#define PREFIX_WITH            10
#define PREFIX_IN              11
#define PREFIX_INSERT          12
#define PREFIX_REMOVE          13
#define PREFIX_FORALL          14
#define PREFIX_DOWITH          15
#define PREFIX_BREAK           16
#define PREFIX_STATICCALL      17
#define PREFIX_CONTINUE        18
#define PREFIX_FUNCSTART       19
#define PREFIX_FUNCSTOP        20
#define PREFIX_FUNCTIONCALL    21
#define PREFIX_STFUNCTIONCALL  22
#define PREFIX_VIRTCALL        23
#define PREFIX_STVIRTCALL      24

#define RUN_FURTHER             0xFFFF
#define FORTYPE_COND            0
#define FORTYPE_INNEROBJ        1
#define FORTYPE_OUTEROBJ        2
#define FORTYPE_DBLIST          3
#define FORTYPE_INIT            4
#define FORTYPE_NONE            5
#define FORTYPE_INNEROBJREV     6
#define FORTYPE_SELECT          7
#define INSERTTYPE_NONE         0
#define INSERTTYPE_BEFORE       1
#define INSERTTYPE_AFTER        2

/*-------< Parameterbeschreibung, wird in hPars1 vom Lexical Scanner beim 
                auffinden eines Funktionsnamens uebergeben >--------------*/
struct pardsc {
  BYTE par_kind;
  BYTE Extra;
  };

struct fncpardef {
  WORD Number;          // Laufende Nummer des Funktionsparameters
  pardsc pd;
  };

/*-------< Darstellung von Variablen (so werden Variablen im Anweisungsfile
                referenziert)                              >------------*/
struct FAR vardef {
  WORD DBNummer;                // Datenbanknummer
  WORD Ident;                   // Identifier
  };

/*-------< Beschreibung einer Variable in parse_var >--------------*/
#define TESTBYTE 0x80
struct full_vardef {
  vardef vd;
  BYTE vartype;
  BYTE isdynamic;
  BYTE isexpression;
  BYTE doubleDefined;
  int TableNr;
  };

/*-------< Beschreibung einer Funktion in parse_var >---------------*/
struct funcdef {
  WORD funcId;                  // Indentifier der Fuktion
  WORD parCount;                // Anzahl der Parameter
  WORD ExtraCount;              // Anzahl der Bytes, die als lokaler Speicher reserviert 
                                // werden sollen
  };

/*-------< Beschreibung einer lokalen Funktion >---------------*/
struct ExpPtr {
  WORD wSize;
  DWORD dwOffs;
  };

struct FAR Ref {
  WORD DBNummer;
  WORD Ident;
  };

struct FAR firstListEle;
struct FAR secondListEle;
struct inlinefnc_header {
  WORD progOffs ;               // Offset des Kompilates zum Beginn der Struktur
  WORD progSize ;               // Groesse des Kompilates
  firstListEle FAR *LookupList ;// Start der 2dim. Liste fuer den Lookup der
                                // Parameter
  firstListEle FAR *ExpLookupList ;          // Lookup der Parameter in den Expressions
  firstListEle FAR *LocalLookup ;            // Start der 2dim. Liste fuer den Lookup der
                                // lokalen Datenelemente
  firstListEle FAR *LocalExpLookup ;         // Start der 2dim. Liste fuer den Lookup der
                                // lokalen Datenelemente
  secondListEle FAR *ExpressionLookup ;       // Start der Liste fuer den Lookup 
                                // von Expressions
  secondListEle FAR *ConstLookup ;            // Start der Liste fuer den Lookup der 
                                // Konstanten
  WORD anzPars;                 // Anzahl der Parameter
  WORD AnzExpressions;          // Anzahl der Expressions
  WORD ExpSize;                 // Groesse des Expressionkompilates
  ExpPtr FAR *ExpPtrs;          // Aufbau der Expressions fuer diese inline
                                // Funktion
  WORD AnzExpOffs;              // Anzahl der up to date zu bringenden
                                // Offsets
  DWORD FAR *ExpOffs;           // Offsets der Expressions auf Expressions
  LPVOID ExpBuffer;             // Expressions
  };

struct enumheader {
  int AnzVars;                  // Anzahl der Variablen in der enum - Definition
  struct pardsc pd;             // Typ der Variablen
  };

#ifndef EM_LOAD
struct fpt {
  float x,y ;
  };

#endif

struct enumvar {
  BYTE par_kind;
  union {
    full_vardef fvd;    // case var, constvar
    LONG l;             // case int
    float f;            // case dec
    } x;
  };

/*-------< Definition der Struktur, die der Lexical Scanner aus
                        dem Text ableitet >---------------*/
struct FAR parse_var {
  BYTE type;            // Typ des gelesenen Terms
  union {
    int k_ident;        // case KEYWORD
    long int_val;       // case INTEGER
    float float_val;    // case DECIMAL
    funcdef fd;         // case FUNCTIONID, LOCALFUNCTIONID
                        // (Parameterdeklaration wird in hPars1 uebergeben)
    full_vardef vd;     // case VARID
    fncpardef pd;       // case PARID
                        // case STRING, case UNKNOWNIDENT
                        // Daten werden in hPars0 uebergeben
    LPVOID vr;          // case BINOP..
    long double ld;     // case QLONG
    } v;
  };

/*--------------< Beschreibung der Syntax >---------------------*/
/*      Die Syntax wird in der ganz normalen Standard-          */
/*      Methode beschrieben.                                    */
/*      Rekursive Aufrufe des Parsers sind vorgesehen           */
/*      Der Code wird durch die Funktionszeiger CODEGEN erzeugt */
/*      die bei erfolgreichem Test aufgerufen wird, bevor mit   */
/*      dem Next - Zeiger weitergemacht wird                    */
/*--------------------------------------------------------------*/

typedef void (* CODEGENFUNC) ();

struct FAR syntax_node {
  struct syntax_node *next;
  struct syntax_node *alt;
  BYTE IsTerm;
  union {
    struct syntax_node FAR *nonterm;
    struct {
      BYTE type;        // siehe parse_var
      BYTE ExtraInfo;   // Wird nur benoetigt bei type == KEYWORD
      } term ;
    } info;
  CODEGENFUNC codegen;
  };

#define BUFFERSIZE 0x8000       // 32 kByte Buffer
#define MAX_DEPTH  0x0040       // 64 Levels, duerfte reichen

// Callback - Funktion zur Anzeige des Wartefensters
typedef void ( WINAPI * LPSHOWWMSG)      (double,LPVOID);

class BitArr {
 private :
  BYTE FAR *Arr;
  GLOBALHANDLE hGmem;
  WORD firstInd;
 public :
  HANDLE hmem;
  BitArr ()
    { hGmem = GlobalAlloc (GHND,0xFFFF * sizeof(BYTE) / 8) ;
      Arr = (BYTE FAR *) GlobalLock (hGmem) ; 
      firstInd = 0 ; }
  ~BitArr ()
    { GlobalUnlock (hGmem) ;
      GlobalFree (hGmem) ; }
  WORD GetFirstFree ();
  void MarkUsed (WORD);
  void *operator new (size_t size);
  void operator delete (void *);
  };

class FAR IdentHash : public hash {
 public :
  void CorrectLookupIdents (DWORD,DWORD);
  IdentHash (WORD type,WORD dim) : hash (type,dim) { }
  virtual ~IdentHash () { }
  void LookUpIdents (BYTE FAR *);
  };

// Uebergabeparameter fuer den Formular - Editor
////////////////////////////////////////////////////
#define MAXDIFFVARS         8

#define FE_STRINGVAR        0
#define FE_STRINGLISTVAR    1
#define FE_DECVAR           2
#define FE_FLAGVAR          3
#define FE_LONGVAR          4
#define FE_DEFSTR           5
#define FE_DATEVAR          6
#define FE_PICTVAR          7
#define FE_DATETIME         8

// Aufbau der Variablennamen:
struct VarNam {
  WORD StrLen;
  WORD Rec,Id;
  char Txt[1];
  }; // Kommt AnzStrs x Vor
struct VarNamSeg {
  WORD SegSize;
  WORD AnzStrs;
  VarNam vn;
  };
// Beschreibung einer Funktion, die vom Editor manipuliert wird
struct EdFncDesc {
  LPSTR ParStart;     // Zeiger auf den Source Code: Parameter Start
  LPSTR FncBeg;       // Zeiger auf die Script - Paramenter (inkl.
                      // Funktionsnummer)
  int level;          // Level beim Aufbau
  };

struct LookupEle {
  LookupEle FAR *Next;
  DWORD Offs;
  BOOL InExp;
  };
typedef LookupEle FAR *LPLUE;


#define OBJARRNAME  "frmed"
struct FEdit_param {
  GLOBALHANDLE hGText;                  // Hauptmodul
  GLOBALHANDLE hGCommands;              // Commandos fuer den Editor
  GLOBALHANDLE hGFncDesc;               // Array mit EdFncDesc
  LPSTR BegField;                       // Start des Hauptfeldes
  LPSTR EndField;                       // Ende des Hauptfeldes
  WORD wError;                          // Gings glatt ?
  int AnzObjs;                          // Anzahl der im Edit - Bereich def.
                                        // Objekte
  int AnzFncs;
  GLOBALHANDLE hGVarNam[MAXDIFFVARS];   // Jeweils Zeiger auf VarNamSeg
  int raster_x,raster_y;                // Rasterung
  };

DLLExport extern BOOL _export WINAPI GetIncludeFileName (LPSTR name,LPSTR NamBuffer,LPSTR finame,LPSTR Item = NULL);
DLLExport extern void _export WINAPI GetDebugFileName (LPSTR name,LPSTR NamBuffer,LPSTR finame);
extern GLOBALHANDLE ReadProgIcon (LPSTR IconName,WORD FAR *IconSize);

struct FAR FOFSTRUCT {
  char mem[sizeof(OFSTRUCT)];
  };

typedef BOOL (WINAPI *GETKEYFUNC) (LPSTR fname,LPPROGKEY k);
#define IS_CONDITION    1
#define IS_PROCEDURE    2
class FAR oplist;
typedef oplist FAR *LPOPLIST;
class FAR WaitWin ;
#pragma pack (1)
struct ScriptDebugInfo {
  short IncNmbr;
  short LineNmbr;
  DWORD progOffs;
  };
struct FAR ExpDebData {
  ExpDebData FAR *Next;
  ScriptDebugInfo sdi;
  };
#pragma pack()
struct ExpressionData {
  GLOBALHANDLE hGExpBuffer;
  GLOBALHANDLE hGExpOffs;
  GLOBALHANDLE hGExpPtr;
  GLOBALHANDLE hGOffs;
  LPLUE ExpOffsList;
  ExpDebData FAR *fEDD;
  };
#define PATH_SIZE   128
#ifndef NOCOMPILE
class FAR compiler {
#define ANALYZEUNQUALIFIEDS 1
#ifdef ANALYZEUNQUALIFIEDS
 public : 
#else
 protected :
#endif
  /*------< Buffer-, Zeigerverwaltung >-------------*/
  int LineNr;                   // Aktuelle Zeilennummer
  int IncLineNr;                // Aktuelle Zeilennummer (Im Include - File)
  char FAR *buffer_start;       // Bufferspeicher
  char FAR *endinclude;
  char FAR *begstr;             // Zeiger der den noch gueltigen Inhalt 
                                // anzeigt
  char FAR *w0,FAR *w1,FAR *w2; // Verschiedene Hilfszeiger, die Ihre 
                                // Gueltigkeit auch bei movebuffer bewahren,
                                // wenn sie innerhalb von begstr und actptr
                                // liegen (ausser bei Openincl.)
  int column;
  void incline (void) ;
  void incptr (void) ;
  /*------< Zeichentests (als Inline) >-------------------*/
  inline BOOL isspac (void);
  inline BOOL isret (void);
  inline BOOL isnumber (void);
  inline BOOL isspecial (void);
  inline BOOL issinglespc (void);
  inline BOOL isdigispc (void);
  inline BOOL ischaralpha (void);
  inline BOOL isdecpoint (void);
  inline BOOL ispreprstart (void);
  inline BOOL isnull (void);
  inline BOOL iscomment (void);
  inline BOOL isoperator (void);
  virtual BOOL isstrsign (void)
    { return (*actptr == '"'); }
  virtual BOOL AllowOperator()
    { return opAllowed; }
  /*------< Uebergabe von Strings >--------*/
#ifdef ANALYZEUNQUALIFIEDS
 public :
#endif
  WORD ActFreeVar ;
  WORD ActFreeHVar ;
  WORD AnzConsts ;
  void Reset_Pars0(void);
  void Push_Pars0(char);
  void Push_Pars0 (int * leadingSpaces, char ch);
  void Push_Pars0 (int * leadingSpaces);
  void Push_Pars0(void);
  char FAR *actptr;             // Eigentlicher Arbeitszeiger
  virtual DLLExport void _export WINAPI OnStartCompile();
  virtual DLLExport void _export WINAPI InstallBuffer(LPVOID);
  BOOL dontCheckDouble;
  FOFSTRUCT Ofm,Ofi;            // Input - File (Hauptfile,Includefile)
  int fd,fdi;                   // Dos - Handle
  LONG act_offset;              // Offsets in den Files, die dem Start des
  GLOBALHANDLE hText;   
  BOOL in_include;
  char fmname[PATH_SIZE];              // Filename des Source - Files
  char finame[PATH_SIZE];              // Aktuelles Include - File
  WORD vardim ;
  int loop_count;
  int loop_ind;
  LPSTR WCaption;
  void ShowWait (void);
  void ShowInclude (void);
  WORD wError;              // falls Error auftauchen sollte
  BOOL PrgEnd;              // Programm vollkommen regulaer zum Ende gekommen
  GLOBALHANDLE hPars0;      // Buffer zur Uebergabe von Strings
  GLOBALHANDLE hPars1;      // oder Uebergabe von Parameterbeschreibung bei
                            // gefundenen Funktionen
  GLOBALHANDLE hPars2;      // oder Uebergabe von Parameterbeschreibung bei
                            // gefundenen Enumvariablen
  hash FAR* hKwHash;        // Hashtabelle fuer Schluesselwoerter
  hash FAR* hAddHash;       // Hashtabelle fuer Schluesselwoerter
  hash FAR* hPpHash;        // Hashtabelle des Preprozessors
  hash FAR* hFcHash;        // Hashtabelle fuer die Funktionen
  hash FAR* hVrHash;        // Hashtabelle fuer die Variablen
  hash FAR* hPcHash;        // Hashtabelle fuer die Proceduren
  IdentHash FAR* hLuHash;   // Hashtabelle fuer die Variablen - Indizess
  hash FAR* hlFHash;        // Hashtabelle mit den lokalen Funktionen
  hash FAR* hlPHash;        // (temp.) Hashtabelle mit den Parametern der lok. Variablen
  hash FAR* henHash;        // Hashtabelle mit den enum - Variablen
  hash FAR* hopHash;        // Hashtabelle mit den Operatoren
  hash FAR* hefHash;        // Hashtabelle mit den Funktionen, die fuer Expressions verwendet werden koennen
  LPOPLIST  hasList;        // OperatorenListe fuer Assignments
  LPOPLIST  hcndList;       // OperatorenListe fuer einfache Conditions
  hash FAR* hcmpHash;       // Hashtabelle mit den compare - Operatoren

  HANDLE hBitArr;       // Bit Array zur Verwaltung der Indizess der lok. Var.

  parse_var scv;         // Aktuell gelesener Term

  /*-----< Lexical Scanner >------*/
  void SetupLists (void);
  void NextTerm (void);      // Lese naechsten Term
  BOOL dont_read;
  BOOL opAllowed;
  void PutTermBack (void) { dont_read = TRUE ; PrgEnd = FALSE ; }

  /*-----< Parser >------*/
  BOOL parse (syntax_node FAR *syntax);
  BOOL InEdit;
  BOOL EditFound;
  FEdit_param FAR *edp;

  virtual DLLExport void _export WINAPI PushToVarTable (LPSTR,full_vardef FAR *) { }
  virtual DLLExport void _export WINAPI OpenInclude(char FAR *);

  /*-----< Hash - Tables >-----*/
  BOOL CheckKwHash(void);   // Es wird der String aus hPars0
  BOOL CheckAddHash(void);  // Es wird der String aus hPars0
  BOOL CheckPpHash(void);   // als Referenz verwendet.
  BOOL CheckFcHash(void);   // res = TRUE -> Fuendig geworden.
  BOOL CheckVrHash(void);   // Es werden die Uebergabeparameter vorbereitet
  BOOL InInlineFunction ()        // Abhaenging davon, muss verschiedener
    { return (hlPHash != 0) ; }   // Code produziert werden
  BOOL ChecklPHash(void);   // Es wurde ein Parameter in der Inlinefunction
                            // gefunden
  BOOL CheckenHash(void);   // enum - Variable
  BOOL ChecklFHash(void);   // res = TRUE -> Fuendig geworden.
  BOOL CheckopHash(void);
  BOOL CheckefHash(void);
  BOOL CheckcmpHash(void);

  /*-----< String -> Zahlen >-----*/
  LONG getlong(int,BYTE FAR *type);
  void getfloat(int,double FAR *,BYTE FAR *type);

  /*---< Error - Handling >-----*/
  virtual DLLExport BOOL _export WINAPI TestError (void);
  
  /*---< Daten fuer das Wartefenster >-----*/
  DWORD dwfsize;
  DWORD dwChar;

  /*---< Konstruktor : Oeffnen des Files und Start der Kompilierung >--*/
  void Init (LPSTR wtxt);
  DLLExport _export WINAPI compiler (LPSTR wtxt);
  DLLExport void _export WINAPI DoParse (LPVOID fname,syntax_node FAR *prg,LPVOID progkey);
  DLLExport void _export WINAPI PrepareParse ();
  DLLExport void _export WINAPI ParseNow (LPVOID fname,syntax_node FAR *prg,LPVOID lpkey);

  /*-----< Destruktor : 
       Freigabe aller Buffer und Zerstoerung aller Hashtabellen >----------*/
  virtual DLLExport _export WINAPI ~compiler ();

  /*-----< Zeiger der Hashtabellen >------*/
  hash FAR *FixKwHash(void) { return hKwHash; }
  void ReleaseKwHash(void) { }
  hash FAR *FixPpHash(void) { return hPpHash; }
  void ReleasePpHash(void) { }
  hash FAR *FixVrHash(void) { return hVrHash; }
  void ReleaseVrHash(void) { }
  hash FAR *FixPcHash(void) { return hPcHash; }
  void ReleasePcHash(void) { }
  IdentHash FAR * FixLUHash(void) { return hLuHash ; }
  void ReleaseLUHash(void) { }
  hash FAR *FixlFHash(void) { return hlFHash ; }
  void ReleaselFHash(void) { }
  hash FAR *FixlPHash(void) { return hlPHash ; }
  void ReleaselPHash(void) { }
  hash FAR *FixenHash(void) { return henHash ; }
  void ReleaseenHash(void) { }
  BitArr *FixBitArr(void) { return (BitArr *) LocalLock (hBitArr) ; }
  void ReleaseBitArr(void) { LocalUnlock (hBitArr) ; }
  hash FAR *FixFcHash(void) { return hFcHash; }
  void ReleaseFcHash(void) { }
  void CorrectLookupIdents (DWORD,DWORD);

  /*-----< Preprozessor - Hashtabelle >-----*/
  void SetPpHash (double);
  void SetPpHash (long double);
  void SetPpHash (LONG,BYTE Type);
  void SetPpHash (void);

  /*-----< Keyword - Hashtabelle >------*/
  virtual DLLExport void _export WINAPI LoadKwHash (void) { }
  virtual DLLExport void _export WINAPI LoadAddHash (void) { }

  /*-----< Code - Generierung >---------*/
  GLOBALHANDLE hGExpBuffer;       // Buffer fuer die Expressions
  GLOBALHANDLE hGInlineExpBuffer; // Buffer fuer die Expressions einer Inline Funktion
  GLOBALHANDLE hGExpPtr;          // Zeiger aller Expressions
  GLOBALHANDLE hGInlineExpPtr;    // Zeiger aller Expressions einer Inline Funktion
  GLOBALHANDLE hGExpOffs;         // Alle Offsets der Expressions
  GLOBALHANDLE hGInlineExpOffs;   // Alle Offsets der Expressions einer Inline Funktion
  GLOBALHANDLE hGOffs;            // Alle Offsets der Expressions in dem
                                  // Hauptprogramm
  void pushExpression (LPVOID,WORD);
  void pushPtr (DWORD,WORD);
  void pushPtr (GLOBALHANDLE FAR &,DWORD,WORD);
  void PushExpressionData (LPVOID data,int size);
  DWORD ExpSize (GLOBALHANDLE hGmem);
  DWORD ExpSize ();
  void pushExpExpPtr (DWORD);
  void pushExpPtr (DWORD);
  GLOBALHANDLE codebuffer[MAX_DEPTH];
  BYTE bCondBuffer[MAX_DEPTH];
  GLOBALHANDLE constbuffer;
  DWORD Correct_dwOffs (DWORD);
  void CorrectProgOffs (DWORD start,DWORD end);
  void CorrectExpOffs (char huge *,DWORD,DWORD);
  void CheckExpSegs (DWORD,WORD);
  void AddExpressions ();
  int level;                      // Aktueller Level der Buffer
  void PrepCodeGen(void);         // Vorbereitungen fuer Codebuffer[0]
  void inclevel (void);           // Level erhoehen
  void pushData (void FAR *,DWORD);// Daten in den aktuellen Buffer schreiben
  void pushWord (WORD);           // Word auf den aktuellen Level
  void pushDWord (DWORD);         // Word auf den aktuellen Level
  void pushPars0 (void);          // Den String, der in hPars0 steht, 
                                  // in den Buffer schreiben

  char FAR *FixBuffer(void) { return LPSTR(GlobalLock (codebuffer[level])); }
  void ReleaseBuffer(void) { GlobalUnlock (codebuffer[level]); }
  DWORD actSize (void);           // Aktuelle Groesse des Buffers (ohne dem
                                  // 1. Word (= Groesse) des Buffers)
  void Pop (void);                // Daten des aktuellen buffers werden einen
                                  // Level tiefer uebernommen, level wird
                                  // decrementiert
  void Clear (void);              // aktuellen Buffer loeschen, level
                                  // dekrementieren
  virtual DLLExport BOOL _export WINAPI IsCondBuffer(int) { return FALSE ; }
  virtual DLLExport BOOL _export WINAPI IsProcBuffer(int) { return FALSE ; }
  DWORD progOffs(void);           // Berechnet den Offset zum Filebeginn
  DWORD ActOffs(void);            // Berechnet den Offset zum Filebeginn
  DWORD fncOffs(void);            // Berechnet den Offset zum Funktionsbeginn

  WORD sizePars0(void);           // Groesse des Stringbuffers (ohne 1. Wort)

  virtual DLLExport void _export WINAPI TestExternError () { }
  virtual DLLExport void _export WINAPI SetExternError () { }
  virtual void WriteRes (LPVOID,LPVOID) { }   // codebuffer[0] auf File schreiben

  /*----------< Buffer Verwaltung >---------------*/
  LPSTR MainBufferPtr;
  GLOBALHANDLE hGIncFiles[50];
  int ActIncFile;
  void CheckSegs();
  void CheckSegs(WORD);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  WaitWin FAR *ww;
  virtual DLLExport BOOL _export WINAPI BInWAllowed()
    {
    return FALSE ;
    }
  };
#endif

struct DebugHdEntry {
  char FName[13];
  };
#define MAX_INCFILES    64
#pragma pack(1)
struct DebugHeader {
  short AnzFiles;
  DebugHdEntry ent[MAX_INCFILES];
  };
class FAR exp_node ;
class FAR oplist ;
typedef oplist FAR *LPOPLIST;
#ifndef NOCOMPILE
struct FAR LocalHashList {
  LocalHashList FAR *Next;
  DWORD procOffset;
  hash FAR *h;
  };
#define FTYPE_NORMAL    0
#define FTYPE_EXPORT    1 // export
#define FTYPE_DECLARE   2 // base
#define FTYPE_IMPORT    3 // import, overloaded
#define FTYPE_VIRTUAL   4 // import_virtual
class FAR SLStack {
 public :
  DWORD sd[32];
  int sdPtr;
  void Push(DWORD d)
    { sd[sdPtr++] = d ; }
  void Pop ()
    { sdPtr -- ; }
  DWORD Top()
    { return sd[sdPtr-1] ; }
  };
struct FAR Alias {
  LPSTR AliasName ;
  LPSTR TableName ;
  short TableNr;
  Alias FAR *Next;
  };
struct FAR PrivateStruct {
  LPSTR Name ;
  WORD constOffs ;
  PrivateStruct FAR *Next;
  };
struct FAR UsedVersion {
  LPSTR TableName;
  WORD minVersion;
  WORD maxVersion;
  UsedVersion FAR *Next;
  };
#pragma pack()
class FAR ScriptCompiler : public compiler {
 private :
  /*------< Buffer-, Zeigerverwaltung >-------------*/
  LONG inc_offset;              // Buffers entsprechen
  LONG LastOffset;              // Hilfsvariable zur Includefileverw.
 public :
  /*----< Konstruktor >-----*/
  virtual DLLExport void _export WINAPI OnStartCompile();
  ScriptCompiler (LPSTR);
  /*-----< Destruktor : 
       Freigabe aller Buffer und Zerstoerung aller Hashtabellen >----------*/
  virtual ~ScriptCompiler ();

  /*-----< Keyword - Hashtabelle >------*/
  virtual DLLExport void _export WINAPI LoadKwHash (void);

  /*-----< Typ - Ueberpruefung >--------*/
  WORD  lstFuncNumber;
  WORD actpar ;
  WORD parcount ;
  DWORD parlenoffs ;
  void pushpar(void);
  void pushfncpar(void);
  void pushfncExpPar (WORD Number,DWORD Offset);
  DWORD fncstart;
  void MarkEdBraceOpen(void);
  void GetFuncCopy(void);
  void push_funchead(void);
  void PrepExpBuffer ();

  /*-----< Prozedur - Aufrufe >---------*/
  void enterPars0 (void);         // Aktuellen Identifier in die Prozedurtabelle
  void enterPars0Function (void);  // Aktuellen Identifier in die Funktionstabelle
  void lookup (void);             // Adresse der Prozedur aus der Prozedurtabelle laden

  WORD pushConst (void FAR *data,WORD size,WORD mType,BOOL WriteLength = TRUE,
                                    BOOL MultiUse = TRUE);
                                  // Daten in Konstantenbuffer schreiben
  WORD ConstSize (void);          // Groesse des Konstantenbuffers

  void MarkInlineforLookup (WORD);      // Berechnet den Offset zum Funktionsbeginn
                                  // und traegt den Ident fuer spaeteres
                                  // Lookup ein
  void MarkforLookup (WORD);      // Berechnet den Offset zum Filebeginn
                                  // und traegt den Ident fuer spaeteres
                                  // Lookup ein
  void MarkInlineforLookup (DWORD,WORD);
  void MarkForConstbinding (DWORD);// Eintragen, dass beim Identifier spaeter
                                  // noch der Gesamtoffset eingetragen werden
                                  // muss
  void MarkForExpbinding (DWORD Offs);
                                  // Eintragen, dass spaeter die Expression
                                  // up to date zu bringen ist
  void MarkExpForLookup (DWORD Offset);
  void MarkExpForLookup ();
  void MarkExpInlineForLookup (DWORD Offset);
  void MarkExpInlineForLookup (); // Eintragen der Expressions in die Liste fuer spaeter
                                  // einzutragende Offsets
  void MarkInlineForConstbinding (DWORD);// Eintragen, dass beim Identifier spaeter
                                  // noch der Gesamtoffset eingetragen werden
                                  // muss
  void pushOp (WORD);             // Operator schreiben (Operator geht
                                  // einen Level tiefer als aktueller Level,
                                  // rel. Zeiger auf den 2. Term wird gestellt
                                  // (= Groesse des aktuellen Buffers)
                                  // impliziter Pop
  void DefVar (LPSTR,BOOL,WORD);
  virtual DLLExport void _export WINAPI PushToVarTable (LPSTR,full_vardef FAR *);
  void FixupInlineFnc (int,LPVOID,int size);
  virtual DLLExport BOOL _export WINAPI IsCondBuffer(int);
  virtual DLLExport BOOL _export WINAPI IsProcBuffer(int);
  virtual DLLExport void _export WINAPI InstallBuffer (LPVOID name);
  void MarkCond ();
  void MarkProcBuffer ();
  void ClearCond ();
  void ClearProcBuffer ();
  void FixupPar ();
  void FixupEnumPar ();
  void FixupEnumEle ();
  void FixupConstPar ();
  void FixupUsedLocals ();
  void FixupUsedExpLocals ();
  void FixupUsedConstants ();
  void FixupUsedExpressions ();
  void DestroyConstList (void);
  void DestroyFncLookup (void);
  void PushOffs (DWORD,WORD);     // Eintragen des Offsets fuer den Ident
  void PushExpId (DWORD,WORD);    // -..- im Epxression - Block
  void PushInlineExpId (DWORD Offset,WORD Ident);

  void StoreEnumVar ();
  WORD GetFreeIdent ();
  void CorrectIdentOffsets(DWORD,DWORD);
  void FixupExpOffs (char _huge *base,DWORD boffs,DWORD roffs);
  void FixupConstOffs (LPSTR,WORD);  // Offsets zu den Konstanten korrigieren
  virtual void WriteRes (LPVOID,LPVOID);   // codebuffer[0] auf File schreiben
  virtual DLLExport void _export WINAPI EndOfWriteRes (LPSTR FromVersion,GLOBALHANDLE hGres,DWORD rSize);

  // Dokumentdefinition
  WORD Type;
  int AnzDBNmbr;
  WORD Category;
#ifdef UEBERLEGT
  WORD DBNumber[MAXDBNMBR];
#endif
  char fullname[100];
  char IconName[128];
  LPSTR PropertyString;

  virtual DLLExport void _export WINAPI TestExternError ();
  virtual DLLExport void _export WINAPI SetExternError ();

  /*--------< Dynamisches Linken >--------------*/
  BOOL ImportDone;
  BOOL exportThis;    // Aktuelle Porzedur muss exportiert werden
  hash *ExportHash;   // Hashtabelle mit den exportierten Funktionen,
                      // die dann auch noch mitgespeichert wird

  void PutConstBuffer (GLOBALHANDLE hGc);

  int SetTableUsed (WORD TableID,WORD Version);
  BOOL IsTableUsed (WORD TableID,WORD Version);
  void LoadResources ();

  /*---< Debugger >-----*/
  int GetIncludeNumber ();
  void PushProgOffs ();
  void Debug_SetProgOffs ();
  void WriteDebugInfo (LPSTR name, LPSTR dirIniName, LPSTR dirDefName);
  void MarkForExpDebPush (DWORD Offs);

  GLOBALHANDLE hGDebugInfo;
  DebugHeader dHd;
  DWORD lastProgOffs;
  ExpDebData FAR *fEDD;
  LPSTR actFPrefix;

  void InitializeDebugInfo ();
  void FreeDebugInfo ();
  void DebugPush (ScriptDebugInfo FAR *sdi);
  void DoExpDebPush (DWORD Offs);
  // Stack fuer Daten der Expressions
  //////////////////////////////////////
  LPOPLIST lastop;
  LPOPLIST lastoplist;
  WORD actres;
  exp_node FAR *last;
  int brlevel;

  exp_node FAR *lstack[64];
  int lstacki;
  ExpressionData _expdstack[MAX_DEPTH];
  int _expdptr;
  LPLUE ExpOffsList ;
  void NextExpProc ();
  void PrevExpProc ();
  BOOL ExpAllowed ();
  void InitializeExpProc ();

  hash FAR *hSFcHash;
  hash FAR *FixSFcHash() { return hSFcHash; }
  void ReleaseSFcHash() { }
  hash FAR *localVars;
  int LocalVarCount,LocalHVarCount;
  BOOL InFunction;
  BYTE funcVarType;
  BOOL IsInFuncDefinition;
  int AnzFuncPars;
  DWORD ActFuncAddress;
  LocalHashList FAR *lhlist;
  BYTE FType;
  BOOL ExportDone;
  void PushToLocalHashList (hash FAR *localVars,DWORD ActFuncAddress);
  LPVOID MyImportModules;
  LPVOID MyBaseModules;
  LPVOID MyVirtualModules;
  hash FAR *declareFuncs;
  hash FAR *FixLocals()
    {
    if (localVars == NULL) localVars = new hash(37,STRKEY);
    return localVars;
    }
  void clearLocals()
    {
    LocalVarCount = 1 ;
    LocalHVarCount = 0 ;
    if (localVars != NULL) {
      PushToLocalHashList (localVars,ActFuncAddress);
      }
    localVars = NULL ;
    }
  LPOPLIST LastVirtFunction;
  WORD AnzTablesToReuse;
  WORD TablesToReuse[64];
  BOOL allowBreak_old[32];
  int bstack;
  BOOL dontVarCheck,allowBreak;
  int lastdatabasenumber ;
  int lastvartype ;
  BOOL setdatabasenumberDone ;
  GLOBALHANDLE hGLookupmem ;
  SLStack ActForTypeOffs,ActForDBSelOffs;
  DWORD ActSingOffs,ActTableNrOffs;
  WORD rfortype;
  LPLUE ConstOffsList ;
  GLOBALHANDLE hGConstOffsMem ;
  int startlevel;
  GLOBALHANDLE hProgCopy;
  GLOBALHANDLE hGPtrs;
  GLOBALHANDLE hGNPtrs;
  ExpPtr corr_offs[10];
  int corr_ptr;
  WORD constOffs;
  WORD constType;
  // GLOBALHANDLE hGFncLookup; // Segment, in dem die Listen angelegt werden
  // WORD actFncLookup;        // Start der Liste
  firstListEle FAR *actFncLookup;
  firstListEle FAR *actExpFncLookup;     // Start der Liste
  firstListEle FAR *actLocalLookup;      // 2dim. Liste mit den Lookupwerten
                            // der Funktion
  firstListEle FAR *actLocalExpLookup;   // 2dim. Liste mit den Lookupwerten
                            // der Funktion
  secondListEle FAR *actConstLookup;      // 2dim. Liste mit Lookupwerten der Konstanten
  secondListEle FAR *actExpressionLookup;
  Alias FAR *FirstAlias,FAR *ActAlias ;
  UsedVersion FAR *fUse;

  WORD actPrivateID;
  PrivateStruct FAR *ps;
  LPSTR actStructData;

  BOOL dontCheckSeg;
  BOOL dontVarCheckGlobals,dontUnqualifiedCheck;
  };

class FAR BlobScriptCompiler : public ScriptCompiler {
 public :
  GLOBALHANDLE hGSource;
  GLOBALHANDLE hGRes;
  DWORD SizeOfRes;
  BOOL of;
  BlobScriptCompiler (LPSTR fName,GLOBALHANDLE hGmem,BOOL mitOberflaeche) : ScriptCompiler (fName)
    {
    hGSource = hGmem ;
    of = mitOberflaeche;
    }
  virtual DLLExport void _export WINAPI InstallBuffer(LPVOID);
  virtual DLLExport void _export WINAPI EndOfWriteRes (LPSTR FromVersion,GLOBALHANDLE hGres,DWORD rSize);
  virtual DLLExport void _export WINAPI OnStartCompile();

  virtual ~BlobScriptCompiler ();
  virtual DLLExport void _export WINAPI OpenInclude(char FAR *);
  virtual DLLExport BOOL _export WINAPI TestError (void);
  };

struct ParStatus {
  int countPart;
  BOOL isfdef;
  BOOL isOptional;
  BOOL isOptionalInCount;
  BOOL isFree;
  BOOL wasOptional;
  BOOL wasFree;
  BOOL freeSet;
  };
  
class FAR FncCompiler : public ScriptCompiler {
 public :
  ParStatus actParStatus;
  /*----< Konstruktor >-----*/
  FncCompiler () : ScriptCompiler (NULL) { actParStatus.isfdef = FALSE; }
  /*-----< Destruktor : 
       Freigabe aller Buffer und Zerstoerung aller Hashtabellen >----------*/
  virtual ~FncCompiler () { } ;

  virtual DLLExport void _export WINAPI OnStartCompile();
  virtual void WriteRes (LPVOID,LPVOID) { }
  virtual BOOL AllowOperator()
    { return TRUE; }
  };
#endif

/*--------------------------------------------------------------*/
/*      Da die Code - Generierung des Parsers ueber             */
/*      (near) Funktionszeiger gesteuert wird,                  */
/*      geht der implizite Zusammenhang zur Instanz verloren.   */
/*      Deswegen wird hier der Zeiger auf die aktuelle Instanz  */
/*      als global Variable verwendet                           */
/*--------------------------------------------------------------*/
#ifndef NOCOMPILE
#ifdef COMPILE_MAIN
ScriptCompiler *_actcmpl;
#else
extern ScriptCompiler *_actcmpl;
#endif
#endif

/*--------------------------------------------------------------*/
/*      Der Parser ist als State - Machine (logo!)              */
/*      aufgebaut.                                              */
/*      Moegliche Zustaende:                                    */
/*--------------------------------------------------------------*/

#define STATE_NORMAL    0       // Noch keine bestimmte Vorstellung
#define STATE_STRING    1       // Innerhalb eines Strings
#define STATE_NUMBER    2       // Bis jetzt sind nur Nummern aufgetreten
#define STATE_DEC       3       // Dizimalzeichen aufgetreten
#define STATE_WORD      4       // In einem normalen Wort
#define STATE_SPCWORD   5       // In einem spezial - Wort (Bsp &&)
#define STATE_COMMENT   6       // In einem Kommentar
#define STATE_PREPROC   7       // Start eine Preprozessor Kommandos
#define STATE_INCCOMMAND   8    // 9Include Kommando (n.v.)
#define STATE_INCSPACE    9     // Include Kommando fertig
#define STATE_INCFNAME    10    // Filename wird angegeben
#define STATE_DEFINE       11   // Define - Kommando (n.v.)
#define STATE_DEFSPACE0   12    // Define - Kommando fertig
#define STATE_DEFIDENT    13    // Im Namen des Define Kommandos
#define STATE_DEFSPACE1   14    // Name fertig
#define STATE_DEFNUMBER   15    // Nummer hinter einem Define
#define STATE_DEFDEC      16    // Dezimalzahl -..-
#define STATE_DEFSTR      17    // String hinter einem Define
#define STATE_PREPIF        18  // Define hinter #ifdef,#ifndef
#define STATE_PREPNOCOMP    19  // Warten auf #endif bzw auf #else

DLLExport void _export WINAPI InitModuleHash ();
DLLExport void _export WINAPI DoneModuleHash ();
DLLExport int _export WINAPI DoCompile (HWND,LPSTR);
DLLExport int _export WINAPI DoCompileMod (HWND hWndParent,LPSTR fname);
DLLExport int _export WINAPI FunctionPrototypes (LPSTR fname);

DLLExport WORD _export WINAPI IsCompileAborted ();
DLLExport LPSTR _export WINAPI GetErrorInfo (int FAR *LineNr,int FAR *ColumnNr);
DLLExport BOOL _export WINAPI InterpreteCString (LPSTR d,int size,LPSTR s,int FAR *rsize);

// Liste, die im Kompilat steht, um auf Expressions zuzugreifen
#ifndef MAXRUN
#define MAXRUN 5
#endif
struct ptr_list {
  LPVOID res[MAXRUN];
  };
typedef ptr_list FAR *LPPTRLIST;

#ifndef WITHOUT_GETININAME
extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
#define MYINI           GetIniName ()
#endif
#endif

#define SCRIPTSECTION   "Script"
#define INCLUDE         "include"
#define SOURCE          "source"
#define SOURCEDEF       ".\\"
#define INCLUDEDEF      ".\\"
#define DEBUGDEF        ".\\"
#define INCLUDE1        "include1"
#define DEBUGENT        "debug"
#define DEBUG1ENT       "debug1"
#define DEBUGFORMSENT   "debugforms"

typedef hash *LPHASH;
#ifndef NOCOMPILE
extern void LoadFuncHashs(GLOBALHANDLE hGmem,compiler *cmp);
#endif

// Die Kategorien eines Dokumentes
#define CATEGORY_SENTER   0x8000    // Eingabedokument, das nur alleine
                                    // auf sein darf
#define CATEGORY_MPENTER  0x4000    // Eingabedokument, das mehrmals 
                                    // offen sein darf, aber nicht fuer den
                                    // gleichen Patienten (bei gleichem
                                    // Hauptdatensatz)
#define CATEGORY_MDENTER  0x2000    // Eingabedokument, das mehrmals
                                    // offen sein darf, aber nicht fuer den
                                    // gleichen Datensatz
#define CATEGORY_MANA     0x0000    // Analyse - Dokument, darf nur bei
                                    // existierenden Daten geoeffnet werden

// For - Header
#pragma pack(1)
struct FAR ForHeader {
  WORD prefix ;       // Immer PREFIX_FOR
  WORD forType;       // Typ der For - Schleife
  LPVOID fp;          // Daten der Schleife
  LPVOID ctrs;        // Counter...
  DWORD objVar;       // Resultat
  DWORD listName;     // Name der Liste, die aufzubauen ist
  WORD AnzParams;     // Anzahl Parameter, auf die ein Fixconnection gebaut werden soll
  DWORD Par[1];       // Parameter
  WORD Size()
    { return (sizeof(*this) + AnzParams * sizeof(Par[0])) - sizeof(Par[0]) ; }
  };

struct FAR ObjCondition {
  DWORD objvar;
  short TableNr;
  };
struct FAR DBSelCondition {
  short anzSels;
  DWORD TableName;
  DWORD WhereName;
  DWORD OrderName;
  BYTE  AnzPars;
  BYTE  DoReverse;
  DWORD Par[1];
  WORD Size()
    { return (sizeof(*this) + AnzPars * sizeof(Par[0])) - sizeof(Par[0]) ; }
  };
struct FAR InitCondition {
  WORD AnzVars ;
  WORD AnzPars ;
  DWORD Par[1];
  WORD Size()
    { return (sizeof(*this) + AnzPars * sizeof(Par[0])) - sizeof(Par[0]) ; }
  } ;
struct FAR DoWithList;
typedef DoWithList FAR *LPWLIST;
struct FAR WithParam {
  WORD  Prefix_With ;
  WORD BlockSize ;
  LPVOID ctrs;
  LPWLIST wlist;
  LPVOID mp;
  LPVOID oldrec;
  WORD  TableInd;
  short TableNr ;
  DWORD objvar ;
  DWORD Par[1] ;
  } ;
struct FAR InParam {
  WORD  Prefix_In ;
  WORD  BlockSize ;
  short TableNr ;
  DWORD Par[1] ;
  } ;
struct FAR InsertParam {
  WORD  Prefix_In ;
  WORD  BlockSize ;
  WORD  InsertType ;
  short TableNr ;
  DWORD Par[1] ;
  } ;
struct FAR RemoveParam {
  WORD  Prefix_In ;
  WORD  BlockSize ;
  short TableNr ;
  DWORD objvar ;
  DWORD Par[1] ;
  } ;
#define BIND_DYNAMIC  0
#define BIND_STATIC   1
#define BIND_RETURN   2
struct FAR FuncStart {
  WORD Prefix_Funcstart ;
  DWORD rec1;
  DWORD rec2;
  WORD AnzPars;
  WORD AnzLocals;
  WORD AnzStaticLocals;
  BYTE BindTyp[1];
  };

struct FAR FunctionCall {
  WORD parSize;
  DWORD procAddr;
#ifdef MULTIPRO_INCLUDED
  MultiProc FAR *mp;
#else
  LPVOID mp;
#endif
  DWORD par[1];
  int AnzPars ()
    {
    return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; 
    }
  };
struct FAR ExpFunctionCall {
  WORD parSize;
#ifdef MULTIPRO_INCLUDED
  MultiProc FAR *mp;
  mdiChild *ec;
#else
  LPVOID mp;
  LPVOID ec;
#endif
  LPWORD destind;
  char Name[1];
  LPSTR FName ()
    {
    return Name + lstrlen(Name) + 1 ;
    }
  WORD IndOffs ()
    {
    // Auf eine gerade Addresse zwingen
    WORD Offs = sizeof(*this) + lstrlen(Name) + lstrlen(FName()) + 1 ;
    if ((Offs % 2) == 0) return Offs ;
    else                 return (Offs / 2 + 1) * 2 ;
    }
  WORD FAR *Ind()
    {
    return (WORD FAR *) (LPSTR (this) + IndOffs() + sizeof(WORD)) ;
    }
  WORD ParOffs ()
    {
    // Auf eine gerade Addresse zwingen
    return IndOffs() + (Ind()[-1] + 1) * sizeof(WORD);
    }
  DWORD FAR *par ()
    {
    return (DWORD FAR *) (LPSTR (this) + ParOffs()) ;
    }
  int AnzPars ()
    {
    return (parSize - ParOffs()) / sizeof(DWORD) ; 
    }
  };
struct FAR VirtFunctionCall {
  WORD parSize;
#ifdef MULTIPRO_INCLUDED
  MultiProc FAR *mp;
  mdiChild *ec;
#else
  LPVOID mp;
  LPVOID ec;
#endif
  LPWORD destind;
  char FName [1];
  WORD IndOffs ()
    {
    // Auf eine gerade Addresse zwingen
    WORD Offs = sizeof(*this) + lstrlen(FName) ;
    if ((Offs % 2) == 0) return Offs ;
    else                 return (Offs / 2 + 1) * 2 ;
    }
  WORD FAR *Ind()
    {
    return (WORD FAR *) (LPSTR (this) + IndOffs() + sizeof(WORD)) ;
    }
  WORD ParOffs ()
    {
    // Auf eine gerade Addresse zwingen
    return IndOffs() + (Ind()[-1] + 1) * sizeof(WORD);
    }
  DWORD FAR *par ()
    {
    // Vor den Parametern steht der Modulname (par()[-1])
    return (DWORD FAR *) (LPSTR (this) + ParOffs() + sizeof(DWORD)) ;
    }
  int AnzPars ()
    {
    int OffsExtra = parSize - (ParOffs() + sizeof(DWORD));
    return (OffsExtra > 0) ? OffsExtra / sizeof(DWORD) : 0 ; 
    }
  };

#pragma pack()

// Fehlertext an das Elternfenster schicken
#define   WMU_SETERRORTEXT   (WM_USER + 3)

typedef BOOL (WINAPI * GENSTRUCT) (LPSTR fName,LPSTR Buffer,LPSTR prefix);
typedef BOOL (WINAPI * GENVIEW) (LPSTR fName,LPSTR Buffer,LPSTR prefix,BOOL mustUseVersions,LPSTR FAR *TableNamesForUseVersion,WORD FAR *VersionsForUseVersion);
DLLExport void _export WINAPI SetCommandLineFlag (BOOL flag);
DLLExport BOOL _export WINAPI GetCommandLineFlag ();
DLLExport void _export WINAPI SetGenStruct (GENSTRUCT gs);
DLLExport void _export WINAPI SetGenView (GENVIEW gv);
DLLExport void _export WINAPI AnalyseAlias (hash *h,LPSTR in,LPSTR name,WORD i,WORD FAR *j);
DLLExport DWORD _export WINAPI GetFunctionsAddress (LPSTR Name,LPVOID exportDef,LPWORD FAR *TableInds,WORD FAR *Restype);
DLLExport void _export WINAPI GetFunctionName (LPSTR Name,LPSTR buffer,int AnzArgs,WORD FAR *vtype);
DLLExport GLOBALHANDLE _export WINAPI DoCompileFromBlob (GLOBALHANDLE hGSource,DWORD SourceSize,LPSTR FName,DWORD FAR *rSize,BOOL mitOberflaeche);


