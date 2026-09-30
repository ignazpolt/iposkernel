///////////////////////////////////////////////////////////////////
//  Templates fuer den Dialogeditor
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/edtempl.cpv   1.27   12 Apr 2000 14:27:46   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/edtempl.cpv  $
// 
//    Rev 1.27   12 Apr 2000 14:27:46   Wolfgang
// 1.) Bei Buchstaben in Zahlenparameter auch sign zuruecksetzen nicht nur res.
// 
//    Rev 1.26   05 Oct 1998 11:25:54   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.25   31 Aug 1998 19:29:54   Hannes
// Umgang mit Formeln in den Positionen
// 
//    Rev 1.24   01 Dec 1997 19:38:48   Hannes
// Diverse Anpassungen
// 
//    Rev 1.23   28 Aug 1997 16:26:40   gerhold
//  kleiner 16-32-Bit Fehler
// 
//    Rev 1.22   28 Aug 1997 15:48:54   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.21   10 Dec 1996 14:04:04   HANNES
// 
//    Rev 1.20   17 Jun 1996 16:53:14   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.19   02 Feb 1996 10:50:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.18   27 Sep 1995 17:43:54   GERHOLD
// 
//    Rev 1.17   27 Aug 1995 13:00:22   HANNES
// 
//    Rev 1.16   23 Aug 1995 11:05:12   GERHOLD
// 
//    Rev 1.15   17 May 1995 11:33:20   HANNES
// Direkte Eingabe von Texten im Editor (vorlaufig)
// 
//    Rev 1.14   27 Mar 1995 10:38:32   GERHOLD
// 
//    Rev 1.13   20 Mar 1995 08:44:48   HANNES
//  
// 
//    Rev 1.12   08 Mar 1995 09:13:14   GERHOLD
// 
//    Rev 1.11   02 Jan 1995 09:29:38   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.9   17 Oct 1994 14:54:26   HANNES
// Tracing eingebaut
// 
//    Rev 1.8   05 Oct 1994 08:48:26   HANNES
// Header in den Listen
// 
//    Rev 1.7   10 Aug 1994 12:08:32   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.6   09 Aug 1994 10:07:56   HANNES
// Fehler in DuplicateElem
// 
//    Rev 1.5   08 Aug 1994 17:37:28   GERHOLD
// Edit-Element fuer das eine Aktion ausgefuehrt werden soll
// (Format oder Farbe) global merken
// 
//    Rev 1.4   05 Aug 1994 20:49:16   HANNES
// 
//    Rev 1.3   01 Aug 1994 15:37:34   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.2   25 Jul 1994 09:37:54   GERHOLD
// 
//    Rev 1.1   21 Jul 1994 13:55:36   HANNES
// Zwischenversion
// 
//    Rev 1.0   12 Jul 1994 14:43:16   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "wonscrip.hpp"
#define MODULENUM 115
#include "winass.hpp"

#define JUST_EM
#include "dds.hpp"

#include "font.hpp"
#include "cfield.hpp"
#define NODLL
#include "toolbar.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"

#include "drdrop.hpp"

#include "compile.hpp"
#include "template.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "frmobj.hpp"

extern HINSTANCE MyInstance;
extern HWND hOptWnd ;
extern HWND hRefWnd;
extern hash FAR *defines;
extern hash *objHash;
extern char _MyObjectName [32];
extern char _MyScreenName [32];


// Prototyp aus resadmin.hpp
extern DLLExport DWORD _export FAR PASCAL GetBitmapID (LPSTR Name);
extern DLLExport DWORD _export FAR PASCAL GetWMFID (LPSTR Name);
extern DLLExport void _export FAR PASCAL ReadResContent ();
extern DLLExport void _export FAR PASCAL UnloadResContent ();
extern HWND OutWnd;

void _EdTemplate::GetParTemplate ()
  {
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  for (LPSTR h = instring ; *h ; h = NextParDsc(h)) {
    pt = PushToParTemplate (pt,GetParType (h));
    }
  }

BOOL _EdTemplate::DoUpdateImmediate (WORD wP)
  {
  return TRUE ;
  }

BOOL _EdTemplate::ShowButton (WORD wP,WORD FAR *dType)
  {
  *dType = DDTYPE_NONE ;

  switch (pt->p[wP]) {
    case PT_BITMAP:
    case PT_WMF:
      *dType = DDTYPE_BITMAP ;
      return TRUE ;

    case PT_FORMAT:
      *dType = DDTYPE_FORMAT;
      return TRUE ;
    
    case PT_COLORVAR:
      *dType = DDTYPE_COLOR;
      return TRUE ;

    default:
      {
      char instring[256];
      *instring = '\0';
      LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
      BOOL res = FALSE ;
      WORD i = 0;
      for (LPSTR h = instring ; *h ; h = NextParDsc(h) , i ++) {
        if (i == wP) 
          res = IsVar (h);
        }
      if (res) 
        *dType = DDTYPE_VAR ;
      return res;
      }
    }
  }


HWND hWndActEdit;  // Editfenster, welches zum ">" -Knopf gehoert
void _EdTemplate::DoAction (WORD wP)
  {
  hWndActEdit = GetDlgItem (hOptWnd,wP);
  switch (pt->p[wP]) {
    case PT_BITMAP:
    case PT_WMF:
      ShowResources (hOptWnd);
      break;
    
    case PT_FORMAT:
      ShowFormat (hOptWnd, TRUE);
      break;
      
    case PT_COLORVAR:
      ShowColor (hOptWnd, TRUE);
      break;    

    }  
  }

