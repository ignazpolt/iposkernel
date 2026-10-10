//
//  Implementierung der Image-Objekte
//
//  $Header:   P:/marille/clinicum/frmobj/rev/frmobj3.cpv   1.19   30 Nov 1998 10:33:54   Martin  $
//  $Log:   P:/marille/clinicum/frmobj/rev/frmobj3.cpv  $
// 
//    Rev 1.19   30 Nov 1998 10:33:54   Martin
// FrmImage reagiert jetzt wieder auf Updates auf den Dateinamen
// 
//    Rev 1.18   14 Apr 1998 20:16:02   Martin
// DefFrmRectImage erweitert
// 
//    Rev 1.17   18 Feb 1998 21:00:48   Hannes
// lpimgbg mit Seite
// 
//    Rev 1.16   15 Sep 1997 20:59:30   Hannes
// Bilder mit Blobs
// 
//    Rev 1.15   18 Aug 1997 18:05:32   Martin
// VTO Formular-faehig
// 
//    Rev 1.14   25 Apr 1997 12:32:50   Martin
// Bildkomrimierung
// 
//    Rev 1.13   10 Jun 1996 10:12:10   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.12   24 Mar 1996 12:11:26   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.11   02 Feb 1996 10:49:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   24 Aug 1995 00:15:10   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.9   20 Mar 1995 12:13:46   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
// 
//    Rev 1.8   15 Nov 1994 22:48:12   MARTIN
// Scanner...
// 
//    Rev 1.7   15 Nov 1994 15:30:22   MARTIN
// StoreImage korrigiert
// 
//    Rev 1.6   15 Nov 1994 12:12:02   MARTIN
// PutImage geaendert
// 
//    Rev 1.5   11 Nov 1994 17:31:44   MARTIN
// FrmRectImage
// 
//    Rev 1.4   10 Nov 1994 14:30:42   MARTIN
// top < bottom
// 
//    Rev 1.3   17 Oct 1994 15:00:20   HANNES
// Filename - Handling in FrmStoreimage provisorisch implementiert
// 
//    Rev 1.2   27 Jun 1994 10:47:42   HANNES
// Virtuelle Funktionen nicht mehr als inline
// 
//    Rev 1.1   24 Jun 1994 20:42:58   MARTIN
// 
//    Rev 1.0   24 Jun 1994 16:45:44   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.16   29 Apr 1994 14:42:40   MARTIN
// FrmGetImageFileName
// 
//    Rev 1.15   19 Apr 1994 18:21:32   MARTIN
// FrmGetImageScaleFact
// 
//    Rev 1.14   13 Apr 1994 20:53:12   MARTIN
// morphing
// 
//    Rev 1.13   10 Mar 1994 11:25:20   MARTIN
// Weichteil in Bild malen
// 
//    Rev 1.12   02 Mar 1994 21:01:24   MARTIN
// farbige Bilder
// 
//    Rev 1.11   09 Feb 1994 19:14:10   MARTIN
// Lampstate
// 
//    Rev 1.10   04 Feb 1994 16:53:48   MARTIN
// TWAIN sauberer
// 
//    Rev 1.9   12 Jan 1994 11:09:10   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.8   07 Jan 1994 12:12:52   HANNES
// WaitWin in die DLL verlegt -> Nur mehr die Caption der Wartefenstern den
// Filterproceduren uebergeben
// 
//    Rev 1.7   29 Nov 1993 08:51:46   HANNES
// Uberschrift bei Benutzerdefinierten Filtern, Verbesserung der Globalen
// Kontrastanpassung, Palettenhandling bei nicht mehr angezeigten Bildern
// 
//    Rev 1.6   18 Nov 1993 16:31:58   HANNES
// Loschen der Palette beim Ausschalten des Bildes
// 
//    Rev 1.5   18 Oct 1993 19:56:02   HANNES
// Doppeltes Include vermeiden
// 
//    Rev 1.4   22 Sep 1993 09:18:02   HANNES
// Version nach St. Poelten
// 
//    Rev 1.3   05 Sep 1993 22:12:14   HANNES
// Aufraeumarbeiten..
// 
//    Rev 1.2   25 Aug 1993 16:00:44   MARTIN
// Filterfunktionen
// 
//    Rev 1.1   23 Aug 1993 19:05:26   MARTIN
// Image-Umstellung (FrmImage)
//
/////////////////////////////////////////////////////////////////////////
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
#include "globmem.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "image.hpp"
#define MODULENUM 34
#include "winass.hpp"
#define CARETHANDLING_DONE
#include "cfield.hpp"
#include "frmobj.hpp"
#include "frmobj3.hpp"

