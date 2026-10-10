// 
// Funktionen, die in der Scriptsprache zur Verfuegung stehen.
//
// $Header:   P:/marille/clinicum/rev/func0.cpv   1.47   02 Jun 2000 14:42:16   Gerhold  $
// $Log:   P:/marille/clinicum/rev/func0.cpv  $
// 
//    Rev 1.47   02 Jun 2000 14:42:16   Gerhold
// Zufallszahlengenerator
// 
//    Rev 1.46   14 Dec 1999 06:11:06   Hannes
// BlockCopy
// 
//    Rev 1.45   15 Jun 1999 16:29:52   WOLFGANG
// 1.) TimeNow durch Now ersetzt.
// 
//    Rev 1.44   18 Nov 1998 15:50:18   Hannes
// Zeitumstellung auf QLong
// 
//    Rev 1.43   14 Sep 1998 03:24:06   Hannes
// SetIndElement: ClearConnection auf Index
// 
//    Rev 1.42   04 Aug 1998 17:54:38   Hannes
// Timestamp
// 
//    Rev 1.41   08 Jul 1998 11:00:50   Hannes
// 
//    Rev 1.40   09 Jan 1998 12:06:18   Hannes
// 
//    Rev 1.39   09 Dec 1997 16:24:54   Gerhold
// bIsValInNorm ... fabs benoetigt "double" als Parameter
// 
//    Rev 1.38   29 Aug 1997 18:31:12   Hannes
// Clearconn bei CombineData (Hannes)
// DBINT statt int bei ExtractTime
// 
//    Rev 1.37   07 Apr 1997 16:46:14   Hannes
// pragma pack()
// 
//    Rev 1.36   19 Feb 1997 10:08:02   Martin
// mShowMessageBox: ClearConnections um Expressions aufzuraeumen
// 
//    Rev 1.35   10 Feb 1997 17:49:46   martin
// bCmpQLong
// 
//    Rev 1.34   26 Nov 1996 08:14:10   HANNES
// Automatischer Update
// 
//    Rev 1.33   08 Nov 1996 13:32:52   HANNES
// QLong - Konvertierungen
// 
//    Rev 1.32   05 Nov 1996 11:43:28   HANNES
// 
//    Rev 1.31   31 Oct 1996 16:12:52   HANNES
// Erweiterungen von InitializeArrayData
// 
//    Rev 1.30   30 Oct 1996 17:42:00   HANNES
// 
//    Rev 1.29   30 Oct 1996 08:43:24   HANNES
// SetSema als BOOL - Funktion
// 
//    Rev 1.28   28 Oct 1996 08:37:08   HANNES
// SetArrayData,GetArrayData
// 
//    Rev 1.27   10 Jun 1996 10:07:58   GERHOLD
// pragma pack
// 
//    Rev 1.26   02 May 1996 20:42:22   HANNES
// Fehlerkorrektur ExtractData
// 
//    Rev 1.25   02 Feb 1996 10:36:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.24   15 Nov 1995 13:50:20   MARTIN
// ExtractData: end < 0 statt <= 0
// 
//    Rev 1.23   02 Nov 1995 19:09:46   martin
// 
//    Rev 1.22   29 Sep 1995 16:52:22   MARTIN
// >= statt <= in EpandBinary
// 
//    Rev 1.21   16 Sep 1995 02:46:58   HANNES
// 
//    Rev 1.20   11 Sep 1995 20:24:58   MARTIN
// OnSetFocusProc
// 
//    Rev 1.19   24 Aug 1995 00:20:16   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.18   20 May 1995 16:13:34   HANNES
// Datumsvergleiche...
// 
//    Rev 1.17   28 Apr 1995 17:18:06   HANNES
// Konstantenhandling
// 
//    Rev 1.16   30 Mar 1995 10:33:48   HANNES
// No change.
// 
//    Rev 1.15   27 Mar 1995 13:16:44   HANNES
//  
// 
//    Rev 1.14   20 Mar 1995 11:56:02   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.13   03 Mar 1995 18:12:20   HANNES
// 
//    Rev 1.12   24 Feb 1995 11:17:04   HANNES
//  
// 
//    Rev 1.11   29 Jan 1995 11:50:22   HANNES
// 
//    Rev 1.10   22 Jan 1995 15:04:56   HANNES
// Vergleichsoperationen verbessert
// 
//    Rev 1.9   05 Dec 1994 17:42:30   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.8   31 Oct 1994 09:52:12   hannes
// - Die Set Funktionen auch bei EM_UPDATE etwas getan
// - Semaphor - Funktionen
// 
//    Rev 1.7   19 Oct 1994 22:36:10   hannes
// Semaphorhandling
// 
//    Rev 1.6   06 Oct 1994 19:26:38   HANNES
// bWordGreater
// 
//    Rev 1.5   03 Oct 1994 18:02:10   HANNES
// bDateGreater
// 
//    Rev 1.4   20 Sep 1994 11:35:08   HANNES
// bDataEqual
// 
//    Rev 1.3   29 Aug 1994 12:46:02   HANNES
// uDelData auch bei UPDATE
// 
//    Rev 1.2   05 Aug 1994 20:14:06   HANNES
// uTimeNow
// 
//    Rev 1.1   05 Aug 1994 17:12:58   HANNES
// 
//    Rev 1.0   24 Jun 1994 17:05:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.42   13 Apr 1994 14:35:54   HANNES
// SetIndElement, bIndGreater
// 
//    Rev 1.41   09 Feb 1994 15:18:30   HANNES
// GetTwainSources
// 
//    Rev 1.40   04 Feb 1994 16:49:08   HANNES
// bStrIndGreater, LinkDocElements
// 
//    Rev 1.39   12 Jan 1994 11:14:58   HANNES
// Unnoetige Includes entfernt, keine Txt_* - Funktionen mehr
// 
//    Rev 1.38   04 Jan 1994 16:40:44   HANNES
// LinkElemnts verbessern
// 
//    Rev 1.37   09 Dec 1993 14:58:56   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.36   29 Nov 1993 08:53:28   HANNES
// Verschiedene Neuen Funktionen, speziell in Verbindung mit dem Wachstum
// 
//    Rev 1.35   16 Nov 1993 04:22:30   HANNES
// Einbau der Voronoi - Daten
// 
//    Rev 1.34   22 Sep 1993 09:18:42   HANNES
// Version nach St. Poelten
// 
//    Rev 1.33   05 Sep 1993 22:14:38   HANNES
// Aufraeumarbeiten
// 
//    Rev 1.32   23 Aug 1993 19:05:46   MARTIN
// bImageExist umgeschrieben auf String
// 
//    Rev 1.31   18 Aug 1993 10:31:44   HANNES
// ...
// 
//    Rev 1.30   09 Aug 1993 15:07:06   MARTIN
// Set- bzw. ClearConnection fuer ptRec/ptId in uGetImgScale eingebaut
// 
//    Rev 1.29   09 Aug 1993 15:02:20   MARTIN
// Fehler in uGetImgScale korrigiert
// 
//    Rev 1.28   22 Jul 1993 20:53:46   HANNES
// uLinkElemente, uSetIndIndex
// 
//    Rev 1.27   06 Jul 1993 20:05:46   MARTIN
// GetImgScale erweitert um Translationsvektor
// 
//    Rev 1.26   05 Jul 1993 14:40:10   HANNES
// bFindInd.. Untersuchung eines Multilisteneintrages
// 
//    Rev 1.25   18 Jun 1993 15:08:22   MARTIN
// Prototyp von GetData
// 
//    Rev 1.24   17 Jun 1993 09:28:26   HANNES
// bFindIndex
// 
//    Rev 1.23   16 Jun 1993 16:51:30   MARTIN
// uSetMulti, uCopyRefs
// 
//    Rev 1.22   16 Jun 1993 12:05:08   HANNES
// bFindInd
// 
//    Rev 1.21   02 Jun 1993 12:42:32   MARTIN
// uDelData
// 
//    Rev 1.20   29 May 1993 17:00:28   MARTIN
// bIsVTO
// 
//    Rev 1.19   03 May 1993 15:44:48   HANNES
// bYearGreater
// 
//    Rev 1.18   22 Apr 1993 21:02:42   MARTIN
// Anpassung fuer geschnittene Konturen
// 
//    Rev 1.17   09 Apr 1993 21:25:52   MARTIN
// Fehler in SetVTORef korrigiert
// 
//    Rev 1.16   02 Apr 1993 17:33:30   HANNES
// Strukturbereinigung,Beschleunigung
// 
//    Rev 1.15   17 Mar 1993 17:28:10   HANNES
// Strukturbereinigung
// 
//    Rev 1.14   01 Mar 1993 12:26:14   MARTIN
// neue Funktion bLongEqual
// 
//    Rev 1.13   17 Feb 1993 14:28:40   HANNES
// bDatExist
// 
//    Rev 1.12   12 Feb 1993 20:08:12   MARTIN
// Neue Funktion: uPtExplizit
// 
//    Rev 1.11   11 Feb 1993 13:51:28   HANNES
// ???
// 
//    Rev 1.10   05 Feb 1993 19:31:52   MARTIN
// bScaleExist
// 
//    Rev 1.9   02 Feb 1993 19:07:12   HANNES
// GetOrt, GetVorwahl, bStrExist
// 
//    Rev 1.8   29 Jan 1993 18:55:02   HANNES
// Einbau von Frm_RecInd..
// 
//    Rev 1.7   21 Jan 1993 22:36:02   HANNES
// GetDecomp...
// 
//    Rev 1.6   20 Jan 1993 15:16:48   HANNES
// uGetOvPoint fuer allgemeine Datentypen erweitert
// 
//    Rev 1.5   19 Jan 1993 11:28:14   MARTIN
// neue Funktion uSetLong implementiert
// 
//    Rev 1.4   18 Jan 1993 14:40:32   HANNES
// Handhabung von EM_CLEAR, EM_UPDATE
// 
//    Rev 1.3   12 Dec 1992 15:41:14   HANNES
// Abfrage nach existenter Kontrollliste bie bbuttonpressed
// 
//    Rev 1.2   06 Dec 1992 17:35:36   HANNES
// Erweiterung um Frm_ShowString und Frm_relShowString
// 
//    Rev 1.1   06 Dec 1992 16:06:06   HANNES
// Erweiterung um Txt_Date
// 
//    Rev 1.0   02 Dec 1992 15:28:28   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <dos.h>
#include <math.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#define MODULENUM   29
#include "winass.hpp"
#include "reconst.hpp"

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
#include "voronoi.hpp"

#include "cutcont.hpp"
#include "image.hpp"

/*-----------------------------------------------------------*/
/*                                                           */
/*   allgemeinen Funktionen                                  */
/*        (Instanzunabhaengig)                               */
/*                                                           */
/*-----------------------------------------------------------*/
#pragma pack(1)
struct EqualPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  LONG compareVal;
  };
