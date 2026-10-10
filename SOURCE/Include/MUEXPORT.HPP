extern HGLOBAL hglb;

struct MUSCROLL
    {
    HWND        hWndAssociate;  //Associate window handle
    DWORD       dwStyle;        //Copy of GetWindowLong(hWnd, GWL_STYLE)
    WORD        iMin;           //Minimum position
    WORD        iMax;           //Maximum position
    WORD        iPos;           //Current position
    WORD        wState;         //State flags
    COLORREF    rgCr[CCOLORS];  //Configurable colors.
    };

// typedef MUSCROLL     *PMUSCROLL;
typedef MUSCROLL FAR *LPMUSCROLL;

//typedef HANDLE FAR *LPHANDLE;

#define CBMUSCROLL sizeof(MUSCROLL)


/*
 * Macros to change the control state given a PMUSCROLL
 * and state flag(s)
 */
#define StateSet(p, wFlags)    (p->wState |=  (wFlags))
#define StateClear(p, wFlags)  (p->wState &= ~(wFlags))
#define StateTest(p, wFlags)   (p->wState &   (wFlags))




//Private functions specific to the control.

//INIT.C
// int    WINAPI LibMain(HINSTANCE, WORD, WORD, LPSTR);

DLLExport BOOL _export WINAPI FRegisterControl(HINSTANCE hInstance);
//BOOL       PASCAL FRegisterControl(HINSTANCE);
LONG       PASCAL LMicroScrollCreate(HWND, WORD, LPMUSCROLL, LPCREATESTRUCT);
BOOL       PASCAL FTextParse(LPSTR, LPINT, LPINT, LPINT);
WORD       PASCAL WTranslateUpToChar(LPSTR FAR *, char);

//MUSCROLL.C
DLLExport LONG WINAPI _export MicroScrollWndProc(HWND, UINT, WPARAM, LPARAM);
void       PASCAL PositionChange(HWND, LPMUSCROLL);
void       PASCAL ClickedRectCalc(HWND, LPMUSCROLL, LPRECT);

//PAINT.C
LONG       PASCAL LMicroScrollPaint(HWND, LPMUSCROLL);
void       PASCAL Draw3DButtonRect(HDC, HPEN, HPEN, WORD, WORD,\
                                   WORD, WORD, BOOL);

//MSAPI.C
LONG   PASCAL LMicroScrollAPI (HWND, UINT, WPARAM, LPARAM, LPMUSCROLL);

//WEP.C
//int WINAPI WEP(int);




//Standard dialog editor callbacks.
HANDLE WINAPI HCtlInfo(void);
WORD   WINAPI WTranslateCtlFlags(DWORD, LPSTR, WORD);
BOOL   WINAPI FShowCtlStyleDlg(HWND, HANDLE, LPFNSTRTOID, LPFNIDTOSTR);
BOOL   WINAPI FCtlStyleDlgProc(HWND, WORD, WORD, LONG);



//Message API Functions
DLLExport HWND     _export WINAPI MSHwndAssociateSet(HWND hWnd, HWND hWndAssociate);
DLLExport HWND     _export WINAPI MSHwndAssociateGet(HWND hWnd);
DLLExport DWORD    _export WINAPI MSDwRangeSet(HWND hWnd, WORD iMin, WORD iMax);
DLLExport DWORD    _export WINAPI MSDwRangeGet(HWND hWnd);
DLLExport WORD     _export WINAPI MSWCurrentPosSet(HWND hWnd, WORD iPos);
DLLExport WORD     _export WINAPI MSWCurrentPosGet(HWND hWnd);
DLLExport BOOL     _export WINAPI MSFNoPegScrollSet(HWND hWnd, BOOL fNoPegScroll);
DLLExport BOOL     _export WINAPI MSFNoPegScrollGet(HWND hWnd);
DLLExport BOOL     _export WINAPI MSFInvertRangeSet(HWND hWnd, BOOL fInvertRange);
DLLExport BOOL     _export WINAPI MSFInvertRangeGet(HWND hWnd);
DLLExport COLORREF _export WINAPI MSCrColorSet(HWND hWnd, WORD iColor, COLORREF cr);
DLLExport COLORREF _export WINAPI MSCrColorGet(HWND hWnd, WORD iColor);
