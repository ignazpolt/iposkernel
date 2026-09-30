//
// Funktionsprototypen und Datenstrukturen fuer OLE - Handling
//
//  $Header:   P:/marille/clinicum/include/rev/ole.hpv   1.1   02 Feb 1996 11:00:06   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/ole.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:52   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   03 Mar 1994 22:06:44   HANNES
// Initial revision.
//

#define OLECB_SAVE      0
#define OLECB_EXIT      1
typedef void (WINAPI * OLESAVEPROC) (LPVOID,GLOBALHANDLE,int);
DLLExport LPOLECLIENT _export WINAPI InitOLE (HWND hFrameWnd,OLESAVEPROC svProc,LPVOID svPtr);
DLLExport int _export WINAPI OLE_CallBack (LPOLECLIENT lpClient,OLE_NOTIFICATION flags,
                                     LPOLEOBJECT lpObject
                                    );
DLLExport void _export WINAPI ObjCreateFromTemplate (LPOLECLIENT lpClient,LPSTR FileName,LPSTR name);
DLLExport void _export WINAPI EndClient (LPOLECLIENT lpClient);
DLLExport void _export WINAPI OnWMUDeleteObj (LONG lP);

typedef struct _APPITEM FAR *LPAPPITEM;
typedef struct _APPITEM {             //- Application item
  OLECLIENT         oleclient;
  HWND              hwnd; 
  LPOLEOBJECT       lpObject;         //- OLE object pointers
  LPOLEOBJECT       lpObjectUndo;     //- undo object
  LONG              otObject;         //- OLE object type
  LONG              otObjectUndo;
  OLEOPT_UPDATE     uoObject;         //- OLE object update option
  OLEOPT_UPDATE     uoObjectUndo;     //- link name atom
  ATOM              aLinkName;        //- Save the link's document name 
  ATOM              aLinkUndo;        //- Save the link's document name 
  LPSTR             lpLinkData;       //- pointer to link data
  BOOL              fVisible;         //- TRUE: item is to be displayed
  BOOL              fOpen;            //- server open? --for undo objects
  BOOL              fRetry;           //- retry flag for busy servers
  BOOL              fNew;
  BOOL              fServerChangedBounds;
  RECT              rect;             //- bounding rectangle
  LHCLIENTDOC       lhcDoc;           //- client document handle
  ATOM              aServer;
  } APPITEM;                             

