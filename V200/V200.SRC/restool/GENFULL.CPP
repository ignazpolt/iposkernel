/////////////////////////////////////////////////////////////
//  Gesteurtes Kompilieren von verschiedenen Dateien
/////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genfull.cpv   1.23   16 Feb 2000 15:03:50   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/genfull.cpv  $
// 
//    Rev 1.23   16 Feb 2000 15:03:50   Wolfgang
// 1.) Mehrere Prototypen-Files ermoeglicht.
// 2.) Prototypen-Files als .PTY
// 
//    Rev 1.22   26 Apr 1999 18:11:18   Wolfgang
// 1.) ERRORINIMPORTED statt SYNTAX_ERROR damit Fehlerfile geoeffnet wird.
// 2.) checkonly zum Laden eines Makefiles in die Modulliste (zwecks Sortieren).
// 
//    Rev 1.21   05 Oct 1998 11:26:14   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.20   14 Aug 1998 18:56:10   Hannes
// Include / Source Pfad wirklich trennen
// 
//    Rev 1.19   28 Aug 1997 15:51:58   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.18   13 Mar 1997 19:03:50   Hannes
// ScriptContent nach jedem Modul erzeugen
// 
//    Rev 1.17   19 Feb 1997 12:12:52   Hannes
// Compilieren von Modulen
// 
//    Rev 1.16   08 Nov 1996 13:30:28   HANNES
// QLong,Replikator
// 
//    Rev 1.15   21 Oct 1996 18:57:34   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.14   17 Jun 1996 16:53:18   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.13   04 Feb 1996 21:49:14   HANNES
// 
//    Rev 1.12   02 Feb 1996 10:50:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   16 Sep 1995 17:50:16   HANNES
// 
//    Rev 1.10   29 Mar 1995 16:32:06   HANNES
// 
//    Rev 1.9   27 Mar 1995 10:39:26   GERHOLD
// 
//    Rev 1.8   20 Mar 1995 08:44:52   HANNES
//  
// 
//    Rev 1.7   03 Mar 1995 11:05:18   HANNES
// 
//    Rev 1.6   24 Feb 1995 11:00:38   HANNES
// No change.
// 
//    Rev 1.5   16 Feb 1995 12:34:06   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.4   10 Jan 1995 15:01:06   HANNES
// 
//    Rev 1.3   02 Jan 1995 09:30:22   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.1   04 Jul 1994 20:25:40   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:54:46   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 91
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "resadmin.hpp"

#include "tbdef.hpp"

#include "scripthd.hpp"

extern void PushSourceForMake (LPSTR FileName);

BOOL checkOnly = FALSE;

BOOL stopOutput = FALSE;
void ToggleOutputState (HMENU hmenu)
  {
  if (stopOutput)
    CheckMenuItem (hmenu,MI_OUTPUTOPT,MF_CHECKED) , stopOutput = FALSE ;
  else
    CheckMenuItem (hmenu,MI_OUTPUTOPT,MF_UNCHECKED) , stopOutput = TRUE ;
  }

HWND hRsWnd;
static int AnzMsgs;
static LPSTR Message[128];
void ShowMsg (LPSTR Text,BOOL priority)
  {
  if ((stopOutput) && (!priority)) return ;

  TEXTMETRIC tm;
  HDC hDC = GetDC (hRsWnd);
  GetTextMetrics (hDC,&tm);
  SetTextAlign (hDC,TA_LEFT | TA_TOP);
  int ystart = 3 + AnzMsgs * tm.tmHeight;
  RECT r;
  GetClientRect (hRsWnd,&r);
  if (ystart + tm.tmHeight < r.bottom) {
    // Text hat noch platz
    Message[AnzMsgs] = LPSTR (GetGlobMem (lstrlen(Text)+1));
    lstrcpy (Message[AnzMsgs],Text);
    AnzMsgs ++ ;
    r.top    = ystart;
    r.bottom = ystart + tm.tmHeight;
    InvalidateRect (hRsWnd,&r,TRUE);
    }
  else {
    // Es muss gescrollt werden
    ScrollWindow (hRsWnd,0,-tm.tmHeight,NULL,NULL);
    FreeGlobMem (Message[0]);
    for (int i = 1 ; i < AnzMsgs ; i++) {
      Message[i-1] = Message[i];
      }
    Message[AnzMsgs-1] = LPSTR (GetGlobMem (lstrlen(Text)+1));
    lstrcpy (Message[AnzMsgs-1],Text);
    int ystart = 3 + (AnzMsgs - 1) * tm.tmHeight;
    r.top    = ystart;
    r.bottom = ystart + tm.tmHeight;
    InvalidateRect (hRsWnd,&r,FALSE);
    }
  ReleaseDC (hRsWnd,hDC);
  }

