// $Header:   F:/marille/clinicum/dmwapi/rev/printer.cpv   1.31   18 May 2000 09:55:10   Hannes  $
// $Log:   F:/marille/clinicum/dmwapi/rev/printer.cpv  $
// 
//    Rev 1.31   18 May 2000 09:55:10   Hannes
// Fehlerhandling bei Fehlern in StartDoc
// 
//    Rev 1.30   29 Mar 2000 20:07:38   Martin
// Aehem, kleiner Fehler ...
// 
//    Rev 1.29   29 Mar 2000 18:32:46   Martin
// TranslateA5hoch und -quer
// 
//    Rev 1.28   18 Nov 1999 18:51:38   Martin
// PaperSize aus dem dmw.ini mit devicename ermitteln
// (in in->dwPaperSize stand immer der Original-Name)
// 
//    Rev 1.27   28 Oct 1999 00:21:02   Hannes
// ChangePaperSource
// 
//    Rev 1.26   07 Jul 1999 15:14:06   Martin
// fixes Papierformat per dmw.ini einstellbar
// 
//    Rev 1.25   26 May 1999 08:15:02   Hannes
// Config:TranslateA5
// 
//    Rev 1.24   18 Dec 1998 15:49:42   Martin
// Schacht-Handling verbessert
// 
//    Rev 1.23   07 Dec 1998 18:41:20   Martin
// DOPCINFO initialisieren
// 
//    Rev 1.22   23 Oct 1998 19:25:22   Martin
// Fehlerabfrage bei StartDoc()
// 
//    Rev 1.21   05 Oct 1998 11:12:42   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.20   07 Aug 1998 00:01:50   Hannes
// SetPrinterCaption
// 
//    Rev 1.19   27 Jul 1998 09:52:34   Hannes
// Doppelseitiger Druck
// 
//    Rev 1.18   09 Jul 1998 10:49:16   Hannes
// Ret - Wert von SetPrinter abgefragt
// 
//    Rev 1.17   22 Apr 1998 16:13:02   Hannes
// GetPaperSize..
// 
//    Rev 1.16   07 Apr 1998 19:50:56   Hannes
// Alte Version des Druckbereiches wieder deaktiviert
// 
//    Rev 1.15   17 Mar 1998 12:42:32   Hannes
// Abfrage der Formulare des Druckers, ev. ummappen
// 
//    Rev 1.14   03 Mar 1998 10:08:06   Hannes
// GetPrivateProfileString beim GetDefaultPrinter
// 
//    Rev 1.13   15 Dec 1997 18:00:04   Hannes
// Diverse Druckproblembehebungen
// 
//    Rev 1.12   19 Nov 1997 18:46:02   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.11   12 Jun 1997 16:59:30   Martin
// StartFrame ...
// 
//    Rev 1.10   25 Apr 1997 16:59:44   Martin
// Meldung, wenn kein Standarddrucker
// 
//    Rev 1.9   04 Apr 1997 18:38:06   Martin
// Escapes -> entsprechende neue Funktionen
// 
//    Rev 1.8   04 Apr 1997 16:14:52   Martin
// Fehler
// 
//    Rev 1.7   04 Apr 1997 16:03:00   Martin
// 32Bit-faehig gemacht
// 
//    Rev 1.6   02 Feb 1996 10:46:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   20 May 1995 14:14:22   HANNES
// Invalidieren des aktiven MDI - Childs
// 
//    Rev 1.4   16 Feb 1995 12:50:12   HANNES
// 
//    Rev 1.3   20 Jan 1995 15:51:16   HANNES
// 
//    Rev 1.2   12 Dec 1994 12:09:54   HANNES
// 
//    Rev 1.1   21 Nov 1994 09:52:48   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:48:54   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.10   04 Jan 1994 17:38:32   HANNES
// Druckereinstellung und Konfiguration des Druckers
// 
//    Rev 1.9   05 Sep 1993 22:03:32   HANNES
// Exportierte Inline - Funktionen rausgenommen
// 
//    Rev 1.8   15 Jul 1993 16:45:58   GERHOLD
// Drucker in DMWAPI verlagert
// 
//    Rev 1.7   14 Jun 1993 18:07:32   HANNES
// EnableWindow vor SetFocus
// 
//    Rev 1.6   14 Jun 1993 13:08:16   HANNES
// Setfocus vor dem Zerstoeren des Abbruchfensters
// 
//    Rev 1.5   11 Jun 1993 12:14:04   HANNES
// Aktivieren des Hauptfenstern (Noch erfolglos..)
// 
//    Rev 1.4   10 Jun 1993 18:47:46   HANNES
// Layout ebenfalls disablen..
// 
//    Rev 1.3   02 Jun 1993 19:52:42   HANNES
// Funktionsprotypen der SL Funktionen
// 
//    Rev 1.2   17 Mar 1993 17:30:22   HANNES
// EnableDDS,DisableDDS
// 
//    Rev 1.1   14 Feb 1993 16:03:56   HANNES
// Aufruf von Startprint und Endprint (Schiebelehre)
// 
//    Rev 1.0   02 Dec 1992 15:41:38   HANNES
// Initial revision.

