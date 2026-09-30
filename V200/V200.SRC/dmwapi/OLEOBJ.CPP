//--------------------------------------------------------------------------
// Hauptmodul fuer OLE2
//        Funktionen die fuer die Scriptbefehle benoetigt werden. 
//--------------------------------------------------------------------------
// $Header:   P:/marille/clinicum/dmwapi/rev/oleobj.cpv   1.15   22 Nov 1999 09:28:30   Hannes  $
// $Log:   P:/marille/clinicum/dmwapi/rev/oleobj.cpv  $
// 
//    Rev 1.15   22 Nov 1999 09:28:30   Hannes
// Diverse OLE - Erweiterungen..
// 
//    Rev 1.14   14 Jun 1999 20:40:06   Hannes
// RunAutomacro
// 
//    Rev 1.13   12 Feb 1999 16:05:16   Hannes
// RENDER_DRAW -> RENDER_NONE
// 
//    Rev 1.12   15 Jan 1999 18:20:36   Hannes
// Propertie - Handling
// 
//    Rev 1.11   05 Oct 1998 11:12:10   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   11 Sep 1998 16:32:20   Gerhold
// in den OLE-Funktionen auf m_pIOleObject == NULL abfragen
// 
//    Rev 1.9   04 Sep 1998 15:51:42   Gerhold
// Ein Haufen Kommentare sind dazu gekommen...
// 
//    Rev 1.8   28 Aug 1998 10:20:28   Gerhold
// SetOLEDocVarEx verbessert
// 
//    Rev 1.7   15 Aug 1998 15:59:56   Gerhold
// SetOleDocVarEx 
// 
//    Rev 1.6   14 Aug 1998 18:25:28   Gerhold
// GetMyIUnknow ... QueryInterfave (IID_UNKNOWN, ...)
// 
//    Rev 1.5   03 Aug 1998 18:04:38   Gerhold
// GetMyIUnknown war noch falsch
// 
//    Rev 1.4   31 Jul 1998 11:45:44   Gerhold
// SetOLEHostName
// 
//    Rev 1.3   30 Jul 1998 13:24:46   Gerhold
// OleInitialize und OleUninitialize sind jetzt in DDS.CPP
// 
//    Rev 1.2   29 Jul 1998 12:03:54   Gerhold
// OLEGetDocProp, OLERestrictInput, OLEUpdateFields
// 
//    Rev 1.1   28 Jul 1998 08:26:52   Gerhold
// SetDocVar
// 
//    Rev 1.0   22 Aug 1997 12:40:08   Gerhold
// Initial revision.
//--------------------------------------------------------------------------
#include <windows.h>

#include <ole2.h>

#include "dds32.h"

#define INITGUIDS

#ifndef WIN32
#include "dvobj.h"
#include "win1632.h"
#include "compobj.h"
#endif

#include "globmem.h"

#ifdef WIN32
#include <winbase.h>
#endif

#include <math.h>             // wegen OLEDateTime Funktionen
#include <time.h>

#include "iclisite.hpp"
#include "olemain.hpp"


#ifndef WIN32
#define FILE_BEGIN                  0
#define FILE_CURRENT                1
#define FILE_END                    2
#endif


static char szHostName[32];
DLLExport void _export SetOLEHostName (LPTSTR lpszHostName)
  {
  lstrcpy (szHostName, lpszHostName);
  }



//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
DLLExport _export COleFrame::COleFrame (HWND hWnd)
  {
//  OleInitialize (NULL);

  m_hWnd = hWnd;
  m_pDoc = NULL;
  Init ();
  }


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
DLLExport _export COleFrame::~COleFrame (void)
  {
  if (m_pDoc)
    delete m_pDoc;

//  OleUninitialize();
  }


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
BOOL COleFrame::Init()
  {
  m_pDoc = new CDocument(m_hWnd);

//*************************************************
//  if (m_pDoc)
//    return (m_pDoc->ULoad (NULL) == DOCERR_NONE);
//*************************************************

  return (m_pDoc != NULL);
  }


//---------------------------------------------------------------------------
// COleFrame::SaveCompoundFile
//
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::SaveCompoundFile (LPTSTR pszFile)
  {
  return m_pDoc->Save (pszFile);
  }

//---------------------------------------------------------------------------
// COleFrame::CreateFromFile
// 
// Zweck:
//   Erzeugt ein neues OLE-Object aus einer Datei
//
// Parameter:
//   pszFile    Name des Compound-Files
//---------------------------------------------------------------------------
BOOL COleFrame::CreateObjFromFile (LPTSTR pszFile)
  {
  return m_pDoc->ULoad (pszFile, NULL,TRUE);
  }


//---------------------------------------------------------------------------
// _export COleFrame::CreateObjFromHGlobal
// 
// Zweck:
//   Erzeugt ein neues OLE-Object aus einem Global-Handle
//
// Parameter:
//   hGlobal    Speicher der mit GlobalAlloc (GMEM-MOVEABLE) alloziert wurde
//
// Rueckgabewert:
//   TRUE wenn das Objekt erfolgreich angelegt wurde
//---------------------------------------------------------------------------
DLLExport UINT _export COleFrame::CreateObjFromHGlobal (HGLOBAL hGlobal,BOOL doActivate)
  {
  return m_pDoc->ULoad (NULL, hGlobal,doActivate);
  }

//---------------------------------------------------------------------------
// COleFrame::LoadCompoundFile
// 
// Zweck:
//   Lädt den Inhalt eines zuvor gespeicherten Compound-Files in den Speicher
//
// Parameter:
//   pszFile    Name des Compound-Files
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::LoadCompoundFile (LPTSTR pszFile)
  {
  HGLOBAL   hGlobal;
  OFSTRUCT  of;

  HFILE hf = OpenFile (pszFile, &of, OF_READ);

  if (hf == HFILE_ERROR)
    return FALSE;

  // ermitteln der Dateigroesse
  //----------------------------
  LONG fl = _llseek (hf, 0, FILE_END);
  _llseek (hf, 0, FILE_BEGIN);

  // Anfordern eines Speicherbereiches der fuer die ILockBytes
  // die Parameter GMEM_MOVEABLE und GMEM_SHARE benoetigt
  //-----------------------------------------------------------
  hGlobal = GlobalAlloc (GHND | GMEM_SHARE, fl);

  LPVOID lpBuf = GlobalLock (hGlobal);

  // den Inhalt der Datei in den Speicher laden
  //--------------------------------------------
  long uiRead = _hread (hf, lpBuf, fl);

  _lclose (hf);

  GlobalUnlock (hGlobal);

  return m_pDoc->ULoad (NULL, hGlobal,FALSE);
  }


DLLExport HGLOBAL _export COleFrame::GetHGlobalFromOLEObj (DWORD FAR *lpsize)
  {
  return m_pDoc->GetHGlobalFromLockBytes (lpsize);
  }


//---------------------------------------------------------------------------
// COleFrame::SetDocVar
// 
// Zweck:
//   
//
// Parameter:
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::SetDocVar (LPTSTR lpstrName, LPTSTR lpstrValue)
  {
  return m_pDoc->SetDocVar (lpstrName, lpstrValue);
  }

DLLExport BOOL _export COleFrame::RunAutoMacro (int wdAutoVar)
  {
  return m_pDoc->RunAutoMacro (wdAutoVar);
  }

//---------------------------------------------------------------------------
// COleFrame::SetDocVarEx
// 
// Zweck:
//   
//
// Parameter:
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::SetDocVarEx (LPTSTR lpstrName, LPTSTR lpstrValue)
  {
  return m_pDoc->SetDocVarEx (lpstrName, lpstrValue);
  }


//---------------------------------------------------------------------------
// COleFrame::GetDocVar
// 
// Zweck:
//   
//
// Parameter:
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::GetDocVar (LPTSTR lpstrName, LPTSTR lpstrValue)
  {
  return m_pDoc->GetDocVar (lpstrName, lpstrValue);
  }


//---------------------------------------------------------------------------
// COleFrame::PrintDoc
// 
// Zweck:
//   
//
// Parameter:
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::PrintDoc (BOOL bSelectPrinter)
  {
  return m_pDoc->PrintDoc (bSelectPrinter);
  }


//---------------------------------------------------------------------------
// COleFrame::GetMyIUnknown
// 
// Zweck:
//   
//
// Parameter:
//
//---------------------------------------------------------------------------
DLLExport BOOL _export COleFrame::GetMyIUnknown (LPUNKNOWN FAR *MyObj)
  {
  return m_pDoc->GetMyIUnknown (MyObj);
  }



DLLExport BOOL _export COleFrame::GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue)
  {
  return m_pDoc->GetOLEDocProp (iKind, iIndex, lpszName, lpszValue);
  }


DLLExport BOOL _export COleFrame::RestrictInput (int iLevel, LPTSTR lpszPassWord)
  {
  return m_pDoc->RestrictInput (iLevel, lpszPassWord);
  }


DLLExport BOOL _export COleFrame::UpdateFields ()
  {
  return m_pDoc->UpdateFields ();
  }


DLLExport BOOL _export COleFrame::CloseApplicationWord (int iSaveChanges)
  {
  return m_pDoc->CloseApplicationWord (iSaveChanges);
  }


DLLExport BOOL _export COleFrame::SaveWordObjectAs (LPTSTR lpszFileName, int iFormat)
  {
  return m_pDoc->SaveWordObjectAs (lpszFileName, iFormat);
  }


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
CDocument::CDocument (HWND hWnd)
  {
  m_pIStorage = NULL;
  m_pOleObj = NULL;
  m_pLockBytes = NULL;
  m_hWnd = hWnd;
  BOOL ret = Init ();
  }


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
CDocument::~CDocument (void)
  {
  Close ();

  CoFreeUnusedLibraries ();
  }

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
BOOL CDocument::Init ()
  {
  return TRUE;
  }

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
void CDocument::Close ()
  {
  if (m_pIStorage) {
    m_pIStorage->Release();
    m_pIStorage = NULL;
    }

  if (m_pOleObj) {
    m_pOleObj->Close ();
    m_pOleObj->Release ();
    }

  if (m_pLockBytes) {
    m_pLockBytes->Release();
    m_pLockBytes = NULL;
    }
  }


