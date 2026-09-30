//////////////////////////////////////////////////////////////////////////////
//
//  Windows Socket access functions
//
// $Header:   P:/marille/clinicum/rev/socket.cpv   1.4   14 Dec 1999 13:10:12   Martin  $
// $Log:   P:/marille/clinicum/rev/socket.cpv  $
// 
//    Rev 1.4   14 Dec 1999 13:10:12   Martin
// Blob-Fehlerkorrekturen
// 
//    Rev 1.3   22 Nov 1999 18:02:04   Wolfgang
// 1.) Send/Receive mit Blobs.
// 
//    Rev 1.2   27 Apr 1999 01:45:26   Hannes
// Diverse Speicherfresser
// 
//    Rev 1.1   12 Oct 1998 10:34:40   Wolfgang
// 1.) FD_CLOSE auch bei FD_CONNECT selektieren.
// 
//    Rev 1.0   09 Oct 1998 18:48:44   Wolfgang
// Initial revision.
//
/////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "ddsmsg.h"
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "hash.hpp"
#include "compile.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#define MODULENUM   186
#include "winass.hpp"

//************************************************************************
// Hilfsfunktionen

static char GetHexChar (BYTE ch,BOOL highnibble)
  {
  if (highnibble) {
    ch = ch >> 4 ;
    }
  ch &= 0x0F;

  return (ch >= 0x0A) ? 'A' + (ch - 0x0A) : '0' + ch ;
  }

//-------------------------------------

static LPSTR DataToStr (LPSTR data, int size)
  {
  LPSTR erg;
  erg = LPSTR (GetGlobMem (size * 2 + 1));
  for (int i = 0 ; (i < size); i ++) {
    erg [2 * i    ] = GetHexChar(data[i],TRUE);
    erg [2 * i + 1] = GetHexChar(data[i],FALSE);
    }
  erg[2 * i] = '\0';
  return erg;
  }

//-------------------------------------

#define MAX_RETRY 20
#define SENDDIR ">>"
#define RECVDIR "<<"
#define ERRDIR  "--"
#define SOCKETLOG "socket.log"

void LogData (LPSTR dir, LPVOID dataVoid, int size, LONG errCode, DWORD startT, DWORD endT)
  {
  OFSTRUCT Of;
  HFILE f;
  LPSTR fname = SOCKETLOG;
  LPSTR data = LPSTR (dataVoid);
  int retry = 0;
  while (retry < MAX_RETRY) {
    f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        }
      else {
        f = OpenFile (fname,&Of,OF_CREATE);
        _lclose(f);
        }
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    char timestr[32];
    wsprintf (timestr,"%s[%8ld - %8ld (= %4ld);%5ld]",dir,startT,endT,endT - startT,errCode);
    _lwrite (f,timestr,lstrlen(timestr));
    LPSTR txt;
    txt = DataToStr (data, size);
    _lwrite (f,txt,lstrlen(txt));
    FreeGlobMem (txt);
    _lwrite (f,"\r\n",2);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

//-------------------------------------

BOOL DoError(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL doError;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("Network","ShowError", "no", buf, sizeof(buf),GetIniName());
    doError = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE;
    }
  return doError;
  }

//-------------------------------------

BOOL DoLog(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL doLog;
  static BOOL ScrollLockOnly;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("Network","DoLog", "no", buf, sizeof(buf),GetIniName());
    doLog = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("Network","ScrollLockOnly", "no", buf, sizeof(buf),GetIniName());
    ScrollLockOnly = (lstrcmp(buf,"yes") == 0);
    FirstTime = FALSE;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog;
  }

//************************************************************************
// Basis-Objekt fuer Speicherverwaltung

class ScriptMemory {
 public:
  LPVOID operator new (size_t size)
    {
    LPVOID res = GetGlobMem (size);
    DBWIN_ASSERT (res == NULL); // Kein Speicher mehr oder size 0
    return res;
    }
  void operator delete (LPVOID object)
    {
    FreeGlobMem (object);
    }
  };
typedef ScriptMemory SCRIPTMEMORY;
typedef ScriptMemory FAR * LPSCRIPTMEMORY;

//************************************************************************
// Objekte zum Zugriff auf Scriptvariablen bzw. -funktionen

#define ENTERIF(A) if (doExtra) { \
                     if (ExtraDataAtCreation != NULL) { \
                       SAVEREC old; \
                       creationC->SetRecsForUpdate (old,ExtraDataAtCreation); \
                       SetExtraInfo s(creationC,ExtraDataAtCreation); \
                       A ; \
                       creationC->RestoreRecs(old);  \
                       } \
                     else { \
                       RestoreListFnc rlf (creationC);  \
                       A ; \
                       } \
                     } \
                   else { \
                     A ; \
                     }

//-------------------------------------

class ScriptAccess : public ScriptMemory {
 protected:
  mdiChild *creationC;
  BOOL doExtra;
  LPCONNEXTRAINFO ExtraDataAtCreation;
 public:
  ScriptAccess ()
    {
    }
  ScriptAccess (mdiChild *setC, BOOL setDoExtra = FALSE, LPCONNEXTRAINFO setExtra = NULL)
    {
    creationC = setC;
    doExtra = setDoExtra;
    ExtraDataAtCreation = setExtra;
    }
  };
typedef ScriptAccess SCRIPTACCESS;
typedef ScriptAccess FAR * LPSCRIPTACCESS;

//-------------------------------------

extern void CallFunction (DWORD FuncAddr,mdiChild *c,LPSCRIPTCONTENT scchild,LPWORD destInd,int AnzPars,LPVOID FAR *vals,int AnzValsRet,LPVOID FAR *ValsRet);

