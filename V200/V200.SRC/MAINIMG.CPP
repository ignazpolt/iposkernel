/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/mainimg.cpv   1.31   17 Jun 1999 16:08:54   Martin  $
// $Log:   P:/marille/clinicum/rev/mainimg.cpv  $
// 
//    Rev 1.31   17 Jun 1999 16:08:54   Martin
// Software-Drehung jetzt ueber LEAD-Tools (damit alle Formate gehen)
// 
//    Rev 1.30   25 May 1999 18:42:56   Martin
// optionaler Parameter bei FrmImportImage: Reduktionsfaktor
// 
//    Rev 1.29   25 Apr 1999 19:04:08   Martin
// optionaler Parameter hWnd bei MCICommand
// 
//    Rev 1.28   03 Dec 1998 11:43:30   Martin
// bei TWAIN: ConvertToDIB anstatt ChangeToDIB
// 
//    Rev 1.27   18 Nov 1998 18:21:28   Martin
// LT10
// 
//    Rev 1.26   05 Oct 1998 11:55:16   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.25   14 Sep 1998 17:10:14   Martin
// SoftWork raus
// 
//    Rev 1.24   31 Mar 1998 12:16:52   Martin
// ScanWizardSpezialBehandlung
// 
//    Rev 1.23   03 Mar 1998 20:06:42   Martin
// True Color
// 
//    Rev 1.22   10 Feb 1998 18:22:36   Martin
// FrmGetImgRatio
// 
//    Rev 1.21   31 Jan 1998 22:25:34   Martin
// DIBFromClipboard, SetWindowPosition, MCICommand (fuer Screen Machine II)
// 
//    Rev 1.20   11 Nov 1997 10:21:46   Martin
// GetImgPhysScale auf form umgestellt
// 
//    Rev 1.19   27 Oct 1997 10:24:30   Martin
// FrmFreeDIB
// 
//    Rev 1.18   21 Oct 1997 11:50:12   Martin
// ScreenMachine: jedenfalls alte Version nehmen
// 
//    Rev 1.17   15 Sep 1997 20:59:12   Hannes
// Bilder mit Blobs
// 
//    Rev 1.16   16 Jul 1997 16:27:58   Martin
// frmloaddib korrigiert
// 
//    Rev 1.15   14 Jul 1997 12:44:10   Martin
// FrmgetImgInfo, FrmLoad/SaveDIB
// 
//    Rev 1.14   28 Apr 1997 17:01:02   Martin
// ent-warning-isiert
// 
//    Rev 1.13   28 Apr 1997 15:01:34   Martin
// (WORD)CM_UNCOMPRESSED
// 
//    Rev 1.12   25 Apr 1997 12:32:42   Martin
// Bildkomrimierung
// 
//    Rev 1.11   18 Mar 1997 11:37:18   Martin
// TWAIN auf LeadTools umgestellt
// 
//    Rev 1.10   24 Mar 1996 12:09:16   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.9   02 Feb 1996 10:34:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   24 Aug 1995 00:20:28   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.7   14 Aug 1995 08:28:20   HANNES
// Tests ...
// 
//    Rev 1.6   03 Jul 1995 16:16:44   HANNES
// Fehler im FrmImportImage
// 
//    Rev 1.5   24 May 1995 21:36:36   HANNES
// FrmImportImage BOOLsch gemacht
// 
//    Rev 1.4   20 Mar 1995 12:04:26   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.3   15 Nov 1994 22:48:56   MARTIN
// Scanner...
// 
//    Rev 1.2   15 Nov 1994 15:30:38   MARTIN
// StoreImage korrigiert
// 
//    Rev 1.1   17 Oct 1994 15:04:58   HANNES
// Umbau der GetExtradata auf den Zeichenkontext
// 
//    Rev 1.0   24 Jun 1994 19:30:44   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#ifndef WIN32
#include <mmsystem.h>
#endif

#include "l_bitmap.h"
#define LT_SUPPORT_GIF "78BY1jl78"
#define LT_SUPPORT_TIF "oam5302FDio"

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

#define NODLL
#include "toolbar.hpp"
#include "image.hpp"
#define MODULENUM 114
#include "winass.hpp"
#include "cfield.hpp"
#include "frmobj.hpp"
#include "frmobj3.hpp"
#include "winextra.hpp"
#include "cutcont.hpp"

#include "hash.hpp"
#include "compile.hpp"

extern DLLExport int _export WINAPI BitsPerPixel (void);

static void MicrotekSpezialBehandlung(LPSTR source,LPWORD Lampstate)
  {
  static BOOL SpezialBehandlung = FALSE;
  static BOOL FirstCall = TRUE;
  static char MicrotekSpezial[64];
  static char MicrotekIni[64];
  static char MicrotekSection[32];
  static char MicrotekEntry[32];
  static char MicrotekOn[32];
  static char MicrotekOff[32];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"MicrotekSpezial","",
                                 MicrotekSpezial,sizeof(MicrotekSpezial),
                                 MYINI
                                ) > 0
       ) {
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekIni","",
                               MicrotekIni,sizeof(MicrotekIni),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekSection","",
                               MicrotekSection,sizeof(MicrotekSection),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekEntry","",
                               MicrotekEntry,sizeof(MicrotekEntry),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekOn","",
                               MicrotekOn,sizeof(MicrotekOn),MYINI);
      GetPrivateProfileString (TIFFIMGSECTION,"MicrotekOff","",
                               MicrotekOff,sizeof(MicrotekOff),MYINI);
      SpezialBehandlung = TRUE;
      }
    FirstCall = FALSE;
    }
  if (SpezialBehandlung && (Lampstate != NULL) && (*Lampstate != 0)) {
    if (lstrcmp(source,MicrotekSpezial) == 0) {
      if (*Lampstate == 1)
        WritePrivateProfileString(MicrotekSection,MicrotekEntry,MicrotekOff,MicrotekIni);
      if (*Lampstate == 2)
        WritePrivateProfileString(MicrotekSection,MicrotekEntry,MicrotekOn,MicrotekIni);
      *Lampstate = 0;  // nicht mehr ueber TWAIN setzen !
      }
    }
  }

