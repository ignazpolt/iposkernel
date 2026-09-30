// globale Klasse fuer Ein-/Ausgabe von Klangdaten
//
// $Header:   P:/marille/clinicum/image/rev/sound.cpv   1.5   13 Oct 1998 13:44:54   Gerhold  $
// $Log:   P:/marille/clinicum/image/rev/sound.cpv  $
// 
//    Rev 1.5   13 Oct 1998 13:44:54   Gerhold
// VC6 Type Casts
// 
//    Rev 1.4   18 Oct 1996 17:25:12   GERHOLD
// Anpassungen 32 Bit (Typecast WAVEFORMATEX)
// 
//    Rev 1.3   14 Oct 1996 15:29:22   MARTIN
// Sound: erste funktionierende Version
// 
//    Rev 1.2   02 Feb 1996 10:49:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   17 Oct 1994 15:03:02   HANNES
// No change.
// 
//    Rev 1.0   24 Jun 1994 16:51:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   26 Jan 1994 18:46:40   MARTIN
// ent-Dr.Watson-isiert
// 
//    Rev 1.0   20 Jan 1994 12:16:12   MARTIN
// Initial revision.
//

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include "dds32.h"
#include "ddsmsg.h"
#include "sound.hpp"
#define MODULENUM 67
#include "winass.hpp"
#include "globmem.h"

// vorerst darf nur ein Objekt gleichzeitig abspielen bzw. aufnehmen
// (spaeter kann man eine Liste der aktiven Objekte bauen und
// bei einer Multimedia-Message nach Handle suchen)
static LPSOUND soplay = NULL;
static LPSOUND   sorec = NULL;

typedef struct waveInst {
  struct waveInst FAR *next;
  HANDLE hWaveInst;
  HANDLE hWaveHdr;
  LPWAVEHDR lpWaveHdr;
  HANDLE hWaveData;
  } WAVEINST;

typedef WAVEINST FAR *LPWAVEINST;

typedef struct PlayInst {
  struct PlayInst FAR *next;
  char filename[128];
  WORD mode;
  BOOL ReadOK;
  HANDLE hFormat, hData;
  DWORD dwDataSize;
  } PLAYINST;

typedef PLAYINST FAR *LPPLAYINST;

static LPWAVEINST top = NULL;
static LPWAVEINST last = NULL;
static LPPLAYINST playtop = NULL;
static LPPLAYINST playlast = NULL;
static HWAVEOUT wavOut = NULL;
static HWND FrameWnd = NULL;

DLLExport void _export WINAPI SndSetMsgWnd(HWND hWnd)
  {
  HWND oldWnd = FrameWnd;
  FrameWnd = hWnd;
  if (FrameWnd == NULL) {
    SndReset();
    LPPLAYINST pi = playtop;
    while (pi != NULL) {
      LPPLAYINST tofree = pi;
      pi = pi->next;
      if (tofree->ReadOK) {
        GlobalFree( tofree->hFormat );
        GlobalFree( tofree->hData );
        }
      FreeGlobMem(tofree);
      }
    playtop = playlast = NULL;
    if (soplay != NULL) soplay->PlayStop();
    if (sorec != NULL) sorec->RecStop();
    if (oldWnd != NULL) {
      MSG msg;
      while (PeekMessage(&msg, oldWnd, MM_WOM_OPEN, MM_WIM_DATA, PM_REMOVE));
      while (PeekMessage(&msg, oldWnd, WMU_PLAYSOUND, WMU_PLAYSOUND, PM_REMOVE));
      }
    }
  }


