///////////////////////////////////////////////////////////////
//  Anbinden der KisQuery - Library
///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/kisquery.cpv   1.7   19 Dec 1996 08:45:00   HANNES  $
//  $Log:   P:/marille/clinicum/rev/kisquery.cpv  $
// 
//    Rev 1.7   19 Dec 1996 08:45:00   HANNES
// 16 - Bit Version wieder abgeglichen (Syntaxfehler bei KISERROR)
// 
//    Rev 1.6   17 Dec 1996 11:57:20   GERHOLD
// 32 Bit Umstellung
// 
//    Rev 1.4   02 Feb 1996 10:35:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   24 Aug 1995 00:19:54   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.2   14 Aug 1995 16:47:18   HANNES
// 
//    Rev 1.1   10 Aug 1995 09:28:58   MARTIN
// Zwischenversion
// 
//    Rev 1.0   26 Jul 1995 14:08:24   MARTIN
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
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
#include "dllchild.hpp"

#define MODULENUM 156
#include "winass.hpp"

#ifndef WIN32
  #include "wowglue.h"
#endif

// KisQuery-Funktionen:

#define KisRetSUCCESS  1L
#define KisRetERROR    0L
#define KisRetLENERR  -1L
#define KisQAttrINFO "TDKQINFO"


#ifdef WIN32
//  #define   WOWLoadLibraryEx32(LPSTR, b, c)   (LoadLibrary (LPSTR))
//  #define   WOWFreeLibrary32(a)        (FreeLibrary (a))
//  #define   WOWGetProcAddress32(a, b)  (GetProcAddress (a, b))
//  #define   WOWGetVDMPointer32(a,b)    (DWORD(a))
#endif

#ifdef WIN32
  typedef int KisRetcode;
  typedef void * KisSelection;
  typedef void * KisRecord;
  typedef void * KisTable;
#else
  typedef DWORD KisRetcode;
  typedef DWORD KisSelection;
  typedef DWORD KisRecord;
  typedef DWORD KisTable;
#endif

#ifdef WIN32
  HINSTANCE   hInstKisQuery;
#else
  HINSTANCE32 hInstKisQuery;
#endif


#ifdef WIN32
  typedef int    (CALLBACK *KISINIT) (char *);
  typedef int    (CALLBACK *KISEXIT) ();
  typedef LPVOID (CALLBACK *KISSELECTIONOPEN) (char *);
  typedef int    (CALLBACK *KISSELECTIONCLOSE) (LPVOID);
  typedef LPVOID (CALLBACK *KISRECORDREAD) (LPVOID);
  typedef int    (CALLBACK *KISRECORDWRITE) (LPVOID);
  typedef LPVOID (CALLBACK *KISRECORDCREATE) (char *);
  typedef int    (CALLBACK *KISRECORDFREE) (LPVOID);
  typedef LPVOID (CALLBACK *KISTABLEOPEN) (LPVOID, char *);
  typedef int    (CALLBACK *KISTABLECLOSE) (LPVOID);
  typedef int    (CALLBACK *KISDATAGET) (void *, long, long, char *, int *);
  typedef int    (CALLBACK *KISDATASET) (LPVOID, long, long, char *, int);
  typedef int    (CALLBACK *KISCONVBCDTOMAC) (char *, char *);
  typedef int    (CALLBACK *KISCONVMACTOBCD) (char *, char *);

  KISINIT lpfnKisInit;
  KISEXIT lpfnKisExit;
  KISSELECTIONOPEN  lpfnKisSelectionOpen;
  KISSELECTIONCLOSE lpfnKisSelectionClose;
  KISRECORDREAD lpfnKisRecordRead;
  KISRECORDWRITE lpfnKisRecordWrite;
  KISRECORDCREATE lpfnKisRecordCreate;
  KISRECORDFREE  lpfnKisRecordFree;
  KISTABLEOPEN lpfnKisTableOpen;
  KISTABLECLOSE lpfnKisTableClose;
  KISDATAGET lpfnKisDataGet;
  KISDATASET lpfnKisDataSet;
  KISCONVBCDTOMAC lpfnKisConvBcdToMac;
  KISCONVMACTOBCD lpfnKisConvMacToBcd;
