/////////////////////////////////////////////////////////////////
//    Implementierung der Klasse cWord,cField, Fortsetzung;
//
/////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/cword1.cpv   1.67   31 Mar 2000 19:47:14   Martin  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/cword1.cpv  $
// 
//    Rev 1.67   31 Mar 2000 19:47:14   Martin
// DeleteSelectedLines in PasteFromClipboard nur wenn Selektion vorhanden
// 
//    Rev 1.66   28 Mar 2000 09:05:06   Hannes
// PasteFromClipBoard: Einfueng an entsprechender Stelle
// 
//    Rev 1.65   16 Feb 2000 12:08:42   Martin
// nochmal WIN_ASSERT raus
// 
//    Rev 1.64   19 Jan 2000 20:05:26   Martin
// WIN_ASSERTs raus
// 
//    Rev 1.63   03 Sep 1999 05:03:36   Hannes
// Einrueckung aktiviert
// 
//    Rev 1.62   16 Aug 1999 18:37:42   Hannes
// Verbesserungen SlantFields
// 
//    Rev 1.61   04 Aug 1999 18:27:58   Wolfgang
// 1.) CheckDirKey hat zusaetzlichen Parameter keyToUse.
// 2.) IsKeyToUse nach CWORD verschoben.
// 
//    Rev 1.60   27 Jun 1999 21:55:40   Hannes
// Hilfsfunktionen fuer Rechtschreibpruefung
// 
//    Rev 1.59   22 Apr 1999 17:19:32   Hannes
// 
//    Rev 1.58   02 Feb 1999 21:29:22   Hannes
// SlantFieldHandling
// 
//    Rev 1.57   18 Nov 1998 15:48:24   Hannes
// Diverse Verbesserungen am Farbhandling
// 
//    Rev 1.56   10 Nov 1998 07:58:08   Hannes
// Ev. Abschliessen mit FormatEnde
// 
//    Rev 1.55   09 Oct 1998 18:02:12   Gerhold
// Farben in Strings
// 
//    Rev 1.54   13 Jul 1998 16:09:20   Hannes
// Absicherung von SetCaretInLine
// 
//    Rev 1.53   09 Jul 1998 10:49:42   Hannes
// \ - Handling im Clipboard
// 
//    Rev 1.52   30 Jun 1998 15:54:18   Gerhold
// ::InvalidateSelectedWords (fErase = TRUE statt FALSE)
// 
//    Rev 1.51   22 May 1998 10:11:28   Hannes
// Verbesserung des Scrollhandlings bei einzeiligen Feldern
// 
//    Rev 1.50   11 May 1998 13:33:04   Gerhold
// Sondertasten wie ALT, NUMLOCK, SCROLLOCK,.. loeschen nicht mehr die Sel.
// 
//    Rev 1.49   07 Apr 1998 19:50:32   Hannes
// Minimalste Absicherung bei '\'
// 
//    Rev 1.48   19 Nov 1997 18:46:00   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.47   27 Oct 1997 19:52:30   Hannes
// RemoveNotNeededFormats in PasteFromClipboard
// 
//    Rev 1.46   21 Oct 1997 16:29:56   Hannes
// 
//    Rev 1.45   25 Sep 1997 08:21:12   Hannes
// Speicherfehler -> 4 Byte pro Format dazu
// 
//    Rev 1.44   24 Sep 1997 20:33:30   Hannes
// Formatumsetzung bei Mappings
// 
//    Rev 1.43   19 Sep 1997 15:48:20   Hannes
// 
//    Rev 1.42   17 Sep 1997 16:27:32   gerhold
// Cursorbewegungen bei selektierten Texten VK_LEFT, VK_RIGHT
// 
//    Rev 1.41   23 Apr 1997 15:32:20   Hannes
// 
//    Rev 1.40   22 Apr 1997 12:09:32   Hannes
// 
//    Rev 1.39   21 Apr 1997 17:20:52   Hannes
// ~cword: Wegschmeissen der Formatierfunktion
// 
//    Rev 1.38   21 Mar 1997 11:27:16   Hannes
// IsKeyToUse
// 
//    Rev 1.37   03 Mar 1997 11:46:36   Hannes
// cField::SetDefFormat
// 
//    Rev 1.36   05 Feb 1997 14:22:26   HANNES
// 
//    Rev 1.35   05 Feb 1997 14:06:34   HANNES
// 
//    Rev 1.34   05 Feb 1997 13:50:52   HANNES
// 
//    Rev 1.33   31 Jan 1997 17:20:40   HANNES
// 
//    Rev 1.32   31 Jan 1997 15:39:02   HANNES
// 
//    Rev 1.31   29 Jan 1997 18:10:50   HANNES
// 
//    Rev 1.30   27 Jan 1997 17:26:16   HANNES
// No change.
// 
//    Rev 1.29   08 Jan 1997 14:39:24   HANNES
// BreakAllowed besser getestet
// 
//    Rev 1.28   07 Jan 1997 18:07:06   HANNES
// Beistriche bei Zahleneingaben durchlassen
// 
//    Rev 1.27   16 Dec 1996 18:46:08   HANNES
// Einfuegen aus dem Clipboard
// 
//    Rev 1.26   07 Nov 1996 12:48:48   GERHOLD
// In Eingabefelder die einen CheckButton haben keine Paste-Clipboard zulassen
// 
//    Rev 1.25   28 Sep 1996 15:49:36   GERHOLD
// Accelerator-Tasten mit CTRL haben nicht funktioniert; deshalb wird bei
// Zeicheneingaben auf CTRL geprueft und diese somit als Accelerator befunden.
// 
//    Rev 1.24   11 Sep 1996 14:13:58   HANNES
// 
//    Rev 1.23   06 Sep 1996 17:26:12   HANNES
// 
//    Rev 1.22   04 Sep 1996 15:55:14   MARTIN
// 
//    Rev 1.21   22 May 1996 18:00:46   MARTIN
// alten Font wieder zurueckselektieren
// 
//    Rev 1.20   18 May 1996 20:56:42   HANNES
// FehlerKorrekturen
// 
//    Rev 1.19   30 Apr 1996 17:09:08   HANNES
// Fehelrkorrektur: CompareIVListe, ShiftHandling, FormatSelection
// 
//    Rev 1.18   13 Apr 1996 19:56:28   HANNES
// Verbesserung von mehrseitigen Feldern, Passworthandling
// 
//    Rev 1.17   05 Apr 1996 13:58:52   MARTIN
// Zusaetzlich First != NULL ...
// 
//    Rev 1.16   04 Apr 1996 20:31:44   HANNES
// No change.
// 
//    Rev 1.15   04 Apr 1996 18:35:14   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.14   24 Mar 1996 12:10:54   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.13   22 Mar 1996 12:13:20   HANNES
// Aenderungen Hannes
// 
//    Rev 1.12   23 Feb 1996 09:50:32   HANNES
// Flackern, versteckter Trennstrich
// 
//    Rev 1.11   22 Feb 1996 15:30:40   GERHOLD
// GetAnzLines wird jetzt exportiert
// 
//    Rev 1.10   02 Feb 1996 10:46:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   12 Jan 1996 14:53:50   MARTIN
// VK_LEFT: Abfrage auf First != NULL
// 
//    Rev 1.8   11 Jan 1996 04:49:28   HANNES
// 
//    Rev 1.7   11 Jan 1996 03:35:00   HANNES
// 
//    Rev 1.6   10 Jan 1996 21:04:46   HANNES
// 
//    Rev 1.5   10 Jan 1996 17:54:34   HANNES
// RemoveFormatInfo, FormatMaps
// 
//    Rev 1.4   10 Jan 1996 15:05:50   GERHOLD
//  Soll ein Combo-Formularfeld Eingaben zulassen muss nach dem fieldMode
//  FM_BTNWITHINPUT abgefragt werden.
// 
//    Rev 1.3   08 Jan 1996 17:41:44   HANNES
// Defaultmodify, Wortumbruch
// 
//    Rev 1.2   05 Jan 1996 20:00:14   HANNES
// Fehlerkorrektur Formatierung
// 
//    Rev 1.0   02 Jan 1996 22:12:06   HANNES
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#include "font.hpp"
#define CFIELD_ALSO
#include "cfield.hpp"
#include "fldcombo.hpp"
#define MODULENUM 140
#include "winass.hpp"

BOOL IsValidEscape (char ch)
  {
  return ((ch == 'f') || (ch == 'e') || (ch == 'h') || (ch == 'z') || (ch == 'c')) ;
  }

BOOL cField::IsCharAllowed (WPARAM wP,BOOL FAR *dontBeep,BOOL forDel,BOOL delUnder)
  {
  WORD orgChar = wP ;
  *dontBeep = FALSE ;
  if (cfb != NULL) {
    TCI t;
    t.wP = wP ;
    t.dontBeep = FALSE ;
    t.cPos = GetRealPos ();
    t.forDel = forDel;
    t.delUnder = delUnder;
    (* cfb) (CALLBACKCMD_ISCHARALLOWED,&t,CallBackMem);
    wP = t.wP ;
    *dontBeep = t.dontBeep ;
    }
  return (wP == orgChar);
  }

#define TD_START    0
#define TD_FAULT    1
#define TD_VK       2
#define TD_K        3
#define TD_NK       4
#define TD_END      5
#define TD_SIGN     6

#define CTEND       0
#define CTKOMMA     1
#define CTDIGIT     2
#define CTSIGN      3
#define CTUNKNOWN   4
inline int chartype(LPSTR h)
  {
  if (*h == '\0') return CTEND ;
//  if (*h == '.') return CTKOMMA ;
  if ((*h == '-') || (*h == '+')) return CTSIGN ;
  if (((*h >= '0') && (*h <= '9')) || (*h == ',') || (*h == '.')) return CTDIGIT ;
  return CTUNKNOWN ;
  }

BOOL cField::TestDecimal (WPARAM wP)
  {
  LPSTR res;
  char str[3];
  InsertStr (res,makeStr(str,char(wP)));  // makestr ueberprueft auch auf '\\'
  int state = TD_START;
  for (LPSTR h = res ; ((state != TD_FAULT) && (state != TD_END)) ; ) {
    int ct = chartype(h);
    switch (state) {
      case TD_START:
        if (ct == CTDIGIT)      state = TD_VK ;
        else if (ct == CTKOMMA) state = TD_K;
        else if (ct == CTEND)   state = TD_END;
        else if (ct == CTSIGN)  state = TD_SIGN;
        else state = TD_FAULT ;
        break ;
      case TD_SIGN :
        if (ct == CTDIGIT) state = TD_VK ;
        else if (ct == CTKOMMA) state = TD_K;
        else if (ct == CTEND) state = TD_END;
        else state = TD_FAULT ;
        break ;
      case TD_VK:
        if      (ct == CTKOMMA) state = TD_K ;
        else if (ct == CTEND) state = TD_END ;
        else if (ct != CTDIGIT) state = TD_FAULT ;
        break ;
      case TD_K:
        if (ct == CTDIGIT) state = TD_NK ;
        else if (ct == CTEND) state = TD_END ;
        else state = TD_FAULT ;
        break ;
      case TD_NK:
        if (ct == CTEND) state = TD_END ;
        else if (ct != CTDIGIT) state = TD_FAULT ;
      }
    h ++ ;
    }
  FreeGlobMem (res);
  return (state == TD_END);
  }

extern void setFieldButtonUp ();
extern cFieldCombo cfBtn;
void cField::ShowList (LPSTR str)
  {
  cfBtn.BeginList (this);
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_SHOWLIST,str,CallBackMem);
  setFieldButtonUp ();
  }

