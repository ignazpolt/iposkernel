/*---------------------------------------------------------------------------\
* Rechtschreibprüfung
*
* $Header:   P:/marille/clinicum/include/rev/cspell.h_v   1.1   16 Jul 1999 12:43:44   Gerhold  $
* $Log:   P:/marille/clinicum/include/rev/cspell.h_v  $
 * 
 *    Rev 1.1   16 Jul 1999 12:43:44   Gerhold
 * Fuunktionsdeklaration auf CDECL gesetzt...
 * 
 *    Rev 1.0   16 Mar 1999 17:03:50   Gerhold
 * Initial revision.
\----------------------------------------------------------------------------*/
#ifndef __CSPELL_H__
#define __CSPELL_H__


//#define MAXMDR 10
//#define MAXUDR 10

/////////////////////////////////////////////////////////////////////////////
// Typdefinitionen der DLL-Funktionen

typedef SEC (CDECL *SPELLVERPROC)(WORD FAR *, WORD FAR *, WORD FAR *);
typedef SEC (CDECL *SPELLINITPROC)(SPLID FAR *, WSC FAR *);
typedef SEC (CDECL *SPELLOPTIONSPROC)(SPLID, LONG);
typedef SEC (CDECL *SPELLCHECKPROC)(SPLID, SCCC, LPSIB, LPSRB);
typedef SEC (CDECL *SPELLTERMINATEPROC)(SPLID, BOOL);
typedef SEC (CDECL *SPELLVERIFYMDRPROC)(LPCSTR, LID, LID FAR *);
typedef SEC (CDECL *SPELLOPENMDRPROC)(SPLID, LPCSTR, LPCSTR, BOOL, BOOL, LID, LPMDRS);
typedef SEC (CDECL *SPELLOPENUDRPROC)(SPLID, LPCSTR, BOOL, WORD, UDR FAR *, BOOL FAR *);
typedef SEC (CDECL *SPELLADDUDRPROC)(SPLID, UDR, LPCSTR);
typedef SEC (CDECL *SPELLADDCHANGEUDRPROC)(SPLID, UDR, LPCSTR, LPCSTR);
typedef SEC (CDECL *SPELLDELUDRPROC)(SPLID, UDR, LPCSTR);
typedef SEC (CDECL *SPELLCLEARUDRPROC)(SPLID, UDR);
typedef SEC (CDECL *SPELLGETSIZEUDRPROC)(SPLID, UDR, WORD FAR *);
typedef SEC (CDECL *SPELLGETLISTUDRPROC)(SPLID, UDR, WORD, LPSRB);
typedef SEC (CDECL *SPELLCLOSEMDRPROC)(SPLID, LPMDRS);
typedef SEC (CDECL *SPELLCLOSEUDRPROC)(SPLID, UDR, BOOL);

/////////////////////////////////////////////////////////////////////////////
// Strukturen zur Speicherung der Daten offener Haupt- und
//  Benutzerwörterbücher

struct MdrDataStruct
  {
  MDRS mdrs;                         // IDs des Wörterbuchs
  char sMdrPath[MAX_PATH];           // Pfad des Hauptwörterbuchs
  char sExclusionPath[MAX_PATH];     // Pfad des Ausschlußwörterbuchs
  MdrDataStruct *Next;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  };
typedef MdrDataStruct *LPMDRDATASTRUCT;


