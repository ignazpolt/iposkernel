/********************************************************/
/*      Bearbeiten der Formate                          */
/********************************************************/
// $Header:   P:/marille/clinicum/rev/format.cpv   1.10   14 Mar 2000 19:16:04   Martin  $
// $Log:   P:/marille/clinicum/rev/format.cpv  $
// 
//    Rev 1.10   14 Mar 2000 19:16:04   Martin
// Font-Dateien im Hauptverzeichnis suchen
// 
//    Rev 1.9   12 Aug 1999 17:06:54   Martin
// default fuer FormatDescription: <exe-path>\FONTS\fi1024s.txt
// 
//    Rev 1.8   04 Nov 1997 17:55:22   Hannes
// fi...txt > 64k
// 
//    Rev 1.7   28 Feb 1996 17:26:18   MARTIN
// ReadFormatDesc=no ins ini-file schreiben auskommentiert
// 
//    Rev 1.6   02 Feb 1996 10:36:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   24 Aug 1995 00:20:14   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.4   15 May 1995 08:27:08   HANNES
// Speicherfreigabe
// 
//    Rev 1.3   30 Aug 1994 13:08:54   GERHOLD
// ueberprueft SMALL und LARGE-FONTS
// 
//    Rev 1.2   17 Aug 1994 09:36:32   HANNES
// Fontinfo aufloesungsabhaengig
// 
//    Rev 1.1   24 Jun 1994 21:01:10   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:04:58   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.10   14 Feb 1994 19:47:28   HANNES
// No change.
// 
//    Rev 1.9   12 Jan 1994 11:08:30   HANNES
// Unnoetige Includes raus, Klasse Text eleminiert
// 
//    Rev 1.8   02 Aug 1993 17:46:38   MARTIN
// #include "image.hpp"
// 
//    Rev 1.7   18 Jun 1993 15:01:14   MARTIN
// GetWindowInst
// 
//    Rev 1.6   10 May 1993 12:48:20   HANNES
// Lesen der Fontinfos
// 
//    Rev 1.5   02 Apr 1993 17:51:44   HANNES
// Fontfunktionen
// 
//    Rev 1.4   08 Mar 1993 14:10:54   HANNES
// Umstellung der Formatspeicherung
// 
//    Rev 1.3   22 Feb 1993 17:06:38   HANNES
// Lesen der Formate Benutzerunabhaengig
// 
//    Rev 1.2   14 Feb 1993 15:56:52   HANNES
// Fontselektionen fuer beide Maptypes
// 
//    Rev 1.1   04 Dec 1992 19:32:30   HANNES
// Liste neu lesen bei Namensaenderung, Handling der Formate bei leeren
// Listen
// 
//    Rev 1.0   02 Dec 1992 15:26:46   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "dds32.h"
#include "test.hpp"
#include "dds.hpp"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "globmem.h"
#include "hash.hpp"
#include "compile.hpp"

#include "dds.h"
#include "ddsmsg.h"

#define MODULENUM 124
#include "winass.hpp"

inline BOOL IsCChar (char ch)
  {
  return ((ch == ' ') || (ch == '\t') || (ch == ':') ||
          (ch == ',') || (ch == ';'));
  }

LPSTR GetNumber (LPSTR h,LONG FAR *i)
  {
  LONG res = 0;
  LONG sign;
  for ( ; IsCChar(*h) ; h++);
  if (*h == '-') {
    sign = -1;
    h++;
    }
  else
    sign = +1;
  for ( ; ((*h >= '0') && (*h <= '9')) ; h++) {
    res = res * 10 + *h - '0' ;
    }
  *i = res * sign;
  return h;
  }


LPSTR GetNumber (LPSTR h,int FAR *i)
  {
  int res = 0;
  int sign;
  for ( ; IsCChar(*h) ; h++);
  if (*h == '-') {
    sign = -1;
    h++;
    }
  else
    sign = +1;
  for ( ; ((*h >= '0') && (*h <= '9')) ; h++) {
    res = res * 10 + *h - '0' ;
    }
  *i = res * sign;
  return h;
  }

LPSTR GetNumber (LPSTR h,WORD FAR *i)
  {
  return GetNumber (h,(int FAR *) i);
  }

LPSTR GetByte (LPSTR h,BYTE FAR *i)
  {
  int b;
  LPSTR res = GetNumber (h,&b);
  *i = BYTE (b);
  return res;
  }

BOOL IsThereName (LPSTR h)
  {
  BOOL found = FALSE ;
  for ( ; ; ) {
    if ((*h == ';') || (*h == '\r') || (*h == '\0')) break;
    if (!IsCChar (*h)) {
      found = TRUE ;
      break;
      }
    }
  return found ;
  }

LPSTR GetName (LPSTR h,LPSTR name,int size)
  {
  for ( ; IsCChar(*h) ; h++);
  if (IsThereName (h)) {
    for (int i = 0 ; i < size - 1 ; i++) {
      *name++ = *h++ ;
      if (IsCChar (*h)) break ;
      }
    }
  *name = '\0';

  return h;
  }

