// $Header:   P:/marille/clinicum/image/rev/tiffimg.cpv   1.12   06 Apr 1999 13:04:52   Martin  $
// $Log:   P:/marille/clinicum/image/rev/tiffimg.cpv  $
// 
//    Rev 1.12   06 Apr 1999 13:04:52   Martin
// unnoetige Datumsfunktionen raus
// 
//    Rev 1.11   13 Oct 1998 12:57:42   Gerhold
// Aenderung wegen VC6 (HINSTANCE)
// 
//    Rev 1.10   31 Mar 1998 12:16:28   Martin
// ScanWizardSpezialBehandlung
// 
//    Rev 1.9   25 Mar 1998 15:03:54   Martin
// Microtek Spezialbehandlung
// 
//    Rev 1.8   25 Apr 1997 12:31:12   Martin
// Bildkomrimierung
// 
//    Rev 1.7   18 Mar 1997 11:38:58   Martin
// GetTwainSources auf LeadTools umgestellt
// 
//    Rev 1.6   02 Feb 1996 10:49:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   24 May 1995 14:07:00   MARTIN
// Fehlerhandling in das Script verlagert...
// 
//    Rev 1.4   03 May 1995 11:39:34   MARTIN
// ScreenMachine und Deskscan 2.1 Spezialbehandlung nachgetragen
// 
//    Rev 1.3   15 Dec 1994 20:16:48   HANNES
// 
//    Rev 1.2   08 Dec 1994 21:48:38   HANNES
// 
//    Rev 1.1   17 Oct 1994 15:03:02   HANNES
// Synchronisation mit Marille
// 
//    Rev 1.0   24 Jun 1994 16:51:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.13   19 Apr 1994 16:53:38   MARTIN
// Fehler bei Abbruch des Scanvorganges korrigiert
// 
//    Rev 1.12   14 Apr 1994 14:48:48   MARTIN
// Fehler bei noch nicht eingestellter TWAIN source korrigiert
// 
//    Rev 1.11   13 Apr 1994 20:46:24   MARTIN
// Auslagerung in Header file
// 
//    Rev 1.10   09 Feb 1994 19:11:56   MARTIN
// Lampstate
// 
//    Rev 1.9   04 Feb 1994 16:46:28   MARTIN
// TWAIN sauberer
// 
//    Rev 1.8   29 Nov 1993 09:00:24   MARTIN
// Eleminieren des DIB - Managers
// 
//    Rev 1.7   22 Sep 1993 10:58:16   MARTIN
// Version nach St. Poelten
// 
//    Rev 1.6   23 Aug 1993 18:50:34   MARTIN
// Image-Umstellung (Native-Mode, DIBs)
// 
//    Rev 1.5   05 Apr 1993 10:44:28   HANNES
// ??
// 
//    Rev 1.4   22 Feb 1993 17:26:40   HANNES
// Loeschen des Cachefiles bei nicht erfolgreichem Scannen
// 
//    Rev 1.3   29 Jan 1993 19:11:00   HANNES
// Direktimport
// 
//    Rev 1.2   13 Dec 1992 20:05:52   HANNES
// Verhindern der SetCap (DCOR_LANDSCAPE), da's ja sowieso selbst gemacht wird
// 
//    Rev 1.1   07 Dec 1992 14:22:10   HANNES
// Einbau der 270 Grad Drehung
// 
//    Rev 1.0   02 Dec 1992 16:23:46   HANNES
// Initial revision.
////////////////////////////////////////////////////////////////////////
//
//      Arbeiten mit Tiff - Files
//      -------------------------
//
//      Die Library dient fuer:
//              - Verwaltung von Tiff - Files in einem sequentiellen
//                Stream mit einem Schluessel, der in einer Btrieve
//                Datei verwaltet wird
//              - Kleine Cache Verwaltung fuer diese Files, wobei
//                die zuletzt verwendeten Files auf die Platte
//                geladen werden
//              - Lesen von Tiff - Files in ein device - independend
//                bitmap Format
//              - Schreiben von Tiff - Files aus dem DIB Format unter
//                Angabe der Komprimierung
//              - Scannen von Bildern unter Verwendung einer Twain
//                Source (die Tiff - Files liefern kann...)
//	        - Umwandlung von device unabhaengigen Bitmaps in
//                device - abhaengige Bilder
//              - Verschiedene Hilfsfunktionen (Histogrammberechnung,
//                LUT - Transformation, Berechnung der optimalen LUT ...)
//
//      26. Okt. 1992           H.S.
////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <io.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include "dds32.h"

#include "l_bitmap.h"

#ifndef WIN32
extern "C" {
#include <winmem32.h>
}
#endif

#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#define USE_TWAIN
#define MIMAGE_CLASS
#include "image.hpp"
#include "dc.h"              // needed for TWAIN definitions

extern "C" {
#include "wbtrv.h"
  }

#include "btrieve.hpp"
#include "ddsmsg.h"              // needed for TWAIN definitions

#define MODULENUM 68
#include "winass.hpp"

// Prototypen fuer tiffimg.cpp, die nicht aus der DLL exportiert werden
BOOL DCOpenDSM ();
BOOL DCCloseDSM ();
VOID DCTerminate ();
VOID DCInitialize (pDC_IDENTITY,HWND);
BOOL SelectTWAINSource (LPSTR src);

///////////////////////////////////////////////////////////////////////
//      Library - Version
///////////////////////////////////////////////////////////////////////
DLLExport int _export WINAPI TI_GetVersion () { return 0x103 ; }

// Liste der Versionen:
// 0x101: Version ohne Kompression
// 0x102: Version mit Kompression durch ImageMan Funktionen
// 0x103: Version mit Kompression durch LeadTools
//

