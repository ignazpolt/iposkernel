// 
// Funktionen, die in der Scriptsprache zur Verfuegung stehen.
//
// $Header:   F:/marille/clinicum/rev/func1.cpv   1.25   23 May 2000 09:21:34   Hannes  $
// $Log:   F:/marille/clinicum/rev/func1.cpv  $
// 
//    Rev 1.25   23 May 2000 09:21:34   Hannes
// Fehler Beim Schreiben von Date und qlong
// 
//    Rev 1.24   03 Apr 2000 20:57:00   Hannes
// TryToReadExtra
// 
//    Rev 1.23   03 Apr 2000 11:47:38   Hannes
// Bei NULL bleibt NULL: Kein DellData..
// 
//    Rev 1.22   27 Apr 1999 01:44:44   Hannes
// dosqrt
// 
//    Rev 1.21   19 Nov 1997 18:47:42   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.20   06 May 1997 11:34:02   Hannes
// 
//    Rev 1.19   05 May 1997 11:37:48   Hannes
// Speicherfresser
// 
//    Rev 1.18   20 Mar 1997 13:02:54   Martin
// GetArgs: else mit NULLen befuellen !
// 
//    Rev 1.17   28 Feb 1997 14:43:24   Hannes
// Speicherhandling fuer Calc - Funktionen
// 
//    Rev 1.16   08 Nov 1996 13:33:00   HANNES
// QLong Funktionen
// 
//    Rev 1.15   22 Jul 1996 22:08:14   HANNES
// 
//    Rev 1.14   22 Jul 1996 21:58:30   HANNES
// Vergleich auf DBINT
// 
//    Rev 1.13   10 Jun 1996 10:08:02   GERHOLD
// pragma pack
// 
//    Rev 1.12   02 Feb 1996 10:36:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.11   27 Aug 1995 13:04:10   HANNES
// MulShort,DivShort,MulLong,DivLong
// 
//    Rev 1.10   24 Aug 1995 00:19:58   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.9   14 Aug 1995 08:27:50   HANNES
// Kleine Optimierungen
// 
//    Rev 1.8   11 Jun 1995 10:08:10   HANNES
// TryToReadData eingebaut, um sinnloses schreiben zu vermeiden
// 
//    Rev 1.7   20 Mar 1995 11:56:06   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.6   24 Feb 1995 11:17:08   HANNES
//  
// 
//    Rev 1.5   13 Jan 1995 21:16:14   HANNES
// SetVal auch bei UPDATE ausfuehren
// 
//    Rev 1.4   05 Dec 1994 17:42:28   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.3   07 Sep 1994 10:51:12   HANNES
// Zeitfunktionen
// 
//    Rev 1.2   31 Aug 1994 12:58:30   HANNES
// Schwerer Fehler in SetConnection
// 
//    Rev 1.1   05 Aug 1994 20:17:48   HANNES
// uDiffTime
// 
//    Rev 1.0   24 Jun 1994 17:05:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.26   12 Jan 1994 11:08:58   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.25   29 Nov 1993 08:54:00   HANNES
// uAddYearsDec
// 
//    Rev 1.24   16 Nov 1993 04:22:52   HANNES
// Konstruktionsfunktionen
// 
//    Rev 1.23   27 Sep 1993 18:28:28   HANNES
// Neue Datumsfunktionen
// 
//    Rev 1.22   22 Sep 1993 09:19:36   HANNES
// Version nach St. Poelten
// 
//    Rev 1.21   05 Sep 1993 22:15:38   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.20   24 Aug 1993 10:33:52   HANNES
// uAddDate
// 
//    Rev 1.19   18 Aug 1993 10:31:52   HANNES
// Liste der alten Werte wird nicht mehr angelegt..
// 
//    Rev 1.18   18 Jun 1993 15:13:00   MARTIN
// Prototypen der Berechnungsfunktionen
// 
//    Rev 1.17   02 Jun 1993 22:20:38   MARTIN
// uTurningPoint
// 
//    Rev 1.16   28 May 1993 21:30:18   MARTIN
// DelData...
// 
//    Rev 1.15   24 May 1993 14:30:54   MARTIN
// uConnectCOnt
// 
//    Rev 1.14   21 May 1993 17:16:50   MARTIN
// uStretchCont
// 
//    Rev 1.13   18 May 1993 17:41:34   MARTIN
// uExpVal, uPowVal
// 
//    Rev 1.12   05 May 1993 11:05:16   MARTIN
// uEstimateTang...
// 
//    Rev 1.11   18 Apr 1993 18:52:36   HANNES
// Umstellen von RunData auf ListData
// 
//    Rev 1.10   02 Apr 1993 17:52:04   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.9   17 Mar 1993 18:08:52   MARTIN
// 32 Bit Umstellung der Scripts
// 
//    Rev 1.8   17 Feb 1993 15:22:54   HANNES
// bDatExist
// 
//    Rev 1.7   16 Feb 1993 13:12:50   HANNES
// Erweiterungen der long Arithmetik
// 
//    Rev 1.6   05 Feb 1993 19:31:20   MARTIN
// uSubVect
// 
//    Rev 1.5   01 Feb 1993 12:05:26   HANNES
// Einbau der Klasse VTO
// 
//    Rev 1.4   21 Jan 1993 22:36:28   HANNES
// Korrekturen...
// 
//    Rev 1.3   21 Jan 1993 20:26:12   HANNES
// uAddVect,uGenVect neu
// 
//    Rev 1.2   18 Jan 1993 16:45:40   HANNES
// Aenderungen des Handlings von EM_UPDATE, EM_CLEAR
// 
//    Rev 1.1   18 Dec 1992 12:44:10   HANNES
// Neu Funktion: uCopyCont
// 
//    Rev 1.0   02 Dec 1992 15:28:42   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
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

