#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "date.hpp"
#include "globmem.h"
#define MODULENUM   57
#include "math.h"
#include "winass.hpp"

// $Header:   P:/marille/clinicum/dbhelp/rev/date.cpv   1.17   29 Jun 1999 18:28:56   Wolfgang  $
// $Log:   P:/marille/clinicum/dbhelp/rev/date.cpv  $
// 
//    Rev 1.17   29 Jun 1999 18:28:56   Wolfgang
// 1.) Geaenderte Datumsstringskonstanten.
// 
//    Rev 1.16   15 Jun 1999 16:23:16   WOLFGANG
// 1.) / als Datumstrennzeichen.
// 2.) Jahrhundert-Wechsel Handling.
// 3.) GetActTimeStr entfernt.
// 4.) Von DMWAPI nach DBHELP verschoben.
// 
//    Rev 1.15   29 Apr 1999 11:55:58   Martin
// StringFromDate liefert ab jetzt beinhart d.m.yyyy
// 
//    Rev 1.14   18 Nov 1998 15:48:38   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.13   05 Oct 1998 11:11:34   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.12   15 May 1998 10:37:50   Gerhold
// Zeitformate in Gro·schreibung lassen Eingaben > 24 Stunden zu
// 
//    Rev 1.11   02 Jul 1997 12:42:52   Hannes
// Kalenderwochen eingebaut
// 
//    Rev 1.10   22 Apr 1997 15:07:46   Hannes
// 
//    Rev 1.9   29 Jan 1997 18:16:12   HANNES
// 
//    Rev 1.8   08 Jan 1997 16:25:46   HANNES
// 
//    Rev 1.7   29 Nov 1996 09:02:10   HANNES
// 
//    Rev 1.6   02 Feb 1996 10:46:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   14 Aug 1995 17:05:34   HANNES
// 
//    Rev 1.4   10 Aug 1995 09:22:16   HANNES
// FormatDate,FormatTime
// 
//    Rev 1.3   21 Nov 1994 09:52:46   HANNES
// 
//    Rev 1.2   02 Oct 1994 17:00:00   HANNES
// Fehlerkorrektur in der numerischen Ausgabe des Monats
// 
//    Rev 1.1   25 Jul 1994 09:42:02   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:48:42   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.7   23 Feb 1994 18:22:02   HANNES
// Verschiedene kleine Fehlerkorrekturen in der Datumsinterpretation
// 
//    Rev 1.6   09 Feb 1994 14:07:06   HANNES
// Kleine verbesserungen an writeDateString
// 
//    Rev 1.5   04 Jan 1994 17:36:06   HANNES
// DatumsÅberprÅfung bei DateFromString
// 
//    Rev 1.4   10 Nov 1993 14:13:14   MARTIN
// Fehlerkorrekturen an DateFromString
// 
//    Rev 1.3   03 Nov 1993 17:45:54   HANNES
// Bindestriche in dem Datum
// 
//    Rev 1.2   07 Jun 1993 11:25:52   HANNES
// mylstrncpy
// 
//    Rev 1.1   07 Jun 1993 11:22:16   HANNES
// lstrncpy ...
// 
//    Rev 1.0   02 Jun 1993 19:32:14   HANNES
// Initial revision.
// 
//    Rev 1.4   22 Apr 1993 10:26:40   HANNES
// numStringFromDate..
// 
//    Rev 1.3   02 Mar 1993 22:31:36   HANNES
// Verbesserte Datumsroutinen
// 
//    Rev 1.2   22 Feb 1993 17:02:14   HANNES
// Kleine Verbesserungen, erweiterungen
// 
//    Rev 1.1   17 Feb 1993 15:22:04   HANNES
// Verbesserte Datumseingabe
// 
//    Rev 1.0   02 Dec 1992 15:23:14   HANNES
// Initial revision.

char MonthAbbr[12][4];
char MonthName[12][20];

#define MONTHNAMES      21000
#define MONTHABBR       21012

#define DAYNAMES        28900

extern HINSTANCE hLibInst;

inline void mylstrncpy (LPSTR dest,LPSTR source,int n)
  {
  lstrncpy (dest,source,n);
  }