#else   
  FARPROC lpfnKisInit;
  FARPROC lpfnKisExit;
  FARPROC lpfnKisSelectionOpen;
  FARPROC lpfnKisSelectionClose;
  FARPROC lpfnKisRecordRead;
  FARPROC lpfnKisRecordWrite;
  FARPROC lpfnKisRecordCreate;
  FARPROC lpfnKisRecordFree;
  FARPROC lpfnKisTableOpen;
  FARPROC lpfnKisTableClose;
  FARPROC lpfnKisDataGet;
  FARPROC lpfnKisDataSet;
  FARPROC lpfnKisConvBcdToMac;
  FARPROC lpfnKisConvMacToBcd;
  FARPROC lpfnKisError;
#endif

KisRetcode KisInit(LPSTR I_Token)
  {
  KisRetcode RetVal = KisRetERROR;

#ifdef WIN32
  hInstKisQuery = LoadLibrary ("KISDLL.DLL");
#else
  hInstKisQuery = WOWLoadLibraryEx32("KISDLL.DLL",NULL,NULL);
#endif
//  hInstKisQuery = GetModuleHandle("KISDLL");
  if (hInstKisQuery) {
#ifdef WIN32
    lpfnKisInit = (KISINIT)GetProcAddress(hInstKisQuery,"MyKisInit");
    lpfnKisExit = (KISEXIT)GetProcAddress(hInstKisQuery,"MyKisExit");
    lpfnKisSelectionOpen  = (KISSELECTIONOPEN)GetProcAddress(hInstKisQuery,"MyKisSelectionOpen");
    lpfnKisSelectionClose = (KISSELECTIONCLOSE)GetProcAddress(hInstKisQuery,"MyKisSelectionClose");
    lpfnKisRecordRead     = (KISRECORDREAD)GetProcAddress(hInstKisQuery,"MyKisRecordRead");
    lpfnKisRecordWrite    = (KISRECORDWRITE)GetProcAddress(hInstKisQuery,"MyKisRecordWrite");
    lpfnKisRecordCreate   = (KISRECORDCREATE)GetProcAddress(hInstKisQuery,"MyKisRecordCreate");
    lpfnKisRecordFree     = (KISRECORDFREE)GetProcAddress(hInstKisQuery,"MyKisRecordFree");
    lpfnKisTableOpen      = (KISTABLEOPEN)GetProcAddress(hInstKisQuery,"MyKisTableOpen");
    lpfnKisTableClose     = (KISTABLECLOSE)GetProcAddress(hInstKisQuery,"MyKisTableClose");
    lpfnKisDataGet        = (KISDATAGET)GetProcAddress(hInstKisQuery,"MyKisDataGet");
    lpfnKisDataSet        = (KISDATASET)GetProcAddress(hInstKisQuery,"MyKisDataSet");
    lpfnKisConvBcdToMac   = (KISCONVBCDTOMAC)GetProcAddress(hInstKisQuery,"MyKisConvBcdToMac");
    lpfnKisConvMacToBcd   = (KISCONVMACTOBCD)GetProcAddress(hInstKisQuery,"MyKisConvMacToBcd");
    
  #else
    lpfnKisInit = WOWGetProcAddress32(hInstKisQuery,"MyKisInit");
    lpfnKisExit = WOWGetProcAddress32(hInstKisQuery,"MyKisExit");
    lpfnKisSelectionOpen = WOWGetProcAddress32(hInstKisQuery,"MyKisSelectionOpen");
    lpfnKisSelectionClose = WOWGetProcAddress32(hInstKisQuery,"MyKisSelectionClose");
    lpfnKisRecordRead = WOWGetProcAddress32(hInstKisQuery,"MyKisRecordRead");
    lpfnKisRecordWrite = WOWGetProcAddress32(hInstKisQuery,"MyKisRecordWrite");
    lpfnKisRecordCreate = WOWGetProcAddress32(hInstKisQuery,"MyKisRecordCreate");
    lpfnKisRecordFree = WOWGetProcAddress32(hInstKisQuery,"MyKisRecordFree");
    lpfnKisTableOpen = WOWGetProcAddress32(hInstKisQuery,"MyKisTableOpen");
    lpfnKisTableClose = WOWGetProcAddress32(hInstKisQuery,"MyKisTableClose");
    lpfnKisDataGet = WOWGetProcAddress32(hInstKisQuery,"MyKisDataGet");
    lpfnKisDataSet = WOWGetProcAddress32(hInstKisQuery,"MyKisDataSet");
    lpfnKisConvBcdToMac = WOWGetProcAddress32(hInstKisQuery,"MyKisConvBcdToMac");
    lpfnKisConvMacToBcd = WOWGetProcAddress32(hInstKisQuery,"MyKisConvMacToBcd");
    lpfnKisError = WOWGetProcAddress32(hInstKisQuery,"MyKisError");
#endif
    if ((lpfnKisInit != NULL) &&
        (lpfnKisExit != NULL) &&
        (lpfnKisSelectionOpen != NULL) &&
        (lpfnKisSelectionClose != NULL) &&
        (lpfnKisRecordRead != NULL) &&
        (lpfnKisRecordWrite != NULL) &&
        (lpfnKisRecordCreate != NULL) &&
        (lpfnKisRecordFree != NULL) &&
        (lpfnKisTableOpen != NULL) &&
        (lpfnKisTableClose != NULL) &&
        (lpfnKisDataGet != NULL) &&
        (lpfnKisDataSet != NULL) &&
        (lpfnKisConvBcdToMac != NULL) &&
        (lpfnKisConvMacToBcd != NULL)) {

#ifdef WIN32
      RetVal = (*lpfnKisInit) (I_Token);
#else
      GlobalFix(WBase::hInstance);
      DWORD dwLinAddr = WOWGetVDMPointer32(I_Token,1);
      RetVal = WOWCallProc32(lpfnKisInit,0,1,dwLinAddr);
#endif

      GlobalUnfix(WBase::hInstance);
      }
    else {
      DBWIN_ASSERT(FALSE);
      }
    }
  else {
    DBWIN_ASSERT(FALSE);
    }
  return RetVal;
  }

