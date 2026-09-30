/*---------------------------------------------------------
**      
**              Zeichnen von Diagrammen
**
**-------------------------------------------------------*/
// $Header:   P:/marille/clinicum/rev/diagram.cpv   1.3   24 Oct 1997 08:37:28   Hannes  $
// $Log:   P:/marille/clinicum/rev/diagram.cpv  $
// 
//    Rev 1.3   24 Oct 1997 08:37:28   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.2   02 Feb 1996 10:35:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Sep 1994 11:33:48   HANNES
// Umstellung auf OutContext
// 
//    Rev 1.0   24 Jun 1994 17:04:16   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   23 Feb 1994 18:06:02   HANNES
// Abspeichern der Position
// 
//    Rev 1.4   13 Jan 1994 16:13:14   HANNES
// dfield inc. raus
// 
//    Rev 1.3   18 Aug 1993 10:25:36   HANNES
// leichte Ueberarbeitung
// 
//    Rev 1.2   18 Jun 1993 15:03:10   MARTIN
// GetWindowInst
// 
//    Rev 1.1   07 Jun 1993 18:42:18   HANNES
// WM_SYSCOMMAND -> wP & 0xFFF0
// 
//    Rev 1.0   02 Dec 1992 15:27:28   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"
#include "dds.h"
#include "ddsmsg.h"
#include "sc2d.hpp"
#include "font.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "diagram.hpp"

Diagram::~Diagram ()
  {
  // Loeschen aller Daten
  if (PaintParam != 0) GlobalFree (PaintParam);
  if (hDmem != 0) GlobalFree (hDmem);
  }

sDiag::~sDiag ()
  {
  }


// Berechnung der Skalierung, Achsenbeschriftungen ...
void CalcScParam (int imin,int imax,double dmin,double dmax,double *sc,double *offs)
  {
  *sc   = double (imax - imin) / (dmax - dmin);
  *offs = double (imax) - dmax * *sc ;
  }

extern int myround(double x);

static inline int myround (double x)
  {
  if (x < 0.0) return int (x - 0.5);
  else         return int (x + 0.5);
  }

int doScale (double val,double sc,double offs)
  {
  return myround (val * sc + offs) ;
  }

int GetValues (ValuePos *h,int min,int max,int len,double dmin,double dmax)
  {
  static float dxp [22] = {
    float(0.01) , float(0.02) , float(0.05) ,  float(0.1) ,   float(0.2) , 
    float(0.5) ,  float(1.0) ,  float(2.0) ,   float(5.0) ,   float(10.0) , 
    float(20.0) , float(50.0) , float(100.0) , float(200.0) , float(500.0) , 
    float(1000.0) , float(2000.0) , float(5000.0) , float(10000.0) , 
    float(20000.0) , float(50000.0) , float(100000.0)
    };
  double a = double (max - min) / (dmax - dmin);
  double b = double (min) - a * dmin ;
  min += len / 2 ;      // Platz am Rand lassen
  max -= len / 2 ;
  int maxvals = (max - min) / len - 1 ;
  if (maxvals < 0) maxvals = -maxvals ;
  double dx = (dmax - dmin) / maxvals ;
  for (int i = 0 ; i < sizeof(dxp) / sizeof(float) - 1 ; i++) {
    if ((fabs(dx) >= dxp[i]) && (fabs(dx) <= dxp[i+1])) {
      if (dx > 0.0) dx = dxp[i+1] ;
      else          dx = -dxp[i+1];
      break ;
      }
    }

  int start = int (dmin / dx) ;
  start -= 2 ;          // sicher ist sicher
  for (i = 0 ; ; start ++) {
    h[i].val = float (start * dx) ;
    int xact = int (h[i].val * a + b) ;
    if (xact > max) break ;
    if (xact > min) i++ ;
    }

  return i ;
  }

