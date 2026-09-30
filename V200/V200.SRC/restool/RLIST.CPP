/////////////////////////////////////////////////////////////////////////
//  Verwaltung einer Liste von Texten, die im ini File gespeichert wird
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/rlist.cpv   1.21   26 Mar 1999 18:14:32   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/rlist.cpv  $
// 
//    Rev 1.21   26 Mar 1999 18:14:32   Wolfgang
// 1.) OnVKReturn braucht caseSensitive-Parameter.
// 
//    Rev 1.20   17 Mar 1999 19:24:20   Wolfgang
// 1.) CheckCommand mit zusaetzlichen Parametern.
// 2.) RemoveCurrentElem neu.
// 3.) WriteEntrys loescht ueberzaehlige Eintraege.
// 
//    Rev 1.19   16 Mar 1999 16:12:50   Wolfgang
// 1.) Erweiterungen fuer Workspace.
// 
//    Rev 1.18   12 Mar 1999 13:51:20   Wolfgang
// 1.) InsertEntry gibt zurueck, ob sich erster Eintrag geaendert hat.
// 2.) InsertEntry benuetzt defaultmaessig caseinsensitiven Vergleich.
// 3.) DelEntrys entfernt, um Existenz der Search-List zu garantieren.
// 
//    Rev 1.17   08 Mar 1999 18:51:16   Wolfgang
// 1.) Pruefung in CheckCommand korrigiert, damit auch letztes File im Menu 
//     aufgeht.
// 
//    Rev 1.16   08 Jul 1998 13:00:18   Gerhold
// Nochmals das Flushproblem (diesmal aber richtig)
// 
//    Rev 1.15   08 Jul 1998 09:53:34   Gerhold
// WritePrivateProfileString flushen
// 
//    Rev 1.14   04 May 1998 11:17:58   Gerhold
// ReplaceCombo ... zusaetzlicher Parameter BOOL InsertEmptyString fuer INI
// 
//    Rev 1.13   03 Feb 1998 17:28:24   Hannes
// 
//    Rev 1.12   08 Jan 1998 13:05:38   Gerhold
// Das Hochkomma-Problem in der INI war nur fuer 32 Bit
// 
//    Rev 1.11   02 Jan 1998 10:05:36   Gerhold
// Eintraege in der INI-Datei mit " schreiben!!
// 
//    Rev 1.10   05 Nov 1997 09:15:28   Gerhold
// 32 Bit
// 
//    Rev 1.9   23 Jul 1996 15:51:22   GERHOLD
// SendMessage (hWndChild, WM_SETTEXT, 0, LPARAM(GetTopString()));
// 
//    Rev 1.8   02 Jul 1996 15:57:30   GERHOLD
// CBN_SELENDCANCEL, CBN_SELENDOK
// 
//    Rev 1.7   02 Feb 1996 10:50:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   10 Nov 1995 13:28:16   MARTIN
// extern HWND hwndmdiClient ...
// 
//    Rev 1.5   09 Nov 1995 19:42:34   HANNES
// Fehlerkorrektur SubID
// 
//    Rev 1.4   27 Aug 1995 13:00:30   HANNES
// 
//    Rev 1.3   07 Jun 1995 12:15:32   GERHOLD
// 
//    Rev 1.2   15 May 1995 08:51:34   GERHOLD
// 
//    Rev 1.1   02 Jan 1995 09:31:08   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   12 Jul 1994 14:45:02   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#define RLIST_MAIN
#include "rlist.hpp"
#define MODULENUM 118
#include "winass.hpp"

extern LPSTR IniFile();

