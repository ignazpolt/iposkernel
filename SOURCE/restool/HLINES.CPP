///////////////////////////////////////////////////////////////////
//  Implementierung der Hilfslinien
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/hlines.cpv   1.8   05 Oct 1998 11:27:04   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/hlines.cpv  $
// 
//    Rev 1.8   05 Oct 1998 11:27:04   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   05 Nov 1997 09:07:30   Gerhold
// 32 Bit
// 
//    Rev 1.6   28 Aug 1997 15:50:44   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.5   02 Feb 1996 10:50:28   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   27 Aug 1995 13:00:30   HANNES
// 
//    Rev 1.3   23 Aug 1995 11:05:06   GERHOLD
// 
//    Rev 1.2   02 Jan 1995 09:30:26   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.1   17 Oct 1994 14:54:40   HANNES
// Tracing eingebaut
// 
//    Rev 1.0   12 Jul 1994 14:42:58   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "wonscrip.hpp"
#define MODULENUM 117
#include "winass.hpp"

//#include "subclass.hpp"

#define JUST_EM
#include "dds.hpp"

#include "font.hpp"
#include "cfield.hpp"
#define NODLL
#include "toolbar.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "hlines.hpp"
#include "template.hpp"

WORD hLineType;
BOOL InHLineEdit;
static int lvold;
#define HLINECOLOR  (RGB(0xFF,0,0))
#define HXLINECOLOR ((~HLINECOLOR) & 0x00FFFFFF)
extern void toLog (LPPOINT pt);
extern void toDev (LPPOINT pt);
extern HWND hFrmWnd;
extern HWND OutWnd;
extern HINSTANCE MyInstance;
inline HWND LineWnd()
  {
  return (hFrmWnd) ? hFrmWnd : OutWnd ;
  }
inline BOOL ForForm ()
  {
  return (hFrmWnd != 0);
  }
LPHILFSLINIE hLines;
void toHLog (LPPOINT pt)
  {
  if (ForForm ()) {
    toLog (pt);
    }
  else {
    double baseunit;
    GetBaseUnit (&baseunit);
    pt->x = int (double (pt->x) / baseunit) ;
    pt->y = int (double (pt->y) / baseunit) ;
    }
  }
void toHDev (LPPOINT pt)
  {
  if (ForForm ()) {
    toDev (pt);
    }
  else {
    double baseunit;
    GetBaseUnit (&baseunit);
    pt->x = int (double (pt->x) * baseunit) ;
    pt->y = int (double (pt->y) * baseunit) ;
    }
  }
int GetHLKoord (int Type,int val)
  {
  POINT pt;
  int FAR *res;
  switch (Type) {
    case HLINE_VERT :
      pt.x = val ;
      pt.y = 0 ;
      res = (int FAR *)&pt.x ;
      break ;
    case HLINE_HORZ :
      pt.x = 0 ;
      pt.y = val ;
      res = (int FAR *)&pt.y ;
      break ;
    }
  toHLog (&pt);
  return *res;
  }
int GetHDKoord (int Type,int val)
  {
  POINT pt;
  int FAR *res;
  switch (Type) {
    case HLINE_VERT :
      pt.x = val ;
      pt.y = 0 ;
      res = (LPINT)&pt.x ;
      break ;
    case HLINE_HORZ :
      pt.x = 0 ;
      pt.y = val ;
      res = (LPINT)&pt.y ;
      break ;
    }
  toHDev (&pt);
  return *res;
  }
void PaintHLine (PaintContext *pc,int type,int lval)
  {
  RECT r;
  GetClientRect (LineWnd(),&r);
  lval = GetHDKoord (type,lval);
  switch (type) {
    case HLINE_VERT :
      MoveToEx (pc->hDC,lval,0, NULL);
      LineTo (pc->hDC,lval,r.bottom);
      break ;
    case HLINE_HORZ :
      MoveToEx (pc->hDC,0,lval, NULL);
      LineTo (pc->hDC,r.right,lval);
      break ;
    }
  }
void SelRect (HDC hDC,int x,int y)
  {
  Rectangle (hDC,x-2,y-2,x+2,y+2);
  }
