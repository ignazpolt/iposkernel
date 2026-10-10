///////////////////////////////////////////////////////////////
//  Numerische Analysen im Formular
///////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/frmobj2.cpv   1.13   02 Feb 2000 20:49:28   Martin  $
// $Log:   P:/marille/clinicum/frmobj/rev/frmobj2.cpv  $
// 
//    Rev 1.13   02 Feb 2000 20:49:28   Martin
// ClickPoint in ActivationRegion
// 
//    Rev 1.12   06 Nov 1998 20:36:18   Hannes
// Deaktivieren bei nicht initialisierten Formularen
// 
//    Rev 1.11   05 Oct 1998 11:21:42   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   24 Jul 1998 18:50:26   Wolfgang
// 1.) SetInActiveIf in ActivationRegion neu da IsActive-Flag 
//     manchmal falsch gesetzt.
// 
//    Rev 1.9   21 Apr 1998 19:32:26   Hannes
// Aktivierungsregion ohne Rahmen
// 
//    Rev 1.8   16 Feb 1998 14:15:24   Gerhold
// VC++5.x ... explicit ist jetzt ein Schluesselwort
// 
//    Rev 1.7   08 Sep 1997 11:03:34   Gerhold
// WORD-Parameter in WPARAM-Parameter umgewandelt
// 
//    Rev 1.6   10 Apr 1997 11:40:42   Hannes
// ActivationRect -> hActivePen und hInActivePen verwendet
// 
//    Rev 1.5   10 Jun 1996 10:12:04   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.4   24 Mar 1996 12:11:24   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 10:49:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:15:10   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.1   20 Mar 1995 12:13:44   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.0   24 Jun 1994 16:45:42   MARTIN
// Neuuebernahme clinicum
//

#include <windows.h>
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
#define CARETHANDLING_DONE
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "frmobj.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"
#define MODULENUM 30
#include "winass.hpp"
#include "winextra.hpp"


typedef mNum FAR *LPMNUM;

int mNumSize_param::HdHeight(dllChild m)
  {
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  LPFORMATMETRIC lpfm = GetFormatMetrics (m.MyHandle(),MapType,m.GetConstInt(rhdnamFormat));
  return lpfm->yHeight ;
  }

int mNumSize_param::ValHeight(dllChild m)
  {
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  LPFORMATMETRIC lpfm = GetFormatMetrics (m.MyHandle(),MapType,m.GetConstInt(rnamFormat));
  return lpfm->yHeight ;
  }

int mNum::yLower (int Seite)
  {
  return y0 + height;
  }

void mNum::GetOrigin ()
  {
  LPFRMOBJ FAR *lpprev = (LPFRMOBJ FAR *) m.ReadlData (Par()->prevObj);
  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  DBWIN_ASSERT (lpps != NULL);

  // Hoehe muss auf jeden Fall schon am 
  //    beim Load berechnet werden
  DBBOOL FAR *lpdoShow = (DBBOOL FAR *) m.ReadlData (Par()->doShow);
  doShow = (lpdoShow != NULL) ? *lpdoShow : FALSE ;
  xw = m.GetConstInt((*lpps)->rxWidth);
  height = 0;

  if ((lpprev != NULL) && (*lpprev != NULL)) {
    y0 = (*lpprev) -> yLower (ErsteSeite());
    if ((IsHeadLine()) && ((*lpprev)->IsmNum ()))
      // Noch eine Zeile dazu
      y0 += (*lpps)->HdHeight(m);
    }
  else
    y0 = m.GetConstInt((*lpps)->ry0) ;
  if (Run == 0)
    x0 = m.GetConstInt((*lpps)->rx0) ;
  else
    x0 = m.GetConstInt((*lpps)->rx0) +
         m.GetConstInt((*lpps)->rnamWidth) + m.GetConstInt((*lpps)->runionWidth) +
         Run * m.GetConstInt((*lpps)->rxWidth) * 3;
  }

int mNum::GetWidth (LPMNSIZE p)
  {
  int width = 3 * m.GetConstInt(p->rxWidth);
  if (Run == 0) {
    DBINT FAR *anzrows = (DBINT FAR *) m.ReadlData (p->rAnzRows);
    DBWIN_ASSERT (anzrows != NULL);
    width = width * *anzrows + m.GetConstInt(p->rnamWidth) + m.GetConstInt(p->runionWidth);
    }
  return width;
  }

