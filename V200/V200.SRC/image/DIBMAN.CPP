/////////////////////////////////////////////////////////////////////
//
//      Verwaltung der Images
//
/////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/image/rev/dibman.cpv   1.11   20 Nov 1998 14:12:56   Martin  $
// $Log:   P:/marille/clinicum/image/rev/dibman.cpv  $
// 
//    Rev 1.11   20 Nov 1998 14:12:56   Martin
// PutImage: nicht hin- und herchangen, sondern kopieren (scheiss LT10)
// 
//    Rev 1.10   16 Sep 1997 07:45:12   Hannes
// Bilder mit Blobs
// 
//    Rev 1.9   14 Jul 1997 12:44:20   Martin
// FrmgetImgInfo, FrmLoad/SaveDIB
// 
//    Rev 1.8   28 Apr 1997 15:04:30   Martin
// 32-bit-faehig
// 
//    Rev 1.7   25 Apr 1997 12:31:12   Martin
// Bildkomrimierung
// 
//    Rev 1.6   17 Mar 1997 16:42:04   Martin
// LeadTools
// 
//    Rev 1.5   16 Feb 1996 15:17:28   GERHOLD
// #ifndef WIN32 ImgOpenSolo
// 
//    Rev 1.4   02 Feb 1996 10:49:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   08 Dec 1994 21:48:30   HANNES
// 
//    Rev 1.2   15 Nov 1994 12:11:22   MARTIN
// PutImage geaendert
// 
//    Rev 1.1   17 Oct 1994 15:02:28   HANNES
// Synchronisation mit Marille
// 
//    Rev 1.0   24 Jun 1994 16:50:58   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.9   04 Feb 1994 16:44:50   MARTIN
// RemoveDIBListElem entfernt
// 
//    Rev 1.8   29 Nov 1993 08:45:26   HANNES
// Dibmanager eleminiert
// 
//    Rev 1.7   24 Nov 1993 16:37:18   HANNES
// 
//    Rev 1.6   24 Nov 1993 15:12:00   HANNES
// Verbesserten WinAssert
// 
//    Rev 1.5   11 Oct 1993 14:09:06   MARTIN
// #include "dds.hpp" (mit JUST_EM)
// 
//    Rev 1.4   08 Oct 1993 17:15:00   MARTIN
// RemoveDIBListElem exportiert
// 
//    Rev 1.3   04 Oct 1993 17:22:50   HANNES
// GetFullDibName exportiert
// 
//    Rev 1.2   22 Sep 1993 10:58:06   MARTIN
// Version nach St. Poelten
// 
//    Rev 1.1   25 Aug 1993 15:56:34   MARTIN
// Speicherfreigabe
// 
//    Rev 1.0   23 Aug 1993 18:47:36   MARTIN
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <direct.h>
#include "dds32.h"

#include "l_bitmap.h"
#define LT_SUPPORT_GIF "78BY1jl78"
#define LT_SUPPORT_TIF "oam5302FDio"

#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#include "data.hpp"
#define MIMAGE_CLASS
#include "image.hpp"
#define MODULENUM 32
#include "winass.hpp"

struct key_bits {
  unsigned No1 : 5;
  unsigned No2 : 5;
  unsigned No3 : 5;
  unsigned No4 : 1;
  unsigned No4a : 4;
  unsigned No5 : 5;
  unsigned No6 : 5;
  unsigned No7 : 2;
  unsigned No7a : 3;
  unsigned No8 : 5;
  unsigned No9 : 5;
  unsigned No10 : 3;
  unsigned Pn0 : 4;
  unsigned Pn1 : 12;
  unsigned Pn2 : 16;
  unsigned Pn3 : 16;
  };

static char base32dig[32] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'
  };

#define MAX_LEVEL0_DIR 257   // wenn moeglich Primzahl

