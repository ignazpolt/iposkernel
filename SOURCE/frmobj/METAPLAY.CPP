/*------------------------------------------------------*/
/*      Verschiedene Spielarten mit Metafiles           */
/*------------------------------------------------------*/
// $Header:   P:/marille/clinicum/frmobj/rev/metaplay.cpv   1.3   05 Oct 1998 11:22:10   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/metaplay.cpv  $
// 
//    Rev 1.3   05 Oct 1998 11:22:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.2   17 Dec 1996 11:05:18   GERHOLD
// int -> short (32 Bit)
// 
//    Rev 1.1   02 Feb 1996 10:49:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:45:46   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.5   14 Jun 1993 17:28:02   HANNES
// Fehlerkorrektur in ScaledMetaOut: Systemresourcen wurden weniger
// (Reihenfolge diPen und SaveDC vertauscht)
// ausserdem: Stillegung von ChangeLogPen und ChangeLogBrush (Effizienz)
// 
//    Rev 1.4   28 May 1993 21:16:32   HANNES
// Einbau von PolyLineTo im EnumDrwRecord...
// 
//    Rev 1.3   03 May 1993 15:45:24   HANNES
// Tests mit Clipboard
// 
//    Rev 1.2   24 Feb 1993 21:31:56   MARTIN
// Korrektur von ChangeLogPen
// (bisher wurde Pen.width unabhaengig vom Mappingmode gesetzt)
// 
//    Rev 1.1   13 Jan 1993 17:28:22   MARTIN
// Metafile-Befehl META_SETROP2 in ScaledMetaOut() ignorieren
// 
//    Rev 1.0   02 Dec 1992 15:37:54   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
  #include <wingdi.h>
#endif

#include "dds32.h"
#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

extern HINSTANCE hLibInst, WBase_hInstance;

struct DrwRecordData {
  tr2 FAR *s;
  WORD tmode;
  WORD Pstyle;
  WORD Pwidth;
  DWORD Pcolor;
  DWORD BType;
  };
typedef DrwRecordData FAR *LPDRD;

/*---------< Prinzipiell nicht behandelte Funktionen >----------*/
/*

META_SETWINDOWORG	     
META_SETWINDOWEXT	     
META_SETVIEWPORTORG	     
META_SETVIEWPORTEXT	     
META_OFFSETWINDOWORG	     
META_SCALEWINDOWEXT	     
META_OFFSETVIEWPORTORG	     
META_SCALEVIEWPORTEXT	     
META_FLOODFILL		     
META_PIE		     
META_BITBLT		     
META_STRETCHBLT		     
META_EXCLUDECLIPRECT	     
META_INTERSECTCLIPRECT	     
META_SETSTRETCHBLTMODE	     
META_PATBLT		     
META_OFFSETCLIPRGN	     
META_ESCAPE		     
META_FILLREGION		     
META_FRAMEREGION	     
META_INVERTREGION	     
META_PAINTREGION	     
META_SELECTCLIPREGION	     
META_CHORD		     
META_SETDIBTODEV	     
META_POLYPOLYGON	     
META_DIBBITBLT		     
META_DIBSTRETCHBLT	     
META_DIBCREATEPATTERNBRUSH   
META_STRETCHDIB		     
META_CREATEBITMAPINDIRECT   
META_CREATEBITMAP	    
META_CREATEREGION	    


*/
/*---------< Prinzipiell behandelte Funktionen >----------------*/

