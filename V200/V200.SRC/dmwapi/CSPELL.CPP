/////////////////////////////////////////////////////////////////////////////
// Rechtschreibpruefung
/////////////////////////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/dmwapi/rev/cspell.cpv   1.2   23 Jul 1999 14:59:44   Gerhold  $
// $Log:   P:/marille/clinicum/dmwapi/rev/cspell.cpv  $
// 
//    Rev 1.2   23 Jul 1999 14:59:44   Gerhold
// Verbessertes Fehlerhandling
// 
//    Rev 1.1   27 Jun 1999 21:55:52   Hannes
// Diverse Fehlerkorrekturen
// 
//    Rev 1.0   16 Mar 1999 17:20:44   Gerhold
// Initial revision.
//
#include <windows.h>

#define MODULENUM  189

#include "dds32.h"
#include "winass.hpp"
#include "globmem.h"


#include "csapi.h"
#include "cspell.h"


//---------------------------------------------------------------------------
// Klasse CSrb
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Größen der reservierten Buffer
//---------------------------------------------------------------------------
#define SRBBUFFER_LARGESIZE 20000    // man gönnt sich ja sonst nichts
#define SRBRATING_LARGESIZE 10      // da Rating derzeit nicht unterstützt
                                    //  wird, nur pro forma reservieren

#define SRBBUFFER_SMALLSIZE 10
#define SRBRATING_SMALLSIZE 10


//#define MAXUDRFILES  10


const LPMDRDATASTRUCT MdrContainer::operator[](const int Index) const
  {
  int i = 0;
  for (LPMDRDATASTRUCT h = MDRData; h != NULL; h = h->Next, i++)
    if (i == Index)
      return h;

  return NULL;
  }



void InsertIntoStringArray (StringArray **sa, LPSTR lpsztxt)
  {
  StringArray *h, *p;

  p = new StringArray;

  p->lpszText = (LPSTR)GetGlobMem(lstrlen(lpsztxt)+1);
  lstrcpy (p->lpszText, lpsztxt);
  p->Next = NULL;

  if (*sa != NULL) {
    for (h = *sa; (h != NULL) && (h->Next != NULL); h = h->Next);
    h->Next = p;
    }
  else
    *sa = p;
  }


void RemoveAll (StringArray *sa)
  {
  StringArray *h, *p;
  if (sa != NULL) {
    for (h = sa; (h != NULL) & (h->Next != NULL); ) {
      FreeGlobMem (h->lpszText);
      p = h->Next;
      delete h;
      h = p;
      }

    if (h != NULL) {
      FreeGlobMem (h->lpszText);
      delete h;
      }
    }
  }


//---------------------------------------------------------------------------
// CSrb Konstruktor
//---------------------------------------------------------------------------
CSrb::CSrb()
  {
  nLastReturnStringIndex = 0;
  pszLastReturnString = NULL;

  srb.lrgsz = NULL;
  srb.cch = 0;
  srb.lrgbRating = NULL;
  srb.cbRate = 0;
  }

//---------------------------------------------------------------------------
// CSrb Destruktor
//---------------------------------------------------------------------------
CSrb::~CSrb()
  {
    // Puffer freigeben
  if (srb.lrgsz != NULL) {
    FreeGlobMem (srb.lrgsz);
    srb.lrgsz = NULL;
    }
//    delete [] srb.lrgsz;
  if (srb.lrgbRating != NULL) {
    FreeGlobMem (srb.lrgbRating);
    srb.lrgbRating = NULL;
    }
//    delete [] srb.lrgbRating;

  }

//---------------------------------------------------------------------------
BOOL CSrb::Init(BOOL bLarge /*= FALSE*/)
  {
  int nBufferSize, nRatingSize;

  if (bLarge) {
    nBufferSize = SRBBUFFER_LARGESIZE;
    nRatingSize = SRBRATING_LARGESIZE;
    }
  else {
    nBufferSize = SRBBUFFER_SMALLSIZE;
    nRatingSize = SRBRATING_SMALLSIZE;
    }

  srb.ichError = 0;
  srb.cchError = 0;


  // erforderliche Puffer reservieren
  srb.lrgsz = (LPSTR)GetGlobMem (nBufferSize);

//  srb.lrgsz = new CHAR[nBufferSize];
  if (srb.lrgsz == NULL)
    return FALSE;
  srb.cch = nBufferSize;

  srb.lrgbRating = (BYTE FAR*)(GetGlobMem(nRatingSize));
//  srb.lrgbRating = new BYTE[nRatingSize];
  if (srb.lrgbRating == NULL) {
    FreeGlobMem (srb.lrgsz);
    srb.lrgsz = NULL;
//    delete [] srb.lrgsz;
    srb.cch = 0;
    return FALSE;
    }

  srb.cbRate = nRatingSize;

  return TRUE;
  }

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CSrb::GetReturnString(int nString, LPSTR sResult)
  {
  //---------------------------------------------------------------------
  // erst überprüfen, ob der angeforderte String überhaupt im Buffer ist
  //---------------------------------------------------------------------
  if ((WORD) nString >= srb.csz)
    return FALSE;

  //----------------------------------------------
  // beim ersten String Zeiger auf Anfang setzen
  //----------------------------------------------
  if (nString == 0) {
    nLastReturnStringIndex = 0;
    pszLastReturnString = (LPCSTR) srb.lrgsz;
    }

  //-------------------------------------------------------------------------
  // wenn der nächste String geholt werden soll, Zeiger einfach weitersetzen
  //-------------------------------------------------------------------------
  else if (nString == nLastReturnStringIndex + 1) {
    nLastReturnStringIndex++;
    pszLastReturnString += lstrlen(pszLastReturnString) + 1;
    }
  //-----------------------------------------------------
  // ansonsten müssen wir uns von Anfang an durchhangeln
  //-----------------------------------------------------
  else {
    for (nLastReturnStringIndex = 0,
      pszLastReturnString = (LPCSTR) srb.lrgsz;
      nLastReturnStringIndex < nString; nLastReturnStringIndex++) {
        pszLastReturnString += lstrlen(pszLastReturnString) + 1;
        }
    }

  //--------------------
  // Ergebnis eintragen
  //--------------------
//  *sResult = pszLastReturnString;
  lstrcpy (sResult, pszLastReturnString);
  return TRUE;
  }

//---------------------------------------------------------------------------
// Klasse CSpellSession
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// CSpellSession Konstruktor
//---------------------------------------------------------------------------
DLLExport _export CSpellSession::CSpellSession()
  {
  // Variablen initialisieren
  hinstSpellDLL = NULL;
  lSpellID = 0;

  lSpellOptions = 0;

  rgMdr = NULL;
  rgUdr = NULL;

  secLastError = secNOERRORS;

  MdrArray = new MdrContainer;
  UdrArray = new UdrContainer;
  }

//---------------------------------------------------------------------------
// CSpellSession Destruktor
//  Aufräumen
//---------------------------------------------------------------------------
DLLExport _export CSpellSession::~CSpellSession()
  {
    // Rechtschreibsitzung beenden und noch offene DLL schließen
  CloseSpellDLL();
  
    // Speicher für Felder freigeben
  if (rgMdr != NULL) {
    FreeGlobMem (rgMdr);
    rgMdr = NULL;
    }

  if (rgUdr != NULL) {
    FreeGlobMem (rgUdr);
    rgUdr = NULL;
    }

  if (MdrArray != NULL) {
    delete MdrArray;
    MdrArray = NULL;
    }

  if (UdrArray != NULL) {
    delete UdrArray;
    UdrArray = NULL;
    }
  }



