/********************************************************/
/*      Malen in Fenstern                               */
/********************************************************/
// $Header:   F:/marille/clinicum/frmobj/rev/paint.cpv   1.16   06 Apr 2000 09:27:52   Hannes  $
// $Log:   F:/marille/clinicum/frmobj/rev/paint.cpv  $
// 
//    Rev 1.16   06 Apr 2000 09:27:52   Hannes
// Scroll
// 
//    Rev 1.15   05 Oct 1998 11:22:18   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.14   02 Sep 1998 08:32:10   Gerhold
// MyLPtoDP wieder raus
// 
//    Rev 1.13   01 Sep 1998 16:26:46   Martin
// Rundung von MyLPtoDP
// 
//    Rev 1.12   01 Sep 1998 12:48:08   Hannes
// MyLPtoDP
// 
//    Rev 1.11   04 Aug 1998 17:57:08   Hannes
// Ambiguos Call to fabs
// 
//    Rev 1.10   02 Jul 1998 11:46:54   Hannes
// Verbessertes Handling PS_NONE
// 
//    Rev 1.9   29 Jun 1998 19:53:40   Hannes
// 
//    Rev 1.8   27 Sep 1997 21:41:20   Martin
// PolyLineTo: PS_NONE nur ueberpruefen, wenn actdipen gueltig !!!!
// 
//    Rev 1.7   18 Aug 1997 18:05:24   Martin
// VTO Formular-faehig
// 
//    Rev 1.6   16 Jun 1997 07:48:44   Hannes
// >= PS_NONE...
// 
//    Rev 1.5   02 Feb 1996 10:49:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   24 Aug 1995 00:15:16   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.3   19 Oct 1994 11:40:46   GERHOLD
// 
//    Rev 1.2   27 Jun 1994 10:42:40   HANNES
// Inline Funktionen nicht mehr exportieren
// 
//    Rev 1.1   24 Jun 1994 20:43:00   MARTIN
// 
//    Rev 1.0   24 Jun 1994 16:45:48   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.13   14 Feb 1994 19:48:02   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.12   24 Sep 1993 22:42:04   HANNES
// Neuer Modus: DO_EXTERN
// 
//    Rev 1.11   22 Jul 1993 20:54:52   HANNES
// Linienfunktionen auch fuer cTool
// 
//    Rev 1.10   12 Jul 1993 07:54:40   HANNES
// Initialize von mit HDC...
// 
//    Rev 1.9   15 Jun 1993 12:19:02   MARTIN
// SelectObject vom alten Bitmap vor DeleteDc (bei operator << fuer Bitmap)
// 
//    Rev 1.8   28 May 1993 21:16:58   HANNES
// Punktierter und undurchsichtiger Stift
// 
//    Rev 1.7   03 May 1993 15:45:38   HANNES
// Erweiterungen bezueglich des Clipboards
// 
//    Rev 1.6   02 Apr 1993 17:42:00   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.5   24 Feb 1993 21:34:18   MARTIN
// Erweiterungen zum Erzeugen eines Memory-Kontextes
// 
//    Rev 1.4   17 Feb 1993 15:21:02   HANNES
// Korrekturen an dem Linienalgorytmus
// 
//    Rev 1.3   16 Feb 1993 13:49:02   HANNES
// Verbesserte Linientypen
// 
//    Rev 1.2   14 Feb 1993 15:56:24   HANNES
// Fontselektionen fuer beie Maptypes
// 
//    Rev 1.1   18 Dec 1992 12:46:42   HANNES
// LoadMetafile (return 0 im Fehlerfall (und nicht return irgendwas))
// 
//    Rev 1.0   02 Dec 1992 15:40:22   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "font.hpp"
#include "sc2d.hpp"
#define PAINT_MAIN
#include "paint.hpp"
#include "test.hpp"
#include "dds.h"
#include "globmem.h"

#define MODULENUM  6
#include "winass.hpp"