void PaintMessages (HDC hDC)
  {
  TEXTMETRIC tm;
  GetTextMetrics (hDC,&tm);
  SetTextAlign (hDC,TA_LEFT | TA_TOP);
  int y = 3 ;
  for (int i = 0 ; i < 128 ; i++) {
    if (Message[i] != NULL) {
      TextOut (hDC,20,y,Message[i],lstrlen(Message[i]));
      y += tm.tmHeight;
      }
    else
      break ;
    }
  }

void FreeMsgs ()
  {
  AnzMsgs = 0;
  for (int i = 0 ; i < 128 ; i++) {
    if (Message[i] != NULL) {
      FreeGlobMem (Message[i]);
      Message[i] = NULL;
      }
    }
  }

extern HINSTANCE MyInstance;
class GCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);

  GCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI GCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,GCKW_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }


static GCompiler FAR *GCmp;
static HWND gWnd;
static BOOL doCreateScriptContent,doCreateContent;
extern HWND hRsWnd;
DLLExport void _export _GenScript ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.TXT",Name);
  if (checkOnly)
    PushSourceForMake (fname);
  else {
    GetIncludeFileName (fname,name,_xname,"source");
    if (!GenerateScript (gWnd,name)) {
      if (GetCommandLineFlag()) {
        GCmp->wError = ERRORINIMPORTED;
        GCmp->TestError ();
        GCmp->wError = 0 ;
        }
      else
        GCmp->wError = ERRORINIMPORTED;
      }
    else
      doCreateScriptContent = TRUE;
    }

  GlobalUnlock (GCmp->hPars0);
  }

DLLExport void _export _GenMod ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.MOD",Name);
  if (checkOnly)
    PushSourceForMake (fname);
  else {
    GetIncludeFileName (fname,name,_xname,"source");
    if (DoCompileMod (gWnd,name) != 0) {
      if (GetCommandLineFlag()) {
        GCmp->wError = ERRORINIMPORTED;
        GCmp->TestError ();
        GCmp->wError = 0 ;
        }
      else
        GCmp->wError = ERRORINIMPORTED;
      }
    else {
      CreateScriptContent (name);
      }
    }

  GlobalUnlock (GCmp->hPars0);
  }

DLLExport void _export _GenTable ()
  {
  WIN_ASSERT_TEXT(FALSE,"KEINE Datadictionaries der alten Konvention mehr unterstuetzt");
  }

extern BOOL GenTbScript (HWND hWnd,LPSTR fname);
DLLExport void _export _GenDBTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.DDD",Name);
  if (checkOnly)
    PushSourceForMake (fname);
  else {
    GetIncludeFileName (fname,name,_xname,"source");
    if (!GenTbScript (gWnd,name)) {
      if (GetCommandLineFlag()) {
        GCmp->wError = ERRORINIMPORTED;
        GCmp->TestError ();
        GCmp->wError = 0 ;
        }
      else
        GCmp->wError = ERRORINIMPORTED;
      }
    ShowMsg (name,TRUE);
    UpdateWindow (hRsWnd);
    doCreateContent = TRUE ;
    }
  GlobalUnlock (GCmp->hPars0);
  }
extern BOOL GenIntScript (HWND hWnd,LPSTR fname);
DLLExport void _export _GenINTTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.IDD",Name);
  if (checkOnly)
    PushSourceForMake (fname);
  else {
    GetIncludeFileName (fname,name,_xname,"source");
    if (!GenIntScript (gWnd,name)) {
      if (GetCommandLineFlag()) {
        GCmp->wError = ERRORINIMPORTED;
        GCmp->TestError ();
        GCmp->wError = 0 ;
        }
      else
        GCmp->wError = ERRORINIMPORTED;
      }
    ShowMsg (name,TRUE);
    UpdateWindow (hRsWnd);
    doCreateContent = TRUE ;
    }
  GlobalUnlock (GCmp->hPars0);
  }
extern BOOL GenRepScript (HWND hWnd,LPSTR fname);
extern BOOL GenGScript (HWND hWnd,LPSTR fname);
DLLExport void _export _GenRep ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.REP",Name);
  GetIncludeFileName (fname,name,_xname,"source");
  if (!GenRepScript (gWnd,name)) {
    if (GetCommandLineFlag()) {
      GCmp->wError = ERRORINIMPORTED;
      GCmp->TestError ();
      GCmp->wError = 0 ;
      }
    else
      GCmp->wError = ERRORINIMPORTED;
    }
  ShowMsg (name,TRUE);
  UpdateWindow (hRsWnd);
  GlobalUnlock (GCmp->hPars0);
  doCreateContent = TRUE ;
  }
