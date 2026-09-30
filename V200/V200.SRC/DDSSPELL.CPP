/////////////////////////////////////////////////////////////////////////////
// Rechtschreibpr�fung
/////////////////////////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/rev/ddsspell.cpv   1.2   30 Mar 2000 11:10:56   Wolfgang  $
// $Log:   P:/marille/clinicum/rev/ddsspell.cpv  $
// 
//    Rev 1.2   30 Mar 2000 11:10:56   Wolfgang
// 1.) Ein paar ClearlConnections hier und da machen sich auch ganz gut.
// 
//    Rev 1.1   27 Jun 1999 21:56:32   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.0   16 Mar 1999 16:51:24   Gerhold
// Initial revision.
//

#include <windows.h>

#include "dds32.h"

#define MODULENUM  190

#include "dds.hpp"
#include "winass.hpp"
#include "globmem.h"

#include "csapi.h"
#include "cspell.h"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "image.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
                       
#include "scripthd.hpp"
#include "mdichild.hpp"



CSpellSession *pspell = NULL;


static BOOL bSpellInitialized = FALSE;


BOOL InitializeSpelling ()
  {
  pspell = new CSpellSession;
  if (pspell != NULL) {
    pspell->InitFromRegistry ();
    return TRUE;
    }
  else {
    DBWIN_ASSERT_TEXT (FALSE, "Die Rechtschreibpr�fung kann nicht initialisiert werden");
    return FALSE;
    }
  }



//****************************************************************************
//*
//* CheckBuffer
//*
//****************************************************************************
#pragma pack(1)
struct checkbuffer_param {
  WORD parSize;
  DWORD CurrentText;
  DWORD SpellCheckResult;
  DWORD ErrorPos;
  DWORD SpellState;
  DWORD Change;
  DWORD ErrorLength;
  };
#pragma pack()