/*

    ----< Funktionen mit Koordinaten >------
    case META_LINETO		     :
    case META_MOVETO		     :
    case META_ARC		     :
    case META_ELLIPSE		     :
    case META_RECTANGLE		     :
    case META_ROUNDRECT		     :
    case META_SETPIXEL		     :
    case META_TEXTOUT		     :
    case META_POLYLINE		     :
    case META_DRAWTEXT		     :
    case META_EXTTEXTOUT	     :
    case META_POLYGON		     :
    ----< Funktionen ohne Koordinaten >------
    case META_SETBKCOLOR	     :
    case META_SETBKMODE		     :
    case META_SETMAPMODE	     :
    case META_SETROP2		     :
    case META_SETRELABS		     :
    case META_SETTEXTCHAREXTRA	     :
    case META_SETTEXTCOLOR	     :
    case META_SETTEXTJUSTIFICATION   :
    case META_SAVEDC		     :
    case META_RESTOREDC		     :
    case META_SELECTOBJECT	     :
    case META_SETTEXTALIGN	     :
    case META_SETMAPPERFLAGS	     :
    case META_SELECTPALETTE	     :
    case META_REALIZEPALETTE	     :
    case META_ANIMATEPALETTE	     :
    case META_SETPALENTRIES	     :
    case META_RESIZEPALETTE	     :
    case META_DELETEOBJECT	     :
    case META_CREATEPALETTE	     :
    case META_CREATEBRUSH	     :
    case META_CREATEPATTERNBRUSH     :
    case META_CREATEPENINDIRECT	     :
    case META_CREATEFONTINDIRECT     :
    case META_CREATEBRUSHINDIRECT    :
    case META_SETPOLYFILLMODE	     :

*/

static void CheckKoords (LPMETARECORD lpMFR,int end,RECT FAR *r,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    if (short(lpMFR->rdParm[i*2+0+offs]) < r->bottom) 
      r->bottom = short(lpMFR->rdParm[i*2+0+offs]);
    if (short(lpMFR->rdParm[i*2+0+offs]) > r->top   ) 
      r->top    = short(lpMFR->rdParm[i*2+0+offs]);
    if (short(lpMFR->rdParm[i*2+1+offs]) < r->left  ) 
      r->left   = short(lpMFR->rdParm[i*2+1+offs]);
    if (short(lpMFR->rdParm[i*2+1+offs]) > r->right ) 
      r->right  = short(lpMFR->rdParm[i*2+1+offs]);
    }
  }

static void CheckniKoords (LPMETARECORD lpMFR,int end,RECT FAR *r,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    if (short(lpMFR->rdParm[i*2+1+offs]) < r->bottom) 
      r->bottom = short(lpMFR->rdParm[i*2+1+offs]);
    if (short(lpMFR->rdParm[i*2+1+offs]) > r->top   ) 
      r->top    = short(lpMFR->rdParm[i*2+1+offs]);
    if (short(lpMFR->rdParm[i*2+0+offs]) < r->left  ) 
      r->left   = short(lpMFR->rdParm[i*2+0+offs]);
    if (short(lpMFR->rdParm[i*2+0+offs]) > r->right ) 
      r->right  = short(lpMFR->rdParm[i*2+0+offs]);
    }
  }

/*---------< Ermitteln der Extremwerte in einem Metafile >-------*/
DLLExport int _export WINAPI EnumMaxInfo (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,RECT FAR *r)
  {
  // Bearbeitet Funktionen
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_LINETO		     :
    case META_MOVETO		     :
      CheckKoords (lpMFR,1,r);
      break ;
    case META_ARC		     :
      CheckKoords (lpMFR,4,r);
      break ;
    case META_ELLIPSE		     :
    case META_RECTANGLE		     :
      CheckKoords (lpMFR,2,r);
      break ;
    case META_ROUNDRECT		     :
      CheckKoords (lpMFR,3,r);
      break ;
    case META_SETPIXEL		     :
      CheckKoords (lpMFR,3,r,2);
      break;
    case META_TEXTOUT		     :
      CheckKoords (lpMFR,1,r,((lpMFR->rdParm[0]+1)>>1)+1);
      break ;
    case META_POLYGON                :
    case META_POLYLINE		     :
      CheckniKoords (lpMFR,lpMFR->rdParm[0],r,1);
      break ;
#ifndef WIN32
    case META_DRAWTEXT		     :
      CheckKoords (lpMFR,2,r,2);
      break ;
#endif
    case META_EXTTEXTOUT	     :
      CheckKoords (lpMFR,1,r);
      break ;
    default :
      break ;
    }
  return 1 ;            // Weiter gehts
  }