static BOOL FixResolution;
static void ScanWizardSpezialBehandlung(LPSTR source)
  {
  static BOOL SpezialBehandlung = FALSE;
  static BOOL FirstCall = TRUE;
  static char ScanWizardSpezial[64];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,"ScanWizardSpezial","",
                                 ScanWizardSpezial,sizeof(ScanWizardSpezial),
                                 MYINI
                                ) > 0
       )
      SpezialBehandlung = TRUE;
    FirstCall = FALSE;
    }
  if (SpezialBehandlung) {
    if (lstrcmp(source,ScanWizardSpezial) == 0)
      FixResolution = TRUE;
    }
  }

BOOL FrmScanImage (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    FrmScanImage_par FAR *par = (FrmScanImage_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *img = (FrmImage FAR *) (*addr);
      LPSTR source = (LPSTR)c->ReadlData(par->source);
      float FAR *left = (float FAR *)c->ReadlData(par->left);
      float FAR *top = (float FAR *)c->ReadlData(par->top);
      float FAR *right = (float FAR *)c->ReadlData(par->right);
      float FAR *bottom = (float FAR *)c->ReadlData(par->bottom);
      float FAR *Resolution = (float FAR *)c->ReadlData(par->Resolution);
      LPWORD Orientation = (LPWORD)c->ReadlData(par->Orientation);
      LPWORD Pixeltype = (LPWORD)c->ReadlData(par->Pixeltype);
      LPWORD Lampstate = (LPWORD)c->ReadlData(par->Lampstate);
      LPWORD UserInterface = (LPWORD)c->ReadlData(par->UserInterface);
      LPWORD AlteVersion = NULL;
      if (par->par_Size >= sizeof(FrmScanImage_par))
        AlteVersion = (LPWORD)c->ReadlData(par->AlteVersion);
      BOOL doAlteVersion;
      static char ScreenMachineSpezial[64];
      if (GetPrivateProfileString (TIFFIMGSECTION,"ScreenMachineSpezial","",
                                  ScreenMachineSpezial,sizeof(ScreenMachineSpezial),
                                  MYINI
                                  ) > 0
        ) {
        doAlteVersion = TRUE;
        }
      else {
        if ((AlteVersion != NULL) && (*AlteVersion != 0))
          doAlteVersion = TRUE;
        else
          doAlteVersion = FALSE;
        }
      if (doAlteVersion) {
        if (img->OnStartScan(source,
                             left,top,right,bottom,
                             Resolution,Orientation,Pixeltype,Lampstate,
                             (UserInterface != NULL) && (*UserInterface),
                             par->rdyRec,par->rdyId,c))
          res = TRUE;
        }
      else {
        WORD myLampstate;
        if (Lampstate != NULL)
          myLampstate = *Lampstate;
        else
          myLampstate = 0;
        FixResolution = FALSE;
        MicrotekSpezialBehandlung(source,&myLampstate);
        ScanWizardSpezialBehandlung(source);
        TWAINPROPERTIES tp;
        lstrcpy(tp.AppManufacturer,"GWI");
        lstrcpy(tp.AppProdFamily,"ORBIS Application Kernel");
        lstrcpy(tp.AppProdName,"TWAIN Support");
        if (source != NULL)
          lstrcpy(tp.SourceName,source);
        else
          tp.SourceName[0] = '\0';
        tp.nMaxPages = 1;
        if (Pixeltype != NULL) {
          if (*Pixeltype == 1)
            tp.nPixelType = TWAIN_PIX_GRAY;
          else if (*Pixeltype == 2)
            tp.nPixelType = TWAIN_PIX_RGB;
          else if (*Pixeltype == 3)
            tp.nPixelType = TWAIN_PIX_HALF;
          else
            tp.nPixelType = TWAIN_PIX_DEFAULT;
          }
        else
          tp.nPixelType = TWAIN_PIX_DEFAULT;
        tp.nBits = -1;
        if (Resolution != NULL)
          tp.nRes = L_INT(*Resolution);
        else
          tp.nRes = -1;
        if (left != NULL)
          tp.nXPos = L_INT32(*left * 1440.0);
        else
          tp.nXPos = -1L;
        if (top != NULL)
          tp.nYPos = L_INT32(*top * 1440.0);
        else
          tp.nYPos = -1L;
        if ((left != NULL) && (right != NULL))
          tp.nWidth = L_INT32((*right - *left) * 1440.0);
        else
          tp.nWidth = -1L;
        if ((top != NULL) && (bottom != NULL))
          tp.nHeight = L_INT32((*bottom - *top) * 1440.0);
        else
          tp.nHeight = -1L;
#ifndef LT7
        tp.nBrightness = TWAIN_DEFAULT_BRIGHTNESS;
        tp.nContrast = TWAIN_DEFAULT_CONTRAST;
        tp.nOrientation = TWAIN_DEFAULT_ORIENTATION;
        tp.nFeederEnabled = TWAIN_FEEDER_DONTCARE;
        tp.nEnableAutoFeed = TWAIN_FEEDER_DONTCARE;
#endif
        L_TwainSetProps(WBase::hFrameWin,&tp,0);
        L_UINT uFlags;
        if ((UserInterface != NULL) && (*UserInterface))
          uFlags = TWAIN_SHOWUI | TWAIN_SHOWSTATUS | TWAIN_NATIVEXFER;
        else
          uFlags = TWAIN_SHOWSTATUS | TWAIN_NATIVEXFER;
        BITMAPHANDLE LeadBitmap;
        GLOBALHANDLE hImage;
        if (L_TwainAcquireExt(WBase::hFrameWin,&LeadBitmap,uFlags,NULL,NULL) < SUCCESS) {
          hImage = NULL;
          }
        else {
          if ((Orientation != NULL) && (*Orientation == 3))
            L_RotateBitmap(&LeadBitmap,90,TRUE);
          hImage = L_ConvertToDIB(&LeadBitmap);
          L_FreeBitmap(&LeadBitmap);
          }
        if (hImage) {
#ifdef ALTE_VERSION
          if ((Orientation != NULL) && (*Orientation == 3))
            hImage = RotateImage(hImage);
#endif
          if (FixResolution && (Resolution != NULL)) {
            LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hImage);
            lpbi->biXPelsPerMeter = lpbi->biYPelsPerMeter = LONG(*Resolution * 39.37);
            GlobalUnlock(hImage);
            }
          }
        if (hImage) {
          ((FrmImage FAR *) (*addr))->SetImage(hImage);
          WORD flag = TRUE;
          c->WriteData(par->rdyRec,par->rdyId, &flag, sizeof(WORD), LPSTR(param) - sizeof(WORD));
          res = TRUE;
          }
        }
      }
    }
  return res ;
  }

