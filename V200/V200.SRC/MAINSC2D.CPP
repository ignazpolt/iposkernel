/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/mainsc2d.cpv   1.4   10 Jun 1996 10:09:18   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/mainsc2d.cpv  $
// 
//    Rev 1.4   10 Jun 1996 10:09:18   GERHOLD
// pragma pack
// 
//    Rev 1.3   02 Feb 1996 10:36:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   20 Mar 1995 12:04:32   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.1   17 Oct 1994 15:05:56   HANNES
// Korrektur von Fehlern, die sich bei der Umstellung eingeschlichen haben
// 
//    Rev 1.0   24 Jun 1994 19:30:48   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"

#include "printer.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "cutcont.hpp"

/*-----------------------------------------------------------------*/
/*           Skalierung von Punkten fuer Durchzeichnungen          */
/*-----------------------------------------------------------------*/

#pragma pack(1)
struct BringToHor_param {
  WORD ParSize;
  // Parameter - Daten
  WORD ScR,ScI;         // Referenz auf die Skalierungsmatrix
  WORD pt1R,pt1I;       // Referenz auf den 1. Punkt
  WORD pt2R,pt2I;       // -"-              2.
  WORD fctR,fctI;       // Referenz auf den Skalierungsfaktor
  };
#pragma pack()

BOOL uBringToHor (mdiChild *c,void FAR *param,WORD mode)
  {
  BringToHor_param FAR *par = (BringToHor_param FAR *) param;
  fpt FAR *p1,FAR *p2;
  float FAR *fact;
  tr2 sc;
  double xf;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Ermitteln der Referenzpunkte
    p1 = (fpt FAR *) c->ReadData (par->pt1R,par->pt1I);
    p2 = (fpt FAR *) c->ReadData (par->pt2R,par->pt2I);
    if (par->ParSize == sizeof (BringToHor_param)) {
      fact = (float FAR *) c->ReadData (par->fctR,par->fctI);
      }
    else
      fact = NULL ;
    // Berechnung der Skalierungsmatrix
    if ((p1 != NULL) && (p2 != NULL)) {
      CalcSc2d (&sc,p1,p2,FALSE);
      if (fact != NULL) {
        if (*fact >= 1.0)
          xf = 1.0 / *fact ;
        else
          xf = 1.0 ;            // keine Verkleinerungen !!!
        Stretch2d (&sc,xf);
        }
      // Skalierungsmatrix speichern
      c->WriteData (par->ScR,par->ScI,&sc,sizeof (sc),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->ScR,par->ScI,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->pt1R,par->pt1I,cmdOffset);
    c->SetConnection (par->pt2R,par->pt2I,cmdOffset);
    if (par->ParSize == sizeof (BringToHor_param))
      c->SetConnection (par->fctR,par->fctI,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->pt1R,par->pt1I,cmdOffset);
    c->ClearConnection (par->pt2R,par->pt2I,cmdOffset);
    if (par->ParSize == sizeof (BringToHor_param))
      c->ClearConnection (par->fctR,par->fctI,cmdOffset);
    }

  return FALSE ;
  }


/*-----------------------------------------------------------*/
/*              Skalieren eines Punktes                      */
/*-----------------------------------------------------------*/
#pragma pack(1)
struct ScPt_param {
  WORD ParSize;
  // Parameter Daten
  WORD dPtR,dPtI;
  WORD sPtR,sPtI;
  WORD scR,scI; 
  };
#pragma pack()