BOOL cField::TestChar (WPARAM wP,BOOL forDel,BOOL delUnder)
  {
  BOOL res = TRUE ;
  BOOL dontBeep = FALSE;
  if (!IsCharAllowed (wP,&dontBeep,forDel,delUnder)) {
    if (!dontBeep) MessageBeep (0);
    return FALSE ;
    }
  if ((fieldMode & FM_LSELECTION) && (!IsLocked())) {
    char str[3];
    ShowList (makeStr(str,char(wP)));
    return FALSE ;
    }
  if (IsLocked())
    return FALSE ;      // Nix tippen, aber auch nicht biepsen

  if (!forDel) {
    if ((wP == '\r') && 
            (
             ((fieldMode & FM_SINGLELINE) == FM_SINGLELINE) ||
             ((AnzLines > 0) && (GetAnzLines() >= AnzLines))
            )
       )
      res = FALSE ;
    if (IsTextLimited ()) 
      res = FALSE ;
    if ((fieldMode & FM_DECIMAL) == FM_DECIMAL)
      res = TestDecimal(wP);
    }
  if (!res) MessageBeep (0);
  return res ;
  }

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
extern void ResetActFormats ();
extern char _startFormat[4];
extern char _endFormat[4];
extern char _startColor[11];
extern char _endColor[11];
extern DWORD _actColor;
// #define WITH_TESTCONTENT
DLLExport BOOL _export WINAPI cField::OnChar (WPARAM wP,int Seite)
  {
#ifdef WITH_TESTCONTENT
  if (wP == '?') {
    WIN_ASSERT_TEXT (FALSE,Text);
    return TRUE ;
    }
#endif
  // if (wP == 92)      // Big Bullshit: haendisch wird kein '\\' zugelassen
  //  return FALSE;

  int letzteSeite;
  if (cfBtn.MyField == this)
    letzteSeite = LastPage();
  // Kombinationen mit CONTROL werden bis auf CTRL-BS, CTRL-Enter 
  // und CTRL-Delete nicht zugelassen!
  if ((GetKeyState(VK_CONTROL) < 0) && ((GetKeyState (VK_MENU) >= 0) && (!((wP == '\b') || (wP == '') || (wP == '\r')))))
    return FALSE;

  if (ActiveField == this) {
    if (HasButton && !(fieldMode & FM_BTNWITHINPUT)) {
      TestChar (wP, FALSE);
      return TRUE;
      }
      
    if (wP == '\b') {            // BACKSPACE
      ResetActFormats ();
      ResetAndDeleteSelState (wP,Seite);
      if ((Text != NULL) && (TestChar (wP,TRUE,FALSE))) {
        DelChar (FALSE,FALSE);   // DelUnder = FALSE
        if (cfb != NULL) {
          (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
          int nModify = 0;
          (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
          }
        }
      }
    else if (wP == '') {
      ResetActFormats ();
      ResetAndDeleteSelState (wP,Seite);
      if ((Text != NULL) && (TestChar (wP,TRUE,FALSE))) {
        DelChar (TRUE,FALSE);    // ganzes Wort loeschen
        if (cfb != NULL) {
          (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
          int nModify = 0;
          (*cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
          }
        }
      }
    //-----------------------------------------------------------------
    // ausser dem Tabulator der speziell in TOOLBAR.CPP behandelt wird,
    // duerfen im "NUR-LOESCHEN" - Modus, keine Zeichen durch.
    //-----------------------------------------------------------------
    else if ((wP != '\033') && (!(fieldMode & FM_JUSTDEL) || (wP == '\t'))) {
      ResetAndDeleteSelState (wP,Seite);
      if (TestChar (wP,FALSE)) {
        if (AlreadySelected) {
          InvalidateSelectedWords ();
          ClearSelection ();
          }

        char str[64];
        //------------------------------------
        // Haessliche Micky-Maus Loesung!!!!!!
        char begstr[32],endstr[32];
        lstrcpy (begstr,_startFormat);
        lstrcat (begstr,_startColor);
        lstrcpy (endstr,_endFormat);
        lstrcat (endstr,_endColor);
        lstrcpy (str, makeStr(str, begstr,char(wP), endstr));

        int mLen = GetMaxChars();
        int AvailableLen = mLen - GetAnzChars();
        if ((mLen < 0) || (AvailableLen > 0)) {
          if ((mLen > 0) && (lstrlen(str) >= AvailableLen)) {
            str[AvailableLen-1] = '\0';
            }
          
          InsertStr (str);
          RemoveNotNeededFormats ();

          if (cfb != NULL)
            (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
          }
        else
          MessageBeep (0);  
        }
      }

    CheckScroll (Seite);
    }
  ResetActFormats ();
  if (cfBtn.MyField == this) {
    if (LastPage() != letzteSeite) {
      // Der Knopf muss die Seite wechseln
      cfBtn.OnMapChange (this);
      Invalidate(Seite,TRUE);
      }
    }
  return TRUE;
  }

DLLExport cField FAR & _export WINAPI cField::operator = (POINT pt)
  {
  x0 = pt.x ;
  y0 = pt.y ;
  cfBtn.OnMapChange (this);
  if (yPageMax > 0) {
    // Seitenumbruch muss ev. neu berechnet werden
    int AlteZeile = 0 ;
    int x = 0 ;
    int Seite = 0 ;
    int y = yTopHeight (DefFormat) + yBaseHeight (DefFormat);
    for (cWord FAR *h = First ; h != NULL ; h = h->Next ) {
      if (h->LineNmbr != AlteZeile) {
        AlteZeile = h->LineNmbr ;
        cWord FAR *p = GetPrev(h);
        WIN_ASSERT (p != NULL);
        p->GetNextLinePos (x,y,Seite,AlteZeile);
        }
      h->RelativSeite = Seite ;
      h->yPos = y ;
      }
    }
  return *this;
  }

DLLExport _export WINAPI cField::cField (WORD bkm,int format,int x,int y,int width,
                                int anzlines,BOOL doSel)
  {
  bkmode = bkm;
  DefFormat = format;
  x0 = x ; y0 = y ;
  xWidth = width;
  AnzLines = anzlines;
  doSelect = doSel;
  AlreadySelected = FALSE;
  xvPos = -1 ;
  }

int cField::GetCaretHeight (HDC hDC,int Format,int FAR *logheight)
  {
  POINT pt[2];
  pt[0].x = pt[1].x = 0;
  pt[0].y = 0 ;
  pt[1].y = yHeight (Format);
  if (logheight != NULL) *logheight = pt[1].y ;
  LPtoDP (hDC,pt,2);
  int dy = pt[1].y - pt[0].y ;
  return (dy > 0) ? dy : -dy ;
  }

int cField::GetCaretHeight (int FAR *logheight)
  {
  int Format,Modify;
  if (act != NULL) Format = int (act->wFormat) , Modify = int (act->wModify);
  else             Format = DefFormat , Modify = DefModify();
   
  HDC hDC = GetFieldDC ();
  int dy = GetCaretHeight (hDC,Format,logheight);
  RestDC (hDC);
  return dy;
  }

//---------------------------------------------------------------------------
// Setzt die Klassenvariable <act> auf das Wort in dem das Caret steht
//---------------------------------------------------------------------------
void cField::SetActToCaret ()
  {
  if (First == NULL) Reformat ();
  prev = NULL;
  if (Text != NULL) {
    LPSTR h = Text + cPos;
    for ( act = First ; act != NULL ; act = act->Next) {
      // Dieses Wort hat die Position
      if ((act->Text <= h) && (act->Text + act->AnzChars > h))
        break;
      if ((h == act->Text + act->AnzChars) && ((*h == '\r') || (*h == '\0')))
        break ;
      prev = act;
      }
    }
  }

void cField::GetCaret ()
  {
  if ((IsWindow (Wnd)) && (oldCaretHeight <= 0)) {
    SetActToCaret ();
    int physheight = GetCaretHeight ();
    CreateCaret (Wnd,NULL,2,physheight);
    oldCaretHeight = physheight;
    CaretIsVisible = FALSE ;
    }
  }

extern void ShowFieldCaret (HWND hWnd);
extern void HideFieldCaret (HWND hWnd);
void cField::ReleaseCaret ()
  {
  if (IsWindow (Wnd)) {
    HideFieldCaret (Wnd);
    if (oldCaretHeight) {
      DestroyCaret ();
      }
    }
  oldCaretHeight = 0;
//*  oldCaretIsShown = FALSE;
  }

void cField::toDPKoords (HDC hDC,int FAR &x,int FAR &y)
  {
  POINT pt;
  pt.x = x , pt.y = y;
  LPtoDP (hDC,&pt,1);
  x = pt.x , y = pt.y ;
  }

void cField::toLPKoords (HDC hDC,int FAR &x,int FAR &y)
  {
  POINT pt;
  pt.x = x , pt.y = y;
  DPtoLP (hDC,&pt,1);
  x = pt.x , y = pt.y ;
  }

void cField::CheckCaretHeight (HDC hDC,int Format,int Modify)
  {
  int height = GetCaretHeight (hDC,Format);
  if (height != oldCaretHeight) {
    ReleaseCaret ();
    GetCaret ();
    }
  }

int cField::GetDefPosition (int Format)
  {
  int of = OutFormat (Format);
  if (xWidth < 0) return 0 ;
  switch (of) {
    case FR_CENTERED :
      return xWidth / 2;
    case FR_RIGHT :
      return xWidth ;
    default :
      return 0 ;
    }
  }

void cField::GetCaretPos (HDC hDC,int FAR &x,int FAR &y,int FAR &LNmbr,
                          int FAR &Format,int FAR &Modify,BOOL checkAlways)
  {
  if ((oldCaretHeight) || (checkAlways)) {
    SetExistingAct ();
    if (act != NULL) {
      HFONT OldFont = 0;
      ModifyDC (hDC,Format = act->wFormat,Modify = act->wModify,&OldFont);
      if ((act->WordType == WORDTYPE_CR) &&
              (cPos >= WORD (act->wOffs() + act->AnzChars))) {
        // Darf eigentlich nur hinten passieren
        y = y0 + act->yPos - yBaseHeight (act->wFormat) ;
        if ((act->LineNmbr < AnzLines - 1) || (AnzLines < 0)) {
          x = x0 + GetDefPosition (act->wFormat);

          y += yLineHeight (act->wFormat) ;
          if ((yPageMax > 0) && (y0 + act->yPos - act->yBaseHeight + 2 * act->yHeight > yPageMax))
            y = yPageNext ;
          LNmbr = act->LineNmbr + 1;
          }
        else {
          x = x0 + act->xPos + act->xExtra ;
          LNmbr = AnzLines - 1;
          }
        }
      else {
        // Ganz normale Positioniern
        int xl = max(0,min (int (cPos - act->wOffs ()),act->AnzChars));
        int xp = act->xIntermWidth (hDC,xl);
        int xe = act->xPos + act->xExtra + xp ;
        if ((xWidth > 0) && (xe > xWidth)) xe = xWidth;
        x = x0 + xe;
        y = y0 + act->yPos - yBaseHeight (act->wFormat);
        LNmbr = act->LineNmbr;
        }
      if (OldFont)
        SelectObject(hDC,OldFont);
      }
    else {
      x = x0 + GetDefPosition (DefFormat);
      y = y0 ;
      LNmbr = 0;
      }
    }
  }

void cField::PosCaret (HDC hDC, BOOL SetOnNewPosition, BOOL ShowMe,int FAR *xres)
  {
  if (oldCaretHeight && (!HasButton || (fieldMode & FM_BTNWITHINPUT))) {
    int x,y,LineNmbr,Format,Modify;

    BOOL doRest = FALSE;
    if (hDC == 0) {
      hDC = GetFieldDC ();
      doRest = TRUE ;
      }

    GetCaretPos (hDC,x,y,LineNmbr,Format,Modify);
    if (xres != NULL) *xres = x ;
    CheckCaretHeight (hDC,Format,Modify);
    if (SetOnNewPosition)
      SetCaretToPos (hDC,x,y);
    if (doRest)
      RestDC (hDC);

    if (ShowMe || !AlreadySelected)
      ShowFieldCaret (Wnd);
    else
      HideFieldCaret (Wnd);
    }
  }

void cField::SetCaretToPos (HDC hDC,int x,int y)
  {
  toDPKoords (hDC,x,y);
  SetCaretPos (x,y);
  }

void cField::SetExistingAct ()
  {
  WORD vStart = 0 ;
  for ( act = First ; act != NULL ; act = act->Next ) {
    if (act->Next == NULL) break ;
    WORD vNext = act->Text + act->AnzChars - Text ;
    if ((vNext > cPos) && (vStart <= cPos)) break ;
    vStart = vNext ;
    }
  }

cWord FAR * cField::GetWordForFormat ()
  {
  for (cWord FAR *h = First ; h != NULL ; h = h->Next ) {
    if (h->Next == NULL) break ;
    if ((WORD (h->Text + h->AnzChars - Text) >= cPos) && (WORD(h->Text - Text) <= cPos)) break ;
    }
  return h ;
  }

cWord FAR * cField::GetExistingWordWithPos (int pos)
  {
  int vStart = 0 ;
  for ( cWord FAR *h = First ; h != NULL ; h = h->Next ) {
    if (h->Next == NULL) break ;
    int vNext = h->Text + h->AnzChars - Text ;
    if ((vNext > pos) && (vStart <= pos)) break ;
    vStart = vNext ;
    }
  return h ;
  }

inline BOOL Is92 (LPSTR Text,WORD cPos)
  {
  return ((Text[cPos] == '\\') && (Text[cPos + 1] == '\\')) ;
  }

inline BOOL Is92Prev (LPSTR Text,WORD cPos)
  {
  return ((Text[cPos] == '\\') && (cPos > 0) && (Text[cPos - 1] == '\\')) ;
  }

WORD cField::GetNextWordStart (WORD cP)
  {
  cPos = cP;
  SetExistingAct ();
  
  WORD res;
  if (act == NULL) {
    if (Text != NULL) 
      if (cPos < WORD (lstrlen(Text))) {
        if (Is92 (Text,cPos)) return SkipFormat (Text + cPos + 2) - Text;
        else                  return SkipFormat (Text + cPos + 1) - Text;
        }
    else
      return 0 ;
    }
  for ( BOOL first = (WORD (act->Text - Text) <= cPos) ; ; ) {
    if ((first) && (act->Next != NULL)) {
      act = act->Next ;
      }
    else if ((act->WordType == WORDTYPE_CHARS) && (!first)) {
      res = act->Text - Text ;
      break ;
      }
    else if (act->Next == NULL) {
      if (Is92 (act->Text,0))
        res = act->Text + 2 - Text ;
      else
        res = act->Text + act->AnzChars - Text ;
      break ;
      }
    else
      act = act->Next ;
    first = FALSE ;
    }
  return res;
  }

WORD cField::GetPrevWordStart (WORD cP)
  {
  cPos = cP;
  SetExistingAct ();
  
  WORD res;
  if (act == NULL) return 0 ;
  else {
    for ( BOOL first = TRUE ; ; ) {
      cWord FAR *prev = GetPrev();
      if (first) {
        if ((act->WordType == WORDTYPE_CHARS) && (Text + cPos <= act->Text))
          first = TRUE ;
        else
          first = FALSE ;
        }
      if ((first) && (prev != NULL)) {
        act = prev ;
        }
      else if ((act->WordType == WORDTYPE_CHARS) && (!first)) {
        res = act->Text - Text ;
        break ;
        }
      else if (prev == NULL) {
        res = SkipFormat (Text) - Text;
        break ;
        }
      else
        act = prev ;
      }
    }
  return res;
  }

cWord FAR *cField::GetPrev (cWord FAR *act)
  {
  if (act == NULL) return NULL;
  else             return act->Prev ;
  }

cWord FAR *cField::GetPrev ()
  {
  return GetPrev (act);
  }

cWord FAR *cField::GetLast ()
  {
  for (cWord FAR *h = First ; ((h != NULL) && (h->Next != NULL)) ; h = h->Next) ;
  return h;
  }

cWord FAR *cField::GetWordWithPos (int Pos)
  {
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    int p = h->wOffs();
    if ((Pos >= p) && (Pos < (p + h->AnzChars)))
      break;
    }
  
  return h;
  }

DLLExport int _export WINAPI cField::GetAnzLines ()
  {
  if (First == NULL) Reformat ();     // Formatiert muss noch werden
  cWord FAR *h = GetLast ();
  if (h != NULL) {
    int l = h->LineNmbr + 1;
    if (h->WordType == WORDTYPE_CR) l++;
    if (AnzLines > 0)
      return min (AnzLines,l);
    else
      return l;
    }
  else
    return 0;
  }

DLLExport int _export WINAPI cField::GetActLine ()
  {
  if (First == NULL) Reformat ();     // Formatiert muss noch werden
  if (act != NULL)
    return act->LineNmbr;
  else
    return 0;
  }

void cField::SetCaretInLine (HDC hDC, int l, int x)
  {
  if (First == 0) {
    cPos = 0;
    return ;
    }
  if (l < 0) {
    SetCaretInLine (hDC, 0, x);
    return;
    }
  else {
    int al = GetAnzLines();
    if (l > al) {
      SetCaretInLine (hDC, al, x);
      return;
      }
    }  
      
  BOOL LineFound = FALSE ;
  x -= x0 ;
  cPos = 0xFFFF ;

  cWord FAR *end;
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if ((!LineFound) && (h->LineNmbr == l)) {
      LineFound = TRUE ;
      end = GetLineEnd (h,NULL);
      }
    if (LineFound) {
      if (x < h->xPos + h->xExtra) {
        cPos = h->wOffs ();
        break ;
        }
      // Caret befindet sich im Wort
      else if ((x >= h->xPos + h->xExtra) && (x < h->xPos + h->xExtra + h->xLen)) {
        int xw = x - (h->xPos + h->xExtra);
        HFONT OldFont = 0;
        ModifyDC (hDC,h->wFormat,h->wModify,&OldFont);
        int lastWidth;
        for (int i = 1 ; i < h->AnzChars ; i++) {
          lastWidth = h->xIntermWidth (hDC,i);
          if (lastWidth > xw) {
            if (OldFont)
              SelectObject(hDC,OldFont);
            break;  // bereits zu gross
            }
          }
          
        // Entscheidet, ob bei einem grossen Zeichen das Caret
        // links oder rechts vom Zeichen zum Stehen kommt!
        if (i > 0)
          if (xw < ((lastWidth + h->xIntermWidth(hDC,i-1)) / 2))
            i--;
            
        cPos = h->wOffs() + i;
        if ((h == end) && (i == h->AnzChars) && (Text[cPos] != '\0'))
          cPos -= 1 ;
        if (OldFont)
          SelectObject(hDC,OldFont);
        break ;
        }
      else if ((h == end) || (h->Next == NULL)) {
        if ((h->wOffs() > 0) || (h->AnzChars > 0)) {
          cPos = h->AnzChars + h->wOffs () - 1;
          if ((h->WordType != WORDTYPE_CR) && (cPos > 0) && (Text[cPos+1] == '\0'))
            cPos += 1;
          }
        else
          cPos = lstrlen (Text);
        break ;
        }
      }
    }
  if (cPos == 0xFFFF) {
    cPos = lstrlen (Text);
    }
  if ((cPos > WORD(First->Text - Text)) && (PrevIsFormatStr (Text + cPos - 1,Text)))
    // cPos wird auf das Ende des vorigen Wortes gesetzt
    cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
  }



void cField::GetSelectionFromLeftToRight (LPFSS SelStart, LPFSS SelEnd)
  {
  if (StartSel.CaretPos > EndSel.CaretPos) {
    *SelStart = EndSel;
    *SelEnd = StartSel;
    }
  else {
    *SelStart = StartSel;
    *SelEnd = EndSel;
    }
  }


extern FieldSelStruct SaveStart, SaveEnd;
extern BOOL SaveAlreadySelected;
extern cField FAR *SavecField;
extern BOOL dontSetSelection;
void cField::ClearSelection ()
  {
  SaveStart = StartSel;
  SaveEnd = EndSel;
  SaveAlreadySelected = AlreadySelected;
  SavecField = this;

  if (First != NULL)
    StartSel.CaretPos = SkipFormat(Text) - Text;
  else
    StartSel.CaretPos = 0;

  StartSel.SelWord = NULL;
  EndSel.CaretPos = StartSel.CaretPos;
  EndSel.SelWord = NULL;
  AlreadySelected = FALSE;
  }

void cField::InvalidateSelectedWords ()
  {
  FieldSelStruct SelStart, SelEnd;

  GetSelectionFromLeftToRight (&SelStart, &SelEnd);  // SelStart < SelEnd
  if (SelStart.SelWord == NULL)
    return;

  HDC hDC = GetFieldDC ();
  for (cWord FAR* w = SelStart.SelWord; w != NULL; w = w->Next) {
    w->Invalidate (hDC, TRUE);
    if (w == SelEnd.SelWord)
      break;
    }

  RestDC (hDC);
  }

//----------------------------------------------------------------------------
void cField::InvalidateWordRange (cWord FAR *StartWord, cWord FAR *EndWord)
  {
  cWord FAR *Start; 
  cWord FAR *End;

  if (StartWord == NULL) StartWord = First;
  if (EndWord == NULL) EndWord = GetLast();
  if (StartWord->wOffs() > EndWord->wOffs()) {
    Start = EndWord;
    End   = StartWord;
    }
  else {
    Start = StartWord;
    End   = EndWord;
    }  
    
  HDC hDC = GetFieldDC ();
  for (cWord FAR* w = Start; w != NULL; w = w->Next) {
    w->Invalidate (hDC, FALSE);
    if (w == End)
      break;
    }  
  RestDC (hDC);
  }


//----------------------------------------------------------------------------
BOOL cField::CheckDirKey (WPARAM wP,int Seite,BOOL keyToUse)
  {
  BOOL res = TRUE ;
  int d,ol,l,x,y,Format,Modify,al;
  HDC hDC;
  BOOL ShiftIsDown = FALSE;
  BOOL ItIsAnAccelerator = FALSE;
  
  cWord FAR * OldWordWithCaret = act;
  int OldCaretPos = cPos;

  // erst einmal die momentane Position einholen
  hDC = GetFieldDC ();
  GetCaretPos (hDC,x,y,l,Format,Modify);
  RestDC (hDC);

  if (GetKeyState(VK_SHIFT) < 0)
    ShiftIsDown = TRUE;

  if ((wP != VK_UP) && (wP != VK_DOWN))
    xvPos = -1;

  switch (wP) {
    case VK_RIGHT :
      {
      ResetSelState (Seite);
      FieldSelStruct SelStart, SelEnd;
      GetSelectionFromLeftToRight (&SelStart, &SelEnd);  // SelStart < SelEnd
//------------------------------------------------------------------
// Aenderung in Rev.1.42
//------------------------------------------------------------------
//    if ((SelEnd.SelWord != NULL) && (!ShiftIsDown))
//      cPos = SelEnd.CaretPos ;
//    else {
//------------------------------------------------------------------
        if ((Text != NULL) && (Text[cPos])) {
          if (GetKeyState (VK_CONTROL) < 0) {
            cPos = SkipFormat(Text + cPos) - Text;
            cPos = GetNextWordStart (cPos) ;
            SetExistingAct ();
            if ((cPos > WORD(First->Text - Text)) && (cPos == WORD(act->Text - Text)) &&
                    (PrevIsFormatStr (Text + cPos - 1,Text))) {
              // cPos wird auf das Ende des vorigen Wortes gesetzt
              cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
              }
            }
          else {
            cPos = SkipFormat (Text + cPos) - Text;
            if (Is92 (Text,cPos)) cPos += 2 ;
            else                  cPos += 1;
            }
          if ((cPos == 0) || (Text[cPos - 1] == '\r'))
            cPos = SkipFormat (Text + cPos) - Text ;  // In diesem Fall die
                                                      // Formatinfo ueberspringen
          }

//      }

      PosCaret (0, TRUE, FALSE);
      }
      break ;
    case VK_LEFT :
      {
      ResetSelState (Seite);
      FieldSelStruct SelStart, SelEnd;
      GetSelectionFromLeftToRight (&SelStart, &SelEnd);  // SelStart < SelEnd
//------------------------------------------------------------------
// Aenderung in Rev.1.42
//------------------------------------------------------------------
//    if ((SelStart.SelWord != NULL) && (!ShiftIsDown))
//      cPos = SelStart.CaretPos ;
//    else {
//------------------------------------------------------------------
        if ((Text != NULL) && (First != NULL) &&
            (cPos > WORD(First->Text - Text)) &&
            (!IsFirstPrintable(cPos))) {
          if (PrevIsFormatStr (Text + cPos - 1,Text))
            // cPos steht direkt hinter einer Formatierinfo.
            // Die wird mal weggenommen, die zaehlt nicht
            cPos = SkipPrevFormat (Text + cPos - 1) - Text ;

          if (GetKeyState (VK_CONTROL) < 0)
            cPos = GetPrevWordStart (cPos) ;
          else {
            if (Is92Prev (Text,cPos - 1))
              cPos -= 2;
            else
              cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
            }

          SetExistingAct ();
          if ((cPos > WORD(First->Text - Text)) && (cPos == WORD(act->Text - Text)) &&
                  (PrevIsFormatStr (Text + cPos - 1,Text))) {
            // cPos wird auf das Ende des vorigen Wortes gesetzt, damit es von 
            // diesem das Format erbt
            cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
            }
          if ((cPos == 0) || (Text[cPos - 1] == '\r')) {
            // In diesem Fall auf den Start des Wortes setzen, damit die
            // Formatinfo vom Wort des Zeilenstartes geerbt wird
            cPos = SkipFormat (Text + cPos) - Text ;  
            }
          }
//      }

      PosCaret (0, TRUE, FALSE);
      }
      break ;
    case VK_HOME :
      ResetSelState (Seite);
      if ((Text != NULL) && (cPos > 0)) {
        if (GetKeyState (VK_CONTROL) < 0) {
          cPos = SkipFormat(Text) - Text;
          }
        else {
          SetExistingAct ();
          cPos = GetLineStart () -> wOffs ();
          }
        SetExistingAct ();
        if ((cPos > WORD(First->Text - Text)) && (cPos == WORD(act->Text - Text)) &&
                (PrevIsFormatStr (Text + cPos - 1,Text))) {
          // cPos wird auf das Ende des vorigen Wortes gesetzt
          cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
          }
        if ((cPos == 0) || (Text[cPos - 1] == '\r'))
          cPos = SkipFormat (Text + cPos) - Text ;  // Harter Zeilenumbruch: In diesem Fall die
                                                    // Formatinfo ueberspringen
        PosCaret (0, TRUE, FALSE);
        }
      break ;
    case VK_DELETE :
      {
      int letzteSeite;
      if (cfBtn.MyField == this) letzteSeite = LastPage();
      ResetSelState (Seite);
      ResetActFormats ();
      if (!(GetKeyState(VK_SHIFT) < 0)) {
        if (AlreadySelected)
          res = FALSE;
        else {  
          if ((Text != NULL) && (TestChar (wP,TRUE,TRUE))) {
            DelChar (FALSE,TRUE);   // DelUnder = TRUE
            if (cfb != NULL)
              (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
            }
          }  
        }
      if (cfBtn.MyField == this) {
        if (LastPage() != letzteSeite) {
          cfBtn.OnMapChange(this);
          Invalidate (Seite,TRUE);
          }
        }
      }
      break ;
    
    case VK_END :
      ResetSelState (Seite);
      if ((Text != NULL) && (Text[cPos])) {
        if (GetKeyState (VK_CONTROL) < 0) {
          cWord FAR *last = GetLast ();
          cPos = last->Text + last->AnzChars - Text ;
          }
        else {
          SetExistingAct ();
          cWord FAR *h = GetLineEnd (act,NULL);  // das letzte Wort einer Zeile
          if (Is92 (h->Text,0))
            cPos = 2 + h->wOffs () - 1;
          else
            cPos = h->AnzChars + h->wOffs () - 1;  // Offset des letzten Wortes + WortLanege
          if (h->Next == NULL)
            if (cPos >= 0) cPos += 1;
          }
        PosCaret (0, TRUE, FALSE);
        }
      break ;
    case VK_DOWN :
      d = +1;
    case VK_UP :
      ResetSelState (Seite);
      if (wP == VK_UP) d = -1 ;
      hDC = GetFieldDC ();
      GetCaretPos (hDC,x,y,l,Format,Modify);
      ol = l;
      al = GetAnzLines () - 1;
      l = min (max (0,l+d),al);
      if (xvPos >= 0) x = xvPos;
      xvPos = x ;
      if (l != ol) {                // andere Zeile?
        SetCaretInLine (hDC,l,x);   // setze das Caret in Zeile l, womoeglich an x
        RestDC (hDC);
        PosCaret (0, TRUE, FALSE);
        break ;
        }
      else
        RestDC (hDC);
      break ;

#if(WINVER >= 0x0400)
    // diese abartigen Windows95 Tastaturen
    case VK_LWIN:
    case VK_RWIN:
    case VK_APPS:
#endif
    case VK_MENU:
    case VK_CAPITAL:
    case VK_NUMLOCK:
    case VK_SCROLL:
    case VK_PRINT:
    case VK_INSERT:
    case VK_PAUSE:
    case VK_SHIFT:
      res = FALSE;
      break ;

    case VK_CONTROL:
      res = FALSE;
      ShiftIsDown = TRUE;
      break;

    // der Tabulator wird zum Zeichnen nicht beruecksichtigt!
    case VK_RETURN:
      {
      res = FALSE ;
      if (GetKeyState(VK_CONTROL) < 0) {
        OnChar (wP,Seite);
        break;
        }
      else  
        if (GetAnzLines() > 1)
          break;
      }

    case VK_BACK :
      res = FALSE ;
      break ;

    case VK_TAB:
    case VK_ESCAPE:
      res = FALSE;
      AlreadySelected = FALSE;
      break;

    default :
      //--------------------------------------------------------------
      // alle alphanumerischen Tasten und der numerische Ziffernblock
      // sind als Eingaben zu betrachten!! Sollte aber ein CONTROL
      // im Spiel sein, koennte es sich um einen Accelerator handeln.
      //--------------------------------------------------------------
      if (((wP > VK_HELP) && (wP <= VK_DIVIDE)) || (wP == VK_SPACE)) {
        if (!(GetKeyState(VK_CONTROL) < 0))
          res = FALSE ;
        else
          ItIsAnAccelerator = TRUE;
        }
          
    }

  if (res && ShiftIsDown) {   // Cursortaste und SHIFT
    if (!AlreadySelected) {   // noch keine Selektion
      StartSel.SelWord = EndSel.SelWord = OldWordWithCaret;   // Start festlegen
      StartSel.CaretPos = EndSel.CaretPos = OldCaretPos;
      StartSel.xPos = EndSel.xPos = x - x0;
      AlreadySelected = (StartSel.SelWord != NULL);
      }
    if (AlreadySelected) {
      if (int(cPos) != OldCaretPos) {   // Position geaendert?
        InvalidateWordRange (OldWordWithCaret, act);  // invalidieren

        hDC = GetFieldDC ();

        GetCaretPos (hDC,x,y,l,Format,Modify);
        RestDC (hDC);

        EndSel.SelWord = act;                  // Ende festlegen
        EndSel.CaretPos = cPos;
        EndSel.xPos = x - x0;
        }
      }
    }  
  else {                      // keine Cursortaste oder kein SHIFT
    if (AlreadySelected) {    
      if (!res) {
#ifdef UEBERLEGT
        if (((fieldMode & FM_DECIMAL) == FM_DECIMAL) || (wP == VK_DELETE)) {
#endif
          //------------------------------------------------------------
          // alle momentan selektierten Zeichen werden bei Eingabe eines 
          // neuen Zeichens geloescht
          //------------------------------------------------------------
          if ((wP != VK_SHIFT) && (wP != VK_MENU) && (wP != VK_CONTROL) && 
              (wP != VK_CAPITAL) && (wP != VK_NUMLOCK) && (wP != VK_SCROLL) &&
              (wP != VK_PRINT) && (wP != VK_INSERT) && (wP != VK_PAUSE) &&
#if(WINVER >= 0x0400)
              (wP != VK_LWIN) && (wP != VK_RWIN) && (wP != VK_APPS) &&
#endif
              keyToUse) {
            DeleteSelectedLines();
            if (cfb != NULL)
              (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
            }
#ifdef UEBERLEGT
          }
#endif
        }
      //-----------------------------------------------------------
      // Bei Accelerator-Tasten soll lieber nichts gemacht werden.
      //-----------------------------------------------------------
      else if (!ItIsAnAccelerator) {
        InvalidateSelectedWords ();
        ClearSelection();
        }
      }
    }  

  if (res) ResetActFormats ();
  return res ;
  }

void cField::ChangeWordPtr (LPSTR nTxt,LPSTR oTxt,int ds,BOOL FAR &formatAll)
  {
  formatAll = FALSE ;
  for (cWord FAR *h = First; h != NULL ; h = h->Next) {
    int Offs = h->Text - oTxt;
    if (Offs > int (cPos)) Offs += ds;
    if (Offs >= 0) {
      h->Text = nTxt + Offs;
      h->WordType = h->GetWordType(h->Text);
      }
    else formatAll = TRUE ;
    }
  }

void cField::ChangeWordPtrFrom (LPSTR nTxt,LPSTR oTxt,int ds,int from)
  {
  for (cWord FAR *h = First; h != NULL ; h = h->Next) {
    int Offs = h->Text - oTxt;
    if (Offs > from) Offs -= ds;
    if (Offs < 0) Offs = 0 ;
    h->Text = nTxt + Offs;
    }
  if (int (cPos) > from) {
    cPos -= ds ;
    }
  if (SaveStart.CaretPos > from) {
    SaveStart.CaretPos -= ds ;
    if (SaveStart.CaretPos < 0) SaveStart.CaretPos = 0 ;
    }
  if (SaveEnd.CaretPos > from) {
    SaveEnd.CaretPos -= ds ;
    if (SaveEnd.CaretPos < 0) SaveEnd.CaretPos = 0 ;
    }
  }

//---------------------------------------------------------------------------
// Fuegt an der Cursorposition im aktuellen Text die Zeichenfolge <str> ein.
// Das Ergebnis wird in <res>, welches hier alloziert wird, zurueckgegeben.
//---------------------------------------------------------------------------
void cField::InsertStr (LPSTR FAR &res,LPSTR str)
  {
  BOOL doIt = TRUE ;
  if (IsIndexedText (cPos)) {
    WORD cStart;
    if (IsFirstOfIndex(cPos,cStart)) {
      cPos = cStart;
      }
    else
      doIt = FALSE ;
    }

  if (doIt) {
    SetActToCaret ();          // Liefert das Wort in dem das Caret steht
    WORD nlen = lstrlen (str);
    if (Text != NULL) {        // Klassenvariable <Text>
      WORD olen;
      res = LPSTR (GetGlobMem ((olen = lstrlen(Text) + 1) + nlen));
      lmemcpy (res,Text,cPos);        // Text bis zum Cursor einfuegen
      lmemcpy (res + cPos,str,nlen);  // die neuen Zeichen einfuegen
      lmemcpy (res + cPos + nlen,Text + cPos,olen - cPos);  // der Rest
      }
    else {
      cPos = 0 ;
      res = LPSTR (GetGlobMem (nlen + 1));
      lmemcpy (res,str,nlen+1);
      }
    }
  else
    MessageBeep (0);
  }

BOOL cField::actIsValid ()
  {
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if (act == h) return TRUE ;
    }
  return FALSE ;
  }

void cField::InsertStr (LPSTR str)
  {
  SaveOld ();
  BOOL doIt = TRUE ;
  if (IsIndexedText (cPos)) {
    WORD cStart;
    if (IsFirstOfIndex(cPos,cStart)) {
      cPos = cStart;
      }
    else
      doIt = FALSE ;
    }

  if (doIt) {
    WORD nlen = lstrlen (str);
    
    // Ein Feld dessen erstes Zeichen gross geschrieben wird, wandelt an der
    // Cursorposition 0 das erste Zeichen in Grossbuchstaben um.
    if ((cPos == 0) && (fieldMode & FM_FIRSTCHARBIG) && 
        ((nlen == 1) ||                         // nur ein einzelnes Zeichen einfuegen
         (fieldMode & FM_NOGERMANCHARS)))       // oder Umlaute sind erlaubt
      AnsiUpperBuff (str,1);

    if (fieldMode & FM_UPPERCHAR)
      AnsiUpperBuff (str, (UINT)lstrlen(str));

    if (Text) {
      WORD olen;
      LPSTR nTxt = LPSTR (GetGlobMem ((olen = lstrlen(Text) + 1) + nlen));
      lmemcpy (nTxt,Text,cPos);
      lmemcpy (nTxt + cPos,str,nlen);
      lmemcpy (nTxt + cPos + nlen,Text + cPos,olen - cPos);
      BOOL formatAll;
      ChangeWordPtr (nTxt,Text,nlen,formatAll);
      FreeGlobMem (Text);
      Text = nTxt;
        
      if (cPos != 0)
        SetExistingAct ();
      else
        act = First;

      BOOL tested = FALSE;
      WORD nPos;
      if (IsWordEndChar(*str)) {
        tested = TestWord (cPos - 1,nPos,CPOS_GETEND);
        if (tested) nPos += 1;  // hinter das Trennzeichen !!!
        tested = tested || TestWord (cPos + 1,nPos,CPOS_GETBEG);
        }
      else {
        tested = TestWord (cPos,nPos,CPOS_GETEND);
        }

      if (tested) cPos = nPos;
      else        cPos = cPos + nlen ;
      if ((cPos > 0) && (PrevIsFormatStr (Text + cPos - 1,Text))) {
        LPSTR nCaretText = SkipPrevFormat (Text + cPos - 1) ; // Vor die Formatierinfo
                                                              // setzten
        if (nCaretText != Text) 
          cPos = nCaretText - Text ;
        }

      if (!actIsValid())
        act = First;
      }
    else {
      cPos = nlen ;
      Text = LPSTR (GetGlobMem (nlen + 1));
      lmemcpy (Text,str,nlen+1);
      }
    RemoveNotNeededFormats ();
    ReformatAct ();
    PosCaret ();
    }
  else
    MessageBeep (0);
  }

void cField::InvalidateWord (cWord FAR *h,HDC FAR &hDC,HFONT FAR *OldFont)
  {
  if (hDC == 0) 
    hDC = GetFieldDC (h->wFormat,h->wModify,OldFont)  ;
  else          
    ModifyDC (hDC,h->wFormat,h->wModify,OldFont,TRUE) ;

  h->Invalidate (hDC);
  }

//----------------------------------------------------------------------------
// loescht aus dem Text oTxt die Woerter von nPos bis ePos
//----------------------------------------------------------------------------
void cField::DelWordPtr (WORD nPos, WORD ePos, LPSTR oTxt)
  {
  cWord FAR *prev = NULL ;
  HDC hDC = 0;
  HFONT OldFont = 0;
  BOOL firstInvalidate = TRUE;

  for (cWord FAR *h = First ; h != NULL ; ) {
    cWord FAR *n = h->Next ;
    if ((h->Text >= oTxt + nPos) && 
         (h->Text + h->AnzChars <= oTxt + ePos)) {
      if (prev != NULL) {      // nicht das erste Wort
        prev->Next = h->Next;
        if (prev->Next != NULL)
          prev->Next->Prev = prev;
        }
      else {                   // das erste Wort
        First = h->Next;
        if (First != NULL)
          First->Prev = NULL ;
        }

      HFONT MyOldFont = 0;
      InvalidateWord (h,hDC,&MyOldFont);
      if (firstInvalidate) {
        OldFont = MyOldFont;
        firstInvalidate = FALSE;
        }
      delete h;
      if (act == h) act = prev;
      }
    else
      prev = h;
    h = n;                    // naechstes Wort
    }

  if (hDC != 0) {
    if (OldFont)
      SelectObject(hDC,OldFont);
    RestDC (hDC);
    }
  }

int FormatSize (LPSTR FormatStart)
  {
  LPSTR t = FormatStart + 1 ;
  for (int fs = 1 ; ((*t) && (*t != '\\')) ; t ++ , fs ++ ) ;
  return (*t) ? fs + 1 : fs ;
  }

LPSTR cField::RemoveFormatFromText (LPSTR pToCorr,LPSTR FormatStart,int fs,LPSTR FAR &pToCorr1,LPSTR FAR &pToCorr2,LPSTR FAR &Text,BOOL mitFeld)
  {
  int nSize = GetBlockSize (Text) - fs;
  LPSTR oTxt = Text ;
  int oOffs = FormatStart - Text ;
  int cOffs = pToCorr - Text ;
  int cOffs1,cOffs2 ;
  if (pToCorr1 != NULL)
    cOffs1 = pToCorr1 - Text ;
  if (pToCorr2 != NULL)
    cOffs2 = pToCorr2 - Text ;
  Text = LPSTR (GetGlobMem (nSize)) ;
  if (oOffs > 0)
    lmemcpy (Text,oTxt,oOffs) ;
  if ((nSize - oOffs) > 0)
    lmemcpy (Text + oOffs,oTxt + oOffs + fs,nSize - oOffs);
  if (mitFeld)
    ChangeWordPtrFrom (Text,oTxt,fs,oOffs);
  if (cOffs > oOffs)
    cOffs -= fs ;
  if (cOffs1 > oOffs)
    cOffs1 -= fs ;
  if (cOffs2 > oOffs)
    cOffs2 -= fs ;
  FreeGlobMem (oTxt);
  if (pToCorr1 != NULL)
    pToCorr1 = Text + cOffs1 ;
  if (pToCorr2 != NULL)
    pToCorr2 = Text + cOffs2 ;
  return Text + cOffs ;
  }
LPSTR cField::RemoveFormat (LPSTR pToCorr,LPSTR FormatStart,LPSTR FAR &pToCorr1,LPSTR FAR &pToCorr2,LPSTR FAR &Text,BOOL mitFeld)
  {
  return RemoveFormatFromText (pToCorr,FormatStart,FormatSize(FormatStart),pToCorr1,pToCorr2,Text,mitFeld);
  }
LPSTR cField::RemoveColor (LPSTR pToCorr,LPSTR ColorStart,LPSTR FAR &pToCorr1,LPSTR FAR &pToCorr2,LPSTR FAR &Text,BOOL mitFeld)
  {
  return RemoveFormatFromText (pToCorr,ColorStart,FormatSize(ColorStart),pToCorr1,pToCorr2,Text,mitFeld);
  }
LPSTR cField::RemoveModify (LPSTR pToCorr,LPSTR ModifyStart,LPSTR FAR &pToCorr1,LPSTR FAR &pToCorr2,LPSTR FAR &Text,BOOL mitFeld)
  {
  return RemoveFormatFromText (pToCorr,ModifyStart,3,pToCorr1,pToCorr2,Text,mitFeld);
  }
extern WORD ModifyNum (char m);
extern int InterpreteFormat (LPSTR FAR *h);
extern DWORD InterpreteColor (LPSTR FAR *h);
void cField::RemoveNotNeededFormats (LPSTR FAR &Text,BOOL mitFeld)
  {
  BOOL ready = FALSE ;
  LPSTR FormatStart = NULL ;
  LPSTR ModifyStart = NULL ;
  LPSTR ColorStart = NULL ;
  BOOL ThereIsAString = FALSE ;
  WORD actModify = DefModify() ;
  WORD actFormat = DefFormat ;
  DWORD actColor = 0xFFFFFFFF ;
  WORD oldModify ;
  WORD oldFormat ;
  DWORD oldColor ;
  for ( LPSTR h = Text ; !ready ; ) {
    if (*h == '\0')
      ready = TRUE ;
    else if (*h == '\\') {
      if (h[1] == 'f') {
        if (FormatStart != NULL) {
          h = RemoveFormat (h,FormatStart,ModifyStart,ColorStart,Text,mitFeld);
          actFormat = oldFormat ;
          }
        FormatStart = h ;
        LPSTR finfo = h + 2 ;
        WORD newFormat = InterpreteFormat (&finfo);
        for ( ++ h ; ((*h) && (*h != '\\')) ; h ++ ) ;
        if (*h) h ++ ;
        if (newFormat == actFormat) {
          // Der kann getrost geschmissen werden
          h = RemoveFormat (h,FormatStart,ModifyStart,ColorStart,Text,mitFeld);
          FormatStart = NULL ;
          }
        else {
          oldFormat = actFormat ;   // Den Formatwert speichern, da dieser geloescht werden koennte
          actFormat = newFormat ;
          }
        }
      else if (h[1] == 'c') {
        if (ColorStart != NULL) {
          h = RemoveColor (h,ColorStart,ModifyStart,FormatStart,Text,mitFeld);
          actColor = oldColor ;
          }
        ColorStart = h ;
        LPSTR finfo = h + 3 ;
        DWORD newColor = InterpreteColor (&finfo);
        for ( ++ h ; ((*h) && (*h != '\\')) ; h ++ ) ;
        if (*h) h ++ ;
        if (newColor == actColor) {
          // Der kann getrost geschmissen werden
          h = RemoveColor (h,ColorStart,ModifyStart,FormatStart,Text,mitFeld);
          ColorStart = NULL ;
          }
        else {
          oldColor = actColor ;
          actColor = newColor ;
          }
        }
      else if (h[1] == 'm') {
        if (ModifyStart != NULL) {
          h = RemoveModify (h,ModifyStart,FormatStart,ColorStart,Text,mitFeld);
          actModify = oldModify ;
          }
        ModifyStart = h ;
        h += 3 ;
        WORD newModify = ModifyNum (ModifyStart[2]);
        if (newModify == actModify) {
          // Der kann getrost geschmissen werden
          h = RemoveModify (h,ModifyStart,FormatStart,ColorStart,Text,mitFeld);
          ModifyStart = NULL ;
          }
        else {
          oldModify = actModify ;   // Den Modifywert speichern, da dieser geloescht werden koennte
          actModify = newModify ;
          }
        }
      else if (h[1] == '\\') {
        ThereIsAString = TRUE ;
        FormatStart = NULL ;
        ModifyStart = NULL ;
        h += 2 ;
        }
      else if (h[1] == 'i') {
        h = Text + SkipIndexed (h - Text) ;
        FormatStart = NULL ;
        ModifyStart = NULL ;
        ThereIsAString = TRUE ;
        }
      else if ((h[1] == 'h') || (h[1] == 'e') || (h[1] == 'z')) {
        h = SkipFormat (h) ;
        FormatStart = NULL ;
        ModifyStart = NULL ;
        ThereIsAString = TRUE ;
        }
      else {
        // WIN_ASSERT (FALSE);
        *h = '_';
        }
      }
    else {
      FormatStart = NULL ;
      ColorStart = NULL ;
      if (*h != '\r') {
        ModifyStart = NULL ;
        }
      h ++ ;
      ThereIsAString = TRUE ;
      }
    }
  if (FormatStart != NULL) {
    RemoveFormat (h,FormatStart,ModifyStart,ColorStart,Text,mitFeld);
    FormatStart = NULL ;
    }
  if (ModifyStart != NULL) {
    RemoveModify (h,ModifyStart,FormatStart,ColorStart,Text,mitFeld);
    }
  if (ColorStart != NULL) {
    RemoveColor (h,ColorStart,ModifyStart,FormatStart,Text,mitFeld);
    }
  if ((!ThereIsAString) && (*Text)) {
    // Alles wegschmeissen
    cPos = 0 ;
    ResetWords ();
    FreeGlobMem (Text) ;
    Text = LPSTR(GetGlobMem (1)) ;
    }
  }

//----------------------------------------------------------------------------
// bei BACKSPACE ist delUnder FALSE, bei DELETE ist delUnder TRUE
void cField::DelChar (BOOL wholeWord,BOOL delUnder) 
  {
  SaveOld ();
  WORD nPos,ePos;
  WORD oPos = cPos;
  BOOL IsIndexed = FALSE;
  if ((Text != NULL) &&
      (((cPos > 0) && (!delUnder)) ||      // BACKSPACE
       ((Text[cPos]) && (delUnder)))) {    // DELETE
    if (delUnder) {
      cPos = SkipFormat (Text + cPos) - Text ;
      if (Is92 (Text,cPos)) {
        nPos = cPos ;
        cPos += 2 ; 
        ePos = cPos ;
        IsIndexed = FALSE;
        }
      else if (Text[cPos]) {
        nPos = cPos ;
        cPos ++ ;
        IsIndexed = IsIndexedText (nPos);
        ePos = cPos;
        }
      else
        nPos = ePos = cPos ;
      }
    else {
      WORD cStart;
      if (wholeWord) {
        IsIndexed = IsIndexedText (cPos);
        if ((cPos > 0) && 
               (!IsFirstPrintable(cPos)) &&
               ((!IsIndexed) || (IsFirstOfIndex(cPos,cStart)))
           ) {
          IsIndexed = FALSE ;
          if (PrevIsFormatStr (Text + cPos - 1,Text))
            // cPos steht direkt hinter einer Formatierinfo. 
            // Die wird mal weggenommen, die zaehlt nicht
            cPos = SkipPrevFormat (Text + cPos - 1) - Text ;

          SetExistingAct ();
          if (cPos > 0) {
            nPos = GetPrevWordStart (cPos);
            ePos = cPos ;
            }
          else 
            nPos = ePos = cPos ;

          // Untersuchung, ob Anfang nicht in einem schreibgeschuetzten Teil liegt
          ////////////////////////////////////////////////////////////////////////
          if (IsIndexedText (nPos)) IsIndexed = TRUE ;
          }
        else
          ePos = nPos = cPos;   // Nichts loeschen bitte
        }
      else {
        if (PrevIsFormatStr (Text + cPos - 1,Text))
          // cPos steht direkt hinter einer Formatierinfo. 
          // Die wird mal weggenommen, die zaehlt nicht
          cPos = SkipPrevFormat (Text + cPos - 1) - Text ;
        SetExistingAct ();
        if (cPos > 0) {
          if (Is92Prev (Text,cPos - 1)) nPos = cPos - 2 ;
          else                          nPos = cPos - 1 ;
          ePos = cPos ;
          }
        else
          nPos = ePos = cPos ;
        IsIndexed = IsIndexedText (nPos);
        }
      if (IsIndexed) {
        if (IsFirstOfIndex(cPos,cStart)) {
          IsIndexed = FALSE ;
          ePos = nPos;
          }
        }
      }
    // nPos zeigt auf das Zeichen des geloescht werden soll
    if ((!IsIndexed) && (ePos > nPos)) {
      DeleteTextOut (GetPrev (act),nPos,ePos);
      }
    else if ((IsIndexed) && (AskForWordDel ())) {
      WORD Index;
      GetWordBeg_End (nPos,nPos,ePos,Index);
      WORD olen;
      int dl = ePos - nPos ;
      LPSTR nTxt = LPSTR (GetGlobMem ((olen = lstrlen(Text) + 1) - dl));
      lmemcpy (nTxt,Text,nPos);
      lmemcpy (nTxt + nPos,Text + nPos + dl,olen - nPos - dl);
      LPSTR oText = Text ;
      FreeGlobMem (Text);
      Text = nTxt;
      cPos = nPos ;
      DelWordPtr (nPos,ePos,oText);
      BOOL formatAll;
      ChangeWordPtr (nTxt,oText,-dl,formatAll);
      RemoveNotNeededFormats ();
      if (formatAll)
        act = First;
      else
        SetActToCaret ();
      ReformatAct () ;
      PosCaret ();
      if (cfb != NULL)
        (* cfb) (CALLBACKCMD_INDEXDEL,&Index,CallBackMem);
      }
    else {
      cPos = oPos;
      MessageBeep (0);
      }
    }
  else {
    MessageBeep (0);
    }
  }

DLLExport void _export WINAPI cField::InstallCallBack (CFIELDCALLBACK cfbfunc,LPVOID param,int size)
  {
  CallBackMem = GetGlobMem (size);
  lmemcpy (CallBackMem,param,size);
  cfb = cfbfunc;
  RefWnd = CalcFontRefWnd();
  }

void cField::CheckScroll (int Seite,BOOL checkAlways)
  {
  if ((cfb != NULL) && ((oldCaretHeight > 0) || (checkAlways))) {
    HDC hDC = GetFieldDC ();
    if (First == NULL) Reformat (hDC);
    int x,y,l,f,m;
    GetCaretPos (hDC,x,y,l,f,m,checkAlways);
    int h = GetCaretHeight (hDC,f);
    toDPKoords (hDC,x,y);
    RestDC (hDC);
    RECT r;
    GetClientRect (Wnd,&r);
    int da = GetSystemMetrics (SM_CXHSCROLL);
    if ((fieldMode & FM_SINGLELINE) == FM_SINGLELINE)
      da = 1;   // Platz fuer Scroll muss nicht geschaffen werden
    else
      da = GetSystemMetrics (SM_CXHSCROLL);
    InflateRect (&r,-da,-da);
    int dx,dy;

    if (x < r.left)        dx = x - r.left ;
    else if (x > r.right)  dx = x - r.right ;
    else                   dx = 0 ;

    if (y < r.top) {
      dy = y - r.top ;
      }
    else if (y + h > r.bottom) {
      dy = y + h - r.bottom ;
      if (y - dy < r.top)
        dy += y - dy - r.top ;
      }
    else                  dy = 0 ;

    int neueSeite;
    if (act != NULL) {
      if ((yPageMax > 0) && (act->Next == NULL) && 
          (cPos >= WORD (act->wOffs() + act->AnzChars)) &&
          (act->WordType == WORDTYPE_CR) && 
          (act->yPos - act->yBaseHeight + y0 + 2 * act->yHeight > yPageMax))   // Auf die naechste Seite 
                                                        // obwohl kein Wort direkt auf diese faellt
        neueSeite = ErsteSeite + act->RelativSeite + 1 ;
      else
        neueSeite = ErsteSeite + act->RelativSeite ;
      }
    else
      neueSeite = ErsteSeite ;

    if ((dx != 0) || (dy != 0) || (neueSeite != Seite)) {
      NeedScroll_Info nsi;
      nsi.pt.x = dx ;
      nsi.pt.y = dy ;
      nsi.Seite = neueSeite ;
      (* cfb) (CALLBACKCMD_NEEDSCROLL,&nsi,CallBackMem);
      }
    }
  }

DLLExport _export WINAPI cField::~cField ()
  {
  if (Text != NULL) {
    FreeGlobMem (Text);
    Text = NULL;
    }
  if (CallBackMem != NULL)
    FreeGlobMem (CallBackMem);
  cWord FAR *h,FAR *hn;
  for (h = First ; h != NULL ; h = hn) {
    hn = h->Next ;
    delete h ;
    }
  if (ActiveField == this) {
    ReleaseCaret ();
    _startFormat[0] = _endFormat[0] = _startColor[0] = _endColor[0] = '\0';
    ActiveField = NULL;
    }
  if (SavecField == this) {
    _startFormat[0] = _endFormat[0] = _startColor[0] = _endColor[0] = '\0';
    }
  if (FormatMaps != NULL)
    FreeGlobMem (FormatMaps);
  }

int cField::GetIndexedLength (LPSTR h)
  {
  for ( ; ((*h) && (*h != 'L')) ; h++) ;
  h++ ;
  int res = 0 ;
  for ( ; ((*h) && (!IsFormatStr(h))) ; h ++)
    res = res * 10 + *h - '0' ;
  return res;
  }

BOOL IsFromFormat (LPSTR Text,int i)
  {
  for ( i -- ; i >= 0 ; i--) {
    if ((Text[i] == '\\') && (Text[i+1] == 'f')) return TRUE ;
    }
  return FALSE ;
  }

BOOL cField::IsIndexedText (WORD cP)
  {
#ifdef UEBERLEGT
  if (Text == NULL) return FALSE ;
  int i = min(cP,lstrlen(Text)) ;
  BOOL res = FALSE ;
  BOOL ready = FALSE ;
  for ( ; ((i >= 0) && (!ready)) ; i--) {
    WIN_ASSERT_TEXT((lstrlen(Text) >= i),Text);
    if ((Text[i] == '\\') && (Text[i+1] == 'i') && (Text[i+2] == ':') && (!IsFromFormat(Text,i))) {
      ready = TRUE ;
      int length = GetIndexedLength (Text + i) ;
      res =  (int(i + length) > int (cP)) ;
      }
    }
  return res;
#else
  return FALSE ;
#endif
  }

BOOL cField::IsFirstOfIndex (WORD cP,WORD FAR &cStart)
  {
  if (Text == NULL) return FALSE ;
  BOOL res = FALSE ;
  int i = cP ;
  BOOL ready = FALSE ;
  for ( ; ((i >= 0) && (!ready)) ; i--) {
    if ((Text[i] == '\\') && (Text[i+1] == 'i') && (Text[i+2] == ':') && (!IsFromFormat(Text,i))) {
      ready = TRUE ;
      cStart = i ;
      if (cP == WORD(SkipFormat (Text + i) - Text)) {
        res = TRUE ;
        }
      }
    }

  return res;
  }

WORD cField::SkipIndexed (WORD nP)
  {
  WORD cStart;
  IsFirstOfIndex (nP,cStart);
  int length = GetIndexedLength (Text + cStart);
  return cStart + length;
  }

BOOL cField::AskForWordDel ()
  {
  return TRUE ;
  }

WORD GetHexDigit (LPSTR h)
  {
  WORD res = 0;
  for ( ; ; h++) {
    if ((*h >= '0') && (*h <= '9'))
      res = res * 16 + *h - '0' ;
    else if ((*h >= 'A') && (*h <= 'F'))
      res = res * 16 + *h - 'A' + 0x0A ;
    else if ((*h >= 'a') && (*h <= 'f'))
      res = res * 16 + *h - 'a' + 0x0A ;
    else break ;
    }
  return res;
  }

WORD cField::GetIndex (LPSTR Text)
  {
  for ( ; ((*Text) && (*Text != ':')) ; Text ++) ;
  return GetHexDigit (++Text);
  }

void cField::GetWordBeg_End (WORD cP,WORD FAR &beg,WORD FAR &end,WORD FAR &Index)
  {
  if (Text == NULL) return ;
  int i = cP ;
  BOOL res = FALSE ;
  BOOL ready = FALSE ;
  for ( ; ((i >= 0) && (!ready)) ; i--) {
    if ((Text[i] == '\\') && (Text[i+1] == 'i') && (Text[i+2])) {
      ready = TRUE;
      beg = i;
      WORD e1 = beg + GetIndexedLength (Text + i);
      if (end < e1) end = e1;
      Index = GetIndex (Text + beg);
      }
    }
  }

BOOL cField::IsWordEndChar (WPARAM wP)
  {
  return ((wP == '\r') || (wP == '\t') || (wP == ' ') || 
          (wP == '.') || (wP == ',') || (wP == ';') || 
          (wP == ':') || // (wP == '"') || (wP == '\'') || 
          (wP == CODE_HIDDENKEY) ||
          (wP == '-') || (wP == '\0') || (wP == '\\'));
  }

TWI FAR *cField::GetWord(WORD cP,WORD FAR &beg,WORD FAR &end,BOOL allowend)
  {
  if (Text == NULL) return NULL;
  for (int i = int (cP); i >= 0 ; i--) {
    if (IsWordEndChar (*(Text+i))) break;
    }
  beg = i+1;
  if (IsIndexedText(beg))
    beg = SkipIndexed (beg);

  for (i = int (cP) ; Text[i] ; i++) {
    if (IsWordEndChar (*(Text+i))) break;
    }
  end = i;
  LPTWI res ;
  BOOL testEnd = Text[end] || allowend;
  if ((end > beg) && (testEnd)) {
    res = LPTWI (GetGlobMem (end - beg + sizeof(*res)));
    lmemcpy (res->Text,Text+beg,end - beg);
    res->Text[end - beg] = '\0';
    res->res = FALSE ;
    res->Index = 0xFFFF;
    res->Format = 0xFFFF;
    res->Modify = DefModify();
    res->resWord = NULL;
    res->IsFirst = (WORD (SkipFormat (Text) - Text) == beg);
    res->IsLast = (*(SkipFormat (Text + end)) == '\0') ;
    }
  else res = NULL ;
  
  return res;
  }

LPSTR cField::GetIndexPref (LPTWI r,int FAR &Indl)
  {
  LPSTR res;
  if (r->Index != 0xFFFF) {
    char nmbr[20];
    int i = sizeof(nmbr) - 2 ;
    nmbr[sizeof(nmbr)-1] = '\0';
    if (r->Index != 0) {
      for (WORD h = r->Index ; h ; ) {
        int x = h % 16 ;
        nmbr[i--] = (x < 10) ? (x + '0') : (x - 10 + 'A');
        h /= 16 ;
        }
      }
    else
      nmbr[i--] = '0' ;
    res = LPSTR (GetGlobMem ((Indl = 3 + sizeof(nmbr) - 2 - i) + 1));
    lstrcpy (res,"\\i:");
    lstrcat (res + 3,nmbr+i+1);
    }
  else {
    Indl = 0;
    res = NULL ;
    }
  return res;
  }

LPSTR cField::GetIndexMod0 (LPTWI r,int FAR &m0l)
  {
  LPSTR res;
  if (r->Modify) {
    res = LPSTR (GetGlobMem (4));
    lstrcpy (res,"\\m");
    res[2] = char(r->Modify) + '0' ;
    m0l = 3 ;
    }
  else {
    res = NULL ;
    m0l = 0 ;
    }
  return res;
  }

LPSTR cField::GetIndexMod1 (LPTWI r,int FAR &m1l)
  {
  LPSTR res;
  if (r->Modify) {
    res = LPSTR (GetGlobMem (4));
    lstrcpy (res,"\\m0");
    m1l = 3 ;
    }
  else {
    res = NULL ;
    m1l = 0 ;
    }
  return res;
  }
  
LPSTR cField::GetIndexLength (LPTWI r,int FAR &Ll,int gl)
  {
  LPSTR res;
  if (r->Index != 0xFFFF) {
    int p;
    if (gl <= 6) p = 1;
    else if (gl <= 95) p = 2;
    else p = 3;
    char num[5];
    num[4] = '\0';
    int i = 3;
    int x = gl + p + 2;
    for ( ; x ; ) {
      num[i--] = x % 10 + '0';
      x /= 10;
      }
    res = LPSTR (GetGlobMem (p + 3));
    res[0] = 'L' ;
    lstrcat (res,num+i+1);
    lstrcat (res,"\\");
    Ll = p + 2;
    }
  else {
    res = NULL ;
    Ll = 0;
    }
  return res;
  }

BOOL cField::TestWord (int tPos,WORD FAR &nPos,WORD mode)
  {
  if (tPos < 0) tPos = 0;
  WORD beg,end;
  BOOL res = FALSE ;
  TWI FAR *actWord = GetWord (tPos,beg,end);
  if ((actWord != NULL) && (cfb != NULL)) {
    (*cfb) (CALLBACKCMD_TESTWORD,actWord,CallBackMem);
    if (actWord->res) {
      ChangeText (actWord,beg,end,nPos,mode);
      res = TRUE ;
      }
    }
  if (actWord != NULL)
    FreeGlobMem (actWord);
  return res;
  }

BOOL cField::IsFirstPrintable (WORD cP)
  {
  return (WORD (SkipFormat(Text) - Text) == cP);
  }

WORD cField::GetStoredTextLength (LPSTR Text)
  {
  WORD Len = 0;
  int cExtra = 0;
  int mExtra = 0;
  for (LPSTR h = Text ; *h ; ) {
    if ((*h == '\\') && (h[1] == 'i') && (h[2] == ':')) {
      int l = GetIndexedLength (h);
      // WIN_ASSERT ((h + l) < Text + GetBlockSize(Text));
      if ((h + l) < Text + GetBlockSize(Text)) {
        for (int i = 0 ; ((h[i] != 'L') && (h[i])) ; i++) ;
        h += l ;
        Len += i + 1;
        }
      else {
        Len++ ;
        h ++ ;
        }
      }
    else if ((*h == '\\') && ((h[1] == 'f') || (h[1] == 'c'))) {
      // Das Ende der Formatierungssequenz absuchen
      ///////////////////////////////////////////////
      if (h[1] == 'c') {
        if (h[3] != '-') cExtra = 5;
        else             cExtra = 0;
        }
      h += 2 ;
      Len += 2 ;
      for ( ; ((*h != '\\') && (*h)) ; ) {
        h++ ;
        Len ++ ;
        }
      if (*h == '\\') {
        h++ ;
        Len ++ ;
        }
      }
    else {
      if ((*h == '\\') && (h[1] == 'm')) {
        if (h[2] != '0') mExtra = 3;
        else             mExtra = 0;
        }
      Len++ ;
      h ++ ;
      }
    }
  return Len + mExtra + cExtra + 1;
  }

// Rausholen der Formatinfo aus einem String ...
//////////////////////////////////////////////////////
DLLExport void _export WINAPI RemoveFormatInfoFrom (LPSTR res,LPSTR Text)
  {
  LPSTR h1 = Text;
  LPSTR h2 = res;
  int state = 0;
  for ( ; *h1 ; ) {
    switch (state) {
      case 0 :
        if ((h1[0] == '\\') && (IsValidEscape (h1[1]))) {
          state = 1 ;
          h1 ++ ;
          }
        else if ((h1[0] == '\\') && (h1[1] == 'm')) {
          h1 += 3 ;
          }
        else {
          *h2++ = *h1 ++ ;
          }
        break ;
      case 1 :
        if (*h1 == '\\') state = 0;
        h1++ ;
        break ;
      }
    }
  *h2++ = '\0';
  }

void cField::StoreText (LPSTR Text,LPSTR res)
  {
  LPSTR h1 = Text;
  LPSTR h2 = res;
  int state = 0;
  BOOL domOff = FALSE,docOff = FALSE;
  for ( ; *h1 ; ) {
    switch (state) {
      case 0 :
        if ((*h1 == '\\') && (h1[1] == 'i') && (h1[2] == ':')) {
          int l = GetIndexedLength (h1);
          for (int i = 0 ; h1[i] != 'L' ; i++)
            *h2++ = h1[i] ;
          h1 += l ;
          *h2++ = '\\';
          }
        else {
          if ((h1[0] == '\\') && (h1[1] == 'm')) {
            if (h1[2] != '0') domOff = TRUE ;
            else              domOff = FALSE ;
            }
          if ((h1[0] == '\\') && (h1[1] == 'c')) {
            if (h1[3] != '-') docOff = TRUE ;
            else              docOff = FALSE ;
            }
          if ((*h1 == '\\') && (h1[1] != 'm')) state = 1;
          *h2++ = *h1++ ;
          }
        break ;
      case 1 :
        if (*h1 == '\\') state = 0;
        *h2++ = *h1++ ;
        break ;
      }
    }
  if (domOff) lstrcpy (h2,"\\m0") , h2 += 3;
  if (docOff) lstrcpy (h2,"\\c:-\\") , h2 += 5 ;
  *h2++ = '\0';
  }

WORD cField::GetFormatUntil (WORD cP)
  {
  WORD Format = DefFormat;
  for (WORD i = 0 ; i < cP ; ) {
    if ((Text[i] == '\\') && (Text[i+1] == 'f')) {
      i += 3;
      Format = 0;
      for ( ; Text[i] != '\\' ; i++ ) {
        Format = Format * 10 + Text[i] - '0' ;
        }
      i++ ;
      }
    else
      i++;
    }
  return Format;
  }

LPSTR cField::GetFormatPrefix (WORD format,int FAR &fl)
  {
  char num[20];
  num[19] = '\0';
  int x = format;
  int i = 18 ;
  if (x) {
    for ( ; x ; ) {
      num[i--] = x % 10 + '0';
      x /= 10;
      }
    }
  else {
    num[i--] = '0' ;
    }
  LPSTR res = LPSTR (GetGlobMem ((fl = 4 + 18 - i) + 1));
  lstrcpy (res,"\\f:");
  lstrcat (res,num+i+1);
  lstrcat (res,"\\");

  return res;
  }

LPSTR cField::GetIndexForm0 (LPTWI t,int FAR &f0l)
  {
  LPSTR res;
  if (t->Format != 0xFFFF) {
    res = GetFormatPrefix (t->Format,f0l);
    }
  else {
    res = NULL ;
    f0l = 0;
    }
  return res;
  }

LPSTR cField::GetIndexForm1 (LPTWI t,int FAR &f1l,WORD beg)
  {
  LPSTR res;
  if (t->Format != 0xFFFF) {
    res = GetFormatPrefix (GetFormatUntil (beg),f1l);
    }
  else {
    res = NULL ;
    f1l = 0;
    }
  return res;
  }

void cField::ChangeText (LPTWI actWord,WORD beg,WORD end,WORD FAR &nPos,
                         WORD mode)
  {
  int Indl,Lengthl,m0l,m1l,f0l,f1l;
  int olen = end - beg;
  int nlen = lstrlen (actWord->resWord);
  int golen = (Text != NULL) ? lstrlen (Text) : 0;

  // Berechnen der ganzen Teilstrings
  LPSTR Index = GetIndexPref (actWord,Indl);
  LPSTR Mod0 = GetIndexMod0 (actWord,m0l);
  LPSTR Mod1 = GetIndexMod1 (actWord,m1l);
  LPSTR Form0 = GetIndexForm0 (actWord,f0l);
  LPSTR Form1 = GetIndexForm1 (actWord,f1l,beg);
  LPSTR Length = GetIndexLength (actWord,Lengthl,Indl+m0l+m1l+nlen+f0l+f1l);

  int gnlen = golen - olen + nlen + Indl + Lengthl + m0l + m1l + f0l + f1l;
  LPSTR nTxt = LPSTR (GetGlobMem (gnlen+1));
  if (Text != NULL)
    lmemcpy (nTxt,Text,beg);
  if (Index != NULL)
    lmemcpy (nTxt+beg,Index,Indl);
  if (Length != NULL)
    lmemcpy (nTxt+beg+Indl,Length,Lengthl);
  if (Form0 != NULL)
    lmemcpy (nTxt+beg+Indl+Lengthl,Form0,f0l);
  if (Mod0 != NULL)
    lmemcpy (nTxt+beg+Indl+Lengthl+f0l,Mod0,m0l);

  lmemcpy (nTxt+beg+Indl+Lengthl+f0l+m0l,actWord->resWord,nlen);

  if (Form1 != NULL)
    lmemcpy (nTxt+beg+Indl+Lengthl+f0l+m0l+nlen,Form1,f1l);
  if (Mod1 != NULL)
    lmemcpy (nTxt+beg+Indl+Lengthl+f0l+m0l+nlen+f1l,Mod1,m1l);

  if (Text != NULL) {
    lmemcpy (nTxt+beg+Indl+Lengthl+f0l+m0l+nlen+f1l+m1l,Text+end,golen-end);
    FreeGlobMem (Text);
    }
  WORD oP = cPos;
  cPos = beg;
  if (Text != NULL)
    DelWordPtr (beg,end,Text);
  BOOL formatAll ;
  if (Text != NULL)
    ChangeWordPtr (nTxt,Text,gnlen-golen,formatAll);
  else
    formatAll = FALSE ;
  cPos = oP;
  Text = nTxt ;
  FreeGlobMem (actWord->resWord);
  if (Index != NULL) FreeGlobMem (Index);
  if (Length != NULL) FreeGlobMem (Length);
  if (Form0 != NULL) FreeGlobMem (Form0);
  if (Mod0 != NULL) FreeGlobMem (Mod0);
  if (Form1 != NULL) FreeGlobMem (Form1);
  if (Mod1 != NULL) FreeGlobMem (Mod1);

  if (mode == CPOS_GETBEG)
    nPos = SkipFormat (Text+beg) - Text;
  else {
    nPos = beg + Indl + Lengthl + f0l + m0l + nlen + f1l + m1l ;
    nPos = SkipFormat (Text+nPos) - Text;
    }
  }

void cField::LoadString () 
  {
  LPSTR h = Text ;
  TWI t;
  int i;
  for ( ; *h ; ) {
    if ((*h == '\\') && (IsValidEscape (h[1]))) {
      for (h ++ ; ((*h) && (*h != '\\')) ; h++) ;
      if (*h == '\\') h++ ;
      }
    else if ((*h == '\\') && (h[1] == 'i') && (h[2] == ':')) {
      WORD Index = GetHexDigit (h+3);
      lmemset (&t,'\0',sizeof(t));
      t.Index = Index;
      t.Format = 0xFFFF;
      if (cfb != NULL)
        (*cfb) (CALLBACKCMD_GETWORD,&t,CallBackMem);
      WORD beg = h - Text;
      for ( i = 1 ; h[i] != '\\' ; i++) ;
      WORD end = beg + i + 1;
      if (t.res) {
        // Interpretierten Block einsetzen
        WORD nPos;
        ChangeText (&t,beg,end,nPos,CPOS_GETEND);
        h = Text + nPos;
        }
      else {
        // Nicht interpretierten Block loeschen
        int dl = end - beg ;
        for (i = 0 ; h[i+dl] ; i++)
          h[i] = h[i+dl];
        h[i] = '\0';
        }
      }
    else
      h++;
    }
  RemoveNotNeededFormats ();
  }

BOOL cField::IsSHWorkKey (WPARAM wP)
  {
  return ((wP == VK_F2) || ((wP == VK_RETURN) && ((fieldMode & FM_MSELECTION) != 0)));
  }

#define VK_CONTROL_MINUS  189
BOOL cField::IsHiddenKey (WPARAM wP)
  {
  return ((wP == VK_CONTROL_MINUS) && (GetKeyState (VK_CONTROL) < 0)) ;
  }

DLLExport void _export WINAPI cField::GetLeftLower (LPPOINT pt,int Seite)
  {
  if (First == NULL) Reformat ();
  if ((AllSameFormat ()) && (AllSamePage())) {
    int l = GetAnzLines ();
    if (l <= 0) l = 1;
    int lHeight = yLineHeight(DefFormat);
    pt->x = x0 ;
    pt->y = y0 + lHeight * l;
    }
  else {
    RECT r;
    GetFieldRect (&r,Seite);
    pt->x = r.left ;
    pt->y = r.bottom ;
    }
  }

DLLExport void _export WINAPI cField::SetVOrg (int x,int y,int s)
  { 
  xp = x ; 
  yp = y ; 
  ErsteSeite = s ;
  if (ActiveField == this)
    PosCaret () ; 
  cfBtn.OnMapChange (this);
  } 

DLLExport void _export WINAPI cField::SetScale (double sc,int type)
  { 
  scale = sc ; 
  MapType = type ; 
  if (ActiveField == this)
    PosCaret () ; 

  cfBtn.OnMapChange (this);
  }

DLLExport void _export WINAPI cField::SetWOrg (int x,int y)
  { 
  xa = x ; 
  ya = y ; 
  if (ActiveField == this)
    PosCaret () ;
  cfBtn.OnMapChange (this);
  }

extern BOOL InExternPaint;
DLLExport void _export WINAPI cField::StartExternPaint ()
  {
  if (ActiveField == this)
    InExternPaint = TRUE ,
    HideFieldCaret (Wnd);
  }

DLLExport void _export WINAPI cField::EndExternPaint ()
  {
  if (ActiveField == this)
    InExternPaint = FALSE ,
    PosCaret ();
  }

DLLExport void _export WINAPI cField::GetActivePos (LPPOINT pt)
  {
  if (oldCaretHeight) {
    int LineNmbr,Format,Modify;

    HDC hDC = GetFieldDC ();
    GetCaretPos (hDC,(int FAR &)pt->x,(int FAR &)pt->y,LineNmbr,Format,Modify);
    RestDC (hDC);
    }
  else
    pt->x = pt->y = 0;
  }

/////////////////////////////////////////////////////////////////////
//  Implementierung der Klasse sWord und sField
/////////////////////////////////////////////////////////////////////
DLLExport _export WINAPI sField::sField (WORD bkmode,int format,int x,int y,int width,
                                int anzlines,BOOL doSelect,double a,int Maptype)
        : cField (bkmode,format,x,y,width,anzlines,doSelect)
  {
  ang = a;
  GetFormatInfo (format) -> GetSlantHandle (ang,Maptype,0,DWORD (this),TRUE);
  GetTransform ();
  }

DLLExport _export WINAPI sField::~sField ()
  {
  GetFormatInfo (DefFormat) -> DelSlantHandle (DWORD(this));
  if (hcrtbmp) DeleteObject (hcrtbmp);
  }


DLLExport void _export WINAPI sField::Paint (HDC hDC,int Seite,BOOL forPrinting)
  {
  if ((First == NULL) || (forPrinting)) 
    Reformat (hDC);
  SetTextAlign (hDC,TA_LEFT | TA_TOP);
  SetBkMode (hDC,bkmode);
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next )
    if ((ErsteSeite + w->RelativSeite == Seite) && (w->Visible (hDC)))          // Wort im Update-Bereich
      w->Paint (hDC,Seite);

  if ((doSelect) && (hAPen != 0) && (hIPen != 0) && (!forPrinting)) {
    SelectObject (hDC,(this == ActiveField) ? hAPen : hIPen);
    POINT pt[4];
    GetPaintRect (pt);
    MoveToEx (hDC,pt[0].x,pt[0].y, NULL);
    LineTo (hDC,pt[1].x,pt[1].y);
    LineTo (hDC,pt[2].x,pt[2].y);
    LineTo (hDC,pt[3].x,pt[3].y);
    LineTo (hDC,pt[0].x,pt[0].y);
    }

  if (ActiveField == this)
    PosCaret ();
  if (forPrinting) ResetWords ();
  }

void sField::ModifyDC (HDC hDC,int Format,int Modify,HFONT FAR *OldFont,BOOL full)
  {
  // Format und modify werden ignoriert, nur defformat ist erlaubt!!
  ///////////////////////////////////////////////////////////////////
  // *OldFont = (HFONT)SelectObject (hDC,GetFormatInfo (DefFormat)->GetSlantHandle(ang,MapType));
  *OldFont = (HFONT)SelectObject (hDC,GetFormatInfo (MappedFormat(Format))->GetSlantHandle(ang,MapType,Modify,DWORD(this)));
  DWORD color = GetOutColor(Format);
  SetTextColor (hDC,color);
  if (full) {
    SetTextAlign (hDC,TA_LEFT | TA_TOP);
    SetBkMode (hDC,bkmode);
    }
  }

void sWord::DrawBlanks (HDC hDC)
  {
  // Do nothing here
  }

void sWord::Invalidate (HDC hDC)
  {
  if ((AnzChars > 0) && (xLen > 0)) {
    RECT r;
    r.left   = xPos + xExtra;
    r.top    = yPos;  // yPos - yBaseHeight;
    r.right  = r.left + xLen;
    r.bottom = r.top + yHeight;
    ((sField FAR *) Parent)->TransformRect (&r);
    LPtoDP (hDC,LPPOINT(&r),2);
    r.left  -= 1;
    r.right += 1;
    int swap ;
    if (r.top > r.bottom)
      swap = r.top, r.top = r.bottom, r.bottom = swap;
    r.top -= 1;
    r.bottom += 1;
    InvalidateRect (Parent->Wnd,&r,TRUE);
    }
  }

void sWord::GetWordRect (LPRECT r)
  {
  if (AnzChars > 0) {
    r->left   = xPos + xExtra;
    r->top    = yPos - yBaseHeight;
    r->right  = r->left + xLen;
    r->bottom = r->top + yHeight;
    ((sField FAR *) Parent)->TransformRect (r);

    int swap;
    if (r->top > r->bottom) swap = r->top, r->top = r->bottom, r->bottom = swap;

    r->left -= 1;      r->top    += 1 ;
    r->bottom -= 1;    r->bottom += 1 ;
    }
  else
    SetRectEmpty (r);
  }

void sWord::Paint (HDC hDC, int Seite, BOOL Inverted, int xLeft, int xRight)
  {
  HFONT OldFont = 0;
  Parent->ModifyDC (hDC,wFormat,wModify,&OldFont);
  if ((AnzChars > 0) && (*Text != '\r')) {
    BOOL txDone = FALSE;
    DWORD OldTextColor;
    if (WordType == WORDTYPE_EXTSPACE)
      DrawBlanks (hDC);
    else {
      if (dwColor != 0xFFFFFFFF) {
        DWORD dwnColor;
        if ((Parent->outcolor & 0xFF000000) != 0)
          dwnColor = Parent->outcolor & 0x00FFFFFF ;
        else
          dwnColor = dwColor;

        if (Parent->cfb != NULL)
          (* Parent->cfb) (CALLBACKCMD_TRANSLATECLR,&dwnColor,Parent->CallBackMem);

        OldTextColor = SetTextColor (hDC,dwnColor);
        txDone = TRUE ;
        }
      
      POINT pt;
      pt.x = xPos + xExtra;
      pt.y = yPos - yBaseHeight ;   // !!! neu: -yBaseHeight
      ((sField FAR *) Parent)->TransformPoint (&pt);
      TextOut (hDC,pt.x,pt.y,Text,AnzChars);
      }
    if (txDone)
      SetTextColor (hDC,OldTextColor);
    }
  if (OldFont)
    SelectObject(hDC,OldFont);
  }

void sField::GetTransform()
  {
  // Die anderen Funktionen verlassen sich darauf, dass -180.0 < ang < 180.0
  for ( ; ang > 180.0 ; )  ang -= 360.0 ;
  for ( ; ang < -180.0 ; ) ang += 360.0 ;
  double a = ang * 3.14 / 180.0 ;
  ca = cos(a);
  sa = sin(a);
  }

void sField::TransformPoint (LPPOINT pt)
  {
  double x = double (pt->x);
  double y = double (pt->y);
  pt->x = int (x * ca + y * sa) + x0 ;
  pt->y = int (- x * sa + y * ca) + y0 ;
  }

inline int min4 (LPPOINT pt)
  {
  int m1 = min(pt[0].x,pt[1].x);
  int m2 = min(pt[2].x,pt[3].x);
  return min(m1,m2);
  }

inline int max4 (LPPOINT pt)
  {
  int m1 = max(pt[0].x,pt[1].x);
  int m2 = max(pt[2].x,pt[3].x);
  return max(m1,m2);
  }

void sField::TransformRect (LPRECT r)
  {
  POINT pt[4];
  pt[0].x = r->left  ;  pt[0].y = r->top;
  pt[1].x = r->left  ;  pt[1].y = r->bottom;
  pt[2].x = r->right ;  pt[2].y = r->bottom;
  pt[3].x = r->right ;  pt[3].y = r->top;
  for (int i = 0 ; i < 4 ; i++)
    TransformPoint (&pt[i]);
  r->left   = min4(pt);
  r->right  = max4(pt);
  r->top    = min4(LPPOINT(LPSTR(pt) + sizeof(int)));
  r->bottom = max4(LPPOINT(LPSTR(pt) + sizeof(int)));
  }

void sField::GetPaintRect (LPPOINT pt)
  {
  RECT r;
  cField::GetFullFieldRect (&r,ErsteSeite);
  OffsetRect (&r,-x0,-y0);
  pt[0].x = r.left  - 1;  pt[0].y = r.top    - 1;
  pt[1].x = r.left  - 1;  pt[1].y = r.bottom + 1;
  pt[2].x = r.right + 1;  pt[2].y = r.bottom + 1;
  pt[3].x = r.right + 1;  pt[3].y = r.top    - 1;
  for (int i = 0 ; i < 4 ; i++)
    TransformPoint (&pt[i]);
  }

BOOL sField::GetFullTextRect (LPRECT r,int Seite)
  {
  BOOL res = cField::GetFullTextRect (r,Seite);
  OffsetRect (r,-x0,-y0);
  TransformRect (r);
  // OffsetRect (r,x0,y0);
  return res;
  }

void sField::SetCaretToPos (HDC hDC,int x,int y)
  {
  POINT pt;
  pt.x = x - x0 ;
  pt.y = y - y0 ;
  TransformPoint (&pt);
  pt.x += CaretDX ;
  toDPKoords (hDC,(int &)pt.x,(int &)pt.y);
  SetCaretPos (pt.x,pt.y);
  }

inline int iabs (int x)
  {
  return (x < 0) ? -x : x ;
  }

void sField::GetCaret ()
  {
  if (IsWindow (Wnd)) {
    if (hcrtbmp) DeleteObject (hcrtbmp);
    SetActToCaret ();
    int lh;
    int physheight = GetCaretHeight (&lh);
    POINT pt;
    pt.x = int (- sa * double (physheight));
    pt.y = int ( ca * double (physheight));
    HDC hDC = GetFieldDC ();
    HDC hmemDC = CreateCompatibleDC (hDC);
    hcrtbmp = CreateBitmap (iabs(pt.x) + 1,iabs(pt.y) + 1,1,1,NULL);
    HBITMAP old = (HBITMAP)SelectObject (hmemDC,hcrtbmp);
    SelectObject (hmemDC,GetStockObject(NULL_PEN));
    SelectObject (hmemDC,GetStockObject(BLACK_BRUSH));
    Rectangle (hmemDC,0,0,iabs(pt.x) + 2,iabs(pt.y) + 2);
    SelectObject (hmemDC,GetStockObject(WHITE_PEN));
    if (((ang >= 0.0) && (ang < 90.0)) || (ang < -90.0)) {
      MoveToEx (hmemDC,0,0,NULL) , LineTo (hmemDC,iabs(pt.x),iabs(pt.y));
      CaretDX = 0;
      }
    else {
      MoveToEx (hmemDC,iabs(pt.x),0,NULL) , LineTo (hmemDC,0,iabs(pt.y));
      CaretDX = - (int (double (lh) * sa));
      }
    SelectObject (hmemDC,old);
    DeleteDC (hmemDC);
    RestDC(hDC);
    CreateCaret (Wnd,hcrtbmp,iabs(pt.x),iabs(pt.y));
    oldCaretHeight = physheight;
    }
  }

DLLExport void _export WINAPI sField::GetFullFieldRect (LPRECT r)
  {
  cField::GetFullFieldRect (r,ErsteSeite);
  OffsetRect (r,-x0,-y0);
  TransformRect (r);
  }

DLLExport void _export WINAPI ResetCFieldCaret ()
  {
//*  if (oldCaretIsShown)
//*    HideCaret (NULL);
  HideFieldCaret (NULL);
  if (oldCaretHeight) {
    DestroyCaret ();
    }
  oldCaretHeight = 0;
//*  oldCaretIsShown = FALSE;
  }

///////////////////////////////////////////////////////
//  Anordenen der Worte fuer die Bubbles und den
//  Icon - Manager
///////////////////////////////////////////////////////
int cField::GetWordCount ()
  {
  int res = 0;
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if (h->WordType == WORDTYPE_CHARS) res++;
    }
  return res;
  }

int cField::GetMaxWidth ()
  {
  int res = 0 ;
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if (h->WordType == WORDTYPE_CHARS) {
      if (h->xLen > res) res = h->xLen;
      }
    }
  return res;
  }

int cField::ArrangeWords (int width)
  {
  int yp = yBaseHeight (DefFormat);
  int xp = 0;
  for (cWord FAR *h = First ; h != NULL ; h = h->Next) {
    if ((xp + h->xLen <= width) || (h->WordType != WORDTYPE_CHARS)) {
      h->xPos = xp;      h->yPos = yp;
      xp += h->xLen;
      }
    else {
      yp += h->yHeight;
      h->yPos = yp ;
      h->xPos = 0;
      xp = h->xLen;
      }
    if (h->Next == NULL) {
      yp += h->yHeight;
      }
    }
  return yp;
  }

void cField::CenterWords (int width)
  {
  cWord FAR *LineStart = NULL ;
  int aw,ay,as;
  for (cWord FAR *h = First ; ; ) {
    if ((LineStart == NULL) && (h != NULL)) {
      LineStart = h;
      ay = h->yPos;
      aw = as = 0;
      }
    if ((h == NULL) || (h->yPos != ay)) {
      int dx = (width - aw) / 2 ;
      for (cWord FAR *x = LineStart ; x != h ; x = x->Next)
        x->xPos += dx;
      LineStart = NULL ;
      if (h == NULL) break ;
      }
    else {
      if (h->WordType == WORDTYPE_CHARS)
        aw = aw + as + h->xLen , as = 0 ;
      else
        as = as + h->xLen;
      h = h->Next ;
      }
    }
  }

void cField::UnionWordRects (LPRECT r)
  {
  RECT rw;
  SetRectEmpty (r);
  BOOL doFirst = TRUE ;
  for ( cWord FAR *w = First ; w != NULL ; w = w->Next ) {
    if (w->WordType == WORDTYPE_CHARS) {
      w->GetWordRect (&rw);
      if (doFirst) 
        CopyRect (r,&rw) , doFirst = FALSE ;
      else
        MyUnionRect (r,&rw,r);
      }
    }
  }

DLLExport void _export WINAPI cField::Arrange (int relHeight)
  {
  Reformat ();
  if (GetWordCount () > 1) {
    RECT r;
    GetFieldRect (&r,ErsteSeite);
    int mxw = r.right - r.left + 1;
    int mnw = GetMaxWidth ();
    int ibest = 0;
    int vbest = 32000;
    int w ;
    for (int i = 0 ; i < 10 ; i++) {
      // 10 Versuche um die Weite herauszufinden, bei der es am besten passt
      w = mnw + int (double(i) * double(mxw - mnw) / 10.0);
      int h = ArrangeWords (w);
      UnionWordRects (&r);
      int v = int (double (r.bottom - r.top) 
                     / double(r.right - r.left) * 100.0
                  ) ;
      v = (v < relHeight) ? relHeight - v : v - relHeight;
      if (v < vbest)
        ibest = i, vbest = v ;
      }
    w = mnw + int (double(ibest) * double(mxw - mnw) / 10.0);
    ArrangeWords (w);
    UnionWordRects (&r);
    CenterWords (r.right - r.left + 1);
    }
  }

//////////////////////////////////////////////////////////////////////////
//  Passwort
//////////////////////////////////////////////////////////////////////////
BOOL pWord::GetWordWidth (HDC hDC,LPSTR Text,int AnzChars,LPINT FAR *chWidth)
  {
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDC,"*",1,&size);
  int sWidth = size.cx;
#else
  int sWidth = LOWORD(GetTextExtent (hDC,"*",1));
#endif
  if (chWidth != NULL) {
    if (*chWidth != NULL)
      FreeGlobMem (*chWidth);
    *chWidth = (int FAR *) GetGlobMem (sizeof(int) * AnzChars);
    for (int i = 0 ; i < AnzChars ; i++) {
      (* chWidth)[i] = sWidth ;
      }
    }
  return sWidth * AnzChars ;
  }