DLLExport void _export WINAPI GetImageFileName(LPSTR FileName, LPVOID lpkey)
  {
#ifdef UEBERLEGT
  full_key FAR *ImgKey = (full_key FAR *)lpkey;
  WORD PatNo[3];
  lmemcpy(PatNo, ImgKey->bkey.PatientenNummer, 3 * sizeof(WORD));
  PatNo[0] &= ~0xf;   // niedrigstwertige 4 Bits wegmaskieren
  unsigned level0 = ((unsigned)GetCRC(LPSTR(PatNo), 3 * sizeof(WORD))) % (unsigned)MAX_LEVEL0_DIR;
  char fnam[12];
  key_bits FAR *bits = (key_bits FAR *)ImgKey;
  fnam[0] = base32dig[bits->No10];
  fnam[1] = base32dig[bits->No9];
  fnam[2] = base32dig[bits->No8];
  fnam[3] = base32dig[bits->No7 + (bits->No7a << 2)];
  fnam[4] = base32dig[bits->No6];
  fnam[5] = base32dig[bits->No5];
  fnam[6] = base32dig[bits->No4 + (bits->No4a << 1)];
  fnam[7] = '.';
  fnam[8] = base32dig[bits->No3];
  fnam[9] = base32dig[bits->No2];
  fnam[10] = base32dig[bits->No1];
  fnam[11] = '\0';
  sprintf(FileName, "%u\\%04X%04X.%03X\\%X%s", level0, PatNo[2], PatNo[1],
          (PatNo[0] >> 4) & 0x0FFF, int(bits->Pn0), (LPSTR)fnam);
#else
  lstrcpy (FileName,LPSTR(lpkey));
#endif
  }


DLLExport LPSTR _export WINAPI GetFullDIBName(LPSTR FileName)
  {
  static BOOL FirstCall = TRUE;
  static int PathLen = 0;
  static char FullDIBName[128];
  if (FirstCall) {
    if (GetPrivateProfileString (TIFFIMGSECTION,INDEXFILE,INDEXFILEDEF,
                             FullDIBName,sizeof(FullDIBName),
                             MYINI
                            ) > 0
       ) {
      PathLen = lstrlen(FullDIBName);
      }
    FirstCall = FALSE;
    }
  lstrcpy(FullDIBName + PathLen, FileName);
  return FullDIBName;
  }