/*-----------< Berechnen der Minimal - Maximal Info >--------*/
void PaintContext::GetMaxInfo (HMETAFILE hMF,RECT FAR *r)
  {
  r->top    = r->right = -30000;        // top, right  -> maximum
  r->bottom = r->left  = 30000;         // bottom, top -> minimum
  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumMaxInfo,hLibInst);

  EnumMetaFile (hDC,hMF,MFENUMPROC(lpfnEnumMeta),LONG ((BYTE FAR *) r));

  FreeProcInstance (lpfnEnumMeta);
  }

/*-----------< Skalieren von Zeichenbefehlen >------------*/
static void TrKoords (LPMETARECORD lpMFR,int end,tr2 FAR *tr,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    fpt hlp;
    hlp.y = float (short(lpMFR->rdParm[i*2+0+offs]));
    hlp.x = float (short(lpMFR->rdParm[i*2+1+offs]));
    Sc2d (tr,&hlp,&hlp);
    * (short FAR *) (lpMFR->rdParm+i*2+0+offs) = short (hlp.y);
    * (short FAR *) (lpMFR->rdParm+i*2+1+offs) = short (hlp.x);
    }
  }

static void TrniKoords (LPMETARECORD lpMFR,int end,tr2 FAR *tr,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    fpt hlp;
    hlp.x = float (short(lpMFR->rdParm[i*2+0+offs]));
    hlp.y = float (short(lpMFR->rdParm[i*2+1+offs]));
    Sc2d (tr,&hlp,&hlp);
    * (short FAR *) (lpMFR->rdParm+i*2+0+offs) = short (hlp.x);
    * (short FAR *) (lpMFR->rdParm+i*2+1+offs) = short (hlp.y);
    }
  }

// void ChangeLogPen (HDC hDC,LPLOGPEN ll,LPDRD d)
//   {
//   if (d->tmode & TRANSLATE_PEN) {
//     ll->lopnStyle = d->Pstyle;
//     ll->lopnWidth.x = d->Pwidth;
//     ll->lopnColor = d->Pcolor;
//     }
//   }

// void ChangeLogBrush (HDC hDC,LPLOGBRUSH ll,LPDRD d)
//   {
//   if (d->tmode & TRANSLATE_BRUSH) {
//     ll->lbStyle = BS_SOLID;
//     ll->lbColor = GetNearestColor (hDC,(d->BType & 0x00FFFFFF));
//     ll->lbHatch = 0;
//     }
//   }

