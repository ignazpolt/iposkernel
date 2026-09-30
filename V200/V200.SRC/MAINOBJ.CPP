//  Implementierung der Objekte (speziell fuer Form)
//
/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/mainobj.cpv   1.112   29 Jun 2000 15:28:24   Wolfgang  $
// $Log:   P:/marille/clinicum/rev/mainobj.cpv  $
// 
//    Rev 1.112   29 Jun 2000 15:28:24   Wolfgang
// 1.) GetObjLineHeight mit FixConnection auf obj.
// 
//    Rev 1.111   28 May 2000 18:40:06   Hannes
// Fehlerkorrektur in SetFocusToSubDoc
// 
//    Rev 1.110   28 Apr 2000 15:09:00   Martin
// act != NULL Abfrage in SetFocusToSubDoc
// 
//    Rev 1.109   10 Apr 2000 15:01:40   Wolfgang
// 1.) SetFieldPageBreak setzt Modify-Flag nicht mehr.
// 
//    Rev 1.108   28 Mar 2000 09:04:48   Hannes
// TAB mit Seitenwechsel
// 
//    Rev 1.107   23 Mar 2000 23:00:08   Hannes
// uMutualExcludeNone...
// 
//    Rev 1.106   23 Mar 2000 15:44:04   Wolfgang
// 1.) BlockIsActive innerhalb von SetFocusToSubDoc auf FALSE.
// 
//    Rev 1.105   20 Mar 2000 09:52:06   Hannes
// 
//    Rev 1.104   29 Feb 2000 10:51:20   Hannes
// Update auf Seitengrenze, ev. Rescale beim ShowObject
// 
//    Rev 1.103   25 Nov 1999 02:52:46   Hannes
// ObjInfo als String
// 
//    Rev 1.102   23 Nov 1999 17:23:22   Hannes
// Diverse Erweiterungen..
// 
//    Rev 1.101   16 Nov 1999 16:48:18   Hannes
// 
//    Rev 1.100   12 Oct 1999 14:04:22   Hannes
// ParentInstance(): Nicht DrawContext, sondern ErzContext...
// 
//    Rev 1.99   27 Jun 1999 21:56:50   Hannes
// Diverse Hilfsfunktionen fuer die Rechtschreibpruefung
// 
//    Rev 1.98   02 Jun 1999 15:41:12   Wolfgang
// 1.) In einem FrmObjectList::Remove c->OutWnd auf NULL geprueft.
// 
//    Rev 1.97   14 May 1999 11:50:40   Hannes
// 
//    Rev 1.96   14 May 1999 11:39:30   Hannes
// Entschaerfung bei uFrmShowObject::Add
// 
//    Rev 1.95   07 May 1999 00:20:20   Hannes
// NextObjDef beim uFrmShowObject, auch echte Objekte zur Reihenfolgenangabe
// 
//    Rev 1.94   31 Mar 1999 15:08:32   Hannes
// Beim Reset keine Reads, wenn Expressions
// 
//    Rev 1.93   05 Mar 1999 10:56:26   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.92   24 Nov 1998 14:49:16   Wolfgang
// 1.) SetExtraModify (0) bei Reset ebenfalls nur wenn nicht in Liste.
// 2.) SetExtraModify reagiert auf Updates.
// 
//    Rev 1.91   24 Nov 1998 12:25:06   Wolfgang
// 1.) Mit Default-Color zeichnen in SetObjectColor nur wenn nicht in Liste.
// 
//    Rev 1.90   02 Nov 1998 19:29:32   Martin
// uFrmShowObject: bei Aenderung der Seite auf jeden Fall GetMinMax()
// 
//    Rev 1.89   15 Sep 1998 10:49:58   Martin
// EntDef: statt WriteData NULL -> DelData
// 
//    Rev 1.88   07 Jul 1998 13:51:54   Hannes
// Enable - Flag -> Focus setzen
// 
//    Rev 1.87   29 Jun 1998 19:03:58   Hannes
// No change.
// 
//    Rev 1.86   08 Jun 1998 15:01:30   Martin
// FieldColor eingebaut
// 
//    Rev 1.85   04 Jun 1998 15:51:56   Hannes
// SetDirKey sauber
// 
//    Rev 1.84   27 Apr 1998 12:52:04   Hannes
// Trc_DefContain2
// 
//    Rev 1.83   21 Apr 1998 19:58:46   Martin
// DefEntParam korrigiert
// 
//    Rev 1.82   21 Apr 1998 19:34:02   Hannes
// Erweiterung um den Containerbausteines
// 
//    Rev 1.81   02 Mar 1998 19:13:50   Hannes
// Trc_DefEllipse
// 
//    Rev 1.80   23 Feb 1998 20:02:24   Hannes
// SetInactiveIf: Ohne rosa Schirm, nur abgesichert
// 
//    Rev 1.79   16 Feb 1998 07:56:28   Gerhold
// VC++5.x ... Variable "explicit" darf nicht verwendet werden (Schluesselwort)
// 
//    Rev 1.78   09 Feb 1998 18:12:56   Hannes
// 
//    Rev 1.77   05 Jan 1998 07:53:38   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.76   15 Dec 1997 17:36:14   Hannes
// 
//    Rev 1.75   05 Dec 1997 17:44:28   Hannes
// diverse Verbesserungen
// 
//    Rev 1.74   19 Nov 1997 18:47:40   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.73   29 Oct 1997 19:00:08   Hannes
// Textbausteine
// 
//    Rev 1.72   24 Oct 1997 08:37:24   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.71   09 Oct 1997 17:29:56   Martin
// WriteNameList statt RemoveName ...
// 
//    Rev 1.70   29 Sep 1997 21:01:52   Martin
// SetObjectColor reagiert jetzt auf Updates
// 
//    Rev 1.69   08 Sep 1997 10:53:08   Gerhold
// Funktion OnButtonDown um rechte Maustaste in Formularen erweitert
// 
//    Rev 1.68   18 Aug 1997 18:02:30   Martin
// VTO Formular-faehig
// 
//    Rev 1.66   16 Jul 1997 11:56:44   Hannes
// 
//    Rev 1.65   08 Jul 1997 11:59:32   Hannes
// 
//    Rev 1.64   01 Jul 1997 14:38:56   Hannes
// 
//    Rev 1.63   25 Jun 1997 16:25:58   Hannes
// 
//    Rev 1.62   20 Jun 1997 17:16:32   Hannes
// GetMinMax ... Ohne Seitepruefung
// 
//    Rev 1.61   05 May 1997 11:37:50   Hannes
// Speicherfresser
// 
//    Rev 1.60   10 Apr 1997 11:45:56   Hannes
// 
//    Rev 1.59   07 Apr 1997 14:20:30   Hannes
// Seitenupdate verbessert
// 
//    Rev 1.58   13 Mar 1997 14:10:24   Hannes
// SetModifyFlag
// 
//    Rev 1.57   28 Feb 1997 14:45:36   Hannes
// GetLeftLowerAndAnzahlSeiten
// 
//    Rev 1.56   19 Feb 1997 12:20:22   Hannes
// 
//    Rev 1.55   27 Jan 1997 17:28:06   HANNES
// SetActive ... Paremter explicit beim OnLButtonDown geaendert
// 
//    Rev 1.54   03 Dec 1996 16:38:40   HANNES
// Invalidate / Rescale erst nach erfolgtem Load
// 
//    Rev 1.53   08 Nov 1996 13:33:50   HANNES
// Nicht dargestellte Objekte auch nicht Invalidieren
// 
//    Rev 1.52   25 Jul 1996 19:51:36   GERHOLD
// #pragma pack(1)
// 
//    Rev 1.51   03 Jul 1996 15:38:46   GERHOLD
// int FAR *  =>  DBINT FAR *,  BOOL FAR *  =>  DBBOOL FAR *
// 
//    Rev 1.50   21 Jun 1996 13:09:18   MARTIN
// ProjectCallBack korrigiert
// 
//    Rev 1.49   22 May 1996 12:06:00   MARTIN
// Invalidate in FrmShowObject
// 
//    Rev 1.48   18 May 1996 20:46:20   GERHOLD
// 
//    Rev 1.47   09 May 1996 19:11:00   HANNES
// SetExtraModify
// 
//    Rev 1.46   07 May 1996 18:12:18   HANNES
// 
//    Rev 1.45   07 May 1996 14:25:32   HANNES
// Invalidate auf 2. Seite
// 
//    Rev 1.44   24 Mar 1996 12:09:16   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.43   22 Mar 1996 12:18:14   HANNES
// Aenderungen Hannes
// 
//    Rev 1.42   02 Feb 1996 10:36:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.41   10 Jan 1996 18:22:06   MARTIN
// SetActivationProc, SetDeactivationProc
// 
//    Rev 1.40   10 Jan 1996 10:21:58   GERHOLD
// SetObjCallBack mit neuem Parameter fuer Texteingabe in Formularfelder die
// einen Knopf haben.
// 
//    Rev 1.39   20 Nov 1995 22:11:06   HANNES
// Focuswechsel -> Vergessen der letzten Eingabe fuer Liste
// 
//    Rev 1.38   20 Nov 1995 11:40:16   HANNES
// RealFocusIsChanging
// 
//    Rev 1.37   02 Nov 1995 10:36:38   GERHOLD
// SetFieldMode setzt in Formular-Eingabefeldern den FM_mode
// 
//    Rev 1.36   27 Aug 1995 13:04:36   HANNES
// DefFrmShort,DefFrmLong,DefFrmMoney
// 
//    Rev 1.35   24 Aug 1995 00:20:48   MARTIN
// 
//    Rev 1.34   10 Aug 1995 09:24:14   HANNES
// ConnectToChekbox, ActivateObject
// 
//    Rev 1.33   26 Jul 1995 14:17:08   HANNES
// ProjectCallBack
// 
//    Rev 1.32   24 Jul 1995 16:40:08   GERHOLD
// GetFieldRightUpper
// 
//    Rev 1.31   11 Jun 1995 19:17:52   MARTIN
// Laengenbegrenzung bei FrmObjects
// 
//    Rev 1.30   11 Jun 1995 10:10:22   MARTIN
// Mit der Maus manipulierbare Objekte fuer die Druckvorlagen eingebaut
// 
//    Rev 1.29   09 Jun 1995 00:21:32   MARTIN
// Richtiges Handling des Updates der Seiten
// 
//    Rev 1.28   20 May 1995 16:14:34   HANNES
// GetActiveElem
// 
//    Rev 1.27   27 Apr 1995 15:37:46   HANNES
// 
//    Rev 1.26   12 Apr 1995 12:26:26   HANNES
// 
//    Rev 1.25   05 Apr 1995 09:28:30   GERHOLD
// 
//    Rev 1.24   04 Apr 1995 16:51:08   HANNES
// 
//    Rev 1.23   04 Apr 1995 16:38:16   HANNES
// 
//    Rev 1.22   04 Apr 1995 15:20:16   HANNES
// 
//    Rev 1.21   04 Apr 1995 12:10:06   HANNES
//  
// 
//    Rev 1.20   31 Mar 1995 13:09:46   HANNES
//  
// 
//    Rev 1.19   30 Mar 1995 11:32:50   GERHOLD
// 
//    Rev 1.18   21 Mar 1995 16:20:54   HANNES
// 
//    Rev 1.17   20 Mar 1995 12:04:28   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.16   03 Mar 1995 12:45:46   HANNES
// 
//    Rev 1.15   20 Jan 1995 15:55:10   HANNES
// 
//    Rev 1.14   07 Dec 1994 15:24:42   GERHOLD
// auf C 8.00 umgestellt
// 
//    Rev 1.13   05 Dec 1994 17:42:46   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.12   20 Nov 1994 18:02:16   HANNES
// Combobuttom fuer Felder mit Callbackfunktion
// 
//    Rev 1.11   16 Nov 1994 12:52:38   HANNES
// Farben veraendern -> Invalidate
// 
//    Rev 1.10   11 Nov 1994 17:29:46   MARTIN
// DefFrmRectImage
// 
//    Rev 1.9   09 Nov 1994 13:15:34   MARTIN
// AvoidInvalidate
// 
//    Rev 1.8   31 Oct 1994 10:02:48   hannes
// SetOutColor
// 
//    Rev 1.7   17 Oct 1994 15:05:30   HANNES
// Reset && DrawContext != this -> Invalidieren
// 
//    Rev 1.6   11 Oct 1994 09:44:22   HANNES
// No change.
// 
//    Rev 1.5   06 Oct 1994 19:26:50   HANNES
// DefFrmTable
// 
//    Rev 1.4   20 Sep 1994 11:37:46   HANNES
// MultiProcFaehigkeit von FrmObjects, Trc_DefFilledCont
// 
//    Rev 1.3   05 Aug 1994 20:55:32   HANNES
// DefFrmTime
// 
//    Rev 1.2   05 Aug 1994 17:14:04   HANNES
// Kleine Umbauten in Verbindung mit ShowObjectList
// 
//    Rev 1.1   02 Aug 1994 18:39:44   HANNES
// PaintActiveCombo
// 
//    Rev 1.0   24 Jun 1994 19:30:46   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "globmem.h"
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "digitize.hpp"

#define MODULENUM     110
#include "winass.hpp"

#include "hash.hpp"
#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "multl.hpp"
#include "voronoi.hpp"
#include "frmobj.hpp"

#include "image.hpp"
#include "frmobj3.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "cubspl.hpp"
#include "cutedit.hpp"
#include "rotcent.hpp"
#include "entpt.hpp"
#include "winextra.hpp"
#include "frmtable.hpp"
#include "frmobj6.hpp"
#include "ddslist.hpp"

// #define DO_PROFILE
#ifdef DO_PROFILE
extern BOOL UseLines () ;
extern BOOL UseFields () ;
extern BOOL UsePatterns () ;
extern BOOL UseSetconn () ;
extern BOOL UseShow () ;

extern void IncAnzFields ();
extern void IncAnzLines ();
extern void IncAnzPatterns ();
extern void IncAnzShows ();
extern void IncAnzSetData ();
extern void IncAnzGetData ();
extern void IncAnzUpdate ();
extern void IncAnzSetConnection ();
extern void IncAnzGetKey ();

#endif

extern void FlushSyncList ();

BOOL Retired(mdiChild *c, void FAR *param, WORD mode)
  {
#undef MODULENUM
#define MODULENUM 1000
  char outtxt[64];
  wsprintf(outtxt,"Retired: %d",*(LPWORD(param)-1));
  DBWIN_ASSERT_TEXT(FALSE,outtxt);
#undef MODULENUM
#define MODULENUM 110
  return FALSE;
  }

void GetDocumentContext (PaintContext *pc,mdiChild *c)
  {
  int MapType;
  pc->GetContext (c->OutWnd(),0xFFFF,0xFFFF,DO_WORK);
  c->GetDocInfo (GETMAPTYPE,0,&MapType);
  if (MapType == MAPTYPE_GEOMETRIC) {
    POINT pt;
    c->GetDocInfo (GETWINDOWORG,0,&pt);
    pc->Map (c->OutScale(),pt.x,pt.y,c->OutXp(),c->OutYp());
    }
  else
    pc->LogicalTwips (c->OutXp(),c->OutYp(),c->OutScale());
  }

LPVOID FrmObjectList::operator new (size_t size)
  {
  LPVOID res = GetGlobMem (size);
  if (res == NULL) {
    DBWIN_ASSERT(FALSE);
    }
  return res;
  }

