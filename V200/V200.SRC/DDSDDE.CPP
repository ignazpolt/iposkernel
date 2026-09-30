////////////////////////////////////////////////////////////////////////////
//  Clinicum relevanter DDE - Code (benoetigt stddde.cpp)
////////////////////////////////////////////////////////////////////////////
//    $Header:   P:/marille/clinicum/rev/ddsdde.cpv   1.19   02 Jul 1998 11:06:32   Hannes  $
//    $Log:   P:/marille/clinicum/rev/ddsdde.cpv  $
// 
//    Rev 1.19   02 Jul 1998 11:06:32   Hannes
// Handling Zeitversetztes Destroy
// 
//    Rev 1.18   16 Jan 1998 12:30:06   Martin
// InClientTransaction bei allen DDE-Befehlen setzen
// 
//    Rev 1.17   29 Jul 1997 09:51:08   Martin
// DDE_SetTimeOut
// 
//    Rev 1.16   26 May 1997 18:00:26   Hannes
// 
//    Rev 1.15   18 Sep 1996 20:46:40   HANNES
// Erweiterung der Textinterpretierung
// 
//    Rev 1.14   04 Jul 1996 15:00:08   GERHOLD
// Format des DDE ist nun einstellbar
// 
//    Rev 1.13   10 Jun 1996 10:06:58   GERHOLD
// pragma pack
// 
//    Rev 1.12   04 Mar 1996 21:10:18   GERHOLD
// (LPSTR) GlobalLock  ... type cast
// 
//    Rev 1.11   24 Feb 1996 16:07:10   MARTIN
// Speicherfresser raus
// 
//    Rev 1.10   07 Feb 1996 11:12:00   MARTIN
// PostMessage erste nach ClientTrans.
// 
//    Rev 1.9   05 Feb 1996 18:55:46   MARTIN
// CallCommand innerhalb DDE verhindert
// 
//    Rev 1.8   02 Feb 1996 10:36:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   16 Sep 1995 02:05:52   HANNES
// 
//    Rev 1.6   24 Aug 1995 00:20:10   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   31 Jul 1995 20:14:56   GERHOLD
// 
//    Rev 1.4   31 Jul 1995 11:49:54   GERHOLD
// besseres Fehler-Handling bei DDE-Client-Funktionen
// 
//    Rev 1.3   14 Jul 1995 13:33:46   GERHOLD
// DDE-Client-Funktionen
// 
//    Rev 1.2   22 Mar 1995 15:27:54   GERHOLD
// 
//    Rev 1.1   19 Nov 1994 21:08:36   HANNES
// DDEServer mit gleichen Items wie in der Kopfzeile
// 
//    Rev 1.0   19 Nov 1994 19:24:26   GERHOLD
// Initial revision.
////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ddeml.h>
#include "dds32.h"
#include "stddde.h"
#include "globmem.h"
#include "dds.hpp"
#include "ddsmsg.h"

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

#define MODULENUM 155
#include "winass.hpp"


#define SZ_SERVICENAME  "CLINICUM"   // service name
DWORD dwDDEInst = 0;                // DDE Instance value

#define SZ_INFO         "Info"      // topic name
#define SZ_TEST         "Test"     // item name

WORD MyFormats[] = {                // Format list
                    CF_TEXT,
                    NULL
                   };


//----------------------------------------------------------------------------
// Return a string in CF_TEXT format
//----------------------------------------------------------------------------
HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem)
  {
  if (wFmt != CF_TEXT) return NULL;

#ifdef WIN32
  return DdeCreateDataHandle(dwDDEInst, LPBYTE(lpszStr), lstrlen(lpszStr)+1, 0, hszItem, CF_TEXT, NULL);
#else
  return DdeCreateDataHandle(dwDDEInst, lpszStr, lstrlen(lpszStr)+1, 0, hszItem, CF_TEXT, NULL);
#endif
  }