void mNum::GetMinMax ()
  {
  RECT rcLogRect;
  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  rcLogRect.top    = y0 ;
  rcLogRect.left   = x0 ;
  rcLogRect.bottom = rcLogRect.top + height ;
  rcLogRect.right  = rcLogRect.left + GetWidth(*lpps);
  if (Run == 0) {
    xl = x0 + m.GetConstInt((*lpps)->rnamWidth) + m.GetConstInt((*lpps)->runionWidth);
    xe = xl + 3 * m.GetConstInt((*lpps)->rxWidth) ;
    }
  else {
    xl = x0 ;
    xe = xl + 3 * m.GetConstInt((*lpps)->rxWidth) ;
    }
  SetLogRect (&rcLogRect,ErsteSeite());
  }

cField FAR *mNum::createField (int x,int format,int w)
  {
  cField FAR *res = new cField 
        (TRANSPARENT,format,x,y0,w,-1,FALSE);
  res->SetWindow (m.MyHandle());
  int MapType;
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  res->SetScale (m_scale(),MapType);
  res->SetVOrg (m.xp(),m.yp(),ErsteSeite());
  if (MapType == MAPTYPE_GEOMETRIC) {
    POINT pt;
    m.GetDocInfo (GETWINDOWORG,0,&pt);
    res->SetWOrg (pt.x,pt.y);
    }
  return res;
  }

void mNum::DelFields ()
  {
  for (int i = 0 ; i < 5 ; i++)
    if (fld[i] != NULL) delete fld[i] ;
  }

void mNum::GetFields ()
  {
  DelFields ();

  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  int xs = m.GetConstInt((*lpps)->rxspcWidth);
  int x = x0;
  int width;
  width = m.GetConstInt((*lpps)->rnamWidth);
  fld[0] = createField (x,
              int (IsHeadLine() ? m.GetConstInt((*lpps)->rhdnamFormat) 
                                : m.GetConstInt((*lpps)->rnamFormat)),
              width - xs
                       );
  x += width;
  width = m.GetConstInt((*lpps)->runionWidth);
  fld[1] = createField (x + xs,
              int (IsHeadLine() ? m.GetConstInt((*lpps)->rhdnamFormat) 
                                : m.GetConstInt((*lpps)->rnamFormat)),
              width - xs
                       );
  x += width ;

  width = xw ;
  for (int i = 2 ; i <= 4 ; i++)
    fld[i] = createField (x + xs,
                int (IsHeadLine() ? m.GetConstInt((*lpps)->rhdvalFormat)
                                  : m.GetConstInt((*lpps)->rvalFormat)),
                width - 2 * xs
                         ),
    x += width ;
  }

LPSTR mNum::UnionString ()
  {
  return LPSTR (m.ReadlData (Par()->Union));
  }

void mNum::SetText ()
  {
  char val[16],norm[16];
  float fval,fnorm;
  char empty = '\0';
  if (fld[0] != NULL) {
    LPSTR Name = LPSTR(m.ReadlData (Par()->Name));
    *fld[0] = (Name != NULL) ?
      Name : &empty ;
    LPSTR UStr = UnionString ();
    *fld[1] = (UStr != NULL) ? UStr : &empty;
    }
  if (IsHeadLine()) {
    LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
    LPSTR Wert       = LPSTR (m.ReadlData ((*lpps)->valDesc));
    LPSTR Norm       = LPSTR (m.ReadlData ((*lpps)->normDesc));
    LPSTR Abweichung = LPSTR (m.ReadlData ((*lpps)->devDesc));
    *fld[2] = (Wert != NULL) ? Wert : &empty;
    *fld[3] = (Norm != NULL) ? Norm : &empty;
    *fld[4] = (Abweichung != NULL) ? Abweichung : &empty;
    }
  else {
    *fld[2] = ValStr (val,sizeof(val),&fval);
    *fld[3] = NormStr (norm,sizeof(norm),&fnorm);
    *fld[4] = DevStr (fval,fnorm);
    }
  }

#define ANZABW  9
static char *devstrs[ANZABW] = {
  "- *** >",
  "- ***",
  "- **",
  "- *",
  "",
  "+ *", 
  "+ **",
  "+ ***",
  "+ *** >"
  };