static GLOBALHANDLE ReadDIB(DWORD DataSize,GLOBALHANDLE hGMem)
  {
  HANDLE hDIB = NULL;

  LONG DIBSize = DataSize;
  WIN_ASSERT (DIBSize >= sizeof(WORD));
  WORD HeaderSize;
  BYTE huge *base = (BYTE huge *) GlobalLock (hGMem);
  HeaderSize = *(WORD FAR *) base;
  base += sizeof(WORD);
  LPIMAGEFILEHEADER Header = (LPIMAGEFILEHEADER)GetGlobMem(HeaderSize);
  Header->HeaderSize = HeaderSize;
  hmemcpy (&Header->Version,base,HeaderSize - sizeof(WORD));
  base += HeaderSize - sizeof(WORD);
  DIBSize -= HeaderSize;
  switch (Header->CompressMode) {
    case CM_RUNLENGTH:
    case CM_UNCOMPRESSED:
      {
      hDIB = GlobalAlloc(GMEM_MOVEABLE, DIBSize);
      if (hDIB == 0) {
        char txt [64];
        wsprintf (txt,"no mem for %ld",DIBSize);
        WIN_ASSERT_TEXT (FALSE,txt);
        }
      BYTE huge *hpDIB = (BYTE huge *)GlobalLock(hDIB);
      hmemcpy (hpDIB,base,DIBSize);
      if (Header->CompressMode == CM_RUNLENGTH) {
        GLOBALHANDLE hDecompressed = DeltaHuffmanToDIB(hDIB);
        WIN_ASSERT(hDecompressed != NULL);
        GlobalFree(hDIB);
        hDIB = hDecompressed;
        }
      }
      break;
    case CM_IM_JPEG:
    case CM_IM_GIF:
    case CM_IM_TIF:
    case CM_LEAD:
      {
      BITMAPINFOHEADER bmih;
      hmemcpy (&bmih,base,sizeof(BITMAPINFOHEADER));
      base += sizeof(BITMAPINFOHEADER);
      HeaderSize += sizeof(BITMAPINFOHEADER);
      DIBSize -= sizeof(BITMAPINFOHEADER);
      hDIB = GlobalAlloc(GMEM_MOVEABLE, DIBSize);
      if (hDIB == 0) {
        char txt [64];
        wsprintf (txt,"no mem for %ld",DIBSize);
        WIN_ASSERT_TEXT (FALSE,txt);
        }
      BYTE huge *hpDIB = (BYTE huge *)GlobalLock(hDIB);
      hmemcpy (hpDIB,base,DIBSize);
      if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
        L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
      if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
        L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
      BITMAPHANDLE LeadBitmap;
      L_INT lterr = L_LoadBitmapMemory((L_CHAR L_FAR *)hpDIB,&LeadBitmap,0,ORDER_BGR,(L_INT32)DIBSize);
      GlobalUnlock(hDIB);
      GlobalFree(hDIB);
      if (lterr < SUCCESS) {
        int err = (int)lterr;
        char txt [64];
        wsprintf (txt,"kann komprimiertes Bild nicht laden (Fehler %d)",err);
        WIN_ASSERT_TEXT (FALSE,txt);
        hDIB = NULL;
        }
      else
        hDIB = L_ChangeToDIB(&LeadBitmap);
      if (hDIB != NULL) {
        LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
        // PelsPerMeter restaurieren (manche Formate vergessen das ...)
        lpbi->biXPelsPerMeter = bmih.biXPelsPerMeter;
        lpbi->biYPelsPerMeter = bmih.biYPelsPerMeter;
        GlobalUnlock(hDIB);
        }
      }
      break;
    default:
      WIN_ASSERT_TEXT(FALSE,"Verwendete Kompression nicht unterstützt!");
    }
  FreeGlobMem(Header);
  GlobalUnlock (hGMem);

  return hDIB;
  }