///////////////////////////////////////////////////////////////////////
//      Local Data und Functions
///////////////////////////////////////////////////////////////////////
static HINSTANCE hLibInst;


//      Kontrolle, ob File noch auf dem Medium Platz hat
//////////////////////////////////////////////////////////////////
static BOOL CheckDriveSpace (LPSTR drv,DWORD space)
  {
  space += space / 2 ;          // Ein bisschen Reserve sollte schon sein

  static unsigned Drive ;
  if (drv[1] == ':') {
    if (drv[0] >= 'a') Drive = drv[0] - 'a' + 1;
    else               Drive = drv[0] - 'A' + 1;
    }
  else {

#ifdef WIN32
    char szDir[256];
    GetCurrentDirectory (sizeof(szDir), szDir);
#else
    _dos_getdrive (&Drive);
#endif
    }

  BOOL res = FALSE ;
#ifdef WIN32
  //---------------------------------------------------------------------------
  // soll ich das szDir von oben nehmen oder genuegt NULL???? ausprobieren!!!
  //---------------------------------------------------------------------------
  DWORD SectorsPerCluster, BytesPerSector,         
        NumberOfFreeClusters, TotalNumberOfClusters;

  if (GetDiskFreeSpace (NULL, &SectorsPerCluster, &BytesPerSector,
                              &NumberOfFreeClusters, &TotalNumberOfClusters)) {
    DWORD freesize = TotalNumberOfClusters *
                     SectorsPerCluster *
                     BytesPerSector;
    res = (freesize > space) ;
    }
#else
  _diskfree_t fr;
  
  if (_dos_getdiskfree(Drive,&fr) == 0) {
    DWORD freesize = DWORD (fr.avail_clusters) *
                        DWORD (fr.sectors_per_cluster) *
                           DWORD (fr.bytes_per_sector) ;
    res = (freesize > space) ;
    }
#endif

  return res;
  }


static GLOBALHANDLE lasthDIB;

DLLExport GLOBALHANDLE _export WINAPI GetScannedImage()
  {
  GLOBALHANDLE res = lasthDIB;
  lasthDIB = NULL;
  return res;
  }

/////////////////////////////////////////////////////////////////////////
//      Scannen der Images
/////////////////////////////////////////////////////////////////////////
BOOL DCDSOpen;              // glue code flag for an Open Source
BOOL DCDSMOpen;             // glue code flag for an Open Source Manager
HINSTANCE hDSMDLL = 0;         // handle to Source Manager for explicit load
DSMENTRYPROC lpDSM_Entry;   // entry point to the SM
DC_IDENTITY appID, dsID;    // storage for App and DS (Source) states
HWND hScanWnd;

VOID Explain_Error(LPSTR state)
  {
  // show the error
  if (state == NULL)
    state = "Having a general Problem" ;
#ifdef OLD_VERSION
  MessageBox (hScanWnd, state, "TWAIN Error", MB_OK);
#else
  char outstr[256];
  lstrcpy(outstr, "TWAIN Error: ");
  lstrcat(outstr, state);
  WIN_ASSERT_TEXT(FALSE, outstr);
#endif
  }  // Explain_Error


static BOOL RotateManual = FALSE;   // Bild selber drehen nach Scannen
static BOOL SMSpezialBehandlung = FALSE;  // Bild kopieren nach Scannen
static BOOL DS21SpezialBehandlung = FALSE;  // DeskScan II 2.1 Spezial
static UINT DS21PT_GRAY = UINT(-1);   // HPs eigenwillige Definitionen der
static UINT DS21PT_RGB = UINT(-1);    // ICAP_PIXELTYPE Werte
static UINT DS21PT_BW = UINT(-1);     // (werden durch dmw.ini befuellt)
static float FixResolution = (float)1.0E10;

static BOOL GetCompleteImage ()
  {
  DC_UINT32 hBitMap;
  DC_UINT16 dcRC = DCRC_FAILURE;
  GLOBALHANDLE hbm_acq;    // handle to bit map from Source to ret to App

  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_IMAGE,
                        DAT_IMAGENATIVEXFER,
                        MSG_GET,
                        (DC_MEMREF)&hBitMap);
  hbm_acq = (GLOBALHANDLE)LOWORD(hBitMap);

  if (dcRC == DCRC_XFERDONE) {
    lasthDIB = hbm_acq;
#define SCHEISS_SCREEN_MACHINE 1
#ifdef SCHEISS_SCREEN_MACHINE
    if (SMSpezialBehandlung) {
#ifdef GLOBAL_SIZE_FUNKTIONIERT
      DWORD size = GlobalSize(hbm_acq);
#else
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hbm_acq);
      lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
      DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
      DWORD size = lpbi->biSizeImage + lpbi->biSize + dwColorTableSize;
      GlobalUnlock(hbm_acq);
#endif
      lasthDIB = GlobalAlloc(GMEM_MOVEABLE,size);
      LPVOID src = GlobalLock(hbm_acq);
      LPVOID dst = GlobalLock(lasthDIB);
      hmemcpy(dst,src,size);
      GlobalUnlock(lasthDIB);
      GlobalUnlock(hbm_acq);
#ifdef HANDLE16BIT
      GlobalFree(hbm_acq);
#else
  #ifdef WIN32
      GlobalFree(hbm_acq);
  #else
      Global32Free(hbm_acq,0);
  #endif
#endif
      }
