/////////////////////////////////////////////////
//  Definitionen fuer Normwert - Berechnungen  //
/////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/normcalc.cpv   1.7   23 Mar 1998 23:12:30   Martin  $
// $Log:   P:/marille/clinicum/rev/normcalc.cpv  $
// 
//    Rev 1.7   23 Mar 1998 23:12:30   Martin
// GetGrowthVal: mode -> rmode
// 
//    Rev 1.6   02 Feb 1996 10:36:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   24 Aug 1995 00:20:30   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.4   12 Apr 1995 12:26:32   HANNES
// 
//    Rev 1.3   10 Apr 1995 16:03:12   HANNES
// 
//    Rev 1.2   31 Mar 1995 20:29:56   HANNES
// 
//    Rev 1.1   20 Mar 1995 12:05:28   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 17:05:18   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   12 Jan 1994 11:10:36   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.1   10 Nov 1993 14:23:18   MARTIN
// neue Funktion: GetGrowthVal
// 
//    Rev 1.0   15 Oct 1993 10:31:30   MARTIN
// Initial revision.
// 

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define MODULENUM 52
#include "winass.hpp"
#include "globmem.h"
#include "normcalc.hpp"
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

static void GetEleSize(LPVOID FAR * FAR *free, int FAR *EleSize, int FAR *actind)
  {
  int addlinfo = 1;   // # DWORDs zwischen 'type's (1 = Variblenreferenz)
  int dimsize = 2;    // Default fuer FLAGVAR
  int myind = (*actind)++;
#define ACTFREE (*((LPDWORD FAR *FAR *)free))
  switch (NC_VARTYPE(**ACTFREE++)) {
    case NC_SAMEAS:
    case NC_UNDEF:
      EleSize[myind] = 0;
      break;
    case NC_DECVAR:
      {
      DWORD dectype = NC_DECTYPE(*(ACTFREE[-1]));
      if (dectype == NC_MINMAX) addlinfo += 2;   // min / max
      else if (dectype == NC_BASEPTS) addlinfo += (int)(**ACTFREE); // basep.
      }
    case NC_STRIND:
      addlinfo += 1;    // dimsize
      dimsize = (int)(**ACTFREE);
    case NC_FLAG:
      {
      DWORD subtype = NC_SUBTYPE(*(ACTFREE[-1]));
      ACTFREE += addlinfo;
      switch (subtype) {
        case NC_END:
          EleSize[myind] = dimsize;
          break;
        case NC_FIX:
          GetEleSize(free, EleSize, actind);
          EleSize[myind] = EleSize[myind + 1] * dimsize;
          break;
        case NC_VARIABLE:
          {
          EleSize[myind] = 0;
          for (int i = 0; i < dimsize; i++) {
            int lastind = *actind;
            GetEleSize(free, EleSize, actind);
            EleSize[myind] += EleSize[lastind];
            }
          break;
          }
        default:
          DBWIN_ASSERT(FALSE);
        }
      break;
      }
    default:
      DBWIN_ASSERT(FALSE);
    }
#undef ACTFREE
  }


static void SkipSubTree(LPVOID FAR *FAR *free, int FAR *actind)
  {
  int addlinfo = 1;   // # DWORDs zwischen 'type's (1 = Variblenreferenz)
  int dimsize = 2;    // Default fuer FLAGVAR
  int myind = (*actind)++;
#define ACTFREE (*((LPDWORD FAR *FAR *)free))
  switch (NC_VARTYPE(**ACTFREE++)) {
    case NC_SAMEAS:
    case NC_UNDEF:
      break;
    case NC_DECVAR:
      {
      DWORD dectype = NC_DECTYPE(*(ACTFREE[-1]));
      if (dectype == NC_MINMAX) addlinfo += 2;   // min / max
      else if (dectype == NC_BASEPTS) addlinfo += (int)(**ACTFREE); // basep.
      }
    case NC_STRIND:
      addlinfo += 1;    // dimsize
      dimsize = (int)(**ACTFREE);
    case NC_FLAG:
      {
      DWORD subtype = NC_SUBTYPE(*(ACTFREE[-1]));
      ACTFREE += addlinfo;
      switch (subtype) {
        case NC_END:
          break;
        case NC_FIX:
          SkipSubTree(free, actind);
          break;
        case NC_VARIABLE:
          {
          for (int i = 0; i < dimsize; i++)
            SkipSubTree(free, actind);
          break;
          }
        default:
          DBWIN_ASSERT(FALSE);
        }
      break;
      }
    default:
      DBWIN_ASSERT(FALSE);
    }
#undef ACTFREE
  }