class ScriptFunction : public ScriptAccess {
 protected:
  LPSCRIPTCONTENT scentAtCreation;
  LPWORD destIndAtCreation;
  DWORD procAddr;
  WORD rType;
 public:
  ScriptFunction () : ScriptAccess ()
    {
    procAddr = 0;
    }
  ScriptFunction (mdiChild *setC, LPSTR functionName, int functionArgsAnz, LPWORD functionArgs, 
                  BOOL setDoExtra = FALSE, LPCONNEXTRAINFO setExtra = NULL) 
    : ScriptAccess (setC, setDoExtra, setExtra)
    {
    char resName[256];
    GetFunctionName (functionName,resName,functionArgsAnz,functionArgs);
    scentAtCreation = creationC->schd;
    DBWIN_ASSERT (scentAtCreation != NULL); // Modul nicht gefunden
    procAddr = GetFunctionsAddress (resName,scentAtCreation->ExportDef,&destIndAtCreation,&rType);
    DBWIN_ASSERT (procAddr != 0); // Funktion nicht gefunden (Name und/oder Parameter falsch)
    }
  void Call (int inValsAnz, LPVOID *inVals, int outValsAnz, LPVOID *outVals)
    {
    if (procAddr != 0) {
      ENTERIF (
        CallFunction (procAddr,creationC,scentAtCreation,destIndAtCreation,inValsAnz,inVals,outValsAnz,outVals)
        );
      }
    }
  };
typedef ScriptFunction SCRIPTFUNCTION;
typedef ScriptFunction FAR * LPSCRIPTFUNCTION;

//-------------------------------------

class ScriptVar : public ScriptAccess {
 protected:
  LPVOID ParamAtCreation;
  DWORD varAddr;
 public:
  ScriptVar () : ScriptAccess ()
    {
    }
  ScriptVar (mdiChild *setC, LPVOID setParam, DWORD setVarAddr, 
             BOOL setDoExtra = FALSE, LPCONNEXTRAINFO setExtra = NULL) 
    : ScriptAccess (setC, setDoExtra, setExtra)
    {
    ParamAtCreation = setParam;
    varAddr = setVarAddr;
    }
  LPVOID ReadVar ()
    {
    LPVOID res;
    ENTERIF (res = creationC->ReadlData (varAddr));
    return res;
    }
  void WriteVar (LPVOID var, int varSize)
    {
    ENTERIF (creationC->WritelData (varAddr,var,varSize,LPSTR (ParamAtCreation) - sizeof(WORD)));
    }
  void DelVar ()
    {
    ENTERIF (creationC->DellData (varAddr,LPSTR (ParamAtCreation) - sizeof(WORD)));
    }
  };
typedef ScriptVar SCRIPTVAR;
typedef ScriptVar FAR * LPSCRIPTVAR;

//-------------------------------------

LPCONNEXTRAINFO CopyExtraData (mdiChild *c)

  {
  LPCONNEXTRAINFO res;
  LPCONNEXTRAINFO ec = c->_GetRecExtra() ;
  if (ec != NULL) {
    res = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize (ec)));
    lmemcpy (res,ec,GetBlockSize (ec));
    }
  else
    res = NULL;
  return res;
  }

//-------------------------------------

LONG GetLongParameter (mdiChild *c, DWORD parIndex, BOOL parExists, int defaultValue)
  {
  LPLONG parLong;
  if (parExists)
    parLong = LPLONG (c->ReadlData (parIndex));
  else
    parLong = NULL;
  if (parLong != NULL)
    return *parLong;
  else
    return defaultValue;
  }
  
//-------------------------------------

DBBOOL GetFlagParameter (mdiChild *c, DWORD parIndex, BOOL parExists, DBBOOL defaultValue)
  {
  DBBOOL FAR * parFlag;
  if (parExists)
    parFlag = (DBBOOL FAR * ) c->ReadlData (parIndex);
  else
    parFlag = NULL;
  if (parFlag != NULL)
    return *parFlag;
  else
    return defaultValue;
  }
  
//************************************************************************
// ScriptSocket Klasse  

// Konstanten fuer ScriptSocket.status, Aenderungen auch in SOCKET.INC (SCRIPT\INCLUDE) nachfuehren
#define SCRIPTSOCKETSTATUS_FREE           0 // -  99 Init moeglich
#define SCRIPTSOCKETSTATUS_INITERROR      1
#define SCRIPTSOCKETSTATUS_INITIALIZED  100 // - 199 Select/Listen/Connect/Accept moeglich
#define SCRIPTSOCKETSTATUS_ERROR        101
#define SCRIPTSOCKETSTATUS_DISCONNECTED 200 // - 299 nur closesocket moeglich, FD_READ+CLOSE ignoriert
#define SCRIPTSOCKETSTATUS_WAITING      300 // - 399 Select/Event moeglich
#define SCRIPTSOCKETSTATUS_CONNECT      301 
#define SCRIPTSOCKETSTATUS_LISTEN       302
#define SCRIPTSOCKETSTATUS_TRANSMITTING 400 // - 499 Send/Receive moeglich
#define SCRIPTSOCKETSTATUS_CONNECTED    401
#define SCRIPTSOCKETSTATUS_ACCEPTED     402

// Folgende Konstanten werden zur Anzeige spezieller Fehlerzustaende verwendet,
// sie duerfen sich nicht mit den WSA...-Errorkonstanten in WINSOCK.H ueberschneiden.
// Aenderungen auch in SOCKET.INC (SCRIPT\INCLUDE) nachfuehren
#define SCRIPTSOCKETERROR_WRONGSTATUS    -1

