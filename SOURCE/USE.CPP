//////////////////////////////////////
//  Setzen eines Datensatzes
//////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/use.cpv   1.58   07 Jun 2000 10:23:20   Wolfgang  $
//  $Log:   P:/marille/clinicum/rev/use.cpv  $
// 
//    Rev 1.58   07 Jun 2000 10:23:20   Wolfgang
// 1.) DBCall_Parse neu.
// 
//    Rev 1.57   03 Dec 1999 02:38:52   Hannes
// ErrorText
// 
//    Rev 1.56   08 Oct 1999 14:21:08   Wolfgang
// 1.) IsInTransaction eingebaut.
// 
//    Rev 1.55   17 Sep 1999 02:38:28   Hannes
// 
//    Rev 1.54   23 Aug 1999 14:58:32   Hannes
// 
//    Rev 1.53   13 May 1999 22:27:16   Hannes
// Beim Update In Liste auf jeden Fall einen Get
// 
//    Rev 1.52   31 Mar 1999 08:12:20   Hannes
// Update des Records...
// 
//    Rev 1.51   17 Feb 1999 21:01:46   Hannes
// UseIntern abgesichert
// 
//    Rev 1.50   11 Feb 1999 17:30:14   Hannes
// 
//    Rev 1.49   05 Feb 1999 21:36:46   Martin
// verbessertes Errorhandling
// 
//    Rev 1.48   28 Jan 1999 12:20:06   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.47   19 Jan 1999 19:25:46   Hannes
// SetUserName
// 
//    Rev 1.46   11 Jan 1999 08:19:54   Hannes
// Austausch Records im Aufrufer-> Kontextaustauch in Kindern
// 
//    Rev 1.45   23 Nov 1998 15:48:48   Wolfgang
// 1.) Rueckgabeflag ist jetzt DBBOOL.
// 
//    Rev 1.44   01 Sep 1998 23:43:18   Hannes
// ClearConnection auf Commando in ExCute
// 
//    Rev 1.43   28 Apr 1998 18:20:24   Martin
// ParamType auch bei NULL setzen
// 
//    Rev 1.42   06 Mar 1998 18:49:50   Hannes
// 
//    Rev 1.41   06 Mar 1998 18:02:58   Hannes
// 
//    Rev 1.40   06 Mar 1998 17:26:46   Hannes
// 
//    Rev 1.39   10 Feb 1998 18:27:32   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.38   05 Jan 1998 10:05:30   Gerhold
// ein kleiner Klammer-Fehler
// 
//    Rev 1.37   05 Jan 1998 07:54:06   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.36   22 Jul 1997 21:08:22   Hannes
// 
//    Rev 1.35   09 Jun 1997 13:11:28   Hannes
// 
//    Rev 1.34   27 May 1997 11:28:10   Hannes
// Erweiterte Funktionalitaet im UseIntern
// 
//    Rev 1.33   21 Apr 1997 20:46:26   Hannes
// SetRecHash,ClearRecHash
// 
//    Rev 1.32   19 Feb 1997 12:18:16   Hannes
// Ueberpruefen der Parents bei den Verwendeten Funktionen
// 
//    Rev 1.31   19 Dec 1996 19:16:34   HANNES
// Sicherheitsabfragen auf par->req
// 
//    Rev 1.30   16 Dec 1996 18:43:14   HANNES
// 
//    Rev 1.29   12 Dec 1996 12:18:30   HANNES
// OldParam eingebaut zur effizienten Refresh - Join behandlung
// 
//    Rev 1.28   26 Nov 1996 08:14:52   HANNES
// Automatischer Update
// 
//    Rev 1.27   08 Nov 1996 13:34:50   HANNES
// SetRec ... neuer Prototyp
// 
//    Rev 1.26   28 Oct 1996 08:39:14   HANNES
// OwnerID,DocumentID
// 
//    Rev 1.25   21 Oct 1996 18:49:22   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.24   12 Sep 1996 23:12:54   HANNES
// SetRecHash, RemoveRecHash
// 
//    Rev 1.23   10 Jun 1996 10:10:10   GERHOLD
// pragma pack
// 
//    Rev 1.22   28 Mar 1996 11:34:46   MARTIN
// DBCall_Excute: req->AnzParam gesetzt
// 
//    Rev 1.21   26 Mar 1996 17:29:14   MARTIN
// AnzParam richtig setzen
// 
//    Rev 1.20   02 Feb 1996 10:35:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.19   26 Jan 1996 14:57:48   HANNES
// 
//    Rev 1.18   24 Aug 1995 00:20:16   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.17   14 Jul 1995 16:54:06   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.16   12 Jul 1995 10:59:52   HANNES
// CopySameVars verbessert
// 
//    Rev 1.15   09 Jun 1995 00:21:00   HANNES
// CSYSRECS
// 
//    Rev 1.14   20 May 1995 16:16:18   HANNES
// CopySameVars
// 
//    Rev 1.13   27 Apr 1995 15:37:54   HANNES
// No change.
// 
//    Rev 1.12   27 Mar 1995 13:17:22   HANNES
//  
// 
//    Rev 1.11   20 Mar 1995 12:05:58   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.10   24 Feb 1995 11:17:26   HANNES
//  
// 
//    Rev 1.9   16 Feb 1995 12:52:16   HANNES
// 
//    Rev 1.8   09 Nov 1994 13:15:56   MARTIN
// AvoidUpdates
// 
//    Rev 1.7   07 Nov 1994 11:25:50   joerg
// Verbesserungen der Kopierfunktionen
// 
//    Rev 1.6   31 Oct 1994 09:58:54   hannes
// IsUpdateDone
// GetRecCopy
// 
//    Rev 1.5   31 Aug 1994 15:40:52   HANNES
// ReUse ... auf andere Tabelle
// 
//    Rev 1.4   19 Aug 1994 10:39:10   HANNES
// Im NewRec Einfueheren des Primaerschluessels
// 
//    Rev 1.3   17 Jul 1994 14:45:56   HANNES
// Primaerschluesselumorganisation
// 
//    Rev 1.2   13 Jul 1994 21:16:22   HANNES
// Verwendung der neuen Prozedur RefreshJoin
// 
//    Rev 1.1   12 Jul 1994 14:50:54   HANNES
// Erweiterung fuer Datenbankhandling mit der Mappe
// 
//    Rev 1.0   24 Jun 1994 17:04:46   HANNES
// Neuuebernahme clinicum
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
#define MODULENUM 97
#include "winass.hpp"
#include "tbcbd.hpp"

/////////////////////////////////////////////////////
// Die Primitiv - variante
// - Keine Datenbankoperation
// - Direkte Angabe des Primaerschluessels
// - Keinen Update auf den Primaerschluessel
/////////////////////////////////////////////////////
#pragma pack(1)
struct FAR UseIntern_param {
  WORD  parSize;
  DWORD TableName;
  DWORD primKey;
  DWORD extraData[1];
  DWORD GetprimID(mdiChild *c)
    {
    if (parSize >= sizeof(*this))
      return c->ReadConstLong (extraData[0]);
    else
      return 0L;
    }
  BOOL withUpdate()
    {
    return (parSize >= sizeof(*this));
    }
  BOOL replacePrimKey(mdiChild *c)
    {
    BOOL replaceKey = TRUE ;
    if (parSize >= sizeof(*this) + sizeof(DWORD)) {
     if (c->ReadConstInt (extraData[1]))
       replaceKey = FALSE ;
     }
    return replaceKey;
    }
  };
#pragma pack()

extern DLLExport int _export WINAPI GetTableNr (LPSCRIPTCONTENT scent,WORD FAR *TableID,WORD FAR *Version,LPSTR TableName,DWORD ExtraID);
extern DLLExport void _export FAR PASCAL ReplacePrimKey (LPDBRECORD n,LPPRIMKEY kn);
void ReplaceNextSame (mdiChild *c,WORD tnr,LPDBRECORD o,LPDBRECORD n)
  {
  for (WORD i = 0 ; i < o->GetAnzVars() ; i++) {
    DWORD eNummer = DWORD(c->rr) + tnr ;
    LPVARELEM v1 = o->GetVarElem(i);
    if (v1->NextSame != NULL) {
      LPVARELEM v1a = n->GetVarElem(i);
      LPVARELEM prev = v1 ;
      for (LPVARELEM h = v1->NextSame ; ; ) {
        LPVARELEM Next = h->NextSame;
        if (h->Erzeuger == eNummer) {
          prev->NextSame = h->NextSame ;
          h->NextSame = NULL ;
          h->FillIn (v1a);
          }
        else
          prev = h ;
        if (Next == v1)
          break ;
        else
          h = Next ;
        }
      if (v1->NextSame == v1) v1->NextSame = NULL ;
      }
    }
  }
