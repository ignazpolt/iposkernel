///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ctool/rev/ddslist.cpv   1.106   16 Jun 2000 17:12:12   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/ddslist.cpv  $
// 
//    Rev 1.106   16 Jun 2000 17:12:12   Gerhold
// Beim FormTool werden jetzt Extradaten mitgespeichert
// (wegen des Kontextes im ExcuteProc)
// 
//    Rev 1.105   06 Mar 2000 11:15:10   Hannes
// Hoehe initialisieren
// 
//    Rev 1.104   06 Mar 2000 07:09:00   Hannes
// Neuer Prototyp UpdateElem
// 
//    Rev 1.103   03 Mar 2000 08:49:18   Dietmar
// InnerUpdateList() (Abgleich f. Hannes)
// 
//    Rev 1.102   19 Dec 1999 21:27:00   Hannes
// ForcePageBreak
// 
//    Rev 1.101   25 Nov 1999 16:02:48   Hannes
// 
//    Rev 1.100   08 Nov 1999 03:44:32   Hannes
// In Testrecord ein Refreshlist..
// 
//    Rev 1.99   20 Oct 1999 07:49:50   Hannes
// Update der Header - Hoehe
// 
//    Rev 1.98   13 May 1999 22:28:02   Hannes
// Capture Auch von Aussen abschaltbar
// 
//    Rev 1.97   31 Mar 1999 14:56:04   Gerhold
// htmlhelp
// 
//    Rev 1.96   05 Mar 1999 10:56:48   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.95   19 Nov 1998 12:05:26   Hannes
// Ueberpruefung von tail != NULL
// 
//    Rev 1.94   18 Nov 1998 15:53:26   Hannes
// Am Tail Daten wieder wegwerfen, wenn im Sichtbaren Bereich
// 
//    Rev 1.93   05 Oct 1998 11:06:18   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.92   30 Jul 1998 11:10:52   Gerhold
// WinHelp angepasst fuer den HELP_FINDER
// 
//    Rev 1.91   27 Jul 1998 17:27:52   Hannes
// DDSLIST_LBUTTONUP
// 
//    Rev 1.90   29 Jun 1998 19:05:56   Hannes
// Bei gedrueckter Shifttaste und Timer die Selektion aufrechterhalten
// 
//    Rev 1.89   21 Apr 1998 19:33:06   Hannes
// Verbesserungen am Refreshverhalten
// 
//    Rev 1.88   03 Apr 1998 18:11:18   Hannes
// Verbesserte Version des RefreshList
// 
//    Rev 1.87   20 Mar 1998 15:27:38   Hannes
// Refresh im sichtbaren bereich
// 
//    Rev 1.86   16 Mar 1998 17:36:42   Hannes
// Verbesserungen an COMPAREDATA
// 
//    Rev 1.85   16 Mar 1998 09:03:28   Hannes
// Beim Refreshlist wird versucht, die Position beizubehalten...
// 
//    Rev 1.84   13 Mar 1998 18:55:54   Hannes
// Listenklickprozedur
// 
//    Rev 1.83   24 Feb 1998 19:52:22   Hannes
// Liste scrollen bei Mause - Handling
// 
//    Rev 1.82   26 Jan 1998 19:59:48   Hannes
// Listenfarben / Listentyp
// 
//    Rev 1.81   16 Jan 1998 15:28:46   Hannes
// 
//    Rev 1.80   17 Sep 1997 14:38:08   Hannes
// OnLButtonDblClk ... Doppelclick
// 
//    Rev 1.79   04 Sep 1997 20:02:50   Hannes
// Kein WMU_DESTROYLIST bei CreateDlgList
// 
//    Rev 1.78   29 Jul 1997 15:18:52   gerhold
// WM_INITDIALOG verhaelt sich in 32-Bit beim Return-Wert anders als 16-Bit
// 
//    Rev 1.77   01 Jul 1997 14:39:40   Hannes
// 
//    Rev 1.76   12 Jun 1997 16:59:26   Martin
// StartFrame ...
// 
//    Rev 1.75   08 Apr 1997 17:42:22   gerhold
// WinHelp (... GetHelpFile() ...)
// 
//    Rev 1.74   07 Apr 1997 19:18:38   gerhold
// DBCall ... Listen sollten jetzt richtig nach oben oder unten positioniert
// werden, d.h sie sollten immer ganz sichtbar sein.
// 
//    Rev 1.73   21 Mar 1997 12:49:54   Hannes
// wheight besser vorbelegen
// 
//    Rev 1.72   18 Mar 1997 15:09:52   Hannes
// 
//    Rev 1.71   29 Jan 1997 15:43:00   HANNES
// 
//    Rev 1.70   29 Jan 1997 12:21:38   HANNES
// 
//    Rev 1.69   29 Jan 1997 08:56:18   HANNES
// Verbesserungen bei der Multiselektion von Listen
// 
//    Rev 1.68   07 Jan 1997 08:27:14   HANNES
// Bei WM_LBUTTONDBLCLK vor der Weiterbearbeitung auf ein WM_LBUTTONUP gewartet.
// 
//    Rev 1.67   17 Dec 1996 16:17:26   HANNES
// Verbesserung des Handling fuer Multiselektionen
// 
//    Rev 1.66   28 Nov 1996 14:14:32   HANNES
// Pagedown - Fehlerkorrektur: Nur bis zum vorletzten zurueck
// 
//    Rev 1.65   08 Nov 1996 13:25:50   HANNES
// SetFocus auf Vaterfenster
// 
//    Rev 1.64   21 Oct 1996 18:49:56   HANNES
// Vorselektion eines Datensatzes -> DefSel aufrufen
// 
//    Rev 1.63   28 Sep 1996 15:41:22   GERHOLD
// WM_LBUTTONDOWN ... if (h == NULL) break;  ... raus, weil sonst HeaderClk
//                    nicht aufgerufen wird.
// WM_COMMAND ... neu, wegen OnLine-Hilfe
// 
//    Rev 1.62   24 Sep 1996 12:41:04   MARTIN
// SelectWholeRange: wenn vorher noch nichts selektiert kein Rosa Schirm mehr
// 
//    Rev 1.61   11 Sep 1996 14:13:36   HANNES
// Clipping hoeher gesetzt
// 
//    Rev 1.60   04 Sep 1996 15:54:34   HANNES
// 
//    Rev 1.59   03 Sep 1996 10:00:36   HANNES
// Krankengeschichtseintraege beim Drucken zerteilt
// 
//    Rev 1.58   25 Jul 1996 19:55:54   GERHOLD
// fuer 32 Bit wieder Dialoge in Resourcen und keine Templates
// 
//    Rev 1.57   03 Jul 1996 15:44:42   GERHOLD
// BOOL FAR *  =>  DBBOOL FAR *
// 
//    Rev 1.56   20 Jun 1996 19:49:04   GERHOLD
// WM_COMMAND fuer Dialoglisten war nicht richtig (Notify-Code)
// 
//    Rev 1.55   17 Jun 1996 15:35:48   HANNES
// 
//    Rev 1.53   20 May 1996 18:02:06   HANNES
// InPrinting
// 
//    Rev 1.52   20 May 1996 15:03:04   HANNES
// FehlerKorrektur FillTail, FillHead
// 
//    Rev 1.51   18 May 1996 20:48:20   HANNES
// Fuellen der Liste in ::Paint ausgelagert
// 
//    Rev 1.50   09 May 1996 19:18:56   HANNES
// 
//    Rev 1.49   09 May 1996 18:15:28   HANNES
// Korrekturen in Comboliste, END bei normalen Listen
// 
//    Rev 1.48   07 May 1996 15:52:44   HANNES
// 
//    Rev 1.47   06 May 1996 19:40:52   HANNES
// SELELE wieder raus aus LINEUP...
// 
//    Rev 1.46   06 May 1996 17:16:38   HANNES
// Nicht wiederholbare Objekte
// 
//    Rev 1.45   06 May 1996 12:56:00   HANNES
// SubScrollen
// 
//    Rev 1.43   26 Mar 1996 18:50:40   MARTIN
// endpage: Parameter last
// 
//    Rev 1.42   18 Mar 1996 16:37:58   GERHOLD
// Die Initialisierung der Knoepfe erfolgt hier in CreateListButtons
// (das war vorher in BUTTONS.CPP).
// 
//    Rev 1.41   16 Feb 1996 14:42:50   GERHOLD
// DDSList::IsMultiSel,  Zeichnen der kleinen Bitmaps
// 
//    Rev 1.40   02 Feb 1996 10:41:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.39   12 Dec 1995 11:46:18   GERHOLD
// WM_KILLFOCUS (WW_ONKILLFOCUS wird an die ToolBarProc geschickt)
// 
//    Rev 1.38   20 Nov 1995 11:42:20   HANNES
// 
//    Rev 1.37   24 Aug 1995 09:36:48   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.36   10 Aug 1995 09:23:56   HANNES
// Drucken auf die neue Konvention
// 
//    Rev 1.35   26 Jun 1995 10:15:26   GERHOLD
// ein bisschen effizienter zeichnen
// 
//    Rev 1.34   09 Jun 1995 00:24:14   HANNES
// Verbesserte Vorselektion (speziell bei Speicherlisten)
// 
//    Rev 1.33   24 May 1995 17:10:30   HANNES
// Fehler beim Scrolldown (Scrollwindow nur wenn wirklich noetig)
// 
//    Rev 1.32   19 May 1995 16:26:12   gerhold
// Es wird ein bisschen besser invalidiert
// 
//    Rev 1.31   02 May 1995 13:48:04   HANNES
// Verbessertes Initialize
// 
//    Rev 1.30   12 Apr 1995 12:27:36   HANNES
// 
//    Rev 1.29   06 Apr 1995 16:08:48   HANNES
// 
//    Rev 1.28   06 Apr 1995 16:00:56   HANNES
// 
//    Rev 1.27   01 Apr 1995 19:44:44   HANNES
// 
//    Rev 1.26   31 Mar 1995 13:10:14   HANNES
//  
// 
//    Rev 1.25   31 Mar 1995 08:53:22   HANNES
// 
//    Rev 1.24   29 Mar 1995 16:22:52   HANNES
// 
//    Rev 1.23   27 Mar 1995 13:18:30   HANNES
//  
// 
//    Rev 1.22   20 Mar 1995 12:12:02   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.21   24 Feb 1995 11:02:58   GERHOLD
// WM_KEYDOWN um VK_RETURN erweitert
// 
//    Rev 1.20   06 Feb 1995 16:50:34   HANNES
// Erweiterung Multiselektion
// 
//    Rev 1.19   31 Jan 1995 15:37:52   HANNES
// 
//    Rev 1.18   20 Jan 1995 15:50:14   HANNES
// Multiselektion
// 
//    Rev 1.17   15 Dec 1994 18:22:32   HANNES
// Windowklassen ext. initialisieren
// 
//    Rev 1.16   18 Nov 1994 19:57:16   GERHOLD
// Drucken reaktiviert
// 
//    Rev 1.15   07 Nov 1994 11:40:28   HANNES
// CheckSelection_scroll public+export
// 
//    Rev 1.14   31 Oct 1994 10:34:34   hannes
// DDSLIST_REMOVEELE
// 
//    Rev 1.13   27 Oct 1994 15:09:50   GERHOLD
// CreateDlgList kann jetzt zwei verschiedene Listen anzeigen.
// Aufruf von SetButtons im DListDlgProc
// Einfuegen von IDB_DELETE in DListDlgProc
// 
//    Rev 1.12   22 Sep 1994 16:08:08   GERHOLD
// wir das letzte Element selektiert ist es ab jeztt vollstaendig sichtbar
// Fehler in PgUp, PgDn ausgebessert
// 
//    Rev 1.11   05 Sep 1994 15:36:22   HANNES
// DrawBottom
// 
//    Rev 1.10   30 Aug 1994 10:40:06   HANNES
// Notify geaendert
// 
//    Rev 1.9   26 Aug 1994 15:51:58   GERHOLD
// 
//    Rev 1.8   16 Aug 1994 08:46:48   GERHOLD
// ein paar kleine Zeichnungsaenderungen
// 
//    Rev 1.7   11 Aug 1994 09:14:22   HANNES
// DDSLIST_DESTROYLIST
// 
//    Rev 1.6   10 Aug 1994 18:28:08   GERHOLD
// Fill auf FillHead und FillTail aufgeteilt
// 
//    Rev 1.5   10 Aug 1994 12:13:02   GERHOLD
// Listeneintraeg werden nicht invertiert
// 
//    Rev 1.4   05 Aug 1994 17:06:26   HANNES
// Richtungsangabe in den Listen
// 
//    Rev 1.3   12 Jul 1994 14:44:02   GERHOLD
// Die "buttons" bekommen jetzt genauere Informationen Åber das ListWnd
// 
//    Rev 1.2   05 Jul 1994 15:33:10   GERHOLD
// Buttons eingebaut. Hannes glaubt aber fehlerhaft! Schmach und Schande!
// 
//    Rev 1.1   27 Jun 1994 16:58:56   HANNES
// Verschiedene Fehlerkorrekturen in Verbindung mit der Dialogbox
// 
//    Rev 1.0   24 Jun 1994 16:41:12   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.28   07 Feb 1994 17:25:54   HANNES
// Optimierung fuer CreateDDSList(...) abgedreht
// 
//    Rev 1.27   20 Jan 1994 23:53:54   HANNES
// WW_RBUTTONDOWN, WW_RBUTTONUP
// 
//    Rev 1.26   07 Jan 1994 19:14:48   HANNES
// Moeglichkeit des Abbruchs in den Listen implementiert
// 
//    Rev 1.25   04 Jan 1994 17:22:56   HANNES
// Scorllbarhandling bei Leer - Dateien
// Doppelklick in invaliden Bereich
// Handling der rechten Mousetaste fuer Hilfe
// 
//    Rev 1.24   18 Nov 1993 16:24:50   HANNES
// Verbessertes Scrollbalken - Handling
// 
//    Rev 1.23   18 Oct 1993 19:44:40   HANNES
// SetCharCallBack
// 
//    Rev 1.22   11 Oct 1993 11:45:54   HANNES
// DestroyList exportiert
// 
//    Rev 1.21   06 Oct 1993 15:13:18   HANNES
// Verbesserungen
// 
//    Rev 1.20   24 Sep 1993 22:44:48   HANNES
// Richtiger Aufruf von DDSLIST_DESTRUCT
// 
//    Rev 1.19   22 Sep 1993 09:48:28   GERHOLD
// Version nach St.Poelten
// 
//    Rev 1.18   09 Sep 1993 19:08:30   HANNES
// Selektionen in der Single - Liste
// 
//    Rev 1.17   03 Sep 1993 15:21:24   GERHOLD
// CheckSelections public+export
// 
//    Rev 1.16   24 Aug 1993 10:34:22   GERHOLD
// 
//    Rev 1.15   18 Aug 1993 10:51:42   GERHOLD
// Drucken verbessert
// 
//    Rev 1.14   09 Aug 1993 12:58:28   HANNES
// ?
// 
//    Rev 1.13   22 Jul 1993 14:47:58   HANNES
// DrawItem mit doPrint - Parameter
// 
//    Rev 1.12   21 Jul 1993 09:44:58   HANNES
// Zerstoeren des Fensters im Destruktor
// 
//    Rev 1.11   20 Jul 1993 12:03:16   HANNES
// Drucker vervollstaendigen
// 
//    Rev 1.10   19 Jul 1993 15:15:04   HANNES
// ...
// 
//    Rev 1.9   19 Jul 1993 14:49:16   GERHOLD
// Drucken
// 
//    Rev 1.7   13 Jul 1993 13:37:12   GERHOLD
// Tastaturschnittstelle + ThumbPos
// 
//    Rev 1.6   12 Jul 1993 13:28:14   GERHOLD
// Multiselektionen..
// 
//    Rev 1.5   09 Jul 1993 10:55:24   HANNES
// ??
// 
//    Rev 1.4   08 Jul 1993 12:35:14   HANNES
// 
//    Rev 1.3   08 Jul 1993 12:29:48   GERHOLD
// Vorbereitung fÅr den Einbau in die CTOOL.DLL
// 
//    Rev 1.2   07 Jul 1993 17:51:22   GERHOLD
// Zwischenversion
// 
//    Rev 1.1   05 Jul 1993 15:02:58   GERHOLD
// Testversion
// 
//    Rev 1.0   29 Jun 1993 10:14:12   HANNES
// Initial revision.
///////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <memory.h>

