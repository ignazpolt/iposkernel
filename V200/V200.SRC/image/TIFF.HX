#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
**	Filename:    	tiff.h
**	Purpose:    	This is the tiff include file.
**	Author:      	Mike Niquette, Patty Lopez, and Jim Graham
**	Environment:	Portable code, orginally designed for MAC, DOS, 
**	            	and MSWindows; now HP-UX and OS/2 PM.
**	Library:    	None.
**	History:    	Creation Date:  08/29/1988
**	Version:    	2.0
**
**	(c) Copyright Hewlett-Packard Company, 1988, 1989, 1990.
**	All rights are reserved. Copying or other reproduction of
**	this program except for archival purposes is prohibited
**	without the prior written consent of Hewlett-Packard Company.
**
**	Notes to U.S. Government Users:
**	
**			  RESTRICTED RIGHTS LEGEND
**
**	Use, duplication, or disclosure by the Government is subject to 
**	restrictions as set forth in paragraph (b) (3) (B) of the Rights 
**	in Technical Data and Computer Software clause in DAR 7-104.9(a).
**
**	Use, duplication, or disclosure by the Government is subject to 
**	restrictions as set forth in paragraph (c) (1) (ii) of the Rights 
**	in Technical Data and Computer Software clause at DFARS 252.227-7013.
**
**	HEWLETT-PACKARD COMPANY
**	Greeley, Colorado
******************************************************************************/
#ifndef	__TIFF__
#define	__TIFF__
#include	"Host.h"

/**----------------------------------------------------------------------------
							  Public Definitions
----------------------------------------------------------------------------**/

#ifndef __READ__         /* TIFF 5.0 default write only; add read capability */
#define __READ__
#endif


#ifndef __CCITT__		
#define __CCITT__		/* comment to disable CCITT compression */
#endif


#define MAXPATHLENGTH         132
#define MAXSAMPLES            10

#define CLOSEERROR            1    /* Errors returned by the TIFF code */
#define CREATEERROR           2
#define OPENERROR             3
#define READERROR             4
#define WRITEERROR            6
#define NOTTIFF               7
#define TIFFEOF               8
#define COMPRESSERROR         9
#define INITERROR             10
#define CONVERTERROR          11
#define STRIPERROR            12
#define TAGERROR              13
#define MEMORYERROR           14
#define UNSUPPORTEDERROR	  15

/* TIFF file header defines */
#define INTEL                 0x4949
#define MOTO                  0x4d4d
#define VERSION               42

/* TIFF field lengths */
#define TIFFBYTE              1
#define TIFFASCII             2
#define TIFFSHORT             3
#define TIFFLONG              4
#define TIFFRATIONAL          5

/* TIFF New Subfile type */
#define REDUCED               1
#define MULTI_PAGE            2
#define MASK                  4

/* TIFF compression type */
#define NOCOMPRESSION         1 /* for fast function-indexed lookup */
#define CCITT                 2
#define LZW                   5
#define PACKBITS              0x8005

/* TIFF planar configuration */
#define CONTIGUOUS            1
#define PLANAR                2

/* Current TIFF tags */
#define ARTIST                315
#define BITS_PER_SAMPLE       258
#define COLOR_CURVE           301
#define COLOR_MAP             320
#define COMPRESSION           259
#define DATE_TIME             306
#define DOCUMENT_NAME         269
#define GRAY_CURVE            291
#define GRAY_UNIT             290
#define GROUP_3_OPTIONS       292
#define GROUP_4_OPTIONS       293
#define HIGHLIGHT_SHADOW      321
#define HOST_COMPUTER         316
#define IMAGE_DESCRIPTION     270
#define IMAGE_LENGTH          257
#define IMAGE_WIDTH           256
#define MAKE                  271
#define MODEL                 272
#define NEW_SUBFILE           254
#define PAGE_NAME             285
#define PAGE_NUMBER           297
#define PHOTO_INTERPRET       262
#define PLANAR_CONFIG         284
#define PREDICTOR             317
#define PRIMARY_CHROMATIC     319
#define RESOLUTION_UNIT       296
#define ROWS_PER_STRIP        278
#define SAMPLES_PER_PIXEL     277
#define SOFTWARE              305
#define STRIP_COUNTS          279
#define STRIP_OFFSETS         273
#define WHITE_POINT           318
#define X_POSITION            286
#define XRESOLUTION           282
#define Y_POSITION            287
#define YRESOLUTION           283

