/////////////////////////////////////////////////////////////////
//  Anzeigen von Listen
/////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/rev/list.cpv   1.179   18 May 2000 09:53:48   Hannes  $
//  $Log:   F:/marille/clinicum/rev/list.cpv  $
// 
//    Rev 1.179   18 May 2000 09:53:48   Hannes
// Fehlerhandling beim Drucken
// 
//    Rev 1.178   26 Apr 2000 12:07:32   Lens
// MultiComboReset
//
//    Rev 1.177   06 Mar 2000 07:11:24   Hannes
// Neuer Prototyp UpdateElem
//
//    Rev 1.176   03 Mar 2000 08:56:16   Dietmar
// Aenderungen in UpdateListEntry(), LOUpdate(), lInnerUpdate
// (Abgleich f. Hannes)
//
//    Rev 1.175   19 Dec 1999 21:26:24   Hannes
// ForcePageBreak
//
//    Rev 1.174   11 Nov 1999 14:55:14   Wolfgang
// 1.) GetFirst korrigiert.
// 2.) GetSelCount auch fuer neue Listen.
//
//    Rev 1.173   08 Nov 1999 03:44:42   Hannes
// In Testrecord ein Refreshlist
//
//    Rev 1.172   20 Oct 1999 07:50:16   Hannes
//
//    Rev 1.171   29 Jul 1999 15:52:56   Wolfgang
// 1.) _actList auch ohne LIKE setzen.
//
//    Rev 1.170   28 Jul 1999 18:29:36   Hannes
// ClearExpression von lRefreshList
//
//    Rev 1.169   08 Jul 1999 08:45:50   Hannes
// Straight Forward
//
//    Rev 1.168   02 May 1999 19:47:40   Hannes
// Clipping erweitert, damit am Ende vertikale Linien dick eingetragen weden
// koennen
//
//    Rev 1.167   30 Apr 1999 21:54:00   Hannes
// SelektionsProzedur auch Beim ForceSelection aufgerufen...
//
//    Rev 1.166   05 Mar 1999 10:56:24   Hannes
// Diverse Verbesserunge Combo - Liste
//
//    Rev 1.165   23 Feb 1999 15:10:44   Hannes
// Combo - Liste
//
//    Rev 1.164   11 Feb 1999 11:44:06   Martin
// oldDlgText vergroessert, auf Laenge geprueft
//
//    Rev 1.163   28 Jan 1999 12:20:26   Hannes
// Erweiterte SQL - Syntax
//
//    Rev 1.162   07 Dec 1998 18:54:10   Hannes
// Diverse Fehlerkorrekturen
//
//    Rev 1.161   18 Nov 1998 15:51:28   Hannes
// Focus auch bei Sofortauswahl richtig setzen
//
//    Rev 1.160   13 Nov 1998 10:28:24   Hannes
// OnSetFocus Bei Formularobjekten sicherheitshalber dazu
//
//    Rev 1.159   12 Nov 1998 18:29:42   Dietmar
// pc.cr gesetzt
//
//    Rev 1.158   11 Nov 1998 08:51:28   Hannes
// Beim Drucken der Liste keine Updates durchlassen...
//
//    Rev 1.157   05 Oct 1998 11:54:20   Gerhold
// Vorbereitung auf C6 (Type Casts)
//
//    Rev 1.156   14 Sep 1998 03:23:36   Hannes
// Verbesserungen Lesen von Koordinaten in Funktionen
//
//    Rev 1.155   01 Sep 1998 23:43:42   Hannes
// Fix / ClearConnection auf die Breiten in PaintFullHeader
//
//    Rev 1.154   19 Aug 1998 21:33:18   Hannes
// Listenobj NULL
//
//    Rev 1.153   07 Aug 1998 00:01:38   Hannes
// SetPrinterCaption
//
//    Rev 1.152   04 Aug 1998 17:54:36   Hannes
// Timestamp
//
//    Rev 1.151   27 Jul 1998 15:15:24   Hannes
// lSetUpCallBack
//
//    Rev 1.150   27 Jul 1998 11:38:34   Hannes
//
//    Rev 1.149   08 Jul 1998 14:22:32   Hannes
//
//    Rev 1.148   07 Jul 1998 13:54:04   Hannes
// TYPE_MULTIFRMOBJ: Ueberall nachgebessert
//
//    Rev 1.147   29 Jun 1998 19:01:24   Hannes
//
//    Rev 1.146   19 May 1998 21:07:06   Hannes
// Extradaten beim LOODrawHeader
//
//    Rev 1.145   20 Mar 1998 15:28:42   Hannes
//
//    Rev 1.144   17 Mar 1998 10:06:24   Hannes
// ClickPositionsberechnung: Listenposition mitberuecksichtigen...
//
//    Rev 1.143   16 Mar 1998 09:03:58   Hannes
// SetListClickProc ... Position wird zurueckgeliefert
//
//    Rev 1.142   13 Mar 1998 18:56:04   Hannes
// Listenklickprozedur
//
//    Rev 1.141   24 Feb 1998 19:44:44   Hannes
// Wenn schon SaveRecord, dann auch Restorerecord
//
//    Rev 1.140   23 Feb 1998 20:01:54   Hannes
// PressedChar
//
//    Rev 1.139   13 Feb 1998 13:26:30   Hannes
//
//    Rev 1.138   12 Feb 1998 19:59:18   Hannes
// ExtraDataAtCreation bei delete ListElem, ClearConnection beruecksichtigt
//
//    Rev 1.137   06 Feb 1998 08:00:54   Hannes
// MultiSelektion bei lChangeSelection
//
//    Rev 1.136   02 Feb 1998 20:33:16   Hannes
// lChangeSelection: Status 2->Multiselektion auch bei normalen
// Singleselektionsboxen
//
//    Rev 1.135   31 Jan 1998 22:24:10   Martin
// list.hpp, einige Funktionen in list1.cpp verlagert (code seg. too large)
//
//    Rev 1.134   30 Jan 1998 19:44:36   Hannes
// Clipping - Area vergroessert, damit eine dicke Linie gezeichnet werden kann
//
//    Rev 1.133   26 Jan 1998 20:01:02   Hannes
// Listenfarben
//
//    Rev 1.132   19 Jan 1998 20:16:48   Hannes
//
//    Rev 1.131   16 Jan 1998 15:27:40   Hannes
// Listenfarben
//
//    Rev 1.130   12 Jan 1998 18:18:42   Hannes
// DDSLIST_SELECT: BlockIsActive ruecksetzten
//
//    Rev 1.129   05 Jan 1998 07:53:44   Hannes
// Einsparungen im Scriptheader
//
//    Rev 1.128   16 Dec 1997 16:08:06   Hannes
// Datensaetze, die nicht getestet werden, ganz freigeben
//
//    Rev 1.127   05 Dec 1997 17:45:24   Hannes
// diverse Verbesserungen
//
//    Rev 1.126   01 Dec 1997 19:38:20   Hannes
// Diverse Anpassungen
//
//    Rev 1.125   05 Nov 1997 15:55:22   Hannes
// Drucken von Modulen aus
//
//    Rev 1.124   04 Nov 1997 17:56:10   Hannes
// IsUpdateToDo ... Fehlerkorrektur
//
//
//    Rev 1.123   27 Oct 1997 19:50:58   Hannes
// Diverse Fehlerkorrekturen
//
//    Rev 1.122   24 Oct 1997 08:37:12   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
//
//    Rev 1.121   21 Oct 1997 08:33:00   Martin
// Extradatenberuecksichtigung
//
//    Rev 1.120   12 Sep 1997 19:29:12   Hannes
// Verbesserungen an der Testprozedur
//
//    Rev 1.119   08 Sep 1997 16:05:10   Hannes
//
//    Rev 1.118   04 Sep 1997 20:02:32   Hannes
// ComboInnerList
//
//    Rev 1.117   12 Aug 1997 13:28:52   Hannes
// DoCheckAnzSels eingebaut
//
//    Rev 1.116   01 Jul 1997 14:38:28   Hannes
//
//    Rev 1.115   25 Jun 1997 08:58:44   Hannes
//
//    Rev 1.114   19 Jun 1997 10:19:12   Hannes
// Testrecord bei OuterList ... sicherheitshalber noch einmal aufrufen
//
//    Rev 1.113   09 Jun 1997 13:11:00   Hannes
//
//    Rev 1.112   13 May 1997 07:55:46   Hannes
//
//    Rev 1.111   13 Mar 1997 18:59:50   Hannes
// DoShowExtBlobChild
//
//    Rev 1.110   28 Feb 1997 14:44:22   Hannes
// Proptotyp von Multipro
//
//    Rev 1.109   19 Feb 1997 12:20:42   Hannes
// Ueberpruefen von Parents
//
//    Rev 1.108   29 Jan 1997 08:58:20   HANNES
// Verbesserung bei der Multiselektion bei Listen
//
//    Rev 1.107   15 Jan 1997 16:14:14   HANNES
// BindInnerListToOutList...Sicherheitshalber die Liste noch einmal lesen
//
//    Rev 1.106   12 Dec 1996 17:20:22   HANNES
//
//    Rev 1.105   12 Dec 1996 12:18:14   HANNES
// PaintFullHeader verbessert
//
//    Rev 1.104   05 Dec 1996 15:08:40   HANNES
//
//    Rev 1.103   03 Dec 1996 16:38:18   HANNES
// PaintFullHeader: auf cfields umgebaut
//
//    Rev 1.102   26 Nov 1996 08:14:14   HANNES
// Automatischer Update
//
//    Rev 1.101   08 Nov 1996 13:33:24   HANNES
// SetRec ... Neuer Prototyp
//
//    Rev 1.100   31 Oct 1996 16:08:04   HANNES
// Connections auf Listen: Eigene OwnerID
//
//    Rev 1.99   28 Oct 1996 08:38:04   HANNES
// Update beim EmptyInnerList
//
//    Rev 1.98   21 Oct 1996 18:48:50   HANNES
// Einbau von Aliasnamen in das Script
//
//    Rev 1.97   15 Oct 1996 17:37:14   GERHOLD
// lSetHeaderClkCallBack ... && (*lpIndex >= 0)  Index 0 ist gueltig!!
//
//    Rev 1.96   20 Sep 1996 17:56:20   MARTIN
// mode in Listen nur einmal lesen und merken
//
//    Rev 1.95   18 Sep 1996 20:46:20   HANNES
//
//    Rev 1.94   03 Sep 1996 10:00:48   HANNES
// Krankengeschichtseintraege beim Drucken zerteilt
//
//    Rev 1.93   16 Aug 1996 14:02:04   MARTIN
// DoHeaderClk: nur wenn Header da, auch checken
//
//    Rev 1.92   28 Jun 1996 14:33:56   GERHOLD
// HeaderClickCallBack ... Maus auf Listenheader erzeugt Funktionsaufruf
//
//    Rev 1.91   18 May 1996 20:37:52   HANNES
//
//    Rev 1.90   07 May 1996 16:16:12   HANNES
// SelectSubLine ... done == FALSE -> Daten restaurieren
//
//    Rev 1.89   07 May 1996 16:14:20   GERHOLD
// #pragma pack vor Strukturen, int far * => DBINT
//
//    Rev 1.88   06 May 1996 17:18:08   HANNES
// Nicht wiederholbare Elemente
//
//    Rev 1.87   06 May 1996 12:57:22   HANNES
// SubScrollen
//
//    Rev 1.86   19 Apr 1996 17:45:56   MARTIN
// DLL-Anbindung
//
//    Rev 1.85   27 Mar 1996 18:05:12   MARTIN
// ParamBlock.AnzPars
//
//    Rev 1.84   26 Mar 1996 18:50:16   MARTIN
// endpage: Parameter last
//
//    Rev 1.83   24 Mar 1996 12:08:38   HANNES
// mehrseitige cFields
//
//    Rev 1.82   22 Mar 1996 12:25:06   GERHOLD
// PaintFullHeader reagiert auf Update
//
//    Rev 1.81   04 Mar 1996 21:09:30   GERHOLD
// FrreProcInstance fuer WIN32 raus!
//
//    Rev 1.80   22 Feb 1996 10:28:36   MARTIN
// noch ein MakeProcInstance
//
//    Rev 1.79   16 Feb 1996 13:33:20   GERHOLD
// Multiselektion wird jetzt anders gezeichnet (mit Checkboxen(
// Hannes hat einen Haufen "myxxxxxxx"-Funktionen eingebaut
//
//    Rev 1.78   02 Feb 1996 10:34:58   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.77   10 Jan 1996 21:05:40   HANNES
//
//    Rev 1.76   19 Dec 1995 17:08:58   HANNES
// GetSelString variabel gross
//
//    Rev 1.75   15 Dec 1995 11:33:22   GERHOLD
// StringEntry::PaintLine ... Texte haben einen Abstand zu den Trennlinien
//
//    Rev 1.74   27 Nov 1995 17:26:30   GERHOLD
// _acttype, _actdlg sind ab jetzt initialisiert
//
//    Rev 1.73   23 Nov 1995 17:58:54   hannes
// Erweiterung in lRefreshList
//
//    Rev 1.72   20 Nov 1995 11:38:48   HANNES
//
//    Rev 1.71   16 Nov 1995 22:03:56   HANNES
// Drucken von Listen / Fehlerkorrektur
// lSetRefreshDirection raus
// Refresh - direction in den Modus rein
//
//    Rev 1.70   13 Nov 1995 18:45:54   HANNES
// Abfragen der Notwendigkeit eines Updates
// Updatesortierung: Updates auf Listeneintraege hinter den Updates auf
//   Parameter
//
//    Rev 1.69   25 Oct 1995 12:23:02   HANNES
// Aenderungen Hannes
//
//    Rev 1.68   19 Sep 1995 18:53:46   MARTIN
// Test-Script-Prozedur auch in LOInitialize aufgerufen
//
//    Rev 1.67   16 Sep 1995 02:06:02   HANNES
//
//    Rev 1.66   10 Sep 1995 10:49:10   HANNES
//
//    Rev 1.65   30 Aug 1995 11:01:34   HANNES
// SetExtraData fuer Listen ueberschrieben
//
//    Rev 1.64   24 Aug 1995 00:20:34   HANNES
// DBWIN_ASSERT
//
//    Rev 1.63   10 Aug 1995 09:27:00   HANNES
// Drucker - Funktionalitaet erweitert
//
//    Rev 1.62   02 Jul 1995 18:28:54   HANNES
// ClearConnection auf die Primaerschluesselsegmente bei lChangeSelection
//
//    Rev 1.61   09 Jun 1995 00:19:22   HANNES
// CSYSRECS
// Refreshlist fuer Speicherlisten verbessert
//
//    Rev 1.60   15 May 1995 08:27:50   HANNES
// Freigabe der verschiedenen Primaerschluessel
//
//    Rev 1.59   08 May 1995 17:13:16   HANNES
// Auch die Sortierungsaenderungen an die dblist weitergeben
//
//    Rev 1.58   02 May 1995 21:06:34   HANNES
// Keine Konstanten Breiten mehr verlangt
//
//    Rev 1.57   02 May 1995 13:50:02   HANNES
// CreateDlgList erweitert, Initialize wiederimplementiert
//
//    Rev 1.56   27 Apr 1995 15:37:30   HANNES
//
//    Rev 1.55   13 Apr 1995 12:54:28   HANNES
//
//    Rev 1.54   12 Apr 1995 12:26:16   HANNES
//
//    Rev 1.53   02 Apr 1995 14:10:40   HANNES
//
//    Rev 1.52   31 Mar 1995 18:23:16   HANNES
//
//
//    Rev 1.51   31 Mar 1995 13:09:26   HANNES
//
//
//    Rev 1.50   29 Mar 1995 16:22:26   HANNES
//
//    Rev 1.49   27 Mar 1995 13:17:08   HANNES
//
//
//    Rev 1.48   20 Mar 1995 11:56:14   HANNES
// Konstantenhanling, RunNmbr...
//
//    Rev 1.47   08 Mar 1995 09:14:48   HANNES
// Forschleifen u.a.
//
//    Rev 1.46   03 Mar 1995 18:12:26   HANNES
//
//    Rev 1.45   24 Feb 1995 11:17:16   HANNES
//
//
//    Rev 1.44   16 Feb 1995 12:52:08   HANNES
//
//    Rev 1.43   06 Feb 1995 16:52:34   HANNES
//
//    Rev 1.42   29 Jan 1995 11:50:24   HANNES
//
//    Rev 1.41   20 Jan 1995 15:54:56   HANNES
// Multiselektionen
//
//    Rev 1.40   15 Dec 1994 18:24:00   HANNES
// ThrowRecord raus, da ansonsten die Liste durcheinandergebracht wird
//
//    Rev 1.39   09 Dec 1994 19:45:04   HANNES
//
//    Rev 1.38   05 Dec 1994 17:42:52   HANNES
// Endgueltiger Einbau der Expressions
//
//    Rev 1.37   21 Nov 1994 20:40:14   HANNES
// Druck von Innerern Listen
//
//    Rev 1.36   19 Nov 1994 21:57:42   HANNES
//
//    Rev 1.35   19 Nov 1994 18:07:44   HANNES
//
//    Rev 1.34   19 Nov 1994 16:31:10   HANNES
// Eintragshoehe in stringlisten
//
//    Rev 1.33   18 Nov 1994 19:58:12   GERHOLD
// Drucken reaktiviert
//
//    Rev 1.32   11 Nov 1994 16:19:16   HANNES
// AddRecToInnerList -> In der Ausgabeliste ein Refresh
//
//    Rev 1.31   10 Nov 1994 14:28:30   HANNES
//
//    Rev 1.30   08 Nov 1994 12:43:42   HANNES
//
//    Rev 1.29   07 Nov 1994 11:23:56   HANNES
// - Doppelclick
// - Stackueberlauf bei Removeoldselection
// - FreeTableInd bei LoadInternList
//
//    Rev 1.28   31 Oct 1994 09:58:12   hannes
// Zusammenhang Innere Liste zu Anzeigeliste
// GetLineCount, EmptyInnerList
//
//    Rev 1.27   27 Oct 1994 15:09:10   GERHOLD
// Aenderungen in ShowDDSListBase (ProcToDel)
//
//    Rev 1.26   20 Oct 1994 06:01:52   hannes
// Verbesserung der ColumnList
//
//    Rev 1.25   19 Oct 1994 22:36:30   hannes
// Hoehenberechnung
//
//    Rev 1.24   05 Oct 1994 15:28:14   GERHOLD
//
//    Rev 1.23   22 Sep 1994 16:06:56   GERHOLD
// Notify-Codes fuer Farbaenderung
//
//    Rev 1.22   20 Sep 1994 11:37:20   HANNES
// LoadInnerList und andere Feinheiten
//
//    Rev 1.21   06 Sep 1994 08:47:56   HANNES
// LOODrawBottom .. nur bei i > 0 etwas unternehmen
//
//    Rev 1.20   05 Sep 1994 15:36:36   HANNES
// PaintFullHeader... Header fuer Listen
// ColumnList ... Ableitung von Stringlist zum Zeichnen von Spalten
// PaintFullBottom, PaintStdBottom
//
//    Rev 1.19   31 Aug 1994 15:41:08   HANNES
// Update in der MultiProcListe
//
//    Rev 1.18   30 Aug 1994 13:01:00   HANNES
// Notify
//
//    Rev 1.17   29 Aug 1994 15:27:20   HANNES
// DDSLIST_SETFOCUS (NULL) richtig behandelt
//
//    Rev 1.16   29 Aug 1994 12:45:26   HANNES
// lCallInInnerListFor ... Auch bei Update
//
//    Rev 1.15   26 Aug 1994 10:12:16   HANNES
// lCallDefSel, lSetFocusCallback
//
//    Rev 1.14   24 Aug 1994 19:44:12   HANNES
// ShowMPObjectList
//
//    Rev 1.13   19 Aug 1994 10:38:58   HANNES
//
//    Rev 1.12   17 Aug 1994 16:50:22   GERHOLD
// LoDrawHeader
//
//    Rev 1.11   16 Aug 1994 08:46:12   GERHOLD
// LODrawHeader
//
//    Rev 1.10   11 Aug 1994 11:16:14   HANNES
// DDSLIST_DESTROYLIST, ResetMap
//
//    Rev 1.9   10 Aug 1994 12:04:00   HANNES
// DDSLIST_SELCHANGE
//
//    Rev 1.8   05 Aug 1994 20:18:24   HANNES
// Selektion beim Update loeschen, Sicherheitshalber Fonts freigeben
//
//    Rev 1.7   05 Aug 1994 17:13:44   HANNES
// ShowObjectList, InnerList
//
//    Rev 1.6   17 Jul 1994 14:44:28   HANNES
// Primaerschluesselumorganisation
//
//    Rev 1.5   13 Jul 1994 21:15:02   HANNES
// LoadInternList und InstallProcForList vereinigt
// Refreshjoins aufgerufen
//
//    Rev 1.4   27 Jun 1994 16:30:44   HANNES
// Vaterfenster in dlglist
//
//    Rev 1.3   24 Jun 1994 20:47:06   HANNES
//
//    Rev 1.2   24 Jun 1994 20:01:22   HANNES
//
//    Rev 1.1   24 Jun 1994 19:50:58   MARTIN
//
//    Rev 1.0   24 Jun 1994 17:05:10   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#ifdef WIN32
#include <wingdi.h>
#else
#include <print.h>
#endif

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
#include "dllchild.hpp"

#include "cfield.hpp"
#include "frmobj.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "ddslist.hpp"

#include "winextra.hpp"
#define MODULENUM 100
#include "winass.hpp"

#include "oneshot.hpp"
#include "multipro.hpp"
#include "ddsmsg.h"

#include "list.hpp"

#define LIST_MAIN
#include "for.hpp"
#include "tbcbd.hpp"

extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
  #define MYINI GetIniName ()
#endif

class FAR PermListObj : public ListObj {
 public :
  PermListObj (mdiChild *doc) : ListObj (doc)
    { }
  virtual BOOL ConnectEntrys ()
    { return TRUE ; }
  };

class FAR StringListObj : public ListObj {
 public :
  StringListObj (mdiChild *doc) : ListObj (doc)
    { } ;
  int EntryHeight;
  LPINT tabx;
  LPINT w;
  int Format;
  int AnzDataToShow;

  virtual void DoInit ();
  virtual LPVOID UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam);

  LPSTR HeaderText;
  virtual ~StringListObj ()
    {
    if (tabx != NULL) FreeGlobMem (tabx) ;
    if (w    != NULL) FreeGlobMem (w) ;
    if (HeaderText != NULL) FreeGlobMem (HeaderText);
    }

  virtual BOOL ConnectEntrys ()
    { return TRUE ; }
  virtual BOOL IsStringList()
    { return TRUE ; }
  };
typedef StringListObj FAR *LPSTRINGLIST;

class FAR ColumnListObj : public StringListObj {
 public :
  ColumnListObj (mdiChild *doc) : StringListObj (doc)
    { }

  virtual LPVOID UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam);
  };

class FAR ObjectListObj : public ListObj {
 public :
  ObjectListObj (mdiChild *doc) ;

  MultiProc FAR *mp;
  virtual void DoInit ();

  virtual LPVOID UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam);

  virtual ~ObjectListObj ()
    {
    delete mp;
    }

  virtual BOOL ConnectEntrys ()
    { return TRUE ; }
  virtual BOOL IsObjectList()
    { return TRUE ; }
  };
typedef ObjectListObj FAR *LPOBJLIST;

class ListDoc : public mdiChild {
 public :
  virtual void LoadData ()
    {
    ExCute (EM_LOAD | EM_FIXCONNECTION);
    }
  virtual void Reset ()
    {
    ExCute (EM_RESET);
    }
  virtual ~ListDoc ()
    {
    if ((FrmObjectList FAR *) GetOutData()->_ObjectList)
      delete ((FrmObjectList FAR *) GetOutData()->_ObjectList);
    GetOutData()->_ObjectList = NULL;
    }
  ListDoc (LPSTR entName) : mdiChild (GetScriptEntry(entName))
    {
    GetOutData()->_ObjectList = LPVOID (new FrmObjectList (this));
    }
  WORD GetRecInd(WORD TableID);

  virtual BOOL IsSmallDoc()
    { return TRUE ; }
  virtual BOOL IsListDoc()
    { return TRUE ; }

  virtual void GetMinMax (BOOL forScreen = TRUE);
  int GetHeight (HDC hDC);
  };

void ListDoc::GetMinMax (BOOL forScreen)
  {
  RECT r;
  ((FrmObjectList FAR *) GetOutData()->_ObjectList)->GetMinMax (&r,forScreen);
  CopyRect (LPRECT(&GetOutData()->rcLogRect),&r);
  }

int ListDoc::GetHeight (HDC hDC)
  {
  PaintContext pc;
  if (hDC)
    pc.SetDC (hDC);
  else
    pc.GetContext (GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
  pc.LogicalTwips(0,0,GetOutData()->_scale);

  int res;
  float FAR *lpheight = (float FAR *) GetDocumentExtraData (DED_ENTRYHEIGHT);
  if (lpheight != NULL)
    DBWIN_ASSERT (*lpheight > float (0.0));

  if ((lpheight != NULL) && (*lpheight > float (0.0))) {
    int h = WorldToLog (*lpheight);
    res = pc.YLOGtoPHYS(h);
    }
  else {
    RECT r;
    pc.LogRecttoPhys (&r,LPRECT(&GetOutData()->rcLogRect));
    res = r.bottom - r.top + 1;
    }
  if (hDC)
    pc.ResetMap ();

  return res;
  }

WORD ListDoc::GetRecInd(WORD TableID)
  {
  for (WORD i = 0 ; i < schd->AnzTables ; i++)
    if (schd->TRef[i].TableNr == TableID) return i + CSYSRECS;
  DBWIN_ASSERT(FALSE);
  return CSYSRECS;
  }

struct ConnectionInfo {
  DWORD   varID;
  LPVOID Cmd;
  };

class FAR ScListEntry {
 public :
  ListObj FAR *lo;
  LPDBRECORD rec;
  OutParam FAR *lop;
  ConnectionInfo FAR *cInfo;
  virtual void CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam)
    { }
  virtual void UpdateListEntry (HDC hDC,int FAR *height)
    { }
  virtual void Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1)
    { }

  ScListEntry (LPDBRECORD r,OutParam FAR *op,ListObj FAR *o)
    {
    lo = o ;
    rec = r ;
    lop = op ;
    if (!lo->ConnectEntrys())
      rec->AvoidUpdates();
    }
  virtual ~ScListEntry ()
    {
#ifdef UEBERLEGT
    // Datensatz wieder freigeben
    if (!lo->IsOuterSet) lo->dblist->ThrowRecord (rec);
#endif
    }

  LPVOID operator new (size_t s)
    { return GetGlobMem (s); }
  void operator delete (LPVOID obj)
    { }   // Ja nix machen !, volle Absicht, der Eintrag wird von
          // DDSList verschoben und wieder geloescht !!!
  virtual int MySize ()
    {
    return sizeof(*this);
    }
  };

