/*
   LTANN.H - annotation module header file
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTANN_H_
#define _LTANN_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   object types
*/
#define ANNOBJECT_CONTAINER      0
#define ANNOBJECT_POINTER        1
#define ANNOBJECT_AUDIO          2
#define ANNOBJECT_BUTTON         3
#define ANNOBJECT_ELLIPSE        4
#define ANNOBJECT_FREEHAND       5
#define ANNOBJECT_HILITE         6
#define ANNOBJECT_HOTSPOT        7
#define ANNOBJECT_LINE           8
#define ANNOBJECT_NOTE           9
#define ANNOBJECT_POLYGON        10
#define ANNOBJECT_POLYLINE       11
#define ANNOBJECT_RECT           12
#define ANNOBJECT_REDACT         13
#define ANNOBJECT_STAMP          14
#define ANNOBJECT_TEXT           15
#define ANNOBJECT_AUTOMATION     16
#define ANNOBJECT_RULER          17

/*
   automation text items
*/
enum {
/*
   automation menu text
*/
   ANNAUTOTEXT_MENU_UNDO,
   ANNAUTOTEXT_MENU_CUT,
   ANNAUTOTEXT_MENU_COPY,
   ANNAUTOTEXT_MENU_PASTE,
   ANNAUTOTEXT_MENU_DELETE,
   ANNAUTOTEXT_MENU_SELECTALL,
   ANNAUTOTEXT_MENU_BRINGTOFRONT,
   ANNAUTOTEXT_MENU_SENDTOBACK,
   ANNAUTOTEXT_MENU_DEFAULTPROPERTIES,
   ANNAUTOTEXT_MENU_SELECTEDPROPERTIES,
   ANNAUTOTEXT_MENU_CONTAINERPROPERTIES,
   ANNAUTOTEXT_MENU_POINTERPROPERTIES,
   ANNAUTOTEXT_MENU_AUDIOPROPERTIES,
   ANNAUTOTEXT_MENU_BUTTONPROPERTIES,
   ANNAUTOTEXT_MENU_ELLIPSEPROPERTIES,
   ANNAUTOTEXT_MENU_FREEHANDPROPERTIES,
   ANNAUTOTEXT_MENU_HILITEPROPERTIES,
   ANNAUTOTEXT_MENU_HOTSPOTPROPERTIES,
   ANNAUTOTEXT_MENU_LINEPROPERTIES,
   ANNAUTOTEXT_MENU_NOTEPROPERTIES,
   ANNAUTOTEXT_MENU_POLYGONPROPERTIES,
   ANNAUTOTEXT_MENU_POLYLINEPROPERTIES,
   ANNAUTOTEXT_MENU_RECTANGLEPROPERTIES,
   ANNAUTOTEXT_MENU_REDACTPROPERTIES,
   ANNAUTOTEXT_MENU_STAMPPROPERTIES,
   ANNAUTOTEXT_MENU_TEXTPROPERTIES,
   ANNAUTOTEXT_MENU_AUTOMATIONPROPERTIES,
   ANNAUTOTEXT_MENU_RULERPROPERTIES,
   ANNAUTOTEXT_MENU_LINE,
   ANNAUTOTEXT_MENU_FILL,
   ANNAUTOTEXT_MENU_FOREGROUNDCOLOR,
   ANNAUTOTEXT_MENU_BACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_FONT,
   ANNAUTOTEXT_MENU_BITMAP,
   ANNAUTOTEXT_MENU_TEXT,
   ANNAUTOTEXT_MENU_FILE,
   ANNAUTOTEXT_MENU_ROP2,
   ANNAUTOTEXT_MENU_TRANSPARENT,
   ANNAUTOTEXT_MENU_LOCK,
   ANNAUTOTEXT_MENU_UNLOCK,
   ANNAUTOTEXT_MENU_LOCKALL,
   ANNAUTOTEXT_MENU_UNLOCKALL,
   ANNAUTOTEXT_MENU_HYPERLINK,
   ANNAUTOTEXT_MENU_NOTEBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_REDACTBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_HILITEBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_RULER,

/*
   automation line dialog text
*/
   ANNAUTOTEXT_LINE_CAPTION,
   ANNAUTOTEXT_LINE_WIDTH,
   ANNAUTOTEXT_LINE_STYLE,
   ANNAUTOTEXT_LINE_OK,
   ANNAUTOTEXT_LINE_CANCEL,

