///////////////////////////////////////////////////////////////
//  Kleinen Editor zur Bearbeitung der Texte
///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/txedit.cpv   1.54   02 Jul 1999 12:19:24   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/txedit.cpv  $
// 
//    Rev 1.54   02 Jul 1999 12:19:24   Wolfgang
// 1.) Wortsuche statt Wortendesuche.
// 2.) Wortueberpruefung bei Suche wie bei Markieren.
// 
//    Rev 1.53   26 Apr 1999 18:11:56   Wolfgang
// 1.) Statuszeile bei Escape immer loeschen.
// 
//    Rev 1.52   24 Mar 1999 15:28:18   Wolfgang
// 1.) OnSetFocus setzt Caret-Position direkt.
// 
//    Rev 1.51   18 Mar 1999 16:51:32   Wolfgang
// 1.) OnSetFocus macht kein PosCaret mehr (Siehe Kommentar dort).
// 
//    Rev 1.50   18 Mar 1999 14:07:34   Wolfgang
// 1.) Angabe des Feldes bei SB_SETTEXT ueber Konstante.
// 
//    Rev 1.49   15 Mar 1999 16:52:38   Wolfgang
// 1.) Aufwaertssuche und Replace lassen nichts mehr aus.
// 
//    Rev 1.48   15 Mar 1999 11:27:12   Wolfgang
// 1.) IsWordChar statt IsPrintable und TxWordChar.
// 2.) Prev- und NextWord an wordStopFlags angepasst.
// 
//    Rev 1.47   12 Mar 1999 13:51:24   Wolfgang
// 1.) Loeschen der Selektion bis zur letzten Zeile des Files moeglich.
// 
//    Rev 1.46   10 Mar 1999 19:46:30   Wolfgang
// 1.) Search fast komplett umgebaut.
// 2.) xExtraNeg, yExtraNeg und preferLeft neu, zwecks besserer 
//     Scrollpositionierung.
// 
//    Rev 1.45   09 Mar 1999 16:30:30   Wolfgang
// 1.) NeedNewCaption durch neue SetCaption-Methode von TextBlock ersetzt.
// 
//    Rev 1.44   09 Mar 1999 16:01:02   Gerhold
// 
//    Rev 1.43   16 Nov 1998 16:39:18   Gerhold
// Syntaxcoloring verbessert (TAB-Shift-Tab)...
// 
//    Rev 1.42   11 Nov 1998 09:11:36   Hannes
// AnalyseLines: Sicherheitsabfrage auf StartLine != NULL
// 
//    Rev 1.41   02 Nov 1998 11:49:20   Gerhold
// Syntax Coloring Verbesserungen
// 
//    Rev 1.40   29 Oct 1998 11:01:42   Gerhold
// Syntax Coloring verbessert
// 
//    Rev 1.38   21 Aug 1998 17:16:00   Hannes
// Loeschen am Zeilenend (peinlich)
// 
//    Rev 1.37   19 Aug 1998 10:21:56   Hannes
// CtrlEntf am Zeilenende
// 
//    Rev 1.36   30 Apr 1998 16:44:48   Gerhold
// noch ein kleiner Fehler ind FindmatchinBraces
// 
//    Rev 1.35   22 Apr 1998 09:46:16   Gerhold
// FindMatchingBraces (dafuer wird mir der Hannes die Daumenschraube anlegen)
// 
//    Rev 1.34   15 Dec 1997 17:37:08   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.33   18 Nov 1997 12:34:30   Gerhold
// Suche nach oben hatte die gefundenen W”rtern nicht korrekt angezeigt
// 
//    Rev 1.32   05 Nov 1997 09:03:42   Gerhold
// 32 Bit
// 
//    Rev 1.31   28 Aug 1997 15:52:20   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.30   28 Oct 1996 08:47:20   HANNES
// 
//    Rev 1.29   21 Oct 1996 18:57:08   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.28   03 Sep 1996 09:58:34   HANNES
// Editor mit mehr Text
// 
//    Rev 1.27   02 Jul 1996 15:58:10   GERHOLD
// 
//    Rev 1.26   02 Feb 1996 10:50:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.25   27 Oct 1995 10:25:20   GERHOLD
// 
//    Rev 1.24   07 Sep 1995 17:02:16   GERHOLD
// 
//    Rev 1.23   05 Sep 1995 11:28:10   GERHOLD
// Autoindent in LineBreak
// 
//    Rev 1.22   23 Aug 1995 11:05:22   GERHOLD
// 
//    Rev 1.21   09 Jun 1995 00:29:30   HANNES
// Warning: Endline
// 
//    Rev 1.20   07 Jun 1995 12:16:30   GERHOLD
// ein bisschen was im Search veraendert
// 
//    Rev 1.19   15 May 1995 08:51:44   GERHOLD
// 
//    Rev 1.18   26 Apr 1995 15:26:52   HANNES
// 
//    Rev 1.17   24 Apr 1995 15:43:50   GERHOLD
// 
//    Rev 1.16   08 Mar 1995 09:13:24   GERHOLD
// 
//    Rev 1.15   24 Feb 1995 11:12:20   GERHOLD
// 
//    Rev 1.14   16 Feb 1995 12:40:42   GERHOLD
// 
//    Rev 1.13   29 Jan 1995 11:48:24   HANNES
// No change.
// 
//    Rev 1.12   18 Jan 1995 17:05:18   GERHOLD
// 
//    Rev 1.11   16 Jan 1995 15:57:32   GERHOLD
// Kleinigkeiten mit der Zwischenablage
// 
//    Rev 1.10   09 Jan 1995 14:32:58   GERHOLD
// 
//    Rev 1.9   02 Jan 1995 18:33:20   HANNES
// 
//    Rev 1.8   02 Jan 1995 09:31:14   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.7   25 Oct 1994 11:22:52   GERHOLD
// Speicherfehler in der Zwischenablage behoben
// 
//    Rev 1.6   17 Oct 1994 12:17:44   GERHOLD
// Zeilenumbruch war noch falsch
// 
//    Rev 1.5   10 Oct 1994 10:42:08   GERHOLD
// sehr viele grosse Veraenderungen
// 
//    Rev 1.4   30 Sep 1994 14:40:22   GERHOLD
// Erweiterungen fuer die Zwischenablage
// 
//    Rev 1.3   14 Sep 1994 16:58:46   GERHOLD
// Erweiterungen fuer Statuszeile
// 
//    Rev 1.2   12 Jul 1994 14:45:20   HANNES
// 
//    Rev 1.1   04 Jul 1994 14:06:22   HANNES
// Verbesserte Textmetric
// 
//    Rev 1.0   24 Jun 1994 16:54:52   HANNES
// Neuuebernahme clinicum
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"

#include "restool.hpp"
#include "hash.hpp"
#include "drdrop.hpp"
#include "wonscrip.hpp"
#define MODULENUM 106
#include "winass.hpp"
#include "statbar.hpp"

extern HWND hWndStatusbar;


#ifdef ANALYSELINE
  DWORD  CurrentAnalyseState;
#endif


static BOOL cshown;
static BOOL bCaretExists;


// ACHTUNG:  genau der gleich Code ist in WONSCRIP.CPP !!!!
inline int FAR PASCAL GetXMin ()
  {
  return XMIN;
  }


BOOL TextBlock::CheckNextChar (void)
  {
  if (iCaret < lstrlen(LineWithCaret->Text))
    iCaret++;
  else
    if (LineWithCaret->Next != NULL) {
      LineWithCaret = LineWithCaret->Next;
      iCaret = 0;
      }
    else
      return FALSE ;
  return TRUE ;
  }

BOOL TextBlock::CheckPrevChar (void)
  {
  if (iCaret > 0)
    iCaret--;
  else
    if (LineWithCaret->Prev != NULL) {
      LineWithCaret = LineWithCaret->Prev;
      iCaret = lstrlen(LineWithCaret->Text);
      }
    else
      return FALSE ;
  return TRUE ;
  }


HANDLE hText = NULL;
HANDLE hData;
LPSTR  lpData;

BOOL TextBlock::CopySelectedTextToGlobalHandle (LPHANDLE hText)
  {
  SelStruct SelStart, SelEnd;

  // SelStart ist jetzt auf alle Faelle kleiner als SelEnd !
  GetSelectionFromTopToBottom (&SelStart, &SelEnd);

  int TextLen = 0;

  if (SelStart.Row == SelEnd.Row) {    // Selektion in der selben Zeile
    int tlen = lstrlen(SelStart.Line->Text);
    int end = min(SelEnd.Col,tlen);
    int start = min(SelStart.Col,tlen);
    TextLen = end - start + 1;  
    }
  else {
    for (LPLINE l = SelStart.Line; l != NULL; l = l->Next) {
      int tlen = lstrlen(l->Text);
      if (l == SelEnd.Line) {
        int end = min(SelEnd.Col,tlen);
        TextLen += end + 1;        // "\0"
        break;
        }
      if (l == SelStart.Line) {
        int start = min(SelStart.Col,tlen);
        TextLen = tlen - start + 2; // "\r\n"
        } 
      else {
        TextLen += tlen + 2;          // Laenge der ganzen Zeile
        }  
      }  
    }
      
  // Speicher fuer den String reservieren  
  *hText = GlobalAlloc(GHND, TextLen);
  LPSTR lpszText = (LPSTR)GlobalLock(*hText);
  if ((*hText == NULL) || (lpszText == NULL))
    return FALSE;
    
  lmemset (lpszText, '\0', TextLen);

  if (SelStart.Row == SelEnd.Row) {
    int tlen = lstrlen(SelStart.Line->Text);
    int start = min(SelStart.Col,tlen);
    lmemcpy (lpszText, SelStart.Line->Text+start, TextLen - 1);
    lpszText[TextLen-1] = '\0' ;
    }
  else {  
    LPSTR h = lpszText ;
    for (LPLINE l = SelStart.Line; l != NULL; l = l->Next) {
      int tlen = lstrlen(l->Text);
      if (l == SelEnd.Line) {
        int end = min(SelEnd.Col,tlen);
        if (end > 0)
          lmemcpy (h,l->Text,end) , h += end ;
        *h = '\0' ;

        break;
        }
      if (l == SelStart.Line) {
        // von der Markierung bis zum Ende der Zeile
        int start = min(SelStart.Col,tlen);
        int len = tlen - start ;
        if (len > 0)
          lmemcpy (h,l->Text+start,len) , h += len ;
        lstrcpy (h, "\r\n") , h += 2 ;
        } 
      else {
        lmemcpy (h,l->Text,tlen) , h += tlen;  // die ganze Zeile
        lstrcpy (h, "\r\n") , h += 2 ;
        }  
      }  
    }

  GlobalUnlock (*hText);
  return TRUE;
  }

