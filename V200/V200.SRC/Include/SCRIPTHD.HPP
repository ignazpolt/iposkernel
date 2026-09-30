////////////////////////////////////////////////////////////////
//  Generieren der Scripts
////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/include/rev/scripthd.hpv   1.24   14 May 2000 17:34:08   Hannes  $
//  $Log:   F:/marille/clinicum/include/rev/scripthd.hpv  $
// 
//    Rev 1.24   14 May 2000 17:34:08   Hannes
// Prototyp GetFirst & GetNextScript
// 
//    Rev 1.23   23 Nov 1999 15:49:02   Wolfgang
// 1.) DDSCopyScriptEntry zum Kopieren eines ScriptEntrys an den Debugger neu.
// 
//    Rev 1.22   26 Mar 1999 18:08:20   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.21   05 Jan 1998 07:48:24   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.20   15 Dec 1997 17:35:42   Hannes
// Zusammenspiel Debugger / Formulargenerierung
// 
//    Rev 1.19   24 Oct 1997 08:37:46   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.18   13 Mar 1997 19:01:52   Hannes
// GetScriptEntry (FROM Blob)
// 
//    Rev 1.17   19 Feb 1997 12:03:08   Hannes
// Scriptfunktionen->Erweiterung des Headers
// 
//    Rev 1.16   17 Dec 1996 18:03:56   HANNES
// 
//    Rev 1.15   26 Nov 1996 08:08:04   HANNES
// Automatischer Update
// 
//    Rev 1.14   21 Oct 1996 18:53:58   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.13   04 Mar 1996 21:14:26   GERHOLD
// pragma pack() ;   in WIN16 szReserved[2] dazu
// 
//    Rev 1.12   04 Feb 1996 15:45:42   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.11   02 Feb 1996 11:00:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   11 Jul 1995 12:42:06   HANNES
// Anzahl Tabellen / Script vergroessert
// 
//    Rev 1.9   09 Jun 1995 00:32:42   HANNES
// Konstantenhandling
// 
//    Rev 1.8   15 May 1995 08:26:28   HANNES
// Propertys
// 
//    Rev 1.7   24 Feb 1995 11:16:42   HANNES
//  
// 
//    Rev 1.6   09 Jan 1995 12:11:52   HANNES
// Debugger eingebaut
// 
//    Rev 1.5   05 Dec 1994 17:37:08   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.4   31 Oct 1994 10:43:28   hannes
// Erweiterung um das Optionsscript
// 
//    Rev 1.3   03 Sep 1994 14:54:46   HANNES
// Formulartyp in den Header
// 
//    Rev 1.2   24 Aug 1994 19:39:48   HANNES
// Erweiterungen im Header
// 
//    Rev 1.1   24 Jun 1994 18:01:26   HANNES
// Neuuebernahme clinicum
//
#pragma pack(1)

// #define MAXTBSINENT 128

#define FT_INTERN                0
#define FT_MAPPE                 1
#define FT_FACHMITVERWEISE       2
#define FT_FACHOHNEVERWEISE      3
#define FT_FORMULARMITVERWEISE   4
#define FT_FORMULAROHNEVERWEISE  5
struct FAR _AliasDef {
  short TableNr;
  char AliasName[1];
  _AliasDef FAR *Next ()
    {
    return (_AliasDef FAR *) (LPSTR (this + 1) + lstrlen(AliasName)) ;
    }
  };
struct FAR _FuncTypeList {
  DWORD procPtr;
  union {
    DWORD NextTypeListOffset ;
    _FuncTypeList FAR *Next;
    } d;
  WORD AnzDynLocals;
  WORD AnzStaticLocals;
  };
typedef _AliasDef FAR *LPALIASDEF ;
#ifndef TABLEREF_DEFINED
struct FAR TableRef {
  WORD Version;
  WORD TableNr;
  };
