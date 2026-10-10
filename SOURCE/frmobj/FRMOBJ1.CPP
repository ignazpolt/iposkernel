////////////////////////////////////////////////////////////
//  Weitere Objektfunktionen
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/frmobj/rev/frmobj1.cpv   1.13   14 Apr 2000 23:12:40   Martin  $
//  $Log:   P:/marille/clinicum/frmobj/rev/frmobj1.cpv  $
// 
//    Rev 1.13   14 Apr 2000 23:12:40   Martin
// SetFocus nach SinglList->WorkOn (maennlich/weiblich - Fehler)
// 
//    Rev 1.12   27 Feb 1998 08:42:06   Hannes
// 
//    Rev 1.11   03 Feb 1998 19:29:40   Hannes
// GetUpperChar
// 
//    Rev 1.10   04 Apr 1997 15:21:04   Gerhold
// ShowToolList ... Umstellung von Client- auf Screen-Koordinaten
// 
//    Rev 1.9   05 Mar 1997 20:18:46   Martin
// Check*Sel: Formatierungen ueberspringen (erstes lesbares Zeichen nehmen)
// 
//    Rev 1.8   25 Jul 1996 20:00:14   GERHOLD
// WIN32 ... CharUpper
// 
//    Rev 1.7   10 Jun 1996 10:12:02   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.6   24 Mar 1996 12:11:24   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.5   02 Feb 1996 10:49:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   24 Aug 1995 00:15:08   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.3   30 Mar 1995 08:50:04   HANNES
// 
//    Rev 1.2   20 Mar 1995 12:13:30   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.1   31 Oct 1994 09:50:54   martin
// FrmTab - Objekte Indizess auf Spalte und Reige auf Referenzen umgestellt
// 
//    Rev 1.0   24 Jun 1994 16:45:42   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.17   14 Feb 1994 19:47:44   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.16   04 Jan 1994 16:37:50   HANNES
// Die Abgespeicherte šberlagerungsnummer (nicht c->RunNmbr) verwenden
// 
//    Rev 1.15   09 Dec 1993 14:58:24   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.14   29 Nov 1993 08:51:28   HANNES
// Updatemode bei Writedata
// 
//    Rev 1.13   22 Sep 1993 09:17:24   HANNES
// Version nach St. Poelten
// 
//    Rev 1.12   18 Aug 1993 10:30:08   HANNES
// Methoden Save ueberall korrigiert (RunNmbrs...)
// 
//    Rev 1.11   12 Jul 1993 07:54:20   HANNES
// Signed/Unsigned Mismatch
// 
//    Rev 1.10   05 Jul 1993 14:40:32   HANNES
// Multiselektionslisten
// 
//    Rev 1.9   19 Jun 1993 19:37:54   HANNES
// Multiselektionslisten
// 
//    Rev 1.8   17 Jun 1993 09:25:48   HANNES
// Erste Versuche mit der Multiliste
// 
//    Rev 1.7   08 Jun 1993 17:44:00   MARTIN
// FrmKuerzel->WorkOn
// 
//    Rev 1.6   28 May 1993 21:09:44   HANNES
// Vaterfenster an Search uebergeben
// 
//    Rev 1.5   10 May 1993 15:17:30   ANDI
// Korrektur bei der Fieberkurve
// 
//    Rev 1.4   10 May 1993 12:48:52   HANNES
// verschiedene neue Funktionen
// 
//    Rev 1.3   06 May 1993 21:00:56   ANDI
// vertikale Zahlenfolgen in Tabellenfeldern
// 
//    Rev 1.2   28 Apr 1993 18:51:46   NORBERT
// neue Tablle-funktionen: DefFrmTabStrList, DefFrmTabDate
// 
//    Rev 1.1   18 Apr 1993 22:55:20   MARTIN
// Checkbox erweitert
// 
//    Rev 1.0   02 Apr 1993 18:03:56   HANNES
// Initial revision.
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "globmem.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#define CARETHANDLING_DONE
#include "cfield.hpp"
#define MODULENUM     18
#include "winass.hpp"
#include "dictlist.hpp"
#include "multl.hpp"
#include "frmobj.hpp"