void PaintHSelLine (PaintContext *pc,int type,int lval)
  {
  RECT r;
  GetClientRect (LineWnd(),&r);
  lval = GetHDKoord (type,lval);
  int l,i;
  switch (type) {
    case HLINE_VERT :
      l = (r.bottom - 4) / 4 ;
      for (i = 0 ; i < 5 ; i++)
        SelRect (pc->hDC,lval,2 + i * l);
      break ;
    case HLINE_HORZ :
      l = (r.bottom - 4) / 4 ;
      for (i = 0 ; i < 5 ; i++)
        SelRect (pc->hDC,2 + i * l,lval);
      break ;
    }
  }
#define NOOLDVAL  -32767
void MoveHLine (int x,int y)
  {
  RECT r;
  GetClientRect (LineWnd(),&r);
  BOOL doIt = FALSE ;
  int lvnew ;
  switch (hLineType) {
    case HLINE_VERT :
      doIt = ((x >= 0) && (x < r.right));
      lvnew = x ;
      break ;
    case HLINE_HORZ :
      doIt = ((y >= 0) && (y < r.bottom));
      lvnew = y ;
      break ;
    }
  if ((doIt) || (lvold >= 0)) {
    lvnew = GetHLKoord (hLineType,lvnew);
    if (lvnew != lvold) {
      PaintContext pc(LineWnd(),0xFFFF,0xFFFF,DO_WORK);
      pc.Attrib (PENDATA(HXLINECOLOR));
      SetROP2 (pc.hDC,R2_XORPEN);
      if (lvold >= 0)
        PaintHLine (&pc,hLineType,lvold);
      if (doIt) {
        PaintHLine (&pc,hLineType,lvnew);
        lvold = lvnew ;
        }
      else
        lvold = NOOLDVAL;
      }
    }
  else
    lvold = NOOLDVAL;
  }
void InsertHLine (int x,int y)
  {
  BOOL doIt ;
  int lvnew ;
  RECT r;
  GetClientRect (LineWnd(),&r);
  switch (hLineType) {
    case HLINE_VERT :
      doIt = ((x >= 0) && (x < r.right));
      lvnew = x ;
      break ;
    case HLINE_HORZ :
      doIt = ((y >= 0) && (y < r.bottom));
      lvnew = y ;
      break ;
    }
  if (doIt) {
    LPHILFSLINIE n = LPHILFSLINIE (GetGlobMem (sizeof(*n)));
    lvnew = GetHLKoord (hLineType,lvnew);
    n->Type = hLineType;
    n->lval = lvnew ;
    n->Next = hLines;
    hLines = n;
    }
  else 
    MessageBeep (0);
  }
void InitializeHMove ()
  {
  lvold = NOOLDVAL;
  LONG l = GetMessagePos ();
  POINT pt;
  pt.x = LOWORD(l);
  pt.y = HIWORD(l);
  ScreenToClient (LineWnd(),&pt);
  MoveHLine (pt.x,pt.y);
  }
static LPHILFSLINIE SelectedLine ;
static int HModifyState;
#define HMDS_NONE       0
#define HMDS_CURSOR     1
#define HMDS_SELECTED   2
#define HMDS_WAITING    3
#define HMDS_MOVING     4
void PaintHLines (HDC hDC)
  {
  PaintContext pc;
  pc.SetDC (hDC);
  if (hLines != NULL) 
    pc.Attrib (PENDATA(HLINECOLOR));
  for (LPHILFSLINIE x = hLines ; x != NULL ; x = x->Next) {
    PaintHLine (&pc,x->Type,x->lval);
    if ((x == SelectedLine) && (HModifyState == HMDS_SELECTED)) {
      HBRUSH hOldBrush = (HBRUSH)SelectObject (pc.hDC,CreateSolidBrush (HLINECOLOR));
      PaintHSelLine (&pc,x->Type,x->lval);
      DeleteObject (SelectObject (pc.hDC,hOldBrush));
      pc.Attrib (PENDATA(HLINECOLOR));
      }
    }
  }
void DestroyHLines ()
  {
  for ( ; hLines != NULL ; ) {
    LPHILFSLINIE n = hLines->Next;
    FreeGlobMem (hLines) ;
    hLines = n;
    }
  }
inline int diff (int x1,int x0)
  {
  int d = x1 - x0 ;
  return (d < 0) ? -d : d ;
  }

// Abstaende zur Hilfslinie bei denen es "Ernst" wird.
#define MAXDIFF_FORM      200
#define MAXDIFF_DIALOG    7
inline int MaxDiff()
  {
  return (ForForm ()) ? MAXDIFF_FORM : MAXDIFF_DIALOG ;
  }

