////////////////////////////////////////////////////////////////////////////
//  serial.cpp - Funktionen zur Kommunikation ueber serielle Schnittstelle
////////////////////////////////////////////////////////////////////////////
//    $Header:   P:/marille/clinicum/rev/serial.cpv   1.6   29 Jun 1998 19:49:02   Martin  $
//    $Log:   P:/marille/clinicum/rev/serial.cpv  $
// 
//    Rev 1.6   29 Jun 1998 19:49:02   Martin
// CommSignalStatus, CommEscape
// 
//    Rev 1.5   09 Jun 1998 19:29:54   Martin
// Fehlercodes statt rosa Schirmen
// 
//    Rev 1.4   03 Apr 1998 19:32:34   Martin
// BuildCommDCB: Mode direkt uebergeben
// 
//    Rev 1.3   27 Jan 1998 11:16:24   Martin
// CommState-Handling richtiggestellt
// 
//    Rev 1.2   24 Jan 1998 14:37:32   Martin
// Fehlerkorrekturen
// 
//    Rev 1.1   19 Jan 1998 20:38:26   Martin
// 16-Bit-Kompilierbar gemacht
// 
//    Rev 1.0   19 Jan 1998 20:03:20   Martin
// Initial revision.
// 
////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdlib.h>
#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#define MODULENUM 185
#include "winass.hpp"

#ifndef WIN32
#define TXQUEUE          0
#define RXQUEUE          1
#endif

WORD LastCommError;
DWORD LastCommStatus;

#define COM_SUCCSESS     0
#define COM_NOPORT       1
#define COM_NOMODE       2
#define COM_BADPORT      3
#define COM_GETMODEERR   4
#define COM_BADMODE      5
#define COM_SETMODEERR   6
#define COM_WRITEERR     7
#define COM_TESTERR      8
#define COM_READERR      9

#pragma pack(1)
struct GetLastCommError_param {
  WORD  parSize;
  DWORD CommError;   // Out: interne Fehlernummer
  DWORD CommStatus;  // Out: Windows Fehlerflags
  };
#pragma pack()

BOOL GetLastCommError (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetLastCommError_param FAR *par = (GetLastCommError_param FAR *) param;
    c->WritelData (par->CommError, &LastCommError,sizeof(LastCommError), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->CommStatus, &LastCommStatus,sizeof(LastCommStatus), LPSTR(param)-sizeof(WORD));
    LastCommError = COM_SUCCSESS;
    LastCommStatus = 0L;
    }

  return FALSE;
  }


inline void cat (LPSTR txt,int status,int test,LPSTR tst)
  {
  if (status & test)
    lstrcat (txt,tst);
  }

void TestCommStatus (int status)
  {
  if (status != NULL) {
    static char outtxt[128];
    wsprintf (outtxt,"Comm - Error: ");
    cat (outtxt,status,CE_RXOVER  ,"CE_RXOVER  ");
    cat (outtxt,status,CE_OVERRUN ,"CE_OVERRUN ");
    cat (outtxt,status,CE_RXPARITY,"CE_RXPARITY");
    cat (outtxt,status,CE_FRAME   ,"CE_FRAME   ");
    cat (outtxt,status,CE_BREAK   ,"CE_BREAK   ");
#ifndef WIN32
    cat (outtxt,status,CE_CTSTO   ,"CE_CTSTO   ");
    cat (outtxt,status,CE_DSRTO   ,"CE_DSRTO   ");
    cat (outtxt,status,CE_RLSDTO  ,"CE_RLSDTO  ");
#endif
    cat (outtxt,status,CE_TXFULL  ,"CE_TXFULL  ");
    cat (outtxt,status,CE_PTO     ,"CE_PTO     ");
    cat (outtxt,status,CE_IOE     ,"CE_IOE     ");
    cat (outtxt,status,CE_DNS     ,"CE_DNS     ");
    cat (outtxt,status,CE_OOP     ,"CE_OOP     ");
    cat (outtxt,status,CE_MODE    ,"CE_MODE    ");
    WIN_ASSERT_TEXT(FALSE,outtxt);
    }
  }


#pragma pack(1)
struct OpenCommPort_param {
  WORD  parSize;
  DWORD Handle;      // Out: Filehandle
  DWORD Port;        // In:  string Port (z.B. "COM1")
  DWORD Mode;        // In:  string Mode (z.B. "9600,n,8,1")
  };
#pragma pack()

