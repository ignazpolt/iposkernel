//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/include/rev/olemain.hpv   1.8   22 Nov 1999 09:27:52   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/olemain.hpv  $
// 
//    Rev 1.8   22 Nov 1999 09:27:52   Hannes
// OLE - Erweiterungen
// 
//    Rev 1.7   14 Jun 1999 20:39:46   Hannes
// RunAutomacro
// 
//    Rev 1.6   15 Jan 1999 18:20:52   Hannes
// Propertie - Handling
// 
//    Rev 1.5   15 Aug 1998 16:00:40   Gerhold
// SetOleDocVarEx
// 
//    Rev 1.4   03 Aug 1998 18:05:12   Gerhold
// GetMyIUnknwon war noch falsch
// 
//    Rev 1.3   31 Jul 1998 11:42:50   Gerhold
// _export SetOLEHostNames
// 
//    Rev 1.2   29 Jul 1998 12:04:56   Gerhold
// OLEGetDocProp, OLERestrictInput, OLEUpdateFields
// 
//    Rev 1.1   28 Jul 1998 08:23:46   Gerhold
// SetDocVar
// 
//    Rev 1.0   22 Aug 1997 13:50:22   Gerhold
// Initial revision.
//--------------------------------------------------------------------------
#define DOCERR_NONE                     0
#define DOCERR_NOFILE                   1
#define DOCERR_COULDNOTOPEN             2
#define DOCERR_READFAILURE              3
#define DOCERR_UNSUPPORTEDVERSION       4
#define DOCERR_WRITEFAILURE             5
#define DOCERR_CANCELLED                6
#define DOCERR_STDMAX                   7
#define DOCERR_COULDNOTCREATELOCKBYTES  8
#define DOCERR_COULDNOTCREATESTORAGE    9
#define DOCERR_NOTVALIDLOCKBYTES       10
#define DOCERR_COULDNOTOPENSTORAGE     11


DLLExport void _export SetOLEHostName (LPTSTR lpszHostName);


DEFINE_GUID(CLSID_DDSOle, 0x9cfedb20, 0x01a3, 0x11d1, 0x9b, 0xa5, 
                          0, 0xa0, 0x24, 0x5f, 0x10, 0x99);



class FAR CDocument
 {
 private:
  LPSTORAGE    m_pIStorage;
  LPLOCKBYTES  m_pLockBytes;
  LPCOLEOBJECT m_pOleObj;
  HWND         m_hWnd;

 public:
  CDocument (HWND hWnd);
  ~CDocument (void); 

  BOOL    Init  (void);
  void    Close (void);
  BOOL    Save  (LPTSTR pszFile);
  UINT    ULoad (LPTSTR pszFile, HGLOBAL hGlobal = NULL,BOOL doActivate = FALSE);
  HGLOBAL GetHGlobalFromLockBytes (DWORD FAR *dwBytes);
  BOOL    SetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL    RunAutoMacro (int wdAutoVar);
  BOOL    SetDocVarEx (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL    GetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL    PrintDoc (BOOL bSelectPrinter);
  BOOL    GetMyIUnknown (LPUNKNOWN FAR *MyObj);
  BOOL    GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue);
  BOOL    RestrictInput(int iLevel, LPTSTR lpszPassword);
  BOOL    UpdateFields ();
  BOOL    CloseApplicationWord (int iSaveChanges);
  BOOL    SaveWordObjectAs (LPTSTR lpszFileName, int iFormat);

  void AddProp (int i,int iKind,int iValue)
    {
    m_pOleObj->AddProp (i,iKind,iValue);
    }

  PropList FAR *GetProp ()
    {
    return m_pOleObj->GetProp ();
    }
 };

typedef CDocument *POLEDOCUMENT;



class FAR COleFrame
 {
 protected:
  PIMPIADVISESINK      m_pAdv;
  POLEDOCUMENT         m_pDoc;
  LPSTORAGE            m_pIStorage;
  HWND                 m_hWnd;

 public:
  DLLExport _export COleFrame (HWND hWnd);
  DLLExport _export ~COleFrame (void);

            BOOL            Init ();
  DLLExport BOOL    _export SaveCompoundFile (LPTSTR pszFile);
  DLLExport BOOL    _export LoadCompoundFile (LPTSTR pszFile);
  DLLExport BOOL    _export CreateObjFromFile (LPTSTR pszFile);
  DLLExport UINT    _export CreateObjFromHGlobal (HGLOBAL hGlobal,BOOL doActivate);
  DLLExport HGLOBAL _export GetHGlobalFromOLEObj (DWORD FAR *lpsize);
  DLLExport BOOL    _export SetDocVar (LPTSTR lpstrName, LPTSTR lpstrValue);
  DLLExport BOOL    _export RunAutoMacro (int wdAutoVar);
  DLLExport BOOL    _export SetDocVarEx (LPTSTR lpstrName, LPTSTR lpstrValue);
  DLLExport BOOL    _export GetDocVar (LPTSTR lpstrName, LPTSTR lpstrValue);
  DLLExport BOOL    _export PrintDoc (BOOL bSelectPrinter);
  DLLExport BOOL    _export GetMyIUnknown (LPUNKNOWN FAR *MyObj);
  DLLExport BOOL    _export GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue);
  DLLExport BOOL    _export RestrictInput(int iLevel, LPTSTR lpszPassword);
  DLLExport BOOL    _export UpdateFields ();
  DLLExport BOOL    _export CloseApplicationWord (int iSaveChanges);
  DLLExport BOOL    _export SaveWordObjectAs (LPTSTR lpszFileName, int iFormat);

  void AddProp (int i,int iKind,int iValue)
    {
    m_pDoc->AddProp (i,iKind,iValue);
    }

  PropList FAR *GetProp ()
    {
    return m_pDoc->GetProp ();
    }
 };

typedef COleFrame* LPCOLEFRAME;