class FAR DocEntry : public ScListEntry {
 public :
  ListDoc *c;
  DocEntry (LPDBRECORD r,ListObj FAR *o) : ScListEntry (r,NULL,o)
    { }

  virtual void CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam);
  virtual void Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1);

  virtual ~DocEntry ()
    {
    c->Reset ();
    delete c;
    }
  };

class FAR StringEntry : public ScListEntry {
 public :
  LPSTR txt;
  StringEntry (LPDBRECORD r,ListObj FAR *o) : ScListEntry (r,NULL,o)
    { }

  virtual void CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam);
  virtual void UpdateListEntry (HDC hDC,int FAR *height);
  void PaintLine (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,BOOL PaintCols);
  virtual void Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1);

  virtual ~StringEntry ();
  };

class FAR ColumnEntry : public StringEntry {
 public :
  ColumnEntry (LPDBRECORD r,ListObj FAR *o) : StringEntry (r,o)
    { }

  virtual void Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1);
  };

struct FAR ObjectsOfEntry {
  ObjectsOfEntry FAR *Next;
  DWORD ref;
  LPFRMOBJ obj;
  };
typedef ObjectsOfEntry FAR *LPOOE;
class FAR ObjectEntry : public ScListEntry {
 protected :
  int type;
 public :
  LPOOE objects;
  LPOBJECTDATA mys;

  ObjectEntry (LPDBRECORD r,OutParam FAR *op,ListObj FAR *o) : ScListEntry (r,op,o)
    {
    type = 0 ;
    }

  LPFRMOBJ GetObj (DWORD ref);
  BOOL IsToPaint (LPFRMOBJ o,ObjectEntry FAR *prev,DWORD Ref);
  void AddToObjList (LPFRMOBJ h,DWORD ref);
  void RemoveObjList ();
  int  GetEntryHeight (HDC hDC,lPrint_param FAR *prParam);
  virtual void CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam);
  virtual void UpdateListEntry (HDC hDC,int FAR *height);
  virtual void Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1);

  virtual ~ObjectEntry ();
  virtual int MySize ()
    {
    return sizeof(*this);
    }
  };
class FAR HBObjectEntry : public ObjectEntry
  {
 public :
  HBObjectEntry (ListObj FAR *o) : ObjectEntry (NULL,NULL,o)
    { }
  void Create (HDC hDC,int FAR *height,lPrint_param FAR *prParam,LPOBJECTDATA s);
  virtual ~HBObjectEntry ();
  };

void DocEntry::Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1)
  {
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;
  if (doPrint) pc.mode = DO_PRINT ;
  c->GetOutData()->_xp = x , c->GetOutData()->_yp = y ; // Fuer ev. noch folgenden Update
  pc.LogicalTwips (x,y,c->GetOutData()->_scale);
  c->MapChanged ();          // sicherheitshalber allen Elementen
                             // noch einmal die Position neu setzen
                             // (duerfte nicht allzu aufwendig sein)
  if (c->GetOutData()->_ObjectList != NULL) {
    ((FrmObjectList FAR *) c->GetOutData()->_ObjectList)->Paint (&pc);
    }
  pc.mode = oldmode ;
  pc.ResetMap ();
  }

static LPPRIMKEY recTested2;
static BOOL inTest;
static LPVOID refreshInTest;
BOOL ListObj::TestRecord (LPDBRECORD r,OutParam FAR *op,DWORD procToTest,DWORD testFlag)
  {
  BOOL res = TRUE ;
  if (procToTest == 0L) {
    procToTest = TestProc;
    testFlag = TestRes;
    }
  if (procToTest != 0L) {
    inTest = TRUE;
    // DBWIN_ASSERT(r != NULL);
    DBBOOL FAR *lpres;
    if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
      // Den Funktionsdaten - Offset der Extradaten uebernehmen
      SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
      SAVEREC sr;
      c->SetRecsForUpdate (sr,ExtraDataAtCreation);

      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old;
      if (r != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (procToTest,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (procToTest,EM_RESET);
      if (r != NULL)
        c->rr->SetRecord (TableInd,old);
      lpres = (DBBOOL FAR *) c->ReadlData (testFlag);
      if (lpres != NULL) {
        res = *lpres ;
        if ((*lpres == 2) && (recTested2 == NULL)) recTested2 = r->GetPrimKey();
        }
      else
        res = FALSE ;
      c->RestoreRecs (sr);
      }
    else {
      RestoreListFnc rlf(c);
      LPDBRECORD old;
      if (r != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (procToTest,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (procToTest,EM_RESET);
      if (r != NULL)
        c->rr->SetRecord (TableInd,old);
      lpres = (DBBOOL FAR *) c->ReadlData (testFlag);
      if (lpres != NULL) {
        res = *lpres ;
        if ((*lpres == 2) && (recTested2 == NULL)) recTested2 = r->GetPrimKey();
        }
      else
        res = FALSE ;
      }
    inTest = FALSE;
    }
  return res ;
  }

#define  LEFTSPACE  50
void StringEntry::PaintLine (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,BOOL paintLines)
  {
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;
  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  GetResolutionCF (&cfact);
  pc.LogicalTwips (x,y,float(cfact));
  HFONT oldFont = (HFONT)SelectObject (hDC,GetFontHandle (0,MAPTYPE_TYPOGRAPHIC,
                                LPSTRINGLIST(lo)->Format,255
                                                )
                               );
  SetTextAlign (hDC,TA_TOP | TA_LEFT);
  int i = 0 ;
  char coltext[1024];
  BOOL collect_done = FALSE;
  LPSTR dest = coltext;
  LPSTR end = coltext + sizeof(coltext) - 1;
  LPSTR ttow,ttos;
  BOOL textdone = FALSE ;
  int hextra = pc.YPHYStoLOG(1);
  BOOL char_done ;
  for ( LPSTR h = txt ; *h ; i++) {
    if ((LPSTRINGLIST(lo)->w[i] == 0) || (collect_done)) {
      if ((collect_done) && (char_done) && (dest < end)) *dest++ = ' ' ;
      char_done = FALSE ;
      for ( LPSTR he = h ; (*he != '\t') ; he ++ )
        if (dest < end)
          *dest++ = *he , char_done = TRUE ;
      h = he + 1;
      *dest = '\0' ;
      if ((collect_done) && (LPSTRINGLIST(lo)->w[i] > 0)) {
        ttow = coltext ;
        ttos = dest ;
        dest = coltext ;
        collect_done = FALSE ;
        }
      else
        collect_done = TRUE ;
      }
    else {
      ttow = h ;
      for ( LPSTR he = h ; *he != '\t' ; he++) ;
      ttos = he ;
      h = he + 1 ;
      }
    if (LPSTRINGLIST(lo)->w[i] > 0) {
      *ttos = '\0';
      RECT r;
      r.top    = 0;
      r.bottom = LPSTRINGLIST(lo)->LogHeight;

      // den Text nicht ganz an der Zwischenlinie zeichnen
      r.left   = LPSTRINGLIST(lo)->tabx[i] + LEFTSPACE;
      r.right  = r.left + LPSTRINGLIST(lo)->w[i] - LEFTSPACE;
 
      ExtTextOut (hDC,r.left,r.top,ETO_CLIPPED | ETO_OPAQUE,&r,ttow,ttos - ttow,NULL);
      if ((textdone) && (paintLines)) {
        MoveToEx (hDC,LPSTRINGLIST(lo)->tabx[i],r.top, NULL);
        LineTo (hDC,LPSTRINGLIST(lo)->tabx[i],r.bottom + hextra);
        }
      textdone = TRUE ;
      *ttos = '\t';
      }
    }
  SelectObject (hDC,oldFont);
  pc.mode = oldmode ;
  pc.ResetMap ();
  }

void StringEntry::Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1)
  {
  PaintLine (hDC,x,y,doPrint,prParam,FALSE);
  }
void ColumnEntry::Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1)
  {
  PaintLine (hDC,x,y,doPrint,prParam,TRUE);
  }

BOOL ObjectEntry::IsToPaint (LPFRMOBJ o,ObjectEntry FAR *prev,DWORD Ref)
  {
  if (prev == NULL) return TRUE ;
  if (prev->lo->nro_p == NULL) return TRUE ;
  if (!prev->lo->nro_p->InList (Ref)) return TRUE ;
  LPFRMOBJ o1 = prev->GetObj (Ref);
  if (o1 == NULL) return TRUE ;
  if (!o->IsField()) return TRUE ;
  if (!o1->IsField()) return TRUE ;
  LPSTR t = LPFRMFIELD(o)->field->TextPtr();
  LPSTR t1 = LPFRMFIELD(o1)->field->TextPtr();
  if ((t == NULL) || (t1 == NULL)) return TRUE ;
  return lstrcmp(t,t1) ;
  }

static Printer FAR *_Listpr;
void ObjectEntry::Paint (HDC hDC,int x,int y,BOOL doPrint,lPrint_param FAR *prParam,ScListEntry FAR *prev,int y0,int y1)
  {
  if ((doPrint) && (y0 != y1)) {
    RECT rc;
    _Listpr -> GetPrinterArea (&rc);
    int extraOffs;
    if (lo->par->SubSelFollows(lo->c)) extraOffs = 0;
    else                               extraOffs = -100;
    HRGN hRgnClip = CreateRectRgn (rc.left + extraOffs,y0 + extraOffs,rc.right + 100,y1);
    SelectClipRgn (hDC,hRgnClip);
    DeleteObject (hRgnClip);
    }
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  pc.hWnd = lo->MyList->hWndList;
  GetClientRect (pc.hWnd,LPRECT (&pc.cr));

  WORD oldmode = pc.mode ;
  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  if ((prParam != NULL) || (lo->par->withNormalSize(lo->c)))
    cfact = 1.0 ;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (x,y,float(cfact));

  for (LPOOE o = objects ; o != NULL ; o = o->Next)
    if ((o->obj->Initialized) && (IsToPaint (o->obj,(ObjectEntry FAR *)prev,o->ref)))
      o->obj->Paint (&pc,0);

  pc.mode = oldmode ;
  pc.ResetMap ();
  if ((doPrint) && (y0 != y1))
    SelectClipRgn (pc.hDC,NULL);  // Clipping wieder aufheben
  }


void DrawHeaderFrame (HDC hDC, BOOL first, RECT r)
  {
  RECT rc1, rc2;

  rc1  = r;
  LPtoDP (hDC, LPPOINT(&rc1), 2);

  if (first)
    rc1.left = -1;

  rc2 = rc1;

  rc1.top--;

  if (!first) {
    rc2.left += 2;
    rc1.left += 1;
    }
  rc2.right -= 1;
  rc1.right += 1;
  rc2.bottom -= 2;
  DPtoLP (hDC, LPPOINT(&rc1), 2);
  DPtoLP (hDC, LPPOINT(&rc2), 2);

  // das wird das schwarze umgebende Rechteck
  HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
  Rectangle (hDC, rc1.left, rc1.top, rc1.right, rc1.bottom);
  SelectObject (hDC, OldBrush);
 
  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, rc2.right, rc2.top, NULL);
  LineTo (hDC, rc2.left, rc2.top);
  LineTo (hDC, rc2.left, rc2.bottom);
  SelectObject (hDC, OldPen);

  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  LineTo (hDC, rc2.right, rc2.bottom);
  LineTo (hDC, rc2.right, rc2.top);
  DeleteObject (SelectObject (hDC, OldPen));
  }

DLLExport void _export WINAPI LODrawHeader (HDC hDC,LPVOID bData,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  DBWIN_ASSERT(ol->IsStringList());
  StringListObj FAR *o = (StringListObj FAR *) ol;
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;

  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  if (o->par->withNormalSize(o->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (x,y,float(cfact));
  RECT r;
  int i = 0 ;
  BOOL first = TRUE ;
  for ( LPSTR h = o->HeaderText ; *h ; i++) {
    for ( LPSTR he = h ; *he != '\t' ; he++) ;
    *he = '\0';
    if (o->w[i]) {
      r.top    = 0;
      r.left   = o->tabx[i];
      r.right  = r.left + o->w[i];
      r.bottom = o->LogHeight * HEADER_RATIO;

      cField FAR *f = new cField (TRANSPARENT, o->Format, o->tabx[i] + 100, 0, o->w[i], 1, FALSE);
      f->SetWindow (ol->MyList->hWndList);
      f->SetScale (cfact,MAPTYPE_TYPOGRAPHIC);
      f->SetVOrg (0,0,0);
      *f = h;
      f->Paint(hDC,0,FALSE);
      delete f ;

      DrawHeaderFrame (hDC, first, r);
      first = FALSE ;
      }
 
    h = he + 1;
    *he = '\t';
    }

  // zeichnet vom letzen Eintrag bis zum Fensterrand noch einen Balken
  RECT rc;
  GetClientRect (ol->MyList->ListWnd(), &rc);
  LPtoDP (hDC, LPPOINT(&r), 2);
  r.left = r.right;
  r.right = rc.right;
  DPtoLP (hDC, LPPOINT(&r), 2);

  DrawHeaderFrame (hDC, FALSE , r);
 
  pc.ResetMap ();
  }

DLLExport void _export WINAPI LODrawBottom (HDC hDC,LPVOID bData,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  DBWIN_ASSERT(ol->IsStringList());
  StringListObj FAR *o = (StringListObj FAR *) ol;
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;

  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  if (o->par->withNormalSize(o->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);

  pc.LogicalTwips (x,0,float(cfact));
  RECT rc;
  GetClientRect (ol->MyList->ListWnd(), &rc);
  int i = 0 ;
  int top    = pc.YPHYStoLOG (y);
  int bottom = pc.YPHYStoLOG (rc.bottom);
  int xe = 0;

  int xold = -1 ;
  for ( LPSTR h = o->HeaderText ; *h ; i++) {
    for ( LPSTR he = h ; *he != '\t' ; he++) ;
    if ((o->tabx[i] > 0) && (o->tabx[i] != xold)) {
      MoveToEx (pc.hDC,o->tabx[i],top, NULL);
      LineTo (pc.hDC,o->tabx[i],bottom);
      xold = o->tabx[i] ;
      }
    xe = o->tabx[i] + o->w[i];
    h = he + 1;
    }
  MoveToEx (hDC,xe,top, NULL);
  LineTo (hDC,xe,bottom);
 
  pc.ResetMap ();
  }

//-----------------------------------------------------------------------------
// Zeichnet den Header fuer die ObjectListe
//-----------------------------------------------------------------------------
void HeaderPaintProc (ListObj FAR *ol,RECT FAR &r,int x0,int Format,double cfact,HDC hDC)
  {
  for ( int i = 0 ; i < ol->HdPar->AnzColumns() ; i++ ) {
    LPSTR h = LPSTR (ol->c->ReadlData (ol->HdPar->cd[i].Text)) ;
    if (h == NULL) h = "" ;
    r.top    = 0;
    r.left   = x0 ;
    DBINT w = *((DBINT FAR *) ol->c->ReadlData (ol->HdPar->cd[i].Width));
    if (w > 0) {
      int x1 = r.left + w;
      r.right  = x1 ;
      r.bottom = ol->LogHeight * HEADER_RATIO;

      cField FAR *f = new cField (TRANSPARENT, Format, x0 + 100, 0, w, ol->AnzahlHdZeilen, FALSE);
      f->SetWindow (ol->MyList->hWndList);
      f->SetScale (cfact,MAPTYPE_TYPOGRAPHIC);
      f->SetVOrg (0,0,0);
      *f = h;
      f->Paint(hDC,0,FALSE);
      delete f ;

      DrawHeaderFrame (hDC, i == 0, r);
      x0 = x1 ;
      }
    }
  }

#define ENTER(A) if (ol->ExtraDataAtCreation != NULL) { \
                    SAVEREC old; \
                    ol->c->SetRecsForUpdate (old,ol->ExtraDataAtCreation); \
                    SetExtraInfo s(ol->c,ol->ExtraDataAtCreation); \
                    A ; \
                    ol->c->RestoreRecs(old);  \
                    } \
                  else { \
                    RestoreListFnc rlf (ol->c);  \
                    A ; \
                    }

DLLExport void _export WINAPI LOODrawHeader (HDC hDC,LPVOID bData,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;

  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  if (ol->par->withNormalSize(ol->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (x,y,float(cfact));
  DBINT Format = *((DBINT FAR *) ol->c->ReadlData (ol->HdPar->Format));
  RECT r;
  int x0 = 0;

  ENTER (HeaderPaintProc (ol,r,x0,Format,cfact,hDC));

  // zeichnet vom letzen Eintrag bis zum Fensterrand noch einen Balken
  RECT rc;
  GetClientRect (ol->MyList->ListWnd(), &rc);
  LPtoDP (hDC, LPPOINT(&r), 2);
  r.left = r.right;
  r.right = rc.right;
  DPtoLP (hDC, LPPOINT(&r), 2);

  DrawHeaderFrame (hDC, FALSE , r);
 
  pc.ResetMap ();
  }

void BottomPaintProc (HDC hDC,LPVOID bData,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1,int x0,int top,int bottom)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  for ( int i = 0 ; i < ol->HdPar->AnzColumns () ; i++) {
    if (i > 0) {
      MoveToEx (hDC,x0,top, NULL);
      LineTo (hDC,x0,bottom);
      }
    DBINT w = *((DBINT FAR *) ol->c->ReadlData (ol->HdPar->cd[i].Width)) ;
    x0 += w ;
    }
  MoveToEx (hDC,x0,top, NULL);
  LineTo (hDC,x0,bottom);
  }

DLLExport void _export WINAPI LOODrawBottom (HDC hDC,LPVOID bData,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;

  if (doPrint) pc.mode = DO_PRINT ;
  double cfact;
  if (ol->par->withNormalSize(ol->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (x,0,float(cfact));
  RECT rc;
  GetClientRect (ol->MyList->ListWnd(), &rc);
  int top    = pc.YPHYStoLOG (y);
  int bottom = pc.YPHYStoLOG (rc.bottom);
  int x0 = 0;
 
  ENTER (BottomPaintProc (hDC,bData,pData,x,y,doPrint,prParam,y0,y1,x0,top,bottom));

  pc.ResetMap ();
  }

void DocEntry::CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  c = new ListDoc(LPSTR(lo->c->ReadlData(lo->par->pntcmd())));

  // Und schon kanns losgehen
  ///////////////////////////////
  c->GetOutData()->_MyHandle = lo->MyList->ListWnd();
                             // Den Objekten ein Fenster zur verfuegung
                             // stellen
  c->GetOutData()->_scale = float(1.0);

  c->rr->SetRec (rec,c->GetRecInd(rec->GetTableID()),c->DocumentID(),FALSE);
  c->LoadData ();
  c->GetMinMax ();
  *height = c->GetHeight (hDC);
  }

void StringEntry::UpdateListEntry (HDC hDC,int FAR *height)
  {
  char txtbuffer[512];
  LPSHOWDATA s = lo->sdata;

  LPSTR h = txtbuffer ;
  for (int i = 0 ; i < int (((StringListObj FAR *) lo)->AnzDataToShow) ; i++) {
    rec->GetOutTxt (h,HIWORD(s->v[i].ref));
    h += lstrlen(h);
    *h = '\t';
    h ++ ;
    }
  *h = '\0';
  h++ ;
  if (txt != NULL) FreeGlobMem (txt);
  txt = LPSTR (GetGlobMem (h-LPSTR(txtbuffer)));
  lmemcpy (txt,txtbuffer,h-LPSTR(txtbuffer));
  *height = LPSTRINGLIST(lo)->EntryHeight + 1;
  }

ConnectionInfo FAR *PushConnectionInfo (ConnectionInfo FAR *c,DWORD varID,
                                        LPVOID Cmd
                                       )
  {
  ConnectionInfo FAR *res;
  int ind;
  if (c != NULL) {
    res = (ConnectionInfo FAR *) (GetGlobMem (GetBlockSize(c) + sizeof(*res)));
    ind = GetBlockSize(c) / sizeof(*c);
    lmemcpy (res,c,GetBlockSize(c));
    FreeGlobMem (c);
    }
  else {
    res = (ConnectionInfo FAR *) (GetGlobMem (sizeof(*res)));
    ind = 0;
    }
  res[ind].varID      = varID;
  res[ind].Cmd        = Cmd;

  return res;
  }

void StringEntry::CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  char txtbuffer[512];
  LPSHOWDATA s = lo->sdata;

  LPSTR h = txtbuffer ;
  SetExtraInfo x(lo->c,rec->GetPrimKey(),0L);
  LPDBRECORD old = lo->c->rr->GetRecord(lo->TableInd);
  lo->c->rr->SetRecord(lo->TableInd,rec);
  lo->c->_ccount = PushBlock(lo->c->_ccount);
  for (int i = 0 ; i < ((StringListObj FAR *) lo)->AnzDataToShow ; i++) {
    rec->GetOutTxt (h,HIWORD(s->v[i].ref));
    lo->c->SetlConnection (s->v[i].ref,lo->par->ConnectionAddress());
    cInfo = PushConnectionInfo (cInfo,s->v[i].ref,lo->par->ConnectionAddress());
    h += lstrlen(h);
    *h = '\t';
    h ++ ;
    }
  lo->c->_ccount = PopBlock(lo->c->_ccount);
  *h = '\0';
  h++ ;
  txt = LPSTR (GetGlobMem (h-LPSTR(txtbuffer)));
  lmemcpy (txt,txtbuffer,h-LPSTR(txtbuffer));
  *height = LPSTRINGLIST(lo)->EntryHeight + 1;
  lo->c->rr->SetRecord(lo->TableInd,old);
  }

void ObjectEntry::AddToObjList (LPFRMOBJ h,DWORD ref)
  {
  LPOOE n = LPOOE (GetGlobMem (sizeof(*n)));
  n->obj = h;
  n->ref = ref;
  for (LPOOE FAR *x = &objects ; *x != NULL ; x = &(*x)->Next ) ;
  *x = n ;
  }

static ObjectEntry FAR *_ActObjectEntry;
void eAddToObjList (LPFRMOBJ h,DWORD ref)
  {
  if (h != NULL)
    _ActObjectEntry->AddToObjList (h,ref);
  }

LPFRMOBJ ObjectEntry::GetObj (DWORD ref)
  {
  for (LPOOE x = objects ; x != NULL ; x = x->Next ) {
    if (x->ref == ref)
      return x->obj;
    }
  return NULL;
  }

void ObjectEntry::RemoveObjList ()
  {
  for (LPOOE x = objects ; x != NULL ; ) {
    LPOOE n = x->Next ;
    FreeGlobMem (x);
    x = n;
    }
  objects = NULL ;
  }

int ObjectEntry::GetEntryHeight (HDC hDC,lPrint_param FAR *prParam)
  {
  PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                      // noch im Destruktor wird etwas gemacht

  if (hDC)
    pc.SetDC (hDC);
  else
    pc.GetContext (lo->MyList->ListWnd(),0xFFFF,0xFFFF,DO_WORK);
  double cfact;
  if ((prParam != NULL) || (lo->par->withNormalSize(lo->c)))
    cfact = 1.0 ;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (0,0,float(cfact));

  int res;
  float FAR *lpheight = (float FAR *) lo->c->GetDocumentExtraData (DED_ENTRYHEIGHT);
  if (lpheight == NULL) {
    RECT r;
    SetRectEmpty (&r);
    for (LPOOE o = objects ; o != NULL ; o = o->Next) {
      o->obj->GetMinMax ();
      if (o->obj->Initialized)
        o->obj->GetUnionRect (0,&r);
      }
    res = pc.YLOGtoPHYS (r.bottom) - 1; // Die Objekte nehmen ueblicherweise
                                        // ein Pixel dazu, damit
                                        // der Invalidate richtig hinhaut..
    }
  else {
    res = pc.YLOGtoPHYS (int (*lpheight));
    lo->c->RemoveDocumentExtraData (DED_ENTRYHEIGHT);
    }

  pc.ResetMap ();
  return res;
  }

void ListObj::SetOutParam (OutParam FAR *op)
  {
  for ( OutParam FAR *x = op ; x != NULL ; x = x->Next) {
    if (x->Data) c->WritelData ((par->Param())[x->parNum - 1],x->Data,GetBlockSize(x->Data),par->ConnectionAddress());
    else         c->DellData ((par->Param())[x->parNum - 1],par->ConnectionAddress());
    }
  }

static BOOL _fp;
void ObjectEntry::CreateListEntry (HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  _fp = FALSE;
  _ActObjectEntry = this;
  ObjectListObj FAR *olo = (ObjectListObj FAR *) lo ;
  LPOBJECTDATA s;
  double cfact;
  if (prParam != NULL) {
    s = prParam->DObjLine(lo->c);
    cfact = 1.0 ;
    }
  else {
    s = lo->objd;
    if (lo->par->withNormalSize(lo->c))
      cfact = 1.0;
    else
      GetResolutionCF (&cfact);
    }

  if (rec != NULL) {
    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);
    SetExtraInfo se (lo->c,rec->GetPrimKey(),(prParam == NULL) ? olo->mp->CorrOffs() : olo->mpp->CorrOffs());

    LPDBRECORD old = lo->c->rr->GetRecord(lo->TableInd);
    lo->c->rr->SetRecord (lo->TableInd,rec);

    if (prParam == NULL) {
      olo->mp->AddProc (rec->GetPrimKey());
      WORD mode = EM_LOAD | EM_CHANGETOTRUE ;
      if (lo->ConnectEntrys ())
        mode |= EM_FIXCONNECTION ;
      lo->c->_ccount = PushBlock(lo->c->_ccount);
      olo->mp->ExCuteFirst (mode,&se);
      lo->c->_ccount = PopBlock(lo->c->_ccount);
      }
    else {
      mys = s;
      olo->mpp->AddProc (rec->GetPrimKey());
      lo->c->_ccount = PushBlock(lo->c->_ccount);
      olo->mpp->ExCuteFirst (EM_LOAD,&se);
      lo->c->_ccount = PopBlock(lo->c->_ccount);
      }

    for (int i = 0 ; i < int (s->AnzObjects(lo->c)) ; i++) {
      LPFRMOBJ FAR *h = (LPFRMOBJ FAR *) lo->c->ReadlData (s->ref[i]);
      if ((h != NULL) && (*h != NULL))
        AddToObjList (*h,s->ref[i]);
      }
    *height = GetEntryHeight (hDC,prParam);

    lo->c->rr->SetRecord (lo->TableInd,old);
    }
  else {
    lo->SetOutParam (lop);
    PrimKey kop;
    kop.PushKeySeg (&lop,sizeof(lop));

    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);
    SetExtraInfo se (lo->c,(prParam == NULL) ? olo->mp->CorrOffs() : olo->mpp->CorrOffs());

    if (prParam == NULL) {
      olo->mp->AddProc (&kop);
      WORD mode = EM_LOAD | EM_CHANGETOTRUE ;
      if (lo->ConnectEntrys ())
        mode |= EM_FIXCONNECTION ;
      lo->c->_ccount = PushBlock(lo->c->_ccount);
      olo->mp->ExCuteFirst (mode,&se);
      lo->c->_ccount = PopBlock(lo->c->_ccount);
      }
    else {
      mys = s;
      olo->mpp->AddProc (&kop);
      lo->c->_ccount = PushBlock(lo->c->_ccount);
      olo->mpp->ExCuteFirst (EM_LOAD,&se);
      lo->c->_ccount = PopBlock(lo->c->_ccount);
      }

    for (int i = 0 ; i < int (s->AnzObjects(lo->c)) ; i++) {
      LPFRMOBJ FAR *h = (LPFRMOBJ FAR *) lo->c->ReadlData (s->ref[i]);
      if ((h != NULL) && (*h != NULL))
        AddToObjList (*h,s->ref[i]);
      }
    *height = GetEntryHeight (hDC,prParam);
    }
  }

void HBObjectEntry::Create (HDC hDC,int FAR *height,lPrint_param FAR *prParam,LPOBJECTDATA s)
  {
  _ActObjectEntry = this;
  ObjectListObj FAR *olo = (ObjectListObj FAR *) lo ;
  double cfact = 1.0 ;
  mys = s ;

  PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);
  WORD mode = EM_LOAD | EM_CHANGETOTRUE ;
  RestoreListFnc rlf(olo->c);
  olo->c->ExCuteProc (s->ProcToCall,mode);
  for (int i = 0 ; i < int (s->AnzObjects(lo->c)) ; i++) {
    LPFRMOBJ FAR *h = (LPFRMOBJ FAR *) lo->c->ReadlData (s->ref[i]);
    if ((h != NULL) && (*h != NULL))
      AddToObjList (*h,s->ref[i]);
    }
  *height = GetEntryHeight (hDC,prParam);
  }
