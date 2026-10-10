/*****************************************************************************
 FILE:              NNETAPI.CPP
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           DDSORA - Clinicum
 
 PRODUCT:           Clinicum
 
 AUTHOR:            Softworks  - Glance AG, CH-Steinmaur
                    F. Loeliger
 
 DATE:              14.03.1996
 
 DESCRIPTION:       Network functions based on Novell Network (IPX/SPX)
 
 ENVIRONMENT:       Windows Application
                    MSVC V7.0 
                    MKS - RCS is used for the revision controlling
                    IPX/SPX
                    
 VERSION:           0.1    first tests
 
 STATUS:            develop
 
 MODIFIED:          
   18.03.96 FL  MySemaphores moved to network.cpp
   14.03.96 FL  created
   
*****************************************************************************/
#include <windows.h>
#include <stdio.h>

#ifdef WIN32
#include <winsock.h>
#include <wsipx.h>
#include <wsnwlink.h>
#include <stdlib.h>

void socket_error();
int  open_winsock();
int  close_winsock();
#endif


#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#endif

#include "dds32.h"
#include "btrieve.hpp"
#include "globmem.h"
#include "ipx.h"

#define MODULENUM   902

extern LPSTR WINAPI GetIniName ();
#define MYINI           GetIniName ()
#define USESEMA         "UseSema"
#define USESEMADEF      "yes"
#define DATASECTION     "Data"

static LPIPXINITIALIZE lpipxinitialize;
static LPIPXGETINTERNETWORKADDRESS lpipxgetinternetworkaddress;
static LPOPENSEMAPHORE lpopensemaphore;
static LPWAITONSEMAPHORE lpwaitonsemaphore;
static LPCLOSESEMAPHORE lpclosesemaphore;
static LPSIGNALSEMAPHORE lpsignalsemaphore;

#ifndef WIN32
extern "C" {
extern void WINAPI DOS3CALL();
  }
#endif

static struct LibDesc {
  HINSTANCE hInst;
  char Name[20];
  BOOL IsLoaded;
  } NetwareLibs[2] = 
  {
    { 0 , "nwipxspx.dll" , FALSE } ,
    { 0 , "nwsync.dll" , FALSE }
  };

static FARPROC GetLibFnc (int LibNum,LPCSTR FuncName)
  {
  if (!NetwareLibs[LibNum].IsLoaded) {
    NetwareLibs[LibNum].hInst = LoadLibrary (NetwareLibs[LibNum].Name);

#ifdef WIN32
    DWORD ErrNum;
    if (NetwareLibs[LibNum].hInst == NULL) {
      ErrNum = GetLastError ();
      }
#endif

    NetwareLibs[LibNum].IsLoaded = TRUE;
    }
  return GetProcAddress (NetwareLibs[LibNum].hInst,FuncName);
  }

static DWORD IpxTaskID;
DLLExport BOOL _export WINAPI DoUseNetware (void)
  {
  static BOOL UseNetwareChecked;
  if (!UseNetwareChecked) {
    UseNetwareChecked = TRUE ;

    // Laden aller Netzwerk Funktions - Zeiger
    lpipxinitialize = LPIPXINITIALIZE (GetLibFnc (0,"IPXINITIALIZE")) ;
    lpipxgetinternetworkaddress = LPIPXGETINTERNETWORKADDRESS (GetLibFnc (0,"IPXGETINTERNETWORKADDRESS")) ;
    lpopensemaphore = LPOPENSEMAPHORE (GetLibFnc (1,"OPENSEMAPHORE")) ;
    lpwaitonsemaphore = LPWAITONSEMAPHORE (GetLibFnc (1,"WAITONSEMAPHORE")) ;
    lpclosesemaphore = LPCLOSESEMAPHORE (GetLibFnc (1,"CLOSESEMAPHORE")) ;
    lpsignalsemaphore = LPSIGNALSEMAPHORE (GetLibFnc (1,"SIGNALSEMAPHORE")) ;
    }

  return TRUE;
  }

static BOOL IpxInitialized;
static void InitializeIpx ()
  {
  if ((DoUseNetware()) && (!IpxInitialized)) {
    IpxTaskID = 0;
    ( *lpipxinitialize) (&IpxTaskID,2,546);
    IpxInitialized = TRUE ;
    }
  }

static char GetHexChar (BYTE ch,BOOL highnibble)
  {
  if (highnibble) {
    ch = ch >> 4 ;
    }
  ch &= 0x0F;

  return (ch >= 0x0A) ? 'A' + (ch - 0x0A) : '0' + ch ;
  }

