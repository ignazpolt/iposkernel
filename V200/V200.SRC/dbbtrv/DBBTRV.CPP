////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in dbbtrv.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbbtrv/rev/dbbtrv.cpv   1.4   13 Oct 1998 13:26:52   Gerhold  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/dbbtrv.cpv  $
// 
//    Rev 1.4   13 Oct 1998 13:26:52   Gerhold
// VC6  HANDLE -> HINSTANCE
// 
//    Rev 1.3   02 Feb 1996 10:42:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   02 Jan 1996 22:15:18   HANNES
// WBTRVSTOP in den WEP
// 
//    Rev 1.1   09 Jan 1995 12:08:52   HANNES
// Debugger eingebaut
// 
//    Rev 1.0   24 Jun 1994 16:43:22   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   18 Apr 1994 20:15:54   HANNES
// Initial revision.
//
#include <windows.h>
#include "dds32.h"

extern "C" {
#include "wbtrv.h"
  }

HINSTANCE hLibInst;
extern void ResetResDB ();
extern void CloseAllDataFiles ();
DLLExport void _export WINAPI DBReset ()
  {
  CloseAllDataFiles ();
  ResetResDB ();
  WBTRVSTOP ();
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