LPSTR mNum::DevStr (double fval,double fnorm)
  {
  if ((fval < 1.0E9) && (fnorm < 1.0E9) && 
      (Par()->hd.par_Size >= sizeof(mNum_param))) {
    float FAR *stddev = (float FAR *) m.ReadlData (Par()->stddev);
    if ((stddev != NULL) && (*stddev > float(1.0E-3))) {
      double dev = (fval - fnorm) / double(*stddev);
      int abw = ((dev < 0.0) ? ( - int(- dev)) : int (dev)) + 4;
      abw = max(0,min(abw,ANZABW-1));
      return devstrs[abw];
      }
    }
  return devstrs[ANZABW / 2];     // Nix..
  }

static LPSTR pFloat (LPSTR buffer,int size,double v)
  {
#ifdef UEBERLEGT
  buffer[size-1] = '\0';
  LPSTR h = buffer + size - 2;
  LONG i = LONG(fabs (v) * 10.0) ;
  for ( int j = 0 ; j < size - 1; j++) {
    *h -- = char (i % 10) + '0';
    i /= 10 ;
    if (j == 0)
      *h-- = '.' , j++ ;
    if ((i == 0) && (j >= 2)) {
      if (v < 0.0)
        *h-- = '-' ;
      break ;
      }
    }
  return ++h ;
#else
  char localstring[20];
  sprintf (localstring,"%.1f",v);
  lstrncpy (buffer,localstring,size);
  return buffer;
#endif
  }

LPSTR mNum::ValStr (LPSTR buffer,int size,float FAR *v)
  {
  float FAR *x = (float FAR *) m.ReadlData (Par()->val);
  if ((x != NULL) && (*x < 1.0E9))
    return pFloat (buffer,size,*v = *x);
  else {
    *v = float(1.0E10) ,
    buffer[0] = '\0';
    return buffer;
    }
  }

LPSTR mNum::NormStr (LPSTR buffer,int size,float FAR *n)
  {
  float FAR *x = (float FAR *) m.ReadlData (Par()->norm);
  if ((x != NULL) && (*x < 1.0E9))
    return pFloat (buffer,size,*n = *x);
  else {
    *n = float(1.0E10) ,
    buffer[0] = '\0';
    return buffer;
    }
  }

void mNum::Load ()
  {
  GetOrigin ();   // Berechnen der Position
  if (doShow) {
    GetFields ();   // Erzeugen der Felder (die werden aus jeden Fall erzeugt)
    SetText ();
    if (Run == 0) {
      LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
      RECT r;
      fld[0]->Reformat ();
      fld[0]->GetFullFieldRect (&r,ErsteSeite());
      // Die richtige Hoehe berechnen (da sichs jetzt entscheidet,
      // wieviel Zeilen benoetigt werden)
      height = r.bottom - r.top ;
      if (IsHeadLine ()) {
        // yl auch berechnen
        yl = y0 + height + m.GetConstInt((*lpps)->ryspcHeight) / 2 ;
        height += m.GetConstInt((*lpps)->ryspcHeight) ;
        }
      // vert. Linienpositionen berechnen
      xl = x0 + m.GetConstInt((*lpps)->rnamWidth) + m.GetConstInt((*lpps)->runionWidth);
      xe = xl + 3 * m.GetConstInt((*lpps)->rxWidth) ;
      }
    else {
      // Die Hoehe von der ersten Ueberlagerung uebernehmen
      LPMNUM FAR *first = (LPMNUM FAR *) 
          m.ReadData (Par()->hd.ObjRec,Par()->hd.ObjId);
      DBWIN_ASSERT((first != NULL) && (*first != NULL)) ;
      height = (* first)->height;
      // vert. Linienpositionen berechnen
      LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
      xl = x0 ;
      xe = xl + 3 * m.GetConstInt((*lpps)->rxWidth) ;
      if (IsHeadLine ()) 
        // yl auch berechnen
        yl = y0 + height - m.GetConstInt((*lpps)->ryspcHeight) +
                           m.GetConstInt((*lpps)->ryspcHeight) / 2 ;
      }
    }
  else
    DelFields ();
  Initialized = TRUE ;
  }

