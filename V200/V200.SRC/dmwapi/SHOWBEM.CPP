////////////////////////////////////////////////////////////////
//  Anzeigen der Bemerkungen
///////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "docbem.hpp"
//#include "subclass.hpp"
#include "globmem.h"
#include "font.hpp"
#include "cfield.hpp"
#include "wordwin.hpp"
#define MODULENUM 48
#include "winass.hpp"

extern HINSTANCE hLibInst;

static BEMCALLBACK actcallback;
static GLOBALHANDLE hGBemSeg;
static WORD ActFallNummer;
static LPSTR ActprgName;
static WORD EditDone;
static BOOL doChange;
static LPBEMREC lastFound;
LPVOID CallBackMem;

static char EdString[512];

extern void ExtSetTwipsMap (HDC hDC,double scale,int xp,int yp);

typedef cField FAR *LPFIELD;
static char oTxt0[30];
static char oTxt1[30];
static char oTxt2[256];
struct bemListCallBack {
  WORD dsState;
  };

void WINAPI BemFldBackCmd (int Cmd,LPVOID Data,LPVOID PrivData)
  {
  if (Cmd == CALLBACKCMD_TRANSLATECLR) {
    WORD dsState = *(WORD FAR *) PrivData;
    if (dsState & ODS_SELECTED) {
      DWORD FAR *Color = (DWORD FAR *) Data;
      if (*Color == 0) *Color = RGB(0xFF,0xFF,0xFF);
      }
    }
  }

void GetFields (LPFIELD FAR *f0,LPFIELD FAR *f1,LPFIELD FAR *f2,LPSTR txt,int gWidth,WORD dsState,HWND hWnd)
  {
  // Zerlegen der Texte
  LPSTR x = oTxt0;
  int state = 0;
  for ( LPSTR h = txt ; ; ) {
    if (*h == '\t') {
      *x = '\0';
      state ++ ;
      switch (state) {
        case 1 :
          x = oTxt1;
          break;
        case 2 :
          x = oTxt2;
          break;
        }
      h++ ;
      }
    if (*h == '\0') {
      *x++ = *h++;
      break ;
      }
    else
      *x++ = *h++;
    }

  // Erzeugen der Felder
  bemListCallBack cb;
  cb.dsState = dsState;
  int space = gWidth / 40 ;
  if (f0 != NULL) {
    *f0 = new cField (TRANSPARENT,WWDEFFORMAT,space,0,gWidth / 5 - 2 * space,1,FALSE);
    (*f0)->InstallCallBack (BemFldBackCmd,&cb,sizeof(cb));
    (*f0)->SetWindow (hWnd);
    (*f0)->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    (*f0)->SetVOrg (0,0,0);
    **f0 = LPSTR (oTxt0);
    }
  if (f1 != NULL) {
    *f1 = new cField (TRANSPARENT,WWDEFFORMAT,space,0,gWidth / 5 - 2 * space,1,FALSE);
    (*f1)->InstallCallBack (BemFldBackCmd,&cb,sizeof(cb));
    (*f1)->SetWindow (hWnd);
    (*f1)->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
    (*f1)->SetVOrg (0,0,0);
    **f1 = LPSTR (oTxt1);
    }
  *f2 = new cField (TRANSPARENT,WWDEFFORMAT,space,0,gWidth * 3 / 5 - 2 * space,-1,FALSE);
  (*f2)->InstallCallBack (BemFldBackCmd,&cb,sizeof(cb));
  (*f2)->SetWindow (hWnd);
  (*f2)->SetScale (1.0,MAPTYPE_TYPOGRAPHIC);
  (*f2)->SetVOrg (0,0,0);
  **f2 = LPSTR (oTxt2);
  }

int GetLogWidth (HDC hDC,HWND hLWnd)
  {
  static int xLogRes;
  if (xLogRes > 0) return xLogRes;
  RECT r;
  GetClientRect (hLWnd,&r);
  DPtoLP (hDC,LPPOINT(&r),2);
  return xLogRes = r.right;
  }