//----------------------------------------------------------------------------
// kopiert selektierten Text in die Zwischenablage
//----------------------------------------------------------------------------
BOOL TextBlock::CopyToClipBoard (HWND hWnd)
  {
  // wenn nichts selektiert ist, dann sollte die ganze aktive
  // Zeile in der Zwischenablage gespeichert werden.
  if (!AlreadySelected) {
    SetSelection (LineWithCaret, LineWithCaret->Next);
    AlreadySelected = FALSE;        // Flag sofort wieder weg!
    }

  if (hText != NULL) {
    GlobalFree (hText);
    hText = NULL;
    }

  CopySelectedTextToGlobalHandle (&hText);

  LPSTR lpszText;

  if (hText != NULL) {
    hData = GlobalAlloc (GMEM_MOVEABLE, GlobalSize(hText));
    if ((hData == NULL) || (lpData = (LPSTR)GlobalLock(hData)) == NULL ||
                           (lpszText = (LPSTR)GlobalLock(hText)) == NULL) {
//        OutOfMemory();
      return FALSE;
      }                     

    lstrcpy (lpData, lpszText);
    GlobalUnlock (hData);
    GlobalUnlock (hText);

    if (OpenClipboard(hWnd)) {
      EmptyClipboard();
      SetClipboardData (CF_TEXT, hData);
      CloseClipboard();
      }

    hData = NULL;  
    }
    
  // Sonderfall wenn nichts selektiert war!
  if (!AlreadySelected) {
    AlreadySelected = TRUE;   // so tun als ob!
    InvalidateSelectedLines (hWnd);
    SetSelection (NULL, NULL);
    }

  return TRUE;  
  }


//============================================================================
// Funktion: TextBlock::DeleteSelectedLines
//
// Zweck:    selektierten Text loeschen
//============================================================================
BOOL TextBlock::DeleteSelectedLines (HWND hWnd)
  {
  if (!AlreadySelected)
    return FALSE;

  if (hText != NULL) {
    GlobalFree (hText);
    hText = NULL;
    }

  SelStruct SelStart, SelEnd;

  // SelStart ist jetzt auf alle Faelle kleiner als SelEnd !
  GetSelectionFromTopToBottom (&SelStart, &SelEnd);

  //---------------------------------
  // Selektion innerhalb einer Zeile
  //---------------------------------
  if (SelStart.Row == SelEnd.Row) {
    SelStart.Line->DeleteText (SelStart.Col, SelEnd.Col);
    }
  else {
    for (LPLINE l = SelStart.Line; (l != NULL); ) {
      //--------------------------------------
      // das ist also das Ende der Selektion
      //--------------------------------------
      if (l == SelEnd.Line) {
        int tlen = lstrlen(l->Text);

        // Rest der letzten Zeile an die erste Zeile anhaengen
        if (SelEnd.Col < tlen)
          SelStart.Line->InsertText (SelEnd.Line->Text + SelEnd.Col,lstrlen(SelStart.Line->Text));

        DelLine (SelEnd.Line, NULL);     // letzte Zeile loeschen

        LineWithCaret = SelStart.Line ;
        break;
        }
      //---------------------------------------
      // das ist also der Anfang der Selektion
      //---------------------------------------
      if (l == SelStart.Line) {
        int tlen = lstrlen(l->Text);
        //-----------------------------------
        // Selektion innerhalb des Textes?
        //-----------------------------------
        if (SelStart.Col < tlen)
          l->DeleteText (SelStart.Col, tlen);
        else {
          //------------------------------
          // oder bin ich im Whitespace?
          //------------------------------
          if (SelStart.Col > tlen) {
            int len = SelStart.Col - tlen ;
            LPSTR spaces = LPSTR (GetGlobMem (len + 1));
            lmemset (spaces,' ',len);
            l->InsertText (spaces,tlen);
            FreeGlobMem (spaces);
            }
          }

        l = l->Next;
        }
      else {
        //-----------------------------------------------------
        // weder Anfang noch Ende =>  die ganze Zeile loeschen
        //-----------------------------------------------------
        BOOL isLastLine = (l->Next == NULL);
        l = DelLine (l, NULL);  // zeigt automatisch auf den naechsten Satz
        if (isLastLine) break ; // Sollte eigentlich nicht passieren, da vorher Ende der Selektion,
                                // aber wer weiss
        }
      }  // end for
    }

#ifdef ANALYSELINE
  //---------------------------------------------------------------------
  //vorsichtshalber den ganzen Text vom Beginn der Selektion analysieren
  //---------------------------------------------------------------------
  AnalyseLines (SelStart.Line, NULL, TRUE);
#endif
  

  iCaret = SelStart.Col;
  SetNewCPos (hWnd);
        
  StartSel.Col = 0;
  StartSel.Row = 0;
  StartSel.Line = NULL;
  EndSel.Col = 0;
  EndSel.Row = 0;
  EndSel.Line = NULL;
  AlreadySelected = FALSE;

  RECT rc;
  GetClientRect (hWnd, &rc);
  rc.top = YCaret * charHeight;
  InvalidateRect (hWnd, &rc, TRUE);
  
  if (!ModifyDone) {
    ModifyDone = TRUE ;
    SetCaption (hWnd);
    }

  return TRUE;
  }

//---------------------  InsertLinesInTextFromBuffer  -----------------------
//
// Fuegt an der aktuellen Cursor-Position einen Text ein.
// Dieser Text kann aus mehreren Zeilen bestehen, die aber jeweils durch
// CR-LF getrennt werden muessen. Das Caret wird nach dem Einfuegen an das 
// Ende des eingefuegten Textes bewegt.
//---------------------------------------------------------------------------
#define MAXBUFLEN 512
BOOL TextBlock::InsertLinesInTextFromBuffer (HWND hWnd, LPSTR lpszText)
  {
  int OldYCaret = YCaret;
  int i = 0;
  int strpos = -1;  // Position im gesamten Text
  int len;          // Laenge eines Satzes
  LPSTR t;
  LPLINE SaveLine;

  RECT rc;
  GetClientRect (hWnd, &rc);

  // Befindet sich das Caret bereits so weit unten, daß der vorhergehende
  // Aufruf von "SetNewCPos" ein "ScrollWindow" verursachte, so muß der zu
  // invalidierende Bereich etwas weiter hoeher (-2) angesetzt werden.
  rc.top = (OldYCaret - 2) * charHeight;
  InvalidateRect (hWnd, &rc, FALSE);

#ifdef ANALYSELINE
  SaveLine = LineWithCaret;
//  StartLineForAnalyse = LineWithCaret;
#endif

  for (LPSTR p = lpszText; *p; i++) {   // alle Saetze durchgehen
    t = p;
    // setzt einmal den Hilfszeiger t auf das Ende des ersten Satzes
    for (len = 0 ; (*t && (*t != '\r') && (*t != '\n')) ; t++, len++, strpos++);
    
    BOOL bLineBreak = ((*t == '\r') || (*t == '\n'));   // CR-LF ist im Text
    LPSTR szBuf = LPSTR (GetGlobMem (len + 1));
    if (len)
      lmemcpy (szBuf, p, len);   // Eine Zeile aus der Ablage
    else
      *szBuf = '\0' ;
    if (bLineBreak) {
      LineBreak (FALSE);   // in LineWithCaret passiert ein Zeilenumbruch
      if (*szBuf)
        LineWithCaret->InsertText (szBuf, iCaret);  // Text im Satz einfuegen
      LineWithCaret = LineWithCaret->Next;
      iCaret = 0;
      }
    else  
      iCaret = LineWithCaret->InsertText (szBuf, iCaret);  // Text im Satz einfuegen

    if (*t == '\0')
      break;
      
    if (*t == '\r') { t++ , strpos++; }
    if (*t == '\n') { t++ , strpos++; }

    p = lpszText+strpos+1;  // um einen Satz weitergehen

    FreeGlobMem (szBuf);
    }

  SetNewCPos (hWnd);

  if (!ModifyDone) {
    ModifyDone = TRUE ;
    SetCaption (hWnd);
    }

#ifdef ANALYSELINE
  AnalyseLines (SaveLine, NULL, TRUE);
#endif


  return TRUE;
  }

//----------------------------------------------------------------------------
// Text aus der Zwischenablage einfuegen
//----------------------------------------------------------------------------
BOOL TextBlock::PasteFromClipBoard (HWND hWnd)
  {
  if (OpenClipboard(hWnd)) {
    HANDLE hClipData;
    LPSTR lpClipData;
    LPSTR lpszText;
      
    if (((hClipData = GetClipboardData(CF_TEXT)) == NULL) && (!AlreadySelected)) {
      CloseClipboard();
      return FALSE;
      }

    if (hText != NULL) {
      GlobalFree (hText);
      hText = NULL;
      }
        
    hText = GlobalAlloc(GMEM_MOVEABLE, GlobalSize(hClipData));
    if ((hText == NULL) || (lpClipData = (LPSTR)GlobalLock(hClipData)) == NULL ||
                           (lpszText = (LPSTR)GlobalLock(hText)) == NULL) {
      CloseClipboard();
      return FALSE;
      }  

    lstrcpy (lpszText, lpClipData);
    GlobalUnlock (hClipData);
    CloseClipboard();
    GlobalUnlock (hText);

    return InsertLinesInTextFromBuffer (hWnd, lpszText);
    }
  else  
    return FALSE;

  }
  
