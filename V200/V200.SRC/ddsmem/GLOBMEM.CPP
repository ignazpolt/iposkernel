// $Header:   P:/marille/clinicum/ddsmem/rev/globmem.cpv   1.69   27 Jun 2000 18:38:34   Martin  $
// $Log:   P:/marille/clinicum/ddsmem/rev/globmem.cpv  $
// 
//    Rev 1.69   27 Jun 2000 18:38:34   Martin
// Ltx()
// 
//    Rev 1.68   29 May 2000 22:17:28   Martin
// SplitScreenX/Y
// 
//    Rev 1.67   18 Feb 2000 19:33:52   Martin
// Doppelmonitor
// 
//    Rev 1.66   12 Jan 2000 21:19:52   Martin
// OpenMed2
// 
//    Rev 1.65   14 Sep 1999 20:07:44   Martin
// [ErrorHandling] / LogPath=... eingebaut
// 
//    Rev 1.64   18 Aug 1999 18:48:08   Martin
// %-Variablen-Aufloesung fuer ORBIS
// 
//    Rev 1.63   12 Aug 1999 16:39:00   Martin
// OpenMed statt ClinicSoftware
// 
//    Rev 1.62   13 Jul 1999 12:30:10   Martin
// falls dmw.ini exisiert, diese nehmen
// 
//    Rev 1.61   29 Jun 1999 19:16:20   Martin
// floydst dynamisch laden (von dort wo dmw.ini liegt)
// 
//    Rev 1.60   14 May 1999 15:31:40   Gerhold
// Der Funktionspointer htmlHelp wird nur aufgerufen, wenn er != NULL ist.
// 
//    Rev 1.59   31 Mar 1999 14:57:02   Gerhold
// htmlhelp
// 
//    Rev 1.58   05 Oct 1998 11:10:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.57   07 Sep 1998 09:07:54   Hannes
// MyLPtoDP
// 
//    Rev 1.56   01 Sep 1998 23:48:12   Hannes
// MyLPtoDP
// 
//    Rev 1.55   13 Jun 1998 17:26:24   Martin
// ExePath
// 
//    Rev 1.54   16 May 1998 18:35:00   Martin
// Stacktrace verbessert
// 
//    Rev 1.53   30 Mar 1998 20:20:52   Martin
// Add-/RemoveProfileOverrideBuffer
// 
//    Rev 1.52   03 Mar 1998 20:06:54   Martin
// True Color
// 
//    Rev 1.51   03 Feb 1998 09:34:06   Hannes
// 
//    Rev 1.50   05 Dec 1997 17:48:06   Martin
// FreeLinMem exportiert
// 
//    Rev 1.49   17 Nov 1997 18:11:58   Martin
// Programm braucht jetzt wieder etwas weniger Speicher ...
// 
//    Rev 1.48   10 Nov 1997 10:49:42   Hannes
// FIFO in LIFO umgebaut zwecks beschleunigung
// 
//    Rev 1.47   21 Aug 1997 15:45:52   Martin
// ... und nocheinmal fuer die DEBUG-Variante ...
// 
//    Rev 1.46   21 Aug 1997 15:16:14   Martin
// wieder mal den Offset von ExCuteBlock im Stacktrace angepasst ...
// 
//    Rev 1.45   24 Jul 1997 11:10:30   Martin
// nanu ? (_this hat sich in der OPT-Variante geaendert !?!?)
// 
//    Rev 1.44   14 Jul 1997 19:37:20   Martin
// 3.Teil
// 
//    Rev 1.43   14 Jul 1997 19:23:14   Martin
// 2.Teil
// 
//    Rev 1.42   14 Jul 1997 15:35:30   Martin
// OPT-32-StackTrace 1.Teil
// 
//    Rev 1.41   14 Jul 1997 12:28:24   Martin
// ... auch bei win_ass_failed_text
// 
//    Rev 1.40   14 Jul 1997 12:16:40   Martin
// Exceptionhandling ...
// 
//    Rev 1.39   23 May 1997 11:13:08   Martin
// Exception (32): Scriptname auch bei CallCommand
// 
//    Rev 1.38   20 May 1997 17:28:52   Martin
// 32-Bit-Exception-Handling (Luxusvariante mit Scriptnamen)
// 
//    Rev 1.37   05 May 1997 16:49:40   Hannes
// 
//    Rev 1.36   30 Apr 1997 11:00:08   Hannes
// 
//    Rev 1.35   30 Apr 1997 10:10:38   Hannes
// 
//    Rev 1.34   30 Apr 1997 09:42:52   Hannes
// Alle Allocs per define auf Globalalloc umgestellt
// 
//    Rev 1.33   08 Apr 1997 17:43:56   gerhold
// SetHelpFile, GetHelpFile
// 
//    Rev 1.32   08 Apr 1997 07:52:18   Hannes
// Verschiedene kleine Verbesserungen, damit auch die Statistiken besser
// funktionieren
// 
//    Rev 1.31   13 Jan 1997 11:18:34   MARTIN
// retries auf jeden Fall erhoehen, egal welcher Fehlercode
// 
//    Rev 1.30   12 Dec 1996 19:14:54   MARTIN
// StationLogPath, "innerhalb Fehlerbehandlung"
// 
//    Rev 1.29   26 Nov 1996 08:01:30   HANNES
// Memcheck auch fuer Globalhandles
// 
//    Rev 1.28   24 Sep 1996 18:56:26   GERHOLD
// DWORD HelpContextNr, SetHelpContextNr, GetHelpContextNr
// 
//    Rev 1.27   19 Aug 1996 12:39:26   MARTIN
// faults.log ins selbe Verzeichnis wie INI-files
// 
//    Rev 1.26   28 Jun 1996 18:51:00   MARTIN
// [ErrorHandling] -> AutoAbortTime
// 
//    Rev 1.25   17 Jun 1996 15:48:22   HANNES
// Kleine Verbesserungen
// 
//    Rev 1.24   05 Mar 1996 13:17:42   MARTIN
// MyGetPrivateProfileString korrigiert
// 
//    Rev 1.23   04 Mar 1996 20:49:10   GERHOLD
// Speicherverwaltung geht jetzt endlich unter 16 Bit
// 
//    Rev 1.21   22 Feb 1996 19:20:28   MARTIN
// fault.log schreiben mit retry ...
// 
//    Rev 1.20   16 Feb 1996 15:14:30   GERHOLD
// 
//    Rev 1.19   05 Feb 1996 19:22:44   MARTIN
// SetErrorContextStr
// 
//    Rev 1.18   04 Feb 1996 15:25:26   GERHOLD
// No change.
// 
//    Rev 1.17   02 Feb 1996 10:41:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.15   17 Jan 1996 09:04:18   HANNES
// 
//    Rev 1.14   02 Jan 1996 22:14:00   HANNES
// Absicherung von LogMsg
// 
//    Rev 1.13   24 Aug 1995 00:13:34   HANNES
// 
//    Rev 1.12   14 Jun 1995 13:06:58   HANNES
// PushGetPtr, PushFreePtr, ToggleWrite exportiert
// 
//    Rev 1.11   09 Jun 1995 00:23:32   MARTIN
// Cursorhandling fuer Updates, die von Tastatureingaben ausgehen...
// 
//    Rev 1.10   11 May 1995 17:59:38   HANNES
// 
//    Rev 1.9   24 Apr 1995 11:55:12   HANNES
// No change.
// 
//    Rev 1.8   24 Mar 1995 18:34:58   GERHOLD
// 
//    Rev 1.7   23 Mar 1995 11:49:36   GERHOLD
// SetStartDir
// 
//    Rev 1.6   19 Dec 1994 08:13:50   GERHOLD
// Cursor Gschichterln.
// 
//    Rev 1.5   15 Dec 1994 18:21:48   HANNES
// UnregisterWindow
// 
//    Rev 1.4   08 Dec 1994 22:07:40   GERHOLD
// _export an alle FAR PASCAL Funktionen
// 
//    Rev 1.3   07 Nov 1994 11:26:58   HANNES
// Directoryhandling fuer die Inifiles
// 
//    Rev 1.2   17 Aug 1994 09:27:32   HANNES
// Beim FreeGlobMem Inhalt auf NULL initialisiert
// 
//    Rev 1.1   04 Jul 1994 11:22:02   HANNES
// lstrncpy Definitionsgemaess verwenden
// 
//    Rev 1.0   24 Jun 1994 16:37:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.22   28 Feb 1994 16:00:52   HANNES
// 
//    Rev 1.21   23 Feb 1994 18:07:10   HANNES
// Verbesserte Statistiken
// 
//    Rev 1.20   22 Feb 1994 15:28:16   HANNES
// WriteSizeStat erweitert und exportiert
// 
//    Rev 1.19   25 Jan 1994 18:11:36   HANNES
// LogMsg exportiert
// 
//    Rev 1.18   18 Jan 1994 11:03:26   HANNES
// 
//    Rev 1.17   16 Jan 1994 19:02:44   HANNES
// Verbessert Hintergrundfarbe, Fehler auf Datei mitschreiben
// 
//    Rev 1.16   21 Nov 1993 22:55:48   MARTIN
// 
//    Rev 1.15   03 Nov 1993 16:10:38   MARTIN
// Sanduhr - Funktionen
// 
//    Rev 1.14   19 Oct 1993 10:24:08   HANNES
// Statische Variable fuer den WinAssert
// 
//    Rev 1.13   11 Oct 1993 11:42:26   HANNES
// win_assert erweitert..
// 
//    Rev 1.12   27 Sep 1993 18:27:20   HANNES
// Verbesserte Win - Assert
// 
//    Rev 1.11   05 Sep 1993 22:06:40   HANNES
// 
//    Rev 1.10   17 Aug 1993 11:50:16   MARTIN
// WIN_ASSERT
// 
//    Rev 1.9   05 Aug 1993 13:10:58   MARTIN
// GetCRC
// 
//    Rev 1.8   11 Jun 1993 09:44:52   HANNES
// GetIniName
// 
//    Rev 1.7   10 May 1993 12:53:14   HANNES
// Exception in FreeFault eingebaut
// 
//    Rev 1.6   18 Apr 1993 22:31:34   HANNES
// Test der Speicherfreigaben..
// 
//    Rev 1.5   05 Apr 1993 10:36:58   HANNES
// Check einbauen
// 
//    Rev 1.4   02 Apr 1993 18:08:10   HANNES
// Beschleunigung, globale Speicherverwaltung
// 
//    Rev 1.3   22 Feb 1993 17:28:54   HANNES
// lstrncpy
// 
//    Rev 1.2   13 Dec 1992 19:57:02   HANNES
// Umstellen der Logik zur Elementgroessenbestimmung (spart ein Byte und ist
// geringfuegig schneller)
// 
//    Rev 1.1   13 Dec 1992 19:52:18   HANNES
// Umbau der Funktionen auf LocalAlloc, LocalFree mit Aufbau von verschiedenen
// Heaps (LocalInit)
// 
//    Rev 1.0   02 Dec 1992 16:16:22   HANNES
// Initial revision.
/*****************************************************************/
/* Funktionen fuer die Speicherverwaltung mit Gloabl...          */
/*****************************************************************/
#include <windows.h>