   ANNAUTOTEXT_LINE_SOLID,
   ANNAUTOTEXT_LINE_DASH,
   ANNAUTOTEXT_LINE_DOT,
   ANNAUTOTEXT_LINE_DASHDOT,
   ANNAUTOTEXT_LINE_DASHDOTDOT,
   ANNAUTOTEXT_LINE_NULL,

/*
   automation fill dialog text
*/
   ANNAUTOTEXT_FILL_CAPTION,
   ANNAUTOTEXT_FILL_MODE,
   ANNAUTOTEXT_FILL_PATTERNS,
   ANNAUTOTEXT_FILL_POLYGON,
   ANNAUTOTEXT_FILL_OK,
   ANNAUTOTEXT_FILL_CANCEL,

   ANNAUTOTEXT_FILL_TRANSPARENT,
   ANNAUTOTEXT_FILL_TRANSLUCENT,
   ANNAUTOTEXT_FILL_OPAQUE,

   ANNAUTOTEXT_FILL_SOLID,
   ANNAUTOTEXT_FILL_BACKWARDDIAGONAL,
   ANNAUTOTEXT_FILL_CROSS,
   ANNAUTOTEXT_FILL_DIAGONALCROSS,
   ANNAUTOTEXT_FILL_FORWARDDIAGONAL,
   ANNAUTOTEXT_FILL_HORIZONTAL,
   ANNAUTOTEXT_FILL_VERTICAL,

   ANNAUTOTEXT_FILL_WINDING,
   ANNAUTOTEXT_FILL_ALTERNATE,

/*
   automation text dialog text
*/
   ANNAUTOTEXT_TEXT_CAPTION,
   ANNAUTOTEXT_TEXT_OK,
   ANNAUTOTEXT_TEXT_CANCEL,

/*
   automation audio file dialog text
*/
   ANNAUTOTEXT_AUDIOFILE_CAPTION,
   ANNAUTOTEXT_AUDIOFILE_FILTER,

/*
   automation stamp file dialog text
*/
   ANNAUTOTEXT_STAMPFILE_CAPTION,
   ANNAUTOTEXT_STAMPFILE_FILTER,

/*
   automation default item text
*/
   ANNAUTOTEXT_ITEM_DEFAULTTEXT,

/*
   automation ROP2 dialog text
*/
   ANNAUTOTEXT_ROP2_CAPTION,
   ANNAUTOTEXT_ROP2_TEXT,
   ANNAUTOTEXT_ROP2_OK,
   ANNAUTOTEXT_ROP2_CANCEL,
   ANNAUTOTEXT_ROP2_COPY,
   ANNAUTOTEXT_ROP2_AND,
   ANNAUTOTEXT_ROP2_XOR,

/*
   automation Lock dialog text
*/
   ANNAUTOTEXT_LOCK_CAPTION,
   ANNAUTOTEXT_LOCK_TEXT,
   ANNAUTOTEXT_LOCK_OK,
   ANNAUTOTEXT_LOCK_CANCEL ,

/*
   automation Unlock dialog text
*/
   ANNAUTOTEXT_UNLOCK_CAPTION,
   ANNAUTOTEXT_UNLOCK_TEXT,
   ANNAUTOTEXT_UNLOCK_OK,
   ANNAUTOTEXT_UNLOCK_CANCEL,

/*
   automation Ruler dialog text
*/
   ANNAUTOTEXT_RULER_CAPTION,
   ANNAUTOTEXT_RULER_UNITS,
   ANNAUTOTEXT_RULER_ABBREV,
   ANNAUTOTEXT_RULER_PRECISION,
   ANNAUTOTEXT_RULER_LENGTH,
   ANNAUTOTEXT_RULER_OK,
   ANNAUTOTEXT_RULER_CANCEL,

   ANNAUTOTEXT_RULER_INCHES,
   ANNAUTOTEXT_RULER_FEET,
   ANNAUTOTEXT_RULER_YARDS,
   ANNAUTOTEXT_RULER_MICROMETERS,
   ANNAUTOTEXT_RULER_MILIMETERS,
   ANNAUTOTEXT_RULER_CENTIMETERS,
   ANNAUTOTEXT_RULER_METERS,
   ANNAUTOTEXT_RULER_TWIPS,
   ANNAUTOTEXT_RULER_POINTS,
   ANNAUTOTEXT_RULER_PIXELS,