static GLOBALHANDLE ReadDIB(LPSTR FileName)
  {
  HFILE dib;
  OFSTRUCT dibof;
  HANDLE hDIB = NULL;
  if ((dib = OpenFile(GetFullDIBName(FileName), &dibof, OF_READ | OF_SHARE_DENY_WRITE)) >= 0) {
    LONG DIBSize = _llseek(dib, 0L, SEEK_END);
    WIN_ASSERT (DIBSize >= sizeof(WORD));
    WIN_ASSERT (_llseek(dib, 0L, SEEK_SET) == 0L);
    WORD BytesRead, HeaderSize;
    BytesRead = _lread(dib, &HeaderSize, sizeof(WORD));
    WIN_ASSERT(BytesRead == sizeof(WORD));
    LPIMAGEFILEHEADER Header = (LPIMAGEFILEHEADER)GetGlobMem(HeaderSize);
    Header->HeaderSize = HeaderSize;
    BytesRead = _lread(dib, &Header->Version, HeaderSize - sizeof(WORD));
    WIN_ASSERT(BytesRead == (HeaderSize - sizeof(WORD)));
    DIBSize -= HeaderSize;
    switch (Header->CompressMode) {
      case CM_RUNLENGTH:
      case CM_UNCOMPRESSED:
        {
        hDIB = GlobalAlloc(GMEM_MOVEABLE, DIBSize);
        if (hDIB == 0) {
          char txt [64];
          wsprintf (txt,"no mem for %ld",DIBSize);
          WIN_ASSERT_TEXT (FALSE,txt);
          }
        BYTE huge *hpDIB = (BYTE huge *)GlobalLock(hDIB);
        LONG NumRead = _hread(dib, hpDIB, DIBSize);
        _lclose(dib);
        WIN_ASSERT(NumRead == DIBSize);
        if (Header->CompressMode == CM_RUNLENGTH) {
          GLOBALHANDLE hDecompressed = DeltaHuffmanToDIB(hDIB);
          WIN_ASSERT(hDecompressed != NULL);
          GlobalFree(hDIB);
          hDIB = hDecompressed;
          }
        }
        break;
      case CM_IM_JPEG:
      case CM_IM_GIF:
      case CM_IM_TIF:
      case CM_LEAD:
        {
        BITMAPINFOHEADER bmih;
        BytesRead = _lread(dib, &bmih, sizeof(BITMAPINFOHEADER));
        WIN_ASSERT(BytesRead == (sizeof(BITMAPINFOHEADER)));
        HeaderSize += sizeof(BITMAPINFOHEADER);
        DIBSize -= sizeof(BITMAPINFOHEADER);
        hDIB = GlobalAlloc(GMEM_MOVEABLE, DIBSize);
        if (hDIB == 0) {
          char txt [64];
          wsprintf (txt,"no mem for %ld",DIBSize);
          WIN_ASSERT_TEXT (FALSE,txt);
          }
        BYTE huge *hpDIB = (BYTE huge *)GlobalLock(hDIB);
        LONG NumRead = _hread(dib, hpDIB, DIBSize);
        _lclose(dib);
        WIN_ASSERT(NumRead == DIBSize);
        if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
          L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
        if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
          L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
        BITMAPHANDLE LeadBitmap;
        L_INT lterr = L_LoadBitmapMemory((L_CHAR L_FAR *)hpDIB,&LeadBitmap,0,ORDER_BGR,(L_INT32)DIBSize);
        GlobalUnlock(hDIB);
        GlobalFree(hDIB);
        if (lterr < SUCCESS) {
          int err = (int)lterr;
          char txt [64];
          wsprintf (txt,"kann komprimiertes Bild nicht laden (Fehler %d)",err);
          WIN_ASSERT_TEXT (FALSE,txt);
          hDIB = NULL;
          }
        else
          hDIB = L_ChangeToDIB(&LeadBitmap);
        if (hDIB != NULL) {
          LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
          // PelsPerMeter restaurieren (manche Formate vergessen das ...)
          lpbi->biXPelsPerMeter = bmih.biXPelsPerMeter;
          lpbi->biYPelsPerMeter = bmih.biYPelsPerMeter;
          GlobalUnlock(hDIB);
          }
        }
        break;
      default:
        _lclose(dib);
        WIN_ASSERT_TEXT(FALSE,"Verwendete Kompression nicht unterstützt!");
      }
    FreeGlobMem(Header);
    }
  return hDIB;
  }


DLLExport GLOBALHANDLE _export WINAPI GetImage(LPSTR FileName)
  {
  return ReadDIB(FileName);
  }

DLLExport GLOBALHANDLE _export WINAPI GetImage(DWORD Size,GLOBALHANDLE hGmem)
  {
  return ReadDIB(Size,hGmem);
  }


DLLExport GLOBALHANDLE _export WINAPI ImportImage(LPSTR FileName)
  {
  if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
    L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
  if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
    L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
  BITMAPHANDLE LeadBitmap;
  if (L_LoadBitmap(FileName,&LeadBitmap,0,ORDER_BGR) < SUCCESS)
    return NULL;
  return L_ChangeToDIB(&LeadBitmap);
  }


static BOOL MakeMissingDirs(LPSTR FullFileName, int FileNameLen)
  {
  int PathNameLen = strlen(FullFileName) - FileNameLen;
  char PathName[128];
  strcpy(PathName, FullFileName);
  LPSTR str = FullFileName + PathNameLen;
  LPSTR pstr = PathName + PathNameLen;
  while (*str) {
    while ((*str != '\0') && (*str != '\\')) *pstr++ = *str++;
    if (*str) {
      *pstr = '\0';
//      if (_mkdir(PathName)) return FALSE;
      _mkdir(PathName);
      *pstr++ = *str++;   // backslash verarbeiten
      }
    }
  return TRUE;
  }


