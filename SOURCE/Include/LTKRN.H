/*[]=====================================================================[]*/
/*[]     LeadTools Run Time Library - Version 9                          []*/
/*[]                                                                     []*/
/*[]                                                                     []*/
/*[]     Copyright (c) 1991-1998  by LEAD Technologies, Inc.             []*/
/*[]     All Rights Reserved.                                            []*/
/*[]=====================================================================[]*/

/*
   LTKRN.H - kernel module header file
*/

#ifndef _LTKRN_H_
#define _LTKRN_H_

#include "lttyp.h"
#include "lterr.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_UnlockSupport and L_IsSupportLocked
*/
#define L_SUPPORT_EXPRESS        0
#define L_SUPPORT_GIFLZW         1
#define L_SUPPORT_TIFLZW         2
#define L_SUPPORT_FPXEXTENSIONS  3
#define L_SUPPORT_OCR            4
#define L_SUPPORT_VIDEO          5
#define L_SUPPORT_MEDICAL        6
#define L_SUPPORT_MAX            6

/*
   flags for L_ColorResBitmap
*/
#define CRF_FIXEDPALETTE        0x01   /* versus custom palette */
#define CRF_OPTIMIZEDPALETTE    0x02   /* versus fixed palette */
#define CRF_IDENTITYPALETTE     0x08   /* versus ALL 256 colors */
#define CRF_USERPALETTE         0x10   /* user generated palette */
#define CRF_FASTMATCHPALETTE    0x20   /* With user, for fast color match */
#define CRF_NETSCAPEPALETTE     0x40   /* use netscape fixed palette */
#define CRF_BYTEORDERBGR        0x04   /* versus RGB */
#define CRF_BYTEORDERRGB        0x00   /* versus BGR */
#define CRF_BYTEORDERGRAY       0x80   /* Convert to grayscale (12 & 16 bit only) */
#define CRF_PALETTEOPTIONS      0xFF   /* Mask to find palette option */

#define CRF_NODITHERING              0x00000000 /* No Dithering */
#define CRF_FLOYDSTEINDITHERING      0x00010000 /* Floyd Stein Dithering */
#define CRF_STUCKIDITHERING          0x00020000 /* Stucki Dithering */
#define CRF_BURKESDITHERING          0x00030000 /* Burkes Dithering */
#define CRF_SIERRADITHERING          0x00040000 /* Sierra Dithering */
#define CRF_STEVENSONARCEDITHERING   0x00050000 /* Stevenson Arce Dithering */
#define CRF_JARVISDITHERING          0x00060000 /* Jarvis Dithering */
#define CRF_ORDEREDDITHERING         0x00070000 /* Ordered Dithering */
#define CRF_CLUSTEREDDITHERING       0x00080000 /* Clustered Dithering */
#define CRF_DITHERINGOPTIONS         0x00FF0000 /* Mask to find dither option */

#define RGB_RESERVED                 0x01 /* Do not map to the entry */
#define RGB_EMPTY                    0x02 /* The entry is empty */

/*
   flags for L_CombineBitmap
*/
#define CB_SRC_NOP 0x00000000
#define CB_SRC_NOT 0x00000001
#define CB_SRC_0   0x00000002
#define CB_SRC_1   0x00000003
#define CB_DST_NOP 0x00000000
#define CB_DST_NOT 0x00000010
#define CB_DST_0   0x00000020
#define CB_DST_1   0x00000030
#define CB_OP_AND    0x00000000
#define CB_OP_OR     0x00000100
#define CB_OP_XOR    0x00000200
#define CB_OP_ADD    0x00000300
#define CB_OP_SUBSRC 0x00000400
#define CB_OP_SUBDST 0x00000500
#define CB_OP_MUL    0x00000600
#define CB_OP_DIVSRC 0x00000700
#define CB_OP_DIVDST 0x00000800
#define CB_OP_AVG    0x00000900
#define CB_OP_MIN    0x00000A00
#define CB_OP_MAX    0x00000B00
#define CB_RES_NOP 0x00000000
#define CB_RES_NOT 0x00001000
#define CB_RES_0   0x00002000
#define CB_RES_1   0x00003000

// useful define for copying the source to the destination
#define L_SRC_COPY (CB_DST_0 | CB_SRC_NOP | CB_OP_OR)