#include	<windows.h>		  // MS header
#include	<stdio.h>		    // und
#include	<string.h>

#ifdef WIN32
  #include	<wingdi.h>
  #define _INC_PRINT
#else
  #include	<print.h>
#endif

#include	<commdlg.h>
#include "dds32.h"
#include	"globmem.h"
#include 	"printer.hpp"
#define MODULENUM   65
#include "winass.hpp"
#define MDICLIEN_MAIN
#include "mdiclien.hpp"

extern HINSTANCE hLibInst;
HWND hFrameWin;
PRCALLBACK prcbfnc;

/*--------< Verwaltung von mehreren Buffern >-------*/
#define MAXPRINTERS     3
static Printer *InstalledPrinter[MAXPRINTERS];      // Maximal 3 Drucker zulaessig

static Printer *NewPrinter(LPSTR DeviceName,LPSTR DriverName,LPSTR PortName)
  {
  BOOL found = FALSE ;
  int IndToSet = -1 ;
  Printer *Act;
  for (int i = 0 ; i < MAXPRINTERS ; i++) {
    if (InstalledPrinter[i] != NULL) {
      Act = InstalledPrinter[i];
      if (lstrcmp (Act->DeviceName,DeviceName) == 0) 
        found = TRUE ,
        Act->PrReference ++ ;
      if (found) return InstalledPrinter[i] ;
      }
    else {
      if (IndToSet < 0) IndToSet = i ;
      }
    }
  // Drucker wurden nicht gefunden -> Drucker installieren
  if (IndToSet >= 0) {
    Act = new Printer;
    InstalledPrinter[IndToSet] = Act;
    lstrcpy (Act->DeviceName,DeviceName);
    lstrcpy (Act->DriverName,DriverName);
    lstrcpy (Act->PortName,PortName);
    Act->PrReference = 1 ;
    Act->Initialized = TRUE ;
    return InstalledPrinter[IndToSet] ;
    }
  return 0 ;            // Keine Moeglichkeit mehr
  }

DLLExport void _export WINAPI FreePrinter(Printer *Act)
  {
  if (-- Act->PrReference == 0) {
    for (int i = 0 ; i < MAXPRINTERS ; i++) {
      if (InstalledPrinter[i] == Act) {
        InstalledPrinter[i] = NULL ;
        break ;
        }
      }
    delete Act ;
    }
  }

#ifdef UEBERLEGT
DLLExport Printer *_export WINAPI GetPrinter(void)
  {
  // Show Dialog - Box to do the rest
  Printer *temp = new Printer;
  Printer *res = NULL ;
  if (PrinterConfig (GetActiveWindow(),
                        temp->DriverName,sizeof(temp->DriverName),
                        temp->DeviceName,sizeof(temp->DeviceName),
                        temp->PortName,sizeof(temp->PortName))) {
    res = NewPrinter (temp->DeviceName,temp->DriverName,
                                temp->PortName);
    }
  delete temp;
  return res ;
  }
#endif