BOOL pWord::GetIVRect (HDC hDC, LPRECT r)
  {
  if (AnzChars > 0) {
    r->left   = xPos + xExtra + Parent->x0;
    r->top    = yPos - yBaseHeight + Parent->y0;
    r->right  = r->left + xLen;
    r->bottom = r->top + yHeight;
    int swap ;
    if (r->top > r->bottom)
      swap = r->top, r->top = r->bottom, r->bottom = swap;
    LPtoDP (hDC,LPPOINT(r),2);
    r->left  -= 1;
    r->right += 1;
    if (r->top > r->bottom)
      swap = r->top, r->top = r->bottom, r->bottom = swap;
    r->top -= 1;
    r->bottom += 1;
    return TRUE ;
    }
  else
    return FALSE ;
  }

int pField::PhysWidth (HDC hDC,LPSTR Text,int AnzChars)
  {
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDC,"*",1,&size);
  int sWidth = size.cx;
#else
  int sWidth = LOWORD(GetTextExtent (hDC,"*",1));
#endif
  int lw = sWidth * AnzChars;
  POINT pt[2];
  pt[0].x = 0 ;  pt[0].y = 0 ;
  pt[1].x = lw ; pt[1].y = 0 ;
  LPtoDP (hDC,pt,2);
  return pt[1].x - pt[0].x ;
  }

