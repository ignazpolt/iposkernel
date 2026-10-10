// $Header:   P:/marille/clinicum/compile/rev/compile.cpv   1.43   29 Sep 1999 16:55:14   Wolfgang  $
// $Log:   P:/marille/clinicum/compile/rev/compile.cpv  $
// 
//    Rev 1.43   29 Sep 1999 16:55:14   Wolfgang
// 1.) Zykluspruefung und Vermeidung doppelter Generierung.
// 
//    Rev 1.42   26 Apr 1999 18:10:02   Wolfgang
// 1.) Bei Fehlern in Sub-Files (ERRORINIMPORTED) wird letzter Fehler 
//     unveraendert gelassen.
// 2.) Fehlermeldung bei Includefile enthaelt jetzt auch Hauptfilename.
// 
//    Rev 1.41   26 Mar 1999 18:15:18   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.40   12 Mar 1999 14:41:02   Wolfgang
// 1.) LastErrorNr fuer IsCompileAborted neu.
// 
//    Rev 1.39   05 Oct 1998 11:05:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.38   26 Jan 1998 19:59:28   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.37   05 Jan 1998 07:49:24   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.36   22 Sep 1997 20:02:18   Hannes
// Variablen ohne Prefix als lokale Variablen erlaubt
// 
//    Rev 1.35   22 Sep 1997 12:37:06   Hannes
// Beschleunigung des Blob - Compilers
// 
//    Rev 1.34   16 Sep 1997 17:10:26   Hannes
// Prototyp von Blobcompiler
// 
//    Rev 1.33   22 Aug 1997 12:01:50   Hannes
// TwoDim: GetGlobalMem ausgebaut
// 
//    Rev 1.32   27 May 1997 11:20:08   Hannes
// Private Strukturen im Scriptkompilat, L. als Expression
// 
//    Rev 1.31   28 Apr 1997 11:18:20   Hannes
// Vorinstallieren von Defines
// 
//    Rev 1.30   23 Apr 1997 17:09:22   Hannes
// Freigabe von hGText
// 
//    Rev 1.29   13 Mar 1997 19:05:36   Hannes
// GenerateScriptFromBlob
// 
//    Rev 1.28   28 Feb 1997 14:38:06   Hannes
// ParseNow,PrepareParse
// 
//    Rev 1.27   19 Feb 1997 12:04:16   Hannes
// Scriptfunktionen
// 
//    Rev 1.26   04 Dec 1996 09:09:54   HANNES
// Die Breakhistory in einen Stack
// 
//    Rev 1.25   26 Nov 1996 07:56:46   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.24   30 Oct 1996 08:41:42   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.23   21 Oct 1996 18:50:46   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.22   17 Jun 1996 15:28:02   HANNES
// Einfuehrung von BLOBS
// 
//    Rev 1.21   04 Feb 1996 15:29:24   hannes
// Teile aus COMPILE in DDSMEM
// 
//    Rev 1.20   02 Feb 1996 10:41:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.19   15 Sep 1995 20:41:44   HANNES
// Schwere Fehlerkorrektur ... PrgEnd, Sytnaxerkennung verbessert
// 
//    Rev 1.18   05 Sep 1995 14:26:36   GERHOLD
// Fehlermeldung anzeigen (WMU_SETERRORTEXT)
// 
//    Rev 1.17   02 Aug 1995 09:59:08   HANNES
// Prioritaetenhandling, verb. Fehlerabfrage, verb. Kapselung
// 
//    Rev 1.16   11 Jul 1995 12:44:16   HANNES
// Statische Daten in die Klasse
// 
//    Rev 1.15   14 Jun 1995 13:05:56   HANNES
// PropCodeGen in des Konstruktor verlagert
// 
//    Rev 1.14   29 May 1995 12:45:14   HANNES
// Destruktor des Compilers: delete BitArr
// 
//    Rev 1.13   24 May 1995 18:29:18   HANNES
// 
//    Rev 1.12   24 May 1995 17:11:30   HANNES
// Abgespeckte Version fuer SQL - Compiler
// 
//    Rev 1.11   15 May 1995 08:22:54   HANNES
// structs im normalen Script
// 
//    Rev 1.10   02 Apr 1995 13:23:44   HANNES
// 
//    Rev 1.9   27 Mar 1995 13:18:04   HANNES
// 
//    Rev 1.8   24 Mar 1995 18:34:50   GERHOLD
// 
//    Rev 1.7   24 Mar 1995 18:33:52   GERHOLD
// 
//    Rev 1.6   23 Mar 1995 11:48:46   GERHOLD
// SetCmdLineFlag, ShowMsg erweitert um LogMsg (schreibt Fehler in Datei)!
// 
//    Rev 1.5   16 Feb 1995 12:43:54   HANNES
// 
//    Rev 1.4   30 Jan 1995 15:04:44   GERHOLD
// 
//    Rev 1.3   09 Jan 1995 12:06:58   HANNES
// Debugger eingebaut
// 
//    Rev 1.2   05 Dec 1994 17:36:18   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   21 Sep 1994 15:47:56   HANNES
// LastErrorFile vergroessert
// 
//    Rev 1.0   24 Jun 1994 16:30:24   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.15   22 Feb 1994 15:28:04   HANNES
// WriteSizeStat aus dem WEP raus
// 
//    Rev 1.14   09 Feb 1994 12:10:48   HANNES
// 
//    Rev 1.13   09 Feb 1994 12:02:06   HANNES
// Wartefenster richtig erzeugt
// 
//    Rev 1.12   04 Feb 1994 16:52:40   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.11   11 Jan 1994 19:04:06   HANNES
// Abbrechen Knopf im Wartefenster, Fensterhirarchie richtig geordnet
// 
//    Rev 1.10   07 Jan 1994 12:07:04   HANNES
// Waitwin in die dmwapi.dll verlegt, Aktuelles Include File in der Wartebox
// angezeigt
// 
//    Rev 1.9   09 Dec 1993 15:09:34   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.8   20 Jul 1993 12:36:48   HANNES
// Icons fuer die Dokumente
// 
//    Rev 1.7   24 May 1993 14:23:20   HANNES
// Expressions
// 
//    Rev 1.6   02 Apr 1993 18:08:04   HANNES
// ?
// 
//    Rev 1.5   11 Mar 1993 20:06:00   HANNES
// ???
// 
//    Rev 1.4   08 Mar 1993 14:19:38   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.3   22 Feb 1993 17:27:54   HANNES
// Code auf mehrere Records aufteilen, unabhaengiges Konstantensegment
// 
//    Rev 1.2   18 Jan 1993 16:58:20   HANNES
// Kategorie im Header eingefuegt
// 
//    Rev 1.1   13 Jan 1993 18:54:56   HANNES
// Veraenderungen des Headers eines Dokumentes
// 
//    Rev 1.0   02 Dec 1992 16:15:52   HANNES
// Initial revision.
/*-----------------------------------------------------
        Hauptbestandteil des Compilers
        Aufbau der Datenstrukturen
        Steuerung des Lexical Scanners und Parsers
-----------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dds32.h"
#include "dds.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "hash.hpp"
#include "btrieve.hpp"
#define COMPILE_MAIN
#include "compile.hpp"
#include "syntax.hpp"
#include "waitwin.hpp"
#include "scripthd.hpp"
#define MODULENUM 139
#include "winass.hpp"

#define KWDIMENSION    111
#define PPDIMENSION    37
#define FCDIMENSION    111
#define VRDIMENSION    383
#define PCDIMENSION    37
#define LUDIMENSION    383
#define LFDIMENSION    111
#define ENDIMENSION    111
#define MODDIMENSION  1511

HINSTANCE MyInstance;

/*-< Abfragen des Error - Flags, und, wenn gesetzt, anzeigen des Fehlers >-*/
#define ERRORMSG 8010
static HWND hActParent = 0;

