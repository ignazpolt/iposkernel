// $Header:   P:/marille/clinicum/compile/rev/lexscan.cpv   1.39   Dec 23 1999 16:39:36   Fiergoll  $
// $Log:   P:/marille/clinicum/compile/rev/lexscan.cpv  $
// 
//    Rev 1.39   Dec 23 1999 16:39:36   Fiergoll
// NextTerm: isstr vor isspecial
// 
//    Rev 1.38   03 Dec 1999 17:05:40   Wolfgang
// 1.) Neue String-Syntax mit \&.
// 
//    Rev 1.37   29 Sep 1999 16:55:18   Wolfgang
// 1.) finame auch bei BLOB-OpenInclude setzen.
// 
//    Rev 1.36   09 Oct 1998 18:53:16   Hannes
// Formtierungsanweisungen ignorieren
// 
//    Rev 1.35   13 Jun 1998 17:26:14   Martin
// ExePath
// 
//    Rev 1.34   07 May 1998 15:17:46   Hannes
// ; als SingleSpecial
// 
//    Rev 1.33   02 Feb 1998 20:32:10   Hannes
// BInWAllowed: Woerter durch eckige Klammern abgrenzen
// 
//    Rev 1.32   19 Nov 1997 18:45:52   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.31   27 Oct 1997 19:51:44   Hannes
// Umbau von CheckIfFullVar
// 
//    Rev 1.30   22 Sep 1997 20:02:14   Hannes
// Variablen ohne Prefix als lokale Variablen erlaubt
// 
//    Rev 1.29   16 Sep 1997 17:10:30   Hannes
// Prototyp von Blobcompiler
// 
//    Rev 1.28   04 Sep 1997 20:12:20   Hannes
// 
//    Rev 1.27   29 Aug 1997 16:52:14   gerhold
// BlobScriptCompiler::OpenInclude ... die Include Dateien werden aus einer
//                                     verschluesselten Datei gelesen.
// 
//    Rev 1.26   18 Aug 1997 18:03:26   Martin
// Realloc-Fehler
// 
//    Rev 1.25   20 Jun 1997 20:13:52   Hannes
// 
//    Rev 1.24   16 Jun 1997 07:46:44   Hannes
// '\\' in String - Defines
// 
//    Rev 1.23   09 Jun 1997 16:48:16   Hannes
// 
//    Rev 1.22   13 May 1997 17:04:54   Hannes
// Hinter einer Zahl darf '\0' stehen
// 
//    Rev 1.21   05 May 1997 10:35:16   Hannes
// 
//    Rev 1.20   13 Mar 1997 19:06:20   Hannes
// GenerateScriptFromBlob
// 
//    Rev 1.19   28 Feb 1997 14:38:42   Hannes
// Spezialzeichen -> Untersuchen der AddHash
// 
//    Rev 1.18   19 Feb 1997 12:04:18   Hannes
// Scriptfunktionen
// 
//    Rev 1.17   26 Nov 1996 07:56:42   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.16   08 Nov 1996 13:24:46   HANNES
// Einbau von QLong
// 
//    Rev 1.15   21 Oct 1996 18:50:46   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.14   24 Sep 1996 12:40:08   MARTIN
// #ifdef -> Zahlen im Identifier gehen jetzt auch hier
// 
//    Rev 1.13   04 Feb 1996 15:30:30   gerhold
// Teile aus COMPILE in DDSMEM
// 
//    Rev 1.12   02 Feb 1996 10:41:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   14 Sep 1995 09:58:32   MARTIN
// 
//    Rev 1.10   24 May 1995 17:11:30   HANNES
// Abgespeckte Version fuer SQL - Compiler
// 
//    Rev 1.9   15 May 1995 08:22:56   HANNES
// structs im normalen Script
// 
//    Rev 1.8   28 Apr 1995 17:17:12   HANNES
// No change.
// 
//    Rev 1.7   20 Mar 1995 12:08:22   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.6   24 Feb 1995 11:10:38   HANNES
// No change.
// 
//    Rev 1.5   16 Feb 1995 12:43:56   HANNES
// 
//    Rev 1.4   10 Jan 1995 14:59:20   HANNES
// Subdirectorys eingebaut
// 
//    Rev 1.3   09 Jan 1995 12:06:58   HANNES
// Debugger eingebaut
// 
//    Rev 1.2   05 Dec 1994 17:37:16   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   07 Jul 1994 22:45:12   HANNES
// InterpreteCString
// 
//    Rev 1.0   24 Jun 1994 16:30:24   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.18   31 Mar 1994 12:26:00   HANNES
// Includefiles und Bilder nicht mehr im aktuellen Pfad suchen
// 
//    Rev 1.17   04 Feb 1994 16:52:48   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.16   07 Jan 1994 12:07:54   HANNES
// Waitwin in die dmwapi.dll verlegt, Aktuelles Include File in der Wartebox
// angezeigt
// 
//    Rev 1.15   04 Jan 1994 17:28:18   HANNES
// '@' als normales Zeichen zugelassen
// 
//    Rev 1.14   09 Dec 1993 15:09:44   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.13   29 Nov 1993 08:34:48   HANNES
// Bedingte Kompilierung
// 
//    Rev 1.12   22 Sep 1993 09:47:04   GERHOLD
// Version nach St. Poelten
// 
//    Rev 1.11   20 Sep 1993 15:36:26   GERHOLD
// PaintFileInProcess
// 
//    Rev 1.10   18 Aug 1993 10:42:26   HANNES
// EscapeSequenzen in Strings
// 
//    Rev 1.9   23 Jun 1993 11:26:30   HANNES
// Huge Pointer arithmetik fuer GetLong, GetFloat..
// 
//    Rev 1.8   07 Jun 1993 15:12:14   HANNES
// Doppelter Include - Pfad
// 
//    Rev 1.7   24 May 1993 14:23:44   HANNES
// Expressions
// 
//    Rev 1.4   02 Apr 1993 18:09:12   HANNES
// ?
// 
//    Rev 1.3   08 Mar 1993 14:20:30   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.2   22 Feb 1993 17:29:40   HANNES
// Nullzeichen in Strings, Stringverwaltung
// 
//    Rev 1.1   06 Dec 1992 15:58:36   HANNES
// Korrektur eines Fehlers, der im Zusammenhang mit OpenInclude und
// Movebuffer vorkommen kann
// 
//    Rev 1.0   02 Dec 1992 16:16:44   HANNES
// Initial revision.
/*-------------------------------------------------------
        Lexical Scanner fuer den internen Compiler
        Die Daten des Scanners werden parse_var
        abgelegt, bzw. Zusatzinfo's in hPars0 und hPars1
--------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#include "btrieve.hpp"
#include "compile.hpp"
#include "scripthd.hpp"
#include "waitwin.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"

#define MODULENUM 183
#include "winass.hpp"

extern DLLExport LPSTR _export WINAPI GetExePath (void);

/*-----< character testing >--------*/
inline BOOL compiler::isspac (void) { return ((*actptr == ' ') || (*actptr == '\t')) ; }
inline BOOL compiler::isret (void) { return ((*actptr == '\r') || (*actptr == '\n')) ; }
inline BOOL compiler::isnumber (void) { return ((*actptr >= '0') && (*actptr <= '9')) ; }
inline BOOL compiler::isspecial (void) { return ((*actptr == '(') || (*actptr == ')') || 
                              (*actptr == '|') || (*actptr == '&') || 
                              (*actptr == '*') || (*actptr == '!') || 
                              (*actptr == ';') || (*actptr == ',') || 
                              (*actptr == '{') || (*actptr == '}') || 
                              (*actptr == '^') || (*actptr == '\\') ||
                              (*actptr == '<') || (*actptr == '>') ||
                              (*actptr == '/') || (*actptr == ':') ||
                              ((*actptr == '[') || (*actptr == ']') && (!BInWAllowed ())) ||
                              (*actptr == '=') || (*actptr == '%')) ; }
