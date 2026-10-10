//
//  $Header:   P:/marille/clinicum/ctool/rev/hotkey.cpv   1.16   05 Oct 1998 11:07:02   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/hotkey.cpv  $
// 
//    Rev 1.16   05 Oct 1998 11:07:02   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.15   14 Apr 1998 12:47:06   Hannes
// Versteckte Fenster ohne Hotkey
// 
//    Rev 1.14   07 Jan 1998 08:05:38   Hannes
// 
//    Rev 1.13   08 Sep 1997 10:48:14   Gerhold
// IsMyWindowEnabled ... zusaetzliche Abfrage (sc->ParentScreen == NULL) 
// 
//    Rev 1.12   08 Jan 1997 17:37:08   HANNES
// Deaktivieren der Hotkeys von Mappen
// 
//    Rev 1.11   02 Feb 1996 10:42:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   11 Jan 1996 03:37:08   HANNES
// HotKeyAction
// 
//    Rev 1.9   20 Nov 1995 13:34:08   GERHOLD
// Zahlen von "0" bis "9" ebenfalls als Hotkeys moeglich
// 
//    Rev 1.8   31 Oct 1995 07:29:34   GERHOLD
// bei SetWindowPos in WM_INITDIALOG das Flag SWP_NOACTIVATE angegeben
// 
//    Rev 1.7   16 Oct 1995 13:23:58   GERHOLD
// Die Dialogbox hat sich grundlegend geaendert. Die Datenstruktur HotKeyData
// nimmt jetzt zwei Hotkeys auf statt einem.
// 
//    Rev 1.6   11 Jun 1995 15:37:32   GERHOLD
// 
//    Rev 1.5   31 Mar 1995 13:10:08   HANNES
//  
// 
//    Rev 1.4   24 Feb 1995 14:38:30   GERHOLD
// 
//    Rev 1.3   24 Feb 1995 11:13:44   HANNES
// 
//    Rev 1.2   06 Feb 1995 16:51:16   HANNES
// Verbesserte Ueberpruefung
// 
//    Rev 1.1   09 Dec 1994 20:41:02   GERHOLD
// subclass raus!!
// 
//    Rev 1.0   24 Jun 1994 16:41:16   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.9   20 Jan 1994 23:54:10   HANNES
// bei VK_F2 auch die Kinder der Toolbar abgefragt
// 
//    Rev 1.8   17 Nov 1993 11:47:52   HANNES
// 
//    Rev 1.7   18 Oct 1993 19:44:50   HANNES
// VK_F2 richtig(er) behandelt
// 
//    Rev 1.6   04 Oct 1993 08:29:42   GERHOLD
// 
//    Rev 1.5   09 Sep 1993 19:08:22   GERHOLD
// 
//    Rev 1.4   18 Aug 1993 10:52:08   GERHOLD
// ???
// 
//    Rev 1.3   22 Jul 1993 14:38:28   GERHOLD
// 
//    Rev 1.2   21 Jul 1993 14:51:28   GERHOLD
// InitHotKey implementiert
// 
//    Rev 1.1   15 Jul 1993 16:51:46   GERHOLD
// PVCS - Header
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "toolbar.hpp"
#define JUST_EM
#define NODDSDATA
#include "dds.hpp"
//#include "subclass.hpp"

#define HK_TOOL_TO_DOC  VK_F2

#define VKCTRL     0x1
#define VKSHIFT    0x2
#define VKALT      0x4

void RemoveHotKey (ActionElem FAR *toRemove);   
HotKey FAR *GetHotKey (ActionElem FAR *);




HotKey::HotKey (HotKeyData keydata, BOOL allowModify,ActionElem FAR *action) 
  {
  KeyData = keydata;
  hkTool  = action;
  doModify = allowModify;
  Next = FirstHotKey;
  FirstHotKey = this;
  }

HotKey::~HotKey () 
  {
  HotKey FAR *prev = NULL ;
  for (HotKey FAR *h = FirstHotKey ; h != NULL ; ) {
    if (h == this) {
      if (prev != NULL) prev->Next = h->Next ;
      else              FirstHotKey = h->Next ;
      break ;
      }
    prev = h ;
    h = h->Next ;
    }
  }