void FrmObjectList::operator delete (LPVOID object)
  {
  FreeGlobMem (object);
  }

///////////////////////////////////////////////////////////////////////
//  Hauptfunktion (fuer alle gleich): ShowObject 
///////////////////////////////////////////////////////////////////////
static LPFRMOBJ GetObject (LPSHOWOBJPAR par,mdiChild *c)
  {
  LPFRMOBJ FAR *addr =
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
  if (addr != NULL) return *addr;
  else              return NULL;
  }

FrmObjectList FAR *List (mdiChild *c)
  {
  return (FrmObjectList FAR *) (c->OutList());
  }

int uFrmShowObject_par::_Side(mdiChild *c)
  {
  if (par_Size >= sizeof(uFrmShowObject_par) - sizeof(nextObj) - 
                        sizeof(prevObj) - sizeof(_sdoPrint)) {
    DBINT FAR *lpSide = (DBINT FAR *) c->ReadlData (_sSide);
    return (lpSide != NULL) ? *lpSide : 0 ;
    }
  else
    return 0;
  }

BOOL uFrmShowObject_par::_doPrint(mdiChild *c)
  {
  if (par_Size >= sizeof(uFrmShowObject_par) - sizeof(prevObj) - sizeof(nextObj)) {
    DBBOOL FAR *lpdoPrint = (DBBOOL FAR *) c->ReadlData (_sdoPrint);
    return (lpdoPrint != NULL) ? *lpdoPrint : TRUE ;
    }
  else
    return TRUE;
  }

BOOL uFrmShowObject_par::CheckSort()
  {
  return (par_Size >= sizeof(uFrmShowObject_par) - sizeof(nextObj));
  }

extern void eAddToObjList (LPFRMOBJ h,DWORD ref);
BOOL uFrmShowObject (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseShow ()) return FALSE ;
#endif
  uFrmShowObject_par FAR *par = (uFrmShowObject_par FAR *) param ;
  LPFRMOBJ obj;

  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzShows ();
#endif
    // Das Objekt in die Liste geben
    obj = GetObject(par,c);
    if ((c->IsInListFunction ()) || ((c->CallerContext != NULL) && (c->CallerContext->IsInListFunction ())))
      eAddToObjList (obj,0L);
    else {
      DBINT Side = par->_Side(c);
      List(c)->Add (obj,Side,par->_doPrint(c),par,c);
      if ((mode & EM_CHANGETOTRUE) && (c->DrawContext()->LoadDone)) {
        if ((obj != NULL) && (Side == c->DrawContext()->GetOutData()->_ActSide)) {
          obj->Invalidate (c->actSide());
          LPRECT r = obj->GetLogRect (Side);
          if (r != NULL)
            obj->m.Rescale (r);
          }
        }
      }
    }

  if (mode & EM_UPDATE) {
    FrmObject FAR *obj = GetObject (par,c);
    if ((c->IsInListFunction ()) || ((c->CallerContext != NULL) && (c->CallerContext->IsInListFunction ())))
      eAddToObjList (obj,0L);
    else {
      // Das Objekt, wenn NULL, aus der Liste wieder streichen
      List(c)->Change (obj,par);
      if (LPSTR(&par->_sSide) - LPSTR(par) < int(par->par_Size)) {
        DBINT Side = par->_Side(c);
        FrmObject FAR *obj = GetObject (par,c);
        LPOBJDEF def = ((FrmObjectList FAR *) (c->OutList()))->Find (obj);
        if (def == NULL) def = ((FrmObjectList FAR *) (c->OutList()))->Find (par);
        if (def != NULL) {
          if ((def->ErsteSeite != Side) ||
              ((def->obj != NULL) && (!def->obj->rcLogRectInitialized))) {
            if (obj != NULL) {
              obj->Invalidate (c->actSide());
              BOOL PageChanged;
              if (def->ErsteSeite != Side)
                PageChanged = TRUE;
              else
                PageChanged = FALSE;
              def->ErsteSeite = Side ;
              obj->OnPageChange(Side);
              if (PageChanged ||
                  ((obj->Initialized) && (obj->InvalidOnUpdate())))
                obj->GetMinMax();
              obj->Invalidate (c->actSide());
              }
            else
              def->ErsteSeite = Side ;
            // Umschalten der Seite, wenn es sich um das aktive Objekt handelt
            if ((List(c)->act != NULL) && (List(c)->act->obj == obj)) {
              DWORD FAR *SideRef = (DWORD FAR *) c->DrawContext()->GetDocumentExtraData (DED_DOCSIDEPAR);
              if (SideRef != NULL)
                c->DrawContext()->WritelData (*SideRef,&Side,sizeof(Side),LPSTR(par)-sizeof(WORD));
              }
            }
          }
        }
      }
    }

  if ((mode & EM_FIXCONNECTION) && (!((c->IsInListFunction ()) || ((c->CallerContext != NULL) && (c->CallerContext->IsInListFunction ()))))) {
    c->SetConnection (par->ObjRec,par->ObjId,LPSTR(par) - sizeof(WORD));
    if (LPSTR(&par->_sSide) - LPSTR(par) < int(par->par_Size))
      c->SetlConnection (par->_sSide,LPSTR(par) - sizeof(WORD));
    }

  if ((mode & (EM_CLEAR | EM_RESET)) && 
          (!((c->IsInListFunction ()) || ((c->CallerContext != NULL) && (c->CallerContext->IsInListFunction ()))))) {
    if (mode & EM_CLEAR) {
      FrmObject FAR *obj;
      if ((par->ObjRec & 0xEF00) != 0xEF00)
        obj = GetObject (par,c);
      else
        obj = NULL;
      if (obj != NULL)
        obj->Invalidate (c->actSide());
      }
    c->ClearConnection (par->ObjRec,par->ObjId,LPSTR(par) - sizeof(WORD));
    if (LPSTR(&par->_sSide) - LPSTR(par) < int(par->par_Size))
      c->ClearlConnection (par->_sSide,LPSTR(par) - sizeof(WORD));
    List(c)->Remove (par);
    }

  return FALSE;
  }

//
//    Listenverwaltung: FrmObjectList
//////////////////////////////////////////////////////////////////////////
hash FAR *parToNode ;
void FrmObjectList::Add (FrmObject FAR *obj,int Side,BOOL doPrint,LPSHOWOBJPAR par,mdiChild *caller)
  {
  BOOL oldActive = BlockIsActive ;
  BlockIsActive = FALSE ;

  if (parToNode == NULL) parToNode = new hash (255,VOIDKEY);
  // Durchsuchen, ob ID schon vergeben
  ///////////////////////////////////////
  LPOBJDEF node;
  node = LPOBJDEF (
          GetGlobMem (sizeof(*node))
                  );
  node->obj = obj;
  node->par = par;
  node->ErsteSeite = Side;
  if (node->obj != NULL)
    node->obj->SetzeAnzahlSeiten (1);
  node->doPrint = doPrint ;
  node->objdoc = c;

  if (obj != NULL) {
    obj->SetNode (node);
    obj->OnPageChange (Side);
    int MapType;
    c->GetDocInfo (GETMAPTYPE,0,&MapType);
    POINT pt;
    pt.x = pt.y = 0;
    obj->OnMapChange (caller->OutScale(),MapType,caller->OutXp(),caller->OutYp(),pt.x,pt.y);
    if (obj->Initialized) {
      obj->GetMinMax();
      }
    if ((c->DrawContext()->LoadDone) && 
         (c->GetDocumentExtraData (DED_AVOIDINVALIDATE) == NULL))
      obj->Invalidate (obj->m.ActSide());
    }

  // Herstellen der Zyklischen Liste
  if ((par == NULL) || (!par->CheckSort()) || (head == NULL)) {
    if (head != NULL)
      head->PrevObjDef = node;
    else
      head = node ;

    if (tail != NULL)
      tail->NextObjDef = node ;
    else
      tail = node ;

    node->NextObjDef = head;
    node->PrevObjDef = tail;

    tail = node;

    if ((act == NULL) && (GetFocus () == c->OutWnd()) && 
              (obj != NULL) && (obj->IsToActivate()) && 
              (Side == c->actSide())) {
      act = node ;
      obj->SetActiveIf (Side,FALSE);
      }
    }
  else {
    // Reihenfolge muss eingehalten werden
    DBWIN_ASSERT (head != NULL);
    WORD testID;
    LPFRMOBJ FAR *testObj;
    if (par->doPrev()) testID = HIWORD(par->prevObj), testObj = (LPFRMOBJ FAR *) caller->ReadlData (par->prevObj);
    else               testID = HIWORD(par->nextObj), testObj = (LPFRMOBJ FAR *) caller->ReadlData (par->nextObj);
    BOOL nimmNaechstes = FALSE ;
    for ( LPOBJDEF h = head ; ; h = h->NextObjDef) {
      if ((h->par != NULL) &&
          (((testObj != NULL) && (h->obj == *testObj)) ||
           (nimmNaechstes) ||
           ((testObj == NULL) && (h->par->ObjId == testID)))) {
        // hinter diesem nun einfuegen
        ///////////////////////////////
        if (par->doPrev ()) {
          node->NextObjDef = h->NextObjDef ;
          h->NextObjDef->PrevObjDef = node;
          node->PrevObjDef = h ;
          h->NextObjDef = node ;
          if (tail == h)
            tail = node ;
          break ;
          }
        else {
          node->PrevObjDef = h->PrevObjDef;
          node->PrevObjDef->NextObjDef = node;
          node->NextObjDef = h;
          h->PrevObjDef = node;
          if (head == h) 
            head = node ;
          break ;
          }
        }
      if (h->NextObjDef == head) {
        // Nicht gefunden
        // DBWIN_ASSERT(FALSE);
        nimmNaechstes = TRUE;
        // break ;
        }
      }
    }

  if ((obj != NULL) && (obj->IsToActivate()))
    lastactive = node;

  parToNode->SetDatav (&par,&node,sizeof(node),sizeof(par));
  BlockIsActive = oldActive;
  }

void FrmObjectList::Change (FrmObject FAR *obj,LPSHOWOBJPAR par)
  {
#ifdef UEBERLEGT
  for ( LPOBJDEF node = head ; node != NULL ; node = node->NextObjDef) {
    if ((node->par != NULL) &&
        (node->par == par)) {
      node->obj = obj;
      if (obj != NULL) {
        obj->SetNode (node);
        obj->OnPageChange (node->ErsteSeite);
        if (obj->Initialized) {
          obj->GetMinMax();
          if (obj->InvalidOnUpdate())
            obj->Invalidate(c->actSide());
          }
        }
      break ;
      }
    if (node->NextObjDef == head) {
      DBWIN_ASSERT(FALSE);
      break ;
      }
    }
#else
  LPOBJDEF FAR *lpnode = (LPOBJDEF FAR *) parToNode->GetDatav (&par,sizeof(par));
  DBWIN_ASSERT (lpnode != NULL);
  (*lpnode)->obj = obj;
  if (obj != NULL) {
    obj->SetNode (*lpnode);
    obj->OnPageChange ((*lpnode)->ErsteSeite);
    if ((obj->Initialized) && (obj->InvalidOnUpdate())) {
      obj->GetMinMax();
      obj->Invalidate(c->actSide());
      }
    }
#endif
  }

void FrmObjectList::Change (FrmObject FAR *oldobj,FrmObject FAR *newobj)
  {
  for ( LPOBJDEF node = head ; node != NULL ; node = node->NextObjDef) {
    if (node->obj == oldobj) {
      node->obj = newobj;
      break ;
      }
    if (node->NextObjDef == head) {
      break ;
      }
    }
  }

void FrmObjectList::Remove (LPSHOWOBJPAR par)
  {
  LPOBJDEF FAR *lpnode = (LPOBJDEF FAR *) parToNode->GetDatav (&par,sizeof(par));
  DBWIN_ASSERT (lpnode != NULL);
  if ((*lpnode)->obj != NULL)
    (*lpnode)->obj->SetNode (NULL);
  if ((*lpnode)->NextObjDef == *lpnode) {
    // Das war dann wohl das letzte
    head = tail = NULL ;
    }
  else {
    (*lpnode)->NextObjDef->PrevObjDef = (*lpnode)->PrevObjDef ;
    (*lpnode)->PrevObjDef->NextObjDef = (*lpnode)->NextObjDef ;
    if (head == *lpnode)
      head = (*lpnode)->NextObjDef ;
    if (tail == *lpnode)
      tail = (*lpnode)->PrevObjDef ;
    }
  if (act == *lpnode) {
    act = NULL ;
    if ((GetFocus () == c->OutWnd()) && (c->OutWnd() != NULL) && (!c->closed)) {
        OnSetFocus (FALSE);
      }
    }
  FreeGlobMem (*lpnode);
  parToNode->DelDatav (&par,sizeof(par));
  }

void FrmObjectList::Remove (FrmObject FAR *obj)
  {
  for ( LPOBJDEF node = head ; node != NULL ; node = node->NextObjDef) {
    if (node->obj == obj) {
      if (node->NextObjDef == node) {
        // Das war dann wohl das letzte
        head = tail = NULL ;
        }
      else {
        node->NextObjDef->PrevObjDef = node->PrevObjDef ;
        node->PrevObjDef->NextObjDef = node->NextObjDef ;
        if (head == node)
          head = node->NextObjDef ;
        if (tail == node)
          tail = node->PrevObjDef ;
        }
      if (act == node) {
        act = NULL ;
#ifdef SDOC
        if ((c->IsSmallDoc()) && (!c->IsListDoc ()))
          ((FrmObjectList FAR *) (((sFormDoc *) c)->parent->ObjectList))->act = NULL ;
#endif
        if (GetFocus () == c->OutWnd()) {
#ifdef SDOC
          if ((c->IsSmallDoc()) && (!c->IsListDoc ()))
            ((FrmObjectList FAR *) (((sFormDoc *) c)->parent->ObjectList))->OnSetFocus(TRUE);
          else
#endif
            OnSetFocus (TRUE);
          }
        }
      FreeGlobMem (node);
      break ;
      }
    if (node->NextObjDef == head) {
      DBWIN_ASSERT(FALSE);
      break ;
      }
    }
  if (obj != NULL)
    obj->SetNode (NULL);
  }

LPOBJDEF FrmObjectList::Find (FrmObject FAR *obj)
  {
#ifdef ALTEVERSION
  for (LPOBJDEF node = head ; node != NULL ; node = Next(node)) {
    if (node->obj == obj) break ;
    if (Next(node) == head) {
      node = NULL ;
      break ;
      }
    }
#endif
  return (obj != NULL) ? obj->GetNode() : NULL;
  }

LPOBJDEF FrmObjectList::Find (LPSHOWOBJPAR par)
  {
  for (LPOBJDEF node = head ; node != NULL ; node = node->NextObjDef) {
    if ((node->par != NULL) &&
        (node->par == par)) break ;
    if (node->NextObjDef == head) {
      node = NULL ;
      break ;
      }
    }
  return node;
  }

