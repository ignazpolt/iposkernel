/*
**      Strukturen zum Zugriff auf die Lokalen Daten
*/
// $Header:   P:/marille/clinicum/include/rev/data.hpv   1.1   02 Feb 1996 11:01:12   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/data.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:01:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.26   17 Jan 1994 17:30:06   HANNES
// Reinitialize: Neulesen eines im System vorhandenen Datensatzes
// 
//    Rev 1.25   04 Jan 1994 17:04:50   HANNES
// Recall - Daten
// 
//    Rev 1.24   09 Dec 1993 15:05:16   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.23   29 Nov 1993 08:46:20   HANNES
// 
//    Rev 1.22   16 Nov 1993 04:24:24   HANNES
// Verallgemeinerung der Benutzerdatenbank
// 
//    Rev 1.21   18 Oct 1993 19:51:46   HANNES
// WriteDocCnfData
// 
//    Rev 1.20   11 Oct 1993 11:43:08   HANNES
// Prototypen zur Datenkonvertierung, Benutzerdatenhandling
// 
//    Rev 1.19   06 Oct 1993 09:51:46   HANNES
// BEMERKUNGENKEY
// 
//    Rev 1.18   24 Sep 1993 22:44:04   HANNES
// Help - Daten
// 
//    Rev 1.17   05 Sep 1993 22:07:32   HANNES
// 
//    Rev 1.16   18 Aug 1993 10:38:20   HANNES
// ClosePatRecs..
// 
//    Rev 1.15   13 Jul 1993 11:08:46   HANNES
// SetNewPatRef
// 
//    Rev 1.14   12 Jul 1993 07:53:46   HANNES
// Direktsetzen von Datenbloecken (fuer Listen)
// 
//    Rev 1.13   05 Jul 1993 14:48:14   HANNES
// Datentyp COMMONDATA
// 
//    Rev 1.12   18 Jun 1993 15:15:56   MARTIN
// Prototypen von GetData, SetData, SetConnection, ....
// 
//    Rev 1.11   28 May 1993 21:19:34   HANNES
// DelData
// 
//    Rev 1.10   10 May 1993 12:51:10   HANNES
// Neuen Datentype (DMWSSTAMM..)
// 
//    Rev 1.9   02 Apr 1993 17:53:04   HANNES
// Strukturbereinigung
// 
//    Rev 1.8   17 Mar 1993 18:02:42   HANNES
// 32 bit Umstellung
// 
//    Rev 1.7   08 Mar 1993 14:17:12   HANNES
// GetRef in der Callrefliste
// 
//    Rev 1.6   22 Feb 1993 17:21:26   HANNES
// Umdrehen der Schluesselreihenfolge
// 
//    Rev 1.5   14 Feb 1993 16:07:32   HANNES
// Weitere Konstanten
// 
//    Rev 1.4   08 Feb 1993 10:42:40   HANNES
// Umbau aller Files auf btrFiles
// 
//    Rev 1.3   29 Jan 1993 18:36:34   HANNES
// Datentyp DCDATA
// 
//    Rev 1.2   13 Jan 1993 18:56:56   HANNES
// Einige Funktionsprototypen nicht mehr ex. Funktionen eleminiert
// 
//    Rev 1.1   14 Dec 1992 12:24:56   HANNES
// Veraenderung des Prototypen von GetFallNummer ()
// 
//    Rev 1.0   02 Dec 1992 15:53:02   HANNES
// Initial revision.
/*----< Schluessel fuer den Zugriff auf die erste Ebene >-----*/
// Entspricht gleichzeitig auch dem Schluessel in der Datenbank
#define GLOBALDATA      1
#define LOCALDATA       0
#define CONSTDATA       0xFFFF
#define HELPDATA        0xFFFE
#define BENUTZERKEY     0xFFFD
#define FBENUTZERKEY    0xFFF0
#define RECALLKEY       0xFFEF
#define DLISTDATA       0xEEFF
#define BEMERKUNGENKEY  0xEEFE
#define MAXHELPRUN      5

extern BOOL IsBenutzerKey (WORD rt);
extern void closeBenutzerFiles();

struct HelpDataTable {
  WORD   NextHelpPtrOffs;     // Zeiger auf den naechsten Help - Pointer
  LPVOID HelpPtr[1];
  };
typedef HelpDataTable FAR *LPHLPTABLE;

