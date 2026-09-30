////////////////////////////////////////////////////////////////
//  Loesen des Vornoi - Diagrammes
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/voronoi.cpv   1.3   05 Oct 1998 11:17:50   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/voronoi.cpv  $
// 
//    Rev 1.3   05 Oct 1998 11:17:50   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.2   18 Aug 1997 18:05:04   Martin
// VTO Formular-faehig
// 
//    Rev 1.1   02 Feb 1996 10:46:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:49:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   20 Jan 1994 23:55:40   HANNES
// Den nur bedingt sinnvollen WIN_ASSERT auf 1178 rausgehaut
// 
//    Rev 1.4   23 Nov 1993 20:28:18   HANNES
// 
//    Rev 1.3   15 Nov 1993 11:28:10   HANNES
// 
//    Rev 1.2   03 Nov 1993 17:46:26   HANNES
// Zwischenversion
// 
//    Rev 1.1   02 Nov 1993 11:08:24   HANNES
// Zwischenversion
// 
//    Rev 1.0   28 Oct 1993 08:48:44   HANNES
// Initial revision.
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#define MODULENUM   55
#include "winass.hpp"
#define JUST_EM
#include "dds.hpp"
#include "sc2d.hpp"
#include "voronoi.hpp"

#define HUGE  float(1.0E20)
#define HUGE2 float(1.0E21)

BOOL Voronoi::TestPtRightOnLine (int i,int i0,int i1)
  {
  // Punkt i rechts der Linie i0,i1 ?
  double dx = pts[i].x - pts[i0].x ;
  double dy = pts[i].y - pts[i0].y ;
  double dx1 = pts[i1].x - pts[i0].x ;
  double dy1 = pts[i1].y - pts[i0].y ;
  return ((dx * dy1 - dx1 * dy) >= -1.0E-5);
  }

BOOL Voronoi::TestPtRight (int i,int i0,int i1)
  {
  // Punkt i rechts der Linie i0,i1 ?
  double dx = pts[i].x - pts[i0].x ;
  double dy = pts[i].y - pts[i0].y ;
  double dx1 = pts[i1].x - pts[i0].x ;
  double dy1 = pts[i1].y - pts[i0].y ;
  return ((dx * dy1 - dx1 * dy) >= 1.0E-5);
  }

BOOL Voronoi::TestPtOnLine (int i,int i0,int i1)
  {
  // Punkt i rechts der Linie i0,i1 ?
  double dx = pts[i].x - pts[i0].x ;
  double dy = pts[i].y - pts[i0].y ;
  double dx1 = pts[i1].x - pts[i0].x ;
  double dy1 = pts[i1].y - pts[i0].y ;
  double exprod = (dx * dy1 - dx1 * dy);
  return ((exprod >= -1.0E-5) && (exprod <= 1.0E-5));
  }

LPCPT Voronoi::AtomicConvex (int min,int max)
  {
  LPCPT c2 = LPCPT (GetGlobMem (sizeof(*c2)));
  LPCPT c1 = LPCPT (GetGlobMem (sizeof(*c1)));
  LPCPT ce = LPCPT (GetGlobMem (sizeof(*ce)));

  ce->pi = pind[min];
  ce->Next = NULL ;
  c1->pi = pind[min];
  c1->Next = c2 ;

  if ((max - min) == 1) {
    // Linie
    c2->pi = pind[max];
    c2->Next = ce ;
    }
  else if ((max - min) == 2) {
    // Dreieck
    LPCPT c3 = LPCPT (GetGlobMem (sizeof(*c3)));
    c2->Next = c3 ;
    c3->Next = ce ;
    if (TestPtRight (pind[min+1],pind[min],pind[max])) {
      c2->pi = pind[min+1];
      c3->pi = pind[max];
      }
    else if (!TestPtOnLine (pind[min+1],pind[min],pind[max])) {
      c2->pi = pind[max];
      c3->pi = pind[min+1];
      }
    else {
      // Punkt min+1 liegt auf der Linie, -> Punkt doppelt aufnehmen
      LPCPT c4 = LPCPT (GetGlobMem (sizeof(*c4)));
      c4->Next = ce ;
      c3->Next = c4 ;
      c2->pi = pind[min+1];
      c3->pi = pind[max];
      c4->pi = pind[min+1];
      }
    }
  else
    WIN_ASSERT(FALSE);
  return c1 ;
  }

LPCPT Voronoi::UnionConvex (LPCPT c1,LPCPT c2)
  {
  // Suchen der Unteren Umrandung ...
  LPCPT res = c1 ;
  for ( ; ; c1 = c1->Next) {
    for ( ; ((c2->Next != NULL) && 
                        (TestPtRight(c2->Next->pi,c1->pi,c2->pi))) ; ) {
      LPCPT n = c2->Next ;
      FreeGlobMem (c2) ;
      c2 = n ;
      }
    double dx = double (pts[c2->pi].x - pts[c1->pi].x) ;
    double dy = double (pts[c2->pi].y - pts[c1->pi].y) ;
    double dx1 = double (pts[c2->pi].x - pts[c1->Next->pi].x);
    if (c1->Next == NULL) break ;
    if ((TestPtOnLine (c1->Next->pi,c1->pi,c2->pi)) && 
         ((dx1 < dx) ||
          ((dx1 == dx) && (double (pts[c2->pi].y - pts[c1->Next->pi].y) < dy)))) 
      continue ;
    if (!TestPtRight (c1->Next->pi,c1->pi,c2->pi))
      break ;
    }
  LPCPT c1last = c1 ;       // Zum schluss: c1last = c2 ;
  WIN_ASSERT (c1last->Next != NULL) ;
  LPCPT c2first = c2 ;

  // Untersuchen, on Punkt verdoppelt werden muss
  if (TestPtOnLine (c1->pi,c1->Next->pi,c2first->pi)) {
    c1 = LPCPT (GetGlobMem (sizeof(*c1)));
    c1->pi = c1last->pi;
    c1->Next = c1last->Next;
    c1last->Next = c1 ;
    }
  else
    c1 = c1->Next;

  // Suchen der oberen Umrandung
  for ( ; ; c2 = c2->Next) {
    for ( ; ((c1->Next != NULL) &&
                (TestPtRight(c1->Next->pi,c2->pi,c1->pi))) ; ) {
      c1last->Next = c1->Next ;
      FreeGlobMem (c1);
      c1 = c1last->Next ;
      }
    double dx = double (pts[c2->pi].x - pts[c1->pi].x) ;
    if ((c2->Next == NULL) || (!TestPtRightOnLine (c2->Next->pi,c2->pi,c1->pi)))
      break ;
    }
  LPCPT c2last = c2 ;

  // Loeschen der noch verbleibenden Punkte
  for ( c2 = c2->Next ; c2 != NULL ; ) {
    LPCPT n = c2->Next ;
    FreeGlobMem (c2) ;
    c2 = n ;
    }

//  if (TestPtOnLine (c1last->pi,c1last->Next->pi,c2first->pi)) {
    // Punkt c1last muss verdoppelt werden
//    LPCPT cn = LPCPT (GetGlobMem (sizeof(*cn)));
//    cn->pi   = c1last->pi;
//    cn->Next = c1 ;
//    c2last->Next = cn ;
//    }
//  else
    c2last->Next = c1 ;
  // Herstellen der endgueltigen Verkettung
  c1last->Next = c2first ;
  return res ;
  }