#pragma pack()

extern LPVOID GetLastOffset (void);
BOOL bWordIndGreater (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    DBINT FAR * h = (DBINT FAR *)(c->ReadlData (par->ref));
    DBINT FAR *h1 = (DBINT FAR *)(c->ReadlData (par->compareVal));
    res = ((h != NULL) && (h1 != NULL) && (*h > *h1)) ;
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    c->SetlConnection (par->compareVal,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    c->ClearlConnection (par->compareVal,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct ButtonPressedPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  };
#pragma pack()

BOOL bButtonPressed (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    DBINT FAR *h = (DBINT FAR *)(c->ReadlData (par->ref));
    res = ((h != NULL) && (*h));
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    }
  return res;
  }

BOOL bPointExist (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    fpt FAR *h = (fpt FAR *) (c->ReadlData (par->ref));
    res = ((h != NULL) && (h->x < 1.0E9));
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    }
  return res;
  }

BOOL bContExist (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    fpt FAR *h = (fpt FAR *) (c->ReadlData (par->ref));
    res = ((h != NULL) && ((h->x < 1.0E9) || is_cut(h)));
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    }
  return res;
  }

BOOL bScaleExist (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    tr2 FAR *h = (tr2 FAR *) (c->ReadlData (par->ref));
    res = ((h != NULL) && (h->A[0][0] < 1.0E9));
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct ValGreaterPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  DWORD rcval;
  };
#pragma pack()

