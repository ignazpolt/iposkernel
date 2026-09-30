/*
   LTIMG.H - image module header file
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTIMG_H_
#define _LTIMG_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_EmbossBitmap
*/
#define EMBOSS_N    0
#define EMBOSS_NE   1
#define EMBOSS_E    2
#define EMBOSS_SE   3
#define EMBOSS_S    4
#define EMBOSS_SW   5
#define EMBOSS_W    6
#define EMBOSS_NW   7

/*
   flags for L_GetHistogram, L_RemapBitmapIntensity, and L_AddNoiseBitmap
*/
#define CHANNEL_MASTER 0        /* All channels */
#define CHANNEL_RED    1        /* Red channel only */
#define CHANNEL_GREEN  2        /* Green channel only */
#define CHANNEL_BLUE   3        /* Blue channel only */

/*
   flags for L_ColorSeparateBitmap/L_ColorMergeBitmap
*/
#define COLORSEP_RGB                 0x00 /* Use 3 RGB color planes. */
#define COLORSEP_CMYK                0x01 /* Use 4 CMYK color planes. */
#define COLORSEP_HSV                 0x02 /* Use 3 HSV color planes. */
#define COLORSEP_HLS                 0x03 /* Use 3 HLS color planes. */
#define COLORSEP_CMY                 0x04 /* Use 3 CMY color planes. */

/*
   Binary filter constants
*/
#define BFLT_DONTCARE   256

typedef struct tagBINARYFLT
{
   L_BOOL bfltMax;              /* select maximimum value */
   L_UINT bfltDim;              /* filter dimensions */
   L_INT bfltMatrix[1];         /* array of filter coefficients */
} BINARYFLT, L_FAR * LPBINARYFLT;

#define BINARYFLTSIZE(dim) (sizeof(BINARYFLT) + (sizeof(L_INT) * (((L_INT) (dim) * (L_INT) (dim)) - 1)))
#define MAKEINTBFLT(i) ((LPBINARYFLT)((L_UINT32)((L_UINT16) (i))))

#define BFLT_EROSION_OMNI    MAKEINTBFLT(0)
#define BFLT_EROSION_HORZ    MAKEINTBFLT(1)
#define BFLT_EROSION_VERT    MAKEINTBFLT(2)
#define BFLT_EROSION_DIAG    MAKEINTBFLT(3)
#define BFLT_DILATION_OMNI    MAKEINTBFLT(4)
#define BFLT_DILATION_HORZ    MAKEINTBFLT(5)
#define BFLT_DILATION_VERT    MAKEINTBFLT(6)
#define BFLT_DILATION_DIAG    MAKEINTBFLT(7)

/*
   spatial filter constants
*/
typedef struct tagSPATIALFLT
{
   L_INT fltDivisor;            /* sum divisor */
   L_INT fltBias;               /* sum bias */
   L_UINT fltDim;               /* filter dimensions */
   L_INT fltMatrix[1];          /* array of filter coefficients */
} SPATIALFLT, L_FAR * LPSPATIALFLT;

#define SPATIALFLTSIZE(dim) (sizeof(SPATIALFLT) + (sizeof(L_INT) * (((L_INT) (dim) * (L_INT) (dim)) - 1)))
#define MAKEINTFLT(i) ((LPSPATIALFLT)((L_UINT32)((L_UINT16) (i))))

#define FLT_EMBOSS_N    MAKEINTFLT(0)
#define FLT_EMBOSS_NE   MAKEINTFLT(1)
#define FLT_EMBOSS_E    MAKEINTFLT(2)
#define FLT_EMBOSS_SE   MAKEINTFLT(3)
#define FLT_EMBOSS_S    MAKEINTFLT(4)
#define FLT_EMBOSS_SW   MAKEINTFLT(5)
#define FLT_EMBOSS_W    MAKEINTFLT(6)
#define FLT_EMBOSS_NW   MAKEINTFLT(7)

#define FLT_GRADIENT_N    MAKEINTFLT(8)
#define FLT_GRADIENT_NE   MAKEINTFLT(9)
#define FLT_GRADIENT_E    MAKEINTFLT(10)
#define FLT_GRADIENT_SE   MAKEINTFLT(11)
#define FLT_GRADIENT_S    MAKEINTFLT(12)
#define FLT_GRADIENT_SW   MAKEINTFLT(13)
#define FLT_GRADIENT_W    MAKEINTFLT(14)
#define FLT_GRADIENT_NW   MAKEINTFLT(15)

#define FLT_LAPLACE_1     MAKEINTFLT(16)
#define FLT_LAPLACE_2     MAKEINTFLT(17)
#define FLT_LAPLACE_3     MAKEINTFLT(18)
#define FLT_LAPLACE_DIAG  MAKEINTFLT(19)
#define FLT_LAPLACE_HORZ  MAKEINTFLT(20)
#define FLT_LAPLACE_VERT  MAKEINTFLT(21)

#define FLT_SOBEL_HORZ    MAKEINTFLT(22)
#define FLT_SOBEL_VERT    MAKEINTFLT(23)

#define FLT_PREWITT_HORZ  MAKEINTFLT(24)
#define FLT_PREWITT_VERT  MAKEINTFLT(25)

#define FLT_SHIFTDIFF_DIAG  MAKEINTFLT(26)
#define FLT_SHIFTDIFF_HORZ  MAKEINTFLT(27)
#define FLT_SHIFTDIFF_VERT  MAKEINTFLT(28)

#define FLT_LINESEG_HORZ  MAKEINTFLT(29)
#define FLT_LINESEG_VERT  MAKEINTFLT(30)
#define FLT_LINESEG_LTOR  MAKEINTFLT(31)
#define FLT_LINESEG_RTOL  MAKEINTFLT(32)

