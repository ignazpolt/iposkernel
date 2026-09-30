/*------------------------------------------------------------------------
 *  Struktur CallBackDescriptor
 *
 *  $Header:   P:/marille/clinicum/include/rev/cbdesc.h_v   1.1   26 Aug 1997 19:24:32   Martin  $
 *  $Log:   P:/marille/clinicum/include/rev/cbdesc.h_v  $
 * 
 *    Rev 1.1   26 Aug 1997 19:24:32   Martin
 * 16 Bit faehig
 * 
 *    Rev 1.0   25 Aug 1997 14:54:26   Martin
 * Initial revision.
 * 
 *------------------------------------------------------------------------*/

#ifdef WIN32
typedef __declspec( dllexport ) void (FAR PASCAL *SCRIPTCALLBACK) (LPVOID Desc, WORD AnzPars, LPWORD ParLen, LPVOID FAR *Param);
#else
typedef void (_export FAR PASCAL *SCRIPTCALLBACK) (LPVOID Desc, WORD AnzPars, LPWORD ParLen, LPVOID FAR *Param);
#endif

#pragma pack(1)
struct CBDesc {
  SCRIPTCALLBACK scb;
  LPVOID c;
  DWORD proc;
  LPVOID Offset;
  WORD AnzPars;
  WORD ExtraSize;
  DWORD Ref[1];  /* variabel, je nach AnzPars */
  /* danach kommen die ExtraDaten (ExtraSize Bytes) */
  };
#pragma pack()

typedef CBDesc FAR *LPCBDESC;

