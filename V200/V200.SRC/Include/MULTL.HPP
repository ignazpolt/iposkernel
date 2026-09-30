///////////////////////////////////////////////////////
//  Implementierung der Multilisten
//  $Header:   P:/marille/clinicum/include/rev/multl.hpv   1.2   02 Feb 1996 11:00:04   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/multl.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:00:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   23 Nov 1995 13:36:42   GERHOLD
// SingleList::WorkOn (int w, int h) ... neue Parameter
// 
//    Rev 1.0   24 Jun 1994 17:01:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   18 Aug 1993 10:40:16   HANNES
// ??
// 
//    Rev 1.0   19 Jun 1993 19:33:54   HANNES
// Initial revision.
///////////////////////////////////////////////////////
#ifndef MULTI_INCLUDED
#define MULTI_INCLUDED

struct FAR MultiListItem {
  MultiListItem FAR *Next;
  WORD IntNum;    // Interne Nummer
  WORD sh;        // Hotkey
  LPSTR shtxt;    // Kurztext, der uebernommen wird
  LPSTR ltxt;     // Langtext, der in der Liste erscheint
  };

typedef MultiListItem FAR *LPMLI;

DLLExport int _export GetIndex (LPMLI Root,WORD IntNum);
DLLExport LPSTR _export GetWordText (LPMLI Root,WORD IntNum);
void GetIndexText (LPMLI Root,int Index,LPSTR res);
BOOL CheckItem (LPMLI Root,WORD wP,WORD FAR *Index);
DLLExport BOOL _export AddItem (LPMLI FAR *Root,WORD IntNum,LPSTR sh,LPSTR shtxt,LPSTR ltxt);
DLLExport BOOL _export DelItem (LPMLI FAR *Root,WORD IntNum);

extern void SetDlgPos (HWND hDlg,HWND ActDlgOwner,LPRECT fr,LPRECT cr);

class FAR MultiList {
 private :
  BOOL DelIndex (WORD index);
  BOOL AddIndex (WORD index);
  LPSTR PushIndex (LPSTR txt,WORD Index);
  WORD SkipIndex (LPSTR FAR &h);
  BOOL IsIndGreater (WORD ind1,WORD ind2);  // Liefert TRUE, wenn ind2
                                            // in der Liste vor ind1 gefunden
                                            // wurde
 public :
  LPMLI List;
  LPSTR restxt;
  LPRECT fr,cr;
  DLLExport _export ~MultiList ();
  DLLExport _export MultiList (LPMLI l,LPSTR txt);

  void Fill (HWND hLWnd);
  void Select (HWND hLWnd);
  void GetRes (HWND hLWnd);
  void SetPos(HWND hDlg);

  DLLExport BOOL _export DelItem (WORD cPos);
  DLLExport BOOL _export AddItem (WORD wP);

  DLLExport BOOL _export WorkOn (HWND hWnd,LPRECT fieldRect,LPRECT ClientRect);
  };

class FAR SinglList {
  LPSTR Strings;    // Strings, mit '\0' implementiert
  LPRECT fr,cr;

 public :
  int res;          // Selektion, wenn eine getroffen wurde
  void SetPos(HWND hDlg);
  void Fill (HWND hLWnd);
  void Select (HWND hLWnd);
  void GetRes (HWND hLWnd);
  DLLExport BOOL _export WorkOn (HWND hWnd,LPRECT fieldRect,LPRECT ClientRect,
                       int w = 0,int h = 0);
  DLLExport _export ~SinglList ();
  DLLExport _export SinglList (LPSTR txt,int res);
  };

#endif