void FrmTab::Load ()
  {
  fpt FAR *pt = (fpt FAR *) m.ReadData (Par()->pR,Par()->pI);
  if ((pt != NULL) && (pt->x < 1.0E9)) {
    x0 = m.WorldToLog (pt->x);
    y0 = m.WorldToLog (pt->y);
    lmemcpy (&p0,pt,sizeof(p0));
    DWORD FAR * lpcu= (DWORD FAR *) m.ReadData (Par()->cuR,Par()->cuI);
    DWORD FAR * lpcv1= (DWORD FAR *) m.ReadData (Par()->cv1R,Par()->cv1I);
    DWORD FAR * lpcv= (DWORD FAR *) m.ReadData (Par()->cvR,Par()->cvI);
    DWORD FAR * lpch1= (DWORD FAR *) m.ReadData (Par()->ch1R,Par()->ch1I);
    DWORD FAR * lpch= (DWORD FAR *) m.ReadData (Par()->chR,Par()->chI);
    if ((lpcu != NULL) && (lpcv1 != NULL) && (lpcv != NULL) && (lpch1 != NULL) && (lpch != NULL)) {
      cu = *lpcu ;
      cv1 = *lpcv1 ;
      cv = *lpcv ;
      ch1 = *lpch1 ;
      ch = *lpch ;
      Initialized = TRUE ;
      width = int (m.GetConstInt(Par()->rs1Width)) + 
            int (m.GetConstInt (Par()->rsWidth) * (m.GetConstInt(Par()->rAnzSpalten) - 1));
      height = m.GetConstInt(Par()->rr1Height) + 
            int (m.GetConstInt(Par()->rrHeight) * (m.GetConstInt(Par()->rAnzReihen) - 1));
      }
    else
      Initialized = FALSE ;
    }
  else
    Initialized = FALSE ;
  }

void FrmTab::Update ()
  {
  Load ();
  }

void FrmTab::GetMinMax ()
  {
  int hpw = m.HalfPenWidth (cu);
  RECT rcLogRect ;
  rcLogRect.left = x0 - hpw ;
  rcLogRect.top = y0 ;
  rcLogRect.right = x0 + width + hpw;
  rcLogRect.bottom = y0 + height;
  int swap;
  if (rcLogRect.bottom < rcLogRect.top) {
    swap = rcLogRect.bottom ;
    rcLogRect.bottom = rcLogRect.top;
    rcLogRect.top = swap;
    }
  rcLogRect.top    -= hpw;
  rcLogRect.bottom += hpw;
  SetLogRect (&rcLogRect,ErsteSeite());
  }

void FrmTab::SetConnection ()
  {
  m.SetConnection (Par()->pR,Par()->pI,Offset());
  m.SetConnection (Par()->cuR,Par()->cuI,Offset());
  m.SetConnection (Par()->cv1R,Par()->cv1I,Offset());
  m.SetConnection (Par()->cvR,Par()->cvI,Offset());
  m.SetConnection (Par()->ch1R,Par()->ch1I,Offset());
  m.SetConnection (Par()->chR,Par()->chI,Offset());
  }

void FrmTab::Reset (BOOL doClear)
  {
  m.ClearConnection (Par()->pR,Par()->pI,Offset());
  m.ClearConnection (Par()->cuR,Par()->cuI,Offset());
  m.ClearConnection (Par()->cv1R,Par()->cv1I,Offset());
  m.ClearConnection (Par()->cvR,Par()->cvI,Offset());
  m.ClearConnection (Par()->ch1R,Par()->ch1I,Offset());
  m.ClearConnection (Par()->chR,Par()->chI,Offset());
  }

void FrmTab::Paint (PaintContext *pc,int Seite)
  {
  int i ;

  pc->diPen (cu);
  pc->PolyMoveTo (x0,y0);
  pc->PolyLineTo (x0,y0+height);
  pc->PolyLineTo (x0+width,y0+height);
  pc->PolyLineTo (x0+width,y0);
  pc->PolyLineTo (x0,y0);
  pc->diPen (cv1);
  int x = x0 + m.GetConstInt(Par()->rs1Width) ;
  for (i = 0 ; i < m.GetConstInt(Par()->rAnzSpalten) - 1 ; i++) {
    pc->PolyMoveTo (x,y0);
    pc->PolyLineTo (x,y0+height);
    x += m.GetConstInt(Par()->rsWidth);
    if (i == 0) pc->diPen (cv);
    }
  pc->diPen (ch1);
  int y = y0 + m.GetConstInt(Par()->rr1Height) ;
  for (i = 0 ; i < m.GetConstInt(Par()->rAnzReihen) - 1 ; i++) {
    pc->PolyMoveTo (x0,y);
    pc->PolyLineTo (x0 + width,y);
    y += m.GetConstInt(Par()->rrHeight) ;
    if (i == 0) pc->diPen (ch);
    }
  }