#include "ddsmsg.h"
#include "cont.hpp"
#define CALCVAL_MAIN
#include "calcval.hpp"
#define MODULENUM 149
#include "winass.hpp"

#pragma pack(1)
struct uSetValPar {
  WORD ParSize;
  // Parameter
  WORD RecordType;
  WORD Ident;
  DWORD val;
  };
#pragma pack()

BOOL uSetVal (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uSetValPar FAR *par = (uSetValPar FAR *) param;
    DBWIN_ASSERT (c->IsConst (par->val));
    float v = c->ReadConstFloat (par->val);
    c->WriteData (par->RecordType,par->Ident,&v,sizeof (float),
        LPSTR(param)-sizeof(WORD),((mode & EM_CHANGETOTRUE) != 0));
    }
  return FALSE;
  }


typedef void * (* CALCFNC) (pv FAR *args);

////////////////////////////////////////////////////////////
//  Verwaltung von linearen Listen
////////////////////////////////////////////////////////////
#pragma pack(1)
struct LinListEle {
  LinListEle FAR *Next;
  WORD Ident;
  };
#pragma pack()

void PushListData (LPVOID FAR &start,WORD Ident,LPVOID data,int size)
  {
  LinListEle FAR *le = (LinListEle FAR *) 
      GetGlobMem (sizeof (*le) + size);
  le->Next = (LinListEle FAR *) start ;
  start = le;
  le->Ident = Ident;
  lmemcpy (le+1,data,size);
  }

LPVOID GetListData (LPVOID start,WORD Ident)
  {
  for (LinListEle FAR *s = (LinListEle FAR *) start ; 
        ((s != NULL) && (s->Ident != Ident)) ; 
            s = s->Next);
  return ((s != NULL) && (s->Ident == Ident)) ? s + 1 : NULL ;
  }

void DelListData (LPVOID FAR &start,WORD Ident)
  {
  LinListEle FAR *s = (LinListEle FAR *) start ;
  LinListEle FAR *sn,FAR *prev;
  for ( prev = NULL ; s != NULL ; s = sn ) {
    sn = s->Next ;
    if (s->Ident == Ident) {
      if (prev != NULL)
        prev->Next = sn ;
      else
        start = sn;
      FreeGlobMem (s);
      }
    else
      prev = s;
    }
  }

