//
//  $Header:   P:/marille/clinicum/dmwapi/rev/singl.cpv   1.16   05 Oct 1998 11:17:44   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/singl.cpv  $
// 
//    Rev 1.16   05 Oct 1998 11:17:44   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.15   28 May 1998 16:56:06   Hannes
// Richtiges Center...
// 
//    Rev 1.14   15 Apr 1998 13:49:06   Hannes
// Knoepfe bei Single - Liste / Dimension der Knoepfe abziehen...
// 
//    Rev 1.13   29 Jul 1997 15:25:00   gerhold
// WM_INITDIALOG ... richtigen Rueckgabewert setzen wegen SetFocus
// 
//    Rev 1.12   17 Apr 1997 15:12:18   Hannes
// Suche des echten Vaterfensters
// 
//    Rev 1.11   07 Apr 1997 19:21:04   gerhold
// Anpassung der Dialogboxen an die ToolEdit - Groesse
// 
//    Rev 1.10   25 Jul 1996 19:58:58   GERHOLD
// 32 Bit Dialoge sind in der Resource und nicht mehr als Templates im Speicher
// 
//    Rev 1.9   02 Feb 1996 10:46:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   05 Dec 1995 15:55:04   GERHOLD
// Der Stil WS_BORDER hat bei der Listbox gefehlt
// 
//    Rev 1.7   28 Nov 1995 13:07:18   GERHOLD
// Beim Erzeugen des Listendialoges muss man LBS_NOTIFY angeben!!
// 
//    Rev 1.6   24 Nov 1995 17:45:04   MARTIN
// ein kleines Woertchen: BOOL !!!!
// 
//    Rev 1.5   23 Nov 1995 14:43:28   GERHOLD
// 
//    Rev 1.4   23 Nov 1995 13:28:48   GERHOLD
// Breite und Hoehe koennen in ShowToolList angegeben werden.
// 
//    Rev 1.3   31 Mar 1995 13:10:48   HANNES
//  
// 
//    Rev 1.2   09 Nov 1994 10:43:12   GERHOLD
// 
//    Rev 1.1   25 Jul 1994 09:43:16   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:49:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   29 Nov 1993 08:39:44   HANNES
// Doppelklick zur Selektion
// 
//    Rev 1.0   18 Aug 1993 10:48:40   HANNES
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
#include <memory.h>      // notwendig wegen DLGTEMPL.HPP
#include "dds32.h"
#include "globmem.h"
#include "multl.hpp"
#include "flist.hpp"
#include "dlgtempl.hpp"  // Templates statt Dialog-Resourcen

static HWND ActDlgOwner;
void SinglList::SetPos(HWND hDlg)
  {
  SetDlgPos (hDlg,ActDlgOwner,fr,cr);
  }

void SinglList::Fill (HWND hWnd)
  {
  for (LPSTR h = Strings ; *h ; ) {
    SendMessage (hWnd,LB_ADDSTRING,0,LONG(h));
    h += lstrlen (h) + 1;
    }
  }

void SinglList::Select (HWND hWnd)
  {
  SendMessage (hWnd,LB_SETCURSEL,res,0L);
  }

void SinglList::GetRes (HWND hWnd)
  {
  res = int (SendMessage (hWnd,LB_GETCURSEL,0,0L));
  }

SinglList FAR *sl;

fList FAR *SingleListDrw;
#define ID_LIST   100
extern void setFieldButtonUp ();
DLLExport BOOL _export CALLBACK SingleListDlg (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP)
  {
  BOOL res = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      {
      //******************************************************************
#ifdef WIN32
      LONG dbu = GetDialogBaseUnits();
      BOOL WithDel = FALSE;
      POINT pt = *LPPOINT(lP);
      int x = LOWORD(dbu)*pt.x / 4;
      int y = HIWORD(dbu)*(pt.y - 14) / 8;
      int h = HIWORD(dbu)*14 / 8;
      SetWindowPos (hDlg, 0, 0, 0, x, y, SWP_NOMOVE | SWP_NOZORDER);

      MoveWindow (GetDlgItem(hDlg, IDOK), 0, y-h, x/2, h, TRUE);
      MoveWindow (GetDlgItem(hDlg, IDCANCEL), x/2,y-h,x-(x/2),h, TRUE);
      MoveWindow (GetDlgItem(hDlg, 100), 0, 0, x, y-h, TRUE);
#endif
      //******************************************************************

      sl->SetPos (hDlg);
      sl->Fill (GetDlgItem (hDlg,ID_LIST));
      sl->Select (GetDlgItem (hDlg,ID_LIST));
      SetFocus (GetDlgItem (hDlg,ID_LIST));
      }
#ifdef WIN32
      return FALSE;        // ICH KUEMMERE MICH SELBER UM DEN FOCUS
#else
      return TRUE;         // ich kuemmere mich selber um den Focus
#endif
      break ;

    case WM_MEASUREITEM :
      res = SingleListDrw->Measure (hDlg,(MEASUREITEMSTRUCT FAR *) lP);
      break ;
    case WM_DRAWITEM :
      res = SingleListDrw->Draw ((DRAWITEMSTRUCT FAR *) lP);
      break ;
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case ID_LIST :
          if (CRACKER_wNotify != LBN_DBLCLK) break ;
        case IDOK :
          sl->GetRes (GetDlgItem (hDlg,ID_LIST));
          setFieldButtonUp ();
          EndDialog (hDlg,TRUE);
          break ;
        case IDCANCEL :
          setFieldButtonUp ();
          EndDialog (hDlg,FALSE);
          break ;
        }
      }
      break ;
    }
  return res ;
  }