BOOL uScPt (mdiChild *c,void FAR *param,WORD mode)
  {
  ScPt_param FAR *par = (ScPt_param FAR *) param ;
  fpt FAR *src,dest;
  tr2 FAR *scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    src = (fpt FAR *) c->ReadData (par->sPtR,par->sPtI);
    scale = (tr2 FAR *) c->ReadData (par->scR,par->scI);
    // Skalieren des Punktes
    if ((scale != NULL) && (src != NULL) && (src->x < float (1.0E9))) {
      Sc2d (scale,&dest,src);
      c->WriteData (par->dPtR,par->dPtI,&dest,sizeof(dest),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else 
      c->DelData (par->dPtR,par->dPtI,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->sPtR,par->sPtI,cmdOffset);
    c->SetConnection (par->scR,par->scI,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->sPtR,par->sPtI,cmdOffset);
    c->ClearConnection (par->scR,par->scI,cmdOffset);
    }

  return FALSE ;
  }


/*-----------------------------------------------------------*/
/*              Skalieren einer Kontur                       */
/*-----------------------------------------------------------*/
#pragma pack(1)
struct ScCont_param {
  WORD ParSize ;
  // Parameter - Daten
  WORD dCtR,dCtI;
  WORD sCtR,sCtI;
  WORD scR,scI; 
  };
#pragma pack()

BOOL uScCont (mdiChild *c,void FAR *param,WORD mode)
  {
  ScCont_param FAR *par = (ScCont_param FAR *) param ;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    fpt FAR *src = (fpt FAR *)c->ReadData(par->sCtR,par->sCtI);
    tr2 FAR *scale = (tr2 FAR *)c->ReadData(par->scR,par->scI);
    // Skalieren der Kontur
    if ((scale != NULL) && (src != NULL)) {
      int siz = GetBlockSize(src);
      fpt FAR *dest = (fpt FAR *)GetGlobMem(siz);
      lmemcpy(dest, src, siz);
      int count;
      fpt FAR *pts = get_cont(dest, &count);
      count = (siz - (LPSTR(pts) - LPSTR(dest))) / sizeof(fpt);
      for (int i = 0; i < count; i++)
        Sc2d(scale, pts + i, pts + i);
      c->WriteData(par->dCtR, par->dCtI, dest, siz, cmdOffset, (mode & (EM_UPDATE | EM_CHANGETOTRUE)) != 0);
      FreeGlobMem(dest);
      }
    else
      c->DelData(par->dCtR, par->dCtI, cmdOffset, (mode & (EM_UPDATE | EM_CHANGETOTRUE)) != 0);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->sCtR, par->sCtI, cmdOffset);
    c->SetConnection(par->scR, par->scI, cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->sCtR, par->sCtI, cmdOffset);
    c->ClearConnection(par->scR, par->scI, cmdOffset);
    }

  return FALSE ;
  }


/*-----------------------------------------------------------*/
/*              Skalieren eines Konturteiles                 */
/*-----------------------------------------------------------*/
#pragma pack(1)
struct ScContPart_param {
  WORD ParSize ;
  // Parameter - Daten
  WORD dCtR,dCtI;
  WORD sCtR,sCtI;
  WORD scR,scI; 
  WORD pnR,pnI;
  };
#pragma pack()

BOOL uScContPart (mdiChild *c,void FAR *param,WORD mode)
  {
  ScContPart_param FAR *par = (ScContPart_param FAR *) param ;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    fpt FAR *src = (fpt FAR *)c->ReadData(par->sCtR,par->sCtI);
    tr2 FAR *scale = (tr2 FAR *)c->ReadData(par->scR,par->scI);
    LONG FAR *part_num = (LONG FAR *)c->ReadData(par->pnR,par->pnI);
    // Skalieren der Kontur
    if ((scale != NULL) && (src != NULL) && (part_num != NULL)) {
      int siz = GetBlockSize(src);
      fpt FAR *dest = (fpt FAR *)GetGlobMem(siz);
      lmemcpy(dest, src, siz);
      int count;
      fpt FAR *pts = get_cont(dest, &count);
      if ((!is_cut(dest)) || (*part_num < 0)) {
        count = (siz - (LPSTR(pts) - LPSTR(dest))) / sizeof(fpt);
        for (int i = 0; i < count; i++)
          Sc2d(scale, pts + i, pts + i);
        }
      else {
        LPCUTCONT cc = LPCUTCONT(dest);
        LPCONTPART part = LPCONTPART(cc + 1);
        for (short partn = 0; partn < cc->num_parts; partn++) {
          if (part->part_num == (short)(*part_num)) {
            LPCONTPIECE piece = LPCONTPIECE(part + 1);
            for (short piecen = 0; piecen < part->num_pieces; piecen++) {
              for (short ind = piece->ptind_from; ind <= piece->ptind_to; ind++)
                Sc2d(scale, pts + ind, pts + ind);
              piece++;
              }
            break;
            }
          part = LPCONTPART(LPCONTPIECE(part + 1) + part->num_pieces);
          }
        }
      c->WriteData(par->dCtR, par->dCtI, dest, siz, cmdOffset, (mode & (EM_UPDATE | EM_CHANGETOTRUE)) != 0);
      FreeGlobMem(dest);
      }
    else {
      c->DelData(par->dCtR, par->dCtI, cmdOffset, (mode & (EM_UPDATE | EM_CHANGETOTRUE)) != 0);
      }
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->sCtR, par->sCtI, cmdOffset);
    c->SetConnection(par->scR, par->scI, cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->sCtR, par->sCtI, cmdOffset);
    c->ClearConnection(par->scR, par->scI, cmdOffset);
    }

  return FALSE ;
  }