//---------------------------------------------------------------------------
// Defines für die Einträge in Registrierungsdatenbank/WIN.INI
//---------------------------------------------------------------------------
#define ENTRYLEN (_MAX_PATH * 2 + 5)
#define REG_SPELLINGKEY "SOFTWARE\\Microsoft\\Shared Tools\\Proofing Tools\\Spelling\\%4d\\Normal"
#define REG_CUSTOMDICTKEY "SOFTWARE\\Microsoft\\Shared Tools\\Proofing Tools\\Custom Dictionaries"
#define REG_SPELLENGINE "Engine"
#define REG_SPELLDICT "Dictionary"


//***************************************************************************
//*
//* Namen und Pfad der Rechtschreib-DLL aus WIN.INI/Registry ermitteln
//*
//***************************************************************************
BOOL CSpellSession::QueryDLLFileName (LPSTR psDllFileName,
                                      WORD nCountryCode /*= DEFAULT_COUNTRY*/)
  {

  // Die 32-Bit-Versionen von Winword und Excel speichern
  //  die Angaben in der Registrierungsdatenbank
    
  DWORD dwType;
  DWORD dwValueSize = ENTRYLEN;
  TCHAR szValue[ENTRYLEN];
  TCHAR szEntry[200];
  TCHAR szErr[ENTRYLEN];
  LONG lResult;
  HKEY hKeyReg;

  //---------------------------------------------------
  // Namen des Eintrags aus Ländercode zusammenstellen
  //---------------------------------------------------
  wsprintf(szEntry, REG_SPELLINGKEY, nCountryCode);

  //---------------------------------------------------
  // Registrierungsdatenbank an richtigem Key öffnen
  //---------------------------------------------------
  lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szEntry, 0, KEY_READ, &hKeyReg);
  //---------------------------------------------------
  // Wenn Key nicht gefunden, FALSE zurückgeben
  //---------------------------------------------------
  if (lResult != ERROR_SUCCESS) {
	wsprintf (szErr, "Die Registrierungsdatenbank konnte nicht mit dem Key \
		              %s geöffnet werden.", szEntry);
    DBWIN_ASSERT_TEXT (FALSE, szErr);
    return FALSE;
    }
    
  //-----------------------------
  // Pfad der DLL-Datei abfragen
  //-----------------------------
  lResult = RegQueryValueEx(hKeyReg, REG_SPELLENGINE, NULL, &dwType,
                            (LPBYTE) szValue, &dwValueSize);
  // Registrierungsdatenbank schließen
  RegCloseKey(hKeyReg);

  //---------------------------------------------------
  // Wenn Eintrag nicht gefunden oder vom falschen Typ,
  //  FALSE zurückgeben
  //---------------------------------------------------
  if (lResult != ERROR_SUCCESS || dwType != REG_SZ) {
    DBWIN_ASSERT_TEXT (FALSE, "Der Engine-Eintrag der Registrierungsdatenbank konnte \
                       nicht ausgelesen werden.");
    return FALSE;
    }
  //-----------------------------------------------------------
  // ansonsten gefundenen Pfad in den Ergebnisstring eintragen
  //-----------------------------------------------------------
  lstrcpy (psDllFileName, szValue);

  return TRUE;

  }


//***************************************************************************
//*
//* Namen und Pfad des Standard-Hauptwörterbuchs aus WIN.INI/Registry ermitteln
//*
//***************************************************************************
BOOL CSpellSession::QueryMdrFileName(LPSTR psMdrFileName, WORD nCountryCode /*= DEFAULT_COUNTRY*/)
  {
  // Die 32-Bit-Versionen von Winword und Excel speichern
  //  die Angaben in der Registrierungsdatenbank
    
  DWORD dwType;
  DWORD dwValueSize = ENTRYLEN;
  TCHAR szValue[ENTRYLEN];
  TCHAR szErr[ENTRYLEN];
  TCHAR szEntry[200];
  LONG lResult;
  HKEY hKeyReg;

  //---------------------------------------------------
  // Namen des Eintrags aus Ländercode zusammenstellen
  //---------------------------------------------------
  wsprintf(szEntry, REG_SPELLINGKEY, nCountryCode);

  //---------------------------------------------------
  // Registrierungsdatenbank an richtigem Key öffnen
  //---------------------------------------------------
  lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szEntry, 0, KEY_READ, &hKeyReg);
  // Wenn Key nicht gefunden, FALSE zurückgeben
  if (lResult != ERROR_SUCCESS) {
	wsprintf (szErr, "Die Registrierungsdatenbank konnte nicht mit dem Key \
		              %s geöffnet werden.", szEntry);
    DBWIN_ASSERT_TEXT (FALSE, szErr);

    return FALSE;
    }

  //---------------------------------------------------
  // Pfad des Standard-Hauptwörterbuchs abfragen
  //---------------------------------------------------
  lResult = RegQueryValueEx(hKeyReg, REG_SPELLDICT, NULL, &dwType, (LPBYTE) szValue, &dwValueSize);
  //---------------------------------------------------
  // Registrierungsdatenbank schließen
  //---------------------------------------------------
  RegCloseKey(hKeyReg);

  //---------------------------------------------------
  // Wenn Eintrag nicht gefunden oder vom falschen Typ, FALSE zurückgeben
  //---------------------------------------------------
  if (lResult != ERROR_SUCCESS || dwType != REG_SZ) {
    DBWIN_ASSERT_TEXT (FALSE, "Der Dictionary-Eintrag der Registrierungsdatenbank konnte \
                       nicht ausgelesen werden.");
    return FALSE;
    }

  //-----------------------------------------------------------
  // ansonsten gefundenen Pfad in den Ergebnisstring eintragen
  //-----------------------------------------------------------
//  *psMdrFileName = szValue;
  lstrcpy (psMdrFileName, szValue);

  return TRUE;
  }


//***************************************************************************
//*
//* Namen und Pfad der Benutzerwörterbücher aus WIN.INI/Registry ermitteln
//*
//***************************************************************************
BOOL CSpellSession::QueryUdrFileNames(int* pnUdrNum, StringArray *pUdrFiles)
  {
  //-------------------------------------------------------
  // Rückgabewerte initialisieren, String-Container leeren
  //-------------------------------------------------------
  *pnUdrNum = 0;

//***  for (int i = 0; i < MAXUDRFILES; i++) {
//***    if (*pUdrFiles[i] != NULL)
//***      FreeGlobMem (*pUdrFiles[i]);
//***    }
//  pUdrFiles->RemoveAll();

  RemoveAll (pUdrFiles);
  
  // Die 32-Bit-Versionen von Winword und Excel speichern
  //  die Angaben in der Registrierungsdatenbank
    
  DWORD dwIndex;
  DWORD dwType;
  DWORD dwEntryNameSize;
  TCHAR szEntryName[ENTRYLEN];
  DWORD dwValueSize;
  char  szValue[ENTRYLEN];
  TCHAR szErr[ENTRYLEN];
  LONG lResult;
  HKEY hKeyReg;

  //---------------------------------------------------
  // Registrierungsdatenbank an richtigem Key öffnen
  //---------------------------------------------------
  lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_CUSTOMDICTKEY, 0, KEY_READ, &hKeyReg);
  //---------------------------------------------------
  // Wenn Key nicht gefunden, FALSE zurückgeben
  //---------------------------------------------------
  if (lResult != ERROR_SUCCESS) {
	wsprintf (szErr, "Die Registrierungsdatenbank konnte nicht mit dem Key \
		              %s geöffnet werden.", REG_CUSTOMDICTKEY);
    DBWIN_ASSERT_TEXT (FALSE, szErr);
    return FALSE;
    }

  //-----------------------------------------------------------------
  // Jetzt alle Einträge des Key aufzählen lassen; jeder Eintrag ist
  //  ein Benutzerwörterbuch
  //-----------------------------------------------------------------
  for (dwIndex = 0, lResult = ERROR_SUCCESS; lResult == ERROR_SUCCESS; dwIndex++) {
    dwEntryNameSize = ENTRYLEN;
    dwValueSize = ENTRYLEN;
    // Einen Eintrag holen
    lResult = RegEnumValue(hKeyReg, dwIndex, (LPTSTR) szEntryName, &dwEntryNameSize,
                           NULL, &dwType, (LPBYTE) szValue, &dwValueSize);
    if (lResult == ERROR_SUCCESS && dwType == REG_SZ && dwValueSize > 0) {
      // Anzahl der ermittelten Benutzerwörterbücher hochzählen

      InsertIntoStringArray (&pUdrFiles, szValue);
      *pnUdrNum++;
      }
    }

    // Registrierungsdatenbank schließen
  RegCloseKey(hKeyReg);


  return TRUE;
  }