#include <htmlhelp.h>

#include "dds32.h"
#include "dds.h"
#include "globmem.h"
#include "toolbar.hpp"
#include "printer.hpp"
#include "buttons.hpp"
#include "ddslist.hpp"
#define JUST_EM
#include "dds.hpp"
#include "ddsmsg.h"
#ifndef MAPTYPE_GEOMETIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "cfield.hpp"
#include "dlgtempl.hpp"

#define MODULENUM 123
#include "winass.hpp"


LPSTR szListClassName;


extern HINSTANCE hLibInst;

DDSList::DDSList (int px, int py,
                  int yscrollmax, LPVOID StartData,LPVOID bD, HWND donotify
                 )
  { 
  x = px; 
  y = py; 
  hWndList = 0; 
  yscrollrange = yscrollmax;
  StartElem = StartData;
  CurrentElem = NULL;
  bData = bD;
  DoNotify = donotify;
  }


BOOL DDSList::Registered = FALSE;


/*-------------------------------------------------------------------------*\
*  member function: CheckCurrentElem                                        *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :   pr¸ft ob das aktive Element sichtbar ist                *
\*-------------------------------------------------------------------------*/
void DDSList::CheckCurrentElem ()
  {
  for ( ListElem FAR *h = head ; h != NULL ; h = h->Next) {
    if (CurrentElem == h) break ;
    }
  if (h == NULL) CurrentElem = NULL;
  }

ListElem FAR *lastElemDown;

/*-------------------------------------------------------------------*\
*  member function:  AddTail                                          *
*                                                                     *
* Parameter:      Data ......                                         *
*                 height ....                                         *
* Zweck:          h‰ngt ein Element an das Ende der Liste             *
\*-------------------------------------------------------------------*/
void DDSList::AddTail (LPVOID Data,int height)
  {
  ListElem FAR *h = CopyData (Data,height);  // kopiert die Daten, und lˆscht sie danach
  h->Prev = tail;                            // an das letzte Element anh‰ngen
  h->Next = NULL;                            // es gibt kein n‰chstes Element
  if (tail != NULL)                          // gab es ein letztes Element?
    tail->Next = h;
  else
    head = h;                                // nein -> das ist also das Erste
  tail = h;
  h->isSel = (* IsSelected) (h->Data);
  }

/*-------------------------------------------------------------------*\
*  member function:  AddHead                                          *
*                                                                     *
* Parameter:      Data ......                                         *
*                 height ....                                         *
\*-------------------------------------------------------------------*/
void DDSList::AddHead (LPVOID Data,int height)
  {
  ListElem FAR *h = CopyData (Data,height);
  h->Prev = NULL ;
  h->Next = head ;
  if (head != NULL)
    head->Prev = h;
  else
    tail = h;
  head = h;
  h->isSel = (* IsSelected) (h->Data);
  }


/*-------------------------------------------------------------------*\
*  member function:  RemoveHead                                       *
*                                                                     *
\*-------------------------------------------------------------------*/
void DDSList::RemoveHead ()
  {
  if (head != NULL) {
    ListElem FAR *h = head->Next;
    if (h != NULL) h->Prev = NULL;
    FreeGlobMem (head);
    head = h;
    if (head == NULL) tail = NULL ;
    BegReached = FALSE ;
    }
  CheckCurrentElem ();
  }

/*-------------------------------------------------------------------*\
*  member function:  RemoveTail                                       *
*                                                                     *
\*-------------------------------------------------------------------*/
void DDSList::RemoveTail ()
  {
  if (tail != NULL) {
    ListElem FAR *h = tail->Prev;
    if (h != NULL) h->Next = NULL ;
    FreeGlobMem (tail);
    tail = h;
    if (tail == NULL) head = NULL ;
    EndReached = FALSE ;
    }
  CheckCurrentElem ();
  }


/*-------------------------------------------------------------------*\
*  member function:  Fill                                             *
*                                                                     *
\*-------------------------------------------------------------------*/
void DDSList::Fill (int StartYPos, LPVOID StartData, int startHeight)
  {
  if (StartData != NULL) {
    DBWIN_ASSERT (startHeight == 0);
    int height;
    LPVOID Data = (* Initialize) (StartData, bData, 0, &height,NULL);
    LPVOID FirstData = NULL ;
    if (Data == NULL) Home (FALSE) ;   // FillHead (startHeight);
    else {
      BegReached = FALSE ;
      int actheight = hdHeight ;
      for ( int i = 0 ; actheight < wheight ; i ++  ) {
        if (i > 0) {
          if (i == 1) // einen von hinten holen, damit die selektion
                      // schoen sichtbar ist
            Data = (* GetPrev) (head->Data,0, &height,NULL) ;
          else
            Data = (* GetNext) (tail->Data, 0, &height,NULL) ;
          }
        if (i == 1) {
          if (!(BegReached = (Data == NULL))) {
            AddHead (Data,height);
            if (CurrentElem == NULL) CurrentElem = head ;
            actheight += height;
            }
          }
        else {
          if (!(EndReached = (Data == NULL))) {
            AddTail (Data,height);
            if (i == 0) {
              if (CurrentElem == NULL) {
                CurrentElem = head ;
                FirstData = head->Data ;
                }
              }
            actheight += height;
            }
          else
            break;
          }
        }
      if (actheight < wheight)
        FillHead (actheight);
      gheight = actheight;
      if (FirstData)
        (* Notify) (FirstData,DDSLIST_DEFSEL,bData);
      }
    }
  else {
    CurrentElem = NULL ;
    if (fillbackward)
      FillHead (startHeight);
    else
      FillTail (startHeight);
    }
  }


