////////////////////////////////////////////////////////////////
// Script-Funktionen fuer Sound-Ein/Ausgabe
//
// $Header:   P:/marille/clinicum/rev/mainsnd.cpv   1.1   18 Oct 1996 17:24:04   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/mainsnd.cpv  $
// 
//    Rev 1.1   18 Oct 1996 17:24:04   GERHOLD
// Anpassungen 32 Bit (Typecast WAVEFORMATEX)
// 
//    Rev 1.0   14 Oct 1996 15:30:34   MARTIN
// Initial revision.
// 
//

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include "dds32.h"
#include "dds.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "globmem.h"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#define MODULENUM 168
#include "winass.hpp"

#include "sound.hpp"


#pragma pack(1)
struct SndDefObj_par {
  WORD parSize;
  DWORD sObj;
  DWORD RecFinished;
  DWORD PlayFinished;
  DWORD DataSize;
  DWORD Channels;
  DWORD SamplesPerSec;
  DWORD BitsPerSample;
  };
#pragma pack()

DLLExport void _export WINAPI SoundCallBack (WORD msg, LPVOID obj)
  {
  LPSOUND so = (LPSOUND)obj;
  mdiChild *mc = (mdiChild *)so->c;
  SndDefObj_par FAR *param = (SndDefObj_par FAR *) so->par;
  WORD FlagTrue = TRUE;

  if (msg == SM_RECFINISHED) {
    mc->WritelData(param->RecFinished,&FlagTrue,sizeof(WORD),NULL);
    }
  if (msg == SM_PLAYFINISHED) {
    mc->WritelData(param->PlayFinished,&FlagTrue,sizeof(WORD),NULL);
    }
  if (msg == SM_DATAINFOCHANGE) {
    DWORD DataSize,SamplesPerSec;
    WORD Channels,BitsPerSample;
    so->GetDataInfo(&DataSize,&Channels,&SamplesPerSec,&BitsPerSample);
    mc->WritelData(param->DataSize,&DataSize,sizeof(DWORD),NULL);
    mc->WritelData(param->Channels,&Channels,sizeof(WORD),NULL);
    mc->WritelData(param->SamplesPerSec,&SamplesPerSec,sizeof(DWORD),NULL);
    mc->WritelData(param->BitsPerSample,&BitsPerSample,sizeof(WORD),NULL);
    }
  }
static SOUNDCB scb = NULL;

BOOL SndDefObj (mdiChild *c,LPVOID param,WORD mode)
  {
  SndDefObj_par FAR *par = (SndDefObj_par FAR *) param;

  if (mode & EM_LOAD) {
    if (scb == NULL)
#ifdef WIN32
      scb = (SOUNDCB)MakeProcInstance(SoundCallBack,WBase::hInstance);
#else
      scb = (SOUNDCB)MakeProcInstance(FARPROC(SoundCallBack),WBase::hInstance);
#endif
    LPSOUND so = new Sound(scb);
    so->c = c;
    so->par = par;
    c->WritelData (par->sObj,&so,sizeof(LPSOUND),LPSTR(param) - sizeof(WORD));
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL)) delete *so;
    c->DellData (par->sObj,LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }


#pragma pack(1)
struct SndClear_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndClear (mdiChild *c,LPVOID param,WORD mode)
  {
  SndClear_par FAR *par = (SndClear_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      (*so)->Clear();
    }

  return FALSE ;
  }


#pragma pack(1)
struct bSndIsEmpty_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL bSndIsEmpty (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = TRUE;
  bSndIsEmpty_par FAR *par = (bSndIsEmpty_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      res = (*so)->IsEmpty();
    }

  return res ;
  }


#pragma pack(1)
struct SndReadWav_par {
  WORD parSize;
  DWORD sObj;
  DWORD fh;
  };
#pragma pack()

BOOL SndReadWav (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndReadWav_par FAR *par = (SndReadWav_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    HFILE FAR * fh = (HFILE FAR *)c->ReadlData(par->fh);
    if ((so != NULL) && (*so != NULL) && (fh != NULL))
      res = (*so)->ReadWav(*fh);
    }

  return res ;
  }


#pragma pack(1)
struct SndWriteWav_par {
  WORD parSize;
  DWORD sObj;
  DWORD fh;
  };
