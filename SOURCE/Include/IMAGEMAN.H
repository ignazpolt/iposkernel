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
//    Copyright (c) 1991 Data Techniques, Inc.
//    All Rights Reserved
//
/////////////////////////////////////////////////////////////////////////////
//Revision-History
//  1 IMAGEMAN.H 24-May-91,14:31:06,`THK' ren to ImageMan
//  2 IMAGEMAN.H 24-May-91,15:41:24,`THK' Moved bFlag defines to imgerr.h
//  3 IMAGEMAN.H 6-Jul-91,21:39:10,`THK' Rev 1.00
//  4 IMAGEMAN.H 23-Jul-91,12:00:02,`JGD' V 1.00 Src Release
//  5 IMAGEMAN.H 24-Jul-91,12:28:16,`THK' Added prototype for ImgGetExt
//  6 IMAGEMAN.H 29-Aug-91,14:46:56,`JGD' Added IMG_FULLBITMAP define.
//  7 IMAGEMAN.H 20-Sep-91,16:22:28,`JGD' Part of Borland C++ changes
//  8 IMAGEMAN.H 27-Nov-91,14:17:10,`THK'
//       Added: ImgOpenSolo, ImgOpenEmbedded, ImgGetPalette
//  9 IMAGEMAN.H 10-Feb-92,9:25:56,`THK' Added ImgEscape Function prototype
//  10 IMAGEMAN.H 22-May-92,15:55:56,`JGD' Modified to compile w/C 7.0
//Revision-History

//Keyword-Flag   "%v %f %w %n"
// "10 22-May-92,15:55:56 JGD IMAGEMAN.H"


#define IMG_TRANSPARENT (0xffffffff)

#define IMG_GLOBAL        (-1)
#define IMG_FULLBITMAP    (-2)
#define IMG_NOBITMAP      (-3)


typedef struct tagImageInfo {
  HANDLE  hDIB;         // handle to BITMAPINFO struct for this image
  int   bFlags;       // 
  long    lOrgWid;        // width of original image
  long    lOrgHi;       // height of original image
} IMAGEINFO;

typedef IMAGEINFO FAR * LPIMAGEINFO;

// prototypes for ImageMan functions
int  FAR PASCAL ImgInit(void);
int  FAR PASCAL ImgClose(HANDLE);
int  FAR PASCAL ImgGetStatus(void);
int  FAR PASCAL ImgErrBox(HWND);
int  FAR PASCAL ImgErrString(LPSTR, int);
int  FAR PASCAL ImgVerString(LPSTR, int);
int  FAR PASCAL ImgSetTolerance(HANDLE hFile, int nTol);
int  FAR PASCAL ImgGetTolerance(HANDLE hFile);
int  FAR PASCAL ImgSetROP(DWORD);
int  FAR PASCAL ImgDrawImage(HANDLE, HDC, LPRECT, LPRECT);
int  FAR PASCAL ImgPrintImage(HANDLE, HDC, LPRECT, LPRECT);
int  FAR PASCAL ImgEscape(HANDLE, int, int, LPVOID, LPVOID);

DWORD    FAR PASCAL ImgGetROP(void);
HANDLE   FAR PASCAL ImgGetInfo(HANDLE);
HANDLE   FAR PASCAL ImgGetExt(void);
HANDLE   FAR PASCAL ImgExt(void);
HANDLE   FAR PASCAL ImgOpen(LPSTR, int, long, LPSTR);
HANDLE   FAR PASCAL ImgGetDIB(HANDLE, LPRECT);
HANDLE   FAR PASCAL ImgGetDIBBuf(HANDLE hFile, LPRECT lpSrc, LPSTR lpBits);
HANDLE   FAR PASCAL ImgGethDIB( HANDLE hFile, LPRECT lpSrc);
HANDLE   FAR PASCAL ImgOpenSolo(LPSTR, LPSTR);
HANDLE   FAR PASCAL ImgOpenEmbedded(int, long, long, LPSTR);
HANDLE   FAR PASCAL ImgGetPalette(HANDLE);