#ifdef WIN32
  #include "imagehlp.h"
#else
  #include <toolhelp.h>
#endif

#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <direct.h>

#define GLOBALCHECK_MAIN
#include "dds32.h"
#include "globmem.h"
#define MODULENUM   39
#include "winass.hpp"
#include <time.h>
#include "lisencr.hpp"

#define JUST_EM 1
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

// nur fuer VirtFunctionCall:
#include "hash.hpp"
#define WITHOUT_GETININAME 1
#include "compile.hpp"

// #define STATISTICS
// #define JUSTUSEGLOBAL
// #define TESTMEM
// #define TESTGALLOC

extern LONG javaReferences; // JMODEL.CPP

DLLExport BOOL _export WINAPI lmemcmp (LPCVOID p1,LPCVOID p2,WORD count)
  {
#ifdef WIN32
  for ( WORD i = 0 ; i < count ; i++) {
    if (LPSTR(p1)[i] != LPSTR(p2)[i]) return FALSE ;
    }
  return TRUE ;
#else
  BOOL res;
  __asm {
   les DI,p2
   lds SI,p1
    mov cx,count
   xor ax,ax
   repe cmpsb   ;compare string
   jne L3   ;strings are equal
      mov res,1
      jmp L4
L3:
    mov res,0
L4:
    }
  return res;
#endif
  }

DLLExport void _export WINAPI lstrncpy (LPSTR p1,LPCSTR p2,WORD count)
  {
  for ( ; ((count >= 1) && (*p2)) ; count --)
    *p1++ = *p2++ ;
  if (count >= 1)
    *p1++ = '\0' ;
  }

static char ExePath[256];
DLLExport void _export WINAPI SetExePath (LPSTR dirname)
  {
  lstrcpy(ExePath,dirname);
  }

DLLExport LPSTR _export WINAPI GetExePath (void)
  {
  return ExePath;
  }

static BOOL JustForDebug = FALSE;
DLLExport void _export WINAPI SetJustForDebug (void)
  {
  JustForDebug = TRUE;
  }

static BOOL IchBinDasRestool = FALSE;
DLLExport void _export WINAPI SetIchBinDasRestool (void)
  {
  IchBinDasRestool = TRUE;
  }

static LPSTR ErrorContext = NULL;
static int first_time = TRUE;
static char StartPath[256];

DLLExport LPSTR _export WINAPI GetErrorContext (void)
  {
  return ErrorContext;
  }

DLLExport LPSTR _export WINAPI makeIni (LPSTR name)
  {
  static char IniName[256];

  if (first_time) {
    lstrcpy(StartPath, GetExePath());
    first_time = FALSE;
    }
  int len = lstrlen(StartPath);
  lstrcpy (IniName,StartPath);
  if (IniName[len - 1] != '\\')
    IniName[len++] = '\\';
  if (JustForDebug && (lstrcmpi(name,"dbbtrv.ini") == 0)) {
    lstrcpy(IniName, GetExePath());
    int len = lstrlen(IniName);
    if (IniName[len - 1] != '\\')
      IniName[len++] = '\\';
    lstrcpy(IniName + len, name);
    }
  else
    lstrcpy(IniName + len, name);
  return IniName;
  }

DLLExport LPSTR _export WINAPI GetIniName ()
  {
  return makeIni ("dmw.ini");
  }

#define MYINI GetIniName ()

static int slo_first_time = TRUE;
static char StationLogName[256];
static BOOL UseMakeIni = TRUE;
static int LogPathLen = 0;

DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name)
  {
  if (first_time) {
    lstrcpy(StartPath, GetExePath());
    first_time = FALSE;
    }
  if (slo_first_time) {
    GetPrivateProfileString ("ErrorHandling","StationLogPath","",StationLogName,100,MYINI);
    if (StationLogName[0] != '\0') {
      int len = lstrlen(StationLogName);
      if (StationLogName[len - 1] != '\\')
        StationLogName[len++] = '\\';
      int ErrorContextLen;
      if (ErrorContext != NULL)
        ErrorContextLen = lstrlen(ErrorContext);
      else
        ErrorContextLen = 0;
      if (ErrorContextLen > 0) {
        if (ErrorContextLen > 8)   // die letzten 8 Zeichen nehmen
          lstrcpy(StationLogName + len, ErrorContext + (ErrorContextLen - 8));
        else
          lstrcpy(StationLogName + len, ErrorContext);
        lstrcat(StationLogName,".LOG");
        }
      else
        lstrcpy(StationLogName + len, "UNKNOWN.LOG");
      UseMakeIni = FALSE;
      }
    else {
      GetPrivateProfileString ("ErrorHandling","LogPath","",StationLogName,100,MYINI);
      if (StationLogName[0] != '\0') {
        int len = lstrlen(StationLogName);
        if (StationLogName[len - 1] != '\\')
          StationLogName[len++] = '\\';
        LogPathLen = len;
        UseMakeIni = FALSE;
        }
      }
    slo_first_time = FALSE;
    }
  if (UseMakeIni) {
    return makeIni(name);
    }
  else {
    if (LogPathLen > 0)
      lstrcpy(StationLogName + LogPathLen, name);
    return StationLogName;
    }
  }

// Hilfsfunktionen fuer Speicherfressersuche:
struct GlobalCheckList {
  struct GlobalCheckList FAR *next;
  DWORD key;
  DWORD CheckNumber;
  DWORD size;
  WORD type;
  };
typedef GlobalCheckList FAR *LPGCL;
#define GCL_TYPE_GLOBALALLOC  0
#define GCL_TYPE_GETGLOBMEM   1
#define GCL_TYPE_GETGLOBALMEM 2

static LPGCL gcl = NULL;
static DWORD ActGlobalCheck = 0;
static DWORD ActFreeCheck = 0;

static BOOL sclongint (LPSTR txt, DWORD FAR *i)
  {
  double f = 0;

  *i = 0;
  BOOL error = (*txt == '\0') ;
  BOOL signFound = FALSE ;
  LONG sign = 1L ;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt == '-') && (!signFound) && (*i == 0))
      sign = -1L , signFound = TRUE ;
    else if ((*txt == '+') && (!signFound) && (*i == 0))
      sign = +1L , signFound = TRUE ;
    else if ((*txt >= '0') && (*txt <= '9')) {
//      *i = *i * 10L + LONG(*txt - '0') ;

      double lastnum = f;
      
      f = f * 10 + double(int(*txt - '0'));
      
      if (f > 2147483647.0) {
        f = lastnum;
        MessageBeep (0);
        error = TRUE;
        break;
        }
      }
    else
      error = TRUE ;
    }

  if (error) {
    *i = 0xFFFFFFFF;
    }
  else {
    *i = long(f);
    *i *= sign ;
    }
  return !error;
  }

static DWORD GetCheckBreak(void)
  {
  DWORD res;
  char str[21];
  GetPrivateProfileString ("Profile","CheckBreak","",str,20,MYINI);
  sclongint(str,&res);
  return res;
  }

static void AddToGlobalCheckList(DWORD key,DWORD size,WORD type)
  {
  static DWORD CheckBreak = GetCheckBreak();
  if (CheckBreak != 0xFFFFFFFF) {
    if (ActGlobalCheck == CheckBreak) {
      int a = 1;
      int b = 0;
      int c = a / b;
      }
    }
  LPGCL newgcl = (LPGCL)GetGlobMem(sizeof(GlobalCheckList));
  newgcl->key = key;
  newgcl->CheckNumber = ActGlobalCheck;
  newgcl->size = size;
  newgcl->type = type;
  newgcl->next = gcl;
  gcl = newgcl;
  ActGlobalCheck++;
  }

static void RemoveFromGlobalCheckList(DWORD key)
  {
  LPGCL prev = NULL;
  LPGCL hgcl = gcl;
  while (hgcl != NULL) {
    LPGCL next = hgcl->next;
    if (hgcl->key == key) {
      if (prev == NULL)
        gcl = next;
      else
        prev->next = next;
      FreeGlobMem(hgcl);
      ActFreeCheck++;
      return;
      }
    else
      prev = hgcl;
    hgcl = next;
    }
  WIN_ASSERT_TEXT(FALSE,"ungueltige Speicherfreigabe !");
  }

/*--------< Anforderung von Speicher >-----------*/
/*-----------------------------------------------*/
DLLExport LPVOID _export WINAPI GetGlobalMem (GLOBALHANDLE FAR *hGmem,WORD FAR *Offs,WORD Size)
  {
#ifndef WIN32
  LPSTR Base;
  if (*hGmem == 0) {
    *hGmem = GlobalAlloc (GHND,0xFFFF);
    Base = LPSTR (GlobalLock (*hGmem));
    LocalInit (FP_SEG(Base),sizeof(WORD),0xFF00);
    }
  else
    Base = GlobalLock (*hGmem);

  WORD actseg = FP_SEG(Base);
  __asm {
    push ds
    mov ds ,actseg
    }
  WORD Offset = LocalAlloc (LPTR,Size+sizeof(WORD));
  __asm {
    pop ds
    }
  if (Offset) {
    LPSTR res = Base + Offset;
    (*(WORD FAR *) res) = Size ;
    (*(WORD FAR *) Base)++;
    *Offs = Offset + sizeof(WORD);
    return res + sizeof(WORD);
    }
  else 
#endif
    return NULL;
  }

// GetBlockSize fuer 32-bit
DLLExport DWORD _export WINAPI GetBlockSize32 (LPVOID Ptr)
  {
  if (Ptr != NULL)
    return ((DWORD FAR *) Ptr)[-1] ;
  else
    return 0;
  }
  
DLLExport WORD _export WINAPI GetBlockSize (LPVOID Ptr)
  {
  if (Ptr != NULL)
    return ((WORD FAR *) Ptr)[-1] ;
  else
    return 0;
  }

// verwendet noch die 16-bit Speicherverwaltung, fuer gespeicherte Strukturen etc. noch gebraucht
DLLExport WORD _export WINAPI GetBlockSize16 (LPVOID Ptr)
  {
  if (Ptr != NULL)
    return ((WORD FAR *) Ptr)[-1] ;
  else
    return 0;
  }
  
DLLExport void _export WINAPI FreeGlobalMem (LPVOID Ptr,GLOBALHANDLE FAR *hGmem)
  {
#ifndef WIN32
  if (Ptr != NULL) {
    WORD ActSeg = FP_SEG (Ptr);
    __asm {
      push ds
      mov ds,ActSeg
      }

    for ( ; LocalFree (FP_OFF(Ptr) - sizeof(WORD)) ; ) ;

    __asm {
      pop ds
      }
    LPSTR Base;
    FP_SEG(Base) = ActSeg;
    FP_OFF(Base) = 0;
    if (-- (*(WORD FAR *) Base) == 0) {
      for ( ; GlobalFree (*hGmem) ; ) ;
      *hGmem = 0;
      }
    }
#endif
  }


DLLExport WORD _export WINAPI OffsetToGlobMem(LPVOID Ptr,GLOBALHANDLE hGmem)
  {
#ifndef WIN32
  return FP_OFF (Ptr);
#else
  return 0 ;
#endif
  }


