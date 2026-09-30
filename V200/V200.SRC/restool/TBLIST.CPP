///////////////////////////////////////////////////////////////////
//  Anzeige der Daten einer Tabelle
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/tblist.cpv   1.9   05 Oct 1998 11:28:12   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/tblist.cpv  $
// 
//    Rev 1.9   05 Oct 1998 11:28:12   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.8   05 Nov 1997 09:02:24   Gerhold
// 32 Bit
// 
//    Rev 1.7   28 Aug 1997 15:52:50   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   26 Nov 1996 08:09:42   HANNES
// Automatischer Update
// 
//    Rev 1.5   02 Feb 1996 10:50:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   02 Jan 1995 09:31:10   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.3   24 Aug 1994 19:45:46   HANNES
// Verkleinerung der angeforderten Datenmenge
// 
//    Rev 1.2   17 Jul 1994 14:47:20   HANNES
// 
//    Rev 1.1   04 Jul 1994 20:49:34   HANNES
// Abfrage, ob die Zugriff fuer View zugelassen ist
// 
//    Rev 1.0   24 Jun 1994 16:54:50   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "restool.hpp"
//#include "subclass.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 87
#include "winass.hpp"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "dbrecord.hpp"

extern HINSTANCE MyInstance;

struct FAR TableList {
  LPTABLEDEF tDef;
  LPSTR      AccessName;
  LPINT      ColumnNums;
  HWND       hParent;
  HWND       hWnd;
  LPINT      ColumnStart;
  TEXTMETRIC tm;
  HCURSOR    cmove;
  LPDLLENTRY ent;
  HWND       hScrollWnd ;
  DBList     FAR *list;
  LPDBRECORD FirstShown;
  LPDBRECORD LastShown;

  int xStart;
  int NrToSet;
  int xOld;
  int xMovement,xRange,xPos;
  int AnzShownLines;

  void GetColumnStart ();
  int  PrimKeyWidth();
  int  ColumnWidth(int i);
  int  AnzColumns()
    { return (GetBlockSize (ColumnNums) / sizeof(*ColumnNums)) ; }
  LPSTR ColumnName (int i)
    { return tDef->GetVarDef(ColumnNums[i])->GetName() ; }
  int Spacing ()
    { return tm.tmAveCharWidth / 2 ; }
  int YStart ()
    { return 1 + tm.tmHeight + tm.tmExternalLeading ; }
  int LineHeight ()
    { return 2 + tm.tmHeight + tm.tmExternalLeading ; }
  
  void DrawVertLines (HDC hDC);
  void DrawHeadLine (HDC hDC);
  BOOL CheckForMove (LONG pos,BOOL setXOld = FALSE);
  void MoveColumns (int x);
  void ShowMoveMent (int x);

  void ReadPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h);
  void WritePos ();
  void WriteSize ();

  void GetScrollRect (LPRECT r);
  void CreateScroll ();
  void MoveScroll ();
  void SetScrollers ();

  LPDBRECORD GetFirstLine ();
  LPDBRECORD GetNextLine (LPDBRECORD p);
  void Out (HDC hDC,int y,int x0,int x1,LPSTR txt);
  void PaintData (HDC hDC);
  LPRECT GetRectToScroll();
  void InvalidatePrimKeys();
  void ReduceSelection ();
  };
typedef TableList FAR *LPTABLELIST;
#define GWL_TABLELIST 0


extern LPSTR IniFile();

void TableList::GetScrollRect (LPRECT r)
  {
  RECT cr;
  GetClientRect (hWnd,&cr);
  r->left   = ColumnStart[0];
  r->right  = cr.right - r->left + 1;
  r->top    = cr.bottom - GetSystemMetrics(SM_CYHSCROLL) + 1;
  r->bottom = GetSystemMetrics(SM_CYHSCROLL);
  }