//----------------------------------------------------------------------------
// Return the Help info
//----------------------------------------------------------------------------
#define REQ_STARTED   0
#define WAITONFINISH  1
static BOOL State = REQ_STARTED;
static LPVOID LastData ;
HDDEDATA InfoRequest (UINT wFmt, HSZ hszTopic, HSZ hszItem)
  {
  switch (State) {
    case REQ_STARTED :
      {
      PDDETOPICINFO t = FindTopicFromHsz (hszTopic);
      PDDEITEMINFO i = FindItemFromHsz (t,hszItem);
      LastData = NULL ;
      int fldlen;
      BOOL flgRes;
      GetKW(i->pszItemName,&fldlen,&flgRes) ;
      if (LastData == NULL) {
        State = WAITONFINISH ;
        return CBR_BLOCK ;
        }
      else {
        HDDEDATA res = MakeCFText(wFmt, LPSTR(LastData), hszItem);
        FreeGlobMem (LastData);
        return res ;
        }
      }
    case WAITONFINISH :
      {
      HDDEDATA res = MakeCFText(wFmt, LPSTR(LastData), hszItem);
      FreeGlobMem (LastData);
      State = REQ_STARTED ;
      return res ;
      break ;
      }
    default :
      return NULL ;
    }
  }

#pragma pack(1)
struct PresentData_param {
  WORD parSize;
  DWORD dataToPresent;
  };
#pragma pack()
void ReestblishConnection ();
BOOL PresentData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PresentData_param FAR *par = (PresentData_param FAR *) param;
    LPVOID res = c->ReadlData (par->dataToPresent);
    LastData = GetGlobMem (GetBlockSize(res));
    lmemcpy (LastData,res,GetBlockSize(res));
    if (State == WAITONFINISH)
      ReestblishConnection ();
    }
  return FALSE ;
  }

HDDEDATA EndRequest (UINT wFmt, HSZ hszTopic, HSZ hszItem)
  {
  PDDETOPICINFO t = FindTopicFromHsz (hszTopic);
  PDDEITEMINFO i = FindItemFromHsz (t,hszItem);
  MessageBox (GetActiveWindow(), "InfoRequest", "DDE", MB_OK);
  int fldlen;
  BOOL flgRes;
  return MakeCFText(wFmt, GetKW(i->pszItemName,&fldlen,&flgRes), hszItem);
  }

void SetupDDE(HINSTANCE hInstance)
  {
  // Do the basic initialization
  InitializeDDE(hInstance, SZ_SERVICENAME, &dwDDEInst, NULL, 0);
  }

void AddDDEItem (LPSTR Item)
  {
  AddDDEItem(SZ_INFO, Item, MyFormats, InfoRequest, NULL);
  }

void RemoveDDEItem (LPSTR Item)
  {
  RemoveDDEItem(SZ_INFO, Item);
  }



//---------------------------------------------------------------------------
//
// Implementation des CLINICUMS als Client 
//
//---------------------------------------------------------------------------
DWORD    idInst = 0;
HCONV    hConv = 0;
FARPROC  lpDDEProc = NULL;
UINT     uError;
BOOL     InClientTransaction = FALSE;
BOOL     CallCommandInClientTransaction = FALSE;

DWORD TIME_OUT = 3000L;

HDDEDATA CALLBACK DDE_ClientCallback(UINT type, UINT fmt, 
                              HCONV hconv, 
                              HSZ hsz1, HSZ hsz2, 
                              HDDEDATA hData, 
                              DWORD dwData1,
                              DWORD dwData2);


extern LPSTR FAR PASCAL GetIniName ();
#ifndef MYINI
  #define MYINI GetIniName ()
#endif
static BOOL NoCallCommandInClientTransaction(void)
  {
  static BOOL NCCICT;
  static BOOL FirstTime = TRUE;
  if (FirstTime) {
    char checkstr[10];
    GetPrivateProfileString ("STGKK","UpdateInDDE","",
                                checkstr,sizeof(checkstr),
                                MYINI
                            );
    if (lstrcmp(checkstr,"yes"))
      NCCICT = TRUE;
    else
      NCCICT = FALSE;
    FirstTime = FALSE;
    }
  return NCCICT;
  }