inline BOOL compiler::issinglespc (void) 
  { 
  return 
    (((*actptr == '(') || (*actptr == ')') || 
      (*actptr == '/') || (*actptr == ';') ||
      (*actptr == ':') || (*actptr == '{') ||
      (*actptr == '}') || (*actptr == ',') ||
      ((*actptr == '[') || (*actptr == ']') && (!BInWAllowed ())) ||
      // (*actptr == '[') || (*actptr == ']') ||
      (*actptr == '*') || (*actptr == '%') ||
      (*actptr == '+') || (*actptr == '-')
     ) ||
      (((*actptr == '!') || (*actptr == '=') ||
        (*actptr == '>')) &&
       (*((char huge *) actptr + 1) != '=')
      ) ||
      ((*actptr == '<') && 
         (!((*((char huge *) actptr + 1) == '=') || (*((char huge *) actptr + 1) == '>'))))
    );
  }
inline BOOL compiler::isdigispc (void) { return (((*actptr == '-') || (*actptr == '+')) && (*(actptr+1) >= '0') && (*(actptr+1) <= '9')); }
inline BOOL compiler::ischaralpha (void) { return (IsCharAlpha (*actptr) || (*actptr == '_') || (*actptr == '@')) ; }
inline BOOL compiler::isdecpoint (void) { return (*actptr == '.') ; }
inline BOOL compiler::ispreprstart (void) { return (*actptr == '#') ; }
inline BOOL compiler::isnull (void) { return (*actptr == '\0') ; }
inline BOOL compiler::iscomment (void) { return (*actptr == '$') ; }
inline BOOL compiler::isoperator (void) { return ((*actptr == '+') ||
                                                  (*actptr == '-') ||
                                                  (*actptr == '*') ||
                                                  (*actptr == '/')) ; }

// Daten werden vollstaendig in den Buffer geladen
/////////////////////////////////////////////////////
void compiler::incptr (void) 
  { 
  if (*actptr == '\r') incline ();
  dwChar++;

  actptr = LPSTR (((char huge *) actptr) + 1);

  if (actptr == endinclude) {
    in_include = FALSE ;
    ShowInclude ();
    actptr = MainBufferPtr;
    }
  column ++ ; 
  }

void compiler::incline (void) 
  { 
  if (in_include) IncLineNr++ ; 
  else            LineNr++ ;
  ShowWait () ; 
  column = -1 ; 
  }

DLLExport void _export WINAPI compiler::OpenInclude (char FAR *name)
  {
  // begstr zeigt auf den bereich, ab dem ausgetauscht werden soll
  // actstr zeigt auf Zeichen, bei dem es nach dem Include - File
  // Weiter gehen soll
  in_include = TRUE ;
  char nambuffer[128];
  GetIncludeFileName (name,nambuffer,finame);
  ShowInclude ();
  if ((fdi = OpenFile (nambuffer,LPOFSTRUCT (&Ofi),OF_READ)) == -1) {
    wError = INCFILENOTFOUND ;
    return ;
    }

// von Gerhold eingefuegt; bei Bedarf loeschen
//  ShowInclude (name);
/////////////////////////////////////////////////

  LONG dwisize = _llseek (fdi,0L,SEEK_END);
  _llseek (fdi,0L,SEEK_SET);
  hGIncFiles[ActIncFile] = GlobalAlloc (GMEM_MOVEABLE,dwisize+4);
  MainBufferPtr = actptr ; // LPSTR ((char huge *) actptr + 1);
  actptr = LPSTR(GlobalLock (hGIncFiles[ActIncFile]));
  endinclude = LPSTR (((char huge *) actptr) + dwisize);
  _hread (fdi,actptr,dwisize);
  // Include File wieder zumachen
  _lclose (fdi);
  ActIncFile ++;
  fdi = -1;
  IncLineNr = 1;

  if (WCaption != NULL) {
    dwfsize += dwisize;
    }
  }

extern LPSTR GetFName(LPVOID fname);
DLLExport void _export WINAPI ScriptCompiler::InstallBuffer (LPVOID name)
  {
  LPSTR Name = GetFName(name);
  for (LPSTR h = Name ; *h ; h++) if (*h == '.') break ;
  actFPrefix = LPSTR (GetGlobMem (h - LPSTR(Name) + 2));
  *actFPrefix = '@' ;
  lmemcpy (actFPrefix + 1,Name,h - Name);
  compiler::InstallBuffer (name);
  }

DLLExport void _export WINAPI BlobScriptCompiler::InstallBuffer (LPVOID name)
  {
  LPSTR Name = GetFName(name);
  for (LPSTR h = Name ; *h ; h++) if (*h == '.') break ;
  actFPrefix = LPSTR (GetGlobMem (h - LPSTR(Name) + 2));
  *actFPrefix = '@' ;
  lmemcpy (actFPrefix + 1,Name,h - Name);
  ActIncFile = 0;

  dwfsize = GlobalSize (hGSource);
  dwChar = 0 ;
  if ((hText = GlobalAlloc (GMEM_MOVEABLE,dwfsize+4)) == 0) { // Damit auch andere
                                                        // Zeigeroperationen
                                                        // am Wortende
                                                        // vorgenommen werden
                                                        // koennen
    wError = NOBUFFMEM ;
    return ;
    }
  buffer_start = begstr = actptr = LPSTR(GlobalLock (hText));
  hmemcpy (buffer_start,GlobalLock (hGSource),dwfsize);
  lstrncpy (fmname,LPSTR(name),sizeof (fmname)-1);
  act_offset = 0 ;
  in_include = FALSE ;
  endinclude = NULL ;
  fdi = -1 ;
  fd = -1 ;

  OnStartCompile();
  column = 1 ;
  }

//***************************************************************************
// Lesen der fuer den Formulargenerator  benoetigten Include-Files aus
// der verschluesselten Include-Datei
//***************************************************************************
#pragma pack(1)
struct IncHeader {
  char inc_file[13];
  long inc_offset;
  long inc_length;
  };
#pragma pack()


static unsigned char EncriptStr[8] = {
  0x0A , 0x1A , 0x7F , 0x5E , 0x0C , 0xA2 , 0xA0 , 0xA1
  };

void EncriptLis (char huge *res, char huge *Name, long Size)
  {
  long j = 0;
  for (long i = 0 ; i < Size ; i++ , j++)
    res[i] = Name[i] ^ EncriptStr[j % 8];
  }


#define  PATHBUFFERSIZE  256
LPSTR GetFullPath(LPSTR buffer, LPSTR FileName)
  {
  GetPrivateProfileString ("DataBase","SeqPath","",buffer,PATHBUFFERSIZE - 13,GetIniName ());
  // default: im EXE-Pfad suchen
  if (!*buffer)
    lstrcpy(buffer,GetExePath());
  lstrcat (buffer,FileName);
  return buffer;
  }


#define   INCCOUNT  20