BOOL UseIntern (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    UseIntern_param FAR *par = (UseIntern_param FAR *) param;
    LPSTR  TableName = LPSTR (c->ReadlData (par->TableName));
    LPVOID pk        = c->ReadlData (par->primKey);
    DBWIN_ASSERT(TableName != NULL);
    DBWIN_ASSERT (pk != NULL);

    // Untersuchung, ob die Tabelle auch wirklich in der Liste ist
    BOOL found = FALSE ;
    PrimKey k;
    k.PushKeySeg (pk,GetBlockSize(pk));
    WORD tid,Version;
    int tnr = GetTableNr (c->schd,&tid,&Version,TableName,par->GetprimID(c));
    if (tnr > 0) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef(tid,Version);
      WIN_ASSERT (td->GetParentID() == 0);
      BOOL doReplace = TRUE;
      LPDBRECORD old = NULL;
      if ((mode & EM_UPDATE) && (!c->IsInListFunction ())) {
        if (par->replacePrimKey (c)) {
          LPDBRECORD n = c->rr->GetRecord (tnr);
          ReplacePrimKey (n,&k);
          doReplace = FALSE;
          LPDBRECORD s = GetDBRecordAdmin()->Find(&k,td->GetTableID(),td->GetVersion());
          if ((s != NULL) && (s != n)) {
            // Im System gibts schon einen Satz mit diesem Primaerschlussel,
            // der muss selbstverstaendlich verwendet werden, damit
            // keine doppelten Primaerschluessel mehr vorkommen!!!!
            ReplaceNextSame (c,tnr,n,s);
            s->Update (n);
            c->rr->SetRec (s,tnr,c->DocumentID(),FALSE);
            }
          }
        else
          old = c->rr->GetRecord (tnr);
        }
      else
        old = c->rr->GetRecord (tnr);
      if (doReplace) {
        LPDBRECORD n = GetDBRecordAdmin()->Find(&k,td->GetTableID(),td->GetVersion());
        if (n == NULL) {
          n = new DBRecord(td);
          n->SetPrimKey (&k);
          }
        if (!((c->IsInListFunction ()) && (par->replacePrimKey (c)))) {
          if ((old != NULL) && (n != old))
            ReplaceNextSame (c,tnr,old,n);
          c->rr->SetRec (n,tnr,c->DocumentID(),FALSE);
          }
        else {
          if ((old != NULL) && (n != old))
            ReplaceNextSame (c,tnr,old,n);
          c->rr->SetRecord (tnr,n);
          }
        }
      GetTableAdmin()->FreeTable(tid,Version);
      }
    else
      DBWIN_ASSERT(FALSE);
    }
  if (mode & EM_FIXCONNECTION) {
    UseIntern_param FAR *par = (UseIntern_param FAR *) param;
    if (par->withUpdate())
      c->SetlConnection (par->primKey,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    UseIntern_param FAR *par = (UseIntern_param FAR *) param;
    c->ClearlConnection (par->primKey,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

/////////////////////////////////////////////////////////////////////
//  Die Volle Variante:
//  - Datenbankoperation
//  - Connections auf die Parameter setzen
//  - Connections auf die Foreignkeys setzen
//  - Auf Update selektiv reagieren
/////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR TRef {
  DWORD TableName;      // Table
  DWORD RecordFound;
  DWORD rdoLock;
  };
#pragma pack()
typedef TableRef FAR *LPTABLEREF;

#pragma pack(1)
struct FAR ParRef {
  DWORD rAnzPars;
  DWORD ref[1];
  int AnzPars(mdiChild *c)
    { return c->ReadConstInt (rAnzPars) ; }
  };
#pragma pack()
typedef ParRef FAR *LPPARREF;

#pragma pack(1)
struct FAR Use_par {
  WORD  parSize;
  LPDBREQUEST req;      // Private Daten
  LPVOID      hstmt;    //  ... 8 Byte ...
  DWORD AccessName;     // Zugriffsname
  DWORD rAnzTables;      // Anzahl Tabellen, die an dem Zugriff beteiligt
                        // sind
  // Dahinter :
  // - AnzTables x TableRef
  // - ParRef mit AnzPars Refernzen auf die Parameter
  };
#pragma pack()

#pragma pack(1)
struct FAR DBGet_par {
  WORD parSize;
  LPDBREQUEST req;
  LPVOID      hstmt;
  DWORD       Command;
  DWORD       TableName;    // Entspricht dem vorderen Teil von TableRef
  DWORD       resFlag;
  ParRef      pr;
  };
#pragma pack()

#pragma pack(1)
struct FAR DBInsert_par {
  WORD parSize;
  LPDBREQUEST req;
  LPVOID      hstmt;
  DWORD       TableName;    // Entspricht dem vorderen Teil von TableRef
  DWORD       resFlag;
  ParRef      pr;
  };
#pragma pack()

class Use_param {
 protected :
  LPVOID ParData;
 public :
  Use_param (LPVOID pdata)
    { ParData = pdata ; }

  virtual LPDBREQUEST req()
    { return ((Use_par FAR *) ParData)->req ; }
  virtual LPVOID hstmt()
    { return ((Use_par FAR *) ParData)->hstmt; }
  virtual DWORD AccessName()
    { return ((Use_par FAR *) ParData)->AccessName; }
  virtual int AnzTables(mdiChild *c)
    { return c->ReadConstInt (((Use_par FAR *) ParData)->rAnzTables); }
  virtual TRef FAR *GetTableRef()
    { return (TRef FAR *)((Use_par FAR *) (ParData)+1) ; }
  virtual LPPARREF par(mdiChild *c) 
    { 
    return LPPARREF (LPSTR(((Use_par FAR *) ParData) + 1) + sizeof(TableRef) * AnzTables(c)) ;
    }
  virtual void SetDBRequest (LPDBREQUEST rq)
    { ((Use_par FAR *) ParData)->req = rq; }
  virtual void SetStatement(LPVOID ptr)
    { ((Use_par FAR *) ParData)->hstmt = ptr; }
  virtual LPVOID FAR *GetStatementAddress()
    { return &(((Use_par FAR *) ParData)->hstmt); }
  virtual BOOL GetLockState  (mdiChild *c,int Nr);
  LPSTR ConnectionAddress()
    {
    return (LPSTR (ParData) - sizeof(WORD)) ;
    }
  LPSTR GetTableName(mdiChild *c,int Nr);
  LPTABLEDEF GetTableDef   (mdiChild *c,int Nr);
  void SetFound(mdiChild *c,int Nr,DBBOOL flag);
  int AnzElems(mdiChild *c);
  void SetRequest(mdiChild *c);
  void SetParams (mdiChild *c);
  WORD TableNr(mdiChild *c,WORD Nr);
  void SetLocked(mdiChild *c,int Nr,BOOL);
  void SetRecs (int res,LPRECBUFFER rb,mdiChild *c,BOOL delPrimkey,BOOL fromInsert);
  void SetDBRes (int res,mdiChild *c);
  BOOL GetRecs (LPRECBUFFER rb,mdiChild *c);
  LPSTR SelectionName (mdiChild *c)
    {
    DWORD AccessN = AccessName();
    if (AccessN != 0xFFFFFFFF)
      return LPSTR(c->ReadlData (AccessName()));
    else
      return "" ;
    }
  void SetStdConnections(mdiChild *c);
  void ExtConnections(int tnr,mdiChild *c,BOOL doSet);
  void ExtUpdate(mdiChild *c);
  void ClearStdConnections(mdiChild *c);
  BOOL IsStdUpdate(mdiChild *c);
  int ReadParams(mdiChild *c,LPVOID FAR *ParData);
  };
class DBGet_param : public Use_param {
 public :
  DBGet_param (LPVOID pdata) : Use_param (pdata)
    { }

  virtual LPDBREQUEST req()
    { return ((DBGet_par FAR *) ParData)->req ; }
  virtual LPVOID hstmt()
    { return ((DBGet_par FAR *) ParData)->hstmt; }
  virtual DWORD AccessName()
    { return ((DBGet_par FAR *) ParData)->Command; }
  virtual int AnzTables(mdiChild *c)
    { return 1; }
  virtual TRef FAR *GetTableRef()
    { return (TRef FAR *) &((DBGet_par FAR *) (ParData))->TableName ; }
  virtual LPPARREF par(mdiChild *c) 
    { 
    return LPPARREF (&(((DBGet_par FAR *) ParData)->pr)) ;
    }
  virtual void SetDBRequest (LPDBREQUEST rq)
    { ((DBGet_par FAR *) ParData)->req = rq; }
  virtual void SetStatement(LPVOID ptr)
    { ((DBGet_par FAR *) ParData)->hstmt = ptr; }
  virtual LPVOID FAR *GetStatementAddress()
    { return &(((DBGet_par FAR *) ParData)->hstmt); }
  virtual BOOL GetLockState  (mdiChild *c,int Nr)
    { return FALSE ; }
  };
class DBInsert_param : public Use_param {
 public :
  DBInsert_param (LPVOID pdata) : Use_param (pdata)
    { }

  virtual LPDBREQUEST req()
    { return ((DBInsert_par FAR *) ParData)->req ; }
  virtual LPVOID hstmt()
    { return ((DBInsert_par FAR *) ParData)->hstmt; }
  virtual DWORD AccessName()
    { return 0xFFFFFFFF; }
  virtual int AnzTables(mdiChild *c)
    { return 1; }
  virtual TRef FAR *GetTableRef()
    { return (TRef FAR *) &((DBInsert_par FAR *) (ParData))->TableName ; }
  virtual LPPARREF par(mdiChild *c) 
    { 
    return LPPARREF (&(((DBInsert_par FAR *) ParData)->pr)) ;
    }
  virtual void SetDBRequest (LPDBREQUEST rq)
    { ((DBInsert_par FAR *) ParData)->req = rq; }
  virtual void SetStatement(LPVOID ptr)
    { ((DBInsert_par FAR *) ParData)->hstmt = ptr; }
  virtual LPVOID FAR *GetStatementAddress()
    { return &(((DBInsert_par FAR *) ParData)->hstmt); }
  virtual BOOL GetLockState  (mdiChild *c,int Nr)
    { return FALSE ; }
  };

LPSTR Use_param::GetTableName (mdiChild *c,int Nr)
  {
  TRef FAR *r = GetTableRef();
  return LPSTR (c->ReadlData (r[Nr].TableName));
  }

void Use_param::SetFound (mdiChild *c,int Nr,DBBOOL flag)
  {
  TRef FAR *r = GetTableRef();
  c->WritelData (r[Nr].RecordFound,&flag,sizeof(flag),
               ConnectionAddress());
  }

LPTABLEDEF Use_param::GetTableDef (mdiChild *c,int Nr)
  {
  LPSTR TableName = GetTableName(c,Nr);
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    WORD tid,Version;
    int tnr = GetTableNr (c->schd,&tid,&Version,TableName);
    if (tnr >= 0) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (tid,Version);
      WIN_ASSERT (td->GetParentID() == 0);
      return td;
      }
    }
  char outtxt[128];
  wsprintf (outtxt,"Tabelle nicht def.: %s (%s)",TableName,c->schd->fName);
  DBWIN_ASSERT_TEXT(FALSE,outtxt);    // Tabelle nicht definiert
  return NULL;
  }