//---------------------------------------------------------------------------
// CDocument::ULoad
//
// Zweck:
//
// Parameter:
//   pszFile      Name der Datei aus der das OLE-Objekt erzeugt wird
//                Ist der Wert von hGlobal ungleich NULL wird dieser
//                Parameter ignoriert !!!
//
//   hGlobal      Handle des Speichers in dem das Compound-File abgelegt ist.
//                Hat hGlobal den Wert NULL, so wird ein neues Compound-File
//                erzeugt.
//                Bei einem gueltigen Handle wird das OLE-Objekt aus dem 
//                Inhalt des Speichers erzeugt.
//---------------------------------------------------------------------------
UINT CDocument::ULoad (LPTSTR pszFile, HGLOBAL hGlobal, BOOL doActivate)
  {
  LPSTORAGE   pIStorage;
  HRESULT     hr;
  CLSID       clsID;
  LPLOCKBYTES lpLockBytes = NULL;
  DWORD       dwMode = STGM_DIRECT |         // Aenderungen werden nicht gebuffert.
                       STGM_READWRITE  |     // das Objekt laesst Lesen und Schreiben zu.
                       STGM_SHARE_EXCLUSIVE; // das Objekt wird exklusiv fuer Lese- und
                                             // Schreibzugriffe geoeffnet.

  //-----------------------------------------------------------------------------
  // erzeugt aus dem Speicherinhalt das Flat-Memory-Abbild des Compound-Files
  // in lpLockBytes. Hat hGlobal den Wert NULL wird in CreateILockBytesOnHGlobal
  // ein neuer Speicherblock mit der Groesse Null angelegt und bei Bedarf durch
  // GlobalReAlloc erweitert.
  // Der zweite Parameter gibt an, ob der Speicherhandle bei <LockBytes::Release>
  // automatisch freigegeben werden soll. Das wurde hier ausgeschaltet; d.h der
  // Handle-Erzeuger muß den Speicher selbst wieder freigeben.
  //-----------------------------------------------------------------------------
  hr = CreateILockBytesOnHGlobal (hGlobal, FALSE, (LPLOCKBYTES FAR*)&lpLockBytes);
  if (hr != NOERROR)
    return DOCERR_COULDNOTCREATELOCKBYTES;

  if (hGlobal == NULL) {

    //--------------------------------------------------------------
    // erzeugt aus den LockBytes ein Storage-Objekt in dem das neue 
    // Objekt gespeichert wird
    //--------------------------------------------------------------
    hr = StgCreateDocfileOnILockBytes (lpLockBytes,
                                       dwMode | STGM_CREATE,
                                       0,
                                       (LPSTORAGE FAR*)&pIStorage);


    if (SUCCEEDED(hr))
      //----------------------------------------------------------------
      // Das wird jetzt unsere Klasse; zur Erkennung durch ReadClassStg
      // schreiben wir auch brav unseren Klassen-ID hinein.
      //----------------------------------------------------------------
      WriteClassStg(pIStorage, CLSID_DDSOle);
    else
      return DOCERR_COULDNOTCREATESTORAGE;

    }
  else {
    //-------------------------------------------------------
    // Hat das mit den Lockbytes auch wirklich funktioniert?
    //-------------------------------------------------------
    hr = StgIsStorageILockBytes (lpLockBytes);
    if (hr != NOERROR)
      return DOCERR_NOTVALIDLOCKBYTES;

    //---------------------------------------------
    // das in den LockBytes abgebildete OLE-Objekt
    // wird in das Storage-Objekt geladen
    //---------------------------------------------
    hr = StgOpenStorageOnILockBytes (lpLockBytes, NULL, dwMode, NULL, 0, &pIStorage);
    if (hr != NOERROR)
      return DOCERR_COULDNOTOPENSTORAGE;
      
    }

  if (FAILED(hr))
    return DOCERR_COULDNOTOPEN;

  //-----------------------------------------------------------------
  // Zuerst einmal probieren ob unser Klassen-ID gelesen werden kann.
  //-----------------------------------------------------------------
  hr = ReadClassStg (pIStorage, &clsID);

  if (FAILED(hr) || CLSID_DDSOle != clsID) {
    pIStorage->Release();
    return DOCERR_READFAILURE;
    }

  m_pIStorage = pIStorage;

  m_pLockBytes = lpLockBytes;


  FORMATETC fetc;

  fetc.cfFormat = 0;                 // Clipboard-Format
  fetc.dwAspect = DVASPECT_CONTENT;  // Darstellungsmodus beim Zeichnen
  fetc.ptd = NULL;                   // Zeiger auf ein DVTARGETDEVICE
  fetc.tymed = TYMED_NULL;           // keine Daten
  fetc.lindex = -1;                  // Standard wenn keine ICON-Darstellung

  //------------------------------------
  // Jetzt wirds erst richtig lustig!!
  //------------------------------------
  m_pOleObj = new COleObject (pIStorage, m_hWnd);
  if (m_pOleObj) {
    m_pOleObj->AddRef ();
    m_pOleObj->Open (pIStorage);     // Erzeugt einen SubStorage und die
                                     // ClientSite und AdviseSink
    if (hGlobal != NULL) {
      m_pOleObj->Load (&fetc);       // Laden des OLE-Objektes
      m_pOleObj->ActivateObject (doActivate);  // Aufrufen des Servers
      }
    else
      {
      if (pszFile != NULL) {
        if (!m_pOleObj->UCreate (pszFile, &fetc)) {  // Erzeugen des OLE-Objektes
          
          }
        }
      }
    }
  else {
    pIStorage->Release();
    }

  return DOCERR_NONE;
  }


//---------------------------------------------------------------------------
// CDocument::Save ()
//
// Zweck:
//   Speichern der LockBytes in eine Datei
//---------------------------------------------------------------------------
BOOL CDocument::Save (LPTSTR pszFile)
  {
//  HRESULT hr;
  HGLOBAL hNewGlobal;
//  STATSTG statstg;
  DWORD dwBytes;

  hNewGlobal = GetHGlobalFromLockBytes (&dwBytes);
  if (hNewGlobal != NULL) {

//    m_pOleObj->SaveObject ();

    //---------------------------------
    // Groesse der LockBytes ermitteln
    //---------------------------------
//    hr = m_pLockBytes->Stat (&statstg, STATFLAG_NONAME);
//    DWORD dwBytes = statstg.cbSize.LowPart;

//    hr = StgIsStorageILockBytes (m_pLockBytes);

    //-------------------------------------------------------------------
    // Da die LockBytes bei Bedarf den Speicher intern mit GlobalReAlloc 
    // vergroessern muss das Speicherhandle jetzt abgefragt werden
    //-------------------------------------------------------------------
//    hr = GetHGlobalFromILockBytes (m_pLockBytes, &hNewGlobal);

    LPVOID lpBuf = GlobalLock (hNewGlobal);

    OFSTRUCT of;
    HFILE hf = OpenFile (pszFile, &of, OF_CREATE | OF_WRITE);
    _hwrite (hf, (LPCSTR)lpBuf, dwBytes);
    _lclose (hf);

    GlobalUnlock (hNewGlobal);
    return TRUE;
    }

  return FALSE;
  }


//---------------------------------------------------------------------------
// CDocument::GetHGlobalFromLockBytes ()
//
// Zweck:
//   
//---------------------------------------------------------------------------
HGLOBAL CDocument::GetHGlobalFromLockBytes (DWORD FAR *dwBytes)
  {
  HGLOBAL hNewGlobal = NULL;

  if (m_pLockBytes != NULL) {

    HRESULT hr;
    STATSTG statstg;

    m_pOleObj->SaveObject ();

    //---------------------------------
    // Groesse der LockBytes ermitteln
    //---------------------------------
    hr = m_pLockBytes->Stat (&statstg, STATFLAG_NONAME);
    *dwBytes = statstg.cbSize.LowPart;

    hr = StgIsStorageILockBytes (m_pLockBytes);

    //-------------------------------------------------------------------
    // Da die LockBytes bei Bedarf den Speicher intern mit GlobalReAlloc 
    // vergroessern muss das Speicherhandle jetzt abgefragt werden
    //-------------------------------------------------------------------
    hr = GetHGlobalFromILockBytes (m_pLockBytes, &hNewGlobal);
    }

  return hNewGlobal;
  }


//---------------------------------------------------------------------------
// CDocument::SetDocVar ()
//
// Zweck:
//   
//---------------------------------------------------------------------------
BOOL CDocument::SetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pOleObj) {
    return m_pOleObj->SetDocVar (lpstrName, lpstrValue);
    }

  return FALSE;
  }

BOOL CDocument::RunAutoMacro (int wdAutoVar)
  {
  if (m_pOleObj) {
    return m_pOleObj->RunAutoMacro (wdAutoVar);
    }

  return FALSE;
  }

//---------------------------------------------------------------------------
// CDocument::SetDocVarEx
//
// Zweck:
//   
//---------------------------------------------------------------------------
BOOL CDocument::SetDocVarEx (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pOleObj) {
    return m_pOleObj->SetDocVarEx (lpstrName, lpstrValue);
    }

  return FALSE;
  }


//---------------------------------------------------------------------------
// CDocument::GetDocVar ()
//
// Zweck:
//   
//---------------------------------------------------------------------------
BOOL CDocument::GetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pOleObj) {
    return m_pOleObj->GetDocVar (lpstrName, lpstrValue);
    }

  return FALSE;
  }


//---------------------------------------------------------------------------
// CDocument::PrintDoc ()
//
// Zweck:
//   
//---------------------------------------------------------------------------
BOOL CDocument::PrintDoc (BOOL bSelectPrinter)
  {
  if (m_pOleObj) {
    return m_pOleObj->PrintDoc (bSelectPrinter);
    }

  return FALSE;
  }

//---------------------------------------------------------------------------
// CDocument::GetMyIUnknown
//
// Zweck:
//   
//---------------------------------------------------------------------------
BOOL CDocument::GetMyIUnknown (LPUNKNOWN FAR *MyObj)
  {
  if (m_pOleObj) {
    return m_pOleObj->GetMyIUnknown (MyObj);
    }

  return FALSE;
  }


BOOL CDocument::GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue)
  {
  if (m_pOleObj)
    return m_pOleObj->GetOLEDocProp (iKind, iIndex, lpszName, lpszValue);

  return FALSE;
  }


BOOL CDocument::RestrictInput (int iLevel, LPTSTR lpszPassWord)
  {
  if (m_pOleObj)
    return m_pOleObj->RestrictInput (iLevel, lpszPassWord);

  return FALSE;
  }


BOOL CDocument::UpdateFields ()
  {
  if (m_pOleObj)
    return m_pOleObj->UpdateFields ();

  return FALSE;
  }


BOOL CDocument::CloseApplicationWord (int iSaveChanges)
  {
  if (m_pOleObj)
    return m_pOleObj->CloseApplicationWord (iSaveChanges);

  return FALSE;
  }


BOOL CDocument::SaveWordObjectAs (LPTSTR lpszFileName, int iFormat)
  {
  if (m_pOleObj)
    return m_pOleObj->SaveWordObjectAs (lpszFileName, iFormat);

  return FALSE;
  }