/* Obsolete TIFF Tags */
#define CELL_LENGTH           265
#define CELL_WIDTH            264
#define FILL_ORDER            266
#define FREE_BYTE_COUNTS      289
#define FREE_OFFSETS          288
#define MAX_SAMPLE_VALUE      281
#define MIN_SAMPLE_VALUE      280
#define SUBFILE_TYPE          255
#define ORIENTATION           274
#define THRESHOLDING          263
#endif

/**----------------------------------------------------------------------------
					  	Public Type Definitions
----------------------------------------------------------------------------**/

typedef PUINT8 FAR * PIMAGE;

typedef struct
{
     INT32     n;
     INT32     d;
}    RATIONAL;

typedef union
{
     INT8      b[4];
     INT16     s[2];
     INT32     l;
     INT32     o;
}    TIFFVALUE;

#ifndef WIN32
  typedef TIFFVALUE FD *  PVALUE;
#endif

typedef struct
{
     UINT16    Tag;
     INT16    Kind;
     INT32     Length;
     TIFFVALUE Value;
}    TIFFENTRY;
typedef TIFFENTRY FD *PTIFFENTRY;

#define ENTRYSIZE sizeof(TIFFENTRY)

typedef struct
{
/* TIFF file information */
     UINT8     Name[MAXPATHLENGTH];/* name of the opened/created file */
     INT16     Handle;      	/* pointer to the opened/created file, or -1 */
     UINT16    Format;      	/* format of file (Intel or Motorola) */

/* TIFF buffer information */
     PUINT8    pBuffer;     	/* pointer to user-allocated tag buffer */
     INT32     Offset;       	/* offset of subfile just put or -1L */
     INT32     Size;        	/* size of tag buffer */
     INT32     WidthBytes;  	/* varies with bits/pixel */
     INT16     BitsPerPixel;	/* varies with plane */
     INT32     Row;

/* TIFF header information */
     INT16     Entries;     	/* number of tag entries in pBuffer */
     INT16     KindOffsets; 	/* kind of StripOffsets (short or long) */
     INT16     KindCounts;  	/* kind of StripCounts  (short or long) */
     INT16     KindLength;  	/* kind of ImageLength  (short or long) */
     INT16     KindWidth;   	/* kind of ImageWidth   (short or long) */
     INT16     KindRowsPer;  	/* kind of RowsPerStrip (short or long) */

/* TIFF image information */
     INT32     NewSubfile;		/* subfile type */
     INT32     ImageWidth;		/* image witdth in pixels */
     INT32     ImageLength;		/* image length in pixels */
     INT32     RowsPerStrip;	/* number of rows in each strip */
     INT16     SamplesPerPixel;	/* number of samples in each pixel */
     UINT16    Compression;		/* type of compression used */
     INT16     PhotoInterpret;	/* type of image data */
     INT16     PlanarConfig;	/* planar or chunky image data */
     RATIONAL  XResolution;		/* horizontal resolution */
     RATIONAL  YResolution;		/* vertical resolution */
     INT16     ResolutionUnit;	/* type of units used for resolution */
     INT16     BitsPerSample[MAXSAMPLES];	/* number of bits in each sample */

}    TIFFFILE;
typedef TIFFFILE FD *  PTIFFFILE;

/**----------------------------------------------------------------------------
					  Public Function Prototypes
----------------------------------------------------------------------------**/

