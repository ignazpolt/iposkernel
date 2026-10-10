///////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/inttable.cpv   1.6   26 Nov 1996 07:53:46   HANNES  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/inttable.cpv  $
// 
//    Rev 1.6   26 Nov 1996 07:53:46   HANNES
// Automatischer Update
// 
//    Rev 1.5   02 Feb 1996 10:42:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   24 Jan 1995 10:59:26   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.3   10 Jan 1995 17:29:34   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.2   09 Jan 1995 12:09:30   HANNES
// Debugger eingebaut
// 
//    Rev 1.1   17 Jul 1994 14:34:08   HANNES
// IsViewAllowed auch fuer Interne Tabellen
// 
//    Rev 1.0   24 Jun 1994 16:44:48   HANNES
// Neuuebernahme clinicum
///////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#define MODULENUM 89
#include "winass.hpp"

DLLExport int _export WINAPI AddTablePart (LPINTTABLE FAR *tbl,LPSTR TableName,BOOL checkOrder,BOOL doLock)
  {
  BOOL found;
  WORD Version;
  WORD nwTable = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
  if (found) {
    // Ueberpruefen, ob die noch nie verwendet wurde
    ////////////////////////////////////////////////
    if ((*tbl != NULL) && (!checkOrder)) {
      for (WORD i = 0 ; i < (*tbl)->AnzTables ; i++)
        if ((*tbl)->GetTableByNum(i,TRUE)->tRef.TableNr == nwTable)
          return ATP_ORDER;
      }
    WORD oSize ;
    if (*tbl != NULL) oSize = GetBlockSize (*tbl);
    else              oSize = sizeof(InternTable) - sizeof(_reft);
    LPINTTABLE n = LPINTTABLE (GetGlobMem (oSize + sizeof(_reft)));
    if (*tbl != NULL) lmemcpy (n,*tbl,oSize) , FreeGlobMem (*tbl);
    n->pTable[n->AnzTables].ptr = 
          LPPTABLE(GetGlobMem (sizeof(partTable) - sizeof(WORD)));
    LPPTABLE pt = n->GetTableByNum(n->AnzTables,TRUE);
    pt->tRef.TableNr = nwTable;
    pt->tRef.Version = Version;
    pt->td      = GetTableAdmin()->GetTableDef(nwTable,Version);
    pt->doLock  = doLock;
    n->AnzTables++;
    *tbl = n;
    return ATP_SUCCESS;
    }
  return ATP_TABLENOTFOUND;
  }

DLLExport void _export WINAPI CreateEmptyInternTable (LPINTTABLE FAR *tbl)
  {
  WIN_ASSERT (*tbl == NULL);
  *tbl = LPINTTABLE(GetGlobMem (sizeof(WORD)));
  (*tbl)->AnzTables = 0;
  }

DLLExport BOOL _export WINAPI InternTable::IsTableReferenced (LPSTR TableName)
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
  return ((AnzTables > 0) &&
          (GetTableByNum(AnzTables-1,TRUE)->tRef.TableNr == TableID));
  }

DLLExport int _export WINAPI InternTable::AddVar (LPSTR VarName,WORD DataType)
  {
  BOOL found;
  WORD dt;
  LPPTABLE pt = GetTableByNum(AnzTables-1,TRUE);
  WORD VarID  = pt->td->GetVarID (VarName,&dt,&found);
  if (found) {
    if (dt != DataType) return ATV_DATATYPE;
    LPPTABLE n = LPPTABLE (GetGlobMem (GetBlockSize(pt) + sizeof(WORD)));
    lmemcpy (n,pt,GetBlockSize(pt));  FreeGlobMem (pt);
    n->VarID[n->AnzVars] = VarID;
    n->AnzVars ++;
    pTable[AnzTables-1].ptr = n;
    return ATV_SUCCESS;
    }
  else
    return ATV_VARNOTFOUND;
  }

DLLExport LPINTTABLE _export WINAPI Pack (LPINTTABLE t,GLOBALHANDLE FAR *hGres,DWORD FAR *gSize)
  {
  WORD bSize = GetBlockSize (t);
  WORD Size = bSize;
  for (WORD i = 0 ; i < t->AnzTables ; i++)
    Size += GetBlockSize (t->GetTableByNum(i,TRUE));

  *hGres = GlobalAlloc (GMEM_MOVEABLE,Size);
  *gSize = Size;
  LPINTTABLE res = LPINTTABLE (GlobalLock (*hGres));
  lmemcpy (res,t,bSize);
  for (i = 0 ; i < res->AnzTables ; i++) {
    res->pTable[i].Offs = DWORD(bSize);
    LPPTABLE pt = LPPTABLE (LPSTR(res)+bSize);
    WORD aSize = GetBlockSize (t->GetTableByNum(i,TRUE));
    lmemcpy (pt,t->GetTableByNum(i,TRUE),aSize);
    pt->td = NULL;
    bSize += aSize;
    }
  return res;
  }

