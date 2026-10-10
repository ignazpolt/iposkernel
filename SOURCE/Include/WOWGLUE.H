/*
  WOWGLUE.H - 1994 James M. Finnegan
*/

// WOWGlue Header.  Used by the WOWGlue DLL source file, as well as any
// app using the DLL.

#ifndef _INC_WOWGLUE
#define _INC_WOWGLUE

#ifdef __cplusplus
extern "C" {            // No mangling!
#endif

#include <windows.h>


// #defines, #defines everywhere!
#define HINSTANCE32              DWORD
#define HFILE32                  DWORD
#define HWND32                   DWORD

// #defines for WOWCallProc32() parameter conversion
#define PARAM_01                 0x00000001
#define PARAM_02                 0x00000002
#define PARAM_03                 0x00000004
#define PARAM_04                 0x00000008
#define PARAM_05                 0x00000010
#define PARAM_06                 0x00000020
#define PARAM_07                 0x00000040
#define PARAM_08                 0x00000080
#define PARAM_09                 0x00000100
#define PARAM_10                 0x00000200
#define PARAM_11                 0x00000400
#define PARAM_12                 0x00000800
#define PARAM_13                 0x00001000
#define PARAM_14                 0x00002000
#define PARAM_15                 0x00004000
#define PARAM_16                 0x00008000
#define PARAM_17                 0x00010000
#define PARAM_18                 0x00020000
#define PARAM_19                 0x00040000
#define PARAM_20                 0x00080000
#define PARAM_21                 0x00100000
#define PARAM_22                 0x00200000
#define PARAM_23                 0x00400000
#define PARAM_24                 0x00800000
#define PARAM_25                 0x01000000
#define PARAM_26                 0x02000000
#define PARAM_27                 0x04000000
#define PARAM_28                 0x08000000
#define PARAM_29                 0x10000000
#define PARAM_30                 0x20000000
#define PARAM_31                 0x40000000
#define PARAM_32                 0x80000000

// #defines for WOWGetCaps32()
#define WOW_LOADLIBRARY          0x0001
#define WOW_FREELIBRARY          0x0002
#define WOW_GETPROCADDRESS       0x0004
#define WOW_CALLPROC             0x0008
#define WOW_VDMPTR32             0x0010
#define WOW_VDMPTR16             0x0020
#define WOW_HWND32               0x0040

// Wrappers for functions in Kernel (16 bit)
HINSTANCE32 WINAPI    WOWLoadLibraryEx32  (LPSTR, HFILE32, DWORD);
BOOL        WINAPI    WOWFreeLibrary32    (HINSTANCE32);
FARPROC     WINAPI    WOWGetProcAddress32 (HINSTANCE32, LPCSTR);
DWORD       WINAPI    WOWGetVDMPointer32  (LPVOID, UINT);
DWORD       FAR CDECL WOWCallProc32       (FARPROC, DWORD, DWORD, ...);

// My two cents
DWORD       WINAPI    WOWGetCaps32         (VOID);
UINT        WINAPI    WOWCreateVDMPointer16(DWORD, DWORD);
UINT        WINAPI    WOWDeleteVDMPointer16(UINT);
HWND32      WINAPI    WOWHwndToHwnd32      (HWND);


#ifdef __cplusplus
}                       // End of extern "C" {
#endif 

#endif  // _INC_WOWGLUE                                   