/*-------------------------------------------------------------------------*\
*  member function:  SetTail                                                *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::SetTail ()
  {
  tail = NULL ;
  for ( ListElem FAR *h = head ; h != NULL ; h = h->Next) {
    if (h->Next == NULL) {
      tail = h ;
      break ;
      }
    }
  }
  

/*-------------------------------------------------------------------------*\
*  member function:  InsertElem                                             *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::InsertElem (LPVOID ElemToStart, LPVOID ElemToInsert)
  {
  int  y = 0;
  int  height;

  LPVOID Data;
  ListElem FAR *NewElem;
  
  if (ElemToInsert != NULL) 
    Data = (* Initialize) (ElemToInsert, bData, 0, &height,NULL); // Startelement holen
  else
    Data = (* GetFirst) (bData, 0, &height,NULL,NULL);

  if (ElemToStart == NULL) {
    // am Anfang der gesamten Liste eintragen
    LPVOID pData = NULL;
    if (BegReached) {
      // Auf jeden Fall einfuegen
      AddHead (Data,height);
      NewElem = head;
      }
    else if ((pData = (* GetPrev) (head->Data, 0, &height,NULL)) != NULL) {
      // Der Beginn der Liste war nicht drauf -> Nur die Daten wieder freigeben, sonst nichts tun
      (* Notify) (pData,DDSLIST_RELEASEELE,bData);
      FreeGlobMem (pData);
      }
    }
  else {
    for (ListElem FAR* h = head; h != NULL; h = h->Next) {
      if ((* CompareData) (ElemToStart, h->Data,FALSE)) {
          NewElem = CopyData (Data, height);  
        NewElem->Prev = h; 
          NewElem->Next = h->Next;
            if (h->Next != NULL)
              h->Next->Prev = NewElem;
        else
            tail = NewElem;
            h->Next = NewElem;
            NewElem->isSel = (* IsSelected) (NewElem->Data);
        break;
        }
      }
    }
    
  // Am Ende alle unsichtbaren Elemente wieder rausnehmen
  BOOL doInvalidate = FALSE ;
  int gheight = hdHeight;
  for (ListElem FAR *h = head ; h != NULL ; ) {
    ListElem FAR *next = h->Next;
    if ((gheight >= wheight) && (h->Prev != NULL)) {
      (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
      h->Prev->Next = NULL;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      FreeGlobMem (h);
      EndReached = FALSE;
      }
    else {
      gheight += h->height;
      if (h == NewElem) doInvalidate = TRUE ;
      BOOL nwSel = (* IsSelected) (h->Data);
      if ((doInvalidate) || (nwSel != h->isSel))
        InvalidateElem (h);
      h->isSel = nwSel;
      }
    h = next;
    }
  SetTail ();
  CheckCurrentElem ();
  }

/*-------------------------------------------------------------------------*\
*  member function:  CheckTail                                              *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::CheckTail ()
  {
  gheight = hdHeight;
  for (ListElem FAR *h = head ; h != NULL ; ) {
    ListElem FAR *next = h->Next;
    if ((gheight + yOffsToShow >= wheight) && (h->Prev != NULL)) {
      if (h->Prev != NULL)
        h->Prev->Next = h->Next;
      else
        head = h->Next;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      else
        tail = h->Prev;
      (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
      FreeGlobMem (h);
      EndReached = FALSE;
      }
    else
      gheight += h->height;
    h = next;
    }
  SetTail ();
  if ((gheight + yOffsToShow < wheight) && (IsWindow (hWndList))) {
    RECT rc;
//    GetClientRect (hWndList,&rc);
    GetScrollRect (hWndList, &rc);  // beruecksichtigt die Buttons!!
    rc.top = gheight;
    InvalidateRect (hWndList,&rc,FALSE);
    CheckCurrentElem ();
    FillTail (gheight);
    }
  }
     
BOOL DDSList::IsFullOnScreen (ListElem FAR *x)
  {
  int y = hdHeight;
  for (ListElem FAR *h = head ; ((h != NULL) && (h != x)) ; h = h->Next) {
    y += h->height;
    }
  if (h == x)
    return (((y + h->height) <= wheight + 2) || (h->Prev == NULL)) ;    // 2.. Ein bisschen reserve sollte schon sein, wegen Rundungsfehler etc
  else
    return FALSE ;
  }

BOOL DDSList::IsFullOnScreen (ListElem FAR *x,int sollExtra)
  {
  int y = hdHeight + sollExtra;
  for (ListElem FAR *h = head ; ((h != NULL) && (h != x)) ; h = h->Next) {
    y += h->height;
    }
  if (h == x)
    return (((y + h->height) <= wheight + 2) || (h->Prev == NULL)) ;    // 2.. Ein bisschen reserve sollte schon sein, wegen Rundungsfehler etc
  else
    return FALSE ;
  }

BOOL DDSList::AnzElems ()
  {
  int i = 0 ;
  for ( ListElem FAR *h = head ; h != NULL ; h = h->Next) i++ ;
  return i;
  }

/*-------------------------------------------------------------------------*\
*  member function:  FillTail                                               *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::FillTail (int actheight,BOOL FAR *dobreak)
  {
  for ( ; actheight < wheight ; ) {
    int height;
    LPVOID Data;
    if (tail != NULL) {
      if (!EndReached) 
        Data = (* GetNext) (tail->Data, 0, &height,NULL) ;
      else
        Data = NULL ;
      }
    else {
      Data = (* GetFirst) (bData, 0, &height,NULL,dobreak) ;
      if ((dobreak) && (*dobreak)) return;
      BegReached = TRUE ;
      }
    if (!(EndReached = (Data == NULL))) {
      AddTail (Data,height);
      actheight += height;
      }
    else
      break;
    }
  gheight = actheight;
  }
    
/*-------------------------------------------------------------------------*\
*  member function:  FillHead                                               *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::FillHead (int actheight)
  {
  for ( ; actheight < wheight ; ) {
    int height;
    LPVOID Data ;
    if (head != NULL) {
      if (!BegReached)
        Data = (* GetPrev) (head->Data, 0, &height,NULL) ;
      else
        Data = NULL ;
      }
    else
      Data = (* GetLast) (bData, 0, &height,NULL,NULL) , EndReached = TRUE ;
    if (!(BegReached = (Data == NULL))) {
      AddHead (Data,height);
      actheight += height;
      }
    else
      break;
    }
  gheight = actheight;
  }
    
/*-------------------------------------------------------------------------*\
*  member function:  CheckSelections                                        *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport void _export WINAPI DDSList::CheckSelections (BOOL doIV)
  {
  for (ListElem FAR *h = head ; h != NULL ; h = h->Next) {
    BOOL nwSel = (* IsSelected) (h->Data);
    if ((IsWindow (hWndList)) && (nwSel != h->isSel) && (doIV)) {
      InvalidateElem (h);
      }
    h->isSel = nwSel;
    }
  }

DLLExport BOOL _export WINAPI DDSList::TryToSetCurrentElem (LPVOID ElemToSetCurrent)
  {
  BOOL found = FALSE ;
  for ( ListElem FAR *h = head ; h != NULL ; h = h->Next) {
    if ((* CompareData) (ElemToSetCurrent, h->Data,FALSE)) {
      found = TRUE ;
      CurrentElem = h;
      break ;
      }
    }
  return found ;
  }

DLLExport void _export WINAPI DDSList::CheckSelections_scroll (BOOL lower,BOOL doIV)
  {
  CheckSelections(doIV);
  if (head != NULL) {
    if (CurrentElem == NULL)
      CurrentElem = (lower) ? tail : head ;
    (* Notify) (CurrentElem->Data,DDSLIST_DEFSEL,bData);
    CheckSelections (doIV);
    }
  }
  
/*-------------------------------------------------------------------------*\
*  member function:  RemoveElem                                             *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::RemoveElem (LPVOID ElemToRemove)
  {
  int y = hdHeight;
  RECT rc;

  GetScrollRect (hWndList, &rc);
  for (ListElem FAR* h = head; h != NULL; ) {
    ListElem FAR *next = h->Next;
    if ((* CompareData) (ElemToRemove, h->Data,FALSE)) {
      if (h->Prev != NULL)
        h->Prev->Next = h->Next;
      else
        head = h->Next;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      else
        tail = h->Prev;

      (* Notify) (h->Data,DDSLIST_REMOVEELE,bData);
      FreeGlobMem (h);

      // ab dem geaenderten Element zeichnen
      rc.top = y + yOffsToShow;
      if (IsWindow (hWndList)) {
        InvalidateRect (hWndList, &rc, FALSE);
        }
      }   // END IF (CompareData(...
    else 
      y += h->height;
    h = next;
    }   // END FOR (ListElem....
    
  CheckCurrentElem ();
  FillTail (y);
  CheckSelections (TRUE);
  }
  
void DDSList::ReleaseElem (LPVOID ElemToRemove)
  {
  int y = hdHeight;
  RECT rc;

  GetScrollRect (hWndList, &rc);
  for (ListElem FAR* h = head; h != NULL; ) {
    ListElem FAR *next = h->Next;
    if ((* CompareData) (ElemToRemove, h->Data,FALSE)) {
      if (h->Prev != NULL)
        h->Prev->Next = h->Next;
      else
        head = h->Next;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      else
        tail = h->Prev;

      (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
      FreeGlobMem (h);
      // ab dem geaenderten Element zeichnen
      rc.top = y + yOffsToShow;
      if (IsWindow (hWndList)) {
        InvalidateRect (hWndList, &rc, FALSE);
        }
      }   // END IF (CompareData(...
    else 
      y += h->height;
    h = next;
    }   // END FOR (ListElem....
  CheckCurrentElem ();
  }
  
/*-------------------------------------------------------------------------*\
*  member function:  DestroyList                                            *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport void _export WINAPI DDSList::DestroyList ()
  {
  CurrentElem = NULL;
  for (ListElem FAR *h = head ; h != NULL ; ) {
    ListElem FAR *next = h->Next;
    (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
    FreeGlobMem (h);
    h = next;
    }
  (* Notify) (bData,DDSLIST_DESTROYLIST,bData);
  head = tail = NULL;
  BegReached = EndReached = FALSE ;
  }


void DDSList::InvalidateFull ()
  {
  if (IsWindow (hWndList)) {
    RECT rc;
    GetScrollRect (hWndList, &rc);
    InvalidateRect (hWndList, &rc, TRUE);
    }
  }
  
/*-------------------------------------------------------------------------*\
*  member function:  RefreshList                                            *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::RefreshList (int mode,LPVOID StartData)
  {
  LPVOID buffer;
  BOOL headDone;
  if (head != NULL) {
    int DataSize = GetBlockSize (head) - sizeof(*(head)) + 1;
    buffer = GetGlobMem (DataSize);
    lmemcpy (buffer,head->Data,DataSize);
    headDone = TRUE ;
    }
  else
    headDone = FALSE ;

  DestroyList ();
  InvalidateFull ();

  if (StartData == NULL) {
    if (fillbackward)
      End ();
    else
      Home ();
    }
  else {
    Fill (0,StartData);
    if (CurrentElem == NULL) {
      if (fillbackward)
        CurrentElem = tail;
      else
        CurrentElem = head;
      }
    if (CurrentElem != NULL)
      (* Notify) (CurrentElem->Data,DDSLIST_DEFSEL,bData);
    if (fillbackward)
      SelSub (-1,TRUE,FALSE);
    else
      SelSub (1,TRUE,FALSE);
    if (SelSubLines != NULL) {
      RECT rcWnd,rcAct;
      GetScrollRect (hWndList,&rcWnd);
      CalculateElemRect (CurrentElem,&rcAct,yOffsToShow);
      rcAct.bottom = rcAct.top + LineStop ;
      if (rcAct.bottom > rcWnd.bottom) {
        // Nur soviel scrollen, dass die Zeile gerade noch sichtbar wird
        yOffsToShow = rcWnd.bottom - rcAct.bottom ;
        }
      }
    else
      CheckCurrentVisible (TRUE);

    //
    // Jetzt Versuchen, den zuletzt vordersten Satz wieder an die 1. Stelle 
    // zu setzen
    //
    BOOL headFound = FALSE ;
    for ( ListElem FAR *h = head ; ((h != NULL) && (headDone)) ; h = h->Next ) {
      if ((* CompareData) (buffer, h->Data,TRUE)) {
        headFound = TRUE ;
        }
      }
    if (headFound) {
      // So lange vorne wegnehmen, bis die Position wieder stimmt...
      for ( BOOL first = TRUE ; ((CurrentElem) && (headDone)) ; ) {
        if (!IsFullOnScreen(CurrentElem,wheight / 2)) {
          if (!first) {
            (* Notify) (head->Data, DDSLIST_RELEASEELE,bData);
            RemoveHead ();
            FillTail (FullHeight());
            }
          break ;
          }
        if ((* CompareData) (buffer, head->Data,TRUE)) {
          FillHead (FullHeight ());
          break ;   // Wunderbar, gefunden
          }

        // Und wieder einen wegschneiden..
        if (head != CurrentElem) {
          (* Notify) (head->Data, DDSLIST_RELEASEELE,bData);
          RemoveHead ();
          FillTail (FullHeight());
          }
        else
          break ;
        }
      }
    else {
      for ( BOOL first = TRUE ; ((CurrentElem) && (headDone)) ; ) {
        if (!IsFullOnScreen(CurrentElem,wheight / 2)) {
          if (!first) {
            (* Notify) (head->Data, DDSLIST_RELEASEELE,bData);
            RemoveHead ();
            FillTail (FullHeight());
            }
          break ;
          }
        if ((* CompareData) (buffer, head->Data,TRUE))
          break ;   // Wunderbar, gefunden

        LPVOID Data ;
        int height;
        if (!BegReached)
          Data = (* GetPrev) (head->Data, 0, &height,NULL) ;
        else
          Data = NULL ;
        if (!(BegReached = (Data == NULL))) {
          AddHead (Data,height);
          }
        else
          break;

        first = FALSE ;
        }
      }
    CheckSelections (TRUE);
    CheckCurrentVisible (TRUE);
    // Nicht mehr benoetigte Datenelemente am Ende rausnehmen
    for ( ; ((tail != NULL) && (FullHeight () + yOffsToShow - tail->height > wheight)) ; ) {
      (* Notify) (tail->Data,DDSLIST_RELEASEELE,bData);
      RemoveTail () ;
      }
    NotifyFocus ();
    }
  if (headDone)
    FreeGlobMem (buffer);
  }
  
/*-------------------------------------------------------------------------*\
*  member function:  UpDateElement                                          *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::UpdateElement (LPVOID ElemToUpDate)
  {
  int y = hdHeight;
  RECT rc;

  if (IsWindow (hWndList))
//    GetClientRect (hWndList, &rc);
    GetScrollRect (hWndList, &rc);  // beruecksichtigt die Buttons!!
  else
    SetRectEmpty (&rc);
  for (ListElem FAR* h = head; h != NULL; h = h->Next) {
    if ((* CompareData) (ElemToUpDate, h->Data,FALSE)) {
      int height;
      LPVOID res = (* Update) (h->Data , 0, &height,NULL,0L,0L);

      rc.top = y + yOffsToShow;
      if (res != NULL) {
        if (h->height == height)
          rc.bottom = rc.top + height;
        h->height = height;
        }
      if (IsWindow (hWndList))
        InvalidateRect (hWndList, &rc, FALSE);

      if (res == NULL) {
        // Das Element muss freigegeben werden
        if (h->Prev != NULL)
          h->Prev->Next = h->Next;
        else
          head = h->Next;
        if (h->Next != NULL)
          h->Next->Prev = h->Prev;
        else
          tail = h->Prev;

        (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
        FreeGlobMem (h);
        }

      break;
      }   // END IF (CompareData(...

    y += h->height;
    }   // END FOR (ListElem....
    
  CheckCurrentElem ();
  if (SelSubLines == NULL)
    CheckTail ();
  else
    SelSub (1,TRUE,TRUE);
  CheckSelections (TRUE);
  }

void DDSList::InnerUpdateList (DWORD utp,DWORD utf)
  {
  int y = hdHeight;
  RECT rc;

  if (IsWindow (hWndList))
//    GetClientRect (hWndList, &rc);
    GetScrollRect (hWndList, &rc);  // beruecksichtigt die Buttons!!
  else
    SetRectEmpty (&rc);
  for (ListElem FAR* h = head; h != NULL; ) {
    ListElem FAR *next = h->Next;
    int height = h->height;
    LPVOID res = (* Update) (h->Data , 0, &height,NULL, utp, utf);

    rc.top = y + yOffsToShow;
    if (res != NULL) {
      if (h->height == height)
        rc.bottom = rc.top + height;
      h->height = height;
      }
    if (IsWindow (hWndList))
      InvalidateRect (hWndList, &rc, FALSE);

    if (res == NULL) {
      // Das Element muss freigegeben werden
      if (h->Prev != NULL)
        h->Prev->Next = h->Next;
      else
        head = h->Next;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      else
        tail = h->Prev;

      (* Notify) (h->Data,DDSLIST_RELEASEELE,bData);
      FreeGlobMem (h);
      }
    else
      y += h->height;
    h = next;
    }   // END FOR (ListElem....
    
  CheckCurrentElem ();
  if (SelSubLines == NULL)
    CheckTail ();
  else
    SelSub (1,TRUE,TRUE);
  CheckSelections (TRUE);
  }

/*-------------------------------------------------------------------------*\
*  member function:  ExistElem                                              *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
BOOL DDSList::ExistElem(ListElem FAR *x)
  {
  BOOL res = FALSE;
  for (ListElem FAR *h = head ; ((h != NULL) && (!res)) ; h = h->Next)
    res = (x == h);
  return res;
  }

/*-------------------------------------------------------------------------*\
*  member function:  Find                                                   *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
ListElem FAR *DDSList::Find (LPPOINT pt,BOOL dontResetOld,BOOL SetNew)
  {
  ListElem FAR *h = head;
  for (int i = hdHeight + yOffsToShow ; ((h != NULL) && !((pt->y > i) && (pt->y <= i + h->height))) ; ) {
    i += h->height;
    h = h->Next;
    }
  if ((h != NULL) && (SelSubLines != NULL)) {
    RECT rcElem,rcWnd;
    char svBuffer[64];
    int ostart,ostop;
    int yMin = 10000 ;
    ListElem FAR *old = CurrentElem ;
    if (SetNew)
      SetCurrentElem (h,TRUE,dontResetOld);
    else
      CurrentElem = h ;
    CalculateElemRect (h,&rcElem,yOffsToShow);
    GetScrollRect (hWndList,&rcWnd);
    int oldStart = LineStart;
    int oldStop = LineStop;
    for ( SelSub (1,TRUE,FALSE) ; ; ) {
      int ay = rcElem.top + LineStart - pt->y ;
      if ((rcElem.top + LineStart <= pt->y) && (rcElem.top + LineStop >= pt->y))
        ay = 0 ;  // Gefunden, der hat absoluten Vorrang

      if (ay < 0) ay = -ay ;
      if (ay < yMin) {
        lmemcpy (svBuffer,SelSubLines_Buffer,GetBlockSize(SelSubLines_Buffer)) ;
        ostart = LineStart ;
        ostop = LineStop ;
        yMin = ay ;
        }
      if (!SelSub(1,FALSE,FALSE)) break ;
      }
    if (yMin < 10000) {
      lmemcpy (SelSubLines_Buffer,svBuffer,GetBlockSize(SelSubLines_Buffer)) ;
      LineStart = ostart ;
      LineStop = ostop ;
      // Auf jeden fall sichtbar machen
      int toScroll = 0 ;
      if (rcElem.top + LineStop > rcWnd.bottom)
        toScroll = rcWnd.bottom - (rcElem.top + LineStop) ;
      if (rcElem.top + LineStart < rcWnd.top)
        toScroll = rcWnd.top - (rcElem.top + LineStart) ;
      if (toScroll)
        Scroll (toScroll);
      yOffsToShow += toScroll ;

      if (LineStart != oldStart) {
        InvalidateElemLine (CurrentElem,LineStart,LineStop);
        InvalidateElemLine (CurrentElem,oldStart,oldStop);
        }
      }
    if (SetNew)
      SetCurrentElem (old,FALSE,dontResetOld);
    }
  return h;
  }



/*-------------------------------------------------------------------------*\
*  member function:  SetCurrentElem                                         *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::SetCurrentElem (ListElem FAR * h,BOOL doIV,BOOL dontResetOld)
  {
  CurrentElem = h;
  if (CurrentElem != NULL) {
    if (dontResetOld)
      (* Notify) (CurrentElem->Data, DDSLIST_FORCESEL, bData);
    else
      (* Notify) (CurrentElem->Data, DDSLIST_FOCUSELE, bData);
    }
  else
    (* Notify) (NULL, DDSLIST_FOCUSELE,bData);
  CheckSelections (doIV);
  }
void DDSList::NotifyFocus ()
  {
  if (CurrentElem != NULL)
    (* Notify) (CurrentElem->Data, DDSLIST_SELCHANGE,bData);
  else
    (* Notify) (NULL, DDSLIST_SELCHANGE,bData);
  }
  

static BOOL Captured = FALSE;
static BOOL TimerSet = FALSE;
static POINT ptCap;

DLLExport void _export WINAPI doCaptureOff ()
  {
  if (Captured) {
    Captured = FALSE;
    ReleaseCapture ();
    }
  }

/*-------------------------------------------------------------------------*\
*  member function:  FullHeight                                             *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
int DDSList::FullHeight ()
  {
  int res = hdHeight;
  for (ListElem FAR *h = head ; h != NULL ; h = h->Next)
    res += h->height;
  gheight = res;
  return res;
  }
  
DDSList FAR *_lst;
//--------------------------  GetScrollRect  --------------------------------
//
// Groesse des Zeichenfensters fuer Listeneintraege (ohne Header und Buttons)
//---------------------------------------------------------------------------
void DDSList::GetScrollRect (HWND hWnd, LPRECT r)
  {
  GetClientRect (hWnd,r);
  r->top += hdHeight;
  if (buttons != NULL)                          // gibts jetzt Knˆpfe?
    switch (buttons->GetButtonPos()) {          // und wo sind die?
      case BTN_BOTTOM_POS:                      // Aha, also unten
        r->bottom -= buttons->GetHeight();      // mal ein biﬂchen verkleinern
        break;
      case BTN_RIGHT_POS:                       // oder rechts?
        r->right -= buttons->GetWidth() - 1;
        break;
      }  
  }

void DDSList::InitializeSize ()
  {
  RECT r;
  GetClientRect (ListWnd(),&r);
  wheight = r.bottom;
  if (buttons != NULL)
    switch (buttons->GetButtonPos()) {          // und wo sind die?
      case BTN_BOTTOM_POS:                      // Aha, also unten
        wheight -= buttons->GetHeight();        // mal ein biﬂchen verkleinern
        break;
      case BTN_RIGHT_POS:                       // oder rechts?
        r.right -= buttons->GetWidth();
        break;
      }
  }

#define WR_ERROR        0
#define WR_SELECTFROMH  1
#define WR_SELECTTOH    2
#define WR_SELECTFWHOLE 3
void DDSList::SelectWholeRange (ListElem FAR *h,WORD Command)
  {
#ifdef UEBERLEGT
  int Type = WR_ERROR ;
  ListElem FAR *FirstSelected = NULL;
  ListElem FAR *LastSelected = NULL;
  BOOL hFound = FALSE ;
  for (ListElem FAR *x = head ; x != NULL ; x = x->Next) {
    if (x == h) {
      hFound = TRUE ;
      if (FirstSelected == NULL) Type = WR_SELECTFROMH ;
      else                       Type = WR_SELECTTOH ;
      }
    if ((* IsSelected) (x->Data)) {
      LastSelected = x ;
      if (Type == WR_SELECTTOH)
        Type = WR_SELECTFWHOLE ;
      if (FirstSelected == NULL) {
        FirstSelected = x;
        }
      }
    }
  if (FirstSelected == NULL) FirstSelected = h;
  if (LastSelected == NULL) LastSelected = h;
  ListElem FAR *first = NULL,FAR *last = NULL;
  switch (Type) {
    case WR_SELECTFROMH :
      first = h;
      last = LastSelected ;
      break ;
    case WR_SELECTTOH :
      first = FirstSelected ;
      last = h ;
      break ;
    case WR_SELECTFWHOLE :
      first = FirstSelected ;
      last = LastSelected ;
      break ;
    }
  DBWIN_ASSERT ((first != NULL) && (last != NULL)) ;
  for (x = first ; x != NULL ; x = x->Next) {
    (* Notify) (x->Data,DDSLIST_FORCESEL,bData);
    if (x == last) break ;
    }
  DBWIN_ASSERT (x != NULL);
#endif
  if (h != NULL) {
    CurrentElem = h;
    (* Notify) (CurrentElem->Data, DDSLIST_FORCESEL, bData);
    (* Notify) (NULL, Command, bData);
    }
  }

void DDSList::CheckCurrentVisible (BOOL doIV)
  {
  if (CurrentElem == tail) {
    BOOL done = FALSE ;
    for (ListElem FAR *h = head ; ((h != NULL) && (head != tail) && (!IsFullOnScreen(tail))) ; h = head ) {
      if (h->Next != NULL) {
        (* Notify) (h->Data, DDSLIST_RELEASEELE,bData);
        RemoveHead ();
        done = TRUE ;
        }
      }
    if (done) {
      if (!EndReached) {
        FillTail (FullHeight());
        }
      
      if (doIV) InvalidateFull ();
      }
    }
  gheight = FullHeight ();
  }

BOOL DDSList::AdditionalMultiSel ()
  {
  BOOL res = FALSE;
  (* Notify) (&res, DDSLIST_ALLOWMULTISEL,bData);
  return res ;
  }

//---------------------------------------------------------------------------
// Abfrage ob die Liste multiselektionsfaehig ist.
//---------------------------------------------------------------------------
BOOL DDSList::isMultiSel ()
  {
  BOOL res = FALSE;
  (* Notify) (&res, DDSLIST_ISMULTISEL,bData);
  return res ;
  }

//--------------------------------------------------------------------------------
// Pfeiltasten ...
//--------------------------------------------------------------------------------
BOOL DDSList::InsertAtHead ()
  {
  if ((head != NULL) && (!BegReached)) {
    int height ;
    LPVOID Data = (*GetPrev) (head->Data,0,&height,NULL);
    if (Data != NULL)
      AddHead (Data,height);
    else
      BegReached = TRUE ;

    return (Data != NULL) ;
    }
  else
    return FALSE ;
  }

BOOL DDSList::InsertAtTail ()
  {
  if ((tail != NULL) && (!EndReached)) {
    int height ;
    LPVOID Data = (*GetNext) (tail->Data,0,&height,NULL);
    if (Data != NULL)
      AddTail (Data,height);
    else
      EndReached = TRUE ;

    return (Data != NULL) ;
    }
  else
    return FALSE ;
  }

void DDSList::InvalidateElemLine (ListElem FAR *h,int y1,int y2)
  {
  RECT rc;
  CalculateElemRect (h,&rc,yOffsToShow);
  rc.bottom = rc.top + y2 ;
  rc.top += y1 ;
  InvalidateRect (hWndList,&rc,TRUE);
  }

BOOL DDSList::SelSub (int dir,BOOL firstOfEntry,BOOL doScroll)
  {
  if ((SelSubLines != NULL) && (CurrentElem != NULL)) {
    HDC hDC = GetDC (hWndList);
    int oldStart = LineStart,oldStop = LineStop ;
    BOOL res = (* SelSubLines) (dir,&LineStart,&LineStop,hDC,firstOfEntry,CurrentElem->Data,SelSubLines_Buffer,FALSE);
    ReleaseDC (hWndList,hDC);
    if ((res) && (doScroll)) {
      RECT rc,rcWnd;
      CalculateElemRect (CurrentElem,&rc,yOffsToShow);
      rc.bottom = rc.top + LineStop ;
      rc.top += LineStart ;
      GetScrollRect (hWndList,&rcWnd);
      int toScroll = 0;
      // Nach unten
      if (rc.bottom > rcWnd.bottom)
        toScroll = rcWnd.bottom - rc.bottom ;
      else {
        if (rc.top < rcWnd.top)
          toScroll = rcWnd.top - rc.top ;
        }
      if ((toScroll) && (!firstOfEntry)) Scroll (toScroll) ;
      yOffsToShow += toScroll ;
      InvalidateElemLine (CurrentElem,LineStart,LineStop);
      InvalidateElemLine (CurrentElem,oldStart,oldStop);
      }
    return res ;
    }
  else
    return FALSE ;
  }

void DDSList::Scroll (int h)
  {
  RECT scr;
  GetScrollRect (hWndList,&scr);
  ScrollWindow (hWndList, 0, h, NULL, &scr);
  }

void DDSList::InvalidateElem (ListElem FAR *h)
  {
  RECT rc;
  CalculateElemRect (h,&rc,yOffsToShow);
  InvalidateRect (hWndList,&rc,TRUE);
  }

void DDSList::LineUp (BOOL ShiftPressed,BOOL ControlPressed)
  {
  if (CurrentElem != NULL) {
    ListElem FAR *oldElem = CurrentElem ;
    ListElem FAR *oldHead = head ;
    BOOL doScroll ;
    if (SelSubLines) {
      if (SelSub (-1,FALSE,TRUE)) {
        doScroll = FALSE ;
        // Nicht mehr benoetigte Datenelemente am Ende rausnehmen
        for ( ; FullHeight () + yOffsToShow - tail->height > wheight ; ) {
          (* Notify) (tail->Data,DDSLIST_RELEASEELE,bData);
          RemoveTail () ;
          }
        }
      else
        doScroll = TRUE ;
      }
    else
      doScroll = ((CurrentElem->Prev != NULL) || (!BegReached)) ;

    if (doScroll) {
      ListElem FAR *h;
      int toScroll = 0;
      if (CurrentElem->Prev != NULL)
        h = CurrentElem->Prev ;
      else {
        if (InsertAtHead ()) {
          h = head ;
          if (SelSubLines == NULL)
            toScroll = head->height ;
          else
            yOffsToShow -= head->height ;
          }
        else
          doScroll = FALSE ;
        }

      if (doScroll) {
        if ((AdditionalMultiSel ()) && (ShiftPressed)) {
          SelectWholeRange (h,DDSLIST_SELRANGE_ACTIVE);
          CheckSelections (TRUE);
          }
        else {
          if (AdditionalMultiSel() && ControlPressed) {
            InvalidateElem (CurrentElem);
            CurrentElem = h ;
            InvalidateElem (h);
            }
          else
            SetCurrentElem (h,TRUE,FALSE);
          }
        if (SelSubLines != NULL) {
          if (SelSub (-1,TRUE,FALSE)) {
            RECT rcAct,rcWnd;
            GetScrollRect (hWndList,&rcWnd);
            CalculateElemRect (CurrentElem,&rcAct,yOffsToShow);
            rcAct.top += LineStart ;
            if (rcAct.top < rcWnd.top) {
              // Nur soviel scrollen, dass die Zeile gerade noch sichtbar wird
              yOffsToShow += rcWnd.top - rcAct.top ;
              toScroll += rcWnd.top - rcAct.top ;
              }
            }
          }
        for ( ; FullHeight () + yOffsToShow - tail->height > wheight ; ) {
          (* Notify) (tail->Data,DDSLIST_RELEASEELE,bData);
          RemoveTail () ;
          }
        if (toScroll)
          Scroll (toScroll);
        InvalidateElem (oldElem);
        if ((nonRepeativePaint) && (toScroll))
          InvalidateElem (oldHead);
        InvalidateElem (CurrentElem);
        }
      }
    }
  }

void DDSList::LineDown (BOOL ShiftPressed,BOOL ControlPressed)
  {
  if (CurrentElem != NULL) {
    ListElem FAR *oldElem = CurrentElem ;
    BOOL doScroll ;
    if (SelSubLines) {
      if (SelSub (1,FALSE,TRUE)) {
        for ( ; (- yOffsToShow > head->height) ; ) {
          yOffsToShow += head->height ;
          (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
          RemoveHead ();
          }
        doScroll = FALSE ;
        }
      else
        doScroll = TRUE ;
      }
    else
      doScroll = ((CurrentElem->Next != NULL) || (!EndReached)) ;

    if (doScroll) {
      ListElem FAR *h;
      int toScroll = 0;
      if (CurrentElem->Next != NULL) {
        h = CurrentElem->Next ;
        if (SelSubLines == NULL) {
          for (  ; ((h != head) && (!IsFullOnScreen (h))) ; ) {
            toScroll -= head->height ;
            (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
            RemoveHead ();
            }
          }
        }
      else {
        if (InsertAtTail ()) {
          h = CurrentElem->Next ;
          if (SelSubLines == NULL) {
            for (  ; ((h != head) && (!IsFullOnScreen (h))) ; ) {
              toScroll -= head->height ;
              (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
              RemoveHead ();
              }
            }
          }
        else
          doScroll = FALSE ;
        }

      if (doScroll) {
        FillTail (FullHeight());
        if ((AdditionalMultiSel ()) && (ShiftPressed)) {
          SelectWholeRange (h,DDSLIST_SELRANGE_ACTIVE);
          CheckSelections (TRUE);
          }
        else {
          if (AdditionalMultiSel() && ControlPressed) {
            InvalidateElem (CurrentElem);
            CurrentElem = h ;
            InvalidateElem (h);
            }
          else
            SetCurrentElem (h,TRUE,FALSE);
          }
        if (SelSubLines) {
          if (SelSub (1,TRUE,FALSE)) {
            RECT rcAct,rcWnd;
            GetScrollRect (hWndList,&rcWnd);
            CalculateElemRect (CurrentElem,&rcAct,yOffsToShow);
            rcAct.bottom = rcAct.top + LineStop ;
            if (rcAct.bottom > rcWnd.bottom) {
              // Nur soviel scrollen, dass die Zeile gerade noch sichtbar wird
              yOffsToShow += rcWnd.bottom - rcAct.bottom ;
              toScroll += rcWnd.bottom - rcAct.bottom ;
              // Am Kopf alle nicht sichtbaren wegnehmen
              for ( ; (head->height < - yOffsToShow) ; ) {
                yOffsToShow += head->height ;
                (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
                RemoveHead ();
                }
              }
            }
          }
        if (toScroll)
          Scroll (toScroll);

        if ((nonRepeativePaint) && (toScroll))
          InvalidateElem (head);

        InvalidateElem (oldElem);
        InvalidateElem (CurrentElem);
        }
      }
    }
  }

void DDSList::Home (BOOL doIV,BOOL CheckKeys)
  {
  ListElem FAR *old = CurrentElem ;
  int oldyOffsToShow = yOffsToShow ;
  char svBuffer[64];
  if (SelSubLines_Buffer != NULL)
    lmemcpy (svBuffer,SelSubLines_Buffer,sizeof(SelSubLines_Buffer));
  BOOL doIVFull,doIVCurrent;
  if (!BegReached) {
    DestroyList ();
    BOOL doBreak = FALSE;
    FillTail (hdHeight,&doBreak);
    if (doBreak) return ;   // Hat alles schon jemand anderer gemacht...
    doIVFull = TRUE ;
    }
  else
    doIVFull = FALSE ;
  BOOL ShiftPressed,ControlPressed;
  if (CheckKeys) {
    ShiftPressed = (GetKeyState (VK_SHIFT) < 0) ;
    ControlPressed = (GetKeyState (VK_CONTROL) < 0) ;
    }
  else {
    ShiftPressed = FALSE ;
    ControlPressed = FALSE ;
    }
  if (AdditionalMultiSel() && ShiftPressed) {
    SelectWholeRange (head,DDSLIST_SELRANGE_HOME);
    CheckSelections (doIV);
    SetCurrentElem (head,doIV,TRUE);
    }
  else {
    if (AdditionalMultiSel() && ControlPressed) {
      if (doIV)
        InvalidateElem (CurrentElem);
      CurrentElem = head ;
      if (doIV)
        InvalidateElem (head);
      }
    else
      SetCurrentElem (head,doIV,FALSE);
    }

  SelSub (1,TRUE,FALSE);
  doIVCurrent = (CurrentElem != old) ;
  if (SelSubLines == NULL) {
    CheckSelections (doIV);
    CheckCurrentVisible (doIV);
    }
  else {
    CheckSelections (doIV);
    yOffsToShow = 0;
    if (SelSubLines_Buffer != NULL)
      doIVCurrent = doIVCurrent || (!lmemcmp (svBuffer,SelSubLines_Buffer,sizeof(SelSubLines_Buffer)));
    }
  doIVFull = doIVFull || (yOffsToShow != oldyOffsToShow) ;
  if ((doIVFull) && (doIV))
    InvalidateFull ();
  else if ((doIVCurrent) && (doIV)) {
    InvalidateElem (old);
    InvalidateElem (CurrentElem);
    }
  NotifyFocus ();
  }

void DDSList::End (BOOL doIV,BOOL SubSelFollows,BOOL CheckKeys)
  {
  ListElem FAR *old = CurrentElem ;
  int oldyOffsToShow = yOffsToShow ;
  char svBuffer[64];
  if (SelSubLines_Buffer != NULL)
    lmemcpy (svBuffer,SelSubLines_Buffer,sizeof(SelSubLines_Buffer));
  BOOL doIVCurrent,doIVFull;
  if (!EndReached) {
    DestroyList ();
    FillHead (hdHeight);
    doIVFull = TRUE ;
    }
  else
    doIVFull = FALSE ;
  BOOL ShiftPressed,ControlPressed;
  if (CheckKeys) {
    ShiftPressed = (GetKeyState (VK_SHIFT) < 0) ;
    ControlPressed = (GetKeyState (VK_CONTROL) < 0) ;
    }
  else {
    ShiftPressed = FALSE ;
    ControlPressed = FALSE ;
    }

  if (AdditionalMultiSel() && ShiftPressed) {
    SelectWholeRange (tail,DDSLIST_SELRANGE_END);
    CheckSelections (doIV);
    SetCurrentElem (tail,doIV,TRUE);
    }
  else {
    if (AdditionalMultiSel() && ControlPressed) {
      if (doIV)
        InvalidateElem (CurrentElem);
      CurrentElem = tail ;
      if (doIV)
        InvalidateElem (tail);
      }
    else
      SetCurrentElem (tail,doIV,FALSE);
    }

  SelSub (-1,TRUE,FALSE);
  if (SelSubLines == NULL) {
    if (!SubSelFollows) {
      CheckSelections_scroll (FALSE,doIV);
      CheckCurrentVisible (doIV);
      }
    }
  else {
    CheckSelections (doIV);
    RECT rcWnd,rcAct;
    GetScrollRect (hWndList,&rcWnd);
    yOffsToShow = 0 ;
    CalculateElemRect (CurrentElem,&rcAct);
    rcAct.bottom = rcAct.top + LineStop ;
    if (rcAct.bottom > rcWnd.bottom) {
      // Nur soviel scrollen, dass die Zeile gerade noch sichtbar wird
      yOffsToShow = rcWnd.bottom - rcAct.bottom ;
      }
    }
  doIVFull = doIVFull || (yOffsToShow != oldyOffsToShow) ;
  doIVCurrent = (CurrentElem != old);
  if (SelSubLines_Buffer != NULL)
    doIVCurrent = doIVCurrent || !lmemcmp (svBuffer,SelSubLines_Buffer,sizeof(SelSubLines_Buffer));
  if ((doIVFull) && (doIV))
    InvalidateFull ();
  else if ((doIVCurrent) && (doIV)) {
    InvalidateElem (old);
    InvalidateElem (CurrentElem);
    }
  NotifyFocus ();
  }

void DDSList::PageDown (BOOL ShiftPressed,BOOL ControlPressed)
  {
  if (CurrentElem != NULL) {
    if (EndReached) End () ;
    else {
      RECT rToSel,rcElem,rcWnd;
      CalculateElemRect (CurrentElem,&rToSel,yOffsToShow);
      GetScrollRect (hWndList,&rcWnd);
      BOOL doScroll = TRUE ;
      if (SelSubLines != NULL) {
        rToSel.bottom = rToSel.top + LineStop ;
        rToSel.top += LineStart ;
        yOffsToShow -= wheight - hdHeight - 2 * (rToSel.bottom - rToSel.top) ; // Bereich, um den Gescroll werden soll
        // Hinten anhaengen was platz hat
        for ( ; ((FullHeight() + yOffsToShow < wheight) && (InsertAtTail())) ; ) ;
        // Vorne rausnehmen, was ueberfluessig ist
        for ( ; ((- yOffsToShow > head->height) && (FullHeight() - head->height >= wheight)) ; ) {
          yOffsToShow += head->height ;
          (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
          RemoveHead ();
          }
        // Moeglicherweise konnten vorne weniger weggenommen werden, als
        // Hinten angezeigt werden kann
        if (FullHeight () + yOffsToShow < wheight) {
          yOffsToShow = min(0,wheight - FullHeight()) ;
          }
        // Suchen eines Passenden Elementes
        for ( ListElem FAR *h = head ; ; h = h->Next) {
          CalculateElemRect (h,&rcElem,yOffsToShow);
          if ((rToSel.top >= rcElem.top) && (rToSel.top < rcElem.bottom))
            break ;
          if (h->Next == NULL) break ;
          }
        char svBuffer[64];
        int ostart,ostop;
        int yMin = 10000 ;
        SetCurrentElem (h,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
        for ( SelSub (1,TRUE,FALSE) ; ; ) {
          int ay = rcElem.top + LineStart - rToSel.top ;
          if (ay < 0) ay = -ay ;
          if (ay < yMin) {
            lmemcpy (svBuffer,SelSubLines_Buffer,GetBlockSize(SelSubLines_Buffer)) ;
            ostart = LineStart ;
            ostop = LineStop ;
            yMin = ay ;
            }
          if (!SelSub(1,FALSE,FALSE)) break ;
          }
        if (yMin < 10000) {
          lmemcpy (SelSubLines_Buffer,svBuffer,GetBlockSize(SelSubLines_Buffer)) ;
          LineStart = ostart ;
          LineStop = ostop ;
          // Auf jeden fall sichtbar machen
          if (rcElem.top + LineStop > rcWnd.bottom)
            yOffsToShow += rcWnd.bottom - (rcElem.top + LineStop) ;
          if (rcElem.top + LineStart < rcWnd.top)
            yOffsToShow += rcWnd.top - (rcElem.top + LineStart) ;
          }
        InvalidateFull ();
        }
      else {
        if (InsertAtTail ()) {
          // Alle am Beginn der Liste loeschen
          ListElem FAR *newHead = tail ;
          if (tail->Prev != NULL) newHead = tail->Prev;
          int toScroll = 0 ;
          for ( ; ((head != newHead) && (!EndReached)) ; ) {
            toScroll -= head->height ;
            (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
            RemoveHead ();
            FillTail (FullHeight());  // Hinten wieder auffuellen
            }
          if (toScroll) {
            // Suchen eines neuen CurrentElem
            for (ListElem FAR *h = head ; h->Next != NULL ; h = h->Next) {
              RECT rToSel1;
              CalculateElemRect (h,&rToSel1);
              IntersectRect (&rToSel1,&rToSel1,&rToSel);
              if (!IsRectEmpty (&rToSel1))
                break ;
              }
            SetCurrentElem (h,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
            InvalidateFull ();
            }
          else {
            if (CurrentElem != tail) {
              for (  ; ((tail != head) && (!IsFullOnScreen (tail))) ; ) {
                toScroll -= head->height ;
                (* Notify) (head->Data,DDSLIST_RELEASEELE,bData);
                RemoveHead ();
                }
              if (toScroll)
                Scroll (toScroll);
              InvalidateElem (CurrentElem);
              SetCurrentElem (tail,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
              InvalidateElem (CurrentElem);
              }
            }
          }
        }
      }
    }
  }

void DDSList::PageUp (BOOL ShiftPressed,BOOL ControlPressed)
  {
  if (CurrentElem != NULL) {
    if (BegReached) Home () ;
    else {
      RECT rToSel,rcElem,rcWnd;
      CalculateElemRect (CurrentElem,&rToSel,yOffsToShow);
      GetScrollRect (hWndList,&rcWnd);
      BOOL doScroll = TRUE ;
      if (SelSubLines != NULL) {
        rToSel.bottom = rToSel.top + LineStop ;
        rToSel.top += LineStart ;
        yOffsToShow += wheight - hdHeight - 2 * (rToSel.bottom - rToSel.top) ; // Bereich, um den Gescroll werden soll
        // Vorne anhaengen was platz hat
        for ( ; (yOffsToShow > 0) ; ) {
          if (!InsertAtHead ()) {
            yOffsToShow = 0 ;
            break ;
            }
          else
            yOffsToShow -= head->height ;
          }
        // Hinten rausnehmen, was ueberfluessig ist
        for ( ; FullHeight () + yOffsToShow - tail->height > wheight ; ) {
          (* Notify) (tail->Data,DDSLIST_RELEASEELE,bData);
          RemoveTail () ;
          }
        // Suchen eines Passenden Elementes
        for ( ListElem FAR *h = head ; ; h = h->Next) {
          CalculateElemRect (h,&rcElem,yOffsToShow);
          if ((rToSel.top >= rcElem.top) && (rToSel.top < rcElem.bottom))
            break ;
          if (h->Next == NULL) break ;
          }
        char svBuffer[64];
        int ostart,ostop;
        int yMin = 10000 ;
        SetCurrentElem (h,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
        for ( SelSub (1,TRUE,FALSE) ; ; ) {
          int ay = rcElem.top + LineStart - rToSel.top ;
          if (ay < 0) ay = -ay ;
          if (ay < yMin) {
            lmemcpy (svBuffer,SelSubLines_Buffer,GetBlockSize(SelSubLines_Buffer)) ;
            ostart = LineStart ;
            ostop = LineStop ;
            yMin = ay ;
            }
          if (!SelSub(1,FALSE,FALSE)) break ;
          }
        if (yMin < 10000) {
          lmemcpy (SelSubLines_Buffer,svBuffer,GetBlockSize(SelSubLines_Buffer)) ;
          LineStart = ostart ;
          LineStop = ostop ;
          // Auf jeden fall sichtbar machen
          if (rcElem.top + LineStop > rcWnd.bottom)
            yOffsToShow += rcWnd.bottom - (rcElem.top + LineStop) ;
          if (rcElem.top + LineStart < rcWnd.top)
            yOffsToShow += rcWnd.top - (rcElem.top + LineStart) ;
          }
        InvalidateFull ();
        }
      else {
        // SelSub == NULL ;
        if (head->Next == NULL)   // Nur eins am Bildschirm, das muss dann spaeter verschwinden
          doScroll = InsertAtHead ();  // Vorne auf jeden fall eins anhaengen, damit weitergeschalten wird
        else
          doScroll = TRUE ;
        if (doScroll) {
          // Alle am Beginn der Liste loeschen
          ListElem FAR *newTail = head ;
          int toScroll = 0 ;
          for ( ; ((tail != newTail) && (!BegReached)) ; ) {
            toScroll += head->height ;
            (* Notify) (tail->Data,DDSLIST_RELEASEELE,bData);
            RemoveTail ();
            FillHead (FullHeight());  // Vorne wieder auffuellen
            }
          FillTail (FullHeight());  // Sollte es durch die Loeschaktionen vorne zu 
                                    // zuvielen Loeschungen gekommen sein, dann muss
                                    // hinten noch geloescht werden
          if (toScroll) {
            // Suchen eines neuen CurrentElem
            for (ListElem FAR *h = head ; h->Next != NULL ; h = h->Next) {
              RECT rToSel1;
              CalculateElemRect (h,&rToSel1);
              IntersectRect (&rToSel1,&rToSel1,&rToSel);
              if (!IsRectEmpty (&rToSel1))
                break ;
              }
            SetCurrentElem (h,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
            InvalidateFull ();
            }
          else {
            if (CurrentElem != head) {
              InvalidateElem (CurrentElem);
              SetCurrentElem (head,TRUE,AdditionalMultiSel() && (ShiftPressed || ControlPressed));
              InvalidateElem (CurrentElem);
              }
            }
          }
        }
      }
    }
  }

void DDSList::OnRButtonDown (HMENU hPopupMenu)
  {
  }

extern DLLExport DWORD _export WINAPI GetHelpContextNr (void);
extern DLLExport LPSTR _export WINAPI GetHelpFile (void);
//extern DLLExport void  _export WINAPI SetHelpContextNr (DWORD dwHelpContextNr);
extern LPSTR WINAPI GetHtmlFile (void);
extern HWND  WINAPI htmlhelp (HWND hWnd, LPCSTR lpstr, 
                                        UINT uint , DWORD dword);


DLLExport long CALLBACK _export ListWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
  DDSList FAR *list = (DDSList FAR *) GetWindowLong (hWnd,GWL_LISTPTR);
  RECT scr;
  RECT rc;

  if ((list != NULL) && (list->buttons != NULL)) {
    BOOL done;
    LONG RetVal = list->buttons->CheckMsg (hWnd,message,wParam,lParam,&done);
    if (done)
      return RetVal;
    }
  switch (message) {
    case WM_GETDLGCODE :
      switch (wParam) {
        case VK_RETURN :
        case VK_TAB :
        case VK_CONTROL :
        case VK_SHIFT :
        case VK_ESCAPE :
          return DefWindowProc (hWnd,message,wParam,lParam);
        default :
          return DLGC_WANTALLKEYS ;
        }
#ifdef UEBERLEGT
      switch (wParam) {
        case VK_UP:
        case VK_DOWN:
        case VK_HOME:
        case VK_END:
        case VK_PRIOR:
        case VK_NEXT:
        case VK_SPACE:
          return DLGC_WANTALLKEYS ;
        default :
          return (DefWindowProc(hWnd, message, wParam, lParam));
        }
#endif
      break ;
    case WM_SIZE:
      if (list != NULL)
        list->InitializeSize ();
      break ;
    case WM_PAINT:
      {
      PAINTSTRUCT PS;
      HDC hDC = BeginPaint(hWnd, &PS);
      list->Paint (hDC);
      if (list->head != NULL) {
        int rx = list->GetScroll (list->head->Data);
        if (list->yscrollrange >= 0) {
          int rm = list->yscrollrange - list->AnzElems() + 1;
          if (rm > 0) {
            EnableScrollBar (hWnd,SB_VERT,ESB_ENABLE_BOTH);
            SetScrollRange (hWnd, SB_VERT, 0, rm, TRUE);
            SetScrollPos   (hWnd, SB_VERT, rx, TRUE);
            }
          else {
            EnableScrollBar (hWnd,SB_VERT,ESB_DISABLE_BOTH);
            }
          }
        }
      else {
        if (list->yscrollrange >= 0)
          EnableScrollBar (hWnd,SB_VERT,ESB_DISABLE_BOTH);
        else
          SetScrollPos (hWnd, SB_VERT, 0, TRUE);
        }

      if (list->buttons != NULL) {
        list->GetScrollRect (hWnd, &scr);
        list->buttons->PaintListButtons (hDC, &scr);
        }
      EndPaint (hWnd, &PS);
      break;
      }
    case WM_LBUTTONDOWN:
      {
      ListElem FAR* h = list->head;
      ListElem FAR* SaveElem = NULL;
      HDC           hDC;
      POINT         pt;

#ifdef WIN32
      LONG2POINT(lParam, pt);
#else
      pt = MAKEPOINT(lParam);
#endif      

      SetCapture (hWnd);
      Captured = TRUE;

      BOOL dontResetOld = ((list->AdditionalMultiSel()) && (wParam & (MK_SHIFT | MK_CONTROL)));
      BOOL SetNew = ((list->AdditionalMultiSel()) && ((wParam & (MK_CONTROL)) == 0));
      SaveElem = list->CurrentElem;         
      h = list->Find (&pt,dontResetOld,SetNew);

      if (h != NULL) {
        // selektierte Elemente werden deselektiert und umgekehrt
        BOOL ShiftPressed = (wParam & MK_SHIFT);
        BOOL ControlPressed = (wParam & MK_CONTROL);
        if (list->AdditionalMultiSel ()) {
          if (ShiftPressed)
            list->SelectWholeRange (h,DDSLIST_SELRANGE_ACTIVE);
          else {
            if (ControlPressed) {
              if ((* list->IsSelected) (h->Data))
                (* list->Notify) (h->Data,DDSLIST_REMOVESEL,list->bData);
              else
                list->SetCurrentElem (h,TRUE,TRUE);
              }
            else {
              list->SetCurrentElem (h,TRUE,FALSE);
              (* list->Notify) (h->Data,DDSLIST_SELELE,list->bData);
              }
            }
          }
        else {
          list->SetCurrentElem (h,TRUE,FALSE);
          (* list->Notify) (h->Data,DDSLIST_SELELE,list->bData);
          }

        hDC = GetDC (hWnd);
        for (h = list->head ; h != NULL ; h = h->Next) {
          BOOL nwSel = (* list->IsSelected) (h->Data);  // ist dieses Element selektiert?
          if (nwSel != h->isSel) {                      // war es vorher anders?
            list->InvalidateElem (h);
            h->isSel = nwSel;                           // Status ‰ndern
            }   
          }

        list->InvalidateElem (SaveElem);
        list->InvalidateElem (list->CurrentElem);

        ReleaseDC (hWnd, hDC);
        if (list->SelSubLines == NULL) {
          list->CheckTail ();
          // list->CheckCurrentVisible (TRUE);
          }
        list->NotifyFocus ();

        char buffer[128];
        int DataSize = GetBlockSize (list->CurrentElem) - sizeof(*(list->CurrentElem)) + 1;
        WIN_ASSERT (DataSize < sizeof(buffer) - sizeof(POINT));
        lmemcpy (buffer,list->CurrentElem->Data,DataSize);
        POINT ptrel;
        RECT rcAct;
        list->CalculateElemRect (list->CurrentElem,&rcAct,list->yOffsToShow);
        ptrel.x = pt.x;
        ptrel.y = pt.y - rcAct.top;
        lmemcpy (buffer + DataSize,&ptrel,sizeof(ptrel));
        (* list->Notify) (buffer,DDSLIST_CLICKDONE,list->bData);
        }
      // nichts in der Liste angeklickt vielleicht im Header?
      else {
        (* list->Notify)(LPPOINT(&pt), DDSLIST_HEADERCLK, list->bData);
        }
      }
      if (GetFocus() != hWnd) {
        SetFocus (hWnd);
        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, DDSLIST_LBUTTON, hWnd);
        WPARAM wId;
#ifdef WIN32
        wId = GetWindowLong (hWnd, GWL_ID);
#else
        wId = GetWindowWord (hWnd, GWW_ID);
#endif

        SendMessage (GetParent(hWnd),
                          WM_COMMAND,
                          wId,
                          HILOCHUNKPARAM (hilo)
                    );
        }
      break;

    case WM_RBUTTONDOWN :
    case WM_RBUTTONUP :
      {
/*
32:
WM_COMMAND 
wNotifyCode = HIWORD(wParam); // notification code 
wID = LOWORD(wParam);         // item, control, or accelerator identifier 
hwndCtl = (HWND) lParam;      // handle of control 

16:
wID = wParam
hwndCtl = (HWND)LOWORD(lParam)
wNotifyCode = HIWORD(lParam)
*/
      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, (message == WM_RBUTTONDOWN) ? 
                                           WW_RBUTTONDOWN : WW_RBUTTONUP, hWnd)