BOOL OpenCommPort (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    OpenCommPort_param FAR *par = (OpenCommPort_param FAR *) param;

    // Server und Topic aus den Script-Parametern ermitteln
    LPSTR Port = (LPSTR)c->ReadlData (par->Port);
    LPSTR Mode = (LPSTR)c->ReadlData (par->Mode);

    if (Port == NULL) {
      LastCommError = COM_NOPORT;
      LastCommStatus = 0L;
      res = FALSE;
      }
    else if (Mode == NULL) {
      LastCommError = COM_NOMODE;
      LastCommStatus = 0L;
      res = FALSE;
      }

#ifdef WIN32
    HANDLE  Handle;
    if (res) {
      char ComStr[50];
      wsprintf(ComStr,"%s:%s",Port,Mode);
      Handle = CreateFile(Port,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
      if (Handle == INVALID_HANDLE_VALUE) {
        LastCommError = COM_BADPORT;
        LastCommStatus = 0L;
        res = FALSE;
        }
      }
    DCB CommDCB;
    if (res) {
      lmemset(&CommDCB,'\0',sizeof(DCB));
      CommDCB.DCBlength = sizeof(DCB);
      if (GetCommState(Handle,&CommDCB) == FALSE) {
        LastCommError = COM_GETMODEERR;
        LastCommStatus = GetLastError();
        res = FALSE;
        }
      }
    if (res) {
      if (BuildCommDCB(Mode,&CommDCB) == FALSE) {
        LastCommError = COM_BADMODE;
        LastCommStatus = GetLastError();
        res = FALSE;
        }
      }
    if (res) {
      if (SetCommState(Handle,&CommDCB) == FALSE) {
        LastCommError = COM_SETMODEERR;
        LastCommStatus = GetLastError();
        res = FALSE;
        }
      }
    if (res) {
      PurgeComm(Handle, PURGE_TXABORT | PURGE_RXABORT	| PURGE_TXCLEAR | PURGE_RXCLEAR);
      c->WritelData (par->Handle, &Handle, sizeof(Handle), LPSTR(param)-sizeof(WORD));
      }
#else
    int Handle;
    if (res) {
      char ComStr[50];
      wsprintf(ComStr,"%s:%s",Port,Mode);
      Handle = OpenComm(Port,1024,1024);
      if (Handle < 0) {
        LastCommError = COM_BADPORT;
        LastCommStatus = Handle;
        res = FALSE;
        }
      }
    DCB CommDCB;
    if (res) {
      lmemset(&CommDCB,'\0',sizeof(DCB));
      int BuildError;
      if ((BuildError = BuildCommDCB(Mode,&CommDCB)) < 0) {
        LastCommError = COM_BADMODE;
        LastCommStatus = BuildError;
        res = FALSE;
        }
      }
    if (res) {
      int SetError;
      if ((SetError = SetCommState(&CommDCB)) < 0) {
        LastCommError = COM_SETMODEERR;
        LastCommStatus = SetError;
        res = FALSE;
        }
      }
    if (res) {
      FlushComm(Handle,TXQUEUE);
      FlushComm(Handle,RXQUEUE);
      c->WritelData (par->Handle, &Handle, sizeof(Handle), LPSTR(param)-sizeof(WORD));
      }
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    OpenCommPort_param FAR *par = (OpenCommPort_param FAR *) param;
    c->ClearlConnection (par->Port,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Mode,LPSTR(param)-sizeof(WORD));
    }
  
  return res;
  }
  

#pragma pack(1)
struct CloseCommPort_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  };
#pragma pack()

BOOL CloseCommPort (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CloseCommPort_param FAR *par = (CloseCommPort_param FAR *) param;

#ifdef WIN32
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE)) {
      // PurgeComm(*lpHandle, PURGE_TXABORT | PURGE_RXABORT	| PURGE_TXCLEAR | PURGE_RXCLEAR);
      CloseHandle(*lpHandle);
      }
#else
    int FAR *lpHandle = (int FAR *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle >= 0)) {
      // FlushComm(*lpHandle,TXQUEUE);
      // FlushComm(*lpHandle,RXQUEUE);
      CloseComm(*lpHandle);
      }
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    CloseCommPort_param FAR *par = (CloseCommPort_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    }
  
  return TRUE;
  }
  
#pragma pack(1)
struct FlushCommPort_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD RxQueue;     // In: flag receive-queue flushen
  DWORD TxQueue;     // In: flag transmit-queue flushen
  };
#pragma pack()