#pragma optimize("",off)
static LPNORMCALC TabOffset(mdiChild *c, LPVOID FAR *FAR *free, int FAR *EleSize, int FAR *actind)
  {
  int addlinfo = 1;   // # DWORDs zwischen 'type's (1 = Variblenreferenz)
  int dimsize = 2;    // Default fuer FLAGVAR
  int myind = (*actind)++;
  int arrind = -1;
  LPNORMCALC newnc = NULL;
  BOOL interpol = FALSE;
  float interval = float(0.0);
#define ACTFREE (*((LPDWORD FAR *FAR *)free))
  switch (NC_VARTYPE(**ACTFREE++)) {
    case NC_SAMEAS:
      DBWIN_ASSERT(FALSE);
    case NC_UNDEF:
      break;
    case NC_DECVAR:
      {
      dimsize = (int)(**ACTFREE);
      float FAR *lpdec = (float FAR *) (ACTFREE[1]);
      if ((lpdec == NULL) || (*lpdec > 1.0E9))
        break;
      float dec = *lpdec;
      float min = float(0.0);
      float max = (float)(dimsize - 1);
      DWORD dectype = NC_DECTYPE(*(ACTFREE[-1]));
      if (dectype == NC_MINMAX) {
        addlinfo += 2;   // min / max
        min = *((float FAR *)(ACTFREE[2]));
        max = *((float FAR *)(ACTFREE[3]));
        }
      else if (dectype == NC_BASEPTS) {
        addlinfo += dimsize;  // Stuetzpunkte
        min = *((float FAR *)(ACTFREE[2]));
        max = *((float FAR *)(ACTFREE[1 + dimsize]));
        }
      DWORD decdef = NC_MMTYPE(*(ACTFREE[-1]));
      if (dec < min) {
        if (decdef == NC_UNDEFIF)
          break;
        dec = min;
        }
      else if (dec > max) {
        if (decdef == NC_UNDEFIF)
          break;
        dec = max;
        }
      if (dectype == NC_MINMAX) {
        dec = ((dec - min) / (max - min)) * ((float)(dimsize - 1));
        }
      DWORD inttype = NC_INTTYPE(*(ACTFREE[-1]));
      if (dectype == NC_BASEPTS) {
        float FAR *FAR *basepts = ((float FAR *FAR *)(ACTFREE + 2));
        arrind = 0;
        if (inttype == NC_ROUND) {
          while ((arrind < (dimsize - 1)) &&
                 (dec >= ((*(basepts[arrind]) + *(basepts[arrind + 1])) / 2.0)))
            arrind++;
          }
        else {
          while ((arrind < (dimsize - 1)) &&
                 (dec >= *(basepts[arrind + 1])))
            arrind++;
          if ((inttype == NC_LININT) && (arrind < (dimsize - 1))) {
            interpol = TRUE;
            interval = (dec - *(basepts[arrind])) /
                       (*(basepts[arrind + 1]) - *(basepts[arrind]));
            }
          }
        }
      else {
        if (inttype == NC_ROUND)
          dec += (float)0.5;
        arrind = (int)dec;
        if ((inttype == NC_LININT) && (arrind < (dimsize - 1))) {
          interpol = TRUE;
          interval = dec - (float)arrind;
          }
        }
      }
    case NC_STRIND:
      addlinfo += 1;    // dimsize
      dimsize = (int)(**ACTFREE);
      if (arrind == -1) {
        WORD FAR *strind = (WORD FAR *)(ACTFREE[1]);
        if ((strind == NULL) || (*strind >= (WORD)dimsize))
          break;
        arrind = *strind;
        }
    case NC_FLAG:
      {
      if (arrind == -1) {
        WORD FAR *flag = (WORD FAR *)(*ACTFREE);
        if (flag == NULL)
          break;
        arrind = (*flag != 0) ? 1 : 0;
        }
      DWORD subtype = NC_SUBTYPE(*(ACTFREE[-1]));
      ACTFREE += addlinfo;
      switch (subtype) {
        case NC_END:
          EleSize[myind] = dimsize;
          newnc = (LPNORMCALC)GetGlobMem(sizeof(NormCalc));
          newnc->Index = arrind;
          newnc->interpol = interpol;
          newnc->interval = interval;
          break;
        case NC_FIX:
          newnc = TabOffset(c, free, EleSize, actind);
          if (newnc != NULL)
            newnc->Index += EleSize[myind + 1] * arrind;
          break;
        case NC_VARIABLE:
          {
          LPDWORD FAR *firstfree = ACTFREE;
          int firstind = *actind;
          int offs = 0;
          for (int i = 0; i < arrind; i++) {
            int lastind = *actind;
            SkipSubTree(free, actind);
            offs += EleSize[lastind];
            }
          if ((NC_VARTYPE(**ACTFREE)) == NC_SAMEAS) {
            arrind = (int)NC_TYPENO(**ACTFREE);
            ACTFREE = firstfree;
            *actind = firstind;
            offs = 0;
            for (i = 0; i < arrind; i++) {
              int lastind = *actind;
              SkipSubTree(free, actind);
              offs += EleSize[lastind];
              }
            }
          newnc = TabOffset(c, free, EleSize, actind);
          if (newnc != NULL)
            newnc->Index += offs;
          break;
          }
        default:
          DBWIN_ASSERT(FALSE);
        }
      break;
      }
    default:
      DBWIN_ASSERT(FALSE);
    }

  return newnc;
#undef ACTFREE
  }