#pragma pack(1)
struct ddeinitiate_param {
  WORD  parSize;
  DWORD szServer;       // In:  DDE-Name des Servers z.B. "WinWord", "Excel",...
  DWORD szTopic;        // In:  z.B. "System"
  DWORD ChanNum;        // Out: Nummer des DDE-Kanals
  DWORD ErrorCode;      // Out: FehlerCode
  };
#pragma pack()

extern void deleteAllOpenChilds ();
BOOL DDE_Initiate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = NoCallCommandInClientTransaction();
    ddeinitiate_param FAR *par = (ddeinitiate_param FAR *) param;

    lpDDEProc = MakeProcInstance ((FARPROC)DDE_ClientCallback, WBase::hInstance);

    // Anmelden fuer eine DDE-Verbindung
    uError = DdeInitialize (&idInst, (PFNCALLBACK)lpDDEProc, 0, 0L);
    
    // Server und Topic aus den Script-Parametern ermitteln
    LPSTR szServer = (LPSTR)c->ReadlData (par->szServer);
    LPSTR szTopic  = (LPSTR)c->ReadlData (par->szTopic);

    if ((uError == DMLERR_NO_ERROR) && idInst) {
      if (!(szServer && *szServer && szTopic && *szTopic)) {
        char szErr[256];
        lstrcpy (szErr, "Fehler beim Aufbau der DDE-Verbindung");
        if (szServer && *szServer) {
          lstrcat (szErr, "\r\nDDE-Server: ");
          lstrcat (szErr, szServer);
          }
        if (szTopic && *szTopic) {
          lstrcat (szErr, "\r\nDDE-Topic: ");
          lstrcat (szErr, szTopic);
          }
        DBWIN_ASSERT_TEXT (FALSE, szErr);
        }

      HSZ hszService = DdeCreateStringHandle (idInst, szServer, CP_WINANSI);
      HSZ hszTopic  = DdeCreateStringHandle (idInst, szTopic, CP_WINANSI);

      DBWIN_ASSERT ((hszService != NULL) && (hszTopic != NULL));
  
      // Verbindung zum Server herstellen
      hConv = DdeConnect (idInst, hszService, hszTopic, NULL);

      if (hConv == NULL) {
        uError = DdeGetLastError(idInst);
        }
        
      DdeFreeStringHandle (idInst, hszService);
      DdeFreeStringHandle (idInst, hszTopic);
    
      // den Instanzen-Bezeichner zurueckgeben
      c->WritelData (par->ChanNum, &idInst, sizeof(idInst), LPSTR(param)-sizeof(WORD));
      }
    
    // den Fehler-Code zurueckgeben
    c->WritelData (par->ErrorCode, &uError, sizeof(uError), LPSTR(param)-sizeof(WORD));

    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    deleteAllOpenChilds ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ddeinitiate_param FAR *par = (ddeinitiate_param FAR *) param;
    c->ClearlConnection (par->szServer,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->szTopic,LPSTR(param)-sizeof(WORD));
    }
  
  return FALSE;
  }
  

#pragma pack(1)
struct ddeterminate_param {
  WORD  parSize;
  DWORD ChanNum;      // In: Nummer des DDE-Kanals
  };
#pragma pack()
  
BOOL DDE_Terminate (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = NoCallCommandInClientTransaction();
    ddeterminate_param FAR *par = (ddeterminate_param FAR *) param;

    DWORD FAR* ChanNum = (DWORD FAR *)c->ReadlData (par->ChanNum);
    DBWIN_ASSERT (ChanNum != NULL);
    
    if (ChanNum && *ChanNum) {
      DdeDisconnect (hConv);
  
      DdeUninitialize (*ChanNum);
      }

    FreeProcInstance (lpDDEProc);

    idInst = 0;
    c->WritelData (par->ChanNum, &idInst, sizeof(idInst), LPSTR(param)-sizeof(WORD));

    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    deleteAllOpenChilds ();
    }
    
  return FALSE;
  }