void mNum::SetConnection ()
  {
  m.SetlOtherConnection (Par()->prevObj,Offset());
  m.SetlConnection (Par()->doShow,Offset());
  m.SetlConnection (Par()->Name,Offset());
  if (!IsHeadLine ())
    m.SetlConnection (Par()->val,Offset()),
    m.SetlConnection (Par()->norm,Offset());
  if (Run == 0) {
    // Auf AnzRecs eine Connection setzen
    LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
    m.SetlConnection (m.GetConstInt((*lpps)->rAnzRows),Offset());
    }
  }

void mNum::Reset (BOOL doClear)
  {
  m.ClearlOtherConnection (Par()->prevObj,Offset());
  m.ClearlConnection (Par()->doShow,Offset());
  m.ClearlConnection (Par()->Name,Offset());
  if (!IsHeadLine ())
    m.ClearlConnection (Par()->val,Offset()),
    m.ClearlConnection (Par()->norm,Offset());
  if (Run == 0) {
    // Auf AnzRecs eine Connection setzen
    LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
    m.ClearlConnection (m.GetConstInt((*lpps)->rAnzRows), Offset());
    }
  DelFields ();
  }

void mNum::Reformat (BOOL forPrinter)
  {
  GetOrigin ();
  int x = x0 ;
  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  int xs = m.GetConstInt((*lpps)->rxspcWidth);
  BOOL firstDone = FALSE ;
  for (int i = 0 ; i < 5 ; i ++) {
    if (fld [i] != NULL) {
      POINT pt;
      pt.x = x + ((i != 0) ? xs : 0) ;
      pt.y = y0 ;
      *fld[i] = pt;
      fld[i]->Reformat ((forPrinter) ? PrinterContext () : 0);
      if (!firstDone) {
        if (Run == 0) {
          RECT r;
          fld[0]->GetFullFieldRect (&r,ErsteSeite());
          // Die richtige Hoehe berechnen (da sichs jetzt entscheidet,
          // wieviel Zeilen benoetigt werden)
          height = r.bottom - r.top ;
          if (IsHeadLine ()) {
            // yl auch berechnen
            yl = y0 + height + m.GetConstInt((*lpps)->ryspcHeight) / 2 ;
            height += m.GetConstInt((*lpps)->ryspcHeight) ;
            }
          }
        else {
          LPMNUM FAR *first = (LPMNUM FAR *) 
              m.ReadData (Par()->hd.ObjRec,Par()->hd.ObjId);
          DBWIN_ASSERT((first != NULL) && (*first != NULL)) ;
          height = (* first)->height;
          // vert. Linienpositionen berechnen
          LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
          if (IsHeadLine ()) 
            // yl auch berechnen
            yl = y0 + height - m.GetConstInt((*lpps)->ryspcHeight) +
                               m.GetConstInt((*lpps)->ryspcHeight) / 2 ;
          }
        firstDone = TRUE ;
        }
      int width;
      if (i == 0)
        width = m.GetConstInt((*lpps)->rnamWidth) ;
      else if (i == 1)
        width = m.GetConstInt((*lpps)->runionWidth) ;
      else
        width = m.GetConstInt((*lpps)->rxWidth) ;
      x += width;
      }
    }
  GetMinMax ();
  }

void mNum::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  for (int i = 0 ; i < 5 ; i++) {
    if (fld[i] != NULL) {
      fld[i]->SetScale (scale,MapType);
      fld[i]->SetVOrg (xp,yp,ErsteSeite());
      fld[i]->SetWOrg (x0,y0);
      }
    }
  }

void mNum::StartExternPaint ()
  {
  for (int i = 0 ; i < 5 ; i++) {
    if (fld[i] != NULL)
      fld[i]->StartExternPaint ();
    }
  }

void mNum::EndExternPaint ()
  {
  for (int i = 0 ; i < 5 ; i++) {
    if (fld[i] != NULL)
      fld[i]->EndExternPaint ();
    }
  }

BOOL mNum::IsToActivate ()
  {
  return ((!IsHeadLine ()) && (Run == 0) && (doShow));
  }

BOOL mNum::IsActive ()
  {
  return (m.act_obj() == this);
  }