/* read entry definitions */
#define GetBitsPerSample(v,w,x,y,z)    GetEntryData((v),BITS_PER_SAMPLE,0L,-1L,(w),(x),(y),(z))
#define GetColorMap(v,w,x,y,z)         GetEntryData((v),COLOR_MAP,0L,-1L,(w),(x),(y),(z))
#define GetColorCurves(v,w,x,y,z)      GetEntryData((v),COLOR_CURVE,0L,-1L,(w),(x),(y),(z))
#define GetCompression(w,x,y,z)        GetEntry((w),    COMPRESSION,0L,(x),(y),(z))
#define GetGrayCurve(v,w,x,y,z)        GetEntryData((v),GRAY_CURVE,0L,-1L,(w),(x),(y),(z))
#define GetGrayUnit(w,x,y,z)           GetEntry((w),    GRAY_UNIT,0L,(x),(y),(z))
#define GetImageWidth(w,x,y,z)         GetEntry((w),    IMAGE_WIDTH,0L,(x),(y),(z))
#define GetImageLength(w,x,y,z)        GetEntry((w),    IMAGE_LENGTH,0L,(x),(y),(z))
#define GetNewSubfile(w,x,y,z)         GetEntry((w),    NEW_SUBFILE,0L,(x),(y),(z))
#define GetPhotoInterpret(w,x,y,z)     GetEntry((w),    PHOTO_INTERPRET,0L,(x),(y),(z))
#define GetPlanarConfig(w,x,y,z)       GetEntry((w),    PLANAR_CONFIG,0L,(x),(y),(z))
#define GetPredictor(w,x,y,z)          GetEntry((w),    PREDICTOR,0L,(x),(y),(z))
#define GetResolutionUnit(w,x,y,z)     GetEntry((w),    RESOLUTION_UNIT,0L,(x),(y),(z))
#define GetRowsPerStrip(w,x,y,z)       GetEntry((w),    ROWS_PER_STRIP,0L,(x),(y),(z))
#define GetSamplesPerPixel(w,x,y,z)    GetEntry((w),    SAMPLES_PER_PIXEL,0L,(x),(y),(z))
#define GetStripCounts(v,w,x,y,z)      GetEntryData((v),STRIP_COUNTS,0L,-1L,(w),(x),(y),(z))
#define GetStripOffsets(v,w,x,y,z)     GetEntryData((v),STRIP_OFFSETS,0L,-1L,(w),(x),(y),(z))
#define GetXResolution(v,w,x,y,z)      GetEntryData((v),XRESOLUTION,0L,1L,(w),(x),(y),(z))
#define GetYResolution(v,w,x,y,z)      GetEntryData((v),YRESOLUTION,0L,1L,(w),(x),(y),(z))
#define GetGroup3Options(w,x,y,z)      GetEntry((w),    GROUP_3_OPTIONS,0L,(x),(y),(z))
#define GetGroup4Options(w,x,y,z)      GetEntry((w),    GROUP_4_OPTIONS,0L,(x),(y),(z))
#define GetArtist(v,w,x,y,z)           GetEntryData((v),ARTIST,0L,-1L,(w),(x),(y),(z))
#define GetDateTime(v,w,x,y,z)         GetEntryData((v),DATE_TIME,0L,-1L,(w),(x),(y),(z))
#define GetHostComputer(v,w,x,y,z)     GetEntryData((v),HOST_COMPUTER,0L,-1L,(w),(x),(y),(z))
#define GetImageDescription(v,w,x,y,z) GetEntryData((v),IMAGE_DESCRIPTION,0L,-1L,(w),(x),(y),(z))
#define GetMake(v,w,x,y,z)             GetEntryData((v),MAKE,0L,-1L,(w),(x),(y),(z))
#define GetModel(v,w,x,y,z)            GetEntryData((v),MODEL,0L,-1L,(w),(x),(y),(z))
#define GetSoftware(v,w,x,y,z)         GetEntryData((v),SOFTWARE,0L,-1L,(w),(x),(y),(z))
#define GetDocumentName(v,w,x,y,z)     GetEntryData((v),DOCUMENT_NAME,0L,-1L,(w),(x),(y),(z))
#define GetPageName(v,w,x,y,z)         GetEntryData((v),PAGE_NAME,0L,-1L,(w),(x),(y),(z))
#define GetPageNumber(v,w,x,y,z)       GetEntryData((v),PAGE_NUMBER,0L,2L,(w),(x),(y),(z))
#define GetXPosition(v,w,x,y,z)        GetEntryData((v),X_POSITION,0L,1L,(w),(x),(y),(z))
#define GetYPosition(v,w,x,y,z)        GetEntryData((v),Y_POSITION,0L,1L,(w),(x),(y),(z))
#define GetWhitePoint(v,w,x,y,z)       GetEntryData((v),WHITE_POINT,0L,2L,(w),(x),(y),(z))
#define GetPrimaryChromatic(v,w,x,y,z) GetEntryData((v),PRIMARY_CHROMATIC,0L,6L,(w),(x),(y),(z))
#define GetHighlightShadow(v,w,x,y,z)  GetEntryData((v),HIGHLIGHT_SHADOW,0L,2L,(w),(x),(y),(z))