//---------------------------------------------------------------------------
// Prueft ob sich das Objekt in der Naehe einer Hilfslinie befindet
//---------------------------------------------------------------------------
BOOL HilfsLinie::Snap (LPPOINT pt,LPPOINT ptsnap,int xoffs,int yoffs)
  {
  switch (Type) {
    case HLINE_VERT :
      if (diff (pt->x + xoffs,lval) < MaxDiff()) {
        if (ptsnap != NULL) ptsnap->x = lval - xoffs ;
        return TRUE ;
        }
      break ;
    case HLINE_HORZ :
      if (diff (pt->y + yoffs,lval) < MaxDiff()) {
        if (ptsnap != NULL) ptsnap->y = lval - yoffs ;
        return TRUE ;
        }
      break ;
    }
  return FALSE ;
  }
int HilfsLinie::Abst (LPPOINT pt,LPPOINT ptsnap)
  {
  int d ;
  switch (Type) {
    case HLINE_VERT :
      d = pt->x - ptsnap->x ; 
      break ;
    case HLINE_HORZ :
      d = pt->y - ptsnap->y ; 
      break ;
    }
  if (d < 0) d = -d ;
  return d ;
  }
BOOL HilfsLinie::IsBetterVLine (LPPOINT pt,LPPOINT ptsnap,int FAR *dh,int FAR *dv)
  {
  int d;
  switch (Type) {
    case HLINE_VERT :
      d = Abst (pt,ptsnap);
      if (d < *dv) {
        *dv = d ;
        return TRUE ;
        }
      break ;
    case HLINE_HORZ :
      break ;
    }
  return FALSE ;
  }
BOOL HilfsLinie::IsBetterHLine (LPPOINT pt,LPPOINT ptsnap,int FAR *dh,int FAR *dv)
  {
  int d;
  switch (Type) {
    case HLINE_VERT :
      break ;
    case HLINE_HORZ :
      d = Abst (pt,ptsnap);
      if (d < *dh) {
        *dh = d ;
        return TRUE ;
        }
      break ;
    }
  return FALSE ;
  }
void HilfsLinie::SetMoveCursor ()
  {
  switch (Type) {
    case HLINE_VERT :
      SetCursor (LoadCursor (NULL,IDC_SIZEWE));
      if (HModifyState == HMDS_NONE) HModifyState = HMDS_CURSOR;
      break ;
    case HLINE_HORZ :
      SetCursor (LoadCursor (NULL,IDC_SIZENS));
      if (HModifyState == HMDS_NONE) HModifyState = HMDS_CURSOR;
      break ;
    }
  }
LPHILFSLINIE BestLine (LPPOINT pt)
  {
  int hAbst = 32767,vAbst = 32767 ;
  POINT ptsnap;
  BOOL xDone = FALSE,yDone = FALSE;
  LPHILFSLINIE hBest = NULL,vBest = NULL;
  for (LPHILFSLINIE h = hLines ; h != NULL ; h = h->Next) {
    if (h->Snap (pt,&ptsnap,0,0)) {
      if (h->IsBetterHLine (pt,&ptsnap,&hAbst,&vAbst))
        hBest = h;
      if (h->IsBetterVLine (pt,&ptsnap,&hAbst,&vAbst))
        vBest = h;
      }
    }
  if (hAbst < vAbst) return hBest ;
  else               return vBest ;
  }
BOOL CheckCursorForHLines (int x,int y)
  {
  POINT pt;
  pt.x = x ; pt.y = y ;
  toHLog (&pt);
  if ((GetAsyncKeyState (VK_LBUTTON) < 0) && (SelectedLine != NULL)) {
    // Die Auswahl muss in diesem Fall schon passiert sein
    if ((HModifyState != HMDS_SELECTED) && (HModifyState != HMDS_NONE)) {
      SelectedLine->SetMoveCursor ();
      return TRUE ;
      }
    else
      return FALSE ;
    }
  // Bei einer Selektion
  if (HModifyState != HMDS_SELECTED) {
    LPHILFSLINIE h = BestLine (&pt);
    if (h != NULL) {
      h->SetMoveCursor ();
      SelectedLine = h;
      return TRUE ;
      }
    }
  if (HModifyState == HMDS_CURSOR) HModifyState = HMDS_NONE;
  return FALSE ;
  }
BOOL IsHLineMoveing()
  {
  return ((SelectedLine != NULL) && 
          (HModifyState != HMDS_NONE) &&
          (HModifyState != HMDS_CURSOR));
  }