/*------< Attribute >------*/
void PaintContext::Attrib(WORD penident,WORD brushident)
  {
  // Selektion eines Standardpens
  if (penident != 0xFFFF) {
    HPEN hHelpPen;
    hHelpPen = (HPEN)SelectObject(hDC,GetStockObject(penident));
    if (hPen)  DeleteObject (hPen);
    if (hOldPen == 0) hOldPen = hHelpPen ;
    hPen = 0 ;
    actdiPen = 0xFFFFFFFF;
    }
  // Selektion eines Standardbrushes
  if (brushident != 0xFFFF) {
    HBRUSH hHelpBrush = (HBRUSH)SelectObject(hDC,GetStockObject(brushident));
    if (hOldBrush == 0) hOldBrush = hHelpBrush;
    }
  }

void PaintContext::Attrib(PENDATA pd,WORD brushident)
  {
  // Kreation und Selektion eines neuen Pens
  HPEN hHelpPen0,hHelpPen1;
  if (pd.style <= PS_INSIDEFRAME) {
    hHelpPen1 = (HPEN)SelectObject (hDC,
                hHelpPen0 = CreatePen (pd.style,pd.width,pd.color)
                             );
    actdiPen = 0xFFFFFFFF;
    if (hPen) DeleteObject (hPen);
    hPen = hHelpPen0 ;
    if (hOldPen == 0) hOldPen = hHelpPen1 ;
    }
  else
    actdiPen = 0xFFFFFFFE;
  // Selektion eines Standardbrushes
  if (brushident != 0xFFFF) {
    HBRUSH hHelpBrush = (HBRUSH)SelectObject(hDC,GetStockObject(brushident));
    if (hOldBrush == 0) hOldBrush = hHelpBrush;
    }
  }

int PaintContext::PenStyle(DWORD pdata)
  {
  return int (pdata >> 28) ;
  }

static inline int myround (double x)
  {
  if (x < 0.0) return int (x - 0.5);
  else         return int (x + 0.5);
  }

int PaintContext::PenWidth(DWORD pdata)
  {
  WORD w = WORD((pdata & 0x0F000000) >> 24);
  return myround(double(w) * logicalunits_per_halfpoint);
  }

int PaintContext::PenPhysWidth(DWORD pdata)
  {
  return XLOGtoPHYS (PenWidth(pdata));
  }

void PaintContext::GetPenInfo(DWORD dipen, WORD FAR *style, WORD FAR *width, DWORD FAR *color)
  {
  *style = WORD(PenStyle(dipen));
  *width = WORD(PenWidth(dipen));
//  *color = GetNearestColor (hDC, dipen & 0x00FFFFFF) ;
  *color = dipen & 0x00FFFFFF;
  if (((dipen & 0x00FFFFFF) != 0x00FFFFFF) && (*color == 0x00FFFFFF))
    *color = 0 ;
  if ((mode == DO_PRINT) && (*width > 0))
    *style = PS_INSIDEFRAME ;    // Der Drucker soll sich gefaelligst ein
                                 // bisschen bemuehen
  }

#define PS_NONE   7
void PaintContext::diPen(DWORD pdata)
  {
  // in pdata ist die Farbe, die device - Unabhaengige Dicke und 
  // der Stil kodiert
  WORD style, width;
  DWORD color;
  GetPenInfo(pdata, &style, &width, &color);
  Attrib(PENDATA(color, width, style)) ;
  if (style < PS_NONE)
    actdiPen = pdata;
  else
    actdiPen = 0xFFFFFFFE;
  }

/*--------< Private Hilfsfunktionen >------*/
void PaintContext::OldAttribs()
  {
  if (hOldPen)   SelectObject (hDC,hOldPen);
  if (hOldBrush) SelectObject (hDC,hOldBrush);
  if (hPen)      DeleteObject (hPen);
  }

void PaintContext::Initialize(HWND hw)
  {
  hWnd = hw ;
  GetClientRect (hWnd,(LPRECT)&cr);

  if (mode == DO_PAINT) 
    hDC  = BeginPaint(hWnd,(LPPAINTSTRUCT)&ps);
  else 
    hDC  = GetDC(hWnd);

    hOldPen = hPen = 0 ;
  hOldBrush = 0 ;
  x0 = y0 = 0 ;
  MapType = MAPTYPE_TEXT;
  logicalunits_per_halfpoint = float(1.0);
  }

