/*
**     Struktur, die an den NCP - NLM uebergeben wird
**
**     $Header:   P:/marille/clinicum/include/rev/lock.hpv   1.1   02 Feb 1996 10:59:28   GERHOLD  $
**     $Log:   P:/marille/clinicum/include/rev/lock.hpv  $
// 
//    Rev 1.1   02 Feb 1996 10:59:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:26   HANNES
// Neuuebernahme clinicum
*/

struct LockRequest {
  WORD Command;
  struct LockInfo {
    WORD TableID;
    BYTE Key[8];
    } i;
  };

#define COMMAND_LOCK              0
#define COMMAND_UNLOCK            1
#define COMMAND_CLOSECONNECTION   2


DLLExport LONG _export WINAPI CallNCPLock (LPVOID key,WORD TableID,WORD command);

#define LOCKSRVNAME  "LOCK SERVER"
