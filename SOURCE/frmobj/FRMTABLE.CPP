//  Implementierung der Objekte (speziell fuer Form)
//
/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/frmtable.cpv   1.7   10 Jun 1996 10:12:42   GERHOLD  $
// $Log:   P:/marille/clinicum/frmobj/rev/frmtable.cpv  $
// 
//    Rev 1.7   10 Jun 1996 10:12:42   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.6   27 Mar 1996 18:05:30   MARTIN
// ParamBlock.AnzPars
// 
//    Rev 1.5   24 Mar 1996 12:12:00   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:49:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   24 Aug 1995 00:15:12   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.2   11 Jun 1995 10:05:18   HANNES
// 
//    Rev 1.1   20 Mar 1995 12:14:26   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   06 Oct 1994 19:28:08   HANNES
// Initial revision.
// 
//    Rev 1.5   22 Sep 1994 16:10:38   GERHOLD
// Callbackfunktionen fuer Farbaenderung in der ObjList (GetSysColor)
// 
//    Rev 1.4   20 Sep 1994 11:24:48   HANNES
// Trc_DefFilledCont
// 
//    Rev 1.3   09 Aug 1994 09:31:36   HANNES
// FrmTime
// 
//    Rev 1.2   25 Jul 1994 18:12:28   HANNES
// SetButtonField
// 
//    Rev 1.1   27 Jun 1994 11:00:52   MARTIN
// exportierte virtuelle Funktionen nicht mehr inline
// 
//    Rev 1.0   24 Jun 1994 16:45:42   MARTIN
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#define CARETHANDLING_DONE
#include "globmem.h"
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#define MODULENUM     130
#include "winass.hpp"

#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "voronoi.hpp"
#include "frmobj.hpp"

#define FRMTABLE_MAIN
#include "frmtable.hpp"

BOOL FrmTable_Param::AnalyseStruct (dllChild FAR *m,LPACCESSDEF FAR &spa,LPACCESSDEF FAR &za,LPACCESSDEF FAR &zellena,
                    LPCELLKEYDEF FAR &spk,LPCELLKEYDEF FAR &zk)
  {
  spa = LPACCESSDEF (gd.NextStruct(m));
  za = LPACCESSDEF (spa->NextStruct(m));
  zellena = LPACCESSDEF (za->NextStruct(m));
  spk = LPCELLKEYDEF (zellena->NextStruct(m));
  zk = LPCELLKEYDEF (spk->NextStruct(m));
  LPSTR NextCommand = LPSTR(this) + hd.par_Size;
  return (NextCommand == LPSTR(zk->NextStruct(m)));
  }

///////////////////////////////////////////////////////////////////////
//  Implementierung CLineDef
///////////////////////////////////////////////////////////////////////
CLineDef::CLineDef (LPSTR t,WORD f,DWORD c,WORD ty,int w,int AnzLines,dllChild FAR *m)
  {
  DBWIN_ASSERT (t != NULL);
  Text = LPSTR (GetGlobMem (lstrlen(t)+1));
  lstrcpy (Text,t) ;

  Format = f;
  Color = c;
  Type = ty;

  fld = new cField (TRANSPARENT,Format,0,0,w,AnzLines,FALSE);
  fld->SetWindow (m->MyHandle());
  int MapType;
  m->GetDocInfo (GETMAPTYPE,0,&MapType);
  fld->SetScale (m__scale(),MapType);
  fld->SetVOrg (m->xp(),m->yp(), 0);
  fld->SetOutColor (c);
  if (MapType == MAPTYPE_GEOMETRIC) {
    POINT pt;
    m->GetDocInfo (GETWINDOWORG,0,&pt);
    fld->SetWOrg (pt.x,pt.y);
    }
  *fld = Text;

  Next = NULL;
  }

int CLineDef::Height(dllChild FAR *m)
  {
  int MapType;
  m->GetDocInfo (GETMAPTYPE,0,&MapType);
  LPFORMATMETRIC lpfm = GetFormatMetrics (m->MyHandle(),Format,0);
  return lpfm->yHeight;
  }

int CLineDef::LineHeight()
  {
  RECT r;
  fld->GetFieldRect (&r,0);
  return r.bottom - r.top;
  }