LPCPT Voronoi::GetConvexList (int min,int max)
  {
  LPCPT res ;
  if ((max - min) < 3) {
    // Menge < 3 Punkte -> Huelle erzeugen
    res = AtomicConvex (min,max);
    }
  else {
    LPCPT c1 = GetConvexList (min,(max + min) / 2);
    LPCPT c2 = GetConvexList ((max + min) / 2 + 1,max);
    res = UnionConvex (c1,c2);
    }
  return res ;
  }

void Voronoi::CompleteConvex (LPCPT start)
  {
  LPCPT prev = NULL ;
  for ( LPCPT h = start ; h != NULL ; h = h->Next) {
    h->Prev = prev ;
    prev = h ;
    }
  // Schliessen (wobei der letzte punkt ausgelassen wird)
  LPCPT c = prev;
  h = prev->Prev ;
  h->Next = start ;
  start->Prev = h ;
  FreeGlobMem (c);
  }

DLLExport void _export WINAPI Voronoi::PaintConvexList (HDC hDC)
  {
  HPEN hOldPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,1,RGB(0x80,0,0)));
  if (clist != NULL) {
    int x = int (pts[clist->pi].x);
    int y = int (pts[clist->pi].y);
    MoveToEx (hDC,x-11,y-11, NULL);
    LineTo (hDC,x-11,y+11);
    LineTo (hDC,x+11,y+11);
    LineTo (hDC,x+11,y-11);
    LineTo (hDC,x-11,y-11);
    MoveToEx (hDC,int (pts[clist->pi].x),int (pts[clist->pi].y), NULL);
    for ( LPCPT h = clist->Next ; ; h = h->Next) {
      LineTo (hDC,x = int (pts[h->pi].x),y = int (pts[h->pi].y));
      MoveToEx (hDC,x-11,y-11, NULL);
      LineTo (hDC,x-11,y+11);
      LineTo (hDC,x+11,y+11);
      LineTo (hDC,x+11,y-11);
      LineTo (hDC,x-11,y-11);
      MoveToEx (hDC,x,y, NULL);
      if (h == clist) break ;
      }
    }
  DeleteObject (SelectObject (hDC,hOldPen));
  }

static class Voronoi FAR *actV;
void Voronoi::StartCalculations ()
  {
  WIN_ASSERT (actV == NULL);
  actV = this;
  }

void Voronoi::EndCalculations ()
  {
  actV = NULL;
  }

inline void Chg(int FAR &i1,int FAR &i2)
  {
  int dummy = i1 ;
  i1 = i2 ;
  i2 = dummy;
  }

void Voronoi::PushToTB (int i)
  {
  WIN_ASSERT (TriangBufferCount < (MAXTRIANGS + 1)) ;
  TriangBuffer[TriangBufferCount++] = i ;
  }

inline int getrandom(int mn,int mx) 
  {
  return ((rand() % (int)(((mx)+1) - (mn))) + (mn)) ;
  }

/*---- Sortieren der Punkte nach steigendem x ----*/
void Voronoi::QuickSort (int Low,int High)
  {
  int Up, Down;
  float xBreak,yBreak;

  if (Low < High) {
    if ((High - Low) == 1) {
      if ((pts[pind[Low]].x > pts[pind[High]].x) || 
          ((pts[pind[Low]].x == pts[pind[High]].x) && 
           (pts[pind[Low]].y > pts[pind[High]].y)))
        Chg (pind[Low],pind[High]);
      }
    else {
      Chg (pind[High],pind[getrandom(Low,High)]);
      xBreak = pts[pind[High]].x ;
      yBreak = pts[pind[High]].y ;
      do {
        Up = Low;
        Down = High;
        while ((Up < Down) &&
                 ((pts[pind[Up]].x < xBreak) ||
                  ((pts[pind[Up]].x == xBreak) &&
                   (pts[pind[Up]].y <= yBreak))))
          Up++;
        while ((Down > Up) &&
                 ((pts[pind[Down]].x > xBreak) || 
                  ((pts[pind[Down]].x == xBreak) &&
                   (pts[pind[Down]].y >= yBreak))))
          Down--;
        if (Up < Down)
          Chg(pind[Up],pind[Down]);
        } while (Up < Down);

      Chg (pind[Up],pind[High]);

      if ((Up - Low) < (High - Up)) {
        QuickSort( Low, Up - 1 );
        QuickSort( Up + 1, High );
        }
      else {
        QuickSort( Up + 1, High );
        QuickSort( Low, Up - 1 );
        }
      }
    }
  }

Triang::Triang (int i1,int i2,int i3)
  {
  lmemset (this,'\0',sizeof(this));
  if (i2 < i1)
    Chg(i1,i2);
  if (i3 < i1)
    Chg(i1,i3);
  if (i3 < i2)
    Chg(i2,i3);
  p1 = i1 ;
  p2 = i2 ;
  p3 = i3 ;
  }

DLLExport LPVOID _export WINAPI Voronoi::operator new (size_t size)
  { 
  return GetGlobMem (size); 
  }

DLLExport void _export WINAPI Voronoi::operator delete (LPVOID obj)
  { 
  FreeGlobMem (obj) ; 
  }

DLLExport _export WINAPI Voronoi::Voronoi (fpt FAR *p,int Anz)
  { 
  pts = p ; AnzPts = Anz ; AnzOrgPts = Anz ;
  pind = (int FAR *) GetGlobMem (sizeof(int) * Anz) ;
  TriangsfromPt = (LPINT FAR *) 
      GetGlobMem (Anz * sizeof(LPINT)) ;
  StartCalculations ();
  }

DLLExport _export WINAPI Voronoi::~Voronoi ()
  { 
  if (hGTriangMem) 
    GlobalUnlock (hGTriangMem) , GlobalFree (hGTriangMem) ; 
  if (pind != NULL)
    FreeGlobMem (pind) ;
  if (TriangsfromPt != NULL) {
    for (int i = 0 ; i < AnzOrgPts ; i++) {
      if (TriangsfromPt[i] != NULL)
        FreeGlobMem (TriangsfromPt[i]);
      }
    FreeGlobMem (TriangsfromPt);
    }
  if (segstart != NULL)
    FreeGlobMem (segstart);
  if (rvpind != NULL)
    FreeGlobMem (rvpind);
  EndCalculations ();
  for ( ; exr != NULL ; ) {
    ExtRange FAR *exn = exr->Next ;
    delete exr ;
    exr = exn ;
    }
  if (TriangsfromSection != NULL) {
    for (int ind = 0 ; ind < ANZSEGS * ANZSEGS ; ind++) {
      if (TriangsfromSection[ind] != NULL)
        FreeGlobMem (TriangsfromSection[ind]);
      }
    FreeGlobMem (TriangsfromSection);
    }
  }

DLLExport void _export WINAPI Voronoi::RemoveAnalyseMem ()
  {
  if (TriangsfromPt != NULL) {
    for (int i = 0 ; i < AnzOrgPts ; i++) {
      if (TriangsfromPt[i] != NULL)
        FreeGlobMem (TriangsfromPt[i]);
      }
    FreeGlobMem (TriangsfromPt);
    TriangsfromPt = NULL ;
    }
  if (segstart != NULL)
    FreeGlobMem (segstart) , segstart = NULL ;
  if (rvpind != NULL)
    FreeGlobMem (rvpind) , rvpind = NULL ;
  }

