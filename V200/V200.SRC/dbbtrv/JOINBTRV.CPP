//////////////////////////////////////////////////
//  Zusammenbasteln der Requests fuer den Join
//////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/dbbtrv/rev/joinbtrv.cpv   1.13   28 Apr 1998 16:24:02   Hannes  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/joinbtrv.cpv  $
// 
//    Rev 1.13   28 Apr 1998 16:24:02   Hannes
// [0] -> [j]
// 
//    Rev 1.12   27 May 1997 11:26:04   Hannes
// Uebernahme von Blobs in den gejointen Datensatz
// 
//    Rev 1.11   26 Nov 1996 08:00:16   HANNES
// Automatischer Update
// 
//    Rev 1.10   17 Jun 1996 15:38:32   HANNES
// Einbau von BLOBS
// 
//    Rev 1.9   04 Feb 1996 21:42:04   HANNES
// No change.
// 
//    Rev 1.8   04 Feb 1996 15:37:58   HANNES
// 
//    Rev 1.7   02 Feb 1996 10:42:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   24 Feb 1995 11:14:28   HANNES
//  
// 
//    Rev 1.5   16 Feb 1995 12:46:20   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.4   31 Oct 1994 10:37:04   hannes
// Statt DBRecord::Set DBRecord::Initialize aufgerufen
// 
//    Rev 1.3   05 Aug 1994 17:08:12   HANNES
// 
//    Rev 1.2   17 Jul 1994 14:38:56   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.1   13 Jul 1994 21:22:36   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:43:22   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 90
#include "winass.hpp"
#include "tbkw.h"
#include "tbfnc.hpp"
#include "dbrecord.hpp"
#include "btrieve.hpp"
#include "opbtrv.hpp"

BOOL IsNullValue (LPVOID key)
  {
  WORD s = GetBlockSize(key);
  for (WORD i = 0 ; i < s ; i++)
    if (LPSTR(key)[i] != '\0') return FALSE ;
  return TRUE ;
  }

BOOL IsNullAllowed (LPDBREQUEST req,LPTABLEDEF ti,LPCLRIDEF r)
  {
  WIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if ((req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->Property & VPROP_NOTNULL) == 0) return TRUE ;
    }
  return FALSE ;
  }

BOOL BtrStatement::SatisfyJoin (LPDBRECORD rec)
  {
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  BOOL res = TRUE ;
  for (WORD i = 1 ; ((i < req->AnzTables) && (res)) ; i++) {
    BOOL useOuter ;
    LPCLRIDEF r = ti->GetRIDef(i-1) ;
    switch (r->TypeOfJoin) {
      case CLJT_USEDEFAULT :
        useOuter = IsNullAllowed(req,ti,ti->GetRIDef(i-1));
        break ;
      case CLJT_USEINNERJOIN :
        useOuter = FALSE ;
        break ;
      case CLJT_USEOUTERJOIN :
        useOuter = TRUE ;
        break ;
      default :
        WIN_ASSERT (FALSE) ;
      }

    if (req->fdsc[i].freq == NULL) continue;
    LPVOID fKey    = rec->Get (req->fdsc[i].VarID[0]);
    WORD   fType   = rec->GetDataType (req->fdsc[i].VarID[0]);
    LPVOID sKey[3];
    WORD sType[3];
    for (WORD j = 0; j < 3 ; j++) {
      if (req->fdsc[i].VarID[j+1] != 0xFFFF) {
        sKey[j]  = rec->Get (req->fdsc[i].VarID[j+1]);
        sType[j] = rec->GetDataType (req->fdsc[i].VarID[j+1]);
        }
      else
        sKey[j] = NULL;
      }
    if ((fKey != NULL) && (!IsNullValue (fKey))) {
      // Einen Schluessel gibts, probieren wir mal weiter
      LPVOID nstmt = NULL;
      RecBuffer rn;
      lmemset (&rn,'\0',sizeof(rn));

      WORD dummy = 0xFFFF;
      req->fdsc[i].freq->SetParam(1,&dummy,sizeof(WORD));
      req->fdsc[i].freq->SetParam(2,fKey,GetBlockSize(fKey));
      req->fdsc[i].freq->SetParamType (2,fType);
      for (j = 0 ; j < 3 ; j++) {
        if (req->fdsc[i].VarID[j+1] != 0xFFFF) {
          if (sKey[j] != NULL) {
            req->fdsc[i].freq->SetParam(3+j,sKey[j],GetBlockSize(sKey[j]));
            req->fdsc[i].freq->SetParamType (3+j,sType[j]);
            }
          }
        else
          break ;
        }

      // Die restlichen parameter werden hinten angehaengen (Parameter 3 + AnzForeignSegs ist der erste davon)
      for (WORD m = 2 ; ((1 + j + m) < CB_PARAM) ; m++) {
        if (req->Param[m] != NULL) {
          req->fdsc[i].freq->SetParam (1+j+m,req->Param[m],GetBlockSize(req->Param[m]));
          req->fdsc[i].freq->SetParamType(1+j+m,req->ParamType[m]);
          }
        }

      int opCode = GetDLLAdmin()->GetDLLEntry(req->fdsc[i].freq->TableDef[0]->
            GetDLLHandle())->DBCall (DBOP_GET,1,req->fdsc[i].freq,&nstmt,&rn);
      // Statement wieder abbauen
      GetDLLAdmin()->GetDLLEntry(req->fdsc[i].freq->TableDef[0]->
            GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&nstmt,NULL);
      req->fdsc[i].freq->ClearParams ();

      if (opCode == DBCALL_SUCCESS) {
        // Resultat speichern
        if (req->AnzElems > 0) {
          for (int j = 0 ; j < req->fdsc[i].freq->AnzElems ; j++) {
            LPVOID data = rn.First()->rec[0]->Get (j);
            if (data != NULL) {
              rec->Initialize(req->fdsc[i].VarIndex[j],data,GetBlockSize(data));
              rn.First()->rec[0]->Del (j);
              }
            }
          }
        else {
          WIN_ASSERT(FALSE);
          }
        // Weiter Aufrauemarbeiten
        rn.Clear ();
        }
      else
        res = useOuter ;  // wenn useOuter, dann gut
      }
    else
      res = useOuter ;   // wenn useOuter , dann gut ...
    }
  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  return res;
  }

// Kaskadierendes Loeschen
///////////////////////////////
void BtrStatement::CallCascade (LPVOID key)
  {
  }