static hash FAR* moduleHash = NULL; // Hashtabelle fuer gerade compilierte Module

static BOOL bRestoolCalledScriptFromCommandLine = FALSE;

//--------------------------  ShowMsg  --------------------------------------
//
// Abhaengig vom <CommandLineFlag> wird der Fehler in einer Message-Box
// ausgegeben oder in ein Datei geschrieben.
//---------------------------------------------------------------------------
WORD ShowMsg (WORD Index,WORD wType,LPSTR str)
  {
  char InZeile0 [100];
  char InZeile1 [100];
  char outline [300];
  LoadString (MyInstance,Index  ,InZeile0,sizeof (InZeile0));
  LoadString (MyInstance,Index+1,InZeile1,sizeof (InZeile1));
  wsprintf (LPSTR(outline),LPSTR(InZeile1),str);
  if (!bRestoolCalledScriptFromCommandLine) {
    return MessageBox (hActParent,outline,InZeile0,wType | MB_TASKMODAL);
    }
  else {
    LogMsg (outline);
    return (TRUE);
    }
  }

#define CMPL_ABORTED    0xFFFF
static char LastErrorFile[128];
static WORD LastErrorNr;
static int  LastErrorLine,LastErrorColumn;
DLLExport BOOL _export compiler::TestError (void)
  {
  if (wError != ERRORINIMPORTED) // Bei Fehlern in importierten Scripts lassen wir diese stehen
    LastErrorNr = wError;
  if (wError) {
    if (wError != CMPL_ABORTED) {
      char outstr[300];
      char pattern[50];
      char errstr[50];
      char filestr[128];
      LoadString (MyInstance,ERRORMSG,pattern,sizeof (pattern));
      LoadString (MyInstance,ERRORMSG+wError,errstr,sizeof (errstr));

      if (wError != ERRORINIMPORTED) // Bei Fehlern in importierten Scripts lassen wir diese stehen
        // die Fehlermeldung an das Elternfenster weiterreichen
        SendMessage (hActParent, WMU_SETERRORTEXT, 0, LPARAM(LPSTR(errstr)));

      if (in_include)
        wsprintf (filestr, "%s in %s in Zeile %d", LPSTR (finame), LPSTR (fmname), LPSTR (LineNr));
      else
        strcpy (filestr, fmname);
      wsprintf (outstr,LPSTR(pattern),LPSTR (filestr),
                               LPSTR (errstr),
                                  (in_include) ? IncLineNr : LineNr,
                                  column) ;
      ShowMsg (MAX_ERROR,MB_OK | MB_ICONEXCLAMATION,outstr);
      if (wError != ERRORINIMPORTED) { // Bei Fehlern in importierten Scripts lassen wir diese stehen
        lstrcpy (LastErrorFile,LPSTR ((in_include) ? finame : fmname));
        LastErrorLine   = (in_include) ? IncLineNr : LineNr;
        LastErrorColumn = column ;
        }
      }
    return TRUE ;
    }
  else return FALSE ;
  }