void Voronoi::PushTriangToPt (int trnum,int pt)
  {
  int oldanz = (TriangsfromPt[pt] != NULL) ? 
        GetBlockSize (TriangsfromPt[pt]) / sizeof(int) : 0 ;
  LPINT n = LPINT (GetGlobMem ((oldanz + 1) * sizeof(int)));
  if (TriangsfromPt[pt] != NULL) {
    lmemcpy (n,TriangsfromPt[pt],oldanz * sizeof(int));
    FreeGlobMem (TriangsfromPt[pt]);
    }
  n[oldanz] = trnum ;
  TriangsfromPt[pt] = n;
  }

void Voronoi::EnlargeTriangMem ()
  {
  if (trmemSize < (LONG (AnzTriangs + 1) * LONG (sizeof(class Triang)))) {
    trmemSize = (LONG (trmemSize / 0x1000) + 1) * LONG (0x1000);
    WIN_ASSERT (trmemSize < 0xFFFF);
    if (hGTriangMem) {
      GlobalUnlock (hGTriangMem);
      hGTriangMem = GlobalReAlloc (hGTriangMem,trmemSize,GMEM_MOVEABLE);
      }
    else
      hGTriangMem = GlobalAlloc (GMEM_MOVEABLE,trmemSize);
    }
  lpTriangs = (Triang FAR *) GlobalLock (hGTriangMem);
  }

void Voronoi::PushTriang (int i1,int i2,int i3)
  {
  Triang t(i1,i2,i3);
  EnlargeTriangMem ();
  lmemcpy (lpTriangs+AnzTriangs,&t,sizeof(t));
  PushTriangToPt (AnzTriangs,i1);
  PushTriangToPt (AnzTriangs,i2);
  PushTriangToPt (AnzTriangs,i3);
  AnzTriangs++;
  }

#define DLELEM  1.0
BOOL Voronoi::IsToEleminate (int i,int j)
  {
  double dx = double(pts[pind[i]].x - pts[pind[j]].x) ;
  double dy = double(pts[pind[i]].y - pts[pind[j]].y) ;
  return (dx * dx + dy * dy < DLELEM);
  }

void Voronoi::Eleminate (int i)
  {
  int w = pind[i];
  // Wegen Sortierung muss das ganze Array verschoben werden..
  for (int j = i ; j < AnzPts-1 ; j++)
    pind[j] = pind[j+1];
  pind[AnzPts-1] = w ;
  AnzPts -= 1;      // Nach hinten verstecken...
  }

void Voronoi::EleminateSingular ()
  {
  // Alle Punkte, die doppelt vorkommen, nach hinten eleminieren
  //   (dabei kommt zugute, dass die Punkte nach x sortiert sind)
  for (int i = 0 ; i < AnzPts - 1 ; i++ ) {
    for (int j = i + 1 ; j < AnzPts ; ) {
      if (pts[pind[j]].x - pts[pind[i]].x > DLELEM) break ;
      if (IsToEleminate (i,j))
        Eleminate (j);
      else
        j++ ;
      }
    }
  }

int Voronoi::SearchConvexClockwise(int ind,int ti,BOOL FAR &ptOnLine)
  {
  BOOL found = FALSE ;
  BOOL tifound = (ti < 0);
  BOOL begfound = FALSE ;
  int res;
  for (LPCPT h = clist ; !found ; ) {
    if ((h->pi == pind[ind]) && (tifound)) {
      res = FindInd (h->Prev->pi);
      if (res == ti) res = FindInd (h->Prev->Prev->pi);
      found = TRUE ;
      }
    else {
      WIN_ASSERT (!begfound);
      if (!tifound) 
        tifound = (h->pi == pind[ti]);
      h = h->Prev ;
      begfound = (h == clist);
      }
    }
  if (ti >= 0)
    ptOnLine = TestPtOnLine (pind[res],pind[ind],pind[ti]);
  return res;
  }

void Voronoi::SetActiveLine (int i0,int i1)
  {
  // Linie aktiv setzen
  l0 = i0 ;
  l1 = i1 ;
  dxl = double (pts[pind[i1]].x - pts[pind[i0]].x);
  dyl = double (pts[pind[i1]].y - pts[pind[i0]].y);
  }

BOOL Voronoi::TestPtRightOrg (int i)
  {
  double dx = double (pts[i].x - pts[pind[l0]].x) ;
  double dy = double (pts[i].y - pts[pind[l0]].y) ;
  // Punkt ist dann rechts, wenn exprodukt mit der aktiven Line < 0 ist
  return ((dxl * dy - dyl * dx) < 0.0);
  }

BOOL Voronoi::TestPtRightOrgPositive (int i)
  {
  double dx = double (pts[i].x - pts[pind[l0]].x) ;
  double dy = double (pts[i].y - pts[pind[l0]].y) ;
  // Punkt ist dann rechts, wenn exprodukt mit der aktiven Line < 0 ist
  return ((dxl * dy - dyl * dx) < 1.0E-5);
  }

BOOL Voronoi::TestPtRight (int i)
  {
  BOOL res;
  if ((i != l0) && (i != l1)) {
    res = TestPtRightOrg (pind[i]);
    }
  else 
    res = FALSE ;
  return res;
  }

void Voronoi::LineCross (int i,double FAR &t1,double FAR &c)
  {
  // Berechnung des cotan (alpha) mit alpha ist
  // Winkel zwischen der Vektoren l0->i,l1->i;
  //  (diesen Winkel gilt es zu maximieren)
  double dxa = double (pts[pind[i]].x - pts[pind[l0]].x) ;
  double dya = double (pts[pind[i]].y - pts[pind[l0]].y) ;
  double dxb = double (pts[pind[i]].x - pts[pind[l1]].x) ;
  double dyb = double (pts[pind[i]].y - pts[pind[l1]].y) ;
  double exprod = dxa * dyb - dya * dxb ;
  double inprod = dxa * dxb + dya * dyb ;
  if (exprod > 1.0E-5)
    t1 = - (c = inprod / exprod) ;
  else if (exprod < 1.0E-5)
    t1 = c = (inprod / exprod) ;
  else {
    if (inprod > 0.0)
      t1 = - HUGE ;
    else
      t1 = HUGE ;
    c = HUGE ;
    }
  }

void Voronoi::GetBorders (double c)
  {
  // Berechnung des Bereiches, in dem eine Loesung vorkommen kann
  double x1  = pts[pind[l0]].x ;
  double y1  = pts[pind[l0]].y ;
  double x2  = pts[pind[l1]].x ;
  double y2  = pts[pind[l1]].y ;
  double x0 = (x1 + x2 + c * (y1 - y2)) / 2.0 ;
  double y0 = (y1 + y2 + c * (x2 - x1)) / 2.0 ;
  double r2 = x1 * x2 + y1 * y2 - c * (x1 * y2 - x2 * y1) - x0 * x0 - y0 * y0 ;
  WIN_ASSERT (r2 <= 0.0) ;
  double r = sqrt (-r2);
  xmin = x0 - r;
  xmax = x0 + r;
  ymin = y0 - r;
  ymax = y0 + r;
  }

