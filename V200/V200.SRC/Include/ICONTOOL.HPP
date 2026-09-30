struct IconEleData ;
typedef IconEleData FAR *LPICONELEDATA ;
typedef void (WINAPI *ICNNOTIFY) (LPICONELEDATA eleData,WORD notifycode);

struct IconEleData {
  LPSCRIPTCONTENT sc;
  LPVOID Record;
  WORD TableInd;
  DWORD cbProc;
  ICNNOTIFY cbFunc;
#ifdef CHWND_TRACING
  LPMDICHILD c;
#else
  LPVOID c;
#endif
  };
typedef IconEleData FAR *LPICONELEDATA ;

#define ICN_DOEXCUTE      0