BOOL FrmImportImage (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    FrmImportImage_par FAR *par = (FrmImportImage_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    LPSTR FileName = (LPSTR)c->ReadData(par->nameR,par->nameI);
    if ((addr != NULL) && (*addr != NULL) && (FileName != NULL)) {
      FrmImage FAR *img = (FrmImage FAR *) (*addr);
      float factor = 1.0;
      if (par->par_Size >= sizeof(*par)) {
        float *lpfactor = (float *)c->ReadlData(par->fact);
        if (lpfactor != NULL)
          factor = *lpfactor;
        }
      if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
        L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
      if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
        L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
      BITMAPHANDLE LeadBitmap;
      GLOBALHANDLE hDIB;
      if (L_LoadBitmap(FileName,&LeadBitmap,0,ORDER_BGR) < SUCCESS) {
        hDIB = NULL;
        }
      else {
        if (factor > 0.001) {
          L_INT nWidth = L_INT((double(LeadBitmap.Width) / double(factor)) + 0.5);
          L_INT nHeight = L_INT((double(LeadBitmap.Height) / double(factor)) + 0.5);
          if ((nWidth != LeadBitmap.Width) ||
              (nHeight != LeadBitmap.Height))
            L_ResampleBitmap(&LeadBitmap,nWidth,nHeight);
          }
        hDIB = L_ChangeToDIB(&LeadBitmap);
        }
      if (hDIB != NULL) {
        img->SetImage(hDIB);
        if (img->Initialized)
          res = TRUE;   // Import gelungen
        }
      }
    }
  return res ;
  }

BOOL FrmSetImage (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmSetImage_par FAR *par = (FrmSetImage_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    GLOBALHANDLE FAR * lphDIB = (GLOBALHANDLE FAR *)c->ReadData(par->ImgR,par->ImgI);
    if ((addr != NULL) && (*addr != NULL) && (lphDIB != NULL))
      ((FrmImage FAR *) (*addr))->SetImage(*lphDIB);
    }
  return FALSE ;
  }

BOOL FrmWriteBMP (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmWriteBMP_par FAR *par = (FrmWriteBMP_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    LPSTR FileName = (LPSTR)c->ReadData(par->nameR,par->nameI);
    if ((addr != NULL) && (*addr != NULL) &&
        (FileName != NULL) && (*FileName != '\0'))
      ((FrmImage FAR *) (*addr))->WriteBMP(FileName);
    }
  return FALSE ;
  }

BOOL FrmStoreImage (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmStoreImage_par FAR *par = (FrmStoreImage_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      GLOBALHANDLE hAddl = NULL;
      int num_pars = ((par->par_Size - (sizeof(FrmStoreImage_par) - sizeof(par->Ref[0]))) /
                     sizeof(par->Ref[0])) ;
      int size = 0;
      for (int i = 0; i < num_pars; i++) {
        LPVOID data = c->ReadData(par->Ref[i].R, par->Ref[i].I);
        int newsize = 0;
        if (data != NULL)
          newsize += GetBlockSize(data);
        if (hAddl == NULL)
          hAddl = GlobalAlloc(GMEM_MOVEABLE, size + 4 + newsize);
        else
          hAddl = GlobalReAlloc(hAddl,size + 4 + newsize,GMEM_MOVEABLE);
        ADDLIMAGEINFO FAR *AddlInfo = (ADDLIMAGEINFO FAR *)(LPSTR(GlobalLock(hAddl)) + size);
        AddlInfo->Id = c->ReadConstInt (par->Ref[i].rtype);
        AddlInfo->Len = newsize;
        if (data != NULL)
          lmemcpy(AddlInfo->data, data, newsize);
        size += 4 + newsize;
        GlobalUnlock(hAddl);
        }
      LPVOID AddlInfo = NULL;
      if (size > 0)
        AddlInfo = GlobalLock(hAddl);
      LPWORD lpCompressMode = (LPWORD)c->ReadData (par->comprR,par->comprI);
      WORD cm = WORD(lpCompressMode != NULL ? *lpCompressMode : CM_UNCOMPRESSED);

      WORD mType = c->GetDataType (MAKELONG (par->nameR,par->nameI));
      LPVOID key = c->ReadData (par->keyR,par->keyI);
      if (mType != VAR_BLOB) {
        HFILE FAR *lpfh = (HFILE FAR *)c->ReadData (par->nameR,par->nameI);
        DBWIN_ASSERT(lpfh != NULL);
        ((FrmImage FAR *) (*addr))->StoreImage(key,(DWORD)lpfh,AddlInfo, size, cm);
        }
      else {
        BlobDesc FAR *bd = (BlobDesc FAR *)c->ReadData (par->nameR,par->nameI);
        if (bd != NULL) {
          if (bd->hGmem) GlobalFree (bd->hGmem);
          c->DelData (par->nameR,par->nameI,LPSTR(param)-sizeof(WORD));
          }
        BlobDesc bdn;
        bdn.hGmem = NULL;
        bdn.Size = 0L;
        ((FrmImage FAR *) (*addr))->StoreImage(key,&bdn,AddlInfo, size, cm);
        if (bdn.hGmem)
          c->WriteData (par->nameR,par->nameI,&bdn,sizeof(bdn),LPSTR(param)-sizeof(WORD));
        }
      if (size > 0) {
        GlobalUnlock(hAddl);
        GlobalFree(hAddl);
        }
      } 
    }
  return FALSE ;
  }


BOOL FrmGetImageFileName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmGetImageFileName_par FAR *par = (FrmGetImageFileName_par FAR *) param;
    LPVOID Key = c->ReadData(par->keyR,par->keyI);
    char FileName[64];
    GetImageFileName(FileName, Key);
    c->WriteData (par->nameR,par->nameI,FileName, lstrlen(FileName) + 1, 0, UPDATE_ASYNCHRON);
    }
  return FALSE ;
  }


// Filter-Script-Funktionen

BOOL ImgGetOriginal (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    LPSTR Offset = LPSTR(param) - sizeof(WORD);
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        Img->SetDIB(Img->hwholeDIB, NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      // Objektzeiger schreiben, damit Palettenobjekt Update erhaelt
      c->WriteData (par->ObjRec, par->ObjId,
                    &ImgObj, sizeof(LPFRMOBJ), Offset);
      }
    }
  return FALSE;
  }