void mNum::Update ()
  {
  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  if ((m.IsUpdatelFromEle (Par()->prevObj)) && (m.UpdateEleCount() == 1)) {
    // Reine Verschiebung
    GetOrigin ();
    int x = x0 ;
    int xs = m.GetConstInt((*lpps)->rxspcWidth);
    for (int i = 0 ; i < 5 ; i ++) {
      if (fld [i] != NULL) {
        POINT pt;
        pt.x = x + ((i != 0) ? xs : 0) ;
        pt.y = y0 ;
        *fld[i] = pt;
        int width;
        if (i == 0)
          width = m.GetConstInt((*lpps)->rnamWidth) ;
        else if (i == 1)
          width = m.GetConstInt((*lpps)->runionWidth) ;
        else
          width = m.GetConstInt((*lpps)->rxWidth) ;
        x += width;
        }
      }
    }
  if ((m.IsUpdatelFromEle (m.GetConstInt((*lpps)->rAnzRows))) && 
      (UpdateEleCount() == 1)) {
    // Updatecount hat sich geaendert -> Nur ein Getminmax muss gemacht werden
    }
  else {
    // Da muss etwas mehr gemacht werden ...
    Load ();
    }
  }

void NeedScroll (NeedScroll_Info FAR *nsi,dllChild m);
void mNum::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate (Seite);
  if (bexplicit) {
    // linker oberer Punkt muss sichtbar sein
    RECT r;
    POINT pt[2];
    {
    PaintContext pcscreen;
    GetDocumentContext (&pcscreen,m);
    CopyRect (&r,(LPRECT)&pcscreen.cr);
  
    // Berechnen des Bildschirmkoordinaten
    LPRECT rcLogRect = GetLogRect (Seite);
    WIN_ASSERT (rcLogRect != NULL);
    pt[0].x = rcLogRect->left ;
    pt[0].y = rcLogRect->top ;
    pt[1].x = rcLogRect->right ;
    pt[1].y = rcLogRect->bottom ;

    LPtoDP (pcscreen.hDC,pt,2);
    }     // Invoke Destruktor for pcscreen

    InflateRect (&r,-10,-10);
    if ((!PtInRect (&r,pt[0])) || (!PtInRect (&r,pt[1]))) {
      if (pt[0].x > pt[1].x) {
        int dummy = pt[1].x ; pt[1].x = pt[0].x ; pt[0].x = dummy ;
        }
      int dx,dy ;
      if (pt[0].x < r.left)          dx = pt[0].x - r.left ;
      else if (pt[1].x > r.right) {
        dx = pt[1].x - r.right ;
        if (pt[0].x - dx < r.left) dx = 0 ;   // Durch die Verschiebung wuerde das linke
                                              // Eck wieder verschwinden. Dann verzichte 
                                              // ich lieber gleich
        }
      else                           dx = 0 ;

      if (pt[0].y < r.top)           dy = pt[0].y - r.top ;
      else if (pt[1].y > r.bottom)   dy = pt[1].y - r.bottom ;
      else                           dy = 0 ;

      NeedScroll_Info nsi;
      nsi.pt.x = dx ;
      nsi.pt.y = dy ;
      nsi.Seite = Seite ;
      NeedScroll (&nsi,m);
      }
    }
  if (m.GetExtraData (DED_GAUSSWIN) != NULL)
    ShowGauss ();
  }

void mNum::SetInActive (int Seite)
  {
  Invalidate (Seite);
  }

void mNum::Paint (PaintContext *pc, int Seite)
  {
  if (doShow) {
    // Zeichnen der Felder
    for (int i = 0 ; i < 5 ; i++) {
      if (fld[i] != NULL)
        fld[i]->Paint (pc->hDC,((pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)),Seite);
      }

    // Zeichnen der Linien
    int x = xl ;
    pc->diPen (diPen);
    LPRECT rcLogRect = GetLogRect (Seite);
    WIN_ASSERT (rcLogRect != NULL);
    for ( i = 0 ; i < 3 ; i++)
      *pc << Line (x,rcLogRect->top,x,rcLogRect->bottom) ,
      x += xw ;
    if (IsHeadLine ())
      *pc << Line (x0,yl,xe,yl);

    // Selektion
    if ((IsActive ()) && (pc->mode == DO_PAINT)) {
      HPEN hOldPen = (HPEN)SelectObject (pc->hDC,m.hActivePen());

      MoveToEx (pc->hDC,rcLogRect->left,rcLogRect->top, NULL);
      LineTo (pc->hDC,rcLogRect->right,rcLogRect->top);
      LineTo (pc->hDC,rcLogRect->right,rcLogRect->bottom);
      LineTo (pc->hDC,rcLogRect->left,rcLogRect->bottom);
      LineTo (pc->hDC,rcLogRect->left,rcLogRect->top);
      SelectObject (pc->hDC,hOldPen);
      }
    }
  }

