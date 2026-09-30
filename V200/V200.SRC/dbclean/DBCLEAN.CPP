////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in dbhelp.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbclean/rev/dbclean.cpv   1.8   17 Jun 1996 15:41:12   HANNES  $
//  $Log:   P:/marille/clinicum/dbclean/rev/dbclean.cpv  $
// 
//    Rev 1.8   17 Jun 1996 15:41:12   HANNES
// Einbau von DDSELEM
// 
//    Rev 1.7   30 Apr 1996 12:40:18   GERHOLD
// DLLExport vor GetMyIniFileName,
// Abgleich Schweiz
// 
//    Rev 1.6   05 Apr 1996 21:48:56   HANNES
// dnetnv freigeben
// 
//    Rev 1.5   05 Apr 1996 19:51:42   MARTIN
// eine geschwungene Klammer zuviel raus
// 
//    Rev 1.4   05 Apr 1996 15:18:48   MARTIN
// Abgleich Schweiz
// 19.03.96 FL adaption to windows NT: do not call freelibrary. Windows NT frees the Libraries by
//             itself and there is a DLL (Oracle), which gets in troubles with memory protection.
// 
//    Rev 1.2   20 Feb 1996 08:07:22   GERHOLD
// _export bei WEP!!!!
// 
//    Rev 1.1   16 Feb 1996 15:11:34   GERHOLD
// WIN32 - Umstellung
// 
//    Rev 1.0   03 Jan 1996 18:51:58   HANNES
// Initial revision.
// 
//    Rev 1.0   24 Jun 1994 16:44:44   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   19 Apr 1994 10:47:46   HANNES
// Initial revision.
// 
//
#include <windows.h>
#include <ctype.h>

#ifndef WIN32
  #include <toolhelp.h>
#endif

#include "dds32.h"

extern DLLExport LPSTR _export WINAPI GetIniName ();
#define MYINI           GetIniName ()
#define DATABASESECTION "DataBase"
#define FREELIB         "FreeLib"
#define FREELIBDEFAULT  "yes"

static BOOL   inidone = FALSE;
static BOOL   dofreelib = TRUE;
  
HANDLE hLibInst;
DLLExport void _export FAR PASCAL DBClean_Init()
  {
  }

#ifndef WIN32
BOOL IsToClean (MODULEENTRY FAR *me)
  {
	if (!inidone) {
		int  i;
		char freelibstr[128];
		GetPrivateProfileString(DATABASESECTION, FREELIB, FREELIBDEFAULT, freelibstr, sizeof(freelibstr), MYINI);
    for (i=0; i < lstrlen(freelibstr); i++) {
    	freelibstr[i] = toupper(freelibstr[i]);
    	} // for
		dofreelib = !(lstrcmp(freelibstr, "NO") == 0);
		inidone = TRUE;
		} // if
  if (dofreelib) {
		  return ((lstrcmp (me->szModule,"DBBTRV") == 0) ||
		          (lstrcmp (me->szModule,"DDSODBC") == 0) ||
	  	        (lstrcmp (me->szModule,"DDSSYB") == 0) ||
	  	        (lstrcmp (me->szModule,"DNETNV") == 0) ||
	    	      (lstrcmp (me->szModule,"DDSORA") == 0) ||
	      	    //(lstrcmp (me->szModule,"DNETIN") == 0) ||
	        	  (lstrcmp (me->szModule,"DDSSEQ") == 0));
	  } // if
	
	return FALSE;
  }
#endif

typedef void (FAR PASCAL * __DBRESET) ();

void OnShutDown ()
  {
#ifndef WIN32
  MODULEENTRY me;
  BOOL allDone = FALSE ;
  for ( ; !allDone ; ) {
    me.dwSize = sizeof(me);
    for ( ModuleFirst (&me) ; ; ) {
      if (IsToClean (&me)) {
//        __DBRESET reset = (__DBRESET) GetProcAddress (me.hModule,"DBRESET");
//        if (reset != NULL) {
//          ( * reset) () ;
//          for (int i = 0 ; i < 10 ; i++)
//            MessageBeep (0);
//          }
        FreeLibrary (me.hModule);
        break ;
        }
      me.dwSize = sizeof(me);
      if (!ModuleNext (&me)) {
        allDone = TRUE ;
        break ;
        }
      }
    }
#endif
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
      OnShutDown ();

      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
extern "C" {
int _export WINAPI WEP (int nShutdownFlag)
  {
  if (nShutdownFlag != WEP_SYSTEM_EXIT) {
    OnShutDown ();
    }
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

