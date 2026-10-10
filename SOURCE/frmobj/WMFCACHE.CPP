/*--------------------------------------------------------*/
/*    Implementierung eines einfachen LRU - Algorythmus   */
/*    fuer Caching der WMF - Bilder                       */
/*--------------------------------------------------------*/
//
// $Header:   P:/marille/clinicum/frmobj/rev/wmfcache.cpv   1.5   05 Oct 1998 11:22:28   Gerhold  $
// $Log:   P:/marille/clinicum/frmobj/rev/wmfcache.cpv  $
// 
//    Rev 1.5   05 Oct 1998 11:22:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   17 Dec 1996 11:06:44   GERHOLD
// 32 Bit
// 
//    Rev 1.3   28 Jun 1996 15:54:12   MARTIN
// auch hier auf neue ResDB umstellen
// 
//    Rev 1.2   02 Feb 1996 10:49:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Jun 1994 20:43:00   MARTIN
// 
//    Rev 1.0   24 Jun 1994 16:45:52   MARTIN
// Neuuebernahme clinicum
// 
//    Rev 1.0   02 Dec 1992 15:48:46   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

#include "wmfcache.hpp"

// Die Daten werden in einer doppelt verketteten Liste gehalten,
// wobei das am letzten referenzierte immer ganz vorne gehalten
// wird. Beim Aufraeumen wird von hinten her geloescht (wenn
// moeglich)

struct HMFData {
  HMFData FAR *Next;
  HMFData FAR *Prev;
  WORD PicRec;
  WORD PicId;
  int  refCount;
  HMETAFILE hMF;
  };

static HMFData FAR *FirstRec ;
static HMFData FAR *LastRec ;

static HMETAFILE GetFromList (WORD PicRec,WORD PicId)
  {
  HMFData FAR *d = FirstRec;
  HMETAFILE res = 0 ;
  for ( ; d != NULL ; ) {
    if ((d->PicRec == PicRec) && (d->PicId == PicId)) {
      res = d->hMF ;
      d->refCount ++ ;
      if (d->Prev) {
        // Umordnungen vornehmen (An die Spitze stellen)
        d->Prev->Next = d->Next;
        if (d->Next) d->Next->Prev = d->Prev;
        else         LastRec       = d->Prev ;
        d->Next = FirstRec ;
        d->Prev = NULL ;
        if (FirstRec != NULL) FirstRec->Prev = d;
        FirstRec = d ;
        }
      break ;
      }
    d = d->Next;
    }
  return res ;
  }

static void DecreaseCount (HANDLE hMF)
  {
  HMFData FAR *d = FirstRec;
  for ( ; d != NULL ; ) {
    if (d->hMF == hMF) {
      d->refCount -- ;
      break ;
      }
    d = d->Next;
    }
  }

static int AnzMFs (void)
  {
  HMFData FAR *d = FirstRec ;
  int res = 0 ;
  for ( ; d != NULL ; ) {
    res ++ ;
    d = d->Next;
    }
  return res ;
  }

static BOOL clearMF (void)
  {
  // den letzen (moeglichen) Record loeschen
  BOOL found = FALSE ;
  HMFData FAR *d = LastRec;

  for ( ; d != NULL ; ) {
    if (d->refCount == 0) {
      DeleteMetaFile (d->hMF);

      // Rausloeschen des Records
      if (d->Prev != NULL) d->Prev->Next = d->Next;
      else                 FirstRec      = d->Next;

      if (d->Next != NULL) d->Next->Prev = d->Prev ;
      else                 LastRec       = d->Prev ;

      FreeGlobMem (d);

      found = TRUE ;
      break ;
      }
    d = d->Prev;
    }
  return found ;
  }


static void InsertMF (WORD PicRec,WORD PicId,HMETAFILE hMF)
  {
  HMFData FAR *d = (HMFData FAR *) GetGlobMem (sizeof(HMFData));
  d->Prev = NULL ;
  d->Next = FirstRec ;
  FirstRec = d ;
  if (LastRec == 0) LastRec = d ;
  d->refCount = 1 ;
  d->PicRec = PicRec ;
  d->PicId = PicId ;
  d->hMF = hMF ;
  if (d->Next) d->Next->Prev = d;
  }

#define MAXRECS 12
DLLExport HMETAFILE _export WINAPI GetHMF (WORD PicRec,WORD PicId)
  {
  HMETAFILE res = GetFromList (PicRec,PicId);
  if (res == 0) {
    // ev. Cache entleeren
    for ( ; (AnzMFs () >= MAXRECS) ; ) {
      if (!clearMF ()) break ;
      }
    // Im Cache nicht gefunden -> Von Datenbank lesen
    DWORD DataSize;
    GLOBALHANDLE hGmem  = ReadResourceData (MAKELONG(PicRec,PicId),&DataSize);
    MtoF (hGmem);

#ifdef WIN32
    res = SetMetaFileBitsEx (UINT(DataSize), (CONST BYTE *)GlobalLock (hGmem));
    GlobalUnlock (hGmem);
#else
    res = SetMetaFileBits (hGmem);
#endif

    InsertMF (PicRec,PicId,res);
    }
  return res ;
  }

DLLExport void _export WINAPI DelHMF (HMETAFILE hMF)
  {
  DecreaseCount (hMF);
  }

DLLExport void _export WINAPI DelAllhMF (void)
  {
  for ( ; clearMF () ; ) ;
  }

