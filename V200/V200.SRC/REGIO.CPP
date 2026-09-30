//--------------------------------------------------------------------
// Region - Funktionen
// $Header:   P:/marille/clinicum/rev/regio.cpv   1.5   26 Feb 1998 20:10:06   Hannes  $
// $Log:   P:/marille/clinicum/rev/regio.cpv  $
// 
//    Rev 1.5   26 Feb 1998 20:10:06   Hannes
// DBINT auf Float umgestellt
// 
//    Rev 1.4   27 May 1997 11:27:44   Hannes
// Angabe des Rechteckes unabhaengig von der Ausrichtung
// 
//    Rev 1.3   21 Apr 1997 17:05:30   Hannes
// Verbesserte Hittest
// 
//    Rev 1.2   10 Apr 1997 11:46:02   Hannes
// Verbesserung der Regionfunktionen
// 
//    Rev 1.1   13 Mar 1997 18:59:06   Hannes
// Verbesserte HitTestfunktion
// 
//    Rev 1.0   28 Feb 1997 14:46:38   Hannes
// Initial revision.
//--------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"

#include "globmem.h"
#include "dds.hpp"
#include "hash.hpp"
#include "compile.hpp"
#define MODULENUM 179
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "mdichild.hpp"
#include "multipro.hpp"

struct Region {
  RECT r;
  DBINT Seite;
  Region FAR *Next,FAR *Prev;
  LPVOID RegioData;
  };
typedef Region FAR *LPREGION;
struct RegioBase {
  LPREGION r;
  hash FAR *CmpData;
  };

#define NHUGE     1.0E100
#define VERYHUGE  1.0E101
typedef BOOL (* CREGION) (LPREGION r,LPVOID sData);
typedef double (* TREGION) (LPREGION r,LPVOID sData);
typedef void (* SREGION) (LPVOID sData);
LPREGION GetRegion (LPREGION First,DBINT Seite,CREGION cfunc,LPVOID sData)
  {
  for (LPREGION x = First ; x != NULL ; x = x->Next) {
    if ((Seite == x->Seite) && (* cfunc) (x,sData))
      return x;
    }
  return NULL;
  }

BOOL RegioTested (LPREGION x,LPREGION FAR *tested)
  {
  int dim = GetBlockSize (tested) / sizeof(*tested);
  for (int i = 0 ; i < dim ; i++)
    if (tested[i] == x) return TRUE ;
  return FALSE ;
  }

LPREGION FAR *MarkTested (LPREGION x,LPREGION FAR *tested)
  {
  int dim = GetBlockSize (tested) / sizeof(*tested);
  LPREGION FAR *n = (LPREGION FAR *) GetGlobMem ((dim + 1) * sizeof(LPREGION)) ;
  if (tested != NULL) {
    lmemcpy (n,tested,dim * sizeof(LPREGION)) ;
    n[dim] = x ;
    }
  return n;
  }

LPREGION GetBestRegion (LPREGION First,DBINT Seite,TREGION tfunc,LPVOID sData,LPREGION FAR *tested,SREGION sfunc)
  {
  double old = NHUGE;
  LPREGION best = NULL;
  for (LPREGION x = First ; x != NULL ; x = x->Next) {
    if (x->Seite != Seite) continue ;
    if (RegioTested (x,tested)) continue ;
    double act = (*tfunc) (x,sData);
    if (act < old) {
      old = act ;
      best = x ;
      if (sfunc != NULL) (*sfunc) (sData);
      }
    }
  return best ;
  }

BOOL htCmp (LPRECT r1,LPRECT r2)
  {
  RECT ri;
  IntersectRect (&ri,r1,r2);
  int ac1 = 0 ;
  if ((ri.left == r1->left) && (ri.top == r1->top) && (ri.bottom == r1->bottom)) ac1 ++ ;
  if ((ri.right == r1->right) && (ri.top == r1->top) && (ri.bottom == r1->bottom)) ac1 ++ ;
  if ((ri.top == r1->top) && (ri.left == r1->left) && (ri.right == r1->right)) ac1 ++ ;
  if ((ri.bottom == r1->bottom) && (ri.left == r1->left) && (ri.right == r1->right)) ac1 ++ ;
  int ac2 = 0 ;
  if ((ri.left == r2->left) && (ri.top == r2->top) && (ri.bottom == r2->bottom)) ac2 ++ ;
  if ((ri.right == r2->right) && (ri.top == r2->top) && (ri.bottom == r2->bottom)) ac2 ++ ;
  if ((ri.top == r2->top) && (ri.left == r2->left) && (ri.right == r2->right)) ac2 ++ ;
  if ((ri.bottom == r2->bottom) && (ri.left == r2->left) && (ri.right == r2->right)) ac2 ++ ;
  double ai = fabs(double (ri.right - ri.left)) * fabs(double (ri.bottom - ri.top));
  double a1 = fabs(double (r1->right - r1->left)) * fabs(double (r1->bottom - r1->top));
  double a2 = fabs(double (r2->right - r2->left)) * fabs(double (r2->bottom - r2->top));
  double v1,v2;
  if (a1 > 0.000001) v1 = ai / a1 ;
  else               v1 = 1.0 ;
  if (a2 > 0.000001) v2 = ai / a2 ;
  else               v2 = 1.0 ;
  return (5.0 - double(ac1) - v1 < 5.0 - double(ac2) - v2); // r1 passt besser als r2
  }