void DrawItem (HWND hDlg,DRAWITEMSTRUCT FAR *ds)
  {
  if (ds->itemState & ODS_SELECTED)
    SelectObject (ds->hDC,GetStockObject (BLACK_BRUSH)),
    SelectObject (ds->hDC,GetStockObject (BLACK_PEN));
  else
    SelectObject (ds->hDC,GetStockObject (WHITE_BRUSH)),
    SelectObject (ds->hDC,GetStockObject (WHITE_PEN));

  // Loeschen des Hintergrundes
  Rectangle (ds->hDC,ds->rcItem.left,ds->rcItem.top,
                    ds->rcItem.right,ds->rcItem.bottom);

  SaveDC (ds->hDC);
  ExtSetTwipsMap (ds->hDC,1.0,ds->rcItem.left,ds->rcItem.top);
  cField FAR *f0,FAR *f1,FAR *f2;
  HWND hLWnd = GetDlgItem(hDlg,ds->CtlID);
  char outtxt[256];
  SendMessage (ds->hwndItem,LB_GETTEXT,ds->itemID,LONG(LPSTR(outtxt)));
  GetFields (&f0,&f1,&f2,outtxt,GetLogWidth(ds->hDC,hLWnd),ds->itemState,hLWnd);
  f0->Paint (ds->hDC,0,FALSE);
  SetViewportOrgEx (ds->hDC,ds->rcItem.left + 
              (ds->rcItem.right - ds->rcItem.left) / 5,ds->rcItem.top, NULL) ;
  f1->Paint (ds->hDC,0,FALSE);
  SetViewportOrgEx (ds->hDC,ds->rcItem.left + 
              (ds->rcItem.right - ds->rcItem.left) * 2 / 5,ds->rcItem.top, NULL) ;
  f2->Paint (ds->hDC,0,FALSE);
  delete f0 ;
  delete f1 ;
  delete f2 ;

  RestoreDC (ds->hDC,-1);
//  if ((ds->itemState & ODS_FOCUS) && 
//             (ds->itemAction & ODA_FOCUS)) {
//    DrawFocusRect (ds->hDC,&ds->rcItem);
//    }
  }

void MeasureItem (HWND hDlg,MEASUREITEMSTRUCT FAR *ms)
  {
  RECT r;
  HWND hLWnd = GetDlgItem(hDlg,ms->CtlID);
  GetClientRect (hLWnd,&r);
  ms->itemWidth = r.right;
  HDC htdc = GetDC (hLWnd);
  ExtSetTwipsMap (htdc,1.0,0,0);
  cField FAR *f;
  GetFields (NULL,NULL,&f,LPSTR(ms->itemData),GetLogWidth(htdc,hLWnd),0,hLWnd);
  f->GetFieldRect (&r,0);
  POINT pt[2];
  pt[0].x = pt[1].x = 0;
  pt[0].y = 0;
  pt[1].y = r.bottom;
  LPtoDP (htdc,pt,2);
  ms->itemHeight = pt[1].y - pt[0].y + 1;
  ReleaseDC (hLWnd,htdc);
  }