KisRetcode KisExit()
  {
#ifdef WIN32
  KisRetcode RetVal = (*lpfnKisExit)();
  FreeLibrary(hInstKisQuery);
#else
  KisRetcode RetVal = WOWCallProc32(lpfnKisExit,0,0);
  WOWFreeLibrary32(hInstKisQuery);
#endif

  return RetVal;
  }

KisSelection KisSelectionOpen(LPSTR S_Token)
  {
#ifdef WIN32
  KisSelection RetVal = (*lpfnKisSelectionOpen)(S_Token);
#else
  GlobalFix(WBase::hInstance);

  DWORD dwLinAddr = WOWGetVDMPointer32(S_Token,1);
  KisSelection RetVal = WOWCallProc32(lpfnKisSelectionOpen,0,1,dwLinAddr);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisSelectionClose(KisSelection S)
  {
#ifdef WIN32
  return (*lpfnKisSelectionClose) (S);
#else
  return WOWCallProc32(lpfnKisSelectionClose,0,1,S);
#endif
  }

KisRecord KisRecordRead(KisSelection S)
  {
#ifdef WIN32
  return (*lpfnKisRecordRead)(S);
#else
  return WOWCallProc32(lpfnKisRecordRead,0,1,S);
#endif
  }

KisRetcode KisRecordWrite(KisRecord R)
  {
#ifdef WIN32
  return (*lpfnKisRecordWrite)(R);
#else
  return WOWCallProc32(lpfnKisRecordWrite,0,1,R);
#endif
  }

KisRecord KisRecordCreate(LPSTR C_Token)
  {
#ifdef WIN32
  KisRecord RetVal = (*lpfnKisRecordCreate)(C_Token);
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr = WOWGetVDMPointer32(C_Token,1);
  KisRecord RetVal = WOWCallProc32(lpfnKisRecordCreate,0,1,dwLinAddr);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisRecordFree(KisRecord R)
  {
#ifdef WIN32
  return (*lpfnKisRecordFree)(R);
#else
  return WOWCallProc32(lpfnKisRecordFree,0,1,R);
#endif
  }

KisTable KisTableOpen(KisRecord R, LPSTR T_Token)
  {
#ifdef WIN32
  KisRecord RetVal = (*lpfnKisTableOpen)(R,T_Token);
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr = WOWGetVDMPointer32(T_Token,1);
  KisRecord RetVal = WOWCallProc32(lpfnKisTableOpen,0,2,R,dwLinAddr);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisTableClose(KisTable T)
  {
#ifdef WIN32
  return (*lpfnKisTableClose)(T);
#else
  return WOWCallProc32(lpfnKisTableClose,0,1,T);
#endif
  }

KisRetcode KisDataGet(KisTable T, long x, long y, LPSTR p, long FAR *plen)
  {
#ifdef WIN32
//************************************************
//  return (*lpfnKisDataGet) (T,x,y,p,plen);
//************************************************
  return 0;
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr1 = WOWGetVDMPointer32(p,1);
  DWORD dwLinAddr2 = WOWGetVDMPointer32(plen,1);
  KisRetcode RetVal = WOWCallProc32(lpfnKisDataGet,0,5,T,x,y,dwLinAddr1,dwLinAddr2);
  GlobalUnfix(WBase::hInstance);
  return RetVal;
#endif
  }

KisRetcode KisDataSet(KisTable T, long x, long y, LPSTR p, long len)
  {
#ifdef WIN32
  KisRetcode RetVal = (*lpfnKisDataSet)(T,x,y,p,len);
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr = WOWGetVDMPointer32(p,1);
  KisRetcode RetVal = WOWCallProc32(lpfnKisDataSet,0,5,T,x,y,dwLinAddr,len);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisConvBcdToMac(LPSTR sBcd, LPSTR sMac)
  {
#ifdef WIN32
  KisRetcode RetVal = (*lpfnKisConvBcdToMac)(sBcd,sMac);
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr1 = WOWGetVDMPointer32(sBcd,1);
  DWORD dwLinAddr2 = WOWGetVDMPointer32(sMac,1);
  KisRetcode RetVal = WOWCallProc32(lpfnKisConvBcdToMac,0,2,dwLinAddr1,dwLinAddr2);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisConvMacToBcd(LPSTR sMac, LPSTR sBcd)
  {
#ifdef WIN32
  KisRetcode RetVal = (*lpfnKisConvMacToBcd)(sMac,sBcd);
#else
  GlobalFix(WBase::hInstance);
  DWORD dwLinAddr1 = WOWGetVDMPointer32(sMac,1);
  DWORD dwLinAddr2 = WOWGetVDMPointer32(sBcd,1);
  KisRetcode RetVal = WOWCallProc32(lpfnKisConvMacToBcd,0,2,dwLinAddr1,dwLinAddr2);
  GlobalUnfix(WBase::hInstance);
#endif
  return RetVal;
  }

KisRetcode KisError()
  {
#ifdef WIN32
  return 0;
#else
  return WOWCallProc32(lpfnKisError,0,0);
#endif
  }


// Script-Funktionen:

struct KisInit_param {
  WORD parSize;
  DWORD Token;
  };

BOOL KisInit (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisInit_param FAR *par = (KisInit_param FAR *) param;
    LPSTR Token = (LPSTR)c->ReadlData(par->Token);
    if ((Token != NULL) && (*Token != '\0'))
      res = (KisInit(Token) == KisRetSUCCESS);
    }
  return res;
  }

struct KisExit_param {
  WORD parSize;
  };

BOOL KisExit (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisExit_param FAR *par = (KisExit_param FAR *) param;
    res = (KisExit() == KisRetSUCCESS);
    }
  return res;
  }

struct KisSelectionOpen_param {
  WORD parSize;
  DWORD Selection;
  DWORD Token;
  };

BOOL KisSelectionOpen (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisSelectionOpen_param FAR *par = (KisSelectionOpen_param FAR *) param;
    LPSTR Token = (LPSTR)c->ReadlData(par->Token);
    if ((Token != NULL) && (*Token != '\0')) {
      KisSelection Selection = KisSelectionOpen(Token);
      c->WritelData(par->Selection,&Selection,sizeof(KisSelection),LPSTR(param)-sizeof(WORD));
      res = (Selection != NULL);
      }
    }
  return res;
  }

struct KisSelectionClose_param {
  WORD parSize;
  DWORD Selection;
  };

BOOL KisSelectionClose (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisSelectionClose_param FAR *par = (KisSelectionClose_param FAR *) param;
    KisSelection FAR *Selection = (KisSelection FAR *)c->ReadlData(par->Selection);
    if ((Selection != NULL) && (*Selection != NULL))
      res = (KisSelectionClose(*Selection) == KisRetSUCCESS);
    }
  return res;
  }

struct KisRecordRead_param {
  WORD parSize;
  DWORD Record;
  DWORD Selection;
  };

BOOL KisRecordRead (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisRecordRead_param FAR *par = (KisRecordRead_param FAR *) param;
    KisSelection FAR *Selection = (KisSelection FAR *)c->ReadlData(par->Selection);
    if ((Selection != NULL) && (*Selection != NULL)) {
      KisRecord Record = KisRecordRead(*Selection);
      c->WritelData(par->Record,&Record,sizeof(KisRecord),LPSTR(param)-sizeof(WORD));
      res = (Record != NULL);
      }
    }
  return res;
  }