BOOL FrmTab::GetFieldPos (POINT FAR *o,dllChild FAR *c,LONG rReihe,LONG rSpalte)
  {
  int Reihe = int(rReihe) ;
  int Spalte = int(rSpalte) ;
  if ((Reihe >= m.GetConstInt(Par()->rAnzReihen)) || 
      (Spalte >= m.GetConstInt(Par()->rAnzSpalten))) 
    return FALSE ;
  if (Spalte == 0) o->x = x0 ;
  else {
    o->x = x0 + m.GetConstInt(Par()->rs1Width) + 
                (Spalte - 1) * m.GetConstInt(Par()->rsWidth);
    }
  if (Reihe == 0) o->y = y0 ;
  else {
    o->y = y0 + m.GetConstInt(Par()->rr1Height) + (Reihe - 1) * m.GetConstInt(Par()->rrHeight);
    }
  return TRUE ;
  }

BOOL FrmTab::CalcLogFieldPos (POINT FAR *o,int Reihe,int Spalte)
  {
  if (Spalte == 0) o->x = x0 ;
  else {
    o->x = x0 + m.GetConstInt(Par()->rs1Width) + int((Spalte - 1) * m.GetConstInt(Par()->rsWidth));
    }
  if (Reihe == 0) o->y = y0 ;
  else {
    o->y = y0 + m.GetConstInt(Par()->rr1Height) + int((Reihe - 1) * m.GetConstInt(Par()->rrHeight));
    }
  return TRUE ;
  }

BOOL FrmTab::CalcFieldPos (fpt FAR *p,int Reihe,int Spalte)
  {
  if (Spalte == 0) p->x = p0.x ;
  else {
    p->x = p0.x + m.GetConstInt(Par()->rs1Width) + ((Spalte - 1) * m.GetConstInt(Par()->rsWidth));
    }
  if (Reihe == 0) p->y = p0.y ;
  else {
    p->y = p0.y + m.GetConstInt(Par()->rr1Height) + ((Reihe - 1) * m.GetConstInt(Par()->rrHeight));
    }
  return TRUE ;
  }

BOOL FrmTabField::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->f.PtRec,Par()->f.PtId);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o, &m, m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabDate::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->f.PtRec,Par()->f.PtId);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o, &m, m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabDec::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->dec.fld.PtRec,Par()->dec.fld.PtId);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o,&m,m.GetConstInt(Par()->rReihe),
                                      m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabStrList::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->slist.fld.PtRec,Par()->slist.fld.PtId);
  DBWIN_ASSERT (obj != NULL);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o,&m,m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabShortStrList::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->slist.fld.PtRec,Par()->slist.fld.PtId);
  DBWIN_ASSERT (obj != NULL);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o,&m,m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabFlag::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->flg.PtRec,Par()->flg.PtId);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o,&m,m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

BOOL FrmTabCheckField::GetOrg (POINT *o)
  {
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->fld.PtRec,Par()->fld.PtId);
  if ((obj != NULL) && (*obj != NULL))
    return (* obj)->GetFieldPos (o,&m,m.GetConstInt(Par()->rReihe),
                                        m.GetConstInt(Par()->rSpalte));
  else
    return FALSE ;
  }

LPSTR PushSent (LPSTR old,LPSTR ts)
  {
  char actstr[128];
  int j = 0 ;
  BOOL spfound = FALSE ;
  for (int i = 0 ; ts[i] ; i++) {
    if ((!spfound) && (ts[i] == ' ')) spfound = TRUE ;
    else {
      if (spfound) actstr[j++] = ts[i] ;
      }
    }
  actstr[j++] = '\0' ;
  int oldsize;
  if (old != NULL)
    oldsize = int (GetBlockSize (old)) - 1;
  else
    oldsize = 0;
  int newsize = lstrlen (actstr) + 2;
  LPSTR nw = LPSTR (GetGlobMem (oldsize + newsize));
  if (old != NULL) {
    lmemcpy (nw,old,oldsize);
    FreeGlobMem (old);
    }
  lstrcpy (nw + oldsize,actstr);

  return nw;
  }

LPSTR GetSpcText (LPSTR otxt)
  {
  LPSTR res = NULL;
  LPSTR ts = otxt;
  LPSTR ht;
  for ( ; ; ) {
    for (ht = ts ; *ht ; ht++) ;
    ht++;
    if (*ht == '\0') {
      res = PushSent (res,ts);
      break ;
      }
    res = PushSent (res,ts);
    ts = ht ;
    }
  return res;
  }

char GetUpper (char ch)
  {
#ifdef WIN32
  char chtmp[2];
  chtmp[0] = ch;
  chtmp[1] = '\0'; 
  CharUpper (chtmp);
  return chtmp[0];
#else
  return (char) (DWORD) AnsiUpper (LPSTR (MAKELP (0,ch)));
#endif
  }