static BOOL AddrBinToStr (LPSTR str, int maxSize, LPSTR netnum, LPSTR nodenum)
  {
  for (int i = 0 ; ((i < 10) && (i < maxSize - 2)) ; i ++) {
    char ch;
    if (i < 4) ch = netnum[i];
    else       ch = nodenum[i-4];
    str [2 * i    ] = GetHexChar(ch,TRUE);
    str [2 * i + 1] = GetHexChar(ch,FALSE);
    }
  str[2 * i] = '\0';
  return (i == 10);
  }

#define KLDIR         "kldir"
#define KLDIRDEF      ".\\"

static void GetDirChars (LPSTR dirch)
  {
  char Path[128];
  GetPrivateProfileString (DATASECTION,KLDIR,KLDIRDEF,
                              Path,sizeof(Path),
                              MYINI
                          );
  WORD QuerSumme = 0;
  lstrcpy (dirch,Path);
// for (LPSTR h = Path ; *h ; h++) QuerSumme += *h;
// dirch[0] = lstrlen (Path);
// dirch[1] = QuerSumme / 0x100 ;
// dirch[2] = QuerSumme % 0x100 ;
  }

static void StationSemaphorName (LPSTR SemName,int size,LPSTR uniqueID)
  {
  lmemset (SemName,'\0',size);
  lstrcpy (SemName,"StatSem");
  GetDirChars (SemName+7);
  lstrcpy (SemName+15,uniqueID+1);
  }


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
#ifdef WIN32
    return (FALSE);
#else
    return (TRUE);
#endif
  } // NetSemaphoreAvailable

/************************************************************************
  NWSocketFamily

  purpose:  returns the socket family for WinSockets
  return:   socket family
            
*************************************************************************/
DLLExport int _export WINAPI NWSocketFamily ()
  {
  return PF_IPX;
  } // NWSocketFamily

/************************************************************************
  NWAddressSize

  purpose:  returns the (maximum) size of a (binary) network address
  return:   size of network address
            
*************************************************************************/
DLLExport int _export WINAPI NWAddressSize ()
  {
  return sizeof (SOCKADDR_IPX);
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
    return NSPROTO_IPX;
  else if (type == SOCK_STREAM)
    return NSPROTO_SPX;
  else
    return -1;
  } // NWSocketProtocol