/*------------------------------------------------
        Verwaltung der numerischen Funktionen
-------------------------------------------------*/
#define MAX_ARGS 50

#define PAR_LONG        0       // Long - Konstante
#define PAR_DEC         1       // Dezimal - Konstante
#define PAR_FLOAT       2       // Dezimal - Variable
#define PAR_POINT       3       // Punkt - Variable
#define PAR_INT         4       // Integer - Variable
#define PAR_CONT        5       // Kontur - Variable
#define PAR_DATE        6       // Datums - Variable
#define PAR_LONGVAR     7       // Long - Varialble
#define PAR_TIME        8       // Zeit - Variable
#define PAR_QLONGVAR    9       // long double - Variable

#pragma pack(1)
struct pardsc {
  unsigned must_exist : 1 ; // parameter muss definiert sein
  unsigned do_check : 1 ;   // Parameter soll in die Updatekette gehaengt werden
  unsigned type : 4 ;       // Typ des Parameters
  unsigned dbase : 1 ;      // Konstante oder aus Datenbank
  };
#pragma pack()

int SetConnections (mdiChild *c,pardsc *dsc,ValPar FAR *par,LPVOID cmd)
  {
  WORD ActOffset = 0;
  for (int i = 0 ; ; i++) {
    if (ActOffset + sizeof (ValPar) - sizeof (BYTE) >= par->ParSize)
      break ;
    switch (dsc[i].type) {
      case PAR_LONG  :
        ActOffset += sizeof (LONG) ;
        dsc[i].dbase = FALSE ;
        break ;
      case PAR_DEC   :
        ActOffset += sizeof (float) ;
        dsc[i].dbase = FALSE ;
        break ;
      case PAR_FLOAT :
      case PAR_POINT :
      case PAR_INT   :
      case PAR_CONT  :
      case PAR_DATE  :
      case PAR_TIME  :
      case PAR_LONGVAR  :
      case PAR_QLONGVAR  :
        if (i >= 1) {
          keydef FAR *kd = (keydef FAR *) (par->arg + ActOffset) ;
          c->SetConnection (kd->Rec,kd->Ident,cmd);
          dsc[i].dbase = TRUE ;
          }
        ActOffset += sizeof (keydef) ;
        break ;
      }
    }
  return i ;
  }

int ClearConnections (mdiChild *c,pardsc *dsc,ValPar FAR *par,LPVOID cmd)
  {
  WORD ActOffset = 0;
  for (int i = 0 ; ; i++) {
    if (ActOffset + sizeof (ValPar) - sizeof (BYTE) >= par->ParSize)
      break ;
    switch (dsc[i].type) {
      case PAR_LONG  :
        ActOffset += sizeof (LONG) ;
        dsc[i].dbase = FALSE ;
        break ;
      case PAR_DEC   :
        ActOffset += sizeof (float) ;
        dsc[i].dbase = FALSE ;
        break ;
      case PAR_FLOAT :
      case PAR_POINT :
      case PAR_INT   :
      case PAR_CONT  :
      case PAR_DATE  :
      case PAR_TIME  :
      case PAR_LONGVAR  :
      case PAR_QLONGVAR  :
        if (i >= 1) {
          keydef FAR *kd = (keydef FAR *) (par->arg + ActOffset) ;
          c->ClearConnection (kd->Rec,kd->Ident,cmd);
          dsc[i].dbase = TRUE ;
          }
        ActOffset += sizeof (keydef) ;
        break ;
      }
    }
  return i ;
  }

