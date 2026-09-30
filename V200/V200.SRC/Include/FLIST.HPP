//
//  $Header:   P:/marille/clinicum/include/rev/flist.hpv   1.1   02 Feb 1996 11:00:20   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/flist.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 18:23:34   HANNES
// Initial revision.
// 
//    Rev 1.2   05 Jul 1993 14:49:42   HANNES
// Tab - Handling
// 
//    Rev 1.1   09 May 1993 17:47:42   HANNES
// Suchen in der Listbox..
// 
//    Rev 1.0   06 May 1993 21:34:58   HANNES
// Initial revision.
//
typedef BOOL (* ITEMTOTEXT) (LPSTR text,LPVOID itemdata,int size,int mode,LPSTR selstr);

#define LIST_MAXSHORT  20

#define TRANSLATE_FORDRAW     0
#define TRANSLATE_FORSEARCH   1

#define SEARCHMODE_SORTED     0

class FAR fList {
 protected :
  UINT CtlID;
  int iCaretPos;
  char ActShortCut[LIST_MAXSHORT];
  int xLeft;
  int DefFormat;
  ITEMTOTEXT itot;
  int SearchMode;

  int AnzItems;

  GLOBALHANDLE ActSels;
  WORD SelIndex;
  GLOBALHANDLE SearchItems (HWND hLWnd,LPSTR Text,int FAR &AnzItems,GLOBALHANDLE hGold,int Anzold);
  WORD NextSel (HWND hLWnd);
  WORD ActSel (HWND hLWnd);
  int FAR *TabPos;
 public :
  DLLExport LPVOID _export operator new (size_t size);
  DLLExport void _export operator delete (LPVOID obj);

  DLLExport _export fList(UINT ID,int DefFormat,ITEMTOTEXT itot,int SM);
  DLLExport _export ~fList();

  DLLExport BOOL _export Draw (DRAWITEMSTRUCT FAR *ds);
  DLLExport BOOL _export Measure (HWND hDlg,MEASUREITEMSTRUCT FAR *ms);
  DLLExport LONG _export ChartoItem (HWND hDlg,WORD wKey,int iCaretPos);
  DLLExport WORD _export SearchBest (HWND hLWnd,LPSTR Text);
  void CharToItem (WORD wP,WORD Ident);

  void SetTabPos(int FAR *tabs,int AnzTabs);
#ifdef CFIELD_INCLUDED
  void GetTab (TCB FAR *b);
#endif
  };

DLLExport void _export SubClassSearchBox (HWND hLWnd);
DLLExport int _export WINAPI SearchNextTab (int x,int FAR *TabPos,int AnzTabs);
void CheckStrLen (LPSTR txt,int xb,int xe,HDC hDC);
DLLExport void _export WINAPI CheckOutTxt (LPSTR txt,HDC hDC,int Format,int FAR *TabPos,int AnzTabs);

