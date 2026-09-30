/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/dllchild.cpv   1.32   29 Jun 1998 18:58:54   Hannes  $
// $Log:   P:/marille/clinicum/rev/dllchild.cpv  $
// 
//    Rev 1.32   29 Jun 1998 18:58:54   Hannes
// GetResFactor
// 
//    Rev 1.31   17 May 1998 17:51:56   Hannes
// ENTER -> Ohne Extradaten, kommend von Programmstelle mit Extradaten
// 
//    Rev 1.30   16 Jan 1998 15:27:18   Hannes
// Listenfarben
// 
//    Rev 1.29   12 Jan 1998 18:17:16   Hannes
// fOffs nach SetExtraData lassen...
// 
//    Rev 1.28   24 Oct 1997 08:37:22   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.27   11 Jul 1997 10:14:38   Hannes
// 
//    Rev 1.26   19 Feb 1997 12:22:16   Hannes
// 
//    Rev 1.25   26 Nov 1996 08:13:48   HANNES
// Automatischer Update
// 
//    Rev 1.24   21 Oct 1996 18:48:44   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.23   24 Mar 1996 12:08:36   HANNES
// mehrseitige cFields
// 
//    Rev 1.22   02 Feb 1996 10:36:00   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.21   24 Aug 1995 00:20:06   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.20   11 Jul 1995 12:47:12   HANNES
// Expressionoptimierung
// 
//    Rev 1.19   11 Jun 1995 10:10:04   MARTIN
// GetClock
// 
//    Rev 1.18   04 May 1995 18:38:32   HANNES
// 
//    Rev 1.17   12 Apr 1995 12:26:10   HANNES
// 
//    Rev 1.16   04 Apr 1995 18:59:08   HANNES
// 
//    Rev 1.15   04 Apr 1995 18:40:00   HANNES
// 
//    Rev 1.14   04 Apr 1995 12:10:00   HANNES
//  
// 
//    Rev 1.13   31 Mar 1995 13:09:38   HANNES
//  
// 
//    Rev 1.12   30 Mar 1995 11:32:58   GERHOLD
// No change.
// 
//    Rev 1.11   21 Mar 1995 16:20:52   HANNES
// 
//    Rev 1.10   20 Mar 1995 11:55:36   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.9   09 Jan 1995 12:14:30   HANNES
// Debugger eingebaut
// 
//    Rev 1.8   05 Dec 1994 17:42:50   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.7   15 Nov 1994 22:48:48   MARTIN
// Scanner...
// 
//    Rev 1.6   10 Nov 1994 14:28:38   HANNES
// LEAVE hinter einem return
// 
//    Rev 1.5   17 Oct 1994 15:04:20   HANNES
// GetExtradata... auf den DrawContext umgeschrieben
// 
//    Rev 1.4   11 Oct 1994 09:43:50   HANNES
// Einbau der Zoomrectfunktionen
// 
//    Rev 1.3   06 Oct 1994 19:25:48   HANNES
// Erweiterungen der Funktionen im Zusammenhang mit FrmTable
// 
//    Rev 1.2   20 Sep 1994 11:34:00   HANNES
// MultiProc Faehigkeit von Objekten
// 
//    Rev 1.1   27 Jun 1994 12:09:42   MARTIN
// Callback-Funktionen exportiert
// 
//    Rev 1.0   24 Jun 1994 19:30:40   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "dds32.h"
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "globmem.h"
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define DLLCHILD_MAIN
#include "dllchild.hpp"

#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "voronoi.hpp"
#include "frmobj.hpp"

#include "winextra.hpp"

#define MODULENUM   129
#include "winass.hpp"


DLLExport LPSCRIPTCONTENT _export WINAPI cb_schd(dllChild FAR *c)
  { return c->PrivData->schd; }
DLLExport HWND _export WINAPI cb_MyHandle(dllChild FAR *c)
  { return c->PrivData->OutWnd(); }
DLLExport void _export WINAPI cb_Get_scale(dllChild FAR *c, float FAR *sc)
  { *sc = c->PrivData->OutScale(); }
DLLExport int _export WINAPI cb_xp(dllChild FAR *c)
  { return c->PrivData->OutXp(); }
DLLExport int _export WINAPI cb_yp(dllChild FAR *c)
  { return c->PrivData->OutYp(); }
DLLExport int _export WINAPI cb_x0(dllChild FAR *c)
  { return c->PrivData->OutX0(); }
