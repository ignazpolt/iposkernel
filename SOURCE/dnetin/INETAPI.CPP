/*****************************************************************************
 FILE:              INETAPI.CPP
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           DDSORA - Clinicum
 
 PRODUCT:           Clinicum
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    F. Loeliger
 
 DATE:              13.03.1996
 
 DESCRIPTION:       Network functions based on Windows Sockets V1.1
 
 ENVIRONMENT:       Windows Application
                    MSVC V7.0 
                    MKS - RCS is used for the revision controlling
                    Windows Sockets V1.1
                    
 VERSION:           0.1    first tests
 
 STATUS:            develop
 
 MODIFIED:          
   13.03.96 FL  created
   
*****************************************************************************/
#include <windows.h>
#include <stdio.h>

#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#endif

#include "dds32.h"
#include "globmem.h"
#include "winsock.h"


#define MODULENUM   901
#include "winass.hpp"

extern LPSTR WINAPI GetIniName ();
#define MYINI           GetIniName ()

void socket_error();
int  open_winsock();
int  close_winsock();

/************************************************************************
  NetSemaphoreAvailable

  purpose:  Determines, whether there are Semaphores available or not
  input:    --
  output:   --
  return:   TRUE   This DLL supports Semaphors
            FALSE  semaphores not supported
            
*************************************************************************/
DLLExport BOOL _export WINAPI NetSemaphoreAvailable ()
  {
    return (FALSE);
  } // NetSemaphoreAvailable

/************************************************************************
  NWSocketFamily

  purpose:  returns the socket family for WinSockets
  return:   socket family
            
*************************************************************************/
DLLExport int _export WINAPI NWSocketFamily ()
  {
  return PF_INET;
  } // NWSocketFamily

/************************************************************************
  NWAddressSize

  purpose:  returns the (maximum) size of a (binary) network address
  return:   size of network address
            
*************************************************************************/
DLLExport int _export WINAPI NWAddressSize ()
  {
  return sizeof (SOCKADDR_IN);
  } // NWAddressSize

/************************************************************************
  NWSocketProtocol

  purpose:  returns the protocol for a given socket type
  input:    type        socket type
  return:   protocol for the socket type or -1 if unknown
            
*************************************************************************/
DLLExport int _export WINAPI NWSocketProtocol (int type)
  {
  if (type == SOCK_DGRAM)
    return IPPROTO_UDP;
  else if (type == SOCK_STREAM)
    return IPPROTO_TCP;
  else
    return -1;
  } // NWSocketProtocol

/************************************************************************
  GetUniqueAddress

  purpose:  determines a unique address based on winsockets
  input:    str         buffer to fill (Pascal String warum auch immer)
            size        maximal size of the buffer 
  output:   --
  return:   TRUE        the windows sockets have been opened successfully
            FALSE       the windows sockets haven't been opened successfully
            
*************************************************************************/
DLLExport void _export WINAPI GetUniqueAddress (LPSTR str,int size)
  {
  char evn[100];
  GetPrivateProfileString ("Network","EnvVarName", "", evn, sizeof(evn),MYINI);
  if (*evn != '\0') {
    // erst mal in der hier angegebenen Environment-Variable nachsehen
    char env[100];
    *env = '\0';
    GetEnvironmentVariable(evn,env,sizeof(env) - 1);
    if (*env != '\0') {
      // wenn auch noch was drin steht, ist das der Platz-Identifier
      lstrcpy(str+1, env);
      *str = lstrlen(env);
      return;
      }
    }
  char buf[30];
  GetPrivateProfileString ("Network","DHCP", "no", buf, sizeof(buf),MYINI);
  if (lstrcmp(buf,"yes") == 0) {
    // statt der IP-Adresse den Computernamen ermitteln
    #define ENTRYLEN (_MAX_PATH * 2 + 5)
    DWORD dwType;
    DWORD dwValueSize = ENTRYLEN;
    TCHAR szValue[ENTRYLEN];
    LONG lResult;
    HKEY hKeyReg;
    lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", 0, KEY_READ, &hKeyReg);
    WIN_ASSERT_TEXT ((lResult == ERROR_SUCCESS), "Registry-Key fuer ComuterName kann nicht gelesen werden !");
    lResult = RegQueryValueEx(hKeyReg, "ComputerName", NULL, &dwType,
                              (LPBYTE) szValue, &dwValueSize);
    RegCloseKey(hKeyReg);
    WIN_ASSERT_TEXT ((lResult == ERROR_SUCCESS && dwType == REG_SZ), "ComputerName kann nicht gelesen werden !");
    lstrcpy(str+1, szValue);
    *str = lstrlen(szValue);
    }
  else {
    char      hostname[128];
    int       namelen = sizeof(hostname);
    struct    hostent FAR *hostentPtr;
    char FAR *inetstr;
    struct in_addr  FAR * ia;
    BOOL      done = FALSE;
  
    /* start the winsockets, ensure that we got a version 1.1 compatible one */  
    if (gethostname(hostname, namelen) != SOCKET_ERROR) {
      hostentPtr = gethostbyname(hostname);      
      if (hostentPtr != NULL) {
        ia = (struct in_addr FAR *)(hostentPtr->h_addr_list[0]);
        inetstr = inet_ntoa(*ia);
        lstrcpy(str+1, inetstr);
        *str = lstrlen(inetstr);
        done = TRUE;
      } // if
      else 
        socket_error();
      } // if
    else
      socket_error();
    if (!done) {
      lstrcpy (str+1,"DOS");
      *str = 3;
      } // if
    }
  } // GetUniqueAddress

