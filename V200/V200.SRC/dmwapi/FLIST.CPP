//
//  $Header:   P:/marille/clinicum/dmwapi/rev/flist.cpv   1.8   05 Oct 1998 11:11:28   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/flist.cpv  $
// 
//    Rev 1.8   05 Oct 1998 11:11:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   05 Feb 1997 15:31:42   GERHOLD
// 
//    Rev 1.6   31 Jan 1997 11:14:02   GERHOLD
// ::Draw ... cField wird mit COLORHIGHLIGHTTEXT ausgegeben
// 
//    Rev 1.5   21 Oct 1996 18:53:06   HANNES
// Selektion gleich wie bei normalen Listen
// 
//    Rev 1.4   22 Mar 1996 12:13:24   HANNES
// Aenderungen Hannes
// 
//    Rev 1.3   04 Feb 1996 15:42:20   HANNES
// Trennung COMPILE - DDSMEM
// 
//    Rev 1.2   02 Feb 1996 10:46:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   09 Nov 1994 10:43:06   GERHOLD
// 
//    Rev 1.0   24 Jun 1994 16:48:46   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.3   14 Feb 1994 19:50:24   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.2   05 Jul 1993 15:01:58   HANNES
// Tabs
// 
//    Rev 1.1   09 May 1993 17:45:44   HANNES
// Suchen in der Listbox..
// 
//    Rev 1.0   06 May 1993 21:31:00   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "font.hpp"
#include "cfield.hpp"
#include "flist.hpp"
#define NODLL
#define WITHINDDS
#include "toolbar.hpp"

extern void ExtSetTwipsMap (HDC hDC,double scale,int xp,int yp);

DLLExport LPVOID _export fList::operator new (size_t size)
  {
  return GetGlobMem (size);
  }

DLLExport void _export fList::operator delete (LPVOID obj)
  {
  FreeGlobMem (obj);
  }

extern double ctool_rfact ;

struct fListCallBack {
  WORD dsState;
  fList FAR *f;
  };
#define TABWIDTH  (int (1440.0 / 2.504))
DLLExport int _export WINAPI SearchNextTab (int x,int FAR *TabPos,int AnzTabs)
  {
  if (x < TabPos[0]) return TabPos [0];
  for (int i = 0 ; i < AnzTabs - 1 ; i++) {
    if ((x >= TabPos[i]) && (x < TabPos[i+1])) return TabPos [i+1];
    }
  // dahinter gehts mit cm Abstaenden weiter
  return ((x / TABWIDTH) + 1) * TABWIDTH;
  }

void fList::GetTab (TCB FAR *b)
  {
  if (TabPos != NULL) {
    int x = b->xold ;
    for (int i = 0 ; i < b->AnzTabs ; i++) {
      x = SearchNextTab (x,TabPos,GetBlockSize(TabPos) / sizeof(int));
      }
    b->xnew = x ;
    b->isdone = TRUE ;
    }
  }

void WINAPI FldBackCmd (int Cmd,LPVOID Data,LPVOID PrivData)
  {
  if (Cmd == CALLBACKCMD_GETNEXTTAB) {
    fListCallBack FAR *cb = (fListCallBack FAR *) PrivData;
    cb->f->GetTab ((TCB FAR *)Data) ;
    }
  else if (Cmd == CALLBACKCMD_GETFONTREFWND) {
    FontRefWndBuffer FAR *f = (FontRefWndBuffer FAR *) Data;
    f->IsDone = TRUE ;
    f->RefWnd = 0;
    }
  }

#define RESERVE 50
void CheckStrLen (LPSTR txt,int xb,int xe,HDC hDC)
  {
  LPSTR h = txt;
  int len = xe - xb - RESERVE;
  int cx;
  for ( int i = 0 ; *h ; h++ , i++) {

#ifdef WIN32
    SIZE size;
    GetTextExtentPoint32 (hDC,txt,i,&size);
    cx = size.cx;
#else
    cx = LOWORD(GetTextExtent (hDC,txt,i));
#endif

    if ((i > 0) && (cx > len)) {
      h[-1] = '\0';
      break ;
      }
    }
  }

