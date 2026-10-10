//////////////////////////////////////////////////////////////////////////
//  Bearbeiten des Scriptheaders
//////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/compile/rev/wonschd.cpv   1.4   02 Feb 1996 10:41:34   GERHOLD  $
//  $Log:   P:/marille/clinicum/compile/rev/wonschd.cpv  $
// 
//    Rev 1.4   02 Feb 1996 10:41:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   31 Oct 1994 10:03:26   hannes
// Optionsscriptangabe
// 
//    Rev 1.2   03 Sep 1994 14:53:56   HANNES
// Formulartyp in den Header
// 
//    Rev 1.1   24 Aug 1994 19:40:06   HANNES
// Erweiterungen im Header
// 
//    Rev 1.0   24 Jun 1994 16:30:28   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#define JUST_EM
#include "dds.hpp"
#include "compile.hpp"
#include "express.hpp"
#include "syntax.hpp"
#include "twodim.hpp"
#include "dds.h"
#define MODULENUM 108
#include "winass.hpp"

#include "scripthd.hpp"

extern ScriptContent_Entry scent;

void SetDarfInFachsein ()
  {
  scent.DarfInFachsein = TRUE ;
  }

void SetDarfImVerzeichnisVorkommen ()
  {
  scent.DarfImVerzeichnisVorkommen = TRUE ;
  }

void SetIstVerweisErzeuger ()
  {
  scent.IstVerweisErzeuger = TRUE ;
  }

void SetIstVerweisSpeicherer ()
  {
  scent.IstVerweisSpeicherer = TRUE ;
  }

#define EXT   ".TXT"
void SetBearbeiteSelektor ()
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(scent.BearbeiteSelektor) - 4);
  lstrcpy (scent.BearbeiteSelektor,Name);
  lstrcat (scent.BearbeiteSelektor,EXT);
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetDefaultVerweisErzeuger ()
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(scent.DefaultVerweisErzeuger) - 4);
  lstrcpy (scent.DefaultVerweisErzeuger,Name);
  lstrcat (scent.DefaultVerweisErzeuger,EXT);
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetDefaultVerweisSpeicherer ()
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(scent.DefaultVerweisSpeicherer) - 4);
  lstrcpy (scent.DefaultVerweisSpeicherer,Name);
  lstrcat (scent.DefaultVerweisSpeicherer,EXT);
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetOptionScript ()
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  WIN_ASSERT (lstrlen(Name) < sizeof(scent.DefaultVerweisSpeicherer) - 4);
  lstrcpy (scent.OptionScript,Name);
  lstrcat (scent.OptionScript,EXT);
  GlobalUnlock (_actcmpl->hPars0);
  }

void SetNoMDI ()
  {
  scent.NoMDI = TRUE ;
  }
                                     
void SetDarfInKrankengeschichteVorkommen ()
  {
  scent.DarfInKrankengeschichteVorkommen = TRUE ;
  }

void SetFormType ()
  {
#define ANZTYPES 6
static struct _TypeToType { int td ; int ts ; } TypeToType[] = {
  { FT_INTERN               , TINTERN    } ,
  { FT_MAPPE                , TMAPPE     } ,
  { FT_FACHMITVERWEISE      , TFACHMIT   } ,
  { FT_FACHOHNEVERWEISE     , TFACHOHNE  } ,
  { FT_FORMULARMITVERWEISE  , TFORMMIT   } ,
  { FT_FORMULAROHNEVERWEISE , TFORMOHNE  } 
  } ;
  for (int i = 0 ; i < ANZTYPES ; i++) {
    if (_actcmpl->scv.v.k_ident == TypeToType[i].ts)
      scent.FormType = TypeToType[i].td ;
    }
  }