BOOL ImgUserFlt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgUserFlt_par FAR *par = (ImgUserFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        Filter f;
        f.a[0][0] = c->ReadConstInt (par->ra00) ;
        f.a[0][1] = c->ReadConstInt (par->ra01) ;
        f.a[0][2] = c->ReadConstInt (par->ra02) ;
        f.a[1][0] = c->ReadConstInt (par->ra10) ;
        f.a[1][1] = c->ReadConstInt (par->ra11) ;
        f.a[1][2] = c->ReadConstInt (par->ra12) ;
        f.a[2][0] = c->ReadConstInt (par->ra20) ;
        f.a[2][1] = c->ReadConstInt (par->ra21) ;
        f.a[2][2] = c->ReadConstInt (par->ra22) ;
        f.fct =     c->ReadConstInt (par->rfact) ;
        LPSTR wn = LPSTR (c->ReadlData (par->WaitWinName));
        if ((wn != NULL) && (c->ReadConstInt (par->rWFuncFlag)))
          Img->linFlt (&f,wn);
        else
          Img->linFlt (&f,NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }


#define AnzColors 256

static GLOBALHANDLE GetPixCnt(mImage FAR *Img, BOOL WFuncFlag)
  {
  GLOBALHANDLE hPixCnt = GlobalAlloc (GHND,AnzColors * sizeof (DWORD));
  DWORD FAR *PCnt = (DWORD FAR *) GlobalLock (hPixCnt);
  if (WFuncFlag)
    Img->GetHisto (PCnt,LRString(9031));
  else
    Img->GetHisto (PCnt,NULL);
  GlobalUnlock (hPixCnt);
  return hPixCnt;
  }


BOOL ImgBestContrast (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        GLOBALHANDLE hPixCnt = GetPixCnt(Img, c->ReadConstInt (par->rWFuncFlag));
        double count ;
        int i ;
        DWORD FAR *PCnt = (DWORD FAR *) GlobalLock (hPixCnt);
        BITMAPINFO FAR *lpbi = (BITMAPINFO FAR *) GlobalLock (Img->hBMHeader);
        // Berechnen des counts
        count = double (lpbi->bmiHeader.biWidth) * 
                              double (lpbi->bmiHeader.biHeight) ;
        // Berechnung der Wahrscheinlichkeiten der einzelnen Grauwerte
        GLOBALHANDLE hGpz = GlobalAlloc (GHND,sizeof (double) * AnzColors) ;
        double FAR *p = (double FAR *) GlobalLock (hGpz);
#ifdef NORMALE_VERSION
        for (i = 0 ; i < AnzColors ; i++)
          p[i] = double (PCnt[i]) / count ;
#else
        double addval = count / (double(AnzColors) * 10.0);
        double nenner = count * 1.10;
        for (i = 0 ; i < AnzColors ; i++)
          p[i] = (double (PCnt[i]) + addval) / nenner ;
#endif
        // Berechnung der LookUpTable
        BYTE lut[256];        // Im Stack halten, damit die Umrechnung
                              // etwas angenehmer ausfaellt
        double sold = 0.0 ;
        double s ;
        double divval = 1.0 - p[0];
        for (i = 0 ; i < AnzColors ; i++) {
          s = sold + p[i] ;
          lut[i] = BYTE (((s - p[0]) / divval) * double (AnzColors - 1)) ;
          sold = s ;
          }
        // Umrechnen des Images
        if (c->ReadConstInt (par->rWFuncFlag))
          Img->lutTrans (lut,LRString(9032));
        else
          Img->lutTrans (lut,NULL);
        // Speicher wieder freigeben
        GlobalUnlock (hGpz);
        GlobalFree (hGpz);
        GlobalUnlock (Img->hBMHeader);
        if (hPixCnt) {
          GlobalUnlock (hPixCnt);
          GlobalFree (hPixCnt);
          }
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }


BOOL ImgCrispFlt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        // Laplace Filter mit Achterumgebung und
        // Mischung des Orginalbildes zu 60 %
        static Filter lpflt = {
          { { -4 , -4 , -4 } ,
            { -4 , 37 , -4 } ,
            { -4 , -4 , -4 } } ,
          5
          } ;
        if (c->ReadConstInt (par->rWFuncFlag))
          Img->linFlt (&lpflt,LRString(9033));
        else
          Img->linFlt (&lpflt,NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }


BOOL ImgMedianFlt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        if (c->ReadConstInt (par->rWFuncFlag))
          Img->MedianFlt (LRString(9034));
        else
          Img->MedianFlt (NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }


BOOL ImgSobelFlt (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        if (c->ReadConstInt (par->rWFuncFlag))
          Img->SobelFlt (LRString(9035));
        else
          Img->SobelFlt (NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }


BOOL ImgLocalContrast (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    ImgFixFlt_par FAR *par = (ImgFixFlt_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
        if (c->ReadConstInt (par->rWFuncFlag))
          Img->LocalContrast (LRString(9080));
        else
          Img->LocalContrast (NULL);
        Img->ResetBMPs();
        ImgObj->Invalidate(c->actSide());
        }
      }
    }
  return FALSE;
  }

