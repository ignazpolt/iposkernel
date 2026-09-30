////////////////////////////////////////////////////
//  Dokumente in Dokumenten....
////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/frmobj/rev/sdoc.cpv   1.3   10 Jun 1996 10:12:44   GERHOLD  $
//  $Log:   P:/marille/clinicum/frmobj/rev/sdoc.cpv  $
// 
//    Rev 1.3   10 Jun 1996 10:12:44   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.2   02 Feb 1996 10:49:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Aug 1995 00:15:16   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.0   24 Jun 1994 16:45:50   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.9   19 Apr 1994 18:22:36   MARTIN
// SetActive -> SetActiveIf
// 
//    Rev 1.8   07 Feb 1994 18:11:20   HANNES
// mdiChild::base beim ExCutePrivateProc gesetzt
// 
//    Rev 1.7   04 Feb 1994 16:50:36   HANNES
// Verschiedene Kleinigkeiten mit den Mapping - Modi ausgemistet
// 
//    Rev 1.6   12 Jan 1994 11:12:10   HANNES
// unnoetige Includes eleminiert
// 
//    Rev 1.5   04 Jan 1994 16:57:38   HANNES
// FindIndex von Recall.cpp hierher verschoben
// Neue Druck - Parameter -> neue AbhÑngigkeiten fÅr CheckspaceOnSide
// 
//    Rev 1.4   09 Dec 1993 15:02:48   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.3   18 Oct 1993 19:56:34   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.2   15 Oct 1993 10:05:30   HANNES
// Fehlerkorrekturen in SetDocOrigion
// 
//    Rev 1.1   06 Oct 1993 09:51:30   HANNES
// Verbesserungen..
// 
//    Rev 1.0   04 Oct 1993 09:44:56   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "sdoc.hpp"
#define CARETHANDLING_DONE
#include "cfield.hpp"
#include "frmobj.hpp"
#define MODULENUM 45
#include "winass.hpp"
#include "winextra.hpp"

#include "recall.hpp"

extern HANDLE WBase_hFrameWin;

#ifdef SDOC
void sFormDoc::PrepareContext (PaintContext *pc)
  {
  if (parent->IsPrinting)
    pc->LogicalTwips (xp + pc->xvp,yp + pc->yvp,scale);
  else
    pc->LogicalTwips (xp,yp,scale);
  }

inline float LOFLOAT(DWORD x)
  {
  return float (int (LOWORD(x))) ;
  }

inline float HIFLOAT(DWORD x)
  {
  return float (int (HIWORD(x))) ;
  }

void LogToLog (fpt FAR *p1,fpt FAR *p2,PaintContext *pc1,PaintContext *pc2)
  {
  DWORD dw1ext = GetWindowExt (pc1->hDC);
  DWORD dv1ext = GetViewportExt (pc1->hDC);
  DWORD dw1org = GetWindowOrg (pc1->hDC);
  DWORD dv1org = GetViewportOrg (pc1->hDC);

  DWORD dw2ext = GetWindowExt (pc2->hDC);
  DWORD dv2ext = GetViewportExt (pc2->hDC);
  DWORD dw2org = GetWindowOrg (pc2->hDC);
  DWORD dv2org = GetViewportOrg (pc2->hDC);

  p2->x = float( (
      ((p1->x - LOFLOAT(dw1org)) * 
                  LOFLOAT(dv1ext)) / LOFLOAT(dw1ext) +
                     LOFLOAT(dv1org) - LOFLOAT(dv2org)
                 ) * LOFLOAT(dw2ext) / LOFLOAT(dv2ext) +
                       LOFLOAT(dw2org)
               );
  p2->y = float( (
      ((p1->y - HIFLOAT(dw1org)) * 
              HIFLOAT(dv1ext)) / HIFLOAT(dw1ext) +
                 HIFLOAT(dv1org) - HIFLOAT(dv2org)
                 ) * HIFLOAT(dw2ext) / HIFLOAT(dv2ext) +
                       HIFLOAT(dw2org)
               );
  }