#define MAXPARTS  20
DLLExport void _export WINAPI CheckOutTxt (LPSTR txt,HDC hDC,int Format,int FAR *TabPos,int AnzTabs)
  {
  if (TabPos != NULL) {
    // Wenn, dann muessen die Dinger auch ueberprueft werden, ob sie Platz
    // haben
    LPSTR ptxt[MAXPARTS];
    lmemset (ptxt,'\0',sizeof(ptxt));
    LPSTR h = txt;

    BOOL doSet = TRUE ;
    // Zerlegen des Strings ('\t' -> '\0', Alle Teile werden mit ptxt 
    // referenziert
    for (int j = 0 ; *h ; h++ ) {
      if (doSet) {
        ptxt[j++] = h ;
        doSet = FALSE ;
        }
      if (*h == '\t') {
        *h = '\0';
        doSet = TRUE ;
        }
      }
    int x = 0 ;

    // Alle Teiltexte ueberpruefen
    SelectObject (hDC,GetFontHandle(0,MAPTYPE_TYPOGRAPHIC,Format,0));
    for (int i = 0 ; i < j - 1 ; i++) {
      int xn = SearchNextTab (x,TabPos,AnzTabs);
      CheckStrLen (ptxt[i],x,xn,hDC);
      x = xn;
      }

    // Und wieder zusammenstoppelen
    char tb[2] ;
    tb[0] = '\t';
    tb[1] = '\0';

    char ntxt[256];
    *ntxt = '\0';
    for (i = 0 ; i < j ; i++) {
      if (i == 0) lstrcpy (ntxt,ptxt[i]);
      else        lstrcat (ntxt,ptxt[i]);
      if (i < j - 1) lstrcat (ntxt,tb);
      }

    lstrcpy (txt,ntxt);
    }
  }

DLLExport BOOL _export fList::Draw (DRAWITEMSTRUCT FAR *ds)
  {
  if (ds->CtlID == CtlID) {
    DWORD OldBack;
    if (ds->itemState & ODS_SELECTED)
      OldBack = SetBkColor (ds->hDC, GetSysColor(COLOR_HIGHLIGHT));
    else
      OldBack = SetBkColor (ds->hDC, RGB(255,255,255));

    // Loeschen des Hintergrundes
    ExtTextOut (ds->hDC, ds->rcItem.left,ds->rcItem.top, ETO_OPAQUE, LPRECT(&ds->rcItem), NULL, 0, NULL);

    cField FAR *f = new cField (TRANSPARENT,DefFormat,0,0,-1,1,FALSE);

    char outTxt[256];
    outTxt[0] = '\0';
    if ((itot != NULL) && (ds->itemData))
      (* itot) (outTxt,LPVOID (ds->itemData),sizeof(outTxt),TRANSLATE_FORDRAW,
              (ds->itemState & ODS_SELECTED) ? ActShortCut : NULL);
    else {
      if (ds->itemData)
        lstrncpy (outTxt,LPSTR(ds->itemData),sizeof(outTxt));
      else
        SendMessage (ds->hwndItem,LB_GETTEXT,ds->itemID,LONG(LPSTR(outTxt)));
      }

    // Zeichnen des Textes durch neugenerieren eines Feldes
    SaveDC (ds->hDC);
    ExtSetTwipsMap (ds->hDC,ctool_rfact,ds->rcItem.left - xLeft,ds->rcItem.top);
    f->SetWindow (ds->hwndItem);

    f->SetScale (ctool_rfact,MAPTYPE_TYPOGRAPHIC);
    f->SetVOrg (ds->rcItem.left - xLeft,ds->rcItem.top,0);

    CheckOutTxt (outTxt,ds->hDC,DefFormat,TabPos,sizeof(TabPos) / sizeof(int));
    *f = outTxt;

    fListCallBack cb;
    cb.dsState = ds->itemState;
    cb.f = this;
    f->InstallCallBack (FldBackCmd,&cb,sizeof(cb));

    if (ds->itemState & ODS_SELECTED)
      f->SetOutColor (GetSysColor(COLOR_HIGHLIGHTTEXT));

    f->Paint (ds->hDC,0,FALSE);
    RestoreDC (ds->hDC,-1);

    // Focus Zeichnen
    if (ds->itemState & ODS_FOCUS) {
      DrawFocusRect (ds->hDC,&ds->rcItem);
      }
    SetBkColor (ds->hDC, OldBack);
    delete f ;

    return TRUE ;
    }
  else
    return FALSE ;
  }