CLineDef::~CLineDef ()
  {
  FreeGlobMem (Text);
  delete fld;
  }

void CLineDef::StartExternPaint ()
  {
  fld->StartExternPaint ();
  }

void CLineDef::EndExternPaint ()
  {
  fld->EndExternPaint ();
  }

void CLineDef::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  fld->SetScale (scale,MapType);
  fld->SetVOrg (xp,yp,0);
  fld->SetWOrg (x0,y0);
  }

void CLineDef::Paint (PaintContext *pc)
  {
  if (pc->mode == DO_EXTERN)
    fld->PaintToMeta (pc->hDC);
  else
    fld->Paint (pc->hDC,0,(pc->mode == DO_PRINT));
  }

///////////////////////////////////////////////////////////////////////
//  Implementierung CellDef
///////////////////////////////////////////////////////////////////////
CellDef::~CellDef ()
  {
  for ( ; cd != NULL ; ) {
    LPCLINEDEF next = cd->Next ;
    delete cd ;
    cd = next ;
    }
  if (IsOuterCell)
    delete more.OuterCell.k ;
  }

void CellDef::StartExternPaint ()
  {
  for ( LPCLINEDEF line = cd ; line != NULL ; line = line->Next ) {
    line->StartExternPaint ();
    }
  }

void CellDef::EndExternPaint ()
  {
  for ( LPCLINEDEF line = cd ; line != NULL ; line = line->Next ) {
    line->EndExternPaint ();
    }
  }

void CellDef::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  for ( LPCLINEDEF line = cd ; line != NULL ; line = line->Next ) {
    line->OnMapChange (scale,MapType,xp,yp,x0,y0);
    }
  }

void CellDef::Paint (PaintContext *pc)
  {
  for ( LPCLINEDEF line = cd ; line != NULL ; line = line->Next ) {
    line->Paint (pc);
    }
  }

void CellDef::CellUnionRect (LPRECT r,BOOL FAR *first)
  {
  RECT mr;
  mr.left = x;
  mr.top = y;
  mr.right = x + w ;
  mr.bottom = y + h ;

  if (*first)
    CopyRect (r,&mr);
  else
    UnionRect (r,r,&mr);
  *first = FALSE ;
  }

int CellDef::Height ()
  {
  int res = 2 * TYSPACING ;
  for (LPCLINEDEF h = cd ; h != NULL ; h = h->Next)
    res += h->LineHeight ();
  return res;
  }

void CellDef::SetPos (int px,int py,int ph)
  {
  x = px , y = py , h = ph ;
  POINT pt;
  pt.x = x + TXSPACING ;
  pt.y = y + TYSPACING ;
  for (LPCLINEDEF h = cd ; h != NULL ; h = h->Next) {
    *(h->fld) = pt ;
    pt.y += h->LineHeight();
    }
  }

///////////////////////////////////////////////////////////////////////
//  Implementierung FrmTable
///////////////////////////////////////////////////////////////////////
DLLExport _export WINAPI FrmTable::FrmTable (LPVOID p,mdiChild *mc) : 
      FrmObject (p,mc)
  {

  }

void FrmTable::Destroy ()
  {
  for ( ; LeftUpper != NULL ; ) {
    LPCELLDEF Down = LeftUpper->Down ;
    for ( ; LeftUpper != NULL ; ) {
      LPCELLDEF Right = LeftUpper->Right ;
      delete LeftUpper ;
      LeftUpper = Right ;
      }
    LeftUpper = Down ;
    }
  RightUpper = LeftLower = NULL;
  }

DLLExport _export WINAPI FrmTable::~FrmTable ()
  {
  Destroy ();
  }

DLLExport void _export WINAPI FrmTable::Reset (BOOL doClear)
  {
  Destroy ();
  }

DLLExport void _export WINAPI FrmTable::StartExternPaint ()
  {
  for ( LPCELLDEF zeile = LeftUpper ; zeile != NULL ; zeile = zeile->Down ) {
    for ( LPCELLDEF zelle = zeile ; zelle != NULL ; zelle = zelle->Right) {
      zelle->StartExternPaint ();
      }
    }
  }