extern LPSTR ExtChildClass;
BOOL BestPalette (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  BestPalette_par FAR *par = (BestPalette_par FAR *)param;
  int num_pars = ((par->par_Size - sizeof(BestPalette_par)) / sizeof(par->img[0])) + 1;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPPALINFO lppi = (LPPALINFO)c->DrawContext()->GetDocumentExtraData(DED_PALETTEINFO);
    if (lppi != NULL) {
      if (lppi->actpal != NULL) DeleteObject(lppi->actpal);
      if (lppi->palind != NULL) GlobalFree(lppi->palind);
      c->DrawContext()->RemoveDocumentExtraData (DED_PALETTEINFO);
      }
    char className[64];
    GetClassName (c->OutWnd(),className,sizeof(className));
    HPALETTE externPalette = 0;
//    if (lstrcmp (className,ExtChildClass) == 0)
//      externPalette = CTOOL_GetActivePalette ();
    BOOL onlygray = TRUE ;
    if (BitsPerPixel() == 8) {
      for (int i = 0; onlygray && (i < num_pars); i++) {
        LPFRMOBJ FAR *addr =
            (LPFRMOBJ FAR *) c->ReadlData (par->img[i]);
        if ((addr != NULL) &&
            (GetBlockSize(addr) == sizeof(LPFRMOBJ)) &&
            (*addr != NULL)) {
          FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
          if (ImgObj->img != NULL)
            onlygray = onlygray && ImgObj->img->IsGray;
          }
        }
      }
    PalInfo pi;
    if (onlygray) {
      pi.actpal = CreateGrayPalette(externPalette);
      pi.palind = NULL;
      pi.gray = TRUE;
      pi.doDelete = TRUE ;
      }
    else {
      GLOBALHANDLE ColorHist = GetEmptyColorHisto();
      for (int i = 0; i < num_pars; i++) {
        LPFRMOBJ FAR *addr =
            (LPFRMOBJ FAR *) c->ReadlData (par->img[i]);
        if ((addr != NULL) &&
            (GetBlockSize(addr) == sizeof(LPFRMOBJ)) &&
            (*addr != NULL)) {
          FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
          if (ImgObj->img != NULL)
            ImgObj->img->AddColorHisto(ColorHist);
          }
        }
      pi.actpal = CalcBestPalette(ColorHist, &pi.palind);
      pi.gray = FALSE;
      pi.doDelete = TRUE ;
      }
//    if (lstrcmp (className,ExtChildClass) == 0)
//      CTOOL_SetActivePalette (pi.actpal);
    if (pi.gray) {
      LPPALINFO lppi = (LPPALINFO)GetGlobMem(sizeof(pi) + sizeof(int) + num_pars * sizeof(FrmImage FAR *));
      *lppi = pi;
      int AnzImgs = 0;
      for (int i = 0; i < num_pars; i++) {
        LPFRMOBJ FAR *addr =
            (LPFRMOBJ FAR *) c->ReadlData (par->img[i]);
        if ((addr != NULL) &&
            (GetBlockSize(addr) == sizeof(LPFRMOBJ)) &&
            (*addr != NULL)) {
          FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
          if ((ImgObj->img != NULL) && ImgObj->img->IsGray)
            ((FrmImage FAR * FAR *)(LPSTR(lppi + 1) + sizeof(int)))[AnzImgs++] = ImgObj;
          }
        }
      *((int FAR *)(lppi + 1)) = AnzImgs;
      c->DrawContext()->PutDocumentExtraData(DED_PALETTEINFO, lppi, sizeof(pi) + sizeof(int) + AnzImgs * sizeof(FrmImage FAR *));
      FreeGlobMem(lppi);
      }
    else
      c->DrawContext()->PutDocumentExtraData(DED_PALETTEINFO, &pi, sizeof(pi));
    WORD doMorph = FALSE;
    for (int i = 0; i < num_pars; i++) {
      LPFRMOBJ FAR *addr = 
          (LPFRMOBJ FAR *) c->ReadlData (par->img[i]);
      if (addr != NULL) {
        if (GetBlockSize(addr) == sizeof(WORD)) {
          doMorph = *((WORD FAR *)addr);
          }
        else {
          if (*addr != NULL) {
            FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
            if (ImgObj->img != NULL) {
              ImgObj->img->SetPal(pi.actpal,pi.palind,doMorph);
              ImgObj->Invalidate(c->actSide());
              }
            }
          doMorph = FALSE;
          }
        }
      }
    SendMessage(WBase::hFrameWin, WM_QUERYNEWPALETTE, NULL, NULL);
    }

  if (mode & EM_FIXCONNECTION) {
    for (int i = 0; i < num_pars; i++)
      c->SetlConnection(par->img[i], Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    LPPALINFO lppi = (LPPALINFO)c->DrawContext()->GetDocumentExtraData(DED_PALETTEINFO);
    if (lppi != NULL) {
      if ((lppi->actpal != NULL) && (lppi->doDelete)) DeleteObject(lppi->actpal);
      if (lppi->palind != NULL) GlobalFree(lppi->palind);
      c->DrawContext()->RemoveDocumentExtraData (DED_PALETTEINFO);
      }
    for (int i = 0; i < num_pars; i++)
      c->ClearlConnection(par->img[i], Offset);
    }

  return FALSE;
  }


BOOL FrmGetPixPerMeter (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  if (mode & EM_LOAD) {
    FrmGetPixPerMeter_par FAR *par = (FrmGetPixPerMeter_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        LONG x, y;
        Img->GetPelsPerMeter(&x, &y);
        c->WriteData(par->xR, par->xI, &x, sizeof(LONG), Offset);
        c->WriteData(par->yR, par->yI, &y, sizeof(LONG), Offset);
        }
      }
    }
  return FALSE;
  }


BOOL FrmSetPixPerMeter (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmSetPixPerMeter_par FAR *par = (FrmSetPixPerMeter_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        LPLONG x = (LPLONG)c->ReadData(par->xR, par->xI);
        LPLONG y = (LPLONG)c->ReadData(par->yR, par->yI);
        if ((x != NULL) && (y != NULL))
          Img->SetPelsPerMeter(*x, *y);
        }
      }
    }
  return FALSE;
  }


BOOL FrmGetImgWidth (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  if (mode & EM_LOAD) {
    FrmGetImgWidth_par FAR *par = (FrmGetImgWidth_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        LONG w = Img->GetImgWidth();
        c->WriteData(par->wR, par->wI, &w, sizeof(LONG), Offset);
        }
      }
    }
  return FALSE;
  }


BOOL FrmGetImgRatio (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  FrmGetImgWidth_par FAR *par = (FrmGetImgWidth_par FAR *) param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        LONG w = Img->GetImgWidth();
        LONG h = Img->GetImgHeight();
        float ratio = float(h) / float(w);
        c->WriteData(par->wR, par->wI, &ratio, sizeof(float), Offset);
        }
      else
        c->DelData(par->wR, par->wI, Offset);
      }
    else
      c->DelData(par->wR, par->wI, Offset);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetConnection(par->ObjRec, par->ObjId, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearConnection(par->ObjRec, par->ObjId, Offset);
    }

  return FALSE;
  }