/************************************************************************
  NWAddressStrToBin

  purpose:  converts a network address from string to binary
  input:    binAddr     buffer to fill
            size        maximal size of the buffer 
            str         string network address
  output:   binAddr     binary network address
            size        bytes needed
  return:   TRUE        address converted
            FALSE       error occured
            
*************************************************************************/
DLLExport BOOL _export WINAPI NWAddressStrToBin (LPVOID binAddr,int *size,LPSTR str,DBINT port)
  {
  LPSOCKADDR_IN nwAddr = LPSOCKADDR_IN (binAddr);
  if (*size < sizeof (*nwAddr)) {
    *size = sizeof (*nwAddr);
    return FALSE;
    }
  else {
    *size = sizeof (*nwAddr);
    nwAddr->sin_port = htons (port);
    nwAddr->sin_family = AF_INET;
    nwAddr->sin_addr.s_addr = inet_addr (str);
    if (nwAddr->sin_addr.s_addr != INADDR_NONE)
      return TRUE;
    else
      return FALSE;
    }
  } // NWAddressStrToBin

/************************************************************************
  NWAddressBinToStr

  purpose:  converts a network address from binary to string
  input:    str         buffer to fill
            size        maximal size of the buffer 
            binAddr     binary network address
  output:   str         string network address
  return:   TRUE        address converted
            FALSE       error occured
            
*************************************************************************/
DLLExport BOOL _export WINAPI NWAddressBinToStr (LPSTR str,int size,DBINT *port,LPVOID binAddr)
  {
  LPSOCKADDR_IN nwAddr = LPSOCKADDR_IN (binAddr);
  *port = ntohs  (nwAddr->sin_port);
  LPSTR inetstr;
  inetstr = inet_ntoa (nwAddr->sin_addr);
  if (int (strlen (inetstr)) >= size) {
    lstrncpy(str, inetstr, size - 1);
    str [size] = '\0';
    return FALSE;
    }
  else {
    lstrcpy(str, inetstr);
    return TRUE;
    }
  } // NWAddressBinToStr

/************************************************************************
  NetSetStationSemaphor

  purpose:  Sets the Net Semaphore
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    uniqueID   The unique description of the semaphore
  output:   --
  return:   --
            
*************************************************************************/
DLLExport DWORD _export WINAPI NetSetStationSemaphor (LPSTR uniqueID)
  {
  DWORD Handle = 0;
  return Handle;
  }

/************************************************************************
  NetClearStationSemaphor

  purpose:  Clears a Net Semaphore
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    Handle  the handle of the semaphore
  output:   --
  return:   --
            
*************************************************************************/
DLLExport void _export WINAPI NetClearStationSemaphor (DWORD Handle)
  {
  }

/************************************************************************
  NetCheckStationSemaphor

  purpose:  Checks the Semaphore in the Net
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    uniqueID   The unique name of the Semaphore
  output:   --
  return:   TRUE  The semaphore exists
            FALSE The semaphore not exists
            
*************************************************************************/
DLLExport BOOL _export WINAPI NetCheckStationSemaphor (LPSTR uniqueID)
  {
  return (FALSE) ;
  }


/************************************************************************
  NetSetSema

  purpose:  Sets the semaphore
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    Name   the name of the semaphore
  output:   Count  nothing at the moment
  return:   the handle of the new semaphore
            0    the semaphore has not been created successfully
            
*************************************************************************/
DLLExport DWORD _export WINAPI NetSetSema (LPSTR Name,WORD FAR *Count)
  {
  DWORD Handle = 0;
  return Handle;
  }