LPSTR GetString (LPSTR h,LPSTR name,int size)
  {
  for ( ; ((*h) && (*h != '"')) ; h++);
  h++;
  if (IsThereName (h)) {
    for ( int i = 0 ; ; i++) {
      if ((*h == '\0') || (*h == '"')) break ;
      if (i < size - 1)
        *name++ = *h++ ;
      else 
        h++;
      }
    }
  if (*h == '"') h++;

  *name = '\0';

  return h;
  }

LPSTR GetNumInd (LPSTR h,WORD FAR *ind,int base,int num)
  {
  char InString[128];
  h = GetName (h,InString,sizeof(InString));
  for (int i = 0 ; i < num ; i++) {
    if (lstrcmp (InString,LRString(base+i)) == 0) {
      *ind = i;
      return h;
      }
    }
  *ind = 0;
  return h;
  }

LPSTR SearchLineEnd (char huge * h)
  {
  for ( ; ((*h) && (*h != '\n')) ; h++) ;
  if (*h == '\n') h++;
  return h;
  }

BOOL IsThereInfo (char huge * h)
  {
  BOOL colonfound = FALSE ;
  for ( ; *h ; h++) {
    if (*h == ':') {
      colonfound = TRUE ;
      break;
      }
    if (*h == '\n') break ;
    }
  return colonfound;
  }

#define IDS_FSBASE      10033
LPSTR InterpreteLine (LPSTR h,PaintContext *pc)
  {
  char huge *x;
  if (IsThereInfo (h)) {
    char linebuffer[512];
    char FAR *res = linebuffer;
    for (  x = h ; ((*x) && (*x != '\r') && (*x != '\n')) ; ) 
      *res++ = *x ++ ;
    *res ++ =  '\0' ;

    for ( ; ((*x) && ((*x == '\r') || (*x != '\n'))) ; x ++ ) ;

    FontInfo fi;
    lmemset (&fi,'\0',sizeof(fi));
    h = linebuffer;

    h = GetNumber (h,&fi.Ident);
    h = GetString (h,fi.FormatName,sizeof(fi.FormatName));
    h = GetString (h,fi.FormatDesc,sizeof(fi.FormatDesc));
    h = GetString (h,fi.lf.lfFaceName,sizeof(fi.lf.lfFaceName));
    h = GetNumber (h,&fi.cf.iPointSize);
    h = GetNumber (h,&fi.lf.lfHeight);
    h = GetNumInd (h,&fi.fei.FormatMode,IDS_FSBASE,4);
    h = GetNumber (h,&fi.fei.LineWidth);
    h = GetNumber (h,&fi.fei.xLeft);
    h = GetNumber (h,&fi.fei.xRight);
    h = GetNumber (h,&fi.lf.lfEscapement);
    h = GetNumber (h,&fi.lf.lfOrientation);
    h = GetNumber (h,&fi.lf.lfWeight);
    h = GetByte (h,&fi.lf.lfItalic);
    h = GetByte (h,&fi.lf.lfUnderline);
    h = GetByte (h,&fi.lf.lfStrikeOut);
    h = GetByte (h,&fi.lf.lfCharSet);
    h = GetByte (h,&fi.lf.lfOutPrecision);
    h = GetByte (h,&fi.lf.lfClipPrecision);
    h = GetByte (h,&fi.lf.lfQuality);
    h = GetByte (h,&fi.lf.lfPitchAndFamily);
    int r,g,b;
    h = GetNumber (h,&r);
    h = GetNumber (h,&g);
    h = GetNumber (h,&b);
    fi.cf.rgbColors = RGB(r,g,b);

    pc->InsertFormat (fi.Ident,&fi);
    }
  else
    x = SearchLineEnd (h);
  return x;
  }

LPSTR PutString (LPSTR h,LPSTR name)
  {
  *h++ = '"' ;
  lstrcpy (h,name);
  h += lstrlen(name);
  *h++ = '"' ;
  return h;
  }

LPSTR PutName (LPSTR h,LPSTR name)
  {
  lstrcpy (h,name);
  h += lstrlen(name);
  return h;
  }

LPSTR PutNumber (LPSTR h,int i)
  {
  char nstr[10];
  wsprintf (nstr,"%d",i);
  return PutName (h,nstr);
  }

LPSTR PutNumber (LPSTR h,WORD i)
  {
  return PutNumber (h,int (i));
  }

LPSTR PutByte (LPSTR h,BYTE b)
  {
  return PutNumber (h,int (b));
  }

LPSTR PutNumInd (LPSTR h,int ind,int base,int m)
  {
  return PutName (h,LRString (base+min (ind,m)));
  }

LPSTR PutColon (LPSTR h)
  {
  return PutName (h,": ");
  }

LPSTR PutComma (LPSTR h)
  {
  return PutName (h,"; ");
  }