BOOL Use_param::GetLockState  (mdiChild *c,int Nr)
  {
  TRef FAR *r = GetTableRef();
  return c->ReadConstInt (r->rdoLock);
  }

int Use_param::AnzElems(mdiChild *c)
  {
  int res;
  if (AnzTables(c) == 1) {
    LPTABLEDEF td = GetTableDef(c,0);
    if (td->IsInternTable()) res = td->GetAnzVars();
    else                     res = -1;
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  else
    res = -1;
  return res;
  }

void Use_param::SetRequest(mdiChild *c)
  {
  BOOL internDone = FALSE ;
  if (AnzTables(c) == 1) {
    // Es koennte ja eine interne sein
    LPTABLEDEF td     = GetTableDef(c,0);
    BOOL       doLock = GetLockState (c,0);
    if (td->IsInternTable()) {
      LPINTTABLE ti = LPINTTABLE(td->GetDLLDef());
      for (WORD i = 0 ; i < ti->AnzTables ; i++) {
        LPPTABLE pt    = ti->GetTableByNum (i);
        BOOL lockState = ti->GetPartLock (i);
        req()->AddTableDef (pt->tRef.TableNr,pt->tRef.Version,lockState && doLock);
        }
      for (i = 0 ; i < WORD(td->GetAnzVars()) ; i++) {
        ReqElem e;
        ti->GetReqElem (&e,i);
        req()->SetReqElemDirect (i,e.TableNumber,e.VarID);
        }
      internDone = TRUE ;
      }
    req()->SetTableID(td->GetTableID(),td->GetVersion());
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  if (!internDone) {
    // Stinkgewoehnlich ...
    int at = AnzTables(c);
    for (int i = 0 ; i < at ; i++) {
      LPTABLEDEF td = GetTableDef(c,i);
      req()->AddTableDef (td->GetTableID(),td->GetVersion(),GetLockState(c,i));
      if (i == 0)
        req()->SetTableID(td->GetTableID(),td->GetVersion());
      GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
      }
    }
  }

void Use_param::SetParams (mdiChild *c)
  {
  WORD TableID = req()->TableDef[0]->GetTableID();
  req()->SetParam (1,&TableID,sizeof(TableID));
  LPPARREF r = par(c);
  int ap = r->AnzPars(c);
  for (int i = 0 ; i < ap ; i ++ ) {
    LPVOID p = c->ReadlData (r->ref[i]);
    if (p != NULL)
      req()->SetParam(i+2,p,GetBlockSize(p));
    req()->SetParamType(i+2,c->GetDataType(r->ref[i]));
    }
  // AnzParam soll bitte angeben, wieviele Referenzen im Script angegeben sind
  req()->AnzParam = ap + 1;
  }

void TestRes (int res,Use_param *par,mdiChild *c)
  {
  char outtxt[128];
  if (res == DBCALL_ERROR) {
    LPTABLEDEF td = par->GetTableDef(c,0);
    wsprintf (outtxt,"DBCALL_ERROR on %s",td->GetName());
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    DBWIN_ASSERT_TEXT (FALSE,outtxt);
    }
  else if (res == DBCALL_ERROR_NOACCESS) {
    LPTABLEDEF td = par->GetTableDef(c,0);
    wsprintf (outtxt,"DBCALL_NOACCESS: %s not defined in %s",
              par->SelectionName(c),
              td->GetName()
             );
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    DBWIN_ASSERT_TEXT (FALSE,outtxt);
    }
  }

WORD GetTableInd (mdiChild *c,LPSTR TableName)
  {
  WORD tid,Version;
  int tnr = GetTableNr (c->schd,&tid,&Version,TableName);
  if (tnr > 0) return tnr ;
  else         return 0xFFFF ;
  }

WORD Use_param::TableNr(mdiChild *c,WORD Nr)
  {
  return GetTableInd (c,GetTableName(c,Nr));
  }

void Use_param::SetStdConnections(mdiChild *c)
  {
  LPPARREF p = par(c);
  int ap = p->AnzPars(c);
  for (int i = 0 ; i < ap ; i++)
    c->SetlConnection (p->ref[i],ConnectionAddress());
  }

void Use_param::ClearStdConnections(mdiChild *c)
  {
  LPPARREF p = par(c);
  int ap = p->AnzPars(c);
  for (int i = 0 ; i < ap ; i++)
    c->ClearlConnection (p->ref[i],ConnectionAddress());
  }

BOOL Use_param::IsStdUpdate(mdiChild *c)
  {
  LPPARREF p = par(c);
  BOOL res = FALSE ;
  int ap = p->AnzPars(c);
  for (int i = 0 ; ((i < ap) && (!res)) ; i++)
    res = c->IsUpdatelFromEle (p->ref[i]);
  return res;
  }

void Use_param::SetRecs (int res,LPRECBUFFER rb,mdiChild *c,BOOL delPrimKey,BOOL fromInsert)
  {
  if (res == DBCALL_SUCCESS) {
    // Na wunderbar
    int at = AnzTables(c);
    for (int i = 0 ; i < at ; i++) {
      if (rb->act->rec[i] != NULL) {
        if (delPrimKey) {
          rb->act->rec[i]->ClearPrimKey();
          rb->act->rec[i]->setLocked ();
          }
        req()->oldP = req()->SaveOldParams (rb->act->rec[i]);
        LPDBRECORD n = rb->act->rec[i];
        WORD tnr = TableNr(c,i);
        LPDBRECORD old = c->rr->GetRecord (tnr);
        if ((!fromInsert) && (old != NULL) && (n != old))
          ReplaceNextSame (c,tnr,old,n);
        c->rr->SetRec (n,tnr,c->DocumentID(),fromInsert) ;

        LPDBRECORD used = c->rr->GetRecord (tnr);
        if (c->rr->PrevInKontext[tnr].rr == NULL) { 
                // Nur dann updaten, wenn es sich wirklich um einen 'Ausgangsdatensatz handelt'
          for ( LPRRR r = c->rr->NextInKontext + tnr ; r->rr != NULL ; r = r->rr->NextInKontext + r->tnr ) {
            r->rr->SetRecord (r->tnr,used);
            used->Update (r->rrOwner->DocumentID());
            }
          }
        rb->act->rec[i] = NULL;
        SetFound(c,i,TRUE);
        }
      else {
        SetFound(c,i,FALSE);
        WORD tnr = TableNr(c,i);
        LPDBRECORD rec = c->rr->GetRecord(tnr);
        if (rec != NULL) {
          if (GetDBRecordAdmin()->Release (rec,DWORD(c->rr) + tnr,c->DocumentID()))
            delete rec;
          }
        c->rr->SetRecord(tnr,NULL);
        }
      }
    }
  else {
    int at = AnzTables(c);
    for (int i = 0 ; i < at ; i++) {
      SetFound(c,i,FALSE);
#ifdef UEBERLEGT
      WORD tnr = GetTableNr(c,i);
      LPDBRECORD rec = c->rr->GetRecord(tnr);
      if (rec != NULL) {
        if (GetDBRecordAdmin()->Release (rec,DWORD(c->rr) + tnr,c->DocumentID()))
          delete rec;
        }
      c->rr->SetRecord(tnr,NULL);
#endif
      }
    }
  rb->Clear ();
  }

void Use_param::SetDBRes (int res,mdiChild *c)
  {
  int at = AnzTables(c);
  if (res == DBCALL_SUCCESS) {
    // Na wunderbar
    for (int i = 0 ; i < at ; i++)
      SetFound(c,i,TRUE);
    }
  else {
    for (int i = 0 ; i < at ; i++)
      SetFound(c,i,FALSE);
    }
  }

BOOL Use_param::GetRecs (LPRECBUFFER rb,mdiChild *c)
  {
  BOOL res = FALSE;
  int at = AnzTables(c);
  rb->AddLine (at,ADDLINEPOS_END);
  for (int i = 0 ; i < at ; i++) {
    LPDBRECORD h = c->rr->GetRecord (TableNr(c,i));
    DBWIN_ASSERT (
        (rb->act->rec[i] = h)
                != NULL
               );
    // if (h->IsUpdateDone ()) res = TRUE ;
    res = TRUE ;
    }
  if (!res) {
    // Nix gewesen ausser Spesen
    for (int i = 0 ; i < at ; i++) 
      rb->act->rec[i] = NULL;
    }
  return res;
  }

#ifdef UEBERLEGT
WORD GetRInd (mdiChild *c,WORD TableID)
  {
  for (WORD k = 0 ; k < c->schd->AnzTables ; k++) {
    if (TableID == c->schd->TableNr[k]) return k + CSYSRECS;
    }
  return 0xFFFF;
  }
#endif
void Use_param::ExtConnections (int tnr,mdiChild *c,BOOL doSet)
  {
  LPDBREQUEST rq = req();
  if ((rq != NULL) && (rq->foreignDone)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (rq->fdsc[i].freq != NULL) {
//        WORD rInd = GetRInd (c,rq->TableID);
        WORD rInd = TableNr (c,0);
        LPDBRECORD r = c->rr->GetRecord(rInd);
        for (WORD j = 0 ; ((j < MANZSEGS) && (r != NULL)) ; j++) {
          if (rq->fdsc[i].VarID[j] != 0xFFFF) {
            if (doSet) r->SetConnection (DWORD(c->rr) + tnr,rq->fdsc[i].VarID[j],
                            c->DocumentID(),ConnectionAddress(),
                            c->_ccount
                                        );
            else       r->ClearConnection (DWORD(c->rr) + tnr,rq->fdsc[i].VarID[j],
                            c->DocumentID(),ConnectionAddress()
                                        );
            }
          }
        }
      }
    }
  }

int Use_param::ReadParams(mdiChild *c,LPVOID FAR *ParData)
  {
  LPPARREF r = par(c);
  int ap = r->AnzPars(c);
  for (int i = 0 ; i < ap ; i ++ ) {
    ParData[i] = c->ReadlData (r->ref[i]);
    }
  return i ;
  }

void Use_param::ExtUpdate (mdiChild *c)
  {
  LPDBREQUEST rq = req();
  if ((rq != NULL) && (rq->foreignDone) && (rq->oldP != NULL)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (rq->fdsc[i].freq != NULL) {
        WORD rInd = TableNr (c,0);
        LPDBRECORD r = c->rr->GetRecord(rInd);
        if (rq->IsUpdateDone (r,i,rq->oldP)) {
          LPVOID ParData[CB_PARAM];
          lmemset (ParData,'\0',sizeof(ParData));
          int AnzPars = ReadParams(c,ParData);
          r->RefreshJoin (rq,i,ParData,AnzPars,rq->oldP);
          }
        }
      }
    }
  }