BOOL bValGreater (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ValGreaterPar FAR *par = (ValGreaterPar FAR *) param;
    float FAR *h = (float FAR *) (c->ReadlData (par->ref));
    float FAR *cval = (float FAR *) (c->ReadlData (par->rcval));
    res = ((h != NULL) && (*h < 1.0E9) && (cval != NULL) && (*h > *cval));
    }
  if (mode & EM_FIXCONNECTION) {
    ValGreaterPar FAR *par = (ValGreaterPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    c->SetlConnection (par->rcval,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ValGreaterPar FAR *par = (ValGreaterPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    c->ClearlConnection (par->rcval,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct YearGreaterPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  DWORD ryear;
  };
#pragma pack()

BOOL bYearGreater (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    YearGreaterPar FAR *par = (YearGreaterPar FAR *) param;
    packdate FAR *data = (packdate FAR *) c->ReadlData (par->ref);
    DBINT FAR *year = (DBINT FAR *) c->ReadlData (par->ryear);
    res = ((data != NULL) && (year != NULL) && (data->year > WORD(*year)));
    }
  if (mode & EM_FIXCONNECTION) {
    YearGreaterPar FAR *par = (YearGreaterPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    c->SetlConnection (par->ryear,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    YearGreaterPar FAR *par = (YearGreaterPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    c->ClearlConnection (par->ryear,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct DateGreaterPar {
  WORD ParSize;
  // Parameter
  DWORD ref1;
  DWORD ref2;
  };
#pragma pack()

BOOL bDateGreater (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DateGreaterPar FAR *par = (DateGreaterPar FAR *) param;
    packdate FAR *date1 = (packdate FAR *) c->ReadlData (par->ref1);
    packdate FAR *date2 = (packdate FAR *) c->ReadlData (par->ref2);
    res = ((date1 != NULL) && (date2 != NULL) &&
              ((date1->year > date2->year) || 
               (((date1->year == date2->year) && (date1->month > date2->month)) ||
                ((date1->month == date2->month) && (date1->day > date2->day))
               )
              )
          );
    }
  if (mode & EM_FIXCONNECTION) {
    DateGreaterPar FAR *par = (DateGreaterPar FAR *) param;
    c->SetlConnection (par->ref1,GetLastOffset());
    c->SetlConnection (par->ref2,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DateGreaterPar FAR *par = (DateGreaterPar FAR *) param;
    c->ClearlConnection (par->ref1,GetLastOffset());
    c->ClearlConnection (par->ref2,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct LongEqualPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  DWORD rcval;
  };
#pragma pack()

BOOL bLongEqual (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LongEqualPar FAR *par = (LongEqualPar FAR *) param;
    LPDWORD data = LPDWORD (c->ReadlData (par->ref));
    LPDWORD rdata = LPDWORD (c->ReadlData (par->rcval));
    res = ((data != NULL) && (rdata != NULL) && (*data == *rdata)) ;
    }
  if (mode & EM_FIXCONNECTION) {
    LongEqualPar FAR *par = (LongEqualPar FAR *) param;
    c->SetlConnection (par->ref,GetLastOffset());
    c->SetlConnection (par->rcval,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LongEqualPar FAR *par = (LongEqualPar FAR *) param;
    c->ClearlConnection (par->ref,GetLastOffset());
    c->ClearlConnection (par->rcval,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct LongVarEqualPar {
  WORD ParSize;
  // Parameter
  DWORD I1;
  DWORD I2;
  };
#pragma pack()

BOOL bLongVarEqual (mdiChild *c,void FAR *param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LongVarEqualPar FAR *par = (LongVarEqualPar FAR *) param;
    DWORD FAR *I1 = (DWORD FAR *) c->ReadlData (par->I1);
    DWORD FAR *I2 = (DWORD FAR *) c->ReadlData (par->I2);
    res = ((I1 != NULL) && (I2 != NULL) && (*I1 == *I2));
    }
  if (mode & EM_FIXCONNECTION) {
    // Den Beginn der Condition in die Updateliste
    LongVarEqualPar FAR *par = (LongVarEqualPar FAR *) param;
    c->SetlConnection (par->I1,GetLastOffset());
    c->SetlConnection (par->I2,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LongVarEqualPar FAR *par = (LongVarEqualPar FAR *) param;
    c->ClearlConnection (par->I1,GetLastOffset());
    c->ClearlConnection (par->I2,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct SetPointPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  DWORD rx;
  DWORD ry;
  };
#pragma pack()

BOOL uSetPoint (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetPointPar FAR *par = (SetPointPar FAR *) param;
    fpt pt;
    DBWIN_ASSERT (c->IsConst (par->rx));
    DBWIN_ASSERT (c->IsConst (par->ry));
    pt.x = *((float FAR *) c->ReadlData (par->rx)) ;
    pt.y = *((float FAR *) c->ReadlData (par->ry)) ;
    c->WritelData (par->ref,&pt,sizeof (pt),LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

#define EPSILON 1.0E-3

#pragma pack(1)
struct PtExplicit_param {
  WORD ParSize;
  // Parameter
  DWORD pt;           // Vektor
  DWORD f1;           // 1. Wert
  DWORD f2;           // 2. Wert
  };
#pragma pack()

BOOL uPtExplicit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    PtExplicit_param FAR *par = (PtExplicit_param FAR *) param ;
    float FAR *f1 = (float FAR *) c->ReadlData (par->f1);
    float FAR *f2 = (float FAR *) c->ReadlData (par->f2);
    if ((f1 != NULL) && (f2 != NULL)) {
      fpt pt;
      pt.x = *f1 ;  pt.y = *f2 ;
      c->WritelData (par->pt,&pt,sizeof(pt),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->pt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    PtExplicit_param FAR *par = (PtExplicit_param FAR *) param ;
    c->SetlConnection (par->f1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->f2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    PtExplicit_param FAR *par = (PtExplicit_param FAR *) param ;
    c->ClearlConnection (par->f1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->f2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFlagPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  DWORD rstat;
  };
#pragma pack()

BOOL uSetFlag (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetFlagPar FAR *par = (SetFlagPar FAR *) param;
    DBWIN_ASSERT (c->IsConst (par->rstat));
    DBBOOL stat = *((DBBOOL FAR *) c->ReadlData (par->rstat));
    c->WritelData (par->ref,&stat,sizeof (stat),LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct SetLongPar {
  WORD ParSize;
  // Parameter
  DWORD res;
  DWORD rval;
  };
#pragma pack()

BOOL uSetLong (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetLongPar FAR *par = (SetLongPar FAR *) param;
    int i = (par->ParSize - sizeof (SetLongPar)) / sizeof (LONG);
    DBWIN_ASSERT (c->IsConst (par->rval));
    LONG val = *((LONG FAR *) c->ReadlData (par->rval));
    c->WritelData (par->res,&val, sizeof(LONG), LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct IsValInNormPar {
  WORD ParSize;
  DWORD v[3];
  };
#pragma pack()

BOOL bIsValInNorm (mdiChild *c,void FAR *param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    IsValInNormPar FAR *par = (IsValInNormPar FAR *) param;
    LPDWORD data0 = LPDWORD (c->ReadlData (par->v[0]));
    LPDWORD data1 = LPDWORD (c->ReadlData (par->v[1]));
    LPDWORD data2 = LPDWORD (c->ReadlData (par->v[2]));
    if ((data0 != NULL) && (data1 != NULL) && (data2 != NULL))
      res = (fabs(double(*data0 - *data1)) <= double (*data2)) ;
    }
  if (mode & EM_FIXCONNECTION) {
    IsValInNormPar FAR *par = (IsValInNormPar FAR *) param;
    c->SetlConnection (par->v[0],GetLastOffset());
    c->SetlConnection (par->v[1],GetLastOffset());
    c->SetlConnection (par->v[2],GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    IsValInNormPar FAR *par = (IsValInNormPar FAR *) param;
    c->ClearlConnection (par->v[0],GetLastOffset());
    c->ClearlConnection (par->v[1],GetLastOffset());
    c->ClearlConnection (par->v[2],GetLastOffset());
    }
  return res;
  }

//   Lineare Interpolation in einem Punkt - Array
//      (bijektive Abbildung)
///////////////////////////////////////////////////////////
#pragma pack(1)
struct LinInterpol_param {
  WORD parSize;
  DWORD rRef;
  DWORD sRef;
  DWORD rpts[1];
  };
#pragma pack()

float Interpolate (float s,LinInterpol_param FAR *par,mdiChild *c)
  {
  float res;
  int count = (par->parSize - sizeof (*par)) / sizeof(DWORD) + 1 ;
  count /= 2 ;
  int i;

  fpt FAR *pts = (fpt FAR *) GetGlobMem (sizeof(fpt) * count) ;

  int j = 0;
  for (i = 0 ; i < count ; i++) {
    DBWIN_ASSERT (c->IsConst (par->rpts[j])) ;
    pts[i].x = *((float FAR *) c->ReadlData (par->rpts[j])) ;
    j++ ;
    DBWIN_ASSERT (c->IsConst (par->rpts[j])) ;
    pts[i].y = *((float FAR *) c->ReadlData (par->rpts[j])) ;
    j++ ;
    }
  for (i = -1 ; i < count ; i++) {
    if (i < 0) {
      if (s <= pts[0].x) break ;
      }
    else if (i < count - 1) {
      if ((s > pts[i].x) && (s <= pts[i+1].x)) break ;
      }
    else break ;
    }
  if (i < 0) res = pts[0].y ;
  else if (i < count - 1) {
    float dxg = pts[i+1].x - pts[i].x;
    if (dxg > 1.0E-5) {       // sollte doch wohl hoffentlich erfuellt sein
      float dyg = pts[i+1].y - pts[i].y;
      float dx  = s - pts[i].x ;
      res = pts[i].y + dyg * dx / dxg ;
      }
    else res = float(1.0E10);
    }
  else res = pts[count-1].y ;

  FreeGlobMem (pts);

  return res;
  }

BOOL uLinInterpol (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LinInterpol_param FAR *par = (LinInterpol_param FAR *) param;
    float FAR *s = (float FAR *) c->ReadlData (par->sRef);
    if (s != NULL) {
      float res = Interpolate (*s,par,c);
      c->WritelData (par->rRef,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->rRef,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    LinInterpol_param FAR *par = (LinInterpol_param FAR *) param;
    c->SetlConnection (par->sRef,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LinInterpol_param FAR *par = (LinInterpol_param FAR *) param;
    c->ClearlConnection (par->sRef,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ImageExistParam {
  WORD parSize;
  DWORD img;
  };
#pragma pack()

BOOL bImageExist (mdiChild *c,void FAR *param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ImageExistParam FAR *par = (ImageExistParam FAR *) param ;
    LPSTR FileName = LPSTR (c->ReadlData(par->img));
    if ((FileName != NULL) && (*FileName != '\0'))
      res = ImageExist(FileName);
    }
  if (mode & EM_FIXCONNECTION) {
    ImageExistParam FAR *par = (ImageExistParam FAR *) param ;
    c->SetlConnection(par->img,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ImageExistParam FAR *par = (ImageExistParam FAR *) param ;
    c->ClearlConnection(par->img,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct GetImageScalePar {
  WORD parSize;
  DWORD scRef;
  DWORD fcRef;
  DWORD ptRef;
  };
#pragma pack()

//
// Berechnung der Skalierungsmatrix so, dass die Daten mit dem Image
// uebereinstimmen !
/////////////////////////////////////////////////////////////////////////
BOOL uGetImgScale (mdiChild *c,void FAR *param,WORD mode)
  {
  GetImageScalePar FAR *par = (GetImageScalePar FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    float scf = float (1.0);
    if (par->parSize >= (sizeof(*par) - sizeof(DWORD))) {
      float FAR *fc = (float FAR *) c->ReadlData (par->fcRef);
      if (fc != NULL) scf = *fc;
      }
    tr2 m;
    // Das ergibt die einfachste Skalierungsmatrix, die man sich vorstellen
    // kann
    m.A[0][0] = float (1.0) / scf;
    m.A[1][1] = float (1.0) / scf;
    m.A[0][1] = 
    m.A[1][0] = float (0.0) ;
    m.B[0] = m.B[1] = float (0.0) ;

    if (par->parSize >= sizeof(*par)) {
      fpt FAR *pt = (fpt FAR *)c->ReadlData(par->ptRef);
      if ((pt != NULL) && (pt->x < 1.0E9)) {
        tr2 t;
        t.A[0][0] = float (1.0);
        t.A[1][1] = float (1.0);
        t.A[0][1] = 
        t.A[1][0] = float (0.0);
        t.B[0] = pt->x;
        t.B[1] = pt->y;
        Combine2d(&m, &m, &t);
        }
      }
    c->WritelData (par->scRef,&m,sizeof(m),LPSTR(par)-sizeof(WORD),
                    (((mode & EM_CHANGETOTRUE) != 0) || ((mode & EM_UPDATE) != 0)));
    }
  if ((mode & EM_FIXCONNECTION) && (par->parSize >= (sizeof(*par) - sizeof(DWORD)))) {
    c->SetlConnection (par->fcRef,LPSTR(par)-sizeof(WORD));
    if (par->parSize >= sizeof(*par))
      c->SetlConnection(par->ptRef,LPSTR(par)-sizeof(WORD));
    }
  if ((mode & (EM_CLEAR | EM_RESET)) && (par->parSize >= (sizeof(*par) - sizeof(DWORD)))) {
    c->ClearlConnection (par->fcRef,LPSTR(par)-sizeof(WORD));
    if (par->parSize >= sizeof(*par))
      c->ClearlConnection(par->ptRef,LPSTR(par)-sizeof(WORD));
    }

  return FALSE ;
  }

BOOL bDatExist (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    LPVOID dat = c->ReadlData (par->ref);
    res = (dat != NULL);
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    c->SetlConnection (par->ref,GetLastOffset ());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    c->ClearlConnection (par->ref,GetLastOffset ());
    }
  return res ;
  }

BOOL bStrExist (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    LPSTR dat = LPSTR (c->ReadlData (par->ref));
    res = ((dat != NULL) && (*dat)) ;
    }
  if (mode & EM_FIXCONNECTION) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    c->SetlConnection (par->ref,GetLastOffset ());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    EqualPar FAR *par = (EqualPar FAR *) param ;
    c->ClearlConnection (par->ref,GetLastOffset ());
    }
  return res ;
  }

#pragma pack(1)
struct DateNowPar {
  WORD ParSize;
  // Parameter
  DWORD ref;
  };
#pragma pack()

BOOL uDateNow (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DateNowPar FAR *par = (DateNowPar FAR *) param;
    INTTIME t = Now() ;
    packdate pdl;
    UnPackTime (t,&pdl);
    c->WritelData(par->ref,
                    &pdl,sizeof(pdl),LPSTR(param) - sizeof(WORD)
                );
    }
  return FALSE ;
  }

#pragma pack(1)
struct uTimeNow_param {
  WORD ParSize;
  // Parameter
  DWORD ref;
  };
#pragma pack()

BOOL uTimeNow (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uTimeNow_param FAR *par = (uTimeNow_param FAR *) param;
    packtime pt;
    UnPackSeconds (Now (), &pt);
    c->WritelData(par->ref,
                    &pt,sizeof(pt),LPSTR(param) - sizeof(WORD)
                );
    }
  return FALSE ;
  }


BOOL VTOSetEmptyCont (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPDWORD r = LPDWORD(LPSTR(param)+sizeof(WORD));
    fpt np;
    np.x = np.y = float(1.0E10);
    c->WritelData (r[0],&np,sizeof(np),
                  NULL,(mode & EM_CHANGETOTRUE) != 0);
    }
  return FALSE;
  }

// testen, ob ein bestimmter Datensatz eine Behandlungssimulation ist
// Datenelement loeschen
#pragma pack(1)
struct DelDataPar {
  WORD ParSize;
  // Parameter
  struct {
    WORD R;       // zu loeschende Datenelemente
    WORD I;
    } Ref[1];
  };
#pragma pack()

BOOL uDelData (mdiChild *c,void FAR *param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR Offset = LPSTR(param) - sizeof(WORD);
    DelDataPar FAR *par = (DelDataPar FAR *) param;
    int num_pars = (par->ParSize - sizeof(par->ParSize)) / sizeof(DWORD);
    for (int i = 0; i < num_pars; i++)
      c->DelData(par->Ref[i].R,par->Ref[i].I,Offset,(mode & EM_CHANGETOTRUE) != 0);
    }
  return FALSE;
  }

#pragma pack(1)
struct bFindInd_param {
  WORD parSize;
  WORD sRec,sId;
  DWORD rnum;
  };
#pragma pack()

static BOOL IsHexDigit (char h)
  {
  return (((h >= '0') && (h <= '9')) ||
          ((h >= 'A') && (h <= 'F')) ||
          ((h >= 'a') && (h <= 'f')));
  }

static int HexVal (char h)
  {
  int res = 0;
  if ((h >= '0') && (h <= '9'))       res = h - '0' ;
  else if ((h >= 'A') && (h <= 'F'))  res = h - 'A' + 10 ;
  else if ((h >= 'a') && (h <= 'f'))  res = h - 'a' + 10 ;
  return res;
  }

BOOL TestIndex (LPSTR str,WORD Index)
  {
  LPSTR h = str;
  BOOL res = FALSE;
  for ( ; ((*h) && (!res)) ; ) {
    if ((*h++ == '\\') && (*h ++ == 'i') && (*h ++ == ':')) {
      WORD x = 0 ;
      for ( ; IsHexDigit (*h) ; h ++) {
        x = x * 16 + HexVal (*h) ;
        }
      res = (x == Index) ;
      }
    }
  return res;
  }

BOOL bFindInd (mdiChild *c,void FAR *param,WORD mode)
  {
  bFindInd_param FAR *par = (bFindInd_param FAR *) param;
  LPSTR str = LPSTR (c->ReadData (par->sRec,par->sId));
  DBWIN_ASSERT (c->IsConst (par->rnum));
  DBINT num = *((DBINT FAR *) c->ReadlData (par->rnum));
  BOOL res = ((str != NULL) && (TestIndex (str,num)));

  if (mode & EM_FIXCONNECTION) {
    // Den Beginn der Condition in die Updateliste
    c->SetConnection (par->sRec,par->sId,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection (par->sRec,par->sId,GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct uSetMultiParam {
  WORD parSize;
  WORD srcR, srcI;
  struct {
    WORD R, I;
    } dstRef[1];            // Zielreferenzen
  };
#pragma pack()

BOOL uSetMulti (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  uSetMultiParam FAR *par = (uSetMultiParam FAR *) param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    int num_pars = (par->parSize - (sizeof(uSetMultiParam) - sizeof(DWORD))) / sizeof(par->dstRef[0]);
    LPVOID data = c->ReadData(par->srcR,par->srcI);
    if (data != NULL) {
      for (int i = 0 ; i < num_pars; i++)
        c->WriteData(par->dstRef[i].R,par->dstRef[i].I,data,GetBlockSize(data),Offset);
      }
    else {
      for (int i = 0 ; i < num_pars; i++)
        c->DelData(par->dstRef[i].R,par->dstRef[i].I,Offset);
      }
    }

  if (mode & EM_FIXCONNECTION)
    c->SetConnection(par->srcR,par->srcI,Offset);

  if (mode & (EM_CLEAR | EM_RESET))
    c->ClearConnection(par->srcR,par->srcI,Offset);

  return FALSE;
  }

#pragma pack(1)
struct BlockCopy_param {
  WORD parSize;
  WORD destR, destI;
  WORD srcR, srcI;
  DWORD count;
  };
#pragma pack()

BOOL BlockCopy (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  BlockCopy_param FAR *par = (BlockCopy_param FAR *) param;

  if (mode & EM_LOAD) {
    short count = c->ReadConstInt (par->count);
    for (short i = 0 ; i < count ; i++) {
      LPVOID data = c->ReadData(par->srcR,par->srcI + i);
      if (data != NULL)
        c->WriteData(par->destR,par->destI + i,data,GetBlockSize(data),Offset);
      else
        c->DelData(par->destR,par->destI + i,Offset);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    short count = c->ReadConstInt (par->count);
    for (short i = 0 ; i < count ; i++)
      c->ClearConnection(par->srcR,par->srcI + i,Offset);
    }

  return FALSE;
  }

#pragma pack(1)
struct uCopyRefsParam {
  WORD parSize;
  struct {
    WORD dstR, dstI;    // Zielreferenz
    WORD srcR, srcI;    // Quellreferenz
    } Ref[1];           // Paare von Referenzen
  };
#pragma pack()

BOOL uCopyRefs (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uCopyRefsParam FAR *par = (uCopyRefsParam FAR *) param;
    int num_pairs = (par->parSize - sizeof(WORD)) / sizeof(par->Ref[0]);
    for (int i = 0 ; i < num_pairs; i++) {
      LPVOID data = c->ReadData(par->Ref[i].srcR,par->Ref[i].srcI);
      if (data != NULL)
        c->WriteData(par->Ref[i].dstR,par->Ref[i].dstI,data,GetBlockSize(data),NULL,FALSE);
      else
        c->DelData(par->Ref[i].dstR,par->Ref[i].dstI,NULL,FALSE);
      }
    }
  return FALSE;
  }

////////////////////////////////////////////////////////////////////////////
//  Verbinden von Elementen, um eine Art 'Array' Zugriff zu bewerkstelligen
////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR LinkElements_param {
  WORD parSize;
  DWORD lRef;     // Ziel - Variable
  DWORD iRef;     // Index
  DWORD aRef[1];  // Array - Daten

  int AnzRefs()
    { return (parSize - sizeof(*this)) / sizeof(DWORD) + 1 ; }
  LPVOID Cmd ()
    { return (LPSTR(this) - sizeof(WORD)) ; }
  };
#pragma pack()

void SetlRef (mdiChild *c,LinkElements_param FAR *par,BOOL doUpdate)
  {
  // Schreiben von lRef
  DBINT FAR *ind = (DBINT FAR *) c->ReadData (LOWORD(par->iRef),HIWORD(par->iRef));
  DBWIN_ASSERT ((ind != NULL) && (*ind >= 0) && (*ind < par->AnzRefs()));
  LPVOID Data = c->ReadData (LOWORD(par->aRef[*ind]),HIWORD(par->aRef[*ind]));
  if (Data != NULL)
    c->WriteData (LOWORD(par->lRef),HIWORD(par->lRef),
                      Data,GetBlockSize(Data),par->Cmd(),
                      doUpdate
                 );
  else
    c->DelData (LOWORD(par->lRef),HIWORD(par->lRef),
                      par->Cmd(),
                      doUpdate
                 );
  }

void SetaRef (mdiChild *c,LinkElements_param FAR *par,BOOL doUpdate)
  {
  // Schreiben von aRef
  DBINT FAR *ind = (DBINT FAR *) c->ReadData (LOWORD(par->iRef),HIWORD(par->iRef));
  DBWIN_ASSERT ((ind != NULL) && (*ind >= 0) && (*ind < par->AnzRefs()));
  LPVOID Data = c->ReadData (LOWORD(par->lRef),HIWORD(par->lRef));
  if (Data != NULL)
    c->WritelData (par->aRef[*ind],
                      Data,GetBlockSize(Data),par->Cmd(),
                      doUpdate
                 );
  else
    c->DellData (par->aRef[*ind],
                      par->Cmd(),
                      doUpdate
               );
  }

BOOL LinkElements (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetlRef (c,(LinkElements_param FAR *) param,(mode & EM_CHANGETOTRUE) != 0);
    }
  if (mode & EM_UPDATE) {
    LinkElements_param FAR *par = (LinkElements_param FAR *) param;
    switch (UpdateEleCount()) {
      case 0 :
        // ganz normalen Load (Update von ChangeConnection...)
        SetlRef (c,par,TRUE);
        break ;
      default :
        // der eigentlich interessante Fall
        {
        BOOL IsUpdatefromZiel = c->IsUpdatelFromEle(par->lRef);
        BOOL IsUpdatefromSource = FALSE ;
        for (int i = 0 ; i < par->AnzRefs() ; i++)
          IsUpdatefromSource = IsUpdatefromSource ||
                    c->IsUpdatelFromEle(par->aRef[i]);
        if ((IsUpdatefromZiel) && (!IsUpdatefromSource))
          // Zurueckkopieren der Zielvariable
          SetaRef (c,par,TRUE);
        else if ((!IsUpdatefromZiel) && (IsUpdatefromSource))
          // Setzen der Zielvariable
          SetlRef (c,par,TRUE);
        else {
          // darf eigentlich nicht vorkommen, aber wenns schon unbendingt
          // sei soll...
          SetlRef (c,par,TRUE);
          }
        }
        break ;
      }
    }
  if (mode & EM_FIXCONNECTION) {
    LinkElements_param FAR *par = (LinkElements_param FAR *) param;
    c->SetlConnection (par->lRef,par->Cmd());
    c->SetlConnection (par->iRef,par->Cmd());
    for (int i = 0 ; i < par->AnzRefs() ; i++) {
      c->SetlConnection (par->aRef[i],par->Cmd());
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LinkElements_param FAR *par = (LinkElements_param FAR *) param;
    c->ClearlConnection (par->lRef,par->Cmd());
    c->ClearlConnection (par->iRef,par->Cmd());
    for (int i = 0 ; i < par->AnzRefs() ; i++) {
      c->ClearlConnection (par->aRef[i],par->Cmd());
      }
    }
  return FALSE ;
  }

BOOL SetIndElement (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetaRef (c,(LinkElements_param FAR *) param,(mode & EM_CHANGETOTRUE) != 0);
    }
  if (mode & EM_FIXCONNECTION) {
    LinkElements_param FAR *par = (LinkElements_param FAR *) param;
    c->SetlConnection (par->lRef,par->Cmd());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LinkElements_param FAR *par = (LinkElements_param FAR *) param;
    c->ClearlConnection (par->lRef,par->Cmd());
    c->ClearlConnection (par->iRef,par->Cmd());
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetIndIndex_param {
  WORD parSize;   
  DWORD iRef;     // Index der Referenz, die gesetzt werden soll
  DWORD rNmbra;     // Wert des Elementes, das nicht dem Index entspricht
  DWORD rNmbrb;     // Wert des Elementes, das dem Index entrspricht
  DWORD iNmbr[1];  // Elemente der Reihe nach

  int AnzRefs()
    { return (parSize - sizeof(*this)) / sizeof(DWORD) + 1 ; }
  LPVOID Cmd ()
    { return (LPSTR(this) - sizeof(WORD)) ; }
  };
#pragma pack()

void CheckVal (mdiChild *c,DWORD Ref,int val,WORD doUpdate,LPVOID Cmd)
  {
  DBINT FAR *old = (DBINT FAR *) c->ReadData (LOWORD(Ref),HIWORD(Ref));
  if ((old == NULL) || (*old != val))
    c->WriteData (LOWORD(Ref),HIWORD(Ref),&val,sizeof(val),
                    Cmd,doUpdate
               );
  }
  
void CheckVals (mdiChild *c,SetIndIndex_param FAR *par,WORD doUpdate)
  {
  DBINT FAR *index = (DBINT FAR *) 
        c->ReadData (LOWORD(par->iRef),HIWORD(par->iRef));
  DBWIN_ASSERT(index != NULL);
  DBWIN_ASSERT(c->IsConst (par->rNmbrb));
  DBINT Nmbrb = *((DBINT FAR *) c->ReadlData (par->rNmbrb));
  DBWIN_ASSERT(c->IsConst (par->rNmbra));
  DBINT Nmbra = *((DBINT FAR *) c->ReadlData (par->rNmbra));
  for (int i = 0 ; i < par->AnzRefs() ; i++)
    CheckVal (c,par->iNmbr[i],
                (*index == i) ? Nmbrb : Nmbra,
                doUpdate,
                par->Cmd()
             );
  }

BOOL SetIndIndex (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    CheckVals (c,(SetIndIndex_param FAR *) param,(mode & EM_CHANGETOTRUE) != 0);
  if (mode & EM_UPDATE)
    CheckVals (c,(SetIndIndex_param FAR *) param,TRUE);
  if (mode & EM_FIXCONNECTION) {
    SetIndIndex_param FAR *par = (SetIndIndex_param FAR *) param;
    c->SetConnection(LOWORD(par->iRef),HIWORD(par->iRef),par->Cmd());
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetIndIndex_param FAR *par = (SetIndIndex_param FAR *) param;
    c->ClearConnection(LOWORD(par->iRef),HIWORD(par->iRef),par->Cmd());
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetCreationData_param {
  WORD parSize;
  DWORD rCode;
  DWORD Ref;
  };
#pragma pack()

BOOL GetCreationData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetCreationData_param FAR *par = (GetCreationData_param FAR *) param;
    int size;
    DBWIN_ASSERT (c->IsConst (par->rCode));
    DBINT Code = *((DBINT FAR *) c->ReadlData (par->rCode));
    LPVOID Data = c->GetDocumentExtraData (Code,&size);
    BOOL res;
    if (Data != NULL) {
      c->WritelData (par->Ref,Data,size,LPSTR(param) - sizeof(WORD),FALSE);
      res = TRUE ;
      }
    else
      res = FALSE ;
    return res;
    }
  else
    return FALSE ;
  }

#pragma pack(1)
struct DataEqualParam {
  WORD parSize;
  WORD d1R, d1I;
  WORD d2R, d2I;
  };
#pragma pack()

BOOL bDataEqual (mdiChild *c,void FAR *param,WORD mode)
  {
  DataEqualParam FAR *par = (DataEqualParam FAR *) param ;
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPVOID d1 = c->ReadData(par->d1R, par->d1I);
    LPVOID d2 = c->ReadData(par->d2R, par->d2I);
    if ((d1 != NULL) && (d2 != NULL)) {
      int size = GetBlockSize(d1);
      if (size == (int)GetBlockSize(d2))
        res = lmemcmp(d1, d2, size);
      }
    else if ((d1 == NULL) && (d2 == NULL))
      res = TRUE ;
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->d1R, par->d1I, GetLastOffset());
    c->SetConnection(par->d2R, par->d2I, GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->d1R, par->d1I, GetLastOffset());
    c->ClearConnection(par->d2R, par->d2I, GetLastOffset());
    }
  return res;
  }

#pragma pack(1)
struct uSetDate_param {
  WORD parSize;
  DWORD dRef;
  DWORD rday,rmonth,ryear;
  };
#pragma pack()

BOOL IniDate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uSetDate_param FAR *par = (uSetDate_param FAR *) param;
    DBINT FAR *day = (DBINT FAR *)(c->ReadlData (par->rday));
    DBINT FAR *month = (DBINT FAR *)(c->ReadlData (par->rmonth));
    DBINT FAR *year = (DBINT FAR *)(c->ReadlData (par->ryear));
    if ((day != NULL) && (month != NULL) && (*year != NULL)) {
      packdate pd;
      pd.day = unsigned (*day);
      pd.month = unsigned (*month);
      pd.year = *year;
      c->WritelData (par->dRef,&pd,sizeof(pd),LPSTR(param) - sizeof(WORD));
      }
    else
      c->DellData (par->dRef,LPSTR(param) - sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    uSetDate_param FAR *par = (uSetDate_param FAR *) param;
    c->SetlConnection (par->rday,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->rmonth,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->ryear,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uSetDate_param FAR *par = (uSetDate_param FAR *) param;
    c->ClearlConnection (par->rday,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rmonth,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ryear,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL uSetDate (mdiChild *c,LPVOID param,WORD mode)
  {
  return IniDate (c,param,mode);
  }

BOOL ToBusy (mdiChild *c,LPVOID param,WORD mode)
  {
  ToBusyCursor();   // Sanduhr vom Script aus einschalten

  return FALSE ;
  }

#define BUSY_ON   1
#define BUSY_OFF  2
#pragma pack(1)
struct DenyNormalCursor_param {
  WORD parSize;
  DWORD mode;
  };
#pragma pack()
extern BOOL DNormalCusor;
BOOL DenyNormalCursor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DenyNormalCursor_param FAR *par = (DenyNormalCursor_param FAR *) param;
    DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->mode);
    if (lpmode != NULL) {
      if (*lpmode == BUSY_ON) {
        ToBusyCursor ();
        DNormalCusor = TRUE ;
        }
      else {
        RestoreCursor ();
        DNormalCusor = FALSE ;
        }
      }
    }
  if (mode & EM_RESET) {
    DenyNormalCursor_param FAR *par = (DenyNormalCursor_param FAR *) param;
    c->ClearlConnection (par->mode,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetMidPts_param {
  WORD parSize;
  DWORD r1,r2;      // Resultat der Berechnung (r1 ... A1o, r2 ... A1u)
  DWORD pg1,pg2;    // Gameneben (PNS,ANS)
  DWORD pm1,pm2;    // Mandibularebene (Gonion,Menton)
  DWORD pl11,pl12;  // Ebene des oberen Scheidezahnes
  DWORD pl21,pl22;  // Ebene des unteren Schneidezahnes
  DWORD dy;         // vert. Abstand der Schneidezahnspizen
  DWORD c;          // Verhaeltnis Oberkieferhoehe zu Unterkieferhoehe
  };
#pragma pack()

BOOL GetMidPts (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetMidPts_param FAR *par = (GetMidPts_param FAR *) param;
    fpt r1,r2;
    GetMidPts (LPFPT (c->ReadlData (par->pg1)),
               LPFPT (c->ReadlData (par->pg2)),
               LPFPT (c->ReadlData (par->pm1)),
               LPFPT (c->ReadlData (par->pm2)),
               LPFPT (c->ReadlData (par->pl11)),
               LPFPT (c->ReadlData (par->pl12)),
               LPFPT (c->ReadlData (par->pl21)),
               LPFPT (c->ReadlData (par->pl22)),
               LPFLOAT (c->ReadlData (par->dy)),
               LPFLOAT (c->ReadlData (par->c)),
               &r1,&r2
              );
    if (r1.x < 1.0E9) {
      c->WritelData (par->r1,&r1,sizeof(r1),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->r2,&r2,sizeof(r2),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->r1,LPSTR(param)-sizeof(WORD));
      c->DellData (par->r2,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    GetMidPts_param FAR *par = (GetMidPts_param FAR *) param;
    c->SetlConnection (par->pg1,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pg2,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pm1,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pm2,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pl11,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pl12,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pl21,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->pl22,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->dy,LPSTR(param) - sizeof(WORD));
    c->SetlConnection (par->c,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetMidPts_param FAR *par = (GetMidPts_param FAR *) param;
    c->ClearlConnection (par->pg1,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pg2,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pm1,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pm2,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pl11,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pl12,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pl21,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->pl22,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->dy,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->c,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

void CleanVGrid (uGetVGrid_param FAR * par)
  {
  if (par->pts != NULL)
    FreeGlobMem (par->pts) ;
  par->pts = NULL ;
  if (par->lpdone != NULL)
    FreeGlobMem (par->lpdone) ;
  par->lpdone = NULL ;
  if (par->vects != NULL)
    FreeGlobMem (par->vects) ;
  par->vects = NULL ;
  if (par->v != NULL)
    delete par->v;
  par->v = NULL ;
  par->anz = NULL;
  par->rrec = NULL;
  }

BOOL uGetVGrid (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uGetVGrid_param FAR *par = (uGetVGrid_param FAR *) param;
    CleanVGrid (par);
    par->pts = (fpt FAR *) (GetGlobMem (par->AnzPts() * sizeof(fpt)));
    par->lpdone = (BOOL FAR *) (GetGlobMem (par->AnzPts() * sizeof(BOOL)));
    for (int i = 0 ; i < par->AnzPts() ; i++) {
      LPFPT lppt = LPFPT (c->ReadlData (par->pt[i]));
      if (lppt != NULL) {
        par->lpdone[i] = TRUE ;
        par->pts[par->anz++] = *lppt;
        }
      else
        par->lpdone[i] = FALSE ;
      }
    par->v = new Voronoi (par->pts,par->anz);
    par->v->Analyse ();
    par->v->RemoveAnalyseMem ();
    c->WritelData (par->res,&par,sizeof(par),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    uGetVGrid_param FAR *par = (uGetVGrid_param FAR *) param;
    for (int i = 0 ; i < par->AnzPts () ; i++) {
      c->ClearlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uGetVGrid_param FAR *par = (uGetVGrid_param FAR *) param;
    CleanVGrid (par);
    for (int i = 0 ; i < par->AnzPts () ; i++) {
      c->ClearlConnection (par->pt[i],LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct InitializeData_param {
  WORD parSize;
  DWORD res;
  DWORD rsize;
  };
#pragma pack()

BOOL InitializeData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    InitializeData_param FAR *par = (InitializeData_param FAR *) param;
    char buffer[256];
    DBWIN_ASSERT (c->IsConst (par->rsize));
    DBINT size = *((DBINT FAR *) c->ReadlData (par->rsize));
    DBWIN_ASSERT (size < sizeof(buffer));
    lmemset (buffer,'\0',size);
    c->WritelData (par->res,buffer,size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetNewPts_par {
  WORD parSize;
  DWORD vobj;
  DWORD vnrec;
  DWORD ptnRef[1];
  int AnzPts () { return (parSize - sizeof (*this)) / sizeof(DWORD) + 1 ; }
  };
#pragma pack()

typedef uGetVGrid_param FAR *LPVGPAR;
BOOL SetNewPts    (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetNewPts_par FAR *par = (SetNewPts_par FAR *) param;
    LPVGPAR FAR *vp = (LPVGPAR FAR *) c->ReadlData (par->vobj);
    DBWIN_ASSERT ((vp != NULL) && (*vp != NULL) && ((*vp)->AnzPts() == par->AnzPts()));
    int j = 0 ;
    (*vp)->vects = (fpt FAR *) GetGlobMem ((*vp)->anz * sizeof(fpt));
    for (int i = 0 ; i < par->AnzPts () ; i++) {
      if ((*vp)->lpdone[i]) {
        fpt FAR *np = (fpt FAR *) c->ReadlData (par->ptnRef[i]);
        DBWIN_ASSERT (np != NULL);
        (*vp)->vects[j].x = np->x - (*vp)->pts[j].x ;
        (*vp)->vects[j].y = np->y - (*vp)->pts[j].y ;
        j ++ ;
        }
      }
    (*vp)->v->SetVects ((*vp)->vects,(*vp)->anz);
    (*vp)->v->PrepareTriangs ();
    LPDBRECORD FAR *lpres = (LPDBRECORD FAR *) c->ReadlData (par->vnrec);
    DBWIN_ASSERT (lpres != NULL);
    (*vp)->rrec = *lpres;
    }
  if (mode & EM_FIXCONNECTION) {
    SetNewPts_par FAR *par = (SetNewPts_par FAR *) param;
    c->SetlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPts () ; i++) {
      c->SetlConnection (par->ptnRef[i],LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetNewPts_par FAR *par = (SetNewPts_par FAR *) param;
    c->ClearlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzPts () ; i++) {
      c->ClearlConnection (par->ptnRef[i],LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR GrowPt_param {
  WORD parSize;
  DWORD vobj;
  DWORD ref[1];
  int AnzRef()
    { return (parSize - sizeof(*this)) / sizeof(DWORD) + 1 ; }
  };
#pragma pack()

BOOL GrowPt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    LPVGPAR FAR *vp = (LPVGPAR FAR *) c->ReadlData (par->vobj);
    for (int i = 0 ; i < par->AnzRef () ; i++) {
      fpt FAR *po = (fpt FAR *) c->ReadlData (par->ref[i]);
      if (po != NULL) {
        fpt n;
        (*vp)->v->Interpolate (po,&n);
        n.x += po->x ;
        n.y += po->y ;
        (*vp)->rrec->Set (HIWORD(par->ref[i]),&n,sizeof(n),LPSTR(param)-sizeof(WORD),TRUE);
        }
      else
        (*vp)->rrec->Del (HIWORD(par->ref[i]),LPSTR(param)-sizeof(WORD),TRUE);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    c->SetlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzRef () ; i++)
      c->SetlConnection (par->ref[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    c->ClearlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzRef () ; i++)
      c->ClearlConnection (par->ref[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GrowCnt      (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    LPVGPAR FAR *vp = (LPVGPAR FAR *) c->ReadlData (par->vobj);
    for (int i = 0 ; i < par->AnzRef () ; i++) {
      fpt FAR *po = (fpt FAR *) c->ReadlData (par->ref[i]);
      if (po != NULL) {
        fpt FAR *npt = (fpt FAR *) GetGlobMem (GetBlockSize(po));
        lmemcpy (npt,po,GetBlockSize (po));
        int anzpnt;
        fpt FAR *o = get_cont (po,&anzpnt);
        fpt FAR *n = get_cont (npt,&anzpnt);
        int hdsize = LPSTR(o) - LPSTR(po);
        anzpnt = (GetBlockSize(po) - hdsize) / sizeof(fpt) ;
        for (int j = 0 ; j < anzpnt ; j++) {
          (*vp)->v->Interpolate (&o[j],&n[j]);
          n[j].x += o[j].x ;
          n[j].y += o[j].y ;
          }
        (*vp)->rrec->Set (HIWORD(par->ref[i]),npt,GetBlockSize(npt),LPSTR(param)-sizeof(WORD),TRUE);
        FreeGlobMem (npt);
        }
      else
        (*vp)->rrec->Del (HIWORD(par->ref[i]),LPSTR(param)-sizeof(WORD),TRUE);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    c->SetlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzRef () ; i++)
      c->SetlConnection (par->ref[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GrowPt_param FAR *par = (GrowPt_param FAR *) param;
    c->ClearlConnection (par->vobj,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzRef () ; i++)
      c->ClearlConnection (par->ref[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct CombineData_param {
  WORD parSize;
  DWORD res;
  DWORD d1,d2;
  };
#pragma pack()

BOOL CombineData  (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CombineData_param FAR *par = (CombineData_param FAR *) param;
    LPVOID d1 = c->ReadlData (par->d1);
    LPVOID d2 = c->ReadlData (par->d2);
    if ((d1 != NULL) && (d2 != NULL)) {
      LPSTR r = LPSTR (GetGlobMem (GetBlockSize (d1) + GetBlockSize (d2)));
      lmemcpy (r,d1,GetBlockSize (d1));
      lmemcpy (r+GetBlockSize(d1),d2,GetBlockSize(d2));
      c->WritelData (par->res,r,GetBlockSize(r),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (r);
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CombineData_param FAR *par = (CombineData_param FAR *) param;
    c->ClearlConnection (par->d1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->d2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct uExtractData_param {
  WORD parSize;
  DWORD res;
  DWORD source;
  DWORD rbeg;
  DWORD rend;
  };
#pragma pack()

BOOL ExtractData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    uExtractData_param FAR *par = (uExtractData_param FAR *) param;
    LPSTR source = LPSTR (c->ReadlData (par->source));
    int beg = -1, end = -1;
    DBINT FAR *lpbeg = (DBINT FAR *) c->ReadlData (par->rbeg);
    if (lpbeg != NULL)
      beg = *lpbeg;
    DBINT FAR *lpend = (DBINT FAR *) c->ReadlData (par->rend);
    if (lpend != NULL)
      end = *lpend;
    else
      end = -1;
    if (end < 0)
      end = int((source != NULL) ? (GetBlockSize (source) - 1) : 0) ;
    if ((beg >= 0) && (end >= 0) && (beg <= end) &&
        (source != NULL) && (int(GetBlockSize(source)) > end))
      c->WritelData (par->res,source + beg,
                int (end - beg + 1),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    uExtractData_param FAR *par = (uExtractData_param FAR *) param;
    c->SetlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->rbeg,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->rend,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uExtractData_param FAR *par = (uExtractData_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rbeg,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rend,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetTwainSources_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetTwainSources (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR txt = LPSTR (GetGlobMem (1024));
    GetTwainSources_param FAR *par = (GetTwainSources_param FAR *) param ;
    GetTWAINSources (txt);
    for ( int i = 0 ; ((txt[i]) || (txt[i+1])) ; i++) ;
    c->WritelData (par->res,txt,i + 2,LPSTR(param)-sizeof(WORD));
    FreeGlobMem (txt);
    }
  return FALSE ;
  }

#pragma pack(1)
struct mShowMessageBox_par {
  WORD parSize;
  WORD MsgR, MsgI;
  };
#pragma pack()

BOOL mShowMessageBox (mdiChild *c,void FAR *par,WORD mode)
  {
  if (mode & EM_LOAD) {
    mShowMessageBox_par FAR *p = (mShowMessageBox_par FAR *) par;
    LPSTR Msg = (LPSTR) c->ReadData (p->MsgR, p->MsgI);
    if (Msg != NULL) {
      DBWIN_ASSERT_TEXT (FALSE,Msg);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    mShowMessageBox_par FAR *p = (mShowMessageBox_par FAR *) par;
    c->ClearConnection (p->MsgR,p->MsgI,LPSTR(par)-sizeof(WORD));
    }
  return FALSE ;
  }

DLLExport DWORD _export SetSema (LPSTR Name,WORD FAR *Count);
DLLExport void _export WINAPI ClearSema (DWORD Handle);
DLLExport BOOL _export TestSema (LPSTR Name);

#pragma pack(1)
struct GetConnNmbr_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

extern DLLExport int _export WINAPI GetConnectionNmbr ();
BOOL GetConnNmbr (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    int Nmbr = GetConnectionNmbr ();
    GetConnNmbr_param FAR *par = (GetConnNmbr_param FAR *) param;
    c->WritelData (par->res,&Nmbr,sizeof(Nmbr),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetSemaphore_param {
  WORD parSize;
  DWORD Handle;
  DWORD name;
  };
#pragma pack()

BOOL SetSemaphore (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res ;
  if (mode & EM_LOAD) {
    SetSemaphore_param FAR *par = (SetSemaphore_param FAR *) param;
    LPSTR Name = LPSTR(c->ReadlData (par->name));
    DBWIN_ASSERT (Name != NULL);
    WORD Count;
    DWORD Handle = SetSema (Name,&Count);
    if (Handle != 0L) {
      c->WritelData (par->Handle,&Handle,sizeof(Handle),LPSTR(param)-sizeof(WORD));
      res = TRUE;
      }
    else {
      c->WritelData (par->Handle,&Handle,sizeof(Handle),LPSTR(param)-sizeof(WORD));
      res = FALSE;
      }
    }
  else
    res = FALSE ;
  return res ;
  }

#pragma pack(1)
struct ClearSemaphore_param {
  WORD parSize;
  DWORD Handle;
  };
#pragma pack()

BOOL ClearSemaphore (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ClearSemaphore_param FAR *par = (ClearSemaphore_param FAR *) param;
    DWORD FAR *Handle = (DWORD FAR *) c->ReadlData (par->Handle);
    if (Handle != NULL)
      ClearSema (*Handle);
    }
  return FALSE ;
  }

#pragma pack(1)
struct TestSemaphore_param {
  WORD mode ;
  DWORD name;
  };
#pragma pack()

BOOL TestSemaphore (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & EM_LOAD) {
    TestSemaphore_param FAR *par = (TestSemaphore_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->name));
    DBWIN_ASSERT (Name != NULL);
    res = TestSema (Name);
    }
  return res;
  }

/*-----------< Allgemeine Vergleichsfunktion >----------*/
#pragma pack(1)
struct doCmp_param {
  WORD parSize;
  DWORD v1;
  DWORD v2;
  LONG cmpCode;
  };
#pragma pack()

#define CMPCODE_EQUAL         0
#define CMPCODE_LESS          1
#define CMPCODE_LESSEQUAL     2
#define CMPCODE_GREATER       3
#define CMPCODE_GREATEREQUAL  4
#define CMPCODE_NOTEQUAL      5

class doCmpBase {
 public :
  BOOL DoIt (mdiChild *c,LPVOID param,WORD mode);

  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return FALSE ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return FALSE ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return FALSE ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return FALSE ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return FALSE ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return FALSE ; }
  };
class doCmpShort : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) == *((short int FAR *) v2)) ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) < *((short int FAR *) v2)) ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) <= *((short int FAR *) v2)) ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) > *((short int FAR *) v2)) ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) >= *((short int FAR *) v2)) ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return (*((short int FAR *) v1) != *((short int FAR *) v2)) ; }
  };
class doCmpLong : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) == *((LONG FAR *) v2)) ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) < *((LONG FAR *) v2)) ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) <= *((LONG FAR *) v2)) ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) > *((LONG FAR *) v2)) ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) >= *((LONG FAR *) v2)) ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return (*((LONG FAR *) v1) != *((LONG FAR *) v2)) ; }
  };
class doCmpFloat : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) == *((float FAR *) v2)) ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) < *((float FAR *) v2)) ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) <= *((float FAR *) v2)) ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) > *((float FAR *) v2)) ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) >= *((float FAR *) v2)) ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return (*((float FAR *) v1) != *((float FAR *) v2)) ; }
  };
class doCmpQLong : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) == *((long double FAR *) v2)) ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) < *((long double FAR *) v2)) ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) <= *((long double FAR *) v2)) ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) > *((long double FAR *) v2)) ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) >= *((long double FAR *) v2)) ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return (*((long double FAR *) v1) != *((long double FAR *) v2)) ; }
  };
class doCmpString : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) == 0 ; }
  virtual BOOL Less (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) < 0 ; }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) <= 0 ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) > 0 ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) >= 0 ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return lstrcmp (LPSTR(v1),LPSTR(v2)) != 0 ; }
  };
