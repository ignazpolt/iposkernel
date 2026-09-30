//--------------------------------------------------------------------------
// Andock-Fenster fuer Toolbar-Fenster
//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/toolbar/rev/tbdock.cpv   1.10   17 Nov 1997 08:13:38   Gerhold  $
//  $Log:   P:/marille/clinicum/toolbar/rev/tbdock.cpv  $
// 
//    Rev 1.10   17 Nov 1997 08:13:38   Gerhold
// 32 Bit
// 
//    Rev 1.9   21 Oct 1996 18:54:26   HANNES
// 
//    Rev 1.8   02 Feb 1996 10:51:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   10 Aug 1995 09:25:30   GERHOLD
// jetzt wird alles richtig freigegeben.
// 
//    Rev 1.6   07 Aug 1995 20:55:10   GERHOLD
// TBD_REMOVETOOLBAR
// 
//    Rev 1.5   21 Jul 1995 13:11:38   hannes
// 
//    Rev 1.4   24 Feb 1995 11:14:28   GERHOLD
// 
//    Rev 1.3   16 Feb 1995 12:44:28   GERHOLD
// 
//    Rev 1.2   24 Jan 1995 10:01:46   GERHOLD
// 
//    Rev 1.1   18 Jan 1995 12:13:48   GERHOLD
// 
//    Rev 1.0   02 Jan 1995 15:47:22   GERHOLD
// Initial revision.
//--------------------------------------------------------------------------
#include <windows.h>
#include <stdlib.h>

#define NO_MEMORY_CHECK    // kein GGlobalAlloc,...
#include "dds32.h"

#include "msdntb.h"
#include "msdntbi.hpp"


HFONT hFontControl = 0;

//char szDockName[] = "ToolbarDock";

class FAR TBDock {
 public:
  HWND      hMyWnd;
  LPTOOLBAR FirstToolBar;
  int       DockWndHeight;

  TBDock (HWND hWnd);
  ~TBDock ();

  void AddToolbar (LPTOOLBAR lptb);
  void RemoveToolbar (LPTOOLBAR lptb, BOOL DestroyChild);
  void ShowToolbar (LPTOOLBAR lptb, BOOL fShow);
  BOOL DockToolbar (LPTOOLBAR lptb);
  BOOL UnDockToolbar (LPTOOLBAR lptb);
  void ToolbarPositionChanged (WPARAM wParam, LPTOOLBAR lptb);
  void PaintToolbars (void);
  };
typedef TBDock FAR *LPTBDOCK;



static HFONT __hfnt;
static int fntUseCount;
static char szHelv[] = "ARIAL";
HFONT GetControlFont (int Fntheight)
  {
  if (__hfnt == 0) {
    __hfnt = CreateFont(Fntheight, 0, 0, 0, 700, 0, 0, 0,
          ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
          DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szHelv);
    }
  fntUseCount ++ ;
  return __hfnt;
  }

void DelControlFont ()
  {
  fntUseCount -- ;
  if (fntUseCount == 0) {
    if (__hfnt)
      DeleteObject (__hfnt);
    __hfnt = 0;
    }
  }


TBDock::TBDock (HWND hWnd)
  {
  FirstToolBar = NULL;
  DockWndHeight = 0;
  hMyWnd = hWnd;
  }

TBDock::~TBDock ()
  {
  for (LPTOOLBAR lptb = FirstToolBar; lptb != NULL; ) {
    LPTOOLBAR Next = lptb->Next ;
    RemoveToolbar (lptb, TRUE);
    lptb = Next ;
    }
  }

void TBDock::AddToolbar (LPTOOLBAR lptb)
  {
  if (FirstToolBar == NULL)
    FirstToolBar = lptb;
  else {
    for (LPTOOLBAR l = FirstToolBar; l->Next != NULL; l = l->Next);
    l->Next = lptb;
    }  
//  lptb->Next = FirstToolBar;
//  FirstToolBar = lptb;
  }