DLLExport BOOL _export fList::Measure (HWND hDlg,MEASUREITEMSTRUCT FAR *ms)
  {
  if (ms->CtlID == CtlID) {
    RECT r;
    HWND hLWnd = GetDlgItem(hDlg,ms->CtlID);
    GetClientRect (hLWnd,&r);
    ms->itemWidth = r.right;
    HDC htdc = CreateDC ("DISPLAY",NULL,NULL,NULL);
    ExtSetTwipsMap (htdc,ctool_rfact,0,0);
    GetFontHandle(0,MAPTYPE_TYPOGRAPHIC,DefFormat,-1);
    LPFORMATMETRIC lpfm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,DefFormat);
    POINT pt[2];
    pt[0].x = pt[1].x = 0;
    pt[0].y = 0;
    pt[1].y = lpfm->yHeight;
    LPtoDP (htdc,pt,2);
    ms->itemHeight = pt[1].y - pt[0].y;
    DeleteDC (htdc);
    int nbottom = (r.bottom / ms->itemHeight) * ms->itemHeight;
    return TRUE ;
    }
  else
    return FALSE ;
  }

DLLExport _export fList::fList(UINT ID,int DF,ITEMTOTEXT it,int SM)
  {
  DefFormat = DF;
  CtlID = ID;
  itot = it;
  SearchMode = SM;

  TabPos = NULL;
  }

WNDPROC DefListProc;
DLLExport LONG _export WINAPI GetCR (HWND hLWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  switch (msg) {
    case WM_GETDLGCODE :
      if (wP == VK_RETURN)
        return LONG (DLGC_WANTMESSAGE);
      else
#ifdef STRICT
        return CallWindowProc (DefListProc,hLWnd,msg,wP,lP);
#else
        return CallWindowProc ((FARPROC)DefListProc,hLWnd,msg,wP,lP);
#endif
      break ;
    default :
#ifdef STRICT
      return CallWindowProc (DefListProc,hLWnd,msg,wP,lP);
#else
      return CallWindowProc ((FARPROC)DefListProc,hLWnd,msg,wP,lP);
#endif
    }
  }

DLLExport void _export SubClassSearchBox (HWND hLWnd)
  {
  DefListProc = WNDPROC (SetWindowLong (hLWnd,GWL_WNDPROC,LONG(GetCR)));
  }

void PushItem (GLOBALHANDLE FAR &hGres,int AnzItems,WORD sel)
  {
  if (hGres == 0)
    hGres = GlobalAlloc (GMEM_MOVEABLE,0x8000);
  WORD FAR *base = (WORD FAR *) GlobalLock (hGres);
  base[AnzItems] = sel;
  GlobalUnlock (hGres);
  }

