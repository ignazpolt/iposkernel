////////////////////////////////////////////////////////////////
//  Generieren der Scripts
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genscr.cpv   1.8   07 Jun 2000 11:51:36   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/genscr.cpv  $
// 
//    Rev 1.8   07 Jun 2000 11:51:36   Wolfgang
// 1.) GenFncProt gibt zurueck, ob Compilieren ok.
// 
//    Rev 1.7   16 Mar 1999 19:41:14   Wolfgang
// 1.) MainFile TRUE bei ShowScript.
// 
//    Rev 1.6   16 Mar 1999 16:12:38   Wolfgang
// 1.) ShowScript mit NULL zur Fenstererzeugung verwenden.
// 
//    Rev 1.5   05 Oct 1998 11:26:54   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   05 Nov 1997 09:14:02   Gerhold
// 32 Bit
// 
//    Rev 1.3   02 Feb 1996 10:50:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   02 Jan 1995 09:30:26   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   24 Jun 1994 16:54:48   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
//#include "subclass.hpp"
#define MODULENUM 94
#include "winass.hpp"
#include "scripthd.hpp"

#include "blandmdi.hpp"   // MakeNewChild

extern HWND hRsWnd;
extern HINSTANCE MyInstance;
BOOL GenFncProt (HWND hWnd,LPSTR FName)
  {
  char pattern[64];
  char outtxt[128];
  hRsWnd = hWnd;
  LoadString (MyInstance,ID_FCMPHEADLINE,pattern,sizeof(pattern));
  wsprintf (outtxt,pattern,FName);
  ShowMsg (outtxt,TRUE);
  UpdateWindow (hRsWnd);
  int res = FunctionPrototypes (FName);
  LoadString (MyInstance,ID_FCMPENDLINE,outtxt,sizeof(outtxt));
  ShowMsg (outtxt,TRUE);
  UpdateWindow (hRsWnd);
  return res == 0;
  }


DLLExport BOOL FAR PASCAL _export ScriptDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  static int sstops[] = { 141 , 207 , 243 , 291 , 333 } ;
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      {
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETTABSTOPS,5,LONG(LPINT(sstops)));
//      SubClassElements (hDlg,MyInstance);

      LoadScriptContent();
      FillScriptDlg (hDlg,ID_LIST);
      }
      break ;
/*
    case WM_CTLCOLOR :
      {
      LONG lres = GetCtlColor (hDlg,wP,lP,RetVal);
      if (RetVal)
        return BOOL (lres);   // ??? !!!! ???
      }
*/
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          UnloadScriptContent();
          EndDialog (hDlg,FALSE);
          break ;
        case ID_NEW :
          {
          char fName[128];
          if (GetCmpName (hDlg,ID_NEWSCRIPT,fName,sizeof(fName))) {
            if (GenerateScript (hDlg,fName)) {
              CreateScriptContent(fName);
              SendDlgItemMessage (hDlg,ID_LIST,LB_RESETCONTENT,0,0L);
              FillScriptDlg (hDlg,ID_LIST);
              }
            }
          }
        case ID_GENERATE :
          {
          char fName[128];
          int Sel = int (SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
          if (GetScriptFName (fName,Sel)) {
            if (GenerateScript (hDlg,fName)) {
              CreateScriptContent(fName);
              SendDlgItemMessage (hDlg,ID_LIST,LB_RESETCONTENT,0,0L);
              FillScriptDlg (hDlg,ID_LIST);
              }
            }
          }
          break ;
        case ID_WORKON :
          {
          char fName[128];
          int Sel = int (SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
          if (GetScriptFName (fName,Sel)) {
            ShowScript (NULL, fName, TRUE);
            UnloadScriptContent();
            EndDialog (hDlg,FALSE);
            }
          }
          break ;
        }
      break ;
    }
  return RetVal;
  }

void WorkOnScripts (HWND hWnd)
  {
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(ScriptDialog),MyInstance));
  BOOL res = DialogBox (MyInstance,"SCRIPT",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  }



DLLExport BOOL FAR PASCAL _export ProjectDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  static int sstops[] = { 141 , 207 , 500} ;
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      {
      SendDlgItemMessage (hDlg,ID_LISTSORTFILE,LB_SETTABSTOPS,3,LONG(LPINT(sstops)));
      SendDlgItemMessage (hDlg,ID_LISTSORTDESC,LB_SETTABSTOPS,3,LONG(LPINT(sstops)));

      LoadScriptContent();
      FillScriptDlg (hDlg,ID_LISTSORTFILE);
      FillScriptDlg (hDlg,ID_LISTSORTDESC);

      CheckRadioButton (hDlg, IDRB_SORTDESC, IDRB_SORTFILE, IDRB_SORTFILE);
      ShowWindow (GetDlgItem(hDlg, ID_LISTSORTDESC), SW_HIDE);
      }
      break ;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case ID_LISTSORTDESC:
        case ID_LISTSORTFILE:
          if (HIWORD(lP) == LBN_DBLCLK)
            SendMessage (hDlg, WM_COMMAND, IDOK, 0);
          break;

        case IDRB_SORTFILE:
          ShowWindow (GetDlgItem(hDlg, ID_LISTSORTFILE), SW_SHOW);
          ShowWindow (GetDlgItem(hDlg, ID_LISTSORTDESC), SW_HIDE);
          break;

        case IDRB_SORTDESC:
          ShowWindow (GetDlgItem(hDlg, ID_LISTSORTFILE), SW_HIDE);
          ShowWindow (GetDlgItem(hDlg, ID_LISTSORTDESC), SW_SHOW);
          break;

        case IDOK:
          {
          char fName[128];
          int CurList = IsWindowVisible (GetDlgItem(hDlg, ID_LISTSORTFILE)) ? ID_LISTSORTFILE : ID_LISTSORTDESC;
          int Sel = int (SendDlgItemMessage (hDlg, CurList, LB_GETCURSEL, 0, 0L));
          if (GetScriptFName (fName,Sel)) {
            ShowScript (NULL, fName, TRUE);
            UnloadScriptContent();
            EndDialog (hDlg,TRUE);
            }
          }
          break ;

        case IDCANCEL:
          {
          UnloadScriptContent();
          EndDialog (hDlg,FALSE);
          }
          break;  
        }
      break ;
    }
  return RetVal;
  }


void OpenProjects (HWND hWnd)
  {
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(ProjectDialog),MyInstance));
  BOOL res = DialogBox (MyInstance,"PROJECTS",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  }
