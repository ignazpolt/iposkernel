//
//  $Header:   P:/marille/clinicum/dmwapi/rev/multl.cpv   1.4   05 Oct 1998 11:12:02   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/multl.cpv  $
// 
//    Rev 1.4   05 Oct 1998 11:12:02   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   04 Apr 1997 15:19:52   Gerhold
// Berechnung SetDlgPos wurde auf Screen-Koordinaten umgestellt
// 
//    Rev 1.2   02 Feb 1996 10:46:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   25 Jul 1994 09:43:14   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:48:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.6   21 Apr 1994 18:10:10   HANNES
// 
//    Rev 1.5   21 Apr 1994 10:43:50   HANNES
// Rechstbuendig zum aufrufenden Fenster setzen
// 
//    Rev 1.4   29 Nov 1993 08:39:36   HANNES
// 
//    Rev 1.3   22 Sep 1993 10:18:04   HANNES
// Version nach St. Poelten
// 
//    Rev 1.2   18 Aug 1993 10:47:48   HANNES
// ??
// 
//    Rev 1.1   05 Jul 1993 14:59:24   HANNES
// Multiselektionslisten
// 
//    Rev 1.0   19 Jun 1993 19:35:34   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "multl.hpp"
#include "flist.hpp"

DLLExport _export MultiList::~MultiList ()
  { 
  if (restxt != NULL) FreeGlobMem (restxt);
  }

DLLExport _export MultiList::MultiList (LPMLI l,LPSTR txt)
  {
  List = l;
  if (txt != NULL) {
    restxt = LPSTR (GetGlobMem (lstrlen(txt) + 1)) ;
    lstrcpy (restxt,txt);
    }
  else
    restxt = LPSTR (GetGlobMem (1)) ;
  }

void MultiList::Fill (HWND hWnd)
  {
  for (LPMLI h = List ; h != NULL ; h = h->Next) {
    char ltxt[256];
    wsprintf (ltxt,"%c\t%s\t%s",h->sh,h->shtxt,h->ltxt);
    SendMessage (hWnd,LB_ADDSTRING,0,LONG(LPSTR(ltxt)));
    }
  }

static BOOL IsHexDigit (char h)
  {
  return (((h >= '0') && (h <= '9')) ||
          ((h >= 'A') && (h <= 'F')) ||
          ((h >= 'a') && (h <= 'f')));
  }

static int HexVal (char h)
  {
  int res = 0;
  if ((h >= '0') && (h <= '9'))       res = h - '0' ;
  else if ((h >= 'A') && (h <= 'F'))  res = h - 'A' + 10 ;
  else if ((h >= 'a') && (h <= 'f'))  res = h - 'a' + 10 ;
  return res;
  }

void MultiList::Select (HWND hWnd)
  {
  int i = 0 ;
  for (LPSTR h = restxt; *h ; ) {
    if ((*h++ == 'i') && (*h++ == ':')) {
      WORD x = 0 ;
      for ( ; IsHexDigit (*h) ; h ++) {
        x = x * 16 + HexVal (*h) ;
        }
      SendMessage (hWnd,LB_SETSEL,TRUE,MAKELONG(i = GetIndex(List,x),0));
      }
    }
  SendMessage (hWnd,LB_SETCURSEL,i,0L);
  }

void MultiList::GetRes (HWND hLWnd)
  {
  int count = int (SendMessage (hLWnd,LB_GETSELCOUNT,0,0L));
  if (restxt != NULL) FreeGlobMem (restxt);
  restxt = NULL ;
  if (count > 0) {
    int FAR *sels = (int FAR *) (GetGlobMem (sizeof(WORD) * count)) ;
    SendMessage (hLWnd,LB_GETSELITEMS,count,LONG(sels));
    int slen = 1;
    for (int i = 0 ; i < count ; i++) {
      char act[30];
      GetIndexText (List,sels[i],act);
      char acttxt[40];
      if (i > 0) wsprintf (acttxt,",%s",LPSTR (act));
      else       wsprintf (acttxt,"%s",LPSTR (act));
      slen += lstrlen (acttxt);
      LPSTR nw = LPSTR (GetGlobMem (slen));
      if (restxt != NULL) lstrcpy (nw,restxt);
      lstrcat (nw,acttxt);
      if (restxt != NULL) FreeGlobMem (restxt);
      restxt = nw ;
      }
    FreeGlobMem (sels);
    }
  else
    restxt = LPSTR (GetGlobMem (1));
  }