LPVOID _EdTemplate::GetIntMem (LPVOID parblock)
  {
  return LPTOOLHEADER (parblock)->MyTool ;
  }

void _EdTemplate::Reconnect (LPVOID parblock,LPVOID old)
  {
  if (GetEdType() == EDTYPE_FORM) {
    LPTOOLHEADER (parblock)->MyTool = (tool FAR *) old;
    LPFRMOBJ (old)->ScriptParam = (FrmObjPar_Header FAR *) (LPSTR(parblock) + sizeof(WORD));
    }
  else {
    LPTOOLHEADER (parblock)->MyTool = (tool FAR *) old;
    ((tool FAR *) old)->StructData = parblock;
    }
  }

void _EdTemplate::GetOrigin (LPDIALOGELEM e,int FAR *x,int FAR *y)
  {
  LPSTR parblock = LPSTR (e->parblock) + 2 * sizeof(WORD) + GetPrivSize();
  *x = -32767 ;
  *y = -32767 ;
  for (int i = 0 ; i < int(pt->AnzPars) ; i++) {
    WORD ParType = pt->p[i];
    if ((ParType == PT_X) || (ParType == PT_X1))
      *x = int(ScanInt (e->Param[i]));
    if ((ParType == PT_Y) || (ParType == PT_Y1))
      *y = int(ScanInt (e->Param[i]));
    if (ParType == PT_P1) {
      fpt FAR *p = ScanPoint (e->Param[i]);
      TransformPoint (p);
      if (p != NULL) {
        *x = int(p->x);
        *y = int(p->y);
        }
      else
        *x = -32767 ;
      }
    parblock += sizeof(DWORD);
    }
  }

void _EdTemplate::InitializeMove (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y,int FAR *x1,int FAR *y1)
  {
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  parblock = LPSTR (parblock) + 2 * sizeof(WORD) + GetPrivSize();
  *x1 = *y1 = 0 ;
  int i = 0;
  for (LPSTR h = instring ; *h ; h = NextParDsc(h)) {
    WORD ParType = GetParType (h);
    if ((ParType == PT_X) || (ParType == PT_X1))
      *x = int(ScanInt (e->Param[i]));
    if ((ParType == PT_Y) || (ParType == PT_Y1))
      *y = int(ScanInt (e->Param[i]));
    if (ParType == PT_X2)
      *x1 = int(ScanInt (e->Param[i]));
    if (ParType == PT_Y2)
      *y1 = int(ScanInt (e->Param[i]));
    if (ParType == PT_P1) {
      fpt FAR *p = ScanPoint (e->Param[i]);
      TransformPoint (p);
      if (p != NULL) {
        *x = int(p->x);
        *y = int(p->y);
        }
      else
        *x = -32767 ;
      }
    if (ParType == PT_P2) {
      fpt FAR *p = ScanPoint (e->Param[i]);
      TransformPoint (p);
      if (p != NULL) {
        *x1 = int(p->x);
        *y1 = int(p->y);
        }
      else
        *x = -32767 ;
      }
    parblock = LPSTR (parblock) + sizeof(DWORD);
    i ++ ;
    }
  }

#ifdef WIN32
void _EdTemplate::GetPointPar (LPDIALOGELEM e,WORD Type,long FAR *x,long FAR *y)
#else
void _EdTemplate::GetPointPar (LPDIALOGELEM e,WORD Type,int FAR *x,int FAR *y)
#endif
  {
  for (int i = 0 ; i < int (pt->AnzPars) ; i ++ ) {
    if (pt->p[i] == Type) {
      fpt FAR *p = ScanPoint (e->Param[i]);
      TransformPoint (p);
      if (p != NULL) {
        *x = int(p->x);
        *y = int(p->y);
        return ;
        }
      }
    }
  }
void _EdTemplate::InitializeP1 (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y)
  {
  if (IsThere (PT_P1))
#ifdef WIN32
    GetPointPar (e,PT_P1,(long far *)x,(long far *)y);
#else
    GetPointPar (e,PT_P1,x,y);
#endif
  else {
#ifdef WIN32
    GetIntPar (e,PT_X1,(long far *)x);
    GetIntPar (e,PT_Y1,(long far *)y);
#else
    GetIntPar (e,PT_X1,x);
    GetIntPar (e,PT_Y1,y);
#endif
    }
  }
void _EdTemplate::InitializeP2 (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y)
  {
  if (IsThere (PT_P2))
#ifdef WIN32
    GetPointPar (e,PT_P2,(long far *)x,(long far *)y);
#else
    GetPointPar (e,PT_P2,x,y);
#endif
  else {
#ifdef WIN32
    GetIntPar (e,PT_X2,(long far *)x);
    GetIntPar (e,PT_Y2,(long far *)y);
#else
    GetIntPar (e,PT_X2,x);
    GetIntPar (e,PT_Y2,y);
#endif
    }
  }

void _EdTemplate::InitializeWidth (LPDIALOGELEM e,int FAR *w)
  {
  for (int i = 0 ; i < int(pt->AnzPars) ; i++) {
    if (pt->p[i] == PT_WIDTH)
      *w = int(ScanInt (e->Param[i]));
    }
  }