BOOL ReadWaveFile(LPSTR szFileName, HANDLE FAR *hFormat, HANDLE FAR *hData, DWORD FAR *dwDataSize, HFILE fh = NULL)
  {
  HMMIO hmmio;
  MMCKINFO mmckinfoParent;
  MMCKINFO mmckinfoSubchunk;
  DWORD dwFmtSize;
  LPWAVEFORMAT lpFormat;
  HPSTR lpData = NULL;

  *hData = NULL;

  /* Open the given file for reading using buffered I/O.
   */
  if (fh == NULL) {
    if(!(hmmio = mmioOpen(szFileName, NULL, MMIO_READ | MMIO_ALLOCBUF)))
      {
      return FALSE;
      }
    }
  else {
    MMIOINFO mi;
    lmemset(&mi,'\0',sizeof(mi));
    mi.fccIOProc = FOURCC_DOS;
    mi.pchBuffer = NULL;
    mi.adwInfo[0] = fh;
    if(!(hmmio = mmioOpen(NULL, &mi, MMIO_READ | MMIO_ALLOCBUF)))
      {
      return FALSE;
      }
    }

  /* Locate a 'RIFF' chunk with a 'WAVE' form type 
   * to make sure it's a WAVE file.
   */
  mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
  if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, NULL, MMIO_FINDRIFF))
    {
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Now, find the format chunk (form type 'fmt '). It should be
   * a subchunk of the 'RIFF' parent chunk.
   */
  mmckinfoSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
  if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, 
      MMIO_FINDCHUNK))
    {
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Get the size of the format chunk, allocate and lock memory for it.
   */
  dwFmtSize = mmckinfoSubchunk.cksize;
  *hFormat = GlobalAlloc(GMEM_MOVEABLE, LOWORD(dwFmtSize));
  if (!*hFormat)
    {
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  lpFormat = (LPWAVEFORMAT) GlobalLock(*hFormat);
  if (!lpFormat)
    {
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Read the format chunk.
   */
  if (mmioRead(hmmio, (HPSTR) lpFormat, dwFmtSize) != (LONG) dwFmtSize)
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Make sure it's a PCM file.
   */
  if (lpFormat->wFormatTag != WAVE_FORMAT_PCM)
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Make sure a waveform output device supports this format.
   */
  if (waveOutOpen(NULL, (UINT)WAVE_MAPPER, 
#ifdef WIN32
                  (LPWAVEFORMATEX)lpFormat, 
#else
                  lpFormat, 
#endif
                  NULL, 0L, (DWORD)WAVE_FORMAT_QUERY))
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Ascend out of the format subchunk.
   */
  mmioAscend(hmmio, &mmckinfoSubchunk, 0);

  /* Find the data subchunk.
   */
  mmckinfoSubchunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
  if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent,
      MMIO_FINDCHUNK))
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Get the size of the data subchunk.
   */
  *dwDataSize = mmckinfoSubchunk.cksize;
  if (*dwDataSize == 0L)
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Allocate and lock memory for the waveform data.
   */
  *hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, *dwDataSize );
  if (!*hData)
    {
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }
  lpData = LPSTR(GlobalLock(*hData));
  if (!lpData)
    {
    GlobalFree( *hData );
    *hData = NULL;
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* Read the waveform data subchunk.
   */
  if(mmioRead(hmmio, (HPSTR) lpData, *dwDataSize) != (LONG) *dwDataSize)
    {
    GlobalUnlock( *hData );
    GlobalFree( *hData );
    *hData = NULL;
    GlobalUnlock( *hFormat );
    GlobalFree( *hFormat );
    *hFormat = NULL;
    mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
    return FALSE;
    }

  /* We're done with the file, close it.
   */
  mmioClose(hmmio, (fh == NULL) ? 0 : MMIO_FHOPEN);
  GlobalUnlock( *hFormat );
  GlobalUnlock( *hData );

  return TRUE;
  }