//============================================================================
// Funktion:  TextBlock::DelActChar ()
//
//
//============================================================================
void TextBlock::DelActChar ()
  {
  if ((LineWithCaret->Text[iCaret] == '\0') && (LineWithCaret->Next != NULL)) {
    // letztes Zeichen geloescht => untere Zeile kommt nach oben
    LPSTR nTxt = LPSTR (GetGlobMem (lstrlen (LineWithCaret->Text) + 
                                    lstrlen (LineWithCaret->Next->Text) + 1
                                   )
                       );
    lstrcpy (nTxt,LineWithCaret->Text);
    lstrcat (nTxt,LineWithCaret->Next->Text);
    FreeGlobMem (LineWithCaret->Text);                     
    LineWithCaret->Text = nTxt;
    DelLine (LineWithCaret->Next, NULL);
    LineChanged = TRUE ;
    }
  else if (LineWithCaret->Text[iCaret] != '\0') {
    // Normalfall
    LPSTR nTxt = LPSTR (GetGlobMem (lstrlen (LineWithCaret->Text)));
    lmemcpy (nTxt,LineWithCaret->Text,iCaret);
    lstrcat (nTxt,LineWithCaret->Text+iCaret+1);
    FreeGlobMem (LineWithCaret->Text);
    LineWithCaret->Text = nTxt;
    }
  // else am ende des Buffers
  }


//============================================================================
// Funktion:  IsAnalyseChar
//
// Zweck:     Ueberprueft auf die Eingabe von Zeichen, die ein spezielles 
//            Handling fuer das Syntax-Coloring erfordern.
//============================================================================
#ifdef ANALYSELINE
BOOL IsAnalyseChar (char ch)
  {
  return ((ch == '"') || (ch == '\\')/* || (ch == '$')*/);
  }
#endif


//============================================================================
// Funktion:  TextBlock::DelCharUnder ()
//
//
//============================================================================
void TextBlock::DelCharUnder ()
  {
#ifdef ANALYSELINE
  BOOL bAnalyseFull = FALSE;
#endif

  LPLINE oLineWithCaret = LineWithCaret;
  int oiCaret = iCaret;
  if (GetAsyncKeyState (VK_CONTROL) < 0)
    NextWord (TRUE);
  else
    CheckNextChar ();                              
  LPLINE eLineWithCaret = LineWithCaret ;
  int eiCaret = iCaret ;
  LineWithCaret = oLineWithCaret ;
  iCaret = oiCaret ;
  for (int i = 0 ; ((LineWithCaret != eLineWithCaret) || (iCaret != eiCaret)) ; i++ ) {

#ifdef ANALYSELINE
    if (IsAnalyseChar (LineWithCaret->Text[iCaret]))
//      bAnalyseFull = TRUE;
      bAnalyseFull = !bAnalyseFull;
#endif

    if (!CheckNextChar()) break ;
    }
  LineWithCaret = oLineWithCaret ;
  iCaret = oiCaret ;
  for (int j = 0 ; j < i ; j++)
    DelActChar ();

#ifdef ANALYSELINE
  //--------------------------------------------------------------------
  // Vorsichtshalber einmal die aktuelle Zeile analysieren, und schauen
  // was wir da alles finden
  //--------------------------------------------------------------------
  AnalyseLines (LineWithCaret, LineWithCaret);

  DWORD CurState = LineWithCaret->GetAnalyseStatus (iCaret);
  if ((CurState == ANALYSE_STATE_INIT) || (CurState == ANALYSE_STATE_QUOTAINIT) ||
      (CurState == ANALYSE_STATE_COMMENT)) {
    if (bAnalyseFull)
      AnalyseLines (LineWithCaret, NULL, TRUE);
    else
      if (LineWithCaret->State == ANALYSE_STATE_QUOTAINIT)
        AnalyseLines (LineWithCaret, NULL, TRUE);
      else
        AnalyseLines (LineWithCaret, LineWithCaret);
    }
#endif
  }

//============================================================================
// Funktion:  TextBlock::DelLineWithCaret
//
// Zweck:  Löscht die ganze Zeile in der sich das Caret befindet
//============================================================================
void TextBlock::DelLineWithCaret (HWND hWnd)
  {
  if (LineWithCaret->Next != NULL) {
    LineWithCaret = DelLine (LineWithCaret, NULL);

#ifdef ANALYSELINE
    if ((LineWithCaret->Prev != NULL) && (LineWithCaret->Prev->State == ANALYSE_STATE_QUOTAINIT) ||
        (LineWithCaret->State == ANALYSE_STATE_QUOTAINIT))
      AnalyseLines (LineWithCaret, NULL, TRUE);
    else
      AnalyseLines (LineWithCaret, LineWithCaret);
#endif
    }
  else
    LineWithCaret->DeleteText (0,lstrlen(LineWithCaret->Text));

  RECT rc;
  GetClientRect (hWnd, &rc);
  rc.top = YCaret * charHeight;
  InvalidateRect (hWnd, &rc, FALSE);
  
  if (!ModifyDone) {
    ModifyDone = TRUE ;
    SetCaption (hWnd);
    }
  }


//============================================================================
// Funktion:  TextBlock::DelPrevChar
//
// Zweck:  Loescht das Zeichen oder das Wort vor dem Caret
//============================================================================
void TextBlock::DelPrevChar ()
  {
#ifdef ANALYSELINE
  BOOL bAnalyseFull = FALSE;
#endif

  LPLINE oLineWithCaret = LineWithCaret;
  int oiCaret = iCaret;

  if (GetAsyncKeyState (VK_CONTROL) < 0)
    PrevWord (TRUE);
  else
    CheckPrevChar ();

  // Bin ich jetzt schon in einer anderen Zeile?
  LPLINE sLineWithCaret = LineWithCaret ;
  int siCaret = iCaret ;
  for (int i = 0 ; ((LineWithCaret != oLineWithCaret) || (iCaret != oiCaret)) ; i++ , CheckNextChar()) ;
  LineWithCaret = sLineWithCaret ;
  iCaret = siCaret ;
  for (int j = 0 ; j < i ; j++) {
#ifdef ANALYSELINE
    if (LineWithCaret->GetAnalyseStatus (iCaret) == ANALYSE_STATE_QUOTAINIT)
      if (IsAnalyseChar (LineWithCaret->Text[iCaret]))
        bAnalyseFull = TRUE;
#endif
    DelActChar ();
    }

#ifdef ANALYSELINE
  //--------------------------------------------------------------------
  // Vorsichtshalber einmal die aktuelle Zeile analysieren, und schauen
  // was wir da alles finden
  //--------------------------------------------------------------------
  AnalyseLines (LineWithCaret, LineWithCaret);

  if (bAnalyseFull)
    AnalyseLines (LineWithCaret, NULL, TRUE);
  else
    if (LineWithCaret->State == ANALYSE_STATE_QUOTAINIT)
      AnalyseLines (LineWithCaret, NULL, TRUE);
    else
      AnalyseLines (LineWithCaret, LineWithCaret);
#endif
  }


void TextBlock::End ()
  {
  LineWithCaret = LastLine ;
  iCaret = lstrlen (LineWithCaret->Text);
  }


//============================================================================
// TextBlock::FindMatchingbraces
//
//============================================================================
#define  MATCHFORWARD  0
#define  MATCHBACKWARD 1

struct Matches {
  char   ActChar;
  char   SearchChar;
  short  Direction;
  short  MatchCount;
  };