void PaintContext::Initialize(PaintContext *pc)
  {
  mode = DO_MEMORY;
  hWnd = pc->hWnd ;
  GetClientRect(hWnd, (LPRECT)&cr);
  lmemcpy(&ps.rcPaint, &cr, sizeof(cr));
  hDC = CreateCompatibleDC(pc->hDC);
  hOldPen = hPen = 0 ;
  hOldBrush = 0 ;
  x0 = y0 = 0 ;
//  MapType = pc->MapType;
  MapType = MAPTYPE_TEXT;
  POINT dp[2];
  dp[0].x = dp[0].y = dp[1].y = 0;
  dp[1].x = int(pc->logicalunits_per_halfpoint * 1000.0);
  LPtoDP(pc->hDC, dp, 2);
  DPtoLP(hDC, dp, 2);
  logicalunits_per_halfpoint = float(fabs(double (dp[1].x - dp[0].x)) / 1000.0);
  }

/*-----< Konstruktoren >------*/
void PaintContext::GetContext(HWND hw,WORD penident,WORD brushident,int m)
  {
  mode = m;
  Initialize(hw);
  Attrib(penident,brushident);
  }

void PaintContext::GetContext(HWND hw,PENDATA pd,WORD brushident,int m)
  {
  mode = m;
  Initialize(hw);
  Attrib(pd,brushident);
  }

void PaintContext::GetContext(PaintContext *pc, WORD penident, WORD brushident)
  {
  Initialize(pc);
  Attrib(penident,brushident);
  }

void PaintContext::SetDC(HDC hExtDC)
  {
  hDC = hExtDC;
  hOldPen = hPen = 0 ;
  hOldBrush = 0 ;
  x0 = y0 = 0 ;
  MapType = MAPTYPE_TEXT;
  logicalunits_per_halfpoint = float(1.0);
  mode = DO_EXTDC;
  }

void PaintContext::GetContext(Printer *Pr)
  {
  // Paintcontext fuer Drucker herstellen
  hDC = Pr->PrinterDC ();
  mode = DO_PRINT ;      // DC muss durch ReleaseDC wieder freigegeben werden
  Pr->GetPrinterArea((LPRECT)&cr);
  lmemcpy (&ps.rcPaint,&cr,sizeof (cr));  // Auch rcPaint muss gueltig sein
  // Stifte u.s.w. freigeben
  hOldPen = hPen = 0 ;
  hOldBrush = 0 ;
  x0 = y0 = 0 ;
  ActPrt = Pr;
  }

PaintContext::PaintContext(HWND hw,WORD penident,WORD brushident,int m)
  {
  orientation = 0;
  GetContext(hw,penident,brushident,m);
  }

PaintContext::PaintContext(HWND hw,PENDATA pd,WORD brushident,int m)
  {
  orientation = 0;
  GetContext (hw,pd,brushident,m);
  }

PaintContext::PaintContext(PaintContext *pc, WORD penident, WORD brushident)
  {
  orientation = 0;
  GetContext(pc,penident,brushident);
  }

PaintContext::PaintContext(Printer *Pr)
  {
  orientation = 0;
  GetContext (Pr);
  }

PaintContext::PaintContext()
  { 
  mode = NO_MODE ; 
  orientation = 0 ; 
  }

void PaintContext::SetOrientation (int o)
  {
  orientation = o ;
  }

int PaintContext::GetOrientation (void)
  {
  return orientation ;
  }

/*-----< Destruktor >-------*/
void PaintContext::ReleaseContext()
  {
  if (mode != NO_MODE) {
    OldAttribs();
    if (mode == DO_PAINT)      
      EndPaint(hWnd,(LPPAINTSTRUCT)&ps);
    else if (mode == DO_WORK)  
      ReleaseDC (hWnd,hDC);
    else if (mode == DO_PRINT) 
      ActPrt->ReleasePrDC ();
    else if (mode == DO_MEMORY) 
      DeleteDC(hDC);
    }
  }

PaintContext::~PaintContext()
  {
  ReleaseContext ();
  }