BOOL FrmDrawContDirect (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmDrawContDirect_par FAR *par = (FrmDrawContDirect_par FAR *) param;
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        fpt FAR *cnt = (fpt FAR *)c->ReadData(par->cntR, par->cntI);
        LPLONG col = (LPLONG)c->ReadData(par->colR, par->colI);
        if ((cnt != NULL) && (col != NULL)) {
          int cntsize;
          cnt = get_cont (cnt, &cntsize);
          Img->DrawContDirect((float FAR *)cnt,cntsize,*col);
          }
        }
      }
    }
  return FALSE;
  }


BOOL uGetImgPhysScale (mdiChild *c,void FAR *param,WORD mode)
  {
  GetImagePhysScalePar FAR *par = (GetImagePhysScalePar FAR *) param;

  if (mode & EM_LOAD) {
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        float scf = (float)Img->GetImgWidth()
                  / c->LogToWorld(ImgObj->ImgRect.right - ImgObj->ImgRect.left);
        tr2 m1,m2,m;
        m1.A[0][0] = scf;
        m1.A[1][1] = scf;
        m1.A[0][1] =
        m1.A[1][0] = float (0.0) ;
        m1.B[0] = m1.B[1] = float (0.0) ;
        m2.A[0][0] = float (1.0) ;
        m2.A[1][1] = float (1.0) ;
        m2.A[0][1] =
        m2.A[1][0] = float (0.0) ;
        m2.B[0] = float (-ImgObj->ImgRect.left);
        m2.B[1] = float (-ImgObj->ImgRect.top) ;
        Combine2d (&m,&m2,&m1);
        c->WriteData(par->scRec,par->scId,&m,sizeof(m),LPSTR(par)-sizeof(WORD));
        }
      }
    }

  return FALSE ;
  }


BOOL CreateEdgeTable (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  CreateEdgeTable_par FAR *par = (CreateEdgeTable_par FAR *) param;

  if (mode & EM_LOAD) {
    LPFRMOBJ FAR *addr =
        (LPFRMOBJ FAR *) c->ReadlData (par->ImgObj);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        LONG h = Img->GetImgHeight();
        DBWIN_ASSERT((h > 0) && (h < 32768L));
        EdgeTable ET;
        ET.ymax = int(h);
        ET.hET = GlobalAlloc(GHND, ET.ymax * sizeof(LPVOID));
        c->WritelData(par->EdgeTab, &ET, sizeof(EdgeTable), Offset);
        }
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    EdgeTable FAR *lpet = (EdgeTable FAR *) c->ReadlData (par->EdgeTab);
    if ((lpet != NULL) && (lpet->hET != NULL)) {
      // bitte spaeter entfernen
      LPVOID FAR *EdgeList = (LPVOID FAR *)GlobalLock(lpet->hET);
      for (int i = 0; i < lpet->ymax; i++) {
        DBWIN_ASSERT(EdgeList[i] == NULL);
        }
      GlobalUnlock(lpet->hET);
      GlobalFree(lpet->hET);
      }
    }

  return FALSE;
  }


BOOL FillInEdges (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  FillInEdges_par FAR *par = (FillInEdges_par FAR *)param;
  int num_pars = ((par->par_Size - sizeof(FillInEdges_par)) / sizeof(par->Edge[0])) + 1;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    EdgeTable FAR *lpet = (EdgeTable FAR *) c->ReadlData (par->EdgeTab);
    if ((lpet != NULL) && (lpet->hET != NULL)) {
      LPVOID FAR *EdgeList = (LPVOID FAR *)GlobalLock(lpet->hET);
      // bitte spaeter entfernen
      for (int i = 0; i < lpet->ymax; i++) {
        DBWIN_ASSERT(EdgeList[i] == NULL);
        }
      for (i = 0; i < num_pars; i++) {
        fpt FAR *p1 = (fpt FAR *)c->ReadlData(par->Edge[i].p1);
        fpt FAR *p2 = (fpt FAR *)c->ReadlData(par->Edge[i].p2);
        fpt FAR *v1 = (fpt FAR *)c->ReadlData(par->Edge[i].v1);
        fpt FAR *v2 = (fpt FAR *)c->ReadlData(par->Edge[i].v2);
        AddEdge(EdgeList,lpet->ymax,p1,p2,v1,v2);
        }
      GlobalUnlock(lpet->hET);
      }
    }

  if (mode & EM_FIXCONNECTION) {
    for (int i = 0; i < num_pars; i++) {
      c->SetlConnection(par->Edge[i].p1, Offset);
      c->SetlConnection(par->Edge[i].p2, Offset);
      c->SetlConnection(par->Edge[i].v1, Offset);
      c->SetlConnection(par->Edge[i].v2, Offset);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    for (int i = 0; i < num_pars; i++) {
      c->ClearlConnection(par->Edge[i].p1, Offset);
      c->ClearlConnection(par->Edge[i].p2, Offset);
      c->ClearlConnection(par->Edge[i].v1, Offset);
      c->ClearlConnection(par->Edge[i].v2, Offset);
      }
    }

  return FALSE;
  }


BOOL FrmMorphImage (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  FrmMorphImage_par FAR *par = (FrmMorphImage_par FAR *) param;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPPALINFO lppi = (LPPALINFO)c->DrawContext()->GetDocumentExtraData(DED_PALETTEINFO);
    if (lppi != NULL) {
      LPFRMOBJ FAR *addr =
          (LPFRMOBJ FAR *) c->ReadlData (par->ImgObj);
      if ((addr != NULL) && (*addr != NULL)) {
        FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
        mImage FAR *Img = ImgObj->img;
        if (ImgObj->Initialized && (Img != NULL) && (Img->hwholeDIB != NULL)) {
          EdgeTable FAR *lpet = (EdgeTable FAR *) c->ReadlData (par->EdgeTab);
          if ((lpet != NULL) && (lpet->hET != NULL)) {
            LPVOID FAR *EdgeList = (LPVOID FAR *)GlobalLock(lpet->hET);
            Img->MorphImage(EdgeList,lpet->ymax, lppi->palind);
            GlobalUnlock(lpet->hET);
            Img->ResetBMPs();
            ImgObj->Invalidate(c->actSide());
            }
          }
        }
      }
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->EdgeTab, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->EdgeTab, Offset);
    }

  return FALSE;
  }


