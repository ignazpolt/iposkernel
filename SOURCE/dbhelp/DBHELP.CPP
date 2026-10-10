////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in dbhelp.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/dbhelp.cpv   1.4   05 Oct 1998 11:09:12   Gerhold  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/dbhelp.cpv  $
// 
//    Rev 1.4   05 Oct 1998 11:09:12   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   08 Nov 1996 13:27:36   HANNES
// Einbau des Replikators
// 
//    Rev 1.2   02 Feb 1996 10:42:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   02 Jan 1996 22:16:10   HANNES
// WEP exportieren
// 
//    Rev 1.0   24 Jun 1994 16:44:44   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   19 Apr 1994 10:47:46   HANNES
// Initial revision.
// 
//
#include <windows.h>
#include "dds32.h"


HINSTANCE hLibInst;


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
extern void FreeRepNodes ();
extern "C" {
int WINAPI WEP (int nShutdownFlag)
  {
  FreeRepNodes();
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