void HotKey::ModifyHotKey (HotKeyData kd) 
  {
  KeyData = kd;
  if (hkTool != NULL)
    hkTool->SetHotKey (kd);
  }


int operator==(HotKey &hk1, HotKey &hk2) {
  return ((hk1.KeyData.Modify  == hk2.KeyData.Modify) &&
          (hk1.KeyData.VirtKey == hk2.KeyData.VirtKey));
  }



void RemoveHotKey (ActionElem FAR *pt)
  {
  for (HotKey FAR *h = FirstHotKey ; h != NULL ; h = h->Next) {
    if (h->hkTool == pt) {
      delete h ;
      break ;
      }
    }
  }

HotKey FAR* GetHotKey (ActionElem FAR *ptool) 
  {
  for (HotKey FAR *h = FirstHotKey ; h != NULL ; h = h->Next) 
    if (h->hkTool == ptool) 
      return h;

  return NULL;
  }


DLLExport void _export WINAPI InitHotKey (LPVOID privData, HotKeyStruct FAR* hkParam, WORD mode)
  {
  if (mode & EM_LOAD) {
    HotKeyData kd;
    kd.VirtKey = BYTE (hkParam->VKey);
    kd.Modify = BYTE (hkParam->Flags);
    (* SetData) (privData, hkParam->hkRef, &kd, sizeof(kd), hkParam);
    }                                                                
  }


