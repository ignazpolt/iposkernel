////////////////////////////////////////////////////////////////////
//  Locking - Handling im Clinicum
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/lockhand.cpv   1.24   30 Jun 1999 11:37:50   Wolfgang  $
//  $Log:   P:/marille/clinicum/rev/lockhand.cpv  $
// 
//    Rev 1.24   30 Jun 1999 11:37:50   Wolfgang
// 1.) und beim AddTableDef im Unlock auch noch.
// 
//    Rev 1.23   29 Jun 1999 18:28:44   Wolfgang
// 1.) Auch bei AddTableDef Version angeben.
// 
//    Rev 1.22   28 Jul 1998 09:25:34   Hannes
// GetTableID
// 
//    Rev 1.21   10 Jul 1998 15:02:26   Hannes
// BlockIsActive beim CheckActivation
// 
//    Rev 1.20   09 Jul 1998 15:10:08   Hannes
// CheckActivation
// 
//    Rev 1.19   07 Jul 1998 13:53:24   Hannes
// Avoid Input: EM_RESET beruecksichtigen
// 
//    Rev 1.18   28 Apr 1998 18:20:24   Martin
// ParamType auch bei NULL setzen
// 
//    Rev 1.17   28 Apr 1997 14:27:44   Hannes
// 
//    Rev 1.16   11 Apr 1997 11:38:30   Gerhold
// Statuszeile hat jetzt Vorder- und Hintergrundfarbe
// 
//    Rev 1.15   19 Feb 1997 10:20:58   Hannes
// Clearconnection bei SetStatText
// 
//    Rev 1.14   27 Nov 1996 15:53:10   HANNES
// 
//    Rev 1.13   26 Nov 1996 08:14:32   HANNES
// Automatischer Update
// 
//    Rev 1.12   06 Nov 1996 09:49:06   HANNES
// Fehler bei NWName
// 
//    Rev 1.11   29 Oct 1996 09:42:28   MARTIN
// 
//    Rev 1.10   10 Jun 1996 10:08:48   GERHOLD
// pragma packinterpr.cpp
// 
//    Rev 1.9   02 Feb 1996 10:34:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   24 Aug 1995 00:19:58   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.7   31 Jul 1995 11:51:54   GERHOLD
// SetConnection auf StatText
// 
//    Rev 1.6   14 Jul 1995 16:54:14   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.5   04 May 1995 18:38:32   HANNES
// 
//    Rev 1.4   27 Apr 1995 15:37:44   HANNES
// 
//    Rev 1.3   20 Mar 1995 12:04:24   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.2   16 Feb 1995 12:52:14   HANNES
// 
//    Rev 1.1   08 Dec 1994 22:06:14   HANNES
// 
//    Rev 1.0   08 Nov 1994 12:44:08   HANNES
// Initial revision.

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
#define MODULENUM 133
#include "winass.hpp"

#include "winextra.hpp"

#include "hash.hpp"
#include "compile.hpp"

#include "cfield.hpp"
#include "dllchild.hpp"
#include "frmobj.hpp"

#define LOCKTABLENAME "LockTable"
#define UNLOCKACCESS  "Nummer = %1"
DLLExport void _export WINAPI GetNWAddress (LPSTR,int);

BOOL DoLockAccess (LPVOID FAR *Handle,mdiChild *c,WORD TableIDToLock,LPVOID Key)
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,LOCKTABLENAME,&found,&Version);
  DBWIN_ASSERT (found);
  LPTABLEDEF td = GetTableAdmin()->GetTableDef(TableID,Version);
  DBWIN_ASSERT (td != NULL);
  LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,c->DocumentID());
  req->SetTableID (TableID,Version);
  req->AddTableDef (TableID,Version,FALSE);
  req->SetParam (1,&TableID,sizeof(TableID));
  LPDBRECORD rec = new DBRecord (td);
  rec->Set (1,&TableIDToLock,sizeof(TableIDToLock));
  rec->Set (2,Key,GetBlockSize(Key));
  char NWName [64];
  GetNWAddress (NWName,sizeof(NWName));
  NWName[NWName[0]+1] = '\0';
  rec->Set (3,NWName+1,lstrlen(NWName+1)+1);
  RecBuffer rb;
  lmemset (&rb,'\0',sizeof(rb));
  rb.AddLine (1,ADDLINEPOS_END);
  rb.act->rec[0] = rec ;

  LPVOID hstmt = NULL;
  BOOL errwasSet = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBIgnoreError (ERRTYPE_DUPLICATEKEY,TRUE);
  int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall 
              (DBOP_GET,1,req,&hstmt,&rb);

  if ((res == DBCALL_SUCCESS) && (rb.first->rec[0] != NULL)) {
    LPVOID NewAutoIncVal = rb.first->rec[0]->Get(0);
    *Handle = GetGlobMem(GetBlockSize(NewAutoIncVal));
    lmemcpy(*Handle,NewAutoIncVal,GetBlockSize(NewAutoIncVal));
    }
  else {
    res = DBCALL_ERROR;
    }

  delete rec ;
  rb.Clear ();

  // Den ganzen Scheiss wieder abbauen
  req->ClearParams();

  if (hstmt != NULL)
    GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
  if (req != NULL) {
    if (!errwasSet) GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBIgnoreError (ERRTYPE_DUPLICATEKEY,FALSE);
    req->ClearForeign();
    req->FreeTableDefs();
    FreeRequest (req);
    }

  GetTableAdmin()->FreeTable(TableID,Version);

  return (res == DBCALL_SUCCESS);
  }