HGLOBAL ReadIncludeFromSeqFile (char *filename, char FAR *includefile, long FAR *size)
  {
  OFSTRUCT of;

  *size = 0;


  char FilePath[PATHBUFFERSIZE];

  HFILE hf = OpenFile (GetFullPath(FilePath, filename), &of, OF_READ);
  if (hf == HFILE_ERROR)
    return FALSE;
  

  IncHeader ih[INCCOUNT];

  lmemset (ih, '\0', sizeof(ih));

  _llseek (hf, 0, SEEK_SET);
  _lread (hf, &ih, sizeof(ih)); 
  
  BOOL bIncludeFileFound = FALSE;
  for (int i = 0; (i < INCCOUNT); i += 1) {
    if (!lstrcmpi(ih[i].inc_file, includefile)) {
      bIncludeFileFound = TRUE;
      break;
      }
    }


  if (!bIncludeFileFound) {
    _lclose (hf);
    return NULL;
    }


  short Index  = i;
  
  
  //----------------------------------------------
  // den Offset fuer das neue Include-File suchen
  //----------------------------------------------
  _llseek (hf, ih[Index].inc_offset, SEEK_SET);

  
  long filelength = ih[Index].inc_length;

  HGLOBAL hglbl = GlobalAlloc (GHND, filelength + 4);
  if (hglbl == NULL) {
    _lclose (hf); 
    return NULL;
    }
    
  void FAR *lpBuf = GlobalLock (hglbl);
  
  long uiread = _hread (hf, lpBuf, filelength);

  *size = filelength;

  EncriptLis ((char huge*)lpBuf, (char huge*)lpBuf, ih[Index].inc_length);


  GlobalUnlock (hglbl);
  
  if (uiread != ih[Index].inc_length) {
    GlobalUnlock (hglbl);
    GlobalFree (hglbl);
    _lclose (hf);
    return FALSE;
    }
  
  _lclose (hf);
  
  return hglbl;
  }


DLLExport void _export WINAPI BlobScriptCompiler::OpenInclude (char FAR *name)
  {
  LONG dwisize;
  char errmsg[128];

  hGIncFiles[ActIncFile] = ReadIncludeFromSeqFile  ("INCLUDE.SEQ", name, &dwisize);

  wsprintf (errmsg, "Kann die Include-Datei #%d <%s> nicht lesen", ActIncFile+1, name);
  WIN_ASSERT_TEXT (hGIncFiles[ActIncFile] != NULL, errmsg);

  MainBufferPtr = actptr ;
  actptr = LPSTR(GlobalLock (hGIncFiles[ActIncFile]));
  endinclude = LPSTR (((char huge *) actptr) + dwisize);
  ActIncFile ++;
  IncLineNr = 1;
  in_include = TRUE ;
  lstrcpy (finame,name);

  if (WCaption != NULL) {
    dwfsize += dwisize;
    }
  }


DLLExport void _export WINAPI compiler::InstallBuffer (LPVOID name)
  {
  if ((fd = OpenFile (LPSTR(name),LPOFSTRUCT (&Ofm),OF_READ)) == -1) {
    wError = FILENOTFOUND ;
    return ;
    }
  dwfsize = _llseek (fd,0L,2);
  dwChar = 0 ;
  _llseek (fd,0L,0);
  if ((hText = GlobalAlloc (GMEM_MOVEABLE,dwfsize+4)) == 0) { // Damit auch andere
                                                        // Zeigeroperationen
                                                        // am Wortende
                                                        // vorgenommen werden
                                                        // koennen
    wError = NOBUFFMEM ;
    return ;
    }
  buffer_start = begstr = actptr = LPSTR(GlobalLock (hText));
  _hread(fd,buffer_start,dwfsize);
  ((char huge *)buffer_start)[dwfsize] = '\0';
  lstrncpy (fmname,LPSTR(name),sizeof (fmname)-1);
  act_offset = 0 ;
  in_include = FALSE ;
  endinclude = NULL ;
  fdi = -1 ;
  _lclose (fd);
  fd = -1 ;

  if (WCaption != NULL) {
    // Ermitteln der Filegroesse
    dwChar = 0 ;
    }
  ActIncFile = 0;

  OnStartCompile();
  column = 1 ;
  }

/*----------< String - Uebergabe >----------------*/
#define PARSESIZE     0x2000
void compiler::Push_Pars0 (char ch)
  {
#ifdef UEBERLEGT
  char FAR *base = GlobalLock (hPars0) ;
  WORD size = *((WORD FAR *) base) + 1 ;
  GlobalUnlock (hPars0);
  hPars0 = GlobalReAlloc (hPars0,size,GMEM_MOVEABLE);
  base = GlobalLock (hPars0);
  *((WORD FAR *) base) = size ;
  base [size-1] = ch ;
  GlobalUnlock (hPars0);
#else
  char FAR *base = LPSTR(GlobalLock (hPars0)) ;
  WORD size = *((WORD FAR *) base) + 1 ;
  *((WORD FAR *) base) = size ;
  base [size-1] = ch ;
  GlobalUnlock (hPars0);
#endif
  }

void compiler::Push_Pars0 (int * leadingSpaces, char ch)
  {
  for (int i = 0; i < *leadingSpaces; i++) Push_Pars0 (' ');
  *leadingSpaces = 0;
  Push_Pars0 (ch);
  }

void compiler::Push_Pars0 (int * leadingSpaces)
  {
  Push_Pars0 (leadingSpaces, *actptr);
  }

void compiler::Push_Pars0 ()
  {
  Push_Pars0 (*actptr);
  }

void compiler::Reset_Pars0 ()
  {
#ifdef UEBERLEGT
  if (hPars0)
    hPars0 = GlobalReAlloc (hPars0,sizeof (WORD),GMEM_MOVEABLE);
  else
    hPars0 = GlobalAlloc (GHND,sizeof (WORD));
#else
  if (hPars0 == 0)
    hPars0 = GlobalAlloc (GMEM_MOVEABLE,PARSESIZE);
#endif
   
  char FAR *base = LPSTR(GlobalLock (hPars0)) ;
  *((WORD FAR *) base) = sizeof (WORD) ;
  GlobalUnlock (hPars0);
  }

/*--------------< Umwandlung String -> Zahl >---------------------*/
// (string faengt bei begstr an, joert bei actptr (excl.) auf
LONG compiler::getlong (int sign,BYTE FAR *type)
  {
  LONG res = 0L;
  *type = T_INTEGER ;
  for (char _huge *h = begstr ; h < actptr ; h++) {
    if ((*h >= '0') && (*h <= '9'))
      res = res * 10 + *h - '0' ;
    else if (*h == 'L')
      *type = T_LINTEGER ;
    else if (*h == 'Q')
      *type = T_QINTEGER ;
    }
  return res * sign ;
  }

void compiler::getfloat (int sign,double FAR *result,BYTE FAR *type)
  {
  double res = 0.0;
  double div = 1.0;
  BOOL decpoint_found = FALSE ;
  *type = DECIMAL ;
  for (char _huge *h = begstr ; h < actptr ; h++) {
    if (*h == '.') decpoint_found = TRUE ;
    else if (*h == 'Q') *type = T_QINTEGER ;
    else {
      res = res * 10.0 + (double) (*h - '0') ;
      if (decpoint_found) div *= 10 ;
      }
    }

  *result = res / div * sign ;
  }

/*-------------< Durchsuchen der Hashtabellen >-------------*/
BOOL compiler::CheckKwHash (void)
  {
  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = FixKwHash();
  WORD FAR *d = (WORD FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    scv.type = KEYWORD ;
    scv.v.k_ident = *d;
    res = TRUE ;
    }
  else res = FALSE ;
  ReleaseKwHash();
  return res ;
  }

BOOL compiler::CheckAddHash (void)
  {
  if (hAddHash == NULL) return FALSE ;
  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = hAddHash;
  WORD FAR *d = (WORD FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    scv.type = BYTE(d[0]) ;
    scv.v.k_ident = d[1];
    res = TRUE ;
    }
  else res = FALSE ;
  ReleaseKwHash();
  return res ;
  }

