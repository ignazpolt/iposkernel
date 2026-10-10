//////////////////////////////////////////////////////////////////
//  Drag und Drop innerhalb des Tools
//////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/drdrop.cpv   1.15   05 Oct 1998 11:25:46   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/drdrop.cpv  $
// 
//    Rev 1.15   05 Oct 1998 11:25:46   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.14   28 Aug 1997 15:49:46   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.13   02 Feb 1996 10:50:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.12   27 Aug 1995 13:00:34   HANNES
// 
//    Rev 1.11   10 Apr 1995 10:44:18   GERHOLD
// 
//    Rev 1.10   31 Mar 1995 12:48:02   GERHOLD
// Das Edit-Feld muss alle D&D-Typen bearbeiten koennen
// 
//    Rev 1.9   24 Feb 1995 11:10:12   GERHOLD
// Ein D&D-Element kann jetzt verschiedene Typen aufnehmen
// 
//    Rev 1.8   16 Feb 1995 12:33:10   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.7   02 Jan 1995 09:29:36   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.5   08 Aug 1994 17:36:54   GERHOLD
// auf OK-Button aus den Dialogen reagieren
// 
//    Rev 1.4   01 Aug 1994 15:37:18   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.3   25 Jul 1994 09:36:00   GERHOLD
// Drag&Drop fuer Formate
// 
//    Rev 1.2   20 Jul 1994 17:02:38   GERHOLD
// Aenderungen im Handling der Mauskoordinaten im Server und Container
// 
//    Rev 1.1   12 Jul 1994 14:41:54   HANNES
// Erweiterungen
// 
//    Rev 1.0   24 Jun 1994 16:54:46   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "drdrop.hpp"

LPDRAGDROP firstdrop;
extern HINSTANCE MyInstance;


void Drag_Drop::AddType (WORD t)
  {
  LPWORD n = LPWORD (GetGlobMem ((AnzTypes + 1) * sizeof(*n)));
  if (Typearr != NULL) {
    lmemcpy (n,Typearr,AnzTypes * sizeof(*n));
    FreeGlobMem (Typearr);
    }
  Typearr = n;
  n[AnzTypes] = t;
  AnzTypes ++;
  }

//--------------------------------------------------------
// Ueberpruefung ob der gesuchte Typ stimmt
// oder ob die Mausmeldungen auf einem Server passieren
//--------------------------------------------------------
BOOL Drag_Drop::TestType (WORD t)
  { 
  for (int i = 0; i < AnzTypes; i++)
    if (Typearr[i] == t)
      return TRUE;

  return (FALSE);
  }

//--------------------------------------------------------
// Ueberpruefung ob Mauskoordinaten im Container
//--------------------------------------------------------
BOOL Drag_Drop::TestKoord (LPPOINT pt)    
  { 
  return ((pt->x >= x1) && (pt->x <= x2) && 
          (pt->y >= y1) && (pt->y <= y2));
  }

void Drag_Drop::GetKoords (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);  // Bildschirmkoordinaten des umgebenden Fensterrechteckes
  x1 = r.left ;    y1 = r.top ;
  x2 = r.right ;   y2 = r.bottom ;
  }

void Drag_Drop::AddToList ()
  {
  Next = firstdrop ;
  firstdrop = this ;
  }

void Drag_Drop::RemoveFromList ()
  {
  LPDRAGDROP FAR *p = &firstdrop ;
  for (LPDRAGDROP h = firstdrop ; h != NULL ; p = &h->Next , h = h->Next ) {
    if (h == this) {
      *p = h->Next ;
      delete (h);
      break ;
      }
    }
  }