int FrmStrList::CheckOneSel (GLOBALHANDLE hG,LPSTR txt)
  {
  char ch = GetUpper (*txt);
  LPSTR Buffer = LPSTR(GlobalLock(hG)) + sizeof (WORD);
  int res = -1 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  Buffer = field->SkipFormat(Buffer);
  for ( ; *Buffer ; ) {
    if (ch == GetUpper (*Buffer)) {
      if (res >= 0) return -1 ;       // nicht eindeutig
      res = i ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    Buffer = field->SkipFormat(Buffer);
    i++ ;
    }
  return res ;
  }

int FrmStrList::CheckBestSel (GLOBALHANDLE hG,LPSTR txt)
  {
  char ch = GetUpper (*txt);
  LPSTR Buffer = LPSTR(GlobalLock(hG)) + sizeof (WORD);
  int res = 0 ;
  int i = 0 ;
  if ((Buffer[0] == '\0') && (Buffer[1])) Buffer++; // Den Leerstring am Start
                                                    // ignorieren
  Buffer = field->SkipFormat(Buffer);
  int olddiff = 10000;
  for ( ; *Buffer ; ) {
    int diff = int (ch) - (int) GetUpper (*Buffer);
    if ((diff >= 0) && (diff < olddiff)) {
      res = i ;
      if (diff == 0) break ;
      }
    for ( ; *Buffer ; Buffer ++) ;
    Buffer ++ ;
    Buffer = field->SkipFormat(Buffer);
    i++ ;
    }
  return res ;
  }

void FrmStrList::ShowList (LPSTR str)
  {
  m.Set_sli_res(0);
  GetResource ();

  int ActInd = -1;

  if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
    // Versuchen, ob die Auswahl eindeutig...
    ActInd = CheckOneSel (m.Get_sli_res(),str);

  if (ActInd < 0) {
    // Nicht direkt gefunden > Liste aufmachen
    int Ind ;
    if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
      // Suchen in der Liste
      Ind = CheckBestSel (m.Get_sli_res(),str);
    else
      // Aktuellen Index verwenden
      Ind = m.Get_sli_Ind() ;

    LPSTR txt = LPSTR(GlobalLock (m.Get_sli_res())) + sizeof(WORD);
    SinglList s(txt,Ind);
    RECT cr,fr;

    GetWindowRect (m.MyHandle(),&cr);    // Screen-Koordinaten verwenden!!
//    GetClientRect (m.MyHandle(),&cr);
    {
    PaintContext pc;
    GetDocumentContext (&pc,m);
    LPRECT logr = GetLogRect (m.ActSide());
    WIN_ASSERT (logr != NULL);
    pc.LogRecttoPhys (&fr,logr);
    ClientToScreen (pc.hWnd, LPPOINT(&fr.left));
    ClientToScreen (pc.hWnd, LPPOINT(&fr.right));
    }
    if (s.WorkOn (m.MyHandle(),&fr,&cr))
      ActInd = s.res;
    GlobalFree (m.Get_sli_res());

    // Focus wieder auf das Formular setzen
    SetFocus(m.MyHandle());
    }
  else
    GlobalFree (m.Get_sli_res());

  if (ActInd >= 0) {
    // Neues Resultat -> Update
    char resstr[256];
    m.Set_sli_Ind(ActInd);
    m.Set_sli_actTxt(resstr);
    GetSelText ();
    *field = resstr;
    field->Reformat();
    Invalidate (m.ActSide());
    Save ();
    }

  }

void FrmDivStrList::ShowList (LPSTR str)
  {
  m.Set_sli_res(0);
  GetResource ();

  int ActInd = -1;

  if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
    // Versuchen, ob die Auswahl eindeutig...
    ActInd = CheckOneSel (m.Get_sli_res(),str);

  if (ActInd < 0) {
    // Nicht direkt gefunden > Liste aufmachen
    int Ind ;
    if ((str != NULL) && (*str) && (*str != ' ') && (*str != '\r'))
      // Suchen in der Liste
      Ind = CheckBestSel (m.Get_sli_res(),str);
    else
      // Aktuellen Index verwenden
      Ind = m.Get_sli_Ind() ;

    LPSTR txt = GetSpcText (LPSTR(GlobalLock (m.Get_sli_res())) + sizeof(WORD));
    SinglList s(txt,Ind);
    RECT cr,fr;
    GetClientRect (m.MyHandle(),&cr);
    {
    PaintContext pc;
    GetDocumentContext (&pc,m);
    LPRECT logr = GetLogRect (m.ActSide());
    WIN_ASSERT (logr != NULL);
    pc.LogRecttoPhys (&fr,logr);
    }
    if (s.WorkOn (m.MyHandle(),&fr,&cr))
      ActInd = s.res;
    FreeGlobMem (txt);
    GlobalFree (m.Get_sli_res());

    // Focus wieder auf das Formular setzen
    SetFocus(m.MyHandle());
    }
  else
    GlobalFree (m.Get_sli_res());

  if (ActInd >= 0) {
    // Neues Resultat -> Update
    char resstr[256];
    m.Set_sli_Ind(ActInd);
    m.Set_sli_actTxt(resstr);
    GetSelText ();
    *field = resstr;
    field->Reformat();
    Invalidate (m.ActSide());
    Save ();
    }

  }

/////////////////////////////////////////////////////////////////
//  Implementierung der Klasse FrmTabColDec
/////////////////////////////////////////////////////////////////
void FrmTabColDec::DelFields ()
  {
  if (fields != NULL) {
    for (int i = 0 ; i < AnzFields ; i++)
      delete fields[i];
    FreeGlobMem (fields);
    fields = NULL;
    }
  }

void FrmTabColDec::GetNextRound (double FAR *res, double dmin)
  {
  static float dxp [22] = {
    float(0.01) , float(0.02) , float(0.05) , float(0.1) ,  float(0.2) ,  float(0.5) , 
    float(1.0) ,  float(2.0) ,  float(5.0) ,  float(10.0) , float(20.0) , float(50.0) , 
    float(100.0) ,   float(200.0) ,   float(500.0) ,   float(1000.0) ,  float(2000.0) , 
    float(5000.0) ,  float(10000.0) , float(20000.0) , float(50000.0) , float(100000.0)
    };
  int dim = 22;
  for (int i = 0 ; i < dim ; i++)
    if (double (dxp[i]) > dmin) {
      *res = dxp[i] ;
      return;
      }
  *res = dxp[dim-1];
  }

void FrmTabColDec::InitializeTrans ()
  {
  // Zuerst mal nachsehen, ob's die Tabelle giebt
  LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) m.ReadData (Par()->TabRec,Par()->TabId);
  Initialized = TRUE;
  POINT o1,o2;
  if ((obj != NULL) && (*obj != NULL)) {
    Initialized = 
        (* obj)->CalcLogFieldPos (&o1,m.GetConstInt(Par()->rReihe),m.GetConstInt(Par()->rSpalte));
    Initialized = Initialized &&
        (* obj)->CalcLogFieldPos (&o2,m.GetConstInt(Par()->rReihe)+1,m.GetConstInt(Par()->rSpalte));
    y0 = min(o1.y,o2.y) ;
    y1 = max(o1.y,o2.y) ;
    }
  else
    Initialized = FALSE ;

  if (!Initialized) return ;

  // Berechnung von x0
  x0 = o1.x + m.GetConstInt(Par()->rx0) ;

  // Berechnung der Zeilenhoehe
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  LPFORMATMETRIC lpfm = GetFormatMetrics (m.MyHandle(),MapType,m.GetConstInt(Par()->rFormat));
  if (Initialized = (lpfm != NULL))
    LineHeight = lpfm->yBaseHeight;

  if (!Initialized) return ;

  // Berechnung der Abblidungsfaktoren
  float FAR *sval = (float FAR *) m.ReadData (Par()->svalr, Par()->svali);
  float FAR *eval = (float FAR *) m.ReadData (Par()->evalr, Par()->evali);
  if ((eval != NULL) && (sval != NULL) && (fabs(*eval - *sval) >= 0.01) &&
        ((o2.y - o1.y) != 0)) {
    double dys = double (*eval - *sval);
    double dyd = double (o2.y - o1.y);
    a = dyd / dys;
    b = double (o1.y) - a * *sval ;
    }
  else
    Initialized = FALSE ;

  if (!Initialized) return ;

  // So, jetzt kommt der schwierige Teil
  int height = o2.y - o1.y - LineHeight;
  int MaxAnz = height / LineHeight ; 

  double epos ;
  double s0v, e0v;
  valfrompos (&s0v, double (o1.y + LineHeight / 2)) ;
  valfrompos (&e0v, epos = double (o2.y - LineHeight / 2)) ;
  double dmin = double (LineHeight) / a;
  GetNextRound (&dval, fabs(dmin));  // Ermitteln der naechsten Runden Zahl
  if (dmin < 0) dval = -dval;

  val0 = double (int (s0v / dval)) * dval ;
  if ((s0v < e0v) && (val0 < s0v)) val0 += fabs (dval) ; // val0 muss groesser als s0v sein 
  if ((s0v > e0v) && (val0 > s0v)) val0 -= fabs (dval) ; // val0 muss kleiner als s0v sein

  // Bestimmung der Anzahl Werte (nicht lang mit komplizierten algorythmen probieren
  for (int i = 0 ; ; i++) {
    double v;
    val(&v, i);
    double fp;
    fldpos(&fp, v);
    if (fp > epos) break ;
    }
  AnzFields = i ;
  if (AnzFields <= 0) Initialized = FALSE ; // War alles umsonst

  // Fertig
  }