DLLExport void _export WINAPI RemoveAllHotKeys ()
  {
  for ( ScreenList FAR *sc = FirstScreen ; sc != NULL ; sc = sc->Next)
    for (WndList FAR *Wnd = sc->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
      for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
        RemoveHotKey (h);
  }



DLLExport void _export WINAPI InitializeAllHotKeys ()
  {
  for ( ScreenList FAR *sc = FirstScreen ; sc != NULL ; sc = sc->Next)
    for (WndList FAR *Wnd = sc->FirstWnd ; Wnd != NULL ; Wnd = Wnd->Next)
      for (tool FAR *h = Wnd->first ; h != NULL ; h = h->Next)
        h->InitHotKey ();
  }




BOOL MyIsWindowEnabled (HWND hWnd,WORD ScreenNmbr)
  {
  ScreenList FAR *sc = (ScreenList FAR *) GetWindowLong (hWnd,GWL_SCREEN);
  if (!IsWindowVisible (hWnd)) return FALSE ;
  if (sc->IstMappe && (sc->ParentScreen == NULL)) {
    // Testen, ob das Fenster mit Focus kein mdiChild ist
    // (Mappen werden bei aktivem mdiChild nicht beruecksichtigt)
    HWND hWFocus = GetFocus ();
    char className[64];
    GetClassName (hWFocus,className,sizeof(className));
    if (lstrcmp (className,"MDICHILD") == 0) return FALSE ;
    return IsWindowEnabled (hFrameWnd);
    }
  if ((ScreenNmbr == 0) || (sc->IstMappe)) {
    for ( ; ; ) {
      if (!IsWindow (hWnd))       return TRUE ;
      if (!IsWindowEnabled(hWnd)) return FALSE ;
      hWnd = GetParent(hWnd);
      }
    }
  else
    return (IsWindowEnabled(hWnd));
  return TRUE ;
  }

DLLExport BOOL _export WINAPI IsHotKey (LPMSG lpmsg) 
  {
  BOOL static AltPressed = FALSE;

  if ((lpmsg->message == WM_KEYDOWN) || (lpmsg->message == WM_SYSKEYDOWN)) {
    // ist das jetzt der Hotkey um zwischen Toolbar und Dokument zu wechseln?
    if (lpmsg->wParam == HK_TOOL_TO_DOC) {
      BYTE keyflag = 0;
      keyflag = (GetKeyState(VK_CONTROL) & 0x1000) ? keyflag | VKCTRL : keyflag & ~VKCTRL;
      keyflag = (GetKeyState(VK_SHIFT) & 0x1000) ? keyflag | VKSHIFT : keyflag & ~VKSHIFT;
      keyflag = (GetKeyState(VK_MENU) & 0x1000) ? keyflag | VKALT : keyflag & ~VKALT;
      if (keyflag == VKCTRL) {

        HWND hWnd;
        HWND hWndMDIClient = 0;
        char classname[50];
        hWnd = GetWindow (hFrameWnd, GW_CHILD);
        for ( ; hWnd != NULL; ) {
          if (GetClassName(hWnd, classname, sizeof(classname))) {
            if (lstrcmp(classname, "MYMDICLIENT") != 0) 
              hWnd = GetWindow(hWnd, GW_HWNDNEXT);
            else
              break;  
            }  
          }
        if (hWnd != NULL)
          hWndMDIClient = hWnd;

        // der Toolbar hat den Fokus
        HWND fWnd = GetFocus();
        if ((fWnd == MainScreen->hWndToolbar()) ||
            (GetParent (fWnd) == MainScreen->hWndToolbar())) {
          if (hWndMDIClient != NULL)

#ifdef WIN32
            hWnd = HWND(SendMessage (hWndMDIClient, WM_MDIGETACTIVE, 0, NULL));
#else
            hWnd = LOWORD(SendMessage (hWndMDIClient, WM_MDIGETACTIVE, 0, 0L));
#endif
          
          if (hWnd) {
            SetFocus (hWnd);
            return TRUE;
            }
          }
        // ein Dokument bzw. der MDI-Client hat den Fokus
        else {
          hWnd = GetFocus();
          HWND hWndParent;
          if (IsWindow (hWnd))
            hWndParent = GetParent(hWnd);
          else
            hWndParent = 0;
          if ((hWndParent == hWndMDIClient) || 
              ((IsWindow(hWndParent)) && (GetParent(hWndParent) == hWndMDIClient)) ||
              (hWnd == hFrameWnd) || (hWnd == hWndMDIClient) ||
              (!IsWindow(hWnd))) {
            SetFocus (MainScreen->hWndToolbar());
            return TRUE;
            }
          }  
        }   // if (keyflag == VKCTRL)
      }

    for (HotKey FAR* hk = FirstHotKey; hk != NULL; hk = hk->Next) {
      if (hk->hkTool->IsElemEnabled()) {        // natuerlich nur weitermachen wenn das Tool anwählbar ist!!!
        if (((lpmsg->wParam == hk->KeyData.VirtKey) || (lpmsg->wParam == hk->KeyData.VirtKey1)) &&
              ((!hk->hkTool->IsTool()) || (
                  MyIsWindowEnabled(((tool FAR *)(hk->hkTool))->Parent->Parent->hWnd,((tool FAR *)(hk->hkTool))->Parent->Parent->ScreenNmbr)
                                          )
              )
           ) {

          // Ueberpruefe den Status der Steuertasten und setze das Flag
          BYTE tmpFlag = 0;
          tmpFlag = (GetKeyState(VK_CONTROL) & 0x1000) ? tmpFlag | VKCTRL : tmpFlag & ~VKCTRL;
          tmpFlag = (GetKeyState(VK_SHIFT) & 0x1000) ? tmpFlag | VKSHIFT : tmpFlag & ~VKSHIFT;
          tmpFlag = (GetKeyState(VK_MENU) & 0x1000) ? tmpFlag | VKALT : tmpFlag & ~VKALT;

          // stimmt die Tastenkombination ueberein?
          if (((hk->KeyData.Modify == tmpFlag) && (lpmsg->wParam == hk->KeyData.VirtKey)) ||
              ((hk->KeyData.Modify1 == tmpFlag) && (lpmsg->wParam == hk->KeyData.VirtKey1))) {
            hk->hkTool->HotKeyAction (FALSE);    // sofort ausfuehren
            AltPressed = FALSE;
            return TRUE;                    // und abbrechen
            }  // end if (hk->KeyData...)
          }  // end if (lpmsg->wParam...)
        }  // end if (hk->IsEnabled)
      }  // end for                       // weitersuchen
    }  // end if

  return FALSE;
  }

extern LPSTR szListClassName;


FARPROC lpfnOldWndProc = NULL;
HWND hEditWnd;

BYTE Modify;
BYTE VirtKey;

struct HotkeyList {
  BYTE Modify;
  BYTE VirtKey;
  char szHotkey[64];
  };

//---------------------  InterpreteHotkey  ----------------------------------
//
// Uebersetzen der Tastatur-Parameter in Zeichenketten
//
// Virtkey.....virtueller Tastaturcode (VK_ ...)
// Modify......Maske mit CTRL, SHIFT, ALT
// szHotkey....Rueckgabewert
//---------------------------------------------------------------------------
void InterpreteHotkey (int iVirtKey, int iModify, LPSTR szHotKey)
  {
  lstrcpy (szHotKey, "");

  VirtKey = iVirtKey;

  // ist Modify kleiner Null, dann muessen die Tasten ausgewertet werden
  if (iModify < 0) {
    Modify = 0;
    if (GetKeyState(VK_CONTROL) < 0) {
      lstrcat (szHotKey, "STRG+");
      Modify |= VKCTRL;
      }
    if (GetKeyState(VK_MENU) < 0) {
      lstrcat (szHotKey, "ALT+");  
      Modify |= VKALT;
      }
    if (GetKeyState(VK_SHIFT) < 0) {
      lstrcat (szHotKey, "SHIFT+");
      Modify |= VKSHIFT;
      }

    }
  else {
    if (iModify & VKCTRL)
      lstrcat (szHotKey, "STRG+");
    if (iModify & VKALT)
      lstrcat (szHotKey, "ALT+");
    if (iModify & VKSHIFT)
      lstrcat (szHotKey, "SHIFT+");

    Modify = iModify;
    }
          
  //------------------------------------------------------------------
  // Die Funktion <GetKeyNameText> waere hier besser, ist aber wegen
  // der momentanen Speicherung der Parameter leider nicht moeglich.
  // (BYTE Virtkey; BYTE Modify; BYTE VirtKey1; BYTE Modify1)
  // Das oben beschriebene struct darf nicht laenger als 4 Bytes sein,
  // da die Hotkey-Referenz in den Buttons als LONG gespeichert ist.
  // GetKeyNameText benoetigt aber zur Auswertung der gedrueckten
  // Taste den LPARAM aus WM_KEYDOWN =>  die Referenz auf den Hotkey
  // muesste anders geloest werden.
  //------------------------------------------------------------------
  switch (iVirtKey) {
    case VK_F1: lstrcat (szHotKey, "F1"); break;
    case VK_F2: lstrcat (szHotKey, "F2"); break;
    case VK_F3: lstrcat (szHotKey, "F3"); break;
    case VK_F4: lstrcat (szHotKey, "F4"); break;
    case VK_F5: lstrcat (szHotKey, "F5"); break;
    case VK_F6: lstrcat (szHotKey, "F6"); break;
    case VK_F7: lstrcat (szHotKey, "F7"); break;
    case VK_F8: lstrcat (szHotKey, "F8"); break;
    case VK_F9: lstrcat (szHotKey, "F9"); break;
    case VK_F10: lstrcat (szHotKey, "F10"); break;
    case VK_F11: lstrcat (szHotKey, "F11"); break;
    case VK_F12: lstrcat (szHotKey, "F12"); break;
    case VK_INSERT : lstrcat (szHotKey, "INS"); break;
    case VK_DELETE : lstrcat (szHotKey, "DEL"); break;
    case VK_RETURN : lstrcat (szHotKey, "ENTER"); break;
    case VK_ESCAPE : lstrcat (szHotKey, "ESC"); break;
          
    default:
      if (szHotKey[0] != '\0') {
        int len = lstrlen(szHotKey);
        szHotKey[len] = char(iVirtKey);
        szHotKey[++len] = '\0';
        }
    }
  }

//---------------------------------------------------------------------------
// So eine Sch.... ! Ich habe 2 Tage intensiven Nachdenkens gebraucht, um
// herauszufinden, dass diese verd..... Prozedur ebenfalls exportiert
// gehoert!!!
//---------------------------------------------------------------------------
DLLExport LONG _export CALLBACK SubClassFunc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
  {
  switch (Message) {

    // alle Tastatur-Nachrichten sofort an mich weitergeben
    case WM_GETDLGCODE:
      return DLGC_WANTALLKEYS;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
      {
      if ((wParam != VK_CONTROL) &&
          (wParam != VK_MENU) &&
          (wParam != VK_SHIFT) &&
          (((char(wParam) >= 'A') && (char(wParam) <= 'Z')) ||
           ((char(wParam) >= '0') && (char(wParam) <= '9')) ||
          ((wParam >= VK_F1) && (wParam <= VK_F12)) ||
           (wParam == VK_INSERT) || (wParam == VK_DELETE) ||
           (wParam == VK_RETURN) || (wParam == VK_ESCAPE))) {
        char szHotKey[64];

        InterpreteHotkey (int(wParam), -1, szHotKey);
        SetWindowText (hWnd, szHotKey);
        SendMessage(hWnd, EM_SETSEL, 0, MAKELONG(0x7fff, 0x7fff));
        }
      else
      if (wParam == VK_TAB)
        {
        BOOL bDirection = FALSE;
        
        if (GetKeyState(VK_SHIFT) < 0)
          bDirection = TRUE;
        
        GetNextDlgTabItem (GetParent(hWnd), hWnd, bDirection);
        }
      }
      return FALSE;
      
    case WM_CHAR:
      return FALSE;
    
    default:
#ifdef STRICT
      return CallWindowProc((WNDPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#else
      return CallWindowProc((FARPROC)lpfnOldWndProc, hWnd, Message, wParam, lParam);
#endif
    }
  return FALSE;
  }



HotkeyList hkl[2];

#define  ID_ED_HOTKEY        101
#define  ID_LB_HOTKEY        102
#define  ID_BN_ADDHOTKEY     103
#define  ID_BN_DELETEHOTKEY  104

DLLExport BOOL _export CALLBACK HotKeyDlgProc (HWND hDlg, UINT msg,
                                     WPARAM wP, LPARAM lP)
  {
  static HotKey FAR *act ;
  char szHotKey[64];

  switch (msg) {
    case WM_INITDIALOG:
      {
      act = ActHotkey ;

      // in der RESTOOL-DLL ist nichts disabled!
      int iPos = lstrlen(szListClassName);
      if ((szListClassName[iPos-1] != '1') ||
          ((act != NULL) && (!act->doModify))) {
          // alles disablen
          EnableWindow (GetDlgItem(hDlg, ID_ED_HOTKEY), FALSE);
          EnableWindow (GetDlgItem(hDlg, ID_BN_ADDHOTKEY), FALSE);
          EnableWindow (GetDlgItem(hDlg, ID_BN_DELETEHOTKEY), FALSE);
          EnableWindow (GetDlgItem(hDlg, IDOK), FALSE);

          // Die DDS-Dialogbox ist auch kleiner
          RECT rc;
          GetWindowRect (hDlg, &rc);
          SetWindowPos (hDlg, 0, 0, 0, rc.right-rc.left, 135, 
                        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

          }
      else {
        // nur im Restool subclassen!
        hEditWnd = GetDlgItem(hDlg, ID_ED_HOTKEY);
        lpfnOldWndProc = (FARPROC)SetWindowLong(hEditWnd, GWL_WNDPROC, 
                                          (LPARAM)SubClassFunc);
        }
      
      hkl[0].VirtKey = 0;
      hkl[0].Modify  = 0;
      hkl[0].szHotkey[0] = '\0';      
      hkl[1].VirtKey = 0;
      hkl[1].Modify  = 0;
      hkl[1].szHotkey[0] = '\0';

      int vkCh = 0, Modify = 0;
      
      // gibt es Hotkeys, dann werden sie in die Liste gestellt
      if (act != NULL) {
        vkCh = act->KeyData.VirtKey;
        Modify = act->KeyData.Modify;

        InterpreteHotkey (vkCh, Modify, szHotKey);
        if (szHotKey[0] != '\0') {
          SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_ADDSTRING, 0, LPARAM(LPSTR(szHotKey)));

          hkl[0].VirtKey = vkCh;
          hkl[0].Modify  = Modify;
          lstrcpy (hkl[0].szHotkey, szHotKey);
          }


        vkCh = act->KeyData.VirtKey1;
        Modify = act->KeyData.Modify1;

        InterpreteHotkey (vkCh, Modify, szHotKey);
        if (szHotKey[0] != '\0') {
          SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_ADDSTRING, 0, LPARAM(LPSTR(szHotKey)));
          
          hkl[1].VirtKey = vkCh;
          hkl[1].Modify  = Modify;
          lstrcpy (hkl[1].szHotkey, szHotKey);
          }
        }
      }
      return (TRUE);

    case WM_COMMAND:
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK:
        case IDCANCEL:
          {
          if (CRACKER_wID == IDOK) {
            HotKeyData  kd = {0, 0, 0, 0};

            if (hkl[0].szHotkey[0] != '\0') {
              kd.Modify = hkl[0].Modify;
              kd.VirtKey = hkl[0].VirtKey;
              
              if (hkl[1].szHotkey[0] != '\0') {
                kd.Modify1 = hkl[1].Modify;
                kd.VirtKey1 = hkl[1].VirtKey;
                }
              }
               
            act = ActHotkey ;
            if (act != NULL)
              act->ModifyHotKey (kd);
            }

          EndDialog(hDlg, TRUE); /* Exits the dialog box        */
          if (lpfnOldWndProc != NULL)
            SetWindowLong (hEditWnd, GWL_WNDPROC, (DWORD) lpfnOldWndProc);
          return (TRUE);
          }
        
        // neuen Hotkey in die Liste stellen.
        // in meiner Idioten-Codierung ist die Anzhal der Hotkeys
        // leider auf zwei Eintraege beschraenkt.
        case ID_BN_ADDHOTKEY:
          {
          DWORD Cnt = SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_GETCOUNT, 0, 0L);
          if (Cnt < 2) {
          
            char szText[64];
            GetDlgItemText (hDlg, ID_ED_HOTKEY, szText, sizeof(szText));
            
            // Dieser Hotkey darf noch nicht existieren
            if (SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_FINDSTRINGEXACT, 
                                    WPARAM(-1), LPARAM(LPSTR(szText))) == LB_ERR) {
              SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_ADDSTRING, 0, LPARAM(LPSTR(szText)));

              hkl[Cnt].VirtKey = VirtKey;
              hkl[Cnt].Modify  = Modify;
              lstrcpy (hkl[Cnt].szHotkey, szText);
              }
            }
          else
            MessageBeep (0);
            
          break;
          }

        // selektierten Hotkey loeschen
        case ID_BN_DELETEHOTKEY:
          {
          DWORD dwIndex = SendDlgItemMessage(hDlg, ID_LB_HOTKEY, LB_GETCURSEL, 0, 0);
          if (dwIndex != LB_ERR) {
            SendDlgItemMessage (hDlg, ID_LB_HOTKEY, LB_DELETESTRING, WPARAM(dwIndex), 0);
            
            if (dwIndex == 0) {
              hkl[0].VirtKey = hkl[1].VirtKey;
              hkl[0].Modify  = hkl[1].Modify;
              lstrcpy (hkl[0].szHotkey, hkl[1].szHotkey);
              }
              
            hkl[1].VirtKey = 0;
            hkl[1].Modify  = 0;
            hkl[1].szHotkey[0] = '\0';
            }
          break;
          }
        }
      }
    }
  return (FALSE);
  }
  
