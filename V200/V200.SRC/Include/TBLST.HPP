/*-----< Definition der Subtabellen fuer die Header >-------------*/
//
// $Header:   P:/marille/clinicum/include/rev/tblst.hpv   1.2   02 Feb 1996 11:00:44   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/tblst.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:00:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   26 Apr 1995 15:31:46   HANNES
// 
//    Rev 1.0   29 Jan 1995 11:49:14   HANNES
// Initial revision.
// 
//    Rev 1.0   24 Jan 1995 11:00:12   HANNES
// Initial revision.
//

class FAR KeyList : public FldList {
 private :
  FldCheck FAR *kNames;
  HWND hWndParent;
 public :
  KeyList (HWND hW,LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { hWndParent = hW ; }

  LPFLDLINE Store (HFILE fm,FldCheck FAR *c);
  BOOL    WriteHeader (HFILE fm);
  BOOL    WriteLine (HFILE fm,LPFLDLINE h,FldCheck FAR *c);
  BOOL    WriteEnd (HFILE fm);

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

  virtual LPVOID GetFirstContext();
  virtual LPVOID GetNextContext(LPVOID oldConext);

  virtual LPSTR  GetMenuName();
  virtual LPSTR  ProfBase();
  virtual int    GetColWidth(int Column);
  virtual BOOL   AllowClose();
  virtual void   DoDrop (int x,int y,LPVOID Data,WORD Type);
  };

class FAR FKList : public FldList {
 private :
  HWND hWndParent;
 public :
  FKList (HWND hW,LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { hWndParent = hW ; }

  BOOL      WriteHeader (HFILE fm);
  BOOL      WriteLine (HFILE fm,LPFLDLINE h,BOOL FAR &IsExtended,FldCheck FAR *c);
  BOOL      WriteEnd (HFILE fm);
  LPFLDLINE Store (HFILE fm,FldCheck FAR *c);

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

  virtual LPVOID GetFirstContext();
  virtual LPVOID GetNextContext(LPVOID oldConext);

  virtual LPSTR  GetMenuName();
  virtual LPSTR  ProfBase();
  virtual int    GetColWidth(int Column);
  virtual BOOL   AllowClose();
  virtual void   DoDrop (int x,int y,LPVOID Data,WORD Type);
  };

extern KeyList FAR *WorkOnKeyList (HWND hWnd,HWND hWMain,LPTABLEDEF td);
extern FKList FAR *WorkOnFKList (HWND hWnd,HWND hWMain,LPTABLEDEF td);