void TextBlock::FindMatchingBraces (HWND hWnd, BOOL bJump, BOOL bMove)
  {
  Matches  m;
  char     outtxt[128];

  BOOL     bMatchFound = FALSE;
  BOOL     bComment = FALSE;
  char     ch;

  if (!bMove || (iCaret > lstrlen(LineWithCaret->Text)))
    ch = '\0';
  else
    ch = LineWithCaret->Text[iCaret];

  switch (ch) {
    case '(' :
      m.SearchChar = ')';
      m.Direction = MATCHFORWARD;
      break;

    case '{' :
      m.SearchChar = '}';
      m.Direction = MATCHFORWARD;
      break;

    case ')' :
      m.SearchChar = '(';
      m.Direction = MATCHBACKWARD;
      break;

    case '}' :
      m.SearchChar = '{';
      m.Direction = MATCHBACKWARD;
      break;

    default:
      {
      BOOL bClearStatus = FALSE;
      if (StartBrace.Line != NULL) {
        StartBrace.Line->ClearStartBrace ();
        InvalidateLine (hWnd, StartBrace.Line);
        StartBrace.Line = NULL;
        bClearStatus = TRUE;
        }

      if (EndBrace.Line != NULL) {
        EndBrace.Line->ClearEndBrace ();
        InvalidateLine (hWnd, EndBrace.Line);
        EndBrace.Line = NULL;
        bClearStatus = TRUE;
        }

//        outtxt[0] = '\0';
//        SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
      }
      return;
    }

#ifdef ANALYSELINE
  if (LineWithCaret->GetAnalyseStatus(iCaret) != ANALYSE_STATE_INIT)
    return;
#else
  //--------------------------------------------------
  // Ist das jetzt eine Klammer nach einem Kommentar?
  //--------------------------------------------------
  if (iCaret > 0) {
    bComment = FALSE;
    int j = iCaret - 1;
    for ( ; (LineWithCaret->Text[j] != '\0') ; j--) {
      if ((LineWithCaret->Text[j] == '$') && (iCaret > j)) {
        bComment = TRUE;
        break;
        }
      }

    if (bComment)  // diese Klammern interessieren mich nicht!
      return;
    }
#endif

  m.ActChar = ch;
  m.MatchCount = 1;
  short xPos = m.Direction == MATCHFORWARD ? iCaret + 1 : iCaret - 1;
  short YOffset = 0;

  for (LPLINE l = LineWithCaret; (l != NULL) && !bMatchFound; ) {

    //--------------------------------------------------
    // Ist das jetzt eine Klammer nach einem Kommentar?
    //--------------------------------------------------
#ifndef ANALYSELINE
    bComment = FALSE;
    int j = xPos - 1;
    for ( ; (j >= 0) && (l->Text[j] != '\0') ; j--) {
      if ((l->Text[j] == '$') && (xPos > j)) {
        bComment = TRUE;
        break;
        }
      }
#endif

    if (!bComment) {

      ch = l->Text[xPos];
      for ( ; (ch != '\0') && !bMatchFound; ) {

        //--------------------------------------------------------------------
        // bei einem Kommentar in der Zeile wird diese Zeile sofort verlassen
        //--------------------------------------------------------------------
//        if (ch == '$')
//          break;

        //--------------------------------------------------------------------
        // bei einem gleichen Zeichen wie dem Gesuchten wird der 
        // Klammer-Zaehler erhoeht
        //--------------------------------------------------------------------
#ifdef ANALYSELINE
        if (l->GetAnalyseStatus(xPos) == ANALYSE_STATE_INIT) {
#endif

        if (ch == m.ActChar)
          m.MatchCount++;

        if (ch == m.SearchChar) {
          if (--m.MatchCount == 0) {
            bMatchFound = TRUE;
            break;
            }
          }

#ifdef ANALYSELINE
          }
#endif

        ch = l->Text[(m.Direction == MATCHFORWARD ? ++xPos : --xPos)];
        }
      }

    if (!bMatchFound) {

      YOffset++;
      if (m.Direction == MATCHFORWARD) {
        xPos = 0;
        l = l->Next;
        }
      else {
        l = l->Prev;
        if (l != NULL)
          xPos = lstrlen(l->Text) - 1;
        }
      }

    }

  if (bJump) {
    if ((l != NULL) && (xPos >= 0)) {
      iCaret = xPos;
      LineWithCaret = l;
      SetNewCPos (hWnd);
      }
    else {
      MessageBox (hWnd, "No matching brace found", "RESTOOL", MB_OK);
      }
    }
  else {
    if ((LineWithCaret != NULL) && (l != NULL)) {
      StartBrace.Col = m.Direction == MATCHFORWARD ? iCaret : xPos;
      StartBrace.Line = m.Direction == MATCHFORWARD ? LineWithCaret : l;
      StartBrace.Line->SetStartBrace ();

      EndBrace.Col = m.Direction == MATCHFORWARD ? xPos : iCaret;
      EndBrace.Line = m.Direction == MATCHFORWARD ? l : LineWithCaret;
      EndBrace.Line->SetEndBrace ();

      InvalidateLine (hWnd, LineWithCaret);
      InvalidateLine (hWnd, l);

      if (m.Direction == MATCHFORWARD) 
        ++YOffset;
      else
        YOffset = -(--YOffset);
      
      wsprintf (outtxt, "Matching brace found at line %d col %d", YAbsCaret+YOffset, ++xPos);
      }
    else {
      lstrcpy (outtxt, "No matching brace found");
      MessageBeep (0);
      }

//    SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
    }
  }

//----------------------------------------------------------------------------
// Berechnet an Hand der Zeile in der sich das Caret befindet die absoluten
// (gesamter Text-Puffer) und relativen (sichtbar am Schirm) Positionen des 
// Carets, sowie die y-Position der ersten sichtbaren Zeile in Bildpunkten
//----------------------------------------------------------------------------
void TextBlock::GetNewCaretPos ()
  {
  LONG yl = 0; 
  yFirstVisible = 0L;
  BOOL lFound = FALSE, aFound = FALSE ;
  for (LPLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if (h == LineWithCaret)  lFound = TRUE ;
    if (h == FirstVisibleLine) aFound = TRUE ;
    if ((lFound) && (aFound))     // beim Caret angelangt, dann raus!
      break ;
    if (!lFound) 
      yl += charHeight ;          // die echte Position im gesamten Text (absolut)
    if (!aFound) 
      yFirstVisible += charHeight ;  // die erste sichtbare Zeile im gesamten Text
    }

  xScroll = GetXMin() + iCaret * charWidth - x0 ;
  yScroll = yl - yFirstVisible ;    // Position Text innerhalb des Fensters (relativ)

  YCaret = int (yScroll/LONG(charHeight));
  YAbsCaret = int (yl/LONG(charHeight));
  }

//-----------------------------------------------------------------------------
// Rueckgabewert: Y-Position innerhalb des Fensters
//-----------------------------------------------------------------------------
int TextBlock::GetYPos (LPLINE l)
  {
  int y = 0;
  for (LPLINE h = FirstVisibleLine; ((h != NULL) && (h != l)) ; h = h->Next , y += charHeight) ;
  return y;
  }

void TextBlock::GiveCaretTo (HWND hWnd)
  {
  if (!bCaretExists) {
    CreateCaret (hWnd,NULL,2,charHeight);
    ShowCaret (hWnd);
    cshown = TRUE ;
    bCaretExists = TRUE ;
    }
  }

void TextBlock::HideCaretFrom (HWND hWnd)
  {
  if (cshown)
    HideCaret (hWnd);
  cshown = FALSE ;
  }


inline void TextBlock::Home ()
  {
  LineWithCaret = FirstLine ;
  iCaret = 0;
  }

//============================================================================
// Funktion:  TexBlock::InsertChar
//
// Zweck: Fuegt ein Zeichen in die aktuelle Zeile ein
//============================================================================
void TextBlock::InsertChar (char ch)
  {
  LPSTR nTxt;
  // einfuegen innerhalb des Textes
  if (!IsCaretBehindLine ()) {
    nTxt = LPSTR (GetGlobMem (lstrlen(LineWithCaret->Text)+2)); 
    lmemcpy (nTxt, LineWithCaret->Text, iCaret);  // alten Text bis zum Caret rein
    nTxt[iCaret] = ch;                            // neues Zeichen dazu
    lstrcpy (nTxt+iCaret+1,LineWithCaret->Text+iCaret); // Rest vom alten Text

    FreeGlobMem (LineWithCaret->Text);     // den alten Text brauch ich nicht mehr
    LineWithCaret->Text = nTxt;            // ich will lieber den neuen

#ifdef ANALYSELINE
    if ((iCaret == 0) && IsAnalyseChar(ch))
      AnalyseLines (LineWithCaret, NULL, TRUE);
    else {
      if (LineWithCaret->GetAnalyseStatus (iCaret-1) != ANALYSE_STATE_COMMENT)
        if (IsAnalyseChar(ch))
          AnalyseLines (LineWithCaret, NULL, TRUE);
        else
          if (LineWithCaret->State == ANALYSE_STATE_QUOTAINIT)
            AnalyseLines (LineWithCaret, NULL, TRUE);
          else
            AnalyseLines (LineWithCaret, LineWithCaret, FALSE);
      }
#endif

    NextChar ();                           // und das Caret um 1 weiter
    }
/*
  // Caret befand sich bereits ausserhalb des Textes
  else {
    InsertSpacesFromLineEndToCaret ();
    NextChar ();
    nTxt[iCaret] = ch;                     // und dann das Zeichen
    nTxt[iCaret+1] = '\0';                 // mit Zero-Terminator
    }
*/
  }

//============================================================================
// Funktion:  TextBlock::InsertSpacesFromLineEndToCaret
//
// Zweck: Befindet sich das Caret hinter dem gueltigen Text (sog. WhiteSpace)
//        wird der Text vom Textende bis zum Caret mit Leerzeichen gefuellt.
//============================================================================
void TextBlock::InsertSpacesFromLineEndToCaret ()
  {
  LPSTR nTxt = LPSTR (GetGlobMem (iCaret+2)); 
  int TextLen = lstrlen(LineWithCaret->Text);   // Text ohne '\0'
  lmemcpy (nTxt, LineWithCaret->Text, TextLen);
  for (int i = TextLen; i < iCaret; i++) // bis zum Caret mit Leerzeichen fuellen
    nTxt[i] = ' ';
  nTxt[iCaret] = '\0';

  FreeGlobMem (LineWithCaret->Text);
  LineWithCaret->Text = nTxt;
  }

//============================================================================
// Funktion:  TextBlock::InvalidateSelectedLines
//
// Zweck:  invalidiert jene Zeilen die von der Selektion betroffen sind
//============================================================================
void TextBlock::InvalidateSelectedLines (HWND hWnd) 
  {
  if (AlreadySelected && (StartSel.Line != NULL) && (EndSel.Line != NULL)) {
    RECT rc;
    GetClientRect (hWnd, &rc);
    
    GetNewCaretPos ();
    
    if (StartSel.Row < EndSel.Row) {
      rc.top = int (LONG (StartSel.Row) * LONG (charHeight) - yFirstVisible);
      rc.bottom = int (LONG (EndSel.Row+1) * LONG (charHeight) - yFirstVisible);
      }
    else {
      rc.top = int (LONG (EndSel.Row) * LONG (charHeight) - yFirstVisible);
      rc.bottom = int (LONG (StartSel.Row+1) * LONG (charHeight) - yFirstVisible);
      }  

    InvalidateRect (hWnd, &rc, FALSE);
    }
  }

//============================================================================
// Funktion:  TextBlock::InvalidateLine
//
// Zweck:  Invalidiert die Zeile die in <l> uebergeben wurde
//============================================================================
void TextBlock::InvalidateLine (HWND hWnd,LPLINE l) 
  {
  int y = 0;
  RECT rc,rcClient;
  SetRectEmpty (&rc);
  GetClientRect (hWnd, &rcClient);

  for (LPLINE h = FirstVisibleLine ; h != NULL ; h = h->Next) {
    // Rechteck in dem die Zeile geschrieben wird
    if (h == l) {
      SetRect (&rc, XMIN, y, rcClient.right, y+charHeight);
      break ;
      }
    y += charHeight;
    }

  if (!IsRectEmpty (&rc))
    InvalidateRect (hWnd, &rc, FALSE);
  }


