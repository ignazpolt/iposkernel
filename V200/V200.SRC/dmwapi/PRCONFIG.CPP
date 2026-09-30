///////////////////////////////////////////////////////////////////
//      Lesen der Druckerkonfiguration
///////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/dmwapi/rev/prconfig.cpv   1.11   10 Nov 1998 07:57:42   Hannes  $
// $Log:   P:/marille/clinicum/dmwapi/rev/prconfig.cpv  $
// 
//    Rev 1.11   10 Nov 1998 07:57:42   Hannes
// Abfragen des Druckertreibers vor dem Konfigurieren
// 
//    Rev 1.10   05 Oct 1998 11:12:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.9   27 Jul 1998 09:52:40   Hannes
// Doppelseitiger Druck
// 
//    Rev 1.8   16 Jan 1998 15:30:04   Hannes
// Diverse Druckverbesserungen
// 
//    Rev 1.7   15 Dec 1997 18:00:04   Hannes
// Diverse Druckproblembehebungen
// 
//    Rev 1.6   09 Dec 1997 17:26:40   Hannes
// GetDevModeSize auch in 16 Bit unterstuetzen
// 
//    Rev 1.5   13 Nov 1997 09:43:14   Hannes
// Auch beim Defaultdrucken Daten in die Druckdialogbox uebernehmen
// 
//    Rev 1.4   23 Apr 1997 15:32:22   Hannes
// 
//    Rev 1.3   04 Apr 1997 16:02:44   Martin
// 32Bit-faehig gemacht
// 
//    Rev 1.2   03 Apr 1997 17:51:02   MARTIN
// Fehlermeldung, wenn Druckertreiber nicht geladen werden kann (32 bit)
// 
//    Rev 1.1   02 Feb 1996 10:46:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:54   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.3   11 Jan 1994 19:05:12   HANNES
// GetDefaultPrinterName, Einstellungen wenn Standarddrucker aktiv ist
// 
//    Rev 1.2   04 Jan 1994 17:41:24   HANNES
// erweiterte Druckerkonfiguration
// 
//    Rev 1.1   15 Jul 1993 16:40:00   HANNES
// Drucker in die DMWAPI ausgelagert
// 
//    Rev 1.0   02 Dec 1992 15:41:24   HANNES
// Initial revision.

#include <windows.h>
#include <commdlg.h>
#include <stdio.h>

#ifdef WIN32
  #include <wingdi.h>
  #define _INC_PRINT
#else
  #include <print.h>
#endif

#include <string.h>
#include "dds32.h"
#include "globmem.h"
#include "printer.hpp"
#define MODULENUM 64
#include "winass.hpp"

// Laden des Drucker - Teibers
HINSTANCE GetPrLib (LPSTR DrvName)
  {
#ifdef WIN32
  WIN_ASSERT_TEXT(FALSE,"Aufruf von GetPrLib in der 32 Bit Variante");
  return 0;
#else  
  char dnm[64];
  wsprintf (dnm,"%s.drv",DrvName);
  HINSTANCE res = LoadLibrary (dnm);

  return (res >= 32) ? res : 0 ;
#endif
  }

EXTDEVMODE GetExtDevAddr (HINSTANCE hPrLib)
  {
#ifdef WIN32
  WIN_ASSERT_TEXT(FALSE,"Aufruf von GetExtDevAddr in der 32 Bit Variante");
  return 0;
#else  
  return EXTDEVMODE (GetProcAddress (hPrLib, "EXTDEVICEMODE"));
#endif
  }

