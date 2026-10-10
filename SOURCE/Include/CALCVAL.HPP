#define EPSILON         1.0E-4
// $Header:   P:/marille/clinicum/include/rev/calcval.hpv   1.11   27 Apr 1999 01:48:38   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/calcval.hpv  $
// 
//    Rev 1.11   27 Apr 1999 01:48:38   Hannes
// dosqrt
// 
//    Rev 1.10   19 Nov 1997 18:45:18   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.9   08 Nov 1996 13:35:38   HANNES
// QLong Funktionen
// 
//    Rev 1.8   22 Jul 1996 21:57:26   HANNES
// inres ... Umbau auf DBINT
// 
//    Rev 1.7   10 Jun 1996 10:14:44   GERHOLD
// pragma pack
// 
//    Rev 1.6   02 Feb 1996 10:59:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   27 Aug 1995 13:05:38   HANNES
// 
//    Rev 1.4   20 Mar 1995 12:07:30   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.3   24 Feb 1995 11:17:54   HANNES
//  
// 
//    Rev 1.2   07 Sep 1994 10:50:20   HANNES
// 
//    Rev 1.1   05 Aug 1994 20:23:14   HANNES
// DiffTime
// 
//    Rev 1.0   24 Jun 1994 17:01:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.19   29 Nov 1993 08:46:14   HANNES
// AddDateYears
// 
//    Rev 1.18   16 Nov 1993 04:24:10   HANNES
// Einbindung der Konstruktionsfunktionen
// 
//    Rev 1.17   27 Sep 1993 19:29:08   HANNES
// 
//    Rev 1.16   24 Sep 1993 22:43:40   HANNES
// Private Daten der Rechenfunktion raus
// 
//    Rev 1.15   22 Sep 1993 09:23:08   HANNES
// Version nach St. Poelten
// 
//    Rev 1.14   24 Aug 1993 10:34:00   HANNES
// uAddDate
// 
//    Rev 1.13   18 Jun 1993 15:15:16   MARTIN
// Prototypen der Berechnungsfunktionen
// 
//    Rev 1.12   02 Jun 1993 22:21:02   MARTIN
// TurnPt
// 
//    Rev 1.11   24 May 1993 14:31:32   MARTIN
// conn_cont
// 
//    Rev 1.10   21 May 1993 17:18:06   MARTIN
// uStretchCont
// 
//    Rev 1.9   18 May 1993 17:42:38   MARTIN
// uExpVal, uPowVal
// 
//    Rev 1.8   05 May 1993 12:18:58   MARTIN
// esttang
// 
//    Rev 1.7   18 Apr 1993 22:49:38   HANNES
// Umstellen von RunData auf ListData
// 
//    Rev 1.6   02 Apr 1993 17:53:44   HANNES
// Strukturbereinigung
// 
//    Rev 1.5   17 Mar 1993 18:07:12   HANNES
// Strukturbereinigung, uDevDecInd..
// 
//    Rev 1.4   16 Feb 1993 13:10:40   HANNES
// Erweiterungen der long Arithmetik
// 
//    Rev 1.3   05 Feb 1993 19:30:58   MARTIN
// uSubVect
// 
//    Rev 1.2   21 Jan 1993 22:46:58   HANNES
// uGenVect,uAddVect...
// 
//    Rev 1.1   18 Dec 1992 12:45:22   HANNES
// Neue Funktion (CopyCont)
// 
//    Rev 1.0   02 Dec 1992 15:51:20   HANNES
// Initial revision.

#pragma pack(1)
typedef struct tag_keydef {
  WORD Rec;
  WORD Ident;
  } keydef ;
#pragma pack()

#pragma pack(1)
struct ValPar {
  WORD ParSize;
  // Private Daten
//  LPVOID hOldRunList ;
  // Parameter - Daten  (variable Laenge)
  BYTE arg[1];
  };
#pragma pack()

typedef fpt FAR *pp;
typedef float FAR *pf;
typedef void FAR *pv;

