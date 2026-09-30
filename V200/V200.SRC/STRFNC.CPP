// $Header:   P:/marille/clinicum/rev/strfnc.cpv   1.67   23 Feb 2000 14:42:06   Martin  $
// $Log:   P:/marille/clinicum/rev/strfnc.cpv  $
// 
//    Rev 1.67   23 Feb 2000 14:42:06   Martin
// beim Runden Groschen abschneiden
// 
//    Rev 1.66   23 Feb 2000 12:30:58   Martin
// modifier 'r' bei %md eingebaut
// 
//    Rev 1.65   27 Sep 1999 17:26:36   WOLFGANG
// 1.) Exchange korrigiert (inString funktioniert auch bei \\).
// 
//    Rev 1.64   04 Mar 1999 18:34:32   Wolfgang
// 1.) %T eingebaut.
// 
//    Rev 1.63   22 Jan 1999 22:00:52   Hannes
// Texte vom StringBuffer / Fehlerkorrektur
// 
//    Rev 1.62   22 Jan 1999 17:54:14   Hannes
// local_str auf Stringbuffer umgestellt
// 
//    Rev 1.61   09 Oct 1998 18:13:14   Hannes
// Formtierungsfunktionen im Zusammenhang mit Farbformatierungen
// 
//    Rev 1.60   15 Sep 1998 20:05:44   Hannes
// WordInStr auch caseinsensitive
// 
//    Rev 1.59   23 Feb 1998 20:03:04   Hannes
// bCompareString .. FIRSTCUS-> Erster String als Suchstring (kurzer String)
// ausgezeichnet
// 
//    Rev 1.58   06 Feb 1998 08:02:56   Hannes
// ClearConnection bei ReplaceString
// 
//    Rev 1.57   24 Jan 1998 14:36:44   Martin
// Formaterweiterung 'L' fuer Dezimalzahlen (Vorzeichen Linksbuendig)
// 
//    Rev 1.56   05 Dec 1997 17:44:58   Hannes
// diverse Verbesserungen
// 
//    Rev 1.55   12 Nov 1997 16:34:08   Martin
// TextFromStrArray,ReallyExtractPath
// 
//    Rev 1.54   06 Oct 1997 17:10:22   WOLFGANG
// 1.) Ausgabe von qlong (long double) mittels Str_Printf und Floating Point
//     Formaten (als double).
// 
//    Rev 1.53   24 Sep 1997 21:03:24   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.52   14 Jul 1997 13:53:18   Martin
// Str_Scanf 32 Bit korrigiert
// 
//    Rev 1.51   08 Jul 1997 15:03:16   Hannes
// 
//    Rev 1.50   08 Jul 1997 11:59:04   Hannes
// 
//    Rev 1.49   20 Jun 1997 22:13:54   Hannes
// 
//    Rev 1.48   19 Jun 1997 12:43:00   Hannes
// Keine Ausgabe von Fragezeichen in strfnc
// 
//    Rev 1.47   27 May 1997 11:29:10   Hannes
// CheckWord: Wort darf mit '.' abgeschlossen werden
// 
//    Rev 1.46   10 Apr 1997 11:46:12   Hannes
// TakeFormatFrom
// 
//    Rev 1.45   14 Mar 1997 15:18:56   Martin
// Str_Printf und Str_Scanf 32 BIT faehig gemacht
// 
//    Rev 1.44   28 Feb 1997 14:47:00   Hannes
// Verbesserte Such und Replace Funktionen
// 
//    Rev 1.43   19 Nov 1996 12:30:54   HANNES
// 
//    Rev 1.42   08 Nov 1996 13:34:20   HANNES
// Verbesserte Zahlenformatierung
// 
//    Rev 1.41   21 Oct 1996 18:49:10   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.40   24 Sep 1996 12:43:50   MARTIN
// einige Fehler bei RNT - Umwandlungen korrigiert
// 
//    Rev 1.39   12 Sep 1996 23:12:28   HANNES
// MakeRNT,RemoveRNT
// 
//    Rev 1.38   06 Sep 1996 17:26:30   HANNES
// 
//    Rev 1.37   06 Sep 1996 12:19:58   HANNES
// 
//    Rev 1.36   08 Aug 1996 18:30:24   GERHOLD
// Str_Scanf ... optionaler Parameter Anzahl der konvertierten Zeichen
// 
//    Rev 1.35   23 Jul 1996 14:33:16   GERHOLD
// Ansixxx -> Charxxx ... 32 Bit-Funktionen
// FreeGlobmem in SplitPath raus!!!!
// 
//    Rev 1.34   04 Jun 1996 13:01:50   GERHOLD
// SplitPath
// 
//    Rev 1.33   13 Apr 1996 19:55:10   HANNES
// RemoveCRLF ... Auch letztes CRLF unterdrueckt.
// 
//    Rev 1.32   07 Mar 1996 18:40:56   GERHOLD
// RemoveCRLF
// 
//    Rev 1.31   02 Feb 1996 10:35:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.30   10 Jan 1996 18:20:20   HANNES
// RemoveFormatInfoFromString
// 
//    Rev 1.29   08 Jan 1996 16:49:22   MARTIN
// Endlosschleife raus
// 
//    Rev 1.28   05 Jan 1996 19:09:14   MARTIN
// kleine Korrektur in DivideIntoFormatStrings
// 
//    Rev 1.27   02 Nov 1995 19:09:10   martin
// RemoveSpaces korrigiert
// 
//    Rev 1.26   25 Oct 1995 12:23:14   HANNES
// Aenderungen Hannes
// 
//    Rev 1.25   16 Sep 1995 02:38:38   HANNES
// 
//    Rev 1.24   13 Sep 1995 01:22:32   HANNES
// 
//    Rev 1.23   24 Aug 1995 00:20:32   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.22   10 Aug 1995 09:24:38   HANNES
// FormatDate,FormatTime ausgelagert
// 
//    Rev 1.21   02 Aug 1995 10:07:40   HANNES
// Str_Scanf etwas erweitert
// 
//    Rev 1.20   31 Jul 1995 20:14:42   GERHOLD
// 
//    Rev 1.19   31 Jul 1995 18:42:38   GERHOLD
// 
//    Rev 1.18   31 Jul 1995 17:33:04   GERHOLD
// ein paar Veraenderungen in In_Str, Mid_Str
// 
//    Rev 1.17   31 Jul 1995 11:50:44   GERHOLD
// ein bisserl WORD-BASIC-Funktionen implementiert (InStr,MidStr,...)
// 
//    Rev 1.16   12 Apr 1995 12:26:34   HANNES
// 
//    Rev 1.15   05 Apr 1995 15:51:32   GERHOLD
// 
//    Rev 1.14   05 Apr 1995 13:36:08   HANNES
// 
//    Rev 1.13   30 Mar 1995 10:33:52   HANNES
// 
//    Rev 1.12   27 Mar 1995 13:17:20   HANNES
//  
// 
//    Rev 1.11   20 Mar 1995 12:05:54   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.10   24 Feb 1995 11:17:24   HANNES
//  
// 
//    Rev 1.9   29 Jan 1995 11:50:34   HANNES
// 
//    Rev 1.8   24 Jan 1995 11:01:54   HANNES
// 
//    Rev 1.7   20 Jan 1995 15:55:20   HANNES
// Str_Cat
// 
//    Rev 1.6   11 Dec 1994 14:48:56   HANNES
// RemoveFormatInfoFrom
// 
//    Rev 1.5   08 Dec 1994 22:06:16   HANNES
// 
//    Rev 1.4   11 Nov 1994 16:19:06   HANNES
// Scanf (%f)
// 
//    Rev 1.3   07 Sep 1994 10:51:50   HANNES
// Drucken von Zeitwerten
// 
//    Rev 1.2   05 Aug 1994 20:13:48   HANNES
// CatMultiString die ...
// 
//    Rev 1.1   05 Aug 1994 17:15:12   HANNES
// CatMultiString
// 
//    Rev 1.0   24 Jun 1994 17:05:24   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.15   03 Mar 1994 22:10:42   HANNES
// ExtractPath
// 
//    Rev 1.14   04 Feb 1994 15:11:10   MARTIN
// Str_Printf: neuer prefix fuer Strings: 'B' = 7bit_to_ansi (fuer DSYS)
// 
//    Rev 1.13   12 Jan 1994 11:12:18   HANNES
// Unnoetige Includes eleminiert
// 
//    Rev 1.12   16 Nov 1993 04:23:34   HANNES
// Anbindung an das DSYS
// 
//    Rev 1.11   03 Nov 1993 19:22:10   HANNES
// GetDigits
// 
//    Rev 1.10   18 Oct 1993 19:53:58   HANNES
// Verschiedene Charakter - Testfunktionen
// 
//    Rev 1.9   11 Oct 1993 12:20:04   HANNES
// ToUpper
// 
//    Rev 1.8   18 Aug 1993 10:28:42   HANNES
// HexDump, StrScanf in einer Vorversion
// 
//    Rev 1.7   05 Aug 1993 13:10:26   HANNES
// Str_scanf (vorerst nur rudimentaer)
// 
//    Rev 1.6   02 Jun 1993 19:53:44   HANNES
// Datumsfunktionen
// 
//    Rev 1.5   22 Apr 1993 10:26:52   HANNES
// Implementierung von %4D (= Aufruf von numStringFromDate)
// 
//    Rev 1.4   18 Apr 1993 22:56:42   MARTIN
// Str_Printf erweitert (%U/LOsS)
// 
//    Rev 1.3   17 Mar 1993 18:11:36   MARTIN
// 32 Bit Umstellung der Scripts
// 
//    Rev 1.2   08 Mar 1993 14:15:28   HANNES
// Fehlerkorrekturen
// 
//    Rev 1.1   02 Mar 1993 22:35:20   HANNES
// Datumseingaben, Nullzeiger
// 
//    Rev 1.0   20 Jan 1993 16:19:30   MARTIN
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>     // splitpath

#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 2
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "date.hpp"

#include "hash.hpp"
#include "compile.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "cfield.hpp"
#include "RegExpDLL.h"

typedef bool (*pfMatches) (char* pattern, char * matchText); //Imported from RegExpDLL
extern DLLExport LPSTR _export WINAPI GetExePath (void);

static HINSTANCE regExpDLL = NULL;
static pfMatches regExpMatch = NULL;

void LoadRegExpDLL()
  {
  if (!regExpDLL) {
    regExpDLL = LoadLibrary ("RegExpDLL.dll");
    if (regExpDLL == NULL) {
      char LibName[256];
      // ansonsten noch im EXE-Verzeichnis probieren
      lstrcpy(LibName, GetExePath());
      int len = lstrlen(LibName);
      if (LibName[len - 1] != '\\')
        LibName[len++] = '\\';
      lstrcpy(LibName + len, "RegExpDLL.dll");
      regExpDLL = LoadLibrary(LibName);
      }
    WIN_ASSERT_TEXT((regExpDLL != NULL),"Kann RegExpDLL.dll nicht laden !");

    regExpMatch = (pfMatches) GetProcAddress(regExpDLL,"?fMatches@@YA_NPAD0@Z");
    WIN_ASSERT_TEXT((regExpMatch != NULL),"Matches in RegExpDLL.dll nicht richtig definiert !");
    }
  }

#pragma pack(1)
struct Str_Cpy_par {
  WORD RecSize;
  WORD dstR;
  WORD dstI;
  WORD srcR;
  WORD srcI;
  };
#pragma pack()