void readMNames(void)
  {
  if (MonthAbbr[0][0] == '\0') {
    for (int i = 0 ; i < 12 ; i++) {
      char Instr[100];
      LoadString (hLibInst,MONTHABBR+i,Instr,sizeof(Instr));
      mylstrncpy (MonthAbbr[i],Instr,3);
      LoadString (hLibInst,MONTHNAMES+i,Instr,sizeof(Instr));
      mylstrncpy (MonthName[i],Instr,19);
      }
    }
  }

int FindSep (LPSTR txt)
  {
  // skip current separator field
  int res = 0 ;
  for ( ; ((txt[res] == ' ') || (txt[res] == '-') || (txt[res] == '.') || (txt[res] == '/')) && 
          (txt[res]) ; )
    res++;

  // search for next separator
  for ( ; txt[res] ; ) {
    if ((txt[res] == ' ') || (txt[res] == '-') || (txt[res] == '.') || (txt[res] == '/')) 
      break ;
    res ++ ;
    }
  if (txt[res] == '\0') res = -1 ;
  return res ;
  }

int FindSep1 (LPSTR txt)
  {
  // search for next separator '/'
  for ( int res = 0 ; txt[res] ; ) {
    if (txt[res] == '/') break ;
    res ++ ;
    }
  if (txt[res] == '\0') res = -1 ;
  return res ;
  }

inline BOOL IsDigit(char ch) 
  { 
  return ((ch >= '0') && (ch <= '9')) ; 
  }

void CopyField (LPSTR dest,LPSTR source,int Size)
  {
  for ( ; ((!IsDigit (*source)) && (*source)) ; ) source ++ ;
  mylstrncpy (dest,source,Size);
  }

LPSTR DeleteField (LPSTR txt)
  {
  for ( ; (IsDigit(*txt) && (*txt)) ; ) txt++ ;
  for ( ; (!IsDigit(*txt)) && (*txt) ; ) txt++ ;
  return txt ;
  }

int nDigits (LPSTR txt)
  {
  int res ;
  for ( res = 0 ; (*txt) && (IsDigit(*txt)) ; txt ++) res ++ ;
  return res;
  }

int AnsiUpperChar(int ch)
  {
  char txt[2];
  txt[0] = ch ;
  txt[1] = '\0' ;

#ifdef WIN32
  CharUpper (txt);
#else
  AnsiUpper(txt);
#endif

  return (txt[0]);
  }

int MatchMonthName (LPSTR txt,int balpha,int ealpha)
  {
  int j ;
  for (int i = 0 ; i < 12 ; i++) {

    BOOL noAbbr = FALSE ;
    for (j = 0 ; ; j++) {
      if ((balpha + j > ealpha) || (MonthAbbr[i][j] == '\0')) break ;
      if (AnsiUpperChar (txt[balpha + j]) != AnsiUpperChar (MonthAbbr[i][j])) {
        noAbbr = TRUE ;
        break ;
        }
      }
    if (!noAbbr) return i + 1;

    BOOL noName = FALSE ;
    for (j = 0 ; ; j++) {
      if ((balpha + j > ealpha) || (MonthName[i][j] == '\0')) break ;
      if (AnsiUpperChar (txt[balpha + j]) != AnsiUpperChar (MonthName[i][j])) {
        noName = TRUE ;
        break ;
        }
      }
    if (!noName) return i + 1;
    }
  return -1 ;           // nichts gefunden
  }

void InsChar (LPSTR txt,int ch,int pos)
  {
  int len = lstrlen (txt) ;
  LPSTR beg = txt + pos ;
  for (LPSTR h = txt + len ; h >= beg ; h --)
    *(h+1) = *h ;
  *beg = ch ;
  }

int ScanPosInt (LPSTR txt)
  {
  int res ;
  for ( res = 0 ; *txt ; txt++)
    if ((*txt >= '0') && (*txt <= '9')) res = res * 10 + *txt - '0' ;
    else return - 1;
  return res;
  }

int AnzDigits (LPSTR txt)
  {
  int res = 0;
  for ( ; *txt ; txt ++)
    if ((*txt >= '0') && (*txt <= '9')) res ++ ;
  return res;
  }

INTTIME LetzterMontagNullUhr (INTTIME T)
  {
  packdate pd ;
  UnPackTime (T,&pd);
  INTTIME T0 = PackTime (&pd);
  int wd = WeekDay (T0);
  return T0 - INTTIME(wd) * INTTIME(24L * 60L * 60L) ;
  }

