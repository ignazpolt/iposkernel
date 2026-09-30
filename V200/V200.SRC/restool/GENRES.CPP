////////////////////////////////////////////////////////////////
//  Generieren des Resourcen
////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/restool/rev/genres.cpv   1.9   01 May 2000 13:32:08   Hannes  $
//  $Log:   F:/marille/clinicum/restool/rev/genres.cpv  $
// 
//    Rev 1.9   01 May 2000 13:32:08   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.8   05 Oct 1998 11:26:44   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   28 Aug 1997 15:52:06   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   04 Feb 1996 21:49:16   HANNES
// 
//    Rev 1.5   04 Feb 1996 17:00:38   HANNES
// Protyp LogMsg
// 
//    Rev 1.4   02 Feb 1996 10:50:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   02 Apr 1995 13:33:24   HANNES
//  
// 
//    Rev 1.2   31 Mar 1995 18:23:32   HANNES
//  
// 
//    Rev 1.1   02 Jan 1995 09:30:24   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   24 Jun 1994 16:54:48   HANNES
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
#define MODULENUM 24
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "resadmin.hpp"

extern HINSTANCE MyInstance;
extern HWND hRsWnd;
class RCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);

  RCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI RCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,RCKW_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

DLLExport BOOL _export WINAPI RCompiler::TestError ()
  {
  if (wError > RCCMPERROR_BASE) {
    char pattern[64];
    char errstr[64];
    LoadString (MyInstance,RCCMPERROR_BASE,pattern,sizeof(pattern));
    LoadString (MyInstance,wError,errstr,sizeof(errstr));
    char outtxt[256];
    wsprintf (outtxt,pattern,fmname,LineNr,column,LPSTR(errstr));
    if (GetCommandLineFlag())
      LogMsg (outtxt);
    else
      MessageBox (hRsWnd,outtxt,"Resourcefehler",MB_OK | MB_TASKMODAL);
    return TRUE ;
    }
  else
    return compiler::TestError ();
  }

static RCompiler FAR *RCmp;
////////////////////////////////////////////////////////////////////////
//  Codegenerierung
////////////////////////////////////////////////////////////////////////
static char ResName[64];
static char ResFName[128];
DLLExport void _export _SetResName ()
  {
  LPSTR Name = LPSTR(GlobalLock (RCmp->hPars0)) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(ResName) - 1);
  lstrcpy (ResName,Name);
  GlobalUnlock (RCmp->hPars0);
  }

DLLExport void _export _SetResFName ()
  {
  LPSTR Name = LPSTR(GlobalLock (RCmp->hPars0)) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(ResFName) - 1);
  lstrcpy (ResFName,Name);
  GlobalUnlock (RCmp->hPars0);
  }

DLLExport void _export _StoreWMF ()
  {
  _SetResFName ();
  char pattern[64],outtxt[128];
  LoadString (MyInstance,ID_RSWMFPATTERN,pattern,sizeof(pattern));
  wsprintf (outtxt,pattern,LPSTR(ResName),LPSTR(ResFName));
  ShowMsg (outtxt);
  UpdateWindow (hRsWnd);
  if (!StoreWMF (ResName,ResFName))
    RCmp->wError = RCCMPERROR_FNOTFOUND;
  }

static int bdx,bdy;
DLLExport void _export _SetBDX ()
  {
  bdx = int(RCmp->scv.v.int_val);
  }

DLLExport void _export _StoreBMP ()
  {
  bdy = int(RCmp->scv.v.int_val);
  char pattern[64],outtxt[128];
  LoadString (MyInstance,ID_RSBMPPATTERN,pattern,sizeof(pattern));
  wsprintf (outtxt,pattern,LPSTR(ResName),LPSTR(ResFName));
  ShowMsg (outtxt);
  UpdateWindow (hRsWnd);
  if (!StoreBitmap (ResName,ResFName,bdx,bdy,RESTYPE_BITMAP))
    RCmp->wError = RCCMPERROR_FNOTFOUND;
  }