/* not recommended */
#define GetCellLength(w,x,y,z)         GetEntry((w),    CELL_LENGTH,0L,(x),(y),(z))
#define GetCellWidth(w,x,y,z)          GetEntry((w),    CELL_WIDTH,0L,(x),(y),(z))
#define GetFillOrder(w,x,y,z)          GetEntry((w),    FILL_ORDER,0L,(x),(y),(z))
#define GetFreeByteCounts(v,w,x,y,z)   GetEntryData((v),FREE_BYTE_COUNTS,0L,-1L,(w),(x),(y),(z))
#define GetFreeOffsets(v,w,x,y,z)      GetEntryData((v),FREE_OFFSETS,0L,-1L,(w),(x),(y),(z))
#define GetMaxSampleValue(v,w,x,y,z)   GetEntryData((v),MAX_SAMPLE_VALUE,0L,-1L,(w),(x),(y),(z))
#define GetMinSampleValue(v,w,x,y,z)   GetEntryData((v),MIN_SAMPLE_VALUE,0L,-1L,(w),(x),(y),(z))
#define GetSubfileType(w,x,y,z)        GetEntry((w),    SUBFILE_TYPE,0L,(x),(y),(z))
#define GetOrientation(w,x,y,z)        GetEntry((w),    ORIENTATION,0L,(x),(y),(z))
#define GetThresholding(w,x,y,z)       GetEntry((w),    THRESHOLDING,0L,(x),(y),(z))