DLLExport void _export WINAPI FrmTable::EndExternPaint ()
  {
  for ( LPCELLDEF zeile = LeftUpper ; zeile != NULL ; zeile = zeile->Down ) {
    for ( LPCELLDEF zelle = zeile ; zelle != NULL ; zelle = zelle->Right) {
      zelle->EndExternPaint ();
      }
    }
  }

DLLExport void _export WINAPI FrmTable::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  for ( LPCELLDEF zeile = LeftUpper ; zeile != NULL ; zeile = zeile->Down ) {
    for ( LPCELLDEF zelle = zeile ; zelle != NULL ; zelle = zelle->Right) {
      zelle->OnMapChange (scale,MapType,xp,yp,x0,y0);
      }
    }
  }

DLLExport void _export WINAPI FrmTable::Paint (PaintContext *pc,int Seite)
  {
  for ( LPCELLDEF zeile = LeftUpper ; zeile != NULL ; zeile = zeile->Down ) {
    for ( LPCELLDEF zelle = zeile ; zelle != NULL ; zelle = zelle->Right) {
      zelle->Paint (pc);
      }
    }

  // Zeichnen des Gitters
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }

DLLExport void _export WINAPI FrmTable::GetMinMax ()
  {
  if (Initialized) {
    BOOL first = TRUE ;
    RECT rcLogRect ;
    SetRectEmpty (&rcLogRect);
    for ( LPCELLDEF zeile = LeftUpper ; zeile != NULL ; zeile = zeile->Down ) {
      for ( LPCELLDEF zelle = zeile ; zelle != NULL ; zelle = zelle->Right) {
        zelle->CellUnionRect (LPRECT(&rcLogRect),&first);
        }
      }
    InflateRect (LPRECT(&rcLogRect),100,100);   // Um die Halben Stiftbreiten
                                                // kuemmern wir uns hier einmal
                                                // nicht
    SetLogRect (&rcLogRect,ErsteSeite());
    }
  }

LPPARAM FrmTable::GetLPParams(LPACCESSDEF a,LPPARAM p)
  {
  int AnzParams = m.GetConstInt (a->rAnzParams);
  if (AnzParams == 0)
    return NULL;
  else {
    lmemset (p,'\0',sizeof(*p));
    for (int i = 0 ; i < AnzParams ; i++)
      p->ptr[i] = m.ReadlData (a->Par[i]);
    p->AnzPars = AnzParams;
    return p;
    }
  }

DBList FAR *FrmTable::GetList (LPACCESSDEF a,WORD FAR *TableInd,LPTABLEDEF FAR *tb)
  {
  LPSTR SelectionName = LPSTR (m.ReadlData (a->SelectionName));
  LPSTR TableName = LPSTR (m.ReadlData (a->TableName));

  ParamBlock p;
  DBList FAR *res = new DBList (*tb = m.GetTableDef(TableName,TableInd),
                             m.DocumentID(),
                             SelectionName,
                             -1,
                             -1,
                             GetLPParams(a,&p),
                             FALSE
                            );
  return res;
  }

void FrmTable::InitializeLeftUpper (int w)
  {
  LeftUpper = new CellDef ();
  RightUpper = LeftLower = LeftUpper ;
  LeftUpper->w = w;
  }

LPSTR FrmTable::ReadText ()
  {
  LPSTR res = LPSTR(m.ReadlData (Par()->Text));
  DBWIN_ASSERT (res != NULL);
  return res;
  }

WORD FrmTable::ReadFormat ()
  {
  WORD FAR *lpFormat = (WORD FAR *) m.ReadlData (Par()->TextFormat);
  DBWIN_ASSERT (lpFormat != NULL);
  return *lpFormat;
  }

WORD FrmTable::ReadType ()
  {
  WORD FAR *lpType = (WORD FAR *) m.ReadlData (Par()->TextType);
  DBWIN_ASSERT (lpType != NULL);
  return *lpType;
  }

DWORD FrmTable::ReadColor ()
  {
  DWORD FAR *lpColor = (DWORD FAR *) m.ReadlData (Par()->TextColor);
  DBWIN_ASSERT (lpColor != NULL);
  return *lpColor;
  }