BOOL AddNewWaveBlock(HANDLE hData, DWORD dwDataSize)
  {
  HPSTR lpData = NULL;
  LPWAVEHDR lpWaveHdr;
  HANDLE hWaveHdr;
  HANDLE hWaveInst;
  LPWAVEINST lpWaveInst;

  /* Allocate a waveform data header. The WAVEHDR must be 
   * globally allocated and locked.
   */
  hWaveHdr = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,
                         (DWORD) sizeof(WAVEHDR));
  if (!hWaveHdr)
    {
    return FALSE;
    }
  lpWaveHdr = (LPWAVEHDR) GlobalLock(hWaveHdr);
  if (!lpWaveHdr)
    {
    GlobalFree( hWaveHdr );
    return FALSE;
    }

  /* Allocate and set up instance data for waveform data block.
   * This information is needed by the routine that frees the
   * data block after it has been played.
   */
  hWaveInst = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,
                          (DWORD) sizeof(WAVEINST));
  if (!hWaveInst)
    {
    GlobalUnlock( hWaveHdr );
    GlobalFree( hWaveHdr );
    return FALSE;
    }
  lpWaveInst = (LPWAVEINST) GlobalLock(hWaveInst);
  if (!lpWaveInst)
    {
    GlobalUnlock( hWaveHdr );
    GlobalFree( hWaveHdr );
    GlobalFree( hWaveInst );
    return FALSE;
    }
  lpWaveInst->next = NULL;
  lpWaveInst->hWaveInst = hWaveInst;
  lpWaveInst->hWaveHdr = hWaveHdr;
  lpWaveInst->lpWaveHdr = lpWaveHdr;
  lpWaveInst->hWaveData = hData;

  lpData = LPSTR(GlobalLock(hData));
  if (!lpData)
    {
    GlobalUnlock( hWaveHdr );
    GlobalFree( hWaveHdr );
    GlobalUnlock( hWaveInst );
    GlobalFree( hWaveInst );
    return FALSE;
    }

  /* Set up WAVEHDR structure and prepare it to be written to wave device.
   */
  lpWaveHdr->lpData = lpData;
  lpWaveHdr->dwBufferLength = dwDataSize;
  lpWaveHdr->dwFlags = 0L;
  lpWaveHdr->dwLoops = 0L;
  lpWaveHdr->dwUser = (DWORD) lpWaveInst;
  if(waveOutPrepareHeader(wavOut, lpWaveHdr, sizeof(WAVEHDR)))
    {
    GlobalUnlock( hData );
    GlobalUnlock( hWaveHdr );
    GlobalFree( hWaveHdr );
    GlobalUnlock( hWaveInst );
    GlobalFree( hWaveInst );
    return FALSE;
    }
      
  /* Then the data block can be sent to the output device.
   */
  if (waveOutWrite(wavOut, lpWaveHdr, sizeof(WAVEHDR)) != 0)
    {
    waveOutUnprepareHeader( wavOut, lpWaveHdr, sizeof(WAVEHDR));
    GlobalUnlock( hData );
    GlobalUnlock( hWaveHdr );
    GlobalFree( hWaveHdr );
    GlobalUnlock( hWaveInst );
    GlobalFree( hWaveInst );
    return FALSE;
    }

  // jetzt noch in Liste der aktiven Bloecke einhaengen
  if (last != NULL)
    last->next = lpWaveInst;
  else
    top = lpWaveInst;
  last = lpWaveInst;

  return TRUE;
  }


DLLExport void _export WINAPI SndReset(void)
  {
  if (wavOut != NULL) {
    waveOutReset(wavOut);
    if (FrameWnd != NULL) {
      MSG msg;
      while (PeekMessage(&msg, FrameWnd, MM_WOM_OPEN, MM_WOM_DONE, PM_REMOVE)) {
        if (wavOut != (HWAVEOUT)msg.wParam)
          SndOnSoundMsg(msg.message,msg.wParam,msg.lParam);
        };
      }
    LPWAVEINST tofree = top;
    while (tofree != NULL) {
      LPWAVEINST next = tofree->next;
      waveOutUnprepareHeader(wavOut, tofree->lpWaveHdr, sizeof(WAVEHDR) );
      GlobalUnlock( tofree->hWaveData );
      GlobalFree( tofree->hWaveData );
      GlobalUnlock( tofree->hWaveHdr );
      GlobalFree( tofree->hWaveHdr );
      HANDLE insttofree = tofree->hWaveInst;
      GlobalUnlock( insttofree );
      GlobalFree( insttofree );
      tofree = next;
      }
    top = NULL;
    last = NULL;
    waveOutClose(wavOut);
    wavOut = NULL;
    }
  }


static BOOL InClearQueue = FALSE;
static BOOL NextMessageHere;