BOOL compiler::CheckPpHash (void)
  {
  if (hPpHash == NULL) return FALSE ;

  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = FixPpHash();
  parse_var FAR *d = (parse_var FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    lmemcpy (&scv,d,sizeof (scv));
    if (d->type == STRING) {
      WORD size = * ((WORD FAR *) (d+1));
      // Hinter der Parservariable + der Laenge steht der String
#ifdef UEBERLEGT
      if (hPars0) 
        hPars0 = GlobalReAlloc (hPars0,size+sizeof (WORD),GMEM_MOVEABLE);
      else        
        hPars0 = GlobalAlloc (GHND,size);
#else
      if (hPars0 == 0) 
        hPars0 = GlobalAlloc (GHND,PARSESIZE);

#endif
      char FAR *base = LPSTR(GlobalLock (hPars0));
      * ((WORD FAR *) base) = size + sizeof (WORD);
      lmemcpy (base + sizeof (WORD),LPSTR (d+1)+sizeof(WORD),size);
      GlobalUnlock (hPars0);
      }
    res = TRUE ;
    }
  else res = FALSE ;
  ReleasePpHash();
  return res ;
  }

BOOL compiler::CheckFcHash (void)
  {
  if (hFcHash == NULL) return FALSE ;

  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = FixFcHash();
  funcdef FAR *d = (funcdef FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    scv.type = FUNCTIONID ;
    lmemcpy (&scv.v.fd,d,sizeof (scv.v.fd));
    // Hinter der Function - Definition steht die Parameterliste
    WORD size = d->parCount * sizeof (pardsc);
    if (hPars1) 
      hPars1 = GlobalReAlloc (hPars1,size,GMEM_MOVEABLE);
    else        
      hPars1 = GlobalAlloc (GHND,size);
    char FAR *base = LPSTR(GlobalLock (hPars1));
    lmemcpy (base,d+1,size);
    GlobalUnlock (hPars1);
    res = TRUE ;
    }
  else res = FALSE ;
  ReleaseFcHash();
  return res ;
  }

BOOL compiler::ChecklFHash (void)
  {
  if (hlFHash == NULL) return FALSE ;
  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = FixlFHash();
  inlinefnc_header FAR *d = (inlinefnc_header FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    scv.type = LOCALFUNCTIONID ;
    scv.v.fd.funcId = 0;        // inlinefunktionen haben keinen Id
    scv.v.fd.parCount = d->anzPars;
    scv.v.fd.ExtraCount = 0;
    // Die ganzen Daten werden nach hPars1 kopiert
    WORD size = d->progOffs + d->progSize;
    if (hPars1) 
      hPars1 = GlobalReAlloc (hPars1,size,GMEM_MOVEABLE);
    else        
      hPars1 = GlobalAlloc (GHND,size);
    char FAR *base = LPSTR(GlobalLock (hPars1));
    lmemcpy (base,d,size);
    GlobalUnlock (hPars1);
    res = TRUE ;
    }
  else res = FALSE ;
  ReleaselFHash();
  return res ;
  }

BOOL compiler::CheckenHash (void)
  {
  if (henHash == NULL) return FALSE ;
  char FAR *ident = LPSTR(GlobalLock (hPars0));
  hash *h = FixenHash();
  enumheader FAR *d = (enumheader FAR *) h->GetData (ident + sizeof (WORD));
  GlobalUnlock (hPars0);
  BOOL res ;
  if (d != NULL) {
    scv.type = ENUMVARID ;
    // Die ganzen Daten werden nach hPars2 kopiert
    WORD size = d->AnzVars * sizeof(enumvar) + sizeof(enumheader);
    if (hPars2) 
      hPars2 = GlobalReAlloc (hPars2,size,GMEM_MOVEABLE);
    else        
      hPars2 = GlobalAlloc (GHND,size);
    char FAR *base = LPSTR(GlobalLock (hPars2));
    lmemcpy (base,d,size);
    GlobalUnlock (hPars2);
    res = TRUE ;
    }
  else res = FALSE ;
  ReleaseenHash();
  return res ;
  }

extern BOOL CheckIfFullName (LPSTR Name);
extern char huge *structStart;
BOOL CheckLocalVars (LPSTR Name)
  {
  full_vardef FAR *d = (full_vardef FAR *)_actcmpl->FixLocals ()->GetData (Name);
  if (d != NULL) {
    _actcmpl->scv.type = VARID ;
    lmemcpy (&_actcmpl->scv.v.vd,d,sizeof (_actcmpl->scv.v.vd));
    // _actcmpl->scv.v.vd.TableNr = -1;
    return TRUE ;
    }
  else
    return FALSE ;
  }

extern BOOL CheckDeclareHash (LPSTR ident);
BOOL CheckDeclareHash ()
  {
  LPSTR ident = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  BOOL res = CheckDeclareHash (ident);
  GlobalUnlock (_actcmpl->hPars0);
  return res;
  }

extern ScriptContent_Entry scent;
extern short patchNextType;
BOOL myCheckVar (LPSTR ident)
  {
  BOOL res;
  if (!(res = CheckLocalVars (ident))) {
    if ((_actcmpl != NULL) && (_actcmpl->dontVarCheckGlobals)) return FALSE ;
    hash *h = _actcmpl->FixVrHash();
    full_vardef FAR *d = (full_vardef FAR *) h->GetData (ident);
    if (d != NULL) {
      _actcmpl->scv.type = VARID ;
      lmemcpy (&_actcmpl->scv.v.vd,d,sizeof (_actcmpl->scv.v.vd));
      if ((!_actcmpl->dontUnqualifiedCheck) && 
          (d->TableNr != -1) && (d->vartype != VAR_PICTURE) && (d->vartype != VAR_BITMAP)) {
#define ANALYZEUNQUALIFIEDS 1
#ifdef ANALYZEUNQUALIFIEDS
        // Um diesen Code compilierbar zu machen muss in COMPILE.HPP das protected aufgehoben werden!
        #define MYWARNINGFORMAT "INSERT INTO unqualifiedvars (datei,zeile,spalte,usedindatei,struktur,variable) VALUES ('%s',%ld,%ld,'%s','%s','%s');\r\n"
        #define COMMITSTR "\r\nCOMMIT;\r\nSET TRANSACTION USE ROLLBACK SEGMENT rb1;\r\n\r\n"
        #define COMMITAFTER 1000
        static char *_fname = "C:\\UNQUALIF.SQL";
        char myWarning[2048];
        static int myWarningCounter = 0;
        myWarningCounter++;
        char myFileName[_MAX_FNAME+_MAX_EXT];
        char fileExt[_MAX_EXT];
        char myUsedInFileName[_MAX_FNAME+_MAX_EXT];
        int lineNr;
        if (_actcmpl->in_include) {
          _splitpath (LPSTR (_actcmpl->finame), NULL, NULL, myFileName, fileExt);
          strcat (myFileName, fileExt);
          _splitpath (LPSTR (_actcmpl->fmname), NULL, NULL, myUsedInFileName, fileExt);
          strcat (myUsedInFileName, fileExt);
          lineNr = _actcmpl->IncLineNr;
          }
        else {
          _splitpath (LPSTR (_actcmpl->fmname), NULL, NULL, myFileName, fileExt);
          strcat (myFileName, fileExt);
          *myUsedInFileName = '\0';
          lineNr = _actcmpl->LineNr;
          }
        LPTABLEDEF tbd = GetTableAdmin()->GetTableDef (scent.TRef[d->TableNr].TableNr, 
                                                       scent.TRef[d->TableNr].Version);

        BOOL thisIsAField = TRUE;
        if (tbd != NULL) {
          WORD dummyDT;
          tbd->GetVarID (ident, &dummyDT, &thisIsAField);
          if (thisIsAField)
            sprintf (myWarning, MYWARNINGFORMAT, myFileName, lineNr, _actcmpl->column, myUsedInFileName, tbd->GetName (), ident);
          GetTableAdmin()->FreeTable (tbd->GetTableID(),tbd->GetVersion());
          }
        else {
          sprintf (myWarning, MYWARNINGFORMAT, myFileName, lineNr, _actcmpl->column, myUsedInFileName, "", ident);
          }

        if (thisIsAField) {
          OFSTRUCT Of;
          LPSTR fname = _fname;
          HFILE f = OpenFile (fname,&Of,OF_EXIST);
          if (f == HFILE_ERROR)
            f = OpenFile (fname,&Of,OF_CREATE);
          else {
            f = OpenFile (fname,&Of,OF_READWRITE);
            _llseek (f,0L,SEEK_END);
            }
          if (f >= 0) {
            if (myWarningCounter > COMMITAFTER)
              myWarningCounter = 1;
            if (myWarningCounter == 1)
              _lwrite (f,COMMITSTR,strlen(COMMITSTR));
            _lwrite (f,myWarning,strlen(myWarning));
            _lclose (f);
            }
          }
#endif
        }
      // scv.v.vd.TableNr = -1;
      #ifdef UEBERLEGT
      if ((d->doubleDefined) && (!dontCheckDouble))
        wError = VARDOUBLEDEFINED;
      #endif
      res = TRUE ;
      }
    else {
      res = CheckIfFullName (ident);
      }
    _actcmpl->ReleaseVrHash();
    }
  return res;
  }