INTTIME NaechsterMontagNullUhr (INTTIME T)
  {
  return LetzterMontagNullUhr (T) + (7L * 24L * 60L * 60L) ;
  }

INTTIME GetMontagNullUhr (int Jahr, int Woche)
  {
  packdate pd;
  pd.year = Jahr;
  pd.month = 1 ;
  pd.day = 1 ;
  INTTIME res = PackTime (&pd);
  int wd = WeekDay(res);
  if (wd < 4) 
    return LetzterMontagNullUhr (res + LONG(Woche - 1) * 7L * 24L * 60L * 60L);
  else
    return NaechsterMontagNullUhr (res + LONG(Woche - 1) * 7L * 24L * 60L * 60L);
  }

BOOL JahrHatDreiUndFuenfzigWochen (int Jahr)
  {
  packdate pd;
  pd.year = Jahr + 1 ;
  pd.month = 1 ;
  pd.day = 1 ;
  INTTIME pnext = PackTime (&pd);
  return (GetMontagNullUhr (Jahr, 53) + INTTIME (3L * 24L * 60L * 60L) < pnext);
  }

void WievielteWocheWelchesJahr (packdate FAR *dvar,int FAR *Jahr,int FAR *Woche)
  {
  packdate pd0;
  pd0.year = dvar->year ;
  pd0.month = 1 ;
  pd0.day = 1 ;
  int wd = WeekDay(PackTime (&pd0));
  INTTIME StartErsteWoche,T;
  if (wd < 4)  // ! Freitag,Samstag,Sonntag,Montag
    StartErsteWoche = LetzterMontagNullUhr (PackTime (&pd0));
  else
    StartErsteWoche = NaechsterMontagNullUhr (PackTime (&pd0));
  T = PackTime (dvar);
  if (StartErsteWoche > T) {
    pd0.year -- ;
    wd = WeekDay(PackTime (&pd0));
    if (wd < 4)   // Freitag,Samstag,Sonntag,Montag
      StartErsteWoche = LetzterMontagNullUhr (PackTime (&pd0));
    else
      StartErsteWoche = NaechsterMontagNullUhr (PackTime (&pd0));
    }
  *Jahr = pd0.year ;
  *Woche = int ((T - StartErsteWoche) / INTTIME (7L * 60L * 60L * 24L)) + 1 ;
  if ((*Woche == 53) && (!JahrHatDreiUndFuenfzigWochen (*Jahr))) {
    *Woche = 1;
    (*Jahr) ++ ;
    }
  }

void DatumVonJahrUndWoche (packdate FAR *pd,int Jahr,int Woche)
  {
  packdate pd0 ;
  pd0.year = Jahr ;
  pd0.month = 1 ;
  pd0.day = 1 ;
  int wd = WeekDay(PackTime (&pd0));
  INTTIME StartErsteWoche,T;
  if (wd < 4)   // Freitag,Samstag,Sonntag,Montag
    StartErsteWoche = LetzterMontagNullUhr (PackTime (&pd0));
  else
    StartErsteWoche = NaechsterMontagNullUhr (PackTime (&pd0));

  T = StartErsteWoche + INTTIME(Woche - 1) * 7L * 24L * 60L * 60L ;
  UnPackTime (T,pd);
  }

extern LPSTR WINAPI GetIniName ();
static BOOL MitKWLesen ()
  {
  static BOOL dmwGelesen,MitKW;
  if (!dmwGelesen) {
    dmwGelesen = TRUE;
    char retstr[32];
    GetPrivateProfileString ("Config","KWInDate","no",
                            retstr,sizeof(retstr),
                            GetIniName ()
                            );
    MitKW = (lstrcmp (retstr,"yes") == 0);
    }
  return MitKW;
  }

int GetCentury (int year, int futureYears)
  {
  packdate pd;
  UnPackTime (Now(), &pd);
  int centuryLimit = -1;
  int oldCentury = -1; 
  centuryLimit = pd.year % 100 + futureYears;
  if (centuryLimit > 100) {
    centuryLimit -= 100;
    oldCentury = pd.year / 100;
    }
  else
    oldCentury = pd.year / 100 - 1;
  if (year > centuryLimit)
    return oldCentury * 100;
  else
    return (oldCentury + 1) * 100;
  }

