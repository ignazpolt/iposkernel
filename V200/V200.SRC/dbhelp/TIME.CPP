/*----------------------------------------------------------*/
/*      Umrechnungen zwischen verschiedenen Datums          */
/*              Typen                                       */
/*----------------------------------------------------------*/
// $Header:   P:/marille/clinicum/dbhelp/rev/time.cpv   1.16   15 Jun 1999 19:17:16   WOLFGANG  $
// $Log:   P:/marille/clinicum/dbhelp/rev/time.cpv  $
// 
//    Rev 1.16   15 Jun 1999 19:17:16   WOLFGANG
// 1.) ResetSync neu.
// 2.) lastSync auf lokale Zeit setzen!
// 
//    Rev 1.15   15 Jun 1999 16:23:20   WOLFGANG
// 1.) TimeNow und ungepacktes Now ausgebaut.
// 2.) Now mit Synchronisation mit Datenbank.
// 3.) Von DMWAPI nach DBHELP verschoben.
// 
//    Rev 1.14   06 Apr 1999 13:01:02   Martin
// GetLocalTime anstatt localtime
// 
//    Rev 1.13   18 Nov 1998 15:48:40   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.12   17 Aug 1998 17:25:32   Hannes
// Neue Interpretation
// 
//    Rev 1.11   15 May 1998 10:39:16   Gerhold
// Zeitangaben im Default-Fall wieder beschraenkt auf 24 Stunden (readtimestr)
// 
//    Rev 1.10   28 Apr 1998 11:21:32   Gerhold
// Ueberpruefung von 24 Stunden bei Zeiteingabe raus
// 
//    Rev 1.9   02 Jul 1997 08:15:26   Hannes
// No change.
// 
//    Rev 1.8   02 Feb 1996 10:46:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   13 Nov 1995 16:50:06   MARTIN
// readTime korrigiert
// 
//    Rev 1.6   01 Sep 1995 09:03:38   HANNES
// 
//    Rev 1.5   23 Mar 1995 10:22:32   GERHOLD
// Zeit-Funktion fuer Eingabefelder umgebaut
// 
//    Rev 1.4   11 Dec 1994 18:19:30   HANNES
// Optimierung ausgeschaltet
// 
//    Rev 1.3   11 Oct 1994 08:59:48   HANNES
// 
//    Rev 1.2   05 Sep 1994 19:53:52   HANNES
// Fuehrende 0 in WriteTimeStr
// 
//    Rev 1.1   05 Aug 1994 19:21:44   HANNES
// readTimeStr,writeTimeStr,TimeNow
// 
//    Rev 1.0   24 Jun 1994 16:49:04   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   04 Jan 1994 17:36:40   HANNES
// Fehlerkorrektur in DaysInMonth
// 
//    Rev 1.3   27 Sep 1993 19:00:04   HANNES
// DaysInMonth, Leap..
// 
//    Rev 1.2   02 Jun 1993 21:54:54   HANNES
// Weitere Versuche mit der Optimierung
// 
//    Rev 1.1   02 Jun 1993 21:27:32   HANNES
// Optimierung ausgeschalten?
// 
//    Rev 1.0   02 Jun 1993 19:34:50   HANNES
// Initial revision.
// 
//    Rev 1.1   22 Feb 1993 17:17:08   HANNES
// Verschiedene kleine erweiterungen
// 
//    Rev 1.0   02 Dec 1992 15:46:10   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#define MODULENUM 66
#include "winass.hpp"
#include "math.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

extern LPSTR WINAPI GetIniName();

// Umrechnen eines Datums in das Softwork - Format
static packdate c_Start_Time = { 1 , 6 , 1950 } ;
#define c_SecsPerDay LONG (86400)