/*-----< Mapping >-------*/
static double _scmap;
void PaintContext::Map(double scale,int xa,int ya,int xp,int yp)
  {
  SetMapMode (hDC,MM_ISOTROPIC);
  /* Fenster ist nun initialisert wie MM_LOMETRIC
     -> 1 Logische Einheit wird in 1/10 mm abgebildet, entspricht
     eim scale von 2.5 */
  // Berechnen des Aktuellen WindowExt
  if (mode != DO_EXTERN) {
    POINT ptHelp[2];
    ptHelp[0].x = 0    , ptHelp[0].y = 0 ;
    ptHelp[1].x = 1000 , ptHelp[1].y = 1000 ;
    DPtoLP (hDC,ptHelp,2);
    // Berechnung der gewuenschten WindowExt
    int dx = ptHelp[1].x - ptHelp[0].x ;
    int dy = ptHelp[1].y - ptHelp[0].y ;
    dx = (int) (fabs ((double) dx * 2.5 / scale)) ;
    dy = - (int) (fabs ((double) dy * 2.5 / scale)) ;
    SetWindowExtEx (hDC,dx,dy,NULL);
    SetViewportExtEx (hDC,1000,1000,NULL);
    SetWindowOrgEx (hDC,xa,ya,NULL);
    SetViewportOrgEx (hDC,xp,yp,NULL);
    _scmap = 1000.0 / double (dx);
    }
  else {
    SetWindowExtEx (hDC,1000,-1000,NULL);
    SetViewportExtEx (hDC,1000,1000,NULL);
    SetWindowOrgEx (hDC,xa,ya,NULL);
    SetViewportOrgEx (hDC,xp,yp,NULL);
    }
  x0 = xa , y0 = ya ;
  xvp = xp, yvp = yp;

  MapType = MAPTYPE_GEOMETRIC ;
  logicalunits_per_halfpoint = float(4.40972);
  }

void PaintContext::LogicalTwips(int xp,int yp,float fact)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int yLogPixels = GetDeviceCaps (hDC,LOGPIXELSY);
  SetMapMode (hDC,MM_ANISOTROPIC);
  SetWindowExtEx (hDC,int (1440 / fact),int (1440 / fact), NULL);
  SetViewportExtEx (hDC,xLogPixels,yLogPixels, NULL);
  SetViewportOrgEx (hDC,xp,yp, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  xvp = xp , yvp = yp ;

  MapType = MAPTYPE_TYPOGRAPHIC ;
  logicalunits_per_halfpoint = float(10.0);
  }

double PaintContext::GetLogStretch (void)
  {
  int xLogPixels = GetDeviceCaps (hDC,LOGPIXELSX);
  int xRes = GetDeviceCaps (hDC,HORZRES);
  int xwith = GetDeviceCaps (hDC,HORZSIZE);
  return double (xLogPixels) /           // = logische Anzahl Pixels pro Inch
                (double (xRes) / (double (xwith) / 25.4)) ;
  }

/*------< Hilfsfunktionen >-------*/
int PaintContext::XLOGtoPHYS(int xlog)
  {
  POINT ptHelp[2];
  ptHelp[0].x = 0 ,    ptHelp[0].y = 0;
  ptHelp[1].x = xlog , ptHelp[1].y = 0;
  LPtoDP (hDC,ptHelp,2);
  return ptHelp[1].x - ptHelp[0].x;
  }

int PaintContext::YLOGtoPHYS(int ylog)
  {
  POINT ptHelp[2];
  ptHelp[0].x = 0 , ptHelp[0].y = 0;
  ptHelp[1].x = 0 , ptHelp[1].y = ylog;
  LPtoDP (hDC,ptHelp,2);
  return ptHelp[1].y - ptHelp[0].y;
  }

int PaintContext::XPHYStoLOG(int xphys)
  {
  POINT ptHelp[2];
  ptHelp[0].x = 0 ,     ptHelp[0].y = 0;
  ptHelp[1].x = xphys , ptHelp[1].y = 0;
  DPtoLP (hDC,ptHelp,2);
  return ptHelp[1].x - ptHelp[0].x;
  }

int PaintContext::YPHYStoLOG(int yphys)
  {
  POINT ptHelp[2];
  ptHelp[0].x = 0 , ptHelp[0].y = 0;
  ptHelp[1].x = 0 , ptHelp[1].y = yphys;
  DPtoLP (hDC,ptHelp,2);
  return ptHelp[1].y - ptHelp[0].y;
  }