#define TABLEREF_DEFINED
#endif
// Aufbau des Compilates:
// 1. * ScriptContent_Entry
// 2. * IconData
// 3. * PropertyData
// 4. * AliasDef
// 5. * ImportModules
// 6. * BaseModules
// 7. * ExportDef
// 8.   LocalDataTypes
// 9.   HelpDataTypes
// 10.  FuncTypeList
//--------------------------
class FAR DBRecord;
typedef DBRecord FAR *LPDBRECORD;
struct FAR ScriptContent_Entry {
  char  Name[64];   // Name des Dokumentes
  char  fName[13];  // Filename
  DWORD fSize;      // Groesse des Scriptcompilates
  DWORD cSize;      // Groesse des Konstantenblocks
  WORD  Category;   // Kategorie
  WORD  Type;       // Typ des Dokumentes

  // Generelle Eingenschaften
  /////////////////////////////////
  short DarfInFachsein;               // Darf Dokument als Fach vorkommen
  short DarfImVerzeichnisVorkommen;   // Darf Dokument von einem Inhaltsverzeichnis
                                      // aus aufgerufen werden
  short DarfInKrankengeschichteVorkommen;   // Darf Dokument von einer Krankengeschichte
                                      // aus aufgerufen werden
  short IstVerweisErzeuger;           // Ist ein Script zum Erzeugen von
                                      // Verweisen
  short IstVerweisSpeicherer;         // Ist ein Script zum Speichern von
                                      // Verweisen
  short NoMDI;                        // Verwende MDI - Logik zum Anzeigen
  char  BearbeiteSelektor[13];        // Script, das den ev. noetigen Selektor bearbeitet
  char  DefaultVerweisErzeuger[13];   // Script, das Standardmaessig zum Erzeugen von
                                      // von Verweisen verwendet wird
  char  DefaultVerweisSpeicherer[13]; // Script, das Standardmaessig zum Speichern von
                                      // von Verweisen verwendet wird
  char  OptionScript[13];             // Script, das fuer das loeschen und 
                                      // kopieren zustaendig ist

  // Weiter Informationen
  ////////////////////////////////
  WORD  AnzLocals;  // Anzahl lokale Variablen
  WORD  AnzHelps;   // Anzahl Hilfsvariablen
  WORD  AnzConsts;  // Anzahl Konstanten
  WORD  FormType;   // Siehe FT_..
  WORD  AnzTables;  // Anzahl Tabellen, die fuer das Script benoetigt
                    // werden
  DWORD  LastTimeUsed;       // Wann wurde das Programm am letzten mal
                             // geladen
  GLOBALHANDLE hData;        // Daten im Speicher (Programm und 
                             // Konstanten in einem)
#ifndef WIN32
  char reserved[2]; // in 16 Bit ist ein Handle 2 Bytes!!!!
#endif

  WORD     IconSize;    // Groesse des Icons
  LPVOID   IconData;    // Die Icondaten als solche
  WORD     PropertySize;
  LPSTR    PropertyData;
  LPBYTE   LocalTypes;
  LPBYTE   HelpTypes;
  _FuncTypeList FAR *ftlist;
  WORD     AliasDefSize;
  WORD     FuncTypeSize;
  short    AnzAlias;
  short    ExportTypeSize;
  short    ImportModuleSize;
  short    BaseModuleSize;
  short    VirtualModuleSize;
  LPVOID   ExportDef;
  LPALIASDEF AliasDef;
  LPSTR    ImportModules;
  LPSTR    BaseModules;
  LPSTR    VirtualModules;
  TableRef FAR *TRef; // [MAXTBSINENT];    // Benoetigte Tabellen

  DLLExport void _export WINAPI GetScriptData (GLOBALHANDLE FAR *hGProg,GLOBALHANDLE FAR *hGConst,LPDBRECORD FAR *constRec);
  DLLExport void _export WINAPI GetCacheScriptData (GLOBALHANDLE FAR *hGProg,GLOBALHANDLE FAR *hGConst,LPDBRECORD FAR *constRec);
  DLLExport BOOL _export WINAPI GetProperty (LPSTR Property,LPSTR buffer,int buffersize);

