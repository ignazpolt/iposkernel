//  $Header:   P:/marille/clinicum/dmwapi/rev/dmwapi.cpv   1.5   05 Oct 1998 11:11:38   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/dmwapi.cpv  $
// 
//    Rev 1.5   05 Oct 1998 11:11:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   29 Oct 1997 18:58:46   Hannes
// Textbausteine
// 
//    Rev 1.3   02 Feb 1996 10:46:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   12 Jul 1994 14:40:54   HANNES
// FieldHasCaret
// 
//    Rev 1.1   24 Jun 1994 18:29:36   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:48:44   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   26 Jan 1994 20:51:28   HANNES
// Statistiken, Profiling
// 
//    Rev 1.3   26 Jan 1994 11:32:38   HANNES
// Beim ShutDown ClearQueue loeschen
// 
//    Rev 1.2   25 Jan 1994 18:42:42   HANNES
// 
//    Rev 1.1   06 May 1993 21:29:28   HANNES
// Kuerzelsystem eingebunden
//
//
//    Wep und LibMain
//
#include <windows.h>
#include "dds32.h"
#include "globmem.h"
#include "cntmenu.hpp"

HINSTANCE hLibInst;
int FieldHasCaret;
CLEARQUEUE clearqueue;

DLLExport void _export WINAPI DMWAPI_ShutDown ()
  {
  clearqueue = NULL;
  }

extern CALLCONTEXTFUNCTION CallContextFunction;
DLLExport void _export WINAPI DMWAPI_Setup (CLEARQUEUE q,LPVOID q1,LPVOID q2,CALLCONTEXTFUNCTION cfn)
  {
  clearqueue = q;
  CallContextFunction = cfn;
  }

DLLExport void _export WINAPI ClearQueue ()
  {
  if (clearqueue != NULL)
    (* clearqueue) ();
  }

LPSTR DMWLRString(int Name)
  {
  static char resstr[128];
  LoadString (hLibInst,Name,resstr,sizeof(resstr));
  return resstr;
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