#pragma optimize ("",off)
DLLExport LONG _export WINAPI JulianDays (packdate FAR *pd)
  {
  LONG jd;
  packdate p;
  lmemcpy (&p,pd,sizeof(p));

  if (p.month <= 2) {
    p.year -= 1 ;
    p.month += 12 ;
    }

  if (p.year >= 0)
    jd = ((365 * 4 + 1) * LONG (p.year)) / 4 ;
  else
    jd = ((365 * 4 + 1) * LONG (p.year) - 3) / 4 ;

  jd += (306 * (LONG(p.month) + 1)) / 10 ;
  jd += 1720996 + LONG(p.day) ;

  if (jd <= 2299162)
    jd -= 2 ;
  else {
    if (jd >= 2299172)
      jd += LONG(p.year) / 400 - LONG(p.year) / 100 ;
    else
      jd = 0 ;
    }
  return jd ;
  }

DLLExport INTTIME _export WINAPI PackTime (packdate FAR *pd)
  {
  INTTIME t;

  t = INTTIME(JulianDays (pd));
  INTTIME Start_JD = INTTIME(JulianDays (&c_Start_Time));
  t = t - Start_JD;
  return t * c_SecsPerDay + 1;
  }

DLLExport INTTIME _export WINAPI PackSeconds (packtime FAR *pt)
  {
  return INTTIME (pt->hour) * (INTTIME) 3600 +
         INTTIME (pt->minute * 60) +
         INTTIME (pt->second) ;
  }

LONG DivDays (INTTIME l,INTTIME base)
  {
  LONG t ;
  if (l < 0)
    t = LONG ((l - base + 1) / base) ;
  else
    t = LONG (l / base) ;
  return t ;
  }

LONG ModDays (INTTIME l,INTTIME base)
  {
  return LONG (l - INTTIME (DivDays (l, base)) * base);
  }

#pragma auto_inline (off)
void JulianDate (LONG jd,packdate FAR *tr)
  {
  LONG a,b,c,hd,e,f;

  a = jd + 1;
  if (a < 2299161)
    c = a + 1524 ;
  else {
    b = (4 * a - 7468865) / 146097 ;
    c = a + b - b / 4 + 1525 ;
    }
  hd = (20 * c - 2442) / 7305 ;
  e = (1461 * hd) / 4;
  f = ((c - e) * 10000) / 306001 ;
  tr->day   = unsigned (c - e - (306001 * f) / 10000) ;
  tr->month = unsigned (f - 1 - 12 * (f / 14)) ;
  tr->year = int (hd - 4715 - (7 + tr->month) / 10) ;
  }
#pragma auto_inline (on)

DLLExport void _export WINAPI UnPackTime (INTTIME t,packdate FAR *tr)
  {
  LONG l ;

  l = DivDays (t,c_SecsPerDay);
  LONG Start_JD = JulianDays (&c_Start_Time);
  JulianDate (l+Start_JD,tr);
  }

DLLExport void _export WINAPI UnPackSeconds (INTTIME t,packtime FAR *pt)
  {
  LONG l ;

  l = ModDays (t,c_SecsPerDay);
  pt->hour   = l / 3600;
  pt->minute = (l % 3600) / 60;
  pt->second = l % 60;
  }


LONG ModPositive (LONG l, LONG base)
  {
  l = l % base ;
  if (l < 0) l += base ;
  return l ;
  }

DLLExport int _export WINAPI WeekDay (INTTIME t)
  {
  return int (ModPositive (3 + DivDays (t,c_SecsPerDay),7));
  }

BOOL GetRemoteTime (INTTIME FAR * serverNow)
  {
  packdatetime pdt;
  DLLHANDLE th = GetTransactionDLL();
  if (GetDLLAdmin()->GetDLLEntry(th)->DBCurrentDateTime (&pdt)) {
    *serverNow = PackTime (&pdt.pd) + PackSeconds (&pdt.pt);
    return TRUE;
    }
  else
    return FALSE;
  }

static INTTIME lastSync = 0.0L;

DLLExport void _export WINAPI ResetSync ()
  {
  lastSync = 0.0L;
  }

int StrToInt (LPSTR txt, int *pi = NULL, char endChar = 0)
  {
  int i = 0;
  int l = lstrlen(txt);
  if (pi != NULL) {
    i = *pi;
    }
  int  starti = i;
  int  res;
  char c;
  for (res = 0; (c = txt[i]) && (i < l); (i)++) {
    if ((c >= '0') && (c <= '9'))
      res = res*10 + c-'0';
    else if (c == endChar) {
      break;
      }
    else {
      if (pi != NULL)
        *pi = i;
      return -1;
      }
    }
  if (pi != NULL)
    *pi = i;
  if (i > starti)
    return res; //at least one digit scaned
  else
    return -1;
  }