   ANNAUTOTEXT_MAX,
};

/*
   data structures
*/
typedef struct _ANNPOINT
{
   L_DOUBLE x;
   L_DOUBLE y;
} ANNPOINT, L_FAR *pANNPOINT;

typedef struct _ANNRECT
{
   L_DOUBLE left;
   L_DOUBLE top;
   L_DOUBLE right;
   L_DOUBLE bottom;
} ANNRECT, L_FAR *pANNRECT;

/*
   save/clipboard formats
*/
#define ANNFMT_NATIVE   0
#define ANNFMT_WMF      1
#define ANNFMT_TIFFTAG  2     /* Save all Lead info */
#define ANNFMT_WANGTAG  3     /* Wang annotation compatibility mode */

/*
   Value of the Annotation Tag
*/
#define ANNTAG_TIFF           32932

/*
   toolbar buttons
*/
#define ANNTOOL_SELECT         0
#define ANNTOOL_LINE           1
#define ANNTOOL_RECT           2
#define ANNTOOL_ELLIPSE        3
#define ANNTOOL_POLYLINE       4
#define ANNTOOL_POLYGON        5
#define ANNTOOL_POINTER        6
#define ANNTOOL_FREEHAND       7
#define ANNTOOL_HILITE         8
#define ANNTOOL_REDACT         9
#define ANNTOOL_TEXT           10
#define ANNTOOL_NOTE           11
#define ANNTOOL_STAMP          12
#define ANNTOOL_BUTTON         13
#define ANNTOOL_HOTSPOT        14
#define ANNTOOL_AUDIO          15
#define ANNTOOL_RULER          16

/*
   messages
*/
#define WM_LTANNEVENT      (WM_USER + 512)
#define WM_LTANNHYPERLINK  (WM_USER + 513)   // message used internally by LEADTOOLS ActiveX

/*
   wParam = event id
   lParam = specific event data
*/
#define LTANNEVENT_TOOLCHECKED   0
#define LTANNEVENT_TOOLCREATE    1
#define LTANNEVENT_TOOLDESTROY   2
#define LTANNEVENT_ACTIVATE      3
#define LTANNEVENT_DEACTIVATE    4
#define LTANNEVENT_INSERT        5
#define LTANNEVENT_REMOVE        6
#define LTANNEVENT_AUTOBEGINSET  7
#define LTANNEVENT_AUTOENDSET    8
#define LTANNEVENT_AUTOCLICKED   9
#define LTANNEVENT_AUTOCHANGED   10
#define LTANNEVENT_AUTOITEMCHANGED  11
#define LTANNEVENT_AUTOSELECT    12
#define LTANNEVENT_LOCKED        13
#define LTANNEVENT_UNLOCKED      14
#define LTANNEVENT_HYPERLINK     15
#define LTANNEVENT_HYPERLINKMENU 16

#ifndef HANDLE_MSG
#define HANDLE_MSG(hwnd, message, fn)    \
    case (message): return HANDLE_##message((hwnd), (wParam), (lParam), (fn))
#endif

/* LRESULT Cls_OnLtAnnEvent(HWND hwnd, int id, LPARAM lParam); */
#define HANDLE_WM_LTANNEVENT(hwnd, wParam, lParam, fn) \
      (LRESULT)(DWORD)(fn)(hwnd, (int) wParam, lParam)
#define FORWARD_WM_LTANNEVENT(hwnd, id, lParam, fn) \
    (LRESULT)(DWORD)(fn)((hwnd), WM_LTANNEVENT, (int) (id), (LPARAM) (lParam))

/*
   line styles
*/
#define ANNLINE_SOLID         0
#define ANNLINE_DASH          1
#define ANNLINE_DOT           2
#define ANNLINE_DASHDOT       3
#define ANNLINE_DASHDOTDOT    4
#define ANNLINE_NULL          5