extern HINSTANCE hLibInst;
#define SINGLELISTDRW_FORMAT 4
//---------------------------------------------------------------------------
// Die Parameter w und h sind Default-Parameter und im Header-File MLIST.HPP
// mit 0 vorbelegt.
// Werden w und h mit 0 angegeben, so hat die Dialogbox eine vorgegebene 
// Groesse.
// Ist die Breite aber -1 so wird sie an das fieldrect angepasst.
//---------------------------------------------------------------------------
DLLExport BOOL _export SinglList::WorkOn (HWND hWnd,LPRECT fieldRect,LPRECT ClientRect, 
                                int w, int h)
  {
  for (HWND hWPopUpParent = hWnd; 
            ((IsWindow (hWPopUpParent)) && ((GetWindowLong (hWPopUpParent,GWL_STYLE) & WS_CHILD) == WS_CHILD)) ;
                hWPopUpParent = GetParent(hWPopUpParent) ) ;
  hWnd = hWPopUpParent;
  sl = this ;
  fr = fieldRect;
  cr = ClientRect;
  SingleListDrw = new fList(ID_LIST,SINGLELISTDRW_FORMAT,NULL,SEARCHMODE_SORTED);
/*--------------------------------------------------------------------------
  SLISTDLG DIALOG 64, 51, 144, 72
  STYLE WS_POPUP | WS_BORDER
  FONT 8, "Arial"
  BEGIN
    LISTBOX 100, 0, 0, 144, 54, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | 
                                LBS_DISABLENOSCROLL | WS_VSCROLL | WS_TABSTOP
    PUSHBUTTON "OK", IDOK, 0, 58, 72, 14
    PUSHBUTTON "Abbruch", IDCANCEL, 72, 58, 72, 14
  END
--------------------------------------------------------------------------*/
  if (w <= 0) {
//    w = 144;
//  else if (w < 0)
    // normalerweise ist beim SystemFont bei Dialogboxen der 
    // Skalierungsfaktor 4, bei "ARIAL 8" aber besser 5.
    w = (fr->right - fr->left) * 5 / LOWORD(GetDialogBaseUnits());
      if (w < 70) w = 70;
    }

  if (h <= 0)
    h = 72;

//**************************************************************************
// Momentan koennen die Dialogtemplates nicht unter WIN32 verwendet werden!
// Deshalb wird auf die alten Resourcen zurueckgegriffen!
//**************************************************************************
#ifdef WIN32
  POINT pt;
  pt.x = w;
  pt.y = h;
  BOOL res = DialogBoxParam (hLibInst,"SLISTDLG",ActDlgOwner = hWnd,DLGPROC(SingleListDlg),LPARAM(&pt));
//  BOOL res = DialogBoxIndirect (hLibInst,LPDLGTEMPLATE(dc.res),
//                                ActDlgOwner = hWnd,DLGPROC(SingleListDlg));
#else
  DlgContainer dc (DialogBoxHeader (WS_POPUP | WS_BORDER | WS_VISIBLE,0,0,w,h,"",8,"Arial"));
  dc += ControlData (0,0,w,h-14,100,WS_VISIBLE | WS_GROUP | WS_CHILD | WS_BORDER |
                                    LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | 
                                    LBS_DISABLENOSCROLL | LBS_NOTIFY |
                                    WS_VSCROLL | WS_TABSTOP,0x83,"");
  dc += ControlData (0,h-14,w/2,14,IDOK,WS_GROUP | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_CHILD,0x80,"Ok");
  dc += ControlData (w/2,h-14,w-w/2,14,IDCANCEL,WS_GROUP | WS_VISIBLE | WS_TABSTOP | WS_CHILD,0x80,"Abbruch");

  BOOL res = DialogBoxIndirect (hLibInst,dc.res,ActDlgOwner = hWnd,DLGPROC(SingleListDlg));
#endif

  delete SingleListDrw;
  return res;
  }

DLLExport _export SinglList::SinglList (LPSTR txt,int r)
  {
  Strings = txt;
  res = r;
  }

DLLExport _export SinglList::~SinglList ()
  {
  }