int FrmTable::ReadWidth ()
  {
  DBINT FAR *lpWidth = (DBINT FAR *) m.ReadlData (Par()->Width);
  DBWIN_ASSERT (lpWidth != NULL);
  return *lpWidth;
  }

void FrmTable::HaengeSpalteAn (LPPRIMKEY k,LPSTR Text,WORD Format,DWORD Color,WORD Type,int Width)
  {
  LPCELLDEF h = new CellDef ();
  h->w = Width;
  h->cd = new CLineDef (Text,Format,Color,Type,Width - 2 * TXSPACING,-1,&m);
  h->more.OuterCell.k = new PrimKey ;
  *(h->more.OuterCell.k) = *k ;
  h->IsOuterCell = TRUE ;
  h->Left = RightUpper;
  RightUpper->Right = h;
  RightUpper = h;
  }

void FrmTable::HaengeZeileAn (LPPRIMKEY k,LPSTR Text,WORD Format,DWORD Color,WORD Type)
  {
  LPCELLDEF h = new CellDef ();
  h->cd = new CLineDef (Text,Format,Color,Type,LeftUpper->w - 2 * TXSPACING,1,&m);
  h->Up = LeftLower;
  h->more.OuterCell.k = new PrimKey ;
  *(h->more.OuterCell.k) = *k ;
  h->IsOuterCell = TRUE ;
  h->w = LeftUpper->w ;
  LeftLower->Down = h;
  LeftLower = h;
  }

void FrmTable::CreateEmptyCells ()
  {
  for (LPCELLDEF z = LeftUpper->Down ; z != NULL ; z = z->Down) {
    LPCELLDEF o = z->Up->Right;
    LPCELLDEF p = z;
    for ( LPCELLDEF s = LeftUpper->Right ; o != NULL ; o = o->Right , s = s->Right) {
      LPCELLDEF c = new CellDef ();
      c->w = o->w;
      c->Left = p;
      c->Up = o;
      o->Down = c;
      p->Right = c;
      c->more.InnerCell.FirstOfLine   = z ;
      c->more.InnerCell.FirstOfColumn = s ;
      p = c ;
      }
    }
  }

LPPRIMKEY FrmTable::LeseSpaltenSchluessel (LPCELLKEYDEF k)
  {
  int AnzKeySegs = m.GetConstInt (k->rAnzKeySegs);
  LPPRIMKEY key = new PrimKey ();
  for (int i = 0 ; i < int (AnzKeySegs) ; i++) {
    LPVOID d = m.ReadlData (k->Key[i]);
    DBWIN_ASSERT (d != NULL);
    key->PushKeySeg (d,GetBlockSize(d));
    }
  return key;
  }

void FrmTable::HaengeEintragAnZelle (LPPRIMKEY ks,LPPRIMKEY kz,LPSTR Text,WORD Format,DWORD Color,WORD Type)
  {
  for (LPCELLDEF z = LeftUpper->Down ; z != NULL ; z = z->Down) {
    if (*(z->more.OuterCell.k) == *kz) {
      for (LPCELLDEF x = z->Right ; x != NULL ; x = x->Right) {
        if (*(x->more.InnerCell.FirstOfColumn->more.OuterCell.k) == *ks) {
          // Zelle gefunden
          LPCLINEDEF h = new CLineDef (Text,Format,Color,Type,x->w - 2 * TXSPACING,1,&m);
          if (x->cd == NULL) x->cd = h ;
          else {
            for (LPCLINEDEF p = x->cd ; p->Next != NULL ; p = p->Next) ;
            p->Next = h;
            }
          return ;
          }
        }
      DBWIN_ASSERT(FALSE);
      }
    }
  DBWIN_ASSERT (FALSE);
  }

void FrmTable::SetPos (LPPOINT pt)
  {
  for ( LPCELLDEF z = LeftUpper ; z != NULL ; z = z->Down ) {
    // Ermitteln der Zeilenhoehe
    int h = 0;
    for (LPCELLDEF s = z ; s != NULL ; s = s->Right) {
      int ah = s->Height();
      if (ah > h) h = ah ;
      }
    // Die Zeile Positionieren
    int x = pt->x ;
    for (s = z ; s != NULL ; s = s->Right) {
      s->SetPos (x,pt->y,h);
      x += s->w ;
      }
    // Naechste Zeile
    pt->y += h;
    }
  }