HCURSOR Drag_Drop::TestPos (LPPOINT pt, HWND hServer, BOOL FAR *doStop)
  {
  // Mauskoordinaten im Container oder im Server?
  POINT ptClient;
  ptClient = *pt;
  ScreenToClient (hRefWnd, &ptClient);

  // Fenster das den D&D Vorgang beenden moechte
  HWND hHitWnd = WindowFromPoint (*pt);
  if ((hRefWnd == DropWnd) && ((hHitWnd == hRefWnd) || (GetParent(hHitWnd) == hRefWnd))) {
    *doStop = TRUE; 
    return GetHitCursor();
    }
  else if ((hRefWnd != DropWnd) && (ChildWindowFromPoint(hRefWnd, ptClient) == DropWnd)) {
    *doStop = TRUE; 
    return GetHitCursor();
    }
  // Fenster das den D&D Vorgang ausloeste
  else if (hHitWnd == hServer) {  
    *doStop = FALSE; 
    return GetHitCursor();
    }
  else { 
    *doStop = FALSE; 
    return GetNonHitCursor(); 
    }
  }

BOOL Drag_Drop::TestWnd (HWND hWnd)
  {
  return (hWnd == DropWnd);
  }

//---------------------------  DDOnMouseMove  -------------------------------
//
// Diese zentrale Routine muss bei allen Mausvorgängen aufgerufen werden.
// Die Boolesche Variable <last> wird nur bei "LButtonUp" auf TRUE gesetzt.
// Hier wird dann ueberprueft, ob auf der aktuellen Position etwas "fallen
// gelassen" werden darf.
//---------------------------------------------------------------------------
BOOL DDOnMouseMove (WORD Type, LPVOID dropData, LPPOINT pt, HWND hServer, BOOL last)
  {
  ClientToScreen (hServer, pt);  // Die Bildschirmkoordinaten des Server-Fensters

  HCURSOR hCur = 0;
  BOOL doStop = FALSE ;
  // sucht alle Drag&Drop-Container durch, bis der richtige gefunden ist.
  for (LPDRAGDROP h = firstdrop ; h != NULL ; h = h->Next) {
    if (h->TestType (Type)) {
      hCur = h->TestPos (pt, hServer, &doStop);    // Cursor waehrend des D&D Vorganges veraendern
      if (doStop) break;
      }
    }

  if (last) {                                      // D&D fertig?
    if (doStop) h->DoDrop (dropData, Type);        // Dropdaten ablegen
    SetCursor (LoadCursor (NULL, IDC_ARROW));      // Standardcursor
    }
  else {                                           // noch im D&D Vorgang
    if (hCur != 0)
      SetCursor (hCur);                            // Cursor umsetzen
    else
      SetCursor (LoadCursor (NULL,IDC_ARROW));
    }
  return (hCur != 0);
  }

void DDOnOKButton (WORD Type, LPVOID dropData, HWND hWndEdit)
  {
  for (LPDRAGDROP h = firstdrop ; h != NULL ; h = h->Next)
    if (h->TestType (Type)) 
      if (h->TestWnd (hWndEdit)) {
        h->DoDrop (dropData, Type);
        break;
        }
  }

//--------------------------  RemoveAll  ------------------------------------
//
// entfernt alle Drag & Drop - Container die zu dem Fenster mit 
// der Handle  RefWnd gehoeren
//---------------------------------------------------------------------------
void RemoveAll (HWND RefWnd)
  {
  for (LPDRAGDROP h = firstdrop ; h != NULL ; ) {
    LPDRAGDROP n = h->Next ;
    if (h->TestRefWnd (RefWnd))
      h->RemoveFromList ();
//      delete h ;
    h = n;
    }
  }

HCURSOR Drag_Drop::GetHitCursor()
  {
  static HCURSOR cur;
  if (cur == 0) 
    cur = LoadCursor (MyInstance, "DODROP");
  return cur ;
  }

HCURSOR Drag_Drop::GetNonHitCursor()
  {
  static HCURSOR cur;
  if (cur == 0) 
    cur = LoadCursor (MyInstance, "NODROP");
  return cur ;
  }

