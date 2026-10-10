//  Implementierung weiterer Objekte (speziell fuer Form)
//
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/frmobj/rev/frmobj5.cpv   1.19   16 Aug 1999 18:36:56   Hannes  $
//  $Log:   P:/marille/clinicum/frmobj/rev/frmobj5.cpv  $
// 
//    Rev 1.19   16 Aug 1999 18:36:56   Hannes
// Update bei Slant - Fields
// 
//    Rev 1.18   02 Feb 1999 21:29:32   Hannes
// SlantFieldHandling, Update auf die Position bei FrmStaticBitmap
// 
//    Rev 1.17   05 Oct 1998 11:21:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.16   08 Jun 1998 15:00:02   Martin
// FieldColor eingebaut
// 
//    Rev 1.15   01 Apr 1998 08:38:04   Gerhold
// LPCOLORREF fuer 16 Bit deklariert
// 
//    Rev 1.14   13 Mar 1998 17:21:30   Hannes
// 
//    Rev 1.13   08 Nov 1996 13:32:22   HANNES
// Zahlenformatierung
// 
//    Rev 1.12   10 Jun 1996 10:12:30   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.11   24 Mar 1996 12:11:50   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.10   02 Feb 1996 10:49:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   29 Nov 1995 11:15:34   GERHOLD
// StaticBitmap (SetConnection, Reset, Update)
// 
//    Rev 1.8   13 Sep 1995 19:39:38   GERHOLD
// Dokument ICON geaendert
// 
//    Rev 1.7   24 Aug 1995 00:15:02   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.6   26 Jun 1995 10:24:42   GERHOLD
// TransparentColor mit GetConstLong() lesen.
// 
//    Rev 1.5   11 Jun 1995 10:05:16   HANNES
// 
//    Rev 1.4   20 Mar 1995 12:13:58   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.3   15 Dec 1994 22:57:22   HANNES
// Vorzeichen in strtofloat
// 
//    Rev 1.2   17 Aug 1994 09:32:58   HANNES
// No change.
// 
//    Rev 1.1   05 Aug 1994 17:11:10   HANNES
// Kleine Aenderungen an PrgIcon, LoadDefIcon exportiert
// 
//    Rev 1.0   24 Jun 1994 16:45:46   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.8   19 Apr 1994 18:22:12   MARTIN
// ->par != NULL
// 
//    Rev 1.7   13 Apr 1994 20:53:26   MARTIN
// ordervtoobjects ...
// 
//    Rev 1.6   04 Feb 1994 16:47:06   HANNES
// Prototyp von ExCuteBlock, base initialisieren
// 
//    Rev 1.5   01 Feb 1994 15:17:56   MARTIN
// dc.h und scan.hpp entfernt
// 
//    Rev 1.4   26 Jan 1994 20:43:20   HANNES
// uSetDirKey... IsField()-> IsField() || IsCheckBox...
// 
//    Rev 1.3   12 Jan 1994 11:14:16   HANNES
// Unnoetige Includes entfernt
// 
//    Rev 1.2   09 Dec 1993 14:58:48   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.1   29 Nov 1993 09:03:52   MARTIN
// Includes fuer image verbessert
// 
//    Rev 1.0   28 Oct 1993 10:24:20   HANNES
// Initial revision.
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

#define MODULENUM     56
#include "winass.hpp"

#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "frmobj.hpp"
#include "winextra.hpp"
#define WITHINDDS
#define NODLL
#include "toolbar.hpp"

extern HINSTANCE hLibInst;

extern void SetCallback (FrmObject FAR *obj,cField FAR *f,dllChild m);


// Ersatzfunktion fuer SCHEISS Microsoft Library
BOOL strtofloat (LPSTR txt,float FAR *f)
  {
  *f = float(0.0);
  if (!*txt)
    return FALSE ;      // Da is nix zum scannen
  BOOL cFound = FALSE ;
  BOOL sFound = FALSE ;
  BOOL dFound = FALSE ;
  float sign = float(1.0) ;
  float ex = float(0.1) ;
  BOOL error = FALSE ;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt >= '0') && (*txt <= '9')) {
      if (cFound)
        *f += float (*txt - '0') * ex , ex *= float(0.1) ;
      else
        *f = *f * float(10.0) + float (*txt - '0') ;
      dFound = TRUE ;
      }
    else if ((*txt == '.') || (*txt == ',')) {
      if (cFound) 
        error = TRUE ;
      cFound = TRUE ;
      }
    else if ((*txt == '+') || (*txt == '-')) {
      if ((cFound) || (dFound) || (sFound))
        error = TRUE ;
      sFound = TRUE ;
      sign = (*txt == '-') ? float(-1.0) : float(1.0) ;
      }
    else
      error = TRUE ;
    }
  if (error)
    *f = float(0.0) ;
  else
    *f = *f * sign ;
  return !error;
  }