//---------------------------------------------------------------------------
// COleObject::COleObject
//
//
//---------------------------------------------------------------------------
COleObject::COleObject (LPSTORAGE pIStorage, HWND hWnd)
  {
  m_pIOleObject=NULL;
  m_pIOleClientSite=NULL;
  m_pIAdviseSink=NULL;
  m_pObj = NULL;

  m_pIStorage = NULL;
  m_hWnd = hWnd;
  m_cRef = 0;

  p = NULL;
  }

//---------------------------------------------------------------------------
// COleObject::~COleObject
//
//
//---------------------------------------------------------------------------
COleObject::~COleObject (void)
  {
  if (m_pIAdviseSink != NULL)
    delete (m_pIAdviseSink);

  if (m_pIOleClientSite != NULL)
    delete (m_pIOleClientSite);

  for ( ; p != NULL ; ) {
    PropList FAR *n = p->Next ;
    if (p->Name) FreeGlobMem (p->Name);
    if (p->Value) FreeGlobMem (p->Value);
    FreeGlobMem (p);
    p = n;
    }
  }


//---------------------------------------------------------------------------
// COleObject::Close
//
//
//---------------------------------------------------------------------------
void COleObject::Close ()
  {
  if (m_pIStorage) 
    m_pIStorage->Release ();

  m_pIStorage = NULL;

  if (m_pIOleObject) {
    m_pIOleObject->Close (OLECLOSE_NOSAVE);
    m_pIOleObject->Release ();
    m_pIOleObject = NULL;
    }

  if (m_pObj) {
    m_pObj->Release ();
    m_pObj = NULL;
    }
  }


//---------------------------------------------------------------------------
// COleObject::Open
//
//
//---------------------------------------------------------------------------
BOOL COleObject::Open (LPSTORAGE pIStorage)
  {
  HRESULT     hr = NOERROR;
  TCHAR       szTemp[MAX_PATH];
  DWORD       dwMode = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;

  if (NULL == m_pIStorage) {
    if (NULL == pIStorage)
      return FALSE;

     // Attempt to open the storage under this ID.  If there is
     // none, then create it.  In either case we end up with an
     // IStorage that we either save in pPage or release.

    lstrcpy (szTemp, "CLINICUM");
    OLECHAR pwcsTemp[MAX_PATH];

#if defined(WIN32) && !defined(UNICODE)
    mbstowcs(pwcsTemp, szTemp, MAX_PATH);
#else
    lstrcpy(pwcsTemp, szTemp);
#endif

    hr=pIStorage->OpenStorage(pwcsTemp, NULL, dwMode, NULL, 0, &m_pIStorage);

    if (FAILED(hr)) {
      hr=pIStorage->CreateStorage(pwcsTemp, dwMode, 0, 0, &m_pIStorage);
      }
    }
  else
    m_pIStorage->AddRef();

  if (FAILED(hr))
    return FALSE;

  m_pIOleClientSite = new CImpIOleClientSite(this, this);
  m_pIAdviseSink = new CImpIAdviseSink(this, this);

  if (NULL == m_pIOleClientSite || NULL == m_pIAdviseSink)
    return FALSE;

  return TRUE;
  }


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
BOOL COleObject::Load (LPFORMATETC pfe)
  {
  LPUNKNOWN   pObj;

  HRESULT hr = OleLoad (m_pIStorage, IID_IUnknown, NULL, (PPVOID)&pObj);

  if (FAILED(hr)) {
    return FALSE;
    }

  FObjectInitialize(pObj, pfe);
  return TRUE;
  }