void _EdTemplate::InitializeHeight (LPDIALOGELEM e,int FAR *h)
  {
  for (int i = 0 ; i < int(pt->AnzPars) ; i++) {
    if (pt->p[i] == PT_HEIGHT)
      *h = int(ScanInt (e->Param[i]));
    }
  }

void _EdTemplate::SetIntPar (WORD Type,LONG val,LPVOID parblock,LPSTR FAR *Param)
  {
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  parblock = LPSTR (parblock) + 2 * sizeof(WORD) + GetPrivSize();
  int i = 0;
  for (LPSTR h = instring ; *h ; h = NextParDsc(h) , i++) {
    WORD ParType = GetParType (h);
    if (ParType == Type) {
      char nparam[256],nparami[32];
      if (Param[i] != NULL) {
        // Alles nach nparam kopieren, bis die erste Nummer kommt
        LPSTR d = nparam;
        BOOL doBreak = TRUE ;
        for (LPSTR s = Param[i] ; *s ; s ++ ) {
          if ((*s >= '0') && (*s <= '9') && (doBreak)) {
            *d = '\0' ;
            break ;
            }
          else {
            if ((IsCharAlpha (*s)) || ((*s >= '0') && (*s <= '9'))) {
              doBreak = FALSE ;
              }
            else
              doBreak = TRUE ;
            *d++ = *s ;
            }
          }
        }
      else
        *nparam = '\0';
      wsprintf (nparami,"%ld",val);
      lstrcat (nparam,nparami);
      if (Param[i] != NULL) FreeGlobMem (Param[i]);
      Param[i] = LPSTR(GetGlobMem (lstrlen(nparam)+1));
      lstrcpy (Param[i],nparam);
      }
    parblock = LPSTR(parblock) + sizeof(DWORD);
    }
  }

#ifdef WIN32
void _EdTemplate::GetIntPar (LPDIALOGELEM e,WORD Type,long FAR *x)
#else
void _EdTemplate::GetIntPar (LPDIALOGELEM e,WORD Type,int FAR *x)
#endif
  {
  *x = 0;
  for (int i = 0; i < int(pt->AnzPars) ; i ++) {
    if (pt->p[i] == Type) {
      *x = int(ScanInt (e->Param[i]));
      return ;
      }
    }
  }

void _EdTemplate::GetIntParWithNum (LPDIALOGELEM e,int Num,int FAR *x)
  {
  *x = 0;
  for (int i = 0; i < int(pt->AnzPars) ; i ++) {
    if (i == Num) {
      *x = int(ScanInt (e->Param[i]));
      return ;
      }
    }
  }

void GetPointString (_EdTemplate *t,LPSTR nparam,int x,int y)
  {
  double xf,yf;
  t->ToPointKoords (x,y,&xf,&yf);
  wsprintf (nparam,"[(%d.%d,%d.%d)]",int(xf),int(LONG(fabs(xf)*10.0) % 10),
                                     int(yf),int(LONG(fabs(yf)*10.0) % 10));
  }

void _EdTemplate::SetPointPar (WORD Type,int x,int y,LPVOID parblock,LPSTR FAR *Param)
  {
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  parblock = LPSTR (parblock) + 2 * sizeof(WORD) + GetPrivSize();
  int i = 0;
  for (LPSTR h = instring ; *h ; h = NextParDsc(h) , i++) {
    WORD ParType = GetParType (h);
    if (ParType == Type) {
      char nparam[256];
      GetPointString (this,nparam,x,y);
      if (Param[i] != NULL) FreeGlobMem (Param[i]);
      Param[i] = LPSTR(GetGlobMem (lstrlen(nparam)+1));
      lstrcpy (Param[i],nparam);
      }
    parblock = LPSTR(parblock) + sizeof(DWORD);
    }
  }

BOOL _EdTemplate::IsThere (WORD Type)
  {
  for (int i = 0 ; i < int (pt->AnzPars) ; i++)
    if (pt->p[i] == Type) return TRUE ;
  return FALSE ;
  }
BOOL _EdTemplate::MoveAllowed (BOOL FAR *isPoint)
  {
  if ((IsThere (PT_P1)) && (IsThere (PT_P2))) {
    if (isPoint != NULL) *isPoint = TRUE ;
    return TRUE ;
    }
  if (IsThere (PT_P1)) {
    if (isPoint != NULL) *isPoint = TRUE ;
    return TRUE ;
    }
  if ((IsThere (PT_X)) && (IsThere (PT_Y))) {
    if (isPoint != NULL) *isPoint = FALSE ;
    return TRUE ;
    }
  if ((IsThere (PT_X1)) && (IsThere (PT_Y1)) &&
      (IsThere (PT_X2)) && (IsThere (PT_Y2))) {
    if (isPoint != NULL) *isPoint = FALSE ;
    return TRUE ;
    }
  return FALSE ;
  }
BOOL _EdTemplate::P1Allowed ()
  {
  return ((IsThere (PT_P1)) ||
      ((IsThere (PT_X1)) && (IsThere (PT_Y1))));
  }
BOOL _EdTemplate::P2Allowed ()
  {
  return ((IsThere (PT_P2)) ||
      ((IsThere (PT_X2)) && (IsThere (PT_Y2))));
  }
BOOL _EdTemplate::HeightAllowed ()
  {
  return IsThere (PT_HEIGHT);
  }
BOOL _EdTemplate::WidthAllowed ()
  {
  return IsThere (PT_WIDTH);
  }

