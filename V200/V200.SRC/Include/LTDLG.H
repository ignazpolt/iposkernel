/*
   LTDLG.H - LEAD Common Dialog module header file
   Copyright (c) 1991-1998 by LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTDLG_H_
#define _LTDLG_H_

#include "ltkrn.h"
#include "ltimg.h"
#include "ltfil.h"
#include <stdlib.h>
#include <commdlg.h>

#define _HEADER_ENTRY_
#include "ltpck.h"

/* callback typedefs */
typedef L_VOID (pEXT_CALLBACK LTCOMMDLGHELPCB) (L_UINT32);

/* structure typedefs */
typedef struct _FILEOPENPARM
{
   L_CHAR        szFileName[L_MAXPATH];/* filename                                   */
   pBITMAPHANDLE pBitmap;              /* Bitmap to fill in if AutoProcess           */
   pBITMAPHANDLE pThumbnail;           /* Bitmap to fill in with Thumbnail           */
   pFILEINFO     pFileInfo;            /* FILEINFO structure to fill                 */
   L_INT         nPageNumber;          /* Page Number to load                        */
   L_INT         nPasses;              /* Passes to load from Progressive image file */
   L_BOOL        bLoadCompressed;      /* Load 1-bit image as compressed data?       */
   L_BOOL        bLoadRotated;         /* Load image without rotating data?          */
   L_BOOL        bPreviewEnabled;      /* TRUE to have Preview enabled               */
} FILEOPENPARM, L_FAR* LPFILEOPENPARM;

/* possible values for uSaveMulti */
#define SAVE_OVERWRITE 0
#define SAVE_APPEND    1
#define SAVE_REPLACE   2
#define SAVE_INSERT    3

typedef struct _FILESAVEPARM
{
   L_CHAR        szFileName[L_MAXPATH];/* filename */
   pBITMAPHANDLE pBitmap;              /* Bitmap to save */
   L_INT         nBitsPerPixel;        /* bits per pixel to save */
   L_INT         nFormat;              /* file format to save */
   L_INT         nQFactor;             /* QFactor value for save */
   L_UINT        uSaveMulti;           /* save as multi-page file? */
   L_BOOL        bSaveInterlaced;      /* save as interlaced GIF? */
   L_BOOL        bSaveProgressive;     /* save as progressive image? */
   L_INT         nPasses;              /* # of progressive passes */
   L_BOOL        bSaveWithStamp;       /* save with stamp preview? */
   L_INT         nStampBits;           /* stamp bits per pixel */
   L_INT         nStampWidth;          /* stamp width */
   L_INT         nStampHeight;         /* stamp height */
   L_INT         nPageNumber;          /* Page Number to replace/insert */
} FILESAVEPARM, L_FAR* LPFILESAVEPARM;

typedef struct _EFXDLGPARM
{
   L_UINT uStructSize;                 /* size of this structure */
   L_UINT uEffect;                     /* effect to use */
   L_UINT uGrain;                      /* grain size */
   L_UINT uDelay;                      /* delay */
   L_UINT uMaxPass;                    /* maximum passes */
   L_BOOL bTransparent;                /* use transparent color? */
   COLORREF crTransparent;             /* transparent color */
   L_UINT uWandWidth;                  /* wand width */
   COLORREF crWand;                    /* wand color */
} EFXDLGPARM, L_FAR * LPEFXDLGPARM;

typedef struct _SHAPEDLGPARM
{
   L_UINT uStructSize;                 /* size of this structure */
   L_UINT uShape;                      /* type of shape	*/
   COLORREF crBack;	                  /* background color	*/
   L_UINT uBackStyle;                  /* background style	*/
   COLORREF crFill;                    /* foreground color	*/
   L_UINT uFillStyle;                  /* foreground style	*/
   COLORREF crBorder;                  /* border color	*/
   L_UINT uBorderStyle;                /* border style	*/
   L_UINT uBorderWidth;                /* border width	*/
   COLORREF crInnerHilite;             /* inner band highlight color	*/
   COLORREF crInnerShadow;             /* inner band shadow color	*/
   L_UINT uInnerStyle;                 /* inner band style	*/
   L_UINT uInnerWidth;                 /* inner band width	*/
   COLORREF crOuterHilite;             /* outer band highlight color	*/
   COLORREF crOuterShadow;             /* outer band shadow color	*/
   L_UINT uOuterStyle;                 /* outer band style	*/
   L_UINT uOuterWidth;                 /* outer band width	*/
   L_INT nShadowX;                     /* horizontal position of the shadow	*/
   L_INT nShadowY;                     /* vertical position of the shadow	*/
   COLORREF crShadow;                  /* shadow color	*/
} SHAPEDLGPARM, L_FAR * LPSHAPEDLGPARM;

