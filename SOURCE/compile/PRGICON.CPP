//////////////////////////////////////////////////////////////
//  Lesen und bearbeiten der Icons
//////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/compile/rev/prgicon.cpv   1.2   26 Mar 1999 18:15:28   Wolfgang  $
//  $Log:   P:/marille/clinicum/compile/rev/prgicon.cpv  $
// 
//    Rev 1.2   26 Mar 1999 18:15:28   Wolfgang
// 1.) GetIncludeFileName vom Source-Pfad.
// 
//    Rev 1.1   02 Feb 1996 10:41:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:37:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   08 Oct 1993 17:55:44   HANNES
// data.hpp changed
// 
//    Rev 1.0   20 Jul 1993 12:38:36   HANNES
// Initial revision.
// 
//    Rev 1.0   20 Jul 1993 12:37:18   HANNES
// Initial revision.
//////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#define JUST_EM
#include "dds.hpp"
#include "data.hpp"
#include "btrieve.hpp"
#include "compile.hpp"

struct tagICONFILEHEADER {
  WORD wReserved;         // Always 0
  WORD wResourceType;     // 1 = icon
  WORD wResourceCount;    // Number of icons in the file
  };

typedef struct tagICONFILEHEADER ICONFILEHEADER;

struct tagICONFILERES {
  BYTE  bWidth;         // Width of image
  BYTE  bHeight;        // Height of image
  BYTE  bColorCount;    // Number of colors in image (2, 8, or 16)
  BYTE  bReserved1;     // Reserved
  WORD  wReserved2;
  WORD  wReserved3; 
  DWORD dwDIBSize;      // Size of DIB for this image
  DWORD dwDIBOffset;    // Offset to DIB for this image
  };

typedef struct tagICONFILERES ICONFILERES;

GLOBALHANDLE ReadProgIcon (LPSTR IconName,WORD FAR *IconSize)
  {
  OFSTRUCT Of;
  GLOBALHANDLE hDIB = 0;
  *IconSize = 0;
  int hFile = OpenFile (IconName,&Of,OF_READ) ;
  if (hFile < 0) {
     char IncPath[128];
     char IncPath1[128];
     GetIncludeFileName (IconName,IncPath,IncPath1,"source");
     hFile = OpenFile (IncPath,&Of,OF_READ) ;
     }
  if (hFile >= 0) {
    // Und los kanns gehen
    ICONFILEHEADER iconFileHead;   // ICON file header structure
    ICONFILERES iconFileRes;       // ICON file resource
    WORD cbHead, cbRes, cbBits;     // Used for reading in file
    LPBITMAPINFO lpDIB;  // Pointer to DIB memory

    // Open and read the .ICO file header and the first ICONFILERES

    cbHead = _lread(hFile, (LPSTR)&iconFileHead, sizeof(ICONFILEHEADER));
    cbRes = _lread(hFile, (LPSTR)&iconFileRes, sizeof(ICONFILERES));

    if ((cbHead != sizeof(ICONFILEHEADER)) || (cbRes != sizeof(ICONFILERES)))
      return NULL;

    // Verify that its an .ICON file
    if (iconFileHead.wResourceType != 1)
      return NULL;

    // Allocate and lock memory to read in the DIB
    hDIB = GlobalAlloc(GHND, iconFileRes.dwDIBSize);
    if (hDIB == NULL)
      return NULL;
    lpDIB = (LPBITMAPINFO)GlobalLock(hDIB);

    // Now read the DIB portion of the file, which follows the 
    // end of icon resource table
    _llseek(hFile, iconFileRes.dwDIBOffset, 0);
    cbBits = _lread(hFile, (LPSTR)lpDIB, (WORD)iconFileRes.dwDIBSize);

    // Done reading file
    _lclose(hFile);

    if ((DWORD)cbBits != iconFileRes.dwDIBSize) {
      GlobalUnlock(hDIB);
      GlobalFree(hDIB);
      return NULL;
      }
    *IconSize = cbBits;
    GlobalUnlock(hDIB);
    }

  return hDIB;
  }