DLLExport int _export WINAPI cb_y0(dllChild FAR *c)
  { return c->PrivData->OutY0(); }
DLLExport int _export WINAPI cb_AnzSides(dllChild FAR *c)
  { return c->PrivData->DrawContext()->anzSides(); }
DLLExport int _export WINAPI cb_ActSide(dllChild FAR *c)
  { return c->PrivData->DrawContext()->actSide(); }
DLLExport DWORD _export WINAPI cb_SelColor(dllChild FAR *c)
  { return c->PrivData->DrawContext()->selColor(); }
DLLExport HPEN _export WINAPI cb_hActivePen(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->hActivePen; }
DLLExport HPEN _export WINAPI cb_hInactivePen(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->hInactivePen; }
DLLExport void _export WINAPI cb_GetDocInfo (dllChild FAR *c, int Cmd,DWORD fldId,LPVOID Buffer)
  { c->PrivData->GetDocInfo(Cmd, fldId, Buffer); }
DLLExport void _export WINAPI cb_Rescale (dllChild FAR *c, LPRECT rect)
  { c->PrivData->DrawContext()->Rescale(rect); }
DLLExport int _export WINAPI cb_WorldToLog (dllChild FAR *c, float val)
  { return c->PrivData->DrawContext()->WorldToLog(val); }
DLLExport void _export WINAPI cb_Get_LogToWorld (dllChild FAR *c, float FAR *ltw, int val)
  { *ltw = c->PrivData->DrawContext()->LogToWorld(val); }
DLLExport int _export WINAPI cb_HalfPenWidth (dllChild FAR *c, DWORD color)
  { return c->PrivData->DrawContext()->HalfPenWidth(color); }
DLLExport Printer FAR * _export WINAPI cb_Pr(dllChild FAR *c)
  { 
  if (c->PrivData->DrawContext()->GetOutData()->Pr == NULL)
    c->PrivData->DrawContext()->GetOutData()->Pr = GetPrinter (TRUE);
  return c->PrivData->DrawContext()->GetOutData()->Pr; 
  }
DLLExport int _export WINAPI cb_tabx(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->tabx; }
DLLExport GLOBALHANDLE _export WINAPI cb_Get_sli_res(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->sli.res; }
DLLExport int _export WINAPI cb_Get_sli_Ind(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->sli.Ind; }
DLLExport LPSTR _export WINAPI cb_Get_sli_actTxt(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->sli.actTxt; }
DLLExport void _export WINAPI cb_Set_sli_res(dllChild FAR *c, GLOBALHANDLE res)
  { c->PrivData->DrawContext()->GetOutData()->sli.res = res; }
DLLExport void _export WINAPI cb_Set_sli_Ind(dllChild FAR *c, int Ind)
  { c->PrivData->DrawContext()->GetOutData()->sli.Ind = Ind; }
DLLExport void _export WINAPI cb_Set_sli_actTxt(dllChild FAR *c, LPSTR actTxt)
  { c->PrivData->DrawContext()->GetOutData()->sli.actTxt = actTxt; }
DLLExport LPVOID _export WINAPI cb_ActScanPtr(dllChild FAR *c)
  { return c->PrivData->DrawContext()->GetOutData()->ActScanPtr; }
DLLExport void _export WINAPI cb_Set_ActScanPtr(dllChild FAR *c, LPVOID ActScanPtr)
  { c->PrivData->DrawContext()->GetOutData()->ActScanPtr = ActScanPtr; }

#define ENTER(A) if (BlockIsActive) { \
                   A ; \
                   } \
                 else { \
                   if (c->Extra != NULL) { \
                     SAVEREC old; \
                     c->PrivData->SetRecsForUpdate (old,c->Extra);  \
                     SetExtraInfo s(c->PrivData,c->Extra);        \
                     A ; \
                     c->PrivData->RestoreRecs(old); \
                     } \
                   else { \
                     LPCONNEXTRAINFO oldExtra = c->PrivData->_GetRecExtra(); \
                     c->PrivData->_SetRecExtra (NULL); \
                     RestoreListFnc rlf (c->PrivData);  \
                     A ; \
                     c->PrivData->_SetRecExtra (oldExtra); \
                     }  \
                   }
