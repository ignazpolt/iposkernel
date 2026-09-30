/*             
   LTSCR.H - screen capture header file
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _L_LTSCR_H_
#define _L_LTSCR_H_

/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/

#define _HEADER_ENTRY_
#include "ltpck.h"

/*----------------------------------------------------------------------------+
| ENUMS                                                                       |
+----------------------------------------------------------------------------*/
typedef enum tagRESTYPEENUM
{
   CAPTURE_ICON=1,
   CAPTURE_BITMAP,
   CAPTURE_CURSOR
}  RESTYPEENUM;

//-----------------------------------------------------------------------------
typedef enum tagAREATYPEENUM
{
   CAPTURE_AREA_TRIANGLE=1,
   CAPTURE_AREA_RECT,
   CAPTURE_AREA_ROUNDRECT,
   CAPTURE_AREA_ELLIPSE,
   CAPTURE_AREA_POLYGON,
   CAPTURE_AREA_FREEHAND
}  AREATYPEENUM;

//-----------------------------------------------------------------------------
// Window-Client Capture Options
typedef enum tagWINDOWCAPTURETYPE
{
   CAPTURE_CLIENT_AREA=1,
   CAPTURE_WINDOW,
}  WINDOWCAPTURETYPE;


/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/
#define         SCOD_MIN_TIME                0
#define         SCOD_MAX_TIME                60
#define         SCOD_MAX_REPEAT              120
#define         SCOD_MIN_REPEAT              0

/****************************************************************************
   Capture From EXE Flags
*****************************************************************************/
// flags for L_CaptureFromExe (Types of resources)
#define RESTYPE_BITMAP                    0x001          // Bitmap
#define RESTYPE_ICON                      0x002          // Icon
#define RESTYPE_CURSOR                    0x004          // Cursor

// flags for L_CaptureFromExeDlg (Dialog Type - nDialogType)
#define LTCAPDLG_TABVIEW                  0x000          // Tab View Dialog
#define LTCAPDLG_TREEVIEW                 0x001          // Tree View Dialog

#define MAKEINDEX(x)          MAKEINTRESOURCE(x)
#define MAKERESOURCEID(x)     MAKEINTRESOURCE(x)
/****************************************************************************
   Capture Area Flags
*****************************************************************************/
// Optional Cursor for L_CaptureArea (LEADCAPTUREAREAOPTION.hDrawCursor)
#define CAPTURE_AREA_CROSSLINES_CURSOR    -1

//   flags for L_CaptureArea - Area Fill Pattern
#define CAPTURE_AREA_PATTERN_HORIZONTAL   HS_HORIZONTAL  /* ----- */
#define CAPTURE_AREA_PATTERN_VERTICAL     HS_VERTICAL    /* ||||| */
#define CAPTURE_AREA_PATTERN_FDIAGONAL    HS_FDIAGONAL   /* \\\\\ */
#define CAPTURE_AREA_PATTERN_BDIAGONAL    HS_BDIAGONAL   /* ///// */
#define CAPTURE_AREA_PATTERN_CROSS        HS_CROSS       /* +++++ */
#define CAPTURE_AREA_PATTERN_DIAGCROSS    HS_DIAGCROSS   /* xxxxx */
#define CAPTURE_AREA_PATTERN_SOLID        HS_DIAGCROSS+1 /*Solid Fill*/

// Flags for L_Capture Area - Area Line Style
#define CAPTURE_AREA_LINE_SOLID           PS_SOLID       // __________
#define CAPTURE_AREA_LINE_DASH            PS_DASH        // ----------
#define CAPTURE_AREA_LINE_DOT             PS_DOT         // ..........
#define CAPTURE_AREA_LINE_DASHDOT         PS_DASHDOT     // -.-.-.-.-.
#define CAPTURE_AREA_LINE_DASHDOTDOT      PS_DASHDOTDOT  // -..-..-..-

