/*****************************************************************************
 FILE:              DDSORA.CPP
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           MedORA - Oracle - Anbindung an das Clinicum (Medica, Steinmaur)
 PRODUCT:           DDSORA.DLL
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    Frank Loeliger
 
 DATE:              14.02.1996
 
 DESCRIPTION:       entry points for database interface DLL
                    
 ENVIRONMENT:       Windows Application
                    MS Visual C++ V1.50
                    Oracle Call Interface, Release 7.1
                    MKS - RCS is used for the revision controlling
                    
 VERSION:           0.1    The DLL is manually ported from the sybase DLL Rev 1.2
 
 STATUS:            develop
 
 MODIFIED:
   10.03.96 FL  DBReset called from WEP
   14.02.96 FL  created this document based on sybase code
   
*****************************************************************************/

////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in ddsodbc.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ddsora/rev/ddsora.cpv   1.2   17 Dec 1996 17:06:34   HANNES  $
//  $Log:   P:/marille/clinicum/ddsora/rev/ddsora.cpv  $
// 
//    Rev 1.2   17 Dec 1996 17:06:34   HANNES
// 
//    Rev 1.1   31 May 1996 20:48:22   MARTIN
// 
//    Rev 1.0   24 May 1996 14:38:36   JOERG
// Initial revision.
//Revision 1.12  1996/03/18  18:31:02  frank
//erste ausgelieferte version
//
//Revision 1.10  1996/03/10  17:01:53  frank
//testsezzion mit HS
//
//Revision 1.9  1996/03/09  14:20:19  frank
//kleinere bugfixes
//
//Revision 1.5  1996/02/26  09:51:38  frank
//some debug info added
//
//Revision 1.4  1996/02/23  14:42:31  frank
//first statements running with dds _test
//
//Revision 1.2  1996/02/14  15:46:14  frank
//first comments of bg
//
//Revision 1.2  1996/02/14  14:23:50  frank
//first comments by bg
//
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
#include "dds32.h" // FL 26.03.96 adapted to version v122
#define MODULENUM 911
HANDLE hLibInst;
#include "syb2ora.hpp"      // additional oci porting routines

extern void _export FAR PASCAL DisConnect ();
void _export FAR PASCAL DBReset ()
  {
  DisConnect ();
  }

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
extern "C" {
extern void _export FAR PASCAL dbexit ();
int FAR PASCAL WEP (int nShutdownFlag)
  {
  return 1 ;
  }

int FAR PASCAL LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  hLibInst = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1 ;
  }
}
#endif

LPVOID _export FAR PASCAL DataDict_NewTableDef (LPVOID ClientTable,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  static WORD done = TRUE ;
  *error = FALSE ;
  *size = sizeof(WORD);
  return &done;
  }