BOOL compiler::CheckVrHash (void)
  {
  if ((_actcmpl != NULL) && (_actcmpl->dontVarCheck)) return FALSE ;
  if (hVrHash == NULL)        return FALSE ;
  if (structStart != NULL)    return FALSE ;

  LPSTR ident = LPSTR(GlobalLock (hPars0)) + sizeof(WORD);
  // Suchen eines Punktes und untersuchen, ob vorne eine Variable und
  // hinten eine Funktion steht.
  BOOL res = myCheckVar (ident);
  if (!res) {
    LPSTR lastP = NULL ;
    for (LPSTR f = ident ; (*f) ; f++) {
      if (*f == '.') lastP = f ;
      }
    if (lastP) {
      if ((this == _actcmpl) && (CheckDeclareHash (lastP))) {
        int neg_offs = lstrlen (lastP);
        *lastP = '\0' ;   // den Punkt ausblenden die Pointers wieder restaurieren
        actptr = LPSTR (((char huge *) actptr) - neg_offs);
        column -= neg_offs ;
        _actcmpl->wError = 0;
        if (lstrcmp (ident,"_Parent") == 0) {
          // Das als Konstante durchgehen lassen
          scv.type = STRING;
          GlobalUnlock (hPars0);
          patchNextType = -1;
          return TRUE ;
          }
        res = myCheckVar (ident);
        }
      else
        lastP = NULL ;
      }
    }
  if ((res) && (patchNextType >= 0))
    scv.v.vd.vartype = BYTE(patchNextType);
  GlobalUnlock (hPars0);
  patchNextType = -1;
  return res ;
  }

BOOL compiler::ChecklPHash (void)
  {
  BOOL res ;
  if (InInlineFunction()) {
    char FAR *ident = LPSTR(GlobalLock (hPars0));
    hash *h = FixlPHash();
    fncpardef FAR *d = (fncpardef FAR *) h->GetData (ident + sizeof (WORD));
    GlobalUnlock (hPars0);
    if (d != NULL) {
      scv.type = PARID ;
      lmemcpy (&scv.v.pd,d,sizeof (scv.v.pd));
      res = TRUE ;
      }
    else res = FALSE ;
    ReleaselPHash();
    }
  else res = FALSE ;
  return res ;
  }

/*-------< Setzen der Preprozessor - Hashtabellen >---------*/
void compiler::SetPpHash (long double ld)
  {
  if (hPpHash == NULL) return ;
  char FAR *base = LPSTR(GlobalLock (hPars0));
  hash *h = FixPpHash ();
  parse_var temp ;
  temp.type = T_QINTEGER ;
  temp.v.ld = ld ;
  if (! (h->SetData (base + sizeof (WORD),&temp,sizeof (temp)))) {
    wError = DEFALREADYSET ;
    }
  GlobalUnlock (hPars0);
  if (edp != NULL) {
    // ev. Rasterung setzen
    if (lstrcmp (base+sizeof(WORD),"RASTER_X") == 0)
      edp->raster_x = int(temp.v.int_val) ;
    else if (lstrcmp (base+sizeof(WORD),"RASTER_Y") == 0)
      edp->raster_y = int(temp.v.int_val) ;
    }
  ReleasePpHash ();
  }

void compiler::SetPpHash (LONG i,BYTE type)
  {
  if (type == T_QINTEGER)
    SetPpHash ((long double) i);
  else {
    if (hPpHash == NULL) return ;
    char FAR *base = LPSTR(GlobalLock (hPars0));
    hash *h = FixPpHash ();
    parse_var temp ;
    temp.type = type ;
    temp.v.int_val = i ;
    if (! (h->SetData (base + sizeof (WORD),&temp,sizeof (temp)))) {
      wError = DEFALREADYSET ;
      }
    GlobalUnlock (hPars0);
    if (edp != NULL) {
      // ev. Rasterung setzen
      if (lstrcmp (base+sizeof(WORD),"RASTER_X") == 0)
        edp->raster_x = int(temp.v.int_val) ;
      else if (lstrcmp (base+sizeof(WORD),"RASTER_Y") == 0)
        edp->raster_y = int(temp.v.int_val) ;
      }
    ReleasePpHash ();
    }
  }

void compiler::SetPpHash (double f)
  {
  if (hPpHash == NULL) return ;

  char FAR *base = LPSTR(GlobalLock (hPars0));
  hash *h = FixPpHash ();
  parse_var temp ;
  temp.type = DECIMAL ;
  temp.v.float_val = float (f) ;
  if (! (h->SetData (base + sizeof (WORD),&temp,sizeof (temp))))
    wError = DEFALREADYSET ;
  GlobalUnlock (hPars0);
  ReleasePpHash ();
  }

LPSTR AnalyseSeq (LPSTR h,int FAR *s)
  {
  *s = 0;
  for ( ; ; ) {
    if ((*h >= '0') && (*h <= '9')) {
      *s = *s * 10 + *h - '0' ;
      h++;
      }
    else
      break ;
    }
  return h;
  }

DLLExport BOOL _export WINAPI InterpreteCString (LPSTR d,int size,LPSTR s,int FAR *rsize)
  {
  if (lstrlen(s) > size) return FALSE ;
  LPSTR d0 = d;
  BOOL inFormat = FALSE;
  for ( ; *s ; ) {
    if (*s == '\\') {
      if (inFormat) {
        *d++ = *s++ ;
        inFormat = FALSE;
        }
      else {
        // Sonderzeichen
        s++;
        BOOL doinc = TRUE ;
        if (*s == 'r')
          *d++ = '\r' ;
        else if (*s == 'n')
          *d++ = '\n' ;
        else if (*s == 't')
          *d++ = '\t' ;
        else if (*s == '\\')
          *d++ = '\\' ;
        else if (*s == '"')
          *d++ = '"' ;
        else if (*s == '0')
          *d++ = '\0' ;
        else if (*s == 'm') {
          *d++ = '\\' ;
          *d++ = 'm' ;
          }
        else if ((*s == 'c') || (*s == 'f')) {
          *d++ = '\\' ;
          *d++ = *s ;
          inFormat = TRUE;
          }
        else if (*s == 'x') {
          int seq ;
          s++;
          s = AnalyseSeq (s,&seq);
          *d++ = char(seq);
          doinc = FALSE ;
          }
        if (doinc)
          s++;
        }
      }
    else
      *d++ = *s++;
    }
  *d++ = '\0';
  *rsize = d - d0;
  return TRUE ;
  }