void GetPtr (mdiChild *c,pardsc *dsc,pv FAR *args,ValPar FAR *par)
  {
  WORD ActOffset = sizeof (keydef) ;    // 0. Parameter == Resultat
  for (int i = 1 ; ; i++) {
    if (ActOffset + sizeof (ValPar) - sizeof (BYTE) >= par->ParSize)
      break ;
    switch (dsc[i].type) {
      case PAR_LONG :
        args[i] = par->arg + ActOffset ;
        ActOffset += sizeof (LONG) ;
        break ;
      case PAR_DEC :
        args[i] = par->arg + ActOffset ;
        ActOffset += sizeof (float) ;
        break ;
      case PAR_FLOAT :
      case PAR_POINT :
      case PAR_INT   :
      case PAR_CONT  :
      case PAR_DATE  :
      case PAR_TIME  :
      case PAR_LONGVAR  :
      case PAR_QLONGVAR  :
        keydef FAR *kd = (keydef FAR *) (par->arg + ActOffset) ;
        args[i] = c->ReadData (kd->Rec,kd->Ident);
        ActOffset += sizeof (keydef) ;
        break ;
      }
    }
  }

void PutRes (mdiChild *c,ValPar FAR *par,void *res,pardsc *dsc)
  {
  keydef FAR *kd = (keydef FAR *) (par->arg) ;
  BOOL done = FALSE;
  LPVOID old = c->TryToReadData (MAKELONG(kd->Rec,kd->Ident),&done);
  switch (dsc[0].type) {
    case PAR_FLOAT :
      if ((res != NULL) && ((old == NULL) || 
                  (*(float *) res != *(float FAR *) old)))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(float),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_POINT :
      if ((res != NULL) && ((old == NULL) ||
            (hypot (((fpt FAR *) old)->x - ((fpt *) res)->x,
                        ((fpt FAR *) old)->y - ((fpt *) res)->y) > EPSILON)))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(fpt),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_CONT :
      if (res != NULL) {
        contdsc *cnt = (contdsc *) res ;
        void FAR *cntData = GlobalLock (cnt->Contmem) ;
        c->WriteData (kd->Rec,kd->Ident,cntData,cnt->ContSize,LPSTR(par)-sizeof(WORD));
        GlobalUnlock (cnt->Contmem);
        GlobalFree (cnt->Contmem);
        }
      else 
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_INT :
      if ((res != NULL) && 
            ((old == NULL) || (*(DBINT FAR *) old != *(DBINT FAR *) res)))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(DBINT),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_LONGVAR :
      if ((res != NULL) && 
            ((old == NULL) || (*(long FAR *) old != *(long *) res)))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(long),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_QLONGVAR :
      if ((res != NULL) && 
            ((old == NULL) || (*(long double FAR *) old != *(long double *) res)))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(long double),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_DATE :
      if ((res != NULL) &&
          ((old == NULL) || !(lmemcmp (old,res,sizeof(packdate)))))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(packdate),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    case PAR_TIME :
      if ((res != NULL) &&
          ((old == NULL) || !(lmemcmp (old,res,sizeof(packtime)))))
        c->WriteData (kd->Rec,kd->Ident,res,sizeof(packtime),LPSTR(par)-sizeof(WORD));
      else if ((res == NULL) && ((old != NULL) || (!done)))
        c->DelData (kd->Rec,kd->Ident,LPSTR(par)-sizeof(WORD));
      break ;
    }
  }

pv FAR *argStack[64];
int argStackPtr = 0;
pv FAR *GetArgs ()
  {
  if (argStack[argStackPtr] == NULL)
    argStack[argStackPtr] = (pv FAR *)GetGlobMem (MAX_ARGS * sizeof(pv));
  else
    lmemset(argStack[argStackPtr],'\0',MAX_ARGS * sizeof(pv));
  return argStack[argStackPtr ++ ];
  }
void FreeArgs ()
  {
  argStackPtr -- ;
  }
void FreeAllArgs ()
  {
  for (int i = 0 ; i < (sizeof(argStack) / sizeof(argStack[0])) ; i++) {
    if (argStack[i] != NULL) FreeGlobMem (argStack[i]) ;
    argStack[i] = NULL ;
    argStackPtr = 0 ;
    }
  }
