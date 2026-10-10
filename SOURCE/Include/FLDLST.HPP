/*-----< Definition der Tabelleneingabe >-------------*/
//
// $Header:   P:/marille/clinicum/include/rev/fldlst.hpv   1.6   26 Nov 1996 08:11:48   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/fldlst.hpv  $
// 
//    Rev 1.6   26 Nov 1996 08:11:48   HANNES
// Automatischer Update
// 
//    Rev 1.5   02 Feb 1996 11:00:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   23 May 1995 12:05:04   GERHOLD
// SearchStringInList
// 
//    Rev 1.3   26 Apr 1995 15:31:40   HANNES
// 
//    Rev 1.2   16 Feb 1995 12:34:38   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.1   29 Jan 1995 11:49:30   HANNES
// 
//    Rev 1.0   24 Jan 1995 11:00:12   HANNES
// Initial revision.
//
typedef cField FAR *LPFIELD;
class FAR FldList;
class FAR FldLine;
typedef FldLine FAR *LPFLDLINE;
typedef FldList FAR *LPFLDLIST;

#define GWL_FLDLIST   0
/*---< Klasse FldLine: Verwaltung von mehreren cFields zur Darstellung 
                       und Eingabe >------*/
struct FieldCallBack {
  int column;
  LPFLDLINE line;
  LPFLDLIST list;
  };
typedef FieldCallBack FAR *LPFIELDCALLBACK;
class FAR FldList;
class FAR FldLine {
 public :
  LPFLDLINE Next;
  WORD LineID;
  LPFIELD FAR *cList;
  FldList FAR *Parent;
  int yv;

  FldLine (int AnzFlds,WORD lId,FldList FAR *lst);
  ~FldLine ();

  int AnzFields()
    { return (GetBlockSize(cList) / sizeof(*cList)); }
  LPFIELD GetField(int i)
    { return cList[i] ; }

  void Paint(HDC hDC,BOOL Select);
  void SetOrg(int x,int y);
  void ToLog (POINT FAR *pt,DWORD pos,BOOL IsScreen);
  void SetField(LPFIELD f,int Column)
    { cList[Column] = f ; }
  void SetYV (int y);
  void SetFldPos (int Column,int x);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

struct FAR FldName {
  FldName FAR *Next;
  LPSTR Name;
  };

class FAR FldCheck {
 private:
  FldName FAR *List;
 public :
  BOOL CheckName (LPSTR Name);
  BOOL FieldExist (LPSTR Name);

  ~FldCheck ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

class FAR FldList {
 public :
  int         xv,yv;
  HWND        hWnd;
  LPVOID      BaseContext;
  LPFLDLINE   FirstLine,ActiveLine,HdLine,LastLine;
  int         ActiveCol;
  LPSTR       Caption;
  int FAR *   ColWidth;
  HCURSOR     cmove;
  HPEN        hActivePen,hInactivePen;
  int         WState,ActVLine;
  LPSTR       ActFldName;
  int         DownColumn;
  int         lHeight;

  FldList FAR *Next;
  VarList_Drop FAR *vdrop ;

  virtual void DoDrop (int x,int y,LPVOID data,WORD Type)
    {
    }
  cField FAR *GetFieldFromPos (int FAR *Column,LPFLDLINE FAR *l,int x,int y);
  FldList (LPVOID Cntx,LPSTR Caption);
  ~FldList ();

  int         LineHeight ();
  cField FAR *GetField (HWND hWnd,int x,int w,int Format,LPSTR Text,LPFIELDCALLBACK cbmem,DWORD mode);
  int         AddLine (LPVOID Context,int y,BOOL SetScrolls,WORD LId);
  void        SetNewFldPos();
  void        BuildLastLine (int y);
  int         BuildHdLine ();
  void        BuildList();
  int         FldLines();
  int         LinesToShow();
  void        SetProfInt (LPSTR Name,int val);
  int         GetProfInt (LPSTR Name,int def);
  int         GesWidth();
  void        DoSetScrolls();
  void        GetPos (int FAR *x,int FAR *y,int FAR *w,int FAR *h);
  void        WriteColWidth();
  void        WritePos();
  void        Invalidate (LPFLDLINE h,LPRECT r,BOOL doErase);
  void        InvalidateArrow (LPFLDLINE h);
  void        ToLog (POINT FAR *pt,DWORD pos,BOOL IsScreen);