class MdrContainer
  {
 public:
  LPMDRDATASTRUCT MDRData;

  MdrContainer ()
    {
    MDRData = NULL;
    }

  virtual ~MdrContainer ()
    {
    if (MDRData != NULL)
      delete MDRData;
    }

  void Add (LPMDRDATASTRUCT lpmdr) 
    {
    for (LPMDRDATASTRUCT h = MDRData; (h != NULL) && (h->Next != NULL); h = h->Next);

    LPMDRDATASTRUCT p = new MdrDataStruct;
    lmemcpy (LPMDRDATASTRUCT(p), (LPMDRDATASTRUCT)lpmdr, sizeof(MdrDataStruct));
    p->Next = NULL;

    if (h != NULL)
      h->Next = p;
    else
      MDRData = p;
    }

  int GetSize ()
    {
    int i = 0;
    for (LPMDRDATASTRUCT h = MDRData ; h != NULL; h = h->Next, i++);
    return i;
    }

  LPMDRDATASTRUCT GetAt (int Index)
    {
    int i = 0;
    for (LPMDRDATASTRUCT h = MDRData; h != NULL; h = h->Next, i++)
      if (i == Index)
        return h;

    return NULL;
    }

  const LPMDRDATASTRUCT operator[](const int Index) const;

  void RemoveAt (int Index)
    {
    LPMDRDATASTRUCT p = NULL;
    int i = 0;
    for (LPMDRDATASTRUCT h = MDRData; (i != Index) && (h != NULL); p = h, h = h->Next, i++);

    if (h != NULL) {
      if (p != NULL)       // Ist das das erste Element in der Liste?
        p->Next = h->Next; // nein
      else
        MDRData = h->Next; // ja. Dann muss der Listenheader geaendert werden

      delete h;
      }
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };
typedef MdrContainer *LPMDRCONTAINER;


struct UdrDataStruct
  {
  UDR udr;                       // ID des Benutzerwörterbuchs
  WORD nType;                    // Typ des Benutzerwörterbuchs
  BOOL bReadOnly;                // Flag für Nur Lesen
  char sUdrPath[MAX_PATH];       // Pfad des Benutzerwörterbuchs
  UdrDataStruct *Next;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };
typedef UdrDataStruct *LPUDRDATASTRUCT;


class UdrContainer
  {
 public:
  LPUDRDATASTRUCT UDRData;

  UdrContainer ()
    {
    UDRData = NULL;
    }

  virtual ~UdrContainer ()
    {
    if (UDRData != NULL)
      delete UDRData;
    }

  void Add (LPUDRDATASTRUCT lpudr) 
    {
    for (LPUDRDATASTRUCT h = UDRData; (h != NULL) && (h->Next != NULL); h = h->Next);

    LPUDRDATASTRUCT p = new UdrDataStruct;
    lmemcpy (LPUDRDATASTRUCT(p), (LPUDRDATASTRUCT)lpudr, sizeof(UdrDataStruct));
    p->Next = NULL;

    if (h != NULL)
      h->Next = p;
    else
      UDRData = p;
    }

  int GetSize ()
    {
    int i = 0;
    for (LPUDRDATASTRUCT h = UDRData ; h != NULL; h = h->Next, i++);
    return i;
    }

  LPUDRDATASTRUCT GetAt (int Index)
    {
    int i = 0;
    for (LPUDRDATASTRUCT h = UDRData; h != NULL; h = h->Next, i++)
      if (i == Index)
        return h;

    return NULL;
    }

  const LPUDRDATASTRUCT operator[](const int Index) const;

  void RemoveAt (int Index)
    {
    LPUDRDATASTRUCT p = NULL;
    int i = 0;
    for (LPUDRDATASTRUCT h = UDRData; (i != Index) && (h != NULL); p = h, h = h->Next, i++);

    if (h != NULL) {
      if (p != NULL)       // Ist das das erste Element in der Liste?
        p->Next = h->Next; // nein
      else
        UDRData = h->Next; // ja. Dann muss der Listenheader geaendert werden

      delete h;
      }
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };
typedef UdrContainer *LPUDRCONTAINER;



struct UINTArray
  {
  UINT Value;
  UINTArray *Next;
  };




struct StringArray {
  LPSTR        lpszText;
  StringArray *Next;

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };


/////////////////////////////////////////////////////////////////////////////
// Wrapperklasse für Spell Return Buffer 

class CSrb
{
// Data
public:
  SRB srb;  // SRB-Struktur, verwendet bei der Rückgabe von Daten aus
        //  CSAPI-Funktionen

protected:
    // Index des Strings, auf die der Zeiger
    //  pszLastReturnString weist.
  int nLastReturnStringIndex;
    // Zeiger auf den nächsten Ergebnisstring
  LPCSTR pszLastReturnString;

// Construction/Destruction
public:
  CSrb();
  ~CSrb();

// Operations
public:
    /////////////////////////////////////////////////////////////////////
    // Init():
    //  legt Puffer für SRB an
    //
    // Parameter:
    //      BOOL bLarge: Größe der reservierten Puffer
    //            TRUE: großer Puffer für große Datenmengen
    //             FALSE: kleiner Puffer für geringe Datenmengen
    //
    // Rückgabewert:
    //    TRUE: Initialisierung gelungen
    //    FALSE: Initialisierung mißlungen, Speicher nicht reserviert
    //
  BOOL Init(BOOL bLarge = FALSE);

    /////////////////////////////////////////////////////////////////////
    // GetReturnString(): liefert den indizierten Rückgabestring aus
    //    dem Spell Return Buffer
    //
    // Parameter:
    //     int nString: Index des gewünschten Strings (zählt ab 0)
    //
    //     CString* sResult: Zeiger auf CString, in den der gewünschte
    //      Ergebnisstring eingetragen wird
    //
    // Rückgabewert:
    //    TRUE: Gewünschter String wurde in sResult eingetragen
    //    FALSE: Operation mißlungen
    //
  BOOL GetReturnString(int nString, LPSTR sResult);
  
};

/////////////////////////////////////////////////////////////////////////////
// Default-Ländercode
  
  // Deutsch/Deutschland
#define DEFAULT_COUNTRY 1031

/////////////////////////////////////////////////////////////////////////////
// Default-Sprache für Wörterbücher

#define DEFAULT_LID lidGerman

//---------------------------------------------------------------------------
// Klasse zur Kapselung der Common Speller API
// Die Klasse CSpellSession repräsentiert eine Rechtschreibsitzung
//---------------------------------------------------------------------------
class CSpellSession
  {

  // Data

 protected:

  // Handle der geöffneten Rechtschreib-DLL
  HINSTANCE hinstSpellDLL;

  // Zeiger auf die Funktionen der CSAPI-DLL
  SPELLVERPROC          lpfnSpellVer;
  SPELLINITPROC         lpfnSpellInit;
  SPELLOPTIONSPROC      lpfnSpellOptions;
  SPELLCHECKPROC        lpfnSpellCheck;
  SPELLTERMINATEPROC    lpfnSpellTerminate;
  SPELLVERIFYMDRPROC    lpfnSpellVerifyMdr;
  SPELLOPENMDRPROC      lpfnSpellOpenMdr;
  SPELLOPENUDRPROC      lpfnSpellOpenUdr;
  SPELLADDUDRPROC       lpfnSpellAddUdr;
  SPELLADDCHANGEUDRPROC lpfnSpellAddChangeUdr;
  SPELLDELUDRPROC       lpfnSpellDelUdr;
  SPELLCLEARUDRPROC     lpfnSpellClearUdr;
  SPELLGETSIZEUDRPROC   lpfnSpellGetSizeUdr;
  SPELLGETLISTUDRPROC   lpfnSpellGetListUdr;
  SPELLCLOSEMDRPROC     lpfnSpellCloseMdr;
  SPELLCLOSEUDRPROC     lpfnSpellCloseUdr;

  // ID der Rechtschreibsitzung
  SPLID lSpellID;
  
  // Fehlercode des zuletzt beim Aufruf der Rechtschreib-DLL
  //  aufgetretenen Fehlers
  SEC secLastError;

  // vom Benutzer zuletzt gesetzte Optionen
  LONG lSpellOptions;

  // Container zum Speichern der Daten geöffneter
  //  Haupt- und Benutzerwörterbücher

//  int iActMdr;
//  int iActUdr;

  LPMDRCONTAINER  MdrArray;
  LPUDRCONTAINER  UdrArray;
//  LPMDRDATASTRUCT MdrArray[MAXMDR];
//  LPUDRDATASTRUCT UdrArray[MAXUDR];

  // Felder mit den Kennungen der geöffneten
  //  Haupt- und Benutzerwörterbücher (zur Übergabe an
  //  die Funktion SpellCheck)
  MDR* rgMdr;
  UDR* rgUdr;
  
// Construction/Destruction
public:
  DLLExport _export CSpellSession();
  DLLExport _export ~CSpellSession();

// Operations
public:
    /////////////////////////////////////////////////////////////////////
    // QueryDLLFileName():
    //    Namen und Pfad der Rechtschreib-DLL aus WIN.INI/Registry
    //    ermitteln
    //
    // Parameter:
    //      CString* psDllFileName: Zeiger auf String, in den der Pfad
    //      der DLL eingetragen wird
    //    WORD nCountryCode: Gewünschte Sprachversion
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen, DLL-Name eingetragen
    //    FALSE: Operation mißlungen, DLL-Name nicht ermittelt
    //
  BOOL QueryDLLFileName(LPSTR psDllFileName,
    WORD nCountryCode = DEFAULT_COUNTRY);

    /////////////////////////////////////////////////////////////////////
    // QueryMdrFileName():
    //    Namen und Pfad des Standard-Hauptwörterbuchs aus
    //    WIN.INI/Registry ermitteln
    //
    // Parameter:
    //      CString* psMdrFileName: Zeiger auf String, in den der Pfad
    //      des Standardwörterbuchs eingetragen wird
    //    WORD nCountryCode: Gewünschte Sprachversion
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen, Hauptwörterbuch-Name eingetragen
    //    FALSE: Operation mißlungen, Hauptwörterbuch-Name nicht
    //      ermittelt
    //
  BOOL QueryMdrFileName(LPSTR psMdrFileName,
    WORD nCountryCode = DEFAULT_COUNTRY);

    /////////////////////////////////////////////////////////////////////
    // QueryUdrFileNames():
    //     Namen und Pfade der Benutzerwörterbücher aus WIN.INI/Registry
    //     ermitteln
    //
    // Parameter:
    //    int* pnUdrNum: Zeiger auf Integer, in den die Anzahl der
    //      gefundenen Benutzerwörterbücher eingetragen wird
    //      CString* psMdrFileName: Zeiger auf String-Container, in den
    //      die Pfade der Benutzerwörterbücher eingetragen werden
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen, Wörterbuch-Namen eingetragen
    //    FALSE: Operation mißlungen, Wörterbuch-Namen nicht
    //      ermittelt
    //
  BOOL QueryUdrFileNames(int* pnUdrNum, StringArray *pUdrFiles);
    
    /////////////////////////////////////////////////////////////////////
    // OpenSpellDLL():
    //     Rechtschreib-DLL öffnen
    //
    // Parameter:
    //      LPCSTR lpszDLL: Name der DLL
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen, DLL ist geöffnet
    //    FALSE: Operation mißlungen, DLL konnte nicht geöffnet werden
    //
  BOOL OpenSpellDLL(LPCSTR lpszDLL);

    /////////////////////////////////////////////////////////////////////
    // CloseSpellDLL():
    //     Rechtschreib-DLL schließen
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    keiner
    //
  void CloseSpellDLL();

    /////////////////////////////////////////////////////////////////////
    // InitSession():
    //     Rechtschreib-Sitzung starten
    //
    // Parameter:
    //      WSC FAR *lpWsc: Zeiger auf WSC-Struktur mit zu ignorierenden
    //      Zeichencodes
    //
    // Rückgabewert:
    //    TRUE: Initialisierung gelungen
    //    FALSE: Initialisierung mißlungen
    //
  BOOL InitSession(WSC FAR *lpWsc = NULL);

    /////////////////////////////////////////////////////////////////////
    // TerminateSession():
    //     Rechtschreib-Sitzung beenden
    //
    // Parameter:
    //      BOOL bForce: TRUE: Schließen auch bei Fehler erzwingen
    //
    // Rückgabewert:
    //    TRUE: Schließen gelungen
    //    FALSE: Schließen mißlungen, Sitzung noch offen
    //
  BOOL TerminateSession(BOOL bForce = FALSE);

    /////////////////////////////////////////////////////////////////////
    // InitFromRegistry():
      //    Registry/WIN.INI auslesen und mit diesen Angaben
      //     Rechtschreib-DLL öffnen, Rechtschreibsitzung initialisieren
      //     und Haupt- und Benutzerwörterbücher öffnen
    //
    // Parameter:
    //      BOOL bOpenCustomDicts: Flag, ob die Benutzerwörterbücher,
    //      deren Namen in der in Registry/WIN.INI gefunden wurden,
    //      geöffnet werden sollen
    //
    // Rückgabewert:
    //    TRUE: Initialisierung gelungen
    //    FALSE: Initialisierung mißlungen, Sitzung nicht geöffnet
    //
  DLLExport BOOL _export InitFromRegistry(BOOL bOpenCustomDicts = TRUE);

    /////////////////////////////////////////////////////////////////////
    // SpellVer():
    //    Versionsnummern der Rechtschreib-DLL ermitteln
    //
    // Parameter:
    //      WORD FAR *lpwVer: Zeiger auf WORD, in das die Versionsnummer
    //      eingetragen wird
    //    WORD FAR *lpwIdEngine: Zeiger auf WORD, in das die Engine-ID
    //      eingetragen wird
    //    WORD FAR *lpwSpellType: Zeiger auf WORD, in das die
    //      Fähigkeiten der eingetragen wird
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL SpellVer(WORD FAR *lpwVer, WORD FAR *lpwIdEngine,
    WORD FAR *lpwSpellType);

    /////////////////////////////////////////////////////////////////////
    // HasWildcardSupport():
    //     Ermittelt, ob die Rechtschreib-DLL Wortmasken unterstützt
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    TRUE: Rechtschreib-DLL unterstützt Wortmasken
    //    FALSE: Rechtschreib-DLL unterstützt keine Wortmasken
    //
  BOOL HasWildcardSupport();

    /////////////////////////////////////////////////////////////////////
    // HasMultiDictSupport():
    //    Ermittelt, ob die Rechtschreib-DLL mehrere Hauptwörterbücher
    //     unterstützt
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    TRUE: Rechtschreib-DLL unterstützt mehrere Hauptwörterbücher
    //    FALSE: Rechtschreib-DLL unterstützt nicht mehrere
    //      Hauptwörterbücher
    //
  BOOL HasMultiDictSupport();

    /////////////////////////////////////////////////////////////////////
    // HasHyphenationSupport():
    //    Ermittelt, ob die Rechtschreib-DLL Angaben zur Worttrennung
    //     liefern kann
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    TRUE: Rechtschreib-DLL unterstützt Worttrennung
    //    FALSE: Rechtschreib-DLL unterstützt keine Worttrennung
    //
  BOOL HasHyphenationSupport();
  
    /////////////////////////////////////////////////////////////////////
    // SetOptions():
    //    Optionen für Rechtschreibsitzung festlegen
    //
    // Parameter:
    //      long lOptions: neue Optionen
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export SetOptions(long lOptions);

    /////////////////////////////////////////////////////////////////////
    // GetOptions():
    //    Zuletzt gesetzte Optionen für Rechtschreibsitzung ermitteln
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    Zuletzt gesetzte Optionen
    //
  DLLExport long _export GetOptions();

    /////////////////////////////////////////////////////////////////////
    // OpenMdr():
    //    Hauptwörterbuch öffnen
    //
    // Parameter:
    //      LPCSTR lpszMdrName:  Pfad des Hauptwörterbuchs
    //    LPCSTR lpszExcName: Pfad des Ausschlußwörterbuchs, wird
    //      hier NULL übergeben, wird kein Ausschlußwörterbuch
    //      geöffnet
    //    BOOL bCreateUdrExc: Flag, ob das Ausschlußwörterbuch
    //      erzeugt werden soll, wenn es nicht existiert
    //    LID lidExpected: ID der gewünschten Sprache
    //    BOOL bCache: Flag, ob das Hauptwörterbuch gepuffert werden
    //      soll
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL OpenMdr(LPCSTR lpszMdrName, LPCSTR lpszExcName = NULL,
    BOOL bCreateUdrExc = FALSE, LID lidExpected = DEFAULT_LID,
    BOOL bCache = TRUE);

    /////////////////////////////////////////////////////////////////////
    // CloseMdr():
    //    Hauptwörterbuch schließen
    //
    // Parameter:
    //      int nMdr: Index des zu schließenden Hauptwörterbuchs im
    //      Container MdrArray
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL CloseMdr(int nMdr);

    /////////////////////////////////////////////////////////////////////
    // GetMdrNum():
    //     Anzahl der offenen Hauptwörterbücher ermitteln
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    Anzahl der offenen Hauptwörterbücher
    //
  int GetMdrNum();

    /////////////////////////////////////////////////////////////////////
    // GetMdrData():
    //     Daten eines offenen Hauptwörterbuchs ermitteln
    //
    // Parameter:
    //      int nMdr: Index des Hauptwörterbuchs im Container MdrArray
    //    MdrDataStruct* pMdrData: Zeiger auf Struktur, in die die
    //      Daten des Hauptwörterbuchs eingetragen werden
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetMdrData(int nMdr, MdrDataStruct* pMdrData);
  
    /////////////////////////////////////////////////////////////////////
    // OpenUdr():
    //     Benutzerwörterbuch öffnen
    //
    // Parameter:
    //      LPCSTR lpszUdrName:  Pfad des Benutzerwörterbuchs
    //    WORD nType: Gewünschter Typ des Benutzerwörterbuchs
    //    BOOL bCreate: Flag, ob das Benutzerwörterbuch
    //      erzeugt werden soll, wenn es nicht existiert
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export OpenUdr(LPCSTR lpszUdrName, WORD nType = IgnoreAlwaysProp,
    BOOL bCreate = FALSE);

    /////////////////////////////////////////////////////////////////////
    // CloseUdr():
    //     Benutzerwörterbuch schließen
    //
    // Parameter:
    //      int nUdr: Index des zu schließenden Benutzerwörterbuchs im
    //      Container UdrArray
    //      BOOL bForce: Flag, ob auch bei einem Dateifehler das
    //      Schließen erzwungen werden soll
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export CloseUdr(int nUdr, BOOL bForce = FALSE);

    /////////////////////////////////////////////////////////////////////
    // GetUdrNum():
    //     Anzahl der offenen Benutzerwörterbücher (ohne
    //    RAM-Cache-Listen) ermitteln
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    Anzahl der offenen Benutzerwörterbücher
    //
  int GetUdrNum();

    /////////////////////////////////////////////////////////////////////
    // GetUdrData():
    //     Daten eines offenen Benutzerwörterbuchs ermitteln
    //
    // Parameter:
    //      int nUdr: Index des Benutzerwörterbuchs im Container
    //      UdrArray
    //    UdrDataStruct* pUdrData: Zeiger auf Struktur, in die die
    //      Daten des Benutzerwörterbuchs eingetragen werden
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetUdrData(int nUdr, UdrDataStruct* pUdrData);

    /////////////////////////////////////////////////////////////////////
    // AddToUdr():
    //     Neuen Eintrag in Benutzerwörterbuch einfügen
    //
    // Parameter:
    //      int nUdr: Index des Benutzerwörterbuchs im Container
    //      UdrArray
    //    LPCSTR lpszAdd: Neu einzutragendes Wort
    //    LPCSTR lpszChangeTo: Bei Benutzerwörterbüchern vom Typ
    //      "Change Once" oder "Change Always" das Ersatzwort,
    //      sonst NULL
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export AddToUdr(int nUdr, LPCSTR lpszAdd, LPCSTR lpszChangeTo = NULL);

    /////////////////////////////////////////////////////////////////////
    // AddToRAMCacheList():
    //     Neuen Eintrag in RAM-Cache-Liste einfügen
    //
    // Parameter:
    //      UDR udr: ID der RAM-Cache-Liste
    //    LPCSTR lpszAdd: Neu einzutragendes Wort
    //    LPCSTR lpszChangeTo: Bei den RAM-Cache-Listen
    //      "Change Once" oder "Change Always" das Ersatzwort,
    //      sonst NULL
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export AddToRAMCacheList(UDR udr, LPCSTR lpszAdd,
    LPCSTR lpszChangeTo = NULL);

    /////////////////////////////////////////////////////////////////////
    // DelFromUdr():
    //     Eintrag aus Benutzerwörterbuch löschen
    //
    // Parameter:
    //      int nUdr: Index des Benutzerwörterbuchs im Container
    //      UdrArray
    //    LPCSTR lpszDel: Zu löschender Eintrag. Bei
    //      Benutzerwörterbüchern vom Typ "Change Once" oder
    //      "Change Always" nur der erste Teile des Wortpaars
    //      (d.h. das zu ersetzende Wort)
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export DelFromUdr(int nUdr, LPCSTR lpszDel);

    /////////////////////////////////////////////////////////////////////
    // DelFromRAMCacheList():
    //     Eintrag aus RAM-Cache-Liste löschen
    //
    // Parameter:
    //      UDR udr: ID der RAM-Cache-Liste
    //    LPCSTR lpszDel: Zu löschender Eintrag. Bei
    //      den RAM-Cache-Listen "Change Once" oder
    //      "Change Always" nur der erste Teile des Wortpaars
    //      (d.h. das zu ersetzende Wort)
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export DelFromRAMCacheList(UDR udr, LPCSTR lpszDel);

    /////////////////////////////////////////////////////////////////////
    // ClearRAMCacheList():
    //     RAM-Cache-Liste komplett löschen
    //
    // Parameter:
    //      UDR udr: ID der RAM-Cache-Liste
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export ClearRAMCacheList(UDR udr);

    /////////////////////////////////////////////////////////////////////
    // GetUdrEntryNum():
    //     Anzahl der Einträge in einem Benutzerwörterbuch ermitteln
    //
    // Parameter:
    //      int nUdr: Index des Benutzerwörterbuchs im Container
    //      UdrArray
    //    int *pnEntryNum: Zeiger auf einen Integer, in den die Anzahl
    //      der Wörterbucheinträge eingetragen wird. Bei
    //      Benutzerwörterbüchern vom Typ "Change Once" oder
    //      "Change Always" gilt das Paar aus zu ersetzendem Wort und
    //      Ersatzwort als ein Eintrag.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetUdrEntryNum(int nUdr, int *pnEntryNum);

    /////////////////////////////////////////////////////////////////////
    // GetRAMCacheListEntryNum():
    //     Anzahl der Einträge in einer RAM-Cache-Liste ermitteln
    //
    // Parameter:
    //      UDR udr: ID der RAM-Cache-Liste
    //    int *pnEntryNum: Zeiger auf einen Integer, in den die Anzahl
    //      der Wörterbucheinträge eingetragen wird. Bei
    //      den RAM-Cache-Listen "Change Once" oder
    //      "Change Always" gilt das Paar aus zu ersetzendem Wort und
    //      Ersatzwort als ein Eintrag.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetRAMCacheListEntryNum(UDR udr, int *pnEntryNum);

    /////////////////////////////////////////////////////////////////////
    // GetUdrEntries():
    //     Einträge eines Benutzerwörterbuchs auslesen
    //
    // Parameter:
    //      int nUdr: Index des Benutzerwörterbuchs im Container
    //      UdrArray
    //    CStringArray* pEntries: Zeiger auf einen String-Container, in
    //      den die Wörterbucheinträge eingetragen werden
    //    CStringArray* pChangeTo: Zeiger auf einen String-Container,
    //      in den bei Benutzerwörterbüchern vom Typ "Change Once"
    //      oder "Change Always" die Ersatzwörter eingetragen werden.
    //      Bei "Ignore"-Wörterbuchtypen kann der Parameter NULL
    //      sein.
    //    int nStartEntry: Index des Wörterbucheintrags, ab dem die
    //      Einträge ausgelesen werden sollen
    //    int nMaxEntryNum: Maximale Anzahl der auszulesenden Einträge.
    //      Ein negativer Wert bedeutet, daß soviele geholt werden,
    //      wie vorhanden sind.
    //    int nStartArrayIndex: Index im String-Container, ab dem
    //      die Wörterbucheinträge abgelegt werden sollen
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetUdrEntries(int nUdr, LPSTR /*CStringArray* */ pEntries,
    LPSTR /*CStringArray* */ pChangeTo = NULL, int nStartEntry = 0,
    int nMaxEntryNum = -1, int nStartArrayIndex = 0);

    /////////////////////////////////////////////////////////////////////
    // GetRAMCacheListEntries():
    //     Einträge einer RAM-Cache-Liste auslesen
    //
    // Parameter:
    //      UDR udr: ID der RAM-Cache-Liste
    //    CStringArray* pEntries: Zeiger auf einen String-Container, in
    //      den die Wörterbucheinträge eingetragen werden
    //    CStringArray* pChangeTo: Zeiger auf einen String-Container,
    //      in den bei den RAM-Cache-Listen "Change Once"
    //      oder "Change Always" die Ersatzwörter eingetragen werden.
    //      Bei der "Ignore"-RAM-Cache-Listen kann der Parameter NULL
    //      sein.
    //    int nStartEntry: Index des Wörterbucheintrags, ab dem die
    //      Einträge ausgelesen werden sollen
    //    int nMaxEntryNum: Maximale Anzahl der auszulesenden Einträge.
    //      Ein negativer Wert bedeutet, daß soviele geholt werden,
    //      wie vorhanden sind.
    //    int nStartArrayIndex: Index im String-Container, ab dem
    //      die Wörterbucheinträge abgelegt werden sollen
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL GetRAMCacheListEntries(UDR udr, LPSTR /*CStringArray* */ pEntries,
    LPSTR /*CStringArray* */ pChangeTo = NULL, int nStartEntry = 0,
    int nMaxEntryNum = -1, int nStartArrayIndex = 0);

    /////////////////////////////////////////////////////////////////////
    // CheckWord():
    //     Ein Wort überprüfen
    //
    // Parameter:
    //      LPCSTR lpszBuffer: Zu überprüfendes Wort
    //    SCRS* pScrs: Zeiger auf SCRS-Variable, in die das Ergebnis
    //      der Rechtschreibprüfung eingetragen wird.
    //    UINT* pnErrorPos: Zeiger auf UINT-Variable, in die die
    //      Position eines eventuell gefundenen Fehlers eingetragen
    //      wird.
    //    CString* psChange: Zeiger auf String, in den ein eventuell
    //      gefundenes Ersatzwort eingetragen wird. Dieser Parameter
    //      kann NULL sein, wenn diese Information nicht gebraucht
    //      wird.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL CheckWord(LPCSTR lpszBuffer, SCRS* pScrs, UINT* pnErrorPos,
    LPSTR psChange = NULL);

    /////////////////////////////////////////////////////////////////////
    // CheckBuffer():
    //     Fortlaufende Sätze überprüfen
    //
    // Parameter:
    //      LPCSTR lpszBuffer: Zu überprüfender Text
    //    SCRS* pScrs: Zeiger auf SCRS-Variable, in die das Ergebnis
    //      der Rechtschreibprüfung eingetragen wird.
    //    UINT* pnErrorPos: Zeiger auf UINT-Variable, in die die
    //      Position eines eventuell gefundenen Fehlers eingetragen
    //      wird.
    //    WORD nSpellState: Status-Anweisung für Übergabe an SpellCheck
    //    CString* psChange: Zeiger auf String, in den ein eventuell
    //      gefundenes Ersatzwort eingetragen wird. Dieser Parameter
    //      kann NULL sein, wenn diese Information nicht gebraucht
    //      wird.
    //    UINT* pnErrorLength: Zeiger auf UINT-Variable, in die die
    //      Länge eines eventuell gefundenen Fehlerworts eingetragen
    //      wird.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export CheckBuffer(LPCSTR lpszBuffer, SCRS* pScrs, UINT* pnErrorPos,
    WORD nSpellState = fssIsContinued, LPSTR psChange = NULL,
    UINT* pnErrorLength = NULL);

    /////////////////////////////////////////////////////////////////////
    // Suggestion():
    //     Alternativvorschläge für ein Wort holen
    //
    // Parameter:
    //      LPCSTR lpszWord: Wort, für das Alternativvorschläge
    //      gesucht werden
    //    CStringArray* pSuggestions: Zeiger auf einen
    //      String-Container, in den die Alternativvorschläge
    //      eingetragen werden
    //    WORD nSpellState: Status-Anweisung für Übergabe an SpellCheck
    //    int nMaxEntryNum: Maximale Anzahl der zu liefernden
    //      Alternativvorschläge. Ein negativer Wert bedeutet, daß
    //      soviele geholt werden, wie vorhanden sind.

    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export Suggestion(LPCSTR lpszWord, LPSTR *pSuggestions,
    WORD nSpellState = fssNoStateInfo, int nMaxEntryNum = -1);

    /////////////////////////////////////////////////////////////////////
    // Anagram():
    //     Anagramme holen
    //
    // Parameter:
    //      LPCSTR lpszWord: Wort, für das Anagramme gesucht werden
    //    CStringArray* pAnagrams: Zeiger auf einen
    //      String-Container, in den die Anagramme
    //      eingetragen werden
    //    int nMaxEntryNum: Maximale Anzahl der zu liefernden
    //      Anagramme. Ein negativer Wert bedeutet, daß soviele
    //      geholt werden, wie vorhanden sind.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export Anagram(LPCSTR lpszWord, LPSTR *pAnagrams,
    int nMaxEntryNum = -1);

    /////////////////////////////////////////////////////////////////////
    // Wildcard():
    //     Worte holen, die auf eine Wildcard (Wortmaske) passen
    //
    // Parameter:
    //      LPCSTR lpszWord: Wildcard, für die passende Worte gesucht
    //      werden
    //    CStringArray* pWildcards: Zeiger auf einen
    //      String-Container, in den die gefundenen Worte
    //      eingetragen werden
    //    int nMaxEntryNum: Maximale Anzahl der zu liefernden
    //      Worte. Ein negativer Wert bedeutet, daß soviele
    //      geholt werden, wie vorhanden sind.
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  DLLExport BOOL _export Wildcard(LPCSTR lpszWord, LPSTR *pWildcards,
    int nMaxEntryNum = -1);

    /////////////////////////////////////////////////////////////////////
    // Hyphenation():
    //     Hinweise zur Worttrennung holen
    // !!! Momentan nicht implementiert !!!
    //
    // Parameter:
    //      LPCSTR lpszWord: Wort, für das Hinweise zur Worttrennung
    //      gesucht werden
    //      int* pnHyphNum: Zeiger auf Integer, in den die Anzahl der
    //      Trennungspunkte eingetragen wird
    //    CUIntArray* pHyphPoints: Zeiger auf UINT-Container, in den
    //      die Positionen der Trennungspunkte eingetragen werden
    //    CUIntArray* pHyphTypes: Zeiger auf UINT-Container, in den
    //      die Typen der Trennungspunkte eingetragen werden
    //
    // Rückgabewert:
    //    TRUE: Operation gelungen
    //    FALSE: Operation mißlungen
    //
  BOOL Hyphenation(LPCSTR lpszWord, int* pnHyphNum,
    UINTArray* pHyphPoints, UINTArray* pHyphTypes);
  
    /////////////////////////////////////////////////////////////////////
    // GetLastError():
    //     Fehlercode des zuletzt beim Aufruf der Rechtschreib-DLL
    //    aufgetretenen Fehlers ermitteln
    //
    // Parameter:
    //      keine
    //
    // Rückgabewert:
    //    Zuletzt aufgetretener Fehler
    //
  SEC GetLastError();

// Implementation
public:

    // Fehlercode des zuletzt beim Aufruf der Rechtschreib-DLL
    //  aufgetretenen Fehlers festsetzen
  void SetLastError(SEC secResult);

    // Hilfsfunktion zum Auslesen der Einträge aus einem
    //  Benutzerwörterbuch oder einer RAM-Cache-Liste
  BOOL ReadUdrEntries(UDR udr, LPSTR /*CStringArray* */ pEntries,
    LPSTR /*CStringArray* */ pChangeTo, int nStartEntry, int nMaxEntryNum,
    int nStartArrayIndex, BOOL bHasWordPairs);

    // Hilfsfunktion zum Holen von Anagrammen oder Wildcards
  BOOL GetSimpleCheckList(SCCC sccc, LPCSTR lpszWord,
    LPSTR *pResult, int nMaxEntryNum);

    // neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
  BOOL RebuildDRLists();

};

#endif // __CSPELL_H__
