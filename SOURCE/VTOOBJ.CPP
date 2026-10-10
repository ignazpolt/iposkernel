/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/vtoobj.cpv   1.4   24 Mar 1996 12:09:36   HANNES  $
// $Log:   P:/marille/clinicum/rev/vtoobj.cpv  $
// 
//    Rev 1.4   24 Mar 1996 12:09:36   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 10:35:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:20:14   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Mar 1995 12:06:04   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 19:30:50   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "winass.hpp"
#define MODULENUM 113
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
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
#include "dllchild.hpp"

#include "dds.h"
#include "cfield.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "cubspl.hpp"
#include "cutedit.hpp"
#include "rotcent.hpp"

BOOL DefSoftEdit(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new SoftEditObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }


// die ganze Scheibe fuer die Speicherverwaltung

inline LPVOID mymalloc(size_t size)
  {
  return GetGlobMem(size);
  };


inline void myfree(LPVOID obj)
  {
  FreeGlobMem(obj);
  };


BOOL uCubSpl(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uCubSpl_param FAR *par = (uCubSpl_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    DBWIN_ASSERT(par->ParSize >= sizeof(uCubSpl_param));
    WORD numbps = par->ParSize - sizeof(uCubSpl_param);
    DBWIN_ASSERT((numbps % (6 * sizeof(Referenz))) == 0);
    LPCUBSPL cs = new CubSpl();
    numbps /= (6 * sizeof(Referenz));
    fpt FAR *p;
    float wp, wn, lp, ln;
    float FAR *dec;
    // erster Stuetzpunkt
    p = (fpt FAR *)(c->ReadData(par->fp[1].p.R, par->fp[1].p.I));
    DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
    dec = (float FAR *)(c->ReadData(par->fp[2].w.R, par->fp[2].w.I));
    if ((dec == NULL) || (*dec > 1.0E9)) {
      wn = ln = float(0.0);
      }
    else {
      wn = *dec;
      dec = (float FAR *)(c->ReadData(par->fp[3].l.R, par->fp[3].l.I));
      if ((dec == NULL) || (*dec > 1.0E9))
        ln = float(0.0);
      else
        ln = *dec;
      }
    cs->AddPt(c->ReadConstInt(par->fp[0].rm), p, float(0.0), wn, float(0.0), ln);
    // Stuetzpunkte in der Mitte
    for (WORD i = 0; i < numbps; i++) {
      dec = (float FAR *)(c->ReadData(par->fp[i*6+5].w.R, par->fp[i*6+5].w.I));
      if ((dec == NULL) || (*dec > 1.0E9)) {
        wp = lp = float(0.0);
        }
      else {
        wp = *dec;
        dec = (float FAR *)(c->ReadData(par->fp[i*6+4].l.R, par->fp[i*6+4].l.I));
        if ((dec == NULL) || (*dec > 1.0E9))
          lp = float(0.0);
        else
          lp = *dec;
        }
      p = (fpt FAR *)(c->ReadData(par->fp[i*6+7].p.R, par->fp[i*6+7].p.I));
      DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
      dec = (float FAR *)(c->ReadData(par->fp[i*6+8].w.R, par->fp[i*6+8].w.I));
      if ((dec == NULL) || (*dec > 1.0E9)) {
        wn = ln = float(0.0);
        }
      else {
        wn = *dec;
        dec = (float FAR *)(c->ReadData(par->fp[i*6+9].l.R, par->fp[i*6+9].l.I));
        if ((dec == NULL) || (*dec > 1.0E9))
          ln = float(0.0);
        else
          ln = *dec;
        }
      cs->AddPt(c->ReadConstInt(par->fp[i*6+6].rm), p, wp, wn, lp, ln);
      }
    // letzter Stuetzpunkt
    dec = (float FAR *)(c->ReadData(par->fp[i*6+5].w.R, par->fp[i*6+5].w.I));
    if ((dec == NULL) || (*dec > 1.0E9)) {
      wp = lp = float(0.0);
      }
    else {
      wp = *dec;
      dec = (float FAR *)(c->ReadData(par->fp[i*6+4].l.R, par->fp[i*6+4].l.I));
      if ((dec == NULL) || (*dec > 1.0E9))
        lp = float(0.0);
      else
        lp = *dec;
      }
    p = (fpt FAR *)(c->ReadData(par->fp[i*6+7].p.R, par->fp[i*6+7].p.I));
    DBWIN_ASSERT((p != NULL) && (p->x < 1.0E9));
    cs->AddPt(c->ReadConstInt(par->fp[i*6+6].rm), p, wp, float(0.0), lp, float(0.0));
    // jetzt noch Kontur berechnen und in die Datenbank schreiben
    cs->CalcAllDpDn();
    int ptCount = c->ReadConstInt (par->rPtCount);
    fpt FAR *hcnt = (fpt FAR *)mymalloc(ptCount * sizeof(fpt));
    cs->CalcCont(hcnt, ptCount);
    c->WriteData(par->cntR, par->cntI, hcnt, ptCount * sizeof(fpt), Offset);
    myfree(hcnt);
    delete cs;
    }

  if (mode & EM_FIXCONNECTION) {
    WORD numfree = par->ParSize - sizeof(uCubSpl_param);
    numfree = (numfree + sizeof(par->fp)) / sizeof(Referenz);
    for (WORD i = 0; i < numfree; i++)
      if ((i % 6) != 0)  // keine Connection fuer Modus
        c->SetConnection(par->fp[i].p.R, par->fp[i].p.I, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    WORD numfree = par->ParSize - sizeof(uCubSpl_param);
    numfree = (numfree + sizeof(par->fp)) / sizeof(Referenz);
    for (WORD i = 0; i < numfree; i++)
      if ((i % 6) != 0)  // keine Connection fuer Modus
        c->ClearConnection(par->fp[i].p.R, par->fp[i].p.I, Offset);
    }

  return FALSE ;
  }


BOOL ChangeCubSplPt(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  ChangeCubSplPt_param FAR *par = (ChangeCubSplPt_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSOFTEDITOBJ FAR *lpsoe = (LPSOFTEDITOBJ FAR *)c->ReadData(par->objR, par->objI);
    LPSOFTEDITOBJ soe;
    if ((lpsoe != NULL) && ((soe = *lpsoe) != NULL) && (soe->Initialized)) {
      // Stuetzpunkt suchen
      int i = 1;
      for (LPBASEPOINT bp = soe->cs->head; bp != NULL; bp = bp->next) {
        if ((soe->Par()->fp[i].p.I == par->optI) &&
            (soe->Par()->fp[i].p.R == par->optR))
          break;
        i += 6;
        }
      if (bp != NULL) {
        fpt FAR *lpnpt = (fpt FAR *)c->ReadData(par->nptR, par->nptI);
        if ((lpnpt != NULL) && (lpnpt->x < 1.0E9)) {
          soe->cs->ChangePt(bp,lpnpt);
          int UpdateMode = c->ReadConstInt (par->rUpdateMode);
          if (UpdateMode & 0x1L)
            soe->DoMove(c->actSide());
          if (UpdateMode & 0x2L) {
            int PtCount = c->ReadConstInt(soe->Par()->rPtCount);
            fpt FAR *hcnt = (fpt FAR *)mymalloc(PtCount * sizeof(fpt));
            soe->cs->CalcCont(hcnt, PtCount);
            c->WriteData(soe->Par()->cntR, soe->Par()->cntI, hcnt, PtCount * sizeof(fpt), 0);
            myfree(hcnt);
            }
          }
        }
      else {
        DBWIN_ASSERT(FALSE);
        }
      }
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->nptR, par->nptI, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->nptR, par->nptI, Offset);
    }

  return FALSE ;
  }