#ifdef WIN32
      WPARAM wId = GetWindowLong (hWnd, GWL_ID);
#else
      WPARAM wId = GetWindowWord (hWnd, GWW_ID);
#endif

      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
/*
#ifdef WIN32
      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   MAKELONG (wID, (message == WM_RBUTTONDOWN) ? 
                                             WW_RBUTTONDOWN : WW_RBUTTONUP)
                   GetWindowLong (hWnd, GWL_ID));
                   MAKELONG(hWnd,(message == WM_RBUTTONDOWN) ? 
                                              WW_RBUTTONDOWN : WW_RBUTTONUP)
                  );
#else
      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   GetWindowWord (hWnd,GWW_ID),
                   MAKELONG(hWnd,(message == WM_RBUTTONDOWN) ? 
                RBUTTONDOWN : WW_RBUTTONUP)
                  );
#endif
*/
      }
      break ;

    case WM_MOUSEMOVE:
      if (Captured) {
        ListElem FAR* h = list->head;
        ListElem FAR* SaveElem = NULL;
        HDC           hDC;
        
        GetClientRect (hWnd, &rc);
        hDC = GetDC (hWnd);

#ifdef WIN32
        LONG2POINT(lParam, ptCap);
#else
        ptCap = MAKEPOINT(lParam);
#endif

        if ((ptCap.y >= rc.top) && (ptCap.y <= rc.bottom)) {
          if (TimerSet) {
            KillTimer (hWnd, 1);
            TimerSet = FALSE;
            }

          if (h == NULL) {
            ReleaseDC (hWnd, hDC);
            break;
            }
      
          BOOL dontResetOld = ((list->AdditionalMultiSel()) && (wParam & (MK_SHIFT | MK_CONTROL)));
          BOOL SetNew = ((list->AdditionalMultiSel()) && ((wParam & (MK_CONTROL)) == 0));
          SaveElem = list->CurrentElem;
          h = list->Find(&ptCap,dontResetOld,SetNew);
      
          if (h != SaveElem) {
            BOOL ShiftPressed = (wParam & MK_SHIFT);
            BOOL ControlPressed = (wParam & MK_CONTROL);

            if (h != NULL) {
              if (list->AdditionalMultiSel ()) {
                if (ShiftPressed)
                  list->SelectWholeRange (h,DDSLIST_SELRANGE_ACTIVE);
                else if (ControlPressed) {
                  if ((* list->IsSelected) (h->Data))
                    (* list->Notify) (h->Data,DDSLIST_REMOVESEL,list->bData);
                  else
                    list->SetCurrentElem (h,TRUE,TRUE);
                  }
                else
                  list->SetCurrentElem (h,FALSE,FALSE);
                for (h = list->head ; h != NULL ; h = h->Next) {
                  BOOL nwSel = (* list->IsSelected) (h->Data);
                  if (nwSel != h->isSel) {
                    list->InvalidateElem (h);
                    h->isSel = nwSel ;
                    }
                  }
                }
              else
                list->SetCurrentElem (h,TRUE,FALSE);

              // selektierte Elemente werden deselektiert und umgekehrt
              if (SaveElem != list->CurrentElem) {
                list->InvalidateElem (SaveElem);
                list->InvalidateElem (list->CurrentElem);
                }
              list->NotifyFocus ();
              }
            }
          }   // ...if (PtInRect) ...
        else {
          if (!TimerSet) {
            SetTimer (hWnd, 1, 0, NULL);
            TimerSet = TRUE;
            }
          }  
        ReleaseDC (hWnd, hDC);
        }
      break;
    case WM_LBUTTONUP:
      if (TimerSet) {
        KillTimer (hWnd, 1);
        TimerSet = FALSE;
        }
        
      lastElemDown = list->CurrentElem;
      // list->CheckCurrentVisible (TRUE);
      ReleaseCapture ();
      Captured = FALSE;
      if (list->CurrentElem != NULL)
        (* list->Notify) (list->CurrentElem->Data, DDSLIST_LBUTTONUP,list->bData);      // gefundenes Element selektieren
      break;
    case WM_LBUTTONDBLCLK:
      {
      POINT pt;

      if (list->CurrentElem == lastElemDown) {
#ifdef WIN32
        LONG2POINT (lParam, pt);
#else
        pt = MAKEPOINT(lParam);
#endif
        // Es muss auf den WM_LBUTTONUP gewartet werden
        //--------------------------------------------------
        MSG msg;
        for ( ; !PeekMessage (&msg,hWnd,WM_LBUTTONUP,WM_LBUTTONUP,PM_REMOVE); ) ;
      
        list->SetCurrentElem (list->Find (&pt,((list->AdditionalMultiSel()) && (wParam & (MK_SHIFT | MK_CONTROL))),((list->AdditionalMultiSel()) && ((wParam & (MK_CONTROL)) == 0))),TRUE,((list->AdditionalMultiSel()) && (wParam & (MK_SHIFT | MK_CONTROL))));
        if (list->CurrentElem != NULL)
          (* list->Notify) (list->CurrentElem->Data, DDSLIST_DBLCLKELE,list->bData);      // gefundenes Element selektieren
        list->CheckSelections(TRUE);
        list->NotifyFocus ();

        HILOCHUNK hilo;
        MAKECHUNKsc (hilo, LBN_DBLCLK, hWnd)

#ifdef WIN32
        WPARAM wId = GetWindowLong (hWnd, GWL_ID);
#else
        WPARAM wId = GetWindowWord (hWnd, GWW_ID);
#endif

        SendMessage (GetParent(hWnd),
                    WM_COMMAND,
                    wId,
                    HILOCHUNKPARAM (hilo)
                    );
        }
      else
        MessageBeep (0);
      }
      break;

    case WM_COMMAND:
      {
      WPARAM wP = wParam;
      LPARAM lP = lParam;

      CRACKER_VARS
      CRACK_MESSAGEsc

      if (CRACKER_wID == MI_H_Help_DDS) {
#ifdef WINHELP
        BOOL bResult;
        DWORD ContextNr = GetHelpContextNr();
#ifdef WIN32
        if (ContextNr < 0)
          bResult = WinHelp (hWnd, GetHelpFile(), HELP_FINDER, 0);
        else
#endif

        bResult = WinHelp (hWnd, GetHelpFile(), HELP_CONTEXT, ContextNr);
#else
        HWND wnd = htmlhelp(hWnd, GetHtmlFile(), HH_DISPLAY_TOPIC, NULL);
#endif
        }
      }

    case WM_TIMER:
      {
      GetClientRect (hWnd, &rc);
      
      if (ptCap.y <= rc.top)
        list->LineUp (GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
      else if (ptCap.y >= rc.bottom)
        list->LineDown (GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
      }
      break;
    case WM_KEYDOWN:
      {
      switch(wParam) {
        case VK_RETURN:
          if (list->CurrentElem != NULL)
            (* list->Notify) (list->CurrentElem->Data, DDSLIST_DBLCLKELE,list->bData);      // gefundenes Element selektieren

          break;
          
        case VK_UP:
          list->LineUp (GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
          break;
        case VK_DOWN:
          list->LineDown (GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
          break;
        case VK_HOME:
          list->Home();
          break;
        case VK_END:
          list->End();
          break;
        case VK_PRIOR:
          list->PageUp(GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
          break;
        case VK_NEXT:
          list->PageDown(GetKeyState (VK_SHIFT) < 0,GetKeyState (VK_CONTROL) < 0);
          break;
          
        case VK_SPACE:
          if (list->CurrentElem != NULL) {
            if ((list->AdditionalMultiSel()) && (GetKeyState (VK_CONTROL) < 0)) {
              if ((* list->IsSelected) (list->CurrentElem->Data))
                (* list->Notify) (list->CurrentElem->Data,DDSLIST_REMOVESEL,list->bData);      // gefundenes Element selektieren
              else
                (* list->Notify) (list->CurrentElem->Data, DDSLIST_FORCESEL, list->bData);
              }
            else
              (* list->Notify) (list->CurrentElem->Data,DDSLIST_SELELE,list->bData);      // gefundenes Element selektieren
            for (ListElem FAR *h = list->head ; h != NULL ; h = h->Next) {
              BOOL nwSel = (* list->IsSelected) (h->Data);  // ist dieses Element selektiert?
              if (nwSel != h->isSel) {                      // war es vorher anders?
                list->InvalidateElem (h);
                h->isSel = nwSel;                           // Status ‰ndern
                }
              }
            list->NotifyFocus ();
            }   
          break;
        case VK_TAB :
          {
          HILOCHUNK hilo;
          MAKECHUNKsc (hilo, DDSLIST_TABPRESSED, 0)

          SendMessage (GetParent (hWnd),WM_COMMAND,0,HILOCHUNKPARAM(hilo));
/*
          SendMessage (GetParent (hWnd),WM_COMMAND,0,MAKELONG(0,DDSLIST_TABPRESSED));
*/  
          }
          break ;
        }
      break;
      }
    case WM_CHAR :
      charNotify cn;
      cn.ch    = char (wParam);
      cn.par   = list->ccPar;
      cn.proc  = list->ccProc;
      cn.bData = list->bData;
      (* list->Notify) (&cn, DDSLIST_CHARPRESSED,list->bData);
      break ;
    case WM_SETFOCUS :
      if (list->CurrentElem == NULL) {
        for ( ListElem FAR *h = list->head ; h != NULL ; h = h->Next) {
          if (h->isSel) {
            list->CurrentElem = h;
            break ;
            }
          }
        if (list->CurrentElem == NULL) 
          list->CurrentElem = list->head;
        }
      list->InvalidateElem (list->CurrentElem) ;
      break ;

    case WM_KILLFOCUS :
      {
      list->InvalidateElem (list->CurrentElem);
        
      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, WW_ONKILLFOCUS, wParam)

#ifdef WIN32
      WPARAM wId = GetWindowLong (hWnd, GWL_ID);
#else
      WPARAM wId = GetWindowWord (hWnd, GWW_ID);
#endif

      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   wId,
                   HILOCHUNKPARAM (hilo)
                  );
      }
      break ;
    case WM_DESTROY:
      list->hWndList = 0;
      if (_lst != list)
        PostMessage (list->DoNotify, WMU_DESTROYDDSLIST, 0, LONG(LPSTR(list)));
      else
        _lst = NULL ;
      break;
      
    default:
      return (DefWindowProc(hWnd, message, wParam, lParam));
    }
  return NULL;
  }

/*-------------------------------------------------------------------------*\
*  member function:  Register                                               *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::Register ()
  {
  if (!Registered) {
    WNDCLASS  wc;

    wc.style = CS_GLOBALCLASS | CS_DBLCLKS ;
    wc.lpfnWndProc = ListWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof (DDSList FAR *);
    wc.hInstance = hLibInst;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = szListClassName;

    if (!RegisterClass(&wc))
      Registered = FALSE;
    else  
      Registered = TRUE ;
    }
  }

static int ddslistid = 0x8000;
void DDSList::Create (HWND hWndParent,DWORD Style,int x,int y,int w,int h)
  {
  Register ();

  if (hWndList == 0) {
    hWndList = CreateWindow (szListClassName, NULL, 
                             Style,
                             x,y,w,h,
                             hWndParent,
                             HMENU(ddslistid++),
                             hLibInst,
                             (LPVOID)NULL);
    SetWindowLong (hWndList,GWL_LISTPTR,LONG (LPSTR (this)));
    RECT r;
    GetClientRect (hWndList,&r);
    wheight = r.bottom;
    if (yscrollrange >= 0) {
      int rm = yscrollrange - AnzElems() + 1;
      if ((rm > 0) && (yscrollrange > 0)) {
        EnableScrollBar (hWndList,SB_VERT,ESB_ENABLE_BOTH);
        SetScrollRange (hWndList, SB_VERT, 0, rm , TRUE);
        }
      else {
        EnableScrollBar (hWndList,SB_VERT,ESB_DISABLE_BOTH);
        }
      }
    else
      SetScrollRange (hWndList, SB_VERT, 0, 0, TRUE);
    }
  }

void DDSList::Show (BOOL SubSelFollows)
  {
  if (IsWindow(hWndList)) {
    ShowWindow (hWndList,SW_NORMAL);
    if ((head == NULL) && (!EndReached) && (!BegReached)) {
      int h = FullHeight();
      if (StartElem != NULL) {
        Fill (h,StartElem,0);
        StartElem = NULL;
        CheckSelections (FALSE);
        }
      else {
        if (fillbackward) {
          End (FALSE,SubSelFollows,FALSE);
          }
        else {
          Home (FALSE,FALSE);
          }
        }
      }
    }
  }                          

void DDSList::Adjust ()
  {
  if (fillbackward) {
    if (SelSubLines == NULL) {
      CheckSelections_scroll (FALSE,FALSE);
      CheckCurrentVisible (FALSE);
      }
    else {
      SelSub (-1,TRUE,FALSE);
      CheckSelections (FALSE);
      RECT rcWnd,rcAct;
      GetScrollRect (hWndList,&rcWnd);
      yOffsToShow = 0 ;
      CalculateElemRect (CurrentElem,&rcAct);
      rcAct.bottom = rcAct.top + LineStop ;
      if (rcAct.bottom > rcWnd.bottom) {
        // Nur soviel scrollen, dass die Zeile gerade noch sichtbar wird
        yOffsToShow = rcWnd.bottom - rcAct.bottom ;
        }
      }
    }
  }

inline void PaintBitmap (HDC hDC, HBITMAP bitmap, int x, int y)
  {
  if (bitmap != NULL) {
    HDC hMemDC;
    hMemDC = CreateCompatibleDC (hDC);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject (hMemDC, bitmap);
    BITMAP bm;
    GetObject (bitmap, sizeof(BITMAP), &bm);
    BitBlt (hDC, x, y, bm.bmWidth, bm.bmHeight,
            hMemDC, 0, 0, SRCCOPY);
    SelectObject (hMemDC, hOldBitmap);
    DeleteDC (hMemDC);
    }
  }
/*-------------------------------------------------------------------------*\
*  member function:  Paint                                                  *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
#define FWIDTH 4
void DDSList::Paint (HDC hDC)
  {
  if ((head == NULL) && (!EndReached) && (!BegReached) && (!InPrinting)) {
    int h = FullHeight();
    if (StartElem != NULL) {
      Fill (h,StartElem,0);
      StartElem = NULL;
      CheckSelections (FALSE);
      }
    else {
      if (fillbackward) {
        End (FALSE,FALSE,FALSE);
        }
      else {
        Home (FALSE,FALSE);
        }
      }
    }
  COLORREF OldBack, OldText;
  RECT rcInvert,rcWnd,rcClip;

  int StartX = 0;
  BOOL bMultiSel = isMultiSel();
  if (bMultiSel)
    StartX = 20;

  if (DrawHeader != NULL) {
    GetClientRect (hWndList, &rcInvert);
    rcInvert.bottom = rcInvert.top+hdHeight;
    if (RectVisible(hDC, &rcInvert)) {
      OldBack = SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));
      ExtTextOut (hDC, rcInvert.left, rcInvert.top, ETO_OPAQUE, 
                  LPRECT(&rcInvert), NULL, 0, NULL);
      (* DrawHeader) (hDC,bData,NULL,StartX,0,FALSE,NULL,0,0);
      SetBkColor (hDC, OldBack);
      }
    }

  int y = hdHeight + yOffsToShow ;
  
  BOOL PaintSelection = FALSE;
  GetScrollRect (hWndList,&rcWnd);
  for (ListElem FAR *h = head ; h != NULL ; h = h->Next) {

    CalculateElemRect (h, &rcInvert, yOffsToShow);
    IntersectRect (&rcClip,&rcInvert,&rcWnd);

    HRGN hRgn = CreateRectRgn (rcClip.left,rcClip.top,rcClip.right,rcClip.bottom);
    SelectClipRgn (hDC,hRgn);

    if (RectVisible(hDC, &rcInvert)) {
      PaintSelection = bMultiSel ? (h == CurrentElem) : h->isSel;

      if (PaintSelection) {
        DWORD txcolor = GetSysColor(COLOR_HIGHLIGHTTEXT);
        DWORD hcolor = 0L;
        BOOL  justFrame = FALSE ;
        DWORD bccolor = ((SelSubLines == NULL) ? 0L : 1L);
        (*Notify) (&hcolor,DDSLIST_GETCOLOR,bData);
        (*Notify) (&bccolor,DDSLIST_GETCOLOR,bData);
        (*Notify) (&justFrame,DDSLIST_GETFRAMETYPE,bData);
        OldBack = SetBkColor (hDC, bccolor);
  
        // Selektierungsrechteck zeichnen bzw. loeschen (siehe SetBkColor)
        if ((SelSubLines == NULL) && (justFrame)) {
          RECT rchlp;
          CopyRect (&rchlp,&rcInvert);
          rchlp.right = rchlp.left + FWIDTH ;
          ExtTextOut (hDC, rchlp.left, rchlp.top, ETO_OPAQUE, LPRECT(&rchlp), NULL, 0, NULL);

          CopyRect (&rchlp,&rcInvert);
          rchlp.left = rchlp.right - FWIDTH ;
          ExtTextOut (hDC, rchlp.left, rchlp.top, ETO_OPAQUE, LPRECT(&rchlp), NULL, 0, NULL);

          CopyRect (&rchlp,&rcInvert);
          rchlp.bottom = rchlp.top + FWIDTH ;
          ExtTextOut (hDC, rchlp.left, rchlp.top, ETO_OPAQUE, LPRECT(&rchlp), NULL, 0, NULL);

          CopyRect (&rchlp,&rcInvert);
          rchlp.top = rchlp.bottom - FWIDTH ;
          ExtTextOut (hDC, rchlp.left, rchlp.top, ETO_OPAQUE, LPRECT(&rchlp), NULL, 0, NULL);

          // ExtTextOut (hDC, rcInvert.left, rcInvert.top, ETO_OPAQUE, LPRECT(&rcInvert), NULL, 0, NULL);
          }
        else {
          OldText = SetTextColor (hDC, txcolor);
          (*Notify) (&txcolor,DDSLIST_SETPAINTCOLOR,NULL);

          ExtTextOut (hDC, rcInvert.left, rcInvert.top, ETO_OPAQUE, LPRECT(&rcInvert), NULL, 0, NULL);

          if ((h == CurrentElem) && (SelSubLines != NULL)) {
            RECT rcLine ;
            CopyRect (&rcLine,&rcInvert);
            rcLine.bottom = rcLine.top + LineStop ;
            rcLine.top += LineStart ;
            COLORREF ActBack = SetBkColor (hDC, hcolor);
            ExtTextOut (hDC, rcLine.left, rcLine.top, ETO_OPAQUE, LPRECT(&rcLine), NULL, 0, NULL);
            SetBkColor (hDC,ActBack);
            }
          }
        }
      else {
        // Hintergrund loeschen
        ExtTextOut (hDC, rcInvert.left, rcInvert.top, ETO_OPAQUE, LPRECT(&rcInvert), NULL, 0, NULL);

        if ((h == CurrentElem) && (SelSubLines != NULL)) {
          RECT rcLine ;
          CopyRect (&rcLine,&rcInvert);
          rcLine.bottom = rcLine.top + LineStop ;
          rcLine.top += LineStart ;
          COLORREF ActBack = SetBkColor (hDC, RGB (0x80,0x80,0x80));
          ExtTextOut (hDC, rcLine.left, rcLine.top, ETO_OPAQUE, LPRECT(&rcLine), NULL, 0, NULL);
          SetBkColor (hDC,ActBack);
          }
        }
      (* DrawItem) (hDC, h->Data, (h->Prev != NULL) ? h->Prev->Data : NULL, StartX, y, FALSE,NULL,0,0);

      if (bMultiSel) {
        if (h->isSel)
          PaintBitmap (hDC, MultiOn, rcInvert.left+2, rcInvert.top+2);
        else
          PaintBitmap (hDC, MultiOff, rcInvert.left+2, rcInvert.top+2);
        }

      if (PaintSelection) {
        SetBkColor (hDC, OldBack);
        SetTextColor (hDC, OldText);
        (*Notify) (NULL,DDSLIST_RESETPAINTCOLOR,NULL);
        }

      if ((h == CurrentElem) && (GetFocus () == hWndList))
        FocusElement (hDC, h);
      }

    y += h->height;
    DeleteObject (hRgn);
    SelectClipRgn (hDC,NULL);
    }

  if (DrawBottom != NULL) {
    (* DrawBottom) (hDC,bData,NULL,StartX,y,FALSE,NULL,0,0);
    }
  }


/*-------------------------------------------------------------------------*\
*  member function:  InvertElement                                          *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::InvertElement (HDC hDC, ListElem FAR *h,BOOL doSelect)
  {
  RECT rcInvert;

  CalculateElemRect (h, &rcInvert);
  InvertRect (hDC, &rcInvert);
  }


/*-------------------------------------------------------------------------*\
*  member function:  FocusElement                                           *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::FocusElement (HDC hDC, ListElem FAR *h)
  {
  RECT rcInvert;

  CalculateElemRect (h, &rcInvert,yOffsToShow);

  LOGBRUSH LogBrush;

  LogBrush.lbStyle = BS_PATTERN;

#ifdef WIN32
  LogBrush.lbHatch = LONG(LoadBitmap(hLibInst, "FOCUSBITS"));
#else
  LogBrush.lbHatch = LoadBitmap(hLibInst, "FOCUSBITS");
#endif

  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, CreateBrushIndirect(&LogBrush));
      
  PatBlt (hDC, rcInvert.left, rcInvert.top, 1, rcInvert.bottom-rcInvert.top-1, 0xA000C9);    // Quelle & Ziel
  PatBlt (hDC, rcInvert.left, rcInvert.top, rcInvert.right-rcInvert.left-1, 1, 0xA000C9);
  PatBlt (hDC, rcInvert.right-1, rcInvert.top, 1, rcInvert.bottom-rcInvert.top-1, 0xA000C9);
  PatBlt (hDC, rcInvert.left, rcInvert.bottom-1, rcInvert.right-rcInvert.left, 1, 0xA000C9);

  DeleteObject(SelectObject(hDC, OldBrush));
  DeleteObject(HBITMAP(LogBrush.lbHatch));
  }


/*-------------------------------------------------------------------------*\
*  member function:  CalculateElemRect                                      *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
void DDSList::CalculateElemRect (ListElem FAR* h, LPRECT ElemRect,int yOffs)
  {
  if (h != NULL) {
    RECT rc;
    int i = hdHeight;

    for (ListElem FAR* ele = head; ele != NULL; ele = ele->Next) {
      if (ele == h)             // gesuchtes Element gefunden?
        break;                  // dann raus
      i += ele->height;
      }

    if (ele != NULL) {          // war Element in der sichtbaren Liste?
      GetClientRect (hWndList, &rc);
    
      // werden in der Listbox auch Knˆpfe gezeichnet?
      if (buttons != NULL)
        if (buttons->GetButtonPos() == BTN_RIGHT_POS)  // an der rechten Seite?
          rc.right = rc.right - buttons->GetWidth() + 1;            // dann dieses Element verkleinern!
    
      SetRect (ElemRect, rc.left, rc.top+i + yOffs, rc.right, rc.top+i+ele->height + yOffs);
      }
    else
      SetRectEmpty (ElemRect);  
    }
  }



/*-------------------------------------------------------------------------*\
*  member function PrintList                                                *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport void _export WINAPI DDSList::PrintList (Printer *pr,LPVOID prParam)
  {
  InPrinting = TRUE ;
  RECT   rc;
  RECT   rcPrintArea;
  int    hheight,bheight,height;
  LPVOID Data;
  
  pr->StartFrame();
  pr->GetPrinterArea (&rc);
  CopyRect (&rcPrintArea, &rc);

  int PageNr = 0;
  int y1,y2;
  int yPrExtraOffs = 0;
  char ssubbuffer_old[64],ssubbuffer[64];
  
  (* DrawHeadLine) (bData, pr->PrDC, rc.left, rc.top, rc.right-rc.left, &hheight, PageNr, prParam);
  (* DrawBottomLine) (bData, pr->PrDC, rc.left, rc.bottom, rc.right-rc.left, &bheight, PageNr ,prParam);
  
  pr->GetPrinterArea (&rc);
  CopyRect (&rcPrintArea, &rc);
  // RECT rcPrintArea0 = rcPrintArea;
  rcPrintArea.top += hheight;
  rcPrintArea.bottom -= bheight;

  long x = rcPrintArea.left;
  long y = rcPrintArea.top;

  (* StartPage) (bData, pr->PrDC, rc.left, rcPrintArea.top, rc.right-rc.left, &hheight, PageNr, prParam);
  y += hheight ;

  BOOL NextSame = FALSE;
  BOOL NextPage = FALSE;
  ForceNextPage = FALSE ;
  BOOL CheckNextSame = FALSE ;

  Data = (* GetFirst) (bData, pr->PrDC, &height,prParam,NULL);
  LPVOID prevData = NULL ;
  while (Data != NULL) {
    if (SelSubLines != NULL) {
      if (NextSame) {
        // Es muss ein Seitenumbruch durchgefuehrt werden und der 
        // aktuelle Eintrag muss um y1 nach oben gescrollt werden.
        yPrExtraOffs = - y1 ;
        NextPage = TRUE ;
        CheckNextSame = TRUE ;    // Nach dem Seitenumbruch muss untersucht
                                  // werden, ob noch weiter mit Subselektionen
                                  // gearbeitet werden muss
        }
      else {
        yPrExtraOffs = 0 ;
        if (y + height >= rcPrintArea.bottom) {
          // Der Eintrag hat nicht mehr ganz platz -> 
          // So lange nach unten scrollen, bis das Ende erreicht ist
          //--------------------------------------------------------
          for ( BOOL first = TRUE ; ; ) {
            if (!first)
              lmemcpy (ssubbuffer_old,ssubbuffer,sizeof(ssubbuffer_old));
            else
              lmemset (ssubbuffer,'\0',sizeof(ssubbuffer));
            BOOL done = (* SelSubLines) (1,&y1,&y2,pr->PrDC,first,Data,ssubbuffer,TRUE);
            if (!done) {
              // Es muesste eigentlich doch der ganze Eintrag platz haben
              // -> Normal weitermachen
              break ;
              }
            if (y + y2 > rcPrintArea.bottom) {
              // Bis y1 kann gedruckt werden
              if (first) {
                // Auf dieser Seite hat nicht einmal mehr eine Zeile platz
                // -> Seite Weiterschalten und normal weitermachen
                //--------------------------------------------------------
                NextPage = TRUE ;
                }
              else {
                // Der Eintrag darf bis y1 gedruckt werden -> Clipping auf
                // y1 einschalten und ausdrucken, aber nicht naechsten
                // Datensatz nehmen
                //--------------------------------------------------------
                NextSame = TRUE ;
                lmemcpy (ssubbuffer,ssubbuffer_old,sizeof(ssubbuffer));
                }
              break ;
              }
            first = FALSE ;
            }
          }
        }
      }

    if (((y + height >= rcPrintArea.bottom) && (SelSubLines == NULL)) || (NextPage) || (ForceNextPage)) {
      (* EndPage) (bData, pr->PrDC, rc.left, int(y), rc.right-rc.left, &hheight, PageNr, prParam, FALSE);
      pr->NewFrame();
      pr->StartFrame();
      PageNr++;
      (* DrawHeadLine) (bData, pr->PrDC, rc.left, rc.top, rc.right-rc.left, &hheight, PageNr, prParam);
      (* DrawBottomLine) (bData, pr->PrDC, rc.left, rc.bottom, rc.right-rc.left, &bheight, PageNr, prParam);

      pr->GetPrinterArea (&rc);
      rcPrintArea = rc;
      rcPrintArea.top += hheight;
      rcPrintArea.bottom -= bheight;
      y = rcPrintArea.top;

      (* StartPage) (bData, pr->PrDC, rc.left, rcPrintArea.top, rc.right-rc.left, &hheight, PageNr, prParam);
      y += hheight + yPrExtraOffs ;
      if (prevData != NULL) {
        (* Notify) (prevData,DDSLIST_RELEASEELE,bData);
        FreeGlobMem (prevData);
        }
      prevData = NULL ;
      NextPage = FALSE ;
      }

    if (CheckNextSame) {
      if (y + height >= rcPrintArea.bottom) {
        // Auch der noch verbleibende Teil hat nicht mehr ganz auf der
        // Seite platz ->
        // So lange nach unten scrollen, bis das Ende erreicht ist
        //--------------------------------------------------------
        for ( ; ; ) {
          lmemcpy (ssubbuffer_old,ssubbuffer,sizeof(ssubbuffer_old));
          BOOL done = (* SelSubLines) (1,&y1,&y2,pr->PrDC,FALSE,Data,ssubbuffer,TRUE);
          if (!done) {
            // Es muesste doch der ganze Eintrag platz haben
            CheckNextSame = FALSE ;   // Wieder in den Normalmodus
            NextSame = FALSE ;
            break ;
            }
          if (y + y2 > rcPrintArea.bottom) {
            // Der Eintrag darf bis y1 gedruckt werden -> Clipping auf
            // y1 einschalten und ausdrucken, aber nicht naechsten
            // Datensatz nehmen
            //--------------------------------------------------------
            NextSame = TRUE ;
            NextPage = TRUE ;
            lmemcpy (ssubbuffer,ssubbuffer_old,sizeof(ssubbuffer));
            break ;
            }
          }
        }
      else {
        CheckNextSame = FALSE ;   // Wieder in den Normalmodus
        NextSame = FALSE ;
        }
      }

    int yend ;
    if (NextSame)
      yend = int (y + y1) ;
    else
      yend = rcPrintArea.bottom;
    ForceNextPage = FALSE ;
    (* DrawItem) (pr->PrDC, Data, prevData, int(x), int(y),TRUE,prParam,rcPrintArea.top + hheight + 1,yend);

    if (!NextSame) {
      y += height;
      if (prevData != NULL) {
        (* Notify) (prevData,DDSLIST_RELEASEELE,bData);
        FreeGlobMem (prevData);
        }
      prevData = Data ;
      Data = (* GetNext)(Data, pr->PrDC, &height,prParam);
      }
    else
      y += y1 ;
    }

  if (prevData != NULL) {
    (* Notify) (prevData,DDSLIST_RELEASEELE,bData);
    FreeGlobMem (prevData);
    }
  if (Data != NULL) {
    (* Notify) (Data,DDSLIST_RELEASEELE,bData);
    FreeGlobMem (Data);
    }

  (* EndPage) (bData, pr->PrDC, rc.left, int(y), rc.right-rc.left, &hheight, PageNr, prParam, TRUE);
  pr->NewFrame();
  InPrinting = FALSE ;
  }
  
  
/*-------------------------------------------------------------------------*\
*  DESTRUCTOR DDSList                                                       *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport _export WINAPI DDSList::~DDSList ()
  {
  if (IsWindow (hWndList))
    DestroyWindow (hWndList);
  DestroyList (); 
  (* Notify) (bData,DDSLIST_DESTRUCT,bData);
  if (cbdata != NULL)
    FreeGlobMem (cbdata);
  if (buttons != NULL)
    delete buttons ;
  };
  
/*-------------------------------------------------------------------------*\
*  member function:  ListWnd                                                *
*                                                                           *
*  Parameter    :                                                           *
*  R¸ckgabewert :                                                           *
*  Zweck        :                                                           *
\*-------------------------------------------------------------------------*/
DLLExport HWND _export WINAPI DDSList::ListWnd ()
  {
  return hWndList;
  }

DLLExport void _export WINAPI DDSList::SetPrCallbacks (PRINTPAGE drawheadline, PRINTPAGE drawbottomline,PRINTPAGE startPage,PRINTENDPAGE endPage)
  {
  DrawHeadLine = drawheadline;
  DrawBottomLine = drawbottomline;
  StartPage = startPage;
  EndPage = endPage;
  }

DLLExport void _export WINAPI DDSList::SetCharCallback (DWORD parameter,DWORD procPtr)
  {
  ccPar = parameter;
  ccProc = procPtr;
  }

DLLExport BOOL _export WINAPI DDSList::CheckAbort ()
  {
  return CheckAbortFlag;
  }

DLLExport BOOL _export WINAPI DDSList::IsToAbort ()
  {
  if (!CheckAbort ()) return FALSE ;
  DBBOOL FAR *doAbort = (DBBOOL FAR *) (* GetData) (cbdata,AbortFlag);
  return ((doAbort != NULL) && (*doAbort));
  }

DLLExport void _export WINAPI DDSList::SetAbort (LPVOID cbd,DWORD flag,DWORD Initp,DWORD Exitp)
  {
  cbdata = GetGlobMem (GetBlockSize (cbd));
  lmemcpy (cbdata,cbd,GetBlockSize (cbd));
  CheckAbortFlag = TRUE;
  InitProc = Initp;
  ExitProc = Exitp;
  AbortFlag = flag;
  }

DLLExport void _export WINAPI DDSList::ClearAbort ()
  {
  FreeGlobMem (cbdata);
  cbdata = NULL;
  CheckAbortFlag = FALSE;
  }

void DDSList::CallInitAbort ()
  {
  if (CheckAbort ())
    (* CallCommand) (cbdata,InitProc,NULL);
  }
  
void DDSList::CallExitAbort ()
  {
  if (CheckAbort ()) {
    (* CallCommand) (cbdata,InitProc,NULL);
    (* CallCommand) (cbdata,ExitProc,NULL);
    }
  }

//////////////////////////////////////////////////////////////////////////
//  Eine DDSListe in einer Dialogbox
//////////////////////////////////////////////////////////////////////////
#define IDB_DELETE  100   // ACHTUNG ebenfalls deklariert in TOOLBAR.DLG
#define ID_DLIST    101

void SetDlgPos (HWND hDlg,HWND ActDlgOwner,LPRECT fr,LPRECT cr, int x, int y)
  {
  //----------------------------------------------------------------------
  // in der 16 Bit Version wurde die Dialogbox durch das Template bereits
  // richtig in der Groesse berechnet. Die 32 Bit Version liest den Dialog
  // noch aus der Resource.
  //----------------------------------------------------------------------
#ifdef WIN32
  int width = x;
  int height = y;
#else
  RECT r;
  GetWindowRect (hDlg,&r);
  int width = r.right - r.left ;
  int height = r.bottom - r.top ;
#endif

  // Untersuchen, wo die Dialogbox Platz haben koennte
  POINT pt;
  /*----< vertikale Position >-----*/
  if (fr->bottom + height < cr->bottom)
    pt.y = fr->bottom + 1;
  else
    pt.y = fr->top - height - 1;

  /*----< horizontale Position >-----*/
  if (fr->left + width < cr->right)
    // Auf jeden Fall linksbuendig mit dem Feld
    pt.x = fr->left;
  else
    pt.x = fr->right - width - 1;


// Nach einer Testphase loeschen (V167, 07.04.97)
//  // Untersuchen, wo die Dialogbox Platz haben koennte
//  POINT pt;
//  /*----< vertikale Position >-----*/
//  if (fr->bottom + height < cr->bottom) {
//    // Auf jeden Fall Unten
//    pt.y = fr->bottom + 1;
//    }
//  else {
//    int dyu = fr->bottom + height - cr->bottom ;
//    int dyo = fr->top - height - cr->top;
//    if (dyu > dyo) {
//      // Doch unten
//      pt.y = fr->bottom + 1;
//      }
//    else {
//      // Oben
//      pt.y = fr->top - height - 1;
//      }
//    }
//  /*----< horizontale Position >-----*/
//  if (fr->left + width < cr->right)
//    // Auf jeden Fall linksbuendig mit dem Feld
//    pt.x = fr->left;
//  else {
//    if ((cr->right - width - 1) > cr->left) {
//      // Rectsbuendig mit dem Fenster
//      pt.x = cr->right - width - 1;
//      }
//    else {
//      pt.x = cr->left ;
//      }
//    }

  // Und noch die Verschiebung
  MoveWindow (hDlg,pt.x,pt.y,width,height,FALSE);
  }



LPRECT _fr,_cr;
DLLExport BOOL _export CALLBACK DListDlgProc (HWND hDlg, UINT msg, WPARAM wP, LPARAM lP)
  {
  BOOL res = FALSE ;
  HWND hParent;
  switch (msg) {
    case WM_INITDIALOG :
      {
#ifdef WIN32
      POINT pt = *LPPOINT(lP);
      LONG dbu = GetDialogBaseUnits();
      int x = LOWORD(dbu)*pt.x / 4;
      int y = HIWORD(dbu)*pt.y / 8;
#else
      int x = 0;
      int y = 0;
#endif    

      SetDlgPos (hDlg,GetParent(hDlg),_fr,_cr, x, y);

      //******************************************************************
#ifdef WIN32
      BOOL WithDel = FALSE;

      int h = HIWORD(dbu)*14 / 8;
      SetWindowPos (hDlg, 0, 0, 0, x, y, SWP_NOMOVE | SWP_NOZORDER);
      if (GetDlgItem(hDlg, 100) != NULL)
        WithDel = TRUE;
      if (WithDel) {
        MoveWindow (GetDlgItem(hDlg, IDOK), 0, y-h, x/3, h, TRUE);
        MoveWindow (GetDlgItem(hDlg, IDCANCEL), x/3,y-h,2*(x/3)-x/3,h, TRUE);
        MoveWindow (GetDlgItem(hDlg, 101), 0, 0, x, y-h, TRUE);
        MoveWindow (GetDlgItem(hDlg, 100), 2*(x/3),y-h,x-2*(x/3),h, TRUE);
        }
      else {
        MoveWindow (GetDlgItem(hDlg, IDOK), 0, y-h, x/2, h, TRUE);
        MoveWindow (GetDlgItem(hDlg, IDCANCEL), x/2,y-h,x-(x/2),h, TRUE);
        MoveWindow (GetDlgItem(hDlg, 101), 0, 0, x, y-h, TRUE);
        }
#endif
      //******************************************************************

      _lst->hWndList = GetDlgItem (hDlg,ID_DLIST);
      _lst->SetButtons();
      SetWindowLong (_lst->hWndList,GWL_LISTPTR,LONG (LPSTR (_lst)));
      RECT cr;
      GetClientRect (_lst->hWndList,&cr);
      _lst->wheight = cr.bottom;
      _lst->Show(FALSE);
      SetFocus (GetDlgItem (hDlg,101));
      }

      // dieser Returnwert bedeutet, dass ich mich selber um den Fokus
      // kuemmern moechte
#ifdef WIN32
      res = FALSE;
#else
      res = TRUE ;
#endif
      break ;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

//      WORD wNotify = WORD(LOCHUNK(lP));
//      WORD whWnd   = WORD(HICHUNK(lP));

      switch (CRACKER_wID) {
        case IDB_DELETE :
          (* _lst->Notify) (_lst->bData,DDSLIST_DELBUTTONPRESSED,_lst->bData);
          _lst->DestroyList ();
          hParent = GetParent(hDlg);
          EndDialog (hDlg,TRUE);
          SetFocus (hParent);
          res = TRUE ;
          break;
        case IDCANCEL :
          _lst->DestroyList ();
          hParent = GetParent(hDlg);
          EndDialog (hDlg,FALSE);
          SetFocus (hParent);
          res = TRUE ;
          break ;
        case IDOK :
          if ((* _lst->Notify) (_lst->bData,DDSLIST_SELECT,_lst->bData)) {
            _lst->DestroyList ();
            hParent = GetParent(hDlg);
            EndDialog (hDlg,TRUE);
            SetFocus (hParent);
            res = TRUE ;
            }
          else
            res = FALSE ;
          break ;
        case ID_DLIST :
          {
          WORD wNotify = WORD(LOCHUNK(lP));
          if (wNotify == LBN_DBLCLK) {
            if ((* _lst->Notify) (_lst->bData,DDSLIST_SELECT,_lst->bData)) {
              _lst->DestroyList ();
              hParent = GetParent(hDlg);
              EndDialog (hDlg,TRUE);
              SetFocus (hParent);
              res = TRUE ;
              }
            else
              res = FALSE ;
            }
          }
          break ;
        }
      }
      break ;
    }
  return res;
  }