/************************************************************************
  NetClearSema

  purpose:  Clears the semaphore
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    Handle  the handle of the semaphore
  output:   --
  return:   --
            
*************************************************************************/
DLLExport void _export WINAPI NetClearSema (DWORD Handle)
  {
  if (Handle) {
    } // if
  }

/************************************************************************
  NetTestSema

  purpose:  Tests whether a semaphor exists or not 
            NOT YET FULLY IMPLEMENTED FOR WINSOCKETS
  input:    Name    the name of the semaphore
  output:   --
  return:   TRUE    the semaphore exists
            FALSE   the semaphore does not exist
            
*************************************************************************/
DLLExport BOOL _export WINAPI NetTestSema (LPSTR Name)
  {
  BOOL res = FALSE ;
  return res;
  }

/************************************************************************
  NetGetConnectionNmbr

  purpose:  determines the connectionnumber. This is only used within the novell
            based DLL 
  input:    --
  output:   --
  return:   0       This DLL returns 0, always
            
*************************************************************************/
DLLExport int _export WINAPI NetGetConnectionNmbr ()
{
  return 0;
} // NetGetConnectionNmbr


/************************************************************************
  open_winsock

  purpose:  tries to open the windows sockets 
  input:    --
  output:   --
  return:   TRUE        the windows sockets have been opened successfully
            FALSE       the windows sockets haven't been opened successfully
            
*************************************************************************/
int open_winsock()
{ 
  int     ret = FALSE;
  WORD    versionRequest;
  WSADATA wsaData;
  
  /* this DLL is designed for Version 1.1 of winsockets */
  versionRequest = MAKEWORD(1,1);

  /* start the winsockets, ensure that we got a version 1.1 compatible one */  
  if (WSAStartup(versionRequest, &wsaData) != SOCKET_ERROR) {
    if ( LOBYTE(wsaData.wVersion) == 1 && 
         HIBYTE(wsaData.wVersion) == 1 ) {
      ret = TRUE;
      } // if
    else {   
      close_winsock();
      } // if
    } // if      
  else
    socket_error();
  return (ret);
} // open_winsock

/************************************************************************
  close_winsock

  purpose:  closes the windows sockets 
  input:    --
  output:   --
  return:   TRUE        the windows sockets have been closed successfully
            FALSE       the windows sockets haven't been closed successfully
            
*************************************************************************/
int close_winsock()
{ 
  int ret = (WSACleanup() != SOCKET_ERROR);
  if (!ret) socket_error();
  return (ret);
} // close_winsock

/************************************************************************
  socket_error

  purpose:  produces an appropriate error message for the last error
            At the moment no error message is shown.
  input:    --
  output:   --
  return:   --
            
*************************************************************************/
void socket_error()
{
/*
  char msg[500], msg1[100];
  int  errcode;

  errcode = WSAGetLastError();
  if (errcode == WSAEFAULT)                lstrcpy(msg1, "namelen too small");
  else if (errcode == WSANOTINITIALISED)   lstrcpy(msg1, "WSAStartup not yet called");
  else if (errcode == WSAENETDOWN)         lstrcpy(msg1, "Network subsystem failed");
  else if (errcode == WSAEINPROGRESS)      lstrcpy(msg1, "A block in Windows Socket operation is in progress");
  // WSAStartup codes
  else if (errcode == WSASYSNOTREADY)      lstrcpy(msg1, "Underlaying Network System not ready");
  else if (errcode == WSAVERNOTSUPPORTED)  lstrcpy(msg1, "requested Version of Windows Sockets API not provided by DLL");
  else if (errcode == WSAEINVAL)           lstrcpy(msg1, "Windows Socket version not supported by DLL");
  // additional gethostbyname codes
  else if (errcode == WSAHOST_NOT_FOUND)   lstrcpy(msg1, "authoritative answer host not found");
  else if (errcode == WSATRY_AGAIN)        lstrcpy(msg1, "non-authoritative host not found or SERVERFAIL");
  else if (errcode == WSANO_RECOVERY)      lstrcpy(msg1, "non recoverable error (FORMERR, REFUSED, NOTIMP)");
  else if (errcode == WSANO_DATA)          lstrcpy(msg1, "Valid name, no data record of requested type");
  else if (errcode == WSAEINTR)            lstrcpy(msg1, "the blocking call was canceled intentionally");
  else 
    lstrcpy(msg1, "");
  sprintf(msg, "socket error = %d <%s>", msg1);
  MessageBox((HWND)NULL, msg, MessageBoxTitle, MB_ICONINFORMATION);
*/
} // socket_error

