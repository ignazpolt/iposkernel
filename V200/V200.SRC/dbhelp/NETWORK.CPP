//////////////////////////////////////////////////////////////////////////////
//
//  Verschiedene Netzwerks - Hilfsfunktionen
//
// 18.03.96 FL Moved from DMWAPI to DBHELP to dissolve the dependancy cycle.
// 14.03.96 FL Integration of new DLL : DNETxx - DLL
//
/////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "btrieve.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"

#define MODULENUM   134
#include "winass.hpp"


extern LPSTR WINAPI GetIniName ();
#define MYINI           GetIniName ()
//#define USESEMA         "UseSema"
//#define USESEMADEF      "yes"
//#define DATASECTION     "Data"

#define NETDEFINE       "Net"
#define NETSECTION      "Network"
#define NETDEFAULT      "NONE"

struct SemaList {
  SemaList FAR *Next ;
  DWORD Handle;
  LPSTR Name;
  };

static SemaList FAR *MySemas;
static LONG _actHandle = 1L;

static BOOL       useSemaphors = FALSE;
static BOOL       dllLoaded = FALSE;
static DLLHANDLE  NetDLL;
static LPDLLENTRY NetDLLEntry = NULL;
static char       subAddressID[20] = "" ;

void LoadNetDLL() 
  {               
  if (!dllLoaded) {
    char netdllstr[128];
    GetPrivateProfileString(NETSECTION, NETDEFINE, NETDEFAULT, netdllstr, sizeof(netdllstr), MYINI);
    dllLoaded = TRUE;
    if (lstrcmp(netdllstr,NETDEFAULT)) {
      NetDLL = GetDLLAdmin()->LoadDLL(netdllstr);
      NetDLLEntry = GetDLLAdmin()->GetDLLEntry(NetDLL);
      useSemaphors = NetDLLEntry->NetSemaphoreAvailable (); // if none is the name of the DLL, this evals to FALSE anyway..
      }
    else {
      NetDLLEntry = NULL;
      useSemaphors = FALSE;
      }
    } // if
  } // CheckNetDLL


/* internal Semaphore Handling for DLLs which do not support semaphors */

static void MyOpenSemaphore (DWORD h,LPSTR nm)
  {
  SemaList FAR *n = (SemaList FAR *) GetGlobMem (sizeof(*n));
  n->Next = MySemas;
  MySemas = n;
  n->Handle = h ;
  n->Name = LPSTR (GetGlobMem (lstrlen(nm)+1));
  lstrcpy (n->Name,nm);
  }

static void MyCloseSemaphore (DWORD Handle)
  {
  SemaList FAR *prev = NULL ;
  for (SemaList FAR *h = MySemas ; h != NULL ; h = h->Next) {
    if (h->Handle == Handle) {
      if (prev != NULL) prev->Next = h->Next ;
      else              MySemas = h->Next ;
      FreeGlobMem (h->Name);
      FreeGlobMem (h);
      break ;
      }
    prev = h ;
    }
  }

static BOOL MyTestSemaphore (LPSTR nm)
  {
  for (SemaList FAR *h = MySemas ; h != NULL ; h = h->Next) {
    if (lstrcmp (h->Name,nm) == 0)
      return TRUE ;
    }
  return FALSE ;
  }

/* The defined function calls */

DLLExport int _export WINAPI NWSocketFamily ()
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NWSocketFamily ();
  else {
    return -1;
    }
  }

DLLExport int _export WINAPI NWAddressSize ()
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NWAddressSize ();
  else {
    return 0;
    }
  }

DLLExport int _export WINAPI NWSocketProtocol (int type)
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NWSocketProtocol (type);
  else {
    return -1;
    }
  }

DLLExport void _export WINAPI GetNWAddress (LPSTR str,int size)
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    NetDLLEntry->GetUniqueAddress (str, size);
  else
    *str = '\0';
  if ( (int)*str <= 0) {
    lstrcpy (str+1,"UNDEFINED");
    *str = lstrlen(str+1);
    } // if
  
  //Am Ende noch die subAddressID hinzufügen:
  int i = str[0] + 1;
  int j = 0 ;
  --size ;
  while ((i < size) && (subAddressID[j])) {
    str[i++] = subAddressID[j++] ;
    }
  str[i] = '\0' ;
  str[0] = i ;
  }

DLLExport void _export WINAPI SetNWSubAddressID (LPSTR str)
  {
  int i ;
  for ( i = 0 ; (str[i]) && (i < sizeof (subAddressID) - 1); i ++ ) {
    subAddressID[i] = str[i] ;
    }
  subAddressID[i] = '\0' ;
  } //SetNWSubAddressID

DLLExport BOOL _export WINAPI NWAddressStrToBin (LPVOID binAddr, int *size, LPSTR str, DBINT port)
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NWAddressStrToBin (binAddr, size, str, port);
  else {
    *size = 0;
    return FALSE;
    }
  }

DLLExport BOOL _export WINAPI NWAddressBinToStr (LPSTR str, int size, DBINT *port, LPVOID binAddr)
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NWAddressBinToStr (str, size, port, binAddr);
  else {
    *str = '\0';
    *port = -1;
    return FALSE;
    }
  }

DLLExport DWORD _export WINAPI SetStationSemaphor (LPSTR uniqueID)
  {
  LoadNetDLL();
  if (useSemaphors) {
    return NetDLLEntry->NetSetStationsemaphor (uniqueID);
    } 
  else {          
    return 0;
    } // if
  }

DLLExport void _export WINAPI ClearStationSemaphor (DWORD Handle)
  {
  LoadNetDLL();
  if (useSemaphors) {
    NetDLLEntry->NetClearStationSemaphor (Handle);
    } 
  else {
    } // if
  }

DLLExport BOOL _export WINAPI CheckStationSemaphor (LPSTR uniqueID)
  {
  LoadNetDLL();
  if (useSemaphors) {
    return NetDLLEntry->NetCheckStationSemaphor (uniqueID);
    } 
  else {
    return (FALSE);
    } // if
  }

DLLExport DWORD _export SetSema (LPSTR Name,WORD FAR *Count)
  {
  DWORD Handle = 0;
  LoadNetDLL();
  if (useSemaphors) {
    Handle = NetDLLEntry->NetSetSema (Name, Count);
    if (Handle != 0) { // got a semaphore, we manage it in here now (see old network.cpp)
      MyOpenSemaphore(Handle, Name);
      } // if
    } 
  else {
    Handle = _actHandle++ ;
    MyOpenSemaphore (Handle,Name);
    } // if
  return (Handle);
  }

DLLExport void _export WINAPI ClearSema (DWORD Handle)
  {
  LoadNetDLL();
  if (Handle) {
    if (useSemaphors) {
      NetDLLEntry->NetClearSema (Handle);
      MyCloseSemaphore(Handle);
      } 
    else {
      MyCloseSemaphore (Handle);
      } // if
    } // if
  }

DLLExport BOOL _export TestSema (LPSTR Name)
  {
  LoadNetDLL();
  if (useSemaphors) {
    if (MyTestSemaphore (Name)) 
      return TRUE;
    return NetDLLEntry->NetTestSema (Name);
    } 
  else {
    return MyTestSemaphore (Name);
    } // if
  }

DLLExport int _export WINAPI GetConnectionNmbr ()
  {
  LoadNetDLL();
  if (NetDLLEntry != NULL)
    return NetDLLEntry->NetGetConnectionNmbr ();
  else
    return 0;
  }