static PaintContext *actmpc;
DLLExport int _export WINAPI EnumDrwRecord (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,LPDRD d)
  {
  BOOL do_play = TRUE;
  GLOBALHANDLE hGtmp = GlobalAlloc (GHND,lpMFR->rdSize * sizeof (WORD));
  LPMETARECORD lptmp = (LPMETARECORD) GlobalLock (hGtmp);
  lmemcpy (lptmp,lpMFR,int (lpMFR->rdSize * sizeof (WORD)));

  // Bearbeitet Funktionen
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_LINETO		     :
    case META_MOVETO		     :
      TrKoords (lptmp,1,d->s);
      if (d->tmode & TRANSLATE_PEN) {
        if (lpMFR->rdFunction == META_MOVETO)
          actmpc->PolyMoveTo (lptmp->rdParm[0],lptmp->rdParm[1]);
        else
          actmpc->PolyLineTo (lptmp->rdParm[0],lptmp->rdParm[1]);
        do_play = FALSE ;
        }
      break ;
    case META_ARC		     :
      TrKoords (lptmp,4,d->s);
      break ;
    case META_ELLIPSE		     :
    case META_RECTANGLE		     :
      TrKoords (lptmp,2,d->s);
      break ;
    case META_ROUNDRECT		     :
      TrKoords (lptmp,3,d->s);
      break ;
    case META_SETPIXEL		     :
      TrKoords (lptmp,3,d->s,2);
      break;
    case META_TEXTOUT		     :
      TrKoords (lptmp,1,d->s,((lptmp->rdParm[0]+1)>>1)+1);
      break ;
    case META_POLYLINE		     :
    case META_POLYGON 		     :
      TrniKoords (lptmp,lptmp->rdParm[0],d->s,1);
      if (d->tmode & TRANSLATE_PEN) {
        actmpc->PolyMoveTo (lptmp->rdParm[1],lptmp->rdParm[2]);
        for (int i = 1 ; i < short (lptmp->rdParm[0]) ; i++) {
          actmpc->PolyLineTo (lptmp->rdParm[1 + i * 2],
                              lptmp->rdParm[2 + i * 2]
                             );
          }
        do_play = FALSE ;
        }
      break ;
#ifndef WIN32
    case META_DRAWTEXT		     :
      TrKoords (lptmp,2,d->s,2);
      break ;
#endif
    case META_EXTTEXTOUT	     :
      TrKoords (lptmp,1,d->s);
      break ;
    case META_CREATEPENINDIRECT	     :
//      ChangeLogPen (hDC,LPLOGPEN(&lptmp->rdParm[0]),d);
      if (d->tmode & TRANSLATE_PEN) {
        do_play = FALSE ;
        }
      break;
#ifndef WIN32
    case META_CREATEBRUSH	     :
      // ???? soviel ich gesehen habe, ist der Parameter auch ein 
      // Solid - Brush
#endif
    case META_CREATEBRUSHINDIRECT    :
//      ChangeLogBrush (hDC,LPLOGBRUSH(&lptmp->rdParm[0]),d);
      if (d->tmode & TRANSLATE_PEN) {
        do_play = FALSE ;
        }
      break;
    case META_SELECTOBJECT	     :
    case META_DELETEOBJECT	     :
      if (d->tmode & TRANSLATE_PEN) {
        do_play = FALSE ;
        }
      break ;
    case META_SETBKCOLOR	     :
    case META_SETBKMODE		     :
    case META_SETMAPMODE	     :
//    case META_SETROP2		     :     Zeichenmodus nicht aendern lassen
    case META_SETRELABS		     :
    case META_SETTEXTCHAREXTRA	     :
    case META_SETTEXTCOLOR	     :
    case META_SETTEXTJUSTIFICATION   :
    case META_SAVEDC		     :
    case META_RESTOREDC		     :
    case META_SETTEXTALIGN	     :
    case META_SETMAPPERFLAGS	     :
    case META_SELECTPALETTE	     :
    case META_REALIZEPALETTE	     :
    case META_ANIMATEPALETTE	     :
    case META_SETPALENTRIES	     :
    case META_RESIZEPALETTE	     :
    case META_CREATEPALETTE	     :
    case META_CREATEPATTERNBRUSH     :
    case META_CREATEFONTINDIRECT     :
    case META_SETPOLYFILLMODE        :
      break ;
    default :
      do_play = FALSE ;
      break ;
    }

  if (do_play) {
    // Zeichnen des Records
    PlayMetaFileRecord (hDC,lpHTable,lptmp,nObj);
    }

  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);

  return 1 ;            // Weiter gehts
  }

