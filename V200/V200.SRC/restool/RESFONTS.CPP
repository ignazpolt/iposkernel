////////////////////////////////////////////////////////////
//  Bearbeiten von Fonts in Restool
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/resfonts.cpv   1.10   05 Oct 1998 11:27:32   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/resfonts.cpv  $
// 
//    Rev 1.10   05 Oct 1998 11:27:32   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.9   05 Nov 1997 08:58:36   Gerhold
// 32 Bit
// 
//    Rev 1.8   04 Nov 1997 17:19:44   Gerhold
// mehr als 64K Formate
// 
//    Rev 1.7   28 Aug 1997 15:51:42   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   02 Feb 1996 10:50:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   02 Jan 1995 18:33:26   HANNES
// 
//    Rev 1.4   02 Jan 1995 16:42:18   GERHOLD
// Font fuer den Editpr aus der INI-Datei lesen
// 
//    Rev 1.3   02 Jan 1995 09:31:06   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.2   30 Aug 1994 13:16:28   GERHOLD
// fi%d auf fi%d%c fuer Small und Large fonts erweitert
// 
//    Rev 1.1   17 Aug 1994 09:33:58   HANNES
// Fontnamen aufloesungsabhaengig
// 
//    Rev 1.0   24 Jun 1994 16:54:48   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"


#include "globmem.h"

#include "font.hpp"
#include "printer.hpp"

#include "hash.hpp"
#include "compile.hpp"

#include "restool.hpp"

#define MODULENUM 125
#include "winass.hpp"

inline BOOL IsCChar (char ch)
  {
  return ((ch == ' ') || (ch == '\t') || (ch == ':') ||
          (ch == ',') || (ch == ';'));
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

LPSTR GetNumber (LPSTR h,LONG FAR *i)
  {
// LONG FAR *i raus !!! in 32 Bit war ein Stack Overflow
//  return GetNumber (h,(LONG FAR *) i);
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

extern HINSTANCE MyInstance;
LPSTR LRString(int ind)
  {
  static char instr[64];
  LoadString (MyInstance,ind,instr,sizeof(instr));
  return instr;
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

LPSTR InterpreteLine (LPSTR h)
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
    h = GetNumInd (h,&fi.fei.FormatMode,RCFI_BASE,4);
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

    fntInsertFormat (fi.Ident,&fi);
    }
  else
    x = SearchLineEnd (h);
  return x;
  }

GLOBALHANDLE ReadTxt ()
  {
  GLOBALHANDLE hGBuffer = 0;

  // Lesen des Blockes aus dem Textfile
  char fname[128],fpattern[128];
  GetPrivateProfileString ("Fonts","FormatDescription","fi%d%c.txt",
                              fpattern,sizeof(fpattern),
                              MYINI
                          );
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
    char huge *buffer = (char huge *)GlobalLock (hGBuffer);
    *((WORD FAR *) buffer) = WORD (fsize + sizeof(WORD) + 1);
    _hread (find,buffer+sizeof(WORD),fsize);
    _lclose (find);
    buffer[fsize+sizeof(WORD)] = '\0';
    GlobalUnlock (hGBuffer);
    }
  else {
    WIN_ASSERT_TEXT (FALSE,"No Fonts");
    }

  return hGBuffer;
  }

void ReadFormatInfo ()
  {
  // Lesen der Formatinfos von einem Textfile
  ////////////////////////////////////////////////
  GLOBALHANDLE hGBuffer = ReadTxt ();
  if (hGBuffer) {
    LPSTR buffer = (LPSTR)GlobalLock (hGBuffer);

    buffer += sizeof(WORD);
    for ( ; *buffer ; ) {
      buffer = InterpreteLine (buffer);
      }

    GlobalUnlock (hGBuffer);
    GlobalFree (hGBuffer);
    }
  }



extern LPSTR IniFile();
//----------------------------------------------------------------------------
// Liest aus der Ini-Datei den Font-Eintrag fuer den Editor
//----------------------------------------------------------------------------
const int FONTSIZE = 128;
HFONT GetEditorFont ()
  {
  LOGFONT lf;
  char szDefault[] = "-13; 0; 0; 0; 400; 0; 0; 0; 0; 1; 2; 1; 31; \"Courier\"";
  char OutText[FONTSIZE];

  LPSTR szFont = OutText; 
  GetPrivateProfileString ("EDITOR", "Font", szDefault, szFont, FONTSIZE, IniFile());

  lmemset (&lf,'\0',sizeof(lf));

  szFont = GetNumber (szFont, &lf.lfHeight);
  szFont = GetNumber (szFont, &lf.lfWidth);
  szFont = GetNumber (szFont, &lf.lfEscapement);
  szFont = GetNumber (szFont, &lf.lfOrientation);
  szFont = GetNumber (szFont, &lf.lfWeight);
  szFont = GetByte (szFont, &lf.lfItalic);
  szFont = GetByte (szFont, &lf.lfUnderline);
  szFont = GetByte (szFont, &lf.lfStrikeOut);
  szFont = GetByte (szFont, &lf.lfCharSet);
  szFont = GetByte (szFont, &lf.lfOutPrecision);
  szFont = GetByte (szFont, &lf.lfClipPrecision);
  szFont = GetByte (szFont, &lf.lfQuality);
  szFont = GetByte (szFont, &lf.lfPitchAndFamily);
  szFont = GetString (szFont, lf.lfFaceName, sizeof(lf.lfFaceName));

  return CreateFontIndirect (&lf);
  }
  
  