BOOL Use (mdiChild *c,Use_param *par,WORD mode,BOOL RecIn,BOOL RecOut,
            BOOL doConnect,BOOL DelPrimKey = FALSE,
            WORD CallType = DBCALLTYPE_EXTENDED
         )
  {
  if (mode & EM_LOAD) {
    // Initialisieren des Requests
    par->SetDBRequest (InitializeRequest (par->SelectionName(c),par->AnzElems(c),CallType,c->DocumentID()));
    par->req()->ErrorCBP = GetLastErrorCBP();
    par->SetRequest(c);

    // Laden der Parameter
    par->SetParams(c);

    // Und es kann schon losgehen
    RecBuffer rb;
    lmemset (&rb,'\0',sizeof(rb));
    BOOL doIt = TRUE ;
    if (RecIn)
      doIt = par->GetRecs (&rb,c);
    int res;
    if ((doIt) || (RecOut)) {
      DLLHANDLE hd = par->req()->GetDLLHandle();
      BeginErrorHandling (par->req()->ErrorCBP,hd);
      res = GetDLLAdmin()->GetDLLEntry(hd)->DBCall 
                  (DBOP_GET,1,par->req(),par->GetStatementAddress(),&rb);
      LONG LastError = GetDLLAdmin()->GetDLLEntry(hd)->DBGetLastError ();
      if (LastError == 0)  // rosa Schirm nur falls kein zu ignorierender !
        TestRes (res,par,c);
      EndErrorHandling (par->req()->ErrorCBP,hd);
      par->req()->ClearParams();
      }
    if (RecOut)
      par->SetRecs (res,&rb,c,DelPrimKey,((RecIn) && (RecOut)));
    else
      par->SetDBRes (res,c);
    rb.Clear ();
    }
  if ((mode & EM_UPDATE) && (!RecIn)) {   // Updates haben kein EM_UPDATE verhalten
    if ((c->IsInListFunction ()) || (par->IsStdUpdate(c))) {
      par->SetParams(c);

      // Und es kann schon losgehen
      RecBuffer rb;
      lmemset (&rb,'\0',sizeof(rb));
      DLLHANDLE hd = par->req()->GetDLLHandle();
      BeginErrorHandling (par->req()->ErrorCBP,hd);
      int res = GetDLLAdmin()->GetDLLEntry(hd)->DBCall
                  (DBOP_GET,1,par->req(),par->GetStatementAddress(),&rb);
      LONG LastError = GetDLLAdmin()->GetDLLEntry(hd)->DBGetLastError ();
      if (LastError == 0)  // rosa Schirm nur falls kein zu ignorierender !
        TestRes (res,par,c);
      EndErrorHandling (par->req()->ErrorCBP,hd);
      par->req()->ClearParams();
      if (RecOut) {
        par->ExtConnections (par->TableNr(c,0),c,FALSE);
        par->SetRecs (res,&rb,c,DelPrimKey,((RecIn) && (RecOut)));
        par->ExtConnections (par->TableNr(c,0),c,TRUE);
        }
      }
    else {
      par->ExtUpdate (c);
      }
    }
  if ((mode & EM_FIXCONNECTION) && (doConnect)) {
    // Connections setzen 
    ////////////////////////////////////
    par->SetStdConnections (c);
    par->ExtConnections (par->TableNr(c,0),c,TRUE);
    // Und die nicht Standardselektionen
    //////////////////////////////////////
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    // Connections wieder freigeben
    ////////////////////////////////////
    if (doConnect) {
      par->ClearStdConnections (c);
      par->ExtConnections (par->TableNr(c,0),c,FALSE);
      }

    // Request wieder aufraeumen
    ////////////////////////////////////
    if (par->hstmt() != NULL)
      GetDLLAdmin()->GetDLLEntry(par->req()->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,par->GetStatementAddress(),NULL);
    WIN_ASSERT (par->req() != NULL);  // muss auf jeden Fall != NULL sein !
    if (par->req() != NULL) {
      if (par->req()->ErrorCBP != NULL) {
        FreeGlobMem(par->req()->ErrorCBP);
        par->req()->ErrorCBP = NULL;
        }
      par->req()->ClearForeign();
      par->req()->FreeTableDefs();
      FreeRequest (par->req());
      }
    par->SetDBRequest(NULL);
    par->SetStatement(NULL);
    }
  return FALSE ;
  }