GLOBALHANDLE WriteFormatLine (GLOBALHANDLE hGmem,FontInfo FAR *fi)
  {
  char outtxt[1024];
  LPSTR h = outtxt;
  h = PutNumber (h,fi->Ident);
  h = PutColon (h);
  h = PutString (h,fi->FormatName);
  h = PutComma (h);
  h = PutString (h,fi->FormatDesc);
  h = PutComma (h);
  h = PutString (h,fi->lf.lfFaceName);
  h = PutComma (h);
  h = PutNumber (h,fi->cf.iPointSize);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfHeight);
  h = PutComma (h);
  h = PutNumInd (h,fi->fei.FormatMode,IDS_FSBASE,4);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.LineWidth);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.xLeft);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.xRight);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfEscapement);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfOrientation);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfWeight);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfItalic);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfUnderline);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfStrikeOut);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfCharSet);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfOutPrecision);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfClipPrecision);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfQuality);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfPitchAndFamily);
  h = PutComma (h);
  int r = int (fi->cf.rgbColors & 0xFF) ;
  int g = int ((fi->cf.rgbColors >> 8) & 0xFF) ;
  int b = int ((fi->cf.rgbColors >> 16) & 0xFF) ;
  h = PutNumber (h,r);
  h = PutComma (h);
  h = PutNumber (h,g);
  h = PutComma (h);
  h = PutNumber (h,b);
  h = PutName (h,"\r\n");
  return PushToGlobBlock (hGmem,outtxt,lstrlen(outtxt));
  }

void WriteFormatInfo ()
  {
  }

extern DLLExport LPSTR _export WINAPI GetExePath (void);
GLOBALHANDLE ReadTxt (BOOL FAR *doWrite)
  {
  GLOBALHANDLE hGBuffer = 0;

  // Lesen des Blockes aus dem Textfile
  char fname[128],fpattern[128];
  GetPrivateProfileString ("Fonts","FormatDescription","",
                              fpattern,sizeof(fpattern),
                              MYINI
                          );
  if (*fpattern == '\0') {
    strcpy(fpattern,GetExePath());
    // strcat(fpattern,"fi%d%c.txt");
    strcat(fpattern,"fi1024s.txt");
    }
  int resx = GetSystemMetrics (SM_CXSCREEN);
  DWORD dbu = GetDialogBaseUnits();
  char c = (LOWORD(dbu) > 9) ? 'L' : 'S';
  wsprintf (fname,fpattern,resx,c);
  OFSTRUCT Of;
  int find = OpenFile (fname,&Of,OF_READ);
  if (find >= 0) {
    DWORD fsize = _llseek (find,0L,SEEK_END);
    _llseek (find,0L,SEEK_SET);
    hGBuffer = GlobalAlloc (GMEM_MOVEABLE,fsize + 1 + sizeof(WORD));
    char huge *buffer = (char huge *) GlobalLock (hGBuffer);
    *((WORD FAR *) buffer) = WORD (fsize + sizeof(WORD) + 1);
    _hread (find,buffer+sizeof(WORD),fsize);
    _lclose (find);
    buffer[fsize+sizeof(WORD)] = '\0';
    GlobalUnlock (hGBuffer);
#ifdef BRAUCHT_KEIN_MENSCH
    // In das Ini - File noch ein no schreiben
    WritePrivateProfileString ("Fonts","ReadFormatDesc","no",
                                MYINI
                              );
#endif
    }
  else {
    DBWIN_ASSERT_TEXT (FALSE,"No Fonts");
    }

  // Ueberpruefen, ob die Formate exportiert werden sollen
  char ppWrite[10];
  GetPrivateProfileString ("Fonts","WriteFormatDesc","no",
                              ppWrite,sizeof(ppWrite),
                              MYINI
                          );
  if (((lstrcmp(ppWrite,"yes")) == 0) && (hGBuffer))
    *doWrite = TRUE ;
  return hGBuffer;
  }

void ReadFormatInfo ()
  {
  // Lesen der Formatinfos von einem Textfile
  ////////////////////////////////////////////////
  BOOL doWrite;
  GLOBALHANDLE hGBuffer = ReadTxt (&doWrite);
  if (hGBuffer) {
    LPSTR buffer = (LPSTR)GlobalLock (hGBuffer);

    // Und los kanns gehen
    Printer *Pr = GetPrinter (TRUE);
    PaintContext pc(Pr);
    pc.LogicalTwips ();

    buffer += sizeof(WORD);
    for ( ; *buffer ; ) {
      buffer = InterpreteLine (buffer,&pc);
      }

    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);

    if (doWrite)
      WriteFormatInfo ();

    FreePrinter (Pr);
    }
  }

void UpdateFI (int Num,FontInfo FAR *fi)
  {
  WriteFormatInfo ();
  RebuildList ();
  }

DLLExport int _export WINAPI ModifyOutFormat (int Format,int OutFormat)
  {
  int res = fntModifyOutFormat (Format,OutFormat);
  if (res >= 0)
    WriteFormatInfo ();
  return res;
  }