void FrmObjectList::Select (FrmObject FAR *obj, DWORD SelColor)
  {
  for ( LPOBJDEF node = head ; ; node = node->NextObjDef) {
    if ((node->par != NULL) &&
        (node->obj == obj)) {
      node->selected = TRUE;
      node->SelColor = SelColor;
      if ((node->obj != NULL) && node->obj->Initialized) {
        PaintContext pc;
        GetDocumentContext (&pc,c);
        c->DrawContext()->GetOutData()->_SelColor = SelColor;
        node->obj->PaintSel(&pc,c->DrawContext()->GetOutData()->_ActSide);
        }
      if (node != tail) {   // zurueckreihen ans Ende der Liste
        if (node == head) {
          head = node->NextObjDef;
          tail = node;
          }
        else {
          node->PrevObjDef->NextObjDef = node->NextObjDef;
          node->NextObjDef->PrevObjDef = node->PrevObjDef;
          node->NextObjDef = head;
          node->PrevObjDef = tail;
          tail->NextObjDef = node;
          head->PrevObjDef = node;
          tail = node;
          }
        }
      break ;
      }
    if (node->NextObjDef == head) {
      DBWIN_ASSERT(FALSE);
      break;
      }
    }
  }


LPFRMOBJ TailObj ;
void FrmObjectList::BringToTail (FrmObject FAR *obj)
  {
#ifdef UEBERLEGT
  for ( LPOBJDEF node = head ; ; node = node->NextObjDef) {
    if ((node->par != NULL) &&
        (node->obj == obj)) {
      if (node != tail) {   // zurueckreihen ans Ende der Liste
        if (node == head) {
          head = node->NextObjDef;
          tail = node;
          }
        else {
          node->PrevObjDef->NextObjDef = node->NextObjDef;
          node->NextObjDef->PrevObjDef = node->PrevObjDef;
          node->NextObjDef = head;
          node->PrevObjDef = tail;
          tail->NextObjDef = node;
          head->PrevObjDef = node;
          tail = node;
          }
        }
      break ;
      }
    if (node->NextObjDef == head) {
      DBWIN_ASSERT(FALSE);
      break;
      }
    }
#else
  TailObj = obj;
#endif
  }

void FrmObjectList::Deselect (FrmObject FAR *obj)
  {
  for ( LPOBJDEF node = head ; ; node = node->NextObjDef) {
    if ((node->par != NULL) &&
        (node->obj == obj)) {
      node->selected = FALSE;
      if ((node->obj != NULL) && node->obj->Initialized) {
        PaintContext pc;
        GetDocumentContext (&pc,c);
        node->obj->Paint(&pc,c->DrawContext()->GetOutData()->_ActSide);
        }
      if (node != tail) {   // zurueckreihen ans Ende der Liste
        if (node == head) {
          head = node->NextObjDef;
          tail = node;
          }
        else {
          node->PrevObjDef->NextObjDef = node->NextObjDef;
          node->NextObjDef->PrevObjDef = node->PrevObjDef;
          node->NextObjDef = head;
          node->PrevObjDef = tail;
          tail->NextObjDef = node;
          head->PrevObjDef = node;
          tail = node;
          }
        }
      break ;
      }
    if (node->NextObjDef == head) {
      DBWIN_ASSERT(FALSE);
      break;
      }
    }
  }

// Bearbeiten der Benutzerinteraktion
/////////////////////////////////////////
void FrmObjectList::NextActive ()
  {
  if (act != NULL) {
    LPOBJDEF hlp = Next(act);
    for ( ; ; ) {
      // if ((hlp->obj != NULL) && (hlp->obj->Initialized) && (CheckSide(hlp)) && (hlp->obj->IsToActivate())) {
      if ((hlp->obj != NULL) && (hlp->obj->Initialized) && (hlp->obj->IsToActivate())) {
        act = hlp ;
        break ;
        }
      if (hlp == act) break ;
      hlp = Next(hlp) ;
      }
    }
  }

void FrmObjectList::PrevActive ()
  {
  if (act != NULL) {
    LPOBJDEF hlp = Prev(act);
    for ( ; ; ) {
      // if ((hlp->obj != NULL) && (hlp->obj->Initialized) && (CheckSide(hlp)) && (hlp->obj->IsToActivate())) {
      if ((hlp->obj != NULL) && (hlp->obj->Initialized) && (hlp->obj->IsToActivate())) {
        act = hlp ;
        break ;
        }
      if (hlp == act) break ;
      hlp = Prev(hlp) ;
      }
    }
  }

void FrmObjectList::FirstActive ()
  {
  if (act == NULL) act = head;
  if (act != NULL) {
    if ((act->obj == NULL) || (!act->obj->Initialized) || (!CheckSide(act)) ||
            (!(act->obj->IsToActivate ())))
      NextActive ();
    }
  if ((act != NULL) && ((act->obj == NULL) || (!act->obj->Initialized) || (!act->obj->IsToActivate()) || (!CheckSide (act))))
    act = NULL;
  }

LPOBJDEF FrmObjectList::GetFirstActive ()
  {
  LPOBJDEF h = head;
  if (h != NULL) {
    for ( ; ((h->obj == NULL) || (!h->obj->Initialized) || (!CheckSide(h)) ||
            (!(h->obj->IsToActivate ()))) ; h = Next(h) ) {
      if (h == tail) break ;
      }
    }
  if ((h != NULL) && ((h->obj == NULL) || (!h->obj->Initialized) || (!h->obj->IsToActivate()) || (!CheckSide (h))))
    h = NULL;
  return h ;
  }

LPOBJDEF FrmObjectList::GetLastActive ()
  {
  LPOBJDEF h = tail;
  if (h != NULL) {
    for ( ; ((h->obj == NULL) || (!h->obj->Initialized) || (!CheckSide(h)) ||
            (!(h->obj->IsToActivate ()))) ; h = Prev(h) ) {
      if (h == head) break ;
      }
    }
  if ((h != NULL) && ((h->obj == NULL) || (h->obj->Initialized) || (!h->obj->IsToActivate()) || (!CheckSide (h))))
    h = NULL;
  return h;
  }

BOOL FrmObjectList::OnSetFocus (BOOL bexplicit)
  {
  BOOL res;
  BOOL oldActive = BlockIsActive ;
  BlockIsActive = FALSE ;
  FirstActive ();
  if (act != NULL) {
    if ((act->obj != NULL) && (act->obj->IsToActivate ())) {
      act->obj->SetActiveIf (c->DrawContext()->GetOutData()->_ActSide,bexplicit);
      res = TRUE ;
      }
    else
      res = FALSE ;
    }
  BlockIsActive = oldActive ;
  return res;
  }

void FrmObjectList::SetActiveExplicit (FrmObject FAR *obj,BOOL doExplicit)
  {
  BOOL oldActive = BlockIsActive ;
  BlockIsActive = FALSE ;

  LPOBJDEF h = Find (obj);
  if (h != NULL) {
    if ((act != h) || (!obj->IsActive)) {
      DeactivateNode ();
      act = h;
      h->obj->SetActiveIf (c->DrawContext()->GetOutData()->_ActSide,doExplicit);
      }
    }
  BlockIsActive = oldActive ;
  }

BOOL FrmObjectList::OnSetCursor ()
  {
  int res = SETCURSOR_NONE ;
  int x,y;
  if (head != NULL) {
    DWORD lP = GetMessagePos();
    POINT pt;
    pt.x = LOWORD(lP);
    pt.y = HIWORD(lP);
    ScreenToClient (c->OutWnd(),&pt);
    GetLogKoords (MAKELONG(pt.x,pt.y),&x,&y);
    LPOBJDEF hlp = head ;
    FrmObject FAR *defobj = NULL;
    if ((act != NULL) && (act->obj != NULL))
      res = act->obj->OnSetCursor(x,y,FALSE);
    if (res != SETCURSOR_DONE) {
      for ( ; ; ) {
        if ((hlp->obj != NULL) && (CheckSide (hlp))
              && ((res = hlp->obj->OnSetCursor(x,y,FALSE)) == SETCURSOR_DONE)) {
          defobj = NULL;
          break ;
          }
        if ((res == SETCURSOR_WANTDEF) && (defobj == NULL)
#ifdef SDOC
            && (!c->IsSmallDoc())
#endif
            )
          defobj = hlp->obj;
        if (hlp->NextObjDef == head) break ;
        hlp = hlp->NextObjDef ;
        }
      if (defobj != NULL)
        res = defobj->OnSetCursor (x,y,TRUE);
      }
    }
  return (res != 0);
  }

void FrmObjectList::DeactivateNode ()
  {
  if (act == lastactive) {
    c->Store ();
    }
  if ((act != NULL) && (act->obj != NULL))
    act->obj->SetInActiveIf (c->DrawContext()->GetOutData()->_ActSide);
  }

BOOL FrmObjectList::OnKillFocus ()
  {
  BOOL res;
  BOOL oldActive = BlockIsActive ;
  BlockIsActive = FALSE ;
  if (act != NULL) {
    if ((act->obj != NULL) && (act->obj->IsToActivate ())) {
      DeactivateNode ();
      act->obj->Invalidate (c->actSide());
      res = TRUE ;
      }
    else
      res = FALSE ;
    }
  BlockIsActive = oldActive ;
  return res;
  }

BOOL FrmObjectList::CheckDirKey (WORD wP)
  {
  int DirId;
  switch (wP) {
    case VK_UP :
      DirId = DIRID_UP;
      break;
    case VK_RIGHT :
      DirId = DIRID_RIGHT;
      break;
    case VK_LEFT :
      DirId = DIRID_LEFT;
      break;
    case VK_DOWN :
      DirId = DIRID_DOWN;
      break;
    default :
      return FALSE ;
    }
  FrmObject FAR *obj;
  LPOBJDEF node;
  if ((act != NULL) && (act->obj != NULL) &&
      ((obj = act->obj->GetNBar (DirId)) != NULL) && 
        (obj->IsToActivate()) && ((node = Find(obj)) != NULL)) {
    BOOL oldActive = BlockIsActive ;
    BlockIsActive = FALSE ;
    DeactivateNode ();
    act = node;
    obj->SetActiveIf (c->DrawContext()->GetOutData()->_ActSide,TRUE);
    BlockIsActive = oldActive ;
    return TRUE ;
    }
  return FALSE ;
  }

extern LPSTR ExtChildClass;
BOOL CheckExternTool (mdiChild *c)
  {
  char classname[64];
  GetClassName (c->OutWnd(),classname,sizeof(classname));
  if (lstrcmp (classname,ExtChildClass) == 0) {

    HILOCHUNK hilo;
    MAKECHUNKsc (hilo, 0, DDSLIST_TABPRESSED);

    SendMessage (GetParent (c->OutWnd()),WM_COMMAND,0,HILOCHUNKPARAM (hilo));
/*
    SendMessage (GetParent (c->OutWnd()),WM_COMMAND,0,MAKELONG(0,DDSLIST_TABPRESSED));
*/
    if (GetFocus () == c->OutWnd()) return FALSE ;  // Nix weitergemacht, einziges Element
    return TRUE ;
    }
  else
    return FALSE ;
  }

extern void RealFocusIsChanging (DWORD old,DWORD n);
BOOL FrmObjectList::OnKeyDown (WORD wP)
  {
  DenyBusyCursorOnce();   // hoffentlich ist das nicht zuviel !
  BOOL res = CheckDirKey (wP);
  if ((!res) && (act != NULL)) {
    if (act->obj != NULL) {
      if (act->obj->IsNextKey (wP)) {
        DWORD o = MAKELONG(act->par->ObjRec,act->par->ObjId) ;
        DeactivateNode ();
        NextActive ();

        if ((act != NULL) && (act->ErsteSeite != c->actSide()))
          c->DrawContext()->ChangeDocSide (act->ErsteSeite - c->actSide());

        DWORD n = MAKELONG(act->par->ObjRec,act->par->ObjId) ;
        if ((act != GetFirstActive()) || (!CheckExternTool(c)))
          act->obj->SetActiveIf (c->DrawContext()->GetOutData()->_ActSide,TRUE);
        RealFocusIsChanging (o,n);
        res = TRUE ;
        }
      else if (act->obj->IsPrevKey (wP)) {
        DWORD o = MAKELONG(act->par->ObjRec,act->par->ObjId) ;
        DeactivateNode ();
        PrevActive ();
        if ((act != NULL) && (act->ErsteSeite != c->actSide()))
          c->DrawContext()->ChangeDocSide (act->ErsteSeite - c->actSide());

        DWORD n = MAKELONG(act->par->ObjRec,act->par->ObjId) ;
        if ((act != GetLastActive()) || (!CheckExternTool(c)))
          act->obj->SetActiveIf (c->DrawContext()->GetOutData()->_ActSide,TRUE);
        RealFocusIsChanging (o,n);
        res = TRUE ;
        }
      else
        res = act->obj->OnKeyDown (wP,c->DrawContext()->GetOutData()->_ActSide);
      }
    }
  if ((!res) && (wP == VK_TAB))
    res = CheckExternTool (c);
  return res;
  }

BOOL FrmObjectList::OnChar (WORD wP)
  {
  DenyBusyCursorOnce();   // hoffentlich ist das nicht zuviel !
  BOOL res = FALSE ;
  if (act != NULL) {
    if ((act->obj != NULL) && (!(act->obj->IsCharToSkip (wP))))
      res = act->obj->OnChar (wP,c->DrawContext()->GetOutData()->_ActSide);
    }
  return res;
  }

BOOL FrmObjectList::OnKeyUp (WORD wP)
  {
  BOOL res = FALSE ;
  if (act != NULL) {
    if (act->obj != NULL)
      res = act->obj->OnKeyUp (wP,c->DrawContext()->GetOutData()->_ActSide);
    }
  return res;
  }

void FrmObjectList::GetLogKoords (LPARAM lP,int *x,int *y)
  {
  PaintContext pc;
  GetDocumentContext (&pc,c);
  POINT pt;
  pt.x = LOWORD(lP);  pt.y = HIWORD(lP);
  DPtoLP (pc.hDC,&pt,1);
  *x = pt.x ;         *y = pt.y ;
  }