/*------------------------------------------------------*/
/*      Daten zur Ueberlagerung bringen                 */
/*------------------------------------------------------*/
#pragma pack(1)
struct BringToOverlap_param {
  WORD ParSize;
  // Parameter
  WORD scR,scI;
  WORD pt1nR,pt1nI;
  WORD pt2nR,pt2nI;
  WORD pt1oR,pt1oI;
  WORD pt2oR,pt2oI;
  WORD fR,fI;
  };
#pragma pack()

BOOL BringToOverlap (mdiChild *c,void FAR *param,WORD mode,int NrCmp)
  {
  BringToOverlap_param FAR *par = (BringToOverlap_param FAR *) param ;
  fpt FAR *p1n,FAR *p2n,FAR *p1o,FAR *p2o;
  float FAR *fact;
  tr2 scale,sc1,sc2;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);
  double xf ;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    p1n = (fpt FAR *) c->ReadData (par->pt1nR,par->pt1nI);
    p2n = (fpt FAR *) c->ReadData (par->pt2nR,par->pt2nI);
    p1o = (fpt FAR *) c->ReadData (par->pt1oR,par->pt1oI);
    p2o = (fpt FAR *) c->ReadData (par->pt2oR,par->pt2oI);
    if (par->ParSize == sizeof (BringToOverlap_param))
      fact = (float FAR *) c->ReadData (par->fR,par->fI);
    else
      fact = NULL ;

    // Berechnen des Skalierungsmatrix
    if ((p1n != NULL) && (p2n != NULL) && (p1o != NULL) && (p2o != NULL)) {
      CalcSc2d (&sc1,p1n,p2n);
      if (fact != NULL) {
        if (*fact >= 0.01)
          xf = 1.0 / *fact ;
        Stretch2d (&sc1,xf) ;
        }
      CalcSc2d (&sc2,p1o,p2o);
      InvSc2d (&sc2);
      Combine2d (&scale,&sc1,&sc2);
      // daten noch setzen
      c->WriteData (par->scR,par->scI,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->scR,par->scI,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);

    // fertig
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->pt1nR,par->pt1nI,cmdOffset);
    c->SetConnection (par->pt2nR,par->pt2nI,cmdOffset);
    c->SetConnection (par->pt1oR,par->pt1oI,cmdOffset);
    c->SetConnection (par->pt2oR,par->pt2oI,cmdOffset);
    if (par->ParSize == sizeof (BringToOverlap_param))
      c->SetConnection (par->fR,par->fI,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->pt1nR,par->pt1nI,cmdOffset);
    c->ClearConnection (par->pt2nR,par->pt2nI,cmdOffset);
    c->ClearConnection (par->pt1oR,par->pt1oI,cmdOffset);
    c->ClearConnection (par->pt2oR,par->pt2oI,cmdOffset);
    if (par->ParSize == sizeof (BringToOverlap_param))
      c->ClearConnection (par->fR,par->fI,cmdOffset);
    }

  return FALSE ;
  }

BOOL uBringToOverlap (mdiChild *c,void FAR *param,WORD mode)
  {
  return BringToOverlap (c,param,mode,0);
  }


#pragma pack(1)
struct LinTrans_param {
  WORD ParSize;
  // Parameter
  WORD scR,scI;         // Skalierungsmatrix
  WORD ptR,ptI;         // Ursprung
  WORD dxR,dxI;         // dx
  WORD dyR,dyI;         // dy
  WORD phiR,phiI;       // phi (in Grad...)
  };