BOOL pField::SameChars (LPSTR t1,LPSTR t2,int FAR *res,int count)
  {
  for ( *res = 0 ; *res < count ; t1 ++ , t2 ++) {
    if ((*t1 != '\0') == (*t2 != '\0')) (*res) ++ ;
    else break ;
    }
  return (*res > 0) ;
  }

void pField::GetCaretPos (HDC hDC,int FAR &x,int FAR &y,int FAR &LNmbr,
                          int FAR &Format,int FAR &Modify,BOOL checkAlways)
  {
  if (oldCaretHeight) {
    SetExistingAct ();
    if (act != NULL) {
      HFONT OldFont = 0;
      ModifyDC (hDC,Format = act->wFormat,Modify = act->wModify,&OldFont);

#ifdef WIN32
      SIZE size;
      GetTextExtentPoint32 (hDC,"*",1,&size);
      int sWidth = size.cx;
#else
      int sWidth = LOWORD(GetTextExtent (hDC,"*",1));
#endif

      x = x0 + GetDefPosition (DefFormat) + sWidth * cPos ;
      y = y0 ;
      LNmbr = 0;
      if (OldFont)
        SelectObject(hDC,OldFont);
      }
    else {
      x = x0 + GetDefPosition (DefFormat);
      y = y0 ;
      LNmbr = 0;
      }
    }
  }