int DevModeSize (LPSTR drvname,LPSTR device,LPSTR port)
  {
  if (*drvname == '\0') {
    return sizeof(DEVMODE);
    }
#ifdef WIN32
  int res = sizeof(DEVMODE);
  HANDLE ph;
  if (OpenPrinter(device,&ph,NULL)) {
    res = (int)DocumentProperties(0,ph,device,NULL,NULL,0);
    ClosePrinter(ph);
    }
  return res;
#else
  int res ;
  if (drvname) {
    HINSTANCE hPrLib = GetPrLib (drvname);
    WIN_ASSERT (hPrLib);
    EXTDEVMODE lpfn;
    if ((lpfn = (EXTDEVMODE) GetProcAddress (hPrLib, "EXTDEVICEMODE")) != NULL) {
      res = (*lpfn) (0,
		                    hPrLib,
		                    NULL,
		                    device,
		                    port,
		                    (LPDEVMODE)NULL,
		                    (LPSTR)NULL,
		                    0);
      }
    else
      res = sizeof(DEVMODE);
    FreeLibrary (hPrLib);
    }
  else
    res = sizeof(DEVMODE);
  return res;
#endif
  }

DLLExport void _export WINAPI GetDefaultPrinterName (LPSTR Name)
  {
  char szTemp[128];
  GetProfileString ("windows","device","",szTemp,sizeof (szTemp));
  for ( LPSTR h = szTemp ; ((*h) && (*h != ',')) ; h++ );
  *h = '\0';
  // wsprintf (Name,"\\m8%s",LPSTR(szTemp));
  wsprintf (Name,"%s",LPSTR(szTemp));
  }

GLOBALHANDLE GetDevNames (LPSTR devname,LPSTR drvname,LPSTR pname)
  {
  char szTemp[128];
  lmemset (szTemp,'\0',sizeof(szTemp));
  BOOL doDefault = FALSE ;
  if (*devname == '\0') {
    // Standardrucker laden
    GetProfileString ("windows","device","",szTemp,sizeof (szTemp));
    LPSTR h = _fstrtok (szTemp,",") ;     lstrcpy (devname,h);
    doDefault = TRUE ;
    }
  if (GetProfileString ("devices",devname,"",szTemp,sizeof (szTemp)) == 0) {
    // Nix in der DMW - Ini gefunden -> default verwenden
    GetProfileString ("windows","device","",szTemp,sizeof (szTemp));
    LPSTR h = _fstrtok (szTemp,",") ;     lstrcpy (devname,h);
    doDefault = TRUE ;
    GetProfileString ("devices",devname,"",szTemp,sizeof (szTemp));
    }

  LPSTR h = szTemp;
  LPSTR driver = szTemp;
  LPSTR port;
  for ( ; ((*h) && (*h != ',')) ; h++);
  if (*h) port = h + 1 , *h = '\0';
  else    port = h;
  GLOBALHANDLE res = 0;
  if ((*driver) && (*port)) {
    res = GlobalAlloc (GMEM_MOVEABLE,sizeof (DEVNAMES) + 
                lstrlen (devname) + 1 +
                lstrlen (driver) + 1 +
                lstrlen (port) + 1);
    DEVNAMES FAR *lpdev = (DEVNAMES FAR *) GlobalLock (res);
    lpdev->wDriverOffset = sizeof (*lpdev);
    lpdev->wDeviceOffset = lpdev->wDriverOffset + lstrlen(driver) + 1;
    lpdev->wOutputOffset = lpdev->wDeviceOffset + lstrlen(devname) + 1;
    lpdev->wDefault = (doDefault) ? DN_DEFAULTPRN : 0;
    lstrcpy (LPSTR(lpdev) + lpdev->wDriverOffset,driver);
    lstrcpy (LPSTR(lpdev) + lpdev->wDeviceOffset,devname);
    lstrcpy (LPSTR(lpdev) + lpdev->wOutputOffset,port);
    lstrcpy (drvname,driver);
    lstrcpy (pname,port);
    GlobalUnlock (res);
    }
  else {
    *drvname = *pname = '\0';
    }
  return res;
  }

