////////////////////////////////////////////////////////
//  Erzeugen der Funktionsprototypen
////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dds32.h"
#include "dds.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "hash.hpp"
#include "btrieve.hpp"
#include "compile.hpp"
#include "syntax.hpp"

#include "fsyntax.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "scripthd.hpp"

struct FncHeader {
  DWORD FncSize;
  DWORD OpSize;
  DWORD EfSize;
  DWORD AsSize;
  DWORD SCndSize;
  DWORD CmpSize;
  };

extern GLOBALHANDLE StoreOpHash(hash *op,BYTE FType,BOOL FAR *IsEmpty);
extern GLOBALHANDLE StoreOpList(LPOPLIST as);
DLLExport int _export WINAPI FunctionPrototypes (LPSTR fname)
  {
  FncCompiler FAR *f = new FncCompiler ();
  f->DoParse (fname,&fprot,NULL);
  BOOL IsEmpty;
  if (f->wError == 0) {
    // Speichern der Hashtabelle als solche
    GLOBALHANDLE hGfmem = f->hFcHash->StoreHugeHash ();
    GLOBALHANDLE hOpmem = StoreOpHash(f->hopHash,FTYPE_NORMAL,&IsEmpty);
    GLOBALHANDLE hEfmem = StoreOpHash(f->hefHash,FTYPE_NORMAL,&IsEmpty);
    GLOBALHANDLE hAsmem,hSCndmem;
    if (f->hasList)
      hAsmem = StoreOpList(f->hasList);
    else
      hAsmem = 0;
    if (f->hcndList)
      hSCndmem = StoreOpList(f->hcndList);
    else
      hSCndmem = 0;
    GLOBALHANDLE hCmpmem = StoreOpHash(f->hcmpHash,FTYPE_NORMAL,&IsEmpty);
    FncHeader hd;
    hd.FncSize  = GlobalSize (hGfmem);
    hd.OpSize   = GlobalSize (hOpmem);
    hd.EfSize   = GlobalSize (hEfmem);
    hd.AsSize   = (hAsmem) ? GlobalSize (hAsmem) : 0 ;
    hd.SCndSize = (hSCndmem) ? GlobalSize (hSCndmem) : 0 ;
    hd.CmpSize  = GlobalSize (hCmpmem);
    DWORD gSize = sizeof(hd) + hd.FncSize + hd.OpSize + hd.EfSize + 
                               hd.AsSize + hd.SCndSize + hd.CmpSize ;
    GLOBALHANDLE hGtmp = GlobalAlloc (GMEM_MOVEABLE,gSize);
    LPSTR Buffer = LPSTR(GlobalLock (hGtmp));
    lmemcpy (Buffer,&hd,sizeof(hd));
    LPSTR h = Buffer + sizeof(hd);
    hmemcpy (h,GlobalLock (hGfmem),hd.FncSize);
    h = LPSTR ((char huge *) h + hd.FncSize) ;
    hmemcpy (h,GlobalLock (hOpmem),hd.OpSize);
    h = LPSTR ((char huge *) h + hd.OpSize) ;
    hmemcpy (h,GlobalLock (hEfmem),hd.EfSize);
    h = LPSTR ((char huge *) h + hd.EfSize) ;
    if (hAsmem) {
      hmemcpy (h,GlobalLock (hAsmem),hd.AsSize);
      h = LPSTR ((char huge *) h + hd.AsSize) ;
      }
    if (hSCndmem) {
      hmemcpy (h,GlobalLock (hSCndmem),hd.SCndSize);
      h = LPSTR ((char huge *) h + hd.SCndSize) ;
      }
    hmemcpy (h,GlobalLock (hCmpmem),hd.CmpSize);
    h = LPSTR ((char huge *) h + hd.CmpSize) ;

    GlobalUnlock(hGfmem);
    GlobalFree (hGfmem);
    GlobalUnlock(hOpmem);
    GlobalFree (hOpmem);
    GlobalUnlock(hEfmem);
    GlobalFree (hEfmem);
    if (hAsmem) {
      GlobalUnlock(hAsmem);
      GlobalFree (hAsmem);
      }
    if (hSCndmem) {
      GlobalUnlock(hSCndmem);
      GlobalFree (hSCndmem);
      }
    GlobalUnlock(hCmpmem);
    GlobalFree (hCmpmem);

    WriteScriptData (2,"_FDEF",hGtmp,gSize);

    GlobalUnlock (hGtmp);
    GlobalFree (hGtmp);
    }
  int error = f->wError ;
  delete f;
  return error;
  }