DLLExport BOOL _export MultiList::DelItem (WORD cPos)
  {
  WORD i = 0 ;
  WORD tbeg = 0xFFFF;
  WORD tend = 0xFFFF;
  WORD abeg;
  WORD aend = 0;
  BOOL SetTEnd = FALSE ;
  for (LPSTR h = restxt ; ; h++ , i++) {
    if ((*h == '\\') && (aend != 0xFFFF)) {
      abeg = i ;
      aend = 0xFFFF ;
      }
    if (cPos == i) {
      tbeg = abeg ;
      SetTEnd = TRUE ;
      }
    if ((*h == ',') || (*h == '\0')) {
      aend = (*h == ',') ? i+1 : i ;
      if (SetTEnd) {
        tend = aend;
        break ;
        }
      }
    if (*h == '\0') break ;
    }
  if (SetTEnd) {
    // Gefunden
    int olen = lstrlen (restxt) + 1;
    int nlen = olen - (tend - tbeg);
    LPSTR nw = LPSTR (GetGlobMem (nlen));
    for (i = 0 ; i < tbeg ; i++)
      nw[i] = restxt[i];
    for (i = tend ; i < WORD(olen) ; i++)
      nw[i + nlen - olen] = restxt[i] ;
    FreeGlobMem (restxt);
    restxt = nw;
    // Am Schluss darf kein Beistrich stehen
    int e = lstrlen (restxt);
    if ((e > 0) && (restxt[e-1] == ',')) restxt[e-1] = '\0' ;
    }
  return SetTEnd;
  }

BOOL MultiList::DelIndex(WORD Index)
  {
  LPSTR h = restxt;
  BOOL res = FALSE;
  for ( ; ((*h) && (!res)) ; ) {
    if (*h == '\\') {
      LPSTR start = h;
      h ++ ;
      if ((*h ++ == 'i') && (*h ++ == ':')) {
        WORD x = 0 ;
        for ( ; IsHexDigit(*h) ; h ++) {
          x = x * 16 + HexVal (*h) ;
          }
        res = (x == Index) ;
        h ++ ;                // h zeigt nun auf den naechsten Eintrag
        if (*h == ',') h++ ;  // Beistrich auch loeschen
        if (res) {
          // Raus damit (von Start bis h)
          int plen = start - restxt ;
          int elen = lstrlen (h) + 1;
          LPSTR nw = LPSTR (GetGlobMem(plen + elen));
          lmemcpy (nw,restxt,plen);
          lmemcpy (nw + plen,h,elen);
          FreeGlobMem (restxt);
          restxt = nw ;
          // Beistrich am Ende bitte auch noch raus
          int e = lstrlen (restxt);
          if ((e > 0) && (restxt[e-1] == ','))
            restxt[e-1] = '\0';
          }
        }
      }
    }
  return res;
  }

LPSTR MultiList::PushIndex (LPSTR txt,WORD Index)
  {
  char acttxt[20];
  if (txt != NULL)
    wsprintf (acttxt,",\\i:%X\\",Index);
  else
    wsprintf (acttxt,"\\i:%X\\",Index);
  int len = (txt != NULL) ? lstrlen (txt) + lstrlen(acttxt) + 1 :
                            lstrlen (acttxt) + 1;
  LPSTR nw = LPSTR (GetGlobMem (len));
  if (txt != NULL) {
    lstrcpy (nw,txt) ;
    FreeGlobMem (txt);
    }
  lstrcat (nw,acttxt);
  return nw ;
  }

WORD MultiList::SkipIndex (LPSTR FAR &h)
  {
  WORD res = 0 ;
  while ((*h) && (*h != '\\')) h ++ ;
  if ((*h++ == '\\') && (*h++ == 'i') && (*h++ == ':')) {
    for ( ; IsHexDigit (*h) ; h ++ ) {
      res = res * 16 + HexVal (*h) ;
      }
    h ++ ;
    }
  return res;
  }