GLOBALHANDLE GetDevMode (LPSTR devname,LPSTR driver,LPSTR port,int orientation,int defaultSource,int paperSize,LPVOID DevMode)
  {
  GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,DevModeSize (driver,devname,port));  // !!!
  DEVMODE FAR * h = (DEVMODE FAR *) GlobalLock (hGres);
  if (DevMode != NULL) lmemcpy (h,DevMode,sizeof(*h));
  lstrcpy (LPSTR(h->dmDeviceName),devname);
  h->dmSpecVersion = 0x30A;
  h->dmSize = sizeof (*h);
  h->dmFields = DM_ORIENTATION | DM_DEFAULTSOURCE | DM_PAPERSIZE | DM_DUPLEX ;
  // if (orientation == -1)
  //  orientation = DMORIENT_ ;
  // if (defaultSource == -1)
  //  defaultSource = DMBIN_AUTO ;
  // if (paperSize == -1)
  //  paperSize = DMPAPER_A4 ;
  h->dmPaperSize = paperSize;
  h->dmOrientation = orientation;
  h->dmDefaultSource = defaultSource ;
  GlobalUnlock (hGres);
  return (hGres);
  }

void IntializepChunk (LPPRINTDLG lpPrintChunk,HWND hWnd,LPSTR devname,int orientation,int defaultSource,int papersize,LPVOID DevMode)
  {
  char driver [64];
  char port [64];
  lpPrintChunk->lStructSize         = sizeof(PRINTDLG);
  lpPrintChunk->hwndOwner           = hWnd;
  lpPrintChunk->hDevNames           = GetDevNames (devname,driver,port);
  // if (lpPrintChunk->hDevNames != 0)
  lpPrintChunk->hDevMode          = GetDevMode (devname,driver,port,orientation,defaultSource,papersize,DevMode);
  // else
  //  lpPrintChunk->hDevMode          = (HANDLE)NULL;
  lpPrintChunk->hDC                 = (HDC)NULL;
  lpPrintChunk->Flags               = PD_PRINTSETUP;
  lpPrintChunk->nFromPage           = 0;
  lpPrintChunk->nToPage             = 0;
  lpPrintChunk->nMinPage            = 0;
  lpPrintChunk->nMaxPage            = 0;
  lpPrintChunk->nCopies             = 0;
  lpPrintChunk->hInstance           = (HINSTANCE)NULL;
  lpPrintChunk->lCustData           = 0L;
  lpPrintChunk->lpfnPrintHook	    = NULL;
  lpPrintChunk->lpfnSetupHook	    = NULL;
  lpPrintChunk->lpPrintTemplateName = (LPSTR)NULL;
  lpPrintChunk->lpSetupTemplateName = (LPSTR)NULL;
  lpPrintChunk->hPrintTemplate      = (HANDLE)NULL;
  lpPrintChunk->hSetupTemplate      = (HANDLE)NULL;
  }


DLLExport BOOL _export WINAPI PrinterConfig (HWND hWnd,LPSTR devname,
                    int FAR &orientation,int FAR &defaultsource,
                    int FAR &papersize,LPVOID DevModeIn,LPVOID FAR &DevModeOut)
  {
  PRINTDLG prdlg;
  BOOL res;

  DevModeOut = NULL;
  IntializepChunk (&prdlg,hWnd,devname,orientation,defaultsource,papersize,DevModeIn);

  int pdres = PrintDlg(&prdlg);
  if (pdres != 0) {
    // Uebergabe der Daten
    LPDEVNAMES lpd = LPDEVNAMES (GlobalLock (prdlg.hDevNames));
    lstrcpy (devname,LPSTR (lpd) + lpd->wDeviceOffset);
    if (lpd->wDefault == DN_DEFAULTPRN)
      *devname = '\0';
    else
      lstrcpy (devname,LPSTR (lpd) + lpd->wDeviceOffset);
    GlobalUnlock (prdlg.hDevNames);
    LPDEVMODE lpm = LPDEVMODE (GlobalLock (prdlg.hDevMode));
    orientation = lpm->dmOrientation;
    defaultsource = lpm->dmDefaultSource;
    papersize = lpm->dmPaperSize;
    DevModeOut = GetGlobMem (lpm->dmSize);
    lmemcpy (DevModeOut,lpm,lpm->dmSize);
    GlobalUnlock (prdlg.hDevMode);
    res = TRUE ;
    }
  else res = FALSE ;
  if (prdlg.hDevNames) GlobalFree (prdlg.hDevNames);
  if (prdlg.hDevMode)  GlobalFree (prdlg.hDevMode);
  return res;
  }