hash FAR *SocketHash; // Hash-Tabelle (winSocket -> Speicheradresse) aller ScriptSockets

DLLExport int _export WINAPI NWSocketFamily ();
DLLExport int _export WINAPI NWSocketProtocol (int);

class ScriptSocket {
 public:
  LPSOCKADDR address;
  DBINT status;
  LONG lastErr; // Typ kompatibel zu int !
 protected:
  SOCKET winSocket;
  int socketFamily;
  int socketType;
  int socketProtocol;

  HWND selectWin;
  u_int selectMsg;
  long sysEvents;
  long scriptEvents;

  FD_SET sendWaitSockets;
  int sendMaxTries;
  TIMEVAL sendTimeOut;

  BOOL useBlob;
  BOOL recvBufferInitialized;
  LPVOID recvBuffer;
  GLOBALHANDLE recvBufferHandle;
  int maxRecvLen;

  ScriptFunction acceptProc;
  ScriptFunction receiveProc;
  ScriptFunction selectProc;
  ScriptVar isConnected;
  
  void SetLastError (int errorCode);
  int GetLastError ()
    {
    SetLastError (WSAGetLastError ());
    return int (lastErr);
    }
  BOOL InitReceiveBuffer ()
    {
    if (useBlob) {
      recvBufferHandle = GlobalAlloc (GMEM_MOVEABLE, maxRecvLen);
      recvBufferInitialized = (recvBufferHandle != NULL);
      }
    else {
      recvBuffer = GetGlobMem (maxRecvLen);
      recvBufferInitialized = (recvBuffer != NULL);
      }
    return recvBufferInitialized;
    }
  void DoneReceiveBuffer ()
    {
    if (recvBufferInitialized) {
      if (useBlob) {
        GlobalFree (recvBufferHandle);
        }
      else
        FreeGlobMem (recvBuffer);
      }
    recvBufferInitialized = FALSE;
    recvBuffer = NULL;
    recvBufferHandle = NULL;
    }
  BOOL InitSocket (LPSOCKADDR setAddress);
  void DoneSocket ()
    {
    if (winSocket != INVALID_SOCKET)
      SocketHash->DelData (winSocket);
    if (status >= SCRIPTSOCKETSTATUS_INITIALIZED)
      closesocket (winSocket);
    DoneReceiveBuffer ();
    if (address != NULL)
      FreeGlobMem (address);
    winSocket = INVALID_SOCKET;
    recvBufferInitialized = FALSE;
    recvBuffer = NULL;
    recvBufferHandle = NULL;
    address = NULL;
    status = SCRIPTSOCKETSTATUS_FREE;
    }
  void DoSelect ()
    {
    WSAAsyncSelect (winSocket, selectWin, selectMsg, sysEvents | scriptEvents);
    }
  void AddSelect (long addEvents, BOOL toSys)
    {
    if (toSys)
      sysEvents = sysEvents | addEvents;
    else
      scriptEvents = scriptEvents | addEvents;
    DoSelect();
    }
  void DelSelect (long delEvents, BOOL fromSys)
    {
    if (fromSys)
      sysEvents = sysEvents & ~delEvents;
    else
      scriptEvents = scriptEvents & ~delEvents;
    DoSelect();
    }
  void SetConnect ()
    {
    status = SCRIPTSOCKETSTATUS_CONNECTED;
    AddSelect (FD_CLOSE, TRUE);
    DBBOOL setFlag = TRUE;
    isConnected.WriteVar (&setFlag, sizeof (setFlag));
    }
  void SetReceiveBuffer (int setMaxRecvLen, BOOL setUseBlob)
    {
    if ((setMaxRecvLen != maxRecvLen) || (setUseBlob != useBlob)) {
      DoneReceiveBuffer ();
      maxRecvLen = setMaxRecvLen;
      useBlob = setUseBlob;
      }
    }
 public:
  ScriptSocket (HWND setSelectWin, u_int setSelectMsg,
                int setSocketType = -1, int setSocketProtocol = -1, int setSocketFamily = -1)
    {
    address = NULL;
    recvBufferInitialized = FALSE;
    recvBuffer = NULL;
    recvBufferHandle = NULL;
    selectWin = setSelectWin;
    selectMsg = setSelectMsg;
    sysEvents = 0;
    scriptEvents = 0;
    if (setSocketType == -1)
      socketType = SOCK_STREAM;
    else
      socketType = setSocketType;
    if (setSocketProtocol == -1)
      socketProtocol = NWSocketProtocol (socketType);
    else
      socketProtocol = setSocketProtocol;
    if (setSocketFamily == -1)
      socketFamily = NWSocketFamily ();
    else
      socketFamily = setSocketFamily;
    sendTimeOut.tv_sec = 0; sendTimeOut.tv_usec = 500000; // 0,5 Sekunden
    sendMaxTries = 1200; // * sendTimeOut = 600 Sekunden = 10 Minuten
    maxRecvLen = 4096;
    winSocket = INVALID_SOCKET;
    status = SCRIPTSOCKETSTATUS_FREE;
    }
  virtual ~ScriptSocket ();
  BOOL StartConnect (LPSOCKADDR connectAddress, LPSCRIPTVAR setIsConnected);
  BOOL StartListen (LPSOCKADDR listenAddress, LPSCRIPTFUNCTION setAcceptProc);
  BOOL DoAccept (ScriptSocket FAR *listenSocket, LPSCRIPTVAR setIsConnected);
  BOOL StartReceive (LPSCRIPTFUNCTION setReceiveProc, int setMaxRecvLen, BOOL setUseBlob);
  void StopReceive ();
  BOOL DoSend (LPVOID toSend, int *bytesNotSent);
  void CheckEvent (LPARAM msglParam);
  };