/*
   Flags for L_PicturizeBitmap
*/
#define PICTURIZE_LOADALL     0x0001   /* Load all files in memory */
#define PICTURIZE_RESIZE      0x0002   /* Resize all images that are not the required size */
#define PICTURIZE_RESAMPLE    0x0004   /* Resample all images that are not the required size */

/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK PICTURIZECALLBACK) (pBITMAPHANDLE, L_INT, L_INT, L_VOID L_FAR *);

/*
   function prototypes
*/
L_INT EXT_FUNCTION L_AddBitmapNoise (pBITMAPHANDLE pBitmap,
                                      L_UINT uRange,
                                      L_UINT uChannel);

L_INT EXT_FUNCTION L_AutoTrimBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

L_INT EXT_FUNCTION L_AverageFilterBitmap (pBITMAPHANDLE pBitmap,
                                           L_UINT uDim);

L_INT EXT_FUNCTION L_BinaryFilterBitmap (pBITMAPHANDLE pBitmap,
                                          LPBINARYFLT pFilter);

L_INT EXT_FUNCTION L_ChangeBitmapContrast (pBITMAPHANDLE pBitmap,
                                            L_INT nChange);

L_INT EXT_FUNCTION L_ChangeBitmapHue (pBITMAPHANDLE pBitmap,
                                       L_INT nAngle);

L_INT EXT_FUNCTION L_ChangeBitmapIntensity (pBITMAPHANDLE pBitmap,
                                             L_INT nChange);

L_INT EXT_FUNCTION L_ChangeBitmapSaturation (pBITMAPHANDLE pBitmap,
                                              L_INT nChange);

L_INT EXT_FUNCTION L_ColorMergeBitmap (pBITMAPHANDLE pBitmap,
                                        pBITMAPHANDLE L_FAR * ppBitmap,
                                        L_UINT32 uFlags);

L_INT EXT_FUNCTION L_ColorSeparateBitmap (pBITMAPHANDLE pBitmap,
                                           pBITMAPHANDLE L_FAR * ppBitmap,
                                           L_UINT32 uFlags);

L_INT EXT_FUNCTION L_DeskewBitmap (pBITMAPHANDLE pBitmap,
                                   L_INT32 L_FAR *pnAngle);

L_INT EXT_FUNCTION L_DespeckleBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_EmbossBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uDirection,
                                    L_UINT uDepth);

L_INT EXT_FUNCTION L_GammaCorrectBitmap (pBITMAPHANDLE pBitmap,
                                          L_UINT uGamma);

L_INT EXT_FUNCTION L_GetAutoTrimRect(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold,
                                     RECT L_FAR *pRect);

L_INT EXT_FUNCTION L_GetBitmapColorCount(pBITMAPHANDLE pBitmap,
                                         L_UINT32 L_FAR *puCount);

L_INT EXT_FUNCTION L_GetBitmapHistogram (pBITMAPHANDLE pBitmap,
                                          L_UINT32 L_FAR * pHistogram,
                                          L_UINT uChannel);

L_INT EXT_FUNCTION L_GetMinMaxBits(pBITMAPHANDLE pBitmap,
                                  L_INT L_FAR*pLowBit,
                                  L_INT L_FAR*pHighBit);

L_INT EXT_FUNCTION L_GetMinMaxVal(pBITMAPHANDLE pBitmap,
                                  L_UINT L_FAR*pMinVal,
                                  L_UINT L_FAR*pMaxVal);

L_INT EXT_FUNCTION L_HistoContrastBitmap (pBITMAPHANDLE pBitmap,
                                           L_INT nChange);

L_INT EXT_FUNCTION L_HistoEqualizeBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_IntensityDetectBitmap (pBITMAPHANDLE pBitmap,
                                             L_UINT uLow,
                                             L_UINT uHigh);

L_INT EXT_FUNCTION L_InvertBitmap (pBITMAPHANDLE pBitmap);


L_INT EXT_FUNCTION L_MaxFilterBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_MedianFilterBitmap (pBITMAPHANDLE pBitmap,
                                          L_UINT uDim);

L_INT EXT_FUNCTION L_MinFilterBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_MosaicBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uDim);

L_INT EXT_FUNCTION L_OilifyBitmap (pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_PosterizeBitmap (pBITMAPHANDLE pBitmap,
                                       L_UINT uLevels);

L_INT EXT_FUNCTION L_PicturizeBitmap(pBITMAPHANDLE pBitmap, 
                                    L_CHAR L_FAR*pszDirName, 
                                    L_UINT uFlags,
                                    L_INT nCellWidth,
                                    L_INT nCellHeight,
                                    PICTURIZECALLBACK pfnCallback,
                                    L_VOID L_FAR*pUserData);

L_INT EXT_FUNCTION L_RemapBitmapIntensity (pBITMAPHANDLE pBitmap,
                                            L_UCHAR L_FAR * pLUT,
                                            L_UINT uChannel);

L_INT EXT_FUNCTION L_SharpenBitmap (pBITMAPHANDLE pBitmap,
                                     L_INT nSharpness);

L_INT EXT_FUNCTION L_SolarizeBitmap (pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

L_INT EXT_FUNCTION L_SpatialFilterBitmap (pBITMAPHANDLE pBitmap,
                                           LPSPATIALFLT pFilter);

L_INT EXT_FUNCTION L_StretchBitmapIntensity (pBITMAPHANDLE pBitmap);


L_INT EXT_FUNCTION L_WindowLevelBitmap( pBITMAPHANDLE pBitmap,
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 RGBQUAD L_HUGE*pLUT,
                                 L_UINT32 uLUTLength,
                                 L_INT nOrderDst);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTIMG_H_ */
