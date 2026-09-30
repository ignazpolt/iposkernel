//
//  Bearbeiten der Zugriffe fuer Joins in internen Tabellen
//  
// $Header:   P:/marille/clinicum/include/rev/jlst.hpv   1.3   21 Oct 1996 18:54:40   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/jlst.hpv  $
// 
//    Rev 1.3   21 Oct 1996 18:54:40   HANNES
// Eingabe von inner / outer join
// 
//    Rev 1.2   02 Feb 1996 11:00:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   26 Apr 1995 15:31:42   HANNES
// 
//    Rev 1.0   16 Feb 1995 12:43:30   HANNES
// Initial revision.
//

class FAR JoinList : public FldList {
 public :
  HWND hWndParent;
  JoinList (HWND hWP,LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { hWndParent = hWP ; }
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
  virtual void   OnCommand (WORD wP);
  virtual BOOL   AllowClose();
  virtual BOOL   AllowChange (LPFLDLINE h,int Column);

  void  AliasChanged (LPSTR old,LPSTR nw);
  int   GetSourceTableNr (LPFLDLINE h);
  int   GetDestTableNr (LPFLDLINE h);
  void  CheckJoins ();
  void  SetRIDef (LPFLDLINE h,int tnr,LPCLRIDEF rid,LPTABLEDEF tsource);
  void  AddTable (int TableNum,LPSTR TableName);
  void  DelTable(int TableNum);
  LPSTR GetJoinText (LPSTR buffer,int tnr);
  LPFLDLINE CheckWholeJoins ();
  };

class FAR IntFldList : public FldList {
 public :
  LPSTR FileName;
  JoinList FAR *jlst;
  jShow FAR *jWnd;
  HWND hWParent;

  IntFldList (HWND hWP,LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { hWParent = hWP ; }
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
  virtual void   OnCommand (WORD wP);
  virtual BOOL   AllowChange(LPFLDLINE h,int Column);

  BOOL  IsAllSelected (int tnr,LPSTR prefix = NULL);
  int   GetTableNr (LPSTR name);
  WORD  SearchVarID();
  WORD  GetFirstVarForTable();
  void  AliasChanged (LPFLDLINE h);
  void  AllAliasChanged (LPFLDLINE h);
  void  DelAllAlias (LPFLDLINE h,int t0);
  LPSTR GetAliasName (LPSTR res,LPFLDLINE line);
  LPFLDLINE GetVarLine (int tnr,WORD VarID,BOOL FAR *allSelected,LPSTR prefix);
  LPSTR GetRealVarName (int tnr,WORD VarID,LPSTR res);
  BOOL  AllVarsHere (int tnr,int AnzVars,WORD FAR *VarIDs);
  void  AddTable (int TableNum,LPSTR TableName);
  void  Attribute();
  void  DelTable(int TableNum);
  BOOL  Store ();
  BOOL  IsNameAllowed (LPSTR Name,LPFLDLINE h);
  LPFLDLINE CheckPrimary ();
  LPFLDLINE CheckDuplicate ();
  void GetOutFileName (LPSTR fName);
  void GetNameWithPrefix (LPSTR str,LPFLDLINE h);
  virtual int     GetDropType (int DownColumn)
    {
    if (DownColumn == 3)
      return DDTYPE_VARNAME ;
    else
      return 0 ;
    }
  };


