#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"

#include "globmem.h"

static void CheckKoords (LPMETARECORD lpMFR,int end,RECT FAR *r,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    if (int(lpMFR->rdParm[i*2+0+offs]) < r->bottom) 
      r->bottom = int(lpMFR->rdParm[i*2+0+offs]);
    if (int(lpMFR->rdParm[i*2+0+offs]) > r->top   ) 
      r->top    = int(lpMFR->rdParm[i*2+0+offs]);
    if (int(lpMFR->rdParm[i*2+1+offs]) < r->left  ) 
      r->left   = int(lpMFR->rdParm[i*2+1+offs]);
    if (int(lpMFR->rdParm[i*2+1+offs]) > r->right ) 
      r->right  = int(lpMFR->rdParm[i*2+1+offs]);
    }
  }

static void CheckniKoords (LPMETARECORD lpMFR,int end,RECT FAR *r,int offs=0)
  {
  for (int i = 0 ; i < end ; i++) {
    if (int(lpMFR->rdParm[i*2+1+offs]) < r->bottom) 
      r->bottom = int(lpMFR->rdParm[i*2+1+offs]);
    if (int(lpMFR->rdParm[i*2+1+offs]) > r->top   ) 
      r->top    = int(lpMFR->rdParm[i*2+1+offs]);
    if (int(lpMFR->rdParm[i*2+0+offs]) < r->left  ) 
      r->left   = int(lpMFR->rdParm[i*2+0+offs]);
    if (int(lpMFR->rdParm[i*2+0+offs]) > r->right ) 
      r->right  = int(lpMFR->rdParm[i*2+0+offs]);
    }
  }

DLLExport int _export FAR PASCAL EnumMaxInfo (HDC hDC,LPHANDLETABLE lpHTable,
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

extern HINSTANCE MyInstance;
void GetMaxInfo (HDC hDC,HMETAFILE hMF,RECT FAR *r)
  {
  r->top    = r->right = -30000;        // top, right  -> maximum
  r->bottom = r->left  = 30000;         // bottom, top -> minimum
  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumMaxInfo,MyInstance);
  EnumMetaFile (hDC,hMF,(MFENUMPROC)lpfnEnumMeta,LONG ((BYTE FAR *) r));
  FreeProcInstance (lpfnEnumMeta);
  }

////////////////////////////////////////////////////////////////////////
//  Zeichnen des Metafiles
////////////////////////////////////////////////////////////////////////
DLLExport int _export FAR PASCAL EnumDrwRecord (HDC hDC,LPHANDLETABLE lpHTable,
                        LPMETARECORD lpMFR,int nObj,LPVOID d)
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
    case META_ARC		         :
    case META_ELLIPSE		     :
    case META_RECTANGLE		     :
    case META_ROUNDRECT		     :
    case META_SETPIXEL		     :
    case META_TEXTOUT		       :
    case META_POLYLINE		     :
    case META_POLYGON 		     :
#ifndef WIN32
    case META_DRAWTEXT		     :
#endif
    case META_EXTTEXTOUT	     :
    case META_CREATEPENINDIRECT	     :
#ifndef WIN32
    case META_CREATEBRUSH	     :
#endif
    case META_CREATEBRUSHINDIRECT    :
    case META_SELECTOBJECT	     :
    case META_DELETEOBJECT	     :
    case META_SETBKCOLOR	     :
    case META_SETBKMODE		     :
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

void ScaledMetaOut (HDC hDC,HWND hWnd,HMETAFILE hMF,LPRECT r)
  {
  int nSave = SaveDC (hDC);
  FARPROC lpfnEnumMeta = 
                MakeProcInstance ((FARPROC) EnumDrwRecord,MyInstance);
  RECT rw;
  GetClientRect (hWnd,&rw);
  double sx = double (rw.right) / double (r->right - r->left + 1);
  double sy = double (rw.bottom) / double (r->bottom - r->top + 1);
  SetMapMode (hDC,MM_ANISOTROPIC);
  if (fabs(sx) < fabs(sy)) {
    SetViewportExtEx (hDC,rw.right,rw.right, NULL);
    int dwx = r->right - r->left + 1;
    if (dwx < 0) dwx = -dwx;
    SetWindowExtEx (hDC,dwx,-dwx, NULL);
    }
  else {
    SetViewportExtEx (hDC,rw.bottom,rw.bottom, NULL);
    int dwy = r->bottom - r->top + 1;
    if (dwy < 0) dwy = -dwy;
    SetWindowExtEx (hDC,dwy,-dwy, NULL);
    }
  SetWindowOrgEx (hDC,(r->right + r->left) / 2,(r->top + r->bottom) / 2, NULL);
  SetViewportOrgEx (hDC,(rw.right + rw.left) / 2,(rw.top + rw.bottom) / 2, NULL);
  EnumMetaFile (hDC,hMF,(MFENUMPROC)lpfnEnumMeta,NULL);
  RestoreDC (hDC,nSave);
  FreeProcInstance (lpfnEnumMeta);
  }