void calcVal (mdiChild *c,pardsc *dsc,void FAR *param,WORD mode,CALCFNC calc)
  {
  ValPar FAR *par = (ValPar FAR *) param ;
  void *res;

  if (mode & EM_LOAD) {
    // Laden aller Zeiger
    pv FAR *args = GetArgs ();
    GetPtr (c,dsc,args,par);

    // Berechnen des Wertes
    res = (* calc) (args) ;

    // Ab in die Datenbank 
    PutRes (c,par,res,dsc);
    FreeArgs ();
    }

  if (mode & EM_UPDATE) {
    // Berechnung der Werte, Vergleichen mit den Alten werten und
    // Geaenderte werte in der Datenbank setzten
    pv FAR *args = GetArgs();
    GetPtr (c,dsc,args,par);

    res = (* calc) (args) ;

    PutRes (c,par,res,dsc);
    FreeArgs ();
    }

  if (mode & EM_FIXCONNECTION) 
    // Setzen der Datenbankverbindung
    SetConnections (c,dsc,par,LPSTR(param)-sizeof(WORD));

  if (mode & (EM_CLEAR | EM_RESET))
    // Loeschen der Datenbankverbindung
    ClearConnections (c,dsc,par,LPSTR(param)-sizeof(WORD));

  }

BOOL uPtDist (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ptDistPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,ptDistPar,param,mode,CALCFNC (ptdist));
  return FALSE ;
  }

BOOL uSmoothCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SmoothContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,SmoothContPar,param,mode,CALCFNC (sm_cont));
  return FALSE ;
  }

BOOL uSmoothCycCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SmoothCycContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,SmoothCycContPar,param,mode,CALCFNC (sm_cyccont));
  return FALSE ;
  }

BOOL uCalcRelPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CalcRelPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 }
  };
  calcVal (c,CalcRelPtPar,param,mode,CALCFNC (crpt));
  return FALSE ;
  }

BOOL uLinInt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc LinIntPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,LinIntPar,param,mode,CALCFNC (LinInt));
  return FALSE ;
  };

BOOL uCombineCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CombineContPar[] = {
  { 0 , 0 , PAR_CONT , 0 } ,    // Resultat
  { 0 , 0 , PAR_INT , 0 } ,    // Anzahl der Punkte der resultierenden Kont.
  { 0 , 0 , PAR_FLOAT  , 0 } ,    // Haerte der Glaettung
  { 0 , 0 , PAR_INT , 0 } ,    // Anzahl der zusammenhaengenden Konturen
  { 0 , 1 , PAR_CONT , 0 } ,    // Ausgangskontur
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 }
  };
  calcVal (c,CombineContPar,param,mode,CALCFNC (cm_cont));
  return FALSE ;
  }

BOOL uConnectCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ConnectContPar[] = {
  { 0 , 0 , PAR_CONT , 0 } ,    // Resultat
  { 0 , 0 , PAR_INT , 0 } ,    // Anzahl der zusammenhaengenden Konturen
  { 0 , 1 , PAR_CONT , 0 } ,    // Ausgangskontur
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 }
  };
  calcVal (c,ConnectContPar,param,mode,CALCFNC (conn_cont));
  return FALSE ;
  }

BOOL uPerpPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PerpPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  };
  calcVal (c,PerpPtPar,param,mode,CALCFNC (PerpPt));
  return FALSE ;
  }

BOOL uParPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ParPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  };
  calcVal (c,ParPtPar,param,mode,CALCFNC (ParPt));
  return FALSE ;
  }

BOOL uCntMax (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CntMaxPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  };
  calcVal (c,CntMaxPar,param,mode,CALCFNC (CntMax));
  return FALSE ;
  }

BOOL uCntCro (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CntCroPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_INT , 0 }
  };
  calcVal (c,CntCroPar,param,mode,CALCFNC (CntCro));
  return FALSE ;
  }

BOOL uCntMaxAng (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CntMaxAngPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_INT , 0 }
  };
  calcVal (c,CntMaxAngPar,param,mode,CALCFNC (CntMaxAng));
  return FALSE ;
  }

BOOL uCntNea (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CntNeaPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  };
  calcVal (c,CntNeaPar,param,mode,CALCFNC (CntNea));
  return FALSE ;
  }

BOOL uEstimateTang (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc EstTangPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  };
  calcVal (c,EstTangPar,param,mode,CALCFNC (EstTang));
  return FALSE ;
  }