// Flags for L_CaptureArea = Capture Area Info Window Optional Size
#define CAPTURE_AREA_INFOWND_SIZE_TINY    -1
#define CAPTURE_AREA_INFOWND_SIZE_SMALL   -2
#define CAPTURE_AREA_INFOWND_SIZE_MEDIUM  -3
#define CAPTURE_AREA_INFOWND_SIZE_LARGE   -4
#define CAPTURE_AREA_INFOWND_SIZE_XLARGE  -5

// Flags for L_CaptureArea - Capture Area Info Window Optional Position

// flags for L_Capture Area - X position of Info window -  LEADCAPTUREAREAOPTION.nInfoLeft
#define CAPTURE_AREA_INFOWND_POS_LEFT     -1
#define CAPTURE_AREA_INFOWND_POS_RIGHT    -2

// flags for L_Capture Area - Y position of Info window - LEADCAPTUREAREAOPTION.nInfoTop
#define CAPTURE_AREA_INFOWND_POS_TOP      -3
#define CAPTURE_AREA_INFOWND_POS_BOTTOM   -4

// flags for L_CaptureArea - LEADCAPTUREAREAOPTION.uFlags
#define CAPTURE_AREA_SHOW_DRAWCURSOR      0x0001            // To display cursor during capture
#define CAPTURE_AREA_INCLUDE_CURSOR       0x0002            /// Include the cursor in the captured image
#define CAPTURE_AREA_ENABLE_KEYBOARD      0x0004            // Allow Ctrl/Shift/+/- keys during capture 
                                                            // (+/-)  for Zooming In/Out
                                                            // (Ctrl) if Area is Rect/RoundRect/Ellipse
                                                            // pressing CTRL will center the drawing
                                                            // (Shift) if Area is Rect/RoundRect/Ellipse
                                                            // pressing SHIFT will draw reqular shapes (Ellipse -> circle, Rectangle ->Square)
#define CAPTURE_AREA_SHOW_OPAQUE_TEXT     0x0008            // Displays cursor position, Width, Height during capture on OPAQUE BACKGROUND

#define CAPTURE_AREA_SHOW_CURSORPOS       0x0010            // Show Mouse Position
#define CAPTURE_AREA_SHOW_CAPTURESIZE     0x0020            // Show captured area size
#define CAPTURE_AREA_SHOW_INFOWINDOW      0x0040            // Show Info Dialog
#define CAPTURE_AREA_SENSITIVE_INFOWINDOW 0x0080            // Enable Sensitive detection for info window position

#define CAPTURE_AREA_BITMAP_WITH_REGION   0x0100            // the captured bitmap will contain a region of the specified Area shape as selected by user
#define CAPTURE_AREA_USE_DEFAULT_VALUES   0x0200            // to use default values for the rest of area options(at least the user must fill in uSize & uAreaType & set this flag)

// zooming factors (exclusive)
#define CAPTURE_AREA_ZOOM_NORM            0x1000
#define CAPTURE_AREA_ZOOM_BY2X            0x2000
#define CAPTURE_AREA_ZOOM_BY3X            0x3000
#define CAPTURE_AREA_ZOOM_BY4X            0x4000
#define CAPTURE_AREA_ZOOM_BY5X            0x5000
#define CAPTURE_AREA_ZOOM_BY6X            0x6000
#define CAPTURE_AREA_ZOOM_BY7X            0x7000
#define CAPTURE_AREA_ZOOM_BY8X            0x8000
#define CAPTURE_AREA_ZOOM_BY9X            0x9000
#define CAPTURE_AREA_ZOOM_BY10X           0xA000
#define CAPTURE_AREA_ZOOM_BY11X           0xB000
#define CAPTURE_AREA_ZOOM_BY12X           0xC000
#define CAPTURE_AREA_ZOOM_BY13X           0xD000
#define CAPTURE_AREA_ZOOM_BY14X           0xE000
#define CAPTURE_AREA_ZOOM_BY15X           0xF000

/****************************************************************************
   Capture Object Flags
*****************************************************************************/
// flags for L_CaptureSelectedObject
#define CAPTURE_OBJECT_INVERT             0x0001
#define CAPTURE_OBJECT_ENABLE_KEYBOARD    0x0002