//----------------------------------------------------------------------------
inline BOOL TextBlock::IsWordChar (char ch, BOOL allowPoint)
  {
  return IsCharAlphaNumeric (ch) || 
         ((ch != '\0') && (strchr (extraWordChars, ch) != NULL)) || 
         (allowPoint && (ch == '.'));
  }

//----------------------------------------------------------------------------
inline BOOL IsVertMove (WORD wP)
  {
  return ((wP == VK_UP) || (wP == VK_DOWN) || 
          (wP == VK_PRIOR) || (wP == VK_NEXT));
  }

//----------------------------------------------------------------------------
inline BOOL IsHorMove (WORD wP)
  {
  return !IsVertMove (wP);
  }

//----------------------------------------------------------------------------
// Rueckgabewert: TRUE wenn eine der Cursortasten gedrueckt wurde
//----------------------------------------------------------------------------
inline BOOL IsMovementKey (WORD KeyCode)
  {
  return ((KeyCode == VK_UP)    || (KeyCode == VK_DOWN)  ||
          (KeyCode == VK_LEFT)  || (KeyCode == VK_RIGHT) ||
          (KeyCode == VK_PRIOR) || (KeyCode == VK_NEXT)  ||
          (KeyCode == VK_HOME)  || (KeyCode == VK_END));
  }

//---------------  LineBreak  ------------------------------------------------
//
// Wird aufgerufen nach Druecken der Taste ENTER in einer Textzeile
//----------------------------------------------------------------------------
void TextBlock::LineBreak (BOOL MoveCaret)
  {
  LPLINE oLineWithCaret = LineWithCaret;

  int i = 0;
  if (MoveCaret) {
    
    // Anzahl der Leerzeichen in der Vorgaengerzeile ermitteln
    if (LineWithCaret != NULL)
      for ( ; LineWithCaret->Text[i] == ' '; i++);
    
    int   len;
    LPSTR txt;      // die neue Zeile
    
    // ist das Caret noch im Leerzeichen-Bereich?
    if (iCaret <= i) {
      len = lstrlen(LineWithCaret->Text) + 1;
      txt = LPSTR(GetGlobMem (len));
      lmemcpy (txt, LineWithCaret->Text, len); // Zeile nach unten schieben!
      i = iCaret;
      }
    else {
      // Zeile nach dem Caret nach unten schieben
      len = lstrlen(LineWithCaret->Text) - iCaret;
      txt = LPSTR(GetGlobMem (len + i + 1));
      for (int j = 0 ; j < i; txt[j++] = ' ');
      lmemcpy (txt+i, LineWithCaret->Text + iCaret, len);
      }

    InsertLineBehind (LineWithCaret, txt);
    FreeGlobMem (txt);
    }
  else
    InsertLineBehind (LineWithCaret, LineWithCaret->Text+iCaret);

  // Die Zeile in der der Cursor zuletzt war
  LPSTR nTxt = LPSTR (GetGlobMem (iCaret+1));
  lmemcpy (nTxt,LineWithCaret->Text,iCaret);
  FreeGlobMem (LineWithCaret->Text);
  LineWithCaret->Text = nTxt;
  if (MoveCaret) {
    LineWithCaret = LineWithCaret->Next;
    if (LineWithCaret != NULL) {
//      iCaret = lstrlen(LineWithCaret->Text);
      iCaret = i;
      }
    else
      CheckNextChar ();
    }
    
#ifdef ANALYSELINE
  AnalyseLines (oLineWithCaret, NULL, TRUE);
#endif
  }

//----------------------------------------------------------------------------
inline void TextBlock::LineBeg ()
  {
  iCaret = 0;
  }

//----------------------------------------------------------------------------
inline void TextBlock::LineEnd ()
  {
  iCaret = lstrlen(LineWithCaret->Text);
  }

//----------------------------------------------------------------------------
// verschiebt einen ganzen Block entweder nach links oder nach rechts!
//----------------------------------------------------------------------------
void TextBlock::MoveBlock (HWND hWnd, BOOL MoveLeft)
  {
  SelStruct SelStart, SelEnd;
  char szSpace[2] = " ";

  // SelStart ist jetzt auf alle Faelle kleiner als SelEnd !
  GetSelectionFromTopToBottom (&SelStart, &SelEnd);

  for (LPLINE l = SelStart.Line; ((l != NULL) && (l != SelEnd.Line)); l = l->Next) {
    if (MoveLeft) {
      if (l->Text[0] == ' ')       // erstes Zeichen ein Leerzeichen?
        l->DeleteText (0, 1);      // dann entferne es!
      }
    else {
      l->InsertText (szSpace, 0);  // fuege ein Leerzeichen an der ersten Spalte ein
      }

#ifdef ANALYSELINE
    AnalyseLines (l, l);
#endif
    }

  InvalidateSelectedLines (hWnd);
  }


//----------------------------------------------------------------------------
inline void TextBlock::NextChar ()
  {
  iCaret ++;
  }

//----------------------------------------------------------------------------
inline void TextBlock::NextLine ()
  {
  if (LineWithCaret->Next != NULL)
    LineWithCaret = LineWithCaret->Next ;
  }

//----------------------------------------------------------------------------
void TextBlock::NextSide (HWND hWnd)
  {
  RECT r;
  GetClientRect (hWnd,&r);
  int AnzLines = r.bottom / charHeight - 1;
  for (int i = 0 ; i < AnzLines ; i ++) {
    NextLine ();
/*
    if (FirstVisibleLine->Next != NULL)
      FirstVisibleLine = FirstVisibleLine->Next;
*/
    }

/*
  RECT rc;
  GetClientRect (hWnd, &rc);
  int sPos = rc.bottom / charHeight;
#ifdef WIN32
  SendMessage (hWnd,WM_VSCROLL,MAKEWPARAM(SB_THUMBPOSITION, sPos), 0);
#else
  SendMessage (hWnd,WM_VSCROLL,SB_THUMBPOSITION,MAKELPARAM(sPos, 0));
#endif

  InvalidateRect (hWnd, NULL, TRUE);
*/
  }

//----------------------------------------------------------------------------
void TextBlock::NextWord (BOOL forDelete)
  {
  BOOL wordStopAtWordEnd;
  BOOL wordStopAtEOL;
  if (AlreadySelected) {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_SELECT_SHIFT) & WORDSTOP_RIGHT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_SELECT_SHIFT) & WORDSTOP_RIGHT_EOL) != 0;
    }
  else if (forDelete) {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_DELETE_SHIFT) & WORDSTOP_RIGHT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_DELETE_SHIFT) & WORDSTOP_RIGHT_EOL) != 0;
    }
  else {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_JUMP_SHIFT) & WORDSTOP_RIGHT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_JUMP_SHIFT) & WORDSTOP_RIGHT_EOL) != 0;
    }
  for ( BOOL spaceFound = FALSE, firstCharacter = TRUE, betweenWords = FALSE ; ; ) {
    LPLINE oLineWithCaret = LineWithCaret;
    int oiCaret = iCaret;
    if (!IsWordChar (LineWithCaret->Text[iCaret])) { // kein Buchstabe oder Ziffer
      if (firstCharacter)
        betweenWords = TRUE;
      else 
        if ((wordStopAtEOL && (LineWithCaret->Text[iCaret] == 0)) ||
            (!betweenWords && wordStopAtWordEnd))
          break;
      spaceFound = TRUE ;
      }
    else
      if (spaceFound)
        break ;
    CheckNextChar ();
    if ((LineWithCaret == oLineWithCaret) && (iCaret == oiCaret)) break ;
    firstCharacter = FALSE;
    }
  }


/*==========================================================================*\
*  Funktion:  TextBlock::AnalyseLines                                        *
*                                                                            *
*                                                                            *
\*==========================================================================*/
void TextBlock::AnalyseLines (LPLINE StartLine, LPLINE EndLine, BOOL AnalyseAll)
  {
 if (!AnalyseAll && (YAbsCaret < yLastVisibleLine)) {
    if ((EndLine == NULL) || (EndLine != StartLine))
      return;
    }

  if (StartLine == NULL)
//    StartLine = FirstVisibleLine;
    StartLine = LastLineAnalyzed != NULL ? LastLineAnalyzed : FirstVisibleLine;

  if (StartLine == NULL) return;
  if (StartLine == EndLine)
    StartLine->AnalyseLine ();
  else {
    if (EndLine == NULL)
      EndLine = LastVisibleLine;

    for (LPLINE h = StartLine; (h != EndLine) && (h != NULL); h = h->Next) {
      if ((h->AnalyseLine () == FALSE) && !AnalyseAll)
        break;
      }

    LastLineAnalyzed = (h != NULL) && (h->Next != NULL) ? h : LastLine;
    yLastVisibleLine = GetAbsoluteLineNmbr (LastLineAnalyzed) - 1;
    }

  RECT rc;
  GetClientRect (MyWnd, &rc);
  if (StartLine)
    rc.top = GetYPos(StartLine);
//    rc.top = YCaret * charHeight;

  if (StartLine == EndLine)
    rc.bottom = rc.top + charHeight;

  InvalidateRect (MyWnd, &rc, FALSE);
  }


/*==========================================================================*\
*  Funktion:  TextBlock::OnChar                                              *
*                                                                            *
*  Parameter: hWnd .... Fensterhandle                                        *
*             wP ...... ASCII-Code des eingegeben Zeichens                   *
\*==========================================================================*/
#define IV_NOTHING      0
#define IV_LINE         1
#define IV_FROMOLD      2
#define IV_FROMACT      3
#define IV_FULL         4

