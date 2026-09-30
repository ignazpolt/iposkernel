//////////////////////////////////////////////////////
//  Header fuer einen Resourceneintrag
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/rsbtrv.hpv   1.5   04 Mar 1996 21:12:40   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/rsbtrv.hpv  $
// 
//    Rev 1.5   04 Mar 1996 21:12:40   GERHOLD
// pragma pack
// 
//    Rev 1.4   02 Feb 1996 11:01:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   16 Feb 1995 12:47:04   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.2   29 Jan 1995 11:45:46   HANNES
// 
//    Rev 1.1   24 Aug 1994 19:42:32   HANNES
// No change.
// 
//    Rev 1.0   24 Jun 1994 17:01:28   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   18 Apr 1994 20:18:34   HANNES
// Initial revision.
//
// Header des Datadictionarys
///////////////////////////////
#pragma pack(1)
struct FAR rsdata_header {
/*   4 */ DWORD InterneNummer;        // Autoincrement Key
/*   5 */ char Type;                  // Typ der Daten, die angefordert werden
/*  25 */ char dllName[20];           // Name der DLL, fuer die die Daten verwaltet
/*     */                             // werden, bzw 0
/*  89 */   char TableName[64];       // Name der Tabelle
/*  91 */ WORD TableIdent;            // Ident der Tabelle
/* 155 */ char VarName[64];           // Name der Variable
/* 157 */ WORD VarIdent;              // Ident der Variable
/* 159 */ WORD LaufendeNummer;        // fuer groessere Bloecke
  };
typedef rsdata_header FAR *LPRSDHEADER;

#define RST_VRDATADICT   '1'  // Eintrag ist das Compilat einer
                              // Variablendeklaration
#define RST_TBDATADICT   '2'  // Eintrag ist das Compilat eines
                              // Tabelleneintrages
#define RST_TBFDATADICT  '3'  // Eintrag ist Tabelle und 
                              // Variablendeklaration zusammengesetzt
#define RST_DDCONT       '4'  // Eintrag ist Inhaltsverzeichnis des DataDictionarys
#define RST_DSERVSRC     '5'  // Eintrag ist Source - Code der Serverzugriffe

// Zusammengesetzte Schluessel
//////////////////////////////////////////
#define KEY_AUTOINC       0
struct Key_Primary {    // Key 0
  DWORD InterneNummer;  // Autoincrement Key
  };

#define KEY_TABLENAME     1
struct TableKey_Name {        // Key 1
  char Type;            // = RST_TBDATADICT
  char dllName[20];     // Name der DLL
  char TableName[64];   // Name der Tabelle
  WORD LaufendeNummer;  // Laufende Nummer (1. Segment faengt immer mit 0 An)
  };

#define KEY_TABLEIDENT    2
struct TableKey_Ident {       // Key 2
  char Type;            // = RST_TBDATADICT
  char dllName[20];     // Name der DLL
  WORD TableIdent;      // Ident der Tabelle
  WORD LaufendeNummer;  // Laufende Nummer
  };

#define KEY_VARNAME       3
struct VarKey_Name {          // Key 3
  char Type;            // = RST_VRDATADICT
  char dllName[20];     // Name der DLL
  WORD TableIdent;      // Ident der Tabelle
  char VarName[64];     // = Variablennamen
  WORD LaufendeNummer;  // Laufende Nummer
  };

#define KEY_VARIDENT      4
struct VarKey_Ident {         // Key 4
  char Type;            // = RST_VRDATADICT
  char dllName[20];     // Name der DLL
  WORD TableIdent;      // Ident der Tabelle
  WORD VarIdent;        // Ident der Variable
  WORD LaufendeNummer;  // Laufende Nummer
  };

#define KEY_TYPE          5
struct Key_Type {             // Key 5
  char Type;            // = RST_DDCONT
  char dllName[20];     // Name der DLL = INTERNNAME
  WORD LaufendeNummer;  // Laufende Nummer
  };

// Header fuer die Script - Compilate
///////////////////////////////////////
struct rsscript_header {
/*  4 */ DWORD InterneNummer;
/*  5 */ char Type;
/* 69 */ char DocumentName[64];
/* 71 */ WORD LaufendeNummer;
  };
typedef rsscript_header FAR *LPRSSHEADER;

#define RSS_TYPEDOCDEF      '1'
#define RSS_TYPEDOCCONT     '2'
#define RSS_TYPEFNCPROT     '3'

#define KEY_SPRIMARY        0
struct Key_SPrimary {         // Key 0
  DWORD InterneNummer; // Autoincrement Key
  };

#define KEY_DOCNAME         1
struct Key_DocName {          // Key 1
  char Type;              // Typ des Eintrages (RSS_TYPEDOCDEF,RSS_TYPEDOCCONT,RSS_TYPEFNCPROT)
  char DocumentName[64];  // Name des Dokumentes
  WORD LaufendeNummer;    // Laufende Nummer
  };

// Header fuer die ResourceDatenbank
///////////////////////////////////////
struct rsres_header {
/*  4 */ DWORD InterneNummer;
/*  8 */ DWORD ResID;
/* 10 */ WORD  Type;
/* 74 */ char  ResName[64];
/* 76 */ WORD  LaufendeNummer;
  };
typedef rsres_header FAR *LPRSRHEADER;

#define KEY_RPRIMARY      0
struct Key_RPrimary {         // Key 0
  DWORD InterneNummer;    // Autoincrement Key
  };

#define KEY_RESID         1
struct Key_ResId {            // Key 1
  DWORD ResID;            // Resource ID
  WORD  LaufendeNummer;   // Laufende Nummer
  };

#define KEY_RESNAME       2
struct Key_ResName {            // Key 2
  WORD  Type;
  char  ResName[64];
  WORD  LaufendeNummer;   // Laufende Nummer
  };

struct rstmp_header {
  DWORD InterneNummer;
  WORD Type;
  char TempName[64];
  WORD LaufendeNummer;
  };

#define KEY_TPRIMARY      0
struct Key_TPrimary {         // Key 0
  DWORD InterneNummer;    // Autoincrement Key
  };

#define KEY_RESID         1
struct Key_Tres {            // Key 1
  WORD Type;
  char TempName[64];
  WORD LaufendeNummer;
  };
#pragma pack()