#ifdef DEBUG
#define CASE_SCODE(sc)  \
    case sc: \
      lstrcpy((LPSTR)szErrName, (LPSTR)#sc); \
      break;
#endif


//---------------------------------------------------------------------------
// COleObject::UCreate
//
//
//---------------------------------------------------------------------------
BOOL COleObject::UCreate (LPTSTR pszFile, LPFORMATETC pfe)
  {
  HRESULT     hr = NOERROR;
  LPUNKNOWN   pObj;

#if defined(WIN32) && !defined(UNICODE)
  OLECHAR pwcsTemp[MAX_PATH];
  mbstowcs(pwcsTemp, (LPTSTR)pszFile, MAX_PATH);

  hr = OleCreateFromFile (CLSID_NULL,     // reserviert
                          pwcsTemp,       // Name der Datei aus der das Objekt erzeugt wird
                          IID_IUnknown,   // Identifier des Interfaces
                          // OLERENDER_DRAW, // der Client will das Objekt selber zeichnen
                          OLERENDER_NONE, // der Client will das Objekt selber zeichnen
                          NULL, 
                          NULL, 
                          m_pIStorage,    // Zeiger auf das IStorage-Interface
                          (PPVOID)&pObj); 
#else
  hr=OleCreateFromFile (CLSID_NULL, 
                        (LPTSTR)pszFile, 
                        IID_IUnknown, 
                        OLERENDER_DRAW, 
                        NULL, 
                        m_pIOleClientSite,
                        m_pIStorage, 
                        (PPVOID)&pObj);

#ifdef DEBUG
  char szTmp[100];
  SCODE scode = GetScode(hr);

  char szErrName[40];

  switch (scode) {
    CASE_SCODE(S_OK)
    CASE_SCODE(S_FALSE)
    CASE_SCODE(E_UNEXPECTED)
    CASE_SCODE(E_OUTOFMEMORY)
    CASE_SCODE(E_INVALIDARG)
    CASE_SCODE(E_NOINTERFACE)
    CASE_SCODE(E_POINTER)
    CASE_SCODE(E_HANDLE)
    CASE_SCODE(E_ABORT)
    CASE_SCODE(E_FAIL)
    CASE_SCODE(E_ACCESSDENIED)

    /* SCODE's defined in OLE2.H */

    CASE_SCODE(OLE_E_OLEVERB)
    CASE_SCODE(OLE_E_ADVF)
    CASE_SCODE(OLE_E_ENUM_NOMORE)
    CASE_SCODE(OLE_E_ADVISENOTSUPPORTED)
    CASE_SCODE(OLE_E_NOCONNECTION)
    CASE_SCODE(OLE_E_NOTRUNNING)
    CASE_SCODE(OLE_E_NOCACHE)
    CASE_SCODE(OLE_E_BLANK)
    CASE_SCODE(OLE_E_CLASSDIFF)
    CASE_SCODE(OLE_E_CANT_GETMONIKER)
    CASE_SCODE(OLE_E_CANT_BINDTOSOURCE)
    CASE_SCODE(OLE_E_STATIC)
    CASE_SCODE(OLE_E_PROMPTSAVECANCELLED)
    CASE_SCODE(OLE_E_INVALIDRECT)
    CASE_SCODE(OLE_E_WRONGCOMPOBJ)
    CASE_SCODE(OLE_E_INVALIDHWND)
    CASE_SCODE(OLE_E_NOT_INPLACEACTIVE)
    CASE_SCODE(OLE_E_CANTCONVERT)
    CASE_SCODE(OLE_E_NOSTORAGE)

    CASE_SCODE(DV_E_FORMATETC)
    CASE_SCODE(DV_E_DVTARGETDEVICE)
    CASE_SCODE(DV_E_STGMEDIUM)
    CASE_SCODE(DV_E_STATDATA)
    CASE_SCODE(DV_E_LINDEX)
    CASE_SCODE(DV_E_TYMED)
    CASE_SCODE(DV_E_CLIPFORMAT)
    CASE_SCODE(DV_E_DVASPECT)
    CASE_SCODE(DV_E_DVTARGETDEVICE_SIZE)
    CASE_SCODE(DV_E_NOIVIEWOBJECT)

    CASE_SCODE(OLE_S_USEREG)
    CASE_SCODE(OLE_S_STATIC)
    CASE_SCODE(OLE_S_MAC_CLIPFORMAT)

    CASE_SCODE(CONVERT10_E_OLESTREAM_GET)
    CASE_SCODE(CONVERT10_E_OLESTREAM_PUT)
    CASE_SCODE(CONVERT10_E_OLESTREAM_FMT)
    CASE_SCODE(CONVERT10_E_OLESTREAM_BITMAP_TO_DIB)
    CASE_SCODE(CONVERT10_E_STG_FMT)
    CASE_SCODE(CONVERT10_E_STG_NO_STD_STREAM)
    CASE_SCODE(CONVERT10_E_STG_DIB_TO_BITMAP)
    CASE_SCODE(CONVERT10_S_NO_PRESENTATION)

    CASE_SCODE(CLIPBRD_E_CANT_OPEN)
    CASE_SCODE(CLIPBRD_E_CANT_EMPTY)
    CASE_SCODE(CLIPBRD_E_CANT_SET)
    CASE_SCODE(CLIPBRD_E_BAD_DATA)
    CASE_SCODE(CLIPBRD_E_CANT_CLOSE)

    CASE_SCODE(DRAGDROP_E_NOTREGISTERED)
    CASE_SCODE(DRAGDROP_E_ALREADYREGISTERED)
    CASE_SCODE(DRAGDROP_E_INVALIDHWND)
    CASE_SCODE(DRAGDROP_S_DROP)
    CASE_SCODE(DRAGDROP_S_CANCEL)
    CASE_SCODE(DRAGDROP_S_USEDEFAULTCURSORS)

    CASE_SCODE(OLEOBJ_E_NOVERBS)
    CASE_SCODE(OLEOBJ_E_INVALIDVERB)
    CASE_SCODE(OLEOBJ_S_INVALIDVERB)
    CASE_SCODE(OLEOBJ_S_CANNOT_DOVERB_NOW)
    CASE_SCODE(OLEOBJ_S_INVALIDHWND)
    CASE_SCODE(INPLACE_E_NOTUNDOABLE)
    CASE_SCODE(INPLACE_E_NOTOOLSPACE)
    CASE_SCODE(INPLACE_S_TRUNCATED)

    /* SCODE's defined in COMPOBJ.H */

    CASE_SCODE(CO_E_NOTINITIALIZED)
    CASE_SCODE(CO_E_ALREADYINITIALIZED)
    CASE_SCODE(CO_E_CANTDETERMINECLASS)
    CASE_SCODE(CO_E_CLASSSTRING)
    CASE_SCODE(CO_E_IIDSTRING)
    CASE_SCODE(CO_E_APPNOTFOUND)
    CASE_SCODE(CO_E_APPSINGLEUSE)
    CASE_SCODE(CO_E_ERRORINAPP)
    CASE_SCODE(CO_E_DLLNOTFOUND)
    CASE_SCODE(CO_E_ERRORINDLL)
    CASE_SCODE(CO_E_WRONGOSFORAPP)
    CASE_SCODE(CO_E_OBJNOTREG)
    CASE_SCODE(CO_E_OBJISREG)
    CASE_SCODE(CO_E_OBJNOTCONNECTED)
    CASE_SCODE(CO_E_APPDIDNTREG)
    CASE_SCODE(CLASS_E_NOAGGREGATION)
    CASE_SCODE(CLASS_E_CLASSNOTAVAILABLE)
    CASE_SCODE(REGDB_E_READREGDB)
    CASE_SCODE(REGDB_E_WRITEREGDB)
    CASE_SCODE(REGDB_E_KEYMISSING)
    CASE_SCODE(REGDB_E_INVALIDVALUE)
    CASE_SCODE(REGDB_E_CLASSNOTREG)
    CASE_SCODE(REGDB_E_IIDNOTREG)
    CASE_SCODE(RPC_E_CALL_REJECTED)
    CASE_SCODE(RPC_E_CALL_CANCELED)
    CASE_SCODE(RPC_E_CANTPOST_INSENDCALL)
    CASE_SCODE(RPC_E_CANTCALLOUT_INASYNCCALL)
    CASE_SCODE(RPC_E_CANTCALLOUT_INEXTERNALCALL)
    CASE_SCODE(RPC_E_CONNECTION_TERMINATED)
    CASE_SCODE(RPC_E_SERVER_DIED)
    CASE_SCODE(RPC_E_CLIENT_DIED)
    CASE_SCODE(RPC_E_INVALID_DATAPACKET)
    CASE_SCODE(RPC_E_CANTTRANSMIT_CALL)
    CASE_SCODE(RPC_E_CLIENT_CANTMARSHAL_DATA)
    CASE_SCODE(RPC_E_CLIENT_CANTUNMARSHAL_DATA)
    CASE_SCODE(RPC_E_SERVER_CANTMARSHAL_DATA)
    CASE_SCODE(RPC_E_SERVER_CANTUNMARSHAL_DATA)
    CASE_SCODE(RPC_E_INVALID_DATA)
    CASE_SCODE(RPC_E_INVALID_PARAMETER)
    CASE_SCODE(RPC_E_CANTCALLOUT_AGAIN)
    CASE_SCODE(RPC_E_UNEXPECTED)

    /* SCODE's defined in DVOBJ.H */

    CASE_SCODE(DATA_S_SAMEFORMATETC)
    CASE_SCODE(VIEW_E_DRAW)
    CASE_SCODE(VIEW_S_ALREADY_FROZEN)
    CASE_SCODE(CACHE_E_NOCACHE_UPDATED)
    CASE_SCODE(CACHE_S_FORMATETC_NOTSUPPORTED)
    CASE_SCODE(CACHE_S_SAMECACHE)
    CASE_SCODE(CACHE_S_SOMECACHES_NOTUPDATED)

    /* SCODE's defined in STORAGE.H */

    CASE_SCODE(STG_E_INVALIDFUNCTION)
    CASE_SCODE(STG_E_FILENOTFOUND)
    CASE_SCODE(STG_E_PATHNOTFOUND)
    CASE_SCODE(STG_E_TOOMANYOPENFILES)
    CASE_SCODE(STG_E_ACCESSDENIED)
    CASE_SCODE(STG_E_INVALIDHANDLE)
    CASE_SCODE(STG_E_INSUFFICIENTMEMORY)
    CASE_SCODE(STG_E_INVALIDPOINTER)
    CASE_SCODE(STG_E_NOMOREFILES)
    CASE_SCODE(STG_E_DISKISWRITEPROTECTED)
    CASE_SCODE(STG_E_SEEKERROR)
    CASE_SCODE(STG_E_WRITEFAULT)
    CASE_SCODE(STG_E_READFAULT)
    CASE_SCODE(STG_E_SHAREVIOLATION)
    CASE_SCODE(STG_E_LOCKVIOLATION)
    CASE_SCODE(STG_E_FILEALREADYEXISTS)
    CASE_SCODE(STG_E_INVALIDPARAMETER)
    CASE_SCODE(STG_E_MEDIUMFULL)
    CASE_SCODE(STG_E_ABNORMALAPIEXIT)
    CASE_SCODE(STG_E_INVALIDHEADER)
    CASE_SCODE(STG_E_INVALIDNAME)
    CASE_SCODE(STG_E_UNKNOWN)
    CASE_SCODE(STG_E_UNIMPLEMENTEDFUNCTION)
    CASE_SCODE(STG_E_INVALIDFLAG)
    CASE_SCODE(STG_E_INUSE)
    CASE_SCODE(STG_E_NOTCURRENT)
    CASE_SCODE(STG_E_REVERTED)
    CASE_SCODE(STG_E_CANTSAVE)
    CASE_SCODE(STG_E_OLDFORMAT)
    CASE_SCODE(STG_E_OLDDLL)
    CASE_SCODE(STG_E_SHAREREQUIRED)
    CASE_SCODE(STG_E_NOTFILEBASEDSTORAGE)
    CASE_SCODE(STG_E_EXTANTMARSHALLINGS)
    CASE_SCODE(STG_S_CONVERTED)

    /* SCODE's defined in STORAGE.H */

    CASE_SCODE(MK_E_CONNECTMANUALLY)
    CASE_SCODE(MK_E_EXCEEDEDDEADLINE)
    CASE_SCODE(MK_E_NEEDGENERIC)
    CASE_SCODE(MK_E_UNAVAILABLE)
    CASE_SCODE(MK_E_SYNTAX)
    CASE_SCODE(MK_E_NOOBJECT)
    CASE_SCODE(MK_E_INVALIDEXTENSION)
    CASE_SCODE(MK_E_INTERMEDIATEINTERFACENOTSUPPORTED)
    CASE_SCODE(MK_E_NOTBINDABLE)
    CASE_SCODE(MK_E_NOTBOUND)
    CASE_SCODE(MK_E_CANTOPENFILE)
    CASE_SCODE(MK_E_MUSTBOTHERUSER)
    CASE_SCODE(MK_E_NOINVERSE)
    CASE_SCODE(MK_E_NOSTORAGE)
    CASE_SCODE(MK_E_NOPREFIX)
    CASE_SCODE(MK_S_REDUCED_TO_SELF)
    CASE_SCODE(MK_S_ME)
    CASE_SCODE(MK_S_HIM)
    CASE_SCODE(MK_S_US)
    CASE_SCODE(MK_S_MONIKERALREADYREGISTERED)

    default:
      lstrcpy(szErrName, "UNKNOWN SCODE");
    }

  if (hr != NOERROR)
    MessageBox (GetActiveWindow(), szErrName, szErrName, MB_OK);
#endif  // DEBUG

#endif // WIN32

  if (hr != NOERROR)
    return FALSE;

  FObjectInitialize(pObj, pfe);
  return TRUE;
  }


//---------------------------------------------------------------------------
// COleObject::FObjectInitialize
//
//
//---------------------------------------------------------------------------
BOOL COleObject::FObjectInitialize (LPUNKNOWN pObj, LPFORMATETC pfe)
  {
  HRESULT         hr;
  LPPERSIST       pIPersist=NULL;
  DWORD           dw;

  if ((NULL==pObj) || (NULL==pfe))
    return FALSE;

  m_pObj = pObj;

  if (SUCCEEDED(pObj->QueryInterface(IID_IPersist, (PPVOID)&pIPersist)))
    {
    CLSID   clsid = CLSID_NULL;

    hr = pIPersist->GetClassID(&clsid);

    //If we don't have a CLSID, default to static
    if (FAILED(hr) || CLSID_Picture_Metafile==clsid || CLSID_Picture_Dib==clsid)
      MessageBeep (0);

    pIPersist->Release();
    }

  //We need an IOleObject most of the time, so get one here.
  m_pIOleObject = NULL;
  hr = pObj->QueryInterface(IID_IOleObject, (PPVOID)&m_pIOleObject);

   // Follow up object creation with advises and so forth.  If
   // we cannot get IOleObject here, then we know we can't do
   // any IOleObject actions from here on--object is static.

  if (FAILED(hr))
      return TRUE;

  //-----------------------------------------------------------------------
  // Ueberpruefe die MiscStatus-Bits, und besonders auf OLEMISC_ONLYICONIC,
  // um das Objekt richtig zu zeichen (pfe->dwAspect)
  //-----------------------------------------------------------------------
  m_pIOleObject->GetMiscStatus(pfe->dwAspect, &m_grfMisc);

  if (OLEMISC_ONLYICONIC & m_grfMisc)
    pfe->dwAspect=DVASPECT_ICON;


  // We could pass m_pIOleClientSite in an OleCreate* call, but
  // since this function could be called after OleLoad, we still
  // need to do this here, so it's always done here...

  m_pIOleObject->SetClientSite(m_pIOleClientSite);
  m_pIOleObject->Advise(m_pIAdviseSink, &dw);

  OleSetContainedObject(m_pIOleObject, TRUE);

//  char szApp[40];
//  lstrcpy (szApp, "CLINICUM");

#if defined(WIN32) && !defined(UNICODE)
  OLECHAR pwcsApp[40];
  mbstowcs(pwcsApp, szHostName, lstrlen(szHostName)+1);
  m_pIOleObject->SetHostNames(pwcsApp, pwcsApp);
#else
  m_pIOleObject->SetHostNames(szHostName, szHostName);
#endif

  return TRUE;
  }


//---------------------------------------------------------------------------
// COleObject::ActivateObject
//
// Zweck:
//   Aufrufen des Servers mit dem geladenen OLE-Objekt
//---------------------------------------------------------------------------
BOOL COleObject::ActivateObject (BOOL doActivate)
  {
  RECT rc;

  if (m_pIOleObject)
    OleRun(m_pIOleObject);
  else
    return FALSE;

  GetClientRect (m_hWnd, &rc);
  m_pIOleObject->DoVerb(OLEIVERB_OPEN, NULL, m_pIOleClientSite, 0, m_hWnd, &rc);

  return TRUE;
  }


//---------------------------------------------------------------------------
// COleObject::SaveObject
//
// Zweck:
//   Speichert das OLE-Objekt im Storage-Objekt
//   Diese Funktion wird von ClientSite::SaveObject aufgerufen !!
//---------------------------------------------------------------------------
void COleObject::SaveObject ()
  {
  for ( PropList FAR *x = p ; x != NULL ; ) {
    char szName[1024];
    char szValue[2048];
    DBBOOL res = GetOLEDocProp (x->iKind, x->iIndex, szName, szValue);
    if (res) {
      if (x->Name != NULL) FreeGlobMem (x->Name);
      if (x->Value != NULL) FreeGlobMem (x->Value);
      x->Name = LPSTR(GetGlobMem (lstrlen(szName) + 1));
      lstrcpy (x->Name,szName);
      x->Value = LPSTR(GetGlobMem (lstrlen(szValue) + 1));
      lstrcpy (x->Value,szValue);
      }
    x = x->Next;
    }

  LPPERSISTSTORAGE lpPS;
  HRESULT          hr;

  hr = m_pIOleObject->QueryInterface (IID_IPersistStorage, (PPVOID)&lpPS);

  if (FAILED(OleSave(lpPS, m_pIStorage, TRUE))) {
    WriteClassStg (m_pIStorage, CLSID_DDSOle);
    lpPS->Save (m_pIStorage, TRUE);
    }

  lpPS->SaveCompleted (NULL);
  lpPS->Release ();

  m_pIStorage->Commit (STGC_OVERWRITE);
  }


//============================================================================
// COleObject::SetDocVar
//
// Zweck: Befuellen einer Dokument Variablen.
//   
// Mit Variables(Index) können Sie ein einzelnes Variable-Objekt zurückgeben. 
// (Index ist der Name der Dokumentvariablen oder die Indexnummer.)    
//
//============================================================================
BOOL COleObject::SetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch == NULL)
    return FALSE;

  VARIANT    vResult;

  VARIANT    av[32];
  DISPID     di[32];
  DISPPARAMS dp;

  dp.rgvarg = av;
  dp.rgdispidNamedArgs = NULL;
  dp.cArgs  = 0;
  dp.cNamedArgs = 0;

  EXCEPINFO excepinfo;

  // holen des IDispatchInterfaces der Variables Enumeration
  //-------------------------------------------------------------------------------
  // LPDISPATCH _Document::GetVariables()
  // {
  // 	LPDISPATCH result;
  // 	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
  // 	return result;
  // }
  //-------------------------------------------------------------------------------
  hr = pIDispatch->Invoke(0x1a, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, &excepinfo, NULL);
  LPDISPATCH pVars = vResult.pdispVal  ;

  pIDispatch->Release();

  if (pVars) {
    long lLen = MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), NULL, NULL);
    av[0].vt       = VT_BSTR;
    av[0].bstrVal  = ::SysAllocStringLen(NULL, lLen);
    MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), av[0].bstrVal, lLen);
    dp.cArgs = 1;
    dp.cNamedArgs = 0;

    // holen des IDispatchInterfaces der DokumentVariablen mit dem Namen "lpstrName"
    //-------------------------------------------------------------------------------
    // LPDISPATCH Variables::Item(VARIANT* Index)
    //   {
    //   LPDISPATCH result;
    //   static BYTE parms[] = VTS_PVARIANT;
    //   InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
    //   return result;
    //   }
    //-------------------------------------------------------------------------------
    hr = pVars->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, &excepinfo, NULL);
    
    ::SysFreeString(av[0].bstrVal);
    LPDISPATCH pVar = vResult.pdispVal  ;

    pVars->Release();

    if (pVar) {
      //-------------------------------------------------------------------
      // Jetzt hab' ich die Adresse der Dokumentvariablen und will sie nun
      // mit einem Wert befuellen.
      //-------------------------------------------------------------------
      // Hier werden "named arguments" verwendet, da die DocVariable ueber
      // einen konkreten Namen angesprochen und gesetzt wird.
      //-------------------------------------------------------------------
      long lLen = MultiByteToWideChar(CP_ACP, 0, lpstrValue, lstrlen(lpstrValue), NULL, NULL);
      av[0].vt       = VT_BSTR;
      av[0].bstrVal  = ::SysAllocStringLen(NULL, lLen);
      MultiByteToWideChar(CP_ACP, 0, lpstrValue, lstrlen(lpstrValue), av[0].bstrVal, lLen);
      di[0] = DISPID_PROPERTYPUT;
      dp.rgdispidNamedArgs = di;
      dp.cArgs = 1;
      dp.cNamedArgs = 1;

      // DokumentVariable mit Wert belegen
      //----------------------------------------------------------------------
      // void Variable::SetValue(LPCTSTR lpszNewValue)
      //   {
      //   static BYTE parms[] = VTS_BSTR;
      //   InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
      //                     lpszNewValue);
      //   }
      //----------------------------------------------------------------------
      hr = pVar->Invoke(0x00, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dp, NULL, NULL, NULL);

      ::SysFreeString(av[0].bstrVal);

      pVar->Release();
      }
    }

  return TRUE;
  }


