////////////////////////////////////////////////////////////////
//      2dim. Liste
////////////////////////////////////////////////////////////////
struct FAR secondListEle;
struct FAR firstListEle {
  firstListEle FAR *next;
  WORD Ind;
  secondListEle FAR *ListStart;
  void FreeMem ();
  };
typedef firstListEle FAR *LPFLE;

struct FAR secondListEle {
  secondListEle FAR *next ;
  };
typedef secondListEle FAR *LPSLE;

class FAR ListEle {
 public :
  void FAR *data;
  int datasize;
  ListEle (void FAR *d,int s) { data = d ; datasize = s ; }
  };


typedef void (* LISTTRFUNCTION) (LPVOID,LPVOID);
typedef void (* FULLLISTTRFUNCTION) (WORD,LPVOID,LPVOID);

class FAR dList {
 private :
  // GLOBALHANDLE FAR *hGmem;
  LPFLE FAR *ListStart;
  LPFLE actList;
 public :
  dList (LPFLE FAR *St) 
    { ListStart = St ; }
  dList &operator[] (WORD);
  void Add(void FAR *,int);
  dList &operator+= (ListEle d)
    { Add (d.data,d.datasize); return *this ; }
  dList &operator+= (DWORD w)
    { Add (&w,sizeof(DWORD)) ; return *this ; }
  void Traverse (WORD,LISTTRFUNCTION,LPVOID);
  void Traverse (FULLLISTTRFUNCTION,LPVOID);
  };

class FAR eList {
 private :
  GLOBALHANDLE FAR *hGmem;
  LPSLE FAR *ListStart;
 public :
  eList (LPSLE FAR *St) 
    { ListStart = St ; }
  void Add(void FAR *,int);
  eList &operator+= (ListEle d)
    { Add (d.data,d.datasize); return *this ; }
  eList &operator+= (DWORD w)
    { Add (&w,sizeof(DWORD)) ; return *this ; }
  void Traverse (LISTTRFUNCTION,LPVOID);
  };

