/////////////////////////////////////////////////
// schiebe.hpp - Handling der Schiebelehre
/////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/include/rev/schiebe.hpv   1.2   18 Jun 1997 19:32:18   Martin  $
// $Log:   P:/marille/clinicum/include/rev/schiebe.hpv  $
// 
//    Rev 1.2   18 Jun 1997 19:32:18   Martin
// serielle Schiebelehre
// 
//    Rev 1.1   02 Feb 1996 11:00:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:02:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   02 Jun 1993 19:40:16   HANNES
// Schiebelehre in die DMWAPI transferiert
// 
//    Rev 1.0   02 Dec 1992 16:08:46   HANNES
// Initial revision.
//

// Initialisierung / Aufsetzen eines Timers
DLLExport BOOL _export WINAPI SetSLTimer (HWND);

// Ende
DLLExport void _export WINAPI ResetSLTimer (HWND);
DLLExport void _export WINAPI CloseSLTimer (HWND);

// Untersuchen des Timers
DLLExport BOOL _export WINAPI CheckTimer (HWND,WPARAM,LPARAM);

DLLExport void _export WINAPI SetStartPrinting ();
DLLExport void _export WINAPI SetEndPrinting ();

