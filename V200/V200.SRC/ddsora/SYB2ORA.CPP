/*****************************************************************************
 FILE:              OCIPORT.C
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           MedORA - Oracle - Anbindung an das Clinicum (Medica, Steinmaur)
 PRODUCT:           DDSORA.DLL
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    F. Loeliger
 
 DATE:              14.02.1996
 
 DESCRIPTION:       additional porting routines 
                    
 
 ENVIRONMENT:       Windows Application
                    MS Visual C++ V1.50
                    Oracle Call Interface, Release 7.1
                    MKS - RCS is used for the revision controlling
                    
 VERSION:           0.9 15.03.96 first freezed version (beta released)   
                    0.1 The DLL is manually ported from the sybase DLL Rev 1.3
 
 STATUS:            beta released
 
 MODIFIED:          
   23.02.96 FL  debug output added
   14.02.96 FL  created
   
*****************************************************************************/


#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

extern "C" {
  #include <oratypes.h>
  #include <ocidfn.h>       // LDA and CDA struct declarations
  #include <ociapr.h>
  #include "ocicons.h"
} 
#include "dds32.h" // FL 26.03.96 adapted to version v122
#include "syb2ora.hpp"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"

#define MODULENUM 910
#include "winass.hpp"

extern LPSTR WINAPI GetIniName ();

#ifdef _DEBUG
#define DBG_ENABLED       1          // enables the functionality of dbglog
#endif

// #define DBG_LOGFILENAME   "dbg.log"  // all debug output is written to this file
#ifdef UEBERLEGT
extern DLLExport LPSTR _export WINAPI makeIni (LPSTR name);
#define DBG_LOGFILENAME   makeIni ("dbg.log")
#endif
extern DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name);
#define DBG_LOGFILENAME GetStationLogFile ("dbg.log")
/*
 *  OCI function code labels,
 *  corresponding to the fc numbers
 *  in the cursor data area.
 */
static CONST text  *oci_func_tab[] =  {(text *) "not used",
/* 1-2 */       (text *) "not used", (text *) "OSQL",
/* 3-4 */       (text *) "not used", (text *) "OEXEC, OEXN",
/* 5-6 */       (text *) "not used", (text *) "OBIND",
/* 7-8 */       (text *) "not used", (text *) "ODEFIN",
/* 9-10 */      (text *) "not used", (text *) "ODSRBN",
/* 11-12 */     (text *) "not used", (text *) "OFETCH, OFEN",
/* 13-14 */     (text *) "not used", (text *) "OOPEN",
/* 15-16 */     (text *) "not used", (text *) "OCLOSE",
/* 17-18 */     (text *) "not used", (text *) "not used",
/* 19-20 */     (text *) "not used", (text *) "not used",
/* 21-22 */     (text *) "not used", (text *) "ODSC",
/* 23-24 */     (text *) "not used", (text *) "ONAME",
/* 25-26 */     (text *) "not used", (text *) "OSQL3",
/* 27-28 */     (text *) "not used", (text *) "OBNDRV",
/* 29-30 */     (text *) "not used", (text *) "OBNDRN",
/* 31-32 */     (text *) "not used", (text *) "not used",
/* 33-34 */     (text *) "not used", (text *) "OOPT",
/* 35-36 */     (text *) "not used", (text *) "not used",
/* 37-38 */     (text *) "not used", (text *) "not used",
/* 39-40 */     (text *) "not used", (text *) "not used",
/* 41-42 */     (text *) "not used", (text *) "not used",
/* 43-44 */     (text *) "not used", (text *) "not used",
/* 45-46 */     (text *) "not used", (text *) "not used",
/* 47-48 */     (text *) "not used", (text *) "not used",
/* 49-50 */     (text *) "not used", (text *) "not used",
/* 51-52 */     (text *) "not used", (text *) "OCAN",
/* 53-54 */     (text *) "not used", (text *) "OPARSE",
/* 55-56 */     (text *) "not used", (text *) "OEXFET",
/* 57-58 */     (text *) "not used", (text *) "OFLNG",
/* 59-60 */     (text *) "not used", (text *) "ODESCR",
/* 61-62 */     (text *) "not used", (text *) "OBNDRA"
};


/************************************************************************
  ociretmap

  purpose:  maps the returncodes of oracle oci functions to the sybase
            ct_ - function return codes.
  input:    retcode    oci - returncode
  output:   --
  return:   CS_xxx     the mapped CS_ - returncode
*************************************************************************/
  CS_RETCODE ociretmap(const sword retcode)  
  {
    return ( (CS_RETCODE)retcode );
  } // ociretmap
  