#pragma pack()

BOOL uLinTrans (mdiChild *c,void FAR *param,WORD mode)
  {
  LinTrans_param FAR *par = (LinTrans_param FAR *) param ;
  fpt FAR *p0;
  float FAR *dx,FAR *dy,FAR *phi;
  tr2 scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    p0 = (fpt FAR *)    c->ReadData (par->ptR,par->ptI  );
    dx = (float FAR *)  c->ReadData (par->dxR,par->dxI  );
    dy = (float FAR *)  c->ReadData (par->dyR,par->dyI  );
    phi = (float FAR *) c->ReadData (par->phiR,par->phiI);

    // Berechnen des Skalierungsmatrix
    if ((p0 != NULL) && (dx != NULL) && (dy != NULL) && (phi != NULL)) {
      CalcLinTrans (&scale,p0,*dx,*dy,*phi);
      // daten noch setzen
      c->WriteData (par->scR,par->scI,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->scR,par->scI,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);

    // fertig
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->ptR,par->ptI,cmdOffset);
    c->SetConnection (par->dxR,par->dxI,cmdOffset);
    c->SetConnection (par->dyR,par->dyI,cmdOffset);
    c->SetConnection (par->phiR,par->phiI,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->ptR,par->ptI,cmdOffset);
    c->ClearConnection (par->dxR,par->dxI,cmdOffset);
    c->ClearConnection (par->dyR,par->dyI,cmdOffset);
    c->ClearConnection (par->phiR,par->phiI,cmdOffset);
    }

  return FALSE ;
  }


// Skalierungsmatrx explizit angeben
////////////////////////////////////////////////////////////
#pragma pack(1)
struct ScExplicit_param {
  WORD ParSize;
  // Parameter
  WORD scR,scI;         // Skalierungsmatrix
  WORD pt1R,pt1I;         // 1. Vektor
  WORD pt2R,pt2I;         // 2. Vektor
  WORD pt3R,pt3I;         // 3. Vektor
  };
#pragma pack()

BOOL uScExplicit (mdiChild *c,void FAR *param,WORD mode)
  {
  ScExplicit_param FAR *par = (ScExplicit_param FAR *) param ;
  fpt FAR *p1;
  fpt FAR *p2;
  fpt FAR *p3;
  tr2 scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    p1 = (fpt FAR *) c->ReadData (par->pt1R,par->pt1I);
    p2 = (fpt FAR *) c->ReadData (par->pt2R,par->pt2I);
    p3 = (fpt FAR *) c->ReadData (par->pt3R,par->pt3I);

    // Berechnen des Skalierungsmatrix
    if ((p1 != NULL) && (p2 != NULL) && (p3 != NULL)) {
      scale.A[0][0] = p1->x;
      scale.A[1][0] = p1->y;
      scale.A[0][1] = p2->x;
      scale.A[1][1] = p2->y;
      scale.B[0] = p3->x;
      scale.B[1] = p3->y;
      // daten noch setzen
      c->WriteData (par->scR,par->scI,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->scR,par->scI,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);

    // fertig
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->pt1R,par->pt1I,cmdOffset);
    c->SetConnection (par->pt2R,par->pt2I,cmdOffset);
    c->SetConnection (par->pt3R,par->pt3I,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->pt1R,par->pt1I,cmdOffset);
    c->ClearConnection (par->pt2R,par->pt2I,cmdOffset);
    c->ClearConnection (par->pt3R,par->pt3I,cmdOffset);
    }

  return FALSE ;
  }


// Zusammenhaengen zweier Skalierungsmatrizen
////////////////////////////////////////////////////////////

#pragma pack(1)
struct uCombineScale_param {
  WORD parSize;
  WORD rRec,rId;
  WORD s1Rec,s1Id;
  WORD s2Rec,s2Id;
  };
#pragma pack()