void ResetHLineCursor ()
  {
  HModifyState = HMDS_NONE;
  SelectedLine = NULL ;
  }
int xhold,yhold;
#define WAITTIME  300
void HLine_Timer ()
  {
  // Der ist immer noch drunten, probieren wir mal verschieben
  KillTimer (LineWnd(),HLINETIMER);
  HModifyState = HMDS_MOVING;
  }
BOOL HLine_OnLButtonDown (int x,int y)
  {
  if (HModifyState == HMDS_SELECTED) {
    // Selektierte Zeile wieder ausschalten
    HModifyState = HMDS_NONE ;
    InvalidateRect (LineWnd(),NULL,TRUE);
    }
  if (HModifyState == HMDS_CURSOR) {
    // In den Wartezustand uebergehen
    HModifyState = HMDS_WAITING;
    SetTimer (LineWnd(),HLINETIMER,WAITTIME,NULL);
    SetCapture (LineWnd());
    xhold = x ; yhold = y ;
    return TRUE ;
    }
  else
    return FALSE ;
  }
void ModifySelected (int x,int y)
  {
  RECT r;
  GetClientRect (LineWnd(),&r);
  x = min(r.right,max(0,x));
  y = min(r.bottom,max(0,y));
  switch (SelectedLine->Type) {
    case HLINE_VERT :
      SelectedLine->lval = GetHLKoord (SelectedLine->Type,x);
      break ;
    case HLINE_HORZ :
      SelectedLine->lval = GetHLKoord (SelectedLine->Type,y);
      break ;
    }
  }
BOOL HLine_OnLButtonUp (int x,int y)
  {
  if (HModifyState == HMDS_WAITING) {
    // Er will wohl gern selektieren
    HModifyState = HMDS_SELECTED;
    InvalidateRect (LineWnd(),NULL,TRUE);
    ReleaseCapture ();
    KillTimer (LineWnd(),HLINETIMER);
    return TRUE ;
    }
  else if (HModifyState == HMDS_MOVING) {
    // Fertig verschoben
    HModifyState = HMDS_NONE;
    ModifySelected (x,y);
    InvalidateRect (LineWnd(),NULL,TRUE);
    ReleaseCapture ();
    return TRUE ;
    }
  else
    return FALSE ;
  }
BOOL HLine_OnMouseMove (int x,int y)
  {
  if (HModifyState == HMDS_MOVING) {
    PaintContext pc (LineWnd(),0xFFFF,0xFFFF,DO_WORK);
    pc.Attrib (PENDATA(HXLINECOLOR));
    SetROP2 (pc.hDC,R2_XORPEN);
    PaintHLine (&pc,SelectedLine->Type,SelectedLine->lval);
    ModifySelected (x,y);
    PaintHLine (&pc,SelectedLine->Type,SelectedLine->lval);
    return TRUE ;
    }
  else
    return FALSE ;
  }
void DeleteHLine ()
  {
  if (HModifyState == HMDS_SELECTED) {
    LPHILFSLINIE prev = NULL ;
    for (LPHILFSLINIE x = hLines ; x != NULL ; x = x->Next) {
      if (x == SelectedLine) {
        if (prev != NULL) prev->Next = x->Next;
        else              hLines     = x->Next;
        FreeGlobMem (x);
        SelectedLine = NULL ;
        HModifyState = HMDS_NONE;
        InvalidateRect (LineWnd(),NULL,TRUE);
        return ;
        }
      prev = x;
      }
    }
  else 
    MessageBeep (0);
  HModifyState = HMDS_NONE;
  }
DLLExport BOOL FAR PASCAL _export WHLine (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  BOOL done;
  int res ;
  switch (msg) {
    case WM_INITDIALOG :
      SetDlgItemInt (hDlg,ID_HLINEPOS,SelectedLine->lval,TRUE);
//      SubClassElements (hDlg,MyInstance);
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
          res = GetDlgItemInt (hDlg,ID_HLINEPOS,&done,TRUE);
          if (done) {
            SelectedLine->lval = res ;
            InvalidateRect (LineWnd(),NULL,TRUE);
            }
          else 
            MessageBeep (0);
          EndDialog (hDlg,TRUE);
          break ;
        }
      break ;
    }
  return RetVal;
  }
