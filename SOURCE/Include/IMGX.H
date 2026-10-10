/////////////////////////////////////////////////////////////////////////////
//
//    imgx.h
//
//		All external definitions needed to use ImageMan/X
//
//    ImageMan/X Image Processing Library
//
//    Copyright (c) 1991, 1992 Data Techniques, Inc.
//    All Rights Reserved
//
/////////////////////////////////////////////////////////////////////////////
//Revision-History
//  1 IMGX.H 19-Oct-92,16:52:52,`JGD' ImageMan/X Release 1.0
//  2 IMGX.H 27-Dec-93,11:03:26,`THK' Added multipage flag
//  3 IMGX.H 28-Dec-93,9:00:20,`THK' Added color caps flags
//       Added color caps flags
//  4 IMGX.H 28-Dec-93,22:16:18,`THK' Merged ImageMan & ImageMan/X
//  
//  5 IMGX.H 4-Jan-94,15:02:30,`THK'
//       Updated status function to be compatible w/ DIL status func.
//  6 IMGX.H 4-Jan-94,16:02:32,`THK'
//       Ooops! Just fixing a little booboo with my last merge...
//  7 IMGX.H 7-Jan-94,11:38:50,`THK'
//       Added IMGXINIT struct to IMXDLget_ext to allow "un-linked linking" into imgx.
//  8 IMGX.H 14-Jan-94,15:08:38,`THK'
//       Fixed OptBlk problem w/DELs. Also, added C code for 2DCCITT.
//  9 IMGX.H 19-Jan-94,18:44:26,`THK'
//       Added new task-based info, including status procs.
//       Also, fixed mucho-many warnings.
//Revision-History

//Keyword-Flag   "%v %f %w %n"

// define all errors

#define IMGX_ERR			0
#define IMGX_OK			1
#define IMGX_NO_DELS	202
#define IMGX_INV_FILE  203   	// unsupported file type
#define IMGX_FILE_ERR  204   	// error writing file
#define IMGX_NOMEM   	205   	// insufficient memory
#define IMGX_INV_HAND 	206   	// invalid image handle
#define IMGX_NSUPPORT 	207   	// image option not supported
#define IMGX_BAD_DEL	208	 	// couldn't load the DEL
#define IMGX_DISK_FULL	209	 	// disk full when writing
#define IMGX_EXISTS		210  	// file exists
#define IMGX_NO_OPEN	211	 	// error opening file
#define IMGX_DELETE_ERR 212	// error deleting file
#define IMGX_ABORTED	 213	// user aborted export
#define IMGX_BADDIB		 214	// Can't lock hDIB in ImgXWriteDIB

// Define xinfo struct

typedef struct _XINFO {
	long	lFlags;			// flags pertaining to an image
	long	lProcessed;		// # of source bytes processed
	long	lTotalBytes;	// # of total source bytes to process
	long	lWritten;		// # of bytes written to export file
	long	lIncrement;		// call status func after this many bytes processed
	long	lIncCnt;			// increment counter
	DWORD	dwUserInfo;		// user info passed to status proc
	int 	(FAR PASCAL *lpfnStat)(HANDLE, int, DWORD);
} XINFO;
typedef XINFO FAR *LPXINFO;

// status function typedef
typedef int (FAR PASCAL *STATUSPROC)(HANDLE, WORD, DWORD);

// define flags for use in XINFO struct's lFlags member
#define XF_BACKWARD		0x01 	// if on, last row written first (like DIB)
#define XF_EXPORTOPTS	0x02	// if on, the format has export options
#define XF_MULTIPAGE	0x04	// if on, format supports multiple images
#define XF_MONOCHROME	0x08	// 1 if can export mono images
#define XF_4BIT			0x10	// 1 if can export 4-bit (16-color) images
#define XF_8BIT			0x20	// 1 if can export 8-bit (256 color) images
#define XF_24BIT			0x40	// 1 if can export 24-bit images
#define XF_PALETTE		0x80	// 1 if can include a palette (otherwise it's grayscale)
#define XF_ALLCOLORS	XF_MONOCHROME | XF_4BIT | XF_8BIT | XF_24BIT | XF_PALETTE

// ImgXWriteDIB defines
#define IMGXOPT_FILE_PROMPT	0x0001
#define IMGXOPT_OVERWRITE		0x0002
#define IMGXOPT_COMPRESS		0x0004
#define IMGXOPT_OPT_PROMPT	0x0008
#define IMGXOPT_OVERWRITE_PROMPT 0x00010

// ImgMan/X callback functions for use by DELs (and ImageMan/X)
void FAR PASCAL ImgXSetError(HANDLE hInst, int nIndex, LPSTR lpModule, LPSTR lpFileName);
typedef void (FAR PASCAL *XERRORPROC)(HANDLE, int, LPSTR, LPSTR);
typedef struct tagXInitStruct {
	long	lFlags;
	XERRORPROC SetError;
	HANDLE	hImgManInst;	// instance of ImageMan DLL
} XINITSTRUCT, FAR *LPXINITSTRUCT;

// Define bitmapinfo struct which contains entries for all 256 pal entries
typedef struct _BITMAPINFO256 {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD				pal[256];	
} BITMAPINFO256;

int FAR PASCAL 	ImgXInit(HANDLE);
int FAR PASCAL 	ImgXGetExt( LPSTR );
HANDLE FAR PASCAL ImgXBeginWrite( LPSTR, LPBITMAPINFO, HANDLE, LPXINFO );
int FAR PASCAL 	ImgXWriteBlock( HANDLE, int, LPSTR, LPXINFO );
int FAR PASCAL 	ImgXEndWrite( HANDLE, LPXINFO );
HANDLE FAR PASCAL ImgXOptBlkCreate( LPSTR );
HANDLE FAR PASCAL ImgXOptBlkAdd( HANDLE, LPSTR, LPSTR );
int FAR PASCAL 	ImgXOptBlkGet( HANDLE, LPSTR, LPSTR );
int FAR PASCAL 	ImgXOptBlkDel( HANDLE );
int FAR PASCAL 	ImgXErrBox( HWND );
void FAR PASCAL 	ImgXErrString( LPSTR );
int FAR PASCAL 	ImgXGetStatus( void );
int FAR PASCAL		ImgXAbort( HANDLE );
HANDLE FAR PASCAL	ImgXFileDialog( HANDLE, HWND );
int FAR PASCAL 	ImgXWriteBMPBlock( HANDLE, HANDLE, HANDLE, int, LPXINFO);

LPSTR FAR PASCAL 	IMXDLget_ext(LPXINITSTRUCT);
HANDLE FAR PASCAL IMXDLbegin_write( LPSTR, LPBITMAPINFO, HANDLE, LPXINFO );
int FAR PASCAL 	IMXDLwrite_block( HANDLE, int, int, LPSTR, LPXINFO );
int FAR PASCAL 	IMXDLend_write( HANDLE, LPXINFO );
LPSTR FAR PASCAL 	IMXDLget_ver( void );

int FAR PASCAL ImgXWriteDIB( LPSTR, LPSTR, HANDLE, HANDLE, HWND, long );