typedef struct _TEXTDLGPARM
{
   L_UINT    uStructSize;                 /* size of this structure */
   LPSTR     pszSampleText;               /* pointer to sample text */
   L_INT     nMaxCount;                   /* maximum size of sample text */
   L_INT     nAngle;                      /* rotation angle for text */
   L_UINT    uStyle;                      /* text style flag */
   L_UINT    uAlign;                      /* text align flag */
   L_BOOL    bWordWrap;                   /* word wrap */
   HFONT     hFont;                       /* handle to font to use */
   COLORREF  crText;                      /* text color */
   COLORREF  crHilite;                    /* border color */
   COLORREF  crShadow;                    /* shadow color */
   L_INT     nXDepth;                     /* horz. shadow position */
   L_INT     nYDepth;                     /* vert. shadow position */
   L_BOOL    bUseForeImage;               /* use foreground image */
} TEXTDLGPARM, L_FAR * LPTEXTDLGPARM;

typedef struct _GRADDLGPARM
{
   L_UINT    uStructSize;                 /* size of this structure */
   L_UINT    uStyle;                      /* gradient style */
   COLORREF  crStart;                     /* start color */
   COLORREF  crEnd;                       /* end color */
   L_UINT    uSteps;                      /* gradient steps */
} GRADDLGPARM, L_FAR * LPGRADDLGPARM;

typedef struct _TRANSDLGPARM
{
   L_UINT uStructSize;                 /* size of this structure */
   L_UINT uTransition;                 /* transition */
   COLORREF crBack;                    /* back/start color */
   COLORREF crFore;                    /* fore/end color */
   L_UINT uSteps;                      /* gradient steps */
   L_UINT uEffect;                     /* effect to use */
   L_UINT uGrain;                      /* grain size */
   L_UINT uDelay;                      /* delay */
   L_UINT uMaxPass;                    /* maximum passes */
   L_BOOL bTransparent;                /* use transparent color? */
   COLORREF crTransparent;             /* transparent color */
   L_UINT uWandWidth;                  /* wand width */
   COLORREF crWand;                    /* wand color */
} TRANSDLGPARM, L_FAR * LPTRANSDLGPARM;


/* flags for the Help Callbacks for L_Dlg* function */
#define DLG_HELP_FILEOPEN        1
#define DLG_HELP_FILEOPEN95      2
#define DLG_HELP_FILESAVE        3
#define DLG_HELP_FILESAVE95      4
#define DLG_HELP_COLORRES        5
#define DLG_HELP_GETANGLE        6
#define DLG_HELP_GETSIZE         7
#define DLG_HELP_GETFILTER       8
#define DLG_HELP_GETCHANGE       9
#define DLG_HELP_GETRANGE        10
#define DLG_HELP_GETGAMMA        11
#define DLG_HELP_GETNOISE        12
#define DLG_HELP_GETEMBOSS       13
#define DLG_HELP_WINDOWLEVEL     14
#define DLG_HELP_GETEFFECT       15
#define DLG_HELP_GETSHAPE        16
#define DLG_HELP_GETTEXT         17
#define DLG_HELP_GETGRADIENT     18
#define DLG_HELP_GETTRANSITION   19

/* flags for L_DlgFileOpen() */
#define DLG_FO_AUTOPROCESS    0x00000001   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_FO_PROGRESSIVE    0x00000002   /* FileOpen Dlg should have Prog. File options */
#define DLG_FO_MULTIPAGE      0x00000004   /* FileOpen Dlg should have Multipage options */
#define DLG_FO_LOADROTATED    0x00000008   /* FileOpen Dlg should have Load Rotated option */
#define DLG_FO_LOADCOMPRESSED 0x00000010   /* FileOpen Dlg should have Load 1-bit compressed option */
#define DLG_FO_FILEINFO       0x00000020   /* FileOpen Dlg should have FileInfo button */
#define DLG_FO_SHOWPREVIEW    0x00000040   /* FileOpen Dlg should have ThumbNail and should create the */
                                           /* preview if none is stored in the file */
