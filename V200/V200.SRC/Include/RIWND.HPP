/*
**  gr. Darstellung der RI zwischen verschiedenen Tabellen
*/
//
//  $Header:   P:/marille/clinicum/include/rev/riwnd.hpv   1.3   28 Aug 1997 15:54:00   gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/riwnd.hpv  $
// 
//    Rev 1.3   28 Aug 1997 15:54:00   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.2   02 Feb 1996 11:00:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   26 Apr 1995 15:31:42   HANNES
// 
//    Rev 1.0   16 Feb 1995 12:43:30   HANNES
// Initial revision.
//

#ifndef RC_INVOKED
#define ELEMTYPE_NONE  0
#define ELEMTYPE_LINE  1
#define ELEMTYPE_TABLE 2

class FAR riShow;
class FAR riElem {
 public :
  riElem FAR *Next;
  riShow FAR *Parent;
  int State;
  int xm0,ym0;

  riElem (riShow FAR *);
  virtual ~riElem ();

  virtual void Paint (PaintContext *pc,BOOL IsSelected,BOOL forPrinter = FALSE);
  virtual void InitializeVOrg();
  virtual void Invalidate (BOOL doErase);
  virtual void InvalidateFull ()
    { }
  virtual BOOL HitTest (int x,int y);
  virtual void OnLButtonUp (int x,int y);
  virtual void OnMouseMove (int x,int y);
  virtual int  ElemType()
    { return ELEMTYPE_NONE ; }
  virtual void OnDblClk ()
    { }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

class FAR riTable;
struct FAR StartEndPos {
  int Side;
  int RPos;
  BOOL operator == (StartEndPos FAR & cmppos)
    { return ((Side == cmppos.Side) && (RPos == cmppos.RPos)) ; }
  };
typedef StartEndPos FAR *LPSEP;
class FAR riLine : public riElem {
 public :
  LPPOINT pt;
  int AnzPts ()
    { return GetBlockSize(pt) / sizeof(*pt) ; }
  riTable FAR *Table1,FAR *Table2;
  StartEndPos pstart,pend;
  LPVOID fk; 

  riLine (riTable FAR *t1,riTable FAR *t2,LPVOID fk);
  ~riLine ();
  void BuildLine ();
  void SetLine (LPPOINT p1,LPPOINT p2);
  void SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3);
  void SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3,LPPOINT p4);
  void SetLine (LPPOINT p1,LPPOINT p2,LPPOINT p3,LPPOINT p4,LPPOINT p5);
  void FreeStartKnots ();
  LONG SearchBestWay ();

  virtual void Invalidate (BOOL doErase);
  virtual void Paint (PaintContext *pc,BOOL IsSelected,BOOL forPrinter = FALSE);
  virtual int  ElemType()
    { return ELEMTYPE_LINE ; }
  };
typedef riLine FAR *LPRILINE;

#define MSTATE_RIGHT     1
#define MSTATE_BOTTOM    2
#define MSTATE_MOVE      3
class FAR riTable : public riElem {
 public :
  LPTABLEDEF td;
  cField FAR *field;
  POINT p0,p1;
  int minw,minh;
  LPRILINE FAR *lines;
  LPSTR TableName;

  riTable (LPSTR Name,riShow FAR *p,int x,int y,int w = -1,int h = -1);

  virtual ~riTable ();
  virtual BOOL HitTest (int x,int y);
  virtual void OnLButtonUp (int x,int y);
  virtual void OnMouseMove (int x,int y);
  int LineHeight();

