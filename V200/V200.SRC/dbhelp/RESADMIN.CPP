////////////////////////////////////////////////////////////////////////
//  Verwaltung der Resourcen
////////////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/dbhelp/rev/resadmin.cpv   1.9   01 May 2000 13:34:56   Hannes  $
//  $Log:   F:/marille/clinicum/dbhelp/rev/resadmin.cpv  $
// 
//    Rev 1.9   01 May 2000 13:34:56   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.8   05 Oct 1998 11:09:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.7   19 Aug 1998 21:39:50   Hannes
// GetSourceFileName
// 
//    Rev 1.6   19 Nov 1997 18:45:44   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.5   17 Jun 1996 15:46:06   HANNES
// Einbau von BLOBS
// 
//    Rev 1.4   04 Feb 1996 15:36:18   gerhold
// Teile von DBHELP in DDSMEM
// 
//    Rev 1.3   02 Feb 1996 10:42:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   21 Jun 1995 16:11:54   hannes
// Bitmaps lesen, die groesser als 64k sind.
// 
//    Rev 1.1   11 Jul 1994 21:30:10   HANNES
// GetWMFID
// 
//    Rev 1.0   24 Jun 1994 16:44:50   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "resadmin.hpp"
#include "hash.hpp"
#include "btrieve.hpp"
#define NOCOMPILE
#include "compile.hpp"
#define MODULENUM 92
#include "winass.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"

extern HINSTANCE hLibInst;

#define MAXSIZE 0x0000FFFF
DLLExport void _export WINAPI WriteResourceData (short type,short typetowrite,LPSTR fName,GLOBALHANDLE hGres,DWORD DataSize);
DLLExport BOOL _export WINAPI StoreBitmap (LPSTR Bmp,LPSTR fname,int xd,int yd,int type)
  {
  OFSTRUCT Of;
  int mfile = OpenFile (fname,&Of,OF_READ) ;
  if (mfile < 0) {
     char IncPath[128];
     char IncPath1[128];
     GetIncludeFileName (fname,IncPath,IncPath1,"source");
     mfile = OpenFile (IncPath,&Of,OF_READ) ;
     }
  if (mfile >= 0) {
    DWORD FileLen = _llseek (mfile, 0, SEEK_END);
    _llseek (mfile, 0, SEEK_SET);
    
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND, FileLen + sizeof(WORD) * 2);
    char huge *source = LPSTR(GlobalLock (hGtmp));

    DWORD dwSize = FileLen;
    UINT nBytes;
    char huge *tmp = source + sizeof(WORD) * 2;
    while (dwSize) {
      nBytes = dwSize > (DWORD)MAXSIZE ? MAXSIZE : LOWORD (dwSize);
 
      WIN_ASSERT (_lread (mfile, tmp, nBytes) == nBytes);
 
      dwSize  -= nBytes;
      tmp += nBytes;
      }

    _lclose (mfile);

    LPWORD h = LPWORD(source);
    h[0] = xd;
    h[1] = yd;
    WriteResourceData (type,Bmp,hGtmp,FileLen + 2 * sizeof(WORD));

    GlobalUnlock (hGtmp);
    GlobalFree (hGtmp);
    return TRUE ;
    }
  else
    return FALSE ;
  }