DLLExport BOOL _export BlobScriptCompiler::TestError ()
  {
  if (of)
    return compiler::TestError ();
  else
    return (wError > 0);
  }

DLLExport WORD _export WINAPI IsCompileAborted ()
  {
  return (LastErrorNr == CMPL_ABORTED);
  }

DLLExport LPSTR _export WINAPI GetErrorInfo (int FAR *LineNr,int FAR *ColumnNr)
  {
  *LineNr   = LastErrorLine;
  *ColumnNr = LastErrorColumn;
  return LastErrorFile;
  }

static double oldfact;
void compiler::ShowWait (void)
  {
  if (WCaption != NULL) {
    if (ww == NULL) 
      ww = new WaitWin (WCaption,"",hActParent,TRUE);
    double fact = double (dwChar) / double (dwfsize);
    ww->SetVal (fact);
    if (ww->IsAborted ())
      wError = CMPL_ABORTED ;
    }
  }

void compiler::ShowInclude (void)
  {
  if (WCaption != NULL) {
    if (ww == NULL) 
      ww = new WaitWin (WCaption,"",hActParent,TRUE);
    ww->SetExtra ((in_include) ? finame : "");
    }
  }

/*---------------------------------------------------------------------
** Initialisierung
**-------------------------------------------------------------------*/