#define DLG_FO_SHOWSTAMP      0x00000080   /* FileOpen Dlg should have ThumbNail and should only load */
                                           /* the preview stamp if one is stored in the file */
#define DLG_FO_95STYLE        0x00000100   /* FileOpen Dlg should have Windows95 Explorer style look */

/* flags for L_DlgFileSave() */
#define DLG_FS_AUTOPROCESS    0x00000001   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_FS_PROGRESSIVE    0x00000002   /* FileSave Dlg should have Prog. File options */
#define DLG_FS_MULTIPAGE      0x00000004   /* FileSave Dlg should have Multipage options */
#define DLG_FS_STAMP          0x00000008   /* FileSave Dlg should have save with stamp options */
#define DLG_FS_QFACTOR        0x00000010   /* FileSave Dlg should have QFactor option */
#define DLG_FS_95STYLE        0x00000020   /* FileSave Dlg should have Windows95 Explorer style look */
/* file format flags for L_DlgFileSave() */
#define DLG_FS_LEAD           0x00000002
#define DLG_FS_LEAD1BIT       0x00000004
#define DLG_FS_JFIF           0x00000008
#define DLG_FS_CALS           0x00000010
#define DLG_FS_PNG            0x00000020
#define DLG_FS_DICOM          0x00000040
#define DLG_FS_FAX            0x00000080
#define DLG_FS_EPS            0x00000100
#define DLG_FS_EXIF           0x00000200
#define DLG_FS_FPX            0x00000400
#define DLG_FS_IMG            0x00000800
#define DLG_FS_GIF            0x00001000
#define DLG_FS_IOCA           0x00002000
#define DLG_FS_PCT            0x00004000
#define DLG_FS_MAC            0x00008000
#define DLG_FS_AWD            0x00010000
#define DLG_FS_MSP            0x00020000
#define DLG_FS_OS2BMP         0x00040000
#define DLG_FS_PCX            0x00080000
#define DLG_FS_PSD            0x00100000
#define DLG_FS_RAS            0x00200000
#define DLG_FS_TGA            0x00400000
#define DLG_FS_TIFF           0x00800000
#define DLG_FS_BMP            0x01000000
#define DLG_FS_WFX            0x02000000
#define DLG_FS_WMF            0x04000000
#define DLG_FS_WPG            0x08000000
#define DLG_FS_ICO            0x10000000
#define DLG_FS_CUR            0x20000000
#define DLG_FS_ALL            0xFFFFFFFF  /* all file formats */

/* flags for Image processing dialog functions */
#define DLG_IMG_AUTOPROCESS     0x80000000   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_IMG_SHOWPREVIEW     0x40000000   /* ImageProcess Dlg should preview of image */
#define DLG_IMG_HIDEBACKCOLOR   0x20000000   /* GetAngle Dlg should hide the Background Color button */

#define DLG_IMG_RESIZE          0x00000001   /* resize dialog */
#define DLG_IMG_RESAMPLE        0x00000002   /* resample dialog */
#define DLG_IMG_ROTATE          0x00000003   /* rotate dialog */
#define DLG_IMG_SHEAR           0x00000004   /* shear dialog */

#define DLG_IMG_GRADIENT        0x00000001   /* gradient dialog */
#define DLG_IMG_LAPLACIAN       0x00000002   /* laplacian dialog */
#define DLG_IMG_SOBEL           0x00000004   /* sobel dialog */
#define DLG_IMG_PREWITT         0x00000008   /* prewitt dialog */
#define DLG_IMG_SHIFTDIFF       0x00000010   /* shiftdiff dialog */
#define DLG_IMG_LINESEG         0x00000020   /* lineseg dialog */
#define DLG_IMG_EROSION         0x00000040   /* erosion dialog */
#define DLG_IMG_DILATION        0x00000080   /* dilation dialog */

