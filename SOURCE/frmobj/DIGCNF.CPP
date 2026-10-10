/*
**      Digitizer - Konfiguration
**
*/
// $Header:   P:/marille/clinicum/frmobj/rev/digcnf.cpv   1.4   05 Oct 1998 11:18:10   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/digcnf.cpv  $
// 
//    Rev 1.4   05 Oct 1998 11:18:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   02 Feb 1996 10:49:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:15:06   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Nov 1994 18:01:12   HANNES
// Digitizer reaktiviert
// 
//    Rev 1.0   24 Jun 1994 16:45:40   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.2   23 Aug 1993 19:31:06   HANNES
// ...
// 
//    Rev 1.1   09 Dec 1992 18:53:30   HANNES
// Pfad, in dem die *.ddl's gesucht werden (gesetzt auf .\)
// 
//    Rev 1.0   02 Dec 1992 15:28:20   HANNES
// Initial revision.
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "dds.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "digitize.hpp"
#define MODULENUM   137
#include "winass.hpp"

static int DigRefCount = 0 ;
static HINSTANCE hDigLib;
static struct DIGICNF digcnf;

static SETUPFNC SforPoint,SforCont;
static MSGCHECK CheckDigiMsg;

/*-------< Laden der Library mit dem Namen >---------*/
DLLExport HINSTANCE _export WINAPI GetDigLib (LPSTR Name)
  {
  HINSTANCE res = LoadLibrary (Name);

#ifdef WIN32
  if (res != NULL) {
#else
  if (res >= 32) {
#endif
    // nochmaliger Check, Window's ist ja zu bloed
    GETDIGNAME GetName = GETDIGNAME (GetProcAddress (res,"GETDIGNAME")) ;
    if (GetName == NULL) {
      FreeLibrary (res);
      res = LoadLibrary (Name);
      }
    }

  return res ;
  }

/*------------------------------------------------------*/
/*      Lesen, Schreiben des Konfigurations - Files     */
/*------------------------------------------------------*/
struct DIGICNF FAR *mydigcnf;
DLLExport void _export WINAPI SetDigCnf (DIGICNF FAR *cnf)
  {
  mydigcnf = cnf;
  }

/*------------------------------------------------------*/
/*           Bedienung des Digitizers                   */
/*------------------------------------------------------*/
/*-----< Laden der DLL >------*/
DLLExport void _export WINAPI InitDigLib ()
  {
  if (DigRefCount == 0) {       // Mehrfaches Laden innerhalb einer
                                // Instanz vermeiden
    DBWIN_ASSERT (mydigcnf != NULL);
    if (mydigcnf->LibName[0] != '\0') {
      hDigLib = GetDigLib (mydigcnf->LibName);
      SforPoint = (SETUPFNC) GetProcAddress (hDigLib,"SETUPFORPOINT");
      SforCont = (SETUPFNC) GetProcAddress (hDigLib,"SETUPFORCONT");
      CheckDigiMsg = (MSGCHECK) GetProcAddress (hDigLib,"DIGIMSG");
      }
    }
  DigRefCount++ ;
  }

DLLExport void _export WINAPI InitDigMse ()
  {
  static char *DigMseName = "digmse.ddl" ;
  hDigLib = GetDigLib (DigMseName);
  SforPoint = (SETUPFNC) GetProcAddress (hDigLib,"SETUPFORPOINT");
  SforCont = (SETUPFNC) GetProcAddress (hDigLib,"SETUPFORCONT");
  CheckDigiMsg = (MSGCHECK) GetProcAddress (hDigLib,"DIGIMSG");
  }

/*-----< DLL wieder rausschmeissen >------*/
DLLExport void _export WINAPI ExitDigLib ()
  {
  DigRefCount--;
  if (DigRefCount == 0) {
#ifdef WIN32
    if (hDigLib != NULL)
#else
    if (hDigLib >= 32)
#endif
      FreeLibrary (hDigLib);
    SforPoint = SforCont = NULL;
    CheckDigiMsg = NULL;
    }
  }

DLLExport void _export WINAPI ExitDigMse ()
  {
  if (hDigLib) FreeLibrary (hDigLib);
  SforPoint = SforCont = NULL;
  CheckDigiMsg = NULL;
  }

/*-----< Digitizer fuer die Punkteingabe vorbereiten >------*/
static HWND lastWnd;
DLLExport void _export WINAPI SetupForPoint (HWND hWnd,BOOL state)
  {
  if (SforPoint != NULL) {
    (* SforPoint) (lastWnd = hWnd,LPSTR (mydigcnf->CnfStr),state);
    }
  }

/*-----< Digitizer fuer die Kontureingabe vorbereiten >------*/
DLLExport void _export WINAPI SetupForCont (HWND hWnd,BOOL state)
  {
  if (SforCont != NULL) {
    (* SforCont) (lastWnd = hWnd,LPSTR (mydigcnf->CnfStr),state) ;
    }
  }

DLLExport HWND _export WINAPI GetDigWindow ()
  {
  return lastWnd;
  }

/*-----< Meldungen nach sinnvollen Digitizer - Meldungen untersuchen >------*/
LONG WINAPI DigiMsg (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL FAR *done,MAPINFO FAR *mi)
  {
  LONG res ;
  if (CheckDigiMsg != NULL) {
    res = (* CheckDigiMsg) (hWnd,msg,wP,lP,(BOOL FAR *) done,(MAPINFO FAR *)mi);
    }
  else {
    res = 0L ;
    *done = FALSE ;
    }
  return res ;
  }