//////////////////////////////////////////////////////////////////////
//  Zeichnen von Icons (in der Datensatzliste)
//////////////////////////////////////////////////////////////////////
int PrgIcon::GetPictWidth ()
  {
  if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL))
    return int(pict.lpbi->bmiHeader.biWidth);
  else if ((type == ICONELE_ICON) && (pict.hico))
    return GetSystemMetrics (SM_CXICON);
  else
    return 32;
  }

int PrgIcon::GetPictHeight ()
  {
  if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL))
    return int(pict.lpbi->bmiHeader.biHeight / 2);
  else if ((type == ICONELE_ICON) && (pict.hico))
    return GetSystemMetrics (SM_CXICON);
  else
    return 32;
  }

WORD DIBNumColors (LPSTR pv)
  {
  int bits;
  LPBITMAPINFOHEADER lpbi;
  LPBITMAPCOREHEADER lpbc;

  lpbi = ((LPBITMAPINFOHEADER)pv);     // assume win 3.0 style DIBs
  lpbc = ((LPBITMAPCOREHEADER)pv);     // assume OS/2 style DIBs

  // With the BITMAPINFO format headers, the size of the palette
  // is in biClrUsed, whereas in the BITMAPCORE - style headers, it
  // is dependent on the bits per pixel ( = 2 raised to the power of
  // bits/pixel).

  if (lpbi->biSize != sizeof(BITMAPCOREHEADER)) {
    if (lpbi->biClrUsed != 0)
      return (WORD)lpbi->biClrUsed;
    bits = lpbi->biBitCount;
    }
  else
    bits = lpbc->bcBitCount;

  switch (bits) {
    case 1:
      return 2;
    case 4:
      return 16;
    case 8:
      return 256;
    default:
      // A 24 bitcount DIB has no color table
      return 0;
    }
  }

WORD PaletteSize (LPSTR pv)
  {
  LPBITMAPINFOHEADER lpbi;
  WORD NumColors;

  lpbi = (LPBITMAPINFOHEADER)pv;
  NumColors = DIBNumColors((LPSTR)lpbi);

  if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
     return NumColors * sizeof(RGBTRIPLE);
  else
     return NumColors * sizeof(RGBQUAD);
  }

void PrgIcon::Paint (PaintContext *pc, int Seite)
  {
  if ((pc->mode == DO_PAINT) || (pc->mode == DO_EXTDC)) {
    POINT pt;
    pt.x = x0l;
    pt.y = y0l;
    LPtoDP(pc->hDC,&pt,1);
    SaveDC (pc->hDC);
    pc->ResetMap ();
    if ((type == ICONELE_BITMAP) && (pict.lpbi != NULL)) {
      int pw = GetPictWidth();
      int ph = GetPictHeight();
      pict.lpbi->bmiHeader.biHeight /= 2;
      LPSTR bits = LPSTR(pict.lpbi) + *(LPDWORD)pict.lpbi + PaletteSize((LPSTR)pict.lpbi);

      DrawTransparentBitmap (pc->hDC, pict.lpbi, bits, pt.x, pt.y, RGB(255, 0, 255));

      pict.lpbi->bmiHeader.biHeight *= 2;
      }
    else if ((type == ICONELE_ICON) && (pict.hico)) {
      DrawIcon (pc->hDC,pt.x,pt.y,pict.hico);
      }
    RestoreDC (pc->hDC,-1);
    }
  }

void PrgIcon::SetConnection ()
  {
  m.SetlConnection (Par()->pt0,Offset());
  }

void PrgIcon::Reset (BOOL doClear)
  {
  m.ClearlConnection (Par()->pt0,Offset());
  }

void PrgIcon::Update ()
  {
  fpt FAR *pt0 = (fpt FAR *) m.ReadlData (Par()->pt0);
  DBWIN_ASSERT (pt0 != NULL);
  x0l = m.WorldToLog (pt0->x);
  y0l = m.WorldToLog (pt0->y);
  }