//***************************************************************************
//*
//* Registry/WIN.INI auslesen und mit den Angaben Rechtschreib-DLL öffnen,
//*  Rechtschreibsitzung initialisieren und Haupt- und Benutzerwörterbücher öffnen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::InitFromRegistry(BOOL bOpenCustomDicts /*= TRUE*/)
  {
  char sDllFileName[MAX_PATH]; 
  char sMdrFileName[MAX_PATH];
  StringArray *UdrFiles = NULL;
  int nUdrNum;

  // Namen von DLL und Hauptwörterbuch ermitteln
  if (!QueryDLLFileName(sDllFileName))
    return FALSE;

  if (!QueryMdrFileName(sMdrFileName))
    return FALSE;


  // Namen und Pfade der Benutzerwörterbücher ermitteln
  if (bOpenCustomDicts) {
    if (!QueryUdrFileNames(&nUdrNum, UdrFiles))
      return FALSE;
    }

  // Öffnen der Rechtschreib-DLL
  if (!OpenSpellDLL(sDllFileName))
    return FALSE;
  
  // Rechtschreibsitzung starten
  if (!InitSession()) {
    CloseSpellDLL();
    return FALSE;
    }

  // Hauptwörterbuch öffnen
  if (!OpenMdr(sMdrFileName)) {
    CloseSpellDLL();
    return FALSE;
    }

  // Benutzerwörterbücher öffnen
  if (bOpenCustomDicts) {
    for (StringArray *h = UdrFiles; h!= NULL; h = h->Next) {  
      if (!OpenUdr(h->lpszText)) {
        CloseSpellDLL();
        return FALSE;
        }
      }
    }

  // alles OK
  return TRUE;
  }


//***************************************************************************
//*
//* Öffnen der Rechtschreib-DLL
//*
//***************************************************************************
BOOL CSpellSession::OpenSpellDLL(LPCSTR lpszDLL)
  {
  char szErr[ENTRYLEN];

  // Fehlermeldung für 'Datei nicht gefunden' ausschalten
  UINT nOldErrMode = SetErrorMode(SEM_NOOPENFILEERRORBOX);

  // DLL öffnen
  hinstSpellDLL = LoadLibrary(lpszDLL);

  // Fehlermeldungen wieder einschalten
  SetErrorMode(nOldErrMode);

  // Glück gehabt?
  if (hinstSpellDLL == NULL) {
    wsprintf (szErr, "Die Rechtschreib-DLL %s konnte nicht geöffnet werden.", lpszDLL);
    DBWIN_ASSERT_TEXT (FALSE, szErr);
    hinstSpellDLL = NULL;
    return FALSE;
    }

  // Zeiger auf alle DLL-Funktionen besorgen
  if ((lpfnSpellVer = (SPELLVERPROC) GetProcAddress(hinstSpellDLL,
      MAKEINTRESOURCE(1))) == NULL ||
      (lpfnSpellInit = (SPELLINITPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(2))) == NULL ||
      (lpfnSpellOptions = (SPELLOPTIONSPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(3))) == NULL ||
      (lpfnSpellCheck = (SPELLCHECKPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(4))) == NULL ||
      (lpfnSpellTerminate = (SPELLTERMINATEPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(5))) == NULL ||
      (lpfnSpellVerifyMdr = (SPELLVERIFYMDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(6))) == NULL ||
      (lpfnSpellOpenMdr = (SPELLOPENMDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(7))) == NULL ||
      (lpfnSpellOpenUdr = (SPELLOPENUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(8))) == NULL ||
      (lpfnSpellAddUdr = (SPELLADDUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(9))) == NULL ||
      (lpfnSpellAddChangeUdr = (SPELLADDCHANGEUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(10))) == NULL ||
      (lpfnSpellDelUdr = (SPELLDELUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(11))) == NULL ||
      (lpfnSpellClearUdr = (SPELLCLEARUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(12))) == NULL ||
      (lpfnSpellGetSizeUdr = (SPELLGETSIZEUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(13))) == NULL ||
      (lpfnSpellGetListUdr = (SPELLGETLISTUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(14))) == NULL ||
      (lpfnSpellCloseMdr = (SPELLCLOSEMDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(15))) == NULL ||
      (lpfnSpellCloseUdr = (SPELLCLOSEUDRPROC) GetProcAddress(hinstSpellDLL,
        MAKEINTRESOURCE(16))) == NULL)
    {
    DBWIN_ASSERT_TEXT (FALSE, "Die Funktionen der Rechtschreib-DLL konnten nicht geöffnet werden.");
    FreeLibrary(hinstSpellDLL);
    hinstSpellDLL = NULL;
    return FALSE;
    }

  return TRUE;
  }


//***************************************************************************
//*
//*
//***************************************************************************
void CSpellSession::CloseSpellDLL()
  {
  // Sitzung beenden
  if (!TerminateSession()) {
    DBWIN_ASSERT_TEXT (FALSE, "Die Rechtschreib-Sitzung konnte nicht ordnungsgemäß beendet werden.");
    // Und bist Du nicht willig, so gebrauch ich bForce
    TerminateSession(TRUE);
    }

  // DLL freigeben
  if (hinstSpellDLL != NULL) {
    FreeLibrary(hinstSpellDLL);
    hinstSpellDLL = NULL;
    }
  }


//***************************************************************************
//*
//* Rechtschreib-Sitzung starten
//*
//***************************************************************************
BOOL CSpellSession::InitSession(WSC FAR *lpWsc /*= NULL*/)
  {
  WSC wsc;

  // falls keine WSC-Struktur übergeben wurde, leere Dummy-Struktur
  //  an DLL-Funktion übergeben
  if (lpWsc == NULL) {
    memset(&wsc, 0, sizeof(wsc));
    lpWsc = &wsc;
    }
  
  // DLL-Aufruf
  SEC secResult = lpfnSpellInit(&lSpellID, lpWsc);
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Die Rechtschreibsitzung konnte nicht gestartet werden.");
    lSpellID = 0;
    SetLastError(secResult);
    return FALSE;
    }

  return TRUE;
  }


//***************************************************************************
//*
//* Rechtschreib-Sitzung beenden
//*
//***************************************************************************
BOOL CSpellSession::TerminateSession(BOOL bForce /*= FALSE*/)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, sofort zurückkehren
  if (lSpellID == NULL)
    return TRUE;

  // noch offene Hauptwörterbücher schließen
//  while (MdrArray.GetSize() > 0)
//***  for (i = 0; i < MAXMDR; i++) {
    // Wörterbuch schließen
//***    if (MdrArray[i] != NULL) {
//***      lpfnSpellCloseMdr(lSpellID, (&((MdrDataStruct*) MdrArray[i])->mdrs));

//***      FreeGlobMem ((MdrDataStruct*) MdrArray[i]);
//***      }
  LPMDRDATASTRUCT h;

  for (LPMDRDATASTRUCT p = MdrArray->MDRData; p != NULL; ) {
    lpfnSpellCloseMdr (lSpellID, (&((MdrDataStruct*) p)->mdrs));
  
    h = p->Next;
    delete (MdrDataStruct*)p;
    p = h;
    }

      // Eintrag aus Container entfernen und freigeben