//============================================================================
// COleObject::RunAutoMacro
//
// Führt ein Auto-Makro aus, das im angegebenen Dokument gespeichert ist.
// Wenn das angegebene Auto-Makro nicht vorhanden ist, passiert nichts.
//
// wdAutoVar ... wdAutoClose, wdAutoExec, wdAutoExit, wdAutoNew, wdAutoOpen
//
//============================================================================
#define  wdAutoClose   3
#define  wdAutoExec    0
#define  wdAutoExit    4
#define  wdAutoNew     1
#define  wdAutoOpen    2


BOOL COleObject::RunAutoMacro (int wdAutoVar)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch == NULL)
    return FALSE;


  VARIANT    av[32];
  DISPPARAMS dp;

  av[0].vt   = VT_I4;
  av[0].lVal = wdAutoVar;
  dp.rgvarg = av;
  dp.rgdispidNamedArgs = NULL;
  dp.cArgs = 1;
  dp.cNamedArgs = 0;

  //-------------------------------------------------------------------------
  //  void _Document::RunAutoMacro(long Which)
  //  {
  //	static BYTE parms[] =
  //		VTS_I4;
  //	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
  //		 Which);
  //  }
  //-------------------------------------------------------------------------
  hr = pIDispatch->Invoke(0x70, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);


  pIDispatch->Release();

  return TRUE;
  }