DLLExport void _export _GenGTable ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.GDD",Name);
  if (checkOnly)
    PushSourceForMake (fname);
  else {
    GetIncludeFileName (fname,name,_xname,"source");
    if (!GenGScript (gWnd,name)) {
      if (GetCommandLineFlag()) {
        GCmp->wError = ERRORINIMPORTED;
        GCmp->TestError ();
        GCmp->wError = 0 ;
        }
      else
        GCmp->wError = ERRORINIMPORTED;
      }
    ShowMsg (name,TRUE);
    UpdateWindow (hRsWnd);
    doCreateContent = TRUE ;
    }
  GlobalUnlock (GCmp->hPars0);
  }
DLLExport void _export _GenRes ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.TXT",Name);
  GetIncludeFileName (fname,name,_xname,"source");
  if (!GenRScript (gWnd,name)) {
    if (GetCommandLineFlag()) {
      GCmp->wError = ERRORINIMPORTED;
      GCmp->TestError ();
      GCmp->wError = 0 ;
      }
    else
      GCmp->wError = ERRORINIMPORTED;
    }
  GlobalUnlock (GCmp->hPars0);
  }

DLLExport void _export _GenFprot ()
  {
  LPSTR Name = LPSTR(GlobalLock (GCmp->hPars0)) + sizeof(WORD);
  char fname[64],name[128],_xname[128];
  wsprintf (fname,"%s.PTY",Name);
  GetIncludeFileName (fname,name,_xname,"source");
  GenFncProt (gWnd,name);
  GlobalUnlock (GCmp->hPars0);
  }

//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
syntax_node grep2    = { NULL   , NULL   , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node grep1    = { &grep1 , &grep2 , TRUE , INITERM(UNKNOWNIDENT,0) , _GenRep } ;
syntax_node grep     = { &grep1 , NULL   , TRUE , INITERM(KEYWORD,GCKW_REP) , NULL } ;

syntax_node gmod2    = { NULL   , NULL   , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node gmod1    = { &gmod1 , &gmod2 , TRUE , INITERM(UNKNOWNIDENT,0) , _GenMod } ;
syntax_node gmod     = { &gmod1 , NULL   , TRUE , INITERM(KEYWORD,GCKW_MODULES) , NULL } ;

syntax_node gte     = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node gt1     = { &gt1  , &gte   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenGTable } ;
syntax_node gtables = { &gt1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_GTABLES) , NULL } ;

syntax_node ite     = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node it1     = { &it1  , &ite   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenINTTable } ;
syntax_node itables = { &it1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_ITABLES) , NULL } ;

syntax_node dte     = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node dt1     = { &dt1  , &dte   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenDBTable } ;
syntax_node dbtables = { &dt1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_DBTABLES) , NULL } ;

syntax_node se      = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node s1      = { &s1  , &se   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenScript } ;
syntax_node scripts = { &s1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_SCRIPTS) , NULL } ;

syntax_node te     = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node t1     = { &t1  , &te   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenTable } ;
syntax_node tables = { &t1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_TABLES) , NULL } ;

syntax_node re    = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node r1    = { &r1  , &re   , TRUE , INITERM(UNKNOWNIDENT,0) , _GenRes } ;
syntax_node res   = { &r1  , NULL  , TRUE , INITERM(KEYWORD,GCKW_RES) , NULL } ;

syntax_node fpe   = { NULL , NULL  , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node fp1   = { &fp1 , &fpe  , TRUE , INITERM(UNKNOWNIDENT,0) , _GenFprot } ;
syntax_node fprot = { &fp1 , NULL  , TRUE , INITERM(KEYWORD,GCKW_FPROT) , NULL } ;

extern syntax_node g0;
syntax_node g10 = { NULL , &g0  , TRUE  , INITERM(KEYWORD,GCKW_END) , NULL } ;
syntax_node g8  = { &g10 , NULL , FALSE , &gmod  , NULL } ;
syntax_node g7  = { &g10 , &g8 , FALSE , &grep  , NULL } ;
syntax_node g6  = { &g10 , &g7 , FALSE , &gtables  , NULL } ;
syntax_node g5  = { &g10 , &g6 , FALSE , &itables  , NULL } ;
syntax_node g4  = { &g10 , &g5 , FALSE , &dbtables  , NULL } ;
syntax_node g3  = { &g10 , &g4 , FALSE , &scripts  , NULL } ;
syntax_node g2  = { &g10 , &g3  , FALSE , &tables   , NULL } ;
syntax_node g1  = { &g10 , &g2  , FALSE , &res      , NULL } ;
syntax_node g0  = { &g10 , &g1  , FALSE , &fprot    , NULL } ;

BOOL GenerateFull (HWND hWnd,LPSTR fname,BOOL setCheckOnly)
  {
  gWnd = hRsWnd = hWnd;
  GCompiler FAR *r = new GCompiler ();
  GCmp = r;
  doCreateScriptContent = FALSE ;
  doCreateContent = FALSE ;
  checkOnly = setCheckOnly;
  r->DoParse (fname,&g0,NULL);
  if (doCreateScriptContent)
    CreateScriptContent(NULL);
  return (r->wError == 0) ;
  }