class doCmpDate : public doCmpBase {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) 
    { 
    packdate FAR *p1 = (packdate FAR *) v1 ;  packdate FAR *p2 = (packdate FAR *) v2 ;
    return ((p1->year == p2->year) && (p1->month == p2->month) && (p1->day == p2->day)) ;
    }
  virtual BOOL Less (LPVOID v1,LPVOID v2) 
    { 
    packdate FAR *p1 = (packdate FAR *) v1 ;  packdate FAR *p2 = (packdate FAR *) v2 ;
    return ((p1->year < p2->year) || 
            (((p1->year == p2->year) && (p1->month < p2->month)) ||
             ((p1->year == p2->year) && (p1->month == p2->month) && (p1->day < p2->day))
            )
           );
    }
  virtual BOOL LessEqual (LPVOID v1,LPVOID v2) { return ((Equal (v1,v2)) || (Less (v1,v2))) ; }
  virtual BOOL Greater (LPVOID v1,LPVOID v2) { return ((!Equal (v1,v2)) && (!Less (v1,v2))) ; }
  virtual BOOL GreaterEqual (LPVOID v1,LPVOID v2) { return !Less (v1,v2) ; }
  virtual BOOL NotEqual (LPVOID v1,LPVOID v2) { return !Equal (v1,v2) ; }
  };