void sFormDoc::LogToParentLog (fpt FAR *dest,fpt FAR *source)
  {
  PaintContext pcp,pcs;
  GetDocumentContext (&pcp,parent);
  GetDocumentContext (&pcs,this);

  LogToLog (source,dest,&pcs,&pcp);
  }

void sFormDoc::ParentLogToLog (fpt FAR *dest,fpt FAR *source)
  {
  PaintContext pcp,pcs;
  GetDocumentContext (&pcp,parent);
  GetDocumentContext (&pcs,this);

  LogToLog (source,dest,&pcp,&pcs);
  }

BOOL sFormDoc::ParentScaleChange (BOOL dorecalc)
  {
  scale = float (parent->scale);
  fpt FAR *pt = (fpt FAR *) GetExtraData (DED_DOCORIGIN);
  int xpn,ypn;
  if (pt != NULL) {
    POINT p;
    p.x = parent->WorldToLog (pt->x);
    p.y = parent->WorldToLog (pt->y);
    PaintContext pc;
    if (parent->IsPrinting) {
      pc.GetContext (parent->Pr);
      pc.LogicalTwips (parent->xp,parent->yp,parent->scale);
      }
    else
      GetDocumentContext (&pc,parent);
    LPtoDP (pc.hDC,&p,1);
    xpn = p.x ;
    ypn = p.y ;
    }
  else {
    xpn = parent->xp ;
    ypn = parent->yp ;
    }

  BOOL res;
  if ((xpn != xp) || (ypn != yp)) {
    xp = xpn ;
    yp = ypn ;
    if (Anchore != NULL)
      GetRectForParent (LPRECT (&(Anchore->obj->rcLogRect)),
                                            LPRECT(&rcLogRect)
                       );
    if (dorecalc)
      doAllParentTransforms ();
    res = TRUE ;
    }
  else
    res = FALSE ;
  return res;
  }

void sFormDoc::GetRectForParent (LPRECT dest,LPRECT source)
  {
  // Achtung: Logische Koordinaten des Vaters entsprechen nicht den
  // Logischen Koordinaten des Subformulares !
  fpt FAR *pt = (fpt FAR *) GetExtraData (DED_DOCORIGIN);
  fpt pt1;
  CopyRect (dest,source);
  if (pt != NULL) {
    fpt p0 = *pt;
    pt1.x = source->right - source->left ;
    pt1.y = source->bottom - source->top ;
    LogToParentLog (&pt1,&pt1);
    dest->left = parent->WorldToLog (p0.x);   dest->right  = int (pt1.x);
    dest->top  = parent->WorldToLog (p0.y);   dest->bottom = int (pt1.y);
    }
  }

void sFormDoc::Rescale (LPRECT rcr)
  {
  RECT rh;
  UnionRect (&rh,LPRECT(&rcLogRect),rcr);
  if (!lmemcmp (&rh,&rcLogRect,sizeof(RECT))) {
    CopyRect (LPRECT(&rcLogRect),&rh);
    GetRectForParent (LPRECT (&Anchore->obj->rcLogRect),LPRECT(&rcLogRect));
    parent->Rescale (LPRECT (&Anchore->obj->rcLogRect));
    }
  }

void SetPrgExtraData (WORD Type,mdiChild *cForRead,mdiChild *cForWrite,DWORD FAR *cData,int AnzCData)
  {
  SubBlock FAR *h = NULL;
  for (int i = 0 ; i < AnzCData ; i++) {
    LPVOID Data = cForRead->ReadlData (cData[i],0);
    if (Data != NULL) 
      h = Add (h,Data,i);
    }
  if (h != NULL) {
    cForWrite->PutExtraData (Type,h,GetBlockSize(h));
    FreeGlobMem (h);
    }
  }

void DocObject::SetCreationData ()
  {
  int AnzCData = (Par()->hd.par_Size - (sizeof (DocObject_par) - sizeof(DWORD))) / sizeof(DWORD);
  SetPrgExtraData (DED_SDOCDATA,c,SubDoc,Par()->cData,AnzCData);
  }

struct GetSDocData_param {
  WORD parSize;
  DWORD cData[1];
  };