BOOL FrmObjectList::OnButtonDown (WPARAM wP, LPARAM lP,UINT msg)
  {
  int x,y;
  BOOL res = FALSE ;
  BOOL bMsgDone;

  LPFRMOBJ  tmpobj = NULL;

  // 1. Untersuchung, ob nicht in einem Feld
  ////////////////////////////////////////////////////
  WORD modify = 0;
  GetLogKoords (lP,&x,&y);
  if (head != NULL) {
    POINT pt;
    pt.x = x ; pt.y = y ;
    for (LPOBJDEF hx = head ; ; ) {
      LPRECT logr ;
      if ((hx->obj != NULL) && (hx->obj->IsField()) &&
            (hx->obj->IsToActivate ()))
        logr = hx->obj->GetLogRect (c->actSide());
      else
        logr = NULL ;
      if ((logr != NULL) && (PtInRect (logr,pt)))
        modify = 0x8000 ;
      if (hx->NextObjDef == head)
        break ;
      hx = hx->NextObjDef ;
      }
    }

  if (head != NULL) {
    bMsgDone = FALSE;
    if ((act != NULL) && (act->obj != NULL)) {
      if (msg == WM_LBUTTONDOWN)
        bMsgDone = act->obj->OnLButtonDown (wP | modify,x,y,c->actSide());
      else
        bMsgDone = act->obj->OnRButtonDown (c->OutWnd(), wP | modify,x,y,c->actSide(), TRUE);

      res = bMsgDone;
      tmpobj = act->obj;
      }

    //---------------------
    // noch nix gefunden
    //---------------------
    if (!bMsgDone) {
      LPOBJDEF hlp = head ;
      for ( ; ; ) {
        if ((hlp->obj != NULL) && (CheckSide (hlp))) {

          //------------------------------------------------------------
          // LBUTTONDOWN geht nur durch wenn das Objekt aktivierbar ist
          //------------------------------------------------------------
          bMsgDone = FALSE;
          if (msg == WM_LBUTTONDOWN) {
            if (hlp->obj->IsToActivate ())
              bMsgDone = hlp->obj->OnLButtonDown (wP | modify,x,y,c->actSide());
            }
          else
            bMsgDone = hlp->obj->OnRButtonDown (c->OutWnd(), wP | modify,x,y,c->actSide(), FALSE);

          //------------------
          // endlich gefunden
          //------------------
          if (bMsgDone) {
            if (act != hlp) {
              //------------------------------------------------------------
              // der Focus wird nur bei linker Maus geaendert oder wenn das
              // Objekt der Begierde auch aktivierbar ist
              //------------------------------------------------------------
              if ((msg == WM_LBUTTONDOWN) || hlp->obj->IsToActivate ()) {
                DWORD o = (act != NULL) ? MAKELONG(act->par->ObjRec,act->par->ObjId) : 0L ;
                if ((act != NULL) && (act->obj != NULL))
                  DeactivateNode ();
                act = hlp ;
                DWORD n = MAKELONG(act->par->ObjRec,act->par->ObjId) ;
                RealFocusIsChanging (o,n);

                act->obj->SetActiveIf (c->actSide(),FALSE);
                tmpobj = act->obj;
                }
              else
                tmpobj = hlp->obj;
//              if ((msg == WM_RBUTTONDOWN) && bMsgDone)
//                ContextObject = (act != hlp) ? hlp->obj : act->obj;  // globale Variable
              //---------------------------------------------------
              // jetzt kannst du endlich Dein Kontext-Menu oeffnen
              //---------------------------------------------------
              if (msg == WM_RBUTTONDOWN)
                bMsgDone = tmpobj->OnRButtonDown (c->OutWnd(), wP | modify,x,y,c->actSide(), TRUE);
              }

            res = TRUE ;
            break ;
            }
          }
        if (hlp->NextObjDef == head)
          break ;
        hlp = hlp->NextObjDef ;
        }
      }

    if ((msg == WM_RBUTTONDOWN) && bMsgDone && (tmpobj != NULL))
      ContextObject = tmpobj;  // globale Variable

    if ((msg == WM_RBUTTONDOWN) && !bMsgDone) {
      
      }
    }

  return res;
  }

BOOL FrmObjectList::OnLButtonDblClk (WPARAM wP,LPARAM lP)
  {
  int x,y;
  BOOL res = FALSE ;
  if (act != NULL) {
    GetLogKoords (lP,&x,&y);
    if (act->obj != NULL)
      res = act->obj->OnLButtonDblClk (wP,x,y,c->actSide());
    }
  return res;
  }

BOOL FrmObjectList::OnMouseMove (WPARAM wP,LPARAM lP)
  {
  int x,y;
  BOOL res = FALSE ;
  if (act != NULL) {
    GetLogKoords (lP,&x,&y);
    if (act->obj != NULL)
      res = act->obj->OnMouseMove (wP,x,y,c->actSide());
    }
  return res;
  }

BOOL FrmObjectList::OnLButtonUp (WPARAM wP,LPARAM lP)
  {
  int x,y;
  BOOL res = FALSE ;
  if (act != NULL) {
    GetLogKoords (lP,&x,&y);
    if (act->obj != NULL)
      res = act->obj->OnLButtonUp (wP,x,y,c->actSide());
    }
  return res;
  }

BOOL FrmObjectList::OnValRead (double val)
  {
  BOOL res = FALSE ;
  if (act != NULL) {
    if (act->obj != NULL) {
      res = act->obj->OnValRead (val);
      DeactivateNode ();
      NextActive ();
      act->obj->SetActiveIf (c->actSide(),TRUE);
      }
    }
  return res;
  }

void FrmObjectList::OnDigitized (UINT msg,GLOBALHANDLE hGmem)
  {
  if ((act != NULL) && (act->obj != NULL) && (act->obj->IsInputObj())) {
    ((InputObj FAR *) act->obj)->OnDigitized (msg,hGmem);
    }
  }

void FrmObjectList::OnMapChange ()
  {
  if (c->GetOutData()->_MyHandle) {
    ResetWindowHandles (c->GetOutData()->_MyHandle);
    int MapType;
    c->GetDocInfo (GETMAPTYPE,0,&MapType);
    POINT pt;
    pt.x = pt.y = 0;
    FlushSyncList ();
    if (MapType == MAPTYPE_GEOMETRIC)
      c->GetDocInfo (GETWINDOWORG,0,&pt);

    // Diese Information an alle Objekte weiterleiten
    for ( LPOBJDEF hlp = head ; hlp != NULL ; ) {
      if (hlp->obj != NULL) hlp->obj->OnMapChange (c->OutScale(),MapType,c->OutXp(),c->OutYp(),pt.x,pt.y);
      if (hlp->NextObjDef == head)
        break ;
      hlp = hlp->NextObjDef ;
      }
    }
  }

BOOL FrmObjectList::OnPalChange (HWND hWnd, BOOL ontop)
  {
  BOOL retval = FALSE;
  LPPALINFO pi = (LPPALINFO)c->GetDocumentExtraData(DED_PALETTEINFO);
  if (pi != NULL) {
    retval = TRUE;
    HDC hDC = GetDC (hWnd);
    HPALETTE hOldPal = SelectPalette (hDC, pi->actpal, !ontop);
    UINT changed = RealizePalette (hDC);
    if (hOldPal) {
      SelectPalette (hDC, hOldPal, TRUE);
     RealizePalette(hDC);
      }

//    if (!ontop)
//      UpdateColors (hDC);

    ReleaseDC (hWnd, hDC);

//    if (ontop && retval)
    if (changed > 0)
      InvalidateRect(hWnd, NULL, FALSE);
    }

  return retval;
  }

void FrmObjectList::StartExternPaint ()
  {
  for ( LPOBJDEF hlp = head ; hlp != NULL ; ) {
    if (hlp->obj != NULL) hlp->obj->StartExternPaint ();
    if (hlp->NextObjDef == head)
      break ;
    hlp = hlp->NextObjDef ;
    }
  }

void FrmObjectList::EndExternPaint ()
  {
  for ( LPOBJDEF hlp = head ; hlp != NULL ; ) {
    if (hlp->obj != NULL) hlp->obj->EndExternPaint ();
    if (hlp->NextObjDef == head)
      break ;
    hlp = hlp->NextObjDef ;
    }
  }

void FrmObjectList::NewPrinter ()
  {
  for ( LPOBJDEF hlp = head ; hlp != NULL ; ) {
    if (hlp->obj != NULL) hlp->obj->NewPrinter ();
    if (hlp->NextObjDef == head)
      break ;
    hlp = hlp->NextObjDef ;
    }
  }

void FrmObjectList::OnRecChange (WORD rType)
  {
  for ( LPOBJDEF hlp = head ; hlp != NULL ; ) {
    if (hlp->obj != NULL) hlp->obj->OnRecChange (rType);
    if (hlp->NextObjDef == head)
      break ;
    hlp = hlp->NextObjDef ;
    }
  }

// Zeichnen
////////////////////
BOOL FrmObjectList::CheckSide (LPOBJDEF lpo)
  {
  return ((lpo->obj != NULL) && (lpo->ErsteSeite <= c->actSide()) && (lpo->ErsteSeite + lpo->obj->AnzahlSeiten() > c->actSide())) ;
  }

BOOL FrmObjectList::CheckForPaint (LPOBJDEF lpo,PaintContext *pc)
  {
  if (CheckSide(lpo)) {
    if ((pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)) return (lpo->par == NULL) || (lpo->doPrint);
    else                                                   return TRUE;
    }
  return FALSE ;
  }

void FrmObjectList::Paint (PaintContext *pc)
  {
  if (head != NULL) {
    LPOBJDEF hlp = head ;
    BOOL TailObjFound = FALSE ;
    for ( ; ; ) {
      if ((hlp->obj != NULL) && (CheckForPaint (hlp,pc)) &&
                    ((hlp->obj->IsToPaint (c->actSide(),pc))
                    )) {
        if (hlp->selected) {
          c->DrawContext()->GetOutData()->_SelColor = hlp->SelColor;
          hlp->obj->PaintSel (pc,c->DrawContext()->GetOutData()->_ActSide);
          }
        else {
          if (hlp->obj != TailObj)
            hlp->obj->Paint (pc,c->DrawContext()->GetOutData()->_ActSide);
          else
            TailObjFound = TRUE ;
          }
        }
      if (hlp->NextObjDef == head) break ;
      hlp = hlp->NextObjDef;
      }
    if (TailObjFound) TailObj->Paint(pc,c->DrawContext()->GetOutData()->_ActSide);
    PaintActiveCombo (pc->hDC,c->OutWnd(),((pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)),c->DrawContext()->GetOutData()->_ActSide);
    }
  }

void FrmObjectList::Reformat (BOOL forPrinter)
  {
  if (head != NULL) {
    FlushSyncList ();
    LPOBJDEF hlp = head ;
    for ( ; ; ) {
      if (hlp->obj != NULL) hlp->obj->Reformat (forPrinter);
      if (hlp->NextObjDef == head) break ;
      hlp = hlp->NextObjDef;
      }
    }
  }

void FrmObjectList::GetMinMax (LPRECT r,BOOL forScreen)
  {
  SetRectEmpty (r);
  if (head != NULL) {
    LPOBJDEF hlp = head ;
    for ( ; ; ) {
#ifdef UEBERLEGT
      if ((hlp->obj != NULL) && ((CheckSide(hlp)) || (!forScreen)) &&
          ((forScreen) || ((hlp->par == NULL) || (hlp->doPrint))))
        hlp->obj->GetUnionRect (c->actSide(),r);
#else
      if ((hlp->obj != NULL) &&
          ((forScreen) || ((hlp->par == NULL) || (hlp->doPrint))))
        hlp->obj->GetUnionRect (c->actSide(),r);
#endif
      if (hlp->NextObjDef == head) break ;
      hlp = hlp->NextObjDef;
      }
    }
  }

// Destruktor
////////////////
FrmObjectList::~FrmObjectList ()
  {
  if (head != NULL) {
    LPOBJDEF hlp = head ;
    for ( ; ; ) {
      LPOBJDEF Next = hlp->NextObjDef ;
      FreeGlobMem (hlp);
      if (Next == head) break ;
      hlp = Next ;
      }
    }
  }

// Interpreter fuer die Funktionen zum Handling der Objekt - Definierung
//////////////////////////////////////////////////////////////////////////
inline void WriteObjectToPar (FrmObject FAR *obj,LPVOID param,mdiChild *c)
  {
  ((LPFRMOBJHEADER) param)->ObjInst = obj;
  }

inline void DelObjectFromPar (FrmObject FAR *obj,LPVOID param)
  {
  ((LPFRMOBJHEADER) param)->ObjInst = NULL;
  }

void InterpreteMode (mdiChild *c,LPVOID param,WORD mode)
  {
  FrmObject FAR *obj = GetObjectFromPar (param,c);
  if (mode & EM_LOAD) {
    DBWIN_ASSERT (obj != NULL);
    obj->Load ();
#ifdef WITH_CHECK
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *)
            (c->ReadData(LPFRMOBJHEADER (param)->ObjRec, 
                         LPFRMOBJHEADER (param)->ObjId)
            );
    DBWIN_ASSERT((lpobj == NULL) || (*lpobj == NULL));
#endif
    obj->Write (obj,((mode & EM_CHANGETOTRUE) != 0) ? UPDATE_SYNCHRON : NO_UPDATE);
    if (obj->Initialized) {
      if ((c->DrawContext()->LoadDone) && ((mode & EM_CHANGETOTRUE) ||
          ((c->DrawContext() != c) &&
           (c->GetDocumentExtraData (DED_AVOIDINVALIDATE) == NULL)))) {
#ifdef UEBERLEGT
        if (c->IsInListFunction ()) {
          obj->Invalidate (obj->m.ActSide());
          }
        else {
#endif
          LPOBJDEF node = ((FrmObjectList FAR *) c->OutList())->
                  Find(obj);
          if ((node != NULL) &&
              (node->obj != NULL) &&
              ((node->ErsteSeite <= c->actSide()) &&
               (node->ErsteSeite + node->obj->AnzahlSeiten() > c->actSide()))) {
            obj->Invalidate (c->actSide());
            LPRECT logr = obj->GetLogRect (c->actSide());
            if (logr != NULL)
              obj->m.Rescale (logr);
            }
#ifdef UEBERLEGT
          }
#endif
        }
      }
    }
  if (mode & EM_UPDATE) {
    DBWIN_ASSERT (obj != NULL);
    LPOBJDEF node = ((FrmObjectList FAR *) c->OutList())->Find(obj);
    if ((obj->Initialized) && (obj->InvalidOnUpdate()) && (node != NULL))
      obj->Invalidate(obj->m.ActSide());
    obj->Update ();
    if ((obj->Initialized) && (obj->InvalidOnUpdate()) && (node != NULL)) {
      obj->GetMinMax();
      obj->Invalidate(obj->m.ActSide());
      int es = obj->ErsteSeite ();
      int as = obj->AnzahlSeiten ();
      if ((es <= obj->m.ActSide()) && (es + as > obj->m.ActSide())) {
        LPRECT logr = obj->GetLogRect (obj->m.ActSide());
        obj->m.Rescale (logr);
        }
      if ((List(c)->act == NULL) && (obj->IsToActivate()) && (GetFocus () == c->OutWnd())) {
        List(c)->OnSetFocus (TRUE);
        }
      }
    if (c->IsInListFunction ()) {
      obj->Write (obj,UPDATE_ASYNCHRON);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    DBWIN_ASSERT (obj != NULL);
    obj->SetConnection ();
    }
  if ((mode & (EM_CLEAR | EM_RESET)) && (obj != NULL)) {
    if (TailObj == obj) TailObj = NULL ;
    LPOBJDEF node = List(obj->m.PrivData)->Find(obj);
    if((obj->Initialized) && (node != NULL) && (!c->DrawContext()->closed) &&
       ((mode & EM_CLEAR) ||
        ((c->DrawContext() != c) &&
         (c->GetDocumentExtraData (DED_AVOIDINVALIDATE) == NULL))))
      obj->Invalidate(c->actSide());
    obj->SetInActiveIf(c->actSide());
    obj->Reset (mode & EM_CLEAR);
    obj->Write (NULL,((mode & EM_RESET) == 0) ? UPDATE_SYNCHRON : NO_UPDATE);
    DelObjectFromPar (obj,param);
    // List(obj->m.PrivData)->Change(obj,(FrmObject FAR *) NULL);
    if (node != NULL) node->obj = NULL ;
    delete obj;
    }
  if (mode & EM_SAVE) {
    DBWIN_ASSERT (obj != NULL);
    obj->Save ();
    }
  if (mode & EM_PRIVATE0) {
    obj->GetResource ();
    }
  if (mode & EM_PRIVATE1) {
    obj->m.PrivData->GetOutData()->tabx = obj->OnPrivate1 (obj->m.PrivData->GetOutData()->tabx);
    }
  if (mode & EM_PRIVATE2) {
    obj->GetSelText ();
    }
  }

