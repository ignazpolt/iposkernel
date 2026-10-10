/********************************************************/
/*      Basisklassen zu der Windows - Oberflaeche       */
/********************************************************/

// $Header:   P:/marille/clinicum/include/rev/dds.hpv   1.19   15 Jun 1999 19:17:24   WOLFGANG  $
// $Log:   P:/marille/clinicum/include/rev/dds.hpv  $
// 
//    Rev 1.19   15 Jun 1999 19:17:24   WOLFGANG
// 1.) ResetSync neu.
// 
//    Rev 1.18   15 Jun 1999 16:21:00   THOMAS
// 1.) TimeNow entfernt.
// 2.) [Un]PackSeconds neu.
// 
//    Rev 1.17   31 Mar 1999 14:57:22   Gerhold
// htmlhelp
// 
//    Rev 1.16   18 Nov 1998 15:48:54   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.15   05 Oct 1998 11:24:58   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.14   04 Aug 1998 17:48:22   Hannes
// Timestamp
// 
//    Rev 1.13   08 Apr 1997 17:45:00   gerhold
// SetHelpFile, GetHelpFile
// 
//    Rev 1.12   08 Nov 1996 13:29:36   HANNES
// Zahlenformatierung
// 
//    Rev 1.11   24 Sep 1996 18:57:34   GERHOLD
// SetHelpContextNrm, GetHelpContextNr
// 
//    Rev 1.10   18 Sep 1996 20:48:58   HANNES
// 
//    Rev 1.9   02 Feb 1996 10:59:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   16 Sep 1995 02:05:36   HANNES
// 
//    Rev 1.7   10 Aug 1995 09:18:40   HANNES
// FormatDate,FormatTime
// 
//    Rev 1.6   09 Jun 1995 00:33:32   MARTIN
// Wartecursorhandling
// 
//    Rev 1.5   06 Feb 1995 16:52:06   HANNES
// 
//    Rev 1.4   19 Dec 1994 08:15:58   GERHOLD
// Sanduhr-Cursor-Funktionen.
// 
//    Rev 1.3   03 Oct 1994 18:03:06   HANNES
// Datum umgestellt
// 
//    Rev 1.2   05 Aug 1994 19:54:58   HANNES
// 
//    Rev 1.1   05 Aug 1994 19:22:22   HANNES
// Zeitfunktionen
// 
//    Rev 1.0   24 Jun 1994 17:01:10   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.17   07 Jan 1994 19:19:58   HANNES
// Funktionsprototyp von CheckMsg
// 
//    Rev 1.16   03 Nov 1993 16:10:54   MARTIN
// Sanduhr - Funktionen
// 
//    Rev 1.15   22 Oct 1993 14:20:54   HANNES
// fpt fuer dlls sichtbar
// 
//    Rev 1.14   27 Sep 1993 18:27:50   HANNES
// Neue Zeitfunktionen
// 
//    Rev 1.13   05 Jul 1993 14:49:02   HANNES
// Umordnung der Definitionen
// 
//    Rev 1.12   16 Jun 1993 16:56:04   MARTIN
// Sanduhr
// 
//    Rev 1.11   04 Jun 1993 17:33:48   HANNES
// EnableOKCANCEL in WDialog
// 
//    Rev 1.10   02 Jun 1993 19:39:28   HANNES
// Verschiedene Funktionen in die DLL ausgelagert
// 
//    Rev 1.9   25 May 1993 10:11:00   GERHOLD
// Include fuer DLL
// 
//    Rev 1.8   02 Apr 1993 17:53:12   HANNES
// Struktrurbereinigung
// 
//    Rev 1.7   17 Mar 1993 18:02:54   HANNES
// 32 bit Umstellung
// 
//    Rev 1.6   08 Mar 1993 14:18:50   HANNES
// Funktionsprototypen...
// 
//    Rev 1.5   29 Jan 1993 18:35:54   HANNES
// Veraenderung im Funktionsprototyp von CreateDocument
// 
//    Rev 1.4   18 Jan 1993 16:52:24   HANNES
// Funktionsprototyp von CreateDoc
// 
//    Rev 1.3   17 Dec 1992 15:58:32   HANNES
// ???
// 
//    Rev 1.2   08 Dec 1992 14:21:04   HANNES
// No change.
// 
//    Rev 1.1   08 Dec 1992 14:02:16   HANNES
// Anderung der Funktionsprototypen von GetItemColor
// 
//    Rev 1.0   02 Dec 1992 15:54:06   HANNES
// Initial revision.

