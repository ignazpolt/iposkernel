/////////////////////////////////////////////////////////////////////////////
//
//    imageman.h
//
//
//    ImageMan Prototypes & User Structures
//
//
//    ImageMan Image Processing Library
//
//    Copyright (c) 1991,1992,1993 Data Techniques, Inc.
//    All Rights Reserved
//
/////////////////////////////////////////////////////////////////////////////
//Revision-History
//  1 IMGMAN2.H 30-Jul-93,12:44:38,`JGD' Initial Alpha Release
//  2 IMGMAN2.H 29-Oct-93,9:11:02,`JGD' 11/1/93 Update
//  3 IMGMAN2.H 7-Dec-93,11:38:56,`JGD' Added IMG_FIXEDPALETTE define
//  4 IMGMAN2.H 20-Jan-94,11:33:50,`JGD' Added PALCOLORS macro
//  5 IMGMAN2.H 20-Jan-94,11:41:12,`JGD' Fixed problem w/last checkin
//  6 IMGMAN2.H 20-Jan-94,13:54:02,`THK'
//       Added new task-based info, including status procs.
//       Also, fixed mucho-many warnings.
//  7 IMGMAN2.H 7-Feb-94,13:35:52,`THK' Added scaling defines.
//  8 IMGMAN2.H 11-Feb-94,0:32:44,`THK' Added ImgInvert function.
//Revision-History

//Keyword-Flag   "%v %f %w %n"

// 
// This include file is broken into several sections:
//      1. Defines
//      2. Structures
//      3. Macros
//      4. 

/////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////

// Error defines
#define IMG_ERR         0       /* this means an error occurred */
#define IMG_OK          1               
#define IMG_INV_FILE    2       /* unsupported file type */
#define IMG_FILE_ERR    3       /* error reading from file */
#define IMG_NOFILE      4       /* file not found */
#define IMG_NOTAVAIL    5       /* info not available */
#define IMG_NOMEM       6       /* insufficient memory */
#define IMG_CLOSED      7       /* image file is closed */
#define IMG_INV_HAND    8       /* invalid image handle */
#define IMG_NSUPPORT    9       /* image option not supported */
#define IMG_PROC_ERR    10    	/* error processing image */
#define IMG_PRINT_ERR   11    	/* error printing image */
#define IMG_BAD_PRN     12    	/* printer don't support bitmaps */
#define IMG_BAD_SRC     13    	/* specified invalid source rect */
#define IMG_BAD_TYPE    14    	/* tried to use ImgGetDIB on vector img */
#define IMG_NO_DILS     15    	/* found no DILs during initialization */
#define IMG_INV_PAGE    16      /* tried to seek to a non-existent page */
#define IMG_NO_PROC     17      /* Couldn't get * to DIL function */
#define IMG_TOOBIG		 18 		// DIB would be > 16MB 
#define IMG_PASTECLIP	 19 		// Error pasting DIB or WMF onto clipboard
#define IMG_BLITERR		 20		// Error StretchBlit'ing to dc
#define IMG_DIBERR		 21		// Error Blit'ing DIB to dc
#define IMG_METAFILEERR 22		// Error Playing metafile to dc

// Image flags
#define IMG_RENDER_SELF 1
#define IMG_PRINT_SELF  2
#define IMG_PRNT_VECTOR 4
#define IMG_DISP_VECTOR 8       // 1 if image will display in vector format
#define IMG_MEM_BASED           16      //1 if image not read from Disk

// Raster-Op defines
#define IMG_TRANSPARENT (0xffffffff)

// Color Reduction Defines
#define IMG_BAYER			1
#define IMG_BURKES			2
#define IMG_FLOYD			4
#define IMG_GRAYSCALE		8
#define IMG_FIXEDPALETTE	16

//
// ImgCopy flags
#define COPY_DEL		0x01	// pick out individual pixels (no AND or OR)
#define	COPY_AND		0x02	// preserve black pixels
#define COPY_OR		0x04	// preserve white pixels

/////////////////////////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////////////////////////

// status function typedef
typedef int (FAR PASCAL *STATUSPROC)(HANDLE, WORD, DWORD);