BOOL FrmGetImageScaleFact (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  FrmGetImageScaleFact_par FAR *par = (FrmGetImageScaleFact_par FAR *) param;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    float sf = float(1.0E10);
    LPFRMOBJ FAR *addr = 
        (LPFRMOBJ FAR *) c->ReadlData (par->Obj);
    if ((addr != NULL) && (*addr != NULL)) {
      FrmImage FAR *ImgObj = (FrmImage FAR *) (*addr);
      mImage FAR *Img = ImgObj->img;
      if (Img != NULL) {
        SCALEIMAGEINFO si;
        Img->InitializeScale (&si,1.0);
        sf = float(si.LogRect.right - si.LogRect.left) /
             float(ImgObj->ImgRect.right - ImgObj->ImgRect.left);
        }
      }
    if (sf < 1.0E9)
      c->WritelData(par->sf, &sf, sizeof(float), Offset);
    else
      c->DellData(par->sf, Offset);
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->Obj, Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->Obj, Offset);
    }

  return FALSE;
  }

BOOL SetContrast (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  SetContrast_par FAR *par = (SetContrast_par FAR *)param;
  int num_pars = ((par->par_Size - sizeof(SetContrast_par)) / sizeof(par->ref[0])) + 1;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPPALINFO lppi = (LPPALINFO)c->DrawContext()->GetDocumentExtraData(DED_PALETTEINFO);
    if ((lppi != NULL) && (lppi->gray) && (lppi->actpal != NULL)) {
      float FAR *lpcontrast = (float FAR *)c->ReadlData(par->contrast);
      float FAR *lpbrightness = (float FAR *)c->ReadlData(par->brightness);
      if ((lpcontrast != NULL) && (lpbrightness != NULL)) {
        HDC hDC = GetDC(c->OutWnd());
        SetContrast(lppi->actpal,hDC,*lpcontrast,*lpbrightness);
        if (BitsPerPixel() != 8) {
          int AnzImgs = *((int FAR *)(lppi + 1));
          FrmImage FAR * FAR *lpImages = (FrmImage FAR * FAR *)(LPSTR(lppi + 1) + sizeof(int));
          for (int i = 0; i < AnzImgs; i++) {
            mImage FAR *Img = lpImages[i]->img;
            if (lpImages[i]->Initialized && (Img != NULL)) {
              Img->ResetBMPs();
              lpImages[i]->Invalidate(c->actSide());
              }
            }
          }
        ReleaseDC(c->OutWnd(),hDC);
        }
      }
    }

  if (mode & EM_FIXCONNECTION) {
    c->SetlConnection(par->contrast, Offset);
    c->SetlConnection(par->brightness, Offset);
    for (int i = 0; i < num_pars; i++)
      c->SetlConnection(par->ref[i], Offset);
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    c->ClearlConnection(par->contrast, Offset);
    c->ClearlConnection(par->brightness, Offset);
    for (int i = 0; i < num_pars; i++)
      c->ClearlConnection(par->ref[i], Offset);
    }

  return FALSE;
  }

#pragma pack(1)
struct FrmGetImgInfo_par {
  WORD par_Size;
  DWORD name;                 // String: Imagename
  DWORD compr;                // Index: Kompressionstyp
  DWORD ver;                  // Index: Library - Versionsnummer
  DWORD width;                // Long: Breite des Bildes in Pixel
  DWORD height;               // Long: Hoehe des Bildes in Pixel
  DWORD bits;                 // Index: Anzahl der Bits pro Pixel
  struct {                    // beliebige Anzahl:
    DWORD rtype;              // Typ
    WORD R, I;                // Referenz
    } Ref[1];                 // zusaetzliche Infos zum Bild
  };
#pragma pack()

BOOL FrmGetImgInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  BOOL res = FALSE;
  if (mode & EM_LOAD) {
    FrmGetImgInfo_par FAR *par = (FrmGetImgInfo_par FAR *) param;
    LPSTR name = (LPSTR)c->ReadlData(par->name);
    if (name != NULL) {
      BITMAPINFOHEADER bmih;
      WORD compr,ver;
      GLOBALHANDLE AddlInfo;
      int AddlInfoLen;
      if (GetImageInfo(name,&bmih,&compr,&ver,&AddlInfo,&AddlInfoLen)) {
        c->WritelData(par->compr, &compr, sizeof(WORD), Offset);
        c->WritelData(par->ver, &ver, sizeof(WORD), Offset);
        c->WritelData(par->width, &bmih.biWidth, sizeof(LONG), Offset);
        c->WritelData(par->height, &bmih.biHeight, sizeof(LONG), Offset);
        c->WritelData(par->bits, &bmih.biBitCount, sizeof(WORD), Offset);
        int num_pars = ((par->par_Size - sizeof(FrmGetImgInfo_par)) /
                       sizeof(par->Ref[0])) + 1;
        LPVOID AddlInfoBlock = GlobalLock(AddlInfo);
        for (int i = 0; i < num_pars; i++) {
          LPVOID data;
          WORD len;
          if (GetAddlInfoById(AddlInfoBlock,AddlInfoLen,WORD(c->ReadConstInt (par->Ref[i].rtype)),&data,&len) && (len > 0))
            c->WriteData(par->Ref[i].R, par->Ref[i].I, data, len, Offset);
          else
            c->DelData(par->Ref[i].R, par->Ref[i].I, Offset);
          }
        GlobalUnlock(AddlInfo);
        GlobalFree(AddlInfo);
        res = TRUE;
        }
      }
    }
  return res;
  }

#pragma pack(1)
struct FrmLoadDIB_par {
  WORD par_Size;
  DWORD DIB;
  DWORD name;                 // String: Imagename
  };
#pragma pack()

BOOL FrmLoadDIB (mdiChild *c,LPVOID param,WORD mode)
  {
  LPSTR Offset = LPSTR(param) - sizeof(WORD);
  if (mode & EM_LOAD) {
    FrmLoadDIB_par FAR *par = (FrmLoadDIB_par FAR *) param;
    LPSTR name = (LPSTR)c->ReadlData(par->name);
    if (name != NULL) {
      GLOBALHANDLE hDIB = GetImage(name);
      if (hDIB != NULL)
        c->WritelData(par->DIB, &hDIB, sizeof(GLOBALHANDLE), Offset);
      else
        c->DellData(par->DIB, Offset);
      }
    else
      c->DellData(par->DIB, Offset);
    }
  return FALSE;
  }

#pragma pack(1)
struct FrmSaveDIB_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // welches Objekt soll gespeichert werden
  WORD fileR,fileI;           // file handle
  WORD comprR,comprI;         // Index: Kompressionstyp
  struct {                    // beliebige Anzahl:
    DWORD rtype;              // Typ
    WORD R, I;                // Referenz
    } Ref[1];                 // zusaetzliche Infos zum Bild
  };