/*
   fill patterns
*/
#define ANNPATTERN_SOLID         0
#define ANNPATTERN_BDIAGONAL     1
#define ANNPATTERN_CROSS         2
#define ANNPATTERN_DIAGCROSS     3
#define ANNPATTERN_FDIAGONAL     4
#define ANNPATTERN_HORIZONTAL    5
#define ANNPATTERN_VERTICAL      6

/*
   fill mode
*/
#define ANNMODE_TRANSPARENT   0
#define ANNMODE_TRANSLUCENT   1
#define ANNMODE_OPAQUE        2

/*
   poly fill mode
*/
#define ANNPOLYFILL_WINDING   0
#define ANNPOLYFILL_ALTERNATE 1

/*
   define states
*/
#define ANNDEFINE_BEGINSET    0
#define ANNDEFINE_BEGINMOVE   1
#define ANNDEFINE_BEGINROTATE 2
#define ANNDEFINE_BEGINRESIZE 3
#define ANNDEFINE_BEGINSELECT 4
#define ANNDEFINE_APPEND      5
#define ANNDEFINE_UPDATE      6
#define ANNDEFINE_END         7
#define ANNDEFINE_BEGINMOVESELECTED    8
#define ANNDEFINE_BEGINROTATESELECTED  9
#define ANNDEFINE_BEGINRESIZESELECTED  10
#define ANNDEFINE_BEGINMOVEPOINT       11

/*
   active states
*/
#define ANNACTIVE_DISABLED    0
#define ANNACTIVE_ENABLED     1

/*
   hittest results
*/
#define ANNHIT_NONE           0
#define ANNHIT_BODY           1
#define ANNHIT_HANDLE         2

/*
   user modes
*/
#define ANNUSER_DESIGN        0
#define ANNUSER_RUN           1

/*
   flags for set functions
*/
#define ANNFLAG_SELECTED       0x0001
#define ANNFLAG_NOTCONTAINER   0x0002
#define ANNFLAG_NOTTHIS        0x0004
#define ANNFLAG_RECURSE        0x0008
#define ANNFLAG_NOINVALIDATE   0x0010

/*
   toolbar create alignment
*/
#define ANNTOOLALIGN_LEFT     0x0000
#define ANNTOOLALIGN_RIGHT    0x0001
#define ANNTOOLALIGN_TOP      0x0000
#define ANNTOOLALIGN_BOTTOM   0x0002

/*
   ROP2 values
*/
#define ANNROP2_COPY          0
#define ANNROP2_AND           1
#define ANNROP2_XOR           2

/*
   Hyperlink types
*/
#define ANNLINK_NONE          0
#define ANNLINK_LTANNEVENT    1
#define ANNLINK_USERMSG       2
#define ANNLINK_RUN           3
#define ANNLINK_WEBPAGE       4

/*
   Distance units
*/
#define ANNUNIT_INCHES        0
#define ANNUNIT_FEET          1
#define ANNUNIT_YARDS         2
#define ANNUNIT_MICROMETERS   3
#define ANNUNIT_MILIMETERS    4
#define ANNUNIT_CENTIMETERS   5
#define ANNUNIT_METERS        6
#define ANNUNIT_TWIPS         7
#define ANNUNIT_POINTS        8
#define ANNUNIT_PIXELS        9

/*
   object handle
*/
typedef HANDLE HANNOBJECT;
typedef HANNOBJECT L_FAR *pHANNOBJECT;
/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK ANNENUMCALLBACK) (HANNOBJECT hObject, L_VOID L_FAR * pUserData);
/*
   function prototypes
*/

L_INT EXT_FUNCTION L_AnnBringToFront (HANNOBJECT hObject);

L_INT EXT_FUNCTION L_AnnClipboardReady(L_BOOL L_FAR *pfReady);

L_INT EXT_FUNCTION L_AnnCopy(HANNOBJECT hSource,
                                 pHANNOBJECT phDest);

L_INT EXT_FUNCTION L_AnnCopyFromClipboard(HWND hWnd,
                                          pHANNOBJECT phContainer);

L_INT EXT_FUNCTION L_AnnCopyToClipboard(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty);

L_INT EXT_FUNCTION L_AnnCutToClipboard(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty);


L_INT EXT_FUNCTION L_AnnCreate (L_UINT uObjectType,
                                 pHANNOBJECT phObject);