/************************************************************************
  ocierr_report

  purpose:  reports the oci error in a readable form
            the following return codes of OCI are handled differently:
            OCI_SUCCESS              no handling at all
            OCI_WRN_NO_DATA_FOUND    no handling, hanlding is done by caller
  input:    cursor     the structur describing the error
  output:   --
  return:   --
*************************************************************************/
  void ocierr_report(const Lda_Def *lda, const Cda_Def *cursor)
  {
    sword n;
    text msg1[512], msg[512]; 

    n = oerhms((Lda_Def*)lda, (sb2)cursor->rc, msg1, (sword) sizeof(msg1));
#ifdef ALTE_VERSION
    sprintf((char *)msg, "OCI <%s> ret=%d<%s>", 
                          (char *)oci_func_tab[cursor->fc], (int)cursor->rc, msg1);

    // DBG_ASSERT_TEXT(FALSE,"ocierr_report", (char*)msg);               // ### FL wieder entfernen
    DBGFORCE_ASSERT_TEXT(FALSE,"ocierr_report", (char*)msg);               // ### FL wieder entfernen
#endif
    sprintf((char *)msg, "OCI <%s> ret = %d", 
            (char *)oci_func_tab[cursor->fc], (int)cursor->rc);
    DBGFORCE_ASSERT_TEXT(FALSE,(char *)msg, (char*)msg1);
  } // ocierr_report

/************************************************************************
  ocirethandling

  purpose:  handles the oci return code in an appropriate way (display errors)
            and returns the appropriate CS_xxx value for that return code.
            If an error occured, then an appropriate message will be
            generated.                                             
  input:    lda        the connection information (local data area)
            cda        the cursor data area (contatins the return code information)
  output:   --
  return:   CS_FAIL    there has been an error
            CS_SUCCEED everything ok
            
*************************************************************************/

static int lastORAError = 0;
static char lastErrMsg[256];
CS_RETCODE ocirethandling(const Lda_Def *lda, const Cda_Def *cda)  
  {
  CS_RETCODE retcode;
  
  BOOL doLast = FALSE;
  if ( (cda->rc != OCI_SUCCESS) &&          
       (cda->rc != OCI_WRN_SEQ_NOT_YET_DEFINED) &&
       (cda->rc != OCI_WRN_NO_DATA_FOUND) &&
       (!IsToIgnore (cda->rc,&doLast)) ) {
    lastORAError = cda->rc;
    ocierr_report(lda, cda);
    lastORAError = 0;
    retcode = CS_FAIL;
    } // if
  else {   
    if (doLast)
      oerhms ((Lda_Def *)lda, (sb2)cda->rc, (unsigned char *)lastErrMsg, (sword) sizeof(lastErrMsg));
    retcode = CS_SUCCEED;
    } // if  
  
  return ( retcode );
  } // ocirethandling
  

/************************************************************************
  dbglog

  purpose:  writes the debuginformation to the File dbg.log
  input:    ModuleNr   the number of the module calling this routine
            LineNr     the line of the module calling this routin
            FileName   the File calling this routine
            text1      the first part of the text
            text2      the second part of the text to write into logfile
  output:   --
  return:   --
            
*************************************************************************/
  void dbglog(const int ModuleNr, const int LineNr, const char *FileName, const char *text1, const char *text2)
  {
#if defined(DBG_ENABLED)
  dbglog_force(ModuleNr, LineNr, FileName, text1, text2);
#endif    
  } // dbglog           

static DWORD  lastmsec = 0;

/************************************************************************
  dbglog_starttimer

  purpose:  starts statement execution timer
  input:    --
  output:   --
  return:   --

*************************************************************************/
  void dbglog_starttimer(void)
  {
    lastmsec = GetTickCount();
  } // dbglog_starttimer

extern DLLExport LPSTR _export WINAPI GetErrorContext (void);

/************************************************************************
  dbglog_force

  purpose:  writes the debuginformation to the File dbg.log
  input:    ModuleNr   the number of the module calling this routine
            LineNr     the line of the module calling this routin
            FileName   the File calling this routine
            text1      the first part of the text
            text2      the second part of the text to write into logfile
  output:   --
  return:   --
*************************************************************************/

extern LPSTR ActCmdBuf;
extern LPSTR GetParamString();

BOOL IsWordChar(char ch)
  {
  if ((ch >= 'A') && (ch <= 'Z')) return TRUE;
  if ((ch >= 'a') && (ch <= 'z')) return TRUE;
  if ((ch >= '0') && (ch <= '9')) return TRUE;
  if ((ch == '.') || (ch == '_')) return TRUE;
  return FALSE;
  }

