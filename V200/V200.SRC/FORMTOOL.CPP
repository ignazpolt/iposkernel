//---------------------------------------------------------------------------
// Kindfenster in einem MDI-Fensters zur Verwaltung von Knoepfen 
//---------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/rev/formtool.cpv   1.6   16 Jun 2000 17:08:26   Gerhold  $
//  $Log:   P:/marille/clinicum/rev/formtool.cpv  $
// 
//    Rev 1.6   16 Jun 2000 17:08:26   Gerhold
// Beim FormTool werden jetzt Extradaten mitgespeichert
// (wegen des Kontextes im ExcuteProc)
// 
//    Rev 1.5   05 Oct 1998 11:54:14   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   25 Sep 1996 10:22:14   GERHOLD
// Im FormTool::~FormTool war kein "DestroyWindow" !!!!!
// 
//    Rev 1.3   10 Jun 1996 10:07:38   GERHOLD
// pragma pack
// 
//    Rev 1.2   22 Apr 1996 10:02:52   GERHOLD
// WIN32 - Aenderung (FreeProcInstance, ...)
// 
//    Rev 1.1   22 Mar 1996 12:24:02   GERHOLD
// Nach dem Create ein WM_SIZE schicken
// 
//    Rev 1.0   18 Mar 1996 17:02:46   GERHOLD
// Initial revision.
//---------------------------------------------------------------------------
#define MODULENUM  165

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "cfield.hpp"
//#include "mover.hpp"
#include "buttons.hpp"


#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#include "dllchild.hpp"

#include "winextra.hpp"
#define NODLL
#define WITHINDDS
#include "toolbar.hpp"
#include "mdiclien.hpp"

#include "winass.hpp"

#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#include "tbcbd.hpp"


#ifndef WIN32
#define  BF_RECT  2
#endif

#define  ANZBUTTONS  3

#define  LEFTBTN     0
#define  RIGHTBTN    1
#define  MOVEBTN     2



#define ENTER1(A) if (BlockIsActive) { \
                    A ; \
                    } \
                  else { \
                    if (LPTBD(PrivData)->Extra != NULL) { \
                      SAVEREC old; \
                      LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                      SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                      LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();     \
                      LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;     \
                      A ; \
                      LPTBD(PrivData)->c->RestoreRecs(old);  \
                      } \
                    else { \
                      RestoreListFnc rlf (LPTBD(PrivData)->c);  \
                      A ; \
                      } \
                    }
#define ENTER1DEB(A) if (BlockIsActive) { \
                        PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                        A ; \
                        } \
                      else { \
                        if (LPTBD(PrivData)->Extra != NULL) { \
                          SAVEREC old; \
                          LPTBD(PrivData)->c->SetRecsForUpdate (old,LPTBD(PrivData)->Extra); \
                          SetExtraInfo s(LPTBD(PrivData)->c,LPTBD(PrivData)->Extra); \
                          PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                          LPTBD(PrivData)->c->_GetRecExtra()->cmdBase = LPTBD(PrivData)->c->GetCmdBase();     \
                          LPTBD(PrivData)->c->_GetRecExtra()->cOffs = 0;     \
                          A ; \
                          LPTBD(PrivData)->c->RestoreRecs(old);  \
                          } \
                        else { \
                          PushToCallStack (LPTBD (PrivData)->c,LPTBD (PrivData)->c->schd->fName,LPTBD (PrivData)->c->GetCmdOffset (par)); \
                          RestoreListFnc rlf (LPTBD(PrivData)->c);  \
                          A ; \
                          } \
                        }



//---------------------------------------------------------------------------
// Diese Prozedur wird von den Knoepfen in BUTTONS.CPP aufgerufen
//---------------------------------------------------------------------------
DLLExport void _export WINAPI BtnCallCommand (LPVOID PrivData, DWORD CmdOffs, LPVOID par)
  {
#ifdef DEBUG
  ENTER1DEB (
    LPTBD(PrivData)->c->ExCuteProc (CmdOffs, EM_LOAD | EM_CHANGETOTRUE);
    LPTBD(PrivData)->c->ExCuteProc (CmdOffs, EM_RESET);
    ) ;
#else
  ENTER1 (
    LPTBD(PrivData)->c->ExCuteProc (CmdOffs, EM_LOAD | EM_CHANGETOTRUE);
    LPTBD(PrivData)->c->ExCuteProc (CmdOffs, EM_RESET);
    ) ;
#endif

#ifdef DEBUG
    PopFromCallStack ();
#endif
  }