#define DLG_IMG_SHARPEN         0x00000001   /* sharpen dialog */
#define DLG_IMG_BRIGHTNESS      0x00000002   /* brightness dialog */
#define DLG_IMG_CONTRAST        0x00000004   /* contrast dialog */
#define DLG_IMG_SATURATION      0x00000008   /* saturation dialog */
#define DLG_IMG_HISTOCONTRAST   0x00000010   /* histo contrast dialog */
#define DLG_IMG_HUE             0x00000020   /* hue dialog */
#define DLG_IMG_HALFTONE        0x00000040   /* halftone dialog */
#define DLG_IMG_POSTERIZE       0x00000080   /* posterize dialog */
#define DLG_IMG_MOSAIC          0x00000100   /* mosaic dialog */
#define DLG_IMG_AVERAGE         0x00000200   /* average dialog */
#define DLG_IMG_MEDIAN          0x00000400   /* median dialog */
#define DLG_IMG_OILIFY          0x00000800   /* oilify dialog */
#define DLG_IMG_MIN             0x00001000   /* min filter dialog */
#define DLG_IMG_MAX             0x00002000   /* max filter dialog */
#define DLG_IMG_SOLARIZE        0x00004000   /* solarize dialog */

#define DLG_IMG_ADDNOISE        0x0000001C   /* add noise dialog */
#define DLG_IMG_GAMMACORRECT    0x0000001D   /* gamma correct dialog */
#define DLG_IMG_EMBOSS          0x0000001E   /* emboss filter dialog */
#define DLG_IMG_INTENSITYDETECT 0x0000001F   /* intensity detect dialog */

/* flags for L_DlgColorRes() */
#define DLG_CR_SHOWPREVIEW      0x00000001   /* shows preview of image */
#define DLG_CR_AUTOPROCESS      0x00000002   /* process the image on OK */

#define DLG_CR_1BIT             0x00000004   /* 1-bit is an option */
#define DLG_CR_2BIT             0x00000008   /* 2-bit is an option */
#define DLG_CR_3BIT             0x00000010   /* 3-bit is an option */
#define DLG_CR_4BIT             0x00000020   /* 4-bit is an option */
#define DLG_CR_5BIT             0x00000040   /* 5-bit is an option */
#define DLG_CR_6BIT             0x00000080   /* 6-bit is an option */
#define DLG_CR_7BIT             0x00000100   /* 7-bit is an option */
#define DLG_CR_8BIT             0x00000200   /* 8-bit is an option */
#define DLG_CR_12BIT            0x00000400   /* 12-bit is an option */
#define DLG_CR_16BIT            0x00000800   /* 16-bit is an option */
#define DLG_CR_24BIT            0x00001000   /* 24-bit is an option */
#define DLG_CR_32BIT            0x00002000   /* 32-bit is an option */
#define DLG_CR_BITALL           0x00003FFC   /* All BitsPerPixel are options */

#define DLG_CR_DITHER_NONE      0x00004000   /* no dithering is an option */
#define DLG_CR_DITHER_FLOYD     0x00008000   /* floyd dithering is an option */
#define DLG_CR_DITHER_STUCKI    0x00010000   /* stucki dithering is an option */
#define DLG_CR_DITHER_BURKES    0x00020000   /* burkes dithering is an option */
#define DLG_CR_DITHER_SIERRA    0x00040000   /* sierra dithering is an option */
#define DLG_CR_DITHER_STEVENSON 0x00080000   /* stevenson dithering is an option */
#define DLG_CR_DITHER_JARVIS    0x00100000   /* jarvis dithering is an option */
#define DLG_CR_DITHER_CLUSTER   0x00200000   /* clustered dithering is an option */
#define DLG_CR_DITHER_ORDERED   0x00400000   /* ordered dithering is an option */
#define DLG_CR_DITHER_ALL       0x007FC000   /* All dithering methods are options */

#define DLG_CR_PAL_FIXED      0x00800000   /* fixed palette is an option */
#define DLG_CR_PAL_OPTIMIZED  0x01000000   /* fixed palette is an option */
#define DLG_CR_PAL_IDENTITY   0x02000000   /* identity palette is an option */
#define DLG_CR_PAL_NETSCAPE   0x04000000   /* netscape palette is an option */
#define DLG_CR_PAL_ALL        0x07800000   /* All palette options are options */

#define DLG_CR_ORDER          0x08000000   /* color order is an option */