#pragma pack()

BOOL SndWriteWav (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndWriteWav_par FAR *par = (SndWriteWav_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    HFILE FAR * fh = (HFILE FAR *)c->ReadlData(par->fh);
    if ((so != NULL) && (*so != NULL) && (fh != NULL))
      res = (*so)->WriteWav(*fh);
    }

  return res ;
  }


#pragma pack(1)
struct SndPlayStart_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndPlayStart (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndPlayStart_par FAR *par = (SndPlayStart_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      res = (*so)->PlayStart();
    }

  return res ;
  }


#pragma pack(1)
struct SndPause_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndPause (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndPause_par FAR *par = (SndPause_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      res = (*so)->Pause();
    }

  return res ;
  }


#pragma pack(1)
struct SndRestart_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndRestart (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndRestart_par FAR *par = (SndRestart_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      res = (*so)->Restart();
    }

  return res ;
  }


#pragma pack(1)
struct SndPlayStop_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndPlayStop (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndPlayStop_par FAR *par = (SndPlayStop_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL))
      res = (*so)->PlayStop();
    }

  return res ;
  }


#pragma pack(1)
struct SndRecStart_par {
  WORD parSize;
  DWORD sObj;
  DWORD Channels;
  DWORD SamplesPerSec;
  DWORD BitsPerSample;
  DWORD MaxRecBuf;
  };
#pragma pack()

BOOL SndRecStart (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndRecStart_par FAR *par = (SndRecStart_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    LPWORD Channels = (LPWORD)c->ReadlData(par->Channels);
    LPDWORD SamplesPerSec = (LPDWORD)c->ReadlData(par->SamplesPerSec);
    LPWORD BitsPerSample = (LPWORD)c->ReadlData(par->BitsPerSample);
    LPDWORD MaxRecBuf = (LPDWORD)c->ReadlData(par->MaxRecBuf);
    if ((so != NULL) && (*so != NULL) &&
        (Channels != NULL) && (MaxRecBuf != NULL) &&
        (SamplesPerSec != NULL) && (BitsPerSample != NULL)) {
      res = (*so)->RecStart(*Channels,*SamplesPerSec,*BitsPerSample,*MaxRecBuf);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    // nur fuer moegliche Expressions ...
    c->ClearlConnection(par->Channels, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection(par->SamplesPerSec, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection(par->BitsPerSample, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection(par->MaxRecBuf, LPSTR(param) - sizeof(WORD));
    }

  return res ;
  }


#pragma pack(1)
struct SndRecStop_par {
  WORD parSize;
  DWORD sObj;
  };
#pragma pack()

BOOL SndRecStop (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  SndRecStop_par FAR *par = (SndRecStop_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    if ((so != NULL) && (*so != NULL)) {
      res = (*so)->RecStop();
      }
    }

  return res ;
  }


#pragma pack(1)
struct bSndIsCompatible_par {
  WORD parSize;
  DWORD sObj;
  DWORD Channels;
  DWORD SamplesPerSec;
  DWORD BitsPerSample;
  };
#pragma pack()

BOOL bSndIsCompatible (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;
  bSndIsCompatible_par FAR *par = (bSndIsCompatible_par FAR *) param;

  if (mode & EM_LOAD) {
    LPSOUND FAR *so = (LPSOUND FAR *) c->ReadlData (par->sObj);
    LPWORD Channels = (LPWORD)c->ReadlData(par->Channels);
    LPDWORD SamplesPerSec = (LPDWORD)c->ReadlData(par->SamplesPerSec);
    LPWORD BitsPerSample = (LPWORD)c->ReadlData(par->BitsPerSample);
    if ((so != NULL) && (*so != NULL) &&
        (Channels != NULL) && (SamplesPerSec != NULL) && (BitsPerSample != NULL)) {
      res = (*so)->IsCompatible(*Channels,*SamplesPerSec,*BitsPerSample);
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    // nur fuer moegliche Expressions ...
    c->ClearlConnection(par->Channels, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection(par->SamplesPerSec, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection(par->BitsPerSample, LPSTR(param) - sizeof(WORD));
    }

  return res ;
  }