static void OnPlaySoundMsg(void)
  {
  WIN_ASSERT(!InClearQueue);
  for (LPPLAYINST pi = playtop; pi != NULL; pi = pi->next) {
    pi->ReadOK = ReadWaveFile(pi->filename, &pi->hFormat, &pi->hData, &pi->dwDataSize);
    NextMessageHere = FALSE;
    InClearQueue = TRUE;
    ClearQueue();
    InClearQueue = FALSE;
    if (FrameWnd == NULL)  // Programm beendet
      return;
    if (NextMessageHere) {
      PostMessage(FrameWnd, WMU_PLAYSOUND, 0, 0L);
      return;
      }
    }
  pi = playtop;
  while (pi != NULL) {
    if (!(pi->mode & SPW_DONTSTOPLAST))
      SndReset();
    if (pi->ReadOK) {
      LPWAVEFORMAT lpFormat = (LPWAVEFORMAT)GlobalLock(pi->hFormat);
      if (wavOut == NULL) {
        /* Open a waveform output device.
        */
        if (waveOutOpen(&wavOut, WAVE_MAPPER, 
#ifdef WIN32
                        (LPWAVEFORMATEX)lpFormat, 
#else
                        lpFormat, 
#endif
                        (UINT)FrameWnd, 0L, (DWORD)CALLBACK_WINDOW))
          wavOut = NULL;
        }
      GlobalUnlock( pi->hFormat );
      GlobalFree( pi->hFormat );
      if ((wavOut == NULL) || (!AddNewWaveBlock(pi->hData, pi->dwDataSize)))
        GlobalFree( pi->hData );
      }
    LPPLAYINST tofree = pi;
    pi = pi->next;
    FreeGlobMem(tofree);
    }
  playtop = playlast = NULL;
  }


DLLExport void _export WINAPI SndPlayWav(LPSTR filename, WORD mode)
  {
  WIN_ASSERT(FrameWnd != NULL);
  LPPLAYINST playnew = (LPPLAYINST)GetGlobMem(sizeof(PLAYINST));
  playnew->next = NULL;
  lstrcpy(playnew->filename, filename);
  playnew->mode = mode;
  playnew->ReadOK = FALSE;
  playnew->hFormat = NULL;
  playnew->hData = NULL;
  playnew->dwDataSize = 0L;
  if (playtop == NULL) {
    WIN_ASSERT(!InClearQueue);
    PostMessage(FrameWnd, WMU_PLAYSOUND, 0, 0L);
    }
  if (mode & SPW_DONTSTOPLAST) {
    if (playtop == NULL)
      playtop = playnew;
    else
      playlast->next = playnew;
    playlast = playnew;
    }
  else {
    LPPLAYINST pi = playtop;
    while (pi != NULL) {
      LPPLAYINST tofree = pi;
      pi = pi->next;
      if (tofree->ReadOK) {
        GlobalFree( tofree->hFormat );
        GlobalFree( tofree->hData );
        }
      FreeGlobMem(tofree);
      }
    playtop = playlast = playnew;
    if (InClearQueue)
      NextMessageHere = TRUE;
    }
  }


DLLExport void _export WINAPI SndOnSoundMsg(UINT msg, WPARAM wP, LPARAM lP)
  {
  WIN_ASSERT(FrameWnd != NULL);
  LPWAVEINST tofree;
  switch (msg) {
    case WMU_PLAYSOUND:
      OnPlaySoundMsg();
      break;
    case MM_WOM_DONE:
      if (wavOut == (HWAVEOUT)wP) {
        /* This message indicates a waveform data block has
        * been played and can be freed. Clean up the preparation
        * done previously on the header.
        */
        waveOutUnprepareHeader( wavOut,
                                (LPWAVEHDR) lP, sizeof(WAVEHDR) );

        /* Get a pointer to the instance data, then unlock and free
        * all memory associated with the data block, including the
        * memory for the instance data itself.
        */
        tofree = (LPWAVEINST) ((LPWAVEHDR)lP)->dwUser;
        WIN_ASSERT(tofree->lpWaveHdr == (LPWAVEHDR) lP);
        WIN_ASSERT(top == tofree);  // sollte als erster fertig sein
        if (top == tofree) {
          top = top->next;
          GlobalUnlock( tofree->hWaveData );
          GlobalFree( tofree->hWaveData );
          GlobalUnlock( tofree->hWaveHdr );
          GlobalFree( tofree->hWaveHdr );
          HANDLE insttofree = tofree->hWaveInst;
          GlobalUnlock( insttofree );
          GlobalFree( insttofree );
          }
        if (top == NULL) {
          /* Close the waveform output device.
          */
          waveOutClose( wavOut );
          wavOut = NULL;
          last = NULL;
          }
        }
      else if ((soplay != NULL) && (soplay->hPlay == (HWAVEOUT)wP)) {
        soplay->OnWomDone(lP);
        }
      else {
        WIN_ASSERT(FALSE);
        }
      break;
    case MM_WIM_DATA:
      if ((sorec != NULL) && (HWAVEIN(sorec->hRec) == (HWAVEIN) wP)) {
        sorec->OnWimData(lP);
        }
      else {
        WIN_ASSERT(FALSE);
        }
      break;
    case MM_WIM_OPEN:
    case MM_WIM_CLOSE:
    case MM_WOM_OPEN:
    case MM_WOM_CLOSE:
      // ignorieren
      break;
    default:
      WIN_ASSERT(FALSE);
    }
  }