void dbglog_force(const int ModuleNr, const int LineNr, const char *FileName, const char *text1, const char *text2)
  {
  static FILE   *logfile = NULL;
  static time_t lasttimer = (time_t)0;
  time_t timer, dtimer;
  int len, retval;
  SYSTEMTIME st;

  DWORD  msec, dmsec;

  if (logfile == NULL) {
    logfile = fopen(DBG_LOGFILENAME, "a+c"); // append and write to disk with the fflush function
    } // if

  if (logfile != NULL) {
    time(&timer);
    if (lasttimer == 0)
      dtimer = 0;
    else
      dtimer = timer - lasttimer;
    lasttimer = timer;
    GetLocalTime(&st);

    msec = GetTickCount();
    if ((lastmsec == 0) || (msec < lastmsec))
      dmsec = 0;
    else
      dmsec = msec - lastmsec;
    lastmsec = msec;

    retval = 0; len = 0;
    if ( (strncmp(text1, "RESULT", 6) == 0 ) ) {
      if ( (strncmp(text1, "RESULT END", 10) == 0 ) )
        retval = fprintf(logfile, "\n");
      else
        retval = fprintf(logfile, "%s", text2);
      } // if
    else {
      /* ---- bisheriges Format: ----
07.12.98 10:47:18 (d=000):[00000] 0073532500104BB54A7A Module:910 Line:142 : ocierr_report 
  <OCI <OEXFET> ret=904<ORA-00904: invalid column name
>                                               >
07.12.98 10:47:18 (d=000):[00000] 0073532500104BB54A7A Module:912 Line:2440 : Error on following command 
  <SELECT t0.Nummer,t0.Klasse,t0.Bezeichnung FROM AuftragBDefinition t0 WHERE (KlassenVersion = :I1 AND>
  < AuftragBDefinition = :I2)                                                                          >
      ---- Ende bisheriges Format ---- */
#ifdef ALTE_VERSION
      fprintf(logfile, "%02.2d.%02.2d.%02.2d %02.2d:%02.2d:%02.2d (d=%3.3d):",
                        ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year,
                        ltm->tm_hour, ltm->tm_min, ltm->tm_sec, (int)dtimer);
      fprintf(logfile, "[%05lu]", dmsec);
      LPSTR ErrorContext = GetErrorContext();
      if (ErrorContext != NULL)
        fprintf(logfile, " %s", ErrorContext);
      retval = fprintf(logfile, " Module:%d Line:%d : %s \n", ModuleNr, LineNr, text1);
      while ((retval >= 0) && (len < (int)strlen(text2))) {
        if (strncmp(text1, "SQL", 3) == 0) {
          retval = fprintf(logfile, "\t%-100.100s\n", &text2[len]);
          }
        else {
          retval = fprintf(logfile, "\t<%-100.100s>\n", &text2[len]);
          } // if

        if ( (strlen(text2) - len) > 100)
          len += 100;
        else
          len = strlen(text2);
        } // while
#endif
      fprintf(logfile, "%02.2d.%02.2d.%02.2d %02.2d:%02.2d:%02.2d (%d ms) -",
                        st.wDay, st.wMonth, st.wYear,
                        st.wHour, st.wMinute, st.wSecond, (int)dtimer);
      LPSTR ErrorContext = GetErrorContext();
      if (ErrorContext != NULL)
        fprintf(logfile, " %s -", ErrorContext);
      fprintf(logfile, " %s\n", text1);
      fprintf(logfile, "%s", text2);
      if (ActCmdBuf != NULL) {
        fprintf(logfile, "statement:\n");
        while (lstrlen(ActCmdBuf) > 60) {
          char EineZeile[100];
          for (int i = 0; (i < 60) || (IsWordChar(*ActCmdBuf)); i++)
            EineZeile[i] = *ActCmdBuf++;
          EineZeile[i] = '\0';
          fprintf(logfile, "%s\n", EineZeile);
          }
        if (lstrlen(ActCmdBuf) > 0)
          fprintf(logfile, "%s\n", ActCmdBuf);
        LPSTR ActParameters = GetParamString();
        if (ActParameters != NULL) {
          fprintf(logfile, "parameters: %s\n", ActParameters);
          FreeGlobMem(ActParameters);
          }
        }
      fprintf(logfile, "\n", text2);
      } // else if
    fclose(logfile);
    logfile = NULL;
    } // if

  BOOL MitRosaSchirm = TRUE;
  if (lastORAError != 0) {
    static BOOL FirstTime = TRUE;
    static int NumErrorsToSupress;
    static int ErrorToSupress[100];
    if (FirstTime) {
      char buf[1024];
      GetPrivateProfileString ("Oracle","IgnoreError", "", buf, sizeof(buf),GetIniName());
      char *ch = buf;
      BOOL minus = FALSE;
      while (*ch != '\0') {
        if (*ch == '-') {
          ch++;
          minus = TRUE;
          }
        else if ((*ch >= '0') && (*ch <= '9')) {
          int err = *ch++ - '0';
          while ((*ch >= '0') && (*ch <= '9'))
            err = (err * 10) + (*ch++ - '0');
          if (minus) {
            err = -err;
            minus = FALSE;
            }
          ErrorToSupress[NumErrorsToSupress++] = err;
          }
        else {
          ch++;
          minus = FALSE;
          }
        }
      FirstTime = FALSE ;
      }
    if (NumErrorsToSupress > 0) {
      for (int i = 0; i < NumErrorsToSupress; i++)
        if (ErrorToSupress[i] == lastORAError)
          MitRosaSchirm = FALSE;
      }
    }

  if (MitRosaSchirm) {
    char RosaSchirm[1000];
    sprintf(RosaSchirm,"ORACLE-Fehler %s(Genauere Informationen wurden in der Datei \"dbg.log\" protokolliert.)",text2);
    WIN_ASSERT_TEXT(FALSE,RosaSchirm);
    }
  } // dbglog_force