#define MAXPTRS 128
LPSUBINFO FindIndex (LPSIARR si,WORD Ident,int AnzData)
  {
  for (int i = 0 ; i < AnzData ; i++) {
    if (si[i]->Ident == Ident)
      return si[i];
    }
  return NULL;
  }

BOOL GetPrgExtraData (WORD Type,mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetSDocData_param FAR *par = (GetSDocData_param FAR *) param;
    int AnzCData = int (par->parSize - sizeof (*par)) / sizeof(DWORD) + 1;
    LPSUBINFO si[MAXPTRS];
    SubBlock FAR *s = (SubBlock FAR *)c->GetExtraData (Type);
    int AnzData = (s != NULL) ? s->AnalyseSubBlock (si,MAXPTRS) :
                                0 ;
    DBWIN_ASSERT (AnzCData >= AnzData);
    for (int i = 0 ; i < AnzCData ; i++) {
      LPSUBINFO s = FindIndex (si,i,AnzData);
      if (s != NULL)
        c->WritelData (par->cData[i],c->RunNmbr,
                         s + 1,      // Daten befinden sich direkt dahinter
                         s->Length,
                         LPSTR(param)-sizeof(WORD),
                         FALSE
                      );
      else
        c->DellData (par->cData[i],c->RunNmbr,
                         LPSTR(param)-sizeof(WORD),
                         FALSE
                      );
      }
    }
  return FALSE ;
  }

BOOL GetSDocData (mdiChild *c,LPVOID param,WORD mode)
  {
  return GetPrgExtraData (DED_SDOCDATA,c,param,mode);
  }

struct SetDocOrigin_param {
  WORD parSize;
  DWORD ptOrg;
  DWORD docSide;
  };

