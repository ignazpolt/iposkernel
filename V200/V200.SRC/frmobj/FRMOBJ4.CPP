////////////////////////////////////////////////////////////////////
// Implementierung der Eingabeobjekte (Punkt / Kontureingabe)
////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/frmobj4.cpv   1.22   05 Oct 1998 11:21:46   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/frmobj4.cpv  $
// 
//    Rev 1.22   05 Oct 1998 11:21:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.21   16 Feb 1998 14:15:32   Gerhold
// VC++5.x ... explicit ist jetzt ein Schluesselwort
// 
//    Rev 1.20   19 Oct 1997 13:51:50   Martin
// OnIndChange defensiver
// 
//    Rev 1.19   09 Oct 1997 17:27:50   Martin
// Eingabeobjekte entsprechend der uFrmShowObjects sortieren
// 
//    Rev 1.18   27 Sep 1997 21:41:00   Martin
// Digitizer-Musterbild 32 Bit faehig gemacht
// 
//    Rev 1.17   10 Sep 1997 17:46:40   Hannes
// Prototypenaenderung
// 
//    Rev 1.16   18 Aug 1997 18:05:20   Martin
// VTO Formular-faehig
// 
//    Rev 1.15   09 Apr 1997 17:43:38   Martin
// ->x -> .x, ->y -> .y
// 
//    Rev 1.14   09 Apr 1997 17:40:04   Martin
// PostMove 32 bit faehig gemacht
// 
//    Rev 1.13   14 Oct 1996 15:29:58   MARTIN
// Sound: erste funktionierende Version
// 
//    Rev 1.12   28 Jun 1996 15:54:12   MARTIN
// auch hier auf neue ResDB umstellen
// 
//    Rev 1.11   10 Jun 1996 10:12:24   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.10   24 Mar 1996 12:11:50   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.9   02 Feb 1996 10:49:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   24 Aug 1995 00:15:12   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.7   10 Aug 1995 09:20:14   HANNES
// OnLButtonDown nur wenn kein Feld getroffen wurde
// 
//    Rev 1.6   20 Mar 1995 12:13:56   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.5   17 Oct 1994 15:01:12   HANNES
// Ueberfluessige Updates auf den Index rausgeschmissen
// 
//    Rev 1.4   03 Oct 1994 11:12:42   HANNES
// restoredone wieder rueckgesetzt
// 
//    Rev 1.3   20 Sep 1994 11:24:58   HANNES
// Fehlerkorrektur im Hintergrundlesen
// 
//    Rev 1.2   27 Jun 1994 11:07:12   HANNES
// Virtuelle exportierte Funktionen nicht mehr als Inline
// 
//    Rev 1.1   24 Jun 1994 20:42:54   MARTIN
// 
//    Rev 1.0   24 Jun 1994 16:45:44   MARTIN
// Neuuebernahme clinicum
//

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#define CARETHANDLING_DONE
#include "cfield.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"