#define NOCOMPILE
#include "hash.hpp"
#include "compile.hpp"

DLLExport _export WINAPI FrmImage::FrmImage (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI TrcImage::TrcImage (LPVOID p,mdiChild *c) : FrmImage (p,c) { }
DLLExport _export WINAPI FrmRectImage::FrmRectImage (LPVOID p,mdiChild *c) : FrmImage (p,c) { }

#include "winextra.hpp"
#include "cutcont.hpp"

#include "trcobj.hpp"    // fuer RI_*

// Implementierung der Klasse FrmImage
///////////////////////////////////////////////
void FrmImage::Load ()
  {
  DBWIN_ASSERT(img == NULL);
  WORD mType = m.GetMType (MAKELONG (Par()->ImgRec,Par()->ImgId));
  if (mType != VAR_BLOB) {
    LPSTR imgname = (LPSTR)m.ReadData(Par()->ImgRec,Par()->ImgId);
    GLOBALHANDLE hnewDIB = NULL;
    if ((imgname != NULL) && (*imgname != '\0'))
      hnewDIB = GetImage(imgname);
    if (Initialized = (hnewDIB != NULL)) {
      img = new mImage();
      img->SetDIB(hnewDIB, NULL);
      lstrcpy(lastStoredFileName,imgname);
      }
    else
      *lastStoredFileName = '\0';
    }
  else {
    BlobDesc FAR *imgname = (BlobDesc FAR *)m.ReadData(Par()->ImgRec,Par()->ImgId);
    GLOBALHANDLE hnewDIB = NULL;
    if ((imgname != NULL) && (imgname->hGmem))
      hnewDIB = GetImage(imgname->Size,imgname->hGmem);
    if (Initialized = (hnewDIB != NULL)) {
      img = new mImage();
      img->SetDIB(hnewDIB, NULL);
      LastStorehGMem = imgname->hGmem;
      // lstrcpy(lastStoredFileName,imgname);
      }
    else
      LastStorehGMem = NULL;
    }
  GetImgRect ();
  }

BOOL FrmImage::OnStartScan (LPSTR source,
                            float FAR *left,
                            float FAR *top,
                            float FAR *right,
                            float FAR *bottom,
                            float FAR *Resolution,
                            LPWORD Orientation,
                            LPWORD Pixeltype,
                            LPWORD Lampstate,
                            BOOL UserInterface,
                            WORD rdyRec,WORD rdyId,mdiChild *rdyMC)
  {
  if (m.ActScanPtr() == NULL) {
    ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
    if (StartScan(source,left,top,right,bottom,Resolution,
                  Orientation,Pixeltype,Lampstate,UserInterface)) {
      rdyR = rdyRec;
      rdyI = rdyId;
      rdyC = rdyMC;
      m.Set_ActScanPtr(LPVOID (this));
      return TRUE;
      }
    }
  return FALSE;
  }

void FrmImage::OnScanReady ()
  {
  ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
  GLOBALHANDLE hnewDIB = GetScannedImage();
  if (img != NULL) {
    img->ResetBMPs();
    Invalidate (m.ActSide());
    if (hnewDIB == NULL) {
      delete img;
      img = NULL;
      }
    }
  else {
    if (hnewDIB != NULL)
      img = new mImage();
    }

  if (Initialized = (img != NULL)) {
    img->SetDIB(hnewDIB);
    *lastStoredFileName = '\0';
    LastStorehGMem = NULL;
    GetImgRect ();
    }
  // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
  LPFRMOBJ obj = this;
  m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                &obj, sizeof(LPFRMOBJ), Offset());

  // auf jeden Fall Script benachrichtigen, dass Scannen beendet ist
  WORD flag = Initialized;
  // jetzt wirds trickreich: kurzeitig Objekt erzeugen, um ein
  // gueltiges dllChild zu bekommen:
  FrmObject FAR *f = new FrmObject(NULL,rdyC);
  f->m.WriteData(rdyR, rdyI, &flag, sizeof(flag), 0);
  delete f;

  if (Initialized) {
    GetMinMax ();
    LPRECT logr = GetLogRect (ErsteSeite());
    WIN_ASSERT (logr != NULL);
    m.Rescale (logr);
    Invalidate (m.ActSide());
    }
  m.Set_ActScanPtr(NULL);
  }