DLLExport void _export WINAPI Clear (LPINTTABLE t)
  {
  for (WORD i = 0 ; i < t->AnzTables ; i++) {
    LPPTABLE pt = t->GetTableByNum(i,TRUE);
    GetTableAdmin()->FreeTable (pt->tRef.TableNr,pt->tRef.Version);
    FreeGlobMem (pt);
    }
  FreeGlobMem (t);
  }

DLLExport LPVOID _export WINAPI Intern_DATADICT_TABLEDEF (LPVOID InitData,LPSTR TableString,BOOL FAR *error,DWORD FAR *size)
  {
  WIN_ASSERT(FALSE);
  return NULL;
  }

DLLExport void _export WINAPI Intern_DATADICT_FREETABLEDEF (LPVOID TableData)
  {
  }

DLLExport LPVOID _export WINAPI Intern_DATADICT_VARDEF (LPVOID InitData,WORD mType,LPVOID TableData,LPSTR VarString,BOOL FAR *error,DWORD FAR *size)
  {
  WIN_ASSERT(FALSE);
  return NULL;
  }

DLLExport void _export WINAPI Intern_DATADICT_FREEVARDEF (LPVOID VarData)
  {
  }

DLLExport WORD _export WINAPI Intern_DATADICT_GETMTYPE (LPVOID VarData)
  {
  return LPINTVARDESC(VarData)->mType;
  }

DLLExport LPACCESSLISTENTRY _export WINAPI Intern_DATADICT_GETACCESSLIST (LPVOID TableData)
  {
  LPINTTABLE Tb = LPINTTABLE(TableData);
  if (Tb->AnzTables > 0) {
    WORD Table0ID = Tb->GetTableByNum(0)->tRef.TableNr;
    WORD Table0Version = Tb->GetTableByNum(0)->tRef.Version;
    LPACCESSLISTENTRY res = GetTableAdmin()->GetTableDef(Table0ID,Table0Version)->GetAccessList () ;
    GetTableAdmin()->FreeTable(Table0ID,Table0Version);
    return res;
    }
  else
    return NULL;
  }

DLLExport void _export WINAPI Intern_DBRESET ()
  {
  }

DLLExport int _export WINAPI Intern_DBCALL (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  WIN_ASSERT(FALSE);
  return DBCALL_ERROR;
  }

DLLExport void _export WINAPI Intern_GETVARDESCEXTRA (LPVOID VarData,LPSTR txt,WORD txtSize)
  {
  LPSTR TableName = LPSTR(LPINTVARDESC(VarData) + 1);
  LPSTR VarName = TableName + lstrlen(TableName) + 1;
  if ((*VarName) && (*TableName))
    wsprintf (txt,"%s from %s",VarName,TableName);
  else
    *txt = '\0';
  }

DLLExport BOOL _export WINAPI Intern_ISPRIMARY (LPVOID VarData)
  {
  return LPINTVARDESC(VarData)->IsPrimary;
  }

DLLExport void _export WINAPI InternTable::GetReqElem (LPREQELEM e,WORD VarID)
  {
  for (WORD i = 0 ; i < AnzTables ; i++) {
    LPPTABLE pt = GetTableByNum(i);
    if (pt->AnzVars > VarID) {
      e->TableNumber = WORD(i);
      e->VarID       = pt->VarID[VarID];
      return;
      }
    VarID -= pt->AnzVars;
    }
  WIN_ASSERT (FALSE);
  }

DLLExport BOOL _export WINAPI Intern_DATADICT_ISACCESSFORVIEW (LPVOID DLLData,LPSTR SelectionName)
  {
  LPINTTABLE Tb = LPINTTABLE(DLLData);
  if (Tb->AnzTables > 0) {
    WORD Table0ID = Tb->GetTableByNum(0)->tRef.TableNr;
    WORD Table0Version = Tb->GetTableByNum(0)->tRef.Version;
    BOOL res = GetTableAdmin()->GetTableDef(Table0ID,Table0Version)->IsViewAllowed (SelectionName);
    GetTableAdmin()->FreeTable(Table0ID,Table0Version);
    return res;
    }
  else
    return NULL;
  }

DLLExport BOOL _export WINAPI Intern_DATADICT_GETVARPROPERTY (LPVOID TableData,LPVOID VarData,WORD PropCmd,LPVOID PropData)
  {
  BOOL res = TRUE ;
  switch (PropCmd) {
    case VPROP_DATASIZE :
      *((int FAR *) (PropData)) = -1 ;
      break ;
    case VPROP_DATAID :
      *((int FAR *) (PropData)) = 0xFFFF ;
      break ;
    case VPROP_GETANZKEYSEGS :
      *((int FAR *) (PropData)) = 0 ;
      break ;
    default :
      res = FALSE ;
    }
  return res ;
  }
