///////////////////////////////////////////////////////////
//  Object Linking and Embadding
//
//  Einfaches Handling von der Marille aus
///////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/ole.cpv   1.2   05 Oct 1998 11:12:06   Gerhold  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/ole.cpv  $
// 
//    Rev 1.2   05 Oct 1998 11:12:06   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.1   02 Feb 1996 10:46:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 16:48:52   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   03 Mar 1994 22:04:46   HANNES
// Initial revision.
//
#ifdef WIN32
#define INC_OLE1
#endif

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"

#ifndef WIN32
#include <ole.h>
#endif

#include "ole.hpp"
#define MODULENUM   73
#include "winass.hpp"
#include "ddsmsg.h"

#define DMWS     MyLRString (107)
#define DMWSDOC  MyLRString (108)

extern HINSTANCE hLibInst;
LPSTR MyLRString (int Nr)
  {
  static char txt[128];
  *txt = '\0';
  LoadString (hLibInst,Nr,txt,sizeof(txt));
  return txt;
  }

LHCLIENTDOC lhcDoc ;
LPOLECLIENT ActClient;
LPAPPITEM ActlpItem;
static void MyEndClient ()
  {          
#ifndef WIN32
  if (lhcDoc)
    OleRevokeClientDoc(lhcDoc);
  if (ActClient) {
    if (ActClient->lpvtbl)
      FreeGlobMem (ActClient->lpvtbl);
    FreeGlobMem (ActClient);
    }
  lhcDoc = 0;
#endif
  }


//
// WaitForObject()
//
// Dispatch messagee until the specified object is not busy. 
// This allows asynchronous processing to occur.
//
static void ProcessMessage ()
  {
  MSG msg;
  if (GetMessage(&msg, NULL, NULL, NULL)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg); 
    }
  }

void WaitForObject (LPAPPITEM lpItem)
  {
#ifndef WIN32
  int i = 0;

  while (OleQueryReleaseStatus(lpItem->lpObject) == OLE_BUSY) {
    ProcessMessage();
    }
#endif
  }


static void FreeAppItem (LPAPPITEM lpItem)
  {                                     //- LOCAL:
#ifndef WIN32
  if (lpItem != NULL) {
    if (lpItem->aLinkName)
      DeleteAtom(lpItem->aLinkName);

    if (lpItem->aServer)
      DeleteAtom(lpItem->aServer);

    FreeGlobMem (lpItem);
    }
#endif
  }

// Schlimme Errors warnen, OLE_WAIT_FOR_RELEASE durchlassen !!
//////////////////////////////////
static int Error (OLESTATUS olestat)
  {
#ifndef WIN32
  switch (olestat) {
    case OLE_WAIT_FOR_RELEASE:
    case OLE_OK:
      return 0;

    case OLE_ERROR_STATIC:
      WIN_ASSERT_TEXT (FALSE,"Static Object");
      break;

    case OLE_ERROR_CLASS:
      WIN_ASSERT_TEXT (FALSE,"OLE_ERROR_CLASS:\rNo Paint Program for Bmps registered");
      break;

    case OLE_ERROR_REQUEST_PICT:
    case OLE_ERROR_ADVISE_RENAME:
    case OLE_ERROR_DOVERB:
    case OLE_ERROR_SHOW:
    case OLE_ERROR_OPEN:
    case OLE_ERROR_NETWORK:
    case OLE_ERROR_ADVISE_PICT:
    case OLE_ERROR_COMM:             //- Invalid links
      WIN_ASSERT_TEXT (FALSE,"Invalid Link");
      break;

    default:
      break;
    }
#endif
  return olestat;
  }

BOOL SaveIsDone;
void ObjDelete (LPAPPITEM lpItem)
  {
#ifndef WIN32
  if (OleRelease (lpItem->lpObject) == OLE_WAIT_FOR_RELEASE)
    WaitForObject (lpItem);
  FreeAppItem (lpItem); 
#endif
  }