/*--- Suchen von Dreiecken -----------*/
BOOL Triang::IsLine (int i1,int i2)
  {
  if (i1 > i2)
    Chg(i1,i2);

  BOOL res;
  if (i1 == p1)
    res = ((i2 == p2) || (i2 == p3));
  else if (i1 == p2)
    res = (i2 == p3);
  else
    res = FALSE ;

  return res;
  }

int Triang::ThirdPt (int i1,int i2)
  {
  if ((p1 != i1) && (p1 != i2)) return p1 ;
  if ((p2 != i1) && (p2 != i2)) return p2 ;
  return p3 ;
  }

BOOL Triang::IsPoint (int i)
  {
  return ((p1 == i) || (p2 == i) || (p3 == i));
  }

BOOL Triang::SecondPoint (int i)
  {
  if (p1 == i) return p2 ;
  else         return p1 ;
  }

void Voronoi::GetRevInd ()
  {
  // Zuordnung i <-> pind[j]
  rvpind = LPINT(GetGlobMem (AnzOrgPts * sizeof(int)));
  for (int i = 0 ; i < AnzOrgPts ; i++)
    rvpind[pind[i]] = i;
  }

void Voronoi::GetRevInd (int i)
  {
  rvpind[pind[i]] = i;
  }

int Voronoi::FindInd (int j)
  {
  return rvpind[j] ;
  }

BOOL Voronoi::InTriangBuffer(int i)
  {
  for (int j = 0 ; j < TriangBufferCount ; j++) {
    if (i == TriangBuffer[j]) return TRUE ;
    }
  return FALSE ;
  }

int Voronoi::SearchTriangle ()
  {
  // Suchen eines Dreickes, das pind[l0] und pind[l1] als
  // Kante hat, und dessen gegenueberliegender punkt rechts
  // von der aktiven Linie ist.
  int i0 = pind[l0];
  int i1 = pind[l1];
  int res = -1;
  LPINT n = TriangsfromPt[i0];
  int anz = (n != NULL) ? GetBlockSize (n) / sizeof (int) : 0 ;
  for (int i = 0 ; i < anz ; i++) {
    if (lpTriangs[n[i]].IsLine (i0,i1)) {
      int io = lpTriangs[n[i]].ThirdPt(i0,i1);
      if ((TestPtRightOrgPositive(io)) && (!InTriangBuffer(n[i]))) {
        res = FindInd(io);
        PushToTB (n[i]);
        break ;
        }
      }
    }
  return res;
  }

BOOL Voronoi::IsTriangSet (int i1,int i2,int i3)
  {
  // Untersuchen, ob ein Dreieck schon existiert
  if (i2 < i1)
    Chg(i1,i2);
  if (i3 < i1)
    Chg(i1,i3);
  if (i3 < i2)
    Chg(i2,i3);
  BOOL res = FALSE ;
  LPINT n = TriangsfromPt[i1];
  int anz = (n != NULL) ? GetBlockSize (n) / sizeof (int) : 0 ;
  for (int i = 0 ; ((i < anz) && (!res)) ; i++)
    res = ((lpTriangs[n[i]].p1 == i1) && 
           (lpTriangs[n[i]].p2 == i2) && 
           (lpTriangs[n[i]].p3 == i3));
  return res ;
  }

int Voronoi::GetSegInd (double x)
  {
  // Berechnen des ersten Index in dem Segment von x
  if (segstart != NULL) {
    if (x < xsbeg) {
      return segstart[0];
      }
    else if (x > xsend) {
      return segstart[ANZSEGS-1];
      }
    else {
      return segstart[int((x - xsbeg) / xswidth)] ;
      }
    }
  else
    return 0;
  }

void Voronoi::SetSegStart ()
  {
  // Initialisieren der Index Grenzen
  xsbeg = pts[pind[0]].x ;
  xsend = pts[pind[AnzPts-1]].x ;
  if ((xsend - xsbeg) > 1.0E-5) {
    xswidth = (xsend - xsbeg) / double (ANZSEGS);
    segstart = LPINT (GetGlobMem (ANZSEGS * sizeof(int)));
    for (int i = 0 ; i < ANZSEGS ; i++)
      segstart[i] = -1;
    for (i = 0 ; i < AnzPts ; i++) {
      int j = int ((pts[pind[i]].x - xsbeg) / xswidth) ;
      if (segstart[j] == -1)
        segstart[j] = i ;
      }
    int lastind = AnzPts - 1 ;
    for (i = ANZSEGS - 1 ; i >= 0 ; i--) {
      if (segstart[i] == -1)
        segstart[i] = lastind ;
      else
        lastind = segstart[i] ;
      }
    }
  }

int Voronoi::NextLine ()
  {
  // Suchen der Naechsten Line 
  BOOL newTriang = FALSE ;
  int res = SearchTriangle (); // Durchsuchen, ob schon ein Dreieck existiert,
                               // das die Bedingungen erfuellt
  if (res < 0) {
    // Es gibt noch kein fertiges Dreieck -> Ueberpruefen mit LineCross
    ////////////////////////////////////////////////////////////////////
    double abst = - HUGE2;
    double c = HUGE;
    xmin = ymin = -HUGE ;
    xmax = ymax = HUGE ;
    for (int i = l0 ; i < AnzPts ; ) {
      if (pts[pind[i]].x > xmax) break ;
      if ((pts[pind[i]].x >= xmin) && 
          (pts[pind[i]].y >= ymin) && 
          (pts[pind[i]].y <= ymax) && (TestPtRight(i))) {
        double nabst ;
        // Suchen einer neuen Loesung
        LineCross (i,nabst,c);
        if (nabst > abst) {
          // neue Loesung gefunden
          newTriang = TRUE ;
          res = i ;
          abst = nabst ;
          // Bereich neu einschraenken
          GetBorders (c);
          int nsi = GetSegInd (xmin) ;
          int nss = i + 1;
          // Index (vielleicht sogar schnell) weiterschalten
          i = max (nsi,nss) ;
          }
        else
          i++ ;
        }
      else
        i++ ;
      }
    TriangBufferCount = 0;
    if (res < 0) {
      // Es gibt keinen Punkt rechts der aktiven Linie ->
      // Punkt ist Element der Konvexen Huelle -> Andere Seite der 
      // Konvexen Huelle suchen
      BOOL ptOnLine;
      res = SearchConvexClockwise(l0,l1,ptOnLine);
      WIN_ASSERT (res >= 0);
      if (ptOnLine)
        if (newTriang = !IsTriangSet (pind[l0],pind[l1],pind[res]))
          PushToTB (AnzTriangs);
      }
    }

  if (newTriang)    // Wieder was gefunden
    PushTriang (pind[l0],pind[l1],pind[res]);
  return res;
  }