#define FUTURE_YEARS 5 // Wieviele Jahre in die Zukunft soll das neue Jahrhundert verwendet werden?

DLLExport BOOL _export WINAPI DateFromString (LPSTR inp,int format,packdate FAR *pd)
  {
  static BOOL FirstTime = TRUE;
  static int  minYear = 1800;
  
  if (FirstTime) {
    minYear   = GetPrivateProfileInt ("Config","MinYear",1800,GetIniName());
    FirstTime = FALSE;
    }

  int Year = 0; 
  int Month = 0; 
  int Day = 0;
  char Num[20];
  char buff[128];
  int N1;
  BOOL res = TRUE ;

  // Vorbereitungen
  lstrncpy (buff,inp,sizeof(buff) - 10);
  buff[sizeof(buff)-10] = '\0';
  LPSTR txt = buff;

  readMNames();

  // Find Field Separators, if any
  int Sep = FindSep (txt);

  // Find (1st) Alpha portion of string, if any
  int bAlpha,eAlpha;
  for (bAlpha = 0 ; txt[bAlpha] ; bAlpha++) {
    if (IsCharAlpha (txt[bAlpha])) {
      for (eAlpha = bAlpha ; txt[eAlpha] ; eAlpha ++)
        if (!IsCharAlpha (txt[eAlpha])) break;
      break ;
      }
    }

  if (txt[bAlpha] != '\0')
    // Text gefunden -> Monats ueberpruefung
    Month = MatchMonthName (txt,bAlpha,eAlpha);

  if (Sep < 0) { //??? / ist jetzt Datumsseperator!
    if (lstrlen(txt) < 4) {
      // Das kann ja wohl hoechstens eine Woche sein
      if (MitKWLesen ()) {
        int w = ScanPosInt (txt);
        if ((w >= 1) && (w <= 53)) {
          packdate pd0 ;
          UnPackTime (Now(),&pd0);
          DatumVonJahrUndWoche (pd,pd0.year,w);
          return TRUE ;
          }
        }
      return FALSE ; // war aber keine oder wir wollen sie nicht
      }
    else {
      InsChar (txt,'.',4);
      InsChar (txt,'.',2);
      Sep = 2 ;
      }
    }
  else if ((txt[Sep] == '/') && MitKWLesen () && (FindSep (txt + Sep) < 0)) {
    // das koennte auch eine Woche sein (kein 2. Trennzeichen!)
    lmemset (Num,'\0',sizeof(Num));
    mylstrncpy (Num,txt,Sep);
    int w = ScanPosInt (Num);
    int j = ScanPosInt (txt + Sep + 1);
    if ((j >= 0) && (j < 100)) {
      j += GetCentury (j, FUTURE_YEARS) ;
      }
    if ((j >= 0) && (w >= 1)) {
      DatumVonJahrUndWoche (pd,j,w);
      return TRUE ;
      }
    }

  // Now process the first number
  lmemset (Num,'\0',sizeof(Num));
  mylstrncpy (Num,txt,Sep);
  if (lstrlen(Num) > 4) return FALSE ;      // Ebenfalls Schwachsinn
  N1 = ScanPosInt (Num);
  if (N1 < 0) return FALSE ;               // -""-
  if (N1 > 100) Year = N1 ;
  else if (N1 > 31) Year = GetCentury (N1, FUTURE_YEARS) + N1 ;
  else {
    // Das format muss genauer befragt werden
    if (format == YMD)          Year = GetCentury (N1, FUTURE_YEARS) + N1 ;
    else if (format == DMY)     Day  = N1 ;
    else if (format == MDY)     Month = N1 ;
    }
  txt += Sep ; // OK, Done

  // remove any alpha field[s] and/or separators
  for ( ; (!IsDigit(*txt)) && (*txt) ; ) txt ++ ;
  if (*txt == '\0') return FALSE ;

  Sep = FindSep (txt) ;
  if (Sep > 0) {
    lmemset (Num,'\0',sizeof(Num));
    mylstrncpy (Num,txt,Sep) ;
    }
  else
    mylstrncpy (Num,txt,sizeof(Num)) ;

  if (lstrlen(Num) > 4) return FALSE ;

  N1 = ScanPosInt (Num);
  if (N1 < 0) return FALSE ;

  if (N1 >= 100) {
    if (Year > 0) return FALSE ;
    Year = N1 ;
    }
  else if (N1 > 31) {
    if (Year > 0) return FALSE ;
    Year = N1 + GetCentury (N1, FUTURE_YEARS) ;
    }
  else {
    if ((Year > 0) && (Month > 0))               Day = N1 ;
    else if ((format == YMD) || (format == DMY)) Month = N1 ;
    else if (format == MDY)                      Day = N1 ;
    }
    
  // remove this field and/or separator
  txt = DeleteField (txt);
  if (lstrlen(txt)) {
    // Immer noch nicht fertig
    CopyField (Num,txt,sizeof(Num)) ;
    if (lstrlen(Num) > 4) return FALSE ;
    N1 = ScanPosInt (Num) ;
    if (N1 < 0) return FALSE ;
    if (N1 >= 100) {
      if (Year > 0) return FALSE ;
      Year = N1 ;
      }
    else if (N1 > 31) {
      if (Year > 0) return FALSE ;
      Year = GetCentury (N1, FUTURE_YEARS) + N1 ;
      }
    else {
      if ((Year > 0) && (Month > 0)) Day = N1 ;
      else if ((format == MDY) || (format == DMY)) {
        if ((AnzDigits (Num) == 1) ||
            (((Month == 0) || (Day == 0)) && ((N1 == 19) || (N1 == 20))))        
          return FALSE ;
        Year = GetCentury (N1, FUTURE_YEARS) + N1 ;
        }
      else if (format == YMD)                      
        Day = N1 ;
      }
    }

  if (Year == 0) {
    // Kein Jahr? Dann nehmen wir halt das aktuelle
    packdate pd0 ;
    UnPackTime (Now(),&pd0);
    Year = pd0.year;
    }

  if ((Year == 0) || (minYear > Year) || (Month < 1) || (Month > 12) || (Day < 1) || (Day > DaysInMonth(Year,Month)))
    res = FALSE ;

  // Fertig
  pd->year = Year;
  pd->day = Day ;
  pd->month = Month ;

  return res ;
  }