/*------------------------------------------------------------------*\
*  Dialog-Funktionen                                                 *
\*------------------------------------------------------------------*/
/*
DLLExport BOOL _export FAR PASCAL HotKeyDlgProc (HWND hDlg, unsigned msg,
                                       WPARAM wP, LPARAM lP)
  {
  char lpStr[20];
  char cbstr[20];
  int  i;
  HotKey FAR *act ;

  switch (msg) {
    case WM_INITDIALOG :
      {
      int  vkCh;
      BOOL found = FALSE;

      lstrcpy (cbstr, "");
      act = ActHotkey ;
      vkCh = (act != NULL) ? act->KeyData.VirtKey : 0;
      for (i = 0; i < 256; i++) {
        if (LoadString (hLibInst, 1000+i, lpStr, sizeof(lpStr))) {
          SendDlgItemMessage (hDlg, ID_CBCHAR, CB_ADDSTRING, 
                                    0, LONG(LPSTR(lpStr)));
          if (i == vkCh) {
            found = TRUE;
            lstrcpy (cbstr, lpStr);
            }
          }
        }

      if ((act != NULL) && (!found)) {
        // Parameter 2 ... konvertiert virtuellen Code in ASCII-Zeichen
        vkCh = (MapVirtualKey (act->KeyData.VirtKey, 2));
        cbstr[0] = char(vkCh);
        cbstr[1] = 0;
        } 

      // Textfeld beschicken
      if (cbstr[0] != 0) 
        SendDlgItemMessage (hDlg, ID_CBCHAR, WM_SETTEXT, lstrlen(cbstr), LONG(LPSTR(cbstr)));
      else
        SendDlgItemMessage (hDlg, ID_CBCHAR, CB_SETCURSEL, 0, 0L);

      // CheckButtons beschicken
      if (act != NULL) {
        SendDlgItemMessage (hDlg, ID_CHSHIFT, BM_SETCHECK, 
                            (act->KeyData.Modify) & VKSHIFT, 0L);
        SendDlgItemMessage (hDlg, ID_CHCTRL, BM_SETCHECK, 
                            (act->KeyData.Modify) & VKCTRL, 0L);
        SendDlgItemMessage (hDlg, ID_CHALT, BM_SETCHECK, 
                            (act->KeyData.Modify) & VKALT, 0L);
        }

      int iPos = lstrlen(szListClassName);
      if ((szListClassName[iPos-1] != '1') ||
          ((act != NULL) && (!act->doModify))) {
          // alles disablen
          EnableWindow (GetDlgItem(hDlg, ID_CHSHIFT), FALSE);
          EnableWindow (GetDlgItem(hDlg, ID_CHCTRL), FALSE);
          EnableWindow (GetDlgItem(hDlg, ID_CHALT), FALSE);
          EnableWindow (GetDlgItem(hDlg, ID_CBCHAR), FALSE);
          EnableWindow (GetDlgItem(hDlg, IDOK), FALSE);
          }
      }
      return TRUE;

    case WM_COMMAND :
     
      switch (wP) {
        case ID_CBCHAR:
          switch (HIWORD(lP)) {
            case CBN_EDITCHANGE :
            case CBN_SELCHANGE  : 
            break;
            }
          break;
        case IDOK :
          {
          char cbstr[5];
          HotKeyData  kd = {0, 0};

          // Text aus dem Editfenster der Combo-Box holen
          SendDlgItemMessage (hDlg, ID_CBCHAR, WM_GETTEXT, 
                                    sizeof(cbstr)+1, LONG(LPSTR(cbstr)));

          if (lstrlen (cbstr) == 1) {         // genau ein Zeichen 
            UINT ui = VkKeyScan(*cbstr);
            if (ui >= 0)  {                   // virtueller Tastencode?
              if (HIBYTE(ui) == 1)            // Shift-Key?
                SendDlgItemMessage (hDlg, ID_CHSHIFT, BM_SETCHECK, 1, 0L);
              else 
                SendDlgItemMessage (hDlg, ID_CHSHIFT, BM_SETCHECK, 0, 0L);

              kd.VirtKey = LOBYTE(ui);
              }
            }
          else {
            // es war ein Zeichen aus der Ressource (F1..F10, ...)
            for (i = 1; i < 256; i++) {
              if (LoadString (hLibInst, 1000+i, lpStr, sizeof(lpStr))) 
                if (lstrcmp(lpStr, cbstr) == 0) {
                  kd.VirtKey = LOBYTE(i);
                  break;
                  }
              }
            }

          int State = (int)SendDlgItemMessage (hDlg, ID_CHSHIFT, BM_GETCHECK, 0, 0L);
          kd.Modify = (State) ? kd.Modify | VKSHIFT : kd.Modify & ~VKSHIFT ;

          State = (int)SendDlgItemMessage (hDlg, ID_CHCTRL, BM_GETCHECK, 0, 0L);
          kd.Modify = (State) ? kd.Modify | VKCTRL : kd.Modify & ~VKCTRL;

          State = (int)SendDlgItemMessage (hDlg, ID_CHALT, BM_GETCHECK, 0, 0L);
          kd.Modify = (State) ? kd.Modify | VKALT : kd.Modify & ~VKALT;

//          act = GetHotKey (Capture);
          act = ActHotkey ;
          if (act != NULL)
            act->ModifyHotKey (kd);

          EndDialog (hDlg, TRUE);
          }  
          return TRUE;
        case IDCANCEL :
          EndDialog (hDlg, FALSE);
          return TRUE;
        }
    }
  return FALSE;
  }
*/