//  Rein lesender Zugriff
/////////////////////////////////
BOOL Use (mdiChild *c,LPVOID param,WORD mode)
  {
  Use_param p (param);
  return Use (c,&p,mode,FALSE,TRUE,TRUE);
  }

//  Rein schreibender Zugriff
/////////////////////////////////
BOOL Out (mdiChild *c,LPVOID param,WORD mode)
  {
  Use_param p (param);
  return Use (c,&p,mode,TRUE,FALSE,FALSE);
  }

//  Schreibender und lesender Zugriff
///////////////////////////////////////
BOOL InOut (mdiChild *c,LPVOID param,WORD mode)
  {
  Use_param p (param);
  return Use (c,&p,mode,TRUE,TRUE,FALSE);
  }

//  Reiner Datenbankzugriff
///////////////////////////////////////
BOOL Do (mdiChild *c,LPVOID param,WORD mode)
  {
  Use_param p (param);
  return Use (c,&p,mode,FALSE,FALSE,FALSE);
  }

//  Kopierender Zugriff
///////////////////////////////////////
BOOL GetCopy (mdiChild *c,LPVOID param,WORD mode)
  {
  Use_param p (param);
  return Use (c,&p,mode,FALSE,TRUE,TRUE,TRUE);
  }

// Standard - Lesezugriff
BOOL DBCall_Get (mdiChild *c,LPVOID param,WORD mode)
  {
  DBGet_param p (param);
  return Use (c,&p,mode,FALSE,TRUE,TRUE,FALSE,DBCALLTYPE_STANDARDGET);
  }

// Standard - Lesezugriff mit Kopierfunktion
BOOL DBCall_Copy (mdiChild *c,LPVOID param,WORD mode)
  {
  DBGet_param p (param);
  return Use (c,&p,mode,FALSE,TRUE,TRUE,TRUE,DBCALLTYPE_STANDARDGET);
  }

// Standard - Update Zugriff
BOOL DBCall_Update (mdiChild *c,LPVOID param,WORD mode)
  {
  DBGet_param p (param);
  return Use (c,&p,mode,TRUE,FALSE,FALSE,FALSE,DBCALLTYPE_STANDARDUPDATE);
  }

// Standard - Insert Zugriff
BOOL DBCall_Insert (mdiChild *c,LPVOID param,WORD mode)
  {
  DBInsert_param p (param);
  return Use (c,&p,mode,TRUE,TRUE,FALSE,FALSE,DBCALLTYPE_STANDARDINSERT);
  }

BOOL DBCall_Delete (mdiChild *c,LPVOID param,WORD mode)
  {
  DBGet_param p (param);
  return Use (c,&p,mode,FALSE,FALSE,FALSE,FALSE,DBCALLTYPE_STANDARDDELETE);
  }

/*-----< Einfaches Ausfuehren eines SQL - Kommandos >-------*/
#pragma pack(1)
struct FAR DBCall_Excuteparam {
  WORD parSize;
  DWORD command;
  DWORD Params[1];
  int AnzPars()
    { return (parSize - (sizeof(*this) - sizeof(Params[0]))) / sizeof(Params[0]); }
  };
#pragma pack()

extern DLLExport DLLHANDLE _export WINAPI GetTransactionDLL ();
BOOL IstAusgabeParameter (LPDBREQUEST req,WORD parNum) 
  {
  for ( OutParam FAR *h = req->op ; h != NULL ; h = h->Next)
    if (h->parNum == parNum) return TRUE ;
  return FALSE;
  };