void FrmImage::ImportFile (LPSTR FileName)
  {
  ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
  GLOBALHANDLE hnewDIB = ImportImage(FileName);
  if (img != NULL) {
    img->ResetBMPs();
    Invalidate (m.ActSide());
    if (hnewDIB == NULL) {
      delete img;
      img = NULL;
      }
    }
  else {
    if (hnewDIB != NULL)
      img = new mImage();
    }

  if (Initialized = (img != NULL)) {
    img->SetDIB(hnewDIB);
    *lastStoredFileName = '\0';
    LastStorehGMem = NULL;
    GetImgRect ();
    }
  // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
  LPFRMOBJ obj = this;
  m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                &obj, sizeof(LPFRMOBJ), Offset());
  if (Initialized) {
    GetMinMax ();
    LPRECT r = GetLogRect (m.ActSide());
    if (r != NULL)
      m.Rescale (r);
    Invalidate (m.ActSide());
    }
  }

void FrmImage::SetImage (GLOBALHANDLE hDIB)
  {
  ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
  GLOBALHANDLE hnewDIB = hDIB;
  if (img != NULL) {
    img->ResetBMPs();
    Invalidate (m.ActSide());
    if (hnewDIB == NULL) {
      delete img;
      img = NULL;
      }
    }
  else {
    if (hnewDIB != NULL)
      img = new mImage();
    }

  if (Initialized = (img != NULL)) {
    img->SetDIB(hnewDIB);
    *lastStoredFileName = '\0';
    LastStorehGMem = NULL;
    GetImgRect ();
    }
  // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
  LPFRMOBJ obj = this;
  m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                &obj, sizeof(LPFRMOBJ), Offset());
  if (Initialized) {
    GetMinMax ();
    LPRECT r = GetLogRect (m.ActSide());
    if (r != NULL)
      m.Rescale (r);
    Invalidate (m.ActSide());
    }
  }

void FrmImage::WriteBMP (LPSTR FileName)
  {
  ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
  if (img != NULL)
    img->WriteBMP(FileName);
  }

void FrmImage::StoreImage (LPVOID key, DWORD nameRef, LPVOID AddlInfo, int InfoSize, WORD CompressMode)
  {
  *lastStoredFileName = '\0';
  if (Initialized && (img != NULL) && (img->hwholeDIB != NULL)) {
    ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
    HFILE FAR *lpfh = (HFILE FAR *)nameRef;
    PutImage(*lpfh, img->hwholeDIB, AddlInfo, InfoSize, CompressMode);
    char FileName[64];
    GetImageFileName(FileName, key);
    lstrcpy(lastStoredFileName,FileName);
    }
  }

void FrmImage::StoreImage (LPVOID key, BlobDesc FAR *bd, LPVOID AddlInfo, int InfoSize, WORD CompressMode)
  {
  LastStorehGMem = NULL;
  if (Initialized && (img != NULL) && (img->hwholeDIB != NULL)) {
    ToBusyCursor();   // vorsichtshalber Sanduhr einschalten
    PutImage (&bd->hGmem,&bd->Size, img->hwholeDIB, AddlInfo, InfoSize, CompressMode);
    LastStorehGMem = bd->hGmem;
    }
  }

void FrmImage::GetImgRect ()
  {
  if (img != NULL) {
    Initialized = TRUE;
    RECT rcDIB;
    fpt   FAR *p     = (fpt   FAR *) m.ReadData (Par()->PtRec,Par()->PtId);
    float FAR *width = (float FAR *) m.ReadData (Par()->wRec ,Par()->wId);

    if ((p != NULL) && (width != NULL)) {
      img->GetDIBRect (&rcDIB);
      double htow = double (rcDIB.bottom - rcDIB.top + 1) /
                    double (rcDIB.right - rcDIB.left + 1) ; 
      int MapType;
      m.GetDocInfo (GETMAPTYPE,0,&MapType);
      if (MapType == MAPTYPE_GEOMETRIC)
        htow = -htow;
      ImgRect.left   = m.WorldToLog (p->x);
      ImgRect.right  = m.WorldToLog (p->x + *width) - 1;
      ImgRect.top    = m.WorldToLog (p->y);
      ImgRect.bottom = m.WorldToLog (p->y + *width * float (htow)) - 1;
      }
    else
      Initialized = FALSE ;
    }
  }