LPVOID InitializeParBlock (WORD FncID,WORD PrivSize)
  {
  LPWORD res = LPWORD (GetGlobMem(2 * sizeof(WORD) + PrivSize));
  res[0] = FncID;
  res[1] = sizeof(WORD) + PrivSize;

  return res;
  }

LPVOID PushToParBlock (LPVOID h,LPVOID d,WORD size)
  {
  LPWORD pSize = LPWORD (h) + 1;
  WORD   nSize = *pSize + size + sizeof(WORD);
  LPVOID res = GetGlobMem (nSize);
  lmemcpy (res,h,*pSize + sizeof(WORD));
  lmemcpy (LPSTR(res) + *pSize + sizeof(WORD),d,size);
  ((LPWORD)res)[1] += size;
  FreeGlobMem (h);
  return res;
  }

static LPSTR StringPtr;
LPSTR ScanString (LPSTR str,BOOL FAR *isConst,BOOL checkDefs)
  {
  char strres[512];
  static char strresx[512];
  LPSTR res = strres;
  *res = '\0';
  BOOL constdone = FALSE ;
  for (LPSTR h = str ; (((*h == ' ') || (*h == '[') || (*h == '"')) && (*h) && (!constdone)) ; h++) {
    if (*h == '"') {
      constdone = TRUE ;
      }
    }
  if (*h) {
    if (constdone) {
      for ( ; ((*h != '"') && (*h)) ; )
        *res++ = *h++ ;
      }
    else {
      for ( ; ((*h != ' ') && (*h != ']') && (*h != '"') && (*h != ',') && (*h)) ; )
        *res++ = *h++ ;
      }
    }
  *res = '\0';
  if ((checkDefs) && (!constdone) && (defines != NULL)) {
    LPSTR rd = LPSTR (defines->GetData (strres));
    if (rd != NULL) {
      lmemcpy (strres,rd,GetBlockSize(rd));
      constdone = TRUE ;
      }
    }
  if (isConst != NULL)
    *isConst = constdone;
  int rsize;
  WIN_ASSERT (InterpreteCString (strresx,sizeof(strresx),strres,&rsize));
  if (StringPtr != NULL) FreeGlobMem (StringPtr);
  StringPtr = LPSTR(GetGlobMem (rsize));
  lmemcpy (StringPtr,strresx,rsize);
  return strresx;
  }
void DelStrBuffer ()
  {
  if (StringPtr != NULL)
    FreeGlobMem (StringPtr);
  StringPtr = NULL;
  }

DWORD ScanInt (LPSTR h)
  {
  DWORD res = 0;
  BOOL digitfound = FALSE ;
  BOOL alphaFound = FALSE ;
  BOOL nextClear = FALSE ;
  int sign = 1;
  for ( LPSTR txt = h ; *txt ; txt ++) {
    if ((*txt == '[') || (*txt == ']') || (*txt == 'L') || (*txt == '(') || (*txt == ')')) continue ;
    if (lstrcmp (txt,"long") == 0) {
      txt += 3 ;
      continue ;
      }
    if (*txt == '-') sign = -1 ;
    if ((*txt >= '0') && (*txt <= '9')) {
      if (nextClear) res = 0L;
      res = res * DWORD(10) + DWORD(*txt - '0') , digitfound = TRUE ;
      nextClear = FALSE ;
      }
    else {
      if (IsCharAlpha(*txt)) {
        alphaFound = TRUE ;
        res = 0L ;
        sign = 1 ;
        }
      else if ((*txt == ' ') || (*txt == '\t'))
        nextClear = TRUE ;
      }
    }
  res = DWORD(LONG(res) * LONG(sign));

  if ((!digitfound) && (defines != NULL) && (alphaFound)) {
    LPDWORD rd = LPDWORD (defines->GetData (ScanString (h,NULL,FALSE)));
    if (rd != NULL) res = *rd;
    }
  return res;
  }

float FAR *ScanDecVar (LPSTR txt)
  {
  #define MAX_DEC 16
  static float res[MAX_DEC];
  static int actind ;
  actind = (actind + 1) % MAX_DEC ;
  char lstring[64];
  lstrcpy (lstring,txt);

  sscanf (lstring,"%f",res + actind);
  return res + actind;
  }

#define MAXDIFFERENT  32
fpt FAR * ScanPoint (LPSTR txt)
  {
  char lstring[64];
  static fpt res[MAXDIFFERENT];
  static int actindex;
  actindex += 1;
  actindex = actindex % MAXDIFFERENT ;
  lstrcpy (lstring,txt);
  if (sscanf (lstring,"[(%f,%f)]",&res[actindex].x,&res[actindex].y) != 2) 
    res[actindex].x = float(0.0) ,
    res[actindex].y = float(0.0) ;
  return &res[actindex];
  }

#define GDN_INIT  0
#define GDN_NAME  1
BOOL GetDefName (LPSTR d,LPSTR s)
  {
  int state = GDN_INIT ;
  for ( LPSTR h = s ; *h ; h ++) {
    switch (state) {
      case GDN_INIT :
        if (*h == '(') state = GDN_NAME ;
        break ;
      case GDN_NAME :
        if (*h == ')') {
          *d = '\0' ;
          return TRUE ;
          }
        else if (*h != ' ')
          *d++ = *h ;
        break ;
      }
    }
  return FALSE ;
  }