void TextBlock::OnChar (HWND hWnd,WPARAM wP)
  {
  BOOL bSelectionDeleted = FALSE;

  //---------------------------------------------------------------
  // bei einer Selektion und Taste = TAB => nix tun
  // Hier wird naemlich der selektierte Text ein- oder ausgerueckt
  //---------------------------------------------------------------
  if (AlreadySelected) {
    if ((wP == '\t') || (wP == VK_ESCAPE)) {
      return;
      }
    else {
      if (wP == 255) {
        DeleteSelectedLines (hWnd);
        bSelectionDeleted = TRUE;
        }
      else {
        InvalidateSelectedLines (hWnd);
        StartSel.Row = EndSel.Row;
        StartSel.Col = EndSel.Col;
        StartSel.Line = EndSel.Line;
        SelWord = NULL;
        AlreadySelected = FALSE;
        }
      }
    }  

  LPLINE oLineWithCaret = LineWithCaret;
  int oiCaret = iCaret ;
  int IvMode = IV_NOTHING;

  AlreadySelected = FALSE;  // ab jetzt keine Selektion mehr
  LineChanged = FALSE ;

  if (IsCaretBehindLine ())
    InsertSpacesFromLineEndToCaret ();

  switch (wP) {
    case '\t' :            // TABULATOR
      if (!AlreadySelected)
        if ((iCaret % 2) == 0)
          OnChar (hWnd,' ');
      OnChar (hWnd,' ');
      IvMode = IV_LINE;
      break ;
    case '\r' :            // RETURN
      LineBreak (TRUE);
      IvMode = IV_FROMOLD;
      break ;
    case 255 :
      if (!bSelectionDeleted) {
        DelCharUnder ();
        IvMode = IV_FROMACT;
        }
      break ;
    case '' :
    case '\b' :
      DelPrevChar ();
      IvMode = IV_FROMACT;
      break ;
    case VK_ESCAPE :
      {
      if (ErrorLine != NULL) {
        ErrorLine->ClearErrorLine();
        InvalidateLine (hWnd, ErrorLine);
        ResetFieldColor (hWndStatusbar, STATBAR_TEXT);
        }
      char outtxt[] = "";
      SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
      return;
//      IvMode = IV_LINE;
      }
      break ;

    default :
      if (wP >= 32) {
        InsertChar (char (wP));
        IvMode = IV_LINE;
        }
      break ;
    }
  if (!ModifyDone) {
    ModifyDone = TRUE ;
    SetCaption (hWnd);
    }

/*
#ifdef ANALYSELINE
  if (wP == '"') {
    AnalyseLines (oLineWithCaret);
//    StartLineForAnalyse = oLineWithCaret;
//    IvMode = IV_FULL;
    }
#endif
*/
  FindMatchingBraces (hWnd, FALSE, FALSE);

  // berechnet den zu invalidierenden Textbereich  
  RECT r;
  GetClientRect (hWnd,&r);
  int xstart = r.left;
  int ystart = r.top;
  int yend   = r.bottom;
  switch (IvMode) {
    case IV_LINE :          // Aenderung innerhalb einer Zeile
      xstart = GetXMin() + (iCaret-1) * charWidth - x0 ;
      ystart = GetYPos (LineWithCaret);
      yend   = ystart + charHeight;
      break ;
    case IV_FROMOLD :       // invalidieren ab der vorigen Zeile
      ystart = GetYPos (oLineWithCaret);
      break ;
    case IV_FROMACT :       // invalidieren ab der aktuellen Zeile
      ystart = GetYPos (LineWithCaret);
      if (!LineChanged)
        yend = ystart + charHeight;
      break ;
    }
  r.left = xstart;
  r.top    = ystart;
  r.bottom = yend;
  InvalidateRect (hWnd, &r, FALSE);
//  viCaret = iCaret;
  SetNewCPos (hWnd);
  }

//----------------------------------------------------------------------------
// OnKeyDown
//
//----------------------------------------------------------------------------
void TextBlock::OnKeyDown (HWND hWnd, WPARAM wP)
  {
  RECT rcClient, rcInvalid;
  int OldXCaret;
  int OldYCaret, OldYAbsCaret;

  LPLINE oLineWithCaret = LineWithCaret;
  int oiCaret = iCaret;
  
  ShiftIsDown = GetKeyState(VK_SHIFT) < 0; 
  if (ShiftIsDown && !AlreadySelected) {  // ab jetzt ist SHIFT gedrueckt
    StartSel.Col = iCaret;
    StartSel.Row = YAbsCaret;
    StartSel.Line = LineWithCaret;
    EndSel.Col = StartSel.Col;
    EndSel.Row = StartSel.Row;
    EndSel.Line = StartSel.Line;
    if (IsMovementKey(wP) &&    // eine der Cursor-Bewegungs-Tasten?
       (wP != VK_INSERT) && (wP != VK_DELETE)) // nicht SHIFT-INSERT oder SHIFT-DEL
      AlreadySelected = TRUE;
    }

  OldXCaret = iCaret;
  OldYCaret = YCaret;
  OldYAbsCaret = YAbsCaret;

//  FindMatchingBraces (hWnd, FALSE, FALSE);

  switch (wP) {
    case VK_LEFT :
      if (GetKeyState (VK_CONTROL) < 0)
        PrevWord ();
      else
        PrevChar ();
      break ;
    case VK_RIGHT :
      if (GetKeyState (VK_CONTROL) < 0)
        NextWord ();
      else
        NextChar ();
      break ;
    case VK_UP :
      PrevLine ();
      break ;
    case VK_DOWN :
      NextLine ();
      break ;
    case VK_PRIOR :
      PrevSide (hWnd);
      break ;
    case VK_NEXT :
      NextSide (hWnd);
      break ;
    case VK_HOME :
      if (GetKeyState (VK_CONTROL) < 0)
        Home ();
      else
        LineBeg ();
      break ;
    case VK_END :
      if (GetKeyState (VK_CONTROL) < 0)
        End ();
      else
        LineEnd ();
      break ;
    case VK_TAB :
      if (AlreadySelected) {
        if (EndSel.Row != StartSel.Row) {    // mindestens eine Zeile
          // sollte die End-Selektion nicht an der nullten Spalte sein, muß
          // man eine Zeile weiterschalten, des Rest macht SetSelection!
          if (EndSel.Row > StartSel.Row)
            if (EndSel.Col > 0)
              EndSel.Line = EndSel.Line->Next;
          SetSelection (StartSel.Line, EndSel.Line);
          if (ShiftIsDown)
            MoveBlock (hWnd, TRUE);   // nach links verschieben
          else  
            MoveBlock (hWnd, FALSE);  // nach rechts verschieben
          }
        if (!ModifyDone) {
          ModifyDone = TRUE ;
          SetCaption (hWnd);
          }
        }  
      break;
    }
  if ((oLineWithCaret != LineWithCaret) || (oiCaret != iCaret)) {
    GetNewCaretPos ();

    if (ShiftIsDown) {
      if (IsMovementKey(wP)) {   // eine der Cursor-Bewegungs-Tasten?
        EndSel.Row = YAbsCaret;
        EndSel.Col = iCaret;
        EndSel.Line = LineWithCaret;

        GetClientRect (hWnd, &rcClient);
        
        // vertikale Bewegung
        if (IsVertMove (wP) || (oLineWithCaret != LineWithCaret)) {
          rcInvalid.left = GetXMin();  
          rcInvalid.right = rcClient.right;

          rcInvalid.top = ((YCaret < OldYCaret) ? YCaret : OldYCaret) * charHeight;
          rcInvalid.bottom = ((YCaret < OldYCaret) ? OldYCaret+1 : YCaret+1) * charHeight;

          if (YCaret == OldYCaret) {        // beim Scrollen bleiben die beiden gleich
            if (YCaret < YAbsCaret) {       // und YAbsCaret muss immer groesser sein
              if (wP == VK_DOWN)
                rcInvalid.top -= charHeight; // ein bisschen mehr nach oben invalidieren
              else if (wP == VK_UP)  
                rcInvalid.bottom += charHeight; // ein bisschen mehr nach unten invalidieren
              }
            }

          }
        else {    // nur horizontale Bewegungen
          rcInvalid.left = GetXMin() + (iCaret < OldXCaret ? iCaret : OldXCaret) * charWidth - x0 ;
          rcInvalid.right = GetXMin() + (iCaret < OldXCaret ? OldXCaret : iCaret) * charWidth - x0 ;

          rcInvalid.top = YCaret * charHeight;
          rcInvalid.bottom = rcInvalid.top+charHeight;
          }

        InvalidateRect (hWnd, &rcInvalid, FALSE);
        }  // if (IsMovementKey())
      }  // if (ShiftIsDown)
    else {
      if (wP != VK_CONTROL) {    // bei CTRL aendert sich an der Selektion nichts
        if (AlreadySelected) {   // kein CTRL => alles ohne Selektion zeichnen
          InvalidateSelectedLines (hWnd);   // die Selektion löschen
          StartSel.Row = EndSel.Row;
          StartSel.Col = EndSel.Col;
          StartSel.Line = EndSel.Line;
          SelWord = NULL;
          }
        AlreadySelected = FALSE;

        FindMatchingBraces (hWnd, FALSE, IsMovementKey(wP));
        }
      }  // if (ShiftIsDown)
    
    PosCaret (hWnd);
    }  // if (Cursor hat sich bewegt)

  if (wP == VK_DELETE)
    OnChar (hWnd,255);
  }

//----------------------------------------------------------------------------
void TextBlock::OnKillFocus (HWND hWnd)
  {
  TakeCaretFrom (hWnd);
  }