//------------------------  ReadEntrys  -------------------------------------
//
// Liest aus der INI-Datei aus der Section <Entry> <Maxentrys> Eintraege
// und fuegt sie in die Liste ein.
//---------------------------------------------------------------------------
void RList::ReadEntrys (BOOL InsertEmptyString)
  {
  DelEntrys ();
  char Entry [128];
  char en [20];
  for (int i = MaxEntrys() ; i >= 0 ; i--) {
    wsprintf (en,"%d",i);
    lstrcpy (Entry,GetEntryTemplate ());
    lstrcat (Entry,en);
    char instr[256];
    instr[0] = '\0';
    GetPrivateProfileString (SectionName (),Entry,"",instr,sizeof(instr),IniFile());
    if (*instr || InsertEmptyString) {
      int zeile = 0; 
      int spalte = 0;
      if (UsePosition ()) {
        LPSTR zeileStr, spalteStr;
        zeileStr = strchr (instr, ';');      // Ende des Filenames suchen
        if (zeileStr) {
          *zeileStr = '\0';                     // Filenamen begrenzen
          zeileStr++;                           // Auf Anfang der Zeilenposition schalten
          spalteStr = strchr (zeileStr, ';');   // Ende der Zeilenposition suchen
          if (spalteStr) {
            *spalteStr = '\0';                  // Zeile begrenzen
            spalteStr++;                        // Auf Anfang der Spaltenposition schalten
            sscanf (spalteStr, "%ld", &spalte);
            }
          sscanf (zeileStr, "%ld", &zeile);
          }
        }
      InsertEntry (instr, FALSE, FALSE, TRUE, zeile, spalte);
      }
    }
  if (UseMenu ()) CreateMenu ();
  }

//------------------------  WriteEntrys  ------------------------------------
//
// schreibt eine Eintragsliste in die INI-Datei
//---------------------------------------------------------------------------
void RList::WriteEntrys ()
  {
  char Entry[128];
  char szTmp[256];
  char en [20];
  int i = 0 ;
  if (ClearSectionOnWrite ())
    WritePrivateProfileString (SectionName (),NULL,NULL,IniFile());
  for (LPRENT x = First ; x != NULL ; x = x->Next) {
    wsprintf (en,"%d",i++);
    lstrcpy (Entry,GetEntryTemplate ());
    lstrcat (Entry,en);

    //-------------------------------------------------------------------
    // Die Eintraege in der INI-Datei muessen unbedingt mit Hochkommata
    // versehen werden, da sonst beim Lesen eventuelle Leerzeichen 
    // entfernt werden
    //-------------------------------------------------------------------
    if (UsePosition ())
      sprintf (szTmp, "\"%s;%ld;%ld\"", x->Text, x->Zeile, x->Spalte);
    else
      sprintf (szTmp, "\"%s\"", x->Text);
    WritePrivateProfileString (SectionName (),Entry,szTmp,IniFile());
    }
  if (!ClearSectionOnWrite ()) {
    for (int j = i; j <= MaxEntrys (); j++) {
      wsprintf (en,"%d",j);
      lstrcpy (Entry,GetEntryTemplate ());
      lstrcat (Entry,en);
      WritePrivateProfileString (SectionName (),Entry,NULL,IniFile());
      }
    }
  //------------------------------------------------------
  // Eintraege in der RESTOOL.INI flushen
  //------------------------------------------------------
  WritePrivateProfileString (NULL, NULL, NULL, IniFile());
  }

void RList::DelEntrys ()
  {
  for ( ; First != NULL ; ) {
    LPRENT n = First->Next ;
    if (First->Text != NULL) FreeGlobMem (First->Text) ;
    FreeGlobMem (First);
    First = n;
    }
  }

void RList::DelEntrysAtTail ()
  {
  LPRENT prev = NULL ;
  int i = 0 ;
  for (LPRENT x = First ; x != NULL ; ) {
    if (i > MaxEntrys ()) {
      LPRENT n = x->Next ;
      if (prev != NULL) prev->Next = n ;
      else              First      = n ;
      if (x->Text != NULL) FreeGlobMem (x->Text) ;
      FreeGlobMem (x);
      x = n ;
      }
    else {
      prev = x ;
      x = x->Next ;
      i ++ ;
      }
    }
  }

