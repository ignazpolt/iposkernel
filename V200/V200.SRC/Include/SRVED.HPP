/*-----------------------------*/
/*  Bearbeiten der Serverinfo  */
/*-----------------------------*/
//
// $Header:   P:/marille/clinicum/include/rev/srved.hpv   1.1   02 Feb 1996 11:00:42   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/srved.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   29 Jan 1995 11:49:12   HANNES
// Initial revision.
class FAR SrvEd {
 public :
  SrvEd FAR *Next;
  LPSTR Caption;
  GLOBALHANDLE hGTxt;
  HWND hWnd;

  SrvEd (LPSTR c,GLOBALHANDLE hGT);
  ~SrvEd ();
  
  void        Hide();
  void        Show();
  void        Create();
  void        Register();
  void        InitializeMenu (HMENU hMenu);

  void        WritePos();
  void        GetPos(int FAR *x,int FAR *y,int FAR *w,int FAR *h);
  int         GetProfInt (LPSTR Name,int def);
  void        SetProfInt (LPSTR Name,int val);

  GLOBALHANDLE GetServerInfo ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