#pragma pack(1)
struct dderequest_param {
  WORD  parSize;
  DWORD ChanNum;      // In:  Nummer des DDE-Kanals
  DWORD szItem;       // In:  Item, der vom Topic unterstuetzt wird
  DWORD szResult;     // Out: Ergebnis der Anfrage an den Server
  DWORD DDEFormat;    // In:  CF_TEXT, ....
  };
#pragma pack()

BOOL DDE_Request (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = NoCallCommandInClientTransaction();
    dderequest_param FAR *par = (dderequest_param FAR *) param;

    DWORD FAR* ChanNum = (DWORD FAR *)c->ReadlData (par->ChanNum);
    DBWIN_ASSERT (ChanNum != NULL);
    
    LPSTR szItem = (LPSTR)c->ReadlData (par->szItem);

    if (ChanNum && *ChanNum) {
      DBWIN_ASSERT (szItem && *szItem);
      
      HSZ hszItem = DdeCreateStringHandle (*ChanNum, szItem, CP_WINANSI);

      if (hszItem) {
        //-----------------------------------------------
        // optionaler Parameter: gibt das Datenformat an
        //-----------------------------------------------
        UINT DDEFormat = CF_TEXT;
        if (par->parSize >= sizeof(*par)) {
          UINT FAR *lpDDEFormat = (UINT FAR *)c->ReadlData (par->DDEFormat);
          if ((lpDDEFormat != NULL) && *lpDDEFormat)
            DDEFormat = *lpDDEFormat;
          }

        HDDEDATA hData = DdeClientTransaction (
                              NULL,         // keine Daten an den Server
                              0,            // wird ignoriert, wenn erster Parameter = NULL
                              hConv,        // Konversations-Handle
                              hszItem,      // Stringhandle des Themenpunktes
                              DDEFormat,    // Kennung des Datenformats
                              XTYP_REQUEST, // Transaktionsart
                              TIME_OUT,
                              NULL);        // Transaktions-Resultate ohne Bedeutung
        
        uError = DdeGetLastError (*ChanNum);  // die Fehlernummer speichern
        
        DdeFreeStringHandle (*ChanNum, hszItem);
  
        if (hData != NULL) {
          DWORD dwLen;
        
          DdeAccessData (hData, &dwLen);
#ifdef WER_HAT_DAS_VERBROCHEN
          LPSTR lpBuf = LPSTR(GlobalLock(GlobalAlloc(GHND, dwLen)));   // Grrrmtjfx !
#endif
          HGLOBAL hBuffer = GlobalAlloc(GHND, dwLen);
          LPSTR lpBuf = LPSTR(GlobalLock(hBuffer));
#ifdef WIN32
          DdeGetData (hData, LPBYTE(lpBuf), dwLen, 0);
#else
          DdeGetData (hData, lpBuf, dwLen, 0);
#endif
          
          // das Ergebnis der Abfrage speichern
          int buflen;
          if (DDEFormat == CF_TEXT)
            buflen = lstrlen(lpBuf) + 1;
          else
            buflen = int(dwLen);

          c->WritelData (par->szResult, lpBuf, buflen, LPSTR(param)-sizeof(WORD));
          
          // wie waers mit wieder freigeben !?!?
          GlobalUnlock(hBuffer);
          GlobalFree(hBuffer);

          DdeUnaccessData (hData);
          DdeFreeDataHandle (hData);
          }
        }
      else
        uError = DdeGetLastError (*ChanNum);  // die Fehlernummer speichern
      }
    else {
      // wenn gar nichts da ist, dann wenigstens einen Leerstring zurueckgeben!
      LPSTR lpBuf = LPSTR(GetGlobMem (1));
      *lpBuf = '\0';
      c->WritelData (par->szResult, lpBuf, lstrlen(lpBuf)+1, LPSTR(param)-sizeof(WORD));
      FreeGlobMem (lpBuf);
      }
    
    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    deleteAllOpenChilds ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    dderequest_param FAR *par = (dderequest_param FAR *) param;
    c->ClearlConnection (par->szItem,LPSTR(param)-sizeof(WORD));
    }
    
  return FALSE;  
  }