BOOL WriteCubSpl(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  WriteCubSpl_param FAR *par = (WriteCubSpl_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSOFTEDITOBJ FAR *lpsoe = (LPSOFTEDITOBJ FAR *)c->ReadData(par->objR, par->objI);
    LPSOFTEDITOBJ soe;
    if ((lpsoe != NULL) && ((soe = *lpsoe) != NULL) && (soe->Initialized)) {
      soe->DoMove(c->actSide());
      BOOL WriteCont = c->ReadConstInt (par->rWriteCont);
      if (WriteCont) {
        int PtCount = c->ReadConstInt (soe->Par()->rPtCount);
        fpt FAR *hcnt = (fpt FAR *)mymalloc(PtCount * sizeof(fpt));
        soe->cs->CalcCont(hcnt, PtCount);
        c->WriteData(soe->Par()->cntR, soe->Par()->cntI, hcnt, PtCount * sizeof(fpt), 0);
        myfree(hcnt);
        }
      }
    }

  return FALSE ;
  }


BOOL uCalcSoftVect(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uCalcSoftVect_param FAR *par = (uCalcSoftVect_param FAR *)param;
  int num_pars = ((par->ParSize - sizeof(uCalcSoftVect_param)) / sizeof(par->t[0])) + 1;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    fpt sum;
    sum.x = sum.y = float(0.0);
    for (int i = 0; i < num_pars; i++) {
      fpt FAR *lprefline = (fpt FAR *)c->ReadData(par->t[i].refR,par->t[i].refI);
      fpt FAR *lpscfact = (fpt FAR *)c->ReadData(par->t[i].scR,par->t[i].scI);
      fpt FAR *lpvect = (fpt FAR *)c->ReadData(par->t[i].srcR,par->t[i].srcI);
      fpt refline, scfact;
      if ((lprefline != NULL) && (lprefline->x < 1.0E9))
        refline = *lprefline;
      else
        refline.x = float(1.0), refline.y = float(0.0);
      if ((lpscfact != NULL) && (lpscfact->x < 1.0E9))
        scfact = *lpscfact;
      else
        scfact.x = scfact.y = float(1.0);
      if (lpvect != NULL) {
        float bxbx = refline.x * refline.x;
        float bxby = refline.x * refline.y;
        float byby = refline.y * refline.y;
        sum.x += (bxbx * scfact.x + byby * scfact.y) * lpvect->x;
        sum.x += (bxby * scfact.x - bxby * scfact.y) * lpvect->y;
        sum.y += (bxby * scfact.x - bxby * scfact.y) * lpvect->x;
        sum.y += (byby * scfact.x + bxbx * scfact.y) * lpvect->y;
        }
      }
    c->WriteData(par->dstR, par->dstI, &sum, sizeof(fpt), Offset);
    }

  if (mode & EM_FIXCONNECTION) {
    for (int i = 0; i < num_pars; i++) {
      c->SetConnection(par->t[i].refR, par->t[i].refI, Offset);
      c->SetConnection(par->t[i].scR,  par->t[i].scI,  Offset);
      c->SetConnection(par->t[i].srcR, par->t[i].srcI, Offset);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    for (int i = 0; i < num_pars; i++) {
      c->ClearConnection(par->t[i].refR, par->t[i].refI, Offset);
      c->ClearConnection(par->t[i].scR,  par->t[i].scI,  Offset);
      c->ClearConnection(par->t[i].srcR, par->t[i].srcI, Offset);
      }
    }

  return FALSE ;
  }

BOOL DefCutEdit(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new CutEditObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Vto_DefRotCent(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new RotCentObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