DLLExport void _export WINAPI DDSList::AfterStart ()
  {
  if (Notify != NULL)
    (* Notify) (bData,DDSLIST_AFTERSTART,bData);
  }

DLLExport BOOL _export WINAPI DDSList::CreateDlgList (HWND hWParent,
                                        LPRECT fRect,LPRECT cRect,
                                        int ButtonType,int w,int h,BOOL checkAnzElems)
  {
  Register ();
  _lst = this;
  _fr = fRect;    // fRect und cRect jeweils in Bildschirmkoordinaten
  _cr = cRect;
  double fc;
  GetBaseUnit (&fc);
  DWORD dbu = GetDialogBaseUnits ();
  if (w <= 0) w = 152 ;
  else        w = int (double(w) * fc) * 4 / LOWORD(dbu);
  if (h <= 0) h = 96 ;
  else        h = int (double(h) * fc) * 8 / HIWORD(dbu);

  wheight = (h - 14) * HIWORD(dbu) / 8 ;  // provisorisch, damit das Show was vernuenftiges macht
  for (HWND hWPopUpParent = hWParent; 
            ((IsWindow (hWPopUpParent)) && ((GetWindowLong (hWPopUpParent,GWL_STYLE) & WS_CHILD) == WS_CHILD)) ;
                hWPopUpParent = GetParent(hWPopUpParent) ) ;
  // Befuellen der Liste, damit AnzElemsInSelection richtig funktioniert
  if ((head == NULL) && (!EndReached) && (!BegReached)) {
    int h = FullHeight();
    if (StartElem != NULL) {
      Fill (h,StartElem,0);
      StartElem = NULL;
      CheckSelections (FALSE);
      }
    else
      Home (FALSE,FALSE);
    }
  if ((checkAnzElems) && (AnzElemsInSelection() == 1)) {
    (* Notify) (head->Data,DDSLIST_SELELE,bData);
    (* Notify) (bData,DDSLIST_SELECT,bData);
    _lst = NULL;
    // PostMessage (DoNotify, WMU_DESTROYDDSLIST, 0, LONG(LPSTR(this)));
    }
  else {
    AfterStart ();
    if (ButtonType == LIST_STANDARD) {

//**************************************************************************
// Momentan koennen die Dialogtemplates nicht unter WIN32 verwendet werden!
// Deshalb wird auf die alten Resourcen zurueckgegriffen!
//**************************************************************************
#ifndef WIN32
      DlgContainer dc (DialogBoxHeader (WS_POPUP | WS_BORDER,0,0,w,h,"",8,"Arial"));
      dc += ControlData (0,0,w,h-14,101,WS_CHILD | WS_GROUP | WS_TABSTOP,"DDSLISTCLASS","");
      dc += ControlData (0,h-14,w/2,14,IDOK,WS_GROUP | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_CHILD,0x80,"Ok");
      dc += ControlData (w/2,h-14,w-w/2,14,IDCANCEL,WS_GROUP | WS_VISIBLE | WS_TABSTOP | WS_CHILD,0x80,"Abbruch");

      return DialogBoxIndirect (hLibInst,dc.res,hWPopUpParent,DLGPROC(DListDlgProc));
#else
      POINT pt;
      pt.x = w;
      pt.y = h;
      return DialogBoxParam (hLibInst, "DLISTDLG", hWPopUpParent, DLGPROC(DListDlgProc), LPARAM(&pt));
#endif
      }
    else {
#ifndef WIN32
      DlgContainer dc (DialogBoxHeader (WS_POPUP | WS_BORDER,0,0,w,h,"",8,"Arial"));
      dc += ControlData (0,0,w,h-14,101,WS_CHILD | WS_GROUP | WS_TABSTOP,"DDSLISTCLASS","");
      dc += ControlData (0,h-14,w/3,14,IDOK,WS_GROUP | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_CHILD,0x80,"Ok");
      dc += ControlData (w/3,h-14,2*(w/3)-w/3,14,IDCANCEL,WS_GROUP | WS_VISIBLE | WS_TABSTOP | WS_CHILD,0x80,"Abbruch");
      dc += ControlData (2*(w/3),h-14,w-2*(w/3),14,100,WS_GROUP | WS_VISIBLE | WS_TABSTOP | WS_CHILD,0x80,"Lˆschen");

      return DialogBoxIndirect (hLibInst,dc.res,hWPopUpParent,DLGPROC(DListDlgProc));

#else
      POINT pt;
      pt.x = w;
      pt.y = h;
      return DialogBoxParam (hLibInst, "DELLISTDLG", hWPopUpParent, DLGPROC(DListDlgProc), LPARAM(&pt));
#endif
      }
    }
  return TRUE ;
  }