#pragma optimize("",on)


BOOL DefNormObj(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  DefNormObj_param FAR *par = (DefNormObj_param FAR *)param;
  int numpars = ((par->ParSize - sizeof(DefNormObj_param)) / sizeof(par->free[0])) + 1;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    DBWIN_ASSERT(par->ParSize >= sizeof(DefNormObj_param));
    LPVOID FAR *actptrs = (LPVOID FAR *) GetGlobMem (numpars * sizeof(LPVOID));
    LPVOID FAR *old = actptrs;
    for (int i = 0 ; i < numpars ; i++)
      actptrs[i] = c->ReadlData (par->free[i]);
    int FAR *EleSize = (int FAR *) GetGlobMem(numpars * sizeof(int));
    for (i = 0; i < numpars; i++)
      EleSize[i] = -1;  // Markierung fuer noch nicht berechnet
    int actind = 0;
    GetEleSize(&actptrs, EleSize, &actind);
    actind = 0;
    actptrs = old;
    LPNORMCALC newnc = TabOffset(c, &actptrs, EleSize, &actind);
    LPNORMCALC FAR *nc = (LPNORMCALC FAR *)c->ReadlData(par->normobj);
    if ((nc != NULL) && (*nc != NULL))
      FreeGlobMem(*nc);
    c->WritelData(par->normobj,&newnc,sizeof(LPNORMCALC),Offset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) ? UPDATE_ASYNCHRON : FALSE);
    FreeGlobMem(EleSize);
    actptrs = old;
    FreeGlobMem (actptrs);
    }

  if ((mode & EM_FIXCONNECTION) || (mode & (EM_CLEAR | EM_RESET))) {
    int i = 0;
    while (i < numpars) {
      int actvar = -1;
      DWORD vartype = c->ReadConstLong (par->free[i++]);
      switch (NC_VARTYPE(vartype)) {
        case NC_SAMEAS:
        case NC_UNDEF:
          break;
        case NC_STRIND:
          i++;
        case NC_FLAG:
          actvar = i++;
          break;
        case NC_DECVAR:
          {
          i++;
          actvar = i++;
          DWORD dectype = NC_DECTYPE(vartype);
          if (dectype == NC_MINMAX) i += 2;
          else if (dectype == NC_BASEPTS) i += c->ReadConstInt (par->free[i-2]);
          break;
          }
        default:
          DBWIN_ASSERT(FALSE);
        }
      if (actvar >= 0) {
        if (mode & EM_FIXCONNECTION)
          c->SetlConnection(par->free[actvar], Offset);
        else
          c->ClearlConnection(par->free[actvar], Offset);
        }
      }
    DBWIN_ASSERT(i == numpars);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    LPNORMCALC FAR *nc = (LPNORMCALC FAR *)c->ReadlData(par->normobj);
    if ((nc != NULL) && (*nc != NULL))
      FreeGlobMem(*nc);
    c->DellData(par->normobj,Offset,(mode & EM_CHANGETOFALSE) ? UPDATE_ASYNCHRON : FALSE);
    }

  return FALSE ;
  }