//---------------------  RemoveToolbar  -------------------------------------
//
// entfernt die Toolbar aus der Liste, und zerstoert sie wenn gewuenscht.
//---------------------------------------------------------------------------
void TBDock::RemoveToolbar (LPTOOLBAR lptb, BOOL bDestroyChild)
  {
  LPTOOLBAR prev = NULL;

  for (LPTOOLBAR l = FirstToolBar; l != NULL; l = l->Next) {
    if (lptb == l) {
      if (prev != NULL)             // war es bereits das erste Element?
        prev->Next = lptb->Next;    // nein -> Element ausklammern
      else
        FirstToolBar = lptb->Next;  // ja -> neues erstes Element

      if (bDestroyChild) {
        if (IsWindow(lptb->hWnd)) {
          lptb->hParent = 0;
          DestroyWindow (lptb->hWnd);
          }
        }

      break;
      }

    prev = l;
    }  
  }


//--------------------------  ShowToolbar  ----------------------------------
void TBDock::ShowToolbar (LPTOOLBAR lptb, BOOL fShow)
  {
  HWND hWndToShow = lptb->hWnd;

  if (lptb->ParentIsPopUp)
    hWndToShow = GetParent (hWndToShow);
  
  ShowWindow (hWndToShow, (fShow ? SW_SHOW : SW_HIDE));
      
  // Bei einer Toolbar im DockWindow muss das Hauptfenster benachrichtigt werden.
  // Es wird eine Dummy-Nachricht an das hwndFrame geschickt, welches wiederum 
  // alle seine Kindfenster ueber deren aktuelle Groesse  befragt!
  if (!lptb->ParentIsPopUp) {
    if ((lptb->rcChild.right - lptb->rcChild.left) == 0)
      lptb->SizeOnParent (hMyWnd, 0, 0, 0, 0);

    CopyRect (LPRECT(&lptb->rcMove), LPRECT(&lptb->rcChild));
    ClientToScreen (lptb->hParent, LPPOINT(&lptb->rcMove));
    ClientToScreen (lptb->hParent, LPPOINT(&lptb->rcMove.right));
  
    SendMessage (hMyWnd, TBD_POSCHANGED, FALSE, LONG(LPTOOLBAR(lptb)));
    }
  }
  
//--------------------------  DockToolbar  ----------------------------------
BOOL TBDock::DockToolbar (LPTOOLBAR lptb)
  {
  return FALSE;
  }


//----------------------  UnDockToolbar  ------------------------------------
BOOL TBDock::UnDockToolbar (LPTOOLBAR lptb)
  {
  return FALSE;
  }
  
//--------------------  ToolbarPositionChanged  -----------------------------
// 
// wird durch Verschieben eines Toolbars mit der linken Maustaste aufgerufen
//---------------------------------------------------------------------------
#define BORDER 3

#define STATE_NONE     0
#define STATE_MOVEDOWN 1
#define STATE_EXCHANGE 2
#define STATE_BENEATH  3
#define STATE_INSERT   4
#define STATE_DONE     5

#define STATE_FIRST_IN_ROW  6
#define STATE_LAST_IN_ROW   7
#define STATE_ANYWHERE      8
#define STATE_INSERT_AFTER_TOOLBAR  9
#define STATE_MOVE_IN_A_ROW        10

static BOOL bFrameSizeChanged;

int compare (const void *arg1, const void *arg2)
  {
  LPTOOLBAR a1 = *((LPTOOLBAR *) arg1);
  LPTOOLBAR a2 = *((LPTOOLBAR *) arg2);
  if (a1->rcChild.left < a2->rcChild.left)
    return (-1);
  else  
  if (a1->rcChild.left > a2->rcChild.left)
    return (1);
  else  
    return (0);
  }

int ArrangeFault(LPTOOLBAR FAR *la,int i,LPTOOLBAR lptb,LPRECT rcOld)
  {
  int fault = 0 ;
  for (int j = 0 ; j < i ; j ++) {
    LPRECT r;
    int fact;
    if (la[j] == lptb) {
      r = LPRECT(&lptb->rcMove) ;
      fact = 1;
      }
    else {
      r = &rcOld[j];
      fact = 2;
      }
    int dx = la[j]->rcChild.left - r->left ;
    int dy = la[j]->rcChild.top - r->top ;
    if (dx < 0) dx = -dx ;
    if (dy < 0) dy = -dy ;
    fault += fact * (dx + dy) ;
    }
  return fault ;
  }

