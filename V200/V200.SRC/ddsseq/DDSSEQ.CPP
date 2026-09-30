/*****************************************************************************
 FILE:              DDSSEQ.CPP
 Sequentielle Anbindung fuer Resource - Files
*****************************************************************************/

////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in ddseq.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ddsseq/rev/ddsseq.cpv   1.1   26 Nov 1996 09:52:36   GERHOLD  $
//  $Log:   P:/marille/clinicum/ddsseq/rev/ddsseq.cpv  $
// 
//    Rev 1.1   26 Nov 1996 09:52:36   GERHOLD
// Umstellung auf 32 Bit
// 
//    Rev 1.0   08 Sep 1996 12:38:30   HANNES
// Initial revision.
// 
//
#include <windows.h>
#include "dds32.h"
#define MODULENUM 911
HANDLE hLibInst;

extern void OnExit ();
DLLExport void _export FAR PASCAL DBReset ()
  {
  OnExit ();
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



DLLExport LPVOID _export FAR PASCAL DataDict_NewTableDef (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  static WORD done = TRUE ;
  *error = FALSE ;
  *size = sizeof(WORD);
  return &done;
  }