#pragma pack(1)
struct ddepoke_param {
  WORD  parSize;
  DWORD ChanNum;      // In:  Nummer des DDE-Kanals
  DWORD szItem;       // In:  Item, der vom Topic unterstuetzt wird
  DWORD szData;       // In:  Daten die ins das Item geschrieben werden (String!!)
  DWORD DDEFormat;
  };
#pragma pack()

BOOL DDE_Poke (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = NoCallCommandInClientTransaction();
    ddepoke_param FAR *par = (ddepoke_param FAR *) param;

    DWORD FAR* ChanNum = (DWORD FAR *)c->ReadlData (par->ChanNum);
    DBWIN_ASSERT (ChanNum != NULL);
    
    LPSTR szItem = (LPSTR)c->ReadlData (par->szItem);
    HSZ hszItem = DdeCreateStringHandle (*ChanNum, szItem, CP_WINANSI);

    if (ChanNum && *ChanNum) {

      UINT DDEFormat = CF_TEXT;
      if (par->parSize >= sizeof(*par)) {
        UINT FAR *lpDDEFormat = (UINT FAR *)c->ReadlData (par->DDEFormat);
        if ((lpDDEFormat != NULL) && *lpDDEFormat)
          DDEFormat = *lpDDEFormat;
        }

      int datalen;
      LPVOID szData = c->ReadlData (par->szData);
      if (DDEFormat == CF_TEXT)
        datalen = lstrlen (LPSTR(szData)) + 1;
      else
        datalen = GetBlockSize (szData);

      HDDEDATA hDdeData = DdeCreateDataHandle (
                              *ChanNum,
                              NULL,
                              0,
                              datalen,
                              hszItem,
                              DDEFormat,
                              0);

      LPSTR lpData = (LPSTR)DdeAccessData (hDdeData, NULL);

      if (DDEFormat = CF_TEXT)
        lstrcpy (lpData, LPSTR(szData));
      else
        lmemcpy (lpData, szData, datalen);

      DdeUnaccessData (hDdeData);

#ifdef WIN32      
      HDDEDATA hData = DdeClientTransaction (
                            LPBYTE(hDdeData),     // Daten fuer den Server
                            DWORD(-1),
                            hConv,        // Konversations-Handle
                            hszItem,      // Stringhandle des Themenpunktes
                            DDEFormat,    // Kennung des Datenformats
                            XTYP_POKE,    // Transaktionsart
                            TIME_OUT,
                            NULL);        // Transaktions-Resultate ohne Bedeutung
#else
      HDDEDATA hData = DdeClientTransaction (
                            LPVOID(hDdeData),     // Daten fuer den Server
                            DWORD(-1),
                            hConv,        // Konversations-Handle
                            hszItem,      // Stringhandle des Themenpunktes
                            DDEFormat,    // Kennung des Datenformats
                            XTYP_POKE,    // Transaktionsart
                            TIME_OUT,
                            NULL);        // Transaktions-Resultate ohne Bedeutung
#endif

      uError = DdeGetLastError (*ChanNum);  // die Fehlernummer speichern

      DdeFreeStringHandle (*ChanNum, hszItem);
      }

    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    deleteAllOpenChilds ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ddepoke_param FAR *par = (ddepoke_param FAR *) param;
    c->ClearlConnection (par->szItem,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->szData,LPSTR(param)-sizeof(WORD));
    }
    
  return FALSE;  
  }


#pragma pack(1)
struct ddeexecute_param {
  WORD  parSize;
  DWORD ChanNum;      // In:  Nummer des DDE-Kanals
  DWORD szCommand;    // In:  Statement oder Funktion im Server
  };
#pragma pack()