/* flags for L_DlgWindowLevel() */
#define DLG_WL_SHOWPREVIEW      0x00000001   /* shows preview of image */
#define DLG_WL_AUTOPROCESS      0x00000002   /* process the image on OK */

/* flags for L_DlgGetEffect() */
#define DLG_EFX_SHOWPREVIEW      0x00000001   /* shows preview of image */
#define DLG_EFX_AUTOPREVIEW      0x00000002   /* auto preview when options change */
#define DLG_EFX_DELAY            0x00000004   /* effect delay is an option */
#define DLG_EFX_GRAIN            0x00000008   /* effect grain is an option */
#define DLG_EFX_PASSES           0x00000010   /* effect passes is an option */
#define DLG_EFX_TRANSPARENT      0x00000020   /* transparency is an option */
#define DLG_EFX_WAND             0x00000040   /* wand is an option */
#define DLG_EFX_NO_TREEVIEW      0x00000080   /* DO NOT use TreeView */
#define DLG_EFX_CLASS_NONE       0x00000100   /* no effect class is option */
#define DLG_EFX_CLASS_WIPE       0x00000200   /* linear wipe class is option */
#define DLG_EFX_CLASS_WIPERECT   0x00000400   /* rect wipe class is option */
#define DLG_EFX_CLASS_WIPECIRCLE 0x00000800   /* circle wipe class is option */
#define DLG_EFX_CLASS_PUSH       0x00001000   /* push class is option */
#define DLG_EFX_CLASS_SLIDE      0x00002000   /* slide class is option */
#define DLG_EFX_CLASS_ROLL       0x00004000   /* roll class is option */
#define DLG_EFX_CLASS_ROTATE     0x00008000   /* rotate class is option */
#define DLG_EFX_CLASS_ZOOM       0x00010000   /* zoom class is option */
#define DLG_EFX_CLASS_DRIP       0x00020000   /* drip class is option */
#define DLG_EFX_CLASS_BLIND      0x00040000   /* blind class is option */
#define DLG_EFX_CLASS_RANDOM     0x00080000   /* random class is option */
#define DLG_EFX_CLASS_CHECK      0x00100000   /* check class is option */
#define DLG_EFX_CLASS_BLOCKS     0x00200000   /* blocks class is option */
#define DLG_EFX_CLASS_CIRCLE     0x00400000   /* circle class is option */
#define DLG_EFX_CLASS_ELLIPSE    0x00800000   /* ellipse class is option */

/* flags for L_DlgGetShape() */
#define DLG_SHAPE_SHOWPREVIEW          0x00000001   /* shows preview of image */
#define DLG_SHAPE_AUTOPREVIEW          0x00000002   /* auto preview when options change */
#define DLG_SHAPE_BACKSTYLE            0x00000004   /* backstyle is an option */
#define DLG_SHAPE_FILLSTYLE            0x00000008   /* fillstyle is an option */
#define DLG_SHAPE_FORE_BACK_COLOR      0x00000010   /* fore and back colors are options */
#define DLG_SHAPE_BORDERSTYLE          0x00000020   /* borderstyle is an option */
#define DLG_SHAPE_BORDERWIDTH          0x00000040   /* border width is an option */
#define DLG_SHAPE_BORDERCOLOR          0x00000080   /* bordercolor is an option */
#define DLG_SHAPE_INNERSTYLE           0x00000100   /* innerbandstyle is an option */
#define DLG_SHAPE_INNERWIDTH           0x00000200   /* innerband width is an option */
#define DLG_SHAPE_INNER_HILITE_SHADOW  0x00000400   /* innerband colors are options */
#define DLG_SHAPE_OUTERSTYLE           0x00000800   /* outerbandstyle is an option */
#define DLG_SHAPE_OUTERWIDTH           0x00001000   /* outerband width is an option */
#define DLG_SHAPE_OUTER_HILITE_SHADOW  0x00002000   /* outerband colors are options */
#define DLG_SHAPE_SHADOWCOLOR          0x00004000   /* shadow color is an option */
#define DLG_SHAPE_SHADOW_X_Y           0x00008000   /* shadow x and y are options */
#define DLG_SHAPE_BROWSEIMAGE          0x00010000   /* browse image button is option */
#define DLG_SHAPE_NO_TREEVIEW          0x00020000   /* DO NOT use TreeView */
#define DLG_SHAPE_CLASS_SQUARE         0x00040000   /* squares are options */
#define DLG_SHAPE_CLASS_RECTANGLE      0x00080000   /* rectangles are options */
#define DLG_SHAPE_CLASS_PARALLELOGRAM  0x00100000   /* parallelograms are options */
#define DLG_SHAPE_CLASS_TRAPEZOID      0x00200000   /* trapezoids are options */
#define DLG_SHAPE_CLASS_TRIANGLE       0x00400000   /* triangles are options */
#define DLG_SHAPE_CLASS_OTHER          0x00800000   /* other polygons are options */
#define DLG_SHAPE_CLASS_CIRCLE         0x01000000   /* circles are options */
#define DLG_SHAPE_CLASS_ELLIPSE        0x02000000   /* ellipses are options */
#define DLG_SHAPE_CLASS_STAR           0x04000000   /* stars are options */
#define DLG_SHAPE_CLASS_CROSS          0x08000000   /* crosses are options */
#define DLG_SHAPE_CLASS_ARROW          0x10000000   /* arrows are options */