DLLExport void _export WINAPI PutImage(HFILE fhand, GLOBALHANDLE hnewDIB, LPVOID AddlInfo, int Len, WORD CompressMode)
  {
  GLOBALHANDLE hCompressed = 0;
  DWORD CompressedSize;
  switch (CompressMode) {
    case CM_UNCOMPRESSED:
      break;
    case CM_RUNLENGTH:
      {
      GLOBALHANDLE hHuffman = DIBToDeltaHuffman(hnewDIB);
      if (hHuffman == NULL)
        CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
      else
        hnewDIB = hHuffman;
      }
      break;
    case CM_IM_JPEG:
    case CM_IM_GIF:
    case CM_IM_TIF:
    case CM_LEAD:
      {
      L_INT nFormat, nQFactor;
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hnewDIB);
      L_INT nBitsPerPixel = lpbi->biBitCount;
      lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
      DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
      char huge *lpbits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
      if (CompressMode == CM_IM_JPEG) {
        nFormat = FILE_JFIF;
        nQFactor = 50;
        }
      if (CompressMode == CM_IM_GIF) {
        if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
          L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
        nFormat = FILE_GIF;
        nQFactor = 0;
        }
      if (CompressMode == CM_IM_TIF) {
        if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
          L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
        nFormat = FILE_CCITT_GROUP4;
        nQFactor = 0;
        }
      if (CompressMode == CM_LEAD) {
        if (nBitsPerPixel == 1) {
          nFormat = FILE_LEAD1BIT;
          nQFactor = 0;
          }
        else {
          nFormat = FILE_LEAD;
          nQFactor = QS;
          }
        }
      BITMAPHANDLE LeadBitmap;
      if (L_ConvertFromDIB(&LeadBitmap,(LPBITMAPINFO)lpbi,(L_UCHAR L_FAR *)lpbits) < SUCCESS) {
        CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
        }
      else {
        L_UINT32 DIBSize;
        if (L_SaveBitmapMemory(&hCompressed,&LeadBitmap,nFormat,nBitsPerPixel,nQFactor,&DIBSize) < SUCCESS) {
          WIN_ASSERT_TEXT (FALSE,"kann Bild im angegebenen Format nicht speichern");
          CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
          }
        else {
          CompressedSize = (DWORD)DIBSize;
          }
        L_FreeBitmap(&LeadBitmap);
        }
      GlobalUnlock(hnewDIB);
      }
      break;
    default:
      CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
      WIN_ASSERT_TEXT(FALSE,"Angegebene Kompression nicht unterstützt!");
    }

  IMAGEFILEHEADER fh;
  fh.HeaderSize = sizeof(IMAGEFILEHEADER) + Len;
  fh.Version = TI_GetVersion();
  fh.CompressMode = CompressMode;
  _lwrite(fhand, LPSTR(&fh), sizeof(IMAGEFILEHEADER));
  _lwrite(fhand, LPSTR(AddlInfo), Len);

  char _huge *lpDIB = LPSTR(GlobalLock(hnewDIB));
  if (hCompressed != 0) {   // mit LeadTools komprimiert
    _lwrite(fhand, lpDIB, sizeof(BITMAPINFOHEADER));  // Header schreiben
    char huge *hpDIB = (char huge *)GlobalLock(hCompressed);
    _hwrite(fhand, hpDIB, CompressedSize);
    GlobalFree(hCompressed);
    }
  else {                    // un- oder selbst komprimiert
    _hwrite(fhand, lpDIB, GlobalSize(hnewDIB));
    if (CompressMode != CM_UNCOMPRESSED)
      GlobalFree(hnewDIB);  // ->hnewDIB enthielt die komprimierten Daten
    }
  }