// Haeufig verwendete Datentypen
//------------------------------
typedef struct tag_fpt {
  float x,y;
  } fpt;
typedef fpt FAR * LPFPT;

struct packdate {
  BYTE day ;
  BYTE month ;
  WORD year;
  };
struct packtime {
  BYTE hour;
  BYTE minute;
  BYTE second;
  BYTE hundred_second;
  };
struct packdatetime {
  packdate pd;
  packtime pt;
  };

#ifndef JUST_EM

#include "test.hpp"

/*-----------< Druck - Job's >-------*/
void PrJobDestroy (void);

/*-----------< Verschiedentlich verwendete Funktionszeiger >--------*/
typedef	LONG (FAR PASCAL *LFPTR)(HWND,UINT,WPARAM,LPARAM);
typedef void (* NOTIFY) (UINT,WPARAM,LPARAM);

struct BASESTRUCT {
  WORD   next ;
  LONG   atomic ;
  BOOL   Locked ;
  };

#ifndef NODDSDATA
/*--------------< Base Class for Normal Windows >------------*/
class WBase {
 private :

  // Daten ueber Windows allgemein
 public :
  static HINSTANCE hInstance ;           // Instanz der Windows Applikation
  static HWND   hFrameWin ;           // Handle des Framewindow
  static HMENU  hMenu ;		      // Handle zum Hauptmenue
  static HWND   hClient ;	      // Handle zum Clientwindow
  WBase(HINSTANCE hInst) ;		      // Construktor: Registriert alle
				      // Windows - Klassen, Laedt das Menu,
				      // Erzeugt Hauptfenster und Klienten-
				      // fenster
  } ;
#endif


#ifdef UEBERLEGT
/*---------< Dialog Boxes >----------*/
BOOL CheckDialogMessage (MSG *);
class WDialog {
 private :
  HWND DHWnd;           // Vaterfenster
  HANDLE rc ;           // Resource name
  BOOL modeless ;

 protected :
  FARPROC Handler;		// user callback

 public :
  HWND MyHandle;
  HWND Notify;                  // Benachrichtigung bei Ende
  BOOL dostore;
  BOOL EnableIDOKCANCEL;
  void DisableOK_CANCEL ()
    { EnableIDOKCANCEL = FALSE ; }
  HANDLE hmem;
  WDialog(HWND,char*);          // modale Dialogbox
  WDialog(HWND,char*,HWND);     // nichtmodale Dialogbox
  WDialog(void);
  void SetNotify(HWND N) { Notify = N ; }
  ~WDialog();
  void Go();
  void Center (HWND);
  virtual BOOL FAR PASCAL Init(HWND,UINT,WPARAM,LPARAM);             // Extra Init Method
  virtual BOOL FAR PASCAL ExtraCommand(HWND,UINT,WPARAM,LPARAM);     // Intrprete Extra Commands
  virtual BOOL SpcFnc (HWND,UINT,WPARAM,LPARAM);
  virtual void Paint(HWND);
  friend DLLExport BOOL _export FAR PASCAL DialogGo(HWND,UINT,WPARAM,LPARAM);
  // Speicherverwaltung (nur fur nichtmodale Dialogboxen verwenden !!!)
  void *operator new (size_t);
  void operator delete (void *);
  };