void TableList::CreateScroll ()
  {
  RECT r;
  GetScrollRect (&r);
  hScrollWnd = CreateWindow ("SCROLLBAR","",
          WS_CHILD | WS_VISIBLE | SBS_HORZ,
          r.left,r.top,r.right,r.bottom,
          hWnd,NULL,MyInstance,NULL);
  }

void TableList::MoveScroll ()
  {
  RECT r;
  GetScrollRect (&r);
  MoveWindow (hScrollWnd,r.left,r.top,r.right,r.bottom,TRUE);
  }

#define ANZRSCROLL  6     // Platz, um die hintere Spalte zu vergroessern
void TableList::SetScrollers ()
  {
  RECT cr;
  GetClientRect (hWnd,&cr);
  int cx = cr.right - ColumnStart[0];
  int sx = ColumnStart[AnzColumns()] - ColumnStart[0];
  if (sx + ANZRSCROLL * GetSystemMetrics (SM_CYCAPTION) < cx) {
    EnableScrollBar (hScrollWnd,SB_CTL,ESB_DISABLE_BOTH);
    xStart = xPos = xRange = 0;
    }
  else {
    xMovement = GetSystemMetrics (SM_CYCAPTION);
    xRange = (sx - cx) / xMovement + ANZRSCROLL;
    EnableScrollBar (hScrollWnd,SB_CTL,ESB_ENABLE_BOTH);
    SetScrollRange (hScrollWnd,SB_CTL,0,xRange,TRUE);
    if (xPos >= xRange) {
      xPos = xRange;
      SetScrollPos (hScrollWnd,SB_CTL,xPos,TRUE);
      xStart = xPos * xMovement;
      }
    }
  }

void TableList::ReadPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h)
  {
  *x = GetPrivateProfileInt (tDef->GetName(),"_X",100,IniFile());
  *y = GetPrivateProfileInt (tDef->GetName(),"_Y",100,IniFile());
  *w = GetPrivateProfileInt (tDef->GetName(),"_Width",500,IniFile());
  *h = GetPrivateProfileInt (tDef->GetName(),"_Height",300,IniFile());
  }

void TableList::WritePos ()
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (tDef->GetName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (tDef->GetName(),"_Y",outstring,IniFile());
  }

void TableList::WriteSize ()
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  int h = r.bottom - r.top  + 1;
  int w = r.right  - r.left + 1;
  char outstring[64];
  wsprintf (outstring,"%d",w);
  WritePrivateProfileString (tDef->GetName(),"_Width",outstring,IniFile());
  wsprintf (outstring,"%d",h);
  WritePrivateProfileString (tDef->GetName(),"_Height",outstring,IniFile());
  }

int TableList::PrimKeyWidth()
  {
  HDC hDC = GetDC (hWnd);
  GetTextMetrics (hDC,&tm);
  ReleaseDC (hWnd,hDC);
  int w = GetPrivateProfileInt (tDef->GetName(),"primkey",-1,IniFile());
  if (w < 0) {
    w = tm.tmAveCharWidth * 13 ;
    char outtxt[32];
    wsprintf (outtxt,"%d",w);
    WritePrivateProfileString (tDef->GetName(),"primkey",outtxt,IniFile());
    }
  return w;
  }

int TableList::ColumnWidth (int i)
  {
  int w = GetPrivateProfileInt (tDef->GetName(),ColumnName(i),-1,IniFile());
  if (w < 0) {
    w = tm.tmAveCharWidth * 10 ;
    char outtxt[32];
    wsprintf (outtxt,"%d",w);
    WritePrivateProfileString (tDef->GetName(),ColumnName(i),outtxt,IniFile());
    }
  return w;
  }

void TableList::GetColumnStart ()
  {
  ColumnStart = LPINT(GetGlobMem((AnzColumns() + 1) * sizeof(*ColumnStart)));
  for (int i = 0 ; i <= AnzColumns () ; i++)
    ColumnStart[i] = (i > 0) ? ColumnStart[i-1] + ColumnWidth(i-1) : PrimKeyWidth();
  }

void TableList::DrawVertLines (HDC hDC)
  {
  RECT r;
  GetClientRect (hWnd,&r);
  MoveToEx (hDC,ColumnStart[0],r.top, NULL);
  LineTo (hDC,ColumnStart[0],r.bottom);
  r.left = ColumnStart[0]+1;
  HRGN rgn = CreateRectRgn (r.left,r.top,r.right,r.bottom);
  SelectClipRgn (hDC,rgn);
  for (int i = 0 ; i <= AnzColumns() ; i++) {
    MoveToEx (hDC,ColumnStart[i] - xStart,r.top, NULL);
    LineTo (hDC,ColumnStart[i] - xStart,r.bottom);
    }
  SelectClipRgn (hDC,NULL);
  DeleteObject (rgn);
  }

void TableList::DrawHeadLine (HDC hDC)
  {
  RECT cr;
  GetClientRect (hWnd,&cr);
  cr.left = ColumnStart[0]+1;
  HRGN rgn = CreateRectRgn (cr.left,cr.top,cr.right,cr.bottom);
  SelectClipRgn (hDC,rgn);
  for (int i = 0 ; i < AnzColumns() ; i++) {
    RECT r;
    r.left   = ColumnStart[i  ] - xStart + Spacing() ;
    r.right  = ColumnStart[i+1] - xStart - Spacing() ;
    r.top    = 1 ;
    r.bottom = r.top + tm.tmHeight ;
    SetTextAlign (hDC,TA_TOP | TA_LEFT);
    ExtTextOut (hDC,r.left,r.top,ETO_CLIPPED,&r,ColumnName(i),lstrlen(ColumnName(i)),NULL);
    }
  SelectClipRgn (hDC,NULL);
  DeleteObject (rgn);
  // Zeichnen einer horizontalen Linie
  int y = 1 + tm.tmHeight + tm.tmExternalLeading ;
  MoveToEx (hDC,0,YStart(), NULL);
  LineTo (hDC,ColumnStart[AnzColumns()]-xStart,YStart());
  // Zeichnen einer Diagonallinie links oben
  MoveToEx (hDC,0,0, NULL);
  LineTo (hDC,ColumnStart[0],YStart());
  }

BOOL TableList::CheckForMove (LONG p,BOOL setXOld)
  {
  ScreenToClient (hWnd,LPPOINT(&p));
  int x = LOWORD(p);
  for (int i = 0 ; i <= AnzColumns() ; i++) {
    int dx = x - (ColumnStart[i] - xStart);
    if ((dx <= 3) && (dx >= -3)) { 
      if (setXOld) {
        NrToSet = i , xOld = ColumnStart[i] - xStart ; 
        SetCapture (hWnd);
        }
      return TRUE ;
      }
    }
  return FALSE ;
  }

void TableList::ShowMoveMent (int x)
  {
  HDC hDC = GetDC (hWnd);
  RECT r;

  GetClientRect (hWnd,&r);
  int oldrop = SetROP2 (hDC,R2_XORPEN);
  HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (WHITE_PEN));
  MoveToEx (hDC,xOld,0, NULL);
  LineTo (hDC,xOld,r.bottom);
  MoveToEx (hDC,x,0, NULL);
  LineTo (hDC,x,r.bottom);
  xOld = x;
  SelectObject (hDC,hOldPen);
  SetROP2 (hDC,oldrop);

  ReleaseDC (hWnd,hDC);
  }

void TableList::MoveColumns (int x)
  {
  int dx = x - (ColumnStart[NrToSet] - xStart);
  int wAct = (NrToSet > 0) ? ColumnStart[NrToSet] - ColumnStart[NrToSet-1] + dx : ColumnStart[0] + dx ;
  if (wAct < tm.tmAveCharWidth * 3) {
    wAct -= dx;   // so nicht
    MessageBeep (0);
    }
  else {
    char outtxt[64];
    wsprintf (outtxt,"%d",wAct);
    WritePrivateProfileString (tDef->GetName(),
                  (NrToSet > 0) ? ColumnName(NrToSet-1) : "primkey",
                          outtxt,IniFile()
                              );
    for (int i = NrToSet ; i <= AnzColumns() ; i++)
      ColumnStart[i] += dx;
    }
  if (NrToSet == 0)
    MoveScroll ();
  SetScrollers ();
  int xs;
  if (NrToSet == 0)
    xs = 0;
  else if (NrToSet == 1)
    xs = ColumnStart[0];
  else
    xs = ColumnStart[NrToSet-1] - xStart;
  if (x <= xs) xs = x - 1;
  RECT cr;
  GetClientRect (hWnd,&cr);
  cr.left = xs;
  InvalidateRect (hWnd,&cr,TRUE);
  }


struct TableWindow {
  TableWindow FAR *Next;
  HWND hWnd;
  };
static TableWindow FAR *TWList;
void AddWindow (HWND hWnd)
  {
  TableWindow FAR *n = (TableWindow FAR *)GetGlobMem (sizeof(*n));
  n->hWnd = hWnd;
  n->Next = TWList;
  TWList = n;
  }

void RemoveWindow (HWND hWnd)
  {
  TableWindow FAR *prev = NULL;
  for (TableWindow FAR *n = TWList ; n != NULL ; prev = n , n = n->Next) {
    if (n->hWnd == hWnd) {
      if (prev != NULL) prev->Next = n->Next;
      else              TWList = n->Next;
      FreeGlobMem (n);
      break ;
      }
    }
  WIN_ASSERT (n != NULL);
  }

LPDBRECORD TableList::GetFirstLine ()
  {
  LPDBRECORD rec = (FirstShown != NULL) ? FirstShown : list->GetFirstActive();
  if (rec == NULL) return list->GetFirst();
  return rec;
  }

LPDBRECORD TableList::GetNextLine (LPDBRECORD p)
  {
  return list->GetNext(p);
  }

void TableList::Out (HDC hDC,int y,int x0,int x1,LPSTR txt)
  {
  RECT r;
  r.left   = x0+1;
  r.right  = x1-1;
  r.top    = y+2;
  r.bottom = r.top + tm.tmHeight;
  SetTextAlign (hDC,TA_TOP | TA_LEFT);
  ExtTextOut (hDC,r.left,r.top,ETO_CLIPPED,&r,txt,lstrlen(txt),NULL);
  }

LPRECT TableList::GetRectToScroll()
  {
  static RECT r;
  GetClientRect (hWnd,&r);
  r.top = YStart ()+1;
  return &r;
  }

void TableList::InvalidatePrimKeys()
  {
  RECT r;
  GetClientRect (hWnd,&r);
  r.right = ColumnStart[0];
  InvalidateRect (hWnd,&r,TRUE);
  }

static char HexChar(char n)
  {
  if (n <= 9) return (n + '0');
  else        return (n - 10 + 'A');
  }

void ToHex (LPSTR res,LPSTR data,int size)
  {
  int j = 0;
  for (int i = 0 ; i < size ; i++) {
    res[j++] = HexChar((data[size - 1 - i] & 0xF0) >> 4);
    res[j++] = HexChar(data[size - 1 - i] & 0x0F);
    }
  res[j] = '\0';
  }

void TableList::PaintData (HDC hDC)
  {
  int y = YStart ();
  RECT r;
  // Berechnen des Clip - Bereiches
  GetClientRect (hWnd,&r);
  r.left = ColumnStart[0]+1;
  HRGN rgn = CreateRectRgn (r.left,r.top,r.right,r.bottom);
  GetScrollRect (&r);
  AnzShownLines = 0;
  for ( LPDBRECORD rec = FirstShown = GetFirstLine () ; rec != NULL ; rec = GetNextLine (rec)) {
    // Primaerschluessel
    LastShown = rec;
    char outtxt[256];
    ToHex (outtxt,LPSTR(rec->GetPrimKey()),GetBlockSize(rec->GetPrimKey()->Data));
    Out (hDC,y,0,ColumnStart[0],outtxt);

    // Daten der Reihe nach
    SelectClipRgn (hDC,rgn);
    for (int i = 0 ; i < AnzColumns() ; i++) {
      LPVARDEF v = tDef->GetVarDef(ColumnNums[i]);
      FormatOutTxt (outtxt,rec->Get(i+1),
              GetDLLAdmin()->GetDLLEntry(tDef->GetDLLHandle())->
                      DataDict_GetMType(v->GetDLLData()));
      Out (hDC,y,ColumnStart[i]-xStart+1,ColumnStart[i+1]-xStart,outtxt);
      }
    SelectClipRgn (hDC,NULL);

    y += LineHeight();
    // Noch die Linie
    MoveToEx (hDC,0,y, NULL);
    LineTo (hDC,ColumnStart[AnzColumns()]-xStart,y);
    AnzShownLines ++ ;
    if (y >= r.top) break ;
    }
  DeleteObject (rgn);
  }

void TableList::ReduceSelection ()
  {
  for (WORD i = 0 ; i < WORD(tDef->GetAnzVars()) ; i++) {
    LPVARDEF v = tDef->GetVarDef(i);
    if (v != NULL) {
      if (GetDLLAdmin()->GetDLLEntry(tDef->GetDLLHandle())->DataDict_IsPrimary
              (v->GetDLLData())) {
        list->AddElemsToGet (&i,1);
        break ; 
        }
      }
    }
   
  list->AddElemsToGet (LPWORD(ColumnNums),AnzColumns());
  }

DLLExport LONG _export FAR PASCAL TableProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  LONG RetVal = 0L;
  LPTABLELIST tl;
  switch (msg) {
    case WM_CREATE :
      tl = LPTABLELIST (((LPCREATESTRUCT)(lP))->lpCreateParams);
      SetWindowLong (hWnd,GWL_TABLELIST,LONG (tl));
      tl->hWnd  = hWnd;
      tl->ent   = GetDLLAdmin()->GetDLLEntry(tl->tDef->GetDLLHandle());
      tl->cmove = LoadCursor (MyInstance,"CMOVE");
      tl->xOld  = -1;

      // Berechnen der Spaltenpositionen
      tl->GetColumnStart ();
      // Erzeugen des Scrollbalkens
      tl->hWnd = hWnd;
      tl->CreateScroll ();
      tl->SetScrollers ();
      AddWindow (hWnd);

      // Und los gehts
      tl->list = new DBList (tl->tDef,DWORD(hWnd),tl->AccessName,10,100);
      tl->ReduceSelection ();
      break ;

    case WM_MOVE :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      tl->WritePos ();
      break ;

    case WM_SIZE :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      tl->WriteSize ();
      tl->MoveScroll ();
      tl->SetScrollers ();
      break ;

    case WM_HSCROLL :
      {
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      int xPosOld = tl->xPos;
      switch (wP) {
        case SB_BOTTOM    :
          tl->xPos = tl->xRange;
          break ;
        case SB_TOP       :
          tl->xPos = 0;
          break ;
        case SB_LINEUP    :
          tl->xPos = max(0,tl->xPos - 1);
          break ;
        case SB_LINEDOWN  :
          tl->xPos = min(tl->xRange,tl->xPos + 1);
          break ;
        case SB_PAGEUP    :
          tl->xPos = max(0,tl->xPos - 5);
          break ;
        case SB_PAGEDOWN  :
          tl->xPos = min(tl->xRange,tl->xPos + 5);
          break ;
        case SB_THUMBPOSITION :
          tl->xPos = LOWORD(lP);
          break ;
        }
      if (xPosOld != tl->xPos) {
        SetScrollPos (tl->hScrollWnd,SB_CTL,tl->xPos,TRUE);
        tl->xStart = tl->xPos * tl->xMovement;
        InvalidateRect (hWnd,NULL,TRUE);
        }
      }
      break ;

    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      HDC hDC = BeginPaint (hWnd, &ps) ;
      tl->DrawVertLines (hDC);
      tl->DrawHeadLine (hDC);
      tl->PaintData (hDC);
	    EndPaint (hWnd, &ps) ;
      }
      break ;

    case WM_SETCURSOR :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      if ((LOWORD(lP) == HTCLIENT) &&
            ((tl->xOld >= 0) || (tl->CheckForMove (GetMessagePos()))))
        SetCursor (tl->cmove) , RetVal = TRUE ;
      else
        RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;

    case WM_LBUTTONDOWN :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      tl->CheckForMove (GetMessagePos(),TRUE);
      break ;

    case WM_MOUSEMOVE :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      if (tl->xOld >= 0)
        tl->ShowMoveMent (LOWORD(lP));
      break ;

    case WM_LBUTTONUP :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      if (tl->xOld >= 0) {
        tl->ShowMoveMent (LOWORD(lP));
        tl->MoveColumns (LOWORD(lP));
        tl->xOld = -1;
        ReleaseCapture ();
        }
      break ;

    case WM_CLOSE :
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      BringWindowToTop (tl->hParent);
      DestroyWindow (hWnd);
      break ;

    case WM_DESTROY :
      RemoveWindow (hWnd);
      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));
      FreeGlobMem (tl->AccessName);
      FreeGlobMem (tl->ColumnNums);
      delete tl->list;
      GetTableAdmin()->FreeTable (tl->tDef->GetTableID(),tl->tDef->GetVersion());
      FreeGlobMem (tl->ColumnStart);
      DestroyCursor (tl->cmove);
      FreeGlobMem (tl);
      break ;

    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      tl = LPTABLELIST (GetWindowLong (hWnd,GWL_TABLELIST));

      switch (CRACKER_wID) {
        case MI_LINEDOWN :
          if (tl->list->IsMoreOnTail()) {
            LPDBRECORD h = tl->list->GetNext (tl->FirstShown);
            tl->list->ThrowRecord(tl->FirstShown);
            tl->FirstShown = h;
            ScrollWindow (hWnd,0,-tl->LineHeight(),tl->GetRectToScroll(),tl->GetRectToScroll());
            tl->InvalidatePrimKeys();
            UpdateWindow (hWnd);
            }
          break ;
        case MI_LINEUP   :
          if (tl->list->IsMoreOnHead()) {
            tl->FirstShown = tl->list->GetPrev(tl->FirstShown);
            tl->list->ThrowRecord(tl->LastShown);
            ScrollWindow (hWnd,0,tl->LineHeight(),tl->GetRectToScroll(),tl->GetRectToScroll());
            tl->InvalidatePrimKeys();
            UpdateWindow (hWnd);
            }
          break ;
        case MI_PAGEDOWN :
          if (tl->list->IsMoreOnTail()) {
            tl->list->ThrowAtHead(tl->LastShown) ;
            tl->FirstShown = NULL;
            ScrollWindow (hWnd,0,- tl->LineHeight() * (tl->AnzShownLines - 1),tl->GetRectToScroll(),tl->GetRectToScroll());
            tl->InvalidatePrimKeys();
            UpdateWindow (hWnd);
            }
          break ;
        case MI_PAGEUP   :
          if (tl->list->IsMoreOnHead()) {
            LPDBRECORD h = tl->FirstShown;
            for ( int i = 0 ; ((i < tl->AnzShownLines - 1) && (h != NULL)) ; i++ ) 
              h = tl->list->GetPrev(h);
            tl->list->ThrowAtTail(tl->FirstShown) ;
            tl->FirstShown = h;
            ScrollWindow (hWnd,0,tl->LineHeight() * (tl->AnzShownLines - 1),tl->GetRectToScroll(),tl->GetRectToScroll());
            tl->InvalidatePrimKeys();
            UpdateWindow (hWnd);
            }
          break ;
        case MI_HOME     :
          tl->list->ThrowList ();
          tl->FirstShown = NULL;
          InvalidateRect (hWnd,NULL,TRUE);
          break ;
        case MI_END      :
          tl->list->ThrowList();
          tl->FirstShown = NULL;
          tl->list->GetLast();
          for (int i = 0 ; i < tl->AnzShownLines - 1; i++)
            tl->list->GetPrev(tl->list->GetFirstActive());
          InvalidateRect (hWnd,NULL,TRUE);
          break ;
        }
      }
      break ;

    case WM_KEYDOWN :
      switch (wP) {
        case VK_UP    :
          PostMessage (hWnd,WM_COMMAND,MI_LINEUP,0L);
          break ;
        case VK_DOWN  :
          PostMessage (hWnd,WM_COMMAND,MI_LINEDOWN,0L);
          break ;
        case VK_PRIOR :
          PostMessage (hWnd,WM_COMMAND,MI_PAGEUP,0L);
          break ;
        case VK_NEXT  :
          PostMessage (hWnd,WM_COMMAND,MI_PAGEDOWN,0L);
          break ;
        case VK_HOME :
          PostMessage (hWnd,WM_COMMAND,MI_HOME,0L);
          break ;
        case VK_END :
          PostMessage (hWnd,WM_COMMAND,MI_END,0L);
          break ;
        default :
          RetVal = DefWindowProc (hWnd,msg,wP,lP);
        }
      break ;

    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
      break ;
    }
  return RetVal;
  }

void RegisterTableWindow ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = TableProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = sizeof(LPTABLELIST) ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = "TBMENU" ;
    wndclass.lpszClassName = "TBLIST" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

void DestroyAllTableLists ()
  {
  for ( ; TWList != NULL ; )
    DestroyWindow (TWList->hWnd);
  }

void ShowTable (LPTABLEDEF tdef,HWND hParent,LPSTR AccessName,LPINT ColumnNums)
  {
  if (tdef->IsViewAllowed (AccessName)) {
    RegisterTableWindow ();

    HMENU hMenu = LoadMenu(MyInstance,"TBMENU");

    LPTABLELIST tl = LPTABLELIST (GetGlobMem (sizeof(*tl)));
    tl->tDef       = tdef;
    tl->AccessName = LPSTR(GetGlobMem(lstrlen(AccessName)+1)) ;
    lstrcpy (tl->AccessName,AccessName);
    tl->ColumnNums = ColumnNums;
    tl->hParent    = hParent;
    int x,y,w,h;
    tl->ReadPos (&x,&y,&w,&h);

    char caption[256];
    wsprintf (caption,"View %s with %s",tdef->GetName(),AccessName);
    HWND hTableWindow = CreateWindow (
                                      "TBLIST",                
	                                    caption,
                                      WS_POPUPWINDOW | WS_CAPTION | 
                                      WS_THICKFRAME | WS_CLIPCHILDREN,
                                      x,y,w,h,
                                      hParent,
                                      hMenu,                   
                                      MyInstance,              
            	                        tl
                                    ) ;
    ShowWindow (hTableWindow,SW_NORMAL);
    UpdateWindow (hTableWindow) ;
    }
  else {
    char outtxt[128];
    wsprintf (outtxt,"Zugriff %s nicht für die Testansicht erlaubt",AccessName);
    MessageBox (GetActiveWindow(),outtxt,"Fehler",MB_OK | MB_ICONEXCLAMATION);
    GetTableAdmin()->FreeTable (tdef->GetTableID(),tdef->GetVersion());
    }
  }

