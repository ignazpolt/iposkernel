////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in ddsodbc.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ddssyb/rev/ddssyb.cpv   1.4   17 Dec 1996 11:16:26   GERHOLD  $
//  $Log:   P:/marille/clinicum/ddssyb/rev/ddssyb.cpv  $
// 
//    Rev 1.4   17 Dec 1996 11:16:26   GERHOLD
// 32 Bit Umstellung
// 
//    Rev 1.3   04 Mar 1996 17:24:18   GERHOLD
// DBReset im WEP aufgerufen
// 
//    Rev 1.2   20 Jan 1996 11:16:58   HANNES
// No change.
// 
//    Rev 1.1   02 Jan 1996 22:20:42   HANNES
// 
//    Rev 1.0   04 Dec 1995 10:06:08   HANNES
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
      DBReset ();
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
  DBReset ();
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