struct KisRecordCreate_param {
  WORD parSize;
  DWORD Record;
  DWORD Token;
  };

BOOL KisRecordCreate (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisRecordCreate_param FAR *par = (KisRecordCreate_param FAR *) param;
    LPSTR Token = (LPSTR)c->ReadlData(par->Token);
    if ((Token != NULL) && (*Token != '\0')) {
      KisRecord Record = KisRecordCreate(Token);
      c->WritelData(par->Record,&Record,sizeof(KisRecord),LPSTR(param)-sizeof(WORD));
      res = (Record != NULL);
      }
    }
  return res;
  }

struct KisRecordWrite_param {
  WORD parSize;
  DWORD Record;
  };

BOOL KisRecordWrite (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisRecordWrite_param FAR *par = (KisRecordWrite_param FAR *) param;
    KisRecord FAR *Record = (KisRecord FAR *)c->ReadlData(par->Record);
    if ((Record != NULL) && (*Record != NULL))
      res = (KisRecordWrite(*Record) == KisRetSUCCESS);
    }
  return res;
  }

struct KisRecordFree_param {
  WORD parSize;
  DWORD Record;
  };

BOOL KisRecordFree (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisRecordFree_param FAR *par = (KisRecordFree_param FAR *) param;
    KisRecord FAR *Record = (KisRecord FAR *)c->ReadlData(par->Record);
    if ((Record != NULL) && (*Record != NULL))
      res = (KisRecordFree(*Record) == KisRetSUCCESS);
    }
  return res;
  }