//////////////////////////////////////////////////////////////////////////
//
//    Vollkommen frei vergabe von Segmenten
//
//////////////////////////////////////////////////////////////////////////
struct _SegHandle {
  GLOBALHANDLE hGmem;
  LPVOID _First;
  _SegHandle FAR *Next;
  WORD size;
  };
typedef _SegHandle FAR *LPSEGHANDLE;

static GLOBALHANDLE SegMem;
static LPSEGHANDLE FirstSegHandle;


static LPSEGHANDLE GetSeg (LPVOID Ptr)
  {
  for (LPSEGHANDLE h = FirstSegHandle ; h != NULL ; h = h->Next) {
    LPSTR Base = LPSTR(GlobalLock(h->hGmem));
    if ((DWORD(Ptr) >= DWORD(Base)) && (DWORD(Ptr) < DWORD(Base) + GlobalSize(h->hGmem))) break ;
    }
  return h;
  }

inline LPVOID TryInThisSeg (LPSEGHANDLE h,WORD size)
  {
  WORD Offset;
  if (size >= h->size) return NULL;
  LPVOID res = GetGlobalMem (&h->hGmem,&Offset,size);
  if (res == NULL) {
    h->size = size;
    }
  return res;
  }

static LPVOID InitializeNewSeg (WORD size)
  {
  WORD Offs1,Offs2;
  LPSEGHANDLE h = LPSEGHANDLE (GetGlobalMem (&SegMem,&Offs1,sizeof(*h)));
  h->Next = FirstSegHandle;
  FirstSegHandle = h;
  LPVOID res = GetGlobalMem (&h->hGmem,&Offs2,size);
  h->_First = res;
  h->size = 0xFFFF;
  return res;
  }

static void DelSegEntry (LPSEGHANDLE d)
  {
  LPSEGHANDLE prev = NULL ;
  for (LPSEGHANDLE h = FirstSegHandle ; h != NULL ; h = h->Next) {
    if (h == d) {
      if (prev != NULL) 
        prev->Next = d->Next ;
      else
        FirstSegHandle = d->Next ;
      FreeGlobalMem (h,&SegMem);
      break ;
      }
    prev = h ;
    }
  }

#define MAXSIZE 1024
struct MemStat {
  DWORD AnzAnf;
  DWORD ActAnzAnf;
  DWORD MaxAnzAnf;
  BYTE type;
  } MemAnf[MAXSIZE];

//-------------------------  SetStartDir  -----------------------------------
//
// Setzt das Verzeichnis in dem die Ini-Dateien fuer das Programm stehen.
// (Wird aufgerufen wenn das Programm mit Cmdline-Parameter gestartet wird)
//---------------------------------------------------------------------------
static BOOL WithStartDir = FALSE;
DLLExport LPSTR _export WINAPI SetStartDir (LPSTR dirname, LPSTR IniFile)
  {
  if ((dirname != NULL) && (IniFile != NULL)) {
    lstrcpy (StartPath, dirname);
    WithStartDir = TRUE;

    static char IniName[140];
    int len = strlen(StartPath);

    lstrcpy (IniName, StartPath);
    if (IniName[len - 1] != '\\')
      IniName[len++] = '\\';
    lstrcpy(IniName + len, IniFile);  

    OFSTRUCT Of;
    HFILE f = OpenFile (IniName, &Of, OF_EXIST);  // gibts eine INI-Datei?
    if (f != HFILE_ERROR)
      first_time = FALSE;
    else {
      char szBuf[256];
      wsprintf (szBuf, "%s ist kein g�ltiges INI-Verzeichnis", StartPath);
      WIN_ASSERT_TEXT (FALSE, szBuf);
      }
    return StartPath;
    }
  else
    return NULL;
  }

// Zeiger auf Fileschreiben fuer Testzwecke
///////////////////////////////////////////////////
static DWORD fcount;
static DWORD gcount;
static HFILE ofile = -1;
void PushMLine (LPSTR txt)
  {
  if (ofile < 0) {
    OFSTRUCT Of;
    ofile = OpenFile ("allocs.txt",&Of,OF_WRITE | OF_CREATE);
    }
  _hwrite (ofile,txt,lstrlen(txt));
  }

void Closeaf ()
  {
  _lclose (ofile);
  }

static DWORD GlobalGesamt = 0L;
void PushGSize(DWORD cbAlloc)
  {
  char SizeStr[20];
  GlobalGesamt += cbAlloc;
//  wsprintf(SizeStr,"%ld\r\n",cbAlloc);
  wsprintf(SizeStr,"+%ld=%ld\r\n",cbAlloc,GlobalGesamt);
  PushMLine(SizeStr);
#ifdef UEBERLEGT
  if (GlobalGesamt > 2700000L) {
    int a = 1;
    int b = 0;
    int c = a / b;
    }
#endif
  }

static LONG ic = -1;
static LONG fc = -1;
void TestFCount ()
  {
  static int iniread;
  if (!iniread) {
    char iBuffer[32];
    GetPrivateProfileString ("Profile","FreeBreak","-1",iBuffer,32,MYINI);
    LPSTR h = iBuffer ;
    LONG sign = 1 ;
    for ( fc = 0L ; *h ; h ++) {
      if ((*h >= '0') && (*h <= '9'))
        fc = LONG(*h - '0') + fc * 10L ;
      else
        if (*h == '-') sign = -1 ;
      }
    fc = fc * sign ;
    iniread = TRUE ;
    }
  if ((DWORD(fc) == fcount) && (fc != -1L)) {
    short k = 0 ;
    // short j = 12 / k ;
    }
  }

DLLExport void _export WINAPI PushFree (LPVOID res)
  {
  char outtxt[26];
#ifdef WIN32
  wsprintf (outtxt,"U%u:%u(%lu)\r\n",HIWORD(LONG(res)),LOWORD(LONG(res)),fcount);
#else
  wsprintf (outtxt,"U%u:%u(%lu)\r\n",FP_SEG(res),FP_OFF(res),fcount);
#endif
  TestFCount ();
  PushMLine (outtxt);
  fcount ++;
  }

void TestGCount ()
  {
  static int iniread;
  if (!iniread) {
    char iBuffer[32];
    GetPrivateProfileString ("Profile","GetBreak","-1",iBuffer,32,MYINI);
    LPSTR h = iBuffer ;
    LONG sign = 1 ;
    for ( ic = 0L ; *h ; h ++) {
      if ((*h >= '0') && (*h <= '9'))
        ic = LONG(*h - '0') + ic * 10L ;
      else
        if (*h == '-') sign = -1 ;
      }
    ic = ic * sign ;
    iniread = TRUE ;
    }
  if ((DWORD(ic) == gcount) && (ic != -1L)) {
    LONG k = 0 ;
    // LONG j = ic / k ;
    }
  }

DLLExport void _export WINAPI PushGet (LPVOID res)
  {
  char outtxt[26];
  TestGCount ();
#ifdef WIN32
  wsprintf (outtxt,"L%u:%u(%lu)\r\n",HIWORD(LONG(res)),LOWORD(LONG(res)),gcount);
#else
  wsprintf (outtxt,"L%u:%u(%lu)\r\n",FP_SEG(res),FP_OFF(res),gcount);
#endif
  PushMLine (outtxt);
  gcount ++;
  }

#ifdef STATISTICS
void PushSize (WORD size)
  {
  if (size < MAXSIZE) {
    MemAnf[size].AnzAnf++;
    MemAnf[size].ActAnzAnf++;
    if (MemAnf[size].ActAnzAnf > MemAnf[size].MaxAnzAnf)
      MemAnf[size].MaxAnzAnf = MemAnf[size].ActAnzAnf;
    }
  }

void PopSize (WORD size)
  {
  if (size < MAXSIZE) {
    WIN_ASSERT (MemAnf[size].ActAnzAnf > 0);
    MemAnf[size].ActAnzAnf--;
    }
  }

void SetTypeFixed (int size)
  {
  if (size < MAXSIZE)
    MemAnf[size].type = TRUE;
  }

DLLExport void _export WINAPI WriteSegStat (HFILE fi,LPSTR txt);
DLLExport void _export WINAPI ShowFifoStat (HFILE fi);
DLLExport void _export WINAPI WriteSizeStat ()
  {
  OFSTRUCT Of;
  HFILE fi = OpenFile ("memstat.inf",&Of,OF_CREATE | OF_WRITE);
  char outtxt[170];
  for (int i = 0 ; i < MAXSIZE ; i++) {
    wsprintf (outtxt,"%d: %s %ld (Max: %d)\r\n",i,
                  LPSTR ((MemAnf[i].type) ? "Fixed" : "Var.") ,
                  MemAnf[i].AnzAnf,MemAnf[i].MaxAnzAnf
             );
    _lwrite (fi,outtxt,lstrlen(outtxt));
    }

  // Statistik fuer die Segmente
  WriteSegStat (fi,outtxt);
  ShowFifoStat (fi);
  _lclose (fi);
#ifdef TESTMEM
  Closeaf ();
#endif
#ifdef TESTGALLOC
  Closeaf ();
#endif
  }

#else
DLLExport void _export WINAPI WriteSizeStat ()
  {
  }

#endif