void FrmTabColDec::FldTopPos (LPPOINT pt,int num)
  {
  pt->x = x0;
  double v;
  val(&v, num);
  double fp;
  fldpos(&fp, v);
  pt->y = int (fp) - (LineHeight) / 2 ;
  }

extern void SetCallback (FrmObject FAR *obj,cField FAR *f,dllChild m) ;
void FrmTabColDec::GetFields ()
  {
  DBWIN_ASSERT (AnzFields > 0);
  fields = (LPCFIELD FAR *) GetGlobMem (AnzFields * sizeof(LPCFIELD));
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  char format[64];
  lstrcpy (format, LPSTR(m.ReadData(Par()->fr, Par()->fi)));  // format muss existieren
  for (int i = 0 ; i < AnzFields ; i++) {
    POINT fldpos;
    FldTopPos (&fldpos,i);
    fields[i] = new cField (TRANSPARENT,int(m.GetConstInt(Par()->rFormat)),
                                        fldpos.x,fldpos.y,
                                        m.GetConstInt(Par()->rwidth),-1,FALSE
                           );
    SetCallback (this,fields[i],m) ;
    fields[i]->SetWindow (m.MyHandle());
    fields[i]->SetScale (m_scale(),MapType);
    fields[i]->SetVOrg (m.xp(),m.yp(),ErsteSeite());
    fields[i]->SetFieldMode (FM_OUTLINEONLY | FM_SINGLELINE);

    if (MapType == MAPTYPE_GEOMETRIC) {
      POINT pt;
      m.GetDocInfo (GETWINDOWORG,0,&pt);
      fields[i]->SetWOrg (pt.x,pt.y);
      }
    char txt[64];
    double v;
    val(&v, i);
    sprintf (txt,format,v);
    *(fields[i]) = txt;
    }
  }