void compiler::SetPpHash ()
  {
  if (hPpHash == NULL) return ;

  char FAR *base = LPSTR(GlobalLock (hPars0));
  hash *h = FixPpHash ();
  parse_var temp ;
  temp.type = STRING ;
  // Der String (begstr - actstr) und temp werden in hPars1 zusammengefasst
  int size = actptr - begstr + 1;  // ist die Groesse inc. noetigem '\0' Zeichen
  if (hPars1) 
    hPars1 = GlobalReAlloc (hPars1,size + sizeof(int) + sizeof (temp),
                                                          GMEM_MOVEABLE);
  else       
    hPars1 = GlobalAlloc (GHND,size + sizeof(int) + sizeof (temp));
  char FAR *buffer = LPSTR(GlobalLock (hPars1));
  lmemcpy (buffer,&temp,sizeof (temp));
  // Kopieren des Strings
  char FAR *s = begstr ;
  char FAR *d = buffer + sizeof(temp) + sizeof(WORD);
  BOOL inFormat = FALSE ;
  for ( ; s < actptr ; ) {
    if (*s == '\\') {
      if (inFormat) {
        *d++ = *s++ ;
        inFormat = FALSE;
        }
      else {
        // Sonderzeichen
        s++;
        BOOL doinc = TRUE ;
        if (*s == 'r')
          *d++ = '\r' ;
        else if (*s == 'n')
          *d++ = '\n' ;
        else if (*s == 't')
          *d++ = '\t' ;
        else if (*s == '\\')
          *d++ = '\\' ;
        else if (*s == '"')
          *d++ = '"' ;
        else if (*s == '0')
          *d++ = '\0' ;
        else if (*s == 'm') {
          *d++ = '\\' ;
          *d++ = 'm' ;
          }
        else if ((*s == 'c') || (*s == 'f')) {
          *d++ = '\\' ;
          *d++ = *s ;
          inFormat = TRUE;
          }
        else if (*s == 'x') {
          int seq ;
          s++;
          s = AnalyseSeq (s,&seq);
          *d++ = char(seq);
          doinc = FALSE ;
          }
        if (doinc)
          s++;
        }
      }
    else
      *d++ = *s++;
    }
  *d++ = '\0';
  // Groesse des Strings eintragen
  *((WORD FAR *) (buffer + sizeof(temp))) = 
          (d - (buffer + sizeof(temp) + sizeof(WORD)));
  if (! (h->SetData (base + sizeof (WORD),buffer,d - buffer)))
    wError = DEFALREADYSET ;

  if (edp != NULL) {    // Der Editor will die Stringdefines haben
    full_vardef fvd;
    fvd.vartype = VAR_EDDEF;
    PushToVarTable (base + sizeof(WORD),&fvd);
    }

  GlobalUnlock (hPars1);
  GlobalUnlock (hPars0);
  ReleasePpHash ();
  }