extern LPSTR WINAPI GetIniName ();
#ifdef WIN32
void CheckProperties (HANDLE ph,DEVMODE FAR *in,LPSTR devname)
  {
  int FixPaperSize = (int)GetPrivateProfileInt (devname,"PaperSize",-1,GetIniName ());
  if (FixPaperSize >= 0) {
    in->dmPaperSize = FixPaperSize;
    }
  else {
    if (in->dmPaperSize == DMPAPER_A5) {
      char szTemp[32];
      BOOL doTranslate = TRUE ;
      char szEntry[32];
      if (in->dmOrientation == DMORIENT_LANDSCAPE)
        lstrcpy(szEntry,"TranslateA5quer");
      else
        lstrcpy(szEntry,"TranslateA5hoch");
      if (GetPrivateProfileString ("Config",szEntry,"",szTemp,sizeof (szTemp),GetIniName ()) > 0) {
        if (lstrcmp (szTemp,"no") == 0)
          doTranslate = FALSE;
        }
      else {
        if (GetPrivateProfileString ("Config","TranslateA5","",szTemp,sizeof (szTemp),GetIniName ()) > 0) {
          if (lstrcmp (szTemp,"no") == 0)
            doTranslate = FALSE;
          }
        }
      if (doTranslate) {
        FORM_INFO_1 fi[32];
        DWORD size,count;
        if (EnumForms (ph,1,LPBYTE(fi),sizeof(fi),&size,&count)) {
          for (int i = 0 ; i < int(count) ; i++) {
            if (lstrcmp (fi[i].pName,"A5") == 0) return ;
            }
          }
        // Nix gefunden -> Umsetzen
        in->dmPaperSize = DMPAPER_A4 ;
        if (in->dmOrientation == DMORIENT_LANDSCAPE)
          in->dmOrientation = DMORIENT_PORTRAIT;
        else
          in->dmOrientation = DMORIENT_LANDSCAPE;
        }
      }
    }
  }
#endif
extern GLOBALHANDLE GetDevMode (LPSTR devname,LPSTR driver,LPSTR port,int orientation,int defaultSource,int paperSize,LPVOID DevMode);
DLLExport Printer *_export WINAPI GetPrinter(LPSTR devname,
                  int orientation,int defaultsource,int papersize,LPVOID DevMode
                                      )
  {
  char drivername[64];
  char portname[64];
  GLOBALHANDLE hGdnames = GetDevNames (devname,drivername,portname);
  if (hGdnames != NULL) {
    // Ermitteln der DEVICEMODE
    DEVNAMES FAR *d = (DEVNAMES FAR *) GlobalLock (hGdnames);
    DEVMODE FAR *in = NULL,FAR *out = NULL;
#ifdef WIN32
    HANDLE ph;
    OpenPrinter(LPSTR(d)+d->wDeviceOffset,&ph,NULL);
    WIN_ASSERT (ph);
#else
    HINSTANCE hPrLib = GetPrLib (LPSTR(d)+d->wDriverOffset);
    WIN_ASSERT (hPrLib);
    EXTDEVMODE ea = GetExtDevAddr (hPrLib);
    if (ea != NULL) {
#endif
      // Der Drucker scheint sich einstellen zu lassen
      int devmodesize = DevModeSize (
                                  LPSTR(d)+d->wDriverOffset,
                                  LPSTR(d)+d->wDeviceOffset,
                                  LPSTR(d)+d->wOutputOffset
                                    );
      in  = (DEVMODE FAR *) GetGlobMem (devmodesize);
      if (DevMode != NULL)
        lmemcpy (in,DevMode,min(GetBlockSize(DevMode),devmodesize));

      out = (DEVMODE FAR *) GetGlobMem (devmodesize);
      // Ermitteln des Defaults
#ifdef WIN32
      DocumentProperties(0,ph,devname,in,in,DM_OUT_BUFFER | DM_IN_BUFFER);
#else
      (*ea) (0,
		                  hPrLib,
		                  in,
		                  devname,
		                  portname,
		                  NULL,
		                  (LPSTR)NULL,
		                  DM_OUT_BUFFER
            );
#endif
      // Modifizieren dieses Wertes
      if (orientation >= 0)
        in->dmOrientation = orientation;
      // merken des defaults fuer den Papierschacht
      int MyDefaultSource = in->dmDefaultSource;
      if (defaultsource > 0)
        in->dmDefaultSource = defaultsource;
      if (papersize >= 0)
        in->dmPaperSize = papersize;
#ifdef WIN32
      CheckProperties (ph,in,devname);
      DocumentProperties(0,ph,devname,out,in,DM_IN_BUFFER | DM_OUT_BUFFER);
#else
      (*ea) (0,
		                  hPrLib,
		                  out,
		                  devname,
		                  portname,
		                  in,
		                  (LPSTR)NULL,
		                  DM_IN_BUFFER | DM_OUT_BUFFER
            );
#endif
#ifdef WIN32
      ClosePrinter(ph);
      ph = NULL;
#else
      }
    FreeLibrary (hPrLib);
#endif
    GlobalUnlock (hGdnames);
    GlobalFree (hGdnames);

    Printer *res = new Printer;
    res->DefaultSource = MyDefaultSource;
    lstrcpy (res->DeviceName,devname);
    lstrcpy (res->DriverName,drivername);
    lstrcpy (res->PortName,portname);
    res->PrReference = 1 ;
    res->Initialized = TRUE ;
    res->DevMode = out ;
    if (in != NULL)
      FreeGlobMem (in);
    return res;
    }
  else {
    Printer *res = GetPrinter (TRUE);
    GLOBALHANDLE hGres = GetDevMode (devname,"","",orientation,defaultsource,papersize,DevMode);
    DEVMODE FAR * h = (DEVMODE FAR *) GlobalLock (hGres);
    DEVMODE FAR *n = (DEVMODE FAR *) GetGlobMem (h->dmSize);
    lmemcpy (n,h,h->dmSize);
    res->DevMode = n;
    GlobalUnlock (hGres);
    GlobalFree (hGres);

    return res;
    }
  }