#endif
// #define WINMEM32TEST 1
#ifdef WINMEM32TEST
    hbm_acq = lasthDIB;
    DWORD size = GlobalSize(hbm_acq);
    WORD res = Global32Alloc(size,(LPWORD)&lasthDIB,size,0);
    LPVOID src = GlobalLock(hbm_acq);
    LPVOID dst = GlobalLock(lasthDIB);
    DWORD size32 = GlobalSize(lasthDIB);
    hmemcpy(dst,src,size);
    GlobalUnlock(lasthDIB);
    GlobalUnlock(hbm_acq);
    GlobalFree(hbm_acq);
    hbm_acq = lasthDIB;
    size32 = GlobalSize(hbm_acq);
    lasthDIB = GlobalAlloc(GMEM_MOVEABLE,size);
    src = GlobalLock(hbm_acq);
    dst = GlobalLock(lasthDIB);
    size32 = GlobalSize(lasthDIB);
    hmemcpy(dst,src,size);
    GlobalUnlock(lasthDIB);
    GlobalUnlock(hbm_acq);
    res = Global32Free(hbm_acq,0);
#endif
    if (FixResolution < 1.0E9) {
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(lasthDIB);
      lpbi->biXPelsPerMeter = lpbi->biYPelsPerMeter = LONG(FixResolution * 39.37);
      GlobalUnlock(lasthDIB);
      }
    if (RotateManual)
      lasthDIB = RotateImage(lasthDIB);
    }
  else
    lasthDIB = NULL;
  RotateManual = FALSE;

  return (dcRC == DCRC_XFERDONE) && (hbm_acq != NULL);
  } // GetCompleteImage

//      Transfer eines Images einleiten
////////////////////////////////////////////////////////////////////
VOID DCTransferImage()
  {
  // DC information
  DC_IMAGEINFO      dcImageInfo;
  DC_PENDINGXFERS   dcPendingXfer;

  // NOTE: you must do the clean up of old images yourself

  // explicitly initialize the our flags
  dcPendingXfer.Count = 0;

  // Tell the Source what type of transfer you want.  I use the default, 
  // NATIVE so no set of ICAP_XFERMECH is required

  // Native also negates the need to ask for a pixel type ICAP_PIXELTYPE
  // DCSetPixelType(DCTY_UINT16, (DC_UINT32)DCPT_RGB);
  // pixeltype=DCGetPixelType();


  // Get the image information, nice to know a little about the image the Source
  // will be sending
  if ((*lpDSM_Entry) (&appID,
                      &dsID,
                      DG_IMAGE,
                      DAT_IMAGEINFO,
                      MSG_GET,
                      (DC_MEMREF)&dcImageInfo) == DCRC_SUCCESS) {


      // Ask Source if more images are coming.  I only support one image per transfer
      // in this example but do/while loop is included to help? those who wish to
      // support more than one.
      do {
        GetCompleteImage ();
        // Required for proper 6<->7 state transitions
        if ((*lpDSM_Entry)(&appID,
                           &dsID,
                           DG_CONTROL,
                           DAT_PENDINGXFERS,
                           MSG_ENDXFER,
                           (DC_MEMREF)&dcPendingXfer) != DCRC_SUCCESS){
            dcPendingXfer.Count = 0;  // trash remaining images
        }
      } while (dcPendingXfer.Count != 0);

    // Notify Parent
    PostMessage (hScanWnd,WMU_XFERDONE,0,0L);

    // shut down the Source if there are no more images pending
    DCTerminate();
    }
  } // DCTransferImage


//      Oeffnen des Twain - Source Managers
/////////////////////////////////////////////////////
BOOL DCOpenDSM ()
  {
  DC_UINT16     dcRC;
  OFSTRUCT      OpenFiles;
#define       WINDIRPATHSIZE 160
  char          WinDir[WINDIRPATHSIZE];
  DC_STR32      DSMName;


  // Only open SM if currently closed
  if (DCDSMOpen!=TRUE) {

    // Open the SM, Refer explicitly to the library so we can post a nice
    // message to the the user in place of the "Insert TWAIN.DLL in drive A:"
    // posted by Windows if the SM is not found.

    GetWindowsDirectory (WinDir, WINDIRPATHSIZE);
    // Hardcode to seperate dca_main.c & dca_glue.c more completely
    // lstrcpy (DSMName, "TWAIN.DLL");

    // NOTE: could use hInst from elsewhere and call name in from resource
    LoadString (hLibInst, IDS_DSMNAME, DSMName,  sizeof(DC_STR32));

    lstrcat (WinDir, "\\");
    lstrcat (WinDir, DSMName);


    if ((OpenFile(WinDir, &OpenFiles, OF_EXIST) != -1) &&
           (hDSMDLL =     LoadLibrary(DSMName)) != NULL &&
#ifndef WIN32
           (hDSMDLL >=    32) &&
#endif
           (lpDSM_Entry = (DSMENTRYPROC)GetProcAddress(hDSMDLL, "DSM_ENTRY")) 
                        != NULL) {

          /* This call performs four important functions:
              - opens/loads the SM
              - passes the handle to the app's window to the SM
              - returns the SM assigned appID.id field
              - be sure to test the return code for SUCCESSful open of SM
          */
      dcRC = (*lpDSM_Entry)(&appID, 
                                NULL,
                                DG_CONTROL,
                                DAT_PARENT,
                                MSG_OPENDSM,
                                (DC_MEMREF)&hScanWnd);


      switch (dcRC) {
        case DCRC_SUCCESS:
          // Needed for house keeping.  Do single open and do not
          // close SM which is not already open ....
          DCDSMOpen = TRUE;
          break;

        case DCRC_FAILURE:
        default:
          // Trouble opening the SM, inform the user
          DCDSMOpen = FALSE;
          Explain_Error (NULL);
          break;
        }
      }
    else {
      DCDSMOpen = FALSE;
      // Explain_Error (NULL);    return FALSE genuegt
      }
    }  // end of if open

  // Let the caller know what happened
  return (DCDSMOpen);
  } // DCOpenDSM