static GLOBALHANDLE PushBem ()
  {
  DWORD nsize = DWORD (lstrlen (EdString));

  LPBEMHEADER b;
  LPBEMREC r;
  DWORD actsize ;

  if (hGBemSeg) {
    b = LPBEMHEADER (GlobalLock (hGBemSeg));

    actsize = b->dwActSize;
    if (doChange) {
      if (EditDone) {
        // Austauschen des aktuellen Segmentes
        actsize = actsize + nsize - DWORD (lastFound->StrLen) ;
        }
      else {
        // Rausloeschen des aktuellen Segmentes
        actsize -= sizeof (BemRecord) + lastFound->StrLen ;
        }
      }
    else {
      actsize += sizeof (BemRecord) + nsize ;
      }

    if (actsize > b->dwActSize) {
      GlobalUnlock (hGBemSeg);
      hGBemSeg = GlobalReAlloc (hGBemSeg,actsize,GMEM_MOVEABLE);
      b = LPBEMHEADER (GlobalLock (hGBemSeg));
      }

    if (!doChange)
      b->AnzBem ++ ;
    else if (!EditDone) b->AnzBem -= 1;
    if (doChange) {
      r = lastFound ;
      int sizebeh = int (b->dwActSize - 
                          ((LPSTR) r + sizeof(BemRecord) + r->StrLen 
                           - LPSTR(b))
                        );
      lmemmove (LPSTR(r) + sizeof(BemRecord) + WORD(nsize),
                LPSTR(r) + sizeof(BemRecord) + r->StrLen,
                sizebeh
               );
      }
    else
      r = LPBEMREC (LPSTR (b) + b->dwActSize);

    if (actsize < b->dwActSize) {
      GlobalUnlock (hGBemSeg);
      hGBemSeg = GlobalReAlloc (hGBemSeg,actsize,GMEM_MOVEABLE);
      b = LPBEMHEADER (GlobalLock (hGBemSeg));
      }

    }
  else {
    hGBemSeg = GlobalAlloc (GHND,actsize = 
                sizeof(BemHeader) + sizeof(BemRecord) + nsize
                           );
    b = LPBEMHEADER (GlobalLock (hGBemSeg));
    b->AnzBem = 1;
    r = LPBEMREC (b + 1);
    }

  // Groesse richtig stellen
  b->dwActSize = actsize;

  // Und Struktur anfuellen
  if (EditDone) {
    lstrcpy (r->Txt,EdString);
    r->StrLen = int (nsize);
    r->FallNummer = ActFallNummer;
    lstrcpy (r->prgName,ActprgName);
    ( * actcallback) (PATBEM_FILLSTRUCT,r,NULL,0,CallBackMem);
    }

  GlobalUnlock (hGBemSeg);

  return hGBemSeg;
  }

DLLExport BOOL _export WINAPI CheckBemSeg (GLOBALHANDLE hGBemSeg,LPSTR prgName,WORD FallNummer)
  {
  BOOL res = FALSE ;
  if (hGBemSeg) {
    LPBEMHEADER b = LPBEMHEADER (GlobalLock (hGBemSeg));
    LPBEMREC r = LPBEMREC (b + 1);
    for (DWORD i = 0 ; ((i < b->AnzBem) && (!res)) ; i++) {
      if ((lstrcmp (r->prgName,prgName) == 0) && 
            (r->FallNummer == FallNummer)) res = TRUE ;
      r = LPBEMREC (LPSTR (r) + sizeof(*r) + r->StrLen);
      }
    GlobalUnlock (hGBemSeg);
    }
  return res;
  }

DLLExport BOOL _export WINAPI GetLastBemerkung (GLOBALHANDLE hGBemSeg,LPSTR prgName,WORD FallNummer,LPSTR rTxt,int rSize)
  {
  BOOL res = FALSE ;
  if (hGBemSeg) {
    LPBEMHEADER b = LPBEMHEADER (GlobalLock (hGBemSeg));
    LPBEMREC r = LPBEMREC (b + 1);
    lastFound = NULL;
    for (DWORD i = 0 ; i < b->AnzBem ; i++) {
      if ((lstrcmp(r->prgName,prgName) == 0) && 
            (r->FallNummer == FallNummer))
        lastFound = r;
      r = LPBEMREC (LPSTR (r) + sizeof(*r) + r->StrLen);
      }
    if (lastFound != NULL) {
      lstrncpy (rTxt,lastFound->Txt,rSize);
      res = TRUE ;
      }
    GlobalUnlock (hGBemSeg);
    }
  return res;
  }