DLLExport void _export WINAPI StringFromDate (LPSTR txt,int format,BOOL usename,BOOL useabbr,packdate FAR *pd)
  {
  FormatDate(txt,pd,"d.m.yyyy");   // beinhart !
#ifdef UEBERLEGT
  char daystr[20],monthstr[20],yearstr[20];
  wsprintf (daystr,"%d",pd->day);
  if ((useabbr) && (!usename))
    wsprintf (yearstr,"%2d",pd->year % 100);
  else
    wsprintf (yearstr,"%d",pd->year);

  unsigned int month = pd->month-1;
  if (month >= 12) month = 11;
  readMNames();
  if (usename)          lstrcpy (monthstr,MonthName[month]);
  else if (useabbr)     lstrcpy (monthstr,MonthAbbr[month]);
  else                  wsprintf (monthstr,"%d",pd->month);

  *txt = '\0' ;

  switch (format) {
    case DMY :
      lstrcat (txt,daystr);
      lstrcat (txt,".");
      lstrcat (txt,monthstr);
      if ((!usename) && (!useabbr))
        lstrcat (txt,".");
      else
        lstrcat (txt," ");
      lstrcat (txt,yearstr);
      break ;
    case MDY :
      lstrcat (txt,monthstr);
      lstrcat (txt," ");
      lstrcat (txt,daystr);
      lstrcat (txt,",");
      lstrcat (txt,yearstr);
      break ;
    case YMD :
      lstrcat (txt,monthstr);
      lstrcat (txt," ");
      lstrcat (txt,daystr);
      lstrcat (txt,",");
      lstrcat (txt,yearstr);
      break ;
    }
#endif
  }

DLLExport void _export WINAPI numStringFromDate (LPSTR txt,packdate FAR *pd)
  {
  char daystr[20],monthstr[20],yearstr[20];
  wsprintf (daystr,"%02d",pd->day);
  wsprintf (monthstr,"%02d",pd->month);
  wsprintf (yearstr,"%04d",pd->year);
  lstrcpy (txt,daystr);
  lstrcat (txt,monthstr);
  lstrcat (txt,yearstr);
  }

// Bearbeitung der Datums - Optionen
#ifdef UEBERLEGT
struct DATEOPT {
  int format ;
  BOOL useAbb;
  BOOL useName;
  } dateopt = { DMY , FALSE , TRUE } ;

