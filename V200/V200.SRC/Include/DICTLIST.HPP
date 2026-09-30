//
//  $Header:   P:/marille/clinicum/include/rev/dictlist.hpv   1.1   02 Feb 1996 10:59:14   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/dictlist.hpv  $
// 
//    Rev 1.1   02 Feb 1996 10:59:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:12   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   06 May 1993 21:33:02   HANNES
// Initial revision.
//

struct dl_node {
  struct dl_node FAR *Parent;
  struct dl_node FAR *Alt;
  BOOL termNode;
  union {
    struct dl_node FAR *Sub;
    LPVOID Data;
    } Next;
  char ch;
  };
typedef dl_node FAR *LPDLNODE;

#define SSN_FAULT       0
#define SSN_NOSUCHSTR   1
#define SSN_NORMAL      2
#define SSN_TERMSYM     3

typedef void (* DLCALLBACK) (LPVOID PrivData,LPVOID MyData);

class FAR DictList {
 protected :
  LPDLNODE top;
  LPDLNODE act;

  void deleteNode (LPDLNODE);
  LPDLNODE EleminateFromList (LPDLNODE first,LPDLNODE todel,LPDLNODE alt);

 public :
  DLLExport LPVOID _export operator new (size_t size);
  DLLExport void _export operator delete (LPVOID obj);

  DLLExport _export DictList ();
  DLLExport _export ~DictList ();

  virtual DLLExport int _export compare (char ent_ch,char node_ch);
  BOOL SetActToTop ()
    { return ((act = top) != NULL) ; }
  DLLExport int _export SearchSubNode (char ch,LPVOID FAR &Data);
  DLLExport int _export SearchSubNode (LPSTR shent,LPVOID FAR &Data);
  DLLExport BOOL _export ChangeData (LPVOID newData);
  inline BOOL ChangeData (LPSTR shent,LPVOID newData);
  DLLExport BOOL _export InsertEntry (LPSTR shent,LPVOID Data);
  DLLExport BOOL _export DelEntry ();
  inline BOOL DelEntry (LPSTR shent);
  DLLExport void _export TraverseSub (DLCALLBACK callback,LPVOID MyData,LPDLNODE node);
  inline void TraverseSub (DLCALLBACK callback,LPVOID MyData);
  inline void Traverse (DLCALLBACK callback,LPVOID MyData);
  };

inline BOOL DictList::ChangeData (LPSTR shent,LPVOID newData)
  { 
  LPVOID h;
  if (SearchSubNode(shent,h) == SSN_TERMSYM) return ChangeData (newData);
  else                                       return FALSE ;
  }

inline BOOL DictList::DelEntry (LPSTR shent)
  {
  LPVOID h;
  if (SearchSubNode(shent,h) == SSN_TERMSYM) return DelEntry ();
  else                                       return FALSE ;
  }

inline void DictList::TraverseSub (DLCALLBACK callback,LPVOID MyData)
  {
  if (!act->termNode)
    TraverseSub (callback,MyData,act);
  else
    TraverseSub (callback,MyData,act->Next.Sub);
  }

inline void DictList::Traverse (DLCALLBACK callback,LPVOID MyData)
  {
  TraverseSub (callback,MyData,top);
  }