DLLExport BOOL _export WINAPI StoreWMF (LPSTR Wmf,LPSTR fname)
  {
  OFSTRUCT Of;
  int mfile = OpenFile (fname,&Of,OF_READ) ;
  if (mfile < 0) {
     char IncPath[128];
     char IncPath1[128];
     GetIncludeFileName (fname,IncPath,IncPath1,"source");
     mfile = OpenFile (IncPath,&Of,OF_READ) ;
     }
  if (mfile >= 0) {
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND,MAXSIZE);
    char FAR *source = LPSTR(GlobalLock (hGtmp));
    WORD Size = _lread (mfile,source,MAXSIZE);
    _lclose (mfile);
    // Test, ob Metafile wohl nicht corrupt ist
    METAHEADER FAR *hd = (METAHEADER FAR *) source ;
    if (hd -> mtHeaderSize != sizeof (METAHEADER) / 2) {
      // Probieren, 22 Byte hinter dem Beginn
      hd = (METAHEADER FAR *) (source + 22) ;                // !!! ??? !!!
      if (hd->mtHeaderSize != sizeof (METAHEADER) / 2) {
        hd = NULL ;
        GlobalUnlock (hGtmp);
        GlobalFree (hGtmp);
        hGtmp = 0 ;
        }
      else {
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
    if (hGtmp) {
      source = LPSTR(GlobalLock (hGtmp));
      WriteResourceData (RESTYPE_WMF,Wmf,hGtmp,Size);
      GlobalUnlock (hGtmp);
      GlobalFree (hGtmp);
      return TRUE ;
      }
    else
      return FALSE ;
    }
  return FALSE ;
  }

static GLOBALHANDLE PushEntry (GLOBALHANDLE hGmem,WORD Type,DWORD ResID,LPSTR name,DWORD FAR *oSize)
  {
  DWORD Size = *oSize + sizeof(Res_CEntry) + lstrlen(name);
  if (hGmem) hGmem = GlobalReAlloc (hGmem,Size,GMEM_MOVEABLE);
  else       hGmem = GlobalAlloc   (GMEM_MOVEABLE | GMEM_ZEROINIT,Size + sizeof(Res_CHead)) , 
             *oSize = sizeof(Res_CHead);
  Res_CHead FAR *lpHead = (Res_CHead FAR *) GlobalLock (hGmem);
  LPRESCENT ent = LPRESCENT (LPSTR(lpHead) + *oSize);
  ent->ResID = ResID ;
  ent->Type  = Type ;
  lstrcpy (ent->name,name);
  lpHead->AnzEntrys ++ ;
  (*oSize) += sizeof(*ent) + lstrlen(name);

  return hGmem;
  }

DLLExport void _export WINAPI CreateResContent ()
  {
  GLOBALHANDLE hGres = 0;
  DWORD cSize = 0;

  DBRecord FAR *r ;

  DBList FAR *allres = GetAllResourceData (RESTYPE_BITMAP);
  for (r = allres->GetFirst() ; r != NULL ; r = allres->GetNext(r) ) {
    hGres = PushEntry (hGres,RESTYPE_BITMAP,*(LONG FAR *) r->Get(0),LPSTR (r->Get(1)),&cSize);
    }
  delete allres ;

  allres = GetAllResourceData (RESTYPE_BITMAP8_6);
  for (r = allres->GetFirst() ; r != NULL ; r = allres->GetNext(r) ) {
    hGres = PushEntry (hGres,RESTYPE_BITMAP8_6,*(LONG FAR *) r->Get(0),LPSTR (r->Get(1)),&cSize);
    }
  delete allres ;

  allres = GetAllResourceData (RESTYPE_WMF);
  for (r = allres->GetFirst() ; r != NULL ; r = allres->GetNext(r) ) {
    hGres = PushEntry (hGres,RESTYPE_WMF,*(LONG FAR *) r->Get(0),LPSTR (r->Get(1)),&cSize);
    }
  delete allres ;

  WriteResourceData (RESTYPE_CONT,"_CONT",hGres,cSize);
  GlobalFree   (hGres);
  }

static GLOBALHANDLE hGResCont;
static Res_CHead FAR *lpRsHd;
static int ContCount;
DLLExport void _export WINAPI ReadResContent ()
  {
  if (ContCount ++ == 0) {
    DWORD DataSize;
    hGResCont = ReadResourceData (RESTYPE_CONT,"_CONT",&DataSize);
    if (hGResCont)
      lpRsHd = (Res_CHead FAR *) GlobalLock (hGResCont);
    }
  }

DLLExport void _export WINAPI UnloadResContent ()
  {
  if (-- ContCount == 0) {
    if (hGResCont) 
      GlobalUnlock(hGResCont) , GlobalFree (hGResCont);
    hGResCont = 0;
    lpRsHd = NULL;
    }
  }

DLLExport void _export WINAPI FillResDlg (HWND hDlg,WORD Id)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
      char dlgtxt[128];
      char enttype[64];
      char rnr[64];
      wsprintf (dlgtxt,"%s\t%s\t%s",lpEnt->GetEntType(enttype),lpEnt->GetName(),lpEnt->GetResID(rnr));
      SendDlgItemMessage (hDlg,Id,LB_ADDSTRING,0,LONG(LPSTR(dlgtxt)));
      }
    }
  }