#pragma pack(1)
struct FAR LockTable_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  DWORD KeySeg[1];

  int AnzKeySegs()
    { return (parSize - (sizeof(*this) - sizeof(KeySeg[0]))) / sizeof(KeySeg[0]) ; }
  BOOL GetPrimKey (LPPRIMKEY k,mdiChild *c);
  WORD TableID (mdiChild *c);
  };
#pragma pack()

BOOL LockTable_param::GetPrimKey (LPPRIMKEY k,mdiChild *c)
  {
  BOOL alldone = TRUE ;
  for (int i = 0 ; i < AnzKeySegs () ; i++) {
    LPVOID Data = c->ReadlData (KeySeg[i]);
    if (Data != NULL)
      k->PushKeySeg (Data,GetBlockSize(Data));
    else
      alldone = FALSE ;
    }
  return alldone ;
  }

WORD LockTable_param::TableID (mdiChild *c)
  {
  LPSTR Name = LPSTR(c->ReadlData (TableName));
  DBWIN_ASSERT (Name != NULL);
  BOOL found;
  WORD Version;
  WORD res = GetTableAdmin()->GetTableID (NULL,Name,&found,&Version);
  DBWIN_ASSERT (found);
  return res;
  }

BOOL LockTable (mdiChild *c,LPVOID param,WORD mode) 
  {
  BOOL lockDone = FALSE ;
  if (mode & EM_LOAD) {
    LockTable_param FAR *par = (LockTable_param FAR *) param;
    PrimKey k;
    DBWIN_ASSERT_TEXT (par->GetPrimKey(&k,c),"Nicht alle Schluesselsegmente definiert");
    LPVOID Handle;
    lockDone = DoLockAccess(&Handle,c,par->TableID(c),k.Data);
    if (lockDone) {
      c->WritelData (par->res,Handle,GetBlockSize(Handle),LPSTR(param)-sizeof(WORD));
      FreeGlobMem(Handle);
      }
    else {
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      if (c->outContext != NULL)
        c->outContext->dontUpdateDocument = TRUE ;
      c->dontUpdateDocument = TRUE ;
      }
    }
  return lockDone;
  }

#pragma pack(1)
struct FAR UnlockTable_param {
  WORD parSize;
  DWORD lptr;
  };
#pragma pack()

BOOL UnlockTable (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    UnlockTable_param FAR *par = (UnlockTable_param FAR *) param;
    BOOL found;
    WORD Version;
    WORD TableID = GetTableAdmin()->GetTableID (NULL,LOCKTABLENAME,&found,&Version);
    DBWIN_ASSERT (found);
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(TableID,Version);
    DBWIN_ASSERT (td != NULL);
    LPDBREQUEST req = InitializeRequest (UNLOCKACCESS,-1,DBCALLTYPE_STANDARDDELETE,c->DocumentID());
    req->SetTableID (TableID,Version);
    req->AddTableDef (TableID,Version,FALSE);
    req->SetParam (1,&TableID,sizeof(TableID));
    LPVOID key = c->ReadlData (par->lptr);
    DBWIN_ASSERT (key != NULL);
    req->SetParam (2,key,GetBlockSize (key));
    req->SetParamType(2,VAR_LONG);

    RecBuffer rb;
    lmemset (&rb,'\0',sizeof(rb));
    LPVOID hstmt = NULL;
    int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall 
                (DBOP_GET,1,req,&hstmt,&rb);

    // Den ganzen Scheiss wieder abbauen
    req->ClearParams();

    if (hstmt != NULL)
      GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
    if (req != NULL) {
      req->ClearForeign();
      req->FreeTableDefs();
      FreeRequest (req);
      }
    GetTableAdmin()->FreeTable(TableID,Version);
    }
  return FALSE;
  }