/* flags for L_DlgGetText() */
#define DLG_TEXT_SHOWPREVIEW           0x00000001   /* shows preview of image */
#define DLG_TEXT_AUTOPREVIEW           0x00000002   /* auto preview when options change */
#define DLG_TEXT_SAMPLETEXT            0x00000004   /* sample text edit box is an option */
#define DLG_TEXT_STYLE                 0x00000008   /* text style is an option */
#define DLG_TEXT_COLOR                 0x00000010   /* text color is an option */
#define DLG_TEXT_BORDERCOLOR           0x00000020   /* bordercolor is an option */
#define DLG_TEXT_ALIGN                 0x00000040   /* alignment is an option */
#define DLG_TEXT_ANGLE                 0x00000080   /* angle is an option */
#define DLG_TEXT_WORDWRAP              0x00000100   /* wordwrap is an option */
#define DLG_TEXT_FONT                  0x00000200   /* font is an option */
#define DLG_TEXT_FOREIMAGE             0x00000400   /* foreground image is an option */
#define DLG_TEXT_BROWSEIMAGE           0x00000800   /* browse image button is option */
#define DLG_TEXT_SHADOWCOLOR           0x00001000   /* shadow color is an option */
#define DLG_TEXT_SHADOW_X_Y            0x00002000   /* shadow x and y are options */

/* flags for L_DlgGetGradient() */
#define DLG_GRAD_SHOWPREVIEW           0x00000001   /* shows preview of image */
#define DLG_GRAD_AUTOPREVIEW           0x00000002   /* auto preview when options change */
#define DLG_GRAD_STARTCOLOR            0x00000004   /* start color is an option */
#define DLG_GRAD_ENDCOLOR              0x00000008   /* end color is an option */
#define DLG_GRAD_STEPS                 0x00000010   /* gradient steps is an option */
#define DLG_GRAD_NO_TREEVIEW           0x00000020   /* DO NOT use TreeView */
#define DLG_GRAD_CLASS_LINEAR          0x00000040   /* linear gradients are an option */
#define DLG_GRAD_CLASS_ANGULAR         0x00000080   /* angular gradients are an option */
#define DLG_GRAD_CLASS_RECTANGULAR     0x00000100   /* rectangular gradients are an option */
#define DLG_GRAD_CLASS_ELLIPTICAL      0x00000200   /* elliptical gradients are an option */
#define DLG_GRAD_CLASS_CONICAL         0x00000400   /* conical gradients are an option */

/* flags for L_DlgGetTransition() */
#define DLG_TRANS_SHOWPREVIEW     0x00000001   /* shows preview of image */
#define DLG_TRANS_AUTOPREVIEW     0x00000002   /* auto preview when options change */
#define DLG_TRANS_FORECOLOR       0x00000004   /* forecolor is an option */
#define DLG_TRANS_BACKCOLOR       0x00000008   /* backcolor is an option */
#define DLG_TRANS_DELAY           0x00000010   /* transition delay is an option */
#define DLG_TRANS_GRAIN           0x00000020   /* transition grain is an option */
#define DLG_TRANS_EFFECT          0x00000040   /* paint effect is an option */
#define DLG_TRANS_PASSES          0x00000080   /* transition passes is an option */
#define DLG_TRANS_WAND            0x00000100   /* wand is an option */
#define DLG_TRANS_TRANSPARENT     0x00000200   /* transparency is an option */
#define DLG_TRANS_GRADIENT        0x00000400   /* gradient is an option */