BOOL SetDocOrigin (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetDocOrigin_param FAR *par = (SetDocOrigin_param FAR *) param;
    sFormDoc *s = (sFormDoc *) c;
    mdiChild *p = s->parent;

    // Setzen des richtigen Ursprungs (und der entsprechenden Seite)
    /////////////////////////////////////////////////////////////////
    fpt FAR *pt  = (fpt FAR *) c->ReadlData (par->ptOrg,c->RunNmbr);
    fpt FAR *opt = (fpt FAR *) c->GetExtraData (DED_DOCORIGIN);
    DBINT FAR *lpside = (DBINT FAR *) c->ReadlData (par->docSide,c->RunNmbr);
    int side = (lpside != NULL) ? *lpside : 0 ;
    if ((pt != NULL) && 
        ((opt == NULL) || (fabs(opt->x - pt->x) > 1.0E-3) || 
         (fabs(opt->y - pt->y) > 1.0E-3))) {
      c->PutExtraData (DED_DOCORIGIN,pt,sizeof(*pt));

      int oldside = ((sFormDoc *) c)->Anchore->Side;
      if ((s->Anchore != NULL) &&
          (s->Anchore->Side != side))
        ((FrmObjectList FAR *) c->ObjectList) -> ChangeSides 
            (side - s->Anchore->Side);
      s->Anchore->Side = side;

      RECT oldr;
      CopyRect (&oldr,LPRECT (&s->Anchore->obj->rcLogRect));
      BOOL doInvalidate = ((s->ParentScaleChange ()) ||
                                  (side != oldside));
      if ((mode & EM_UPDATE) && (doInvalidate) && 
                  (p->ActSide == oldside)) {
        RECT newr ;
        CopyRect (&newr,LPRECT (&s->Anchore->obj->rcLogRect));
        CopyRect (LPRECT (&s->Anchore->obj->rcLogRect),&oldr);
        s->Anchore->obj->Invalidate ();
        CopyRect (LPRECT (&s->Anchore->obj->rcLogRect),&newr);
        }
      if (doInvalidate)
        c->MapChanged();

      if ((mode & EM_UPDATE) && (doInvalidate) &&
              (p->ActSide == s->Anchore->Side))
        s->Anchore->obj->Invalidate ();
      }
    else {
      if ((opt == NULL) && (opt != NULL)) {
        if ((mode & EM_UPDATE) &&
            (p->ActSide == s->Anchore->Side))
          s->Anchore->obj->Invalidate ();
        c->RemoveExtraData (DED_DOCORIGIN);
        if (s->Anchore != NULL)
          s->Anchore->Side = side ;
        s->ParentScaleChange ();
        if ((mode & EM_UPDATE) &&
            (p->ActSide == s->Anchore->Side))
          s->Anchore->obj->Invalidate ();
        }
      }
    if ((mode & EM_UPDATE) &&
        (((FrmObjectList FAR *) p->ObjectList)->act->objdoc == c) &&
        (p->ActSide != side)) {
      p->ActSide = side;
      p->GetMinMax ();
      p->InitializeBars ();
      p->MapChanged ();
      InvalidateRect (p->MyHandle,NULL,TRUE);
      DWORD FAR *lpdsp = (DWORD FAR *) p->GetExtraData (DED_DOCSIDEPAR);
      if (lpdsp != NULL) {
        p->WritelData (*lpdsp,0,&side,sizeof(side),LPSTR(param)-sizeof(WORD));
        }
      }
    else if ((mode & EM_LOAD) && (p->ActSide != side)) {
      DWORD FAR *lpdsp = (DWORD FAR *) p->GetExtraData (DED_DOCSIDEPAR);
      p->ActSide = side;
      p->GetMinMax ();
      p->InitializeBars ();
      p->MapChanged ();
      InvalidateRect (p->MyHandle,NULL,TRUE);
      if (lpdsp != NULL) {
        p->WritelData (*lpdsp,0,&side,sizeof(side),LPSTR(param)-sizeof(WORD));
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetDocOrigin_param FAR *par = (SetDocOrigin_param FAR *) param;
    c->SetlConnection (par->ptOrg,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->docSide,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetDocOrigin_param FAR *par = (SetDocOrigin_param FAR *) param;
    c->ClearlConnection (par->ptOrg,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->docSide,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

struct GetParentKoord_param {
  WORD parSize;
  DWORD ParentPt;
  DWORD MyPt;
  };

LPVOID FAR *sFormDoc::GetTransformList (int FAR *Anz)
  {
  int size;
  LPVOID res = GetExtraData (DED_TRANSFORMDATA,&size);
  if (res != NULL)
    *Anz = size / sizeof(LPVOID);
  else
    *Anz = 0;
  return (LPVOID FAR *) res;
  }

void sFormDoc::PushToTransformList (LPVOID p)
  {
  int Anz;
  LPVOID FAR *old = GetTransformList (&Anz);
  LPVOID n = GetGlobMem ((Anz + 1)* sizeof(LPVOID));
  if (old != NULL)
    lmemcpy (n,old,Anz * sizeof(LPVOID));
  ((LPVOID FAR *)n)[Anz] = p;
  PutExtraData (DED_TRANSFORMDATA,n,GetBlockSize(n));

  FreeGlobMem (n);
  }

BOOL GetParentKoord (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetParentKoord_param FAR *par = (GetParentKoord_param FAR *) param;
    fpt FAR *pt = (fpt FAR *) c->ReadlData (par->MyPt,c->RunNmbr);
    // Koordinaten in einer Liste
    if (mode & EM_LOAD)
      // Alle Wichtigen Daten fuer den Mapchange vermerken
      ((sFormDoc *) c)->PushToTransformList (param);
    fpt FAR *nw = (fpt FAR *) c->ReadlData (par->ParentPt,c->RunNmbr);
    if (pt != NULL) {
      // logische Koordinaten in dem Dokument -> Koordinaten in einer Liste
      // mitfuerhren
      fpt r;
      ((sFormDoc *) c)->LogToParentLog (&r,pt);
      if ((nw == NULL) || (fabs(nw->x - r.x) > 1.0E-3) || (fabs(nw->y - r.y) > 1.0E-3))
        c->WritelData (par->ParentPt,c->RunNmbr,&r,sizeof(r),LPSTR(param)-sizeof(WORD));
      }
    else {
      if (nw != NULL)
        c->DellData (par->ParentPt,c->RunNmbr,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    GetParentKoord_param FAR *par = (GetParentKoord_param FAR *) param;
    c->SetlConnection (par->MyPt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    GetParentKoord_param FAR *par = (GetParentKoord_param FAR *) param;
    c->ClearlConnection (par->MyPt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

void sFormDoc::doAllParentTransforms ()
  {
  int Anz;
  LPVOID FAR *allpars = GetTransformList (&Anz);
  for (int i = 0 ; i < Anz ; i++)
    GetParentKoord (this,allpars[i],EM_UPDATE);
  }

BOOL GetDocRData (mdiChild *c,LPVOID param,WORD mode)
  {
  return GetPrgExtraData (DED_DOCRDATA,c,param,mode);
  }

BOOL SetDocRData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetSDocData_param FAR *par = (GetSDocData_param FAR *) param;
    int AnzCData = int (par->parSize - sizeof (*par)) / sizeof(DWORD) + 1;
    SetPrgExtraData (DED_DOCRDATA,c,((sFormDoc *) c)->parent,par->cData,AnzCData);
    }
  return FALSE ;
  }

struct doRepeatUntil_param {
  WORD parSize;
  GLOBALHANDLE hGBlocks;
  DWORD objPtr;
  DWORD doContinue;
  DWORD InitProc;
  DWORD NextProc;
  DWORD EndProc;
  DWORD EnlargeProc;
  DWORD BlockProc;
  };
typedef doRepeatUntil_param FAR *LPRUP;

struct ProcCollection {
  DWORD gesSize;
  WORD AnzProc;
  DWORD ProcSize;
  };
typedef ProcCollection FAR *LPPC;
typedef char _huge * HPSTR;
GLOBALHANDLE EnlargeBlocks (mdiChild *c,GLOBALHANDLE hGmem,DWORD procPtr)
  {
  LPSTR cmds = GlobalLock (c->commands);
  HPSTR base = HPSTR (cmds) + procPtr;
  DWORD ProcSize = *(DWORD FAR *) (base);
  LPPC p;
  if (hGmem == 0) {
    hGmem = GlobalAlloc (GMEM_MOVEABLE,sizeof(ProcCollection) + ProcSize);
    p = LPPC(GlobalLock (hGmem));
    p->gesSize = sizeof(*p);
    p->AnzProc = 0;
    p->ProcSize = ProcSize;
    }
  else {
    p = LPPC(GlobalLock (hGmem));
    DBWIN_ASSERT (p->ProcSize == ProcSize);
    DWORD nSize = p->gesSize + ProcSize;
    GlobalUnlock (hGmem);
    hGmem = GlobalReAlloc (hGmem,nSize,GMEM_MOVEABLE);
    p = LPPC(GlobalLock (hGmem));
    }
  hmemcpy (HPSTR(p) + p->gesSize,base,ProcSize);
  p->gesSize += ProcSize;
  p->AnzProc += 1;
  GlobalUnlock (hGmem);
  return hGmem;
  }

#define EXCUTE_ALLPROC    -2
#define EXCUTE_LASTPROC   -1
BOOL ExCutePrivateProc (mdiChild *c,WORD mode,GLOBALHANDLE hGmem,int ind)
  {
  LPPC p = LPPC (GlobalLock (hGmem));
  BOOL res = FALSE ;
  if (ind == EXCUTE_ALLPROC) {
    for (int i = 0 ; i < int (p->AnzProc) ; i++) {
      HPSTR base = HPSTR (p + 1) + LONG(i) * p->ProcSize;
      LPSTR oldBase = c->base;
      c->base = base;
      res = c->ExCuteBlock (LPSTR (base),0L,mode);
      c->base = oldBase;
      }
    }
  else {
    if (ind == EXCUTE_LASTPROC) ind = int (p->AnzProc - 1) ;
    HPSTR base = HPSTR (p + 1) + LONG(ind) * p->ProcSize;
    LPSTR oldBase = c->base;
    c->base = base;
    res = c->ExCuteBlock (LPSTR (base),0L,mode);
    c->base = oldBase;
    }
  return res;
  }

BOOL doRepeatUntil (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    doRepeatUntil_param FAR *par = (doRepeatUntil_param FAR *) param;
    for ( c->ExCuteProc (par->InitProc,EM_LOAD) ; ; ) {
      DBBOOL FAR *lpfound = (DBBOOL FAR *)
        c->ReadlData (par->doContinue,c->RunNmbr);
      DBWIN_ASSERT (lpfound != NULL);
      if (*lpfound) {
        par->hGBlocks = EnlargeBlocks (c,par->hGBlocks,par->BlockProc);
        ExCutePrivateProc (c,EM_LOAD,par->hGBlocks,EXCUTE_LASTPROC);
        c->ExCuteProc (par->NextProc,EM_LOAD) ;
        }
      else {
        c->ExCuteProc (par->EndProc,EM_LOAD) ;
        break ;
        }
      }
    // Zeiger auf Parameter - Daten in die Datenbank schreiben..
    c->WritelData (par->objPtr,c->RunNmbr,&param,sizeof(LPVOID),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_RESET) {
    doRepeatUntil_param FAR *par = (doRepeatUntil_param FAR *) param;
    if (par->hGBlocks) {
      ExCutePrivateProc (c,EM_RESET,par->hGBlocks,EXCUTE_ALLPROC);
      GlobalFree (par->hGBlocks);
      }
    par->hGBlocks = 0;
    }
  return FALSE;
  }

struct EnlargeBlocks_param {
  WORD parSize;
  DWORD objPtr;
  };

BOOL EnlargeBlocks (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & EM_LOAD) {
    EnlargeBlocks_param FAR *par = (EnlargeBlocks_param FAR *) param;
    LPRUP FAR *lppar = (LPRUP FAR *) c->ReadlData (par->objPtr,c->RunNmbr);
    DBWIN_ASSERT ((lppar != NULL) && (*lppar != NULL));
    // Enlarge - Procedur aufrufen...
    c->ExCuteProc ((*lppar)->EnlargeProc,EM_LOAD);
    // Block vergroessern, und aufrufen...
    (*lppar)->hGBlocks = EnlargeBlocks (c,(*lppar)->hGBlocks,(*lppar)->BlockProc);
    ExCutePrivateProc (c,EM_LOAD | EM_CHANGETOTRUE,(*lppar)->hGBlocks,EXCUTE_LASTPROC);
    // das war's auch schon
    c->ExCuteProc ((*lppar)->EndProc,EM_LOAD) ;
    }
  return FALSE ;
  }

BOOL ActiveSubDoc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPOBJDEF last = NULL ;
    for (LPOBJDEF hlp = ((FrmObjectList FAR *) (c->ObjectList))->head ; ; ) {
      if ((hlp->obj != NULL) && (hlp->obj->IsNodeObject()))
        last = hlp;
      hlp = hlp->NextObjDef;
      if (hlp == ((FrmObjectList FAR *) (c->ObjectList))->head) break ;
      }
    if (last != NULL) {
      ((FrmObjectList FAR *) (c->ObjectList))->DeactivateNode ();
      sFormDoc *s = ((DocObject FAR *) (last->obj))->SubDoc;
      ((FrmObjectList FAR *) (s->ObjectList))->FirstActive ();
      hlp = ((FrmObjectList FAR *) (s->ObjectList))->act;
      if (hlp != NULL) {
        hlp->obj->SetActiveIf(TRUE);
        ((FrmObjectList FAR *) (c->ObjectList))->act = hlp;
        }
      if (hlp->Side != c->ActSide) {
        c->ActSide = hlp->Side;
        c->GetMinMax ();
        c->InitializeBars ();
        c->MapChanged ();
        InvalidateRect (c->MyHandle,NULL,TRUE);
        DWORD FAR *lpdsp = (DWORD FAR *) c->GetExtraData (DED_DOCSIDEPAR);
        if (lpdsp != NULL) {
          c->WritelData (*lpdsp,c->RunNmbr,&hlp->Side,sizeof(hlp->Side),LPSTR(param)-sizeof(WORD));
          }
        }
      }
    }
  return FALSE ;
  }

struct CheckSpaceOnSide_param {
  WORD parSize;
  DWORD oldSide;
  DWORD newSide;
  DWORD oldPt;
  DWORD newPt;
  DWORD yHeight;
  DWORD defPt;
  DWORD DriverName;
  DWORD doLandscape;
  DWORD doPortrait;
  DWORD yTop,yBottom;
  };

BOOL CheckSpaceOnSide (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CheckSpaceOnSide_param FAR *par = (CheckSpaceOnSide_param FAR *) param;
    float FAR *lpyh = (float FAR *) c->ReadlData (par->yHeight,c->RunNmbr);
    fpt FAR *lppt   = (fpt FAR *) c->ReadlData (par->oldPt,c->RunNmbr);
    DBINT FAR *lpSide = (DBINT FAR *) c->ReadlData (par->oldSide,c->RunNmbr);
    fpt FAR *lpnewpt   = (fpt FAR *) c->ReadlData (par->newPt,c->RunNmbr);
    DBINT FAR *lpnewSide = (DBINT FAR *) c->ReadlData (par->newSide,c->RunNmbr);
    DBWIN_ASSERT ((lpyh != NULL) && (lppt != NULL) && (lpSide != NULL));
    // Berechnen der Papier - Hoehe
    Printer *Pr;
    if (c->IsSmallDoc ()) {
      if (((sFormDoc *) c)->parent->Pr == NULL) {
        ((sFormDoc *) c)->parent->Pr = GetPrinter (TRUE);
        ((sFormDoc *) c)->parent->Pr->PrinterIC();
        }
      Pr = ((sFormDoc *) c)->parent->Pr;
      }
    else {
      if (c->Pr == NULL) {
        c->Pr = GetPrinter (TRUE);
        c->Pr->PrinterIC();
        }
      Pr = c->Pr;
      }
    RECT r;
    Pr->PaperSize(&r);
    int yheight;
    {
    PaintContext pc(Pr);
    pc.Map (1.0);
    yheight = - pc.YPHYStoLOG (r.bottom - r.top);
    }
    float gheight = yheight / float (25.0); // Hoehe in mm
    float FAR *ytop = (float FAR *) c->ReadlData (par->yTop,c->RunNmbr);
    float FAR *ybottom = (float FAR *) c->ReadlData (par->yBottom,c->RunNmbr);
    if (ytop != NULL)
      gheight -= *ytop;
    if (ybottom != NULL)
      gheight -= *ybottom;
    gheight *= float (1440.0 / 25.403) ;  // Hoehe in log. Twips
    if (lppt->y + *lpyh < gheight) {
      // Vorhergesehen Position stimmt
      if ((lpnewpt == NULL) || (!lmemcmp (lppt,lpnewpt,sizeof(*lppt))))
        c->WritelData (par->newPt,c->RunNmbr,lppt,sizeof(*lppt),LPSTR(param)-sizeof(WORD));
      if ((lpnewSide == NULL) || (*lpnewSide != *lpSide))
        c->WritelData (par->newSide,c->RunNmbr,lpSide,sizeof(*lpSide),LPSTR(param)-sizeof(WORD));
      }
    else {
      // Verschiebung auf die naechste Seite
      fpt FAR *lpdpt = (fpt FAR *) c->ReadlData (par->defPt,c->RunNmbr);
      DBWIN_ASSERT (lpdpt != NULL);
      if ((lpnewpt == NULL) || (!lmemcmp (lpdpt,lpnewpt,sizeof(*lpdpt))))
        c->WritelData (par->newPt,c->RunNmbr,lpdpt,sizeof(*lpdpt),LPSTR(param)-sizeof(WORD));
      int nside = *lpSide + 1;
      if ((lpnewSide == NULL) || (*lpnewSide != nside))
        c->WritelData (par->newSide,c->RunNmbr,&nside,sizeof(nside),LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    CheckSpaceOnSide_param FAR *par = (CheckSpaceOnSide_param FAR *) param;
    c->SetlConnection (par->oldSide,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->oldPt,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yHeight,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yTop,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yBottom,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->doLandscape,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->doPortrait,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CheckSpaceOnSide_param FAR *par = (CheckSpaceOnSide_param FAR *) param;
    c->ClearlConnection (par->oldSide,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->oldPt,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yHeight,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yTop,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yBottom,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->DriverName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->doLandscape,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->doPortrait,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
#endif