// prototypes for ImageMan functions
// done
int  FAR PASCAL ImgInit(void);
int  FAR PASCAL ImgClose(HANDLE);
int  FAR PASCAL ImgGetStatus(void);
int  FAR PASCAL ImgErrBox(HWND);
int  FAR PASCAL ImgErrString(LPSTR, int);
int  FAR PASCAL ImgVerString(LPSTR, int);
void FAR PASCAL ImgShutdown(void);
HANDLE   FAR PASCAL ImgOpen(LPSTR, int, long, LPSTR);
HANDLE   FAR PASCAL ImgGetDIB(HANDLE, BOOL, LPRECT);
HANDLE FAR PASCAL ImgGetWMF(HANDLE, LPRECT);
HANDLE   FAR PASCAL ImgOpenSolo(LPSTR, LPSTR);
HANDLE   FAR PASCAL ImgGetPalette(HANDLE);
int  FAR PASCAL ImgSetROP(HANDLE,DWORD);
DWORD    FAR PASCAL ImgGetROP(HANDLE);
int  FAR PASCAL ImgDrawImage(HANDLE, HDC, LPRECT, LPRECT);
LPBITMAPINFO  FAR PASCAL ImgGetInfo(HANDLE, LPINT);
HANDLE FAR PASCAL ImgGetDDB(HANDLE hImage, HDC hDC);
HANDLE FAR PASCAL ImgFromDIB(HANDLE hDIB);
HANDLE FAR PASCAL ImgFromWMF(HANDLE hWMF, LPRECT lpBBox);
HANDLE FAR PASCAL ImgFromClipboard(void);
int FAR PASCAL ImgToClipboard(HANDLE);
LPSTR FAR PASCAL ImgGetExt(void);
int  FAR PASCAL ImgLoad(HANDLE, LPRECT);
int FAR PASCAL ImgUnload(HANDLE, BOOL, BOOL, BOOL);
HANDLE FAR PASCAL ImgVectorToRaster(HANDLE, HDC);
int FAR PASCAL ImgCreateDDB(HANDLE,HDC,int,int);
int FAR PASCAL ImgPageCount(HANDLE, LPINT);
int FAR PASCAL ImgSetPage(HANDLE, int);
int FAR PASCAL ImgGetPage(HANDLE, LPINT);
HANDLE FAR PASCAL ImgRotate( HANDLE, int, COLORREF );
int FAR PASCAL ImgBrightness( HANDLE, int );
int FAR PASCAL ImgGamma( HANDLE, int );
int FAR PASCAL ImgInvert(HANDLE hImage);

int FAR PASCAL ImgMirror( HANDLE, BOOL, BOOL );
HANDLE FAR PASCAL ImgReduceColors( HANDLE, int, long );

HANDLE FAR PASCAL ImgCopy(HANDLE, int, int, LPRECT, LONG);

int  FAR PASCAL ImgPrintImage(HANDLE, HDC, LPRECT, LPRECT);
HANDLE   FAR PASCAL ImgExt(void);
HANDLE   FAR PASCAL ImgOpenEmbedded( LPSTR, long, long, LPSTR );
void FAR PASCAL ImgSetDefaultStatusProc(STATUSPROC, LONG, DWORD);
int FAR PASCAL ImgSetStatusProc( HANDLE, STATUSPROC, LONG, DWORD);
int FAR PASCAL ImgSaveImage( HANDLE );

// macros
#define PALETTESIZE(lpbi) (((lpbi)->biClrUsed ? (lpbi)->biClrUsed : (1 << (lpbi)->biBitCount)) * sizeof(RGBQUAD))
#define PALCOLORS(lpbi) (((lpbi)->biClrUsed ? (lpbi)->biClrUsed : (1 << (lpbi)->biBitCount) ))
#define BITSOFFSET(lpbi) (sizeof(BITMAPINFOHEADER) + PALETTESIZE(lpbi))
#define ROWSIZE(w,bits) (w*bits+31)/32*4
#define RECTWID(r) (r->right-r->left+1)
#define RECTHI(r) (r->bottom-r->top+1)