DWORD FAR * ScanIntVar (LPSTR txt)
  {
  static DWORD res[MAXDIFFERENT];
  static int actindex;
  actindex += 1;
  actindex = actindex % MAXDIFFERENT ;
  res[actindex] = ScanInt (txt);
  return &res[actindex];
  }

LPVOID _EdTemplate::CreateParBlock (WORD pcount,LPSTR FAR *par)
  {
  LPVOID res = InitializeParBlock (GetToolType(),GetPrivSize());
  if (pt == NULL) return NULL;
  for (WORD i = 0 ; ((i < pt->AnzPars) && (i < pcount)) ; i++) {
    DWORD di = i;
    switch (pt->p[i]) {
      case PT_OBJADDRESS :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_STRING     :
      case PT_TEXT    :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_UNKNOWN    :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_POINT    :
      case PT_P1       :
      case PT_P2       :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_COLORVAR :
      case PT_HOTKEY :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_INT        :
      case PT_WIDTH      :
      case PT_HEIGHT     :
      case PT_X      :
      case PT_Y      :
      case PT_BX     :
      case PT_BY     :
      case PT_X1     :
      case PT_X2     :
      case PT_Y1     :
      case PT_Y2     :
      case PT_FORMAT :
        res = PushToParBlock (res,&di,sizeof(di));
        break ;
      case PT_BITMAP :
        {
        LPSTR str = ScanString(par[i]);
        DWORD Id = GetBitmapID (str);
        res = PushToParBlock (res,&Id,sizeof(Id));
        }
        break ;
      case PT_WMF :
        {
        LPSTR str = ScanString(par[i]);
        DWORD Id = GetWMFID (str);
        res = PushToParBlock (res,&Id,sizeof(Id));
        }
        break ;
      case PT_DEC :
        {
        res = PushToParBlock (res,&di,sizeof(di));
        }
        break ;
      default :
        WIN_ASSERT(FALSE);
      }
    }
  return res;
  }

void _EdTemplate::GetParName (LPSTR outtxt,int i)
  {
  *outtxt = '\0';
  // Suchen im Prototypen
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  int j = 0 ;
  for (LPSTR h = instring ; ((*h) && (j < i)) ; h = NextParDsc(h) , j ++ ) ;

  if (*h) {
    for ( ; ((*h) && (*h != ' ') && (*h != ',')) ; h++) ;
    if (*h == ' ') {    // Da ist ein extranamen angegeben
      h ++ ;
      for (LPSTR x = outtxt ; ((*h) && (*h != ',')) ; )
        *x++ = *h++ ;
      *x++ = '\0';
      }
    }

  if (*outtxt == '\0') {
    char patternname[32];
    *patternname = '\0';
    LoadString (MyInstance,PTNAME_BASE + pt->p[i],patternname,sizeof(patternname));
    wsprintf (outtxt,patternname,i);
    }
  }

BOOL _EdTemplate::IsOpt (LPSTR t)
  {
  for ( LPSTR h = t ; (*h) && (*h != ',') ; h++)
    if (mystrcmp (h,"opt")) return TRUE ;
  return FALSE ;
  }

BOOL _EdTemplate::IsVar (LPSTR t)
  {
  for ( LPSTR h = t ; (*h) && (*h != ',') ; h++)
    if (mystrcmp (h,"var")) return TRUE ;
  return FALSE ;
  }

void _EdTemplate::AnalyseExtraInfo (LPSTR FAR *_Param)
  {
  if (*_MyObjectName == '\0') lstrcpy (_MyObjectName,ScipEndingDigits(_Param[0]));
  }

LPDIALOGELEM firstElem = NULL;
BOOL IsNameAllowed(LPSTR oName)
  {
  BOOL res = TRUE ;
  for ( LPDIALOGELEM h = firstElem ; ((h != NULL) && (res)) ; h = h->Next )
    res = ((h->AnzParams == 0) || (lstrcmp (h->Param[0],oName) != 0));
  return res;
  }

BOOL _EdTemplate::TestParam (LPDIALOGELEM h,int i,int x,int y)
  {
  return FALSE ;
  }

extern void toDevKoord (LPPOINT pt);
BOOL TestSnapParam (LPDIALOGELEM c,int i,int x,int y)
  {
  if (i == 12) {
    for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
      if ((h->templ->GetToolType() == TOOLTYPE_EDIT) || 
          (h->templ->GetToolType() == TOOLTYPE_BEDIT) ||
          (h->templ->GetToolType() == TOOLTYPE_FLOAT) ||
          (h->templ->GetToolType() == TOOLTYPE_MONEY) ||
          (h->templ->GetToolType() == TOOLTYPE_LONGINT) ||
          (h->templ->GetToolType() == TOOLTYPE_SHORTINT)) {
        RECT r;
        h->GetRect (NULL,&r);
        POINT pt;
        pt.x = x ;
        pt.y = y ;
        toDevKoord (&pt);
        if (PtInRect (&r,pt)) {
          c->PushParToParList (h->Param[0]);
          return TRUE ;
          }
        }
      }
    }
  return FALSE ;
  }
BOOL _ComboButton::TestParam (LPDIALOGELEM c,int i,int x,int y)
  {
  return TestSnapParam (c,i,x,y);
  }

BOOL _UpDown::TestParam (LPDIALOGELEM c,int i,int x,int y)
  {
  return TestSnapParam (c,i,x,y);
  }