BOOL MultiList::IsIndGreater (WORD ind1,WORD ind2)
  {
  for (LPMLI h = List ; h != NULL ; h = h->Next) {
    if (h->IntNum == ind1) return FALSE ;
    if (h->IntNum == ind2) return TRUE ;
    }
  return FALSE ;
  }

BOOL MultiList::AddIndex (WORD Index)
  {
  LPSTR nw = NULL ;
  int count = 0 ;
  BOOL done = FALSE ;

  for ( LPSTR h = restxt ; *h ; ) {
    WORD ActInd = SkipIndex (h);
    if ((IsIndGreater (ActInd,Index)) && (!done)) {
      done = TRUE ;
      nw = PushIndex (nw,Index);
      }
    nw = PushIndex (nw,ActInd);
    }
  if (!done)
    nw = PushIndex (nw,Index);

  FreeGlobMem (restxt);
  restxt = nw ;

  return TRUE ;
  }

DLLExport BOOL _export MultiList::AddItem (WORD wP)
  {
  WORD Index;
  BOOL res = CheckItem (List,wP,&Index);
  if (res) {
    // Es Handelt sich um einen Hotkey -> Neuaufbau des Ausgabetextes
    if (!DelIndex(Index)) {   
      // Nicht gefunden -> Reinstellen
      AddIndex (Index);
      }
    }
  return res;
  }

static MultiList FAR *ml;
void SetDlgPos (HWND hDlg,HWND ActDlgOwner,LPRECT fr,LPRECT cr)
  {
  RECT r;
  GetWindowRect (hDlg,&r);
  int width = r.right - r.left ;
  int height = r.bottom - r.top ;

  int sx = GetSystemMetrics (SM_CXSCREEN);
  int sy = GetSystemMetrics (SM_CYSCREEN);

  // Untersuchen, wo die Dialogbox Platz haben koennte
  POINT pt;
  /*----< vertikale Position >-----*/
  if (fr->bottom + height < sy)
    pt.y = fr->bottom + 1;
  else
    pt.y = fr->top - height - 1;


// Nach einer Testphase loeschen (V166, 04.04.97)
/***************************************************
  if (fr->bottom + height < cr->bottom) {
    // Auf jeden Fall Unten
    pt.y = fr->bottom + 1;
    }
  else {
    int dyu = fr->bottom + height - cr->bottom ;
    int dyo = fr->top - height - cr->top;
    if (dyu > dyo) {
      // Doch unten
      pt.y = fr->bottom + 1;
      }
    else {
      // Oben
      pt.y = fr->top - height - 1;
      }
    }
***********************************************/

  /*----< horizontale Position >-----*/
  if (fr->left + width < sx)
    pt.x = fr->left;
  else
    pt.x = fr->right - width - 1;


// Nach einer Testphase loeschen (V166, 04.04.97)
/**************************************************
  if (fr->left + width < cr->right)
    // Auf jeden Fall linksbuendig mit dem Feld
    pt.x = fr->left;
  else {
    if ((cr->right - width - 1) > cr->left) {
      // Rectsbuendig mit dem Fenster
      pt.x = cr->right - width - 1;
      }
    else {
      pt.x = cr->left ;
      }
    }
***********************************************/

  // Achtung: Koordinaten sind Klientkoordinaten des Dialog - Vaterfensters
//  ClientToScreen (ActDlgOwner,&pt);

  // Und noch die Verschiebung
  MoveWindow (hDlg,pt.x,pt.y,width,height,FALSE);
  }

static HWND ActDlgOwner;
void MultiList::SetPos(HWND hDlg)
  {
  SetDlgPos (hDlg,ActDlgOwner,fr,cr);
  }