int Voronoi::NextStartLine (int start)
  {
  // Suchen der einer Linie in dem noch nicht untersuchten Bereich
  // Gefundenen Punkt auf den Startindex legen
  int res = -1;
  BOOL found = FALSE ;
  for (int i = start ; ((!found) && (i < AnzPts)) ; i++) {
    for (int j = 0 ; ((!found) && (j < AnzTriangs)) ; j++) {
      if (lpTriangs[j].IsPoint(pind[i])) {
        res = FindInd(lpTriangs[j].SecondPoint(pind[i]));
        found = TRUE ;
        Chg(pind[start],pind[i]);
        GetRevInd (start);
        GetRevInd (i);
        }
      }
    }
  WIN_ASSERT (res >= 0);
  return res;
  }

/*-------- Dreieckszerlegung ------------*/
DLLExport void _export WINAPI Voronoi::Analyse ()
  {
  if (AnzPts > 2) {
    for (int i = 0 ; i < AnzPts ; i++)    // Default Sortierung
      pind[i] = i;

    QuickSort (0,AnzPts-1);

    // Eleminieren der doppelten Punkte
    EleminateSingular ();
    if (AnzPts <= 2) return ;
    GetRevInd ();

    clist = GetConvexList (0,AnzPts - 1);
    CompleteConvex (clist);
    SetSegStart ();

    BOOL ptOnLine;
    lstart = SearchConvexClockwise(0,-1,ptOnLine);
    for (i = 0 ; i < AnzPts - 1; i++) {
      int lact = lstart ;
      TriangBufferCount = 0;
      do {
        SetActiveLine (i,lact);
        lact = NextLine ();
        } while (lact != lstart) ;
      if (i < (AnzPts - 1))
        lstart = NextStartLine (i+1);
      }
    }
  }

void scale (int FAR *x,int FAR *y,tr2 FAR *sc,fpt FAR *p)
  {
  *x = int ((sc->A[0][0] * p->x + sc->A[0][1] * p->y + sc->B[0]));
  *y = int ((sc->A[1][0] * p->x + sc->A[1][1] * p->y + sc->B[1]));
  }

DLLExport void _export WINAPI Voronoi::Paint (HDC hDC,tr2 FAR *sc)
  {
  for (int i = 0 ; i < AnzTriangs ; i++) {
    // Zeichnen der Dreiecke
    int x,y;
    scale (&x,&y,sc,&pts[lpTriangs[i].p1]); MoveToEx (hDC,x,y, NULL);
    scale (&x,&y,sc,&pts[lpTriangs[i].p2]); LineTo (hDC,x,y);
    scale (&x,&y,sc,&pts[lpTriangs[i].p3]); LineTo (hDC,x,y);
    scale (&x,&y,sc,&pts[lpTriangs[i].p1]); LineTo (hDC,x,y);
    }
  HPEN hOldPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,1,RGB(0xFF,0,0)));
  for (i = 0 ; i < AnzOrgPts ; i++) {
    // Zeichnen der Punkte als Kreueze
    int x,y;
    scale (&x,&y,sc,&pts[i]);
    MoveToEx (hDC,x - 170,y, NULL) ;
    LineTo (hDC,x + 170,y) ;
    MoveToEx (hDC,x,y - 170, NULL) ;
    LineTo (hDC,x,y + 170) ;
    }
  DeleteObject (SelectObject (hDC,hOldPen));
  }

DLLExport void _export WINAPI Voronoi::PaintVect (HDC hDC,fpt FAR *p,fpt FAR *v)
  {
  HPEN hOldPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,1,RGB(0,0xFF,0)));
  int mx = int(p->x + v->x / 2.0);
  int my = int(p->y + v->y / 2.0);
  MoveToEx (hDC,int(p->x),int(p->y), NULL);
  LineTo (hDC,mx,my);
  DeleteObject (SelectObject (hDC,hOldPen));
  hOldPen = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,1,RGB(0,0,0xFF)));
  MoveToEx (hDC,int(p->x + v->x),int(p->y + v->y), NULL);
  LineTo (hDC,mx,my);
  DeleteObject (SelectObject (hDC,hOldPen));
  }

DLLExport void _export WINAPI Voronoi::PaintAllVects (HDC hDC)
  {
  for (int i = 0 ; i < AnzPts ; i++)
    PaintVect (hDC,&pts[i],&vects[i]);
  }

///////////////////////////////////////////////////////////////////////////
//    Berechnungen mit den Dreicken (zwecks linearer Interpolierung)
///////////////////////////////////////////////////////////////////////////
void Triang::OrderDirection ()
  {
  // Die Indizess so Anorden, dass 
  //      p3 rechts von p1->p2
  //      p2 rechts von p3->p1
  //      p1 rechts von p2->p3 liegt
  double dx  = double (actV->pts[p2].x - actV->pts[p1].x) ;
  double dy  = double (actV->pts[p2].y - actV->pts[p1].y) ;
  double dx1 = double (actV->pts[p3].x - actV->pts[p1].x) ;
  double dy1 = double (actV->pts[p3].y - actV->pts[p1].y) ;
  if ((dx * dy1 - dy * dx1) <= 0.0)
    // p1 und p2 vertauschen
    Chg (p1,p2);
  }

void Voronoi::ChgTriang (Triang FAR *t1,Triang FAR *t2)
  {
  char buffer[sizeof(Triang)];
  lmemcpy (buffer,t1,sizeof(buffer));
  lmemcpy (t1,t2,sizeof(*t1));
  lmemcpy (t2,buffer,sizeof(*t2));
  }

BOOL Triang::IsTriangEmpty ()
  {
  double dx  = double (actV->pts[p2].x - actV->pts[p1].x) ;
  double dy  = double (actV->pts[p2].y - actV->pts[p1].y) ;
  double dx1 = double (actV->pts[p3].x - actV->pts[p1].x) ;
  double dy1 = double (actV->pts[p3].y - actV->pts[p1].y) ;
  return (dx * dy1 - dy * dx1 <= 1.0E-5);
  }

BOOL Triang::IsPtInside (fpt FAR *p)
  {
  double dx1  = double (actV->pts[p2].x - actV->pts[p1].x) ;
  double dy1  = double (actV->pts[p2].y - actV->pts[p1].y) ;
  double dx2  = double (actV->pts[p3].x - actV->pts[p2].x) ;
  double dy2  = double (actV->pts[p3].y - actV->pts[p2].y) ;
  double dx3  = double (actV->pts[p1].x - actV->pts[p3].x) ;
  double dy3  = double (actV->pts[p1].y - actV->pts[p3].y) ;
  double dxp1 = double (p->x - actV->pts[p1].x) ;
  double dyp1 = double (p->y - actV->pts[p1].y) ;
  double dxp2 = double (p->x - actV->pts[p2].x) ;
  double dyp2 = double (p->y - actV->pts[p2].y) ;
  double dxp3 = double (p->x - actV->pts[p3].x) ;
  double dyp3 = double (p->y - actV->pts[p3].y) ;
  return (((dy1 * dxp1 - dx1 * dyp1) <= 0.0) &&
          ((dy2 * dxp2 - dx2 * dyp2) <= 0.0) &&
          ((dy3 * dxp3 - dx3 * dyp3) <= 0.0));
  }

DLLExport void _export WINAPI Voronoi::SetVects(fpt FAR *v,int Anz)
  {
  vects = v ;
  WIN_ASSERT (Anz == AnzOrgPts) ;
  }