void SetDefines (compiler FAR *c)
  {
  static char doDefine[32];
  static BOOL defReadDone;
  if (!defReadDone) {
    GetPrivateProfileString ("Script","Define","",doDefine,sizeof(doDefine),MYINI);
    defReadDone = TRUE ;
    }
  if ((*doDefine) && (c->hPpHash != NULL)) {
    parse_var temp ;
    temp.type = T_INTEGER ;
    temp.v.ld = 1 ;
    c->hPpHash->SetData (doDefine,&temp,sizeof (temp));
    }
  }

void InitializeDebugInfo ();
void compiler::Init (LPSTR wtxt)
  {
  oldfact = -1.0;
  WCaption = wtxt;
  LineNr = 1 ;                  // Ab Zeilennummer 1 wird angefangen
  vardim = 0;
  // Erzeugen der Hashtabellen
  hKwHash = new hash (KWDIMENSION,STRKEY);
  hPpHash = new hash (PPDIMENSION,STRKEY);

  SetDefines (this);
  }

DLLExport _export WINAPI compiler::compiler (LPSTR wtxt)
  {
  Init (wtxt);
  PrepCodeGen() ;
  }

extern ScriptContent_Entry scent;
extern void ResetAlias ();
extern void ResetVersionList ();
extern char huge * structStart;
short patchNextType;

ScriptCompiler::ScriptCompiler (LPSTR wtxt) : compiler (wtxt)
  {
  _actcmpl = this;
  patchNextType = -1;
  hFcHash = new hash (FCDIMENSION,STRKEY);
  hVrHash = new hash (VRDIMENSION,STRKEY);
  hPcHash = new hash (PCDIMENSION,STRKEY);
  hLuHash = new IdentHash (LUDIMENSION,WORDKEY);
  hlFHash = new hash (LFDIMENSION,STRKEY);
  henHash = new hash (ENDIMENSION,STRKEY);
  hopHash = new hash (FCDIMENSION,STRKEY);
  hefHash = new hash (FCDIMENSION,STRKEY);
  hcmpHash = new hash (FCDIMENSION,STRKEY);
  hSFcHash = new hash (37,STRKEY);
  hlPHash = NULL;
  BitArr *b = new BitArr ();
  hBitArr = b->hmem ;
  LocalUnlock (b->hmem);
  InitializeDebugInfo ();
  ResetAlias ();
  ResetVersionList ();

  InitializeExpProc ();
  fdi = fd = -1;
  AnzDBNmbr = 0;
  Category = 0;
  *IconName = '\0';
  lmemset (&scent,'\0',sizeof(scent));

  dontVarCheck = FALSE ;
  allowBreak = FALSE ;
  bstack = 0 ;
  structStart = NULL ;
  }

DLLExport void _export WINAPI ScriptCompiler::TestExternError ()
  {
  if ((edp != NULL) && (wError == 0)) {
    if (!EditFound) wError = NOEDITSECTION;
    }
  }

DLLExport void _export WINAPI ScriptCompiler::SetExternError ()
  {
  if (edp != NULL) {
    edp->wError = wError;     // Dem auch die Errors mitteilen
    }
  }