DLLExport INTTIME _export WINAPI Now ()
  {
  static int useSync = -1;
  static INTTIME syncInterval = 0.0L;
  static INTTIME syncDifference = 0.0L;

  static int useStaticTime = -1;
  static SYSTEMTIME staticTime;
  if (useStaticTime == -1) {
    char dbgDate[11], dbgTime[9];
    GetPrivateProfileString ("Profile","DbgDate","",dbgDate,sizeof(dbgDate),GetIniName());
    GetPrivateProfileString ("Profile","DbgTime","",dbgTime,sizeof(dbgTime),GetIniName());
    if (dbgDate[0] && dbgTime[0]) {
      int parsePos = 0;
      staticTime.wDay   = StrToInt(LPSTR (dbgDate),&parsePos,'.');
      parsePos++;
      staticTime.wMonth = StrToInt(LPSTR (dbgDate),&parsePos,'.');
      parsePos++;
      staticTime.wYear  = StrToInt(LPSTR (dbgDate),&parsePos);

      parsePos = 0;
      staticTime.wHour   = StrToInt(LPSTR (dbgTime),&parsePos,':');
      parsePos++;
      staticTime.wMinute = StrToInt(LPSTR (dbgTime),&parsePos,':');
      parsePos++;
      short secs = StrToInt(LPSTR (dbgTime),&parsePos);
      if (secs == -1)
        staticTime.wSecond = 0;
      else
        staticTime.wSecond = secs;

      if
        (
          (staticTime.wYear > 0) &&
          (staticTime.wMonth >= 1) && (staticTime.wMonth <= 12) &&
          (staticTime.wDay >= 1) && (staticTime.wDay <= DaysInMonth(staticTime.wYear,staticTime.wMonth)) &&
          (staticTime.wHour >= 0) && (staticTime.wHour <= 23) &&
          (staticTime.wMinute >= 0) && (staticTime.wMinute <= 59) &&
          (staticTime.wSecond >= 0) && (staticTime.wSecond <= 59)
        )
        {
        useStaticTime=1;
        }
      else
        {
        useStaticTime=0; //nicht verwenden
        }
      }
    else {
      useStaticTime=0; //nicht verwenden
      }
    }

  SYSTEMTIME st,*ust;
  GetLocalTime (&st);
  if (useStaticTime == 1)
    ust = &staticTime;
  else
    ust = &st;

  packdate   pd;
  pd.year  = ust->wYear ;
  pd.month = BYTE (ust->wMonth);
  pd.day   = BYTE (ust->wDay);

  INTTIME localNow = PackTime (&pd);

  localNow += INTTIME (ust->wHour) * (INTTIME) 3600 +
              INTTIME (ust->wMinute * 60) +
              INTTIME (ust->wSecond) ;

  if (useSync == -1) {
    syncInterval = GetPrivateProfileInt ("Config", "SyncInterval", 3600, GetIniName ());
    if (syncInterval >= 0)
      useSync = TRUE;
    else
      useSync = FALSE;
    }
  if (useSync && ((localNow - lastSync >= syncInterval) || (localNow < lastSync))) {
    INTTIME serverNow;
    if (GetRemoteTime (&serverNow)) {
      // Hier koennte man (konfigurierbar) auch die Rechnerzeit und localNow
      // auf serverNow und die syncDifference auf 0 stellen
      syncDifference = serverNow - localNow;
      lastSync = localNow;
      }
    }
  return localNow + syncDifference;
  }

DLLExport BOOL WINAPI _export Leap(int year)
  {
  return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
  }

DLLExport int WINAPI _export YearLen(int year)
  {
  return Leap(year) ? 366 : 365;
  }