void PrgIcon::GetMinMax ()
  {
  PaintContext pc;
  GetDocumentContext (&pc,m);
  int x = pc.XPHYStoLOG (GetPictWidth()+1);
  int y = pc.YPHYStoLOG (GetPictHeight()+1);

  RECT rcLogRect ;
  rcLogRect.left   = x0l;
  rcLogRect.top    = y0l;
  rcLogRect.right  = x0l + x;
  rcLogRect.bottom = y0l + y;
  SetLogRect (&rcLogRect,ErsteSeite());
  }

static HICON hico;
DLLExport HICON _export WINAPI LoadDefIcon ()
  {
  if (hico == 0) {
    hico = (HICON)LoadIcon (hLibInst,"DOCICON");
    }
  return hico;
  }

void PrgIcon::Load ()
  {
  fpt FAR *pt0 = (fpt FAR *) m.ReadlData (Par()->pt0);
  DBWIN_ASSERT (pt0 != NULL);
  x0l = m.WorldToLog (pt0->x);
  y0l = m.WorldToLog (pt0->y);
  LPSTR prgName = LPSTR (m.ReadlData (Par()->prgName));
  DBWIN_ASSERT (prgName != NULL);

  LPSCRIPTCONTENT ent = GetScriptEntry(prgName);
  if (ent != NULL) {
    if (ent->IconData != NULL) {
      type = ICONELE_BITMAP ;
      pict.lpbi = LPBITMAPINFO (ent->IconData);
      }
    else {
      type = ICONELE_ICON ;
      pict.hico = LoadDefIcon();
      }
    }
  else {
    type = ICONELE_ICON ;
    pict.hico = LoadDefIcon();
    }
  Initialized = TRUE ;
  }


void FrmStaticBitmap::SetConnection ()
  {
  m.SetlConnection (Par()->ri, Offset());
  m.SetlConnection (Par()->rj, Offset());
  m.SetlConnection (Par()->org,Offset());
  }

void FrmStaticBitmap::Reset(BOOL Clear)
  {
  m.ClearlConnection (Par()->ri, Offset());
  m.ClearlConnection (Par()->rj, Offset());
  m.ClearlConnection (Par()->transparentColor,Offset());
  m.ClearlConnection (Par()->org,Offset());
  }

void FrmStaticBitmap::Update ()
  {
  Load ();
  }
  
void FrmStaticBitmap::Paint (PaintContext *pc, int Seite)
  {
  if ((pc->mode == DO_PAINT) || (pc->mode == DO_EXTDC)) {
    POINT pt;
    pt.x = x0l;
    pt.y = y0l;
    LPtoDP(pc->hDC,&pt,1);
    SaveDC (pc->hDC);
    pc->ResetMap ();

    DrawTransparentBitmap (pc->hDC, hbmp, pt.x, pt.y, 
                        xStart,yStart,bmpWidth,bmpHeight,
                        TransparentColor);

    RestoreDC (pc->hDC,-1);
    }
  }

#ifndef WIN32
typedef COLORREF FAR * LPCOLORREF;
#endif

void FrmStaticBitmap::Load ()
  {
  int AnzRows,AnzCols;
  hbmp = GetBitmap (Par()->pict,AnzRows,AnzCols);
  DBWIN_ASSERT ((AnzCols > m.GetConstInt(Par()->ri)) && (AnzRows > m.GetConstInt(Par()->rj)));
  BITMAP bi;
  GetObject (hbmp,sizeof(bi),&bi);
  bmpWidth  = bi.bmWidth  / AnzCols ;
  bmpHeight = bi.bmHeight / AnzRows ;
  xStart = bmpWidth * m.GetConstInt(Par()->ri);
  yStart = bmpHeight * m.GetConstInt(Par()->rj);
  fpt FAR *pt0 = (fpt FAR *) m.ReadlData (Par()->org);
  DBWIN_ASSERT (pt0 != NULL);
  x0l = m.WorldToLog (pt0->x);
  y0l = m.WorldToLog (pt0->y);
  Initialized = TRUE ;

  LPCOLORREF lpTransparentColor = LPCOLORREF (m.ReadlData (Par()->transparentColor));
  if (lpTransparentColor != NULL)
    TransparentColor = *lpTransparentColor;
  }