#define ENTER1(A) if (BlockIsActive) { \
                    A ; \
                    } \
                  else { \
                    if (c->Extra != NULL) { \
                      SAVEREC old; \
                      c->PrivData->SetRecsForUpdate (old,c->Extra);  \
                      SetExtraInfo s(c->PrivData,c->Extra);        \
                      c->PrivData->_GetRecExtra()->cmdBase = c->PrivData->GetCmdBase();     \
                      c->PrivData->_GetRecExtra()->cOffs = 0;     \
                      A ; \
                      c->PrivData->RestoreRecs(old); \
                      } \
                    else { \
                      LPCONNEXTRAINFO oldExtra = c->PrivData->_GetRecExtra(); \
                      c->PrivData->_SetRecExtra (NULL); \
                      RestoreListFnc rlf (c->PrivData);  \
                      A ; \
                      c->PrivData->_SetRecExtra (oldExtra); \
                      } \
                    }
DLLExport void _export WINAPI cb_ExCuteProc(dllChild FAR *c, DWORD Offset, WORD mode)
  { 
  BlockIsActive = FALSE ;
  ENTER1((c->PrivData->ExCuteProc(Offset, EM_LOAD | EM_CHANGETOTRUE) , 
         c->PrivData->ExCuteProc(Offset, EM_RESET)));
  }
DLLExport BOOL _export WINAPI cb_IsDocLocked (dllChild FAR *c, WORD RecType)
  { 
  BOOL res;
  ENTER(res = c->PrivData->IsDocLocked(RecType)); 
  return res ;
  }
DLLExport LPVOID _export WINAPI cb_GetDocumentExtraData (dllChild FAR *c, WORD Code,int FAR *size = NULL)
  { 
  switch (Code) {
    case DED_IMGBG :
    case DED_PALETTEINFO :
    case DED_MOUSESCALE :
    case DED_HELPLINELIST :
      return c->PrivData->DrawContext()->GetDocumentExtraData(Code, size); 
    default :
      return c->PrivData->GetDocumentExtraData(Code, size); 
    }
  }
DLLExport void _export WINAPI cb_PutDocumentExtraData (dllChild FAR *c, WORD Type,LPVOID Data,int size)
  { 
  switch (Type) {
    case DED_IMGBG :
    case DED_PALETTEINFO :
    case DED_MOUSESCALE :
    case DED_HELPLINELIST :
      c->PrivData->DrawContext()->PutDocumentExtraData(Type, Data, size);
      break ;
    default :
      c->PrivData->PutDocumentExtraData(Type, Data, size);
    }
  }
DLLExport void _export WINAPI cb_RemoveDocumentExtraData (dllChild FAR *c, WORD Type)
  { 
  switch (Type) {
    case DED_IMGBG :
    case DED_PALETTEINFO :
    case DED_MOUSESCALE :
    case DED_HELPLINELIST :
      c->PrivData->DrawContext()->RemoveDocumentExtraData(Type); 
      break ;
    default :
      c->PrivData->RemoveDocumentExtraData(Type); 
    }
  }
DLLExport void _export WINAPI cb_NextField (dllChild FAR *c)
  { 
  c->PrivData->NextField(); 
  }
DLLExport void _export WINAPI cb_PrevField (dllChild FAR *c)
  { 
  c->PrivData->PrevField(); 
  }
DLLExport void _export WINAPI cb_CreateGaussWin(dllChild FAR *c)
  { 
  c->PrivData->CreateGaussWin(); 
  }
DLLExport void _export WINAPI cb_ShowGauss (dllChild FAR *c, double FAR *val,double FAR *norm,double FAR *dev,int AnzRec,LPSTR caption)
  { 
  c->PrivData->ShowGauss(val, norm, dev, AnzRec, caption); 
  }
DLLExport GLOBALHANDLE _export WINAPI cb_GetGaussPar (dllChild FAR *c, double FAR *val,double FAR *norm,double FAR *dev,int AnzRun)
  { 
  return c->PrivData->GetGaussPar(val, norm, dev, AnzRun); 
  }
DLLExport void _export WINAPI cb_CloseGauss (dllChild FAR *c)
  { 
  c->PrivData->CloseGauss(); 
  }
DLLExport LPVOID _export WINAPI cb_ReadlData (dllChild FAR *c, DWORD DataRef)
  { 
  LPVOID res;
  ENTER (res = c->PrivData->ReadlData(DataRef));
  return res;
  }