/*---< Ausgabe aller Daten, nachdem die Koordinaten skaliert werden >----*/
void PaintContext::ScaledMetaOut (HMETAFILE hMF,tr2 FAR *s,
                                  WORD TranslateMode,DWORD Pen,DWORD Brush)
  {
  actmpc = this;
  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumDrwRecord,hLibInst);

  DrwRecordData drd;
  drd.s = s;
  drd.tmode = TranslateMode ;
  if (drd.tmode & TRANSLATE_PEN)
    diPen (Pen);
  int nSave;
  if (mode != DO_EXTERN)
    nSave = SaveDC (hDC);
  GetPenInfo(Pen, &drd.Pstyle, &drd.Pwidth, &drd.Pcolor);
  drd.BType = Brush ;

  EnumMetaFile (hDC,hMF,MFENUMPROC(lpfnEnumMeta),LONG ((BYTE FAR *) &drd));

  if (mode != DO_EXTERN)
    RestoreDC (hDC,nSave);
  else
    SetMapMode (hDC,MM_ISOTROPIC);
  FreeProcInstance (lpfnEnumMeta);
  }


/*----< Ausgabe nur von 'unkritischen' Befehlen >------*/
DLLExport int _export WINAPI EnumFilterRecord (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,BYTE FAR *data)
  {
  BOOL do_play;

  // Bearbeitet Funktionen
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_LINETO		     :
    case META_MOVETO		     :
    case META_ARC		     :
    case META_ELLIPSE		     :
    case META_RECTANGLE		     :
    case META_ROUNDRECT		     :
    case META_SETPIXEL		     :
    case META_TEXTOUT		     :
    case META_POLYLINE		     :
#ifndef WIN32
    case META_DRAWTEXT		     :
#endif
    case META_EXTTEXTOUT	     :
    case META_SETBKCOLOR	     :
    case META_SETBKMODE		     :
    case META_SETMAPMODE	     :
    case META_SETROP2		     :
    case META_SETRELABS		     :
    case META_SETTEXTCHAREXTRA	     :
    case META_SETTEXTCOLOR	     :
    case META_SETTEXTJUSTIFICATION   :
    case META_SAVEDC		     :
    case META_RESTOREDC		     :
    case META_SELECTOBJECT	     :
    case META_SETTEXTALIGN	     :
    case META_SETMAPPERFLAGS	     :
    case META_SELECTPALETTE	     :
    case META_REALIZEPALETTE	     :
    case META_ANIMATEPALETTE	     :
    case META_SETPALENTRIES	     :
    case META_RESIZEPALETTE	     :
    case META_DELETEOBJECT	     :
    case META_CREATEPALETTE	     :
#ifndef WIN32
    case META_CREATEBRUSH	     :
#endif
    case META_CREATEPATTERNBRUSH     :
    case META_CREATEFONTINDIRECT     :
    case META_CREATEPENINDIRECT	     :
    case META_CREATEBRUSHINDIRECT    :
    case META_SETPOLYFILLMODE        :
    case META_POLYGON                :
      do_play = TRUE ;
      break ;
    default :
      do_play = FALSE ;
      break ;
    }

  if (do_play)
    // Zeichnen des Records
    PlayMetaFileRecord (hDC,lpHTable,lpMFR,nObj);

  return 1 ;            // Weiter gehts
  }

/*--------< Darstellung von Metafiles >---------*/
PaintContext& PaintContext::operator << (MetaDesc m)
  {
  HMETAFILE hmf = 0;
  char szfilename[100];
  if (m.mode == META_FILE) {
    strcpy (szfilename,m.x.str);
    strcat (szfilename,".WMF");
    hmf = GetMetaFile (szfilename);
    }
  else if (m.mode == META_RSC) {
    HRSRC hrsrc = FindResource(WBase_hInstance, m.x.str, "METAFILE");
    HANDLE hResource = LoadResource (WBase_hInstance, hrsrc);
    LockResource (hResource);

#ifdef WIN32
    hmf = SetMetaFileBitsEx (SizeofResource(WBase_hInstance, hrsrc), 
                             (CONST BYTE *)hResource);
#else
    hmf = SetMetaFileBits (hResource);
#endif

    GlobalUnlock (hResource);
    }
  else if (m.mode == META_DIRECT) {
    hmf = m.x.hMeta;
    }
  if (hmf != 0) {
    // Test, ob das mit dem GetMetafileBits und SetMetaFileBits hinhaut
    SaveDC (hDC);
    FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumFilterRecord,hLibInst);

    EnumMetaFile (hDC,hmf,MFENUMPROC(lpfnEnumMeta),NULL);
    FreeProcInstance (lpfnEnumMeta);
    RestoreDC (hDC,-1);
    if (m.mode != META_DIRECT)
      DeleteMetaFile (hmf);
    }
  return *this ;
  }

