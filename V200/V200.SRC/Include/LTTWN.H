/*
   LTTWN.H - twain module header file
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTTWN_H_
#define _LTTWN_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   Flags for L_TwainAcquireExt
*/
#define TWAIN_SHOWUI               0x0001 /* Show the User Interface */
#define TWAIN_SHOWSTATUS           0x0002 /* Show the Status Indicator, if it
                                             is selectable */
#define TWAIN_NATIVEXFER           0x0004 /* Use native transfer */
#define TWAIN_KEEPOPEN             0x0008 /* Keep the data source open */

#define TWAIN_UPDATE_DEFAULTS_ONLY 0x0010 /* Update only properties with the default values */
#define TWAIN_UPDATE_NON_DEFAULTS  0x0020 /* Update only properties with non-default values */
#define TWAIN_UPDATE_ALL (TWAIN_UPDATE_DEFAULTS_ONLY | TWAIN_UPDATE_NON_DEFAULTS)

#define TWAIN_QUICK_UPDATE         0x0040 /* Just update the settings to be used the next time you do TwainAcquire */
#define TWAIN_CACHE_SOURCE         0x0080 /* Scan once and keep the data source open after each scan - faster scanning */

/*
   Flags for TWAINPROPERTIES
*/
#define TWAIN_PIX_DEFAULT         -1   /* Use default type, bits per pixel. */
#define TWAIN_PIX_HALF             0   /* Halftone, 1 bit per pixel. */
#define TWAIN_PIX_GRAY             1   /* GrayScale, 4 or 8 bits per pixel,
                                          the largest supported value. */
#define TWAIN_PIX_RGB              2   /* Color, 24 bits per pixel. */
#define TWAIN_PIX_PALETTE          3   /* Color, 4 or 8 bits per pixel, the
                                          largest supported value. */
#define TWAIN_PIX_LAST             3

#define TWAIN_DEFAULT_BRIGHTNESS    2000
#define TWAIN_DEFAULT_CONTRAST      2000
#define TWAIN_DEFAULT_ORIENTATION   -1

#define TWAIN_FEEDER_DONTCARE       2

enum
{
   TWAIN_ROT0,
   TWAIN_ROT90,
   TWAIN_ROT180,
   TWAIN_ROT270,
   TWAIN_PORTRAIT = TWAIN_ROT0,
   TWAIN_LANDSCAPE = TWAIN_ROT270
};

/*
   TWAIN Properties structure
*/
typedef struct struct_twain_properties
{
   L_CHAR AppManufacturer[36];
   L_CHAR AppProdFamily[36];
   L_CHAR AppProdName[36];
   L_CHAR SourceName[36];
   L_INT nMaxPages;
   L_INT nPixelType;
   L_INT nBits;
   L_INT nRes;
   L_INT32 nXPos;
   L_INT32 nYPos;
   L_INT32 nWidth;
   L_INT32 nHeight;
   L_INT    nBrightness;
   L_INT    nContrast;
   L_INT    nOrientation;
   L_INT    nFeederEnabled;   /* enable the auto feeder */
   L_INT    nEnableAutoFeed;  /* enable the automatic feeding */
} TWAINPROPERTIES, L_FAR * pTWAINPROPERTIES;

/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK ENUMSOURCECALLBACK) (L_UCHAR L_FAR *, L_INT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK TWAINCALLBACK) (pBITMAPHANDLE, L_VOID L_FAR *);

/*
   function prototypes
*/
L_INT EXT_FUNCTION L_TwainAcquire (HWND hWnd, pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_TwainAcquireExt (HWND hWnd,
                                       pBITMAPHANDLE pBitmap,
                                       L_UINT uFlags,
                                       TWAINCALLBACK pfnCallback,
                                       L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_TwainCloseSession(HWND hWnd);

L_INT EXT_FUNCTION L_TwainEnumSources (HWND hWnd,
                                        ENUMSOURCECALLBACK pfnCallback,
                                        L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_TwainSelect (HWND hWnd);

L_INT EXT_FUNCTION L_TwainSetProps (HWND hWnd, pTWAINPROPERTIES pTwain, L_UINT32 uFlags);
L_INT EXT_FUNCTION L_TwainGetProps (pTWAINPROPERTIES pTwain);

L_BOOL EXT_FUNCTION L_IsTwainAvailable(HWND hWnd);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTTWN_H_ */