BOOL DBCall_Excute (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DBCall_Excuteparam FAR *par = (DBCall_Excuteparam FAR *) param;
    // jetzt wirds pervers: (ich will mir private Daten sparen)
    LPDWORD CommandUndErrorCBP;  // [0] = command, [1] = ErrorCBP
    if (mode & EM_LOAD) {
      CommandUndErrorCBP = (LPDWORD)GetGlobMem(2 * sizeof(DWORD));
      CommandUndErrorCBP[0] = par->command;
      CommandUndErrorCBP[1] = (DWORD)GetLastErrorCBP();
      par->command = (DWORD)CommandUndErrorCBP;
      }
    else {
      CommandUndErrorCBP = (LPDWORD)par->command;
      WIN_ASSERT(GetBlockSize(CommandUndErrorCBP) == (2 * sizeof(DWORD)));
      }
    LPSTR command = LPSTR (c->ReadlData (CommandUndErrorCBP[0]));
    LPDBREQUEST req = InitializeRequest (command,0,DBCALLTYPE_EXECUTE,c->DocumentID());
    for (int i = 0 ; i < par->AnzPars() ; i ++ ) {
      LPVOID p = c->ReadlData (par->Params[i]);
      if (p != NULL)
        req->SetParam(i+2,p,GetBlockSize(p));
      req->SetParamType(i+2,c->GetDataType(par->Params[i]));
      }
    req->AnzParam = par->AnzPars() + 1;
    DLLHANDLE hd = GetTransactionDLL ();
    LPDLLENTRY ent = GetDLLAdmin()->GetDLLEntry(hd);
    LPVOID hstmt = NULL;
    for ( BOOL first = TRUE ; ; first = FALSE ) {
      RecBuffer rb;
      lmemset (&rb,'\0',sizeof(rb));
      BeginErrorHandling (LPVOID(CommandUndErrorCBP[1]),hd);
      int res = ent->DBCall ((first) ? DBOP_GETFIRST : DBOP_GETNEXT,-1,req,&hstmt,&rb);
      EndErrorHandling (LPVOID(CommandUndErrorCBP[1]),hd);
      rb.Clear ();
      for ( OutParam FAR *h = req->op ; h != NULL ; h = h->Next) {
        if (h->Data)
          c->WritelData (par->Params[h->parNum - 1],h->Data,GetBlockSize (h->Data),LPSTR(param)-sizeof(WORD));
        else
          c->DellData (par->Params[h->parNum - 1],LPSTR(param)-sizeof(WORD));
        }

      #ifdef UEBERLEGT
      if ((mode & EM_FIXCONNECTION) && (first)) {
        // Alle Parameter, die nicht als Ausgabe vorhanden sind, muessen
        // verbunden werden
        for ( int i = 0 ; i < par->AnzPars () ; i++) {
          if (!IstAusgabeParameter (req,i + 1))
            c->SetlConnection (par->Params[i],LPSTR(param)-sizeof(WORD));
          }
        }
      #endif
      req->ClearOutParam ();
      if (res != DBCALL_SUCCESS) break;
      }
    ent->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);

    if (req->GetTableID() != 0)
      GetTableAdmin()->FreeTemporaryTable (req->GetTableID());

    req->ClearParams();
    req->FreeTableDefs();
    FreeRequest (req);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DBCall_Excuteparam FAR *par = (DBCall_Excuteparam FAR *) param;
    // Perversitaet wieder aufraeumen
    LPDWORD CommandUndErrorCBP = (LPDWORD)par->command;
    WIN_ASSERT(GetBlockSize(CommandUndErrorCBP) == (2 * sizeof(DWORD)));
    par->command = CommandUndErrorCBP[0];
    // if (CommandUndErrorCBP[1] != NULL)
    //   FreeGlobMem(LPVOID(CommandUndErrorCBP[1]));  !!!! Was ist das?
    FreeGlobMem(CommandUndErrorCBP);
    c->ClearlConnection (par->command,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR DBCall_Parseparam {
  WORD parSize;
  DWORD command;
  DWORD parseRes;
  DWORD parseStatement;
  DWORD parseError;
  DWORD parseErrorMsg;
  DWORD parseErrorOfs;
  DWORD Params[1];
  int AnzPars()
    { return (parSize - (sizeof(*this) - sizeof(Params[0]))) / sizeof(Params[0]); }
  };
#pragma pack()

void SetCPLParam (LPDBREQUEST req, WORD parNo, mdiChild *c, DWORD par)
  {
  LPVOID p = c->ReadlData (par);
  if (p != NULL)
    req->SetParam(parNo,p,GetBlockSize(p));
  req->SetParamType(parNo,c->GetDataType(par));
  }

BOOL DBCall_Parse (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DBCall_Parseparam FAR *par = (DBCall_Parseparam FAR *) param;
    // jetzt wirds pervers: (ich will mir private Daten sparen)
    LPDWORD CommandUndErrorCBP;  // [0] = command, [1] = ErrorCBP
    if (mode & EM_LOAD) {
      CommandUndErrorCBP = (LPDWORD)GetGlobMem(2 * sizeof(DWORD));
      CommandUndErrorCBP[0] = par->command;
      CommandUndErrorCBP[1] = (DWORD)GetLastErrorCBP();
      par->command = (DWORD)CommandUndErrorCBP;
      }
    else {
      CommandUndErrorCBP = (LPDWORD)par->command;
      WIN_ASSERT(GetBlockSize(CommandUndErrorCBP) == (2 * sizeof(DWORD)));
      }
    LPSTR command = LPSTR (c->ReadlData (CommandUndErrorCBP[0]));
    LPDBREQUEST req = InitializeRequest (command,0,DBCALLTYPE_EXECUTE,c->DocumentID());
    for (int i = 0 ; i < par->AnzPars() ; i ++ ) {
      SetCPLParam(req, i+2, c, par->Params[i]);
      }
    req->AnzParam = par->AnzPars() + 1;
    DLLHANDLE hd = GetTransactionDLL ();
    LPDLLENTRY ent = GetDLLAdmin()->GetDLLEntry(hd);
    LPVOID hstmt = NULL;
    ParseRecBuffer rb;
    lmemset (&rb,'\0',sizeof(rb));
    BeginErrorHandling (LPVOID(CommandUndErrorCBP[1]),hd);
    int res = ent->DBCall (DBOP_PARSE,-1,req,&hstmt,&rb);
    EndErrorHandling (LPVOID(CommandUndErrorCBP[1]),hd);

    DBBOOL flagRes;
    if (res == DBCALL_SUCCESS)
      flagRes = TRUE;
    else
      flagRes = FALSE;
    c->WritelData (par->parseRes,&flagRes,sizeof (flagRes),LPSTR(param)-sizeof(WORD));
    c->WritelData (par->parseStatement,rb.parseCmd,strlen (rb.parseCmd) + 1,LPSTR(param)-sizeof(WORD));
    if (!flagRes) {
      c->WritelData (par->parseError,&rb.error,sizeof (rb.error),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->parseErrorOfs,&rb.errorOfs,sizeof (rb.errorOfs),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->parseErrorMsg,rb.errorMsg,strlen (rb.errorMsg) + 1,LPSTR(param)-sizeof(WORD));
      }

    rb.Clear ();

    req->ClearOutParam ();

    ent->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);

    if (req->GetTableID() != 0)
      GetTableAdmin()->FreeTemporaryTable (req->GetTableID());

    req->ClearParams();
    req->FreeTableDefs();
    FreeRequest (req);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DBCall_Parseparam FAR *par = (DBCall_Parseparam FAR *) param;
    // Perversitaet wieder aufraeumen
    LPDWORD CommandUndErrorCBP = (LPDWORD)par->command;
    WIN_ASSERT(GetBlockSize(CommandUndErrorCBP) == (2 * sizeof(DWORD)));
    par->command = CommandUndErrorCBP[0];
    FreeGlobMem(CommandUndErrorCBP);
    c->ClearlConnection (par->command,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

//  Anlegen eines leeren Records
///////////////////////////////////////
#pragma pack(1)
struct FAR NewRec_param {
  WORD  parSize;
  LPDBREQUEST req;
  DWORD TableName;

  DWORD KeySeg[1];

  int AnzElems(LPTABLEDEF td);
  void ExtConnections (int tnr,mdiChild *c,BOOL doSet);
  void ExtUpdate (mdiChild *c);
  void SetRequest(mdiChild *c,LPTABLEDEF td);
  WORD TableNr (mdiChild *c)
    {
    LPSTR Name = LPSTR (c->ReadlData (TableName));
    return GetTableInd (c,Name);
    }

  int AnzKeySegs ()
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; }
  };
#pragma pack()

void NewRec_param::SetRequest(mdiChild *c,LPTABLEDEF td)
  {
  if (td->IsInternTable()) {
    LPINTTABLE ti = LPINTTABLE(td->GetDLLDef());
    for (WORD i = 0 ; i < ti->AnzTables ; i++) {
      LPPTABLE pt    = ti->GetTableByNum (i);
      req->AddTableDef (pt->tRef.TableNr,pt->tRef.Version,FALSE);
      }
    for (i = 0 ; i < WORD(td->GetAnzVars()) ; i++) {
      ReqElem e;
      ti->GetReqElem (&e,i);
      req->SetReqElemDirect (i,e.TableNumber,e.VarID);
      }
    req->SetTableID(td->GetTableID(),td->GetVersion());
    }
  }

void NewRec_param::ExtConnections (int tnr,mdiChild *c,BOOL doSet)
  {
  if ((req != NULL) && (req->foreignDone)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (req->fdsc[i].freq != NULL) {
//        WORD rInd = GetRInd (c,req->TableID);
        WORD rInd = TableNr(c);
        LPDBRECORD r = c->rr->GetRecord(rInd);
        for (WORD j = 0 ; ((j < MANZSEGS) && (r != NULL)) ; j++) {
          if (req->fdsc[i].VarID[j] != 0xFFFF) {
            if (doSet) r->SetConnection (DWORD(c->rr) + tnr,req->fdsc[i].VarID[j],
                            c->DocumentID(),LPSTR(this)-sizeof(WORD),
                            c->_ccount
                                        );
            else       r->ClearConnection (DWORD(c->rr) + tnr,req->fdsc[i].VarID[j],
                            c->DocumentID(),LPSTR(this)-sizeof(WORD)
                                        );
            }
          }
        }
      }
    }
  }

void NewRec_param::ExtUpdate (mdiChild *c)
  {
  if ((req != NULL) && (req->foreignDone) && (req->oldP != NULL)) {
    for (WORD i = 1 ; i < CB_TABLEDEF ; i++) {
      if (req->fdsc[i].freq != NULL) {
        WORD rInd = TableNr(c);
        LPDBRECORD r = c->rr->GetRecord(rInd);
        if (req->IsUpdateDone (r,i,req->oldP))
          r->RefreshJoin (req,i,NULL,0,req->oldP);
        }
      }
    }
  }

int NewRec_param::AnzElems(LPTABLEDEF td)
  {
  int res;
  if (td->IsInternTable()) res = td->GetAnzVars();
  else                     res = -1;
  return res;
  }