// Implementierung der Klasse Sound
///////////////////////////////////

DLLExport LPVOID _export WINAPI Sound::operator new (size_t size)
  {
  LPVOID res = GetGlobMem (size);
  if (res == NULL) {
    DBWIN_ASSERT(FALSE);
    }
  return res;
  }

DLLExport void _export WINAPI Sound::operator delete (LPVOID object)
  {
  FreeGlobMem (object);
  }

DLLExport _export WINAPI Sound::Sound (SOUNDCB SoundCallBack)
  {
  scb = SoundCallBack;
  }

DLLExport _export WINAPI Sound::~Sound ()
  {
  scb = NULL;
  Clear();
  }

DLLExport void _export WINAPI Sound::Clear (void)
  {
  if (hPlay != NULL) PlayStop();
  if (hRec != NULL) RecStop();
  if (hData != NULL) {
    GlobalFree(hData), hData = NULL;
    if (scb != NULL)
      (*scb)(SM_DATAINFOCHANGE,this);
    }
  }

DLLExport BOOL _export WINAPI Sound::IsEmpty (void)
  {
  return (hData == NULL);
  }

DLLExport BOOL _export WINAPI Sound::ReadWav (HFILE fh)
  {
  Clear();
  GLOBALHANDLE hFormat;
  BOOL ReadOK = ReadWaveFile(NULL, &hFormat, &hData, &DataSize, fh);
  if (ReadOK) {
    LPPCMWAVEFORMAT lpFormat = (LPPCMWAVEFORMAT)GlobalLock(hFormat);
    actChannels = lpFormat->wf.nChannels;
    actSamplesPerSecond = lpFormat->wf.nSamplesPerSec;
    actBitsPerSample = lpFormat->wBitsPerSample;
    (*scb)(SM_DATAINFOCHANGE,this);
    }

  return ReadOK;
  }

DLLExport BOOL _export WINAPI Sound::WriteWav (HFILE fh)
  {
  BOOL res = FALSE;
  if (hRec != NULL) RecStop();
  if (hData) {
    MMIOINFO mi;
    lmemset(&mi,'\0',sizeof(mi));
    mi.fccIOProc = FOURCC_DOS;
    mi.pchBuffer = NULL;
    mi.adwInfo[0] = fh;
    HMMIO hmmioOut = mmioOpen(NULL, &mi, MMIO_WRITE | MMIO_ALLOCBUF);
    if (hmmioOut) {
      MMCKINFO ckOutRIFF;
      ckOutRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
      ckOutRIFF.cksize  = 0L;
      if (!mmioCreateChunk(hmmioOut, &ckOutRIFF, MMIO_CREATERIFF)) {
        MMCKINFO ckOut;
        ckOut.ckid   = mmioFOURCC('f', 'm', 't', ' ');
        ckOut.cksize = sizeof(PCMWAVEFORMAT);
        if (!mmioCreateChunk(hmmioOut, &ckOut, 0)) {
          PCMWAVEFORMAT wf;
          wf.wf.wFormatTag = WAVE_FORMAT_PCM;
          wf.wf.nChannels = actChannels;
          wf.wf.nSamplesPerSec = actSamplesPerSecond;
          wf.wf.nAvgBytesPerSec = (actChannels * actSamplesPerSecond * actBitsPerSample) / 8L;
          wf.wf.nBlockAlign = (actChannels * actBitsPerSample) / 8;
          wf.wBitsPerSample = actBitsPerSample;
          if (mmioWrite(hmmioOut, (HPSTR)&wf, sizeof(PCMWAVEFORMAT)) == (LONG)sizeof(PCMWAVEFORMAT)) {
            if (!mmioAscend(hmmioOut, &ckOut, 0)) {
              ckOut.ckid = mmioFOURCC('d', 'a', 't', 'a');
              ckOut.cksize = 0L;
              if (!mmioCreateChunk(hmmioOut, &ckOut, 0)) {
                HPSTR hpData = (HPSTR)GlobalLock(hData);
                if (mmioWrite(hmmioOut, hpData, DataSize) == (LONG)DataSize) {
                  res = TRUE;
                  }
                GlobalUnlock(hData);
                mmioAscend(hmmioOut, &ckOut, 0);
                }
              }
            }
          else {
            mmioAscend(hmmioOut, &ckOut, 0);
            }
          }
        mmioAscend(hmmioOut, &ckOutRIFF, 0);
        }
      mmioClose(hmmioOut, MMIO_FHOPEN);
      }
    }
  return res;
  }