/*----------------------------------------------------------------------------+
| TYPEDEFS                                                                    |
+----------------------------------------------------------------------------*/
/*
   LEADCAPTUREOPTION structure
*/
typedef struct tagLEADCAPTUREOPTION
{
   HCURSOR     hCursor;
   HCURSOR     hStatusCursor;
   L_INT       nHotKey;
   L_UINT      uHotKeyModifiers; //a combination of MOD_ALT, MOD_CONTROL and MOD_SHIFT
   L_INT       nCancelKey; 
   L_INT       nDelay;
   L_UINT      uCount;
   L_INT       nInterval;
}  LEADCAPTUREOPTION,L_FAR* pLEADCAPTUREOPTION;

/*
   LEADCAPTUREINFO structure
*/
typedef struct tagLEADCAPTUREINFO
{
   HWND        hWnd;
   RECT        rcArea;
   L_INT       nResType;
   L_INT       nIndex;
   LPSTR       pszResID;
   L_CHAR      szReserved[256];
   LPSTR       pszExeName;
   L_INT       nMaxExeName;
}  LEADCAPTUREINFO,L_FAR* pLEADCAPTUREINFO;

/*
   LEADCAPTUREAREAOPTION structure
*/
typedef struct tagLEADCAPTUREAREAOPTION
{
   L_UINT   uSize;            /* size of the structure */
   L_UINT   uAreaType;        /* type of area to capture */
   L_INT    nFillPattern;     /* fill pattern for the bitmap */
   COLORREF crFillForeColor;  /* foreground color */
   COLORREF crFillBackColor;  /* background color */
   L_UINT   uDrawLineStyle;   /* draw line style */
   COLORREF crDrawLineColor;  /* line color for drawing */
   L_UINT   uEllipseWidth;    /* Ellipse width */
   L_UINT   uEllipseHeight;   /* Ellipse height */
   L_UINT   uFlags;           /* flags for options */
   HCURSOR  hDrawCursor;      /* cursor for drawing area */
   COLORREF crTextForeColor;  /* foreground color of info text */
   COLORREF crTextBackColor;  /* background color of info text */
   L_INT    nInfoLeft;        /*left corner for info window*/
   L_INT    nInfoTop;         /*top corner for info window*/
   L_INT    nInfoWidth;       /*width of info window*/
   L_INT    nInfoHeight;      /*height of info window*/
}  LEADCAPTUREAREAOPTION,L_FAR* pLEADCAPTUREAREAOPTION;

/*
   CAPTUROBJECTOPTIONS structure
*/
typedef struct tagLEADCAPTUREOBJECTOPTION
{                      
   L_UINT      uFlags;
   L_UINT      uBorderWidth;
   HCURSOR     hSelectCursor;
}  LEADCAPTUREOBJECTOPTION,L_FAR* pLEADCAPTUREOBJECTOPTION;


/*----------------------------------------------------------------------------+
| Callback definitions                                                        |
+----------------------------------------------------------------------------*/
// Capture Callback
typedef L_INT (pEXT_CALLBACK CAPTURECALLBACK)
              (pBITMAPHANDLE, pLEADCAPTUREINFO, L_VOID L_FAR*);

// Hotkey Callback
typedef L_INT (pEXT_CALLBACK CAPTUREHOTKEYCALLBACK) 
               (L_INT, L_UINT, L_VOID L_FAR*);

/*----------------------------------------------------------------------------+
| FUNCTIONS PROTOTYPES                                                        |
+----------------------------------------------------------------------------*/
L_INT EXT_FUNCTION L_SetCaptureOption(pLEADCAPTUREOPTION pOptions);
L_INT EXT_FUNCTION L_GetCaptureOption(pLEADCAPTUREOPTION pOptions);