class doCmpTime : public doCmpDate {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) 
    { 
    packtime FAR *p1 = (packtime FAR *) v1 ;  packtime FAR *p2 = (packtime FAR *) v2 ;
    return ((p1->hour == p2->hour) && (p1->minute == p2->minute) && (p1->second == p2->second)) ;
    }
  virtual BOOL Less (LPVOID v1,LPVOID v2) 
    { 
    packtime FAR *p1 = (packtime FAR *) v1 ;  packtime FAR *p2 = (packtime FAR *) v2 ;
    return ((p1->hour < p2->hour) || 
            (((p1->hour == p2->hour) && (p1->minute < p2->minute)) ||
             ((p1->hour == p2->hour) && (p1->minute == p2->minute) && (p1->second < p2->second))
            )
           );
    }
  };

class doCmpDateTime : public doCmpDate {
  virtual BOOL Equal (LPVOID v1,LPVOID v2) 
    { 
    packdatetime FAR *p1 = (packdatetime FAR *) v1 ;  packdatetime FAR *p2 = (packdatetime FAR *) v2 ;
    return ((p1->pd.year == p2->pd.year) && (p1->pd.month == p2->pd.month) && (p1->pd.day == p2->pd.day) &&
            (p1->pt.hour == p2->pt.hour) && (p1->pt.minute == p2->pt.minute) && (p1->pt.second == p2->pt.second)) ;
    }
  virtual BOOL Less (LPVOID v1,LPVOID v2) 
    { 
    packdatetime FAR *p1 = (packdatetime FAR *) v1 ;  packdatetime FAR *p2 = (packdatetime FAR *) v2 ;
    return ((p1->pd.year < p2->pd.year) || 
            ((p1->pd.year == p2->pd.year) && (p1->pd.month < p2->pd.month)) ||
            ((p1->pd.year == p2->pd.year) && (p1->pd.month == p2->pd.month) && (p1->pd.day < p2->pd.day)) ||
            ((p1->pd.year == p2->pd.year) && (p1->pd.month == p2->pd.month) && (p1->pd.day == p2->pd.day) && (p1->pt.hour < p2->pt.hour)) ||
            ((p1->pd.year == p2->pd.year) && (p1->pd.month == p2->pd.month) && (p1->pd.day == p2->pd.day) && (p1->pt.hour == p2->pt.hour) && (p1->pt.minute < p2->pt.minute)) ||
            ((p1->pd.year == p2->pd.year) && (p1->pd.month == p2->pd.month) && (p1->pd.day == p2->pd.day) && (p1->pt.hour == p2->pt.hour) && (p1->pt.minute == p2->pt.minute) && (p1->pt.second < p2->pt.second))
           );
    }
  };