DLLExport void _export WINAPI compiler::DoParse (LPVOID fname,syntax_node FAR *prg,LPVOID lpkey)
  {
  // Installieren des Filebuffers
  wError = 0 ;          // wird schon noch kommen (oder vielleicht doch nicht?)
  dont_read = FALSE ;
  InstallBuffer (fname);
  loop_count = -1 ;
  PrgEnd = FALSE ;
  if (!TestError ()) {

    // Laden der Keywords - Hashtabelle
    LoadKwHash ();
    LoadAddHash ();

    // Und los gehts
    SetupLists ();
    NextTerm ();
    BOOL res = FALSE ;
    if (!TestError ()) {
      // und los gehts
      res = parse (prg);

      // Mal sehen, obs hinhaut
      if ((res) && (!PrgEnd)) {
        dont_read = FALSE ;
        NextTerm();  // PrgEnd muss initialisiert werden
        }
      if ((!res) || (res && !PrgEnd)) {
        // Wenns kein Semantik - Fehler ist, dann ists ein Syntax Error
        if (wError == 0) wError = SYNTAX_ERROR ;
        }

      TestExternError ();

      // Noch ein paar abschliessende Checks
      if (!TestError ()) {
        // Ok, ab aufs File damit
        WriteRes (lpkey,fname) ;
        TestError ();
        }
      }
    }
  SetExternError ();
  }

DLLExport void _export WINAPI compiler::PrepareParse ()
  {
  // Laden der Keywords - Hashtabelle
  LoadKwHash ();
  LoadAddHash ();
  }

DLLExport void _export WINAPI compiler::ParseNow (LPVOID fname,syntax_node FAR *prg,LPVOID lpkey)
  {
  // Installieren des Filebuffers
  wError = 0 ;          // wird schon noch kommen (oder vielleicht doch nicht?)
  dont_read = FALSE ;
  InstallBuffer (fname);
  loop_count = -1 ;
  PrgEnd = FALSE ;
  if (!TestError ()) {
    // Und los gehts
    SetupLists ();
    NextTerm ();
    BOOL res = FALSE ;
    if (!TestError ()) {
      // und los gehts
      res = parse (prg);

      // Mal sehen, obs hinhaut
      if ((res) && (!PrgEnd)) {
        dont_read = FALSE ;
        NextTerm();  // PrgEnd muss initialisiert werden
        }
      if ((!res) || (res && !PrgEnd)) {
        // Wenns kein Semantik - Fehler ist, dann ists ein Syntax Error
        if (wError == 0) wError = SYNTAX_ERROR ;
        }

      TestExternError ();

      // Noch ein paar abschliessende Checks
      if (!TestError ()) {
        // Ok, ab aufs File damit
        WriteRes (lpkey,fname) ;
        TestError ();
        }
      }
    }
  SetExternError ();
  }

/*-----< Destruktor : Ganzen Arbeitsspeicher wieder freigeben >----*/
extern void clearAllPtrs ();
extern void DelOpHash(hash *res);
extern void DelOpList(LPOPLIST res);
DLLExport _export WINAPI compiler::~compiler ()
  {
  // Freigabe der Globalen Handles
  if (hText)  GlobalFree (hText);
  if (hPars0) GlobalFree (hPars0);
  if (hPars1) GlobalFree (hPars1);
  if (hPars2) GlobalFree (hPars2);

  for (int i = 0 ; i < ActIncFile ; i++) {
    GlobalFree (hGIncFiles[i]);
    }

  hash FAR *h;
  h = FixKwHash ();     if (h != NULL) delete (h);
  h = FixPpHash ();     if (h != NULL) delete (h);
  h = FixFcHash ();     if (h != NULL) delete (h);
  h = FixVrHash ();     if (h != NULL) delete (h);
  h = FixPcHash ();     if (h != NULL) delete (h);
  h = FixLUHash ();     if (h != NULL) delete (h);
  h = FixlFHash ();     if (h != NULL) delete (h);
  h = FixenHash ();     if (h != NULL) delete (h);
  if (hAddHash != NULL) delete hAddHash ;
  if (hopHash != NULL)  { DelOpHash(hopHash); delete hopHash; }
  if (hefHash != NULL)  { DelOpHash(hefHash); delete hefHash; }
  if (hasList != NULL)  { DelOpList (hasList); }
  if (hcndList != NULL) { DelOpList (hcndList); }
  if (hcmpHash != NULL) { DelOpHash(hcmpHash);  delete hcmpHash; }
  if (hlPHash != NULL) { h = FixlPHash ();     delete (h); }
  if (hBitArr) {
    BitArr *b = FixBitArr ();     if (b != NULL) delete (b);
    }
  // Freigabe der Code - Buffer
  for (int i = 0; i < MAX_DEPTH; i++) {
      if (codebuffer[i]) GlobalFree(codebuffer[i]);
  }
  if (constbuffer) GlobalFree (constbuffer);

  if (ww != NULL)
    delete ww;
  ww = NULL;
  }