DLLExport BOOL _export WINAPI GetFirstSegInfo (GLOBALHANDLE FAR *hGmem,WORD FAR *Seg,LPVOID FAR *hlp)
  {
  *hlp = FirstSegHandle;
  if (*hlp) {
    *hGmem = FirstSegHandle->hGmem;
#ifndef WIN32    
    *Seg = FP_SEG(FirstSegHandle->_First);
#endif
    return TRUE ;
    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI GetNextSegInfo (GLOBALHANDLE FAR *hGmem,WORD FAR *Seg,LPVOID FAR *hlp)
  {
  LPSEGHANDLE h = LPSEGHANDLE (*hlp);
  if ((h != NULL) && (h->Next)) {
    *hlp = h->Next ;
    *hGmem = h->hGmem;
#ifndef WIN32
    *Seg = FP_SEG(h->_First);
#endif
    return TRUE ;
    }
  return FALSE ;
  }


/////////////////////////////////////////////////////////////////
//  Initialisierung der Segmente
/////////////////////////////////////////////////////////////////
struct IniMemDesc {
  WORD start;
  WORD end;
  WORD size;
  };

struct FAR hGSizedMem {
  GLOBALHANDLE hGres;
  LPSTR Base;

  BOOL IsInSeg (LPVOID Ptr)
    {
    return ((DWORD(Ptr) >= DWORD(Base)) &&
            (DWORD(Ptr) <= DWORD(Base) + (GlobalSize(hGres) - 1L))) ;
    }
  };

struct SegDesc {
  hGSizedMem Next;
  WORD ItemSize;
  WORD AnzItems;
  WORD MaxAnzItems;
  WORD AnzItemsPerTry;
#ifdef STATISTICS
  WORD SegSize;
#endif
#ifdef WIN32
  LPVOID FreePtr;
#else
  WORD FreePtr;
#endif
  };
typedef SegDesc FAR *LPSEGDESC;

#define MAX_DIM   1024
hGSizedMem smdata[MAX_DIM];
hGSizedMem FAR *sm[MAX_DIM];
inline LPSEGDESC GetDesc (LPSTR s) 
  { 
  return LPSEGDESC (s) ; 
  }

#ifdef STATISTICS
static char *hdline = "\r\n\r\nSegmentstatistik:\r\n-----------------\r\n\r\n";
DLLExport void _export WINAPI WriteSegStat (HFILE fi,LPSTR txt)
  {
  _lwrite (fi,hdline,lstrlen(hdline));
  int state = 0;
  LPVOID oldBase;
  DWORD MaxSize,AnzHits,GesSize_o,GesSize_m ;
  int beg ;
  int j = 0;
  DWORD outSpace = 0,AnzExt = 0;
  WORD segSize;
  for (int i = 0 ; i < MAX_DIM ; ) {
    switch (state) {
      case 0 :
        if (sm[i]->hGres) {
          state = 1 ;
          LPSEGDESC sd = GetDesc (sm[i]->Base);
          MaxSize = MemAnf[i].MaxAnzAnf * sd->ItemSize ;
          GesSize_o = MemAnf[i].AnzAnf * DWORD(i);
          GesSize_m = MemAnf[i].AnzAnf * sd->ItemSize;
          AnzHits = MemAnf[i].AnzAnf;
          segSize = sd->SegSize;
          beg = i ;
          }
        else {
          outSpace += MemAnf[i].AnzAnf * DWORD(i) ;
          AnzExt += MemAnf[i].AnzAnf;
          }
        i++ ;
        break ;
      case 1 :
        if (sm[i]->Base == oldBase) {
          LPSEGDESC sd = GetDesc (sm[i]->Base);
          MaxSize += MemAnf[i].MaxAnzAnf * sd->ItemSize ;
          AnzHits += MemAnf[i].AnzAnf;
          GesSize_o += MemAnf[i].AnzAnf * DWORD(i);
          GesSize_m += MemAnf[i].AnzAnf * sd->ItemSize;
          i++ ;
          }
        else {
          oldBase = sm[i]->Base ;
          int vers;
          if (GesSize_m)
            vers = int (100L * (GesSize_m - GesSize_o) / GesSize_m);
          else
            vers = 0;
          wsprintf (txt,"  Segment %d (Gr��e %d - %d): %ld Byte in %ld Anf. (Seg. gr��e: %u, Verschnitt: %d%%)\r\n",j++,
                        beg,i-1,MaxSize,AnzHits,segSize,vers
                   );
          _lwrite (fi,txt,lstrlen(txt));
          state = 0;
          }
        break ;
      }
    }
  wsprintf (txt,"\r\nAngeforderter Speicher au�erhalb:\r\n === %ld Anforderungen (%ld Byte) ===",AnzExt,outSpace);
  _lwrite (fi,txt,lstrlen(txt));
  }
#endif

void InitializeLinMem (HINSTANCE hInst)
  {
  for (int ii = 0; ii < MAX_DIM; ii++)
    sm[ii] = &(smdata[ii]);
  HGLOBAL hGmem = LoadResource (hInst,
        FindResource(hInst,"#1000",RT_RCDATA)
                               );
  if (hGmem) {
    IniMemDesc FAR *res = (IniMemDesc FAR *)LockResource (hGmem);
    for ( ; res->start ; res ++) {
#ifdef WIN32
      sm[res->start]->hGres = GlobalAlloc (GMEM_FIXED,res->size);
#else
      sm[res->start]->hGres = GlobalAlloc (GMEM_MOVEABLE,res->size);
#endif
      // PushGSize(res->size);
      LPSEGDESC sd = LPSEGDESC (GlobalLock (sm[res->start]->hGres));
      sm[res->start]->Base = LPSTR(sd);
      lmemset (sd,'\0',sizeof(*sd));
      for (WORD i = res->start + 1; i <= res->end ; i++)
        sm[i] = sm[res->start];
#ifdef STATISTICS
      for (i = res->start; i <= res->end ; i++)
        SetTypeFixed (i);
#endif
      sd->ItemSize = (res->end + sizeof(WORD));
      sd->MaxAnzItems = (res->size - sizeof (*sd)) / (sd->ItemSize);
      sd->AnzItemsPerTry = sd->MaxAnzItems ;
#ifdef STATISTICS
      sd->SegSize = res->size;
#endif
      }
    UnlockResource (hGmem);
    FreeResource (hGmem);
    }
  }

DLLExport void _export WINAPI FreeLinMem () 
  {
  for (WORD i = 0 ; i < MAX_DIM ; i++) {
    if (sm[i]->hGres) {
      while ((i < MAX_DIM - 1) && (sm[i+1]->hGres == sm[i]->hGres)) i ++; 
      LPSEGDESC sd = GetDesc (sm[i]->Base);
      GLOBALHANDLE hGmem = sm[i]->hGres;
      while (sd != NULL) {
        LPSEGDESC sdn = GetDesc (sd->Next.Base);
        GLOBALHANDLE hGNext = sd->Next.hGres;
        GlobalUnlock (hGmem);
        GlobalFree (hGmem);
        sd = sdn;
        hGmem = hGNext;
        }
      }
    }
  }

BOOL doWrite = TRUE;
DLLExport LPVOID _export WINAPI GetGlobMem (WORD size)
  {
  LPVOID res = NULL ;
#ifdef WIN32
#ifdef JUSTUSEGLOBAL
  GLOBALHANDLE hG = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,size + sizeof(WORD));
  res = LPSTR(GlobalLock (hG)) + sizeof(WORD);
  ((WORD *) res)[-1] = size ;
  return res ;
#endif
#endif
  if ((size < MAX_DIM) && (sm[size]->hGres)) {
    LPSTR b;
    LPSEGDESC sd = GetDesc (b = sm[size]->Base);
    while ((sd->FreePtr == NULL) && (sd->AnzItems == sd->MaxAnzItems)) {
      // Naechstes Segment..
      if (sd->Next.Base) {
        sd = GetDesc (b = sd->Next.Base);
        }
      else {
        // Neues Segment..
        GLOBALHANDLE NewRes = GlobalAlloc (GMEM_MOVEABLE,
                sd->MaxAnzItems * sd->ItemSize + sizeof(*sd)
                                     );
        // PushGSize(sd->MaxAnzItems * sd->ItemSize + sizeof(*sd));
        LPSEGDESC sdn = LPSEGDESC (GlobalLock (NewRes));
        LPSTR NewBase = LPSTR(sdn) ;
        lmemset (sdn,'\0',sizeof(*sdn));
        sdn->MaxAnzItems = sd->MaxAnzItems;
        sdn->ItemSize = sd->ItemSize;
        sdn->Next.hGres = sm[size]->hGres;
        sdn->Next.Base = sm[size]->Base;
        sm[size]->hGres = NewRes;
        sm[size]->Base = NewBase;
        sd = sdn;
        }
      }
    if (sd->FreePtr) {
#ifdef WIN32
      res = sd->FreePtr ;
      sd->FreePtr = * ((LPVOID *) res) ;
#else
      res = MAKELP (FP_SEG(b),sd->FreePtr);
      sd->FreePtr = * ((WORD FAR *) res) ;
#endif
      }
    else {
      // Hat hinten Platz
      res = LPSTR (sd + 1) + sd->ItemSize * sd->AnzItems++ ;
      }

    *(WORD FAR *) res = size;
    res = ((WORD FAR *) res) + 1;
    lmemset (res,'\0',size);

#ifdef STATISTICS
    PushSize (size);
#endif

    }
  else {
#ifndef WIN32
    for (LPSEGHANDLE h = FirstSegHandle ; h != NULL ; h = h->Next) {
      if ((res = TryInThisSeg (h,size)) != NULL) break ;
      }
    if (res == NULL) 
      res = InitializeNewSeg (size);
#else
    GLOBALHANDLE hG = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,size + sizeof(WORD));
    res = LPSTR(GlobalLock (hG)) + sizeof(WORD);
    ((WORD *) res)[-1] = size ;
#endif
#ifdef STATISTICS
    PushSize (size);
#endif
    }

#ifdef TESTMEM
  if (doWrite)
    PushGet (res);
#endif
  return res ;
  }

void FreeFault ()
  {
  MessageBox (GetActiveWindow (),
                  "MemFault","!!! Freemem failed !!!",
                  MB_ICONEXCLAMATION | MB_OK
            );
  int a = 3 ;
  int b = 0 ;
  int c = a / b ;   // Provozieren eine Division / 0 Fehlers
  }

DLLExport void _export WINAPI FreeGlobMem (LPVOID res)
  {
#ifdef WIN32
#ifdef JUSTUSEGLOBAL
  GLOBALHANDLE hGmem = GlobalHandle (LPSTR(res) - sizeof(WORD)) ;
  GlobalUnlock (hGmem);
  GlobalFree (hGmem);
  return ;
#endif
#endif

#ifdef TESTMEM
  if (doWrite)
    PushFree (res);
#endif
  WORD size = GetBlockSize (res);
#ifdef STATISTICS
  PopSize (size);
#endif
  if ((size < MAX_DIM) && (sm[size]->hGres)) {
    hGSizedMem FAR *h = sm[size] ;
    LPSEGDESC sd = GetDesc(h->Base) ;
    while (!h->IsInSeg (res)) {
      h = &sd->Next ;
      sd = GetDesc(sd->Next.Base) ;
      }
    if (sd != NULL) {
#ifdef DEBUG
      lmemset (res,'\0',((WORD FAR *) res)[-1]);
#endif
#ifndef WIN32
      ((WORD FAR *) res)[-1] = sd->FreePtr;
      sd->FreePtr = FP_OFF(res) - sizeof(WORD);
#else
      *((LPVOID FAR *)((WORD FAR *) res - 1)) = sd->FreePtr;
      sd->FreePtr = LPSTR(res) - sizeof(WORD);
#endif
      }
    else
      FreeFault ();
    }
  else {
#ifndef WIN32
    LPSEGHANDLE h = GetSeg (res);
    if (h != NULL) {
      FreeGlobalMem (res,&h->hGmem);
      if (h->hGmem == 0) DelSegEntry (h);
      else               h->size = 0xFFFF;
      }
    else FreeFault ();
#else
    GLOBALHANDLE hGmem = GlobalHandle (LPSTR(res) - sizeof(WORD)) ;
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
#endif
    }
  }

// CRC-Berechnung (fuer Hash-Funktionen)

static WORD ctable[256] = {
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
  0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
  0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
  0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
  0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
  0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
  0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
  0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
  0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
  0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
  0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
  0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
  0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
  0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
  0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
  0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
  0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
  0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
  0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
  0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
  0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
  0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
  0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
  };

static DWORD c32table[256] = {
  0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
  0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
  0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
  0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
  0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
  0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
  0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
  0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
  0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
  0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
  0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
  0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
  0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
  0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
  0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
  0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
  0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
  0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
  0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
  0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
  0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
  0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
  0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
  0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
  0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
  0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
  0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
  0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
  0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
  0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
  0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
  0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
  };

inline int updcrc(char cp, int crc) {
  return (ctable[((crc >> 8) & 255)] ^ (crc << 8) ^ cp);
  }

DLLExport int _export WINAPI GetCRC (LPSTR buffer,int size)
  {
  int res = 0;
  for (int i = size - 1 ; i >= 0 ; i--)
    res = updcrc (buffer[i],res);
  return res;
  }