BOOL uTurningPoint (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc TurnPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_INT , 0 }
  };
  calcVal (c,TurnPtPar,param,mode,CALCFNC (TurnPt));
  return FALSE ;
  }

BOOL uPtPro (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PtProPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,PtProPar,param,mode,CALCFNC (PtPro));
  return FALSE ;
  }

BOOL uExtSmoothCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ExtSmoothContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  } ;
  calcVal (c,ExtSmoothContPar,param,mode,CALCFNC (smext_cont));
  return FALSE ;
  }

BOOL uAddFixVect (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddFixVectPar[] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 0 , PAR_FLOAT , 0 } 
  };
  calcVal (c,AddFixVectPar,param,mode,CALCFNC (AddFixVect));
  return FALSE ;
  }

BOOL uMaxPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MaxPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,MaxPtPar,param,mode,CALCFNC (MaxPt));
  return FALSE ;
  }

BOOL uDiffYears (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DiffYearsPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_DATE , 0 }
  };
  calcVal (c,DiffYearsPar,param,mode,CALCFNC (DiffYears));
  return FALSE ;
  }

BOOL uMulVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MulValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,MulValPar,param,mode,CALCFNC (MulVal));
  return FALSE ;
  }

BOOL uExpVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ExpValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,ExpValPar,param,mode,CALCFNC (ExpVal));
  return FALSE ;
  }

BOOL uPowVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PowValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,PowValPar,param,mode,CALCFNC (PowVal));
  return FALSE ;
  }

BOOL uAddVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,AddValPar,param,mode,CALCFNC (AddVal));
  return FALSE ;
  }

BOOL uDivVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DivValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,DivValPar,param,mode,CALCFNC (DivVal));
  return FALSE ;
  }

BOOL uSubVal (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SubValPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,SubValPar,param,mode,CALCFNC (SubVal));
  return FALSE ;
  }

BOOL uPtNDist (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PtNDistPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,PtNDistPar,param,mode,CALCFNC (ptndist));
  return FALSE ;
  }

BOOL uPtPDist (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PtPDistPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,PtPDistPar,param,mode,CALCFNC (ptpdist));
  return FALSE ;
  }

BOOL uDiffAng (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DiffAngPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  } ;
  calcVal (c,DiffAngPar,param,mode,CALCFNC (DiffAng));
  return FALSE ;
  }

BOOL uValRange (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ValRangePar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } 
  } ;
  calcVal (c,ValRangePar,param,mode,CALCFNC (ValRange));
  return FALSE ;
  }

BOOL uDevInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DevIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  } ;
  calcVal (c,DevIndPar,param,mode,CALCFNC (GetDevInd));
  return FALSE ;
  }

BOOL uTrcDevInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc TrcDevIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,TrcDevIndPar,param,mode,CALCFNC (GetTrcDevInd));
  return FALSE ;
  }

BOOL uDivideCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DevideContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  } ;
  calcVal (c,DevideContPar,param,mode,CALCFNC (doContDivide));
  return FALSE ;
  }

BOOL uSymmetrieLine (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SymmetrieLinePar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,SymmetrieLinePar,param,mode,CALCFNC (GetSymmetrieLine));
  return FALSE ;
  }

BOOL uGet33Arr (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc Get33ArrPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,Get33ArrPar,param,mode,CALCFNC (Get33Arr));
  return FALSE ;
  }

BOOL uGenAgeNorm (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GenAgeNormPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,GenAgeNormPar,param,mode,CALCFNC (GenAgeNorm));
  return FALSE ;
  }

BOOL uArcInt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ArcIntPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,ArcIntPar,param,mode,CALCFNC (ArcInt));
  return FALSE ;
  }

BOOL uCalcMiddDev (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CalcMiddDevPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  } ;
  calcVal (c,CalcMiddDevPar,param,mode,CALCFNC (CalcMiddDev));
  return FALSE ;
  }

BOOL uArcSin (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ArcSinPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  } ;
  calcVal (c,ArcSinPar,param,mode,CALCFNC (ArcSin));
  return FALSE ;
  }

