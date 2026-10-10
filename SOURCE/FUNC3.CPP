/*-------------------------------------------------*/
/* func3.cpp - Weitere Scriptfunktionen            */
/*-------------------------------------------------*/
//  $Header:   P:/marille/clinicum/rev/func3.cpv   1.25   10 Jan 2000 18:18:18   Martin  $
//  $Log:   P:/marille/clinicum/rev/func3.cpv  $
// 
//    Rev 1.25   10 Jan 2000 18:18:18   Martin
// GetFullTime: res auf jeden Fall initialisieren
// 
//    Rev 1.24   10 Sep 1999 17:10:34   Wolfgang
// 1.) ClearFeiertage und SetFeiertag eingebaut.
// 
//    Rev 1.23   12 Feb 1999 19:47:02   Martin
// noch eine Korrektur in Zeitberechnungsfunktionen
// 
//    Rev 1.22   01 Dec 1998 15:35:40   Martin
// Zeitberechnungsfunktionen korrigiert (Fehler ServoData)
// 
//    Rev 1.21   18 Nov 1998 15:50:22   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.20   29 Oct 1998 11:53:06   Wolfgang
// 1.) ein int in uDiffDateTime.
// 
//    Rev 1.19   09 Oct 1998 18:48:04   Wolfgang
// 1.) NetWorkAddressStrToBin und NetWorkAddressBinToStr neu.
// 
//    Rev 1.18   09 Sep 1998 17:13:30   WOLFGANG
// Martin: Kettenlinien Korrekturen (fuer Diagnosticum)
// 
//    Rev 1.17   04 Aug 1998 17:54:34   Hannes
// Timestamp
// 
//    Rev 1.16   17 May 1998 17:51:36   Hannes
// Statistik - FUnktion
// 
//    Rev 1.15   21 Apr 1998 19:33:42   Hannes
// 
//    Rev 1.14   08 Nov 1996 13:33:20   HANNES
// 
//    Rev 1.13   30 Oct 1996 19:30:20   HANNES
// 
//    Rev 1.12   10 Jun 1996 10:08:08   GERHOLD
// pragma pack
// 
//    Rev 1.11   01 Mar 1996 11:48:22   lens
// IntersectionVektor und bVektorTeilmenge neu.
// 
//    Rev 1.10   02 Feb 1996 10:36:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   16 Sep 1995 22:33:30   HANNES
// 
//    Rev 1.8   14 Sep 1995 09:59:44   HANNES
// 
//    Rev 1.7   01 Sep 1995 09:04:02   HANNES
// 
//    Rev 1.6   30 Aug 1995 11:38:26   HANNES
// GetScaleDateTime ... Division durch Null abgefangen
// 
//    Rev 1.5   09 Jun 1995 00:17:26   HANNES
// GetFormatBaseHeight
// 
//    Rev 1.4   27 Mar 1995 13:16:46   HANNES
//  
// 
//    Rev 1.3   20 Mar 1995 11:56:10   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.2   10 Nov 1994 22:10:16   MARTIN
// uGetDevString
// 
//    Rev 1.1   07 Sep 1994 10:51:34   HANNES
// Skalieren von Datums und Zeitwerte
// 
//    Rev 1.0   24 Jun 1994 17:05:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   13 Apr 1994 14:36:16   HANNES
// MakeCont, MakeContFromDec
// 
//    Rev 1.0   23 Feb 1994 18:49:10   MARTIN
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "hash.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "cont.hpp"
#define MODULENUM 159
#include "winass.hpp"
#include "math.h"

#pragma pack(1)
struct FAR KettenLinienParameter_param {
  WORD parSize;
  DWORD res;
  DWORD rdirection;
  DWORD pt[1];
  int AnzPt ()
    { return (parSize - sizeof(*this)) / sizeof (DWORD) + 1 ; }
  };
#pragma pack()