typedef int (* SCRFNC) (WORD,WORD,LONG);
/*--------< Listen zum Anzeigen von Strings aus einer Stringliste >-------*/
/* (Mit diesem String als Titel wird dann ein Kindfenster eroeffnet) */
class WList : public WDialog {
 private :
  WORD Listid ;
  WORD Textid ;
  WORD Selected ;
 public :
  WList(HWND,char *,WORD,WORD);                 // Neuer Konstruktor
  void Go();                                    // Funktion wird ueberladen, um Selected aufzurufen
  virtual char *GetLine(unsigned);              // Funktion zum Zusammenstellen von Strings
  virtual BOOL FAR PASCAL Init(HWND,UINT,WPARAM,LPARAM);
  virtual BOOL FAR PASCAL ExtraCommand(HWND,UINT,WPARAM,LPARAM);
  };

/*------< Allgemeine Fenstertypen (Rahmenfenster, Comboboxen ...) >---------*/
class Wgen {
 private :
  HANDLE hmem ;  	// Handle auf den Speicher, 
                 	//          damit wieder freigegeben werden kann!
 public:
  HWND GroupTop;	// Handle auf Rahmenfenster
  static int xact;	// Aktuelle Position fuer naechstes Fenster
  static int yact;	// (kann statisch gehalten werden)
  static int DefHeight;

  static FARPROC Handler; // Es gibt nur einen Einzigen Handler
  FARPROC DefaultHandler;
  WORD posident;         // sek. Schluessel zur Positionsspeicherung
  HWND ChWnd;           // Handle auf das Fenster
  NOTIFY Notify;	// bestimmte Meldungen werden Weitergeleitet
  ~Wgen();              // Destruktor: Versendet WM_DESTROY Message
  Wgen() {}
  Wgen(char *,		// window caption
       LONG,		// style
       int,		// x position
       int,		// y location
       int,		// width
       int,		// height
       HWND,		// parent handle
       NOTIFY Not = NULL,
       BOOL Show = TRUE,
       WORD PosIdent = 0xFFFF);            
  void Create (char *,  // Class name
               char *,  // window caption
               LONG,	// style
               int,	// x position
               int,	// y location
               int,	// width
               int,	// height
               HWND,    // parent handle
               HMENU,   // Menu handle
	       BOOL Show = TRUE);	// Fenster anzeigen

  virtual LONG FAR PASCAL WgenCallBack(HWND,UINT,WPARAM,LPARAM);
  virtual void ReSize(void);
  friend LONG FAR PASCAL WgenWndProc(HWND,UINT,WPARAM,LPARAM);
  void   Hide(void);
  void   Show(void);
  BOOL   IsVisible(void);
  void   PaintOn(void);
  void   PaintOff(void);

  // Scroll - Bar's
  int hmax,hpos;
  int vmax,vpos;

  void SetHScroll(int,int);
  void SetVScroll(int,int);
  SCRFNC ScrollFunction;
  void SetScrollFunction(SCRFNC fnc) { ScrollFunction = fnc ; }

  // User new operater to invoke constructor
  void * operator new(size_t);
  void   operator delete(void *);
  };

typedef DWORD (* GETCOLORFNC) (int,LPSTR);
class WgList : public Wgen {
 public :
  int fr ;	// Platz, der noch freigelassen werden soll
  WgList() { }
  GETCOLORFNC ItemColor;
  WgList(HWND,int,NOTIFY Not = NULL,BOOL Show = TRUE,GETCOLORFNC Color = NULL);
  void Add (char FAR *);
  void Clear (int ind = -1);
  void Select (int);
  virtual LONG FAR PASCAL WgenCallBack (HWND,UINT,WPARAM,LPARAM);
  virtual void ReSize(void);
  };

/*------< Combo - Box >------*/
class WCombo : public Wgen {
 public :
  WCombo(HWND,BOOL Show = TRUE);// Constructor: Breite der Combobox
  void Add (char *);		// Dazufuegen eines Items
  void Select (int);		// Selektion eines Items von aussen
  virtual LONG FAR PASCAL WgenCallBack(HWND,UINT,WPARAM,LPARAM);
  };