void rcChildSave (LPTOOLBAR FAR *la,LPRECT rcOld,int i)
  {
  for (int j = 0 ; j < i ; j++) {
    rcOld[j] = *(LPRECT (&la[j]->rcChild)) ;
    }
  }
void rcChildRestore (LPTOOLBAR FAR *la,LPRECT rcOld,int i)
  {
  for (int j = 0 ; j < i ; j++) {
    *(LPRECT (&la[j]->rcChild)) = rcOld[j];
    }
  }
int Arrange (LPTOOLBAR FAR *la,int i,LPRECT rcmax) 
  {
  int xmax = rcmax->right - rcmax->left;
  int x = 0,y = 0,ymax = 0;
  for (int j = 0 ; j < i ; j++) {
    if ((x != 0) && (x + (la[j]->rcChild.right - la[j]->rcChild.left + 1) > xmax))
      x = 0 , y = ymax ;
    OffsetRect (LPRECT(&la[j]->rcChild),x - la[j]->rcChild.left,y - la[j]->rcChild.top);
    if (la[j]->rcChild.bottom >= ymax)
      ymax = la[j]->rcChild.bottom + 1;
    x = la[j]->rcChild.right + 1;
    }
  return ymax ;
  }
void Exchange (LPTOOLBAR FAR &l1,LPTOOLBAR FAR &l2)
  {
  LPTOOLBAR h = l2 ;
  l2 = l1 ;
  l1 = h ;
  }
