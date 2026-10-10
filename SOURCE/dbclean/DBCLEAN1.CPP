////////////////////////////////////////////////////////////////////
//  Einsprungpunkte in dbhelp.dll
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbclean/rev/dbclean1.cpv   1.7   05 Oct 1998 11:08:48   Gerhold  $
//  $Log:   P:/marille/clinicum/dbclean/rev/dbclean1.cpv  $
// 
//    Rev 1.7   05 Oct 1998 11:08:48   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.6   18 Mar 1997 18:53:12   Martin
// unter WIN32 fehlerfrei kompilierbar
// 
//    Rev 1.5   17 Jun 1996 15:41:16   HANNES
// Einbau von DDSELEM
// 
//    Rev 1.4   30 Apr 1996 12:30:02   MARTIN
// Abgleich Schweiz
// 
//    Rev 1.3   05 Apr 1996 21:49:06   HANNES
// dnetnv freigeben
// 
//    Rev 1.2   05 Apr 1996 15:18:50   MARTIN
// Abgleich Schweiz
// 19.03.96 FL adaption to windows NT: do not call freelibrary. Windows NT frees the Libraries by
//             itself and there is a DLL (Oracle), which gets in troubles with memory protection.
// 
//    Rev 1.0   03 Jan 1996 18:52:12   HANNES
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
#include "dds32.h"

#ifndef WIN32
#include <toolhelp.h>

extern LPSTR FAR PASCAL GetIniName();
#define MYINI           GetIniName ()
#define DATABASESECTION "DataBase"
#define FREELIB         "FreeLib"
#define FREELIBDEFAULT  "yes"

static BOOL   inidone = FALSE;
static BOOL   dofreelib = TRUE;
#endif
  
HINSTANCE hLibInst;
DLLExport void _export WINAPI DBClean_Init()
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
  return ((lstrcmp (me->szModule,"DBBTRV1") == 0) ||
          (lstrcmp (me->szModule,"DDSODBC1") == 0) ||
          (lstrcmp (me->szModule,"DDSSYB1") == 0) ||
          (lstrcmp (me->szModule,"DDSORA1") == 0) ||
          (lstrcmp (me->szModule,"DNETNV1") == 0) ||
          (lstrcmp (me->szModule,"DNETIN1") == 0) ||
          (lstrcmp (me->szModule,"DDSSEQ1") == 0));
	  } // if
	return FALSE;
  }

typedef void (FAR PASCAL * __DBRESET) ();
void DoFree (HMODULE hmod)
  {
  FreeLibrary (hmod);
  }

void OnShutDown ()
  {
  MODULEENTRY me;
  BOOL allDone = FALSE ;
  for ( ; !allDone ; ) {
    me.dwSize = sizeof(me);
    for ( ModuleFirst (&me) ; ; ) {
      if (IsToClean (&me)) {
        DoFree (me.hModule);
        break ;
        }
      me.dwSize = sizeof(me);
      if (!ModuleNext (&me)) {
        allDone = TRUE ;
        break ;
        }
      }
    }
  }

extern "C" {
int _export FAR PASCAL WEP (int nShutdownFlag)
  {
  if (nShutdownFlag != WEP_SYSTEM_EXIT) {
    OnShutDown ();
    }
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