BOOL uCopyCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CopyContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 }
  };
  calcVal (c,CopyContPar,param,mode,CALCFNC (CopyCont));
  return FALSE ;
  }

BOOL uGenVect (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GenVectPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,GenVectPar,param,mode,CALCFNC (GenVect));
  return FALSE ;
  }

BOOL uAddVect (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddVectPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,AddVectPar,param,mode,CALCFNC (AddVect));
  return FALSE ;
  }

BOOL uSubVect (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SubVectPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,SubVectPar,param,mode,CALCFNC (SubVect));
  return FALSE ;
  }

BOOL uAddLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddLongPar [] = {
  { 0 , 0 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,AddLongPar,param,mode,CALCFNC (AddLong));
  return FALSE ;
  }

BOOL uSubLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SubLongPar [] = {
  { 0 , 0 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,SubLongPar,param,mode,CALCFNC (SubLong));
  return FALSE ;
  }

BOOL uDivLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DivLongPar [] = {
  { 0 , 0 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,DivLongPar,param,mode,CALCFNC (DivLong));
  return FALSE ;
  }

BOOL uMulLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MulLongPar [] = {
  { 0 , 0 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,MulLongPar,param,mode,CALCFNC (MulLong));
  return FALSE ;
  }

BOOL uMaskLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MaskLongPar [] = {
  { 0 , 0 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,MaskLongPar,param,mode,CALCFNC (MaskLong));
  return FALSE ;
  }

BOOL uFindLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc FindLongPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,FindLongPar,param,mode,CALCFNC (FindLong));
  return FALSE ;
  }

BOOL uGetLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetLongPar [] = {
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 } ,
  { 0 , 1 , PAR_LONGVAR , 0 }
  };
  calcVal (c,GetLongPar,param,mode,CALCFNC (GetLong));
  return FALSE ;
  }

BOOL uGetIndDec (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetIndDecPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,GetIndDecPar,param,mode,CALCFNC (GetIndDec));
  return FALSE ;
  }

BOOL uCntmCro (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CntmCroPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,CntmCroPar,param,mode,CALCFNC (CntmCro));
  return FALSE ;
  }


BOOL uStretchCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc StretchContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 }
  };
  calcVal (c,StretchContPar,param,mode,CALCFNC (StretchCont));
  return FALSE ;
  }

BOOL uAddDays (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddDaysPar [] = {
  { 0 , 0 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,AddDaysPar,param,mode,CALCFNC (AddDays));
  return FALSE ;
  }

BOOL uAddInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,AddIndPar,param,mode,CALCFNC (AddInd));
  return FALSE ;
  }

BOOL uSubInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SubIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,SubIndPar,param,mode,CALCFNC (SubInd));
  return FALSE ;
  }

BOOL uMulInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MulIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,MulIndPar,param,mode,CALCFNC (MulInd));
  return FALSE ;
  }

BOOL uDivInd (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DivIndPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,DivIndPar,param,mode,CALCFNC (DivInd));
  return FALSE ;
  }

BOOL uAddMonths (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddMonthsPar [] = {
  { 0 , 0 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,AddMonthsPar,param,mode,CALCFNC (AddMonths));
  return FALSE ;
  }

BOOL uAddYears (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddYearsPar [] = {
  { 0 , 0 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_INT  , 0 }
  };
  calcVal (c,AddYearsPar,param,mode,CALCFNC (AddYears));
  return FALSE ;
  }

BOOL uGetThirdPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetThirdPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 } ,
  { 0 , 0 , PAR_INT , 0 }
  };
  calcVal (c,GetThirdPtPar,param,mode,CALCFNC (fGetThirdPt));
  return FALSE ;
  }

BOOL uGetNAbstPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetNAbstPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 }
  };
  calcVal (c,GetNAbstPtPar,param,mode,CALCFNC (fGetNAbstPt));
  return FALSE ;
  }

BOOL uGetRotPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetRotPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 } ,
  { 0 , 1 , PAR_FLOAT  , 0 }
  };
  calcVal (c,GetRotPtPar,param,mode,CALCFNC (fGetRotPt));
  return FALSE ;
  }