void FrmTabColDec::Load ()
  {
  InitializeTrans ();
  if (Initialized)
    GetFields ();
  }

void FrmTabColDec::Update ()
  {
  DelFields ();
  Load ();
  }

void FrmTabColDec::Paint (PaintContext *pc,int Seite)
  {
  for (int i = 0 ; i < AnzFields ; i++) {
    DBWIN_ASSERT(fields[i] != NULL);
    fields[i]->Paint (pc->hDC,Seite,((pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)));
    }
  }

void FrmTabColDec::SetConnection ()
  {
  m.SetConnection (Par()->TabRec,Par()->TabId,Offset());
  m.SetConnection (Par()->svalr,Par()->svali,Offset());
  m.SetConnection (Par()->evalr,Par()->evali,Offset());
  }

void FrmTabColDec::Reset (BOOL Clear)
  {
  m.ClearConnection (Par()->TabRec,Par()->TabId,Offset());
  m.ClearConnection (Par()->svalr,Par()->svali,Offset());
  m.ClearConnection (Par()->evalr,Par()->evali,Offset());
  DelFields ();
  }

void FrmTabColDec::Reformat (BOOL forPrinter)
  {
  if (Initialized) {
    DBWIN_ASSERT(fields != NULL);
    for (int i = 0 ; i < AnzFields ; i++)
      fields[i]->Reformat ();
    }
  }

void FrmTabColDec::GetMinMax ()
  {
  if (Initialized) {
    DBWIN_ASSERT(fields != NULL)
    RECT rcLogRect;
    fields[0]->GetFullFieldRect(&rcLogRect,ErsteSeite());
    for (int i = 1 ; i < AnzFields ; i++) {
      RECT r;
      fields[i]->GetFullFieldRect (&r,ErsteSeite());
      MyUnionRect (&rcLogRect,&rcLogRect,&r);
      }
    SetLogRect (&rcLogRect,ErsteSeite());
    }
  }

void FrmTabColDec::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  if (fields != NULL) {
    for (int i = 0 ; i < AnzFields ; i++) {
      fields[i]->SetScale (scale,MapType);
      fields[i]->SetVOrg (xp,yp,ErsteSeite());
      fields[i]->SetWOrg (x0,y0);
      }
    }
  }