//      Schliessen des Source - Managers
//////////////////////////////////////////////////////////////////////
BOOL DCCloseDSM ()
  {
  DC_UINT16 dcRC;

  // Only close something which is already open
  WIN_ASSERT (DCDSMOpen);
  /* This call performs one important function:
     - tells the SM which application, appID.id, is requesting SM to close
     - be sure to test return code, failure indicates SM did not close !!
  */
  dcRC = (*lpDSM_Entry)(&appID,
                        NULL,
                        DG_CONTROL,
                        DAT_PARENT,
                        MSG_CLOSEDSM,
                        &hScanWnd);

  if (dcRC != DCRC_SUCCESS){
    // Trouble closing the SM, inform the user
    Explain_Error (E_CLOSEDSM);
    }
  else {
    DCDSMOpen = FALSE;        
    // Explicitly free the SM library
    if (hDSMDLL){
      FreeLibrary (hDSMDLL);
      hDSMDLL=0;
      }
    }

  // Let the caller know what happened
  return (DCDSMOpen);
  } // DCCloseDSM

static BOOL lastUI = FALSE;
static VOID DCDisableDS ()
  {
  DC_UINT16         dcRC=DCRC_FAILURE;
  DC_USERINTERFACE  dcUI;

  // only disable open Source's
  WIN_ASSERT (DCDSOpen);
  // Hide the Source UI
  dcUI.hParent = hScanWnd;
  dcUI.ShowUI  = lastUI;
  dcUI.ModalUI = TRUE;

  dcRC = (*lpDSM_Entry)(&appID,
                          &dsID,
                          DG_CONTROL,
                          DAT_USERINTERFACE,
                          MSG_DISABLEDS,
                          (DC_MEMREF)&dcUI);

  if (dcRC != DCRC_SUCCESS)
    Explain_Error (E_DISABLEDS);

  return;
  } // DCDisableDS


/***********************************************************************
 * FUNCTION: DCCloseDS
 *
 * ARGS:    none
 *
 * RETURNS: none
 *
 * NOTES:    1). only attempt to close an open Source
 *           2). call Source Manager to:
 *                - ask that Source identified by info in dsID close itself
 */
static VOID DCCloseDS (VOID)
  {
  DC_UINT16         dcRC=DCRC_FAILURE;

  WIN_ASSERT(DCDSOpen);
  // Close an open Source
  dcRC = (*lpDSM_Entry)(&appID,
                            NULL,
                            DG_CONTROL,
                            DAT_IDENTITY,
                            MSG_CLOSEDS,
                            &dsID);

  // show error on close
  if (dcRC!= DCRC_SUCCESS)
    Explain_Error (E_CLOSEDS);
  else
    DCDSOpen = FALSE;
  } // DCCloseDS


//  Deinitialisieren der Datenbanken
/////////////////////////////////////////
VOID DCTerminate ()
  {
  if (DCDSOpen) {
    DCDisableDS ();     // this is required by 'the rules'
    DCCloseDS ();
    }
  if (DCDSMOpen)
    DCCloseDSM ();
  return;
  } // DCTerminate

DLLExport VOID _export WINAPI DCExit (VOID)
  {
  DCTerminate ();
  }

VOID DCInitialize (pDC_IDENTITY pIdentity, HWND hMainWnd)
  {
  appID = *pIdentity;    // get copy of app info
  hScanWnd = hMainWnd;       // get copy of app window handle
  } // DCInitialize

DLLExport BOOL _export WINAPI ProcessDCMessage(LPMSG lpMsg)
  {
  DC_UINT16  dcRC=DCRC_NOTDSEVENT;
  DC_EVENT   dcEvent;


  // Only ask Source Manager to process event if there is a Source connected.

  /* A Source provides a modeless dialog box as its user interface.
   * The following call relays Windows messages down to the Source's
   * UI that were intended for its dialog box.  It also retrieves TWAIN
   * messages sent from the Source to our  Application.
   */

  if ((DCDSOpen) && (DCDSMOpen)) {
    dcEvent.pEvent = (DC_MEMREF)lpMsg;
    dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_CONTROL,
                        DAT_EVENT,
                        MSG_PROCESSEVENT,
                        (DC_MEMREF)&dcEvent);


    switch (dcEvent.DCMessage){
      case MSG_XFERREADY:
        DCTransferImage();
        break;

      case MSG_CLOSEDSREQ:
        PostMessage (hScanWnd,WMU_XFERDONE,0,0L);
        DCTerminate();
        break;

      case MSG_NULL:
        // No message from the Source to the App break;
      default:
        // possible new message
        break;
      }  // END OF MESSAGE SWITCH
    }

  // tell the caller what happened
  return (dcRC == DCRC_DSEVENT);        // returns TRUE or FALSE
  } // ProcessDCMessage


/***********************************************************************
 * FUNCTION: ScanConfigure
 *
 * ARGS:    none
 *
 * RETURNS: dcRC TWAIN status return code
 *
 * NOTES:   1). call the Source Manager to:
 *              - have the SM put up a list of the available Sources
 *              - get information about the user selected Source from
 *                NewDSIdentity, filled by Source
 */