void PaintContext::LogRecttoPhys(RECT FAR *dest,RECT FAR *source)
  {
  POINT ptHelp[2];
  ptHelp[0].x = source->left   ;
  ptHelp[0].y = source->top    ;
  ptHelp[1].x = source->right  ;
  ptHelp[1].y = source->bottom ;
  LPtoDP (hDC,ptHelp,2);
  dest->left   = ptHelp[0].x ;
  dest->top    = ptHelp[0].y ;
  dest->right  = ptHelp[1].x ;
  dest->bottom = ptHelp[1].y ;
  }

void PaintContext::Scroll (int x,int y)
  {
  // Aufruf von ScrollWindow
  if (y < 0)
    y = -YLOGtoPHYS(-y);
  else
    y = YLOGtoPHYS(y);
  if (x < 0)
    x = -XLOGtoPHYS(-x);
  else
    x = XLOGtoPHYS(x);

  ScrollWindow (hWnd,x,y,NULL,NULL);

  // Update der WindowUrspruenge
  xvp += x ;
  yvp += y ;
  }

int PaintContext::XScroll (int x)
  {
  Scroll (x,0);
  return xvp ;
  }

int PaintContext::YScroll (int y)
  {
  Scroll (0,y);
  return yvp ;
  }

/*-------< Font's >--------*/

/*-------< Weitere Konstruktoren fuer Hilfsklassen >-------*/
PENDATA::PENDATA(WORD brush)
  {
  LOGBRUSH lgo ;
  GetObject (GetStockObject(brush),sizeof (LOGBRUSH),(LPSTR) &lgo);
  color = lgo.lbColor ;
  width = 1 ;
  style = PS_SOLID ;
  }

PENDATA::PENDATA(DWORD c,int w,WORD s) 
  { 
  color = c ,
  width = w , 
  style = s ; 
  }

PosStr::PosStr(char *txt,int x,int y,DWORD c,WORD b)
  {
  str = txt ;
  x0 = x , y0 = y ;
  fgc = c;
  if (b != 0xFFFF) {
    LOGBRUSH lgo ;
    GetObject (GetStockObject(b),sizeof (LOGBRUSH),(LPSTR) &lgo);
    fgb = lgo.lbColor ;
    }
  else fgb = 0xFFFFFFFF;
  }

GrayStr::GrayStr(char *txt,int x,int y,WORD b)
  {
  str = txt ;
  x0 = x , y0 = y ;
  bgb = b;
  }

ExtPosStr::ExtPosStr(char FAR *txt,int l,WORD fi,int x,int y,DWORD c,DWORD b,WORD a)
  {
  str = txt ;
  len = l ;
  FontIdent = fi;
  x0 = x , y0 = y ;
  fgc = c , bgc = b ;
  Align = a ;
  }

/*----------< Fonts >-----------------*/
/**************************************/
/*-----< frei definierter Font >------*/
void PaintContext::InsertFormat(WORD Ident,FontInfo *fi)
  {
  fntInsertFormat (Ident,fi);
  }

DLLExport UINT _export WINAPI GetFormatFlags (FontInfo FAR *fi)
  {
  UINT res = 0;
  
  if (fi->lf.lfWeight > 400) res |= FI_BOLD ;
  if (fi->lf.lfItalic)       res |= FI_ITALIC ;
  if (fi->lf.lfUnderline)    res |= FI_UNDERLINE ;
  if (fi->lf.lfStrikeOut)    res |= FI_STRIKEOUT ;

  return res ;
  }

DLLExport UINT _export WINAPI GetFormatFlags (LPFORMATINFO lfi)
  {
  return GetFormatFlags (&lfi->fi);
  }

DLLExport UINT _export WINAPI GetFormatFlags (int Format)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);
  UINT res = 0;
  if (lpf != NULL) 
    return GetFormatFlags (lpf);
  return res;
  }

void PaintContext::SelectFont (WORD id,int modifyer)
  {
  hFont = GetFontHandle (hWnd,MapType,id,modifyer,orientation);
  hOldFont = (HFONT)SelectObject (hDC,hFont);
  }