//============================================================================
// COleObject::SetDocVarEx
//
// Zweck:
//   
//   
//============================================================================
BOOL COleObject::SetDocVarEx (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr;

  IDispatch* pIDispatch;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);
  if (pIDispatch) {
    VARIANT    vResult;

    VARIANT    av[32];
    DISPID     di[32];
    DISPPARAMS dp;

    dp.rgvarg = av;
    dp.rgdispidNamedArgs = NULL;
    dp.cArgs  = 0;
    dp.cNamedArgs = 0;

    // holen des IDispatchInterfaces der Variables Enumeration
    //-------------------------------------------------------------------------------
    // LPDISPATCH _Document::GetVariables()
    // {
    // 	LPDISPATCH result;
    // 	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    // 	return result;
    // }
    //-------------------------------------------------------------------------------
    pIDispatch->Invoke(0x1a, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
    LPDISPATCH pVars = vResult.pdispVal  ;


    if (pVars) {
      long lLen = MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), NULL, NULL);
      av[0].vt       = VT_BSTR;
      av[0].bstrVal  = ::SysAllocStringLen(NULL, lLen);
      MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), av[0].bstrVal, lLen);
      dp.cArgs = 1;
      dp.cNamedArgs = 0;

      // holen des IDispatchInterfaces der DokumentVariablen
      //-------------------------------------------------------------------------------
      // LPDISPATCH Variables::Item(VARIANT* Index)
      //   {
      // 	 LPDISPATCH result;
      // 	 static BYTE parms[] = VTS_PVARIANT;
      // 	 InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
      // 	 return result;
      //   }
      //-------------------------------------------------------------------------------
      hr = pVars->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
       
      ::SysFreeString(av[0].bstrVal);
      LPDISPATCH pVar = vResult.pdispVal  ;

      if (pVar) {
        char* pMark = "\xff";
        LPTSTR lpstrSrc = (LPTSTR)lpstrValue;

        BOOL bHide = FALSE;
        if (!lstrcmp(lpstrValue, "")) {
          lpstrSrc = pMark;
          bHide    = TRUE;
          }

        long lLen = MultiByteToWideChar(CP_ACP, 0, lpstrSrc, lstrlen(lpstrSrc), NULL, NULL);
        av[0].vt       = VT_BSTR;
        av[0].bstrVal  = ::SysAllocStringLen(NULL, lLen);
        MultiByteToWideChar(CP_ACP, 0, lpstrSrc, lstrlen(lpstrSrc), av[0].bstrVal, lLen);
        di[0] = DISPID_PROPERTYPUT;
        dp.rgdispidNamedArgs = di;
        dp.cArgs = 1;
        dp.cNamedArgs = 1;

        // DokumentVariable mit Wert belegen
        //--------------------------------------------------------------------
        // void Variable::SetValue(LPCTSTR lpszNewValue)
        //   {
        // 	 static BYTE parms[] = VTS_BSTR;
        // 	 InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
        //                lpszNewValue);
        //   }
        //--------------------------------------------------------------------
        hr = pVar->Invoke(0x00, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dp, NULL, NULL, NULL);

        ::SysFreeString(av[0].bstrVal);

        // und nun alle Stellen an denen die Variable verwendet wird sichtbar
        // oder unsichtbar machen

        // holen des IDispatchInterfaces der Fields Enumeration
        //--------------------------------------------------------------------
        // LPDISPATCH _Document::GetFields()
        //   {
        // 	 LPDISPATCH result;
        // 	 InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
        // 	 return result;
        //   }
        //--------------------------------------------------------------------
        dp.cArgs  = 0;
        dp.cNamedArgs = 0;
        hr = pIDispatch->Invoke(0x14, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        LPDISPATCH pFields = vResult.pdispVal;

        if (pFields) {
          dp.cArgs = 0;
          dp.cNamedArgs = 0;
          //--------------------------------------------------------------------
          // long Fields::GetCount()
          // {
          // 	long result;
          // 	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
          // 	return result;
          // }
          //--------------------------------------------------------------------
          hr = pFields->Invoke(0x01, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
          long lCount = vResult.lVal;

          for(int iZ = 1; iZ <= lCount; iZ++) {
            av[0].vt   = VT_I4;
            av[0].lVal = iZ;
            dp.cArgs = 1;
            dp.cNamedArgs = 0;
            //--------------------------------------------------------------------
            // LPDISPATCH Fields::Item(long Index)
            //   {
            // 	 LPDISPATCH result;
            // 	 static BYTE parms[] = VTS_I4;
            // 	 InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
            //                Index);
            //   return result;
            //   }
            //--------------------------------------------------------------------
            hr = pFields->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
            LPDISPATCH pField = vResult.pdispVal;

            if (pField) {
              // holen des FieldCode's => Range-Object
              dp.cArgs = 0;
              dp.cNamedArgs = 0;
              //--------------------------------------------------------------------
              // LPDISPATCH Field::GetCode()
              // {
              // 	LPDISPATCH result;
              // 	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
              // 	return result;
              // }
              //--------------------------------------------------------------------
              hr = pField->Invoke(0x00, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
              LPDISPATCH pRange = vResult.pdispVal;
              if (pRange) {
                char acTmp[256];

                // holen des Textes
                //-------------------------------------------------------------------------
                // CString Range::GetText()
                // {
	              //   CString result;
	              //   InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	              //   return result;
                // }
                //-------------------------------------------------------------------------
                hr = pRange->Invoke(0x00, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
                long lLen = WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, NULL, 0, NULL, NULL);
                WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, acTmp, lLen, NULL, NULL);
                ::SysFreeString(vResult.bstrVal);

                _strupr((LPTSTR)lpstrName);
                _strupr(acTmp);

                int iCount = 0;
                char* lpstrSep =  "\"";
                char* lpstrToken = strtok(acTmp, lpstrSep);
                while(NULL != lpstrToken) {
   //                        TRACE("%s\n", lpstrToken);

                  iCount++;

                  // Der Variablenname kommt immer an 2.Stelle
                  if (2 == iCount) {
                    // wenn die Variable verwendet wurde, dann ...
                    if (!lstrcmp(lpstrToken, lpstrName)) {
                      dp.cArgs = 0;
                      dp.cNamedArgs = 0;
                      //-----------------------------------------------------------------------------
                      // holen des Results
                      // LPDISPATCH Field::GetResult()
                      // {
                      // 	LPDISPATCH result;
                      // 	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
                      // 	return result;
                      // }
                      //-----------------------------------------------------------------------------
                      hr = pField->Invoke(0x04, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
                      LPDISPATCH pResult = vResult.pdispVal;

                      if (pResult) {
                        // löschen des Results
                        hr = pResult->Invoke(0x7f, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);

                        // updaten des Feldes
                        //---------------------------------------------------------------------
                        // BOOL Field::Update()
                        // {
                        // 	BOOL result;
                        // 	InvokeHelper(0x65, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
                        // 	return result;
                        // }
                        //---------------------------------------------------------------------
                        hr = pField->Invoke(0x65, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);

                        pResult->Release();
                        // erneutes holen des Results
                        //------------------------------------------------------------------------------
                        // LPDISPATCH Field::GetResult()
                        // {
                        // 	LPDISPATCH result;
                        // 	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
                        // 	return result;
                        // }
                        //------------------------------------------------------------------------------
                        hr = pField->Invoke(0x04, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
                        pResult = vResult.pdispVal;
                        }
                      
                      if (pResult) {
                        dp.cArgs = 0;
                        dp.cNamedArgs = 0;
                        // holen des Fonts
                        //----------------------------------------------------------------------------
                        // LPDISPATCH Range::GetFont()
                        // {
	                      //   LPDISPATCH result;
	                      //   InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	                      //   return result;
                        // }
                        //----------------------------------------------------------------------------
                        hr = pResult->Invoke(0x05, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
                        LPDISPATCH pFont = vResult.pdispVal;

                        // ... werden die Font-Attribute angepaßt
                        if (pFont) {
                          av[0].vt   = VT_I4;
                          av[0].lVal = bHide;
                          dp.cArgs = 1;
                          dp.cNamedArgs = 0;
                          // versorgen des Hidden-Attributes
                          //------------------------------------------------------------------
                          // void _Font::SetHidden(long nNewValue)
                          // {
                          // 	static BYTE parms[] =
                          // 		VTS_I4;
                          // 	InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                          // 		 nNewValue);
                          // }
                          //------------------------------------------------------------------
                          hr = pFont->Invoke(0x84, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dp, NULL, NULL, NULL);

                          pFont->Release();
                          }

                        pResult->Release();
                        }
                      }
                    break;
                    }

                  lpstrToken = strtok(NULL, lpstrSep);
                  }

                pRange->Release();
                }

              pField->Release();
              }
            }
          pFields->Release();
          }
        pVar->Release();
        }
      pVars->Release();
      }
    pIDispatch->Release();
    }

  return TRUE;
  }



//============================================================================
// COleObject::GetDocVar
//
// Zweck:
//   
//   
//============================================================================
BOOL COleObject::GetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch == NULL)
    return FALSE;

  VARIANT    vResult;

  VARIANT    av[32];
//  DISPID     di[32];
  DISPPARAMS dp;

  dp.rgvarg = av;
  dp.rgdispidNamedArgs = NULL;
  dp.cArgs  = 0;
  dp.cNamedArgs = 0;

  EXCEPINFO excepinfo;

  // holen des IDispatchInterfaces der Variables Enumeration
  //-------------------------------------------------------------------------------
  // LPDISPATCH _Document::GetVariables()
  // {
  // 	LPDISPATCH result;
  // 	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
  // 	return result;
  // }
  //-------------------------------------------------------------------------------
  hr = pIDispatch->Invoke(0x1a, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, &excepinfo, NULL);
  LPDISPATCH pVars = vResult.pdispVal  ;

  pIDispatch->Release();

  if (pVars) {
    long lLen = MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), NULL, NULL);
    av[0].vt       = VT_BSTR;
    av[0].bstrVal  = ::SysAllocStringLen(NULL, lLen);
    MultiByteToWideChar(CP_ACP, 0, lpstrName, lstrlen(lpstrName), av[0].bstrVal, lLen);
    dp.cArgs = 1;
    dp.cNamedArgs = 0;

    // holen des IDispatchInterfaces der Dokumentvariable
    hr = pVars->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, &excepinfo, NULL);
    
    ::SysFreeString(av[0].bstrVal);
    LPDISPATCH pVar = vResult.pdispVal  ;

    pVars->Release();

    if (pVar) {
      dp.rgvarg            = NULL;
      dp.rgdispidNamedArgs = NULL;
      dp.cArgs             = 0;
      dp.cNamedArgs        = 0;

      // holen des Wertes der DokumentVariablen
      hr = pVar->Invoke(0x00, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, &excepinfo, NULL);

      long lLen = WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, NULL, 0, NULL, NULL);
      WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, (LPSTR)lpstrValue, lLen, NULL, NULL);
      ::SysFreeString(vResult.bstrVal);

      pVar->Release();
      }
    }

  return TRUE;
  }



//============================================================================
// COleObject::PrintDoc
//
// Zweck:
//   
//   
//============================================================================
#define wdDialogFilePrint 88