void FrmTabColDec::GetValPos (LPFKPT pt,double val)
  {
  pt->x0 = x0 ;
  pt->x1 = x0 + m.GetConstInt(Par()->rwidth) ;
  double fp;
  fldpos(&fp, val);
  pt->y = int (fp) ;
  pt->isValid = TRUE ;
  if (pt->y < y0) {
    pt->isBorder = TRUE ;
    pt->yb = y0 ;
    }
  if (pt->y > y1) {
    pt->isBorder = TRUE ;
    pt->yb = y1 ;
    }
  }

// Implementierung der Klasse FrmFKurve
int LinIntPos (int x0,int y0,int x1,int y1,int border)
  {
  double dxg = double (x1 - x0) ;
  double dyg = double (y1 - y0) ;
  double dy  = double (border - y0) ;
  return int (dy * dxg / dyg) ;
  }

void FrmFKurve::Load ()
  {
  Anz = AnzRows ();
  Initialized = TRUE ;
  if (points != NULL) {
    FreeGlobMem (points) ;
    points = NULL ;
    }
  points = LPFKPT (GetGlobMem (sizeof(FKpt) * Anz));
  DWORD FAR *col = (DWORD FAR *)
     m.ReadData(Par()->colr,Par()->coli);
  if (col != NULL)
    color = *col;
  else
    Initialized = FALSE ;

  BOOL oneFound = FALSE ;
  for (int i = 0 ; ((i < Anz) && (Initialized)) ; i++) {
    LPTABDECOBJ FAR *tdo = (LPTABDECOBJ FAR *) 
       m.ReadData (Par()->x[i].cdr,Par()->x[i].cdi);
    float FAR *val = (float FAR *)
       m.ReadData (Par()->x[i].valr,Par()->x[i].vali);
    if ((tdo != NULL) && (*tdo != NULL) &&
               (val != NULL) && (*val <= 1.0E9)) {
      (*tdo)->GetValPos (&points[i],*val);
      oneFound = ((points[i].isValid) && (!points[i].isBorder)) ;
      points[i].hIsValid = TRUE ;
      }
    }
  if (!oneFound) Initialized = FALSE ;

  for ( i = 1 ; ((i < Anz) && (Initialized)) ; i++) {
    if (points[i].hIsValid = points[i].isValid) {
      if ((points[i].isBorder) &&
          (points[i-1].isValid) && 
            ((!points[i-1].isBorder) || (points[i-1].yb != points[i].yb))
         ) {
        points[i].x0 = LinIntPos (points[i-1].x1,points[i-1].y,
                                  points[i].x0,points[i].y,
                                  points[i].yb
                                 );
        }
      else {
        if ((points[i].isBorder) &&
             (points[i-1].isValid) && 
               ((!points[i-1].isBorder) == (points[i-1].yb != points[i].yb)))
          points[i].hIsValid = FALSE ;
        }
      }
    }

  for ( i = Anz - 1 ; ((i >= 0) && (Initialized)) ; i--) {
    if (points[i].hIsValid = points[i].isValid) {
      if ((points[i].isBorder) &&
           (points[i+1].isValid) && 
             ((!points[i+1].isBorder) || (points[i+1].yb != points[i].yb))
         ) {
        points[i].x1 = LinIntPos (points[i+1].x0,points[i+1].y,
                                  points[i].x1,points[i].y,
                                  points[i].yb
                                 );
        }
      else {
        if ((points[i].isBorder) &&
             (points[i+1].isValid) && 
               ((!points[i+1].isBorder) == (points[i+1].yb != points[i].yb)))
          points[i].hIsValid = FALSE ;
        }
      }
    }

  for ( i = 0 ; ((i < Anz) && (Initialized)) ; i++) {
    if (points[i].isValid = points[i].hIsValid) {
      if (points[i].isBorder)
        points[i].y = points[i].yb;
      }
    }
  }

void FrmFKurve::Update ()
  {
  Load ();
  }

void FrmFKurve::SetConnection()
  {
  m.SetConnection (Par()->colr,Par()->coli,Offset());
  for (int i = 0 ; i < Anz ; i++) {
    m.SetConnection (Par()->x[i].valr,Par()->x[i].vali,Offset());
    m.SetConnection (Par()->x[i].cdr,Par()->x[i].cdi,Offset());
    }
  }

void FrmFKurve::Reset(BOOL)
  {
  m.ClearConnection (Par()->colr,Par()->coli,Offset());
  for (int i = 0 ; i < Anz ; i++) {
    m.ClearConnection (Par()->x[i].valr,Par()->x[i].vali,Offset());
    m.ClearConnection (Par()->x[i].cdr,Par()->x[i].cdi,Offset());
    }
  if (points != NULL) {
    FreeGlobMem (points) ;
    points = NULL ;
    }
  }

