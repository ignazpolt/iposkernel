//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/include/rev/iclisite.hpv   1.7   22 Nov 1999 09:27:52   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/iclisite.hpv  $
// 
//    Rev 1.7   22 Nov 1999 09:27:52   Hannes
// OLE - Erweiterungen
// 
//    Rev 1.6   14 Jun 1999 20:39:48   Hannes
// RunAutomacro
// 
//    Rev 1.5   15 Jan 1999 18:20:50   Hannes
// Propertie - Handling
// 
//    Rev 1.4   15 Aug 1998 16:00:26   Gerhold
// SetOleDocVarEx
// 
//    Rev 1.3   03 Aug 1998 18:04:58   Gerhold
// GetMyIUnknown war noch falsch
// 
//    Rev 1.2   29 Jul 1998 12:04:44   Gerhold
// OLEGetDocProp, OLERestrictInput, OLEUpdateFields
// 
//    Rev 1.1   28 Jul 1998 08:23:28   Gerhold
// 
//    Rev 1.0   22 Aug 1997 13:50:06   Gerhold
// Initial revision.
//--------------------------------------------------------------------------
typedef LPVOID * PPVOID;

#ifdef INITGUIDS
#include <initguid.h>
#endif //INITGUIDS


#ifndef WIN32
//OLE32 has these defined, OLE16 doesn't
#undef CLSID_Picture_Metafile
#undef CLSID_Picture_Dib
DEFINE_OLEGUID(CLSID_Picture_Metafile,        0x00000315, 0, 0);
DEFINE_OLEGUID(CLSID_Picture_Dib,             0x00000316, 0, 0);
#endif



#define   WMU_OLESERVER_HAS_CLOSED   WM_USER+80
#define   WMU_OLESERVER_WILLSAVE     WM_USER+81

class COleObject;

typedef COleObject FAR* LPCOLEOBJECT;

class CImpIAdviseSink : public IAdviseSink2
    {
    protected:
        ULONG               m_cRef;
        LPCOLEOBJECT        m_pCObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIAdviseSink(LPCOLEOBJECT, LPUNKNOWN);
        ~CImpIAdviseSink(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);
        STDMETHODIMP_(void)  OnLinkSrcChange(LPMONIKER);
    };


typedef CImpIAdviseSink FAR *PIMPIADVISESINK;



class CImpIOleClientSite : public IOleClientSite
    {
    protected:
        ULONG               m_cRef;
        LPUNKNOWN           m_pUnkOuter;
        class COleObject FAR*m_pObj;

    public:
        CImpIOleClientSite(LPCOLEOBJECT, LPUNKNOWN);
        ~CImpIOleClientSite(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP SaveObject(void);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP GetContainer(LPOLECONTAINER *);
        STDMETHODIMP ShowObject(void);
        STDMETHODIMP OnShowWindow(BOOL);
        STDMETHODIMP RequestNewObjectLayout(void);
    };

typedef CImpIOleClientSite FAR *PIMPIOLECLIENTSITE;


struct PropList {
  int iKind,iIndex,i;
  LPSTR Name,Value;
  PropList FAR *Next;
  };

class COleObject : public IUnknown
 {
 friend CImpIOleClientSite;
 friend CImpIAdviseSink;

 private:
  ULONG                m_cRef;
  LPOLEOBJECT          m_pIOleObject;
  PIMPIADVISESINK      m_pIAdviseSink;
  PIMPIOLECLIENTSITE   m_pIOleClientSite;
  LPSTORAGE            m_pIStorage;
  LPUNKNOWN            m_pObj;
  ULONG                m_grfMisc;
  HWND                 m_hWnd;

  PropList FAR *p;

 public:
  PropList FAR *GetProp ()
    {
    return p;
    }

  void AddProp (int i,int iKind,int iIndex) 
    {
    PropList FAR *x = (PropList FAR *) GetGlobMem (sizeof(*x));
    x->Next = p;
    p = x;
    x->iKind = iKind;
    x->iIndex = iIndex;
    x->i = i;
    }

  COleObject (LPSTORAGE pIStorage, HWND hWnd);
  ~COleObject (void);

  BOOL         Open (LPSTORAGE pIStorage);
  void         Close (void);
  void         SaveObject (void);
  BOOL         UCreate (LPTSTR pwcsTemp, LPFORMATETC fe);
  BOOL         ActivateObject (BOOL doActivate);
  BOOL         FObjectInitialize (LPUNKNOWN pObj, LPFORMATETC fe);
  BOOL         Load (LPFORMATETC pfe);
  void         Notify (DWORD NotifyMsg);
  BOOL         SetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL         RunAutoMacro (int wdAutoVar);
  BOOL         SetDocVarEx (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL         GetDocVar (LPCTSTR lpstrName, LPCTSTR lpstrValue);
  BOOL         PrintDoc (BOOL bSelectPrinter);
  BOOL         GetMyIUnknown (LPUNKNOWN FAR *MyObj);
  BOOL         GetOLEDocProp (int iKind, int iIndex, LPTSTR lpszName, LPTSTR lpszValue);
  BOOL         RestrictInput(int iLevel, LPTSTR lpszPassword);
  BOOL         UpdateFields ();
  BOOL         CloseApplicationWord (int iSaveChanges);
  BOOL         SaveWordObjectAs (LPTSTR lpszFileName, int iFileFormat);

  
  STDMETHODIMP QueryInterface(REFIID, PPVOID);
  STDMETHODIMP_(ULONG) AddRef(void);
  STDMETHODIMP_(ULONG) Release(void);

 };



class CTestDoc : public IUnknown
  {
  private:
    ULONG m_cRef;
  protected:
    PIMPIOLECLIENTSITE   m_pIOleClientSite;
  public:
      CTestDoc ();
      ~CTestDoc(void);

      STDMETHODIMP QueryInterface(REFIID, PPVOID);
      STDMETHODIMP_(ULONG) AddRef(void);
      STDMETHODIMP_(ULONG) Release(void);
  };