DLLExport DWORD _export WINAPI GetCRC32(LPSTR buffer,int  size,DWORD _crc)
  {
  typedef BYTE FAR *t_BytePtr;

  t_BytePtr bytePtr;
  DWORD oldcrc;
  t_BytePtr oldcrc_lowbyte = t_BytePtr (&oldcrc);

  oldcrc = ~_crc;
  bytePtr = t_BytePtr(buffer);
  while (size > 0) {
    oldcrc = (c32table[(*oldcrc_lowbyte) ^ (*bytePtr)] ^ (oldcrc >> 8));
    bytePtr++;
    size--;
    }
  return ~oldcrc;
  }

////////////////////////////////////////////////////////////////
//  Ermitteln des True - Names
////////////////////////////////////////////////////////////////
extern "C" {
extern void WINAPI DOS3Call(void);
  }
DLLExport BOOL _export WINAPI GetTrueName (LPSTR filename,LPSTR truename)
  {
  char origin[256];
  lstrcpy (origin,filename);
  if ((lstrlen(origin) == 0) || 
      (filename[lstrlen(origin)-1] == ':') ||
      (filename[lstrlen(origin)-1] == '\\'))
    lstrcat (origin,".");
  BOOL res;
  _asm {
    push ds
    push es
    push ss
    pop ds
    lea si, origin
    les di, truename
    mov ah,60h
    int 21h
;    call DOS3Call
    jc fehler
    mov res,1
fehler:
    mov res,0
    pop es
    pop ds
    }
  return res;
  }

////////////////////////////////////////////////////////////////
//  Fenster aufbauen und dorthin zeichnen
////////////////////////////////////////////////////////////////
extern HINSTANCE MyInstance;
static char *FaultClass = "WINASS";
static void RegisterFaultWnd ()
  {
  WNDCLASS wndclass;
  wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
  wndclass.lpfnWndProc   = DefWindowProc ;
  wndclass.cbClsExtra    = 0 ;
  wndclass.cbWndExtra    = 0 ;
  wndclass.hInstance     = MyInstance ;
  wndclass.hIcon         = NULL ;
  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
  wndclass.hbrBackground = CreateSolidBrush (RGB(0xFF,0x80,0xFF));
  wndclass.lpszMenuName  = NULL ;
  wndclass.lpszClassName = FaultClass ;

  RegisterClass (&wndclass) ;
  }

static void UnRegisterFaultWnd ()
  {
  UnregisterClass (FaultClass,MyInstance);
  }

static HWND FaultWnd;
static void CreateFaultWnd ()
  {
  int w = MyGetSystemMetrics (SM_CXSCREEN) / 2 ;
  int h = MyGetSystemMetrics (SM_CYSCREEN) / 2 ;
  int x0 = (MyGetSystemMetrics (SM_CXSCREEN) - w) / 2;
  int y0 = (MyGetSystemMetrics (SM_CYSCREEN) - h) / 2;
  FaultWnd = CreateWindow (FaultClass,
                          "Programmfehler",
                            WS_POPUP | WS_BORDER | WS_CAPTION | WS_VISIBLE,
                            x0,y0,
                            w,h,
                            NULL,
                            0,
                            MyInstance,
                            NULL
                           );
  }

static void DestroyFaultWnd ()
  {
  DestroyWindow (FaultWnd);
  }

static LPSTR ftxt;
static void PaintFaultWnd (HWND hWnd)
  {
  HDC hDC = GetDC (hWnd);
  RECT r;
  GetClientRect (hWnd,&r);
  r.top += r.bottom / 4;
  r.left += 10 ;
  r.right -= 10 ;
  int oldmode = SetBkMode (hDC,TRANSPARENT);
  DrawText (hDC,ftxt,-1,&r,DT_CENTER | DT_WORDBREAK);
  SetBkMode (hDC,oldmode);
  ReleaseDC (hWnd,hDC);
  }

static BOOL InOWA = FALSE;
static BOOL FromException = FALSE;
static BOOL ContinueAllowed = TRUE;

#pragma optimize("",off)
static void showAssWindow (LPSTR txt)
  {
  if (ContinueAllowed)
    lstrcat(txt,"(C)ontinue ");
  if (InOWA || (!FromException) || (!ContinueAllowed)) {
    lstrcat(txt,"(A)bort");
    lstrcat(txt," (D)ebug");
    }
  ftxt = txt;
  long AutoAbortTime = long(GetPrivateProfileInt("ErrorHandling","AutoAbortTime",-1,MYINI)) * 1000L;
  if (AutoAbortTime != 0L) {
    RegisterFaultWnd ();
    CreateFaultWnd ();
    PaintFaultWnd (FaultWnd);
    DWORD starttime;
    if (AutoAbortTime > 0L)
      starttime = GetTickCount();
    for ( ; ; ) {
      if (GetAsyncKeyState ('R') < 0) {
        while (GetAsyncKeyState ('R') < 0);
        PaintFaultWnd (FaultWnd);
        }
      if (AutoAbortTime > 0L) {
        if (long(GetTickCount() - starttime) > AutoAbortTime) {
          if (InOWA || (!FromException) || (!ContinueAllowed))
            FatalExit (0);
          break;
          }
        }
      if (ContinueAllowed) {
        if (GetAsyncKeyState ('C') < 0) {
          while (GetAsyncKeyState ('C') < 0);
          DeleteObject (0);   // Force Dr. Watson..
          break ;
          }
        }
      if (InOWA || (!FromException) || (!ContinueAllowed)) {
        if (GetAsyncKeyState ('A') < 0) {
          while (GetAsyncKeyState ('A') < 0);
          DeleteObject (0);   // Force Dr. Watson..
          FatalExit (0);
          break ;
          }
        if (GetAsyncKeyState ('D') < 0) {
          while (GetAsyncKeyState ('D') < 0);
          int a = 1 ;
          int b = 0 ;
          int c = a / b ;
          break ;
          }
        }
      }
    DestroyFaultWnd ();
    UnRegisterFaultWnd ();
    }
  else {
    if (InOWA || (!FromException) || (!ContinueAllowed))
      FatalExit (0);
    }
  if (!InOWA)
    FromException = FALSE;
  }

static char modname[32];
DLLExport LPSTR _export WINAPI ModName (int modnum)
  {
  if (LoadString (MyInstance,modnum,modname,sizeof(modname)-1) == 0)
    wsprintf (modname,"???");
  return modname;
  }

#ifdef WIN32
static DWORD wSS,wCS,wIP,wBP;
DLLExport void _export WINAPI SetFromException(DWORD actSS, DWORD actCS, DWORD actIP, DWORD actBP)
  {
  wSS = actSS;
  wCS = actCS;
  wIP = actIP;
  wBP = actBP;
  FromException = TRUE;
  }
#else
static WORD wSS,wCS,wIP,wBP;
void _export FAR PASCAL SetFromException(WORD actSS, WORD actCS, WORD actIP, WORD actBP)
  {
  wSS = actSS;
  wCS = actCS;
  wIP = actIP;
  wBP = actBP;
  FromException = TRUE;
  }
#endif

typedef BOOL (FAR PASCAL * BOOL_PROC) (void);
BOOL_PROC OnWinAssert = NULL;
DLLExport void  _export WINAPI SetOnWinAssertProc(FARPROC actOnWinAssert)
  {
  OnWinAssert = (BOOL_PROC)actOnWinAssert;
  }

static char winassstr[2048];