void _EdTemplate::InsertNewElem (int x,int y)
  {
  LPDIALOGELEM h = new DialogElem (this,NULL,0);
  // Suchen eines neuen Objektnamens
  char oName[64];
  for (int i = 0 ; ; i++) {
    wsprintf (oName,"%s%d",LPSTR(_MyObjectName),i);
    if (IsNameAllowed(oName)) break ;
    }
  h->PushParToParList (oName);
  int base;
  if (GetEdType() == EDTYPE_DIALOG) {
    h->PushParToParList (_MyScreenName);
    base = 2;
    }
  else
    base = 1;

  // Erzeugen der restlichen Parameter
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetParID(),instring,sizeof(instring));
  
  LPSTR d = instring;

  for ( i = base ; *d ; i++) {
    LPSTR dn = NextParDsc(d);
    if (*dn) *(dn-1) = '\0';
    char otxt[32];
    switch (pt->p[i]) {
      case PT_X :
      case PT_X1 :
        wsprintf (otxt,"%d",x);
        h->PushParToParList (otxt);
        break;
      case PT_Y :
      case PT_Y1 :
        wsprintf (otxt,"%d",y);
        h->PushParToParList (otxt);
        break;
      case PT_P1 :
        GetPointString (this,otxt,x,y);
        h->PushParToParList (otxt);
        break;
      case PT_P2 :
        GetPointString (this,otxt,x+500,y);
        h->PushParToParList (otxt);
        break;
      case PT_X2 :
        wsprintf (otxt,"%d",x + 20);
        h->PushParToParList (otxt);
        break;
      case PT_Y2 :
        wsprintf (otxt,"%d",y);
        h->PushParToParList (otxt);
        break;
      default :
        if (!TestParam (h,i,x,y))
          h->PushParToParList (d);
      }
    d = dn;
    }

  h->parblock = CreateParBlock (h->AnzParams,h->Param);

  if (GetEdType() == EDTYPE_FORM)
    NewShow (oName);
  DoEdit (h,EM_LOAD | EM_CHANGETOTRUE);
  ActivateControl (hRefWnd);
  }

void _EdTemplate::InsertNewElem ()
  {
  InsertNewElem (10,10);
  }

void _EdTemplate::DuplicateElem (LPDIALOGELEM e)
  {
  LPDIALOGELEM h = new DialogElem (this,NULL,0);
  // Suchen eines neuen Objektnamens
  char oName[64];
  for (int i = 0 ; ; i++) {
    wsprintf (oName,"%s%d",LPSTR(_MyObjectName),i);
    if (IsNameAllowed(oName)) break ;
    }
  h->PushParToParList (oName);

  // Duplizieren der restlichen Parameter
  char instring[256];
  *instring = '\0';
  LoadString (MyInstance,GetDscID(),instring,sizeof(instring));
  
  LPSTR d = instring;
  d = NextParDsc(d);

  int base;
  if (GetEdType() == EDTYPE_DIALOG) {
    h->PushParToParList (_MyScreenName);
    d = NextParDsc(d);
    base = 2;
    }
  else
    base = 1;

  for ( i = base ; *d ; d = NextParDsc(d) , i ++) {
    WORD Type = GetParType (d);
    if (i >= int(e->AnzParams)) break ;
    switch (Type) {
      case PT_OBJADDRESS :
      case PT_STRING     :
      case PT_TEXT       :
      case PT_UNKNOWN    :
      case PT_WIDTH      :
      case PT_HEIGHT     :
      case PT_INT        :
      case PT_BX         :
      case PT_BY         :
      case PT_BITMAP     :
      case PT_WMF        :
      case PT_FORMAT     :
      case PT_DEC        :
      case PT_POINT      :
      case PT_COLORVAR   :
      case PT_HOTKEY     :
        h->PushParToParList (e->Param[i]);
        break ;
      case PT_X          :
      case PT_Y          :
      case PT_X1         :
      case PT_Y1         :
      case PT_X2         :
      case PT_Y2         :
        {
        int di = int (ScanInt (e->Param[i]));
        char otxt[20];
        if (GetEdType() == EDTYPE_DIALOG)
          wsprintf(otxt,"%d",di+10);
        else
          wsprintf(otxt,"%d",di+200);
        h->PushParToParList (otxt);
        }
        break ;
      case PT_P1         :
        {
        fpt FAR *p = ScanPoint (e->Param[i]);
        TransformPoint (p);
        if (p != NULL) {
          p->x += float(200.0) ;
          char otxt[20];
          GetPointString (this,otxt,int(p->x),int(p->y));
          h->PushParToParList (otxt);
          }
        else
          h->PushParToParList (e->Param[i]);
        }
        break ;
      case PT_P2         :
        {
        fpt FAR *p = ScanPoint (e->Param[i]);
        TransformPoint (p);
        if (p != NULL) {
          p->x += float(200.0) ;
          char otxt[20];
          GetPointString (this,otxt,int(p->x),int(p->y));
          h->PushParToParList (otxt);
          }
        else
          h->PushParToParList (e->Param[i]);
        }
        break ;
      default :
        WIN_ASSERT(FALSE);
      }
    }
  h->parblock = CreateParBlock (h->AnzParams,h->Param);
  if (GetEdType() == EDTYPE_FORM)
    NewShow (oName);
  DoEdit (h,EM_LOAD | EM_CHANGETOTRUE);
  ActivateControl (hRefWnd);
  }