struct KisTableOpen_param {
  WORD parSize;
  DWORD Table;
  DWORD Record;
  DWORD Token;
  };

BOOL KisTableOpen (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisTableOpen_param FAR *par = (KisTableOpen_param FAR *) param;
    LPSTR Token = (LPSTR)c->ReadlData(par->Token);
    KisRecord FAR *Record = (KisRecord FAR *)c->ReadlData(par->Record);
    if ((Token != NULL) && (*Token != '\0') &&
        (Record != NULL) && (*Record != NULL)) {
      KisTable Table = KisTableOpen(*Record,Token);
      c->WritelData(par->Table,&Table,sizeof(KisTable),LPSTR(param)-sizeof(WORD));
      res = (Table != NULL);
      }
    }
  return res;
  }

struct KisTableClose_param {
  WORD parSize;
  DWORD Table;
  };

BOOL KisTableClose (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisTableClose_param FAR *par = (KisTableClose_param FAR *) param;
    KisTable FAR *Table = (KisTable FAR *)c->ReadlData(par->Table);
    if ((Table != NULL) && (*Table != NULL))
      res = (KisTableClose(*Table) == KisRetSUCCESS);
    }
  return res;
  }

struct KisDataGet_param {
  WORD parSize;
  DWORD Data;
  DWORD Table;
  DWORD x;
  DWORD y;
  DWORD DataLen;
  };

