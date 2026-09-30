/////////////////////////////////////////////////////////////////////////
//   $Header:   P:/marille/clinicum/include/rev/dlg3d.hpv   1.3   02 Feb 1996 10:59:24   GERHOLD  $
//   $Log:   P:/marille/clinicum/include/rev/dlg3d.hpv  $
// 
//    Rev 1.3   02 Feb 1996 10:59:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   28 Aug 1994 11:35:06   GERHOLD
// Groesse der Caption dem Font angepasst, inline int DlgBorder()
// 
//    Rev 1.1   25 Jul 1994 08:59:28   GERHOLD
// LPDLGSTRUCT
// 
//    Rev 1.0   05 Jul 1994 15:48:50   GERHOLD
// Initial revision.
////////////////////////////////////////////////////////////////////////

#ifndef _ITSYBITS_H_
#define _ITSYBITS_H_

BOOL         WINAPI ibInit (HANDLE hInstance);     //obsolete!
DLLExport UINT _export WINAPI ibGetCaptionSize (HWND hWnd);
UINT         WINAPI ibSetCaptionSize (HWND hWnd, UINT nSize);
VOID         WINAPI ibAdjustWindowRect (HWND hWnd, LPRECT lprc);

#endif

#ifndef _RGB_H_
#define _RGB_H_
         
   // Some mildly useful macros for the standard 16 colors
   #define RGBBLACK     RGB(0,0,0)
   #define RGBRED       RGB(128,0,0)
   #define RGBGREEN     RGB(0,128,0)
   #define RGBBLUE      RGB(0,0,128)
   
   #define RGBBROWN     RGB(128,128,0)
   #define RGBMAGENTA   RGB(128,0,128)
   #define RGBCYAN      RGB(0,128,128)
   #define RGBLTGRAY    RGB(192,192,192)
   
   #define RGBGRAY      RGB(128,128,128)
   #define RGBLTRED     RGB(255,0,0)
   #define RGBLTGREEN   RGB(0,255,0)
   #define RGBLTBLUE    RGB(0,0,255)
   
   #define RGBYELLOW    RGB(255,255,0)
   #define RGBLTMAGENTA RGB(255,0,255)
   #define RGBLTCYAN    RGB(0,255,255)
   #define RGBWHITE     RGB(255,255,255)
#endif


DLLExport LRESULT _export WINAPI ibDefWindowProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) ;

////////////////////////////////////////////////////////////////////////
// End of File: itsybits.h
////////////////////////////////////////////////////////////////////////

struct Dlg3Dstruct;
typedef Dlg3Dstruct FAR* LPDLGSTRUCT;


struct Dlg3Dstruct {
  HWND    hWnd;

#ifdef CFIELD_INCLUDED
  cField FAR *cfCaption;
#else
  LPVOID cfCaption;
#endif

  LPDLGSTRUCT Next;
  };
  
