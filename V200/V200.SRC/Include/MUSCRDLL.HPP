/*
 * MUSCRDLL.H
 *
 * DLL Specific include file.
 *
 * Contains all definitions and and prototypes pertinent ONLY
 * to the DLL.  API related information is contained in MUSCROLL.H.
 * API in any way.
 *
 * Version 1.1, October 1991, Kraig Brockschmidt
 *
 */


#include <custcntl.h>   //Standard Windows header file for custom controls.
#include "muscroll.hpp"   //Get interface stuff for the control.



/*
 * In window extra bytes we simply store a local handle to
 * a MUSCROLL data structure.  The local memory is allocated
 * from the control's local heap (either application or DLL)
 * instead of from USER's heap, thereby saving system resources.
 *
 * Note that the window styles that are stored in the regular
 * windwow structure are copied here.  This is to optimize access
 * to these bits, avoiding extra calls to GetWindowLong.
 */




//Offsets to use with GetWindowWord
#define GWW_MUSCROLLHMEM    0

//Extra bytes for the window if the size of a local handle.
#define CBWINDOWEXTRA       sizeof(LPHANDLE)

//Extra Class bytes.
#define CBCLASSEXTRA        0



//Control state flags.
#define MUSTATE_GRAYED      0x0001  // disabled
#define MUSTATE_HIDDEN      0x0002
#define MUSTATE_MOUSEOUT    0x0004
#define MUSTATE_UPCLICK     0x0008
#define MUSTATE_DOWNCLICK   0x0010
#define MUSTATE_LEFTCLICK   0x0008  //Repeated since MSS_VERTICAL and
#define MUSTATE_RIGHTCLICK  0x0010  //MSS_HORIZONTAL are exclusive.

//Combination of click states.
#define MUSTATE_CLICKED     (MUSTATE_LEFTCLICK | MUSTATE_RIGHTCLICK)

//Combination of state flags.
#define MUSTATE_ALL         0x001F








//Timer identifiers.
#define IDT_FIRSTCLICK      500
#define IDT_HOLDCLICK       501

#define CTICKS_FIRSTCLICK   400
#define CTICKS_HOLDCLICK    50


//Default range and position constants.
#define IDEFAULTMIN         0
#define IDEFAULTMAX         9
#define IDEFAULTPOS         5




//Stringtable identifiers
#define IDS_CLASSNAME           0
#define IDS_FULLNAME            1
#define IDS_CREDITS             2

//Dialog editor interface string
#define IDS_VERTICAL            3
#define IDS_HORIZONTAL          4
#define IDS_MSS_VERTICAL        5
#define IDS_MSS_HORIZONTAL      6
#define IDS_MSS_TEXTHASRANGE    7
#define IDS_MSS_NOPEGSCROLL     8
#define IDS_MSS_INVERTRANGE     9
#define IDS_RANGEERROR          10





/*
 * All that follows in this include file is specific to
 * the dialog editor interface for the MicroScroll control.
 */

//Identifiers for the Style dialog.
#define ID_NULL                 -1
#define ID_IDEDIT               100
#define ID_TEXTEDIT             101
#define ID_RADIOVERTICAL        102
#define ID_RADIOHORIZONTAL      103
#define ID_CHECKTEXTHASRANGE    104
#define ID_CHECKNOPEGSCROLL     105
#define ID_CHECKINVERTRANGE     106



//Dialog box identifiers.
#define IDD_STYLEDIALOG         1