BOOL mNum::OnChar (WORD wP, int)
  {
  if (wP == '\r') {
    ShowGauss ();
    return TRUE ;
    }
  return FALSE ;
  }

BOOL mNum::OnKeyDown (WORD wP, int)
  {
  BOOL res = FALSE ;
  if ((wP == VK_F1) &&
        (GetKeyState (VK_SHIFT) >= 0) &&
        (GetKeyState (VK_MENU) >= 0) &&
        (GetKeyState (VK_CONTROL) >= 0))
    ShowHelp () , res = TRUE ;
  return res;
  }

void mNum::ShowHelp ()
  {
  if (m.GetConstInt(Par()->rKontextNr) > 0)
    WinHelp (m.MyHandle(), "DDS.HLP", HELP_CONTEXT, m.GetConstInt(Par()->rKontextNr));
  else
    MessageBeep (0);
  }

BOOL mNum::GetGaussData (double FAR *val,double FAR *norm,double FAR *dev,int FAR *anz)
  {
  LPMNSIZE FAR *lpps = (LPMNSIZE FAR *) m.ReadlData (Par()->SizeDesc);
  DBINT FAR *anzrows = (DBINT FAR *) m.ReadlData ((*lpps)->rAnzRows);
  DBWIN_ASSERT(anzrows != NULL);
  int AnzRecs = *anzrows;

  int j = 0;
  BOOL correct = TRUE ;
  for (int i = 0 ; i < AnzRecs ; i++) {
    LPMNUM FAR *lpobj = (LPMNUM FAR *) m.ReadData (Par()->hd.ObjRec,
                                                    Par()->hd.ObjId);
    if ((lpobj != NULL) && (*lpobj != NULL) && ((*lpobj)->doShow)) {
      // Nur wenn das Objekt auch wirklich existiert, wird was getan
      ///////////////////////////////////////////////////////////////
      float FAR *lpval  = (float FAR *) m.ReadlData (Par()->val);
      if (correct = ((correct) && (lpval != NULL) && (*lpval < 1.0E9)))
        val[j] = *lpval ;
      float FAR *lpnorm = (float FAR *) m.ReadlData (Par()->norm);
      if (correct = ((correct) && (lpnorm != NULL) && (*lpnorm < 1.0E9)))
        norm[j] = *lpnorm ;
      float FAR *lpdev  = (float FAR *) m.ReadlData (Par()->stddev);
      if (correct = ((correct) && (lpdev != NULL) && (*lpdev < 1.0E9) && (*lpdev > 1.0E-3)))
        dev[j] = *lpdev ;
      j ++ ;
      }
    }
  *anz = j ;
  return correct;
  }

void mNum::ShowGauss ()
  {
#define MAXROWS 10
  double val[MAXROWS],norm[MAXROWS],dev[MAXROWS];
  int AnzRecs;
  if (GetGaussData (val,norm,dev,&AnzRecs)) {
    if (m.GetExtraData (DED_GAUSSWIN) == NULL) 
      m.CreateGaussWin ();
    LPSTR Name = LPSTR (m.ReadlData (Par()->Name));
    m.ShowGauss (val,norm,dev,AnzRecs,Name);
    }
  }

BOOL mNum::OnLButtonDown (WPARAM wP,int x,int y,int Seite)
  {
  LPRECT rcLogRect = GetLogRect (Seite);
  return ((rcLogRect != NULL) && (IsToActivate()) && (x >= rcLogRect->left) && (x < rcLogRect->right)
          && (y >= min(rcLogRect->top,rcLogRect->bottom)) 
          && (y <  max(rcLogRect->top,rcLogRect->bottom)));
  }

/////////////////////////////////////////////////////
// Implementierung der Klasse ActivationRegion
/////////////////////////////////////////////////////
void ActivationRegion::CallIt ()
  {
  m.ExCuteProc (Par()->procPtr,EM_LOAD);
  }