/*--- Berechnen der Ebenengleichnung ------*/
void Triang::GetPlane (float z1,float z2,float z3,
                           float FAR &a,float FAR &b,float FAR &c)
  {
  double dx2 = double (actV->pts[p2].x - actV->pts[p1].x);
  double dy2 = double (actV->pts[p2].y - actV->pts[p1].y);
  double dz2 = double (z2 - z1) ;
  double dx3 = double (actV->pts[p3].x - actV->pts[p1].x);
  double dy3 = double (actV->pts[p3].y - actV->pts[p1].y);
  double dz3 = double (z3 - z1) ;
  double alpha = dy3 * dz2 - dz3 * dy2 ;
  double beta  = dz3 * dx2 - dx3 * dz2 ;
  double gamma = dx3 * dy2 - dy3 * dx2 ;
  double delta = - double (actV->pts[p1].x) * alpha
                 - double (actV->pts[p1].y) * beta
                 - double (z1) * gamma ;
  WIN_ASSERT (fabs (gamma) >= 1.0E-5);
  a = - float (alpha / gamma) ;
  b = - float (beta / gamma) ;
  c = - float (delta / gamma) ;
  }

DLLExport void _export WINAPI Voronoi::PrepareTriangs ()
  {
  // 1. Indizess richtig setzen
  for (int i = 0 ; i < AnzTriangs ; i++)
    lpTriangs[i].OrderDirection ();
  // 2. Leere Dreiecke eleminieren
  for (i = 0 ; i < AnzTriangs ; ) {
    if (lpTriangs[i].IsTriangEmpty ())
      ChgTriang (&lpTriangs[i],&lpTriangs[AnzTriangs-1]), AnzTriangs -= 1;
    else
      i++ ;
    }
  // 3. Berechnen der Flaechengleichungen
  WIN_ASSERT (vects != NULL) ;
  for (i = 0 ; i < AnzTriangs ; i++) {
    Triang FAR *t = &lpTriangs[i];
    t->GetPlane (vects[t->p1].x,vects[t->p2].x,vects[t->p3].x,
                    t->ax,t->bx,t->cx
                );
    t->GetPlane (vects[t->p1].y,vects[t->p2].y,vects[t->p3].y,
                    t->ay,t->by,t->cy
                );
    }
  BuildSectionList ();
  if (clist != NULL)
    exr = GetExtRange ();
  }

/*--------- Erstellen einer Liste der Dreiecke in den Segmenten -----*/
BOOL Triang::IsTriangInSect (double xmin,double xmax,double ymin,double ymax)
  {
  return ((actV->pts[p1].x >= xmin) && (actV->pts[p1].x <= xmax) &&
          (actV->pts[p1].y >= ymin) && (actV->pts[p1].y <= ymax) &&
          (actV->pts[p2].x >= xmin) && (actV->pts[p2].x <= xmax) &&
          (actV->pts[p2].y >= ymin) && (actV->pts[p2].y <= ymax) &&
          (actV->pts[p3].x >= xmin) && (actV->pts[p3].x <= xmax) &&
          (actV->pts[p3].y >= ymin) && (actV->pts[p3].y <= ymax)) ;
  }

BOOL Triang::IsRectPartInside (double xmin,double xmax,double ymin,double ymax)
  {
  fpt p;
  p.x = float (xmin);
  p.y = float (ymin);
  if (IsPtInside (&p)) return TRUE ;
  p.x = float (xmin);
  p.y = float (ymax);
  if (IsPtInside (&p)) return TRUE ;
  p.x = float (xmax);
  p.y = float (ymax);
  if (IsPtInside (&p)) return TRUE ;
  p.x = float (xmax);
  p.y = float (ymin);
  if (IsPtInside (&p)) return TRUE ;
  return FALSE ; 
  }

BOOL Triang::HLineCross (double y,double xmin,double xmax,int i1,int i2)
  {
  if (((double (actV->pts[i1].y) - y) * (double (actV->pts[i2].y) - y))
       <= 0.0) {
    double dx = xmax - xmin;
    double dy1 = double (actV->pts[i2].y - actV->pts[i1].y) ;
    if (fabs(dy1) >= 0.0) {
      double dx1 = double (actV->pts[i2].x - actV->pts[i1].x) ;
      double t = (double (actV->pts[i1].x) + dx1 / dy1 *
                      (y - double (actV->pts[i1].y)) - xmin) ;
      return ((t >= 0.0) && (t <= dx));
      }
    else {
      return ((((double (actV->pts[i1].x) - xmin) * 
                (double (actV->pts[i2].x) - xmin)) <= 0.0) ||
              (((double (actV->pts[i1].x) - xmax) * 
                (double (actV->pts[i2].x) - xmax)) <= 0.0));
      }
    }
  else
    return FALSE ;
  }

BOOL Triang::VLineCross (double x,double ymin,double ymax,int i1,int i2)
  {
  if (((double (actV->pts[i1].x) - x) * (double (actV->pts[i2].x) - x))
       <= 0.0) {
    double dy = ymax - ymin;
    double dx1 = double (actV->pts[i2].x - actV->pts[i1].x) ;
    if (fabs(dx1) >= 0.0) {
      double dy1 = double (actV->pts[i2].y - actV->pts[i1].y) ;
      double t = (double (actV->pts[i1].y) + dy1 / dx1 *
                      (x - double (actV->pts[i1].x)) - ymin) ;
      return ((t >= 0.0) && (t <= dy));
      }
    else {
      return ((((double (actV->pts[i1].y) - ymin) * 
                (double (actV->pts[i2].y) - ymin)) <= 0.0) ||
              (((double (actV->pts[i1].y) - ymax) * 
                (double (actV->pts[i2].y) - ymax)) <= 0.0));
      }
    }
  else
    return FALSE ;
  }

BOOL Triang::HLineCross (double y,double xmin,double xmax)
  {
  return ((HLineCross (y,xmin,xmax,p1,p2)) || 
          (HLineCross (y,xmin,xmax,p2,p3)) || 
          (HLineCross (y,xmin,xmax,p3,p1)));
  }

BOOL Triang::VLineCross (double x,double ymin,double ymax)
  {
  return ((VLineCross (x,ymin,ymax,p1,p2)) || 
          (VLineCross (x,ymin,ymax,p2,p3)) || 
          (VLineCross (x,ymin,ymax,p3,p1)));
  }

BOOL Triang::TestSection (double xmin,double xmax,double ymin,double ymax)
  {
  if (((xmax < double (actV->pts[p1].x)) && (xmax < double(actV->pts[p2].x)) && (xmax < double(actV->pts[p3].x))) ||
      ((xmin > double (actV->pts[p1].x)) && (xmin > double(actV->pts[p2].x)) && (xmin > double(actV->pts[p3].x))) ||
      ((ymax < double (actV->pts[p1].y)) && (ymax < double(actV->pts[p2].y)) && (ymax < double(actV->pts[p3].y))) ||
      ((ymin > double (actV->pts[p1].y)) && (ymin > double(actV->pts[p2].y)) && (ymin > double(actV->pts[p3].y))))
    return FALSE ;
  else
    return ((IsRectPartInside (xmin,xmax,ymin,ymax)) || 
            (IsTriangInSect (xmin,xmax,ymin,ymax)) || 
            (HLineCross (ymin,xmin,xmax)) ||
            (HLineCross (ymax,xmin,xmax)) ||
            (VLineCross (xmin,ymin,ymax)) ||
            (VLineCross (xmax,ymin,ymax)));
  }