LPREGION RegionCompare (LPREGION First,DBINT Seite,LPPOINT lppt)
  {
  double old = NHUGE;
  LPREGION best = NULL;
  for (LPREGION x = First ; x != NULL ; x = x->Next) {
    if (x->Seite != Seite) continue ;
    if (PtInRect (&x->r,*lppt)) {
      if ((best == NULL) || (htCmp (&x->r,&best->r))) best = x ;
      }
    }
  return best ;
  }

LPREGION RemoveRegion (LPREGION First,LPVOID RegioData)
  {
  LPREGION prev = NULL ;
  for (LPREGION x = First ; x != NULL ; x = x->Next) {
    if ((GetBlockSize (RegioData) == GetBlockSize(x->RegioData)) &&
        (lmemcmp (RegioData,x->RegioData,GetBlockSize(RegioData)))) {
      if (prev == NULL) First = x->Next ;
      else              prev->Next = x->Next ;
      FreeGlobMem (x->RegioData);
      FreeGlobMem (x);
      return First;
      }
    prev = x ;
    }
  return NULL;
  }

LPREGION AddRegion (LPREGION First,DBINT Seite,LPRECT r,LPVOID RegioData)
  {
  LPREGION n = LPREGION (GetGlobMem (sizeof(*n)));
  n->Next = First ;
  if (First != NULL) First->Prev = n ;
  First = n ;
  n->RegioData = GetGlobMem (GetBlockSize(RegioData));
  lmemcpy (n->RegioData,RegioData,GetBlockSize(RegioData));
  n->Seite = Seite;
  n->r = *r ;
  return First ;
  }

LPREGION FindRegion (LPREGION First,LPVOID RegioData)
  {
  for (LPREGION x = First ; x != NULL ; x = x->Next) {
    if ((GetBlockSize (RegioData) == GetBlockSize(x->RegioData)) &&
        (lmemcmp (RegioData,x->RegioData,GetBlockSize(RegioData))))
      return x;
    }
  return NULL ;
  }

#pragma pack(1)
struct DefineRegion_param {
  WORD parSize;
  DWORD RegioList;
  DWORD Seite;
  DWORD x0,y0,x1,y1;
  DWORD rData;
  };
#pragma pack()