DLLExport BOOL _export WINAPI ScanConfigure (VOID)
  {
  DC_UINT16 dcRC;
  DC_IDENTITY NewDSIdentity;

  if (DCOpenDSM ()) {
    // I will settle for the system default.  Shouldnt I get a highlight
    // on system default without this call?
    dcRC = (*lpDSM_Entry)(&appID,
                          NULL,
                          DG_CONTROL,
                          DAT_IDENTITY,
                          MSG_GETDEFAULT,
                          (DC_MEMREF)&NewDSIdentity);

    /* This call performs one important function:
    - should cause SM to put up dialog box of available Source's
    - tells the SM which application, appID.id, is requesting, REQUIRED
    - returns the SM assigned NewDSIdentity.id field, you check if changed
      (needed to talk to a particular Data Source)
    - be sure to test return code, failure indicates SM did not close !!
    */
    dcRC = (*lpDSM_Entry)(&appID,
                          NULL,
                          DG_CONTROL,
                          DAT_IDENTITY,
                          MSG_USERSELECT,
                          (DC_MEMREF)&NewDSIdentity);

    /* Check if the user changed the Source and react as apporpriate.
    - DCRC_SUCCESS, log in new Source
    - DCRC_CANCEL,  keep the current Source
    - default,      check down the codes in a status message, display result
    */

    switch (dcRC){
      case DCRC_SUCCESS:
        dsID = NewDSIdentity;
        break;
    
      case DCRC_CANCEL:
        break;

      default:
        Explain_Error (E_USERSELECT);
        break;
      }

    DCCloseDSM ();
    }

  // Let the caller know what happened
  return (dcRC);
  }  // Scanconfigure


static BOOL DCOpenDS (VOID)
  {
  DC_UINT16         dcRC=DCRC_FAILURE;

  if (!DCDSOpen) {
    // This will open the Source.
    dcRC = (*lpDSM_Entry)(&appID,
                              NULL,
                              DG_CONTROL,
                              DAT_IDENTITY,
                              MSG_OPENDS,
                              &dsID);

    if (dcRC == DCRC_SUCCESS){
      // do not change flag unless we successfully open
      DCDSOpen = TRUE;
      }
    else {
      // Trouble opening the Source
      Explain_Error (NULL);
      }
    }

  return DCDSOpen;
  } // DCOpenDS

BOOL DCEnableDS (BOOL UserInterface)
  {
  BOOL Result = FALSE;
  DC_UINT16 dcRC = DCRC_FAILURE;
  DC_USERINTERFACE dcUI;

  // only enable open Source's
  WIN_ASSERT (DCDSOpen);
  // This will display the Source User Interface. The Source should only display
  // a user interface that is compatible with the group defined
  // by appID.SupportedGroups (in our case DG_IMAGE | DG_CONTROL)
  dcUI.hParent = hScanWnd;
  dcUI.ShowUI  = lastUI = UserInterface;
  dcUI.ModalUI = TRUE;
  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_CONTROL,
                        DAT_USERINTERFACE,
                        MSG_ENABLEDS,
                        (DC_MEMREF)&dcUI);

  if (dcRC!=DCRC_SUCCESS)
    Explain_Error (E_ENABLEDS);
  else Result = TRUE;

  return Result;
  } // DCEnableDS

//
//      Setzen der Source Capabilitys
/////////////////////////////////////////////////////////////////////
static DC_UINT16 SetSourceCap (DC_UINT16 Cap,int Type,LONG Data)
  {
  DC_CAPABILITY dccp;
  DC_UINT16 dcRC = DCRC_FAILURE;

  WIN_ASSERT (DCDSOpen);
  GLOBALHANDLE hGmem;

  hGmem = GlobalAlloc (GHND,sizeof(DC_ONEVALUE));
  pDC_ONEVALUE d = pDC_ONEVALUE (GlobalLock (hGmem)) ;

  d->ItemType = Type ;
  d->Item = Data ;

  dccp.ConType = DCON_ONEVALUE ;
  dccp.Cap = Cap ;
  dccp.hContainer = hGmem;

  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_CONTROL,
                        DAT_CAPABILITY,
                        MSG_SET,
                        (DC_MEMREF)&dccp);

  GlobalUnlock (hGmem);
  GlobalFree (hGmem);

  return dcRC ;
  }

static DC_UINT16 SetSourceCap (DC_UINT16 Cap, DC_FIX32 Data)
  {
  DC_CAPABILITY dccp;
  DC_UINT16 dcRC = DCRC_FAILURE;

  WIN_ASSERT (DCDSOpen);
  GLOBALHANDLE hGmem;

  hGmem = GlobalAlloc (GHND,sizeof(DC_ONEVALUE));
  pDC_ONEVALUE d = pDC_ONEVALUE (GlobalLock (hGmem)) ;

  d->ItemType = DCTY_FIX32 ;
  d->Item = *((LPLONG)(&Data)) ;

  dccp.ConType = DCON_ONEVALUE ;
  dccp.Cap = Cap ;
  dccp.hContainer = hGmem;

  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_CONTROL,
                        DAT_CAPABILITY,
                        MSG_SET,
                        (DC_MEMREF)&dccp);

  GlobalUnlock (hGmem);
  GlobalFree (hGmem);

  return dcRC ;
  }

DC_FIX32 GetDCFix32 (int x)
  {
  DC_FIX32 res;
  res.Whole = x ;
  res.Frac = 0;
  return res;
  }

DC_FIX32 FloatToFIX32 (float floater)
  {
	DC_FIX32 Fix32_value;
	DC_INT32 value = (DC_INT32) (floater * 65536.0 + 0.5);
	Fix32_value.Whole = (DC_INT16)(value >> 16);
	Fix32_value.Frac = (DC_UINT16)(value & 0x0000ffffL);
	return Fix32_value;
  }

LONG GetLongFix32 (int x)
  {
  LONG res = 0L;
  res = LONG(x) << 16 ;

  return res;
  }