#define DOCCNFDATA      99
#define SYSTEMDATA      100
#define PICTUREDATA     101
#define COMMONDATA      0xDFFF

#define DIAGDATA        4
#define ARCHDATA        5
#define AXIODATA        6
#define PDATA0          7
#define PDATA1          8
#define PDATA2          9
#define PDATA3          10
#define PDATA4          11
#define PDATA5          12
#define PDATA6          13
#define PDATA7          14
#define PDATA8          15
#define PDATA9          16
#define DCDATA          17
#define SECSTAMM        18

#define RECORDDIMENSION 111
#define BASEDIMENSION   37
#define RDHASHDIMENSION 11

// Fallnummer == FULLWINDOW -> Alle Records eines Fensters schliessen
// (bei Funktion CloseRecord)
#define CLOSEALLRECORDS      0x0000  
#define DELFULLRECORD        0xFFFF  

/*----< Datenbank - Schluessel :
        Achtung: btrieve ordnet die numerischen Schluessel in verkehrter
                 Reihenfolge an >------------*/
struct dbkey {
  unsigned DataType:1;          // Lokale - Globale Daten (bei lokalen Daten
                                // ist der Recordtyp der Fensterhandle)
  unsigned FallNummer:15;       // 15 bit Fallnummer
  union {
    WORD Recordtyp;             // Typ des Records (case DataType == GLOBALDATA)
    HWND hWnd;                  // Fenster, das die lokalen Daten anfordert (case DataType == LOCALDATA)
    } rt;
  WORD PatientenNummer[3];      // 48 bit Patientennummer
  }; // (=> 10 Byte Datenbankschluessel)

// Datenelement zur Referenzierung der 2. Hashtabelle
struct RecordRef {
  WORD RefCount;   // Anzahl der Fenster, die den Record referenzierten
#ifndef HASH_INCLUDED
  LPVOID _hmem;
#else
  hash *_hmem;     // Hashtabelle
#endif
  };
typedef RecordRef FAR *lpRref;

// Listenelement in der Liste der referenzierten Record's
struct RefListElement {
  RefListElement FAR *Next; // Es ist ja bekanntlich eine Liste
  dbkey key;                // Die Record - Referenz wird abgespeichert
  };

/*--< Schluessel zur vollstaendigen Referenzierung eines Datenelementes >--*/
struct full_key {
  WORD Ident;      // Zusaetzlich kommt noch die Referenzierung
  dbkey bkey;   // fuer ein einzelnes Element dazu
  };

// forward declaration von mdiChild
class mdiChild;

/*----< Datenelement der Zyklenliste >----*/
struct zl_element {
  WORD Next;
  full_key key;
  mdiChild *c;
  LPVOID Cmd;
  };

/*----< Datenelement der Argumentenliste >-----*/
struct al_element {
  WORD Next;
  WORD Size;    // Die eigentlichen Daten werden direkt hinter diesem
                // element abgespeichert
  };