DLLExport _export WINAPI InputObj::InputObj (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI EnterPoint::EnterPoint (LPVOID p,mdiChild *c) : InputObj (p,c) { }
DLLExport _export WINAPI EnterCont::EnterCont (LPVOID p,mdiChild *c) : InputObj (p,c) { }

#define MODULENUM 35
#include "winass.hpp"
#include "digitize.hpp"
#include "ddsmsg.h"
#include "namfld.hpp"
#include "sound.hpp"

extern HWND WBase_hFrameWin;
extern HINSTANCE WBase_hInstance;

InputObj FAR *lname;
static MouseName mn;
static LPSTR oName;
void InputObj::SetName ()
  {
  if (Def->ShowNameAtMouse) {
    LPSTR Name = Par()->Name(m);
    if (Name != oName)
      mn.Create (m.MyHandle(),oName = Name) ;
    mn.Show (m.MyHandle());
    lname = this;
    }
  }

DLLExport void _export WINAPI ShowName ()
  {
  if (lname != NULL)
    lname->SetName();
  }

DLLExport void _export WINAPI ClearName ()
  {
  if (lname != NULL) {
    mn.Clear (lname->m.MyHandle());
    oName = NULL ;
    lname = NULL ;
    }
  }

DLLExport void _export WINAPI HideName ()
  {
  if (lname != NULL)
    mn.Clear (lname->m.MyHandle());
  }

#ifdef ALTER_SCHEISS  
    (gerade eben 1/4 Stunden alt)
////////////////////////////////////////////////////////////
//  Vernuenftige Invalidierfunktion
////////////////////////////////////////////////////////////
void InvalidatePartErase (PaintContext *pc,HWND hWnd,LPRECT rv,LPRECT ri)
  {
  // Es wird der Bereich r1 mit FALSE invalidiert, wobei
  // r1 zuerst selbst geloescht wird (mit der Einschraenkung, dass
  // r2 von der Loeschung ausgenommen wird...
  RECT r1,r2;
  pc->LogRecttoPhys (&r1,rv);
  pc->LogRecttoPhys (&r2,ri);

  int dummy ;
  if (r1.bottom < r1.top)
    dummy = r1. bottom , r1.bottom = r1.top , r1.top = dummy;
  if (r2.bottom < r2.top)
    dummy = r2. bottom , r2.bottom = r2.top , r2.top = dummy;

  InflateRect (&r1,1,1);
  InflateRect (&r2,-1,-1);

  pc->ResetMap ();
  HRGN hrgn = CreateRectRgnIndirect (&r2);
  SelectClipRgn (pc->hDC,hrgn);
  HBRUSH hb = SelectObject (pc->hDC,GetStockObject (WHITE_BRUSH));
  HPEN   hp = SelectObject (pc->hDC,GetStockObject (NULL_PEN));
  Rectangle (pc->hDC,r1.left,r1.top,r1.right,r1.bottom);
  SelectObject (pc->hDC,hb);
  SelectObject (pc->hDC,hp);
  DeleteObject (hrgn);

  InvalidateRect (hWnd,&r1,FALSE);
  }
#endif

////////////////////////////////////////////////////////////
//  Funktionen der Eingabe - Definition
////////////////////////////////////////////////////////////
#define GWL_ED  0

DefEnt::DefEnt (DefEnt_param FAR *p,mdiChild *x)
  { 
  par = p ; m.PrivData = x ; 
  }

void DefEnt::ShowEnterMark (PaintContext *pc,int x,int y)
  {
  pc->Attrib(PENDATA(RGB(0,0xFF,0),2,PS_SOLID));
  *pc << Line (x-25,y-25,x+25,y-25);
  *pc << Line (x+25,y-25,x+25,y+25);
  *pc << Line (x+25,y+25,x-25,y+25);
  *pc << Line (x-25,y+25,x-25,y-25);
  }

void DefEnt::ShowEnterCont (PaintContext *pc,int FAR *cnts)
  {
  pc->Attrib(PENDATA(RGB(0,0,0)));
  pc->ExtMetaOut (hmf,cnts);
  }

void DefEnt::InvalidateEnterMark (PaintContext *pc,int x,int y)
  {
  RECT r;
  r.left = x-26 ;  r.right  = x+26 ;
  r.top  = y-26 ;  r.bottom = y+26 ;
  pc->LogRecttoPhys (&r,&r);
  int dummy;
  if (r.left > r.right ) dummy = r.left , r.left = r.right  , r.right  = dummy ;
  if (r.top  > r.bottom) dummy = r.top  , r.top  = r.bottom , r.bottom = dummy ;
  r.left -- ;   r.right ++ ;
  r.top  -- ;   r.bottom ++ ;
  InvalidateRect (hWnd,&r,TRUE);
  }

void DefEnt::InvalidateEnterCont (PaintContext *pc,int FAR *cnts)
  {
  RECT r;
  pc->GetPolyRect (hmf,&r,cnts);
  if ((r.left - r.right != 0) && (r.top - r.bottom != 0)) {
    pc->LogRecttoPhys (&r,&r);
    int dummy;
    if (r.left > r.right ) dummy = r.left , r.left = r.right  , r.right  = dummy ;
    if (r.top  > r.bottom) dummy = r.top  , r.top  = r.bottom , r.bottom = dummy ;
    r.left -- ;   r.right ++ ;
    r.top  -- ;   r.bottom ++ ;
    InvalidateRect (hWnd,&r,FALSE);
    }
  }

void DefEnt::ShowActMark (PaintContext *pc,int x,int y)
  {
  pc->Attrib(PENDATA(RGB(0xFF,0,0),1,PS_SOLID));
  *pc << Line (x-50,y,x+50,y);
  *pc << Line (x,y-50,x,y+50);
  }

void DefEnt::ShowActCont (PaintContext *pc,int FAR *cnts)
  {
  pc->Attrib(PENDATA(RGB(0xFF,0,0)));
  pc->ExtMetaOut (hmf,cnts);
  }

void DefEnt::InvalidateActMark (PaintContext *pc,int x,int y)
  {
  RECT r;
  r.left = x-51 ;  r.right  = x+51 ;
  r.top  = y-51 ;  r.bottom = y+51 ;
  pc->LogRecttoPhys (&r,&r);
  int dummy;
  if (r.left > r.right ) dummy = r.left , r.left = r.right  , r.right  = dummy ;
  if (r.top  > r.bottom) dummy = r.top  , r.top  = r.bottom , r.bottom = dummy ;
  r.left -- ;   r.right ++ ;
  r.top  -- ;   r.bottom ++ ;
  InvalidateRect (hWnd,&r,TRUE);
  }

void DefEnt::InvalidateActCont (PaintContext *pc,int FAR *cnts)
  {
  InvalidateEnterCont (pc,cnts);
  }

void DefEnt::ShowNormal (PaintContext *pc,SeqGr FAR *s)
  {
  if (((InputObj FAR *) m.GetObjectFromPar (s->p))->GetType() == ET_POINT) {
    short x = *(short FAR *)m.ReadlData(s->p->dgrDef.pt.X);
    short y = *(short FAR *)m.ReadlData(s->p->dgrDef.pt.Y);
    ShowEnterMark (pc,int (x),int (y));
    }
  else {
    WORD NumConts = *(LPWORD)m.ReadlData(s->p->dgrDef.cntdef[0]);
    int FAR *cnt = (int FAR *)
        GetGlobMem (int (sizeof(int) * (NumConts + 1)));
    for (int i = 0 ; i <= int (NumConts) ; i++)
      cnt[i] = int (*(short FAR *)m.ReadlData(s->p->dgrDef.cntdef[i])) ;
    ShowEnterCont (pc,cnt);
    FreeGlobMem (cnt);
    }
  }

void DefEnt::ShowSelected (PaintContext *pc,SeqGr FAR *s)
  {
  if (((InputObj FAR *) m.GetObjectFromPar (s->p))->GetType() == ET_POINT) {
    short x = *(short FAR *)m.ReadlData(s->p->dgrDef.pt.X);
    short y = *(short FAR *)m.ReadlData(s->p->dgrDef.pt.Y);
    ShowActMark (pc,int (x),int (y));
    }
  else {
    WORD NumConts = *(LPWORD)m.ReadlData(s->p->dgrDef.cntdef[0]);
    int FAR *cnt = (int FAR *) 
        GetGlobMem (int (sizeof(int) * (NumConts + 1)));
    for (int i = 0 ; i <= int (NumConts) ; i++)
      cnt[i] = int (*(short FAR *)m.ReadlData(s->p->dgrDef.cntdef[i])) ;
    ShowActCont (pc,cnt);
    FreeGlobMem (cnt);
    }
  }

void DefEnt::Invalidate (EntPtCnt_param FAR *p)
  {
  if (!hWnd) return;
  PaintContext pc (hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.Map (scale,x0,y0,xp,yp);
  if (((InputObj FAR *) m.GetObjectFromPar (p))->GetType() == ET_POINT) {
    short x = *(short FAR *)m.ReadlData(p->dgrDef.pt.X);
    short y = *(short FAR *)m.ReadlData(p->dgrDef.pt.Y);
    InvalidateActMark (&pc,int (x),int (y));
    }
  else {
    WORD NumConts = *(LPWORD)m.ReadlData(p->dgrDef.cntdef[0]);
    int FAR *cnt = (int FAR *) 
        GetGlobMem (int (sizeof(int) * (NumConts + 1)));
    for (int i = 0 ; i <= int (NumConts) ; i++)
      cnt[i] = int (*(short FAR *)m.ReadlData(p->dgrDef.cntdef[i])) ;
    InvalidateActCont (&pc,cnt);
    FreeGlobMem (cnt);
    }
  }

void DefEnt::PaintExtraGr(EntPtCnt_param FAR *par,BOOL state)
  {
  Invalidate (par);
  if (state)
    act = par ;
  else
    act = NULL ;
  }

void DefEnt::PaintSeq (PaintContext *pc)
  {
  SeqGr FAR *a = NULL;
  for (SeqGr FAR *s = Root ; s != NULL ; s = s->Next) {
    ShowNormal (pc,s);
    if (s->p == act) a = s;
    }
  if (a != NULL)
    ShowSelected (pc,a);
  }

void DefEnt::CalcScale ()
  {
  PaintContext pc (hWnd,0xFFFF,0xFFFF,DO_WORK);
  pc.Map (1.0);
  int dxs = pc.XPHYStoLOG (pc.cr.right);
  int dys = pc.YPHYStoLOG (-pc.cr.bottom);
  int dxl = int ((xmax - xmin) * float (27.5)) ; // 10 % Reserve
  int dyl = int ((ymax - ymin) * float (27.5)) ;
  float xfact = float (dxs) / float (dxl) ;
  float yfact = float (dys) / float (dyl) ;
  scale = min (xfact,yfact) ;
  xp = (pc.cr.left + pc.cr.right) / 2 ;
  yp = (pc.cr.top + pc.cr.bottom) / 2 ;
  x0 = int ((xmax + xmin) * 12.5);
  y0 = int ((ymax + ymin) * 12.5);
  }

#pragma pack(1)
struct WndPos {
  short x,y,w,h;
  };
#pragma pack()

void DefEnt::WriteWndPos ()
  {
  RECT r;
  GetWindowRect (hWnd,&r);

  WndPos wp;
  wp.x = (short)r.left ;
  wp.y = (short)r.top ;
  wp.w = (short)(r.right - r.left + 1);
  wp.h = (short)(r.bottom - r.top + 1);

  m.WritelData (par->PosRef,&wp,sizeof(wp),LPSTR(par)-sizeof(WORD));
  }

DLLExport LONG _export CALLBACK EntGrWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LPDEFENT ed = LPDEFENT (GetWindowLong (hWnd,GWL_ED));
  switch (msg) {
    case WM_CREATE :
      {
      LPCREATESTRUCT lpc = LPCREATESTRUCT (lP);
      SetWindowLong (hWnd,GWL_ED,LONG (ed = LPDEFENT(lpc->lpCreateParams)));
      ed->hWnd = hWnd;
      }
      break ;
    case WM_SIZE :
      ed->WriteWndPos ();
      ed->CalcScale ();
      SetFocus (GetParent (hWnd));
      break ;
    case WM_MOVE :
      ed->WriteWndPos ();
      SetFocus (GetParent (hWnd));
      break ;
    case WM_PAINT :
      {
      PaintContext pc(hWnd,BLACK_PEN,WHITE_BRUSH) ;
      pc.Map (ed->scale,ed->x0,ed->y0,ed->xp,ed->yp);

      pc << MetaDesc (ed->hmf);
      ed->PaintSeq (&pc);
      }
      break ;
    default :
      return DefWindowProc (hWnd,msg,wP,lP);
    }

  return 0L ;
  }

static char *DefEntWndClass = "DEFENTWND";
static void RegisterDEWnd ()
  {
  static BOOL IsRegistered;
  if (!IsRegistered) {
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = EntGrWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = sizeof(LPVOID);
    wc.hInstance     = WBase_hInstance;
    wc.hIcon         = 0;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = DefEntWndClass;

    IsRegistered = RegisterClass(&wc);
    }
  }

void DefEnt::Create ()
  {
  DWORD DataSize;
  GLOBALHANDLE hGmem = ReadResourceData (par->picRef,&DataSize);

#ifdef WIN32
  BYTE *metafile = (BYTE *)GlobalLock(hGmem);
  hmf = SetMetaFileBitsEx (UINT(DataSize), (CONST BYTE *)metafile);
  GlobalUnlock(hGmem);
#else
  hmf = SetMetaFileBits (hGmem);
#endif

  GlobalUnlock (hGmem);
  PaintContext pchelp(WBase_hFrameWin,0xFFFF,0xFFFF,DO_WORK);
  RECT r;
  pchelp.GetMaxInfo (hmf,&r);
  ymin = float (r.bottom) / float (25.0) ;
  ymax = float (r.top) / float (25.0) ;
  xmin = float (r.left) / float (25.0) ;
  xmax = float (r.right) / float (25.0) ;
  RegisterDEWnd ();

  int x,y,w,h;
  WndPos FAR *wp = (WndPos FAR *) 
    m.ReadlData (par->PosRef);
  if (wp != NULL) {
    x = wp->x , y = wp->y , w = wp->w , h = wp->h ;
    }
  else {
    w = h = GetSystemMetrics (SM_CYSCREEN) / 2 ;
    x = (GetSystemMetrics (SM_CXSCREEN) - w) / 2 ;
    y = (GetSystemMetrics (SM_CYSCREEN) - h) / 2 ;
    }
    
  char titel[100];
  *titel = '\0';
  LoadString (WBase_hInstance,8031,titel,sizeof(titel) - 1) ; 
  CreateWindow (DefEntWndClass, titel,
                WS_POPUP | WS_CAPTION | WS_THICKFRAME,
                x, y, w, h,
                m.MyHandle(), 0, WBase_hInstance, LPVOID(this)
               );
  ShowWindow (hWnd,SW_SHOWNOACTIVATE);
  }

void DefEnt::InsertGr (EntPtCnt_param FAR *par,BOOL doInvalidate,BOOL doCreate)
  {
  SeqGr FAR *n = (SeqGr FAR *) GetGlobMem (sizeof(*n));
  n->p = par;

  if (Root == NULL) {
    n->Next = NULL ;
    Root = n;
    if (doCreate) Create ();
    }
  else {
    // entsprechend der uFrmShowObject - Aufrufe einsortieren
    LPSCRIPTCONTENT sc = ((FrmObject *)(par->objlist))->m.PrivData->schd;
    DBWIN_ASSERT_TEXT(sc->fSize < 65535L,"Script fuer Eingabe zu gross !");
    DWORD ScriptBeg = DWORD(((FrmObject *)(par->objlist))->m.PrivData->GetCmdBase());
    DWORD ScriptEnd = ScriptBeg + sc->fSize;
    LPOBJDEF ol = ((FrmObjectList FAR *) (m.PrivData->OutList()))->head;
    SeqGr FAR *h = Root;
    SeqGr FAR *last = NULL;
    for (LPOBJDEF node = ol ; node != NULL ; node = node->NextObjDef) {
      // nur uFrmShowObjects in Betracht ziehen, die im selben Script liegen
      if ((DWORD(node->par) > ScriptBeg) &&
          (DWORD(node->par) < ScriptEnd)) {
        DWORD oi = MAKELONG(node->par->ObjRec,node->par->ObjId);
        if (oi == par->ObjId) {
          break;
          }
        else {
          if (oi == h->p->ObjId) {
            last = h;
            h = h->Next;
            if (h == NULL)
              break;
            }
          }
        }
      if (node->NextObjDef == ol) {
        node = NULL ;
        break ;
        }
      }
    if (last == NULL) {
      n->Next = Root;
      Root = n;
      }
    else {
      n->Next = h;
      last->Next = n;
      }
    }

  if (doInvalidate)
    Invalidate (n->p);
  }

void DefEnt::RemoveGr (EntPtCnt_param FAR *par,BOOL doInvalidate)
  {
  SeqGr FAR *prev = NULL;
  for (SeqGr FAR *h = Root ; h != NULL ; h = h->Next) {
    if (h->p == par) {
      if (prev != NULL)
        prev->Next = h->Next;
      else
        Root = h->Next;
      break ;
      }
    prev = h;
    }
  DBWIN_ASSERT (h != NULL);

  if (doInvalidate)
    Invalidate (h->p);
  FreeGlobMem (h);

  if ((hWnd) && (Root == NULL)) {
    DestroyWindow (hWnd);
    hWnd = 0;
    }

  if ((hmf) && (Root == NULL)) {
    DeleteMetaFile (hmf);
    hmf = 0;
    }
  }

int DefEnt::GetSeqNum (EntPtCnt_param FAR *p)
  {
  SeqGr FAR *h = Root ;
  for (int i = 0 ; h != NULL ; i++) {
    if (h->p == p)
      break ;
    else
      h = h->Next;
    }
  DBWIN_ASSERT(h != NULL);
  return i;
  }

void DefEnt::ActivateName (EntPtCnt_param FAR *p)
  {
  int ind = GetSeqNum (p);
  DBINT FAR *oldInd = (DBINT FAR *) m.ReadlData (par->SeqInd);
  if ((oldInd == NULL) || (ind != *oldInd))
    m.WritelData (par->SeqInd,&ind,sizeof(ind),LPSTR(par)-sizeof(WORD));
  }

void DefEnt::DeActivateName ()
  {
#ifdef UEBERLEGT
  m.DellData (par->SeqInd,0,LPSTR(par)-sizeof(WORD));
#endif
  }

static LPSTR AddString (LPSTR Name,LPSTR old,BOOL doFree)
  {
  int offs = (old != NULL) ? (GetBlockSize (old) - 1) : 0 ;
  int strsize = lstrlen (Name) + 1;
  LPSTR res = LPSTR (GetGlobMem (strsize + offs + 1));  // hinten 2 
                                                        // Nullzeichen bitte
  if (old != NULL)
    lmemcpy (res,old,offs);
  lmemcpy (res+offs,Name,strsize);
  if ((doFree) && (old != NULL))
    FreeGlobMem (old);
  return res;
  }

void DefEnt::WriteNameList ()
  {
  LPSTR AllNames = NULL;
  for (SeqGr FAR *h = Root ; h != NULL ; h = h->Next)
    AllNames = AddString (h->p->Name(m),AllNames,TRUE);
  if (AllNames != NULL) {
    m.WritelData (par->AllNames,AllNames,GetBlockSize(AllNames),LPSTR(par)-sizeof(WORD));
    FreeGlobMem (AllNames);
    }
  else
    m.DellData (par->AllNames,LPSTR(par)-sizeof(WORD));
  }

#ifdef UEBERLEGT
void DefEnt::InsertName (EntPtCnt_param FAR *p)
  {
  LPSTR Name = p->Name(m);
  LPSTR AllNames = LPSTR (m.ReadlData (par->AllNames));
  LPSTR res = AddString (Name,AllNames,FALSE);
  m.WritelData (par->AllNames,res,GetBlockSize(res),LPSTR(par)-sizeof(WORD));
  FreeGlobMem (res);
  }

void DefEnt::RemoveName (EntPtCnt_param FAR *p)
  {
  int ind = GetSeqNum (p);
  LPSTR AllNames = LPSTR (m.ReadlData (par->AllNames));
  DBWIN_ASSERT (AllNames != NULL);
  LPSTR h = AllNames;
  LPSTR res = NULL;
  for ( int i = 0 ; *h ; i++ ) {
    LPSTR n = h + lstrlen (h) + 1;
    if (i != ind) {
      res = AddString (h,res,TRUE);
      }
    h = n;
    }
  if (res != NULL) {
    m.WritelData (par->AllNames,res,GetBlockSize(res),LPSTR(par)-sizeof(WORD));
    FreeGlobMem (res);
    }
  else
    m.DellData (par->AllNames,LPSTR(par)-sizeof(WORD));
  }
#endif

///////////////////////////////////////////////////////////
FrmObject FAR *DefEnt::GetInputObj (int i)
  {
  if (Root == NULL) return NULL;  // noch kein Objekt definiert
  SeqGr FAR *h = Root;
  for (int j = 0 ; ((j < i) && (h->Next != NULL)) ; j++)
    h = h->Next ;
  return (m.GetObjectFromPar (h->p));
  }

void DefEnt::OnIndChange ()
  {
  DBINT FAR *ind = (DBINT FAR *) m.ReadlData (par->SeqInd);
  int i = (ind != NULL) ? *ind : 0;
  LPFRMOBJ io = GetInputObj(i);
  if (io != NULL) {
    m.SetActiveExplicit (GetInputObj(i));
    SetFocus (m.MyHandle());
    }
  }

void DefEnt::GetScaleMat ()
  {
  // Laden der Skalierungsfaktoren
  /////////////////////////////////////////
  ftr2 FAR *lpetod = (ftr2 FAR *) m.ReadlData (par->scetod);
  ftr2 FAR *lpdtos = (ftr2 FAR *) m.ReadlData (par->scdtos);
  if (lpetod != NULL)
    etod = *lpetod;
  else    // So koennen die eingegebenen Daten nicht verarbeitet werden
          // -> so kann nicht gearbeitet werden
    return ;

  if (lpdtos != NULL)
    dtos = *lpdtos;   // Die muss nicht unbedingt existieren
                      // (Bsp. Digitizer Eingabe...)
  else {
    dtos.A[0][0] = dtos.A[1][1] = float (1.0) ;
    dtos.A[0][1] = dtos.A[0][1] = 
    dtos.B[0]    = dtos.B[1]    = float (0.0) ;
    }
  }


///////////////////////////////////////////////////////////
// Funktionen der Basis - Eingabe Klasse
///////////////////////////////////////////////////////////
BOOL InputObj::IsInputObj ()
  { 
  return TRUE ; 
  }

int InputObj::GetType ()
  { 
  return ET_NONE ; 
  }

void InputObj::ArmHardware (BOOL state) { }
void InputObj::SetData (LPVOID data) { }   // Speichern der internen Daten
void InputObj::ResetData () { }
void InputObj::DelMyData () { }

void InputObj::ShowHelp ()
  {
  if (Par()->KontextNr > 0)
    WinHelp (m.MyHandle(), "DDS.HLP", HELP_CONTEXT, Par()->KontextNr);
  else
    MessageBeep (0);
  }

BOOL InputObj::IsToActivate ()
  {
  return (mode != INPUT_NOTDEFINED);
  }

void InputObj::SetActive (int Seite,BOOL bexplicit)
  {
  if (Def->SayName) {
    int anzsnd = Par()->SoundCount(GetType(),m);
    DWORD FAR *sndstr = Par()->SoundNames(GetType(),m);
    LPSTR path = (LPSTR)m.ReadlData(Def->WavePath);
    for (int i = 0; i < anzsnd; i++) {
      LPSTR sndname = (LPSTR)m.ReadlData(sndstr[i]);
      if ((sndname != NULL) && (*sndname)) {
        char filnam[128];
        if (path != NULL)
          lstrcpy(filnam, path);
        else
          *filnam = '\0';
        lstrcat(filnam, sndname);
        SndPlayWav(filnam, (i == 0) ? SPW_NORMAL : SPW_DONTSTOPLAST);
        }
      }
    }
  if (IsDigitizer()) {
    Def->PaintExtraGr(Par(),TRUE);
    }
  else if (IsImage()) {
    SetName ();
    Invalidate(Seite);
    ScrollInto();
    }
  Def->ActivateName (Par());      // Den Index schreiben...
  ArmHardware (TRUE);
  }

void InputObj::SetInActive (int Seite)
  {
  if (IsDigitizer()) {
    Def->PaintExtraGr(Par(),FALSE);
    }
  else if (IsImage()) {
    Invalidate(Seite);
    ClearName ();
    }
  Def->DeActivateName ();        // Den Index loeschen...
  ArmHardware (FALSE);
  }

/////////////////////////////////////////////////////////////////////
//  Cursor - Handling
/////////////////////////////////////////////////////////////////////
class FAR CursorList {
 private :
  int RefCount;
  HCURSOR hCur;

 public :
  HCURSOR Load (LPSTR Name);
  void Remove ();
  };

HCURSOR CursorList::Load (LPSTR Name)
  {
  if (RefCount == 0) {
    hCur = (HCURSOR)LoadCursor (WBase_hInstance,Name);
    }
  RefCount ++ ;
  return hCur;
  }

void CursorList::Remove ()
  {
  RefCount -- ;
  if (RefCount == 0) {
    DestroyCursor (hCur);
    hCur = 0;
    }
  }
static CursorList nCursorl,cCursorl,iCursorl;

void InputObj::MyLoad (BOOL doInsert)
  {
  // Laden der Eigabe - Definition (die muss es aber geben...)
  LPDEFENT FAR *lpde = (LPDEFENT FAR *) m.ReadlData (Par()->EntDef);
  DBWIN_ASSERT ((lpde != NULL) && (*lpde != NULL))
  Def = *lpde;

  // Laden des Punktes
  Initialized = FALSE ;

  LPVOID Data = m.ReadlData (Par()->Cntpt);
  if (Data != NULL)
    OwnData = TRUE ;
  else
    OwnData = FALSE ;

  // Lesen des Modus...
  ////////////////////////////
  DBINT FAR *lpmode = (DBINT FAR *) m.ReadlData (Par()->mode);
  if (lpmode != NULL)
    mode = *lpmode;
  else
    mode = INPUT_NOTDEFINED;

  // Entsprechenden Update in der Liste
  ////////////////////////////////////////
  if (doInsert) {
    if (IsDigitizer())
      Def->InsertGr(Par(),TRUE,TRUE);
    else if (IsImage())
      Def->InsertGr(Par(),FALSE,FALSE);

    // Name in der Liste...
    if (mode != INPUT_NOTDEFINED)
      Def->WriteNameList ();
    }

  if (Data != NULL)
    SetData (Data);
  else
    ResetData ();

  Initialized = TRUE ;
  }

void InputObj::Load ()
  {
  MyLoad (TRUE);
  /*-----< Laden der Digitizer - DLL >-----*/
  if (IsDigitizer())
    InitDigLib ();
  else {
    nCursor = nCursorl.Load ("ech");
    cCursor = cCursorl.Load ("ech1");
    iCursor = iCursorl.Load ("ech2");
    }
  }

void InputObj::SetConnection()
  {
  m.SetlConnection (Par()->mode    ,Offset());
  m.SetlConnection (Par()->EntDef  ,Offset());
  m.SetlConnection (Par()->Cntpt   ,Offset());
  }

class FAR TestObj {
 public :
  InputObj FAR *ActIObj;
  int iInd;
  int cInd;
  BOOL InEnter;

  BOOL IsActive (InputObj FAR *o);
  void Reset ();
  void ArmObj (InputObj FAR *o,int i = -1,int c = -1)
    { ActIObj = o ; iInd = i ; cInd = c ; } 
  void SetEnter()
    { InEnter = TRUE ; }
  BOOL IsInEnter()
    { return InEnter ; }
  };
static TestObj to;

void InputObj::Reset(BOOL doClear)
  {
  m.ClearlConnection (Par()->mode    ,Offset());
  m.ClearlConnection (Par()->EntDef  ,Offset());
  m.ClearlConnection (Par()->Cntpt   ,Offset());

  if (IsDigitizer()) {
    ExitDigLib ();
    if (IsWindow (m.MyHandle()))
      SendMessage (m.MyHandle(),WMU_CLOSECOMM,0,0L);      // Digitizer noch abstellen
    }
  else {
    nCursorl.Remove ();
    cCursorl.Remove ();
    iCursorl.Remove ();
    }

  DelMyData ();
  LPDEFENT FAR *lpde = (LPDEFENT FAR *) m.ReadlData (Par()->EntDef);
  if ((lpde != NULL) && (*lpde != NULL)) {
    (*lpde)->RemoveGr  (Par(),doClear);
    (*lpde)->WriteNameList ();
    }
  to.Reset ();
  if (lname == this)
    lname = NULL;
  }

void InputObj::Update ()
  {
  // Der Modus muss hundertprozent richtig sein...
  DBINT FAR *lpmode = (DBINT FAR *) m.ReadlData (Par()->mode);
  int nmode;
  if (lpmode != NULL)
    nmode = *lpmode;
  else
    nmode = INPUT_NOTDEFINED;

  if (mode != nmode) {
    // Digitizer - Graphik
    if (nmode == INPUT_NOTDEFINED) {
      // Modus hat sich vom Digitizer wegbewegt
      Def->RemoveGr(Par(),TRUE);
      Def->WriteNameList ();
      }
    else {
      Def->InsertGr(Par(),TRUE,FALSE),
      Def->WriteNameList ();
      if ((mode != INPUT_DIGITIZER) && (nmode == INPUT_DIGITIZER))
        InitDigLib ();
      }

    mode = nmode;
    }
  else
    MyLoad (FALSE);
  }

////////////////////////////////////////////////////////////////////
//  Sonstige kleine Hilfsfunktionen
////////////////////////////////////////////////////////////////////
DWORD FAR *EntPtCnt_param::SoundNames(int Type,dllChild m)
  {
  int offs = sizeof(*this) - sizeof(dgrDef);
  if (Type == ET_POINT)
    offs += sizeof(dgrDef.pt);
  else if (Type == ET_CONT)
    offs += (1 + int(*(LPWORD)m.ReadlData(dgrDef.cntdef[0]))) * sizeof(DWORD);
  else
    DBWIN_ASSERT(FALSE);
  return (DWORD FAR *)(LPSTR(this) + offs);
  }

int EntPtCnt_param::SoundCount(int Type,dllChild m)
  {
  return (DWORD FAR *)(LPSTR(this) + parSize) - SoundNames(Type,m);
  }

LPSTR EntPtCnt_param::Name (dllChild m)
  {
  LPSTR xN = LPSTR (m.ReadlData (NameRef));
  if (xN != NULL)
    return xN;
  else {
    DBWIN_ASSERT (FALSE);
    }
  return NULL;
  }

////////////////////////////////////////////////////////////////////
//  Implementierung der richtigen Eingaben
////////////////////////////////////////////////////////////////////
int EnterPoint::GetType ()
  { 
  return ET_POINT ; 
  }

void EnterPoint::SetData (LPVOID data)
  {
  fpt FAR *pt = (fpt FAR *) data;
  fpt scpt;
  Sc2d ((tr2 FAR *) &Def->dtos,&scpt,pt);
  x = m.WorldToLog (scpt.x);
  y = m.WorldToLog (scpt.y);
  }

void EnterPoint::ResetData ()
  {
  x = y = 0x8000 ;
  }

#define RDX   45
#define RDY   45
#define MAXDX   136
#define MAXDY   136
#define RL    227.0
int EnterCont::GetType ()
  { 
  return ET_CONT ; 
  }
void EnterCont::GetZCont ()
  {
  if (zcnt != NULL) FreeGlobMem (zcnt) ;
  zcnt = NULL;
  if (PtCount > 1) {
    zcnt = (LogPt FAR *) GetGlobMem (PtCount * sizeof(LogPt));
    double dxg = double (cnt[1].x - cnt[0].x) ;
    double dyg = double (cnt[1].y - cnt[0].y) ;
    double lg = sqrt(dxg*dxg+dyg*dyg);
    if (lg >= 0.01) {
      zcnt[0].x = cnt[0].x - int (RL / lg * dxg);
      zcnt[0].y = cnt[0].y - int (RL / lg * dyg);
      }

    for (WORD i = 1 ; i < PtCount ; i++) {
      zcnt[i].x = (cnt[i-1].x + cnt[i].x) / 2;
      zcnt[i].y = (cnt[i-1].y + cnt[i].y) / 2;
      }
    }
  }

void EnterCont::SetData (LPVOID data)
  {
  fpt FAR *ncnt = (fpt FAR *) data;
  ncnt = get_cont(ncnt, (int FAR *)&PtCount);
  if (PtCount > 0) {
    int size = PtCount * sizeof(fpt);
    if (size != int (GetBlockSize (cnt))) {
      if (cnt != NULL) FreeGlobMem(cnt);
      cnt = (LogPt FAR *)GetGlobMem(PtCount * sizeof(fpt));
      }
    for (WORD i = 0; i < PtCount; i++) {
      fpt scpt;
      Sc2d ((tr2 FAR *) &Def->dtos,&scpt,&ncnt[i]);
      int x = m.WorldToLog (scpt.x);
      int y = m.WorldToLog (scpt.y);
      cnt[i].x = m.WorldToLog(scpt.x);
      cnt[i].y = m.WorldToLog(scpt.y);
      }
    }
  else {
    if (cnt != NULL) FreeGlobMem(cnt);
    cnt = NULL;
    }
  GetZCont ();
  }

void EnterCont::ResetData ()
  {
  if (cnt != NULL)
    FreeGlobMem (cnt);
  if (zcnt != NULL)
    FreeGlobMem (zcnt);
  cnt = zcnt = NULL;
  PtCount = 0;
  }

void EnterPoint::ArmHardware (BOOL state)
  {
  if (IsDigitizer())
    SetupForPoint (m.MyHandle(),state);
  }

void InputObj::OnDigitized (UINT Command,GLOBALHANDLE hGmem)
  {
  if ((Command == WMU_DIGITIZED) && (hGmem)) {
    MessageBeep (WORD(-1));   // Dem Benutzer mal das wichtigste mitteilen
    LPSTR buffer = LPSTR(GlobalLock (hGmem));
    WORD count = (*(WORD FAR *) buffer - sizeof(WORD)) / sizeof (fpt) ;
    for (int i = 0 ; i < int (count) ; i++)
      Sc2d ((tr2 FAR *) &Def->etod,((fpt FAR *) (buffer+sizeof(WORD))) + i,
                    ((fpt FAR *) (buffer+sizeof(WORD))) + i);

    m.WritelData(Par()->Cntpt,buffer + sizeof(WORD),
              count * sizeof (fpt),LPSTR(ScriptParam)-sizeof(WORD));
    // Vermerken, dass Punkt digitalisiert wurde
    BOOL flag = TRUE ;
    m.WritelData(Par()->SetOnStore,&flag,
              sizeof(flag),LPSTR(ScriptParam)-sizeof(WORD));

    GlobalUnlock (hGmem);
    GlobalFree (hGmem);

    // Und weiter zum Naechsten
    if ((IsDigitizer()) || (GetType() == ET_POINT)) {
      m.EmptyUpdateList ();
      m.NextField ();
      }
    }
  else if (Command == WMU_DIGNEXT) {
    m.NextField ();
    }
  else if (Command == WMU_DIGPREV) {
    m.PrevField ();
    }
  else if (Command == WMU_DIGDEL) {
    OnKeyDown (VK_DELETE,m.ActSide());
    }
  }

void EnterCont::ArmHardware (BOOL state)
  {
  if (IsDigitizer())
    SetupForCont (m.MyHandle(),state);
  }

void EnterPoint::DelMyData ()
  {
  }

void EnterCont::DelMyData ()
  {
  if (cnt != NULL)
    FreeGlobMem (cnt);
  if (zcnt != NULL)
    FreeGlobMem (zcnt);
  }

/////////////////////////////////////////////////////////////////////////
//  Implementierung der Image - Eingaben
/////////////////////////////////////////////////////////////////////////
void InputObj::InflateMinMax (LPRECT rcLogRect)
  {
  InflateRect (rcLogRect,RDX,RDY);
  }

void EnterPoint::GetMinMax ()
  {
  if ((Initialized) && (IsImage()) && ((x != 0x8000) || (y != 0x8000))) {
    RECT rcLogRect;
    rcLogRect.left = rcLogRect.right = x ;
    rcLogRect.top = rcLogRect.bottom = y ;
    InflateMinMax (&rcLogRect);
    SetLogRect (&rcLogRect,ErsteSeite());
    }
  }

void EnterCont::GetMinMax ()
  {
  if ((Initialized) && (IsImage()) && (cnt != NULL)) {
    RECT rcLogRect;
    if (zcnt != NULL) {
      rcLogRect.left   = rcLogRect.right  = zcnt[0].x;
      rcLogRect.top    = rcLogRect.bottom = zcnt[0].y;
      }
    else {
      rcLogRect.left   = rcLogRect.right  = cnt[0].x;
      rcLogRect.top    = rcLogRect.bottom = cnt[0].y;
      }
    for (WORD i = 0 ; i < PtCount; i++) {
      rcLogRect.left   = min(cnt[i].x,rcLogRect.left);
      rcLogRect.right  = max(cnt[i].x,rcLogRect.right);
      rcLogRect.top    = min(cnt[i].y,rcLogRect.top);
      rcLogRect.bottom = max(cnt[i].y,rcLogRect.bottom);
      }
    InflateMinMax (&rcLogRect);
    SetLogRect (&rcLogRect,ErsteSeite());
    }
  }

BOOL InputObj::IsAct ()
  {
  return ((m.act_obj() == this) && IsActive);
  }

void InputObj::PaintRect (PaintContext *pc,int x,int y)
  {
  MoveToEx (pc->hDC,x - RDX,y - RDX, NULL);
  LineTo (pc->hDC,x - RDX,y + RDX);
  LineTo (pc->hDC,x + RDX,y + RDX);
  LineTo (pc->hDC,x + RDX,y - RDX);
  LineTo (pc->hDC,x - RDX,y - RDX);
  }

void EnterPoint::Paint (PaintContext *pc,int Seite)
  {
  if (!IsImage()) return ;
  if ((x != 0x8000) || (y != 0x8000)) {
    if (IsAct())
      pc->Attrib (PENDATA (RGB(0xFF,0,0)));
    else {
      DBBOOL FAR *stflag = (DBBOOL FAR *) m.ReadlData (Par()->SetOnStore);
      if ((LOWORD(Par()->SetOnStore) == 0) || ((stflag != NULL) && (*stflag)))
        pc->Attrib (PENDATA (RGB(0,0xFF,0)));
      else
        pc->Attrib (PENDATA (RGB(0x80,0x80,0)));
      }
    PaintRect (pc,x,y);
    }
  }

void EnterCont::Paint (PaintContext *pc,int Seite)
  {
  if (!IsImage()) return ;
  if (IsAct())
    pc->Attrib (PENDATA (RGB(0xFF,0,0)));
  else
    pc->Attrib (PENDATA (RGB(0,0xFF,0)));
  for (WORD i = 0; i < PtCount; i++)
    PaintRect (pc,cnt[i].x,cnt[i].y);
  if ((zcnt != NULL) && (Def->InputMode == INPUTMODE_CORRECT)) {
    // Zeichnen der Zwischenpunkte
    pc->Attrib (PENDATA (RGB(0,0,0xFF)));
    for (i = 0 ; i < PtCount ; i++)
      PaintRect (pc,zcnt[i].x,zcnt[i].y);
    }
  }

//////////////////////////////////////////////////////////////
//  Vermerken des Objektes, das sich fuer einen lButtonDown
//  fertig zu machen hat
//////////////////////////////////////////////////////////////
BOOL TestObj::IsActive (InputObj FAR *o)
  {
  if (ActIObj != NULL)
    return (o == ActIObj);
  else 
    return o->IsAct();
  }

void TestObj::Reset ()
  {
  ActIObj = NULL ;
  iInd = cInd = -1;
  InEnter = FALSE ;
  }

/////////////////////////////////////////////////////////////
//  Hintergrundbearbeitung bei der Punkt - Verschiebung
/////////////////////////////////////////////////////////////
class FAR PtBackground {
  HBITMAP hbm;
  HBITMAP holdbmp;
  HDC hmemDC;
  int x0,y0;
  int dx,dy;
  BOOL restoreDone ;
 public :
  void ReadBackground (PaintContext *pc,float scale,int xp,int yp,int x,int y);
  void Restore(PaintContext *pc);
  void Reset ();
  BOOL IsRestoreDone ()
    { return restoreDone ; }
  };

void PtBackground::ReadBackground (PaintContext *pc,
                                   float scale,int xp,int yp,
                                   int x,int y)
  {
  if (hbm == 0) {
    hmemDC = CreateCompatibleDC (pc->hDC);
    pc->LogicalTwips (xp,yp,scale);
    dx = pc->XLOGtoPHYS (2 * RDX) + 2 ;
    dy = pc->YLOGtoPHYS (2 * RDY) + 2 ;
    hbm = CreateCompatibleBitmap (pc->hDC,dx,dy);
    holdbmp = (HBITMAP)SelectObject (hmemDC,hbm);
    }
  SelectObject (hmemDC,hbm);
  pc->LogicalTwips (xp,yp,scale);
  POINT pt;
  pt.x = x - RDX ;
  pt.y = y - RDY ;
  LPtoDP (pc->hDC,&pt,1);
  x0 = pt.x ;
  y0 = pt.y ;
  pc->ResetMap ();
  BitBlt (hmemDC,0,0,dx,dy,pc->hDC,x0,y0,SRCCOPY);
  restoreDone = FALSE ;
  }

void PtBackground::Restore (PaintContext *pc)
  {
  if (hbm) {
    SelectObject (hmemDC,hbm);
    BitBlt (pc->hDC,x0,y0,dx,dy,hmemDC,0,0,SRCCOPY);
    restoreDone = TRUE ;
    }
  else
    restoreDone = TRUE ;
  }

void PtBackground::Reset ()
  {
  if (hbm != 0) {
    SelectObject (hmemDC,holdbmp);
    if (hmemDC)
      DeleteDC (hmemDC);
    else {
      for (int i = 0 ; i < 100 ; i++)
        MessageBeep (0);
      }
    DeleteObject (hbm);
    }
  hbm = 0;
  hmemDC = 0;
  }

static class PtBackground ptb;

DLLExport void _export WINAPI RestorePTB (PaintContext *pc)
  {
  ptb.Restore (pc);
  }

DLLExport void _export WINAPI ReadPTB (PaintContext *pc,HWND MyHandle,float scale,int xp,int yp)
  {
  if (ptb.IsRestoreDone ()) {
    POINT p;
    GetCursorPos (&p);
    ScreenToClient (MyHandle,&p);
    DPtoLP (pc->hDC,&p,1);
    ptb.ReadBackground (pc,scale,xp,yp,p.x,p.y);
    }
  }

void PostMove (HWND hWnd)
  {
  LONG l = GetMessagePos();
#ifdef WIN32
  POINT p;
  LONG2POINT (l, p);
  ScreenToClient (hWnd,&p);
  l = MAKELONG((SHORT)p.x,(SHORT)p.y);
#else
  ScreenToClient (hWnd,LPPOINT(&l));
#endif
  PostMessage (hWnd,WM_MOUSEMOVE,MK_LBUTTON,l);
  }

BOOL EnterPoint::OnLButtonDown (WPARAM wP,int xl,int yl,int Seite)
  {
  if (wP & 0x8000) return FALSE ;
  if (!IsImage ()) return FALSE ;
  if (to.IsActive(this)) {
    ClearName ();
    LPRECT oldr = GetLogRect (ErsteSeite());
    if (oldr != NULL)
      CopyRect (LPRECT (&oldRect),oldr);
    to.SetEnter();
    PaintContext pc(m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
    ptb.ReadBackground (&pc,m_scale(),m.xp(),m.yp(),xl,yl);
    pc.Attrib (PENDATA (RGB(0xFF,0,0)));
    pc.LogicalTwips (m.xp(),m.yp(),m_scale());
    PaintRect (&pc,xl,yl);

    PostMove (m.MyHandle());

    return TRUE ;
    }
  return FALSE ;
  }

BOOL EnterPoint::OnLButtonUp (WPARAM wP,int xl,int yl,int Seite)
  {
  if (!IsImage ()) return FALSE ;
  InvalidateRect (m.MyHandle(),LPRECT (&oldRect),TRUE);
  Invalidate (Seite);
  x = xl , y = yl ;
  GetMinMax ();
  LPRECT logr = GetLogRect (Seite);
  if (logr != NULL)
    m.Rescale (logr);
  Invalidate (Seite);
  GLOBALHANDLE hGmem = GlobalAlloc (GHND,sizeof(fpt)+sizeof(WORD));
  LPSTR Buffer = LPSTR(GlobalLock (hGmem));
  *(WORD FAR *) Buffer = sizeof(fpt) + sizeof (WORD);
  fpt FAR *res = (fpt FAR *) (Buffer + sizeof(WORD));
  res->x = m_LogToWorld (x);
  res->y = m_LogToWorld (y);
  GlobalUnlock (hGmem);
  OnDigitized (WMU_DIGITIZED,hGmem);
  to.Reset ();
  ptb.Reset ();
  return TRUE ;
  }

void EnterCont::EnlargeCont (int ind)
  {
  if (cnt != NULL) {
    LogPt FAR *ncnt = (LogPt FAR *) GetGlobMem (GetBlockSize (cnt) + sizeof(LogPt));
    if (ind < 0) 
      lmemcpy (ncnt,cnt,GetBlockSize(cnt));
    else {
      lmemcpy (ncnt,cnt,ind * sizeof(LogPt));
      lmemcpy (ncnt + ind + 1,cnt + ind,(PtCount - ind) * sizeof(LogPt));
      }
    FreeGlobMem (cnt);
    cnt = ncnt ;
    }
  else
    cnt = (LogPt FAR *) GetGlobMem (sizeof(LogPt));
  PtCount += 1;
  }

BOOL EnterCont::OnLButtonDown (WPARAM wP,int xl,int yl,int Seite)
  {
  if (wP & 0x8000) return FALSE ;
  if (!IsImage ()) return FALSE ;
  if (to.IsActive(this)) {
    ClearName ();
    LPRECT logr = GetLogRect (Seite);
    if (logr != NULL)
      CopyRect (LPRECT (&oldRect),logr);
    to.SetEnter();
    if (to.cInd < 0) {
      EnlargeCont (to.iInd);
      to.cInd = (to.iInd < 0) ? PtCount - 1 : to.iInd;
      }
    PaintContext pc(m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
    ptb.ReadBackground (&pc,m_scale(),m.xp(),m.yp(),xl,yl);
    pc.Attrib (PENDATA (RGB(0xFF,0,0)));
    pc.LogicalTwips (m.xp(),m.yp(),m_scale());
    PaintRect (&pc,xl,yl);

    PostMove (m.MyHandle());
    return TRUE ;
    }
  return FALSE ;
  }

BOOL EnterCont::OnLButtonUp (WPARAM wP,int xl,int yl,int Seite)
  {
  if (!IsImage ()) return FALSE ;
  if ((to.cInd < 0) || (to.cInd >= (int)PtCount))
    return FALSE;  // vermutlich ButtonUp nach DoubleClick
  InvalidateRect (m.MyHandle(),LPRECT (&oldRect),TRUE);
  Invalidate (Seite);
  cnt[to.cInd].x = xl , cnt[to.cInd].y = yl ;
  GetZCont ();
  GetMinMax ();
  LPRECT logr = GetLogRect (Seite) ;
  if (logr != NULL)
    m.Rescale (logr);
  Invalidate (Seite);
  GLOBALHANDLE hGmem = GlobalAlloc (GHND,sizeof(fpt)*PtCount+sizeof(WORD));
  LPSTR Buffer = LPSTR(GlobalLock (hGmem));
  *(WORD FAR *) Buffer = sizeof(fpt) * PtCount + sizeof (WORD);
  fpt FAR *res = (fpt FAR *) (Buffer + sizeof(WORD));
  for (WORD i = 0 ; i < PtCount ; i++) {
    res[i].x = m_LogToWorld (cnt[i].x);
    res[i].y = m_LogToWorld (cnt[i].y);
    }
  GlobalUnlock (hGmem);
  OnDigitized (WMU_DIGITIZED,hGmem);
  to.Reset ();
  ptb.Reset ();
  return TRUE ;
  }

int InputObj::TestCursor (int xc,int yc,int x,int y,HCURSOR hc)
  {
  int dx = xc - x ;       int dy = yc - y ;
  if (dx < 0) dx = -dx ;  if (dy < 0) dy = -dy ;
  if ((dx < MAXDX) && (dy < MAXDY)) {
    SetCursor (hc);
    return SETCURSOR_DONE ;
    }
  else
    return SETCURSOR_NONE ;
  }

int EnterPoint::OnSetCursor (int xc,int yc,int dodef)
  {
  if (!IsImage ()) return FALSE ;
  if ((Initialized) && (!to.IsInEnter()) && (IsToActivate()) && (IsImage())) {
    if (dodef) {
      SetCursor (nCursor);
      to.Reset ();
      }
    else {
      if (Def->InputMode == INPUTMODE_SEQ) return SETCURSOR_WANTDEF ;
      if (TestCursor (xc,yc,x,y,cCursor)) {
        to.ArmObj (this,-1,-1);
        return SETCURSOR_DONE ;
        }
      }
    return SETCURSOR_WANTDEF ;
    }
  else
    return SETCURSOR_NONE ;
  }

int EnterCont::OnSetCursor (int xc,int yc,int dodef)
  {
  if (!IsImage ()) return FALSE ;
  if ((Initialized) && (!to.IsInEnter()) && (IsToActivate()) && (IsImage()) && 
            ((cnt != NULL) || (zcnt != NULL))) {
    if (dodef) {
      SetCursor (nCursor);
      to.Reset ();
      }
    else {
      if (Def->InputMode == INPUTMODE_SEQ) return SETCURSOR_WANTDEF ;
      if (cnt != NULL) {
        for (WORD i = 0 ; i < PtCount ; i++) {
          if (TestCursor (xc,yc,cnt[i].x,cnt[i].y,cCursor)) {
            to.ArmObj (this,-1,i);
            return SETCURSOR_DONE ;
            }
          }
        }
      if (zcnt != NULL) {
        for (WORD i = 0 ; i < PtCount ; i++) {
          if (TestCursor (xc,yc,zcnt[i].x,zcnt[i].y,iCursor)) {
            to.ArmObj (this,i,-1);
            return SETCURSOR_DONE ;
            }
          }
        }
      }
    return SETCURSOR_WANTDEF ;
    }
  else
    return SETCURSOR_NONE ;
  }

BOOL EnterCont::OnMouseMove (WPARAM wP,int xl,int yl,int Seite)
  {
  if (!IsImage ()) return FALSE ;
  if (wP == MK_LBUTTON) {
    if (cnt == NULL) {
      cnt = (LogPt FAR *) GetGlobMem (sizeof(LogPt));
      to.cInd = 0;
      PtCount = 1;
      }
    if (to.cInd < 0) {
      EnlargeCont (to.iInd);
      to.cInd = (to.iInd < 0) ? PtCount - 1 : to.iInd;
      }
//    cnt[to.cInd].x = xl , cnt[to.cInd].y = yl ;
    PaintContext pc(m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
    ptb.Restore (&pc);
    ptb.ReadBackground (&pc,m_scale(),m.xp(),m.yp(),xl,yl);
    pc.Attrib (PENDATA (RGB(0xFF,0,0)));
    pc.LogicalTwips (m.xp(),m.yp(),m_scale());
    PaintRect (&pc,xl,yl);
    return TRUE ;
    }
  else {
    if (wP == 0) {
      if (to.ActIObj != NULL)
        to.ActIObj->SetName ();
      else
        SetName ();
      }
    return FALSE ;
    }
  }

BOOL EnterPoint::OnMouseMove (WPARAM wP,int xl,int yl,int Seite)
  {
  if (!IsImage ()) return FALSE ;
  if (wP == MK_LBUTTON) {
    PaintContext pc(m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
    ptb.Restore (&pc);
    ptb.ReadBackground (&pc,m_scale(),m.xp(),m.yp(),xl,yl);
    pc.Attrib (PENDATA (RGB(0xFF,0,0)));
    pc.LogicalTwips (m.xp(),m.yp(),m_scale());
    PaintRect (&pc,xl,yl);
    return TRUE ;
    }
  else {
    if (wP == 0) {
      if (to.ActIObj != NULL)
        to.ActIObj->SetName ();
      else
        SetName ();
      }
    return FALSE ;
    }
  }

BOOL EnterPoint::OnKeyDown (WORD wP,int Seite)
  {
  if (((wP == VK_F2) || (wP == VK_DELETE)) && (!to.IsInEnter())) {
    if ((to.ActIObj == NULL) || (to.ActIObj == this)) {
      // Punkt loeschen (nur wenn wirklich eingegeben...)
      DBBOOL FAR *stflag = (DBBOOL FAR *) m.ReadlData (Par()->SetOnStore);
      if (((stflag != NULL) && (*stflag)) || (LOWORD(Par()->SetOnStore) == 0)) {
        Invalidate (Seite);
        MessageBeep (0);
        m.DellData (Par()->Cntpt,LPSTR(ScriptParam)-sizeof(WORD));
        // Vermerken, dass Punkt nicht digitaliert ist
        m.DellData(Par()->SetOnStore,LPSTR(ScriptParam)-sizeof(WORD));
        ResetData ();
        }
      return TRUE ;
      }
    else {
      m.SetActiveExplicit (to.ActIObj);
      return to.ActIObj->OnKeyDown (wP,Seite);
      }
    }
  else
    return FALSE ;
  }

BOOL EnterCont::OnKeyDown (WORD wP,int Seite)
  {
  if (((wP == VK_F2) || (wP == VK_DELETE)) && (!to.IsInEnter())) {
    if ((to.ActIObj == NULL) || (to.ActIObj == this)) {
      Invalidate (Seite);
      if ((to.ActIObj == this) && (to.cInd >= 0) && (PtCount > 1)) {
        // Punkt loeschen
        LogPt FAR *ncnt = (LogPt FAR *) 
              GetGlobMem (sizeof(LogPt) * (PtCount - 1));
        int j = 0 ;
        for (WORD i = 0 ; i < PtCount ; i++) {
          if (i == WORD(to.cInd)) continue ;
          ncnt[j++] = cnt[i] ;
          }
        FreeGlobMem (cnt) ;
        cnt = ncnt ;
        PtCount -= 1 ;
        GetZCont ();
        GetMinMax ();
        Invalidate (Seite);
        GLOBALHANDLE hGmem = GlobalAlloc (GHND,sizeof(fpt)*PtCount+sizeof(WORD));
        LPSTR Buffer = LPSTR(GlobalLock (hGmem));
        *(WORD FAR *) Buffer = sizeof(fpt) * PtCount + sizeof (WORD);
        fpt FAR *res = (fpt FAR *) (Buffer + sizeof(WORD));
        for (i = 0 ; i < PtCount ; i++) {
          res[i].x = m_LogToWorld (cnt[i].x);
          res[i].y = m_LogToWorld (cnt[i].y);
          }
        GlobalUnlock (hGmem);
        OnDigitized (WMU_DIGITIZED,hGmem);
        to.Reset ();
        }
      else {
        // Ganze Kontur loeschen
        MessageBeep (0);
        m.DellData (Par()->Cntpt,LPSTR(ScriptParam)-sizeof(WORD));
        // Vermerken, dass Kontur nicht digitaliert ist
        m.DellData(Par()->SetOnStore,LPSTR(ScriptParam)-sizeof(WORD));
        ResetData ();
        }
      return TRUE ;
      }
    else {
      m.SetActiveExplicit (to.ActIObj);
      return to.ActIObj->OnKeyDown (wP,Seite);
      }
    }
  else
    return FALSE ;
  }