  WORD TRefOffs ()
    { return sizeof (*this) + IconSize + PropertySize ; }
  WORD AliasDefOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize ; }
  WORD ImportModuleOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize ; }
  WORD BaseModuleOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize ; }
  WORD VirtualModuleOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize ; }
  WORD ExportOffset ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize; }
  WORD LocalTypeOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize + ExportTypeSize ; }
  WORD HelpTypeOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize + ExportTypeSize + sizeof(BYTE) * AnzLocals ; }
  WORD FuncTypeOffs ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize + ExportTypeSize + sizeof(BYTE) * AnzLocals + sizeof(BYTE) * AnzHelps ; }
  WORD GesSize_Content ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize + ExportTypeSize ; }
  WORD GesSize_ProgStart ()
    { return sizeof (*this) + (AnzTables * sizeof(TableRef)) + IconSize + PropertySize + AliasDefSize + sizeof(BYTE) * AnzLocals + sizeof(BYTE) * AnzHelps + FuncTypeSize + ExportTypeSize + ImportModuleSize + BaseModuleSize + VirtualModuleSize; }
  void SetTypes (char huge *base);
  };
typedef ScriptContent_Entry FAR *LPSCRIPTCONTENT;

struct ScriptContent_Header {
  WORD AnzScripts;
  };
typedef ScriptContent_Header FAR *LPSCRIPTCONT;

DLLExport void _export WINAPI LoadScriptContent ();
DLLExport void _export WINAPI LoadUpdateScriptContent();
DLLExport void _export WINAPI UnloadScriptContent ();
DLLExport void _export WINAPI UnloadUpdateScriptContent ();
DLLExport void _export WINAPI FillScriptDlg (HWND hDlg,WORD Id);
DLLExport void _export WINAPI CreateScriptContent (LPSTR fName);
DLLExport void _export WINAPI CreateUpdateScriptContent(LPSTR fName);
DLLExport BOOL _export WINAPI CheckScriptContent(LPSTR fName);
DLLExport BOOL _export WINAPI CheckUpdateScriptContent(LPSTR fName);
DLLExport BOOL _export WINAPI GetScriptFName (LPSTR fName,int Sel);
DLLExport LPSCRIPTCONTENT _export WINAPI GetScriptEntry(LPSTR fName);
DLLExport LPSCRIPTCONTENT _export WINAPI GetScriptEntry(GLOBALHANDLE hGmem);
DLLExport LPSCRIPTCONTENT _export WINAPI DDSCopyScriptEntry(LPSCRIPTCONTENT schd);
DLLExport void _export WINAPI AddScriptEntry(LPSTR fName, LPSCRIPTCONTENT schd);
DLLExport void _export WINAPI ClearCachedScript(LPSTR Name);
DLLExport LPSCRIPTCONTENT _export WINAPI GetFirstScript (int anzProperty = 0,LPSTR FAR *property = NULL,LPSTR Name = NULL);
DLLExport LPSCRIPTCONTENT _export WINAPI GetNextScript (LPSCRIPTCONTENT prev,int anzProperty = 0,LPSTR FAR *property = NULL,LPSTR Name = NULL);
DLLExport LPSCRIPTCONTENT _export WINAPI GetFirstUpdateScript ();
DLLExport LPSCRIPTCONTENT _export WINAPI GetNextUpdateScript (LPSCRIPTCONTENT prev);
DLLExport void _export WINAPI SetHDataNULL (LPSTR fName);

BOOL GenerateScript (HWND hWnd,LPSTR fName);
#pragma pack()

DLLExport int _export WINAPI GetTableNr (LPSCRIPTCONTENT ent,WORD FAR *TableID,WORD FAR *Version,LPSTR TableName);
DLLExport void _export WINAPI FreeScriptData(GLOBALHANDLE FAR *hGProg,GLOBALHANDLE hGConst,LPDBRECORD constRec,LPSTR Name);

#ifdef STRKEY
DLLExport hash FAR *_export WINAPI GetFuncHash ();
#endif
DLLExport void _export WINAPI ClearFuncHash();