/* external prototypes */
L_INT EXT_FUNCTION L_DlgFileOpen( HWND hWnd,
                                  LPOPENFILENAME pOpenFileName,
                                  LPFILEOPENPARM pFileOpenParm,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetAngle( HWND hWnd,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT32 L_FAR* pnAngle,
                                  L_INT L_FAR* pbFlag,
                                  COLORREF L_FAR* pcrBack,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetSize( HWND hWnd,
                                 pBITMAPHANDLE pBitmap,
                                 L_INT L_FAR* pnWidth,
                                 L_INT L_FAR* pnHeight,
                                 L_UINT32 uFlags,
                                 LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetFilter( HWND hWnd,
                                   pBITMAPHANDLE pBitmap,
                                   LPSPATIALFLT L_FAR* ppSpatialFlt,
                                   LPBINARYFLT L_FAR* ppBinaryFlt,
                                   L_BOOL L_FAR* pbSpatialFilter, 
                                   L_UINT32 uFlags,
                                   LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetChange( HWND hWnd,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT L_FAR* pnChange,
                                   L_UINT32 L_FAR* puProcess,
                                   L_UINT32 uFlags,
                                   LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetGamma( HWND hWnd,
                                  pBITMAPHANDLE pBitmap,
                                  L_UINT L_FAR* puGamma,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetNoise( HWND hWnd,
                                  pBITMAPHANDLE pBitmap,
                                  L_UINT L_FAR* puRange,
                                  L_UINT L_FAR* puChannel,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetEmboss( HWND hWnd,
                                   pBITMAPHANDLE pBitmap,
                                   L_UINT L_FAR* puDirection,
                                   L_UINT L_FAR* puDepth,
                                   L_UINT32 uFlags,
                                   LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetRange( HWND hWnd,
                                  pBITMAPHANDLE pBitmap,
                                  L_UINT L_FAR* puLow,
                                  L_UINT L_FAR* puHigh,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgColorRes( HWND hWnd,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT L_FAR* pnBits,
                                  L_UINT32 L_FAR* puColorResFlags,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgFileSave( HWND hWnd,
                                  LPOPENFILENAME pOpenFileName,
                                  LPFILESAVEPARM pFileSaveParm,
                                  L_UINT32 uFlags,
                                  L_UINT32 uFormatFlags,
                                  LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgWindowLevel( HWND hWnd, 
                                     pBITMAPHANDLE pBitmap, 
                                     L_RGBQUAD L_HUGE* pLUT, 
                                     L_UINT32 uLUTLength, 
                                     L_INT nLowBit, 
                                     L_INT nHighBit, 
                                     L_UINT L_FAR* pnLow, 
                                     L_UINT L_FAR* pnHigh,
                                     COLORREF L_FAR* pcrStart, 
                                     COLORREF L_FAR* pcrEnd, 
                                     L_UINT32 uFlags, 
                                     LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetEffect( HWND hWnd,
                                   pBITMAPHANDLE pBitmap,
                                   EFXDLGPARM L_FAR * pEfxDlgParm,
                                   L_UINT32 uFlags,
                                   LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetShape( HWND hWnd, pBITMAPHANDLE pBitmap,
                                  pBITMAPHANDLE pBackgroundBitmap,
                                  SHAPEDLGPARM L_FAR * pShapeDlgParm,
                                  L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetText( HWND hWnd, pBITMAPHANDLE pBitmap,
                                 pBITMAPHANDLE pForegroundBitmap,
                                 TEXTDLGPARM L_FAR * pTextDlgParm,
                                 L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetGradient( HWND hWnd, pBITMAPHANDLE pBitmap,
                                     GRADDLGPARM L_FAR * pGradDlgParm,
                                     L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback );

L_INT EXT_FUNCTION L_DlgGetTransition( HWND hWnd,
                                       pBITMAPHANDLE pBitmap,
                                       TRANSDLGPARM L_FAR * pTransDlgParm,
                                       L_UINT32 uFlags,
                                       LTCOMMDLGHELPCB pfnCallback );

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTDLG_H_ */