BOOL COleObject::PrintDoc (BOOL bSelectPrinter)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  BOOL bResult = FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (SUCCEEDED(hr)) {
    VARIANT    vResult;

    VARIANT    av[32];
    DISPPARAMS dp;

    if (bSelectPrinter) {

      dp.rgvarg = av;
      dp.rgdispidNamedArgs = NULL;
      dp.cArgs  = 0;
      dp.cNamedArgs = 0;

      // get Application Object
      //------------------------------------------------------------------------------
      // LPDISPATCH _Document::GetApplication()
      // {
      // 	LPDISPATCH result;
      // 	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
      // 	return result;
      // }
      //------------------------------------------------------------------------------
      hr = pIDispatch->Invoke(0x01, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
      LPDISPATCH pApp = vResult.pdispVal;

      if (pApp) {
        // get Dialogs Object
        //-------------------------------------------------------------------------------
        // LPDISPATCH _Application::GetDialogs()
        // {
        // 	LPDISPATCH result;
        // 	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
        // 	return result;
        // }
        //-------------------------------------------------------------------------------
        hr = pApp->Invoke(0x13, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        LPDISPATCH pDlgs = vResult.pdispVal;

        if (pDlgs) {
          av[0].vt = VT_I4;
          av[0].lVal = wdDialogFilePrint;
          dp.cArgs = 1;
          // get Dialog Object
          //-------------------------------------------------------------------------
          // LPDISPATCH Dialogs::Item(long Index)
          // {
          // 	LPDISPATCH result;
          // 	static BYTE parms[] =
          // 		VTS_I4;
          // 	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
          // 		Index);
          // 	return result;
          // }
          //-------------------------------------------------------------------------
          hr = pDlgs->Invoke(0x0, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
          LPDISPATCH pDlg = vResult.pdispVal;

          if (pDlg) {
            av[0].vt = VT_I4;
            av[0].lVal = 0L;
            dp.cArgs = 1;
            // Invoke Show Method   Dialog::Show
            //-----------------------------------------------------------------------
            // long Dialog::Show(VARIANT* TimeOut)
            // {
	          //   long result;
	          //   static BYTE parms[] =
		        //     VTS_PVARIANT;
	          //   InvokeHelper(0x150, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		        //     TimeOut);
	          //   return result;
            // }
            //-----------------------------------------------------------------------

            hr = pDlg->Invoke(0x0150, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
            if (vResult.iVal == -1)
              bResult = TRUE;
            pDlg->Release();
            }

          pDlgs->Release();
          }

        pApp->Release();
        }
      }
    else {
      //-----------------------------------------------------------------------
      // void _Document::PrintOut(
      //                     VARIANT* Background, 
      //                     VARIANT* Append, 
      //                     VARIANT* Range, 
      //                     VARIANT* OutputFileName, 
      //                     VARIANT* From, 
      //                     VARIANT* To, 
      //                     VARIANT* Item, 
      //                     VARIANT* Copies, 
      //                     VARIANT* Pages, 
      //                     VARIANT* PageType, 
      //                     VARIANT* PrintToFile, 
      //                     VARIANT* Collate, 
      //                     VARIANT* ActivePrinterMacGX, 
      //                     VARIANT* ManualDuplexPrint)
      // {
      // 	static BYTE parms[] =
      // 		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT
      //    VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT 
      //    VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
      // 	InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
      // 		           Background, Append, Range, OutputFileName, From, To, 
      //               Item, Copies, Pages, PageType, PrintToFile, Collate, 
      //               ActivePrinterMacGX, ManualDuplexPrint);
      // }
      //-----------------------------------------------------------------------
      dp.rgvarg = NULL;
      dp.rgdispidNamedArgs = NULL;
      dp.cArgs  = 0;
      dp.cNamedArgs = 0;

      // Methode PrintOut über IDispatchInterfaces des Dokuments aufrufen
      pIDispatch->Invoke(0x6d, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);
      bResult = TRUE;

      }
    pIDispatch->Release();
    }
  return bResult;
  }



//============================================================================
// COleObject::GetMyIUnknown
//
// Zweck:
//   
//   
//============================================================================
BOOL COleObject::GetMyIUnknown (LPUNKNOWN FAR *MyObj)
  {
  HRESULT hr = m_pIOleObject->QueryInterface(IID_IUnknown, (PPVOID)MyObj);

  if (FAILED(hr))
    return FALSE;
  else
    return TRUE;
  }




/////////////////////////////////////////////////////////////////////////////
// COleDateTime class HELPER definitions

// Verifies will fail if the needed buffer size is too large
#define MAX_TIME_BUFFER_SIZE    128         // matches that in timecore.cpp
#define MIN_DATE                (-657434L)  // about year 100
#define MAX_DATE                2958465L    // about year 9999

// Half a second, expressed in days
#define HALF_SECOND  (1.0/172800.0)

// One-based array of days in year at month start
static int rgMonthDays[13] =
  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

BOOL _TmFromOleDate(DATE dtSrc, struct tm& tmDest)
  {
  // The legal range does not actually span year 0 to 9999.
  if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
    return FALSE;

  long nDays;             // Number of days since Dec. 30, 1899
  long nDaysAbsolute;     // Number of days since 1/1/0
  long nSecsInDay;        // Time in seconds since midnight
  long nMinutesInDay;     // Minutes in day

  long n400Years;         // Number of 400 year increments since 1/1/0
  long n400Century;       // Century within 400 year block (0,1,2 or 3)
  long n4Years;           // Number of 4 year increments since 1/1/0
  long n4Day;             // Day within 4 year block
              //  (0 is 1/1/yr1, 1460 is 12/31/yr4)
  long n4Yr;              // Year within 4 year block (0,1,2 or 3)
  BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

  double dblDate = dtSrc; // tempory serial date

  // If a valid date, then this conversion should not overflow
  nDays = (long)dblDate;

  // Round to the second
  dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

  nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

  dblDate = fabs(dblDate);
  nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

  // Calculate the day of week (sun=1, mon=2...)
  //   -1 because 1/1/0 is Sat.  +1 because we want 1-based
  tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

  // Leap years every 4 yrs except centuries not multiples of 400.
  n400Years = (long)(nDaysAbsolute / 146097L);

  // Set nDaysAbsolute to day within 400-year block
  nDaysAbsolute %= 146097L;

  // -1 because first century has extra day
  n400Century = (long)((nDaysAbsolute - 1) / 36524L);

  // Non-leap century
  if (n400Century != 0)
  {
    // Set nDaysAbsolute to day within century
    nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

    // +1 because 1st 4 year increment has 1460 days
    n4Years = (long)((nDaysAbsolute + 1) / 1461L);

    if (n4Years != 0)
      n4Day = (long)((nDaysAbsolute + 1) % 1461L);
    else
    {
      bLeap4 = FALSE;
      n4Day = (long)nDaysAbsolute;
    }
  }
  else
  {
    // Leap century - not special case!
    n4Years = (long)(nDaysAbsolute / 1461L);
    n4Day = (long)(nDaysAbsolute % 1461L);
  }

  if (bLeap4)
  {
    // -1 because first year has 366 days
    n4Yr = (n4Day - 1) / 365;

    if (n4Yr != 0)
      n4Day = (n4Day - 1) % 365;
  }
  else
  {
    n4Yr = n4Day / 365;
    n4Day %= 365;
  }

  // n4Day is now 0-based day of year. Save 1-based day of year, year number
  tmDest.tm_yday = (int)n4Day + 1;
  tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

  // Handle leap year: before, on, and after Feb. 29.
  if (n4Yr == 0 && bLeap4)
  {
    // Leap Year
    if (n4Day == 59)
    {
      /* Feb. 29 */
      tmDest.tm_mon = 2;
      tmDest.tm_mday = 29;
      goto DoTime;
    }

    // Pretend it's not a leap year for month/day comp.
    if (n4Day >= 60)
      --n4Day;
  }

  // Make n4DaY a 1-based day of non-leap year and compute
  //  month/day for everything but Feb. 29.
  ++n4Day;

  // Month number always >= n/32, so save some loop time */
  for (tmDest.tm_mon = (n4Day >> 5) + 1;
    n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

  tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
  if (nSecsInDay == 0)
    tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
  else
  {
    tmDest.tm_sec = (int)nSecsInDay % 60L;
    nMinutesInDay = nSecsInDay / 60L;
    tmDest.tm_min = (int)nMinutesInDay % 60;
    tmDest.tm_hour = (int)nMinutesInDay / 60;
  }

  return TRUE;
}

void _TmConvertToStandardFormat(struct tm& tmSrc)
{
  // Convert afx internal tm to format expected by runtimes (_tcsftime, etc)
  tmSrc.tm_year -= 1900;  // year is based on 1900
  tmSrc.tm_mon -= 1;      // month of year is 0-based
  tmSrc.tm_wday -= 1;     // day of week is 0-based
  tmSrc.tm_yday -= 1;     // day of year is 0-based
}



//============================================================================
// COleObject::GetOLEDocProp
//
// Zweck:
//   
//   
//============================================================================
BOOL COleObject::GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  BOOL bResult = FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch) {
    VARIANT    vResult;

    VARIANT    av[32];
//    DISPID     di[32];
    DISPPARAMS dp;

    dp.rgvarg     = av;
    dp.rgdispidNamedArgs = NULL;
    dp.cArgs      = 0;
    dp.cNamedArgs = 0;

    LPDISPATCH pVars = NULL;
    switch (iKind) {
      case 0:
        //---------------------------------------------------------------------------------
        // LPDISPATCH _Document::GetBuiltInDocumentProperties()
        // {
	      //   LPDISPATCH result;
	      //   InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	      //   return result;
        // }
        //---------------------------------------------------------------------------------
        pIDispatch->Invoke(0x03e8, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        pVars = vResult.pdispVal;
        break;
      case 1:
        //---------------------------------------------------------------------------------
        // LPDISPATCH _Document::GetCustomDocumentProperties()
        // {
        // 	LPDISPATCH result;
        // 	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
        // 	return result;
        // }
        //---------------------------------------------------------------------------------
        pIDispatch->Invoke(0x0002, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        pVars = vResult.pdispVal;
        break;
      default:
        pVars = NULL;
        break;
      }

    if (pVars) {
      pIDispatch->Release();

      dp.rgvarg = av;
      dp.rgdispidNamedArgs = NULL;

      av[0].vt      = VT_I4;
      av[0].lVal    = iIndex;
      dp.cArgs      = 1;
      dp.cNamedArgs = 0;

      // holen des IDispatchInterfaces der Dokumenteigenschaft
      //--------------------------------------------------------------------------
      // LPDISPATCH Variables::Item(VARIANT* Index)
      // {
      // 	LPDISPATCH result;
      // 	static BYTE parms[] = VTS_PVARIANT;
      // 	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      // 		Index);
      // 	return result;
      // }
      //--------------------------------------------------------------------------
      hr = pVars->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD | DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);

      pVars->Release();
      
      LPDISPATCH pVar = vResult.pdispVal;

      if (pVar) {
        long lLen;
        dp.cArgs      = 0;
        dp.cNamedArgs = 0;

        // Ermitteln des Namens
        hr = pVar->Invoke(0x03, IID_NULL, 0, DISPATCH_METHOD | DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        lLen = WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, NULL, 0, NULL, NULL);
        WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, lpszName, lLen, NULL, NULL);
        ::SysFreeString(vResult.bstrVal);

        // Ermitteln des Wertes
         hr = pVar->Invoke(0x00, IID_NULL, 0, DISPATCH_METHOD | DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
        switch(vResult.vt) {
          case VT_BSTR:
            lLen = WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, NULL, 0, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, vResult.bstrVal, -1, lpszValue, lLen, NULL, NULL);
            ::SysFreeString(vResult.bstrVal);
            break;

          case VT_DATE: {
               OLECHAR acTmp[64];
              struct tm tmDest;
              _TmFromOleDate(vResult.date, tmDest);
              _TmConvertToStandardFormat(tmDest);
              wcsftime(acTmp, 32, (OLECHAR *)L"%d.%m.%Y %H:%M:%S", &tmDest);
               lLen = WideCharToMultiByte(CP_ACP, 0, acTmp, -1, NULL, 0, NULL, NULL);
               WideCharToMultiByte(CP_ACP, 0, acTmp, -1, lpszValue, lLen, NULL, NULL);
            }
            break;

          case VT_I2:
            wsprintf(lpszValue, "%d", vResult.iVal);
            break;

          case VT_I4:
            wsprintf(lpszValue, "%ld", vResult.lVal);
            break;

          default:
            wsprintf(lpszValue, "");
            break;
          }
        pVar->Release();
        bResult = TRUE;
        }
      }
    }
  return bResult;
  }



//============================================================================
// COleObject::RestrictInput
//
// Zweck:
//   
//   
//============================================================================
#define  wdNoProtection  0

BOOL COleObject::RestrictInput(int iLevel, LPTSTR lpszPassword)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch) {

    VARIANT    av[32];
    DISPPARAMS dp;

    OLECHAR acPassword[256];

    MultiByteToWideChar(CP_ACP, 0, lpszPassword, -1, acPassword, sizeof(acPassword));

    if (wdNoProtection == iLevel) {
      av[0].vt      = VT_BSTR;
      av[0].bstrVal = ::SysAllocString(acPassword);
      dp.rgvarg     = av;
      dp.rgdispidNamedArgs = NULL;
      dp.cArgs      = 1;
      dp.cNamedArgs = 0;

      // unprotect
      //--------------------------------------------------------------
      // void _Document::Unprotect(VARIANT* Password)
      //   {
      // 	 static BYTE parms[] = VTS_PVARIANT;
      // 	 InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
      //                Password);
      //   }
      //--------------------------------------------------------------
      hr = pIDispatch->Invoke(0x79, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);

      ::SysFreeString(av[0].bstrVal);
      }
    else {
      av[30].vt = VT_BOOL;
      av[30].boolVal = TRUE;
      av[31].vt = VT_BSTR;
      av[31].bstrVal = ::SysAllocString(acPassword);

      // DANGER: reverse order of arguments !!!!!!!
      av[0].vt      = VT_VARIANT | VT_BYREF;
      av[0].pvarVal = &av[31];
      av[1].vt      = VT_VARIANT | VT_BYREF;
      av[1].pvarVal = &av[30];
      av[2].vt      = VT_I4;
      av[2].lVal    = iLevel;
      dp.rgvarg     = av;
      dp.rgdispidNamedArgs = NULL;
      dp.cArgs      = 3;
      dp.cNamedArgs = 0;

      // protect
      //-------------------------------------------------------------------------
      // void _Document::Protect(long Type, VARIANT* NoReset, VARIANT* Password)
      // {
      // 	static BYTE parms[] =
      // 		VTS_I4 VTS_PVARIANT VTS_PVARIANT;
      // 	InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
      // 		 Type, NoReset, Password);
      // }
      //-------------------------------------------------------------------------
      hr = pIDispatch->Invoke(0x78, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);

      ::SysFreeString(av[31].bstrVal);
      }
      pIDispatch->Release();
    }

  return TRUE;
  }