DLLExport int WINAPI _export DaysInMonth (int year,int month)
  {
  static int AnzDays[] = { 
    31 ,  // Jan
    28 ,  // Feb
    31 ,  // Mar
    30 ,  // Apr
    31 ,  // May
    30 ,  // Jun
    31 ,  // Jul
    31 ,  // Aug
    30 ,  // Sep
    31 ,  // Okt
    30 ,  // Nov
    31    // Dez
    };
  WIN_ASSERT ((month >= 1) && (month <= 12));
  return ((month == 2) && (Leap(year))) ? 29 : AnzDays[month-1];
  }

const int STATE_START              = 0;
const int STATE_GETNEXTHOUR        = 1;
const int STATE_GETDELIMITER       = 2;
const int STATE_GETMINUTE          = 3;
const int STATE_GETNEXTMINUTE      = 4;
const int STATE_GETMINUTEDELIMITER = 5;
const int STATE_ERROR              = 255;

BOOL IsDelimiter (char ch)
  {
  return ((ch == ':') || (ch == '.') || (ch == '-') || (ch == ' '));
  }

BOOL NoDelimiter (LPSTR txt)
  {
  for ( LPSTR h = txt ; *h ; h++ ) {
    if (IsDelimiter(*txt)) return FALSE ;
    }
  return TRUE ;
  }

DLLExport BOOL _export WINAPI readTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt)
  {
  if ((txt == NULL) || (lstrlen(txt) > 8))
    return FALSE;

  BOOL res = TRUE;

  int TimeArr[3];
  char Buffer[32];
  if ((lstrlen(txt) < 4) && (*txt) && (NoDelimiter (txt))) {
    for ( int i = 0 ; i < 4 - lstrlen(txt) ; i++)
      Buffer[i] = '0' ;
    Buffer[i] = '\0' ;
    lstrcat (Buffer,txt);
    }
  else
    lstrcpy (Buffer,txt);

  int i, j;
  for (i = 0; i < 3; TimeArr[i++] = 0);  // leer machen

  char szBuf[3];
  LPSTR p = Buffer;

  // j ist der Zaehler fuer Stunden, Minuten und Sekunden
  for (j = 0; j < 3; j++) {
    for (i = 0; *p && !IsDelimiter(*p) && (i < 2); p++, i++)
      szBuf[i] = *p;

    szBuf[i] = '\0';               // h, m oder s
    if ((j == 0) && (szBuf[0] == '\0')) res = FALSE;  // zumindest Stunde !!!
    TimeArr[j] = StrToInt(szBuf);

    if (IsDelimiter(*p))
      p++;

    if (*p == '\0')
      break;
    }

  //------------------------------------------------------------------
  // Im Default-Fall werden Zeitangaben > 24 Stunden nicht akzeptiert
  // (einstellbar ueber das Format)
  //------------------------------------------------------------------
  pt->hour = BYTE(TimeArr[0]);
  if (((Format == 0) && (pt->hour >= 24)) || (pt->hour < 0))
    res = FALSE;
    
  pt->minute = BYTE(TimeArr[1]);
  if ((pt->minute < 0) || (pt->minute > 59))
    res = FALSE;

  pt->second = BYTE(TimeArr[2]);
  if ((pt->second < 0) || (pt->second > 59))
    res = FALSE;

  pt->hundred_second = 0;

  return res;
  }