BOOL DefineRegion (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DefineRegion_param FAR *par = (DefineRegion_param FAR *) param;
    LPVOID rData = c->ReadlData (par->rData);
    RegioBase FAR *rold = (RegioBase FAR *) c->ReadlData (par->RegioList);
    DBINT FAR *Seite = (DBINT FAR *) c->ReadlData (par->Seite);
    float FAR *x0 = (float FAR *) c->ReadlData (par->x0);
    float FAR *y0 = (float FAR *) c->ReadlData (par->y0);
    float FAR *x1 = (float FAR *) c->ReadlData (par->x1);
    float FAR *y1 = (float FAR *) c->ReadlData (par->y1);
    DBWIN_ASSERT ((Seite != NULL) && (x0 != NULL) && (y0 != NULL) && (x1 != NULL) && (y1 != NULL) &&
                  (rData != NULL));
    RECT r;
    int xm,ym,xx,yx;
    if (*x0 < *x1) xm = int(*x0) , xx = int(*x1) ;
    else           xm = int(*x1) , xx = int(*x0) ;
    if (*y0 < *y1) ym = int(*y0) , yx = int(*y1) ;
    else           ym = int(*y1) , yx = int(*y0) ;
    SetRect (&r,xm,ym,xx,yx);
    LPREGION n;
    RegioBase rb;
    if (rold != NULL) {
      n = AddRegion (rold->r,*Seite,&r,rData);
      rb.r = n ;
      rb.CmpData = rold->CmpData ;
      rb.CmpData->SetDatav (rData,&n,sizeof(n),GetBlockSize(rData));
      }
    else {
      n = AddRegion (NULL,*Seite,&r,rData);
      rb.r = n ;
      rb.CmpData = new hash(VOIDKEY,137) ;
      rb.CmpData->SetDatav (rData,&n,sizeof(n),GetBlockSize(rData));
      }

    c->WritelData (par->RegioList,&rb,sizeof(rb),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_UPDATE) {
    DefineRegion_param FAR *par = (DefineRegion_param FAR *) param;
    LPVOID rData = c->ReadlData (par->rData);
    RegioBase FAR *rold = (RegioBase FAR *) c->ReadlData (par->RegioList);
    DBINT FAR *Seite = (DBINT FAR *) c->ReadlData (par->Seite);
    float FAR *x0 = (float FAR *) c->ReadlData (par->x0);
    float FAR *y0 = (float FAR *) c->ReadlData (par->y0);
    float FAR *x1 = (float FAR *) c->ReadlData (par->x1);
    float FAR *y1 = (float FAR *) c->ReadlData (par->y1);
    DBWIN_ASSERT ((Seite != NULL) && (x0 != NULL) && (y0 != NULL) && (x1 != NULL) && (y1 != NULL) &&
                  (rData != NULL));
    RECT r;
    float xm,ym,xx,yx;
    if (*x0 < *x1) xm = *x0 , xx = *x1 ;
    else           xm = *x1 , xx = *x0 ;
    if (*y0 < *y1) ym = *y0 , yx = *y1 ;
    else           ym = *y1 , yx = *y0 ;
    SetRect (&r,int(xm),int(ym),int(xx),int(yx));
    LPREGION FAR *x = (LPREGION FAR *) rold->CmpData->GetDatav (rData,GetBlockSize(rData));
    (*x)->r = r;
    (*x)->Seite = *Seite ;
    }
  if (mode & EM_FIXCONNECTION) {
    DefineRegion_param FAR *par = (DefineRegion_param FAR *) param;
    c->SetlConnection (par->Seite,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->x0,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->y0,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->x1,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->y1,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DefineRegion_param FAR *par = (DefineRegion_param FAR *) param;
    c->ClearlConnection (par->Seite,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x1,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y1,LPSTR(param) - sizeof(WORD));
    LPVOID rData = c->ReadlData (par->rData);
    RegioBase FAR *rold = (RegioBase FAR *) c->ReadlData (par->RegioList);
    LPREGION FAR *x = (LPREGION FAR *) rold->CmpData->GetDatav (rData,GetBlockSize(rData));
    if ((*x)->Prev != NULL) (*x)->Prev->Next = (*x)->Next ;
    if ((*x)->Next != NULL) (*x)->Next->Prev = (*x)->Prev ;
    if (rold->r == *x) rold->r = (*x)->Next ;
    rold->CmpData->DelDatav (rData,GetBlockSize(rData));
    if (rold->r == NULL) {
      delete rold->CmpData;
      c->DellData (par->RegioList,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FindRegion_param {
  WORD parSize;
  DWORD RegioList;
  DWORD rData;
  DWORD Seite;
  DWORD x0,y0;
  DWORD x1,y1;
  };
#pragma pack()

struct HTDATA {
  POINT pt;
  RECT r;
  RECT ract;
  int  AnzahlSeitenGleich;
  };
typedef HTDATA FAR *LPHTDATA;
void SetActRect (LPVOID sData)
  {
  LPHTDATA (sData)->r = LPHTDATA (sData)->ract;
  }
double HitTest (LPREGION r,LPVOID sData)
  {
  if (PtInRect (&r->r,LPHTDATA(sData)->pt)) {
    LPRECT rbest = &((LPHTDATA (sData))->r) ;
    RECT ri;
    IntersectRect (&ri,rbest,&(r->r));
    int ac = 0 ;
    if ((ri.left == r->r.left) && (ri.top == r->r.top) && (ri.bottom == r->r.bottom)) ac ++ ;
    if ((ri.right == r->r.right) && (ri.top == r->r.top) && (ri.bottom == r->r.bottom)) ac ++ ;
    if ((ri.top == r->r.top) && (ri.left == r->r.left) && (ri.right == r->r.right)) ac ++ ;
    if ((ri.bottom == r->r.bottom) && (ri.left == r->r.left) && (ri.right == r->r.right)) ac ++ ;
    LPHTDATA (sData)->ract = r->r;
    double a1 = fabs(double (ri.right - ri.left)) * fabs(double (ri.bottom - ri.top));
    double a2 = fabs(double (r->r.right - r->r.left)) * fabs(double (r->r.bottom - r->r.top));
    double v;
    if (a2 > 0.000001) v = a1 / a2 ;
    else               v = 1.0 ;
    return 5.0 - double(ac) - v ;
    }
  else
    return VERYHUGE ;
  }
BOOL RectTest (LPREGION r,LPVOID sData)
  {
  RECT rd;
  IntersectRect (&rd,&r->r,LPRECT(sData));
  return !IsRectEmpty (&rd);
  }

double BestV (LPREGION r,LPVOID sData)
  {
  int dy = LPPOINT(sData)->y - r->r.bottom ;
  if (dy > 0) {
    int dx = LPPOINT(sData)->x - r->r.left ;
    if (dx < 0) dx = -dx ;
    return 3.0 * double (dy) + double (dx) ;
    }
  else
    return VERYHUGE ;
  }

BOOL RegioFromPoint (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    LPVOID rData = NULL;
    LPREGION FAR *rold = (LPREGION FAR *) c->ReadlData (par->RegioList);
    DBINT FAR *Seite = (DBINT FAR *) c->ReadlData (par->Seite);
    float FAR *x0 = (float FAR *) c->ReadlData (par->x0);
    float FAR *y0 = (float FAR *) c->ReadlData (par->y0);
    DBWIN_ASSERT ((Seite != NULL) && (x0 != NULL) && (y0 != NULL)) ;
    POINT pt;
    pt.x = int(*x0) ;
    pt.y = int(*y0) ;
    LPREGION n;
    if (rold != NULL)
      n = RegionCompare (*rold,*Seite,&pt);
    else
      n = NULL ;
    if (n != NULL) {
      c->WritelData (par->RegioList,&(n->Next),sizeof(n->Next),LPSTR(param) - sizeof(WORD));
      c->WritelData (par->rData,n->RegioData,GetBlockSize (n->RegioData),LPSTR(param) - sizeof(WORD));
      }
    else {
      c->DellData (par->rData,LPSTR(param) - sizeof(WORD));
      c->DellData (par->RegioList,LPSTR(param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    c->ClearlConnection (par->Seite,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y0,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL RegioFromRect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    LPVOID rData = NULL;
    LPREGION FAR *rold = (LPREGION FAR *) c->ReadlData (par->RegioList);
    DBINT FAR *Seite = (DBINT FAR *) c->ReadlData (par->Seite);
    float FAR *x0 = (float FAR *) c->ReadlData (par->x0);
    float FAR *y0 = (float FAR *) c->ReadlData (par->y0);
    float FAR *x1 = (float FAR *) c->ReadlData (par->x1);
    float FAR *y1 = (float FAR *) c->ReadlData (par->y1);
    DBWIN_ASSERT ((Seite != NULL) && (x0 != NULL) && (y0 != NULL) && (x1 != NULL) && (y1 != NULL)) ;
    RECT r;
    SetRect (&r,int(*x0),int(*y0),int(*x1),int(*y1));
    LPREGION n;
    if (rold != NULL)
      n = GetRegion (*rold,*Seite,RectTest,&r);
    else
      n = NULL ;
    if (n != NULL) {
      c->WritelData (par->RegioList,&(n->Next),sizeof(n->Next),LPSTR(param) - sizeof(WORD));
      c->WritelData (par->rData,n->RegioData,GetBlockSize (n->RegioData),LPSTR(param) - sizeof(WORD));
      }
    else {
      c->DellData (par->rData,LPSTR(param) - sizeof(WORD));
      c->DellData (par->RegioList,LPSTR(param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    c->ClearlConnection (par->Seite,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x1,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y1,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL BestRegioFromPoint (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    LPVOID rData = NULL;
    LPREGION FAR *rold = (LPREGION FAR *) c->ReadlData (par->RegioList);
    DBINT FAR *Seite = (DBINT FAR *) c->ReadlData (par->Seite);
    float FAR *x0 = (float FAR *) c->ReadlData (par->x0);
    float FAR *y0 = (float FAR *) c->ReadlData (par->y0);
    LPREGION FAR *tested = (LPREGION FAR *) c->ReadlData (par->x1);
    DBWIN_ASSERT ((Seite != NULL) && (x0 != NULL) && (y0 != NULL)) ;
    POINT pt;
    pt.x = int(*x0) ;
    pt.y = int(*y0) ;
    LPREGION n;
    if (rold != NULL)
      n = GetBestRegion (*rold,*Seite,BestV,&pt,tested,NULL);
    else
      n = NULL ;
    if (n != NULL) {
      c->WritelData (par->rData,n->RegioData,GetBlockSize (n->RegioData),LPSTR(param) - sizeof(WORD));
      tested = MarkTested (n,tested);
      c->WritelData (par->x1,tested,GetBlockSize(tested),LPSTR(param) - sizeof(WORD));
      FreeGlobMem (tested);
      }
    else
      c->DellData (par->rData,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FindRegion_param FAR *par = (FindRegion_param FAR *) param;
    c->ClearlConnection (par->Seite,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->x0,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->y0,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