class DOpt : public WDialog {
 public :
  DATEOPT dop;
  DOpt (HWND h) : WDialog (h,"DATEOPT") { memcpy (&dop,&dateopt,sizeof(dop)) ; }
  virtual BOOL WINAPI Init(HWND,UINT,WPARAM,LPARAM);             // Extra Init Method
  virtual BOOL WINAPI ExtraCommand(HWND,UINT,WPARAM,LPARAM);     // Intrprete Extra Commands
  };

#define ID_DMY  100
#define ID_MDY  101
#define ID_YMD  102
#define ID_UN   103
#define ID_UA   104

BOOL WINAPI DOpt::Init(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  if (dop.format == DMY) {
    CheckDlgButton (hWnd,ID_DMY,TRUE);
    CheckDlgButton (hWnd,ID_MDY,FALSE);
    CheckDlgButton (hWnd,ID_YMD,FALSE);
    }
  else if (dop.format == MDY) {
    CheckDlgButton (hWnd,ID_DMY,FALSE);
    CheckDlgButton (hWnd,ID_MDY,TRUE);
    CheckDlgButton (hWnd,ID_YMD,FALSE);
    }
  else if (dop.format == YMD) {
    CheckDlgButton (hWnd,ID_DMY,FALSE);
    CheckDlgButton (hWnd,ID_MDY,FALSE);
    CheckDlgButton (hWnd,ID_YMD,TRUE);
    }
  if (dop.useAbb)
    CheckDlgButton (hWnd,ID_UA,TRUE);
  else if (dop.useName)
    CheckDlgButton (hWnd,ID_UN,TRUE);
  return TRUE ;
  }

BOOL WINAPI DOpt::ExtraCommand(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  if (HIWORD(lP) == BN_DOUBLECLICKED) {
    switch (wP) {
      case ID_DMY :
        if (dop.format != DMY) {
          dop.format = DMY ;
          CheckDlgButton (hWnd,ID_DMY,TRUE);
          CheckDlgButton (hWnd,ID_MDY,FALSE);
          CheckDlgButton (hWnd,ID_YMD,FALSE);
          }
        break ;
      case ID_MDY :
        if (dop.format != MDY) {
          dop.format = MDY ;
          CheckDlgButton (hWnd,ID_DMY,FALSE);
          CheckDlgButton (hWnd,ID_MDY,TRUE);
          CheckDlgButton (hWnd,ID_YMD,FALSE);
          }
        break ;
      case ID_YMD :
        if (dop.format != YMD) {
          dop.format = YMD ;
          CheckDlgButton (hWnd,ID_DMY,FALSE);
          CheckDlgButton (hWnd,ID_MDY,FALSE);
          CheckDlgButton (hWnd,ID_YMD,TRUE);
          }
        break ;
      case ID_UA :
        if (dop.useAbb) {
          dop.useAbb = FALSE ;
          CheckDlgButton (hWnd,ID_UA,FALSE);
          }
        else {
          dop.useAbb = TRUE ;
          CheckDlgButton (hWnd,ID_UA,TRUE);
          dop.useName = FALSE ;
          CheckDlgButton (hWnd,ID_UN,FALSE);
          }
        break ;
      case ID_UN :
        if (dop.useName) {
          dop.useName = FALSE ;
          CheckDlgButton (hWnd,ID_UN,FALSE);
          }
        else {
          dop.useName = TRUE ;
          CheckDlgButton (hWnd,ID_UN,TRUE);
          dop.useAbb = FALSE ;
          CheckDlgButton (hWnd,ID_UA,FALSE);
          }
        break ;
      }
    return TRUE ;
    }
  return FALSE ;
  }

void GetDateOpt ()
  {
  DOpt d(WBase::hFrameWin);
  d.Go ();
  if (d.dostore)
    memcpy (&dateopt,&d.dop,sizeof(dateopt));
  }
#else

static int dop_format = DMY;
static int dop_useName = TRUE;
static int dop_useAbb = FALSE;

#endif


DLLExport BOOL _export WINAPI readDateStr (LPSTR txt,packdate FAR *pd)
  {
  char buffer[64];
  lstrncpy (buffer,txt,sizeof(buffer));
  return DateFromString (buffer,dop_format,pd);
  }