ScriptCompiler::~ScriptCompiler ()
  {
  // Freigabe der Globalen Handles
  if ((hText) && (edp == NULL))
    GlobalFree (hText) , hText = NULL;     // Vielleicht brauchts der Formulareditor noch
  if (edp != NULL) {
    edp->hGText = hText;
    }
  if (ExportHash != NULL)
    delete ExportHash;
  // Schliessen der noch offenen Files
  if (fdi != -1)  _lclose (fdi);
  if (fd  != -1)  _lclose (fd);
  if (actFPrefix)
    FreeGlobMem (actFPrefix);

  DestroyConstList ();
  DestroyFncLookup ();

  if (ww != NULL)
    delete ww;
  ww = NULL;
  if (PropertyString != NULL) FreeGlobMem (PropertyString);
  FreeDebugInfo ();

  // Loeschen aller Hashtabellen und sonstiger Zeiger
  clearAllPtrs ();
  if (hSFcHash != NULL) delete hSFcHash ;
  if (localVars != NULL) delete localVars ;
  if (MyImportModules != NULL) FreeGlobMem (MyImportModules);
  if (MyBaseModules != NULL) FreeGlobMem (MyBaseModules);
  if (MyVirtualModules != NULL) FreeGlobMem (MyVirtualModules);
  if (declareFuncs != NULL) delete declareFuncs ;
  for ( ; lhlist != NULL ; ) {
    LocalHashList FAR *hl = lhlist->Next ;
    if (lhlist->h != NULL) delete lhlist->h ;
    FreeGlobMem (lhlist);
    lhlist = hl ;
    }
  for ( ; ps != NULL ; ) {
    PrivateStruct FAR *n = ps->Next ;
    FreeGlobMem (ps->Name);
    FreeGlobMem (ps);
    ps = n ;
    }
  if (actStructData != NULL) FreeGlobMem (actStructData);
  _actcmpl = NULL;
  if (scent.TRef != NULL) {
    FreeGlobMem (scent.TRef);
    scent.TRef = NULL;
    }
  }

BlobScriptCompiler::~BlobScriptCompiler ()
  {
  }

/*----< Aufbau der Keyword - Hashtabelle >---------*/
DLLExport void _export WINAPI AnalyseAlias (hash *h,LPSTR in,LPSTR name,WORD i,WORD FAR *j)
  {
  *j = i ;
  LPSTR q = name ;
  LPSTR s = in ;
  for ( ; ; ) {
    if ((*s == '\0') || (*s == ' ')) {
      *q = '\0' ;
      break ;
      }
    *q++ = *s++ ;
    }
  if (*s) {
    for ( ; *s == ' ' ; s++) ;
    if ((s[0] == 'a') &&
        (s[1] == 'l') &&
        (s[2] == 'i') &&
        (s[3] == 'a') &&
        (s[4] == 's')) {
      s += 5 ;
      for ( ; *s == ' ' ; s++) ;
      WORD FAR *n = (WORD FAR *) h->GetData (s);
      WIN_ASSERT (n != NULL) ;
      *j = *n ;
      }
    else
      WIN_ASSERT(FALSE);
    }
  }
DLLExport void _export WINAPI ScriptCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[150];
    LoadString (MyInstance,KWNAME+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    char name[150];
    WORD j;
    AnalyseAlias (h,instring,name,i,&j);
    h->SetData (name,&j,sizeof (WORD));
    }
  ReleaseKwHash ();
  }