class FAR FormTool {
 public:
  HWND hWndParent;
  HWND hWndFormTool;
  int w;
  int h;
  BTNPROC btnproc;

  LPBTNLIST Buttons;
  
  FormTool (HWND hWnd, int fw, int fh);
  ~FormTool ();

  void SetButtonProc ();
  void RemoveButtonProc ();

  
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
    
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef FormTool FAR * LPFORMTOOL;



long FAR PASCAL FormToolWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
  LPFORMTOOL lpft = (LPFORMTOOL)GetWindowLong (hWnd, 0);

  if ((lpft != NULL) && (lpft->Buttons != NULL)) {
    BOOL done;
    LONG RetVal = lpft->Buttons->CheckMsg (hWnd,message,wParam,lParam,&done);
    if (done)
      return RetVal;
    }

  switch (message) {
    case WM_CREATE:
      {
      }
      break;

    // nimmt die Abmessungen des Elternfensters, und paßt sich an
    case WM_SIZE:
      {

      if (lpft != NULL) {
        RECT rc;
        GetClientRect (GetParent(hWnd), &rc);
  
        int h = lpft->h > 0 ? lpft->h : GetSystemMetrics (SM_CYMENU);
        MoveWindow (hWnd, -1, rc.bottom-h, rc.right+2, h, TRUE);
        }
      }
      break;
      
    case WM_PAINT:
      {
      PAINTSTRUCT PS;
      HDC hDC = BeginPaint (hWnd, &PS);
      
      if ((lpft != NULL) && (lpft->Buttons != NULL))
        lpft->Buttons->Paint (hDC);

      EndPaint (hWnd, &PS);
      }
      break;
/*
    case WM_DESTROY:
      MessageBeep (0);
      break;
*/
    default:
      return (DefWindowProc(hWnd, message, wParam, lParam));
    }

  return 0;
  }





BOOL InitFormTool ()
  {
  static BOOL bRegistered = FALSE;

  if (!bRegistered) {
    WNDCLASS  wc;
  
    wc.style = NULL;
    wc.lpfnWndProc = FormToolWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LPVOID);
    wc.hInstance = WBase::hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "FORMTOOL";
  
    if (RegisterClass(&wc))
      bRegistered = TRUE;
    }
    
  return bRegistered;  
  }
  
HWND CreateFormToolWindow (HWND hWndParent, int w, int h)
  {
  HWND hWndFormTool = 0;
  if (InitFormTool ()) {
    RECT rc;
    GetClientRect (hWndParent, &rc);

    hWndFormTool = CreateWindow ("FORMTOOL", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                               0, 0, 10, 10,
                               hWndParent, 0, WBase::hInstance, NULL);
    if (hWndFormTool)
      SendMessage (hWndFormTool, WM_SIZE, 0, 0);
    }
    
  return hWndFormTool;  
  }



FormTool::FormTool (HWND hWnd, int fw, int fh)
  {
  hWndParent = hWnd;
  hWndFormTool = 0;
  w = fw;
  h = fh;
  Buttons = NULL;
  btnproc = NULL;

  if (InitFormTool ()) {
    hWndFormTool = CreateWindow ("FORMTOOL", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                               0, 0, fw, fh,
                               hWndParent, 0, WBase::hInstance, NULL);

    if (hWndFormTool) {
      SetWindowLong (hWndFormTool, 0, LONG(this));
      SendMessage (hWndFormTool, WM_SIZE, 0, 0);
      }

    }
  }

FormTool::~FormTool () 
  { 
  delete Buttons; 
  
  SetWindowLong (hWndFormTool, 0, LONG(NULL));
  DestroyWindow (hWndFormTool);
  }

//----------------------------------------------------------------------------
//
// SetButtonProc
//
// Das FormTool verwaltet die Adresse der Haupt-Knopf-Prozedur.
// Diese Prozedur wird von den einzelnen Knoepfen aufgerufen, wobei jeder
// Knopf eine eigene CPL Prozedur besitzt.
//----------------------------------------------------------------------------
void FormTool::SetButtonProc ()
  {
#ifdef WIN32
  btnproc = BtnCallCommand;
#else
  btnproc = (BTNPROC)MakeProcInstance(FARPROC(BtnCallCommand),WBase::hInstance);
#endif
  }