DLLExport BOOL _export WINAPI Sound::PlayStart (void)
  {
  BOOL res = FALSE;
  if (hPlay != NULL) PlayStop();
  if (soplay != NULL) soplay->PlayStop();
  soplay = this;
  if (hData != NULL) {
    PCMWAVEFORMAT wf;
    wf.wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.wf.nChannels = actChannels;
    wf.wf.nSamplesPerSec = actSamplesPerSecond;
    wf.wf.nAvgBytesPerSec = (actChannels * actSamplesPerSecond * actBitsPerSample) / 8L;
    wf.wf.nBlockAlign = (actChannels * actBitsPerSample) / 8;
    wf.wBitsPerSample = actBitsPerSample;
    if (waveOutOpen(&hPlay, WAVE_MAPPER, 
#ifdef WIN32
                    (LPWAVEFORMATEX)&wf,
#else
                    (LPWAVEFORMAT)&wf,
#endif
                    (UINT)FrameWnd, 0L, (DWORD)CALLBACK_WINDOW) == 0) {
      res = TRUE;
      for (int i = 0; res && (i < PLAYBUFMAX) && (PlayOffset < DataSize); i++) {
        PlayHdr[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,(DWORD)sizeof(WAVEHDR));
        LPWAVEHDR lpWaveHdr = (LPWAVEHDR)GlobalLock(PlayHdr[i]);
        PlayBuf[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,(DWORD)PLAYBUFSIZE);
        lpWaveHdr->lpData = (LPSTR)GlobalLock(PlayBuf[i]);
        lpWaveHdr->dwFlags = 0L;
        lpWaveHdr->dwLoops = 0L;
        if (!SendDataBlock(lpWaveHdr))
          res = FALSE;
        }
      }
    }
  return res;
  }

DLLExport BOOL _export WINAPI Sound::SendDataBlock (LPWAVEHDR wh)
  {
  BOOL res = FALSE;
  wh->dwBufferLength = DataSize - PlayOffset;
  if (wh->dwBufferLength > PLAYBUFSIZE)
    wh->dwBufferLength = PLAYBUFSIZE;
  HPSTR hpData = (HPSTR)GlobalLock(hData);
  hmemcpy(wh->lpData, hpData + PlayOffset, wh->dwBufferLength);
  GlobalUnlock(hData);
  PlayOffset += wh->dwBufferLength;
  wh->dwUser = (PlayOffset >= DataSize);
  if ((waveOutPrepareHeader(hPlay, wh, sizeof(WAVEHDR)) == 0) &&
      (waveOutWrite(hPlay, wh, sizeof(WAVEHDR)) == 0))
    res = TRUE;
  if (!res) PlayStop();
  return res;
  }

DLLExport void _export WINAPI Sound::OnWomDone (LPARAM lP)
  {
  LPWAVEHDR wh = (LPWAVEHDR)lP;
  waveOutUnprepareHeader(hPlay, wh, sizeof(WAVEHDR));
  if (wh->dwUser != 0L)
    PlayStop();
  else if (PlayOffset < DataSize)
    SendDataBlock(wh);
  }

DLLExport BOOL _export WINAPI Sound::Pause (void)
  {
  BOOL res = FALSE;
  if (hPlay) {
    res = (waveOutPause(hPlay) == 0);
    }
  return res;
  }