void GetOpHash(GLOBALHANDLE hGmem,hash *res,LPSTR Prefix,int nFType,LPSCRIPTCONTENT scent);
extern LPOPLIST GetOpList(GLOBALHANDLE hGmem);
void LoadFuncHashs(GLOBALHANDLE hGmem,compiler *cmp)
  {
  FncHeader FAR *hd = (FncHeader FAR *) GlobalLock (hGmem);
  GLOBALHANDLE hGfmem,hOpmem,hEfmem,hAsmem,hSCndmem,hCmpmem;
  if (hd->FncSize)  hGfmem = GlobalAlloc (GMEM_MOVEABLE,hd->FncSize) ;
  else              hGfmem = 0;
  if (hd->OpSize)   hOpmem = GlobalAlloc (GMEM_MOVEABLE,hd->OpSize);
  else              hOpmem = 0;
  if (hd->EfSize)   hEfmem = GlobalAlloc (GMEM_MOVEABLE,hd->EfSize);
  else              hEfmem = 0;
  if (hd->AsSize)   hAsmem = GlobalAlloc (GMEM_MOVEABLE,hd->AsSize);
  else              hAsmem = 0;
  if (hd->SCndSize) hSCndmem = GlobalAlloc (GMEM_MOVEABLE,hd->SCndSize);
  else              hSCndmem = 0;
  if (hd->CmpSize)  hCmpmem = GlobalAlloc (GMEM_MOVEABLE,hd->CmpSize);
  else              hCmpmem = 0;
  LPSTR h = LPSTR(hd+1);
  if (hGfmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hGfmem));
    hmemcpy (Buffer,h,hd->FncSize);
    GlobalUnlock (hGfmem);
    cmp->hFcHash->GetHugeHash (hGfmem);
    GlobalFree (hGfmem);
    }
  if (hOpmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hOpmem));
    h = LPSTR(((char huge *)h) + hd->FncSize);
    hmemcpy (Buffer,h,hd->OpSize);
    GlobalUnlock (hOpmem);
    GetOpHash(hOpmem,cmp->hopHash,NULL,FTYPE_NORMAL,NULL);
    GlobalFree (hOpmem);
    }
  if (hEfmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hEfmem));
    h = LPSTR(((char huge *)h) + hd->OpSize);
    hmemcpy (Buffer,h,hd->EfSize);
    GlobalUnlock (hEfmem);
    GetOpHash(hEfmem,cmp->hefHash,NULL,FTYPE_NORMAL,NULL);
    GlobalFree (hEfmem);
    }
  if (hAsmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hAsmem));
    h = LPSTR(((char huge *)h) + hd->EfSize);
    hmemcpy (Buffer,h,hd->AsSize);
    GlobalUnlock (hAsmem);
    cmp->hasList = GetOpList(hAsmem);
    GlobalFree (hAsmem);
    }
  if (hSCndmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hSCndmem));
    h = LPSTR(((char huge *)h) + hd->AsSize);
    hmemcpy (Buffer,h,hd->SCndSize);
    GlobalUnlock (hSCndmem);
    cmp->hcndList = GetOpList(hSCndmem);
    GlobalFree (hSCndmem);
    }
  if (hCmpmem) {
    LPSTR Buffer = LPSTR(GlobalLock (hCmpmem));
    h = LPSTR(((char huge *)h) + hd->SCndSize);
    hmemcpy (Buffer,h,hd->CmpSize);
    GlobalUnlock (hCmpmem);
    GetOpHash(hCmpmem,cmp->hcmpHash,NULL,FTYPE_NORMAL,NULL);
    GlobalFree (hCmpmem);
    }
  }
