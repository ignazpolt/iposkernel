struct CreateIconFolder_param {
  WORD parSize;
#ifdef UPDATE_ASYNCHRON
  LPMDICHILD c;
#else
  LPVOID c;
#endif
  WORD  TableInd;
  DWORD res;
  DWORD Screen;
  DWORD cbProc;
  DWORD abortProc;
  DWORD TableNameToChange;
  };
typedef CreateIconFolder_param FAR *LPCIFPAR;

struct IconEleData {
  LPSCRIPTCONTENT sc;
  LPVOID Record;
  };
typedef IconEleData FAR *LPICONELEDATA ;

#define ICN_DOEXCUTE      0
#define ICN_DOABORT       1
typedef void (WINAPI *ICNNOTIFY) (LPICONELEDATA eleData,CreateIconFolder_param FAR *par,WORD notifycode);

DLLExport void _export WINAPI CreateGroupWindow (
                        HWND hWndParent,LPSTR Caption,
                        int AnzGroups,
                        CreateIconFolder_param FAR *par,
                        ICNNOTIFY Notify
                                          );
DLLExport void _export WINAPI CreateIconWindow (LPSTR Caption);
DLLExport void _export WINAPI AddPmEle (LPSTR txt,LPBITMAPINFO lpbi,LPICONELEDATA eledata);
DLLExport void _export WINAPI AddPmEle (LPSTR txt,HICON hico,LPICONELEDATA eledata);
DLLExport void _export WINAPI GroupReady ();
DLLExport void _export WINAPI CloseIconWnd ();
DLLExport void _export WINAPI ShowGroupWindow ();
DLLExport void _export WINAPI HideGroupWindow ();
DLLExport BOOL _export WINAPI IsScreenValid ();
DLLExport BOOL _export WINAPI IsPmHotkey (LPMSG msg);