BOOL AvoidInput (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    if (c->outContext != NULL)
      c->outContext->dontUpdateDocument = TRUE ;
    c->dontUpdateDocument = TRUE ;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    if (c->outContext != NULL)
      c->outContext->dontUpdateDocument = FALSE ;
    c->dontUpdateDocument = FALSE ;
    if (mode & EM_CHANGETOFALSE) {
      InvalidateRect (c->OutWnd(),NULL,FALSE);
      ((FrmObjectList FAR *) c->OutList())->OnSetFocus ();

      BOOL oldBlockIsActive = BlockIsActive ;
      BlockIsActive = FALSE;

      LPOBJDEF hlp = ((FrmObjectList FAR *) c->OutList())->head ;
      for ( ; hlp != NULL ; hlp = hlp->NextObjDef ) {
        if (hlp->obj != NULL)
          hlp->obj->CheckActivation ();
        if (hlp->NextObjDef == ((FrmObjectList FAR *) c->OutList())->head) break ;
        }
      BlockIsActive = oldBlockIsActive;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetStatText_param {
  WORD parSize;
  DWORD Text;
  DWORD foreColor;
  DWORD backColor;
  };
#pragma pack()

BOOL SetStatText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetStatText_param FAR *par = (SetStatText_param FAR *) param;
    LPSTR Text = LPSTR (c->ReadlData (par->Text));
    if (Text != NULL) {
      c->PutDocumentExtraData (DED_RSTATBARTEXT,Text,lstrlen(Text)+1);
      }

    COLORREF foreColor = 0xFFFFFFFF;
    COLORREF backColor = 0xFFFFFFFF;
    if (par->parSize  >= sizeof(WORD) + 2*sizeof(DWORD)) {
      COLORREF FAR *lpforeColor = (COLORREF FAR *) (c->ReadlData (par->foreColor));

      if (lpforeColor == NULL) {
        DBWIN_ASSERT_TEXT (FALSE, "Fehlerhafte Schriftfarbe in Statuszeile");
        }
      else
        foreColor = *lpforeColor;
      }

    if (par->parSize  >= sizeof(WORD) + 3*sizeof(DWORD)) {
      COLORREF FAR *lpbackColor = (COLORREF FAR *) (c->ReadlData (par->backColor));

      if (lpbackColor == NULL) {
        DBWIN_ASSERT_TEXT (FALSE, "Fehlerhafte Hintergrundfarbe in Statuszeile");
        }
      else
        backColor = *lpbackColor;
      }

    ActivateStatBar (c,TRUE,foreColor,backColor);
    }
  if (mode & EM_FIXCONNECTION) {
    SetStatText_param FAR *par = (SetStatText_param FAR *) param;
    c->SetlConnection (par->Text,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetStatText_param FAR *par = (SetStatText_param FAR *) param;
    c->ClearlConnection (par->Text,LPSTR(param)-sizeof(WORD));
    c->RemoveDocumentExtraData (DED_RSTATBARTEXT);
    ActivateStatBar (c,FALSE);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR LockDataKey_param {
  WORD parSize;
  DWORD res;
  DWORD DataKey;
  };
#pragma pack()

BOOL LockDataKey (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL lockDone = FALSE ;
  if (mode & EM_LOAD) {
    LockDataKey_param FAR *par = (LockDataKey_param FAR *) param;
    LPVOID Key = c->ReadlData(par->DataKey);
    DBWIN_ASSERT(Key != NULL);
    LPVOID Handle;
    if (lockDone = DoLockAccess(&Handle,c,0,Key)) {
      c->WritelData (par->res,Handle,GetBlockSize(Handle),LPSTR(param)-sizeof(WORD));
      FreeGlobMem(Handle);
      }
    else {
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      if (c->outContext != NULL)
        c->outContext->dontUpdateDocument = TRUE ;
      c->dontUpdateDocument = TRUE ;
      }
    }
  return lockDone;
  }

#pragma pack(1)
struct FAR GetTableID_param {
  WORD parSize;
  DWORD res;
  DWORD TBName;
  };
#pragma pack()

BOOL GetTableID (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL lockDone = FALSE ;
  if (mode & EM_LOAD) {
    GetTableID_param FAR *par = (GetTableID_param FAR *) param;
    LPSTR Key = LPSTR (c->ReadlData(par->TBName));
    DBWIN_ASSERT(Key != NULL);
    BOOL found;
    WORD Version;
    WORD res = GetTableAdmin()->GetTableID (NULL,Key,&found,&Version);
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetTableID_param FAR *par = (GetTableID_param FAR *) param;
    c->ClearlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  return lockDone;
  }