void _CreateScreen::AnalyseExtraInfo (LPSTR FAR *_Param)
  {
  if (*_MyScreenName == '\0') lstrcpy (_MyScreenName,_Param[0]);
  }

struct ETBData {
  DialogElem FAR *e;
  };
void _EdTemplate::DoEdit (LPDIALOGELEM h,WORD Mode)
  {
  if ((IsImplemented ()) && (h->parblock != NULL)) {
    ETBData d;
    d.e = h;
    SetControl (hRefWnd, LPTOOLHEADER(h->parblock),
                          Mode,&d,sizeof(d)
              );
    }
  }

void _CreateScreen::DoEdit (LPDIALOGELEM h,WORD mode)
  {
  static HWND hToolWnd;
  if (IsImplemented ()) {
    if (mode & EM_LOAD) {
      CreateScreen_param FAR *par = (CreateScreen_param FAR *) h->parblock;
      WINDOWATTRSTRUCT attr;
      attr.Title = ScanString(h->Param[3]);
#ifdef WIN32
      GetIntPar (h,PT_WIDTH,(long far *)(&attr.w));
      GetIntPar (h,PT_HEIGHT,(long far *)(&attr.h));
#else
      GetIntPar (h,PT_WIDTH,&attr.w);
      GetIntPar (h,PT_HEIGHT,&attr.h);
#endif
      attr.Style = WS_POPUP | WS_VISIBLE | 
                   WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN ;
      int x = 0;
      int y = 0;

      ETBData d;
      d.e = h;

      hToolWnd = CreateToolBar (par->ScreenId,hRefWnd,
                                int (par->ScreenNmbr),
                                par->PosRef,
                                &attr,&d,sizeof(d),
                                x,y,
                                FALSE,FALSE,par
                               );
      SetWindowPos (hToolWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
      new Tool_Drop (hToolWnd);
      }
    if (mode & (EM_RESET | EM_CLEAR)) {
      RemoveAll (hToolWnd);
      LPSCREEN FAR *llps = (LPSCREEN FAR *) 
          objHash->GetData (ScanString(h->Param[0]));
      if ((llps != NULL) && (*llps != NULL))
        DestroyToolBar (*llps);
      }
    if (mode & EM_PRIVATE1) {
      CreateScreen_param FAR *par = (CreateScreen_param FAR *) h->parblock;
      SetWindowText (hToolWnd,ScanString(h->Param[3]));
      RECT r;
      double unit ;
      GetBaseUnit (&unit);
      int _w,_h;
#ifdef WIN32
      GetIntPar (h,PT_WIDTH,(long far *)(&_w));
      GetIntPar (h,PT_HEIGHT,(long far *)(&_h));
#else
      GetIntPar (h,PT_WIDTH,&_w);
      GetIntPar (h,PT_HEIGHT,&_h);
#endif
      int w = int (double (_w) * unit) ;
      int h = int (double (_h) * unit);
      GetWindowRect (hToolWnd,&r);
      SetWindowPos (hToolWnd,NULL,r.left,r.top,w,h,SWP_NOZORDER | SWP_NOACTIVATE);
      }
    }
  }

void _EdTemplate::ToLogKoords (int FAR *dx,int FAR *dy)
  {
  double baseunit;
  GetBaseUnit (&baseunit);
  if (dx != NULL)
    *dx = int (double (*dx) / baseunit) ;
  if (dy != NULL)
    *dy = int (double (*dy) / baseunit) ;
  }

void _EdTemplate::ToAbsLogKoords (int FAR *x,int FAR *y)
  {
  double baseunit;
  GetBaseUnit (&baseunit);
  *x = int (double (*x) / baseunit) ;
  *y = int (double (*y) / baseunit) ;
  }

#ifdef WIN32
void _EdTemplate::ToAbsDevKoords (long FAR *x,long FAR *y)
#else
void _EdTemplate::ToAbsDevKoords (int FAR *x,int FAR *y)
#endif
  {
  double baseunit;
  GetBaseUnit (&baseunit);
  *x = int (double (*x) * baseunit) ;
  *y = int (double (*y) * baseunit) ;
  }

void _EdTemplate::Move (LPDIALOGELEM e,int x,int y,int x1,int y1)
  {
  if (GetEdType() == EDTYPE_DIALOG) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    }
  BOOL isPoint;
  MoveAllowed (&isPoint);
  if (isPoint) {
    SetPointPar (PT_P1,x,y,e->parblock,e->Param);
    SetPointPar (PT_P2,x1,y1,e->parblock,e->Param);
    }
  else {
    if (IsThere (PT_X)) {
      SetIntPar (PT_X,x,e->parblock,e->Param);
      SetIntPar (PT_Y,y,e->parblock,e->Param);
      }
    else {
      SetIntPar (PT_X1,x,e->parblock,e->Param);
      SetIntPar (PT_Y1,y,e->parblock,e->Param);
      SetIntPar (PT_X2,x1,e->parblock,e->Param);
      SetIntPar (PT_Y2,y1,e->parblock,e->Param);
      }
    }
  DoEdit (e,EM_PRIVATE1);   // EM_RESET | EM_LOAD
  }

void _EdTemplate::SetP1 (LPDIALOGELEM e,int x,int y)
  {
  if (IsThere (PT_P1))
    SetPointPar (PT_P1,x,y,e->parblock,e->Param);
  else {
    SetIntPar (PT_X1,x,e->parblock,e->Param);
    SetIntPar (PT_Y1,y,e->parblock,e->Param);
    }
  DoEdit (e,EM_PRIVATE1);
  }