static WORD GetType (DWORD Id)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next())
      if (lpEnt->ResID == Id)
        return lpEnt->Type;
    }
  return 0;
  }

DLLExport GLOBALHANDLE _export WINAPI GetResource (DWORD Id,WORD FAR *Type,DWORD FAR *DataSize)
  {
  *Type = GetType (Id);
  return ReadResourceData (Id,DataSize);
  }

DLLExport void _export WINAPI GetResourceInfo (int Sel,LPSTR TypeName,LPSTR RsName,DWORD FAR *Id)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
      if (WORD(Sel) == i) {
        lpEnt->GetEntType(TypeName);
        lstrcpy (RsName,lpEnt->GetName());
        *Id = lpEnt->ResID;
        break ;
        }
      }
    }
  }

DLLExport LPRESCENT _export WINAPI GetFirstResourceInfo()
  {
  if (lpRsHd != NULL)
    return (lpRsHd->AnzEntrys > 0) ? LPRESCENT(lpRsHd + 1) : NULL ;
  else
    return NULL;
  }
  
DLLExport LPRESCENT _export WINAPI GetNextResourceInfo(LPRESCENT h,WORD Nr)
  {
  return (Nr < lpRsHd->AnzEntrys) ? h->Next() : NULL ;
  }

DLLExport DWORD _export WINAPI GetBitmapID (LPSTR Name)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
      if ((lpEnt->Type == RESTYPE_BITMAP) && 
            (lstrcmp (lpEnt->GetName(),Name) == 0)) return lpEnt->ResID;
      }
    }
  return 0xFFFFFFFF;
  }

DLLExport DWORD _export WINAPI GetBitmap8x6ID (LPSTR Name)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
      if ((lpEnt->Type == RESTYPE_BITMAP8_6) && 
            (lstrcmp (lpEnt->GetName(),Name) == 0)) return lpEnt->ResID;
      }
    }
  return 0xFFFFFFFF;
  }

DLLExport DWORD _export WINAPI GetWMFID (LPSTR Name)
  {
  if (lpRsHd != NULL) {
    LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
    for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
      if ((lpEnt->Type == RESTYPE_WMF) && 
            (lstrcmp (lpEnt->GetName(),Name) == 0)) return lpEnt->ResID;
      }
    }
  return 0xFFFFFFFF;
  }

DLLExport DWORD _export WINAPI TransformResID (DWORD ID,short resX)
  {
  DWORD res = ID;
  if (resX == 800) {
    if (lpRsHd == NULL) ReadResContent ();
    if (lpRsHd != NULL) {
      LPRESCENT lpEnt = LPRESCENT(lpRsHd + 1);
      for (WORD i = 0 ; i < lpRsHd->AnzEntrys ; i++ , lpEnt = lpEnt->Next()) {
        if ((lpEnt->ResID == res) && (lpEnt->Type == RESTYPE_BITMAP)) {
          DWORD res1 = GetBitmap8x6ID (lpEnt->GetName());
          if (res1 != 0xFFFFFFFF)
            res = res1;
          break ;
          }
        }
      }
    }
  return res;
  }