void TBDock::ToolbarPositionChanged (WPARAM wParam, LPTOOLBAR lptb)
  {
  BOOL StateHasChanged = BOOL(wParam);  // von Popup in Child und umgekehrt
#ifdef UEBERLEGT

  if (lptb != NULL) {
    WORD State = STATE_NONE;
    LPTOOLBAR l = NULL;
    LPTOOLBAR MyNeighbour = NULL;
    RECT rcClient;
    
    GetClientRect (hMyWnd, &rcClient);

    ScreenToClient (hMyWnd, LPPOINT(&lptb->rcMove));
    ScreenToClient (hMyWnd, LPPOINT(&lptb->rcMove.right));

    int InsertAtY = rcClient.top;

    int ChildHeight = lptb->rcChild.bottom - lptb->rcChild.top;
    int ChildWidth = lptb->rcChild.right - lptb->rcChild.left;
    
    // zuerst suchen ob mehr als ein Toolbar in der selben Zeile war
    BOOL bMoreToolbarsInARow = FALSE;
    if (!lptb->ParentIsPopUp) {      // nur wenn das verschoben Fenster kein Popup war
      for (l = FirstToolBar; l != NULL; l = l->Next) {
        if ((l != lptb) && (IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
          if (l->rcChild.top == lptb->rcChild.top) {
            bMoreToolbarsInARow = TRUE;
            MyNeighbour = l;
            break;
            }
          }
        }
      }

    //------------------
    // Child -> Popup
    //------------------
    if (!lptb->ParentIsPopUp && StateHasChanged) {
      // es war kein weiterer Toolbar vorhanden =>
      // alle Toolbars die darunter lagen, werden nach oben geschoben!
      if (!bMoreToolbarsInARow) {
        for (l = FirstToolBar; l != NULL; l = l->Next)
          if ((l != lptb) && (IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp))
            if (l->rcChild.top > lptb->rcChild.top)
              OffsetRect (LPRECT(&l->rcChild), 0, -ChildHeight);
        }
      
      if (IsWindowVisible(lptb->hWnd))  
        lptb->ChangeState (FALSE);
      }
    //----------------------------------------------
    // Bewegen von Kindfenstern im Docking-Fenster
    //----------------------------------------------
    else if ((!lptb->ParentIsPopUp && !StateHasChanged) ||
             (lptb->ParentIsPopUp && StateHasChanged)) {
      // horizontale Bewegeung in einer Ebene
      if ((lptb->rcMove.top > (lptb->rcChild.top - BORDER)) &&
          (lptb->rcMove.top < (lptb->rcChild.top + BORDER)) && !lptb->ParentIsPopUp) {
        if (IsWindowVisible(lptb->hWnd))
          State = STATE_MOVE_IN_A_ROW;
        else
          State = STATE_ANYWHERE;  
        }
      else {
        for (l = FirstToolBar; l!= NULL; l = l->Next) {
          if ((l != lptb) && (IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {

              // Koordinaten innerhalb eines benachbarten Toolbars?
              if ((lptb->rcMove.top > (l->rcChild.top + BORDER)) &&
                  (lptb->rcMove.top < (l->rcChild.bottom - BORDER))) {
                if (bMoreToolbarsInARow) {
                  // bei mehr als einem Toolbar pro Zeile genuegt ein Verschieben des
                  // Toolbars um BORDER Einheiten zu einem anderen in dieser Zeile,
                  // um eine neue Ebene mit diesem einen Toolbar zu erzeugen.
                  State = STATE_MOVEDOWN;
                  break;
                  }
                else {  
                  // bin ich vielleicht schon an dieser Position??
                  if (lptb->rcChild.top != l->rcChild.bottom) {
                    State = STATE_EXCHANGE;  // nein!!
                    break;
                    }
                  }
                }
              else if ((lptb->rcMove.top >= (l->rcChild.top - BORDER)) &&
                       (lptb->rcMove.top <= (l->rcChild.top + BORDER))) {
                State = STATE_BENEATH;
                break;
                }
            }
          }  // for
        }

      if (lptb->ParentIsPopUp && StateHasChanged) {
        lptb->ChangeState (FALSE);
        bMoreToolbarsInARow = TRUE;
        }
      }
/*
    if (lptb->ParentIsPopUp && StateHasChanged)
      lptb->ChangeState (FALSE);
*/
/*
    //------------------
    // Popup -> Child 
    //------------------
    else if (lptb->ParentIsPopUp && StateHasChanged) {
      if (lptb->rcMove.top < rcClient.top) {  // wird an erster Stelle eingefuegt
        State = STATE_INSERT;
        }
      else {
        for (l = FirstToolBar; l!= NULL; l = l->Next) {
          if ((l != lptb) && (IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
            // Koordinaten innerhalb eines Toolbars?
            if ((lptb->rcMove.top > (l->rcChild.top + BORDER)) &&
                (lptb->rcMove.top < (l->rcChild.bottom - BORDER))) {
              State = STATE_INSERT;
              break;
              }
            else if ((lptb->rcMove.top >= (l->rcChild.top - BORDER)) &&
                     (lptb->rcMove.top <= (l->rcChild.top + BORDER))) {
              State = STATE_BENEATH;
              break;
              }
            }
          }  // for
        }  
        
      lptb->ChangeState (FALSE);
      }
*/

    int MaxX = 0;
    int MaxY = 0;
    switch (State) {
      case STATE_MOVE_IN_A_ROW:
      case STATE_ANYWHERE:
      case STATE_BENEATH:
        {
        int i;
        int Cnt = 0;
        static LPTOOLBAR lptbArray[10];

        for (i = 0; i < 10; lptbArray[i] = NULL, i++);

        InsertAtY = lptb->rcChild.bottom;

        // schon einmal die vorlaeufigen Koordinaten vergeben
        if (l != NULL)
          lptb->rcChild.top = l->rcChild.top;

        lptb->rcChild.bottom = lptb->rcChild.top + ChildHeight;

        lptb->rcChild.left = lptb->rcMove.left;
        lptb->rcChild.right = lptb->rcChild.left + ChildWidth;
      
        if (IsWindowVisible(lptb->hWnd)) {
          // Die Toolbars dieser Zeile in ein statisches Array
          for (l = FirstToolBar; l != NULL; l = l->Next) {
            if ((IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
              if (l->rcChild.top == lptb->rcChild.top) {
                lptbArray[Cnt++] = l;
                }
              }
            }
          
          // Sortieren der Toolbars nach ihrer linken Position
          qsort (lptbArray, Cnt, sizeof(LPTOOLBAR), compare);
  
          // nach dem Sortieren noch fuer Ordnung sorgen
          if (lptb->rcChild.left < 0) {
            lptb->rcChild.left = 0;
            lptb->rcChild.right = ChildWidth;
            }
  
          // der nachfolgende Toolbar haengt immer am vorhergehenden
          i = 0;
          l = lptbArray[i];
          for ( ; i < (Cnt-1); ) {
            if (lptbArray[i+1]->rcChild.left < l->rcChild.right) {
              OffsetRect (LPRECT(&lptbArray[i+1]->rcChild), 
                          l->rcChild.right - lptbArray[i+1]->rcChild.left, 0);
              }
            MaxX += (l->rcChild.right - l->rcChild.left);
            l = lptbArray[++i];
            }
  
          MaxX += (l->rcChild.right - l->rcChild.left);  // Laenge aller Toolbars
  
          int Delta = 0;
          // der letzte Toolbar ist zu weit rechts!
          if (l->rcChild.right > rcClient.right) {
            // Ist die Breite aller Toolbars kleiner als das Docking-Fenster?
            if (MaxX <= rcClient.right)
              // dann verschiebe einfach nach links
              Delta = rcClient.right - l->rcChild.right;
            else {
              // beginnt der erste Toolbar ganz links?
              if (lptbArray[0]->rcChild.left > 0)
                // nein dann verschiebe ihn ganz nach links
                Delta = -lptbArray[0]->rcChild.left;
              else {
                // wenn ein Toolbar nicht mehr sichtbar ist, muss er in die
                // naechste Zeile verschoben werden. Die Toolbars die unter
                // dieser Zeile waren, werden ebenfalls nach unten verschoben.
                BOOL bAlreadyMoved = FALSE;
                int cx, cy;
                int x = 0;
                for (i = 0 ; i < Cnt; i++) {
                  l = lptbArray[i];
                  if (l->rcChild.left > rcClient.right) {  // ueberhaupt noch sichtbar?
  
                    cx = l->rcChild.right - l->rcChild.left;
                    cy = l->rcChild.bottom - l->rcChild.top;
  
                    if (!bAlreadyMoved) {
                      int StartY = l->rcChild.bottom;
                      for (LPTOOLBAR lp = FirstToolBar; lp != NULL; lp = lp->Next) {
                        if ((IsWindowVisible(lp->hWnd)) && (!lp->ParentIsPopUp)) {
                          if (lp->rcChild.top >= StartY) {
                            bMoreToolbarsInARow = TRUE;
                            OffsetRect (LPRECT(&lp->rcChild), 0, cy);
                            }
                          }
                        }
                      bAlreadyMoved = TRUE;  
                      }  
                                                     
                    l->rcChild.left = x;
                    l->rcChild.top = l->rcChild.bottom;
                    l->rcChild.bottom = l->rcChild.top + cy;
                    l->rcChild.right = l->rcChild.left + cx;
                    
                    x += cx;                                 
                    }
                  }
                }  
              }  
            }

          if (Delta != 0) {
            i = 0;
            for ( ; i < Cnt; i++) {
              l = lptbArray[i];
              OffsetRect (LPRECT(&l->rcChild), Delta, 0);
              }
            }
          }
          
        // waren in der Zeile, in der vorher die Toolbar war, keine weiteren
        // Toolbars, so muessen die darunterliegenden nach oben geschoben werden
        if (State != STATE_MOVE_IN_A_ROW) {
          if (!bMoreToolbarsInARow) {
            for (l = FirstToolBar; l != NULL; l = l->Next) {
              if ((IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
                if (l->rcChild.top >= InsertAtY) {
                  OffsetRect (LPRECT(&l->rcChild), 0, -ChildHeight);
                  }
                }
              }
            }
          }  
        }
        break;
        
      case STATE_MOVEDOWN:
      case STATE_EXCHANGE:
      case STATE_INSERT:
        if (l != NULL)
          InsertAtY = l->rcChild.bottom;

        // alles was jetzt unter dem Kind liegt muss nach unten verschoben werden
        for (l = FirstToolBar; l != NULL; l = l->Next) {
          if ((l != lptb) && (IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
            if (l->rcChild.top >= InsertAtY) {
              OffsetRect (LPRECT(&l->rcChild), 0, ChildHeight);
              }
            if (l->rcChild.bottom > MaxY)  // wie weit bin ich schon unten?
              MaxY = l->rcChild.bottom;
            }
          }
          
        int StartY = lptb->rcChild.top;

        // dem verschoebenen Kind seine Koordinaten geben
        lptb->rcChild.left = lptb->rcMove.left;
        lptb->rcChild.right = lptb->rcChild.left + ChildWidth;
        lptb->rcChild.top = InsertAtY;
        lptb->rcChild.bottom = lptb->rcChild.top + ChildHeight;

        // Durch das Swappen wurden die Toolbars ueber den Rand des 
        // Docking-Fensters bewegt => wieder retour ab StartY
        if (State != STATE_INSERT) {
          if ((MaxY >= rcClient.bottom) && !bMoreToolbarsInARow) {
            for (l = FirstToolBar; l != NULL; l = l->Next) {
              if ((IsWindowVisible(l->hWnd)) && (!l->ParentIsPopUp)) {
                if (l->rcChild.top > StartY) {
                  OffsetRect (LPRECT(&l->rcChild), 0, -ChildHeight);
                  }
                }
              }
            }
          }
        
        break;  
      }
      
    HWND hParent = GetParent(hMyWnd);
    GetClientRect (hParent, &rcClient);
    SendMessage (hParent, WM_SIZE, 0, 
                 MAKELONG(rcClient.right-rcClient.left, rcClient.bottom-rcClient.top));
    }
#else
  if (lptb != NULL) {
    RECT rcClient;
    GetClientRect (hMyWnd, &rcClient);
    if (StateHasChanged) {
      if (IsWindowVisible(lptb->hWnd))  
        lptb->ChangeState (FALSE);
      }
    LPTOOLBAR la[32],laOld[32];
    RECT rcBest[32],rcOld[32];
    int i = 0,i1,i2;
    for (LPTOOLBAR l = FirstToolBar ; l != NULL ; l = l->Next) {
      if ((!l->ParentIsPopUp) && (IsWindowVisible(l->hWnd))) {
        la[i] = laOld[i] = l ;
        i ++ ;
        }
      }
    if (i == 1)
      Arrange (la,i,&rcClient) ;    // Da Gibts nicht viel zu tun
    else {
      rcChildSave (laOld,rcOld,i);
      int ymax = 32000 ;
      int maxFault = 32000 ;
      for (i1 = 0 ; i1 < i ; i1 ++) {
        // Durchprobieren alle Kombinationen und die beste Variante
        // rausfinden
        for (i2 = i1 + 1 ; i2 < i ; i2 ++) {
          int y = Arrange (la,i,&rcClient);
          if (y < ymax) {
            // Primaeres Kriterium: Moeglischt geringe Hoehe
            // -> Ermitteln eines Fehlers (fuer noetige Verschiebung)
            int fault = ArrangeFault (la,i,lptb,rcOld);
            if (fault < maxFault) {
              // Sekundaers Kriterium: Moeglichst geringe Verschiebung
              rcChildSave (laOld,rcBest,i);
              maxFault = fault;
              }
            y = ymax ;
            }
          Exchange (la[i1],la[i2]);
          // Zeiger austauschen und das Spielchen von neuem
          y = Arrange (la,i,&rcClient);
          if (y < ymax) {
            int fault = ArrangeFault (la,i,lptb,rcOld);
            if (fault < maxFault) {
              rcChildSave (laOld,rcBest,i);
              maxFault = fault;
              }
            y = ymax ;
            }
          }
        }
      // Fertig
      rcChildRestore (laOld,rcBest,i);
      }
      
    HWND hParent = GetParent(hMyWnd);
    GetClientRect (hParent, &rcClient);
    SendMessage (hParent, WM_SIZE, 0, 
                 MAKELONG(rcClient.right-rcClient.left, rcClient.bottom-rcClient.top));
    }
#endif
  }


void TBDock::PaintToolbars (void)
  {
  for (LPTOOLBAR l = FirstToolBar; l != NULL; l = l->Next)
    if (IsWindowVisible(l->hWnd) && (!l->ParentIsPopUp))
      InvalidateRect (l->hWnd, NULL, FALSE);
  }


//******************************************************************
 
//
//  FUNCTION   HandlePopupMenu (hwnd, point)
//
//  PURPOSE    Handles the display of the "floating" pop-up menu 
//             that appears on a mouse click in the application's
//             client area.
//
//******************************************************************
void WINAPI HandlePopupMenu (LPTBDOCK lptbDock, HWND hwnd, POINT point)
  {
  HMENU   hMenuTrackPopup;
  RECT    rcTrack;

  hMenuTrackPopup = CreatePopupMenu();
  
  if (!hMenuTrackPopup)
     return;

  int i = 0;
  for (LPTOOLBAR l = lptbDock->FirstToolBar; l != NULL; l = l->Next, i++) {
    UINT fuFlags = MF_ENABLED | MF_STRING;
    if (IsWindowVisible(l->hWnd))
      fuFlags |= MF_CHECKED;
      
    AppendMenu(hMenuTrackPopup, fuFlags, i, l->Title);
    }

  // Convert point to screen coordinates since that is
  // what TrackPopupMenu expects.
  ClientToScreen(hwnd, (LPPOINT)&point);
   
  // Create the tracking rectangle. If the mouse button is released
  // within the rectangle, the menu is not dismissed. point is 
  // already in screen coordinates, so no need to convert.
  rcTrack.top = point.y - 20;
  rcTrack.bottom = point.y + 20;
  rcTrack.left = point.x -20;
  rcTrack.right = point.x + 20;

  // Draw and track the "floating" pop-up menu.
  TrackPopupMenu(hMenuTrackPopup, TPM_LEFTBUTTON, point.x, point.y,
                 0, hwnd, (const RECT FAR *)&rcTrack);

  // Destroy the menu, because we are done with it.
  DestroyMenu(hMenuTrackPopup);
  }
 

static BOOL bSizeChanged = FALSE;

DLLExport LRESULT _export CALLBACK DockWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LRESULT res = 0;
  
  LPTBDOCK lpTBDock = (LPTBDOCK)GetWindowLong (hWnd, 0);

  switch (msg) {
    //-----------------------------------------------------------------------
    case WM_CREATE :
      {
      lpTBDock = new TBDock (hWnd);
      if (lpTBDock == NULL)
        return -1;

      int FntHeight = -11;
      HDC hDC = GetDC(NULL);
      if (hDC) {
        FntHeight = MulDiv(-8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
        ReleaseDC (NULL, hDC);
        }
      
      hFontControl = GetControlFont (FntHeight);
      
      SetWindowLong (hWnd, 0, LONG(lpTBDock));
      lpTBDock->DockWndHeight = LPCREATESTRUCT(lP)->cy;
      }
      break;

    //-----------------------------------------------------------------------
    case WM_SIZE :
      {
      RECT rcClient;
      static int cyDock = 0;

      if (!bSizeChanged) {
        cyDock = 0;
   
        GetClientRect (hWnd, &rcClient);
   
        for (LPTOOLBAR lptb = lpTBDock->FirstToolBar; lptb != NULL; lptb = lptb->Next)
          if ((!lptb->ParentIsPopUp) && (IsWindowVisible(lptb->hWnd))) {
            RECT rc;
   
            BOOL bInitializeChild = FALSE;
            if ((lptb->rcChild.right - lptb->rcChild.left) == 0) {
              lptb->SizeOnParent (hWnd, 0, 0, 0, 0);
              OffsetRect (LPRECT(&lptb->rcChild), 0, cyDock);
              bInitializeChild = TRUE;
              }
            
            CopyRect (&rc, LPRECT(&lptb->rcChild));

            if (rc.bottom > cyDock)
              cyDock = rc.bottom;
            // sagt dem Toolbar, wo er hingehoert (mit MoveWindow) !!!
            MoveWindow (lptb->hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, TRUE);
/*
            SetWindowPos (lptb->hWnd, 0, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                          SWP_NOZORDER);
*/
            }
   
        bSizeChanged = TRUE;
        SetWindowPos (hWnd, 0, rcClient.left, rcClient.top, LOWORD(lP), cyDock, SWP_NOZORDER);
//        UpdateWindow (hWnd);
        }

      bSizeChanged = FALSE;
      }  
      break;
        
    //-----------------------------------------------------------------------
    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      BeginPaint (hWnd, &ps);

      lpTBDock->PaintToolbars ();

      EndPaint (hWnd, &ps);
      }
      break;  

    case WM_RBUTTONDOWN:
      {
      POINT pt;
#ifdef WIN32
      LONG2POINT (lP, pt);
#else
      pt = MAKEPOINT(lP);
#endif

      HandlePopupMenu (lpTBDock, hWnd, pt);
      }
      break;
      
    //-----------------------------------------------------------------------
    case WM_DESTROY:  
      DelControlFont ();
      delete lpTBDock;
      break;

    case WM_COMMAND:
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      int i = 0;
      for (LPTOOLBAR l = lpTBDock->FirstToolBar; l != NULL; l = l->Next, i++) {
        if (UINT(i) == CRACKER_wID) {
          BOOL bVisible = IsWindowVisible(l->hWnd);
#ifdef WIN32
          SendMessage (hWnd, TB_SHOWTOOLBAR, !bVisible, (LPARAM)l->hWnd);
#else
          SendMessage (hWnd, TB_SHOWTOOLBAR, !bVisible, MAKELONG(l->hWnd, 0));
#endif
          break;
          }
        }
      break;
      }

    //-----------------------------------------------------------------------
    case TBD_ADDTOOLBAR:
      lpTBDock->AddToolbar (LPTOOLBAR(lP));
      break;

    //-----------------------------------------------------------------------
    case TBD_REMOVETOOLBAR:
      lpTBDock->RemoveToolbar (LPTOOLBAR(lP), FALSE);
      break;

    //-----------------------------------------------------------------------
    case TB_SHOWTOOLBAR:
      {
#ifdef WIN32
      HWND hToolbarWnd = HWND(lP);
#else
      HWND hToolbarWnd = HWND(LOWORD(lP));
#endif

      if (IsWindow(hToolbarWnd)) {
        BOOL bFound = FALSE;
        for (LPTOOLBAR lptb = lpTBDock->FirstToolBar; lptb != NULL; lptb = lptb->Next) {
          if (lptb->hWnd == hToolbarWnd) {
            bFound = TRUE;
            break;
            }
          }
      
        if (bFound)
          lpTBDock->ShowToolbar (lptb, BOOL(wP));
        }
      }
      break;

    //-----------------------------------------------------------------------
    case TBD_POSCHANGED:
      {
      LPTOOLBAR lptb = LPTOOLBAR(lP);
      lpTBDock->ToolbarPositionChanged (wP, lptb);
      }
      break;

    //-----------------------------------------------------------------------
    case TBD_GETCONTROLFONT:
#ifdef WIN32
      return (LPARAM)hFontControl;
#else
      return MAKELONG(hFontControl, 0);
#endif
      break;

    default:
      return DefWindowProc(hWnd, msg, wP, lP);
    }

  return res;
  }

  
DLLExport HWND _export WINAPI CreateToolbarDockWindow (HWND hWndParent)
  {
  return CreateWindow ("DOCKWINDOW", NULL, WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, 
                       0, 0, 0, 0, hWndParent, 0, hLibInst, NULL);
  }
  
  