BOOL KettenLinienParameter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    fpt FAR *p = (fpt FAR *) GetGlobMem (sizeof(fpt) * par->AnzPt());
    KLParam k;
    int j = 0;
    for (int i = 0 ; i < par->AnzPt () ; i++) {
      fpt FAR *h = (fpt FAR *) c->ReadlData (par->pt[i]);
      if (h != NULL)
        p[j++] = *h ;
      }
    if (j >= 3) {
      KettenlinienInterpolation (p,j,&k.a,&k.b,&k.c,c->ReadConstFloat(par->rdirection));
      k.xmin = k.ymin = 1.0E10 ;
      k.xmax = k.ymax = - 1.0E10 ;
      for (i = 0 ; i < j ; i++) {
        if (k.xmin > double (p[i].x)) k.xmin = double (p[i].x);
        if (k.xmax < double (p[i].x)) k.xmax = double (p[i].x);
        if (k.ymin > double (p[i].y)) k.ymin = double (p[i].y);
        if (k.ymax < double (p[i].y)) k.ymax = double (p[i].y);
        }
      double dx = k.xmax - k.xmin;
      double x0 = 0.5 * (k.xmax + k.xmin);
      k.xmin = x0 - /* 0.55 * */ dx;
      k.xmax = x0 + /* 0.55 * */ dx;
      double dy = k.ymax - k.ymin;
      double y0 = 0.5 * (k.ymax + k.ymin);
      k.ymin = y0 - 0.7 * dy;
      k.ymax = y0 + 0.7 * dy;
      }
    else
      k.c = 1.0E10 ;

    if (k.c < 1.0E9)
      c->WritelData (par->res,&k,sizeof(k),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    FreeGlobMem (p);
    }
  if (mode & EM_FIXCONNECTION) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    for (int i = 0 ; i < par->AnzPt () ; i++)
      c->SetlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    for (int i = 0 ; i < par->AnzPt () ; i++)
      c->ClearlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ModifyKettenLinienExt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    KLParam FAR *k = (KLParam FAR *) c->ReadlData (par->res);
    int j = 0;
    if (k != NULL) {
      k->xmin = k->ymin = 1.0E10 ;
      k->xmax = k->ymax = - 1.0E10 ;
      int j = 0 ;
      for (int i = 0 ; i < par->AnzPt () ; i++) {
        fpt FAR *h = (fpt FAR *) c->ReadlData (par->pt[i]);
        if ((h != NULL) && (h->x < 1.0E9)) {
          if (k->xmin > double (h->x)) k->xmin = double (h->x);
          if (k->xmax < double (h->x)) k->xmax = double (h->x);
          if (k->ymin > double (h->y)) k->ymin = double (h->y);
          if (k->ymax < double (h->y)) k->ymax = double (h->y);
          j ++ ;
          }
        }
      if (j > 2) {
        double dx = k->xmax - k->xmin;
        double x0 = 0.5 * (k->xmax + k->xmin);
        k->xmin = x0 - /* 0.55 * */ dx;
        k->xmax = x0 + /* 0.55 * */ dx;
        double dy = k->ymax - k->ymin;
        double y0 = 0.5 * (k->ymax + k->ymin);
        k->ymin = y0 - 0.6 * dy;
        k->ymax = y0 + 0.6 * dy;
        KLParam hk = *k;
        c->WritelData (par->res,&hk,sizeof(hk),LPSTR(param)-sizeof(WORD));
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    for (int i = 0 ; i < par->AnzPt () ; i++)
      c->SetlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    KettenLinienParameter_param FAR *par = (KettenLinienParameter_param FAR *) param; 
    for (int i = 0 ; i < par->AnzPt () ; i++)
      c->ClearlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetKettenLinie_param {
  WORD parSize;
  DWORD res;
  DWORD klpar;
  DWORD rAnzPt;
  };
#pragma pack()

BOOL GetKettenLinie (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetKettenLinie_param FAR *par = (GetKettenLinie_param FAR *) param;
    KLParam FAR *p = (KLParam FAR *) c->ReadlData (par->klpar);
    if (p != NULL) {
      int AnzPt = c->ReadConstInt (par->rAnzPt);
      fpt FAR *cnt = (fpt FAR *) GetGlobMem (sizeof (fpt) * AnzPt);
      GetKettenLinie (cnt,AnzPt,p);
      c->WritelData (par->res,cnt,AnzPt * sizeof(fpt),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (cnt);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetKettenLinie_param FAR *par = (GetKettenLinie_param FAR *) param;
    c->SetlConnection (par->klpar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetKettenLinie_param FAR *par = (GetKettenLinie_param FAR *) param;
    c->ClearlConnection (par->klpar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SplitCont_param {
  WORD parSize;
  DWORD org;
  DWORD c1,c2;
  };
#pragma pack()

BOOL SplitCont (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SplitCont_param FAR *par = (SplitCont_param FAR *) param;
    fpt FAR *cnt = (fpt FAR *) c->ReadlData (par->org);
    if (cnt != NULL) {
      fpt FAR *c1 = (fpt FAR *) GetGlobMem (GetBlockSize(cnt));
      fpt FAR *c2 = (fpt FAR *) GetGlobMem (GetBlockSize(cnt));
      float xold = float(1.0E10);
      int count1 = 0,count2 = 0;
      int state = 0 ;
      for (int i = 0 ; i < int(GetBlockSize (cnt) / sizeof(fpt)) ; i++) {
        if (fabs (xold - cnt[i].x) >= 1.0E-5) {
          switch (state) {
            case 0 :
              c1[count1++] = cnt[i];    // 1. Punkt der 1. Kontur
              state = 1;
              break ;
            case 1 :
            case 2 :
              c1[count1++] = cnt[i];    // Folgepunkte 1. Kontur
              state = 2;
              break ;
            case 3 :
              c2[count2++] = cnt[i];    // 1. bzw. Folgepunkt der 2. Kontur
              break ;
            }
          }
        else {
          switch (state) {
            case 1 :
              // Leerpunkte am Anfang der 1. Kontur
              break ;
            case 2 :
              // Leerpunkte am Ende
              state = 3 ;
              break ;
            case 3 :
              // 2. Kontur, nix mehr kritisches
              break ;
            }
          }
        xold = cnt[i].x;
        }

      if (count1)
        c->WritelData (par->c1,c1,count1 * sizeof(fpt),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->c1,LPSTR(param)-sizeof(WORD));

      if (count2)
        c->WritelData (par->c2,c2,count2 * sizeof(fpt),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->c2,LPSTR(param)-sizeof(WORD));

      FreeGlobMem (c1);
      FreeGlobMem (c2);
      }
    else {
      c->DellData (par->c1,LPSTR(param)-sizeof(WORD));
      c->DellData (par->c2,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SplitCont_param FAR *par = (SplitCont_param FAR *) param;
    c->SetlConnection (par->org,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SplitCont_param FAR *par = (SplitCont_param FAR *) param;
    c->ClearlConnection (par->org,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR MakeCont_param {
  WORD parSize;
  DWORD res;
  DWORD pnt[1];

  int AnzPnt ()
    { return (parSize - sizeof(*this)) / sizeof (pnt[0]) + 1 ; }
  };
#pragma pack()

BOOL MakeCont (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    MakeCont_param FAR *par = (MakeCont_param FAR *) param;
    fpt FAR *res = (fpt FAR *) GetGlobMem (sizeof(fpt) * par->AnzPnt());
    int j = 0 ;
    for (int i = 0 ; i < par->AnzPnt() ; i++) {
      fpt FAR *p = (fpt FAR *) c->ReadlData (par->pnt[i]);
      if (p != NULL)
        res[j++] = *p;
      }
    if (j > 0)
      c->WritelData (par->res,res,sizeof(*res)*j,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    FreeGlobMem (res);
    }
  if (mode & EM_FIXCONNECTION) {
    MakeCont_param FAR *par = (MakeCont_param FAR *) param;
    for (int i = 0 ; i < par->AnzPnt() ; i++)
      c->SetlConnection (par->pnt[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    MakeCont_param FAR *par = (MakeCont_param FAR *) param;
    for (int i = 0 ; i < par->AnzPnt() ; i++)
      c->ClearlConnection (par->pnt[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR MCD_pt {
  DWORD fref;
  DWORD xref;
  DWORD yref;
  };
#pragma pack()

#pragma pack(1)
struct FAR MakeContFromDec_param {
  WORD parSize;
  DWORD res;
  DWORD xoffs;
  DWORD yoffs;
  DWORD xfact;
  DWORD yfact;
  DWORD rnotInd;
  MCD_pt p[1];

  int AnzPt () { return ((parSize - sizeof(*this)) / sizeof (MCD_pt)) + 1 ; }
  };
#pragma pack()

BOOL MakeContFromDec (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    MakeContFromDec_param FAR *par = (MakeContFromDec_param FAR *) param;
    fpt FAR *res = (fpt FAR *) GetGlobMem (sizeof(fpt) * par->AnzPt());
    float FAR *xoffs = (float FAR *) (c->ReadlData (par->xoffs));
    float FAR *yoffs = (float FAR *) (c->ReadlData (par->yoffs));
    float FAR *xfact = (float FAR *) (c->ReadlData (par->xfact));
    float FAR *yfact = (float FAR *) (c->ReadlData (par->yfact));
    if ((xoffs != NULL) && (yoffs != NULL) && (xfact != NULL) && (yfact != NULL)) {
      int j = 0 ;
      int notInd = c->ReadConstInt (par->rnotInd);
      for (int i = 0 ; i < par->AnzPt() ; i++) {
        DBINT FAR *f   = (DBINT FAR *)   c->ReadlData (par->p[i].fref);
        float FAR *x = (float FAR *) c->ReadlData (par->p[i].xref);
        float FAR *y = (float FAR *) c->ReadlData (par->p[i].yref);
        if ((x != NULL) && (y != NULL) && ((f == NULL) || (*f != notInd))) {
          res[j].x = *x * *xfact + *xoffs ;
          res[j].y = *y * *yfact + *yoffs ;
          j++ ;
          }
        }
      if (j > 0)
        c->WritelData (par->res,res,sizeof(*res)*j,LPSTR(par)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(par)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(par)-sizeof(WORD));
    FreeGlobMem (res);
    }
  if (mode & EM_FIXCONNECTION) {
    MakeContFromDec_param FAR *par = (MakeContFromDec_param FAR *) param;
    c->SetlConnection (par->xoffs,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yoffs,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->xfact,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yfact,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPt () ; i++) {
      c->SetlConnection (par->p[i].fref,LPSTR(param)-sizeof(WORD));
      c->SetlConnection (par->p[i].xref,LPSTR(param)-sizeof(WORD));
      c->SetlConnection (par->p[i].yref,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    MakeContFromDec_param FAR *par = (MakeContFromDec_param FAR *) param;
    c->ClearlConnection (par->xoffs,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yoffs,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->xfact,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yfact,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPt () ; i++) {
      c->ClearlConnection (par->p[i].fref,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->p[i].xref,LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->p[i].yref,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

DLLExport void _export WINAPI GetNWAddress (LPSTR,int);
#pragma pack(1)
struct GetNetWorkAddress_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetNetWorkAddress (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    char NWAddress[40];
    GetNetWorkAddress_param FAR *par = (GetNetWorkAddress_param FAR *) param;
    GetNWAddress (NWAddress,sizeof(NWAddress));
    NWAddress[NWAddress[0]+1] = '\0';
    c->WritelData (par->res,NWAddress+1,lstrlen(NWAddress+1)+1,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

DLLExport void _export WINAPI SetNWSubAddressID (LPSTR);
#pragma pack(1)
struct SetNetWorkSubAddressID_param {
  WORD  parSize;
  DWORD psSubAddressID;
  };
#pragma pack()

BOOL SetNetWorkSubAddressID (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  SetNetWorkSubAddressID_param FAR *par = (SetNetWorkSubAddressID_param FAR *)param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR subAddressID = LPSTR (c->ReadlData (par->psSubAddressID));
    SetNWSubAddressID (subAddressID) ;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->psSubAddressID, Offset);
    }
  return FALSE ;
  } //SetNetWorkSubAddressID

DLLExport BOOL _export WINAPI NWAddressStrToBin (LPVOID binAddr,int *size,LPSTR str,DBINT port);
#pragma pack(1)
struct NetWorkAddressStrToBin_param {
  WORD parSize;
  DWORD nwAddrBinObj;
  DWORD nwAddrStr;
  DWORD nwPortShort;
  };
#pragma pack()

BOOL NetWorkAddressStrToBin (mdiChild *c,LPVOID param,WORD mode)
  {
  NetWorkAddressStrToBin_param FAR *par = (NetWorkAddressStrToBin_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    char NWAddressBin[256]; // SOCKADDR_... je nach Protokoll
    int NWAddressBinLen;
    NWAddressBinLen = sizeof(NWAddressBin);
    LPSTR NWAddressStr = LPSTR (c->ReadlData (par->nwAddrStr));
    DBINT NWPort = *((DBINT *) c->ReadlData (par->nwPortShort));
    if (NWAddressStrToBin (NWAddressBin,&NWAddressBinLen,NWAddressStr,NWPort))
      c->WritelData (par->nwAddrBinObj,NWAddressBin,NWAddressBinLen,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->nwAddrBinObj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_FIXCONNECTION)) {
    c->SetlConnection (par->nwAddrStr,LPSTR (param) - sizeof(WORD));
    c->SetlConnection (par->nwPortShort,LPSTR (param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->nwAddrStr,LPSTR (param) - sizeof(WORD));
    c->ClearlConnection (par->nwPortShort,LPSTR (param) - sizeof(WORD));
    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI NWAddressBinToStr (LPSTR str,int size,DBINT *port,LPVOID binAddr);
#pragma pack(1)
struct NetWorkAddressBinToStr_param {
  WORD parSize;
  DWORD nwAddrStr;
  DWORD nwAddrBinObj;
  DWORD nwPortShort;
  BOOL MitNWPort ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL NetWorkAddressBinToStr (mdiChild *c,LPVOID param,WORD mode)
  {
    NetWorkAddressBinToStr_param FAR *par = (NetWorkAddressBinToStr_param FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    char NWAddressStr[256]; // SOCKADDR_... je nach Protokoll
    LPVOID NWAddressBin = c->ReadlData (par->nwAddrBinObj);
    DBINT NWPort;
    if (NWAddressBinToStr (NWAddressStr,sizeof(NWAddressStr),&NWPort,NWAddressBin)) {
      c->WritelData (par->nwAddrStr,NWAddressStr,lstrlen(NWAddressStr)+1,LPSTR(param)-sizeof(WORD));
      if (par->MitNWPort())
        c->WritelData (par->nwPortShort,&NWPort,sizeof(NWPort),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->nwAddrStr,LPSTR(param)-sizeof(WORD));
      if (par->MitNWPort())
        c->DellData (par->nwPortShort,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_FIXCONNECTION)) {
    c->SetlConnection (par->nwAddrBinObj,LPSTR (param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection (par->nwAddrBinObj,LPSTR (param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetScaleDateTime_param {
  WORD parSize;
  DWORD res;
  DWORD val1;
  DWORD date1;
  DWORD time1;
  DWORD val2;
  DWORD date2;
  DWORD time2;
  };
#pragma pack()

#pragma pack(1)
#ifndef SCDT_DEFINED
struct SCDT_res {
  double a ;
  double b ;
  };
#define SCDT_DEFINED
#endif
#pragma pack()

INTTIME GetFulltime (mdiChild *c,DWORD d,DWORD t,BOOL FAR *done)
  {
  packdate FAR *d1 = (packdate FAR *) c->ReadlData (d);
  packtime FAR *t1 = (packtime FAR *) c->ReadlData (t);
  INTTIME res = 0.0;
  if ((d1 != NULL) && (t1 != NULL)) {
    res = PackTime (d1);
    res += INTTIME (LONG(t1->hour) * 3600L + LONG(t1->minute) * 60L + LONG(t1->second));
    *done = TRUE ;
    }
  else
    *done = FALSE ;
  return res;
  }

BOOL GetScaleDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    BOOL done1,done2;
    GetScaleDateTime_param FAR *par = (GetScaleDateTime_param FAR *) param;
    INTTIME t1 = GetFulltime (c,par->date1,par->time1,&done1);
    INTTIME t2 = GetFulltime (c,par->date2,par->time2,&done2);
    float FAR *v1 = (float FAR *) c->ReadlData (par->val1);
    float FAR *v2 = (float FAR *) c->ReadlData (par->val2);
    if ((done1) && (done2) && (v1 != NULL) && (v2 != NULL) && (t1 != t2)) {
      SCDT_res res ;
      res.b = (double (*v1) - double(*v2)) / (t1 - t2) ;
      res.a = double(*v1) - res.b * t1;
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetScaleDateTime_param FAR *par = (GetScaleDateTime_param FAR *) param;
    c->SetlConnection (par->val1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->val2,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->date1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->date2,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->time1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->time2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetScaleDateTime_param FAR *par = (GetScaleDateTime_param FAR *) param;
    c->ClearlConnection (par->val1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->val2,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->date1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->date2,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->time1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->time2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ScaleDateTime_param {
  WORD parSize;
  DWORD res;
  DWORD sc;
  DWORD date;
  DWORD time;
  };
#pragma pack()

BOOL ScaleDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ScaleDateTime_param FAR *par = (ScaleDateTime_param FAR *) param;
    BOOL done;
    INTTIME t = GetFulltime (c,par->date,par->time,&done);
    SCDT_res FAR *sc = (SCDT_res FAR *) c->ReadlData (par->sc);
    if ((done) && (sc != NULL)) {
      float res = float(sc->a + sc->b * t);
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ScaleDateTime_param FAR *par = (ScaleDateTime_param FAR *) param;
    c->SetlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->date,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->time,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ScaleDateTime_param FAR *par = (ScaleDateTime_param FAR *) param;
    c->ClearlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->date,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->time,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

inline LONG ROUNDLONG(INTTIME t)
  {
  return LONG(t + 0.5);
  }

inline void INTTIME2packtime(INTTIME t, packtime FAR *pt)
  {
  pt->hour   = BYTE(ROUNDLONG(t) / (60L * 60L)) ;
  t -= LONG(pt->hour) * 60L * 60L ;
  pt->minute = BYTE(ROUNDLONG(t) / 60L) ;
  t -= LONG(pt->minute) * 60L ;
  pt->second = BYTE(ROUNDLONG(t)) ;
  pt->hundred_second = 0;
  }

#pragma pack(1)
struct UnScaleDateTime_param {
  WORD parSize;
  DWORD date;
  DWORD time;
  DWORD sc;
  DWORD res;
  };
#pragma pack()

BOOL UnScaleDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    UnScaleDateTime_param FAR *par = (UnScaleDateTime_param FAR *) param;
    float FAR *res = (float FAR *) c->ReadlData (par->res);
    SCDT_res FAR *sc = (SCDT_res FAR *) c->ReadlData (par->sc);
    if ((res != NULL) && (sc != NULL)) {
      INTTIME t = (*res - sc->a) / sc->b ;
      packdate pd;
      UnPackTime (t,&pd);
      INTTIME dt = t - PackTime (&pd);
      packtime pt;
#ifdef UEBERLEGT
      pt.hour = BYTE(dt / 3600) ;
      dt -= LONG(pt.hour) * 3600 ;
      pt.minute = BYTE(dt / 60) ;
      dt -= LONG(pt.minute) * 60 ;
      pt.second = BYTE (dt);
      pt.hundred_second = 0;
#endif
      INTTIME2packtime(dt,&pt);
      c->WritelData (par->date,&pd,sizeof(pd),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->time,&pt,sizeof(pt),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->date,LPSTR(param)-sizeof(WORD));
      c->DellData (par->time,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    UnScaleDateTime_param FAR *par = (UnScaleDateTime_param FAR *) param;
    c->SetlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    UnScaleDateTime_param FAR *par = (UnScaleDateTime_param FAR *) param;
    c->ClearlConnection (par->sc,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR uGetDevString_param {
  WORD parSize;
  DWORD res;
  DWORD val;
  DWORD norm;
  DWORD dev;
  DWORD unknown;
  DWORD str[1];

  int AnzStr ()
    { return (parSize - sizeof(*this)) / sizeof (str[0]) + 1 ; }
  };
#pragma pack()

BOOL uGetDevString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uGetDevString_param FAR *par = (uGetDevString_param FAR *) param;
    float FAR *val = (float FAR *) c->ReadlData (par->val);
    float FAR *norm = (float FAR *) c->ReadlData (par->norm);
    float FAR *dev = (float FAR *) c->ReadlData (par->dev);
    if ((val != NULL) && (norm != NULL) && (dev != NULL) &&
        (*dev > float(1.0E-3))) {
      double ddev = (*val - *norm) / double(*dev);
      int AnzAbw = par->AnzStr();
      int abw = ((ddev < 0.0) ? ( - int(- ddev)) : int (ddev)) + (AnzAbw / 2);
      abw = max(0,min(abw,AnzAbw-1));
      LPSTR str = (LPSTR)c->ReadlData (par->str[abw]);
      if (str != NULL)
        c->WritelData (par->res,str,GetBlockSize(str),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else {
      LPSTR unknown = (LPSTR)c->ReadlData (par->unknown);
      if (unknown != NULL)
        c->WritelData (par->res,unknown,GetBlockSize(unknown),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    uGetDevString_param FAR *par = (uGetDevString_param FAR *) param;
    c->SetlConnection (par->val,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->norm,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dev,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->unknown,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzStr() ; i++)
      c->SetlConnection (par->str[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uGetDevString_param FAR *par = (uGetDevString_param FAR *) param;
    c->ClearlConnection (par->val,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->norm,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dev,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->unknown,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzStr() ; i++)
      c->ClearlConnection (par->str[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct uDiffDateTime_param {
  WORD parSize;
  DWORD anzTage;
  DWORD diffTime;
  DWORD d1;
  DWORD t1;
  DWORD d2;
  DWORD t2;
  };
#pragma pack()
BOOL uDiffDateTimeIntern (mdiChild *c,LPVOID param,WORD mode,BOOL asLong)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uDiffDateTime_param FAR *par = (uDiffDateTime_param FAR *) param ;
    packdate FAR *d1 = (packdate FAR *) c->ReadlData (par->d1);
    packdate FAR *d2 = (packdate FAR *) c->ReadlData (par->d2);
    packtime FAR *t1 = (packtime FAR *) c->ReadlData (par->t1);
    packtime FAR *t2 = (packtime FAR *) c->ReadlData (par->t2);
    if ((d1 != NULL) && (d2 != NULL) && (t1 != NULL) && (t2 != NULL)) {
      INTTIME ta1 = PackTime (d1) + LONG(t1->hour) * 60L * 60L + LONG(t1->minute) * 60L + LONG(t1->second) ;
      INTTIME ta2 = PackTime (d2) + LONG(t2->hour) * 60L * 60L + LONG(t2->minute) * 60L + LONG(t2->second) ;
      INTTIME dt = ta1 - ta2;
      LONG AnzDays = LONG ((dt + ((dt >= 0) ? 0.5 : -0.5)) / (60L * 60L * 24L)) ;
      dt -= AnzDays * 60L * 60L * 24L ;
      packtime dtt ;
      INTTIME2packtime(dt,&dtt);
      if (asLong)
        c->WritelData (par->anzTage,&AnzDays,sizeof(AnzDays),LPBYTE(param) - sizeof(WORD));
      else {
        DBINT AnzDaysShort = (DBINT) AnzDays;
        c->WritelData (par->anzTage,&AnzDaysShort,sizeof(AnzDaysShort),LPBYTE(param) - sizeof(WORD));
        }
      c->WritelData (par->diffTime,&dtt,sizeof(dtt),LPBYTE(param) - sizeof(WORD));
      }
    else {
      c->DellData (par->anzTage,LPBYTE(param) - sizeof(WORD));
      c->DellData (par->diffTime,LPBYTE(param) - sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    uDiffDateTime_param FAR *par = (uDiffDateTime_param FAR *) param ;
    c->SetlConnection (par->d1,LPBYTE(param) - sizeof(WORD));
    c->SetlConnection (par->d2,LPBYTE(param) - sizeof(WORD));
    c->SetlConnection (par->t1,LPBYTE(param) - sizeof(WORD));
    c->SetlConnection (par->t2,LPBYTE(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uDiffDateTime_param FAR *par = (uDiffDateTime_param FAR *) param ;
    c->ClearlConnection (par->d1,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->d2,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->t1,LPBYTE(param) - sizeof(WORD));
    c->ClearlConnection (par->t2,LPBYTE(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL uDiffDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  return uDiffDateTimeIntern (c,param,mode,FALSE);
  }

BOOL uDiffDateTimeLong (mdiChild *c,LPVOID param,WORD mode)
  {
  return uDiffDateTimeIntern (c,param,mode,TRUE);
  }

#pragma pack(1)
struct uAddDateTime_param {
  WORD parSize;
  DWORD dres;
  DWORD tres;
  DWORD d1;
  DWORD t1;
  DWORD anzTage;
  DWORD diffTime;
  };
#pragma pack()
BOOL uAddDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uAddDateTime_param FAR *par = (uAddDateTime_param FAR *) param ;
    packdate FAR *d1 = (packdate FAR *) c->ReadlData (par->d1);
    packtime FAR *t1 = (packtime FAR *) c->ReadlData (par->t1);
    DBINT FAR *at = (DBINT FAR *) c->ReadlData (par->anzTage);
    packtime FAR *dt = (packtime FAR *) c->ReadlData (par->diffTime);
    if ((d1 != NULL) && (at != NULL) && (t1 != NULL) && (dt != NULL)) {
      INTTIME ta1 = PackTime (d1) + LONG(t1->hour) * 60L * 60L + LONG(t1->minute) * 60L + LONG(t1->second) ;
      INTTIME ta2 = LONG(*at) * 60L * 60L * 24L + LONG(dt->hour) * 60L * 60L + LONG(dt->minute) * 60L + LONG(dt->second) ;
      INTTIME t = ta1 + ta2 ;
      packdate dres;
      UnPackTime (t,&dres);
      t -= PackTime (&dres);
      packtime tres ;
#ifdef UEBERLEGT
      tres.hour   = BYTE(t / (60L * 60L)) ;
      t -= LONG(tres.hour) * 60L * 60L ;
      tres.minute = BYTE(t / 60L) ;
      t -= LONG(tres.minute) * 60L ;
      tres.second = BYTE(t) ;
      tres.hundred_second = 0;
#endif
      INTTIME2packtime(t,&tres);
      c->WritelData (par->dres,&dres,sizeof(dres),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->tres,&tres,sizeof(tres),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->dres,LPSTR(param)-sizeof(WORD));
      c->DellData (par->tres,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    uAddDateTime_param FAR *par = (uAddDateTime_param FAR *) param ;
    c->SetlConnection (par->d1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->t1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->anzTage,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->diffTime,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uAddDateTime_param FAR *par = (uAddDateTime_param FAR *) param ;
    c->ClearlConnection (par->d1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->t1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->anzTage,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->diffTime,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct bIsInIntervall_param {
  WORD parSize;
  DWORD dVar;
  DWORD tVar;
  DWORD sDate;
  DWORD sTime;
  DWORD eDate;
  DWORD eTime;
  DWORD isTime;
  DWORD ieTime;
  DWORD pAnzDays;
  DWORD pTime;
  };
#pragma pack()

extern LPVOID GetLastOffset (void);
BOOL bIsInIntervall (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bIsInIntervall_param FAR *par = (bIsInIntervall_param FAR *) param ;
    packdate FAR * dVar = (packdate FAR *) c->ReadlData (par->dVar);
    packtime FAR * tVar = (packtime FAR *) c->ReadlData (par->tVar);
    packdate FAR * sDate = (packdate FAR *) c->ReadlData (par->sDate);
    packtime FAR * sTime = (packtime FAR *) c->ReadlData (par->sTime);
    packdate FAR * eDate = (packdate FAR *) c->ReadlData (par->eDate);
    packtime FAR * eTime = (packtime FAR *) c->ReadlData (par->eTime);
    packtime FAR * isTime = (packtime FAR *) c->ReadlData (par->isTime);
    packtime FAR * ieTime = (packtime FAR *) c->ReadlData (par->ieTime);
    DBINT    FAR * pAnzDays = (DBINT  FAR *) c->ReadlData (par->pAnzDays);
    packtime FAR * pTime = (packtime FAR *) c->ReadlData (par->pTime);
    if ((dVar != NULL) &&
        (tVar != NULL) &&
        (sDate != NULL) &&
        (sTime != NULL) &&
        (eDate != NULL) &&
        (eTime != NULL) &&
        (isTime != NULL) &&
        (ieTime != NULL) &&
        (pAnzDays != NULL) &&
        (pTime != NULL)) {
      INTTIME t = PackTime (dVar) + LONG(tVar->hour) * 60L * 60L + LONG(tVar->minute) * 60L + LONG(tVar->second) ;
      INTTIME ts = PackTime (sDate) + LONG(sTime->hour) * 60L * 60L + LONG(sTime->minute) * 60L + LONG(sTime->second) ;
      INTTIME te = PackTime (eDate) + LONG(eTime->hour) * 60L * 60L + LONG(eTime->minute) * 60L + LONG(eTime->second) ;
      INTTIME tis = PackTime (sDate) + LONG(isTime->hour) * 60L * 60L + LONG(isTime->minute) * 60L + LONG(isTime->second) ;
      INTTIME tes = PackTime (sDate) + LONG(ieTime->hour) * 60L * 60L + LONG(ieTime->minute) * 60L + LONG(ieTime->second) ;
      if (tes < tis) tes += INTTIME (24L * 60L * 60L) ;
      INTTIME dt = INTTIME (*pAnzDays) * INTTIME (24L * 60L * 60L + LONG(pTime->hour) * 60L * 60L + LONG(pTime->minute) * 60L) + INTTIME (pTime->second) ;

      if ((t >= ts) && (t >= tis) && (t <= te)) {
        INTTIME iP = (t - tis) / dt ;
        res = ((t >= tis + iP * dt) && (t <= tes + iP * dt)) ;
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    bIsInIntervall_param FAR *par = (bIsInIntervall_param FAR *) param ;
    c->SetlConnection (par->dVar,GetLastOffset()) ;
    c->SetlConnection (par->tVar,GetLastOffset()) ;
    c->SetlConnection (par->sDate,GetLastOffset()) ;
    c->SetlConnection (par->sTime,GetLastOffset()) ;
    c->SetlConnection (par->eDate,GetLastOffset()) ;
    c->SetlConnection (par->eTime,GetLastOffset()) ;
    c->SetlConnection (par->isTime,GetLastOffset()) ;
    c->SetlConnection (par->ieTime,GetLastOffset()) ;
    c->SetlConnection (par->pAnzDays,GetLastOffset()) ;
    c->SetlConnection (par->pTime,GetLastOffset()) ;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    bIsInIntervall_param FAR *par = (bIsInIntervall_param FAR *) param ;
    c->ClearlConnection (par->dVar,GetLastOffset()) ;
    c->ClearlConnection (par->tVar,GetLastOffset()) ;
    c->ClearlConnection (par->sDate,GetLastOffset()) ;
    c->ClearlConnection (par->sTime,GetLastOffset()) ;
    c->ClearlConnection (par->eDate,GetLastOffset()) ;
    c->ClearlConnection (par->eTime,GetLastOffset()) ;
    c->ClearlConnection (par->isTime,GetLastOffset()) ;
    c->ClearlConnection (par->ieTime,GetLastOffset()) ;
    c->ClearlConnection (par->pAnzDays,GetLastOffset()) ;
    c->ClearlConnection (par->pTime,GetLastOffset()) ;
    }
  return res ;
  }

#pragma pack(1)
struct GetIntervallBorders_param {
  WORD parSize;
  DWORD d1res;
  DWORD t1res;
  DWORD d2res;
  DWORD t2res;
  DWORD dVar;
  DWORD tVar;
  DWORD sDate;
  DWORD sTime;
  DWORD eDate;
  DWORD eTime;
  DWORD isTime;
  DWORD ieTime;
  DWORD pAnzDays;
  DWORD pTime;
  };
#pragma pack()

void WriteDateTime (DWORD pdres,DWORD ptres,INTTIME  t,LPVOID param,mdiChild *c)
   {
   packdate dres;
   UnPackTime (t,&dres);
   t -= PackTime (&dres);
   packtime tres ;
#ifdef UEBERLEGT
   tres.hour   = BYTE(t / (60L * 60L)) ;
   t -= INTTIME (tres.hour) * 60L * 60L ;
   tres.minute = BYTE(t / 60L) ;
   t -= INTTIME (tres.minute) * 60L ;
   tres.second = BYTE(t) ;
   tres.hundred_second = 0;
#endif
   INTTIME2packtime(t,&tres);
   c->WritelData (pdres,&dres,sizeof(dres),LPSTR(param)-sizeof(WORD));
   c->WritelData (ptres,&tres,sizeof(tres),LPSTR(param)-sizeof(WORD));
   }

BOOL GetIntervallBorders (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetIntervallBorders_param FAR *par = (GetIntervallBorders_param FAR *) param ;
    packdate FAR * dVar = (packdate FAR *) c->ReadlData (par->dVar);
    packtime FAR * tVar = (packtime FAR *) c->ReadlData (par->tVar);
    packdate FAR * sDate = (packdate FAR *) c->ReadlData (par->sDate);
    packtime FAR * sTime = (packtime FAR *) c->ReadlData (par->sTime);
    packdate FAR * eDate = (packdate FAR *) c->ReadlData (par->eDate);
    packtime FAR * eTime = (packtime FAR *) c->ReadlData (par->eTime);
    packtime FAR * isTime = (packtime FAR *) c->ReadlData (par->isTime);
    packtime FAR * ieTime = (packtime FAR *) c->ReadlData (par->ieTime);
    DBINT    FAR * pAnzDays = (DBINT  FAR *) c->ReadlData (par->pAnzDays);
    packtime FAR * pTime = (packtime FAR *) c->ReadlData (par->pTime);
    if ((dVar != NULL) &&
        (tVar != NULL) &&
        (sDate != NULL) &&
        (sTime != NULL) &&
        (eDate != NULL) &&
        (eTime != NULL) &&
        (isTime != NULL) &&
        (ieTime != NULL) &&
        (pAnzDays != NULL) &&
        (pTime != NULL)) {
      INTTIME t = PackTime (dVar) + LONG(tVar->hour) * 60L * 60L + LONG(tVar->minute) * 60L + LONG(tVar->second) ;
      INTTIME ts = PackTime (sDate) + LONG(sTime->hour) * 60L * 60L + LONG(sTime->minute) * 60L + LONG(sTime->second) ;
      INTTIME te = PackTime (eDate) + LONG(eTime->hour) * 60L * 60L + LONG(eTime->minute) * 60L + LONG(eTime->second) ;
      INTTIME tis = PackTime (sDate) + LONG(isTime->hour) * 60L * 60L + LONG(isTime->minute) * 60L + LONG(isTime->second) ;
      INTTIME tes = PackTime (sDate) + LONG(ieTime->hour) * 60L * 60L + LONG(ieTime->minute) * 60L + LONG(ieTime->second) ;
      if (tes < tis) tes += INTTIME (24L * 60L * 60L) ;
      INTTIME dt = INTTIME (*pAnzDays) * INTTIME (24L * 60L * 60L + LONG(pTime->hour) * 60L * 60L + LONG(pTime->minute) * 60L) + INTTIME (pTime->second) ;

      INTTIME iP = floorl(INTTIME (t - tis) / INTTIME (dt)) ;
      INTTIME t1 = tis + dt * iP ;
      INTTIME t2 = tes + dt * iP ;

      WriteDateTime (par->d1res,par->t1res,t1,param,c);
      WriteDateTime (par->d2res,par->t2res,t2,param,c);
      }
    else {
      c->DellData (par->d1res,LPSTR(param)-sizeof(WORD));
      c->DellData (par->t1res,LPSTR(param)-sizeof(WORD));
      c->DellData (par->d2res,LPSTR(param)-sizeof(WORD));
      c->DellData (par->t2res,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    GetIntervallBorders_param FAR *par = (GetIntervallBorders_param FAR *) param ;
    c->SetlConnection (par->dVar,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->tVar,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->sDate,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->sTime,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->eDate,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->eTime,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->isTime,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->ieTime,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->pAnzDays,LPSTR(param)-sizeof(WORD)) ;
    c->SetlConnection (par->pTime,LPSTR(param)-sizeof(WORD)) ;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetIntervallBorders_param FAR *par = (GetIntervallBorders_param FAR *) param ;
    c->ClearlConnection (par->dVar,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->tVar,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->sDate,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->sTime,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->eDate,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->eTime,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->isTime,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->ieTime,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->pAnzDays,LPSTR(param)-sizeof(WORD)) ;
    c->ClearlConnection (par->pTime,LPSTR(param)-sizeof(WORD)) ;
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFormatBaseHeight_param {
  WORD parSize;
  DWORD res;
  DWORD f;
  };
#pragma pack()
BOOL GetFormatBaseHeight(mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetFormatBaseHeight_param FAR *par = (GetFormatBaseHeight_param FAR *) param;
    DBINT FAR *lpFormat = (DBINT FAR *) c->ReadlData (par->f);
    if (lpFormat != NULL) {
      LPFORMATMETRIC lpfm = GetFormatMetrics (c->OutWnd(),MAPTYPE_TYPOGRAPHIC,*lpFormat);
      float h = float(lpfm->yBaseHeight) ;
      c->WritelData (par->res,&h,sizeof(h),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetFormatBaseHeight_param FAR *par = (GetFormatBaseHeight_param FAR *) param;
    c->SetlConnection (par->f,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetFormatBaseHeight_param FAR *par = (GetFormatBaseHeight_param FAR *) param;
    c->ClearlConnection (par->f,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL useFeierTageOesterreich = TRUE;
hash FAR *FeierTagHash = NULL; // Hash-Tabelle aller (zusaetzlichen) Feiertage

#pragma pack(1)
struct ClearFeierTage_param {
  WORD parSize;
  DWORD useOesterreich;
  };
#pragma pack()

BOOL ClearFeierTage (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ClearFeierTage_param FAR *par = (ClearFeierTage_param FAR *) param ;
    DBBOOL FAR *useOesterreich = (DBBOOL FAR *) c->ReadlData (par->useOesterreich);
    useFeierTageOesterreich = *useOesterreich;
    if (FeierTagHash != NULL) {
      delete FeierTagHash;
      FeierTagHash = NULL;
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ClearFeierTage_param FAR *par = (ClearFeierTage_param FAR *) param ;
    c->ClearlConnection (par->useOesterreich,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFeierTag_param {
  WORD parSize;
  DWORD date;
  };
#pragma pack()

BOOL SetFeierTag (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetFeierTag_param FAR *par = (SetFeierTag_param FAR *)param ;
    packdate FAR *pd = (packdate FAR *) c->ReadlData (par->date);
    if (pd != NULL) {
      if (FeierTagHash == NULL)
        FeierTagHash = new hash (1009, VOIDKEY);
      FeierTagHash->SetDatav (pd, pd, sizeof(*pd), sizeof(*pd)); // Schluessel = Daten
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetFeierTag_param FAR *par = (SetFeierTag_param FAR *)param ;
    c->ClearlConnection (par->date,GetLastOffset ());
    }
  return FALSE ;
  }

#pragma pack(1)
struct IstFeierTag_param {
  WORD parSize;
  DWORD date;
  };
#pragma pack()

extern DLLExport LONG _export WINAPI JulianDays (packdate FAR *pd);
extern DLLExport LONG _export WINAPI WievielterTagIstAschermittwoch (int jahr);
BOOL IstFeierTag (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    IstFeierTag_param FAR *par = (IstFeierTag_param FAR *)param ;
    packdate FAR *pd = (packdate FAR *) c->ReadlData (par->date);
    if (pd != NULL) {
      if (useFeierTageOesterreich) {
        if (((pd->month == 1) && (pd->day == 1)) ||
            ((pd->month == 1) && (pd->day == 6)) ||
            ((pd->month == 5) && (pd->day == 1)) ||
            ((pd->month == 8) && (pd->day == 15)) ||
            ((pd->month == 10) && (pd->day == 26)) ||
            ((pd->month == 11) && (pd->day == 1)) ||
            ((pd->month == 12) && (pd->day == 8)) ||
            ((pd->month == 12) && (pd->day == 25)) ||
            ((pd->month == 12) && (pd->day == 26)))
          res = TRUE ;
        else {
          packdate tr = *pd;
          LONG julian = JulianDays (&tr);
          tr.month = 1 ;
          tr.day = 1 ;
          julian =
            (julian - JulianDays (&tr)) -
            WievielterTagIstAschermittwoch (tr.year) + 1 ;
          if ((julian == 46) ||
              (julian == 47) ||
              (julian == 85) ||
              (julian == 95) ||
              (julian == 96) ||
              (julian == 106))
            res = TRUE ;
          }
        }
      if (!res && (FeierTagHash != NULL)) {
        packdate FAR *foundPd = (packdate FAR *) (FeierTagHash->GetDatav (pd, sizeof(*pd)));
        if (foundPd != NULL)
          res = TRUE;
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    IstFeierTag_param FAR *par = (IstFeierTag_param FAR *)param ;
    c->SetlConnection (par->date,GetLastOffset ());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    IstFeierTag_param FAR *par = (IstFeierTag_param FAR *)param ;
    c->ClearlConnection (par->date,GetLastOffset ());
    }
  return res;
  }

#pragma pack(1)
struct GenerateVector_param {
  WORD parSize;
  DWORD Vektor;
  DWORD list;
  DWORD elem;
  };
#pragma pack()

LPDBRECORD GetRecordWithList (LPVOID list,LPDBRECORD h,mdiChild *c,WORD FAR *TableInd);
BOOL GenerateVector (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GenerateVector_param FAR *par = (GenerateVector_param FAR *) param ;
    LPVOID list = c->ReadlData (par->list);
    WORD ti ;
    LPVOID res = NULL ;
    int Size ;
    for ( LPDBRECORD h = GetRecordWithList (list,NULL,c,&ti) ;
          h != NULL ;
          h = GetRecordWithList (list,h,c,&ti)
        ) {
      DBWIN_ASSERT (LOWORD(par->elem) == ti);
      LPVOID data = h->Get (HIWORD(par->elem));
      if (data != NULL) {
        if (res == NULL) {
          res = GetGlobMem (sizeof(short));
          *((short FAR *) res) = GetBlockSize(data) ;
          Size = GetBlockSize(data);
          }
        DBWIN_ASSERT (Size == int(GetBlockSize(data)));
        LPVOID n = GetGlobMem (GetBlockSize(res) + Size) ;
        lmemcpy (n,res,GetBlockSize(res));
        lmemcpy (LPSTR(n) + GetBlockSize(res),data,Size);
        FreeGlobMem(res);
        res = n ;
        }
      }
    if (res != NULL) {
      c->WritelData (par->Vektor,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->Vektor,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GenerateVector_param FAR *par = (GenerateVector_param FAR *) param ;
    c->SetlConnection (par->list,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GenerateVector_param FAR *par = (GenerateVector_param FAR *) param ;
    c->ClearlConnection (par->list,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct UnionVektor_param {
  WORD parSize;
  DWORD vres;
  DWORD v1;
  DWORD v2;
  };
#pragma pack()
inline LPVOID VektorElem (LPVOID v,int i)
  {
  return (LPSTR(v) + sizeof(short) + i * *((short FAR *) v)) ;
  }
BOOL InVektor (LPVOID v,LPVOID d)
  {
  short Size = *((short FAR *) v) ;
  int Count = (GetBlockSize(v) - sizeof(short)) / Size ;
  for (int i = 0 ; i < Count ; i++) {
    if (lmemcmp (VektorElem(v,i),d,Size)) return TRUE ;
    }
  return FALSE ;
  }

BOOL UnionVektor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    UnionVektor_param FAR *par = (UnionVektor_param FAR *) param ;
    LPVOID v1 = c->ReadlData (par->v1);
    LPVOID v2 = c->ReadlData (par->v2);
    LPVOID res = NULL ;
    if (v1 != NULL) {
      res = GetGlobMem (GetBlockSize (v1)) ;
      lmemcpy (res,v1,GetBlockSize(v1));
      }
    if (v2 != NULL) {
      short Size = *((short FAR *) v2) ;
      if (res != NULL) {
        DBWIN_ASSERT (Size == *((short FAR *) res)) ;
        int Count = (GetBlockSize(v2) - sizeof(short)) / Size ;
        for (int i = 0 ; i < Count ; i++) {
          LPVOID d = VektorElem(v2,i) ;
          if (!InVektor (res,d)) {
            LPVOID n = GetGlobMem (GetBlockSize(res) + Size) ;
            lmemcpy (n,res,GetBlockSize(res));
            lmemcpy (LPSTR(n) + GetBlockSize(res),d,Size);
            FreeGlobMem(res);
            res = n ;
            }
          }
        }
      else {
        res = GetGlobMem (GetBlockSize (v2)) ;
        lmemcpy (res,v2,GetBlockSize(v2));
        }
      }
    if (res != NULL) {
      c->WritelData (par->vres,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->vres,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    UnionVektor_param FAR *par = (UnionVektor_param FAR *) param ;
    c->SetlConnection (par->v1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->v2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    UnionVektor_param FAR *par = (UnionVektor_param FAR *) param ;
    c->ClearlConnection (par->v1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->v2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct IntersectionVektor_param {
  WORD parSize;
  DWORD vres;
  DWORD v1;
  DWORD v2;
  };
#pragma pack()
BOOL IntersectionVektor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    IntersectionVektor_param FAR *par = (IntersectionVektor_param FAR *) param ;
    LPVOID v1 = c->ReadlData (par->v1);
    LPVOID v2 = c->ReadlData (par->v2);
    LPVOID res = NULL ;
    if ((v1 != NULL) && (v2 != NULL)) {
      short Size = *((short FAR *) v1) ;
      DBWIN_ASSERT (Size == *((short FAR *) v2)) ;
      int Count1 = (GetBlockSize(v1) - sizeof(short)) / Size ;
      int Count2 = (GetBlockSize(v2) - sizeof(short)) / Size ;
      if (Count1 > Count2) {
        LPVOID vChange = v1 ; v1 = v2 ; v2 = vChange ;
        int cChange = Count1 ; Count1 = Count2 ; Count2 = cChange ;
        }
      for (int i = 0 ; i < Count1 ; i++) {
        LPVOID d = VektorElem(v1, i) ;
        if (InVektor (v2, d)) {
          if (res == NULL) {
            res = GetGlobMem (sizeof(short) + Size) ;
            *((short FAR *) res) = Size ;
            lmemcpy (LPSTR(res) + sizeof(short),d,Size);
            }
          else {
            LPVOID n = GetGlobMem (GetBlockSize(res) + Size) ;
            lmemcpy (n,res,GetBlockSize(res));
            lmemcpy (LPSTR(n) + GetBlockSize(res),d,Size);
            FreeGlobMem(res);
            res = n ;
            }
          }
        }
      }
    if (res != NULL) {
      c->WritelData (par->vres,res,GetBlockSize(res),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->vres,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    IntersectionVektor_param FAR *par = (IntersectionVektor_param FAR *) param ;
    c->SetlConnection (par->v1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->v2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    IntersectionVektor_param FAR *par = (IntersectionVektor_param FAR *) param ;
    c->ClearlConnection (par->v1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->v2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct bVektorInProd_param {
  WORD parSize;
  DWORD v1;
  DWORD v2;
  };
#pragma pack()
BOOL bVektorInProd (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bVektorInProd_param FAR *par = (bVektorInProd_param FAR *) param ;
    LPVOID v1 = c->ReadlData (par->v1);
    LPVOID v2 = c->ReadlData (par->v2);
    if ((v1 != NULL) && (v2 != NULL)) {
      short Size = *((short FAR *) v2) ;
      DBWIN_ASSERT (*((short FAR *) v2) == *((short FAR *) v1)) ;
      int c2 = (GetBlockSize(v2) - sizeof(short)) / Size ;
      for (int i = 0 ; ((i < c2) && (!res)) ; i++) {
        LPVOID d = VektorElem(v2,i) ;
        if (InVektor (v1,d)) res = TRUE ;
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    bVektorInProd_param FAR *par = (bVektorInProd_param FAR *) param ;
    c->SetlConnection (par->v1,GetLastOffset());
    c->SetlConnection (par->v2,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    bVektorInProd_param FAR *par = (bVektorInProd_param FAR *) param ;
    c->ClearlConnection (par->v1,GetLastOffset());
    c->ClearlConnection (par->v2,GetLastOffset());
    }
  return res ;
  }

#pragma pack(1)
struct bVektorTeilmenge_param {
  WORD parSize;
  DWORD v1;
  DWORD v2;
  };
#pragma pack()
BOOL bVektorTeilmenge (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bVektorTeilmenge_param FAR *par = (bVektorTeilmenge_param FAR *) param ;
    LPVOID v1 = c->ReadlData (par->v1);
    LPVOID v2 = c->ReadlData (par->v2);
    if ((v1 != NULL) && (v2 != NULL)) {
      short Size = *((short FAR *) v1) ;
      DBWIN_ASSERT (Size == *((short FAR *) v2)) ;
      int c1 = (GetBlockSize(v1) - sizeof(short)) / Size ;
      int c2 = (GetBlockSize(v2) - sizeof(short)) / Size ;
      if (c1 <= c2) {
        res = TRUE;
        for (int i = 0 ; ((i < c1) && res) ; i++) {
          LPVOID d = VektorElem(v1, i) ;
          if (!InVektor (v2,d)) res = FALSE ;
          }
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    bVektorTeilmenge_param FAR *par = (bVektorTeilmenge_param FAR *) param ;
    c->SetlConnection (par->v1,GetLastOffset());
    c->SetlConnection (par->v2,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    bVektorTeilmenge_param FAR *par = (bVektorTeilmenge_param FAR *) param ;
    c->ClearlConnection (par->v1,GetLastOffset());
    c->ClearlConnection (par->v2,GetLastOffset());
    }
  return res ;
  }

#pragma pack(1)
struct BitCount_param {
  WORD parSize;
  DWORD res ;
  DWORD l;
  };
#pragma pack()
BOOL BitCount (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    BitCount_param FAR *par = (BitCount_param FAR *) param ;
    DWORD FAR *l = (DWORD FAR *) c->ReadlData (par->l);
    if (l != NULL) {
      int count = 0;
      DWORD mask = 1L ;
      for (int i = 0 ; i < 32 ; i++) {
        if (((*l) & mask) != 0L) count ++ ;
        mask = mask << 1 ;
        }
      c->WritelData (par->res,&count,sizeof(count),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    BitCount_param FAR *par = (BitCount_param FAR *) param ;
    c->SetlConnection (par->l,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    BitCount_param FAR *par = (BitCount_param FAR *) param ;
    c->ClearlConnection (par->l,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct StatFunc_param FAR {
  WORD parSize;
  DWORD res;
  DWORD func ;
  DWORD p[1] ;
  };
#pragma pack()
#define STATMIN     0
#define STATMAX     1
#define STATSUM     2
#define STATCOUNT   3
#define STATAVG     4
#define STATSTDABW  5
#define STATIN      6
BOOL StatFunc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    StatFunc_param FAR *par = (StatFunc_param FAR *) param ;
    int anzArgs = (par->parSize - (sizeof(*par) - sizeof(DWORD))) / sizeof(DWORD);
    DBINT FAR *func = (DBINT FAR *) (c->ReadlData (par->func));
    DBWIN_ASSERT (func != NULL) ;

    float res;
    BOOL doIt = FALSE ;
    if (*func == STATMIN) {
      res = float (1.0E10) ;
      for (int i = 0 ; i < anzArgs ; i++) {
        float FAR *h = (float FAR *) c->ReadlData (par->p[i]);
        if ((h != NULL) && (*h < res)) {
          res = *h ;
          doIt = TRUE ;
          }
        }
      }
    else if (*func == STATMAX) {
      res = float (-1.0E10) ;
      for (int i = 0 ; i < anzArgs ; i++) {
        float FAR *h = (float FAR *) c->ReadlData (par->p[i]);
        if ((h != NULL) && (*h > res)) {
          res = *h ;
          doIt = TRUE ;
          }
        }
      }
    else if (*func == STATIN) {
      // Die ersten 2 Zahlen sind die Grenzen
      if (anzArgs > 2) {
        float FAR *u = (float FAR *) c->ReadlData (par->p[0]);
        float FAR *o = (float FAR *) c->ReadlData (par->p[1]);
        if ((u != NULL) && (o != NULL)) {
          res = float (0.0) ;
          for (int i = 2 ; i < anzArgs ; i++) {
            float FAR *h = (float FAR *) c->ReadlData (par->p[i]);
            if ((h != NULL) && (*h > res) && (*h >= *u) && (*h <= *o)) {
              res = res + float(1.0) ;
              doIt = TRUE ;
              }
            }
          }
        }
      }
    else if ((*func == STATCOUNT) || 
             (*func == STATSUM) || 
             (*func == STATAVG) || 
             (*func == STATSTDABW)) {
      float sum = float(0.0);
      float count = float(0.0);
      for (int i = 0 ; i < anzArgs ; i++) {
        float FAR *h = (float FAR *) c->ReadlData (par->p[i]);
        if (h != NULL) {
          sum += *h ;
          count += float (1.0);
          doIt = TRUE ;
          }
        }
      if (doIt) {
        if (*func == STATAVG) res = sum / count ;
        else if (*func == STATSUM) res = sum ;
        else if (*func == STATCOUNT) res = count ;
        else if (*func == STATSTDABW) {
          float avg = sum / count;
          sum = float (0.0) ;
          for (int i = 0 ; i < anzArgs ; i++) {
            float FAR *h = (float FAR *) c->ReadlData (par->p[i]);
            if (h != NULL) {
              sum += (*h - avg) * (*h - avg) ;
              }
            }
          res = float (sqrt (sum / count)) ;
          }
        }
      }

    float FAR *old = (float FAR *) c->TryToReadData (par->res);
    if (doIt && ((old == NULL) || 
                (res != *(float FAR *) old)))
      c->WritelData (par->res,&res,sizeof(float),LPSTR(par)-sizeof(WORD));
    else if (!doIt)
      c->DellData (par->res,LPSTR(par)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    StatFunc_param FAR *par = (StatFunc_param FAR *) param ;
    int anzArgs = (par->parSize - (sizeof(*par) - sizeof(DWORD))) / sizeof(DWORD);
    c->SetlConnection (par->func,LPSTR(param)-sizeof(WORD));
    for ( int i = 0 ; i < anzArgs ; i++)
      c->SetlConnection (par->p[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    StatFunc_param FAR *par = (StatFunc_param FAR *) param ;
    int anzArgs = (par->parSize - (sizeof(*par) - sizeof(DWORD))) / sizeof(DWORD);
    c->ClearlConnection (par->func,LPSTR(param)-sizeof(WORD));
    for ( int i = 0 ; i < anzArgs ; i++)
      c->ClearlConnection (par->p[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct MakeDateTime_param {
  WORD parSize;
  DWORD res;
  DWORD d;
  DWORD t;
  };
#pragma pack()

BOOL MakeDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    MakeDateTime_param FAR *par = (MakeDateTime_param FAR *) param;
    packdate FAR *pd = (packdate FAR *) c->ReadlData (par->d);
    packtime FAR *pt = (packtime FAR *) c->ReadlData (par->t);
    if ((pd != NULL) && (pt != NULL)) {
      packdatetime res ;
      res.pd = *pd;
      res.pt = *pt;
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    MakeDateTime_param FAR *par = (MakeDateTime_param FAR *) param;
    c->SetlConnection (par->d,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->t,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    MakeDateTime_param FAR *par = (MakeDateTime_param FAR *) param;
    c->ClearlConnection (par->d,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->t,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFromDateTime_param {
  WORD parSize;
  DWORD res;
  DWORD dt;
  };
#pragma pack()
BOOL GetDateFromDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    packdatetime FAR *pdt = (packdatetime FAR *) c->ReadlData (par->dt);
    if (pdt != NULL) {
      packdate res ;
      res = pdt->pd;
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    c->SetlConnection (par->dt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    c->ClearlConnection (par->dt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetTimeFromDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    packdatetime FAR *pdt = (packdatetime FAR *) c->ReadlData (par->dt);
    if (pdt != NULL) {
      packtime res ;
      res = pdt->pt;
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    c->SetlConnection (par->dt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetFromDateTime_param FAR *par = (GetFromDateTime_param FAR *) param;
    c->ClearlConnection (par->dt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