BOOL doCmpBase::DoIt (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    doCmp_param FAR *par = (doCmp_param FAR *) param;
    LPVOID v1 = c->ReadlData (par->v1);
    LPVOID v2 = c->ReadlData (par->v2);
    short cmpCode = c->ReadConstInt (par->cmpCode);
    if ((v1 != NULL) && (v2 != NULL)) {
      switch (cmpCode) {
        case CMPCODE_EQUAL         :
          res = Equal (v1,v2);
          break ;
        case CMPCODE_LESS          :
          res = Less (v1,v2);
          break ;
        case CMPCODE_LESSEQUAL     :
          res = LessEqual (v1,v2);
          break ;
        case CMPCODE_GREATER       :
          res = Greater (v1,v2);
          break ;
        case CMPCODE_GREATEREQUAL  :
          res = GreaterEqual (v1,v2);
          break ;
        case CMPCODE_NOTEQUAL      :
          res = NotEqual (v1,v2);
          break ;
        default :
          DBWIN_ASSERT (FALSE);
        }
      }
    else if ((v1 == NULL) && (v2 == NULL) && (cmpCode == CMPCODE_EQUAL))
      res = TRUE ;
    else if ((((v1 == NULL) && (v2 != NULL)) || ((v1 != NULL) && (v2 == NULL))) && (cmpCode == CMPCODE_NOTEQUAL))
      res = TRUE ;
    }
  if (mode & EM_FIXCONNECTION) {
    doCmp_param FAR *par = (doCmp_param FAR *) param;
    c->SetlConnection (par->v1,GetLastOffset());
    c->SetlConnection (par->v2,GetLastOffset());
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    doCmp_param FAR *par = (doCmp_param FAR *) param;
    c->ClearlConnection (par->v1,GetLastOffset());
    c->ClearlConnection (par->v2,GetLastOffset());
    }
  return res;
  }