GLOBALHANDLE fList::SearchItems (HWND hLWnd,LPSTR Text,int FAR &AnzItems,
                                      GLOBALHANDLE hGold,int Anzold)
  {
  GLOBALHANDLE res = 0 ;
  int len = lstrlen (Text);
  char Acttxt[LIST_MAXSHORT];
  lstrcpy (Acttxt,Text);
  AnsiUpper (Acttxt);
  AnzItems = 0;
  if (itot != NULL) {
    if (hGold == 0) {
      // Ganze Listbox muss durchsucht werden
      /////////////////////////////////////////
      WORD count = WORD (SendMessage (hLWnd,LB_GETCOUNT,0,0L));

      for (WORD i = 0 ; i < count ; i++) {
        DWORD data = SendMessage (hLWnd,LB_GETITEMDATA,i,0L);
        char cmpTxt[256];
        (* itot) (cmpTxt,LPVOID (data),sizeof(cmpTxt),TRANSLATE_FORSEARCH,NULL);
        cmpTxt[len] = '\0';
        AnsiUpper (cmpTxt);
        if (lstrcmp (cmpTxt,Acttxt) == 0) {
          PushItem (res,AnzItems,i);
          AnzItems ++ ;
          }
        }
      }
    else {
      // Nur die bereits bestehenden Selektionen weiter eingrenzen
      //////////////////////////////////////////////////////////////////
      WORD FAR *base = (WORD FAR *) GlobalLock (hGold);
      for (int i = 0 ; i < Anzold ; i ++ ) {
        DWORD data = SendMessage (hLWnd,LB_GETITEMDATA,base[i],0L);
        char cmpTxt[256];
        (* itot) (cmpTxt,LPVOID (data),sizeof(cmpTxt),TRANSLATE_FORSEARCH,NULL);
        cmpTxt[len] = '\0';
        AnsiUpper (cmpTxt);
        if (lstrcmp (cmpTxt,Acttxt) == 0) {
          PushItem (res,AnzItems,base[i]);
          AnzItems ++ ;
          }
        }
      GlobalUnlock (hGold);
      }
    }
  return res;
  }

int AnzSame (LPSTR Text,LPSTR cmp)
  {
  AnsiUpper (Text);
  int i = 0 ;
  for ( ; (Text[i] && cmp[i]) ; ) {
    if (Text[i] == cmp[i]) i ++ ;
    else break ;
    }
  return i;
  }

DLLExport WORD _export fList::SearchBest (HWND hLWnd,LPSTR Text)
  {
  WORD res = 0;
  if ((itot != NULL) && (Text != NULL) && (*Text)) {
    char ActTxt[LIST_MAXSHORT];
    lstrncpy (ActTxt,Text,sizeof(ActTxt));
    AnsiUpper (ActTxt);
    WORD count = WORD (SendMessage (hLWnd,LB_GETCOUNT,0,0L));

    iCaretPos = 0;
    for (WORD i = 0 ; i < count ; i++) {
      DWORD data = SendMessage (hLWnd,LB_GETITEMDATA,i,0L);
      char cmpTxt[256];
      (* itot) (cmpTxt,LPVOID (data),sizeof(cmpTxt),TRANSLATE_FORSEARCH,NULL);
      AnsiUpper (cmpTxt);
      int samechars = AnzSame (cmpTxt,ActTxt);
      if (samechars > iCaretPos) {
        res = i;
        if (ActSels) {
          GlobalFree (ActSels) ;
          ActSels = 0;
          }
        for (int j = 0 ; j < samechars ; j++)
          ActShortCut[j] = ActTxt[j];
        ActShortCut[j] = '\0';
        AnzItems = 0;
        iCaretPos = samechars ;
        }

      if ((iCaretPos > 0) && (samechars == iCaretPos)) {
        PushItem (ActSels,AnzItems,i);
        AnzItems ++ ;
        }
      }
    }
  return res;
  }

WORD fList::NextSel (HWND hLWnd)
  {
  WORD res;
  if (ActSels) {
    SelIndex += 1 ;
    if (SelIndex >= WORD (AnzItems)) SelIndex = 0;
    res = ActSel (hLWnd);
    }
  else {
    res = WORD (SendMessage (hLWnd,LB_GETCURSEL,0,0L));
    res += 1;
    WORD count = WORD (SendMessage (hLWnd,LB_GETCOUNT,0,0L));
    if (res >= count) res = 0;
    }
  return res;
  }

WORD fList::ActSel (HWND hLWnd)
  {
  WORD res;
  if (ActSels) {
    WORD FAR *base = (WORD FAR *) GlobalLock (ActSels);
    res = base[SelIndex];
    GlobalUnlock (ActSels);
    }
  else {
    // Die Position von Windows erfragen
    res = WORD (SendMessage (hLWnd,LB_GETCURSEL,0,0L));
    }
  return res;
  }