BOOL SetCap (LPWORD Orientation, float FAR *Resolution, LPWORD Pixeltype, LPWORD Lampstate)
  {
  BOOL fault;

  // Nur 1 Image bitte
  SetSourceCap (CAP_XFERCOUNT,DCTY_INT16,1);
  SetSourceCap (ICAP_UNITS,DCTY_UINT16,DCUN_INCHES);
  SetSourceCap (ICAP_COMPRESSION,DCTY_UINT16,DCCP_NONE);

  if ((Pixeltype == NULL) || (*Pixeltype == 0))
    fault = FALSE;
  else if (*Pixeltype == 1)
    fault = (SetSourceCap (ICAP_PIXELTYPE,DCTY_UINT16,
                           DS21SpezialBehandlung ? DS21PT_GRAY : DCPT_GRAY)
                != DCRC_SUCCESS);
  else if (*Pixeltype == 2)
    fault = (SetSourceCap (ICAP_PIXELTYPE,DCTY_UINT16,
                           DS21SpezialBehandlung ? DS21PT_RGB : DCPT_RGB)
                != DCRC_SUCCESS);
  else if (*Pixeltype == 3)
    fault = (SetSourceCap (ICAP_PIXELTYPE,DCTY_UINT16,
                           DS21SpezialBehandlung ? DS21PT_BW : DCPT_BW)
                != DCRC_SUCCESS);

  if ((Lampstate == NULL) || (*Lampstate == 0))
    fault = FALSE;
  else if (*Lampstate == 1)
    fault = (SetSourceCap (ICAP_LAMPSTATE,DCTY_BOOL,FALSE)
                != DCRC_SUCCESS);
  else if (*Lampstate == 2)
    fault = (SetSourceCap (ICAP_LAMPSTATE,DCTY_BOOL,TRUE)
                != DCRC_SUCCESS);

  if (!fault) {
    if (Resolution != NULL) {
      fault = (SetSourceCap (ICAP_XRESOLUTION,FloatToFIX32(*Resolution))
                != DCRC_SUCCESS);
      fault |= (SetSourceCap (ICAP_YRESOLUTION,FloatToFIX32(*Resolution))
                != DCRC_SUCCESS);
      }
    }

  if (!fault) {
    if ((Orientation == NULL) || (*Orientation == 0))
      fault = FALSE;
    else if (*Orientation == 1)
      fault = (SetSourceCap (ICAP_ORIENTATION,DCTY_UINT16,DCOR_PORTRAIT)
                != DCRC_SUCCESS);
    else if (*Orientation == 2)
      fault = (SetSourceCap (ICAP_ORIENTATION,DCTY_UINT16,DCOR_LANDSCAPE)
                != DCRC_SUCCESS);
    else if (*Orientation == 3) {
      RotateManual = TRUE;
      }
    }

//  SetSourceCap (ICAP_AUTOBRIGHT,DCTY_BOOL,TRUE);   // ????

  return !fault ;
  }

static BOOL SetImageLayout (float FAR *left,
                            float FAR *top,
                            float FAR *right,
                            float FAR *bottom)
  {
  if ((left == NULL) || (top == NULL) ||
      (right == NULL) || (bottom == NULL))
    return TRUE;
  DC_IMAGELAYOUT dcil;
  DC_UINT16 dcRC = DCRC_FAILURE;
  WIN_ASSERT (DCDSOpen);
  dcil.DocumentNumber = dcil.PageNumber = dcil.FrameNumber = 1;
  dcil.Frame.Left = FloatToFIX32 (*left) ;
  dcil.Frame.Top = FloatToFIX32 (*top) ;
  dcil.Frame.Right = FloatToFIX32 (*right) ;
  dcil.Frame.Bottom = FloatToFIX32 (*bottom) ;
  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_IMAGE,
                        DAT_IMAGELAYOUT,
                        MSG_SET,
                        (DC_MEMREF)&dcil);
  return (dcRC == DCRC_SUCCESS);
  }

BOOL CheckSourceStatus ()
  {
  // Lesen des Source - Status
  BOOL res;
  DC_STATUS dcstat;
  DC_UINT16 dcRC = DCRC_FAILURE;
  WIN_ASSERT (DCDSOpen);
  dcRC = (*lpDSM_Entry)(&appID,
                        &dsID,
                        DG_CONTROL,
                        DAT_STATUS,
                        MSG_GET,
                        (DC_MEMREF)&dcstat);
  if (dcRC == DCRC_SUCCESS) {
    res = (dcstat.ConditionCode == DCCC_SUCCESS) ;
    }
  else res = FALSE ;

  return res;
  }