DLLExport BOOL _export WINAPI Sound::Restart (void)
  {
  BOOL res = FALSE;
  if (hPlay) {
    res = (waveOutRestart(hPlay) == 0);
    }
  return res;
  }

DLLExport BOOL _export WINAPI Sound::PlayStop (void)
  {
  BOOL res = FALSE;
  if (hPlay) {
    waveOutReset(hPlay);
    MSG msg;
    while (PeekMessage(&msg, FrameWnd, MM_WOM_OPEN, MM_WOM_DONE, PM_REMOVE)) {
      if (hPlay == (HWAVEOUT)msg.wParam) {
        if (msg.message == MM_WOM_DONE)
          waveOutUnprepareHeader(hPlay, (LPWAVEHDR)msg.lParam, sizeof(WAVEHDR));
        }
      else
        SndOnSoundMsg(msg.message,msg.wParam,msg.lParam);
      };
    for (int i = 0; i < PLAYBUFMAX; i++) {
      if (PlayHdr[i]) {
        GlobalUnlock(PlayHdr[i]);
        GlobalFree(PlayHdr[i]);
        PlayHdr[i] = NULL;
        }
      if (PlayBuf[i]) {
        GlobalUnlock(PlayBuf[i]);
        GlobalFree(PlayBuf[i]);
        PlayBuf[i] = NULL;
        }
      }
    waveOutClose(hPlay);
    PlayOffset = 0L;
    hPlay = NULL;
    (*scb)(SM_PLAYFINISHED,this);
    res = TRUE;
    }
  if (soplay == this) soplay = NULL;
  return res;
  }

DLLExport BOOL _export WINAPI Sound::RecStart (WORD Channels,
                                               DWORD SamplesPerSecond,
                                               WORD BitsPerSample,
                                               DWORD MaxRecBuf)
  {
  BOOL res = FALSE;
  if (hRec != NULL) RecStop();
  if (sorec != NULL) sorec->RecStop();
  sorec = this;
  if (hData == NULL) {
    actChannels = Channels;
    actSamplesPerSecond = SamplesPerSecond;
    actBitsPerSample = BitsPerSample;
    }
  MaxRecLen = MaxRecBuf;
  PCMWAVEFORMAT wf;
  wf.wf.wFormatTag = WAVE_FORMAT_PCM;
  wf.wf.nChannels = actChannels;
  wf.wf.nSamplesPerSec = actSamplesPerSecond;
  wf.wf.nAvgBytesPerSec = (actChannels * actSamplesPerSecond * actBitsPerSample) / 8L;
  wf.wf.nBlockAlign = (actChannels * actBitsPerSample) / 8;
  wf.wBitsPerSample = actBitsPerSample;
  if (waveInOpen(&hRec, WAVE_MAPPER, 
#ifdef WIN32
                (LPWAVEFORMATEX)&wf,
#else
                (LPWAVEFORMAT)&wf,
#endif

                 (UINT)FrameWnd, 0L, (DWORD)CALLBACK_WINDOW) == 0) {
    res = TRUE;
    for (int i = 0; res && (i < RECBUFMAX); i++) {
      RecHdr[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,(DWORD)sizeof(WAVEHDR));
      LPWAVEHDR lpWaveHdr = (LPWAVEHDR)GlobalLock(RecHdr[i]);
      RecBuf[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,(DWORD)RECBUFSIZE);
      lpWaveHdr->lpData = (LPSTR)GlobalLock(RecBuf[i]);
      lpWaveHdr->dwBufferLength = RECBUFSIZE;
      lpWaveHdr->dwBytesRecorded = 0L;
      lpWaveHdr->dwUser = 0L;
      lpWaveHdr->dwFlags = 0L;
      lpWaveHdr->dwLoops = 0L;
      if ((waveInPrepareHeader(hRec, lpWaveHdr, sizeof(WAVEHDR)) != 0) ||
          (waveInAddBuffer(hRec, lpWaveHdr, sizeof(WAVEHDR)) != 0)) {
        RecStop();
        res = FALSE;
        }
      }
    if (res) {
      if (waveInStart(hRec) != 0) {
        RecStop();
        res = FALSE;
        }
      }
    }
  return res;
  }