//    MdrDataStruct* pMdrDataStruct = (MdrDataStruct*) MdrArray.GetAt(0);
//    delete pMdrDataStruct;
//    MdrArray.RemoveAt(0);
//    }
    // Containereinträge löschen
//  MdrArray.RemoveAll();
  
  // noch offene Benutzerwörterbücher schließen
//  while (UdrArray.GetSize() > 0)

  LPUDRDATASTRUCT hu;
  for (LPUDRDATASTRUCT pu = UdrArray->UDRData; pu != NULL; ) {
    UDR udr = ((UdrDataStruct*) pu)->udr;
    if (udr != udrChangeOnce && udr != udrChangeAlways && udr != udrIgnoreAlways)
      lpfnSpellCloseUdr (lSpellID, udr, TRUE);
  
    hu = pu->Next;
    delete (UdrDataStruct*)pu;
    pu = hu;
    }


//***  for (i = 0; i < UdrArray->GetSize(); i++) {
    // Wörterbuch schließen, falls es keine RAM-Cache-Liste ist
//***    UDR udr = ((UdrDataStruct*) UdrArray->GetAt(i))->udr;
//***    if (udr != udrChangeOnce && udr != udrChangeAlways && udr != udrIgnoreAlways)
//***      lpfnSpellCloseUdr(lSpellID, udr, TRUE);

//****    FreeGlobMem ((UdrDataStruct*) UdrArray[i]);


      // Eintrag aus Container entfernen und freigeben
//    UdrDataStruct* pUdrDataStruct = (UdrDataStruct*) UdrArray.GetAt(0);
//    delete pUdrDataStruct;
//    UdrArray.RemoveAt(0);
//***  }
    // Containereinträge löschen
//  UdrArray.RemoveAll();
  
  SEC secResult = lpfnSpellTerminate(lSpellID, bForce);
  if (secResult == secNOERRORS) {
    lSpellID = NULL;
    return TRUE;
    }
  else {
    SetLastError(secResult);
    return FALSE;
    }
  }


//***************************************************************************
//*
//* Versionsnummern der Rechtschreib-DLL ermitteln
//*
//***************************************************************************
BOOL CSpellSession::SpellVer(WORD FAR *lpwVer, WORD FAR *lpwIdEngine, WORD FAR *lpwSpellType)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  SEC secResult = lpfnSpellVer(lpwVer, lpwIdEngine, lpwSpellType);
  if (secResult == secNOERRORS) {
    return TRUE;
    }
  else {
    SetLastError(secResult);
    return FALSE;
    }
  }


//***************************************************************************
//*
//* Ermittelt, ob die Rechtschreib-DLL Wortmasken unterstützt
//*
//***************************************************************************
BOOL CSpellSession::HasWildcardSupport()
  {
  WORD wVer, wIdEngine, wSpellType;

  // Versionsangaben ermitteln
  if (!SpellVer(&wVer, &wIdEngine, &wSpellType))
    return FALSE;

  // zurückgeben, ob die Fähigkeit unterstützt wird
  if ((wSpellType & fscisWildCardSupport) != 0)
    return TRUE;
  else
    return FALSE;
  }

//***************************************************************************
//*
//* Ermittelt, ob die Rechtschreib-DLL mehrere Hauptwörterbücher unterstützt
//*
//***************************************************************************
BOOL CSpellSession::HasMultiDictSupport()
  {
  WORD wVer, wIdEngine, wSpellType;

  // Versionsangaben ermitteln
  if (!SpellVer(&wVer, &wIdEngine, &wSpellType))
    return FALSE;

  // zurückgeben, ob die Fähigkeit unterstützt wird
  if ((wSpellType & fscisMultiDictSupport) != 0)
    return TRUE;
  else
    return FALSE;
  }

//***************************************************************************
//*
//* Ermittelt, ob die Rechtschreib-DLL Angaben zur Worttrennung liefern kann
//*
//***************************************************************************
BOOL CSpellSession::HasHyphenationSupport()
  {
  WORD wVer, wIdEngine, wSpellType;

  // Versionsangaben ermitteln
  if (!SpellVer(&wVer, &wIdEngine, &wSpellType))
    return FALSE;

  // zurückgeben, ob die Fähigkeit unterstützt wird
  if ((wSpellType & fscisHyphenationSupport) != 0)
    return TRUE;
  else
    return FALSE;
  }

//***************************************************************************
//*
//* Optionen für Rechtschreibsitzung festlegen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::SetOptions(long lOptions)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Optionen setzen
  SEC secResult = lpfnSpellOptions(lSpellID, lOptions);
  // falls Funktion erfolgreich war, gesetzte Optionen merken
  if (secResult == secNOERRORS) {
    lSpellOptions = lOptions;
    return TRUE;
    }
  else {
    SetLastError(secResult);
    return FALSE;
    }

  }

//***************************************************************************
//*
//* Zuletzt gesetzte Optionen für Rechtschreibsitzung ermitteln
//*
//***************************************************************************
long CSpellSession::GetOptions()
  {
  return lSpellOptions;
  }

//***************************************************************************
//*
//* Hauptwörterbuch öffnen
//*
//***************************************************************************
BOOL CSpellSession::OpenMdr (LPCSTR lpszMdrName, 
                             LPCSTR lpszExcName /*= NULL*/,
                             BOOL bCreateUdrExc /*= FALSE*/, 
                             LID lidExpected /*= DEFAULT_LID*/,
                             BOOL bCache /*= TRUE*/)
  {

  //-----------------------------------------------------------------
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  //-----------------------------------------------------------------
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  //-----------------------------------------------------------------
  // Struktur zur Speicherung der Daten des Hauptwörterbuchs anlegen
  //-----------------------------------------------------------------
  MdrDataStruct* pMdrDataStruct = new MdrDataStruct;
  if (pMdrDataStruct == NULL) {
    SetLastError(secOOM);
    return FALSE;
    }

  //-----------------------------------------
  // Hauptwörterbuch durch DLL-Aufruf öffnen
  //-----------------------------------------
  SEC secResult = lpfnSpellOpenMdr(lSpellID, lpszMdrName, lpszExcName,
                                   bCreateUdrExc, bCache, lidExpected, 
                                   &(pMdrDataStruct->mdrs));
  //-------------------------------------
  // falls Fehler beim Öffnen, aufräumen
  //-------------------------------------
  if (secResult != secNOERRORS) {
//***    FreeGlobMem (pMdrDataStruct);
    delete pMdrDataStruct;
    pMdrDataStruct = NULL;
    DBWIN_ASSERT_TEXT (FALSE, "Das Hauptwörterbuch konnte nicht geöffnet werden.");
    SetLastError(secResult);
    return FALSE;
    }

  //---------------------------------------------------------
  // Struktur mit weiteren Daten zum Hauptwörterbuchs füllen
  //---------------------------------------------------------
  lstrcpy (pMdrDataStruct->sMdrPath, lpszMdrName);
  if (lpszExcName != NULL)
    lstrcpy (pMdrDataStruct->sExclusionPath, lpszExcName);
  else
    lstrcpy (pMdrDataStruct->sExclusionPath, "");

  //--------------------------------------------------------
  // Daten des neuen Hauptwörterbuchs in Container einfügen
  //--------------------------------------------------------
//  MdrArray.Add(pMdrDataStruct);
  MdrArray->Add (pMdrDataStruct);
//****  MdrArray[iActMdr++] = pMdrDataStruct;

  //--------------------------------------------------------------------
  // neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
  //--------------------------------------------------------------------
  if (!RebuildDRLists()) {
    SetLastError(secOOM);
    return FALSE;
    }

  return TRUE;
  }