static void DeskScanSpezialBehandlung(LPSTR source,LPWORD Pixeltype)
  {
  static BOOL SpezialBehandlung = FALSE;
  static int SpezialVersion21 = FALSE;
  static BOOL FirstCall = TRUE;
  static char DeskScanSpezial[64];
  static char DeskScanStr0[64];
  static char DeskScanStr1[64];
  static char DeskScanStr2[64];
  static char DeskScanStr3[64];
  static char DeskScanStr4[64];
  static char DeskScanStr5[64];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"DeskScanSpezial","",
                                 DeskScanSpezial,sizeof(DeskScanSpezial),
                                 MYINI
                                ) > 0
       ) {
      GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr0","",
                               DeskScanStr0,sizeof(DeskScanStr0),MYINI);
      SpezialBehandlung = TRUE;
      if (lstrcmp(DeskScanSpezial,"2.1")) {
        GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr1","",
                                 DeskScanStr1,sizeof(DeskScanStr1),MYINI);
        GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr2","",
                                 DeskScanStr2,sizeof(DeskScanStr2),MYINI);
        GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr3","",
                                 DeskScanStr3,sizeof(DeskScanStr3),MYINI);
        GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr4","",
                                 DeskScanStr4,sizeof(DeskScanStr4),MYINI);
        GetPrivateProfileString (TIFFIMGSECTION,"DeskScanStr5","",
                                 DeskScanStr5,sizeof(DeskScanStr5),MYINI);
        }
      else {
        DS21PT_GRAY = GetPrivateProfileInt (TIFFIMGSECTION,"DeskScan21Grau",2,MYINI);
        DS21PT_RGB  = GetPrivateProfileInt (TIFFIMGSECTION,"DeskScan21Farbe",4,MYINI);
        DS21PT_BW   = GetPrivateProfileInt (TIFFIMGSECTION,"DeskScan21SW",1,MYINI);
        SpezialVersion21 = TRUE;
        }
      }
    FirstCall = FALSE;
    }
  DS21SpezialBehandlung = FALSE;
  if (SpezialBehandlung && (Pixeltype != NULL) && (*Pixeltype != 0)) {
    static char vorher[256];
    static char nachher[256];
    if (lstrcmp(source,DeskScanStr0) == 0) {
      if (SpezialVersion21) {
        DS21SpezialBehandlung = TRUE;
        }
      else {
        if (GetPrivateProfileString (DeskScanStr1,DeskScanStr2,"",
                                 vorher,sizeof(vorher),
                                 DeskScanSpezial
                                ) > 0
           ) {
          char *str = vorher;
          while ((*str) && (*str != ',')) str++;
          if (*Pixeltype == 1)
            strcpy(nachher,DeskScanStr3);
          else if (*Pixeltype == 2)
            strcpy(nachher,DeskScanStr4);
          else if (*Pixeltype == 3)
            strcpy(nachher,DeskScanStr5);
          else {
            WIN_ASSERT(FALSE);  // bitte hier entsprechend behandeln
            }
          strcat(nachher,str);
          WritePrivateProfileString(DeskScanStr1,DeskScanStr2,
                                    nachher,DeskScanSpezial);
          }
        }
      }
    }
  }

static void ScreenMachineSpezialBehandlung(LPSTR source)
  {
  static BOOL SpezialBehandlung = FALSE;
  static BOOL FirstCall = TRUE;
  static char ScreenMachineSpezial[64];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"ScreenMachineSpezial","",
                                 ScreenMachineSpezial,sizeof(ScreenMachineSpezial),
                                 MYINI
                                ) > 0
       ) {
      SpezialBehandlung = TRUE;
      }
    FirstCall = FALSE;
    }
  if (SpezialBehandlung) {
    if (lstrcmp(source,ScreenMachineSpezial) == 0)
      SMSpezialBehandlung = TRUE;
    else
      SMSpezialBehandlung = FALSE;
    }
  }

static void MicrotekSpezialBehandlung(LPSTR source,LPWORD Lampstate)
  {
  static BOOL SpezialBehandlung = FALSE;
  static BOOL FirstCall = TRUE;
  static char MicrotekSpezial[64];
  static char MicrotekIni[64];
  static char MicrotekSection[32];
  static char MicrotekEntry[32];
  static char MicrotekOn[32];
  static char MicrotekOff[32];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"MicrotekSpezial","",
                                 MicrotekSpezial,sizeof(MicrotekSpezial),
                                 MYINI
                                ) > 0
       ) {
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekIni","",
                               MicrotekIni,sizeof(MicrotekIni),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekSection","",
                               MicrotekSection,sizeof(MicrotekSection),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekEntry","",
                               MicrotekEntry,sizeof(MicrotekEntry),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekOn","",
                               MicrotekOn,sizeof(MicrotekOn),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekOff","",
                               MicrotekOff,sizeof(MicrotekOff),MYINI);
      SpezialBehandlung = TRUE;
      }
    FirstCall = FALSE;
    }
  if (SpezialBehandlung && (Lampstate != NULL) && (*Lampstate != 0)) {
    if (lstrcmp(source,MicrotekSpezial) == 0) {
      if (*Lampstate == 1)
        WritePrivateProfileString(MicrotekSection,MicrotekEntry,MicrotekOff,MicrotekIni);
      if (*Lampstate == 2)
        WritePrivateProfileString(MicrotekSection,MicrotekEntry,MicrotekOn,MicrotekIni);
      *Lampstate = 0;  // nicht mehr ueber TWAIN setzen !
      }
    }
  }

static void ScanWizardSpezialBehandlung(LPSTR source,float FAR *Resolution)
  {
  static BOOL SpezialBehandlung = FALSE;
  static BOOL FirstCall = TRUE;
  static char ScanWizardSpezial[64];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"ScanWizardSpezial","",
                                 ScanWizardSpezial,sizeof(ScanWizardSpezial),
                                 MYINI
                                ) > 0
       )
      SpezialBehandlung = TRUE;
    FirstCall = FALSE;
    }
  if (SpezialBehandlung) {
    if (lstrcmp(source,ScanWizardSpezial) == 0) {
      if (Resolution != NULL)
        FixResolution = *Resolution;
      }
    }
  }

//
//      Anfordern Der Daten !!!!
/////////////////////////////////////////////////////////////////////
DLLExport BOOL _export WINAPI StartScan (LPSTR source,
                           float FAR *left,
                           float FAR *top,
                           float FAR *right,
                           float FAR *bottom,
                           float FAR *Resolution,
                           LPWORD Orientation,
                           LPWORD Pixeltype,
                           LPWORD Lampstate,
                           BOOL UserInterface)
  {
  WORD myLampstate;
  if (Lampstate != NULL)
    myLampstate = *Lampstate;
  else
    myLampstate = 0;
  lasthDIB = NULL;
  RotateManual = FALSE;
  FixResolution = (float)1.0E10;
  DeskScanSpezialBehandlung(source,Pixeltype);
  ScreenMachineSpezialBehandlung(source);
  MicrotekSpezialBehandlung(source,&myLampstate);
  ScanWizardSpezialBehandlung(source,Resolution);
  if (DCOpenDSM ()) {
    if (SelectTWAINSource(source) && DCOpenDS ()) {
      if ((CheckSourceStatus ()) && 
          (SetCap (Orientation,Resolution,Pixeltype,&myLampstate)) &&
          (SetImageLayout (left,top,right,bottom)) &&
          (DCEnableDS (UserInterface))) {
        // Theres all ok
        return TRUE;
        }
      DCCloseDS ();
      }
    DCCloseDSM();
    }
  return FALSE;
  }