DLLExport _export WINAPI pField::pField (WORD bkmode,int format,int x,int y,int width,
                                int anzlines,BOOL doSelect)
        : cField (bkmode,format,x,y,width,anzlines,doSelect)
  {
  }

DLLExport void _export WINAPI pField::Paint (HDC hDC,int Seite,BOOL forPrinting)
  {
  if (Text != NULL) {
    if (First == NULL)
      Reformat (hDC);
    if (First != NULL) {
      HFONT OldFont = 0;
      ModifyDC (hDC,DefFormat,DefModify(),&OldFont,TRUE);
      int AnzChars = lstrlen (Text);
      LPSTR h = LPSTR (GetGlobMem (AnzChars + 1));
      for (int i = 0 ; i < AnzChars ; i++)
        h[i] = '*' ;
      TextOut (hDC,First->xPos+x0+First->xExtra,First->yPos+y0,
                    h,AnzChars);
      FreeGlobMem (h);
      if (OldFont)
        SelectObject(hDC,OldFont);
      }
    }

  if (ActiveField == this) {
    if ((oldCaretHeight == 0) && (!InExternPaint))
      GetCaret ();
    PosCaret (hDC, TRUE);
    }
  }

//////////////////////////////////////////////////////////////////////
//  Setzen eines Absatz - Formates
//////////////////////////////////////////////////////////////////////
DLLExport void _export WINAPI cField::SetFormat (int format)
  {
  SetExistingAct ();
  char Ins1String[30],Ins2String[30];
  wsprintf (Ins1String,"\\f:%d\\",format);
  if (act == NULL) {
    if (format != int (DefFormat))
      *this = Ins1String;
    }
  else {
    if (int (act->wFormat) == format) return;
    wsprintf (Ins2String,"\\f:%d\\",format);
    int h = cPos ;
    BOOL dontCheck = FALSE ;
    int fpos,epos;
    if (Text[h] == '\r') {
      if (h > 0) {
        if (Text[h-1] == '\r') {
          fpos = epos = h;
          dontCheck = TRUE ;
          }
        else
          h -= 1;
        }
      else {
        fpos = epos = 0;
        }
      }
    // Suchen des Anfangs des aktuellen Absatzes
    if (!dontCheck) {
      for (fpos = h ; ; ) {
        if (fpos <= 0) break ;
        else if (Text[fpos] == '\r') {
          fpos++;
          break ;
          }
        else
          fpos-- ;
        }
      // Suchen des Endes des Aktuellen Strings
      for (epos = h ; ; ) {
        if (Text[epos] == '\0') break;
        else if (Text[epos] == '\r') {
          epos ++ ;
          break;
          }
        epos ++ ;
        }
      }
    // Neu Zusammenstellen des Absatzes
    LPSTR nAbsatz = LPSTR (GetGlobMem (epos - fpos + 1 + lstrlen (Ins1String) + 
                                lstrlen (Ins2String)));

    lstrcpy (nAbsatz,Ins1String);
    int oldcPos = cPos;
    cPos += lstrlen (Ins1String);

    LPSTR a = nAbsatz + lstrlen(nAbsatz);
    for (int i = fpos ; i < epos ; ) {
      if ((Text[i] == '\\') && (IsValidEscape (Text[i+1]))) {
        int cd = (i < int (oldcPos)) ? -1 : 0 ;
        cPos += cd ;
        for ( i ++ ; ((Text[i]) && (Text[i] != '\\')) ; 
                    i++ , cPos = cPos + cd) ;
        if (Text[i] == '\\')
          i ++ , cPos = cPos + cd ;
        }
      else
        *a++ = Text[i++];
      }
    int olen = lstrlen (Text);
    if ((Text[epos]) && (epos < olen - 2) && 
                (!((Text[epos] == '\\') && (Text[epos+1] == 'f'))))
      lstrcat (nAbsatz,Ins2String);
    LPSTR nTxt = LPSTR (GetGlobMem (fpos + (olen - epos) + lstrlen (nAbsatz) + 1));
    lmemcpy (nTxt,Text,fpos);
    lstrcat (nTxt,nAbsatz);
    lstrcat (nTxt,Text+epos);
    FreeGlobMem (Text);
    FreeGlobMem (nAbsatz);
    Text = nTxt;
#ifdef UEBERLEGT
    int h = act->wOffs();
    for (int fpos = h ; ; ) {
      if (fpos <= 0) break ;
      else if (Text[fpos] == '\r') {
        fpos++;
        break ;
        }
      else
        fpos-- ;
      }
    for (int epos = h ; ; ) {
      if (Text[epos] == '\0') break;
      else if (Text[epos] == '\r') break;
      epos ++ ;
      }
    LPSTR nAbsatz = LPSTR (GetGlobMem (epos - fpos + 1 + lstrlen (Ins1String) + 
                                lstrlen (Ins2String)));

    lstrcpy (nAbsatz,Ins1String);
    LPSTR a = nAbsatz + lstrlen(nAbsatz);
    for (int i = fpos ; i < epos ; i++) {
      if ((Text[i] == '\\') && (IsValidEscape (Text[i+1]))) {
        for ( i ++ ; ((Text[i]) && (Text[i] != '\\')) ; i++) ;
        }
      else
        *a++ = Text[i];
      }
    if (Text[epos])
      lstrcat (nAbsatz,Ins2String);
    int olen = lstrlen (Text);
    LPSTR nTxt = LPSTR (GetGlobMem (fpos + (olen - epos) + lstrlen (nAbsatz) + 1));
    lmemcpy (nTxt,Text,fpos);
    lstrcat (nTxt,nAbsatz);
    lstrcat (nTxt,Text+epos);
    FreeGlobMem (Text);
    FreeGlobMem (nAbsatz);
    Text = nTxt;
    cPos = SkipFormat(Text) - Text;
#endif
    ResetWords ();
    Reformat ();
    PosCaret ();
    }
  if (cfb != NULL)
    (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
  }

DLLExport int _export WINAPI cField::GetActFormat ()
  {
  if (Text == NULL) return DefFormat;
  if (cPos == 0)
    cPos = SkipFormat (Text) - Text;
  if (First == NULL)
    Reformat ();
  cWord FAR *fAct = GetWordForFormat ();
  if (fAct != NULL)
    return fAct->wFormat ;
  else
    return DefFormat;
  }

DLLExport DWORD _export WINAPI cField::GetActColor ()
  {
  if (*_startColor) return _actColor;
  if (Text == NULL) return 0L;
  if (cPos == 0)
    cPos = SkipFormat (Text) - Text;
  if (First == NULL)
    Reformat ();
  cWord FAR *fAct = GetWordForFormat ();
  if (fAct != NULL) {
    return (fAct->dwColor == 0xFFFFFFFF) ? 0L : fAct->dwColor ;
    }
  else
    return 0L;
  }

DLLExport WORD _export WINAPI cField::GetActModify ()
  {
  if (_startFormat[0])
    return ModifyNum (_startFormat[2]);
  cWord FAR *fAct ;
  if ((First != NULL) && AlreadySelected && (StartSel.CaretPos != EndSel.CaretPos)) {
    cWord FAR *fMin = GetExistingWordWithPos (StartSel.CaretPos),
          FAR *fMax = GetExistingWordWithPos (EndSel.CaretPos); 
    if (fMin->wOffs() > fMax->wOffs()) {
      cWord FAR *d = fMax ;
      fMax = fMin;
      fMin = d ;
      }
    WORD res = 0 ;
    for ( fAct = fMin ; fAct != NULL ; fAct = fAct->Next) {
      if (fAct == fMax) {
        if (fMax->wOffs() <= WORD(max(StartSel.CaretPos,EndSel.CaretPos)))
          res = res | fAct->wModify ;
        break ;
        }
      res = res | fAct->wModify ;
      }
    return res;
    }
  else
    fAct = GetWordForFormat ();
  if (fAct != NULL)
    return fAct->wModify ;
  else
    return DefModify();
  }

HWND cField::CalcFontRefWnd ()
  {
  if (cfb != NULL) {
    FontRefWndBuffer buffer;
    buffer.IsDone = FALSE ;
    (* (cfb)) (CALLBACKCMD_GETFONTREFWND,&buffer,CallBackMem);
    return (buffer.IsDone) ? buffer.RefWnd : Wnd;
    }
  else
    return 0; // ehemals: return hWnd;
  }

/////////////////////////////////////////////////////////////////////////
//  Verwaltung der Invertierung von Text beim Ueberschreibmodus
/////////////////////////////////////////////////////////////////////////
void cField::TestSelState (int Seite)
  {
  if (cfb != NULL) {
    BOOL state = FALSE;
    (* (cfb)) (CALLBACKCMD_DOOVERWRITE,&state,CallBackMem);
    if (state) sel_state = SELSTATE_DOOVERWRITE , cPos = 0 , Invalidate (Seite,FALSE); 
    else       sel_state = SELSTATE_NONE;
    }
  else         sel_state = SELSTATE_NONE;
  }

void cField::ResetSelState (int Seite)
  { 
  if (sel_state == SELSTATE_DOOVERWRITE) {
    sel_state = SELSTATE_NONE ; 
    ResetActFormats ();
    Invalidate (Seite,FALSE); 
    }
  }

void cField::ResetAndDeleteSelState (WPARAM wP,int Seite)
  {
  if ((wP != '\t') && (wP != '\r') && 
        (sel_state == SELSTATE_DOOVERWRITE)) {
    if (Text != NULL) FreeGlobMem (Text);
    ResetWords ();
    Text = NULL;
    sel_state = SELSTATE_NONE ; 
    Invalidate (Seite,FALSE); 
    }
  }

void cField::InvertText (HDC hDC)
  {
  if (sel_state == SELSTATE_DOOVERWRITE) {
    for ( cWord FAR *w = First ; w != NULL ; w = w->Next ) {
      RECT r;
      w->GetWordRect (&r);
      InvertRect (hDC,&r);
      }
    }
  }

DLLExport void _export WINAPI cField::SetOutColor (COLORREF color)
  {
  outcolor = color | 0xFF000000 ;
  }

DLLExport void _export WINAPI cField::UseDefOutColor ()
  {
  outcolor = 0;
  }

DLLExport void _export WINAPI cField::SetButtonField (BOOL flag)
  {
  HasButton = flag;
  if (this == ActiveField) {
    ClearSelection ();
    cfBtn.OnSetFocus (ActiveField);
    ReleaseCaret ();
    }
  }

DLLExport void _export WINAPI PaintActiveCombo (HDC hDC,HWND hW,BOOL isPrinting,int Seite)
  {
  if (!isPrinting) {
    if ((cfBtn.MyField != NULL) && (cfBtn.MyField->FirstPage() + cfBtn.MyField->LastPage() == Seite))
      cfBtn.OnPaint (hDC, FALSE,hW);
    }
  }

DLLExport cField FAR * _export WINAPI GetActiveField ()
  {
  return ActiveField;
  }


HANDLE hText = NULL;
HANDLE hCText = NULL;
HANDLE hData,hCData;

#define MAXBUFLEN   512

//----------------------------------------------------------------------------
// Text in die Zwischenablage schreiben
//----------------------------------------------------------------------------
int AnzFormats (LPSTR Text,int AnzChars)
  {
  int f = 0 ;
  for ( LPSTR h = Text ; ((*h) && (h < Text + AnzChars)) ; ) {
    if ((h[0] == '\\') && (h[1] == 'f') && (h[2] == ':')) {
      f += 1 ;
      for ( ++ h ; ((*h) && (*h != '\\')) ; h++ ) ;
      }
    h ++ ;
    }
  return f ;
  }

DLLExport BOOL _export WINAPI cField::CopyToClipBoard (HWND hWnd)
  {
  if (!AlreadySelected)
    return FALSE;

  FieldSelStruct SelStart, SelEnd;
  GetSelectionFromLeftToRight (&SelStart, &SelEnd);

  // GetAnzLines() nimmt die zusaetzlichen LF auf!

  WORD cStart = SelStart.CaretPos;
  WORD cEnd = SelEnd.CaretPos;

  if (cStart == cEnd) return FALSE ;

  if ((cStart > 0) && (PrevIsFormatStr (Text + cStart - 1,Text)))
    cStart = SkipPrevFormat (Text + cStart - 1) - Text; // Vor die Formatierinfo
  int TextCLen = cEnd - cStart + 1 + 3 + // Hinten wird sicherheitshalber noch ein \\m0 eingefuegt
        AnzFormats (Text + cStart,cEnd - cStart + 1) * 4 ; // Die Formatbezeichnung koennte um bis zu 4 Zeichen laenger werden
  int TextTLen = cEnd - cStart + 1 + GetAnzLines() + 3; // \r -> \r\n

  if (hText != NULL) {  GlobalFree (hText);  hText = NULL; }
  if (hCText != NULL) {  GlobalFree (hCText);  hCText = NULL; }
  hText = GlobalAlloc(GMEM_MOVEABLE, TextTLen);
  hCText = GlobalAlloc(GMEM_MOVEABLE, TextCLen);
  LPSTR lpszText = LPSTR(GlobalLock(hText));
  LPSTR lpszCText = LPSTR(GlobalLock(hCText));
  *lpszText = *lpszCText = '\0' ;

  LPSTR x = lpszText;
  for (LPSTR h = Text + cStart ; h < Text + cEnd ; ) {
    if (*h == '\\') {
      if (h[1] == 'm') h += 3 ;
      else if (h[1] == '\\') {
        *x ++ = *h ;
        h += 2 ;
        }
      else {
        for ( ++ h ; ((*h) && (*h != '\\')) ; h++) ;
        }
      }
    else if (*h == '\r') {
      *x++ = *h ++ ;
      *x++ = '\n' ;
      }
    else
      *x++ = *h++ ;
    }
  *x ++ = '\0' ;

  x = lpszCText ;
  for ( h = Text + cStart ; h < Text + cEnd ; ) {
    if (*h == '\\') {
      if (h[1] == 'm') *x ++ = *h ++ ;
      else if (h[1] == '\\') {
        *x ++ = *h ;
        *x ++ = *h ;
        h += 2 ;
        }
      else if ((h[1] == 'f') && (h[2] == ':')) {
        int f = 0 ;
        for ( int i = 3 ; ((h[i] >= '0') && (h[i] <= '9')) ; i++) {
          f = f * 10 + h[i] - '0';
          }
        h += i + 1;
        char ftext[32];
        int nf = MappedFormat (f);
        wsprintf (ftext,"\\f:%d\\",nf);
        lstrcpy (x,ftext);
        x += lstrlen (x);
        }
      else {
        for ( *x++ = *h++ ; ((*h) && (*h != '\\')) ; *x++ = *h++) ;
        *x++ = *h++ ;
        }
      }
    else
      *x ++ = *h ++ ;
    }
  *x ++ = '\\' ;
  *x ++ = 'm' ;
  *x ++ = '0' ;
  *x ++ = '\0' ;

#ifdef UEBERLEGT
  if (SelStart.SelWord == SelEnd.SelWord) {      // Selektion im selben Wort?
    lstrcpyn (lpszText, Text + SelStart.CaretPos, TextLen-1);
    }
  else {                                         // nein!
    for (cWord FAR* w = SelStart.SelWord; w != NULL; w = w->Next) {
      if (w == SelEnd.SelWord) {
        int Len = SelEnd.CaretPos - w->wOffs() + 1;
        if (Len > 0) {
          lstrcpyn (szBuf, w->Text, Len);
          lstrcat (lpszText, szBuf);
          }
  
        break;     // Ende der Selektion also raus
        }
        
      if (w == SelStart.SelWord) {
        lstrcpyn (szBuf, Text + SelStart.CaretPos, 
                  w->wOffs() + w-> AnzChars - SelStart.CaretPos + 1);
        lstrcat (lpszText, szBuf);
        }
      else {
        lstrcpyn (szBuf, w->Text, w->AnzChars+1);
        lstrcat (lpszText, szBuf);
        }
  
      // einem Hard-RETURN wird ein LINEFEED angefuegt!
      if (w->WordType == WORDTYPE_CR) { 
        char str[3];
        lstrcat (lpszText, makeStr (str, '\n'));  
        }
      }
    }
#endif
    
  if (hText) {
    UINT shouldBe = RegisterClipboardFormat ("CWORD");

    hData = GlobalAlloc (GMEM_MOVEABLE, GlobalSize(hText));
    hCData = GlobalAlloc (GMEM_MOVEABLE, GlobalSize(hCText));

    LPSTR lpData = LPSTR (GlobalLock (hData));
    LPSTR lpCData = LPSTR (GlobalLock (hCData));

    lstrcpy (lpData, lpszText);
    lstrcpy (lpCData, lpszCText);
    GlobalUnlock (hData);
    GlobalUnlock (hText);
    GlobalUnlock (hCText);

    if (OpenClipboard(hWnd)) {
      EmptyClipboard();
      SetClipboardData (CF_TEXT, hData);
      SetClipboardData (shouldBe, hCData);
      CloseClipboard();
      }

    hData = NULL;  
    hCData = NULL;  
    }
    
  if (hText != NULL) {   GlobalFree (hText);  hText = NULL;  }
  if (hCText != NULL) {  GlobalFree (hCText);   hCText = NULL;  }

  return TRUE;  
  }


//----------------------------------------------------------------------------
// Text aus der Zwischenablage einfuegen
//----------------------------------------------------------------------------
DLLExport BOOL _export WINAPI cField::PasteFromClipBoard (HWND hWnd)
  {
  if ((fieldMode & FM_JUSTDEL) ||  // nix Einfuegen im "NUR-LOESCHEN" - Modus
      (HasButton && !(fieldMode & FM_BTNWITHINPUT)))
    return FALSE;
  
  if (OpenClipboard(hWnd)) {
    HANDLE hClipData;
    LPSTR  lpClipData;
    LPSTR  lpszText;

    if (AlreadySelected) {
      DeleteSelectedLines();
      InvalidateSelectedWords();
      ClearSelection ();
      }
      
    int Seite ;
    if (act != NULL) {
      Seite = ErsteSeite + act->RelativSeite ;
      }
    else
      Seite = ErsteSeite ;

    UINT myFormat;
    UINT shouldBe = RegisterClipboardFormat ("CWORD");

    if (shouldBe) {
      hClipData = GetClipboardData(shouldBe);
      myFormat = shouldBe;
      }

    if (hClipData == NULL) {
      if (((hClipData = GetClipboardData(CF_TEXT)) == NULL) && (!AlreadySelected)) {
        CloseClipboard();
        return FALSE;
        }
      myFormat = CF_TEXT;
      }

    if (hText != NULL) {
      GlobalFree (hText);
      hText = NULL;
      }
        
    hText = GlobalAlloc(GMEM_MOVEABLE, GlobalSize(hClipData));
    if ((hText == NULL) || (lpClipData = LPSTR(GlobalLock(hClipData))) == NULL ||
                           (lpszText = LPSTR(GlobalLock(hText))) == NULL) {
      CloseClipboard();
      return FALSE;
      }

    lstrcpy (lpszText, lpClipData);
    GlobalUnlock (hClipData);
    CloseClipboard();
    GlobalUnlock (hText);

    int s = 0 ;
    for ( LPSTR h = lpszText ; *h ; h++ ) {
      if (*h != '\n') {
        if (*h == '\\') s += 2 ;
        else            s ++ ;
        }
      }
    s ++ ;

    LPSTR tmpstr = LPSTR (GetGlobMem (s));
    LPSTR strptr = tmpstr;
    if (myFormat == CF_TEXT) {
      for ( ; *lpszText; ) {
        if (*lpszText != '\n')
          if (*lpszText == '\\') {
            *tmpstr++ = *lpszText;
            *tmpstr++ = *lpszText ++ ;
            }
          else
            *tmpstr++ = *lpszText++;
        else
          lpszText++;  
        }
      }
    else {
      lstrcpy (strptr,lpszText);
      }

    tmpstr = strptr;
    LPSTR unformatText = LPSTR (GetGlobMem (GetBlockSize (strptr))) ;
    lstrcpy (unformatText,strptr);
    // RemoveFormatInfoFrom (unformatText,strptr);

    
    int mLen = GetMaxChars();
    int AvailableLen = mLen - GetAnzChars();
    BOOL doIt = TRUE ;
    if ((mLen < 0) || (AvailableLen > 0)) {
      if ((mLen > 0) && (lstrlen(unformatText) >= AvailableLen)) {
        if (myFormat == CF_TEXT) {
          unformatText[AvailableLen-1] = '\0';
          doIt = TRUE ;
          }
        else
          doIt = FALSE ;
        }
      else
        doIt = TRUE;
      }
    else
      doIt = FALSE ;
      
    if (doIt) {
      InsertStr (unformatText);
      RemoveNotNeededFormats();
      if (cfb != NULL) {
        (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
        int nModify = 0;
        (* cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
        }

      CheckScroll (Seite);
      }
    else
      MessageBeep (0);  

    FreeGlobMem (tmpstr);
    FreeGlobMem (unformatText);

    return TRUE;
    }
  else  
    return FALSE;
  }


void cField::DeleteTextOut (cWord FAR *wToFormat,int nPos,int ePos)
  {
  if (ePos > nPos) {
    // 1. Nachrechnen, wieviel Geloescht werden soll
    LPSTR h = Text ;
    for (int i = 0 ; (*h) ; ) {
      if ((h < Text + nPos) || (h >= Text + ePos)) i ++ , h++ ;
      else if (*h == '\\') {
        if (IsValidEscape (h[1])) {
          int fs = FormatSize (h);
          h += fs ;
          i += fs ;
          }
        else if (h[1] == 'm') {
          h += 3 ;
          i += 3 ;
          }
        else if (h[1] == '\\') {
          h += 2 ;
          }
        else if (h[1] == 'i') {
          h = Text + SkipIndexed (h - Text) ;
          }
        else
          // WIN_ASSERT (FALSE);
          h ++ ;
        }
      else
        h ++ ;
      }
    i ++ ;

    // 2. Die Worte umkopieren
    ////////////////////////////
    HDC hDC = GetFieldDC ();
    LPSTR nTxt = LPSTR (GetGlobMem (i)) ;
    h = Text ;
    for (LPSTR x = nTxt ; (*h) ; ) {
      if ((h < Text + nPos) || (h >= Text + ePos)) *x++ = *h++ ;
      else if (*h == '\\') {
        if (IsValidEscape (h[1])) {
          int fs = FormatSize (h);
          lmemcpy (x,h,fs);
          x += fs ;
          h += fs ;
          }
        else if (h[1] == 'm') {
          lmemcpy (x,h,3);
          h += 3 ;
          x += 3 ;
          }
        else if (h[1] == '\\') {
          cWord FAR * toDel = GetWordWithPos (x - nTxt + 1);
          if (toDel != NULL)
            DelWord (toDel,hDC);
          ChangeWordPtrFrom (Text,Text,2,x - nTxt);
          h += 2 ;
          }
        else if (h[1] == 'i') {
          LPSTR next_h = Text + SkipIndexed (h - Text) ;
          int do_remove = next_h - h ;
          LPSTR x1 = x ;
          for (LPSTR tx = h ; tx < next_h ; tx++ , x1 ++ ) {
            cWord FAR * toDel = GetWordWithPos (x1 - nTxt);
            if (toDel != NULL)
              DelWord (toDel,hDC);
            }
          ChangeWordPtrFrom (Text,Text,do_remove,x - nTxt);
          h = next_h ;
          }
        else {
          cWord FAR * toDel = GetWordWithPos (x - nTxt);
          if (toDel != NULL)
            DelWord (toDel,hDC);
          ChangeWordPtrFrom (Text,Text,1,x - nTxt);
          h ++ ;
          }
        }
      else {
        cWord FAR * toDel = GetWordWithPos (x - nTxt);
        if (toDel != NULL)
          DelWord (toDel,hDC);
        ChangeWordPtrFrom (Text,Text,1,x - nTxt);
        h ++ ;
        }
      }

    RestDC (hDC);

    // Die Zeiger in den Worten neu bestimmen
    ChangeWordPtrFrom (nTxt,Text,0,0);

    // Die nun nicht mehr benoetigten Infos rausschmeissen
    FreeGlobMem (Text);
    Text = nTxt;
    RemoveNotNeededFormats ();

    WORD tPos;
    BOOL tested = TestWord (cPos-1,tPos,CPOS_GETEND);

    if ((cPos == 0) || (Text[cPos - 1] == '\r'))
      cPos = SkipFormat (Text + cPos) - Text ;  // In diesem Fall die
                                                // Formatinfo ueberspringen
    if (tested) cPos = tPos;
    if ((cPos > 0) && (PrevIsFormatStr (Text + cPos - 1,Text))) {
      LPSTR nCaretText = SkipPrevFormat (Text + cPos - 1) ; // Vor die Formatierinfo
                                                            // setzten
      if (nCaretText != Text) 
        cPos = nCaretText - Text ;
      }

    act = NULL ;
    wToFormat = GetExistingWordWithPos (cPos);
    ReformatAct (wToFormat) ;
    SetActToCaret ();
    PosCaret ();
    }
  }
DLLExport BOOL _export WINAPI cField::DeleteSelectedLines ()
  {
  int letzteSeite;
  if (cfBtn.MyField == this) letzteSeite = LastPage();
  BOOL dontBeep;
  int Seite ;
  if ((HasButton) || (IsCharAllowed (VK_DELETE,&dontBeep,TRUE,TRUE))) {
    if (act != NULL) {
      Seite = ErsteSeite + act->RelativSeite ;
      }
    else
      Seite = ErsteSeite ;
    FieldSelStruct SelStart, SelEnd;
    GetSelectionFromLeftToRight (&SelStart, &SelEnd);

    AlreadySelected = FALSE;
    cWord FAR *wToFormat = GetPrev(SelStart.SelWord);
    cPos = SelStart.CaretPos;
    int ePos = SelEnd.CaretPos ;
    int nPos = SelStart.CaretPos ;
    DeleteTextOut (wToFormat,nPos,ePos);

    ClearSelection();

    if (cfb != NULL) {
      (* cfb) (CALLBACKCMD_SAVESTR,Text,CallBackMem);
      int nModify = 0;
      (* cfb) (CALLBACKCMD_CARETPOSCHG,&nModify,CallBackMem);  // normales Eingabefeld
      }
    CheckScroll (Seite);
    }

  if (cfBtn.MyField == this) {
    if (LastPage() != letzteSeite) {
      cfBtn.OnMapChange(this);
      Invalidate (Seite,TRUE);
      }
    }
  return FALSE;
  }

DLLExport void _export WINAPI WWEnableSelect (BOOL Select)
  {
  bEnableSelect = Select;
  }

DLLExport BOOL _export WINAPI WWGetSelect ()
  {
  return bEnableSelect;
  }

DLLExport void _export WINAPI cField::SetDefFormat (int f)
  {
  if (DefFormat != f) {
    ResetWords ();
    DefFormat = f ;
    }
  }

DLLExport void _export WINAPI cField::SetActLine (int l)
  {
  HDC hDC = GetFieldDC();
  SetCaretInLine (hDC,l,0);   // setze das Caret in Zeile l, womoeglich an x
  RestDC (hDC);
  PosCaret (0, TRUE, FALSE);
  CheckScroll (0);
  }