void RList::RemoveCurrentElem (LPRENT lpe)

  {
  // Element aus der Liste ausklammern ...
  if (lpe->Prev != NULL)
    lpe->Prev->Next = lpe->Next;
  if (lpe->Next != NULL)
    lpe->Next->Prev = lpe->Prev;

  // und eventuell noch First korrigieren
  if (lpe == First)
    First = lpe->Next;

  // und weg damit
  if (lpe->Text != NULL) FreeGlobMem (lpe->Text) ;
  FreeGlobMem (lpe);
  }

//--------------------------  SetCurrentElemOnTop  --------------------------
//
// lpe ... Element das an die erste Stelle in der Liste gesetzt wird
//---------------------------------------------------------------------------
void RList::SetCurrentElemOnTop (LPRENT lpe)
  {
  if (lpe == First)  // sofort raus da!!
    return;

  // Element aus der Liste ausklammern ...
  if (lpe->Prev != NULL)
    lpe->Prev->Next = lpe->Next;
  if (lpe->Next != NULL)
    lpe->Next->Prev = lpe->Prev;

  // ... und an die erste Stelle setzen
  First->Prev = lpe;
  lpe->Next = First;
  
  First = lpe;
  First->Prev = NULL;
  }

BOOL RList::CmpEntry (LPSTR txt1, LPSTR txt2, BOOL caseSensitive)
  {
  if (caseSensitive)
    return lstrcmp(txt1, txt2) == 0;
  else
    return lstrcmpi(txt1, txt2) == 0;
  }

BOOL RList::InsertEntry (LPSTR Text,BOOL MenuModify,BOOL caseSensitive,BOOL forceInsert,
                         int zeile, int spalte)
  {
  WIN_ASSERT (Text != NULL);

  if (!forceInsert) {
    // die Liste durchgehen ob der Text bereits existiert
    for (LPRENT lpe = First; lpe != NULL; lpe = lpe->Next) {
      if (CmpEntry (lpe->Text, Text, caseSensitive)) {
        lpe->Zeile = zeile;
        lpe->Spalte = spalte;
        if (lpe != First) {            // Text ist erstes Element?
          if ((UseMenu ()) && (MenuModify))
            DestroyMenu ();
          SetCurrentElemOnTop (lpe);   // nein => nach oben setzen!
          if ((UseMenu ()) && (MenuModify))
            CreateMenu ();
          return TRUE;
          }
        else
          return FALSE;
        }
      }
    }
  if ((UseMenu ()) && (MenuModify)) DestroyMenu ();
  LPRENT n = LPRENT (GetGlobMem (sizeof(*n)));
  n->Next = First ;
  if (First != NULL) First->Prev = n ;
  First = n;
  int l = lstrlen (Text) + 1 ;
  n->Text = LPSTR (GetGlobMem (l));
  lstrcpy (n->Text,Text);
  n->Zeile = zeile;
  n->Spalte = spalte;
  DelEntrysAtTail ();
  if ((UseMenu ()) && (MenuModify)) CreateMenu ();
  return TRUE;
  }

LPRENT RList::GetLast() 
  {
  for (LPRENT x = First ; ((x != NULL) && (x->Next != NULL)) ; x = x->Next) ;
  return x ;
  }

extern HWND hwndMDIClient;
void RList::CreateMenu ()
  {
  HMENU hMenu = GetMenu (hWnd);
  WIN_ASSERT (hMenu);
  BOOL bMDI_IsMaximized = FALSE;

  if (hwndMDIClient) {
#ifdef WIN32
    SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, LPARAM(&bMDI_IsMaximized));
#else
    bMDI_IsMaximized = BOOL(HIWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif
    }

  HMENU hSub = GetSubMenu (hMenu,(bMDI_IsMaximized) ? SubID + 1 : SubID);
  WIN_ASSERT (hSub);
  int j = 0 ;
  for (LPRENT x = First ; x != NULL ; x = x->Next , j ++) {
    char mtext[128];
    lstrcpy (mtext,x->Text);
    if (*HKTemplate ()) {
      lstrcat (mtext,HKTemplate ());
      char mnum[20];
      wsprintf (mnum,"%d",j+1);
      lstrcat (mtext,mnum);
      }
    AppendMenu (hSub,MF_STRING,GetMENUBaseId()+j,mtext);
    }
  DrawMenuBar (hWnd);
  }

