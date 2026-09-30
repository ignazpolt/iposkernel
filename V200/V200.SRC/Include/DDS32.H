/*------------------------------------------------------------------------
 *  $Header:   P:/marille/clinicum/include/rev/dds32.h_v   1.7   27 Jun 2000 18:37:12   Martin  $
 *  $Log:   P:/marille/clinicum/include/rev/dds32.h_v  $
 * 
 *    Rev 1.7   27 Jun 2000 18:37:12   Martin
 * Ltx()
 * 
 *    Rev 1.6   18 Feb 2000 19:34:04   Martin
 * Doppelmonitor
 * 
 *    Rev 1.5   27 Jan 1998 12:35:14   Martin
 * MyGetPrivateProfileString auch in 32 Bit
 * 
 *    Rev 1.4   04 Mar 1996 20:53:46   MARTIN
 * MyGetPrivateProfile ...
 * 
 *    Rev 1.3   02 Feb 1996 11:02:32   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.2   27 Jan 1996 14:17:18   GERHOLD
 * noch ein paar #defines dazu.
 * 
 *    Rev 1.1   17 Jan 1996 19:47:44   GERHOLD
 * Sch.... PVCS Header
 * 
 *    Rev 1.0   17 Jan 1996 19:27:46   GERHOLD
 * Initial revision.
--------------------------------------------------------------------------*/

#ifdef _UNICODE
# define _T(x) L##x
# define _stprintf swprintf
#else
# define _T(x) x
# define _stprintf sprintf
#endif

typedef char ACHAR;  /// Ansi character
typedef LPSTR LPASTR;  /// Ansi character string
typedef LPCSTR LPCASTR;  /// constant Ansi character string

typedef BYTE CPLCHAR;  /// placeholder for declaring fixed size CPLSTR buffers
typedef CPLCHAR *LPCPLSTR;  /// CPL string (unknown if Ansi or Unicode with BOM prefix)

// the followiong macros must only be used with LPCPLSTRs!
#define WITH_BOM(cplstr) ((cplstr[0] == 0xFF) && (cplstr[1] == 0xFE))

#ifdef UNICODE

#define BOM_SIZE 2
#define BOM 0xFEFF
// the followiong macros must only be used with LPCPLSTRs!
#define WITHOUT_BOM(cplstr) ((cplstr[0] != 0xFF) || (cplstr[1] != 0xFE))
#define TO_LPTSTR(cplstr) (LPTSTR (cplstr) + 1)
// the following macro must only be used with LPTSTRs that were read directy from a CPL string variable
#define TO_BOMSTR(lptstr) (lptstr - 1)

#define CF_MYTEXT CF_UNICODETEXT

#else

#define WriteStrData WriteData
#define WritelStrData WritelData
#define SetStrData SetData

#define CF_MYTEXT CF_TEXT

#endif

#define CRACKER_VARS           \
   HWND CRACKER_hWnd;          \
   WORD CRACKER_wNotify;       \
   WORD CRACKER_wID;

#ifdef WIN32
//---------------------------------------------------------------------------
// Deklarationen fuer die 32 - Bit - Version
//---------------------------------------------------------------------------
#define _export   
#define __export  
#define huge     
#define _huge    

#define DLLImport	__declspec( dllimport )
#define DLLExport	__declspec( dllexport )

#define hmemcpy(a, b, c)    lmemcpy(a, b, c)
#define _fmemcpy(a, b, c)   lmemcpy(a, b, c)
#define _fmemset(a, b, c)   lmemset(a, b, c)
#define _fstrcpy(a, b)      lstrcpy(a, b)
#define _fstrcat(a, b)      lstrcat(a, b)
#define _fstrtok(a, b)       strtok(a, b)

#define   LONG2POINT(l, pt)   ((pt).x = (SHORT)LOWORD(l), (pt).y = (SHORT)HIWORD(l))

#define CRACK_MESSAGEsc                 \
  {                                     \
  CRACKER_wID       = LOWORD(wP);       \
  CRACKER_wNotify   = HIWORD(wP);       \
  CRACKER_hWnd      = (HWND)lP;         \
  }

typedef struct tagHILOCHUNK
  {
  LONG hi;
  LONG lo;
  }
HILOCHUNK;

typedef HILOCHUNK FAR *LPHILOCHUNK;

#define HICHUNK(lParam) (((LPHILOCHUNK)(lParam))->hi)
#define LOCHUNK(lParam) (((LPHILOCHUNK)(lParam))->lo)
#define MAKECHUNKsc(lParam,low,high) {lParam.lo=(LONG)(low);lParam.hi=(LONG)(high);}
#define HILOCHUNKPARAM(lParam) ((LONG)(&lParam))


#define DBINT   short
#define DBBOOL  short

#else

#define DLLExport
//---------------------------------------------------------------------------
// Deklarationen fuer die 16 - Bit - Version
//---------------------------------------------------------------------------

#define CRACK_MESSAGEsc                 \
  {                                     \
  CRACKER_wID       = wP;               \
  CRACKER_wNotify   = HIWORD(lP);       \
  CRACKER_hWnd      = LOWORD(lP);       \
  }


#define HICHUNK(lParam) HIWORD(lParam)
#define LOCHUNK(lParam) LOWORD(lParam)
#define MAKECHUNKsc(lParam,lo,hi) lParam=MAKELONG(lo,hi);
#define HILOCHUNK DWORD
#define HILOCHUNKPARAM(lParam) (lParam)

#define DBINT   int
#define DBBOOL  int

#endif


#ifndef  NO_MEMORY_CHECK
// fuer Speicherfressersuche:
#ifdef DEBUG
DLLExport extern HGLOBAL _export WINAPI GGlobalAlloc (UINT fuAlloc, DWORD cbAlloc);
DLLExport extern HGLOBAL _export WINAPI GGlobalReAlloc (HGLOBAL hglb, DWORD cbNewSize, UINT fuAlloc);
DLLExport extern HGLOBAL _export WINAPI GGlobalFree (HGLOBAL hglb);
DLLExport extern void _export WINAPI CheckGlobalAllocs (void);
#ifndef GLOBALCHECK_MAIN
#define GlobalAlloc GGlobalAlloc
#define GlobalReAlloc GGlobalReAlloc
#define GlobalFree GGlobalFree

#endif    // globalcheck_main
#endif    // debug
#endif    // no_memory_check

// eigene PrivateProfile-Lese-Funktionen (die die .ini-Datei shareable oeffnen)
DLLExport extern UINT _export WINAPI MyGetPrivateProfileInt(LPCSTR, LPCSTR, int, LPCSTR);
DLLExport extern int _export WINAPI MyGetPrivateProfileString(LPCSTR, LPCSTR, LPCSTR, LPSTR, int, LPCSTR);
#ifdef WIN32
#undef GetPrivateProfileInt
#undef GetPrivateProfileString
#endif
#define GetPrivateProfileInt MyGetPrivateProfileInt
#define GetPrivateProfileString MyGetPrivateProfileString

// GetSystemMetrics abfangen (wegen Doppelmonitorsystemen)
__declspec( dllexport ) int WINAPI MyGetSystemMetrics(int nIndex);
#ifndef GLOBALCHECK_MAIN
#ifdef WIN32
#undef GetSystemMetrics
#endif
#define GetSystemMetrics MyGetSystemMetrics
#endif

// einfache Mehrsprachigkeit mittles Texttabelle
DLLExport extern void _export WINAPI InitLanguageTextTable(void);
DLLExport extern LPSTR _export WINAPI Ltx(DWORD id);
DLLExport extern int _export WINAPI GetLtx(DWORD id, LPSTR s, int maxsize);