BOOL KisDataGet (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisDataGet_param FAR *par = (KisDataGet_param FAR *) param;
    KisTable FAR *Table = (KisTable FAR *)c->ReadlData(par->Table);
    long FAR *x = (long FAR *)c->ReadlData(par->x);
    long FAR *y = (long FAR *)c->ReadlData(par->y);
    long DataLen = 256;
    if (par->parSize >= sizeof(*par)) {
      long FAR *lpDataLen = (long FAR *)c->ReadlData(par->DataLen);
      if (lpDataLen != NULL)
        DataLen = *lpDataLen;
      }
    if ((Table != NULL) && (*Table != NULL) &&
        (x != NULL) && (y != NULL) && (DataLen > 0)) {
      LPSTR Data = (LPSTR)GetGlobMem((int)DataLen);
      res = (KisDataGet(*Table,*x,*y,Data,&DataLen) == KisRetSUCCESS);
      if (res && (DataLen > 0)) {
        c->WritelData(par->Data,Data,(int)DataLen,LPSTR(param)-sizeof(WORD));
        }
      else {
        c->DellData(par->Data,LPSTR(param)-sizeof(WORD));
        DataLen = 0L;
        }
      if (par->parSize >= sizeof(*par))
        c->WritelData(par->DataLen,&DataLen,sizeof(long),LPSTR(param)-sizeof(WORD));
      FreeGlobMem(Data);
      }
    }
  return res;
  }

struct KisDataSet_param {
  WORD parSize;
  DWORD Table;
  DWORD x;
  DWORD y;
  DWORD Data;
  };

BOOL KisDataSet (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisDataSet_param FAR *par = (KisDataSet_param FAR *) param;
    KisTable FAR *Table = (KisTable FAR *)c->ReadlData(par->Table);
    long FAR *x = (long FAR *)c->ReadlData(par->x);
    long FAR *y = (long FAR *)c->ReadlData(par->y);
    if ((Table != NULL) && (*Table != NULL) &&
        (x != NULL) && (y != NULL)) {
      LPSTR Data = (LPSTR)c->ReadlData(par->Data);
      if (Data != NULL) {
        res = (KisDataSet(*Table,*x,*y,Data,GetBlockSize(Data)) == KisRetSUCCESS);
        }
      else {
        static char dummy[1];
        *dummy = '\0';
        res = (KisDataSet(*Table,*x,*y,dummy,0L) == KisRetSUCCESS);
        }
      }
    }
  return res;
  }

#define MAXBCDSIZE 30
#define MAXMACSIZE 30

struct KisConvBcdToMac_param {
  WORD parSize;
  DWORD Bcd;
  DWORD Mac;
  };

BOOL KisConvBcdToMac (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisConvBcdToMac_param FAR *par = (KisConvBcdToMac_param FAR *) param;
    LPSTR lpBcd = (LPSTR)c->ReadlData(par->Bcd);
    if ((lpBcd != NULL) && (*lpBcd != '\0')) {
      LPSTR lpMac = (LPSTR)GetGlobMem(MAXMACSIZE);
      res = (KisConvBcdToMac(lpBcd,lpMac) == KisRetSUCCESS);
      if (res) {
        c->WritelData(par->Mac,lpMac,lstrlen(lpMac)+1,LPSTR(param)-sizeof(WORD));
        }
      else {
        c->DellData(par->Mac,LPSTR(param)-sizeof(WORD));
        }
      FreeGlobMem(lpMac);
      }
    }
  return res;
  }

struct KisConvMacToBcd_param {
  WORD parSize;
  DWORD Bcd;
  DWORD Mac;
  };

BOOL KisConvMacToBcd (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisConvMacToBcd_param FAR *par = (KisConvMacToBcd_param FAR *) param;
    LPSTR lpMac = (LPSTR)c->ReadlData(par->Mac);
    if ((lpMac != NULL) && (*lpMac != '\0')) {
      LPSTR lpBcd = (LPSTR)GetGlobMem(MAXBCDSIZE);
      res = (KisConvMacToBcd(lpMac,lpBcd) == KisRetSUCCESS);
      if (res) {
        c->WritelData(par->Bcd,lpBcd,lstrlen(lpBcd)+1,LPSTR(param)-sizeof(WORD));
        }
      else {
        c->DellData(par->Bcd,LPSTR(param)-sizeof(WORD));
        }
      FreeGlobMem(lpBcd);
      }
    }
  return res;
  }


struct KisError_param {
  WORD parSize;
  DWORD Retcode;
  };

BOOL KisError (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    KisError_param FAR *par = (KisError_param FAR *) param;
    KisRetcode Retcode = KisError();
    c->WritelData(par->Retcode,&Retcode,sizeof(KisRetcode),LPSTR(param)-sizeof(WORD));
    res = (Retcode == KisRetSUCCESS);
    }
  return res;
  }

