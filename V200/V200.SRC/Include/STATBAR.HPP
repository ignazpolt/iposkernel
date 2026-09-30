//-----------------------------------------------------------------------------
// Implementation einer Statuszeile
//-----------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/include/rev/statbar.hpv   1.6   02 Feb 1996 10:59:36   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/statbar.hpv  $
// 
//    Rev 1.6   02 Feb 1996 10:59:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   23 Aug 1995 11:06:42   GERHOLD
// 
//    Rev 1.4   15 Dec 1994 18:58:50   HANNES
// Klassennamen extern vergeben
// 
//    Rev 1.3   07 Nov 1994 17:31:40   GERHOLD
//-----------------------------------------------------------------------------
#define SB_SETTEXT        WM_USER+0
#define SB_SETPART        WM_USER+1
#define SB_SETPARTS       WM_USER+2
#define SB_GETHEIGHT      WM_USER+3
#define SB_GETTEXTLENGTH  WM_USER+4
#define SB_SETBORDERS     WM_USER+5
#define SB_GETPARTS       WM_USER+6
#define SB_GETBORDERS     WM_USER+7
#define SB_SETMINHEIGHT   WM_USER+8
#define SB_SIMPLE         WM_USER+9


#define SBT_OWNERDRAW   0x100
#define SBT_NOBORDERS   0x200
#define SBT_POPOUT      0x400
#define HBT_SPRING      0x800

#define FIELD_SEPARATOR   0
#define FIELD_TEXT        1

DLLExport LONG _export WINAPI StatBar_WndProc(HWND hWnd, WORD msg, WPARAM wParam, LPARAM lParam);
DLLExport BOOL _export WINAPI StatBar_Register(HINSTANCE hInstance);
DLLExport HWND _export WINAPI CreateStatusbar (DWORD Style, LPSTR StartText, HWND hParent, int wID);
DLLExport void _export WINAPI STATBAR_SetClassNames (LPSTR StatBarClassName);

DLLExport void _export WINAPI SetFieldColor (HWND hWnd, int FieldNum, COLORREF crFore, COLORREF crBack);
DLLExport void _export WINAPI ResetFieldColor (HWND hWnd, int FieldNum);