/* write entry definitions */
#define PutBitsPerSample(x,y,z)  PutEntryData((x), BITS_PER_SAMPLE,  TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutColorMap(x,y,z)       PutEntryData((x), COLOR_MAP,        TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutColorCurve(x,y,z)     PutEntryData((x), COLOR_CURVE,      TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutCompression(x,y)      PutEntry((x),     COMPRESSION,      TIFFSHORT,   (INT32)(y))
#define PutGrayCurve(x,y,z)      PutEntryData((x), GRAY_CURVE,       TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutGrayUnit(x,y)         PutEntry((x),     GRAY_UNIT,        TIFFSHORT,   (INT32)(y))
#define PutImageWidth(x,y,z)     PutEntry((x),     IMAGE_WIDTH,      (y),         (INT32)(z))
#define PutImageLength(x,y,z)    PutEntry((x),     IMAGE_LENGTH,     (y),         (INT32)(z))
#define PutNewSubfile(x,y)       PutEntry((x),     NEW_SUBFILE,      TIFFLONG,    (INT32)(y))
#define PutPhotoInterpret(x,y)   PutEntry((x),     PHOTO_INTERPRET,  TIFFSHORT,   (INT32)(y))
#define PutPlanarConfig(x,y)     PutEntry((x),     PLANAR_CONFIG,    TIFFSHORT,   (INT32)(y))
#define PutPredictor(x,y)        PutEntry((x),     PREDICTOR,        TIFFSHORT,   (INT32)(y))
#define PutResolutionUnit(x,y)   PutEntry((x),     RESOLUTION_UNIT,  TIFFSHORT,   (INT32)(y))
#define PutRowsPerStrip(x,y,z)   PutEntry((x),     ROWS_PER_STRIP,   (y),         (INT32)(z))
#define PutSamplesPerPixel(x,y)  PutEntry((x),     SAMPLES_PER_PIXEL,TIFFSHORT,   (INT32)(y))
#define PutStripCounts(x,y,z)    PutEntryData((x), STRIP_COUNTS,     (y),         (INT32)(z))
#define PutStripOffsets(x,y,z)   PutEntryData((x), STRIP_OFFSETS,    (y),         (INT32)(z))
#define PutXResolution(x,y)      PutEntryData((x), XRESOLUTION,      TIFFRATIONAL,(PUINT8)(y),1L)
#define PutYResolution(x,y)      PutEntryData((x), YRESOLUTION,      TIFFRATIONAL,(PUINT8)(y),1L)
#define PutGroup3Options(x,y)    PutEntry((x),     GROUP_3_OPTIONS,  TIFFLONG,    (INT32)(y))
#define PutGroup4Options(x,y)    PutEntry((x),     GROUP_4_OPTIONS,  TIFFLONG,    (INT32)(y))
#define PutArtist(x,y)           PutEntryData((x), ARTIST,           TIFFASCII,   (PUINT8)(y),0L) 
#define PutDateTime(x,y)         PutEntryData((x), DATE_TIME,        TIFFASCII,   (PUINT8)(y),0L)
#define PutHostComputer(x,y)     PutEntryData((x), HOST_COMPUTER,    TIFFASCII,   (PUINT8)(y),0L)
#define PutImageDescription(x,y) PutEntryData((x), IMAGE_DESCRIPTION,TIFFASCII,   (PUINT8)(y),0L)
#define PutMake(x,y)             PutEntryData((x), MAKE,             TIFFASCII,   (PUINT8)(y),0L)
#define PutModel(x,y)            PutEntryData((x), MODEL,            TIFFASCII,   (PUINT8)(y),0L)
#define PutSoftware(x,y)         PutEntryData((x), SOFTWARE,         TIFFASCII,   (PUINT8)(y),0L)
#define PutDocumentName(x,y)     PutEntryData((x), DOCUMENT_NAME,    TIFFASCII,   (PUINT8)(y),0L)
#define PutPageName(x,y)         PutEntryData((x), PAGE_NAME,        TIFFASCII,   (PUINT8)(y),0L)
#define PutPageNumber(x,y)       PutEntry((x),     PAGE_NUMBER,      TIFFSHORT,   (INT32)(y))
#define PutXPosition(x,y)        PutEntryData((x), X_POSITION,       TIFFRATIONAL,(PUINT8)(y),1L)
#define PutYPosition(x,y)        PutEntryData((x), Y_POSITION,       TIFFRATIONAL,(PUINT8)(y),1L)
#define PutWhitePoint(x,y)       PutEntryData((x), WHITE_POINT,      TIFFRATIONAL,(PUINT8)(y),2L)
#define PutPrimaryChromatic(x,y) PutEntryData((x), PRIMARY_CHROMATIC,TIFFRATIONAL,(PUINT8)(y),6L)
#define PutHighlightShadow(x,y)  PutEntryData((x), HIGHLIGHT_SHADOW, TIFFSHORT,   (PUINT8)(y),2L)