BOOL bCmpShort (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpShort s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpLong (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpLong s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpFloat (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpFloat s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpQLong (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpQLong s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpString (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpString s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpDate (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpDate s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpTime (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpTime s;
  return s.DoIt (c,param,mode);
  }

BOOL bCmpDateTime (mdiChild *c,LPVOID param,WORD mode)
  {
  doCmpDateTime s;
  return s.DoIt (c,param,mode);
  }

#pragma pack(1)
struct ConvertStruct {
  WORD parSize;
  DWORD dest;
  DWORD source;
  };
#pragma pack()
class ConvertBase {
 public :
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    }
  BOOL doIt(mdiChild *c,LPVOID param,WORD mode)
    {
    if (mode & (EM_LOAD | EM_UPDATE)) {
      char buffer[256];
      int bsize;
      LPVOID source = c->ReadlData (((ConvertStruct FAR *) param)->source);
      if (source != NULL) {
        ConvertIt (buffer,&bsize,source);
        c->WritelData (((ConvertStruct FAR *) param)->dest,
                        buffer,bsize,LPSTR(param)-sizeof(WORD));
        }
      else {
        c->DellData (((ConvertStruct FAR *) param)->dest,
                      LPSTR(param)-sizeof(WORD));
        }
      }
    if (mode & EM_FIXCONNECTION) {
      c->SetlConnection (((ConvertStruct FAR *) param)->source,LPSTR(param)-sizeof(WORD));
      }
    if (mode & (EM_CLEAR | EM_RESET))  {
      c->ClearlConnection (((ConvertStruct FAR *) param)->source,LPSTR(param)-sizeof(WORD));
      }
    return FALSE ;
    }
  };
class ConvertLongToFloat : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((float FAR *) buffer) = float (*((LONG FAR *) source));
    *bsize = sizeof(float);
    }
  };
class ConvertShortToFloat : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((float FAR *) buffer) = float (*((short FAR *) source));
    *bsize = sizeof(float);
    }
  };
class ConvertFloatToLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((LONG FAR *) buffer) = LONG (*((float FAR *) source));
    *bsize = sizeof(LONG);
    }
  };
class ConvertFloatToShort : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((short FAR *) buffer) = short (*((float FAR *) source));
    *bsize = sizeof(short);
    }
  };
class ConvertLongToShort : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((short FAR *) buffer) = short (*((LONG FAR *) source));
    *bsize = sizeof(short);
    }
  };
class ConvertShortToLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((LONG FAR *) buffer) = short (*((short FAR *) source));
    *bsize = sizeof(LONG);
    }
  };
class ConvertShortToQLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((long double FAR *) buffer) = (long double) (*((short FAR *) source));
    *bsize = sizeof(long double);
    }
  };
class ConvertFloatToQLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((long double FAR *) buffer) = (long double) (*((float FAR *) source));
    *bsize = sizeof(long double);
    }
  };
class ConvertLongToQLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((long double FAR *) buffer) = (long double) (*((LONG FAR *) source));
    *bsize = sizeof(long double);
    }
  };
class ConvertQLongToShort : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((short FAR *) buffer) = (short) (*((long double FAR *) source));
    *bsize = sizeof(short);
    }
  };
class ConvertQLongToFloat : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((float FAR *) buffer) = (float) (*((long double FAR *) source));
    *bsize = sizeof(float);
    }
  };
class ConvertQLongToLong : public ConvertBase
  {
  virtual void ConvertIt(LPVOID buffer,int *bsize,LPVOID source)
    {
    *((LONG FAR *) buffer) = (LONG) (*((long double FAR *) source));
    *bsize = sizeof(LONG);
    }
  };
BOOL LongToFloat (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertLongToFloat b;
  return b.doIt (c,param,mode);
  }
BOOL ShortToFloat (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertShortToFloat b;
  return b.doIt (c,param,mode);
  }
BOOL FloatToLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertFloatToLong b;
  return b.doIt (c,param,mode);
  }
BOOL FloatToShort (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertFloatToShort b;
  return b.doIt (c,param,mode);
  }
BOOL LongToShort (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertLongToShort b;
  return b.doIt (c,param,mode);
  }
BOOL ShortToLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertShortToLong b;
  return b.doIt (c,param,mode);
  }
BOOL ShortToQLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertShortToQLong b;
  return b.doIt (c,param,mode);
  }
BOOL FloatToQLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertFloatToQLong b;
  return b.doIt (c,param,mode);
  }
BOOL LongToQLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertLongToQLong b;
  return b.doIt (c,param,mode);
  }
BOOL QLongToShort (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertQLongToShort b;
  return b.doIt (c,param,mode);
  }
BOOL QLongToFloat (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertQLongToFloat b;
  return b.doIt (c,param,mode);
  }
BOOL QLongToLong (mdiChild *c,LPVOID param,WORD mode)
  {
  ConvertQLongToLong b;
  return b.doIt (c,param,mode);
  }

#pragma pack(1)
struct ExtractDate_param {
  WORD parSize;
  DWORD dvar;
  DWORD year;
  DWORD month;
  DWORD day;
  DWORD weekday;
  };