BOOL uCalcNewPt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CalcNewPtPar [] = {
  { 0 , 0 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 0 , PAR_FLOAT   , 0 } ,
  { 0 , 0 , PAR_FLOAT   , 0 }
  };
  calcVal (c,CalcNewPtPar,param,mode,CALCFNC (crpt));
  return FALSE ;
  }

BOOL uSin (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SinPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,SinPar,param,mode,CALCFNC (GetSin));
  return FALSE ;
  }

BOOL uCos (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc CosPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,CosPar,param,mode,CALCFNC (GetCos));
  return FALSE ;
  }

BOOL uAddYearsDec (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddYearsDecPar [] = {
  { 0 , 0 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_DATE , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,AddYearsDecPar,param,mode,CALCFNC (AddYearsDec));
  return FALSE ;
  }

BOOL uDiffTime (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DiffTimePar [] = {
  { 0 , 0 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_TIME , 0 }
  };
  calcVal (c,DiffTimePar,param,mode,CALCFNC (DiffTime));
  return FALSE ;
  }

BOOL uSetTime (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SetTimePar [] = {
  { 0 , 0 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 }
  };
  calcVal (c,SetTimePar,param,mode,CALCFNC (SetTime));
  return FALSE ;
  }

BOOL uAddTime (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddTimePar [] = {
  { 0 , 0 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_TIME , 0 }
  };
  calcVal (c,AddTimePar,param,mode,CALCFNC (AddTime));
  return FALSE ;
  }

BOOL uAddRelTime (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddRelTimePar [] = {
  { 0 , 0 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_TIME , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_INT , 0 } 
  };
  calcVal (c,AddRelTimePar,param,mode,CALCFNC (AddRelTime));
  return FALSE ;
  }

BOOL uGetx (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetXPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  };
  calcVal (c,GetXPar,param,mode,CALCFNC (GetX));
  return FALSE ;
  }

BOOL uGety (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc GetYPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  };
  calcVal (c,GetYPar,param,mode,CALCFNC (GetY));
  return FALSE ;
  }

BOOL uClipCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc ClipContPar [] = {
  { 0 , 0 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } 
  };
  calcVal (c,ClipContPar,param,mode,CALCFNC (ClipCont));
  return FALSE ;
  }

BOOL uAddQLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc AddQLongPar [] = {
  { 0 , 0 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 }
  };
  calcVal (c,AddQLongPar,param,mode,CALCFNC (AddQLong));
  return FALSE ;
  }

BOOL uSubQLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc SubQLongPar [] = {
  { 0 , 0 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 }
  };
  calcVal (c,SubQLongPar,param,mode,CALCFNC (SubQLong));
  return FALSE ;
  }

BOOL uDivQLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc DivQLongPar [] = {
  { 0 , 0 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 }
  };
  calcVal (c,DivQLongPar,param,mode,CALCFNC (DivQLong));
  return FALSE ;
  }

BOOL uMulQLong (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc MulQLongPar [] = {
  { 0 , 0 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 } ,
  { 0 , 1 , PAR_QLONGVAR , 0 }
  };
  calcVal (c,MulQLongPar,param,mode,CALCFNC (MulQLong));
  return FALSE ;
  }

BOOL uPtInCont (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc PtInContPar [] = {
  { 0 , 0 , PAR_INT , 0 } ,
  { 0 , 1 , PAR_POINT , 0 } ,
  { 0 , 1 , PAR_CONT , 0 }
  };
  calcVal (c,PtInContPar,param,mode,CALCFNC (PtInCont));
  return FALSE ;
  }

BOOL usqrt (mdiChild *c,void FAR *param,WORD mode)
  {
static pardsc usqrtPar [] = {
  { 0 , 0 , PAR_FLOAT , 0 } ,
  { 0 , 1 , PAR_FLOAT , 0 }
  };
  calcVal (c,usqrtPar,param,mode,CALCFNC (dosqrt));
  return FALSE ;
  }