/////////////////////////////////////////////////////////////////////
//  Implementierung des Headers
/////////////////////////////////////////////////////////////////////
DLLExport void _export WINAPI DDSList::SetHeaderCallBack (GETHEADER gHeader,DRAWITEM dHeader)
  {
  GetHeader = gHeader;
  DrawHeader = dHeader;
  (* GetHeader) (bData, 0, &hdHeight);

  if (buttons != NULL) {
    RECT rc;
    GetClientRect (hWndList, &rc);

    rc.top += hdHeight;
    buttons->ArrangeButtons (BTN_RIGHT_POS, &rc);
    InitializeSize();
    }
  }

/////////////////////////////////////////////////////////////////////
//  ScrollKnoepfe in der Liste anzeigen
/////////////////////////////////////////////////////////////////////

//----------------------------------------------
// die Bitmaps werden aus der Resource geladen
//----------------------------------------------
static HBITMAP buttonhandle;
HBITMAP GetButtonBitmap (LPSTR szBmp)
  {
  if (buttonhandle == 0)
    buttonhandle = LoadBitmap (hLibInst, szBmp);
  return buttonhandle;
  }

void DestroyButtonBitmaps ()
  {
  if (buttonhandle) 
    DeleteObject (buttonhandle);
    
  buttonhandle = 0;  
  }