void RList::DestroyMenu ()
  {
  HMENU hMenu = GetMenu (hWnd);
  WIN_ASSERT (hMenu);

  BOOL bMDI_IsMaximized;
#ifdef WIN32
  SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, LPARAM(&bMDI_IsMaximized));
#else
  bMDI_IsMaximized = BOOL(HIWORD(SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L)));
#endif

  HMENU hSub = GetSubMenu (hMenu,(bMDI_IsMaximized) ? SubID + 1 : SubID);
  WIN_ASSERT (hSub);
  int j = 0 ;
  for (LPRENT x = GetLast() ; x != NULL ; x = x->Prev , j ++)
    DeleteMenu (hSub,GetMENUBaseId()+j,MF_BYCOMMAND);
  DrawMenuBar (hWnd);
  }

//--------------------------  CheckCommand  ---------------------------------
//
// wP ... Menu-Command-Parameter von der WM_COMMAND Nachricht
//---------------------------------------------------------------------------
LPSTR RList::CheckCommand (WORD wP, BOOL removeEntry, LPSTR strBuffer, LPINT zeile, LPINT spalte)
  {
  int cmd = int (wP);
  int coffs = cmd - GetMENUBaseId();
  if ((coffs >= 0) && (coffs <= MaxEntrys())) {
    int j = 0 ;
    for (LPRENT x = First ; x != NULL ; x = x->Next , j ++) {
      if (j == coffs) {
        if (UseMenu ()) DestroyMenu ();
        if (zeile != NULL)
          *zeile = x->Zeile;
        if (spalte != NULL)
          *spalte = x->Spalte;
        if (removeEntry) {
          if (strBuffer != NULL) {
            if (x->Text != NULL)
              lstrcpy (strBuffer, x->Text);
            else
              *strBuffer = '\0';
            }
          RemoveCurrentElem (x);
          }
        else {
          SetCurrentElemOnTop (x);
          strBuffer = x->Text;
          }
        if (UseMenu ()) CreateMenu ();
        return strBuffer ;
        }
      }
    }
  return NULL ;
  }

//***************************************************************************
//
// SearchNames
//
//***************************************************************************

void SearchNames::FillDialog (HWND hDlg,WORD Id)
  {
  int i = 0;
  for (LPRENT x = GetLast() ; x != NULL ; x = x->Prev , i++)
    SendDlgItemMessage (hDlg,Id,LB_ADDSTRING,0,LONG(x->Text));
  if (First != NULL)
    SendDlgItemMessage (hDlg,Id,LB_SETCURSEL,i-1,0L);
  }

void SearchNames::OnDialogInit (HWND hDlg,WORD IdList,WORD IdEdit)
  {
  if (IsWindow(hDlg)) {
    ReadEntrys ();
    FillDialog (hDlg,IdList);
    LPRENT l = First ;
    if (l != NULL)
      SetDlgItemText (hDlg,IdEdit,l->Text);
    }
  }

void SearchNames::OnDialogOk (HWND hDlg,WORD IdList,WORD IdEdit)
  {
  char Text[256];
  GetDlgItemText (hDlg,IdEdit,Text,sizeof(Text));
  InsertEntry (Text,FALSE);
  WriteEntrys ();
  }

void SearchNames::OnCommand (HWND hDlg,WORD IdList,WORD IdEdit,LONG lP)
  {
  if (HIWORD(lP) == LBN_DBLCLK) {
    int Sel = int (SendDlgItemMessage (hDlg,IdList,LB_GETCURSEL,0,0L));
    int i = 0;
    for (LPRENT x = GetLast() ; x != NULL ; x = x->Prev , i++) {
      if (i == Sel) {
        SetDlgItemText (hDlg,IdEdit,x->Text);
        break ;
        }
      }
    }
  }



