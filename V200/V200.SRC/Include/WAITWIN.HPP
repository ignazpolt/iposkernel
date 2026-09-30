// $Header:   P:/marille/clinicum/include/rev/waitwin.hpv   1.1   02 Feb 1996 10:59:38   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/waitwin.hpv  $
// 
//    Rev 1.1   02 Feb 1996 10:59:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:22   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   11 Jan 1994 19:03:56   HANNES
// Abbrechen - Knopf
// 
//    Rev 1.3   07 Jan 1994 12:09:16   HANNES
// Waitwin in die DLL verlegt
// 
//    Rev 1.2   22 Sep 1993 09:44:28   GERHOLD
// Version nach St. Poelten
// 
//    Rev 1.1   20 Sep 1993 15:25:48   GERHOLD
// PaintFileInProcess ... schreibt mit, welche Datei bearbeitet wird.
// 
//    Rev 1.0   02 Dec 1992 16:07:32   HANNES
// Initial revision.
/*------------------------------------------------*/
/*      Wartefenster                              */
/*------------------------------------------------*/

class FAR WaitWin {
 private :
  void Create (LPSTR Caption,LPSTR ExtraText,HWND hWndParent,BOOL showAbort);
 public :
  LPSTR ExtraText;
  int height,width ;
  int xs,ysu,yso ;
  int tmh;
  HWND MyHandle;
  HWND Parent;
  BOOL BasePainted;
  void Paint(void);
  double percval ;
  double percstep ;
  int xact ;
  BOOL doShowAbort;
  HWND hBtnWnd;
  BOOL _IsAborted;

  // Speicherverwaltung
  DLLExport LPVOID _export WINAPI operator new (size_t size);
  DLLExport void _export WINAPI operator delete (LPVOID obj);
  DLLExport _export WINAPI WaitWin (LPSTR caption,LPSTR extra = NULL,HWND hWnd = 0,BOOL showAbort = FALSE);

  DLLExport void _export WINAPI SetVal (double val);
  DLLExport void _export WINAPI ResetVal (void);
  DLLExport void _export WINAPI SetStep (double s);
  DLLExport void _export WINAPI SetCaption (LPSTR caption);

  DLLExport void _export WINAPI SetExtra (LPSTR Text);

  DLLExport BOOL _export WINAPI IsAborted ();

  DLLExport _export WINAPI ~WaitWin ();
  };