void FrmStaticBitmap::GetMinMax ()
  {
  PaintContext pc;
  GetDocumentContext (&pc,m);
  int x = pc.XPHYStoLOG (bmpWidth + 1);
  int y = pc.YPHYStoLOG (bmpHeight + 1);

  RECT rcLogRect;
  rcLogRect.left   = x0l;
  rcLogRect.top    = y0l;
  rcLogRect.right  = x0l + x;
  rcLogRect.bottom = y0l + y;
  SetLogRect (&rcLogRect,ErsteSeite());
  }

///////////////////////////////////////////////////
//  FrmSlantField: Schiefes Texteingabefeld
///////////////////////////////////////////////////
void FrmField::GetSlantField (int Format,WORD aR,WORD aI,float FAR *oA)
  {
  DBWIN_ASSERT(field == NULL);
  POINT pt;
  int width;
  if (Initialized = GetFldPos (&pt,&width)) {
    float FAR *a = (float FAR *) m.ReadData (aR,aI);
    if (a != NULL) {
      int MapType;
      m.GetDocInfo (GETMAPTYPE,0,&MapType);
      field = new sField (TRANSPARENT,Format,pt.x,pt.y,width,-1,FALSE,*a,MapType);
      SetCallback (this,field,m) ;
      field->SetWindow (m.MyHandle());
      field->SetScale (m_scale(),MapType);
      field->SetVOrg (m.xp(),m.yp(),ErsteSeite());
      if (MapType == MAPTYPE_GEOMETRIC) {
        POINT pt;
        m.GetDocInfo (GETWINDOWORG,0,&pt);
        field->SetWOrg (pt.x,pt.y);
        }

      if (FieldColor != 0xFFFFFFFF)
        field->SetOutColor (FieldColor);

      DBWIN_ASSERT(field != NULL);
      *oA = *a;
      }
    else
      Initialized = FALSE , *oA = float(1.0E10) ;
    }
  else
    *oA = float(1.0E10);
  }

void FrmField::CheckSlantField (WORD aR,WORD aI,float FAR *oA)
  {
  if (Initialized) {
    float FAR *a = (float FAR *) m.ReadData (aR,aI);
    if ((a == NULL) || (fabs (*a - *oA) > 0.1)) {
      delete field ;
      field = NULL ;
      }
    }
  }

void FrmField::FrmSlantUpdate (int Format,WORD aR,WORD aI,float FAR *oA)
  {
  CheckSlantField (aR,aI,oA);

  int nWidth;
  if (field != NULL) {
    POINT pt;
    if (Initialized = GetFldPos (&pt,&nWidth))
      *field = pt;
    else {
      delete field ;
      field = NULL ;
      }
    }
  else {
    GetSlantField (Format,aR,aI,oA);
    }
    
  if (Format != field->GetDefFormat())
    field->SetDefFormat (Format);
  if (nWidth != field->GetWidth()) 
    field->SetWidth (nWidth);

  SetText ();
  SetFieldMode (FM_NOSELECTION);

  if (field != NULL)
    field->Reformat ();
  }

void FrmSlantField::GetField ()
  {
  GetSlantField (m.GetConstInt(Par()->rFormat),APar()->aR,APar()->aI,&oldAng);
  }

void FrmSlantField::Load ()
  {
  GetField ();

  // Feld Aktivieren
  if (Initialized) {
    SetFieldMode (FM_NOSELECTION);
    // Und noch den Text hinmalen
    SetText ();
    }
  }

void FrmSlantField::SetConnection ()
  {
  FrmField::SetConnection ();
  m.SetConnection (APar()->aR,APar()->aI,Offset());
  }

void FrmSlantField::Reset (BOOL doClear)
  {
  FrmField::Reset (doClear);
  m.ClearConnection (APar()->aR,APar()->aI,Offset());
  }

void FrmSlantField::Update ()
  {
  FrmSlantUpdate (m.GetConstInt(Par()->rFormat),APar()->aR,APar()->aI,&oldAng);
  }

//////////////////////////////////////////////////////////////////
//  FrmSlantDec: Schiefes Dezimal Eingabefeld
//////////////////////////////////////////////////////////////////
void FrmSlantDec::GetField ()
  {
  GetSlantField (m.GetConstInt(Par()->rFormat),APar()->aR,APar()->aI,&oldAng);
  }

void FrmSlantDec::Load ()
  {
  GetField ();

  // Feld Aktivieren
  if (Initialized) {
    SetFieldMode (FM_NOSELECTION);
    // Und noch den Text hinmalen
    SetText ();
    }
  SetDecFieldMode();
  }