DLLExport void _export WINAPI PutImage(GLOBALHANDLE FAR *hGres,DWORD FAR *rSize, GLOBALHANDLE hnewDIB, LPVOID AddlInfo, int Len, WORD CompressMode)
  {
  GLOBALHANDLE hCompressed = 0;
  DWORD CompressedSize;
  switch (CompressMode) {
    case CM_UNCOMPRESSED:
      break;
    case CM_RUNLENGTH:
      {
      GLOBALHANDLE hHuffman = DIBToDeltaHuffman(hnewDIB);
      if (hHuffman == NULL)
        CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
      else
        hnewDIB = hHuffman;
      }
      break;
    case CM_IM_JPEG:
    case CM_IM_GIF:
    case CM_IM_TIF:
    case CM_LEAD:
      {
      L_INT nFormat, nQFactor;
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hnewDIB);
      L_INT nBitsPerPixel = lpbi->biBitCount;
      lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
      DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
      char huge *lpbits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
      if (CompressMode == CM_IM_JPEG) {
        nFormat = FILE_JFIF;
        nQFactor = 50;
        }
      if (CompressMode == CM_IM_GIF) {
        if (L_IsSupportLocked(L_SUPPORT_GIFLZW))
          L_UnlockSupport(L_SUPPORT_GIFLZW,LT_SUPPORT_GIF);
        nFormat = FILE_GIF;
        nQFactor = 0;
        }
      if (CompressMode == CM_IM_TIF) {
        if (L_IsSupportLocked(L_SUPPORT_TIFLZW))
          L_UnlockSupport(L_SUPPORT_TIFLZW,LT_SUPPORT_TIF);
        nFormat = FILE_CCITT_GROUP4;
        nQFactor = 0;
        }
      if (CompressMode == CM_LEAD) {
        if (nBitsPerPixel == 1) {
          nFormat = FILE_LEAD1BIT;
          nQFactor = 0;
          }
        else {
          nFormat = FILE_LEAD;
          nQFactor = QS;
          }
        }
      BITMAPHANDLE LeadBitmap;
      if (L_ConvertFromDIB(&LeadBitmap,(LPBITMAPINFO)lpbi,(L_UCHAR L_FAR *)lpbits) < SUCCESS) {
        CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
        }
      else {
        L_UINT32 DIBSize;
        if (L_SaveBitmapMemory(&hCompressed,&LeadBitmap,nFormat,nBitsPerPixel,nQFactor,&DIBSize) < SUCCESS) {
          WIN_ASSERT_TEXT (FALSE,"kann Bild im angegebenen Format nicht speichern");
          CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
          }
        else {
          CompressedSize = (DWORD)DIBSize;
          }
        L_FreeBitmap(&LeadBitmap);
        }
      GlobalUnlock(hnewDIB);
      }
      break;
    default:
      CompressMode = CM_UNCOMPRESSED;  // wenigstens unkomprimiert
      WIN_ASSERT_TEXT(FALSE,"Angegebene Kompression nicht unterstützt!");
    }

  IMAGEFILEHEADER fh;
  fh.HeaderSize = sizeof(IMAGEFILEHEADER) + Len;
  fh.Version = TI_GetVersion();
  fh.CompressMode = CompressMode;

  char _huge *lpDIB = LPSTR(GlobalLock(hnewDIB));
  if (hCompressed != 0) {   // mit LeadTools komprimiert
    *rSize = sizeof(IMAGEFILEHEADER) + Len + sizeof(BITMAPINFOHEADER) + CompressedSize;
    *hGres = GlobalAlloc (GMEM_MOVEABLE,*rSize);
    BYTE huge *base = (BYTE huge *) GlobalLock (*hGres);
    hmemcpy (base,LPSTR(&fh), sizeof(IMAGEFILEHEADER));
    base += sizeof(IMAGEFILEHEADER);
    hmemcpy (base,LPSTR(AddlInfo), Len);
    base += Len;
    hmemcpy (base,lpDIB, sizeof(BITMAPINFOHEADER));  // Header schreiben
    base += sizeof(BITMAPINFOHEADER);
    char huge *hpDIB = (char huge *)GlobalLock(hCompressed);
    hmemcpy (base, hpDIB, CompressedSize);
    GlobalFree(hCompressed);
    }
  else {                    // un- oder selbst komprimiert
    *rSize = sizeof(IMAGEFILEHEADER) + Len + GlobalSize(hnewDIB);
    *hGres = GlobalAlloc (GMEM_MOVEABLE,*rSize);
    BYTE huge *base = (BYTE huge *)GlobalLock (*hGres);
    hmemcpy (base,LPSTR(&fh), sizeof(IMAGEFILEHEADER));
    base += sizeof(IMAGEFILEHEADER);
    hmemcpy (base,LPSTR(AddlInfo), Len);
    base += Len;

    hmemcpy (base, lpDIB, GlobalSize(hnewDIB));
    if (CompressMode != CM_UNCOMPRESSED)
      GlobalFree(hnewDIB);  // ->hnewDIB enthielt die komprimierten Daten
    }
  }

