#define MOUSEINDEX	     6
#define CBTINDEX             1

#define NUMOFHOOKS 9

//
// Entry functions for the DLL
//
DLLExport void _export FAR PASCAL InstallFilter (int nHookIndex, int nCode );
DLLExport void _export FAR PASCAL CheckWindow (HWND hWnd,BOOL On_Off);

#define DOAVOID         1
#define DONTAVOID       0
DLLExport void _export FAR PASCAL AvoidActivation (HWND hWnd,int state);
DLLExport void _export FAR PASCAL InstallDestroyServer (HWND hWnd,BOOL state,HWND ActivateWnd);
DLLExport void _export FAR PASCAL WatchCreate (BOOL state,LPSTR Caption,LPSTR ClassName,HWND hMyWnd);