void Voronoi::PushTriangToSection (int tr,int xs,int ys)
  {
  if (TriangsfromSection == NULL) {
    TriangsfromSection = (LPINT FAR *) GetGlobMem (sizeof(LPINT) * ANZSEGS * ANZSEGS);
    }
  WIN_ASSERT ((xs < ANZSEGS) && (ys < ANZSEGS));
  int ind = xs * ANZSEGS + ys ;
  int Anz = (TriangsfromSection[ind] != NULL) ? 
                GetBlockSize(TriangsfromSection[ind]) / sizeof(int) :
                0 ;
  LPINT n = LPINT (GetGlobMem ((Anz + 1) * sizeof(int)));
  if (TriangsfromSection[ind] != NULL) {
    lmemcpy (n,TriangsfromSection[ind],Anz * sizeof(int));
    FreeGlobMem (TriangsfromSection[ind]);
    }
  n[Anz] = tr ;
  TriangsfromSection[ind] = n;
  }

void Voronoi::BuildSectionList ()
  {
  if (AnzTriangs <= 0) return ;
  xmin = ymin = HUGE ;
  xmax = ymax = -HUGE ;
  for (int i = 0 ; i < AnzPts ; i++) {
    if (double (pts[i].x) > xmax) xmax = double (pts[i].x) ;
    if (double (pts[i].y) > ymax) ymax = double (pts[i].y) ;
    if (double (pts[i].x) < xmin) xmin = double (pts[i].x) ;
    if (double (pts[i].y) < ymin) ymin = double (pts[i].y) ;
    }
  if (((xmax - xmin) <= 1.0E-5) || ((ymax - ymin) <= 1.0E-5)) return ;
  xsw = (xmax - xmin) / double (ANZSEGS) ;
  ysw = (ymax - ymin) / double (ANZSEGS) ;
  for (i = 0 ; i < ANZSEGS ; i++) {
    // Uber alle x
    for (int j = 0 ; j < ANZSEGS ; j++) {
      // Ueber alle y
      for (int t = 0 ; t < AnzTriangs ; t++) {
        // Alle Dreiecke durchsuchen
        if (lpTriangs[t].TestSection (xmin + xsw * double (i),
                                      xmin + xsw * double (i + 1),
                                      ymin + ysw * double (j),
                                      ymin + ysw * double (j + 1)
                                     ))
          PushTriangToSection (t,i,j);
        }
      }
    }
  }

LPTRIANG Voronoi::SearchTriang (fpt FAR *p)
  {
  if (TriangsfromSection != NULL) {
    int xs = int ((double (p->x) - xmin) / xsw) ;
    int ys = int ((double (p->y) - ymin) / ysw) ;
    if ((xs >= 0) && (xs < ANZSEGS) &&
        (ys >= 0) && (ys < ANZSEGS)) {
      int ind = xs * ANZSEGS + ys ;
      int Anz = (TriangsfromSection[ind] != NULL) ? 
                   GetBlockSize(TriangsfromSection[ind]) / sizeof(int) :
                   0 ;
      for (int i = 0 ; i < Anz ; i++) {
        if (lpTriangs[TriangsfromSection[ind][i]].IsPtInside (p)) 
          return &lpTriangs[TriangsfromSection[ind][i]];
        }
      }
    }
  else {
    for (int i = 0 ; i < AnzTriangs ; i++)
      if (lpTriangs[i].IsPtInside (p)) return &lpTriangs[i] ;
    }
  return NULL ;
  }

DLLExport void _export WINAPI Voronoi::Interpolate (fpt FAR *p,fpt FAR *v)
  {
  LPTRIANG t = SearchTriang (p);
  if (t != NULL) {
    v->x = t->ax * p->x + t->bx * p->y + t->cx ;
    v->y = t->ay * p->x + t->by * p->y + t->cy ;
    }
  else {
    ExtRange FAR *e = SearchExtRange (p);
    if (e != NULL)
      e->Interpolate (p,v);
    else {
//      WIN_ASSERT (FALSE);
      v->x = v->y = float (0.0) ;
      }
    }
  }

/*---- Untersuchung der Bereiche ausserhalb des Konvexen Dreieckes ----*/
LPVOID ExtRange::operator new (size_t size)
  { 
  return GetGlobMem (size) ; 
  }

void ExtRange::operator delete (LPVOID obj)
  { 
  FreeGlobMem (obj) ; 
  }

BOOL ExtRange::IsDeadEnd (int i,int ip,int in)
  {
  double dpx = double (actV->pts[ip].x - actV->pts[i].x) ;
  double dpy = double (actV->pts[ip].y - actV->pts[i].y) ;
  double dnx = double (actV->pts[in].x - actV->pts[i].x) ;
  double dny = double (actV->pts[in].y - actV->pts[i].y) ;
  return ((fabs (dpx * dny - dpy * dnx) <= 1.0E-5) &&
                ((dpx * dnx + dpy * dny) >= 0.0));
  }

#define ERSTATE_NORMAL   0
#define ERSTATE_DEADEND  1
void ExtRange::GetSymmetrie (int i,int ip,int in,tag_ffpt FAR &res,double lfact,int FAR &state)
  {
  double dpx = double (actV->pts[ip].x - actV->pts[i].x) ;
  double dpy = double (actV->pts[ip].y - actV->pts[i].y) ;
  if (state == ERSTATE_NORMAL) {
    double dnx = double (actV->pts[in].x - actV->pts[i].x) ;
    double dny = double (actV->pts[in].y - actV->pts[i].y) ;
    if (fabs (dpx * dny - dpy * dnx) > 1.0E-5) {
      double lp = sqrt (dpx * dpx + dpy * dpy) ;
      double ln = sqrt (dnx * dnx + dny * dny) ;
      WIN_ASSERT ((lp > 0.0) && (ln >= 0.0));
      res.x = actV->pts[i].x + float ((dpx / lp + dnx / ln) * lfact);
      res.y = actV->pts[i].y + float ((dpy / lp + dny / ln) * lfact);
      }
    else {
      res.x = actV->pts[i].x - float (lfact * dpy) ;
      res.y = actV->pts[i].y + float (lfact * dpx) ;
      }
    }
  else {
    double l = sqrt (dpx * dpx + dpy * dpy) ;
    WIN_ASSERT (l > 0.0);
    double sq2 = sqrt (0.5) / l * 100.0 ;
    // Rotation des dpx Vektors um - 135 Grad
    res.x = actV->pts[i].x + float (- dpx * sq2 + dpy * sq2) ;
    res.y = actV->pts[i].y + float (- dpx * sq2 - dpy * sq2) ;
    state = ERSTATE_NORMAL;
    }
  }

void ExtRange::GetDeadEndSide (int i,int ip,tag_ffpt FAR &r1)
  {
  double dpx = double (actV->pts[ip].x - actV->pts[i].x) ;
  double dpy = double (actV->pts[ip].y - actV->pts[i].y) ;
  double sq2 = sqrt (0.5);
  // r1 .. Rotation um - 45 Grad
  r1.x = actV->pts[i].x + float (dpx * sq2 + dpy * sq2) ;
  r1.y = actV->pts[i].y + float (- dpx * sq2 + dpy * sq2) ;
  }