DLLExport BOOL _export WINAPI ImageExist(LPSTR FileName)
  {
  OFSTRUCT dibof;
  if (OpenFile(GetFullDIBName(FileName), &dibof, OF_EXIST) >= 0)
    return TRUE;
  return FALSE;
  }

DLLExport BOOL _export WINAPI GetImageInfo(LPSTR FileName, LPBITMAPINFOHEADER lpbi,
                                           LPWORD CompressMode, LPWORD Version,
                                           LPHANDLE AddlInfo, int FAR *Len)
  {
  HFILE dib;
  OFSTRUCT dibof;
  if ((dib = OpenFile(GetFullDIBName(FileName), &dibof, OF_READ | OF_SHARE_DENY_WRITE)) >= 0) {
    WORD BytesRead, HeaderSize;
    BytesRead = _lread(dib, &HeaderSize, sizeof(WORD));
    WIN_ASSERT(BytesRead == sizeof(WORD));
    LPIMAGEFILEHEADER Header = (LPIMAGEFILEHEADER)GetGlobMem(HeaderSize);
    BytesRead = _lread(dib, &Header->Version, HeaderSize - sizeof(WORD));
    WIN_ASSERT(BytesRead == (HeaderSize - sizeof(WORD)));
    *CompressMode = Header->CompressMode;
    *Version = Header->Version;
    int AddlSize = HeaderSize - sizeof(IMAGEFILEHEADER);
    if (AddlSize > 0) {
      *AddlInfo = GlobalAlloc(GMEM_MOVEABLE, AddlSize);
      LPVOID addl = GlobalLock(*AddlInfo);
      lmemcpy(addl,Header + 1,AddlSize);
      *Len = AddlSize;
      }
    else {
      *AddlInfo = NULL;
      *Len = 0;
      }
    BytesRead = _lread(dib, lpbi, sizeof(BITMAPINFOHEADER));
    WIN_ASSERT(BytesRead == (sizeof(BITMAPINFOHEADER)));
    _lclose(dib);
    FreeGlobMem(Header);
    return TRUE;
    }
  return FALSE;
  }


DLLExport BOOL _export WINAPI GetAddlInfoById(LPVOID AddlInfoBlock, int AddlInfoLen,
                                              WORD Id, LPVOID FAR *Data, LPWORD Len)
  {
  ADDLIMAGEINFO FAR *act = (ADDLIMAGEINFO FAR *)AddlInfoBlock;
  while ((LPSTR(act) - LPSTR(AddlInfoBlock)) < AddlInfoLen) {
    if (act->Id == Id) {
      *Data = act->data;
      *Len = act->Len;
      return TRUE;
      }
    act = (ADDLIMAGEINFO FAR *)(act->data + act->Len);
    }
  return FALSE;
  }