typedef float FAR *LPFLOAT;

BOOL DefNormTab(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  DefNormTab_param FAR *par = (DefNormTab_param FAR *)param;

  if (mode & EM_LOAD) {
    int freelen = par->ParSize - sizeof(DefNormTab_param);
    DBWIN_ASSERT(freelen > 0);
    int count = freelen / sizeof(DWORD);
    LPFLOAT nt = LPFLOAT (GetGlobMem (count * sizeof(float)));
    for (int i = 0 ; i < count ; i++) {
      LPFLOAT lpnt = LPFLOAT (c->ReadlData (((LPDWORD)(par + 1))[i]));
      DBWIN_ASSERT (lpnt != NULL);
      nt[i] = *lpnt;
      }
    c->WritelData(par->normtab,&nt,sizeof(LPFLOAT),Offset,(mode & EM_CHANGETOTRUE) ? UPDATE_ASYNCHRON : FALSE);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    LPVOID FAR *old = (LPVOID FAR *) c->ReadlData (par->normtab);
    FreeGlobMem (*old);
    c->DellData(par->normtab,Offset,(mode & EM_CHANGETOFALSE) ? UPDATE_ASYNCHRON : FALSE);
    }

  return FALSE ;
  }


static float GetNormInt(LPNORMCALC nc, LPFLOAT nt)
  {
  if (nc->interpol)
    return ((float)1.0 - nc->interval) * nt[nc->Index] +
            nc->interval * nt[nc->Index + 1];
  else
    return nt[nc->Index];
  }


BOOL GetNorm(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  GetNorm_param FAR *par = (GetNorm_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPNORMCALC FAR *lpnc = (LPNORMCALC FAR *)c->ReadlData(par->normobj);
    LPFLOAT FAR *lpnt = (LPFLOAT FAR *)c->ReadlData(par->normtab);
    if ((lpnc != NULL) && (*lpnc != NULL) && (lpnt != NULL) && (*lpnt != NULL)) {
      float norm = GetNormInt(*lpnc, *lpnt);
      c->WritelData(par->normval,&norm,sizeof(float),Offset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) ? UPDATE_ASYNCHRON : FALSE);
      }
    else
      c->DellData(par->normval,Offset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) ? UPDATE_ASYNCHRON : FALSE);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->normobj,Offset);
    c->SetlConnection(par->normtab,Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->normobj,Offset);
    c->ClearlConnection(par->normtab,Offset);
    if (mode & EM_CHANGETOFALSE)
      c->DellData(par->normval,Offset);
    }

  return FALSE ;
  }


