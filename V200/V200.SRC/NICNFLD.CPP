///////////////////////////////////////////////////////////////////
//  Verwaltung der Folders (Neuanlage eines Dokumentes)
///////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/nicnfld.cpv   1.9   26 Nov 1996 08:14:38   HANNES  $
// $Log:   P:/marille/clinicum/rev/nicnfld.cpv  $
// 
//    Rev 1.9   26 Nov 1996 08:14:38   HANNES
// Automatischer Update
// 
//    Rev 1.8   21 Oct 1996 18:49:10   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.7   02 Feb 1996 10:36:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   24 Aug 1995 00:19:52   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.5   10 Aug 1995 09:26:16   HANNES
// Sicherheitsabfragen...
// 
//    Rev 1.4   09 Jun 1995 00:20:36   HANNES
// CSYSRECS
// Angabe des Dokumentnames extra
// 
//    Rev 1.3   31 Mar 1995 18:23:30   HANNES
//  
// 
//    Rev 1.2   20 Mar 1995 12:05:28   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.1   20 Nov 1994 18:29:04   HANNES
// NotifyActiveEle
// 
//    Rev 1.0   20 Sep 1994 11:42:28   GERHOLD
// Initial revision.
// 
//    Rev 1.0   05 Aug 1994 17:13:24   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define MODULENUM 13
#include "winass.hpp"

#include "icontool.hpp"
#define NODLL
#include "toolbar.hpp"

#include "cfield.hpp"
#include "dllchild.hpp"
#include "frmobj.hpp"

DLLExport void _export WINAPI IcnNotify (LPICONELEDATA ele,WORD code)
  {
  if (code == ICN_DOEXCUTE) {
    LPDBRECORD old = ele->c->rr->GetRecord(ele->TableInd);
    ele->c->rr->SetRecord (ele->TableInd,LPDBRECORD (ele->Record));
    ele->c->ExCuteProc (ele->cbProc,EM_LOAD | EM_CHANGETOTRUE);
    ele->c->ExCuteProc (ele->cbProc,EM_RESET);
    ele->c->rr->SetRecord (ele->TableInd,old);
    }
  }

ICNNOTIFY GetNotify()
  {
  static ICNNOTIFY lpntf;
  if (lpntf == NULL)
    lpntf = ICNNOTIFY (MakeProcInstance (FARPROC(IcnNotify),WBase::hInstance));
  return lpntf;
  }

struct AddIconEle_param {
  WORD parSize;
  DWORD itool;
  DWORD prgName;
  DWORD docName;
  };

WORD GetTableID (LPSTR Name,mdiChild FAR *c)
  {
  WORD tid,Version;
  int tind = GetTableNr (c->schd,&tid,&Version,Name);
  if (tind > 0) return tind ;
  else          return 0xFFFF ;
  }

BOOL AddIconEleEx (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddIconEle_param FAR *par = (AddIconEle_param FAR *) param;
    LPSTR prgName = LPSTR (c->ReadlData (par->prgName));
    DBWIN_ASSERT (prgName != NULL);
    LPSCRIPTCONTENT ele = GetScriptEntry (prgName);
    if (ele != NULL) {
      LPSTR docName = NULL ;
      if (par->parSize >= sizeof(*par)) {
        docName = LPSTR(c->ReadlData (par->docName));
        }
      if (docName == NULL)
        docName = ele->Name;
      IconEleData d;
      LPICONTOOL FAR *lpIconTool = (LPICONTOOL FAR *) c->ReadlData (par->itool);
      DBWIN_ASSERT ((lpIconTool != NULL) && (*lpIconTool != NULL));
      LPICONTOOL IconTool = *lpIconTool ;
      LPSTR TableName = LPSTR (c->ReadlData (
              IconTool->IconPar()->TableName));
      WORD TableInd = GetTableID (TableName,c);
      DBWIN_ASSERT (TableInd != 0xFFFF);
      d.sc = ele;
      LPDBRECORD r = c->rr->GetRecord (TableInd);
      DBWIN_ASSERT (r != NULL);
      d.Record = r;
      d.TableInd = TableInd;
      d.cbProc = IconTool->IconPar()->cbProc ;
      d.cbFunc = GetNotify();
      d.c = c ;

      if (ele->IconData != NULL) {
        // Ein Icon steht zur Verfuegung
        LPBITMAPINFO lpbmi = LPBITMAPINFO (ele->IconData);
        IconTool->AddPmEle (docName,lpbmi,&d);
        }
      else {
        IconTool->AddPmEle (docName,LoadDefIcon(),&d);
        }
      }
    }
  return FALSE ;
  }

struct DoIconEleSelect_param {
  WORD parSize;
  DWORD itool;
  };
BOOL DoIconEleSelect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DoIconEleSelect_param FAR *par = (DoIconEleSelect_param FAR *) param;
    LPICONTOOL FAR *lpIconTool = (LPICONTOOL FAR *) c->ReadlData (par->itool);
    DBWIN_ASSERT ((lpIconTool != NULL) && (*lpIconTool != NULL));
    (*lpIconTool)->NotifyActiveEle ();
    }
  return FALSE ;
  }