typedef ScriptSocket FAR * LPSCRIPTSOCKET;
typedef ScriptSocket SCRIPTSOCKET;

typedef LPSCRIPTSOCKET SOCKETOBJ; // Script Objekt fuer Sockets
typedef SOCKETOBJ FAR * LPSOCKETOBJ;

ScriptSocket::~ScriptSocket ()
  {
  DoneSocket ();
  }

BOOL ScriptSocket::InitSocket (LPSOCKADDR setAddress)
  {
  if (status < SCRIPTSOCKETSTATUS_INITIALIZED) {
    winSocket = socket (socketFamily, socketType, socketProtocol); 
    if (winSocket == INVALID_SOCKET) {
      GetLastError ();
      status = SCRIPTSOCKETSTATUS_INITERROR;
      return FALSE;
      }
    else {
      status = SCRIPTSOCKETSTATUS_INITIALIZED;
      ULONG nonblocking = 1;
      ioctlsocket (winSocket, FIONBIO, &nonblocking);
      address = LPSOCKADDR (GetGlobMem (GetBlockSize (setAddress)));
      lmemcpy (address, setAddress, GetBlockSize (setAddress));
      if (SocketHash == NULL)
        SocketHash = new hash (37,LONGKEY);
      LPSCRIPTSOCKET p = this;
      SocketHash->SetData (LONG(winSocket),&p,sizeof(p));
      return TRUE;
      }
    }
  else {
    SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
    return FALSE;
    }
  }

void ScriptSocket::SetLastError (int errorCode)
  {
  lastErr = errorCode;
  if ((lastErr != 0) && (lastErr != WSAEWOULDBLOCK)) {
    char errtxt[64];
    if (DoError ()) {
      wsprintf (errtxt,"WinSocket Error %ld", lastErr);
      DBWIN_ASSERT_TEXT (FALSE, errtxt);
      }
    else if (DoLog ()) {
      DWORD errT = GetTickCount();
      LogData (ERRDIR, NULL, 0, lastErr, errT, errT);
      }
    if ((status >= SCRIPTSOCKETSTATUS_WAITING) && 
        ((lastErr == WSAECONNRESET) || (lastErr == WSAECONNREFUSED))) {
      DBBOOL setFlag = FALSE;
      isConnected.WriteVar (&setFlag, sizeof (setFlag));
      status = SCRIPTSOCKETSTATUS_DISCONNECTED;
      }
    }
  }
  
BOOL ScriptSocket::StartConnect (LPSOCKADDR connectAddress, LPSCRIPTVAR setIsConnected)
  {
  isConnected = *setIsConnected;
  if (InitSocket (connectAddress)) {
    AddSelect (FD_CONNECT, TRUE);
    status = SCRIPTSOCKETSTATUS_CONNECT;
    isConnected.DelVar ();
    if (connect (winSocket, address, GetBlockSize (address)) == SOCKET_ERROR) {
      if (GetLastError () == WSAEWOULDBLOCK) {
        return TRUE;
        }
      else {
        DelSelect (FD_CONNECT, TRUE);
        status = SCRIPTSOCKETSTATUS_ERROR;
        DBBOOL setFlag = FALSE;
        isConnected.WriteVar (&setFlag, sizeof (setFlag));
        return FALSE;
        }
      }
    else {
      DelSelect (FD_CONNECT, TRUE);
      SetConnect ();
      return TRUE;
      }
    }
  else {
    DBBOOL setFlag = FALSE;
    isConnected.WriteVar (&setFlag, sizeof (setFlag));
    return FALSE;
    }
  }

BOOL ScriptSocket::StartListen (LPSOCKADDR listenAddress, LPSCRIPTFUNCTION setAcceptProc)
  {
  if (InitSocket (listenAddress)) {
    acceptProc = *setAcceptProc;
    if (bind (winSocket, address, GetBlockSize (address)) == SOCKET_ERROR) {
      GetLastError ();
      status = SCRIPTSOCKETSTATUS_ERROR;
      return FALSE;
      }
    else {
      if (listen (winSocket, 5) == SOCKET_ERROR) {
        GetLastError ();
        status = SCRIPTSOCKETSTATUS_ERROR;
        return FALSE;
        }
      else {
        status = SCRIPTSOCKETSTATUS_LISTEN;
        AddSelect (FD_ACCEPT, TRUE);
        return TRUE;
        }
      }
    }
  else
    return FALSE;
  }

BOOL ScriptSocket::DoAccept (ScriptSocket FAR *listenSocket, LPSCRIPTVAR setIsConnected)
  {
  if (status < SCRIPTSOCKETSTATUS_INITIALIZED) {
    isConnected = *setIsConnected;
    socketFamily = listenSocket->socketFamily;
    socketType = listenSocket->socketType;    
    socketProtocol = listenSocket->socketProtocol;
    int acceptAddressLen = GetBlockSize (listenSocket->address);
    address = LPSOCKADDR (GetGlobMem (acceptAddressLen));
    winSocket = accept (listenSocket->winSocket, address, &acceptAddressLen);
    if (winSocket == INVALID_SOCKET) {
      GetLastError ();
      status = SCRIPTSOCKETSTATUS_INITERROR;
      DBBOOL setFlag = FALSE;
      isConnected.WriteVar (&setFlag, sizeof (setFlag));
      return FALSE;
      }
    else {
      if (SocketHash == NULL)
        SocketHash = new hash (37,LONGKEY);
      LPSCRIPTSOCKET p = this;
      SocketHash->SetData (LONG(winSocket),&p,sizeof(p));
      status = SCRIPTSOCKETSTATUS_ACCEPTED;
      AddSelect (FD_CLOSE, TRUE);
      DBBOOL setFlag = TRUE;
      isConnected.WriteVar (&setFlag, sizeof (setFlag));
      return TRUE;
      }
    }
  else {
    SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
    DBBOOL setFlag = FALSE;
    isConnected.WriteVar (&setFlag, sizeof (setFlag));
    return FALSE;
    }
  }
  