struct errToIgnore {
  errToIgnore FAR *Next;
  int errnr;
  };

static struct errToIgnore FAR *eri;
void PushErrToIgnore (int errnr)
  {
  errToIgnore FAR *h = (errToIgnore FAR *) GetGlobMem (sizeof(*h));
  h->Next = eri ;
  eri = h ;
  h->errnr = errnr ;
  }

void FreeErrToIgnore ()
  {
  for ( ; eri != NULL ; ) {
    errToIgnore FAR *h = eri->Next;
    FreeGlobMem (eri);
    eri = h;
    }
  }


static int LastIgnoredErrorCode;
BOOL IsToIgnore (int errnr,BOOL *doLast)
  {
  LastIgnoredErrorCode = 0;
  *doLast = FALSE;
  for (errToIgnore FAR *h = eri ; h != NULL ; h = h->Next) {
    if ((h->errnr == errnr) || ((h->errnr < 0) && (errnr > 20000))) {
      if (errnr > 20000) *doLast = TRUE;
      LastIgnoredErrorCode = errnr;
      return TRUE ;
      }
    }
  return FALSE ;
  }

void PopErrToIgnore (int errnr)
  {
  errToIgnore FAR *prev = NULL ;
  for (errToIgnore FAR *h = eri ; h != NULL ; h = h->Next) {
    if (h->errnr == errnr) {
      if (prev != NULL) prev->Next = h->Next ;
      else              eri = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    else
      prev = h;
    }
  }

static struct {
  int ErrType ;
  int RetCode ;
  } errmap [] = {
  { ERRTYPE_OBJEXISTS , 955 } ,
  { ERRTYPE_DUPLICATEKEY , 1 } ,
  { ERRTYPE_OBJNOTEXISTS , 942 } ,
  { ERRTYPE_NOPRIVILEGS , 1031 }
  } ;

int GetErrMap (int ErrType)
  {
  for (int i = 0 ; i < sizeof(errmap) / sizeof(errmap[0]) ; i++)
    if (ErrType == errmap[i].ErrType) return errmap[i].RetCode ;
  return OCI_SUCCESS ;
  }

BOOL IgnoreOracleError(int errnr,BOOL State)
  {
  BOOL res;
  BOOL dummy;
  if (State) {
    if (!(res = IsToIgnore (errnr,&dummy)))
      PushErrToIgnore (errnr);
    }
  else {
    PopErrToIgnore (errnr);
    res = FALSE ;
    }
  return res;
  }

DLLExport BOOL _export FAR PASCAL DBIgnoreError (int ErrType,BOOL State)
  {
  int errnr;
  if (ErrType > 10000)
    errnr = ErrType - 10000;
  else if (ErrType < 0)
    errnr = ErrType;
  else
    errnr = GetErrMap (ErrType);
  return IgnoreOracleError(errnr,State);
  }

DLLExport int _export FAR PASCAL GetDBLastError ()
  {
  for (int i = 0 ; i < sizeof(errmap) / sizeof(errmap[0]) ; i++)
    if (LastIgnoredErrorCode == errmap[i].RetCode) return errmap[i].ErrType ;
  return LastIgnoredErrorCode;
  }

DLLExport LPSTR _export FAR PASCAL GetDBLastErrorText ()
  {
  return lastErrMsg;
  }