#define ID_LIST   100
fList FAR *MultiListDrw;
extern void setFieldButtonUp ();
DLLExport BOOL _export CALLBACK MultiListDlg (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP)
  {
  BOOL res = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      ml->SetPos (hDlg);
      ml->Fill (GetDlgItem (hDlg,ID_LIST));
      ml->Select (GetDlgItem (hDlg,ID_LIST));
      SetFocus (GetDlgItem (hDlg,ID_LIST));
      break ;
    case WM_MEASUREITEM :
      res = MultiListDrw->Measure (hDlg,(MEASUREITEMSTRUCT FAR *) lP);
      break ;
    case WM_DRAWITEM :
      res = MultiListDrw->Draw ((DRAWITEMSTRUCT FAR *) lP);
      break ;
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          ml->GetRes (GetDlgItem (hDlg,ID_LIST));
          setFieldButtonUp ();
          EndDialog (hDlg,FALSE);
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
#define MULTLISTDRW_FORMAT 2
DLLExport BOOL _export MultiList::WorkOn (HWND hWnd,LPRECT fieldRect,LPRECT ClientRect)
  {
  ml = this ;
  fr = fieldRect;
  cr = ClientRect;
  MultiListDrw = new fList(ID_LIST,MULTLISTDRW_FORMAT,NULL,SEARCHMODE_SORTED);
  BOOL res = DialogBox (hLibInst,"MLISTDLG",ActDlgOwner = hWnd,DLGPROC(MultiListDlg));
  delete MultiListDrw;
  return res;
  }

DLLExport BOOL _export AddItem (LPMLI FAR *Root,WORD IntNum,LPSTR sh,LPSTR shtxt,LPSTR ltxt)
  {
  LPMLI res = LPMLI (GetGlobMem (sizeof(*res)));
  res->Next = NULL;
  res->IntNum = IntNum;

#ifdef WIN32
  res->sh = WORD(DWORD(CharUpper(sh)));
#else
  res->sh = WORD(DWORD(AnsiUpper(LPSTR (MAKELP(0,*sh)))));
#endif

  res->shtxt = LPSTR (GetGlobMem (lstrlen(shtxt)+1));
  lstrcpy (res->shtxt,shtxt);
  res->ltxt = LPSTR (GetGlobMem (lstrlen(ltxt)+1));
  lstrcpy (res->ltxt,ltxt);

  if (*Root == NULL)
    *Root = res;
  else {
    for (LPMLI h = *Root ; ; h = h->Next) {
      if (h->Next == NULL) {
        h->Next = res ;
        break ;
        }
      }
    }
  return TRUE ;
  }

DLLExport BOOL _export DelItem (LPMLI FAR *Root,WORD IntNum)
  {
  LPMLI prev = NULL ;
  for ( LPMLI h = *Root ; h != NULL ; ) {
    if (h->IntNum == IntNum) {
      if (prev != NULL) prev->Next = h->Next ;
      else              *Root = h->Next ;
      FreeGlobMem (h->ltxt);
      FreeGlobMem (h->shtxt);
      FreeGlobMem (h);
      break ;
      }
    prev = h ;
    h = h->Next ;
    }
  return TRUE ;
  }

BOOL CheckItem (LPMLI List,WORD wP,WORD FAR *Index)
  {
  BOOL res = FALSE ;
  for ( ; List != NULL ; List = List->Next) {

#ifdef WIN32
    if (List->sh == WORD(DWORD(CharUpper(LPSTR(wP))))) {
#else
    if (List->sh == WORD(DWORD(AnsiUpper(LPSTR (MAKELP(0,wP)))))) {
#endif

      *Index = List->IntNum;
      res = TRUE ;
      break ;
      }
    }
  return res;
  }

DLLExport LPSTR _export GetWordText (LPMLI Root,WORD IntNum)
  {
  for ( ; Root != NULL ; Root = Root->Next) {
    if (Root->IntNum == IntNum)
      return Root->shtxt ;
    }
  return NULL ;
  }

void GetIndexText (LPMLI Root,int Index,LPSTR res)
  {
  for (int i = 0 ; i < Index ; i++ , Root = Root->Next) ;
  wsprintf (res,"\\i:%X\\",Root->IntNum);
  }

DLLExport int _export GetIndex (LPMLI Root,WORD IntNum)
  {
  for ( int i = 0 ; Root != NULL ; Root = Root->Next , i++) {
    if (Root->IntNum == IntNum)
      break;
    }
  return i ;
  }