static char LRStrBuffer[100];
inline LPSTR LRString (HINSTANCE hInst,WORD Id)
  {
  LoadString (hInst,Id,LRStrBuffer,sizeof(LRStrBuffer));
  return LRStrBuffer;
  }

DLLExport void _export WINAPI DCInitialize (HWND hWnd)
  {
  DC_IDENTITY AppIdentity;

  AppIdentity.Id = 0; // init to 0, but Source Manager will assign real value
  AppIdentity.Version.MajorNum = 1;
  AppIdentity.Version.MinorNum = 0;
  AppIdentity.Version.Language = DCLG_USA;
  AppIdentity.Version.Country  = DCCY_USA;

  lstrcpy (AppIdentity.Version.Info,  LRString (hLibInst,IDS_SCANVERSION));

  AppIdentity.ProtocolMajor =    DCON_PROTOCOLMAJOR;
  AppIdentity.ProtocolMinor =    DCON_PROTOCOLMINOR;
  AppIdentity.SupportedGroups =  DG_IMAGE | DG_CONTROL;
  lstrcpy (AppIdentity.Manufacturer,  LRString (hLibInst,IDS_SCANMANUFACTURER));
  lstrcpy (AppIdentity.ProductFamily, LRString (hLibInst,IDS_PRODUCTFAMILY));
  lstrcpy (AppIdentity.ProductName,   LRString (hLibInst,IDS_PRODUCTNAME));

  DCInitialize (&AppIdentity,hWnd);
  }


#ifdef ALTE_VERSION
DLLExport BOOL _export WINAPI GetTWAINSources (LPSTR res)
  {
  BOOL retval = FALSE;
  BOOL wasopen = DCDSMOpen;
  if (DCOpenDSM ()) {
    DC_UINT16 dcRC;
    DC_IDENTITY NewDSIdentity;
    int act_pos = 0;
    for (
        dcRC = (*lpDSM_Entry)(&appID,
                              NULL,
                              DG_CONTROL,
                              DAT_IDENTITY,
                              MSG_GETFIRST,
                              (DC_MEMREF)&NewDSIdentity);
        dcRC == DCRC_SUCCESS;
        dcRC = (*lpDSM_Entry)(&appID,
                              NULL,
                              DG_CONTROL,
                              DAT_IDENTITY,
                              MSG_GETNEXT,
                              (DC_MEMREF)&NewDSIdentity)
        ) {
      lstrcpy(res + act_pos, NewDSIdentity.ProductName);
      act_pos += lstrlen(NewDSIdentity.ProductName) + 1;
      }
    if (act_pos == 0) {
      res[0] = res[1] = '\0';
      retval = FALSE;
      }
    else {
      res[act_pos] = '\0';
      retval = TRUE;
      }
    if (!wasopen)
      DCCloseDSM();
    }
  else {
    res[0] = res[1] = '\0';
    }
  return retval;
  }
#endif

int act_pos = 0;
LPSTR dest = NULL;
L_INT L_EXPORT EXT_CALLBACK EnumTwainSourceProc(L_UCHAR L_FAR *pBuffer, L_INT uBytes, L_VOID L_FAR *pUserData)
  {
  lstrcpy(dest + act_pos, LPSTR(pBuffer));
  act_pos += int(uBytes);
  return SUCCESS;
  }

DLLExport BOOL _export WINAPI GetTWAINSources (LPSTR res)
  {
  act_pos = 0;
  dest = res;
  if (L_TwainEnumSources(hScanWnd,EnumTwainSourceProc,NULL) < SUCCESS) {
    res[0] = res[1] = '\0';
    return FALSE;
    }
  else {
    if (act_pos == 0) {
      res[0] = res[1] = '\0';
      return FALSE;
      }
    else {
      res[act_pos] = '\0';
      return TRUE;
      }
    }
  }


BOOL SelectTWAINSource (LPSTR src)
  {
  DC_UINT16 dcRC;
  DC_IDENTITY NewDSIdentity;
  BOOL res = FALSE;

  if (src != NULL) {
    for (
        dcRC = (*lpDSM_Entry)(&appID,
                              NULL,
                              DG_CONTROL,
                              DAT_IDENTITY,
                              MSG_GETFIRST,
                              (DC_MEMREF)&NewDSIdentity);
        dcRC == DCRC_SUCCESS;
        dcRC = (*lpDSM_Entry)(&appID,
                              NULL,
                              DG_CONTROL,
                              DAT_IDENTITY,
                              MSG_GETNEXT,
                              (DC_MEMREF)&NewDSIdentity)
        ) {
      if (lstrcmp(src, NewDSIdentity.ProductName) == 0) {
        dsID = NewDSIdentity;
        res = TRUE;
        break;
        }
      }
    }

  return res;
  }


//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
  {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hLibInst = hModule;
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
extern "C" {
int WINAPI WEP (int nShutdownFlag)
  {
  return 1 ;
  }

int WINAPI LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  hLibInst = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1 ;
  }
}

#endif

