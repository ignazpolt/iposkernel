/////////////////////////////////////////////////////////////////////////
//  Dialogbox zum Suchen
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/misc.hpv   1.2   02 Feb 1996 10:59:16   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/misc.hpv  $
// 
//    Rev 1.2   02 Feb 1996 10:59:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   07 Jun 1995 12:18:52   GERHOLD
// Suchen und Ersetzen (COMMDLG)
// 
//    Rev 1.0   12 Jul 1994 14:46:18   HANNES
// Initial revision.
//
extern HWND hDlgFind;               //FindText modeless dialog handle
extern HWND hDlgReplace;            //ReplaceText modeless dialog handle
extern UINT iMSGFind;

LONG WINAPI LSearchMessageHandler (HWND hWnd, LPFINDREPLACE pFR);
HWND WINAPI SearchDialogs (HWND hWndOwner, WORD iDialog, 
                               LPSTR SearchStr, LPSTR ReplaceStr);


BOOL GetSearchString (HWND hWParent,
                      LPSTR sstring,int sstringsize,
                      LPSTR rstring,int rstringsize,
                      BOOL FAR *cs,
                      BOOL FAR *doReplace
                     );

BOOL GetCaseSensitive();

BOOL MoveDialog (HWND hWnd,int FAR *dx,int FAR *dy);
BOOL SR_LButtonDown (HWND hWnd,int x,int y);
LONG SR_CheckMSG (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done);
void StartScrolling (HWND hWnd);
void EndScrolling (HWND hWnd,int dx,int dy);
void SelectElems (HWND hWnd,LPRECT r);
LONG TrackMsgProc (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done);
void WriteInCaption (LPSTR txt);
void WriteInCaption (int x,int y);


