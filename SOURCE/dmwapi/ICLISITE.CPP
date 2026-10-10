//--------------------------------------------------------------------------
// OleClientSite - Notifikation fuer OLE2
//--------------------------------------------------------------------------
// $Header:   P:/marille/clinicum/dmwapi/rev/iclisite.cpv   1.1   15 Jan 1999 18:20:36   Hannes  $
// $Log:   P:/marille/clinicum/dmwapi/rev/iclisite.cpv  $
// 
//    Rev 1.1   15 Jan 1999 18:20:36   Hannes
// Propertie - Handling
// 
//    Rev 1.0   22 Aug 1997 12:39:44   Gerhold
// Initial revision.
//--------------------------------------------------------------------------

#include <windows.h>
#ifdef WIN32
#include <winver.h>
#else
#include <winver.h>
#endif

#include "dds32.h"

#include <ole2.h>

#ifndef WIN32
#include "dvobj.h"

#include "win1632.h"
#include "compobj.h"
#endif

 
#include "globmem.h"

#include "iclisite.hpp"
#include "olemain.hpp"


CImpIOleClientSite::CImpIOleClientSite(LPCOLEOBJECT lpObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pObj = lpObj;
    return;
    }

CImpIOleClientSite::~CImpIOleClientSite(void)
    {
    return;
    }




/*
 * CImpIOleClientSite::QueryInterface
 * CImpIOleClientSite::AddRef
 * CImpIOleClientSite::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleClientSite object.
 */

STDMETHODIMP CImpIOleClientSite::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleClientSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleClientSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleClientSite::SaveObject
 *
 * Purpose:
 *  Requests that the container call OleSave for the object that
 *  lives here.  Typically this happens on server shutdown.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::SaveObject(void)
    {
    //We're already set up with the tenant to save; this is trivial.
    m_pObj->SaveObject();
    return NOERROR;
    }





/*
 * CImpIOleClientSite::GetMoniker
 *
 * Purpose:
 *  Retrieves the moniker for the site in which this object lives,
 *  either the moniker relative to the container or the full
 *  moniker.
 *
 * Parameters:
 *  dwAssign        DWORD specifying that the object wants moniker
 *                  assignment.  Yeah.  Right.  Got any bridges to
 *                  sell?
 *  dwWhich         DWORD identifying which moniker the object
 *                  wants, either the container's moniker, the
 *                  moniker relative to this client site, or the
 *                  full moniker.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::GetMoniker(DWORD dwAssign, DWORD dwWhich, LPMONIKER *ppmk)
    {
    *ppmk=NULL;

    /*
     * We don't yet want to allow for linking to embedded objects
     * within us, so we just fail for now.  If you are only a simple
     * container you never have to implement this function.
     */
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIOleClientSite::GetContainer
 *
 * Purpose:
 *  Returns a pointer to the document's IOleContainer interface.
 *
 * Parameters:
 *  ppContainer     LPOLECONTAINER * in which to return the
 *                  interface.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::GetContainer(LPOLECONTAINER * ppContainer)
    {
    //Only necessary if you allow linking to embeddings
    *ppContainer=NULL;
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIOleClientSite::ShowObject
 *
 * Purpose:
 *  Tells the container to bring the object fully into view as much
 *  as possible, that is, scroll the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::ShowObject(void)
    {
    /*
     * We let the tenant do this, since it can access the current
     * scroll position as a friend of CPages whereas we cannot.
     */
//    m_pTen->ShowYourself();
    return NOERROR;
    }






/*
 * CImpIOleClientSite::OnShowWindow
 *
 * Purpose:
 *  Informs the container if the object is showing itself or
 *  hiding itself.  This is done only in the opening mode and allows
 *  the container to know when to shade or unshade the object.
 *
 * Parameters:
 *  fShow           BOOL indiciating that the object is being shown
 *                  (TRUE) or hidden (FALSE).
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::OnShowWindow(BOOL fShow)
    {
    //All we have to do is tell the tenant of the open state change.
//    m_pTen->ShowAsOpen(fShow);
    if (fShow)
      EnableWindow (m_pObj->m_hWnd, FALSE);
    else
      EnableWindow (m_pObj->m_hWnd, TRUE);

    return NOERROR;
    }






/*
 * CImpIOleClientSite::RequestNewObjectLayout
 *
 * Purpose:
 *  Called when the object needs more room in the container.
 *  This is not used in OLE 2.0
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::RequestNewObjectLayout(void)
    {
    //Nothing to do since this is not supported in OLE 2.0.
    return ResultFromScode(E_NOTIMPL);
    }



CTestDoc::CTestDoc()
    {
    m_pIOleClientSite=NULL;
    return;
    }


CTestDoc::~CTestDoc(void)
    {
    if (NULL!=m_pIOleClientSite)
        delete m_pIOleClientSite;

    return;
    }


STDMETHODIMP CTestDoc::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IOleClientSite==riid)
        *ppv=m_pIOleClientSite;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CTestDoc::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CTestDoc::Release(void)
    {
    ULONG           cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        delete this;

    return cRefT;
    }