/*
   return values of L_IsGrayScaleBitmap
*/
#define GRAY_NO               0  /* not grayscale */
#define GRAY_ORDEREDNORMAL    1  /* contains a normally ordered grayscale palette */
#define GRAY_ORDEREDINVERSE   2  /* contains a reverse ordered grayscale palette */
#define GRAY_NOTORDERED       3  /* contains a non-ordered grayscale palette */

/*
   flags for L_VersionInfo
*/
#define TOOLKIT_LEVEL_EXP            0x00 /* Document Express Toolkit. */
#define TOOLKIT_LEVEL_PRO            0x01 /* Professional Toolkit. */
#define TOOLKIT_LEVEL_MEDICAL        0x02 /* Medical Express Toolkit. */

/*
   Dithering methods. To be used for DitheringMethod in BITMAPHANDLE.
*/
#define NO_DITHERING              0
#define FLOYD_STEIN_DITHERING     1
#define STUCKI_DITHERING          2
#define BURKES_DITHERING          3
#define SIERRA_DITHERING          4
#define STEVENSON_ARCE_DITHERING  5
#define JARVIS_DITHERING          6
#define ORDERED_DITHERING         7
#define CLUSTERED_DITHERING       8
#define LAST_DITHERING            8

/*
   bitmap data colors order
*/
#define ORDER_RGB                 0 /* RGB ordering */
#define ORDER_BGR                 1 /* BRG ordering */
#define ORDER_GRAY                2 /* Gray pixels */
#define ORDER_RGBORGRAY           3 /* Valid only for L_LoadXXX functions - gray or RGB */
#define ORDER_BGRORGRAY           4 /* Valid only for L_LoadXXX functions - gray or BGR */

/*
   view perspectives
*/
#define TOP_LEFT              0  /* Top-left of image is first in memory */
#define TOP_RIGHT             1  /* Top-right of image is first in memory */
#define BOTTOM_LEFT           2  /* Bottom-left of image is first in memory */
#define BOTTOM_RIGHT          3  /* Bottom-right of image is first in memory */

#define RIGHT_TOP             4  /* First row is the right side, first column is top side */
#define TOP_LEFT90            4  /* RIGHT_TOP is TOP_LEFT rotated clocwise by 90 degrees */ 
#define LEFT_BOTTOM           8  /* First row is the left side, first column is top side */
#define TOP_LEFT270           8  /* LEFT_BOTTOM is TOP_LEFT rotated clocwise by 270 degrees */ 

/* helper macros for dealing with rotated bitmap view perspectives */
#define ISROTATED(pBitmap) ((pBitmap)->ViewPerspective == TOP_LEFT90 || (pBitmap)->ViewPerspective == TOP_LEFT270)
#define BITMAPWIDTH(pBitmap) (ISROTATED(pBitmap)?(pBitmap)->Height:(pBitmap)->Width)
#define BITMAPHEIGHT(pBitmap) (ISROTATED(pBitmap)?(pBitmap)->Width:(pBitmap)->Height)

/* helper macro to determine whether a bitmap is 12 or 16 bit grayscale */
#define ISGRAY(pBitmap) ((pBitmap)->Order == ORDER_GRAY)

/*
   memory allocation flags
*/
#define TYPE_CONV               0x0001 /* Use conventional memory first */
#define TYPE_DISK               0x0080 /* Use Disk (if possible) */
#define TYPE_NODISK             0x0100 /* Do not use disk */
#define TYPE_COMPRESSED         0x0200 /* keep 1 bit images compressed in memory */

/*
   playback handle
*/
typedef HANDLE HPLAYBACK;
typedef HPLAYBACK L_FAR *pHPLAYBACK;

/* 
   flags for L_SizeBitmap
*/

#define SIZE_NORMAL              0x0000
#define SIZE_FAVORBLACK          0x0001
#define SIZE_RESAMPLE            0x0002

/* 
   flags for L_ConvertBufferExt
*/

#define CVT_SRCGRAY              0x0001
#define CVT_DSTGRAY              0x0002
#define CVT_SRCUSEBITS           0x0004
#define CVT_DSTUSEBITS           0x0008

/*
   flag that you can use to detect when a pixel color is 16 bit grayscale
*/

#define COLORREF_GRAY16          0x04000000L

/*
   BITMAPHANDLE structure
*/