BOOL FlushCommPort (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FlushCommPort_param FAR *par = (FlushCommPort_param FAR *) param;

    DBINT FAR *lpRxQueue = (DBINT *)c->ReadlData (par->RxQueue);
    DBINT FAR *lpTxQueue = (DBINT *)c->ReadlData (par->TxQueue);
#ifdef WIN32
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    DWORD flags = 0L;
    if ((lpRxQueue != NULL) && (*lpRxQueue))
      flags |= (PURGE_RXABORT | PURGE_RXCLEAR);
    if ((lpTxQueue != NULL) && (*lpTxQueue))
      flags |= (PURGE_TXABORT | PURGE_TXCLEAR);
    if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE))
      PurgeComm(*lpHandle,flags);
#else
    int FAR *lpHandle = (int FAR *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle >= 0)) {
      if ((lpRxQueue != NULL) && (*lpRxQueue))
        FlushComm(*lpHandle,RXQUEUE);
      if ((lpTxQueue != NULL) && (*lpTxQueue))
        FlushComm(*lpHandle,TXQUEUE);
      }
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    FlushCommPort_param FAR *par = (FlushCommPort_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->RxQueue,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->TxQueue,LPSTR(param)-sizeof(WORD));
    }
  
  return TRUE;
  }


#pragma pack(1)
struct WriteStrCommPort_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD Str;         // In: string, der gesendet werden soll
  };
#pragma pack()

BOOL WriteStrCommPort (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    WriteStrCommPort_param FAR *par = (WriteStrCommPort_param FAR *) param;

    LPSTR Str = (LPSTR)c->ReadlData (par->Str);
    if ((Str != NULL) && (lstrlen(Str) > 0)) {
#ifdef WIN32
      HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
      if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE)) {
        DWORD AnzWritten;
        WriteFile(*lpHandle, Str, lstrlen(Str), &AnzWritten, NULL);
        if (AnzWritten != (DWORD)lstrlen(Str)) {
          COMSTAT CommState;
          ClearCommError(*lpHandle, &LastCommStatus, &CommState);
//          TestCommStatus (LastCommStatus);
          LastCommError = COM_WRITEERR;
          res = FALSE;
          }
        }
#else
      int FAR *lpHandle = (int FAR *)c->ReadlData (par->Handle);
      if ((lpHandle != NULL) && (*lpHandle >= 0)) {
        WORD AnzWritten;
        AnzWritten = WriteComm (*lpHandle,Str,lstrlen(Str));
        if (AnzWritten != lstrlen(Str)) {
          LastCommStatus = GetCommError (*lpHandle,NULL);
//          TestCommStatus (LastCommStatus);
          LastCommError = COM_WRITEERR;
          res = FALSE;
          }
        }
#endif
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    WriteStrCommPort_param FAR *par = (WriteStrCommPort_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Str,LPSTR(param)-sizeof(WORD));
    }
  
  return res;
  }


#pragma pack(1)
struct ReadStrCommPort_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD Str;         // Out: string, der empfangen worden ist
  DWORD AnzChars;    // optional: maximale Anzahl der zu empfangenden Zeichen
  };
#pragma pack()

BOOL ReadStrCommPort (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    ReadStrCommPort_param FAR *par = (ReadStrCommPort_param FAR *) param;
    DBINT Max = 0;
    if (par->parSize >= sizeof(*par)) {
      DBINT FAR *lpMax = (DBINT FAR *)c->ReadlData (par->AnzChars);
      if (lpMax != NULL)
        Max = *lpMax;
      }

#ifdef WIN32
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE)) {
      DWORD nRead;
      COMSTAT CommState;
      DWORD dwCommError;
      ClearCommError(*lpHandle, &dwCommError, &CommState);
      if (dwCommError != 0L) {
        LastCommError = COM_TESTERR;
        LastCommStatus = dwCommError;
        res = FALSE;
        }
//      TestCommStatus (dwCommError);
      if (res && (CommState.cbInQue > 0)) {
        DWORD AnzToRead = CommState.cbInQue;
        if (Max > 0) {
          if (DWORD(Max) < CommState.cbInQue)
            AnzToRead = DWORD(Max);
          }
        LPSTR Buffer = (LPSTR)GetGlobMem((int)AnzToRead + 1);
        ReadFile(*lpHandle, Buffer, AnzToRead, &nRead, NULL);
        if (AnzToRead != nRead) {
          COMSTAT CommState;
          ClearCommError(*lpHandle, &LastCommStatus, &CommState);
//          TestCommStatus (dwCommError);
          LastCommError = COM_READERR;
          res = FALSE;
          }
        if (res)
          c->WritelData (par->Str, Buffer, nRead + 1, LPSTR(param)-sizeof(WORD));
        else
          c->DellData (par->Str, LPSTR(param)-sizeof(WORD));
        FreeGlobMem(Buffer);
        }
      else
        c->DellData (par->Str, LPSTR(param)-sizeof(WORD));
      }