DLLExport void _export WINAPI cb_WritelData (dllChild FAR *c, DWORD DataRef,LPVOID data,int size,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
  { 
  ENTER (c->PrivData->WritelData(DataRef, data, size, Cmd, UpdateSystem)); 
  }
DLLExport void _export WINAPI cb_SetlConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { 
  ENTER (c->PrivData->SetlConnection(DataRef, Cmd)); 
  }
DLLExport void _export WINAPI cb_SetlOtherConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { 
  DBWIN_ASSERT (FALSE);
  }
DLLExport void _export WINAPI cb_ClearlConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { 
  ENTER (c->PrivData->ClearlConnection(DataRef, Cmd)); 
  }
DLLExport void _export WINAPI cb_ClearlOtherConnection (dllChild FAR *c, DWORD DataRef,LPVOID Cmd)
  { 
  DBWIN_ASSERT (FALSE);
  }
DLLExport void _export WINAPI cb_DellData (dllChild FAR *c, DWORD DataRef,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
  { 
  ENTER (c->PrivData->DellData(DataRef, Cmd, UpdateSystem)); 
  }
DLLExport BOOL _export WINAPI cb_IsUpdatelFromEle (dllChild FAR *c, DWORD DataRef)
  { 
  BOOL res;
  ENTER (res = c->PrivData->IsUpdatelFromEle(DataRef)); 
  return res ;
  }
DLLExport void _export WINAPI cb_DestroySchiebeLehre (dllChild FAR *c)
  { ((Form *)c->PrivData)->DestroySchiebeLehre(); }
DLLExport void _export WINAPI cb_SetUpSchiebeLehre (dllChild FAR *c)
  { ((Form *)c->PrivData)->SetUpSchiebeLehre(); }
DLLExport int _export WINAPI cb_GetObjSide (dllChild FAR *c, FrmObject FAR *obj)
  { return obj->ErsteSeite(); }
DLLExport FrmObject FAR * _export WINAPI cb_act_obj(dllChild FAR *c)
  {
  if (((FrmObjectList FAR *) (c->PrivData->OutList()))->act != NULL)
    return ((FrmObjectList FAR *) (c->PrivData->OutList()))->act->obj;
  else
    return NULL;
  }
DLLExport void _export WINAPI cb_SetActiveExplicit (dllChild FAR *c, FrmObject FAR *obj)
  { 
  ((FrmObjectList FAR *) (c->PrivData->OutList()))->SetActiveExplicit(obj); 
  }
DLLExport FrmObject FAR * _export WINAPI cb_GetObjectFromPar(dllChild FAR *c, LPVOID param)
  { 
  return GetObjectFromPar(param, c->PrivData); 
  }
DLLExport int _export WINAPI cb_UpdateEleCount(dllChild FAR *c)
  { 
  return UpdateEleCount(); 
  }
extern void EmptyUpdateList();
DLLExport void _export WINAPI cb_EmptyUpdateList(dllChild FAR *c)
  { 
  EmptyUpdateList(); 
  }
DLLExport void _export WINAPI cb_SetCaretShown(dllChild FAR *c)
  { 
  SetCaretShown(); 
  }
DLLExport void _export WINAPI cb_SetNoCaret(dllChild FAR *c)
  { 
  SetNoCaret(); 
  }
DLLExport void _export WINAPI cb_SetStatus(dllChild FAR *c, LPSTR hlp)
  { 
  PrgStat.SetStatus(hlp); 
  }
DLLExport LPTABLEDEF _export WINAPI cb_GetTableDef(dllChild FAR *c,LPSTR Name,WORD FAR *TableInd)
  {
  WORD tid,Version;
  int TableNr = GetTableNr (c->PrivData->schd,&tid,&Version,Name);
  if (TableNr > 0) {
    *TableInd = WORD (TableNr);
    return GetTableAdmin()->GetTableDef(tid,Version);
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }
DLLExport DWORD _export WINAPI cb_GetDocumentID(dllChild FAR *c)
  {
  return c->PrivData->DocumentID();
  }
DLLExport LPDBRECORD _export WINAPI cb_SetRecord(dllChild FAR *c,LPDBRECORD r,WORD TableInd)
  {
  LPDBRECORD old = c->PrivData->rr->GetRecord (TableInd);
  c->PrivData->rr->SetRecord (TableInd,r);
  return old;
  }
DLLExport void _export WINAPI cb_FreeTableDef(dllChild FAR *c,LPTABLEDEF td)
  {
  GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
  }
DLLExport int _export WINAPI cb_GetVarSize (dllChild FAR *c, DWORD DataRef)
  { 
  int res;
  ENTER (res = c->PrivData->GetVarSize(DataRef));
  return res;
  }
DLLExport int _export WINAPI cb_GetConstInt (dllChild FAR *c, DWORD DataRef)
  { 
  int res;
  ENTER (res = c->PrivData->ReadConstInt(DataRef));
  return res;
  }

DLLExport LONG _export WINAPI cb_GetConstLong (dllChild FAR *c, DWORD DataRef)
  { 
  LONG res;
  ENTER (res = c->PrivData->ReadConstLong(DataRef));
  return res;
  }

DLLExport void _export WINAPI cb_GetConstFloat (dllChild FAR *c, DWORD DataRef,float FAR *res)
  { 
  ENTER (*res = c->PrivData->ReadConstFloat(DataRef));
  }

DLLExport void _export WINAPI cb_Bringtotail (dllChild FAR *c,LPVOID obj)
  {
  ((FrmObjectList FAR *) (c->PrivData->OutList()))->BringToTail ((FrmObject FAR *) obj);
  }

DLLExport LONG _export WINAPI cb_GetClock (dllChild FAR *c)
  { 
  return clock();
  }

DLLExport WORD _export WINAPI cb_GetMType (dllChild FAR *c,DWORD DataRef)
  {
  WORD res;
  ENTER (res = c->PrivData->GetDataType(DataRef));
  return res;
  }

inline void AssignProc(int fncind, FARPROC procaddr)
  {
  dcfunc[fncind] = DCCB_VOID_VOID(MakeProcInstance (procaddr,WBase::hInstance));
  }

void InitFrmObjDll(void)
  {
  AssignProc(DCFUNC_SCHD                 , FARPROC(cb_schd));
  AssignProc(DCFUNC_MYHANDLE             , FARPROC(cb_MyHandle));
  AssignProc(DCFUNC_GET_SCALE            , FARPROC(cb_Get_scale));
  AssignProc(DCFUNC_XP                   , FARPROC(cb_xp));
  AssignProc(DCFUNC_YP                   , FARPROC(cb_yp));
  AssignProc(DCFUNC_X0                   , FARPROC(cb_x0));
  AssignProc(DCFUNC_Y0                   , FARPROC(cb_y0));
  AssignProc(DCFUNC_ANZSIDES             , FARPROC(cb_AnzSides));
  AssignProc(DCFUNC_ACTSIDE              , FARPROC(cb_ActSide));
  AssignProc(DCFUNC_SELCOLOR             , FARPROC(cb_SelColor));
  AssignProc(DCFUNC_HACTIVEPEN           , FARPROC(cb_hActivePen));
  AssignProc(DCFUNC_HINACTIVEPEN         , FARPROC(cb_hInactivePen));
  AssignProc(DCFUNC_GETDOCINFO           , FARPROC(cb_GetDocInfo));
  AssignProc(DCFUNC_RESCALE              , FARPROC(cb_Rescale));
  AssignProc(DCFUNC_WORLDTOLOG           , FARPROC(cb_WorldToLog));
  AssignProc(DCFUNC_GET_LOGTOWORLD       , FARPROC(cb_Get_LogToWorld));
  AssignProc(DCFUNC_HALFPENWIDTH         , FARPROC(cb_HalfPenWidth));
  AssignProc(DCFUNC_PR                   , FARPROC(cb_Pr));
  AssignProc(DCFUNC_TABX                 , FARPROC(cb_tabx));
  AssignProc(DCFUNC_GET_SLI_RES          , FARPROC(cb_Get_sli_res));
  AssignProc(DCFUNC_GET_SLI_IND          , FARPROC(cb_Get_sli_Ind));
  AssignProc(DCFUNC_GET_SLI_ACTTXT       , FARPROC(cb_Get_sli_actTxt));
  AssignProc(DCFUNC_SET_SLI_RES          , FARPROC(cb_Set_sli_res));
  AssignProc(DCFUNC_SET_SLI_IND          , FARPROC(cb_Set_sli_Ind));
  AssignProc(DCFUNC_SET_SLI_ACTTXT       , FARPROC(cb_Set_sli_actTxt));
  AssignProc(DCFUNC_ACTSCANPTR           , FARPROC(cb_ActScanPtr));
  AssignProc(DCFUNC_SET_ACTSCANPTR       , FARPROC(cb_Set_ActScanPtr));
  AssignProc(DCFUNC_EXCUTEPROC           , FARPROC(cb_ExCuteProc));
  AssignProc(DCFUNC_ISDOCLOCKED          , FARPROC(cb_IsDocLocked));
  AssignProc(DCFUNC_GETEXTRADATA         , FARPROC(cb_GetDocumentExtraData));
  AssignProc(DCFUNC_PUTEXTRADATA         , FARPROC(cb_PutDocumentExtraData));
  AssignProc(DCFUNC_REMOVEEXTRADATA      , FARPROC(cb_RemoveDocumentExtraData));
  AssignProc(DCFUNC_NEXTFIELD            , FARPROC(cb_NextField));
  AssignProc(DCFUNC_PREVFIELD            , FARPROC(cb_PrevField));
  AssignProc(DCFUNC_CREATEGAUSSWIN       , FARPROC(cb_CreateGaussWin));
  AssignProc(DCFUNC_SHOWGAUSS            , FARPROC(cb_ShowGauss));
  AssignProc(DCFUNC_GETGAUSSPAR          , FARPROC(cb_GetGaussPar));
  AssignProc(DCFUNC_CLOSEGAUSS           , FARPROC(cb_CloseGauss));
  AssignProc(DCFUNC_READLDATA            , FARPROC(cb_ReadlData));
  AssignProc(DCFUNC_WRITELDATA           , FARPROC(cb_WritelData));
  AssignProc(DCFUNC_SETLCONNECTION       , FARPROC(cb_SetlConnection));
  AssignProc(DCFUNC_SETLOTHERCONNECTION  , FARPROC(cb_SetlOtherConnection));
  AssignProc(DCFUNC_CLEARLCONNECTION     , FARPROC(cb_ClearlConnection));
  AssignProc(DCFUNC_CLEARLOTHERCONNECTION, FARPROC(cb_ClearlOtherConnection));
  AssignProc(DCFUNC_DELLDATA             , FARPROC(cb_DellData));
  AssignProc(DCFUNC_ISUPDATEFROMELE      , FARPROC(cb_IsUpdatelFromEle));
  AssignProc(DCFUNC_DESTROYSCHIEBELEHRE  , FARPROC(cb_DestroySchiebeLehre));
  AssignProc(DCFUNC_SETUPSCHIEBELEHRE    , FARPROC(cb_SetUpSchiebeLehre));
  AssignProc(DCFUNC_GETOBJSIDE           , FARPROC(cb_GetObjSide));
  AssignProc(DCFUNC_ACT_OBJ              , FARPROC(cb_act_obj));
  AssignProc(DCFUNC_SETACTIVEEXPLICIT    , FARPROC(cb_SetActiveExplicit));
  AssignProc(DCFUNC_GETOBJECTFROMPAR     , FARPROC(cb_GetObjectFromPar));
  AssignProc(DCFUNC_UPDATEELECOUNT       , FARPROC(cb_UpdateEleCount));
  AssignProc(DCFUNC_EMPTYUPDATELIST      , FARPROC(cb_EmptyUpdateList));
  AssignProc(DCFUNC_SETCARETSHOWN        , FARPROC(cb_SetCaretShown));
  AssignProc(DCFUNC_SETNOCARET           , FARPROC(cb_SetNoCaret));
  AssignProc(DCFUNC_SETSTATUS            , FARPROC(cb_SetStatus));
  AssignProc(DCFUNC_GETTABLEDEF          , FARPROC(cb_GetTableDef));
  AssignProc(DCFUNC_DOCUMENTID           , FARPROC(cb_GetDocumentID));
  AssignProc(DCFUNC_SETRECORD            , FARPROC(cb_SetRecord));
  AssignProc(DCFUNC_FREETABLEDEF         , FARPROC(cb_FreeTableDef));
  AssignProc(DCFUNC_GETVARSIZE           , FARPROC(cb_GetVarSize));
  AssignProc(DCFUNC_GETCONSTINT          , FARPROC(cb_GetConstInt));
  AssignProc(DCFUNC_GETCONSTLONG         , FARPROC(cb_GetConstLong));
  AssignProc(DCFUNC_GETCONSTFLOAT        , FARPROC(cb_GetConstFloat));
  AssignProc(DCFUNC_BRINGTOTAIL          , FARPROC(cb_Bringtotail));
  AssignProc(DCFUNC_GETCLOCK             , FARPROC(cb_GetClock));
  AssignProc(DCFUNC_GETMTYPE             , FARPROC(cb_GetMType));

  InitFrmObjLib(WBase::hFrameWin, WBase::hInstance, dcfunc);
  }