L_INT EXT_FUNCTION L_AnnCreateContainer (HWND hWnd,
                                          pANNRECT pRect,
                                          L_BOOL fVisible,
                                          pHANNOBJECT phObject);
L_INT EXT_FUNCTION L_AnnCreateItem (HANNOBJECT hContainer,
                                     L_UINT uObjectType,
                                     L_BOOL fVisible,
                                     pHANNOBJECT phObject);

L_INT EXT_FUNCTION L_AnnCreateToolBar(HWND hwndParent,
                                      LPPOINT pPoint,
                                      L_UINT uAlign,
                                      L_BOOL fVisible,
                                      HWND L_FAR *phWnd);

L_INT EXT_FUNCTION L_AnnDefine (HANNOBJECT hObject,
                                 LPPOINT pPoint,
                                 L_UINT uState);

L_INT EXT_FUNCTION L_AnnDestroy (HANNOBJECT hObject,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnDraw (HDC hDC,
                               LPRECT prcInvalid,
                               HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnEnumerate (HANNOBJECT hObject,
                                    ANNENUMCALLBACK pfnCallback,
                                    L_VOID L_FAR * pUserData,
                                    L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnFlip(HANNOBJECT hObject,
                                    pANNPOINT pCenter,
                                    L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetActiveState (HANNOBJECT hObject,
                                         L_UINT L_FAR * puState);
L_INT EXT_FUNCTION L_AnnGetAutoContainer (HANNOBJECT hObject,
                                          HANNOBJECT L_FAR * phContainer);

L_INT EXT_FUNCTION L_AnnGetAutoDrawEnable (HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);

L_INT EXT_FUNCTION L_AnnGetAutoMenuEnable (HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);

L_INT EXT_FUNCTION L_AnnGetAutoText (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_CHAR L_FAR *pText);

L_INT EXT_FUNCTION L_AnnGetAutoTextLen (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_UINT L_FAR * puLen);

L_INT EXT_FUNCTION L_AnnGetBackColor (HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrBack);
L_INT EXT_FUNCTION L_AnnGetBitmap (HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap);
L_INT EXT_FUNCTION L_AnnGetBoundingRect (HANNOBJECT hObject,
                                    LPRECT pRect);
L_INT EXT_FUNCTION L_AnnGetContainer (HANNOBJECT hObject,
                                       pHANNOBJECT phContainer);
L_INT EXT_FUNCTION L_AnnGetDpiX (HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiX);
L_INT EXT_FUNCTION L_AnnGetDpiY (HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiY);
L_INT EXT_FUNCTION L_AnnGetFillMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puFillMode);
L_INT EXT_FUNCTION L_AnnGetFillPattern (HANNOBJECT hObject,
                                         L_UINT L_FAR * puFillPattern);
L_INT EXT_FUNCTION L_AnnGetFontBold (HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfFontBold);
L_INT EXT_FUNCTION L_AnnGetFontItalic (HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontItalic);
L_INT EXT_FUNCTION L_AnnGetFontName (HANNOBJECT hObject,
                                      L_CHAR L_FAR * pFontName);
L_INT EXT_FUNCTION L_AnnGetFontNameLen (HANNOBJECT hObject,
                                         L_UINT L_FAR * puLen);
L_INT EXT_FUNCTION L_AnnGetFontSize (HANNOBJECT hObject,
                                      L_DOUBLE L_FAR * pdFontSize);
L_INT EXT_FUNCTION L_AnnGetFontStrikeThrough (HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontStrikeThrough);
L_INT EXT_FUNCTION L_AnnGetFontUnderline (HANNOBJECT hObject,
                                           L_BOOL L_FAR * pfFontUnderline);
L_INT EXT_FUNCTION L_AnnGetForeColor (HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrFore);
L_INT EXT_FUNCTION L_AnnGetHyperlink (HANNOBJECT hObject,
                                       L_UINT L_FAR*puType,
                                       L_UINT L_FAR*puMsg,
                                       WPARAM L_FAR*pwParam,
                                       L_CHAR L_FAR*pLink);
L_INT EXT_FUNCTION L_AnnGetHyperlinkLen (HANNOBJECT hObject,
                                       L_UINT L_FAR*puLen);
L_INT EXT_FUNCTION L_AnnGetHyperlinkMenuEnable(HANNOBJECT hObject,
                              L_BOOL L_FAR*pfEnable);
L_INT EXT_FUNCTION L_AnnGetLineStyle (HANNOBJECT hObject,
                                       L_UINT L_FAR * puLineStyle);
L_INT EXT_FUNCTION L_AnnGetLineWidth (HANNOBJECT hObject,
                                       L_DOUBLE L_FAR * pdLineWidth);
L_INT EXT_FUNCTION L_AnnGetLocked (HANNOBJECT hObject, 
                                   L_BOOL L_FAR * pfLocked);
L_INT EXT_FUNCTION L_AnnGetOffsetX (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetX);
L_INT EXT_FUNCTION L_AnnGetOffsetY (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetY);
L_INT EXT_FUNCTION L_AnnGetPointCount (HANNOBJECT hObject,
                                     L_UINT L_FAR *puCount);
L_INT EXT_FUNCTION L_AnnGetPoints (HANNOBJECT hObject,
                                     pANNPOINT pPoints);
L_INT EXT_FUNCTION L_AnnGetPolyFillMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puPolyFillMode);
L_INT EXT_FUNCTION L_AnnGetRect (HANNOBJECT hObject,
                                  pANNRECT pRect);
L_INT EXT_FUNCTION L_AnnGetROP2 (HANNOBJECT hObject,
                                  L_UINT L_FAR*puRop2);
L_INT EXT_FUNCTION L_AnnGetScalarX (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarX);
L_INT EXT_FUNCTION L_AnnGetScalarY (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarY);
L_INT EXT_FUNCTION L_AnnGetSelectCount (HANNOBJECT hObject,
                                      L_UINT L_FAR *puCount);
L_INT EXT_FUNCTION L_AnnGetSelected (HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfSelected);
L_INT EXT_FUNCTION L_AnnGetSelectItems(HANNOBJECT hObject, 
                                       pHANNOBJECT pItems);
L_INT EXT_FUNCTION L_AnnGetSelectRect(HANNOBJECT hObject,
                                       LPRECT pRect);
L_INT EXT_FUNCTION L_AnnGetTag (HANNOBJECT hObject,
                                 L_UINT32 L_FAR * puTag);
L_INT EXT_FUNCTION L_AnnGetText (HANNOBJECT hObject,
                                  L_CHAR L_FAR * pText);
L_INT EXT_FUNCTION L_AnnGetTextLen (HANNOBJECT hObject,
                                     L_UINT L_FAR * puLen);
L_INT EXT_FUNCTION L_AnnGetTool (HANNOBJECT hObject,
                                    L_UINT L_FAR * puTool);
L_INT EXT_FUNCTION L_AnnGetToolBarButtonVisible(HWND hwndToolBar,
                                     L_UINT uButton,
                                     L_BOOL L_FAR *pfVisible);
L_INT EXT_FUNCTION L_AnnGetToolBarChecked (HWND hwndToolBar,
                                     L_UINT L_FAR *puChecked);
L_INT EXT_FUNCTION L_AnnGetTransparent (HANNOBJECT hObject,
                                  L_BOOL L_FAR*pbTransparent);
L_INT EXT_FUNCTION L_AnnGetType (HANNOBJECT hObject,
                                  L_UINT L_FAR * puObjectType);
L_INT EXT_FUNCTION L_AnnGetTopContainer (HANNOBJECT hObject,
                                  pHANNOBJECT phContainer);
L_INT EXT_FUNCTION L_AnnGetUserMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puMode);
L_INT EXT_FUNCTION L_AnnGetVisible (HANNOBJECT hObject,
                                     L_BOOL L_FAR * pfVisible);
L_INT EXT_FUNCTION L_AnnGetWnd (HANNOBJECT hObject,
                                 HWND L_FAR * phWnd);
L_INT EXT_FUNCTION L_AnnHitTest (HANNOBJECT hObject,
                                  LPPOINT pPoint,
                                  L_UINT L_FAR * puResult,
                                  pHANNOBJECT phObjectHit);
L_INT EXT_FUNCTION L_AnnInsert (HANNOBJECT hContainer,
                                 HANNOBJECT hObject,
                                 L_BOOL fStripContainer);
L_INT EXT_FUNCTION L_AnnGetItem (HANNOBJECT hContainer,
                                 pHANNOBJECT phItem);
L_INT EXT_FUNCTION L_AnnLoad (L_CHAR L_FAR * pFile,
                               pHANNOBJECT phObject);
L_INT EXT_FUNCTION L_AnnLoadOffset (L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 nLength,
                               pHANNOBJECT phObject);
L_INT EXT_FUNCTION L_AnnLoadMemory (L_UCHAR L_FAR * pMem,
                               L_UINT32 uMemSize,
                               pHANNOBJECT phObject);
L_INT EXT_FUNCTION L_AnnLock (HANNOBJECT hObject, 
                              L_CHAR L_FAR* pLockKey, 
                              L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnMove(HANNOBJECT hObject,
                               L_DOUBLE dDx,
                               L_DOUBLE dDy,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnPrint(HDC hDC,
                              LPRECT prcBounds,
                              HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnRealize(pBITMAPHANDLE pBitmap,
                               LPRECT prcBounds,
                               HANNOBJECT hObject,
                               L_BOOL fRedactOnly);
L_INT EXT_FUNCTION L_AnnResize(HANNOBJECT hObject,
                               L_DOUBLE dFactorX,
                               L_DOUBLE dFactorY,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnReverse(HANNOBJECT hObject,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnRemove (HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnRotate(HANNOBJECT hObject,
                               L_DOUBLE dAngle,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSave (L_CHAR L_FAR * pFile,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected);
L_INT EXT_FUNCTION L_AnnSaveOffset (L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 L_FAR *puSizeWritten,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected);
L_INT EXT_FUNCTION L_AnnSaveMemory (HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               HGLOBAL L_FAR *phMem,
                               L_UINT32 L_FAR * puMemSize);
L_INT EXT_FUNCTION L_AnnSaveTag(HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected);
L_INT EXT_FUNCTION L_AnnSelectPoint(HANNOBJECT hObject,
                                     LPPOINT pPoint);
L_INT EXT_FUNCTION L_AnnSelectRect(HANNOBJECT hObject,
                                     LPRECT pRect);
L_INT EXT_FUNCTION L_AnnSendToBack (HANNOBJECT hObject);

L_INT EXT_FUNCTION L_AnnSetActiveState (HANNOBJECT hObject,
                                         L_UINT uState);
L_INT EXT_FUNCTION L_AnnSetAutoContainer (HANNOBJECT hObject,
                                          HANNOBJECT hContainer);
L_INT EXT_FUNCTION L_AnnSetAutoDrawEnable (HANNOBJECT hObject,
                                          L_BOOL fEnable);
L_INT EXT_FUNCTION L_AnnSetAutoMenuEnable (HANNOBJECT hObject,
                                          L_BOOL fEnable);
L_INT EXT_FUNCTION L_AnnSetAutoText (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_CHAR L_FAR *pText);
L_INT EXT_FUNCTION L_AnnSetBackColor (HANNOBJECT hObject,
                                       COLORREF crBack,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetBitmap (HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap,
                                    L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetDpiX(HANNOBJECT hObject,
                                 L_DOUBLE dDpiX,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetDpiY(HANNOBJECT hObject,
                                 L_DOUBLE dDpiY,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFillMode (HANNOBJECT hObject,
                                      L_UINT uFillMode,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFillPattern (HANNOBJECT hObject,
                                         L_UINT uFillPattern,
                                         L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontBold (HANNOBJECT hObject,
                                      L_BOOL fFontBold,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontItalic (HANNOBJECT hObject,
                                        L_BOOL fFontItalic,
                                        L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontName (HANNOBJECT hObject,
                                      L_CHAR L_FAR * pFontName,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontSize (HANNOBJECT hObject,
                                      L_DOUBLE dFontSize,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontStrikeThrough (HANNOBJECT hObject,
                                               L_BOOL fFontStrikeThrough,
                                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontUnderline (HANNOBJECT hObject,
                                           L_BOOL fFontUnderline,
                                           L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetForeColor (HANNOBJECT hObject,
                                       COLORREF crFore,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetHyperlink (HANNOBJECT hObject,
                                       L_UINT uType,
                                       L_UINT uMsg,
                                       WPARAM wParam,
                                       L_CHAR L_FAR*pLink,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetHyperlinkMenuEnable(HANNOBJECT hObject,
                            L_BOOL fEnable,
                            L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetLineStyle (HANNOBJECT hObject,
                                       L_UINT uLineStyle,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetLineWidth (HANNOBJECT hObject,
                                       L_DOUBLE dLineWidth,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetOffsetX(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetX,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetOffsetY(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetY,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetPoints (HANNOBJECT hObject,
                                    pANNPOINT pPoints,
                                    L_UINT uCount);
L_INT EXT_FUNCTION L_AnnSetPolyFillMode (HANNOBJECT hObject,
                                      L_UINT uPolyFillMode,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetROP2 (HANNOBJECT hObject,
                                      L_UINT uROP2,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetRect (HANNOBJECT hObject,
                                  pANNRECT pRect);
L_INT EXT_FUNCTION L_AnnSetSelected (HANNOBJECT hObject,
                                      L_BOOL fSelected,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetScalarX(HANNOBJECT hObject,
                                 L_DOUBLE dScalarX,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetScalarY(HANNOBJECT hObject,
                                 L_DOUBLE dScalarY,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetTag (HANNOBJECT hObject,
                                 L_UINT32 uTag,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetText (HANNOBJECT hObject,
                                  L_CHAR L_FAR * pText,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetTool (HANNOBJECT hObject,
                                 L_UINT uTool);
L_INT EXT_FUNCTION L_AnnSetToolBarButtonVisible(HWND hwndToolBar,
                                  L_UINT uButton,
                                  L_BOOL fVisible);
L_INT EXT_FUNCTION L_AnnSetToolBarChecked(HWND hwndToolBar,
                                  L_UINT uChecked);
L_INT EXT_FUNCTION L_AnnSetTransparent (HANNOBJECT hObject,
                                      L_BOOL bTransparent,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetUndoDepth (HANNOBJECT hObject,
                                      L_UINT uLevels);
L_INT EXT_FUNCTION L_AnnSetUserMode (HANNOBJECT hObject,
                                      L_UINT uMode);
L_INT EXT_FUNCTION L_AnnSetVisible (HANNOBJECT hObject,
                                     L_BOOL fVisible,
                                     L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetWnd (HANNOBJECT hObject,
                                 HWND hWnd);
L_INT EXT_FUNCTION L_AnnShowLockedIcon (HANNOBJECT hObject,
                                     L_BOOL bShow,
                                     L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnUndo (HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnUnlock (HANNOBJECT hObject, 
                              L_CHAR L_FAR* pUnlockKey, 
                              L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnUnrealize(pBITMAPHANDLE pBitmap, 
                                LPRECT prcBounds, 
                                HANNOBJECT hObject, 
                                L_BOOL fSelected);

L_INT EXT_FUNCTION L_AnnSetBitmapDpiX(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiX,
                                      L_UINT    uFlags);
L_INT EXT_FUNCTION L_AnnSetBitmapDpiY(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiY,
                                      L_UINT    uFlags);
L_INT EXT_FUNCTION L_AnnGetBitmapDpiX(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiX);
L_INT EXT_FUNCTION L_AnnGetBitmapDpiY(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiY);
L_INT EXT_FUNCTION L_AnnSetUnit(HANNOBJECT hObject,
                                L_UINT uUnit,
                                L_CHAR L_FAR* pUnitAbbrev,
                                L_UINT uPrecision,
                                L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetUnit(HANNOBJECT hObject,
                                L_UINT L_FAR*puUnit,
                                L_CHAR L_FAR*pUnitAbbrev,
                                L_UINT L_FAR*puPrecision);
L_INT EXT_FUNCTION L_AnnGetUnitLen(HANNOBJECT hObject,
                                   L_UINT L_FAR*puLen);
L_INT EXT_FUNCTION L_AnnGetDistance(HANNOBJECT hObject,
                                    L_DOUBLE L_FAR*pdDistance);
L_INT EXT_FUNCTION L_AnnSetGaugeLength(HANNOBJECT hObject,
                                       L_DOUBLE dLength,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetGaugeLength(HANNOBJECT hObject,
                                       L_DOUBLE L_FAR*pdLength);
#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTANN_H_ */