/* defines for obsolete tags */
#define PutCellLength(x,y)       PutEntry((x),     CELL_LENGTH,      TIFFSHORT,   (INT32)(y))
#define PutCellWidth(x,y)        PutEntry((x),     CELL_WIDTH,       TIFFSHORT,   (INT32)(y))
#define PutFillOrder(x,y)        PutEntry((x),     FILL_ORDER,       TIFFSHORT,   (INT32)(y))
#define PutFreeByteCounts(x,y,z) PutEntryData((x), FREE_BYTE_COUNTS, TIFFLONG,    (PUINT8)(y),(UINT32)(z))
#define PutFreeOffsets(x,y,z)    PutEntryData((x), FREE_OFFSETS,     TIFFLONG,    (PUINT8)(y),(UINT32)(z))
#define PutMaxSampleValue(x,y,z) PutEntryData((x), MAX_SAMPLE_VALUE, TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutMinSampleValue(x,y,z) PutEntryData((x), MIN_SAMPLE_VALUE, TIFFSHORT,   (PUINT8)(y),(UINT32)(z))
#define PutSubfileType(x,y)      PutEntry((x),     SUBFILE_TYPE,     TIFFSHORT,   (INT32)(y))
#define PutOrientation(x,y)      PutEntry((x),     ORIENTATION,      TIFFSHORT,   (INT32)(y))
#define PutThresholding(x,y)     PutEntry((x),     THRESHOLDING,     TIFFSHORT,   (INT32)(y))

#ifdef   __UNIX__

/* High Level */
INT16 GetImage( /* PTIFFFILE pTiff, INT16 Plane, INT32 Start, INT32 Lines, 
                   PUINT8 pData, INT32 Count */ );
INT16 PutImage( /* PTIFFFILE pTiff, INT16 Plane, INT32 Start, INT32 Lines, 
                   PUINT8 pData, INT32 Count */ );

/* File */
INT16 CloseTiff ( /* PTIFFFILE pTiff */ );
INT16 CreateTiff( /* PTIFFFILE pTiff, PUINT8 pName, UINT16 Format */ );
INT16 OpenTiff  ( /* PTIFFFILE pTiff, PUINT8 pName */ );

/* Subfile  */
void  CreateSubfile ( /* PTIFFFILE pTiff, PUINT8 pBuffer, UINT32 Size */ );
INT16 GetSubfile    ( /* PTIFFFILE pTiff, INT16 Subfile */ );
INT16 PutSubfile    ( /* PTIFFFILE pTiff */ );

/* Entry */
INT16 DeleteEntry ( /* PTIFFFILE pTiff, UINT16 Tag */ );
INT16 GetEntry( /* PTIFFFILE pTiff, UINT16 Tag, INT32 Index, PINT16 pKind, 
		PINT32 Length, PINT32 pValue */ );
INT16 GetEntryData( /* PTIFFFILE pTiff, UINT16 Tag, INT32 Start, INT32 Items, 
		INT32 MaxBytes, PINT16 pKind, PINT32 pLength, PUINT8 pData */ );
INT16 IndexEntry  ( /* PTIFFFILE pTiff, UINT16 Index, PTIFFENTRY pEntry */ );
INT16 PutEntry	  ( /* PTIFFFILE pTiff, UINT16 Tag, INT16 Kind, INT32 Value */ );
INT16 PutEntryData( /* PTIFFFILE pTiff, UINT16 Tag, INT16 Kind, PUINT8 pValue,
                       INT32 Length */ );

#else

/* High Level */
INT16 FAR PASCAL GetImage( PTIFFFILE pTiff, INT16 Plane, INT32 Start, INT32 Lines, 
                PUINT8 pData, INT32 Count );
INT16 FAR PASCAL PutImage( PTIFFFILE pTiff, INT16 Plane, INT32 Start, INT32 Lines, 
                PUINT8 pData, INT32 Count );