void FrmFKurve::Paint (PaintContext *pc,int Seite)
  {
  pc->diPen (color);
  for (int i = 0 ; i < Anz ; i++) {
    if (points[i].isValid) {
      if ((i > 0) && (points[i-1].isValid))
        *pc << Line(points[i-1].x1,points[i-1].y,
                    points[i].x0,points[i].y
                   );
      *pc << Line(points[i].x0,points[i].y,
                  points[i].x1,points[i].y
                 );
      }
    }
  }

void FrmFKurve::InitializeLogRect (LPRECT rcLogRect)
  {
  rcLogRect->top    = 32000;
  rcLogRect->left   = 32000;
  rcLogRect->right  = -32000;
  rcLogRect->bottom = -32000;
  }

void FrmFKurve::CheckLogRect (LPRECT rcLogRect,int x,int y)
  {
  if (x < rcLogRect->left)   rcLogRect->left = x ;
  if (x > rcLogRect->right)  rcLogRect->right = x ;
  if (y < rcLogRect->top)    rcLogRect->top = y ;
  if (y > rcLogRect->bottom) rcLogRect->bottom = y ;
  }

void FrmFKurve::GetMinMax ()
  {
  RECT rcLogRect;
  InitializeLogRect (&rcLogRect);
  for (int i = 0 ; i < Anz ; i++) {
    if (points[i].isValid) 
      CheckLogRect (&rcLogRect,points[i].x0,points[i].y),
      CheckLogRect (&rcLogRect,points[i].x1,points[i].y);
    }
  int hpw = m.HalfPenWidth(color) ;
  rcLogRect.top    -= hpw;
  rcLogRect.left   -= hpw;
  rcLogRect.right  += hpw;
  rcLogRect.bottom += hpw;

  SetLogRect (&rcLogRect,ErsteSeite());
  }

void FrmMultiField::WorkOn (LPVOID Info)
  {
  // Text vom Feld abfragen
  GLOBALHANDLE hGtmp ;
  *field >> hGtmp;
  LPSTR txt = LPSTR(GlobalLock (hGtmp));

  MultiList h (List,txt);
  TWI FAR *t = (TWI FAR *) Info;

  RECT fr,cr;
  {
  PaintContext pc;
  GetDocumentContext (&pc,m);
  LPRECT logr = GetLogRect (m.ActSide());
  WIN_ASSERT (logr != NULL)
  pc.LogRecttoPhys (&fr,logr);
  }
  GetClientRect (m.MyHandle(),&cr);
  h.WorkOn (m.MyHandle(),&fr,&cr);

  if (lstrcmp (txt,h.restxt) != NULL) {
    *field = h.restxt;
    Save ();

    GetMinMax ();
    Invalidate (m.ActSide());
    }

  if (hGtmp)
    GlobalFree (hGtmp);
  }

void FrmMultiField::GetWord (LPVOID Info)
  {
  TWI FAR *t = (TWI FAR *) Info;
  LPSTR res = GetWordText (List,t->Index);
  if (res != NULL) {
    t->res = TRUE ;
    t->resWord = LPSTR (GetGlobMem (lstrlen(res)+1));
    lstrcpy (t->resWord,res);
    }
  }

void FrmMultiField::Load ()
  {
  LPMLI FAR *d = (LPMLI FAR *) m.ReadData (Par()->lRec,Par()->lId);
  DBWIN_ASSERT (d != NULL) ;
  List = *d ;
  FrmField::Load ();
  if (Initialized) {
    field->SetFieldMode (FM_MSELECTION | FM_NOSELECTION);
    }
  }

void FrmMultiField::Update ()
  {
  FrmField::Update ();
  if (Initialized) {
    field->SetFieldMode (FM_MSELECTION | FM_NOSELECTION);
    }
  }

void FrmMultiField::TestChar (LPVOID Info)
  {
  LPTCI t = LPTCI (Info);
  GLOBALHANDLE hGtmp ;
  *field >> hGtmp;
  LPSTR txt = LPSTR(GlobalLock (hGtmp));
  MultiList h (List,txt);

  if (t->forDel) {
    WORD cPos = t->cPos;
    if (!t->delUnder) {
      cPos = (cPos > 0) ? cPos - 1 : 0xFFFF ;
      }
    if (int (cPos) < lstrlen(txt))
      t->dontBeep = h.DelItem (cPos);
    }
  else {
    t->dontBeep = h.AddItem (t->wP);
    }
  t->wP = 0;

  if (lstrcmp (txt,h.restxt) != NULL) {
    *field = h.restxt;
    Save ();
    GetMinMax ();
    Invalidate (m.ActSide());
    }

  if (hGtmp)
    GlobalFree (hGtmp);
  }