DLLExport void _export _StoreBMP1 ()
  {
  LPSTR Name = LPSTR(GlobalLock (RCmp->hPars0)) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(ResFName) - 1);
  lstrcpy (ResFName,Name);
  GlobalUnlock (RCmp->hPars0);

  char pattern[64],outtxt[128];
  LoadString (MyInstance,ID_RSBMPPATTERN,pattern,sizeof(pattern));
  wsprintf (outtxt,pattern,LPSTR(ResName),LPSTR(ResFName));
  ShowMsg (outtxt);
  UpdateWindow (hRsWnd);
  if (!StoreBitmap (ResName,ResFName,bdx,bdy,RESTYPE_BITMAP8_6))
    RCmp->wError = RCCMPERROR_FNOTFOUND;
  }
/////////////////////////////////////////////////////////////////////////
//  Syntax des Resourcecompilers
/////////////////////////////////////////////////////////////////////////
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

syntax_node wmf3     = { NULL  , NULL , TRUE , INITERM(STRING,0) , _StoreWMF } ;
syntax_node wmf2     = { &wmf3 , NULL , TRUE , INITERM(KEYWORD,RCKW_EQUAL) , NULL } ;
syntax_node wmf1     = { &wmf2 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetResName } ;
syntax_node wmf      = { &wmf1 , NULL , TRUE , INITERM(KEYWORD,RCKW_WMF) , NULL } ;

syntax_node bme      = { NULL     , NULL , TRUE , INITERM(FREECHAR,0) , NULL} ;
syntax_node bitmap9  = { NULL     , NULL , TRUE , INITERM(STRING,0) , _StoreBMP1 } ;
syntax_node bitmap8  = { &bitmap9 , &bme , TRUE , INITERM(KEYWORD,RCKW_8x6) , NULL } ;
syntax_node bitmap7  = { &bitmap8 , NULL , TRUE , INITERM(T_INTEGER,0) , _StoreBMP } ;
syntax_node bitmap6  = { &bitmap7 , NULL , TRUE , INITERM(KEYWORD,RCKW_COLON) , NULL } ;
syntax_node bitmap5  = { &bitmap6 , NULL , TRUE , INITERM(T_INTEGER,0) , _SetBDX } ;
syntax_node bitmap4  = { &bitmap5 , NULL , TRUE , INITERM(KEYWORD,RCKW_DIMENSION) , NULL } ;
syntax_node bitmap3  = { &bitmap4 , NULL , TRUE , INITERM(STRING,0) , _SetResFName } ;
syntax_node bitmap2  = { &bitmap3 , NULL , TRUE , INITERM(KEYWORD,RCKW_EQUAL) , NULL } ;
syntax_node bitmap1  = { &bitmap2 , NULL , TRUE , INITERM(UNKNOWNIDENT,0) , _SetResName } ;
syntax_node bitmap   = { &bitmap1 , NULL , TRUE , INITERM(KEYWORD,RCKW_BITMAP) , NULL } ;

extern syntax_node rsyntax;
syntax_node rsyntax3 = { NULL      , &rsyntax  , TRUE  , INITERM(KEYWORD,RCKW_XXXX) , NULL } ;
syntax_node rsyntax2 = { &rsyntax3 , NULL      , TRUE  , INITERM(KEYWORD,RCKW_SEMICOLON) , NULL } ;
syntax_node rsyntax1 = { &rsyntax2 , NULL      , FALSE , &wmf    , NULL } ;
syntax_node rsyntax  = { &rsyntax2 , &rsyntax1 , FALSE , &bitmap , NULL } ;

BOOL GenRScript (HWND hWnd,LPSTR fname)
  {
  RCompiler FAR *r = new RCompiler ();
  RCmp = r;
  hRsWnd = hWnd;
  char pattern[64];
  char outtxt[128];
  LoadString (MyInstance,ID_RCCMPHEADLINE,pattern,sizeof(pattern));
  wsprintf (outtxt,pattern,fname);
  ShowMsg (outtxt,TRUE);
  UpdateWindow (hRsWnd);
  r->DoParse (fname,&rsyntax,NULL);
  CreateResContent ();
  LoadString (MyInstance,ID_RCCMPENDLINE,outtxt,sizeof(outtxt));
  ShowMsg (outtxt,TRUE);
  UpdateWindow (hRsWnd);
  return (r->wError == 0) ;
  }