BOOL DDE_Execute (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InClientTransaction = NoCallCommandInClientTransaction();
    ddeexecute_param FAR *par = (ddeexecute_param FAR *) param;

    DWORD FAR* ChanNum = (DWORD FAR *)c->ReadlData (par->ChanNum);
    DBWIN_ASSERT (ChanNum != NULL);
    
    LPSTR szCommand = (LPSTR)c->ReadlData (par->szCommand);

    if (ChanNum && *ChanNum) {

      HDDEDATA hDdeData = DdeCreateDataHandle (
                              *ChanNum,
                              NULL,
                              0,
                              lstrlen(szCommand) + 1,
                              NULL,
                              CF_TEXT,
                              0);


      LPSTR lpData = (LPSTR)DdeAccessData (hDdeData, NULL);
      lstrcpy (lpData, szCommand);
      DdeUnaccessData (hDdeData);

#ifdef WIN32
      HDDEDATA hData = DdeClientTransaction (
                            LPBYTE(hDdeData),     // Daten fuer den Server
                            DWORD(-1),
                            hConv,        // Konversations-Handle
                            NULL,         // kein Stringhandle bei XTYP_EXECUTE
                            CF_TEXT,      // Kennung des Datenformats
                            XTYP_EXECUTE, // Transaktionsart
                            TIME_OUT,
                            NULL);        // Transaktions-Resultate ohne Bedeutung
#else
      HDDEDATA hData = DdeClientTransaction (
                            LPVOID(hDdeData),     // Daten fuer den Server
                            DWORD(-1),
                            hConv,        // Konversations-Handle
                            NULL,         // kein Stringhandle bei XTYP_EXECUTE
                            CF_TEXT,      // Kennung des Datenformats
                            XTYP_EXECUTE, // Transaktionsart
                            TIME_OUT,
                            NULL);        // Transaktions-Resultate ohne Bedeutung
#endif

      uError = DdeGetLastError (*ChanNum);  // die Fehlernummer speichern
      }

    InClientTransaction = FALSE;
    if (CallCommandInClientTransaction) {
      PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
      CallCommandInClientTransaction = FALSE;
      }
    deleteAllOpenChilds ();
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ddeexecute_param FAR *par = (ddeexecute_param FAR *) param;
    c->ClearlConnection (par->szCommand,LPSTR(param)-sizeof(WORD));
    }
    
  return FALSE;  
  }


#pragma pack(1)
struct ddelasterror_param {
  WORD  parSize;
  DWORD ChanNum;      // In:  Nummer des DDE-Kanals
  DWORD ErrorNum;     // Out: FehlerNummer des letzten DDE-Fehlers
  };
#pragma pack()

BOOL DDE_GetLastError (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ddelasterror_param FAR *par = (ddelasterror_param FAR *) param;

    DWORD FAR* ChanNum = (DWORD FAR *)c->ReadlData (par->ChanNum);
    DBWIN_ASSERT (ChanNum != NULL);
    
    DWORD lastError;
    if (ChanNum && *ChanNum)
      lastError = (DWORD)uError;
    else
      lastError = (DWORD)1;   // das ist keine DMLERR_xxxxx - Fehlernummer!!!
      
    c->WritelData (par->ErrorNum, &lastError, sizeof(lastError), LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

HDDEDATA CALLBACK DDE_ClientCallback(UINT type, UINT fmt, 
                              HCONV hconv, 
                              HSZ hsz1, HSZ hsz2, 
                              HDDEDATA hData, 
                              DWORD dwData1,
                              DWORD dwData2)
  {
  return (HDDEDATA)NULL;
  }

#pragma pack(1)
struct ddesettimeout_param {
  WORD  parSize;
  DWORD TimeOut;      // In:  Timeout in Millisekunden
  };
#pragma pack()

BOOL DDE_SetTimeOut (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ddesettimeout_param FAR *par = (ddesettimeout_param FAR *) param;

    DWORD FAR* TimeOut = (DWORD FAR *)c->ReadlData (par->TimeOut);
    if (TimeOut != NULL)
      TIME_OUT = *TimeOut;
    else
      TIME_OUT = 3000L;
    }

  return FALSE;
  }