BOOL Str_Cpy(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_Cpy_par FAR *par = (Str_Cpy_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    char FAR *src = (char FAR *)(c->ReadData(par->srcR, par->srcI));
    if (src != NULL) {
      LPSTR dst = LPSTR (GetGlobMem (lstrlen(src)+1));
      lstrcpy (dst,src);
      c->WriteData(par->dstR, par->dstI, dst, lstrlen(dst)+1, Offset);
      FreeGlobMem (dst);
      }
    else
      c->DelData(par->dstR,par->dstI,Offset);
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->srcR, par->srcI, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->srcR, par->srcI, Offset);
    }

  return FALSE;
  }


BOOL StrRemoveFormat(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_Cpy_par FAR *par = (Str_Cpy_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    char FAR *src = (char FAR *)(c->ReadData(par->srcR, par->srcI));
    if (src != NULL) {
      LPSTR dst = RemoveFormatInfoFromString (src);
      if (dst != NULL) {
        c->WriteData(par->dstR, par->dstI, dst, GetBlockSize (dst), Offset);
        FreeGlobMem (dst);
        }
      else
        c->DelData(par->dstR,par->dstI,Offset);
      }
    else
      c->DelData(par->dstR,par->dstI,Offset);
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->srcR, par->srcI, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->srcR, par->srcI, Offset);
    }

  return FALSE;
  }


#pragma pack(1)
struct Str_Cat_par {
  WORD RecSize;
  WORD dstR;
  WORD dstI;
  WORD src1R;
  WORD src1I;
  WORD src2R;
  WORD src2I;
  };
#pragma pack()


BOOL Str_Cat(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_Cat_par FAR *par = (Str_Cat_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    char FAR *src1 = (char FAR *)(c->ReadData(par->src1R, par->src1I));
    char FAR *src2 = (char FAR *)(c->ReadData(par->src2R, par->src2I));
    int size = 1, size1 = 0;
    if (src1 != NULL)
      size += size1 = lstrlen(src1);
    if (src2 != NULL)
      size += lstrlen(src2);
    if ((src1 != NULL) || (src2 != NULL)) {
      LPSTR dst = LPSTR (GetGlobMem (size));
      if (src1 != NULL)
        lstrcpy (dst, src1);
      if (src2 != NULL)
        lstrcpy (dst + size1, src2);
      c->WriteData(par->dstR, par->dstI, dst, size, Offset);
      FreeGlobMem (dst);
      }
    else
      c->DelData(par->dstR, par->dstI, Offset);
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->src1R, par->src1I, Offset);
    c->SetConnection (par->src2R, par->src2I, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->src1R, par->src1I, Offset);
    c->ClearConnection (par->src2R, par->src2I, Offset);
    }

  return FALSE;
  }


#pragma pack(1)
struct Str_Printf_par {
  WORD RecSize;
  WORD dstR;
  WORD dstI;
  WORD frmR;
  WORD frmI;
  struct {
    WORD R;
    WORD I;
    } Ref[1];
  };
#pragma pack()


static void HexDump (LPSTR ptr,LPSTR data)
  {
  int size = GetBlockSize (data);
  for (int i = 0 ; i < 2 * size ; i ++) {
    int nibble = !(i % 2) ;
    char h = data[size - 1 - i / 2];
    if (nibble)
      h = h >> 4 ;
    h = h & 0x0F ;
    if (h <= 9)
      ptr[i] = h + '0' ;
    else
      ptr[i] = h - 10 + 'A' ;
    }
  ptr[i] = '\0';
  }


static void SevenBitToOem(LPSTR sbit, LPSTR oem)
  {
  while ((*oem = *sbit++) != '\0') {
    switch (*oem) {
      case '{':  *oem = '„';  break;
      case '|':  *oem = '”';  break;
      case '}':  *oem = '';  break;
      case '[':  *oem = 'Ž';  break;
      case '\\': *oem = '™';  break;
      case ']':  *oem = 'š';  break;
      case '~':  *oem = 'á';  break;
      }
    oem++;
    }
  }


static void InsertSpaces(LPSTR dst, LPSTR src)
  {
  LPSTR lastspace = dst;
  while (*src) {
    if ((*dst++ = *src++) == ' ') {
      lastspace = dst - 1;
      *dst++ = ' ';    // bei einem Space noch zwei Spaces Extra
      *dst++ = ' ';
      }
    else
      lastspace = dst;
    *dst++ = ' ';
    }
  *lastspace = '\0';   // Spaces am Ende entfernen
  }


void VorzeichenLinksbuendig(LPSTR ptr)
  {
  LPSTR str = ptr;
  BOOL UngleichNull = FALSE;
  BOOL Plus = FALSE;
  BOOL Minus = FALSE;
  char ch;
  while ((ch = *str++) != '\0') {
    if ((ch >= '1') && (ch <= '9'))
      UngleichNull = TRUE;
    if (ch == '+') {
      Plus = TRUE;
      str[-1] = ' ';
      }
    if (ch == '-') {
      Minus = TRUE;
      str[-1] = ' ';
      }
    }
  if (UngleichNull) {
    if (Plus) ptr[0] = '+';
    if (Minus) ptr[0] = '-';
    }
  }

static GLOBALHANDLE hGStrBuffer;
static LPSTR _StrBuffer;
#define MAXSTRSIZE      0x8000
#define LOCALSTR_OFFS   (MAXSTRSIZE / 2)
LPSTR StrBuffer()
  {
  return _StrBuffer;
  }
void ResetStrBuffer ()
  {
  if (_StrBuffer == NULL) {
    hGStrBuffer = GlobalAlloc (GMEM_MOVEABLE,MAXSTRSIZE);
    _StrBuffer = LPSTR (GlobalLock (hGStrBuffer)) + sizeof(WORD);
    }
  ((WORD FAR *) _StrBuffer)[-1] = 0;
  }

BOOL Str_Printf(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_Printf_par FAR *par = (Str_Printf_par FAR *)param;
  int num_pars = (par->RecSize - (sizeof(Str_Printf_par) - sizeof(DWORD))) / sizeof(DWORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    char FAR *frm = (char FAR *)(c->ReadData(par->frmR, par->frmI));
    if (frm != NULL) {
      LONG FAR *data;
      int parnum = 0;
      char format[20];
      char *fptr;
      int is_long, do_lower, do_upper, do_oem, do_ansi, do_7bit, do_space,
          is_money, is_zahl, do_round;
      char ch;
      ResetStrBuffer ();
      LPSTR dst = StrBuffer();
      char *ptr = dst;
      do {
        ch = *frm++;
        if (ch == '%') {
          ch = *frm++;
          if ((ch == '%') || (parnum >= num_pars)) {
            *ptr++ = ch;
            }
          else {
            data = (LONG FAR *)(c->ReadData(par->Ref[parnum].R, par->Ref[parnum].I));
            *ptr = '\0';
            fptr = format;
            is_long = FALSE;
            do_lower = FALSE;
            do_upper = FALSE;
            do_oem = FALSE;
            do_ansi = FALSE;
            do_space = FALSE;
            do_7bit = FALSE;
            do_round = FALSE;
            is_money = FALSE;
            *fptr++ = '%';
            int frm_end = FALSE;
            do {
              switch (ch) {
                case '\0':
                  frm_end = TRUE;    // illegale Formatangabe
                  break;
                case 'p':
                  *ptr++ = '%';
                  *ptr++ = 'p';
                  frm_end = TRUE;
                  break;
                case 's':
                  {
                  *fptr++ = ch;
                  *fptr = '\0';
                  LPSTR local_str = StrBuffer() + LOCALSTR_OFFS;
                  if (data != NULL) {
                    if (do_space)
                      InsertSpaces(local_str, (char FAR *)data);
                    else
                      lstrcpy(local_str, (char FAR *)data);
                    }
                  else {
                    local_str[0] = '\0';
                    }
                  if (do_ansi) {
                    LPSTR old = LPSTR (GetGlobMem (lstrlen (local_str) + 1)) ;
                    lstrcpy (old,local_str);
                    OemToAnsi(local_str, local_str);
                    for (int k = 0 ; ; k++) {
                      if (old[k]) {
                        if (old[k] == 'í') local_str[k] = 'ø' ;
                        }
                      else
                        break ;
                      }
                    FreeGlobMem (old);
                    }
                  else if (do_7bit) {
                    SevenBitToOem(local_str, local_str);
                    OemToAnsi(local_str, local_str);
                    }
                  if (do_lower) {
                    AnsiLower(local_str);
                    }
                  else if (do_upper) {
#ifdef WIN32
                    CharUpper(local_str);
#else
                    AnsiUpper(local_str);
#endif
                    }
                  if (do_oem) {
                    AnsiToOem(local_str, local_str);
                    }
                  sprintf(ptr, format, local_str);
                  }
                  frm_end = TRUE;
                  break;
                case 'S':
                  {
                  *fptr++ = 's';
                  *fptr = '\0';
                  LPSTR local_str = StrBuffer() + LOCALSTR_OFFS;
                  if ((parnum < (num_pars - 1)) && (data != NULL)) {
                    parnum++;
                    LPSTR strfield = (LPSTR)(c->ReadData(par->Ref[parnum].R, par->Ref[parnum].I));
                    if (strfield != NULL) {
                      WORD index = *((WORD FAR *)data);
                      LPSTR ht;
                      for (int i = 0 ; i < int (index) ; i++) {
                        for (ht = strfield ; *ht ; ht++) ;
                        ht++;
                        if (*ht == '\0') break ;
                        strfield = ht ;
                        }
                      if (do_space)
                        InsertSpaces(local_str, strfield);
                      else
                        lstrcpy(local_str, strfield);
                      }
                    else
                      strcpy(local_str, "???");
                    }
                  else
                    strcpy (local_str, "???");
                  if (do_ansi) {
#ifdef WIN32
                    OemToChar(local_str, local_str);
#else
                    OemToAnsi(local_str, local_str);
#endif
                    }
                  else if (do_7bit) {
                    SevenBitToOem(local_str, local_str);
#ifdef WIN32
                    OemToChar(local_str, local_str);
#else
                    OemToAnsi(local_str, local_str);
#endif
                    }
                  if (do_lower) {
#ifdef WIN32
                    CharLower(local_str);
#else
                    AnsiLower(local_str);
#endif
                    }
                  else if (do_upper) {
#ifdef WIN32
                    CharUpper(local_str);
#else
                    AnsiUpper(local_str);
#endif
                    }
                  if (do_oem) {
#ifdef WIN32
                    CharToOem(local_str, local_str);
#else
                    AnsiToOem(local_str, local_str);
#endif
                    }
                  sprintf(ptr, format, local_str);
                  }
                  frm_end = TRUE;
                  break;
                case 'e':
                case 'E':
                case 'f':
                case 'g':
                case 'G':
                  if (data != NULL) {
                    if (GetBlockSize (data) == sizeof(long double)) {
                      *fptr++ = ch;
                      *fptr = '\0';
                      sprintf(ptr, format,double(*((long double FAR *)data)));
                      if (do_lower)
                        VorzeichenLinksbuendig(ptr);
                      }
                    else {
                      if (*((float FAR *) data) < 1.0E9) {
                        *fptr++ = ch;
                        *fptr = '\0';
                        sprintf(ptr, format,double(*((float FAR *)data)));
                        if (do_lower)
                          VorzeichenLinksbuendig(ptr);
                        }
                      }
                    }
                  // else
                  //  strcpy (ptr,"???");
                  frm_end = TRUE;
                  break;
                case 'D':   // Datumsausgabe
                  {
                  BOOL useName;
                  BOOL useAbbr;
                  int datformat;
                  *fptr = '\0';
                  BOOL useNum = FALSE ;
                  switch (format[1]) {
                    case '0' :
                      datformat = DMY ;
                      useName = TRUE ;
                      useAbbr = FALSE ;
                      break;
                    case '1' :
                      datformat = DMY ;
                      useName = FALSE ;
                      useAbbr = TRUE ;
                      break;
                    case '2' :
                      datformat = DMY ;
                      useName = FALSE ;
                      useAbbr = FALSE ;
                      break;
                    case '3' :
                      datformat = YMD ;
                      useName = FALSE ;
                      useAbbr = FALSE ;
                      break;
                    case '4' :
                      useNum = TRUE ;
                      break ;
                    }
                  if (data != NULL) {
                    packdate pdl;
                    lmemcpy (&pdl,data,sizeof(pdl));
                    if (useNum)
                      numStringFromDate (ptr,&pdl);
                    else
                      StringFromDate (ptr,datformat,useName,useAbbr,&pdl);
                    }
                  }
                  frm_end = TRUE;
                  break ;
                case 'T':   // Zeitausgabe
                  {
                  if (data != NULL) {
                    packtime pdt;
                    lmemcpy (&pdt,data,sizeof(pdt));
                    writeTimeStr (ptr, 0, &pdt);
                    }
                  }
                  frm_end = TRUE;
                  break ;
                case 'c':
                case 'i':
                case 'u':
                case 'o':
                case 'x':
                case 'X':
                case 'd':
                  if (ch == 'd')
                    is_zahl = TRUE ;
                  *fptr++ = ch;
                  *fptr = '\0';
                  if (data != NULL) {
                    if (do_lower) {
                      HexDump (ptr,LPSTR (data));
                      }
                    else {
                      if ((is_long) && (is_zahl) && 
                          ((lstrcmp (format,"%ld") == 0) || (lstrcmp (format,"%l.d") == 0)) ||
                          ((lstrcmp (format,"%+ld") == 0) || (lstrcmp (format,"%+l.d") == 0))
                         ) {
                        BOOL doT = ((lstrcmp (format,"%l.d") == 0) || (lstrcmp (format,"%+l.d") == 0)) ;
                        BOOL mitVorzeichen = FALSE ;
                        if (format[1] == '+') mitVorzeichen = TRUE ;
                        LPSTR rptr ;
                        if ((mitVorzeichen) && ((*(long FAR *) data) >= 0L)) {
                          ptr[0] = '+' ;
                          rptr = ptr + 1 ;
                          }
                        else
                          rptr = ptr ;
                        GetLongStr(rptr,*(long FAR *) data,doT);
                        }
                      else if (is_long)
                        sprintf(ptr, format, *data);
                      else if (is_money) {
                        BOOL mitVorzeichen = FALSE ;
                        if (format[1] == '+')
                          mitVorzeichen = TRUE ;
                        else
                          mitVorzeichen = FALSE ;
                        LPSTR rptr = ptr;
                        if (GetBlockSize (data) == sizeof(long double)) {
                          if ((mitVorzeichen) && ((*(long FAR *) data) >= 0L)) {
                            ptr[0] = '+' ;
                            rptr = ptr + 1 ;
                            }
                          long wert = (long) (*(long double FAR *) data);
                          if (do_round)
                            wert = ((wert + 50L) / 100L) * 100L;
                          GetMoneyStr (rptr,wert);
                          if (do_round) {
                            int len = strlen(rptr);
                            if (len > 3)
                              rptr[len-3] = '\0';
                            }
                          }
                        else {
                          if ((mitVorzeichen) && ((*(long FAR *) data) >= 0L)) {
                            ptr[0] = '+' ;
                            rptr = ptr + 1 ;
                            }
                          long wert = *data;
                          if (do_round)
                            wert = ((wert + 50L) / 100L) * 100L;
                          GetMoneyStr (rptr,wert);
                          if (do_round) {
                            int len = strlen(rptr);
                            if (len > 3)
                              rptr[len-3] = '\0';
                            }
                          }
                        }
                      else
                        sprintf(ptr, format, int(*((short FAR *)data)));
                      }
                    }
                  frm_end = TRUE;
                  break;
                case 'L':  // prefix fuer String: to_lower
                  do_lower = TRUE;
                  do_upper = FALSE;
                  ch = *frm++;
                  break;
                case 'U':  // prefix fuer String: to_upper
                  do_lower = FALSE;
                  do_upper = TRUE;
                  ch = *frm++;
                  break;
                case 'O':  // prefix fuer String: ansi_to_oem
                  do_oem = TRUE;
                  ch = *frm++;
                  break;
                case 'A':  // prefix fuer String: oem_to_ansi
                  do_ansi = TRUE;
                  ch = *frm++;
                  break;
                case ' ':  // prefix fuer String: Spaces einfuegen
                  do_space = TRUE;
                  ch = *frm++;
                  break;
                case 'B':  // prefix fuer String: 7bit_to_ansi
                  do_7bit = TRUE;
                  ch = *frm++;
                  break;
                case 'm':
                  is_money = TRUE ;
                  *fptr++ = ch;
                  ch = *frm++;
                  break ;
                case 'r':  // prefix fuer %md: rounded
                  do_round = TRUE;
                  ch = *frm++;
                  break;
                case 'l':
                  is_long = TRUE;
                default:
                  *fptr++ = ch;
                  ch = *frm++;
                }
              } while (!frm_end);
            ptr += strlen(ptr);
            parnum++;
            }
          }
        else {
          *ptr++ = ch;
          }
        } while (ch != '\0');
      c->WriteData(par->dstR, par->dstI, dst, strlen(dst)+1, Offset);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->frmR, par->frmI, Offset);
    for (int i = 0; i < num_pars; i++)
      c->SetConnection (par->Ref[i].R, par->Ref[i].I, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->frmR, par->frmI, Offset);
    for (int i = 0; i < num_pars; i++)
      c->ClearConnection (par->Ref[i].R, par->Ref[i].I, Offset);
    }

  return FALSE;
  }