#ifdef WIN32
DLLExport BOOL _export WINAPI MyReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead)
  {
  return ReadProcessMemory(GetCurrentProcess(), lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
  }

static void GetScriptName(LPSTR ScriptName,mdiChild *c)
  {
  LPSCRIPTCONTENT sc;
  DWORD bytesread;
  if (MyReadProcessMemory(NULL,(LPVOID)&(c->schd),&sc,sizeof(LPVOID),&bytesread) && (bytesread == sizeof(LPVOID))) {
    if ((!MyReadProcessMemory(NULL,(LPVOID)&(sc->fName),ScriptName,sizeof(sc->fName),&bytesread)) || (bytesread != sizeof(sc->fName)))
      lstrcpy(ScriptName,"<invalid mdiChild (3)>");
    }
  else
    lstrcpy(ScriptName,"<invalid mdiChild (2)>");
  }

static LPSTR GetFunctionName(VirtFunctionCall *fc)
  {
  static char FunctionName[256];
  lmemset(FunctionName,'\0',sizeof(FunctionName));
  DWORD bytesread;
  if (!MyReadProcessMemory(NULL,(LPVOID)fc->FName,FunctionName,sizeof(FunctionName) - 1,&bytesread))
    lstrcpy(FunctionName,"<invalid VirtFunctionCall (2)>");
  return FunctionName;
  }
#endif

static void WriteStackTrace(HFILE f)
  {
#ifdef WIN32
  if (!FromException) {
    // ich muss mir die aktuellen Register selber holen
    __asm {
      mov eax,esp;
      mov wSS,eax;
      xor eax,eax;
      mov ax,cs;
      label:
      mov wCS,eax;
      mov eax,offset label;
      mov wIP,eax;
      mov eax,ebp;
      mov wBP,eax;
      }
    }
  STACKFRAME sf;
  lmemset(&sf,'\0',sizeof(STACKFRAME));
  sf.AddrPC.Offset = wIP;
  sf.AddrPC.Mode = AddrModeFlat;
  sf.AddrFrame.Offset = wBP;
  sf.AddrFrame.Mode = AddrModeFlat;
  sf.AddrStack.Offset = wSS;
  sf.AddrStack.Mode = AddrModeFlat;
  HANDLE hProc = (HANDLE)GetCurrentProcessId();
  HANDLE hThread = GetCurrentThread();
  SymSetOptions((SymGetOptions() & ~SYMOPT_UNDNAME) | SYMOPT_DEFERRED_LOADS);
  SymInitialize(hProc,NULL,TRUE);
  GetLastError();
  BOOL stok = StackWalk(IMAGE_FILE_MACHINE_I386,hProc,hThread,&sf,NULL,(PREAD_PROCESS_MEMORY_ROUTINE)MyReadProcessMemory,SymFunctionTableAccess,SymGetModuleBase,NULL);
  GetLastError();
  int StackFrameNo = 0;
  while (stok) {
    if (FromException || (StackFrameNo > 2)) {
      IMAGEHLP_MODULE mod;
      SymGetModuleInfo(hProc,sf.AddrPC.Offset,&mod);
      GetLastError();
      PIMAGEHLP_SYMBOL sym = (PIMAGEHLP_SYMBOL)GetGlobMem(sizeof(IMAGEHLP_SYMBOL) + 256);
      sym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
      sym->MaxNameLength = 256;
      DWORD displacement;
      BOOL gotsym = SymGetSymFromAddr(hProc,sf.AddrPC.Offset,&displacement,sym);
      GetLastError();
      if (gotsym) {
        LPSTR undecname = (LPSTR)GetGlobMem(512);
        if (UnDecorateSymbolName(sym->Name,undecname,512,UNDNAME_COMPLETE)) {
          char ScriptName[30];
          DWORD bytesread;
          mdiChild *c;
          if (!lstrcmp(undecname,"public: int __thiscall mdiChild::ExCuteBlock(char *,unsigned long,unsigned short)")) {
            if (MyReadProcessMemory(NULL,(LPVOID)(sf.AddrFrame.Offset -
#ifdef DEBUG
                                    0x10C
#else
                                    0x20
#endif
                                   ),(LPVOID)&c,sizeof(LPVOID),&bytesread) && (bytesread == sizeof(LPVOID))) {
              GetScriptName(ScriptName,c);
              }
            else
              lstrcpy(ScriptName,"<invalid mdiChild (1)>");
            wsprintf(undecname,"ExCuteBlock in Script %s",ScriptName);
            }
          else if (!lstrcmp(undecname,"public: void __thiscall mdiChild::CallCommand(void *,unsigned short)")) {
            if (MyReadProcessMemory(NULL,(LPVOID)(sf.AddrFrame.Offset -
#ifdef DEBUG
                                    0xA8
#else
                                    0x48
#endif
                                   ),(LPVOID)&c,sizeof(LPVOID),&bytesread) && (bytesread == sizeof(LPVOID))) {
              GetScriptName(ScriptName,c);
              }
            else
              lstrcpy(ScriptName,"<invalid mdiChild (1)>");
            wsprintf(undecname,"CallCommand in Script %s",ScriptName);
            }
          else if (!lstrcmp(undecname,"public: char * __thiscall mdiChild::DoVirtFunctionCall(char *,unsigned short)")) {
            LPSTR h;
            if (MyReadProcessMemory(NULL,(LPVOID)(sf.AddrFrame.Offset +
#ifdef DEBUG
                                    0x8
#else
                                    0x8
#endif
                                   ),(LPVOID)&h,sizeof(LPVOID),&bytesread) && (bytesread == sizeof(LPVOID))) {
              VirtFunctionCall *fc = (VirtFunctionCall *) (h + sizeof(WORD));
              wsprintf(undecname,"call virtual function '%s'",GetFunctionName(fc));
              }
            else {
              lstrcpy(undecname,"call virtual function <invalid VirtFunctionCall (1)>");
              }
            }
          else {
            if (!SymUnDName(sym,undecname,512))
              lstrcpy(undecname,sym->Name);
            }
          }
        else {
          if (!SymUnDName(sym,undecname,512))
            lstrcpy(undecname,sym->Name);
          }
        if (!lstrcmp(undecname,"WinMainCRTStartup"))
          stok = FALSE;
        wsprintf(winassstr, "Frame %2d: %-9.9s at %08X (%s + 0x%X)\r\n",StackFrameNo, mod.ModuleName, sf.AddrPC.Offset - mod.BaseOfImage, undecname, displacement);
        }
      else
        wsprintf(winassstr, "Frame %2d: %-9.9s at %08X\r\n",StackFrameNo, mod.ModuleName, sf.AddrPC.Offset - mod.BaseOfImage);
      _lwrite (f,winassstr,lstrlen(winassstr));
      FreeGlobMem(sym);
      }
    if (stok) {
      StackFrameNo++;
      stok = StackWalk(IMAGE_FILE_MACHINE_I386,hProc,hThread,&sf,NULL,(PREAD_PROCESS_MEMORY_ROUTINE)MyReadProcessMemory,SymFunctionTableAccess,SymGetModuleBase,NULL);
      GetLastError();
      }
    }
  SymCleanup(hProc);
#else
  if (!FromException) {
    // ich muss mir die aktuellen Register selber holen
    __asm {
      mov ax,ss;
      mov wSS,ax;
      mov ax,cs;
      label:
      mov wCS,ax;
      mov ax,offset label;
      mov wIP,ax;
      mov ax,bp;
      mov wBP,ax;
      }
    }
  STACKTRACEENTRY ste;
  lmemset(&ste,'\0',sizeof(STACKTRACEENTRY));
  ste.dwSize = sizeof(STACKTRACEENTRY);
  BOOL stok = StackTraceCSIPFirst(&ste,wSS,wCS,wIP,wBP);
  int StackFrameNo = 0;
  while (stok) {
    if (FromException || (StackFrameNo > 2)) {
      MODULEENTRY me;
      lmemset(&me,'\0',sizeof(MODULEENTRY));
      me.dwSize = sizeof(MODULEENTRY);
      ModuleFindHandle(&me,ste.hModule);
      wsprintf(winassstr, "Frame %2d: %-9.9s at %04X:%04X\r\n",StackFrameNo,(LPSTR)me.szModule,ste.wSegment,ste.wIP);
      _lwrite (f,winassstr,lstrlen(winassstr));
      }
    StackFrameNo++;
    stok = StackTraceNext(&ste);
    }
#endif
  }
#pragma optimize("",on)

DLLExport void _export WINAPI SetErrorContextStr (LPSTR txt)
  {
  ErrorContext = txt;
  }

GLOBALHANDLE JavaExceptionText = NULL;
DLLExport void _export WINAPI SetJavaExceptionText (GLOBALHANDLE jet)
  {
  JavaExceptionText = jet;
  }

static BOOL Folgefehler = FALSE;
DLLExport void _export WINAPI LogMsg (int modnum,int line,LPSTR txt)
  {
  if (!InOWA) {
    InOWA = TRUE;
    if (OnWinAssert != NULL)
      ContinueAllowed = (*OnWinAssert)();
    InOWA = FALSE;
    }
  OFSTRUCT Of;
#ifdef UEBERLEGT
  LPSTR fname = makeIni ("faults.log");
#endif
  LPSTR fname = GetStationLogFile ("faults.log");
#ifdef UEBERLEGT
  HFILE f = OpenFile (fname,&Of,OF_EXIST | OF_SHARE_EXCLUSIVE);
  if (f == HFILE_ERROR) {
    f = OpenFile (fname,&Of,OF_CREATE | OF_SHARE_EXCLUSIVE);
    _lclose(f);
    }
  f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
#endif
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
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
    static char date[64],time[64];
    _strdate (date);
    _strtime (time);
    if (modnum > 0) {
      if (txt != NULL)
        wsprintf (winassstr,"%s, %s\r\n  Modul: %d (%s), Zeile %d\t%.1900s",LPSTR(date),LPSTR(time),modnum,ModName(modnum),line,txt);
      else
        wsprintf (winassstr,"%s, %s\r\n  Modul: %d (%s), Zeile %d",LPSTR(date),LPSTR(time),modnum,ModName(modnum),line);
      int rfound = 0 ;
      for (LPSTR h = winassstr ; *h ; h++) {
        if (*h == '\r') {
          if ((-- rfound) < -1)
            *h = '\t' ;
          }
        }
      }
    else
      lstrncpy (winassstr,txt,2040);
    _lwrite (f,winassstr,lstrlen(winassstr));
    lstrcpy (winassstr,"\r\n");
    if (ErrorContext != NULL)
      lstrcat (winassstr,ErrorContext);
    if (InOWA) {
      lstrcat (winassstr,"(innerhalb Fehlerbehandlung)");
      }
    else {
      if (Folgefehler)
        lstrcat (winassstr,"(Folgefehler)");
      else
        Folgefehler = TRUE;
      }
    lstrcat (winassstr,"\r\n");
    _lwrite (f,winassstr,lstrlen(winassstr));
    WriteStackTrace(f);
    lstrcpy (winassstr,"\r\n");
    _lwrite (f,winassstr,lstrlen(winassstr));
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

DLLExport void _export WINAPI win_ass_failed (int modnum, int line)
  {
  LogMsg (modnum,line,NULL);
  if (InOWA || !FromException)
    wsprintf (winassstr,"In der Anwendung ist ein Programmfehler aufgetreten.\r"
                  "Notieren Sie bitte die folgenden Informationen f�r eine weitere Behandlung des Problems.\r\r"
                  "Modul Nr.: %d (%s), Zeile: %d\r\r",
              modnum, ModName(modnum), line
             );
  else
    wsprintf (winassstr,"In der Anwendung ist ein Programmfehler aufgetreten.\r"
                  "Notieren Sie bitte die folgenden Informationen f�r eine weitere Behandlung des Problems.\r\r"
                  "Interne Fehlermeldung: WIN_ASSERT bei Exception\r\r"
             );
  showAssWindow (winassstr);
  }

DLLExport void _export WINAPI win_ass_failed_text (int modnum, int line,LPSTR txt)
  {
  LogMsg (modnum,line,txt);
  if (InOWA || !FromException)
    wsprintf (winassstr,"In der Anwendung ist ein Programmfehler aufgetreten.\r"
                  "Notieren Sie bitte die folgenden Informationen f�r eine weitere Behandlung des Problems.\r\r"
                  "Modul Nr.: %d (%s), Zeile: %d\r%.1800s\r\r",
              modnum, ModName(modnum), line , txt
             );
  else
    wsprintf (winassstr,"In der Anwendung ist ein Programmfehler aufgetreten.\r"
                  "Notieren Sie bitte die folgenden Informationen f�r eine weitere Behandlung des Problems.\r\r"
                  "%.1800s\r\r",
              txt
             );
  showAssWindow (winassstr);
  }

static BOOL BusyCursorAllowed = TRUE;
static BOOL DenyOnce = FALSE;
static HCURSOR hOldCursor = 0;

DLLExport void _export WINAPI DenyBusyCursor()
  {
  BusyCursorAllowed = FALSE;
  }

DLLExport void _export WINAPI DenyBusyCursorOnce()
  {
  DenyOnce = TRUE;
  DenyBusyCursor();
  }

DLLExport void _export WINAPI AllowBusyCursor()
  {
  BusyCursorAllowed = TRUE;
  }

DLLExport BOOL _export WINAPI IsBusyCursor()
  {
  return hOldCursor != 0;
  }

void RestoreIntern()
  {
  if (hOldCursor != 0)
    SetCursor(hOldCursor);
  hOldCursor = 0;
  }

DLLExport void _export WINAPI RestoreCursor()
  {
  if (DenyOnce) {
    AllowBusyCursor();
    DenyOnce = FALSE;
    }
  RestoreIntern();
  }

DLLExport void _export WINAPI ToBusyCursor()
  {
  if (BusyCursorAllowed) {
    if (hOldCursor == 0)
      hOldCursor = SetCursor(LoadCursor(NULL,IDC_WAIT));
    }
  else
    RestoreIntern();
  }

DLLExport void _export WINAPI ToggleWrite()
  {
  if (doWrite) doWrite = FALSE ;
  else         doWrite = TRUE ;
  }

// #define WITH_GLOBALCHECK
DLLExport HGLOBAL _export WINAPI GGlobalAlloc (UINT fuAlloc, DWORD cbAlloc)
  {
  HGLOBAL res = GlobalAlloc (fuAlloc, cbAlloc);
  // PushGSize(cbAlloc);
#ifdef WITH_GLOBALCHECK
  WIN_ASSERT_TEXT ((res != NULL), "GlobalAlloc fehlgeschlagen !");
  AddToGlobalCheckList(res,GCL_TYPE_GLOBALALLOC);
#endif
#ifdef TESTGALLOC
  PushGet (GlobalLock(res));
  GlobalUnlock(res);
#endif
  return res;
  }

DLLExport HGLOBAL _export WINAPI GGlobalReAlloc (HGLOBAL hglb, DWORD cbNewSize, UINT fuAlloc)
  {
#ifdef TESTGALLOC
  PushFree (GlobalLock (hglb));
  GlobalUnlock (hglb);
#endif
  HGLOBAL res = GlobalReAlloc (hglb, cbNewSize, fuAlloc);
#ifdef WITH_GLOBALCHECK
  if (res != hglb) {
//    WIN_ASSERT_TEXT (FALSE, "GlobalReAlloc aenderte Handle !");
    RemoveFromGlobalCheckList(hglb);
    AddToGlobalCheckList(res,GCL_TYPE_GLOBALALLOC);
    }
#endif
#ifdef TESTGALLOC
  PushGet (GlobalLock(res));
  GlobalUnlock(res);
#endif
  return res;
  }

DLLExport HGLOBAL _export WINAPI GGlobalFree (HGLOBAL hglb)
  {
#ifdef TESTGALLOC
  PushFree (GlobalLock (hglb));
  GlobalUnlock (hglb);
#endif
  HGLOBAL res = GlobalFree (hglb);
#ifdef WITH_GLOBALCHECK
  WIN_ASSERT_TEXT ((res == NULL), "GlobalFree fehlgeschlagen !");
  RemoveFromGlobalCheckList(hglb);
#endif
  return res;
  }

DLLExport void _export WINAPI CheckGlobalAllocs (void)
  {
  WIN_ASSERT_TEXT((ActGlobalCheck == ActFreeCheck),"Speicherfresser !");
  }


// profile handling
#define MAX_PROFILE_PRIORITY 10
struct {
  WORD AnzChars;
  LPSTR Buffer;
  } ProfileBuffer[MAX_PROFILE_PRIORITY];

DLLExport void _export WINAPI AddProfileOverrideBuffer (WORD Priority,LPSTR buffer)
  {
  DBWIN_ASSERT(Priority < MAX_PROFILE_PRIORITY);
  DBWIN_ASSERT(ProfileBuffer[Priority].AnzChars == 0);
  if (buffer == NULL) {
    ProfileBuffer[Priority].AnzChars = 1;
    ProfileBuffer[Priority].Buffer = (LPSTR)GetGlobMem(1);
    }
  else {
    ProfileBuffer[Priority].AnzChars = GetBlockSize(buffer);
    ProfileBuffer[Priority].Buffer = (LPSTR)GetGlobMem(ProfileBuffer[Priority].AnzChars);
    lmemcpy(ProfileBuffer[Priority].Buffer,buffer,ProfileBuffer[Priority].AnzChars);
    }
  }

DLLExport void _export WINAPI RemoveProfileOverrideBuffer (WORD Priority)
  {
  DBWIN_ASSERT(ProfileBuffer[Priority].AnzChars > 0);
  FreeGlobMem(ProfileBuffer[Priority].Buffer);
  ProfileBuffer[Priority].Buffer = NULL;
  ProfileBuffer[Priority].AnzChars = 0;
  }

int ActProfileBuffer = -1;
#define BUFFER_SIZE 4096
static char FileBuffer[BUFFER_SIZE];
static int BufPtr;
static int BytesInBuffer;
HFILE ProFile;
static BOOL ReadChar(LPSTR ch)
  {
  if (ActProfileBuffer >= 0) {
    if (BufPtr < ProfileBuffer[ActProfileBuffer].AnzChars)
      *ch = ProfileBuffer[ActProfileBuffer].Buffer[BufPtr++];
    else
      return FALSE;
    }
  else {
    if (BufPtr >= BytesInBuffer) {
      if (BytesInBuffer < BUFFER_SIZE) return FALSE;
      BytesInBuffer = _lread (ProFile, FileBuffer, sizeof(FileBuffer));
      if (BytesInBuffer == 0) return FALSE;
      BufPtr = 0;
      }
    *ch = FileBuffer[BufPtr++];
    }
  return TRUE;
  }

static char LineBuffer[512];
static BOOL WasLastLine;
static int LineCount;
static BOOL ReadLine(void)
  {
  if (WasLastLine) return FALSE;
  BOOL ReadOK;
  LineBuffer[0] = '\0';
  while ((ReadOK = ReadChar(LineBuffer)) != 0) {
    if ((LineBuffer[0] != '\r') && (LineBuffer[0] != '\n')) break;
    if (LineBuffer[0] == '\r')
      LineCount++;
    }
  if (!ReadOK)
    LineBuffer[0] = '\0';
  for (int i = 1; i < 510; i++) {
    if (ReadOK && ReadChar(LineBuffer + i)) {
      if ((LineBuffer[i] == '\r') || (LineBuffer[i] == '\n')) {
        if (LineBuffer[i] == '\r')
          LineCount++;
        LineBuffer[i] = '\0';
        return TRUE;
        }
      }
    else {
      LineBuffer[i] = '\0';
      WasLastLine = TRUE;
      return TRUE;
      }
    }
  WIN_ASSERT_TEXT(FALSE,"Zeile in ini-file laenger als 512 Bytes !");
  return FALSE;
  }

DLLExport void _export WINAPI CheckOneProfileBuffer(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault, LPSTR lpszReturnBuffer, int cbReturnBuffer, LPCSTR lpszFilename, BOOL FAR *found)
  {
  WasLastLine = FALSE;
  BOOL InMySection = FALSE;
  while ((!*found) && ReadLine()) {
    if (LineBuffer[0] == '[') {
      for (int i = 1; LineBuffer[i] && (LineBuffer[i] != ']'); i++);
      WIN_ASSERT_TEXT(LineBuffer[i] == ']',"Section: ']' fehlt in ini-file !");
      LineBuffer[i] = '\0';
      InMySection = (lstrcmpi(lpszSection,LineBuffer + 1) == 0);
      }
    else if (InMySection && LineBuffer[0]) {
      LPSTR EntryText = LineBuffer;
      while (*EntryText && *EntryText != '=') EntryText++;
      if (*EntryText == '=') {
        *EntryText++ = '\0';
        if (lstrcmpi(lpszEntry,LineBuffer) == 0) {
          if (*EntryText == '"') {
            int l = lstrlen(EntryText) ;
            if (EntryText[l-1] == '"') {
              EntryText[l-1] = '\0'; 
              EntryText ++ ;
              }
            }
          lstrncpy(lpszReturnBuffer,EntryText,cbReturnBuffer);
          lpszReturnBuffer[cbReturnBuffer - 1] = '\0';
          *found = TRUE;
          }
        }
      }
    }
  }

static BOOL OrbisGetestet = FALSE;
static BOOL IsOrbis = FALSE;
static char OrbisCnfName[256];
typedef char * (__stdcall *RESOLVEVARPROC)(const char*);
static RESOLVEVARPROC ResolveOrbisVar;
DLLExport void _export WINAPI SetOrbisCnfName (LPSTR CnfName,RESOLVEVARPROC r)
  {
  if (CnfName != NULL)
    lstrcpy(OrbisCnfName,CnfName);
  ResolveOrbisVar = r;
  }

BOOL Orbis ()
  {
  if (!OrbisGetestet) {
    if ((!WithStartDir) && (!IchBinDasRestool)) {
      if (*OrbisCnfName)
        IsOrbis = TRUE;
      }
    OrbisGetestet = TRUE;
    }
  return IsOrbis;
  }

DLLExport int _export WINAPI MyGetPrivateProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault, LPSTR lpszReturnBuffer, int cbReturnBuffer, LPCSTR lpszFilename)
  {
  if (JustForDebug) {
    if ((lstrcmpi(lpszSection,"DataBase") == 0) &&
        (lstrcmpi(lpszEntry,"ResourceDLL") == 0)) {
      lstrcpy(lpszReturnBuffer,"dbbtrv.dll");
      return lstrlen(lpszReturnBuffer);
      }
    }
  BOOL found = FALSE;
  for (int i = 0; (!found) && (i < MAX_PROFILE_PRIORITY); i++) {
    if (ProfileBuffer[i].AnzChars > 0) {
      ActProfileBuffer = i;
      BufPtr = 0;
      CheckOneProfileBuffer(lpszSection,lpszEntry,lpszDefault,lpszReturnBuffer,cbReturnBuffer,lpszFilename,&found);
      }
    }
  ActProfileBuffer = -1;
  if (!found) {
    char MyFileName[256];
    lstrcpy(MyFileName,lpszFilename);
    BOOL Kombi = FALSE;
    if (Orbis()) {
      int Len = lstrlen(MyFileName);
      if (Len >= 7) {
        AnsiUpperBuff(MyFileName + (Len - 7),7);
        if (!lstrcmp(MyFileName + (Len - 7),"DMW.INI")) {
          OFSTRUCT testof;
          if (OpenFile (MyFileName, &testof, OF_EXIST) == HFILE_ERROR) {
#ifdef UEBERLEGT
            lstrcpy(MyFileName + (Len - 7),"ORBIS.CNF");
#endif
            lstrcpy(MyFileName,OrbisCnfName);
            Kombi = TRUE;
            }
          }
        }
      }
    OFSTRUCT of;
    ProFile = OpenFile (MyFileName, &of, OF_READ | OF_SHARE_DENY_WRITE);
    if (ProFile != HFILE_ERROR) {
      BytesInBuffer = BufPtr = BUFFER_SIZE;
      if (Kombi) {
        char KombiEntry[256];
        char MyReturnBuffer[512];
        wsprintf(KombiEntry,"%s_%s",lpszSection,lpszEntry);
        CheckOneProfileBuffer("OpenMed",KombiEntry,lpszDefault,MyReturnBuffer,512,MyFileName,&found);
        if (!found) {
          _llseek (ProFile,0L,SEEK_SET);
          BytesInBuffer = BufPtr = BUFFER_SIZE;
          CheckOneProfileBuffer("OpenMed2",KombiEntry,lpszDefault,MyReturnBuffer,512,MyFileName,&found);
          }
        lstrncpy(lpszReturnBuffer,(*ResolveOrbisVar)(MyReturnBuffer),cbReturnBuffer);
        lpszReturnBuffer[cbReturnBuffer - 1] = '\0';
        }
      else
        CheckOneProfileBuffer(lpszSection,lpszEntry,lpszDefault,lpszReturnBuffer,cbReturnBuffer,MyFileName,&found);
      _lclose (ProFile);
      }
    }
  if (!found)
    lstrcpy(lpszReturnBuffer,lpszDefault);

  return lstrlen(lpszReturnBuffer);
  }

DLLExport UINT _export WINAPI MyGetPrivateProfileInt(LPCSTR lpszSection, LPCSTR lpszEntry, int idefault, LPCSTR lpszFilename)
  {
  char IntBuffer[10];
  MyGetPrivateProfileString(lpszSection,lpszEntry,"",IntBuffer,10,lpszFilename);
  long res = 0L;
  int i = 0;
  BOOL negativ = FALSE;
  if (IntBuffer[0] == '-') {
    i++;
    negativ = TRUE;
    }
  while (IntBuffer[i]) {
    if ((IntBuffer[i] >= '0') && (IntBuffer[i] <= '9')) {
      res = res * 10L + long(IntBuffer[i] - '0');
      if (res > 32767L) return idefault;
      i++;
      }
    }
  if (negativ) {
    if (i > 1)
      return UINT(-res);
    else
      return idefault;
    }
  else {
    if (i > 0)
      return UINT(res);
    else
      return idefault;
    }
  }

DWORD HelpContextNr = 1;   // statische Variable!!
char HelpFile[64] = "DDS.HLP";

DLLExport LPSTR _export WINAPI GetHelpFile ()
  {
  return HelpFile;
  }

DLLExport DWORD _export WINAPI GetHelpContextNr ()
  {
  return HelpContextNr;
  }

DLLExport void  _export WINAPI SetHelpContextNr (DWORD dwHelpContextNr)
  {
  HelpContextNr = dwHelpContextNr;
  }

DLLExport void  _export WINAPI SetHelpFile (LPSTR lpHelpFile)
  {
  lstrcpy (HelpFile, lpHelpFile);
  }


//============================================================================
//
// HTML Hilfe
//
//============================================================================
//char chmFile[MAX_PATH] = "";
typedef HWND (WINAPI *FPHH) (HWND, LPCSTR, UINT, DWORD);

FPHH htmlHelp;


char HtmlFile[MAX_PATH] = "";

DLLExport void _export SetHtmlHelp (FARPROC htmlproc)
  {
  (FARPROC&) htmlHelp = htmlproc;
  }


//----------------------------------------------------------------------------
// Ruft die Funktion htmlHelp ueber den Funktionspointer aus dem 
// HHCTRL.OCX auf.
//----------------------------------------------------------------------------
DLLExport HWND _export WINAPI htmlhelp (HWND hWnd, LPCSTR lpstr, 
                                        UINT uint , DWORD dword)
  {
  return (htmlHelp ? htmlHelp (hWnd, lpstr, uint, dword) : NULL);
  }

//----------------------------------------------------------------------------
// lpchmfile .... Die kompilierte HTML-Hilfe Datei
// lphtmlfile ... Das Sprungziel in der kompilierten Datei
//----------------------------------------------------------------------------
DLLExport void _export WINAPI SetHtmlContext (LPSTR lpchmfile, 
                                              LPSTR lphtmlfile)
  {
//  lstrcpy (chmFile, lpchmfile);
  lstrcpy (HtmlFile, lpchmfile);
  lstrcat (HtmlFile, "::/");
  lstrcat (HtmlFile, lphtmlfile);
  }

DLLExport LPSTR _export WINAPI GetHtmlFile ()
  {
  return HtmlFile;
  }


DLLExport int _export WINAPI BitsPerPixel (void)
  {
  static int bpp = 0;
  if (!bpp) {
    HDC hdc = GetDC(NULL);
    bpp = GetDeviceCaps(hdc,BITSPIXEL);
    ReleaseDC(NULL,hdc);
    }
  return bpp;
  }


DLLExport void _export WINAPI MyLPtoDP (HDC hDC,LPPOINT pt,int cnt)
  {
  POINT vo,wo;
  SIZE ve,we;
  GetWindowExtEx (hDC,&we);
  GetViewportExtEx (hDC,&ve);
  GetWindowOrgEx (hDC,&wo);
  GetViewportOrgEx (hDC,&vo);
  for (int i = 0 ; i < cnt ; i++) {
    pt[i].x = ((pt[i].x - wo.x) * ve.cx + we.cx / 2) / we.cx + vo.x ;
    pt[i].y = ((pt[i].y - wo.y) * ve.cy + we.cy / 2) / we.cy + vo.y ;
    }
  }

static HINSTANCE hFloydst = NULL;
typedef BOOL (CALLBACK *GETFSBUFFERPROC)(LPSTR,int);
typedef BOOL (CALLBACK *SEARCHFSITEMPROC)(LPSTR,LPSTR,int);
static GETFSBUFFERPROC GetFSBufferPtr;
static SEARCHFSITEMPROC SearchFSItemPtr;
void LoadFloydst()
  {
  if (!hFloydst) {
    hFloydst = LoadLibrary(makeIni("floydst.dll"));
    if (hFloydst == NULL) {
      char LibName[256];
      // ansonsten noch im EXE-Verzeichnis probieren
      lstrcpy(LibName, GetExePath());
      int len = lstrlen(LibName);
      if (LibName[len - 1] != '\\')
        LibName[len++] = '\\';
      lstrcpy(LibName + len, "floydst.dll");
      hFloydst = LoadLibrary(LibName);
      }
    WIN_ASSERT_TEXT((hFloydst != NULL),"Kann floydst.dll nicht laden !");
    GetFSBufferPtr = GETFSBUFFERPROC (GetProcAddress(hFloydst,"?GetFSBuffer@@YGHPADH@Z"));
    WIN_ASSERT_TEXT((GetFSBufferPtr != NULL),"GetFSBuffer in floydst.dll nicht richtig definiert !");
    SearchFSItemPtr = SEARCHFSITEMPROC (GetProcAddress(hFloydst,"?SearchFSItem@@YGHPAD0H@Z"));
    WIN_ASSERT_TEXT((SearchFSItemPtr != NULL),"SearchFSItem in floydst.dll nicht richtig definiert !");
    }
  }

DLLExport BOOL _export WINAPI GetFSBuffer (LPSTR res,int Size)
  {
  LoadFloydst();
  return (*GetFSBufferPtr)(res,Size);
  }

DLLExport BOOL _export WINAPI SearchFSItem (LPSTR str,LPSTR Item,int ItemSize)
  {
  LoadFloydst();
  return (*SearchFSItemPtr)(str,Item,ItemSize);
  }

int first_metric = 1;
int cx_screen, cy_screen;
__declspec( dllexport ) int WINAPI MyGetSystemMetrics(int nIndex)
  {
  if (first_metric) {
    cx_screen = GetSystemMetrics(SM_CXSCREEN);
    cy_screen = GetSystemMetrics(SM_CYSCREEN);
    
    int FixResolutionX = int(GetPrivateProfileInt("Profile","FixResolutionX",-1,MYINI));
    int FixResolutionY = int(GetPrivateProfileInt("Profile","FixResolutionY",-1,MYINI));
    
    if (FixResolutionX > 0) {
      cx_screen = FixResolutionX;
      }
    if (FixResolutionY > 0) {
      cy_screen = FixResolutionY;
      }
      
    char retstr[5];
    GetPrivateProfileString ("Profile", "SplitScreenX", "no",
                            retstr,sizeof(retstr),
                            MYINI
                            );
    if ((!lstrcmp (retstr,"yes")) ||
        ((float(cx_screen) / float(cy_screen)) > 2.0001))
      cx_screen = cx_screen / 2;
    GetPrivateProfileString ("Profile", "SplitScreenY", "no",
                            retstr,sizeof(retstr),
                            MYINI
                            );
    if (!lstrcmp (retstr,"yes"))
      cy_screen = cy_screen / 2;
    first_metric = 0;
    }
  if (nIndex == SM_CXSCREEN)
    return cx_screen;
  else if (nIndex == SM_CYSCREEN)
    return cy_screen;
  else
    return GetSystemMetrics(nIndex);
  }


static hash *LtxHash;
DLLExport void _export WINAPI InitLanguageTextTable(void)
  {
  for (int ind = 1; ind <= 10; ind++) {
    char LtxFile[256];
    char EntryName[10];
    sprintf(EntryName,"LtxFile%d",ind);
    GetPrivateProfileString ("Config",EntryName,"",
                            LtxFile,sizeof(LtxFile),
                            MYINI
                            );
    if (*LtxFile) {
      OFSTRUCT of;
      ProFile = OpenFile (LtxFile, &of, OF_READ | OF_SHARE_DENY_WRITE);
      if (ProFile != HFILE_ERROR) {
        if (LtxHash == NULL)
          LtxHash = new hash(997,LONGKEY);
        BytesInBuffer = BufPtr = BUFFER_SIZE;
        WasLastLine = FALSE;
        LineCount = 0;
        while (ReadLine()) {
          int line = LineCount;
          int i = 0;
          while ((LineBuffer[i] == ' ') || (LineBuffer[i] == '\t'))
            i++;
          DWORD id = 0L;
          while ((LineBuffer[i] >= '0') && (LineBuffer[i] <= '9')) {
            id = (id * 10L) + DWORD(LineBuffer[i] - '0');
            i++;
            }
          if (id > 0L) {
            if (LineBuffer[i] == ' ') {
              if (LtxHash->GetData(id) == NULL) {
                i++;
                LPSTR s = LineBuffer + i;
                LPSTR d = s;
                while (*s) {
                  if (*s == '\\') {
                    s++;
                    if (*s == 'r')
                      *d++ = '\r';
                    else if (*s == 't')
                      *d++ = '\t';
                    else if (*s == '\\')
                      *d++ = '\\';
                    else {
                      char errtxt[256];
                      sprintf(errtxt,"Fehler in Datei %s, Zeile %d: Ung�ltige Escape-Sequenz!",LtxFile,line);
                      WIN_ASSERT_TEXT(FALSE,errtxt);
                      if (*s == '\0')
                        s--;
                      }
                    s++;
                    }
                  else
                    *d++ = *s++;
                  }
                *d++ = '\0';
                LtxHash->SetData(id,LineBuffer + i,strlen(LineBuffer + i) + 1);
                }
              }
            else {
              char errtxt[256];
              sprintf(errtxt,"Fehler in Datei %s, Zeile %d: Leerzeichen nach dem Code fehlt!",LtxFile,line);
              WIN_ASSERT_TEXT(FALSE,errtxt);
              }
            }
          else {
            if ((LineBuffer[i] != ';') && (LineBuffer[i] != '\0')) {
              char errtxt[256];
              sprintf(errtxt,"Fehler in Datei %s, Zeile %d: Ziffer oder Semikolon erwartet!",LtxFile,line);
              WIN_ASSERT_TEXT(FALSE,errtxt);
              }
            }
          }
        _lclose (ProFile);
        }
      }
    }
  }

DLLExport LPSTR _export WINAPI Ltx(DWORD id)
  {
  if (LtxHash != NULL)
    return LPSTR(LtxHash->GetData(id));
  else
    return NULL;
  }

DLLExport int _export WINAPI GetLtx(DWORD id, LPSTR s, int maxsize)
  {
  LPSTR h = Ltx(id);
  if (h != NULL) {
    lstrncpy(s, h, maxsize - 1);
    s[maxsize - 1] = '\0';
    return strlen(s);
    }
  else
    return 0;
  }

#ifdef UNICODE

DLLExport LPCPLSTR _export WINAPI AnsiToBomStr (LPASTR str)
  {
  int len = strlen(str) + 1;
  LPTSTR res = (LPTSTR)GetGlobMem((len + 1) * sizeof(TCHAR));
  res[0] = BOM;
  MultiByteToWideChar(CP_THREAD_ACP, 0, str, len, res + 1, len);
  return (LPCPLSTR)res;  // muss vom Aufrufer freigegeben werden!
  }

#endif

DLLExport LPASTR _export WINAPI UnicodeToAnsi (LPWSTR str)
  {
  int len = lstrlenW(str) + 1;
  LPASTR res = (LPASTR)GetGlobMem(len);
  WideCharToMultiByte(CP_THREAD_ACP, 0, str, len, res, len, NULL, NULL);
  return res;  // muss vom Aufrufer freigegeben werden!
  }