#pragma pack()

BOOL FrmSaveDIB (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmSaveDIB_par FAR *par = (FrmSaveDIB_par FAR *) param;
    GLOBALHANDLE FAR *lpDIB = 
        (GLOBALHANDLE FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((lpDIB != NULL) && (*lpDIB != NULL)) {
      GLOBALHANDLE hAddl = NULL;
      int num_pars = ((par->par_Size - sizeof(FrmSaveDIB_par)) /
                     sizeof(par->Ref[0])) + 1;
      int size = 0;
      for (int i = 0; i < num_pars; i++) {
        LPVOID data = c->ReadData(par->Ref[i].R, par->Ref[i].I);
        int newsize = 0;
        if (data != NULL)
          newsize += GetBlockSize(data);
        if (hAddl == NULL)
          hAddl = GlobalAlloc(GMEM_MOVEABLE, size + 4 + newsize);
        else
          hAddl = GlobalReAlloc(hAddl,size + 4 + newsize,GMEM_MOVEABLE);
        ADDLIMAGEINFO FAR *AddlInfo = (ADDLIMAGEINFO FAR *)(LPSTR(GlobalLock(hAddl)) + size);
        AddlInfo->Id = c->ReadConstInt (par->Ref[i].rtype);
        AddlInfo->Len = newsize;
        if (data != NULL)
          lmemcpy(AddlInfo->data, data, newsize);
        size += 4 + newsize;
        GlobalUnlock(hAddl);
        }
      LPVOID AddlInfo = NULL;
      if (size > 0)
        AddlInfo = GlobalLock(hAddl);
      HFILE FAR *lpfh = (HFILE FAR *)c->ReadData (par->fileR,par->fileI);
      DBWIN_ASSERT(lpfh != NULL);
      LPWORD lpCompressMode = (LPWORD)c->ReadData (par->comprR,par->comprI);
      WORD cm = WORD(lpCompressMode != NULL ? *lpCompressMode : CM_UNCOMPRESSED);
      PutImage(*lpfh, *lpDIB, AddlInfo, size, cm);
      if (size > 0) {
        GlobalUnlock(hAddl);
        GlobalFree(hAddl);
        }
      } 
    }
  return FALSE ;
  }

#pragma pack(1)
struct FrmFreeDIB_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // welches Objekt soll freigegeben werden
  };
#pragma pack()

BOOL FrmFreeDIB (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    FrmFreeDIB_par FAR *par = (FrmFreeDIB_par FAR *) param;
    GLOBALHANDLE FAR *lpDIB = 
        (GLOBALHANDLE FAR *) c->ReadData (par->ObjRec,par->ObjId);
    if ((lpDIB != NULL) && (*lpDIB != NULL))
      GlobalFree(*lpDIB);
    }
  return FALSE ;
  }

#pragma pack(1)
struct DIBFromClipboard_par {
  WORD par_Size;
  DWORD DIB;
  };
#pragma pack()

BOOL DIBFromClipboard (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DIBFromClipboard_par FAR *par = (DIBFromClipboard_par FAR *) param;
    GLOBALHANDLE hDIB = NULL;
    OpenClipboard(NULL);
    GLOBALHANDLE hClipboardDIB = GetClipboardData(CF_DIB);
    if (hClipboardDIB != NULL) {
      DWORD DIBSize = GlobalSize(hClipboardDIB);
      hDIB = GlobalAlloc(GMEM_MOVEABLE,DIBSize);
      if (hDIB != NULL) {
        void HUGE *src = GlobalLock(hClipboardDIB);
        void HUGE *dst = GlobalLock(hDIB);
        hmemcpy(dst,src,DIBSize);
        GlobalUnlock(hClipboardDIB);
        GlobalUnlock(hDIB);
        }
      else {
        DBWIN_ASSERT_TEXT(FALSE,"Zuwenig Speicher zum Kopieren des Bildes aus der Zwischenablage !");
        }
      }
    EmptyClipboard();
    CloseClipboard();
    if (hDIB != NULL)
      c->WritelData(par->DIB, &hDIB, sizeof(GLOBALHANDLE), LPSTR(param) - sizeof(WORD));
    else
      c->DellData(par->DIB, LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetWindowPosition_par {
  WORD par_Size;
  DWORD h;
  DWORD x;
  DWORD y;
  };
#pragma pack()

BOOL SetWindowPosition (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetWindowPosition_par FAR *par = (SetWindowPosition_par FAR *) param;
    LPDWORD lph = (LPDWORD)c->ReadlData(par->h);
    LPWORD lpx = (LPWORD)c->ReadlData(par->x);
    LPWORD lpy = (LPWORD)c->ReadlData(par->y);
    if ((lph != NULL) && (*lph != NULL) && (lpx != NULL) && (lpy != NULL)) {
      HWND wh = (HWND) *lph;
      SetWindowPos(wh,NULL,*lpx,*lpy,0,0,SWP_NOSIZE | SWP_NOZORDER);
      }
    }
  return FALSE ;
  }

#pragma pack(1)
struct MCICommand_par {
  WORD par_Size;
  DWORD res;
  DWORD cmd;
  DWORD hWnd;
  };
#pragma pack()

BOOL MCICommand (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MCICommand_par FAR *par = (MCICommand_par FAR *) param;
    LPSTR lpCmd = (LPSTR)c->ReadlData(par->cmd);
    HWND hCallBack = NULL;
    if (par->par_Size >= sizeof(MCICommand_par)) {
      HWND *lphWnd = (HWND *)c->ReadlData(par->hWnd);
      if (lphWnd != NULL)
        hCallBack = *lphWnd;
      }
    if ((lpCmd != NULL) && (*lpCmd != '\0')) {
      char ResStr[130];
      DWORD error = mciSendString(lpCmd,ResStr,sizeof(ResStr) - 1,hCallBack);
      if (error != 0) {
        if (!mciGetErrorString(error,ResStr,sizeof(ResStr) - 1))
          wsprintf(ResStr,"unknown MCI error (%ld)",error);
        }
      c->WritelData(par->res, ResStr, lstrlen(ResStr) + 1, LPSTR(param) - sizeof(WORD));
      }
    }
  return FALSE ;
  }