//***************************************************************************
//*
//* Hauptwörterbuch schließen
//*
//***************************************************************************
BOOL CSpellSession::CloseMdr(int nMdr)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
//***  if (nMdr < 0 || nMdr >= iActMdr/*MdrArray.GetSize()*/) {
  if (nMdr < 0 || nMdr >= MdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  // Hauptwörterbuch durch DLL-Aufruf schließen
  LPMDRDATASTRUCT p = MdrArray->GetAt (nMdr);
  SEC secResult = lpfnSpellCloseMdr(lSpellID,
//***                                    (&((MdrDataStruct*)MdrArray[nMdr])->mdrs));
                                    &p->mdrs);
  // falls Fehler beim Schließen, sofort zurückkehren
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Das Hauptwörterbuch konnte nicht geschlossen werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  // Daten des geschlossenen Hauptwörterbuchs aus Container entfernen
  MdrDataStruct* pMdrDataStruct = (MdrDataStruct*) MdrArray->GetAt(nMdr);

//******************************************************************
// da sollte das Element aus der verketteten Liste gelöscht werden
//******************************************************************
//***  FreeGlobMem (MdrArray[nMdr]);
  MdrArray->RemoveAt(nMdr);
//***  FreeGlobMem (pMdrDataStruct);
//****  delete pMdrDataStruct;

  // neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
  if (!RebuildDRLists()) {
    SetLastError(secOOM);
    return FALSE;
    }

  return TRUE;
  }


//***************************************************************************
//*
//* Anzahl der offenen Hauptwörterbücher ermitteln
//*
//***************************************************************************
int CSpellSession::GetMdrNum()
  {
  return MdrArray->GetSize();
  }


//***************************************************************************
//*
//* Daten eines offenen Hauptwörterbuchs ermitteln
//*
//***************************************************************************
BOOL CSpellSession::GetMdrData(int nMdr, MdrDataStruct* pMdrData)
  {
    // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
//***  if (nMdr < 0 || nMdr >= iActMdr/*MdrArray.GetSize()*/) {
  if (nMdr < 0 || nMdr >= MdrArray->GetSize()) {
    return FALSE;
    }

  *pMdrData = *((MdrDataStruct*) MdrArray->GetAt(nMdr));

  return TRUE;
  }


//***************************************************************************
//*
//* Benutzerwörterbuch öffnen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::OpenUdr (LPCSTR lpszUdrName, 
                                               WORD nType /*= IgnoreAlwaysProp*/,
                                               BOOL bCreate /*= FALSE*/)
  {
  //-----------------------------------------------------------------
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  //-----------------------------------------------------------------
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  //--------------------------------------------------------------------
  // Struktur zur Speicherung der Daten des Benutzerwörterbuchs anlegen
  //--------------------------------------------------------------------
  UdrDataStruct* pUdrDataStruct = new UdrDataStruct;

  if (pUdrDataStruct == NULL) {
    SetLastError(secOOM);
    return FALSE;
    }

  //--------------------------------------------
  // Benutzerwörterbuch durch DLL-Aufruf öffnen
  //--------------------------------------------
  SEC secResult = lpfnSpellOpenUdr(lSpellID, lpszUdrName, bCreate,
                                   nType, &(pUdrDataStruct->udr), 
                                   &(pUdrDataStruct->bReadOnly));
  //-------------------------------------
  // falls Fehler beim Öffnen, aufräumen
  //-------------------------------------
  if (secResult != secNOERRORS) {
    delete pUdrDataStruct;
    DBWIN_ASSERT_TEXT (FALSE, "Das Benutzerwörterbuch konnte nicht geöffnet werden.");
    SetLastError(secResult);
    return FALSE;
    }

  //------------------------------------------------------------------
  // Struktur mit den restlichen Daten des Benutzerwörterbuchs füllen
  //------------------------------------------------------------------
  pUdrDataStruct->nType = nType;
  lstrcpy (pUdrDataStruct->sUdrPath, lpszUdrName);

  //-----------------------------------------------------------
  // Daten des neuen Benutzerwörterbuchs in Container einfügen
  //-----------------------------------------------------------
//  UdrArray.Add(pUdrDataStruct);
//******************************************************************
// und hier in die dynamische Liste einfügen
//******************************************************************
//***  UdrArray[iActUdr++] = pUdrDataStruct;
  UdrArray->Add (pUdrDataStruct);
  
  //--------------------------------------------------------------------
  // neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
  //--------------------------------------------------------------------
  if (!RebuildDRLists()) {
    SetLastError(secOOM);
    return FALSE;
    }

  return TRUE;
  }

//***************************************************************************
//*
//* Benutzerwörterbuch schließen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::CloseUdr(int nUdr, BOOL bForce /*= FALSE*/)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  // Benutzerwörterbuch durch DLL-Aufruf schließen
  SEC secResult = lpfnSpellCloseUdr(lSpellID,
                                    ((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr, bForce);
  // falls Fehler beim Schließen, sofort zurückkehren
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT(FALSE, "Das Benutzerwörterbuch konnte nicht geschlossen werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  // Daten des geschlossenen Benutzerwörterbuchs aus Container entfernen
  UdrDataStruct* pUdrDataStruct = (UdrDataStruct*) UdrArray->GetAt(nUdr);

//******************************************************************
// und hier aus der dynamischen Liste raus
//******************************************************************
//***  FreeGlobMem (UdrArray[nUdr]);
  UdrArray->RemoveAt(nUdr);
//***  FreeGlobMem (pUdrDataStruct);
//  delete pUdrDataStruct;

  // neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
  if (!RebuildDRLists()) {
    SetLastError(secOOM);
    return FALSE;
    }

  return TRUE;
  }


//***************************************************************************
//*
//* Anzahl der offenen Benutzerwörterbücher (ohne RAM-Cache-Listen) ermitteln
//*
//***************************************************************************
int CSpellSession::GetUdrNum()
  {
  return UdrArray->GetSize();
  }


//***************************************************************************
//*
//* Daten eines offenen Benutzerwörterbuchs ermitteln
//*
//***************************************************************************
BOOL CSpellSession::GetUdrData(int nUdr, UdrDataStruct* pUdrData)
  {
  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    return FALSE;
    }

  *pUdrData = *((UdrDataStruct*) UdrArray->GetAt(nUdr));

  return TRUE;
  }


//***************************************************************************
//*
//* Neuen Eintrag in Benutzerwörterbuch einfügen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::AddToUdr (int nUdr, 
                                                LPCSTR lpszAdd, 
                                                LPCSTR lpszChangeTo /*= NULL*/)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  SEC secResult;
  
  // Hat das Wörterbuch einfache Einträge?
  if (((UdrDataStruct*) UdrArray->GetAt(nUdr))->nType == IgnoreAlwaysProp) {
    // Benutzerwörterbuch durch DLL-Aufruf erweitern
    secResult = lpfnSpellAddUdr(lSpellID,
    ((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr, lpszAdd);
    }
  // ansonsten enthält es Wortpaare
  else {
    // Sicherstellen, daß das zweite Wort richtig übergeben wurde
    if (lpszChangeTo == NULL) {
      SetLastError(secOOM | secInvalidUdrEntry);
      return FALSE;
      }

    // Benutzerwörterbuch durch DLL-Aufruf erweitern
    secResult = lpfnSpellAddChangeUdr(lSpellID,
    ((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr, lpszAdd, lpszChangeTo);
    }

  // Ergebnis auswerten
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Das Benutzerwörterbuch konnte nicht um den neuen Eintrag erweitert werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  return TRUE;
  }


//***************************************************************************
//*
//* Neuen Eintrag in RAM-Cache-Liste einfügen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::AddToRAMCacheList (UDR udr, 
                                                         LPCSTR lpszAdd, 
                                                         LPCSTR lpszChangeTo /*= NULL*/)
  {
  //-----------------------------------------------------------------
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  //-----------------------------------------------------------------
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  SEC secResult;
  
  //---------------------------------------
  // Hat das Wörterbuch einfache Einträge?
  //---------------------------------------
  if (udr == udrIgnoreAlways) {
    // Benutzerwörterbuch durch DLL-Aufruf erweitern
    secResult = lpfnSpellAddUdr(lSpellID, udr, lpszAdd);
    }
  //---------------------------------------
  // ansonsten enthält es Wortpaare
  //---------------------------------------
  else {
    //------------------------------------------------------------
    // Sicherstellen, daß das zweite Wort richtig übergeben wurde
    //------------------------------------------------------------
    if (lpszChangeTo == NULL) {
      SetLastError(secOOM | secInvalidUdrEntry);
      return FALSE;
      }

    //-----------------------------------------------
    // Benutzerwörterbuch durch DLL-Aufruf erweitern
    //-----------------------------------------------
    secResult = lpfnSpellAddChangeUdr(lSpellID, udr, lpszAdd, lpszChangeTo);
    }

  //--------------------
  // Ergebnis auswerten
  //--------------------
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Die RAM-Cache-Liste konnte nicht um den neuen Eintrag erweitert werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  return TRUE;
  }


//***************************************************************************
//*
//* Eintrag aus Benutzerwörterbuch löschen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::DelFromUdr(int nUdr, LPCSTR lpszDel)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  // Eintrag durch DLL-Aufruf löschen
  SEC secResult = lpfnSpellDelUdr(lSpellID,
                                  ((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr, 
                                  lpszDel);

  // Ergebnis auswerten
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Der Eintrag konnte nicht aus dem Benutzerwörterbuch gelöscht werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  return TRUE;
  }


//***************************************************************************
//*
//* Eintrag aus RAM-Cache-Liste löschen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::DelFromRAMCacheList(UDR udr, LPCSTR lpszDel)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Eintrag durch DLL-Aufruf löschen
  SEC secResult = lpfnSpellDelUdr(lSpellID, udr, lpszDel);

  // Ergebnis auswerten
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Der Eintrag konnte nicht aus der RAM-Cache-Liste gelöscht werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  return TRUE;
  }


//***************************************************************************
//*
//* RAM-Cache-Liste komplett löschen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::ClearRAMCacheList (UDR udr)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  SEC secResult = lpfnSpellClearUdr(lSpellID, udr);
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Die RAM-Cache-Liste konnte nicht gelöscht werden.");
    SetLastError(secResult);
    return FALSE;
    }

  return TRUE;
  }