  BOOL GetFirstPos(LPSEP p);
  BOOL GetNextPos(LPSEP p);
  BOOL GetFirstPos(LPSEP p,LPSEP n,riLine FAR *l);
  BOOL GetNextPos(LPSEP p,LPSEP n,riLine FAR *l);
  int  MaxRPos (int Side);
  int  MidFault (LPSEP p);
  BOOL IsPosFree (LPSEP p,LPSEP e,riLine FAR *l);
  int  GetAnzLines() 
    { return GetBlockSize(lines) / sizeof(*lines) ; } 
  void PushLine (riLine FAR *l);
  void RemoveLine (riLine FAR *l);
  void GetXY (LPSEP p,LPPOINT pt);
  void GetStartPoint (int Side,LPPOINT pt);
  void GetSideVect (int Side,LPPOINT v);
  void GetOutVect (int Side,LPPOINT v);
  void FreeTableDef ();

  virtual void  InitializeVOrg();
  virtual void  Invalidate (BOOL doErase);
  virtual void  InvalidateFull ();
  virtual void  Paint (PaintContext *pc,BOOL IsSelected,BOOL forPrinter = FALSE);
  virtual void  OnDblClk ();
  virtual int   ElemType()
    { return ELEMTYPE_TABLE ; }
  virtual void SetFldPos ();

  virtual DWORD TableColor ();
  virtual void CheckRI(riTable FAR *x);
  };
typedef riTable FAR *LPRITABLE;

class FAR jTable : public riTable {
 public :
  int TableNum ;
  jTable (int num,LPSTR Name,riShow FAR *p,int x,int y,int w = -1,int h = -1)
    : riTable (Name,p,x,y,w,h)
    { TableNum = num ; }
  void UpdateName ();
  virtual DWORD TableColor ();
  virtual void SetFldPos ();
  virtual void CheckRI(riTable FAR *x);

  int GetTableNum()
    { return TableNum ; }
  };

class FAR riShow {
 public :
  riShow FAR *Next;
  LPSTR FileName;
  HWND hWnd;
  int xv,yv;
  riElem FAR *elem,FAR *ActiveElem;
  BOOL ChangeDone;

  void Register ();
  void Create (HWND hWnd);
  void Load ();
  void Store ();
  void Show ();
  void Hide ();
  void DoSetScrolls();
  void InitializeVOrg ();
  void OnVScroll(WPARAM wP,LPARAM lP);
  void OnHScroll(WPARAM wP,LPARAM lP);
  void ToLog (int FAR *x,int FAR *y);

#ifdef WIN32
  void ToPhys (long FAR *x,long FAR *y);
#else
  void ToPhys (int FAR *x,int FAR *y);
#endif

  int  SnapW (int x,int fact = 1);
  int  SnapH (int y,int fact = 1);
  void Snap (LPPOINT pt);
  void OnLButtonDown (LPARAM lP);
  void OnLButtonUp (LPARAM lP);
  void OnMouseMove (LPARAM lP);
  void OnDblClk ();
  void Print ();

  Table_Drop FAR *td;
  BOOL LineReferenced (LPVOID k);
  void CheckRI();
  void DelLineDefs();
  void FreeTableDefs (LPSTR Name);
  void UpdateTableDef (LPSTR Name);

  void PaintGrid(PaintContext *pc);
  void Paint (PaintContext *pc);
  int  GetTableCount();

  riShow (LPSTR name);
  ~riShow ();

  virtual LONG OnClose ();
  virtual void NewTable (LPSTR TableName);
  virtual void NewTable (LPSTR TableName,int x,int y,int w,int h);
  virtual void DelElem ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef riShow FAR *LPRISHOW;

class FAR jShow : public riShow {
 public :
  LPVOID extra;
  jShow (LPVOID x) : riShow ("")
    {
    extra = x ;
    }
  virtual void NewTable (LPSTR TableName);
  virtual void NewTable (LPSTR TableName,int x,int y,int w,int h);
  virtual void DelElem ();
  virtual LONG OnClose ();
  LPSTR GetTableName (int nr);
  };

#endif

// Konstanten fuer den Compiler
#define LDCMPL_BASE     31000
#define LDKWBRACEOPEN   0
#define LDKWBRACECLOSE  1
#define LDKWCOLON       2
#define LDKWEND         3