#pragma pack(1)
struct Str_Scanf_param {
  WORD parSize;
  DWORD txt;
  DWORD format;
  DWORD res;
  DWORD nConverted;        // Anzahl der erfolgreich formatierten Zeichen
  };
#pragma pack()

/*-----------------------------------
**  Einschraenkungen:
**  - Nur Formatstring ohne zwischengestreute Texte o. Spaces etc.
**  - Nur ein Resultat
**  - eingeschraenkter Format - Bereich: lX,f,d,X,u,ld,D(Datum),LX(beliebig langer hex. String)
**-------------------------------------*/
BOOL Str_Scanf (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    Str_Scanf_param FAR * par = (Str_Scanf_param FAR *) param;
    LPSTR format = LPSTR (c->ReadlData (par->format));
    LPSTR txt = LPSTR (c->ReadlData (par->txt));
    int count = 0;
    if (lstrcmp (format,"%lX") == 0) {
      if ((txt != NULL) && (*txt)) {
        DWORD res;
        char ltxt[128];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        if (sscanf (ltxt,"%lX%n",&res,&count) == 1)
          c->WritelData (par->res,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%f") == 0) {
      if ((txt != NULL) && (*txt)) {
        float res;
        char ltxt[128];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        for ( LPSTR h = ltxt ; *h ; h++ ) {
          if (*h == ',') *h = '.' ;
          }
        if (sscanf (ltxt,"%f%n",&res,&count) == 1)
          c->WritelData (par->res,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%d") == 0) {
      if ((txt != NULL) && (*txt)) {
        int res;
        char ltxt[128];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        if (sscanf (ltxt,"%d%n",&res,&count) == 1) {
          short sres = (short)res;
          c->WritelData (par->res,&sres,sizeof(sres),LPSTR(param) - sizeof(WORD));
          }
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%X") == 0) {
      if ((txt != NULL) && (*txt)) {
        int res;
        char ltxt[128];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        if (sscanf (ltxt,"%X%n",&res,&count) == 1) {
          short sres = (short)res;
          c->WritelData (par->res,&sres,sizeof(sres),LPSTR(param) - sizeof(WORD));
          }
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%u") == 0) {
      if ((txt != NULL) && (*txt)) {
        unsigned res;
        char ltxt[128];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        if (sscanf (ltxt,"%u%n",&res,&count) == 1) {
          unsigned short sres = (unsigned short)res;
          c->WritelData (par->res,&sres,sizeof(sres),LPSTR(param) - sizeof(WORD));
          }
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%ld") == 0) {
      if ((txt != NULL) && (*txt)) {
        DWORD res;
        char ltxt[64];
        lstrncpy (ltxt,txt,sizeof(ltxt) - 1);
        if (sscanf (ltxt,"%ld%n",&res,&count) == 1)
          c->WritelData (par->res,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
        else
          c->DellData (par->res,LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%LX") == 0) {
      LPSTR x = txt ;
      BOOL done = FALSE ;
      if ((txt != NULL) && (*txt)) {
        for (int len = 0 ; ((*x) && 
                  (((*x >= '0') && (*x <= '9')) ||
                  ((*x >= 'A') && (*x <= 'F')))) ; len ++ , x++ ) ;
        if ((len > 0) && ((len % 2) == 0)) {
          int size = len / 2 ;
          LPSTR h = LPSTR (GetGlobMem (size));
          for ( int i = 0 ; i < len ; i++) {
            char x;
            if ((txt[i] >= '0') && (txt[i] <= '9'))
              x = txt[i] - '0' ;
            else
              x = txt[i] - 'A' + 10 ;
            char y = h[size - i / 2 - 1];
            if (i % 2 == 0)
              y = x << 4 ;
            else
              y = y | x ;
            h[size - i / 2 - 1] = y ;
            }
          c->WritelData (par->res,h,size,LPSTR(param) - sizeof(WORD));
          count = lstrlen(h);
          done = TRUE ;
          }
        }
      if (!done)
        c->DellData (par->res,LPSTR(param) - sizeof(WORD));
      }
    else if (lstrcmp (format,"%D") == 0) {
      packdate pd;
      if ((txt != NULL) && (*txt) && (readDateStr(txt,&pd)))
        c->WritelData (par->res,&pd,sizeof(pd),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else if ((lstrcmp (format,"%T") == 0) || (lstrcmp (format,"%24T") == 0)) {
      packtime pt;
      int timeFormat;
      if (lstrcmp (format,"%24T") == 0)
        timeFormat = 0;
      else
        timeFormat = 1;
      if ((txt != NULL) && (*txt) && (readTimeStr(txt,timeFormat,&pt)))
        c->WritelData (par->res,&pt,sizeof(pt),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else {
      DBWIN_ASSERT(FALSE);
      }

    if (par->parSize > sizeof(par->parSize) + 3 * sizeof(DWORD)) {
      unsigned short scount = (unsigned short)count;
      c->WritelData (par->nConverted,&scount,sizeof(scount),LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    Str_Scanf_param FAR * par = (Str_Scanf_param FAR *) param;
    c->SetlConnection (par->txt,LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Str_Scanf_param FAR * par = (Str_Scanf_param FAR *) param;
    c->ClearlConnection (par->txt,LPSTR(par) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct Code128bc_par {
  WORD  RecSize;
  WORD  dstR;
  WORD  dstI;
  WORD  srcR;
  WORD  srcI;
  DWORD blankChar;
  };
#pragma pack()

static int CODEBLANK = 207; //194 for standard? or 207 for Code128

/**
 * tests if all there are mini numeric characters in chaein, beginning from
 * position i
 * 
 * @param chaine
 * @param i
 * @param mini
 * @return
 */
BOOL testnum(char *ptr, int plen, int i, int mini) {
		if (i + mini <= plen) {
			for (int j = i; j < i + mini; j++) {
				int currentChar = (int) ptr[j];
				if (!((48 <= currentChar) && (currentChar <= 57)))
					return FALSE;
			}
			return TRUE;
		} else
			return FALSE;
	}

#ifdef Source
Public Function Code128$(chaine$)
  'V 1.0
  'Paramètres : une chaine
  'Retour : * une chaine qui, affichée avec la police CODE128.TTF, donne le code barre
  '         * une chaine vide si paramètre fourni incorrect
  Dim i%, checksum&, mini%, dummy%, tableB As Boolean
  Code128$ = ""
  If Len(chaine$) > 0 Then
  'Vérifier si caractères valides
    For i% = 1 To Len(chaine$)
      Select Case Asc(Mid$(chaine$, i%, 1))
      Case 32 To 126
      Case Else
        i% = 0
        Exit For
      End Select
    Next
    'Calculer la chaine de code en optimisant l'usage des tables B et C
    Code128$ = ""
    tableB = True
    If i% > 0 Then
      i% = 1 'i% devient l'index sur la chaine
      Do While i% <= Len(chaine$)
        If tableB Then
          'Voir si intéressant de passer en table C
          'Oui pour 4 chiffres au début ou à la fin, sinon pour 6 chiffres
          mini% = IIf(i% = 1 Or i% + 3 = Len(chaine$), 4, 6)
          GoSub testnum
          If mini% < 0 Then 'Choix table C
            If i% = 1 Then 'Débuter sur table C
              Code128$ = Chr$(205)
            Else 'Commuter sur table C
              Code128$ = Code128$ & Chr$(199)
            End If
            tableB = False
          Else
            If i% = 1 Then Code128$ = Chr$(204) 'Débuter sur table B
          End If
        End If
        If Not tableB Then
          'On est sur la table C, essayer de traiter 2 chiffres
          mini% = 2
          GoSub testnum
          If mini% < 0 Then 'OK pour 2 chiffres, les traiter
            dummy% = Val(Mid$(chaine$, i%, 2))
            dummy% = IIf(dummy% < 95, dummy% + 32, dummy% + 100)
            Code128$ = Code128$ & Chr$(dummy%)
            i% = i% + 2
          Else 'On n'a pas 2 chiffres, repasser en table B
            Code128$ = Code128$ & Chr$(200)
            tableB = True
          End If
        End If
        If tableB Then
          'Traiter 1 caractère en table B
          Code128$ = Code128$ & Mid$(chaine$, i%, 1)
          i% = i% + 1
        End If
      Loop
      'Calcul de la clé de contrôle
      For i% = 1 To Len(Code128$)
        dummy% = Asc(Mid$(Code128$, i%, 1))
        dummy% = IIf(dummy% < 127, dummy% - 32, dummy% - 100)
        If i% = 1 Then checksum& = dummy%
        checksum& = (checksum& + (i% - 1) * dummy%) Mod 103
      Next
      'Calcul du code ASCII de la clé
      checksum& = IIf(checksum& < 95, checksum& + 32, checksum& + 100)
      'Ajout de la clé et du STOP
      Code128$ = Code128$ & Chr$(checksum&) & Chr$(206)
    End If
  End If
  Exit Function
testnum:
  'si les mini% caractères à partir de i% sont numériques, alors mini%=0
  mini% = mini% - 1
  If i% + mini% <= Len(chaine$) Then
    Do While mini% >= 0
      If Asc(Mid$(chaine$, i% + mini%, 1)) < 48 Or Asc(Mid$(chaine$, i% + mini%, 1)) > 57 Then Exit Do
      mini% = mini% - 1
    Loop
  End If
Return
End Function
#endif

/**
 * @return a string which give the bar code when it is displayed with
 *         CODE128.TTF font an empty string if the supplied parameter is no
 *         good
 */
BOOL Code128bc(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Code128bc_par FAR *par = (Code128bc_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    char FAR *src = (char FAR *)(c->ReadData(par->srcR, par->srcI));
    if (src != NULL) {
      ResetStrBuffer ();
      LPSTR dst = StrBuffer();
      char *ptr = dst;
      
      int srclen = lstrlen(src);
      
      int blankChar = CODEBLANK;
      LPVOID blankCharPtr = c->ReadlData (par->blankChar);
      if (blankCharPtr != NULL)
        blankChar = c->ReadConstInt (par->blankChar);

      if (srclen > 0) {
        BOOL isValidChars = TRUE;
    		// Check for valid characters
    		for (int i = 0; i < srclen; i++) {
    			int currentChar = src[i];
    			if (!((32 <= currentChar) && (currentChar <= 126)))
    				isValidChars = FALSE;
    		}
    
        if (isValidChars) {    
      		// Calculation of the code string with optimized use of tables B and C
          
          int plen = 0;
          
      		boolean tableB = TRUE;
      		int i = 0;
      		while (i < srclen) {
      			if (tableB) {
      				// See if interesting to switch to table C
      				// yes for 4 digits at start or end, else if 6 digits
      				if (testnum(src, srclen, i, ((i == 0) || (i + 4 == srclen)) ? 4 : 6)) {
      					if (i == 0)
      						ptr[plen++] = (char) 205; // Starting with table C
      					else
      						ptr[plen++] = (char) 199; // Switch to table C
      					tableB = FALSE;
      				} else if (i == 0)
      					ptr[plen++] = (char) 204; // Starting with table B
      			}
      			
            if (!tableB) {
      				// We are on table C, try to process 2 digits
      				if (testnum(src, srclen, i, 2)) {
      					// OK for 2 digits, process it
      					int td = (int) (src[i] - '0');
      					td = td * 10 + (int) (src[i + 1] - '0');
      					td = td < 95 ? td + 32 : td + 100;
      					td = td == 32 ? blankChar : td;
      					ptr[plen++] = (char) td;
      					i = i + 2;
      				} else {
      					// We haven't 2 digits, switch to table B
      					ptr[plen++] = (char) 200; // Switch to table B
      					tableB = TRUE;
      				}
      			}
      
      			if (tableB) {
      				// Process 1 digit with table B
      				int currentChar = (int) src[i];
      				currentChar = currentChar == 32 ? blankChar : currentChar;
      				ptr[plen++] = (char) currentChar;
      				i = i + 1;
      			}
      		}
      
      		int checkSumm = 0;
      		for (i = 0; i < plen; i++) {
      			int currentChar = ((int) dst[i] + 256) % 256;
      			if (currentChar == blankChar)
      				currentChar = 32;
    				currentChar = currentChar < 127 ? currentChar - 32 : currentChar - 100;
      			if (i == 0)
      				checkSumm = currentChar;
      			else
      				checkSumm = (checkSumm + i * currentChar) % 103;
            }

      		// Calculation of the checksum ASCII code
      		checkSumm = checkSumm < 95 ? checkSumm + 32 : checkSumm + 100;
      		checkSumm = checkSumm == 32 ? blankChar : checkSumm;
      		ptr[plen++] = (char) checkSumm;

      		ptr[plen++] = (char) 206; // stop
      		      		
      		ptr[plen++] = '\0';                		
    		}
    	}
    
      c->WriteData(par->dstR, par->dstI, dst, strlen(dst)+1, Offset);
      }
    else
      c->DelData(par->dstR,par->dstI,Offset);
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->srcR, par->srcI, Offset);

    c->SetlConnection (par->blankChar,LPSTR(param)-sizeof(WORD));
    }
    
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->srcR, par->srcI, Offset);
    
    c->ClearlConnection (par->blankChar,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

////////////////////////////////////////////////////////////////////////
//  Arbeiten mit Fixen Strings
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct PaddString_param {
  WORD parSize;
  DWORD rString;
  DWORD rstrLen;
  DWORD old;
  };
#pragma pack()

BOOL PaddString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    PaddString_param FAR *par = (PaddString_param FAR *) param;
    LPSTR old = LPSTR (c->ReadlData (par->old));
    int strLen = c->ReadConstInt (par->rstrLen);
    LPSTR n = LPSTR (GetGlobMem (strLen+1));
    if (old != NULL)
      lstrncpy (n,old,strLen);
    for (int i = lstrlen(n) ; i < strLen ; i++)
      n[i] = ' ';   // Mit Spaces auffuellen
    c->WritelData (par->rString,n,strLen+1,LPSTR(param)-sizeof(WORD));
    FreeGlobMem (n);
    }
  if (mode & EM_FIXCONNECTION) {
    PaddString_param FAR *par = (PaddString_param FAR *) param;
    c->SetlConnection (par->old,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    PaddString_param FAR *par = (PaddString_param FAR *) param;
    c->ClearlConnection (par->old,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct RemoveSpaces_param {
  WORD parSize;
  DWORD res;
  DWORD src;
  };
#pragma pack()

BOOL RemoveSpaces (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveSpaces_param FAR *par = (RemoveSpaces_param FAR *)param;
    LPSTR txt = LPSTR(c->ReadlData (par->src));
    if (txt != NULL) {
      int len = lstrlen(txt) + 1;
      LPSTR res = LPSTR (GetGlobMem (len)) ;
      lmemcpy(res,txt,len);
      len -= 2;
      for ( ; ; len -- ) {
        if ((len == 0) && (res[0] == ' ')) {
          c->DellData (par->res,LPSTR (param)-sizeof(WORD));
          break ;
          }
        if (res[len] == ' ') continue ;
        res[++len] = '\0';
        c->WritelData (par->res,res,len + 1,LPSTR (param)-sizeof(WORD));
        break ;
        }
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR (param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveSpaces_param FAR *par = (RemoveSpaces_param FAR *)param;
    c->SetlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    RemoveSpaces_param FAR *par = (RemoveSpaces_param FAR *)param;
    c->ClearlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ExpandRNT_param {
  WORD parSize;
  DWORD res;
  DWORD src;
  };
#pragma pack()

BOOL ExpandRNT (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    LPSTR txt = LPSTR(c->ReadlData (par->src));
    if (txt != NULL) {
      int l = 0 ;
      for (int i = 0 ; txt[i] ; i++ , l++) {
        // Abzaehlen der Sonderzeichen
        if (txt[i] == '\r') l ++ ;
        else if (txt[i] == '\n') l ++ ;
        else if (txt[i] == '\t') l ++ ;
        }
      LPSTR res = LPSTR (GetGlobMem (l + 1)) ;
      l = 0 ;
      for (i = 0 ; txt[i] ; i++) {
        if (txt[i] == '\r') res[l++] = '\\' , res[l++] = 'r' ;
        else if (txt[i] == '\n') res[l++] = '\\' , res[l++] = 'n' ;
        else if (txt[i] == '\t') res[l++] = '\\' , res[l++] = 't' ;
        else res[l++] = txt[i] ;
        }
      if (l > 0)
        c->WritelData (par->res,res,l + 1,LPSTR (param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR (param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR (param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    c->SetlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    c->ClearlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL MakeRNT (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    LPSTR txt = LPSTR(c->ReadlData (par->src));
    if (txt != NULL) {
      LPSTR res = LPSTR (GetGlobMem (lstrlen(txt) + 1)) ;
      int l = 0 ;
      for (int i = 0 ; txt[i] ; ) {
        if ((txt[i] == '\\') && (txt[i+1] == 'r'))
          res[l++] = '\r', i += 2 ;
        else if ((txt[i] == '\\') && (txt[i+1] == 'n'))
          res[l++] = '\n', i += 2 ;
        else if ((txt[i] == '\\') && (txt[i+1] == 't'))
          res[l++] = '\t', i += 2 ;
        else res[l++] = txt[i++] ;
        }
      if (l > 0)
        c->WritelData (par->res,res,l + 1,LPSTR (param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR (param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR (param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    c->SetlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExpandRNT_param FAR *par = (ExpandRNT_param FAR *)param;
    c->ClearlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ExtractString_param {
  WORD parSize;
  DWORD rString;
  DWORD rsPos,rePos;   // jeweils inklusive (funktioniert nur,
                    // wenn beide Position im String enthalten sind,
                    // ePos == -1 ist auch legal (String bis zum Ende
                    // nehmen)
  DWORD old;
  };
#pragma pack()

BOOL ExtractString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractString_param FAR *par = (ExtractString_param FAR *) param;
    LPSTR old = LPSTR (c->ReadlData (par->old));
    int sPos = c->ReadConstInt (par->rsPos);
    int ePos = c->ReadConstInt (par->rePos);
    if ((old != NULL) && 
          (((ePos < 0) && (lstrlen(old) > sPos)) || 
           (lstrlen(old) >= ePos)
          )
       ) {
      if (ePos < 0) ePos = lstrlen(old) - 1;
      if (ePos >= sPos) {
        LPSTR res = LPSTR (GetGlobMem (ePos - sPos+2));
        LPSTR h = res;
        for (int i = sPos ; i <= ePos ; i++)
          *h++ = old[i];
        *h++ = '\0';
        c->WritelData (par->rString,res,ePos - sPos + 2,
                          LPSTR(param)-sizeof(WORD));
        FreeGlobMem (res);
        }
      else {
        c->DellData (par->rString,LPSTR(param)-sizeof(WORD));
        }
      }
    else
      c->DellData (par->rString,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractString_param FAR *par = (ExtractString_param FAR *) param;
    c->SetlConnection (par->old,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ExtractString_param FAR *par = (ExtractString_param FAR *) param;
    c->ClearlConnection (par->old,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL IsLike (LPSTR pattern, LPSTR str, BOOL firstLike, BOOL withRegular)
  {
  for ( ; (*pattern != '\0'); str++, pattern++) {
    if (*pattern == '%') {
      for ( ; ((*pattern != '\0') && (*pattern == '%')); pattern++); // Absichtlich leere for-Schleife
      if (*pattern == '\0')
        return TRUE;
      else {
        for ( ; (*str != '\0') ; str++) {
          if (IsLike (pattern, str, firstLike, withRegular))
            return TRUE;
          }
        return FALSE;
        }
      }
    else if (withRegular && (*pattern == '[')) {
      pattern++;
      BOOL isNegative;
      BOOL foundIt = FALSE;
      if (*pattern == '^') {
        pattern++;
        isNegative = TRUE;
        }
      else
        isNegative = FALSE;
      for ( ; ((*pattern != '\0') && (*pattern != ']')); pattern++) {
        if (*str == *pattern) {
          if (isNegative)
            return FALSE; // Brutal aber schnell
          else
            foundIt = TRUE;
          }
        }
      if (!isNegative && !foundIt)
        return FALSE;
      }
    else if ((*pattern != '_') && (*pattern != *str))
      return FALSE;
    }
  return (firstLike || (*str == '\0'));
  }

#define STRCMP_EQUAL        0
#define STRCMP_FIRSTEQUAL   1
#define STRCMP_CUS          2
#define STRCMP_LIKE         4
#define STRCMP_REGULAR      8 // Stark uebertrieben. Dzt. nur [abc] fuer Zeichen a oder b oder c, kein Escape

#pragma pack(1)
struct bCompareString_param {
  WORD parSize;
  DWORD s1; // Bei FIRSTEQUAL Suchstring, bei LIKE Pattern
  DWORD s2;
  DWORD rmode;
  };
#pragma pack()

extern LPVOID GetLastOffset (void);
BOOL bCompareString (mdiChild *c,LPVOID param,WORD mode)
  {
  bCompareString_param FAR *par = (bCompareString_param FAR *) param;
  if (mode & EM_FIXCONNECTION) {
    LPVOID LastOffset = GetLastOffset();
    c->SetlConnection (par->s1,LastOffset);
    c->SetlConnection (par->s2,LastOffset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LPVOID LastOffset = GetLastOffset();
    c->ClearlConnection (par->s1,LastOffset);
    c->ClearlConnection (par->s2,LastOffset);
    }
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR s1 = LPSTR(c->ReadlData(par->s1));
    LPSTR s2 = LPSTR(c->ReadlData(par->s2));
    int parmode = c->ReadConstInt (par->rmode);
    if ((s1 != NULL) && (s2 != NULL)) {
      LPSTR s1n,s2n;
      BOOL doFree = FALSE ;
      if (parmode & STRCMP_CUS) {
        s1n = LPSTR(GetGlobMem (lstrlen(s1)+1));
        lstrcpy (s1n,s1);
        s1 = s1n ;
        AnsiUpper (s1);
        s2n = LPSTR(GetGlobMem (lstrlen(s2)+1));
        lstrcpy (s2n,s2);
        s2 = s2n;
        AnsiUpper (s2);
        doFree = TRUE ;
        }
      if (parmode & STRCMP_LIKE) {
        res = IsLike (s1, s2, (parmode & STRCMP_FIRSTEQUAL) != 0, (parmode & STRCMP_REGULAR) != 0);
        }
      else if (parmode & STRCMP_REGULAR) {
        LoadRegExpDLL(); //Check and load RegExpDLL.dll
        
        if (regExpMatch)
          res = regExpMatch (s1, s2); //s1 is pattern, s2 the text to be matched
        }
      else {
        if (parmode & STRCMP_FIRSTEQUAL) {
          int l1 = lstrlen(s1);
          int l2 = lstrlen(s2);
          if ((l1 > 0) && (l2 > 0)) {
            int len = min (l1,l2);
            res = TRUE ;
            for (int i = 0 ; ((i < len) && (res)) ; i++)
              res = (s1[i] == s2[i]);
            if (res) res = (s1[i] == '\0');
            }
          else res = FALSE ;
          }
        else {
          res = (lstrcmp(s1,s2) == 0);
          }
        }
      if (doFree) {
        FreeGlobMem (s1);
        FreeGlobMem (s2);
        }
      }
    else if (s1 != NULL) { // garantiert s2 == NULL, weil nicht beide != NULL wegen oberen if
      if (parmode & (STRCMP_LIKE | STRCMP_REGULAR)) {
        for ( ; ((*s1 != '\0') && (*s1 == '%')); s1++); // Absichtlich leere for-Schleife
        }
      res = (*s1 == '\0');
      }
    else if ((parmode & STRCMP_FIRSTEQUAL) || (s2 == NULL) || (*s2 == '\0')) // s1 == NULL garantiert wegen oberen if
      res = TRUE;
    }
  return res;
  }

#pragma pack(1)
struct TestChar_param {
  WORD parSize;
  DWORD str;
  };
#pragma pack()

BOOL IsFirstCharAlpha (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    res = ((str != NULL) && (IsCharAlpha (*str)));
    }
  if (mode & EM_FIXCONNECTION) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return res;
  }

BOOL IsFirstCharNumeric (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    res = ((str != NULL) && (*str >= '0') && (*str <= '9'));
    }
  if (mode & EM_FIXCONNECTION) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TestChar_param FAR *par = (TestChar_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return res;
  }

#pragma pack(1)
struct RemoveLastChar_param {
  WORD parSize;
  DWORD res;
  DWORD str;
  };
#pragma pack()

BOOL RemoveLastChar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RemoveLastChar_param FAR *par = (RemoveLastChar_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    int len;
    if ((str != NULL) && ((len = lstrlen (str)) > 1)) {
      char cpy[256];
      lstrncpy (cpy,str,sizeof(cpy));
      cpy[len-1] = '\0';
      c->WritelData (par->res,cpy,len,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetDigits_param {
  WORD parSize;
  DWORD res;
  DWORD src;
  };
#pragma pack()

BOOL GetDigits (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetDigits_param FAR *par = (GetDigits_param FAR *) param; 
    LPSTR src = LPSTR (c->ReadlData (par->src));
    if (src != NULL) {
      for ( ; ((*src) && ((*src > '9') || (*src < '0'))) ; src++);
      c->WritelData (par->res,src,lstrlen(src)+1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetDigits_param FAR *par = (GetDigits_param FAR *) param; 
    c->SetlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetDigits_param FAR *par = (GetDigits_param FAR *) param; 
    c->ClearlConnection (par->src,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


#pragma pack(1)
struct ExtractPath_param {
  WORD parSize;
  DWORD res;
  DWORD source;
  };
#pragma pack()

BOOL ExtractPath (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractPath_param FAR *par = (ExtractPath_param FAR *) param;
    LPSTR src = LPSTR (c->ReadlData (par->source));
    if (src != NULL) {
      LPSTR last = src - 1;
      for ( ; *src ; src ++) {
        if ((*src == ':') || (*src == '\\'))
          last = src ;
        }
      c->WritelData (par->res,last+1,lstrlen(last+1)+1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractPath_param FAR *par = (ExtractPath_param FAR *) param;
    c->SetlConnection (par->source,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExtractPath_param FAR *par = (ExtractPath_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FindSubString_param {
  WORD parSize;
  WORD sRec,sId;
  WORD fRec,fId;
  };
#pragma pack()

BOOL CheckStr (LPSTR start,LPSTR s1,LPSTR s2)
  {
  for ( ; *s1 && *s2 ; s1 ++ , s2 ++) {
    if (*s2 != *s1) return FALSE;
    }
  if ((*s2) && (*s1 == '\0')) return FALSE;
  return TRUE ;
  }

BOOL CheckIStr (LPSTR start,LPSTR s1,LPSTR s2)
  {
  char ch1[2],ch2[2];
  ch1[1] = ch2[1] = '\0';
  for ( ; *s1 && *s2 ; s1 ++ , s2 ++) {
    ch1[0] = *s1;
    ch2[0] = *s2;
#ifdef WIN32
    CharUpper(ch1);
    CharUpper(ch2);
#else
    AnsiUpper(ch1);
    AnsiUpper(ch2);
#endif
    if (*ch2 != *ch1) return FALSE;
    }
  if ((*s2) && (*s1 == '\0')) return FALSE;
  return TRUE ;
  }

#define CHECK_WORD            1
#define CHECK_STRING          2
#define CHECK_JUSTSTRING      4
#define CHECK_CASEINSESITIVE  8
typedef BOOL (* CHFUNC) (LPSTR start,LPSTR s1,LPSTR s2);
inline BOOL WordChar (char ch)
  {
  return (IsCharAlpha (ch) || ((ch >= '0') && (ch <= '9')) || (ch == '_') || (ch == '@') || (ch == '.'));
  }
inline BOOL WordEndChar (char ch)
  {
  return (IsCharAlpha (ch) || ((ch >= '0') && (ch <= '9')) || (ch == '_') || (ch == '@'));
  }
BOOL CheckWord (LPSTR start,LPSTR s1,LPSTR s2)
  {
  if ((s1 > start) && (WordChar(s1[-1]))) return FALSE ;
  for ( ; *s1 && *s2 ; s1 ++ , s2 ++) {
    if (*s2 != *s1) return FALSE;
    }
  if ((*s2) && (*s1 == '\0')) return FALSE;
  return (!WordEndChar (*s1));
  }

BOOL CheckIWord (LPSTR start,LPSTR s1,LPSTR s2)
  {
  if ((s1 > start) && (WordChar(s1[-1]))) return FALSE ;
  char ch1[2],ch2[2];
  ch1[1] = ch2[1] = '\0';
  for ( ; *s1 && *s2 ; s1 ++ , s2 ++) {
    ch1[0] = *s1;
    ch2[0] = *s2;
#ifdef WIN32
    CharUpper(ch1);
    CharUpper(ch2);
#else
    AnsiUpper(ch1);
    AnsiUpper(ch2);
#endif
    if (*ch2 != *ch1) return FALSE;
    }
  if ((*s2) && (*s1 == '\0')) return FALSE;
  return (!WordEndChar (*s1));
  }

int FindStr (LPSTR s1,LPSTR s2)
  {
  BOOL res = FALSE;
  int FoundPos = 0;
  LPSTR start = s1;
  for ( ; (!res) && (*s1) ; FoundPos++) {
    res = CheckStr (start,s1,s2);
    s1 ++ ;
    }
  if (res)
    return FoundPos;
  else
    return 0;
  }

int FindWord (LPSTR s1,LPSTR s2,int mode)
  {
  BOOL res = FALSE;
  BOOL inString = (mode & CHECK_JUSTSTRING) ? TRUE : FALSE ;
  CHFUNC chfunc;
  if (mode & CHECK_CASEINSESITIVE) {
    if (mode & CHECK_WORD) chfunc = CheckIWord ;
    else                   chfunc = CheckIStr ;
    }
  else {
    if (mode & CHECK_WORD) chfunc = CheckWord ;
    else                   chfunc = CheckStr ;
    }
  for (LPSTR h = s1 ; *h ; ) {
    if ((*h == '"') && (mode & CHECK_STRING)) {
      inString = !inString ;
      h ++ ;
      }
    else if ((*h == '\\') && (h[1] == '"') && (mode & CHECK_STRING))
      h += 2 ;
    else if ((!inString) && ((*chfunc) (s1,h,s2))) {
      return h - s1 + 1 ;
      break ;
      }
    else
      h ++ ;
    }
  return 0 ;
  }

extern LPVOID GetLastOffset (void);
BOOL eFindSubStr (mdiChild *c,LPVOID param,WORD mode)
  {
  FindSubString_param FAR *par = (FindSubString_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR sname = LPSTR (c->ReadData (par->sRec,par->sId));
    LPSTR fname = LPSTR (c->ReadData (par->fRec,par->fId));
    if ((sname != NULL) && (fname != NULL)) {
      return (BOOL)FindStr (sname,fname);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->sRec,par->sId,GetLastOffset());
    c->SetConnection (par->fRec,par->fId,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->sRec,par->sId,GetLastOffset());
    c->ClearConnection (par->fRec,par->fId,GetLastOffset());
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CatMultiString_param {
  WORD parSize;
  DWORD res;
  DWORD s[1];
  
  int AnzSource () {
    return ((parSize - (sizeof(*this) - sizeof(s[0]))) / sizeof(s[0])) ;
    }
  };
#pragma pack()

BOOL CatMultiString (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CatMultiString_param FAR *par = (CatMultiString_param FAR *) param;
    LPSTR res = NULL ;
    for (int i = 0 ; i < par->AnzSource() ; i++) {
      LPSTR src = LPSTR (c->ReadlData (par->s[i]));
      if (src != NULL) {
        WORD oSize = GetBlockSize (res);
        WORD nSize = GetBlockSize (src);
        LPSTR nres = LPSTR (GetGlobMem (oSize + nSize)) ;
        if (res != NULL) {
          lmemcpy (nres,res,oSize);
          FreeGlobMem (res);
          nres[oSize-1] = ' ';
          }
        res = nres ;
        lmemcpy (res+oSize,src,GetBlockSize(src));
        }
      }
    if (res != NULL) {
      c->WritelData (par->res,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    CatMultiString_param FAR *par = (CatMultiString_param FAR *) param;
    for (int i = 0 ; i < par->AnzSource() ; i++)
      c->SetlConnection (par->s[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    CatMultiString_param FAR *par = (CatMultiString_param FAR *) param;
    for (int i = 0 ; i < par->AnzSource() ; i++)
      c->ClearlConnection (par->s[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct RemoveFormatInfo_param {
  WORD parSize;
  DWORD res;
  DWORD str;
  };
#pragma pack()

extern DLLExport void _export WINAPI RemoveFormatInfoFrom (LPSTR res,LPSTR Text);
BOOL RemoveFormatInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    LPSTR str = LPSTR(c->ReadlData (par->str));
    if (str) {
      LPSTR res = LPSTR (GetGlobMem (GetBlockSize (str)));
      RemoveFormatInfoFrom (res,str);
      c->WritelData (par->res,res,lstrlen(res)+1,LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

DLLExport void _export WINAPI ReexchangeEscape (LPSTR Str);
DLLExport void _export WINAPI ExchangeEscape (LPSTR Str);
BOOL ExchangeEscape (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    LPSTR str = LPSTR(c->ReadlData (par->str));
    if (str) {
      LPSTR res = LPSTR (GetGlobMem (GetBlockSize (str)));
      lstrcpy (res,str);
      ExchangeEscape (res);
      c->WritelData (par->res,res,lstrlen(res)+1,LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ReexchangeEscape (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    LPSTR str = LPSTR(c->ReadlData (par->str));
    if (str) {
      LPSTR res = LPSTR (GetGlobMem (GetBlockSize (str)));
      lstrcpy (res,str);
      ReexchangeEscape (res);
      c->WritelData (par->res,res,lstrlen(res)+1,LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    RemoveFormatInfo_param FAR *par = (RemoveFormatInfo_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetPascalString_param {
  WORD parSize;
  DWORD res;
  DWORD Str;
  DWORD rSize;
  };
#pragma pack()

BOOL GetPascalString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetPascalString_param FAR *par = (GetPascalString_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->Str));
    int Size = c->ReadConstInt (par->rSize);
    LPSTR res = LPSTR (GetGlobMem (Size+1));
    if (str != NULL) {
      lstrncpy (res+1,str,Size-1);
      AnsiToOem(res+1,res+1);
      }
    res[0] = lstrlen(res+1);
    c->WritelData (par->res,res,Size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct DivideIntoFormatStrings_param {
  WORD parSize;
  DWORD r1,r2;
  DWORD str;
  };
#pragma pack()
BOOL DivideIntoFormatStrings (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DivideIntoFormatStrings_param FAR *par = (DivideIntoFormatStrings_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    if (str != NULL) {
      if ((str[0] == '\\') && (str[1] == 'f') && (str[2] == ':')) {
        BOOL found = FALSE;
        LPSTR h = str + 2 ;
        while (*h && (*h != '\\')) h++;
        for ( ; *h ; h++) {
          if ((h[0] == '\\') && (h[1] == 'f') && (h[2] == ':')) {
            for ( ; ((*h) && (*h != '\r')) ; h++ ) ;
            if (*h == '\r')
              found = TRUE ;
            break ;
            }
          }
        if (found) {
          LPSTR t = LPSTR (GetGlobMem (h - str + 1));
          lmemcpy (t,str,h-str);
          c->WritelData (par->r1,t,lstrlen(t)+1,LPSTR(param)-sizeof(WORD));
          c->WritelData (par->r2,h+1,lstrlen(h+1)+1,LPSTR(param)-sizeof(WORD));
          FreeGlobMem (t);
          }
        else {
          // Alles in r1, r2 loeschen
          c->WritelData (par->r1,str,lstrlen(str)+1,LPSTR(param)-sizeof(WORD));
          c->DellData (par->r2,LPSTR(param)-sizeof(WORD));
          }
        }
      else {
        // Alles in r1, r2 loeschen
        c->WritelData (par->r1,str,lstrlen(str)+1,LPSTR(param)-sizeof(WORD));
        c->DellData (par->r2,LPSTR(param)-sizeof(WORD));
        }
      }
    else {
      c->DellData (par->r1,LPSTR(param)-sizeof(WORD));
      c->DellData (par->r2,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    DivideIntoFormatStrings_param FAR *par = (DivideIntoFormatStrings_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DivideIntoFormatStrings_param FAR *par = (DivideIntoFormatStrings_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FormatDate_param {
  WORD  parSize;
  DWORD res;
  DWORD format;
  DWORD dvar;
  };
#pragma pack()
BOOL FormatDate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    FormatDate_param FAR *par = (FormatDate_param FAR *) param;
    LPSTR format = LPSTR (c->ReadlData (par->format));
    packdate FAR *dvar = (packdate FAR *) c->ReadlData (par->dvar);
    if ((format != NULL) && (dvar != NULL)) {
      char outtxt[256];
      FormatDate (outtxt,dvar,format);
      c->WritelData (par->res,LPSTR(outtxt),lstrlen(outtxt)+1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    FormatDate_param FAR *par = (FormatDate_param FAR *) param;
    c->SetlConnection (par->format,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FormatDate_param FAR *par = (FormatDate_param FAR *) param;
    c->ClearlConnection (par->format,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dvar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FormatTime_param {
  WORD  parSize;
  DWORD res;
  DWORD format;
  DWORD tvar;
  };
#pragma pack()
BOOL FormatTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    FormatTime_param FAR *par = (FormatTime_param FAR *) param;
    LPSTR format = LPSTR (c->ReadlData (par->format));
    packtime FAR *tvar = (packtime FAR *) c->ReadlData (par->tvar);
    if ((format != NULL) && (tvar != NULL)) {
      char outtxt[128];
      FormatTime (outtxt,tvar,format);
      c->WritelData (par->res,LPSTR(outtxt),lstrlen(outtxt)+1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    FormatTime_param FAR *par = (FormatTime_param FAR *) param;
    c->SetlConnection (par->format,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FormatTime_param FAR *par = (FormatTime_param FAR *) param;
    c->ClearlConnection (par->format,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tvar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//----------------------------------------------------------------------------
//
//  String - Funktionen die an WordBasic angelehnt sind.
//
//----------------------------------------------------------------------------
#pragma pack(1)
struct Str_instr_par {
  WORD  RecSize;
  DWORD FoundPos;      // Position, an der der zu suchende String gefunden wurde, "0" sonst
  DWORD StartPos;      // Position, ab der mit der Suche begonnen wird
  DWORD lpszSource;    // String, der durchsucht werden soll
  DWORD lpszSearch;    // String, nach dem gesucht wird
  DWORD mode;          // nur fuer FindWord
  };
#pragma pack()


//----------------------------------------------------------------------------
// Aufruf: Instr (strfield Result, strfield StartPos,
//                string szSource, string szFind);
// Achtung: im Gegensatz zu "C" beginnen die String-Indizes wie in BASIC mit 1
//----------------------------------------------------------------------------
BOOL In_Str (mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_instr_par FAR *par = (Str_instr_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR lpszSource = LPSTR (c->ReadlData (par->lpszSource));
    LPSTR lpszSearch = LPSTR (c->ReadlData (par->lpszSearch));
    DBINT FAR *lpStartPos = (DBINT FAR *) c->ReadlData (par->StartPos);
    int StartPos = (lpStartPos != NULL) ? *lpStartPos : -1 ;

    int res = 0;
    if ((lpszSource != NULL) && (lpszSearch != NULL) && (StartPos <= lstrlen(lpszSource))) {
      if (StartPos <= 0)   // falls der dumme Gerhold bei 0 anfaengt!!
        StartPos = 1;
        
      lpszSource += (StartPos-1);      // String um StartPos weiterschalten
      res = FindStr (lpszSource,lpszSearch) ;
      if (res) res = res + StartPos - 1;
      else     res = 0 ;
      }

    c->WritelData (par->FoundPos,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->lpszSource, Offset);
    c->SetlConnection (par->lpszSearch, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->lpszSource, Offset);
    c->ClearlConnection (par->lpszSearch, Offset);
    c->ClearlConnection (par->StartPos, Offset);
    }

  return FALSE;
  }

BOOL WordIn_Str (mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_instr_par FAR *par = (Str_instr_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR lpszSource = LPSTR (c->ReadlData (par->lpszSource));
    LPSTR lpszSearch = LPSTR (c->ReadlData (par->lpszSearch));
    DBINT FAR *lpsMode = (DBINT FAR *) c->ReadlData (par->mode);
    int smode;
    if (lpsMode != NULL) smode = *lpsMode ;
    else                 smode = 0;
    DBINT FAR *lpStartPos = (DBINT FAR *) c->ReadlData (par->StartPos);
    int StartPos = (lpStartPos != NULL) ? *lpStartPos : -1 ;

    int res = 0;
    if ((lpszSource != NULL) && (lpszSearch != NULL) && (StartPos <= lstrlen(lpszSource))) {
      if (StartPos <= 0)   // falls der dumme Gerhold bei 0 anfaengt!!
        StartPos = 1;
        
      lpszSource += (StartPos-1);      // String um StartPos weiterschalten
      res = FindWord (lpszSource,lpszSearch,smode) ;
      if (res) res = res + StartPos - 1;
      else     res = 0 ;
      }

    c->WritelData (par->FoundPos,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->lpszSource, Offset);
    c->SetlConnection (par->lpszSearch, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->lpszSource, Offset);
    c->ClearlConnection (par->lpszSearch, Offset);
    c->ClearlConnection (par->StartPos, Offset);
    }

  return FALSE;
  }

#pragma pack(1)
struct Str_midstr_par {
  WORD  RecSize;
  DWORD lpszResult;    // String in dem das Ergebnis abgelegt wird
  DWORD lpszSource;    // String, aus dem der Sub-String ermittelt wird
  DWORD StartPos;      // Position, ab der mit dem Sub-String begonnen wird
  DWORD Count;         // Anzahl der Zeichen des Sub-Strings
  };
#pragma pack()

//----------------------------------------------------------------------------
// Aufruf: MidStr (string szResult, string szSource,
//                 strfield Start, strfield Count);
//----------------------------------------------------------------------------
BOOL Mid_Str (mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_midstr_par FAR *par = (Str_midstr_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR lpszSource = LPSTR (c->ReadlData (par->lpszSource));
    DBINT FAR *lpStartPos = (DBINT FAR *)c->ReadlData (par->StartPos);
    int StartPos = (lpStartPos != NULL) ? *lpStartPos : -1 ;

    DBINT FAR *lpSize = (DBINT FAR *) c->ReadlData (par->Count);

    if ((lpszSource != NULL) && (lpSize != NULL)) {
      int Size = *lpSize;
      if (StartPos <= 0)   // falls der dumme Gerhold bei 0 anfaengt!!
        StartPos = 1;

      int MaxSize = lstrlen(lpszSource) + 1 - StartPos;
      if (Size > MaxSize)
        Size = MaxSize;
      
      if (Size > 0) {
        LPSTR res = LPSTR (GetGlobMem (Size+1));
        lmemcpy (res, lpszSource + StartPos - 1, Size);
        res[Size] = '\0';
        c->WritelData (par->lpszResult, res, Size+1, Offset);
        FreeGlobMem (res);
        }
      else
        c->DellData (par->lpszResult,Offset);
      }
    else
      c->DellData (par->lpszResult, Offset);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->lpszSource, Offset);
    c->SetlConnection (par->StartPos, Offset);
    c->SetlConnection (par->Count, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->lpszSource, Offset);
    c->ClearlConnection (par->StartPos, Offset);
    c->ClearlConnection (par->Count, Offset);
    }

  return FALSE;
  }


#pragma pack(1)
struct Str_len_par {
  WORD  RecSize;
  DWORD len;           // integer in dem die Stringlaenge abgelegt wird
  DWORD lpszSource;    // String, desse Laenge ermittelt wird
  };
#pragma pack()

//----------------------------------------------------------------------------
// Aufruf: StrLen (strfield len, string szResult);
//----------------------------------------------------------------------------
BOOL Str_Len (mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  Str_len_par FAR *par = (Str_len_par FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR lpszSource = LPSTR (c->ReadlData (par->lpszSource));

    int len = 0;
    if (lpszSource != NULL) {
      len = lstrlen (lpszSource);
      c->WritelData (par->len, &len, sizeof(len),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->len,LPSTR(param)-sizeof(WORD));
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection (par->lpszSource, Offset);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->lpszSource, Offset);
    }

  return FALSE;
  }

#pragma pack(1)
struct RemoveChar_param {
  WORD parSize;
  DWORD res ;
  DWORD orig;
  DWORD ch;
  };
#pragma pack()

BOOL RemoveChar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveChar_param FAR *par = (RemoveChar_param FAR *) param ;
    LPSTR old = LPSTR(c->ReadlData (par->orig));
    LPSTR ch = LPSTR(c->ReadlData (par->ch));
    if ((old != NULL) && (ch != NULL)) {
      LPSTR res = LPSTR (GetGlobMem (lstrlen (old) + 1)) ;
      LPSTR o = old ;
      LPSTR n = res ;
      for (int j = 0 ; *o ; o++ ) {
        if (*o != *ch) *n++ = *o , j ++ ;
        }
      c->WritelData (par->res,res,++ j,LPSTR(param)-sizeof(WORD));
      FreeGlobMem(res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveChar_param FAR *par = (RemoveChar_param FAR *) param ;
    c->SetlConnection (par->orig,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->ch,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    RemoveChar_param FAR *par = (RemoveChar_param FAR *) param ;
    c->ClearlConnection (par->orig,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ch,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }



//---------------------------------------------------------------------------
// Funktion RemoveCRLF
// 
// Zweck: Reduziert mehrere aufeinanderfolgende CR-Sequenzen auf eine 
//        einzelne. Befinden sich zwischen diesen CR-Sequenzen nur Leer- 
//        oder Tabulator-Zeichen, werden diese ebenfalls mit entfernt.
//---------------------------------------------------------------------------
#pragma pack(1)
struct RemoveCRLF_param {
  WORD parSize;
  DWORD res ;      // String in dem das Resultat gespeichert wird
  DWORD string;    // String der ausgewertet wird
  };
#pragma pack()

BOOL IsCharValid (char ch)
  {
  return ((ch != ' ') &&
          (ch != '\r') &&
          (ch != '\n') &&
          (ch != '\t '));
  }

BOOL RemoveCRLF (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    RemoveCRLF_param FAR *par = (RemoveCRLF_param FAR *) param ;
    LPSTR string = LPSTR(c->ReadlData (par->string));
    if (string != NULL) {
      LPSTR res = LPSTR (GetGlobMem (lstrlen (string) + 1)) ;
      LPSTR o = string ;
      LPSTR n = res ;

      BOOL bValidChar = TRUE;
      short CRPos = -1, OldCRPos = 0;
      for (int len = 0, i = 0 ; ; o++, i++ ) {
        if ((*o == '\r') || (*o == '\0')) {
          OldCRPos = (CRPos > 0) ? CRPos : 0;
          CRPos = i;
          }
        
        //-----------------------------------------------------------------
        // wurde zwischen zwei CR kein gueltiges Zeichen entdeckt, bleiben
        // alle Zeichen zwischen diesen CR unberuecksichtigt.
        //-----------------------------------------------------------------
        if (CRPos == i) {
          if (!bValidChar) {
            int Delta = CRPos - OldCRPos;          // Zeichen zwischen CR
            n -= Delta;                 // Resultat-Pointer zuruecksetzen
            len -= Delta;
            }
          bValidChar = FALSE;
          }
        else {
          if (IsCharValid (*o))
            bValidChar = TRUE;
          }
        
        // Daten vom Ausgangsstring in das Resultat uebertragen
        *n++ = *o , len ++ ;
        if (*o == '\0') break ;
        }

      c->WritelData (par->res,res,len,LPSTR(param)-sizeof(WORD));
      FreeGlobMem(res);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    RemoveCRLF_param FAR *par = (RemoveCRLF_param FAR *) param ;
    c->SetlConnection (par->string,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    RemoveCRLF_param FAR *par = (RemoveCRLF_param FAR *) param ;
    c->ClearlConnection (par->string,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//---------------------------------------------------------------------------
// Funktion SplitPath
// 
// Zweck: Zerlegt einen uebergebenen Dateinamen in seine Komponenten  
//---------------------------------------------------------------------------
#pragma pack(1)
struct SplitPath_param {
  WORD parSize;
  DWORD path;     // Dateiname der zerlegt wird
  DWORD drive;    // Laufwerk
  DWORD dir;      // Verzeichnis
  DWORD fname;    // Dateiname
  DWORD ext;      // Erweiterung
  };
#pragma pack()


BOOL SplitPath (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SplitPath_param FAR *par = (SplitPath_param FAR *) param ;
    LPSTR path = LPSTR(c->ReadlData (par->path));
    if (path != NULL) {
      char szPath[_MAX_PATH];
      char drive[_MAX_DRIVE];
      char dir[_MAX_DIR];
      char fname[_MAX_FNAME];
      char ext[_MAX_EXT];

//      LPSTR drive = LPSTR (GetGlobMem (_MAX_DRIVE + 1)) ;
//      LPSTR dir = LPSTR (GetGlobMem (_MAX_DIR + 1)) ;
//      LPSTR fname = LPSTR (GetGlobMem (_MAX_FNAME + 1)) ;
//      LPSTR ext = LPSTR (GetGlobMem (_MAX_EXT + 1)) ;

      lstrcpy (szPath, path);
      _splitpath (szPath, drive, dir, fname, ext);

      c->WritelData (par->drive,drive,lstrlen(drive)+1,LPSTR(param)-sizeof(WORD));
      c->WritelData (par->dir,  dir,  lstrlen(dir)+1,  LPSTR(param)-sizeof(WORD));
      c->WritelData (par->fname,fname,lstrlen(fname)+1,LPSTR(param)-sizeof(WORD));
      c->WritelData (par->ext,  ext,  lstrlen(ext)+1,  LPSTR(param)-sizeof(WORD));

//      FreeGlobMem(ext);
//      FreeGlobMem(fname);
//      FreeGlobMem(dir);
//      FreeGlobMem(drive);
      }
    else {
      c->DellData (par->drive,LPSTR(param)-sizeof(WORD));
      c->DellData (par->dir,LPSTR(param)-sizeof(WORD));
      c->DellData (par->fname,LPSTR(param)-sizeof(WORD));
      c->DellData (par->ext,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SplitPath_param FAR *par = (SplitPath_param FAR *) param ;
    c->SetlConnection (par->path,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SplitPath_param FAR *par = (SplitPath_param FAR *) param ;
    c->ClearlConnection (par->path,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ExchangeString_param {
  WORD parSize;
  DWORD dest;
  DWORD source;
  DWORD list;
  DWORD str1;
  DWORD str2;
  DWORD ignoreString;
  };
#pragma pack()
LPSTR PushString (LPSTR old,LPSTR str,int l)
  {
  if (_StrBuffer == NULL) {
    hGStrBuffer = GlobalAlloc (GMEM_MOVEABLE,0x8000);
    _StrBuffer = LPSTR (GlobalLock (hGStrBuffer)) + sizeof(WORD);
    }
  int sold = GetBlockSize (old);
  LPSTR n ;
  if (old != NULL) {
    n = _StrBuffer;
    ((WORD FAR *) _StrBuffer)[-1] = sold + l;
    sold -= 1 ;
    _StrBuffer[sold + l] = '\0' ;
    }
  else {
    n = _StrBuffer;
    ((WORD FAR *) _StrBuffer)[-1] = l + 1;
    _StrBuffer[l] = '\0' ;
    }
  lmemcpy (n + sold,str,l);
  return _StrBuffer;
  }
LPSTR GetStringMem ()
  {
  LPSTR res = LPSTR (GetGlobMem (GetBlockSize (_StrBuffer)));
  lmemcpy (res,_StrBuffer,GetBlockSize (_StrBuffer));
  return res;
  }
LPSTR Exchange (LPSTR source,LPSTR str1,LPSTR str2,int mode)
  {
  LPSTR last = source ;
  BOOL inString = (mode & CHECK_JUSTSTRING) ? TRUE : FALSE ;
  LPSTR res = NULL ;
  CHFUNC chfunc;
  if (mode & CHECK_WORD) chfunc = CheckWord ;
  else                   chfunc = CheckStr ;
  BOOL lastWasBackslash = FALSE;
  for (LPSTR h = source ; *h ; ) {
    if ((*h == '"') && (mode & CHECK_STRING) && !lastWasBackslash) {
      inString = !inString ;
      h ++ ;
      }
    else {
      lastWasBackslash = ((*h == '\\') && !lastWasBackslash);
      if ((!inString) && ((*chfunc) (source,h,str1))) {
        res = PushString (res,last,h - last);
        res = PushString (res,str2,lstrlen(str2));
        h += lstrlen(str1);
        last = h ;
        }
      else
        h ++ ;
      }
    }
  if (res != NULL)
    res = PushString (res,last,h - last);

  return res;
  }

inline BOOL IsConstChar (LPSTR h)
  {
  return ((*h == '"') ||
          (((*h == '+') || (*h == '-')) && (h[1] >= '0') && (h[1] <= '9')));
  }

BOOL PlusVorne (LPSTR h)
  {
  BOOL res = TRUE ;
  for (LPSTR s = h ; *h ; h++) {
    if ((*h == ' ') || (*h == '\r') || (*h == '\r')) continue ;
    if (WordChar (*h)) return FALSE ;
    if (IsConstChar (h)) return FALSE ;
    }
  return res ;
  }

LPSTR ExchangeModifier (LPSTR source)
  {
  LPSTR last = source ;
  ResetStrBuffer();
  BOOL inString = FALSE ;
  LPSTR res = NULL ;
  for (LPSTR h = source ; *h ; ) {
    if (*h == '"') {
      inString = !inString ;
      h ++ ;
      }
    else if ((*h == '\\') && (h[1] == '"'))
      h += 2 ;
    else if ((!inString) && (h[0] == '\\') && (h[1] == 'm'))  {
      res = PushString (res,last,h - last);
      char mod[16];
      char modnr[2];
      modnr[0] = h[2];
      modnr[1] = '\0';
      if (PlusVorne(h)) {
        lstrcpy (mod," + \"\\m");
        lstrcat (mod,modnr);
        lstrcat (mod,"\"");
        }
      else {
        lstrcpy (mod,"\"\\m");
        lstrcat (mod,modnr);
        lstrcat (mod,"\" + ");
        }
      res = PushString (res,mod,lstrlen(mod));
      h += 3;
      last = h ;
      }
    else
      h ++ ;
    }
  if (res != NULL)
    res = PushString (res,last,h - last);

  return res;
  }

extern LPDBRECORD GetRecordWithList (LPVOID list,LPDBRECORD h,mdiChild *c,WORD FAR *TableInd);
BOOL ExchangeStringWithReplaceList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ExchangeString_param FAR *par = (ExchangeString_param FAR *) param;
    LPSTR source = LPSTR (c->ReadlData (par->source));
    LPVOID list = c->ReadlData (par->list);
    DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->ignoreString);
    int mode;
    if (lpmode != NULL) mode = *lpmode ;
    else                mode = FALSE ;
    LPDBRECORD h = NULL;
    LPSTR res = source ;
    WORD ti;
    if ((source != NULL) && (list != NULL)) {
      for ( ; ; ) {
        h = GetRecordWithList (list,h,c,&ti);
        if (h != NULL) {
          LPSTR str1 = LPSTR (h->Get(HIWORD(par->str1)));
          LPSTR str2 = LPSTR (h->Get(HIWORD(par->str2)));
          if ((str1) && (str2) && (*str1) && (*str2)) {
            LPSTR nres = Exchange (res,str1,str2,mode);
            if (nres != NULL) {
              if (res != source) FreeGlobMem (res);
              res = LPSTR (GetGlobMem (GetBlockSize (nres))) ;
              lmemcpy (res,nres,GetBlockSize(nres)) ;
              }
            }
          }
        else
          break ;
        }
      if (res == source) {
        if (par->dest != par->source)
          c->WritelData (par->dest,source,GetBlockSize(source),LPSTR(param)-sizeof(WORD));
        }
      else {
        c->WritelData (par->dest,res,lstrlen(res) + 1,LPSTR(param)-sizeof(WORD));
        FreeGlobMem (res);
        }
      }
    else
      c->DellData (par->dest,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ReplaceString_param {
  WORD parSize;
  DWORD dest;
  DWORD source;
  DWORD str1;
  DWORD str2;
  DWORD ignoreString;
  };
#pragma pack()
BOOL ReplaceString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ReplaceString_param FAR *par = (ReplaceString_param FAR *) param;
    LPSTR source = LPSTR (c->ReadlData (par->source));
    DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->ignoreString);
    int mode;
    if (lpmode != NULL) mode = *lpmode ;
    else                mode = FALSE ;
    LPSTR str1 = LPSTR (c->ReadlData(par->str1));
    LPSTR str2 = LPSTR (c->ReadlData(par->str2));
    if ((source != NULL) && (str1 != NULL) && (str2 != NULL)) {
      LPSTR res = Exchange (source,str1,str2,mode);
      if (res == NULL) {
        if (par->dest != par->source)
          c->WritelData (par->dest,source,GetBlockSize(source),LPSTR(param)-sizeof(WORD));
        }
      else {
        c->WritelData (par->dest,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
        }
      }
    else
      c->DellData (par->dest,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ReplaceString_param FAR *par = (ReplaceString_param FAR *) param;
    c->SetlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->str1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->str2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ReplaceString_param FAR *par = (ReplaceString_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->str1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->str2,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ignoreString,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ModifierToString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ReplaceString_param FAR *par = (ReplaceString_param FAR *) param;
    LPSTR source = LPSTR (c->ReadlData (par->source));
    if (source != NULL) {
      LPSTR res = ExchangeModifier (source);
      if (res == NULL) {
        if (par->dest != par->source)
          c->WritelData (par->dest,source,GetBlockSize(source),LPSTR(param)-sizeof(WORD));
        }
      else {
        c->WritelData (par->dest,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
        }
      }
    else
      c->DellData (par->dest,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct TakeModifyFrom_param {
  WORD parSize;
  DWORD res;
  DWORD str;
  DWORD bsp;
  };
#pragma pack()
int FarbLaenge (LPSTR h)
  {
  if ((h[0] == '\\') && (h[1] == 'm')) {
    h += 3;
    }
  if ((h[0] == '\\') && (h[1] == 'c')) {
    h++ ;
    for ( int res = 1 ; ((*h != '\\') && (*h)) ; h++ , res ++ ) ;
    res ++ ;
    return res;
    }
  return 0;
  }
int ModifyLaenge (LPSTR h)
  {
  if ((h[0] == '\\') && (h[1] == 'c')) {
    for ( h ++ ; ((*h != '\\') && (*h)) ; h++ ) ;
    h ++ ;
    }
  if ((h[0] == '\\') && (h[1] == 'm')) {
    return 3;
    }
  return 0;
  }
void SetzeModify (LPSTR res,LPSTR h)
  {
  if ((h[0] == '\\') && (h[1] == 'c')) {
    for ( h ++ ; ((*h != '\\') && (*h)) ; h++ ) ;
    h ++ ;
    }
  if ((h[0] == '\\') && (h[1] == 'm')) {
    lmemcpy (res,h,3);
    }
  }
void SetzeFarbe (LPSTR res,LPSTR h)
  {
  if ((h[0] == '\\') && (h[1] == 'm')) {
    h += 3;
    }
  if ((h[0] == '\\') && (h[1] == 'c')) {
    *res ++ = *h++ ;
    for ( ; ((*h != '\\') && (*h)) ; *res ++ = *h++ ) ;
    *res = *h ;
    }
  }

BOOL TakeModifyFrom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TakeModifyFrom_param FAR *par = (TakeModifyFrom_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    LPSTR bsp = LPSTR (c->ReadlData (par->bsp));
    if (str != NULL) {
      LPSTR res;
      BOOL done = FALSE;
      if (bsp != NULL) {
        int ml = ModifyLaenge (bsp);
        int fl = FarbLaenge (bsp);
        int lextra = 1;
        if (ml > 0) lextra += 6 ;
        if (fl > 0) lextra += fl + 5 ;
        if (lextra > 1) {
          done = TRUE ;
          int l = lstrlen(str);
          res = LPSTR (GetGlobMem (l + lextra));
          SetzeModify (res,bsp);
          SetzeFarbe (res + ml,bsp);
          lstrcpy (res + fl + ml,str);
          if (ml > 0) lstrcpy (res + l + fl + ml,"\\m0");
          if (fl > 0) lstrcpy (res + l + fl + 2 * ml,"\\c:-\\");
          }
        }
      if (!done) {
        res = LPSTR (GetGlobMem (lstrlen(str) + 1));
        lstrcpy (res,str);
        }
      c->WritelData (par->res,res,lstrlen(res) + 1,LPSTR(param) - sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param) - sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    TakeModifyFrom_param FAR *par = (TakeModifyFrom_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->bsp,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TakeModifyFrom_param FAR *par = (TakeModifyFrom_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->bsp,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR TextFromStrArray_param {
  WORD parSize;
  DWORD res;
  DWORD str;
  DWORD ind;
  };
#pragma pack()

BOOL TextFromStrArray (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TextFromStrArray_param FAR *par = (TextFromStrArray_param FAR *) param;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    DBINT FAR *lpind = (DBINT FAR *) c->ReadlData (par->ind);
    DBINT i = 0;
    BOOL found = FALSE ;
    DBINT ind = (lpind != NULL) ? *lpind : -1;

    if (str != NULL) {
      for ( LPSTR h = str; ; ) {
        if (i++ == ind) {
          c->WritelData (par->res,h,lstrlen(h)+1,
                          LPSTR(param)-sizeof(WORD));
          found = TRUE ;
          break ;
          }
        h += lstrlen (h) + 1;
        if (int(h - str) >= int(GetBlockSize(str))) break;
        }
      }
    if (!found)
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    TextFromStrArray_param FAR *par = (TextFromStrArray_param FAR *) param;
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->ind,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TextFromStrArray_param FAR *par = (TextFromStrArray_param FAR *) param;
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ind,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ReallyExtractPath_param {
  WORD parSize;
  DWORD res;
  DWORD source;
  };
#pragma pack()

BOOL ReallyExtractPath (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ReallyExtractPath_param FAR *par = (ReallyExtractPath_param FAR *) param;
    LPSTR src = LPSTR (c->ReadlData (par->source));
    if (src != NULL) {
      LPSTR ccpy = (LPSTR)GetGlobMem(GetBlockSize(src));
      lstrcpy(ccpy,src);
      LPSTR cpy = ccpy;
      LPSTR last = cpy;
      for ( ; *cpy ; cpy ++) {
        if ((*cpy == ':') || (*cpy == '\\'))
          last = cpy + 1;
        }
      *last = '\0';
      c->WritelData (par->res,ccpy,lstrlen(ccpy)+1,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ReallyExtractPath_param FAR *par = (ReallyExtractPath_param FAR *) param;
    c->SetlConnection (par->source,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ReallyExtractPath_param FAR *par = (ReallyExtractPath_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