//----------------------------------------------------------------------------
void TextBlock::OnSetFocus (HWND hWnd)
  {
  if (LineWithCaret == NULL)
    LineWithCaret = FirstVisibleLine , iCaret = 0;
  GiveCaretTo (hWnd);
  /*
  Da PosCaret ein NeedViewFor macht, dieses ein GetClientRect macht, und 
  dieses bei einem Fensterwechsel im Zoom-Modus noch die kleine Grösse liefert,
  kommt es dadurch, falls der Cursor ausserhalb des kleineren Fensters positioniert
  ist, zu einem unerwünschten Scrolling. 
  Da die Position eigentlich unveraendert sein sollte ist ein GetNewCaretPos 
  (hoffentlich) unnotwendig. Daher braucht man dann auch kein PosCaret mehr.
  GetNewCaretPos (); 
  PosCaret (hWnd);
  */
  // Allerdings muessen wir jetzt die Statusbar und das Caret selbst setzen.
  SetCaretPos (xScroll, int (yScroll));
  char outtxt[6];
  wsprintf (outtxt, "%05d", iCaret+1);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_LINE, LONG(LPSTR(outtxt)));
  wsprintf (outtxt, "%05d", YAbsCaret+1);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_COLUMN, LONG(LPSTR(outtxt)));
  }

//============================================================================
// TextBlock::PosCaret
//
//============================================================================
void TextBlock::PosCaret (HWND hWnd,int xExtra,int yExtra,int xExtraNeg,int yExtraNeg,BOOL preferLeft)
  {
  NeedViewFor (hWnd, this, &xScroll, &yScroll, yFirstVisible,xExtra,yExtra,xExtraNeg,yExtraNeg,preferLeft);
  SetCaretPos (xScroll, int (yScroll));

#ifdef ANALYSELINE
  AnalyseLines (NULL, NULL, FALSE);
  CurrentAnalyseState = LineWithCaret->GetAnalyseStatus (iCaret);
#endif

  char outtxt[6];
  wsprintf (outtxt, "%05d", iCaret+1);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_LINE, LONG(LPSTR(outtxt)));
  wsprintf (outtxt, "%05d", YAbsCaret+1);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_COLUMN, LONG(LPSTR(outtxt)));
  }

//----------------------------------------------------------------------------
void TextBlock::PrevChar ()
  {
  if (iCaret > 0) iCaret--;
  }

//----------------------------------------------------------------------------
void TextBlock::PrevLine ()
  {
  if (LineWithCaret->Prev != NULL)
    LineWithCaret = LineWithCaret->Prev ;
  }

//----------------------------------------------------------------------------
void TextBlock::PrevSide (HWND hWnd)
  {
  if (FirstVisibleLine->Prev == NULL)
    return;

  RECT r;
  GetClientRect (hWnd,&r);
  int AnzLines = r.bottom / charHeight - 1;
  for (int i = 0 ; i < AnzLines ; i ++) {
    PrevLine ();
/*
    if (FirstVisibleLine->Prev != NULL)
      FirstVisibleLine = FirstVisibleLine->Prev;
*/
    }
//  InvalidateRect (hWnd, NULL, TRUE);
  }

//----------------------------------------------------------------------------
#define PWS_INIT    0
#define PWS_SPACE1  1
#define PWS_WORD    2
void TextBlock::PrevWord (BOOL forDelete)
  {
  BOOL wordStopAtWordEnd;
  BOOL wordStopAtEOL;
  if (AlreadySelected) {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_SELECT_SHIFT) & WORDSTOP_LEFT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_SELECT_SHIFT) & WORDSTOP_LEFT_EOL) != 0;
    }
  else if (forDelete) {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_DELETE_SHIFT) & WORDSTOP_LEFT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_DELETE_SHIFT) & WORDSTOP_LEFT_EOL) != 0;
    }
  else {
    wordStopAtWordEnd = ((wordStopFlags >> WORDSTOP_JUMP_SHIFT) & WORDSTOP_LEFT_WORDEND) != 0;
    wordStopAtEOL     = ((wordStopFlags >> WORDSTOP_JUMP_SHIFT) & WORDSTOP_LEFT_EOL) != 0;
    }
  BOOL stop = FALSE ;
  if (iCaret > lstrlen(LineWithCaret->Text))
    iCaret = lstrlen(LineWithCaret->Text) + 1;
  for ( int state = PWS_INIT ; !stop ; ) {
    LPLINE oLineWithCaret = LineWithCaret;
    int oiCaret = iCaret;
    CheckPrevChar ();
    switch (state) {
      case PWS_INIT :
        if (IsWordChar (LineWithCaret->Text[iCaret])) state = PWS_WORD ;
        else                                          state = PWS_SPACE1 ;
        break ;
      case PWS_SPACE1 :
        if (IsWordChar (LineWithCaret->Text[iCaret])) 
          if (wordStopAtWordEnd)
            stop = TRUE;
          else
            state = PWS_WORD ;
        else if (wordStopAtEOL && (LineWithCaret->Text[iCaret] == '\0')) {
          stop = TRUE ;
          }
        break ;
      case PWS_WORD :
        if (!IsWordChar (LineWithCaret->Text[iCaret])) {
          stop = TRUE ;
          }
        break ;
      }
    if ((LineWithCaret == oLineWithCaret) && (iCaret == oiCaret)) break ;
    }
  CheckNextChar ();
  }

//----------------------------------------------------------------------------
BOOL TextBlock::TestString (LPSTR s,LPSTR t,BOOL CaseSensitive,BOOL wholeWord,BOOL lineStart)
  {
  if (wholeWord && !lineStart && IsWordChar(*(t-1)))
    return FALSE;
  for ( ; ((*s) && (*t)) ; s ++ , t ++) {
    unsigned char c1,c2 ;
    if (!CaseSensitive) {

#ifdef WIN32
      c1 = *s;

      c1 = (char)LOWORD(CharUpper (LPTSTR(c1)));
//      c1 = (char)(DWORD) CharUpper (LPSTR(*s));
#else
      c1 = char (DWORD (AnsiUpper (LPSTR(MAKELP(0,*s)))));
#endif

#ifdef WIN32
      c2 = *t;

      c2 = (char)LOWORD(CharUpper (LPTSTR(c2)));
//      c2 = (char)(DWORD) CharUpper (LPSTR(*t));
#else
      c2 = char (DWORD (AnsiUpper (LPSTR(MAKELP(0,*t)))));
#endif

      }
    else {
      c1 = *s ;
      c2 = *t ;
      }
    if (!(c1 == c2)) break ;
    }
  if (*s == '\0') {
    if (wholeWord)
      return (!IsWordChar(*t));
    else
      return TRUE ;
    }
  else
    return FALSE ;
  }

//-----------------------------  Search  ------------------------------------
//
//---------------------------------------------------------------------------
BOOL TextBlock::CheckSelectedLines (LPSTR SearchString,BOOL CaseSensitive,BOOL wholeWord)
  {
  SelStruct SelStart, SelEnd;
  GetSelectionFromTopToBottom (&SelStart,&SelEnd);
  if ((SelStart.Line != NULL) && (SelStart.Line == SelEnd.Line) &&
      (TestString (SearchString,SelStart.Line->Text + SelStart.Col,
                   CaseSensitive,wholeWord,(SelStart.Col == 0))))
    return TRUE ;
  else
    return FALSE ;
  }

BOOL TextBlock::SearchIt (BOOL bCycled,
                          HWND hWnd,LPSTR SearchString,LPSTR ReplaceString,
                          BOOL CaseSensitive,BOOL replace,BOOL wholeWord,BOOL directionDown,
                          BOOL withMessage)

  {
  int iSearchLen = lstrlen(SearchString);
  LPLINE cycleLine;
  int cyclePos, moveDir;

  if (directionDown) {
    cycleLine = FirstLine;
    cyclePos = 0;
    moveDir = 1;
    }
  else {
    cycleLine = LastLine;
    if (cycleLine != NULL)
      cyclePos = lstrlen (cycleLine->Text) - iSearchLen;
    moveDir = -1;
    }

  BOOL res = FALSE ;

  if ((replace) && (CheckSelectedLines (SearchString,CaseSensitive,wholeWord))) {
    DeleteSelectedLines (hWnd);
    if (ReplaceString != NULL)
      InsertLinesInTextFromBuffer (hWnd, ReplaceString);
    }

  InvalidateSelectedLines (hWnd);   // aktuelle Selektion loeschen
  AlreadySelected = FALSE;
  UpdateWindow (hWnd);

  if ((SearchString == NULL) || (*SearchString == '\0')) {
    MessageBeep (0);
    return FALSE ;
    }
    
  LPLINE StartLine;
  BOOL setToLineBegin = FALSE;
  int i;
  
  // bCycled == TRUE ... Ende des Textes wurde erreicht
  if (bCycled) {
    StartLine = cycleLine;   // Suchvorgang vom Anfang an starten
    setToLineBegin = TRUE;
    }
  else {
    StartLine = LineWithCaret;  // beginne an der aktuellen Position
    if (replace || !directionDown)
      i = iCaret;
    else
      i = iCaret + moveDir;     // Bei Suchen nach unten aktuelle Cursor-Position nicht beruecksichtigen
    if (!directionDown)
      i -= iSearchLen;
    }

  
  for (LPLINE h = StartLine; h != NULL; h = (directionDown ? h->Next : h->Prev)) {
    int maxLinePos = lstrlen (h->Text) - iSearchLen;
    if (maxLinePos >= 0) {
      if (setToLineBegin || (directionDown ? i < 0 : i > maxLinePos))
        i = (directionDown ? 0 : maxLinePos);
      for (LPSTR t = h->Text + i ; (i >= 0) && (i <= maxLinePos); t += moveDir , i += moveDir ) {
        if (TestString (SearchString,t,CaseSensitive,wholeWord,t == h->Text)) {
          iCaret = i ;
          LineWithCaret = h ;
  
          RECT rc;
          GetClientRect (hWnd, &rc);
                                                        
          SetNewCPos (hWnd, (lstrlen(SearchString) + 5) * charWidth, rc.bottom / 5, 
                            5 * charWidth, rc.bottom / 5, TRUE);
  
          SetSelWord (h, i, i+lstrlen(SearchString)-1);
  
          InvalidateSelectedLines (hWnd);
          UpdateWindow (hWnd);
  
          return TRUE ;
          }
        }
      }
    setToLineBegin = TRUE;
    }

  if (!bCycled) {
    bCycled = (LineWithCaret == cycleLine);
    }
  
  if (withMessage) {
    char msgtxt[256];
    if (bCycled) {
      wsprintf (msgtxt, "Suchtext <%s> wurde im Text nicht gefunden.", SearchString);
      MessageBox (hWnd, msgtxt, "Clinicum RESTOOL", MB_OK | MB_ICONINFORMATION);
      }
    else {
      wsprintf (msgtxt, "Suchtext <%s> wurde bis zum %s nicht gefunden.\rAm %s weitersuchen?", 
                        SearchString, (directionDown ? "Ende" : "Anfang"), (directionDown ? "Anfang" : "Ende"));
      if (MessageBox (hWnd, msgtxt, "Clinicum RESTOOL", MB_YESNOCANCEL | MB_ICONINFORMATION) == IDYES) {
        res = SearchIt (TRUE, hWnd, SearchString, ReplaceString, CaseSensitive, replace, wholeWord, directionDown);
        }
      }  
    }

  return res ;
  }