#pragma pack(1)
struct contdsc {
  WORD ContSize;        // Groesse der Kontur in Byte
  GLOBALHANDLE Contmem; // GlobalHandle der neuen Kontur
  };
#pragma pack()

union calcresbuffer {
  float floatres;
  fpt fptres;
  DBINT inres;
  contdsc cntres ;
  packdate pd;
  LONG lres;
  packtime pt;
  long double qlong;
  } ;

#ifdef CALCVAL_MAIN
calcresbuffer result;
#else
extern calcresbuffer result;
#endif

void *ptdist (pv FAR *args);
void *sm_cont (pv FAR *args);
void *sm_cyccont (pv FAR *args);
void *smext_cont (pv FAR *args);
void *cm_cont (pv FAR *args);
void *crpt (pv FAR *args);
void *LinInt (pv FAR *args);
void *PtPro (pv FAR *args);
void *PerpPt (pv FAR *args);
void *ParPt (pv FAR *args);
void *CntMax (pv FAR *args);
void *CntCro (pv FAR *args);
void *CntMaxAng (pv FAR *args);
void *CntNea (pv FAR *args);
void *EstTang (pv FAR *args);
void *TurnPt (pv FAR *args);
void *AddFixVect (pv FAR *args);
void *MaxPt (pv FAR *args);
void *DiffYears (pv FAR *args);
void *MulVal (pv FAR *args);
void *ExpVal (pv FAR *args);
void *PowVal (pv FAR *args);
void *AddVal (pv FAR *args);
void *DivVal (pv FAR *args);
void *SubVal (pv FAR *args);
void * ptndist (pp FAR *p);
void * ptpdist (pp FAR *p);
double arcus (double y, double x);
void * DiffAng (pp FAR *p);
void * ValRange (pv FAR *args);
void * GetDevInd (pv FAR *args);
void * GetTrcDevInd (pv FAR *args);
void * GetSymmetrieLine (pv FAR *args);
void * Get33Arr (pv FAR *args);
void * doContDivide (pv FAR *args);
void * GenAgeNorm (pv FAR *args);
void * ArcInt (pv FAR *args);
void * CalcMiddDev (pv FAR *args);
void * ArcSin (pv FAR *args);
void * CopyCont (pv FAR *args);
void * GenVect (pv FAR *args);
void * AddVect (pv FAR *args);
void * SubVect (pv FAR *args);
void * AddLong (pv FAR *args);
void * SubLong (pv FAR *args);
void * MulLong (pv FAR *args);
void * DivLong (pv FAR *args);
void * MaskLong (pv FAR *args);
void * FindLong (pv FAR *args);
void * GetLong (pv FAR *args);
#define MAXARRDIM 9
void * GetIndDec (pv FAR *args);
void * CntmCro (pv FAR *args);
void * StretchCont (pv FAR *args);
void * conn_cont (pv FAR *args);
void *AddDays (pv FAR *args);
void *AddInd (pv FAR *args);
void *SubInd (pv FAR *args);
void *MulInd (pv FAR *args);
void *DivInd (pv FAR *args);
void *AddMonths (pv FAR *args);
void *AddYears (pv FAR *args);
void *fGetThirdPt (pv FAR *args);
void *fGetNAbstPt (pv FAR *args);
void *fGetRotPt (pv FAR *args);
void *GetSin (pv FAR *args);
void *GetCos (pv FAR *args);
void *AddYearsDec (pv FAR *args);
void *DiffTime (pv FAR *args);
void *SetTime (pv FAR *args);
void *AddTime (pv FAR *args);
void *AddRelTime (pv FAR *args);
void *GetX (pv FAR *args);
void *GetY (pv FAR *args);
void *ClipCont (pv FAR *p);
void * AddQLong (pv FAR *args);
void * SubQLong (pv FAR *args);
void * MulQLong (pv FAR *args);
void * DivQLong (pv FAR *args);
void * PtInCont (pv FAR *args);
void * dosqrt (pv FAR *args);