/*-----< TextButton >-----*/
class WTextButton : public Wgen {
 protected :
  BOOL State ;
  int denum ;
 public :
  WTextButton(HWND,char *,int,WORD ObjectID = 0,NOTIFY Not = NULL,BOOL Show = TRUE);
  WTextButton() {}
  void SetState(void);
  void ResetState(void);
  BOOL Active(void);
  virtual LONG FAR PASCAL WgenCallBack(HWND,UINT,WPARAM,LPARAM);
  virtual void ReSize(void);
  };

/*-----< Graphische Knoepfe >------*/
class WGrButton : public WTextButton {
 public :
  BOOL LastIL;
  int denum;
  int HlpId;
  HBITMAP hBitMap;
  WGrButton(HWND,char *,int,int,NOTIFY Not = NULL,BOOL Show = TRUE,BOOL State = FALSE,BOOL LastInLine = FALSE);
  WGrButton() {}
  virtual void ReSize (void);
  virtual LONG FAR PASCAL WgenCallBack(HWND,UINT,WPARAM,LPARAM);
  };

/*-----< CheckBox >------*/
class WChkButton : public Wgen {
 public :
  int denum ;
  WChkButton(HWND p,char *,int,NOTIFY Not = NULL,BOOL Show = TRUE);
  WChkButton() {}
  void Enable(void);
  void Disable(void);
  void Set(void);
  void Reset(void);
  BOOL State(void);
  virtual LONG FAR PASCAL WgenCallBack(HWND,UINT,WPARAM,LPARAM);
  virtual void ReSize(void);
  };
#endif

// #define ACTIVATE_HANDLING


// Verschiedene Hilfsfunktionen
WORD AskUser (WORD,WORD);               // Anzeigen einer Messagebox
WORD AskUser (WORD,WORD,char *str);     // Anzeigen einer Messagebox

void CheckMsg (MSG *msg);
extern void btrvinit (void);
extern void btrvexit (void);
extern void toAllDocuments (UINT,WPARAM,LPARAM);

// Datum in einem LONG einpacken
DLLExport BOOL _export WINAPI readDateStr (LPSTR txt,packdate FAR *pd);
DLLExport BOOL _export WINAPI readTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt);
DLLExport void _export WINAPI writeShortDateStr (LPSTR txt,packdate FAR *pd);
DLLExport void _export WINAPI writeDateStr (LPSTR txt,packdate FAR *pd);
DLLExport BOOL _export WINAPI writeTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt);
DLLExport void _export WINAPI FormatTime (LPSTR outtxt,packtime FAR *tvar,LPSTR format);
DLLExport void _export WINAPI FormatDate (LPSTR outtxt,packdate FAR *dvar,LPSTR format);
DLLExport LPSTR _export WINAPI GetWeekDay(packdate FAR *pd);
DLLExport LPSTR _export WINAPI GetMonthName(int m);

DLLExport void _export WINAPI GetLongStr (LPSTR res,LONG m,BOOL withTousendPt);
DLLExport void _export WINAPI GetMoneyStr (LPSTR res,LONG m);
DLLExport BOOL _export WINAPI sclongint (LPSTR txt, long FAR *i);
DLLExport BOOL _export WINAPI scmony (LPSTR txt, long FAR *i);
DLLExport BOOL _export WINAPI scint (LPSTR txt, int FAR *i);
DLLExport void _export WINAPI GetShortStr (LPSTR res,DBINT i);

void DestroyKeyWords (void);
void DeleteBitMaps (void);
void CompleteMenu (HMENU);
DLLExport int WINAPI _export DaysInMonth (int year,int month);
DLLExport int WINAPI _export YearLen(int year);
DLLExport BOOL WINAPI _export Leap(int year);