DLLExport LONG _export fList::ChartoItem (HWND hLWnd,WORD wKey,int iWinCaretPos)
  {
#ifdef WIN32
  UINT Id = (UINT)GetWindowLong (hLWnd,GWL_ID);
#else  
  WORD Id = GetWindowWord (hLWnd,GWW_ID);
#endif

  if (Id == CtlID) {
    BOOL switchNext = FALSE ;
    BOOL doIt = TRUE ;
    if (wKey == '\b') {
      if (iCaretPos > 0)
        iCaretPos --;
      }
    else if (wKey == '\n') {
      switchNext = TRUE ;
      }
    else if (wKey == '\r') {
      doIt = FALSE ;
      }
    else {
      if (iCaretPos < LIST_MAXSHORT - 1)
        ActShortCut [iCaretPos++] = char (wKey) ;
      }
    ActShortCut [iCaretPos] = '\0';

    WORD Sel;
    if (doIt) {
      if (switchNext) {
        // Weiter zum naechsten passenden Eintrag
        ////////////////////////////////////////////
        Sel = NextSel (hLWnd);
        }
      else {
        if (iCaretPos == 0) {
          // Buffer muss geloescht werden
          AnzItems = 0;
          SelIndex = 0;
          if (ActSels) {
            GlobalFree (ActSels);
            ActSels = 0;
            }
          Sel = 0;
          }
        else {
          // Neuinitialisieren des Suchbuffers
          int nAnz;
          GLOBALHANDLE hGold;
          if (wKey != '\b')
            hGold = ActSels ;
          else
            hGold = 0;
          GLOBALHANDLE hGres = SearchItems (hLWnd,ActShortCut,nAnz,
                                            hGold,AnzItems
                                           );
          if (nAnz > 0) {
            if (ActSels) {
              GlobalFree (ActSels);
              ActSels = 0;
              }
            ActSels = hGres ;
            AnzItems = nAnz ;
            SelIndex = 0;
            Sel = ActSel (hLWnd);
            }
          else {
            // Nix gefunden -> wieder rueckgaengig machen
            //////////////////////////////////////////////
            MessageBeep (0);
            iCaretPos -- ;
            ActShortCut [iCaretPos] = '\0' ;
            Sel = ActSel (hLWnd);
            }
          }
        }
      SendMessage (hLWnd,LB_SETCURSEL,Sel,0L);
      }
    else {
      // cr wurde gedrueckt -> IDOK soll gesendet werden
      PostMessage (GetParent (hLWnd),WM_COMMAND,IDOK,0L);
      }
#ifdef TESTSEARCH
    HWND hDlg = GetParent (hLWnd);
    HWND TestWnd = GetParent (hDlg);
    char Text[40];
    wsprintf (Text,"%d %s %d %d Anz: %d Sel: %d",iCaretPos,ActShortCut,switchNext,doIt,AnzItems,Sel);
    if (IsWindow (TestWnd)) {
      HDC hDC = GetDC (TestWnd);
      RECT r;
      GetClientRect (TestWnd,&r);
      SelectObject (hDC,GetStockObject (WHITE_PEN));
      Rectangle (hDC,(r.left+r.right)/2-5,r.bottom - 65 ,
                     r.right-5,r.bottom - 35 );
      TextOut (hDC,(r.left+r.right)/2,r.bottom - 60,Text,
                                           lstrlen(Text));
      ReleaseDC (TestWnd,hDC);
      }
#endif
    }
  return -2;
  }

DLLExport _export fList::~fList ()
  {
  if (ActSels) {
    GlobalFree (ActSels);
    ActSels = 0;
    }
  if (TabPos != NULL)
    FreeGlobMem (TabPos);
  }

void fList::SetTabPos(int FAR *tabs,int AnzTabs)
  {
  TabPos = (int FAR *) GetGlobMem (sizeof(int) * AnzTabs);
  lmemcpy (TabPos,tabs,sizeof(int) * AnzTabs);
  }