//***************************************************************************
//*
//* Anzahl der Einträge in einem Benutzerwörterbuch ermitteln
//*
//***************************************************************************
BOOL CSpellSession::GetUdrEntryNum(int nUdr, int *pnEntryNum)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  WORD nEntryNum;
  
  // Anzahl der Einträge durch DLL-Aufruf ermitteln
  SEC secResult = lpfnSpellGetSizeUdr(lSpellID,
                                      ((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr, 
                                      &nEntryNum);

  // Ergebnis auswerten
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Die Anzahl der Einträge im Benutzerwörterbuch konnte nicht ermittelt werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
    // Ergebnis zurückgeben
  *pnEntryNum = (int) nEntryNum;
  
  return TRUE;
  }

//***************************************************************************
//*
//* Anzahl der Einträge in einer RAM-Cache-Liste ermitteln
//*
//***************************************************************************
BOOL CSpellSession::GetRAMCacheListEntryNum(UDR udr, int *pnEntryNum)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  WORD nEntryNum;
  
  // Anzahl der Einträge durch DLL-Aufruf ermitteln
  SEC secResult = lpfnSpellGetSizeUdr(lSpellID, udr, &nEntryNum);

  // Ergebnis auswerten
  if (secResult != secNOERRORS) {
    DBWIN_ASSERT_TEXT (FALSE, "Die Anzahl der Einträge in der RAM-Cache-Liste konnte nicht ermittelt werden.");
    SetLastError(secResult);
    return FALSE;
    }
  
  // Ergebnis zurückgeben
  *pnEntryNum = (int) nEntryNum;
  
  return TRUE;
  }

//***************************************************************************
//*
//* Einträge eines Benutzerwörterbuchs auslesen
//*
//***************************************************************************
BOOL CSpellSession::GetUdrEntries (int nUdr, 
                                   LPSTR /*CStringArray* */ pEntries,
                                   LPSTR /*CStringArray* */pChangeTo /*= NULL*/, 
                                   int nStartEntry /*= 0*/,
                                   int nMaxEntryNum /*= -1*/, 
                                   int nStartArrayIndex /*= 0*/)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  // Prüfen, ob ein Wörterbuch unter dem übergebenen Index existiert
  if (nUdr < 0 || nUdr >= UdrArray->GetSize()) {
    SetLastError(secOOM);
    return FALSE;
    }

  BOOL bHasWordPairs;

  // Hat das Wörterbuch einfache Einträge?
  if (((UdrDataStruct*) UdrArray->GetAt(nUdr))->nType == IgnoreAlwaysProp) {
    bHasWordPairs = FALSE;
    }
  // ansonsten enthält es Wortpaare
  else {
    bHasWordPairs = TRUE;
    // Prüfen, ob auch ein Zeiger auf den Container für die
    //  Alternativen übergeben wurde
    if (pChangeTo == NULL) {
      SetLastError(secOOM);
      return FALSE;
      }
    }

  return ReadUdrEntries(((UdrDataStruct*) UdrArray->GetAt(nUdr))->udr,
                        pEntries, pChangeTo, nStartEntry, nMaxEntryNum, 
                        nStartArrayIndex, bHasWordPairs);
  }

//***************************************************************************
//*
//* Einträge einer RAM-Cache-Liste auslesen
//*
//***************************************************************************
BOOL CSpellSession::GetRAMCacheListEntries(UDR udr, 
                                           LPSTR /*CStringArray* */ pEntries,
                                           LPSTR /*CStringArray* */ pChangeTo /*= NULL*/, 
                                           int nStartEntry /*= 0*/,
                                           int nMaxEntryNum /*= -1*/, 
                                           int nStartArrayIndex /*= 0*/)
  {
  // Wenn keine Rechtschreibsitzung geöffnet ist, Fehler zurückgeben
  if (lSpellID == NULL) {
    SetLastError(secModuleError | secInvalidID);
    return FALSE;
    }

  BOOL bHasWordPairs;

  // Hat die RAM-Cache-Liste einfache Einträge?
  if (udr == udrIgnoreAlways) {
    bHasWordPairs = FALSE;
    }
  // oder enthält sie Wortpaare?
  else if (udr == udrChangeOnce && udr == udrChangeAlways) {
    bHasWordPairs = TRUE;
    // Prüfen, ob auch ein Zeiger auf den Container für die
    //  Alternativen übergeben wurde
    if (pChangeTo == NULL) {
      SetLastError(secOOM);
      return FALSE;
      }
    }
  // sonst ist es gar keine RAM-Cache-Liste
  else {
    SetLastError(secOOM);
    return FALSE;
    }

  return ReadUdrEntries(udr, pEntries, pChangeTo, nStartEntry, nMaxEntryNum,
                        nStartArrayIndex, bHasWordPairs);
  }