BOOL CheckBuffer (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    checkbuffer_param FAR *par = (checkbuffer_param FAR *) param;


    if (!bSpellInitialized) {
      if (!InitializeSpelling ())
        return FALSE;

      bSpellInitialized = TRUE;
      }

    if (pspell) {
      UINT nErrorPos;
      UINT nErrorLength;
      char szChange[100];   // Ein Wort das laenger als 100 Zeichen ist????? Ne ne!!!!
      SCRS scrs;

      LPSTR lpszCurrentText = LPSTR (c->ReadlData (par->CurrentText));
      WORD FAR *nSpellState = (WORD FAR *)(c->ReadlData (par->SpellState));

      if ((lpszCurrentText == NULL) || (nSpellState == NULL)) {
        DBWIN_ASSERT_TEXT (FALSE, "Ung�ltige Parameter fur Rechtschreibpr�fung (CheckBuffer)");
        return FALSE;
        }

      if (!pspell->CheckBuffer (lpszCurrentText, &scrs, &nErrorPos, *nSpellState, szChange, &nErrorLength))
        DBWIN_ASSERT_TEXT (FALSE, "Rechtschreibpr�fung (CheckBuffer). Fehlerhafter Aufruf");


      c->WritelData (par->SpellCheckResult, &scrs, sizeof(scrs), LPSTR(param) - sizeof(WORD));
      c->WritelData (par->ErrorPos, &nErrorPos, sizeof(nErrorPos), LPSTR(param) - sizeof(WORD));
      c->WritelData (par->Change, szChange, lstrlen(szChange) + 1, LPSTR(param) - sizeof(WORD));
      c->WritelData (par->ErrorLength, &nErrorLength, sizeof(nErrorLength), LPSTR(param) - sizeof(WORD));
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    checkbuffer_param FAR *par = (checkbuffer_param FAR *) param;
    c->ClearlConnection (par->CurrentText, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->SpellState, LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }



//****************************************************************************
//*
//* SpellSuggestion
//*
//****************************************************************************
#pragma pack(1)
struct suggestion_param {
  WORD parSize;
  DWORD CurrentWord;
  DWORD Suggestions;
  DWORD SpellState;
  DWORD MaxEntryNum;
  };
#pragma pack()

BOOL SpellSuggestion (mdiChild *c,LPVOID param,WORD mode)
  {
  suggestion_param FAR *par = (suggestion_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      LPSTR lpszCurrentWord = LPSTR (c->ReadlData (par->CurrentWord));
      WORD FAR *nSpellState = (WORD FAR *)(c->ReadlData (par->SpellState));
      DBINT FAR *lpMaxEntryNum = (DBINT FAR *)(c->ReadlData (par->MaxEntryNum));
      //----------------------------------------------------------------------
      // lpszSuggestion wird in der folgenden Funktion alloziert.
      // D.h. nach dem WritelData mu� dieser String wieder freigegeben werden
      //----------------------------------------------------------------------
      LPSTR lpszSuggestion;

      pspell->Suggestion (lpszCurrentWord, &lpszSuggestion, *nSpellState, *lpMaxEntryNum);

      c->WritelData (par->Suggestions, lpszSuggestion, GetBlockSize(lpszSuggestion), LPSTR(param) - sizeof(WORD));
      FreeGlobMem (lpszSuggestion);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->CurrentWord, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->SpellState, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->MaxEntryNum, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }



//****************************************************************************
//*
//* SpellAnagram
//*
//****************************************************************************
#pragma pack(1)
struct anagram_param {
  WORD parSize;
  DWORD CurrentWord;
  DWORD Anagram;
  DWORD MaxEntryNum;
  };
#pragma pack()

BOOL SpellAnagram (mdiChild *c,LPVOID param,WORD mode)
  {
  anagram_param FAR *par = (anagram_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      LPSTR lpszCurrentWord = LPSTR (c->ReadlData (par->CurrentWord));
      DBINT FAR *lpMaxEntryNum = (DBINT FAR *)(c->ReadlData (par->MaxEntryNum));
      //----------------------------------------------------------------------
      // lpszSuggestion wird in der folgenden Funktion alloziert.
      // D.h. nach dem WritelData mu� dieser String wieder freigegeben werden
      //----------------------------------------------------------------------
      LPSTR lpszAnagram;

      if (lpszCurrentWord) {
        pspell->Anagram (lpszCurrentWord, &lpszAnagram, *lpMaxEntryNum);

        c->WritelData (par->Anagram, lpszAnagram, GetBlockSize(lpszAnagram), LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->Anagram, LPSTR(param) - sizeof(WORD));
      FreeGlobMem (lpszAnagram);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->CurrentWord, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->MaxEntryNum, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellWildcard
//*
//****************************************************************************
#pragma pack(1)
struct wildcard_param {
  WORD parSize;
  DWORD CurrentWord;
  DWORD Wildcard;
  DWORD MaxEntryNum;
  };
#pragma pack()

BOOL SpellWildcard (mdiChild *c,LPVOID param,WORD mode)
  {
  wildcard_param FAR *par = (wildcard_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      LPSTR lpszCurrentWord = LPSTR (c->ReadlData (par->CurrentWord));
      DBINT FAR *lpMaxEntryNum = (DBINT FAR *)(c->ReadlData (par->MaxEntryNum));
      //----------------------------------------------------------------------
      // lpszSuggestion wird in der folgenden Funktion alloziert.
      // D.h. nach dem WritelData mu� dieser String wieder freigegeben werden
      //----------------------------------------------------------------------
      LPSTR lpszWildcard;

      if (lpszCurrentWord) {
        pspell->Wildcard (lpszCurrentWord, &lpszWildcard, *lpMaxEntryNum);

        c->WritelData (par->Wildcard, lpszWildcard, GetBlockSize(lpszWildcard), LPSTR(param) - sizeof(WORD));
        }
      else
        c->DellData (par->Wildcard, LPSTR(param) - sizeof(WORD));
      FreeGlobMem (lpszWildcard);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->CurrentWord, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->MaxEntryNum, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }



//****************************************************************************
//*
//* SpellSetOptions
//*
//****************************************************************************
#pragma pack(1)
struct setoptions_param {
  WORD parSize;
  DWORD Options;
  };
#pragma pack()

BOOL SpellSetOptions (mdiChild *c,LPVOID param,WORD mode)
  {
  setoptions_param FAR *par = (setoptions_param FAR *) param;

  if (mode & EM_LOAD) {
    //----------------------------------------------------
    // Wurde die Rechtschreibpr�fung schon initialisiert?
    //----------------------------------------------------
    if (!bSpellInitialized) {
      if (!InitializeSpelling ())
        return FALSE;

      bSpellInitialized = TRUE;
      }

    if (pspell) {
      LONG FAR *lpoptions = (LONG FAR *)(c->ReadlData (par->Options));

      LONG Options;
      if (lpoptions != NULL)
        Options = *lpoptions;
      else {
        DBWIN_ASSERT_TEXT (FALSE, "Ung�ltiger Parameter f�r Rechtschreiboption");
        Options = 0;
        }

      pspell->SetOptions (Options);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->Options, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellGetOptions
//*
//****************************************************************************
#pragma pack(1)
struct getoptions_param {
  WORD parSize;
  DWORD Options;
  };
#pragma pack()

BOOL SpellGetOptions (mdiChild *c,LPVOID param,WORD mode)
  {
  getoptions_param FAR *par = (getoptions_param FAR *) param;

  if (mode & EM_LOAD) {
    //----------------------------------------------------
    // Wurde die Rechtschreibpr�fung schon initialisiert?
    //----------------------------------------------------
    if (!bSpellInitialized) {
      if (!InitializeSpelling ())
        return FALSE;

      bSpellInitialized = TRUE;
      }

    if (pspell) {
      LONG Options = pspell->GetOptions ();

      c->WritelData (par->Options, &Options, sizeof(Options), LPSTR(param) - sizeof(WORD));
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellOpenUserDictionary
//*
//****************************************************************************
#pragma pack(1)
struct openuserdictionary_param {
  WORD parSize;
  DWORD UdrName;
  DWORD Type;
  DWORD Create;
  };
#pragma pack()

BOOL SpellOpenUserDictionary (mdiChild *c,LPVOID param,WORD mode)
  {
  openuserdictionary_param FAR *par = (openuserdictionary_param FAR *) param;

  if (mode & EM_LOAD) {
    if (!bSpellInitialized) {
      if (!InitializeSpelling ())
        return FALSE;

      bSpellInitialized = TRUE;
      }

    if (pspell) {
      LPSTR lpszudrname = LPSTR (c->ReadlData (par->UdrName));
      WORD FAR *wtype = (WORD FAR *)(c->ReadlData (par->Type));
      DBBOOL FAR *bCreate = (DBBOOL FAR *)(c->ReadlData (par->Create));

      if (!(lpszudrname && *lpszudrname)) {
        DBWIN_ASSERT_TEXT (FALSE, "Kein Name f�r das Benutzerw�rterbuch angegeben");
        return FALSE;
        }
      WORD Type = wtype ? *wtype : IgnoreAlwaysProp;
      BOOL Create = bCreate ? *bCreate : FALSE;

      if (!pspell->OpenUdr (lpszudrname, Type, Create))
        DBWIN_ASSERT_TEXT (FALSE, "Rechtschreibpr�fung (OpenUdr). Fehlerhafter Aufruf");
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->UdrName, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->Type, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->Create, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellAddtoUserDictionary
//*
//****************************************************************************
#pragma pack(1)
struct addtouserdictionary_param {
  WORD parSize;
  DWORD UdrNum;
  DWORD AddWord;
  DWORD ChangeWord;
  };
#pragma pack()

BOOL SpellAddToUserDictionary (mdiChild *c,LPVOID param,WORD mode)
  {
  addtouserdictionary_param FAR *par = (addtouserdictionary_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      DBINT FAR *lpudrnum = (DBINT FAR *)(c->ReadlData (par->UdrNum));
      LPSTR lpszaddword = (LPSTR)c->ReadlData (par->AddWord);
      LPSTR lpszchangeword = (LPSTR)c->ReadlData (par->ChangeWord);

      if ((lpudrnum == NULL) || !(lpszaddword && *lpszaddword))
        DBWIN_ASSERT_TEXT (FALSE, "Ung�ltige Parameter f�r AddToUdr");

      if (!pspell->AddToUdr (*lpudrnum, lpszaddword, lpszchangeword))
        DBWIN_ASSERT_TEXT (FALSE, "Rechtschreibpr�fung (AddToUdr). Fehlerhafter Aufruf");
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->UdrNum, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->AddWord, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->ChangeWord, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellDelFromUserDictionary
//*
//****************************************************************************
#pragma pack(1)
struct delfromuserdictionary_param {
  WORD parSize;
  DWORD UdrNum;
  DWORD StrToDel;
  };
#pragma pack()

BOOL SpellDelFromUserDictionary (mdiChild *c,LPVOID param,WORD mode)
  {
  delfromuserdictionary_param FAR *par = (delfromuserdictionary_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      DBINT FAR *lpudrnum = (DBINT FAR *)(c->ReadlData (par->UdrNum));
      LPSTR lpszstrtodel = (LPSTR)c->ReadlData (par->StrToDel);

      if ((lpudrnum == NULL) || !(lpszstrtodel && *lpszstrtodel))
        DBWIN_ASSERT_TEXT (FALSE, "Ung�ltige Parameter f�r DelFromUdr");

      if (!pspell->DelFromUdr (*lpudrnum, lpszstrtodel))
        DBWIN_ASSERT_TEXT (FALSE, "Rechtschreibpr�fung (DelFromUdr). Fehlerhafter Aufruf");

      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->UdrNum, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->StrToDel, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellCloseUserDictionary
//*
//****************************************************************************
#pragma pack(1)
struct closeuserdictionary_param {
  WORD parSize;
  DWORD UdrNum;
  DWORD ForceClose;
  };
#pragma pack()

BOOL SpellCloseUserDictionary (mdiChild *c,LPVOID param,WORD mode)
  {
  closeuserdictionary_param FAR *par = (closeuserdictionary_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      DBINT FAR *lpudrnum = (DBINT FAR *)(c->ReadlData (par->UdrNum));
      DBBOOL FAR *lpforceclose = (DBBOOL FAR *)(c->ReadlData (par->ForceClose));

      if (!(lpudrnum)) {
        DBWIN_ASSERT_TEXT (FALSE, "Ung�ltiger Index f�r das Benutzerw�rterbuch");
        return FALSE;
        }

      BOOL ForceClose = lpforceclose ? *lpforceclose : FALSE;

      if (!pspell->CloseUdr (*lpudrnum, ForceClose))
        DBWIN_ASSERT_TEXT (FALSE, "Rechtschreibpr�fung (CloseUdr). Fehlerhafter Aufruf");
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->UdrNum, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->ForceClose, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellAddToRAMCacheList
//*
//****************************************************************************
#pragma pack(1)
struct addtoramcachelist_param {
  WORD parSize;
  DWORD udr;
  DWORD AddWord;
  DWORD ChangeWord;
  };
#pragma pack()

BOOL SpellAddToRAMCacheList (mdiChild *c,LPVOID param,WORD mode)
  {
  addtoramcachelist_param FAR *par = (addtoramcachelist_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellDelFromRAMCacheList
//*
//****************************************************************************
#pragma pack(1)
struct delfromramcachelist_param {
  WORD parSize;
  DWORD Udr;
  DWORD WordToDel;
  };
#pragma pack()

BOOL SpellDelFromRAMCacheList (mdiChild *c,LPVOID param,WORD mode)
  {
  delfromramcachelist_param FAR *par = (delfromramcachelist_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    }

  return FALSE;
  }


//****************************************************************************
//*
//* SpellClearRAMCacheList
//*
//****************************************************************************
#pragma pack(1)
struct clearramcachelist_param {
  WORD parSize;
  DWORD udr;
  };
#pragma pack()

BOOL SpellClearRAMCacheList (mdiChild *c,LPVOID param,WORD mode)
  {
  clearramcachelist_param FAR *par = (clearramcachelist_param FAR *) param;

  if (mode & EM_LOAD) {
    if (pspell) {
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    }

  return FALSE;
  }



//****************************************************************************
//*
//* CloseSpell
//*
//****************************************************************************
BOOL CloseSpell (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    if (pspell)
      delete pspell;
    
    pspell = NULL;
    bSpellInitialized = FALSE;
    }

  return FALSE;
  }