void FormTool::RemoveButtonProc ()
  {
#ifndef WIN32
  FreeProcInstance(FARPROC(btnproc));
#endif
  }



//---------------------------------------------------------------------------
// Das FormTool ist ein Kindfenster in einem MDICHILD, und verwaltet eine 
// Liste von Knoepfen die eine Prozedur in Script aufrufen.
//---------------------------------------------------------------------------
#pragma pack(1)
struct SetFormTool_param {
  WORD parSize;
  DWORD FormTool;
  DWORD w;
  DWORD h;
  };
#pragma pack()


static HWND ChildWithFormTool = 0;    // MDI-Child in dem das Formtool angelegt wird
static LPFORMTOOL lpFormTool = NULL;

//============================================================================
//
// CPL Funktion  CreateFormTool
//
// CreateFormTool (FormObj, 0, 25);
// FormToolPictureButton (FormObj, 0, 0, 28, 0, FALSE, PreviousMonth, ...
// FormToolTextButton    (FormObj, 0, 0, 80, 0, FALSE, DateProc, "Datum", 5);
//============================================================================
BOOL CreateFormTool (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WIN_ASSERT((ChildWithFormTool == 0) && (lpFormTool == NULL));
    ChildWithFormTool = c->OutWnd();
    SetFormTool_param FAR * par = (SetFormTool_param FAR *)param ;

    DBINT FAR *lpw = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *lph = (DBINT FAR *) c->ReadlData (par->h);

    int w = (lpw != NULL) ? *lpw : 0;
    int h = (lph != NULL) ? *lph : 0;

    lpFormTool = new FormTool (ChildWithFormTool, w, h);
    WIN_ASSERT (lpFormTool != NULL);

    // Die Adresse der Callback-Funktion bekanntgeben
    lpFormTool->SetButtonProc ();
  
    lpFormTool->Buttons = new BtnList (lpFormTool->hWndFormTool);
    WIN_ASSERT (lpFormTool->Buttons != NULL);

    ShowScrollBar (ChildWithFormTool, SB_BOTH, FALSE);
    }

  if (mode & EM_UPDATE) {
    SetFormTool_param FAR * par = (SetFormTool_param FAR *)param ;
    }

  if (mode & EM_FIXCONNECTION) {
    SetFormTool_param FAR * par = (SetFormTool_param FAR *)param ;
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    SetFormTool_param FAR * par = (SetFormTool_param FAR *)param ;

    // alles aufraeumen
    lpFormTool->RemoveButtonProc ();

    delete lpFormTool;
    lpFormTool = NULL;
    
    ChildWithFormTool = 0;
    }

  return FALSE ;
  }


//---------------------------------------------------------------------------
// FormToolPictureButton
//  ... Ein Knopf mit Bild
//---------------------------------------------------------------------------
#pragma pack(1)
struct FormToolPictureButton_param {
  WORD parSize;
  DWORD FormTool; // Parent
  DWORD x;
  DWORD y;
  DWORD w;
  DWORD h;
  DWORD disabled;
  DWORD proc;
  DWORD bmp;      // Bitmap Ressource
  DWORD ix;       // horizontaler Index
  DWORD iy;       // vertikaler Index
  };
#pragma pack()