#ifdef UEBERLEGT
//***************************************************************************
//
//  Tatue - Tata - Code von Gerhold, sollte eine State - Machine sein
//
//***************************************************************************
DLLExport BOOL _export WINAPI readTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt)
  {
  int State = STATE_START;

  int hour = 0;
  int minute = 0;
  int second = 0;
  int ms = 0;

  int  cnt = 0;
  char ch;
  char sztmp[20];
  
  while (((ch = txt[cnt]) != '\0') && (State != STATE_ERROR)) {
    switch (State) {
      case STATE_START:
        {
        if ((ch >= '0') && (ch <= '2'))        // es kann eine weitere Ziffer folgen
          State = STATE_GETNEXTHOUR;
        else if ((ch >= '3') && (ch <= '9'))   // jetzt mu� ein Delimiter kommen
          State = STATE_GETDELIMITER;
        else 
          State = STATE_ERROR;
        }
        break;
        
      //---------------------------------------------
      // ich habe schon 0, 1 oder 2; was kommt jetzt?
      case STATE_GETNEXTHOUR:
        {
        if ((ch >= '0') && (ch <= '9')) {
          lmemset (sztmp, '\0', sizeof(sztmp));
          lstrncpy (sztmp, txt, cnt+1);
          if (StrToInt(sztmp) < 24)        // sind die ersten zwei Ziffern sinnvoll?
            State = STATE_GETDELIMITER;    // ja, jetzt mu� ein Delimiter kommen!
          else  
            State = STATE_ERROR;           // nein, z.b.: 24 ... 29
          }
        }
        break;  

      //---------------------------------------------
      // jetzt mu� aber ein Trennzeichen kommen!
      case STATE_GETDELIMITER:
        {
        if (IsDelimiter(ch)) {                       // g�ltiges Trennzeichen?
          lmemset (sztmp, '\0', sizeof(sztmp));
          lstrncpy (sztmp, txt, cnt);
          hour = StrToInt(sztmp);                    // Stunde ist somit fertig
          State = STATE_GETMINUTE;                   // jetzt kommt die Minute
          }
        else
          State = STATE_ERROR;  
        }
        break;

      //---------------------------------------------
      // nach der Stunde kommen die Minuten
      case STATE_GETMINUTE:
        {
        if ((ch >= '0') && (ch <= '5'))
          State = STATE_GETNEXTMINUTE;
        else
          State = STATE_ERROR;  
        }
        break;

      //---------------------------------------------
      // die erste Minuten-Ziffer war 0 ... 5
      case STATE_GETNEXTMINUTE:
        {
        if ((ch >= '0') && (ch <= '9')) {
          lmemset (sztmp, '\0', sizeof(sztmp));
          lstrncpy (sztmp, txt+cnt-1, 2);
          if (minute >= 0) {                           // wurde die Minute schon ermittelt?
            second = StrToInt(sztmp);                  // ja, dann sind die Sekunden fertig
            }
          else {
            minute = StrToInt(sztmp);                  // Minute ist somit fertig
            State = STATE_GETMINUTEDELIMITER;
            }
          }
        else
          State = STATE_ERROR;
        }
        break;

      //---------------------------------------------
      // Trennzeichen nach den Minuten
      case STATE_GETMINUTEDELIMITER:
        {
        State = STATE_GETMINUTE;   // um Code nicht mehrfach zu programmieren
        }
        break;

      }  // switch (State)

    cnt++;
    }  // while

  if (State == STATE_ERROR) {
    lmemset (pt, 0, sizeof(*pt));
    return FALSE;
    }
  else {
    pt->hour = BYTE(hour);
    pt->minute = BYTE(minute);
    pt->second = BYTE(second);
    pt->hundred_second = 0;
    
    return TRUE;  
    }
  }
#endif

DLLExport BOOL _export WINAPI writeTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt)
  {
  wsprintf (txt,"%02d:%02d:%02d",pt->hour,pt->minute,pt->second);
  return TRUE;
  }

BOOL IstSchaltjahr (int jahr)
  {
  return (((jahr % 4 == 0) && (jahr % 100 != 0)) || (jahr % 400 == 0)) ;
  }

DLLExport LONG _export WINAPI WievielterTagIstAschermittwoch (int jahr)
  {
  int ylp1 = jahr / 100 - jahr / 400 + 4 ;    // 27
  int ylp2 = ylp1 + 11 - jahr / 300 ;         // 32
  int r1 = ((jahr % 19) * 19 + ylp2) % 30 ;   // 2
  int r2 = ((jahr % 4) * 2 + 4 * jahr + 6 * r1 + ylp1) % 7 + r1 + 22 ; // (6 + 7980 + 12 + 27 = 8025) %7 (= 3) + 2 + 22 = 27 ; 
  if ((r2 == 57) ||
      ((r1 == 28) && (r2 == 56) && ((11 * (ylp2 + 1) % 30) < 19)))
    r2 = r2 - 7 ;
  if (IstSchaltjahr (jahr))
    r2 = r2 + 14 ;
  else
    r2 = r2 + 13 ;
  return LONG(r2);
  }

#pragma optimize ("",on)