void _EdTemplate::SetP2 (LPDIALOGELEM e,int x,int y)
  {
  if (IsThere (PT_P2))
    SetPointPar (PT_P2,x,y,e->parblock,e->Param);
  else {
    SetIntPar (PT_X2,x,e->parblock,e->Param);
    SetIntPar (PT_Y2,y,e->parblock,e->Param);
    }
  DoEdit (e,EM_PRIVATE1);
  }

//---------------------------------------------------------------------------
// Editieren eines Elementes wenn es selektiert ist
//---------------------------------------------------------------------------
void _EdTemplate::OnChar (LPDIALOGELEM e,char ch)
  {
  for (int i = 0; i < int(pt->AnzPars) ; i ++) {
    if ((pt->p[i] == PT_TEXT) || (pt->p[i] == PT_STRING)) {
      LPSTR old = ScanString (e->Param[i]);
      char buffer[512];
      *buffer = '"' ;
      if (old != NULL)
        lstrcpy (buffer+1,old);
      else
        buffer[1] = '\0';
      int l;
      switch (ch) {
        case '\b' :
        case '' :
          if (lstrlen(buffer) > 1)
            buffer[lstrlen(buffer)-1] = '\0';
          break ;
        default :
          l = lstrlen(buffer) ;
          buffer[l] = ch ;
          buffer[l+1] = '\0' ;
        }
      l = lstrlen(buffer);
      buffer[l] = '"' ;
      buffer[l+1] = '\0';
      if (e->Param[i] != NULL) FreeGlobMem (e->Param[i]);
      e->Param[i] = LPSTR(GetGlobMem (lstrlen(buffer)+1));
      lstrcpy (e->Param[i],buffer);

      DoEdit (e,EM_PRIVATE1);
      return ;
      }
    }
  MessageBeep (0);
  }

int GetDialogSnapYOffs (int Format,int ExtraPixels = 0)
  {
  LPFORMATMETRIC m = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,Format);
  PaintContext pc(OutWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips (0,0,float(1.0));
  int pheight = pc.YLOGtoPHYS (m->yBaseHeight);
  double baseunit;
  GetBaseUnit (&baseunit);
  return int (double(pheight + ExtraPixels) / baseunit);
  }
int _TextCheckButton::SnapYOffs (LPDIALOGELEM e)
  {
  int Format;
  GetIntParWithNum (e,22,&Format);
  return GetDialogSnapYOffs (Format);
  }
int _StaticTool::SnapYOffs (LPDIALOGELEM e)
  {
  int Format;
  GetIntParWithNum (e,7,&Format);
  return GetDialogSnapYOffs (Format);
  }
int _ToolEdit::SnapYOffs (LPDIALOGELEM e)
  {
  int Format;
  GetIntParWithNum (e,10,&Format);
  return GetDialogSnapYOffs (Format,2);
  }

// Sortierung
int _EdTemplate::SortNum (LPDIALOGELEM e)
  {
  int num = 0;

  if (GetEdType() == EDTYPE_DIALOG) {
    for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next , num ++) {
      if (h == e) break ;
      }
    }
  else
    num = GetShownNmbr(e);
/*
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next , num ++) {
    if (h == e) break ;
    }
*/
  return num ;
  }

typedef ExternTool FAR *LPEXTERNTOOL;
void _PaintStdHeader::DoEdit (LPDIALOGELEM h,WORD mode)
  {
  if (IsImplemented ()) {
    if (mode & EM_LOAD) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,0);
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,GWL_HEADERPTR,LONG(h));
        }
      }
    if (mode & (EM_RESET | EM_CLEAR)) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,0);
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,GWL_HEADERPTR,0L);
        }
      }
    if (mode & EM_PRIVATE1) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,0);
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,GWL_HEADERPTR,LONG(h));
        }
      }
    }
  }

void _PaintStdButton::DoEdit (LPDIALOGELEM h,WORD mode)
  {
  if (IsImplemented ()) {
    if (mode & EM_LOAD) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,GetParNr());
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,WndId(),LONG(h));
        }
      }
    if (mode & (EM_RESET | EM_CLEAR)) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,GetParNr());
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,WndId(),0L);
        }
      }
    if (mode & EM_PRIVATE1) {
      LPEXTERNTOOL FAR *lpext = (LPEXTERNTOOL FAR *) 
          MyGetData (h,GetParNr());
      if ((lpext != NULL) && (*lpext != NULL)) {
        HWND hExtWnd = (*lpext)->hExtWnd;
        SetWindowLong (hExtWnd,WndId(),LONG(h));
        }
      }
    }
  }

BOOL _ComboButton::ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  if (lstrcmp (x1->Param[12],x2->Param[0]) == 0) return FALSE ;
  else                                           return TRUE ;
  }

BOOL _UpDown::ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  if (lstrcmp (x1->Param[12],x2->Param[0]) == 0) return FALSE ;
  else                                           return TRUE ;
  }

BOOL _PaintStdHeader::ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  if (lstrcmp (x1->Param[0],x2->Param[0]) == 0) return FALSE ;
  else                                          return TRUE ;
  }
BOOL _PaintStdButton::ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  if (lstrcmp (x1->Param[GetParNr()],x2->Param[0]) == 0) return FALSE ;
  else                                                   return TRUE ;
  }
