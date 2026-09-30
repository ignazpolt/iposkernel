//
//      Arbeiten mit dem Drucker
//
// $Header:   F:/marille/clinicum/include/rev/printer.hpv   1.7   18 May 2000 09:54:52   Hannes  $
// $Log:   F:/marille/clinicum/include/rev/printer.hpv  $
// 
//    Rev 1.7   18 May 2000 09:54:52   Hannes
// Fehlerhandling Bei STartDoc - Fehlern
// 
//    Rev 1.6   18 Dec 1998 15:50:00   Martin
// DefaultSource
// 
//    Rev 1.5   07 Aug 1998 00:02:08   Hannes
// SetPrinterCaption
// 
//    Rev 1.4   27 Jul 1998 09:53:10   Hannes
// Doppelseitiger Druck
// 
//    Rev 1.3   12 Jun 1997 16:59:24   Martin
// StartFrame ...
// 
//    Rev 1.2   29 Jan 1997 17:32:12   HANNES
// 
//    Rev 1.1   02 Feb 1996 11:00:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:56   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   12 Jan 1994 11:16:02   HANNES
// Strukturen fuer die Textinterpretierung
// 
//    Rev 1.4   11 Jan 1994 19:06:46   HANNES
// GetDefaultPrinterName
// 
//    Rev 1.3   04 Jan 1994 17:10:46   HANNES
// Neue Funktionen zur Auswahl des Druckers, GetPrinter () eleminiert
// 
//    Rev 1.2   05 Sep 1993 22:03:52   HANNES
// Exportierte Inline - Funktionen rausgenommen
// 
//    Rev 1.1   15 Jul 1993 16:46:14   GERHOLD
// Drucker in DMWAPI verlagert
// 
//    Rev 1.0   02 Dec 1992 16:03:32   HANNES
// Initial revision.

#ifndef PRINTER_INCLUDED
#define DEVNAMSIZE      64

#ifndef FRECT_DEFINED
struct FAR fRECT {
  int left,top,right,bottom;
  };
#define FRECT_DEFINED
#endif

class FAR Printer {
 private:
  fRECT PrinterArea;     // Druckbereich des ganzen Blattes
  fRECT PartArea;        // Aktueller Druckbereich (Banding)
 public:
  BOOL Initialized;
  BOOL Banding;
  char DeviceName[DEVNAMSIZE];  // Druckerbeschreibung
  char DriverName[64];
  char PortName[128];
  DLLExport _export WINAPI Printer ();
  virtual DLLExport _export WINAPI ~Printer (void);
  WORD PrReference;     // Wie oft wird die Instance Referenziert
  WORD ReferenceCount;  // Wie oft wird der PrinterIC referenziert ?
  HDC PrIC;             // Gelesen mit PrinterIC
  HDC PrDC;             // Gelesen mit PrinterDC
  WORD wError ;
  DLLExport HDC _export WINAPI PrinterDC(BOOL);  // Device - Kontext fuer Drucker
  DLLExport HDC _export WINAPI PrinterDC(void);  // Device - Kontext fuer Drucker
  DLLExport HDC _export WINAPI PrinterIC(void);  // Device - Kontext fuer Drucker
  DLLExport BOOL _export WINAPI StartPrint(LPSTR szMessage);
  DLLExport void _export WINAPI EndPrint(void);
  DLLExport void _export WINAPI StartFrame(void); // Beginn einer Seite
  DLLExport void _export WINAPI NewFrame(void);   // Ende der Seite
  DLLExport void _export WINAPI CheckError(void);
  DLLExport void _export WINAPI SetPrinterArea(LPRECT r); // Setzen eines Druck - Bereiches
  DLLExport void _export WINAPI GetPrinterArea(LPRECT r); // Lesen des Druck - Bereiches
  DLLExport void _export WINAPI FullArea(LPRECT r);       // Lesen des Druck - Bereiches
  DLLExport void _export WINAPI PaperSize(LPRECT r);      // Lesen der Papiergroesse (Achtung: 
                                                   // im gleichen KoordSys wie FullArea)
  DLLExport void _export WINAPI ReleasePrDC(void);       // Freigabe des Printer IC
  DLLExport void _export WINAPI ReleaseDC(void);         // Freigabe des Printer DC (Druck - Ende)
  DLLExport BOOL _export WINAPI NextBand(void);          // Umschalten auf das naechste Band
  DLLExport BOOL _export WINAPI BandSupport(void);
  void SetAbort(void);
  void ReleaseAbort(void);
  DLLExport HDC _export WINAPI ActDC(void);
  DLLExport WORD _export WINAPI HorzRes(void);
  DLLExport WORD _export WINAPI VertRes(void);
  DLLExport LPVOID _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (LPVOID);
#ifdef _INC_PRINT
  DEVMODE FAR *DevMode;
#else
  LPVOID DevMode;
#endif
  int DefaultSource;
  };
typedef Printer FAR *LPPRINTER;

DLLExport BOOL _export WINAPI AbortProc (HDC,short);    // Drucker Abbruchfunktion
void EnableDDS(void);
void DisableDDS(void);
#ifdef UERBERLEGT
DLLExport Printer *_export WINAPI GetPrinter(void);
#endif
DLLExport Printer *_export WINAPI GetPrinter(BOOL);
DLLExport Printer *_export WINAPI GetPrinter(LPSTR devname,
                            int orientation,int defaultsource,
                            int papersize,
                            LPVOID DevMode
                                      );
DLLExport void _export WINAPI FreePrinter(Printer *);

typedef BOOL (WINAPI * PRCALLBACK) (WORD Action) ;
#define PRCALLBACK_SETSTARTPRINTIG  0
#define PRCALLBACK_SETENDPRINTING   1
#define PRCALLBACK_DISABLELAYOUT    2
#define PRCALLBACK_ENABLELAYOUT     3
#define PRCALLBACK_DISABLEFWND      4
#define PRCALLBACK_ENABLEFWND       5
#define PRCALLBACK_SETLAYOUTFOCUS   6
#define PRCALLBACK_SETFWNDFOCUS     7

DLLExport void _export WINAPI PrCallback (HWND hWnd,PRCALLBACK prcbfnc);

DLLExport BOOL _export WINAPI PrinterConfig (HWND hWnd,LPSTR devname,
                    int FAR &orientation,int FAR &defaultsource,
                    int FAR &papersize,LPVOID DevModeIn,LPVOID FAR &DevModeOut);
DLLExport void _export WINAPI GetDefaultPrinterName (LPSTR Name);
#ifdef _INC_PRINT
typedef int (WINAPI *EXTDEVMODE)(HWND, HANDLE, LPDEVMODE, LPSTR, LPSTR, LPDEVMODE, LPSTR, WORD);
HINSTANCE GetPrLib (LPSTR DrvName);
int DevModeSize (LPSTR drvname,LPSTR device,LPSTR port);
EXTDEVMODE GetExtDevAddr (HINSTANCE hPrLib);
GLOBALHANDLE GetDevNames (LPSTR devname,LPSTR drvname,LPSTR pname);
#endif

struct ParData {
  LPVOID hBaseInst;             // Instanz eines Mdi - Datensatzes,
                                // die zum Laden eines Schluessels verwendet
                                // werden kann
  LPVOID hExtInst;              // Eingentlichen Dokumenten - Instanz
  };

GLOBALHANDLE ConvertText (char FAR *txt,GLOBALHANDLE hGPar);

#define PRINTER_INCLUDED
#endif