//============================================================================
// COleObject::UpdateFields
//
// Zweck:
//   
//   
//============================================================================
BOOL COleObject::UpdateFields()
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (pIDispatch) {
    LPDISPATCH pRange = NULL;

    VARIANT    vResult;

    VARIANT    av[32];
    DISPPARAMS dp;

    dp.rgvarg     = av;
    dp.rgdispidNamedArgs = NULL;
    dp.cArgs      = 0;
    dp.cNamedArgs = 0;

    // holen des RangeObjects
    //----------------------------------------------------------------------------
    // LPDISPATCH _Document::Range(VARIANT* Start, VARIANT* End)
    // {
    // 	LPDISPATCH result;
    // 	static BYTE parms[] =
    // 		VTS_PVARIANT VTS_PVARIANT;
    // 	InvokeHelper(0x7d0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
    // 		Start, End);
    // 	return result;
    // }
    //----------------------------------------------------------------------------
    hr = pIDispatch->Invoke(0x07d0, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
    pRange = vResult.pdispVal;

    if (pRange) {
      LPDISPATCH pFields = NULL;

      // holen des FieldsObjects
      //------------------------------------------------------------------------------
      // LPDISPATCH Range::GetFields()
      // {
      // 	LPDISPATCH result;
      // 	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
      // 	return result;
      // }
      //------------------------------------------------------------------------------
      hr = pRange->Invoke(0x40, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
      pFields = vResult.pdispVal;

      if (pFields) {
        // aufrufen der UpdateMethode
        //------------------------------------------------------------------------------
        // long Fields::Update()
        // {
        //   long result;
        //   InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
        //   return result;
        // }
        //------------------------------------------------------------------------------
        hr = pFields->Invoke(0x65, IID_NULL, 0, DISPATCH_METHOD, &dp, &vResult, NULL, NULL);
        // iError > 0 => iError = FieldIndex 
        int iError = vResult.lVal;
        pFields->Release();
        }
      pRange->Release();
      }

    pIDispatch->Release();
    }

  return TRUE;
  }


//============================================================================
// COleObject::CloseApplicationWord
//
// Zweck:  Beendet Word und speichert die geöffneten Dokumente oder leitet 
//         sie weiter (optional).
//
// Parameter:
//
//         SaveChanges   Variant optional. Legt fest, ob geänderte Dokumente 
//                       vor dem Beenden von Word gespeichert werden. Dies 
//                       kann eine der folgenden WdSaveOptions-Konstanten sein:
//                       wdDoNotSaveChanges, wdPromptToSaveChanges, wdSaveChanges.
//
//         OriginalFormat   Variant optional. 
//                       Legt fest, wie Word Dokumente speichert, deren 
//                       ursprüngliches Format kein Word-Dokumentformat war. 
//                       Dies kann eine der folgenden WdOriginalFormat-Konstanten 
//                       sein: 
//                       wdOriginalDocumentFormat, wdPromptUser, wdWordDocument.
//
//         RouteDocument Variant optional. TRUE, um das Dokument an den nächsten 
//                       Empfänger weiterzuleiten. Ist dem Dokument kein Verteiler 
//                       zugeordnet, wird dieses Argument ignoriert.
// 
//============================================================================
#define  wdDoNotSaveChanges      0
#define  wdPromptToSaveChanges  -2
#define  wdSaveChanges          -1


BOOL COleObject::CloseApplicationWord (int iSaveChanges)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  BOOL bResult = FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (SUCCEEDED(hr)) {
    VARIANT    vResult;

    VARIANT    av[32];
    DISPPARAMS dp;

    dp.rgvarg = av;
    dp.rgdispidNamedArgs = NULL;
    dp.cArgs  = 0;
    dp.cNamedArgs = 0;

    // get Application Object (in diesem Fall WORD)
    //------------------------------------------------------------------------------
    // LPDISPATCH _Document::GetApplication()
    //   {
    // 	 LPDISPATCH result;
    // 	 InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    // 	 return result;
    //   }
    //------------------------------------------------------------------------------
    hr = pIDispatch->Invoke(0x01, IID_NULL, 0, DISPATCH_PROPERTYGET, &dp, &vResult, NULL, NULL);
    LPDISPATCH pApp = vResult.pdispVal;

    if (pApp) {
      dp.rgvarg = av;
      dp.rgdispidNamedArgs = NULL;

      // mich interessiert nur die SaveChanges Variable.
      av[0].vt      = VT_I4;
      av[0].lVal    = iSaveChanges;
      dp.cArgs      = 1;
      dp.cNamedArgs = 0;
      //-------------------------------------------------------------------------------
      // void _Application::Quit(VARIANT* SaveChanges, VARIANT* OriginalFormat, 
      //                         VARIANT* RouteDocument)
      //   {
	    //   static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	    //   InvokeHelper(0x451, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		  //                SaveChanges, OriginalFormat, RouteDocument);
      //   }
      //-------------------------------------------------------------------------------
      hr = pApp->Invoke(0x451, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);
      pApp->Release();
      }

    pIDispatch->Release();
    }
  return TRUE ;
  }


//============================================================================
// COleObject::SaveWordObjectAs
//
// Zweck: Speichert das angegebene Dokument unter einem neuen Namen oder in
//        einem neuen Format. Die Argumente für diese Methode entsprechen den
//        Optionen im Dialogfeld "Speichern unter" (Menü Datei).
//
// Parameter:
//        FileName   Variant optional. Der Name für das Dokument.
//                   Als Standard gilt der Name des aktuellen Ordners und der
//                   aktuellen Datei. Wenn das Dokument noch nicht gespeichert
//                   wurde, wird der Standardname verwendet (z. B. "Dok1.doc").
//                   Wenn bereits ein Dokument mit dem angegebenen FileName
//                   vorhanden ist, wird das Dokument überschrieben, wobei 
//                   vorher keine Eingabeaufforderung für den Benutzer 
//                   angezeigt wird.
//
//     eFileFormat   Variant optional. Das Format, in dem das Dokument
//                   gespeichert wird. Kann eine der folgenden WdSaveFormat-
//                   Konstanten sein: wdFormatDocument, wdFormatDOSText, 
//                   wdFormatDOSTextLineBreaks, wdFormatEncodedText, 
//                   wdFormatHTML, wdFormatRTF, wdFormatTemplate, wdFormatText, 
//                   wdFormatTextLineBreaks oder wdFormatUnicodeText. 
//                   Um ein Dokument in einem anderen Format zu speichern, 
//                   geben Sie den entsprechenden Wert für die SaveFormat-
//                   Eigenschaft des FileConverter-Objekts an.
//
//============================================================================
#define  wdFormatDocument             0
#define  wdFormatDOSText              4
#define  wdFormatDOSTextLineBreaks    5
#define  wdFormatEncodedText          7
#define  wdFormatHTML                 8
#define  wdFormatRTF                  6
#define  wdFormatTemplate             1
#define  wdFormatText                 2
#define  wdFormatTextLineBreaks       3
#define  wdFormatUnicodeText          7


BOOL COleObject::SaveWordObjectAs (LPTSTR lpszFileName, int iFileFormat)
  {
  if (m_pIOleObject == NULL)
    return FALSE;

  BOOL bResult = FALSE;

  HRESULT hr = NULL;

  IDispatch* pIDispatch = NULL;
  hr = m_pIOleObject->QueryInterface(IID_IDispatch, (void **)&pIDispatch);

  if (SUCCEEDED(hr)) {

    VARIANT    av[32];
    DISPPARAMS dp;

    OLECHAR acFileName[256];

    MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, acFileName, sizeof(acFileName));

    //-------------------------------------------------- 
    // Achtung!!! Die Argumente sind in "reverse order"
    //--------------------------------------------------
    av[0].vt      = VT_I4;
    av[0].lVal    = iFileFormat;
    av[1].vt      = VT_BSTR;
    av[1].bstrVal = ::SysAllocString(acFileName);
    dp.rgvarg     = av;
    dp.rgdispidNamedArgs = NULL;
    dp.cArgs      = 2;
    dp.cNamedArgs = 0;
    
    //--------------------------------------------------------------------------------------
    // void _Document::SaveAs(VARIANT* FileName, VARIANT* FileFormat, VARIANT* LockComments, 
    //                        VARIANT* Password, VARIANT* AddToRecentFiles, 
    //                        VARIANT* WritePassword, VARIANT* ReadOnlyRecommended, 
    //                        VARIANT* EmbedTrueTypeFonts, VARIANT* SaveNativePictureFormat, 
    // 		                    VARIANT* SaveFormsData, VARIANT* SaveAsAOCELetter)
    //   {
    //   static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT 
    //                         VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT 
    //                         VTS_PVARIANT;
    //   InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
    //                  FileName, FileFormat, LockComments, Password, AddToRecentFiles, 
    //                  WritePassword, ReadOnlyRecommended, EmbedTrueTypeFonts, 
    //                  SaveNativePictureFormat, SaveFormsData, SaveAsAOCELetter);
    //   }
    //--------------------------------------------------------------------------------------
    hr = pIDispatch->Invoke(0x66, IID_NULL, 0, DISPATCH_METHOD, &dp, NULL, NULL, NULL);

    ::SysFreeString(av[1].bstrVal);

    pIDispatch->Release();
    }

  return TRUE ;
  }




//============================================================================
//
//  Standardmethoden eines jeden Interfaces
//
//============================================================================
STDMETHODIMP COleObject::QueryInterface(REFIID riid, PPVOID ppv)
  {
  *ppv=NULL;

  if (IID_IUnknown==riid)
    *ppv=this;

  if (IID_IOleClientSite==riid)
    *ppv=m_pIOleClientSite;

  if (IID_IAdviseSink2==riid || IID_IAdviseSink==riid)
    *ppv=m_pIAdviseSink;

  if (NULL!=*ppv)
    {
    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }

  return ResultFromScode(E_NOINTERFACE);
  }



//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) COleObject::AddRef(void)
  {
  return ++m_cRef;
  }

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) COleObject::Release(void)
  {
  ULONG           cRefT;

  cRefT=--m_cRef;

  if (0L==m_cRef)
    delete this;

  return cRefT;
  }


void COleObject::Notify (DWORD NotifyMsg)
  {
  if (NotifyMsg == WMU_OLESERVER_HAS_CLOSED)
    PostMessage (m_hWnd, NotifyMsg, 0, 0);
  }