DLLExport void _export WINAPI writeDateStr (LPSTR txt,packdate FAR *pd)
  {
  StringFromDate (txt,dop_format,dop_useName,dop_useAbb,pd);
  }

DLLExport void _export WINAPI writeShortDateStr (LPSTR txt,packdate FAR *pd)
  {
  StringFromDate (txt,DMY,FALSE,TRUE,pd);
  }

DLLExport void _export WINAPI DiffYears (double FAR *res,packdate FAR *d1,packdate FAR *d0)
  {
  INTTIME t1 = PackTime(d1);
  INTTIME t0 = PackTime(d0);
  *res = floorl((t1 - t0) / INTTIME(365.0 * 24.0 * 60.0 * 60.0));
  }

DLLExport LPSTR _export WINAPI GetMonthName(int m)
  {
  readMNames();
  if (m < 1) m = 1 ;
  if (m > 12) m = 12 ;
  return MonthName[m - 1] ;
  }
DLLExport LPSTR _export WINAPI GetWeekDay(packdate FAR *pd)
  {
  int wd = WeekDay(PackTime (pd));
  static char WeekDays[7][20];
  static int  IsRead;
  if (!IsRead) {
    for (int i = 0 ; i < 7 ; i++)
      LoadString (hLibInst,DAYNAMES+i,WeekDays[i],20);
    IsRead = TRUE ;
    }
  return WeekDays[wd] ;
  }

LPSTR SkipSame (LPSTR h,int FAR *Anz)
  {
  char ch = *h ;
  *Anz = 0 ;
  for ( ; *h == ch ; h++) (*Anz)++ ;
  return h ;
  }

DLLExport void _export WINAPI FormatDate (LPSTR outtxt,packdate FAR *dvar,LPSTR format)
  {
  LPSTR h = outtxt;
  *h = '\0' ;
  int anz;
  for ( LPSTR f = format ; *f ; ) {
    switch (*f) {
      case 'w' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%.1s",GetWeekDay(dvar));
            break ;
          case 2 :
            wsprintf (h,"%.2s",GetWeekDay(dvar));
            break ;
          case 3 :
            wsprintf (h,"%s",GetWeekDay(dvar));
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      case 'd' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%d",dvar->day);
            break ;
          case 2 :
            wsprintf (h,"%02d",dvar->day);
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      case 'm' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%d",dvar->month);
            break ;
          case 2 :
            wsprintf (h,"%02d",dvar->month);
            break ;
          case 3 :
            wsprintf (h,"%3.3s",GetMonthName(dvar->month));
            break ;
          case 4 :
            wsprintf (h,"%s",GetMonthName(dvar->month));
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      case 'y' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 2 :
            wsprintf (h,"%02d",dvar->year % 100);
            break ;
          case 4 :
            wsprintf (h,"%d",dvar->year);
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      case 'k' :
        f ++ ;
        if (*f == 'w') {
          int Jahr,Woche;
          WievielteWocheWelchesJahr (dvar,&Jahr,&Woche);
          wsprintf (h,"%d/%d",Woche,Jahr % 100);
          }
        f ++ ;
        h += lstrlen (h);
        break ;
      default :
        *h++ = *f++ ;
        *h = '\0' ;
      }
    }
  }

DLLExport void _export WINAPI FormatTime (LPSTR outtxt,packtime FAR *tvar,LPSTR format)
  {
  LPSTR h = outtxt;
  *h = '\0';
  int anz;
  for ( LPSTR f = format ; *f ; ) {
    switch (*f) {
      case 'h' :
      case 'H' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%d",tvar->hour);
            break ;
          case 2 :
            wsprintf (h,"%02d",tvar->hour);
            break ;
          default :
            *h = '\0' ;
            break ;
          }
        h += lstrlen (h);
        break ;
      case 'm' :
      case 'M' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%d",tvar->minute);
            break ;
          case 2 :
            wsprintf (h,"%02d",tvar->minute);
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      case 's' :
      case 'S' :
        f = SkipSame (f,&anz);
        switch (anz) {
          case 1 :
            wsprintf (h,"%d",tvar->second);
            break ;
          case 2 :
            wsprintf (h,"%02d",tvar->second);
            break ;
          default :
            *h = '\0' ;
          }
        h += lstrlen (h);
        break ;
      default :
        *h++ = *f++ ;
        *h = '\0' ;
      }
    }
  }

