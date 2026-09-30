/************************************************************
 *
 *  globmem.h
 *
 * $Header:   P:/marille/clinicum/include/rev/globmem.h_v   1.5   30 Mar 1998 20:20:14   Martin  $
 * $Log:   P:/marille/clinicum/include/rev/globmem.h_v  $
 * 
 *    Rev 1.5   30 Mar 1998 20:20:14   Martin
 * Add-/RemoveProfileOverrideBuffer
 * 
 *    Rev 1.4   29 Oct 1997 18:59:34   Hannes
 * Textbausteine
 * 
 *    Rev 1.3   04 Feb 1996 15:45:54   gerhold
 * 
 *    Rev 1.2   02 Feb 1996 11:02:20   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.1   09 Dec 1994 14:27:42   GERHOLD
 * 
 *    Rev 1.0   24 Jun 1994 17:01:00   HANNES
 * Neuuebernahme clinicum
 * 
 *    Rev 1.4   25 Jan 1994 18:38:06   HANNES
 * LogMsg, DMWAPI_ShutDown, DMWAPI_Setup
 * 
 *    Rev 1.3   05 Aug 1993 13:10:46   MARTIN
 * GetCRC
 * 
 *    Rev 1.2   05 Jul 1993 14:48:00   HANNES
 * lmemmove
 * 
 *    Rev 1.1   02 Apr 1993 18:07:12   HANNES
 * Beschleunigung, inlinefunktionen, Globale Speicherverwaltung
 * 
 *    Rev 1.0   02 Dec 1992 16:02:06   HANNES
 * Initial revision.
 ************************************************************/

#define FASTMEM

// Funktionprototypen zur Speicherverwaltung
DLLExport LPVOID _export WINAPI GetGlobalMem(GLOBALHANDLE FAR *,WORD FAR *,WORD);
DLLExport void   _export WINAPI FreeGlobalMem(LPVOID,GLOBALHANDLE FAR *);

#ifdef FASTMEM
inline LPVOID FixGlobalMem(GLOBALHANDLE hGmem,WORD Offs)
  { return LPSTR(GlobalLock (hGmem)) + Offs ; }
inline void   ReleaseGlobalMem(LPVOID lptr,GLOBALHANDLE hGmem)
  { }
inline void   ReleaseGlobalMem(WORD offs,GLOBALHANDLE hGmem)
  { }
#else
DLLExport LPVOID _export WINAPI FixGlobalMem(GLOBALHANDLE,WORD);
DLLExport void   _export WINAPI ReleaseGlobalMem(LPVOID,GLOBALHANDLE);
DLLExport void   _export WINAPI ReleaseGlobalMem(WORD,GLOBALHANDLE);
#endif
DLLExport WORD   _export WINAPI OffsetToGlobMem(LPVOID,GLOBALHANDLE);
DLLExport DWORD  _export WINAPI GetBlockSize32 (LPVOID);
DLLExport WORD   _export WINAPI GetBlockSize(LPVOID);
DLLExport WORD   _export WINAPI GetBlockSize16 (LPVOID);

inline void FAR *FixGlobalPtr(GLOBALHANDLE hGmem,WORD Offset)
  { return LPSTR(GlobalLock (hGmem)) + Offset ; }
inline WORD PtrOffs (GLOBALHANDLE hGmem,void FAR *Ptr)
  { return LPSTR (Ptr) - LPSTR(GlobalLock (hGmem)); }

// far Memory Funktionen
typedef const void FAR *LPCVOID;
#ifdef OLD_VERSION
void WINAPI lmemcpy (LPVOID,LPCVOID,WORD);
void WINAPI lmemset (LPVOID,WORD,WORD);
#endif
DLLExport BOOL _export WINAPI lmemcmp (LPCVOID,LPCVOID,WORD);
DLLExport void _export WINAPI lstrncpy (LPSTR,LPCSTR,WORD);

// Funktionen zur Speicherverwaltung bei freier Wahl des Segmentes
///////////////////////////////////////////////////////////////////
DLLExport LPVOID _export WINAPI GetGlobMem (WORD size);
DLLExport void _export WINAPI FreeGlobMem (LPVOID res);
DLLExport BOOL _export WINAPI GetFirstSegInfo (GLOBALHANDLE FAR *,WORD FAR *,LPVOID FAR *);
DLLExport BOOL _export WINAPI GetNextSegInfo (GLOBALHANDLE FAR *,WORD FAR *,LPVOID FAR *);

#ifdef UNICODE

// Die folgenden beiden Funktionen duerfen nur dann aufgerufen werden, wenn
// bereits feststeht, dass der Ausgangsstring im falschen Format vorliegt.
// Der Pointer, der zurueckgegeben wird, ist mit GetGlobMem alloziert und
// muss vom Aufrufer irgendwann wieder freigegeben werden!
DLLExport LPCPLSTR _export WINAPI AnsiToBomStr(LPASTR str);
#endif
DLLExport LPASTR _export WINAPI UnicodeToAnsi(LPWSTR str);

DLLExport void _export WINAPI LogMsg (LPSTR txt,LPSTR fName = NULL);
DLLExport void _export WINAPI LogMsg (int modnum,int line,LPSTR txt);
DLLExport extern void _export WINAPI DMWAPI_ShutDown ();
typedef void (WINAPI *CLEARQUEUE) (void);
typedef void (* CALLCONTEXTFUNCTION) (LPSTR Mod,LPSTR Name,LPVOID obj);
DLLExport extern void _export WINAPI DMWAPI_Setup (CLEARQUEUE,LPVOID,LPVOID,CALLCONTEXTFUNCTION);
DLLExport extern void _export WINAPI ClearQueue (void);

// CRC-Berechnung (fuer Hashfunktionen)
DLLExport int _export WINAPI GetCRC (LPSTR buffer,int size);

// profile overriding
DLLExport void _export WINAPI AddProfileOverrideBuffer (WORD Priority,LPSTR buffer);
DLLExport void _export WINAPI RemoveProfileOverrideBuffer (WORD Priority);

// logging

extern DLLExport void _export WINAPI SetJavaExceptionText (GLOBALHANDLE jet);

#pragma optimize ("alt" , on)

#ifdef WIN32
    inline void lmemcpy (LPVOID p1,LPCVOID p2,DWORD count)
      { 
      for (DWORD i = 0 ; i < count ; i++)
        ((BYTE FAR *) p1)[i] = ((BYTE FAR *) p2)[i];
      }
#else
    inline void lmemcpy (LPVOID p1,LPCVOID p2,WORD count)
      { 
      for (WORD i = 0 ; i < count ; i++)
        ((BYTE FAR *) p1)[i] = ((BYTE FAR *) p2)[i];
      }
#endif

inline void lmemset (LPVOID p1,WORD ch,WORD count)
  {
  for (WORD i = 0 ; i < count ; i++)
    ((BYTE FAR *) p1)[i] = (BYTE) ch;
  }

inline void lmemmove (LPVOID p1,LPVOID p2,int size)
  {
  if (p1 < p2) {
    for (int i = 0 ; i < size ; i++) {
      ((BYTE FAR *) p1)[i] = ((BYTE FAR *) p2)[i];
      }
    }
  else {
    for (int i = size - 1 ; i >= 0 ; i--) {
      ((BYTE FAR *) p1)[i] = ((BYTE FAR *) p2)[i];
      }
    }
  }

#pragma optimize ( "" , on)