typedef struct struct_LEAD_Bitmap
{
   union
   {
      struct struct_compressed_memory
      {
         HGLOBAL hData;         /* internal use */
         L_VOID L_HUGE*pData;  /* internal use */
      } Compressed;

      struct struct_window_memory
      {                         
         HGLOBAL hData;         /* Internal use */
         L_UCHAR L_FAR *pData;  /* Internal use */
      } Windows;

      struct struct_file_memory 
      {                         
         L_INT fd;              /* Internal use */
         L_CHAR L_FAR *Filename;/* Internal use */
      } File;
   } Addr;
   L_INT Width;                 /* Image width */
   L_INT Height;                /* Image height */
   L_INT BitsPerPixel;          /* Number of bits per pixel */
   L_UINT BytesPerLine;         /* Bytes per line, rounded by four */
   L_UINT32 CurrentPos;         /* Internal use */
   L_INT CurrentRow;            /* Internal use */
   struct struct_bitmap_flags
   {
      L_BITFIELD Allocated:1;          /* Is the bitmap allocated? */
      L_BITFIELD ConventionalMemory:1; /* allocated in conventional memory */
      L_BITFIELD DiskMemory:1;         /* allocated on disk */
      L_BITFIELD Progressive:1;        /* progressive format */
      L_BITFIELD LockedMemory:1;       /* Is memory locked in windows */
      L_BITFIELD Interlaced:1;         /* Interlaced format */
      L_BITFIELD WaitUserInput:1;      /* Playback wait for user input */
      L_BITFIELD Transparency:1;       /* Playback uses transparency */
      L_BITFIELD Compressed:1;         /* 1 bit RLE compressed data */
      L_BITFIELD Signed:1;             /* the pixel values are signed */
      L_BITFIELD Mirror:1;             /* this is a mirror of another image */
      L_BITFIELD UseLUT:1;             /* use pLUT for image processing */
      L_BITFIELD Global:1;             /* hData is HGLOBAL */
      L_BITFIELD Reserved7:1;          /* Internal use */
      L_BITFIELD Reserved8:1;          /* Internal use */
      L_BITFIELD Reserved9:1;          /* Internal use */
#ifdef FOR_WIN32
      L_BITFIELD Dummy:16;
#endif
   } Flags;
   L_INT nColors;                /* No. of possible colors in the bitmap */

   HPALETTE hPalette;            /* Handle to a palette */

   L_INT ViewPerspective;        /* Is TOP_LEFT, BOTTOM_RIGHT, ... */
   L_INT Order;                  /* Is it ORDER_RGB, ORDER_BGR */
   L_UINT32 Size;                /* Size of the bitmap */
   L_VOID L_FAR *pDitherData;    /* Internal use */
   L_UINT DitheringMethod;       /* Which dithering method used */
   L_VOID L_FAR *pRgnInfo;       /* Internal use */
   L_INT XResolution;            /* Bitmaps X resolution (DPI) */
   L_INT YResolution;            /* Bitmaps Y resolution (DPI) */
   L_INT Left;                   /* Left playback offset */
   L_INT Top;                    /* Top playback offset */
   L_UINT32 Delay;               /* Playback delay (ms) */
   COLORREF Background;          /* Playback background color */
   COLORREF Transparency;        /* Playback transparent color */
   L_UINT DisposalMethod;        /* Playback disposal method */
   L_INT   LowBit;               /* low bit set by L_WindowLevelBitmap */
   L_INT   HighBit;              /* high bit set by L_WindowLevelBitmap */
   RGBQUAD L_HUGE*pLUT;          /* LUT set by L_WindowLevel or L_WindowLevelBitmap */
   L_UINT32 LUTLength;           /* no of entries pointed by LUT */
   L_UINT32 DataOffset;          /* offset into hData */
   L_INT32  MinVal;              /* min val for a grayscale bitmap */
   L_INT32  MaxVal;              /* max val for a grayscale bitmap */
   L_INT    PaintLowBit;         /* low bit set by L_WindowLevelBitmap */
   L_INT    PaintHighBit;        /* high bit set by L_WindowLevelBitmap */
} BITMAPHANDLE, L_FAR * pBITMAPHANDLE;

/*
   version structure
*/
typedef struct struct_version_information
{
   L_UCHAR Product[60];         /* Product Name */
   L_INT Level;                 /* Toolkit Level (EXP, PRO, etc.) */
   L_INT MajorNumber;           /* Major Version Number */
   L_INT MinorNumber;           /* Minor Version Number */
   L_UCHAR Date[16];            /* Date of the Build */
   L_UCHAR Time[16];            /* Time of the Build */
} VERSIONINFO, L_FAR * pVERSIONINFO;