#else
    int FAR *lpHandle = (int FAR *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle >= 0)) {
      COMSTAT CommState;
      int GetError;
      if ((GetError = GetCommError(*lpHandle,&CommState)) != 0) {
        LastCommError = COM_TESTERR;
        LastCommStatus = GetError;
        res = FALSE;
        }
      if (res && (CommState.cbInQue > 0)) {
        UINT AnzToRead = CommState.cbInQue;
        if (Max > 0) {
          if (UINT(Max) < CommState.cbInQue)
            AnzToRead = UINT(Max);
          }
        LPSTR Buffer = (LPSTR)GetGlobMem((int)AnzToRead + 1);
        int nRead;
        nRead = ReadComm(*lpHandle, Buffer, (int)AnzToRead);
        if ((int)AnzToRead != nRead) {
          LastCommStatus = GetCommError (*lpHandle,NULL);
//          TestCommStatus (LastCommStatus);
          LastCommError = COM_READERR;
          res = FALSE;
          }
        if (res)
          c->WritelData (par->Str, Buffer, nRead + 1, LPSTR(param)-sizeof(WORD));
        else
          c->DellData (par->Str, LPSTR(param)-sizeof(WORD));
        FreeGlobMem(Buffer);
        }
      else
        c->DellData (par->Str, LPSTR(param)-sizeof(WORD));
      }
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    ReadStrCommPort_param FAR *par = (ReadStrCommPort_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    }
  
  return res;
  }


#pragma pack(1)
struct CommBytesReceived_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD NumBytes;    // Out: Anzahl der Zeichen
  };
#pragma pack()

BOOL CommBytesReceived (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    CommBytesReceived_param FAR *par = (CommBytesReceived_param FAR *) param;

    COMSTAT CommState;
#ifdef WIN32
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE)) {
      DWORD dwCommError;
      ClearCommError(*lpHandle, &dwCommError, &CommState);
      if (dwCommError != 0L) {
        LastCommError = COM_TESTERR;
        LastCommStatus = dwCommError;
        res = FALSE;
        }
//      TestCommStatus (dwCommError);
#else
    int FAR *lpHandle = (int FAR *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle >= 0)) {
      int GetError;
      if ((GetError = GetCommError(*lpHandle,&CommState)) != 0) {
        LastCommError = COM_TESTERR;
        LastCommStatus = GetError;
        res = FALSE;
        }
#endif
      DBINT InQueue = (DBINT)CommState.cbInQue;
      if (res)
        c->WritelData (par->NumBytes, &InQueue, sizeof(InQueue), LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->NumBytes, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->NumBytes, LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    CommBytesReceived_param FAR *par = (CommBytesReceived_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    }
  
  return res;
  }


#pragma pack(1)
struct CommSignalStatus_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD Status;      // Out: Bits fuer Signale (CTS,DSR,RING,RLSD)
  };
#pragma pack()

BOOL CommSignalStatus (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    CommSignalStatus_param FAR *par = (CommSignalStatus_param FAR *) param;

#ifdef WIN32
    DWORD CommModemStatus = 0L;
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    if ((lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE))
      res = GetCommModemStatus(*lpHandle,&CommModemStatus);
    c->WritelData (par->Status, &CommModemStatus, sizeof(CommModemStatus), LPSTR(param)-sizeof(WORD));
#else
    DBWIN_ASSERT_TEXT(FALSE,"CommSignalStatus not supported in 16 Bit EXE !");
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    CommSignalStatus_param FAR *par = (CommSignalStatus_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    }

  return res;
  }


#pragma pack(1)
struct CommEscape_param {
  WORD  parSize;
  DWORD Handle;      // In: Filehandle
  DWORD Escape;      // In: welche Escape-Funktion ?
  };
#pragma pack()

BOOL CommEscape (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;

  if (mode & EM_LOAD) {
    CommEscape_param FAR *par = (CommEscape_param FAR *) param;

    LPDWORD lpEscape = (LPDWORD)c->ReadlData (par->Escape);
#ifdef WIN32
    HANDLE *lpHandle = (HANDLE *)c->ReadlData (par->Handle);
    if ((lpEscape != NULL) && (lpHandle != NULL) && (*lpHandle != INVALID_HANDLE_VALUE))
      res = EscapeCommFunction(*lpHandle,*lpEscape);
#else
    DBWIN_ASSERT_TEXT(FALSE,"CommEscape not supported in 16 Bit EXE !");
#endif
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    CommEscape_param FAR *par = (CommEscape_param FAR *) param;
    c->ClearlConnection (par->Handle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Escape,LPSTR(param)-sizeof(WORD));
    }
  
  return res;
  }