L_INT EXT_FUNCTION L_CaptureWindow(pBITMAPHANDLE pBitmap, HWND hWnd, WINDOWCAPTURETYPE wctCaptureType,pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureActiveWindow(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureActiveClient(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_CaptureWallPaper(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureFullScreen(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureMenuUnderCursor(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureWindowUnderCursor(pBITMAPHANDLE pBitmap, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_CaptureSelectedObject(pBITMAPHANDLE pBitmap,pLEADCAPTUREOBJECTOPTION pObjectOptions,pLEADCAPTUREINFO pCaptureInfo,CAPTURECALLBACK pfnCaptureCallback,L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureArea(pBITMAPHANDLE pBitmap,pLEADCAPTUREAREAOPTION pCaptureAreaOption, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_CaptureMouseCursor(pBITMAPHANDLE pBitmap, COLORREF crFill, pLEADCAPTUREINFO pCaptureInfo, CAPTURECALLBACK pfnCaptureCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_CaptureSetHotKeyCallback(CAPTUREHOTKEYCALLBACK pfnCaptureHotKeyCB, L_VOID L_FAR* pUserData);


L_INT EXT_FUNCTION L_SetCaptureOptionDlg(HWND hwndOwner, pLEADCAPTUREOPTION pOptions);
L_INT EXT_FUNCTION L_CaptureAreaOptionDlg(HWND hParentWnd,pLEADCAPTUREAREAOPTION pCaptureAreaOption,L_INT nUseDefault);
L_INT EXT_FUNCTION L_CaptureObjectOptionDlg(HWND hParentWnd,pLEADCAPTUREOBJECTOPTION pObjectOptions,L_INT nUseDefault);

L_INT EXT_FUNCTION L_GetDefaultAreaOption(pLEADCAPTUREAREAOPTION pCaptureAreaOption);
L_INT EXT_FUNCTION L_GetDefaultObjectOption(pLEADCAPTUREOBJECTOPTION pObjectOptions);
L_INT EXT_FUNCTION L_StopCapture();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                          C A P T U R E       E X E       F U N C T I O N S
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
L_INT EXT_FUNCTION L_CaptureFromExeDlg
(
   pBITMAPHANDLE pBitmap,                 //Pointer to LEAD Bitmap Object to be filled on return
   L_CHAR L_FAR* pszFileName,             //.EXE or .DLL Full Path and Name to read resources from
   LPCOLORREF pTransparentColor,          //Background color to be used inplace of transparent 
                                          //color of Icons/Cursors
   L_INT nResType,                        // resource type(s) to capture                                        
   L_INT nDialogType,                     //Type of dialog ( Either LTCAPDLG_TABVIEW or LTCAPDLG_TREEVIEW)
   pLEADCAPTUREINFO pCaptureInfo,         //Captured info. On return the resource type and ID are
                                          //filled.
   CAPTURECALLBACK pfnCaptureCallback,    //Callback function for user-special purposes
   L_VOID L_FAR* pUserData                //User-supplied data to be passed to the callback
);

L_INT EXT_FUNCTION L_CaptureFromExe
(
   pBITMAPHANDLE pBitmap,                 //Pointer to LEAD Bitmap Object to be filled on return
   L_CHAR L_FAR* pszFileName,             //.EXE or .DLL Full Path and Name to read resources from
   L_INT nResType,                        //Resource type (RESTYPE_BITMAP, RESTYPE_ICON or 
                                          //RESTYPE_CURSOR
   L_CHAR L_FAR * pResID,                 //Resoruce ID to be captured
   L_BOOL bCaptureByIndex,                 //TRUE indicates that pResID is the index position of the
                                          //requested resource
                                          //FALSE indicates that pResID is the resource ID of the 
                                          //requested resource
   COLORREF clrBackGnd,                   //Background color to be used inplace of transparent 
                                          //color for icons
   CAPTURECALLBACK pfnCaptureCallback,    //Callback function for user-special purposes
   L_VOID L_FAR* pUserData                //User-supplied data to be passed to the callback
);

L_INT EXT_FUNCTION L_CaptureGetResCount
(
   L_CHAR L_FAR * pszFileName,            //Full path to .EXE/.DLL to count resource for
   L_INT nResType,                        //Resource type, RESTYPE_BITMAP,RESTYPE_ICON or
                                          //RESTYPE_CURSOR
   L_INT32 L_FAR* pnCount                 //Pointer to long integer to hold the count
);


L_BOOL EXT_FUNCTION L_IsCaptureActive();

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif         /* _LTSCR_H_ */

/*================================================================== EOF ====*/