/*
   bitmap list handle
*/
typedef HANDLE HBITMAPLIST;
typedef HBITMAPLIST L_FAR *pHBITMAPLIST;

/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK COLORRESCALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_INT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK STATUSCALLBACK) (L_INT);
typedef L_INT (pEXT_CALLBACK HOTKEYCALLBACK) (L_INT, L_UINT, L_VOID L_FAR*);

typedef L_INT (pEXT_CALLBACK REDIRECTOPEN) (L_CHAR L_FAR *, L_INT, L_INT);
typedef L_UINT (pEXT_CALLBACK REDIRECTREAD) (L_INT, L_CHAR L_FAR *, L_INT);
typedef L_UINT (pEXT_CALLBACK REDIRECTWRITE) (L_INT, L_CHAR L_FAR *, L_INT);
typedef L_INT32 (pEXT_CALLBACK REDIRECTSEEK) (L_INT, L_INT32, L_INT);
typedef L_INT (pEXT_CALLBACK REDIRECTCLOSE) (L_INT);

/*
   function prototypes
*/
L_VOID EXT_FUNCTION L_AccessBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_AllocateBitmap (pBITMAPHANDLE pBitmap,
                                      L_INT nMemoryType);

L_INT EXT_FUNCTION L_ChangeBitmapHeight (pBITMAPHANDLE pBitmap,
                                          L_INT nHeight);

L_INT EXT_FUNCTION L_ChangeBitmapViewPerspective(pBITMAPHANDLE pDstBitmap,
                                          pBITMAPHANDLE pSrcBitmap,
                                          L_INT   ViewPerspective);

L_INT EXT_FUNCTION L_ChangeFromDIB (pBITMAPHANDLE pBitmap,
                                     HGLOBAL hDIB);