BOOL ScriptSocket::StartReceive (LPSCRIPTFUNCTION setReceiveProc, int setMaxRecvLen, BOOL setUseBlob)
  {
  if (status >= SCRIPTSOCKETSTATUS_TRANSMITTING) {
    SetReceiveBuffer (setMaxRecvLen, setUseBlob);
    receiveProc = *setReceiveProc;
    AddSelect (FD_READ, TRUE);
    return TRUE;
    }
  else
    return FALSE;
  }

void ScriptSocket::StopReceive ()
  {
  DelSelect (FD_READ, TRUE);
  }

BOOL ScriptSocket::DoSend (LPVOID toSend, int *bytesNotSent)
  {
  if (toSend == NULL) {
    if (bytesNotSent > 0)
      return FALSE;
    else
      return TRUE;
    }
  else if (status >= SCRIPTSOCKETSTATUS_TRANSMITTING) {
    int bytesToSend = *bytesNotSent;
    int tries = 0;
    int bytesSent;
    LPSTR stillToSend = LPSTR (toSend);
    lastErr = WSAEWOULDBLOCK;
    DWORD startT = GetTickCount () ;
    while ((lastErr == WSAEWOULDBLOCK) && (*bytesNotSent > 0) && 
           ((tries < sendMaxTries) || (sendMaxTries == 0))) {
      tries++;
      bytesSent = send (winSocket, LPSTR (stillToSend), *bytesNotSent, 0);
      if (bytesSent != SOCKET_ERROR) {
        stillToSend += bytesSent;
        *bytesNotSent -= bytesSent;
        }
      GetLastError ();
      if (*bytesNotSent > 0) {
        if ((lastErr == WSAEWOULDBLOCK) && 
            ((tries < sendMaxTries) || (sendMaxTries == 0))) {
          FD_ZERO (&sendWaitSockets);
          FD_SET (winSocket, &sendWaitSockets);
          if (select (0, LPFD_SET (NULL), &sendWaitSockets, LPFD_SET (NULL), &sendTimeOut) == SOCKET_ERROR)
            GetLastError ();
          }
        }
      }
    DWORD endT = GetTickCount () ;
    if (DoLog ())
      LogData (SENDDIR, toSend, bytesToSend - *bytesNotSent, lastErr, startT, endT);
    if (bytesNotSent > 0)
      return FALSE;
    else
      return TRUE;
    }
  else {
    SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
    return FALSE;
    }
  }

void ScriptSocket::CheckEvent (LPARAM msglParam)
  {
  DBBOOL setFlag;
  LPVOID inVals[2];
  int recvLen = 0;
  WORD eventType = WSAGETSELECTEVENT (msglParam);
  LONG eventError = LONG (WSAGETSELECTERROR (msglParam));
  switch (eventType)
    {
    case FD_CONNECT: // connect-Call beendet
      if (status == SCRIPTSOCKETSTATUS_CONNECT) {
        if (!eventError) {
          DelSelect (FD_CONNECT, TRUE);
          AddSelect (FD_CLOSE, TRUE);
          status = SCRIPTSOCKETSTATUS_CONNECTED;
          setFlag = TRUE;
          }
        else {
          SetLastError (eventError);
          setFlag = FALSE;
          }
        isConnected.WriteVar (&setFlag, sizeof (setFlag));
        }
      else
        SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
      break;
    case FD_ACCEPT: // accept auf listen-Socket moeglich
      if (status == SCRIPTSOCKETSTATUS_LISTEN) {
        SetLastError (eventError);
        inVals[0] = GetGlobMem (sizeof (SOCKETOBJ));
        *LPSOCKETOBJ (inVals[0]) = this;
        inVals[1] = GetGlobMem (sizeof (lastErr));
        *LPLONG (inVals[1]) = lastErr;
        acceptProc.Call (2, inVals, 0, NULL);
        FreeGlobMem (inVals[0]);
        FreeGlobMem (inVals[1]);
        }
      else
        SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
      break;
    case FD_READ: // recv moeglich
      if (status >= SCRIPTSOCKETSTATUS_TRANSMITTING) {
        SetLastError (eventError);
        DWORD startT = GetTickCount () ;
        if (!eventError)
          {
          if (!recvBufferInitialized)
            DBWIN_ASSERT (InitReceiveBuffer ());
          if (useBlob) {
            recvBuffer = GlobalLock (recvBufferHandle);
            recvLen = recv (winSocket, LPSTR (recvBuffer), maxRecvLen, 0);
            GetLastError ();
            if ((recvLen == SOCKET_ERROR) || (recvLen == 0))
              inVals[0] = NULL;
            else {
              LPBLOBDESC blobDesc = (LPBLOBDESC) GetGlobMem (sizeof (*blobDesc));
              blobDesc->hGmem = recvBufferHandle;
              blobDesc->Size = recvLen;
              inVals[0] = blobDesc;
              }
            }
          else {
            recvLen = recv (winSocket, LPSTR (recvBuffer), maxRecvLen, 0);
            GetLastError ();
            if ((recvLen == SOCKET_ERROR) || (recvLen == 0))
              inVals[0] = NULL;
            else {
              inVals[0] = GetGlobMem (recvLen);
              lmemcpy (inVals[0],recvBuffer,recvLen);
              }
            }
          }
        else
          inVals[0] = NULL;
        inVals[1] = GetGlobMem (sizeof (lastErr));
        *LPLONG (inVals[1]) = lastErr;
        DWORD endT = GetTickCount () ;
        if (DoLog ())
          LogData (RECVDIR, recvBuffer, recvLen, lastErr, startT, endT);
        if (useBlob && (recvBuffer != NULL)) {
          GlobalUnlock (recvBufferHandle);
          recvBuffer = NULL;
          }
        receiveProc.Call (2, inVals, 0, NULL);
        if (inVals[0] != NULL) {
          FreeGlobMem (inVals[0]);
          }
        FreeGlobMem (inVals[1]);
        }
      else if ((status < SCRIPTSOCKETSTATUS_DISCONNECTED) ||
               (status >= SCRIPTSOCKETSTATUS_WAITING))
        SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
      break;
    case FD_CLOSE: // Verbindung durch andere Seite beendet
      if (status >= SCRIPTSOCKETSTATUS_WAITING) {
        status = SCRIPTSOCKETSTATUS_DISCONNECTED;
        SetLastError (eventError);
        setFlag = FALSE;
        isConnected.WriteVar (&setFlag, sizeof (setFlag));
        }
      else if (status < SCRIPTSOCKETSTATUS_DISCONNECTED)
        SetLastError (SCRIPTSOCKETERROR_WRONGSTATUS);
    //   FD_OOB: not used because Out Of Band data is not implemented
    //   FD_WRITE: not used because send function blocks
    }
  }
    