void FrmImage::GetMinMax ()
  {
  RECT rcLogRect;
  if (Initialized) {
    rcLogRect.left = ImgRect.left;
    rcLogRect.right = ImgRect.right;
    if (ImgRect.top < ImgRect.bottom) {
      rcLogRect.top = ImgRect.top;
      rcLogRect.bottom = ImgRect.bottom;
      }
    else {
      rcLogRect.top = ImgRect.bottom;
      rcLogRect.bottom = ImgRect.top;
      }
    InflateRect (&rcLogRect,1,1);
    }
  else
    SetRectEmpty (&rcLogRect);
  SetLogRect (&rcLogRect,ErsteSeite());
  SetImgBg ();
  }

void FrmImage::SetConnection()
  {
  m.SetConnection (Par()->ImgRec,Par()->ImgId,Offset());
  m.SetConnection (Par()->PtRec ,Par()->PtId ,Offset());
  m.SetConnection (Par()->wRec  ,Par()->wId  ,Offset());
  if (Par()->hd.par_Size >= sizeof(Frm_DefImage))
    m.SetlConnection (Par()->flags, Offset());
  }

void FrmImage::Reset(BOOL doClear)
  {
  m.ClearConnection (Par()->ImgRec,Par()->ImgId,Offset());
  m.ClearConnection (Par()->PtRec ,Par()->PtId ,Offset());
  m.ClearConnection (Par()->wRec  ,Par()->wId  ,Offset());
  if (Par()->hd.par_Size >= sizeof(Frm_DefImage))
    m.ClearlConnection (Par()->flags, Offset());
  if (img != NULL) {
    delete img;
    }
  RemoveImgBg ();
  }

void FrmImage::Update ()
  {
#ifdef UEBERLEGT
  $ funktioniert nicht mehr !
  if (m.IsUpdateFromEle(Par()->ImgRec,Par()->ImgId)) {
#endif
    WORD mType = m.GetMType (MAKELONG (Par()->ImgRec,Par()->ImgId));
    if (mType != VAR_BLOB) {
      LPSTR imgname = (LPSTR)m.ReadData(Par()->ImgRec,Par()->ImgId);
      if ((imgname == NULL) || (*imgname == '\0') ||
          (lstrcmp(lastStoredFileName,imgname))) {
        GLOBALHANDLE hnewDIB = NULL;
        if ((imgname != NULL) && (*imgname != '\0'))
          hnewDIB = GetImage(imgname);
        if (img != NULL) {
          img->ResetBMPs();
          if (hnewDIB == NULL) {
            delete img;
            img = NULL;
            }
          RemoveImgBg();
          }
        else {
          if (hnewDIB != NULL)
            img = new mImage();
          }
        if (Initialized = (img != NULL)) {
          img->SetDIB(hnewDIB, NULL);
          lstrcpy(lastStoredFileName,imgname);
          }
        else
          *lastStoredFileName = '\0';
        // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
        LPFRMOBJ obj = this;
        m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                      &obj, sizeof(LPFRMOBJ), Offset());
        }
      }
    else {
      BlobDesc FAR *imgname = (BlobDesc FAR *)m.ReadData(Par()->ImgRec,Par()->ImgId);
      if ((imgname == NULL) || (imgname->hGmem == NULL) ||
          (imgname->hGmem != LastStorehGMem)) {
        GLOBALHANDLE hnewDIB = NULL;
        if ((imgname != NULL) && (imgname->hGmem))
          hnewDIB = GetImage(imgname->Size,imgname->hGmem);
        if (img != NULL) {
          img->ResetBMPs();
          if (hnewDIB == NULL) {
            delete img;
            img = NULL;
            }
          RemoveImgBg();
          }
        else {
          if (hnewDIB != NULL)
            img = new mImage();
          }
        if (Initialized = (img != NULL)) {
          img->SetDIB(hnewDIB, NULL);
          LastStorehGMem = imgname->hGmem;
          }
        else
          LastStorehGMem = NULL;
        // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
        LPFRMOBJ obj = this;
        m.WriteData (ScriptParam->ObjRec, ScriptParam->ObjId,
                      &obj, sizeof(LPFRMOBJ), Offset());
        }
      }
    SetImgBg();
#ifdef UEBERLEGT
    }