BOOL TextBlock::Search (HWND hWnd,LPSTR SearchString,LPSTR ReplaceString,BOOL CaseSensitive,BOOL replace,BOOL wholeWord)
  {
  return SearchIt (FALSE, hWnd, SearchString, ReplaceString, CaseSensitive, replace, wholeWord, TRUE);
  }

//---------------------------  SearchUp  ------------------------------------
//
//---------------------------------------------------------------------------
BOOL TextBlock::SearchUp (HWND hWnd, LPSTR SearchString,BOOL CaseSensitive,BOOL wholeWord)
  {
  return SearchIt (FALSE, hWnd, SearchString, "", CaseSensitive, FALSE, wholeWord, FALSE);
  }



//----------------------------------------------------------------------------
void TextBlock::SetCaretWithMouse (HWND hWnd,int x,int y,BOOL MoveCaret)
  {
  GiveCaretTo (hWnd);
  LPLINE oLineWithCaret = LineWithCaret;  // Zeile in der vorher das Caret war
  int oiCaret = iCaret;

  int LineNr = y / charHeight;   // Zeile die mit der Maus selektiert wird
  LPLINE h = FirstVisibleLine;
  if (LineNr >= 0)
    for (int i = 0 ; ((i < LineNr) && (h->Next != NULL)) ; i++ , h = h->Next);
  else   
    for (int i = 0 ; ((i > LineNr) && (h->Prev != NULL)) ; i-- , h = h->Prev);

  if (h != NULL) {
    LineWithCaret = h;
    int charNr = (x - GetXMin() + x0) / charWidth ;
    iCaret = max(charNr, 0);
    }
  else
    End();

//  viCaret = iCaret;
  if ((oLineWithCaret != LineWithCaret) || (oiCaret != iCaret))
    if (MoveCaret)
      SetNewCPos (hWnd);
  }

//-------------------------------- SetNewCPos --------------------------------
//
//----------------------------------------------------------------------------
void TextBlock::SetNewCPos (HWND hWnd,int xExtra,int yExtra,int xExtraNeg,int yExtraNeg,BOOL preferLeft)
  {
  GetNewCaretPos ();
  PosCaret (hWnd,xExtra,yExtra,xExtraNeg,yExtraNeg,preferLeft);
  }

//----------------------------------------------------------------------------
// setzt die Selektion auf jeweils ganze Zeilen von first bis last
//----------------------------------------------------------------------------
void TextBlock::SetSelection (LPLINE first, LPLINE last)
  {
  int row;
  LPLINE h;

  if ((first == NULL) && (last == NULL)) {
    AlreadySelected = FALSE;
    StartSel.Col = 0;
    EndSel.Col = 0;
    StartSel.Row = NULL;
    EndSel.Row = NULL;
    StartSel.Line = NULL;
    EndSel.Line = NULL;
    }
  else {
    AlreadySelected = TRUE;
    StartSel.Col = 0;
    for (h = FirstLine, row = 0; ((h != first) && (h != NULL)); row++, h = h->Next);
    StartSel.Row = row;
    StartSel.Line = first;
  
    EndSel.Col = 0;
    for (h = FirstLine, row = 0; ((h != last) && (h != NULL)); row++, h = h->Next);
    EndSel.Row = row;
    EndSel.Line = last;
    }
  }

//----------------------------------------------------------------
// Setzt das SelWord aus der Zeile <h> von B(eginn) bis zum E(nde)
//----------------------------------------------------------------
void TextBlock::SetSelWord (LPLINE h, WORD b, WORD e)
  {
  SetSelection (h, h);
  StartSel.Col = b;
  EndSel.Col = e+1;

  if (SelWord != NULL) 
    FreeGlobMem (SelWord);
  SelWord = NULL;
  if (h != NULL) {
    SelWord = LPSTR (GetGlobMem (int(e - b + 2)));
    lmemcpy (SelWord, h->Text + b, e - b + 1);
    SelWord[e - b + 1] = '\0';
    }
  }

//----------------------------------------------------------------------------
void TextBlock::ShowCaretIn (HWND hWnd)
  {
  if (!cshown)
    ShowCaret (hWnd);
  cshown = TRUE ;
  }

//----------------------------------------------------------------------------
void TextBlock::TakeCaretFrom (HWND hWnd)
  {
  if (bCaretExists)
    DestroyCaret ();
  cshown = FALSE ;
  bCaretExists = FALSE ;
  }


//----------------------------------------------------------------------------
void TextBlock::OnLButtonDown (HWND hWnd, WPARAM wParam, LPARAM lParam)
  {
  if (AlreadySelected)
    InvalidateSelectedLines (hWnd);   // die Selektion löschen

  AlreadySelected = FALSE;
  SetCaretWithMouse (hWnd, LOWORD(lParam), HIWORD(lParam));
  StartSel.Col = iCaret;
  StartSel.Row = YAbsCaret;
  StartSel.Line = LineWithCaret;

  EndSel.Row = StartSel.Row;
  EndSel.Col = StartSel.Col;
  EndSel.Line = StartSel.Line;

  SelWord = NULL;

  if (LOWORD(lParam) < XMIN) {
    SetSelection (StartSel.Line, EndSel.Line);
    InvalidateSelectedLines (hWnd);   // die Selektion löschen
    }
  }
  
  
//----------------------------------------------------------------------------
void TextBlock::OnMouseMove (HWND hWnd, WPARAM wParam, LPARAM lParam)
  {
  RECT rcInvalid, rcClient;
  
  int OldYAbsCaret = YAbsCaret;
  int OldYCaret = YCaret;
  int OldXCaret = iCaret;

  GetClientRect (hWnd, &rcClient);

  short YMouse = HIWORD(lParam);
  if (YMouse < -charHeight)
    YMouse = -charHeight;
  else  
  if (YMouse > rcClient.bottom)
    YMouse = rcClient.bottom;

  SetCaretWithMouse (hWnd, LOWORD(lParam), YMouse);

  EndSel.Row = YAbsCaret;
  EndSel.Col = iCaret;
  EndSel.Line = LineWithCaret;
  
  if (YAbsCaret != OldYAbsCaret) {
    rcInvalid.left = GetXMin();
    rcInvalid.right = rcClient.right;

    rcInvalid.top = int (LONG (YAbsCaret > OldYAbsCaret ? (OldYAbsCaret-1) : (YAbsCaret)) * LONG (charHeight) - yFirstVisible) ;
    rcInvalid.bottom = int (LONG (YAbsCaret > OldYAbsCaret ? (YAbsCaret+1) : (OldYAbsCaret+2)) * LONG (charHeight) - yFirstVisible) ;
    }
  else {    // nur horizontale Bewegungen
    rcInvalid.left = GetXMin() + (iCaret < OldXCaret ? iCaret : OldXCaret) * charWidth - x0 ;
    rcInvalid.right = GetXMin() + (iCaret < OldXCaret ? OldXCaret : iCaret) * charWidth - x0 ;

    rcInvalid.top = YCaret * charHeight;
    rcInvalid.bottom = rcInvalid.top+charHeight;
    }

  if (!AlreadySelected)       // erst bei der ersten Mausbewegung
    if ((YAbsCaret != OldYAbsCaret) || (iCaret != OldXCaret)) {
      AlreadySelected = TRUE;
      }

  InvalidateRect (hWnd, &rcInvalid, FALSE);
  }
  
//----------------------------------------------------------------------------
void TextBlock::OnLButtonUp (HWND hWnd, WPARAM wParam, LPARAM lParam)
  {
  }
  
//----------------------------------------------------------------------------
// Bei einem Doppelclick wird das ganze Wort selektiert
//----------------------------------------------------------------------------
void TextBlock::OnLButtonDblClk (HWND hWnd, WPARAM wP, LPARAM lP)
  {
  if (iCaret < lstrlen(LineWithCaret->Text)) {
    for (int b = iCaret; (b > 0) ; b--)
      if (!IsWordChar(LineWithCaret->Text[b])) { b++ ; break ; }
    for (int e = iCaret; ; e++)
      if (!IsWordChar(LineWithCaret->Text[e])) { e-- ; break ; }
        
    if (b < e) {
      StartSel.Col = b;
      StartSel.Row = YAbsCaret;
      StartSel.Line = LineWithCaret;
            
      EndSel.Col = e+1;
      EndSel.Row = StartSel.Row;
      EndSel.Line = StartSel.Line;
        
      SetSelWord (StartSel.Line, b, e);
      InvalidateSelectedLines (hWnd);   // die Selektion anzeigen
      }
    }
  }