/* File */
INT16 FAR PASCAL CloseTiff ( PTIFFFILE pTiff );
INT16 FAR PASCAL CreateTiff( PTIFFFILE pTiff, PUINT8 pName, UINT16 Format );
INT16 FAR PASCAL OpenTiff  ( PTIFFFILE pTiff, PUINT8 pName );

/* Subfile  */
void  FAR PASCAL CreateSubfile ( PTIFFFILE pTiff, PUINT8 pBuffer, UINT32 Size );
INT16 FAR PASCAL GetSubfile    ( PTIFFFILE pTiff, INT16 Subfile );
INT16 FAR PASCAL PutSubfile    ( PTIFFFILE pTiff );

/* Entry */
INT16 FAR PASCAL DeleteEntry ( PTIFFFILE pTiff, UINT16 Tag );
INT16 FAR PASCAL GetEntry( PTIFFFILE pTiff, UINT16 Tag, INT32 Index, PINT16 pKind, 
		PINT32 Length, PINT32 pValue );
INT16 FAR PASCAL GetEntryData( PTIFFFILE pTiff, UINT16 Tag, INT32 Start, INT32 Items, 
		INT32 MaxBytes, PINT16 pKind, PINT32 pLength, PUINT8 pData );
INT16 FAR PASCAL IndexEntry  ( PTIFFFILE pTiff, INT16 Index, PTIFFENTRY pEntry );
INT16 FAR PASCAL PutEntry	  ( PTIFFFILE pTiff, UINT16 Tag, INT16 Kind, INT32 Value );
INT16 FAR PASCAL PutEntryData( PTIFFFILE pTiff, UINT16 Tag, INT16 Kind, PUINT8 pValue,
                       INT32 Length );

#endif

/* Compression */
#ifdef __UNIX__

INT16 PackTight  ( /* PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength */ ); 
INT16 PackBITS   ( /* PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength */ ); 
INT16 PackCCITT  ( /* PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength */ ); 
INT16 PackLZW    ( /* PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength */ ); 

INT16 UnpackTight( /* PTIFFFILE pTiff, PUINT8 pData, PINT32 pOffset, 
                        INT32 Lines, INT32 Count */ );
INT16 UnpackBITS ( /* PTIFFFILE pTiff, PUINT8 pData, PINT32 pOffset, 
                        INT32 Lines, INT32 Count */ );
INT16 UnpackCCITT( /* PTIFFFILE pTiff, PUINT8 pData, PINT32 pOffset, 
                        INT32 Lines, INT32 Count */ );
INT16 UnpackLZW  ( /* PTIFFFILE pTiff, PUINT8 pData, PINT32 pOffset, 
                        INT32 Lines, INT32 Count */ );

#else /* DOS and Mac */

INT16 FAR PASCAL PackTight  ( PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength ); 
INT16 FAR PASCAL PackBITS   ( PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength ); 
INT16 FAR PASCAL PackCCITT  ( PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength ); 
INT16 FAR PASCAL PackLZW    ( PTIFFFILE pTiff, PUINT8 pData, INT32 Lines, 
                        INT32 Count, PINT32 pLength ); 
 
INT16 FAR PASCAL UnpackTight( PTIFFFILE pTiff, PUINT8 pData, PINT32 Offset, 
                        INT32 Lines, INT32 Count );
INT16 FAR PASCAL UnpackBITS ( PTIFFFILE pTiff, PUINT8 pData, PINT32 Offset, 
                        INT32 Lines, INT32 Count );
INT16 FAR PASCAL UnpackCCITT( PTIFFFILE pTiff, PUINT8 pData, PINT32 Offset, 
                        INT32 Lines, INT32 Count );
INT16 FAR PASCAL UnpackLZW  ( PTIFFFILE pTiff, PUINT8 pData, PINT32 Offset, 
                        INT32 Lines, INT32 Count );

#endif
#ifdef __cplusplus
}
#endif