DLLExport void _export WINAPI Sound::OnWimData (LPARAM lP)
  {
  BOOL StopMe = FALSE;
  LPWAVEHDR wh = (LPWAVEHDR)lP;
  waveInUnprepareHeader(hRec, wh, sizeof(WAVEHDR));
  if (wh->dwBytesRecorded > 0L) {
    DWORD oldDataSize;
    GLOBALHANDLE hNewData;
    if (hData == NULL) {
      oldDataSize = 0L;
      DataSize = wh->dwBytesRecorded;
      hNewData = GlobalAlloc(GMEM_MOVEABLE,DataSize);
      }
    else {
      oldDataSize = DataSize;
      DataSize += wh->dwBytesRecorded;
      hNewData = GlobalReAlloc(hData,DataSize,GMEM_MOVEABLE);
      }
    if (hNewData) {
      hData = hNewData;
      HPSTR hpData = (HPSTR)GlobalLock(hData);
      hmemcpy(hpData + oldDataSize, wh->lpData, wh->dwBytesRecorded);
      GlobalUnlock(hData);
      (*scb)(SM_DATAINFOCHANGE,this);
      }
    else {
      DataSize = oldDataSize;
      StopMe = TRUE;
      }
    if ((MaxRecLen > 0L) && (DataSize > MaxRecLen))
      StopMe = TRUE;
    }
  if (!InRecStop) {
    if (StopMe) {
      RecStop();
      }
    else {
      wh->dwBufferLength = RECBUFSIZE;
      wh->dwBytesRecorded = 0L;
      wh->dwUser = 0L;
      wh->dwFlags = 0L;
      wh->dwLoops = 0L;
      if ((waveInPrepareHeader(hRec, wh, sizeof(WAVEHDR)) != 0) ||
          (waveInAddBuffer(hRec, wh, sizeof(WAVEHDR)) != 0)) {
        RecStop();
        }
      }
    }
  }

DLLExport BOOL _export WINAPI Sound::RecStop (void)
  {
  BOOL res = FALSE;
  if (hRec) {
    waveInReset(hRec);
    MSG msg;
    InRecStop = TRUE;
    while (PeekMessage(&msg, FrameWnd, MM_WIM_OPEN, MM_WIM_DATA, PM_REMOVE))
      SndOnSoundMsg(msg.message,msg.wParam,msg.lParam);
    InRecStop = FALSE;
    for (int i = 0; i < RECBUFMAX; i++) {
      if (RecHdr[i]) {
        GlobalUnlock(RecHdr[i]);
        GlobalFree(RecHdr[i]);
        RecHdr[i] = NULL;
        }
      if (RecBuf[i]) {
        GlobalUnlock(RecBuf[i]);
        GlobalFree(RecBuf[i]);
        RecBuf[i] = NULL;
        }
      }
    waveInClose(hRec);
    hRec = NULL;
    (*scb)(SM_RECFINISHED,this);
    res = TRUE;
    }
  if (sorec == this) sorec = NULL;
  return res;
  }

DLLExport BOOL _export WINAPI Sound::IsCompatible (WORD Channels,
                                                   DWORD SamplesPerSecond,
                                                   WORD BitsPerSample)
  {
  return (hData == NULL) ||
         ((Channels == actChannels) &&
          (SamplesPerSecond == actSamplesPerSecond) &&
          (BitsPerSample == actBitsPerSample));
  }

DLLExport void _export WINAPI Sound::SetDataHandle(GLOBALHANDLE hNewData)
  {
  Clear();
  hData = hNewData;
  }

DLLExport GLOBALHANDLE _export WINAPI Sound::GetDataHandle(void)
  {
  return hData;
  }

DLLExport void _export WINAPI Sound::GetDataInfo(LPDWORD Size,
                                                 LPWORD Channels,
                                                 LPDWORD SamplesPerSec,
                                                 LPWORD BitsPerSample)
  {
  if (hData == NULL) {
    *Size = 0L;
    *Channels = 0;
    *SamplesPerSec = 0L;
    *BitsPerSample = 0;
    }
  else {
    *Size = DataSize;
    *Channels = actChannels;
    *SamplesPerSec = actSamplesPerSecond;
    *BitsPerSample = actBitsPerSample;
    }
  }