#define ANZBUTTONS  12    // zur Zeit befinden sich 12 Bilder im Bitmap


void CreateListButtons (HWND hWnd, LPSINGLELIST BtnList)
  {
  LPBITBUTTON Button = NULL;
  RECT rcList;
  
  HBITMAP hBmp = GetButtonBitmap ("BUTTONS");  // Bitmaps f¸r die Knˆpfe
  if (hBmp != 0) {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    GetClientRect (hWnd, &rcList);
    
    // der Knopf "gehe an den Anfang der Liste"
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_HOME, 1);  // 1.Bild aus 1.Zeile
    rcList.bottom++;
    y = rcList.top = rcList.bottom-Button->GetHeight();   // Knˆpfe kommen an den unteren Rand
    Button->SetXYPos (x, y);                              // Position neu festlegen
    BtnList->Insert (Button);                             // und in die Liste einf¸gen

    // der Knopf "Bl‰ttern zur vorigen Seite"
    x += Button->GetWidth();
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_PREVPAGE, 1);
    Button->AllowTimer();    // zu Testzwecken
    BtnList->Insert (Button);
    
    // der Knopf "gehe um ein Element nach oben"
    x += Button->GetWidth();
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_PREV, 1);
    Button->AllowTimer();    // zu Testzwecken
    BtnList->Insert (Button);

    x += 50;    // Platz zwischen den Knopf-Elementen f¸r "Bewegen nach oben" und "Bewegen nach unten"
    // der Knopf "gehe um ein Element nach unten"
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_NEXT, 1);
    Button->AllowTimer();    // zu Testzwecken
    BtnList->Insert (Button);

    // der Knopf "Bl‰ttern zur n‰chsten Seite"
    x += Button->GetWidth();
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_NEXTPAGE, 1);
    Button->AllowTimer();    // zu Testzwecken
    BtnList->Insert (Button);

    // der Knopf "gehe an das Ende der Liste"
    x += Button->GetWidth();
    Button = new BitButton (NULL, 0, hWnd, x, y, w, h, hBmp, ANZBUTTONS, 1, BTN_IND_END, 1);
    BtnList->Insert (Button);
    }

  }  


DLLExport void _export WINAPI DDSList::SetButtons ()
  {
  RECT rc;

  buttons = new SingleList (hWndList);
  CreateListButtons (hWndList, buttons);
  
  GetClientRect (hWndList, &rc);

  rc.top += hdHeight;
  buttons->ArrangeButtons (BTN_RIGHT_POS, &rc);

  InitializeSize();
  }

DLLExport int _export WINAPI DDSList::AnzElemsInSelection ()
  {
  int res ;
  (* Notify) (&res,DDSLIST_GETSELCOUNT,bData);
  return res ;
  }