//***************************************************************************
//*
//* Hilfsfunktion zum Auslesen der Einträge aus einem Benutzerwörterbuch oder
//*  einer RAM-Cache-Liste
//*
//***************************************************************************
BOOL CSpellSession::ReadUdrEntries(UDR udr, LPSTR /*CStringArray* */ pEntries, 
                                   LPSTR /*CStringArray* */ pChangeTo,
                                   int nStartEntry, 
                                   int nMaxEntryNum, 
                                   int nStartArrayIndex, 
                                   BOOL bHasWordPairs)
  {
  // Buffer in SRB reservieren
  CSrb csrb;

  if (!csrb.Init(TRUE)) {
    SetLastError(secOOM);
    return FALSE;
    }

  WORD nCurrentEntry = (WORD) nStartEntry;
  int nCurrentArrayIndex = nStartArrayIndex;
  int nAlreadyRetrieved = 0;
  SEC secResult;
  int nSteps, nCurrentStep, nCurrentString;
  char sCurrentString[1024];
  BOOL bGotAllEntries = FALSE;

  // Einträge solange auslesen, bis keine weiteren vorhanden sind oder
  // nMaxEntryNum erreicht ist
  do {
    // einen Satz Einträge durch DLL-Aufruf auslesen
    secResult = lpfnSpellGetListUdr(lSpellID, udr, nCurrentEntry, &csrb.srb);
    if (secResult != secNOERRORS) {
      SetLastError(secResult);
      return FALSE;
      }

    nSteps = csrb.srb.csz;

    // Falls das Wörterbuch Wortpaare enthält, holen wir bei
    //  jedem Schritt gleich 2 Strings
    if (bHasWordPairs)
      nSteps /= 2;
        
    // Falls mehr Wörter vorhanden sind als beim Aufruf der Funktion
    //  angefordert wurden, brauchen wir nicht alle auszulesen
    if (nMaxEntryNum >= 0) {
      if (nAlreadyRetrieved + nSteps < nMaxEntryNum) {
        nSteps = nMaxEntryNum - nAlreadyRetrieved;
        bGotAllEntries = TRUE;
        }
      else {
        nAlreadyRetrieved += nSteps;
        }
      }

    for (nCurrentStep = 0, nCurrentString = 0; nCurrentStep < nSteps;
      nCurrentStep++, nCurrentString++, nCurrentArrayIndex++) {
      // einen String aus dem Return-Buffer holen
      csrb.GetReturnString(nCurrentString, sCurrentString);
      // und im Container eintragen
//********************************************************************************************
//      pEntries->SetAtGrow(nCurrentArrayIndex, sCurrentString);
//********************************************************************************************
      // Falls das Wörterbuch Wortpaare enthält, den 2. String holen
      if (bHasWordPairs) {
        nCurrentString++;
        csrb.GetReturnString(nCurrentString, sCurrentString);
//********************************************************************************************
//        pChangeTo->SetAtGrow(nCurrentArrayIndex, sCurrentString);
//********************************************************************************************
        }
      }

    } while (csrb.srb.scrs == scrsMoreInfoThanBufferCouldHold && !bGotAllEntries);

  return TRUE;
  }

//***************************************************************************
//*
//* Ein oder mehrere Wörter überprüfen
//*
//***************************************************************************
BOOL CSpellSession::CheckWord(LPCSTR lpszBuffer, SCRS* pScrs, UINT* pnErrorPos,
                              LPSTR psChange /*= NULL*/)
  {
  // kleinen Buffer in SRB reservieren
  CSrb csrb;
  if (!csrb.Init(FALSE)) {
    SetLastError(secOOM);
    return FALSE;
    }

  // Spell Input Buffer aufbauen
  SIB sib;
  sib.cch = (unsigned short) lstrlen(lpszBuffer);
  sib.cMdr = (unsigned short) GetMdrNum();
  sib.cUdr = (unsigned short) GetUdrNum();
  sib.wSpellState = fssNoStateInfo;
  sib.lrgch = (CHAR FAR *) lpszBuffer;
  sib.lrgMdr = rgMdr;
  sib.lrgUdr = rgUdr;

  // Buffer überprüfen lassen
  SEC secResult = lpfnSpellCheck(lSpellID, sccVerifyWord, &sib, &csrb.srb);
  if (secResult != secNOERRORS) {
    SetLastError(secResult);
    return FALSE;
    }

  // Ergebnisse zurückgeben
  *pScrs = csrb.srb.scrs;
  *pnErrorPos = csrb.srb.ichError;
  if ((csrb.srb.scrs == scrsReturningChangeAlways || 
       csrb.srb.scrs == scrsReturningChangeOnce) && psChange != NULL) {
    psChange = csrb.srb.lrgsz;
    }
  
  return TRUE;
  }

//***************************************************************************
//*
//* Fortlaufende Sätze überprüfen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::CheckBuffer(LPCSTR lpszBuffer, 
                                                  SCRS* pScrs,
                                                  UINT* pnErrorPos, 
                                                  WORD nSpellState /*= fssIsContinued*/,
                                                  LPSTR psChange /*= NULL*/, 
                                                  UINT* pnErrorLength /*= NULL*/)
  {
  //-----------------------------------
  // kleinen Buffer in SRB reservieren
  //-----------------------------------
  CSrb csrb;
  if (!csrb.Init(FALSE)) {
    SetLastError(secOOM);
    return FALSE;
    }

  //-----------------------------------
  // Spell Input Buffer aufbauen
  //-----------------------------------
  SIB sib;
  sib.cch = (unsigned short) lstrlen(lpszBuffer);
  sib.cMdr = (unsigned short) GetMdrNum();
  sib.cUdr = (unsigned short) GetUdrNum();
  sib.wSpellState = nSpellState;
  sib.lrgch = (CHAR FAR *) lpszBuffer;
  sib.lrgMdr = rgMdr;
  sib.lrgUdr = rgUdr;

  //-----------------------------------
  // Buffer überprüfen lassen
  //-----------------------------------
  SEC secResult = lpfnSpellCheck(lSpellID, sccVerifyBuffer, &sib, &csrb.srb);

  if (secResult != secNOERRORS) {
    SetLastError(secResult);
    return FALSE;
    }

  //-----------------------------------
  // Ergebnisse zurückgeben
  //-----------------------------------
  *pScrs = csrb.srb.scrs;
  *pnErrorPos = csrb.srb.ichError;
  if ((csrb.srb.scrs == scrsReturningChangeAlways || 
       csrb.srb.scrs == scrsReturningChangeOnce) && psChange != NULL) {
    psChange = csrb.srb.lrgsz;
    }

  if (csrb.srb.scrs != scrsNoErrors && pnErrorLength != NULL)
    *pnErrorLength = csrb.srb.cchError;
  else
    *pnErrorPos = -1;
  
  return TRUE;
  }