DLLExport void _export WINAPI ModifyPrinterSource(Printer *Pr,int defSource)
  {
  if (Pr->PrDC) {
    if (defSource > 0)
      Pr->DevMode->dmDefaultSource = defSource;
    else
      Pr->DevMode->dmDefaultSource = Pr->DefaultSource;
    ResetDC (Pr->PrDC,Pr->DevMode);
    }
  }

DLLExport Printer *_export WINAPI GetPrinter(BOOL Default)
  {
  WIN_ASSERT (Default);     // Der andere Modus ist rausgefallen
  char szTemp[64];
  char DeviceName[64];
  char DriverName[64];
  char PortName[64];

  // Laden des Default - Printers
  if (GetPrivateProfileString ("windows","device","",szTemp,sizeof (szTemp),GetIniName ()) == 0)
    GetProfileString ("windows","device","",szTemp,sizeof (szTemp));
  WIN_ASSERT_TEXT(*szTemp != '\0',"kein Standarddrucker definiert !!!!");
  LPSTR h = _fstrtok (szTemp,",") ;     lstrcpy (DeviceName,h);
        h = _fstrtok (NULL,  ",") ;     lstrcpy (DriverName,h);
        h = _fstrtok (NULL,  ",") ;     lstrcpy (PortName,h);
  return NewPrinter (DeviceName,DriverName,PortName);
  }

/*--------< Handling der Abbruch - Funktion >-------*/
BOOL bUserAbort;
HWND hDlgPrint;
DLLExport BOOL _export WINAPI AbortProc (HDC PrinterDC,short nCommand)
  {
  MSG msg;
  while (!bUserAbort && (PeekMessage (&msg,NULL,0,0,PM_REMOVE))) {
    if (!hDlgPrint || !IsDialogMessage (hDlgPrint,&msg)) {
      TranslateMessage (&msg);
      DispatchMessage (&msg);
      }
    }
  return !bUserAbort ;
  }

HWND GetActiveChild (HWND hFrameWin)
  {
  for (HWND hChild = GetWindow (hFrameWin,GW_CHILD) ; IsWindow (hChild) ; hChild = GetWindow (hChild,GW_HWNDNEXT)) {
    char classname[128];
    GetClassName (hChild,classname,sizeof(classname));
    if (lstrcmp (classname,MDIClientClass) == 0) {
      return HWND (SendMessage (hChild,WM_MDIGETACTIVE,0,0L));
      }
    }
  return 0;
  }

DLLExport BOOL _export CALLBACK PrintDlgProc (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP)
  {
  HWND ActiveChild;
  switch (msg) {
    case WM_INITDIALOG :
      EnableMenuItem (GetSystemMenu(hDlg,FALSE),SC_CLOSE,MF_GRAYED);
      return TRUE;
    case WM_COMMAND :
      bUserAbort = TRUE ;
      EnableWindow (hFrameWin,TRUE);
      DestroyWindow (hDlg);
      ActiveChild = GetActiveChild (hFrameWin);
      if (IsWindow (ActiveChild))
        InvalidateRect (ActiveChild,NULL,FALSE);
      hDlgPrint = 0 ;
      return TRUE ;
      break ;
    }
  return FALSE ;
  }

void Printer::SetAbort ()
  {
  bUserAbort = FALSE ;
  // ModeLess - DialogBox
  hDlgPrint = CreateDialog (hLibInst,"PrintDlgBox",
                                hFrameWin,DLGPROC (PrintDlgProc));
  EnableWindow (hFrameWin,FALSE);
#ifdef WIN32
  wError = SetAbortProc (PrDC,(ABORTPROC) AbortProc);
  if (short(wError) < 0)
    DWORD error = GetLastError();
#else
  wError = Escape (PrDC,SETABORTPROC,0,(LPSTR) AbortProc,NULL);
#endif
  }