#endif
  GetImgRect ();
  }

void FrmImage::SetImgBg ()
  {
  if ((Initialized) && (IsWindow(m.MyHandle()))) {
    LPIMGBG ib = LPIMGBG (m.GetExtraData (DED_IMGBG));
    if ((ib == NULL) || (ib->Id == Par()->hd.ObjId)) {
      ImgBackgnd i;
      i.Id = Par()->hd.ObjId;
      CopyRect (&i.r,LPRECT (&ImgRect));
      i.Seite = ErsteSeite();
      m.PutExtraData (DED_IMGBG,&i,sizeof(i));
      }
    }
  }

void FrmImage::RemoveImgBg ()
  {
  LPIMGBG ib = LPIMGBG (m.GetExtraData (DED_IMGBG));
  if ((ib != NULL) && (ib->Id == Par()->hd.ObjId))
    m.RemoveExtraData (DED_IMGBG);
  }

void FrmImage::Paint (PaintContext *pc,int Seite)
  {
  if (Initialized) {
    RECT rcWnd,rcDIB,rcView,rcViewDIB;
    CopyRect (&rcWnd,(LPRECT)&pc->cr);
    // Berechnung des DIB in Device Koordinaten
    POINT pthlp[2];
    pthlp[0].x = ImgRect.left ;
    pthlp[0].y = ImgRect.top ;
    pthlp[1].x = ImgRect.right ;
    pthlp[1].y = ImgRect.bottom ;
    LPtoDP (pc->hDC,pthlp,2);
    rcView.left   = pthlp[0].x ;
    rcView.top    = pthlp[0].y ;
    rcView.right  = pthlp[1].x ;
    rcView.bottom = pthlp[1].y ;
    // Berechnung des Fensters in DIB Koordinaten
    CopyRect (&rcViewDIB,&rcWnd);
    img->GetDIBRect (&rcDIB);
    CalcDIBKoords (&rcViewDIB,&rcDIB,&rcView);
//    BOOL doPrint = ((c->hDArea == NULL) || (!c->FormatForScreen));
//    if (doPrint) {
    if ((pc->mode == DO_PRINT) || (pc->mode == DO_EXTERN)) {
      img->SetLogRect (LPRECT (&ImgRect));
      img->Paint (pc->hDC,&rcWnd,&rcViewDIB,&rcView,TRUE);
      }
    else {
      SaveDC (pc->hDC);
      float lphold = pc->logicalunits_per_halfpoint ;
      int oldMapType = pc->MapType;
      pc->ResetMap ();
      HRGN ClpRgn = CreateRectRgn (rcView.left,rcView.top,
                                   rcView.right,rcView.bottom
                                  );
      SelectClipRgn (pc->hDC,ClpRgn);
      img->Paint (pc->hDC,&rcWnd,&rcViewDIB,&rcView);
      DeleteObject (ClpRgn);
      RestoreDC (pc->hDC,-1);
      pc->logicalunits_per_halfpoint = lphold;
      pc->MapType = oldMapType;
      }
    }
  }

void FrmImage::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  if (Initialized) {
    RECT rcWnd,rcDIB,rcView,rcViewDIB;
    GetClientRect (m.MyHandle(),&rcWnd);

    // Berechnung des DIB in Device Koordinaten
    PaintContext pc;
    GetDocumentContext (&pc,m);
    POINT pthlp[2];
    pthlp[0].x = ImgRect.left ;
    pthlp[0].y = ImgRect.top ;
    pthlp[1].x = ImgRect.right ;
    pthlp[1].y = ImgRect.bottom ;
    LPtoDP (pc.hDC,pthlp,2);
    rcView.left   = pthlp[0].x ;
    rcView.top    = pthlp[0].y ;
    rcView.right  = pthlp[1].x ;
    rcView.bottom = pthlp[1].y ;

    // Berechnung des Fensters in DIB Koordinaten
    CopyRect (&rcViewDIB,&rcWnd);
    img->GetDIBRect (&rcDIB);
    CalcDIBKoords (&rcViewDIB,&rcDIB,&rcView);

    pc.ResetMap ();
    img->MapChange (pc.hDC,&rcWnd,&rcViewDIB,&rcView);
    }
  SetImgBg ();
  }