//----------------------------------------------------------------------------
// Liest die "Search"-Eintraege aus der INI-Datei, und besetzt die Combo-Box
// Wird sofort nach dem Erzeugen der Combo-Box, bzw. nach Oeffnen der Combo-
// Listbox aufgerufen.
//----------------------------------------------------------------------------
void SearchFromCombo::OnInit (HWND hWndCombo)
  {
  if (IsWindow(hWndCombo)) {
    ReadEntrys ();
    FillCombo (hWndCombo);
    }
  }
  
//----------------------------------------------------------------------------
// Fuellt die Combo-Box mit den Eintraegen aus der INI-Datei.
//----------------------------------------------------------------------------
void SearchFromCombo::FillCombo (HWND hWndCombo)
  {
  if (IsWindow(hWndCombo)) {
    SendMessage (hWndCombo, CB_RESETCONTENT, 0, 0);
  
    int i = 0;
    for (LPRENT x = First ; x != NULL ; x = x->Next, i++)
      SendMessage (hWndCombo, CB_ADDSTRING, 0, LONG(x->Text));
    if (First != NULL)
      SendMessage (hWndCombo, CB_SETCURSEL, 0, 0L);
    }
  }

//----------------------------------------------------------------------------
// Liest den Text aus dem Edit-Feld der Combo-Box und schreibt ihn in die INI.
//----------------------------------------------------------------------------
void SearchFromCombo::OnVKReturn (HWND hWndCombo, BOOL InsertEmptyString, BOOL caseSensitive)
  {
  if (IsWindow(hWndCombo)) {
    char Text[64];
    SendMessage (hWndCombo, WM_GETTEXT, sizeof(Text), LPARAM(LPSTR(Text)));
  
    ReadEntrys (InsertEmptyString);  // alle INI-Eintraege in temp. Liste lesen
    InsertEntry (Text,FALSE,caseSensitive);   // Einfuegen in die temp. Liste
    WriteEntrys ();                           // schreiben in die INI-Datei
    }
  }  

//----------------------------------------------------------------------------
// Reagiert auf die Notify-Meldungen des Elternfensters.
// Wird die Listbox heruntergeklappt werden die Eintraege gelesen.
// Wird ein Eintrag aus der Listbox gewaehlt, wird die INI-Datei aktualisiert.
//----------------------------------------------------------------------------
void SearchFromCombo::OnCommand (WPARAM wParam, LPARAM lParam)
  {
#ifdef WIN32
  WORD wNotifyCode = HIWORD(wParam);
  WORD wID = LOWORD(wParam);
  HWND hWndChild = (HWND) lParam;
#else
  WORD wNotifyCode = HIWORD(lParam);
  WORD wID = wParam;
  HWND hWndChild = HWND(LOWORD(lParam));
#endif

  
  if (IsWindow(hWndChild)) {
    if (wNotifyCode == CBN_DROPDOWN)
      OnInit (hWndChild);
    
    // Bei Abbruch wird der vorige Eintrag wieder in das Editfeld geschrieben
    else if (wNotifyCode == CBN_SELENDCANCEL) {
//      SendMessage (hWndChild, WM_SETTEXT, 0, LPARAM(First->Text));
      SendMessage (hWndChild, WM_SETTEXT, 0, LPARAM(GetTopString()));
      }
    
    // Der Eintrag wurde ausgewaehlt
    else if (wNotifyCode == CBN_SELENDOK) {
      char Text[64];
  
      DWORD dwIndex = SendMessage (hWndChild, CB_GETCURSEL, 0, 0);
      if (dwIndex != CB_ERR)
        SendMessage (hWndChild, CB_GETLBTEXT, 
                     WPARAM(dwIndex), LPARAM(LPSTR(Text)));
      InsertEntry (Text,FALSE);
      WriteEntrys ();
      }
    }  
  }
  
  