void WorkOnHLine ()
  {
  if (HModifyState == HMDS_SELECTED) {
    DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(WHLine),MyInstance));
    DialogBox (MyInstance,"WONHLINE",LineWnd(),dlgProc);
    FreeProcInstance (dlgProc);
    }
  else
    MessageBeep (0);
  }
void InsertMultiLines (int Anz,int Abst)
  {
  for (int i = 0 ; i < Anz ; i++) {
    LPHILFSLINIE n = LPHILFSLINIE (GetGlobMem (sizeof(*n)));
    n->Next = hLines ;
    n->Type = SelectedLine->Type;
    n->lval = SelectedLine->lval + (i + 1) * Abst ;
    hLines = n ;
    }
  }
DLLExport BOOL FAR PASCAL _export MHLine (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  BOOL done1,done2;
  int Anz,Abst;
  switch (msg) {
    case WM_INITDIALOG :
//      SubClassElements (hDlg,MyInstance);
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
          Anz  = GetDlgItemInt (hDlg,ID_ANZLINES,&done1,TRUE);
          Abst = GetDlgItemInt (hDlg,ID_ABSTHLINE,&done2,TRUE);
          if ((done1) && (done2)) {
            InsertMultiLines (Anz,Abst);
            HModifyState = HMDS_NONE;
            InvalidateRect (LineWnd(),NULL,TRUE);
            EndDialog (hDlg,TRUE);
            }
          else
            MessageBeep (0);
          break ;
        case IDCANCEL :
          EndDialog (hDlg,FALSE);
          break ;
        }
      break ;
    }
  return RetVal;
  }
void SetMultiHLine ()
  {
  if (HModifyState == HMDS_SELECTED) {
    DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(MHLine),MyInstance));
    BOOL res = DialogBox (MyInstance,"MULTIHLINE",LineWnd(),dlgProc);
    FreeProcInstance (dlgProc);
    }
  }
#define AS_INIT     0
#define AS_COMMENT  1
#define AS_KWFOUND  2
#define AS_TYPFOUND 3
#define AS_INDIGIT  4
#define AS_END      5
static char HLineText[] = "Hilfslinien:";
static char VKeyWord[] = "V!";
static char HKeyWord[] = "H!";
struct HDefLine {
  HDefLine FAR *Next;
  LPLINE l;
  };
typedef HDefLine FAR *LPDEFLINE;
LPDEFLINE DefLines;
void MarkAsDefLine (LPLINE l)
  {
  LPDEFLINE n = LPDEFLINE (GetGlobMem (sizeof(*n)));
  n->Next = DefLines ;
  n->l = l;
  DefLines = n;
  }
BOOL AnalyseForHLine (LPLINE l)
  {
  int state = AS_INIT ;
  int ActType,ActPos;
  for ( LPSTR h = l->Text ; *h ; ) {
    switch (state) {
      case AS_INIT     :
        if (*h == '$') state = AS_COMMENT ;
        h++ ;
        break ;
      case AS_COMMENT  :
        if (mystrcmp (h,HLineText)) {
          h += lstrlen(HLineText);
          state = AS_KWFOUND ;
          }
        else
          h ++ ;
        break ;
      case AS_KWFOUND  :
        if (mystrcmp (h,VKeyWord)) {
          h += lstrlen(VKeyWord);
          ActType = HLINE_VERT ;
          state = AS_TYPFOUND ;
          }
        else if (mystrcmp (h,HKeyWord)) {
          h += lstrlen(HKeyWord);
          ActType = HLINE_HORZ ;
          state = AS_TYPFOUND ;
          }
        else if (*h == ';') {
          state = AS_END ;
          h ++ ;
          }
        else
          h ++ ;
        break ;
      case AS_TYPFOUND :
        if ((*h >= '0') && (*h <= '9')) {
          state = AS_INDIGIT ;
          ActPos = 0;
          }
        else
          h ++ ;
        break ;
      case AS_INDIGIT  :
        if ((*h >= '0') && (*h <= '9')) {
          ActPos = ActPos * 10 + *h - '0' ;
          h ++ ;
          }
        else {
          LPHILFSLINIE n = LPHILFSLINIE (GetGlobMem (sizeof(*n)));
          n->Next = hLines ;
          hLines = n ;
          n->Type = ActType ;
          n->lval = ActPos ;
          state = AS_KWFOUND ;
          }
        break ;
      case AS_END      :
        h ++ ;
        break ;
      }
    }
  if (state == AS_END) {
    MarkAsDefLine (l);
    return TRUE ;
    }
  else
    return FALSE ;
  }