void Diagram::SetUpWData ()
  {
  if ((!Initialized) && ((xmax - xmin) > 0.01)) {
    int xvalheight,xvallen;
    int yvalheight,yvallen;
    DWORD hlp;
    int xlabelheight,xlabellen;
    int ylabelheight,ylabellen;

    double a,b;
    int xcent,ycent,dn,dn1;
    ValuePos hvalpos[30],FAR *vp;

    PaintContext pc(GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
    pc.LogicalTwips ();
    TEXTMETRIC tm;

    if (mode & (DS_XVALUES | DS_YVALUES)) {
      pc.SelectFont (int (DS_GETSCFORMAT(mode)));
      GetTextMetrics (pc.hDC,&tm);
      }

    /*--- Analyieren der X - Achsenbeschriftung ----*/
    if (mode & DS_XVALUES) {
      xvalheight = pc.YLOGtoPHYS (tm.tmHeight);
      xvallen    = pc.XLOGtoPHYS (tm.tmAveCharWidth * 5);
      }
    else xvalheight = xvallen = 0 ;

    /*--- Analyieren der Y - Achsenbeschriftung ----*/
    if (mode & DS_YVALUES) {
      yvalheight = pc.YLOGtoPHYS (tm.tmHeight);
      yvallen    = pc.XLOGtoPHYS (tm.tmAveCharWidth * 5);
      }
    else yvalheight = yvallen = 0 ;

    if ((XLOffs != 0) || (YLOffs != 0)) {
      pc.SelectFont (int (DS_GETLMFORMAT(mode)));
      GetTextMetrics (pc.hDC,&tm);
      }

    /*--- Analysieren des X AchsenNamens ---*/
    if (XLOffs != 0) {
      char FAR *xlabel = LPSTR (FixGlobalMem (hDmem,XLOffs));

      int cx, cy;
#ifdef WIN32
      SIZE size;
      hlp = GetTextExtentPoint32 (pc.hDC,xlabel,lstrlen(xlabel),&size);
      cx = size.cx;
      cy = size.cy;
#else
      hlp = GetTextExtent (pc.hDC,xlabel,lstrlen(xlabel));
      cx = LOWORD(hlp);
      cy = HIWORD(hlp);
#endif

      xlabellen = pc.XLOGtoPHYS(cx);
      xlabelheight = pc.YLOGtoPHYS(cy);
      ReleaseGlobalMem (xlabel,hDmem);
      }
    else xlabellen = xlabelheight = 0 ;

    /*--- Analysieren des Y AchsenNamens ---*/
    if (YLOffs != 0) {
      char FAR *ylabel = LPSTR (FixGlobalMem (hDmem,YLOffs));

      int cx, cy;
#ifdef WIN32
      SIZE size;
      hlp = GetTextExtentPoint32 (pc.hDC,ylabel,lstrlen(ylabel),&size);
      cx = size.cx;
      cy = size.cy;
#else
      hlp = GetTextExtent (pc.hDC,ylabel,lstrlen(ylabel));
      cx = LOWORD(hlp);
      cy = HIWORD(hlp);
#endif

      ylabellen = pc.XLOGtoPHYS(cx);
      ylabelheight = pc.YLOGtoPHYS(cy);
      ReleaseGlobalMem (ylabel,hDmem);
      }
    else ylabellen = ylabelheight = 0 ;

    /*--- Berechnung des wirklich zur Verfuegung stehenden Platzes ---*/
    RECT r;
    GetClientRect (GetOutData()->_MyHandle,&r);

    // Prinzipiellen Rand abziehen
    pc.Map (1.0);
    r.top    += -pc.YLOGtoPHYS (50);   // 2 mm
    r.bottom -= -pc.YLOGtoPHYS (50);
    r.left   += pc.XLOGtoPHYS (50);
    r.right  -= pc.XLOGtoPHYS (50);

    // Y - Achse
    if (ylabelheight != 0)      // Y Label verkleinert prinzipiell
      r.top += -pc.YLOGtoPHYS(50) + ylabelheight ;
    if (mode & DS_TIPUP)        // Spitze nach oben verkleinert prinzipiell
      r.top += -pc.YLOGtoPHYS(70);
    if (mode & DS_TIPDOWN)      // Spitze nach unten verkleinert prinzipiell
      r.bottom -= -pc.YLOGtoPHYS(70);
    
    CalcScParam (r.bottom,r.top,ymin,ymax,&a,&b);
    ycent = doScale (yc,a,b);
    // Korrektur von r.bottom
    dn = 0 ;
    if (mode & DS_XPARTDOWN) dn += -pc.YLOGtoPHYS(25) ;
    if (xvalheight != 0) dn += -pc.YLOGtoPHYS(50) + xvalheight ;
    if (xlabelheight != 0) dn += -pc.YLOGtoPHYS(50) + xlabelheight ;
    if (ycent + dn > r.bottom) {
      // Es muss korrigiert werden
      dn1 = r.bottom - ycent ;
      r.bottom -= (dn - dn1);
      }

    // X - Achse
    if (mode & DS_TIPRIGHT)
      r.right -= pc.XLOGtoPHYS(70);
    if (mode & DS_TIPLEFT)      // Spitze nach unten verkleinert prinzipiell
      r.bottom += pc.XLOGtoPHYS(70);

    // Korrektur von r.left
    dn = 0 ;    
    CalcScParam (r.left,r.right,xmin,xmax,&a,&b);
    xcent = doScale (xc,a,b);
    if (mode & DS_YPARTLEFT) dn += pc.XLOGtoPHYS(25);
    if (yvallen != 0) dn += pc.XLOGtoPHYS(50) + yvallen;
    if (xcent - dn < r.left) {
      dn1 = xcent - r.left ;
      r.left += (dn - dn1);
      }

    /*------ Bereich fertig berechnet -------*/
    // Berechnung der Beschriftung
    if (mode & DS_XVALUES) {
      if (hXValPos) {
        vp = (ValuePos FAR *) FixGlobalMem (hDmem,hXValPos);
        FreeGlobalMem (vp,&hDmem);
        hXValPos = 0 ;
        }
      if ((nXVals = GetValues (hvalpos,r.left,r.right,xvallen,xmin,xmax))
                                > 0) {
        vp = (ValuePos FAR *) GetGlobalMem (&hDmem,&hXValPos,sizeof(ValuePos) * nXVals);
        lmemcpy (vp,hvalpos,sizeof(ValuePos) * nXVals);
        }
      }
    if (mode & DS_YVALUES) {
      if (hYValPos) {
        vp = (ValuePos FAR *) FixGlobalMem (hDmem,hYValPos);
        FreeGlobalMem (vp,&hDmem);
        hYValPos = 0 ;
        }
      if ((nYVals = GetValues (hvalpos,r.bottom,r.top,yvalheight * 2,ymin,ymax))
                                > 0) {
        vp = (ValuePos FAR *) GetGlobalMem (&hDmem,&hYValPos,sizeof(ValuePos) * nYVals);
        lmemcpy (vp,hvalpos,sizeof(ValuePos) * nYVals);
        }
      }
    // fertig
    lmemcpy (&rWork,&r,sizeof(rWork));
    Initialized = TRUE ;
    }
  }

LONG Diagram::Paint (PaintContext *pc)
  {
  static DWORD CursorColor [] = {
    RGB(0xFF,0,0) ,
    RGB(0,0,0xFF) ,
    RGB(0xFF,0,0xFF) 
    } ;
  static DWORD LineColor [] = {
    RGB(0,0xFF,0) ,
    RGB(0xFF,0xFF,0) ,
    RGB(0x80,0x80,0x80) 
    } ;

  BOOL ready ;
  SetUpWData ();                        // Berechnen der einzelnen Daten
  if (Initialized) {
    SetMapMode (pc->hDC,MM_TEXT);         // Kein Mapping
    SetWindowOrgEx (pc->hDC,0,0, NULL);
    SetViewportOrgEx (pc->hDC,0,0, NULL);
    double xs,xo,ys,yo;
    int i,lb,le,xa,ya ;
    int colind ;
    ValuePos FAR *vp;
    PaintContext pchlp (GetOutData()->_MyHandle,0xFFFF,0xFFFF,DO_WORK);
    pchlp.Map (1.0);
    int ymm1 = -pchlp.YLOGtoPHYS (25);
    int xmm1 = pchlp.XLOGtoPHYS (25);

    CalcScParam (rWork.left,rWork.right,xmin,xmax,&xs,&xo);
    CalcScParam (rWork.bottom,rWork.top,ymin,ymax,&ys,&yo);
    int xcent = doScale (xc,xs,xo);
    int ycent = doScale (yc,ys,yo);
    char outtxt[10];
    POINT ptText;

    // Zeichnen der Achsen
    pc->Attrib (PENDATA(RGB(0,0,0)));
    if (mode & DS_XAXIS)
      *pc << Line (rWork.left,ycent,rWork.right,ycent);
    if (mode & DS_YAXIS)
      *pc << Line (xcent,rWork.bottom,xcent,rWork.top);

    // Zeichen der Achsenunterteilung
    if ((nXVals > 0) && ((mode & DS_XPARTUP) || (mode & DS_XPARTDOWN))) {
      vp = (ValuePos FAR *) FixGlobalMem (hDmem,hXValPos);
      if (mode & DS_XPARTUP) lb = ycent - ymm1 ;
      else                   lb = ycent ;
      if (mode & DS_XPARTDOWN) le = ycent + ymm1 ;
      else                     le = ycent ;
      for (i = 0 ; i < nXVals ; i++) {
        xa = doScale (vp[i].val,xs,xo);
        *pc << Line (xa,lb,xa,le);
        }
      ReleaseGlobalMem (vp,hDmem);
      }
    if ((nYVals > 0) && ((mode & DS_YPARTLEFT) || (mode & DS_YPARTRIGHT))) {
      vp = (ValuePos FAR *) FixGlobalMem (hDmem,hYValPos);
      if (mode & DS_YPARTLEFT) lb = xcent - xmm1 ;
      else                     lb = xcent ;
      if (mode & DS_YPARTRIGHT) le = xcent + xmm1 ;
      else                      le = xcent ;
      for (i = 0 ; i < nYVals ; i++) {
        ya = doScale (vp[i].val,ys,yo);
        *pc << Line (lb,ya,le,ya);
        }
      ReleaseGlobalMem (vp,hDmem);
      }

    /*------< Eigentliche Zeichnung >-------*/
    if (linefunc != NULL) {
      // Zeichnen einer Linie
      double dx = (xmax - xmin) / 50.0 ;
      ready = FALSE ;
      for (i = 0 ; !ready ; i++) {
        BOOL first = TRUE ;
        for (double xm = xmin ; ((xm < xmax) && (!ready)) ; xm += dx) {
          int xd = doScale (xm,xs,xo) ;
          double val = (*linefunc) (xm,PaintParam,i) ;
          if (val < 1.0E10) {
            int yd = doScale (val,ys,yo) ;
            if (first) {
              colind = (i < (sizeof(LineColor) / sizeof(DWORD))) ? i :
                                  (sizeof(LineColor) / sizeof(DWORD)) - 1 ;
              pc->Attrib (PENDATA(LineColor[colind]));
              MoveToEx (pc->hDC,xd,yd,NULL), first = FALSE;
              }
            else       LineTo (pc->hDC,xd,yd);
            }
          else ready = TRUE ;
          }
        }
      }

    if (cursorfunc != NULL) {
      double xdcur,ydcur ;
      ready = FALSE ;
      for (i = 0 ; !ready ; i++) {
        colind = (i < (sizeof(CursorColor) / sizeof(DWORD))) ? i :
                                  (sizeof(CursorColor) / sizeof(DWORD)) - 1 ;
        pc->Attrib (PENDATA(CursorColor[colind])) ;
        (* cursorfunc) (&xdcur,&ydcur,PaintParam,i);
        if (xdcur < 1.0E9) {
          int xicur = doScale (xdcur,xs,xo);
          int yicur = doScale (ydcur,ys,yo);
          *pc << Line (rWork.left,yicur,rWork.right,yicur);
          *pc << Line (xicur,rWork.top,xicur,rWork.bottom);
          }
        else
          ready = TRUE ;
        }
      }

    if (histofunc != NULL) {
      double x0,x1,y ;
      int xa,xb,ya,yb ;
      pc->Attrib(PENDATA(RGB(0,0,0),1,PS_SOLID));
      HBRUSH hBr[2] ;
      hBr[0] = CreateHatchBrush (HS_BDIAGONAL,RGB(0,0,0));
      hBr[1] = CreateHatchBrush (HS_FDIAGONAL,RGB(0,0,0));
      for (i = 0 ;  ; i++) {
        (* histofunc) (&x0,&x1,&y,i,PaintParam);
        if (x0 < 1.0E9) {
          SelectObject (pc->hDC,hBr[i%2]) ;
          xa = doScale (x0,xs,xo);
          ya = doScale (0.0,ys,yo);
          xb = doScale (x1,xs,xo);
          yb = doScale (y,ys,yo);
          Rectangle(pc->hDC,xa,ya,xb,yb);
          }
        else
          break ;
        }
      for (i = 0 ; i < 2 ; i++)
        DeleteObject (hBr[i]) ;
      }
  
    // Schreiben der Achsenwerte
    pc->LogicalTwips();
    pc->SelectFont (int (DS_GETSCFORMAT(mode)));
    if ((nXVals > 0) && (mode & DS_XVALUES)) {
      SetTextAlign (pc->hDC,TA_TOP | TA_CENTER);
      vp = (ValuePos FAR *) FixGlobalMem (hDmem,hXValPos);
      for (i = 0 ; i < nXVals ; i++) {
        xa = doScale (vp[i].val,xs,xo);
        sprintf (outtxt,"%.1f",vp[i].val);
        ptText.x = xa ;
        ptText.y = ycent + ymm1 * 2 ;
        DPtoLP (pc->hDC,&ptText,1);
        TextOut (pc->hDC,ptText.x,ptText.y,outtxt,lstrlen(outtxt));
        }
      ReleaseGlobalMem (vp,hDmem);
      }
    if ((nYVals > 0) && (mode & DS_YVALUES)) {
      SetTextAlign (pc->hDC,TA_BOTTOM | TA_RIGHT);
      vp = (ValuePos FAR *) FixGlobalMem (hDmem,hYValPos);
      TEXTMETRIC tm;
      GetTextMetrics (pc->hDC,&tm);
      for (i = 0 ; i < nYVals ; i++) {
        ya = doScale (vp[i].val,ys,yo);
        sprintf (outtxt,"%.1f",vp[i].val);
        ptText.x = xcent - xmm1 * 2 ;
        ptText.y = ya ;
        DPtoLP (pc->hDC,&ptText,1);
        TextOut (pc->hDC,ptText.x,ptText.y + tm.tmHeight / 2,outtxt,lstrlen(outtxt));
        }
      ReleaseGlobalMem (vp,hDmem);
      }
    }

  return 0L;
  }

void Diagram::SetPaintParam (GLOBALHANDLE PP)
  {
  if (PaintParam) GlobalFree (PaintParam);
  PaintParam = PP ;
  }

void Diagram::SetLineFunc (LINEFUNC lf)
  {
  linefunc = lf ;
  }

void Diagram::SetPointFunc (POINTFUNC pf)
  {
  pointfunc = pf ;
  }

void Diagram::SetHistoFunc (HISTOFUNC hf)
  {
  histofunc = hf ;
  }

void Diagram::SetCursorFunc (CURSORFUNC cf)
  {
  cursorfunc = cf ;
  }

void Diagram::SetDiagramMode (DWORD m)
  {
  mode = m ;
  }

void Diagram::SetAxValues (double x0,double x1,double y0,double y1,double xb,double yb)
  {
  xmin = x0 , ymin = y0 ;
  xmax = x1 , ymax = y1 ;
  xc = xb , yc = yb ;
  }

void Diagram::InvalidateWindow (void)
  {
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  }

void Diagram::Rescale (void)
  {
  InvalidateRect (GetOutData()->_MyHandle,NULL,TRUE);
  Initialized = FALSE ;
  }


/*-----------------------------------------------------*/
/*      Eigenstaendiges Fenster zur Darstellung        */
/*      von Histogrammen ...                           */
/*-----------------------------------------------------*/
sDiag::sDiag (HWND Not,WORD lstid,DWORD st,BOOL ah) : Diagram ()
  {
  Notify = Not;
  ListID = lstid;
  style = st;
  ActivateHandling = ah;
  }

/*-----< Kreation, Startet die Eingabe >-----*/
static LPVOID ActhMem;
void sDiag::Create (char *caption)
  {
  // Kreation des eigentlichen Fensters
  ActhMem = this;
  int sx = GetSystemMetrics (SM_CXSCREEN);
  int sy = GetSystemMetrics (SM_CYSCREEN);

  int x,y,w,h ;
  WindowPosDef FAR *wd = (WindowPosDef FAR *) 
                SendMessage (Notify,WMU_GETPREFPOS,PS_GAUSSWIN,0L);
  if (wd->x == CW_USEDEFAULT)
    x = sx / 2, y = sy / 7 , w = sx - sx / 2, h = sy / 2;
  else
    x = wd->x , y = wd->y , w = wd->w , h = wd->h ;
    
  GetOutData()->_scale = wd->scale ;
  GetOutData()->_MyHandle = CreateWindow ("DIAGWND",caption,style,
                                x,y,w,h,
                                WBase::hFrameWin, 0 , WBase::hInstance, NULL) ;

  }

void sDiag::StoreWPos (WORD wP)
  {
  storeprefpospar p;
  p.hWnd = GetOutData()->_MyHandle;
  p.scale = GetOutData()->_scale ;
  if (IsWindow(Notify))
    SendMessage (Notify,WMU_STOREPREFPOS,PS_GAUSSWIN,(LONG) (LPSTR) &p);
  }

DLLExport LONG _export FAR PASCAL sDiagWndProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal=0L;
  sDiag *pmdich = (sDiag *) GetWindowInst (hWnd);
  BOOL done = FALSE ;

  switch (msg) {
    case WM_CREATE:
      SetWindowLong(hWnd, GWL_HWINFO, LONG(ActhMem));
      pmdich = (sDiag *) ActhMem ;
      // DefaultHandler muss gueltig sein, wenn zusaetzliches WindowWord
      // gesetzt wurde
      pmdich->DefaultHandler_base = (FARPROC) DefWindowProc;
      break;

    case WM_MOVE:
      RetVal = DefWindowProc(hWnd, msg, wP, lP);
      break ;

    case WM_SIZE:
      if (pmdich != NULL)
        RetVal = pmdich->ChildProc (hWnd,msg,wP,lP,&done);
      if (!done)
        RetVal = DefWindowProc(hWnd, msg, wP, lP);
      if ((pmdich != NULL) && (pmdich->GetOutData()->_MyHandle)) pmdich -> Rescale ();
      break ;

    case WM_SYSCOMMAND:
      if (((wP & 0xFFF0) == SC_CLOSE) && (pmdich != NULL) && (pmdich->ActivateHandling)) {
        if (!GlobalDestroy) {
          PostMessage (WBase::hFrameWin,WM_COMMAND,MI_QUIT,0L);
          }
        break ;
        }
    default:

      if (pmdich)
        RetVal = pmdich->ChildProc (hWnd,msg,wP,lP,&done);
      if (!done)
        RetVal = DefWindowProc(hWnd, msg, wP, lP);

      break;
    }
  return RetVal ;
  }

LONG FAR PASCAL sDiag::SpcFnc (HWND hWnd,UINT msg,WPARAM wP,
                               LPARAM lP,BOOL *done)
  {
  LONG RetVal = 0L;
  switch (msg) {
    // Einige Funktionen muessen abgefangen werden
    case WMU_STATECHANGE :
      if (wP == IDC_DG_ABBRUCH) {
        PostMessage (Notify,WMU_CLOSEGAUSS,0,0L);
        *done = TRUE ;
        }
      break ;
    }
  return RetVal ;
  }