static void Delete (LPAPPITEM lpItem)
  {
  WaitForObject (lpItem);
  ObjDelete (lpItem);
  }

static void Release (LPAPPITEM lpItem)
  {
#ifndef WIN32
  WORD wParam;

  if ((wParam = OleQueryReleaseError(lpItem->lpObject)) == OLE_OK) 
     return;

  switch (OleQueryReleaseMethod(lpItem->lpObject)) {
    case OLE_LNKPASTE:
      lpItem->fVisible = FALSE;
      break;

    case OLE_CREATEFROMTEMPLATE:
    case OLE_CREATE:
      lpItem->fVisible = FALSE;
      Delete (lpItem);
      break;
    }
#endif
  }

// OLE - Client CallBack - Funktion:
//  Grundlegende Reaktionen auf Anforderungen / Mitteilungen des
//  Servers
////////////////////////////////////////////////////////////////
DLLExport void _export WINAPI OnWMUDeleteObj (LONG lP)
  {
  LPAPPITEM lpAppItem = LPAPPITEM (lP);
  Delete (LPAPPITEM(lpAppItem));
  MyEndClient ();
  }

HWND hAppWnd;
OLESAVEPROC SaveProc;
LPVOID privPtr;
BOOL ServerIsClosing = FALSE ;
DLLExport int _export WINAPI OLE_CallBack (LPOLECLIENT lpClient,OLE_NOTIFICATION flags,
                                     LPOLEOBJECT lpObject
                                    )
  {
#ifndef WIN32
  switch (flags) {
    case OLE_CLOSED:                 //- server has closed
      ServerIsClosing = TRUE ;
      (* SaveProc) (privPtr,0,OLECB_EXIT);
      PostMessage (hAppWnd,WMU_DELETEOBJ,0,LONG(lpClient));
      SetFocus (hAppWnd);
      break;

    case OLE_SAVED:                  //- server has saved object
    case OLE_CHANGED:                //- object has changes
      {
      SaveIsDone = TRUE ;
      GLOBALHANDLE hData = 0;
      if ((OleGetData (lpObject,CF_DIB,&hData) != OLE_WARN_DELETE_DATA) && (hData)) {
        GLOBALHANDLE hGCopy = GlobalAlloc (GMEM_MOVEABLE,GlobalSize (hData));
        LPSTR lpcopy = LPSTR(GlobalLock (hGCopy));
        LPSTR lpdata = LPSTR(GlobalLock (hData));
        hmemcpy (lpcopy,lpdata,GlobalSize (hData));
        GlobalUnlock (hGCopy);
        GlobalUnlock (hData);
        hData = hGCopy ;
        }
      if (hData)
        (* SaveProc) (privPtr,hData,OLECB_SAVE);
      }
      // Save Data 
      break;

    case OLE_QUERY_RETRY:  //- Continue retrying or Painting
    case OLE_QUERY_PAINT:
      return TRUE ;

    case OLE_RELEASE:
      break ;

    default:
      break;
    }
#endif
  return 0;
  }

//
// Initialize the OLE client structure, create and fill the OLECLIENTVTBL 
// structure.
//
// Returns LPOLECLIENT
//
DLLExport LPOLECLIENT _export WINAPI InitOLE (HWND hFrameWnd,OLESAVEPROC svProc,LPVOID svPtr)
  {
#ifndef WIN32
  hAppWnd = hFrameWnd;
  SaveProc = svProc;
  privPtr  = svPtr;
  LPOLECLIENT lpClient = LPOLECLIENT (GetGlobMem (sizeof(OLECLIENT)));
  lpClient->lpvtbl     = LPOLECLIENTVTBL (GetGlobMem (sizeof(OLECLIENTVTBL)));
  lpClient->lpvtbl->CallBack = OLE_CallBack;

  ActClient = lpClient;
  SaveIsDone = FALSE ;
  return lpClient;                    //- SUCCESS return
#else
  return NULL;
#endif
  }