void FrmTable::GetOrg (LPPOINT pt)
  {
  fpt FAR *ptOrg = (fpt FAR *) m.ReadlData (Par()->ptOrg);
  DBWIN_ASSERT (ptOrg != NULL);
  pt->x = m.WorldToLog (ptOrg->x);
  pt->y = m.WorldToLog (ptOrg->y);
  WORD MappingType;
  m.GetDocInfo (GETMAPTYPE,0,&MappingType);
  DBINT FAR *lpx = (DBINT FAR *) m.ReadlData (Par()->rx0);
  DBINT FAR *lpy = (DBINT FAR *) m.ReadlData (Par()->ry0);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL)) ;
  if (MappingType == MAPTYPE_GEOMETRIC) {
    pt->x += *lpx / 4 ,
    pt->y += *lpy / 4 ;
    }
  else {
    pt->x += *lpx ,
    pt->y += *lpy ;
    }
  }

DLLExport void _export WINAPI FrmTable::Load ()
  {
  LPACCESSDEF zz,sz,cz;
  LPCELLKEYDEF ckz,cks;
  DBWIN_ASSERT (Par()->AnalyseStruct(&m,sz,zz,cz,cks,ckz));

  // Initialisieren der Linken oberen Spalte
  int w0 = m.GetConstInt (Par()->rw0);
  InitializeLeftUpper (w0);

  DBList FAR *l;
  WORD TableInd;
  LPTABLEDEF tb;

  // Laden der Spalten
  l = GetList (sz,&TableInd,&tb);
  for (LPDBRECORD r = l->GetFirst() ; r != NULL ; r = l->GetNext(r)) {
    LPDBRECORD old = m.SetRecord (r,TableInd);
    m.ExCuteProc (sz->AnalyseProc,EM_LOAD | EM_CHANGETOTRUE);
    m.ExCuteProc (sz->AnalyseProc,EM_RESET);
    HaengeSpalteAn (r->GetPrimKey(),ReadText(),ReadFormat(),ReadColor(),ReadType(),ReadWidth());
    m.SetRecord (old,TableInd);
    }
  delete l;
  m.FreeTableDef (tb);

  // Laden der Zeilen
  l = GetList (zz,&TableInd,&tb);
  for (r = l->GetFirst() ; r != NULL ; r = l->GetNext(r)) {
    LPDBRECORD old = m.SetRecord (r,TableInd);
    m.ExCuteProc (zz->AnalyseProc,EM_LOAD | EM_CHANGETOTRUE);
    m.ExCuteProc (zz->AnalyseProc,EM_RESET);
    HaengeZeileAn (r->GetPrimKey(),ReadText(),ReadFormat(),ReadColor(),ReadType());
    m.SetRecord (old,TableInd);
    }
  delete l;
  m.FreeTableDef (tb);

  // Erzeugen der leeren Zellen
  CreateEmptyCells ();

  // Laden der Zellen
  l = GetList (cz,&TableInd,&tb);
  for (r = l->GetFirst() ; r != NULL ; r = l->GetNext(r)) {
    LPDBRECORD old = m.SetRecord (r,TableInd);
    m.ExCuteProc (cz->AnalyseProc,EM_LOAD | EM_CHANGETOTRUE);
    m.ExCuteProc (cz->AnalyseProc,EM_RESET);
    LPSTR Text = ReadText ();
    if (Text != NULL) {
      LPPRIMKEY ks = LeseSpaltenSchluessel (cks);
      LPPRIMKEY kz = LeseSpaltenSchluessel (ckz);
      HaengeEintragAnZelle (ks,kz,Text,ReadFormat(),ReadColor(),ReadType());
      delete ks;
      delete kz;
      }
    m.SetRecord (old,TableInd);
    }
  delete l;
  m.FreeTableDef (tb);

  // Position des linken oberen Eckes
  POINT pt;
  GetOrg (&pt);

  // Positionsgebung
  SetPos (&pt);

  // fertig
  Initialized = TRUE;
  }