BOOL FormToolPictureButton (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WIN_ASSERT (IsWindow(ChildWithFormTool) && (lpFormTool != NULL));
    FormToolPictureButton_param FAR * par = (FormToolPictureButton_param FAR *)param ;

    int AnzRows, AnzCols;
    HBITMAP hBmp = GetBitmap (
                        par->bmp,
                        AnzRows, AnzCols
                             );
    WIN_ASSERT (hBmp != 0);

    LPBITBUTTON Button;

    DBINT FAR *lpx = (DBINT FAR *) c->ReadlData (par->x);
    DBINT FAR *lpy = (DBINT FAR *) c->ReadlData (par->y);
    DBINT FAR *lpw = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *lph = (DBINT FAR *) c->ReadlData (par->h);
    DBINT FAR *lpix = (DBINT FAR *) c->ReadlData (par->ix);
    DBINT FAR *lpiy = (DBINT FAR *) c->ReadlData (par->iy);

    int x = (lpx != NULL) ? *lpx : 0;
    int y = (lpy != NULL) ? *lpy : 0;
    int w = (lpw != NULL) ? *lpw : 0;
    int h = (lph != NULL) ? *lph : 0;
    int ix = (lpix != NULL) ? *lpix : 0;
    int iy = (lpiy != NULL) ? *lpiy : 0;
    
    // bei einer Hoehe von 0 nimmt der Knopf die Hoehe des Parents an
    if (h == 0)
      h = lpFormTool->h - 1;

    // bei einer Position von 0 wird der Knopf an seinen Vorgaenger angehaengt
    if ((x == 0) && (lpFormTool->Buttons->First != NULL)) {
      x = lpFormTool->Buttons->First->Item->x + lpFormTool->Buttons->First->Item->GetWidth();
      }
    

    toolbar_cbdata tbcbd(c);
    Button = new BitButton (&tbcbd, sizeof(tbcbd),
                            lpFormTool->hWndFormTool, x, y, w, h, 
                            hBmp, AnzCols, AnzRows, ix, iy);

    // der Knopf bekommt eine externe Prozedur
    Button->SetButtonProc (lpFormTool->btnproc, par->proc, LPSTR(param)-sizeof(WORD));

    lpFormTool->Buttons->Insert (Button);
    }
    
  if (mode & (EM_RESET | EM_CLEAR)) {
    }
    
  return FALSE;
  }


//---------------------------------------------------------------------------
// FormToolTextButton
//  ... Ein Knopf mit Text
//---------------------------------------------------------------------------
#pragma pack(1)
struct FormToolTextButton_param {
  WORD parSize;
  DWORD FormTool;   // Parent
  DWORD x;          
  DWORD y;
  DWORD w;
  DWORD h;
  DWORD disabled;
  DWORD proc;
  DWORD txt;
  DWORD format;     // Formatnummer des Textes
  };
#pragma pack()

BOOL FormToolTextButton (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WIN_ASSERT (IsWindow(ChildWithFormTool) && (lpFormTool != NULL));
    FormToolTextButton_param FAR * par = (FormToolTextButton_param FAR *)param ;

    LPTEXTBUTTON Button;

    DBINT FAR *lpx = (DBINT FAR *) c->ReadlData (par->x);
    DBINT FAR *lpy = (DBINT FAR *) c->ReadlData (par->y);
    DBINT FAR *lpw = (DBINT FAR *) c->ReadlData (par->w);
    DBINT FAR *lph = (DBINT FAR *) c->ReadlData (par->h);
        LPSTR  txt =     (LPSTR) c->ReadlData (par->txt);
    DBINT FAR *lpformat = (DBINT FAR *) c->ReadlData (par->format);

    int x = (lpx != NULL) ? *lpx : 0;
    int y = (lpy != NULL) ? *lpy : 0;
    int w = (lpw != NULL) ? *lpw : 0;
    int h = (lph != NULL) ? *lph : 0;
    int format = (lpformat != NULL) ? *lpformat : 0;
    
    // bei einer Hoehe von 0 nimmt der Knopf die Hoehe des Parents an
    if (h == 0)
      h = lpFormTool->h - 1;

    // bei einer Position von 0 wird der Knopf an seinen Vorgaenger angehaengt
    if ((x == 0) && (lpFormTool->Buttons->First != NULL)) {
      x = lpFormTool->Buttons->First->Item->x + lpFormTool->Buttons->First->Item->GetWidth();
      }

    
    toolbar_cbdata tbcbd(c);
    Button = new TextButton (&tbcbd, sizeof(tbcbd), 
                             lpFormTool->hWndFormTool, x, y, w, h, txt, format);

    // der Knopf bekommt eine externe Prozedur
    Button->SetButtonProc (lpFormTool->btnproc, par->proc, LPSTR(param)-sizeof(WORD));

    lpFormTool->Buttons->Insert (Button);
    }
    
  return FALSE;
  }

//-----------------------------------------------------------------------------
// Wenn sich die Groesse des Parents aendert wird dies dem FormTool mitgeteilt
//-----------------------------------------------------------------------------
int SetNewFormToolDimension (HWND hWnd, int cx, int cy)
  {
  int h = 0;       // Hoehe des FormTools
  if ((hWnd == ChildWithFormTool) && (lpFormTool != NULL)) {
    MoveWindow (lpFormTool->hWndFormTool, 0, 0, cx, cy, TRUE);

    RECT rc;
    GetClientRect (lpFormTool->hWndFormTool, &rc);
    h = rc.bottom - rc.top;
    }
  
  return h;
  }