/*-------------------< Hauptprogramm des Parsers >-----------------------*/
static BOOL testdef;
static BOOL invertdef;
static int  ifdefcount;
void compiler::NextTerm ()
  {
  BOOL ready ;
  int sign;
  if (dont_read) {
    dont_read = FALSE ;
    opAllowed = FALSE ;
    return ;
    }
  int state = STATE_NORMAL ;
  begstr = actptr ;
  BOOL strbeg = FALSE;
  BOOL checkForBClose = FALSE;
  BOOL inFormat;
  BOOL stringContinue = FALSE;
  BOOL stringContinuePermanent = FALSE;
  BOOL stringContinueWithLine = FALSE;
  int spacesAtEnd = 0;

  for ( ready = FALSE ; !ready ; ) {
    switch (state) {
      case STATE_NORMAL    :
        begstr = actptr;
        if (isnull ()) {
          ready = TRUE ;
          PrgEnd = TRUE ;
          }
        else if ((*actptr == '[') && (BInWAllowed())) {
          checkForBClose = TRUE ;
          Reset_Pars0();
          state = STATE_WORD ;
          }
        else if ((isspac()) || (isret())) {
          incptr ();
          begstr = actptr ;
          }
        else if ((ischaralpha()) || ((AllowOperator()) && (isoperator()))) {
          state = STATE_WORD ;  // begstr zeigt auf den Anfang des Wortes
          Reset_Pars0();
          }
        else if ((isnumber ()) || (isdigispc ())) {
          if (isdigispc ()) {
            if (*actptr == '-') sign = -1 ;
            else                sign = +1 ;
            incptr ();
            begstr = actptr ;
            }
          else
            sign = 1 ;
          state = STATE_NUMBER ;
          incptr ();
          }
        else if (isdecpoint ()) {
          incptr ();
          if (ischaralpha()) {
            actptr = LPSTR (((char huge *) actptr) - 1);
            column--;
            state = STATE_WORD ;  // begstr zeigt auf den Anfang des Wortes
            Reset_Pars0();
            }
          else {
            state = STATE_DEC ;
            sign = +1 ;
            }
          }
        else if (isstrsign ()) {
          state = STATE_STRING ;
          stringContinue = FALSE;
          stringContinuePermanent = FALSE;
          stringContinueWithLine = FALSE;
          inFormat = FALSE;
          incptr ();
          begstr = actptr;
          Reset_Pars0();
          }
        else if (isspecial()) {
          state = STATE_SPCWORD ;  // begstr zeigt auf den Anfang des Wortes
          Reset_Pars0();
          }
        else if (iscomment ()) {
          state = STATE_COMMENT ;
          incptr ();
          begstr = actptr ;
          }
        else if (ispreprstart ()) {
          state = STATE_PREPROC ;
          incptr ();
          begstr = actptr;
          }
        else {
          // Unbekanntes Zeichen
          ready = TRUE ;
          wError = UNKNOWNCHAR ;
          }
        break ;
      case STATE_STRING    :
        if (*actptr == '\\') {
          if (inFormat) {
            incptr();
            Push_Pars0 (&spacesAtEnd, '\\');
            inFormat = FALSE;
            }
          else {
            incptr () ;
            BOOL doinc = TRUE ;
            if (*actptr == 'r') Push_Pars0 (&spacesAtEnd, '\r') ;
            else if (*actptr == 'n') Push_Pars0 (&spacesAtEnd, '\n') ;
            else if (*actptr == 't') Push_Pars0 (&spacesAtEnd, '\t') ;
            else if (*actptr == '\\') Push_Pars0 (&spacesAtEnd, '\\') ;
            else if (*actptr == '"')  Push_Pars0 (&spacesAtEnd, '"') ;
            else if (*actptr == '0') Push_Pars0 (&spacesAtEnd, '\0') ;
            else if (*actptr == 'm') Push_Pars0 (&spacesAtEnd, '\\') , Push_Pars0 (&spacesAtEnd, 'm') ;
            else if ((*actptr == 'c') || (*actptr == 'f')) {
              Push_Pars0 (&spacesAtEnd, '\\');
              Push_Pars0 (&spacesAtEnd, *actptr);
              inFormat = TRUE;
              }
            else if (*actptr == 'x') {
              int seq;
              incptr () ;
              LPSTR newActptr = AnalyseSeq (actptr,&seq);
              column += (newActptr - actptr);
              actptr = newActptr;
              Push_Pars0 (&spacesAtEnd, seq) ;
              doinc = FALSE ;
              }
            else if (*actptr == '&') {
              if (spacesAtEnd > 0)
                Push_Pars0 (&spacesAtEnd - 1, ' ');
              incptr () ;
              if (*actptr == '+') {
                stringContinue = TRUE;
                stringContinuePermanent = TRUE;
                }
              else if (*actptr == '*') {
                stringContinue = TRUE;
                stringContinuePermanent = TRUE;
                stringContinueWithLine = TRUE;
                }
              else if (*actptr == '-') {
                stringContinue = FALSE;
                stringContinuePermanent = FALSE;
                stringContinueWithLine = FALSE;
                }
              else {
                doinc = FALSE ;
                for ( ; isspac() ; incptr () );
                if (!isret()) {
                  // Nach \& darf nur +, *, - oder Zeilenumbruch kommen
                  ready = TRUE ;
                  wError = SYNTAX_ERROR ;
                  }
                else
                  stringContinue = TRUE;
                }

              }
            if (doinc)
              incptr () ;
            }
          begstr = actptr ;
          }
        else if (isstrsign()) {
          Push_Pars0 (&spacesAtEnd, '\0');
          incptr ();
          scv.type = STRING;
          ready = TRUE ;
          }
        else if (isret()) {
          spacesAtEnd = 0;
          incptr ();
          if (isret()) // \n auch noch ueberlesen
            incptr ();
          if (stringContinueWithLine)
            Push_Pars0 (&spacesAtEnd, '\r') ;
          if (stringContinue) {
            for ( ; isspac(); incptr () );
            if (*actptr != '&') {
              // Zeile im Continue-Modus muss mit & anfangen
              ready = TRUE ;
              wError = SYNTAX_ERROR ;
              }
            else
              incptr();
            }
          stringContinue = stringContinuePermanent;
          begstr = actptr;
          }
        else if (isspac() && stringContinue) {
          spacesAtEnd++;
          incptr () ;
          begstr = actptr;
          }
        else {
          Push_Pars0 (&spacesAtEnd);
          incptr ();
          begstr = actptr;
          }
        break ;
      case STATE_NUMBER    :
        if ((isnumber()) || (*actptr == 'L') || (*actptr == 'Q')) {
          incptr ();
          }
        else if (isdecpoint()) {
          incptr ();
          state = STATE_DEC ;
          }
        else if ((isspac()) || (isret()) || (iscomment()) || (isspecial()) || (isnull())) {
          ready = TRUE ;
          long ival = getlong (sign,&scv.type);
          if (scv.type == T_QINTEGER)
            scv.v.ld = (long double) ival;
          else
            scv.v.int_val = ival ;
          }
        else {
          // Ungueltige Nummer ;
          ready = TRUE ;
          wError = INVNUMBER ;
          }
        break ;
      case STATE_DEC       :
        if ((isnumber()) || (*actptr == 'Q')) {
          incptr ();
          }
        else if ((isspac()) || (isret()) || (iscomment()) || (isspecial()) || (isnull())) {
          ready = TRUE ;
          double fv;
          getfloat (sign,&fv,&scv.type);
          if (scv.type == DECIMAL)
            scv.v.float_val = (float) fv;
          else
            scv.v.ld = (long double) fv;
          }
        else {
          // Ungueltiger float
          ready = TRUE ;
          wError = INVDEC ;
          }
        break ;
      case STATE_WORD      :
        {
        BOOL str_ready = FALSE ;
        if (checkForBClose) {
          if (*actptr == ']')
            checkForBClose = FALSE ;
          Push_Pars0 ();
          incptr ();
          }
        else {
          if ((isoperator()) && (!strbeg)) {
            Push_Pars0 ();
            incptr ();
            str_ready = TRUE ;
            }
          else if ((ischaralpha()) || (isnumber()) || (isdecpoint())) {
            Push_Pars0 ();
            incptr ();
            begstr = actptr ;
            }
          else if ((isspac()) || (isret()) || (iscomment()) || (isspecial()) ||
                  (isnull ()) || ((isoperator ()) && (strbeg))) {
            str_ready = TRUE ;
            }
          else {
            // Ungueltiges Zeichen
            ready = TRUE ;
            wError = UNKNOWNCHAR ;
            }
          }

        strbeg = TRUE ;

        if (str_ready) {
          ready = TRUE ;
          Push_Pars0('\0');     // String muss auf jeden Fall mit '\0' abgeschlossen werden
          // Untersuchen saemtlicher Hashtabellen
          if (CheckKwHash()) ;          // Keyword
          else if (CheckAddHash()) ;    // Zusaetzliche Typen
          else if (CheckPpHash()) ;     // Preprozessor (define's)
          else if (CheckFcHash()) ;     // Funktion
          else if (CheckefHash()) ;     // expression Function
          else if ((this == _actcmpl) && (CheckDeclareHash())) ;     // expression virt. Function
          else if (CheckVrHash()) ;     // Variable
          else if (ChecklPHash()) ;     // Parameter (nur waehrend der def.
                                        // einer lok. Funktion)
          else if (ChecklFHash()) ;     // inline Funktion
          else if (CheckenHash()) ;     // enum Variable
          else if (CheckopHash()) ;     // Operator
          else if (CheckcmpHash()) ;    // Vergleichsoperator
          else {
            // in den Hash - Tabellen nicht gefunden -> Direkt uebergeben
            scv.type = UNKNOWNIDENT ;
            }
          }
        }
        break ;
      case STATE_SPCWORD      :
        if ((isspecial()) && (!issinglespc ())) {
          Push_Pars0 ();
          incptr ();
          begstr = actptr ;
          }
        else if (issinglespc ()) {
          // Wenn es sich um Sonderzeichen handelt, die prinzipiell
          // nur aus einem Zeichen bestehen, Zeichen schreiben und abbrechen
          Push_Pars0 ();
          BOOL cSpecial = ((*actptr == '=') || (*actptr == '<') || (*actptr == '>'));
          incptr ();
          begstr = actptr ;
          ready = TRUE ;
          Push_Pars0('\0');     // String muss auf jeden Fall mit '\0' abgeschlossen werden
          // Untersuchen der Keyword - Hashtabellen
          if ((!CheckAddHash()) && (!CheckKwHash()) && (!CheckcmpHash())) {          // Keyword
            if (cSpecial)
              // gueltiges Sonderzeichen -> als Unknown durchlassen ('==', '!=', '>', '<')
              scv.type = UNKNOWNIDENT ;
            else
              // Ungueltiges Sonderzeichen -> Syntax - Error
              wError = SYNTAX_ERROR ;
            ready = TRUE ;
            }
          }
        else if ((isspac()) || (isret()) || (iscomment()) ||
                 (ischaralpha()) || (isnumber()) || (isdecpoint()) ||
                 (isstrsign()) || (isdigispc()) || (isnull())) {
          ready = TRUE ;
          Push_Pars0('\0');     // String muss auf jeden Fall mit '\0' abgeschlossen werden
          // Untersuchen der Keyword - Hashtabellen
          if (!CheckKwHash()) {          // Keyword
            // Ungueltiges Sonderzeichen -> Syntax - Error
            ready = TRUE ;
            wError = SYNTAX_ERROR ;
            }
          }
        else {
          // Ungueltiges Zeichen
          ready = TRUE ;
          wError = UNKNOWNCHAR ;
          }
        break ;
      case STATE_COMMENT   :
        if ((isret ()) || (isnull())) {         // Return ist das Ende eines Kommentares
          incptr () ;
          begstr = actptr ;
          state = STATE_NORMAL ;
          }
        else {
          incptr () ;
          begstr = actptr ;
          }
        break ;
      case STATE_PREPROC   :
        if (ischaralpha ()) {
          incptr ();
          }
        else if ((isspac ()) || (isret())) {
          char oldchar = *actptr;
          *actptr = '\0' ;
          if (lstrcmp ("define",begstr) == 0) {
            state = STATE_DEFSPACE0 ;
            *actptr = oldchar ;
            begstr = actptr ;
            incptr ();
            }
          else if (lstrcmp ("include",begstr) == 0) {
            state = STATE_INCSPACE ;
            *actptr = oldchar ;
            incptr ();
            }
          else if (lstrcmp ("edit",begstr) == 0) {
            if (EditFound) wError = MULTIEDITFIELD;
            InEdit = TRUE ;
            *actptr = oldchar ;
            if (edp != NULL)
              edp->BegField = actptr;
            EditFound = TRUE;
            incptr ();
            state = STATE_NORMAL;
            }
          else if (lstrcmp ("endedit",begstr) == 0) {
            InEdit = FALSE ;
            *actptr = oldchar;
            if (edp != NULL)
              edp->EndField = LPSTR ((char huge *) begstr - 1) ;
            incptr ();
            state = STATE_NORMAL;
            }
          else if (lstrcmp ("ifdef",begstr) == 0) {
            *actptr = oldchar;
            state = STATE_PREPIF ;
            invertdef = FALSE ;
            testdef = TRUE;
            }
          else if (lstrcmp ("ifndef",begstr) == 0) {
            *actptr = oldchar;
            state = STATE_PREPIF ;
            invertdef = TRUE ;
            testdef = TRUE;
            }
          else if (lstrcmp ("else",begstr) == 0) {
            *actptr = oldchar;
            state = STATE_PREPIF ;
            ifdefcount = 1 ;
            testdef = FALSE;
            }
          else if (lstrcmp ("endif",begstr) == 0) {
            *actptr = oldchar;
            state = STATE_NORMAL;
            }
          else {
            // Unbekanntes Preprozessor - Kommando
            wError = UNKNOWNCOMMAND ;
            ready = TRUE ;
            }
          }
        else {
          // Unbekanntes Preprozessor - Kommando
          wError = UNKNOWNCOMMAND ;
          ready = TRUE ;
          }
        break ;
      case STATE_PREPIF :
        if (testdef) {
          // Das naeschset Wort lesen
          for ( ; !ischaralpha() ; incptr () );
          begstr = actptr;
          for ( ; ischaralpha () || isnumber() ; incptr () );
          char oldchar = *actptr ;
          *actptr = '\0';
          hash *h = FixPpHash();
          parse_var FAR *d = (parse_var FAR *) h->GetData (begstr);
          *actptr = oldchar;
          if (((d != NULL) && (!invertdef)) || ((d == NULL) && (invertdef)))
            state = STATE_NORMAL ;
          else
            ifdefcount = 1 ;
          testdef = FALSE ;
          }
        if (ispreprstart ()) {
          incptr ();
          begstr = actptr ;
          for ( ; ischaralpha () ; incptr () ) ;
          char oldchar = *actptr ;
          *actptr = '\0';
          if (lstrcmp (begstr,"endif") == 0) {
            if (-- ifdefcount == 0)
              state = STATE_NORMAL ;
            }
          else if ((lstrcmp (begstr,"else") == 0) && (ifdefcount == 1)) {
            ifdefcount -- ;
            state = STATE_NORMAL ;
            }
          else if ((lstrcmp (begstr,"ifdef") == 0) || (lstrcmp (begstr,"ifndef") == 0))
            ifdefcount ++ ;
          *actptr = oldchar;
          }
        else if (isnull ()) {
          ready = TRUE ;
          PrgEnd = TRUE ;
          }
        else
          incptr ();
        break ;
      case STATE_INCSPACE  :
        if (isstrsign()) {
          incptr ();
          w0 = actptr ;
          state = STATE_INCFNAME ;
          }
        else if (isspac ()) {
          incptr () ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_INCFNAME  :
        if (isstrsign ()) {
          *actptr = '\0' ;
          incptr ();
          OpenInclude (w0) ;
          if (wError == 0) state = STATE_NORMAL ;
          else ready = TRUE ;
          }
        else if ((isret()) || (isnull()) || (isspac())) {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        else
          incptr ();
        break ;
      case STATE_DEFSPACE0 :
        if (isspac ()) {
          incptr ();
          begstr = actptr ;
          }
        else if (ischaralpha ()) {
          Reset_Pars0 ();
          state = STATE_DEFIDENT ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_DEFIDENT  :
        if ((ischaralpha ()) || (isnumber())) {
          Push_Pars0 ();
          incptr ();
          begstr = actptr ;
          }
        else if (isspac ()) {
          Push_Pars0 ('\0') ;   // Ident mit '\0' abschliessen
          incptr ();
          begstr = actptr ;
          state = STATE_DEFSPACE1 ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_DEFSPACE1 :
        if (isstrsign ()) {
          state = STATE_DEFSTR ;
          incptr ();
          begstr = actptr ;
          }
        else if ((isnumber ()) || (isdigispc ())) {
          if (isdigispc ()) {
            if (*actptr == '-') sign = -1 ;
            else                sign = +1 ;
            incptr ();
            begstr = actptr ;
            }
          else
            sign = +1 ;
          state = STATE_DEFNUMBER ;
          incptr ();
          }
        else if (isdecpoint ()) {
          state = STATE_DEFDEC ;
          incptr ();
          }
        else if (isspac ()) {
          incptr ();
          begstr = actptr ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_DEFNUMBER :
        if ((isnumber ()) || (*actptr == 'L')) {
          incptr ();
          }
        else if (isdecpoint ()) {
          state = STATE_DEFDEC ;
          incptr ();
          }
        else if ((isspac ()) || (isret ())) {
          BYTE type ;
          LONG res = getlong (sign,&type);
          SetPpHash (res,type) ;
          begstr = actptr ;
          if (wError == 0) 
            state = STATE_NORMAL ;
          else
            ready = TRUE ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_DEFDEC    :
        if (isnumber ()) {
          incptr ();
          }
        else if ((isspac ()) || (isret ())) {
          double fv;
          BYTE type;
          getfloat (sign,&fv,&type);
          if (type == DECIMAL)
            SetPpHash (fv) ;
          else
            SetPpHash ((long double) fv) ;
          begstr = actptr ;
          if (wError == 0)
            state = STATE_NORMAL ;
          else
            ready = TRUE ;
          }
        else {
          // Preprozessor - Syntaxerror
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        break ;
      case STATE_DEFSTR    :
        if (isstrsign ()) {
          SetPpHash ();
          begstr = actptr ;
          if (wError == 0) {
            incptr ();
            begstr = actptr ;
            state = STATE_NORMAL ;
            }
          else
            ready = TRUE ;
          }
        else if (*actptr == '\\') {
          incptr() ;  // naechstes zeichen nicht interpretieren
          incptr() ;
          }
        else if (isret ()) {
          // Return's sind in define - Anweisungen im String verboten !!!
          wError = PREPSYNTAXERROR ;
          ready = TRUE ;
          }
        else {
          incptr ();    // Ansonsten ist im String alles erlaubt
          }
        break ;
      }
    }
  opAllowed = FALSE ;
  }