HBObjectEntry::~HBObjectEntry ()
  {
  _ActObjectEntry = this;
  double cfact = 1.0;
  PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);

  RestoreListFnc rlf(lo->c);
  lo->c->ExCuteProc (mys->ProcToCall,EM_RESET);
  }
void ObjectEntry::UpdateListEntry (HDC hDC,int FAR *height)
  {
  _ActObjectEntry = this;
  ObjectListObj FAR *olo = (ObjectListObj FAR *) lo ;
  LPOBJECTDATA s = lo->objd;

  double cfact;
  if (lo->par->withNormalSize(lo->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);
  if (rec != NULL) {
    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);
    LPDBRECORD old = lo->c->rr->GetRecord (lo->TableInd);
    lo->c->rr->SetRecord (lo->TableInd,rec);
    SetExtraInfo se (lo->c,rec->GetPrimKey(),olo->mp->CorrOffs());

    RemoveObjList ();

    lo->c->_ccount = PushBlock(lo->c->_ccount);
    olo->mp->ExCute (rec->GetPrimKey(),EM_UPDATE,&se);
    lo->c->_ccount = PopBlock(lo->c->_ccount);

    for (int i = 0 ; i < int (s->AnzObjects(lo->c)) ; i++) {
      LPFRMOBJ FAR *h = (LPFRMOBJ FAR *) lo->c->ReadlData (s->ref[i]);
      if ((h != NULL) && (*h != NULL))
        AddToObjList (*h,s->ref[i]);
      }

    *height = GetEntryHeight (hDC,NULL);
    lo->c->rr->SetRecord (lo->TableInd,old);
    }
  else {
    lo->SetOutParam (lop);
    PrimKey kop;
    kop.PushKeySeg (&lop,sizeof(lop));

    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),lo->MyList->ListWnd(),0,0,cfact);
    SetExtraInfo se (lo->c,olo->mp->CorrOffs());

    RemoveObjList ();

    lo->c->_ccount = PushBlock(lo->c->_ccount);
    olo->mp->ExCute (&kop,EM_UPDATE,&se);
    lo->c->_ccount = PopBlock(lo->c->_ccount);

    for (int i = 0 ; i < int (s->AnzObjects(lo->c)) ; i++) {
      LPFRMOBJ FAR *h = (LPFRMOBJ FAR *) lo->c->ReadlData (s->ref[i]);
      if ((h != NULL) && (*h != NULL))
        AddToObjList (*h,s->ref[i]);
      }

    *height = GetEntryHeight (hDC,NULL);
    }
  }
StringEntry::~StringEntry ()
  {
  lo->ResetOldSelection (rec);
  int AnzConnections = GetBlockSize(cInfo) / sizeof (*cInfo);
  LPDBRECORD old = lo->c->rr->GetRecord(lo->TableInd);
  lo->c->rr->SetRecord(lo->TableInd,rec);
  SetExtraInfo se (lo->c,rec->GetPrimKey(),0L);
  lo->c->_ccount = PushBlock(lo->c->_ccount);
  for (int i = 0 ; i < AnzConnections ; i++) {
    lo->c->ClearlConnection (cInfo[i].varID,cInfo[i].Cmd);
    }
  lo->c->_ccount = PopBlock(lo->c->_ccount);
  lo->c->rr->SetRecord(lo->TableInd,old);
  FreeGlobMem (txt);
  FreeGlobMem (cInfo);
  }

ObjectEntry::~ObjectEntry ()
  {
  ObjectListObj FAR *olo = (ObjectListObj FAR *) lo ;
  HWND hWnd = lo->MyList->ListWnd();
  WORD mode;
  if (!IsWindow (hWnd)) {
    hWnd = WBase::hFrameWin;
    mode = EM_RESET ;
    }
  else
    mode = EM_RESET | EM_CLEAR ;

  double cfact;
  if (olo->par->withNormalSize(olo->c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);

  if (rec != NULL) {
    lo->ResetOldSelection (rec);

    LPDBRECORD old = lo->c->rr->GetRecord(lo->TableInd);
    lo->c->rr->SetRecord (lo->TableInd,rec);

    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),hWnd,0,0,cfact);
    SetExtraInfo se (lo->c,rec->GetPrimKey(),(mys == NULL) ? olo->mp->CorrOffs() : olo->mpp->CorrOffs());

    _ActObjectEntry = this;
    if (mys == NULL) {
      olo->c->_ccount = PushBlock(olo->c->_ccount);
      olo->mp->ExCute (rec->GetPrimKey(),mode,&se);
      olo->c->_ccount = PopBlock(olo->c->_ccount);
      olo->mp->Remove (rec->GetPrimKey());
      }
    else {
      olo->c->_ccount = PushBlock(olo->c->_ccount);
      olo->mpp->ExCute (rec->GetPrimKey(),EM_RESET,&se);
      olo->c->_ccount = PopBlock(olo->c->_ccount);
      olo->mpp->Remove (rec->GetPrimKey());
      }

    lo->c->rr->SetRecord (lo->TableInd,old);
    }
  else if (lop != NULL) {
    PrepareListFunction p (DWORD(lo->dblist),lo->c,lo->par->ConnectionAddress(),hWnd,0,0,cfact);
    SetExtraInfo se (lo->c,(mys == NULL) ? olo->mp->CorrOffs() : olo->mpp->CorrOffs());

    PrimKey kop;
    kop.PushKeySeg (&lop,sizeof(lop));

    _ActObjectEntry = this;
    if (mys == NULL) {
      olo->c->_ccount = PushBlock(olo->c->_ccount);
      olo->mp->ExCute (&kop,mode,&se);
      olo->c->_ccount = PopBlock(olo->c->_ccount);
      olo->mp->Remove (&kop);
      }
    else {
      olo->c->_ccount = PushBlock(olo->c->_ccount);
      olo->mpp->ExCute (&kop,EM_RESET,&se);
      olo->c->_ccount = PopBlock(olo->c->_ccount);
      olo->mpp->Remove (&kop);
      }
    }

  RemoveObjList ();
  }

void StringListObj::DoInit ()
  {
  sdata = par->DShow(c);
  LPSHOWDATA s = sdata;
  Format = *((DBINT FAR *) c->ReadlData (s->Format)) ;
  AnzDataToShow = *((DBINT FAR *) c->ReadlData (s->AnzDataToShow));
  DBWIN_ASSERT (AnzDataToShow >= 0);
  PaintContext pc(WBase::hFrameWin,0xFFFF,0xFFFF,DO_WORK);
  double cfact;
  GetResolutionCF (&cfact);
  pc.LogicalTwips(0,0,float(cfact));
  HFONT oldFont = (HFONT)SelectObject (pc.hDC,GetFontHandle(0,MAPTYPE_TYPOGRAPHIC,Format,255));

#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (pc.hDC,"Gg",2, &size);
  LogHeight = size.cy;
#else
  LogHeight = HIWORD(GetTextExtent (pc.hDC,"Gg",2));
#endif

  EntryHeight = pc.YLOGtoPHYS (LogHeight);

  SelectObject (pc.hDC,oldFont);
  tabx = LPINT (GetGlobMem (AnzDataToShow * sizeof(int)));
  w    = LPINT (GetGlobMem (AnzDataToShow * sizeof(int)));
  tabx[0] = 0;
  DBWIN_ASSERT (c->IsConst (s->v[0].width));
  DBINT wa  = *((DBINT FAR *) c->ReadlData (s->v[0].width));
  w[0]    = wa;
  for (int i = 1 ; i < AnzDataToShow ; i++) {
    DBWIN_ASSERT (c->IsConst (s->v[i].width));
    w[i] = c->ReadConstInt (s->v[i].width);
    tabx[i] = tabx[i-1] + w[i-1];
    }
  }

ObjectListObj::ObjectListObj (mdiChild *doc) : ListObj (doc)
  {
  }

void ObjectListObj::DoInit ()
  {
  objd = par->DObj(c);
  LPOBJECTDATA s = objd;
  DBWIN_ASSERT (s->AnzObjects(c) >= 0);
  mp = new MultiProc (c,s->ProcToCall,TRUE);
  }

#define MAXTYPES 32
DLLExport void _export WINAPI LODrawItem (HDC hDC,LPVOID Data,LPVOID pData,int x,int y,BOOL doPrint,LPVOID prParam,int y0,int y1)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  e->Paint (hDC,x,y,doPrint,(lPrint_param FAR *)prParam,(ScListEntry FAR *) pData,y0,y1);
  if ((doPrint) && (_fp))
    e->lo->MyList->ForceNextPage = TRUE ;
  }

DLLExport BOOL _export WINAPI LOCompareData (LPVOID Data1,LPVOID Data2,BOOL Data1Full)
  {
  if (Data1Full) {
    ScListEntry FAR *e1 = (ScListEntry FAR *) Data1;
    ScListEntry FAR *e2 = (ScListEntry FAR *) Data2;
    if (e1->rec)
      return (*e1->rec->GetPrimKey() == *e2->rec->GetPrimKey());
    else {
      return e1->lop == e2->lop;
      }
    }
  else {
    PrimKey s;
    s.PushKeySeg (Data1,GetBlockSize(Data1));
    ScListEntry FAR *e = (ScListEntry FAR *) Data2;
    if (e->rec)
      return (*e->rec->GetPrimKey() == s);
    else {
      PrimKey s2;
      s2.PushKeySeg (&e->lop,sizeof(e->lop));
      return (s2 == s);
      }
    }
  }

BOOL firstcmp (LPSTR s1,LPSTR s2)
  {
  for ( ; ((*s1 == *s2) && (*s2) && (*s1)) ; s1 ++ , s2 ++ ) ;
  return !*s2;
  }

BOOL CheckAccess (LPSTR where)
  {
  return firstcmp (where,"SELECT") ;
  }

DLLExport void _export WINAPI LOGetHeader (LPVOID bData,HDC hDC,int FAR *height)
  {
  ListObj FAR *o = (ListObj FAR *) bData;
  StringListObj FAR *so = (StringListObj FAR *) o;
  DBWIN_ASSERT(o->IsStringList());
  if (hDC == 0) {
    PaintContext pc(o->MyList->ListWnd(),0xFFFF,0xFFFF,DO_WORK);
    double cfact;
    GetResolutionCF (&cfact);
    pc.LogicalTwips (0,0,float(cfact));
    HFONT oldFont = (HFONT)SelectObject (pc.hDC,GetFontHandle(0,MAPTYPE_TYPOGRAPHIC,so->Format,255));

#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (pc.hDC,"Gg",2, &size);
  o->LogHeight = size.cy;
#else
  o->LogHeight = HIWORD(GetTextExtent (pc.hDC,"Gg",2));
#endif
    *height = pc.YLOGtoPHYS (o->LogHeight * HEADER_RATIO);
    SelectObject (pc.hDC,oldFont);
    }
  }

int AnzahlZeilen (ListObj FAR *ol)
  {
  int res = 0;
  for ( int i = 0 ; i < ol->HdPar->AnzColumns() ; i++ ) {
    LPSTR h = LPSTR (ol->c->ReadlData (ol->HdPar->cd[i].Text)) ;
    if (h == NULL) h = "" ;
    int ar = 0 ;
    for (LPSTR x = h ; (*x) ; x ++ ) {
      if (*x == '\r') ar = ar + 1;
      }
    if (ar > res) res = ar;
    }
  return res + 1;
  }

DLLExport void _export WINAPI LOOGetHeader (LPVOID bData,HDC hDC,int FAR *height)
  {
  ListObj FAR *ol = (ListObj FAR *) bData;
  if (hDC == 0) {
    PaintContext pc(ol->MyList->ListWnd(),0xFFFF,0xFFFF,DO_WORK);
    double cfact;
    if (ol->par->withNormalSize(ol->c))
      cfact = 1.0;
    else
      GetResolutionCF (&cfact);
    pc.LogicalTwips (0,0,float(cfact));
    DBINT Format = *((DBINT FAR *) ol->c->ReadlData (ol->HdPar->Format));
    HFONT oldFont = (HFONT)SelectObject (pc.hDC,GetFontHandle(0,MAPTYPE_TYPOGRAPHIC,Format,255));

    ENTER (ol->AnzahlHdZeilen = AnzahlZeilen (ol));

#ifdef WIN32
    SIZE size;
    GetTextExtentPoint32 (pc.hDC,"Gg",2, &size);
    ol->LogHeight = ol->AnzahlHdZeilen * size.cy;
#else
    ol->LogHeight = HIWORD(GetTextExtent (pc.hDC,"Gg",2));
#endif
    *height = pc.YLOGtoPHYS (ol->LogHeight * HEADER_RATIO);

    SelectObject (pc.hDC,oldFont);
    }
  }

DLLExport int _export WINAPI LOGetScrollPos (LPVOID Data)
  {
  return 0;
  }

DLLExport LPVOID _export WINAPI LOSetScrollPos (LPVOID bData,int Pos,int FAR *height)
  {
  DBWIN_ASSERT (FALSE);
  return NULL;
  }

DLLExport LPVOID _export WINAPI LOInitialize (LPVOID Data,LPVOID bData,HDC hDC,int FAR *height,LPVOID prParam)
  {
  PrimKey FAR *ki = (PrimKey FAR *) Data;
  ListObj FAR *o = (ListObj FAR *) bData;
  for ( LPDBRECORD rn = o->dblist->GetFirst ();
        ((rn != NULL) && !(*(rn->GetPrimKey ()) == *ki)) ;
        rn = o->dblist->GetNext (rn) ) ;
 
  if (rn != NULL) {
    if (o->TestRecord (rn,NULL))
      return o->UseRecord (rn,NULL,hDC,height,(lPrint_param FAR *)prParam);
    else {
      o->RemoveSelKey (rn->GetPrimKey());
      o->dblist->MarkRecordUnused (rn);
      return NULL;
      }
    }
  else
    return NULL;
  }

DLLExport LPVOID _export WINAPI LOUpdate (LPVOID Data,HDC hDC,int FAR *height,LPVOID prParam,DWORD utp,DWORD utf)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  if (e->lo->TestRecord (e->rec,e->lop,utp,utf)) {
    e->UpdateListEntry (hDC,height);
    return e;
    }
  else if (utp == 0L) {
    if (e->rec) {
      e->lo->RemoveSelKey (e->rec->GetPrimKey());
      e->lo->dblist->MarkRecordUnused (e->rec);
      }
    return NULL ;
    }
  else
    return e;
  }

DLLExport LONG _export WINAPI LOProcessMsg (HWND hWnd,UINT msg,WPARAM wP,
                                LPARAM lP,BOOL FAR *done)
  {
  return 0L;
  }

extern int Rand (mdiChild *c,DWORD id);
DLLExport void _export WINAPI LOPrintHead (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID param)
  {
  // Seiten - Daten in die Extradaten schreiben, damit das Script
  // eventuell darauf zugreifen kann ....
  ///////////////////////////////////////////////////////////////
  ListObj FAR *o = (ListObj FAR *) bData;
  int s = PageNr + 1;
  o->c->PutDocumentExtraData (DED_PRSIDE,&s,sizeof(s));
  RECT rpold,rp;
  o->c->DrawContext()->GetOutData()->Pr->PaperSize (&rpold);
  o->c->DrawContext()->GetOutData()->Pr->SetPrinterArea (&rpold);
  lPrint_param FAR *par = (lPrint_param FAR *) param;
  if ((o->ExtraDataAtCreation != NULL) && (o->ExtraDataAtCreation->fOffs != 0L)) {
    SetExtraInfo s (o->c,DWORD (0),o->ExtraDataAtCreation->fOffs);
    SAVEREC sr;
    o->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);
    o->c->ExCuteProc (par->printProc,EM_LOAD | EM_CHANGETOTRUE);
    o->c->ExCuteProc (par->printProc,EM_RESET | EM_CLEAR);
    o->c->RestoreRecs (sr);
    }
  else {
    o->c->ExCuteProc (par->printProc,EM_LOAD | EM_CHANGETOTRUE);
    o->c->ExCuteProc (par->printProc,EM_RESET | EM_CLEAR);
    }

  o->c->RemoveDocumentExtraData (DED_PRSIDE);
  o->c->RemoveDocumentExtraData (DED_PRANZSIDE);

  CopyRect (&rp,&rpold);
  {
  PaintContext pc(o->c->DrawContext()->GetOutData()->Pr);
  pc.Map (1.0);
  rp.left  += pc.XLOGtoPHYS(Rand(o->c,par->xLeft));
  rp.top   -= pc.YLOGtoPHYS(Rand(o->c,par->yTop));
  rp.right -= pc.XLOGtoPHYS(Rand(o->c,par->xRight));
  rp.bottom += pc.YLOGtoPHYS(Rand(o->c,par->yBottom));
  }
  o->c->DrawContext()->GetOutData()->Pr->SetPrinterArea (&rp);
  *h = 0 ;
  }

DLLExport void _export WINAPI LOStartPage (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID param)
  {
  ListObj FAR *o = (ListObj FAR *) bData;
  lPrint_param FAR *par = (lPrint_param FAR *) param;

  HBObjectEntry FAR *e = new HBObjectEntry (o);
  if ((o->ExtraDataAtCreation != NULL) && (o->ExtraDataAtCreation->fOffs != 0L)) {
    SetExtraInfo s (o->c,DWORD (0),o->ExtraDataAtCreation->fOffs);
    SAVEREC sr;
    o->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);
    e->Create (hDC,h,par,par->DObjHeader(o->c));
    o->c->RestoreRecs (sr);
    }
  else {
    e->Create (hDC,h,par,par->DObjHeader(o->c));
    }
  e->Paint (hDC,x,y,TRUE,par,NULL,0,0);
  delete e ;
  FreeGlobMem (e);
  }
DLLExport void _export WINAPI LOEndPage (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID param, BOOL last)
  {
  ListObj FAR *o = (ListObj FAR *) bData;
  lPrint_param FAR *par = (lPrint_param FAR *) param;

  HBObjectEntry FAR *e = new HBObjectEntry (o);
  if (par->LastEndPageFlagGiven(o->c)) {
    WORD IsLastEndPage = last;
    o->c->WritelData(par->LastEndPageFlagRef(o->c),&IsLastEndPage,sizeof(IsLastEndPage),NULL);
    }
  if ((o->ExtraDataAtCreation != NULL) && (o->ExtraDataAtCreation->fOffs != 0L)) {
    SetExtraInfo s (o->c,DWORD (0),o->ExtraDataAtCreation->fOffs);
    SAVEREC sr;
    o->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);
    e->Create (hDC,h,par,par->DObjBottom(o->c));
    o->c->RestoreRecs (sr);
    }
  else {
    e->Create (hDC,h,par,par->DObjBottom(o->c));
    }
  e->Paint (hDC,x,y,TRUE,par,NULL,0,0);
  delete e ;
  FreeGlobMem (e);
  }

DLLExport BOOL _export WINAPI LOIsSelected (LPVOID Data)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  if (e->rec)
    return e->lo->IsKeySelected (e->rec->GetPrimKey());
  else {
    PrimKey k;
    k.PushKeySeg (&e->lop,sizeof(e->lop));
    return e->lo->IsKeySelected (&k);
    }
  return FALSE ;
  }

DLLExport void _export WINAPI LOPrintBottom (LPVOID bData, HDC hDC, int x, int y, int w, int FAR* h, int PageNr, LPVOID param)
  {
  *h = 0 ;
  }

LPVOID ListObj::UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  DBWIN_ASSERT (prParam == NULL);
  DocEntry FAR *n = new DocEntry (h,this);
  n->CreateListEntry (hDC,height,prParam);
  return n;
  }

LPVOID StringListObj::UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  DBWIN_ASSERT (prParam == NULL);
  StringEntry FAR *n = new StringEntry (h,this);
  n->CreateListEntry (hDC,height,prParam);
  return n;
  }

LPVOID ColumnListObj::UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  DBWIN_ASSERT (prParam == NULL);
  ColumnEntry FAR *n = new ColumnEntry (h,this);
  n->CreateListEntry (hDC,height,prParam);
  return n;
  }

LPVOID ObjectListObj::UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam)
  {
  ObjectEntry FAR *n = new ObjectEntry (h,op,this);
  if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
    // Den Funktionsdaten - Offset der Extradaten uebernehmen
    SAVEREC sr;
    c->SetRecsForUpdate (sr,ExtraDataAtCreation);
    SetExtraInfo s (c,ExtraDataAtCreation);
    n->CreateListEntry (hDC,height,prParam);
    c->RestoreRecs (sr);
    }
  else
    n->CreateListEntry (hDC,height,prParam);
  return n;
  }