BOOL IsHLine (LPLINE l)
  {
  LPDEFLINE prev = NULL ;
  for ( LPDEFLINE x = DefLines ; x != NULL ; ) {
    if (x->l == l) {
      if (prev != NULL) prev->Next = x->Next ;
      else              DefLines   = x->Next ;
      FreeGlobMem (x) ;
      return TRUE ;
      }
    prev = x ;
    x = x->Next ;
    }
  return FALSE ;
  }
void DelDefLines ()
  {
  for ( ; DefLines != NULL ; ) {
    LPDEFLINE x = DefLines->Next ; 
    FreeGlobMem (DefLines);
    DefLines = x ;
    }
  }
LPLINE GetHDefLine ()
  {
  if (hLines != NULL) {
    LPLINE res = LPLINE (GetGlobMem (sizeof(*res)));
    res->Text = LPSTR(GetGlobMem (1));
    res->AddText ("  $ ");
    res->AddText (HLineText);
    for ( LPHILFSLINIE h = hLines ; h != NULL ; h = h->Next) {
      if (h->Type == HLINE_VERT) res->AddText(VKeyWord);
      else                       res->AddText(HKeyWord);
      char nm[20];
      wsprintf (nm,"%d",h->lval);
      res->AddText(nm);
      if (h->Next == NULL) res->AddText(";");
      else                 res->AddText(",");
      }
    return res ;
    }
  else
    return NULL ;
  }

LONG CheckHLineMSG (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done)
  {
  *done = FALSE ;
  LONG RetVal = 0L;
  switch (msg) {
    case WM_LBUTTONUP:
      if (InHLineEdit) {
        InsertHLine (LOWORD(lP),HIWORD(lP));
        ReleaseCapture ();
        InHLineEdit = FALSE ;
        InvalidateRect (hWnd,NULL,TRUE);
        *done = TRUE ;
        }
      else
        *done = HLine_OnLButtonUp (LOWORD(lP),HIWORD(lP));
      break ;
    case WM_LBUTTONDOWN :
      if (InHLineEdit) *done = TRUE ;
      else             *done = HLine_OnLButtonDown (LOWORD(lP),HIWORD(lP));
      break ;
    case WM_MOUSEMOVE:
      if (InHLineEdit) {
        MoveHLine (LOWORD(lP),HIWORD(lP));
        *done = TRUE ;
        }
      else *done = HLine_OnMouseMove (LOWORD(lP),HIWORD(lP));
      break ;
    case WM_TIMER :
      if (wP == HLINETIMER) {
        HLine_Timer ();
        *done = TRUE ;
        }
      break ;
    case WM_SETCURSOR :
      if (InHLineEdit) 
        *done = TRUE ;
      break ;
    }
  return RetVal ;
  }

BOOL HLineAllowed ()
  {
  return (LineWnd() != 0);
  }

HWND GetHLineWnd()
  {
  return LineWnd();
  }

void ClearHLines ()
  {
  DestroyHLines ();
  DelDefLines ();
  }

extern WORD FrmType;
extern WORD ActType;
BOOL TryToSnap (int FAR *xn,int FAR *yn,int XOffs,int YOffs)
  {
  int hAbst = 32767,vAbst = 32767 ;
  POINT pt,ptsnap;
  pt.x = *xn ; pt.y = *yn ;
  int rx,ry;
  BOOL xDone = FALSE,yDone = FALSE;
  if ((ActType == EDTYPE_FORM) && (FrmType != FORMTYPE_FORM))
    pt.x /= 4 , pt.y /= 4 ;
  for (LPHILFSLINIE h = hLines ; h != NULL ; h = h->Next) {
    if (h->Snap (&pt,&ptsnap,XOffs,YOffs)) {
      if (h->IsBetterHLine (&pt,&ptsnap,&hAbst,&vAbst))
        ry = ptsnap.y , yDone = TRUE ;
      if (h->IsBetterVLine (&pt,&ptsnap,&hAbst,&vAbst))
        rx = ptsnap.x , xDone = TRUE ;
      }
    }
  if ((ActType == EDTYPE_FORM) && (FrmType != FORMTYPE_FORM))
    rx *= 4 , ry *= 4 ;
  if (xDone) *xn = rx ;
  if (yDone) *yn = ry ;
  return xDone || yDone ;
  }