void PaintContext::GetFontExtraInfo (WORD id,FontExtraInfo FAR *fei)
  {
  fntGetFontExtraInfo (id,fei);
  }

void PaintContext::DeleteFormat (WORD id)
  {
  fntDeleteFormat (id);
  }

BOOL PaintContext::GetFormatFaceName (WORD id,LPSTR szName,int nSize)
  {
  return fntGetFormatFaceName (id,szName,nSize);
  }

BOOL PaintContext::GetFormatName (WORD id,LPSTR szName,int nSize)
  {
  return fntGetFormatName (id,szName,nSize);
  }

DWORD PaintContext::GetFormatColor (WORD id)
  {
  return fntGetFormatColor (id);
  }

DWORD PaintContext::GetFormatIvColor (WORD id)
  {
  return fntGetFormatIvColor (id);
  }

DLLExport void _export WINAPI DeleteFonts()
  {
  fntDeleteAllFormats ();
  }

/*----------< Ausgaben >--------------*/
PaintContext& PaintContext::operator << (RECT r)
  {
  Rectangle (hDC,r.left,r.top,r.right,r.bottom);
  return *this;
  }

PaintContext& PaintContext::operator << (Line l)
  {
  PolyMoveTo (l.pt0.x,l.pt0.y);
  PolyLineTo (l.pt1.x,l.pt1.y);
  return *this;
  }

PaintContext& PaintContext::operator << (Bitmap b)
  {
  /*------< Create a compatible Device Context >--------*/
  HDC hmDC = CreateCompatibleDC (hDC);
  /*------< Select the BitMap in it >----------*/
  HBITMAP oldBitmap = (HBITMAP)SelectObject (hmDC,b.hBitmap);
  /*------< Bring it to the Screen >---------*/
  BITMAP bm ;
  GetObject (b.hBitmap,sizeof (BITMAP),(LPSTR) &bm);
  if (b.width  == 0) b.width  = bm.bmWidth ;
  if (b.height == 0) b.height = bm.bmHeight ;
  if ((b.width != bm.bmWidth) || (b.height != bm.bmHeight)) {
    short oldMode = SetStretchBltMode(hDC,COLORONCOLOR);
    StretchBlt (hDC,b.pt.x,b.pt.y,
		b.width,
		b.height,
		hmDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
    SetStretchBltMode(hDC,oldMode);
    }
  else
    BitBlt (hDC,b.pt.x,b.pt.y,
		b.width,
		b.height,
		hmDC,0,0,SRCCOPY);
  /*------< All done for the moment >---------*/
  SelectObject (hmDC,oldBitmap);
  DeleteDC (hmDC);
  return *this ;
  }

PaintContext& PaintContext::operator << (PosStr p)
  {
  if (p.fgc != 0xFFFFFFFF) SetTextColor (hDC,p.fgc);
  if (p.fgb != 0xFFFFFFFF) SetBkColor (hDC,p.fgb);
  SetTextAlign (hDC,TA_BOTTOM | TA_CENTER);
  TextOut (hDC,p.x0,p.y0,p.str,strlen(p.str));
  return *this ;
  }

PaintContext& PaintContext::operator << (GrayStr p)
  {
  int len ;
  int cx,cy;
#ifdef WIN32
  SIZE size;
  GetTextExtentPoint32 (hDC,p.str,len = strlen(p.str), &size);
  cx = size.cx;
  cy = size.cy;
#else
  DWORD ext = GetTextExtent (hDC,p.str,len = strlen(p.str));
  cx = LOWORD(ext);
  cy = HIWORD(ext);
#endif
  GrayString (hDC,(HBRUSH)GetStockObject (p.bgb),NULL,
                (DWORD) (LPSTR) p.str,len,
                p.x0 - cx / 2,p.y0 - cy,0,0);
  return *this ;
  }

PaintContext& PaintContext::operator << (ExtPosStr p)
  {
  if (p.fgc != 0xFFFFFFFF) SetTextColor (hDC,p.fgc);
  if (p.bgc != 0xFFFFFFFF) SetBkColor (hDC,p.bgc);
  SetTextAlign (hDC,p.Align);
  
  // Selektion des Fonts in den Device - Kontext
  SelectFont (p.FontIdent);
  
  TextOut (hDC,p.x0,p.y0,p.str,p.len);
  SelectObject (hDC,hOldFont);

#ifdef PROTOKOLL
  POINT h[1] ;
  h[0].x = p.x0 , h[0].y = p.y0 ;
  LPtoDP (hDC,h,1);
  tp << "Text bei <" << h[0].x << ", " << h[0].y << ">\r\n" ;
#endif

  return *this ;
  }

DLLExport HANDLE _export WINAPI LoadMetaFile (char FAR *fname)
  {
  // Laden eines Metafiles (unter Beruecksichtigung der ominoesen 22 Bytes)
  HANDLE res = NULL;
  OFSTRUCT Of;
  int mfile = OpenFile (fname,&Of,OF_READ) ;
  if (mfile >= 0) {
#define MAXSIZE 0x0000FFFF
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND,MAXSIZE);
    char FAR *source = LPSTR(GlobalLock (hGtmp));
    WORD Size = _lread (mfile,source,MAXSIZE);
    // Test, ob Metafile wohl nicht corrupt ist
    METAHEADER FAR *hd = (METAHEADER FAR *) source ;
    if (hd -> mtHeaderSize != sizeof (METAHEADER) / 2) {
      // Probieren, 22 Byte hinter dem Beginn
      hd = (METAHEADER FAR *) (source + 22) ;                // !!! ??? !!!
      if (hd->mtHeaderSize == sizeof (METAHEADER) / 2) {
        Size -= 22 ;
        // Neuen Buffer anlegen, Kopieren ohne die 22 Byte
        GLOBALHANDLE hGtmp1 = GlobalAlloc (GHND,Size);
        source = LPSTR(GlobalLock (hGtmp1));
        lmemcpy (source,hd,Size);
        GlobalUnlock (hGtmp1);
        GlobalUnlock (hGtmp);
        GlobalFree (hGtmp);
        hGtmp = hGtmp1 ;        // In hGtmp wieder das Resultat
        }
      }
    else {
      // Realloc machen
      GlobalUnlock (hGtmp);
      GlobalReAlloc (hGtmp,Size,GMEM_MOVEABLE);
      }
    if (hGtmp) {

#ifdef WIN32
      res = SetMetaFileBitsEx (Size, (CONST BYTE *)hGtmp);
#else
      res = SetMetaFileBits (hGtmp);
#endif

      MtoF (hGtmp);
      }
    }
  return res ;
  }