HGLOBAL EXT_FUNCTION L_ChangeToDIB (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ClearBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ClearNegativePixels( pBITMAPHANDLE pBitmap );

L_INT EXT_FUNCTION L_ColorResBitmap (pBITMAPHANDLE pBitmapSrc,
                                      pBITMAPHANDLE pBitmapDst,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      L_UINT uColors,
                                      COLORRESCALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_ColorResBitmapList (HBITMAPLIST hList,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      L_UINT uColors);

L_INT EXT_FUNCTION L_CombineBitmap (pBITMAPHANDLE pBitmapDst,
                                     L_INT nXDst,
                                     L_INT nYDst,
                                     L_INT nWidth,
                                     L_INT nHeight,
                                     pBITMAPHANDLE pBitmapSrc,
                                     L_INT nXSrc,
                                     L_INT nYSrc,
                                     L_UINT32 uFlags);

L_INT EXT_FUNCTION L_CompressRow( L_UINT16 L_HUGE * pRunBuffer,
                                  L_UCHAR L_HUGE * pBuffer,
                                  L_INT nCol,
                                  L_INT nWidth);

L_INT EXT_FUNCTION L_CompressRows(  L_UINT16 L_HUGE*pRunBuffer,
                                    L_UCHAR L_HUGE*pBuffer,
                                    L_UINT nWidth,
                                    L_UINT nRows);

L_INT EXT_FUNCTION L_ConvertBuffer (L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst);

L_INT EXT_FUNCTION L_ConvertBufferExt (L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst,
                                     L_UINT  uFlags,
                                     L_INT   uLowBit,
                                     L_INT   uHighBit);

L_INT EXT_FUNCTION L_ConvertFromDIB (pBITMAPHANDLE pBitmap,
                                      BITMAPINFO L_FAR * pInfo,
                                      L_UCHAR L_FAR * pBits);

HGLOBAL EXT_FUNCTION L_ConvertToDIB (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_CopyBitmap (pBITMAPHANDLE pBitmapDst,
                                  pBITMAPHANDLE pBitmapSrc);

L_INT EXT_FUNCTION L_CopyBitmapData (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc);

L_VOID EXT_FUNCTION L_CopyBitmapHandle (pBITMAPHANDLE pBitmapDst,
                                         pBITMAPHANDLE pBitmapSrc);

L_INT EXT_FUNCTION L_CopyBitmapListItems(pHBITMAPLIST phList,
                                        HBITMAPLIST hList,
                                        L_UINT uIndex,
                                        L_UINT uCount);

L_INT EXT_FUNCTION L_CopyBitmapRect (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

L_INT EXT_FUNCTION L_CreateBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uMemory,
                                    L_UINT uWidth,
                                    L_UINT uHeight,
                                    L_UINT uBitsPerPixel,
                                    L_UINT uOrder,
                                    LPRGBQUAD pPalette,
                                    L_UINT uViewPerspective);

L_INT EXT_FUNCTION L_CreateBitmapList(pHBITMAPLIST phList);

HDC EXT_FUNCTION L_CreateLeadDC (pBITMAPHANDLE pBitmap);

L_UINT L_FAR *EXT_FUNCTION L_CreateUserMatchTable (LPRGBQUAD pPalette,
                                                    L_UINT uColors);

L_INT EXT_FUNCTION L_DefaultDithering (L_UINT uMethod);

L_INT EXT_FUNCTION L_DeleteBitmapListItems(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           L_UINT uCount);

L_INT EXT_FUNCTION L_DestroyBitmapList(HBITMAPLIST hList);

L_BOOL EXT_FUNCTION L_DeleteLeadDC (HDC hDC);

L_INT EXT_FUNCTION L_DitherLine (pBITMAPHANDLE pBitmap,
                                  L_UCHAR L_FAR * pBufferSrc,
                                  L_UCHAR L_FAR * pBufferDst);

HPALETTE EXT_FUNCTION L_DupPalette (HPALETTE hPalette);

L_INT EXT_FUNCTION L_ExpandRow(L_UINT16 L_HUGE * pRunBuffer, 
                               L_UCHAR L_HUGE * pBuffer, 
                               L_UINT nCol, 
                               L_INT nWidth);

L_INT EXT_FUNCTION L_ExpandRows( L_UINT16 L_HUGE *pRun, 
                                 L_UCHAR L_HUGE*pBuffer, 
                                 L_UINT nWidth, 
                                 L_UINT nRows);

L_INT EXT_FUNCTION L_FillBitmap (pBITMAPHANDLE pBitmap,
                                  COLORREF crFill);

L_INT EXT_FUNCTION L_FlipBitmap (pBITMAPHANDLE pBitmap);

L_VOID EXT_FUNCTION L_FreeBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_FreeUserMatchTable (L_UINT L_FAR * pTable);

L_INT EXT_FUNCTION L_GetBitmapAlpha (pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);

L_INT EXT_FUNCTION L_GetBitmapColors (pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

L_INT EXT_FUNCTION L_GetBitmapListCount(HBITMAPLIST hList,
                                           L_UINT L_FAR *puCount);

L_INT EXT_FUNCTION L_GetBitmapListItem(HBITMAPLIST hList,
                                       L_UINT uIndex,
                                       pBITMAPHANDLE pBitmap);

L_INT32 EXT_FUNCTION L_GetBitmapRow (pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_GetBitmapRowCol (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_GetBitmapRowColCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

L_INT EXT_FUNCTION L_GetBitmapRowCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

L_INT EXT_FUNCTION L_GetFixedPalette (LPRGBQUAD pPalette,
                                       L_INT nBitsPerPixel);

COLORREF EXT_FUNCTION L_GetPixelColor (pBITMAPHANDLE pBitmap,
                                        L_INT nRow,
                                        L_INT nCol);

L_INT EXT_FUNCTION L_GrayScaleBitmap (pBITMAPHANDLE pBitmap,
                                      L_INT nBitsPerPixel);

L_INT EXT_FUNCTION L_InitBitmap (pBITMAPHANDLE pBitmap,
                                  L_INT nWidth,
                                  L_INT nHeight,
                                  L_INT nBitsPerPixel);

L_INT EXT_FUNCTION L_InsertBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_IsGrayScaleBitmap (pBITMAPHANDLE pBitmap);

L_BOOL EXT_FUNCTION L_IsSupportLocked (L_UINT uType);

L_INT EXT_FUNCTION L_PointFromBitmap(pBITMAPHANDLE pBitmap, 
                                     L_INT ViewPerspective, 
                                     L_INT L_FAR*px, 
                                     L_INT L_FAR*py);

L_INT EXT_FUNCTION L_PointToBitmap(pBITMAPHANDLE pBitmap,
                                   L_INT ViewPerspective,
                                   L_INT L_FAR*px,
                                   L_INT L_FAR*py);

L_INT EXT_FUNCTION L_PutBitmapColors (pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

L_INT32 EXT_FUNCTION L_PutBitmapRow (pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_PutBitmapRowCol (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_PutBitmapRowColCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

L_INT EXT_FUNCTION L_PutBitmapRowCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

L_INT EXT_FUNCTION L_PutPixelColor (pBITMAPHANDLE pBitmap,
                                     L_INT nRow,
                                     L_INT nCol,
                                     COLORREF crColor);

L_INT EXT_FUNCTION L_RectFromBitmap(pBITMAPHANDLE pBitmap, 
                                    L_INT ViewPerspective,
                                    LPRECT lprc);

L_INT EXT_FUNCTION L_RectToBitmap(  pBITMAPHANDLE pBitmap, 
                                    L_INT nViewPerspective,
                                    LPRECT lprc);

L_VOID EXT_FUNCTION L_RedirectIO (REDIRECTOPEN pfnOpen,
                                   REDIRECTREAD pfnRead,
                                   REDIRECTWRITE pfnWrite,
                                   REDIRECTSEEK pfnSeek,
                                   REDIRECTCLOSE pfnClose);

L_VOID EXT_FUNCTION L_ReleaseBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_RemoveBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ResampleBitmap (pBITMAPHANDLE pBitmap,
                                      L_INT nWidth,
                                      L_INT nHeight);

L_INT EXT_FUNCTION L_Resize (L_UCHAR L_FAR * pBuffer,
                              L_INT nRow,
                              L_INT nBitsPerPixel,
                              L_INT L_FAR * pXSize,
                              L_INT L_FAR * pYSize,
                              L_VOID L_FAR * pResizeData);

L_INT EXT_FUNCTION L_ResizeBitmap (pBITMAPHANDLE pBitmapSrc,
                                    pBITMAPHANDLE pBitmapDst);

L_INT EXT_FUNCTION L_ReverseBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_RotateBitmap (pBITMAPHANDLE pBitmap,
                                    L_INT nAngle,
                                    L_BOOL fResize);

L_INT EXT_FUNCTION L_RotateBitmapFine (pBITMAPHANDLE pBitmap,
                                        L_INT32 nAngle,
                                        L_BOOL fResize,
                                        COLORREF crFill);

L_INT EXT_FUNCTION L_RotateBitmapViewPerspective (pBITMAPHANDLE pBitmap,
                                   L_INT nAngle);

L_INT EXT_FUNCTION L_SetBitmapAlpha (pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);

L_INT EXT_FUNCTION L_SetBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_SetHotKeyCallback(L_INT nHotKey, 
                                       L_UINT uHotKeyModifiers, 
                                       HOTKEYCALLBACK pfnHotKeyCallback, 
                                       L_VOID L_FAR* pUserData);

STATUSCALLBACK EXT_FUNCTION L_SetStatusCallBack (STATUSCALLBACK pfnCallback);

L_UINT L_FAR *EXT_FUNCTION L_SetUserMatchTable (L_UINT L_FAR * pTable);

L_INT EXT_FUNCTION L_ShearBitmap (pBITMAPHANDLE pBitmap,
                                   L_INT nAngle,
                                   L_BOOL fHorizontal,
                                   COLORREF crFill);

L_INT EXT_FUNCTION L_SizeBitmap(pBITMAPHANDLE pBitmap,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_UINT32 uFlags);

L_INT EXT_FUNCTION L_StartDithering (pBITMAPHANDLE pBitmap,
                                      LPRGBQUAD pPalette,
                                      L_UINT uColors);

L_INT EXT_FUNCTION L_StartResize (L_INT nOldWidth,
                                   L_INT nOldHeight,
                                   L_INT nNewWidth,
                                   L_INT nNewHeight,
                                   L_VOID L_FAR * L_FAR * ppResizeData);

L_INT EXT_FUNCTION L_StopDithering (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_StopResize (L_VOID L_FAR * pResizeData);

COLORREF EXT_FUNCTION L_TranslateBitmapColor(pBITMAPHANDLE pBitmapDst,
                                             pBITMAPHANDLE pBitmapSrc,
                                             COLORREF crColor);

L_INT EXT_FUNCTION L_TrimBitmap ( pBITMAPHANDLE pBitmap,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

L_VOID EXT_FUNCTION L_UnlockSupport (L_UINT uType, L_CHAR L_FAR * pKey);

L_INT EXT_FUNCTION L_VersionInfo (pVERSIONINFO pVersionInfo);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTKRN_H_ */