//***************************************************************************
//*
//* Alternativvorschläge für ein Wort holen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::Suggestion (LPCSTR lpszWord, 
                                                  LPSTR  *pSuggestions,
                                                  WORD   nSpellState /*= fssNoStateInfo*/, 
                                                  int    nMaxEntryNum /*= -1*/)
  {
  //--------------------------
  // Buffer in SRB reservieren
  //--------------------------
  CSrb csrb;
  if (!csrb.Init(TRUE)) {
    SetLastError(secOOM);
    return FALSE;
    }

  //-----------------------------
  // Spell Input Buffer aufbauen
  //-----------------------------
  SIB sib;
  sib.cch = (unsigned short) lstrlen(lpszWord);
  sib.cMdr = (unsigned short) GetMdrNum();
  sib.cUdr = (unsigned short) GetUdrNum();
  sib.wSpellState = nSpellState;
  sib.lrgch = (CHAR FAR *) lpszWord;
  sib.lrgMdr = rgMdr;
  sib.lrgUdr = rgUdr;
    
  WORD nCurrentEntry = 0;
  int nCurrentArrayIndex = 0;
  int nAlreadyRetrieved = 0;
  SEC secResult;
  int nSteps;
  LPSTR sCurrentString = NULL;
  BOOL bGotAllEntries = FALSE;
  SCCC sccc = sccSuggest;

  //---------------------------------------------------------------------
  // Alternativvorschläge solange auslesen, bis keine weiteren vorhanden
  //  sind oder nMaxEntryNum erreicht ist
  //---------------------------------------------------------------------
  do {
    //------------------------------------------------------------
    // einen Satz Alternativvorschläge durch DLL-Aufruf auslesen
    //------------------------------------------------------------
    secResult = lpfnSpellCheck(lSpellID, sccc, &sib, &csrb.srb);
    if (secResult != secNOERRORS) {
      SetLastError(secResult);
      return FALSE;
      }

    nSteps = csrb.srb.csz;

    //---------------------------------------------------------------
    // Falls mehr Wörter vorhanden sind als beim Aufruf der Funktion
    //  angefordert wurden, brauchen wir nicht alle auszulesen
    //---------------------------------------------------------------
    if (nMaxEntryNum >= 0) {
      if (nAlreadyRetrieved + nSteps < nMaxEntryNum) {
        nSteps = nMaxEntryNum - nAlreadyRetrieved;
        bGotAllEntries = TRUE;
        }
      else {
        nAlreadyRetrieved += nSteps;
        }
      }

    if (sCurrentString == NULL) {
      sCurrentString = (LPSTR)GetGlobMem (csrb.srb.cchMac + 1);
      lmemcpy (sCurrentString, csrb.srb.lrgsz, csrb.srb.cchMac);
      }
    else {
      int iCurrentLen = GetBlockSize(sCurrentString);
      LPSTR lpszNewString = (LPSTR)GetGlobMem (iCurrentLen + 1 + csrb.srb.cchMac + 1);
      lmemcpy (lpszNewString, sCurrentString, iCurrentLen);
      lmemcpy (lpszNewString + iCurrentLen + 1, csrb.srb.lrgsz, csrb.srb.cchMac);
      FreeGlobMem (sCurrentString);
      sCurrentString = lpszNewString;
      }

    //---------------------------------------------------
    // ab dem 2. Mal müssen wir die DLL-Funktion mit dem
    //  Befehl sccSuggestMore aufrufen
    //---------------------------------------------------
    sccc = sccSuggestMore;
    
    } while (csrb.srb.scrs == scrsMoreInfoThanBufferCouldHold && !bGotAllEntries);


  *pSuggestions = (LPSTR)sCurrentString;

  return TRUE;
  }


//***************************************************************************
//*
//* Anagramme holen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::Anagram (LPCSTR lpszWord, 
                                               LPSTR  *pAnagrams, 
                                               int    nMaxEntryNum /*= -1*/)
  {
  return GetSimpleCheckList(sccAnagram, lpszWord, pAnagrams, nMaxEntryNum);
  }


//***************************************************************************
//*
//* Wildcards holen
//*
//***************************************************************************
DLLExport BOOL _export CSpellSession::Wildcard (LPCSTR lpszWord, 
                                                LPSTR  *pWildcards, 
                                                int nMaxEntryNum /*= -1*/)
  {
  return GetSimpleCheckList(sccWildcard, lpszWord, pWildcards, nMaxEntryNum);
  }


//***************************************************************************
//*
//* Hinweise zur Worttrennung holen
//*
//***************************************************************************
BOOL CSpellSession::Hyphenation(LPCSTR /*lpszWord*/, int* /*pnHyphNum*/,
  UINTArray* /*pHyphPoints*/, UINTArray* /*pHyphTypes*/)
  {
  // noch nicht implementiert
  return FALSE;
  }


//***************************************************************************
//*
//* Hilfsfunktion zum Holen von Anagrammen oder Wildcards
//*
//***************************************************************************
BOOL CSpellSession::GetSimpleCheckList (SCCC   sccc, 
                                        LPCSTR lpszWord,
                                        LPSTR *pResult, 
                                        int    nMaxEntryNum)
  {
  SIB sib;
  
  //---------------------------
  // Buffer in SRB reservieren
  //---------------------------
  CSrb csrb;
  if (!csrb.Init(TRUE)) {
    SetLastError(secOOM);
    return FALSE;
    }

  //-----------------------------
  // Spell Input Buffer aufbauen
  //-----------------------------
  sib.cch = (unsigned short) lstrlen(lpszWord);
  sib.cMdr = (unsigned short) GetMdrNum();
  sib.cUdr = (unsigned short) GetUdrNum();
  sib.wSpellState = fssNoStateInfo;
  sib.lrgch = (CHAR FAR *) lpszWord;
  sib.lrgMdr = rgMdr;
  sib.lrgUdr = rgUdr;
    
  //-----------------------
  // DLL-Funktion aufrufen
  //-----------------------
  SEC secResult = lpfnSpellCheck(lSpellID, sccc, &sib, &csrb.srb);
  if (secResult != secNOERRORS) {
    SetLastError(secResult);
    return FALSE;
    }

  int nSteps;
  LPSTR sCurrentString;

  nSteps = csrb.srb.csz;

  //---------------------------------------------------------------
  // Falls mehr Wörter vorhanden sind als beim Aufruf der Funktion
  //  angefordert wurden, brauchen wir nicht alle auszulesen
  //---------------------------------------------------------------
  if (nMaxEntryNum >= 0) {
    if (nMaxEntryNum < nSteps)
      nSteps = nMaxEntryNum;
    }

  sCurrentString = (LPSTR)GetGlobMem (csrb.srb.cchMac + 1);
  lmemcpy (sCurrentString, csrb.srb.lrgsz, csrb.srb.cchMac);

  *pResult = sCurrentString;

  return TRUE;
  }


//***************************************************************************
//*
//* Fehlercode des zuletzt beim Aufruf der Rechtschreib-DLL
//*  aufgetretenen Fehlers ermitteln
//*
//***************************************************************************
SEC CSpellSession::GetLastError()
  {
  return secLastError;
  }

//---------------------------------------------------------------------------
// Fehlercode des zuletzt beim Aufruf der Rechtschreib-DLL
//  aufgetretenen Fehlers festsetzen
//---------------------------------------------------------------------------
void CSpellSession::SetLastError(SEC secResult)
  {
  secLastError = secResult;
  }


//***************************************************************************
//*
//* neue Felder mit den MDRs und UDRs der offenen Wörterbücher anlegen
//*
//***************************************************************************
BOOL CSpellSession::RebuildDRLists()
  {
  MDR* rgNewMdr = NULL;
  UDR* rgNewUdr = NULL;
  int n, AnzMdr, AnzUdr;

  AnzMdr = MdrArray->GetSize();
  // neues Feld mit den MDRs der offenen Hauptwörterbücher anlegen
  if (AnzMdr > 0) {
    rgNewMdr = (MDR *)GetGlobMem (sizeof(*rgNewMdr) * AnzMdr);

    if (rgNewMdr == NULL)
      return FALSE;
      // Daten dort einfüllen
    for (n = 0; n < AnzMdr; n++) {
      rgNewMdr[n] = ((MdrDataStruct*) MdrArray->GetAt(n))->mdrs.mdr;
      }
    }

  AnzUdr = UdrArray->GetSize();

  // neues Feld mit den MDRs der offenen Benutzerwörterbücher anlegen
  if (AnzUdr > 0) {
    rgNewUdr = (UDR *)GetGlobMem(sizeof(*rgNewUdr) * AnzUdr);
    if (rgNewUdr == NULL) {
      FreeGlobMem (rgNewMdr);
      return FALSE;
      }

    // Daten einfüllen
    for (n = 0; n < AnzUdr; n++) {
      rgNewUdr[n] = ((UdrDataStruct*) UdrArray->GetAt(n))->udr;
      }
    }

  // alte Felder freigeben
  if (rgMdr != NULL)
    FreeGlobMem (rgMdr);

  if (rgUdr != NULL)
    FreeGlobMem (rgUdr);

  // und durch neue ersetzen
  rgMdr = rgNewMdr;
  rgUdr = rgNewUdr;

  return TRUE;
  }