/*--< Zugriff zu den Daten >---*/
#define NO_UPDATE         0
#define UPDATE_ASYNCHRON  1
#define UPDATE_SYNCHRON   2
class Data {
 public :
  GLOBALHANDLE hGmem;   // fuer die noetigen listen (Argument - List, Liste 
                        // zum Unterbinden von Zyklen)
#ifdef HASH_INCLUDED
  hash *hDBmem;   // Hashtabelle 1. Stufe
  hash *hRdmem;   // Hashtabelle, in der fuer jedes Fenster die
                  // Record's in einer Liste gehalten werden, die von 
                  // dem Fenster benoetig werden (Lesend bzw. schreibend)
  hash *hWrmem;   // Hashtabelle, in der fuer jedes Fenster die
                  // Record's in einer Liste gehalten werden, die von
                  // dem Fenster modifiziert wurden (-> nur Schreibend)
  hash *hCrlmem;  // Hashtabelle, in der fuer jedes Element die Funktionen
                  // eingetragen werden, die das Elemente vielleicht
                  // fuer Update - Zwecke brauchen
#else
  LPVOID hDBmem;   
  LPVOID hRdmem;   
  LPVOID hWrmem;   
  LPVOID hCrlmem;  
#endif
  WORD wZykList;   // Erstes Element der Zyklenliste
  WORD wArgList;   // Erstes Element fuer temp. Daten
  /*----< Hilfsvariablen fuer die Schnellsuche >-----*/
  BOOL lastWrite;
  dbkey lastkey;
  mdiChild *lastRefc;
#ifdef HASH_INCLUDED
  hash* lastRecHash;
#else
  LPVOID lastRecHash;
#endif
  /*----< Zyklenliste >----*/
  void PushZykRef (full_key FAR *,mdiChild *,LPVOID);
  BOOL IsInZykList (full_key FAR *,mdiChild *,LPVOID);
  void PopZykRef (void);
  /*----< Argumentenlist >-----*/
  void PushArg (void FAR *,WORD);
  void FAR *GetLastArg (void);
  void ReleaseArg (void FAR *);
  void PopArg (void FAR *);
  /*----< Anforderung von Daten (fuer Lesezwecke) >------*/
  void FAR *GetData (full_key FAR *,mdiChild *);
  /*----< Modifizierung (oder erstmaliges Schreiben) von Daten >----*/
  void SetData (full_key FAR *,mdiChild *,void FAR *,int,LPVOID Cmd,WORD doUpdate = UPDATE_ASYNCHRON);
  /*----< Loeschen von Daten von Daten >----*/
  void DelData (full_key FAR *,mdiChild *,LPVOID Cmd,WORD doUpdate = UPDATE_ASYNCHRON);
  /*--< Record's wieder freigeben (Key entspricht dem fuer lokalen Daten 
        -> es muss fuer jeden verw. Patienten und jeden verw. Fall 
           aufgerufen werden                                     >--*/
  void CloseRecord (dbkey *,mdiChild *,BOOL delref = TRUE);
  /*--< Record wird geloescht >-----*/
  void DelRecord (dbkey FAR *);
  /*--< Herstellung des Zusammenhanges Daten <-> Funktionen >---*/
  void SetConnection (full_key FAR *,mdiChild *,LPVOID);
  void ClearConnection (full_key FAR *,mdiChild *,LPVOID);
  void ChangeConnection (WORD FAR *,WORD,WORD,WORD,mdiChild *);
  void SetNewPatConnection (WORD FAR *PatientenNummer,mdiChild *c);
  void ReinitializeData (dbkey FAR *k);
  void ClosePatRecs (WORD FAR *PatientenNummer,mdiChild *c,BOOL nolocals);
  /*--< Record wird geschrieben >----*/
  void WriteRecord (dbkey FAR *);
  void CopyData (dbkey FAR *,dbkey FAR *,HANDLE);
  // Initialisierung ...
  void Initialize (void);
  void Destroy    (void);

  // Setzen von Daten, die sicher gebraucht werden
  void SetDataRec (dbkey FAR *key,GLOBALHANDLE hGmem);
  };

#ifdef DATA_MAIN
Data dat;               // Ueber diese Variable greift das ganze Programm
                        // auf alle Daten zu
void SetIndexedData (hash *,HANDLE,WORD,LPVOID,WORD);
void FAR *GetIndexedData (hash *,HANDLE,WORD *Offset,WORD);

#else
extern Data dat;
#endif

// Schluessel fuer die Konfiguartionsdatei
struct CnfKey {
  WORD LoKey;
  WORD HiKey;
  DWORD User;
  char DocName[13];
  };

// Elemente der Patientenliste (Zur Bufferung)
struct patlistelement {
  dbkey key;    // Zur Ermittlung des eindeutigen Schluessels
  DWORD pos;    // Zur Durchfuehrung eines GETDIRECT
  char str[80]; // Angezeigter String
  };

// Weitere Hilfsfunktionen
GLOBALHANDLE ReadData (dbkey FAR *);
void         WriteData (dbkey FAR *,GLOBALHANDLE);
void         NameChanged (dbkey FAR *,HWND);
void         CommentChanged (dbkey FAR *,HWND);
void         DateChanged (dbkey FAR *,HWND);
void         XFactChanged (dbkey FAR *,HWND);
void         WriteBenutzerData (dbkey FAR *,GLOBALHANDLE);

GLOBALHANDLE GetProgData (WORD,WORD);
void         PutProgData (GLOBALHANDLE,WORD,WORD);
BOOL         DelProgData (WORD,WORD);
BOOL         MoveProgData(WORD,WORD,WORD,WORD);