void Printer::ReleaseAbort ()
  {
  if (hDlgPrint) {
    EnableWindow (hFrameWin,TRUE);
    HWND ActiveChild = GetActiveChild (hFrameWin);
    if (IsWindow (ActiveChild))
      InvalidateRect (ActiveChild,NULL,FALSE);
    DestroyWindow (hDlgPrint);
    hDlgPrint = 0;
    }
  }

/*---------< Holen des PrinterDC's >---------*/
HDC Printer::PrinterDC (BOOL DoIt)
  {
  if (PrDC) return PrDC ;  // Er existiert eh schon
  if (DoIt) {              // Es muss wirklich der PrinterDC erzeugt werden
    if (Initialized) {
      for (LPSTR h = DriverName ; ((*h != '.') && (*h)) ; h++) ;
      BOOL do_set;
      if (do_set = (*h == '.')) *h = '\0' ;
      PrDC = CreateDC (DriverName,DeviceName,PortName,DevMode);
      if (do_set) *h = '.' ;
      if (PrDC) {
        // Setzen der Papierabmasse
        if (prcbfnc != NULL)
          (* prcbfnc) (PRCALLBACK_SETSTARTPRINTIG);
        PrinterArea.top = PrinterArea.left = 0 ;
        PrinterArea.right = GetDeviceCaps (PrDC,HORZRES);
        PrinterArea.bottom = GetDeviceCaps (PrDC,VERTRES);
        }
      }
    return PrDC;
    }
  else return PrinterIC();
  }

HDC Printer::PrinterDC ()
  {
  return PrinterDC(FALSE);
  }

Printer::Printer () 
  { } ;

Printer::~Printer (void) 
  { 
  if (PrIC) DeleteDC (PrIC);
  if (DevMode != NULL)
    FreeGlobMem (DevMode);
  }

HDC Printer::PrinterIC ()
  {
  if (PrIC) {
    ReferenceCount++ ;
    return PrIC ;
    }
  if (Initialized) {
    for (LPSTR h = DriverName ; (*h != '.') && (*h) ; ) h++ ;
    BOOL do_reset;
    if (do_reset = (*h == '.')) *h = '\0' ;
    PrIC = CreateIC (DriverName,DeviceName,PortName,DevMode);
    if (do_reset) *h = '.' ;
    if (PrIC) {
      // Setzen der Papierabmasse
      PrinterArea.top = PrinterArea.left = 0 ;
      PrinterArea.right = GetDeviceCaps (PrIC,HORZRES);
      PrinterArea.bottom = GetDeviceCaps (PrIC,VERTRES);
      ReferenceCount = 1 ;
      }
    return PrIC;
    }
  else return NULL ;
  }

void Printer::FullArea(LPRECT r)
  {
  r->top = r->left = 0 ;
  HDC hAct = (PrDC) ? PrDC : PrIC ;
  r->right = GetDeviceCaps (hAct,HORZRES);
  r->bottom = GetDeviceCaps (hAct,VERTRES);
  }

void Printer::PaperSize (LPRECT r)
  {
  HDC hAct = (PrDC) ? PrDC : PrIC ;
  POINT ptg;
  Escape (hAct,GETPHYSPAGESIZE,NULL,NULL,(LPSTR) &ptg);
  FullArea (r);
#ifdef NEUEVERSION
  Escape (hAct,GETPRINTINGOFFSET,NULL,NULL,(LPSTR) &pt);
  r->left   = - pt.x ;
  r->top   = - pt.y ;
  r->right  = r->left + ptg.x ;
  r->bottom  = r->top + ptg.y ;
#else
  int dx = ptg.x - r->right ;
  int dy = ptg.y - r->bottom ;
  r->left   = - dx / 2 ;
  r->right  += (dx - dx / 2) ;
  r->top    = - dy / 2 ;
  r->bottom += (dy - dy / 2) ;
#endif
  }

void Printer::SetPrinterArea(LPRECT r)
  {
  PrinterArea = *((fRECT FAR *)r);
  }

void Printer::ReleasePrDC()
  {
  if ((PrDC == 0) && (PrIC)) {
    ReferenceCount -- ;
    if (ReferenceCount == 0)
      DeleteDC (PrIC) , PrIC = 0 ;
    }
  }