void ExtRange::GetDeadEnd (int i,int ip,tag_ffpt FAR &r1,tag_ffpt FAR &r2,int FAR &state)
  {
  double dpx = double (actV->pts[ip].x - actV->pts[i].x) ;
  double dpy = double (actV->pts[ip].y - actV->pts[i].y) ;
  double sq2 = sqrt (0.5);
  // r1 .. Rotation um 135 Grad
  r1.x = actV->pts[i].x + float (- dpx * sq2 - dpy * sq2) ;
  r1.y = actV->pts[i].y + float (dpx * sq2 - dpy * sq2) ;
  // r2 .. Rotation um 45 Grad
  r2.x = actV->pts[i].x + float (dpx * sq2 - dpy * sq2) ;
  r2.y = actV->pts[i].y + float (dpx * sq2 + dpy * sq2) ;
  state = ERSTATE_DEADEND;
  }

LPCPT ExtRange::NextLine (LPCPT c,BOOL FAR &state)
  {
  // Es wird jeweils die Linie zwischen den Punkte c->Next,c->Next->pi
  // verwendet (wenn moeglich)
  LPCPT res ;
  if ((state == ERSTATE_NORMAL) && 
        (IsDeadEnd (c->pi,c->Next->pi,c->Prev->pi))) {
    GetDeadEnd (c->pi,c->Next->pi,p1,p2,state);
    res = c;
    i1 = i2 = c->pi;
    }
  else {
    i1 = c->pi;
    i2 = c->Next->pi ;
    GetSymmetrie (c->pi,c->Next->pi,c->Prev->pi,p1,-100.0,state);
    if (IsDeadEnd (c->Next->pi,c->Next->Next->pi,c->pi))
      GetDeadEndSide (c->Next->pi,c->Next->Next->pi,p2);
    else
      GetSymmetrie (c->Next->pi,c->Next->Next->pi,c->pi,p2,100.0,state);
    res = c->Next;
    Cross ((tag_ffpt FAR *) &(actV->pts[c->pi]),&p1,
           (tag_ffpt FAR *) &(actV->pts[c->Next->pi]),&p2,&pcross
          );
    }
  return res;
  }


void ExtRange::Cross (tag_ffpt FAR *p11,tag_ffpt FAR *p12,tag_ffpt FAR *p21,tag_ffpt FAR *p22,double FAR &res)
  {
  // Schnittpunkt berechnen 
  //   Resultierender Punkt: p11 + res * (p12 - p11) ;
  double dx1 = p12->x - p11->x ;
  double dy1 = p12->y - p11->y ;
  double dx2 = p22->x - p21->x ;
  double dy2 = p22->y - p21->y ;
  double exprod = dx1 * dy2 - dy1 * dx2 ;
  if (fabs (exprod) > 1.0E-5)
    res = (double (p21->x - p11->x) * dy2 +
           double (p11->y - p21->y) * dx2) / exprod ;
  else
    res = HUGE2 ;
  }

void ExtRange::Cross (tag_ffpt FAR *p11,tag_ffpt FAR *p12,tag_ffpt FAR *p21,tag_ffpt FAR *p22,tag_ffpt FAR *res)
  {
  double t1 ;
  Cross (p11,p12,p21,p22,t1);
  if (t1 < HUGE) {
    double dx1 = p12->x - p11->x ;
    double dy1 = p12->y - p11->y ;
    res->x = p11->x + float (dx1 * t1) ;
    res->y = p11->y + float (dy1 * t1) ;
    }
  else
    res->x = res->y = HUGE2 ;
  }

BOOL ExtRange::TestRight (fpt FAR *p,tag_ffpt FAR *p1,tag_ffpt FAR *p2)
  {
  double dx = p->x - p1->x ;
  double dy = p->y - p1->y ;
  double dx1 = p2->x - p1->x ;
  double dy1 = p2->y - p1->y ;
  return ((dx * dy1 - dx1 * dy) >= -1.0E-5);
  }

void ExtRange::ProPt (fpt FAR *p,fpt FAR *p1,fpt FAR *p2,double FAR &t)
  {
  double dx  = double (p->x - p1->x) ;
  double dy  = double (p->y - p1->y) ;
  double dx1 = double (p2->x - p1->x) ;
  double dy1 = double (p2->y - p1->y) ;
  double inprod = dx * dx1 + dy * dy1 ;
  double l  = sqrt (dx * dx + dy * dy);
  double l1 = sqrt (dx1 * dx1 + dy1 * dy1);
  WIN_ASSERT ((l > 1.0E-5) && (l1 > 1.0E-5));
  t = inprod / (l * l1) ;
  }

BOOL ExtRange::Test (fpt FAR *p)
  {
  if (i1 != i2)
    return ((TestRight (p,&p1,(tag_ffpt FAR *) &(actV->pts[i1]))) &&
            (TestRight (p,(tag_ffpt FAR *) &(actV->pts[i1]),(tag_ffpt FAR *) &(actV->pts[i2]))) &&
            (TestRight (p,&p2,(tag_ffpt FAR *) &(actV->pts[i2]))));
  else
    return ((TestRight (p,&p1,(tag_ffpt FAR *) &(actV->pts[i1]))) &&
            (TestRight (p,&p2,(tag_ffpt FAR *) &(actV->pts[i1]))));
  }

void ExtRange::Interpolate (fpt FAR *p,fpt FAR *v)
  {
  if (i1 != i2) {
      double t ;
    if ((pcross.x < HUGE) && (pcross.y < HUGE))
      Cross ((tag_ffpt FAR *) &(actV->pts[i1]),(tag_ffpt FAR *) &(actV->pts[i2]),
             (tag_ffpt FAR *) p,&pcross,t);
    else
      ProPt (p,&(actV->pts[i1]),&(actV->pts[i2]),t);
    if ((t < -0.01) || (t > 1.01)) {
      WIN_ASSERT (FALSE);
      }
    v->x = float (double (actV->vects[i1].x) * (1.0 - t) + 
                  double (actV->vects[i2].x) * t); 
    v->y = float (double (actV->vects[i1].y) * (1.0 - t) + 
                  double (actV->vects[i2].y) * t); 
    }
  else {
    v->x = actV->vects[i1].x ;
    v->y = actV->vects[i1].y ;
    }
  }

ExtRange FAR *Voronoi::GetExtRange ()
  {
  ExtRange FAR *first = NULL ;
  ExtRange FAR *prev = NULL ;
  int state = ERSTATE_NORMAL ;
  for ( LPCPT h = clist ; ; ) {
    ExtRange FAR *e = new ExtRange ();
    e->Next = NULL ;
    if (prev != NULL)
      prev->Next = e;
    prev = e ;
    if (first == NULL)
      first = e;
    h = e->NextLine (h,state);
    if ((state == ERSTATE_NORMAL) && (h == clist)) break ;
    }
  return first ;
  }

ExtRange FAR *Voronoi::SearchExtRange (fpt FAR *p)
  {
  for (ExtRange FAR *h = exr ; h != NULL ; h = h->Next) {
    if (h->Test (p)) break ;
    }
  return h ;  
  }


