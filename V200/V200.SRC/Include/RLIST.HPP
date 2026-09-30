/////////////////////////////////////////////////////////////////////////
//  Verwaltung einer Liste von Texten, die im ini File gespeichert wird
/////////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/rlist.hpv   1.11   26 Mar 1999 18:08:16   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/rlist.hpv  $
// 
//    Rev 1.11   26 Mar 1999 18:08:16   Wolfgang
// 1.) OnVKReturn braucht caseSensitive-Parameter.
// 
//    Rev 1.10   17 Mar 1999 19:24:36   Wolfgang
// 1.) CheckCommand mit zusaetzlichen Parametern.
// 2.) RemoveCurrentElem neu.
// 
//    Rev 1.9   16 Mar 1999 16:12:24   Wolfgang
// 1.) Erweiterungen fuer Workspace.
// 
//    Rev 1.8   12 Mar 1999 13:51:44   Wolfgang
// 1.) InsertEntry gibt BOOL zurueck und hat neuen Parameter caseSensitive.
// 
//    Rev 1.7   04 May 1998 11:38:44   Gerhold
// ReplaceCombo ... zusaetzlicher Parameter BOOL InsertEmptyString fuer INI
// 
//    Rev 1.6   21 Oct 1996 18:54:56   HANNES
// 
//    Rev 1.5   02 Feb 1996 11:01:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   27 Aug 1995 13:00:52   HANNES
// 
//    Rev 1.3   07 Jun 1995 12:20:00   GERHOLD
// Klassen auf FAR, ReplaceCombo (COMMDLG)
// 
//    Rev 1.2   02 Jan 1995 09:32:16   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.1   18 Jul 1994 08:45:36   GERHOLD
// \t fr Tabulator in Menue bei Funktion "HKTemplate()"
// 
//    Rev 1.0   12 Jul 1994 14:46:58   HANNES
// Initial revision.
//
struct RListEntry {
  RListEntry FAR *Next;
  RListEntry FAR *Prev;
  LPSTR Text;
  int Zeile;
  int Spalte;
  };
typedef RListEntry FAR *LPRENT;
class FAR RList {
 public :
  LPRENT First;
  HWND hWnd;
  int SubID;

  void ReadEntrys (BOOL InsertEmptyString = FALSE);
  void WriteEntrys ();
  void DelEntrys ();
  void DelEntrysAtTail ();
  LPRENT GetLast ();

  virtual LPRENT GetLineToCheck()
    { return First ; }
  BOOL InsertEntry (LPSTR Text,BOOL MenuModify = TRUE,BOOL caseSensitive = FALSE, BOOL forceInsert = FALSE,
                    int zeile = 0, int spalte = 0);
  void SetMenuWnd (HWND hW,int S)
    {
    hWnd = hW ; SubID = S ;
    }
  void CreateMenu ();
  void DestroyMenu ();
  LPSTR CheckCommand (WORD wP, BOOL removeEntry = FALSE, 
                      LPSTR strBuffer = NULL, LPINT zeile = NULL, LPINT spalte = NULL);
  void RemoveCurrentElem (LPRENT lpe);
  void SetCurrentElemOnTop (LPRENT lpe);

  virtual int MaxEntrys ()
    { return 8 ; }
  virtual BOOL UseMenu ()
    { return FALSE ; }
  virtual BOOL UsePosition ()
    { return FALSE ; }
  virtual LPSTR GetEntryTemplate ()
    { return "" ; }
  virtual int GetMENUBaseId ()
    { return 0 ; }
  virtual LPSTR HKTemplate ()
    { return "" ; }
  virtual BOOL ClearSectionOnWrite ()
    { return FALSE ; }
  virtual LPSTR SectionName ()
    { return "RListEntrys" ; }
  virtual int CmpEntry (LPSTR txt1, LPSTR txt2, BOOL caseSensitive);
  };

class FAR FileNameList : public RList {
 public :
  virtual BOOL UsePosition ()
    { return TRUE ; }
  };

class FAR FileNames : public FileNameList {
 public :
  virtual BOOL UseMenu ()
    { return TRUE ; }
  virtual LPSTR GetEntryTemplate ()
    { return "WFile" ; }
  virtual int GetMENUBaseId ()
    { return 3000 ; }
  virtual LPSTR HKTemplate ()
    { return " \tALT "; }
  };

class FAR WorkSpaceFileNames : public FileNameList {
 public :
  virtual int MaxEntrys ()
    { return 49 ; }
  virtual LPSTR GetEntryTemplate ()
    { return "WSFile" ; }
  virtual BOOL ClearSectionOnWrite ()
    { return TRUE ; }
  virtual LPSTR SectionName ()
    { return "WorkSpaceEntrys" ; }
  void RestoreWorkSpace ();
  };

class FAR SearchNames : public RList {
 public :
  void FillDialog (HWND hDlg,WORD Id);
  LPSTR GetTopString (BOOL InsertEmptyString = FALSE)
    {
    if (First == NULL)
      ReadEntrys (InsertEmptyString);
    return (First != NULL) ? First->Text : NULL ;
    }
  void OnCommand (HWND hDlg,WORD IdList,WORD IdEdit,LONG lP);
  void OnDialogInit (HWND hDlg,WORD IdList,WORD IdEdit);
  void OnDialogOk (HWND hDlg,WORD IdList,WORD IdEdit);
  virtual BOOL UseMenu ()
    { return FALSE ; }
  virtual LPSTR GetEntryTemplate ()
    { return "Search" ; }
  };

class FAR SearchFromCombo : public SearchNames {
 public:
  void FillCombo (HWND hWnd);
  
  void OnCommand (WPARAM wParam, LPARAM lParam);
  void OnInit (HWND hWnd);
  void OnVKReturn (HWND hWnd, BOOL InsertEmptyString = FALSE, BOOL caseSensitive = FALSE);
  };

class FAR ReplaceFromCombo : public SearchFromCombo {
 public :
  virtual LPSTR GetEntryTemplate ()
    { return "Replace" ; }
  };
  

#ifdef RLIST_MAIN
FileNames          SourceFileNames;
WorkSpaceFileNames WorkSpaceNames;
SearchFromCombo    SearchCombo;
ReplaceFromCombo   ReplaceCombo;
#else
extern FileNames          SourceFileNames;
extern WorkSpaceFileNames WorkSpaceNames;
extern SearchFromCombo    SearchCombo;
extern ReplaceFromCombo   ReplaceCombo;
#endif