void FrmImage::Reformat (BOOL forPrinter)
  {
  if (Initialized) {
    img->ResetBMPs();
    }
  }

BOOL FrmImage::ForceToBackground ()
  {
  return TRUE ;
  }

void TrcImage::GetImgRect ()
  {
  if (img != NULL) {
    Initialized = TRUE;
    fpt FAR *p = (fpt FAR *)m.ReadData(Par()->PtRec,Par()->PtId);
    float scfact;
    float FAR *fc = (float FAR *)m.ReadData(Par()->wRec,Par()->wId);
    if (fc != NULL) scfact = *fc ;
    else            scfact = float(1.0);

    if (p != NULL) {
      SCALEIMAGEINFO si;
      img->InitializeScale (&si,scfact);
      int x = m.WorldToLog (p->x);
      int y = m.WorldToLog (p->y);
      ImgRect.left   = si.LogRect.left   + x;
      ImgRect.right  = si.LogRect.right  + x;
      ImgRect.top    = si.LogRect.top    + y;
      ImgRect.bottom = si.LogRect.bottom + y;
      }
    else
      Initialized = FALSE ;
    }
  }

void FrmRectImage::GetImgRect ()
  {
  if ((img != NULL) && (img->hwholeDIB != NULL)) {
    Initialized = TRUE;
    fpt FAR *p1 = (fpt FAR *) m.ReadData (Par()->PtRec,Par()->PtId);
    fpt FAR *p2 = (fpt FAR *) m.ReadData (Par()->wRec ,Par()->wId);

    if ((p1 != NULL) && (p2 != NULL)) {
      LPDWORD lpflags;
      if (Par()->hd.par_Size >= sizeof(Frm_DefImage))
        lpflags = (LPDWORD)(m.ReadlData(Par()->flags));
      else
        lpflags = NULL;
      DWORD flags;
      if (lpflags != NULL)
        flags = *lpflags;
      else
        flags = 0L;

#ifdef ALTE_VERSION
      RECT rcDIB;
      img->GetDIBRect (&rcDIB);
      float wtoh = float (rcDIB.right - rcDIB.left + 1) /
                   float (rcDIB.bottom - rcDIB.top + 1);
      float w = p2->x - p1->x;
      float h = p2->y - p1->y;
      float wtohw = w / h;
      int MapType;
      m.GetDocInfo (GETMAPTYPE,0,&MapType);
      if (MapType == MAPTYPE_GEOMETRIC)
        wtohw = -wtohw;
      float dx, dy;
      if (wtoh < wtohw) {
        dx = (w - (wtoh * h)) / (float)2.0;
        dy = float(0.0);
        }
      else {
        dx = float(0.0);
        dy = (h - (w / wtoh)) / (float)2.0;
        }
      if (MapType == MAPTYPE_GEOMETRIC)
        dy = -dy;
      ImgRect.left   = m.WorldToLog (p1->x + dx);
      ImgRect.right  = m.WorldToLog (p2->x - dx) - 1;
      ImgRect.top    = m.WorldToLog (p1->y + dy);
      ImgRect.bottom = m.WorldToLog (p2->y - dy) - 1;
#endif

      // neue Version:
      float dx = p1->x;
      float dy = p1->y;
      float dx2 = p2->x;
      float dy2 = p2->y;
      RECT rmf;
      float LogicalUnitsPerMillimeter, negfact;
      int MapType;
      m.GetDocInfo (GETMAPTYPE,0,&MapType);
      if (MapType == MAPTYPE_GEOMETRIC)
        LogicalUnitsPerMillimeter = float(25.0),  negfact = float(1.0);
      else
        LogicalUnitsPerMillimeter = float(56.69291339), negfact = float(-1.0);
      BITMAPINFO FAR *lpbi = (BITMAPINFO FAR *) GlobalLock (img->hwholeDIB);
      rmf.top = rmf.left = 0 ;
      LONG XPelsPerMeter = lpbi->bmiHeader.biXPelsPerMeter;
      LONG YPelsPerMeter = lpbi->bmiHeader.biYPelsPerMeter;
      if (XPelsPerMeter == 0L) {
        if (YPelsPerMeter == 0L)
          XPelsPerMeter = 3936L;   // default: 100 dpi
        else
          XPelsPerMeter = YPelsPerMeter;
        }
      rmf.right =   int (double (lpbi->bmiHeader.biWidth) *
                        (LogicalUnitsPerMillimeter * 1000.0)
                          / double (XPelsPerMeter));
      if (YPelsPerMeter == 0L)
        YPelsPerMeter = XPelsPerMeter;
      rmf.bottom = -int (double (lpbi->bmiHeader.biHeight) *
                        (LogicalUnitsPerMillimeter * negfact * 1000.0)
                            / double (YPelsPerMeter));

      GlobalUnlock (img->hwholeDIB);
      ImgRect.left = rmf.left + int(dx);
      ImgRect.right = rmf.right + int(dx);
      if (ImgRect.left > ImgRect.right) {
        int width = ImgRect.left - ImgRect.right;
        ImgRect.left += width;
        ImgRect.right += width;
        }
      ImgRect.top = rmf.top + int(dy);
      ImgRect.bottom = rmf.bottom + int(dy);
      if (ImgRect.top > ImgRect.bottom) {
        int height = ImgRect.top - ImgRect.bottom;
        ImgRect.top += height;
        ImgRect.bottom += height;
        }
      // einpassen in Rechteck
      float w = float(fabs(float (ImgRect.right - ImgRect.left + 1)));
      float h = float(fabs(float (ImgRect.bottom - ImgRect.top + 1)));
      float wtoh = w / h;
      float ww = dx2 - dx;
      float hw = dy2 - dy;
      float wtohw = ww / hw;
      if (MapType == MAPTYPE_GEOMETRIC)
        wtohw = -wtohw;
      float ddx, ddy, ssx, ssy;
      if ((flags & (RI_LINKS | RI_RECHTS | RI_OBEN | RI_UNTEN)) ==
          (RI_LINKS | RI_RECHTS | RI_OBEN | RI_UNTEN)) {
        ddx = float(0.0);
        ddy = float(0.0);
        ssx = ww / w;
        ssy = hw / h;
        }
      else if ((flags & (RI_LINKS | RI_RECHTS)) ==
              (RI_LINKS | RI_RECHTS)) {
        ddx = float(0.0);
        if (flags & RI_OBEN)
          ddy = float(0.0);
        else if (flags & RI_UNTEN)
          ddy = hw - (ww / wtoh);
        else
          ddy = (hw - (ww / wtoh)) / (float)2.0;
        ssx = ww / w;
        ssy = ssx;
        }
      else if ((flags & (RI_OBEN | RI_UNTEN)) ==
              (RI_OBEN | RI_UNTEN)) {
        if (flags & RI_LINKS)
          ddx = float(0.0);
        else if (flags & RI_RECHTS)
          ddx = ww - (wtoh * hw);
        else
          ddx = (ww - (wtoh * hw)) / (float)2.0;
        ddy = float(0.0);
        ssy = hw / h;
        ssx = ssy;
        }
      else {
        if (wtoh < wtohw) {
          ssy = hw / h;
          ssx = ssy;
          ddy = float(0.0);
          if (flags & RI_LINKS)
            ddx = float(0.0);
          else if (flags & RI_RECHTS)
            ddx = ww - (wtoh * hw);
          else
            ddx = (ww - (wtoh * hw)) / (float)2.0;
          }
        else {
          ssx = ww / w;
          ssy = ssx;
          ddx = float(0.0);
          if (flags & RI_OBEN)
            ddy = float(0.0);
          else if (flags & RI_UNTEN)
            ddy = hw - (ww / wtoh);
          else
            ddy = (hw - (ww / wtoh)) / (float)2.0;
          }
        }
      if (MapType == MAPTYPE_GEOMETRIC)
        ddy = -ddy;
      ImgRect.left = int(((float(ImgRect.left) - dx) * ssx) + ddx + dx);
      ImgRect.right = int(((float(ImgRect.right) - dx) * ssx) + ddx + dx);
      ImgRect.top = int(((float(ImgRect.top) - dy) * ssy) + ddy + dy);
      ImgRect.bottom = int(((float(ImgRect.bottom) - dy) * ssy) + ddy + dy);
      }
    else
      Initialized = FALSE ;
    }
  }