struct SelEnumer {
  int arrind ;
  int metaind ;
  int arrcount ;
  int FAR *arr ;
  };

DLLExport int _export WINAPI EnumDrwSelRecord (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,SelEnumer FAR *s)
  {
  BOOL do_play;

  // Bearbeitet Funktionen
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_POLYLINE		     :
      
      do_play = ((s->arrind < s->arrcount) && 
                        (s->metaind == s->arr[s->arrind]));
      s->metaind++;
      if (do_play) s->arrind++;
      break ;
    default :
      do_play = FALSE ;
      break ;
    }

  if (do_play)
    // Zeichnen des Records
    PlayMetaFileRecord (hDC,lpHTable,lpMFR,nObj);

  return 1 ;            // Weiter gehts
  }

/*---< Ausgabe nur von Bestimmten Linien >----*/
void PaintContext::ExtMetaOut (HMETAFILE hMF,int FAR *sel)
  {
  SelEnumer s ;
  s.arrind = 0 ;
  s.metaind = 0 ;
  s.arrcount = *sel ;
  s.arr = sel + 1 ;

  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumDrwSelRecord,hLibInst);

  EnumMetaFile (hDC,hMF,MFENUMPROC(lpfnEnumMeta),LONG ((BYTE FAR *) &s));

  FreeProcInstance (lpfnEnumMeta);
  }

DLLExport int _export WINAPI EnumCountPolygon (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,int FAR *count)
  {
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_POLYLINE		     :
      (* count) ++ ;
      break ;
    }
  return 1 ;            // Weiter gehts
  }

int PaintContext::GetPolyCount (HMETAFILE hMF)
  {
  int count = 0 ;
  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumCountPolygon,hLibInst);

  EnumMetaFile (hDC,hMF,(MFENUMPROC)lpfnEnumMeta,LONG ((BYTE FAR *) &count));

  FreeProcInstance (lpfnEnumMeta);

  return count ;
  }

struct MeassureEnumer {
  int arrind ;
  int metaind ;
  int arrcount ;
  int FAR *arr ;
  RECT r;
  };

DLLExport int _export WINAPI EnumMeassurePolygon (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,MeassureEnumer FAR *s)
  {
  switch (lpMFR->rdFunction) {
    /*----< Funktionen mit Koordinaten >------*/
    case META_POLYLINE		     :
      if ((s->arrind < s->arrcount) && 
                        (s->metaind == s->arr[s->arrind])) {
        s->arrind++;
        CheckniKoords (lpMFR,lpMFR->rdParm[0],&s->r,1);
        }
      s->metaind++;
      break ;
    }
  return 1 ;            // Weiter gehts
  }


void PaintContext::GetPolyRect (HMETAFILE hMF,RECT *r,int FAR *sel)
  {
  MeassureEnumer s ;
  s.arrind = 0 ;
  s.metaind = 0 ;
  s.arrcount = *sel ;
  s.arr = sel + 1 ;
  s.r.bottom = s.r.left   = 32000;
  s.r.top    = s.r.right  = -32000;

  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumMeassurePolygon,hLibInst);

  EnumMetaFile (hDC,hMF,MFENUMPROC(lpfnEnumMeta),LONG ((BYTE FAR *) &s));

  FreeProcInstance (lpfnEnumMeta);
  if (s.r.bottom < 32000)
    lmemcpy (r,&s.r,sizeof(RECT));
  else
    SetRectEmpty (r);
  }


