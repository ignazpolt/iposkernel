////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in ddsodbc.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ddsodbc/rev/ddsodbc.cpv   1.2   02 Feb 1996 10:46:06   GERHOLD  $
//  $Log:   P:/marille/clinicum/ddsodbc/rev/ddsodbc.cpv  $
// 
//    Rev 1.2   02 Feb 1996 10:46:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Feb 1995 11:15:42   HANNES
//  
// 
//    Rev 1.0   20 Feb 1995 21:55:34   HANNES
// Initial revision.
// 
//
#include <windows.h>
#include "dds32.h"

HANDLE hLibInst;


extern void DisConnect ();
DLLExport void _export WINAPI DBReset ()
  {
  DisConnect ();
  }

DLLExport LPVOID _export WINAPI DataDict_NewTableDef (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  static WORD done = TRUE ;
  *error = FALSE ;
  *size = sizeof(WORD);
  return &done;
  }


//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HANDLE hModule, DWORD fdwReason, LPVOID lpReserved)
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