// Mapping Modus zuruecksetzten
void PaintContext::ResetMap ()
  {
  SetMapMode (hDC,MM_TEXT);
  SetViewportOrgEx (hDC,0,0, NULL);
  SetWindowOrgEx (hDC,0,0, NULL);
  MapType = MAPTYPE_TEXT;
  logicalunits_per_halfpoint = float(1.0);
  }

// Lesen eines Bitmaps
HBITMAP PaintContext::ReadBitmap (RECT FAR *r)
  {
  int xwidth  = r->right - r->left + 1 ;
  int yheight = r->bottom - r->top + 1 ;
  HBITMAP hBitmap ;

  if ((xwidth > 0) && (yheight > 0)) {
    // Kreation eines Memory - Kontextes
    HDC hdcMem = CreateCompatibleDC (hDC);
    hBitmap = CreateCompatibleBitmap (hDC,xwidth,yheight);
    SelectObject (hdcMem,hBitmap);

    // Kopieren der Daten in den Hauptspeicher
    BitBlt (hdcMem,0,0,xwidth,yheight,
                  hDC,r->left,r->top,SRCCOPY);

    // Loeschen des Memory - Dev.Kontexts
    DeleteDC (hdcMem);
    }
  else
    hBitmap = 0 ;

  // fertig
  return hBitmap;
  }

// Schreiben eines Bitmaps
void PaintContext::DrawBitmap (HBITMAP hBitmap,RECT FAR *r)
  {
  int xwidth  = r->right - r->left + 1 ;
  int yheight = r->bottom - r->top + 1 ;

  if ((xwidth > 0) && (yheight > 0) && (hBitmap)) {
    // Kreation eines Memory - Kontextes
    HDC hdcMem = CreateCompatibleDC (hDC);
    SelectObject (hdcMem,hBitmap);

    // Kopieren der Daten in den Hauptspeicher
    BitBlt (hDC,r->left,r->top,xwidth,yheight,
                  hdcMem,0,0,SRCCOPY);

    // Loeschen des Memory - Dev.Kontexts
    DeleteDC (hdcMem);
    }
  }