void Bitmap_Drop::DoDrop (LPVOID data, WORD Type)
  {
  LPBDD d = LPBDD (data);
  SetWindowText (DropWnd,d->BitmapName);
  HWND hp = GetParent (DropWnd);

#ifdef WIN32
  WORD id = (WORD)GetWindowLong (DropWnd, GWL_ID);
#else
  WORD id = GetWindowWord (DropWnd, GWW_ID);
#endif

  char xtxt[16],ytxt[16];
  wsprintf (xtxt,"%d",d->x);
  wsprintf (ytxt,"%d",d->y);
  SetDlgItemText (hp,id+1,xtxt);
  SetDlgItemText (hp,id+2,ytxt);
  }

void Var_Drop::DoDrop (LPVOID data, WORD Type)
  {
  LPVDD d = LPVDD (data);
  char outtxt[128];
  wsprintf (outtxt,"%s.%s",d->TableName,d->VarName);
  SetWindowText (DropWnd,outtxt);
  }

void Tool_Drop::DoDrop (LPVOID data, WORD Type)
  {
  LPTOOLDD d = LPTOOLDD (data);
  if (d->ToolName != NULL) {
    ScreenToClient (DropWnd,&d->pts);
    InsertTool (d->ToolName,d->pts.x,d->pts.y);
    }
  else
    MessageBeep (0);
  }

//---------------------------  DoDrop  --------------------------------------
//
// ein einzeiliges Edit-Feld kann alle diese Typen empfangen
//---------------------------------------------------------------------------
void Text_Drop::DoDrop (LPVOID data, WORD Type)
  {
  switch (Type) {
    case DDTYPE_BITMAP:
      {
      LPBDD d = LPBDD (data);
      SetWindowText (DropWnd,d->BitmapName);
      HWND hp = GetParent (DropWnd);

#ifdef WIN32
      WORD id = (WORD)GetWindowLong (DropWnd,GWL_ID);
#else
      WORD id = GetWindowWord (DropWnd,GWW_ID);
#endif

      char xtxt[16],ytxt[16];
      wsprintf (xtxt,"%d",d->x);
      wsprintf (ytxt,"%d",d->y);
      SetDlgItemText (hp,id+1,xtxt);
      SetDlgItemText (hp,id+2,ytxt);
      }
      break;

    case DDTYPE_FORMAT:
      {
      LPFDD d = LPFDD(data);
      char outtxt[5];
      wsprintf (outtxt, "%d", d->FormatNr);
      SetWindowText (DropWnd, outtxt);
      }
      break;

    case DDTYPE_COLOR:
      {
      LPCLRDD d = LPCLRDD(data);
      char outtxt[50];
      wsprintf (outtxt, "[long(%lu)]", d->LineAttr);
      SetWindowText (DropWnd, outtxt);
      }
      break;

    default:
      SetWindowText (DropWnd,LPSTR(data));
    }
  
  SetFocus (DropWnd);
  }

void Format_Drop::DoDrop (LPVOID data, WORD Type)
  {
  LPFDD d = LPFDD(data);
  char outtxt[5];
  wsprintf (outtxt, "%d", d->FormatNr);
  SetWindowText (DropWnd, outtxt);
  }

void Color_Drop::DoDrop (LPVOID data, WORD Type)
  {
  LPCLRDD d = LPCLRDD(data);
  char outtxt[50];
  wsprintf (outtxt, "[long(%lu)]", d->LineAttr);
  SetWindowText (DropWnd, outtxt);
  }

//***************************************************
// Implementation von "Editor_Drop" in "WONSCRIP.CPP"
//***************************************************
HCURSOR Editor_Drop::GetHitCursor()
  {
  static HCURSOR cur;
  if (cur == 0)
    cur = LoadCursor (MyInstance, "COPYTEXT");
  return cur ;
  }

//***************************************************
// Implementation von "Table_Drop" in "RIWND.CPP"
//***************************************************

  