static void FillListBox (HWND hDlg,WORD lid,WORD eid)
  {
  if (hGBemSeg) {
    LPBEMHEADER b = LPBEMHEADER (GlobalLock (hGBemSeg));
    LPBEMREC r = LPBEMREC (b + 1);
    lastFound = NULL;
    for (DWORD i = 0 ; i < b->AnzBem ; i++) {
      if ((lstrcmp(r->prgName,ActprgName) == 0) && 
            (r->FallNummer == ActFallNummer)) {
        (* actcallback) (PATBEM_GETTEXT,r,EdString,sizeof(EdString),CallBackMem);
        SendDlgItemMessage (hDlg,lid,LB_ADDSTRING,0,LONG(LPSTR(EdString)));
        lastFound = r;
        }
      r = LPBEMREC (LPSTR (r) + sizeof(*r) + r->StrLen);
      }
    SendDlgItemMessage (hDlg,lid,LB_SETCURSEL,0,0L);

    doChange = ((doChange) && (lastFound != NULL)) ;
    if (doChange) {
      // Setzen des Editfensters
      lstrcpy (EdString,lastFound->Txt);
      if (GetDlgItem (hDlg,eid))
        SetDlgItemText (hDlg,eid,lastFound->Txt);
      }
    GlobalUnlock (hGBemSeg);
    }
  }

#define ID_LBWND      100
#define ID_EDWND      101
DLLExport BOOL _export CALLBACK BemDlgFunc (HWND hDlg,UINT msg,WPARAM wP,LPARAM lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      {
      HWND hEdWnd = GetDlgItem (hDlg,ID_EDWND);
      RECT r;
      GetWindowRect (hEdWnd,&r);
      ScreenToClient (hDlg,LPPOINT(&r));
      ScreenToClient (hDlg,LPPOINT(&r.right));
      if (IsWindow (hEdWnd))
        MoveWindow (hEdWnd,r.left,r.top,r.right - r.left + 1,
                        WWGetYHeight(WWDEFFORMAT) + 2,FALSE);
      FillListBox (hDlg,ID_LBWND,ID_EDWND);
//      SubClassElements (hDlg,hLibInst);
      }
      return TRUE ;
      break ;
/*
    case WM_CTLCOLOR :
      {
      BOOL res;
      LONG lres = GetCtlColor (hDlg,wP,lP,res);
      if (res)
        return BOOL (lres);   // ??? !!!! ???
      }
      break ;
*/
    case WM_DRAWITEM :
      {
      DrawItem (hDlg,(DRAWITEMSTRUCT FAR *) lP);
      }
      break ;

    case WM_MEASUREITEM :
      {
      MeasureItem (hDlg,(MEASUREITEMSTRUCT FAR *) lP);
      }
      break ;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case ID_EDWND :
          GetDlgItemText (hDlg,CRACKER_wID,EdString,sizeof(EdString));
          EditDone = (lstrlen (EdString) > 0);
          return TRUE ;
          break ;
        case IDOK :
          EndDialog (hDlg,TRUE);
          return TRUE ;
          break ;
        case IDCANCEL :
          EndDialog (hDlg,FALSE);
          break ;
        }
      }
      break ;
    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI ShowBemerkungen (HWND hWndParent,
        GLOBALHANDLE FAR &hGtxt,BEMCALLBACK cfb,LPVOID cbm,BOOL doEdit,
        BOOL FAR &changeLast,LPSTR prgName,WORD FallNummer
                                        )
  {
  BOOL res = FALSE ;
  if (cfb != NULL) {
    actcallback = cfb;
    CallBackMem = cbm;
    hGBemSeg = hGtxt;
    ActprgName = prgName;
    ActFallNummer = FallNummer;
    doChange = changeLast;
    
    // Anzeigen der Dialogbox
    RegisterWordWin (hLibInst);
    res = DialogBox (hLibInst,
                  (doEdit) ? "BEMEDLIST" : "BEMLIST" ,
                  hWndParent,DLGPROC (BemDlgFunc));

    // fertig
    res = ((res) && (doEdit) && ((EditDone) || (doChange)));
    if (res)
      hGtxt = PushBem ();
    changeLast = changeLast || EditDone;
    }
  return res;
  }

