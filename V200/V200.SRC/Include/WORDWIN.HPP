//
//  Funktionsprototypen zur Erzeugung von Editfenstern und
//  damit verbundene Hilfsfunktionen
//
//  $Header:   P:/marille/clinicum/include/rev/wordwin.hpv   1.6   05 Oct 1998 11:24:52   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/wordwin.hpv  $
// 
//    Rev 1.6   05 Oct 1998 11:24:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.5   04 Feb 1996 15:45:46   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.4   02 Feb 1996 10:59:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   27 Aug 1995 13:05:46   HANNES
// 
//    Rev 1.2   31 Mar 1995 13:12:02   HANNES
//  
// 
//    Rev 1.1   15 Dec 1994 18:58:54   HANNES
// Klassennamen extern vergeben
// 
//    Rev 1.0   24 Jun 1994 17:57:52   HANNES
// Neuubernahme clinicum
// 
//    Rev 1.3   13 Jan 1994 16:01:22   HANNES
// WWM_SETCARETTOEND
// 
//    Rev 1.2   06 Oct 1993 09:55:54   HANNES
// Neue Definitionen und Funktionsprototypen
// 
//    Rev 1.1   02 Jun 1993 13:23:16   GERHOLD
// WWCreateEx
// 
//    Rev 1.0   12 May 1993 17:23:00   HANNES
// Initial revision.
//

DLLExport HWND _export WINAPI WWCreateWin (HWND hParent,WORD Id,int format,
                                     int x0,int y0,
                                     int AnzChars,
                                     DWORD style,
                                     HINSTANCE hInstance
                                    );
DLLExport HWND _export WINAPI WWCreateWinEx (HWND hParent,WORD Id,int format,
                                       int x0,int y0,
                                       int w,int h,
                                       DWORD style,
                                       BOOL password,
                                       int AnzLines,
                                       int Width,
                                       int mAnzChars
                                      );

DLLExport int _export WINAPI WWGetXWidth (int format,int AnzChars);
DLLExport int _export WINAPI WWGetYHeight (int format);
typedef VOID (WINAPI * WWPAINTCALLBACK) (HWND hWnd,HDC hDC);
DLLExport void _export WINAPI DMWAPI_SetClassNames (LPSTR WordWinClass,WWPAINTCALLBACK pcallback, double ratio);
void RegisterWordWin (HINSTANCE hInstance);
#define WWDEFFORMAT     2
#define WWM_CARETTOEND  WM_USER + 1000