GLOBALHANDLE ReadCnfData (WORD,WORD,BOOL UseActUser = TRUE);
GLOBALHANDLE ReadDocCnfData (WORD,WORD,BOOL UseActUser = TRUE);
void         WriteCnfData (GLOBALHANDLE,WORD,WORD,BOOL UseActUser = TRUE);
void         WriteDocCnfData (GLOBALHANDLE,WORD,WORD,BOOL UseActUser = TRUE);
WORD         GetCnfFirstKey (WORD,BOOL UseActUser = TRUE);
BOOL         DelCnfData (WORD,WORD,BOOL UseActUser = TRUE);
BOOL         MoveCnfData(WORD,WORD,WORD,WORD,BOOL UseActUser = TRUE);

#define PRINTJOBKEY     0xF000
#define DIGCNFKEY       0xF001
#define FORMATBASE_KEY  0xF002
#define LOUTPOSBASE     0xE500
#define MDIPOSBASE      0xE001
#define FRAMEPOSBASE    0xE000
#define DOCLISTCNFKEY   0xD000
#define HOTKEY_KEY      0xC000
#define DEMOKEY         0xA000

#define MAKROKEY                0x9000
#define DRVSPEC_KEY             0x8000
#define CACHECONFIG_KEY         0x8001
#define DOCCOMMENT_KEY          0x8002
#define PROGCNFKEY              0x8003
#define DOCLISTKEY              0x8004
#define PROGLISTKEY             0x8005
#define FORMATLISTKEY           0x8006

// Funktionen fuer die Listenverwaltung
void PrepKey(DWORD,dbkey FAR *);     // Vorbereitung fuer GetNext,GetPrev...
char FAR *GetListEntry(dbkey FAR *); // Lesen des Namens (Aus Schluessel)
char FAR *GetListEntry(DWORD,dbkey FAR *key = NULL);
                                     // Lesen des Namens (Aus Name)
BOOL GetNext(dbkey FAR *);           // Naechster Patient
BOOL GetPrev(dbkey FAR *);           // Vorhergehender Patient
DWORD GetPos(char FAR *);            // Zugriff durch String - Schluessel
DWORD GetPos(void);                  // aktuelle physikalische Position im
                                     // File

void CmtPrepKey (WORD,DWORD,dbkey FAR *);
char FAR *GetCmtListEntry(WORD,dbkey FAR *);
char FAR *GetCmtListEntry(WORD,DWORD,dbkey FAR *key = NULL);
BOOL CmtGetNext (WORD,dbkey FAR *);
BOOL CmtGetPrev (WORD,dbkey FAR *);
DWORD CmtGetPos (WORD,WORD FAR *);
DWORD CmtGetPos (void);
void CleanCmtBuffers (void);

WORD GetFallNummer (WORD FAR *,WORD,WORD,BOOL *);

// Funktionen zur Verwaltung der Ueberlagerungsdaten bei den Funktionen
void PushRunData (WORD FAR *,GLOBALHANDLE *,WORD,void FAR *,int);
void FAR *GetRunData (WORD,GLOBALHANDLE,WORD);
void ReleaseRunData (void FAR *,GLOBALHANDLE);
void DelRunData (WORD FAR *,GLOBALHANDLE *,WORD);
void DelAllRunData (WORD FAR *,GLOBALHANDLE *);
void FAR *GetFirstRunData (WORD,GLOBALHANDLE,WORD *RNmbr = NULL);
void FAR *GetNextRunData (void FAR *,GLOBALHANDLE,WORD *RNmbr = NULL);
WORD GetRunDataOffset (void FAR *,GLOBALHANDLE);

extern BOOL IsIndexedData(full_key FAR *);

GLOBALHANDLE PrepBuffer () ;
typedef char pchar ;
GLOBALHANDLE AddData (GLOBALHANDLE data,WORD Ident,pchar FAR *str);
GLOBALHANDLE AddDataw (GLOBALHANDLE data,WORD Ident,WORD w);
GLOBALHANDLE AddDatal (GLOBALHANDLE data,WORD Ident,long w);
GLOBALHANDLE AddData (GLOBALHANDLE data,WORD Ident,packdate pd);
GLOBALHANDLE AddDatav (GLOBALHANDLE data,WORD Ident,LPVOID d,int size);

void SetNoWrite (mdiChild *c,dbkey FAR *key);
void DelNoWrite (mdiChild *c,dbkey FAR *key);
BOOL DelDataRec (dbkey FAR *key,BOOL doBdelete = TRUE);