// Sprungfunktionen fuer den Scriptinterpreter
//////////////////////////////////////////////////////
BOOL DefmNum (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new mNum(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefOutVGrid (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new OutVGrid(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmBField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmBField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefActivationRegion (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new ActivationRegion(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefPrgIcon (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new PrgIcon(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmStaticBitmap (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmStaticBitmap(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

#ifdef SDOC
BOOL DefDocObject (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new DocObject(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }
#endif

BOOL DefFrmSlantField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmSlantField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmMultiField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmMultiField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmTabField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmTabDate (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabDate(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabDecField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabColDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabColDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFKurve (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmFKurve(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabStrListField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabStrList(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabShortStrListField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabShortStrList(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabFlagField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabFlag(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefCheckBox (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmCheckBox(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefCheckField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmCheckField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTabCheckField (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTabCheckField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmSozNr (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmSozNr(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmDate (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmDate(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmTime (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmTime(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmSlantDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmSlantDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmSlantSLDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmSlantSLDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmDevDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmDevDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmDefDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmDefDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmSLDec (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmSLDec(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmStrList (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmStrList(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }


BOOL DefFrmStrShortList (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmStrShortList(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmStrDivList (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmDivStrList(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }


BOOL DefFrmLine (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseLines ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzLines ();
#endif
    WriteObjectToPar (new FrmLine(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmTab (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseLines ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzLines ();
#endif
    WriteObjectToPar (new FrmTab(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmImage (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmImage(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmRectImage (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new FrmRectImage(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTrcImage (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new TrcImage(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefEnterPoint (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new EnterPoint(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefEnterCont (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef DO_PROFILE
  if (!UseFields ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzFields ();
#endif
    WriteObjectToPar (new EnterCont(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

#pragma pack(1)
struct SetCaretToEnd_param {
  WORD parSize;
  DWORD obj;
  };
#pragma pack()

BOOL SetCaretToEnd (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetCaretToEnd_param FAR *par = (SetCaretToEnd_param FAR *) param;
    LPFRMFIELD FAR *lpobj = (LPFRMFIELD FAR *) c->ReadlData(par->obj);
    if ((lpobj != NULL) && (*lpobj != NULL) && ((*lpobj)->field != NULL))
      (*lpobj)->field->SetCaretToEnd ();
    }
  return FALSE;
  }

#pragma pack(1)
struct SetObjCallBack_param {
  WORD parSize;
  DWORD obj;        // Formular-Objekt welches einen Combo-Knopf bekommt
  DWORD procPtr;    // Prozedur die bei Druecken des Combos aufgerufen wird
  DWORD WithInput;  // TRUE =>  freie Text-Eingabe ist moeglich
                    // FALSE => Auswahl nur aus fixer Liste moeglich
  };
#pragma pack()

BOOL SetObjCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetObjCallBack_param FAR *par = (SetObjCallBack_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    (*lpobj)->CallBackProc = par->procPtr;

    DBBOOL FAR *lpInput = NULL;
    if (par->parSize > ((sizeof(SetObjCallBack_param))-sizeof(DWORD)))
      lpInput = (DBBOOL FAR *)c->ReadlData(par->WithInput);

    BOOL Input = (lpInput != NULL) ? *lpInput : FALSE;
    
    if ((*lpobj)->Initialized) {
      if (Input == 1)
        ((LPFRMFIELD)(*lpobj))->field->SetFieldMode (FM_BTNWITHINPUT);
      else       // das wird eine Listenauswahl !!!
        ((LPFRMFIELD)(*lpobj))->field->SetFieldMode (FM_LSELECTION | FM_NOSELECTION);
        
      if (Input != 2)
        ((LPFRMFIELD)(*lpobj))->field->SetButtonField (TRUE);  // mach mir den Knopf!
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetOnActivate_param {
  WORD parSize;
  DWORD obj;        // Formular-Objekt
  DWORD procPtr;    // Prozedur die beim Aktivieren des Objektes aufgerufen wird
  };
#pragma pack()

BOOL SetOnActivate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOnActivate_param FAR *par = (SetOnActivate_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    (*lpobj)->OnActivateProc = par->procPtr;
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetOnDeactivate_param {
  WORD parSize;
  DWORD obj;        // Formular-Objekt
  DWORD procPtr;    // Prozedur die beim Deaktivieren des Objektes aufgerufen wird
  };
#pragma pack()

BOOL SetOnDeactivate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetOnDeactivate_param FAR *par = (SetOnDeactivate_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    (*lpobj)->OnDeactivateProc = par->procPtr;
    }
  return FALSE ;
  }

#pragma pack(1)
struct CalcTabPos_Param {
  WORD ParSize;
  WORD pR, pI;
  WORD tR, tI;
  LONG reihe;
  LONG spalte;
  };
#pragma pack()

BOOL CalcTabPos (mdiChild *c,LPVOID param,WORD mode)
  {
  CalcTabPos_Param FAR *Par = (CalcTabPos_Param FAR *) param;
  
  if (mode & (EM_LOAD | EM_UPDATE)) {
    fpt res;
    LPFRMTABOBJ FAR *obj = (LPFRMTABOBJ FAR *) c->ReadData (Par->tR,Par->tI);

    if ((obj == NULL) || (*obj == NULL) ||
      (!(* obj)->CalcFieldPos (&res,int (Par->reihe),int (Par->spalte))))
      res.x = res.y = float(1.0E10);
    c->WriteData (Par->pR, Par->pI, &res, sizeof(res),
                                LPSTR (param) - sizeof(WORD),
                                (mode & (EM_UPDATE | EM_CHANGETOTRUE)) != 0
                 );
    }
  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(Par->tR, Par->tI, LPSTR (param) - sizeof (WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearConnection(Par->tR, Par->tI, LPSTR (param) - sizeof (WORD));
    }

  return FALSE;
  }

//  GetFieldLeftLower
typedef mNum FAR *LPMNUM;
class GetFldPos
  {
 public :
  BOOL doIt (mdiChild *c,LPVOID param,WORD mode);
  virtual void GetPos (cField FAR *f,LPPOINT pt,int Seite,mdiChild *c)
    { f->GetLeftLower (pt,Seite) ; }
  };

class GetFldRightPos : public GetFldPos 
  {
 private:
  BOOL bUpperPos;  // die rechten oberen Koordinaten nehmen ?

 public :
  GetFldRightPos (BOOL UpperPos) { bUpperPos = UpperPos; }
  virtual void GetPos (cField FAR *f,LPPOINT pt,int Seite,mdiChild *c)
    { 
    RECT r; 
    f->GetFieldRect (&r,Seite);
    pt->x = r.right ; 
    pt->y = bUpperPos ? r.top : r.bottom ; 
    int MapType;
    c->GetDocInfo (GETMAPTYPE,0,&MapType);
    if (MapType == MAPTYPE_GEOMETRIC)
      pt->y = bUpperPos ? r.bottom : r.top ;
    else
      pt->y = bUpperPos ? r.top : r.bottom ;
    }
  };

BOOL GetFldPos::doIt (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFieldLeftLower_par FAR *par = (GetFieldLeftLower_par FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPFRMOBJ FAR *obj = (LPFRMOBJ FAR *) 
        c->ReadData (par->or,par->oi);
    if ((obj != NULL) && (*obj != NULL) && ((*obj)->Initialized)) {
      POINT pt;
      DBINT LetzteSeite ;
      if ((*obj)->IsmNum ()) {
        LetzteSeite = (*obj)->ErsteSeite();
        GetPos ((LPMNUM (*obj))->fld[0],&pt,LetzteSeite,c);
        }
      else {
        LetzteSeite = (*obj)->ErsteSeite() + (*obj)->AnzahlSeiten() - 1 ;
        GetPos ((LPFRMFIELD (*obj))->field,&pt,LetzteSeite,c);
        }
      fpt p;
      p.x = c->LogToWorld (pt.x),  p.y = c->LogToWorld(pt.y) ;
      fpt FAR *old ;
      old = (fpt FAR *) c->TryToReadData (MAKELONG(par->pr,par->pi));
      if ((old == NULL) || (hypot (old->x - p.x,old->y - p.y) > 0.01)) {
        c->WriteData (par->pr,par->pi,&p,sizeof(fpt),
                                LPSTR (param) - sizeof(WORD));
        }
      }
    else
      c->DelData (par->pr,par->pi,LPSTR (param) - sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    for (int i = 0 ; i < AnzConn ; i++)
      c->SetConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    par->xold = 0 ;
    par->yold = 0 ;
    for (int i = 0 ; i < AnzConn ; i++)
      c->ClearConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }

BOOL GetFieldLeftLower (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFldPos p ;
  return p.doIt (c,param,mode);
  }

BOOL GetFieldLeftLowerSeite (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFieldLeftLowerSeite_par FAR *par = (GetFieldLeftLowerSeite_par FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPFRMOBJ FAR *obj = (LPFRMOBJ FAR *) 
        c->ReadData (par->or,par->oi);
    if ((obj != NULL) && (*obj != NULL) && ((*obj)->Initialized)) {
      POINT pt;
      int LetzteSeite ;
      if (!(*obj)->rcLogRectInitialized)
        (*obj)->GetMinMax();
      if ((*obj)->IsmNum ()) {
        LetzteSeite = (*obj)->ErsteSeite();
        ((LPMNUM) (*obj))->fld[0]->GetLeftLower (&pt,LetzteSeite);
        }
      else {
        LetzteSeite = (*obj)->ErsteSeite() + (*obj)->AnzahlSeiten() - 1 ;
        ((LPFRMFIELD) (*obj))->field->GetLeftLower (&pt,LetzteSeite);
        }
      fpt p;
      p.x = c->LogToWorld (pt.x),  p.y = c->LogToWorld(pt.y) ;
      fpt FAR *old ;
      old = (fpt FAR *) c->TryToReadData (MAKELONG(par->pr,par->pi));
      if ((old == NULL) || (hypot (old->x - p.x,old->y - p.y) > 0.01)) {
        c->WriteData (par->pr,par->pi,&p,sizeof(fpt),
                                LPSTR (param) - sizeof(WORD));
        }
      DBINT FAR *AlteSeite = (DBINT FAR *) c->TryToReadData (par->Seite);
      if ((AlteSeite == NULL) || (*AlteSeite != LetzteSeite)) {
        c->WritelData (par->Seite,&LetzteSeite,sizeof(LetzteSeite),
                                LPSTR (param) - sizeof(WORD));
        }
      }
    else {
      c->DelData (par->pr,par->pi,LPSTR (param) - sizeof(WORD));
      c->DellData (par->Seite,LPSTR (param) - sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    for (int i = 0 ; i < AnzConn ; i++)
      c->SetConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    par->xold = 0 ;
    par->yold = 0 ;
    for (int i = 0 ; i < AnzConn ; i++)
      c->ClearConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }

BOOL GetFieldLeftLowerAnzahlSeite (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFieldLeftLowerSeite_par FAR *par = (GetFieldLeftLowerSeite_par FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPFRMOBJ FAR *obj = (LPFRMOBJ FAR *) 
        c->ReadData (par->or,par->oi);
    if ((obj != NULL) && (*obj != NULL) && ((*obj)->Initialized)) {
      POINT pt;
      int LetzteSeite ;
      if (!(*obj)->rcLogRectInitialized)
        (*obj)->GetMinMax();
      if ((*obj)->IsmNum ()) {
        LetzteSeite = 0;
        ((LPMNUM) (*obj))->fld[0]->GetLeftLower (&pt,(*obj)->ErsteSeite() + LetzteSeite);
        }
      else {
        LetzteSeite = (*obj)->AnzahlSeiten() - 1 ;
        ((LPFRMFIELD) (*obj))->field->GetLeftLower (&pt,(*obj)->ErsteSeite() + LetzteSeite);
        }
      fpt p;
      p.x = c->LogToWorld (pt.x),  p.y = c->LogToWorld(pt.y) ;
      fpt FAR *old ;
      old = (fpt FAR *) c->TryToReadData (MAKELONG(par->pr,par->pi));
      if ((old == NULL) || (hypot (old->x - p.x,old->y - p.y) > 0.01)) {
        c->WriteData (par->pr,par->pi,&p,sizeof(fpt),
                                LPSTR (param) - sizeof(WORD));
        }
      DBINT FAR *AlteSeite = (DBINT FAR *) c->TryToReadData (par->Seite);
      if ((AlteSeite == NULL) || (*AlteSeite != LetzteSeite)) {
        c->WritelData (par->Seite,&LetzteSeite,sizeof(LetzteSeite),
                                LPSTR (param) - sizeof(WORD));
        }
      }
    else {
      c->DelData (par->pr,par->pi,LPSTR (param) - sizeof(WORD));
      c->DellData (par->Seite,LPSTR (param) - sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    for (int i = 0 ; i < AnzConn ; i++)
      c->SetConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    int AnzConn = (par->par_Size - sizeof(*par)) / sizeof(LONG) + 1;
    par->xold = 0 ;
    par->yold = 0 ;
    for (int i = 0 ; i < AnzConn ; i++)
      c->ClearConnection (par->dep[i].tr,par->dep[i].ti,LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }

//---------------------------------------------------------------------------
// gibt die rechte untere Position des FrmFields als <pointvar> zurueck
//---------------------------------------------------------------------------
BOOL GetFieldRightLower (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFldRightPos p (FALSE) ;
  return p.doIt (c,param,mode);
  }

//---------------------------------------------------------------------------
// gibt die rechte obere Position des FrmFields als <pointvar> zurueck
//---------------------------------------------------------------------------
BOOL GetFieldRightUpper (mdiChild *c,LPVOID param,WORD mode)
  {
  GetFldRightPos p (TRUE) ;
  return p.doIt (c,param,mode);
  }
//////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//    Eintrag in die Liste eines Multiselektionsfeldes
////////////////////////////////////////////////////////////
#pragma pack(1)
struct AddSHEnt_param {
  WORD parSize;
  WORD lRec,lId;
  LONG Id;
  WORD shRec,shId;    // String, 1. Buchstabe = Hotkey
  WORD stRec,stId;    // String, der im Feld angezeigt wird
  WORD ltRec,ltId;      // Hilfestring, der in der Liste angezeigt wird
  };
#pragma pack()

BOOL AddSHEnt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddSHEnt_param FAR *par = (AddSHEnt_param FAR *) param;
    LPMLI h ;
    LPMLI FAR *d = (LPMLI FAR *) c->ReadData (par->lRec,par->lId);
    if (d != NULL)
      h = *d ;
    else
      h = NULL ;

    LPSTR shk   = LPSTR (c->ReadData (par->shRec,par->shId));
    LPSTR shtxt = LPSTR (c->ReadData (par->stRec,par->stId));
    LPSTR ltxt  = LPSTR (c->ReadData (par->ltRec,par->ltId));
    DBWIN_ASSERT ((shk != NULL) && (shtxt != NULL) && (ltxt != NULL));

    AddItem (&h,WORD (par->Id),shk,shtxt,ltxt);

    c->WriteData (par->lRec,par->lId,&h,sizeof(h),
                                LPSTR (param) - sizeof(WORD),FALSE);
    }
  if (mode & EM_RESET) {
    AddSHEnt_param FAR *par = (AddSHEnt_param FAR *) param;
    LPMLI h ;
    LPMLI FAR *d = (LPMLI FAR *) c->ReadData (par->lRec,par->lId);
    if (d != NULL)
      h = *d ;
    else
      h = NULL ;

    DelItem (&h,WORD (par->Id));
    c->WriteData (par->lRec,par->lId,&h,sizeof(h),
                                LPSTR (param) - sizeof(WORD),FALSE);
    }
  return FALSE ;
  }

BOOL mNumSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    // Nix weiter zu tun, als die Parameter zu schreiben
    /////////////////////////////////////////////////////
    mNumSize_param FAR *par = (mNumSize_param FAR *) param;
    c->WritelData (par->Obj,&par,sizeof(par),
                      LPSTR(param)-sizeof(WORD),FALSE
                  );
    }
  return FALSE ;
  }

BOOL ShowmNumHelp (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmObjectList FAR *ol = (FrmObjectList FAR *) c->OutList();
    if ((ol != NULL) && (ol->act != NULL) && (ol->act->obj != NULL)
         && (ol->act->obj->IsmNum ()))
      ((mNum FAR *) (ol->act->obj))->ShowHelp ();
    else if ((ol != NULL) && (ol->act != NULL) && (ol->act->obj != NULL)
         && (ol->act->obj->IsInputObj ()))
      ((InputObj FAR *) (ol->act->obj))->ShowHelp ();
    else 
      MessageBeep (0);
    }
  return FALSE ;
  }

BOOL ShowmNumGauss (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmObjectList FAR *ol = (FrmObjectList FAR *) c->OutList();
    if ((ol != NULL) && (ol->act != NULL) && (ol->act->obj != NULL)
         && (ol->act->obj->IsmNum ()))
      ((mNum FAR *) (ol->act->obj))->ShowGauss ();
    else 
      MessageBeep (0);
    }
  return FALSE ;
  }

BOOL DefEntParam (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DefEnt_param FAR *par = (DefEnt_param FAR *)param;
    DefEnt FAR *e = new DefEnt (par,c);
    par->obj = e;

    e->GetScaleMat ();

    DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->modeRef);
    par->obj->InputMode = (lpmode != NULL) ? *lpmode : INPUTMODE_CORRECT ;

    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData (par->ImageRef);
    par->obj->ImageObject = (lpobj != NULL) ? *lpobj : NULL ;

    DBBOOL FAR *mn = (DBBOOL FAR *) c->ReadlData (par->MouseName);
    par->obj->ShowNameAtMouse = (mn != NULL) ? *mn : TRUE ;

    DBBOOL FAR *sn = (DBBOOL FAR *) c->ReadlData (par->SoundFlag);
    par->obj->SayName = (sn != NULL) ? *sn : FALSE ;

    e->WavePath = par->WavePath;

    c->WritelData (par->EntDef,&e,sizeof(e),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_UPDATE) {
#ifdef UEBERLEGT
    BOOL updateDone = FALSE ;
    DefEnt_param FAR *par = (DefEnt_param FAR *)param;
    if (c->IsUpdatelFromEle (par->SeqInd))
      // Neues Element aktivieren
      par->obj->OnIndChange (),
      updateDone = TRUE ;
    if (c->IsUpdatelFromEle (par->modeRef)) {
      // Modus hat sich geaendert
      DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->modeRef);
      par->obj->InputMode = (lpmode != NULL) ? *lpmode : INPUTMODE_CORRECT ;
      // Konturen muessen neu gezeichnet werden, da hilft nichts anderes
      InvalidateRect (c->OutWnd(),NULL,TRUE);
      updateDone = TRUE ;
      }
    if (c->IsUpdatelFromEle (par->ImageRef)) {
      // Das im Hintergrund liegende Image hat sich geaendert
      LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData (par->ImageRef);
      par->obj->ImageObject = (lpobj != NULL) ? *lpobj : NULL ;
      updateDone = TRUE ;
      }
    if (c->IsUpdatelFromEle (par->MouseName)) {
      DBBOOL FAR *mn = (DBBOOL FAR *) c->ReadlData (par->MouseName);
      par->obj->ShowNameAtMouse = (mn != NULL) ? *mn : TRUE ;
      updateDone = TRUE ;
      }
    if (c->IsUpdatelFromEle (par->SoundFlag)) {
      DBBOOL FAR *sn = (DBBOOL FAR *) c->ReadlData (par->SoundFlag);
      par->obj->SayName = (sn != NULL) ? *sn : FALSE ;
      updateDone = TRUE ;
      }
    if ((UpdateEleCount() != 1) || (!updateDone)) {
      // Sich selbst neu schreiben, um Update zu erzwingen
      par->obj->GetScaleMat ();
      c->WritelData (par->EntDef,&par->obj,sizeof(par->obj),LPSTR(param)-sizeof(WORD));
      }
#endif
    DefEnt_param FAR *par = (DefEnt_param FAR *)param;
    // Neues Element aktivieren
    par->obj->OnIndChange ();
    DBINT FAR *lpmode = (DBINT FAR *) c->ReadlData (par->modeRef);
    DBINT NewIM = (lpmode != NULL) ? *lpmode : INPUTMODE_CORRECT ;
    if (NewIM != par->obj->InputMode) {
      par->obj->InputMode = NewIM;
      // Konturen muessen neu gezeichnet werden, da hilft nichts anderes
      InvalidateRect (c->OutWnd(),NULL,TRUE);
      }
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData (par->ImageRef);
    par->obj->ImageObject = (lpobj != NULL) ? *lpobj : NULL ;
    DBBOOL FAR *mn = (DBBOOL FAR *) c->ReadlData (par->MouseName);
    par->obj->ShowNameAtMouse = (mn != NULL) ? *mn : TRUE ;
    DBBOOL FAR *sn = (DBBOOL FAR *) c->ReadlData (par->SoundFlag);
    par->obj->SayName = (sn != NULL) ? *sn : FALSE ;
    par->obj->GetScaleMat ();
    c->WritelData (par->EntDef,&par->obj,sizeof(par->obj),LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    // Weg mit dem Dreck
    DefEnt_param FAR *par = (DefEnt_param FAR *)param;
    DefEnt FAR *e = par->obj;

    for ( ; e->Root != NULL ; ) {
      e->RemoveGr (e->Root->p,FALSE);
      }
    e->WriteNameList ();

    delete e;
    c->ClearlConnection (par->SeqInd,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->scetod,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->scdtos,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->modeRef,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->MouseName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->SoundFlag,LPSTR(param)-sizeof(WORD));

#ifdef UEBERLEGT
    e = NULL;
    // Null Zeiger explizit reinschreiben, um Update zu verhindern
    c->WritelData (par->EntDef,&e,sizeof(e),LPSTR(param)-sizeof(WORD));
#endif
    c->DellData (par->EntDef,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    DefEnt_param FAR *par = (DefEnt_param FAR *)param;
    c->SetlConnection (par->SeqInd,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->scetod,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->scdtos,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->modeRef,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->MouseName,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->SoundFlag,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

ObjectDef FAR *FrmObjectList::Next(ObjectDef FAR *d)
  {
  return d->NextObjDef ;
  }

ObjectDef FAR *FrmObjectList::Prev(ObjectDef FAR *d)
  {
  return d->PrevObjDef ;
  }

// Gegenseitiger Ausschluss von Checkboxen
//////////////////////////////////////////////////////
#pragma pack(1)
struct uMutualExclude_param {
  WORD par_Size;
  DBINT oldActive;
  struct {
    WORD Rec,Id;
    } d[1];
  };

struct FrmObjectAddress {
  FrmObject FAR *obj;
  };
#pragma pack()

FrmCheckBox FAR *CheckObject (mdiChild *c,int i,uMutualExclude_param FAR *par)
  {
  FrmObjectAddress FAR *addr ;
  FrmCheckBox FAR *obj = NULL;
  addr = (FrmObjectAddress FAR *) c->ReadData (par->d[i].Rec,
                                               par->d[i].Id
                                              );
  if (addr != NULL)
    obj = (FrmCheckBox FAR *) (addr->obj);
  return obj;
  }

void SetFirstActive (mdiChild *c,uMutualExclude_param FAR *par)
  {
  // Den ersten setzen
  int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
  FrmCheckBox FAR *obj = NULL;
  for (int i = 0 ; i < AnzObjs ; i++) {
    if ((obj = CheckObject(c,i,par)) != NULL) break;
    }
  if (obj != NULL) {
    obj->State = TRUE ;
    obj->Save() ;
    obj->Invalidate(obj->m.ActSide()) ;
    par->oldActive = i;
    }
  }

BOOL uMutualExclude (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    uMutualExclude_param FAR *par =
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    par->oldActive = -1;

    // Ueberpruefung, ob sich einer im Grundzustand befindet
    FrmCheckBox FAR *obj;
    for (int i = 0 ; i < AnzObjs ; i++) {
      obj = CheckObject (c,i,par);
      if (obj != NULL) {
        if (!obj->IsCheckBox())
          DBWIN_ASSERT(FALSE);
        if (obj->State) {
          if (par->oldActive < 0)
            par->oldActive = i;
          else {
            obj->State = FALSE ;
            obj->Save ();
            }
          }
        }
      }
    if (par->oldActive < 0)
      SetFirstActive (c,par);
    }

  if (mode & EM_UPDATE) {
    int Sel[100];
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    int j = 0 ;
    FrmCheckBox FAR *obj;
    BOOL skipCalc = FALSE ;
    for (int i = 0 ; (i < AnzObjs) ; i++) {
      obj = CheckObject (c,i,par);
      if (obj != NULL) {
        if (obj->State) Sel[j++] = i ;
        }
      else
        skipCalc = TRUE ;
      }
    if (!skipCalc) {
      if (j == 0)
        SetFirstActive (c,par);
      else if (j >= 2) {
        int DontSwitch = (par->oldActive == Sel[0]) ? Sel[1] : Sel[0];
        for (int k = 0 ; k < j ; k++) {
          if (Sel[k] != DontSwitch) {
            obj = CheckObject (c,Sel[k],par);
            obj->State = FALSE ;
            obj->Save ();
            obj->Invalidate (obj->m.ActSide());
            }
          }
        par->oldActive = DontSwitch;
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    for (int i = 0 ; i < AnzObjs ; i++)
      c->SetConnection (par->d[i].Rec,par->d[i].Id,LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    for (int i = 0 ; i < AnzObjs ; i++)
      c->ClearConnection (par->d[i].Rec,par->d[i].Id,LPSTR(par) - sizeof(WORD));
    }
  return FALSE ;
  }

// Gegenseitiger Ausschluss von Checkboxen - ohne "SetFirstActive"
//////////////////////////////////////////////////////////////////
BOOL uMutualExcludeNone (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    par->oldActive = -1;

    // Ueberpruefung, ob sich einer im Grundzustand befindet
    FrmCheckBox FAR *obj;
    for (int i = 0 ; i < AnzObjs ; i++) {
      obj = CheckObject (c,i,par);
      if (obj != NULL) {
        if (!obj->IsCheckBox())
          DBWIN_ASSERT(FALSE);
        if (obj->State) {
          if (par->oldActive < 0)
            par->oldActive = i;
          else {
            obj->State = FALSE ;
            obj->Save ();
            }
          }
        }
      }
    }

  if (mode & EM_UPDATE) {
    int Sel[10];
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    int j = 0 ;
    FrmCheckBox FAR *obj;
    for (int i = 0 ; (i < AnzObjs) ; i++) {
      obj = CheckObject (c,i,par);
      if (obj != NULL) {
        if (obj->State) Sel[j++] = i ;
        }
      }
    int DontSwitch = (par->oldActive == Sel[0]) ? Sel[1] : Sel[0];
    if (j >= 2) {
      for (int k = 0 ; k < j ; k++) {
        if (Sel[k] != DontSwitch) {
          obj = CheckObject (c,Sel[k],par);
          obj->State = FALSE ;
          obj->Save ();
          obj->Invalidate (obj->m.ActSide());
          }
        }
      }
    par->oldActive = DontSwitch;
    }
  if (mode & EM_FIXCONNECTION) {
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    for (int i = 0 ; i < AnzObjs ; i++)
      c->SetConnection (par->d[i].Rec,par->d[i].Id,LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    uMutualExclude_param FAR *par = 
        (uMutualExclude_param FAR *) param;
    int AnzObjs = (par->par_Size - sizeof(WORD)) / (2 * sizeof(WORD));
    for (int i = 0 ; i < AnzObjs ; i++)
      c->ClearConnection (par->d[i].Rec,par->d[i].Id,LPSTR(par) - sizeof(WORD));
    }
  return FALSE ;
  }

static FrmObject FAR* GetObject (WORD Rec,WORD Id,mdiChild *c)
  {
  FrmObjectAddress FAR *addr = 
        (FrmObjectAddress FAR *) c->ReadData (Rec,Id);
  if (addr != NULL) return addr->obj;
  else              return NULL;
  }

// Setzen von Nachbarobjekten fuer die Hotkeys
/////////////////////////////////////////////////////
#pragma pack(1)
struct uSetDirKey_param {
  WORD parSize;
  WORD oRec,oId;
  struct {
    DWORD Id;
    }d[4];
  };
#pragma pack()

BOOL uSetDirKey (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    uSetDirKey_param FAR *par = (uSetDirKey_param FAR *) param;
    FrmObject FAR *oobj = GetObject (par->oRec,par->oId,c);
    if (oobj != NULL) {
      if ((!oobj->IsField()) && (!oobj->IsCheckBox()))
        DBWIN_ASSERT(FALSE);
      for (int i = 0 ; i < 4 ; i++)
        oobj->SetDirKey(par->d[i].Id,i);
      }
    }
  return FALSE ;
  }

BOOL uSetDirKeyUpDown (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    uSetDirKey_param FAR *par = (uSetDirKey_param FAR *) param;
    FrmObject FAR *oobj = GetObject (par->oRec,par->oId,c);
    if (oobj != NULL) {
      if ((!oobj->IsField()) && (!oobj->IsCheckBox()))
        DBWIN_ASSERT(FALSE);
      oobj->SetDirKey(par->d[0].Id,0); // up
      oobj->SetDirKey(par->d[1].Id,1); // down
      }
    }
  return FALSE ;
  }

BOOL uSetDirKeyLeftRight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    uSetDirKey_param FAR *par = (uSetDirKey_param FAR *) param;
    FrmObject FAR *oobj = GetObject (par->oRec,par->oId,c);
    if (oobj != NULL) {
      if ((!oobj->IsField()) && (!oobj->IsCheckBox()))
        DBWIN_ASSERT(FALSE);
      oobj->SetDirKey(par->d[0].Id,2); // left
      oobj->SetDirKey(par->d[1].Id,3); // right
      }
    }
  return FALSE ;
  }

//    Umordnen der Zeichenobjekte fuer die VTO
//////////////////////////////////////////////////////////////////
void FrmObjectList::OrderVTOObjs ()
  {
#ifdef UEBERLEGT
  // Alle Objekte mit der Laufenden Nummer 1, die nicht zum aktivieren
  // gehen, ganz nach vorne setzen
  if ((head == NULL) || (head->NextObjDef == head)) return ;
  LPOBJDEF old = NULL ;
  for ( LPOBJDEF hlp = head ; ; ) {
    LPOBJDEF next = hlp->NextObjDef ;
    if ((hlp->RunNmbr == 1) && 
        ((hlp->obj == NULL) ||
         ((!hlp->obj->IsToActivate()) &&
          (!hlp->obj->ForceToBackground())))) {
      // Rausnehmen aus der Liste
      if (hlp == head) head = head->NextObjDef ;
      if (hlp == tail) tail = tail->PrevObjDef ;
      hlp->PrevObjDef->NextObjDef = hlp->NextObjDef ;
      hlp->NextObjDef->PrevObjDef = hlp->PrevObjDef ;

      if (old != NULL) {
        // Hinter firstold reinhaengen
        hlp->NextObjDef = old->NextObjDef ;
        old->NextObjDef = hlp ;
        hlp->PrevObjDef = old ;
        hlp->NextObjDef->PrevObjDef = hlp ;
        }
      else {
        tail->NextObjDef = hlp;
        head->PrevObjDef = hlp;
        hlp->NextObjDef = head ;
        hlp->PrevObjDef = tail ;
        head = hlp;
        }
      old = hlp ;
      }
    hlp = next ;
    if (hlp == head) break ;
    }
  // zweiter Durchgang: Objekte in den Hintergrund schieben, die das wollen
  old = NULL ;
  for ( hlp = head ; ; ) {
    LPOBJDEF next = hlp->NextObjDef ;
    if ((hlp->obj != NULL) &&
        ((!hlp->obj->IsToActivate()) &&
         (hlp->obj->ForceToBackground()))) {
      // Rausnehmen aus der Liste
      if (hlp == head) head = head->NextObjDef ;
      if (hlp == tail) tail = tail->PrevObjDef ;
      hlp->PrevObjDef->NextObjDef = hlp->NextObjDef ;
      hlp->NextObjDef->PrevObjDef = hlp->PrevObjDef ;

      if (old != NULL) {
        // Hinter firstold reinhaengen
        hlp->NextObjDef = old->NextObjDef ;
        old->NextObjDef = hlp ;
        hlp->PrevObjDef = old ;
        hlp->NextObjDef->PrevObjDef = hlp ;
        }
      else {
        tail->NextObjDef = hlp;
        head->PrevObjDef = hlp;
        hlp->NextObjDef = head ;
        hlp->PrevObjDef = tail ;
        head = hlp;
        }
      old = hlp ;
      }
    hlp = next ;
    if (hlp == head) break ;
    }
  // dritter Durchgang: fix vorgegebene Reihenfolge der Objekte herstellen
  for ( hlp = head ; ; ) {
    LPOBJDEF next = hlp->NextObjDef ;
    if ((hlp->par != NULL) &&
        (hlp->par->CheckPrev()) &&
        (hlp->PrevObjDef->par != NULL) &&
        ((hlp->PrevObjDef->par->ObjId != HIWORD(hlp->par->prevObj)) ||
         (hlp->PrevObjDef->RunNmbr != WORD(hlp->par->prevRun)))) {
      // Rausnehmen aus der Liste
      if (hlp == head) head = head->NextObjDef ;
      if (hlp == tail) tail = tail->PrevObjDef ;
      hlp->PrevObjDef->NextObjDef = hlp->NextObjDef ;
      hlp->NextObjDef->PrevObjDef = hlp->PrevObjDef ;

      for ( LPOBJDEF h = head ; ; ) {
        if ((h->par != NULL) &&
            (h->par->ObjId == HIWORD(hlp->par->prevObj)) &&
            (h->RunNmbr == WORD(hlp->par->prevRun))) {
          // hinter diesem nun einfuegen
          ///////////////////////////////
          hlp->NextObjDef = h->NextObjDef ;
          h->NextObjDef->PrevObjDef = hlp;
          hlp->PrevObjDef = h ;
          h->NextObjDef = hlp ;
          if (tail == h)
            tail = hlp ;
          break ;
          }
        h = h->NextObjDef;
        if (h == head) {
          // Nicht gefunden
          DBWIN_ASSERT(FALSE);
          break ;
          }
        }
      }
    hlp = next ;
    if (hlp == head) break ;
    }
#endif
  }

void FrmObjectList::MoveToTail (LPFRMOBJ h)
  {
  if ((head == NULL) || (head->NextObjDef == head)) return ;
  LPOBJDEF old = NULL ;
  for ( LPOBJDEF hlp = head ; ; ) {
    if (hlp->obj == h) {
      // Rausnehmen aus der Liste
      if (hlp == head) head = head->NextObjDef ;
      if (hlp == tail) tail = tail->PrevObjDef ;
      hlp->PrevObjDef->NextObjDef = hlp->NextObjDef ;
      hlp->NextObjDef->PrevObjDef = hlp->PrevObjDef ;

      // Am Ende einfuegen
      tail->NextObjDef = hlp ;
      hlp->PrevObjDef = tail ;
      hlp->NextObjDef = head ;
      head->PrevObjDef = hlp ;
      tail = hlp;
      break ;
      }
    hlp = hlp->NextObjDef ;
    if (hlp == head) break ;
    }
  }

void FrmObjectList::ChangeSides (int diff)
  {
  if (head != NULL) {
    for (LPOBJDEF node = head ; ; node = node->NextObjDef) {
      node->ErsteSeite += diff;
      if (node->NextObjDef == head) break;
      }
    }
  }

#pragma pack(1)
struct GetDocInstance_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetDocInstance (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDocInstance_param FAR *par = (GetDocInstance_param FAR *) param;
    c->WritelData (par->res,&c,sizeof(c),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL GetParentInstance (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDocInstance_param FAR *par = (GetDocInstance_param FAR *) param;
    mdiChild *d;
    if (c->erzContext)
      d = c->erzContext;
    else
      d = c->DrawContext();
    c->WritelData (par->res,&d,sizeof(d),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SimpleObject_param {
  WORD parSize;
  DWORD objPtr;
  };
#pragma pack()

BOOL BringObjectToTail (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SimpleObject_param FAR *par = (SimpleObject_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData (par->objPtr);
    if ((lpobj != NULL) && (*lpobj != NULL))
      ((FrmObjectList FAR *) (c->OutList()))->MoveToTail (*lpobj);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetObjectSide_param {
  WORD parSize;
  DWORD Side;
  DWORD objPtr[1];
  int AnzObjs ()
    { return (parSize - sizeof (*this)) / sizeof (DWORD) + 1 ; }
  };
#pragma pack()

BOOL SetObjectSide (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetObjectSide_param FAR *par = (SetObjectSide_param FAR *) param;
    DBINT FAR *lpSide = (DBINT FAR *) c->ReadlData (par->Side);
    DBWIN_ASSERT (lpSide != NULL);
    for (int i = 0 ; i < par->AnzObjs() ; i++) {
      LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData (par->objPtr[i]);
      if ((lpobj != NULL) && (*lpobj != NULL)) {
        LPOBJDEF def = ((FrmObjectList FAR *) (c->OutList()))->Find (*lpobj);
        if ((def->ErsteSeite != *lpSide) && (mode & EM_UPDATE))
          (*lpobj)->Invalidate (c->actSide());
        def->ErsteSeite = *lpSide ;
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetObjectSide_param FAR *par = (SetObjectSide_param FAR *) param;
    c->SetlConnection (par->Side,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetObjectSide_param FAR *par = (SetObjectSide_param FAR *) param;
    c->ClearlConnection (par->Side,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetPrHeight_param {
  WORD parSize;
  DWORD res;
  DWORD DriverName;
  DWORD doLandscape;
  DWORD doPortrait;
  DWORD xleft,xright;
  DWORD str;
  };
#pragma pack()

BOOL GetPrTextHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetPrHeight_param FAR *par = (GetPrHeight_param FAR *) param ;
    LPSTR str = LPSTR (c->ReadlData (par->str));
    float fres;
    if (str != NULL) {

      // Berechnen der Papier - Groesse
      Printer *Pr;
      int xwidth;
#ifdef SDOC
      if (c->IsSmallDoc ()) {
        if (((sFormDoc *) c)->parent->Pr == NULL) {
          ((sFormDoc *) c)->parent->Pr = GetPrinter (TRUE);
          ((sFormDoc *) c)->parent->Pr->PrinterIC();
          }
        Pr = ((sFormDoc *) c)->parent->Pr;
        }
      else {
#endif
        if (c->GetOutData()->Pr == NULL) {
          c->GetOutData()->Pr = GetPrinter (TRUE);
          c->GetOutData()->Pr->PrinterIC();
          }
        Pr = c->GetOutData()->Pr;
#ifdef SDOC
        }
#endif
      RECT r;
      Pr->PaperSize (&r);

      {
      PaintContext pc(Pr);
      pc.Map (1.0);
      xwidth = - pc.YPHYStoLOG (r.bottom - r.top);
      }
      float gwidth = xwidth / float (25.0); // Hoehe in mm
      float FAR *xleft  = (float FAR *) c->ReadlData (par->xleft);
      float FAR *xright = (float FAR *) c->ReadlData (par->xright);
      if (xleft != NULL)
        gwidth -= *xleft;
      if (xright != NULL)
        gwidth -= *xright;
      gwidth *= float (1440.0 / 25.4) ;  // Hoehe in log. Twips

      GLOBALHANDLE hGPar = GlobalAlloc (GHND,sizeof(ParData));
      ParData FAR *pd = (ParData FAR *) GlobalLock (hGPar);
      pd->hBaseInst = pd->hExtInst = c;
      GlobalUnlock (hGPar);

      GLOBALHANDLE hGtxt = ConvertText (str,hGPar);
      GlobalFree (hGPar);
      LPSTR ntxt = (LPSTR)GlobalLock (hGtxt);
      HWND hWnd = (c->OutWnd() != 0) ? c->OutWnd() : WBase::hFrameWin ;
      cField *f = new cField (TRANSPARENT,2,0,0,int (gwidth),-1,FALSE);
      f->SetWindow (hWnd);
      f->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
      f->SetVOrg (0,0,0);
      *f = ntxt ;

      f->Reformat ();
      RECT rb;
      f->GetFieldRect (&rb,0);

      GlobalUnlock (hGtxt);
      GlobalFree (hGtxt);

      fres = float (double (rb.bottom - rb.top + 1) * 25.4 / 1440.0) ;
      }
    else
      fres = float (0.0);

    c->WritelData (par->res,&fres,sizeof(fres),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetPrHeight_param FAR *par = (GetPrHeight_param FAR *) param ;
    c->SetlConnection (par->DriverName,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->doLandscape,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->doPortrait,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->xleft,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->xright,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetPrHeight_param FAR *par = (GetPrHeight_param FAR *) param ;
    c->ClearlConnection (par->DriverName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->doLandscape,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->doPortrait,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->xleft,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->xright,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->str,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL Trc_DefMark(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcMarkObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefLine(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcLineObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefRectangle(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcRectangleObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefEllipse(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcEllipseObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefRectImage(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcRectImageObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefArc(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcArcObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefPattern(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcPatternObj(param,c,FALSE),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefmPattern(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcPatternObj(param,c,TRUE),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefPattern(mdiChild *c, LPVOID param, WORD mode)
  {
#ifdef DO_PROFILE
  if (!UsePatterns ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzPatterns ();
#endif
    WriteObjectToPar (new PatternObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefMovePattern(mdiChild *c, LPVOID param, WORD mode)
  {
#ifdef DO_PROFILE
  if (!UsePatterns ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzPatterns ();
#endif
    WriteObjectToPar (new MovePatternObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefClickPattern(mdiChild *c, LPVOID param, WORD mode)
  {
#ifdef DO_PROFILE
  if (!UsePatterns ()) return FALSE ;
#endif
  if (mode & EM_LOAD) {
#ifdef DO_PROFILE
    IncAnzPatterns ();
#endif
    WriteObjectToPar (new ClickPatternObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefCont(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcContObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefContain(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcContainObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefContain2 (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcContain2Obj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL Trc_DefFilledCont(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcFilledContObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmTable(mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new FrmTable(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetOutColor_param {
  WORD parSize;
  DWORD cRef;
  DWORD oRef[1];
  int AnzObjs ()
    { return (parSize - (sizeof(*this) - sizeof(oRef[0]))) / sizeof(oRef[0]) ; }
  };
#pragma pack()
BOOL SetObjectColor (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    DWORD FAR *color = (DWORD FAR *) c->ReadlData (par->cRef);
    for (int i = 0 ; i < par->AnzObjs () ; i++) {
      LPFRMFIELD FAR *f = (LPFRMFIELD FAR *) c->ReadlData (par->oRef[i]);
      if ((f != NULL) && (*f != NULL) && ((*f)->IsField())) {
        if (color != NULL)
          (*f)->FieldColor = *color;
        else
          (*f)->FieldColor = 0xFFFFFFFF;
        if ((*f)->Initialized) {
          if (color != NULL)
            (*f)->field->SetOutColor (*color);
          else
            (*f)->field->UseDefOutColor ();
          (*f)->Invalidate (c->actSide());
          }
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    c->SetlConnection (par->cRef,LPSTR(par) - sizeof(WORD));
    for (int i = 0 ; i < par->AnzObjs () ; i++)
      c->SetlConnection (par->oRef[i],LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    c->ClearlConnection (par->cRef,LPSTR(par) - sizeof(WORD));
    for (int i = 0 ; i < par->AnzObjs () ; i++) {
      if (!c->IsInListFunction ()) {
        LPFRMFIELD FAR *f = (LPFRMFIELD FAR *) c->ReadlData (par->oRef[i]);
        if ((f != NULL) && (*f != NULL) && ((*f)->IsField())) {
          (*f)->FieldColor = 0xFFFFFFFF ;
          if ((*f)->Initialized) {
            (*f)->field->UseDefOutColor ();
            (*f)->Invalidate (c->actSide());
            }
          }
        }
      c->ClearlConnection (par->oRef[i],LPSTR(par) - sizeof(WORD));
      }
    }
  return FALSE ;
  }

BOOL SetExtraModify (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    DBINT FAR *em = (DBINT FAR *) c->ReadlData (par->cRef);
    if (em != NULL) {
      for (int i = 0 ; i < par->AnzObjs () ; i++) {
        LPFRMFIELD FAR *f = (LPFRMFIELD FAR *) c->ReadlData (par->oRef[i]);
        if ((f != NULL) && (*f != NULL) && ((*f)->IsField()) && ((*f)->Initialized)) {
          (*f)->field->SetExtraModify (*em);
          (*f)->Invalidate (c->actSide());
          }
        }
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    c->SetlConnection (par->cRef,LPSTR(par) - sizeof(WORD));
    for (int i = 0 ; i < par->AnzObjs () ; i++)
      c->SetlConnection (par->oRef[i],LPSTR(par) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetOutColor_param FAR *par = (SetOutColor_param FAR *) param ;
    for (int i = 0 ; i < par->AnzObjs () ; i++) {
      if (!c->IsInListFunction ()) {
        LPFRMFIELD FAR *f = (LPFRMFIELD FAR *) c->ReadlData (par->oRef[i]);
        if ((f != NULL) && (*f != NULL) && ((*f)->IsField()) && ((*f)->Initialized)) {
          (*f)->field->SetExtraModify (0);
          (*f)->Invalidate (c->actSide());
          }
        }
      c->ClearlConnection (par->oRef[i],LPSTR(par) - sizeof(WORD));
      }
    c->ClearlConnection (par->cRef,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL DefProjectPoint (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new ProjectPoint(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

#pragma pack(1)
struct GetActiveElem_param {
  WORD parSize;
  DWORD childToCheck;
  DWORD rObj;
  DWORD rChild;
  };
#pragma pack()
BOOL GetActiveElem (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetActiveElem_param FAR *par = (GetActiveElem_param FAR *) param;
    LPMDICHILD FAR *pc = (LPMDICHILD FAR *) c->ReadlData (par->childToCheck);
    BOOL done = FALSE ;
    if (pc != NULL) {
      FrmObjectList FAR *l = (FrmObjectList FAR *) ((*pc)->OutList());
      LPOBJDEF act = l->act;
      if (act != NULL) {
        c->WritelData (par->rObj,&act->obj,sizeof(act->obj),LPSTR(param)-sizeof(WORD));
        c->WritelData (par->rChild,&act->obj->m.PrivData,sizeof(act->obj->m.PrivData),LPSTR(param)-sizeof(WORD));
        done = TRUE ;
        }
      }
    if (!done) {
      c->DellData (par->rObj,LPSTR(param)-sizeof(WORD));
      c->DellData (par->rChild,LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE ;
  }


// Move - Objekte:
///////////////////

BOOL DefMoveField (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new MoveField(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefMoveLine (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new MoveLine(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefMoveRect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new MoveRect(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefMoveRectImage (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new MoveRectImage(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefHelpLine (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new HelpLine(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmShort (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new FrmShort(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }


BOOL DefFrmLong (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new FrmLong(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefFrmMoney (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new FrmMoney(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

BOOL DefTrcGrid (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    WriteObjectToPar (new TrcGridObj(param,c),param,c);
    }
  InterpreteMode (c,param,mode);
  return FALSE ;
  }

  #pragma pack(1)
struct SetDblClkProc_param {
  WORD parSize;
  WORD oRec,oId;
  DWORD procoffs;
  };
#pragma pack()

BOOL SetDblClkProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDblClkProc_param FAR *par = (SetDblClkProc_param FAR *) param;
    FrmObject FAR *oobj = GetObject (par->oRec,par->oId,c);
    if (oobj != NULL) {
      LPMOVEOBJ mo = oobj->moptr();
      if (mo != NULL)
        mo->SetDblClkProc(par->procoffs);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFrmEditSize_param {
  WORD parSize;
  DWORD obj;
  DWORD size;
  };
#pragma pack()

BOOL SetFrmEditSize (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFrmEditSize_param FAR *par = (SetFrmEditSize_param FAR *) param;
    LPFRMFIELD FAR *e = (LPFRMFIELD FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    DBINT FAR *size = (DBINT FAR *) c->ReadlData (par->size);
    if (size != NULL)
      (*e)->SetStringSize (*size);
    else
      (*e)->SetStringSize (-1);
    }
  return FALSE ;
  }

#pragma pack(1)
struct ProjectCallBack_param {
  WORD parSize;
  DWORD proc;
  DWORD x;
  DWORD y;
  };
#pragma pack()
BOOL ProjectCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ProjectCallBack_param FAR *par = (ProjectCallBack_param FAR *) param;
    SetProjectCallBack(par->proc,par->x,par->y);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetProjectCallBack(0L,0L,0L);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR ActivateObject_param {
  WORD parSize;
  DWORD obj;
  DWORD useExplicit;
  BOOL withExplicit ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

BOOL ActivateObject (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldActive = BlockIsActive ;
    BlockIsActive = FALSE ;
    ActivateObject_param FAR *par = (ActivateObject_param FAR *) param;
    LPFRMOBJ FAR *obj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    if ((obj != NULL) && (*obj != NULL)) {
      BOOL doExplicit = TRUE ;
      if (par->withExplicit ()) {
        DBBOOL FAR *lpExp = (DBBOOL FAR *) (c->ReadlData (par->useExplicit));
        if (lpExp != NULL)
          doExplicit = *lpExp;
        }
      List(c)->SetActiveExplicit (*obj,doExplicit);
      if (GetFocus() != c->OutWnd()) {
        LPOBJDEF d = List(c)->Find (*obj);
        if ((d != NULL) && (d->ErsteSeite != c->actSide()))
          c->DrawContext()->ChangeDocSide (d->ErsteSeite - c->actSide());
        else
          SetFocus (c->OutWnd());
        }
      }
    BlockIsActive = oldActive ;
    }
  return FALSE ;
  }

#pragma pack(1)
struct ConnectToCheckBox_param {
  WORD parSize;
  DWORD field;
  DWORD box;
  };
#pragma pack()
BOOL ConnectToCheckBox (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ConnectToCheckBox_param FAR * par = (ConnectToCheckBox_param FAR *) param ;
    LPFRMFIELD FAR *o1 = (LPFRMFIELD FAR *) c->ReadlData (par->field);
    LPFRMOBJ FAR *o2 = (LPFRMOBJ FAR *) c->ReadlData (par->box);
    if ((o1 != NULL) && (*o1 != NULL) && (o2 != NULL) && (*o2 != NULL)) {
      ((FrmCheckBox FAR *)(*o2))->SetField (*o1);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFieldMode_param {
  WORD parSize;
  DWORD obj;         // Formular-Eingabefeld
  DWORD fieldmode;   // Modus z.b. FM_NOGERMANCHARS, FM_DECIMAL, ...
  };
#pragma pack()

BOOL SetFieldMode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFieldMode_param FAR *par = (SetFieldMode_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    ((LPFRMFIELD)(*lpobj))->SetFieldMode (c->ReadConstLong(par->fieldmode));
    }
  return FALSE ;
  }
  
#pragma pack(1)
struct SetObjLineHeight_param {
  WORD parSize;
  DWORD obj;
  DWORD height;
  };
#pragma pack()

BOOL SetObjLineHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetObjLineHeight_param FAR *par = (SetObjLineHeight_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    if (((LPFRMFIELD)(*lpobj))->field != NULL) {
      ((LPFRMFIELD)(*lpobj))->Invalidate (c->actSide());
      ((LPFRMFIELD)(*lpobj))->field->SetLineHeight (c->ReadConstInt(par->height));
      ((LPFRMFIELD)(*lpobj))->Invalidate (c->actSide());
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetObjLineHeight_param {
  WORD parSize;
  DWORD height;
  DWORD obj;
  };
#pragma pack()

BOOL GetObjLineHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetObjLineHeight_param FAR *par = (GetObjLineHeight_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    if (((LPFRMFIELD)(*lpobj))->field != NULL) {
      short hg = ((LPFRMFIELD)(*lpobj))->field->GetLineHeight ();
      c->WritelData (par->height,&hg,sizeof(hg),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->height,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetObjLineHeight_param FAR *par = (GetObjLineHeight_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetObjLineHeight_param FAR *par = (GetObjLineHeight_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFieldPageBreak_param {
  WORD parSize ;
  DWORD obj;
  DWORD ymax;
  DWORD yNext;
  };
#pragma pack()

BOOL SetFieldPageBreak (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetFieldPageBreak_param FAR *par = (SetFieldPageBreak_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    DBWIN_ASSERT ((lpobj != NULL) && (*lpobj != NULL)) ;
    short FAR *ymax = (short FAR *) c->ReadlData (par->ymax);
    short FAR *yNext = (short FAR *) c->ReadlData (par->yNext);
    DBWIN_ASSERT ((ymax != NULL) && (yNext != NULL)) ;
    ((LPFRMFIELD)(*lpobj))->Invalidate (c->actSide());
    ((LPFRMFIELD)(*lpobj))->field->SetPageBreak (*ymax,*yNext);
    ((LPFRMFIELD)(*lpobj))->GetMinMax ();
    DWORD saveRefForWrite = ((LPFRMFIELD)(*lpobj))->RefForWrite; // Modify-Flag kurz ausschalten
    ((LPFRMFIELD)(*lpobj))->RefForWrite = 0L;
    ((LPFRMFIELD)(*lpobj))->Save ();    // Damit des LeftLower einen Update kriegt
    ((LPFRMFIELD)(*lpobj))->RefForWrite = saveRefForWrite;
    ((LPFRMFIELD)(*lpobj))->Invalidate (c->actSide());
    LPRECT logr = ((LPFRMFIELD)(*lpobj))->GetLogRect (c->actSide());
    ((LPFRMFIELD)(*lpobj))->m.Rescale (logr);
    }
  if (mode & EM_FIXCONNECTION) {
    SetFieldPageBreak_param FAR *par = (SetFieldPageBreak_param FAR *) param;
    c->SetlConnection (par->ymax,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->yNext,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetFieldPageBreak_param FAR *par = (SetFieldPageBreak_param FAR *) param;
    c->ClearlConnection (par->ymax,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->yNext,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetModifyFlag_param {
  WORD parSize ;
  DWORD obj;
  DWORD flag;
  };
#pragma pack()

BOOL SetModifyFlag (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetModifyFlag_param FAR *par = (SetModifyFlag_param FAR *) param;
    LPFRMOBJ FAR *lpobj = (LPFRMOBJ FAR *) c->ReadlData(par->obj);
    if ((lpobj != NULL) && (*lpobj != NULL))
      (*lpobj)->RefForWrite = par->flag ;
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetFrmFieldText_param {
  WORD parSize;
  DWORD res;
  DWORD obj;
  };
#pragma pack()

BOOL GetFrmFieldText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetFrmFieldText_param FAR *par = (GetFrmFieldText_param FAR *) param;
    LPFRMFIELD FAR *e = (LPFRMFIELD FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    GLOBALHANDLE hGmem;
    *((*e)->field) >> hGmem;
    LPSTR dst = RemoveAllFormatInfoFromString (LPSTR (GlobalLock (hGmem)));
    GlobalUnlock (hGmem);

    if (dst != NULL) {
      c->WritelData (par->res,dst,lstrlen(dst) + 1,LPSTR(param) - sizeof(WORD));
      FreeGlobMem (dst);
      }
    else
      c->DellData (par->res,LPSTR(param) - sizeof(WORD));

    if (hGmem)
      GlobalFree (hGmem);
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetSelection_param {
  WORD parSize;
  DWORD obj;
  DWORD s,l;
  DWORD x0,y0;
  };
#pragma pack()

BOOL SetSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetSelection_param FAR *par = (SetSelection_param FAR *) param;
    LPFRMFIELD FAR *e = (LPFRMFIELD FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    DBINT FAR *s = (DBINT FAR *) c->ReadlData (par->s);
    DBINT FAR *l = (DBINT FAR *) c->ReadlData (par->l);

    if ((s != NULL) && (e != NULL)) {
      (*e)->field->SetSelection (*s,*l,c->DrawContext()->GetOutData()->_ActSide);
      // c->WritelData (par->x0,&p0.x,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      // c->WritelData (par->y0,&p0.y,sizeof(DBINT),LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & EM_FIXCONNECTION) {
    SetSelection_param FAR *par = (SetSelection_param FAR *) param;
    c->SetlConnection (par->s,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->l,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetSelection_param FAR *par = (SetSelection_param FAR *) param;
    c->ClearlConnection (par->s,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->l,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ChangeSelection_param {
  WORD parSize;
  DWORD obj;
  DWORD s,l;
  DWORD txt;
  };
#pragma pack()

BOOL ChangeSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ChangeSelection_param FAR *par = (ChangeSelection_param FAR *) param;
    LPFRMFIELD FAR *e = (LPFRMFIELD FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    DBINT FAR *s = (DBINT FAR *) c->ReadlData (par->s);
    DBINT FAR *l = (DBINT FAR *) c->ReadlData (par->l);
    LPSTR txt = LPSTR (c->ReadlData (par->txt));

    if ((s != NULL) && (e != NULL) && (txt != NULL) && (l != NULL)) {
      (*e)->field->ChangeSelection (*s,*l,txt);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    ChangeSelection_param FAR *par = (ChangeSelection_param FAR *) param;
    c->SetlConnection (par->s,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->l,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ChangeSelection_param FAR *par = (ChangeSelection_param FAR *) param;
    c->ClearlConnection (par->s,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->l,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->txt,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetHelpPrefix_param {
  WORD parSize;
  DWORD res;
  DWORD obj;
  };
#pragma pack()

BOOL GetHelpPrefix (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetHelpPrefix_param FAR *par = (GetHelpPrefix_param FAR *) param;
    LPFRMOBJ FAR *e = (LPFRMOBJ FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    DWORD res = (*e)->GetHelpPrefix ();

    if (res > 0L)
      c->WritelData (par->res,&res,sizeof(DWORD),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetHelpPrefix_param FAR *par = (GetHelpPrefix_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetHelpPrefix_param FAR *par = (GetHelpPrefix_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetObjInfo_param {
  WORD parSize;
  DWORD obj;
  DWORD inf;
  };
#pragma pack()
BOOL SetObjInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetObjInfo_param FAR *par = (SetObjInfo_param FAR *) param;
    LPFRMOBJ FAR *e = (LPFRMOBJ FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));
    LPSTR x = LPSTR (c->ReadlData (par->inf));
    if (x != NULL)
      (*e)->SetObjInfo (x);
    else
      (*e)->SetObjInfo (NULL);
    }
  if (mode & EM_FIXCONNECTION) {
    SetObjInfo_param FAR *par = (SetObjInfo_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->inf,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetObjInfo_param FAR *par = (SetObjInfo_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->inf,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetObjInfo_param {
  WORD parSize;
  DWORD res;
  DWORD obj;
  };
#pragma pack()
BOOL GetObjInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetObjInfo_param FAR *par = (GetObjInfo_param FAR *) param;
    LPFRMOBJ FAR *e = (LPFRMOBJ FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));

    LPSTR res = (*e)->GetObjInfo ();
    if (res > 0L)
      c->WritelData (par->res,res,lstrlen(res) + 1,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetObjInfo_param FAR *par = (GetObjInfo_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetObjInfo_param FAR *par = (GetObjInfo_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetObjContext_param {
  WORD parSize;
  DWORD res;
  DWORD obj;
  };
#pragma pack()
BOOL GetObjContext (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetObjContext_param FAR *par = (GetObjContext_param FAR *) param;
    LPFRMOBJ FAR *e = (LPFRMOBJ FAR *) c->ReadlData (par->obj);
    DBWIN_ASSERT ((e != NULL) && (*e != NULL));

    mdiChild *res = (*e)->m.PrivData->DrawContext();
    if (res)
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetObjContext_param FAR *par = (GetObjContext_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetObjContext_param FAR *par = (GetObjContext_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFocusToSubDoc_param {
  WORD parSize;
  DWORD docInst;
  };
#pragma pack()
BOOL SetFocusToSubDoc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BOOL oldActive = BlockIsActive ;
    BlockIsActive = FALSE ;
    SetFocusToSubDoc_param FAR *par = (SetFocusToSubDoc_param FAR *) param;
    LPMDICHILD FAR *inst = (LPMDICHILD FAR *) c->ReadlData (par->docInst);
    if ((inst != NULL) && (*inst != NULL)) {
      for ( LPOBJDEF h = List(*inst)->head ; ; ) {
        if ((GetFocus () == (*inst)->OutWnd()) && 
                  (h->obj != NULL) && (h->obj->IsToActivate()) &&
                  (h->ErsteSeite == c->actSide()) &&
                  (h->obj->m.PrivData == *inst)) {
          List(*inst)->DeactivateNode();
          DWORD o = (List(*inst)->act != NULL) ? MAKELONG(List(*inst)->act->par->ObjRec,List(*inst)->act->par->ObjId) : 0L ;
          List(*inst)->act = h ;
          h->obj->SetActiveIf ((*inst)->actSide(),TRUE);
          DWORD n = MAKELONG(List(*inst)->act->par->ObjRec,List(*inst)->act->par->ObjId) ;
          RealFocusIsChanging (o,n);
          break ;
          }
        h = h->NextObjDef;
        if (h == List(*inst)->head) break;
        }
      }
    BlockIsActive = oldActive;
    }
  return FALSE ;
  }