void FrmSlantDec::SetConnection ()
  {
  FrmDec::SetConnection ();
  m.SetConnection (APar()->aR,APar()->aI,Offset());
  }

void FrmSlantDec::Reset (BOOL doClear)
  {
  FrmDec::Reset (doClear);
  m.ClearConnection (APar()->aR,APar()->aI,Offset());
  }

void FrmSlantDec::Update ()
  {
  FrmSlantUpdate (m.GetConstInt(Par()->rFormat),APar()->aR,APar()->aI,&oldAng);
  SetDecFieldMode ();
  }

//////////////////////////////////////////////////////////////////
//  FrmDefDec: Dezimal Eingabefeld mit Defaultwert
//////////////////////////////////////////////////////////////////
void FrmDefDec::SetConnection ()
  {
  FrmDec::SetConnection ();
  m.SetConnection (DefPar()->defR,DefPar()->defI,Offset());
  m.SetConnection (DefPar()->flagR,DefPar()->flagI,Offset());
  }

void FrmDefDec::Reset (BOOL doClear)
  {
  FrmDec::Reset (doClear);
  m.ClearConnection (DefPar()->defR,DefPar()->defI,Offset());
  m.ClearConnection (DefPar()->flagR,DefPar()->flagI,Offset());
  }

void FrmDefDec::SetText ()
  {
  if (Initialized) {
    if (*fstring == '\0') {
      DBWIN_ASSERT(DPar()->fld.hd.par_Size == sizeof (Frm_DefDefDec));
      lstrcpy (fstring,LPSTR (m.ReadData(DPar()->prfRec,
                              DPar()->prfId)));
      }
    float val;
    WORD FAR *flg = (WORD FAR *)
      m.ReadData (DefPar()->flagR,DefPar()->flagI);
    if ((flg == NULL) || !*flg) {
      float FAR *v = (float FAR *)
        m.ReadData (DefPar()->defR,DefPar()->defI);
      if (v == NULL)
        val = float(1.0E10);
      else
        val = *v;
      float FAR *actval = (float FAR *) 
            (m.ReadData(Par()->DataRec,Par()->DataId));
      if ((val < 1.0E9) &&
              ((actval == NULL) || (fabs(*actval - val) > 1.0E-3)))
        m.WriteData (Par()->DataRec,Par()->DataId,
                            &val,sizeof(float),Offset());
      else {
        if ((val > 1.0E9) && (actval != NULL))
          m.DelData (Par()->DataRec,Par()->DataId,
                            Offset());
        }
      }
    else {
      float FAR *v = (float FAR *)
        m.ReadData (Par()->DataRec,Par()->DataId);
      if (v == NULL)
        val = float(1.0E10);
      else
        val = *v;
      }
    char ftext[128];
    char fs[16];
    lstrcpy (fs,fstring);
    *ftext = '\0';
    if (val < 1.0E9)
      sprintf (ftext,fs,val);
    *field = ftext;
    }
  }

void FrmDefDec::SetInActive (int Seite)
  {
  SetText ();  // auf jeden Fall Text ausgeben
  FrmField::SetInActive (Seite);
  if ((IsSchiebe()) && (m.schd()->Type == CHWND_FORM))
    m.DestroySchiebeLehre ();
  }

void FrmDefDec::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  float res;
  char txt[128];
  lstrncpy (txt,LPSTR(GlobalLock (hGtmp)),sizeof(txt));
#ifdef SCHEISS_MICROSOFT
  if (sscanf(txt,"%f",&res) != 1) {
#else
  if (!strtofloat(txt,&res)) {
#endif
    m.DelData (Par()->DataRec,Par()->DataId,
                Offset());
    }
  else {
    m.WriteData (Par()->DataRec,Par()->DataId,
                        &res,sizeof(res),Offset());
    WORD flg = TRUE;
    m.WriteData (DefPar()->flagR,DefPar()->flagI,
                        &flg,sizeof(WORD),Offset());
    }
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  }

void FrmDefDec::WorkOn (LPVOID Info)
  {
  m.DelData (DefPar()->flagR,DefPar()->flagI,Offset());
  SetText();
  Invalidate(m.ActSide());
  }

HDC FrmObject::PrinterContext ()
  {
#ifdef SDOC
  if (c->IsSmallDoc ())
    return ((sFormDoc *) c)->parent->Pr->PrinterDC ();
  else
#endif
    return m.Pr()->PrinterDC ();
  }