BOOL NewRec (mdiChild *c,LPVOID param,WORD mode)
  {
  WORD TableInd;
  if (mode & EM_LOAD) {
    NewRec_param FAR *par = (NewRec_param FAR *) param ;
    LPSTR Name = LPSTR (c->ReadlData (par->TableName));
    DBWIN_ASSERT (Name != NULL);
    TableInd = GetTableInd (c,Name);
    DBWIN_ASSERT (TableInd != 0xFFFF);
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(c->schd->TRef[TableInd-CSYSRECS].TableNr,c->schd->TRef[TableInd-CSYSRECS].Version);
    WIN_ASSERT (td->GetParentID() == 0);
    int AnzElems = par->AnzElems(td);
    LPDBRECORD n;
    if (AnzElems > 0) {     // Interne Tabelle
      par->req = InitializeRequest ("",AnzElems,DBCALLTYPE_STANDARDGET,c->DocumentID());
      par->SetRequest (c,td);
      par->req->BuildForeign ();
      n = new DBRecord(par->req);   // Mit Verweis auf die Teiltabellen
      }
    else {
      par->req = NULL ;     // Ansonsten keine besonderen Vorkommnisse mehr
      n = new DBRecord(td);
      }
    if (par->AnzKeySegs () > 0) {
      PrimKey k;
      BOOL alldone = TRUE ;
      for (int i = 0 ; i < par->AnzKeySegs () ; i++) {
        LPVOID Data = c->ReadlData (par->KeySeg[i]);
        if (Data != NULL)
          k.PushKeySeg (Data,GetBlockSize(Data));
        else
          alldone = FALSE ;
        }
      if (alldone)
        n->SetPrimKey (&k);
      }
    n->setLocked ();
    if (par->req != NULL)
      par->req->oldP = par->req->SaveOldParams (n);
    LPDBRECORD old = c->rr->GetRecord (TableInd);
    if ((old != NULL) && (n != old))
      ReplaceNextSame (c,TableInd,old,n);
    c->rr->SetRec (n,TableInd,c->DocumentID(),TRUE);
    }
  if (mode & EM_UPDATE) {
    NewRec_param FAR *par = (NewRec_param FAR *) param ;
    if (par->req != NULL) {
      par->ExtUpdate (c);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    NewRec_param FAR *par = (NewRec_param FAR *) param ;
    if (par->req != NULL) {
      par->ExtConnections (TableInd,c,TRUE);
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    NewRec_param FAR *par = (NewRec_param FAR *) param ;
    LPSTR Name = LPSTR (c->ReadlData (par->TableName));
    DBWIN_ASSERT (Name != NULL);
    TableInd = GetTableInd (c,Name);
    if (par->req != NULL) {
      par->ExtConnections (TableInd,c,FALSE);
      par->req->ClearForeign();
      par->req->FreeTableDefs();
      FreeRequest (par->req);
      }
    GetTableAdmin()->FreeTable(c->schd->TRef[TableInd-CSYSRECS].TableNr,c->schd->TRef[TableInd-CSYSRECS].Version);
    }
  return FALSE ;
  }

// Ermittlung der Adresse eines Records fuer Mehrfachverwendung ohne Daten-
// bankzugriffe, 
// ACHTUNG: Datensatz darf keinen Update kriegen...
///////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR GetRecordPtr_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  DWORD Updates[1];
  int AnzUpdates()
    { return (parSize - (sizeof(*this) - sizeof(Updates[0]))) / sizeof(Updates[0]) ; }
  };
#pragma pack()

BOOL GetRecordPtr (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetRecordPtr_param FAR *par = (GetRecordPtr_param FAR *) param ;
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    DBWIN_ASSERT (TableName != NULL);
    WORD TableInd = GetTableInd (c,TableName);
    DBWIN_ASSERT (TableInd != 0xFFFF);
    LPDBRECORD rec = c->rr->GetRecord (TableInd);
    c->WritelData (par->res,&rec,sizeof(rec),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetRecordPtr_param FAR *par = (GetRecordPtr_param FAR *) param ;
    for ( int i = 0 ; i < par->AnzUpdates () ; i ++ )
      c->SetlConnection (par->Updates[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetRecordPtr_param FAR *par = (GetRecordPtr_param FAR *) param ;
    for ( int i = 0 ; i < par->AnzUpdates () ; i ++ )
      c->ClearlConnection (par->Updates[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR GetRecPrimKey_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  };
#pragma pack()

BOOL GetRecPrimKey (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetRecPrimKey_param FAR *par = (GetRecPrimKey_param FAR *) param;
    LPSTR TableName = LPSTR (c->ReadlData (par->TableName));
    DBWIN_ASSERT (TableName != NULL);
    WORD TableInd = GetTableInd (c,TableName);
    DBWIN_ASSERT (TableInd != 0xFFFF);
    LPDBRECORD rec = c->rr->GetRecord (TableInd);
    if (rec->GetPrimKey()->Data != NULL)
      c->WritelData (par->res,rec->GetPrimKey()->Data,GetBlockSize(rec->GetPrimKey()->Data),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetRecPrimKey_param FAR *par = (GetRecPrimKey_param FAR *) param;
    c->SetlConnection (par->TableName,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetRecPrimKey_param FAR *par = (GetRecPrimKey_param FAR *) param;
    c->ClearlConnection (par->TableName,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// Setzen eines Records, dessen Adresse schon bekannt ist
///////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR ReUseRecord_param {
  WORD parSize;
  DWORD ptr;
  DWORD TableName;
  BOOL UseOtherTable ()
    { return (parSize == sizeof(*this)) ; }
  };
#pragma pack()

BOOL ReUseRecord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ReUseRecord_param FAR *par = (ReUseRecord_param FAR *) param;
    LPDBRECORD FAR *rec = (LPDBRECORD FAR *) (c->ReadlData (par->ptr));
    DBWIN_ASSERT (rec != NULL);
    if (*rec != NULL) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef((*rec)->GetTableID(),(*rec)->GetVersion());
      WIN_ASSERT (td->GetParentID() == 0);
      WORD TableInd ;
      if (par->UseOtherTable())
        TableInd = GetTableInd (c,LPSTR(c->ReadlData (par->TableName)));
      else
        TableInd = GetTableInd (c,td->GetName());
      DBWIN_ASSERT (TableInd != 0xFFFF);
      GetTableAdmin()->FreeTable((*rec)->GetTableID(),(*rec)->GetVersion());
      if ((*rec)->IsUsedBy(DWORD(c->rr) + TableInd)) {
        // Die Kurzversion
        WIN_ASSERT (*rec == c->rr->GetRecord (TableInd));
        // c->rr->SetRecord (TableInd,*rec) ;
        }
      else {
        LPDBRECORD old = c->rr->GetRecord (TableInd);
        if ((old != NULL) && (*rec != old))
          ReplaceNextSame (c,TableInd,old,*rec);
        // Die Vollversion, Daten sind noch nicht geladen
        c->rr->SetRec (*rec,TableInd,c->DocumentID(),FALSE) ;

        LPDBRECORD used = c->rr->GetRecord (TableInd);
        if (c->rr->PrevInKontext[TableInd].rr == NULL) { 
                // Nur dann updaten, wenn es sich wirklich um einen 'Ausgangsdatensatz handelt'
          for ( LPRRR r = c->rr->NextInKontext + TableInd ; r->rr != NULL ; r = r->rr->NextInKontext + r->tnr ) {
            r->rr->SetRecord (r->tnr,used);
            used->Update (r->rrOwner->DocumentID());
            }
          }
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    ReUseRecord_param FAR *par = (ReUseRecord_param FAR *) param;
    c->SetlConnection (par->ptr,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ReUseRecord_param FAR *par = (ReUseRecord_param FAR *) param;
    c->ClearlConnection (par->ptr,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

// Verhindern von Updates fuer ein Record
///////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR AvoidUpdates_param {
  WORD parSize;
  DWORD ptr;
  };
#pragma pack()

BOOL AvoidUpdates (mdiChild *c,LPVOID param,WORD mode)
  {
  AvoidUpdates_param FAR *par = (AvoidUpdates_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPDBRECORD FAR *rec = (LPDBRECORD FAR *) (c->ReadlData (par->ptr));
    DBWIN_ASSERT (rec != NULL);
    if (*rec != NULL)
      (*rec)->AvoidUpdates();
    }
  if (mode & EM_FIXCONNECTION)
    c->SetlConnection (par->ptr,LPSTR(param)-sizeof(WORD));
  if (mode & (EM_CLEAR | EM_RESET))
    c->ClearlConnection (par->ptr,LPSTR(param)-sizeof(WORD));
  return FALSE ;
  }

////////////////////////////////////////////////////////////////////
//  Callbackfunktionen, die von CTOOL aus gesetzt werden
////////////////////////////////////////////////////////////////////
DLLExport LPVOID _export WINAPI SetTableContext (LPVOID CallBackData,WORD TableInd,LPVOID recAddr)
  {
  LPVOID old = LPTBD(CallBackData)->c->rr->GetRecord (TableInd);
  LPTBD(CallBackData)->c->rr->SetRecord (TableInd,LPDBRECORD(recAddr)) ;
  return old ;
  }
DLLExport LPVOID _export WINAPI GetTableContext (LPVOID CallBackData,WORD TableInd)
  {
  return LPTBD(CallBackData)->c->rr->GetRecord (TableInd);
  }

#pragma pack(1)
struct SetDBLog_param {
  WORD  parSize;
  DWORD setLog;
  DWORD logFile;
  };
#pragma pack()

BOOL SetDBLogState (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL  bsetLog     = FALSE;
    LPSTR logFileName = NULL;
    SetDBLog_param FAR *par = (SetDBLog_param FAR *) param;
    DBINT FAR * lpbsetLog = (DBINT FAR *) c->ReadlData (par->setLog);
    if (lpbsetLog != NULL)
      bsetLog = *lpbsetLog;
    logFileName = LPSTR (c->ReadlData (par->logFile));
    SetDBLogState (bsetLog,logFileName);
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////////////////
//  Transaktionsfunktionen
////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct BinTransaction_param {
  WORD parSize;
  DWORD withLarge;
  };
#pragma pack()

BOOL BeginTransaction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL withLarge;
    BinTransaction_param FAR *par = (BinTransaction_param FAR *) param;
    if (par->parSize >= sizeof(*par)) {
      DBINT FAR * lpwithLarge = (DBINT FAR *) c->ReadlData (par->withLarge);
      if (lpwithLarge != NULL)
        withLarge = *lpwithLarge;
      else
        withLarge = FALSE;
      }
    else
      withLarge = FALSE;
    BeginTransaction (withLarge);
    }
  return FALSE ;
  }

#pragma pack(1)
extern DLLExport LPSTR _export FAR PASCAL LastErrorText ();
struct GetLastErrorText_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetLastErrorText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetLastErrorText_param FAR *par = (GetLastErrorText_param FAR *) param;
    LPSTR x = LastErrorText ();
    if (x != NULL)
      c->WritelData (par->res,x,lstrlen(x) + 1,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct InTransaction_param {
  WORD parSize;
  DWORD isInTransaction;
  };
#pragma pack()

extern BOOL _export FAR PASCAL InTransaction();
BOOL IsInTransactionProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InTransaction_param FAR *par = (InTransaction_param FAR *) param;
    DBBOOL myInTransaction = InTransaction();
    c->WritelData (par->isInTransaction,&myInTransaction,sizeof(myInTransaction),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


#pragma pack(1)
struct SetUserName_param {
  WORD parSize;
  DWORD userName;
  DWORD passWord;
  };
#pragma pack()

BOOL SetUserName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetUserName_param FAR *par = (SetUserName_param FAR *) param;
    LPSTR un = LPSTR (c->ReadlData (par->userName));
    LPSTR pw = LPSTR (c->ReadlData (par->passWord));
    if ((un != NULL) && (pw != NULL)) {
      (GetDLLAdmin()->GetDLLEntry (GetTransactionDLL()))->SetUserName (un,pw);
      }
    }
  return FALSE ;
  }

BOOL EndTransaction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    EndTransaction ();
    }
  return FALSE ;
  }

BOOL AbortTransaction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AbortTransaction ();
    }
  return FALSE ;
  }

#pragma pack(1)
struct IsUpdateDone_param {
  WORD parSize;
  DWORD res;
  DWORD TableName;
  };
#pragma pack()

BOOL IsUpdateDone (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    IsUpdateDone_param FAR *par = (IsUpdateDone_param FAR *) param;
    LPSTR TableName = LPSTR(c->ReadlData (par->TableName));
    DBWIN_ASSERT (TableName != NULL);
    WORD TableInd = GetTableInd (c,TableName);
    DBWIN_ASSERT (TableInd != 0xFFFF);
    LPDBRECORD rec = c->rr->GetRecord(TableInd);
    BOOL res = rec->IsUpdateDone ();
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct CopySameVars_param {
  WORD parSize;
  DWORD r1,r2;
  };
#pragma pack()

WORD GetRealTableId (LPDBRECORD r,WORD FAR *Version)
  {
  LPTABLEDEF t = NULL ;
  for (WORD i = 0 ; i < r->GetAnzVars() ; i++) {
    WORD j;
    LPTABLEDEF tx = r->GetTableDef (i,&j);
    if (t == NULL)         t = tx ;
    else if (t != tx)      return 0xFFFF ;
    if (i != j)            return 0xFFFF ;
    }
  if ((t != NULL) && (t->IsInternTable ())) {
    InternTable FAR *x = (InternTable FAR *) t->GetDLLDef() ;
    if (x->AnzTables == 1) {
      *Version = x->GetTableByNum(0)->tRef.Version;
      return x->GetTableByNum(0)->tRef.TableNr;
      }
    else {
      *Version = 0;
      return 0xFFFF ;
      }
    }
  *Version = t->GetVersion();
  return t->GetTableID();
  }
BOOL CopySameVars (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CopySameVars_param FAR *par = (CopySameVars_param FAR *) param;
    LPDBRECORD FAR *lpr1 = (LPDBRECORD FAR *) c->ReadlData (par->r1);
    LPDBRECORD FAR *lpr2 = (LPDBRECORD FAR *) c->ReadlData (par->r2);
    DBWIN_ASSERT (lpr1 != NULL);
    DBWIN_ASSERT (lpr2 != NULL);
    LPDBRECORD r1 = *lpr1,r2 = *lpr2;
    DBWIN_ASSERT (r1 != NULL);
    DBWIN_ASSERT (r2 != NULL);

    WORD rt1,V1,V2 ;
    if ((r1->GetAnzVars() == r2->GetAnzVars()) && 
        ((rt1 = GetRealTableId(r1,&V1)) != 0xFFFF) && 
        (rt1 == GetRealTableId(r2,&V2))) {
      // die Struktur der Datensaetze stimmt ueberein
      for (WORD i = 0 ; i < r1->GetAnzVars() ; i++) {
        LPVOID data = r2->Get (i);
        if (data != NULL)
          r1->Set (i,data,GetBlockSize(data),LPSTR(param)-sizeof(WORD));
        else
          r1->Del (i,LPSTR(param)-sizeof(WORD));
        }
      }
    else {
      for (WORD i = 0 ; i < r1->GetAnzVars() ; i++) {
        WORD v1,v2;
        LPTABLEDEF t1 = r1->GetTableDef (i,&v1);
        for (WORD j = 0 ; j < r2->GetAnzVars() ; j++) {
          LPTABLEDEF t2 = r2->GetTableDef (j,&v2);
          if ((v1 == v2) && (t1 == t2)) {
            LPVOID data = r2->Get (j);
            if (data != NULL)
              r1->Set (i,data,GetBlockSize(data),LPSTR(param)-sizeof(WORD));
            else
              r1->Del (i,LPSTR(param)-sizeof(WORD));
            break ;
            }
          }
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    CopySameVars_param FAR *par = (CopySameVars_param FAR *) param;
    c->SetlConnection (par->r1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->r2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CopySameVars_param FAR *par = (CopySameVars_param FAR *) param;
    c->ClearlConnection (par->r1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->r2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetNewFileRef_param {
  WORD parSize;
  DWORD oldName;
  DWORD newName;
  };
#pragma pack()

BOOL SetNewFileRef (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetNewFileRef_param FAR *par = (SetNewFileRef_param FAR *) param ;
    AddFileTranslation (c->DocumentID(),LPSTR(c->ReadlData (par->oldName)),LPSTR(c->ReadlData (par->newName)));
    }
  if (mode & EM_RESET) {
    SetNewFileRef_param FAR *par = (SetNewFileRef_param FAR *) param ;
    RemoveFileTranslation (c->DocumentID(),LPSTR(c->ReadlData (par->oldName))) ;
    }
  return FALSE ;
  }

