// globale Klasse fuer Ein-/Ausgabe von Klangdaten
//
// $Header:   P:/marille/clinicum/include/rev/sound.hpv   1.2   14 Oct 1996 15:29:12   MARTIN  $
// $Log:   P:/marille/clinicum/include/rev/sound.hpv  $
// 
//    Rev 1.2   14 Oct 1996 15:29:12   MARTIN
// Sound: erste funktionierende Version
// 
//    Rev 1.1   02 Feb 1996 10:59:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:02:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   20 Jan 1994 12:14:02   MARTIN
// Initial revision.
//

DLLExport void _export WINAPI SndReset(void); // unterbricht alle bisherigen Sounds
DLLExport void _export WINAPI SndSetMsgWnd(HWND hWnd);  // HWND der FrameWndProc
DLLExport void _export WINAPI SndOnSoundMsg(UINT msg, WPARAM wP, LPARAM lP);
DLLExport void _export WINAPI SndPlayWav(LPSTR filename, WORD mode); // siehe SPW_*
#define SPW_NORMAL        0x0000
#define SPW_SYNC          0x0001
#define SPW_DONTSTOPME    0x0002
#define SPW_DONTSTOPLAST  0x0004


// Klasse Sound:
////////////////

typedef void (WINAPI * SOUNDCB) (WORD msg, LPVOID obj);
#define SM_RECFINISHED     0
#define SM_PLAYFINISHED    1
#define SM_DATAINFOCHANGE  2

#define PLAYBUFMAX  3
#define PLAYBUFSIZE 16384
#define RECBUFMAX   3
#define RECBUFSIZE  16384

class FAR Sound {
 private:
  SOUNDCB scb;
  GLOBALHANDLE hData;
  DWORD DataSize;
  WORD actChannels;
  DWORD actSamplesPerSecond;
  WORD actBitsPerSample;
  DWORD MaxRecLen;
  HWAVEOUT hPlay;
  DWORD PlayOffset;
  GLOBALHANDLE PlayHdr[PLAYBUFMAX];
  GLOBALHANDLE PlayBuf[PLAYBUFMAX];
  HWAVEIN hRec;
  GLOBALHANDLE RecHdr[RECBUFMAX];
  GLOBALHANDLE RecBuf[RECBUFMAX];
  BOOL InRecStop;
 public:
  LPVOID c;
  LPVOID par;
  DLLExport LPVOID _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (LPVOID object);
  DLLExport _export WINAPI Sound (SOUNDCB SoundCallBack);
  DLLExport _export WINAPI ~Sound ();
  DLLExport void _export WINAPI Clear (void);
  DLLExport BOOL _export WINAPI IsEmpty (void);
  DLLExport BOOL _export WINAPI ReadWav (HFILE fh);
  DLLExport BOOL _export WINAPI WriteWav (HFILE fh);
  DLLExport BOOL _export WINAPI PlayStart (void);
  DLLExport BOOL _export WINAPI SendDataBlock (LPWAVEHDR wh);
  DLLExport void _export WINAPI OnWomDone (LPARAM lP);
  DLLExport BOOL _export WINAPI Pause (void);
  DLLExport BOOL _export WINAPI Restart (void);
  DLLExport BOOL _export WINAPI PlayStop (void);
  DLLExport BOOL _export WINAPI RecStart (WORD Channels,
                                          DWORD SamplesPerSecond,
                                          WORD BitsPerSample,
                                          DWORD MaxRecBuf);
  DLLExport void _export WINAPI OnWimData (LPARAM lP);
  DLLExport BOOL _export WINAPI RecStop (void);
  DLLExport BOOL _export WINAPI IsCompatible (WORD Channels,
                                              DWORD SamplesPerSecond,
                                              WORD BitsPerSample);
  DLLExport void _export WINAPI SetDataHandle(GLOBALHANDLE hNewData);
  DLLExport GLOBALHANDLE _export WINAPI GetDataHandle(void);
  DLLExport void _export WINAPI GetDataInfo(LPDWORD Size,
                                            LPWORD Channels,
                                            LPDWORD SamplesPerSec,
                                            LPWORD BitsPerSample);

  friend DLLExport void _export WINAPI SndOnSoundMsg(UINT msg, WPARAM wP, LPARAM lP);
  };
typedef Sound FAR *LPSOUND;

