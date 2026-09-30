/*
**  Laden der RI aus einem Beschreibungsfile
*/
//
//  $Header:   P:/marille/clinicum/restool/rev/ldriwnd.cpv   1.4   05 Oct 1998 11:27:14   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/ldriwnd.cpv  $
// 
//    Rev 1.4   05 Oct 1998 11:27:14   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   28 Aug 1997 15:52:42   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.2   04 Feb 1996 21:49:28   HANNES
// 
//    Rev 1.1   02 Feb 1996 10:50:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   16 Feb 1995 12:41:12   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "drdrop.hpp"
#include "font.hpp"
#include "printer.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "cfield.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "riwnd.hpp"

extern HINSTANCE MyInstance;
class LdCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);

  LdCompiler () : compiler (NULL) { }
  };

DLLExport void _export WINAPI LdCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  for (int i = 0 ; ; i++) {
    char instring[50];
    LoadString (MyInstance,LDCMPL_BASE+i,instring,sizeof (instring));
    if (lstrcmp (instring,"END") == 0) break ;
    else h->SetData (instring,&i,sizeof (WORD));
    }
  ReleaseKwHash ();
  }

static int x,y,w,h;
static char TableName[64];
static LdCompiler FAR *lCmp;
DLLExport void _export SetX ()
  {
  x = int(lCmp->scv.v.int_val);
  }
DLLExport void _export SetY ()
  {
  y = int(lCmp->scv.v.int_val);
  }
DLLExport void _export SetW ()
  {
  w = int(lCmp->scv.v.int_val);
  }
DLLExport void _export SetH ()
  {
  h = int(lCmp->scv.v.int_val);
  }
DLLExport void _export SetTableName ()
  {
  LPSTR Name = (LPSTR)GlobalLock (lCmp->hPars0) + sizeof(WORD);
  lstrcpy (TableName,Name);
  GlobalUnlock (lCmp->hPars0);
  }
static riShow FAR *_rs;
DLLExport void _export AddTable ()
  {
  _rs->NewTable (TableName,x,y,w,h);
  }

#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

extern syntax_node ld0;

syntax_node lde = { NULL , NULL , TRUE , INITERM (KEYWORD,LDKWEND) , NULL } ;
syntax_node ld9 = { &ld0 , NULL , TRUE , INITERM (KEYWORD,LDKWBRACECLOSE) , AddTable } ;
syntax_node ld8 = { &ld9 , NULL , TRUE , INITERM (T_INTEGER,0) , SetH } ;
syntax_node ld7 = { &ld8 , NULL , TRUE , INITERM (KEYWORD,LDKWCOLON) , NULL } ;
syntax_node ld6 = { &ld7 , NULL , TRUE , INITERM (T_INTEGER,0) , SetW } ;
syntax_node ld5 = { &ld6 , NULL , TRUE , INITERM (KEYWORD,LDKWCOLON) , NULL } ;
syntax_node ld4 = { &ld5 , NULL , TRUE , INITERM (T_INTEGER,0) , SetY } ;
syntax_node ld3 = { &ld4 , NULL , TRUE , INITERM (KEYWORD,LDKWCOLON) , NULL } ;
syntax_node ld2 = { &ld3 , NULL , TRUE , INITERM (T_INTEGER,0) , SetX } ;
syntax_node ld1 = { &ld2 , NULL , TRUE , INITERM (KEYWORD,LDKWBRACEOPEN) , NULL } ;
syntax_node ld0 = { &ld1 , &lde , TRUE , INITERM (UNKNOWNIDENT,0) , SetTableName } ;


void riShow::Load ()
  {
  LdCompiler FAR *r = new LdCompiler ();
  lCmp = r;
  _rs = this;
  OFSTRUCT Of;
  if (OpenFile (FileName,&Of,OF_EXIST) > 0) {
    r->DoParse (FileName,&ld0,NULL);
    delete r;
    CheckRI();
    }
  }
