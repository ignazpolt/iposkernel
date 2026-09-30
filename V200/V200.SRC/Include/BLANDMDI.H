//-------------------------------------------------------------------------
// IDs fuer Knoepfe und Elemente in der Toolbar
//-------------------------------------------------------------------------
/*
    $Header:   P:/marille/clinicum/include/rev/blandmdi.h_v   1.5   02 Feb 1996 11:02:38   GERHOLD  $
    $Log:   P:/marille/clinicum/include/rev/blandmdi.h_v  $
 * 
 *    Rev 1.5   02 Feb 1996 11:02:38   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.4   23 May 1995 12:06:06   GERHOLD
 * IDR_PREVIEW ... neue Buttons
 * 
 *    Rev 1.3   24 Apr 1995 15:44:26   GERHOLD
 * 
 *    Rev 1.2   24 Jan 1995 09:59:02   GERHOLD
 * 
 *    Rev 1.1   10 Jan 1995 10:58:02   GERHOLD
 * 
 *    Rev 1.0   02 Jan 1995 10:39:22   GERHOLD
 * Initial revision.
*/
//-------------------------------------------------------------------------
#define IDM_PATH 500
#define IDM_EDIT 501
#define IDM_EDITORFONT 502
#define IDM_FILEOPEN 120
#define IDM_FILECLOSE 121
#define IDM_FILESAVE 122
#define IDM_FILESAVEAS 123
#define IDM_FILESAVEALL 124
#define IDM_EXIT 1

// horizontale Position des Popup-Menus in dem die aktiven MDI-Fenster 
// angezeigt werden
#define MAINWINDOWMENU    5
#define DIALOGWINDOWMENU  5
#define WNDINMDIMENU      1


#define CBWNDEXTRA  0

#ifdef RC_INVOKED
#define ID(id) id
#else
#define ID(id) MAKEINTRESOURCE(id)
#endif

/* resource ID's */
#define IDBLANDFRAME  ID(1)
#define IDBLANDCHILD  ID(2)
#define IDBLANDMENU   ID(3)

/* menu ID's */
#define IDM_FILENEW        1001
#define IDM_FILEEXIT       1006
#define IDM_WINDOWTILE     4001
#define IDM_WINDOWCASCADE  4002
#define IDM_WINDOWCLOSEALL 4003
#define IDM_WINDOWICONS    4004
#define IDM_WINDOWCHILD    4100

/* string constants */
#define IDS_CLIENTTITLE    16
#define IDS_UNTITLED       17
#define IDS_APPNAME        18

#define CMD_TB_BASE        500
#define IDR_TOOLICONS      999
#define IDR_DIALOG         998
#define IDR_PREVIEW        997


#define ID_SEARCHCOMBO           CMD_TB_BASE+30
#define IDB_PROJECTFILES         CMD_TB_BASE+40
#define IDB_OPENPROJECT          CMD_TB_BASE+41