BOOL GetGrowthVal(mdiChild *c, LPVOID param, WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  GetGrowthVal_param FAR *par = (GetGrowthVal_param FAR *)param;
  WORD ggvmode = c->ReadConstInt (par->rmode);
  if (mode & (EM_LOAD | EM_UPDATE)) {
    float FAR *lpold = (float FAR *)c->ReadlData(par->gold);
    LPNORMCALC FAR *lponc = (LPNORMCALC FAR *)c->ReadlData(par->onobj);
    LPNORMCALC FAR *lpnnc = (LPNORMCALC FAR *)c->ReadlData(par->nnobj);
    LPFLOAT FAR *lpnt = (LPFLOAT FAR *)c->ReadlData(par->ntab);
    float res = float(1.0E10);
    if ((lpold != NULL) && (*lpold < 1.0E9) &&
        (lponc != NULL) && (*lponc != NULL) &&
        (lpnnc != NULL) && (*lpnnc != NULL) &&
        (lpnt != NULL) && (*lpnt != NULL)) {
      float onorm = GetNormInt(*lponc, *lpnt);
      float nnorm = GetNormInt(*lpnnc, *lpnt);
      if (ggvmode == GGV_ABSOLUT) {
        // absolute Abweichung bleibt gleich
        res = (*lpold - onorm) + nnorm;
        }
      else if (ggvmode == GGV_RELATIV) {
        // relative Abweichung bleibt gleich
        if (fabs(onorm) > 1.0E-3)
          res = (*lpold / onorm) * nnorm;
        }
      else if ((ggvmode == GGV_EXPABS) || (ggvmode == GGV_EXPREL)) {
        float FAR *lpa = (float FAR *)c->ReadlData(par->a);
        float FAR *lpt = (float FAR *)c->ReadlData(par->t);
        float FAR *lptau = (float FAR *)c->ReadlData(par->tau);
        if ((lpa != NULL) && (*lpa < 1.0E9) &&
            (lpt != NULL) && (*lpt < 1.0E9) &&
            (lptau != NULL) && (*lptau < 1.0E9) &&
            (fabs(*lptau) > 1.0E-3)) {
          float e = (float)(1.0 + (1.0 - *lpa) * (exp(-*lpt / *lptau) - 1.0));
          if (ggvmode == GGV_EXPABS)
            res = (*lpold - onorm) * e + nnorm;
          else
            res = (*lpold / onorm) * e * nnorm;
          }
        }
      else {
        DBWIN_ASSERT(FALSE);
        }
      }
    if (res < 1.0E9)
      c->WritelData(par->gres,&res,sizeof(float),Offset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) ? UPDATE_ASYNCHRON : FALSE);
    else
      c->DellData(par->gres,Offset,(mode & (EM_CHANGETOTRUE | EM_UPDATE)) ? UPDATE_ASYNCHRON : FALSE);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->gold,Offset);
    c->SetlConnection(par->onobj,Offset);
    c->SetlConnection(par->nnobj,Offset);
    c->SetlConnection(par->ntab,Offset);
    if ((ggvmode == GGV_EXPABS) || (ggvmode == GGV_EXPREL)) {
      c->SetlConnection(par->a,Offset);
      c->SetlConnection(par->t,Offset);
      c->SetlConnection(par->tau,Offset);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->gold,Offset);
    c->ClearlConnection(par->onobj,Offset);
    c->ClearlConnection(par->nnobj,Offset);
    c->ClearlConnection(par->ntab,Offset);
    if ((ggvmode == GGV_EXPABS) || (ggvmode == GGV_EXPREL)) {
      c->ClearlConnection(par->a,Offset);
      c->ClearlConnection(par->t,Offset);
      c->ClearlConnection(par->tau,Offset);
      }
    if (mode & EM_CHANGETOFALSE)
      c->DellData(par->gres,Offset);
    }

  return FALSE ;
  }