void Printer::ReleaseDC()
  {
  ReleaseAbort();
  if (PrDC) {
    DeleteDC(PrDC);
    PrDC = 0 ;
    if (prcbfnc != NULL)
      (* prcbfnc) (PRCALLBACK_SETENDPRINTING);
    }
  }

/*--------< Verschiedene Druck - Funktionen >-----*/
BOOL Printer::StartPrint(LPSTR szMessage)
  {
  if (PrDC) {
    SetAbort ();  if (wError <= 0) return FALSE;
#ifdef WIN32
    DOCINFO di;
    lmemset(&di,'\0',sizeof(DOCINFO));
    di.cbSize = sizeof(di);
    di.lpszDocName = szMessage;
    di.lpszOutput = NULL;
    // di.lpszDatatype = "N.A.";
    // di.fwType = 0;
    wError = StartDoc (PrDC,&di);
    if (short(wError) < 0) {
      DWORD error = GetLastError();
      char szText[64];
      wsprintf(szText, "Fehler bei StartDoc (%ld)", error);
      // DBWIN_ASSERT_TEXT(FALSE,szText);
      if (MessageBox (NULL,szText,"Druckfehler: ",MB_OK | MB_ICONHAND) == IDOK)
        return FALSE;
      }
#else
    wError = Escape (PrDC,STARTDOC,lstrlen(szMessage),szMessage,NULL);
#endif
    if (wError <= 0)               return FALSE;
    }
  return TRUE;
  }

void Printer::EndPrint()
  {
  if ((PrDC) && (wError > 0)) {
#ifdef WIN32
    wError = EndDoc (PrDC);
#else
    wError = Escape (PrDC,ENDDOC,0,NULL,NULL);
#endif
    DeleteDC (PrDC) , PrDC = 0;
    if (prcbfnc != NULL)
      (* prcbfnc) (PRCALLBACK_SETENDPRINTING);
    }
  }

void Printer::StartFrame()
  {
#ifdef WIN32
  if ((PrDC) && (wError > 0))
    wError = StartPage (PrDC);
#endif
  }

void Printer::NewFrame()
  {
  if ((PrDC) && (wError > 0))
#ifdef WIN32
    wError = EndPage (PrDC);
#else
    wError = Escape (PrDC,NEWFRAME,0,NULL,NULL);
#endif
  }

void Printer::GetPrinterArea(LPRECT r)
  {
  *((fRECT FAR *)r) = PrinterArea;
  }

void Printer::CheckError()
  {
  if (wError <= 0) {
    }
  }

WORD Printer::HorzRes()
  {
  HDC hAct = ActDC();
  return GetDeviceCaps (hAct,HORZRES);
  }

WORD Printer::VertRes()
  {
  HDC hAct = ActDC();
  return GetDeviceCaps (hAct,VERTRES);
  }

HDC Printer::ActDC()
  {
  return (PrDC) ? PrDC : PrIC ;
  }

/*-----< Banding >-----*/
BOOL Printer::BandSupport()
  {
  int nBands = NEXTBAND ;
  if ((PrDC) && (wError > 0) &&
      (Escape (PrDC,QUERYESCSUPPORT,sizeof (int),(LPSTR)& nBands,NULL))) {
    Banding = TRUE ;
    return TRUE ;
    }
  else {
    Banding = FALSE ;
    return FALSE ;
    }
  }

typedef BOOL (WINAPI *FPABORTPROC) (HDC,short);
BOOL Printer::NextBand()
  {
  BOOL res ;
  if ((PrDC) && (wError > 0)) {
    RECT rcBand;
    wError = Escape (PrDC,NEXTBAND,0,NULL,(LPSTR) &rcBand);
    // Aufruf der Abbruch - Funktion
    AbortProc (PrDC,0);
    res = ((!IsRectEmpty (&rcBand)) && (wError > 0)) ;
    }
  else
    res = FALSE;
  return res;
  }

/*------< Speicherverwaltung >-----*/
LPVOID Printer::operator new (size_t size)
  {
  return GetGlobMem (size);
  }

void Printer::operator delete (LPVOID obj)
  {
  FreeGlobMem (obj);
  }

DLLExport void _export WINAPI PrCallback (HWND hWnd,PRCALLBACK fnc)
  {
  hFrameWin = hWnd;
  prcbfnc = fnc;
  }