DLLExport LPVOID _export WINAPI LOGetNext (LPVOID Data,HDC hDC,int FAR *height,LPVOID prParam)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  if (!e->lo->useSimpleList) {
    LPDBRECORD rn ;
    for ( rn = e->lo->dblist->GetNext (e->rec);
            (rn != NULL) ;
                rn = e->lo->dblist->GetNext (rn) ) {
      if (e->lo->TestRecord (rn,NULL)) break ;
      else {
        e->lo->RemoveSelKey (rn->GetPrimKey());
        e->lo->dblist->MarkRecordUnused (rn);
        }
      }
    if (rn != NULL)
      return e->lo->UseRecord (rn,NULL,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  else {
    OutParam FAR *op ;
    for ( op = ((DBList FAR *) e->lo->dblist)->GetNextParam (e->lop);
            (op != NULL) ;
                op = ((DBList FAR *) e->lo->dblist)->GetNextParam (op) ) {
      if (e->lo->TestRecord (NULL,op)) break ;
      }
    if (op != NULL)
      return e->lo->UseRecord (NULL,op,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  }

DLLExport BOOL _export WINAPI LOSelectSubLines (int dir,int FAR *y1,int FAR *y2,HDC hDC,BOOL firstOfEntry,LPVOID bData,LPVOID lData,BOOL forPrinter)
  {
  ObjectEntry FAR *oe = (ObjectEntry FAR *) bData;
  SelectSubLines_Data FAR *d = (SelectSubLines_Data FAR *) lData ;
  SelectSubLines_Data bck = *d ;
  BOOL done = FALSE ;
  if (firstOfEntry) {
    // Neu am Anfang oder am Ende einsetzen
    if (dir > 0) {
      d->LineNmbr = 0 ;
      for ( d->ObjNmbr = 0 ; ((!done) && (d->ObjNmbr < oe->lo->slo_p->AnzFlds())) ; ) {
        LPFRMOBJ h = oe->GetObj (oe->lo->slo_p->flds[d->ObjNmbr]);
        if ((h != NULL) && (!done)) {
          WIN_ASSERT (h->IsField ());
          done = LPFRMFIELD(h)->field->ZeilenGrenze (d->LineNmbr,y1,y2) ;
          }
        if (!done)
          d->ObjNmbr ++ ;
        }
      }
    else {
      for ( d->ObjNmbr = oe->lo->slo_p->AnzFlds() - 1 ; ((!done) && (d->ObjNmbr >= 0)) ; ) {
        LPFRMOBJ h = oe->GetObj (oe->lo->slo_p->flds[d->ObjNmbr]);
        if ((h != NULL) && (!done)) {
          WIN_ASSERT (h->IsField ());
          for ( int l = 0 ; ; ) {
            int myY1,myY2;
            BOOL myDone = LPFRMFIELD(h)->field->ZeilenGrenze (l,&myY1,&myY2);
            if (myDone) {
              done = TRUE ;
              *y1 = myY1 ;
              *y2 = myY2 ;
              d->LineNmbr = l ;
              l ++ ;
              }
            else
              break ;
            }
          }
        if (!done) d->ObjNmbr -- ;
        }
      }
    }
  else {
    if (d->ObjNmbr < 0) d->ObjNmbr = 0 ;
    if (d->ObjNmbr >= oe->lo->slo_p->AnzFlds()) d->ObjNmbr = oe->lo->slo_p->AnzFlds() - 1;
    if (dir > 0) {
      // Weiterschalten
      for ( d->LineNmbr ++ ; ((!done) && (d->ObjNmbr < oe->lo->slo_p->AnzFlds())) ; ) {
        LPFRMOBJ h = oe->GetObj (oe->lo->slo_p->flds[d->ObjNmbr]);
        if ((h != NULL) && (!done)) {
          WIN_ASSERT (h->IsField ());
          done = LPFRMFIELD(h)->field->ZeilenGrenze (d->LineNmbr,y1,y2) ;
          }
        if (!done)
          d->LineNmbr = 0 , d->ObjNmbr ++ ;
        }
      }
    else {
      // Zurueckschalten
      for ( d->LineNmbr -- ; ((!done) && (d->ObjNmbr >= 0)) ; ) {
        if (d->LineNmbr < 0) {
          d->ObjNmbr -- ;
          if (d->ObjNmbr >= 0) {
            LPFRMOBJ h = oe->GetObj (oe->lo->slo_p->flds[d->ObjNmbr]);
            if ((h != NULL) && (!done)) {
              WIN_ASSERT ((h)->IsField ());
              for ( int l = 0 ; ; ) {
                int myY1,myY2;
                BOOL myDone = LPFRMFIELD(h)->field->ZeilenGrenze (l,&myY1,&myY2);
                if (myDone) {
                  done = TRUE ;
                  *y1 = myY1 ;
                  *y2 = myY2 ;
                  d->LineNmbr = l ;
                  l ++ ;
                  }
                else
                  break ;
                }
              }
            }
          }
        else {
          LPFRMOBJ h = oe->GetObj (oe->lo->slo_p->flds[d->ObjNmbr]);
          done = LPFRMFIELD(h)->field->ZeilenGrenze (d->LineNmbr,y1,y2);
          }
        }
      }
    }
  if (done) {
    // Echte Hoehe berechnen
    PaintContext pc;    // void Konstruktor -> Weder im Konstruktor
                        // noch im Destruktor wird etwas gemacht

    pc.SetDC (hDC);
    double cfact;
    if (forPrinter)
      cfact = 1.0 ;
    else
      GetResolutionCF (&cfact);
    pc.LogicalTwips (0,0,float(cfact));
    *y1 = pc.YLOGtoPHYS(*y1);
    *y2 = pc.YLOGtoPHYS(*y2);
    }
  else
    *d = bck ;
  return done ;
  }

DLLExport LPVOID _export WINAPI LOGetPrev (LPVOID Data,HDC hDC,int FAR *height,LPVOID prParam)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  if (!e->lo->useSimpleList) {
    LPDBRECORD rn ;
    for ( rn = e->lo->dblist->GetPrev (e->rec);
            (rn != NULL) ;
                rn = e->lo->dblist->GetPrev (rn) ) {
      if (e->lo->TestRecord (rn,NULL)) break ;
      else {
        e->lo->RemoveSelKey (rn->GetPrimKey());
        e->lo->dblist->MarkRecordUnused (rn);
        }
      }
    if (rn != NULL)
      return e->lo->UseRecord (rn,NULL,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  else {
    OutParam FAR *op ;
    for ( op = ((DBList FAR *) e->lo->dblist)->GetPrevParam (e->lop);
            (op != NULL) ;
                op = ((DBList FAR *) e->lo->dblist)->GetPrevParam (op) ) {
      if (e->lo->TestRecord (NULL,op)) break ;
      }
    if (op != NULL)
      return e->lo->UseRecord (NULL,op,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  }

static ShowDBCallList_param FAR *_actPar = NULL;
static int _actType = -1;
ListObj FAR *_actList = NULL;
static DWORD LastProcessedField;
static char oldDlgText[2048],DlgText[128];
void GetDlgText (LPSTR rTxt,int rSize);
void doSetDlgText (LPSTR rTxt);
DLLExport LPVOID _export WINAPI LOGetFirst (LPVOID bData,HDC hDC,int FAR *height,LPVOID prParam,BOOL FAR *doBreak)
  {
  if (doBreak != NULL) *doBreak = FALSE;
  ListObj FAR *o = (ListObj FAR *) bData;
  o->ResetOldSelection ();
  if ((o->updateDone) && (!o->IsOuterSet)) {
    o->dblist->ThrowList();   // Huelft nix !
    // Die Selektion neu lesen
    ((DBList FAR *) o->dblist)->SetAccess (o->GetAccessName());
    if (o->par->DoSetOrder())
      o->dblist->SetOrder (LPSTR (o->c->ReadlData (o->par->Order())));
    }
  o->updateDone = FALSE ;
  if (!o->useSimpleList) {
    LPDBRECORD rn ;
    for ( rn = o->dblist->GetFirst ();
            (rn != NULL) ;
                rn = o->dblist->GetNext (rn) ) {
      BOOL res = o->TestRecord (rn,NULL);
      if (refreshInTest) break ;
      else {
        if (res) break ;
        else {
          o->RemoveSelKey (rn->GetPrimKey());
          o->dblist->MarkRecordUnused (rn);
          }
        }
      }
    if (refreshInTest) {
      // Kann nur in Dialoglisten vorkommen
      //--------------------------------------------------
      PrimKey k;
      k.PushKeySeg (refreshInTest,GetBlockSize (refreshInTest));

      if (_actList != NULL) {
        _actList->ResetOldSelection ();
        _actList->DelDefSel();
        _actList->MyList->RefreshList (REFRESHMODE_START,&k);
        }
      FreeGlobMem (refreshInTest);
      refreshInTest = NULL;
      if (doBreak != NULL) *doBreak = TRUE;
      return NULL;
      }
    else {
      if (rn != NULL)
        return o->UseRecord (rn,NULL,hDC,height,(lPrint_param FAR *)prParam);
      else
        return NULL;
      }
    }
  else {
    OutParam FAR *op ;
    for ( op = ((DBList FAR *) o->dblist)->GetFirstParam ();
            (op != NULL) ;
                op = ((DBList FAR *) o->dblist)->GetNextParam (op) ) {
      if (o->TestRecord (NULL,op)) break ;
      }
    if (op != NULL)
      return o->UseRecord (NULL,op,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  }

DLLExport LPVOID _export WINAPI LOGetLast (LPVOID bData,HDC hDC,int FAR *height,LPVOID prParam,BOOL FAR *doBreak)
  {
  ListObj FAR *o = (ListObj FAR *) bData;
  o->ResetOldSelection ();
  if ((o->updateDone) && (!o->IsOuterSet)) {
    o->dblist->ThrowList();   // Huelft nix !
    // Die Selektion neu lesen
    ((DBList FAR *) o->dblist)->SetAccess (o->GetAccessName());
    if (o->par->DoSetOrder())
      o->dblist->SetOrder (LPSTR (o->c->ReadlData (o->par->Order())));
    }
  o->updateDone = FALSE ;
  if (!o->useSimpleList) {
    LPDBRECORD rn;
    for ( rn = o->dblist->GetLast ();
            (rn != NULL) ;
                rn = o->dblist->GetPrev (rn) ) {
      if (o->TestRecord (rn,NULL)) break ;
      else {
        o->RemoveSelKey (rn->GetPrimKey());
        o->dblist->MarkRecordUnused (rn);
        }
      }
    if (rn != NULL)
      return o->UseRecord (rn,NULL,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  else {
    OutParam FAR *op = ((DBList FAR *) o->dblist)->GetLastParam ();
    for ( ; (op != NULL) ;
                op = ((DBList FAR *) o->dblist)->GetPrevParam (op) ) {
      if (o->TestRecord (NULL,op)) break ;
      }
    if (op != NULL)
      return o->UseRecord (NULL,op,hDC,height,(lPrint_param FAR *)prParam);
    else
      return NULL;
    }
  }

BOOL ListObj::IsKeySelected (LPPRIMKEY kn)
  {
  for (int i = 0 ; i < scount ; i++)
    if (*k[i] == *kn) return TRUE ;
  return FALSE ;
  }

void ListObj::AddSelKey (LPPRIMKEY kn)
  {
  for (int i = 0 ; i < scount ; i++) {
    if (*k[i] == *kn) break ;
    }
  if (i == scount) {
    LPPRIMKEY FAR *n = (LPPRIMKEY FAR *) GetGlobMem (GetBlockSize(k) + sizeof(*n));
    if (k != NULL) {
      lmemcpy (n,k,GetBlockSize(k));
      FreeGlobMem (k);
      }
    k = n;
    k[scount] = new PrimKey();
    *k[scount] = *kn;
    scount ++ ;
    }
  }

void ListObj::RemoveSelKey (LPPRIMKEY kn)
  {
  BOOL found = FALSE ;
  for (int i = 0 ; i < scount ; i++) {
    if (found)
      k[i-1] = k[i] ;
    else {
      found = (*k[i] == *kn);
      if (found)
        delete k[i] ;
      }
    }
  if (found) {
    if (--scount == 0) {
      FreeGlobMem (k);
      k = NULL;
      }
    else {
      LPPRIMKEY FAR *n = (LPPRIMKEY FAR *) GetGlobMem (scount * sizeof(*n));
      lmemcpy (n,k,scount * sizeof(*n));
      FreeGlobMem (k);
      k = n;
      }
    }
  }

void ListObj::DoSelCallBack (BOOL state,LPPRIMKEY kc)
  {
  DWORD proc = (state) ? SetStateProc : ClearStateProc ;
  if (proc != NULL) {
    LPDBRECORD r;
    OutParam FAR *op;
    if (useSimpleList) {
      op = *((OutParam FAR * FAR *)kc->Data);
      SetOutParam (op);
      r = NULL;
      }
    else {
      r = dblist->FindRec(kc);
      op = NULL;
      }
    if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
      // Den Funktionsdaten - Offset der Extradaten uebernehmen
      SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
      SAVEREC sr;
      c->SetRecsForUpdate (sr,ExtraDataAtCreation);

      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old;
      if (r != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        }
      c->ExCuteProc (proc,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (proc,EM_RESET);
      if (r != NULL)
        c->rr->SetRecord (TableInd,old);
      c->RestoreRecs (sr);
      }
    else {
      LPDBRECORD old;
      if (r != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        }
      c->ExCuteProc (proc,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (proc,EM_RESET);
      if (r != NULL)
        c->rr->SetRecord (TableInd,old);
      }
    }
  }

void ListObj::ResetSelection ()
  {
  if (k != NULL) {
    for (int i = scount - 1; i >= 0 ; i--) {
      DoSelCallBack (FALSE,k[i]);
      delete k[i] ;
   scount = i ;  // Damit in DoSelCallBack potentielle blödheiten nicht passieren können...
      }
    scount = 0;
    FreeGlobMem (k);
    k = NULL;
    }
  }

void ListObj::_ToggleSelKey (LPPRIMKEY kn)
  {
  if (IsKeySelected(kn)) {
    RemoveSelKey(kn);
    DoSelCallBack (FALSE,kn);
    }
  else {
    if ((MaxSels > 0) && (scount == MaxSels)) {
      if (SelMode == REMOVE_FIRST) {
        PrimKey k0 ;  // Bitte nicht zusammenfassen !!! (scheiss C++)
        k0 = *k[0];
        RemoveSelKey(&k0);
        DoSelCallBack (FALSE,&k0);
        AddSelKey (kn);
        DoSelCallBack (TRUE,kn);
        }
      }
    else {
      AddSelKey (kn);
      DoSelCallBack (TRUE,kn);
      }
    }
  }

void ListObj::ToggleSelKey (LPDBRECORD rec,OutParam FAR *op)
  {
  if (rec != NULL)
    _ToggleSelKey (rec->GetPrimKey());
  else {
    PrimKey k;
    k.PushKeySeg (&op,sizeof(op));
    _ToggleSelKey (&k);
    }
  }

void ListObj::_ForceSelection (LPPRIMKEY kn)
  {
  if (!IsKeySelected(kn)) {
    if ((MaxSels > 0) && (scount == MaxSels)) {
      if (SelMode == REMOVE_FIRST) {
        PrimKey k0 = *k[0];
        RemoveSelKey(&k0);
        DoSelCallBack (FALSE,&k0);
        AddSelKey (kn);
        DoSelCallBack (TRUE,kn);
        }
      }
    else {
      AddSelKey (kn);
      DoSelCallBack (TRUE,kn);
      }
    }
  }

void ListObj::ForceSelection (LPDBRECORD rec,OutParam FAR *op)
  {
  if (rec != NULL)
    _ForceSelection (rec->GetPrimKey());
  else {
    PrimKey k;
    k.PushKeySeg (&op,sizeof(op));
    _ForceSelection (&k);
    }
  }

void ListObj::SetSelMode (DWORD smode)
  {
  // Alle Eintraege deselektieren
  for ( ; scount > 0 ; )
    RemoveSelKey (k[0]);
  par->SetMode (smode) ;
  MyList->CheckSelections_scroll (FALSE,TRUE);
  }

void ListObj::_SetSingleSelKey (LPPRIMKEY kn)
  {
  if (scount == 1)
    *k[0] = *kn;
  else {
    ResetSelection ();
    AddSelKey (kn);
    }
  }

void ListObj::SetSingleSelKey (LPDBRECORD rec,OutParam FAR *op)
  {
  if (rec != NULL)
    _SetSingleSelKey (rec->GetPrimKey());
  else {
    PrimKey k;
    k.PushKeySeg (&op,sizeof(op));
    _SetSingleSelKey (&k);
    }
  }

void ListObj::_SetDefSel (LPPRIMKEY kn,BOOL forceIt)
  {
  BOOL doIt;
  if (DefSel == NULL)
    DefSel = new PrimKey () , forceIt = TRUE ;
  forceIt = forceIt || (!MyList->TryToSetCurrentElem (DefSel->Data)) ;
  if (forceIt) {
    doIt = (!(*DefSel == *kn)) ;
    if (MyList->TryToSetCurrentElem (kn->Data)) {
      *DefSel = *kn;
      if (par->mode(c) != MODE_MULTISELECTION)
        _SetSingleSelKey (kn);
      }
    else
      doIt = FALSE ;
    }
  else {
    if (par->mode(c) != MODE_MULTISELECTION)
      _SetSingleSelKey (DefSel);
    doIt = FALSE ;
    }
  if (doIt)
    DoFocusFunction ();
  }
void ListObj::SetDefSel (LPDBRECORD rec,OutParam FAR *op,BOOL forceIt)
  {
  if (rec)
    _SetDefSel (rec->GetPrimKey(),forceIt);
  else {
    PrimKey k;
    k.PushKeySeg (&op,sizeof(op));
    _SetDefSel (&k,forceIt);
    }
  }

void ListObj::DelDefSel ()
  {
  if (DefSel != NULL)
    delete DefSel;
  DefSel = NULL;
  }

void ListObj::DoDblClk (LPDBRECORD rec,OutParam FAR *op)
  {
  if ((DblClkCallback != NULL) && ((rec != NULL) || (op != NULL))) {
    if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
      // Den Funktionsdaten - Offset der Extradaten uebernehmen
      SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
      SAVEREC sr;
      c->SetRecsForUpdate (sr,ExtraDataAtCreation);

      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old;
      if (rec != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (DblClkCallback,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (DblClkCallback,EM_RESET);
      if (rec != NULL)
        c->rr->SetRecord (TableInd,old);
      c->RestoreRecs (sr);
      }
    else {
      LPDBRECORD old;
      if (rec != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (DblClkCallback,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (DblClkCallback,EM_RESET);
      if (rec != NULL)
        c->rr->SetRecord (TableInd,old);
      }
    }
  }
 
void ListObj::DoUpClk (LPDBRECORD rec,OutParam FAR *op)
  {
  if ((UpClkCallback != NULL) && ((rec != NULL) || (op != NULL))) {
    if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
      // Den Funktionsdaten - Offset der Extradaten uebernehmen
      SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
      SAVEREC sr;
      c->SetRecsForUpdate (sr,ExtraDataAtCreation);

      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old;
      if (rec != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (UpClkCallback,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (UpClkCallback,EM_RESET);
      if (rec != NULL)
        c->rr->SetRecord (TableInd,old);
      c->RestoreRecs (sr);
      }
    else {
      LPDBRECORD old;
      if (rec != NULL) {
        old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,rec);
        }
      else
        SetOutParam (op);
      c->ExCuteProc (UpClkCallback,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (UpClkCallback,EM_RESET);
      if (rec != NULL)
        c->rr->SetRecord (TableInd,old);
      }
    }
  }

void ListObj::doClk (LPDBRECORD rec,OutParam FAR *op,int x,int y)
  {
  if (ClickProc != NULL) {
      {
      PaintContext pc;
      GetDocumentContext (&pc,c);
      double cfact;
      GetResolutionCF (&cfact);
      pc.LogicalTwips (0,0,float(cfact));
      x = pc.YPHYStoLOG (x);
      y = pc.YPHYStoLOG (y);
      }
    fpt pt;
    pt.x = float(x);
    pt.y = float(y);

    c->WritelData (ClickPos,&pt,sizeof(pt),NULL);
    // LPDBRECORD r;
    // if (kc)
    //  r = dblist->FindRec(kc);
    // else if (DefSel != NULL)
    //  r = dblist->FindRec(DefSel);
    //else
    //  r = NULL;
    if ((rec == NULL) && (op == NULL)) {
      if (DefSel != NULL) {
        if (useSimpleList)
          op = *((OutParam FAR * FAR *) DefSel->Data);
        else
          rec = dblist->FindRec(DefSel);
        }
      }
    if ((rec != NULL) || (op != NULL)) {
      if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
        SAVEREC sr;
        c->SetRecsForUpdate (sr,ExtraDataAtCreation);

        // Diesen Record ohne Umweg direkt setzten
        LPDBRECORD old;
        if (rec != NULL) {
          old = c->rr->GetRecord(TableInd);
          c->rr->SetRecord (TableInd,rec);
          }
        else
          SetOutParam (op);
        c->ExCuteProc (ClickProc,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (ClickProc,EM_RESET);
        if (rec != NULL)
          c->rr->SetRecord (TableInd,old);
        c->RestoreRecs (sr);
        }
      else {
        LPDBRECORD old;
        if (rec != NULL) {
          old = c->rr->GetRecord(TableInd);
          c->rr->SetRecord (TableInd,rec);
          }
        else
          SetOutParam (op);
        c->ExCuteProc (ClickProc,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (ClickProc,EM_RESET);
        if (rec != NULL)
          c->rr->SetRecord (TableInd,old);
        }
      }
    }
  }

//---------------------------------------------------------------------------
// Aufruf, wenn auf einen Headereintrag geklickt wurde
//---------------------------------------------------------------------------
void ListObj::DoHeaderClk (LPPOINT lppt)
  {
  //------------------------------------
  // auf welchen Header wurde geklickt?
  //------------------------------------
  int Cnt = 0;
  RECT r;
  int Index = 0;

  HWND hWnd = MyList->ListWnd();
  HDC hDC = GetDC (hWnd);

  PaintContext pc;
  pc.SetDC (hDC);
  WORD oldmode = pc.mode ;
  double cfact;
  if (par->withNormalSize(c))
    cfact = 1.0;
  else
    GetResolutionCF (&cfact);
  pc.LogicalTwips (0,0,float(cfact));

  DPtoLP (hDC, lppt, 1);

  pc.mode = oldmode ;
  pc.ResetMap ();
  ReleaseDC (hWnd, hDC);
 
  //---------------------------------------------------------------------
  // Die Breite der Stringliste wird anders berechnet als die Breite der
  // Objektliste
  //---------------------------------------------------------------------
  if (IsStringList()) {
    Cnt = LPSTRINGLIST(this)->AnzDataToShow;
 
    for (int i = 0; i < Cnt; i++) {
      r.top    = 0;
      r.left   = LPSTRINGLIST(this)->tabx[i];
      r.right  = r.left + LPSTRINGLIST(this)->w[i];
      r.bottom = LogHeight * HEADER_RATIO;
 
      if (PtInRect(&r, *lppt)) {
        Index = i + 1;
        break;
        }
      }
    }
  else if (IsObjectList()) {
    if (HdPar != NULL) {
      Cnt = HdPar->AnzColumns();
      int x0 = 0;
      ListObj FAR *ol = this;
      for (int i = 0; i < Cnt; i++) {
        DBINT w;
        ENTER(w = *((DBINT FAR *) c->ReadlData (HdPar->cd[i].Width))) ;

        r.top    = 0;
        r.left   = x0;
        r.right  = r.left + w;
        r.bottom = LogHeight * HEADER_RATIO;

        x0 += w ;

        if (PtInRect(&r, *lppt)) {
          Index = i + 1;
          break;
          }
        }
      }
    }

  if ((Index > 0) && (HeaderClkCallback[Index-1] != 0)) {
    HWND hWnd = MyList->ListWnd();
    HDC hDC = GetDC (hWnd);
 
    pc.SetDC (hDC);
    oldmode = pc.mode ;
    if (par->withNormalSize(c))
      cfact = 1.0;
    else
      GetResolutionCF (&cfact);

    pc.LogicalTwips (0,0,float(cfact));

    InvertRect (pc.hDC, &r);

    pc.mode = oldmode ;
    pc.ResetMap ();
 
    ReleaseDC (hWnd, hDC);
 
    c->ExCuteProc (HeaderClkCallback[Index-1],EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc (HeaderClkCallback[Index-1],EM_RESET);
 
    hDC = GetDC (hWnd);

    pc.SetDC (hDC);
    oldmode = pc.mode ;
    if (par->withNormalSize(c))
      cfact = 1.0;
    else
      GetResolutionCF (&cfact);
    pc.LogicalTwips (0,0,float(cfact));

    InvertRect (pc.hDC, &r);

    pc.mode = oldmode ;
    pc.ResetMap ();

    ReleaseDC (hWnd, hDC);
    }
  }
 
void OnDlgChar (WORD wP);
static BOOL dontLeaveDlg;
static mdiChild *_actDlg = NULL;
#define SEL_FROMEND   0
#define SEL_FROMSTART 1
#define SEL_ACTIVAE   2
DWORD GetListColor (WORD Type,ListObj FAR *obj);
BOOL GetFrameType (ListObj FAR *obj);
DLLExport BOOL _export WINAPI LONotify (LPVOID Data,int Action,LPVOID bData)
  {
  ScListEntry FAR *e = (ScListEntry FAR *) Data;
  ListObj FAR *o = (ListObj FAR *) bData;
  BOOL res = TRUE;
  switch (Action) {
    case DDSLIST_RELEASEELE :
      {
      if ((o->ExtraDataAtCreation != NULL) && (o->ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SAVEREC sr;
        o->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);
        SetExtraInfo s (o->c,o->ExtraDataAtCreation);
        delete e ;
        o->c->RestoreRecs (sr) ;
        }
      else
        delete e ;
      }
      break ;
    case DDSLIST_GETSELCOUNT :
      {
      int Anz = 0 ;
      for ( LPDBRECORD h = o->dblist->GetFirst (); h != NULL ; h = o->dblist->GetNext (h)) {
        if (o->TestRecord (h,NULL)) Anz ++ ;
        if (Anz >= 2) break ;
        }
      (* (int FAR *) Data) = Anz;
      }
      break ;
    case DDSLIST_GETCOLOR :
      *(DWORD FAR *) Data = GetListColor (*(WORD FAR *) Data,o);
      break ;
    case DDSLIST_GETFRAMETYPE :
      *(BOOL FAR *) Data = GetFrameType (o);
      break ;
    case DDSLIST_REMOVEELE :
      if (e->lo->IsOuterSet) {
        LPDBRECORD rec = e->rec;
        delete e ;
        e->lo->dblist->ThrowRecord (rec);
        }
      else
        delete e ;
      break ;
    case DDSLIST_SELELE :
      if (e->lo->par->mode(e->lo->c) == MODE_MULTISELECTION) {
        // Es handelt sich um eine Multiselektionsliste
        BOOL found = FALSE ;
        e->lo->ToggleSelKey (e->rec,e->lop);
        }
      else {
        e->lo->SetSingleSelKey (e->rec,e->lop);
        }
      break ;
    case DDSLIST_REMOVESEL :
      e->lo->ToggleSelKey (e->rec,e->lop);
      break ;
    case DDSLIST_FORCESEL :
      e->lo->ForceSelection (e->rec,e->lop);
      e->lo->DoFocusFunction ();
      break ;
    case DDSLIST_DELBUTTONPRESSED :
      {
      ListObj FAR *obj = (ListObj FAR *)Data;
      if (obj->DeleteCallBack != 0L) {
        if (obj->ExtraDataAtCreation != NULL) {
          SetExtraInfo s (obj->c,DWORD (0),o->ExtraDataAtCreation->fOffs);
          SAVEREC sr;
          obj->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);

          obj->c->ExCuteProc (obj->DeleteCallBack,EM_LOAD | EM_CHANGETOTRUE);
          obj->c->ExCuteProc (obj->DeleteCallBack,EM_RESET);

          obj->c->RestoreRecs (sr);
          }
        else {
          obj->c->ExCuteProc (obj->DeleteCallBack,EM_LOAD | EM_CHANGETOTRUE);
          obj->c->ExCuteProc (obj->DeleteCallBack,EM_RESET);
          }
        }
      }
      break ;
    case DDSLIST_DEFSEL :
      e->lo->SetDefSel (e->rec,e->lop,FALSE);
      break ;
    case DDSLIST_DESTROYLIST :
      {
      ListObj FAR *obj = (ListObj FAR *)Data;
      obj->ResetOldSelection ();
      if (!obj->IsOuterSet)
        obj->dblist->ThrowList ();
      }
      break ;
    case DDSLIST_DESTRUCT :
      {
      ListObj FAR *obj = (ListObj FAR *)Data;
      DBWIN_ASSERT (obj != NULL);
      delete obj;
      }
      break ;
    case DDSLIST_FOCUSELE :
      if (Data != NULL)
        e->lo->SetDefSel (e->rec,e->lop,TRUE);
      else
        o->DelDefSel ();
      break ;
    case DDSLIST_SELCHANGE :
      if (Data != NULL) {
        e->lo->SetNewSelection (e->rec,e->lop);
        }
      break ;
    case DDSLIST_CHARPRESSED :
      {
      charNotify FAR *cn = (charNotify FAR *) Data ;
      if (cn->proc) {
        char res[2];
        res[0] = cn->ch;
        res[1] = '\0';
        o->c->WritelData (cn->par,res,sizeof(res),NULL);
        o->c->ExCuteProc (cn->proc,EM_LOAD | EM_CHANGETOTRUE);
        o->c->ExCuteProc (cn->proc,EM_RESET);
        }
      else if ((cn->ch == ' ') && (_actDlg != NULL) && (o->ClickProc != 0L)) {
        o->doClk (NULL,NULL,0,0);
        }
      else if ((o->par->mode(o->c) != MODE_MULTISELECTION) ||
            (cn->ch != ' '))
        OnDlgChar (cn->ch) ;
      }
      break ;
    case DDSLIST_SELECT :
      // Nur gueltig fuer Dialogboxen
      if (o->SelectProc != 0) {
        DBWIN_ASSERT (o != NULL);
        if ((!o->MyList->IsEmpty()) && (o->scount > 0)) {
          LPDBRECORD r = o->dblist->FindRec(o->k[0]);
          DBWIN_ASSERT(r != NULL);
          if (o->ExtraDataAtCreation != NULL) {
            SetExtraInfo s (o->c,DWORD (0),o->ExtraDataAtCreation->fOffs);
            SAVEREC sr;
            o->c->SetRecsForUpdate (sr,o->ExtraDataAtCreation);

            // Diesen Record ohne Umweg direkt setzten
            LPDBRECORD old = o->c->rr->GetRecord(o->TableInd);
            o->c->rr->SetRecord (o->TableInd,r);
            BlockIsActive = FALSE ;
            o->c->ExCuteProc (o->SelectProc,EM_LOAD | EM_CHANGETOTRUE);
            o->c->ExCuteProc (o->SelectProc,EM_RESET);
            o->c->rr->SetRecord (o->TableInd,old);

            o->c->RestoreRecs (sr);
            }
          else {
            // Diesen Record ohne Umweg direkt setzten
            LPDBRECORD old = o->c->rr->GetRecord(o->TableInd);
            o->c->rr->SetRecord (o->TableInd,r);
            BlockIsActive = FALSE ;
            o->c->ExCuteProc (o->SelectProc,EM_LOAD | EM_CHANGETOTRUE);
            o->c->ExCuteProc (o->SelectProc,EM_RESET);
            o->c->rr->SetRecord (o->TableInd,old);
            }

          if (dontLeaveDlg)
            res = FALSE ;
          dontLeaveDlg = FALSE ;
          }
        }
      break ;
    case DDSLIST_SETPAINTCOLOR   :
      SetTranslateColor (* ((DWORD FAR *) Data));
      break ;
    case DDSLIST_RESETPAINTCOLOR :
      ResetTranslateColor ();
      break ;
    case DDSLIST_DBLCLKELE :
      o->DoDblClk (e->rec,e->lop);
      break ;
    case DDSLIST_LBUTTONUP :
      o->DoUpClk (e->rec,e->lop);
      break ;
    case DDSLIST_ALLOWMULTISEL :
      *((BOOL FAR *) Data) = o->AllowMultiSel;
      break ;
    case DDSLIST_ISMULTISEL :
      *((BOOL FAR *) Data) = o->par->DrawMultiSelRect (o->c);
      break ;
    case DDSLIST_HEADERCLK :
      o->DoHeaderClk (LPPOINT(Data));
      break ;
    case DDSLIST_SELRANGE_HOME :
      o->SelRange (SEL_FROMEND);
      break;
    case DDSLIST_SELRANGE_END :
      o->SelRange (SEL_FROMSTART);
      break;
    case DDSLIST_SELRANGE_ACTIVE :
      o->SelRange (SEL_ACTIVAE);
      break;
    case DDSLIST_AFTERSTART :
      o->AfterStart ();
      break ;
    case DDSLIST_CLICKDONE :
      if (Data != NULL) {
        LPPOINT pt = LPPOINT(LPSTR (Data) + e->MySize());
        o->doClk (e->rec,e->lop,pt->x,pt->y);
        }
      break ;
    }
  return res;
  }

void ListObj::SelRange (WORD mode)
  {
  if (useSimpleList) {
    OutParam FAR *first = NULL,FAR *last = NULL,FAR *h ;
    switch (mode) {
      case SEL_FROMSTART :
        for ( h = dblist->GetFirstActiveParam () ; h != NULL ; h = ((DBList FAR *) dblist)->GetPrevParam (h)) ;
        break ;
      case SEL_FROMEND :
        for ( h = dblist->GetLastActiveParam () ; h != NULL ; h = ((DBList FAR *) dblist)->GetNextParam (h)) ;
        break ;
      }
    for ( h = dblist->GetFirstActiveParam () ; h != NULL ; h = dblist->GetNextActiveParam (h)) {
      PrimKey k;
      k.PushKeySeg (&h,sizeof(h));
      if (IsKeySelected (&k)) {
        if (first == NULL) first = h ;
        last = h ;
        }
      }
    BOOL InSel = FALSE ;
    for ( h = dblist->GetFirstActiveParam () ; h != NULL ; h = dblist->GetNextActiveParam (h)) {
      PrimKey k;
      k.PushKeySeg (&h,sizeof(h));
      if (h == first) InSel = TRUE ;
      if ((InSel) && (!IsKeySelected (&k)))
        _ForceSelection (&k);
      if (h == last) InSel = FALSE ;
      }
    }
  else {
    LPDBRECORD first = NULL,last = NULL,h ;
    switch (mode) {
      case SEL_FROMSTART :
        for ( h = dblist->GetFirstActive () ; h != NULL ; h = dblist->GetPrev (h)) ;
        break ;
      case SEL_FROMEND :
        for ( h = dblist->GetLastActive () ; h != NULL ; h = dblist->GetNext (h)) ;
        break ;
      }
    for ( h = dblist->GetFirstActive () ; h != NULL ; h = dblist->GetNextActive (h)) {
      if (IsKeySelected (h->GetPrimKey())) {
        if (first == NULL) first = h ;
        last = h ;
        }
      }
    BOOL InSel = FALSE ;
    for ( h = dblist->GetFirstActive () ; h != NULL ; h = dblist->GetNextActive (h)) {
      if (h == first) InSel = TRUE ;
      if ((InSel) && (!IsKeySelected (h->GetPrimKey ())))
        _ForceSelection (h->GetPrimKey());
      if (h == last) InSel = FALSE ;
      }
    }
  }

void ListObj::SetNewSelection (LPDBRECORD r,OutParam FAR *h)
  {
  ResetOldSelection ();
  // LPDBRECORD r = dblist->FindRec(k);
  if (SelChangeCallback != 0L) {
    if (r != NULL) {
      if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
        SAVEREC sr;
        c->SetRecsForUpdate (sr,ExtraDataAtCreation);

        // Diesen Record ohne Umweg direkt setzten
        LPDBRECORD old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        c->ExCuteProc (SelChangeCallback,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
        c->rr->SetRecord (TableInd,old);
        c->RestoreRecs (sr);
        }
      else {
        LPDBRECORD old = c->rr->GetRecord(TableInd);
        c->rr->SetRecord (TableInd,r);
        c->ExCuteProc (SelChangeCallback,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
        c->rr->SetRecord (TableInd,old);
        }
      }
    else {
      SetOutParam (h);
      if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
        c->ExCuteProc (SelChangeCallback,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
        }
      else {
        c->ExCuteProc (SelChangeCallback,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
        }
      }
    }
  }

void ListObj::DoFocusFunction ()
  {
  if ((FocusFunction != 0L) && (DefSel != NULL)) {
    LPDBRECORD r;
    OutParam FAR *op;
    if (useSimpleList) {
      op = *((OutParam FAR * FAR *)DefSel->Data);
      SetOutParam (op);
      r = NULL;
      }
    else {
      r = dblist->FindRec(DefSel);
      op = NULL;
      }
    if ((r != NULL) || (op != NULL)) {
      if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
        SAVEREC sr;
        c->SetRecsForUpdate (sr,ExtraDataAtCreation);

        // Diesen Record ohne Umweg direkt setzten
        LPDBRECORD old;
        if (r != NULL) {
          old = c->rr->GetRecord(TableInd);
          c->rr->SetRecord (TableInd,r);
          }
        c->ExCuteProc (FocusFunction,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (FocusFunction,EM_RESET);
        if (r != NULL)
          c->rr->SetRecord (TableInd,old);
        c->RestoreRecs (sr);
        }
      else {
        LPDBRECORD old;
        if (r != NULL) {
          old = c->rr->GetRecord(TableInd);
          c->rr->SetRecord (TableInd,r);
          }
        c->ExCuteProc (FocusFunction,EM_LOAD | EM_CHANGETOTRUE);
        c->ExCuteProc (FocusFunction,EM_RESET);
        if (r != NULL)
          c->rr->SetRecord (TableInd,old);
        }
      }
    }
  }

void ListObj::ResetOldSelection (LPDBRECORD recToDel)
  {
  #ifdef UEBERLEGT
  if ((oldSelRecord == recToDel) && (SelChangeCallback))
    ResetOldSelection ();
  #endif
  }
void ListObj::ResetOldSelection ()
  {
  #ifdef UEBERLEGT
  if ((oldSelRecord != NULL) && (SelChangeCallback)) {
    // Den Funktionsdaten - Offset der Extradaten uebernehmen
    if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
      SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
      SAVEREC sr;
      c->SetRecsForUpdate (sr,ExtraDataAtCreation);

      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old = c->rr->GetRecord(TableInd);
      c->rr->SetRecord (TableInd,oldSelRecord);
      c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
      c->rr->SetRecord (TableInd,old);
      c->RestoreRecs (sr);
      }
    else {
      LPDBRECORD old = c->rr->GetRecord(TableInd);
      c->rr->SetRecord (TableInd,oldSelRecord);
      c->ExCuteProc (SelChangeCallback,EM_RESET | EM_CLEAR);
      c->rr->SetRecord (TableInd,old);
      }
    }
  oldSelRecord = NULL ;
  #endif
  }

static DRAWITEM MyDrawItem;
DRAWITEM myDrawItem()
  {
  if (MyDrawItem == NULL)
    MyDrawItem = DRAWITEM (MakeProcInstance (FARPROC(LODrawItem),WBase::hInstance));
  return MyDrawItem;
  }

static GETELEMEX MyInitialize;
GETELEMEX myInitialize()
  {
  if (MyInitialize == NULL)
    MyInitialize = GETELEMEX (MakeProcInstance (FARPROC(LOInitialize),WBase::hInstance));
  return MyInitialize;
  }

static UPDATEELEM MyUpdate;
UPDATEELEM myUpdate()
  {
  if (MyUpdate == NULL)
    MyUpdate = UPDATEELEM (MakeProcInstance (FARPROC(LOUpdate),WBase::hInstance));
  return MyUpdate;
  }

static GETELEM MyGetNext;
GETELEM myGetNext()
  {
  if (MyGetNext == NULL)
    MyGetNext = GETELEM (MakeProcInstance (FARPROC(LOGetNext),WBase::hInstance));
  return MyGetNext;
  }

static GETELEM MyGetPrev;
GETELEM myGetPrev()
  {
  if (MyGetPrev == NULL)
    MyGetPrev = GETELEM (MakeProcInstance (FARPROC(LOGetPrev),WBase::hInstance));
  return MyGetPrev;
  }

static GETSCROLLPOS MyGetScrollPos;
GETSCROLLPOS myGetScrollPos()
  {
  if (MyGetScrollPos == NULL)
    MyGetScrollPos = GETSCROLLPOS (MakeProcInstance (FARPROC(LOGetScrollPos),WBase::hInstance));
  return MyGetScrollPos;
  }

static SETSCROLLPOS MySetScrollPos;
SETSCROLLPOS mySetScrollPos()
  {
  if (MySetScrollPos == NULL)
    MySetScrollPos = SETSCROLLPOS (MakeProcInstance (FARPROC(LOSetScrollPos),WBase::hInstance));
  return MySetScrollPos;
  }

static ISSELECTED MyIsSelected;
ISSELECTED myIsSelected()
  {
  if (MyIsSelected == NULL)
    MyIsSelected = ISSELECTED (MakeProcInstance (FARPROC(LOIsSelected),WBase::hInstance));
  return MyIsSelected;
  }

static COMPAREDATA MyCompareData;
COMPAREDATA myCompareData()
  {
  if (MyCompareData == NULL)
    MyCompareData = COMPAREDATA (MakeProcInstance (FARPROC(LOCompareData),WBase::hInstance));
  return MyCompareData;
  }

static GETFIRST MyGetFirst;
GETFIRST myGetFirst()
  {
  if (MyGetFirst == NULL)
    MyGetFirst = GETFIRST (MakeProcInstance (FARPROC(LOGetFirst),WBase::hInstance));
  return MyGetFirst;
  }

static GETFIRST MyGetLast;
GETFIRST myGetLast()
  {
  if (MyGetLast == NULL)
    MyGetLast = GETFIRST (MakeProcInstance (FARPROC(LOGetLast),WBase::hInstance));
  return MyGetLast;
  }

static PROCESSMSG MyProcessmsg;
PROCESSMSG myProcessmsg()
  {
  if (MyProcessmsg == NULL)
    MyProcessmsg = PROCESSMSG (MakeProcInstance (FARPROC(LOProcessMsg),WBase::hInstance));
  return MyProcessmsg;
  }

static SELECTSUBLINES MylSelectSubLines ;
SELECTSUBLINES mylSelectSubLines ()
  {
  if (MylSelectSubLines == NULL)
    MylSelectSubLines = SELECTSUBLINES (MakeProcInstance (FARPROC (LOSelectSubLines),WBase::hInstance)) ;
  return MylSelectSubLines;
  }

static DDSLISTNOTIFY MyNotifycb;
DDSLISTNOTIFY myNotifycb()
  {
  if (MyNotifycb == NULL)
    MyNotifycb = DDSLISTNOTIFY (MakeProcInstance (FARPROC(LONotify),WBase::hInstance));
  return MyNotifycb;
  }

static PRINTPAGE Mydrawheadline;
PRINTPAGE mydrawheadline()
  {
  if (Mydrawheadline == NULL)
    Mydrawheadline = PRINTPAGE (MakeProcInstance (FARPROC(LOPrintHead),WBase::hInstance));
  return Mydrawheadline;
  }

static PRINTPAGE Mydrawbottomline;
PRINTPAGE mydrawbottomline()
  {
  if (Mydrawbottomline == NULL)
    Mydrawbottomline = PRINTPAGE (MakeProcInstance (FARPROC(LOPrintBottom),WBase::hInstance));
  return Mydrawbottomline;
  }

static PRINTPAGE Mystartpage;
PRINTPAGE mystartpage()
  {
  if (Mystartpage == NULL)
    Mystartpage = PRINTPAGE (MakeProcInstance (FARPROC(LOStartPage),WBase::hInstance));
  return Mystartpage;
  }

static PRINTENDPAGE Myendpage;
PRINTENDPAGE myendpage()
  {
  if (Myendpage == NULL)
    Myendpage = PRINTENDPAGE (MakeProcInstance (FARPROC(LOEndPage),WBase::hInstance));
  return Myendpage;
  }

static GETHEADER MyLOGetHeader;
GETHEADER myLOGetHeader()
  {
  if (MyLOGetHeader == NULL)
    MyLOGetHeader = GETHEADER (MakeProcInstance (FARPROC(LOGetHeader),WBase::hInstance));
  return MyLOGetHeader;
  }

static GETHEADER MyLOOGetHeader;
GETHEADER myLOOGetHeader()
  {
  if (MyLOOGetHeader == NULL)
    MyLOOGetHeader = GETHEADER (MakeProcInstance (FARPROC(LOOGetHeader),WBase::hInstance));
  return MyLOOGetHeader;
  }

static DRAWITEM MyLODrawHeader;
DRAWITEM myLODrawHeader()
  {
  if (MyLODrawHeader == NULL)
    MyLODrawHeader = DRAWITEM (MakeProcInstance (FARPROC(LODrawHeader),WBase::hInstance));
  return MyLODrawHeader;
  }

static DRAWITEM MyLODrawBottom;
DRAWITEM myLODrawBottom()
  {
  if (MyLODrawBottom == NULL)
    MyLODrawBottom = DRAWITEM (MakeProcInstance (FARPROC(LODrawBottom),WBase::hInstance));
  return MyLODrawBottom;
  }

static DRAWITEM MyLOODrawHeader;
DRAWITEM myLOODrawHeader()
  {
  if (MyLOODrawHeader == NULL)
    MyLOODrawHeader = DRAWITEM (MakeProcInstance (FARPROC(LOODrawHeader),WBase::hInstance));
  return MyLOODrawHeader;
  }

static DRAWITEM MyLOODrawBottom;
DRAWITEM myLOODrawBottom()
  {
  if (MyLOODrawBottom == NULL)
    MyLOODrawBottom = DRAWITEM (MakeProcInstance (FARPROC(LOODrawBottom),WBase::hInstance));
  return MyLOODrawBottom;
  }


DDSLISTNOTIFY Notifycb;
void ListObj::GetCallBacks ()
  {
  DrawItem = myDrawItem();
  Initialize = myInitialize();
  Update = myUpdate();
  GetNext = myGetNext();
  GetPrev = myGetPrev();
  GetScrollPos = myGetScrollPos();
  SetScrollPos = mySetScrollPos();
  IsSelected = myIsSelected();
  CompareData = myCompareData();
  GetFirst = myGetFirst();
  GetLast = myGetLast();
  Processmsg = myProcessmsg();
  SelectSubLines = mylSelectSubLines ();
  if (Notifycb == NULL)
    Notifycb = myNotifycb();
  Notify = Notifycb;
  drawheadline = mydrawheadline();
  drawbottomline = mydrawbottomline();
  startpage = mystartpage();
  endpage = myendpage();
  }

GETHEADER ListObj::GetHeaderCB ()
  {
  GetHeader = myLOGetHeader();
  return GetHeader;
  }

GETHEADER ListObj::ObjGetHeaderCB ()
  {
  GetHeader = myLOOGetHeader();
  return GetHeader;
  }

DRAWITEM ListObj::PaintHeaderCB ()
  {
  PaintHeader = myLODrawHeader();
  return PaintHeader;
  }

DRAWITEM ListObj::PaintBottomCB ()
  {
  PaintBottom = myLODrawBottom();
  return PaintBottom;
  }

DRAWITEM ListObj::ObjPaintHeaderCB ()
  {
  PaintHeader = myLOODrawHeader();
  return PaintHeader;
  }

DRAWITEM ListObj::ObjPaintBottomCB ()
  {
  PaintBottom = myLOODrawBottom();
  return PaintBottom;
  }

void ListObj::SetConnections ()
  {
  for (int i = 0 ; i < par->AnzSelParams() ; i++)
    c->SetlConnection ((par->Param())[i],par->ConnectionAddress());
  if ((ConnectEntrys()) && (dblist != NULL))
    dblist->SetConnectionInfo (par->ConnectionAddress(),c->_ccount);
  }

void ListObj::ClearConnections ()
  {
  for (int i = 0 ; i < par->AnzSelParams() ; i++)
    c->ClearlConnection ((par->Param())[i],par->ConnectionAddress());
  c->ClearlConnection (par->ModePar(),par->ConnectionAddress());
  }

void ListObj::ReleaseCallBacks ()
  {
  // wird jetzt alles erst ganz zum Schluss freigegeben !
  }

LPPARAM ListObj::GetLPParams(LPPARAM p)
  {
  if (par->AnzSelParams() == 0)
    return NULL;
  else {
    lmemset (p,'\0',sizeof(*p));
    for (int i = 0 ; i < par->AnzSelParams() ; i++) {
      p->ptr[i] = c->ReadlData ((par->Param())[i]);
      p->pType[i] = c->GetDataType ((par->Param())[i]);
      }
    p->AnzPars = par->AnzSelParams();
    return p;
    }
  }

LPTABLEDEF ListObj::GetTableDef()
  {
  LPSTR Name = LPSTR(c->ReadlData (par->TableName()));
  WORD tid,Version;
  int tnr = GetTableNr (c->schd,&tid,&Version,Name);
  if (tnr >= 0) {
    TableInd = tnr;
    td = GetTableAdmin()->GetTableDef(tid,Version);
    WIN_ASSERT (td->GetParentID() == 0);
    AliasName = LPSTR (GetGlobMem (lstrlen(Name) + 1));
    lstrcpy (AliasName,Name);
    return td;
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }

void ListObj::FreeTableDef ()
  {
  if (td != NULL)
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
  }

void ListObj::CreateList (HWND hwParent,int x,int y,int w,int h)
  {
  ParamBlock p;
  LPSTR an = GetAccessName();
  DBWIN_ASSERT (an != NULL);
  LPTABLEDEF td;
  int acg,acc;
  if (CheckAccess (an)) {
    useSimpleList = TRUE ;
    td = NULL;
    acg = 1;
    acc = 1;
    }
  else {
    td = GetTableDef();
    acg = GetAnzRecsToGet();
    acc = GetAnzRecsToCache();
    }
 
  if ((*an) || (par->DoSetOrder())) {
    dblist = new DBList (td,
                         c->DocumentID(),
                         an,
                         acg,
                         acc,
                         GetLPParams(&p),
                         ConnectEntrys()
                        );
    ((DBList FAR *) dblist)->SetSimpleList ();
    if (par->DoSetOrder())
      dblist->SetOrder (LPSTR (c->ReadlData (par->Order())));
    }

  // Erzeugen der Ausgabeliste
#ifdef EINSCHOENESBEISPIEL
  MyList = new DDSList (x,y,DrawItem,Initialize,Update,GetNext,GetPrev,
                        GetScrollPos,SetScrollPos,Notify,IsSelected,
                        CompareData,GetFirst,GetLast,
                        -1,
                        NULL,
                        this,WBase::hFrameWin
                       );
#endif
  MyList = new DDSList (x,y,
                        -1,
                        NULL,
                        this,WBase::hFrameWin
                       );

  MyList->SetCompareData (CompareData);
  MyList->SetDrawItem (DrawItem);
  MyList->SetGetNext (GetNext);
  MyList->SetGetPrev (GetPrev);
  MyList->SetInitialize (Initialize);
  MyList->SetUpdate (Update);
  MyList->SetGetFirst (GetFirst);
  MyList->SetGetLast (GetLast);
  MyList->SetGetScroll (GetScrollPos);
  MyList->SetIsSelected (IsSelected);
  MyList->SetNotify (Notify);
  MyList->SetSetScroll (SetScrollPos);
  if (par->backward(c))
    MyList->SetBackward (TRUE);

  MyList->Create(hwParent,WS_CHILD | WS_VSCROLL ,
                 x,y,w,h
                );
  }

BOOL ListObj::CreateDlgList (HWND hwParent,LPRECT fRect,LPRECT cRect,BOOL doShowDelButton,int w,int h,LPSTR Sel,LPVOID StartData,DWORD startProc,DWORD selCallBack,DWORD delCallBack,BOOL doCheckAnzSels)
  {
  if (!IsOuterSet) {
    ParamBlock p;
    LPSTR s = (Sel != NULL) ? Sel : GetAccessName() ;
    dblist = new DBList (GetTableDef(),
                        c->DocumentID(),
                        s,
                        GetAnzRecsToGet(),
                        GetAnzRecsToCache(),
                        GetLPParams(&p),
                        ConnectEntrys()
                        );
    ((DBList FAR *) dblist)->SetSimpleList ();
    if (par->DoSetOrder()) {
      dblist->SetOrder (LPSTR (c->ReadlData (par->Order())));
      }
    }
  else
    GetTableDef();

  // Erzeugen der Ausgabeliste
#ifdef EINSCHOENESBEISPIEL
  MyList = new DDSList (0,0,DrawItem,Initialize,Update,GetNext,GetPrev,
                        GetScrollPos,SetScrollPos,Notify,IsSelected,
                        CompareData,GetFirst,GetLast,
                        -1,
                        NULL,
                        this,WBase::hFrameWin
                       );
#endif
  afterStart = startProc;
  MyList = new DDSList (0,0,
                        -1,
                        StartData,
                        this,WBase::hFrameWin
                       );

  MyList->SetCompareData (CompareData);
  MyList->SetDrawItem (DrawItem);
  MyList->SetGetNext (GetNext);
  MyList->SetGetPrev (GetPrev);
  MyList->SetInitialize (Initialize);
  MyList->SetUpdate (Update);
  MyList->SetGetFirst (GetFirst);
  MyList->SetGetLast (GetLast);
  MyList->SetGetScroll (GetScrollPos);
  MyList->SetIsSelected (IsSelected);
  MyList->SetNotify (Notify);
  MyList->SetSetScroll (SetScrollPos);
  SetStateProc = selCallBack;
  ClearStateProc = delCallBack;

  return MyList->CreateDlgList (hwParent,fRect,cRect,doShowDelButton,w,h,doCheckAnzSels);
  }

#define SHOWLIST          1
#define SHOWPERMLIST      2
#define SHOWSTRINGLIST    3
#define SHOWOBJECTLIST    4
#define SHOWMPOBJECTLIST  5
#define SHOWCOLUMNLIST    6
#define SHOWEXTSTRINGLIST       7
#define SHOWEXTCOLUMNLIST       8
#define SHOWEXTOBJECTLIST       9
#define SHOWEXTMPOBJECTLIST    10
void ListObj::DoUpdate ()
  {
  if (!IsOuterSet) {
    ParamBlock p;
    ((DBList FAR *) dblist)->SetParams (GetLPParams(&p));
    if ((par->mode(c) == 0) && (k != NULL)) {
      scount = 0 ;
      FreeGlobMem (k);
      k = NULL ;
      }
    }
  updateDone = TRUE ;
  if (IsOuterSet)
    MyList->RefreshList (REFRESHMODE_END,DefSel);
  else
    MyList->RefreshList (REFRESHMODE_END);
  }

BOOL ListObj::IsUpdateToDo ()
  {
  if ((ExtraDataAtCreation != NULL) && (ExtraDataAtCreation->fOffs != 0L)) {
    // Den Funktionsdaten - Offset der Extradaten uebernehmen
    SetExtraInfo s (c,DWORD (0),ExtraDataAtCreation->fOffs);
    SAVEREC sr;
    c->SetRecsForUpdate (sr,ExtraDataAtCreation);
    for (int i = 0 ; i < par->AnzSelParams() ; i++) {
      if (c->IsUpdatelFromEle ((par->Param())[i]))
        return TRUE ;
      }
    c->RestoreRecs (sr);
    }
  else {
    for (int i = 0 ; i < par->AnzSelParams() ; i++) {
      if (c->IsUpdatelFromEle ((par->Param())[i]))
        return TRUE ;
      }
    }
  return FALSE ;
  }

void WINAPI ListShot (LPVOID Data,LPVOID edc)
  {
  LPLISTOBJ obj = *((LPLISTOBJ FAR *) Data);
  // Ueberpruefen, ob keine Tastendruecke anliegen
  obj->DelayDone = FALSE ;
  MSG msg ;
  if ((!PeekMessage (&msg,NULL,WM_KEYDOWN,
              WM_KEYDOWN,PM_NOREMOVE | PM_NOYIELD)) &&
        (!PeekMessage (&msg,NULL,WM_COMMAND,
                    WM_COMMAND,PM_NOREMOVE | PM_NOYIELD)))
    obj->DoUpdate ();
  else
    obj->SetDelay ();
  }

void ListObj::SetDelay ()
  {
  if (!DelayDone) {
    LPLISTOBJ obj = this;
    SetOneShot (DelayTime,ListShot,&obj,sizeof(obj));
    DelayDone = TRUE ;
    }
  }

void lShowListBase (LPVOID param,WORD Action,LPDEPAR p,WORD Type)
  {
  switch (Action) {
    case DO_LOAD  :
      {
      MSG m;
      while (PeekMessage (&m, WBase::hFrameWin, WMU_DESTROYDDSLIST, WMU_DESTROYDDSLIST, PM_REMOVE))
        CheckMsg (&m);
      lShowList_param FAR *par = (lShowList_param FAR *) param ;
      ListObj FAR *obj;
      switch (Type) {
        case SHOWLIST :
          obj = new ListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWPERMLIST :
          obj = new PermListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWSTRINGLIST :
          obj = new StringListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWCOLUMNLIST :
          obj = new ColumnListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWOBJECTLIST :
          obj = new ObjectListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWMPOBJECTLIST :
          DBWIN_ASSERT(FALSE);
          break ;
        case SHOWEXTSTRINGLIST :
          obj = new StringListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParExtDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWEXTCOLUMNLIST :
          obj = new ColumnListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParExtDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWEXTOBJECTLIST :
          obj = new ObjectListObj (LPTBD(p->load.privData)->c);
          obj->par = new lShowParExtDesc (param,obj->c);
          obj->DoInit ();
          break ;
        case SHOWEXTMPOBJECTLIST :
          DBWIN_ASSERT(FALSE);
          break ;
        }

      // MakeProcInstance aller Callback - Funktionen
      obj->GetCallBacks ();

      // Extradaten fuer spaetere Zwecke aufbewahren
      LPCONNEXTRAINFO ec = obj->c->_GetRecExtra() ;
      if (ec != NULL) {
        obj->ExtraDataAtCreation = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize (ec)));
        lmemcpy (obj->ExtraDataAtCreation,ec,GetBlockSize (ec));
        }

      // los gehts
      p->load.objData = obj;
      obj->CreateList (p->load.hWParent,p->load.x,p->load.y,p->load.w,p->load.h);

      p->load.hWnd = obj->MyList->ListWnd();
      }
      break ;
    case DO_SETCONNECTION :
      {
      DBWIN_ASSERT (p->reset.objData != NULL);
      ListObj FAR *obj = (ListObj FAR *) p->reset.objData;
      obj->SetConnections ();
      }
      break ;
    case DO_GETHELP :
      {
      mdiChild *c = LPTBD(p->gethelptext.privData)->c;
      ListObj FAR *obj = (ListObj FAR *) p->gethelptext.objData;
      p->gethelptext.helpText = LPSTR (c->ReadlData (obj->par->Help()));
      }
      break ;
    case DO_UPDATE :
      {
      mdiChild *c = LPTBD(p->reset.privData)->c;
      DBWIN_ASSERT (p->reset.objData != NULL);
      ListObj FAR *obj = (ListObj FAR *) p->reset.objData;
      // 1. Untersuchen, ob Update eines Parameters
      //////////////////////////////////////////////
      BOOL outerUpdateDone ;
      if (outerUpdateDone = obj->IsUpdateToDo ()) {
        if (obj->DelayUpdates)
          obj->SetDelay ();
        else
          obj->DoUpdate();
        }
      if (!outerUpdateDone) {
        // Der Update muss sich irgendwo innerhalb eines Listenelementes
        // abspielen
        int ExtraType;
        LPCONNEXTRAINFO Extra = LPCONNEXTRAINFO(GetUpdateExtraData (&ExtraType));
        BOOL extUpdateDone;
        if ((obj->ConnectEntrys()) && (obj->dblist != NULL)) {
          extUpdateDone = ((obj->dblist->ExtUpdate ()) && (UpdateEleCount () == 1));
          }
        else
          extUpdateDone = FALSE;
        if ((Extra != NULL) && (ExtraType == EXTRATYPE_LIST))
          obj->MyList->UpdateElement (Extra->i.keyData); // Stringliste
        }
      }
      break ;

    case DO_RESET :
      {
      mdiChild *c = LPTBD(p->reset.privData)->c;
      DBWIN_ASSERT (p->reset.objData != NULL);
      ListObj FAR *obj = (ListObj FAR *) p->reset.objData;
      obj->ResetOldSelection ();
      obj->MyList->DestroyList ();
      DestroyWindow (obj->MyList->hWndList);
      p->reset.objData = NULL ;
      if ((obj->ExtraDataAtCreation != NULL) && (obj->ExtraDataAtCreation->fOffs != 0L)) {
        // Den Funktionsdaten - Offset der Extradaten uebernehmen
        SAVEREC sr;
        c->SetRecsForUpdate (sr,obj->ExtraDataAtCreation);
        SetExtraInfo s (c,obj->ExtraDataAtCreation);
        obj->ClearConnections ();
        c->RestoreRecs (sr);
        }
      else
        obj->ClearConnections ();
      ResetWindowHandles (obj->MyList->hWndList);
      delete obj->MyList ;
      }
      break ;
    case DO_ACTIVATE :
      {
      if (p->activate.flag) {
        DBWIN_ASSERT (p->activate.objData != NULL);
        ListObj FAR *obj = (ListObj FAR *) p->activate.objData;
        if (((obj->IsActivated) || (!obj->par->SubSelFollows(obj->c))) &&
                (obj->dblist != NULL)) {
          obj->MyList->Show (obj->par->SubSelFollows(obj->c));
          obj->IsActivated = TRUE ;
          }
        }
      }
      break ;
    }
  }

DLLExport void _export WINAPI lShowList (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                  )
  {
  lShowListBase (param,Action,p,SHOWLIST);
  }

DLLExport void _export WINAPI lShowPermList  (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                       )
  {
  lShowListBase (param,Action,p,SHOWPERMLIST);
  }

DLLExport void _export WINAPI lShowStringList  (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                       )
  {
  lShowListBase (param,Action,p,SHOWSTRINGLIST);
  }

DLLExport void _export WINAPI lShowColumnList  (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                         )
  {
  lShowListBase (param,Action,p,SHOWCOLUMNLIST);
  }

DLLExport void _export WINAPI lShowObjectList  (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                       )
  {
  lShowListBase (param,Action,p,SHOWOBJECTLIST);
  }

DLLExport void _export WINAPI lShowMPObjectList (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                          )
  {
  lShowListBase (param,Action,p,SHOWMPOBJECTLIST);
  }
DLLExport void _export WINAPI lShowExtStringList (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                          )
  {
  lShowListBase (param,Action,p,SHOWEXTSTRINGLIST);
  }
DLLExport void _export WINAPI lShowExtColList (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                         )
  {
  lShowListBase (param,Action,p,SHOWEXTCOLUMNLIST);
  }
DLLExport void _export WINAPI lShowExtObjList(
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                       )
  {
  lShowListBase (param,Action,p,SHOWEXTOBJECTLIST);
  }
DLLExport void _export WINAPI lShowExtMPObjList(
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                         )
  {
  lShowListBase (param,Action,p,SHOWEXTMPOBJECTLIST);
  }

static DOEXTERN MylShowList;
DOEXTERN DoShowListptr ()
  {
  if (MylShowList == NULL)
    MylShowList = DOEXTERN (MakeProcInstance (FARPROC(lShowList),WBase::hInstance));
  return MylShowList;
  }

static DOEXTERN MylShowPermList;
DOEXTERN DoShowPermListptr ()
  {
  if (MylShowPermList == NULL)
    MylShowPermList = DOEXTERN (MakeProcInstance (FARPROC(lShowPermList),WBase::hInstance));
  return MylShowPermList;
  }

static DOEXTERN MylShowStringList;
DOEXTERN DoShowStringListptr ()
  {
  if (MylShowStringList == NULL)
    MylShowStringList = DOEXTERN (MakeProcInstance (FARPROC(lShowStringList),WBase::hInstance));
  return MylShowStringList;
  }

static DOEXTERN MylShowColumnList;
DOEXTERN DoShowColumnListptr ()
  {
  if (MylShowColumnList == NULL)
    MylShowColumnList = DOEXTERN (MakeProcInstance (FARPROC(lShowColumnList),WBase::hInstance));
  return MylShowColumnList;
  }

static DOEXTERN MylShowObjectList;
DOEXTERN DoShowObjectListptr ()
  {
  if (MylShowObjectList == NULL)
    MylShowObjectList = DOEXTERN (MakeProcInstance (FARPROC(lShowObjectList),WBase::hInstance));
  return MylShowObjectList;
  }

static DOEXTERN MylShowMPObjectList;
DOEXTERN DoShowMPObjectListptr ()
  {
  if (MylShowMPObjectList == NULL)
    MylShowMPObjectList = DOEXTERN (MakeProcInstance (FARPROC(lShowMPObjectList),WBase::hInstance));
  return MylShowMPObjectList;
  }

static DOEXTERN MylShowExtStringList;
DOEXTERN DoShowExtStringListptr ()
  {
  if (MylShowExtStringList == NULL)
    MylShowExtStringList = DOEXTERN (MakeProcInstance (FARPROC(lShowExtStringList),WBase::hInstance));
  return MylShowExtStringList;
  }

static DOEXTERN MylShowExtColList;
DOEXTERN DoShowExtColListptr ()
  {
  if (MylShowExtColList == NULL)
    MylShowExtColList = DOEXTERN (MakeProcInstance (FARPROC(lShowExtColList),WBase::hInstance));
  return MylShowExtColList;
  }

static DOEXTERN MylShowExtObjList;
DOEXTERN DoShowExtObjListptr ()
  {
  if (MylShowExtObjList == NULL)
    MylShowExtObjList = DOEXTERN (MakeProcInstance (FARPROC(lShowExtObjList),WBase::hInstance));
  return MylShowExtObjList;
  }

static DOEXTERN MylShowExtMPObjList;
DOEXTERN DoShowExtMPObjListptr ()
  {
  if (MylShowExtMPObjList == NULL)
    MylShowExtMPObjList = DOEXTERN (MakeProcInstance (FARPROC(lShowExtMPObjList),WBase::hInstance));
  return MylShowExtMPObjList;
  }

static DOEXTERN MylShowExtChild;
static DOEXTERN MylShowExtBlobChild;
extern DLLExport void _export WINAPI lShowExtChild (LPVOID param,WORD Action,LPDEPAR p);
extern DLLExport void _export WINAPI lShowExtBlobChild (LPVOID param,WORD Action,LPDEPAR p);
DOEXTERN DoShowExtChild ()
  {
  if (MylShowExtChild == NULL)
    MylShowExtChild = DOEXTERN (MakeProcInstance (FARPROC(lShowExtChild),WBase::hInstance));
  return MylShowExtChild;
  }
DOEXTERN DoShowExtBlobChild ()
  {
  if (MylShowExtBlobChild == NULL)
    MylShowExtBlobChild = DOEXTERN (MakeProcInstance (FARPROC(lShowExtBlobChild),WBase::hInstance));
  return MylShowExtBlobChild;
  }

static DOEXTERN MylShowExtWindow;
extern DLLExport void _export WINAPI lShowExtWindow (LPVOID param,WORD Action,LPDEPAR p);
DOEXTERN DoShowExtWindow ()
  {
  if (MylShowExtWindow == NULL)
    MylShowExtWindow = DOEXTERN (MakeProcInstance (FARPROC(lShowExtWindow),WBase::hInstance));
  return MylShowExtWindow;
  }

extern RecordList FAR * GetListFromForParam (LPVOID obj,LPVOID outobj);
void OnListDestroy (ListObj FAR *o);
ListObj::~ListObj ()
  {
  // Callback - Funktionen wieder freigeben
  OnListDestroy(this);
  if (!IsOuterSet)
    delete dblist;
  else {
    if (fparam != NULL) {
      // Der innerlist mitteilen, dass die Ausgabeliste zerstoert wird
      GetListFromForParam (fparam,NULL);
      }
    }
  ReleaseCallBacks ();
  FreeTableDef ();
  LPLISTOBJ obj = this;
  RemoveShot (&obj,sizeof(obj));
  delete par;
  if (DefSel != NULL) delete DefSel ;
  if (k != NULL) {
    for (int i = 0 ; i < scount ; i++)
      if (k[i] != NULL) delete k[i] ;
    FreeGlobMem (k);
    }
  if (AliasName)
    FreeGlobMem (AliasName);
  if (ExtraDataAtCreation != NULL)
    FreeGlobMem (ExtraDataAtCreation);
  }

//////////////////////////////////////////////////////////////////////
//  Verschiedene Hilfsfunktionen
//////////////////////////////////////////////////////////////////////
/*------------< Anzahl Selektionen in der Liste >----------*/
#pragma pack(1)
struct lGetSelCount_param {
  WORD parSize;
  DWORD scres;    // Referenz auf das Resultat
  DWORD lRef;     // Referenz auf die Liste
  };
#pragma pack()

BOOL lGetSelCount (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lGetSelCount_param FAR *par = (lGetSelCount_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadlData (par->lRef));
    DBWIN_ASSERT((t != NULL) && (*t != NULL));
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    // Noch einmal ueberpruefen
    int anz = 0 ;
    if (!obj->useSimpleList) {
      for (int i = 0 ; i < obj->AnzSelections () ; i ++ ) {
        LPDBRECORD r = obj->dblist->FindRec(obj->k[i]);
        if (r != NULL) anz ++ ;
        }
      }
    else
      anz = obj->AnzSelections ();
    c->WritelData (par->scres,&anz,sizeof(short),
                        LPSTR(param)-sizeof(WORD)
                  );
    }
  return FALSE ;
  }

/*------------< Fenstergroesse ermitteln >----------*/
#pragma pack(1)
struct GetListHeight_param {
  WORD parSize;
  DWORD res;
  DWORD lobj;
  };
#pragma pack()

BOOL GetListHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetListHeight_param FAR *par = (GetListHeight_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lobj);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    RECT r;
    GetClientRect (obj->MyList->hWndList,&r);
    LONG res = r.bottom - r.top;
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

/*------------< Eintragshoehe der Fenstergroesse anpassen >----------*/
#pragma pack(1)
struct OptimizeHeight_param {
  WORD parSize;
  DWORD res;        // Resultat: Optimale Hoehe (in log. Koordinaten, als Float)
  DWORD pxHeight;   // Longvar: Hoehe des Fensters in Pixel
  DWORD ptLL;       // Punkt, Linkes unteres Ecke des hoehesten Fensters
                    // als fpt, in log. Koordinaten
  };
#pragma pack()

BOOL OptimizeHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    OptimizeHeight_param FAR *par = (OptimizeHeight_param FAR *) param;
    LONG FAR *gheight = (LONG FAR *) c->ReadlData (par->pxHeight);
    fpt FAR *ll = (fpt FAR *) c->ReadlData (par->ptLL);
    if ((gheight != NULL) && (ll != NULL) && (ll->y > 1.0) && (*gheight > 0) && (c->DrawContext()->GetOutData()->_MyHandle)) {
      PaintContext pc(c->DrawContext()->GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
      double cfact;
      GetResolutionCF (&cfact);
      pc.LogicalTwips (0,0,float(cfact));
      int gh = pc.YPHYStoLOG (int (*gheight));
      int ph = c->WorldToLog (ll->y);
      float res = c->LogToWorld (gh / int (gh/ph));
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

/*------------< Setzen der Eintragshoehe >----------*/
#pragma pack(1)
struct SetEntryHeight_param {
  WORD parSize;
  DWORD height;
  };
#pragma pack()

BOOL SetEntryHeight (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetEntryHeight_param FAR *par = (SetEntryHeight_param FAR *) param;
    float FAR *lpheight = (float FAR *) c->ReadlData (par->height);
    if (lpheight != NULL)
      c->PutDocumentExtraData (DED_ENTRYHEIGHT,lpheight,sizeof(*lpheight));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetEntryHeight_param FAR *par = (SetEntryHeight_param FAR *) param;
    c->ClearlConnection (par->height,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

/*------------< Aufrufen der Selektionsprozedur >----------*/
#pragma pack(1)
struct FAR lSelect_param {
  WORD parSize;
  DWORD lRef;
  DWORD indRef;
  DWORD procPtr;
  };
#pragma pack()

LPDBRECORD GetSelRec (LPVOID ExternList,int FAR *ind,LPTABLEDEF FAR *td,LPSTR FAR *Alias,BOOL FAR *doMore)
  {
  *doMore = FALSE;
  LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) ExternList;
  if ((t != NULL) && (*t != NULL)) {
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    if (td != NULL) {
      *td = obj->td;
      *Alias = obj->AliasName;
      }
    if (*ind < obj->AnzSelections()) {
      for ( ; (*ind < obj->AnzSelections()) ; ) {
        if (!obj->useSimpleList) {
          LPDBRECORD r = obj->dblist->FindRec(obj->k[*ind]);
          if (r == NULL) (*ind) ++ ;
          else {
            if (obj->TestRecord (r,NULL))
              return r ;
            else
              (*ind) ++ ;
            }
          }
        else {
          OutParam FAR *op = *((OutParam FAR * FAR *) obj->k[*ind]->Data);
          obj->SetOutParam (op);
          if (obj->TestRecord (NULL,op)) {
            *doMore = TRUE ;
            return NULL;
            }
          else
            (*ind) ++ ;
          }
        }
      return NULL ;
      }
    else
      return NULL ;
    }
  else
    return NULL ;
  }

BOOL lSelect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSelect_param FAR *par = (lSelect_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    DBWIN_ASSERT (!obj->MyList->IsEmpty());
    DBINT FAR *ind = (DBINT FAR *)(c->ReadlData (par->indRef));
    DBWIN_ASSERT ((ind != NULL) && (*ind < obj->AnzSelections()));
    LPDBRECORD r = obj->dblist->FindRec(obj->k[*ind]);
    DBWIN_ASSERT(r != NULL);
    // Diesen Record ohne Umweg direkt setzten
    LPDBRECORD old = c->rr->GetRecord(obj->TableInd);
    c->rr->SetRecord (obj->TableInd,r);
    c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc (par->procPtr,EM_RESET);
    c->rr->SetRecord (obj->TableInd,old);
    }
  return FALSE ;
  }

BOOL lCallDefSel (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSelect_param FAR *par = (lSelect_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    if (obj->DefSel != NULL) {
      LPDBRECORD r = obj->dblist->FindRec(obj->DefSel);
      DBWIN_ASSERT(r != NULL);
      // Diesen Record ohne Umweg direkt setzten
      LPDBRECORD old = c->rr->GetRecord(obj->TableInd);
      c->rr->SetRecord (obj->TableInd,r);
      c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procPtr,EM_RESET);
      c->rr->SetRecord (obj->TableInd,old);
      }
    }
  return FALSE ;
  }

/*--< Aufruf einer Funktion fuer alle Selektierten Datensaetze >--*/
#pragma pack(1)
struct CallForSelected_param {
  WORD  parSize;
  DWORD lRef;
  DWORD procPtr;
  };
#pragma pack()

BOOL CallForSelected (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CallForSelected_param FAR *par = (CallForSelected_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    LPDBRECORD old = c->rr->GetRecord(obj->TableInd);
    for (int i = 0 ; i < obj->AnzSelections() ; i++) {
      LPDBRECORD r = obj->dblist->FindRec(obj->k[i]);
      DBWIN_ASSERT(r != NULL);
      // Diesen Record ohne Umweg direkt setzten
      c->rr->SetRecord (obj->TableInd,r);
      c->ExCuteProc (par->procPtr,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procPtr,EM_RESET);
      }
    c->rr->SetRecord (obj->TableInd,old);
    }
  return FALSE ;
  }

/*------------< Callbackfunktion fuer das Tastaturhandling >----------*/
#pragma pack(1)
struct ListCharCallBack_param {
  WORD parSize;
  DWORD lRef;
  DWORD parameter;
  DWORD procPtr;
  };
#pragma pack()

BOOL ListCharCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ListCharCallBack_param FAR *par = (ListCharCallBack_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->MyList->SetCharCallback (par->parameter,par->procPtr);
    }
  return FALSE ;
  }

DLLExport LPFRMOBJ _export WINAPI GetWorkObject ();
void GetFieldRect (mdiChild *c,DWORD fObj,LPRECT fr,HWND hWnd)
  {
  LPFRMOBJ FAR *llo = (LPFRMOBJ FAR *) c->ReadlData (fObj);
  LPFRMOBJ x;
  if (llo == NULL) {
    x = GetWorkObject();
    llo = &x;
    }
  DBWIN_ASSERT ((llo != NULL) && (*llo != NULL));
  PaintContext pc;
  GetDocumentContext (&pc,c);
  LPRECT logr = (*llo)->GetLogRect (c->actSide());
  WIN_ASSERT (logr != NULL);
  pc.LogRecttoPhys (fr,logr);
  ClientToScreen (hWnd,LPPOINT(&fr->left));
  ClientToScreen (hWnd,LPPOINT(&fr->right));
  }

typedef ToolEdit FAR *LPTOOLEDIT;
void GetToolEditRect (mdiChild *c,DWORD fObj,LPRECT fr,HWND FAR *parent)
  {
  LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) c->ReadlData (fObj);
  DBWIN_ASSERT     ((ed != NULL) && (*ed != NULL));
  GetWindowRect  ((*ed)->hWndEdit,fr);
  *parent = GetParent((*ed)->hWndEdit);
  }

#define TYPE_FRMOBJ          0
#define TYPE_TOOLEDIT        1
#define TYPE_MULTIFRMOBJ     2
#define TYPE_MULTITOOLEDIT   3

#pragma pack(1)
struct stentParam {
  DWORD  Format;
  DWORD  AnzDataToShow; // wie oft kommt nachfolgendes struct vor
  struct {
    DWORD ref;
    DWORD width;
    } v[1];
  int Size(mdiChild *c)
    {
    DBINT Anz = *(DBINT FAR *) c->ReadlData (AnzDataToShow);
    return Anz * sizeof(v[0]) + 2 * sizeof(DWORD);
    }
  };

struct oentParam {
  DWORD ProcToCall;
  DWORD _AnzObjects;
  DWORD ref[1];
  int Size(mdiChild *c)
    {
    DBINT Anz = *(DBINT FAR *) c->ReadlData (_AnzObjects);
    return Anz * sizeof(ref[0]) + 2 * sizeof(DWORD);
    }
  };

struct ShowDBCallList_param {
  WORD   parSize;
  DWORD  fObj;         // Feld
  DWORD  Access;       // Where Statement
  DWORD  Order;        // Order Statement
  DWORD  TableName;
  DWORD  SelectProc;
  // Dahinter entweder stentParam oder oentParam

  // Dahinter Anzahl Parameter, dann die Parameter
  // und optional dahinter die Loeschprozedur
  // und optional dahinter die Abmessungen
  // und optional einen Primaerschluessel
  };
#pragma pack()

void RealFocusIsChanging (DWORD old,DWORD n)
  {
  if (old == LastProcessedField)
    LastProcessedField = 0L ;
  }
DLLExport void _export WINAPI TBFocusChanging (DWORD old,DWORD n)
  {
  RealFocusIsChanging (old,n);
  }
void DoSetDlgParams (mdiChild *c,ShowDBCallList_param FAR *par,int type,ListObj FAR *o,DWORD fObj)
  {
  _actType = type;
  _actDlg = c;
  _actPar = par;
  _actList = o;
  if (LastProcessedField != fObj)
    DlgText[0] = '\0' ;
  GetDlgText (oldDlgText,sizeof(oldDlgText));
  if (_actType == TYPE_FRMOBJ)
    ((FrmObjectList FAR *) (_actDlg->OutList()))->OnKillFocus ();

  WORD wP;
  if ((wP = GetLastPressedChar ()) == 0)
    wP = GetLastFormPressedChar () ;
  if (wP) {
    if ((wP == '') || (wP == '\b')) {
      int l = lstrlen(DlgText);
      if (l > 0)
        DlgText[l-1] = '\0';
      }
    else {
      char txt[2];
      txt[0] = char(wP) , txt[1] = '\0';
      lstrcat (DlgText,txt);
      }
    }
  else
    DlgText[0] = '\0' ;
  }
BOOL lShowParDesc::UseDlgParams (mdiChild *c,ShowDBCallList_param FAR *par)
  {
  return !c->IsConst (par->Access);
  }
BOOL lShowParExtDesc::UseDlgParams (mdiChild *c,ShowDBCallList_param FAR *par)
  {
  BOOL res = FALSE ;
  LPSTR sel = LPSTR (c->ReadlData (par->Access));
  if (sel != NULL) {
    int len = lstrlen (sel);
    if ((len > 4) && (lstrcmp (sel + len - 4,"LIKE") == 0))
      res = TRUE ;
    }
  return res;
  }
void SetDlgParams (mdiChild *c,ShowDBCallList_param FAR *par,int type,ListObj FAR *o,DWORD fObj)
  {
  _actList = o; // Wegen MultiComboSet auch ohne DlgParams
  if (o->par->UseDlgParams (c,par))
    DoSetDlgParams (c,par,type,o,fObj);
  }

void ResetDlgParams ()
  {
  doSetDlgText (oldDlgText);
  _actDlg = NULL ;
  _actPar = NULL ;
  *oldDlgText = '\0';
  _actType = -1;
  _actList = NULL;
  }

extern void DoBind (mdiChild *c,ListObj FAR *obj,DWORD lPtr);
extern void EndBinding (mdiChild *c,DWORD lPtr);
BOOL ShowDBCallList_base (mdiChild *c,LPVOID param,WORD mode,int Type,BOOL isInner = FALSE,BOOL useObj = FALSE)
  {
  if (mode & EM_LOAD) {
    ShowDBCallList_param FAR *par = (ShowDBCallList_param FAR *) param;
    // DBINT ads = *((DBINT FAR *) c->ReadlData (par->AnzDataToShow));
    int dscSize;
    if (useObj) {
      oentParam FAR *o = (oentParam FAR *) (par + 1);
      dscSize = o->Size (c);
      }
    else {
      stentParam FAR *s = (stentParam FAR *) (par + 1);
      dscSize = s->Size (c);
      }
    WORD sSize = sizeof (*par) + dscSize;
    DWORD procToDel ;
    BOOL doParam = FALSE ;
    DWORD pSize;
    LPDWORD params;
    DWORD FAR *lpAnzPars;
    int AnzPars;
    if (par->parSize >= sSize + sizeof(DWORD)) {
      params = LPDWORD (LPSTR(par) + sSize + sizeof(DWORD));
      lpAnzPars = ((DWORD FAR *) (LPSTR(par) + sSize));
      DBWIN_ASSERT (c->IsConst (*lpAnzPars));
      AnzPars = *((DBINT FAR *) c->ReadlData (*lpAnzPars));
      pSize = (AnzPars + 1) * sizeof(DWORD);
      }
    else {
      pSize = sizeof(DWORD);
      AnzPars = 0;
      lpAnzPars = NULL;
      params = NULL;
      }
    if (par->parSize >= sSize + pSize + sizeof(DWORD)) {
      // Ueberpruefen, ob die Loeschprozedur nicht leer ist
      procToDel = * (LPDWORD (LPSTR (par) + sSize + pSize)) ;
      LPSTR start = LPSTR ((char huge *) c->GetCmdBase() + procToDel) ;
      LPSTR end = LPSTR ((char huge *) start + *(LPDWORD) start) ;
      if (end - start <= 2 * sizeof(DWORD)) procToDel = 0L ;
      }
    else
      procToDel = 0L ;
    int w,h;
    if (par->parSize >= sSize + pSize + 3 * sizeof(DWORD)) {
      w = c->ReadConstInt (* (LPDWORD (LPSTR (par) + sSize + pSize + sizeof(DWORD)))) ;
      h = c->ReadConstInt (* (LPDWORD (LPSTR (par) + sSize + pSize + 2 * sizeof(DWORD)))) ;
      }
    else
      w = h = -1 ;
    BOOL keyDone = FALSE;
    PrimKey k;
    DWORD startProc = 0L;
    DWORD FilterProc = 0L;
    DWORD FilterRes = 0L;
    switch (Type) {
      case TYPE_FRMOBJ :
      case TYPE_TOOLEDIT :
        if (par->parSize >= sSize + pSize + 4 * sizeof(DWORD)) {
          keyDone = TRUE ;
          // int Anz = int(par->parSize - (sSize + pSize + 3 * sizeof(DWORD))) / sizeof(DWORD) ;
          int Anz = 1;    // ACHTUNG: Dahinter koennten noch Filterprozedur und Resultat kommen ->
                          // Bei mehrsegmentigen Schluesseln haendischen CombinevData !
          DWORD FAR *pkVar = (DWORD FAR *) (LPSTR(par) + sSize + pSize + 3 * sizeof(DWORD));
          for (int i = 0 ; i < Anz ; i++) {
            LPVOID Data;
            if ((Data = c->ReadlData (pkVar[i])) == NULL)
              keyDone = FALSE ;
            else
              k.PushKeySeg (Data,GetBlockSize (Data));
            }
          }
        break ;
      case TYPE_MULTIFRMOBJ :
      case TYPE_MULTITOOLEDIT :
        if (par->parSize >= sSize + pSize + 4 * sizeof(DWORD))
          startProc = *(DWORD FAR *) (LPSTR(par) + sSize + pSize + 3 * sizeof(DWORD));
        else
          DBWIN_ASSERT(FALSE);
        break ;
      }

    // Filterprozedur
    //-------------------------------------------------------------------
    if (par->parSize >= sSize + pSize + 6 * sizeof(DWORD)) {
      FilterProc = *(DWORD FAR *) (LPSTR(par) + sSize + pSize + 4 * sizeof(DWORD));
      FilterRes = *(DWORD FAR *) (LPSTR(par) + sSize + pSize + 5 * sizeof(DWORD));
      }

    char pBuffer[sizeof(lShowList_extparam)+sizeof(DWORD) * 80];
    lmemset (pBuffer,'\0',sizeof(pBuffer));
    if (isInner) {
      // Es wird eine lShowList_extparam auf dem Stack zusammengebaut
      lShowList_param &p = (lShowList_param &) pBuffer[0];
      p.Access          = par->Access;
      p.TableName       = par->TableName;
      switch (Type) {
        case TYPE_FRMOBJ :
        case TYPE_TOOLEDIT :
          p.mode            = 0xFFFFFFFF;
          break ;
        case TYPE_MULTIFRMOBJ :
        case TYPE_MULTITOOLEDIT :
          p.mode            = 0xFFFFFFFE;
          break ;
        }
      p.AnzSelParams    = 0xFFFFFFFF;
      p.RecsToGet = 0xFFFFFFFF;
      p.RecsToCache = 0xFFFFFFFF;
      ExtraData FAR *ex = (ExtraData FAR *)(&p.AnzSelParams + 1) ;
      ex->AnzExtra = 0xFFFFFFFF;
      ListObj FAR *o;
      if (useObj) {
        ObjectData FAR *od = (ObjectData FAR *) (LPSTR (ex) + sizeof(DWORD));
        oentParam FAR *oe = (oentParam FAR *) (par + 1);
        od->ProcToCall = oe->ProcToCall;
        od->_AnzObjects = oe->_AnzObjects;
        DBINT ao = *((DBINT FAR *) c->ReadlData (oe->_AnzObjects));
        for (int i = 0 ; i < ao ; i++)
          od->ref[i] = oe->ref[i];
        o = new ObjectListObj (c);
        }
      else {
        ShowData FAR *sd  = (ShowData FAR *) (LPSTR (ex) + sizeof(DWORD));
        stentParam FAR *s = (stentParam FAR *) (par + 1);
        sd->Format        = s->Format;
        sd->AnzDataToShow = s->AnzDataToShow;
        DBINT ads = *((DBINT FAR *) c->ReadlData (s->AnzDataToShow));
        for (int i = 0 ; i < ads ; i++) {
          sd->v[i].ref   = s->v[i].ref   ;
          sd->v[i].width = s->v[i].width ;
          }
        o = new StringListObj (c);
        }
      o->par = new lShowParDesc (&p,c);
      o->DoInit ();
      o->GetCallBacks ();
      RECT cr,fr;
      HWND hWParent;
      cr.left = cr.top = 0;
      cr.right  = GetSystemMetrics (SM_CXSCREEN);
      cr.bottom = GetSystemMetrics (SM_CYSCREEN);
      switch (Type) {
        case TYPE_FRMOBJ :
        case TYPE_MULTIFRMOBJ :
          hWParent = c->OutWnd();
          GetFieldRect (c,par->fObj,&fr,hWParent);
          break ;
        case TYPE_TOOLEDIT :
        case TYPE_MULTITOOLEDIT :
          GetToolEditRect (c,par->fObj,&fr,&hWParent);
          break ;
        }
      DWORD SelCallBack,DelCallBack;
      switch (Type) {
        case TYPE_MULTIFRMOBJ :
        case TYPE_MULTITOOLEDIT :
          SelCallBack = par->SelectProc;
          DelCallBack = procToDel;
          break ;
        case TYPE_FRMOBJ :
        case TYPE_TOOLEDIT :
          o->SelectProc = par->SelectProc;
          if (procToDel)
            o->SetDelCallBack (procToDel);
          SelCallBack = DelCallBack = 0L;
          break ;
        }
      LPVOID keyptr;
      SetDlgParams (c,par,Type,o,par->fObj);
      if (keyDone) {
        o->DefSel = new PrimKey ();
        *(o->DefSel) = k ;
        keyptr = &k;
        }
      else
        keyptr = NULL ;

      LPSTR buffer = o->par->GetDlgSel(DlgText,FALSE);

      if (FilterProc != 0L)
        o->SetTestProc (FilterProc,FilterRes);
      DoBind (c,o,par->Order);

      if (par->parSize >= sSize + pSize + 8 * sizeof(DWORD)) {
        DWORD ClickProc = *(DWORD FAR *) (LPSTR(par) + sSize + pSize + 6 * sizeof(DWORD));
        DWORD ClickPt = *(DWORD FAR *) (LPSTR(par) + sSize + pSize + 7 * sizeof(DWORD));
        o->SetClickProc (ClickProc,ClickPt);
        }

      LPCONNEXTRAINFO ec = c->_GetRecExtra() ;
      if (ec != NULL) {
        o->ExtraDataAtCreation = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize (ec)));
        lmemcpy (o->ExtraDataAtCreation,ec,GetBlockSize (ec));
        }

      if (o->CreateDlgList (hWParent,&fr,&cr,o->DeleteCallBack != 0L,w,h,buffer,keyptr,startProc,SelCallBack,DelCallBack,*DlgText))
        LastProcessedField = par->fObj;
      LastProcessedField = 0L;
      EndBinding (c,par->Order);
      delete o->MyList;   // Achtung: o wird ueber Callback geloescht
      if (buffer != NULL)
        FreeGlobMem (buffer);
      }
    else {
      // Es wird eine lShowList_extparam auf dem Stack zusammengebaut
      lShowList_extparam &p = (lShowList_extparam &) pBuffer[0];
      p.Access          = par->Access;
      p.Order           = par->Order;
      p.TableName       = par->TableName;
      switch (Type) {
        case TYPE_FRMOBJ :
        case TYPE_TOOLEDIT :
          p.mode            = 0xFFFFFFFF;
          break ;
        case TYPE_MULTIFRMOBJ :
        case TYPE_MULTITOOLEDIT :
          p.mode            = 0xFFFFFFFE;
          break ;
        }
      if (lpAnzPars != NULL)
        p.AnzSelParams    = *lpAnzPars;
      else
        p.AnzSelParams    = 0xFFFFFFFF;
      for (int i = 0 ; i < AnzPars ; i++) {
        p.Param[i]      = params[i];
        }
      ListObj FAR *o;

      if (useObj) {
        ObjectData FAR *od = (ObjectData FAR *) (LPSTR(&p) + sizeof(lShowList_extparam) + (AnzPars - 1) * sizeof(DWORD));
        oentParam FAR *oe = (oentParam FAR *) (par + 1);
        od->ProcToCall = oe->ProcToCall;
        od->_AnzObjects = oe->_AnzObjects;
        DBINT ao = *((DBINT FAR *) c->ReadlData (oe->_AnzObjects));
        for (int i = 0 ; i < ao ; i++)
          od->ref[i] = oe->ref[i];
        o = new ObjectListObj (c);
        }
      else {
        ShowData FAR *sd  = (ShowData FAR *) (LPSTR(&p) + sizeof(lShowList_extparam) + (AnzPars - 1) * sizeof(DWORD)) ;
        stentParam FAR *s = (stentParam FAR *) (par + 1);
        sd->Format        = s->Format;
        sd->AnzDataToShow = s->AnzDataToShow;
        DBINT ads = *((DBINT FAR *) c->ReadlData (s->AnzDataToShow));
        for (int i = 0 ; i < ads ; i++) {
          sd->v[i].ref   = s->v[i].ref   ;
          sd->v[i].width = s->v[i].width ;
          }
        o = new StringListObj (c);
        }

      o->par = new lShowParExtDesc (&p,c);
      o->DoInit ();
      o->GetCallBacks ();
      RECT cr,fr;
      HWND hWParent;
      cr.left = cr.top = 0;
      cr.right  = GetSystemMetrics (SM_CXSCREEN);
      cr.bottom = GetSystemMetrics (SM_CYSCREEN);
      switch (Type) {
        case TYPE_FRMOBJ :
        case TYPE_MULTIFRMOBJ :
          hWParent = c->OutWnd();
          GetFieldRect (c,par->fObj,&fr,hWParent);
          break ;
        case TYPE_TOOLEDIT :
        case TYPE_MULTITOOLEDIT :
          GetToolEditRect (c,par->fObj,&fr,&hWParent);
          break ;
        }
      DWORD SelCallBack,DelCallBack;
      switch (Type) {
        case TYPE_MULTIFRMOBJ :
        case TYPE_MULTITOOLEDIT :
          SelCallBack = par->SelectProc;
          DelCallBack = procToDel;
          break ;
        case TYPE_FRMOBJ :
        case TYPE_TOOLEDIT :
          o->SelectProc = par->SelectProc;
          if (procToDel)
            o->SetDelCallBack (procToDel);
          SelCallBack = DelCallBack = 0L;
          break ;
        }
      SetDlgParams (c,par,Type,o,par->fObj);
      LPVOID keyptr;
      if (keyDone) {
        o->DefSel = new PrimKey ();
        *(o->DefSel) = k ;
        keyptr = &k;
        }
      else
        keyptr = NULL ;
      LPSTR buffer = o->par->GetDlgSel(DlgText,FALSE);
      if (FilterProc != 0L)
        o->SetTestProc (FilterProc,FilterRes);
      if (o->CreateDlgList (hWParent,&fr,&cr,o->DeleteCallBack != 0L,w,h,buffer,keyptr,startProc,SelCallBack,DelCallBack,*DlgText))
        LastProcessedField = par->fObj;
      LastProcessedField = 0L;
      delete o->MyList;   // Achtung: o wird ueber Callback geloescht
      if (buffer != NULL)
        FreeGlobMem (buffer);
      }
    if ((Type == TYPE_FRMOBJ) || (Type == TYPE_MULTIFRMOBJ)) {
      // Den Focus dem Element sicherheitshalber wieder geben und einen
      // Zusaetzlichen OnSetFocus, falls das Fenster bereits den Focus
      // besitzt
      SetFocus (c->OutWnd());
      if (_actDlg != NULL)
        ((FrmObjectList FAR *) (_actDlg->OutList()))->OnSetFocus ();
      }

    // Instanz wird automatisch in der Notify - Prozedur zerstoert
    ResetDlgParams ();
    }
  return FALSE ;
  }

void GetDlgText (LPSTR rTxt,int rSize)
  {
  *rTxt = '\0';
  if (_actDlg != NULL) {
    if (_actType == TYPE_FRMOBJ) {
      GLOBALHANDLE hGtxt;
      LPFRMOBJ FAR *llo = (LPFRMOBJ FAR *) _actDlg->ReadlData (_actPar->fObj);
      LPFRMOBJ x;
      if (llo == NULL) {
        x = GetWorkObject();
        llo = &x;
        }
      *(((FrmField FAR *) (*llo))->field) >> hGtxt;
      LPSTR res = (LPSTR)GlobalLock (hGtxt);
      *rTxt = '\0';
      strncat (rTxt,res,rSize-2);
      GlobalFree (hGtxt);
      }
    else if (_actType == TYPE_TOOLEDIT) {
      LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) _actDlg->ReadlData (_actPar->fObj);
      SendMessage ((*ed)->hWndEdit,WMU_GETTEXT,rSize,LPARAM(LPSTR(rTxt)));
      }
    }
  }
void doSetDlgText (LPSTR rTxt)
  {
  if (_actDlg != NULL) {
    if (_actType == TYPE_FRMOBJ) {
      LPFRMOBJ FAR *llo = (LPFRMOBJ FAR *) _actDlg->ReadlData (_actPar->fObj);
      LPFRMOBJ x;
      if (llo == NULL) {
        x = GetWorkObject();
        llo = &x;
        }
      *(((FrmField FAR *) (*llo))->field) = rTxt ;
      (*llo)->Invalidate ((*llo)->ErsteSeite(),TRUE);
      }
    else if (_actType == TYPE_TOOLEDIT) {
      LPTOOLEDIT FAR *ed = (LPTOOLEDIT FAR *) _actDlg->ReadlData (_actPar->fObj);
      SendMessage ((*ed)->hWndEdit,WM_SETTEXT,0,LPARAM(LPSTR(rTxt)));
      }
    }
  }
LPSTR lShowParDesc::GetDlgSel (LPSTR dlgText,BOOL doSet)
  {
  if (_actDlg != NULL) {
    if (!_actList->c->IsConst (_actPar->Access))
      _actList->c->WritelData (_actPar->Access,dlgText,lstrlen(dlgText) + 1,LPSTR(_actPar) - sizeof(WORD));
    }
  return NULL;
  }
LPSTR lShowParExtDesc::GetDlgSel (LPSTR dlgText,BOOL doSet)
  {
  if (_actDlg != NULL) {
    LPSTR sName = LPSTR (_actDlg->ReadlData (_actPar->Access));
    int len = lstrlen (sName) + 2 + lstrlen(dlgText) + 3 ;
    LPSTR buffer = LPSTR (GetGlobMem (len)) ;
    lstrcpy (buffer,sName);
    lstrcat (buffer," '");
    lstrcat (buffer,dlgText);
    lstrcat (buffer,"%'");
    if (doSet) {
      ((DBList FAR *) _actList->dblist)->SetAccess (buffer);
      FreeGlobMem (buffer);
      return NULL;
      }
    else
      return buffer;
    }
  return NULL;
  }
void OnDlgChar (WORD wP)
  {
  if (_actDlg != NULL) {
    if ((IsCharAlpha(char(wP))) || ((wP >= '0') && (wP <= '9')) || (wP == ' ') ||
        (wP == '_') || (wP == '-') || (wP == '.') || (wP == ':') || (wP == ',') || (wP == ';') || (wP == '+') || (wP == '*') || (wP == '/')) {
      int l = lstrlen(DlgText);
      if (l < sizeof(DlgText)-1) {
        if (l == 0)
#ifdef WIN32
          DlgText[l] = (char)(DWORD) CharUpper (LPSTR(wP));
#else
          DlgText[l] = (char)(DWORD) AnsiUpper (LPSTR(MAKELP(0,wP)));
#endif
        else
          DlgText[l] = char(wP);
        DlgText[l+1] = '\0' ;
        }
      else
        MessageBeep (0);
      }
    else if ((wP == '') || (wP == '\b')) {
      int l = lstrlen(DlgText);
      if (l > 0) {
        DlgText[l-1] = '\0';
        }
      }
    doSetDlgText (DlgText);
    _actList->par->GetDlgSel (DlgText,TRUE);
    recTested2 = NULL;
    MSG msg;
    if (!PeekMessage (&msg,NULL,WM_CHAR,
                WM_CHAR,PM_NOREMOVE | PM_NOYIELD)) {
      _actList->MyList->RefreshList (REFRESHMODE_START);
      if ((recTested2) && (_actList->IsOuterSet)) {
        if (_actList->DefSel == NULL) _actList->DefSel = new PrimKey();
        *_actList->DefSel = *recTested2;
        _actList->MyList->RefreshList (REFRESHMODE_START,recTested2);
        }
      recTested2 = NULL;
      if (_actList->afterStart == 0L) {
        if (_actList->MyList->AnzElemsInSelection () == 1)
          PostMessage (GetParent(_actList->MyList->hWndList),WM_COMMAND,
                      IDOK,0L);
        }
      else
        _actList->MyList->AfterStart ();
      }
    }
  }

BOOL DBCall_FormComboList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_FRMOBJ);
  }

BOOL DBCall_ToolComboList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_TOOLEDIT);
  }

BOOL DBCall_FormMultiComboList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTIFRMOBJ);
  }

BOOL DBCall_ToolMultiComboList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTITOOLEDIT);
  }

BOOL ShowFormComboInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_FRMOBJ,TRUE);
  }

BOOL ShowToolComboInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_TOOLEDIT,TRUE);
  }