#pragma pack()
BOOL ExtractDate (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    packdate FAR *pd = (packdate FAR *) c->ReadlData (par->dvar);
    if (pd != NULL) {
      int year    = pd->year;
      int month   = pd->month;
      int day     = pd->day;
      int weekday = WeekDay (PackTime(pd)) ;
      c->WritelData (par->year,&year,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->month,&month,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->day,&day,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->weekday,&weekday,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->year,LPSTR(param)-sizeof(WORD));
      c->DellData (par->month,LPSTR(param)-sizeof(WORD));
      c->DellData (par->day,LPSTR(param)-sizeof(WORD));
      c->DellData (par->weekday,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    c->SetlConnection (par->dvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    c->ClearlConnection (par->dvar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
BOOL BuildDate (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    short FAR *year    = (short FAR *) c->ReadlData (par->year);
    short FAR *month   = (short FAR *) c->ReadlData (par->month);
    short FAR *day     = (short FAR *) c->ReadlData (par->day);
    if ((year != NULL) && (month != NULL) && (day != NULL)) {
      packdate pd;
      pd.year = WORD (*year) ; pd.month = BYTE(*month) ; pd.day = BYTE(*day) ;
      c->WritelData (par->dvar,&pd,sizeof(pd),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->dvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    c->SetlConnection (par->year,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->month,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->day,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExtractDate_param FAR *par = (ExtractDate_param FAR *) param;
    c->ClearlConnection (par->year,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->month,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->day,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ExtractTime_param {
  WORD parSize;
  DWORD tvar;
  DWORD hour;
  DWORD minute;
  DWORD second;
  };
#pragma pack()
BOOL ExtractTime (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    packtime FAR *pt = (packtime FAR *) c->ReadlData (par->tvar);
    if (pt != NULL) {
      DBINT hour    = pt->hour;
      DBINT minute   = pt->minute;
      DBINT second     = pt->second;
      c->WritelData (par->hour,&hour,sizeof(hour),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->minute,&minute,sizeof(minute),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->second,&second,sizeof(second),LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->hour,LPSTR(param)-sizeof(WORD));
      c->DellData (par->minute,LPSTR(param)-sizeof(WORD));
      c->DellData (par->second,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    c->SetlConnection (par->tvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    c->ClearlConnection (par->tvar,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
BOOL BuildTime (mdiChild *c,LPVOID param,WORD mode) 
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    short FAR *hour    = (short FAR *) c->ReadlData (par->hour);
    short FAR *minute   = (short FAR *) c->ReadlData (par->minute);
    short FAR *second     = (short FAR *) c->ReadlData (par->second);
    if ((hour != NULL) && (minute != NULL) && (second != NULL)) {
      packtime pt;
      pt.hour = BYTE (*hour) ; pt.minute = BYTE(*minute) ; pt.second = BYTE(*second) ; pt.hundred_second = 0 ;
      c->WritelData (par->tvar,&pt,sizeof(pt),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->tvar,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    c->SetlConnection (par->hour,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->minute,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->second,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExtractTime_param FAR *par = (ExtractTime_param FAR *) param;
    c->ClearlConnection (par->hour,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->minute,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->second,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR GetNextFlagInd_param {
  WORD parSize;
  DWORD indref;
  DWORD _step;
  DWORD _flagval;
  DWORD flagref[1];
  int AnzRef()
    { return (parSize - sizeof(*this)) / sizeof(DWORD) + 1 ; }
  };
#pragma pack()

BOOL GetNextFlagInd (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    GetNextFlagInd_param FAR *par = (GetNextFlagInd_param FAR *) param;
    short numflags = par->AnzRef();
    short FAR *lpind = (short FAR *) c->ReadlData (par->indref);
    if (lpind != NULL) {
      short step;
      short _step = c->ReadConstInt(par->_step);
      short _flagval = c->ReadConstInt(par->_flagval);
      if (_step < 0L)
        step = _step + numflags;
      else
        step = _step;
      DBWIN_ASSERT((step > 0) && (step < numflags));
      short oldind = *lpind;
      short ind = (oldind + step) % numflags;
      while (ind != oldind) {   // hoechstens einmal alle durchsuchen
        short FAR *lpflag = (short FAR *)c->ReadlData(par->flagref[ind]);
        if ((lpflag != NULL) && (*lpflag)) {
          if (_flagval != 0L) break;
          }
        else {
          if (_flagval == 0L) break;
          }
        ind = (ind + step) % numflags;
        }
      c->WritelData (par->indref,&ind,sizeof(ind),LPSTR(param)-sizeof(WORD));
      if (_step < 0L)
        res = (ind >= oldind);
      else
        res = (ind <= oldind);
      }
    }

  return res ;
  }

#pragma pack(1)
struct ExpandBinary_param {
  WORD parSize;
  DWORD res;
  DWORD old;
  DWORD size;
  };
#pragma pack()
BOOL ExpandBinary (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExpandBinary_param FAR *par = (ExpandBinary_param FAR *) param;
    LPVOID old = c->ReadlData (par->old);
    short FAR *lpsize = (short FAR *) c->ReadlData (par->size);
    if ((old != NULL) && (lpsize != NULL) && (*lpsize >= (short) GetBlockSize(old))) {
      LPVOID res = GetGlobMem (*lpsize);
      lmemcpy (res,old,GetBlockSize(old));
      c->WritelData (par->res,res,*lpsize,LPSTR(param) - sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param) - sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExpandBinary_param FAR *par = (ExpandBinary_param FAR *) param;
    c->SetlConnection (par->old,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->size,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    ExpandBinary_param FAR *par = (ExpandBinary_param FAR *) param;
    c->ClearlConnection (par->old,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct InitializeVoidData_param {
  WORD parSize;
  DWORD Id;
  DWORD Size;
  DWORD Ref;
  };
#pragma pack()
BOOL InitializeVoidData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InitializeVoidData_param FAR * par = (InitializeVoidData_param FAR *) param;
    DBINT FAR *lpSize = (DBINT FAR *) c->ReadlData (par->Size);
    DBWIN_ASSERT ((lpSize != NULL) && (*lpSize > 0));
    LPVOID dummy = GetGlobMem (*lpSize);
    if (par->parSize >= sizeof(*par)) {
      LPVOID Init = c->ReadlData (par->Ref);
      int Size = GetBlockSize (Init);
      WIN_ASSERT (*lpSize % Size == 0);
      int count = *lpSize / Size ;
      for (int i = 0 ; i < count ; i++)
        lmemcpy (LPSTR(dummy) + i * Size,Init,Size);
      }
    c->WritelData (par->Id,dummy,*lpSize,LPSTR(param)-sizeof(WORD));
    FreeGlobMem (dummy);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    InitializeVoidData_param FAR * par = (InitializeVoidData_param FAR *) param;
    c->ClearlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
#pragma pack(1)
struct SetArrayData_param {
  WORD parSize;
  DWORD data;
  DWORD array;
  DWORD Ind;
  DWORD Size;
  };
#pragma pack()
BOOL SetArrayData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    LPSTR pool = LPSTR (c->ReadlData (par->array));
    LPVOID data = c->ReadlData (par->data);
    DBINT FAR *lpind = (DBINT FAR *) c->ReadlData (par->Ind);
    DBINT FAR *lpsize = (DBINT FAR *) c->ReadlData (par->Size);
    DBWIN_ASSERT ((pool != NULL) && (lpind != NULL) && (lpsize != NULL));
    int maxSize = GetBlockSize (pool);
    int offs = *lpind * *lpsize ;
    DBWIN_ASSERT (offs + *lpsize <= maxSize);
    lmemcpy (pool + offs,data,*lpsize);
    }
  if (mode & EM_FIXCONNECTION) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    c->SetlConnection (par->Ind,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->data,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    c->ClearlConnection (par->Ind,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->data,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
BOOL GetArrayData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    LPSTR pool = LPSTR (c->ReadlData (par->array));
    DBINT FAR *lpind = (DBINT FAR *) c->ReadlData (par->Ind);
    DBINT FAR *lpsize = (DBINT FAR *) c->ReadlData (par->Size);
    DBWIN_ASSERT ((pool != NULL) && (lpind != NULL) && (lpsize != NULL));
    int maxSize = GetBlockSize (pool);
    int offs = *lpind * *lpsize ;
    DBWIN_ASSERT (offs + *lpsize <= maxSize);
    c->WritelData (par->data,pool + offs,*lpsize,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    c->SetlConnection (par->Ind,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->array,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetArrayData_param FAR * par = (SetArrayData_param FAR *) param;
    c->ClearlConnection (par->Ind,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->array,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//============================================================================
//
// Zufallszahlengenerator
//
//============================================================================
#define CLOCK_SEQ_LAST              0x7FFF
#define RAND_MASK                   CLOCK_SEQ_LAST


struct unsigned64_t {
  DWORD  lo;
  DWORD  hi;
  };

void ADD_64b_2_64b (unsigned64_t *A, unsigned64_t *B, unsigned64_t *sum)
  {
  if (!(((A)->lo & 0x80000000UL) ^ ((B)->lo & 0x80000000UL))) {
    if (((A)->lo&0x80000000UL)) {
      (sum)->lo = (A)->lo + (B)->lo;
      (sum)->hi = (A)->hi + (B)->hi + 1;
      }
    else {
      (sum)->lo  = (A)->lo + (B)->lo;
      (sum)->hi = (A)->hi + (B)->hi;
      }
    }
  else {
    (sum)->lo = (A)->lo + (B)->lo;
    (sum)->hi = (A)->hi + (B)->hi;
    if (!((sum)->lo&0x80000000UL)) (sum)->hi++;
    }
  }



void mult32 (DWORD u, DWORD v, unsigned64_t *result)
  {
  // Following the notation in Knuth, Vol. 2.
  DWORD uuid1, uuid2, v1, v2, temp;

  uuid1 = u >> 16;
  uuid2 = u & 0xFFFF;
  v1 = v >> 16;
  v2 = v & 0xFFFF;
  temp = uuid2 * v2;
  result->lo = temp & 0xFFFF;
  temp = uuid1 * v2 + (temp >> 16);
  result->hi = temp >> 16;
  temp = uuid2 * v1 + (temp & 0xFFFF);
  result->lo += (temp & 0xFFFF) << 16;
  result->hi += uuid1 * v1 + (temp >> 16);
  }

void get_system_time (unsigned64_t *uuid_time)
  {
  unsigned64_t utc, usecs, os_basetime_diff;

  SYSTEMTIME SystemTime;

  GetSystemTime (&SystemTime);
  mult32((long)SystemTime.wSecond, 10000000L, &utc);
  mult32((long)SystemTime.wMilliseconds, 10, &usecs);
  ADD_64b_2_64b(&usecs, &utc, &utc);

  // Offset between UUID formatted times and Unix formatted times.
  // UUID UTC base time is October 15, 1582.
  // Unix base time is January 1, 1970.
  os_basetime_diff.lo = 0x13814000;
  os_basetime_diff.hi = 0x01B21DD2;
  ADD_64b_2_64b(&utc, &os_basetime_diff, uuid_time);
  }

//
// See "The Multiple Prime Random Number Generator" by Alexander 
// Hass pp. 368-381, ACM Transactions on Mathematical Software,
// 12/87.
//
static DWORD rand_m;
static DWORD rand_ia;
static DWORD rand_ib;
static DWORD rand_irand;

void true_random_init (void)
  {
  unsigned64_t t;
  WORD         seed;

  // Generating our 'seed' value Start with the current time, but,
  // since the resolution of clocks is system hardware dependent and
  // most likely coarser than our resolution (10 usec) we 'mixup' the
  // bits by xor'ing all the bits together.  This will have the effect
  // of involving all of the bits in the determination of the seed
  // value while remaining system independent.  Then for good measure
  // to ensure a unique seed when there are multiple processes 
  // creating UUIDs on a system, we add in the PID.
  // 
  rand_m = 971;
  rand_ia = 11113;
  rand_ib = 104322;
  rand_irand = 4181;
  get_system_time(&t);
  seed  =  WORD(t.lo) & 0xFFFF;
  seed ^= (t.lo >> 16) & 0xFFFF;
  seed ^=  t.hi        & 0xFFFF;
  seed ^= (t.hi >> 16) & 0xFFFF;
  rand_irand += seed + _getpid();
  }

WORD true_random (void)
  {
  if ((rand_m += 7) >= 9973)
       rand_m -= 9871;
  if ((rand_ia += 1907) >= 99991)
       rand_ia -= 89989;
  if ((rand_ib += 73939) >= 224729)
       rand_ib -= 96233;
  rand_irand = (rand_irand * rand_m) + rand_ia + rand_ib;
  return WORD((rand_irand >> 16) ^ (rand_irand & RAND_MASK));
  }


#pragma pack(1)
struct random_param {
  WORD parSize;
  DWORD result;
  };
#pragma pack()


static BOOL bFirstRandomInit = FALSE;


BOOL Random (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    random_param FAR * par = (random_param FAR *) param;
    if (!bFirstRandomInit) {
      true_random_init ();
      bFirstRandomInit = FALSE;
      }

    WORD j;
    j = true_random ();
    DWORD random = true_random () | j << 16;

    c->WritelData (par->result, &random, sizeof(random), LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }
