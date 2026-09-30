///////////////////////////////////////////////////////////////////
//  Hilfslinien
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/hlines.hpv   1.2   02 Feb 1996 11:00:00   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/hlines.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:00:00   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   27 Aug 1995 13:00:50   HANNES
// 
//    Rev 1.0   12 Jul 1994 14:45:50   HANNES
// Initial revision.
//


#define HLINE_HORZ      0
#define HLINE_VERT      1
struct FAR HilfsLinie {
  HilfsLinie FAR *Next;
  int Type;
  int lval;

  BOOL Snap (LPPOINT pt,LPPOINT ptsnap = NULL,int xoffs = 0,int yoffs = 0);
  int Abst (LPPOINT pt,LPPOINT ptsnap);
  int IsBetterHLine (LPPOINT pt,LPPOINT ptsnap,int FAR *dh,int FAR *dv);
  int IsBetterVLine (LPPOINT pt,LPPOINT ptsnap,int FAR *dh,int FAR *dv);
  void SetMoveCursor ();
  };
typedef HilfsLinie FAR *LPHILFSLINIE;

#define HLINECOLOR  (RGB(0xFF,0,0))
#define HXLINECOLOR ((~HLINECOLOR) & 0x00FFFFFF)
#define HLINETIMER  1001
int GetHLKoord (int Type,int val);
int GetHDKoord (int Type,int val);
void PaintHLine (PaintContext *pc,int type,int lval);
void MoveHLine (int x,int y);
void InsertHLine (int x,int y);
void InitializeHMove ();
void PaintHLines (HDC hDC);
void DestroyHLines ();
BOOL CheckCursorForHLines (int x,int y);
BOOL HLine_OnLButtonDown (int x,int y);
void HLine_Timer ();
BOOL HLine_OnLButtonUp (int x,int y);
BOOL HLine_OnMouseMove (int x,int y);
void DeleteHLine ();
void WorkOnHLine ();
void SetMultiHLine ();
BOOL AnalyseForHLine (LPLINE l);
BOOL IsHLine (LPLINE l);
void DelDefLines ();
LPLINE GetHDefLine ();
BOOL HLineAllowed ();
LONG CheckHLineMSG (HWND hWnd,unsigned msg,WORD wP,LONG lP,BOOL FAR *done);
HWND GetHLineWnd();
void ClearHLines ();
BOOL TryToSnap (int FAR *xn,int FAR *yn,int XOffs,int YOffs);
BOOL IsHLineMoveing();
void ResetHLineCursor ();