BOOL ShowFormMultiComboInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTIFRMOBJ,TRUE);
  }

BOOL ShowToolMultiComboInnerList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTITOOLEDIT,TRUE);
  }

BOOL DBCall_FormComboObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_FRMOBJ,FALSE,TRUE);
  }

BOOL DBCall_ToolComboObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_TOOLEDIT,FALSE,TRUE);
  }

BOOL DBCall_FormMultiComboObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTIFRMOBJ,FALSE,TRUE);
  }

BOOL DBCall_ToolMultiComboObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTITOOLEDIT,FALSE,TRUE);
  }

BOOL ShowFormComboInnerListObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_FRMOBJ,TRUE,TRUE);
  }

BOOL ShowToolComboInnerObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_TOOLEDIT,TRUE,TRUE);
  }

BOOL ShowFormMultiComboInnerObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTIFRMOBJ,TRUE);
  }

BOOL ShowToolMultiComboInnerObjList (mdiChild *c,LPVOID param,WORD mode)
  {
  return ShowDBCallList_base (c,param,mode,TYPE_MULTITOOLEDIT,TRUE);
  }

#pragma pack(1)
struct RefreshDlgList_param {
  WORD parSize;
  DWORD Sel;
  };
#pragma pack()

BOOL RefreshDlgList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RefreshDlgList_param FAR *par = (RefreshDlgList_param FAR *) param;
    LPVOID sel;
    if (par->parSize >= sizeof(*par))
      sel = c->ReadlData (par->Sel);
    else
      sel = NULL;
    if (inTest) {
      if (sel) {
        refreshInTest = GetGlobMem (GetBlockSize (sel));
        lmemcpy (refreshInTest,sel,GetBlockSize(sel));
        }
      }
    else {
      PrimKey k;
      if (sel)
        k.PushKeySeg (sel,GetBlockSize (sel));

      if (_actList != NULL)
        _actList->MyList->RefreshList (REFRESHMODE_START,&k);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    RefreshDlgList_param FAR *par = (RefreshDlgList_param FAR *) param;
    if (par->parSize >= sizeof(*par))
      c->ClearlConnection (par->Sel,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct FAR lRefresh_param {
  WORD parSize;
  DWORD lRef;
  DWORD RefreshMode;
  DWORD kSeg[1];
  int AnzKeySegs() {
    return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ;
    }
  };
#pragma pack()

BOOL lRefreshList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lRefresh_param FAR *par = (lRefresh_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->ResetOldSelection ();
    obj->MyList->DestroyList ();
    if (!obj->IsOuterSet)
      obj->dblist->ThrowList();   // Huelft nix !
    DBWIN_ASSERT (c->IsConst (par->RefreshMode));
    if (par->AnzKeySegs() > 0) {
      PrimKey k;
      BOOL found = TRUE ;
      for (int i = 0 ; ((i < par->AnzKeySegs()) && (found)) ; i++) {
        LPVOID Data;
        if ((Data = c->ReadlData (par->kSeg[i])) == NULL)
          found = FALSE ;
        else
          k.PushKeySeg (Data,GetBlockSize (Data));
        }
      if (found) {
        if (obj->DefSel)
          delete obj->DefSel;
        obj->DefSel = NULL;
        obj->MyList->RefreshList (
                  *((DBINT FAR *) c->ReadlData (par->RefreshMode)),
                  &k
                                 );
        }
      else
        obj->MyList->RefreshList (*((DBINT FAR *) c->ReadlData (par->RefreshMode)));
      }
    else
      obj->MyList->RefreshList (*((DBINT FAR *) c->ReadlData (par->RefreshMode)));
    }
  if (mode & (EM_LOAD | EM_CLEAR)) {
    lRefresh_param FAR *par = (lRefresh_param FAR *) param;
    for (int i = 0 ; (i < par->AnzKeySegs()) ; i++)
      c->ClearlConnection (par->kSeg[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR lInnerUpdate_param {
  WORD parSize;
  DWORD lRef;
  DWORD InnerUpdateTestProc;
  DWORD InnerUpdateTestFlag;
  };
#pragma pack()
BOOL lInnerUpdate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lInnerUpdate_param FAR *par = (lInnerUpdate_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    DWORD utp,utf;
    if (par->parSize >= sizeof(*par)) {
      utp = par->InnerUpdateTestProc;
      utf = par->InnerUpdateTestFlag;
      }
    else {
      utp = 0L;
      utf = 0L;
      }
    obj->MyList->InnerUpdateList (utp,utf);
    }
  return FALSE ;
  }

BOOL DelDefSel (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lRefresh_param FAR *par = (lRefresh_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    if ((t != NULL) && (*t != NULL)) {
      ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
      if (obj->DefSel != NULL) delete obj->DefSel ;
      obj->DefSel = NULL ;
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR lSetSelCallBack_param {
  WORD parSize;
  DWORD lRef;
  DWORD OnSetProc;
  DWORD OnClearProc;
  };
#pragma pack()

BOOL lSetSelCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetSelCallBack_param FAR *par = (lSetSelCallBack_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->SetSelCallBack (par->OnSetProc,par->OnClearProc);
    }
  return FALSE ;
  }

#pragma pack(1)
struct lSetListMode_param {
  WORD parSize;
  DWORD lRef;
  DWORD mode;
  };
#pragma pack()
BOOL lSetListMode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetListMode_param FAR *par = (lSetListMode_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->SetSelMode (par->mode);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR lSetFocusFunction_param {
  WORD parSize;
  DWORD lRef;
  DWORD FocusFunction;
  };
#pragma pack()

BOOL lSetFocusFunction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetFocusFunction_param FAR *par = (lSetFocusFunction_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->FocusFunction = par->FocusFunction;
    if (obj->DefSel != NULL) {
      obj->DoFocusFunction ();
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR lChangeSelection_param {
  WORD parSize;
  DWORD lRef;
  DWORD state;
  DWORD var[1];
  int AnzVars()
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; }
  };
#pragma pack()

BOOL lChangeSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lChangeSelection_param FAR *par = (lChangeSelection_param FAR *) param;

    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;

    PrimKey k;
    BOOL found = TRUE ;
    for (int i = 0 ; ((i < par->AnzVars()) && (found)) ; i++) {
      LPVOID Data;
      if ((Data = c->ReadlData (par->var[i])) == NULL)
        found = FALSE ;
      else
        k.PushKeySeg (Data,GetBlockSize (Data));
      }
    DBBOOL FAR *state = (DBBOOL FAR *) c->ReadlData (par->state);
    if (((mode & EM_CHANGETOTRUE) != 0) && (obj->dblist != NULL) && (!obj->IsOuterSet))
      obj->MyList->Show (obj->par->SubSelFollows(obj->c));
    if ((found) && (state != NULL)) {
      if ((obj->par->mode(obj->c) == MODE_MULTISELECTION) || ((state != NULL) && (*state == 2))) {
        if (*state) obj->AddSelKey (&k);
        else        obj->RemoveSelKey (&k);
        obj->MyList->CheckSelections (TRUE);
        }
      else {
        if (obj->IsOuterSet) {
          if (obj->DefSel == NULL) obj->DefSel = new PrimKey();
          *obj->DefSel = k;
          obj->MyList->RefreshList (REFRESHMODE_START,&k);
          }
        else {
          obj->_SetDefSel (&k,TRUE);
          obj->MyList->CheckSelections (TRUE);
          }
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    lChangeSelection_param FAR *par = (lChangeSelection_param FAR *) param;
    for (int i = 0 ; i < par->AnzVars() ; i++)
      c->ClearlConnection (par->var[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR MultiComboSet_param {
  WORD parSize;
  DWORD var[1];
  int AnzVars()
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; }
  };
#pragma pack()

BOOL MultiComboSet (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MultiComboSet_param FAR *par = (MultiComboSet_param FAR *) param;

    ListObj FAR *obj = _actList;

    PrimKey k;
    BOOL found = TRUE ;
    for (int i = 0 ; ((i < par->AnzVars()) && (found)) ; i++) {
      LPVOID Data;
      if ((Data = c->ReadlData (par->var[i])) == NULL)
        found = FALSE ;
      else
        k.PushKeySeg (Data,GetBlockSize (Data));
      }
    if (found) {
      if (obj->par->mode(obj->c) == MODE_MULTISELECTION) {
        obj->AddSelKey (&k);
        obj->MyList->CheckSelections (TRUE);
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    MultiComboSet_param FAR *par = (MultiComboSet_param FAR *) param;
    for (int i = 0 ; i < par->AnzVars() ; i++)
      c->ClearlConnection (par->var[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL MultiComboReset (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MultiComboSet_param FAR *par = (MultiComboSet_param FAR *) param;

    ListObj FAR *obj = _actList;

    PrimKey k;
    BOOL found = TRUE ;
    for (int i = 0 ; ((i < par->AnzVars()) && (found)) ; i++) {
      LPVOID Data;
      if ((Data = c->ReadlData (par->var[i])) == NULL)
        found = FALSE ;
      else
        k.PushKeySeg (Data,GetBlockSize (Data));
      }
    if (found) {
      if (obj->par->mode(obj->c) == MODE_MULTISELECTION) {
        obj->RemoveSelKey (&k);
        obj->MyList->CheckSelections (TRUE);
        }
      }
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    MultiComboSet_param FAR *par = (MultiComboSet_param FAR *) param;
    for (int i = 0 ; i < par->AnzVars() ; i++)
      c->ClearlConnection (par->var[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////////////////////
//  CallOverSelection: Aufrufen einer Scriptprozedur fuer alle
//                     Datensaetze einer Selektion
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR CallOverSelection_param {
  WORD parSize;
  DWORD AccessName;
  DWORD TableName;
  DWORD procToCall;
  DWORD _AnzPars;
  DWORD Param[1];

  LPTABLEDEF GetTableDef(mdiChild *c,WORD FAR *TableInd);
  LPSTR GetAccessName(mdiChild *c);
  LPPARAM GetLPParams(LPPARAM p,mdiChild *c);
  int AnzPars (mdiChild *c)
    {
    DBWIN_ASSERT(c->IsConst(_AnzPars));
    return *((DBINT FAR *) c->ReadlData (_AnzPars));
    }
  };
#pragma pack()

LPTABLEDEF CallOverSelection_param::GetTableDef(mdiChild *c,WORD FAR *TableInd)
  {
  LPSTR Name = LPSTR(c->ReadlData (TableName));
  for (WORD i = 0 ; i < c->schd->AnzTables ; i++) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(c->schd->TRef[i].TableNr,c->schd->TRef[i].Version);
    if (lstrcmp(Name,td->GetName()) == 0) {
      *TableInd = i + CSYSRECS;
      return td;
      }
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  DBWIN_ASSERT(FALSE);  // Tabelle nicht deklariert !!
  return NULL;
  }

LPSTR CallOverSelection_param::GetAccessName(mdiChild *c)
  {
  return LPSTR (c->ReadlData (AccessName));
  }

LPPARAM CallOverSelection_param::GetLPParams(LPPARAM p,mdiChild *c)
  {
  if (AnzPars(c) == 0)
    return NULL;
  else {
    lmemset (p,'\0',sizeof(*p));
    for (int i = 0 ; i < AnzPars(c) ; i++) {
      p->ptr[i] = c->ReadlData (Param[i]);
      p->pType[i] = c->GetDataType (Param[i]);
      }
    p->AnzPars = AnzPars(c);
    return p;
    }
  }

BOOL CallOverSelection (mdiChild *c,LPVOID param,WORD mode,BOOL SetOrder)
  {
  if (mode & EM_LOAD) {
    CallOverSelection_param FAR *par = (CallOverSelection_param FAR *) param;
    ParamBlock p;
    WORD TableInd;
    LPTABLEDEF td = par->GetTableDef(c,&TableInd);
    DBList *dblist = new DBList (td,
                                 c->DocumentID(),
                                 par->GetAccessName(c),
                                 -1,
                                 -1,
                                 par->GetLPParams(&p,c),
                                 FALSE
                                );
    if (SetOrder)
      dblist->SetOrder ("");
 
    LPDBRECORD old = c->rr->GetRecord(TableInd);
    RestoreListFnc rlf(c);
    for (LPDBRECORD r = dblist->GetFirst () ; r != NULL ; r = dblist->GetNext (r) ) {
      c->rr->SetRecord (TableInd,r);
      c->ExCuteProc (par->procToCall,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->procToCall,EM_RESET);
      }
    c->rr->SetRecord (TableInd,old);
    delete dblist;
    GetTableAdmin()->FreeTable(td->GetTableID(),td->GetVersion());
    }
  return FALSE ;
  }

BOOL CallOverSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallOverSelection (c,param,mode,FALSE);
  }

BOOL DBCall_ForSelection (mdiChild *c,LPVOID param,WORD mode)
  {
  return CallOverSelection (c,param,mode,TRUE);
  }




////////////////////////////////////////////////////////////////////////
//  Die Liste anweisen, dass sie Knoepfe fuer das Blaettern zeichnen
//  soll
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct FAR PaintStdHeader_param {
  WORD parSize;
  DWORD lRef;
  DWORD txt[1];
  };
#pragma pack()

BOOL PaintStdHeader (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PaintStdHeader_param FAR *par = (PaintStdHeader_param FAR *) param;

    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj->IsStringList());
    StringListObj FAR *o = (StringListObj FAR *) obj;
    obj->MyList->SetHeaderCallBack (obj->GetHeaderCB(),obj->PaintHeaderCB());



    // Lesen der Ueberschriften
    /////////////////////////////////
    char txtbuffer[512];
    LPSHOWDATA s = obj->sdata;

    LPSTR h = txtbuffer ;
    for (int i = 0 ; i < int (o->AnzDataToShow) ; i++) {
      LPSTR txt = LPSTR (c->ReadlData (par->txt[i]));
      DBWIN_ASSERT (txt != NULL);
      lstrcpy (h,txt);
      h += lstrlen(h);
      *h = '\t';
      h ++ ;
      }
    *h = '\0';
    h++ ;
    if (o->HeaderText != NULL) FreeGlobMem (o->HeaderText);
    o->HeaderText = LPSTR (GetGlobMem (h-LPSTR(txtbuffer)));
    lstrcpy (o->HeaderText,txtbuffer);
    obj->MyList->Adjust();
    }
  return FALSE ;
  }
BOOL PaintStdBottom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PaintStdHeader_param FAR *par = (PaintStdHeader_param FAR *) param;

    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj->IsStringList());
    obj->MyList->SetBottomCallBack (obj->PaintBottomCB());
    }
  return FALSE ;
  }

BOOL PaintFullHeader (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    PaintFullHeader_param FAR *par = (PaintFullHeader_param FAR *) param;

    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    obj->SetHdPar(par);
    obj->MyList->SetHeaderCallBack (obj->ObjGetHeaderCB(),obj->ObjPaintHeaderCB());
    if (mode & (EM_CHANGETOTRUE | EM_UPDATE))
      InvalidateRect (obj->MyList->ListWnd(),NULL,TRUE);
    obj->MyList->Adjust();
    }

  // einen Update auf den Header-Text erzwingen
  //--------------------------------------------
  if (mode & EM_FIXCONNECTION) {
    PaintFullHeader_param FAR *par = (PaintFullHeader_param FAR *) param;
    for (int i = 0; i < par->AnzColumns(); i++) {
      c->SetlConnection (par->cd[i].Text, LPSTR(param)-sizeof(WORD));
      c->SetlConnection (par->cd[i].Width, LPSTR(param)-sizeof(WORD));
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    PaintFullHeader_param FAR *par = (PaintFullHeader_param FAR *) param;
    for (int i = 0; i < par->AnzColumns(); i++) {
      c->ClearlConnection (par->cd[i].Text, LPSTR(param)-sizeof(WORD));
      c->ClearlConnection (par->cd[i].Width, LPSTR(param)-sizeof(WORD));
      }
    }

  return FALSE ;
  }

BOOL PaintFullBottom (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PaintFullHeader_param FAR *par = (PaintFullHeader_param FAR *) param;

    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    obj->MyList->SetBottomCallBack (obj->ObjPaintBottomCB());
    }
  return FALSE ;
  }
////////////////////////////////////////////////////////////////////////
//  Die Liste anweisen, dass sie Knoepfe fuer das Blaettern zeichnen
//  soll
////////////////////////////////////////////////////////////////////////
#pragma pack(1)
struct SetButtons_param {
  WORD parSize;
  DWORD lRef;
  };
#pragma pack()

BOOL SetButtons (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetButtons_param FAR *par = (SetButtons_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadlData (par->lRef));
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->MyList->SetButtons ();
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR SetDelayedUpdate_param {
  WORD parSize;
  DWORD lRef;
  LONG _DelayTime;
  int DelayTime(mdiChild *c)
    {
    DBWIN_ASSERT (c->IsConst (_DelayTime));
    return *((DBINT FAR *) c->ReadlData (_DelayTime));
    }
  };
#pragma pack()

BOOL SetDelayedUpdate (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDelayedUpdate_param FAR *par = (SetDelayedUpdate_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadlData (par->lRef));
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->DelayUpdates = TRUE ;
    obj->DelayTime = par->DelayTime(c);
    }
  return FALSE ;
  }


#pragma pack(1)
struct FAR lSetSelChangeCallback_param {
  WORD parSize;
  DWORD lRef;
  DWORD procPtr;
  };
#pragma pack()

BOOL lSetSelChangeCallback (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetSelChangeCallback_param FAR *par = (lSetSelChangeCallback_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->SetSelChangeCallback (par->procPtr);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR lSetMaxSelCount_param {
  WORD parSize;
  DWORD lRef;
  DWORD AnzSels;
  DWORD SelMode;
  };
#pragma pack()

BOOL lSetMaxSelCount (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetMaxSelCount_param FAR *par = (lSetMaxSelCount_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    DBWIN_ASSERT (c->IsConst(par->SelMode));
    obj->SetMaxSelCount (*((DBINT FAR *) c->ReadlData (par->AnzSels)),
                         *((DBINT FAR *) c->ReadlData (par->SelMode)));
    }
  return FALSE ;
  }


#pragma pack(1)
struct BindInnerListToOuterList_param {
  WORD parSize;
  DWORD lPtr; // Innere Liste
  DWORD lRef; // Anzeigeliste
  DWORD kRef; // Zu selektierendes Element
  };
#pragma pack()

void DoBind (mdiChild *c,ListObj FAR *obj,DWORD lPtr)
  {
  LPVOID FAR *lpo = (LPVOID FAR *) c->ReadlData (lPtr);
  DBWIN_ASSERT ((lpo != NULL) && (*lpo != NULL));
  RecordList FAR *list;
  if (GetBlockSize (*lpo) == sizeof(InnerListDesc)) {
    list = LPINNERLISTDESC (*lpo)->list;
    LPINNERLISTDESC(*lpo)->lo = obj;
    }
  else {
    list = GetListFromForParam (*lpo,obj);
    obj->lptr = lPtr;
    }
  DBWIN_ASSERT (list != NULL);

  obj->SetOuterList (list,*lpo);
  if (obj->MyList != NULL)
    obj->MyList->Show(obj->par->SubSelFollows(obj->c));
  }

void EndBinding (mdiChild *c,DWORD lPtr)
  {
  LPVOID FAR *lpo = (LPVOID FAR *) c->ReadlData (lPtr);
  if ((lpo != NULL) && (*lpo != NULL)) {
    if (GetBlockSize (*lpo) == sizeof(InnerListDesc))
      LPINNERLISTDESC(*lpo)->lo = NULL;
    else
      GetListFromForParam (*lpo,NULL);
    }
  }

BOOL BindInnerListToOuterList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BindInnerListToOuterList_param FAR *par = (BindInnerListToOuterList_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DoBind (c,obj,par->lPtr);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    BindInnerListToOuterList_param FAR *par = (BindInnerListToOuterList_param FAR *) param;
    EndBinding (c,par->lPtr);
    c->ClearlConnection (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    BindInnerListToOuterList_param FAR *par = (BindInnerListToOuterList_param FAR *) param;
    c->SetlConnection (par->lPtr,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_UPDATE) {
    BindInnerListToOuterList_param FAR *par = (BindInnerListToOuterList_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                             HIWORD(par->lRef)
                                            )
                                         );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;

    // Sicherheitshalber noch einmal die liste lesen
    LPVOID FAR *lpo = (LPVOID FAR *) c->ReadlData (par->lPtr);
    DBWIN_ASSERT ((lpo != NULL) && (*lpo != NULL));
    RecordList FAR *list;
    if (GetBlockSize (*lpo) == sizeof(InnerListDesc)) {
      list = LPINNERLISTDESC (*lpo)->list;
      LPINNERLISTDESC(*lpo)->lo = obj;
      }
    else {
      list = GetListFromForParam (*lpo,obj);
      }
    DBWIN_ASSERT (list != NULL);
    obj->MyList->RefreshList (REFRESHMODE_START,obj->DefSel);
    }
  return FALSE ;
  }

void DoRemoveObjEnt (LPVOID lo,LPDBRECORD r)
  {
  if (r == NULL) {
    // Die Liste wird zerstoert
    ((ListObj FAR *) lo)->fparam = NULL;
    }
  else {
    ((ListObj FAR *) lo)->MyList->ReleaseElem (r->GetPrimKey()->Data);
    ((ListObj FAR *) lo)->RemoveSelKey (r->GetPrimKey());
    }
  }

#pragma pack(1)
struct FAR lSetDblClkCallBack_param {
  WORD parSize;
  DWORD lRef;
  DWORD ClkProc;
  };
#pragma pack()

BOOL lSetDblClkCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetDblClkCallBack_param FAR *par = (lSetDblClkCallBack_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->SetDblCallBack (par->ClkProc);
    }
  return FALSE ;
  }

BOOL lSetUpCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetDblClkCallBack_param FAR *par = (lSetDblClkCallBack_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->SetUpCallBack (par->ClkProc);
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
// Aufruf bei Mausnachrichten auf Listenheader
//---------------------------------------------------------------------------
#pragma pack(1)
struct FAR lSetHeaderClkCallBack_param {
  WORD parSize;
  DWORD lRef;       // Bezugsobjekt der Liste
  DWORD HeaderPos;  // Nr. des Eintrags im Header
  DWORD ClkProc;    // Prozedur fuer diesen Eintrag
  };
#pragma pack()

BOOL lSetHeaderClkCallBack (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lSetHeaderClkCallBack_param FAR *par = (lSetHeaderClkCallBack_param FAR *) param;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
 
    DBINT FAR *lpIndex = (DBINT FAR *)c->ReadlData (par->HeaderPos);
    DBWIN_ASSERT ((lpIndex != NULL) && (*lpIndex >= 0));
 
    obj->SetHeaderClkCallBack (par->ClkProc, *lpIndex);
    }
  return FALSE ;
  }

////////////////////////////////////////////////////////////////////////
//  Listendruck
////////////////////////////////////////////////////////////////////////
void GetDevModeParam (lPrint_param FAR *par,mdiChild *c,
      LPSTR dn,int FAR &orientation,int FAR &dsource,int FAR &psize
                     )
  {
  LPSTR devname   = LPSTR (c->ReadlData (par->DriverName));
  DBBOOL FAR *portrait  = (DBBOOL FAR *) c->ReadlData (par->doPortrait);
  DBBOOL FAR *landscape = (DBBOOL FAR *) c->ReadlData (par->doLandscape);
  DBINT FAR *defaultsource = (DBINT FAR *) c->ReadlData (par->defaultsource);
  DBINT FAR *papersize = (DBINT FAR *) c->ReadlData (par->papersize);

  if (devname != NULL)
    lstrcpy (dn,devname);
  else
    *dn = '\0';     // Default Drucker
  if ((landscape != NULL) && (portrait != NULL)) {
    if (*landscape) orientation = DMORIENT_LANDSCAPE ;
    else            orientation = DMORIENT_PORTRAIT ;
    }
  else
    orientation = -1;
  if (defaultsource != NULL)
    dsource = *defaultsource ;
  else
    dsource = -1;
  if (papersize != NULL)
    psize = *papersize;
  else
    psize = -1;
  }

extern LPSTR GetPrinterHeader ();
extern BOOL InClientTransaction;
extern BOOL CallCommandInClientTransaction;
void ListObj::DoPrint (lPrint_param FAR *par)
  {
  InClientTransaction = TRUE;
  DBWIN_ASSERT (IsObjectList());
  MyList->SetPrCallbacks (drawheadline,drawbottomline,startpage,endpage);
  // Ermitteln des Druckers, auf dem Gedruckt werden sollte
  char dn[64];
  int orientation,dsource,psize;
  GetDevModeParam (par,c,
      dn,orientation,dsource,psize
                  );
  Printer *Pr = GetPrinter (dn,orientation,dsource,psize,NULL);
  _Listpr = Pr;
  Printer *oldPrinter = c->DrawContext()->GetOutData()->Pr;
  c->DrawContext()->GetOutData()->Pr = Pr;
  Pr->PrinterDC(TRUE);          // Jetzt wirds ernst
  if (!Pr->StartPrint(GetPrinterHeader())) {
    Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben
    return ;
    }
  RECT rp;
  ResetWindowHandles (0);   // Alle Fonts muessen neu erstellt werden, damit das die Extensions richtig gemacht werden
  Pr->PaperSize (&rp);
  Pr->SetPrinterArea (&rp);
  LPOBJECTDATA s = par->DObjLine(c);
  mpp = new MultiProc (c,s->ProcToCall,TRUE);
  DBINT FAR *AnzCopys = (DBINT FAR *) c->ReadlData (par->AnzCopys);
  DBWIN_ASSERT (AnzCopys != NULL);
  for (int i = 0 ; i < *AnzCopys ; i++)
    MyList->PrintList (Pr,par);
  delete mpp;

  // Drucker wieder freigeben
  Pr->EndPrint();
  Pr->ReleaseDC();      // wirklich den DC (nicht IC) freigeben

  FreePrinter (Pr);
  c->DrawContext()->GetOutData()->Pr = oldPrinter;
  ResetWindowHandles (0);
  InClientTransaction = FALSE;
  if (CallCommandInClientTransaction) {
    PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
    CallCommandInClientTransaction = FALSE;
    }
  }

BOOL lPrint (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    lPrint_param FAR *par = (lPrint_param FAR *)param ;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (obj != NULL);
    obj->MyList->StartPrinting ();
    obj->MyList->DestroyList ();
    obj->DoPrint(par);
    obj->MyList->EndPrinting ();
    obj->MyList->RefreshList (REFRESHMODE_END);
    }
  return FALSE ;
  }

BOOL ForcePageBreak (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    _fp = TRUE;
  return FALSE;
  }

#pragma pack(1)
struct AllowAdditionalSel_param {
  WORD parSize;
  DWORD lRef;
  DWORD AllowMultiSel;
  };
#pragma pack()
BOOL AllowAdditionalSel (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AllowAdditionalSel_param FAR *par = (AllowAdditionalSel_param FAR *)param ;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) (c->ReadData (LOWORD(par->lRef),
                                            HIWORD(par->lRef)
                                            )
                                          );
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    DBWIN_ASSERT (c->IsConst (par->AllowMultiSel));
    obj->AllowMultiSel = *((DBBOOL FAR *) c->ReadlData (par->AllowMultiSel));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetFilterProc_param {
  WORD parSize;
  DWORD lRef;
  DWORD proc;
  DWORD res;
  };
#pragma pack()

BOOL SetFilterProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFilterProc_param FAR *par = (SetFilterProc_param FAR *) param ;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lRef);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;

    static BOOL FirstTime = TRUE;
    static BOOL AssertActivated = FALSE;
    if (FirstTime) {
      char retstr[5];
      GetPrivateProfileString ("Profile","DebugListFilter","no",retstr,sizeof(retstr),MYINI);
      if (lstrcmp (retstr,"yes") == 0) {
        AssertActivated = TRUE ;
        }
      FirstTime = FALSE ;
      }
    
    if (AssertActivated) {
      DBWIN_ASSERT (!obj->IsActivated);
      }

    obj->SetTestProc (par->proc,par->res);
    }
  return FALSE ;
  }

BOOL ActivateList (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetFilterProc_param FAR *par = (SetFilterProc_param FAR *) param ;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lRef);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    if (IsWindowVisible (obj->MyList->hWndList))
      obj->MyList->Show (obj->par->SubSelFollows(obj->c));
    obj->IsActivated = TRUE ;
    }
  return FALSE ;
  }

void FreeListProcs (void)
  {
  // wird jetzt alles erst ganz zum Schluss freigegeben !
#ifndef WIN32
  if (MyDrawItem != NULL) FreeProcInstance (FARPROC(MyDrawItem));
  if (MyInitialize != NULL) FreeProcInstance (FARPROC(MyInitialize));
  if (MyUpdate != NULL) FreeProcInstance (FARPROC(MyUpdate));
  if (MyGetNext != NULL) FreeProcInstance (FARPROC(MyGetNext));
  if (MyGetPrev != NULL) FreeProcInstance (FARPROC(MyGetPrev));
  if (MyGetScrollPos != NULL) FreeProcInstance (FARPROC(MyGetScrollPos));
  if (MySetScrollPos != NULL) FreeProcInstance (FARPROC(MySetScrollPos));
  if (MyIsSelected != NULL) FreeProcInstance (FARPROC(MyIsSelected));
  if (MyCompareData != NULL) FreeProcInstance (FARPROC(MyCompareData));
  if (MyGetFirst != NULL) FreeProcInstance (FARPROC(MyGetFirst));
  if (MyGetLast != NULL) FreeProcInstance (FARPROC(MyGetLast));
  if (MyProcessmsg != NULL) FreeProcInstance (FARPROC(MyProcessmsg));
  if (MyNotifycb != NULL) FreeProcInstance (FARPROC(MyNotifycb));
  if (Mydrawheadline != NULL) FreeProcInstance (FARPROC(Mydrawheadline));
  if (Mydrawbottomline != NULL) FreeProcInstance (FARPROC(Mydrawbottomline));
  if (Mystartpage != NULL) FreeProcInstance (FARPROC(Mystartpage));
  if (Myendpage != NULL) FreeProcInstance (FARPROC(Myendpage));
  if (MyLOGetHeader != NULL) FreeProcInstance (FARPROC(MyLOGetHeader));
  if (MyLOOGetHeader != NULL) FreeProcInstance (FARPROC(MyLOOGetHeader));
  if (MyLODrawHeader != NULL) FreeProcInstance (FARPROC(MyLODrawHeader));
  if (MyLOODrawHeader != NULL) FreeProcInstance (FARPROC(MyLOODrawHeader));
  if (MyLODrawBottom != NULL) FreeProcInstance (FARPROC(MyLODrawBottom));
  if (MyLOODrawBottom != NULL) FreeProcInstance (FARPROC(MyLOODrawBottom));
  if (MylShowList != NULL) FreeProcInstance (FARPROC(MylShowList));
  if (MylShowPermList != NULL) FreeProcInstance (FARPROC(MylShowPermList));
  if (MylShowStringList != NULL) FreeProcInstance (FARPROC(MylShowStringList));
  if (MylShowColumnList != NULL) FreeProcInstance (FARPROC(MylShowColumnList));
  if (MylShowObjectList != NULL) FreeProcInstance (FARPROC(MylShowObjectList));
  if (MylShowMPObjectList != NULL) FreeProcInstance (FARPROC(MylShowMPObjectList));
  if (MylShowExtStringList != NULL) FreeProcInstance (FARPROC(MylShowExtStringList));
  if (MylShowExtColList != NULL) FreeProcInstance (FARPROC(MylShowExtColList));
  if (MylShowExtObjList != NULL) FreeProcInstance (FARPROC(MylShowExtObjList));
  if (MylShowExtMPObjList != NULL) FreeProcInstance (FARPROC(MylShowExtMPObjList));
  if (MylShowExtChild != NULL) FreeProcInstance (FARPROC(MylShowExtChild));
  if (MylShowExtWindow != NULL) FreeProcInstance (FARPROC(MylShowExtWindow));
  if (MylSelectSubLines != NULL) FreeProcInstance (FARPROC(MylSelectSubLines)) ;
#endif
  }

#pragma pack(1)
struct PressedChar_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()
BOOL PressedChar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PressedChar_param FAR *par = (PressedChar_param FAR *) param;
    WORD wP;
    if ((wP = GetLastPressedChar ()) == 0)
      wP = GetLastFormPressedChar () ;
    char ch[2];
    ch[0] = char(wP);
    ch[1] = '\0' ;
    c->WritelData (par->res,ch,2,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetListClickProc_param {
  WORD parSize;
  DWORD lRef;
  DWORD proc;
  DWORD pt;
  };
#pragma pack()
BOOL SetListClickProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetListClickProc_param FAR *par = (SetListClickProc_param FAR *) param ;
    LPEXTTOOL FAR *t = (LPEXTTOOL FAR *) c->ReadlData (par->lRef);
    DBWIN_ASSERT ((t != NULL) && (*t != NULL)) ;
    ListObj FAR *obj = (ListObj FAR *) (* t)->extObj;
    obj->SetClickProc (par->proc,par->pt);
    }
  return FALSE ;
  }

BOOL DenyDlgClose (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD)
    dontLeaveDlg = TRUE;
  return FALSE;
  }

#pragma pack(1)
struct FAR SetDlgText_param {
  WORD parSize;
  DWORD text;
  };
#pragma pack()
BOOL SetDlgText (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDlgText_param FAR *par = (SetDlgText_param FAR *) param;
    LPSTR txt = LPSTR (c->ReadlData (par->text));
    if (txt) {
      lstrncpy (DlgText,txt,sizeof(DlgText));
      doSetDlgText (txt);
      }
    else {
      *DlgText = '\0';
      doSetDlgText ("");
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetDlgText_param FAR *par = (SetDlgText_param FAR *) param;
    c->ClearlConnection (par->text,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