// PreItemCreate()
//
// This routine allocates an application item structure. A pointer to this 
// structure is passed as the client structure, therefore we need to 
// have a pointer to the vtbl as the first entry. We are doing this 
// to allow acess to the application item information during a OLE
// DLL callback.  This approach simplifies matters.
//
// Returns APPITEMPTR - a pointer to a new application item structure
//                      which can operate as a client structure.
static LPAPPITEM PreItemCreate (LPOLECLIENT lpClient,BOOL fShow,LHCLIENTDOC lhcDoc)
  {
#ifndef WIN32
  LPAPPITEM lpItem = LPAPPITEM (GetGlobMem (sizeof(*lpItem)));
  lpItem->oleclient.lpvtbl     = lpClient->lpvtbl;
  lpItem->lpObjectUndo         = NULL;
  lpItem->fVisible             = fShow;
  lpItem->fServerChangedBounds = FALSE;
  lpItem->lhcDoc               = lhcDoc;

  return lpItem;
#else
  return NULL;
#endif
  }

static LPSTR FAR CreateNewUniqueName (LPSTR lpstr,LPSTR name)
  {
  static int iObjectNumber;
  if (name == NULL)
    wsprintf (lpstr,"%s%04d",DMWS,iObjectNumber++);
  else
    wsprintf (lpstr,"%s%s%04d",DMWS,name,iObjectNumber++);
  return lpstr;
  }

// Vervollstaendigen der Creationsdaten
/////////////////////////////////////////////
static BOOL PostItemCreate (LPOLEOBJECT lpObject,LPAPPITEM lpItem)
  {
#ifndef WIN32
  lpItem->otObject = OT_EMBEDDED;
  lpItem->lpObject = lpObject;
  lpItem->fRetry  = TRUE;

  char sz[128];
  unsigned int cb = sizeof(sz);
  OleQueryName(lpObject, (LPSTR)sz, &cb );

  WaitForObject(lpItem);
  Error(OleSetHostNames (lpObject,DMWS,sz));
  WaitForObject(lpItem);
#endif
  return TRUE;
  }

//
// Hauptprozedur:
//  Aufbau der Verbindung
//
#define STDFILEEDITING     ((LPSTR) "StdFileEditing")
LHCLIENTDOC RegisterDoc ()
  {
#ifndef WIN32
  LHCLIENTDOC res;
  Error (OleRegisterClientDoc(DMWS, DMWSDOC, 0L, &res)) ;
  return res;
#else
  return 0;
#endif
  }

DLLExport void _export WINAPI ObjCreateFromTemplate (LPOLECLIENT lpClient,LPSTR FileName,LPSTR name)
  {                                     
#ifndef WIN32
  LPOLEOBJECT lpObject;
  char        szTmp     [128];
  lhcDoc = RegisterDoc ();

  LPAPPITEM lpItem = PreItemCreate (lpClient, FALSE, lhcDoc);
  ActlpItem = lpItem;
  if (Error(OleCreateFromTemplate (STDFILEEDITING,LPOLECLIENT(lpItem),FileName,
             lhcDoc,CreateNewUniqueName(szTmp,name),&lpObject,olerender_draw, 0))) {
    ServerIsClosing = TRUE ;
    (* SaveProc) (privPtr,0,OLECB_EXIT);
    MyEndClient ();
    FreeAppItem (lpItem);
    }
  else
    PostItemCreate (lpObject,lpItem);
#endif
  }

// Abbauen der Verbindung
////////////////////////////////////
DLLExport void _export WINAPI EndClient (LPOLECLIENT lpClient)
  {          
#ifndef WIN32
  if (!ServerIsClosing) {
    if (ActlpItem != NULL) {
      OleDelete (ActlpItem->lpObject);
      WaitForObject (ActlpItem);
      }
    MyEndClient ();
    }
#endif
  }