//************************************************************************
// Script Befehle

#pragma pack(1)
struct FAR NetListen_param {
  WORD parSize;                    // Prototyp: private 8
  SOCKETOBJ privScriptSocket;      // 4
  LPCONNEXTRAINFO privExtraData;   // 4 
  DWORD mySocketObj;
  DWORD listenAddress;
  DWORD acceptProc;
  DWORD socketTypeLong;     // optional
  DWORD socketProtocolLong; // optional
  DWORD socketFamilyLong;   // optional
  BOOL MitSocketType ()
    {
    return (parSize >= sizeof(*this) - 2 * sizeof (DWORD));
    }
  BOOL MitSocketProtocol ()
    {
    return (parSize >= sizeof(*this) - sizeof (DWORD));
    }
  BOOL MitSocketFamily ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL NetListen (mdiChild *c, LPVOID param, WORD mode)
  {
  NetListen_param FAR *par = (NetListen_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    par->privExtraData = CopyExtraData( c );
    // Parameter einlesen
    LPSTR functionName = LPSTR (c->ReadlData (par->acceptProc));
    WORD functionArgs[2];
    functionArgs[0] = VAR_OBJ ;
    functionArgs[1] = VAR_LONG ;
    ScriptFunction setAcceptProc (c, functionName, 2, functionArgs, TRUE, par->privExtraData);
    LPSOCKADDR listenAddress = LPSOCKADDR (c->ReadlData (par->listenAddress));
    LONG socketType;
    LONG socketProtocol;
    LONG socketFamily;
    socketType = GetLongParameter (c, par->socketTypeLong, par->MitSocketType(), -1);
    socketProtocol = GetLongParameter (c, par->socketProtocolLong, par->MitSocketProtocol(), -1);
    socketFamily = GetLongParameter (c, par->socketFamilyLong, par->MitSocketFamily(), -1);
    // ScriptSocket anlegen
    par->privScriptSocket = new ScriptSocket (WBase::hFrameWin, WMU_SOCKETEVENT, 
                                              socketType, socketProtocol, socketFamily);
    // Abhoeren auf Verbindungen ausloesen
    if (par->privScriptSocket->StartListen (listenAddress, &setAcceptProc)) {
      c->WritelData (par->mySocketObj,&par->privScriptSocket,sizeof(par->privScriptSocket),
                     LPSTR (param) - sizeof(WORD));
      }
    else {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    if (par->privScriptSocket != NULL) {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      }
    c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    if (par->privExtraData != NULL) {
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }

    c->ClearlConnection (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->listenAddress,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->acceptProc,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//-------------------------------------

#pragma pack(1)
struct FAR NetConnect_param {
  WORD parSize;                    // Prototyp: private 8
  SOCKETOBJ privScriptSocket;      // 4
  LPCONNEXTRAINFO privExtraData;   // 4 
  DWORD isConnected;
  DWORD mySocketObj;
  DWORD connectAddress;
  DWORD socketTypeLong;     // optional
  DWORD socketProtocolLong; // optional
  DWORD socketFamilyLong;   // optional
  BOOL MitSocketType ()
    {
    return (parSize >= sizeof(*this) - 2 * sizeof (DWORD));
    }
  BOOL MitSocketProtocol ()
    {
    return (parSize >= sizeof(*this) - sizeof (DWORD));
    }
  BOOL MitSocketFamily ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL NetConnect (mdiChild *c, LPVOID param, WORD mode)
  {
  NetConnect_param FAR *par = (NetConnect_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    par->privExtraData = CopyExtraData( c );
    // Parameter einlesen
    ScriptVar setIsConnected (c, param, par->isConnected, TRUE, par->privExtraData);
    LPSOCKADDR connectAddress = LPSOCKADDR (c->ReadlData (par->connectAddress));
    LONG socketType;
    LONG socketProtocol;
    LONG socketFamily;
    socketType = GetLongParameter (c, par->socketTypeLong, par->MitSocketType(), -1);
    socketProtocol = GetLongParameter (c, par->socketProtocolLong, par->MitSocketProtocol(), -1);
    socketFamily = GetLongParameter (c, par->socketFamilyLong, par->MitSocketFamily(), -1);
    // ScriptSocket anlegen
    par->privScriptSocket = new ScriptSocket (WBase::hFrameWin, WMU_SOCKETEVENT, 
                                              socketType, socketProtocol, socketFamily);
    // Verbindung anfordern
    if (par->privScriptSocket->ScriptSocket::StartConnect (connectAddress, &setIsConnected))
      c->WritelData (par->mySocketObj,&par->privScriptSocket,sizeof(par->privScriptSocket),
                     LPSTR (param) - sizeof(WORD));
    else {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    if (par->privScriptSocket != NULL) {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      }
    c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    if (par->privExtraData != NULL) {
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }

    c->ClearlConnection (par->isConnected,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->connectAddress,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//-------------------------------------

#pragma pack(1)
struct FAR NetAccept_param {
  WORD parSize;                    // Prototyp: private 8
  SOCKETOBJ privScriptSocket;      // 4
  LPCONNEXTRAINFO privExtraData;   // 4 
  DWORD isConnected;
  DWORD mySocketObj;
  DWORD acceptAddressObj;
  DWORD listenSocketObj;
  };
#pragma pack()

BOOL NetAccept (mdiChild *c, LPVOID param, WORD mode)
  {
  NetAccept_param FAR *par = (NetAccept_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    par->privExtraData = CopyExtraData( c );
    // Parameter einlesen/zugaenglich machen
    LPSOCKETOBJ listenSocket = LPSOCKETOBJ (c->ReadlData (par->listenSocketObj));
    ScriptVar setIsConnected (c, param, par->isConnected, TRUE, par->privExtraData);
    // ScriptSocket anlegen
    par->privScriptSocket = new ScriptSocket (WBase::hFrameWin, WMU_SOCKETEVENT);
    // Verbindung akzeptieren
    if (par->privScriptSocket->DoAccept (*listenSocket, &setIsConnected)) {
      // Socket und Adresse zurueckschreiben
      c->WritelData (par->mySocketObj,&par->privScriptSocket,sizeof(par->privScriptSocket),
                     LPSTR (param) - sizeof(WORD));
      c->WritelData (par->acceptAddressObj,par->privScriptSocket->address,
                     GetBlockSize (par->privScriptSocket->address),LPSTR (param) - sizeof(WORD));
      }
    else {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    if (par->privScriptSocket != NULL) {
      delete par->privScriptSocket ;
      par->privScriptSocket = NULL;
      }
    c->DellData (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    if (par->privExtraData != NULL) {
      FreeGlobMem (par->privExtraData);
      par->privExtraData = NULL;
      }

    c->ClearlConnection (par->isConnected,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->mySocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->acceptAddressObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->listenSocketObj,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//-------------------------------------

#pragma pack(1)
struct FAR NetReceive_param {
  WORD parSize;                    // Prototyp: private 8
  SOCKETOBJ privScriptSocket;      // 4
  LPCONNEXTRAINFO privExtraData;   // 4
  DWORD receiveSocketObj;
  DWORD receiveProc;
  DWORD receiveLenLong;
  DWORD useBlobFlag;
  BOOL MitReceiveLen ()
    {
    return (parSize >= sizeof(*this) - sizeof (DWORD));
    }
  BOOL MitUseBlob ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL NetReceive (mdiChild *c, LPVOID param, WORD mode)
  {
  NetReceive_param FAR *par = (NetReceive_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSOCKETOBJ receiveSocket = LPSOCKETOBJ (c->ReadlData (par->receiveSocketObj));
    if (receiveSocket != NULL)
      par->privScriptSocket = *receiveSocket;
    else
      par->privScriptSocket = NULL;
    if (par->privScriptSocket != NULL) {
      par->privExtraData = CopyExtraData( c );
      LPSTR functionName = LPSTR (c->ReadlData (par->receiveProc));
      LONG receiveLen = GetLongParameter (c, par->receiveLenLong, par->MitReceiveLen(), 4096);
      DBBOOL useBlob = GetFlagParameter (c, par->useBlobFlag, par->MitUseBlob(), FALSE);
      WORD functionArgs[2];
      if (useBlob)
        functionArgs[0] = VAR_BLOB ;
      else
        functionArgs[0] = VAR_OBJ ;
      functionArgs[1] = VAR_LONG ;
      ScriptFunction setReceiveProc (c, functionName, 2, functionArgs, TRUE, par->privExtraData);
      // Abhoeren auf Daten ausloesen
      par->privScriptSocket->StartReceive (&setReceiveProc, receiveLen, useBlob);
      }
    else
      par->privExtraData = NULL;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    if (par->privScriptSocket != NULL)
      par->privScriptSocket->StopReceive ();
    if (par->privExtraData != NULL)
      FreeGlobMem (par->privExtraData);

    c->ClearlConnection (par->receiveSocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->receiveProc,LPSTR (param) - sizeof(WORD));
    if (par->MitReceiveLen ())
      c->ClearlConnection (par->receiveLenLong,LPSTR (param) - sizeof(WORD));
    if (par->MitUseBlob ())
      c->ClearlConnection (par->useBlobFlag,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }
  
//-------------------------------------

#pragma pack(1)
struct FAR NetSend_param { // Prototyp: private 0
  WORD parSize;                       
  DWORD sendSocketObj;
  DWORD toSend;
  DWORD bytesNotSent; // optional, short oder long
  BOOL MitBytesNotSent ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL NetSend (mdiChild *c, LPVOID param, WORD mode)
  {
  NetSend_param FAR *par = (NetSend_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Parameter einlesen
    LPSOCKETOBJ sendSocket = LPSOCKETOBJ (c->ReadlData (par->sendSocketObj));
    if ((sendSocket != NULL) && ((*sendSocket) != NULL)) {
      LPVOID toSend = c->ReadlData (par->toSend);
      int bytesNotSent;
      if (toSend != NULL) {
        // Daten senden
        bytesNotSent = GetBlockSize (toSend);
        (*sendSocket)->DoSend (toSend, &bytesNotSent);
        }
      else
        bytesNotSent = 0;
      // bytesNotSent zurueckschreiben
      if (par->MitBytesNotSent()) {
        DBINT dbBytesNotSent;
        dbBytesNotSent = DBINT (bytesNotSent);
        c->WritelData (par->bytesNotSent,&dbBytesNotSent,sizeof (dbBytesNotSent),
                       LPSTR (param) - sizeof(WORD));
        }
      }
    }
  if (mode & (EM_FIXCONNECTION)) {
    c->SetlConnection (par->toSend,LPSTR (param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->sendSocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->toSend,LPSTR (param) - sizeof(WORD));
    if (par->MitBytesNotSent())
      c->ClearlConnection (par->bytesNotSent,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL NetSendBlob (mdiChild *c, LPVOID param, WORD mode)
  {
  NetSend_param FAR *par = (NetSend_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Parameter einlesen
    LPSOCKETOBJ sendSocket = LPSOCKETOBJ (c->ReadlData (par->sendSocketObj));
    if ((sendSocket != NULL) && ((*sendSocket) != NULL)) {
      LPBLOBDESC blobToSend = (LPBLOBDESC) c->ReadlData (par->toSend);
      int bytesNotSent;
      if (blobToSend != NULL) {
        LPVOID toSend = GlobalLock (blobToSend->hGmem);
        // Daten senden
        bytesNotSent = blobToSend->Size;
        (*sendSocket)->DoSend (toSend, &bytesNotSent);
        // bytesNotSent zurueckschreiben
        GlobalUnlock (blobToSend->hGmem);
        }
      else
        bytesNotSent = 0;
      if (par->MitBytesNotSent()) {
        LONG dbBytesNotSent;
        dbBytesNotSent = LONG (bytesNotSent);
        c->WritelData (par->bytesNotSent,&dbBytesNotSent,sizeof (dbBytesNotSent),
                       LPSTR (param) - sizeof(WORD));
        }
      }
    }
  if (mode & (EM_FIXCONNECTION)) {
    c->SetlConnection (par->toSend,LPSTR (param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->sendSocketObj,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->toSend,LPSTR (param) - sizeof(WORD));
    if (par->MitBytesNotSent())
      c->ClearlConnection (par->bytesNotSent,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//-------------------------------------

#pragma pack(1)
struct FAR NetStatus_param {
  WORD parSize;                    // Prototyp: private 0
  DWORD statusCode;
  DWORD statusSocketObj;
  };
#pragma pack()

BOOL NetStatus (mdiChild *c, LPVOID param, WORD mode)
  {
  NetStatus_param FAR *par = (NetStatus_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Status fuer welchen Socket
    LPSOCKETOBJ statusSocket = LPSOCKETOBJ (c->ReadlData (par->statusSocketObj));
    if ((statusSocket != NULL) && ((*statusSocket) != NULL)) {
      c->WritelData (par->statusCode,&(*statusSocket)->lastErr,sizeof((*statusSocket)->lastErr),
                     LPSTR (param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->statusCode,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->statusSocketObj,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//-------------------------------------

#pragma pack(1)
struct FAR NetError_param {
  WORD parSize;                    // Prototyp: private 0
  DWORD errorCode;
  DWORD errorSocketObj;
  };
#pragma pack()

BOOL NetError (mdiChild *c, LPVOID param, WORD mode)
  {
  NetError_param FAR *par = (NetError_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Error fuer welchen Socket
    LPSOCKETOBJ errorSocket = LPSOCKETOBJ (c->ReadlData (par->errorSocketObj));
    if ((errorSocket != NULL) && ((*errorSocket) != NULL)) {
      c->WritelData (par->errorCode,&(*errorSocket)->lastErr,sizeof((*errorSocket)->lastErr),
                     LPSTR (param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->errorCode,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->errorSocketObj,LPSTR (param) - sizeof(WORD));
    }
  return FALSE;
  }

//************************************************************************
// Funktionen fuer Message-Loop

void CheckSocketEvent (WPARAM wP, LPARAM lP)

  {
  LPSCRIPTSOCKET FAR *eventScriptSocket = (LPSCRIPTSOCKET FAR *) (SocketHash->GetData (LONG (wP)));
  if (eventScriptSocket != NULL)
    (*eventScriptSocket)->CheckEvent (lP);
  }

void FreeSocketData ()
  {
  if (SocketHash != NULL)
    delete SocketHash; // Hash-Tabelle (winSocket -> Speicheradresse) aller ScriptSockets
  }

//************************************************************************
  
