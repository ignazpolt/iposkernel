//////////////////////////////////////////////////////////////////
//  Drag und Drop innerhalb des Tools
//////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/drdrop.hpv   1.10   02 Feb 1996 11:01:18   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/drdrop.hpv  $
// 
//    Rev 1.10   02 Feb 1996 11:01:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   26 Apr 1995 15:31:44   HANNES
// 
//    Rev 1.8   10 Apr 1995 10:45:38   GERHOLD
// 
//    Rev 1.7   03 Mar 1995 11:02:22   HANNES
// 
//    Rev 1.6   24 Feb 1995 11:13:28   GERHOLD
// 
//    Rev 1.5   16 Feb 1995 12:34:38   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.4   08 Aug 1994 17:39:46   GERHOLD
// Drag & Drop reagiert auch auf OK aus den Dialogen.
// 
//    Rev 1.3   01 Aug 1994 15:40:00   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.2   25 Jul 1994 09:47:42   GERHOLD
// Drag & Drop fuer Formate
// 
//    Rev 1.1   20 Jul 1994 17:04:02   GERHOLD
// Einige inline Funktionen aus der Klassendeklaration ins .CPP File geholt
// 
//    Rev 1.0   24 Jun 1994 17:01:30   HANNES
// Neuuebernahme clinicum
//
#define DDTYPE_NONE     0
#define DDTYPE_BITMAP   1
#define DDTYPE_VAR      2
#define DDTYPE_TOOL     3
#define DDTYPE_TEXT     4
#define DDTYPE_FORMAT   5
#define DDTYPE_COLOR    6
#define DDTYPE_TABLE    7
#define DDTYPE_INTTABLE 8
#define DDTYPE_EDITOR   9
#define DDTYPE_VARNAME  10


class FAR Drag_Drop {
 public :
  int            x1,y1,x2,y2;
  Drag_Drop FAR *Next;
  HWND           DropWnd;
  HWND           hRefWnd;

  LPWORD         Typearr;
  int AnzTypes;
//  BOOL IsServer;

  virtual HCURSOR GetHitCursor();
  virtual HCURSOR GetNonHitCursor();
  virtual void DoDrop (LPVOID dropData, WORD Type) { }

  void AddType (WORD t);
  void GetKoords (HWND hWnd);
  BOOL TestType (WORD t);
  BOOL TestRefWnd (HWND hWnd)    { return (hRefWnd == hWnd); }
  BOOL TestKoord (LPPOINT pt);
  HCURSOR TestPos (LPPOINT pt, HWND hServer, BOOL FAR *doStop);
  BOOL TestWnd (HWND hWnd);

  void AddToList ();
  void RemoveFromList ();

  Drag_Drop (WORD t,HWND dropWnd,HWND RefWnd)
    { 
    AddToList () ;
    DropWnd = dropWnd;
    GetKoords (dropWnd);
    AddType (t);
    hRefWnd = RefWnd ;
    }

  virtual ~Drag_Drop ()          { FreeGlobMem (Typearr) ; }

  LPVOID operator new (size_t size)
    {
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };
typedef Drag_Drop FAR *LPDRAGDROP;


struct BitmapDropData {
  LPSTR BitmapName;
  int x;
  int y;
  };
typedef BitmapDropData FAR *LPBDD;


struct VarDropData {
  char TableName[64];
  char VarName[64];
  };
typedef VarDropData FAR *LPVDD;


struct ToolDropData {
  POINT pts;
  LPSTR ToolName;
  };
typedef ToolDropData FAR *LPTOOLDD;


struct FormatDropData {
  int FormatNr;
  };
typedef FormatDropData FAR *LPFDD;


struct ColorDropData {
  LONG LineAttr;
  };
typedef ColorDropData FAR *LPCLRDD;

class FAR Bitmap_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Bitmap_Drop (HWND dropWnd,HWND RefWnd) : Drag_Drop (DDTYPE_BITMAP,dropWnd,RefWnd)
    { }
  };


class FAR Var_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Var_Drop (HWND dropWnd,HWND RefWnd) : Drag_Drop (DDTYPE_VAR,dropWnd,RefWnd)
    { }
  };


class FAR Tool_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Tool_Drop (HWND dropWnd) : Drag_Drop (DDTYPE_TOOL,dropWnd,dropWnd)
    { }
  };


class FAR Text_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Text_Drop (HWND dropWnd,HWND RefWnd) : Drag_Drop (DDTYPE_TEXT,dropWnd,RefWnd)
    { }
  };

class FAR Table_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Table_Drop (HWND dropWnd,HWND RefWnd) : Drag_Drop (DDTYPE_TABLE,dropWnd,RefWnd)
    { }
  };

class FAR Format_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);

  Format_Drop (HWND dropWnd,HWND RefWnd) : Drag_Drop (DDTYPE_FORMAT, dropWnd, RefWnd)
    { }
  };

class FAR Color_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);
  Color_Drop (HWND dropWnd, HWND RefWnd) : Drag_Drop (DDTYPE_COLOR, dropWnd, RefWnd)
    { }
  };

class FAR Editor_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);
  Editor_Drop (HWND dropWnd, HWND RefWnd) : Drag_Drop (DDTYPE_EDITOR, dropWnd, RefWnd)
    { }

  virtual HCURSOR GetHitCursor();
  };

class FAR VarList_Drop : public Drag_Drop {
 public :
  virtual void DoDrop (LPVOID dropData, WORD Type);
  VarList_Drop (HWND dropWnd, HWND RefWnd) : Drag_Drop (DDTYPE_VARNAME, dropWnd, RefWnd)
    { }
  };


//***************************************************
// Implementation von "Editor_Drop" in "WONSCRIP.CPP"
//***************************************************

//***************************************************
// Implementation von "Table_Drop" in "RIWND.CPP"
//***************************************************
  
BOOL DDOnMouseMove (WORD Type,LPVOID dropData,LPPOINT pt,HWND hClient,BOOL last);
void DDOnOKButton (WORD Type, LPVOID dropData, HWND hWndEdit);
void RemoveAll (HWND RefWnd);
