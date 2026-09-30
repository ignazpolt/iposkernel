//////////////////////////////////////////////////////////////
//
//  Anzeigen einer Multiliste
//
//  $Header:   P:/marille/clinicum/dmwapi/rev/mlist.cpv   1.4   05 Oct 1998 11:11:56   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/mlist.cpv  $
// 
//    Rev 1.4   05 Oct 1998 11:11:56   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   02 Feb 1996 10:46:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   09 Dec 1994 20:41:46   GERHOLD
// subclass raus
// 
//    Rev 1.1   25 Jul 1994 09:43:12   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:48:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   09 Jun 1993 15:08:12   HANNES
// ??
// 
//    Rev 1.1   07 Jun 1993 11:22:30   HANNES
// Einspaltige Listen
// 
//    Rev 1.0   28 May 1993 21:27:40   HANNES
// Initial revision.
//
//////////////////////////////////////////////////////////////
//
//  Aufbau des Uebergabebuffers:
//    text 0 \0 Eintrag 00 \0 Eintrag 01 \0 ... Eintrag 0n\0\0
//
#include <windows.h>
#include "dds32.h"
#include "mlist.hpp"
//#include "subclass.hpp"

extern HINSTANCE hLibInst;
static LPMLIST actList;

#define ID_EDFIELDBASE      120
#define ID_DLIST1BASE       100
#define ID_DLIST2BASE       110

extern void setFieldButtonUp ();
DLLExport BOOL _export WINAPI MListDlgProc (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP)
  {
  int i,j;
  BOOL res = FALSE ;

  switch (msg) {
    case WM_INITDIALOG :
      for (i = 0 ; i < MAXROWS ; i++) {
        BOOL enableed = (i < actList->AnzDSet) ;
        BOOL enabled1 = ((i < actList->AnzDSet) && (actList->d[i].doSelect));
        BOOL enabled2 = ((i < actList->AnzDSet) && (actList->d[i].doSelect) &&
                          (actList->d[i].allowMulti));
        EnableWindow (GetDlgItem (hDlg,ID_EDFIELDBASE+i),enableed);
        EnableWindow (GetDlgItem (hDlg,ID_DLIST1BASE+i),enabled1);
        HWND h2combo = GetDlgItem (hDlg,ID_DLIST2BASE+i);
        if (IsWindow (h2combo))
          EnableWindow (h2combo,enabled2);
        if (i < actList->AnzDSet) {
          SetDlgItemText (hDlg,ID_EDFIELDBASE+i,actList->d[i].DocName);
          if (actList->d[i].doSelect) {
            for (j = 0 ; j < actList->d[i].AnzDSet ; j++)
              SendMessage (GetDlgItem (hDlg,ID_DLIST1BASE+i),CB_ADDSTRING,
                                0,LONG(LPSTR(actList->d[i].DSetName[j])));
            SendMessage (GetDlgItem (hDlg,ID_DLIST1BASE+i),CB_SETCURSEL,0,0L);
            actList->d[i].Selektion[0] = 0;
            actList->d[i].AnzSelection = 1;
            }
          else
            actList->d[i].AnzSelection = 0;

          if ((actList->d[i].doSelect) && (actList->d[i].allowMulti)) {
            for (j = 0 ; j < actList->d[i].AnzDSet ; j++)
              SendMessage (GetDlgItem (hDlg,ID_DLIST2BASE+i),CB_ADDSTRING,
                                0,LONG(LPSTR(actList->d[i].DSetName[j])));
            SendMessage (GetDlgItem (hDlg,ID_DLIST2BASE+i),CB_SETCURSEL,
                    actList->d[i].AnzDSet - 1,0L);
            actList->d[i].Selektion[1] = actList->d[i].AnzDSet - 1;
            actList->d[i].AnzSelection += 1;
            }
          }
        }
//      SubClassElements (hDlg,hLibInst);
      res = TRUE ;
      break ;
/*
    case WM_CTLCOLOR :
      {
      LONG lres = GetCtlColor (hDlg,wP,lP,res);
      if (res)
        return BOOL (lres);   // ??? !!!! ???
      }
      break ;
*/
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      if (CRACKER_wNotify == CBN_SELCHANGE) {
        if ((CRACKER_wID >= ID_DLIST1BASE) && (CRACKER_wID <= (ID_DLIST1BASE + MAXROWS)))
          actList->d[CRACKER_wID - ID_DLIST1BASE].Selektion[0] = 
              int (SendDlgItemMessage (hDlg,CRACKER_wID,CB_GETCURSEL,0,0L));
        if ((CRACKER_wID >= ID_DLIST2BASE) && (CRACKER_wID <= (ID_DLIST2BASE + MAXROWS)))
          actList->d[CRACKER_wID - ID_DLIST2BASE].Selektion[1] = 
              int (SendDlgItemMessage (hDlg,CRACKER_wID,CB_GETCURSEL,0,0L));
        res = TRUE ;
        }
      if (CRACKER_wID == IDOK)
        EndDialog (hDlg,TRUE) , res = TRUE , setFieldButtonUp ();
      if (CRACKER_wID == IDCANCEL)
        EndDialog (hDlg,FALSE) , res = TRUE , setFieldButtonUp ();
      }
      break ;
    }
  return res;
  }

DLLExport BOOL _export WINAPI ShowMultiList (HWND hWParent,LPMLIST Def)
  {
  actList = Def;
  BOOL enabled2 = TRUE ;
  for (int i = 0 ; i < MAXROWS ; i++)
    enabled2 = ((i < actList->AnzDSet) && (actList->d[i].doSelect) &&
                      (actList->d[i].allowMulti) && (enabled2));

  LPSTR dlgname = enabled2 ? "MLIST" : "M1LIST" ;
  return DialogBox(hLibInst,dlgname,hWParent,DLGPROC(MListDlgProc));
  }