  void        Register();
  void        Create(HWND hWnd);
  void        Show();
  void        Hide();
  void        Paint (PaintContext *pc);
  void        EraseBkGnd(HDC hDC);

  void        OnVScroll(WPARAM wP,LPARAM lP);
  void        OnHScroll(WPARAM wP,LPARAM lP);
  BOOL        CheckVGrid(LPPOINT pt,LONG FAR *res);
  LONG        OnSetCursor(WPARAM wP,LPARAM lP);
  void        DrawVLine (PaintContext *pc,int x);
  LONG        OnLButtonDown (WPARAM wP,LPARAM lP);
  LONG        OnLButtonUp (WPARAM wP,LPARAM lP);
  LONG        MouseMove (WPARAM wP,LPARAM lP);
  void        OnKillFocus ();
  void        OnSetFocus ();
  void        OnChar (WPARAM wP);
  void        OnKeyDown (WPARAM wP);
  void        PrevField ();
  void        NextField ();
  void        NextLine ();
  void        PrevLine ();
  LPFLDLINE   GetNextLine (LPFLDLINE h);
  LPFLDLINE   GetPrevLine (LPFLDLINE h);
  LPFLDLINE   GetLastLine();
  void        NeedScroll (int dx,int dy);
  void        ShowList (LPSTR Info,LPFLDLINE line,int column);
  LPFLDLINE   Enlarge (LPFLDLINE LineBefore);
  LPFLDLINE   RemoveLine (LPFLDLINE Line);
  LPFLDLINE   SearchField (DWORD lP,int FAR *Col);
  void        GetActFldName();
  void        DelActFldName();
  void        ModifyContent (LPFLDLINE line,int column,LPSTR str);

  BOOL GetFieldContent (LPSTR res,LPFLDLINE h,int Column);
  BOOL GetFieldSent (LPSTR res,LPFLDLINE h,int Column);
  BOOL GetFieldRes (LPSTR res,LPFLDLINE h,int Column,BOOL mustExist);
  BOOL GetFieldWord (LPSTR res,LPFLDLINE h,int Column,BOOL mustExist);
  void Fehler (LPSTR String);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }

  virtual void  Save (LPFLDLINE line,int column);
  virtual int   AnzColumns();
  virtual DWORD GetColMode(int Column);
  virtual int   GetX0();
  virtual int   GetFormat();
  virtual LPSTR GetHdString (int Column);
  virtual LPSTR GetFieldString (LPVOID Context,int Column);
  virtual BOOL  EnableNewContext();
  virtual void  OnDestroy();
  virtual LPSTR GetResource (int Column);
  virtual BOOL  EnableInput ();
  virtual int   GetColWidth(int Column);
  virtual void  OnDblClk(LPFLDLINE line,int column);
  virtual void  SearchInList (WORD wP);
  virtual BOOL  SearchStringInList (LPSTR SearchStr,LPSTR prefix,LPSTR doOpen) 
    { 
    return TRUE; 
    }
  virtual void  OnCommand (WORD wP);

  virtual LPVOID GetFirstContext();
  virtual LPVOID GetNextContext(LPVOID oldConext);

  virtual LPSTR  GetMenuName();
  virtual LPSTR  ProfBase();
  virtual int    GetDropType (int DownColumn);

  virtual BOOL   AllowClose();
  virtual BOOL   AllowChange(LPFLDLINE h,int Column)
    { return EnableInput() ; }
  };