/************************************************************************
  GetUniqueAddress

  purpose:  determines a unique address based on winsockets
  input:    str         buffer to fill
            size        maximal size of the buffer 
  output:   --
  return:   TRUE        the windows sockets have been opened successfully
            FALSE       the windows sockets haven't been opened successfully
            
*************************************************************************/
DLLExport void _export WINAPI GetUniqueAddress (LPSTR str,int size)
  {
#ifdef WIN32
  int cAdapters = 1,
      cbOpt  = sizeof( cAdapters ),
      cbAddr = sizeof( SOCKADDR_IPX );

  SOCKET s;
  SOCKADDR_IPX Addr;

  // Create IPX socket.
  s = socket( AF_IPX, SOCK_DGRAM, NSPROTO_IPX );
  if (s == INVALID_SOCKET)
    socket_error();

  // Socket must be bound prior to calling IPX_MAX_ADAPTER_NUM
  memset( &Addr, 0, sizeof( Addr ));
  Addr.sa_family = AF_IPX;
  if (bind( s, (SOCKADDR*) &Addr, cbAddr) == SOCKET_ERROR)
    socket_error();

  // Get the number of adapters => cAdapters.
  if (getsockopt( (SOCKET) s, NSPROTO_IPX, IPX_MAX_ADAPTER_NUM,
                  (char *) &cAdapters, &cbOpt ) == SOCKET_ERROR)
    socket_error();

  // At this point cAdapters is the number of installed adapters.
  while ( cAdapters > 0 )
    {
    IPX_ADDRESS_DATA  IpxData;

    memset( &IpxData, 0, sizeof(IpxData));

    // Specify which adapter to check.
    IpxData.adapternum = cAdapters - 1;
    cbOpt = sizeof( IpxData );

    // Get information for the current adapter.
    if (getsockopt( s, NSPROTO_IPX, IPX_ADDRESS,
                    (char*) &IpxData, &cbOpt ) == SOCKET_ERROR)
      socket_error();

    lmemset (str,'\0',size);
    AddrBinToStr (str+1, size - 1, LPSTR (IpxData.netnum), LPSTR (IpxData.nodenum));
    str[0] = lstrlen (str+1);
    // IpxData contains the address for the current adapter.
    cAdapters--;
    }
#else
  if (DoUseNetware ()) {
    char Buffer[20];
    lmemset (str,'\0',size);
    InitializeIpx ();
    ( *lpipxgetinternetworkaddress ) (IpxTaskID,Buffer);
    // Umwandeln in (Pascal) Hex - String
    for (int i = 0 ; i < 10 ; i ++) {
      str [2 * i + 1] = GetHexChar(Buffer[i],TRUE);
      str [2 * i + 2] = GetHexChar(Buffer[i],FALSE);
      }
    str[0] = lstrlen (str+1);
    }
  else {
    lstrcpy (str+1,"DOS");
    *str = 3;
    }
#endif
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
  LPSOCKADDR_IPX nwAddr = LPSOCKADDR_IPX (binAddr);
  if (*size < sizeof (*nwAddr)) {
    *size = sizeof (*nwAddr);
    return FALSE;
    }
  else {
    char baseChar, einByte;
    int i;
    *size = sizeof (*nwAddr);
    nwAddr->sa_socket = htons (port);
    nwAddr->sa_family = AF_IPX;
    for (i = 0; i < 20; i++) {
      if ((str[i] >= '0') && (str[i] <= '9'))
        baseChar = '0';
      else if ((str[i] >= 'A') && (str[i] <= 'F'))
        baseChar = 'A' - 10;
      else if ((str[i] >= 'a') && (str[i] <= 'f'))
        baseChar = 'a' - 10;
      else
        break;
      if (i & 0x01) {
        einByte = einByte + (str[i] - baseChar);
        if (i < 8)
          nwAddr->sa_netnum[i >> 1] = einByte;
        else
          nwAddr->sa_nodenum[(i - 8) >> 1] = einByte;
        }
      else
        einByte = (str[i] - baseChar) << 4;
      }
    if ((i == 20) && (str[i] == '\0'))
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
  LPSOCKADDR_IPX nwAddr = LPSOCKADDR_IPX (binAddr);
  *port = ntohs  (nwAddr->sa_socket);
  return AddrBinToStr (str, size, nwAddr->sa_netnum, nwAddr->sa_nodenum);
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
#ifndef WIN32
  if (DoUseNetware ()) {
    char SemName[128];
    StationSemaphorName (SemName,sizeof(SemName),uniqueID);
    WORD count;
    ( *lpopensemaphore ) (SemName,1,&Handle,&count);
    if (Handle != 0) {
      if (( *lpwaitonsemaphore ) (Handle,9) != 0) {
        ( *lpclosesemaphore ) (Handle);
        Handle = 0;
        }
      }
    }
#endif
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
#ifndef WIN32
  if (DoUseNetware ()) {
    ( *lpsignalsemaphore ) (Handle);
    ( *lpclosesemaphore ) (Handle);
    }
#endif
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
  DWORD Handle = 1;
#ifndef WIN32
  if (DoUseNetware ()) {
    Handle = NetSetStationSemaphor (uniqueID);
    if (Handle)
      ( *lpclosesemaphore ) (Handle);
    }
#endif
  return (Handle == 0) ;
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
#ifndef WIN32
  if (DoUseNetware ()) {
    WORD count;
    ( *lpopensemaphore ) (Name,1,&Handle,&count);
    if (Handle != 0) {
      if (( *lpwaitonsemaphore ) (Handle,9) != 0) {
        ( *lpclosesemaphore ) (Handle);
        Handle = 0;
        }
      // >>> FL 18.03.96: the following is done in network.cpp
      // else
      //  MyOpenSemaphore (Handle,Name);
      }
    }
  // >>> FL 18.03.96: the following is done in network.cpp
  //else {
  //  Handle = _actHandle++ ;
  //  MyOpenSemaphore (Handle,Name);
  //  }
#endif
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
#ifndef WIN32
  if ((DoUseNetware ()) && (Handle)) {
    ( *lpsignalsemaphore ) (Handle);
    ( *lpclosesemaphore ) (Handle);
    // >>> FL 18.03.96: the following is done in network.cpp
    // >>> it seems, that a call to MyCloseSemaphore should be done also if not using netware...
    //MyCloseSemaphore (Handle);
    }
#endif
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
  DWORD Handle = 0;
  BOOL res = FALSE ;
#ifndef WIN32
  if (DoUseNetware ()) {
    // >>> FL 18.03.96: the following is done in network.cpp
    //if (MyTestSemaphore (Name)) return TRUE ;
    WORD count;
    ( *lpopensemaphore ) (Name,1,&Handle,&count);
    if (Handle != 0) {
      if (( *lpwaitonsemaphore ) (Handle,9) != 0) {
        ( *lpclosesemaphore ) (Handle);
        Handle = 0;
        res = TRUE ;
        }
      else {
        ( *lpclosesemaphore ) (Handle);
        res = FALSE ;
        }
      }
    }
  // >>> FL 18.03.96: the following is done in network.cpp
  //else
  //  return MyTestSemaphore (Name);
#endif
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
  BYTE ConnNmbr = 0;

#ifndef WIN32
  _asm {
    mov ax,0xDC00
    call DOS3CALL
    mov ConnNmbr,al
    }
#endif

  return int(ConnNmbr);
} // NetGetConnectionNmbr

#ifdef WIN32
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
#endif