void PString (int,int,char FAR *,int);
void AddBackSlash (char *);

void GetListConfig (void);
void DelDocListIdent (int);
void ReadDocuments (void);

int FAR *FixDocListIndex(int *AnzDocs = NULL);
void ReleaseDocListIndex(void);
int FAR *FixIndex(int *Dim = NULL);
void ReleaseIndex(void);
int FAR *FixDBNr(int *Dim = NULL);
void ReleaseDBNr(void);
int GetType(int Sel);
int GetDBNr(int Sel);
void GetDocumentName (char *,int,int);

BOOL GetDocName (int,char *,int,WORD *,WORD *);
int GetFirstForm (void);

void ReadCnfList (void);
void WriteCnfList (void);

void GetTextScale (float *);

char *LRString (int id);
void LRString (int id,char *txt,int size);
GLOBALHANDLE PushToGlobBlock (GLOBALHANDLE,LPVOID,int);

DLLExport void _export WINAPI RegisterCustomControl (void);

// Sanduhr-Cursor Funktionen
extern void WINAPI DenyBusyCursor();
extern void WINAPI DenyBusyCursorOnce();
extern void WINAPI AllowBusyCursor();
extern void WINAPI ToBusyCursor();
extern BOOL WINAPI IsBusyCursor();
extern void WINAPI RestoreCursor();

void ShowCalender (void);

typedef long double INTTIME;

DLLExport INTTIME _export WINAPI PackTime (packdate FAR *);
DLLExport void _export WINAPI UnPackTime (INTTIME,packdate FAR *);
DLLExport INTTIME _export WINAPI PackSeconds (packtime FAR *pt);
DLLExport void _export WINAPI UnPackSeconds (INTTIME t,packtime FAR *pt);
DLLExport int _export WINAPI WeekDay (INTTIME t);
DLLExport INTTIME _export WINAPI Now(void);
DLLExport void _export WINAPI ResetSync ();

DLLExport DWORD _export WINAPI GetHelpContextNr (void);
DLLExport void  _export WINAPI SetHelpContextNr (DWORD dwHelpContextNr);
DLLExport void  _export WINAPI SetHelpFile (LPSTR lpHelpFile);
DLLExport LPSTR _export WINAPI GetHelpFile ();

//============================================================================
// HTML Hilfe
//============================================================================
DLLExport void _export SetHtmlHelp (FARPROC htmlproc);
DLLExport HWND _export WINAPI htmlhelp (HWND hWnd, LPCSTR lpstr, 
                                        UINT uint , DWORD dword);
DLLExport void _export WINAPI SetHtmlContext (LPSTR lpchmfile, 
                                              LPSTR lphtmlfile);
DLLExport LPSTR _export WINAPI GetHtmlFile ();


BOOL TranslateMyAccelerator (HWND,MSG *);
BOOL CheckMakroCommand (WORD);
void InitializeAccelerators (void);
void WorkOnMakro (void);
BOOL WINAPI CenterPopup(HWND,HWND);
void GetOwner (LPSTR,int);

void CreateDoc (int,BOOL newRec = FALSE,WORD Category = 0,
                    int AnzDataSet = 0,LPVOID KeyBuffer = NULL,BOOL doCopy = FALSE);

//#define MEMCHK
//#define EXTMEMCHK

#ifdef MEMCHK

#define GlobalAlloc GAlloc
#define GlobalFree  GFree
#define LocalAlloc  LAlloc
#define LocalFree   LFree

extern void preplog (void);
extern void closelog (void);
extern HANDLE GAlloc (WORD,DWORD);
extern HANDLE LAlloc (WORD,WORD);
extern HANDLE GFree  (HANDLE);
extern HANDLE LFree  (HANDLE);
extern void MtoF (HANDLE);
extern void MtoA (HANDLE);
extern void ExtMtoG (HANDLE,WORD);
extern void ExtMtoF (HANDLE,WORD);

#else