BOOL uCombineScale (mdiChild *c,void FAR *param,WORD mode) 
  {
  uCombineScale_param FAR *par = (uCombineScale_param FAR *) param ;
  tr2 FAR *s1,FAR *s2;
  tr2 scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    s1 = (tr2 FAR *) c->ReadData (par->s1Rec,par->s1Id);
    s2 = (tr2 FAR *) c->ReadData (par->s2Rec,par->s2Id);

    // Berechnen des Skalierungsmatrix
    if ((s1 != NULL) && (s2 != NULL)) {
      Combine2d (&scale,s1,s2);
      // daten noch setzen
      c->WriteData (par->rRec,par->rId,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else 
      c->DelData (par->rRec,par->rId,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
    // fertig
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection (par->s1Rec,par->s1Id,cmdOffset);
    c->SetConnection (par->s2Rec,par->s2Id,cmdOffset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->s1Rec,par->s1Id,cmdOffset);
    c->ClearConnection (par->s2Rec,par->s2Id,cmdOffset);
    }

  return FALSE ;
  }

// Invertieren einer Skalierungsmatrix
////////////////////////////////////////////////////////////
#pragma pack(1)
struct uInvScale_param {
  WORD parSize;
  WORD rRec,rId;
  WORD sRec,sId;
  };
#pragma pack()

BOOL uInvScale (mdiChild *c,void FAR *param,WORD mode) 
  {
  uInvScale_param FAR *par = (uInvScale_param FAR *) param ;
  tr2 FAR *s;
  tr2 scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    s = (tr2 FAR *) c->ReadData (par->sRec,par->sId);

    // Berechnen des Skalierungsmatrix
    if (s != NULL) {
      scale = *s;
      InvSc2d (&scale);
      // daten noch setzen
      c->WriteData (par->rRec,par->rId,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->rRec,par->rId,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
    // fertig
    }

  if (mode & EM_FIXCONNECTION)
    c->SetConnection (par->sRec,par->sId,cmdOffset);

  if (mode & (EM_CLEAR | EM_RESET))
    c->ClearConnection (par->sRec,par->sId,cmdOffset);

  return FALSE ;
  }

// Bilden einer Skalierungsmatrix ohne Offset
////////////////////////////////////////////////////////////
#pragma pack(1)
struct uScSkipOffset_param {
  WORD parSize;
  WORD rRec,rId;
  WORD sRec,sId;
  };
#pragma pack()

BOOL uScSkipOffset (mdiChild *c,void FAR *param,WORD mode) 
  {
  uScSkipOffset_param FAR *par = (uScSkipOffset_param FAR *) param ;
  tr2 FAR *s;
  tr2 scale;
  LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);

  if (mode & (EM_LOAD | EM_UPDATE)) {
    // Lesen der Daten
    s = (tr2 FAR *) c->ReadData (par->sRec,par->sId);

    // Berechnen des Skalierungsmatrix
    if (s != NULL) {
      scale = *s;
      scale.B[0] = scale.B[1] = float(0.0);
      // daten noch setzen
      c->WriteData (par->rRec,par->rId,&scale,sizeof (scale),cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
      }
    else
      c->DelData (par->rRec,par->rId,cmdOffset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) != 0);
    // fertig
    }

  if (mode & EM_FIXCONNECTION)
    c->SetConnection (par->sRec,par->sId,cmdOffset);

  if (mode & (EM_CLEAR | EM_RESET))
    c->ClearConnection (par->sRec,par->sId,cmdOffset);

  return FALSE ;
  }

//      Berechnung einer Skalierungsmatrix, die die X - Koordinaten
//      umdreht
//////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct uGetNegX_param {
  WORD par_size;
  WORD sRec,sId;
  };
#pragma pack()

BOOL uGetNegX (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & EM_LOAD) {
    tr2 scale;
    scale.B[0] = scale.B[1] = float (0.0);
    scale.A[0][1] = 
    scale.A[1][0] = float (0.0);
    scale.A[1][1] = float (1.0);
    scale.A[0][0] = - float (1.0);
    uGetNegX_param FAR *p = (uGetNegX_param FAR *) param ;
    LPSTR cmdOffset = LPSTR(param) - sizeof(WORD);
    c->WriteData (p->sRec,p->sId,&scale,sizeof (scale),cmdOffset);
    }
  return FALSE ;
  }

BOOL uOverlapPoints (mdiChild *c,void FAR *param,WORD mode)
  {
  return BringToOverlap (c,param,mode,-1);
  }