//      Die entwas ausgefeilteren Linie
//////////////////////////////////////////////////////////////////
void PaintContext::PolyMoveTo (int x,int y)
  {
  xold = x ;
  yold = y ;
  lold = 0.0 ;
  state = 0 ;
  MoveToEx (hDC,x,y, NULL);
  }

typedef double (FAR * NEXTSTOP) (double FAR *,double,double,int FAR *);

#define STATE_LINE0     0
#define STATE_LINE1     2
#define STATE_SPACE0    1
#define STATE_SPACE1    3

static double llen,splen,lslen;
double NextDashed (double FAR *lold,double lact,double lges,int FAR *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = llen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }

double NextDotDashed (double FAR *lold,double lact,double lges,int FAR *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = llen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE1 ;
      break ;
    case STATE_LINE1 :
      dl = lslen - *lold ;
      *state = STATE_SPACE1 ;
      break ;
    case STATE_SPACE1 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }

double NextDot (double FAR *lold,double lact,double lges,int FAR *state)
  {
  double dl;
  int oldstate = *state;
  switch (*state) {
    case STATE_LINE0 :
      dl = splen - *lold ;
      *state = STATE_SPACE0;
      break;
    case STATE_SPACE0 :
      dl = splen - *lold ;
      *state = STATE_LINE0 ;
      break ;
    }
  if (lact + dl < lges) {
    lact += dl ;
    *lold = 0.0 ;
    }
  else {
    *lold += (lges - lact);
    lact = lges ;
    *state = oldstate ;
    }
  return lact;
  }

#define MAXLFNC 4
NEXTSTOP Nextl[MAXLFNC] = {
  NULL ,          // PS_SOLID
  NextDashed ,    // PS_DASHED
  NextDot ,       // PS_DOT
  NextDotDashed , // PS_DOTDASHED
  };

void PaintContext::PolyLineTo (int x,int y)
  {
  // Untersuchung, obs ueberhaupt noetig
  int Style = PenStyle(actdiPen) ;
#ifdef SO_ABER_AUCH_NICHT
  if (Style >= PS_NONE) return ;    // so nicht
#endif
  // PS_NONE gilt nur, wenn actdiPen gueltig !!!!
  if ((actdiPen != 0xFFFFFFFF) && (Style >= PS_NONE)) return ;
  if ((actdiPen != 0xFFFFFFFF) && (Style != PS_SOLID)) {
    double lact = 0.0 ;
    double dy = double (y - yold);
    double dx = double (x - xold);
    double lges = hypot (dx,dy);
    if ((Style >= MAXLFNC) || (Nextl[Style] == NULL))
      WIN_ASSERT(FALSE);
    // Berechnung der Laengen der Teilstuecke
    if (MapType == MAPTYPE_GEOMETRIC) {
      llen = 75.0 ;
      lslen = splen = 25.0 ;
      }
    else if (MapType == MAPTYPE_TYPOGRAPHIC) {
      llen = 170.08 ;
      lslen = splen = 56.69 ;
      }
    else {  // MAPTYPE_TEXT
      llen  = 75.0 * _scmap ;
      lslen = splen = 25.0 * _scmap ;
      }
    double w2 = double (PenWidth(actdiPen)) / 2.0 ;
    llen -= w2 ;
    lslen -= w2 ;
    splen += w2 ;
    if (lges >= 0.5) {
      for ( int i = state + 1 ; ; i++ ) {
        lact = (* Nextl[Style]) (&lold,lact,lges,&state);
        int xn = xold + myround (lact / lges * dx);
        int yn = yold + myround (lact / lges * dy);
        if (i & 0x01) LineTo (hDC,xn,yn); 
        else          MoveToEx (hDC,xn,yn, NULL);
        if (lact >= lges - 0.5) break ;
        }
      }
    }
  else
    LineTo (hDC,x,y);
  xold = x ; yold = y ;
  }