#define MtoF(A)
#define MtoA(A)

#endif

#ifndef NODDSDATA

#ifdef DDS_MAIN

BOOL GlobalDestroy;     // Ganzes Programm schliessen
WORD DBKeyNumber = 1;   // Zugriff auf die Stammdatenbank mit Schluessel..
DWORD ActUser = 0;      // Aktueller User (fuer Multiuserversionen)
GLOBALHANDLE hDocLst;   // Liste mit den verwendeten Dokumenten
GLOBALHANDLE hGIndex;   // Liste der Basisnummern der einzelnen Dokumente
                        // (bei gegebenem Index der Hauptliste:
                        //   Zugriff ueber Array, das in hDocLst gespeichert ist)

GLOBALHANDLE hGDBNr;    // Zugriff wie oben
BOOL DocLstChanged = FALSE ;
BOOL ShowAllDocuments = FALSE ;
BOOL AllSamePatient = FALSE;

#ifdef UEBERLEGT
WgList *DList;
Wgen *Documents;
WGrButton *DGrNewDoc,*DGrCorrDoc;
#endif

// Haufig verwendete Strings
char *AppName = "dds";
char *DefProgExt = "txt";

char statstrspace[50];

#ifdef UEBERLEGT
WDialog *actDialog;
#endif

HINSTANCE WBase::hInstance = 0;
HWND   WBase::hFrameWin = 0;
HMENU  WBase::hMenu = 0;	
HWND   WBase::hClient = 0;
#ifdef UEBERLEGT
int Wgen::xact = 0;	
int Wgen::yact = 0;	
int Wgen::DefHeight = 0;
FARPROC Wgen::Handler = NULL;
#endif

#else

extern BOOL GlobalDestroy;
extern WORD DBKeyNumber;
extern DWORD ActUser;
extern GLOBALHANDLE hDocLst;
extern GLOBALHANDLE hGIndex;
extern GLOBALHANDLE hGDBNr;
extern BOOL DocLstChanged;
extern BOOL ShowAllDocuments;
extern BOOL AllSamePatient;
extern LPSTR GetKW(LPSTR kw,int FAR *fldLen,BOOL FAR *flgRes);

#ifdef UEBERLEGT
extern WgList *DList;
extern Wgen *Documents;
extern WGrButton *DGrNewDoc,*DGrCorrDoc;
#endif

extern char *AppName;
extern char *DefProgExt;

extern char statstrspace[50];

#ifdef UEBERLEGT
extern WDialog *actDialog;
#endif

#endif

#endif

#endif

// Mode's bei der Ausfuehrung der Kommandos
#define EM_LOAD                 0x0001  // Laden der Daten
#define EM_FIXCONNECTION        0x0002  // Herstellung der Verknuepfung von
                                        // Daten
#define EM_UPDATE               0x0004  // Datenelemet hat sich geaendert
#define EM_SAVE                 0x0008  // Datenelement muss gesetzt werden
#define EM_CLEAR                0x0010  // Funktion wird das letzte mal auf-
                                        // gerufen
#define EM_CHANGETOTRUE         0x0020  // Funktion ist in einem Block, der
                                        // das erste mal wegen einer Conditions
                                        // aufgerufen wird
#define EM_CHANGETOFALSE        0x0040  // -"- das letzte mal
#define EM_PAINT                0x0080  // Aufforderung zum Zeichenen 
                                        // (nur von bestimmten Funktionen benuetzt)
#define EM_RESET                0x0100  // Speicher freigeben
#define EM_PRIVATE0             0x0200  // kontextabhaengiger Hilfsmodus
#define EM_PRIVATE1             0x0400  // -"-
#define EM_PRIVATE2             0x0800  // -"-
#define EM_PRIVATE3		0x1000	// -"-
#define EM_PRIVATE4		0x2000  // -"-
#define EM_PRIVATE5		0x4000  // -"-
#define EM_SHOWBUTTON		0x8000  // -"-