/*
DLLExport void _export WINAPI ScriptCompiler::LoadKwHash ()
  {
  }
*/

HWND GetActParent ()
  {
  return hActParent ;
  }

DLLExport int _export WINAPI DoCompile (HWND hWndParent,LPSTR fname)
  {
  hActParent = hWndParent;
  ScriptCompiler *c = new ScriptCompiler(fname);
  c->ImportDone = TRUE ;
  c->DoParse (fname,&prog,fname);
  int res = c->wError;
  delete c;
  return res;
  }

DLLExport GLOBALHANDLE _export WINAPI DoCompileFromBlob (GLOBALHANDLE hGSource,DWORD SourceSize,LPSTR FName,DWORD FAR *rSize,BOOL mitOberflaeche)
  {
  hActParent = GetActiveWindow ();
  BlobScriptCompiler *c;
  if (mitOberflaeche)
    c = new BlobScriptCompiler(FName,hGSource,mitOberflaeche);
  else
    c = new BlobScriptCompiler(NULL,hGSource,mitOberflaeche);
  c->ImportDone = TRUE ;
  c->DoParse (FName,&prog,FName);
  *rSize = c->SizeOfRes;
  GLOBALHANDLE hGRes = c->hGRes;
  delete c;
  return hGRes;
  }

DLLExport void _export WINAPI DoneModuleHash ()
  {
  if (moduleHash != NULL) {
    delete moduleHash;
    moduleHash = NULL;
    }
  }

DLLExport void _export WINAPI InitModuleHash ()
  {
  WIN_ASSERT (moduleHash == NULL);
  if (moduleHash)
    DoneModuleHash ();
  moduleHash = new hash (MODDIMENSION,STRKEY);
  }

DLLExport int _export WINAPI DoCompileMod (HWND hWndParent,LPSTR fname)
  {
  WIN_ASSERT (moduleHash != NULL);
  hActParent = hWndParent;
  int FAR *oldRes;
  int res = -1; // Modul wird gerade kompiliert
  char hashName[_MAX_FNAME];

  _splitpath (fname, NULL, NULL, hashName, NULL);

  if (moduleHash->SetData (hashName,&res,sizeof (res))) {
    ScriptCompiler *c = new ScriptCompiler(fname);
    c->DoParse (fname,&mod,fname);
    res = c->wError;
    delete c;
    // gleich nach dem SetData muss dass GetData funktionieren
    oldRes = (int FAR *) (moduleHash->GetData (hashName));
    *oldRes = res;
    return res;
    }
  else {
    // Wenn SetData danebengeht, muss GetData funktionieren
    oldRes = (int FAR *) (moduleHash->GetData (hashName));
    if (*oldRes == -1) {
      ScriptCompiler *c = new ScriptCompiler(fname);
      lstrcpy (c->fmname, fname);
      c->wError = CYCLICIMPORT;
      c->TestError ();
      delete c;
      *oldRes = CYCLICIMPORT;
      }
    return *oldRes;
    }
  }

//-----------------------  SetCommandLineFlag  ------------------------------
//
// setzt das Flag, welches die Steuerung der Compile-Fehler uebernimmt.
//     TRUE .... Compile-Fehler werden in ein Datei geschrieben
//     FALSE ... Compile-Fehler werden in einer Msg-Box ausgegeben
//---------------------------------------------------------------------------
DLLExport void _export WINAPI SetCommandLineFlag (BOOL flag)
  {
  bRestoolCalledScriptFromCommandLine = flag;
  }

DLLExport BOOL _export WINAPI GetCommandLineFlag ()
  {
  return bRestoolCalledScriptFromCommandLine;
  }

///////////////////////////////////////////////////////////////////////
//      Initialisieren der DLL
///////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
  {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      MyInstance = hModule;
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
int WINAPI WEP (int nShutdownFlag)
  {
  return 1 ;
  }

extern "C" {
int WINAPI LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  MyInstance = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1 ;
  }
}

#endif