void ActivationRegion::Load ()
  {
  fpt FAR *p1 = (fpt FAR *) m.ReadlData (Par()->p1);
  fpt FAR *p2 = (fpt FAR *) m.ReadlData (Par()->p2);
  if ((p1 != NULL) && (p2 != NULL)) {
    x0 = m.WorldToLog (p1->x);
    y0 = m.WorldToLog (p1->y);
    x1 = m.WorldToLog (p2->x);
    y1 = m.WorldToLog (p2->y);
    Initialized = TRUE ;
    }
  if (Par()->MitMitRahmen()) {
    DBINT FAR *lpMitRand = (DBINT FAR *) m.ReadlData (Par()->mitRahmen);
    if (lpMitRand != NULL)
      mitUmrandung = *lpMitRand;
    }
  else
    mitUmrandung = 1 ;
  }

void ActivationRegion::Update ()
  {
  Load ();
  }

BOOL ActivationRegion::OnLButtonDown (WPARAM wP,int x,int y,int)
  {
  BOOL res = FALSE ;
  if (((LONG (x - x0) * LONG (x - x1)) < 0L) && 
      ((LONG (y - y0) * LONG (y - y1)) < 0L)) {
    if (Par()->MitClickPoint()) {
      fpt pt;
      m.Get_LogToWorld(&pt.x,x - x0);
      m.Get_LogToWorld(&pt.y,y - y0);
      m.WritelData(Par()->ClickPoint,&pt,sizeof(pt),NULL);
      }
    CallIt () , res = TRUE ;
    }
  return res;
  }

BOOL ActivationRegion::IsAct ()
  {
#ifdef SDOC
  FrmObjectList FAR *l;
  if (c->IsSmallDoc ())
    l = (FrmObjectList FAR *) (((sFormDoc *) c)->parent->ObjectList);
  else
    l = (FrmObjectList FAR *) (c->ObjectList);
  return ((l->act != NULL) && (l->act->obj == this));
#endif
  return (m.act_obj() == this);
  }

void ActivationRegion::Paint (PaintContext *pc, int Seite)
  {
  if (mitUmrandung != 0) {
    BOOL elIsAct;
    elIsAct = IsAct();
    if (elIsAct || (mitUmrandung == 1)) {
      HPEN hpn = (elIsAct) ? m.hActivePen() : m.hInactivePen() ;
      if (hpn) {
        HPEN oldpen = (HPEN)SelectObject (pc->hDC,hpn);
        MoveToEx (pc->hDC,x0,y0, NULL);
        LineTo (pc->hDC,x1,y0);
        LineTo (pc->hDC,x1,y1);
        LineTo (pc->hDC,x0,y1);
        LineTo (pc->hDC,x0,y0);
        SelectObject (pc->hDC,oldpen);
        }
      }
    }
  }

void ActivationRegion::GetMinMax ()
  {
  RECT rcLogRect;
  rcLogRect.left   = min(x0,x1) ;
  rcLogRect.right  = max(x0,x1) ;
  rcLogRect.top    = min(y0,y1) ;
  rcLogRect.bottom = max(y0,y1) ;
  SetLogRect (&rcLogRect,ErsteSeite());
  }

BOOL ActivationRegion::OnChar (WORD wP,int)
  {
  BOOL res = FALSE ;
  if (wP == ' ') {
    if (Par()->MitClickPoint())
      m.DellData(Par()->ClickPoint,NULL);
    CallIt () , res = TRUE ;
    }
  return res;
  }

void ActivationRegion::Reset(BOOL doClear)
  {
  m.ClearlConnection (Par()->p1,Offset());
  m.ClearlConnection (Par()->p2,Offset());
  }

void ActivationRegion::SetConnection()
  {
  m.SetlConnection (Par()->p1,Offset());
  m.SetlConnection (Par()->p2,Offset());
  }

BOOL ActivationRegion::IsToActivate ()
  {
  return TRUE ;
  }

void ActivationRegion::SetActive (int Seite, BOOL bexplicit)
  {
  Invalidate (Seite);
  if (bexplicit)
    ScrollInto ();
  }

void ActivationRegion::SetInActive (int Seite)
  {
  Invalidate (Seite);
  }

void ActivationRegion::SetInActiveIf (int Seite)
  {
  if (Initialized) {    // Da das IfActive manchmal falsch ist, sicherheitshalber das Initialized abgefragt
    DBWIN_ASSERT(Initialized);
    SetInActive(Seite);
    if (OnDeactivateProc != 0)
      m.ExCuteProc (OnDeactivateProc,EM_LOAD);
    IsActive = FALSE;
    }
  }

